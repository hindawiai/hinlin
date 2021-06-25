<शैली गुरु>
/* savage_state.c -- State and drawing support क्रम Savage
 *
 * Copyright 2004  Felix Kuehling
 * All Rights Reserved.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sub license,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial portions
 * of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NON-INFRINGEMENT. IN NO EVENT SHALL FELIX KUEHLING BE LIABLE FOR
 * ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
 * CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>

#समावेश <drm/drm_device.h>
#समावेश <drm/drm_file.h>
#समावेश <drm/drm_prपूर्णांक.h>
#समावेश <drm/savage_drm.h>

#समावेश "savage_drv.h"

व्योम savage_emit_clip_rect_s3d(drm_savage_निजी_t * dev_priv,
			       स्थिर काष्ठा drm_clip_rect * pbox)
अणु
	uपूर्णांक32_t scstart = dev_priv->state.s3d.new_scstart;
	uपूर्णांक32_t scend = dev_priv->state.s3d.new_scend;
	scstart = (scstart & ~SAVAGE_SCISSOR_MASK_S3D) |
	    ((uपूर्णांक32_t) pbox->x1 & 0x000007ff) |
	    (((uपूर्णांक32_t) pbox->y1 << 16) & 0x07ff0000);
	scend = (scend & ~SAVAGE_SCISSOR_MASK_S3D) |
	    (((uपूर्णांक32_t) pbox->x2 - 1) & 0x000007ff) |
	    ((((uपूर्णांक32_t) pbox->y2 - 1) << 16) & 0x07ff0000);
	अगर (scstart != dev_priv->state.s3d.scstart ||
	    scend != dev_priv->state.s3d.scend) अणु
		DMA_LOCALS;
		BEGIN_DMA(4);
		DMA_WRITE(BCI_CMD_WAIT | BCI_CMD_WAIT_3D);
		DMA_SET_REGISTERS(SAVAGE_SCSTART_S3D, 2);
		DMA_WRITE(scstart);
		DMA_WRITE(scend);
		dev_priv->state.s3d.scstart = scstart;
		dev_priv->state.s3d.scend = scend;
		dev_priv->रुकोing = 1;
		DMA_COMMIT();
	पूर्ण
पूर्ण

व्योम savage_emit_clip_rect_s4(drm_savage_निजी_t * dev_priv,
			      स्थिर काष्ठा drm_clip_rect * pbox)
अणु
	uपूर्णांक32_t drawctrl0 = dev_priv->state.s4.new_drawctrl0;
	uपूर्णांक32_t drawctrl1 = dev_priv->state.s4.new_drawctrl1;
	drawctrl0 = (drawctrl0 & ~SAVAGE_SCISSOR_MASK_S4) |
	    ((uपूर्णांक32_t) pbox->x1 & 0x000007ff) |
	    (((uपूर्णांक32_t) pbox->y1 << 12) & 0x00fff000);
	drawctrl1 = (drawctrl1 & ~SAVAGE_SCISSOR_MASK_S4) |
	    (((uपूर्णांक32_t) pbox->x2 - 1) & 0x000007ff) |
	    ((((uपूर्णांक32_t) pbox->y2 - 1) << 12) & 0x00fff000);
	अगर (drawctrl0 != dev_priv->state.s4.drawctrl0 ||
	    drawctrl1 != dev_priv->state.s4.drawctrl1) अणु
		DMA_LOCALS;
		BEGIN_DMA(4);
		DMA_WRITE(BCI_CMD_WAIT | BCI_CMD_WAIT_3D);
		DMA_SET_REGISTERS(SAVAGE_DRAWCTRL0_S4, 2);
		DMA_WRITE(drawctrl0);
		DMA_WRITE(drawctrl1);
		dev_priv->state.s4.drawctrl0 = drawctrl0;
		dev_priv->state.s4.drawctrl1 = drawctrl1;
		dev_priv->रुकोing = 1;
		DMA_COMMIT();
	पूर्ण
पूर्ण

अटल पूर्णांक savage_verअगरy_texaddr(drm_savage_निजी_t * dev_priv, पूर्णांक unit,
				 uपूर्णांक32_t addr)
अणु
	अगर ((addr & 6) != 2) अणु	/* reserved bits */
		DRM_ERROR("bad texAddr%d %08x (reserved bits)\n", unit, addr);
		वापस -EINVAL;
	पूर्ण
	अगर (!(addr & 1)) अणु	/* local */
		addr &= ~7;
		अगर (addr < dev_priv->texture_offset ||
		    addr >= dev_priv->texture_offset + dev_priv->texture_size) अणु
			DRM_ERROR
			    ("bad texAddr%d %08x (local addr out of range)\n",
			     unit, addr);
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु		/* AGP */
		अगर (!dev_priv->agp_textures) अणु
			DRM_ERROR("bad texAddr%d %08x (AGP not available)\n",
				  unit, addr);
			वापस -EINVAL;
		पूर्ण
		addr &= ~7;
		अगर (addr < dev_priv->agp_textures->offset ||
		    addr >= (dev_priv->agp_textures->offset +
			     dev_priv->agp_textures->size)) अणु
			DRM_ERROR
			    ("bad texAddr%d %08x (AGP addr out of range)\n",
			     unit, addr);
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

#घोषणा SAVE_STATE(reg,where)			\
	अगर(start <= reg && start+count > reg)	\
		dev_priv->state.where = regs[reg - start]
#घोषणा SAVE_STATE_MASK(reg,where,mask) करो अणु			\
	अगर(start <= reg && start+count > reg) अणु			\
		uपूर्णांक32_t पंचांगp;					\
		पंचांगp = regs[reg - start];			\
		dev_priv->state.where = (पंचांगp & (mask)) |	\
			(dev_priv->state.where & ~(mask));	\
	पूर्ण							\
पूर्ण जबतक (0)

अटल पूर्णांक savage_verअगरy_state_s3d(drm_savage_निजी_t * dev_priv,
				   अचिन्हित पूर्णांक start, अचिन्हित पूर्णांक count,
				   स्थिर uपूर्णांक32_t *regs)
अणु
	अगर (start < SAVAGE_TEXPALADDR_S3D ||
	    start + count - 1 > SAVAGE_DESTTEXRWWATERMARK_S3D) अणु
		DRM_ERROR("invalid register range (0x%04x-0x%04x)\n",
			  start, start + count - 1);
		वापस -EINVAL;
	पूर्ण

	SAVE_STATE_MASK(SAVAGE_SCSTART_S3D, s3d.new_scstart,
			~SAVAGE_SCISSOR_MASK_S3D);
	SAVE_STATE_MASK(SAVAGE_SCEND_S3D, s3d.new_scend,
			~SAVAGE_SCISSOR_MASK_S3D);

	/* अगर any texture regs were changed ... */
	अगर (start <= SAVAGE_TEXCTRL_S3D &&
	    start + count > SAVAGE_TEXPALADDR_S3D) अणु
		/* ... check texture state */
		SAVE_STATE(SAVAGE_TEXCTRL_S3D, s3d.texctrl);
		SAVE_STATE(SAVAGE_TEXADDR_S3D, s3d.texaddr);
		अगर (dev_priv->state.s3d.texctrl & SAVAGE_TEXCTRL_TEXEN_MASK)
			वापस savage_verअगरy_texaddr(dev_priv, 0,
						dev_priv->state.s3d.texaddr);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक savage_verअगरy_state_s4(drm_savage_निजी_t * dev_priv,
				  अचिन्हित पूर्णांक start, अचिन्हित पूर्णांक count,
				  स्थिर uपूर्णांक32_t *regs)
अणु
	पूर्णांक ret = 0;

	अगर (start < SAVAGE_DRAWLOCALCTRL_S4 ||
	    start + count - 1 > SAVAGE_TEXBLENDCOLOR_S4) अणु
		DRM_ERROR("invalid register range (0x%04x-0x%04x)\n",
			  start, start + count - 1);
		वापस -EINVAL;
	पूर्ण

	SAVE_STATE_MASK(SAVAGE_DRAWCTRL0_S4, s4.new_drawctrl0,
			~SAVAGE_SCISSOR_MASK_S4);
	SAVE_STATE_MASK(SAVAGE_DRAWCTRL1_S4, s4.new_drawctrl1,
			~SAVAGE_SCISSOR_MASK_S4);

	/* अगर any texture regs were changed ... */
	अगर (start <= SAVAGE_TEXDESCR_S4 &&
	    start + count > SAVAGE_TEXPALADDR_S4) अणु
		/* ... check texture state */
		SAVE_STATE(SAVAGE_TEXDESCR_S4, s4.texdescr);
		SAVE_STATE(SAVAGE_TEXADDR0_S4, s4.texaddr0);
		SAVE_STATE(SAVAGE_TEXADDR1_S4, s4.texaddr1);
		अगर (dev_priv->state.s4.texdescr & SAVAGE_TEXDESCR_TEX0EN_MASK)
			ret |= savage_verअगरy_texaddr(dev_priv, 0,
						dev_priv->state.s4.texaddr0);
		अगर (dev_priv->state.s4.texdescr & SAVAGE_TEXDESCR_TEX1EN_MASK)
			ret |= savage_verअगरy_texaddr(dev_priv, 1,
						dev_priv->state.s4.texaddr1);
	पूर्ण

	वापस ret;
पूर्ण

#अघोषित SAVE_STATE
#अघोषित SAVE_STATE_MASK

अटल पूर्णांक savage_dispatch_state(drm_savage_निजी_t * dev_priv,
				 स्थिर drm_savage_cmd_header_t * cmd_header,
				 स्थिर uपूर्णांक32_t *regs)
अणु
	अचिन्हित पूर्णांक count = cmd_header->state.count;
	अचिन्हित पूर्णांक start = cmd_header->state.start;
	अचिन्हित पूर्णांक count2 = 0;
	अचिन्हित पूर्णांक bci_size;
	पूर्णांक ret;
	DMA_LOCALS;

	अगर (!count)
		वापस 0;

	अगर (S3_SAVAGE3D_SERIES(dev_priv->chipset)) अणु
		ret = savage_verअगरy_state_s3d(dev_priv, start, count, regs);
		अगर (ret != 0)
			वापस ret;
		/* scissor regs are emitted in savage_dispatch_draw */
		अगर (start < SAVAGE_SCSTART_S3D) अणु
			अगर (start + count > SAVAGE_SCEND_S3D + 1)
				count2 = count - (SAVAGE_SCEND_S3D + 1 - start);
			अगर (start + count > SAVAGE_SCSTART_S3D)
				count = SAVAGE_SCSTART_S3D - start;
		पूर्ण अन्यथा अगर (start <= SAVAGE_SCEND_S3D) अणु
			अगर (start + count > SAVAGE_SCEND_S3D + 1) अणु
				count -= SAVAGE_SCEND_S3D + 1 - start;
				start = SAVAGE_SCEND_S3D + 1;
			पूर्ण अन्यथा
				वापस 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		ret = savage_verअगरy_state_s4(dev_priv, start, count, regs);
		अगर (ret != 0)
			वापस ret;
		/* scissor regs are emitted in savage_dispatch_draw */
		अगर (start < SAVAGE_DRAWCTRL0_S4) अणु
			अगर (start + count > SAVAGE_DRAWCTRL1_S4 + 1)
				count2 = count -
					 (SAVAGE_DRAWCTRL1_S4 + 1 - start);
			अगर (start + count > SAVAGE_DRAWCTRL0_S4)
				count = SAVAGE_DRAWCTRL0_S4 - start;
		पूर्ण अन्यथा अगर (start <= SAVAGE_DRAWCTRL1_S4) अणु
			अगर (start + count > SAVAGE_DRAWCTRL1_S4 + 1) अणु
				count -= SAVAGE_DRAWCTRL1_S4 + 1 - start;
				start = SAVAGE_DRAWCTRL1_S4 + 1;
			पूर्ण अन्यथा
				वापस 0;
		पूर्ण
	पूर्ण

	bci_size = count + (count + 254) / 255 + count2 + (count2 + 254) / 255;

	अगर (cmd_header->state.global) अणु
		BEGIN_DMA(bci_size + 1);
		DMA_WRITE(BCI_CMD_WAIT | BCI_CMD_WAIT_3D);
		dev_priv->रुकोing = 1;
	पूर्ण अन्यथा अणु
		BEGIN_DMA(bci_size);
	पूर्ण

	करो अणु
		जबतक (count > 0) अणु
			अचिन्हित पूर्णांक n = count < 255 ? count : 255;
			DMA_SET_REGISTERS(start, n);
			DMA_COPY(regs, n);
			count -= n;
			start += n;
			regs += n;
		पूर्ण
		start += 2;
		regs += 2;
		count = count2;
		count2 = 0;
	पूर्ण जबतक (count);

	DMA_COMMIT();

	वापस 0;
पूर्ण

अटल पूर्णांक savage_dispatch_dma_prim(drm_savage_निजी_t * dev_priv,
				    स्थिर drm_savage_cmd_header_t * cmd_header,
				    स्थिर काष्ठा drm_buf * dmabuf)
अणु
	अचिन्हित अक्षर reorder = 0;
	अचिन्हित पूर्णांक prim = cmd_header->prim.prim;
	अचिन्हित पूर्णांक skip = cmd_header->prim.skip;
	अचिन्हित पूर्णांक n = cmd_header->prim.count;
	अचिन्हित पूर्णांक start = cmd_header->prim.start;
	अचिन्हित पूर्णांक i;
	BCI_LOCALS;

	अगर (!dmabuf) अणु
		DRM_ERROR("called without dma buffers!\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!n)
		वापस 0;

	चयन (prim) अणु
	हाल SAVAGE_PRIM_TRILIST_201:
		reorder = 1;
		prim = SAVAGE_PRIM_TRILIST;
		fallthrough;
	हाल SAVAGE_PRIM_TRILIST:
		अगर (n % 3 != 0) अणु
			DRM_ERROR("wrong number of vertices %u in TRILIST\n",
				  n);
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल SAVAGE_PRIM_TRISTRIP:
	हाल SAVAGE_PRIM_TRIFAN:
		अगर (n < 3) अणु
			DRM_ERROR
			    ("wrong number of vertices %u in TRIFAN/STRIP\n",
			     n);
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	शेष:
		DRM_ERROR("invalid primitive type %u\n", prim);
		वापस -EINVAL;
	पूर्ण

	अगर (S3_SAVAGE3D_SERIES(dev_priv->chipset)) अणु
		अगर (skip != 0) अणु
			DRM_ERROR("invalid skip flags 0x%04x for DMA\n", skip);
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		अचिन्हित पूर्णांक size = 10 - (skip & 1) - (skip >> 1 & 1) -
		    (skip >> 2 & 1) - (skip >> 3 & 1) - (skip >> 4 & 1) -
		    (skip >> 5 & 1) - (skip >> 6 & 1) - (skip >> 7 & 1);
		अगर (skip > SAVAGE_SKIP_ALL_S4 || size != 8) अणु
			DRM_ERROR("invalid skip flags 0x%04x for DMA\n", skip);
			वापस -EINVAL;
		पूर्ण
		अगर (reorder) अणु
			DRM_ERROR("TRILIST_201 used on Savage4 hardware\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (start + n > dmabuf->total / 32) अणु
		DRM_ERROR("vertex indices (%u-%u) out of range (0-%u)\n",
			  start, start + n - 1, dmabuf->total / 32);
		वापस -EINVAL;
	पूर्ण

	/* Vertex DMA करोesn't work with command DMA at the same समय,
	 * so we use BCI_... to submit commands here. Flush buffered
	 * faked DMA first. */
	DMA_FLUSH();

	अगर (dmabuf->bus_address != dev_priv->state.common.vbaddr) अणु
		BEGIN_BCI(2);
		BCI_SET_REGISTERS(SAVAGE_VERTBUFADDR, 1);
		BCI_WRITE(dmabuf->bus_address | dev_priv->dma_type);
		dev_priv->state.common.vbaddr = dmabuf->bus_address;
	पूर्ण
	अगर (S3_SAVAGE3D_SERIES(dev_priv->chipset) && dev_priv->रुकोing) अणु
		/* Workaround क्रम what looks like a hardware bug. If a
		 * WAIT_3D_IDLE was emitted some समय beक्रमe the
		 * indexed drawing command then the engine will lock
		 * up. There are two known workarounds:
		 * WAIT_IDLE_EMPTY or emit at least 63 NOPs. */
		BEGIN_BCI(63);
		क्रम (i = 0; i < 63; ++i)
			BCI_WRITE(BCI_CMD_WAIT);
		dev_priv->रुकोing = 0;
	पूर्ण

	prim <<= 25;
	जबतक (n != 0) अणु
		/* Can emit up to 255 indices (85 triangles) at once. */
		अचिन्हित पूर्णांक count = n > 255 ? 255 : n;
		अगर (reorder) अणु
			/* Need to reorder indices क्रम correct flat
			 * shading जबतक preserving the घड़ी sense
			 * क्रम correct culling. Only on Savage3D. */
			पूर्णांक reorder[3] = अणु -1, -1, -1 पूर्ण;
			reorder[start % 3] = 2;

			BEGIN_BCI((count + 1 + 1) / 2);
			BCI_DRAW_INDICES_S3D(count, prim, start + 2);

			क्रम (i = start + 1; i + 1 < start + count; i += 2)
				BCI_WRITE((i + reorder[i % 3]) |
					  ((i + 1 +
					    reorder[(i + 1) % 3]) << 16));
			अगर (i < start + count)
				BCI_WRITE(i + reorder[i % 3]);
		पूर्ण अन्यथा अगर (S3_SAVAGE3D_SERIES(dev_priv->chipset)) अणु
			BEGIN_BCI((count + 1 + 1) / 2);
			BCI_DRAW_INDICES_S3D(count, prim, start);

			क्रम (i = start + 1; i + 1 < start + count; i += 2)
				BCI_WRITE(i | ((i + 1) << 16));
			अगर (i < start + count)
				BCI_WRITE(i);
		पूर्ण अन्यथा अणु
			BEGIN_BCI((count + 2 + 1) / 2);
			BCI_DRAW_INDICES_S4(count, prim, skip);

			क्रम (i = start; i + 1 < start + count; i += 2)
				BCI_WRITE(i | ((i + 1) << 16));
			अगर (i < start + count)
				BCI_WRITE(i);
		पूर्ण

		start += count;
		n -= count;

		prim |= BCI_CMD_DRAW_CONT;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक savage_dispatch_vb_prim(drm_savage_निजी_t * dev_priv,
				   स्थिर drm_savage_cmd_header_t * cmd_header,
				   स्थिर uपूर्णांक32_t *vtxbuf, अचिन्हित पूर्णांक vb_size,
				   अचिन्हित पूर्णांक vb_stride)
अणु
	अचिन्हित अक्षर reorder = 0;
	अचिन्हित पूर्णांक prim = cmd_header->prim.prim;
	अचिन्हित पूर्णांक skip = cmd_header->prim.skip;
	अचिन्हित पूर्णांक n = cmd_header->prim.count;
	अचिन्हित पूर्णांक start = cmd_header->prim.start;
	अचिन्हित पूर्णांक vtx_size;
	अचिन्हित पूर्णांक i;
	DMA_LOCALS;

	अगर (!n)
		वापस 0;

	चयन (prim) अणु
	हाल SAVAGE_PRIM_TRILIST_201:
		reorder = 1;
		prim = SAVAGE_PRIM_TRILIST;
		fallthrough;
	हाल SAVAGE_PRIM_TRILIST:
		अगर (n % 3 != 0) अणु
			DRM_ERROR("wrong number of vertices %u in TRILIST\n",
				  n);
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल SAVAGE_PRIM_TRISTRIP:
	हाल SAVAGE_PRIM_TRIFAN:
		अगर (n < 3) अणु
			DRM_ERROR
			    ("wrong number of vertices %u in TRIFAN/STRIP\n",
			     n);
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	शेष:
		DRM_ERROR("invalid primitive type %u\n", prim);
		वापस -EINVAL;
	पूर्ण

	अगर (S3_SAVAGE3D_SERIES(dev_priv->chipset)) अणु
		अगर (skip > SAVAGE_SKIP_ALL_S3D) अणु
			DRM_ERROR("invalid skip flags 0x%04x\n", skip);
			वापस -EINVAL;
		पूर्ण
		vtx_size = 8;	/* full vertex */
	पूर्ण अन्यथा अणु
		अगर (skip > SAVAGE_SKIP_ALL_S4) अणु
			DRM_ERROR("invalid skip flags 0x%04x\n", skip);
			वापस -EINVAL;
		पूर्ण
		vtx_size = 10;	/* full vertex */
	पूर्ण

	vtx_size -= (skip & 1) + (skip >> 1 & 1) +
	    (skip >> 2 & 1) + (skip >> 3 & 1) + (skip >> 4 & 1) +
	    (skip >> 5 & 1) + (skip >> 6 & 1) + (skip >> 7 & 1);

	अगर (vtx_size > vb_stride) अणु
		DRM_ERROR("vertex size greater than vb stride (%u > %u)\n",
			  vtx_size, vb_stride);
		वापस -EINVAL;
	पूर्ण

	अगर (start + n > vb_size / (vb_stride * 4)) अणु
		DRM_ERROR("vertex indices (%u-%u) out of range (0-%u)\n",
			  start, start + n - 1, vb_size / (vb_stride * 4));
		वापस -EINVAL;
	पूर्ण

	prim <<= 25;
	जबतक (n != 0) अणु
		/* Can emit up to 255 vertices (85 triangles) at once. */
		अचिन्हित पूर्णांक count = n > 255 ? 255 : n;
		अगर (reorder) अणु
			/* Need to reorder vertices क्रम correct flat
			 * shading जबतक preserving the घड़ी sense
			 * क्रम correct culling. Only on Savage3D. */
			पूर्णांक reorder[3] = अणु -1, -1, -1 पूर्ण;
			reorder[start % 3] = 2;

			BEGIN_DMA(count * vtx_size + 1);
			DMA_DRAW_PRIMITIVE(count, prim, skip);

			क्रम (i = start; i < start + count; ++i) अणु
				अचिन्हित पूर्णांक j = i + reorder[i % 3];
				DMA_COPY(&vtxbuf[vb_stride * j], vtx_size);
			पूर्ण

			DMA_COMMIT();
		पूर्ण अन्यथा अणु
			BEGIN_DMA(count * vtx_size + 1);
			DMA_DRAW_PRIMITIVE(count, prim, skip);

			अगर (vb_stride == vtx_size) अणु
				DMA_COPY(&vtxbuf[vb_stride * start],
					 vtx_size * count);
			पूर्ण अन्यथा अणु
				क्रम (i = start; i < start + count; ++i) अणु
					DMA_COPY(&vtxbuf [vb_stride * i],
						 vtx_size);
				पूर्ण
			पूर्ण

			DMA_COMMIT();
		पूर्ण

		start += count;
		n -= count;

		prim |= BCI_CMD_DRAW_CONT;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक savage_dispatch_dma_idx(drm_savage_निजी_t * dev_priv,
				   स्थिर drm_savage_cmd_header_t * cmd_header,
				   स्थिर uपूर्णांक16_t *idx,
				   स्थिर काष्ठा drm_buf * dmabuf)
अणु
	अचिन्हित अक्षर reorder = 0;
	अचिन्हित पूर्णांक prim = cmd_header->idx.prim;
	अचिन्हित पूर्णांक skip = cmd_header->idx.skip;
	अचिन्हित पूर्णांक n = cmd_header->idx.count;
	अचिन्हित पूर्णांक i;
	BCI_LOCALS;

	अगर (!dmabuf) अणु
		DRM_ERROR("called without dma buffers!\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!n)
		वापस 0;

	चयन (prim) अणु
	हाल SAVAGE_PRIM_TRILIST_201:
		reorder = 1;
		prim = SAVAGE_PRIM_TRILIST;
		fallthrough;
	हाल SAVAGE_PRIM_TRILIST:
		अगर (n % 3 != 0) अणु
			DRM_ERROR("wrong number of indices %u in TRILIST\n", n);
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल SAVAGE_PRIM_TRISTRIP:
	हाल SAVAGE_PRIM_TRIFAN:
		अगर (n < 3) अणु
			DRM_ERROR
			    ("wrong number of indices %u in TRIFAN/STRIP\n", n);
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	शेष:
		DRM_ERROR("invalid primitive type %u\n", prim);
		वापस -EINVAL;
	पूर्ण

	अगर (S3_SAVAGE3D_SERIES(dev_priv->chipset)) अणु
		अगर (skip != 0) अणु
			DRM_ERROR("invalid skip flags 0x%04x for DMA\n", skip);
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		अचिन्हित पूर्णांक size = 10 - (skip & 1) - (skip >> 1 & 1) -
		    (skip >> 2 & 1) - (skip >> 3 & 1) - (skip >> 4 & 1) -
		    (skip >> 5 & 1) - (skip >> 6 & 1) - (skip >> 7 & 1);
		अगर (skip > SAVAGE_SKIP_ALL_S4 || size != 8) अणु
			DRM_ERROR("invalid skip flags 0x%04x for DMA\n", skip);
			वापस -EINVAL;
		पूर्ण
		अगर (reorder) अणु
			DRM_ERROR("TRILIST_201 used on Savage4 hardware\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	/* Vertex DMA करोesn't work with command DMA at the same समय,
	 * so we use BCI_... to submit commands here. Flush buffered
	 * faked DMA first. */
	DMA_FLUSH();

	अगर (dmabuf->bus_address != dev_priv->state.common.vbaddr) अणु
		BEGIN_BCI(2);
		BCI_SET_REGISTERS(SAVAGE_VERTBUFADDR, 1);
		BCI_WRITE(dmabuf->bus_address | dev_priv->dma_type);
		dev_priv->state.common.vbaddr = dmabuf->bus_address;
	पूर्ण
	अगर (S3_SAVAGE3D_SERIES(dev_priv->chipset) && dev_priv->रुकोing) अणु
		/* Workaround क्रम what looks like a hardware bug. If a
		 * WAIT_3D_IDLE was emitted some समय beक्रमe the
		 * indexed drawing command then the engine will lock
		 * up. There are two known workarounds:
		 * WAIT_IDLE_EMPTY or emit at least 63 NOPs. */
		BEGIN_BCI(63);
		क्रम (i = 0; i < 63; ++i)
			BCI_WRITE(BCI_CMD_WAIT);
		dev_priv->रुकोing = 0;
	पूर्ण

	prim <<= 25;
	जबतक (n != 0) अणु
		/* Can emit up to 255 indices (85 triangles) at once. */
		अचिन्हित पूर्णांक count = n > 255 ? 255 : n;

		/* check indices */
		क्रम (i = 0; i < count; ++i) अणु
			अगर (idx[i] > dmabuf->total / 32) अणु
				DRM_ERROR("idx[%u]=%u out of range (0-%u)\n",
					  i, idx[i], dmabuf->total / 32);
				वापस -EINVAL;
			पूर्ण
		पूर्ण

		अगर (reorder) अणु
			/* Need to reorder indices क्रम correct flat
			 * shading जबतक preserving the घड़ी sense
			 * क्रम correct culling. Only on Savage3D. */
			पूर्णांक reorder[3] = अणु 2, -1, -1 पूर्ण;

			BEGIN_BCI((count + 1 + 1) / 2);
			BCI_DRAW_INDICES_S3D(count, prim, idx[2]);

			क्रम (i = 1; i + 1 < count; i += 2)
				BCI_WRITE(idx[i + reorder[i % 3]] |
					  (idx[i + 1 +
					   reorder[(i + 1) % 3]] << 16));
			अगर (i < count)
				BCI_WRITE(idx[i + reorder[i % 3]]);
		पूर्ण अन्यथा अगर (S3_SAVAGE3D_SERIES(dev_priv->chipset)) अणु
			BEGIN_BCI((count + 1 + 1) / 2);
			BCI_DRAW_INDICES_S3D(count, prim, idx[0]);

			क्रम (i = 1; i + 1 < count; i += 2)
				BCI_WRITE(idx[i] | (idx[i + 1] << 16));
			अगर (i < count)
				BCI_WRITE(idx[i]);
		पूर्ण अन्यथा अणु
			BEGIN_BCI((count + 2 + 1) / 2);
			BCI_DRAW_INDICES_S4(count, prim, skip);

			क्रम (i = 0; i + 1 < count; i += 2)
				BCI_WRITE(idx[i] | (idx[i + 1] << 16));
			अगर (i < count)
				BCI_WRITE(idx[i]);
		पूर्ण

		idx += count;
		n -= count;

		prim |= BCI_CMD_DRAW_CONT;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक savage_dispatch_vb_idx(drm_savage_निजी_t * dev_priv,
				  स्थिर drm_savage_cmd_header_t * cmd_header,
				  स्थिर uपूर्णांक16_t *idx,
				  स्थिर uपूर्णांक32_t *vtxbuf,
				  अचिन्हित पूर्णांक vb_size, अचिन्हित पूर्णांक vb_stride)
अणु
	अचिन्हित अक्षर reorder = 0;
	अचिन्हित पूर्णांक prim = cmd_header->idx.prim;
	अचिन्हित पूर्णांक skip = cmd_header->idx.skip;
	अचिन्हित पूर्णांक n = cmd_header->idx.count;
	अचिन्हित पूर्णांक vtx_size;
	अचिन्हित पूर्णांक i;
	DMA_LOCALS;

	अगर (!n)
		वापस 0;

	चयन (prim) अणु
	हाल SAVAGE_PRIM_TRILIST_201:
		reorder = 1;
		prim = SAVAGE_PRIM_TRILIST;
		fallthrough;
	हाल SAVAGE_PRIM_TRILIST:
		अगर (n % 3 != 0) अणु
			DRM_ERROR("wrong number of indices %u in TRILIST\n", n);
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल SAVAGE_PRIM_TRISTRIP:
	हाल SAVAGE_PRIM_TRIFAN:
		अगर (n < 3) अणु
			DRM_ERROR
			    ("wrong number of indices %u in TRIFAN/STRIP\n", n);
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	शेष:
		DRM_ERROR("invalid primitive type %u\n", prim);
		वापस -EINVAL;
	पूर्ण

	अगर (S3_SAVAGE3D_SERIES(dev_priv->chipset)) अणु
		अगर (skip > SAVAGE_SKIP_ALL_S3D) अणु
			DRM_ERROR("invalid skip flags 0x%04x\n", skip);
			वापस -EINVAL;
		पूर्ण
		vtx_size = 8;	/* full vertex */
	पूर्ण अन्यथा अणु
		अगर (skip > SAVAGE_SKIP_ALL_S4) अणु
			DRM_ERROR("invalid skip flags 0x%04x\n", skip);
			वापस -EINVAL;
		पूर्ण
		vtx_size = 10;	/* full vertex */
	पूर्ण

	vtx_size -= (skip & 1) + (skip >> 1 & 1) +
	    (skip >> 2 & 1) + (skip >> 3 & 1) + (skip >> 4 & 1) +
	    (skip >> 5 & 1) + (skip >> 6 & 1) + (skip >> 7 & 1);

	अगर (vtx_size > vb_stride) अणु
		DRM_ERROR("vertex size greater than vb stride (%u > %u)\n",
			  vtx_size, vb_stride);
		वापस -EINVAL;
	पूर्ण

	prim <<= 25;
	जबतक (n != 0) अणु
		/* Can emit up to 255 vertices (85 triangles) at once. */
		अचिन्हित पूर्णांक count = n > 255 ? 255 : n;

		/* Check indices */
		क्रम (i = 0; i < count; ++i) अणु
			अगर (idx[i] > vb_size / (vb_stride * 4)) अणु
				DRM_ERROR("idx[%u]=%u out of range (0-%u)\n",
					  i, idx[i], vb_size / (vb_stride * 4));
				वापस -EINVAL;
			पूर्ण
		पूर्ण

		अगर (reorder) अणु
			/* Need to reorder vertices क्रम correct flat
			 * shading जबतक preserving the घड़ी sense
			 * क्रम correct culling. Only on Savage3D. */
			पूर्णांक reorder[3] = अणु 2, -1, -1 पूर्ण;

			BEGIN_DMA(count * vtx_size + 1);
			DMA_DRAW_PRIMITIVE(count, prim, skip);

			क्रम (i = 0; i < count; ++i) अणु
				अचिन्हित पूर्णांक j = idx[i + reorder[i % 3]];
				DMA_COPY(&vtxbuf[vb_stride * j], vtx_size);
			पूर्ण

			DMA_COMMIT();
		पूर्ण अन्यथा अणु
			BEGIN_DMA(count * vtx_size + 1);
			DMA_DRAW_PRIMITIVE(count, prim, skip);

			क्रम (i = 0; i < count; ++i) अणु
				अचिन्हित पूर्णांक j = idx[i];
				DMA_COPY(&vtxbuf[vb_stride * j], vtx_size);
			पूर्ण

			DMA_COMMIT();
		पूर्ण

		idx += count;
		n -= count;

		prim |= BCI_CMD_DRAW_CONT;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक savage_dispatch_clear(drm_savage_निजी_t * dev_priv,
				 स्थिर drm_savage_cmd_header_t * cmd_header,
				 स्थिर drm_savage_cmd_header_t *data,
				 अचिन्हित पूर्णांक nbox,
				 स्थिर काष्ठा drm_clip_rect *boxes)
अणु
	अचिन्हित पूर्णांक flags = cmd_header->clear0.flags;
	अचिन्हित पूर्णांक clear_cmd;
	अचिन्हित पूर्णांक i, nbufs;
	DMA_LOCALS;

	अगर (nbox == 0)
		वापस 0;

	clear_cmd = BCI_CMD_RECT | BCI_CMD_RECT_XP | BCI_CMD_RECT_YP |
	    BCI_CMD_SEND_COLOR | BCI_CMD_DEST_PBD_NEW;
	BCI_CMD_SET_ROP(clear_cmd, 0xCC);

	nbufs = ((flags & SAVAGE_FRONT) ? 1 : 0) +
	    ((flags & SAVAGE_BACK) ? 1 : 0) + ((flags & SAVAGE_DEPTH) ? 1 : 0);
	अगर (nbufs == 0)
		वापस 0;

	अगर (data->clear1.mask != 0xffffffff) अणु
		/* set mask */
		BEGIN_DMA(2);
		DMA_SET_REGISTERS(SAVAGE_BITPLANEWTMASK, 1);
		DMA_WRITE(data->clear1.mask);
		DMA_COMMIT();
	पूर्ण
	क्रम (i = 0; i < nbox; ++i) अणु
		अचिन्हित पूर्णांक x, y, w, h;
		अचिन्हित पूर्णांक buf;
		x = boxes[i].x1, y = boxes[i].y1;
		w = boxes[i].x2 - boxes[i].x1;
		h = boxes[i].y2 - boxes[i].y1;
		BEGIN_DMA(nbufs * 6);
		क्रम (buf = SAVAGE_FRONT; buf <= SAVAGE_DEPTH; buf <<= 1) अणु
			अगर (!(flags & buf))
				जारी;
			DMA_WRITE(clear_cmd);
			चयन (buf) अणु
			हाल SAVAGE_FRONT:
				DMA_WRITE(dev_priv->front_offset);
				DMA_WRITE(dev_priv->front_bd);
				अवरोध;
			हाल SAVAGE_BACK:
				DMA_WRITE(dev_priv->back_offset);
				DMA_WRITE(dev_priv->back_bd);
				अवरोध;
			हाल SAVAGE_DEPTH:
				DMA_WRITE(dev_priv->depth_offset);
				DMA_WRITE(dev_priv->depth_bd);
				अवरोध;
			पूर्ण
			DMA_WRITE(data->clear1.value);
			DMA_WRITE(BCI_X_Y(x, y));
			DMA_WRITE(BCI_W_H(w, h));
		पूर्ण
		DMA_COMMIT();
	पूर्ण
	अगर (data->clear1.mask != 0xffffffff) अणु
		/* reset mask */
		BEGIN_DMA(2);
		DMA_SET_REGISTERS(SAVAGE_BITPLANEWTMASK, 1);
		DMA_WRITE(0xffffffff);
		DMA_COMMIT();
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक savage_dispatch_swap(drm_savage_निजी_t * dev_priv,
				अचिन्हित पूर्णांक nbox, स्थिर काष्ठा drm_clip_rect *boxes)
अणु
	अचिन्हित पूर्णांक swap_cmd;
	अचिन्हित पूर्णांक i;
	DMA_LOCALS;

	अगर (nbox == 0)
		वापस 0;

	swap_cmd = BCI_CMD_RECT | BCI_CMD_RECT_XP | BCI_CMD_RECT_YP |
	    BCI_CMD_SRC_PBD_COLOR_NEW | BCI_CMD_DEST_GBD;
	BCI_CMD_SET_ROP(swap_cmd, 0xCC);

	क्रम (i = 0; i < nbox; ++i) अणु
		BEGIN_DMA(6);
		DMA_WRITE(swap_cmd);
		DMA_WRITE(dev_priv->back_offset);
		DMA_WRITE(dev_priv->back_bd);
		DMA_WRITE(BCI_X_Y(boxes[i].x1, boxes[i].y1));
		DMA_WRITE(BCI_X_Y(boxes[i].x1, boxes[i].y1));
		DMA_WRITE(BCI_W_H(boxes[i].x2 - boxes[i].x1,
				  boxes[i].y2 - boxes[i].y1));
		DMA_COMMIT();
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक savage_dispatch_draw(drm_savage_निजी_t * dev_priv,
				स्थिर drm_savage_cmd_header_t *start,
				स्थिर drm_savage_cmd_header_t *end,
				स्थिर काष्ठा drm_buf * dmabuf,
				स्थिर अचिन्हित पूर्णांक *vtxbuf,
				अचिन्हित पूर्णांक vb_size, अचिन्हित पूर्णांक vb_stride,
				अचिन्हित पूर्णांक nbox,
				स्थिर काष्ठा drm_clip_rect *boxes)
अणु
	अचिन्हित पूर्णांक i, j;
	पूर्णांक ret;

	क्रम (i = 0; i < nbox; ++i) अणु
		स्थिर drm_savage_cmd_header_t *cmdbuf;
		dev_priv->emit_clip_rect(dev_priv, &boxes[i]);

		cmdbuf = start;
		जबतक (cmdbuf < end) अणु
			drm_savage_cmd_header_t cmd_header;
			cmd_header = *cmdbuf;
			cmdbuf++;
			चयन (cmd_header.cmd.cmd) अणु
			हाल SAVAGE_CMD_DMA_PRIM:
				ret = savage_dispatch_dma_prim(
					dev_priv, &cmd_header, dmabuf);
				अवरोध;
			हाल SAVAGE_CMD_VB_PRIM:
				ret = savage_dispatch_vb_prim(
					dev_priv, &cmd_header,
					vtxbuf, vb_size, vb_stride);
				अवरोध;
			हाल SAVAGE_CMD_DMA_IDX:
				j = (cmd_header.idx.count + 3) / 4;
				/* j was check in savage_bci_cmdbuf */
				ret = savage_dispatch_dma_idx(dev_priv,
					&cmd_header, (स्थिर uपूर्णांक16_t *)cmdbuf,
					dmabuf);
				cmdbuf += j;
				अवरोध;
			हाल SAVAGE_CMD_VB_IDX:
				j = (cmd_header.idx.count + 3) / 4;
				/* j was check in savage_bci_cmdbuf */
				ret = savage_dispatch_vb_idx(dev_priv,
					&cmd_header, (स्थिर uपूर्णांक16_t *)cmdbuf,
					(स्थिर uपूर्णांक32_t *)vtxbuf, vb_size,
					vb_stride);
				cmdbuf += j;
				अवरोध;
			शेष:
				/* What's the best वापस code? EFAULT? */
				DRM_ERROR("IMPLEMENTATION ERROR: "
					  "non-drawing-command %d\n",
					  cmd_header.cmd.cmd);
				वापस -EINVAL;
			पूर्ण

			अगर (ret != 0)
				वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक savage_bci_cmdbuf(काष्ठा drm_device *dev, व्योम *data, काष्ठा drm_file *file_priv)
अणु
	drm_savage_निजी_t *dev_priv = dev->dev_निजी;
	काष्ठा drm_device_dma *dma = dev->dma;
	काष्ठा drm_buf *dmabuf;
	drm_savage_cmdbuf_t *cmdbuf = data;
	drm_savage_cmd_header_t *kcmd_addr = शून्य;
	drm_savage_cmd_header_t *first_draw_cmd;
	अचिन्हित पूर्णांक *kvb_addr = शून्य;
	काष्ठा drm_clip_rect *kbox_addr = शून्य;
	अचिन्हित पूर्णांक i, j;
	पूर्णांक ret = 0;

	DRM_DEBUG("\n");

	LOCK_TEST_WITH_RETURN(dev, file_priv);

	अगर (dma && dma->buflist) अणु
		अगर (cmdbuf->dma_idx >= dma->buf_count) अणु
			DRM_ERROR
			    ("vertex buffer index %u out of range (0-%u)\n",
			     cmdbuf->dma_idx, dma->buf_count - 1);
			वापस -EINVAL;
		पूर्ण
		dmabuf = dma->buflist[cmdbuf->dma_idx];
	पूर्ण अन्यथा अणु
		dmabuf = शून्य;
	पूर्ण

	/* Copy the user buffers पूर्णांकo kernel temporary areas.  This hasn't been
	 * a perक्रमmance loss compared to VERIFYAREA_READ/
	 * COPY_FROM_USER_UNCHECKED when करोne in other drivers, and is correct
	 * क्रम locking on FreeBSD.
	 */
	अगर (cmdbuf->size) अणु
		kcmd_addr = kदो_स्मृति_array(cmdbuf->size, 8, GFP_KERNEL);
		अगर (kcmd_addr == शून्य)
			वापस -ENOMEM;

		अगर (copy_from_user(kcmd_addr, cmdbuf->cmd_addr,
				       cmdbuf->size * 8))
		अणु
			kमुक्त(kcmd_addr);
			वापस -EFAULT;
		पूर्ण
		cmdbuf->cmd_addr = kcmd_addr;
	पूर्ण
	अगर (cmdbuf->vb_size) अणु
		kvb_addr = memdup_user(cmdbuf->vb_addr, cmdbuf->vb_size);
		अगर (IS_ERR(kvb_addr)) अणु
			ret = PTR_ERR(kvb_addr);
			kvb_addr = शून्य;
			जाओ करोne;
		पूर्ण
		cmdbuf->vb_addr = kvb_addr;
	पूर्ण
	अगर (cmdbuf->nbox) अणु
		kbox_addr = kदो_स्मृति_array(cmdbuf->nbox, माप(काष्ठा drm_clip_rect),
					  GFP_KERNEL);
		अगर (kbox_addr == शून्य) अणु
			ret = -ENOMEM;
			जाओ करोne;
		पूर्ण

		अगर (copy_from_user(kbox_addr, cmdbuf->box_addr,
				       cmdbuf->nbox * माप(काष्ठा drm_clip_rect))) अणु
			ret = -EFAULT;
			जाओ करोne;
		पूर्ण
	cmdbuf->box_addr = kbox_addr;
	पूर्ण

	/* Make sure ग_लिखोs to DMA buffers are finished beक्रमe sending
	 * DMA commands to the graphics hardware. */
	mb();

	/* Coming from user space. Don't know अगर the Xserver has
	 * emitted रुको commands. Assuming the worst. */
	dev_priv->रुकोing = 1;

	i = 0;
	first_draw_cmd = शून्य;
	जबतक (i < cmdbuf->size) अणु
		drm_savage_cmd_header_t cmd_header;
		cmd_header = *(drm_savage_cmd_header_t *)cmdbuf->cmd_addr;
		cmdbuf->cmd_addr++;
		i++;

		/* Group drawing commands with same state to minimize
		 * iterations over clip rects. */
		j = 0;
		चयन (cmd_header.cmd.cmd) अणु
		हाल SAVAGE_CMD_DMA_IDX:
		हाल SAVAGE_CMD_VB_IDX:
			j = (cmd_header.idx.count + 3) / 4;
			अगर (i + j > cmdbuf->size) अणु
				DRM_ERROR("indexed drawing command extends "
					  "beyond end of command buffer\n");
				DMA_FLUSH();
				ret = -EINVAL;
				जाओ करोne;
			पूर्ण
			fallthrough;
		हाल SAVAGE_CMD_DMA_PRIM:
		हाल SAVAGE_CMD_VB_PRIM:
			अगर (!first_draw_cmd)
				first_draw_cmd = cmdbuf->cmd_addr - 1;
			cmdbuf->cmd_addr += j;
			i += j;
			अवरोध;
		शेष:
			अगर (first_draw_cmd) अणु
				ret = savage_dispatch_draw(
				      dev_priv, first_draw_cmd,
				      cmdbuf->cmd_addr - 1,
				      dmabuf, cmdbuf->vb_addr, cmdbuf->vb_size,
				      cmdbuf->vb_stride,
				      cmdbuf->nbox, cmdbuf->box_addr);
				अगर (ret != 0)
					जाओ करोne;
				first_draw_cmd = शून्य;
			पूर्ण
		पूर्ण
		अगर (first_draw_cmd)
			जारी;

		चयन (cmd_header.cmd.cmd) अणु
		हाल SAVAGE_CMD_STATE:
			j = (cmd_header.state.count + 1) / 2;
			अगर (i + j > cmdbuf->size) अणु
				DRM_ERROR("command SAVAGE_CMD_STATE extends "
					  "beyond end of command buffer\n");
				DMA_FLUSH();
				ret = -EINVAL;
				जाओ करोne;
			पूर्ण
			ret = savage_dispatch_state(dev_priv, &cmd_header,
				(स्थिर uपूर्णांक32_t *)cmdbuf->cmd_addr);
			cmdbuf->cmd_addr += j;
			i += j;
			अवरोध;
		हाल SAVAGE_CMD_CLEAR:
			अगर (i + 1 > cmdbuf->size) अणु
				DRM_ERROR("command SAVAGE_CMD_CLEAR extends "
					  "beyond end of command buffer\n");
				DMA_FLUSH();
				ret = -EINVAL;
				जाओ करोne;
			पूर्ण
			ret = savage_dispatch_clear(dev_priv, &cmd_header,
						    cmdbuf->cmd_addr,
						    cmdbuf->nbox,
						    cmdbuf->box_addr);
			cmdbuf->cmd_addr++;
			i++;
			अवरोध;
		हाल SAVAGE_CMD_SWAP:
			ret = savage_dispatch_swap(dev_priv, cmdbuf->nbox,
						   cmdbuf->box_addr);
			अवरोध;
		शेष:
			DRM_ERROR("invalid command 0x%x\n",
				  cmd_header.cmd.cmd);
			DMA_FLUSH();
			ret = -EINVAL;
			जाओ करोne;
		पूर्ण

		अगर (ret != 0) अणु
			DMA_FLUSH();
			जाओ करोne;
		पूर्ण
	पूर्ण

	अगर (first_draw_cmd) अणु
		ret = savage_dispatch_draw (
			dev_priv, first_draw_cmd, cmdbuf->cmd_addr, dmabuf,
			cmdbuf->vb_addr, cmdbuf->vb_size, cmdbuf->vb_stride,
			cmdbuf->nbox, cmdbuf->box_addr);
		अगर (ret != 0) अणु
			DMA_FLUSH();
			जाओ करोne;
		पूर्ण
	पूर्ण

	DMA_FLUSH();

	अगर (dmabuf && cmdbuf->discard) अणु
		drm_savage_buf_priv_t *buf_priv = dmabuf->dev_निजी;
		uपूर्णांक16_t event;
		event = savage_bci_emit_event(dev_priv, SAVAGE_WAIT_3D);
		SET_AGE(&buf_priv->age, event, dev_priv->event_wrap);
		savage_मुक्तlist_put(dev, dmabuf);
	पूर्ण

करोne:
	/* If we didn't need to allocate them, these'll be शून्य */
	kमुक्त(kcmd_addr);
	kमुक्त(kvb_addr);
	kमुक्त(kbox_addr);

	वापस ret;
पूर्ण
