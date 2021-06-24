<शैली गुरु>
// SPDX-License-Identअगरier: GPL-1.0+
/*
 * Renesas USB driver
 *
 * Copyright (C) 2011 Renesas Solutions Corp.
 * Copyright (C) 2019 Renesas Electronics Corporation
 * Kuninori Morimoto <kuninori.morimoto.gx@renesas.com>
 */
#समावेश <linux/clk.h>
#समावेश <linux/err.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/reset.h>
#समावेश <linux/slab.h>
#समावेश <linux/sysfs.h>
#समावेश "common.h"
#समावेश "rcar2.h"
#समावेश "rcar3.h"
#समावेश "rza.h"

/*
 *		image of renesas_usbhs
 *
 * ex) gadget हाल

 * mod.c
 * mod_gadget.c
 * mod_host.c		pipe.c		fअगरo.c
 *
 *			+-------+	+-----------+
 *			| pipe0 |------>| fअगरo pio  |
 * +------------+	+-------+	+-----------+
 * | mod_gadget |=====> | pipe1 |--+
 * +------------+	+-------+  |	+-----------+
 *			| pipe2 |  |  +-| fअगरo dma0 |
 * +------------+	+-------+  |  |	+-----------+
 * | mod_host   |	| pipe3 |<-|--+
 * +------------+	+-------+  |	+-----------+
 *			| ....  |  +--->| fअगरo dma1 |
 *			| ....  |	+-----------+
 */

/*
 * platक्रमm call back
 *
 * renesas usb support platक्रमm callback function.
 * Below macro call it.
 * अगर platक्रमm करोesn't have callback, it वापस 0 (no error)
 */
#घोषणा usbhs_platक्रमm_call(priv, func, args...)\
	(!(priv) ? -ENODEV :			\
	 !((priv)->pfunc->func) ? 0 :		\
	 (priv)->pfunc->func(args))

/*
 *		common functions
 */
u16 usbhs_पढ़ो(काष्ठा usbhs_priv *priv, u32 reg)
अणु
	वापस ioपढ़ो16(priv->base + reg);
पूर्ण

व्योम usbhs_ग_लिखो(काष्ठा usbhs_priv *priv, u32 reg, u16 data)
अणु
	ioग_लिखो16(data, priv->base + reg);
पूर्ण

व्योम usbhs_bset(काष्ठा usbhs_priv *priv, u32 reg, u16 mask, u16 data)
अणु
	u16 val = usbhs_पढ़ो(priv, reg);

	val &= ~mask;
	val |= data & mask;

	usbhs_ग_लिखो(priv, reg, val);
पूर्ण

काष्ठा usbhs_priv *usbhs_pdev_to_priv(काष्ठा platक्रमm_device *pdev)
अणु
	वापस dev_get_drvdata(&pdev->dev);
पूर्ण

पूर्णांक usbhs_get_id_as_gadget(काष्ठा platक्रमm_device *pdev)
अणु
	वापस USBHS_GADGET;
पूर्ण

/*
 *		syscfg functions
 */
अटल व्योम usbhs_sys_घड़ी_ctrl(काष्ठा usbhs_priv *priv, पूर्णांक enable)
अणु
	usbhs_bset(priv, SYSCFG, SCKE, enable ? SCKE : 0);
पूर्ण

व्योम usbhs_sys_host_ctrl(काष्ठा usbhs_priv *priv, पूर्णांक enable)
अणु
	u16 mask = DCFM | DRPD | DPRPU | HSE | USBE;
	u16 val  = DCFM | DRPD | HSE | USBE;

	/*
	 * अगर enable
	 *
	 * - select Host mode
	 * - D+ Line/D- Line Pull-करोwn
	 */
	usbhs_bset(priv, SYSCFG, mask, enable ? val : 0);
पूर्ण

व्योम usbhs_sys_function_ctrl(काष्ठा usbhs_priv *priv, पूर्णांक enable)
अणु
	u16 mask = DCFM | DRPD | DPRPU | HSE | USBE;
	u16 val  = HSE | USBE;

	/* CNEN bit is required क्रम function operation */
	अगर (usbhs_get_dparam(priv, has_cnen)) अणु
		mask |= CNEN;
		val  |= CNEN;
	पूर्ण

	/*
	 * अगर enable
	 *
	 * - select Function mode
	 * - D+ Line Pull-up is disabled
	 *      When D+ Line Pull-up is enabled,
	 *      calling usbhs_sys_function_pullup(,1)
	 */
	usbhs_bset(priv, SYSCFG, mask, enable ? val : 0);
पूर्ण

व्योम usbhs_sys_function_pullup(काष्ठा usbhs_priv *priv, पूर्णांक enable)
अणु
	usbhs_bset(priv, SYSCFG, DPRPU, enable ? DPRPU : 0);
पूर्ण

व्योम usbhs_sys_set_test_mode(काष्ठा usbhs_priv *priv, u16 mode)
अणु
	usbhs_ग_लिखो(priv, TESTMODE, mode);
पूर्ण

/*
 *		frame functions
 */
पूर्णांक usbhs_frame_get_num(काष्ठा usbhs_priv *priv)
अणु
	वापस usbhs_पढ़ो(priv, FRMNUM) & FRNM_MASK;
पूर्ण

/*
 *		usb request functions
 */
व्योम usbhs_usbreq_get_val(काष्ठा usbhs_priv *priv, काष्ठा usb_ctrlrequest *req)
अणु
	u16 val;

	val = usbhs_पढ़ो(priv, USBREQ);
	req->bRequest		= (val >> 8) & 0xFF;
	req->bRequestType	= (val >> 0) & 0xFF;

	req->wValue	= cpu_to_le16(usbhs_पढ़ो(priv, USBVAL));
	req->wIndex	= cpu_to_le16(usbhs_पढ़ो(priv, USBINDX));
	req->wLength	= cpu_to_le16(usbhs_पढ़ो(priv, USBLENG));
पूर्ण

व्योम usbhs_usbreq_set_val(काष्ठा usbhs_priv *priv, काष्ठा usb_ctrlrequest *req)
अणु
	usbhs_ग_लिखो(priv, USBREQ,  (req->bRequest << 8) | req->bRequestType);
	usbhs_ग_लिखो(priv, USBVAL,  le16_to_cpu(req->wValue));
	usbhs_ग_लिखो(priv, USBINDX, le16_to_cpu(req->wIndex));
	usbhs_ग_लिखो(priv, USBLENG, le16_to_cpu(req->wLength));

	usbhs_bset(priv, DCPCTR, SUREQ, SUREQ);
पूर्ण

/*
 *		bus/vbus functions
 */
व्योम usbhs_bus_send_sof_enable(काष्ठा usbhs_priv *priv)
अणु
	u16 status = usbhs_पढ़ो(priv, DVSTCTR) & (USBRST | UACT);

	अगर (status != USBRST) अणु
		काष्ठा device *dev = usbhs_priv_to_dev(priv);
		dev_err(dev, "usbhs should be reset\n");
	पूर्ण

	usbhs_bset(priv, DVSTCTR, (USBRST | UACT), UACT);
पूर्ण

व्योम usbhs_bus_send_reset(काष्ठा usbhs_priv *priv)
अणु
	usbhs_bset(priv, DVSTCTR, (USBRST | UACT), USBRST);
पूर्ण

पूर्णांक usbhs_bus_get_speed(काष्ठा usbhs_priv *priv)
अणु
	u16 dvstctr = usbhs_पढ़ो(priv, DVSTCTR);

	चयन (RHST & dvstctr) अणु
	हाल RHST_LOW_SPEED:
		वापस USB_SPEED_LOW;
	हाल RHST_FULL_SPEED:
		वापस USB_SPEED_FULL;
	हाल RHST_HIGH_SPEED:
		वापस USB_SPEED_HIGH;
	पूर्ण

	वापस USB_SPEED_UNKNOWN;
पूर्ण

पूर्णांक usbhs_vbus_ctrl(काष्ठा usbhs_priv *priv, पूर्णांक enable)
अणु
	काष्ठा platक्रमm_device *pdev = usbhs_priv_to_pdev(priv);

	वापस usbhs_platक्रमm_call(priv, set_vbus, pdev, enable);
पूर्ण

अटल व्योम usbhsc_bus_init(काष्ठा usbhs_priv *priv)
अणु
	usbhs_ग_लिखो(priv, DVSTCTR, 0);

	usbhs_vbus_ctrl(priv, 0);
पूर्ण

/*
 *		device configuration
 */
पूर्णांक usbhs_set_device_config(काष्ठा usbhs_priv *priv, पूर्णांक devnum,
			   u16 upphub, u16 hubport, u16 speed)
अणु
	काष्ठा device *dev = usbhs_priv_to_dev(priv);
	u16 usbspd = 0;
	u32 reg = DEVADD0 + (2 * devnum);

	अगर (devnum > 10) अणु
		dev_err(dev, "cannot set speed to unknown device %d\n", devnum);
		वापस -EIO;
	पूर्ण

	अगर (upphub > 0xA) अणु
		dev_err(dev, "unsupported hub number %d\n", upphub);
		वापस -EIO;
	पूर्ण

	चयन (speed) अणु
	हाल USB_SPEED_LOW:
		usbspd = USBSPD_SPEED_LOW;
		अवरोध;
	हाल USB_SPEED_FULL:
		usbspd = USBSPD_SPEED_FULL;
		अवरोध;
	हाल USB_SPEED_HIGH:
		usbspd = USBSPD_SPEED_HIGH;
		अवरोध;
	शेष:
		dev_err(dev, "unsupported speed %d\n", speed);
		वापस -EIO;
	पूर्ण

	usbhs_ग_लिखो(priv, reg,	UPPHUB(upphub)	|
				HUBPORT(hubport)|
				USBSPD(usbspd));

	वापस 0;
पूर्ण

/*
 *		पूर्णांकerrupt functions
 */
व्योम usbhs_xxxsts_clear(काष्ठा usbhs_priv *priv, u16 sts_reg, u16 bit)
अणु
	u16 pipe_mask = (u16)GENMASK(usbhs_get_dparam(priv, pipe_size), 0);

	usbhs_ग_लिखो(priv, sts_reg, ~(1 << bit) & pipe_mask);
पूर्ण

/*
 *		local functions
 */
अटल व्योम usbhsc_set_busरुको(काष्ठा usbhs_priv *priv)
अणु
	पूर्णांक रुको = usbhs_get_dparam(priv, busरुको_bरुको);

	/* set bus रुको अगर platक्रमm have */
	अगर (रुको)
		usbhs_bset(priv, BUSWAIT, 0x000F, रुको);
पूर्ण

अटल bool usbhsc_is_multi_clks(काष्ठा usbhs_priv *priv)
अणु
	वापस priv->dparam.multi_clks;
पूर्ण

अटल पूर्णांक usbhsc_clk_get(काष्ठा device *dev, काष्ठा usbhs_priv *priv)
अणु
	अगर (!usbhsc_is_multi_clks(priv))
		वापस 0;

	/* The first घड़ी should exist */
	priv->clks[0] = of_clk_get(dev_of_node(dev), 0);
	अगर (IS_ERR(priv->clks[0]))
		वापस PTR_ERR(priv->clks[0]);

	/*
	 * To backward compatibility with old DT, this driver checks the वापस
	 * value अगर it's -ENOENT or not.
	 */
	priv->clks[1] = of_clk_get(dev_of_node(dev), 1);
	अगर (PTR_ERR(priv->clks[1]) == -ENOENT)
		priv->clks[1] = शून्य;
	अन्यथा अगर (IS_ERR(priv->clks[1]))
		वापस PTR_ERR(priv->clks[1]);

	वापस 0;
पूर्ण

अटल व्योम usbhsc_clk_put(काष्ठा usbhs_priv *priv)
अणु
	पूर्णांक i;

	अगर (!usbhsc_is_multi_clks(priv))
		वापस;

	क्रम (i = 0; i < ARRAY_SIZE(priv->clks); i++)
		clk_put(priv->clks[i]);
पूर्ण

अटल पूर्णांक usbhsc_clk_prepare_enable(काष्ठा usbhs_priv *priv)
अणु
	पूर्णांक i, ret;

	अगर (!usbhsc_is_multi_clks(priv))
		वापस 0;

	क्रम (i = 0; i < ARRAY_SIZE(priv->clks); i++) अणु
		ret = clk_prepare_enable(priv->clks[i]);
		अगर (ret) अणु
			जबतक (--i >= 0)
				clk_disable_unprepare(priv->clks[i]);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम usbhsc_clk_disable_unprepare(काष्ठा usbhs_priv *priv)
अणु
	पूर्णांक i;

	अगर (!usbhsc_is_multi_clks(priv))
		वापस;

	क्रम (i = 0; i < ARRAY_SIZE(priv->clks); i++)
		clk_disable_unprepare(priv->clks[i]);
पूर्ण

/*
 *		platक्रमm शेष param
 */

/* commonly used on old SH-Mobile SoCs */
अटल काष्ठा renesas_usbhs_driver_pipe_config usbhsc_शेष_pipe[] = अणु
	RENESAS_USBHS_PIPE(USB_ENDPOINT_XFER_CONTROL, 64, 0x00, false),
	RENESAS_USBHS_PIPE(USB_ENDPOINT_XFER_ISOC, 1024, 0x08, false),
	RENESAS_USBHS_PIPE(USB_ENDPOINT_XFER_ISOC, 1024, 0x18, false),
	RENESAS_USBHS_PIPE(USB_ENDPOINT_XFER_BULK, 512, 0x28, true),
	RENESAS_USBHS_PIPE(USB_ENDPOINT_XFER_BULK, 512, 0x38, true),
	RENESAS_USBHS_PIPE(USB_ENDPOINT_XFER_BULK, 512, 0x48, true),
	RENESAS_USBHS_PIPE(USB_ENDPOINT_XFER_INT, 64, 0x04, false),
	RENESAS_USBHS_PIPE(USB_ENDPOINT_XFER_INT, 64, 0x05, false),
	RENESAS_USBHS_PIPE(USB_ENDPOINT_XFER_INT, 64, 0x06, false),
	RENESAS_USBHS_PIPE(USB_ENDPOINT_XFER_INT, 64, 0x07, false),
पूर्ण;

/* commonly used on newer SH-Mobile and R-Car SoCs */
अटल काष्ठा renesas_usbhs_driver_pipe_config usbhsc_new_pipe[] = अणु
	RENESAS_USBHS_PIPE(USB_ENDPOINT_XFER_CONTROL, 64, 0x00, false),
	RENESAS_USBHS_PIPE(USB_ENDPOINT_XFER_ISOC, 1024, 0x08, true),
	RENESAS_USBHS_PIPE(USB_ENDPOINT_XFER_ISOC, 1024, 0x28, true),
	RENESAS_USBHS_PIPE(USB_ENDPOINT_XFER_BULK, 512, 0x48, true),
	RENESAS_USBHS_PIPE(USB_ENDPOINT_XFER_BULK, 512, 0x58, true),
	RENESAS_USBHS_PIPE(USB_ENDPOINT_XFER_BULK, 512, 0x68, true),
	RENESAS_USBHS_PIPE(USB_ENDPOINT_XFER_INT, 64, 0x04, false),
	RENESAS_USBHS_PIPE(USB_ENDPOINT_XFER_INT, 64, 0x05, false),
	RENESAS_USBHS_PIPE(USB_ENDPOINT_XFER_INT, 64, 0x06, false),
	RENESAS_USBHS_PIPE(USB_ENDPOINT_XFER_BULK, 512, 0x78, true),
	RENESAS_USBHS_PIPE(USB_ENDPOINT_XFER_BULK, 512, 0x88, true),
	RENESAS_USBHS_PIPE(USB_ENDPOINT_XFER_BULK, 512, 0x98, true),
	RENESAS_USBHS_PIPE(USB_ENDPOINT_XFER_BULK, 512, 0xa8, true),
	RENESAS_USBHS_PIPE(USB_ENDPOINT_XFER_BULK, 512, 0xb8, true),
	RENESAS_USBHS_PIPE(USB_ENDPOINT_XFER_BULK, 512, 0xc8, true),
	RENESAS_USBHS_PIPE(USB_ENDPOINT_XFER_BULK, 512, 0xd8, true),
पूर्ण;

/*
 *		घातer control
 */
अटल व्योम usbhsc_घातer_ctrl(काष्ठा usbhs_priv *priv, पूर्णांक enable)
अणु
	काष्ठा platक्रमm_device *pdev = usbhs_priv_to_pdev(priv);
	काष्ठा device *dev = usbhs_priv_to_dev(priv);

	अगर (enable) अणु
		/* enable PM */
		pm_runसमय_get_sync(dev);

		/* enable clks */
		अगर (usbhsc_clk_prepare_enable(priv))
			वापस;

		/* enable platक्रमm घातer */
		usbhs_platक्रमm_call(priv, घातer_ctrl, pdev, priv->base, enable);

		/* USB on */
		usbhs_sys_घड़ी_ctrl(priv, enable);
	पूर्ण अन्यथा अणु
		/* USB off */
		usbhs_sys_घड़ी_ctrl(priv, enable);

		/* disable platक्रमm घातer */
		usbhs_platक्रमm_call(priv, घातer_ctrl, pdev, priv->base, enable);

		/* disable clks */
		usbhsc_clk_disable_unprepare(priv);

		/* disable PM */
		pm_runसमय_put_sync(dev);
	पूर्ण
पूर्ण

/*
 *		hotplug
 */
अटल व्योम usbhsc_hotplug(काष्ठा usbhs_priv *priv)
अणु
	काष्ठा platक्रमm_device *pdev = usbhs_priv_to_pdev(priv);
	काष्ठा usbhs_mod *mod = usbhs_mod_get_current(priv);
	पूर्णांक id;
	पूर्णांक enable;
	पूर्णांक cable;
	पूर्णांक ret;

	/*
	 * get vbus status from platक्रमm
	 */
	enable = usbhs_mod_info_call(priv, get_vbus, pdev);

	/*
	 * get id from platक्रमm
	 */
	id = usbhs_platक्रमm_call(priv, get_id, pdev);

	अगर (enable && !mod) अणु
		अगर (priv->edev) अणु
			cable = extcon_get_state(priv->edev, EXTCON_USB_HOST);
			अगर ((cable > 0 && id != USBHS_HOST) ||
			    (!cable && id != USBHS_GADGET)) अणु
				dev_info(&pdev->dev,
					 "USB cable plugged in doesn't match the selected role!\n");
				वापस;
			पूर्ण
		पूर्ण

		ret = usbhs_mod_change(priv, id);
		अगर (ret < 0)
			वापस;

		dev_dbg(&pdev->dev, "%s enable\n", __func__);

		/* घातer on */
		अगर (usbhs_get_dparam(priv, runसमय_pwctrl))
			usbhsc_घातer_ctrl(priv, enable);

		/* bus init */
		usbhsc_set_busरुको(priv);
		usbhsc_bus_init(priv);

		/* module start */
		usbhs_mod_call(priv, start, priv);

	पूर्ण अन्यथा अगर (!enable && mod) अणु
		dev_dbg(&pdev->dev, "%s disable\n", __func__);

		/* module stop */
		usbhs_mod_call(priv, stop, priv);

		/* bus init */
		usbhsc_bus_init(priv);

		/* घातer off */
		अगर (usbhs_get_dparam(priv, runसमय_pwctrl))
			usbhsc_घातer_ctrl(priv, enable);

		usbhs_mod_change(priv, -1);

		/* reset phy क्रम next connection */
		usbhs_platक्रमm_call(priv, phy_reset, pdev);
	पूर्ण
पूर्ण

/*
 *		notअगरy hotplug
 */
अटल व्योम usbhsc_notअगरy_hotplug(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा usbhs_priv *priv = container_of(work,
					       काष्ठा usbhs_priv,
					       notअगरy_hotplug_work.work);
	usbhsc_hotplug(priv);
पूर्ण

पूर्णांक usbhsc_schedule_notअगरy_hotplug(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा usbhs_priv *priv = usbhs_pdev_to_priv(pdev);
	पूर्णांक delay = usbhs_get_dparam(priv, detection_delay);

	/*
	 * This functions will be called in पूर्णांकerrupt.
	 * To make sure safety context,
	 * use workqueue क्रम usbhs_notअगरy_hotplug
	 */
	schedule_delayed_work(&priv->notअगरy_hotplug_work,
			      msecs_to_jअगरfies(delay));
	वापस 0;
पूर्ण

/*
 *		platक्रमm functions
 */
अटल स्थिर काष्ठा of_device_id usbhs_of_match[] = अणु
	अणु
		.compatible = "renesas,usbhs-r8a774c0",
		.data = &usbhs_rcar_gen3_with_pll_plat_info,
	पूर्ण,
	अणु
		.compatible = "renesas,usbhs-r8a7790",
		.data = &usbhs_rcar_gen2_plat_info,
	पूर्ण,
	अणु
		.compatible = "renesas,usbhs-r8a7791",
		.data = &usbhs_rcar_gen2_plat_info,
	पूर्ण,
	अणु
		.compatible = "renesas,usbhs-r8a7794",
		.data = &usbhs_rcar_gen2_plat_info,
	पूर्ण,
	अणु
		.compatible = "renesas,usbhs-r8a7795",
		.data = &usbhs_rcar_gen3_plat_info,
	पूर्ण,
	अणु
		.compatible = "renesas,usbhs-r8a7796",
		.data = &usbhs_rcar_gen3_plat_info,
	पूर्ण,
	अणु
		.compatible = "renesas,usbhs-r8a77990",
		.data = &usbhs_rcar_gen3_with_pll_plat_info,
	पूर्ण,
	अणु
		.compatible = "renesas,usbhs-r8a77995",
		.data = &usbhs_rcar_gen3_with_pll_plat_info,
	पूर्ण,
	अणु
		.compatible = "renesas,rcar-gen2-usbhs",
		.data = &usbhs_rcar_gen2_plat_info,
	पूर्ण,
	अणु
		.compatible = "renesas,rcar-gen3-usbhs",
		.data = &usbhs_rcar_gen3_plat_info,
	पूर्ण,
	अणु
		.compatible = "renesas,rza1-usbhs",
		.data = &usbhs_rza1_plat_info,
	पूर्ण,
	अणु
		.compatible = "renesas,rza2-usbhs",
		.data = &usbhs_rza2_plat_info,
	पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, usbhs_of_match);

अटल पूर्णांक usbhs_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा renesas_usbhs_platक्रमm_info *info;
	काष्ठा usbhs_priv *priv;
	काष्ठा resource *irq_res;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा gpio_desc *gpiod;
	पूर्णांक ret;
	u32 पंचांगp;

	/* check device node */
	अगर (dev_of_node(dev))
		info = of_device_get_match_data(dev);
	अन्यथा
		info = renesas_usbhs_get_info(pdev);

	/* check platक्रमm inक्रमmation */
	अगर (!info) अणु
		dev_err(dev, "no platform information\n");
		वापस -EINVAL;
	पूर्ण

	/* platक्रमm data */
	irq_res = platक्रमm_get_resource(pdev, IORESOURCE_IRQ, 0);
	अगर (!irq_res) अणु
		dev_err(dev, "Not enough Renesas USB platform resources.\n");
		वापस -ENODEV;
	पूर्ण

	/* usb निजी data */
	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(priv->base))
		वापस PTR_ERR(priv->base);

	अगर (of_property_पढ़ो_bool(dev_of_node(dev), "extcon")) अणु
		priv->edev = extcon_get_edev_by_phandle(dev, 0);
		अगर (IS_ERR(priv->edev))
			वापस PTR_ERR(priv->edev);
	पूर्ण

	priv->rsts = devm_reset_control_array_get_optional_shared(dev);
	अगर (IS_ERR(priv->rsts))
		वापस PTR_ERR(priv->rsts);

	/*
	 * care platक्रमm info
	 */

	priv->dparam = info->driver_param;

	अगर (!info->platक्रमm_callback.get_id) अणु
		dev_err(dev, "no platform callbacks\n");
		वापस -EINVAL;
	पूर्ण
	priv->pfunc = &info->platक्रमm_callback;

	/* set शेष param अगर platक्रमm करोesn't have */
	अगर (usbhs_get_dparam(priv, has_new_pipe_configs)) अणु
		priv->dparam.pipe_configs = usbhsc_new_pipe;
		priv->dparam.pipe_size = ARRAY_SIZE(usbhsc_new_pipe);
	पूर्ण अन्यथा अगर (!priv->dparam.pipe_configs) अणु
		priv->dparam.pipe_configs = usbhsc_शेष_pipe;
		priv->dparam.pipe_size = ARRAY_SIZE(usbhsc_शेष_pipe);
	पूर्ण
	अगर (!priv->dparam.pio_dma_border)
		priv->dparam.pio_dma_border = 64; /* 64byte */
	अगर (!of_property_पढ़ो_u32(dev_of_node(dev), "renesas,buswait", &पंचांगp))
		priv->dparam.busरुको_bरुको = पंचांगp;
	gpiod = devm_gpiod_get_optional(dev, "renesas,enable", GPIOD_IN);
	अगर (IS_ERR(gpiod))
		वापस PTR_ERR(gpiod);

	/* FIXME */
	/* runसमय घातer control ? */
	अगर (priv->pfunc->get_vbus)
		usbhs_get_dparam(priv, runसमय_pwctrl) = 1;

	/*
	 * priv settings
	 */
	priv->irq	= irq_res->start;
	अगर (irq_res->flags & IORESOURCE_IRQ_SHAREABLE)
		priv->irqflags = IRQF_SHARED;
	priv->pdev	= pdev;
	INIT_DELAYED_WORK(&priv->notअगरy_hotplug_work, usbhsc_notअगरy_hotplug);
	spin_lock_init(usbhs_priv_to_lock(priv));

	/* call pipe and module init */
	ret = usbhs_pipe_probe(priv);
	अगर (ret < 0)
		वापस ret;

	ret = usbhs_fअगरo_probe(priv);
	अगर (ret < 0)
		जाओ probe_end_pipe_निकास;

	ret = usbhs_mod_probe(priv);
	अगर (ret < 0)
		जाओ probe_end_fअगरo_निकास;

	/* dev_set_drvdata should be called after usbhs_mod_init */
	platक्रमm_set_drvdata(pdev, priv);

	ret = reset_control_deनिश्चित(priv->rsts);
	अगर (ret)
		जाओ probe_fail_rst;

	ret = usbhsc_clk_get(dev, priv);
	अगर (ret)
		जाओ probe_fail_clks;

	/*
	 * deviece reset here because
	 * USB device might be used in boot loader.
	 */
	usbhs_sys_घड़ी_ctrl(priv, 0);

	/* check GPIO determining अगर USB function should be enabled */
	अगर (gpiod) अणु
		ret = !gpiod_get_value(gpiod);
		अगर (ret) अणु
			dev_warn(dev, "USB function not selected (GPIO)\n");
			ret = -ENOTSUPP;
			जाओ probe_end_mod_निकास;
		पूर्ण
	पूर्ण

	/*
	 * platक्रमm call
	 *
	 * USB phy setup might depend on CPU/Board.
	 * If platक्रमm has its callback functions,
	 * call it here.
	 */
	ret = usbhs_platक्रमm_call(priv, hardware_init, pdev);
	अगर (ret < 0) अणु
		dev_err(dev, "platform init failed.\n");
		जाओ probe_end_mod_निकास;
	पूर्ण

	/* reset phy क्रम connection */
	usbhs_platक्रमm_call(priv, phy_reset, pdev);

	/* घातer control */
	pm_runसमय_enable(dev);
	अगर (!usbhs_get_dparam(priv, runसमय_pwctrl)) अणु
		usbhsc_घातer_ctrl(priv, 1);
		usbhs_mod_स्वतःnomy_mode(priv);
	पूर्ण अन्यथा अणु
		usbhs_mod_non_स्वतःnomy_mode(priv);
	पूर्ण

	/*
	 * manual call notअगरy_hotplug क्रम cold plug
	 */
	usbhsc_schedule_notअगरy_hotplug(pdev);

	dev_info(dev, "probed\n");

	वापस ret;

probe_end_mod_निकास:
	usbhsc_clk_put(priv);
probe_fail_clks:
	reset_control_निश्चित(priv->rsts);
probe_fail_rst:
	usbhs_mod_हटाओ(priv);
probe_end_fअगरo_निकास:
	usbhs_fअगरo_हटाओ(priv);
probe_end_pipe_निकास:
	usbhs_pipe_हटाओ(priv);

	dev_info(dev, "probe failed (%d)\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक usbhs_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा usbhs_priv *priv = usbhs_pdev_to_priv(pdev);

	dev_dbg(&pdev->dev, "usb remove\n");

	/* घातer off */
	अगर (!usbhs_get_dparam(priv, runसमय_pwctrl))
		usbhsc_घातer_ctrl(priv, 0);

	pm_runसमय_disable(&pdev->dev);

	usbhs_platक्रमm_call(priv, hardware_निकास, pdev);
	usbhsc_clk_put(priv);
	reset_control_निश्चित(priv->rsts);
	usbhs_mod_हटाओ(priv);
	usbhs_fअगरo_हटाओ(priv);
	usbhs_pipe_हटाओ(priv);

	वापस 0;
पूर्ण

अटल __maybe_unused पूर्णांक usbhsc_suspend(काष्ठा device *dev)
अणु
	काष्ठा usbhs_priv *priv = dev_get_drvdata(dev);
	काष्ठा usbhs_mod *mod = usbhs_mod_get_current(priv);

	अगर (mod) अणु
		usbhs_mod_call(priv, stop, priv);
		usbhs_mod_change(priv, -1);
	पूर्ण

	अगर (mod || !usbhs_get_dparam(priv, runसमय_pwctrl))
		usbhsc_घातer_ctrl(priv, 0);

	वापस 0;
पूर्ण

अटल __maybe_unused पूर्णांक usbhsc_resume(काष्ठा device *dev)
अणु
	काष्ठा usbhs_priv *priv = dev_get_drvdata(dev);
	काष्ठा platक्रमm_device *pdev = usbhs_priv_to_pdev(priv);

	अगर (!usbhs_get_dparam(priv, runसमय_pwctrl)) अणु
		usbhsc_घातer_ctrl(priv, 1);
		usbhs_mod_स्वतःnomy_mode(priv);
	पूर्ण

	usbhs_platक्रमm_call(priv, phy_reset, pdev);

	usbhsc_schedule_notअगरy_hotplug(pdev);

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(usbhsc_pm_ops, usbhsc_suspend, usbhsc_resume);

अटल काष्ठा platक्रमm_driver renesas_usbhs_driver = अणु
	.driver		= अणु
		.name	= "renesas_usbhs",
		.pm	= &usbhsc_pm_ops,
		.of_match_table = of_match_ptr(usbhs_of_match),
	पूर्ण,
	.probe		= usbhs_probe,
	.हटाओ		= usbhs_हटाओ,
पूर्ण;

module_platक्रमm_driver(renesas_usbhs_driver);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Renesas USB driver");
MODULE_AUTHOR("Kuninori Morimoto <kuninori.morimoto.gx@renesas.com>");
