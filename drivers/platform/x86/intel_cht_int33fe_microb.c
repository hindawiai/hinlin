<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Intel Cherry Trail ACPI INT33FE pseuकरो device driver क्रम devices with
 * USB Micro-B connector (e.g. without of FUSB302 USB Type-C controller)
 *
 * Copyright (C) 2019 Yauhen Kharuzhy <jekhor@gmail.com>
 *
 * At least one Intel Cherry Trail based device which ship with Winकरोws 10
 * (Lenovo YogaBook YB1-X91L/F tablet), have this weird INT33FE ACPI device
 * with a CRS table with 2 I2cSerialBusV2 resources, क्रम 2 dअगरferent chips
 * attached to various i2c busses:
 * 1. The Whiskey Cove PMIC, which is also described by the INT34D3 ACPI device
 * 2. TI BQ27542 Fuel Gauge Controller
 *
 * So this driver is a stub / pseuकरो driver whose only purpose is to
 * instantiate i2c-client क्रम battery fuel gauge, so that standard i2c driver
 * क्रम these chip can bind to the it.
 */

#समावेश <linux/acpi.h>
#समावेश <linux/i2c.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/slab.h>
#समावेश <linux/usb/pd.h>

#समावेश "intel_cht_int33fe_common.h"

अटल स्थिर अक्षर * स्थिर bq27xxx_suppliers[] = अणु "bq25890-charger" पूर्ण;

अटल स्थिर काष्ठा property_entry bq27xxx_props[] = अणु
	PROPERTY_ENTRY_STRING_ARRAY("supplied-from", bq27xxx_suppliers),
	अणु पूर्ण
पूर्ण;

अटल स्थिर काष्ठा software_node bq27xxx_node = अणु
	.properties = bq27xxx_props,
पूर्ण;

पूर्णांक cht_पूर्णांक33fe_microb_probe(काष्ठा cht_पूर्णांक33fe_data *data)
अणु
	काष्ठा device *dev = data->dev;
	काष्ठा i2c_board_info board_info;

	स_रखो(&board_info, 0, माप(board_info));
	strscpy(board_info.type, "bq27542", ARRAY_SIZE(board_info.type));
	board_info.dev_name = "bq27542";
	board_info.swnode = &bq27xxx_node;
	data->battery_fg = i2c_acpi_new_device(dev, 1, &board_info);

	वापस PTR_ERR_OR_ZERO(data->battery_fg);
पूर्ण

पूर्णांक cht_पूर्णांक33fe_microb_हटाओ(काष्ठा cht_पूर्णांक33fe_data *data)
अणु
	i2c_unरेजिस्टर_device(data->battery_fg);

	वापस 0;
पूर्ण
