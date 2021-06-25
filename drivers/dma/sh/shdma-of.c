<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * SHDMA Device Tree glue
 *
 * Copyright (C) 2013 Renesas Electronics Inc.
 * Author: Guennadi Liakhovetski <g.liakhovetski@gmx.de>
 */

#समावेश <linux/dmaengine.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_dma.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/shdma-base.h>

#घोषणा to_shdma_chan(c) container_of(c, काष्ठा shdma_chan, dma_chan)

अटल काष्ठा dma_chan *shdma_of_xlate(काष्ठा of_phandle_args *dma_spec,
				       काष्ठा of_dma *ofdma)
अणु
	u32 id = dma_spec->args[0];
	dma_cap_mask_t mask;
	काष्ठा dma_chan *chan;

	अगर (dma_spec->args_count != 1)
		वापस शून्य;

	dma_cap_zero(mask);
	/* Only slave DMA channels can be allocated via DT */
	dma_cap_set(DMA_SLAVE, mask);

	chan = dma_request_channel(mask, shdma_chan_filter,
				   (व्योम *)(uपूर्णांकptr_t)id);
	अगर (chan)
		to_shdma_chan(chan)->hw_req = id;

	वापस chan;
पूर्ण

अटल पूर्णांक shdma_of_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा of_dev_auxdata *lookup = dev_get_platdata(&pdev->dev);
	पूर्णांक ret;

	ret = of_dma_controller_रेजिस्टर(pdev->dev.of_node,
					 shdma_of_xlate, pdev);
	अगर (ret < 0)
		वापस ret;

	ret = of_platक्रमm_populate(pdev->dev.of_node, शून्य, lookup, &pdev->dev);
	अगर (ret < 0)
		of_dma_controller_मुक्त(pdev->dev.of_node);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा of_device_id shdma_of_match[] = अणु
	अणु .compatible = "renesas,shdma-mux", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, sh_dmae_of_match);

अटल काष्ठा platक्रमm_driver shdma_of = अणु
	.driver		= अणु
		.name	= "shdma-of",
		.of_match_table = shdma_of_match,
	पूर्ण,
	.probe		= shdma_of_probe,
पूर्ण;

module_platक्रमm_driver(shdma_of);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("SH-DMA driver DT glue");
MODULE_AUTHOR("Guennadi Liakhovetski <g.liakhovetski@gmx.de>");
