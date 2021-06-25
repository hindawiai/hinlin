<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Intel MAX 10 Board Management Controller chip
 *
 * Copyright (C) 2018-2020 Intel Corporation. All rights reserved.
 */
#समावेश <linux/bitfield.h>
#समावेश <linux/init.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/mfd/पूर्णांकel-m10-bmc.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/regmap.h>
#समावेश <linux/spi/spi.h>

क्रमागत m10bmc_type अणु
	M10_N3000,
	M10_D5005
पूर्ण;

अटल काष्ठा mfd_cell m10bmc_d5005_subdevs[] = अणु
	अणु .name = "d5005bmc-hwmon" पूर्ण,
पूर्ण;

अटल काष्ठा mfd_cell m10bmc_pacn3000_subdevs[] = अणु
	अणु .name = "n3000bmc-hwmon" पूर्ण,
	अणु .name = "n3000bmc-retimer" पूर्ण,
	अणु .name = "n3000bmc-secure" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_range m10bmc_regmap_range[] = अणु
	regmap_reg_range(M10BMC_LEGACY_BUILD_VER, M10BMC_LEGACY_BUILD_VER),
	regmap_reg_range(M10BMC_SYS_BASE, M10BMC_SYS_END),
	regmap_reg_range(M10BMC_FLASH_BASE, M10BMC_FLASH_END),
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table m10bmc_access_table = अणु
	.yes_ranges	= m10bmc_regmap_range,
	.n_yes_ranges	= ARRAY_SIZE(m10bmc_regmap_range),
पूर्ण;

अटल काष्ठा regmap_config पूर्णांकel_m10bmc_regmap_config = अणु
	.reg_bits = 32,
	.val_bits = 32,
	.reg_stride = 4,
	.wr_table = &m10bmc_access_table,
	.rd_table = &m10bmc_access_table,
	.max_रेजिस्टर = M10BMC_MEM_END,
पूर्ण;

अटल sमाप_प्रकार bmc_version_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा पूर्णांकel_m10bmc *ddata = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	ret = m10bmc_sys_पढ़ो(ddata, M10BMC_BUILD_VER, &val);
	अगर (ret)
		वापस ret;

	वापस प्र_लिखो(buf, "0x%x\n", val);
पूर्ण
अटल DEVICE_ATTR_RO(bmc_version);

अटल sमाप_प्रकार bmcfw_version_show(काष्ठा device *dev,
				  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा पूर्णांकel_m10bmc *ddata = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	ret = m10bmc_sys_पढ़ो(ddata, NIOS2_FW_VERSION, &val);
	अगर (ret)
		वापस ret;

	वापस प्र_लिखो(buf, "0x%x\n", val);
पूर्ण
अटल DEVICE_ATTR_RO(bmcfw_version);

अटल sमाप_प्रकार mac_address_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा पूर्णांकel_m10bmc *max10 = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक macaddr_low, macaddr_high;
	पूर्णांक ret;

	ret = m10bmc_sys_पढ़ो(max10, M10BMC_MAC_LOW, &macaddr_low);
	अगर (ret)
		वापस ret;

	ret = m10bmc_sys_पढ़ो(max10, M10BMC_MAC_HIGH, &macaddr_high);
	अगर (ret)
		वापस ret;

	वापस sysfs_emit(buf, "%02x:%02x:%02x:%02x:%02x:%02x\n",
			  (u8)FIELD_GET(M10BMC_MAC_BYTE1, macaddr_low),
			  (u8)FIELD_GET(M10BMC_MAC_BYTE2, macaddr_low),
			  (u8)FIELD_GET(M10BMC_MAC_BYTE3, macaddr_low),
			  (u8)FIELD_GET(M10BMC_MAC_BYTE4, macaddr_low),
			  (u8)FIELD_GET(M10BMC_MAC_BYTE5, macaddr_high),
			  (u8)FIELD_GET(M10BMC_MAC_BYTE6, macaddr_high));
पूर्ण
अटल DEVICE_ATTR_RO(mac_address);

अटल sमाप_प्रकार mac_count_show(काष्ठा device *dev,
			      काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा पूर्णांकel_m10bmc *max10 = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक macaddr_high;
	पूर्णांक ret;

	ret = m10bmc_sys_पढ़ो(max10, M10BMC_MAC_HIGH, &macaddr_high);
	अगर (ret)
		वापस ret;

	वापस sysfs_emit(buf, "%u\n",
			  (u8)FIELD_GET(M10BMC_MAC_COUNT, macaddr_high));
पूर्ण
अटल DEVICE_ATTR_RO(mac_count);

अटल काष्ठा attribute *m10bmc_attrs[] = अणु
	&dev_attr_bmc_version.attr,
	&dev_attr_bmcfw_version.attr,
	&dev_attr_mac_address.attr,
	&dev_attr_mac_count.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(m10bmc);

अटल पूर्णांक check_m10bmc_version(काष्ठा पूर्णांकel_m10bmc *ddata)
अणु
	अचिन्हित पूर्णांक v;
	पूर्णांक ret;

	/*
	 * This check is to filter out the very old legacy BMC versions. In the
	 * old BMC chips, the BMC version info is stored in the old version
	 * रेजिस्टर (M10BMC_LEGACY_BUILD_VER), so its पढ़ो out value would have
	 * not been M10BMC_VER_LEGACY_INVALID (0xffffffff). But in new BMC
	 * chips that the driver supports, the value of this रेजिस्टर should be
	 * M10BMC_VER_LEGACY_INVALID.
	 */
	ret = m10bmc_raw_पढ़ो(ddata, M10BMC_LEGACY_BUILD_VER, &v);
	अगर (ret)
		वापस -ENODEV;

	अगर (v != M10BMC_VER_LEGACY_INVALID) अणु
		dev_err(ddata->dev, "bad version M10BMC detected\n");
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_m10_bmc_spi_probe(काष्ठा spi_device *spi)
अणु
	स्थिर काष्ठा spi_device_id *id = spi_get_device_id(spi);
	काष्ठा device *dev = &spi->dev;
	काष्ठा mfd_cell *cells;
	काष्ठा पूर्णांकel_m10bmc *ddata;
	पूर्णांक ret, n_cell;

	ddata = devm_kzalloc(dev, माप(*ddata), GFP_KERNEL);
	अगर (!ddata)
		वापस -ENOMEM;

	ddata->dev = dev;

	ddata->regmap =
		devm_regmap_init_spi_avmm(spi, &पूर्णांकel_m10bmc_regmap_config);
	अगर (IS_ERR(ddata->regmap)) अणु
		ret = PTR_ERR(ddata->regmap);
		dev_err(dev, "Failed to allocate regmap: %d\n", ret);
		वापस ret;
	पूर्ण

	spi_set_drvdata(spi, ddata);

	ret = check_m10bmc_version(ddata);
	अगर (ret) अणु
		dev_err(dev, "Failed to identify m10bmc hardware\n");
		वापस ret;
	पूर्ण

	चयन (id->driver_data) अणु
	हाल M10_N3000:
		cells = m10bmc_pacn3000_subdevs;
		n_cell = ARRAY_SIZE(m10bmc_pacn3000_subdevs);
		अवरोध;
	हाल M10_D5005:
		cells = m10bmc_d5005_subdevs;
		n_cell = ARRAY_SIZE(m10bmc_d5005_subdevs);
		अवरोध;
	शेष:
		वापस -ENODEV;
	पूर्ण

	ret = devm_mfd_add_devices(dev, PLATFORM_DEVID_AUTO, cells, n_cell,
				   शून्य, 0, शून्य);
	अगर (ret)
		dev_err(dev, "Failed to register sub-devices: %d\n", ret);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा spi_device_id m10bmc_spi_id[] = अणु
	अणु "m10-n3000", M10_N3000 पूर्ण,
	अणु "m10-d5005", M10_D5005 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(spi, m10bmc_spi_id);

अटल काष्ठा spi_driver पूर्णांकel_m10bmc_spi_driver = अणु
	.driver = अणु
		.name = "intel-m10-bmc",
		.dev_groups = m10bmc_groups,
	पूर्ण,
	.probe = पूर्णांकel_m10_bmc_spi_probe,
	.id_table = m10bmc_spi_id,
पूर्ण;
module_spi_driver(पूर्णांकel_m10bmc_spi_driver);

MODULE_DESCRIPTION("Intel MAX 10 BMC Device Driver");
MODULE_AUTHOR("Intel Corporation");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("spi:intel-m10-bmc");
