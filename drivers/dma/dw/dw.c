<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) 2007-2008 Aपंचांगel Corporation
// Copyright (C) 2010-2011 ST Microelectronics
// Copyright (C) 2013,2018 Intel Corporation

#समावेश <linux/bitops.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>

#समावेश "internal.h"

अटल व्योम dw_dma_initialize_chan(काष्ठा dw_dma_chan *dwc)
अणु
	काष्ठा dw_dma *dw = to_dw_dma(dwc->chan.device);
	u32 cfghi = is_slave_direction(dwc->direction) ? 0 : DWC_CFGH_FIFO_MODE;
	u32 cfglo = DWC_CFGL_CH_PRIOR(dwc->priority);
	bool hs_polarity = dwc->dws.hs_polarity;

	cfghi |= DWC_CFGH_DST_PER(dwc->dws.dst_id);
	cfghi |= DWC_CFGH_SRC_PER(dwc->dws.src_id);
	cfghi |= DWC_CFGH_PROTCTL(dw->pdata->protctl);

	/* Set polarity of handshake पूर्णांकerface */
	cfglo |= hs_polarity ? DWC_CFGL_HS_DST_POL | DWC_CFGL_HS_SRC_POL : 0;

	channel_ग_लिखोl(dwc, CFG_LO, cfglo);
	channel_ग_लिखोl(dwc, CFG_HI, cfghi);
पूर्ण

अटल व्योम dw_dma_suspend_chan(काष्ठा dw_dma_chan *dwc, bool drain)
अणु
	u32 cfglo = channel_पढ़ोl(dwc, CFG_LO);

	channel_ग_लिखोl(dwc, CFG_LO, cfglo | DWC_CFGL_CH_SUSP);
पूर्ण

अटल व्योम dw_dma_resume_chan(काष्ठा dw_dma_chan *dwc, bool drain)
अणु
	u32 cfglo = channel_पढ़ोl(dwc, CFG_LO);

	channel_ग_लिखोl(dwc, CFG_LO, cfglo & ~DWC_CFGL_CH_SUSP);
पूर्ण

अटल u32 dw_dma_bytes2block(काष्ठा dw_dma_chan *dwc,
			      माप_प्रकार bytes, अचिन्हित पूर्णांक width, माप_प्रकार *len)
अणु
	u32 block;

	अगर ((bytes >> width) > dwc->block_size) अणु
		block = dwc->block_size;
		*len = dwc->block_size << width;
	पूर्ण अन्यथा अणु
		block = bytes >> width;
		*len = bytes;
	पूर्ण

	वापस block;
पूर्ण

अटल माप_प्रकार dw_dma_block2bytes(काष्ठा dw_dma_chan *dwc, u32 block, u32 width)
अणु
	वापस DWC_CTLH_BLOCK_TS(block) << width;
पूर्ण

अटल u32 dw_dma_prepare_ctllo(काष्ठा dw_dma_chan *dwc)
अणु
	काष्ठा dma_slave_config	*sconfig = &dwc->dma_sconfig;
	u8 smsize = (dwc->direction == DMA_DEV_TO_MEM) ? sconfig->src_maxburst : 0;
	u8 dmsize = (dwc->direction == DMA_MEM_TO_DEV) ? sconfig->dst_maxburst : 0;
	u8 p_master = dwc->dws.p_master;
	u8 m_master = dwc->dws.m_master;
	u8 dms = (dwc->direction == DMA_MEM_TO_DEV) ? p_master : m_master;
	u8 sms = (dwc->direction == DMA_DEV_TO_MEM) ? p_master : m_master;

	वापस DWC_CTLL_LLP_D_EN | DWC_CTLL_LLP_S_EN |
	       DWC_CTLL_DST_MSIZE(dmsize) | DWC_CTLL_SRC_MSIZE(smsize) |
	       DWC_CTLL_DMS(dms) | DWC_CTLL_SMS(sms);
पूर्ण

अटल व्योम dw_dma_encode_maxburst(काष्ठा dw_dma_chan *dwc, u32 *maxburst)
अणु
	/*
	 * Fix burst size according to dw_dmac. We need to convert them as:
	 * 1 -> 0, 4 -> 1, 8 -> 2, 16 -> 3.
	 */
	*maxburst = *maxburst > 1 ? fls(*maxburst) - 2 : 0;
पूर्ण

अटल व्योम dw_dma_set_device_name(काष्ठा dw_dma *dw, पूर्णांक id)
अणु
	snम_लिखो(dw->name, माप(dw->name), "dw:dmac%d", id);
पूर्ण

अटल व्योम dw_dma_disable(काष्ठा dw_dma *dw)
अणु
	करो_dw_dma_off(dw);
पूर्ण

अटल व्योम dw_dma_enable(काष्ठा dw_dma *dw)
अणु
	करो_dw_dma_on(dw);
पूर्ण

पूर्णांक dw_dma_probe(काष्ठा dw_dma_chip *chip)
अणु
	काष्ठा dw_dma *dw;

	dw = devm_kzalloc(chip->dev, माप(*dw), GFP_KERNEL);
	अगर (!dw)
		वापस -ENOMEM;

	/* Channel operations */
	dw->initialize_chan = dw_dma_initialize_chan;
	dw->suspend_chan = dw_dma_suspend_chan;
	dw->resume_chan = dw_dma_resume_chan;
	dw->prepare_ctllo = dw_dma_prepare_ctllo;
	dw->encode_maxburst = dw_dma_encode_maxburst;
	dw->bytes2block = dw_dma_bytes2block;
	dw->block2bytes = dw_dma_block2bytes;

	/* Device operations */
	dw->set_device_name = dw_dma_set_device_name;
	dw->disable = dw_dma_disable;
	dw->enable = dw_dma_enable;

	chip->dw = dw;
	वापस करो_dma_probe(chip);
पूर्ण
EXPORT_SYMBOL_GPL(dw_dma_probe);

पूर्णांक dw_dma_हटाओ(काष्ठा dw_dma_chip *chip)
अणु
	वापस करो_dma_हटाओ(chip);
पूर्ण
EXPORT_SYMBOL_GPL(dw_dma_हटाओ);
