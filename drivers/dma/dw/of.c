<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Platक्रमm driver क्रम the Synopsys DesignWare DMA Controller
 *
 * Copyright (C) 2007-2008 Aपंचांगel Corporation
 * Copyright (C) 2010-2011 ST Microelectronics
 * Copyright (C) 2013 Intel Corporation
 */

#समावेश <linux/of.h>
#समावेश <linux/of_dma.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश "internal.h"

अटल काष्ठा dma_chan *dw_dma_of_xlate(काष्ठा of_phandle_args *dma_spec,
					काष्ठा of_dma *ofdma)
अणु
	काष्ठा dw_dma *dw = ofdma->of_dma_data;
	काष्ठा dw_dma_slave slave = अणु
		.dma_dev = dw->dma.dev,
	पूर्ण;
	dma_cap_mask_t cap;

	अगर (dma_spec->args_count < 3 || dma_spec->args_count > 4)
		वापस शून्य;

	slave.src_id = dma_spec->args[0];
	slave.dst_id = dma_spec->args[0];
	slave.m_master = dma_spec->args[1];
	slave.p_master = dma_spec->args[2];
	अगर (dma_spec->args_count >= 4)
		slave.channels = dma_spec->args[3];

	अगर (WARN_ON(slave.src_id >= DW_DMA_MAX_NR_REQUESTS ||
		    slave.dst_id >= DW_DMA_MAX_NR_REQUESTS ||
		    slave.m_master >= dw->pdata->nr_masters ||
		    slave.p_master >= dw->pdata->nr_masters ||
		    slave.channels >= BIT(dw->pdata->nr_channels)))
		वापस शून्य;

	dma_cap_zero(cap);
	dma_cap_set(DMA_SLAVE, cap);

	/* TODO: there should be a simpler way to करो this */
	वापस dma_request_channel(cap, dw_dma_filter, &slave);
पूर्ण

काष्ठा dw_dma_platक्रमm_data *dw_dma_parse_dt(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा dw_dma_platक्रमm_data *pdata;
	u32 पंचांगp, arr[DW_DMA_MAX_NR_MASTERS], mb[DW_DMA_MAX_NR_CHANNELS];
	u32 nr_masters;
	u32 nr_channels;

	अगर (!np) अणु
		dev_err(&pdev->dev, "Missing DT data\n");
		वापस शून्य;
	पूर्ण

	अगर (of_property_पढ़ो_u32(np, "dma-masters", &nr_masters))
		वापस शून्य;
	अगर (nr_masters < 1 || nr_masters > DW_DMA_MAX_NR_MASTERS)
		वापस शून्य;

	अगर (of_property_पढ़ो_u32(np, "dma-channels", &nr_channels))
		वापस शून्य;
	अगर (nr_channels > DW_DMA_MAX_NR_CHANNELS)
		वापस शून्य;

	pdata = devm_kzalloc(&pdev->dev, माप(*pdata), GFP_KERNEL);
	अगर (!pdata)
		वापस शून्य;

	pdata->nr_masters = nr_masters;
	pdata->nr_channels = nr_channels;

	अगर (!of_property_पढ़ो_u32(np, "chan_allocation_order", &पंचांगp))
		pdata->chan_allocation_order = (अचिन्हित अक्षर)पंचांगp;

	अगर (!of_property_पढ़ो_u32(np, "chan_priority", &पंचांगp))
		pdata->chan_priority = पंचांगp;

	अगर (!of_property_पढ़ो_u32(np, "block_size", &पंचांगp))
		pdata->block_size = पंचांगp;

	अगर (!of_property_पढ़ो_u32_array(np, "data-width", arr, nr_masters)) अणु
		क्रम (पंचांगp = 0; पंचांगp < nr_masters; पंचांगp++)
			pdata->data_width[पंचांगp] = arr[पंचांगp];
	पूर्ण अन्यथा अगर (!of_property_पढ़ो_u32_array(np, "data_width", arr, nr_masters)) अणु
		क्रम (पंचांगp = 0; पंचांगp < nr_masters; पंचांगp++)
			pdata->data_width[पंचांगp] = BIT(arr[पंचांगp] & 0x07);
	पूर्ण

	अगर (!of_property_पढ़ो_u32_array(np, "multi-block", mb, nr_channels)) अणु
		क्रम (पंचांगp = 0; पंचांगp < nr_channels; पंचांगp++)
			pdata->multi_block[पंचांगp] = mb[पंचांगp];
	पूर्ण अन्यथा अणु
		क्रम (पंचांगp = 0; पंचांगp < nr_channels; पंचांगp++)
			pdata->multi_block[पंचांगp] = 1;
	पूर्ण

	अगर (of_property_पढ़ो_u32_array(np, "snps,max-burst-len", pdata->max_burst,
				       nr_channels)) अणु
		स_रखो32(pdata->max_burst, DW_DMA_MAX_BURST, nr_channels);
	पूर्ण

	अगर (!of_property_पढ़ो_u32(np, "snps,dma-protection-control", &पंचांगp)) अणु
		अगर (पंचांगp > CHAN_PROTCTL_MASK)
			वापस शून्य;
		pdata->protctl = पंचांगp;
	पूर्ण

	वापस pdata;
पूर्ण

व्योम dw_dma_of_controller_रेजिस्टर(काष्ठा dw_dma *dw)
अणु
	काष्ठा device *dev = dw->dma.dev;
	पूर्णांक ret;

	अगर (!dev->of_node)
		वापस;

	ret = of_dma_controller_रेजिस्टर(dev->of_node, dw_dma_of_xlate, dw);
	अगर (ret)
		dev_err(dev, "could not register of_dma_controller\n");
पूर्ण

व्योम dw_dma_of_controller_मुक्त(काष्ठा dw_dma *dw)
अणु
	काष्ठा device *dev = dw->dma.dev;

	अगर (!dev->of_node)
		वापस;

	of_dma_controller_मुक्त(dev->of_node);
पूर्ण
