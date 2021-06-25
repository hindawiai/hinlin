<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR MIT
/**************************************************************************
 *
 * Copyright 2013 VMware, Inc., Palo Alto, CA., USA
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modअगरy, merge, publish,
 * distribute, sub license, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to करो so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial portions
 * of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL
 * THE COPYRIGHT HOLDERS, AUTHORS AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
 * USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 **************************************************************************/
/*
 * Authors:
 *     Thomas Hellstrom <thellstrom@vmware.com>
 *
 */

#समावेश "vmwgfx_drv.h"
#समावेश "ttm_object.h"
#समावेश <linux/dma-buf.h>

/*
 * DMA-BUF attach- and mapping methods. No need to implement
 * these until we have other भव devices use them.
 */

अटल पूर्णांक vmw_prime_map_attach(काष्ठा dma_buf *dma_buf,
				काष्ठा dma_buf_attachment *attach)
अणु
	वापस -ENOSYS;
पूर्ण

अटल व्योम vmw_prime_map_detach(काष्ठा dma_buf *dma_buf,
				 काष्ठा dma_buf_attachment *attach)
अणु
पूर्ण

अटल काष्ठा sg_table *vmw_prime_map_dma_buf(काष्ठा dma_buf_attachment *attach,
					      क्रमागत dma_data_direction dir)
अणु
	वापस ERR_PTR(-ENOSYS);
पूर्ण

अटल व्योम vmw_prime_unmap_dma_buf(काष्ठा dma_buf_attachment *attach,
				    काष्ठा sg_table *sgb,
				    क्रमागत dma_data_direction dir)
अणु
पूर्ण

स्थिर काष्ठा dma_buf_ops vmw_prime_dmabuf_ops =  अणु
	.attach = vmw_prime_map_attach,
	.detach = vmw_prime_map_detach,
	.map_dma_buf = vmw_prime_map_dma_buf,
	.unmap_dma_buf = vmw_prime_unmap_dma_buf,
	.release = शून्य,
पूर्ण;

पूर्णांक vmw_prime_fd_to_handle(काष्ठा drm_device *dev,
			   काष्ठा drm_file *file_priv,
			   पूर्णांक fd, u32 *handle)
अणु
	काष्ठा tपंचांग_object_file *tfile = vmw_fpriv(file_priv)->tfile;

	वापस tपंचांग_prime_fd_to_handle(tfile, fd, handle);
पूर्ण

पूर्णांक vmw_prime_handle_to_fd(काष्ठा drm_device *dev,
			   काष्ठा drm_file *file_priv,
			   uपूर्णांक32_t handle, uपूर्णांक32_t flags,
			   पूर्णांक *prime_fd)
अणु
	काष्ठा tपंचांग_object_file *tfile = vmw_fpriv(file_priv)->tfile;

	वापस tपंचांग_prime_handle_to_fd(tfile, handle, flags, prime_fd);
पूर्ण
