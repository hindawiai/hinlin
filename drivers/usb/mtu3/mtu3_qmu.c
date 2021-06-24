<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * mtu3_qmu.c - Queue Management Unit driver क्रम device controller
 *
 * Copyright (C) 2016 MediaTek Inc.
 *
 * Author: Chunfeng Yun <chunfeng.yun@mediatek.com>
 */

/*
 * Queue Management Unit (QMU) is deचिन्हित to unload SW efक्रमt
 * to serve DMA पूर्णांकerrupts.
 * By preparing General Purpose Descriptor (GPD) and Buffer Descriptor (BD),
 * SW links data buffers and triggers QMU to send / receive data to
 * host / from device at a समय.
 * And now only GPD is supported.
 *
 * For more detailed inक्रमmation, please refer to QMU Programming Guide
 */

#समावेश <linux/dmapool.h>
#समावेश <linux/iopoll.h>

#समावेश "mtu3.h"
#समावेश "mtu3_trace.h"

#घोषणा QMU_CHECKSUM_LEN	16

#घोषणा GPD_FLAGS_HWO	BIT(0)
#घोषणा GPD_FLAGS_BDP	BIT(1)
#घोषणा GPD_FLAGS_BPS	BIT(2)
#घोषणा GPD_FLAGS_ZLP	BIT(6)
#घोषणा GPD_FLAGS_IOC	BIT(7)
#घोषणा GET_GPD_HWO(gpd)	(le32_to_cpu((gpd)->dw0_info) & GPD_FLAGS_HWO)

#घोषणा GPD_RX_BUF_LEN_OG(x)	(((x) & 0xffff) << 16)
#घोषणा GPD_RX_BUF_LEN_EL(x)	(((x) & 0xfffff) << 12)
#घोषणा GPD_RX_BUF_LEN(mtu, x)	\
(अणु				\
	typeof(x) x_ = (x);	\
	((mtu)->gen2cp) ? GPD_RX_BUF_LEN_EL(x_) : GPD_RX_BUF_LEN_OG(x_); \
पूर्ण)

#घोषणा GPD_DATA_LEN_OG(x)	((x) & 0xffff)
#घोषणा GPD_DATA_LEN_EL(x)	((x) & 0xfffff)
#घोषणा GPD_DATA_LEN(mtu, x)	\
(अणु				\
	typeof(x) x_ = (x);	\
	((mtu)->gen2cp) ? GPD_DATA_LEN_EL(x_) : GPD_DATA_LEN_OG(x_); \
पूर्ण)

#घोषणा GPD_EXT_FLAG_ZLP	BIT(29)
#घोषणा GPD_EXT_NGP_OG(x)	(((x) & 0xf) << 20)
#घोषणा GPD_EXT_BUF_OG(x)	(((x) & 0xf) << 16)
#घोषणा GPD_EXT_NGP_EL(x)	(((x) & 0xf) << 28)
#घोषणा GPD_EXT_BUF_EL(x)	(((x) & 0xf) << 24)
#घोषणा GPD_EXT_NGP(mtu, x)	\
(अणु				\
	typeof(x) x_ = (x);	\
	((mtu)->gen2cp) ? GPD_EXT_NGP_EL(x_) : GPD_EXT_NGP_OG(x_); \
पूर्ण)

#घोषणा GPD_EXT_BUF(mtu, x)	\
(अणु				\
	typeof(x) x_ = (x);	\
	((mtu)->gen2cp) ? GPD_EXT_BUF_EL(x_) : GPD_EXT_BUF_OG(x_); \
पूर्ण)

#घोषणा HILO_GEN64(hi, lo) (((u64)(hi) << 32) + (lo))
#घोषणा HILO_DMA(hi, lo)	\
	((dma_addr_t)HILO_GEN64((le32_to_cpu(hi)), (le32_to_cpu(lo))))

अटल dma_addr_t पढ़ो_txq_cur_addr(व्योम __iomem *mbase, u8 epnum)
अणु
	u32 txcpr;
	u32 txhiar;

	txcpr = mtu3_पढ़ोl(mbase, USB_QMU_TQCPR(epnum));
	txhiar = mtu3_पढ़ोl(mbase, USB_QMU_TQHIAR(epnum));

	वापस HILO_DMA(QMU_CUR_GPD_ADDR_HI(txhiar), txcpr);
पूर्ण

अटल dma_addr_t पढ़ो_rxq_cur_addr(व्योम __iomem *mbase, u8 epnum)
अणु
	u32 rxcpr;
	u32 rxhiar;

	rxcpr = mtu3_पढ़ोl(mbase, USB_QMU_RQCPR(epnum));
	rxhiar = mtu3_पढ़ोl(mbase, USB_QMU_RQHIAR(epnum));

	वापस HILO_DMA(QMU_CUR_GPD_ADDR_HI(rxhiar), rxcpr);
पूर्ण

अटल व्योम ग_लिखो_txq_start_addr(व्योम __iomem *mbase, u8 epnum, dma_addr_t dma)
अणु
	u32 tqhiar;

	mtu3_ग_लिखोl(mbase, USB_QMU_TQSAR(epnum),
		    cpu_to_le32(lower_32_bits(dma)));
	tqhiar = mtu3_पढ़ोl(mbase, USB_QMU_TQHIAR(epnum));
	tqhiar &= ~QMU_START_ADDR_HI_MSK;
	tqhiar |= QMU_START_ADDR_HI(upper_32_bits(dma));
	mtu3_ग_लिखोl(mbase, USB_QMU_TQHIAR(epnum), tqhiar);
पूर्ण

अटल व्योम ग_लिखो_rxq_start_addr(व्योम __iomem *mbase, u8 epnum, dma_addr_t dma)
अणु
	u32 rqhiar;

	mtu3_ग_लिखोl(mbase, USB_QMU_RQSAR(epnum),
		    cpu_to_le32(lower_32_bits(dma)));
	rqhiar = mtu3_पढ़ोl(mbase, USB_QMU_RQHIAR(epnum));
	rqhiar &= ~QMU_START_ADDR_HI_MSK;
	rqhiar |= QMU_START_ADDR_HI(upper_32_bits(dma));
	mtu3_ग_लिखोl(mbase, USB_QMU_RQHIAR(epnum), rqhiar);
पूर्ण

अटल काष्ठा qmu_gpd *gpd_dma_to_virt(काष्ठा mtu3_gpd_ring *ring,
		dma_addr_t dma_addr)
अणु
	dma_addr_t dma_base = ring->dma;
	काष्ठा qmu_gpd *gpd_head = ring->start;
	u32 offset = (dma_addr - dma_base) / माप(*gpd_head);

	अगर (offset >= MAX_GPD_NUM)
		वापस शून्य;

	वापस gpd_head + offset;
पूर्ण

अटल dma_addr_t gpd_virt_to_dma(काष्ठा mtu3_gpd_ring *ring,
		काष्ठा qmu_gpd *gpd)
अणु
	dma_addr_t dma_base = ring->dma;
	काष्ठा qmu_gpd *gpd_head = ring->start;
	u32 offset;

	offset = gpd - gpd_head;
	अगर (offset >= MAX_GPD_NUM)
		वापस 0;

	वापस dma_base + (offset * माप(*gpd));
पूर्ण

अटल व्योम gpd_ring_init(काष्ठा mtu3_gpd_ring *ring, काष्ठा qmu_gpd *gpd)
अणु
	ring->start = gpd;
	ring->enqueue = gpd;
	ring->dequeue = gpd;
	ring->end = gpd + MAX_GPD_NUM - 1;
पूर्ण

अटल व्योम reset_gpd_list(काष्ठा mtu3_ep *mep)
अणु
	काष्ठा mtu3_gpd_ring *ring = &mep->gpd_ring;
	काष्ठा qmu_gpd *gpd = ring->start;

	अगर (gpd) अणु
		gpd->dw0_info &= cpu_to_le32(~GPD_FLAGS_HWO);
		gpd_ring_init(ring, gpd);
	पूर्ण
पूर्ण

पूर्णांक mtu3_gpd_ring_alloc(काष्ठा mtu3_ep *mep)
अणु
	काष्ठा qmu_gpd *gpd;
	काष्ठा mtu3_gpd_ring *ring = &mep->gpd_ring;

	/* software own all gpds as शेष */
	gpd = dma_pool_zalloc(mep->mtu->qmu_gpd_pool, GFP_ATOMIC, &ring->dma);
	अगर (gpd == शून्य)
		वापस -ENOMEM;

	gpd_ring_init(ring, gpd);

	वापस 0;
पूर्ण

व्योम mtu3_gpd_ring_मुक्त(काष्ठा mtu3_ep *mep)
अणु
	काष्ठा mtu3_gpd_ring *ring = &mep->gpd_ring;

	dma_pool_मुक्त(mep->mtu->qmu_gpd_pool,
			ring->start, ring->dma);
	स_रखो(ring, 0, माप(*ring));
पूर्ण

व्योम mtu3_qmu_resume(काष्ठा mtu3_ep *mep)
अणु
	काष्ठा mtu3 *mtu = mep->mtu;
	व्योम __iomem *mbase = mtu->mac_base;
	पूर्णांक epnum = mep->epnum;
	u32 offset;

	offset = mep->is_in ? USB_QMU_TQCSR(epnum) : USB_QMU_RQCSR(epnum);

	mtu3_ग_लिखोl(mbase, offset, QMU_Q_RESUME);
	अगर (!(mtu3_पढ़ोl(mbase, offset) & QMU_Q_ACTIVE))
		mtu3_ग_लिखोl(mbase, offset, QMU_Q_RESUME);
पूर्ण

अटल काष्ठा qmu_gpd *advance_enq_gpd(काष्ठा mtu3_gpd_ring *ring)
अणु
	अगर (ring->enqueue < ring->end)
		ring->enqueue++;
	अन्यथा
		ring->enqueue = ring->start;

	वापस ring->enqueue;
पूर्ण

अटल काष्ठा qmu_gpd *advance_deq_gpd(काष्ठा mtu3_gpd_ring *ring)
अणु
	अगर (ring->dequeue < ring->end)
		ring->dequeue++;
	अन्यथा
		ring->dequeue = ring->start;

	वापस ring->dequeue;
पूर्ण

/* check अगर a ring is emtpy */
अटल पूर्णांक gpd_ring_empty(काष्ठा mtu3_gpd_ring *ring)
अणु
	काष्ठा qmu_gpd *enq = ring->enqueue;
	काष्ठा qmu_gpd *next;

	अगर (ring->enqueue < ring->end)
		next = enq + 1;
	अन्यथा
		next = ring->start;

	/* one gpd is reserved to simplअगरy gpd preparation */
	वापस next == ring->dequeue;
पूर्ण

पूर्णांक mtu3_prepare_transfer(काष्ठा mtu3_ep *mep)
अणु
	वापस gpd_ring_empty(&mep->gpd_ring);
पूर्ण

अटल पूर्णांक mtu3_prepare_tx_gpd(काष्ठा mtu3_ep *mep, काष्ठा mtu3_request *mreq)
अणु
	काष्ठा qmu_gpd *enq;
	काष्ठा mtu3_gpd_ring *ring = &mep->gpd_ring;
	काष्ठा qmu_gpd *gpd = ring->enqueue;
	काष्ठा usb_request *req = &mreq->request;
	काष्ठा mtu3 *mtu = mep->mtu;
	dma_addr_t enq_dma;
	u32 ext_addr;

	gpd->dw0_info = 0;	/* SW own it */
	gpd->buffer = cpu_to_le32(lower_32_bits(req->dma));
	ext_addr = GPD_EXT_BUF(mtu, upper_32_bits(req->dma));
	gpd->dw3_info = cpu_to_le32(GPD_DATA_LEN(mtu, req->length));

	/* get the next GPD */
	enq = advance_enq_gpd(ring);
	enq_dma = gpd_virt_to_dma(ring, enq);
	dev_dbg(mep->mtu->dev, "TX-EP%d queue gpd=%p, enq=%p, qdma=%pad\n",
		mep->epnum, gpd, enq, &enq_dma);

	enq->dw0_info &= cpu_to_le32(~GPD_FLAGS_HWO);
	gpd->next_gpd = cpu_to_le32(lower_32_bits(enq_dma));
	ext_addr |= GPD_EXT_NGP(mtu, upper_32_bits(enq_dma));
	gpd->dw0_info = cpu_to_le32(ext_addr);

	अगर (req->zero) अणु
		अगर (mtu->gen2cp)
			gpd->dw0_info |= cpu_to_le32(GPD_FLAGS_ZLP);
		अन्यथा
			gpd->dw3_info |= cpu_to_le32(GPD_EXT_FLAG_ZLP);
	पूर्ण

	gpd->dw0_info |= cpu_to_le32(GPD_FLAGS_IOC | GPD_FLAGS_HWO);

	mreq->gpd = gpd;
	trace_mtu3_prepare_gpd(mep, gpd);

	वापस 0;
पूर्ण

अटल पूर्णांक mtu3_prepare_rx_gpd(काष्ठा mtu3_ep *mep, काष्ठा mtu3_request *mreq)
अणु
	काष्ठा qmu_gpd *enq;
	काष्ठा mtu3_gpd_ring *ring = &mep->gpd_ring;
	काष्ठा qmu_gpd *gpd = ring->enqueue;
	काष्ठा usb_request *req = &mreq->request;
	काष्ठा mtu3 *mtu = mep->mtu;
	dma_addr_t enq_dma;
	u32 ext_addr;

	gpd->dw0_info = 0;	/* SW own it */
	gpd->buffer = cpu_to_le32(lower_32_bits(req->dma));
	ext_addr = GPD_EXT_BUF(mtu, upper_32_bits(req->dma));
	gpd->dw0_info = cpu_to_le32(GPD_RX_BUF_LEN(mtu, req->length));

	/* get the next GPD */
	enq = advance_enq_gpd(ring);
	enq_dma = gpd_virt_to_dma(ring, enq);
	dev_dbg(mep->mtu->dev, "RX-EP%d queue gpd=%p, enq=%p, qdma=%pad\n",
		mep->epnum, gpd, enq, &enq_dma);

	enq->dw0_info &= cpu_to_le32(~GPD_FLAGS_HWO);
	gpd->next_gpd = cpu_to_le32(lower_32_bits(enq_dma));
	ext_addr |= GPD_EXT_NGP(mtu, upper_32_bits(enq_dma));
	gpd->dw3_info = cpu_to_le32(ext_addr);
	gpd->dw0_info |= cpu_to_le32(GPD_FLAGS_IOC | GPD_FLAGS_HWO);

	mreq->gpd = gpd;
	trace_mtu3_prepare_gpd(mep, gpd);

	वापस 0;
पूर्ण

व्योम mtu3_insert_gpd(काष्ठा mtu3_ep *mep, काष्ठा mtu3_request *mreq)
अणु

	अगर (mep->is_in)
		mtu3_prepare_tx_gpd(mep, mreq);
	अन्यथा
		mtu3_prepare_rx_gpd(mep, mreq);
पूर्ण

पूर्णांक mtu3_qmu_start(काष्ठा mtu3_ep *mep)
अणु
	काष्ठा mtu3 *mtu = mep->mtu;
	व्योम __iomem *mbase = mtu->mac_base;
	काष्ठा mtu3_gpd_ring *ring = &mep->gpd_ring;
	u8 epnum = mep->epnum;

	अगर (mep->is_in) अणु
		/* set QMU start address */
		ग_लिखो_txq_start_addr(mbase, epnum, ring->dma);
		mtu3_setbits(mbase, MU3D_EP_TXCR0(epnum), TX_DMAREQEN);
		/* send zero length packet according to ZLP flag in GPD */
		mtu3_setbits(mbase, U3D_QCR1, QMU_TX_ZLP(epnum));
		mtu3_ग_लिखोl(mbase, U3D_TQERRIESR0,
				QMU_TX_LEN_ERR(epnum) | QMU_TX_CS_ERR(epnum));

		अगर (mtu3_पढ़ोl(mbase, USB_QMU_TQCSR(epnum)) & QMU_Q_ACTIVE) अणु
			dev_warn(mtu->dev, "Tx %d Active Now!\n", epnum);
			वापस 0;
		पूर्ण
		mtu3_ग_लिखोl(mbase, USB_QMU_TQCSR(epnum), QMU_Q_START);

	पूर्ण अन्यथा अणु
		ग_लिखो_rxq_start_addr(mbase, epnum, ring->dma);
		mtu3_setbits(mbase, MU3D_EP_RXCR0(epnum), RX_DMAREQEN);
		/* करोn't expect ZLP */
		mtu3_clrbits(mbase, U3D_QCR3, QMU_RX_ZLP(epnum));
		/* move to next GPD when receive ZLP */
		mtu3_setbits(mbase, U3D_QCR3, QMU_RX_COZ(epnum));
		mtu3_ग_लिखोl(mbase, U3D_RQERRIESR0,
				QMU_RX_LEN_ERR(epnum) | QMU_RX_CS_ERR(epnum));
		mtu3_ग_लिखोl(mbase, U3D_RQERRIESR1, QMU_RX_ZLP_ERR(epnum));

		अगर (mtu3_पढ़ोl(mbase, USB_QMU_RQCSR(epnum)) & QMU_Q_ACTIVE) अणु
			dev_warn(mtu->dev, "Rx %d Active Now!\n", epnum);
			वापस 0;
		पूर्ण
		mtu3_ग_लिखोl(mbase, USB_QMU_RQCSR(epnum), QMU_Q_START);
	पूर्ण

	वापस 0;
पूर्ण

/* may called in atomic context */
व्योम mtu3_qmu_stop(काष्ठा mtu3_ep *mep)
अणु
	काष्ठा mtu3 *mtu = mep->mtu;
	व्योम __iomem *mbase = mtu->mac_base;
	पूर्णांक epnum = mep->epnum;
	u32 value = 0;
	u32 qcsr;
	पूर्णांक ret;

	qcsr = mep->is_in ? USB_QMU_TQCSR(epnum) : USB_QMU_RQCSR(epnum);

	अगर (!(mtu3_पढ़ोl(mbase, qcsr) & QMU_Q_ACTIVE)) अणु
		dev_dbg(mtu->dev, "%s's qmu is inactive now!\n", mep->name);
		वापस;
	पूर्ण
	mtu3_ग_लिखोl(mbase, qcsr, QMU_Q_STOP);

	ret = पढ़ोl_poll_समयout_atomic(mbase + qcsr, value,
			!(value & QMU_Q_ACTIVE), 1, 1000);
	अगर (ret) अणु
		dev_err(mtu->dev, "stop %s's qmu failed\n", mep->name);
		वापस;
	पूर्ण

	dev_dbg(mtu->dev, "%s's qmu stop now!\n", mep->name);
पूर्ण

व्योम mtu3_qmu_flush(काष्ठा mtu3_ep *mep)
अणु

	dev_dbg(mep->mtu->dev, "%s flush QMU %s\n", __func__,
		((mep->is_in) ? "TX" : "RX"));

	/*Stop QMU */
	mtu3_qmu_stop(mep);
	reset_gpd_list(mep);
पूर्ण

/*
 * QMU can't transfer zero length packet directly (a hardware limit
 * on old SoCs), so when needs to send ZLP, we पूर्णांकentionally trigger
 * a length error पूर्णांकerrupt, and in the ISR sends a ZLP by BMU.
 */
अटल व्योम qmu_tx_zlp_error_handler(काष्ठा mtu3 *mtu, u8 epnum)
अणु
	काष्ठा mtu3_ep *mep = mtu->in_eps + epnum;
	काष्ठा mtu3_gpd_ring *ring = &mep->gpd_ring;
	व्योम __iomem *mbase = mtu->mac_base;
	काष्ठा qmu_gpd *gpd_current = शून्य;
	काष्ठा mtu3_request *mreq;
	dma_addr_t cur_gpd_dma;
	u32 txcsr = 0;
	पूर्णांक ret;

	mreq = next_request(mep);
	अगर (mreq && mreq->request.length != 0)
		वापस;

	cur_gpd_dma = पढ़ो_txq_cur_addr(mbase, epnum);
	gpd_current = gpd_dma_to_virt(ring, cur_gpd_dma);

	अगर (GPD_DATA_LEN(mtu, le32_to_cpu(gpd_current->dw3_info)) != 0) अणु
		dev_err(mtu->dev, "TX EP%d buffer length error(!=0)\n", epnum);
		वापस;
	पूर्ण

	dev_dbg(mtu->dev, "%s send ZLP for req=%p\n", __func__, mreq);
	trace_mtu3_zlp_exp_gpd(mep, gpd_current);

	mtu3_clrbits(mbase, MU3D_EP_TXCR0(mep->epnum), TX_DMAREQEN);

	ret = पढ़ोl_poll_समयout_atomic(mbase + MU3D_EP_TXCR0(mep->epnum),
			txcsr, !(txcsr & TX_FIFOFULL), 1, 1000);
	अगर (ret) अणु
		dev_err(mtu->dev, "%s wait for fifo empty fail\n", __func__);
		वापस;
	पूर्ण
	mtu3_setbits(mbase, MU3D_EP_TXCR0(mep->epnum), TX_TXPKTRDY);

	/* by pass the current GDP */
	gpd_current->dw0_info |= cpu_to_le32(GPD_FLAGS_BPS | GPD_FLAGS_HWO);

	/*enable DMAREQEN, चयन back to QMU mode */
	mtu3_setbits(mbase, MU3D_EP_TXCR0(mep->epnum), TX_DMAREQEN);
	mtu3_qmu_resume(mep);
पूर्ण

/*
 * NOTE: request list maybe is alपढ़ोy empty as following हाल:
 * queue_tx --> qmu_पूर्णांकerrupt(clear पूर्णांकerrupt pending, schedule tasklet)-->
 * queue_tx --> process_tasklet(meanजबतक, the second one is transferred,
 * tasklet process both of them)-->qmu_पूर्णांकerrupt क्रम second one.
 * To aव्योम upper हाल, put qmu_करोne_tx in ISR directly to process it.
 */
अटल व्योम qmu_करोne_tx(काष्ठा mtu3 *mtu, u8 epnum)
अणु
	काष्ठा mtu3_ep *mep = mtu->in_eps + epnum;
	काष्ठा mtu3_gpd_ring *ring = &mep->gpd_ring;
	व्योम __iomem *mbase = mtu->mac_base;
	काष्ठा qmu_gpd *gpd = ring->dequeue;
	काष्ठा qmu_gpd *gpd_current = शून्य;
	काष्ठा usb_request *request = शून्य;
	काष्ठा mtu3_request *mreq;
	dma_addr_t cur_gpd_dma;

	/*transfer phy address got from QMU रेजिस्टर to भव address */
	cur_gpd_dma = पढ़ो_txq_cur_addr(mbase, epnum);
	gpd_current = gpd_dma_to_virt(ring, cur_gpd_dma);

	dev_dbg(mtu->dev, "%s EP%d, last=%p, current=%p, enq=%p\n",
		__func__, epnum, gpd, gpd_current, ring->enqueue);

	जबतक (gpd != gpd_current && !GET_GPD_HWO(gpd)) अणु

		mreq = next_request(mep);

		अगर (mreq == शून्य || mreq->gpd != gpd) अणु
			dev_err(mtu->dev, "no correct TX req is found\n");
			अवरोध;
		पूर्ण

		request = &mreq->request;
		request->actual = GPD_DATA_LEN(mtu, le32_to_cpu(gpd->dw3_info));
		trace_mtu3_complete_gpd(mep, gpd);
		mtu3_req_complete(mep, request, 0);

		gpd = advance_deq_gpd(ring);
	पूर्ण

	dev_dbg(mtu->dev, "%s EP%d, deq=%p, enq=%p, complete\n",
		__func__, epnum, ring->dequeue, ring->enqueue);

पूर्ण

अटल व्योम qmu_करोne_rx(काष्ठा mtu3 *mtu, u8 epnum)
अणु
	काष्ठा mtu3_ep *mep = mtu->out_eps + epnum;
	काष्ठा mtu3_gpd_ring *ring = &mep->gpd_ring;
	व्योम __iomem *mbase = mtu->mac_base;
	काष्ठा qmu_gpd *gpd = ring->dequeue;
	काष्ठा qmu_gpd *gpd_current = शून्य;
	काष्ठा usb_request *req = शून्य;
	काष्ठा mtu3_request *mreq;
	dma_addr_t cur_gpd_dma;

	cur_gpd_dma = पढ़ो_rxq_cur_addr(mbase, epnum);
	gpd_current = gpd_dma_to_virt(ring, cur_gpd_dma);

	dev_dbg(mtu->dev, "%s EP%d, last=%p, current=%p, enq=%p\n",
		__func__, epnum, gpd, gpd_current, ring->enqueue);

	जबतक (gpd != gpd_current && !GET_GPD_HWO(gpd)) अणु

		mreq = next_request(mep);

		अगर (mreq == शून्य || mreq->gpd != gpd) अणु
			dev_err(mtu->dev, "no correct RX req is found\n");
			अवरोध;
		पूर्ण
		req = &mreq->request;

		req->actual = GPD_DATA_LEN(mtu, le32_to_cpu(gpd->dw3_info));
		trace_mtu3_complete_gpd(mep, gpd);
		mtu3_req_complete(mep, req, 0);

		gpd = advance_deq_gpd(ring);
	पूर्ण

	dev_dbg(mtu->dev, "%s EP%d, deq=%p, enq=%p, complete\n",
		__func__, epnum, ring->dequeue, ring->enqueue);
पूर्ण

अटल व्योम qmu_करोne_isr(काष्ठा mtu3 *mtu, u32 करोne_status)
अणु
	पूर्णांक i;

	क्रम (i = 1; i < mtu->num_eps; i++) अणु
		अगर (करोne_status & QMU_RX_DONE_INT(i))
			qmu_करोne_rx(mtu, i);
		अगर (करोne_status & QMU_TX_DONE_INT(i))
			qmu_करोne_tx(mtu, i);
	पूर्ण
पूर्ण

अटल व्योम qmu_exception_isr(काष्ठा mtu3 *mtu, u32 qmu_status)
अणु
	व्योम __iomem *mbase = mtu->mac_base;
	u32 errval;
	पूर्णांक i;

	अगर ((qmu_status & RXQ_CSERR_INT) || (qmu_status & RXQ_LENERR_INT)) अणु
		errval = mtu3_पढ़ोl(mbase, U3D_RQERRIR0);
		क्रम (i = 1; i < mtu->num_eps; i++) अणु
			अगर (errval & QMU_RX_CS_ERR(i))
				dev_err(mtu->dev, "Rx %d CS error!\n", i);

			अगर (errval & QMU_RX_LEN_ERR(i))
				dev_err(mtu->dev, "RX %d Length error\n", i);
		पूर्ण
		mtu3_ग_लिखोl(mbase, U3D_RQERRIR0, errval);
	पूर्ण

	अगर (qmu_status & RXQ_ZLPERR_INT) अणु
		errval = mtu3_पढ़ोl(mbase, U3D_RQERRIR1);
		क्रम (i = 1; i < mtu->num_eps; i++) अणु
			अगर (errval & QMU_RX_ZLP_ERR(i))
				dev_dbg(mtu->dev, "RX EP%d Recv ZLP\n", i);
		पूर्ण
		mtu3_ग_लिखोl(mbase, U3D_RQERRIR1, errval);
	पूर्ण

	अगर ((qmu_status & TXQ_CSERR_INT) || (qmu_status & TXQ_LENERR_INT)) अणु
		errval = mtu3_पढ़ोl(mbase, U3D_TQERRIR0);
		क्रम (i = 1; i < mtu->num_eps; i++) अणु
			अगर (errval & QMU_TX_CS_ERR(i))
				dev_err(mtu->dev, "Tx %d checksum error!\n", i);

			अगर (errval & QMU_TX_LEN_ERR(i))
				qmu_tx_zlp_error_handler(mtu, i);
		पूर्ण
		mtu3_ग_लिखोl(mbase, U3D_TQERRIR0, errval);
	पूर्ण
पूर्ण

irqवापस_t mtu3_qmu_isr(काष्ठा mtu3 *mtu)
अणु
	व्योम __iomem *mbase = mtu->mac_base;
	u32 qmu_status;
	u32 qmu_करोne_status;

	/* U3D_QISAR1 is पढ़ो update */
	qmu_status = mtu3_पढ़ोl(mbase, U3D_QISAR1);
	qmu_status &= mtu3_पढ़ोl(mbase, U3D_QIER1);

	qmu_करोne_status = mtu3_पढ़ोl(mbase, U3D_QISAR0);
	qmu_करोne_status &= mtu3_पढ़ोl(mbase, U3D_QIER0);
	mtu3_ग_लिखोl(mbase, U3D_QISAR0, qmu_करोne_status); /* W1C */
	dev_dbg(mtu->dev, "=== QMUdone[tx=%x, rx=%x] QMUexp[%x] ===\n",
		(qmu_करोne_status & 0xFFFF), qmu_करोne_status >> 16,
		qmu_status);
	trace_mtu3_qmu_isr(qmu_करोne_status, qmu_status);

	अगर (qmu_करोne_status)
		qmu_करोne_isr(mtu, qmu_करोne_status);

	अगर (qmu_status)
		qmu_exception_isr(mtu, qmu_status);

	वापस IRQ_HANDLED;
पूर्ण

पूर्णांक mtu3_qmu_init(काष्ठा mtu3 *mtu)
अणु

	compileसमय_निश्चित(QMU_GPD_SIZE == 16, "QMU_GPD size SHOULD be 16B");

	mtu->qmu_gpd_pool = dma_pool_create("QMU_GPD", mtu->dev,
			QMU_GPD_RING_SIZE, QMU_GPD_SIZE, 0);

	अगर (!mtu->qmu_gpd_pool)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

व्योम mtu3_qmu_निकास(काष्ठा mtu3 *mtu)
अणु
	dma_pool_destroy(mtu->qmu_gpd_pool);
पूर्ण
