<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Extcon अक्षरger detection driver क्रम Intel Cherrytrail Whiskey Cove PMIC
 * Copyright (C) 2017 Hans de Goede <hdegoede@redhat.com>
 *
 * Based on various non upstream patches to support the CHT Whiskey Cove PMIC:
 * Copyright (C) 2013-2015 Intel Corporation. All rights reserved.
 */

#समावेश <linux/extcon-provider.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mfd/पूर्णांकel_soc_pmic.h>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>

#समावेश "extcon-intel.h"

#घोषणा CHT_WC_PHYCTRL			0x5e07

#घोषणा CHT_WC_CHGRCTRL0		0x5e16
#घोषणा CHT_WC_CHGRCTRL0_CHGRRESET	BIT(0)
#घोषणा CHT_WC_CHGRCTRL0_EMRGCHREN	BIT(1)
#घोषणा CHT_WC_CHGRCTRL0_EXTCHRDIS	BIT(2)
#घोषणा CHT_WC_CHGRCTRL0_SWCONTROL	BIT(3)
#घोषणा CHT_WC_CHGRCTRL0_TTLCK		BIT(4)
#घोषणा CHT_WC_CHGRCTRL0_CCSM_OFF	BIT(5)
#घोषणा CHT_WC_CHGRCTRL0_DBPOFF		BIT(6)
#घोषणा CHT_WC_CHGRCTRL0_CHR_WDT_NOKICK	BIT(7)

#घोषणा CHT_WC_CHGRCTRL1			0x5e17
#घोषणा CHT_WC_CHGRCTRL1_FUSB_INLMT_100		BIT(0)
#घोषणा CHT_WC_CHGRCTRL1_FUSB_INLMT_150		BIT(1)
#घोषणा CHT_WC_CHGRCTRL1_FUSB_INLMT_500		BIT(2)
#घोषणा CHT_WC_CHGRCTRL1_FUSB_INLMT_900		BIT(3)
#घोषणा CHT_WC_CHGRCTRL1_FUSB_INLMT_1500	BIT(4)
#घोषणा CHT_WC_CHGRCTRL1_FTEMP_EVENT		BIT(5)
#घोषणा CHT_WC_CHGRCTRL1_OTGMODE		BIT(6)
#घोषणा CHT_WC_CHGRCTRL1_DBPEN			BIT(7)

#घोषणा CHT_WC_USBSRC			0x5e29
#घोषणा CHT_WC_USBSRC_STS_MASK		GENMASK(1, 0)
#घोषणा CHT_WC_USBSRC_STS_SUCCESS	2
#घोषणा CHT_WC_USBSRC_STS_FAIL		3
#घोषणा CHT_WC_USBSRC_TYPE_SHIFT	2
#घोषणा CHT_WC_USBSRC_TYPE_MASK		GENMASK(5, 2)
#घोषणा CHT_WC_USBSRC_TYPE_NONE		0
#घोषणा CHT_WC_USBSRC_TYPE_SDP		1
#घोषणा CHT_WC_USBSRC_TYPE_DCP		2
#घोषणा CHT_WC_USBSRC_TYPE_CDP		3
#घोषणा CHT_WC_USBSRC_TYPE_ACA		4
#घोषणा CHT_WC_USBSRC_TYPE_SE1		5
#घोषणा CHT_WC_USBSRC_TYPE_MHL		6
#घोषणा CHT_WC_USBSRC_TYPE_FLOATING	7
#घोषणा CHT_WC_USBSRC_TYPE_OTHER	8
#घोषणा CHT_WC_USBSRC_TYPE_DCP_EXTPHY	9

#घोषणा CHT_WC_CHGDISCTRL		0x5e2f
#घोषणा CHT_WC_CHGDISCTRL_OUT		BIT(0)
/* 0 - खोलो drain, 1 - regular push-pull output */
#घोषणा CHT_WC_CHGDISCTRL_DRV		BIT(4)
/* 0 - pin is controlled by SW, 1 - by HW */
#घोषणा CHT_WC_CHGDISCTRL_FN		BIT(6)

#घोषणा CHT_WC_PWRSRC_IRQ		0x6e03
#घोषणा CHT_WC_PWRSRC_IRQ_MASK		0x6e0f
#घोषणा CHT_WC_PWRSRC_STS		0x6e1e
#घोषणा CHT_WC_PWRSRC_VBUS		BIT(0)
#घोषणा CHT_WC_PWRSRC_DC		BIT(1)
#घोषणा CHT_WC_PWRSRC_BATT		BIT(2)
#घोषणा CHT_WC_PWRSRC_USBID_MASK	GENMASK(4, 3)
#घोषणा CHT_WC_PWRSRC_USBID_SHIFT	3
#घोषणा CHT_WC_PWRSRC_RID_ACA		0
#घोषणा CHT_WC_PWRSRC_RID_GND		1
#घोषणा CHT_WC_PWRSRC_RID_FLOAT		2

#घोषणा CHT_WC_VBUS_GPIO_CTLO		0x6e2d
#घोषणा CHT_WC_VBUS_GPIO_CTLO_OUTPUT	BIT(0)
#घोषणा CHT_WC_VBUS_GPIO_CTLO_DRV_OD	BIT(4)
#घोषणा CHT_WC_VBUS_GPIO_CTLO_सूची_OUT	BIT(5)

क्रमागत cht_wc_mux_select अणु
	MUX_SEL_PMIC = 0,
	MUX_SEL_SOC,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक cht_wc_extcon_cables[] = अणु
	EXTCON_USB,
	EXTCON_USB_HOST,
	EXTCON_CHG_USB_SDP,
	EXTCON_CHG_USB_CDP,
	EXTCON_CHG_USB_DCP,
	EXTCON_CHG_USB_ACA,
	EXTCON_NONE,
पूर्ण;

काष्ठा cht_wc_extcon_data अणु
	काष्ठा device *dev;
	काष्ठा regmap *regmap;
	काष्ठा extcon_dev *edev;
	अचिन्हित पूर्णांक previous_cable;
	bool usb_host;
पूर्ण;

अटल पूर्णांक cht_wc_extcon_get_id(काष्ठा cht_wc_extcon_data *ext, पूर्णांक pwrsrc_sts)
अणु
	चयन ((pwrsrc_sts & CHT_WC_PWRSRC_USBID_MASK) >> CHT_WC_PWRSRC_USBID_SHIFT) अणु
	हाल CHT_WC_PWRSRC_RID_GND:
		वापस INTEL_USB_ID_GND;
	हाल CHT_WC_PWRSRC_RID_FLOAT:
		वापस INTEL_USB_ID_FLOAT;
	हाल CHT_WC_PWRSRC_RID_ACA:
	शेष:
		/*
		 * Once we have IIO support क्रम the GPADC we should पढ़ो
		 * the USBID GPADC channel here and determine ACA role
		 * based on that.
		 */
		वापस INTEL_USB_ID_FLOAT;
	पूर्ण
पूर्ण

अटल पूर्णांक cht_wc_extcon_get_अक्षरger(काष्ठा cht_wc_extcon_data *ext,
				     bool ignore_errors)
अणु
	पूर्णांक ret, usbsrc, status;
	अचिन्हित दीर्घ समयout;

	/* Charger detection can take upto 600ms, रुको 800ms max. */
	समयout = jअगरfies + msecs_to_jअगरfies(800);
	करो अणु
		ret = regmap_पढ़ो(ext->regmap, CHT_WC_USBSRC, &usbsrc);
		अगर (ret) अणु
			dev_err(ext->dev, "Error reading usbsrc: %d\n", ret);
			वापस ret;
		पूर्ण

		status = usbsrc & CHT_WC_USBSRC_STS_MASK;
		अगर (status == CHT_WC_USBSRC_STS_SUCCESS ||
		    status == CHT_WC_USBSRC_STS_FAIL)
			अवरोध;

		msleep(50); /* Wait a bit beक्रमe retrying */
	पूर्ण जबतक (समय_beक्रमe(jअगरfies, समयout));

	अगर (status != CHT_WC_USBSRC_STS_SUCCESS) अणु
		अगर (ignore_errors)
			वापस EXTCON_CHG_USB_SDP; /* Save fallback */

		अगर (status == CHT_WC_USBSRC_STS_FAIL)
			dev_warn(ext->dev, "Could not detect charger type\n");
		अन्यथा
			dev_warn(ext->dev, "Timeout detecting charger type\n");
		वापस EXTCON_CHG_USB_SDP; /* Save fallback */
	पूर्ण

	usbsrc = (usbsrc & CHT_WC_USBSRC_TYPE_MASK) >> CHT_WC_USBSRC_TYPE_SHIFT;
	चयन (usbsrc) अणु
	शेष:
		dev_warn(ext->dev,
			"Unhandled charger type %d, defaulting to SDP\n",
			 ret);
		वापस EXTCON_CHG_USB_SDP;
	हाल CHT_WC_USBSRC_TYPE_SDP:
	हाल CHT_WC_USBSRC_TYPE_FLOATING:
	हाल CHT_WC_USBSRC_TYPE_OTHER:
		वापस EXTCON_CHG_USB_SDP;
	हाल CHT_WC_USBSRC_TYPE_CDP:
		वापस EXTCON_CHG_USB_CDP;
	हाल CHT_WC_USBSRC_TYPE_DCP:
	हाल CHT_WC_USBSRC_TYPE_DCP_EXTPHY:
	हाल CHT_WC_USBSRC_TYPE_MHL: /* MHL2+ delivers upto 2A, treat as DCP */
		वापस EXTCON_CHG_USB_DCP;
	हाल CHT_WC_USBSRC_TYPE_ACA:
		वापस EXTCON_CHG_USB_ACA;
	पूर्ण
पूर्ण

अटल व्योम cht_wc_extcon_set_phymux(काष्ठा cht_wc_extcon_data *ext, u8 state)
अणु
	पूर्णांक ret;

	ret = regmap_ग_लिखो(ext->regmap, CHT_WC_PHYCTRL, state);
	अगर (ret)
		dev_err(ext->dev, "Error writing phyctrl: %d\n", ret);
पूर्ण

अटल व्योम cht_wc_extcon_set_5v_boost(काष्ठा cht_wc_extcon_data *ext,
				       bool enable)
अणु
	पूर्णांक ret, val;

	/*
	 * The 5V boost converter is enabled through a gpio on the PMIC, since
	 * there currently is no gpio driver we access the gpio reg directly.
	 */
	val = CHT_WC_VBUS_GPIO_CTLO_DRV_OD | CHT_WC_VBUS_GPIO_CTLO_सूची_OUT;
	अगर (enable)
		val |= CHT_WC_VBUS_GPIO_CTLO_OUTPUT;

	ret = regmap_ग_लिखो(ext->regmap, CHT_WC_VBUS_GPIO_CTLO, val);
	अगर (ret)
		dev_err(ext->dev, "Error writing Vbus GPIO CTLO: %d\n", ret);
पूर्ण

अटल व्योम cht_wc_extcon_set_otgmode(काष्ठा cht_wc_extcon_data *ext,
				      bool enable)
अणु
	अचिन्हित पूर्णांक val = enable ? CHT_WC_CHGRCTRL1_OTGMODE : 0;
	पूर्णांक ret;

	ret = regmap_update_bits(ext->regmap, CHT_WC_CHGRCTRL1,
				 CHT_WC_CHGRCTRL1_OTGMODE, val);
	अगर (ret)
		dev_err(ext->dev, "Error updating CHGRCTRL1 reg: %d\n", ret);
पूर्ण

अटल व्योम cht_wc_extcon_enable_अक्षरging(काष्ठा cht_wc_extcon_data *ext,
					  bool enable)
अणु
	अचिन्हित पूर्णांक val = enable ? 0 : CHT_WC_CHGDISCTRL_OUT;
	पूर्णांक ret;

	ret = regmap_update_bits(ext->regmap, CHT_WC_CHGDISCTRL,
				 CHT_WC_CHGDISCTRL_OUT, val);
	अगर (ret)
		dev_err(ext->dev, "Error updating CHGDISCTRL reg: %d\n", ret);
पूर्ण

/* Small helper to sync EXTCON_CHG_USB_SDP and EXTCON_USB state */
अटल व्योम cht_wc_extcon_set_state(काष्ठा cht_wc_extcon_data *ext,
				    अचिन्हित पूर्णांक cable, bool state)
अणु
	extcon_set_state_sync(ext->edev, cable, state);
	अगर (cable == EXTCON_CHG_USB_SDP)
		extcon_set_state_sync(ext->edev, EXTCON_USB, state);
पूर्ण

अटल व्योम cht_wc_extcon_pwrsrc_event(काष्ठा cht_wc_extcon_data *ext)
अणु
	पूर्णांक ret, pwrsrc_sts, id;
	अचिन्हित पूर्णांक cable = EXTCON_NONE;
	/* Ignore errors in host mode, as the 5v boost converter is on then */
	bool ignore_get_अक्षरger_errors = ext->usb_host;

	ret = regmap_पढ़ो(ext->regmap, CHT_WC_PWRSRC_STS, &pwrsrc_sts);
	अगर (ret) अणु
		dev_err(ext->dev, "Error reading pwrsrc status: %d\n", ret);
		वापस;
	पूर्ण

	id = cht_wc_extcon_get_id(ext, pwrsrc_sts);
	अगर (id == INTEL_USB_ID_GND) अणु
		cht_wc_extcon_enable_अक्षरging(ext, false);
		cht_wc_extcon_set_otgmode(ext, true);

		/* The 5v boost causes a false VBUS / SDP detect, skip */
		जाओ अक्षरger_det_करोne;
	पूर्ण

	cht_wc_extcon_set_otgmode(ext, false);
	cht_wc_extcon_enable_अक्षरging(ext, true);

	/* Plugged पूर्णांकo a host/अक्षरger or not connected? */
	अगर (!(pwrsrc_sts & CHT_WC_PWRSRC_VBUS)) अणु
		/* Route D+ and D- to PMIC क्रम future अक्षरger detection */
		cht_wc_extcon_set_phymux(ext, MUX_SEL_PMIC);
		जाओ set_state;
	पूर्ण

	ret = cht_wc_extcon_get_अक्षरger(ext, ignore_get_अक्षरger_errors);
	अगर (ret >= 0)
		cable = ret;

अक्षरger_det_करोne:
	/* Route D+ and D- to SoC क्रम the host or gadget controller */
	cht_wc_extcon_set_phymux(ext, MUX_SEL_SOC);

set_state:
	अगर (cable != ext->previous_cable) अणु
		cht_wc_extcon_set_state(ext, cable, true);
		cht_wc_extcon_set_state(ext, ext->previous_cable, false);
		ext->previous_cable = cable;
	पूर्ण

	ext->usb_host = ((id == INTEL_USB_ID_GND) || (id == INTEL_USB_RID_A));
	extcon_set_state_sync(ext->edev, EXTCON_USB_HOST, ext->usb_host);
पूर्ण

अटल irqवापस_t cht_wc_extcon_isr(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा cht_wc_extcon_data *ext = data;
	पूर्णांक ret, irqs;

	ret = regmap_पढ़ो(ext->regmap, CHT_WC_PWRSRC_IRQ, &irqs);
	अगर (ret) अणु
		dev_err(ext->dev, "Error reading irqs: %d\n", ret);
		वापस IRQ_NONE;
	पूर्ण

	cht_wc_extcon_pwrsrc_event(ext);

	ret = regmap_ग_लिखो(ext->regmap, CHT_WC_PWRSRC_IRQ, irqs);
	अगर (ret) अणु
		dev_err(ext->dev, "Error writing irqs: %d\n", ret);
		वापस IRQ_NONE;
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक cht_wc_extcon_sw_control(काष्ठा cht_wc_extcon_data *ext, bool enable)
अणु
	पूर्णांक ret, mask, val;

	val = enable ? 0 : CHT_WC_CHGDISCTRL_FN;
	ret = regmap_update_bits(ext->regmap, CHT_WC_CHGDISCTRL,
				 CHT_WC_CHGDISCTRL_FN, val);
	अगर (ret)
		dev_err(ext->dev,
			"Error setting sw control for CHGDIS pin: %d\n",
			ret);

	mask = CHT_WC_CHGRCTRL0_SWCONTROL | CHT_WC_CHGRCTRL0_CCSM_OFF;
	val = enable ? mask : 0;
	ret = regmap_update_bits(ext->regmap, CHT_WC_CHGRCTRL0, mask, val);
	अगर (ret)
		dev_err(ext->dev, "Error setting sw control: %d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक cht_wc_extcon_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा पूर्णांकel_soc_pmic *pmic = dev_get_drvdata(pdev->dev.parent);
	काष्ठा cht_wc_extcon_data *ext;
	अचिन्हित दीर्घ mask = ~(CHT_WC_PWRSRC_VBUS | CHT_WC_PWRSRC_USBID_MASK);
	पूर्णांक pwrsrc_sts, id;
	पूर्णांक irq, ret;

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	ext = devm_kzalloc(&pdev->dev, माप(*ext), GFP_KERNEL);
	अगर (!ext)
		वापस -ENOMEM;

	ext->dev = &pdev->dev;
	ext->regmap = pmic->regmap;
	ext->previous_cable = EXTCON_NONE;

	/* Initialize extcon device */
	ext->edev = devm_extcon_dev_allocate(ext->dev, cht_wc_extcon_cables);
	अगर (IS_ERR(ext->edev))
		वापस PTR_ERR(ext->edev);

	/*
	 * When a host-cable is detected the BIOS enables an बाह्यal 5v boost
	 * converter to घातer connected devices there are 2 problems with this:
	 * 1) This माला_लो seen by the बाह्यal battery अक्षरger as a valid Vbus
	 *    supply and it then tries to feed Vsys from this creating a
	 *    feedback loop which causes aprox. 300 mA extra battery drain
	 *    (and unless we drive the बाह्यal-अक्षरger-disable pin high it
	 *    also tries to अक्षरge the battery causing even more feedback).
	 * 2) This माला_लो seen by the pwrsrc block as a SDP USB Vbus supply
	 * Since the बाह्यal battery अक्षरger has its own 5v boost converter
	 * which करोes not have these issues, we simply turn the separate
	 * बाह्यal 5v boost converter off and leave it off entirely.
	 */
	cht_wc_extcon_set_5v_boost(ext, false);

	/* Enable sw control */
	ret = cht_wc_extcon_sw_control(ext, true);
	अगर (ret)
		जाओ disable_sw_control;

	/* Disable अक्षरging by बाह्यal battery अक्षरger */
	cht_wc_extcon_enable_अक्षरging(ext, false);

	/* Register extcon device */
	ret = devm_extcon_dev_रेजिस्टर(ext->dev, ext->edev);
	अगर (ret) अणु
		dev_err(ext->dev, "Error registering extcon device: %d\n", ret);
		जाओ disable_sw_control;
	पूर्ण

	ret = regmap_पढ़ो(ext->regmap, CHT_WC_PWRSRC_STS, &pwrsrc_sts);
	अगर (ret) अणु
		dev_err(ext->dev, "Error reading pwrsrc status: %d\n", ret);
		जाओ disable_sw_control;
	पूर्ण

	/*
	 * If no USB host or device connected, route D+ and D- to PMIC क्रम
	 * initial अक्षरger detection
	 */
	id = cht_wc_extcon_get_id(ext, pwrsrc_sts);
	अगर (id != INTEL_USB_ID_GND)
		cht_wc_extcon_set_phymux(ext, MUX_SEL_PMIC);

	/* Get initial state */
	cht_wc_extcon_pwrsrc_event(ext);

	ret = devm_request_thपढ़ोed_irq(ext->dev, irq, शून्य, cht_wc_extcon_isr,
					IRQF_ONESHOT, pdev->name, ext);
	अगर (ret) अणु
		dev_err(ext->dev, "Error requesting interrupt: %d\n", ret);
		जाओ disable_sw_control;
	पूर्ण

	/* Unmask irqs */
	ret = regmap_ग_लिखो(ext->regmap, CHT_WC_PWRSRC_IRQ_MASK, mask);
	अगर (ret) अणु
		dev_err(ext->dev, "Error writing irq-mask: %d\n", ret);
		जाओ disable_sw_control;
	पूर्ण

	platक्रमm_set_drvdata(pdev, ext);

	वापस 0;

disable_sw_control:
	cht_wc_extcon_sw_control(ext, false);
	वापस ret;
पूर्ण

अटल पूर्णांक cht_wc_extcon_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा cht_wc_extcon_data *ext = platक्रमm_get_drvdata(pdev);

	cht_wc_extcon_sw_control(ext, false);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_id cht_wc_extcon_table[] = अणु
	अणु .name = "cht_wcove_pwrsrc" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, cht_wc_extcon_table);

अटल काष्ठा platक्रमm_driver cht_wc_extcon_driver = अणु
	.probe = cht_wc_extcon_probe,
	.हटाओ = cht_wc_extcon_हटाओ,
	.id_table = cht_wc_extcon_table,
	.driver = अणु
		.name = "cht_wcove_pwrsrc",
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(cht_wc_extcon_driver);

MODULE_DESCRIPTION("Intel Cherrytrail Whiskey Cove PMIC extcon driver");
MODULE_AUTHOR("Hans de Goede <hdegoede@redhat.com>");
MODULE_LICENSE("GPL v2");
