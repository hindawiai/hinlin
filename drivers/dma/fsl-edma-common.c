<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// Copyright (c) 2013-2014 Freescale Semiconductor, Inc
// Copyright (c) 2017 Sysam, Angelo Dureghello  <angelo@sysam.it>

#समावेश <linux/dmapool.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/dma-mapping.h>

#समावेश "fsl-edma-common.h"

#घोषणा EDMA_CR			0x00
#घोषणा EDMA_ES			0x04
#घोषणा EDMA_ERQ		0x0C
#घोषणा EDMA_EEI		0x14
#घोषणा EDMA_SERQ		0x1B
#घोषणा EDMA_CERQ		0x1A
#घोषणा EDMA_SEEI		0x19
#घोषणा EDMA_CEEI		0x18
#घोषणा EDMA_CINT		0x1F
#घोषणा EDMA_CERR		0x1E
#घोषणा EDMA_SSRT		0x1D
#घोषणा EDMA_CDNE		0x1C
#घोषणा EDMA_INTR		0x24
#घोषणा EDMA_ERR		0x2C

#घोषणा EDMA64_ERQH		0x08
#घोषणा EDMA64_EEIH		0x10
#घोषणा EDMA64_SERQ		0x18
#घोषणा EDMA64_CERQ		0x19
#घोषणा EDMA64_SEEI		0x1a
#घोषणा EDMA64_CEEI		0x1b
#घोषणा EDMA64_CINT		0x1c
#घोषणा EDMA64_CERR		0x1d
#घोषणा EDMA64_SSRT		0x1e
#घोषणा EDMA64_CDNE		0x1f
#घोषणा EDMA64_INTH		0x20
#घोषणा EDMA64_INTL		0x24
#घोषणा EDMA64_ERRH		0x28
#घोषणा EDMA64_ERRL		0x2c

#घोषणा EDMA_TCD		0x1000

अटल व्योम fsl_edma_enable_request(काष्ठा fsl_edma_chan *fsl_chan)
अणु
	काष्ठा edma_regs *regs = &fsl_chan->edma->regs;
	u32 ch = fsl_chan->vchan.chan.chan_id;

	अगर (fsl_chan->edma->drvdata->version == v1) अणु
		edma_ग_लिखोb(fsl_chan->edma, EDMA_SEEI_SEEI(ch), regs->seei);
		edma_ग_लिखोb(fsl_chan->edma, ch, regs->serq);
	पूर्ण अन्यथा अणु
		/* ColdFire is big endian, and accesses natively
		 * big endian I/O peripherals
		 */
		ioग_लिखो8(EDMA_SEEI_SEEI(ch), regs->seei);
		ioग_लिखो8(ch, regs->serq);
	पूर्ण
पूर्ण

व्योम fsl_edma_disable_request(काष्ठा fsl_edma_chan *fsl_chan)
अणु
	काष्ठा edma_regs *regs = &fsl_chan->edma->regs;
	u32 ch = fsl_chan->vchan.chan.chan_id;

	अगर (fsl_chan->edma->drvdata->version == v1) अणु
		edma_ग_लिखोb(fsl_chan->edma, ch, regs->cerq);
		edma_ग_लिखोb(fsl_chan->edma, EDMA_CEEI_CEEI(ch), regs->ceei);
	पूर्ण अन्यथा अणु
		/* ColdFire is big endian, and accesses natively
		 * big endian I/O peripherals
		 */
		ioग_लिखो8(ch, regs->cerq);
		ioग_लिखो8(EDMA_CEEI_CEEI(ch), regs->ceei);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(fsl_edma_disable_request);

अटल व्योम mux_configure8(काष्ठा fsl_edma_chan *fsl_chan, व्योम __iomem *addr,
			   u32 off, u32 slot, bool enable)
अणु
	u8 val8;

	अगर (enable)
		val8 = EDMAMUX_CHCFG_ENBL | slot;
	अन्यथा
		val8 = EDMAMUX_CHCFG_DIS;

	ioग_लिखो8(val8, addr + off);
पूर्ण

अटल व्योम mux_configure32(काष्ठा fsl_edma_chan *fsl_chan, व्योम __iomem *addr,
			    u32 off, u32 slot, bool enable)
अणु
	u32 val;

	अगर (enable)
		val = EDMAMUX_CHCFG_ENBL << 24 | slot;
	अन्यथा
		val = EDMAMUX_CHCFG_DIS;

	ioग_लिखो32(val, addr + off * 4);
पूर्ण

व्योम fsl_edma_chan_mux(काष्ठा fsl_edma_chan *fsl_chan,
		       अचिन्हित पूर्णांक slot, bool enable)
अणु
	u32 ch = fsl_chan->vchan.chan.chan_id;
	व्योम __iomem *muxaddr;
	अचिन्हित पूर्णांक chans_per_mux, ch_off;
	पूर्णांक endian_dअगरf[4] = अणु3, 1, -1, -3पूर्ण;
	u32 dmamux_nr = fsl_chan->edma->drvdata->dmamuxs;

	chans_per_mux = fsl_chan->edma->n_chans / dmamux_nr;
	ch_off = fsl_chan->vchan.chan.chan_id % chans_per_mux;

	अगर (fsl_chan->edma->drvdata->mux_swap)
		ch_off += endian_dअगरf[ch_off % 4];

	muxaddr = fsl_chan->edma->muxbase[ch / chans_per_mux];
	slot = EDMAMUX_CHCFG_SOURCE(slot);

	अगर (fsl_chan->edma->drvdata->version == v3)
		mux_configure32(fsl_chan, muxaddr, ch_off, slot, enable);
	अन्यथा
		mux_configure8(fsl_chan, muxaddr, ch_off, slot, enable);
पूर्ण
EXPORT_SYMBOL_GPL(fsl_edma_chan_mux);

अटल अचिन्हित पूर्णांक fsl_edma_get_tcd_attr(क्रमागत dma_slave_buswidth addr_width)
अणु
	चयन (addr_width) अणु
	हाल 1:
		वापस EDMA_TCD_ATTR_SSIZE_8BIT | EDMA_TCD_ATTR_DSIZE_8BIT;
	हाल 2:
		वापस EDMA_TCD_ATTR_SSIZE_16BIT | EDMA_TCD_ATTR_DSIZE_16BIT;
	हाल 4:
		वापस EDMA_TCD_ATTR_SSIZE_32BIT | EDMA_TCD_ATTR_DSIZE_32BIT;
	हाल 8:
		वापस EDMA_TCD_ATTR_SSIZE_64BIT | EDMA_TCD_ATTR_DSIZE_64BIT;
	शेष:
		वापस EDMA_TCD_ATTR_SSIZE_32BIT | EDMA_TCD_ATTR_DSIZE_32BIT;
	पूर्ण
पूर्ण

व्योम fsl_edma_मुक्त_desc(काष्ठा virt_dma_desc *vdesc)
अणु
	काष्ठा fsl_edma_desc *fsl_desc;
	पूर्णांक i;

	fsl_desc = to_fsl_edma_desc(vdesc);
	क्रम (i = 0; i < fsl_desc->n_tcds; i++)
		dma_pool_मुक्त(fsl_desc->echan->tcd_pool, fsl_desc->tcd[i].vtcd,
			      fsl_desc->tcd[i].ptcd);
	kमुक्त(fsl_desc);
पूर्ण
EXPORT_SYMBOL_GPL(fsl_edma_मुक्त_desc);

पूर्णांक fsl_edma_terminate_all(काष्ठा dma_chan *chan)
अणु
	काष्ठा fsl_edma_chan *fsl_chan = to_fsl_edma_chan(chan);
	अचिन्हित दीर्घ flags;
	LIST_HEAD(head);

	spin_lock_irqsave(&fsl_chan->vchan.lock, flags);
	fsl_edma_disable_request(fsl_chan);
	fsl_chan->edesc = शून्य;
	fsl_chan->idle = true;
	vchan_get_all_descriptors(&fsl_chan->vchan, &head);
	spin_unlock_irqrestore(&fsl_chan->vchan.lock, flags);
	vchan_dma_desc_मुक्त_list(&fsl_chan->vchan, &head);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(fsl_edma_terminate_all);

पूर्णांक fsl_edma_छोड़ो(काष्ठा dma_chan *chan)
अणु
	काष्ठा fsl_edma_chan *fsl_chan = to_fsl_edma_chan(chan);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&fsl_chan->vchan.lock, flags);
	अगर (fsl_chan->edesc) अणु
		fsl_edma_disable_request(fsl_chan);
		fsl_chan->status = DMA_PAUSED;
		fsl_chan->idle = true;
	पूर्ण
	spin_unlock_irqrestore(&fsl_chan->vchan.lock, flags);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(fsl_edma_छोड़ो);

पूर्णांक fsl_edma_resume(काष्ठा dma_chan *chan)
अणु
	काष्ठा fsl_edma_chan *fsl_chan = to_fsl_edma_chan(chan);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&fsl_chan->vchan.lock, flags);
	अगर (fsl_chan->edesc) अणु
		fsl_edma_enable_request(fsl_chan);
		fsl_chan->status = DMA_IN_PROGRESS;
		fsl_chan->idle = false;
	पूर्ण
	spin_unlock_irqrestore(&fsl_chan->vchan.lock, flags);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(fsl_edma_resume);

अटल व्योम fsl_edma_unprep_slave_dma(काष्ठा fsl_edma_chan *fsl_chan)
अणु
	अगर (fsl_chan->dma_dir != DMA_NONE)
		dma_unmap_resource(fsl_chan->vchan.chan.device->dev,
				   fsl_chan->dma_dev_addr,
				   fsl_chan->dma_dev_size,
				   fsl_chan->dma_dir, 0);
	fsl_chan->dma_dir = DMA_NONE;
पूर्ण

अटल bool fsl_edma_prep_slave_dma(काष्ठा fsl_edma_chan *fsl_chan,
				    क्रमागत dma_transfer_direction dir)
अणु
	काष्ठा device *dev = fsl_chan->vchan.chan.device->dev;
	क्रमागत dma_data_direction dma_dir;
	phys_addr_t addr = 0;
	u32 size = 0;

	चयन (dir) अणु
	हाल DMA_MEM_TO_DEV:
		dma_dir = DMA_FROM_DEVICE;
		addr = fsl_chan->cfg.dst_addr;
		size = fsl_chan->cfg.dst_maxburst;
		अवरोध;
	हाल DMA_DEV_TO_MEM:
		dma_dir = DMA_TO_DEVICE;
		addr = fsl_chan->cfg.src_addr;
		size = fsl_chan->cfg.src_maxburst;
		अवरोध;
	शेष:
		dma_dir = DMA_NONE;
		अवरोध;
	पूर्ण

	/* Alपढ़ोy mapped क्रम this config? */
	अगर (fsl_chan->dma_dir == dma_dir)
		वापस true;

	fsl_edma_unprep_slave_dma(fsl_chan);

	fsl_chan->dma_dev_addr = dma_map_resource(dev, addr, size, dma_dir, 0);
	अगर (dma_mapping_error(dev, fsl_chan->dma_dev_addr))
		वापस false;
	fsl_chan->dma_dev_size = size;
	fsl_chan->dma_dir = dma_dir;

	वापस true;
पूर्ण

पूर्णांक fsl_edma_slave_config(काष्ठा dma_chan *chan,
				 काष्ठा dma_slave_config *cfg)
अणु
	काष्ठा fsl_edma_chan *fsl_chan = to_fsl_edma_chan(chan);

	स_नकल(&fsl_chan->cfg, cfg, माप(*cfg));
	fsl_edma_unprep_slave_dma(fsl_chan);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(fsl_edma_slave_config);

अटल माप_प्रकार fsl_edma_desc_residue(काष्ठा fsl_edma_chan *fsl_chan,
		काष्ठा virt_dma_desc *vdesc, bool in_progress)
अणु
	काष्ठा fsl_edma_desc *edesc = fsl_chan->edesc;
	काष्ठा edma_regs *regs = &fsl_chan->edma->regs;
	u32 ch = fsl_chan->vchan.chan.chan_id;
	क्रमागत dma_transfer_direction dir = edesc->dirn;
	dma_addr_t cur_addr, dma_addr;
	माप_प्रकार len, size;
	पूर्णांक i;

	/* calculate the total size in this desc */
	क्रम (len = i = 0; i < fsl_chan->edesc->n_tcds; i++)
		len += le32_to_cpu(edesc->tcd[i].vtcd->nbytes)
			* le16_to_cpu(edesc->tcd[i].vtcd->biter);

	अगर (!in_progress)
		वापस len;

	अगर (dir == DMA_MEM_TO_DEV)
		cur_addr = edma_पढ़ोl(fsl_chan->edma, &regs->tcd[ch].saddr);
	अन्यथा
		cur_addr = edma_पढ़ोl(fsl_chan->edma, &regs->tcd[ch].daddr);

	/* figure out the finished and calculate the residue */
	क्रम (i = 0; i < fsl_chan->edesc->n_tcds; i++) अणु
		size = le32_to_cpu(edesc->tcd[i].vtcd->nbytes)
			* le16_to_cpu(edesc->tcd[i].vtcd->biter);
		अगर (dir == DMA_MEM_TO_DEV)
			dma_addr = le32_to_cpu(edesc->tcd[i].vtcd->saddr);
		अन्यथा
			dma_addr = le32_to_cpu(edesc->tcd[i].vtcd->daddr);

		len -= size;
		अगर (cur_addr >= dma_addr && cur_addr < dma_addr + size) अणु
			len += dma_addr + size - cur_addr;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस len;
पूर्ण

क्रमागत dma_status fsl_edma_tx_status(काष्ठा dma_chan *chan,
		dma_cookie_t cookie, काष्ठा dma_tx_state *txstate)
अणु
	काष्ठा fsl_edma_chan *fsl_chan = to_fsl_edma_chan(chan);
	काष्ठा virt_dma_desc *vdesc;
	क्रमागत dma_status status;
	अचिन्हित दीर्घ flags;

	status = dma_cookie_status(chan, cookie, txstate);
	अगर (status == DMA_COMPLETE)
		वापस status;

	अगर (!txstate)
		वापस fsl_chan->status;

	spin_lock_irqsave(&fsl_chan->vchan.lock, flags);
	vdesc = vchan_find_desc(&fsl_chan->vchan, cookie);
	अगर (fsl_chan->edesc && cookie == fsl_chan->edesc->vdesc.tx.cookie)
		txstate->residue =
			fsl_edma_desc_residue(fsl_chan, vdesc, true);
	अन्यथा अगर (vdesc)
		txstate->residue =
			fsl_edma_desc_residue(fsl_chan, vdesc, false);
	अन्यथा
		txstate->residue = 0;

	spin_unlock_irqrestore(&fsl_chan->vchan.lock, flags);

	वापस fsl_chan->status;
पूर्ण
EXPORT_SYMBOL_GPL(fsl_edma_tx_status);

अटल व्योम fsl_edma_set_tcd_regs(काष्ठा fsl_edma_chan *fsl_chan,
				  काष्ठा fsl_edma_hw_tcd *tcd)
अणु
	काष्ठा fsl_edma_engine *edma = fsl_chan->edma;
	काष्ठा edma_regs *regs = &fsl_chan->edma->regs;
	u32 ch = fsl_chan->vchan.chan.chan_id;

	/*
	 * TCD parameters are stored in काष्ठा fsl_edma_hw_tcd in little
	 * endian क्रमmat. However, we need to load the TCD रेजिस्टरs in
	 * big- or little-endian obeying the eDMA engine model endian,
	 * and this is perक्रमmed from specअगरic edma_ग_लिखो functions
	 */
	edma_ग_लिखोw(edma, 0,  &regs->tcd[ch].csr);

	edma_ग_लिखोl(edma, (s32)tcd->saddr, &regs->tcd[ch].saddr);
	edma_ग_लिखोl(edma, (s32)tcd->daddr, &regs->tcd[ch].daddr);

	edma_ग_लिखोw(edma, (s16)tcd->attr, &regs->tcd[ch].attr);
	edma_ग_लिखोw(edma, tcd->soff, &regs->tcd[ch].soff);

	edma_ग_लिखोl(edma, (s32)tcd->nbytes, &regs->tcd[ch].nbytes);
	edma_ग_लिखोl(edma, (s32)tcd->slast, &regs->tcd[ch].slast);

	edma_ग_लिखोw(edma, (s16)tcd->citer, &regs->tcd[ch].citer);
	edma_ग_लिखोw(edma, (s16)tcd->biter, &regs->tcd[ch].biter);
	edma_ग_लिखोw(edma, (s16)tcd->करोff, &regs->tcd[ch].करोff);

	edma_ग_लिखोl(edma, (s32)tcd->dlast_sga,
			&regs->tcd[ch].dlast_sga);

	edma_ग_लिखोw(edma, (s16)tcd->csr, &regs->tcd[ch].csr);
पूर्ण

अटल अंतरभूत
व्योम fsl_edma_fill_tcd(काष्ठा fsl_edma_hw_tcd *tcd, u32 src, u32 dst,
		       u16 attr, u16 soff, u32 nbytes, u32 slast, u16 citer,
		       u16 biter, u16 करोff, u32 dlast_sga, bool major_पूर्णांक,
		       bool disable_req, bool enable_sg)
अणु
	u16 csr = 0;

	/*
	 * eDMA hardware SGs require the TCDs to be stored in little
	 * endian क्रमmat irrespective of the रेजिस्टर endian model.
	 * So we put the value in little endian in memory, रुकोing
	 * क्रम fsl_edma_set_tcd_regs करोing the swap.
	 */
	tcd->saddr = cpu_to_le32(src);
	tcd->daddr = cpu_to_le32(dst);

	tcd->attr = cpu_to_le16(attr);

	tcd->soff = cpu_to_le16(soff);

	tcd->nbytes = cpu_to_le32(nbytes);
	tcd->slast = cpu_to_le32(slast);

	tcd->citer = cpu_to_le16(EDMA_TCD_CITER_CITER(citer));
	tcd->करोff = cpu_to_le16(करोff);

	tcd->dlast_sga = cpu_to_le32(dlast_sga);

	tcd->biter = cpu_to_le16(EDMA_TCD_BITER_BITER(biter));
	अगर (major_पूर्णांक)
		csr |= EDMA_TCD_CSR_INT_MAJOR;

	अगर (disable_req)
		csr |= EDMA_TCD_CSR_D_REQ;

	अगर (enable_sg)
		csr |= EDMA_TCD_CSR_E_SG;

	tcd->csr = cpu_to_le16(csr);
पूर्ण

अटल काष्ठा fsl_edma_desc *fsl_edma_alloc_desc(काष्ठा fsl_edma_chan *fsl_chan,
		पूर्णांक sg_len)
अणु
	काष्ठा fsl_edma_desc *fsl_desc;
	पूर्णांक i;

	fsl_desc = kzalloc(काष्ठा_size(fsl_desc, tcd, sg_len), GFP_NOWAIT);
	अगर (!fsl_desc)
		वापस शून्य;

	fsl_desc->echan = fsl_chan;
	fsl_desc->n_tcds = sg_len;
	क्रम (i = 0; i < sg_len; i++) अणु
		fsl_desc->tcd[i].vtcd = dma_pool_alloc(fsl_chan->tcd_pool,
					GFP_NOWAIT, &fsl_desc->tcd[i].ptcd);
		अगर (!fsl_desc->tcd[i].vtcd)
			जाओ err;
	पूर्ण
	वापस fsl_desc;

err:
	जबतक (--i >= 0)
		dma_pool_मुक्त(fsl_chan->tcd_pool, fsl_desc->tcd[i].vtcd,
				fsl_desc->tcd[i].ptcd);
	kमुक्त(fsl_desc);
	वापस शून्य;
पूर्ण

काष्ठा dma_async_tx_descriptor *fsl_edma_prep_dma_cyclic(
		काष्ठा dma_chan *chan, dma_addr_t dma_addr, माप_प्रकार buf_len,
		माप_प्रकार period_len, क्रमागत dma_transfer_direction direction,
		अचिन्हित दीर्घ flags)
अणु
	काष्ठा fsl_edma_chan *fsl_chan = to_fsl_edma_chan(chan);
	काष्ठा fsl_edma_desc *fsl_desc;
	dma_addr_t dma_buf_next;
	पूर्णांक sg_len, i;
	u32 src_addr, dst_addr, last_sg, nbytes;
	u16 soff, करोff, iter;

	अगर (!is_slave_direction(direction))
		वापस शून्य;

	अगर (!fsl_edma_prep_slave_dma(fsl_chan, direction))
		वापस शून्य;

	sg_len = buf_len / period_len;
	fsl_desc = fsl_edma_alloc_desc(fsl_chan, sg_len);
	अगर (!fsl_desc)
		वापस शून्य;
	fsl_desc->iscyclic = true;
	fsl_desc->dirn = direction;

	dma_buf_next = dma_addr;
	अगर (direction == DMA_MEM_TO_DEV) अणु
		fsl_chan->attr =
			fsl_edma_get_tcd_attr(fsl_chan->cfg.dst_addr_width);
		nbytes = fsl_chan->cfg.dst_addr_width *
			fsl_chan->cfg.dst_maxburst;
	पूर्ण अन्यथा अणु
		fsl_chan->attr =
			fsl_edma_get_tcd_attr(fsl_chan->cfg.src_addr_width);
		nbytes = fsl_chan->cfg.src_addr_width *
			fsl_chan->cfg.src_maxburst;
	पूर्ण

	iter = period_len / nbytes;

	क्रम (i = 0; i < sg_len; i++) अणु
		अगर (dma_buf_next >= dma_addr + buf_len)
			dma_buf_next = dma_addr;

		/* get next sg's physical address */
		last_sg = fsl_desc->tcd[(i + 1) % sg_len].ptcd;

		अगर (direction == DMA_MEM_TO_DEV) अणु
			src_addr = dma_buf_next;
			dst_addr = fsl_chan->dma_dev_addr;
			soff = fsl_chan->cfg.dst_addr_width;
			करोff = 0;
		पूर्ण अन्यथा अणु
			src_addr = fsl_chan->dma_dev_addr;
			dst_addr = dma_buf_next;
			soff = 0;
			करोff = fsl_chan->cfg.src_addr_width;
		पूर्ण

		fsl_edma_fill_tcd(fsl_desc->tcd[i].vtcd, src_addr, dst_addr,
				  fsl_chan->attr, soff, nbytes, 0, iter,
				  iter, करोff, last_sg, true, false, true);
		dma_buf_next += period_len;
	पूर्ण

	वापस vchan_tx_prep(&fsl_chan->vchan, &fsl_desc->vdesc, flags);
पूर्ण
EXPORT_SYMBOL_GPL(fsl_edma_prep_dma_cyclic);

काष्ठा dma_async_tx_descriptor *fsl_edma_prep_slave_sg(
		काष्ठा dma_chan *chan, काष्ठा scatterlist *sgl,
		अचिन्हित पूर्णांक sg_len, क्रमागत dma_transfer_direction direction,
		अचिन्हित दीर्घ flags, व्योम *context)
अणु
	काष्ठा fsl_edma_chan *fsl_chan = to_fsl_edma_chan(chan);
	काष्ठा fsl_edma_desc *fsl_desc;
	काष्ठा scatterlist *sg;
	u32 src_addr, dst_addr, last_sg, nbytes;
	u16 soff, करोff, iter;
	पूर्णांक i;

	अगर (!is_slave_direction(direction))
		वापस शून्य;

	अगर (!fsl_edma_prep_slave_dma(fsl_chan, direction))
		वापस शून्य;

	fsl_desc = fsl_edma_alloc_desc(fsl_chan, sg_len);
	अगर (!fsl_desc)
		वापस शून्य;
	fsl_desc->iscyclic = false;
	fsl_desc->dirn = direction;

	अगर (direction == DMA_MEM_TO_DEV) अणु
		fsl_chan->attr =
			fsl_edma_get_tcd_attr(fsl_chan->cfg.dst_addr_width);
		nbytes = fsl_chan->cfg.dst_addr_width *
			fsl_chan->cfg.dst_maxburst;
	पूर्ण अन्यथा अणु
		fsl_chan->attr =
			fsl_edma_get_tcd_attr(fsl_chan->cfg.src_addr_width);
		nbytes = fsl_chan->cfg.src_addr_width *
			fsl_chan->cfg.src_maxburst;
	पूर्ण

	क्रम_each_sg(sgl, sg, sg_len, i) अणु
		/* get next sg's physical address */
		last_sg = fsl_desc->tcd[(i + 1) % sg_len].ptcd;

		अगर (direction == DMA_MEM_TO_DEV) अणु
			src_addr = sg_dma_address(sg);
			dst_addr = fsl_chan->dma_dev_addr;
			soff = fsl_chan->cfg.dst_addr_width;
			करोff = 0;
		पूर्ण अन्यथा अणु
			src_addr = fsl_chan->dma_dev_addr;
			dst_addr = sg_dma_address(sg);
			soff = 0;
			करोff = fsl_chan->cfg.src_addr_width;
		पूर्ण

		iter = sg_dma_len(sg) / nbytes;
		अगर (i < sg_len - 1) अणु
			last_sg = fsl_desc->tcd[(i + 1)].ptcd;
			fsl_edma_fill_tcd(fsl_desc->tcd[i].vtcd, src_addr,
					  dst_addr, fsl_chan->attr, soff,
					  nbytes, 0, iter, iter, करोff, last_sg,
					  false, false, true);
		पूर्ण अन्यथा अणु
			last_sg = 0;
			fsl_edma_fill_tcd(fsl_desc->tcd[i].vtcd, src_addr,
					  dst_addr, fsl_chan->attr, soff,
					  nbytes, 0, iter, iter, करोff, last_sg,
					  true, true, false);
		पूर्ण
	पूर्ण

	वापस vchan_tx_prep(&fsl_chan->vchan, &fsl_desc->vdesc, flags);
पूर्ण
EXPORT_SYMBOL_GPL(fsl_edma_prep_slave_sg);

व्योम fsl_edma_xfer_desc(काष्ठा fsl_edma_chan *fsl_chan)
अणु
	काष्ठा virt_dma_desc *vdesc;

	lockdep_निश्चित_held(&fsl_chan->vchan.lock);

	vdesc = vchan_next_desc(&fsl_chan->vchan);
	अगर (!vdesc)
		वापस;
	fsl_chan->edesc = to_fsl_edma_desc(vdesc);
	fsl_edma_set_tcd_regs(fsl_chan, fsl_chan->edesc->tcd[0].vtcd);
	fsl_edma_enable_request(fsl_chan);
	fsl_chan->status = DMA_IN_PROGRESS;
	fsl_chan->idle = false;
पूर्ण
EXPORT_SYMBOL_GPL(fsl_edma_xfer_desc);

व्योम fsl_edma_issue_pending(काष्ठा dma_chan *chan)
अणु
	काष्ठा fsl_edma_chan *fsl_chan = to_fsl_edma_chan(chan);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&fsl_chan->vchan.lock, flags);

	अगर (unlikely(fsl_chan->pm_state != RUNNING)) अणु
		spin_unlock_irqrestore(&fsl_chan->vchan.lock, flags);
		/* cannot submit due to suspend */
		वापस;
	पूर्ण

	अगर (vchan_issue_pending(&fsl_chan->vchan) && !fsl_chan->edesc)
		fsl_edma_xfer_desc(fsl_chan);

	spin_unlock_irqrestore(&fsl_chan->vchan.lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(fsl_edma_issue_pending);

पूर्णांक fsl_edma_alloc_chan_resources(काष्ठा dma_chan *chan)
अणु
	काष्ठा fsl_edma_chan *fsl_chan = to_fsl_edma_chan(chan);

	fsl_chan->tcd_pool = dma_pool_create("tcd_pool", chan->device->dev,
				माप(काष्ठा fsl_edma_hw_tcd),
				32, 0);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(fsl_edma_alloc_chan_resources);

व्योम fsl_edma_मुक्त_chan_resources(काष्ठा dma_chan *chan)
अणु
	काष्ठा fsl_edma_chan *fsl_chan = to_fsl_edma_chan(chan);
	अचिन्हित दीर्घ flags;
	LIST_HEAD(head);

	spin_lock_irqsave(&fsl_chan->vchan.lock, flags);
	fsl_edma_disable_request(fsl_chan);
	fsl_edma_chan_mux(fsl_chan, 0, false);
	fsl_chan->edesc = शून्य;
	vchan_get_all_descriptors(&fsl_chan->vchan, &head);
	fsl_edma_unprep_slave_dma(fsl_chan);
	spin_unlock_irqrestore(&fsl_chan->vchan.lock, flags);

	vchan_dma_desc_मुक्त_list(&fsl_chan->vchan, &head);
	dma_pool_destroy(fsl_chan->tcd_pool);
	fsl_chan->tcd_pool = शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(fsl_edma_मुक्त_chan_resources);

व्योम fsl_edma_cleanup_vchan(काष्ठा dma_device *dmadev)
अणु
	काष्ठा fsl_edma_chan *chan, *_chan;

	list_क्रम_each_entry_safe(chan, _chan,
				&dmadev->channels, vchan.chan.device_node) अणु
		list_del(&chan->vchan.chan.device_node);
		tasklet_समाप्त(&chan->vchan.task);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(fsl_edma_cleanup_vchan);

/*
 * On the 32 channels Vybrid/mpc577x edma version (here called "v1"),
 * रेजिस्टर offsets are dअगरferent compared to ColdFire mcf5441x 64 channels
 * edma (here called "v2").
 *
 * This function sets up रेजिस्टर offsets as per proper declared version
 * so must be called in xxx_edma_probe() just after setting the
 * edma "version" and "membase" appropriately.
 */
व्योम fsl_edma_setup_regs(काष्ठा fsl_edma_engine *edma)
अणु
	edma->regs.cr = edma->membase + EDMA_CR;
	edma->regs.es = edma->membase + EDMA_ES;
	edma->regs.erql = edma->membase + EDMA_ERQ;
	edma->regs.eeil = edma->membase + EDMA_EEI;

	edma->regs.serq = edma->membase + ((edma->drvdata->version == v2) ?
			EDMA64_SERQ : EDMA_SERQ);
	edma->regs.cerq = edma->membase + ((edma->drvdata->version == v2) ?
			EDMA64_CERQ : EDMA_CERQ);
	edma->regs.seei = edma->membase + ((edma->drvdata->version == v2) ?
			EDMA64_SEEI : EDMA_SEEI);
	edma->regs.ceei = edma->membase + ((edma->drvdata->version == v2) ?
			EDMA64_CEEI : EDMA_CEEI);
	edma->regs.cपूर्णांक = edma->membase + ((edma->drvdata->version == v2) ?
			EDMA64_CINT : EDMA_CINT);
	edma->regs.cerr = edma->membase + ((edma->drvdata->version == v2) ?
			EDMA64_CERR : EDMA_CERR);
	edma->regs.ssrt = edma->membase + ((edma->drvdata->version == v2) ?
			EDMA64_SSRT : EDMA_SSRT);
	edma->regs.cdne = edma->membase + ((edma->drvdata->version == v2) ?
			EDMA64_CDNE : EDMA_CDNE);
	edma->regs.पूर्णांकl = edma->membase + ((edma->drvdata->version == v2) ?
			EDMA64_INTL : EDMA_INTR);
	edma->regs.errl = edma->membase + ((edma->drvdata->version == v2) ?
			EDMA64_ERRL : EDMA_ERR);

	अगर (edma->drvdata->version == v2) अणु
		edma->regs.erqh = edma->membase + EDMA64_ERQH;
		edma->regs.eeih = edma->membase + EDMA64_EEIH;
		edma->regs.errh = edma->membase + EDMA64_ERRH;
		edma->regs.पूर्णांकh = edma->membase + EDMA64_INTH;
	पूर्ण

	edma->regs.tcd = edma->membase + EDMA_TCD;
पूर्ण
EXPORT_SYMBOL_GPL(fsl_edma_setup_regs);

MODULE_LICENSE("GPL v2");
