/*
 * Software License Agreement (BSD License)
 *
 *  Point Cloud Library (PCL) - www.pointclouds.org
 *  Copyright (c) 2010-2012, Willow Garage, Inc.
 *
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *   * Neither the name of Willow Garage, Inc. nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 *  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 *  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 *
 * $Id$
 *
 */

#ifndef PCL_2D_KERNEL_IMPL_HPP
#define PCL_2D_KERNEL_IMPL_HPP

template<typename PointT>
void
pcl::pcl_2d::kernel<PointT>::fetchKernel (PointCloud<PointT> &kernel)
{
  switch (kernel_type_)
  {
  case SOBEL_X:
    sobelKernelX (kernel);
    break;
  case SOBEL_Y:
    sobelKernelY (kernel);
    break;
  case PREWITT_X:
    prewittKernelX (kernel);
    break;
  case PREWITT_Y:
    prewittKernelY (kernel);
    break;
  case ROBERTS_X:
    robertsKernelX (kernel);
    break;
  case ROBERTS_Y:
    robertsKernelY (kernel);
    break;
  case LOG:
    loGKernel (kernel);
    break;
  case DERIVATIVE_CENTRAL_X:
    derivativeXCentralKernel (kernel);
    break;
  case DERIVATIVE_FORWARD_X:
    derivativeXForwardKernel (kernel);
    break;
  case DERIVATIVE_BACKWARD_X:
    derivativeXBackwardKernel (kernel);
    break;
  case DERIVATIVE_CENTRAL_Y:
    derivativeYCentralKernel (kernel);
    break;
  case DERIVATIVE_FORWARD_Y:
    derivativeYForwardKernel (kernel);
    break;
  case DERIVATIVE_BACKWARD_Y:
    derivativeYBackwardKernel (kernel);
    break;
  case GAUSSIAN:
    gaussianKernel (kernel);
  }
}

template<typename PointT>
void
pcl::pcl_2d::kernel<PointT>::gaussianKernel (PointCloud<PointT> &kernel)
{
  float sum = 0;
  kernel.resize (kernel_size_ * kernel_size_);
  kernel.height = kernel_size_;
  kernel.width = kernel_size_;
  for (int i = 0; i < kernel_size_; i++)
  {
    for (int j = 0; j < kernel_size_; j++)
    {
      kernel (j, i).intensity = exp (-(((i - kernel_size_ / 2) * (i - kernel_size_ / 2) + (j - kernel_size_ / 2) * (j - kernel_size_ / 2)) / (2 * sigma_ * sigma_)));
      sum += kernel (j, i).intensity;
    }
  }
  /*normalizing the kernel*/
  for (int i = 0; i < kernel_size_; i++)
  {
    for (int j = 0; j < kernel_size_; j++)
    {
      kernel (j, i).intensity /= sum;
    }
  }
}

template<typename PointT>
void
pcl::pcl_2d::kernel<PointT>::loGKernel (PointCloud<PointT> &kernel)
{
  float sum = 0;
  float temp = 0;
  kernel.resize (kernel_size_ * kernel_size_);
  kernel.height = kernel_size_;
  kernel.width = kernel_size_;
  for (int i = 0; i < kernel_size_; i++)
  {
    for (int j = 0; j < kernel_size_; j++)
    {
      temp = (((i - kernel_size_ / 2) * (i - kernel_size_ / 2) + (j - kernel_size_ / 2) * (j - kernel_size_ / 2)) / (2 * sigma_ * sigma_));
      kernel (j, i).intensity = (1 - temp) * exp (-temp);
      sum += kernel (j, i).intensity;
    }
  }
  for (int i = 0; i < kernel_size_; i++)
  {
    for (int j = 0; j < kernel_size_; j++)
    {
      kernel (j, i).intensity /= sum;
    }
  }
}

template<typename PointT>
void
pcl::pcl_2d::kernel<PointT>::sobelKernelX (PointCloud<PointT> &kernel)
{
  kernel.resize (9);
  kernel.height = 3;
  kernel.width = 3;
  kernel (0, 0).intensity = -1; kernel (1, 0).intensity = 0; kernel (2, 0).intensity = 1;
  kernel (0, 1).intensity = -2; kernel (1, 1).intensity = 0; kernel (2, 1).intensity = 2;
  kernel (0, 2).intensity = -1; kernel (1, 2).intensity = 0; kernel (2, 2).intensity = 1;
}

template<typename PointT>
void
pcl::pcl_2d::kernel<PointT>::prewittKernelX (PointCloud<PointT> &kernel)
{
  kernel.resize (9);
  kernel.height = 3;
  kernel.width = 3;
  kernel (0, 0).intensity = -1; kernel (1, 0).intensity = 0; kernel (2, 0).intensity = 1;
  kernel (0, 1).intensity = -1; kernel (1, 1).intensity = 0; kernel (2, 1).intensity = 1;
  kernel (0, 2).intensity = -1; kernel (1, 2).intensity = 0; kernel (2, 2).intensity = 1;
}

template<typename PointT>
void
pcl::pcl_2d::kernel<PointT>::robertsKernelX (PointCloud<PointT> &kernel)
{
  kernel.resize (4);
  kernel.height = 2;
  kernel.width = 2;
  kernel (0, 0).intensity = 1; kernel (1, 0).intensity = 0;
  kernel (0, 1).intensity = 0; kernel (1, 1).intensity = -1;
}

template<typename PointT>
void
pcl::pcl_2d::kernel<PointT>::sobelKernelY (PointCloud<PointT> &kernel)
{
  kernel.resize (9);
  kernel.height = 3;
  kernel.width = 3;
  kernel (0, 0).intensity = -1; kernel (1, 0).intensity = -2; kernel (2, 0).intensity = -1;
  kernel (0, 1).intensity = 0; kernel (1, 1).intensity = 0; kernel (2, 1).intensity = 0;
  kernel (0, 2).intensity = 1; kernel (1, 2).intensity = 2; kernel (2, 2).intensity = 1;
}

template<typename PointT>
void
pcl::pcl_2d::kernel<PointT>::prewittKernelY (PointCloud<PointT> &kernel)
{
  kernel.resize (9);
  kernel.height = 3;
  kernel.width = 3;
  kernel (0, 0).intensity = 1; kernel (1, 0).intensity = 1; kernel (2, 0).intensity = 1;
  kernel (0, 1).intensity = 0; kernel (1, 1).intensity = 0; kernel (2, 1).intensity = 0;
  kernel (0, 2).intensity = -1; kernel (1, 2).intensity = -1; kernel (2, 2).intensity = -1;
}

template<typename PointT>
void
pcl::pcl_2d::kernel<PointT>::robertsKernelY (PointCloud<PointT> &kernel)
{
  kernel.resize (4);
  kernel.height = 2;
  kernel.width = 2;
  kernel (0, 0).intensity = 0; kernel (1, 0).intensity = 1;
  kernel (0, 1).intensity = -1; kernel (1, 1).intensity = 0;
}

template<typename PointT>
void
pcl::pcl_2d::kernel<PointT>::derivativeXCentralKernel (PointCloud<PointT> &kernel)
{
  kernel.resize (3);
  kernel.height = 1;
  kernel.width = 3;
  kernel (0, 0).intensity = -1; kernel (1, 0).intensity = 0; kernel (2, 0).intensity = 1;
}

template<typename PointT>
void
pcl::pcl_2d::kernel<PointT>::derivativeXForwardKernel (PointCloud<PointT> &kernel)
{
  kernel.resize (3);
  kernel.height = 1;
  kernel.width = 3;
  kernel (0, 0).intensity = 0; kernel (1, 0).intensity = -1; kernel (2, 0).intensity = 1;
}

template<typename PointT>
void
pcl::pcl_2d::kernel<PointT>::derivativeXBackwardKernel (PointCloud<PointT> &kernel)
{
  kernel.resize (3);
  kernel.height = 1;
  kernel.width = 3;
  kernel (0, 0).intensity = -1; kernel (1, 0).intensity = 1; kernel (2, 0).intensity = 0;
}

template<typename PointT>
void
pcl::pcl_2d::kernel<PointT>::derivativeYCentralKernel (PointCloud<PointT> &kernel)
{
  kernel.resize (3);
  kernel.height = 3;
  kernel.width = 1;
  kernel (0, 0).intensity = -1; kernel (0, 1).intensity = 0; kernel (0, 2).intensity = 1;
}


template<typename PointT>
void
pcl::pcl_2d::kernel<PointT>::derivativeYForwardKernel (PointCloud<PointT> &kernel)
{
  kernel.resize (3);
  kernel.height = 3;
  kernel.width = 1;
  kernel (0, 0).intensity = 0; kernel (0, 1).intensity = -1; kernel (0, 2).intensity = 1;
}

template<typename PointT>
void
pcl::pcl_2d::kernel<PointT>::derivativeYBackwardKernel (PointCloud<PointT> &kernel)
{
  kernel.resize (3);
  kernel.height = 3;
  kernel.width = 1;
  kernel (0, 0).intensity = -1; kernel (0, 1).intensity = 1; kernel (0, 2).intensity = 0;
}

template<typename PointT>
void
pcl::pcl_2d::kernel<PointT>::setKernelType (KERNEL_ENUM kernel_type)
{
  kernel_type_ = kernel_type;
}

template<typename PointT>
void
pcl::pcl_2d::kernel<PointT>::setKernelSize (int kernel_size)
{
  kernel_size_ = kernel_size;
}

template<typename PointT>
void
pcl::pcl_2d::kernel<PointT>::setKernelSigma (float kernel_sigma)
{
  sigma_ = kernel_sigma;
}


#endif
