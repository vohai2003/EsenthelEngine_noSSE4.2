/*
* The MIT License (MIT)
* Copyright (c) 2015 amigo(white luckers), tanakamura, DeadSix27, YukihoAA and contributors
* 
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
* 
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
* 
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*/

#ifndef W2XCONV_H
#define W2XCONV_H

#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>
#include <vector>
#include "Env.hpp"
#include "modelHandler.hpp"

namespace w2xc
{

enum W2XConvGPUMode
{
	W2XCONV_GPU_DISABLE = 0,
	W2XCONV_GPU_AUTO = 1,
	W2XCONV_GPU_FORCE_OPENCL = 2
};

enum W2XConvErrorCode
{
	W2XCONV_NOERROR,
	W2XCONV_ERROR_WIN32_ERROR,	/* errno_ = GetLastError() */
	W2XCONV_ERROR_WIN32_ERROR_PATH, /* u.win32_path */
	W2XCONV_ERROR_LIBC_ERROR,	/* errno_ */
	W2XCONV_ERROR_LIBC_ERROR_PATH,	/* libc_path */

	W2XCONV_ERROR_MODEL_LOAD_FAILED, /* u.path */

	W2XCONV_ERROR_IMREAD_FAILED,	/* u.path */
	W2XCONV_ERROR_IMWRITE_FAILED,	/* u.path */

	W2XCONV_ERROR_RGB_MODEL_MISMATCH_TO_Y,
	W2XCONV_ERROR_Y_MODEL_MISMATCH_TO_RGB_F32,

	W2XCONV_ERROR_OPENCL,	/* u.cl_error */

	W2XCONV_ERROR_SCALE_LIMIT,
	W2XCONV_ERROR_SIZE_LIMIT,
	W2XCONV_ERROR_WEBP_SIZE_LIMIT,
	W2XCONV_ERROR_WEBP_LOSSY_SIZE_LIMIT,
};

struct W2XConvError
{
	enum W2XConvErrorCode code;

	union
	{
		char *path;
		unsigned int errno_;

		struct
		{
			unsigned int errno_;
			char *path;
		} win32_path;

		struct
		{
			int errno_;
			char *path;
		} libc_path;

		struct
		{
			int error_code;
			int dev_id;
		} cl_error;
	} u;
};

enum W2XConvProcessorType
{
	W2XCONV_PROC_HOST,
	W2XCONV_PROC_CUDA,
	W2XCONV_PROC_OPENCL
};

enum W2XConvFilterType
{
	W2XCONV_FILTER_DENOISE0,
	W2XCONV_FILTER_DENOISE1,
	W2XCONV_FILTER_DENOISE2,
	W2XCONV_FILTER_DENOISE3,
	W2XCONV_FILTER_SCALE2x
};

/* W2XConvProcessor::sub_type */
#define W2XCONV_PROC_HOST_OPENCV 0x0000
#define W2XCONV_PROC_HOST_SSE3 0x0001
#define W2XCONV_PROC_HOST_AVX 0x0002
#define W2XCONV_PROC_HOST_FMA 0x0003

#define W2XCONV_PROC_HOST_NEON 0x0104

#define W2XCONV_PROC_HOST_ALTIVEC 0x0205

#define W2XCONV_PROC_CUDA_NVIDIA 0

#define W2XCONV_PROC_OPENCL_PLATFORM_MASK 0x00ff
#define W2XCONV_PROC_OPENCL_DEVICE_MASK   0xff00

#define W2XCONV_PROC_OPENCL_PLATFORM_NVIDIA 0
#define W2XCONV_PROC_OPENCL_PLATFORM_AMD 1
#define W2XCONV_PROC_OPENCL_PLATFORM_INTEL 2
#define W2XCONV_PROC_OPENCL_PLATFORM_UNKNOWN 0xff

#define W2XCONV_PROC_OPENCL_DEVICE_CPU (1<<8)
#define W2XCONV_PROC_OPENCL_DEVICE_GPU (2<<8)
#define W2XCONV_PROC_OPENCL_DEVICE_UNKNOWN (0xff<<8)

#define W2XCONV_PROC_OPENCL_NVIDIA_GPU (W2XCONV_PROC_OPENCL_PLATFORM_NVIDIA | W2XCONV_PROC_OPENCL_DEVICE_GPU)
#define W2XCONV_PROC_OPENCL_AMD_GPU (W2XCONV_PROC_OPENCL_PLATFORM_AMD | W2XCONV_PROC_OPENCL_DEVICE_GPU)
#define W2XCONV_PROC_OPENCL_INTEL_GPU (W2XCONV_PROC_OPENCL_PLATFORM_INTEL | W2XCONV_PROC_OPENCL_DEVICE_GPU)
#define W2XCONV_PROC_OPENCL_UNKNOWN_GPU (W2XCONV_PROC_OPENCL_PLATFORM_UNKNOWN | W2XCONV_PROC_OPENCL_DEVICE_GPU)

#define W2XCONV_PROC_OPENCL_AMD_CPU (W2XCONV_PROC_OPENCL_PLATFORM_AMD | W2XCONV_PROC_OPENCL_DEVICE_CPU)
#define W2XCONV_PROC_OPENCL_INTEL_CPU (W2XCONV_PROC_OPENCL_PLATFORM_INTEL | W2XCONV_PROC_OPENCL_DEVICE_CPU)
#define W2XCONV_PROC_OPENCL_UNKNOWN_CPU (W2XCONV_PROC_OPENCL_PLATFORM_UNKNOWN | W2XCONV_PROC_OPENCL_DEVICE_CPU)

#define W2XCONV_PROC_OPENCL_UNKNOWN (W2XCONV_PROC_OPENCL_PLATFORM_UNKNOWN | W2XCONV_PROC_OPENCL_DEVICE_UNKNOWN)

struct W2XConvProcessor
{
	enum W2XConvProcessorType type;
	int sub_type;
	int dev_id;
	int num_core;
	const char *dev_name;
};

struct W2XConv
{
	struct W2XConvError last_error;
	const struct W2XConvProcessor *target_processor;

	std::string dev_name;

	ComputeEnv env;

	std::vector<Model> scale2_models;
};

const struct W2XConvProcessor *w2xconv_get_processor_list(size_t *ret_num);

struct W2XConv* w2xconv_init();
void            w2xconv_fini(struct W2XConv *conv);

bool w2xconv_2x_rgb_f32_esenthel(struct W2XConv *conv, unsigned char *data, size_t pitch, int w, int h, bool clamp);

void clearError(W2XConv *conv);

}

#endif
