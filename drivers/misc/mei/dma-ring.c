<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright(c) 2016-2018 Intel Corporation. All rights reserved.
 */
#समावेश <linux/dma-mapping.h>
#समावेश <linux/mei.h>

#समावेश "mei_dev.h"

/**
 * mei_dmam_dscr_alloc() - allocate a managed coherent buffer
 *     क्रम the dma descriptor
 * @dev: mei_device
 * @dscr: dma descriptor
 *
 * Return:
 * * 0       - on success or zero allocation request
 * * -EINVAL - अगर size is not घातer of 2
 * * -ENOMEM - of allocation has failed
 */
अटल पूर्णांक mei_dmam_dscr_alloc(काष्ठा mei_device *dev,
			       काष्ठा mei_dma_dscr *dscr)
अणु
	अगर (!dscr->size)
		वापस 0;

	अगर (WARN_ON(!is_घातer_of_2(dscr->size)))
		वापस -EINVAL;

	अगर (dscr->vaddr)
		वापस 0;

	dscr->vaddr = dmam_alloc_coherent(dev->dev, dscr->size, &dscr->daddr,
					  GFP_KERNEL);
	अगर (!dscr->vaddr)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

/**
 * mei_dmam_dscr_मुक्त() - मुक्त a managed coherent buffer
 *     from the dma descriptor
 * @dev: mei_device
 * @dscr: dma descriptor
 */
अटल व्योम mei_dmam_dscr_मुक्त(काष्ठा mei_device *dev,
			       काष्ठा mei_dma_dscr *dscr)
अणु
	अगर (!dscr->vaddr)
		वापस;

	dmam_मुक्त_coherent(dev->dev, dscr->size, dscr->vaddr, dscr->daddr);
	dscr->vaddr = शून्य;
पूर्ण

/**
 * mei_dmam_ring_मुक्त() - मुक्त dma ring buffers
 * @dev: mei device
 */
व्योम mei_dmam_ring_मुक्त(काष्ठा mei_device *dev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < DMA_DSCR_NUM; i++)
		mei_dmam_dscr_मुक्त(dev, &dev->dr_dscr[i]);
पूर्ण

/**
 * mei_dmam_ring_alloc() - allocate dma ring buffers
 * @dev: mei device
 *
 * Return: -ENOMEM on allocation failure 0 otherwise
 */
पूर्णांक mei_dmam_ring_alloc(काष्ठा mei_device *dev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < DMA_DSCR_NUM; i++)
		अगर (mei_dmam_dscr_alloc(dev, &dev->dr_dscr[i]))
			जाओ err;

	वापस 0;

err:
	mei_dmam_ring_मुक्त(dev);
	वापस -ENOMEM;
पूर्ण

/**
 * mei_dma_ring_is_allocated() - check अगर dma ring is allocated
 * @dev: mei device
 *
 * Return: true अगर dma ring is allocated
 */
bool mei_dma_ring_is_allocated(काष्ठा mei_device *dev)
अणु
	वापस !!dev->dr_dscr[DMA_DSCR_HOST].vaddr;
पूर्ण

अटल अंतरभूत
काष्ठा hbm_dma_ring_ctrl *mei_dma_ring_ctrl(काष्ठा mei_device *dev)
अणु
	वापस (काष्ठा hbm_dma_ring_ctrl *)dev->dr_dscr[DMA_DSCR_CTRL].vaddr;
पूर्ण

/**
 * mei_dma_ring_reset() - reset the dma control block
 * @dev: mei device
 */
व्योम mei_dma_ring_reset(काष्ठा mei_device *dev)
अणु
	काष्ठा hbm_dma_ring_ctrl *ctrl = mei_dma_ring_ctrl(dev);

	अगर (!ctrl)
		वापस;

	स_रखो(ctrl, 0, माप(*ctrl));
पूर्ण

/**
 * mei_dma_copy_from() - copy from dma ring पूर्णांकo buffer
 * @dev: mei device
 * @buf: data buffer
 * @offset: offset in slots.
 * @n: number of slots to copy.
 */
अटल माप_प्रकार mei_dma_copy_from(काष्ठा mei_device *dev, अचिन्हित अक्षर *buf,
				u32 offset, u32 n)
अणु
	अचिन्हित अक्षर *dbuf = dev->dr_dscr[DMA_DSCR_DEVICE].vaddr;

	माप_प्रकार b_offset = offset << 2;
	माप_प्रकार b_n = n << 2;

	स_नकल(buf, dbuf + b_offset, b_n);

	वापस b_n;
पूर्ण

/**
 * mei_dma_copy_to() - copy to a buffer to the dma ring
 * @dev: mei device
 * @buf: data buffer
 * @offset: offset in slots.
 * @n: number of slots to copy.
 */
अटल माप_प्रकार mei_dma_copy_to(काष्ठा mei_device *dev, अचिन्हित अक्षर *buf,
			      u32 offset, u32 n)
अणु
	अचिन्हित अक्षर *hbuf = dev->dr_dscr[DMA_DSCR_HOST].vaddr;

	माप_प्रकार b_offset = offset << 2;
	माप_प्रकार b_n = n << 2;

	स_नकल(hbuf + b_offset, buf, b_n);

	वापस b_n;
पूर्ण

/**
 * mei_dma_ring_पढ़ो() - पढ़ो data from the ring
 * @dev: mei device
 * @buf: buffer to पढ़ो पूर्णांकo: may be शून्य in हाल of droping the data.
 * @len: length to पढ़ो.
 */
व्योम mei_dma_ring_पढ़ो(काष्ठा mei_device *dev, अचिन्हित अक्षर *buf, u32 len)
अणु
	काष्ठा hbm_dma_ring_ctrl *ctrl = mei_dma_ring_ctrl(dev);
	u32 dbuf_depth;
	u32 rd_idx, rem, slots;

	अगर (WARN_ON(!ctrl))
		वापस;

	dev_dbg(dev->dev, "reading from dma %u bytes\n", len);

	अगर (!len)
		वापस;

	dbuf_depth = dev->dr_dscr[DMA_DSCR_DEVICE].size >> 2;
	rd_idx = READ_ONCE(ctrl->dbuf_rd_idx) & (dbuf_depth - 1);
	slots = mei_data2slots(len);

	/* अगर buf is शून्य we drop the packet by advancing the poपूर्णांकer.*/
	अगर (!buf)
		जाओ out;

	अगर (rd_idx + slots > dbuf_depth) अणु
		buf += mei_dma_copy_from(dev, buf, rd_idx, dbuf_depth - rd_idx);
		rem = slots - (dbuf_depth - rd_idx);
		rd_idx = 0;
	पूर्ण अन्यथा अणु
		rem = slots;
	पूर्ण

	mei_dma_copy_from(dev, buf, rd_idx, rem);
out:
	WRITE_ONCE(ctrl->dbuf_rd_idx, ctrl->dbuf_rd_idx + slots);
पूर्ण

अटल अंतरभूत u32 mei_dma_ring_hbuf_depth(काष्ठा mei_device *dev)
अणु
	वापस dev->dr_dscr[DMA_DSCR_HOST].size >> 2;
पूर्ण

/**
 * mei_dma_ring_empty_slots() - calaculate number of empty slots in dma ring
 * @dev: mei_device
 *
 * Return: number of empty slots
 */
u32 mei_dma_ring_empty_slots(काष्ठा mei_device *dev)
अणु
	काष्ठा hbm_dma_ring_ctrl *ctrl = mei_dma_ring_ctrl(dev);
	u32 wr_idx, rd_idx, hbuf_depth, empty;

	अगर (!mei_dma_ring_is_allocated(dev))
		वापस 0;

	अगर (WARN_ON(!ctrl))
		वापस 0;

	/* easier to work in slots */
	hbuf_depth = mei_dma_ring_hbuf_depth(dev);
	rd_idx = READ_ONCE(ctrl->hbuf_rd_idx);
	wr_idx = READ_ONCE(ctrl->hbuf_wr_idx);

	अगर (rd_idx > wr_idx)
		empty = rd_idx - wr_idx;
	अन्यथा
		empty = hbuf_depth - (wr_idx - rd_idx);

	वापस empty;
पूर्ण

/**
 * mei_dma_ring_ग_लिखो - ग_लिखो data to dma ring host buffer
 *
 * @dev: mei_device
 * @buf: data will be written
 * @len: data length
 */
व्योम mei_dma_ring_ग_लिखो(काष्ठा mei_device *dev, अचिन्हित अक्षर *buf, u32 len)
अणु
	काष्ठा hbm_dma_ring_ctrl *ctrl = mei_dma_ring_ctrl(dev);
	u32 hbuf_depth;
	u32 wr_idx, rem, slots;

	अगर (WARN_ON(!ctrl))
		वापस;

	dev_dbg(dev->dev, "writing to dma %u bytes\n", len);
	hbuf_depth = mei_dma_ring_hbuf_depth(dev);
	wr_idx = READ_ONCE(ctrl->hbuf_wr_idx) & (hbuf_depth - 1);
	slots = mei_data2slots(len);

	अगर (wr_idx + slots > hbuf_depth) अणु
		buf += mei_dma_copy_to(dev, buf, wr_idx, hbuf_depth - wr_idx);
		rem = slots - (hbuf_depth - wr_idx);
		wr_idx = 0;
	पूर्ण अन्यथा अणु
		rem = slots;
	पूर्ण

	mei_dma_copy_to(dev, buf, wr_idx, rem);

	WRITE_ONCE(ctrl->hbuf_wr_idx, ctrl->hbuf_wr_idx + slots);
पूर्ण
