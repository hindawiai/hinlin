<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * This file is part of wl1271
 *
 * Copyright (C) 2009-2010 Nokia Corporation
 *
 * Contact: Luciano Coelho <luciano.coelho@nokia.com>
 */

#समावेश <linux/irq.h>
#समावेश <linux/module.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mmc/sdपन.स>
#समावेश <linux/mmc/sdio_func.h>
#समावेश <linux/mmc/sdio_ids.h>
#समावेश <linux/mmc/card.h>
#समावेश <linux/mmc/host.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/of.h>
#समावेश <linux/of_irq.h>

#समावेश "wlcore.h"
#समावेश "wl12xx_80211.h"
#समावेश "io.h"

अटल bool dump = false;

काष्ठा wl12xx_sdio_glue अणु
	काष्ठा device *dev;
	काष्ठा platक्रमm_device *core;
पूर्ण;

अटल स्थिर काष्ठा sdio_device_id wl1271_devices[] = अणु
	अणु SDIO_DEVICE(SDIO_VENDOR_ID_TI, SDIO_DEVICE_ID_TI_WL1271) पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(sdio, wl1271_devices);

अटल व्योम wl1271_sdio_set_block_size(काष्ठा device *child,
				       अचिन्हित पूर्णांक blksz)
अणु
	काष्ठा wl12xx_sdio_glue *glue = dev_get_drvdata(child->parent);
	काष्ठा sdio_func *func = dev_to_sdio_func(glue->dev);

	sdio_claim_host(func);
	sdio_set_block_size(func, blksz);
	sdio_release_host(func);
पूर्ण

अटल पूर्णांक __must_check wl12xx_sdio_raw_पढ़ो(काष्ठा device *child, पूर्णांक addr,
					     व्योम *buf, माप_प्रकार len, bool fixed)
अणु
	पूर्णांक ret;
	काष्ठा wl12xx_sdio_glue *glue = dev_get_drvdata(child->parent);
	काष्ठा sdio_func *func = dev_to_sdio_func(glue->dev);

	sdio_claim_host(func);

	अगर (unlikely(addr == HW_ACCESS_ELP_CTRL_REG)) अणु
		((u8 *)buf)[0] = sdio_f0_पढ़ोb(func, addr, &ret);
		dev_dbg(child->parent, "sdio read 52 addr 0x%x, byte 0x%02x\n",
			addr, ((u8 *)buf)[0]);
	पूर्ण अन्यथा अणु
		अगर (fixed)
			ret = sdio_पढ़ोsb(func, buf, addr, len);
		अन्यथा
			ret = sdio_स_नकल_fromio(func, buf, addr, len);

		dev_dbg(child->parent, "sdio read 53 addr 0x%x, %zu bytes\n",
			addr, len);
	पूर्ण

	sdio_release_host(func);

	अगर (WARN_ON(ret))
		dev_err(child->parent, "sdio read failed (%d)\n", ret);

	अगर (unlikely(dump)) अणु
		prपूर्णांकk(KERN_DEBUG "wlcore_sdio: READ from 0x%04x\n", addr);
		prपूर्णांक_hex_dump(KERN_DEBUG, "wlcore_sdio: READ ",
			       DUMP_PREFIX_OFFSET, 16, 1,
			       buf, len, false);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक __must_check wl12xx_sdio_raw_ग_लिखो(काष्ठा device *child, पूर्णांक addr,
					      व्योम *buf, माप_प्रकार len, bool fixed)
अणु
	पूर्णांक ret;
	काष्ठा wl12xx_sdio_glue *glue = dev_get_drvdata(child->parent);
	काष्ठा sdio_func *func = dev_to_sdio_func(glue->dev);

	sdio_claim_host(func);

	अगर (unlikely(dump)) अणु
		prपूर्णांकk(KERN_DEBUG "wlcore_sdio: WRITE to 0x%04x\n", addr);
		prपूर्णांक_hex_dump(KERN_DEBUG, "wlcore_sdio: WRITE ",
				DUMP_PREFIX_OFFSET, 16, 1,
				buf, len, false);
	पूर्ण

	अगर (unlikely(addr == HW_ACCESS_ELP_CTRL_REG)) अणु
		sdio_f0_ग_लिखोb(func, ((u8 *)buf)[0], addr, &ret);
		dev_dbg(child->parent, "sdio write 52 addr 0x%x, byte 0x%02x\n",
			addr, ((u8 *)buf)[0]);
	पूर्ण अन्यथा अणु
		dev_dbg(child->parent, "sdio write 53 addr 0x%x, %zu bytes\n",
			addr, len);

		अगर (fixed)
			ret = sdio_ग_लिखोsb(func, addr, buf, len);
		अन्यथा
			ret = sdio_स_नकल_toio(func, addr, buf, len);
	पूर्ण

	sdio_release_host(func);

	अगर (WARN_ON(ret))
		dev_err(child->parent, "sdio write failed (%d)\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक wl12xx_sdio_घातer_on(काष्ठा wl12xx_sdio_glue *glue)
अणु
	पूर्णांक ret;
	काष्ठा sdio_func *func = dev_to_sdio_func(glue->dev);
	काष्ठा mmc_card *card = func->card;

	ret = pm_runसमय_get_sync(&card->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(&card->dev);
		dev_err(glue->dev, "%s: failed to get_sync(%d)\n",
			__func__, ret);

		वापस ret;
	पूर्ण

	sdio_claim_host(func);
	/*
	 * To guarantee that the SDIO card is घातer cycled, as required to make
	 * the FW programming to succeed, let's करो a brute क्रमce HW reset.
	 */
	mmc_hw_reset(card->host);

	sdio_enable_func(func);
	sdio_release_host(func);

	वापस 0;
पूर्ण

अटल पूर्णांक wl12xx_sdio_घातer_off(काष्ठा wl12xx_sdio_glue *glue)
अणु
	काष्ठा sdio_func *func = dev_to_sdio_func(glue->dev);
	काष्ठा mmc_card *card = func->card;

	sdio_claim_host(func);
	sdio_disable_func(func);
	sdio_release_host(func);

	/* Let runसमय PM know the card is घातered off */
	pm_runसमय_put(&card->dev);
	वापस 0;
पूर्ण

अटल पूर्णांक wl12xx_sdio_set_घातer(काष्ठा device *child, bool enable)
अणु
	काष्ठा wl12xx_sdio_glue *glue = dev_get_drvdata(child->parent);

	अगर (enable)
		वापस wl12xx_sdio_घातer_on(glue);
	अन्यथा
		वापस wl12xx_sdio_घातer_off(glue);
पूर्ण

अटल काष्ठा wl1271_अगर_operations sdio_ops = अणु
	.पढ़ो		= wl12xx_sdio_raw_पढ़ो,
	.ग_लिखो		= wl12xx_sdio_raw_ग_लिखो,
	.घातer		= wl12xx_sdio_set_घातer,
	.set_block_size = wl1271_sdio_set_block_size,
पूर्ण;

#अगर_घोषित CONFIG_OF

अटल स्थिर काष्ठा wilink_family_data wl127x_data = अणु
	.name = "wl127x",
	.nvs_name = "ti-connectivity/wl127x-nvs.bin",
पूर्ण;

अटल स्थिर काष्ठा wilink_family_data wl128x_data = अणु
	.name = "wl128x",
	.nvs_name = "ti-connectivity/wl128x-nvs.bin",
पूर्ण;

अटल स्थिर काष्ठा wilink_family_data wl18xx_data = अणु
	.name = "wl18xx",
	.cfg_name = "ti-connectivity/wl18xx-conf.bin",
	.nvs_name = "ti-connectivity/wl1271-nvs.bin",
पूर्ण;

अटल स्थिर काष्ठा of_device_id wlcore_sdio_of_match_table[] = अणु
	अणु .compatible = "ti,wl1271", .data = &wl127x_data पूर्ण,
	अणु .compatible = "ti,wl1273", .data = &wl127x_data पूर्ण,
	अणु .compatible = "ti,wl1281", .data = &wl128x_data पूर्ण,
	अणु .compatible = "ti,wl1283", .data = &wl128x_data पूर्ण,
	अणु .compatible = "ti,wl1285", .data = &wl128x_data पूर्ण,
	अणु .compatible = "ti,wl1801", .data = &wl18xx_data पूर्ण,
	अणु .compatible = "ti,wl1805", .data = &wl18xx_data पूर्ण,
	अणु .compatible = "ti,wl1807", .data = &wl18xx_data पूर्ण,
	अणु .compatible = "ti,wl1831", .data = &wl18xx_data पूर्ण,
	अणु .compatible = "ti,wl1835", .data = &wl18xx_data पूर्ण,
	अणु .compatible = "ti,wl1837", .data = &wl18xx_data पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल पूर्णांक wlcore_probe_of(काष्ठा device *dev, पूर्णांक *irq, पूर्णांक *wakeirq,
			   काष्ठा wlcore_platdev_data *pdev_data)
अणु
	काष्ठा device_node *np = dev->of_node;
	स्थिर काष्ठा of_device_id *of_id;

	of_id = of_match_node(wlcore_sdio_of_match_table, np);
	अगर (!of_id)
		वापस -ENODEV;

	pdev_data->family = of_id->data;

	*irq = irq_of_parse_and_map(np, 0);
	अगर (!*irq) अणु
		dev_err(dev, "No irq in platform data\n");
		वापस -EINVAL;
	पूर्ण

	*wakeirq = irq_of_parse_and_map(np, 1);

	/* optional घड़ी frequency params */
	of_property_पढ़ो_u32(np, "ref-clock-frequency",
			     &pdev_data->ref_घड़ी_freq);
	of_property_पढ़ो_u32(np, "tcxo-clock-frequency",
			     &pdev_data->tcxo_घड़ी_freq);

	वापस 0;
पूर्ण
#अन्यथा
अटल पूर्णांक wlcore_probe_of(काष्ठा device *dev, पूर्णांक *irq, पूर्णांक *wakeirq,
			   काष्ठा wlcore_platdev_data *pdev_data)
अणु
	वापस -ENODATA;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक wl1271_probe(काष्ठा sdio_func *func,
				  स्थिर काष्ठा sdio_device_id *id)
अणु
	काष्ठा wlcore_platdev_data *pdev_data;
	काष्ठा wl12xx_sdio_glue *glue;
	काष्ठा resource res[2];
	mmc_pm_flag_t mmcflags;
	पूर्णांक ret = -ENOMEM;
	पूर्णांक irq, wakeirq, num_irqs;
	स्थिर अक्षर *chip_family;

	/* We are only able to handle the wlan function */
	अगर (func->num != 0x02)
		वापस -ENODEV;

	pdev_data = devm_kzalloc(&func->dev, माप(*pdev_data), GFP_KERNEL);
	अगर (!pdev_data)
		वापस -ENOMEM;

	pdev_data->अगर_ops = &sdio_ops;

	glue = devm_kzalloc(&func->dev, माप(*glue), GFP_KERNEL);
	अगर (!glue)
		वापस -ENOMEM;

	glue->dev = &func->dev;

	/* Grab access to FN0 क्रम ELP reg. */
	func->card->quirks |= MMC_QUIRK_LENIENT_FN0;

	/* Use block mode क्रम transferring over one block size of data */
	func->card->quirks |= MMC_QUIRK_BLKSZ_FOR_BYTE_MODE;

	ret = wlcore_probe_of(&func->dev, &irq, &wakeirq, pdev_data);
	अगर (ret)
		जाओ out;

	/* अगर sdio can keep घातer जबतक host is suspended, enable wow */
	mmcflags = sdio_get_host_pm_caps(func);
	dev_dbg(glue->dev, "sdio PM caps = 0x%x\n", mmcflags);

	अगर (mmcflags & MMC_PM_KEEP_POWER)
		pdev_data->pwr_in_suspend = true;

	sdio_set_drvdata(func, glue);

	/* Tell PM core that we करोn't need the card to be घातered now */
	pm_runसमय_put_noidle(&func->dev);

	/*
	 * Due to a hardware bug, we can't dअगरferentiate wl18xx from
	 * wl12xx, because both report the same device ID.  The only
	 * way to dअगरferentiate is by checking the SDIO revision,
	 * which is 3.00 on the wl18xx chips.
	 */
	अगर (func->card->cccr.sdio_vsn == SDIO_SDIO_REV_3_00)
		chip_family = "wl18xx";
	अन्यथा
		chip_family = "wl12xx";

	glue->core = platक्रमm_device_alloc(chip_family, PLATFORM_DEVID_AUTO);
	अगर (!glue->core) अणु
		dev_err(glue->dev, "can't allocate platform_device");
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	glue->core->dev.parent = &func->dev;

	स_रखो(res, 0x00, माप(res));

	res[0].start = irq;
	res[0].flags = IORESOURCE_IRQ |
		       irqd_get_trigger_type(irq_get_irq_data(irq));
	res[0].name = "irq";


	अगर (wakeirq > 0) अणु
		res[1].start = wakeirq;
		res[1].flags = IORESOURCE_IRQ |
			       irqd_get_trigger_type(irq_get_irq_data(wakeirq));
		res[1].name = "wakeirq";
		num_irqs = 2;
	पूर्ण अन्यथा अणु
		num_irqs = 1;
	पूर्ण
	ret = platक्रमm_device_add_resources(glue->core, res, num_irqs);
	अगर (ret) अणु
		dev_err(glue->dev, "can't add resources\n");
		जाओ out_dev_put;
	पूर्ण

	ret = platक्रमm_device_add_data(glue->core, pdev_data,
				       माप(*pdev_data));
	अगर (ret) अणु
		dev_err(glue->dev, "can't add platform data\n");
		जाओ out_dev_put;
	पूर्ण

	ret = platक्रमm_device_add(glue->core);
	अगर (ret) अणु
		dev_err(glue->dev, "can't add platform device\n");
		जाओ out_dev_put;
	पूर्ण
	वापस 0;

out_dev_put:
	platक्रमm_device_put(glue->core);

out:
	वापस ret;
पूर्ण

अटल व्योम wl1271_हटाओ(काष्ठा sdio_func *func)
अणु
	काष्ठा wl12xx_sdio_glue *glue = sdio_get_drvdata(func);

	/* Unकरो decrement करोne above in wl1271_probe */
	pm_runसमय_get_noresume(&func->dev);

	platक्रमm_device_unरेजिस्टर(glue->core);
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक wl1271_suspend(काष्ठा device *dev)
अणु
	/* Tell MMC/SDIO core it's OK to घातer करोwn the card
	 * (अगर it isn't alपढ़ोy), but not to हटाओ it completely */
	काष्ठा sdio_func *func = dev_to_sdio_func(dev);
	काष्ठा wl12xx_sdio_glue *glue = sdio_get_drvdata(func);
	काष्ठा wl1271 *wl = platक्रमm_get_drvdata(glue->core);
	mmc_pm_flag_t sdio_flags;
	पूर्णांक ret = 0;

	अगर (!wl) अणु
		dev_err(dev, "no wilink module was probed\n");
		जाओ out;
	पूर्ण

	dev_dbg(dev, "wl1271 suspend. wow_enabled: %d\n",
		wl->wow_enabled);

	/* check whether sdio should keep घातer */
	अगर (wl->wow_enabled) अणु
		sdio_flags = sdio_get_host_pm_caps(func);

		अगर (!(sdio_flags & MMC_PM_KEEP_POWER)) अणु
			dev_err(dev, "can't keep power while host "
				     "is suspended\n");
			ret = -EINVAL;
			जाओ out;
		पूर्ण

		/* keep घातer जबतक host suspended */
		ret = sdio_set_host_pm_flags(func, MMC_PM_KEEP_POWER);
		अगर (ret) अणु
			dev_err(dev, "error while trying to keep power\n");
			जाओ out;
		पूर्ण
	पूर्ण
out:
	वापस ret;
पूर्ण

अटल पूर्णांक wl1271_resume(काष्ठा device *dev)
अणु
	dev_dbg(dev, "wl1271 resume\n");

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops wl1271_sdio_pm_ops = अणु
	.suspend	= wl1271_suspend,
	.resume		= wl1271_resume,
पूर्ण;
#पूर्ण_अगर

अटल काष्ठा sdio_driver wl1271_sdio_driver = अणु
	.name		= "wl1271_sdio",
	.id_table	= wl1271_devices,
	.probe		= wl1271_probe,
	.हटाओ		= wl1271_हटाओ,
#अगर_घोषित CONFIG_PM
	.drv = अणु
		.pm = &wl1271_sdio_pm_ops,
	पूर्ण,
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक __init wl1271_init(व्योम)
अणु
	वापस sdio_रेजिस्टर_driver(&wl1271_sdio_driver);
पूर्ण

अटल व्योम __निकास wl1271_निकास(व्योम)
अणु
	sdio_unरेजिस्टर_driver(&wl1271_sdio_driver);
पूर्ण

module_init(wl1271_init);
module_निकास(wl1271_निकास);

module_param(dump, bool, 0600);
MODULE_PARM_DESC(dump, "Enable sdio read/write dumps.");

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Luciano Coelho <coelho@ti.com>");
MODULE_AUTHOR("Juuso Oikarinen <juuso.oikarinen@nokia.com>");
