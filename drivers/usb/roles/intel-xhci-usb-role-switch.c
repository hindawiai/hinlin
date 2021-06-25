<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Intel XHCI (Cherry Trail, Broxton and others) USB OTG role चयन driver
 *
 * Copyright (c) 2016-2017 Hans de Goede <hdegoede@redhat.com>
 *
 * Loosely based on android x86 kernel code which is:
 *
 * Copyright (C) 2014 Intel Corp.
 *
 * Author: Wu, Hao
 */

#समावेश <linux/acpi.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/property.h>
#समावेश <linux/usb/role.h>

/* रेजिस्टर definition */
#घोषणा DUAL_ROLE_CFG0			0x68
#घोषणा SW_VBUS_VALID			BIT(24)
#घोषणा SW_IDPIN_EN			BIT(21)
#घोषणा SW_IDPIN			BIT(20)
#घोषणा SW_SWITCH_EN			BIT(16)

#घोषणा DRD_CONFIG_DYNAMIC		0
#घोषणा DRD_CONFIG_STATIC_HOST		1
#घोषणा DRD_CONFIG_STATIC_DEVICE	2
#घोषणा DRD_CONFIG_MASK			3

#घोषणा DUAL_ROLE_CFG1			0x6c
#घोषणा HOST_MODE			BIT(29)

#घोषणा DUAL_ROLE_CFG1_POLL_TIMEOUT	1000

#घोषणा DRV_NAME			"intel_xhci_usb_sw"

काष्ठा पूर्णांकel_xhci_usb_data अणु
	काष्ठा device *dev;
	काष्ठा usb_role_चयन *role_sw;
	व्योम __iomem *base;
	bool enable_sw_चयन;
पूर्ण;

अटल स्थिर काष्ठा software_node पूर्णांकel_xhci_usb_node = अणु
	"intel-xhci-usb-sw",
पूर्ण;

अटल पूर्णांक पूर्णांकel_xhci_usb_set_role(काष्ठा usb_role_चयन *sw,
				   क्रमागत usb_role role)
अणु
	काष्ठा पूर्णांकel_xhci_usb_data *data = usb_role_चयन_get_drvdata(sw);
	अचिन्हित दीर्घ समयout;
	acpi_status status;
	u32 glk, val;
	u32 drd_config = DRD_CONFIG_DYNAMIC;

	/*
	 * On many CHT devices ACPI event (_AEI) handlers पढ़ो / modअगरy /
	 * ग_लिखो the cfg0 रेजिस्टर, just like we करो. Take the ACPI lock
	 * to aव्योम us racing with the AML code.
	 */
	status = acpi_acquire_global_lock(ACPI_WAIT_FOREVER, &glk);
	अगर (ACPI_FAILURE(status) && status != AE_NOT_CONFIGURED) अणु
		dev_err(data->dev, "Error could not acquire lock\n");
		वापस -EIO;
	पूर्ण

	pm_runसमय_get_sync(data->dev);

	/*
	 * Set idpin value as requested.
	 * Since some devices rely on firmware setting DRD_CONFIG and
	 * SW_SWITCH_EN bits to be zero क्रम role चयन,
	 * करो not set these bits क्रम those devices.
	 */
	val = पढ़ोl(data->base + DUAL_ROLE_CFG0);
	चयन (role) अणु
	हाल USB_ROLE_NONE:
		val |= SW_IDPIN;
		val &= ~SW_VBUS_VALID;
		drd_config = DRD_CONFIG_DYNAMIC;
		अवरोध;
	हाल USB_ROLE_HOST:
		val &= ~SW_IDPIN;
		val &= ~SW_VBUS_VALID;
		drd_config = DRD_CONFIG_STATIC_HOST;
		अवरोध;
	हाल USB_ROLE_DEVICE:
		val |= SW_IDPIN;
		val |= SW_VBUS_VALID;
		drd_config = DRD_CONFIG_STATIC_DEVICE;
		अवरोध;
	पूर्ण
	val |= SW_IDPIN_EN;
	अगर (data->enable_sw_चयन) अणु
		val &= ~DRD_CONFIG_MASK;
		val |= SW_SWITCH_EN | drd_config;
	पूर्ण
	ग_लिखोl(val, data->base + DUAL_ROLE_CFG0);

	acpi_release_global_lock(glk);

	/* In most हाल it takes about 600ms to finish mode चयनing */
	समयout = jअगरfies + msecs_to_jअगरfies(DUAL_ROLE_CFG1_POLL_TIMEOUT);

	/* Polling on CFG1 रेजिस्टर to confirm mode चयन.*/
	करो अणु
		val = पढ़ोl(data->base + DUAL_ROLE_CFG1);
		अगर (!!(val & HOST_MODE) == (role == USB_ROLE_HOST)) अणु
			pm_runसमय_put(data->dev);
			वापस 0;
		पूर्ण

		/* Interval क्रम polling is set to about 5 - 10 ms */
		usleep_range(5000, 10000);
	पूर्ण जबतक (समय_beक्रमe(jअगरfies, समयout));

	pm_runसमय_put(data->dev);

	dev_warn(data->dev, "Timeout waiting for role-switch\n");
	वापस -ETIMEDOUT;
पूर्ण

अटल क्रमागत usb_role पूर्णांकel_xhci_usb_get_role(काष्ठा usb_role_चयन *sw)
अणु
	काष्ठा पूर्णांकel_xhci_usb_data *data = usb_role_चयन_get_drvdata(sw);
	क्रमागत usb_role role;
	u32 val;

	pm_runसमय_get_sync(data->dev);
	val = पढ़ोl(data->base + DUAL_ROLE_CFG0);
	pm_runसमय_put(data->dev);

	अगर (!(val & SW_IDPIN))
		role = USB_ROLE_HOST;
	अन्यथा अगर (val & SW_VBUS_VALID)
		role = USB_ROLE_DEVICE;
	अन्यथा
		role = USB_ROLE_NONE;

	वापस role;
पूर्ण

अटल पूर्णांक पूर्णांकel_xhci_usb_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा usb_role_चयन_desc sw_desc = अणु पूर्ण;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा पूर्णांकel_xhci_usb_data *data;
	काष्ठा resource *res;
	पूर्णांक ret;

	data = devm_kzalloc(dev, माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res)
		वापस -EINVAL;
	data->base = devm_ioremap(dev, res->start, resource_size(res));
	अगर (!data->base)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, data);

	ret = software_node_रेजिस्टर(&पूर्णांकel_xhci_usb_node);
	अगर (ret)
		वापस ret;

	sw_desc.set = पूर्णांकel_xhci_usb_set_role,
	sw_desc.get = पूर्णांकel_xhci_usb_get_role,
	sw_desc.allow_userspace_control = true,
	sw_desc.fwnode = software_node_fwnode(&पूर्णांकel_xhci_usb_node);
	sw_desc.driver_data = data;

	data->dev = dev;
	data->enable_sw_चयन = !device_property_पढ़ो_bool(dev,
						"sw_switch_disable");

	data->role_sw = usb_role_चयन_रेजिस्टर(dev, &sw_desc);
	अगर (IS_ERR(data->role_sw)) अणु
		fwnode_handle_put(sw_desc.fwnode);
		वापस PTR_ERR(data->role_sw);
	पूर्ण

	pm_runसमय_set_active(dev);
	pm_runसमय_enable(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_xhci_usb_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा पूर्णांकel_xhci_usb_data *data = platक्रमm_get_drvdata(pdev);

	pm_runसमय_disable(&pdev->dev);

	usb_role_चयन_unरेजिस्टर(data->role_sw);
	fwnode_handle_put(software_node_fwnode(&पूर्णांकel_xhci_usb_node));

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_id पूर्णांकel_xhci_usb_table[] = अणु
	अणु .name = DRV_NAME पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, पूर्णांकel_xhci_usb_table);

अटल काष्ठा platक्रमm_driver पूर्णांकel_xhci_usb_driver = अणु
	.driver = अणु
		.name = DRV_NAME,
	पूर्ण,
	.id_table = पूर्णांकel_xhci_usb_table,
	.probe = पूर्णांकel_xhci_usb_probe,
	.हटाओ = पूर्णांकel_xhci_usb_हटाओ,
पूर्ण;

module_platक्रमm_driver(पूर्णांकel_xhci_usb_driver);

MODULE_AUTHOR("Hans de Goede <hdegoede@redhat.com>");
MODULE_DESCRIPTION("Intel XHCI USB role switch driver");
MODULE_LICENSE("GPL");
