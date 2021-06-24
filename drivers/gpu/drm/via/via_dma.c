<शैली गुरु>
/* via_dma.c -- DMA support क्रम the VIA Unichrome/Pro
 *
 * Copyright 2003 Tungsten Graphics, Inc., Cedar Park, Texas.
 * All Rights Reserved.
 *
 * Copyright 2004 Digeo, Inc., Palo Alto, CA, U.S.A.
 * All Rights Reserved.
 *
 * Copyright 2004 The Unichrome project.
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
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL
 * THE COPYRIGHT HOLDERS, AUTHORS AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
 * USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * Authors:
 *    Tungsten Graphics,
 *    Erdi Chen,
 *    Thomas Hellstrom.
 */

#समावेश <linux/delay.h>
#समावेश <linux/uaccess.h>

#समावेश <drm/drm.h>
#समावेश <drm/drm_agpsupport.h>
#समावेश <drm/drm_device.h>
#समावेश <drm/drm_file.h>
#समावेश <drm/via_drm.h>

#समावेश "via_drv.h"
#समावेश "via_3d_reg.h"

#घोषणा CMDBUF_ALIGNMENT_SIZE   (0x100)
#घोषणा CMDBUF_ALIGNMENT_MASK   (0x0ff)

/* defines क्रम VIA 3D रेजिस्टरs */
#घोषणा VIA_REG_STATUS          0x400
#घोषणा VIA_REG_TRANSET         0x43C
#घोषणा VIA_REG_TRANSPACE       0x440

/* VIA_REG_STATUS(0x400): Engine Status */
#घोषणा VIA_CMD_RGTR_BUSY       0x00000080	/* Command Regulator is busy */
#घोषणा VIA_2D_ENG_BUSY         0x00000001	/* 2D Engine is busy */
#घोषणा VIA_3D_ENG_BUSY         0x00000002	/* 3D Engine is busy */
#घोषणा VIA_VR_QUEUE_BUSY       0x00020000	/* Virtual Queue is busy */

#घोषणा SetReg2DAGP(nReg, nData) अणु				\
	*((uपूर्णांक32_t *)(vb)) = ((nReg) >> 2) | HALCYON_HEADER1;	\
	*((uपूर्णांक32_t *)(vb) + 1) = (nData);			\
	vb = ((uपूर्णांक32_t *)vb) + 2;				\
	dev_priv->dma_low += 8;					\
पूर्ण

#घोषणा via_flush_ग_लिखो_combine() mb()

#घोषणा VIA_OUT_RING_QW(w1, w2)	करो अणु		\
	*vb++ = (w1);				\
	*vb++ = (w2);				\
	dev_priv->dma_low += 8;			\
पूर्ण जबतक (0)

अटल व्योम via_cmdbuf_start(drm_via_निजी_t *dev_priv);
अटल व्योम via_cmdbuf_छोड़ो(drm_via_निजी_t *dev_priv);
अटल व्योम via_cmdbuf_reset(drm_via_निजी_t *dev_priv);
अटल व्योम via_cmdbuf_शुरुआत(drm_via_निजी_t *dev_priv);
अटल पूर्णांक via_रुको_idle(drm_via_निजी_t *dev_priv);
अटल व्योम via_pad_cache(drm_via_निजी_t *dev_priv, पूर्णांक qwords);

/*
 * Free space in command buffer.
 */

अटल uपूर्णांक32_t via_cmdbuf_space(drm_via_निजी_t *dev_priv)
अणु
	uपूर्णांक32_t agp_base = dev_priv->dma_offset + (uपूर्णांक32_t) dev_priv->agpAddr;
	uपूर्णांक32_t hw_addr = *(dev_priv->hw_addr_ptr) - agp_base;

	वापस ((hw_addr <= dev_priv->dma_low) ?
		(dev_priv->dma_high + hw_addr - dev_priv->dma_low) :
		(hw_addr - dev_priv->dma_low));
पूर्ण

/*
 * How much करोes the command regulator lag behind?
 */

अटल uपूर्णांक32_t via_cmdbuf_lag(drm_via_निजी_t *dev_priv)
अणु
	uपूर्णांक32_t agp_base = dev_priv->dma_offset + (uपूर्णांक32_t) dev_priv->agpAddr;
	uपूर्णांक32_t hw_addr = *(dev_priv->hw_addr_ptr) - agp_base;

	वापस ((hw_addr <= dev_priv->dma_low) ?
		(dev_priv->dma_low - hw_addr) :
		(dev_priv->dma_wrap + dev_priv->dma_low - hw_addr));
पूर्ण

/*
 * Check that the given size fits in the buffer, otherwise रुको.
 */

अटल अंतरभूत पूर्णांक
via_cmdbuf_रुको(drm_via_निजी_t *dev_priv, अचिन्हित पूर्णांक size)
अणु
	uपूर्णांक32_t agp_base = dev_priv->dma_offset + (uपूर्णांक32_t) dev_priv->agpAddr;
	uपूर्णांक32_t cur_addr, hw_addr, next_addr;
	अस्थिर uपूर्णांक32_t *hw_addr_ptr;
	uपूर्णांक32_t count;
	hw_addr_ptr = dev_priv->hw_addr_ptr;
	cur_addr = dev_priv->dma_low;
	next_addr = cur_addr + size + 512 * 1024;
	count = 1000000;
	करो अणु
		hw_addr = *hw_addr_ptr - agp_base;
		अगर (count-- == 0) अणु
			DRM_ERROR
			    ("via_cmdbuf_wait timed out hw %x cur_addr %x next_addr %x\n",
			     hw_addr, cur_addr, next_addr);
			वापस -1;
		पूर्ण
		अगर  ((cur_addr < hw_addr) && (next_addr >= hw_addr))
			msleep(1);
	पूर्ण जबतक ((cur_addr < hw_addr) && (next_addr >= hw_addr));
	वापस 0;
पूर्ण

/*
 * Checks whether buffer head has reach the end. Rewind the ring buffer
 * when necessary.
 *
 * Returns भव poपूर्णांकer to ring buffer.
 */

अटल अंतरभूत uपूर्णांक32_t *via_check_dma(drm_via_निजी_t * dev_priv,
				      अचिन्हित पूर्णांक size)
अणु
	अगर ((dev_priv->dma_low + size + 4 * CMDBUF_ALIGNMENT_SIZE) >
	    dev_priv->dma_high) अणु
		via_cmdbuf_शुरुआत(dev_priv);
	पूर्ण
	अगर (via_cmdbuf_रुको(dev_priv, size) != 0)
		वापस शून्य;

	वापस (uपूर्णांक32_t *) (dev_priv->dma_ptr + dev_priv->dma_low);
पूर्ण

पूर्णांक via_dma_cleanup(काष्ठा drm_device *dev)
अणु
	अगर (dev->dev_निजी) अणु
		drm_via_निजी_t *dev_priv =
		    (drm_via_निजी_t *) dev->dev_निजी;

		अगर (dev_priv->ring.भव_start) अणु
			via_cmdbuf_reset(dev_priv);

			drm_legacy_ioremapमुक्त(&dev_priv->ring.map, dev);
			dev_priv->ring.भव_start = शून्य;
		पूर्ण

	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक via_initialize(काष्ठा drm_device *dev,
			  drm_via_निजी_t *dev_priv,
			  drm_via_dma_init_t *init)
अणु
	अगर (!dev_priv || !dev_priv->mmio) अणु
		DRM_ERROR("via_dma_init called before via_map_init\n");
		वापस -EFAULT;
	पूर्ण

	अगर (dev_priv->ring.भव_start != शून्य) अणु
		DRM_ERROR("called again without calling cleanup\n");
		वापस -EFAULT;
	पूर्ण

	अगर (!dev->agp || !dev->agp->base) अणु
		DRM_ERROR("called with no agp memory available\n");
		वापस -EFAULT;
	पूर्ण

	अगर (dev_priv->chipset == VIA_DX9_0) अणु
		DRM_ERROR("AGP DMA is not supported on this chip\n");
		वापस -EINVAL;
	पूर्ण

	dev_priv->ring.map.offset = dev->agp->base + init->offset;
	dev_priv->ring.map.size = init->size;
	dev_priv->ring.map.type = 0;
	dev_priv->ring.map.flags = 0;
	dev_priv->ring.map.mtrr = 0;

	drm_legacy_ioremap(&dev_priv->ring.map, dev);

	अगर (dev_priv->ring.map.handle == शून्य) अणु
		via_dma_cleanup(dev);
		DRM_ERROR("can not ioremap virtual address for"
			  " ring buffer\n");
		वापस -ENOMEM;
	पूर्ण

	dev_priv->ring.भव_start = dev_priv->ring.map.handle;

	dev_priv->dma_ptr = dev_priv->ring.भव_start;
	dev_priv->dma_low = 0;
	dev_priv->dma_high = init->size;
	dev_priv->dma_wrap = init->size;
	dev_priv->dma_offset = init->offset;
	dev_priv->last_छोड़ो_ptr = शून्य;
	dev_priv->hw_addr_ptr =
		(अस्थिर uपूर्णांक32_t *)((अक्षर *)dev_priv->mmio->handle +
		init->reg_छोड़ो_addr);

	via_cmdbuf_start(dev_priv);

	वापस 0;
पूर्ण

अटल पूर्णांक via_dma_init(काष्ठा drm_device *dev, व्योम *data, काष्ठा drm_file *file_priv)
अणु
	drm_via_निजी_t *dev_priv = (drm_via_निजी_t *) dev->dev_निजी;
	drm_via_dma_init_t *init = data;
	पूर्णांक retcode = 0;

	चयन (init->func) अणु
	हाल VIA_INIT_DMA:
		अगर (!capable(CAP_SYS_ADMIN))
			retcode = -EPERM;
		अन्यथा
			retcode = via_initialize(dev, dev_priv, init);
		अवरोध;
	हाल VIA_CLEANUP_DMA:
		अगर (!capable(CAP_SYS_ADMIN))
			retcode = -EPERM;
		अन्यथा
			retcode = via_dma_cleanup(dev);
		अवरोध;
	हाल VIA_DMA_INITIALIZED:
		retcode = (dev_priv->ring.भव_start != शून्य) ?
			0 : -EFAULT;
		अवरोध;
	शेष:
		retcode = -EINVAL;
		अवरोध;
	पूर्ण

	वापस retcode;
पूर्ण

अटल पूर्णांक via_dispatch_cmdbuffer(काष्ठा drm_device *dev, drm_via_cmdbuffer_t *cmd)
अणु
	drm_via_निजी_t *dev_priv;
	uपूर्णांक32_t *vb;
	पूर्णांक ret;

	dev_priv = (drm_via_निजी_t *) dev->dev_निजी;

	अगर (dev_priv->ring.भव_start == शून्य) अणु
		DRM_ERROR("called without initializing AGP ring buffer.\n");
		वापस -EFAULT;
	पूर्ण

	अगर (cmd->size > VIA_PCI_BUF_SIZE)
		वापस -ENOMEM;

	अगर (copy_from_user(dev_priv->pci_buf, cmd->buf, cmd->size))
		वापस -EFAULT;

	/*
	 * Running this function on AGP memory is dead slow. Thereक्रमe
	 * we run it on a temporary cacheable प्रणाली memory buffer and
	 * copy it to AGP memory when पढ़ोy.
	 */

	अगर ((ret =
	     via_verअगरy_command_stream((uपूर्णांक32_t *) dev_priv->pci_buf,
				       cmd->size, dev, 1))) अणु
		वापस ret;
	पूर्ण

	vb = via_check_dma(dev_priv, (cmd->size < 0x100) ? 0x102 : cmd->size);
	अगर (vb == शून्य)
		वापस -EAGAIN;

	स_नकल(vb, dev_priv->pci_buf, cmd->size);

	dev_priv->dma_low += cmd->size;

	/*
	 * Small submissions somehow stalls the CPU. (AGP cache effects?)
	 * pad to greater size.
	 */

	अगर (cmd->size < 0x100)
		via_pad_cache(dev_priv, (0x100 - cmd->size) >> 3);
	via_cmdbuf_छोड़ो(dev_priv);

	वापस 0;
पूर्ण

पूर्णांक via_driver_dma_quiescent(काष्ठा drm_device *dev)
अणु
	drm_via_निजी_t *dev_priv = dev->dev_निजी;

	अगर (!via_रुको_idle(dev_priv))
		वापस -EBUSY;
	वापस 0;
पूर्ण

अटल पूर्णांक via_flush_ioctl(काष्ठा drm_device *dev, व्योम *data, काष्ठा drm_file *file_priv)
अणु

	LOCK_TEST_WITH_RETURN(dev, file_priv);

	वापस via_driver_dma_quiescent(dev);
पूर्ण

अटल पूर्णांक via_cmdbuffer(काष्ठा drm_device *dev, व्योम *data, काष्ठा drm_file *file_priv)
अणु
	drm_via_cmdbuffer_t *cmdbuf = data;
	पूर्णांक ret;

	LOCK_TEST_WITH_RETURN(dev, file_priv);

	DRM_DEBUG("buf %p size %lu\n", cmdbuf->buf, cmdbuf->size);

	ret = via_dispatch_cmdbuffer(dev, cmdbuf);
	वापस ret;
पूर्ण

अटल पूर्णांक via_dispatch_pci_cmdbuffer(काष्ठा drm_device *dev,
				      drm_via_cmdbuffer_t *cmd)
अणु
	drm_via_निजी_t *dev_priv = dev->dev_निजी;
	पूर्णांक ret;

	अगर (cmd->size > VIA_PCI_BUF_SIZE)
		वापस -ENOMEM;
	अगर (copy_from_user(dev_priv->pci_buf, cmd->buf, cmd->size))
		वापस -EFAULT;

	अगर ((ret =
	     via_verअगरy_command_stream((uपूर्णांक32_t *) dev_priv->pci_buf,
				       cmd->size, dev, 0))) अणु
		वापस ret;
	पूर्ण

	ret =
	    via_parse_command_stream(dev, (स्थिर uपूर्णांक32_t *)dev_priv->pci_buf,
				     cmd->size);
	वापस ret;
पूर्ण

अटल पूर्णांक via_pci_cmdbuffer(काष्ठा drm_device *dev, व्योम *data, काष्ठा drm_file *file_priv)
अणु
	drm_via_cmdbuffer_t *cmdbuf = data;
	पूर्णांक ret;

	LOCK_TEST_WITH_RETURN(dev, file_priv);

	DRM_DEBUG("buf %p size %lu\n", cmdbuf->buf, cmdbuf->size);

	ret = via_dispatch_pci_cmdbuffer(dev, cmdbuf);
	वापस ret;
पूर्ण

अटल अंतरभूत uपूर्णांक32_t *via_align_buffer(drm_via_निजी_t *dev_priv,
					 uपूर्णांक32_t * vb, पूर्णांक qw_count)
अणु
	क्रम (; qw_count > 0; --qw_count)
		VIA_OUT_RING_QW(HC_DUMMY, HC_DUMMY);
	वापस vb;
पूर्ण

/*
 * This function is used पूर्णांकernally by ring buffer management code.
 *
 * Returns भव poपूर्णांकer to ring buffer.
 */
अटल अंतरभूत uपूर्णांक32_t *via_get_dma(drm_via_निजी_t *dev_priv)
अणु
	वापस (uपूर्णांक32_t *) (dev_priv->dma_ptr + dev_priv->dma_low);
पूर्ण

/*
 * Hooks a segment of data पूर्णांकo the tail of the ring-buffer by
 * modअगरying the छोड़ो address stored in the buffer itself. If
 * the regulator has alपढ़ोy छोड़ोd, restart it.
 */
अटल पूर्णांक via_hook_segment(drm_via_निजी_t *dev_priv,
			    uपूर्णांक32_t छोड़ो_addr_hi, uपूर्णांक32_t छोड़ो_addr_lo,
			    पूर्णांक no_pci_fire)
अणु
	पूर्णांक छोड़ोd, count;
	अस्थिर uपूर्णांक32_t *छोड़ोd_at = dev_priv->last_छोड़ो_ptr;
	uपूर्णांक32_t पढ़ोer, ptr;
	uपूर्णांक32_t dअगरf;

	छोड़ोd = 0;
	via_flush_ग_लिखो_combine();
	(व्योम) *(अस्थिर uपूर्णांक32_t *)(via_get_dma(dev_priv) - 1);

	*छोड़ोd_at = छोड़ो_addr_lo;
	via_flush_ग_लिखो_combine();
	(व्योम) *छोड़ोd_at;

	पढ़ोer = *(dev_priv->hw_addr_ptr);
	ptr = ((अस्थिर अक्षर *)छोड़ोd_at - dev_priv->dma_ptr) +
		dev_priv->dma_offset + (uपूर्णांक32_t) dev_priv->agpAddr + 4;

	dev_priv->last_छोड़ो_ptr = via_get_dma(dev_priv) - 1;

	/*
	 * If there is a possibility that the command पढ़ोer will
	 * miss the new छोड़ो address and छोड़ो on the old one,
	 * In that हाल we need to program the new start address
	 * using PCI.
	 */

	dअगरf = (uपूर्णांक32_t) (ptr - पढ़ोer) - dev_priv->dma_dअगरf;
	count = 10000000;
	जबतक (dअगरf == 0 && count--) अणु
		छोड़ोd = (via_पढ़ो(dev_priv, 0x41c) & 0x80000000);
		अगर (छोड़ोd)
			अवरोध;
		पढ़ोer = *(dev_priv->hw_addr_ptr);
		dअगरf = (uपूर्णांक32_t) (ptr - पढ़ोer) - dev_priv->dma_dअगरf;
	पूर्ण

	छोड़ोd = via_पढ़ो(dev_priv, 0x41c) & 0x80000000;

	अगर (छोड़ोd && !no_pci_fire) अणु
		पढ़ोer = *(dev_priv->hw_addr_ptr);
		dअगरf = (uपूर्णांक32_t) (ptr - पढ़ोer) - dev_priv->dma_dअगरf;
		dअगरf &= (dev_priv->dma_high - 1);
		अगर (dअगरf != 0 && dअगरf < (dev_priv->dma_high >> 1)) अणु
			DRM_ERROR("Paused at incorrect address. "
				  "0x%08x, 0x%08x 0x%08x\n",
				  ptr, पढ़ोer, dev_priv->dma_dअगरf);
		पूर्ण अन्यथा अगर (dअगरf == 0) अणु
			/*
			 * There is a concern that these ग_लिखोs may stall the PCI bus
			 * अगर the GPU is not idle. However, idling the GPU first
			 * करोesn't make a dअगरference.
			 */

			via_ग_लिखो(dev_priv, VIA_REG_TRANSET, (HC_ParaType_PreCR << 16));
			via_ग_लिखो(dev_priv, VIA_REG_TRANSPACE, छोड़ो_addr_hi);
			via_ग_लिखो(dev_priv, VIA_REG_TRANSPACE, छोड़ो_addr_lo);
			via_पढ़ो(dev_priv, VIA_REG_TRANSPACE);
		पूर्ण
	पूर्ण
	वापस छोड़ोd;
पूर्ण

अटल पूर्णांक via_रुको_idle(drm_via_निजी_t *dev_priv)
अणु
	पूर्णांक count = 10000000;

	जबतक (!(via_पढ़ो(dev_priv, VIA_REG_STATUS) & VIA_VR_QUEUE_BUSY) && --count)
		;

	जबतक (count && (via_पढ़ो(dev_priv, VIA_REG_STATUS) &
			   (VIA_CMD_RGTR_BUSY | VIA_2D_ENG_BUSY |
			    VIA_3D_ENG_BUSY)))
		--count;
	वापस count;
पूर्ण

अटल uपूर्णांक32_t *via_align_cmd(drm_via_निजी_t *dev_priv, uपूर्णांक32_t cmd_type,
			       uपूर्णांक32_t addr, uपूर्णांक32_t *cmd_addr_hi,
			       uपूर्णांक32_t *cmd_addr_lo, पूर्णांक skip_रुको)
अणु
	uपूर्णांक32_t agp_base;
	uपूर्णांक32_t cmd_addr, addr_lo, addr_hi;
	uपूर्णांक32_t *vb;
	uपूर्णांक32_t qw_pad_count;

	अगर (!skip_रुको)
		via_cmdbuf_रुको(dev_priv, 2 * CMDBUF_ALIGNMENT_SIZE);

	vb = via_get_dma(dev_priv);
	VIA_OUT_RING_QW(HC_HEADER2 | ((VIA_REG_TRANSET >> 2) << 12) |
			(VIA_REG_TRANSPACE >> 2), HC_ParaType_PreCR << 16);
	agp_base = dev_priv->dma_offset + (uपूर्णांक32_t) dev_priv->agpAddr;
	qw_pad_count = (CMDBUF_ALIGNMENT_SIZE >> 3) -
	    ((dev_priv->dma_low & CMDBUF_ALIGNMENT_MASK) >> 3);

	cmd_addr = (addr) ? addr :
	    agp_base + dev_priv->dma_low - 8 + (qw_pad_count << 3);
	addr_lo = ((HC_SubA_HAGPBpL << 24) | (cmd_type & HC_HAGPBpID_MASK) |
		   (cmd_addr & HC_HAGPBpL_MASK));
	addr_hi = ((HC_SubA_HAGPBpH << 24) | (cmd_addr >> 24));

	vb = via_align_buffer(dev_priv, vb, qw_pad_count - 1);
	VIA_OUT_RING_QW(*cmd_addr_hi = addr_hi, *cmd_addr_lo = addr_lo);
	वापस vb;
पूर्ण

अटल व्योम via_cmdbuf_start(drm_via_निजी_t *dev_priv)
अणु
	uपूर्णांक32_t छोड़ो_addr_lo, छोड़ो_addr_hi;
	uपूर्णांक32_t start_addr, start_addr_lo;
	uपूर्णांक32_t end_addr, end_addr_lo;
	uपूर्णांक32_t command;
	uपूर्णांक32_t agp_base;
	uपूर्णांक32_t ptr;
	uपूर्णांक32_t पढ़ोer;
	पूर्णांक count;

	dev_priv->dma_low = 0;

	agp_base = dev_priv->dma_offset + (uपूर्णांक32_t) dev_priv->agpAddr;
	start_addr = agp_base;
	end_addr = agp_base + dev_priv->dma_high;

	start_addr_lo = ((HC_SubA_HAGPBstL << 24) | (start_addr & 0xFFFFFF));
	end_addr_lo = ((HC_SubA_HAGPBendL << 24) | (end_addr & 0xFFFFFF));
	command = ((HC_SubA_HAGPCMNT << 24) | (start_addr >> 24) |
		   ((end_addr & 0xff000000) >> 16));

	dev_priv->last_छोड़ो_ptr =
	    via_align_cmd(dev_priv, HC_HAGPBpID_PAUSE, 0,
			  &छोड़ो_addr_hi, &छोड़ो_addr_lo, 1) - 1;

	via_flush_ग_लिखो_combine();
	(व्योम) *(अस्थिर uपूर्णांक32_t *)dev_priv->last_छोड़ो_ptr;

	via_ग_लिखो(dev_priv, VIA_REG_TRANSET, (HC_ParaType_PreCR << 16));
	via_ग_लिखो(dev_priv, VIA_REG_TRANSPACE, command);
	via_ग_लिखो(dev_priv, VIA_REG_TRANSPACE, start_addr_lo);
	via_ग_लिखो(dev_priv, VIA_REG_TRANSPACE, end_addr_lo);

	via_ग_लिखो(dev_priv, VIA_REG_TRANSPACE, छोड़ो_addr_hi);
	via_ग_लिखो(dev_priv, VIA_REG_TRANSPACE, छोड़ो_addr_lo);
	wmb();
	via_ग_लिखो(dev_priv, VIA_REG_TRANSPACE, command | HC_HAGPCMNT_MASK);
	via_पढ़ो(dev_priv, VIA_REG_TRANSPACE);

	dev_priv->dma_dअगरf = 0;

	count = 10000000;
	जबतक (!(via_पढ़ो(dev_priv, 0x41c) & 0x80000000) && count--);

	पढ़ोer = *(dev_priv->hw_addr_ptr);
	ptr = ((अस्थिर अक्षर *)dev_priv->last_छोड़ो_ptr - dev_priv->dma_ptr) +
	    dev_priv->dma_offset + (uपूर्णांक32_t) dev_priv->agpAddr + 4;

	/*
	 * This is the dअगरference between where we tell the
	 * command पढ़ोer to छोड़ो and where it actually छोड़ोs.
	 * This dअगरfers between hw implementation so we need to
	 * detect it.
	 */

	dev_priv->dma_dअगरf = ptr - पढ़ोer;
पूर्ण

अटल व्योम via_pad_cache(drm_via_निजी_t *dev_priv, पूर्णांक qwords)
अणु
	uपूर्णांक32_t *vb;

	via_cmdbuf_रुको(dev_priv, qwords + 2);
	vb = via_get_dma(dev_priv);
	VIA_OUT_RING_QW(HC_HEADER2, HC_ParaType_NotTex << 16);
	via_align_buffer(dev_priv, vb, qwords);
पूर्ण

अटल अंतरभूत व्योम via_dummy_bitblt(drm_via_निजी_t *dev_priv)
अणु
	uपूर्णांक32_t *vb = via_get_dma(dev_priv);
	SetReg2DAGP(0x0C, (0 | (0 << 16)));
	SetReg2DAGP(0x10, 0 | (0 << 16));
	SetReg2DAGP(0x0, 0x1 | 0x2000 | 0xAA000000);
पूर्ण

अटल व्योम via_cmdbuf_jump(drm_via_निजी_t *dev_priv)
अणु
	uपूर्णांक32_t छोड़ो_addr_lo, छोड़ो_addr_hi;
	uपूर्णांक32_t jump_addr_lo, jump_addr_hi;
	अस्थिर uपूर्णांक32_t *last_छोड़ो_ptr;
	uपूर्णांक32_t dma_low_save1, dma_low_save2;

	via_align_cmd(dev_priv, HC_HAGPBpID_JUMP, 0, &jump_addr_hi,
		      &jump_addr_lo, 0);

	dev_priv->dma_wrap = dev_priv->dma_low;

	/*
	 * Wrap command buffer to the beginning.
	 */

	dev_priv->dma_low = 0;
	अगर (via_cmdbuf_रुको(dev_priv, CMDBUF_ALIGNMENT_SIZE) != 0)
		DRM_ERROR("via_cmdbuf_jump failed\n");

	via_dummy_bitblt(dev_priv);
	via_dummy_bitblt(dev_priv);

	last_छोड़ो_ptr =
	    via_align_cmd(dev_priv, HC_HAGPBpID_PAUSE, 0, &छोड़ो_addr_hi,
			  &छोड़ो_addr_lo, 0) - 1;
	via_align_cmd(dev_priv, HC_HAGPBpID_PAUSE, 0, &छोड़ो_addr_hi,
		      &छोड़ो_addr_lo, 0);

	*last_छोड़ो_ptr = छोड़ो_addr_lo;
	dma_low_save1 = dev_priv->dma_low;

	/*
	 * Now, set a trap that will छोड़ो the regulator अगर it tries to rerun the old
	 * command buffer. (Which may happen अगर via_hook_segment detecs a command regulator छोड़ो
	 * and reissues the jump command over PCI, जबतक the regulator has alपढ़ोy taken the jump
	 * and actually छोड़ोd at the current buffer end).
	 * There appears to be no other way to detect this condition, since the hw_addr_poपूर्णांकer
	 * करोes not seem to get updated immediately when a jump occurs.
	 */

	last_छोड़ो_ptr =
		via_align_cmd(dev_priv, HC_HAGPBpID_PAUSE, 0, &छोड़ो_addr_hi,
			      &छोड़ो_addr_lo, 0) - 1;
	via_align_cmd(dev_priv, HC_HAGPBpID_PAUSE, 0, &छोड़ो_addr_hi,
		      &छोड़ो_addr_lo, 0);
	*last_छोड़ो_ptr = छोड़ो_addr_lo;

	dma_low_save2 = dev_priv->dma_low;
	dev_priv->dma_low = dma_low_save1;
	via_hook_segment(dev_priv, jump_addr_hi, jump_addr_lo, 0);
	dev_priv->dma_low = dma_low_save2;
	via_hook_segment(dev_priv, छोड़ो_addr_hi, छोड़ो_addr_lo, 0);
पूर्ण


अटल व्योम via_cmdbuf_शुरुआत(drm_via_निजी_t *dev_priv)
अणु
	via_cmdbuf_jump(dev_priv);
पूर्ण

अटल व्योम via_cmdbuf_flush(drm_via_निजी_t *dev_priv, uपूर्णांक32_t cmd_type)
अणु
	uपूर्णांक32_t छोड़ो_addr_lo, छोड़ो_addr_hi;

	via_align_cmd(dev_priv, cmd_type, 0, &छोड़ो_addr_hi, &छोड़ो_addr_lo, 0);
	via_hook_segment(dev_priv, छोड़ो_addr_hi, छोड़ो_addr_lo, 0);
पूर्ण

अटल व्योम via_cmdbuf_छोड़ो(drm_via_निजी_t *dev_priv)
अणु
	via_cmdbuf_flush(dev_priv, HC_HAGPBpID_PAUSE);
पूर्ण

अटल व्योम via_cmdbuf_reset(drm_via_निजी_t *dev_priv)
अणु
	via_cmdbuf_flush(dev_priv, HC_HAGPBpID_STOP);
	via_रुको_idle(dev_priv);
पूर्ण

/*
 * User पूर्णांकerface to the space and lag functions.
 */

अटल पूर्णांक via_cmdbuf_size(काष्ठा drm_device *dev, व्योम *data, काष्ठा drm_file *file_priv)
अणु
	drm_via_cmdbuf_माप_प्रकार *d_siz = data;
	पूर्णांक ret = 0;
	uपूर्णांक32_t पंचांगp_size, count;
	drm_via_निजी_t *dev_priv;

	DRM_DEBUG("\n");
	LOCK_TEST_WITH_RETURN(dev, file_priv);

	dev_priv = (drm_via_निजी_t *) dev->dev_निजी;

	अगर (dev_priv->ring.भव_start == शून्य) अणु
		DRM_ERROR("called without initializing AGP ring buffer.\n");
		वापस -EFAULT;
	पूर्ण

	count = 1000000;
	पंचांगp_size = d_siz->size;
	चयन (d_siz->func) अणु
	हाल VIA_CMDBUF_SPACE:
		जबतक (((पंचांगp_size = via_cmdbuf_space(dev_priv)) < d_siz->size)
		       && --count) अणु
			अगर (!d_siz->रुको)
				अवरोध;
		पूर्ण
		अगर (!count) अणु
			DRM_ERROR("VIA_CMDBUF_SPACE timed out.\n");
			ret = -EAGAIN;
		पूर्ण
		अवरोध;
	हाल VIA_CMDBUF_LAG:
		जबतक (((पंचांगp_size = via_cmdbuf_lag(dev_priv)) > d_siz->size)
		       && --count) अणु
			अगर (!d_siz->रुको)
				अवरोध;
		पूर्ण
		अगर (!count) अणु
			DRM_ERROR("VIA_CMDBUF_LAG timed out.\n");
			ret = -EAGAIN;
		पूर्ण
		अवरोध;
	शेष:
		ret = -EFAULT;
	पूर्ण
	d_siz->size = पंचांगp_size;

	वापस ret;
पूर्ण

स्थिर काष्ठा drm_ioctl_desc via_ioctls[] = अणु
	DRM_IOCTL_DEF_DRV(VIA_ALLOCMEM, via_mem_alloc, DRM_AUTH),
	DRM_IOCTL_DEF_DRV(VIA_FREEMEM, via_mem_मुक्त, DRM_AUTH),
	DRM_IOCTL_DEF_DRV(VIA_AGP_INIT, via_agp_init, DRM_AUTH|DRM_MASTER),
	DRM_IOCTL_DEF_DRV(VIA_FB_INIT, via_fb_init, DRM_AUTH|DRM_MASTER),
	DRM_IOCTL_DEF_DRV(VIA_MAP_INIT, via_map_init, DRM_AUTH|DRM_MASTER),
	DRM_IOCTL_DEF_DRV(VIA_DEC_FUTEX, via_decoder_futex, DRM_AUTH),
	DRM_IOCTL_DEF_DRV(VIA_DMA_INIT, via_dma_init, DRM_AUTH),
	DRM_IOCTL_DEF_DRV(VIA_CMDBUFFER, via_cmdbuffer, DRM_AUTH),
	DRM_IOCTL_DEF_DRV(VIA_FLUSH, via_flush_ioctl, DRM_AUTH),
	DRM_IOCTL_DEF_DRV(VIA_PCICMD, via_pci_cmdbuffer, DRM_AUTH),
	DRM_IOCTL_DEF_DRV(VIA_CMDBUF_SIZE, via_cmdbuf_size, DRM_AUTH),
	DRM_IOCTL_DEF_DRV(VIA_WAIT_IRQ, via_रुको_irq, DRM_AUTH),
	DRM_IOCTL_DEF_DRV(VIA_DMA_BLIT, via_dma_blit, DRM_AUTH),
	DRM_IOCTL_DEF_DRV(VIA_BLIT_SYNC, via_dma_blit_sync, DRM_AUTH)
पूर्ण;

पूर्णांक via_max_ioctl = ARRAY_SIZE(via_ioctls);
