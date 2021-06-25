<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause
/*
 * Copyright (c) 2020, MIPI Alliance, Inc.
 *
 * Author: Nicolas Pitre <npitre@baylibre.com>
 *
 * Note: The I3C HCI v2.0 spec is still in flux. The IBI support is based on
 * v1.x of the spec and v2.0 will likely be split out.
 */

#समावेश <linux/bitfield.h>
#समावेश <linux/device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/i3c/master.h>
#समावेश <linux/पन.स>

#समावेश "hci.h"
#समावेश "cmd.h"
#समावेश "ibi.h"


/*
 * Software Parameter Values (somewhat arb itrary क्रम now).
 * Some of them could be determined at run समय eventually.
 */

#घोषणा XFER_RINGS			1	/* max: 8 */
#घोषणा XFER_RING_ENTRIES		16	/* max: 255 */

#घोषणा IBI_RINGS			1	/* max: 8 */
#घोषणा IBI_STATUS_RING_ENTRIES		32	/* max: 255 */
#घोषणा IBI_CHUNK_CACHELINES		1	/* max: 256 bytes equivalent */
#घोषणा IBI_CHUNK_POOL_SIZE		128	/* max: 1023 */

/*
 * Ring Header Preamble
 */

#घोषणा rhs_reg_पढ़ो(r)		पढ़ोl(hci->RHS_regs + (RHS_##r))
#घोषणा rhs_reg_ग_लिखो(r, v)	ग_लिखोl(v, hci->RHS_regs + (RHS_##r))

#घोषणा RHS_CONTROL			0x00
#घोषणा PREAMBLE_SIZE			GENMASK(31, 24)	/* Preamble Section Size */
#घोषणा HEADER_SIZE			GENMASK(23, 16)	/* Ring Header Size */
#घोषणा MAX_HEADER_COUNT_CAP		GENMASK(7, 4) /* HC Max Header Count */
#घोषणा MAX_HEADER_COUNT		GENMASK(3, 0) /* Driver Max Header Count */

#घोषणा RHS_RHn_OFFSET(n)		(0x04 + (n)*4)

/*
 * Ring Header (Per-Ring Bundle)
 */

#घोषणा rh_reg_पढ़ो(r)		पढ़ोl(rh->regs + (RH_##r))
#घोषणा rh_reg_ग_लिखो(r, v)	ग_लिखोl(v, rh->regs + (RH_##r))

#घोषणा RH_CR_SETUP			0x00	/* Command/Response Ring */
#घोषणा CR_XFER_STRUCT_SIZE		GENMASK(31, 24)
#घोषणा CR_RESP_STRUCT_SIZE		GENMASK(23, 16)
#घोषणा CR_RING_SIZE			GENMASK(8, 0)

#घोषणा RH_IBI_SETUP			0x04
#घोषणा IBI_STATUS_STRUCT_SIZE		GENMASK(31, 24)
#घोषणा IBI_STATUS_RING_SIZE		GENMASK(23, 16)
#घोषणा IBI_DATA_CHUNK_SIZE		GENMASK(12, 10)
#घोषणा IBI_DATA_CHUNK_COUNT		GENMASK(9, 0)

#घोषणा RH_CHUNK_CONTROL			0x08

#घोषणा RH_INTR_STATUS			0x10
#घोषणा RH_INTR_STATUS_ENABLE		0x14
#घोषणा RH_INTR_SIGNAL_ENABLE		0x18
#घोषणा RH_INTR_FORCE			0x1c
#घोषणा INTR_IBI_READY			BIT(12)
#घोषणा INTR_TRANSFER_COMPLETION	BIT(11)
#घोषणा INTR_RING_OP			BIT(10)
#घोषणा INTR_TRANSFER_ERR		BIT(9)
#घोषणा INTR_WARN_INS_STOP_MODE		BIT(7)
#घोषणा INTR_IBI_RING_FULL		BIT(6)
#घोषणा INTR_TRANSFER_ABORT		BIT(5)

#घोषणा RH_RING_STATUS			0x20
#घोषणा RING_STATUS_LOCKED		BIT(3)
#घोषणा RING_STATUS_ABORTED		BIT(2)
#घोषणा RING_STATUS_RUNNING		BIT(1)
#घोषणा RING_STATUS_ENABLED		BIT(0)

#घोषणा RH_RING_CONTROL			0x24
#घोषणा RING_CTRL_ABORT			BIT(2)
#घोषणा RING_CTRL_RUN_STOP		BIT(1)
#घोषणा RING_CTRL_ENABLE		BIT(0)

#घोषणा RH_RING_OPERATION1		0x28
#घोषणा RING_OP1_IBI_DEQ_PTR		GENMASK(23, 16)
#घोषणा RING_OP1_CR_SW_DEQ_PTR		GENMASK(15, 8)
#घोषणा RING_OP1_CR_ENQ_PTR		GENMASK(7, 0)

#घोषणा RH_RING_OPERATION2		0x2c
#घोषणा RING_OP2_IBI_ENQ_PTR		GENMASK(23, 16)
#घोषणा RING_OP2_CR_DEQ_PTR		GENMASK(7, 0)

#घोषणा RH_CMD_RING_BASE_LO		0x30
#घोषणा RH_CMD_RING_BASE_HI		0x34
#घोषणा RH_RESP_RING_BASE_LO		0x38
#घोषणा RH_RESP_RING_BASE_HI		0x3c
#घोषणा RH_IBI_STATUS_RING_BASE_LO	0x40
#घोषणा RH_IBI_STATUS_RING_BASE_HI	0x44
#घोषणा RH_IBI_DATA_RING_BASE_LO	0x48
#घोषणा RH_IBI_DATA_RING_BASE_HI	0x4c

#घोषणा RH_CMD_RING_SG			0x50	/* Ring Scatter Gather Support */
#घोषणा RH_RESP_RING_SG			0x54
#घोषणा RH_IBI_STATUS_RING_SG		0x58
#घोषणा RH_IBI_DATA_RING_SG		0x5c
#घोषणा RING_SG_BLP			BIT(31)	/* Buffer Vs. List Poपूर्णांकer */
#घोषणा RING_SG_LIST_SIZE		GENMASK(15, 0)

/*
 * Data Buffer Descriptor (in memory)
 */

#घोषणा DATA_BUF_BLP			BIT(31)	/* Buffer Vs. List Poपूर्णांकer */
#घोषणा DATA_BUF_IOC			BIT(30)	/* Interrupt on Completion */
#घोषणा DATA_BUF_BLOCK_SIZE		GENMASK(15, 0)


काष्ठा hci_rh_data अणु
	व्योम __iomem *regs;
	व्योम *xfer, *resp, *ibi_status, *ibi_data;
	dma_addr_t xfer_dma, resp_dma, ibi_status_dma, ibi_data_dma;
	अचिन्हित पूर्णांक xfer_entries, ibi_status_entries, ibi_chunks_total;
	अचिन्हित पूर्णांक xfer_काष्ठा_sz, resp_काष्ठा_sz, ibi_status_sz, ibi_chunk_sz;
	अचिन्हित पूर्णांक करोne_ptr, ibi_chunk_ptr;
	काष्ठा hci_xfer **src_xfers;
	spinlock_t lock;
	काष्ठा completion op_करोne;
पूर्ण;

काष्ठा hci_rings_data अणु
	अचिन्हित पूर्णांक total;
	काष्ठा hci_rh_data headers[];
पूर्ण;

काष्ठा hci_dma_dev_ibi_data अणु
	काष्ठा i3c_generic_ibi_pool *pool;
	अचिन्हित पूर्णांक max_len;
पूर्ण;

अटल अंतरभूत u32 lo32(dma_addr_t physaddr)
अणु
	वापस physaddr;
पूर्ण

अटल अंतरभूत u32 hi32(dma_addr_t physaddr)
अणु
	/* trickery to aव्योम compiler warnings on 32-bit build tarमाला_लो */
	अगर (माप(dma_addr_t) > 4) अणु
		u64 hi = physaddr;
		वापस hi >> 32;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम hci_dma_cleanup(काष्ठा i3c_hci *hci)
अणु
	काष्ठा hci_rings_data *rings = hci->io_data;
	काष्ठा hci_rh_data *rh;
	अचिन्हित पूर्णांक i;

	अगर (!rings)
		वापस;

	क्रम (i = 0; i < rings->total; i++) अणु
		rh = &rings->headers[i];

		rh_reg_ग_लिखो(RING_CONTROL, 0);
		rh_reg_ग_लिखो(CR_SETUP, 0);
		rh_reg_ग_लिखो(IBI_SETUP, 0);
		rh_reg_ग_लिखो(INTR_SIGNAL_ENABLE, 0);

		अगर (rh->xfer)
			dma_मुक्त_coherent(&hci->master.dev,
					  rh->xfer_काष्ठा_sz * rh->xfer_entries,
					  rh->xfer, rh->xfer_dma);
		अगर (rh->resp)
			dma_मुक्त_coherent(&hci->master.dev,
					  rh->resp_काष्ठा_sz * rh->xfer_entries,
					  rh->resp, rh->resp_dma);
		kमुक्त(rh->src_xfers);
		अगर (rh->ibi_status)
			dma_मुक्त_coherent(&hci->master.dev,
					  rh->ibi_status_sz * rh->ibi_status_entries,
					  rh->ibi_status, rh->ibi_status_dma);
		अगर (rh->ibi_data_dma)
			dma_unmap_single(&hci->master.dev, rh->ibi_data_dma,
					 rh->ibi_chunk_sz * rh->ibi_chunks_total,
					 DMA_FROM_DEVICE);
		kमुक्त(rh->ibi_data);
	पूर्ण

	rhs_reg_ग_लिखो(CONTROL, 0);

	kमुक्त(rings);
	hci->io_data = शून्य;
पूर्ण

अटल पूर्णांक hci_dma_init(काष्ठा i3c_hci *hci)
अणु
	काष्ठा hci_rings_data *rings;
	काष्ठा hci_rh_data *rh;
	u32 regval;
	अचिन्हित पूर्णांक i, nr_rings, xfers_sz, resps_sz;
	अचिन्हित पूर्णांक ibi_status_ring_sz, ibi_data_ring_sz;
	पूर्णांक ret;

	regval = rhs_reg_पढ़ो(CONTROL);
	nr_rings = FIELD_GET(MAX_HEADER_COUNT_CAP, regval);
	dev_info(&hci->master.dev, "%d DMA rings available\n", nr_rings);
	अगर (unlikely(nr_rings > 8)) अणु
		dev_err(&hci->master.dev, "number of rings should be <= 8\n");
		nr_rings = 8;
	पूर्ण
	अगर (nr_rings > XFER_RINGS)
		nr_rings = XFER_RINGS;
	rings = kzalloc(माप(*rings) + nr_rings * माप(*rh), GFP_KERNEL);
	अगर (!rings)
		वापस -ENOMEM;
	hci->io_data = rings;
	rings->total = nr_rings;

	क्रम (i = 0; i < rings->total; i++) अणु
		u32 offset = rhs_reg_पढ़ो(RHn_OFFSET(i));

		dev_info(&hci->master.dev, "Ring %d at offset %#x\n", i, offset);
		ret = -EINVAL;
		अगर (!offset)
			जाओ err_out;
		rh = &rings->headers[i];
		rh->regs = hci->base_regs + offset;
		spin_lock_init(&rh->lock);
		init_completion(&rh->op_करोne);

		rh->xfer_entries = XFER_RING_ENTRIES;

		regval = rh_reg_पढ़ो(CR_SETUP);
		rh->xfer_काष्ठा_sz = FIELD_GET(CR_XFER_STRUCT_SIZE, regval);
		rh->resp_काष्ठा_sz = FIELD_GET(CR_RESP_STRUCT_SIZE, regval);
		DBG("xfer_struct_sz = %d, resp_struct_sz = %d",
		    rh->xfer_काष्ठा_sz, rh->resp_काष्ठा_sz);
		xfers_sz = rh->xfer_काष्ठा_sz * rh->xfer_entries;
		resps_sz = rh->resp_काष्ठा_sz * rh->xfer_entries;

		rh->xfer = dma_alloc_coherent(&hci->master.dev, xfers_sz,
					      &rh->xfer_dma, GFP_KERNEL);
		rh->resp = dma_alloc_coherent(&hci->master.dev, resps_sz,
					      &rh->resp_dma, GFP_KERNEL);
		rh->src_xfers =
			kदो_स्मृति_array(rh->xfer_entries, माप(*rh->src_xfers),
				      GFP_KERNEL);
		ret = -ENOMEM;
		अगर (!rh->xfer || !rh->resp || !rh->src_xfers)
			जाओ err_out;

		rh_reg_ग_लिखो(CMD_RING_BASE_LO, lo32(rh->xfer_dma));
		rh_reg_ग_लिखो(CMD_RING_BASE_HI, hi32(rh->xfer_dma));
		rh_reg_ग_लिखो(RESP_RING_BASE_LO, lo32(rh->resp_dma));
		rh_reg_ग_लिखो(RESP_RING_BASE_HI, hi32(rh->resp_dma));

		regval = FIELD_PREP(CR_RING_SIZE, rh->xfer_entries);
		rh_reg_ग_लिखो(CR_SETUP, regval);

		rh_reg_ग_लिखो(INTR_STATUS_ENABLE, 0xffffffff);
		rh_reg_ग_लिखो(INTR_SIGNAL_ENABLE, INTR_IBI_READY |
						 INTR_TRANSFER_COMPLETION |
						 INTR_RING_OP |
						 INTR_TRANSFER_ERR |
						 INTR_WARN_INS_STOP_MODE |
						 INTR_IBI_RING_FULL |
						 INTR_TRANSFER_ABORT);

		/* IBIs */

		अगर (i >= IBI_RINGS)
			जाओ ring_पढ़ोy;

		regval = rh_reg_पढ़ो(IBI_SETUP);
		rh->ibi_status_sz = FIELD_GET(IBI_STATUS_STRUCT_SIZE, regval);
		rh->ibi_status_entries = IBI_STATUS_RING_ENTRIES;
		rh->ibi_chunks_total = IBI_CHUNK_POOL_SIZE;

		rh->ibi_chunk_sz = dma_get_cache_alignment();
		rh->ibi_chunk_sz *= IBI_CHUNK_CACHELINES;
		BUG_ON(rh->ibi_chunk_sz > 256);

		ibi_status_ring_sz = rh->ibi_status_sz * rh->ibi_status_entries;
		ibi_data_ring_sz = rh->ibi_chunk_sz * rh->ibi_chunks_total;

		rh->ibi_status =
			dma_alloc_coherent(&hci->master.dev, ibi_status_ring_sz,
					   &rh->ibi_status_dma, GFP_KERNEL);
		rh->ibi_data = kदो_स्मृति(ibi_data_ring_sz, GFP_KERNEL);
		ret = -ENOMEM;
		अगर (!rh->ibi_status || !rh->ibi_data)
			जाओ err_out;
		rh->ibi_data_dma =
			dma_map_single(&hci->master.dev, rh->ibi_data,
				       ibi_data_ring_sz, DMA_FROM_DEVICE);
		अगर (dma_mapping_error(&hci->master.dev, rh->ibi_data_dma)) अणु
			rh->ibi_data_dma = 0;
			ret = -ENOMEM;
			जाओ err_out;
		पूर्ण

		regval = FIELD_PREP(IBI_STATUS_RING_SIZE,
				    rh->ibi_status_entries) |
			 FIELD_PREP(IBI_DATA_CHUNK_SIZE,
				    ilog2(rh->ibi_chunk_sz) - 2) |
			 FIELD_PREP(IBI_DATA_CHUNK_COUNT,
				    rh->ibi_chunks_total);
		rh_reg_ग_लिखो(IBI_SETUP, regval);

		regval = rh_reg_पढ़ो(INTR_SIGNAL_ENABLE);
		regval |= INTR_IBI_READY;
		rh_reg_ग_लिखो(INTR_SIGNAL_ENABLE, regval);

ring_पढ़ोy:
		rh_reg_ग_लिखो(RING_CONTROL, RING_CTRL_ENABLE);
	पूर्ण

	regval = FIELD_PREP(MAX_HEADER_COUNT, rings->total);
	rhs_reg_ग_लिखो(CONTROL, regval);
	वापस 0;

err_out:
	hci_dma_cleanup(hci);
	वापस ret;
पूर्ण

अटल व्योम hci_dma_unmap_xfer(काष्ठा i3c_hci *hci,
			       काष्ठा hci_xfer *xfer_list, अचिन्हित पूर्णांक n)
अणु
	काष्ठा hci_xfer *xfer;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < n; i++) अणु
		xfer = xfer_list + i;
		dma_unmap_single(&hci->master.dev,
				 xfer->data_dma, xfer->data_len,
				 xfer->rnw ? DMA_FROM_DEVICE : DMA_TO_DEVICE);
	पूर्ण
पूर्ण

अटल पूर्णांक hci_dma_queue_xfer(काष्ठा i3c_hci *hci,
			      काष्ठा hci_xfer *xfer_list, पूर्णांक n)
अणु
	काष्ठा hci_rings_data *rings = hci->io_data;
	काष्ठा hci_rh_data *rh;
	अचिन्हित पूर्णांक i, ring, enqueue_ptr;
	u32 op1_val, op2_val;

	/* For now we only use ring 0 */
	ring = 0;
	rh = &rings->headers[ring];

	op1_val = rh_reg_पढ़ो(RING_OPERATION1);
	enqueue_ptr = FIELD_GET(RING_OP1_CR_ENQ_PTR, op1_val);
	क्रम (i = 0; i < n; i++) अणु
		काष्ठा hci_xfer *xfer = xfer_list + i;
		u32 *ring_data = rh->xfer + rh->xfer_काष्ठा_sz * enqueue_ptr;

		/* store cmd descriptor */
		*ring_data++ = xfer->cmd_desc[0];
		*ring_data++ = xfer->cmd_desc[1];
		अगर (hci->cmd == &mipi_i3c_hci_cmd_v2) अणु
			*ring_data++ = xfer->cmd_desc[2];
			*ring_data++ = xfer->cmd_desc[3];
		पूर्ण

		/* first word of Data Buffer Descriptor Structure */
		अगर (!xfer->data)
			xfer->data_len = 0;
		*ring_data++ =
			FIELD_PREP(DATA_BUF_BLOCK_SIZE, xfer->data_len) |
			((i == n - 1) ? DATA_BUF_IOC : 0);

		/* 2nd and 3rd words of Data Buffer Descriptor Structure */
		अगर (xfer->data) अणु
			xfer->data_dma =
				dma_map_single(&hci->master.dev,
					       xfer->data,
					       xfer->data_len,
					       xfer->rnw ?
						  DMA_FROM_DEVICE :
						  DMA_TO_DEVICE);
			अगर (dma_mapping_error(&hci->master.dev,
					      xfer->data_dma)) अणु
				hci_dma_unmap_xfer(hci, xfer_list, i);
				वापस -ENOMEM;
			पूर्ण
			*ring_data++ = lo32(xfer->data_dma);
			*ring_data++ = hi32(xfer->data_dma);
		पूर्ण अन्यथा अणु
			*ring_data++ = 0;
			*ring_data++ = 0;
		पूर्ण

		/* remember corresponding xfer काष्ठा */
		rh->src_xfers[enqueue_ptr] = xfer;
		/* remember corresponding ring/entry क्रम this xfer काष्ठाure */
		xfer->ring_number = ring;
		xfer->ring_entry = enqueue_ptr;

		enqueue_ptr = (enqueue_ptr + 1) % rh->xfer_entries;

		/*
		 * We may update the hardware view of the enqueue poपूर्णांकer
		 * only अगर we didn't reach its dequeue poपूर्णांकer.
		 */
		op2_val = rh_reg_पढ़ो(RING_OPERATION2);
		अगर (enqueue_ptr == FIELD_GET(RING_OP2_CR_DEQ_PTR, op2_val)) अणु
			/* the ring is full */
			hci_dma_unmap_xfer(hci, xfer_list, i + 1);
			वापस -EBUSY;
		पूर्ण
	पूर्ण

	/* take care to update the hardware enqueue poपूर्णांकer atomically */
	spin_lock_irq(&rh->lock);
	op1_val = rh_reg_पढ़ो(RING_OPERATION1);
	op1_val &= ~RING_OP1_CR_ENQ_PTR;
	op1_val |= FIELD_PREP(RING_OP1_CR_ENQ_PTR, enqueue_ptr);
	rh_reg_ग_लिखो(RING_OPERATION1, op1_val);
	spin_unlock_irq(&rh->lock);

	वापस 0;
पूर्ण

अटल bool hci_dma_dequeue_xfer(काष्ठा i3c_hci *hci,
				 काष्ठा hci_xfer *xfer_list, पूर्णांक n)
अणु
	काष्ठा hci_rings_data *rings = hci->io_data;
	काष्ठा hci_rh_data *rh = &rings->headers[xfer_list[0].ring_number];
	अचिन्हित पूर्णांक i;
	bool did_unqueue = false;

	/* stop the ring */
	rh_reg_ग_लिखो(RING_CONTROL, RING_CTRL_ABORT);
	अगर (रुको_क्रम_completion_समयout(&rh->op_करोne, HZ) == 0) अणु
		/*
		 * We're deep in it अगर ever this condition is ever met.
		 * Hardware might still be writing to memory, etc.
		 * Better suspend the world than risking silent corruption.
		 */
		dev_crit(&hci->master.dev, "unable to abort the ring\n");
		BUG();
	पूर्ण

	क्रम (i = 0; i < n; i++) अणु
		काष्ठा hci_xfer *xfer = xfer_list + i;
		पूर्णांक idx = xfer->ring_entry;

		/*
		 * At the समय the पात happened, the xfer might have
		 * completed alपढ़ोy. If not then replace corresponding
		 * descriptor entries with a no-op.
		 */
		अगर (idx >= 0) अणु
			u32 *ring_data = rh->xfer + rh->xfer_काष्ठा_sz * idx;

			/* store no-op cmd descriptor */
			*ring_data++ = FIELD_PREP(CMD_0_ATTR, 0x7);
			*ring_data++ = 0;
			अगर (hci->cmd == &mipi_i3c_hci_cmd_v2) अणु
				*ring_data++ = 0;
				*ring_data++ = 0;
			पूर्ण

			/* disassociate this xfer काष्ठा */
			rh->src_xfers[idx] = शून्य;

			/* and unmap it */
			hci_dma_unmap_xfer(hci, xfer, 1);

			did_unqueue = true;
		पूर्ण
	पूर्ण

	/* restart the ring */
	rh_reg_ग_लिखो(RING_CONTROL, RING_CTRL_ENABLE);

	वापस did_unqueue;
पूर्ण

अटल व्योम hci_dma_xfer_करोne(काष्ठा i3c_hci *hci, काष्ठा hci_rh_data *rh)
अणु
	u32 op1_val, op2_val, resp, *ring_resp;
	अचिन्हित पूर्णांक tid, करोne_ptr = rh->करोne_ptr;
	काष्ठा hci_xfer *xfer;

	क्रम (;;) अणु
		op2_val = rh_reg_पढ़ो(RING_OPERATION2);
		अगर (करोne_ptr == FIELD_GET(RING_OP2_CR_DEQ_PTR, op2_val))
			अवरोध;

		ring_resp = rh->resp + rh->resp_काष्ठा_sz * करोne_ptr;
		resp = *ring_resp;
		tid = RESP_TID(resp);
		DBG("resp = 0x%08x", resp);

		xfer = rh->src_xfers[करोne_ptr];
		अगर (!xfer) अणु
			DBG("orphaned ring entry");
		पूर्ण अन्यथा अणु
			hci_dma_unmap_xfer(hci, xfer, 1);
			xfer->ring_entry = -1;
			xfer->response = resp;
			अगर (tid != xfer->cmd_tid) अणु
				dev_err(&hci->master.dev,
					"response tid=%d when expecting %d\n",
					tid, xfer->cmd_tid);
				/* TODO: करो something about it? */
			पूर्ण
			अगर (xfer->completion)
				complete(xfer->completion);
		पूर्ण

		करोne_ptr = (करोne_ptr + 1) % rh->xfer_entries;
		rh->करोne_ptr = करोne_ptr;
	पूर्ण

	/* take care to update the software dequeue poपूर्णांकer atomically */
	spin_lock(&rh->lock);
	op1_val = rh_reg_पढ़ो(RING_OPERATION1);
	op1_val &= ~RING_OP1_CR_SW_DEQ_PTR;
	op1_val |= FIELD_PREP(RING_OP1_CR_SW_DEQ_PTR, करोne_ptr);
	rh_reg_ग_लिखो(RING_OPERATION1, op1_val);
	spin_unlock(&rh->lock);
पूर्ण

अटल पूर्णांक hci_dma_request_ibi(काष्ठा i3c_hci *hci, काष्ठा i3c_dev_desc *dev,
			       स्थिर काष्ठा i3c_ibi_setup *req)
अणु
	काष्ठा i3c_hci_dev_data *dev_data = i3c_dev_get_master_data(dev);
	काष्ठा i3c_generic_ibi_pool *pool;
	काष्ठा hci_dma_dev_ibi_data *dev_ibi;

	dev_ibi = kदो_स्मृति(माप(*dev_ibi), GFP_KERNEL);
	अगर (!dev_ibi)
		वापस -ENOMEM;
	pool = i3c_generic_ibi_alloc_pool(dev, req);
	अगर (IS_ERR(pool)) अणु
		kमुक्त(dev_ibi);
		वापस PTR_ERR(pool);
	पूर्ण
	dev_ibi->pool = pool;
	dev_ibi->max_len = req->max_payload_len;
	dev_data->ibi_data = dev_ibi;
	वापस 0;
पूर्ण

अटल व्योम hci_dma_मुक्त_ibi(काष्ठा i3c_hci *hci, काष्ठा i3c_dev_desc *dev)
अणु
	काष्ठा i3c_hci_dev_data *dev_data = i3c_dev_get_master_data(dev);
	काष्ठा hci_dma_dev_ibi_data *dev_ibi = dev_data->ibi_data;

	dev_data->ibi_data = शून्य;
	i3c_generic_ibi_मुक्त_pool(dev_ibi->pool);
	kमुक्त(dev_ibi);
पूर्ण

अटल व्योम hci_dma_recycle_ibi_slot(काष्ठा i3c_hci *hci,
				     काष्ठा i3c_dev_desc *dev,
				     काष्ठा i3c_ibi_slot *slot)
अणु
	काष्ठा i3c_hci_dev_data *dev_data = i3c_dev_get_master_data(dev);
	काष्ठा hci_dma_dev_ibi_data *dev_ibi = dev_data->ibi_data;

	i3c_generic_ibi_recycle_slot(dev_ibi->pool, slot);
पूर्ण

अटल व्योम hci_dma_process_ibi(काष्ठा i3c_hci *hci, काष्ठा hci_rh_data *rh)
अणु
	काष्ठा i3c_dev_desc *dev;
	काष्ठा i3c_hci_dev_data *dev_data;
	काष्ठा hci_dma_dev_ibi_data *dev_ibi;
	काष्ठा i3c_ibi_slot *slot;
	u32 op1_val, op2_val, ibi_status_error;
	अचिन्हित पूर्णांक ptr, enq_ptr, deq_ptr;
	अचिन्हित पूर्णांक ibi_size, ibi_chunks, ibi_data_offset, first_part;
	पूर्णांक ibi_addr, last_ptr;
	व्योम *ring_ibi_data;
	dma_addr_t ring_ibi_data_dma;

	op1_val = rh_reg_पढ़ो(RING_OPERATION1);
	deq_ptr = FIELD_GET(RING_OP1_IBI_DEQ_PTR, op1_val);

	op2_val = rh_reg_पढ़ो(RING_OPERATION2);
	enq_ptr = FIELD_GET(RING_OP2_IBI_ENQ_PTR, op2_val);

	ibi_status_error = 0;
	ibi_addr = -1;
	ibi_chunks = 0;
	ibi_size = 0;
	last_ptr = -1;

	/* let's find all we can about this IBI */
	क्रम (ptr = deq_ptr; ptr != enq_ptr;
	     ptr = (ptr + 1) % rh->ibi_status_entries) अणु
		u32 ibi_status, *ring_ibi_status;
		अचिन्हित पूर्णांक chunks;

		ring_ibi_status = rh->ibi_status + rh->ibi_status_sz * ptr;
		ibi_status = *ring_ibi_status;
		DBG("status = %#x", ibi_status);

		अगर (ibi_status_error) अणु
			/* we no दीर्घer care */
		पूर्ण अन्यथा अगर (ibi_status & IBI_ERROR) अणु
			ibi_status_error = ibi_status;
		पूर्ण अन्यथा अगर (ibi_addr ==  -1) अणु
			ibi_addr = FIELD_GET(IBI_TARGET_ADDR, ibi_status);
		पूर्ण अन्यथा अगर (ibi_addr != FIELD_GET(IBI_TARGET_ADDR, ibi_status)) अणु
			/* the address changed unexpectedly */
			ibi_status_error = ibi_status;
		पूर्ण

		chunks = FIELD_GET(IBI_CHUNKS, ibi_status);
		ibi_chunks += chunks;
		अगर (!(ibi_status & IBI_LAST_STATUS)) अणु
			ibi_size += chunks * rh->ibi_chunk_sz;
		पूर्ण अन्यथा अणु
			ibi_size += FIELD_GET(IBI_DATA_LENGTH, ibi_status);
			last_ptr = ptr;
			अवरोध;
		पूर्ण
	पूर्ण

	/* validate what we've got */

	अगर (last_ptr == -1) अणु
		/* this IBI sequence is not yet complete */
		DBG("no LAST_STATUS available (e=%d d=%d)", enq_ptr, deq_ptr);
		वापस;
	पूर्ण
	deq_ptr = last_ptr + 1;
	deq_ptr %= rh->ibi_status_entries;

	अगर (ibi_status_error) अणु
		dev_err(&hci->master.dev, "IBI error from %#x\n", ibi_addr);
		जाओ करोne;
	पूर्ण

	/* determine who this is क्रम */
	dev = i3c_hci_addr_to_dev(hci, ibi_addr);
	अगर (!dev) अणु
		dev_err(&hci->master.dev,
			"IBI for unknown device %#x\n", ibi_addr);
		जाओ करोne;
	पूर्ण

	dev_data = i3c_dev_get_master_data(dev);
	dev_ibi = dev_data->ibi_data;
	अगर (ibi_size > dev_ibi->max_len) अणु
		dev_err(&hci->master.dev, "IBI payload too big (%d > %d)\n",
			ibi_size, dev_ibi->max_len);
		जाओ करोne;
	पूर्ण

	/*
	 * This ring model is not suitable क्रम zero-copy processing of IBIs.
	 * We have the data chunk ring wrap-around to deal with, meaning
	 * that the payload might span multiple chunks beginning at the
	 * end of the ring and wrap to the start of the ring. Furthermore
	 * there is no guarantee that those chunks will be released in order
	 * and in a समयly manner by the upper driver. So let's just copy
	 * them to a discrete buffer. In practice they're supposed to be
	 * small anyway.
	 */
	slot = i3c_generic_ibi_get_मुक्त_slot(dev_ibi->pool);
	अगर (!slot) अणु
		dev_err(&hci->master.dev, "no free slot for IBI\n");
		जाओ करोne;
	पूर्ण

	/* copy first part of the payload */
	ibi_data_offset = rh->ibi_chunk_sz * rh->ibi_chunk_ptr;
	ring_ibi_data = rh->ibi_data + ibi_data_offset;
	ring_ibi_data_dma = rh->ibi_data_dma + ibi_data_offset;
	first_part = (rh->ibi_chunks_total - rh->ibi_chunk_ptr)
			* rh->ibi_chunk_sz;
	अगर (first_part > ibi_size)
		first_part = ibi_size;
	dma_sync_single_क्रम_cpu(&hci->master.dev, ring_ibi_data_dma,
				first_part, DMA_FROM_DEVICE);
	स_नकल(slot->data, ring_ibi_data, first_part);

	/* copy second part अगर any */
	अगर (ibi_size > first_part) अणु
		/* we wrap back to the start and copy reमुख्यing data */
		ring_ibi_data = rh->ibi_data;
		ring_ibi_data_dma = rh->ibi_data_dma;
		dma_sync_single_क्रम_cpu(&hci->master.dev, ring_ibi_data_dma,
					ibi_size - first_part, DMA_FROM_DEVICE);
		स_नकल(slot->data + first_part, ring_ibi_data,
		       ibi_size - first_part);
	पूर्ण

	/* submit it */
	slot->dev = dev;
	slot->len = ibi_size;
	i3c_master_queue_ibi(dev, slot);

करोne:
	/* take care to update the ibi dequeue poपूर्णांकer atomically */
	spin_lock(&rh->lock);
	op1_val = rh_reg_पढ़ो(RING_OPERATION1);
	op1_val &= ~RING_OP1_IBI_DEQ_PTR;
	op1_val |= FIELD_PREP(RING_OP1_IBI_DEQ_PTR, deq_ptr);
	rh_reg_ग_लिखो(RING_OPERATION1, op1_val);
	spin_unlock(&rh->lock);

	/* update the chunk poपूर्णांकer */
	rh->ibi_chunk_ptr += ibi_chunks;
	rh->ibi_chunk_ptr %= rh->ibi_chunks_total;

	/* and tell the hardware about मुक्तd chunks */
	rh_reg_ग_लिखो(CHUNK_CONTROL, rh_reg_पढ़ो(CHUNK_CONTROL) + ibi_chunks);
पूर्ण

अटल bool hci_dma_irq_handler(काष्ठा i3c_hci *hci, अचिन्हित पूर्णांक mask)
अणु
	काष्ठा hci_rings_data *rings = hci->io_data;
	अचिन्हित पूर्णांक i;
	bool handled = false;

	क्रम (i = 0; mask && i < 8; i++) अणु
		काष्ठा hci_rh_data *rh;
		u32 status;

		अगर (!(mask & BIT(i)))
			जारी;
		mask &= ~BIT(i);

		rh = &rings->headers[i];
		status = rh_reg_पढ़ो(INTR_STATUS);
		DBG("rh%d status: %#x", i, status);
		अगर (!status)
			जारी;
		rh_reg_ग_लिखो(INTR_STATUS, status);

		अगर (status & INTR_IBI_READY)
			hci_dma_process_ibi(hci, rh);
		अगर (status & (INTR_TRANSFER_COMPLETION | INTR_TRANSFER_ERR))
			hci_dma_xfer_करोne(hci, rh);
		अगर (status & INTR_RING_OP)
			complete(&rh->op_करोne);

		अगर (status & INTR_TRANSFER_ABORT)
			dev_notice_ratelimited(&hci->master.dev,
				"ring %d: Transfer Aborted\n", i);
		अगर (status & INTR_WARN_INS_STOP_MODE)
			dev_warn_ratelimited(&hci->master.dev,
				"ring %d: Inserted Stop on Mode Change\n", i);
		अगर (status & INTR_IBI_RING_FULL)
			dev_err_ratelimited(&hci->master.dev,
				"ring %d: IBI Ring Full Condition\n", i);

		handled = true;
	पूर्ण

	वापस handled;
पूर्ण

स्थिर काष्ठा hci_io_ops mipi_i3c_hci_dma = अणु
	.init			= hci_dma_init,
	.cleanup		= hci_dma_cleanup,
	.queue_xfer		= hci_dma_queue_xfer,
	.dequeue_xfer		= hci_dma_dequeue_xfer,
	.irq_handler		= hci_dma_irq_handler,
	.request_ibi		= hci_dma_request_ibi,
	.मुक्त_ibi		= hci_dma_मुक्त_ibi,
	.recycle_ibi_slot	= hci_dma_recycle_ibi_slot,
पूर्ण;
