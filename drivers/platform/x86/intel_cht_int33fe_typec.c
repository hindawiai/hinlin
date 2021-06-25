<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Intel Cherry Trail ACPI INT33FE pseuकरो device driver
 *
 * Copyright (C) 2017 Hans de Goede <hdegoede@redhat.com>
 *
 * Some Intel Cherry Trail based device which ship with Winकरोws 10, have
 * this weird INT33FE ACPI device with a CRS table with 4 I2cSerialBusV2
 * resources, क्रम 4 dअगरferent chips attached to various IतऑC buses:
 * 1. The Whiskey Cove PMIC, which is also described by the INT34D3 ACPI device
 * 2. Maxim MAX17047 Fuel Gauge Controller
 * 3. FUSB302 USB Type-C Controller
 * 4. PI3USB30532 USB चयन
 *
 * So this driver is a stub / pseuकरो driver whose only purpose is to
 * instantiate IतऑC clients क्रम chips 2 - 4, so that standard IतऑC drivers
 * क्रम these chips can bind to the them.
 */

#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pci.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/property.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/slab.h>
#समावेश <linux/usb/pd.h>

#समावेश "intel_cht_int33fe_common.h"

/*
 * Grrr, I severely dislike buggy BIOS-es. At least one BIOS क्रमागतerates
 * the max17047 both through the INT33FE ACPI device (it is right there
 * in the resources table) as well as through a separate MAX17047 device.
 *
 * These helpers are used to work around this by checking अगर an IतऑC client
 * क्रम the max17047 has alपढ़ोy been रेजिस्टरed.
 */
अटल पूर्णांक cht_पूर्णांक33fe_check_क्रम_max17047(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा i2c_client **max17047 = data;
	काष्ठा acpi_device *adev;

	adev = ACPI_COMPANION(dev);
	अगर (!adev)
		वापस 0;

	/* The MAX17047 ACPI node करोesn't have an UID, so we don't check that */
	अगर (!acpi_dev_hid_uid_match(adev, "MAX17047", शून्य))
		वापस 0;

	*max17047 = to_i2c_client(dev);
	वापस 1;
पूर्ण

अटल स्थिर अक्षर * स्थिर max17047_suppliers[] = अणु "bq24190-charger" पूर्ण;

अटल स्थिर काष्ठा property_entry max17047_properties[] = अणु
	PROPERTY_ENTRY_STRING_ARRAY("supplied-from", max17047_suppliers),
	अणु पूर्ण
पूर्ण;

अटल स्थिर काष्ठा software_node max17047_node = अणु
	.name = "max17047",
	.properties = max17047_properties,
पूर्ण;

/*
 * We are not using अंतरभूत property here because those are स्थिरant,
 * and we need to adjust this one at runसमय to poपूर्णांक to real
 * software node.
 */
अटल काष्ठा software_node_ref_args fusb302_mux_refs[] = अणु
	अणु .node = शून्य पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा property_entry fusb302_properties[] = अणु
	PROPERTY_ENTRY_STRING("linux,extcon-name", "cht_wcove_pwrsrc"),
	PROPERTY_ENTRY_REF_ARRAY("usb-role-switch", fusb302_mux_refs),
	अणु पूर्ण
पूर्ण;

अटल स्थिर काष्ठा software_node fusb302_node = अणु
	.name = "fusb302",
	.properties = fusb302_properties,
पूर्ण;

#घोषणा PDO_FIXED_FLAGS \
	(PDO_FIXED_DUAL_ROLE | PDO_FIXED_DATA_SWAP | PDO_FIXED_USB_COMM)

अटल स्थिर u32 src_pकरो[] = अणु
	PDO_FIXED(5000, 1500, PDO_FIXED_FLAGS),
पूर्ण;

अटल स्थिर u32 snk_pकरो[] = अणु
	PDO_FIXED(5000, 400, PDO_FIXED_FLAGS),
	PDO_VAR(5000, 12000, 3000),
पूर्ण;

अटल स्थिर काष्ठा software_node pi3usb30532_node = अणु
	.name = "pi3usb30532",
पूर्ण;

अटल स्थिर काष्ठा software_node displayport_node = अणु
	.name = "displayport",
पूर्ण;

अटल स्थिर काष्ठा property_entry usb_connector_properties[] = अणु
	PROPERTY_ENTRY_STRING("data-role", "dual"),
	PROPERTY_ENTRY_STRING("power-role", "dual"),
	PROPERTY_ENTRY_STRING("try-power-role", "sink"),
	PROPERTY_ENTRY_U32_ARRAY("source-pdos", src_pकरो),
	PROPERTY_ENTRY_U32_ARRAY("sink-pdos", snk_pकरो),
	PROPERTY_ENTRY_U32("op-sink-microwatt", 2500000),
	PROPERTY_ENTRY_REF("orientation-switch", &pi3usb30532_node),
	PROPERTY_ENTRY_REF("mode-switch", &pi3usb30532_node),
	PROPERTY_ENTRY_REF("displayport", &displayport_node),
	अणु पूर्ण
पूर्ण;

अटल स्थिर काष्ठा software_node usb_connector_node = अणु
	.name = "connector",
	.parent = &fusb302_node,
	.properties = usb_connector_properties,
पूर्ण;

अटल स्थिर काष्ठा software_node alपंचांगodes_node = अणु
	.name = "altmodes",
	.parent = &usb_connector_node,
पूर्ण;

अटल स्थिर काष्ठा property_entry dp_alपंचांगode_properties[] = अणु
	PROPERTY_ENTRY_U32("svid", 0xff01),
	PROPERTY_ENTRY_U32("vdo", 0x0c0086),
	अणु पूर्ण
पूर्ण;

अटल स्थिर काष्ठा software_node dp_alपंचांगode_node = अणु
	.name = "displayport-altmode",
	.parent = &alपंचांगodes_node,
	.properties = dp_alपंचांगode_properties,
पूर्ण;

अटल स्थिर काष्ठा software_node *node_group[] = अणु
	&fusb302_node,
	&max17047_node,
	&pi3usb30532_node,
	&displayport_node,
	&usb_connector_node,
	&alपंचांगodes_node,
	&dp_alपंचांगode_node,
	शून्य
पूर्ण;

अटल पूर्णांक cht_पूर्णांक33fe_setup_dp(काष्ठा cht_पूर्णांक33fe_data *data)
अणु
	काष्ठा fwnode_handle *fwnode;
	काष्ठा pci_dev *pdev;

	fwnode = software_node_fwnode(&displayport_node);
	अगर (!fwnode)
		वापस -ENODEV;

	/* First let's find the GPU PCI device */
	pdev = pci_get_class(PCI_CLASS_DISPLAY_VGA << 8, शून्य);
	अगर (!pdev || pdev->venकरोr != PCI_VENDOR_ID_INTEL) अणु
		pci_dev_put(pdev);
		वापस -ENODEV;
	पूर्ण

	/* Then the DP child device node */
	data->dp = device_get_named_child_node(&pdev->dev, "DD02");
	pci_dev_put(pdev);
	अगर (!data->dp)
		वापस -ENODEV;

	fwnode->secondary = ERR_PTR(-ENODEV);
	data->dp->secondary = fwnode;

	वापस 0;
पूर्ण

अटल व्योम cht_पूर्णांक33fe_हटाओ_nodes(काष्ठा cht_पूर्णांक33fe_data *data)
अणु
	software_node_unरेजिस्टर_node_group(node_group);

	अगर (fusb302_mux_refs[0].node) अणु
		fwnode_handle_put(software_node_fwnode(fusb302_mux_refs[0].node));
		fusb302_mux_refs[0].node = शून्य;
	पूर्ण

	अगर (data->dp) अणु
		data->dp->secondary = शून्य;
		fwnode_handle_put(data->dp);
		data->dp = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक cht_पूर्णांक33fe_add_nodes(काष्ठा cht_पूर्णांक33fe_data *data)
अणु
	स्थिर काष्ठा software_node *mux_ref_node;
	पूर्णांक ret;

	/*
	 * There is no ACPI device node क्रम the USB role mux, so we need to रुको
	 * until the mux driver has created software node क्रम the mux device.
	 * It means we depend on the mux driver. This function will वापस
	 * -EPROBE_DEFER until the mux device is रेजिस्टरed.
	 */
	mux_ref_node = software_node_find_by_name(शून्य, "intel-xhci-usb-sw");
	अगर (!mux_ref_node)
		वापस -EPROBE_DEFER;

	/*
	 * Update node used in "usb-role-switch" property. Note that we
	 * rely on software_node_रेजिस्टर_nodes() to use the original
	 * instance of properties instead of copying them.
	 */
	fusb302_mux_refs[0].node = mux_ref_node;

	ret = software_node_रेजिस्टर_node_group(node_group);
	अगर (ret)
		वापस ret;

	/* The devices that are not created in this driver need extra steps. */

	/*
	 * The DP connector करोes have ACPI device node. In this हाल we can just
	 * find that ACPI node and assign our node as the secondary node to it.
	 */
	ret = cht_पूर्णांक33fe_setup_dp(data);
	अगर (ret)
		जाओ err_हटाओ_nodes;

	वापस 0;

err_हटाओ_nodes:
	cht_पूर्णांक33fe_हटाओ_nodes(data);

	वापस ret;
पूर्ण

अटल पूर्णांक
cht_पूर्णांक33fe_रेजिस्टर_max17047(काष्ठा device *dev, काष्ठा cht_पूर्णांक33fe_data *data)
अणु
	काष्ठा i2c_client *max17047 = शून्य;
	काष्ठा i2c_board_info board_info;
	काष्ठा fwnode_handle *fwnode;
	पूर्णांक ret;

	fwnode = software_node_fwnode(&max17047_node);
	अगर (!fwnode)
		वापस -ENODEV;

	i2c_क्रम_each_dev(&max17047, cht_पूर्णांक33fe_check_क्रम_max17047);
	अगर (max17047) अणु
		/* Pre-existing IतऑC client क्रम the max17047, add device properties */
		set_secondary_fwnode(&max17047->dev, fwnode);
		/* And re-probe to get the new device properties applied */
		ret = device_reprobe(&max17047->dev);
		अगर (ret)
			dev_warn(dev, "Reprobing max17047 error: %d\n", ret);
		वापस 0;
	पूर्ण

	स_रखो(&board_info, 0, माप(board_info));
	strlcpy(board_info.type, "max17047", I2C_NAME_SIZE);
	board_info.dev_name = "max17047";
	board_info.fwnode = fwnode;
	data->battery_fg = i2c_acpi_new_device(dev, 1, &board_info);

	वापस PTR_ERR_OR_ZERO(data->battery_fg);
पूर्ण

पूर्णांक cht_पूर्णांक33fe_typec_probe(काष्ठा cht_पूर्णांक33fe_data *data)
अणु
	काष्ठा device *dev = data->dev;
	काष्ठा i2c_board_info board_info;
	काष्ठा fwnode_handle *fwnode;
	काष्ठा regulator *regulator;
	पूर्णांक fusb302_irq;
	पूर्णांक ret;

	/*
	 * We expect the WC PMIC to be paired with a TI bq24292i अक्षरger-IC.
	 * We check क्रम the bq24292i vbus regulator here, this has 2 purposes:
	 * 1) The bq24292i allows अक्षरging with up to 12V, setting the fusb302's
	 *    max-snk voltage to 12V with another अक्षरger-IC is not good.
	 * 2) For the fusb302 driver to get the bq24292i vbus regulator, the
	 *    regulator-map, which is part of the bq24292i regulator_init_data,
	 *    must be रेजिस्टरed beक्रमe the fusb302 is instantiated, otherwise
	 *    it will end up with a dummy-regulator.
	 * Note "cht_wc_usb_typec_vbus" comes from the regulator_init_data
	 * which is defined in i2c-cht-wc.c from where the bq24292i IतऑC client
	 * माला_लो instantiated. We use regulator_get_optional here so that we
	 * करोn't end up getting a dummy-regulator ourselves.
	 */
	regulator = regulator_get_optional(dev, "cht_wc_usb_typec_vbus");
	अगर (IS_ERR(regulator)) अणु
		ret = PTR_ERR(regulator);
		वापस (ret == -ENODEV) ? -EPROBE_DEFER : ret;
	पूर्ण
	regulator_put(regulator);

	/* The FUSB302 uses the IRQ at index 1 and is the only IRQ user */
	fusb302_irq = acpi_dev_gpio_irq_get(ACPI_COMPANION(dev), 1);
	अगर (fusb302_irq < 0) अणु
		अगर (fusb302_irq != -EPROBE_DEFER)
			dev_err(dev, "Error getting FUSB302 irq\n");
		वापस fusb302_irq;
	पूर्ण

	ret = cht_पूर्णांक33fe_add_nodes(data);
	अगर (ret)
		वापस ret;

	/* Work around BIOS bug, see comment on cht_पूर्णांक33fe_check_क्रम_max17047() */
	ret = cht_पूर्णांक33fe_रेजिस्टर_max17047(dev, data);
	अगर (ret)
		जाओ out_हटाओ_nodes;

	fwnode = software_node_fwnode(&fusb302_node);
	अगर (!fwnode) अणु
		ret = -ENODEV;
		जाओ out_unरेजिस्टर_max17047;
	पूर्ण

	स_रखो(&board_info, 0, माप(board_info));
	strlcpy(board_info.type, "typec_fusb302", I2C_NAME_SIZE);
	board_info.dev_name = "fusb302";
	board_info.fwnode = fwnode;
	board_info.irq = fusb302_irq;

	data->fusb302 = i2c_acpi_new_device(dev, 2, &board_info);
	अगर (IS_ERR(data->fusb302)) अणु
		ret = PTR_ERR(data->fusb302);
		जाओ out_unरेजिस्टर_max17047;
	पूर्ण

	fwnode = software_node_fwnode(&pi3usb30532_node);
	अगर (!fwnode) अणु
		ret = -ENODEV;
		जाओ out_unरेजिस्टर_fusb302;
	पूर्ण

	स_रखो(&board_info, 0, माप(board_info));
	board_info.dev_name = "pi3usb30532";
	board_info.fwnode = fwnode;
	strlcpy(board_info.type, "pi3usb30532", I2C_NAME_SIZE);

	data->pi3usb30532 = i2c_acpi_new_device(dev, 3, &board_info);
	अगर (IS_ERR(data->pi3usb30532)) अणु
		ret = PTR_ERR(data->pi3usb30532);
		जाओ out_unरेजिस्टर_fusb302;
	पूर्ण

	वापस 0;

out_unरेजिस्टर_fusb302:
	i2c_unरेजिस्टर_device(data->fusb302);

out_unरेजिस्टर_max17047:
	i2c_unरेजिस्टर_device(data->battery_fg);

out_हटाओ_nodes:
	cht_पूर्णांक33fe_हटाओ_nodes(data);

	वापस ret;
पूर्ण

पूर्णांक cht_पूर्णांक33fe_typec_हटाओ(काष्ठा cht_पूर्णांक33fe_data *data)
अणु
	i2c_unरेजिस्टर_device(data->pi3usb30532);
	i2c_unरेजिस्टर_device(data->fusb302);
	i2c_unरेजिस्टर_device(data->battery_fg);

	cht_पूर्णांक33fe_हटाओ_nodes(data);

	वापस 0;
पूर्ण
