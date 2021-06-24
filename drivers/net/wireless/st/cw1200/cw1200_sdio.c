<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Mac80211 SDIO driver क्रम ST-Ericsson CW1200 device
 *
 * Copyright (c) 2010, ST-Ericsson
 * Author: Dmitry Tarnyagin <dmitry.tarnyagin@lockless.no>
 */

#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/delay.h>
#समावेश <linux/mmc/host.h>
#समावेश <linux/mmc/sdio_func.h>
#समावेश <linux/mmc/card.h>
#समावेश <linux/mmc/sdपन.स>
#समावेश <linux/mmc/sdio_ids.h>
#समावेश <net/mac80211.h>

#समावेश "cw1200.h"
#समावेश "hwbus.h"
#समावेश <linux/platक्रमm_data/net-cw1200.h>
#समावेश "hwio.h"

MODULE_AUTHOR("Dmitry Tarnyagin <dmitry.tarnyagin@lockless.no>");
MODULE_DESCRIPTION("mac80211 ST-Ericsson CW1200 SDIO driver");
MODULE_LICENSE("GPL");

#घोषणा SDIO_BLOCK_SIZE (512)

/* Default platक्रमm data क्रम Sagrad modules */
अटल काष्ठा cw1200_platक्रमm_data_sdio sagrad_109x_evk_platक्रमm_data = अणु
	.ref_clk = 38400,
	.have_5ghz = false,
	.sdd_file = "sdd_sagrad_1091_1098.bin",
पूर्ण;

/* Allow platक्रमm data to be overridden */
अटल काष्ठा cw1200_platक्रमm_data_sdio *global_plat_data = &sagrad_109x_evk_platक्रमm_data;

व्योम __init cw1200_sdio_set_platक्रमm_data(काष्ठा cw1200_platक्रमm_data_sdio *pdata)
अणु
	global_plat_data = pdata;
पूर्ण

काष्ठा hwbus_priv अणु
	काष्ठा sdio_func	*func;
	काष्ठा cw1200_common	*core;
	स्थिर काष्ठा cw1200_platक्रमm_data_sdio *pdata;
पूर्ण;

अटल स्थिर काष्ठा sdio_device_id cw1200_sdio_ids[] = अणु
	अणु SDIO_DEVICE(SDIO_VENDOR_ID_STE, SDIO_DEVICE_ID_STE_CW1200) पूर्ण,
	अणु /* end: all zeroes */			पूर्ण,
पूर्ण;

/* hwbus_ops implemetation */

अटल पूर्णांक cw1200_sdio_स_नकल_fromio(काष्ठा hwbus_priv *self,
				     अचिन्हित पूर्णांक addr,
				     व्योम *dst, पूर्णांक count)
अणु
	वापस sdio_स_नकल_fromio(self->func, dst, addr, count);
पूर्ण

अटल पूर्णांक cw1200_sdio_स_नकल_toio(काष्ठा hwbus_priv *self,
				   अचिन्हित पूर्णांक addr,
				   स्थिर व्योम *src, पूर्णांक count)
अणु
	वापस sdio_स_नकल_toio(self->func, addr, (व्योम *)src, count);
पूर्ण

अटल व्योम cw1200_sdio_lock(काष्ठा hwbus_priv *self)
अणु
	sdio_claim_host(self->func);
पूर्ण

अटल व्योम cw1200_sdio_unlock(काष्ठा hwbus_priv *self)
अणु
	sdio_release_host(self->func);
पूर्ण

अटल व्योम cw1200_sdio_irq_handler(काष्ठा sdio_func *func)
अणु
	काष्ठा hwbus_priv *self = sdio_get_drvdata(func);

	/* note:  sdio_host alपढ़ोy claimed here. */
	अगर (self->core)
		cw1200_irq_handler(self->core);
पूर्ण

अटल irqवापस_t cw1200_gpio_hardirq(पूर्णांक irq, व्योम *dev_id)
अणु
	वापस IRQ_WAKE_THREAD;
पूर्ण

अटल irqवापस_t cw1200_gpio_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा hwbus_priv *self = dev_id;

	अगर (self->core) अणु
		cw1200_sdio_lock(self);
		cw1200_irq_handler(self->core);
		cw1200_sdio_unlock(self);
		वापस IRQ_HANDLED;
	पूर्ण अन्यथा अणु
		वापस IRQ_NONE;
	पूर्ण
पूर्ण

अटल पूर्णांक cw1200_request_irq(काष्ठा hwbus_priv *self)
अणु
	पूर्णांक ret;
	u8 cccr;

	cccr = sdio_f0_पढ़ोb(self->func, SDIO_CCCR_IENx, &ret);
	अगर (WARN_ON(ret))
		जाओ err;

	/* Master पूर्णांकerrupt enable ... */
	cccr |= BIT(0);

	/* ... क्रम our function */
	cccr |= BIT(self->func->num);

	sdio_f0_ग_लिखोb(self->func, cccr, SDIO_CCCR_IENx, &ret);
	अगर (WARN_ON(ret))
		जाओ err;

	ret = enable_irq_wake(self->pdata->irq);
	अगर (WARN_ON(ret))
		जाओ err;

	/* Request the IRQ */
	ret =  request_thपढ़ोed_irq(self->pdata->irq, cw1200_gpio_hardirq,
				    cw1200_gpio_irq,
				    IRQF_TRIGGER_HIGH | IRQF_ONESHOT,
				    "cw1200_wlan_irq", self);
	अगर (WARN_ON(ret))
		जाओ err;

	वापस 0;

err:
	वापस ret;
पूर्ण

अटल पूर्णांक cw1200_sdio_irq_subscribe(काष्ठा hwbus_priv *self)
अणु
	पूर्णांक ret = 0;

	pr_debug("SW IRQ subscribe\n");
	sdio_claim_host(self->func);
	अगर (self->pdata->irq)
		ret = cw1200_request_irq(self);
	अन्यथा
		ret = sdio_claim_irq(self->func, cw1200_sdio_irq_handler);

	sdio_release_host(self->func);
	वापस ret;
पूर्ण

अटल पूर्णांक cw1200_sdio_irq_unsubscribe(काष्ठा hwbus_priv *self)
अणु
	पूर्णांक ret = 0;

	pr_debug("SW IRQ unsubscribe\n");

	अगर (self->pdata->irq) अणु
		disable_irq_wake(self->pdata->irq);
		मुक्त_irq(self->pdata->irq, self);
	पूर्ण अन्यथा अणु
		sdio_claim_host(self->func);
		ret = sdio_release_irq(self->func);
		sdio_release_host(self->func);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक cw1200_sdio_off(स्थिर काष्ठा cw1200_platक्रमm_data_sdio *pdata)
अणु
	अगर (pdata->reset) अणु
		gpio_set_value(pdata->reset, 0);
		msleep(30); /* Min is 2 * CLK32K cycles */
		gpio_मुक्त(pdata->reset);
	पूर्ण

	अगर (pdata->घातer_ctrl)
		pdata->घातer_ctrl(pdata, false);
	अगर (pdata->clk_ctrl)
		pdata->clk_ctrl(pdata, false);

	वापस 0;
पूर्ण

अटल पूर्णांक cw1200_sdio_on(स्थिर काष्ठा cw1200_platक्रमm_data_sdio *pdata)
अणु
	/* Ensure I/Os are pulled low */
	अगर (pdata->reset) अणु
		gpio_request(pdata->reset, "cw1200_wlan_reset");
		gpio_direction_output(pdata->reset, 0);
	पूर्ण
	अगर (pdata->घातerup) अणु
		gpio_request(pdata->घातerup, "cw1200_wlan_powerup");
		gpio_direction_output(pdata->घातerup, 0);
	पूर्ण
	अगर (pdata->reset || pdata->घातerup)
		msleep(10); /* Settle समय? */

	/* Enable 3v3 and 1v8 to hardware */
	अगर (pdata->घातer_ctrl) अणु
		अगर (pdata->घातer_ctrl(pdata, true)) अणु
			pr_err("power_ctrl() failed!\n");
			वापस -1;
		पूर्ण
	पूर्ण

	/* Enable CLK32K */
	अगर (pdata->clk_ctrl) अणु
		अगर (pdata->clk_ctrl(pdata, true)) अणु
			pr_err("clk_ctrl() failed!\n");
			वापस -1;
		पूर्ण
		msleep(10); /* Delay until घड़ी is stable क्रम 2 cycles */
	पूर्ण

	/* Enable POWERUP संकेत */
	अगर (pdata->घातerup) अणु
		gpio_set_value(pdata->घातerup, 1);
		msleep(250); /* or more..? */
	पूर्ण
	/* Enable RSTn संकेत */
	अगर (pdata->reset) अणु
		gpio_set_value(pdata->reset, 1);
		msleep(50); /* Or more..? */
	पूर्ण
	वापस 0;
पूर्ण

अटल माप_प्रकार cw1200_sdio_align_size(काष्ठा hwbus_priv *self, माप_प्रकार size)
अणु
	अगर (self->pdata->no_nptb)
		size = round_up(size, SDIO_BLOCK_SIZE);
	अन्यथा
		size = sdio_align_size(self->func, size);

	वापस size;
पूर्ण

अटल पूर्णांक cw1200_sdio_pm(काष्ठा hwbus_priv *self, bool suspend)
अणु
	पूर्णांक ret = 0;

	अगर (self->pdata->irq)
		ret = irq_set_irq_wake(self->pdata->irq, suspend);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा hwbus_ops cw1200_sdio_hwbus_ops = अणु
	.hwbus_स_नकल_fromio	= cw1200_sdio_स_नकल_fromio,
	.hwbus_स_नकल_toio	= cw1200_sdio_स_नकल_toio,
	.lock			= cw1200_sdio_lock,
	.unlock			= cw1200_sdio_unlock,
	.align_size		= cw1200_sdio_align_size,
	.घातer_mgmt		= cw1200_sdio_pm,
पूर्ण;

/* Probe Function to be called by SDIO stack when device is discovered */
अटल पूर्णांक cw1200_sdio_probe(काष्ठा sdio_func *func,
			     स्थिर काष्ठा sdio_device_id *id)
अणु
	काष्ठा hwbus_priv *self;
	पूर्णांक status;

	pr_info("cw1200_wlan_sdio: Probe called\n");

	/* We are only able to handle the wlan function */
	अगर (func->num != 0x01)
		वापस -ENODEV;

	self = kzalloc(माप(*self), GFP_KERNEL);
	अगर (!self) अणु
		pr_err("Can't allocate SDIO hwbus_priv.\n");
		वापस -ENOMEM;
	पूर्ण

	func->card->quirks |= MMC_QUIRK_LENIENT_FN0;

	self->pdata = global_plat_data; /* FIXME */
	self->func = func;
	sdio_set_drvdata(func, self);
	sdio_claim_host(func);
	sdio_enable_func(func);
	sdio_release_host(func);

	status = cw1200_sdio_irq_subscribe(self);

	status = cw1200_core_probe(&cw1200_sdio_hwbus_ops,
				   self, &func->dev, &self->core,
				   self->pdata->ref_clk,
				   self->pdata->macaddr,
				   self->pdata->sdd_file,
				   self->pdata->have_5ghz);
	अगर (status) अणु
		cw1200_sdio_irq_unsubscribe(self);
		sdio_claim_host(func);
		sdio_disable_func(func);
		sdio_release_host(func);
		sdio_set_drvdata(func, शून्य);
		kमुक्त(self);
	पूर्ण

	वापस status;
पूर्ण

/* Disconnect Function to be called by SDIO stack when
 * device is disconnected
 */
अटल व्योम cw1200_sdio_disconnect(काष्ठा sdio_func *func)
अणु
	काष्ठा hwbus_priv *self = sdio_get_drvdata(func);

	अगर (self) अणु
		cw1200_sdio_irq_unsubscribe(self);
		अगर (self->core) अणु
			cw1200_core_release(self->core);
			self->core = शून्य;
		पूर्ण
		sdio_claim_host(func);
		sdio_disable_func(func);
		sdio_release_host(func);
		sdio_set_drvdata(func, शून्य);
		kमुक्त(self);
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक cw1200_sdio_suspend(काष्ठा device *dev)
अणु
	पूर्णांक ret;
	काष्ठा sdio_func *func = dev_to_sdio_func(dev);
	काष्ठा hwbus_priv *self = sdio_get_drvdata(func);

	अगर (!cw1200_can_suspend(self->core))
		वापस -EAGAIN;

	/* Notअगरy SDIO that CW1200 will reमुख्य घातered during suspend */
	ret = sdio_set_host_pm_flags(func, MMC_PM_KEEP_POWER);
	अगर (ret)
		pr_err("Error setting SDIO pm flags: %i\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक cw1200_sdio_resume(काष्ठा device *dev)
अणु
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops cw1200_pm_ops = अणु
	.suspend = cw1200_sdio_suspend,
	.resume = cw1200_sdio_resume,
पूर्ण;
#पूर्ण_अगर

अटल काष्ठा sdio_driver sdio_driver = अणु
	.name		= "cw1200_wlan_sdio",
	.id_table	= cw1200_sdio_ids,
	.probe		= cw1200_sdio_probe,
	.हटाओ		= cw1200_sdio_disconnect,
#अगर_घोषित CONFIG_PM
	.drv = अणु
		.pm = &cw1200_pm_ops,
	पूर्ण
#पूर्ण_अगर
पूर्ण;

/* Init Module function -> Called by insmod */
अटल पूर्णांक __init cw1200_sdio_init(व्योम)
अणु
	स्थिर काष्ठा cw1200_platक्रमm_data_sdio *pdata;
	पूर्णांक ret;

	/* FIXME -- this won't support multiple devices */
	pdata = global_plat_data;

	अगर (cw1200_sdio_on(pdata)) अणु
		ret = -1;
		जाओ err;
	पूर्ण

	ret = sdio_रेजिस्टर_driver(&sdio_driver);
	अगर (ret)
		जाओ err;

	वापस 0;

err:
	cw1200_sdio_off(pdata);
	वापस ret;
पूर्ण

/* Called at Driver Unloading */
अटल व्योम __निकास cw1200_sdio_निकास(व्योम)
अणु
	स्थिर काष्ठा cw1200_platक्रमm_data_sdio *pdata;

	/* FIXME -- this won't support multiple devices */
	pdata = global_plat_data;
	sdio_unरेजिस्टर_driver(&sdio_driver);
	cw1200_sdio_off(pdata);
पूर्ण


module_init(cw1200_sdio_init);
module_निकास(cw1200_sdio_निकास);
