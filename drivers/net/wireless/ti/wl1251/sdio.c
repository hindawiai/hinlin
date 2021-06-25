<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * wl12xx SDIO routines
 *
 * Copyright (C) 2005 Texas Instruments Incorporated
 * Copyright (C) 2008 Google Inc
 * Copyright (C) 2009 Bob Copeland (me@bobcopeland.com)
 */
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/mmc/sdio_func.h>
#समावेश <linux/mmc/sdio_ids.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/wl12xx.h>
#समावेश <linux/irq.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/of.h>
#समावेश <linux/of_irq.h>

#समावेश "wl1251.h"

काष्ठा wl1251_sdio अणु
	काष्ठा sdio_func *func;
	u32 elp_val;
पूर्ण;

अटल काष्ठा sdio_func *wl_to_func(काष्ठा wl1251 *wl)
अणु
	काष्ठा wl1251_sdio *wl_sdio = wl->अगर_priv;
	वापस wl_sdio->func;
पूर्ण

अटल व्योम wl1251_sdio_पूर्णांकerrupt(काष्ठा sdio_func *func)
अणु
	काष्ठा wl1251 *wl = sdio_get_drvdata(func);

	wl1251_debug(DEBUG_IRQ, "IRQ");

	/* FIXME should be synchronous क्रम sdio */
	ieee80211_queue_work(wl->hw, &wl->irq_work);
पूर्ण

अटल स्थिर काष्ठा sdio_device_id wl1251_devices[] = अणु
	अणु SDIO_DEVICE(SDIO_VENDOR_ID_TI_WL1251, SDIO_DEVICE_ID_TI_WL1251) पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(sdio, wl1251_devices);


अटल व्योम wl1251_sdio_पढ़ो(काष्ठा wl1251 *wl, पूर्णांक addr,
			     व्योम *buf, माप_प्रकार len)
अणु
	पूर्णांक ret;
	काष्ठा sdio_func *func = wl_to_func(wl);

	sdio_claim_host(func);
	ret = sdio_स_नकल_fromio(func, buf, addr, len);
	अगर (ret)
		wl1251_error("sdio read failed (%d)", ret);
	sdio_release_host(func);
पूर्ण

अटल व्योम wl1251_sdio_ग_लिखो(काष्ठा wl1251 *wl, पूर्णांक addr,
			      व्योम *buf, माप_प्रकार len)
अणु
	पूर्णांक ret;
	काष्ठा sdio_func *func = wl_to_func(wl);

	sdio_claim_host(func);
	ret = sdio_स_नकल_toio(func, addr, buf, len);
	अगर (ret)
		wl1251_error("sdio write failed (%d)", ret);
	sdio_release_host(func);
पूर्ण

अटल व्योम wl1251_sdio_पढ़ो_elp(काष्ठा wl1251 *wl, पूर्णांक addr, u32 *val)
अणु
	पूर्णांक ret = 0;
	काष्ठा wl1251_sdio *wl_sdio = wl->अगर_priv;
	काष्ठा sdio_func *func = wl_sdio->func;

	/*
	 * The hardware only supports RAW (पढ़ो after ग_लिखो) access क्रम
	 * पढ़ोing, regular sdio_पढ़ोb won't work here (it पूर्णांकerprets
	 * the unused bits of CMD52 as ग_लिखो data even अगर we send पढ़ो
	 * request).
	 */
	sdio_claim_host(func);
	*val = sdio_ग_लिखोb_पढ़ोb(func, wl_sdio->elp_val, addr, &ret);
	sdio_release_host(func);

	अगर (ret)
		wl1251_error("sdio_readb failed (%d)", ret);
पूर्ण

अटल व्योम wl1251_sdio_ग_लिखो_elp(काष्ठा wl1251 *wl, पूर्णांक addr, u32 val)
अणु
	पूर्णांक ret = 0;
	काष्ठा wl1251_sdio *wl_sdio = wl->अगर_priv;
	काष्ठा sdio_func *func = wl_sdio->func;

	sdio_claim_host(func);
	sdio_ग_लिखोb(func, val, addr, &ret);
	sdio_release_host(func);

	अगर (ret)
		wl1251_error("sdio_writeb failed (%d)", ret);
	अन्यथा
		wl_sdio->elp_val = val;
पूर्ण

अटल व्योम wl1251_sdio_reset(काष्ठा wl1251 *wl)
अणु
पूर्ण

अटल व्योम wl1251_sdio_enable_irq(काष्ठा wl1251 *wl)
अणु
	काष्ठा sdio_func *func = wl_to_func(wl);

	sdio_claim_host(func);
	sdio_claim_irq(func, wl1251_sdio_पूर्णांकerrupt);
	sdio_release_host(func);
पूर्ण

अटल व्योम wl1251_sdio_disable_irq(काष्ठा wl1251 *wl)
अणु
	काष्ठा sdio_func *func = wl_to_func(wl);

	sdio_claim_host(func);
	sdio_release_irq(func);
	sdio_release_host(func);
पूर्ण

/* Interrupts when using dedicated WLAN_IRQ pin */
अटल irqवापस_t wl1251_line_irq(पूर्णांक irq, व्योम *cookie)
अणु
	काष्ठा wl1251 *wl = cookie;

	ieee80211_queue_work(wl->hw, &wl->irq_work);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम wl1251_enable_line_irq(काष्ठा wl1251 *wl)
अणु
	वापस enable_irq(wl->irq);
पूर्ण

अटल व्योम wl1251_disable_line_irq(काष्ठा wl1251 *wl)
अणु
	वापस disable_irq(wl->irq);
पूर्ण

अटल पूर्णांक wl1251_sdio_set_घातer(काष्ठा wl1251 *wl, bool enable)
अणु
	काष्ठा sdio_func *func = wl_to_func(wl);
	पूर्णांक ret;

	अगर (enable) अणु
		ret = pm_runसमय_get_sync(&func->dev);
		अगर (ret < 0) अणु
			pm_runसमय_put_sync(&func->dev);
			जाओ out;
		पूर्ण

		sdio_claim_host(func);
		sdio_enable_func(func);
		sdio_release_host(func);
	पूर्ण अन्यथा अणु
		sdio_claim_host(func);
		sdio_disable_func(func);
		sdio_release_host(func);

		ret = pm_runसमय_put_sync(&func->dev);
		अगर (ret < 0)
			जाओ out;
	पूर्ण

out:
	वापस ret;
पूर्ण

अटल काष्ठा wl1251_अगर_operations wl1251_sdio_ops = अणु
	.पढ़ो = wl1251_sdio_पढ़ो,
	.ग_लिखो = wl1251_sdio_ग_लिखो,
	.ग_लिखो_elp = wl1251_sdio_ग_लिखो_elp,
	.पढ़ो_elp = wl1251_sdio_पढ़ो_elp,
	.reset = wl1251_sdio_reset,
	.घातer = wl1251_sdio_set_घातer,
पूर्ण;

अटल पूर्णांक wl1251_sdio_probe(काष्ठा sdio_func *func,
			     स्थिर काष्ठा sdio_device_id *id)
अणु
	पूर्णांक ret;
	काष्ठा wl1251 *wl;
	काष्ठा ieee80211_hw *hw;
	काष्ठा wl1251_sdio *wl_sdio;
	स्थिर काष्ठा wl1251_platक्रमm_data *wl1251_board_data;
	काष्ठा device_node *np = func->dev.of_node;

	hw = wl1251_alloc_hw();
	अगर (IS_ERR(hw))
		वापस PTR_ERR(hw);

	wl = hw->priv;

	wl_sdio = kzalloc(माप(*wl_sdio), GFP_KERNEL);
	अगर (wl_sdio == शून्य) अणु
		ret = -ENOMEM;
		जाओ out_मुक्त_hw;
	पूर्ण

	sdio_claim_host(func);
	ret = sdio_enable_func(func);
	अगर (ret)
		जाओ release;

	sdio_set_block_size(func, 512);
	sdio_release_host(func);

	SET_IEEE80211_DEV(hw, &func->dev);
	wl_sdio->func = func;
	wl->अगर_priv = wl_sdio;
	wl->अगर_ops = &wl1251_sdio_ops;

	wl1251_board_data = wl1251_get_platक्रमm_data();
	अगर (!IS_ERR(wl1251_board_data)) अणु
		wl->irq = wl1251_board_data->irq;
		wl->use_eeprom = wl1251_board_data->use_eeprom;
	पूर्ण अन्यथा अगर (np) अणु
		wl->use_eeprom = of_property_पढ़ो_bool(np, "ti,wl1251-has-eeprom");
		wl->irq = of_irq_get(np, 0);
		अगर (wl->irq == -EPROBE_DEFER) अणु
			ret = -EPROBE_DEFER;
			जाओ disable;
		पूर्ण
	पूर्ण

	अगर (wl->irq) अणु
		irq_set_status_flags(wl->irq, IRQ_NOAUTOEN);
		ret = request_irq(wl->irq, wl1251_line_irq, 0, "wl1251", wl);
		अगर (ret < 0) अणु
			wl1251_error("request_irq() failed: %d", ret);
			जाओ disable;
		पूर्ण

		irq_set_irq_type(wl->irq, IRQ_TYPE_EDGE_RISING);

		wl1251_sdio_ops.enable_irq = wl1251_enable_line_irq;
		wl1251_sdio_ops.disable_irq = wl1251_disable_line_irq;

		wl1251_info("using dedicated interrupt line");
	पूर्ण अन्यथा अणु
		wl1251_sdio_ops.enable_irq = wl1251_sdio_enable_irq;
		wl1251_sdio_ops.disable_irq = wl1251_sdio_disable_irq;

		wl1251_info("using SDIO interrupt");
	पूर्ण

	ret = wl1251_init_ieee80211(wl);
	अगर (ret)
		जाओ out_मुक्त_irq;

	sdio_set_drvdata(func, wl);

	/* Tell PM core that we करोn't need the card to be घातered now */
	pm_runसमय_put_noidle(&func->dev);

	वापस ret;

out_मुक्त_irq:
	अगर (wl->irq)
		मुक्त_irq(wl->irq, wl);
disable:
	sdio_claim_host(func);
	sdio_disable_func(func);
release:
	sdio_release_host(func);
	kमुक्त(wl_sdio);
out_मुक्त_hw:
	wl1251_मुक्त_hw(wl);
	वापस ret;
पूर्ण

अटल व्योम wl1251_sdio_हटाओ(काष्ठा sdio_func *func)
अणु
	काष्ठा wl1251 *wl = sdio_get_drvdata(func);
	काष्ठा wl1251_sdio *wl_sdio = wl->अगर_priv;

	/* Unकरो decrement करोne above in wl1251_probe */
	pm_runसमय_get_noresume(&func->dev);

	अगर (wl->irq)
		मुक्त_irq(wl->irq, wl);
	wl1251_मुक्त_hw(wl);
	kमुक्त(wl_sdio);

	sdio_claim_host(func);
	sdio_release_irq(func);
	sdio_disable_func(func);
	sdio_release_host(func);
पूर्ण

अटल पूर्णांक wl1251_suspend(काष्ठा device *dev)
अणु
	/*
	 * Tell MMC/SDIO core it's OK to घातer करोwn the card
	 * (अगर it isn't alपढ़ोy), but not to हटाओ it completely.
	 */
	वापस 0;
पूर्ण

अटल पूर्णांक wl1251_resume(काष्ठा device *dev)
अणु
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops wl1251_sdio_pm_ops = अणु
	.suspend        = wl1251_suspend,
	.resume         = wl1251_resume,
पूर्ण;

अटल काष्ठा sdio_driver wl1251_sdio_driver = अणु
	.name		= "wl1251_sdio",
	.id_table	= wl1251_devices,
	.probe		= wl1251_sdio_probe,
	.हटाओ		= wl1251_sdio_हटाओ,
	.drv.pm		= &wl1251_sdio_pm_ops,
पूर्ण;

अटल पूर्णांक __init wl1251_sdio_init(व्योम)
अणु
	पूर्णांक err;

	err = sdio_रेजिस्टर_driver(&wl1251_sdio_driver);
	अगर (err)
		wl1251_error("failed to register sdio driver: %d", err);
	वापस err;
पूर्ण

अटल व्योम __निकास wl1251_sdio_निकास(व्योम)
अणु
	sdio_unरेजिस्टर_driver(&wl1251_sdio_driver);
	wl1251_notice("unloaded");
पूर्ण

module_init(wl1251_sdio_init);
module_निकास(wl1251_sdio_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Kalle Valo <kvalo@adurom.com>");
