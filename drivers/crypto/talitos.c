<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * talitos - Freescale Integrated Security Engine (SEC) device driver
 *
 * Copyright (c) 2008-2011 Freescale Semiconductor, Inc.
 *
 * Scatterlist Crypto API glue code copied from files with the following:
 * Copyright (c) 2006-2007 Herbert Xu <herbert@gonकरोr.apana.org.au>
 *
 * Crypto algorithm registration code copied from hअगरn driver:
 * 2007+ Copyright (c) Evgeniy Polyakov <johnpol@2ka.mipt.ru>
 * All rights reserved.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/crypto.h>
#समावेश <linux/hw_अक्रमom.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/पन.स>
#समावेश <linux/spinlock.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/slab.h>

#समावेश <crypto/algapi.h>
#समावेश <crypto/aes.h>
#समावेश <crypto/पूर्णांकernal/des.h>
#समावेश <crypto/sha1.h>
#समावेश <crypto/sha2.h>
#समावेश <crypto/md5.h>
#समावेश <crypto/पूर्णांकernal/aead.h>
#समावेश <crypto/authenc.h>
#समावेश <crypto/पूर्णांकernal/skcipher.h>
#समावेश <crypto/hash.h>
#समावेश <crypto/पूर्णांकernal/hash.h>
#समावेश <crypto/scatterwalk.h>

#समावेश "talitos.h"

अटल व्योम to_talitos_ptr(काष्ठा talitos_ptr *ptr, dma_addr_t dma_addr,
			   अचिन्हित पूर्णांक len, bool is_sec1)
अणु
	ptr->ptr = cpu_to_be32(lower_32_bits(dma_addr));
	अगर (is_sec1) अणु
		ptr->len1 = cpu_to_be16(len);
	पूर्ण अन्यथा अणु
		ptr->len = cpu_to_be16(len);
		ptr->eptr = upper_32_bits(dma_addr);
	पूर्ण
पूर्ण

अटल व्योम copy_talitos_ptr(काष्ठा talitos_ptr *dst_ptr,
			     काष्ठा talitos_ptr *src_ptr, bool is_sec1)
अणु
	dst_ptr->ptr = src_ptr->ptr;
	अगर (is_sec1) अणु
		dst_ptr->len1 = src_ptr->len1;
	पूर्ण अन्यथा अणु
		dst_ptr->len = src_ptr->len;
		dst_ptr->eptr = src_ptr->eptr;
	पूर्ण
पूर्ण

अटल अचिन्हित लघु from_talitos_ptr_len(काष्ठा talitos_ptr *ptr,
					   bool is_sec1)
अणु
	अगर (is_sec1)
		वापस be16_to_cpu(ptr->len1);
	अन्यथा
		वापस be16_to_cpu(ptr->len);
पूर्ण

अटल व्योम to_talitos_ptr_ext_set(काष्ठा talitos_ptr *ptr, u8 val,
				   bool is_sec1)
अणु
	अगर (!is_sec1)
		ptr->j_extent = val;
पूर्ण

अटल व्योम to_talitos_ptr_ext_or(काष्ठा talitos_ptr *ptr, u8 val, bool is_sec1)
अणु
	अगर (!is_sec1)
		ptr->j_extent |= val;
पूर्ण

/*
 * map भव single (contiguous) poपूर्णांकer to h/w descriptor poपूर्णांकer
 */
अटल व्योम __map_single_talitos_ptr(काष्ठा device *dev,
				     काष्ठा talitos_ptr *ptr,
				     अचिन्हित पूर्णांक len, व्योम *data,
				     क्रमागत dma_data_direction dir,
				     अचिन्हित दीर्घ attrs)
अणु
	dma_addr_t dma_addr = dma_map_single_attrs(dev, data, len, dir, attrs);
	काष्ठा talitos_निजी *priv = dev_get_drvdata(dev);
	bool is_sec1 = has_ftr_sec1(priv);

	to_talitos_ptr(ptr, dma_addr, len, is_sec1);
पूर्ण

अटल व्योम map_single_talitos_ptr(काष्ठा device *dev,
				   काष्ठा talitos_ptr *ptr,
				   अचिन्हित पूर्णांक len, व्योम *data,
				   क्रमागत dma_data_direction dir)
अणु
	__map_single_talitos_ptr(dev, ptr, len, data, dir, 0);
पूर्ण

अटल व्योम map_single_talitos_ptr_nosync(काष्ठा device *dev,
					  काष्ठा talitos_ptr *ptr,
					  अचिन्हित पूर्णांक len, व्योम *data,
					  क्रमागत dma_data_direction dir)
अणु
	__map_single_talitos_ptr(dev, ptr, len, data, dir,
				 DMA_ATTR_SKIP_CPU_SYNC);
पूर्ण

/*
 * unmap bus single (contiguous) h/w descriptor poपूर्णांकer
 */
अटल व्योम unmap_single_talitos_ptr(काष्ठा device *dev,
				     काष्ठा talitos_ptr *ptr,
				     क्रमागत dma_data_direction dir)
अणु
	काष्ठा talitos_निजी *priv = dev_get_drvdata(dev);
	bool is_sec1 = has_ftr_sec1(priv);

	dma_unmap_single(dev, be32_to_cpu(ptr->ptr),
			 from_talitos_ptr_len(ptr, is_sec1), dir);
पूर्ण

अटल पूर्णांक reset_channel(काष्ठा device *dev, पूर्णांक ch)
अणु
	काष्ठा talitos_निजी *priv = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक समयout = TALITOS_TIMEOUT;
	bool is_sec1 = has_ftr_sec1(priv);

	अगर (is_sec1) अणु
		setbits32(priv->chan[ch].reg + TALITOS_CCCR_LO,
			  TALITOS1_CCCR_LO_RESET);

		जबतक ((in_be32(priv->chan[ch].reg + TALITOS_CCCR_LO) &
			TALITOS1_CCCR_LO_RESET) && --समयout)
			cpu_relax();
	पूर्ण अन्यथा अणु
		setbits32(priv->chan[ch].reg + TALITOS_CCCR,
			  TALITOS2_CCCR_RESET);

		जबतक ((in_be32(priv->chan[ch].reg + TALITOS_CCCR) &
			TALITOS2_CCCR_RESET) && --समयout)
			cpu_relax();
	पूर्ण

	अगर (समयout == 0) अणु
		dev_err(dev, "failed to reset channel %d\n", ch);
		वापस -EIO;
	पूर्ण

	/* set 36-bit addressing, करोne ग_लिखोback enable and करोne IRQ enable */
	setbits32(priv->chan[ch].reg + TALITOS_CCCR_LO, TALITOS_CCCR_LO_EAE |
		  TALITOS_CCCR_LO_CDWE | TALITOS_CCCR_LO_CDIE);
	/* enable chaining descriptors */
	अगर (is_sec1)
		setbits32(priv->chan[ch].reg + TALITOS_CCCR_LO,
			  TALITOS_CCCR_LO_NE);

	/* and ICCR ग_लिखोback, अगर available */
	अगर (priv->features & TALITOS_FTR_HW_AUTH_CHECK)
		setbits32(priv->chan[ch].reg + TALITOS_CCCR_LO,
		          TALITOS_CCCR_LO_IWSE);

	वापस 0;
पूर्ण

अटल पूर्णांक reset_device(काष्ठा device *dev)
अणु
	काष्ठा talitos_निजी *priv = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक समयout = TALITOS_TIMEOUT;
	bool is_sec1 = has_ftr_sec1(priv);
	u32 mcr = is_sec1 ? TALITOS1_MCR_SWR : TALITOS2_MCR_SWR;

	setbits32(priv->reg + TALITOS_MCR, mcr);

	जबतक ((in_be32(priv->reg + TALITOS_MCR) & mcr)
	       && --समयout)
		cpu_relax();

	अगर (priv->irq[1]) अणु
		mcr = TALITOS_MCR_RCA1 | TALITOS_MCR_RCA3;
		setbits32(priv->reg + TALITOS_MCR, mcr);
	पूर्ण

	अगर (समयout == 0) अणु
		dev_err(dev, "failed to reset device\n");
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Reset and initialize the device
 */
अटल पूर्णांक init_device(काष्ठा device *dev)
अणु
	काष्ठा talitos_निजी *priv = dev_get_drvdata(dev);
	पूर्णांक ch, err;
	bool is_sec1 = has_ftr_sec1(priv);

	/*
	 * Master reset
	 * errata करोcumentation: warning: certain SEC पूर्णांकerrupts
	 * are not fully cleared by writing the MCR:SWR bit,
	 * set bit twice to completely reset
	 */
	err = reset_device(dev);
	अगर (err)
		वापस err;

	err = reset_device(dev);
	अगर (err)
		वापस err;

	/* reset channels */
	क्रम (ch = 0; ch < priv->num_channels; ch++) अणु
		err = reset_channel(dev, ch);
		अगर (err)
			वापस err;
	पूर्ण

	/* enable channel करोne and error पूर्णांकerrupts */
	अगर (is_sec1) अणु
		clrbits32(priv->reg + TALITOS_IMR, TALITOS1_IMR_INIT);
		clrbits32(priv->reg + TALITOS_IMR_LO, TALITOS1_IMR_LO_INIT);
		/* disable parity error check in DEU (erroneous? test vect.) */
		setbits32(priv->reg_deu + TALITOS_EUICR, TALITOS1_DEUICR_KPE);
	पूर्ण अन्यथा अणु
		setbits32(priv->reg + TALITOS_IMR, TALITOS2_IMR_INIT);
		setbits32(priv->reg + TALITOS_IMR_LO, TALITOS2_IMR_LO_INIT);
	पूर्ण

	/* disable पूर्णांकegrity check error पूर्णांकerrupts (use ग_लिखोback instead) */
	अगर (priv->features & TALITOS_FTR_HW_AUTH_CHECK)
		setbits32(priv->reg_mdeu + TALITOS_EUICR_LO,
		          TALITOS_MDEUICR_LO_ICE);

	वापस 0;
पूर्ण

/**
 * talitos_submit - submits a descriptor to the device क्रम processing
 * @dev:	the SEC device to be used
 * @ch:		the SEC device channel to be used
 * @desc:	the descriptor to be processed by the device
 * @callback:	whom to call when processing is complete
 * @context:	a handle क्रम use by caller (optional)
 *
 * desc must contain valid dma-mapped (bus physical) address poपूर्णांकers.
 * callback must check err and feedback in descriptor header
 * क्रम device processing status.
 */
अटल पूर्णांक talitos_submit(काष्ठा device *dev, पूर्णांक ch, काष्ठा talitos_desc *desc,
			  व्योम (*callback)(काष्ठा device *dev,
					   काष्ठा talitos_desc *desc,
					   व्योम *context, पूर्णांक error),
			  व्योम *context)
अणु
	काष्ठा talitos_निजी *priv = dev_get_drvdata(dev);
	काष्ठा talitos_request *request;
	अचिन्हित दीर्घ flags;
	पूर्णांक head;
	bool is_sec1 = has_ftr_sec1(priv);

	spin_lock_irqsave(&priv->chan[ch].head_lock, flags);

	अगर (!atomic_inc_not_zero(&priv->chan[ch].submit_count)) अणु
		/* h/w fअगरo is full */
		spin_unlock_irqrestore(&priv->chan[ch].head_lock, flags);
		वापस -EAGAIN;
	पूर्ण

	head = priv->chan[ch].head;
	request = &priv->chan[ch].fअगरo[head];

	/* map descriptor and save caller data */
	अगर (is_sec1) अणु
		desc->hdr1 = desc->hdr;
		request->dma_desc = dma_map_single(dev, &desc->hdr1,
						   TALITOS_DESC_SIZE,
						   DMA_BIसूचीECTIONAL);
	पूर्ण अन्यथा अणु
		request->dma_desc = dma_map_single(dev, desc,
						   TALITOS_DESC_SIZE,
						   DMA_BIसूचीECTIONAL);
	पूर्ण
	request->callback = callback;
	request->context = context;

	/* increment fअगरo head */
	priv->chan[ch].head = (priv->chan[ch].head + 1) & (priv->fअगरo_len - 1);

	smp_wmb();
	request->desc = desc;

	/* GO! */
	wmb();
	out_be32(priv->chan[ch].reg + TALITOS_FF,
		 upper_32_bits(request->dma_desc));
	out_be32(priv->chan[ch].reg + TALITOS_FF_LO,
		 lower_32_bits(request->dma_desc));

	spin_unlock_irqrestore(&priv->chan[ch].head_lock, flags);

	वापस -EINPROGRESS;
पूर्ण

अटल __be32 get_request_hdr(काष्ठा talitos_request *request, bool is_sec1)
अणु
	काष्ठा talitos_edesc *edesc;

	अगर (!is_sec1)
		वापस request->desc->hdr;

	अगर (!request->desc->next_desc)
		वापस request->desc->hdr1;

	edesc = container_of(request->desc, काष्ठा talitos_edesc, desc);

	वापस ((काष्ठा talitos_desc *)(edesc->buf + edesc->dma_len))->hdr1;
पूर्ण

/*
 * process what was करोne, notअगरy callback of error अगर not
 */
अटल व्योम flush_channel(काष्ठा device *dev, पूर्णांक ch, पूर्णांक error, पूर्णांक reset_ch)
अणु
	काष्ठा talitos_निजी *priv = dev_get_drvdata(dev);
	काष्ठा talitos_request *request, saved_req;
	अचिन्हित दीर्घ flags;
	पूर्णांक tail, status;
	bool is_sec1 = has_ftr_sec1(priv);

	spin_lock_irqsave(&priv->chan[ch].tail_lock, flags);

	tail = priv->chan[ch].tail;
	जबतक (priv->chan[ch].fअगरo[tail].desc) अणु
		__be32 hdr;

		request = &priv->chan[ch].fअगरo[tail];

		/* descriptors with their करोne bits set करोn't get the error */
		rmb();
		hdr = get_request_hdr(request, is_sec1);

		अगर ((hdr & DESC_HDR_DONE) == DESC_HDR_DONE)
			status = 0;
		अन्यथा
			अगर (!error)
				अवरोध;
			अन्यथा
				status = error;

		dma_unmap_single(dev, request->dma_desc,
				 TALITOS_DESC_SIZE,
				 DMA_BIसूचीECTIONAL);

		/* copy entries so we can call callback outside lock */
		saved_req.desc = request->desc;
		saved_req.callback = request->callback;
		saved_req.context = request->context;

		/* release request entry in fअगरo */
		smp_wmb();
		request->desc = शून्य;

		/* increment fअगरo tail */
		priv->chan[ch].tail = (tail + 1) & (priv->fअगरo_len - 1);

		spin_unlock_irqrestore(&priv->chan[ch].tail_lock, flags);

		atomic_dec(&priv->chan[ch].submit_count);

		saved_req.callback(dev, saved_req.desc, saved_req.context,
				   status);
		/* channel may resume processing in single desc error हाल */
		अगर (error && !reset_ch && status == error)
			वापस;
		spin_lock_irqsave(&priv->chan[ch].tail_lock, flags);
		tail = priv->chan[ch].tail;
	पूर्ण

	spin_unlock_irqrestore(&priv->chan[ch].tail_lock, flags);
पूर्ण

/*
 * process completed requests क्रम channels that have करोne status
 */
#घोषणा DEF_TALITOS1_DONE(name, ch_करोne_mask)				\
अटल व्योम talitos1_करोne_##name(अचिन्हित दीर्घ data)			\
अणु									\
	काष्ठा device *dev = (काष्ठा device *)data;			\
	काष्ठा talitos_निजी *priv = dev_get_drvdata(dev);		\
	अचिन्हित दीर्घ flags;						\
									\
	अगर (ch_करोne_mask & 0x10000000)					\
		flush_channel(dev, 0, 0, 0);			\
	अगर (ch_करोne_mask & 0x40000000)					\
		flush_channel(dev, 1, 0, 0);			\
	अगर (ch_करोne_mask & 0x00010000)					\
		flush_channel(dev, 2, 0, 0);			\
	अगर (ch_करोne_mask & 0x00040000)					\
		flush_channel(dev, 3, 0, 0);			\
									\
	/* At this poपूर्णांक, all completed channels have been processed */	\
	/* Unmask करोne पूर्णांकerrupts क्रम channels completed later on. */	\
	spin_lock_irqsave(&priv->reg_lock, flags);			\
	clrbits32(priv->reg + TALITOS_IMR, ch_करोne_mask);		\
	clrbits32(priv->reg + TALITOS_IMR_LO, TALITOS1_IMR_LO_INIT);	\
	spin_unlock_irqrestore(&priv->reg_lock, flags);			\
पूर्ण

DEF_TALITOS1_DONE(4ch, TALITOS1_ISR_4CHDONE)
DEF_TALITOS1_DONE(ch0, TALITOS1_ISR_CH_0_DONE)

#घोषणा DEF_TALITOS2_DONE(name, ch_करोne_mask)				\
अटल व्योम talitos2_करोne_##name(अचिन्हित दीर्घ data)			\
अणु									\
	काष्ठा device *dev = (काष्ठा device *)data;			\
	काष्ठा talitos_निजी *priv = dev_get_drvdata(dev);		\
	अचिन्हित दीर्घ flags;						\
									\
	अगर (ch_करोne_mask & 1)						\
		flush_channel(dev, 0, 0, 0);				\
	अगर (ch_करोne_mask & (1 << 2))					\
		flush_channel(dev, 1, 0, 0);				\
	अगर (ch_करोne_mask & (1 << 4))					\
		flush_channel(dev, 2, 0, 0);				\
	अगर (ch_करोne_mask & (1 << 6))					\
		flush_channel(dev, 3, 0, 0);				\
									\
	/* At this poपूर्णांक, all completed channels have been processed */	\
	/* Unmask करोne पूर्णांकerrupts क्रम channels completed later on. */	\
	spin_lock_irqsave(&priv->reg_lock, flags);			\
	setbits32(priv->reg + TALITOS_IMR, ch_करोne_mask);		\
	setbits32(priv->reg + TALITOS_IMR_LO, TALITOS2_IMR_LO_INIT);	\
	spin_unlock_irqrestore(&priv->reg_lock, flags);			\
पूर्ण

DEF_TALITOS2_DONE(4ch, TALITOS2_ISR_4CHDONE)
DEF_TALITOS2_DONE(ch0, TALITOS2_ISR_CH_0_DONE)
DEF_TALITOS2_DONE(ch0_2, TALITOS2_ISR_CH_0_2_DONE)
DEF_TALITOS2_DONE(ch1_3, TALITOS2_ISR_CH_1_3_DONE)

/*
 * locate current (offending) descriptor
 */
अटल __be32 current_desc_hdr(काष्ठा device *dev, पूर्णांक ch)
अणु
	काष्ठा talitos_निजी *priv = dev_get_drvdata(dev);
	पूर्णांक tail, iter;
	dma_addr_t cur_desc;

	cur_desc = ((u64)in_be32(priv->chan[ch].reg + TALITOS_CDPR)) << 32;
	cur_desc |= in_be32(priv->chan[ch].reg + TALITOS_CDPR_LO);

	अगर (!cur_desc) अणु
		dev_err(dev, "CDPR is NULL, giving up search for offending descriptor\n");
		वापस 0;
	पूर्ण

	tail = priv->chan[ch].tail;

	iter = tail;
	जबतक (priv->chan[ch].fअगरo[iter].dma_desc != cur_desc &&
	       priv->chan[ch].fअगरo[iter].desc->next_desc != cpu_to_be32(cur_desc)) अणु
		iter = (iter + 1) & (priv->fअगरo_len - 1);
		अगर (iter == tail) अणु
			dev_err(dev, "couldn't locate current descriptor\n");
			वापस 0;
		पूर्ण
	पूर्ण

	अगर (priv->chan[ch].fअगरo[iter].desc->next_desc == cpu_to_be32(cur_desc)) अणु
		काष्ठा talitos_edesc *edesc;

		edesc = container_of(priv->chan[ch].fअगरo[iter].desc,
				     काष्ठा talitos_edesc, desc);
		वापस ((काष्ठा talitos_desc *)
			(edesc->buf + edesc->dma_len))->hdr;
	पूर्ण

	वापस priv->chan[ch].fअगरo[iter].desc->hdr;
पूर्ण

/*
 * user diagnostics; report root cause of error based on execution unit status
 */
अटल व्योम report_eu_error(काष्ठा device *dev, पूर्णांक ch, __be32 desc_hdr)
अणु
	काष्ठा talitos_निजी *priv = dev_get_drvdata(dev);
	पूर्णांक i;

	अगर (!desc_hdr)
		desc_hdr = cpu_to_be32(in_be32(priv->chan[ch].reg + TALITOS_DESCBUF));

	चयन (desc_hdr & DESC_HDR_SEL0_MASK) अणु
	हाल DESC_HDR_SEL0_AFEU:
		dev_err(dev, "AFEUISR 0x%08x_%08x\n",
			in_be32(priv->reg_afeu + TALITOS_EUISR),
			in_be32(priv->reg_afeu + TALITOS_EUISR_LO));
		अवरोध;
	हाल DESC_HDR_SEL0_DEU:
		dev_err(dev, "DEUISR 0x%08x_%08x\n",
			in_be32(priv->reg_deu + TALITOS_EUISR),
			in_be32(priv->reg_deu + TALITOS_EUISR_LO));
		अवरोध;
	हाल DESC_HDR_SEL0_MDEUA:
	हाल DESC_HDR_SEL0_MDEUB:
		dev_err(dev, "MDEUISR 0x%08x_%08x\n",
			in_be32(priv->reg_mdeu + TALITOS_EUISR),
			in_be32(priv->reg_mdeu + TALITOS_EUISR_LO));
		अवरोध;
	हाल DESC_HDR_SEL0_RNG:
		dev_err(dev, "RNGUISR 0x%08x_%08x\n",
			in_be32(priv->reg_rngu + TALITOS_ISR),
			in_be32(priv->reg_rngu + TALITOS_ISR_LO));
		अवरोध;
	हाल DESC_HDR_SEL0_PKEU:
		dev_err(dev, "PKEUISR 0x%08x_%08x\n",
			in_be32(priv->reg_pkeu + TALITOS_EUISR),
			in_be32(priv->reg_pkeu + TALITOS_EUISR_LO));
		अवरोध;
	हाल DESC_HDR_SEL0_AESU:
		dev_err(dev, "AESUISR 0x%08x_%08x\n",
			in_be32(priv->reg_aesu + TALITOS_EUISR),
			in_be32(priv->reg_aesu + TALITOS_EUISR_LO));
		अवरोध;
	हाल DESC_HDR_SEL0_CRCU:
		dev_err(dev, "CRCUISR 0x%08x_%08x\n",
			in_be32(priv->reg_crcu + TALITOS_EUISR),
			in_be32(priv->reg_crcu + TALITOS_EUISR_LO));
		अवरोध;
	हाल DESC_HDR_SEL0_KEU:
		dev_err(dev, "KEUISR 0x%08x_%08x\n",
			in_be32(priv->reg_pkeu + TALITOS_EUISR),
			in_be32(priv->reg_pkeu + TALITOS_EUISR_LO));
		अवरोध;
	पूर्ण

	चयन (desc_hdr & DESC_HDR_SEL1_MASK) अणु
	हाल DESC_HDR_SEL1_MDEUA:
	हाल DESC_HDR_SEL1_MDEUB:
		dev_err(dev, "MDEUISR 0x%08x_%08x\n",
			in_be32(priv->reg_mdeu + TALITOS_EUISR),
			in_be32(priv->reg_mdeu + TALITOS_EUISR_LO));
		अवरोध;
	हाल DESC_HDR_SEL1_CRCU:
		dev_err(dev, "CRCUISR 0x%08x_%08x\n",
			in_be32(priv->reg_crcu + TALITOS_EUISR),
			in_be32(priv->reg_crcu + TALITOS_EUISR_LO));
		अवरोध;
	पूर्ण

	क्रम (i = 0; i < 8; i++)
		dev_err(dev, "DESCBUF 0x%08x_%08x\n",
			in_be32(priv->chan[ch].reg + TALITOS_DESCBUF + 8*i),
			in_be32(priv->chan[ch].reg + TALITOS_DESCBUF_LO + 8*i));
पूर्ण

/*
 * recover from error पूर्णांकerrupts
 */
अटल व्योम talitos_error(काष्ठा device *dev, u32 isr, u32 isr_lo)
अणु
	काष्ठा talitos_निजी *priv = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक समयout = TALITOS_TIMEOUT;
	पूर्णांक ch, error, reset_dev = 0;
	u32 v_lo;
	bool is_sec1 = has_ftr_sec1(priv);
	पूर्णांक reset_ch = is_sec1 ? 1 : 0; /* only SEC2 supports continuation */

	क्रम (ch = 0; ch < priv->num_channels; ch++) अणु
		/* skip channels without errors */
		अगर (is_sec1) अणु
			/* bits 29, 31, 17, 19 */
			अगर (!(isr & (1 << (29 + (ch & 1) * 2 - (ch & 2) * 6))))
				जारी;
		पूर्ण अन्यथा अणु
			अगर (!(isr & (1 << (ch * 2 + 1))))
				जारी;
		पूर्ण

		error = -EINVAL;

		v_lo = in_be32(priv->chan[ch].reg + TALITOS_CCPSR_LO);

		अगर (v_lo & TALITOS_CCPSR_LO_DOF) अणु
			dev_err(dev, "double fetch fifo overflow error\n");
			error = -EAGAIN;
			reset_ch = 1;
		पूर्ण
		अगर (v_lo & TALITOS_CCPSR_LO_SOF) अणु
			/* h/w dropped descriptor */
			dev_err(dev, "single fetch fifo overflow error\n");
			error = -EAGAIN;
		पूर्ण
		अगर (v_lo & TALITOS_CCPSR_LO_MDTE)
			dev_err(dev, "master data transfer error\n");
		अगर (v_lo & TALITOS_CCPSR_LO_SGDLZ)
			dev_err(dev, is_sec1 ? "pointer not complete error\n"
					     : "s/g data length zero error\n");
		अगर (v_lo & TALITOS_CCPSR_LO_FPZ)
			dev_err(dev, is_sec1 ? "parity error\n"
					     : "fetch pointer zero error\n");
		अगर (v_lo & TALITOS_CCPSR_LO_IDH)
			dev_err(dev, "illegal descriptor header error\n");
		अगर (v_lo & TALITOS_CCPSR_LO_IEU)
			dev_err(dev, is_sec1 ? "static assignment error\n"
					     : "invalid exec unit error\n");
		अगर (v_lo & TALITOS_CCPSR_LO_EU)
			report_eu_error(dev, ch, current_desc_hdr(dev, ch));
		अगर (!is_sec1) अणु
			अगर (v_lo & TALITOS_CCPSR_LO_GB)
				dev_err(dev, "gather boundary error\n");
			अगर (v_lo & TALITOS_CCPSR_LO_GRL)
				dev_err(dev, "gather return/length error\n");
			अगर (v_lo & TALITOS_CCPSR_LO_SB)
				dev_err(dev, "scatter boundary error\n");
			अगर (v_lo & TALITOS_CCPSR_LO_SRL)
				dev_err(dev, "scatter return/length error\n");
		पूर्ण

		flush_channel(dev, ch, error, reset_ch);

		अगर (reset_ch) अणु
			reset_channel(dev, ch);
		पूर्ण अन्यथा अणु
			setbits32(priv->chan[ch].reg + TALITOS_CCCR,
				  TALITOS2_CCCR_CONT);
			setbits32(priv->chan[ch].reg + TALITOS_CCCR_LO, 0);
			जबतक ((in_be32(priv->chan[ch].reg + TALITOS_CCCR) &
			       TALITOS2_CCCR_CONT) && --समयout)
				cpu_relax();
			अगर (समयout == 0) अणु
				dev_err(dev, "failed to restart channel %d\n",
					ch);
				reset_dev = 1;
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (reset_dev || (is_sec1 && isr & ~TALITOS1_ISR_4CHERR) ||
	    (!is_sec1 && isr & ~TALITOS2_ISR_4CHERR) || isr_lo) अणु
		अगर (is_sec1 && (isr_lo & TALITOS1_ISR_TEA_ERR))
			dev_err(dev, "TEA error: ISR 0x%08x_%08x\n",
				isr, isr_lo);
		अन्यथा
			dev_err(dev, "done overflow, internal time out, or "
				"rngu error: ISR 0x%08x_%08x\n", isr, isr_lo);

		/* purge request queues */
		क्रम (ch = 0; ch < priv->num_channels; ch++)
			flush_channel(dev, ch, -EIO, 1);

		/* reset and reinitialize the device */
		init_device(dev);
	पूर्ण
पूर्ण

#घोषणा DEF_TALITOS1_INTERRUPT(name, ch_करोne_mask, ch_err_mask, tlet)	       \
अटल irqवापस_t talitos1_पूर्णांकerrupt_##name(पूर्णांक irq, व्योम *data)	       \
अणु									       \
	काष्ठा device *dev = data;					       \
	काष्ठा talitos_निजी *priv = dev_get_drvdata(dev);		       \
	u32 isr, isr_lo;						       \
	अचिन्हित दीर्घ flags;						       \
									       \
	spin_lock_irqsave(&priv->reg_lock, flags);			       \
	isr = in_be32(priv->reg + TALITOS_ISR);				       \
	isr_lo = in_be32(priv->reg + TALITOS_ISR_LO);			       \
	/* Acknowledge पूर्णांकerrupt */					       \
	out_be32(priv->reg + TALITOS_ICR, isr & (ch_करोne_mask | ch_err_mask)); \
	out_be32(priv->reg + TALITOS_ICR_LO, isr_lo);			       \
									       \
	अगर (unlikely(isr & ch_err_mask || isr_lo & TALITOS1_IMR_LO_INIT)) अणु    \
		spin_unlock_irqrestore(&priv->reg_lock, flags);		       \
		talitos_error(dev, isr & ch_err_mask, isr_lo);		       \
	पूर्ण								       \
	अन्यथा अणु								       \
		अगर (likely(isr & ch_करोne_mask)) अणु			       \
			/* mask further करोne पूर्णांकerrupts. */		       \
			setbits32(priv->reg + TALITOS_IMR, ch_करोne_mask);      \
			/* करोne_task will unmask करोne पूर्णांकerrupts at निकास */    \
			tasklet_schedule(&priv->करोne_task[tlet]);	       \
		पूर्ण							       \
		spin_unlock_irqrestore(&priv->reg_lock, flags);		       \
	पूर्ण								       \
									       \
	वापस (isr & (ch_करोne_mask | ch_err_mask) || isr_lo) ? IRQ_HANDLED :  \
								IRQ_NONE;      \
पूर्ण

DEF_TALITOS1_INTERRUPT(4ch, TALITOS1_ISR_4CHDONE, TALITOS1_ISR_4CHERR, 0)

#घोषणा DEF_TALITOS2_INTERRUPT(name, ch_करोne_mask, ch_err_mask, tlet)	       \
अटल irqवापस_t talitos2_पूर्णांकerrupt_##name(पूर्णांक irq, व्योम *data)	       \
अणु									       \
	काष्ठा device *dev = data;					       \
	काष्ठा talitos_निजी *priv = dev_get_drvdata(dev);		       \
	u32 isr, isr_lo;						       \
	अचिन्हित दीर्घ flags;						       \
									       \
	spin_lock_irqsave(&priv->reg_lock, flags);			       \
	isr = in_be32(priv->reg + TALITOS_ISR);				       \
	isr_lo = in_be32(priv->reg + TALITOS_ISR_LO);			       \
	/* Acknowledge पूर्णांकerrupt */					       \
	out_be32(priv->reg + TALITOS_ICR, isr & (ch_करोne_mask | ch_err_mask)); \
	out_be32(priv->reg + TALITOS_ICR_LO, isr_lo);			       \
									       \
	अगर (unlikely(isr & ch_err_mask || isr_lo)) अणु			       \
		spin_unlock_irqrestore(&priv->reg_lock, flags);		       \
		talitos_error(dev, isr & ch_err_mask, isr_lo);		       \
	पूर्ण								       \
	अन्यथा अणु								       \
		अगर (likely(isr & ch_करोne_mask)) अणु			       \
			/* mask further करोne पूर्णांकerrupts. */		       \
			clrbits32(priv->reg + TALITOS_IMR, ch_करोne_mask);      \
			/* करोne_task will unmask करोne पूर्णांकerrupts at निकास */    \
			tasklet_schedule(&priv->करोne_task[tlet]);	       \
		पूर्ण							       \
		spin_unlock_irqrestore(&priv->reg_lock, flags);		       \
	पूर्ण								       \
									       \
	वापस (isr & (ch_करोne_mask | ch_err_mask) || isr_lo) ? IRQ_HANDLED :  \
								IRQ_NONE;      \
पूर्ण

DEF_TALITOS2_INTERRUPT(4ch, TALITOS2_ISR_4CHDONE, TALITOS2_ISR_4CHERR, 0)
DEF_TALITOS2_INTERRUPT(ch0_2, TALITOS2_ISR_CH_0_2_DONE, TALITOS2_ISR_CH_0_2_ERR,
		       0)
DEF_TALITOS2_INTERRUPT(ch1_3, TALITOS2_ISR_CH_1_3_DONE, TALITOS2_ISR_CH_1_3_ERR,
		       1)

/*
 * hwrng
 */
अटल पूर्णांक talitos_rng_data_present(काष्ठा hwrng *rng, पूर्णांक रुको)
अणु
	काष्ठा device *dev = (काष्ठा device *)rng->priv;
	काष्ठा talitos_निजी *priv = dev_get_drvdata(dev);
	u32 ofl;
	पूर्णांक i;

	क्रम (i = 0; i < 20; i++) अणु
		ofl = in_be32(priv->reg_rngu + TALITOS_EUSR_LO) &
		      TALITOS_RNGUSR_LO_OFL;
		अगर (ofl || !रुको)
			अवरोध;
		udelay(10);
	पूर्ण

	वापस !!ofl;
पूर्ण

अटल पूर्णांक talitos_rng_data_पढ़ो(काष्ठा hwrng *rng, u32 *data)
अणु
	काष्ठा device *dev = (काष्ठा device *)rng->priv;
	काष्ठा talitos_निजी *priv = dev_get_drvdata(dev);

	/* rng fअगरo requires 64-bit accesses */
	*data = in_be32(priv->reg_rngu + TALITOS_EU_FIFO);
	*data = in_be32(priv->reg_rngu + TALITOS_EU_FIFO_LO);

	वापस माप(u32);
पूर्ण

अटल पूर्णांक talitos_rng_init(काष्ठा hwrng *rng)
अणु
	काष्ठा device *dev = (काष्ठा device *)rng->priv;
	काष्ठा talitos_निजी *priv = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक समयout = TALITOS_TIMEOUT;

	setbits32(priv->reg_rngu + TALITOS_EURCR_LO, TALITOS_RNGURCR_LO_SR);
	जबतक (!(in_be32(priv->reg_rngu + TALITOS_EUSR_LO)
		 & TALITOS_RNGUSR_LO_RD)
	       && --समयout)
		cpu_relax();
	अगर (समयout == 0) अणु
		dev_err(dev, "failed to reset rng hw\n");
		वापस -ENODEV;
	पूर्ण

	/* start generating */
	setbits32(priv->reg_rngu + TALITOS_EUDSR_LO, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक talitos_रेजिस्टर_rng(काष्ठा device *dev)
अणु
	काष्ठा talitos_निजी *priv = dev_get_drvdata(dev);
	पूर्णांक err;

	priv->rng.name		= dev_driver_string(dev);
	priv->rng.init		= talitos_rng_init;
	priv->rng.data_present	= talitos_rng_data_present;
	priv->rng.data_पढ़ो	= talitos_rng_data_पढ़ो;
	priv->rng.priv		= (अचिन्हित दीर्घ)dev;

	err = hwrng_रेजिस्टर(&priv->rng);
	अगर (!err)
		priv->rng_रेजिस्टरed = true;

	वापस err;
पूर्ण

अटल व्योम talitos_unरेजिस्टर_rng(काष्ठा device *dev)
अणु
	काष्ठा talitos_निजी *priv = dev_get_drvdata(dev);

	अगर (!priv->rng_रेजिस्टरed)
		वापस;

	hwrng_unरेजिस्टर(&priv->rng);
	priv->rng_रेजिस्टरed = false;
पूर्ण

/*
 * crypto alg
 */
#घोषणा TALITOS_CRA_PRIORITY		3000
/*
 * Defines a priority क्रम करोing AEAD with descriptors type
 * HMAC_SNOOP_NO_AFEA (HSNA) instead of type IPSEC_ESP
 */
#घोषणा TALITOS_CRA_PRIORITY_AEAD_HSNA	(TALITOS_CRA_PRIORITY - 1)
#अगर_घोषित CONFIG_CRYPTO_DEV_TALITOS2
#घोषणा TALITOS_MAX_KEY_SIZE		(AES_MAX_KEY_SIZE + SHA512_BLOCK_SIZE)
#अन्यथा
#घोषणा TALITOS_MAX_KEY_SIZE		(AES_MAX_KEY_SIZE + SHA256_BLOCK_SIZE)
#पूर्ण_अगर
#घोषणा TALITOS_MAX_IV_LENGTH		16 /* max of AES_BLOCK_SIZE, DES3_EDE_BLOCK_SIZE */

काष्ठा talitos_ctx अणु
	काष्ठा device *dev;
	पूर्णांक ch;
	__be32 desc_hdr_ढाँचा;
	u8 key[TALITOS_MAX_KEY_SIZE];
	u8 iv[TALITOS_MAX_IV_LENGTH];
	dma_addr_t dma_key;
	अचिन्हित पूर्णांक keylen;
	अचिन्हित पूर्णांक enckeylen;
	अचिन्हित पूर्णांक authkeylen;
पूर्ण;

#घोषणा HASH_MAX_BLOCK_SIZE		SHA512_BLOCK_SIZE
#घोषणा TALITOS_MDEU_MAX_CONTEXT_SIZE	TALITOS_MDEU_CONTEXT_SIZE_SHA384_SHA512

काष्ठा talitos_ahash_req_ctx अणु
	u32 hw_context[TALITOS_MDEU_MAX_CONTEXT_SIZE / माप(u32)];
	अचिन्हित पूर्णांक hw_context_size;
	u8 buf[2][HASH_MAX_BLOCK_SIZE];
	पूर्णांक buf_idx;
	अचिन्हित पूर्णांक swinit;
	अचिन्हित पूर्णांक first;
	अचिन्हित पूर्णांक last;
	अचिन्हित पूर्णांक to_hash_later;
	अचिन्हित पूर्णांक nbuf;
	काष्ठा scatterlist bufsl[2];
	काष्ठा scatterlist *psrc;
पूर्ण;

काष्ठा talitos_export_state अणु
	u32 hw_context[TALITOS_MDEU_MAX_CONTEXT_SIZE / माप(u32)];
	u8 buf[HASH_MAX_BLOCK_SIZE];
	अचिन्हित पूर्णांक swinit;
	अचिन्हित पूर्णांक first;
	अचिन्हित पूर्णांक last;
	अचिन्हित पूर्णांक to_hash_later;
	अचिन्हित पूर्णांक nbuf;
पूर्ण;

अटल पूर्णांक aead_setkey(काष्ठा crypto_aead *authenc,
		       स्थिर u8 *key, अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा talitos_ctx *ctx = crypto_aead_ctx(authenc);
	काष्ठा device *dev = ctx->dev;
	काष्ठा crypto_authenc_keys keys;

	अगर (crypto_authenc_extractkeys(&keys, key, keylen) != 0)
		जाओ badkey;

	अगर (keys.authkeylen + keys.enckeylen > TALITOS_MAX_KEY_SIZE)
		जाओ badkey;

	अगर (ctx->keylen)
		dma_unmap_single(dev, ctx->dma_key, ctx->keylen, DMA_TO_DEVICE);

	स_नकल(ctx->key, keys.authkey, keys.authkeylen);
	स_नकल(&ctx->key[keys.authkeylen], keys.enckey, keys.enckeylen);

	ctx->keylen = keys.authkeylen + keys.enckeylen;
	ctx->enckeylen = keys.enckeylen;
	ctx->authkeylen = keys.authkeylen;
	ctx->dma_key = dma_map_single(dev, ctx->key, ctx->keylen,
				      DMA_TO_DEVICE);

	memzero_explicit(&keys, माप(keys));
	वापस 0;

badkey:
	memzero_explicit(&keys, माप(keys));
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक aead_des3_setkey(काष्ठा crypto_aead *authenc,
			    स्थिर u8 *key, अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा talitos_ctx *ctx = crypto_aead_ctx(authenc);
	काष्ठा device *dev = ctx->dev;
	काष्ठा crypto_authenc_keys keys;
	पूर्णांक err;

	err = crypto_authenc_extractkeys(&keys, key, keylen);
	अगर (unlikely(err))
		जाओ out;

	err = -EINVAL;
	अगर (keys.authkeylen + keys.enckeylen > TALITOS_MAX_KEY_SIZE)
		जाओ out;

	err = verअगरy_aead_des3_key(authenc, keys.enckey, keys.enckeylen);
	अगर (err)
		जाओ out;

	अगर (ctx->keylen)
		dma_unmap_single(dev, ctx->dma_key, ctx->keylen, DMA_TO_DEVICE);

	स_नकल(ctx->key, keys.authkey, keys.authkeylen);
	स_नकल(&ctx->key[keys.authkeylen], keys.enckey, keys.enckeylen);

	ctx->keylen = keys.authkeylen + keys.enckeylen;
	ctx->enckeylen = keys.enckeylen;
	ctx->authkeylen = keys.authkeylen;
	ctx->dma_key = dma_map_single(dev, ctx->key, ctx->keylen,
				      DMA_TO_DEVICE);

out:
	memzero_explicit(&keys, माप(keys));
	वापस err;
पूर्ण

अटल व्योम talitos_sg_unmap(काष्ठा device *dev,
			     काष्ठा talitos_edesc *edesc,
			     काष्ठा scatterlist *src,
			     काष्ठा scatterlist *dst,
			     अचिन्हित पूर्णांक len, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा talitos_निजी *priv = dev_get_drvdata(dev);
	bool is_sec1 = has_ftr_sec1(priv);
	अचिन्हित पूर्णांक src_nents = edesc->src_nents ? : 1;
	अचिन्हित पूर्णांक dst_nents = edesc->dst_nents ? : 1;

	अगर (is_sec1 && dst && dst_nents > 1) अणु
		dma_sync_single_क्रम_device(dev, edesc->dma_link_tbl + offset,
					   len, DMA_FROM_DEVICE);
		sg_pcopy_from_buffer(dst, dst_nents, edesc->buf + offset, len,
				     offset);
	पूर्ण
	अगर (src != dst) अणु
		अगर (src_nents == 1 || !is_sec1)
			dma_unmap_sg(dev, src, src_nents, DMA_TO_DEVICE);

		अगर (dst && (dst_nents == 1 || !is_sec1))
			dma_unmap_sg(dev, dst, dst_nents, DMA_FROM_DEVICE);
	पूर्ण अन्यथा अगर (src_nents == 1 || !is_sec1) अणु
		dma_unmap_sg(dev, src, src_nents, DMA_BIसूचीECTIONAL);
	पूर्ण
पूर्ण

अटल व्योम ipsec_esp_unmap(काष्ठा device *dev,
			    काष्ठा talitos_edesc *edesc,
			    काष्ठा aead_request *areq, bool encrypt)
अणु
	काष्ठा crypto_aead *aead = crypto_aead_reqtfm(areq);
	काष्ठा talitos_ctx *ctx = crypto_aead_ctx(aead);
	अचिन्हित पूर्णांक ivsize = crypto_aead_ivsize(aead);
	अचिन्हित पूर्णांक authsize = crypto_aead_authsize(aead);
	अचिन्हित पूर्णांक cryptlen = areq->cryptlen - (encrypt ? 0 : authsize);
	bool is_ipsec_esp = edesc->desc.hdr & DESC_HDR_TYPE_IPSEC_ESP;
	काष्ठा talitos_ptr *civ_ptr = &edesc->desc.ptr[is_ipsec_esp ? 2 : 3];

	अगर (is_ipsec_esp)
		unmap_single_talitos_ptr(dev, &edesc->desc.ptr[6],
					 DMA_FROM_DEVICE);
	unmap_single_talitos_ptr(dev, civ_ptr, DMA_TO_DEVICE);

	talitos_sg_unmap(dev, edesc, areq->src, areq->dst,
			 cryptlen + authsize, areq->assoclen);

	अगर (edesc->dma_len)
		dma_unmap_single(dev, edesc->dma_link_tbl, edesc->dma_len,
				 DMA_BIसूचीECTIONAL);

	अगर (!is_ipsec_esp) अणु
		अचिन्हित पूर्णांक dst_nents = edesc->dst_nents ? : 1;

		sg_pcopy_to_buffer(areq->dst, dst_nents, ctx->iv, ivsize,
				   areq->assoclen + cryptlen - ivsize);
	पूर्ण
पूर्ण

/*
 * ipsec_esp descriptor callbacks
 */
अटल व्योम ipsec_esp_encrypt_करोne(काष्ठा device *dev,
				   काष्ठा talitos_desc *desc, व्योम *context,
				   पूर्णांक err)
अणु
	काष्ठा aead_request *areq = context;
	काष्ठा crypto_aead *authenc = crypto_aead_reqtfm(areq);
	अचिन्हित पूर्णांक ivsize = crypto_aead_ivsize(authenc);
	काष्ठा talitos_edesc *edesc;

	edesc = container_of(desc, काष्ठा talitos_edesc, desc);

	ipsec_esp_unmap(dev, edesc, areq, true);

	dma_unmap_single(dev, edesc->iv_dma, ivsize, DMA_TO_DEVICE);

	kमुक्त(edesc);

	aead_request_complete(areq, err);
पूर्ण

अटल व्योम ipsec_esp_decrypt_swauth_करोne(काष्ठा device *dev,
					  काष्ठा talitos_desc *desc,
					  व्योम *context, पूर्णांक err)
अणु
	काष्ठा aead_request *req = context;
	काष्ठा crypto_aead *authenc = crypto_aead_reqtfm(req);
	अचिन्हित पूर्णांक authsize = crypto_aead_authsize(authenc);
	काष्ठा talitos_edesc *edesc;
	अक्षर *oicv, *icv;

	edesc = container_of(desc, काष्ठा talitos_edesc, desc);

	ipsec_esp_unmap(dev, edesc, req, false);

	अगर (!err) अणु
		/* auth check */
		oicv = edesc->buf + edesc->dma_len;
		icv = oicv - authsize;

		err = crypto_memneq(oicv, icv, authsize) ? -EBADMSG : 0;
	पूर्ण

	kमुक्त(edesc);

	aead_request_complete(req, err);
पूर्ण

अटल व्योम ipsec_esp_decrypt_hwauth_करोne(काष्ठा device *dev,
					  काष्ठा talitos_desc *desc,
					  व्योम *context, पूर्णांक err)
अणु
	काष्ठा aead_request *req = context;
	काष्ठा talitos_edesc *edesc;

	edesc = container_of(desc, काष्ठा talitos_edesc, desc);

	ipsec_esp_unmap(dev, edesc, req, false);

	/* check ICV auth status */
	अगर (!err && ((desc->hdr_lo & DESC_HDR_LO_ICCR1_MASK) !=
		     DESC_HDR_LO_ICCR1_PASS))
		err = -EBADMSG;

	kमुक्त(edesc);

	aead_request_complete(req, err);
पूर्ण

/*
 * convert scatterlist to SEC h/w link table क्रमmat
 * stop at cryptlen bytes
 */
अटल पूर्णांक sg_to_link_tbl_offset(काष्ठा scatterlist *sg, पूर्णांक sg_count,
				 अचिन्हित पूर्णांक offset, पूर्णांक datalen, पूर्णांक elen,
				 काष्ठा talitos_ptr *link_tbl_ptr, पूर्णांक align)
अणु
	पूर्णांक n_sg = elen ? sg_count + 1 : sg_count;
	पूर्णांक count = 0;
	पूर्णांक cryptlen = datalen + elen;
	पूर्णांक padding = ALIGN(cryptlen, align) - cryptlen;

	जबतक (cryptlen && sg && n_sg--) अणु
		अचिन्हित पूर्णांक len = sg_dma_len(sg);

		अगर (offset >= len) अणु
			offset -= len;
			जाओ next;
		पूर्ण

		len -= offset;

		अगर (len > cryptlen)
			len = cryptlen;

		अगर (datalen > 0 && len > datalen) अणु
			to_talitos_ptr(link_tbl_ptr + count,
				       sg_dma_address(sg) + offset, datalen, 0);
			to_talitos_ptr_ext_set(link_tbl_ptr + count, 0, 0);
			count++;
			len -= datalen;
			offset += datalen;
		पूर्ण
		to_talitos_ptr(link_tbl_ptr + count,
			       sg_dma_address(sg) + offset, sg_next(sg) ? len : len + padding, 0);
		to_talitos_ptr_ext_set(link_tbl_ptr + count, 0, 0);
		count++;
		cryptlen -= len;
		datalen -= len;
		offset = 0;

next:
		sg = sg_next(sg);
	पूर्ण

	/* tag end of link table */
	अगर (count > 0)
		to_talitos_ptr_ext_set(link_tbl_ptr + count - 1,
				       DESC_PTR_LNKTBL_RET, 0);

	वापस count;
पूर्ण

अटल पूर्णांक talitos_sg_map_ext(काष्ठा device *dev, काष्ठा scatterlist *src,
			      अचिन्हित पूर्णांक len, काष्ठा talitos_edesc *edesc,
			      काष्ठा talitos_ptr *ptr, पूर्णांक sg_count,
			      अचिन्हित पूर्णांक offset, पूर्णांक tbl_off, पूर्णांक elen,
			      bool क्रमce, पूर्णांक align)
अणु
	काष्ठा talitos_निजी *priv = dev_get_drvdata(dev);
	bool is_sec1 = has_ftr_sec1(priv);
	पूर्णांक aligned_len = ALIGN(len, align);

	अगर (!src) अणु
		to_talitos_ptr(ptr, 0, 0, is_sec1);
		वापस 1;
	पूर्ण
	to_talitos_ptr_ext_set(ptr, elen, is_sec1);
	अगर (sg_count == 1 && !क्रमce) अणु
		to_talitos_ptr(ptr, sg_dma_address(src) + offset, aligned_len, is_sec1);
		वापस sg_count;
	पूर्ण
	अगर (is_sec1) अणु
		to_talitos_ptr(ptr, edesc->dma_link_tbl + offset, aligned_len, is_sec1);
		वापस sg_count;
	पूर्ण
	sg_count = sg_to_link_tbl_offset(src, sg_count, offset, len, elen,
					 &edesc->link_tbl[tbl_off], align);
	अगर (sg_count == 1 && !क्रमce) अणु
		/* Only one segment now, so no link tbl needed*/
		copy_talitos_ptr(ptr, &edesc->link_tbl[tbl_off], is_sec1);
		वापस sg_count;
	पूर्ण
	to_talitos_ptr(ptr, edesc->dma_link_tbl +
			    tbl_off * माप(काष्ठा talitos_ptr), aligned_len, is_sec1);
	to_talitos_ptr_ext_or(ptr, DESC_PTR_LNKTBL_JUMP, is_sec1);

	वापस sg_count;
पूर्ण

अटल पूर्णांक talitos_sg_map(काष्ठा device *dev, काष्ठा scatterlist *src,
			  अचिन्हित पूर्णांक len, काष्ठा talitos_edesc *edesc,
			  काष्ठा talitos_ptr *ptr, पूर्णांक sg_count,
			  अचिन्हित पूर्णांक offset, पूर्णांक tbl_off)
अणु
	वापस talitos_sg_map_ext(dev, src, len, edesc, ptr, sg_count, offset,
				  tbl_off, 0, false, 1);
पूर्ण

/*
 * fill in and submit ipsec_esp descriptor
 */
अटल पूर्णांक ipsec_esp(काष्ठा talitos_edesc *edesc, काष्ठा aead_request *areq,
		     bool encrypt,
		     व्योम (*callback)(काष्ठा device *dev,
				      काष्ठा talitos_desc *desc,
				      व्योम *context, पूर्णांक error))
अणु
	काष्ठा crypto_aead *aead = crypto_aead_reqtfm(areq);
	अचिन्हित पूर्णांक authsize = crypto_aead_authsize(aead);
	काष्ठा talitos_ctx *ctx = crypto_aead_ctx(aead);
	काष्ठा device *dev = ctx->dev;
	काष्ठा talitos_desc *desc = &edesc->desc;
	अचिन्हित पूर्णांक cryptlen = areq->cryptlen - (encrypt ? 0 : authsize);
	अचिन्हित पूर्णांक ivsize = crypto_aead_ivsize(aead);
	पूर्णांक tbl_off = 0;
	पूर्णांक sg_count, ret;
	पूर्णांक elen = 0;
	bool sync_needed = false;
	काष्ठा talitos_निजी *priv = dev_get_drvdata(dev);
	bool is_sec1 = has_ftr_sec1(priv);
	bool is_ipsec_esp = desc->hdr & DESC_HDR_TYPE_IPSEC_ESP;
	काष्ठा talitos_ptr *civ_ptr = &desc->ptr[is_ipsec_esp ? 2 : 3];
	काष्ठा talitos_ptr *ckey_ptr = &desc->ptr[is_ipsec_esp ? 3 : 2];
	dma_addr_t dma_icv = edesc->dma_link_tbl + edesc->dma_len - authsize;

	/* hmac key */
	to_talitos_ptr(&desc->ptr[0], ctx->dma_key, ctx->authkeylen, is_sec1);

	sg_count = edesc->src_nents ?: 1;
	अगर (is_sec1 && sg_count > 1)
		sg_copy_to_buffer(areq->src, sg_count, edesc->buf,
				  areq->assoclen + cryptlen);
	अन्यथा
		sg_count = dma_map_sg(dev, areq->src, sg_count,
				      (areq->src == areq->dst) ?
				      DMA_BIसूचीECTIONAL : DMA_TO_DEVICE);

	/* hmac data */
	ret = talitos_sg_map(dev, areq->src, areq->assoclen, edesc,
			     &desc->ptr[1], sg_count, 0, tbl_off);

	अगर (ret > 1) अणु
		tbl_off += ret;
		sync_needed = true;
	पूर्ण

	/* cipher iv */
	to_talitos_ptr(civ_ptr, edesc->iv_dma, ivsize, is_sec1);

	/* cipher key */
	to_talitos_ptr(ckey_ptr, ctx->dma_key  + ctx->authkeylen,
		       ctx->enckeylen, is_sec1);

	/*
	 * cipher in
	 * map and adjust cipher len to aead request cryptlen.
	 * extent is bytes of HMAC postpended to ciphertext,
	 * typically 12 क्रम ipsec
	 */
	अगर (is_ipsec_esp && (desc->hdr & DESC_HDR_MODE1_MDEU_CICV))
		elen = authsize;

	ret = talitos_sg_map_ext(dev, areq->src, cryptlen, edesc, &desc->ptr[4],
				 sg_count, areq->assoclen, tbl_off, elen,
				 false, 1);

	अगर (ret > 1) अणु
		tbl_off += ret;
		sync_needed = true;
	पूर्ण

	/* cipher out */
	अगर (areq->src != areq->dst) अणु
		sg_count = edesc->dst_nents ? : 1;
		अगर (!is_sec1 || sg_count == 1)
			dma_map_sg(dev, areq->dst, sg_count, DMA_FROM_DEVICE);
	पूर्ण

	अगर (is_ipsec_esp && encrypt)
		elen = authsize;
	अन्यथा
		elen = 0;
	ret = talitos_sg_map_ext(dev, areq->dst, cryptlen, edesc, &desc->ptr[5],
				 sg_count, areq->assoclen, tbl_off, elen,
				 is_ipsec_esp && !encrypt, 1);
	tbl_off += ret;

	अगर (!encrypt && is_ipsec_esp) अणु
		काष्ठा talitos_ptr *tbl_ptr = &edesc->link_tbl[tbl_off];

		/* Add an entry to the link table क्रम ICV data */
		to_talitos_ptr_ext_set(tbl_ptr - 1, 0, is_sec1);
		to_talitos_ptr_ext_set(tbl_ptr, DESC_PTR_LNKTBL_RET, is_sec1);

		/* icv data follows link tables */
		to_talitos_ptr(tbl_ptr, dma_icv, authsize, is_sec1);
		to_talitos_ptr_ext_or(&desc->ptr[5], authsize, is_sec1);
		sync_needed = true;
	पूर्ण अन्यथा अगर (!encrypt) अणु
		to_talitos_ptr(&desc->ptr[6], dma_icv, authsize, is_sec1);
		sync_needed = true;
	पूर्ण अन्यथा अगर (!is_ipsec_esp) अणु
		talitos_sg_map(dev, areq->dst, authsize, edesc, &desc->ptr[6],
			       sg_count, areq->assoclen + cryptlen, tbl_off);
	पूर्ण

	/* iv out */
	अगर (is_ipsec_esp)
		map_single_talitos_ptr(dev, &desc->ptr[6], ivsize, ctx->iv,
				       DMA_FROM_DEVICE);

	अगर (sync_needed)
		dma_sync_single_क्रम_device(dev, edesc->dma_link_tbl,
					   edesc->dma_len,
					   DMA_BIसूचीECTIONAL);

	ret = talitos_submit(dev, ctx->ch, desc, callback, areq);
	अगर (ret != -EINPROGRESS) अणु
		ipsec_esp_unmap(dev, edesc, areq, encrypt);
		kमुक्त(edesc);
	पूर्ण
	वापस ret;
पूर्ण

/*
 * allocate and map the extended descriptor
 */
अटल काष्ठा talitos_edesc *talitos_edesc_alloc(काष्ठा device *dev,
						 काष्ठा scatterlist *src,
						 काष्ठा scatterlist *dst,
						 u8 *iv,
						 अचिन्हित पूर्णांक assoclen,
						 अचिन्हित पूर्णांक cryptlen,
						 अचिन्हित पूर्णांक authsize,
						 अचिन्हित पूर्णांक ivsize,
						 पूर्णांक icv_stashing,
						 u32 cryptoflags,
						 bool encrypt)
अणु
	काष्ठा talitos_edesc *edesc;
	पूर्णांक src_nents, dst_nents, alloc_len, dma_len, src_len, dst_len;
	dma_addr_t iv_dma = 0;
	gfp_t flags = cryptoflags & CRYPTO_TFM_REQ_MAY_SLEEP ? GFP_KERNEL :
		      GFP_ATOMIC;
	काष्ठा talitos_निजी *priv = dev_get_drvdata(dev);
	bool is_sec1 = has_ftr_sec1(priv);
	पूर्णांक max_len = is_sec1 ? TALITOS1_MAX_DATA_LEN : TALITOS2_MAX_DATA_LEN;

	अगर (cryptlen + authsize > max_len) अणु
		dev_err(dev, "length exceeds h/w max limit\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	अगर (!dst || dst == src) अणु
		src_len = assoclen + cryptlen + authsize;
		src_nents = sg_nents_क्रम_len(src, src_len);
		अगर (src_nents < 0) अणु
			dev_err(dev, "Invalid number of src SG.\n");
			वापस ERR_PTR(-EINVAL);
		पूर्ण
		src_nents = (src_nents == 1) ? 0 : src_nents;
		dst_nents = dst ? src_nents : 0;
		dst_len = 0;
	पूर्ण अन्यथा अणु /* dst && dst != src*/
		src_len = assoclen + cryptlen + (encrypt ? 0 : authsize);
		src_nents = sg_nents_क्रम_len(src, src_len);
		अगर (src_nents < 0) अणु
			dev_err(dev, "Invalid number of src SG.\n");
			वापस ERR_PTR(-EINVAL);
		पूर्ण
		src_nents = (src_nents == 1) ? 0 : src_nents;
		dst_len = assoclen + cryptlen + (encrypt ? authsize : 0);
		dst_nents = sg_nents_क्रम_len(dst, dst_len);
		अगर (dst_nents < 0) अणु
			dev_err(dev, "Invalid number of dst SG.\n");
			वापस ERR_PTR(-EINVAL);
		पूर्ण
		dst_nents = (dst_nents == 1) ? 0 : dst_nents;
	पूर्ण

	/*
	 * allocate space क्रम base edesc plus the link tables,
	 * allowing क्रम two separate entries क्रम AD and generated ICV (+ 2),
	 * and space क्रम two sets of ICVs (stashed and generated)
	 */
	alloc_len = माप(काष्ठा talitos_edesc);
	अगर (src_nents || dst_nents || !encrypt) अणु
		अगर (is_sec1)
			dma_len = (src_nents ? src_len : 0) +
				  (dst_nents ? dst_len : 0) + authsize;
		अन्यथा
			dma_len = (src_nents + dst_nents + 2) *
				  माप(काष्ठा talitos_ptr) + authsize;
		alloc_len += dma_len;
	पूर्ण अन्यथा अणु
		dma_len = 0;
	पूर्ण
	alloc_len += icv_stashing ? authsize : 0;

	/* अगर its a ahash, add space क्रम a second desc next to the first one */
	अगर (is_sec1 && !dst)
		alloc_len += माप(काष्ठा talitos_desc);
	alloc_len += ivsize;

	edesc = kदो_स्मृति(alloc_len, GFP_DMA | flags);
	अगर (!edesc)
		वापस ERR_PTR(-ENOMEM);
	अगर (ivsize) अणु
		iv = स_नकल(((u8 *)edesc) + alloc_len - ivsize, iv, ivsize);
		iv_dma = dma_map_single(dev, iv, ivsize, DMA_TO_DEVICE);
	पूर्ण
	स_रखो(&edesc->desc, 0, माप(edesc->desc));

	edesc->src_nents = src_nents;
	edesc->dst_nents = dst_nents;
	edesc->iv_dma = iv_dma;
	edesc->dma_len = dma_len;
	अगर (dma_len)
		edesc->dma_link_tbl = dma_map_single(dev, &edesc->link_tbl[0],
						     edesc->dma_len,
						     DMA_BIसूचीECTIONAL);

	वापस edesc;
पूर्ण

अटल काष्ठा talitos_edesc *aead_edesc_alloc(काष्ठा aead_request *areq, u8 *iv,
					      पूर्णांक icv_stashing, bool encrypt)
अणु
	काष्ठा crypto_aead *authenc = crypto_aead_reqtfm(areq);
	अचिन्हित पूर्णांक authsize = crypto_aead_authsize(authenc);
	काष्ठा talitos_ctx *ctx = crypto_aead_ctx(authenc);
	अचिन्हित पूर्णांक ivsize = crypto_aead_ivsize(authenc);
	अचिन्हित पूर्णांक cryptlen = areq->cryptlen - (encrypt ? 0 : authsize);

	वापस talitos_edesc_alloc(ctx->dev, areq->src, areq->dst,
				   iv, areq->assoclen, cryptlen,
				   authsize, ivsize, icv_stashing,
				   areq->base.flags, encrypt);
पूर्ण

अटल पूर्णांक aead_encrypt(काष्ठा aead_request *req)
अणु
	काष्ठा crypto_aead *authenc = crypto_aead_reqtfm(req);
	काष्ठा talitos_ctx *ctx = crypto_aead_ctx(authenc);
	काष्ठा talitos_edesc *edesc;

	/* allocate extended descriptor */
	edesc = aead_edesc_alloc(req, req->iv, 0, true);
	अगर (IS_ERR(edesc))
		वापस PTR_ERR(edesc);

	/* set encrypt */
	edesc->desc.hdr = ctx->desc_hdr_ढाँचा | DESC_HDR_MODE0_ENCRYPT;

	वापस ipsec_esp(edesc, req, true, ipsec_esp_encrypt_करोne);
पूर्ण

अटल पूर्णांक aead_decrypt(काष्ठा aead_request *req)
अणु
	काष्ठा crypto_aead *authenc = crypto_aead_reqtfm(req);
	अचिन्हित पूर्णांक authsize = crypto_aead_authsize(authenc);
	काष्ठा talitos_ctx *ctx = crypto_aead_ctx(authenc);
	काष्ठा talitos_निजी *priv = dev_get_drvdata(ctx->dev);
	काष्ठा talitos_edesc *edesc;
	व्योम *icvdata;

	/* allocate extended descriptor */
	edesc = aead_edesc_alloc(req, req->iv, 1, false);
	अगर (IS_ERR(edesc))
		वापस PTR_ERR(edesc);

	अगर ((edesc->desc.hdr & DESC_HDR_TYPE_IPSEC_ESP) &&
	    (priv->features & TALITOS_FTR_HW_AUTH_CHECK) &&
	    ((!edesc->src_nents && !edesc->dst_nents) ||
	     priv->features & TALITOS_FTR_SRC_LINK_TBL_LEN_INCLUDES_EXTENT)) अणु

		/* decrypt and check the ICV */
		edesc->desc.hdr = ctx->desc_hdr_ढाँचा |
				  DESC_HDR_सूची_INBOUND |
				  DESC_HDR_MODE1_MDEU_CICV;

		/* reset पूर्णांकegrity check result bits */

		वापस ipsec_esp(edesc, req, false,
				 ipsec_esp_decrypt_hwauth_करोne);
	पूर्ण

	/* Have to check the ICV with software */
	edesc->desc.hdr = ctx->desc_hdr_ढाँचा | DESC_HDR_सूची_INBOUND;

	/* stash incoming ICV क्रम later cmp with ICV generated by the h/w */
	icvdata = edesc->buf + edesc->dma_len;

	sg_pcopy_to_buffer(req->src, edesc->src_nents ? : 1, icvdata, authsize,
			   req->assoclen + req->cryptlen - authsize);

	वापस ipsec_esp(edesc, req, false, ipsec_esp_decrypt_swauth_करोne);
पूर्ण

अटल पूर्णांक skcipher_setkey(काष्ठा crypto_skcipher *cipher,
			     स्थिर u8 *key, अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा talitos_ctx *ctx = crypto_skcipher_ctx(cipher);
	काष्ठा device *dev = ctx->dev;

	अगर (ctx->keylen)
		dma_unmap_single(dev, ctx->dma_key, ctx->keylen, DMA_TO_DEVICE);

	स_नकल(&ctx->key, key, keylen);
	ctx->keylen = keylen;

	ctx->dma_key = dma_map_single(dev, ctx->key, keylen, DMA_TO_DEVICE);

	वापस 0;
पूर्ण

अटल पूर्णांक skcipher_des_setkey(काष्ठा crypto_skcipher *cipher,
				 स्थिर u8 *key, अचिन्हित पूर्णांक keylen)
अणु
	वापस verअगरy_skcipher_des_key(cipher, key) ?:
	       skcipher_setkey(cipher, key, keylen);
पूर्ण

अटल पूर्णांक skcipher_des3_setkey(काष्ठा crypto_skcipher *cipher,
				  स्थिर u8 *key, अचिन्हित पूर्णांक keylen)
अणु
	वापस verअगरy_skcipher_des3_key(cipher, key) ?:
	       skcipher_setkey(cipher, key, keylen);
पूर्ण

अटल पूर्णांक skcipher_aes_setkey(काष्ठा crypto_skcipher *cipher,
				  स्थिर u8 *key, अचिन्हित पूर्णांक keylen)
अणु
	अगर (keylen == AES_KEYSIZE_128 || keylen == AES_KEYSIZE_192 ||
	    keylen == AES_KEYSIZE_256)
		वापस skcipher_setkey(cipher, key, keylen);

	वापस -EINVAL;
पूर्ण

अटल व्योम common_nonsnoop_unmap(काष्ठा device *dev,
				  काष्ठा talitos_edesc *edesc,
				  काष्ठा skcipher_request *areq)
अणु
	unmap_single_talitos_ptr(dev, &edesc->desc.ptr[5], DMA_FROM_DEVICE);

	talitos_sg_unmap(dev, edesc, areq->src, areq->dst, areq->cryptlen, 0);
	unmap_single_talitos_ptr(dev, &edesc->desc.ptr[1], DMA_TO_DEVICE);

	अगर (edesc->dma_len)
		dma_unmap_single(dev, edesc->dma_link_tbl, edesc->dma_len,
				 DMA_BIसूचीECTIONAL);
पूर्ण

अटल व्योम skcipher_करोne(काष्ठा device *dev,
			    काष्ठा talitos_desc *desc, व्योम *context,
			    पूर्णांक err)
अणु
	काष्ठा skcipher_request *areq = context;
	काष्ठा crypto_skcipher *cipher = crypto_skcipher_reqtfm(areq);
	काष्ठा talitos_ctx *ctx = crypto_skcipher_ctx(cipher);
	अचिन्हित पूर्णांक ivsize = crypto_skcipher_ivsize(cipher);
	काष्ठा talitos_edesc *edesc;

	edesc = container_of(desc, काष्ठा talitos_edesc, desc);

	common_nonsnoop_unmap(dev, edesc, areq);
	स_नकल(areq->iv, ctx->iv, ivsize);

	kमुक्त(edesc);

	areq->base.complete(&areq->base, err);
पूर्ण

अटल पूर्णांक common_nonsnoop(काष्ठा talitos_edesc *edesc,
			   काष्ठा skcipher_request *areq,
			   व्योम (*callback) (काष्ठा device *dev,
					     काष्ठा talitos_desc *desc,
					     व्योम *context, पूर्णांक error))
अणु
	काष्ठा crypto_skcipher *cipher = crypto_skcipher_reqtfm(areq);
	काष्ठा talitos_ctx *ctx = crypto_skcipher_ctx(cipher);
	काष्ठा device *dev = ctx->dev;
	काष्ठा talitos_desc *desc = &edesc->desc;
	अचिन्हित पूर्णांक cryptlen = areq->cryptlen;
	अचिन्हित पूर्णांक ivsize = crypto_skcipher_ivsize(cipher);
	पूर्णांक sg_count, ret;
	bool sync_needed = false;
	काष्ठा talitos_निजी *priv = dev_get_drvdata(dev);
	bool is_sec1 = has_ftr_sec1(priv);
	bool is_ctr = (desc->hdr & DESC_HDR_SEL0_MASK) == DESC_HDR_SEL0_AESU &&
		      (desc->hdr & DESC_HDR_MODE0_AESU_MASK) == DESC_HDR_MODE0_AESU_CTR;

	/* first DWORD empty */

	/* cipher iv */
	to_talitos_ptr(&desc->ptr[1], edesc->iv_dma, ivsize, is_sec1);

	/* cipher key */
	to_talitos_ptr(&desc->ptr[2], ctx->dma_key, ctx->keylen, is_sec1);

	sg_count = edesc->src_nents ?: 1;
	अगर (is_sec1 && sg_count > 1)
		sg_copy_to_buffer(areq->src, sg_count, edesc->buf,
				  cryptlen);
	अन्यथा
		sg_count = dma_map_sg(dev, areq->src, sg_count,
				      (areq->src == areq->dst) ?
				      DMA_BIसूचीECTIONAL : DMA_TO_DEVICE);
	/*
	 * cipher in
	 */
	sg_count = talitos_sg_map_ext(dev, areq->src, cryptlen, edesc, &desc->ptr[3],
				      sg_count, 0, 0, 0, false, is_ctr ? 16 : 1);
	अगर (sg_count > 1)
		sync_needed = true;

	/* cipher out */
	अगर (areq->src != areq->dst) अणु
		sg_count = edesc->dst_nents ? : 1;
		अगर (!is_sec1 || sg_count == 1)
			dma_map_sg(dev, areq->dst, sg_count, DMA_FROM_DEVICE);
	पूर्ण

	ret = talitos_sg_map(dev, areq->dst, cryptlen, edesc, &desc->ptr[4],
			     sg_count, 0, (edesc->src_nents + 1));
	अगर (ret > 1)
		sync_needed = true;

	/* iv out */
	map_single_talitos_ptr(dev, &desc->ptr[5], ivsize, ctx->iv,
			       DMA_FROM_DEVICE);

	/* last DWORD empty */

	अगर (sync_needed)
		dma_sync_single_क्रम_device(dev, edesc->dma_link_tbl,
					   edesc->dma_len, DMA_BIसूचीECTIONAL);

	ret = talitos_submit(dev, ctx->ch, desc, callback, areq);
	अगर (ret != -EINPROGRESS) अणु
		common_nonsnoop_unmap(dev, edesc, areq);
		kमुक्त(edesc);
	पूर्ण
	वापस ret;
पूर्ण

अटल काष्ठा talitos_edesc *skcipher_edesc_alloc(काष्ठा skcipher_request *
						    areq, bool encrypt)
अणु
	काष्ठा crypto_skcipher *cipher = crypto_skcipher_reqtfm(areq);
	काष्ठा talitos_ctx *ctx = crypto_skcipher_ctx(cipher);
	अचिन्हित पूर्णांक ivsize = crypto_skcipher_ivsize(cipher);

	वापस talitos_edesc_alloc(ctx->dev, areq->src, areq->dst,
				   areq->iv, 0, areq->cryptlen, 0, ivsize, 0,
				   areq->base.flags, encrypt);
पूर्ण

अटल पूर्णांक skcipher_encrypt(काष्ठा skcipher_request *areq)
अणु
	काष्ठा crypto_skcipher *cipher = crypto_skcipher_reqtfm(areq);
	काष्ठा talitos_ctx *ctx = crypto_skcipher_ctx(cipher);
	काष्ठा talitos_edesc *edesc;
	अचिन्हित पूर्णांक blocksize =
			crypto_tfm_alg_blocksize(crypto_skcipher_tfm(cipher));

	अगर (!areq->cryptlen)
		वापस 0;

	अगर (areq->cryptlen % blocksize)
		वापस -EINVAL;

	/* allocate extended descriptor */
	edesc = skcipher_edesc_alloc(areq, true);
	अगर (IS_ERR(edesc))
		वापस PTR_ERR(edesc);

	/* set encrypt */
	edesc->desc.hdr = ctx->desc_hdr_ढाँचा | DESC_HDR_MODE0_ENCRYPT;

	वापस common_nonsnoop(edesc, areq, skcipher_करोne);
पूर्ण

अटल पूर्णांक skcipher_decrypt(काष्ठा skcipher_request *areq)
अणु
	काष्ठा crypto_skcipher *cipher = crypto_skcipher_reqtfm(areq);
	काष्ठा talitos_ctx *ctx = crypto_skcipher_ctx(cipher);
	काष्ठा talitos_edesc *edesc;
	अचिन्हित पूर्णांक blocksize =
			crypto_tfm_alg_blocksize(crypto_skcipher_tfm(cipher));

	अगर (!areq->cryptlen)
		वापस 0;

	अगर (areq->cryptlen % blocksize)
		वापस -EINVAL;

	/* allocate extended descriptor */
	edesc = skcipher_edesc_alloc(areq, false);
	अगर (IS_ERR(edesc))
		वापस PTR_ERR(edesc);

	edesc->desc.hdr = ctx->desc_hdr_ढाँचा | DESC_HDR_सूची_INBOUND;

	वापस common_nonsnoop(edesc, areq, skcipher_करोne);
पूर्ण

अटल व्योम common_nonsnoop_hash_unmap(काष्ठा device *dev,
				       काष्ठा talitos_edesc *edesc,
				       काष्ठा ahash_request *areq)
अणु
	काष्ठा talitos_ahash_req_ctx *req_ctx = ahash_request_ctx(areq);
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(areq);
	काष्ठा talitos_निजी *priv = dev_get_drvdata(dev);
	bool is_sec1 = has_ftr_sec1(priv);
	काष्ठा talitos_desc *desc = &edesc->desc;
	काष्ठा talitos_desc *desc2 = (काष्ठा talitos_desc *)
				     (edesc->buf + edesc->dma_len);

	unmap_single_talitos_ptr(dev, &edesc->desc.ptr[5], DMA_FROM_DEVICE);
	अगर (desc->next_desc &&
	    desc->ptr[5].ptr != desc2->ptr[5].ptr)
		unmap_single_talitos_ptr(dev, &desc2->ptr[5], DMA_FROM_DEVICE);
	अगर (req_ctx->last)
		स_नकल(areq->result, req_ctx->hw_context,
		       crypto_ahash_digestsize(tfm));

	अगर (req_ctx->psrc)
		talitos_sg_unmap(dev, edesc, req_ctx->psrc, शून्य, 0, 0);

	/* When using hashctx-in, must unmap it. */
	अगर (from_talitos_ptr_len(&edesc->desc.ptr[1], is_sec1))
		unmap_single_talitos_ptr(dev, &edesc->desc.ptr[1],
					 DMA_TO_DEVICE);
	अन्यथा अगर (desc->next_desc)
		unmap_single_talitos_ptr(dev, &desc2->ptr[1],
					 DMA_TO_DEVICE);

	अगर (is_sec1 && req_ctx->nbuf)
		unmap_single_talitos_ptr(dev, &desc->ptr[3],
					 DMA_TO_DEVICE);

	अगर (edesc->dma_len)
		dma_unmap_single(dev, edesc->dma_link_tbl, edesc->dma_len,
				 DMA_BIसूचीECTIONAL);

	अगर (edesc->desc.next_desc)
		dma_unmap_single(dev, be32_to_cpu(edesc->desc.next_desc),
				 TALITOS_DESC_SIZE, DMA_BIसूचीECTIONAL);
पूर्ण

अटल व्योम ahash_करोne(काष्ठा device *dev,
		       काष्ठा talitos_desc *desc, व्योम *context,
		       पूर्णांक err)
अणु
	काष्ठा ahash_request *areq = context;
	काष्ठा talitos_edesc *edesc =
		 container_of(desc, काष्ठा talitos_edesc, desc);
	काष्ठा talitos_ahash_req_ctx *req_ctx = ahash_request_ctx(areq);

	अगर (!req_ctx->last && req_ctx->to_hash_later) अणु
		/* Position any partial block क्रम next update/final/finup */
		req_ctx->buf_idx = (req_ctx->buf_idx + 1) & 1;
		req_ctx->nbuf = req_ctx->to_hash_later;
	पूर्ण
	common_nonsnoop_hash_unmap(dev, edesc, areq);

	kमुक्त(edesc);

	areq->base.complete(&areq->base, err);
पूर्ण

/*
 * SEC1 करोesn't like hashing of 0 sized message, so we करो the padding
 * ourself and submit a padded block
 */
अटल व्योम talitos_handle_buggy_hash(काष्ठा talitos_ctx *ctx,
			       काष्ठा talitos_edesc *edesc,
			       काष्ठा talitos_ptr *ptr)
अणु
	अटल u8 padded_hash[64] = अणु
		0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	पूर्ण;

	pr_err_once("Bug in SEC1, padding ourself\n");
	edesc->desc.hdr &= ~DESC_HDR_MODE0_MDEU_PAD;
	map_single_talitos_ptr(ctx->dev, ptr, माप(padded_hash),
			       (अक्षर *)padded_hash, DMA_TO_DEVICE);
पूर्ण

अटल पूर्णांक common_nonsnoop_hash(काष्ठा talitos_edesc *edesc,
				काष्ठा ahash_request *areq, अचिन्हित पूर्णांक length,
				व्योम (*callback) (काष्ठा device *dev,
						  काष्ठा talitos_desc *desc,
						  व्योम *context, पूर्णांक error))
अणु
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(areq);
	काष्ठा talitos_ctx *ctx = crypto_ahash_ctx(tfm);
	काष्ठा talitos_ahash_req_ctx *req_ctx = ahash_request_ctx(areq);
	काष्ठा device *dev = ctx->dev;
	काष्ठा talitos_desc *desc = &edesc->desc;
	पूर्णांक ret;
	bool sync_needed = false;
	काष्ठा talitos_निजी *priv = dev_get_drvdata(dev);
	bool is_sec1 = has_ftr_sec1(priv);
	पूर्णांक sg_count;

	/* first DWORD empty */

	/* hash context in */
	अगर (!req_ctx->first || req_ctx->swinit) अणु
		map_single_talitos_ptr_nosync(dev, &desc->ptr[1],
					      req_ctx->hw_context_size,
					      req_ctx->hw_context,
					      DMA_TO_DEVICE);
		req_ctx->swinit = 0;
	पूर्ण
	/* Indicate next op is not the first. */
	req_ctx->first = 0;

	/* HMAC key */
	अगर (ctx->keylen)
		to_talitos_ptr(&desc->ptr[2], ctx->dma_key, ctx->keylen,
			       is_sec1);

	अगर (is_sec1 && req_ctx->nbuf)
		length -= req_ctx->nbuf;

	sg_count = edesc->src_nents ?: 1;
	अगर (is_sec1 && sg_count > 1)
		sg_copy_to_buffer(req_ctx->psrc, sg_count, edesc->buf, length);
	अन्यथा अगर (length)
		sg_count = dma_map_sg(dev, req_ctx->psrc, sg_count,
				      DMA_TO_DEVICE);
	/*
	 * data in
	 */
	अगर (is_sec1 && req_ctx->nbuf) अणु
		map_single_talitos_ptr(dev, &desc->ptr[3], req_ctx->nbuf,
				       req_ctx->buf[req_ctx->buf_idx],
				       DMA_TO_DEVICE);
	पूर्ण अन्यथा अणु
		sg_count = talitos_sg_map(dev, req_ctx->psrc, length, edesc,
					  &desc->ptr[3], sg_count, 0, 0);
		अगर (sg_count > 1)
			sync_needed = true;
	पूर्ण

	/* fअगरth DWORD empty */

	/* hash/HMAC out -or- hash context out */
	अगर (req_ctx->last)
		map_single_talitos_ptr(dev, &desc->ptr[5],
				       crypto_ahash_digestsize(tfm),
				       req_ctx->hw_context, DMA_FROM_DEVICE);
	अन्यथा
		map_single_talitos_ptr_nosync(dev, &desc->ptr[5],
					      req_ctx->hw_context_size,
					      req_ctx->hw_context,
					      DMA_FROM_DEVICE);

	/* last DWORD empty */

	अगर (is_sec1 && from_talitos_ptr_len(&desc->ptr[3], true) == 0)
		talitos_handle_buggy_hash(ctx, edesc, &desc->ptr[3]);

	अगर (is_sec1 && req_ctx->nbuf && length) अणु
		काष्ठा talitos_desc *desc2 = (काष्ठा talitos_desc *)
					     (edesc->buf + edesc->dma_len);
		dma_addr_t next_desc;

		स_रखो(desc2, 0, माप(*desc2));
		desc2->hdr = desc->hdr;
		desc2->hdr &= ~DESC_HDR_MODE0_MDEU_INIT;
		desc2->hdr1 = desc2->hdr;
		desc->hdr &= ~DESC_HDR_MODE0_MDEU_PAD;
		desc->hdr |= DESC_HDR_MODE0_MDEU_CONT;
		desc->hdr &= ~DESC_HDR_DONE_NOTIFY;

		अगर (desc->ptr[1].ptr)
			copy_talitos_ptr(&desc2->ptr[1], &desc->ptr[1],
					 is_sec1);
		अन्यथा
			map_single_talitos_ptr_nosync(dev, &desc2->ptr[1],
						      req_ctx->hw_context_size,
						      req_ctx->hw_context,
						      DMA_TO_DEVICE);
		copy_talitos_ptr(&desc2->ptr[2], &desc->ptr[2], is_sec1);
		sg_count = talitos_sg_map(dev, req_ctx->psrc, length, edesc,
					  &desc2->ptr[3], sg_count, 0, 0);
		अगर (sg_count > 1)
			sync_needed = true;
		copy_talitos_ptr(&desc2->ptr[5], &desc->ptr[5], is_sec1);
		अगर (req_ctx->last)
			map_single_talitos_ptr_nosync(dev, &desc->ptr[5],
						      req_ctx->hw_context_size,
						      req_ctx->hw_context,
						      DMA_FROM_DEVICE);

		next_desc = dma_map_single(dev, &desc2->hdr1, TALITOS_DESC_SIZE,
					   DMA_BIसूचीECTIONAL);
		desc->next_desc = cpu_to_be32(next_desc);
	पूर्ण

	अगर (sync_needed)
		dma_sync_single_क्रम_device(dev, edesc->dma_link_tbl,
					   edesc->dma_len, DMA_BIसूचीECTIONAL);

	ret = talitos_submit(dev, ctx->ch, desc, callback, areq);
	अगर (ret != -EINPROGRESS) अणु
		common_nonsnoop_hash_unmap(dev, edesc, areq);
		kमुक्त(edesc);
	पूर्ण
	वापस ret;
पूर्ण

अटल काष्ठा talitos_edesc *ahash_edesc_alloc(काष्ठा ahash_request *areq,
					       अचिन्हित पूर्णांक nbytes)
अणु
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(areq);
	काष्ठा talitos_ctx *ctx = crypto_ahash_ctx(tfm);
	काष्ठा talitos_ahash_req_ctx *req_ctx = ahash_request_ctx(areq);
	काष्ठा talitos_निजी *priv = dev_get_drvdata(ctx->dev);
	bool is_sec1 = has_ftr_sec1(priv);

	अगर (is_sec1)
		nbytes -= req_ctx->nbuf;

	वापस talitos_edesc_alloc(ctx->dev, req_ctx->psrc, शून्य, शून्य, 0,
				   nbytes, 0, 0, 0, areq->base.flags, false);
पूर्ण

अटल पूर्णांक ahash_init(काष्ठा ahash_request *areq)
अणु
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(areq);
	काष्ठा talitos_ctx *ctx = crypto_ahash_ctx(tfm);
	काष्ठा device *dev = ctx->dev;
	काष्ठा talitos_ahash_req_ctx *req_ctx = ahash_request_ctx(areq);
	अचिन्हित पूर्णांक size;
	dma_addr_t dma;

	/* Initialize the context */
	req_ctx->buf_idx = 0;
	req_ctx->nbuf = 0;
	req_ctx->first = 1; /* first indicates h/w must init its context */
	req_ctx->swinit = 0; /* assume h/w init of context */
	size =	(crypto_ahash_digestsize(tfm) <= SHA256_DIGEST_SIZE)
			? TALITOS_MDEU_CONTEXT_SIZE_MD5_SHA1_SHA256
			: TALITOS_MDEU_CONTEXT_SIZE_SHA384_SHA512;
	req_ctx->hw_context_size = size;

	dma = dma_map_single(dev, req_ctx->hw_context, req_ctx->hw_context_size,
			     DMA_TO_DEVICE);
	dma_unmap_single(dev, dma, req_ctx->hw_context_size, DMA_TO_DEVICE);

	वापस 0;
पूर्ण

/*
 * on h/w without explicit sha224 support, we initialize h/w context
 * manually with sha224 स्थिरants, and tell it to run sha256.
 */
अटल पूर्णांक ahash_init_sha224_swinit(काष्ठा ahash_request *areq)
अणु
	काष्ठा talitos_ahash_req_ctx *req_ctx = ahash_request_ctx(areq);

	req_ctx->hw_context[0] = SHA224_H0;
	req_ctx->hw_context[1] = SHA224_H1;
	req_ctx->hw_context[2] = SHA224_H2;
	req_ctx->hw_context[3] = SHA224_H3;
	req_ctx->hw_context[4] = SHA224_H4;
	req_ctx->hw_context[5] = SHA224_H5;
	req_ctx->hw_context[6] = SHA224_H6;
	req_ctx->hw_context[7] = SHA224_H7;

	/* init 64-bit count */
	req_ctx->hw_context[8] = 0;
	req_ctx->hw_context[9] = 0;

	ahash_init(areq);
	req_ctx->swinit = 1;/* prevent h/w initting context with sha256 values*/

	वापस 0;
पूर्ण

अटल पूर्णांक ahash_process_req(काष्ठा ahash_request *areq, अचिन्हित पूर्णांक nbytes)
अणु
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(areq);
	काष्ठा talitos_ctx *ctx = crypto_ahash_ctx(tfm);
	काष्ठा talitos_ahash_req_ctx *req_ctx = ahash_request_ctx(areq);
	काष्ठा talitos_edesc *edesc;
	अचिन्हित पूर्णांक blocksize =
			crypto_tfm_alg_blocksize(crypto_ahash_tfm(tfm));
	अचिन्हित पूर्णांक nbytes_to_hash;
	अचिन्हित पूर्णांक to_hash_later;
	अचिन्हित पूर्णांक nsg;
	पूर्णांक nents;
	काष्ठा device *dev = ctx->dev;
	काष्ठा talitos_निजी *priv = dev_get_drvdata(dev);
	bool is_sec1 = has_ftr_sec1(priv);
	u8 *ctx_buf = req_ctx->buf[req_ctx->buf_idx];

	अगर (!req_ctx->last && (nbytes + req_ctx->nbuf <= blocksize)) अणु
		/* Buffer up to one whole block */
		nents = sg_nents_क्रम_len(areq->src, nbytes);
		अगर (nents < 0) अणु
			dev_err(ctx->dev, "Invalid number of src SG.\n");
			वापस nents;
		पूर्ण
		sg_copy_to_buffer(areq->src, nents,
				  ctx_buf + req_ctx->nbuf, nbytes);
		req_ctx->nbuf += nbytes;
		वापस 0;
	पूर्ण

	/* At least (blocksize + 1) bytes are available to hash */
	nbytes_to_hash = nbytes + req_ctx->nbuf;
	to_hash_later = nbytes_to_hash & (blocksize - 1);

	अगर (req_ctx->last)
		to_hash_later = 0;
	अन्यथा अगर (to_hash_later)
		/* There is a partial block. Hash the full block(s) now */
		nbytes_to_hash -= to_hash_later;
	अन्यथा अणु
		/* Keep one block buffered */
		nbytes_to_hash -= blocksize;
		to_hash_later = blocksize;
	पूर्ण

	/* Chain in any previously buffered data */
	अगर (!is_sec1 && req_ctx->nbuf) अणु
		nsg = (req_ctx->nbuf < nbytes_to_hash) ? 2 : 1;
		sg_init_table(req_ctx->bufsl, nsg);
		sg_set_buf(req_ctx->bufsl, ctx_buf, req_ctx->nbuf);
		अगर (nsg > 1)
			sg_chain(req_ctx->bufsl, 2, areq->src);
		req_ctx->psrc = req_ctx->bufsl;
	पूर्ण अन्यथा अगर (is_sec1 && req_ctx->nbuf && req_ctx->nbuf < blocksize) अणु
		पूर्णांक offset;

		अगर (nbytes_to_hash > blocksize)
			offset = blocksize - req_ctx->nbuf;
		अन्यथा
			offset = nbytes_to_hash - req_ctx->nbuf;
		nents = sg_nents_क्रम_len(areq->src, offset);
		अगर (nents < 0) अणु
			dev_err(ctx->dev, "Invalid number of src SG.\n");
			वापस nents;
		पूर्ण
		sg_copy_to_buffer(areq->src, nents,
				  ctx_buf + req_ctx->nbuf, offset);
		req_ctx->nbuf += offset;
		req_ctx->psrc = scatterwalk_ffwd(req_ctx->bufsl, areq->src,
						 offset);
	पूर्ण अन्यथा
		req_ctx->psrc = areq->src;

	अगर (to_hash_later) अणु
		nents = sg_nents_क्रम_len(areq->src, nbytes);
		अगर (nents < 0) अणु
			dev_err(ctx->dev, "Invalid number of src SG.\n");
			वापस nents;
		पूर्ण
		sg_pcopy_to_buffer(areq->src, nents,
				   req_ctx->buf[(req_ctx->buf_idx + 1) & 1],
				      to_hash_later,
				      nbytes - to_hash_later);
	पूर्ण
	req_ctx->to_hash_later = to_hash_later;

	/* Allocate extended descriptor */
	edesc = ahash_edesc_alloc(areq, nbytes_to_hash);
	अगर (IS_ERR(edesc))
		वापस PTR_ERR(edesc);

	edesc->desc.hdr = ctx->desc_hdr_ढाँचा;

	/* On last one, request SEC to pad; otherwise जारी */
	अगर (req_ctx->last)
		edesc->desc.hdr |= DESC_HDR_MODE0_MDEU_PAD;
	अन्यथा
		edesc->desc.hdr |= DESC_HDR_MODE0_MDEU_CONT;

	/* request SEC to INIT hash. */
	अगर (req_ctx->first && !req_ctx->swinit)
		edesc->desc.hdr |= DESC_HDR_MODE0_MDEU_INIT;

	/* When the tfm context has a keylen, it's an HMAC.
	 * A first or last (ie. not middle) descriptor must request HMAC.
	 */
	अगर (ctx->keylen && (req_ctx->first || req_ctx->last))
		edesc->desc.hdr |= DESC_HDR_MODE0_MDEU_HMAC;

	वापस common_nonsnoop_hash(edesc, areq, nbytes_to_hash, ahash_करोne);
पूर्ण

अटल पूर्णांक ahash_update(काष्ठा ahash_request *areq)
अणु
	काष्ठा talitos_ahash_req_ctx *req_ctx = ahash_request_ctx(areq);

	req_ctx->last = 0;

	वापस ahash_process_req(areq, areq->nbytes);
पूर्ण

अटल पूर्णांक ahash_final(काष्ठा ahash_request *areq)
अणु
	काष्ठा talitos_ahash_req_ctx *req_ctx = ahash_request_ctx(areq);

	req_ctx->last = 1;

	वापस ahash_process_req(areq, 0);
पूर्ण

अटल पूर्णांक ahash_finup(काष्ठा ahash_request *areq)
अणु
	काष्ठा talitos_ahash_req_ctx *req_ctx = ahash_request_ctx(areq);

	req_ctx->last = 1;

	वापस ahash_process_req(areq, areq->nbytes);
पूर्ण

अटल पूर्णांक ahash_digest(काष्ठा ahash_request *areq)
अणु
	काष्ठा talitos_ahash_req_ctx *req_ctx = ahash_request_ctx(areq);
	काष्ठा crypto_ahash *ahash = crypto_ahash_reqtfm(areq);

	ahash->init(areq);
	req_ctx->last = 1;

	वापस ahash_process_req(areq, areq->nbytes);
पूर्ण

अटल पूर्णांक ahash_export(काष्ठा ahash_request *areq, व्योम *out)
अणु
	काष्ठा talitos_ahash_req_ctx *req_ctx = ahash_request_ctx(areq);
	काष्ठा talitos_export_state *export = out;
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(areq);
	काष्ठा talitos_ctx *ctx = crypto_ahash_ctx(tfm);
	काष्ठा device *dev = ctx->dev;
	dma_addr_t dma;

	dma = dma_map_single(dev, req_ctx->hw_context, req_ctx->hw_context_size,
			     DMA_FROM_DEVICE);
	dma_unmap_single(dev, dma, req_ctx->hw_context_size, DMA_FROM_DEVICE);

	स_नकल(export->hw_context, req_ctx->hw_context,
	       req_ctx->hw_context_size);
	स_नकल(export->buf, req_ctx->buf[req_ctx->buf_idx], req_ctx->nbuf);
	export->swinit = req_ctx->swinit;
	export->first = req_ctx->first;
	export->last = req_ctx->last;
	export->to_hash_later = req_ctx->to_hash_later;
	export->nbuf = req_ctx->nbuf;

	वापस 0;
पूर्ण

अटल पूर्णांक ahash_import(काष्ठा ahash_request *areq, स्थिर व्योम *in)
अणु
	काष्ठा talitos_ahash_req_ctx *req_ctx = ahash_request_ctx(areq);
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(areq);
	काष्ठा talitos_ctx *ctx = crypto_ahash_ctx(tfm);
	काष्ठा device *dev = ctx->dev;
	स्थिर काष्ठा talitos_export_state *export = in;
	अचिन्हित पूर्णांक size;
	dma_addr_t dma;

	स_रखो(req_ctx, 0, माप(*req_ctx));
	size = (crypto_ahash_digestsize(tfm) <= SHA256_DIGEST_SIZE)
			? TALITOS_MDEU_CONTEXT_SIZE_MD5_SHA1_SHA256
			: TALITOS_MDEU_CONTEXT_SIZE_SHA384_SHA512;
	req_ctx->hw_context_size = size;
	स_नकल(req_ctx->hw_context, export->hw_context, size);
	स_नकल(req_ctx->buf[0], export->buf, export->nbuf);
	req_ctx->swinit = export->swinit;
	req_ctx->first = export->first;
	req_ctx->last = export->last;
	req_ctx->to_hash_later = export->to_hash_later;
	req_ctx->nbuf = export->nbuf;

	dma = dma_map_single(dev, req_ctx->hw_context, req_ctx->hw_context_size,
			     DMA_TO_DEVICE);
	dma_unmap_single(dev, dma, req_ctx->hw_context_size, DMA_TO_DEVICE);

	वापस 0;
पूर्ण

अटल पूर्णांक keyhash(काष्ठा crypto_ahash *tfm, स्थिर u8 *key, अचिन्हित पूर्णांक keylen,
		   u8 *hash)
अणु
	काष्ठा talitos_ctx *ctx = crypto_tfm_ctx(crypto_ahash_tfm(tfm));

	काष्ठा scatterlist sg[1];
	काष्ठा ahash_request *req;
	काष्ठा crypto_रुको रुको;
	पूर्णांक ret;

	crypto_init_रुको(&रुको);

	req = ahash_request_alloc(tfm, GFP_KERNEL);
	अगर (!req)
		वापस -ENOMEM;

	/* Keep tfm keylen == 0 during hash of the दीर्घ key */
	ctx->keylen = 0;
	ahash_request_set_callback(req, CRYPTO_TFM_REQ_MAY_BACKLOG,
				   crypto_req_करोne, &रुको);

	sg_init_one(&sg[0], key, keylen);

	ahash_request_set_crypt(req, sg, hash, keylen);
	ret = crypto_रुको_req(crypto_ahash_digest(req), &रुको);

	ahash_request_मुक्त(req);

	वापस ret;
पूर्ण

अटल पूर्णांक ahash_setkey(काष्ठा crypto_ahash *tfm, स्थिर u8 *key,
			अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा talitos_ctx *ctx = crypto_tfm_ctx(crypto_ahash_tfm(tfm));
	काष्ठा device *dev = ctx->dev;
	अचिन्हित पूर्णांक blocksize =
			crypto_tfm_alg_blocksize(crypto_ahash_tfm(tfm));
	अचिन्हित पूर्णांक digestsize = crypto_ahash_digestsize(tfm);
	अचिन्हित पूर्णांक keysize = keylen;
	u8 hash[SHA512_DIGEST_SIZE];
	पूर्णांक ret;

	अगर (keylen <= blocksize)
		स_नकल(ctx->key, key, keysize);
	अन्यथा अणु
		/* Must get the hash of the दीर्घ key */
		ret = keyhash(tfm, key, keylen, hash);

		अगर (ret)
			वापस -EINVAL;

		keysize = digestsize;
		स_नकल(ctx->key, hash, digestsize);
	पूर्ण

	अगर (ctx->keylen)
		dma_unmap_single(dev, ctx->dma_key, ctx->keylen, DMA_TO_DEVICE);

	ctx->keylen = keysize;
	ctx->dma_key = dma_map_single(dev, ctx->key, keysize, DMA_TO_DEVICE);

	वापस 0;
पूर्ण


काष्ठा talitos_alg_ढाँचा अणु
	u32 type;
	u32 priority;
	जोड़ अणु
		काष्ठा skcipher_alg skcipher;
		काष्ठा ahash_alg hash;
		काष्ठा aead_alg aead;
	पूर्ण alg;
	__be32 desc_hdr_ढाँचा;
पूर्ण;

अटल काष्ठा talitos_alg_ढाँचा driver_algs[] = अणु
	/* AEAD algorithms.  These use a single-pass ipsec_esp descriptor */
	अणु	.type = CRYPTO_ALG_TYPE_AEAD,
		.alg.aead = अणु
			.base = अणु
				.cra_name = "authenc(hmac(sha1),cbc(aes))",
				.cra_driver_name = "authenc-hmac-sha1-"
						   "cbc-aes-talitos",
				.cra_blocksize = AES_BLOCK_SIZE,
				.cra_flags = CRYPTO_ALG_ASYNC |
					     CRYPTO_ALG_ALLOCATES_MEMORY,
			पूर्ण,
			.ivsize = AES_BLOCK_SIZE,
			.maxauthsize = SHA1_DIGEST_SIZE,
		पूर्ण,
		.desc_hdr_ढाँचा = DESC_HDR_TYPE_IPSEC_ESP |
			             DESC_HDR_SEL0_AESU |
		                     DESC_HDR_MODE0_AESU_CBC |
		                     DESC_HDR_SEL1_MDEUA |
		                     DESC_HDR_MODE1_MDEU_INIT |
		                     DESC_HDR_MODE1_MDEU_PAD |
		                     DESC_HDR_MODE1_MDEU_SHA1_HMAC,
	पूर्ण,
	अणु	.type = CRYPTO_ALG_TYPE_AEAD,
		.priority = TALITOS_CRA_PRIORITY_AEAD_HSNA,
		.alg.aead = अणु
			.base = अणु
				.cra_name = "authenc(hmac(sha1),cbc(aes))",
				.cra_driver_name = "authenc-hmac-sha1-"
						   "cbc-aes-talitos-hsna",
				.cra_blocksize = AES_BLOCK_SIZE,
				.cra_flags = CRYPTO_ALG_ASYNC |
					     CRYPTO_ALG_ALLOCATES_MEMORY,
			पूर्ण,
			.ivsize = AES_BLOCK_SIZE,
			.maxauthsize = SHA1_DIGEST_SIZE,
		पूर्ण,
		.desc_hdr_ढाँचा = DESC_HDR_TYPE_HMAC_SNOOP_NO_AFEU |
				     DESC_HDR_SEL0_AESU |
				     DESC_HDR_MODE0_AESU_CBC |
				     DESC_HDR_SEL1_MDEUA |
				     DESC_HDR_MODE1_MDEU_INIT |
				     DESC_HDR_MODE1_MDEU_PAD |
				     DESC_HDR_MODE1_MDEU_SHA1_HMAC,
	पूर्ण,
	अणु	.type = CRYPTO_ALG_TYPE_AEAD,
		.alg.aead = अणु
			.base = अणु
				.cra_name = "authenc(hmac(sha1),"
					    "cbc(des3_ede))",
				.cra_driver_name = "authenc-hmac-sha1-"
						   "cbc-3des-talitos",
				.cra_blocksize = DES3_EDE_BLOCK_SIZE,
				.cra_flags = CRYPTO_ALG_ASYNC |
					     CRYPTO_ALG_ALLOCATES_MEMORY,
			पूर्ण,
			.ivsize = DES3_EDE_BLOCK_SIZE,
			.maxauthsize = SHA1_DIGEST_SIZE,
			.setkey = aead_des3_setkey,
		पूर्ण,
		.desc_hdr_ढाँचा = DESC_HDR_TYPE_IPSEC_ESP |
			             DESC_HDR_SEL0_DEU |
		                     DESC_HDR_MODE0_DEU_CBC |
		                     DESC_HDR_MODE0_DEU_3DES |
		                     DESC_HDR_SEL1_MDEUA |
		                     DESC_HDR_MODE1_MDEU_INIT |
		                     DESC_HDR_MODE1_MDEU_PAD |
		                     DESC_HDR_MODE1_MDEU_SHA1_HMAC,
	पूर्ण,
	अणु	.type = CRYPTO_ALG_TYPE_AEAD,
		.priority = TALITOS_CRA_PRIORITY_AEAD_HSNA,
		.alg.aead = अणु
			.base = अणु
				.cra_name = "authenc(hmac(sha1),"
					    "cbc(des3_ede))",
				.cra_driver_name = "authenc-hmac-sha1-"
						   "cbc-3des-talitos-hsna",
				.cra_blocksize = DES3_EDE_BLOCK_SIZE,
				.cra_flags = CRYPTO_ALG_ASYNC |
					     CRYPTO_ALG_ALLOCATES_MEMORY,
			पूर्ण,
			.ivsize = DES3_EDE_BLOCK_SIZE,
			.maxauthsize = SHA1_DIGEST_SIZE,
			.setkey = aead_des3_setkey,
		पूर्ण,
		.desc_hdr_ढाँचा = DESC_HDR_TYPE_HMAC_SNOOP_NO_AFEU |
				     DESC_HDR_SEL0_DEU |
				     DESC_HDR_MODE0_DEU_CBC |
				     DESC_HDR_MODE0_DEU_3DES |
				     DESC_HDR_SEL1_MDEUA |
				     DESC_HDR_MODE1_MDEU_INIT |
				     DESC_HDR_MODE1_MDEU_PAD |
				     DESC_HDR_MODE1_MDEU_SHA1_HMAC,
	पूर्ण,
	अणु       .type = CRYPTO_ALG_TYPE_AEAD,
		.alg.aead = अणु
			.base = अणु
				.cra_name = "authenc(hmac(sha224),cbc(aes))",
				.cra_driver_name = "authenc-hmac-sha224-"
						   "cbc-aes-talitos",
				.cra_blocksize = AES_BLOCK_SIZE,
				.cra_flags = CRYPTO_ALG_ASYNC |
					     CRYPTO_ALG_ALLOCATES_MEMORY,
			पूर्ण,
			.ivsize = AES_BLOCK_SIZE,
			.maxauthsize = SHA224_DIGEST_SIZE,
		पूर्ण,
		.desc_hdr_ढाँचा = DESC_HDR_TYPE_IPSEC_ESP |
				     DESC_HDR_SEL0_AESU |
				     DESC_HDR_MODE0_AESU_CBC |
				     DESC_HDR_SEL1_MDEUA |
				     DESC_HDR_MODE1_MDEU_INIT |
				     DESC_HDR_MODE1_MDEU_PAD |
				     DESC_HDR_MODE1_MDEU_SHA224_HMAC,
	पूर्ण,
	अणु       .type = CRYPTO_ALG_TYPE_AEAD,
		.priority = TALITOS_CRA_PRIORITY_AEAD_HSNA,
		.alg.aead = अणु
			.base = अणु
				.cra_name = "authenc(hmac(sha224),cbc(aes))",
				.cra_driver_name = "authenc-hmac-sha224-"
						   "cbc-aes-talitos-hsna",
				.cra_blocksize = AES_BLOCK_SIZE,
				.cra_flags = CRYPTO_ALG_ASYNC |
					     CRYPTO_ALG_ALLOCATES_MEMORY,
			पूर्ण,
			.ivsize = AES_BLOCK_SIZE,
			.maxauthsize = SHA224_DIGEST_SIZE,
		पूर्ण,
		.desc_hdr_ढाँचा = DESC_HDR_TYPE_HMAC_SNOOP_NO_AFEU |
				     DESC_HDR_SEL0_AESU |
				     DESC_HDR_MODE0_AESU_CBC |
				     DESC_HDR_SEL1_MDEUA |
				     DESC_HDR_MODE1_MDEU_INIT |
				     DESC_HDR_MODE1_MDEU_PAD |
				     DESC_HDR_MODE1_MDEU_SHA224_HMAC,
	पूर्ण,
	अणु	.type = CRYPTO_ALG_TYPE_AEAD,
		.alg.aead = अणु
			.base = अणु
				.cra_name = "authenc(hmac(sha224),"
					    "cbc(des3_ede))",
				.cra_driver_name = "authenc-hmac-sha224-"
						   "cbc-3des-talitos",
				.cra_blocksize = DES3_EDE_BLOCK_SIZE,
				.cra_flags = CRYPTO_ALG_ASYNC |
					     CRYPTO_ALG_ALLOCATES_MEMORY,
			पूर्ण,
			.ivsize = DES3_EDE_BLOCK_SIZE,
			.maxauthsize = SHA224_DIGEST_SIZE,
			.setkey = aead_des3_setkey,
		पूर्ण,
		.desc_hdr_ढाँचा = DESC_HDR_TYPE_IPSEC_ESP |
			             DESC_HDR_SEL0_DEU |
		                     DESC_HDR_MODE0_DEU_CBC |
		                     DESC_HDR_MODE0_DEU_3DES |
		                     DESC_HDR_SEL1_MDEUA |
		                     DESC_HDR_MODE1_MDEU_INIT |
		                     DESC_HDR_MODE1_MDEU_PAD |
		                     DESC_HDR_MODE1_MDEU_SHA224_HMAC,
	पूर्ण,
	अणु	.type = CRYPTO_ALG_TYPE_AEAD,
		.priority = TALITOS_CRA_PRIORITY_AEAD_HSNA,
		.alg.aead = अणु
			.base = अणु
				.cra_name = "authenc(hmac(sha224),"
					    "cbc(des3_ede))",
				.cra_driver_name = "authenc-hmac-sha224-"
						   "cbc-3des-talitos-hsna",
				.cra_blocksize = DES3_EDE_BLOCK_SIZE,
				.cra_flags = CRYPTO_ALG_ASYNC |
					     CRYPTO_ALG_ALLOCATES_MEMORY,
			पूर्ण,
			.ivsize = DES3_EDE_BLOCK_SIZE,
			.maxauthsize = SHA224_DIGEST_SIZE,
			.setkey = aead_des3_setkey,
		पूर्ण,
		.desc_hdr_ढाँचा = DESC_HDR_TYPE_HMAC_SNOOP_NO_AFEU |
				     DESC_HDR_SEL0_DEU |
				     DESC_HDR_MODE0_DEU_CBC |
				     DESC_HDR_MODE0_DEU_3DES |
				     DESC_HDR_SEL1_MDEUA |
				     DESC_HDR_MODE1_MDEU_INIT |
				     DESC_HDR_MODE1_MDEU_PAD |
				     DESC_HDR_MODE1_MDEU_SHA224_HMAC,
	पूर्ण,
	अणु	.type = CRYPTO_ALG_TYPE_AEAD,
		.alg.aead = अणु
			.base = अणु
				.cra_name = "authenc(hmac(sha256),cbc(aes))",
				.cra_driver_name = "authenc-hmac-sha256-"
						   "cbc-aes-talitos",
				.cra_blocksize = AES_BLOCK_SIZE,
				.cra_flags = CRYPTO_ALG_ASYNC |
					     CRYPTO_ALG_ALLOCATES_MEMORY,
			पूर्ण,
			.ivsize = AES_BLOCK_SIZE,
			.maxauthsize = SHA256_DIGEST_SIZE,
		पूर्ण,
		.desc_hdr_ढाँचा = DESC_HDR_TYPE_IPSEC_ESP |
			             DESC_HDR_SEL0_AESU |
		                     DESC_HDR_MODE0_AESU_CBC |
		                     DESC_HDR_SEL1_MDEUA |
		                     DESC_HDR_MODE1_MDEU_INIT |
		                     DESC_HDR_MODE1_MDEU_PAD |
		                     DESC_HDR_MODE1_MDEU_SHA256_HMAC,
	पूर्ण,
	अणु	.type = CRYPTO_ALG_TYPE_AEAD,
		.priority = TALITOS_CRA_PRIORITY_AEAD_HSNA,
		.alg.aead = अणु
			.base = अणु
				.cra_name = "authenc(hmac(sha256),cbc(aes))",
				.cra_driver_name = "authenc-hmac-sha256-"
						   "cbc-aes-talitos-hsna",
				.cra_blocksize = AES_BLOCK_SIZE,
				.cra_flags = CRYPTO_ALG_ASYNC |
					     CRYPTO_ALG_ALLOCATES_MEMORY,
			पूर्ण,
			.ivsize = AES_BLOCK_SIZE,
			.maxauthsize = SHA256_DIGEST_SIZE,
		पूर्ण,
		.desc_hdr_ढाँचा = DESC_HDR_TYPE_HMAC_SNOOP_NO_AFEU |
				     DESC_HDR_SEL0_AESU |
				     DESC_HDR_MODE0_AESU_CBC |
				     DESC_HDR_SEL1_MDEUA |
				     DESC_HDR_MODE1_MDEU_INIT |
				     DESC_HDR_MODE1_MDEU_PAD |
				     DESC_HDR_MODE1_MDEU_SHA256_HMAC,
	पूर्ण,
	अणु	.type = CRYPTO_ALG_TYPE_AEAD,
		.alg.aead = अणु
			.base = अणु
				.cra_name = "authenc(hmac(sha256),"
					    "cbc(des3_ede))",
				.cra_driver_name = "authenc-hmac-sha256-"
						   "cbc-3des-talitos",
				.cra_blocksize = DES3_EDE_BLOCK_SIZE,
				.cra_flags = CRYPTO_ALG_ASYNC |
					     CRYPTO_ALG_ALLOCATES_MEMORY,
			पूर्ण,
			.ivsize = DES3_EDE_BLOCK_SIZE,
			.maxauthsize = SHA256_DIGEST_SIZE,
			.setkey = aead_des3_setkey,
		पूर्ण,
		.desc_hdr_ढाँचा = DESC_HDR_TYPE_IPSEC_ESP |
			             DESC_HDR_SEL0_DEU |
		                     DESC_HDR_MODE0_DEU_CBC |
		                     DESC_HDR_MODE0_DEU_3DES |
		                     DESC_HDR_SEL1_MDEUA |
		                     DESC_HDR_MODE1_MDEU_INIT |
		                     DESC_HDR_MODE1_MDEU_PAD |
		                     DESC_HDR_MODE1_MDEU_SHA256_HMAC,
	पूर्ण,
	अणु	.type = CRYPTO_ALG_TYPE_AEAD,
		.priority = TALITOS_CRA_PRIORITY_AEAD_HSNA,
		.alg.aead = अणु
			.base = अणु
				.cra_name = "authenc(hmac(sha256),"
					    "cbc(des3_ede))",
				.cra_driver_name = "authenc-hmac-sha256-"
						   "cbc-3des-talitos-hsna",
				.cra_blocksize = DES3_EDE_BLOCK_SIZE,
				.cra_flags = CRYPTO_ALG_ASYNC |
					     CRYPTO_ALG_ALLOCATES_MEMORY,
			पूर्ण,
			.ivsize = DES3_EDE_BLOCK_SIZE,
			.maxauthsize = SHA256_DIGEST_SIZE,
			.setkey = aead_des3_setkey,
		पूर्ण,
		.desc_hdr_ढाँचा = DESC_HDR_TYPE_HMAC_SNOOP_NO_AFEU |
				     DESC_HDR_SEL0_DEU |
				     DESC_HDR_MODE0_DEU_CBC |
				     DESC_HDR_MODE0_DEU_3DES |
				     DESC_HDR_SEL1_MDEUA |
				     DESC_HDR_MODE1_MDEU_INIT |
				     DESC_HDR_MODE1_MDEU_PAD |
				     DESC_HDR_MODE1_MDEU_SHA256_HMAC,
	पूर्ण,
	अणु	.type = CRYPTO_ALG_TYPE_AEAD,
		.alg.aead = अणु
			.base = अणु
				.cra_name = "authenc(hmac(sha384),cbc(aes))",
				.cra_driver_name = "authenc-hmac-sha384-"
						   "cbc-aes-talitos",
				.cra_blocksize = AES_BLOCK_SIZE,
				.cra_flags = CRYPTO_ALG_ASYNC |
					     CRYPTO_ALG_ALLOCATES_MEMORY,
			पूर्ण,
			.ivsize = AES_BLOCK_SIZE,
			.maxauthsize = SHA384_DIGEST_SIZE,
		पूर्ण,
		.desc_hdr_ढाँचा = DESC_HDR_TYPE_IPSEC_ESP |
			             DESC_HDR_SEL0_AESU |
		                     DESC_HDR_MODE0_AESU_CBC |
		                     DESC_HDR_SEL1_MDEUB |
		                     DESC_HDR_MODE1_MDEU_INIT |
		                     DESC_HDR_MODE1_MDEU_PAD |
		                     DESC_HDR_MODE1_MDEUB_SHA384_HMAC,
	पूर्ण,
	अणु	.type = CRYPTO_ALG_TYPE_AEAD,
		.alg.aead = अणु
			.base = अणु
				.cra_name = "authenc(hmac(sha384),"
					    "cbc(des3_ede))",
				.cra_driver_name = "authenc-hmac-sha384-"
						   "cbc-3des-talitos",
				.cra_blocksize = DES3_EDE_BLOCK_SIZE,
				.cra_flags = CRYPTO_ALG_ASYNC |
					     CRYPTO_ALG_ALLOCATES_MEMORY,
			पूर्ण,
			.ivsize = DES3_EDE_BLOCK_SIZE,
			.maxauthsize = SHA384_DIGEST_SIZE,
			.setkey = aead_des3_setkey,
		पूर्ण,
		.desc_hdr_ढाँचा = DESC_HDR_TYPE_IPSEC_ESP |
			             DESC_HDR_SEL0_DEU |
		                     DESC_HDR_MODE0_DEU_CBC |
		                     DESC_HDR_MODE0_DEU_3DES |
		                     DESC_HDR_SEL1_MDEUB |
		                     DESC_HDR_MODE1_MDEU_INIT |
		                     DESC_HDR_MODE1_MDEU_PAD |
		                     DESC_HDR_MODE1_MDEUB_SHA384_HMAC,
	पूर्ण,
	अणु	.type = CRYPTO_ALG_TYPE_AEAD,
		.alg.aead = अणु
			.base = अणु
				.cra_name = "authenc(hmac(sha512),cbc(aes))",
				.cra_driver_name = "authenc-hmac-sha512-"
						   "cbc-aes-talitos",
				.cra_blocksize = AES_BLOCK_SIZE,
				.cra_flags = CRYPTO_ALG_ASYNC |
					     CRYPTO_ALG_ALLOCATES_MEMORY,
			पूर्ण,
			.ivsize = AES_BLOCK_SIZE,
			.maxauthsize = SHA512_DIGEST_SIZE,
		पूर्ण,
		.desc_hdr_ढाँचा = DESC_HDR_TYPE_IPSEC_ESP |
			             DESC_HDR_SEL0_AESU |
		                     DESC_HDR_MODE0_AESU_CBC |
		                     DESC_HDR_SEL1_MDEUB |
		                     DESC_HDR_MODE1_MDEU_INIT |
		                     DESC_HDR_MODE1_MDEU_PAD |
		                     DESC_HDR_MODE1_MDEUB_SHA512_HMAC,
	पूर्ण,
	अणु	.type = CRYPTO_ALG_TYPE_AEAD,
		.alg.aead = अणु
			.base = अणु
				.cra_name = "authenc(hmac(sha512),"
					    "cbc(des3_ede))",
				.cra_driver_name = "authenc-hmac-sha512-"
						   "cbc-3des-talitos",
				.cra_blocksize = DES3_EDE_BLOCK_SIZE,
				.cra_flags = CRYPTO_ALG_ASYNC |
					     CRYPTO_ALG_ALLOCATES_MEMORY,
			पूर्ण,
			.ivsize = DES3_EDE_BLOCK_SIZE,
			.maxauthsize = SHA512_DIGEST_SIZE,
			.setkey = aead_des3_setkey,
		पूर्ण,
		.desc_hdr_ढाँचा = DESC_HDR_TYPE_IPSEC_ESP |
			             DESC_HDR_SEL0_DEU |
		                     DESC_HDR_MODE0_DEU_CBC |
		                     DESC_HDR_MODE0_DEU_3DES |
		                     DESC_HDR_SEL1_MDEUB |
		                     DESC_HDR_MODE1_MDEU_INIT |
		                     DESC_HDR_MODE1_MDEU_PAD |
		                     DESC_HDR_MODE1_MDEUB_SHA512_HMAC,
	पूर्ण,
	अणु	.type = CRYPTO_ALG_TYPE_AEAD,
		.alg.aead = अणु
			.base = अणु
				.cra_name = "authenc(hmac(md5),cbc(aes))",
				.cra_driver_name = "authenc-hmac-md5-"
						   "cbc-aes-talitos",
				.cra_blocksize = AES_BLOCK_SIZE,
				.cra_flags = CRYPTO_ALG_ASYNC |
					     CRYPTO_ALG_ALLOCATES_MEMORY,
			पूर्ण,
			.ivsize = AES_BLOCK_SIZE,
			.maxauthsize = MD5_DIGEST_SIZE,
		पूर्ण,
		.desc_hdr_ढाँचा = DESC_HDR_TYPE_IPSEC_ESP |
			             DESC_HDR_SEL0_AESU |
		                     DESC_HDR_MODE0_AESU_CBC |
		                     DESC_HDR_SEL1_MDEUA |
		                     DESC_HDR_MODE1_MDEU_INIT |
		                     DESC_HDR_MODE1_MDEU_PAD |
		                     DESC_HDR_MODE1_MDEU_MD5_HMAC,
	पूर्ण,
	अणु	.type = CRYPTO_ALG_TYPE_AEAD,
		.priority = TALITOS_CRA_PRIORITY_AEAD_HSNA,
		.alg.aead = अणु
			.base = अणु
				.cra_name = "authenc(hmac(md5),cbc(aes))",
				.cra_driver_name = "authenc-hmac-md5-"
						   "cbc-aes-talitos-hsna",
				.cra_blocksize = AES_BLOCK_SIZE,
				.cra_flags = CRYPTO_ALG_ASYNC |
					     CRYPTO_ALG_ALLOCATES_MEMORY,
			पूर्ण,
			.ivsize = AES_BLOCK_SIZE,
			.maxauthsize = MD5_DIGEST_SIZE,
		पूर्ण,
		.desc_hdr_ढाँचा = DESC_HDR_TYPE_HMAC_SNOOP_NO_AFEU |
				     DESC_HDR_SEL0_AESU |
				     DESC_HDR_MODE0_AESU_CBC |
				     DESC_HDR_SEL1_MDEUA |
				     DESC_HDR_MODE1_MDEU_INIT |
				     DESC_HDR_MODE1_MDEU_PAD |
				     DESC_HDR_MODE1_MDEU_MD5_HMAC,
	पूर्ण,
	अणु	.type = CRYPTO_ALG_TYPE_AEAD,
		.alg.aead = अणु
			.base = अणु
				.cra_name = "authenc(hmac(md5),cbc(des3_ede))",
				.cra_driver_name = "authenc-hmac-md5-"
						   "cbc-3des-talitos",
				.cra_blocksize = DES3_EDE_BLOCK_SIZE,
				.cra_flags = CRYPTO_ALG_ASYNC |
					     CRYPTO_ALG_ALLOCATES_MEMORY,
			पूर्ण,
			.ivsize = DES3_EDE_BLOCK_SIZE,
			.maxauthsize = MD5_DIGEST_SIZE,
			.setkey = aead_des3_setkey,
		पूर्ण,
		.desc_hdr_ढाँचा = DESC_HDR_TYPE_IPSEC_ESP |
			             DESC_HDR_SEL0_DEU |
		                     DESC_HDR_MODE0_DEU_CBC |
		                     DESC_HDR_MODE0_DEU_3DES |
		                     DESC_HDR_SEL1_MDEUA |
		                     DESC_HDR_MODE1_MDEU_INIT |
		                     DESC_HDR_MODE1_MDEU_PAD |
		                     DESC_HDR_MODE1_MDEU_MD5_HMAC,
	पूर्ण,
	अणु	.type = CRYPTO_ALG_TYPE_AEAD,
		.priority = TALITOS_CRA_PRIORITY_AEAD_HSNA,
		.alg.aead = अणु
			.base = अणु
				.cra_name = "authenc(hmac(md5),cbc(des3_ede))",
				.cra_driver_name = "authenc-hmac-md5-"
						   "cbc-3des-talitos-hsna",
				.cra_blocksize = DES3_EDE_BLOCK_SIZE,
				.cra_flags = CRYPTO_ALG_ASYNC |
					     CRYPTO_ALG_ALLOCATES_MEMORY,
			पूर्ण,
			.ivsize = DES3_EDE_BLOCK_SIZE,
			.maxauthsize = MD5_DIGEST_SIZE,
			.setkey = aead_des3_setkey,
		पूर्ण,
		.desc_hdr_ढाँचा = DESC_HDR_TYPE_HMAC_SNOOP_NO_AFEU |
				     DESC_HDR_SEL0_DEU |
				     DESC_HDR_MODE0_DEU_CBC |
				     DESC_HDR_MODE0_DEU_3DES |
				     DESC_HDR_SEL1_MDEUA |
				     DESC_HDR_MODE1_MDEU_INIT |
				     DESC_HDR_MODE1_MDEU_PAD |
				     DESC_HDR_MODE1_MDEU_MD5_HMAC,
	पूर्ण,
	/* SKCIPHER algorithms. */
	अणु	.type = CRYPTO_ALG_TYPE_SKCIPHER,
		.alg.skcipher = अणु
			.base.cra_name = "ecb(aes)",
			.base.cra_driver_name = "ecb-aes-talitos",
			.base.cra_blocksize = AES_BLOCK_SIZE,
			.base.cra_flags = CRYPTO_ALG_ASYNC |
					  CRYPTO_ALG_ALLOCATES_MEMORY,
			.min_keysize = AES_MIN_KEY_SIZE,
			.max_keysize = AES_MAX_KEY_SIZE,
			.setkey = skcipher_aes_setkey,
		पूर्ण,
		.desc_hdr_ढाँचा = DESC_HDR_TYPE_COMMON_NONSNOOP_NO_AFEU |
				     DESC_HDR_SEL0_AESU,
	पूर्ण,
	अणु	.type = CRYPTO_ALG_TYPE_SKCIPHER,
		.alg.skcipher = अणु
			.base.cra_name = "cbc(aes)",
			.base.cra_driver_name = "cbc-aes-talitos",
			.base.cra_blocksize = AES_BLOCK_SIZE,
			.base.cra_flags = CRYPTO_ALG_ASYNC |
					  CRYPTO_ALG_ALLOCATES_MEMORY,
			.min_keysize = AES_MIN_KEY_SIZE,
			.max_keysize = AES_MAX_KEY_SIZE,
			.ivsize = AES_BLOCK_SIZE,
			.setkey = skcipher_aes_setkey,
		पूर्ण,
		.desc_hdr_ढाँचा = DESC_HDR_TYPE_COMMON_NONSNOOP_NO_AFEU |
				     DESC_HDR_SEL0_AESU |
				     DESC_HDR_MODE0_AESU_CBC,
	पूर्ण,
	अणु	.type = CRYPTO_ALG_TYPE_SKCIPHER,
		.alg.skcipher = अणु
			.base.cra_name = "ctr(aes)",
			.base.cra_driver_name = "ctr-aes-talitos",
			.base.cra_blocksize = 1,
			.base.cra_flags = CRYPTO_ALG_ASYNC |
					  CRYPTO_ALG_ALLOCATES_MEMORY,
			.min_keysize = AES_MIN_KEY_SIZE,
			.max_keysize = AES_MAX_KEY_SIZE,
			.ivsize = AES_BLOCK_SIZE,
			.setkey = skcipher_aes_setkey,
		पूर्ण,
		.desc_hdr_ढाँचा = DESC_HDR_TYPE_AESU_CTR_NONSNOOP |
				     DESC_HDR_SEL0_AESU |
				     DESC_HDR_MODE0_AESU_CTR,
	पूर्ण,
	अणु	.type = CRYPTO_ALG_TYPE_SKCIPHER,
		.alg.skcipher = अणु
			.base.cra_name = "ctr(aes)",
			.base.cra_driver_name = "ctr-aes-talitos",
			.base.cra_blocksize = 1,
			.base.cra_flags = CRYPTO_ALG_ASYNC |
					  CRYPTO_ALG_ALLOCATES_MEMORY,
			.min_keysize = AES_MIN_KEY_SIZE,
			.max_keysize = AES_MAX_KEY_SIZE,
			.ivsize = AES_BLOCK_SIZE,
			.setkey = skcipher_aes_setkey,
		पूर्ण,
		.desc_hdr_ढाँचा = DESC_HDR_TYPE_COMMON_NONSNOOP_NO_AFEU |
				     DESC_HDR_SEL0_AESU |
				     DESC_HDR_MODE0_AESU_CTR,
	पूर्ण,
	अणु	.type = CRYPTO_ALG_TYPE_SKCIPHER,
		.alg.skcipher = अणु
			.base.cra_name = "ecb(des)",
			.base.cra_driver_name = "ecb-des-talitos",
			.base.cra_blocksize = DES_BLOCK_SIZE,
			.base.cra_flags = CRYPTO_ALG_ASYNC |
					  CRYPTO_ALG_ALLOCATES_MEMORY,
			.min_keysize = DES_KEY_SIZE,
			.max_keysize = DES_KEY_SIZE,
			.setkey = skcipher_des_setkey,
		पूर्ण,
		.desc_hdr_ढाँचा = DESC_HDR_TYPE_COMMON_NONSNOOP_NO_AFEU |
				     DESC_HDR_SEL0_DEU,
	पूर्ण,
	अणु	.type = CRYPTO_ALG_TYPE_SKCIPHER,
		.alg.skcipher = अणु
			.base.cra_name = "cbc(des)",
			.base.cra_driver_name = "cbc-des-talitos",
			.base.cra_blocksize = DES_BLOCK_SIZE,
			.base.cra_flags = CRYPTO_ALG_ASYNC |
					  CRYPTO_ALG_ALLOCATES_MEMORY,
			.min_keysize = DES_KEY_SIZE,
			.max_keysize = DES_KEY_SIZE,
			.ivsize = DES_BLOCK_SIZE,
			.setkey = skcipher_des_setkey,
		पूर्ण,
		.desc_hdr_ढाँचा = DESC_HDR_TYPE_COMMON_NONSNOOP_NO_AFEU |
				     DESC_HDR_SEL0_DEU |
				     DESC_HDR_MODE0_DEU_CBC,
	पूर्ण,
	अणु	.type = CRYPTO_ALG_TYPE_SKCIPHER,
		.alg.skcipher = अणु
			.base.cra_name = "ecb(des3_ede)",
			.base.cra_driver_name = "ecb-3des-talitos",
			.base.cra_blocksize = DES3_EDE_BLOCK_SIZE,
			.base.cra_flags = CRYPTO_ALG_ASYNC |
					  CRYPTO_ALG_ALLOCATES_MEMORY,
			.min_keysize = DES3_EDE_KEY_SIZE,
			.max_keysize = DES3_EDE_KEY_SIZE,
			.setkey = skcipher_des3_setkey,
		पूर्ण,
		.desc_hdr_ढाँचा = DESC_HDR_TYPE_COMMON_NONSNOOP_NO_AFEU |
				     DESC_HDR_SEL0_DEU |
				     DESC_HDR_MODE0_DEU_3DES,
	पूर्ण,
	अणु	.type = CRYPTO_ALG_TYPE_SKCIPHER,
		.alg.skcipher = अणु
			.base.cra_name = "cbc(des3_ede)",
			.base.cra_driver_name = "cbc-3des-talitos",
			.base.cra_blocksize = DES3_EDE_BLOCK_SIZE,
			.base.cra_flags = CRYPTO_ALG_ASYNC |
					  CRYPTO_ALG_ALLOCATES_MEMORY,
			.min_keysize = DES3_EDE_KEY_SIZE,
			.max_keysize = DES3_EDE_KEY_SIZE,
			.ivsize = DES3_EDE_BLOCK_SIZE,
			.setkey = skcipher_des3_setkey,
		पूर्ण,
		.desc_hdr_ढाँचा = DESC_HDR_TYPE_COMMON_NONSNOOP_NO_AFEU |
			             DESC_HDR_SEL0_DEU |
		                     DESC_HDR_MODE0_DEU_CBC |
		                     DESC_HDR_MODE0_DEU_3DES,
	पूर्ण,
	/* AHASH algorithms. */
	अणु	.type = CRYPTO_ALG_TYPE_AHASH,
		.alg.hash = अणु
			.halg.digestsize = MD5_DIGEST_SIZE,
			.halg.statesize = माप(काष्ठा talitos_export_state),
			.halg.base = अणु
				.cra_name = "md5",
				.cra_driver_name = "md5-talitos",
				.cra_blocksize = MD5_HMAC_BLOCK_SIZE,
				.cra_flags = CRYPTO_ALG_ASYNC |
					     CRYPTO_ALG_ALLOCATES_MEMORY,
			पूर्ण
		पूर्ण,
		.desc_hdr_ढाँचा = DESC_HDR_TYPE_COMMON_NONSNOOP_NO_AFEU |
				     DESC_HDR_SEL0_MDEUA |
				     DESC_HDR_MODE0_MDEU_MD5,
	पूर्ण,
	अणु	.type = CRYPTO_ALG_TYPE_AHASH,
		.alg.hash = अणु
			.halg.digestsize = SHA1_DIGEST_SIZE,
			.halg.statesize = माप(काष्ठा talitos_export_state),
			.halg.base = अणु
				.cra_name = "sha1",
				.cra_driver_name = "sha1-talitos",
				.cra_blocksize = SHA1_BLOCK_SIZE,
				.cra_flags = CRYPTO_ALG_ASYNC |
					     CRYPTO_ALG_ALLOCATES_MEMORY,
			पूर्ण
		पूर्ण,
		.desc_hdr_ढाँचा = DESC_HDR_TYPE_COMMON_NONSNOOP_NO_AFEU |
				     DESC_HDR_SEL0_MDEUA |
				     DESC_HDR_MODE0_MDEU_SHA1,
	पूर्ण,
	अणु	.type = CRYPTO_ALG_TYPE_AHASH,
		.alg.hash = अणु
			.halg.digestsize = SHA224_DIGEST_SIZE,
			.halg.statesize = माप(काष्ठा talitos_export_state),
			.halg.base = अणु
				.cra_name = "sha224",
				.cra_driver_name = "sha224-talitos",
				.cra_blocksize = SHA224_BLOCK_SIZE,
				.cra_flags = CRYPTO_ALG_ASYNC |
					     CRYPTO_ALG_ALLOCATES_MEMORY,
			पूर्ण
		पूर्ण,
		.desc_hdr_ढाँचा = DESC_HDR_TYPE_COMMON_NONSNOOP_NO_AFEU |
				     DESC_HDR_SEL0_MDEUA |
				     DESC_HDR_MODE0_MDEU_SHA224,
	पूर्ण,
	अणु	.type = CRYPTO_ALG_TYPE_AHASH,
		.alg.hash = अणु
			.halg.digestsize = SHA256_DIGEST_SIZE,
			.halg.statesize = माप(काष्ठा talitos_export_state),
			.halg.base = अणु
				.cra_name = "sha256",
				.cra_driver_name = "sha256-talitos",
				.cra_blocksize = SHA256_BLOCK_SIZE,
				.cra_flags = CRYPTO_ALG_ASYNC |
					     CRYPTO_ALG_ALLOCATES_MEMORY,
			पूर्ण
		पूर्ण,
		.desc_hdr_ढाँचा = DESC_HDR_TYPE_COMMON_NONSNOOP_NO_AFEU |
				     DESC_HDR_SEL0_MDEUA |
				     DESC_HDR_MODE0_MDEU_SHA256,
	पूर्ण,
	अणु	.type = CRYPTO_ALG_TYPE_AHASH,
		.alg.hash = अणु
			.halg.digestsize = SHA384_DIGEST_SIZE,
			.halg.statesize = माप(काष्ठा talitos_export_state),
			.halg.base = अणु
				.cra_name = "sha384",
				.cra_driver_name = "sha384-talitos",
				.cra_blocksize = SHA384_BLOCK_SIZE,
				.cra_flags = CRYPTO_ALG_ASYNC |
					     CRYPTO_ALG_ALLOCATES_MEMORY,
			पूर्ण
		पूर्ण,
		.desc_hdr_ढाँचा = DESC_HDR_TYPE_COMMON_NONSNOOP_NO_AFEU |
				     DESC_HDR_SEL0_MDEUB |
				     DESC_HDR_MODE0_MDEUB_SHA384,
	पूर्ण,
	अणु	.type = CRYPTO_ALG_TYPE_AHASH,
		.alg.hash = अणु
			.halg.digestsize = SHA512_DIGEST_SIZE,
			.halg.statesize = माप(काष्ठा talitos_export_state),
			.halg.base = अणु
				.cra_name = "sha512",
				.cra_driver_name = "sha512-talitos",
				.cra_blocksize = SHA512_BLOCK_SIZE,
				.cra_flags = CRYPTO_ALG_ASYNC |
					     CRYPTO_ALG_ALLOCATES_MEMORY,
			पूर्ण
		पूर्ण,
		.desc_hdr_ढाँचा = DESC_HDR_TYPE_COMMON_NONSNOOP_NO_AFEU |
				     DESC_HDR_SEL0_MDEUB |
				     DESC_HDR_MODE0_MDEUB_SHA512,
	पूर्ण,
	अणु	.type = CRYPTO_ALG_TYPE_AHASH,
		.alg.hash = अणु
			.halg.digestsize = MD5_DIGEST_SIZE,
			.halg.statesize = माप(काष्ठा talitos_export_state),
			.halg.base = अणु
				.cra_name = "hmac(md5)",
				.cra_driver_name = "hmac-md5-talitos",
				.cra_blocksize = MD5_HMAC_BLOCK_SIZE,
				.cra_flags = CRYPTO_ALG_ASYNC |
					     CRYPTO_ALG_ALLOCATES_MEMORY,
			पूर्ण
		पूर्ण,
		.desc_hdr_ढाँचा = DESC_HDR_TYPE_COMMON_NONSNOOP_NO_AFEU |
				     DESC_HDR_SEL0_MDEUA |
				     DESC_HDR_MODE0_MDEU_MD5,
	पूर्ण,
	अणु	.type = CRYPTO_ALG_TYPE_AHASH,
		.alg.hash = अणु
			.halg.digestsize = SHA1_DIGEST_SIZE,
			.halg.statesize = माप(काष्ठा talitos_export_state),
			.halg.base = अणु
				.cra_name = "hmac(sha1)",
				.cra_driver_name = "hmac-sha1-talitos",
				.cra_blocksize = SHA1_BLOCK_SIZE,
				.cra_flags = CRYPTO_ALG_ASYNC |
					     CRYPTO_ALG_ALLOCATES_MEMORY,
			पूर्ण
		पूर्ण,
		.desc_hdr_ढाँचा = DESC_HDR_TYPE_COMMON_NONSNOOP_NO_AFEU |
				     DESC_HDR_SEL0_MDEUA |
				     DESC_HDR_MODE0_MDEU_SHA1,
	पूर्ण,
	अणु	.type = CRYPTO_ALG_TYPE_AHASH,
		.alg.hash = अणु
			.halg.digestsize = SHA224_DIGEST_SIZE,
			.halg.statesize = माप(काष्ठा talitos_export_state),
			.halg.base = अणु
				.cra_name = "hmac(sha224)",
				.cra_driver_name = "hmac-sha224-talitos",
				.cra_blocksize = SHA224_BLOCK_SIZE,
				.cra_flags = CRYPTO_ALG_ASYNC |
					     CRYPTO_ALG_ALLOCATES_MEMORY,
			पूर्ण
		पूर्ण,
		.desc_hdr_ढाँचा = DESC_HDR_TYPE_COMMON_NONSNOOP_NO_AFEU |
				     DESC_HDR_SEL0_MDEUA |
				     DESC_HDR_MODE0_MDEU_SHA224,
	पूर्ण,
	अणु	.type = CRYPTO_ALG_TYPE_AHASH,
		.alg.hash = अणु
			.halg.digestsize = SHA256_DIGEST_SIZE,
			.halg.statesize = माप(काष्ठा talitos_export_state),
			.halg.base = अणु
				.cra_name = "hmac(sha256)",
				.cra_driver_name = "hmac-sha256-talitos",
				.cra_blocksize = SHA256_BLOCK_SIZE,
				.cra_flags = CRYPTO_ALG_ASYNC |
					     CRYPTO_ALG_ALLOCATES_MEMORY,
			पूर्ण
		पूर्ण,
		.desc_hdr_ढाँचा = DESC_HDR_TYPE_COMMON_NONSNOOP_NO_AFEU |
				     DESC_HDR_SEL0_MDEUA |
				     DESC_HDR_MODE0_MDEU_SHA256,
	पूर्ण,
	अणु	.type = CRYPTO_ALG_TYPE_AHASH,
		.alg.hash = अणु
			.halg.digestsize = SHA384_DIGEST_SIZE,
			.halg.statesize = माप(काष्ठा talitos_export_state),
			.halg.base = अणु
				.cra_name = "hmac(sha384)",
				.cra_driver_name = "hmac-sha384-talitos",
				.cra_blocksize = SHA384_BLOCK_SIZE,
				.cra_flags = CRYPTO_ALG_ASYNC |
					     CRYPTO_ALG_ALLOCATES_MEMORY,
			पूर्ण
		पूर्ण,
		.desc_hdr_ढाँचा = DESC_HDR_TYPE_COMMON_NONSNOOP_NO_AFEU |
				     DESC_HDR_SEL0_MDEUB |
				     DESC_HDR_MODE0_MDEUB_SHA384,
	पूर्ण,
	अणु	.type = CRYPTO_ALG_TYPE_AHASH,
		.alg.hash = अणु
			.halg.digestsize = SHA512_DIGEST_SIZE,
			.halg.statesize = माप(काष्ठा talitos_export_state),
			.halg.base = अणु
				.cra_name = "hmac(sha512)",
				.cra_driver_name = "hmac-sha512-talitos",
				.cra_blocksize = SHA512_BLOCK_SIZE,
				.cra_flags = CRYPTO_ALG_ASYNC |
					     CRYPTO_ALG_ALLOCATES_MEMORY,
			पूर्ण
		पूर्ण,
		.desc_hdr_ढाँचा = DESC_HDR_TYPE_COMMON_NONSNOOP_NO_AFEU |
				     DESC_HDR_SEL0_MDEUB |
				     DESC_HDR_MODE0_MDEUB_SHA512,
	पूर्ण
पूर्ण;

काष्ठा talitos_crypto_alg अणु
	काष्ठा list_head entry;
	काष्ठा device *dev;
	काष्ठा talitos_alg_ढाँचा algt;
पूर्ण;

अटल पूर्णांक talitos_init_common(काष्ठा talitos_ctx *ctx,
			       काष्ठा talitos_crypto_alg *talitos_alg)
अणु
	काष्ठा talitos_निजी *priv;

	/* update context with ptr to dev */
	ctx->dev = talitos_alg->dev;

	/* assign SEC channel to tfm in round-robin fashion */
	priv = dev_get_drvdata(ctx->dev);
	ctx->ch = atomic_inc_वापस(&priv->last_chan) &
		  (priv->num_channels - 1);

	/* copy descriptor header ढाँचा value */
	ctx->desc_hdr_ढाँचा = talitos_alg->algt.desc_hdr_ढाँचा;

	/* select करोne notअगरication */
	ctx->desc_hdr_ढाँचा |= DESC_HDR_DONE_NOTIFY;

	वापस 0;
पूर्ण

अटल पूर्णांक talitos_cra_init_aead(काष्ठा crypto_aead *tfm)
अणु
	काष्ठा aead_alg *alg = crypto_aead_alg(tfm);
	काष्ठा talitos_crypto_alg *talitos_alg;
	काष्ठा talitos_ctx *ctx = crypto_aead_ctx(tfm);

	talitos_alg = container_of(alg, काष्ठा talitos_crypto_alg,
				   algt.alg.aead);

	वापस talitos_init_common(ctx, talitos_alg);
पूर्ण

अटल पूर्णांक talitos_cra_init_skcipher(काष्ठा crypto_skcipher *tfm)
अणु
	काष्ठा skcipher_alg *alg = crypto_skcipher_alg(tfm);
	काष्ठा talitos_crypto_alg *talitos_alg;
	काष्ठा talitos_ctx *ctx = crypto_skcipher_ctx(tfm);

	talitos_alg = container_of(alg, काष्ठा talitos_crypto_alg,
				   algt.alg.skcipher);

	वापस talitos_init_common(ctx, talitos_alg);
पूर्ण

अटल पूर्णांक talitos_cra_init_ahash(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा crypto_alg *alg = tfm->__crt_alg;
	काष्ठा talitos_crypto_alg *talitos_alg;
	काष्ठा talitos_ctx *ctx = crypto_tfm_ctx(tfm);

	talitos_alg = container_of(__crypto_ahash_alg(alg),
				   काष्ठा talitos_crypto_alg,
				   algt.alg.hash);

	ctx->keylen = 0;
	crypto_ahash_set_reqsize(__crypto_ahash_cast(tfm),
				 माप(काष्ठा talitos_ahash_req_ctx));

	वापस talitos_init_common(ctx, talitos_alg);
पूर्ण

अटल व्योम talitos_cra_निकास(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा talitos_ctx *ctx = crypto_tfm_ctx(tfm);
	काष्ठा device *dev = ctx->dev;

	अगर (ctx->keylen)
		dma_unmap_single(dev, ctx->dma_key, ctx->keylen, DMA_TO_DEVICE);
पूर्ण

/*
 * given the alg's descriptor header ढाँचा, determine whether descriptor
 * type and primary/secondary execution units required match the hw
 * capabilities description provided in the device tree node.
 */
अटल पूर्णांक hw_supports(काष्ठा device *dev, __be32 desc_hdr_ढाँचा)
अणु
	काष्ठा talitos_निजी *priv = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = (1 << DESC_TYPE(desc_hdr_ढाँचा) & priv->desc_types) &&
	      (1 << PRIMARY_EU(desc_hdr_ढाँचा) & priv->exec_units);

	अगर (SECONDARY_EU(desc_hdr_ढाँचा))
		ret = ret && (1 << SECONDARY_EU(desc_hdr_ढाँचा)
		              & priv->exec_units);

	वापस ret;
पूर्ण

अटल पूर्णांक talitos_हटाओ(काष्ठा platक्रमm_device *ofdev)
अणु
	काष्ठा device *dev = &ofdev->dev;
	काष्ठा talitos_निजी *priv = dev_get_drvdata(dev);
	काष्ठा talitos_crypto_alg *t_alg, *n;
	पूर्णांक i;

	list_क्रम_each_entry_safe(t_alg, n, &priv->alg_list, entry) अणु
		चयन (t_alg->algt.type) अणु
		हाल CRYPTO_ALG_TYPE_SKCIPHER:
			crypto_unरेजिस्टर_skcipher(&t_alg->algt.alg.skcipher);
			अवरोध;
		हाल CRYPTO_ALG_TYPE_AEAD:
			crypto_unरेजिस्टर_aead(&t_alg->algt.alg.aead);
			अवरोध;
		हाल CRYPTO_ALG_TYPE_AHASH:
			crypto_unरेजिस्टर_ahash(&t_alg->algt.alg.hash);
			अवरोध;
		पूर्ण
		list_del(&t_alg->entry);
	पूर्ण

	अगर (hw_supports(dev, DESC_HDR_SEL0_RNG))
		talitos_unरेजिस्टर_rng(dev);

	क्रम (i = 0; i < 2; i++)
		अगर (priv->irq[i]) अणु
			मुक्त_irq(priv->irq[i], dev);
			irq_dispose_mapping(priv->irq[i]);
		पूर्ण

	tasklet_समाप्त(&priv->करोne_task[0]);
	अगर (priv->irq[1])
		tasklet_समाप्त(&priv->करोne_task[1]);

	वापस 0;
पूर्ण

अटल काष्ठा talitos_crypto_alg *talitos_alg_alloc(काष्ठा device *dev,
						    काष्ठा talitos_alg_ढाँचा
						           *ढाँचा)
अणु
	काष्ठा talitos_निजी *priv = dev_get_drvdata(dev);
	काष्ठा talitos_crypto_alg *t_alg;
	काष्ठा crypto_alg *alg;

	t_alg = devm_kzalloc(dev, माप(काष्ठा talitos_crypto_alg),
			     GFP_KERNEL);
	अगर (!t_alg)
		वापस ERR_PTR(-ENOMEM);

	t_alg->algt = *ढाँचा;

	चयन (t_alg->algt.type) अणु
	हाल CRYPTO_ALG_TYPE_SKCIPHER:
		alg = &t_alg->algt.alg.skcipher.base;
		alg->cra_निकास = talitos_cra_निकास;
		t_alg->algt.alg.skcipher.init = talitos_cra_init_skcipher;
		t_alg->algt.alg.skcipher.setkey =
			t_alg->algt.alg.skcipher.setkey ?: skcipher_setkey;
		t_alg->algt.alg.skcipher.encrypt = skcipher_encrypt;
		t_alg->algt.alg.skcipher.decrypt = skcipher_decrypt;
		अगर (!म_भेद(alg->cra_name, "ctr(aes)") && !has_ftr_sec1(priv) &&
		    DESC_TYPE(t_alg->algt.desc_hdr_ढाँचा) !=
		    DESC_TYPE(DESC_HDR_TYPE_AESU_CTR_NONSNOOP)) अणु
			devm_kमुक्त(dev, t_alg);
			वापस ERR_PTR(-ENOTSUPP);
		पूर्ण
		अवरोध;
	हाल CRYPTO_ALG_TYPE_AEAD:
		alg = &t_alg->algt.alg.aead.base;
		alg->cra_निकास = talitos_cra_निकास;
		t_alg->algt.alg.aead.init = talitos_cra_init_aead;
		t_alg->algt.alg.aead.setkey = t_alg->algt.alg.aead.setkey ?:
					      aead_setkey;
		t_alg->algt.alg.aead.encrypt = aead_encrypt;
		t_alg->algt.alg.aead.decrypt = aead_decrypt;
		अगर (!(priv->features & TALITOS_FTR_SHA224_HWINIT) &&
		    !म_भेदन(alg->cra_name, "authenc(hmac(sha224)", 20)) अणु
			devm_kमुक्त(dev, t_alg);
			वापस ERR_PTR(-ENOTSUPP);
		पूर्ण
		अवरोध;
	हाल CRYPTO_ALG_TYPE_AHASH:
		alg = &t_alg->algt.alg.hash.halg.base;
		alg->cra_init = talitos_cra_init_ahash;
		alg->cra_निकास = talitos_cra_निकास;
		t_alg->algt.alg.hash.init = ahash_init;
		t_alg->algt.alg.hash.update = ahash_update;
		t_alg->algt.alg.hash.final = ahash_final;
		t_alg->algt.alg.hash.finup = ahash_finup;
		t_alg->algt.alg.hash.digest = ahash_digest;
		अगर (!म_भेदन(alg->cra_name, "hmac", 4))
			t_alg->algt.alg.hash.setkey = ahash_setkey;
		t_alg->algt.alg.hash.import = ahash_import;
		t_alg->algt.alg.hash.export = ahash_export;

		अगर (!(priv->features & TALITOS_FTR_HMAC_OK) &&
		    !म_भेदन(alg->cra_name, "hmac", 4)) अणु
			devm_kमुक्त(dev, t_alg);
			वापस ERR_PTR(-ENOTSUPP);
		पूर्ण
		अगर (!(priv->features & TALITOS_FTR_SHA224_HWINIT) &&
		    (!म_भेद(alg->cra_name, "sha224") ||
		     !म_भेद(alg->cra_name, "hmac(sha224)"))) अणु
			t_alg->algt.alg.hash.init = ahash_init_sha224_swinit;
			t_alg->algt.desc_hdr_ढाँचा =
					DESC_HDR_TYPE_COMMON_NONSNOOP_NO_AFEU |
					DESC_HDR_SEL0_MDEUA |
					DESC_HDR_MODE0_MDEU_SHA256;
		पूर्ण
		अवरोध;
	शेष:
		dev_err(dev, "unknown algorithm type %d\n", t_alg->algt.type);
		devm_kमुक्त(dev, t_alg);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	alg->cra_module = THIS_MODULE;
	अगर (t_alg->algt.priority)
		alg->cra_priority = t_alg->algt.priority;
	अन्यथा
		alg->cra_priority = TALITOS_CRA_PRIORITY;
	अगर (has_ftr_sec1(priv))
		alg->cra_alignmask = 3;
	अन्यथा
		alg->cra_alignmask = 0;
	alg->cra_ctxsize = माप(काष्ठा talitos_ctx);
	alg->cra_flags |= CRYPTO_ALG_KERN_DRIVER_ONLY;

	t_alg->dev = dev;

	वापस t_alg;
पूर्ण

अटल पूर्णांक talitos_probe_irq(काष्ठा platक्रमm_device *ofdev)
अणु
	काष्ठा device *dev = &ofdev->dev;
	काष्ठा device_node *np = ofdev->dev.of_node;
	काष्ठा talitos_निजी *priv = dev_get_drvdata(dev);
	पूर्णांक err;
	bool is_sec1 = has_ftr_sec1(priv);

	priv->irq[0] = irq_of_parse_and_map(np, 0);
	अगर (!priv->irq[0]) अणु
		dev_err(dev, "failed to map irq\n");
		वापस -EINVAL;
	पूर्ण
	अगर (is_sec1) अणु
		err = request_irq(priv->irq[0], talitos1_पूर्णांकerrupt_4ch, 0,
				  dev_driver_string(dev), dev);
		जाओ primary_out;
	पूर्ण

	priv->irq[1] = irq_of_parse_and_map(np, 1);

	/* get the primary irq line */
	अगर (!priv->irq[1]) अणु
		err = request_irq(priv->irq[0], talitos2_पूर्णांकerrupt_4ch, 0,
				  dev_driver_string(dev), dev);
		जाओ primary_out;
	पूर्ण

	err = request_irq(priv->irq[0], talitos2_पूर्णांकerrupt_ch0_2, 0,
			  dev_driver_string(dev), dev);
	अगर (err)
		जाओ primary_out;

	/* get the secondary irq line */
	err = request_irq(priv->irq[1], talitos2_पूर्णांकerrupt_ch1_3, 0,
			  dev_driver_string(dev), dev);
	अगर (err) अणु
		dev_err(dev, "failed to request secondary irq\n");
		irq_dispose_mapping(priv->irq[1]);
		priv->irq[1] = 0;
	पूर्ण

	वापस err;

primary_out:
	अगर (err) अणु
		dev_err(dev, "failed to request primary irq\n");
		irq_dispose_mapping(priv->irq[0]);
		priv->irq[0] = 0;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक talitos_probe(काष्ठा platक्रमm_device *ofdev)
अणु
	काष्ठा device *dev = &ofdev->dev;
	काष्ठा device_node *np = ofdev->dev.of_node;
	काष्ठा talitos_निजी *priv;
	पूर्णांक i, err;
	पूर्णांक stride;
	काष्ठा resource *res;

	priv = devm_kzalloc(dev, माप(काष्ठा talitos_निजी), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	INIT_LIST_HEAD(&priv->alg_list);

	dev_set_drvdata(dev, priv);

	priv->ofdev = ofdev;

	spin_lock_init(&priv->reg_lock);

	res = platक्रमm_get_resource(ofdev, IORESOURCE_MEM, 0);
	अगर (!res)
		वापस -ENXIO;
	priv->reg = devm_ioremap(dev, res->start, resource_size(res));
	अगर (!priv->reg) अणु
		dev_err(dev, "failed to of_iomap\n");
		err = -ENOMEM;
		जाओ err_out;
	पूर्ण

	/* get SEC version capabilities from device tree */
	of_property_पढ़ो_u32(np, "fsl,num-channels", &priv->num_channels);
	of_property_पढ़ो_u32(np, "fsl,channel-fifo-len", &priv->chfअगरo_len);
	of_property_पढ़ो_u32(np, "fsl,exec-units-mask", &priv->exec_units);
	of_property_पढ़ो_u32(np, "fsl,descriptor-types-mask",
			     &priv->desc_types);

	अगर (!is_घातer_of_2(priv->num_channels) || !priv->chfअगरo_len ||
	    !priv->exec_units || !priv->desc_types) अणु
		dev_err(dev, "invalid property data in device tree node\n");
		err = -EINVAL;
		जाओ err_out;
	पूर्ण

	अगर (of_device_is_compatible(np, "fsl,sec3.0"))
		priv->features |= TALITOS_FTR_SRC_LINK_TBL_LEN_INCLUDES_EXTENT;

	अगर (of_device_is_compatible(np, "fsl,sec2.1"))
		priv->features |= TALITOS_FTR_HW_AUTH_CHECK |
				  TALITOS_FTR_SHA224_HWINIT |
				  TALITOS_FTR_HMAC_OK;

	अगर (of_device_is_compatible(np, "fsl,sec1.0"))
		priv->features |= TALITOS_FTR_SEC1;

	अगर (of_device_is_compatible(np, "fsl,sec1.2")) अणु
		priv->reg_deu = priv->reg + TALITOS12_DEU;
		priv->reg_aesu = priv->reg + TALITOS12_AESU;
		priv->reg_mdeu = priv->reg + TALITOS12_MDEU;
		stride = TALITOS1_CH_STRIDE;
	पूर्ण अन्यथा अगर (of_device_is_compatible(np, "fsl,sec1.0")) अणु
		priv->reg_deu = priv->reg + TALITOS10_DEU;
		priv->reg_aesu = priv->reg + TALITOS10_AESU;
		priv->reg_mdeu = priv->reg + TALITOS10_MDEU;
		priv->reg_afeu = priv->reg + TALITOS10_AFEU;
		priv->reg_rngu = priv->reg + TALITOS10_RNGU;
		priv->reg_pkeu = priv->reg + TALITOS10_PKEU;
		stride = TALITOS1_CH_STRIDE;
	पूर्ण अन्यथा अणु
		priv->reg_deu = priv->reg + TALITOS2_DEU;
		priv->reg_aesu = priv->reg + TALITOS2_AESU;
		priv->reg_mdeu = priv->reg + TALITOS2_MDEU;
		priv->reg_afeu = priv->reg + TALITOS2_AFEU;
		priv->reg_rngu = priv->reg + TALITOS2_RNGU;
		priv->reg_pkeu = priv->reg + TALITOS2_PKEU;
		priv->reg_keu = priv->reg + TALITOS2_KEU;
		priv->reg_crcu = priv->reg + TALITOS2_CRCU;
		stride = TALITOS2_CH_STRIDE;
	पूर्ण

	err = talitos_probe_irq(ofdev);
	अगर (err)
		जाओ err_out;

	अगर (has_ftr_sec1(priv)) अणु
		अगर (priv->num_channels == 1)
			tasklet_init(&priv->करोne_task[0], talitos1_करोne_ch0,
				     (अचिन्हित दीर्घ)dev);
		अन्यथा
			tasklet_init(&priv->करोne_task[0], talitos1_करोne_4ch,
				     (अचिन्हित दीर्घ)dev);
	पूर्ण अन्यथा अणु
		अगर (priv->irq[1]) अणु
			tasklet_init(&priv->करोne_task[0], talitos2_करोne_ch0_2,
				     (अचिन्हित दीर्घ)dev);
			tasklet_init(&priv->करोne_task[1], talitos2_करोne_ch1_3,
				     (अचिन्हित दीर्घ)dev);
		पूर्ण अन्यथा अगर (priv->num_channels == 1) अणु
			tasklet_init(&priv->करोne_task[0], talitos2_करोne_ch0,
				     (अचिन्हित दीर्घ)dev);
		पूर्ण अन्यथा अणु
			tasklet_init(&priv->करोne_task[0], talitos2_करोne_4ch,
				     (अचिन्हित दीर्घ)dev);
		पूर्ण
	पूर्ण

	priv->chan = devm_kसुस्मृति(dev,
				  priv->num_channels,
				  माप(काष्ठा talitos_channel),
				  GFP_KERNEL);
	अगर (!priv->chan) अणु
		dev_err(dev, "failed to allocate channel management space\n");
		err = -ENOMEM;
		जाओ err_out;
	पूर्ण

	priv->fअगरo_len = roundup_घात_of_two(priv->chfअगरo_len);

	क्रम (i = 0; i < priv->num_channels; i++) अणु
		priv->chan[i].reg = priv->reg + stride * (i + 1);
		अगर (!priv->irq[1] || !(i & 1))
			priv->chan[i].reg += TALITOS_CH_BASE_OFFSET;

		spin_lock_init(&priv->chan[i].head_lock);
		spin_lock_init(&priv->chan[i].tail_lock);

		priv->chan[i].fअगरo = devm_kसुस्मृति(dev,
						priv->fअगरo_len,
						माप(काष्ठा talitos_request),
						GFP_KERNEL);
		अगर (!priv->chan[i].fअगरo) अणु
			dev_err(dev, "failed to allocate request fifo %d\n", i);
			err = -ENOMEM;
			जाओ err_out;
		पूर्ण

		atomic_set(&priv->chan[i].submit_count,
			   -(priv->chfअगरo_len - 1));
	पूर्ण

	dma_set_mask(dev, DMA_BIT_MASK(36));

	/* reset and initialize the h/w */
	err = init_device(dev);
	अगर (err) अणु
		dev_err(dev, "failed to initialize device\n");
		जाओ err_out;
	पूर्ण

	/* रेजिस्टर the RNG, अगर available */
	अगर (hw_supports(dev, DESC_HDR_SEL0_RNG)) अणु
		err = talitos_रेजिस्टर_rng(dev);
		अगर (err) अणु
			dev_err(dev, "failed to register hwrng: %d\n", err);
			जाओ err_out;
		पूर्ण अन्यथा
			dev_info(dev, "hwrng\n");
	पूर्ण

	/* रेजिस्टर crypto algorithms the device supports */
	क्रम (i = 0; i < ARRAY_SIZE(driver_algs); i++) अणु
		अगर (hw_supports(dev, driver_algs[i].desc_hdr_ढाँचा)) अणु
			काष्ठा talitos_crypto_alg *t_alg;
			काष्ठा crypto_alg *alg = शून्य;

			t_alg = talitos_alg_alloc(dev, &driver_algs[i]);
			अगर (IS_ERR(t_alg)) अणु
				err = PTR_ERR(t_alg);
				अगर (err == -ENOTSUPP)
					जारी;
				जाओ err_out;
			पूर्ण

			चयन (t_alg->algt.type) अणु
			हाल CRYPTO_ALG_TYPE_SKCIPHER:
				err = crypto_रेजिस्टर_skcipher(
						&t_alg->algt.alg.skcipher);
				alg = &t_alg->algt.alg.skcipher.base;
				अवरोध;

			हाल CRYPTO_ALG_TYPE_AEAD:
				err = crypto_रेजिस्टर_aead(
					&t_alg->algt.alg.aead);
				alg = &t_alg->algt.alg.aead.base;
				अवरोध;

			हाल CRYPTO_ALG_TYPE_AHASH:
				err = crypto_रेजिस्टर_ahash(
						&t_alg->algt.alg.hash);
				alg = &t_alg->algt.alg.hash.halg.base;
				अवरोध;
			पूर्ण
			अगर (err) अणु
				dev_err(dev, "%s alg registration failed\n",
					alg->cra_driver_name);
				devm_kमुक्त(dev, t_alg);
			पूर्ण अन्यथा
				list_add_tail(&t_alg->entry, &priv->alg_list);
		पूर्ण
	पूर्ण
	अगर (!list_empty(&priv->alg_list))
		dev_info(dev, "%s algorithms registered in /proc/crypto\n",
			 (अक्षर *)of_get_property(np, "compatible", शून्य));

	वापस 0;

err_out:
	talitos_हटाओ(ofdev);

	वापस err;
पूर्ण

अटल स्थिर काष्ठा of_device_id talitos_match[] = अणु
#अगर_घोषित CONFIG_CRYPTO_DEV_TALITOS1
	अणु
		.compatible = "fsl,sec1.0",
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_CRYPTO_DEV_TALITOS2
	अणु
		.compatible = "fsl,sec2.0",
	पूर्ण,
#पूर्ण_अगर
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, talitos_match);

अटल काष्ठा platक्रमm_driver talitos_driver = अणु
	.driver = अणु
		.name = "talitos",
		.of_match_table = talitos_match,
	पूर्ण,
	.probe = talitos_probe,
	.हटाओ = talitos_हटाओ,
पूर्ण;

module_platक्रमm_driver(talitos_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Kim Phillips <kim.phillips@freescale.com>");
MODULE_DESCRIPTION("Freescale integrated security engine (SEC) driver");
