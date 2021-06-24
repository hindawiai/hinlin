<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR MIT
/**************************************************************************
 *
 * Copyright 2009-2015 VMware, Inc., Palo Alto, CA., USA
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

#समावेश <drm/tपंचांग/tपंचांग_bo_driver.h>

#समावेश "vmwgfx_drv.h"

#घोषणा VMW_PPN_SIZE (माप(अचिन्हित दीर्घ))
/* A future safe maximum remap size. */
#घोषणा VMW_PPN_PER_REMAP ((31 * 1024) / VMW_PPN_SIZE)
#घोषणा DMA_ADDR_INVALID ((dma_addr_t) 0)
#घोषणा DMA_PAGE_INVALID 0UL

अटल पूर्णांक vmw_gmr2_bind(काष्ठा vmw_निजी *dev_priv,
			 काष्ठा vmw_piter *iter,
			 अचिन्हित दीर्घ num_pages,
			 पूर्णांक gmr_id)
अणु
	SVGAFअगरoCmdDefineGMR2 define_cmd;
	SVGAFअगरoCmdRemapGMR2 remap_cmd;
	uपूर्णांक32_t *cmd;
	uपूर्णांक32_t *cmd_orig;
	uपूर्णांक32_t define_size = माप(define_cmd) + माप(*cmd);
	uपूर्णांक32_t remap_num = num_pages / VMW_PPN_PER_REMAP + ((num_pages % VMW_PPN_PER_REMAP) > 0);
	uपूर्णांक32_t remap_size = VMW_PPN_SIZE * num_pages + (माप(remap_cmd) + माप(*cmd)) * remap_num;
	uपूर्णांक32_t remap_pos = 0;
	uपूर्णांक32_t cmd_size = define_size + remap_size;
	uपूर्णांक32_t i;

	cmd_orig = cmd = VMW_CMD_RESERVE(dev_priv, cmd_size);
	अगर (unlikely(cmd == शून्य))
		वापस -ENOMEM;

	define_cmd.gmrId = gmr_id;
	define_cmd.numPages = num_pages;

	*cmd++ = SVGA_CMD_DEFINE_GMR2;
	स_नकल(cmd, &define_cmd, माप(define_cmd));
	cmd += माप(define_cmd) / माप(*cmd);

	/*
	 * Need to split the command अगर there are too many
	 * pages that goes पूर्णांकo the gmr.
	 */

	remap_cmd.gmrId = gmr_id;
	remap_cmd.flags = (VMW_PPN_SIZE > माप(*cmd)) ?
		SVGA_REMAP_GMR2_PPN64 : SVGA_REMAP_GMR2_PPN32;

	जबतक (num_pages > 0) अणु
		अचिन्हित दीर्घ nr = min(num_pages, (अचिन्हित दीर्घ)VMW_PPN_PER_REMAP);

		remap_cmd.offsetPages = remap_pos;
		remap_cmd.numPages = nr;

		*cmd++ = SVGA_CMD_REMAP_GMR2;
		स_नकल(cmd, &remap_cmd, माप(remap_cmd));
		cmd += माप(remap_cmd) / माप(*cmd);

		क्रम (i = 0; i < nr; ++i) अणु
			अगर (VMW_PPN_SIZE <= 4)
				*cmd = vmw_piter_dma_addr(iter) >> PAGE_SHIFT;
			अन्यथा
				*((uपूर्णांक64_t *)cmd) = vmw_piter_dma_addr(iter) >>
					PAGE_SHIFT;

			cmd += VMW_PPN_SIZE / माप(*cmd);
			vmw_piter_next(iter);
		पूर्ण

		num_pages -= nr;
		remap_pos += nr;
	पूर्ण

	BUG_ON(cmd != cmd_orig + cmd_size / माप(*cmd));

	vmw_cmd_commit(dev_priv, cmd_size);

	वापस 0;
पूर्ण

अटल व्योम vmw_gmr2_unbind(काष्ठा vmw_निजी *dev_priv,
			    पूर्णांक gmr_id)
अणु
	SVGAFअगरoCmdDefineGMR2 define_cmd;
	uपूर्णांक32_t define_size = माप(define_cmd) + 4;
	uपूर्णांक32_t *cmd;

	cmd = VMW_CMD_RESERVE(dev_priv, define_size);
	अगर (unlikely(cmd == शून्य))
		वापस;

	define_cmd.gmrId = gmr_id;
	define_cmd.numPages = 0;

	*cmd++ = SVGA_CMD_DEFINE_GMR2;
	स_नकल(cmd, &define_cmd, माप(define_cmd));

	vmw_cmd_commit(dev_priv, define_size);
पूर्ण


पूर्णांक vmw_gmr_bind(काष्ठा vmw_निजी *dev_priv,
		 स्थिर काष्ठा vmw_sg_table *vsgt,
		 अचिन्हित दीर्घ num_pages,
		 पूर्णांक gmr_id)
अणु
	काष्ठा vmw_piter data_iter;

	vmw_piter_start(&data_iter, vsgt, 0);

	अगर (unlikely(!vmw_piter_next(&data_iter)))
		वापस 0;

	अगर (unlikely(!(dev_priv->capabilities & SVGA_CAP_GMR2)))
		वापस -EINVAL;

	वापस vmw_gmr2_bind(dev_priv, &data_iter, num_pages, gmr_id);
पूर्ण


व्योम vmw_gmr_unbind(काष्ठा vmw_निजी *dev_priv, पूर्णांक gmr_id)
अणु
	अगर (likely(dev_priv->capabilities & SVGA_CAP_GMR2))
		vmw_gmr2_unbind(dev_priv, gmr_id);
पूर्ण
