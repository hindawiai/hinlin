<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ST's Remote Processor Control Driver
 *
 * Copyright (C) 2015 STMicroelectronics - All Rights Reserved
 *
 * Author: Luकरोvic Barre <luकरोvic.barre@st.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/err.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mailbox_client.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_reserved_स्मृति.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/remoteproc.h>
#समावेश <linux/reset.h>

#समावेश "remoteproc_internal.h"

#घोषणा ST_RPROC_VQ0		0
#घोषणा ST_RPROC_VQ1		1
#घोषणा ST_RPROC_MAX_VRING	2

#घोषणा MBOX_RX			0
#घोषणा MBOX_TX			1
#घोषणा MBOX_MAX		2

काष्ठा st_rproc_config अणु
	bool			sw_reset;
	bool			pwr_reset;
	अचिन्हित दीर्घ		bootaddr_mask;
पूर्ण;

काष्ठा st_rproc अणु
	काष्ठा st_rproc_config	*config;
	काष्ठा reset_control	*sw_reset;
	काष्ठा reset_control	*pwr_reset;
	काष्ठा clk		*clk;
	u32			clk_rate;
	काष्ठा regmap		*boot_base;
	u32			boot_offset;
	काष्ठा mbox_chan	*mbox_chan[ST_RPROC_MAX_VRING * MBOX_MAX];
	काष्ठा mbox_client mbox_client_vq0;
	काष्ठा mbox_client mbox_client_vq1;
पूर्ण;

अटल व्योम st_rproc_mbox_callback(काष्ठा device *dev, u32 msg)
अणु
	काष्ठा rproc *rproc = dev_get_drvdata(dev);

	अगर (rproc_vq_पूर्णांकerrupt(rproc, msg) == IRQ_NONE)
		dev_dbg(dev, "no message was found in vqid %d\n", msg);
पूर्ण

अटल
व्योम st_rproc_mbox_callback_vq0(काष्ठा mbox_client *mbox_client, व्योम *data)
अणु
	st_rproc_mbox_callback(mbox_client->dev, 0);
पूर्ण

अटल
व्योम st_rproc_mbox_callback_vq1(काष्ठा mbox_client *mbox_client, व्योम *data)
अणु
	st_rproc_mbox_callback(mbox_client->dev, 1);
पूर्ण

अटल व्योम st_rproc_kick(काष्ठा rproc *rproc, पूर्णांक vqid)
अणु
	काष्ठा st_rproc *ddata = rproc->priv;
	काष्ठा device *dev = rproc->dev.parent;
	पूर्णांक ret;

	/* send the index of the triggered virtqueue in the mailbox payload */
	अगर (WARN_ON(vqid >= ST_RPROC_MAX_VRING))
		वापस;

	ret = mbox_send_message(ddata->mbox_chan[vqid * MBOX_MAX + MBOX_TX],
				(व्योम *)&vqid);
	अगर (ret < 0)
		dev_err(dev, "failed to send message via mbox: %d\n", ret);
पूर्ण

अटल पूर्णांक st_rproc_mem_alloc(काष्ठा rproc *rproc,
			      काष्ठा rproc_mem_entry *mem)
अणु
	काष्ठा device *dev = rproc->dev.parent;
	व्योम *va;

	va = ioremap_wc(mem->dma, mem->len);
	अगर (!va) अणु
		dev_err(dev, "Unable to map memory region: %pa+%zx\n",
			&mem->dma, mem->len);
		वापस -ENOMEM;
	पूर्ण

	/* Update memory entry va */
	mem->va = va;

	वापस 0;
पूर्ण

अटल पूर्णांक st_rproc_mem_release(काष्ठा rproc *rproc,
				काष्ठा rproc_mem_entry *mem)
अणु
	iounmap(mem->va);

	वापस 0;
पूर्ण

अटल पूर्णांक st_rproc_parse_fw(काष्ठा rproc *rproc, स्थिर काष्ठा firmware *fw)
अणु
	काष्ठा device *dev = rproc->dev.parent;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा rproc_mem_entry *mem;
	काष्ठा reserved_mem *rmem;
	काष्ठा of_phandle_iterator it;
	पूर्णांक index = 0;

	of_phandle_iterator_init(&it, np, "memory-region", शून्य, 0);
	जबतक (of_phandle_iterator_next(&it) == 0) अणु
		rmem = of_reserved_mem_lookup(it.node);
		अगर (!rmem) अणु
			dev_err(dev, "unable to acquire memory-region\n");
			वापस -EINVAL;
		पूर्ण

		/*  No need to map vdev buffer */
		अगर (म_भेद(it.node->name, "vdev0buffer")) अणु
			/* Register memory region */
			mem = rproc_mem_entry_init(dev, शून्य,
						   (dma_addr_t)rmem->base,
						   rmem->size, rmem->base,
						   st_rproc_mem_alloc,
						   st_rproc_mem_release,
						   it.node->name);
		पूर्ण अन्यथा अणु
			/* Register reserved memory क्रम vdev buffer allocation */
			mem = rproc_of_resm_mem_entry_init(dev, index,
							   rmem->size,
							   rmem->base,
							   it.node->name);
		पूर्ण

		अगर (!mem)
			वापस -ENOMEM;

		rproc_add_carveout(rproc, mem);
		index++;
	पूर्ण

	वापस rproc_elf_load_rsc_table(rproc, fw);
पूर्ण

अटल पूर्णांक st_rproc_start(काष्ठा rproc *rproc)
अणु
	काष्ठा st_rproc *ddata = rproc->priv;
	पूर्णांक err;

	regmap_update_bits(ddata->boot_base, ddata->boot_offset,
			   ddata->config->bootaddr_mask, rproc->bootaddr);

	err = clk_enable(ddata->clk);
	अगर (err) अणु
		dev_err(&rproc->dev, "Failed to enable clock\n");
		वापस err;
	पूर्ण

	अगर (ddata->config->sw_reset) अणु
		err = reset_control_deनिश्चित(ddata->sw_reset);
		अगर (err) अणु
			dev_err(&rproc->dev, "Failed to deassert S/W Reset\n");
			जाओ sw_reset_fail;
		पूर्ण
	पूर्ण

	अगर (ddata->config->pwr_reset) अणु
		err = reset_control_deनिश्चित(ddata->pwr_reset);
		अगर (err) अणु
			dev_err(&rproc->dev, "Failed to deassert Power Reset\n");
			जाओ pwr_reset_fail;
		पूर्ण
	पूर्ण

	dev_info(&rproc->dev, "Started from 0x%llx\n", rproc->bootaddr);

	वापस 0;


pwr_reset_fail:
	अगर (ddata->config->pwr_reset)
		reset_control_निश्चित(ddata->sw_reset);
sw_reset_fail:
	clk_disable(ddata->clk);

	वापस err;
पूर्ण

अटल पूर्णांक st_rproc_stop(काष्ठा rproc *rproc)
अणु
	काष्ठा st_rproc *ddata = rproc->priv;
	पूर्णांक sw_err = 0, pwr_err = 0;

	अगर (ddata->config->sw_reset) अणु
		sw_err = reset_control_निश्चित(ddata->sw_reset);
		अगर (sw_err)
			dev_err(&rproc->dev, "Failed to assert S/W Reset\n");
	पूर्ण

	अगर (ddata->config->pwr_reset) अणु
		pwr_err = reset_control_निश्चित(ddata->pwr_reset);
		अगर (pwr_err)
			dev_err(&rproc->dev, "Failed to assert Power Reset\n");
	पूर्ण

	clk_disable(ddata->clk);

	वापस sw_err ?: pwr_err;
पूर्ण

अटल स्थिर काष्ठा rproc_ops st_rproc_ops = अणु
	.kick			= st_rproc_kick,
	.start			= st_rproc_start,
	.stop			= st_rproc_stop,
	.parse_fw		= st_rproc_parse_fw,
	.load			= rproc_elf_load_segments,
	.find_loaded_rsc_table	= rproc_elf_find_loaded_rsc_table,
	.sanity_check		= rproc_elf_sanity_check,
	.get_boot_addr		= rproc_elf_get_boot_addr,
पूर्ण;

/*
 * Fetch state of the processor: 0 is off, 1 is on.
 */
अटल पूर्णांक st_rproc_state(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा rproc *rproc = platक्रमm_get_drvdata(pdev);
	काष्ठा st_rproc *ddata = rproc->priv;
	पूर्णांक reset_sw = 0, reset_pwr = 0;

	अगर (ddata->config->sw_reset)
		reset_sw = reset_control_status(ddata->sw_reset);

	अगर (ddata->config->pwr_reset)
		reset_pwr = reset_control_status(ddata->pwr_reset);

	अगर (reset_sw < 0 || reset_pwr < 0)
		वापस -EINVAL;

	वापस !reset_sw && !reset_pwr;
पूर्ण

अटल स्थिर काष्ठा st_rproc_config st40_rproc_cfg = अणु
	.sw_reset = true,
	.pwr_reset = true,
	.bootaddr_mask = GENMASK(28, 1),
पूर्ण;

अटल स्थिर काष्ठा st_rproc_config st231_rproc_cfg = अणु
	.sw_reset = true,
	.pwr_reset = false,
	.bootaddr_mask = GENMASK(31, 6),
पूर्ण;

अटल स्थिर काष्ठा of_device_id st_rproc_match[] = अणु
	अणु .compatible = "st,st40-rproc", .data = &st40_rproc_cfg पूर्ण,
	अणु .compatible = "st,st231-rproc", .data = &st231_rproc_cfg पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, st_rproc_match);

अटल पूर्णांक st_rproc_parse_dt(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा rproc *rproc = platक्रमm_get_drvdata(pdev);
	काष्ठा st_rproc *ddata = rproc->priv;
	काष्ठा device_node *np = dev->of_node;
	पूर्णांक err;

	अगर (ddata->config->sw_reset) अणु
		ddata->sw_reset = devm_reset_control_get_exclusive(dev,
								   "sw_reset");
		अगर (IS_ERR(ddata->sw_reset)) अणु
			dev_err(dev, "Failed to get S/W Reset\n");
			वापस PTR_ERR(ddata->sw_reset);
		पूर्ण
	पूर्ण

	अगर (ddata->config->pwr_reset) अणु
		ddata->pwr_reset = devm_reset_control_get_exclusive(dev,
								    "pwr_reset");
		अगर (IS_ERR(ddata->pwr_reset)) अणु
			dev_err(dev, "Failed to get Power Reset\n");
			वापस PTR_ERR(ddata->pwr_reset);
		पूर्ण
	पूर्ण

	ddata->clk = devm_clk_get(dev, शून्य);
	अगर (IS_ERR(ddata->clk)) अणु
		dev_err(dev, "Failed to get clock\n");
		वापस PTR_ERR(ddata->clk);
	पूर्ण

	err = of_property_पढ़ो_u32(np, "clock-frequency", &ddata->clk_rate);
	अगर (err) अणु
		dev_err(dev, "failed to get clock frequency\n");
		वापस err;
	पूर्ण

	ddata->boot_base = syscon_regmap_lookup_by_phandle(np, "st,syscfg");
	अगर (IS_ERR(ddata->boot_base)) अणु
		dev_err(dev, "Boot base not found\n");
		वापस PTR_ERR(ddata->boot_base);
	पूर्ण

	err = of_property_पढ़ो_u32_index(np, "st,syscfg", 1,
					 &ddata->boot_offset);
	अगर (err) अणु
		dev_err(dev, "Boot offset not found\n");
		वापस -EINVAL;
	पूर्ण

	err = clk_prepare(ddata->clk);
	अगर (err)
		dev_err(dev, "failed to get clock\n");

	वापस err;
पूर्ण

अटल पूर्णांक st_rproc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	स्थिर काष्ठा of_device_id *match;
	काष्ठा st_rproc *ddata;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा rproc *rproc;
	काष्ठा mbox_chan *chan;
	पूर्णांक enabled;
	पूर्णांक ret, i;

	match = of_match_device(st_rproc_match, dev);
	अगर (!match || !match->data) अणु
		dev_err(dev, "No device match found\n");
		वापस -ENODEV;
	पूर्ण

	rproc = rproc_alloc(dev, np->name, &st_rproc_ops, शून्य, माप(*ddata));
	अगर (!rproc)
		वापस -ENOMEM;

	rproc->has_iommu = false;
	ddata = rproc->priv;
	ddata->config = (काष्ठा st_rproc_config *)match->data;

	platक्रमm_set_drvdata(pdev, rproc);

	ret = st_rproc_parse_dt(pdev);
	अगर (ret)
		जाओ मुक्त_rproc;

	enabled = st_rproc_state(pdev);
	अगर (enabled < 0) अणु
		ret = enabled;
		जाओ मुक्त_clk;
	पूर्ण

	अगर (enabled) अणु
		atomic_inc(&rproc->घातer);
		rproc->state = RPROC_RUNNING;
	पूर्ण अन्यथा अणु
		clk_set_rate(ddata->clk, ddata->clk_rate);
	पूर्ण

	अगर (of_get_property(np, "mbox-names", शून्य)) अणु
		ddata->mbox_client_vq0.dev		= dev;
		ddata->mbox_client_vq0.tx_करोne		= शून्य;
		ddata->mbox_client_vq0.tx_block	= false;
		ddata->mbox_client_vq0.knows_txकरोne	= false;
		ddata->mbox_client_vq0.rx_callback	= st_rproc_mbox_callback_vq0;

		ddata->mbox_client_vq1.dev		= dev;
		ddata->mbox_client_vq1.tx_करोne		= शून्य;
		ddata->mbox_client_vq1.tx_block	= false;
		ddata->mbox_client_vq1.knows_txकरोne	= false;
		ddata->mbox_client_vq1.rx_callback	= st_rproc_mbox_callback_vq1;

		/*
		 * To control a co-processor without IPC mechanism.
		 * This driver can be used without mbox and rpmsg.
		 */
		chan = mbox_request_channel_byname(&ddata->mbox_client_vq0, "vq0_rx");
		अगर (IS_ERR(chan)) अणु
			dev_err(&rproc->dev, "failed to request mbox chan 0\n");
			ret = PTR_ERR(chan);
			जाओ मुक्त_clk;
		पूर्ण
		ddata->mbox_chan[ST_RPROC_VQ0 * MBOX_MAX + MBOX_RX] = chan;

		chan = mbox_request_channel_byname(&ddata->mbox_client_vq0, "vq0_tx");
		अगर (IS_ERR(chan)) अणु
			dev_err(&rproc->dev, "failed to request mbox chan 0\n");
			ret = PTR_ERR(chan);
			जाओ मुक्त_mbox;
		पूर्ण
		ddata->mbox_chan[ST_RPROC_VQ0 * MBOX_MAX + MBOX_TX] = chan;

		chan = mbox_request_channel_byname(&ddata->mbox_client_vq1, "vq1_rx");
		अगर (IS_ERR(chan)) अणु
			dev_err(&rproc->dev, "failed to request mbox chan 1\n");
			ret = PTR_ERR(chan);
			जाओ मुक्त_mbox;
		पूर्ण
		ddata->mbox_chan[ST_RPROC_VQ1 * MBOX_MAX + MBOX_RX] = chan;

		chan = mbox_request_channel_byname(&ddata->mbox_client_vq1, "vq1_tx");
		अगर (IS_ERR(chan)) अणु
			dev_err(&rproc->dev, "failed to request mbox chan 1\n");
			ret = PTR_ERR(chan);
			जाओ मुक्त_mbox;
		पूर्ण
		ddata->mbox_chan[ST_RPROC_VQ1 * MBOX_MAX + MBOX_TX] = chan;
	पूर्ण

	ret = rproc_add(rproc);
	अगर (ret)
		जाओ मुक्त_mbox;

	वापस 0;

मुक्त_mbox:
	क्रम (i = 0; i < ST_RPROC_MAX_VRING * MBOX_MAX; i++)
		mbox_मुक्त_channel(ddata->mbox_chan[i]);
मुक्त_clk:
	clk_unprepare(ddata->clk);
मुक्त_rproc:
	rproc_मुक्त(rproc);
	वापस ret;
पूर्ण

अटल पूर्णांक st_rproc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा rproc *rproc = platक्रमm_get_drvdata(pdev);
	काष्ठा st_rproc *ddata = rproc->priv;
	पूर्णांक i;

	rproc_del(rproc);

	clk_disable_unprepare(ddata->clk);

	क्रम (i = 0; i < ST_RPROC_MAX_VRING * MBOX_MAX; i++)
		mbox_मुक्त_channel(ddata->mbox_chan[i]);

	rproc_मुक्त(rproc);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver st_rproc_driver = अणु
	.probe = st_rproc_probe,
	.हटाओ = st_rproc_हटाओ,
	.driver = अणु
		.name = "st-rproc",
		.of_match_table = of_match_ptr(st_rproc_match),
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(st_rproc_driver);

MODULE_DESCRIPTION("ST Remote Processor Control Driver");
MODULE_AUTHOR("Ludovic Barre <ludovic.barre@st.com>");
MODULE_LICENSE("GPL v2");
