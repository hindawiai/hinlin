<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Copyright (C) 2019 Texas Instruments Incorporated - https://www.ti.com/
// Author: Vignesh Raghavendra <vigneshr@ti.com>

#समावेश <linux/completion.h>
#समावेश <linux/dma-direction.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/err.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/mtd/cfi.h>
#समावेश <linux/mtd/hyperbus.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mux/consumer.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/sched/task_stack.h>
#समावेश <linux/types.h>

#घोषणा AM654_HBMC_CALIB_COUNT 25

काष्ठा am654_hbmc_device_priv अणु
	काष्ठा completion rx_dma_complete;
	phys_addr_t device_base;
	काष्ठा hyperbus_ctlr *ctlr;
	काष्ठा dma_chan *rx_chan;
पूर्ण;

काष्ठा am654_hbmc_priv अणु
	काष्ठा hyperbus_ctlr ctlr;
	काष्ठा hyperbus_device hbdev;
	काष्ठा mux_control *mux_ctrl;
पूर्ण;

अटल पूर्णांक am654_hbmc_calibrate(काष्ठा hyperbus_device *hbdev)
अणु
	काष्ठा map_info *map = &hbdev->map;
	काष्ठा cfi_निजी cfi;
	पूर्णांक count = AM654_HBMC_CALIB_COUNT;
	पूर्णांक pass_count = 0;
	पूर्णांक ret;

	cfi.पूर्णांकerleave = 1;
	cfi.device_type = CFI_DEVICETYPE_X16;
	cfi_send_gen_cmd(0xF0, 0, 0, map, &cfi, cfi.device_type, शून्य);
	cfi_send_gen_cmd(0x98, 0x55, 0, map, &cfi, cfi.device_type, शून्य);

	जबतक (count--) अणु
		ret = cfi_qry_present(map, 0, &cfi);
		अगर (ret)
			pass_count++;
		अन्यथा
			pass_count = 0;
		अगर (pass_count == 5)
			अवरोध;
	पूर्ण

	cfi_qry_mode_off(0, map, &cfi);

	वापस ret;
पूर्ण

अटल व्योम am654_hbmc_dma_callback(व्योम *param)
अणु
	काष्ठा am654_hbmc_device_priv *priv = param;

	complete(&priv->rx_dma_complete);
पूर्ण

अटल पूर्णांक am654_hbmc_dma_पढ़ो(काष्ठा am654_hbmc_device_priv *priv, व्योम *to,
			       अचिन्हित दीर्घ from, sमाप_प्रकार len)

अणु
	क्रमागत dma_ctrl_flags flags = DMA_CTRL_ACK | DMA_PREP_INTERRUPT;
	काष्ठा dma_chan *rx_chan = priv->rx_chan;
	काष्ठा dma_async_tx_descriptor *tx;
	dma_addr_t dma_dst, dma_src;
	dma_cookie_t cookie;
	पूर्णांक ret;

	अगर (!priv->rx_chan || !virt_addr_valid(to) || object_is_on_stack(to))
		वापस -EINVAL;

	dma_dst = dma_map_single(rx_chan->device->dev, to, len, DMA_FROM_DEVICE);
	अगर (dma_mapping_error(rx_chan->device->dev, dma_dst)) अणु
		dev_dbg(priv->ctlr->dev, "DMA mapping failed\n");
		वापस -EIO;
	पूर्ण

	dma_src = priv->device_base + from;
	tx = dmaengine_prep_dma_स_नकल(rx_chan, dma_dst, dma_src, len, flags);
	अगर (!tx) अणु
		dev_err(priv->ctlr->dev, "device_prep_dma_memcpy error\n");
		ret = -EIO;
		जाओ unmap_dma;
	पूर्ण

	reinit_completion(&priv->rx_dma_complete);
	tx->callback = am654_hbmc_dma_callback;
	tx->callback_param = priv;
	cookie = dmaengine_submit(tx);

	ret = dma_submit_error(cookie);
	अगर (ret) अणु
		dev_err(priv->ctlr->dev, "dma_submit_error %d\n", cookie);
		जाओ unmap_dma;
	पूर्ण

	dma_async_issue_pending(rx_chan);
	अगर (!रुको_क्रम_completion_समयout(&priv->rx_dma_complete,  msecs_to_jअगरfies(len + 1000))) अणु
		dmaengine_terminate_sync(rx_chan);
		dev_err(priv->ctlr->dev, "DMA wait_for_completion_timeout\n");
		ret = -ETIMEDOUT;
	पूर्ण

unmap_dma:
	dma_unmap_single(rx_chan->device->dev, dma_dst, len, DMA_FROM_DEVICE);
	वापस ret;
पूर्ण

अटल व्योम am654_hbmc_पढ़ो(काष्ठा hyperbus_device *hbdev, व्योम *to,
			    अचिन्हित दीर्घ from, sमाप_प्रकार len)
अणु
	काष्ठा am654_hbmc_device_priv *priv = hbdev->priv;

	अगर (len < SZ_1K || am654_hbmc_dma_पढ़ो(priv, to, from, len))
		स_नकल_fromio(to, hbdev->map.virt + from, len);
पूर्ण

अटल स्थिर काष्ठा hyperbus_ops am654_hbmc_ops = अणु
	.calibrate = am654_hbmc_calibrate,
	.copy_from = am654_hbmc_पढ़ो,
पूर्ण;

अटल पूर्णांक am654_hbmc_request_mmap_dma(काष्ठा am654_hbmc_device_priv *priv)
अणु
	काष्ठा dma_chan *rx_chan;
	dma_cap_mask_t mask;

	dma_cap_zero(mask);
	dma_cap_set(DMA_MEMCPY, mask);

	rx_chan = dma_request_chan_by_mask(&mask);
	अगर (IS_ERR(rx_chan)) अणु
		अगर (PTR_ERR(rx_chan) == -EPROBE_DEFER)
			वापस -EPROBE_DEFER;
		dev_dbg(priv->ctlr->dev, "No DMA channel available\n");
		वापस 0;
	पूर्ण
	priv->rx_chan = rx_chan;
	init_completion(&priv->rx_dma_complete);

	वापस 0;
पूर्ण

अटल पूर्णांक am654_hbmc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा am654_hbmc_device_priv *dev_priv;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा am654_hbmc_priv *priv;
	काष्ठा resource res;
	पूर्णांक ret;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, priv);

	priv->hbdev.np = of_get_next_child(np, शून्य);
	ret = of_address_to_resource(priv->hbdev.np, 0, &res);
	अगर (ret)
		वापस ret;

	अगर (of_property_पढ़ो_bool(dev->of_node, "mux-controls")) अणु
		काष्ठा mux_control *control = devm_mux_control_get(dev, शून्य);

		अगर (IS_ERR(control))
			वापस PTR_ERR(control);

		ret = mux_control_select(control, 1);
		अगर (ret) अणु
			dev_err(dev, "Failed to select HBMC mux\n");
			वापस ret;
		पूर्ण
		priv->mux_ctrl = control;
	पूर्ण

	priv->hbdev.map.size = resource_size(&res);
	priv->hbdev.map.virt = devm_ioremap_resource(dev, &res);
	अगर (IS_ERR(priv->hbdev.map.virt))
		वापस PTR_ERR(priv->hbdev.map.virt);

	priv->ctlr.dev = dev;
	priv->ctlr.ops = &am654_hbmc_ops;
	priv->hbdev.ctlr = &priv->ctlr;

	dev_priv = devm_kzalloc(dev, माप(*dev_priv), GFP_KERNEL);
	अगर (!dev_priv) अणु
		ret = -ENOMEM;
		जाओ disable_mux;
	पूर्ण

	priv->hbdev.priv = dev_priv;
	dev_priv->device_base = res.start;
	dev_priv->ctlr = &priv->ctlr;

	ret = am654_hbmc_request_mmap_dma(dev_priv);
	अगर (ret)
		जाओ disable_mux;

	ret = hyperbus_रेजिस्टर_device(&priv->hbdev);
	अगर (ret) अणु
		dev_err(dev, "failed to register controller\n");
		जाओ release_dma;
	पूर्ण

	वापस 0;
release_dma:
	अगर (dev_priv->rx_chan)
		dma_release_channel(dev_priv->rx_chan);
disable_mux:
	अगर (priv->mux_ctrl)
		mux_control_deselect(priv->mux_ctrl);
	वापस ret;
पूर्ण

अटल पूर्णांक am654_hbmc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा am654_hbmc_priv *priv = platक्रमm_get_drvdata(pdev);
	काष्ठा am654_hbmc_device_priv *dev_priv = priv->hbdev.priv;
	पूर्णांक ret;

	ret = hyperbus_unरेजिस्टर_device(&priv->hbdev);
	अगर (priv->mux_ctrl)
		mux_control_deselect(priv->mux_ctrl);

	अगर (dev_priv->rx_chan)
		dma_release_channel(dev_priv->rx_chan);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा of_device_id am654_hbmc_dt_ids[] = अणु
	अणु
		.compatible = "ti,am654-hbmc",
	पूर्ण,
	अणु /* end of table */ पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(of, am654_hbmc_dt_ids);

अटल काष्ठा platक्रमm_driver am654_hbmc_platक्रमm_driver = अणु
	.probe = am654_hbmc_probe,
	.हटाओ = am654_hbmc_हटाओ,
	.driver = अणु
		.name = "hbmc-am654",
		.of_match_table = am654_hbmc_dt_ids,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(am654_hbmc_platक्रमm_driver);

MODULE_DESCRIPTION("HBMC driver for AM654 SoC");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:hbmc-am654");
MODULE_AUTHOR("Vignesh Raghavendra <vigneshr@ti.com>");
