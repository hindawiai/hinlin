<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * AMD MP2 PCIe communication driver
 * Copyright 2020 Advanced Micro Devices, Inc.
 *
 * Authors: Shyam Sundar S K <Shyam-sundar.S-k@amd.com>
 *	    Sandeep Singh <Sandeep.singh@amd.com>
 */

#समावेश <linux/bitops.h>
#समावेश <linux/delay.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/dmi.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/io-64-nonatomic-lo-hi.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>

#समावेश "amd_sfh_pcie.h"

#घोषणा DRIVER_NAME	"pcie_mp2_amd"
#घोषणा DRIVER_DESC	"AMD(R) PCIe MP2 Communication Driver"

#घोषणा ACEL_EN		BIT(0)
#घोषणा GYRO_EN		BIT(1)
#घोषणा MAGNO_EN	BIT(2)
#घोषणा ALS_EN		BIT(19)

अटल पूर्णांक sensor_mask_override = -1;
module_param_named(sensor_mask, sensor_mask_override, पूर्णांक, 0444);
MODULE_PARM_DESC(sensor_mask, "override the detected sensors mask");

व्योम amd_start_sensor(काष्ठा amd_mp2_dev *privdata, काष्ठा amd_mp2_sensor_info info)
अणु
	जोड़ sfh_cmd_param cmd_param;
	जोड़ sfh_cmd_base cmd_base;

	/* fill up command रेजिस्टर */
	स_रखो(&cmd_base, 0, माप(cmd_base));
	cmd_base.s.cmd_id = ENABLE_SENSOR;
	cmd_base.s.period = info.period;
	cmd_base.s.sensor_id = info.sensor_idx;

	/* fill up command param रेजिस्टर */
	स_रखो(&cmd_param, 0, माप(cmd_param));
	cmd_param.s.buf_layout = 1;
	cmd_param.s.buf_length = 16;

	ग_लिखोq(info.dma_address, privdata->mmio + AMD_C2P_MSG2);
	ग_लिखोl(cmd_param.ul, privdata->mmio + AMD_C2P_MSG1);
	ग_लिखोl(cmd_base.ul, privdata->mmio + AMD_C2P_MSG0);
पूर्ण

व्योम amd_stop_sensor(काष्ठा amd_mp2_dev *privdata, u16 sensor_idx)
अणु
	जोड़ sfh_cmd_base cmd_base;

	/* fill up command रेजिस्टर */
	स_रखो(&cmd_base, 0, माप(cmd_base));
	cmd_base.s.cmd_id = DISABLE_SENSOR;
	cmd_base.s.period = 0;
	cmd_base.s.sensor_id = sensor_idx;

	ग_लिखोq(0x0, privdata->mmio + AMD_C2P_MSG2);
	ग_लिखोl(cmd_base.ul, privdata->mmio + AMD_C2P_MSG0);
पूर्ण

व्योम amd_stop_all_sensors(काष्ठा amd_mp2_dev *privdata)
अणु
	जोड़ sfh_cmd_base cmd_base;

	/* fill up command रेजिस्टर */
	स_रखो(&cmd_base, 0, माप(cmd_base));
	cmd_base.s.cmd_id = STOP_ALL_SENSORS;
	cmd_base.s.period = 0;
	cmd_base.s.sensor_id = 0;

	ग_लिखोl(cmd_base.ul, privdata->mmio + AMD_C2P_MSG0);
पूर्ण

अटल स्थिर काष्ठा dmi_प्रणाली_id dmi_sensor_mask_overrides[] = अणु
	अणु
		.matches = अणु
			DMI_MATCH(DMI_PRODUCT_NAME, "HP ENVY x360 Convertible 13-ag0xxx"),
		पूर्ण,
		.driver_data = (व्योम *)(ACEL_EN | MAGNO_EN),
	पूर्ण,
	अणु
		.matches = अणु
			DMI_MATCH(DMI_PRODUCT_NAME, "HP ENVY x360 Convertible 15-cp0xxx"),
		पूर्ण,
		.driver_data = (व्योम *)(ACEL_EN | MAGNO_EN),
	पूर्ण,
	अणु पूर्ण
पूर्ण;

पूर्णांक amd_mp2_get_sensor_num(काष्ठा amd_mp2_dev *privdata, u8 *sensor_id)
अणु
	पूर्णांक activestatus, num_of_sensors = 0;
	स्थिर काष्ठा dmi_प्रणाली_id *dmi_id;
	u32 activecontrolstatus;

	अगर (sensor_mask_override == -1) अणु
		dmi_id = dmi_first_match(dmi_sensor_mask_overrides);
		अगर (dmi_id)
			sensor_mask_override = (दीर्घ)dmi_id->driver_data;
	पूर्ण

	अगर (sensor_mask_override >= 0) अणु
		activestatus = sensor_mask_override;
	पूर्ण अन्यथा अणु
		activecontrolstatus = पढ़ोl(privdata->mmio + AMD_P2C_MSG3);
		activestatus = activecontrolstatus >> 4;
	पूर्ण

	अगर (ACEL_EN  & activestatus)
		sensor_id[num_of_sensors++] = accel_idx;

	अगर (GYRO_EN & activestatus)
		sensor_id[num_of_sensors++] = gyro_idx;

	अगर (MAGNO_EN & activestatus)
		sensor_id[num_of_sensors++] = mag_idx;

	अगर (ALS_EN & activestatus)
		sensor_id[num_of_sensors++] = als_idx;

	वापस num_of_sensors;
पूर्ण

अटल व्योम amd_mp2_pci_हटाओ(व्योम *privdata)
अणु
	amd_sfh_hid_client_deinit(privdata);
	amd_stop_all_sensors(privdata);
पूर्ण

अटल पूर्णांक amd_mp2_pci_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा amd_mp2_dev *privdata;
	पूर्णांक rc;

	privdata = devm_kzalloc(&pdev->dev, माप(*privdata), GFP_KERNEL);
	अगर (!privdata)
		वापस -ENOMEM;

	privdata->pdev = pdev;
	pci_set_drvdata(pdev, privdata);
	rc = pcim_enable_device(pdev);
	अगर (rc)
		वापस rc;

	rc = pcim_iomap_regions(pdev, BIT(2), DRIVER_NAME);
	अगर (rc)
		वापस rc;

	privdata->mmio = pcim_iomap_table(pdev)[2];
	pci_set_master(pdev);
	rc = pci_set_dma_mask(pdev, DMA_BIT_MASK(64));
	अगर (rc) अणु
		rc = pci_set_dma_mask(pdev, DMA_BIT_MASK(32));
		वापस rc;
	पूर्ण
	rc = devm_add_action_or_reset(&pdev->dev, amd_mp2_pci_हटाओ, privdata);
	अगर (rc)
		वापस rc;

	वापस amd_sfh_hid_client_init(privdata);
पूर्ण

अटल स्थिर काष्ठा pci_device_id amd_mp2_pci_tbl[] = अणु
	अणु PCI_VDEVICE(AMD, PCI_DEVICE_ID_AMD_MP2) पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, amd_mp2_pci_tbl);

अटल काष्ठा pci_driver amd_mp2_pci_driver = अणु
	.name		= DRIVER_NAME,
	.id_table	= amd_mp2_pci_tbl,
	.probe		= amd_mp2_pci_probe,
पूर्ण;
module_pci_driver(amd_mp2_pci_driver);

MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("Shyam Sundar S K <Shyam-sundar.S-k@amd.com>");
MODULE_AUTHOR("Sandeep Singh <Sandeep.singh@amd.com>");
