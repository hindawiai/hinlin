<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Arche Platक्रमm driver to enable Unipro link.
 *
 * Copyright 2014-2015 Google Inc.
 * Copyright 2014-2015 Linaro Ltd.
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/pinctrl/consumer.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/suspend.h>
#समावेश <linux/समय.स>
#समावेश <linux/greybus.h>
#समावेश "arche_platform.h"

#अगर IS_ENABLED(CONFIG_USB_HSIC_USB3613)
#समावेश <linux/usb/usb3613.h>
#अन्यथा
अटल अंतरभूत पूर्णांक usb3613_hub_mode_ctrl(bool unused)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

#घोषणा WD_COLDBOOT_PULSE_WIDTH_MS	30

क्रमागत svc_wakedetect_state अणु
	WD_STATE_IDLE,			/* Default state = pulled high/low */
	WD_STATE_BOOT_INIT,		/* WD = falling edge (low) */
	WD_STATE_COLDBOOT_TRIG,		/* WD = rising edge (high), > 30msec */
	WD_STATE_STANDBYBOOT_TRIG,	/* As of now not used ?? */
	WD_STATE_COLDBOOT_START,	/* Cold boot process started */
	WD_STATE_STANDBYBOOT_START,	/* Not used */
पूर्ण;

काष्ठा arche_platक्रमm_drvdata अणु
	/* Control GPIO संकेतs to and from AP <=> SVC */
	काष्ठा gpio_desc *svc_reset;
	bool is_reset_act_hi;
	काष्ठा gpio_desc *svc_sysboot;
	काष्ठा gpio_desc *wake_detect; /* bi-dir,maps to WAKE_MOD & WAKE_FRAME संकेतs */

	क्रमागत arche_platक्रमm_state state;

	काष्ठा gpio_desc *svc_refclk_req;
	काष्ठा clk *svc_ref_clk;

	काष्ठा pinctrl *pinctrl;
	काष्ठा pinctrl_state *pin_शेष;

	पूर्णांक num_apbs;

	क्रमागत svc_wakedetect_state wake_detect_state;
	पूर्णांक wake_detect_irq;
	spinlock_t wake_lock;			/* Protect wake_detect_state */
	काष्ठा mutex platक्रमm_state_mutex;	/* Protect state */
	अचिन्हित दीर्घ wake_detect_start;
	काष्ठा notअगरier_block pm_notअगरier;

	काष्ठा device *dev;
पूर्ण;

/* Requires calling context to hold arche_pdata->platक्रमm_state_mutex */
अटल व्योम arche_platक्रमm_set_state(काष्ठा arche_platक्रमm_drvdata *arche_pdata,
				     क्रमागत arche_platक्रमm_state state)
अणु
	arche_pdata->state = state;
पूर्ण

/* Requires arche_pdata->wake_lock is held by calling context */
अटल व्योम arche_platक्रमm_set_wake_detect_state(काष्ठा arche_platक्रमm_drvdata *arche_pdata,
						 क्रमागत svc_wakedetect_state state)
अणु
	arche_pdata->wake_detect_state = state;
पूर्ण

अटल अंतरभूत व्योम svc_reset_onoff(काष्ठा gpio_desc *gpio, bool onoff)
अणु
	gpiod_set_raw_value(gpio, onoff);
पूर्ण

अटल पूर्णांक apb_cold_boot(काष्ठा device *dev, व्योम *data)
अणु
	पूर्णांक ret;

	ret = apb_ctrl_coldboot(dev);
	अगर (ret)
		dev_warn(dev, "failed to coldboot\n");

	/*Child nodes are independent, so करो not निकास coldboot operation */
	वापस 0;
पूर्ण

अटल पूर्णांक apb_घातeroff(काष्ठा device *dev, व्योम *data)
अणु
	apb_ctrl_घातeroff(dev);

	/* Enable HUB3613 पूर्णांकo HUB mode. */
	अगर (usb3613_hub_mode_ctrl(false))
		dev_warn(dev, "failed to control hub device\n");

	वापस 0;
पूर्ण

अटल व्योम arche_platक्रमm_wd_irq_en(काष्ठा arche_platक्रमm_drvdata *arche_pdata)
अणु
	/* Enable पूर्णांकerrupt here, to पढ़ो event back from SVC */
	enable_irq(arche_pdata->wake_detect_irq);
पूर्ण

अटल irqवापस_t arche_platक्रमm_wd_irq_thपढ़ो(पूर्णांक irq, व्योम *devid)
अणु
	काष्ठा arche_platक्रमm_drvdata *arche_pdata = devid;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&arche_pdata->wake_lock, flags);
	अगर (arche_pdata->wake_detect_state != WD_STATE_COLDBOOT_TRIG) अणु
		/* Something is wrong */
		spin_unlock_irqrestore(&arche_pdata->wake_lock, flags);
		वापस IRQ_HANDLED;
	पूर्ण

	arche_platक्रमm_set_wake_detect_state(arche_pdata,
					     WD_STATE_COLDBOOT_START);
	spin_unlock_irqrestore(&arche_pdata->wake_lock, flags);

	/* It should complete घातer cycle, so first make sure it is घातeroff */
	device_क्रम_each_child(arche_pdata->dev, शून्य, apb_घातeroff);

	/* Bring APB out of reset: cold boot sequence */
	device_क्रम_each_child(arche_pdata->dev, शून्य, apb_cold_boot);

	/* Enable HUB3613 पूर्णांकo HUB mode. */
	अगर (usb3613_hub_mode_ctrl(true))
		dev_warn(arche_pdata->dev, "failed to control hub device\n");

	spin_lock_irqsave(&arche_pdata->wake_lock, flags);
	arche_platक्रमm_set_wake_detect_state(arche_pdata, WD_STATE_IDLE);
	spin_unlock_irqrestore(&arche_pdata->wake_lock, flags);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t arche_platक्रमm_wd_irq(पूर्णांक irq, व्योम *devid)
अणु
	काष्ठा arche_platक्रमm_drvdata *arche_pdata = devid;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&arche_pdata->wake_lock, flags);

	अगर (gpiod_get_value(arche_pdata->wake_detect)) अणु
		/* wake/detect rising */

		/*
		 * If wake/detect line goes high after low, within less than
		 * 30msec, then standby boot sequence is initiated, which is not
		 * supported/implemented as of now. So ignore it.
		 */
		अगर (arche_pdata->wake_detect_state == WD_STATE_BOOT_INIT) अणु
			अगर (समय_beक्रमe(jअगरfies,
					arche_pdata->wake_detect_start +
					msecs_to_jअगरfies(WD_COLDBOOT_PULSE_WIDTH_MS))) अणु
				arche_platक्रमm_set_wake_detect_state(arche_pdata,
								     WD_STATE_IDLE);
			पूर्ण अन्यथा अणु
				/*
				 * Check we are not in middle of irq thपढ़ो
				 * alपढ़ोy
				 */
				अगर (arche_pdata->wake_detect_state !=
						WD_STATE_COLDBOOT_START) अणु
					arche_platक्रमm_set_wake_detect_state(arche_pdata,
									     WD_STATE_COLDBOOT_TRIG);
					spin_unlock_irqrestore(&arche_pdata->wake_lock,
							       flags);
					वापस IRQ_WAKE_THREAD;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		/* wake/detect falling */
		अगर (arche_pdata->wake_detect_state == WD_STATE_IDLE) अणु
			arche_pdata->wake_detect_start = jअगरfies;
			/*
			 * In the beginning, when wake/detect goes low
			 * (first समय), we assume it is meant क्रम coldboot
			 * and set the flag. If wake/detect line stays low
			 * beyond 30msec, then it is coldboot अन्यथा fallback
			 * to standby boot.
			 */
			arche_platक्रमm_set_wake_detect_state(arche_pdata,
							     WD_STATE_BOOT_INIT);
		पूर्ण
	पूर्ण

	spin_unlock_irqrestore(&arche_pdata->wake_lock, flags);

	वापस IRQ_HANDLED;
पूर्ण

/*
 * Requires arche_pdata->platक्रमm_state_mutex to be held
 */
अटल पूर्णांक
arche_platक्रमm_coldboot_seq(काष्ठा arche_platक्रमm_drvdata *arche_pdata)
अणु
	पूर्णांक ret;

	अगर (arche_pdata->state == ARCHE_PLATFORM_STATE_ACTIVE)
		वापस 0;

	dev_info(arche_pdata->dev, "Booting from cold boot state\n");

	svc_reset_onoff(arche_pdata->svc_reset, arche_pdata->is_reset_act_hi);

	gpiod_set_value(arche_pdata->svc_sysboot, 0);
	usleep_range(100, 200);

	ret = clk_prepare_enable(arche_pdata->svc_ref_clk);
	अगर (ret) अणु
		dev_err(arche_pdata->dev, "failed to enable svc_ref_clk: %d\n",
			ret);
		वापस ret;
	पूर्ण

	/* bring SVC out of reset */
	svc_reset_onoff(arche_pdata->svc_reset, !arche_pdata->is_reset_act_hi);

	arche_platक्रमm_set_state(arche_pdata, ARCHE_PLATFORM_STATE_ACTIVE);

	वापस 0;
पूर्ण

/*
 * Requires arche_pdata->platक्रमm_state_mutex to be held
 */
अटल पूर्णांक
arche_platक्रमm_fw_flashing_seq(काष्ठा arche_platक्रमm_drvdata *arche_pdata)
अणु
	पूर्णांक ret;

	अगर (arche_pdata->state == ARCHE_PLATFORM_STATE_FW_FLASHING)
		वापस 0;

	dev_info(arche_pdata->dev, "Switching to FW flashing state\n");

	svc_reset_onoff(arche_pdata->svc_reset, arche_pdata->is_reset_act_hi);

	gpiod_set_value(arche_pdata->svc_sysboot, 1);

	usleep_range(100, 200);

	ret = clk_prepare_enable(arche_pdata->svc_ref_clk);
	अगर (ret) अणु
		dev_err(arche_pdata->dev, "failed to enable svc_ref_clk: %d\n",
			ret);
		वापस ret;
	पूर्ण

	svc_reset_onoff(arche_pdata->svc_reset,	!arche_pdata->is_reset_act_hi);

	arche_platक्रमm_set_state(arche_pdata, ARCHE_PLATFORM_STATE_FW_FLASHING);

	वापस 0;
पूर्ण

/*
 * Requires arche_pdata->platक्रमm_state_mutex to be held
 */
अटल व्योम
arche_platक्रमm_घातeroff_seq(काष्ठा arche_platक्रमm_drvdata *arche_pdata)
अणु
	अचिन्हित दीर्घ flags;

	अगर (arche_pdata->state == ARCHE_PLATFORM_STATE_OFF)
		वापस;

	/* If in fw_flashing mode, then no need to repeate things again */
	अगर (arche_pdata->state != ARCHE_PLATFORM_STATE_FW_FLASHING) अणु
		disable_irq(arche_pdata->wake_detect_irq);

		spin_lock_irqsave(&arche_pdata->wake_lock, flags);
		arche_platक्रमm_set_wake_detect_state(arche_pdata,
						     WD_STATE_IDLE);
		spin_unlock_irqrestore(&arche_pdata->wake_lock, flags);
	पूर्ण

	clk_disable_unprepare(arche_pdata->svc_ref_clk);

	/* As part of निकास, put APB back in reset state */
	svc_reset_onoff(arche_pdata->svc_reset,	arche_pdata->is_reset_act_hi);

	arche_platक्रमm_set_state(arche_pdata, ARCHE_PLATFORM_STATE_OFF);
पूर्ण

अटल sमाप_प्रकार state_store(काष्ठा device *dev,
			   काष्ठा device_attribute *attr,
			   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा arche_platक्रमm_drvdata *arche_pdata = dev_get_drvdata(dev);
	पूर्णांक ret = 0;

	mutex_lock(&arche_pdata->platक्रमm_state_mutex);

	अगर (sysfs_streq(buf, "off")) अणु
		अगर (arche_pdata->state == ARCHE_PLATFORM_STATE_OFF)
			जाओ निकास;

		/*  If SVC goes करोwn, bring करोwn APB's as well */
		device_क्रम_each_child(arche_pdata->dev, शून्य, apb_घातeroff);

		arche_platक्रमm_घातeroff_seq(arche_pdata);

	पूर्ण अन्यथा अगर (sysfs_streq(buf, "active")) अणु
		अगर (arche_pdata->state == ARCHE_PLATFORM_STATE_ACTIVE)
			जाओ निकास;

		/* First we want to make sure we घातer off everything
		 * and then activate back again
		 */
		device_क्रम_each_child(arche_pdata->dev, शून्य, apb_घातeroff);
		arche_platक्रमm_घातeroff_seq(arche_pdata);

		arche_platक्रमm_wd_irq_en(arche_pdata);
		ret = arche_platक्रमm_coldboot_seq(arche_pdata);
		अगर (ret)
			जाओ निकास;

	पूर्ण अन्यथा अगर (sysfs_streq(buf, "standby")) अणु
		अगर (arche_pdata->state == ARCHE_PLATFORM_STATE_STANDBY)
			जाओ निकास;

		dev_warn(arche_pdata->dev, "standby state not supported\n");
	पूर्ण अन्यथा अगर (sysfs_streq(buf, "fw_flashing")) अणु
		अगर (arche_pdata->state == ARCHE_PLATFORM_STATE_FW_FLASHING)
			जाओ निकास;

		/*
		 * Here we only control SVC.
		 *
		 * In हाल of FW_FLASHING mode we करो not want to control
		 * APBs, as in हाल of V2, SPI bus is shared between both
		 * the APBs. So let user chose which APB he wants to flash.
		 */
		arche_platक्रमm_घातeroff_seq(arche_pdata);

		ret = arche_platक्रमm_fw_flashing_seq(arche_pdata);
		अगर (ret)
			जाओ निकास;
	पूर्ण अन्यथा अणु
		dev_err(arche_pdata->dev, "unknown state\n");
		ret = -EINVAL;
	पूर्ण

निकास:
	mutex_unlock(&arche_pdata->platक्रमm_state_mutex);
	वापस ret ? ret : count;
पूर्ण

अटल sमाप_प्रकार state_show(काष्ठा device *dev,
			  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा arche_platक्रमm_drvdata *arche_pdata = dev_get_drvdata(dev);

	चयन (arche_pdata->state) अणु
	हाल ARCHE_PLATFORM_STATE_OFF:
		वापस प्र_लिखो(buf, "off\n");
	हाल ARCHE_PLATFORM_STATE_ACTIVE:
		वापस प्र_लिखो(buf, "active\n");
	हाल ARCHE_PLATFORM_STATE_STANDBY:
		वापस प्र_लिखो(buf, "standby\n");
	हाल ARCHE_PLATFORM_STATE_FW_FLASHING:
		वापस प्र_लिखो(buf, "fw_flashing\n");
	शेष:
		वापस प्र_लिखो(buf, "unknown state\n");
	पूर्ण
पूर्ण

अटल DEVICE_ATTR_RW(state);

अटल पूर्णांक arche_platक्रमm_pm_notअगरier(काष्ठा notअगरier_block *notअगरier,
				      अचिन्हित दीर्घ pm_event, व्योम *unused)
अणु
	काष्ठा arche_platक्रमm_drvdata *arche_pdata =
		container_of(notअगरier, काष्ठा arche_platक्रमm_drvdata,
			     pm_notअगरier);
	पूर्णांक ret = NOTIFY_DONE;

	mutex_lock(&arche_pdata->platक्रमm_state_mutex);
	चयन (pm_event) अणु
	हाल PM_SUSPEND_PREPARE:
		अगर (arche_pdata->state != ARCHE_PLATFORM_STATE_ACTIVE) अणु
			ret = NOTIFY_STOP;
			अवरोध;
		पूर्ण
		device_क्रम_each_child(arche_pdata->dev, शून्य, apb_घातeroff);
		arche_platक्रमm_घातeroff_seq(arche_pdata);
		अवरोध;
	हाल PM_POST_SUSPEND:
		अगर (arche_pdata->state != ARCHE_PLATFORM_STATE_OFF)
			अवरोध;

		arche_platक्रमm_wd_irq_en(arche_pdata);
		arche_platक्रमm_coldboot_seq(arche_pdata);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	mutex_unlock(&arche_pdata->platक्रमm_state_mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक arche_platक्रमm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा arche_platक्रमm_drvdata *arche_pdata;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev->of_node;
	पूर्णांक ret;
	अचिन्हित पूर्णांक flags;

	arche_pdata = devm_kzalloc(&pdev->dev, माप(*arche_pdata),
				   GFP_KERNEL);
	अगर (!arche_pdata)
		वापस -ENOMEM;

	/* setup svc reset gpio */
	arche_pdata->is_reset_act_hi = of_property_पढ़ो_bool(np,
							     "svc,reset-active-high");
	अगर (arche_pdata->is_reset_act_hi)
		flags = GPIOD_OUT_HIGH;
	अन्यथा
		flags = GPIOD_OUT_LOW;

	arche_pdata->svc_reset = devm_gpiod_get(dev, "svc,reset", flags);
	अगर (IS_ERR(arche_pdata->svc_reset)) अणु
		ret = PTR_ERR(arche_pdata->svc_reset);
		dev_err(dev, "failed to request svc-reset GPIO: %d\n", ret);
		वापस ret;
	पूर्ण
	arche_platक्रमm_set_state(arche_pdata, ARCHE_PLATFORM_STATE_OFF);

	arche_pdata->svc_sysboot = devm_gpiod_get(dev, "svc,sysboot",
						  GPIOD_OUT_LOW);
	अगर (IS_ERR(arche_pdata->svc_sysboot)) अणु
		ret = PTR_ERR(arche_pdata->svc_sysboot);
		dev_err(dev, "failed to request sysboot0 GPIO: %d\n", ret);
		वापस ret;
	पूर्ण

	/* setup the घड़ी request gpio first */
	arche_pdata->svc_refclk_req = devm_gpiod_get(dev, "svc,refclk-req",
						     GPIOD_IN);
	अगर (IS_ERR(arche_pdata->svc_refclk_req)) अणु
		ret = PTR_ERR(arche_pdata->svc_refclk_req);
		dev_err(dev, "failed to request svc-clk-req GPIO: %d\n", ret);
		वापस ret;
	पूर्ण

	/* setup refclk2 to follow the pin */
	arche_pdata->svc_ref_clk = devm_clk_get(dev, "svc_ref_clk");
	अगर (IS_ERR(arche_pdata->svc_ref_clk)) अणु
		ret = PTR_ERR(arche_pdata->svc_ref_clk);
		dev_err(dev, "failed to get svc_ref_clk: %d\n", ret);
		वापस ret;
	पूर्ण

	platक्रमm_set_drvdata(pdev, arche_pdata);

	arche_pdata->num_apbs = of_get_child_count(np);
	dev_dbg(dev, "Number of APB's available - %d\n", arche_pdata->num_apbs);

	arche_pdata->wake_detect = devm_gpiod_get(dev, "svc,wake-detect",
						  GPIOD_IN);
	अगर (IS_ERR(arche_pdata->wake_detect)) अणु
		ret = PTR_ERR(arche_pdata->wake_detect);
		dev_err(dev, "Failed requesting wake_detect GPIO: %d\n", ret);
		वापस ret;
	पूर्ण

	arche_platक्रमm_set_wake_detect_state(arche_pdata, WD_STATE_IDLE);

	arche_pdata->dev = &pdev->dev;

	spin_lock_init(&arche_pdata->wake_lock);
	mutex_init(&arche_pdata->platक्रमm_state_mutex);
	arche_pdata->wake_detect_irq =
		gpiod_to_irq(arche_pdata->wake_detect);

	ret = devm_request_thपढ़ोed_irq(dev, arche_pdata->wake_detect_irq,
					arche_platक्रमm_wd_irq,
					arche_platक्रमm_wd_irq_thपढ़ो,
					IRQF_TRIGGER_FALLING |
					IRQF_TRIGGER_RISING | IRQF_ONESHOT,
					dev_name(dev), arche_pdata);
	अगर (ret) अणु
		dev_err(dev, "failed to request wake detect IRQ %d\n", ret);
		वापस ret;
	पूर्ण
	disable_irq(arche_pdata->wake_detect_irq);

	ret = device_create_file(dev, &dev_attr_state);
	अगर (ret) अणु
		dev_err(dev, "failed to create state file in sysfs\n");
		वापस ret;
	पूर्ण

	ret = of_platक्रमm_populate(np, शून्य, शून्य, dev);
	अगर (ret) अणु
		dev_err(dev, "failed to populate child nodes %d\n", ret);
		जाओ err_device_हटाओ;
	पूर्ण

	arche_pdata->pm_notअगरier.notअगरier_call = arche_platक्रमm_pm_notअगरier;
	ret = रेजिस्टर_pm_notअगरier(&arche_pdata->pm_notअगरier);

	अगर (ret) अणु
		dev_err(dev, "failed to register pm notifier %d\n", ret);
		जाओ err_device_हटाओ;
	पूर्ण

	/* Explicitly घातer off अगर requested */
	अगर (!of_property_पढ़ो_bool(pdev->dev.of_node, "arche,init-off")) अणु
		mutex_lock(&arche_pdata->platक्रमm_state_mutex);
		ret = arche_platक्रमm_coldboot_seq(arche_pdata);
		अगर (ret) अणु
			dev_err(dev, "Failed to cold boot svc %d\n", ret);
			जाओ err_coldboot;
		पूर्ण
		arche_platक्रमm_wd_irq_en(arche_pdata);
		mutex_unlock(&arche_pdata->platक्रमm_state_mutex);
	पूर्ण

	dev_info(dev, "Device registered successfully\n");
	वापस 0;

err_coldboot:
	mutex_unlock(&arche_pdata->platक्रमm_state_mutex);
err_device_हटाओ:
	device_हटाओ_file(&pdev->dev, &dev_attr_state);
	वापस ret;
पूर्ण

अटल पूर्णांक arche_हटाओ_child(काष्ठा device *dev, व्योम *unused)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);

	platक्रमm_device_unरेजिस्टर(pdev);

	वापस 0;
पूर्ण

अटल पूर्णांक arche_platक्रमm_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा arche_platक्रमm_drvdata *arche_pdata = platक्रमm_get_drvdata(pdev);

	unरेजिस्टर_pm_notअगरier(&arche_pdata->pm_notअगरier);
	device_हटाओ_file(&pdev->dev, &dev_attr_state);
	device_क्रम_each_child(&pdev->dev, शून्य, arche_हटाओ_child);
	arche_platक्रमm_घातeroff_seq(arche_pdata);

	अगर (usb3613_hub_mode_ctrl(false))
		dev_warn(arche_pdata->dev, "failed to control hub device\n");
		/* TODO: Should we करो anything more here ?? */
	वापस 0;
पूर्ण

अटल __maybe_unused पूर्णांक arche_platक्रमm_suspend(काष्ठा device *dev)
अणु
	/*
	 * If timing profile premits, we may shutकरोwn bridge
	 * completely
	 *
	 * TODO: sequence ??
	 *
	 * Also, need to make sure we meet precondition क्रम unipro suspend
	 * Precondition: Definition ???
	 */
	वापस 0;
पूर्ण

अटल __maybe_unused पूर्णांक arche_platक्रमm_resume(काष्ठा device *dev)
अणु
	/*
	 * Atleast क्रम ES2 we have to meet the delay requirement between
	 * unipro चयन and AP bridge init, depending on whether bridge is in
	 * OFF state or standby state.
	 *
	 * Based on whether bridge is in standby or OFF state we may have to
	 * निश्चित multiple संकेतs. Please refer to WDM spec, क्रम more info.
	 *
	 */
	वापस 0;
पूर्ण

अटल व्योम arche_platक्रमm_shutकरोwn(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा arche_platक्रमm_drvdata *arche_pdata = platक्रमm_get_drvdata(pdev);

	arche_platक्रमm_घातeroff_seq(arche_pdata);

	usb3613_hub_mode_ctrl(false);
पूर्ण

अटल SIMPLE_DEV_PM_OPS(arche_platक्रमm_pm_ops,
			arche_platक्रमm_suspend,
			arche_platक्रमm_resume);

अटल स्थिर काष्ठा of_device_id arche_platक्रमm_of_match[] = अणु
	/* Use PID/VID of SVC device */
	अणु .compatible = "google,arche-platform", पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा of_device_id arche_combined_id[] = अणु
	/* Use PID/VID of SVC device */
	अणु .compatible = "google,arche-platform", पूर्ण,
	अणु .compatible = "usbffff,2", पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, arche_combined_id);

अटल काष्ठा platक्रमm_driver arche_platक्रमm_device_driver = अणु
	.probe		= arche_platक्रमm_probe,
	.हटाओ		= arche_platक्रमm_हटाओ,
	.shutकरोwn	= arche_platक्रमm_shutकरोwn,
	.driver		= अणु
		.name	= "arche-platform-ctrl",
		.pm	= &arche_platक्रमm_pm_ops,
		.of_match_table = arche_platक्रमm_of_match,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init arche_init(व्योम)
अणु
	पूर्णांक retval;

	retval = platक्रमm_driver_रेजिस्टर(&arche_platक्रमm_device_driver);
	अगर (retval)
		वापस retval;

	retval = arche_apb_init();
	अगर (retval)
		platक्रमm_driver_unरेजिस्टर(&arche_platक्रमm_device_driver);

	वापस retval;
पूर्ण
module_init(arche_init);

अटल व्योम __निकास arche_निकास(व्योम)
अणु
	arche_apb_निकास();
	platक्रमm_driver_unरेजिस्टर(&arche_platक्रमm_device_driver);
पूर्ण
module_निकास(arche_निकास);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Vaibhav Hiremath <vaibhav.hiremath@linaro.org>");
MODULE_DESCRIPTION("Arche Platform Driver");
