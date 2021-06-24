<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) 2013,2018 Intel Corporation

#समावेश <linux/bitops.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>

#समावेश "internal.h"

अटल व्योम idma32_initialize_chan(काष्ठा dw_dma_chan *dwc)
अणु
	u32 cfghi = 0;
	u32 cfglo = 0;

	/* Set शेष burst alignment */
	cfglo |= IDMA32C_CFGL_DST_BURST_ALIGN | IDMA32C_CFGL_SRC_BURST_ALIGN;

	/* Low 4 bits of the request lines */
	cfghi |= IDMA32C_CFGH_DST_PER(dwc->dws.dst_id & 0xf);
	cfghi |= IDMA32C_CFGH_SRC_PER(dwc->dws.src_id & 0xf);

	/* Request line extension (2 bits) */
	cfghi |= IDMA32C_CFGH_DST_PER_EXT(dwc->dws.dst_id >> 4 & 0x3);
	cfghi |= IDMA32C_CFGH_SRC_PER_EXT(dwc->dws.src_id >> 4 & 0x3);

	channel_ग_लिखोl(dwc, CFG_LO, cfglo);
	channel_ग_लिखोl(dwc, CFG_HI, cfghi);
पूर्ण

अटल व्योम idma32_suspend_chan(काष्ठा dw_dma_chan *dwc, bool drain)
अणु
	u32 cfglo = channel_पढ़ोl(dwc, CFG_LO);

	अगर (drain)
		cfglo |= IDMA32C_CFGL_CH_DRAIN;

	channel_ग_लिखोl(dwc, CFG_LO, cfglo | DWC_CFGL_CH_SUSP);
पूर्ण

अटल व्योम idma32_resume_chan(काष्ठा dw_dma_chan *dwc, bool drain)
अणु
	u32 cfglo = channel_पढ़ोl(dwc, CFG_LO);

	अगर (drain)
		cfglo &= ~IDMA32C_CFGL_CH_DRAIN;

	channel_ग_लिखोl(dwc, CFG_LO, cfglo & ~DWC_CFGL_CH_SUSP);
पूर्ण

अटल u32 idma32_bytes2block(काष्ठा dw_dma_chan *dwc,
			      माप_प्रकार bytes, अचिन्हित पूर्णांक width, माप_प्रकार *len)
अणु
	u32 block;

	अगर (bytes > dwc->block_size) अणु
		block = dwc->block_size;
		*len = dwc->block_size;
	पूर्ण अन्यथा अणु
		block = bytes;
		*len = bytes;
	पूर्ण

	वापस block;
पूर्ण

अटल माप_प्रकार idma32_block2bytes(काष्ठा dw_dma_chan *dwc, u32 block, u32 width)
अणु
	वापस IDMA32C_CTLH_BLOCK_TS(block);
पूर्ण

अटल u32 idma32_prepare_ctllo(काष्ठा dw_dma_chan *dwc)
अणु
	काष्ठा dma_slave_config	*sconfig = &dwc->dma_sconfig;
	u8 smsize = (dwc->direction == DMA_DEV_TO_MEM) ? sconfig->src_maxburst : 0;
	u8 dmsize = (dwc->direction == DMA_MEM_TO_DEV) ? sconfig->dst_maxburst : 0;

	वापस DWC_CTLL_LLP_D_EN | DWC_CTLL_LLP_S_EN |
	       DWC_CTLL_DST_MSIZE(dmsize) | DWC_CTLL_SRC_MSIZE(smsize);
पूर्ण

अटल व्योम idma32_encode_maxburst(काष्ठा dw_dma_chan *dwc, u32 *maxburst)
अणु
	*maxburst = *maxburst > 1 ? fls(*maxburst) - 1 : 0;
पूर्ण

अटल व्योम idma32_set_device_name(काष्ठा dw_dma *dw, पूर्णांक id)
अणु
	snम_लिखो(dw->name, माप(dw->name), "idma32:dmac%d", id);
पूर्ण

/*
 * Program FIFO size of channels.
 *
 * By शेष full FIFO (512 bytes) is asचिन्हित to channel 0. Here we
 * slice FIFO on equal parts between channels.
 */
अटल व्योम idma32_fअगरo_partition(काष्ठा dw_dma *dw)
अणु
	u64 value = IDMA32C_FP_PSIZE_CH0(64) | IDMA32C_FP_PSIZE_CH1(64) |
		    IDMA32C_FP_UPDATE;
	u64 fअगरo_partition = 0;

	/* Fill FIFO_PARTITION low bits (Channels 0..1, 4..5) */
	fअगरo_partition |= value << 0;

	/* Fill FIFO_PARTITION high bits (Channels 2..3, 6..7) */
	fअगरo_partition |= value << 32;

	/* Program FIFO Partition रेजिस्टरs - 64 bytes per channel */
	idma32_ग_लिखोq(dw, FIFO_PARTITION1, fअगरo_partition);
	idma32_ग_लिखोq(dw, FIFO_PARTITION0, fअगरo_partition);
पूर्ण

अटल व्योम idma32_disable(काष्ठा dw_dma *dw)
अणु
	करो_dw_dma_off(dw);
	idma32_fअगरo_partition(dw);
पूर्ण

अटल व्योम idma32_enable(काष्ठा dw_dma *dw)
अणु
	idma32_fअगरo_partition(dw);
	करो_dw_dma_on(dw);
पूर्ण

पूर्णांक idma32_dma_probe(काष्ठा dw_dma_chip *chip)
अणु
	काष्ठा dw_dma *dw;

	dw = devm_kzalloc(chip->dev, माप(*dw), GFP_KERNEL);
	अगर (!dw)
		वापस -ENOMEM;

	/* Channel operations */
	dw->initialize_chan = idma32_initialize_chan;
	dw->suspend_chan = idma32_suspend_chan;
	dw->resume_chan = idma32_resume_chan;
	dw->prepare_ctllo = idma32_prepare_ctllo;
	dw->encode_maxburst = idma32_encode_maxburst;
	dw->bytes2block = idma32_bytes2block;
	dw->block2bytes = idma32_block2bytes;

	/* Device operations */
	dw->set_device_name = idma32_set_device_name;
	dw->disable = idma32_disable;
	dw->enable = idma32_enable;

	chip->dw = dw;
	वापस करो_dma_probe(chip);
पूर्ण
EXPORT_SYMBOL_GPL(idma32_dma_probe);

पूर्णांक idma32_dma_हटाओ(काष्ठा dw_dma_chip *chip)
अणु
	वापस करो_dma_हटाओ(chip);
पूर्ण
EXPORT_SYMBOL_GPL(idma32_dma_हटाओ);
