<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * extcon-axp288.c - X-Power AXP288 PMIC extcon cable detection driver
 *
 * Copyright (c) 2017-2018 Hans de Goede <hdegoede@redhat.com>
 * Copyright (C) 2015 Intel Corporation
 * Author: Ramakrishna Pallala <ramakrishna.pallala@पूर्णांकel.com>
 */

#समावेश <linux/acpi.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/पन.स>
#समावेश <linux/slab.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/property.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/extcon-provider.h>
#समावेश <linux/regmap.h>
#समावेश <linux/mfd/axp20x.h>
#समावेश <linux/usb/role.h>
#समावेश <linux/workqueue.h>

#समावेश <यंत्र/cpu_device_id.h>
#समावेश <यंत्र/पूर्णांकel-family.h>

/* Power source status रेजिस्टर */
#घोषणा PS_STAT_VBUS_TRIGGER		BIT(0)
#घोषणा PS_STAT_BAT_CHRG_सूची		BIT(2)
#घोषणा PS_STAT_VBUS_ABOVE_VHOLD	BIT(3)
#घोषणा PS_STAT_VBUS_VALID		BIT(4)
#घोषणा PS_STAT_VBUS_PRESENT		BIT(5)

/* BC module global रेजिस्टर */
#घोषणा BC_GLOBAL_RUN			BIT(0)
#घोषणा BC_GLOBAL_DET_STAT		BIT(2)
#घोषणा BC_GLOBAL_DBP_TOUT		BIT(3)
#घोषणा BC_GLOBAL_VLGC_COM_SEL		BIT(4)
#घोषणा BC_GLOBAL_DCD_TOUT_MASK		(BIT(6)|BIT(5))
#घोषणा BC_GLOBAL_DCD_TOUT_300MS	0
#घोषणा BC_GLOBAL_DCD_TOUT_100MS	1
#घोषणा BC_GLOBAL_DCD_TOUT_500MS	2
#घोषणा BC_GLOBAL_DCD_TOUT_900MS	3
#घोषणा BC_GLOBAL_DCD_DET_SEL		BIT(7)

/* BC module vbus control and status रेजिस्टर */
#घोषणा VBUS_CNTL_DPDM_PD_EN		BIT(4)
#घोषणा VBUS_CNTL_DPDM_FD_EN		BIT(5)
#घोषणा VBUS_CNTL_FIRST_PO_STAT		BIT(6)

/* BC USB status रेजिस्टर */
#घोषणा USB_STAT_BUS_STAT_MASK		(BIT(3)|BIT(2)|BIT(1)|BIT(0))
#घोषणा USB_STAT_BUS_STAT_SHIFT		0
#घोषणा USB_STAT_BUS_STAT_ATHD		0
#घोषणा USB_STAT_BUS_STAT_CONN		1
#घोषणा USB_STAT_BUS_STAT_SUSP		2
#घोषणा USB_STAT_BUS_STAT_CONF		3
#घोषणा USB_STAT_USB_SS_MODE		BIT(4)
#घोषणा USB_STAT_DEAD_BAT_DET		BIT(6)
#घोषणा USB_STAT_DBP_UNCFG		BIT(7)

/* BC detect status रेजिस्टर */
#घोषणा DET_STAT_MASK			(BIT(7)|BIT(6)|BIT(5))
#घोषणा DET_STAT_SHIFT			5
#घोषणा DET_STAT_SDP			1
#घोषणा DET_STAT_CDP			2
#घोषणा DET_STAT_DCP			3

क्रमागत axp288_extcon_reg अणु
	AXP288_PS_STAT_REG		= 0x00,
	AXP288_PS_BOOT_REASON_REG	= 0x02,
	AXP288_BC_GLOBAL_REG		= 0x2c,
	AXP288_BC_VBUS_CNTL_REG		= 0x2d,
	AXP288_BC_USB_STAT_REG		= 0x2e,
	AXP288_BC_DET_STAT_REG		= 0x2f,
पूर्ण;

क्रमागत axp288_extcon_irq अणु
	VBUS_FALLING_IRQ = 0,
	VBUS_RISING_IRQ,
	MV_CHNG_IRQ,
	BC_USB_CHNG_IRQ,
	EXTCON_IRQ_END,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक axp288_extcon_cables[] = अणु
	EXTCON_CHG_USB_SDP,
	EXTCON_CHG_USB_CDP,
	EXTCON_CHG_USB_DCP,
	EXTCON_USB,
	EXTCON_NONE,
पूर्ण;

काष्ठा axp288_extcon_info अणु
	काष्ठा device *dev;
	काष्ठा regmap *regmap;
	काष्ठा regmap_irq_chip_data *regmap_irqc;
	काष्ठा usb_role_चयन *role_sw;
	काष्ठा work_काष्ठा role_work;
	पूर्णांक irq[EXTCON_IRQ_END];
	काष्ठा extcon_dev *edev;
	काष्ठा extcon_dev *id_extcon;
	काष्ठा notअगरier_block id_nb;
	अचिन्हित पूर्णांक previous_cable;
	bool vbus_attach;
पूर्ण;

अटल स्थिर काष्ठा x86_cpu_id cherry_trail_cpu_ids[] = अणु
	X86_MATCH_INTEL_FAM6_MODEL(ATOM_AIRMONT,	शून्य),
	अणुपूर्ण
पूर्ण;

/* Power up/करोwn reason string array */
अटल स्थिर अक्षर * स्थिर axp288_pwr_up_करोwn_info[] = अणु
	"Last wake caused by user pressing the power button",
	"Last wake caused by a charger insertion",
	"Last wake caused by a battery insertion",
	"Last wake caused by SOC initiated global reset",
	"Last wake caused by cold reset",
	"Last shutdown caused by PMIC UVLO threshold",
	"Last shutdown caused by SOC initiated cold off",
	"Last shutdown caused by user pressing the power button",
पूर्ण;

/*
 * Decode and log the given "reset source indicator" (rsi)
 * रेजिस्टर and then clear it.
 */
अटल व्योम axp288_extcon_log_rsi(काष्ठा axp288_extcon_info *info)
अणु
	अचिन्हित पूर्णांक val, i, clear_mask = 0;
	अचिन्हित दीर्घ bits;
	पूर्णांक ret;

	ret = regmap_पढ़ो(info->regmap, AXP288_PS_BOOT_REASON_REG, &val);
	अगर (ret < 0) अणु
		dev_err(info->dev, "failed to read reset source indicator\n");
		वापस;
	पूर्ण

	bits = val & GENMASK(ARRAY_SIZE(axp288_pwr_up_करोwn_info) - 1, 0);
	क्रम_each_set_bit(i, &bits, ARRAY_SIZE(axp288_pwr_up_करोwn_info))
		dev_dbg(info->dev, "%s\n", axp288_pwr_up_करोwn_info[i]);
	clear_mask = bits;

	/* Clear the रेजिस्टर value क्रम next reboot (ग_लिखो 1 to clear bit) */
	regmap_ग_लिखो(info->regmap, AXP288_PS_BOOT_REASON_REG, clear_mask);
पूर्ण

/*
 * The below code to control the USB role-चयन on devices with an AXP288
 * may seem out of place, but there are 2 reasons why this is the best place
 * to control the USB role-चयन on such devices:
 * 1) On many devices the USB role is controlled by AML code, but the AML code
 *    only चयनes between the host and none roles, because of Winकरोws not
 *    really using device mode. To make device mode work we need to toggle
 *    between the none/device roles based on Vbus presence, and this driver
 *    माला_लो पूर्णांकerrupts on Vbus insertion / removal.
 * 2) In order क्रम our BC1.2 अक्षरger detection to work properly the role
 *    mux must be properly set to device mode beक्रमe we करो the detection.
 */

/* Returns the id-pin value, note pulled low / false == host-mode */
अटल bool axp288_get_id_pin(काष्ठा axp288_extcon_info *info)
अणु
	क्रमागत usb_role role;

	अगर (info->id_extcon)
		वापस extcon_get_state(info->id_extcon, EXTCON_USB_HOST) <= 0;

	/* We cannot access the id-pin, see what mode the AML code has set */
	role = usb_role_चयन_get_role(info->role_sw);
	वापस role != USB_ROLE_HOST;
पूर्ण

अटल व्योम axp288_usb_role_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा axp288_extcon_info *info =
		container_of(work, काष्ठा axp288_extcon_info, role_work);
	क्रमागत usb_role role;
	bool id_pin;
	पूर्णांक ret;

	id_pin = axp288_get_id_pin(info);
	अगर (!id_pin)
		role = USB_ROLE_HOST;
	अन्यथा अगर (info->vbus_attach)
		role = USB_ROLE_DEVICE;
	अन्यथा
		role = USB_ROLE_NONE;

	ret = usb_role_चयन_set_role(info->role_sw, role);
	अगर (ret)
		dev_err(info->dev, "failed to set role: %d\n", ret);
पूर्ण

अटल bool axp288_get_vbus_attach(काष्ठा axp288_extcon_info *info)
अणु
	पूर्णांक ret, pwr_stat;

	ret = regmap_पढ़ो(info->regmap, AXP288_PS_STAT_REG, &pwr_stat);
	अगर (ret < 0) अणु
		dev_err(info->dev, "failed to read vbus status\n");
		वापस false;
	पूर्ण

	वापस !!(pwr_stat & PS_STAT_VBUS_VALID);
पूर्ण

अटल पूर्णांक axp288_handle_chrg_det_event(काष्ठा axp288_extcon_info *info)
अणु
	पूर्णांक ret, stat, cfg;
	u8 chrg_type;
	अचिन्हित पूर्णांक cable = info->previous_cable;
	bool vbus_attach = false;

	vbus_attach = axp288_get_vbus_attach(info);
	अगर (!vbus_attach)
		जाओ no_vbus;

	/* Check अक्षरger detection completion status */
	ret = regmap_पढ़ो(info->regmap, AXP288_BC_GLOBAL_REG, &cfg);
	अगर (ret < 0)
		जाओ dev_det_ret;
	अगर (cfg & BC_GLOBAL_DET_STAT) अणु
		dev_dbg(info->dev, "can't complete the charger detection\n");
		जाओ dev_det_ret;
	पूर्ण

	ret = regmap_पढ़ो(info->regmap, AXP288_BC_DET_STAT_REG, &stat);
	अगर (ret < 0)
		जाओ dev_det_ret;

	chrg_type = (stat & DET_STAT_MASK) >> DET_STAT_SHIFT;

	चयन (chrg_type) अणु
	हाल DET_STAT_SDP:
		dev_dbg(info->dev, "sdp cable is connected\n");
		cable = EXTCON_CHG_USB_SDP;
		अवरोध;
	हाल DET_STAT_CDP:
		dev_dbg(info->dev, "cdp cable is connected\n");
		cable = EXTCON_CHG_USB_CDP;
		अवरोध;
	हाल DET_STAT_DCP:
		dev_dbg(info->dev, "dcp cable is connected\n");
		cable = EXTCON_CHG_USB_DCP;
		अवरोध;
	शेष:
		dev_warn(info->dev, "unknown (reserved) bc detect result\n");
		cable = EXTCON_CHG_USB_SDP;
	पूर्ण

no_vbus:
	extcon_set_state_sync(info->edev, info->previous_cable, false);
	अगर (info->previous_cable == EXTCON_CHG_USB_SDP)
		extcon_set_state_sync(info->edev, EXTCON_USB, false);

	अगर (vbus_attach) अणु
		extcon_set_state_sync(info->edev, cable, vbus_attach);
		अगर (cable == EXTCON_CHG_USB_SDP)
			extcon_set_state_sync(info->edev, EXTCON_USB,
						vbus_attach);

		info->previous_cable = cable;
	पूर्ण

	अगर (info->role_sw && info->vbus_attach != vbus_attach) अणु
		info->vbus_attach = vbus_attach;
		/* Setting the role can take a जबतक */
		queue_work(प्रणाली_दीर्घ_wq, &info->role_work);
	पूर्ण

	वापस 0;

dev_det_ret:
	अगर (ret < 0)
		dev_err(info->dev, "failed to detect BC Mod\n");

	वापस ret;
पूर्ण

अटल पूर्णांक axp288_extcon_id_evt(काष्ठा notअगरier_block *nb,
				अचिन्हित दीर्घ event, व्योम *param)
अणु
	काष्ठा axp288_extcon_info *info =
		container_of(nb, काष्ठा axp288_extcon_info, id_nb);

	/* We may not sleep and setting the role can take a जबतक */
	queue_work(प्रणाली_दीर्घ_wq, &info->role_work);

	वापस NOTIFY_OK;
पूर्ण

अटल irqवापस_t axp288_extcon_isr(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा axp288_extcon_info *info = data;
	पूर्णांक ret;

	ret = axp288_handle_chrg_det_event(info);
	अगर (ret < 0)
		dev_err(info->dev, "failed to handle the interrupt\n");

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम axp288_extcon_enable(काष्ठा axp288_extcon_info *info)
अणु
	regmap_update_bits(info->regmap, AXP288_BC_GLOBAL_REG,
						BC_GLOBAL_RUN, 0);
	/* Enable the अक्षरger detection logic */
	regmap_update_bits(info->regmap, AXP288_BC_GLOBAL_REG,
					BC_GLOBAL_RUN, BC_GLOBAL_RUN);
पूर्ण

अटल व्योम axp288_put_role_sw(व्योम *data)
अणु
	काष्ठा axp288_extcon_info *info = data;

	cancel_work_sync(&info->role_work);
	usb_role_चयन_put(info->role_sw);
पूर्ण

अटल पूर्णांक axp288_extcon_find_role_sw(काष्ठा axp288_extcon_info *info)
अणु
	स्थिर काष्ठा software_node *swnode;
	काष्ठा fwnode_handle *fwnode;

	अगर (!x86_match_cpu(cherry_trail_cpu_ids))
		वापस 0;

	swnode = software_node_find_by_name(शून्य, "intel-xhci-usb-sw");
	अगर (!swnode)
		वापस -EPROBE_DEFER;

	fwnode = software_node_fwnode(swnode);
	info->role_sw = usb_role_चयन_find_by_fwnode(fwnode);
	fwnode_handle_put(fwnode);

	वापस info->role_sw ? 0 : -EPROBE_DEFER;
पूर्ण

अटल पूर्णांक axp288_extcon_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा axp288_extcon_info *info;
	काष्ठा axp20x_dev *axp20x = dev_get_drvdata(pdev->dev.parent);
	काष्ठा device *dev = &pdev->dev;
	काष्ठा acpi_device *adev;
	पूर्णांक ret, i, pirq;

	info = devm_kzalloc(&pdev->dev, माप(*info), GFP_KERNEL);
	अगर (!info)
		वापस -ENOMEM;

	info->dev = &pdev->dev;
	info->regmap = axp20x->regmap;
	info->regmap_irqc = axp20x->regmap_irqc;
	info->previous_cable = EXTCON_NONE;
	INIT_WORK(&info->role_work, axp288_usb_role_work);
	info->id_nb.notअगरier_call = axp288_extcon_id_evt;

	platक्रमm_set_drvdata(pdev, info);

	ret = axp288_extcon_find_role_sw(info);
	अगर (ret)
		वापस ret;

	अगर (info->role_sw) अणु
		ret = devm_add_action_or_reset(dev, axp288_put_role_sw, info);
		अगर (ret)
			वापस ret;

		adev = acpi_dev_get_first_match_dev("INT3496", शून्य, -1);
		अगर (adev) अणु
			info->id_extcon = extcon_get_extcon_dev(acpi_dev_name(adev));
			put_device(&adev->dev);
			अगर (!info->id_extcon)
				वापस -EPROBE_DEFER;

			dev_info(dev, "controlling USB role\n");
		पूर्ण अन्यथा अणु
			dev_info(dev, "controlling USB role based on Vbus presence\n");
		पूर्ण
	पूर्ण

	info->vbus_attach = axp288_get_vbus_attach(info);

	axp288_extcon_log_rsi(info);

	/* Initialize extcon device */
	info->edev = devm_extcon_dev_allocate(&pdev->dev,
					      axp288_extcon_cables);
	अगर (IS_ERR(info->edev)) अणु
		dev_err(&pdev->dev, "failed to allocate memory for extcon\n");
		वापस PTR_ERR(info->edev);
	पूर्ण

	/* Register extcon device */
	ret = devm_extcon_dev_रेजिस्टर(&pdev->dev, info->edev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to register extcon device\n");
		वापस ret;
	पूर्ण

	क्रम (i = 0; i < EXTCON_IRQ_END; i++) अणु
		pirq = platक्रमm_get_irq(pdev, i);
		अगर (pirq < 0)
			वापस pirq;

		info->irq[i] = regmap_irq_get_virq(info->regmap_irqc, pirq);
		अगर (info->irq[i] < 0) अणु
			dev_err(&pdev->dev,
				"failed to get virtual interrupt=%d\n", pirq);
			ret = info->irq[i];
			वापस ret;
		पूर्ण

		ret = devm_request_thपढ़ोed_irq(&pdev->dev, info->irq[i],
				शून्य, axp288_extcon_isr,
				IRQF_ONESHOT | IRQF_NO_SUSPEND,
				pdev->name, info);
		अगर (ret) अणु
			dev_err(&pdev->dev, "failed to request interrupt=%d\n",
							info->irq[i]);
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (info->id_extcon) अणु
		ret = devm_extcon_रेजिस्टर_notअगरier_all(dev, info->id_extcon,
							&info->id_nb);
		अगर (ret)
			वापस ret;
	पूर्ण

	/* Make sure the role-sw is set correctly beक्रमe करोing BC detection */
	अगर (info->role_sw) अणु
		queue_work(प्रणाली_दीर्घ_wq, &info->role_work);
		flush_work(&info->role_work);
	पूर्ण

	/* Start अक्षरger cable type detection */
	axp288_extcon_enable(info);

	device_init_wakeup(dev, true);
	platक्रमm_set_drvdata(pdev, info);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused axp288_extcon_suspend(काष्ठा device *dev)
अणु
	काष्ठा axp288_extcon_info *info = dev_get_drvdata(dev);

	अगर (device_may_wakeup(dev))
		enable_irq_wake(info->irq[VBUS_RISING_IRQ]);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused axp288_extcon_resume(काष्ठा device *dev)
अणु
	काष्ठा axp288_extcon_info *info = dev_get_drvdata(dev);

	/*
	 * Wakeup when a अक्षरger is connected to करो अक्षरger-type
	 * connection and generate an extcon event which makes the
	 * axp288 अक्षरger driver set the input current limit.
	 */
	अगर (device_may_wakeup(dev))
		disable_irq_wake(info->irq[VBUS_RISING_IRQ]);

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(axp288_extcon_pm_ops, axp288_extcon_suspend,
			 axp288_extcon_resume);

अटल स्थिर काष्ठा platक्रमm_device_id axp288_extcon_table[] = अणु
	अणु .name = "axp288_extcon" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, axp288_extcon_table);

अटल काष्ठा platक्रमm_driver axp288_extcon_driver = अणु
	.probe = axp288_extcon_probe,
	.id_table = axp288_extcon_table,
	.driver = अणु
		.name = "axp288_extcon",
		.pm = &axp288_extcon_pm_ops,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(axp288_extcon_driver);

MODULE_AUTHOR("Ramakrishna Pallala <ramakrishna.pallala@intel.com>");
MODULE_AUTHOR("Hans de Goede <hdegoede@redhat.com>");
MODULE_DESCRIPTION("X-Powers AXP288 extcon driver");
MODULE_LICENSE("GPL v2");
