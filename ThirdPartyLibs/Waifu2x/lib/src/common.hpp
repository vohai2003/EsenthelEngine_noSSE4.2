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

#ifndef COMMON_HPP
#define COMMON_HPP

#include <vector>
#include "cvwrap.hpp"

namespace w2xc
{

#define ALIGN_UP(v,a) (((v+(a-1))/(a))*(a))

void pack_mat(float *out, std::vector<W2Mat> &inputPlanes, int w, int h, int nplane);

void unpack_mat(std::vector<W2Mat> &outputPlanes, const float *in, int w, int h, int nplane);

void unpack_mat1(W2Mat &outputMat, const float *in, int w, int h);

void pack_mat_rgb(float *out, W2Mat &inputPlane, int w, int h);

void pack_mat_rgb_f32(float *out, W2Mat &inputPlane, int w, int h);

void pack_mat_bgr(float *out, W2Mat &inputPlane, int w, int h);

void unpack_mat_rgb(W2Mat &outputMat, const float *in, int w, int h);

void unpack_mat_rgb_f32(W2Mat &outputMat, const float *in, int w, int h);

void unpack_mat_bgr(W2Mat &outputMat, const float *in, int w, int h);

}

#endif
