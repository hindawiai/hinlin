<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * extcon driver क्रम Basin Cove PMIC
 *
 * Copyright (c) 2019, Intel Corporation.
 * Author: Andy Shevchenko <andriy.shevchenko@linux.पूर्णांकel.com>
 */

#समावेश <linux/extcon-provider.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mfd/पूर्णांकel_soc_pmic.h>
#समावेश <linux/mfd/पूर्णांकel_soc_pmic_mrfld.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>

#समावेश "extcon-intel.h"

#घोषणा BCOVE_USBIDCTRL			0x19
#घोषणा BCOVE_USBIDCTRL_ID		BIT(0)
#घोषणा BCOVE_USBIDCTRL_ACA		BIT(1)
#घोषणा BCOVE_USBIDCTRL_ALL	(BCOVE_USBIDCTRL_ID | BCOVE_USBIDCTRL_ACA)

#घोषणा BCOVE_USBIDSTS			0x1a
#घोषणा BCOVE_USBIDSTS_GND		BIT(0)
#घोषणा BCOVE_USBIDSTS_RARBRC_MASK	GENMASK(2, 1)
#घोषणा BCOVE_USBIDSTS_RARBRC_SHIFT	1
#घोषणा BCOVE_USBIDSTS_NO_ACA		0
#घोषणा BCOVE_USBIDSTS_R_ID_A		1
#घोषणा BCOVE_USBIDSTS_R_ID_B		2
#घोषणा BCOVE_USBIDSTS_R_ID_C		3
#घोषणा BCOVE_USBIDSTS_FLOAT		BIT(3)
#घोषणा BCOVE_USBIDSTS_SHORT		BIT(4)

#घोषणा BCOVE_CHGRIRQ_ALL	(BCOVE_CHGRIRQ_VBUSDET | BCOVE_CHGRIRQ_DCDET | \
				 BCOVE_CHGRIRQ_BATTDET | BCOVE_CHGRIRQ_USBIDDET)

#घोषणा BCOVE_CHGRCTRL0			0x4b
#घोषणा BCOVE_CHGRCTRL0_CHGRRESET	BIT(0)
#घोषणा BCOVE_CHGRCTRL0_EMRGCHREN	BIT(1)
#घोषणा BCOVE_CHGRCTRL0_EXTCHRDIS	BIT(2)
#घोषणा BCOVE_CHGRCTRL0_SWCONTROL	BIT(3)
#घोषणा BCOVE_CHGRCTRL0_TTLCK		BIT(4)
#घोषणा BCOVE_CHGRCTRL0_BIT_5		BIT(5)
#घोषणा BCOVE_CHGRCTRL0_BIT_6		BIT(6)
#घोषणा BCOVE_CHGRCTRL0_CHR_WDT_NOKICK	BIT(7)

काष्ठा mrfld_extcon_data अणु
	काष्ठा device *dev;
	काष्ठा regmap *regmap;
	काष्ठा extcon_dev *edev;
	अचिन्हित पूर्णांक status;
	अचिन्हित पूर्णांक id;
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक mrfld_extcon_cable[] = अणु
	EXTCON_USB,
	EXTCON_USB_HOST,
	EXTCON_CHG_USB_SDP,
	EXTCON_CHG_USB_CDP,
	EXTCON_CHG_USB_DCP,
	EXTCON_CHG_USB_ACA,
	EXTCON_NONE,
पूर्ण;

अटल पूर्णांक mrfld_extcon_clear(काष्ठा mrfld_extcon_data *data, अचिन्हित पूर्णांक reg,
			      अचिन्हित पूर्णांक mask)
अणु
	वापस regmap_update_bits(data->regmap, reg, mask, 0x00);
पूर्ण

अटल पूर्णांक mrfld_extcon_set(काष्ठा mrfld_extcon_data *data, अचिन्हित पूर्णांक reg,
			    अचिन्हित पूर्णांक mask)
अणु
	वापस regmap_update_bits(data->regmap, reg, mask, 0xff);
पूर्ण

अटल पूर्णांक mrfld_extcon_sw_control(काष्ठा mrfld_extcon_data *data, bool enable)
अणु
	अचिन्हित पूर्णांक mask = BCOVE_CHGRCTRL0_SWCONTROL;
	काष्ठा device *dev = data->dev;
	पूर्णांक ret;

	अगर (enable)
		ret = mrfld_extcon_set(data, BCOVE_CHGRCTRL0, mask);
	अन्यथा
		ret = mrfld_extcon_clear(data, BCOVE_CHGRCTRL0, mask);
	अगर (ret)
		dev_err(dev, "can't set SW control: %d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक mrfld_extcon_get_id(काष्ठा mrfld_extcon_data *data)
अणु
	काष्ठा regmap *regmap = data->regmap;
	अचिन्हित पूर्णांक id;
	bool ground;
	पूर्णांक ret;

	ret = regmap_पढ़ो(regmap, BCOVE_USBIDSTS, &id);
	अगर (ret)
		वापस ret;

	अगर (id & BCOVE_USBIDSTS_FLOAT)
		वापस INTEL_USB_ID_FLOAT;

	चयन ((id & BCOVE_USBIDSTS_RARBRC_MASK) >> BCOVE_USBIDSTS_RARBRC_SHIFT) अणु
	हाल BCOVE_USBIDSTS_R_ID_A:
		वापस INTEL_USB_RID_A;
	हाल BCOVE_USBIDSTS_R_ID_B:
		वापस INTEL_USB_RID_B;
	हाल BCOVE_USBIDSTS_R_ID_C:
		वापस INTEL_USB_RID_C;
	पूर्ण

	/*
	 * PMIC A0 reports USBIDSTS_GND = 1 क्रम ID_GND,
	 * but PMIC B0 reports USBIDSTS_GND = 0 क्रम ID_GND.
	 * Thus we must check this bit at last.
	 */
	ground = id & BCOVE_USBIDSTS_GND;
	चयन ('A' + BCOVE_MAJOR(data->id)) अणु
	हाल 'A':
		वापस ground ? INTEL_USB_ID_GND : INTEL_USB_ID_FLOAT;
	हाल 'B':
		वापस ground ? INTEL_USB_ID_FLOAT : INTEL_USB_ID_GND;
	पूर्ण

	/* Unknown or unsupported type */
	वापस INTEL_USB_ID_FLOAT;
पूर्ण

अटल पूर्णांक mrfld_extcon_role_detect(काष्ठा mrfld_extcon_data *data)
अणु
	अचिन्हित पूर्णांक id;
	bool usb_host;
	पूर्णांक ret;

	ret = mrfld_extcon_get_id(data);
	अगर (ret < 0)
		वापस ret;

	id = ret;

	usb_host = (id == INTEL_USB_ID_GND) || (id == INTEL_USB_RID_A);
	extcon_set_state_sync(data->edev, EXTCON_USB_HOST, usb_host);

	वापस 0;
पूर्ण

अटल पूर्णांक mrfld_extcon_cable_detect(काष्ठा mrfld_extcon_data *data)
अणु
	काष्ठा regmap *regmap = data->regmap;
	अचिन्हित पूर्णांक status, change;
	पूर्णांक ret;

	/*
	 * It seems SCU firmware clears the content of BCOVE_CHGRIRQ1
	 * and makes it useless क्रम OS. Instead we compare a previously
	 * stored status to the current one, provided by BCOVE_SCHGRIRQ1.
	 */
	ret = regmap_पढ़ो(regmap, BCOVE_SCHGRIRQ1, &status);
	अगर (ret)
		वापस ret;

	change = status ^ data->status;
	अगर (!change)
		वापस -ENODATA;

	अगर (change & BCOVE_CHGRIRQ_USBIDDET) अणु
		ret = mrfld_extcon_role_detect(data);
		अगर (ret)
			वापस ret;
	पूर्ण

	data->status = status;

	वापस 0;
पूर्ण

अटल irqवापस_t mrfld_extcon_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा mrfld_extcon_data *data = dev_id;
	पूर्णांक ret;

	ret = mrfld_extcon_cable_detect(data);

	mrfld_extcon_clear(data, BCOVE_MIRQLVL1, BCOVE_LVL1_CHGR);

	वापस ret ? IRQ_NONE: IRQ_HANDLED;
पूर्ण

अटल पूर्णांक mrfld_extcon_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा पूर्णांकel_soc_pmic *pmic = dev_get_drvdata(dev->parent);
	काष्ठा regmap *regmap = pmic->regmap;
	काष्ठा mrfld_extcon_data *data;
	अचिन्हित पूर्णांक id;
	पूर्णांक irq, ret;

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	data = devm_kzalloc(dev, माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->dev = dev;
	data->regmap = regmap;

	data->edev = devm_extcon_dev_allocate(dev, mrfld_extcon_cable);
	अगर (IS_ERR(data->edev))
		वापस -ENOMEM;

	ret = devm_extcon_dev_रेजिस्टर(dev, data->edev);
	अगर (ret < 0) अणु
		dev_err(dev, "can't register extcon device: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = devm_request_thपढ़ोed_irq(dev, irq, शून्य, mrfld_extcon_पूर्णांकerrupt,
					IRQF_ONESHOT | IRQF_SHARED, pdev->name,
					data);
	अगर (ret) अणु
		dev_err(dev, "can't register IRQ handler: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = regmap_पढ़ो(regmap, BCOVE_ID, &id);
	अगर (ret) अणु
		dev_err(dev, "can't read PMIC ID: %d\n", ret);
		वापस ret;
	पूर्ण

	data->id = id;

	ret = mrfld_extcon_sw_control(data, true);
	अगर (ret)
		वापस ret;

	/* Get initial state */
	mrfld_extcon_role_detect(data);

	mrfld_extcon_clear(data, BCOVE_MIRQLVL1, BCOVE_LVL1_CHGR);
	mrfld_extcon_clear(data, BCOVE_MCHGRIRQ1, BCOVE_CHGRIRQ_ALL);

	mrfld_extcon_set(data, BCOVE_USBIDCTRL, BCOVE_USBIDCTRL_ALL);

	platक्रमm_set_drvdata(pdev, data);

	वापस 0;
पूर्ण

अटल पूर्णांक mrfld_extcon_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mrfld_extcon_data *data = platक्रमm_get_drvdata(pdev);

	mrfld_extcon_sw_control(data, false);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_id mrfld_extcon_id_table[] = अणु
	अणु .name = "mrfld_bcove_pwrsrc" पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, mrfld_extcon_id_table);

अटल काष्ठा platक्रमm_driver mrfld_extcon_driver = अणु
	.driver = अणु
		.name	= "mrfld_bcove_pwrsrc",
	पूर्ण,
	.probe		= mrfld_extcon_probe,
	.हटाओ		= mrfld_extcon_हटाओ,
	.id_table	= mrfld_extcon_id_table,
पूर्ण;
module_platक्रमm_driver(mrfld_extcon_driver);

MODULE_AUTHOR("Andy Shevchenko <andriy.shevchenko@linux.intel.com>");
MODULE_DESCRIPTION("extcon driver for Intel Merrifield Basin Cove PMIC");
MODULE_LICENSE("GPL v2");
