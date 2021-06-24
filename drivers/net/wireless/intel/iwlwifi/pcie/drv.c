<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause
/*
 * Copyright (C) 2005-2014, 2018-2021 Intel Corporation
 * Copyright (C) 2013-2015 Intel Mobile Communications GmbH
 * Copyright (C) 2016-2017 Intel Deutschland GmbH
 */
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/acpi.h>

#समावेश "fw/acpi.h"

#समावेश "iwl-trans.h"
#समावेश "iwl-drv.h"
#समावेश "iwl-prph.h"
#समावेश "internal.h"

#घोषणा TRANS_CFG_MARKER BIT(0)
#घोषणा _IS_A(cfg, _काष्ठा) __builtin_types_compatible_p(typeof(cfg),	\
							 काष्ठा _काष्ठा)
बाह्य पूर्णांक _invalid_type;
#घोषणा _TRANS_CFG_MARKER(cfg)						\
	(__builtin_choose_expr(_IS_A(cfg, iwl_cfg_trans_params),	\
			       TRANS_CFG_MARKER,			\
	 __builtin_choose_expr(_IS_A(cfg, iwl_cfg), 0, _invalid_type)))
#घोषणा _ASSIGN_CFG(cfg) (_TRANS_CFG_MARKER(cfg) + (kernel_uदीर्घ_t)&(cfg))

#घोषणा IWL_PCI_DEVICE(dev, subdev, cfg) \
	.venकरोr = PCI_VENDOR_ID_INTEL,  .device = (dev), \
	.subvenकरोr = PCI_ANY_ID, .subdevice = (subdev), \
	.driver_data = _ASSIGN_CFG(cfg)

/* Hardware specअगरic file defines the PCI IDs table क्रम that hardware module */
अटल स्थिर काष्ठा pci_device_id iwl_hw_card_ids[] = अणु
#अगर IS_ENABLED(CONFIG_IWLDVM)
	अणुIWL_PCI_DEVICE(0x4232, 0x1201, iwl5100_agn_cfg)पूर्ण, /* Mini Card */
	अणुIWL_PCI_DEVICE(0x4232, 0x1301, iwl5100_agn_cfg)पूर्ण, /* Half Mini Card */
	अणुIWL_PCI_DEVICE(0x4232, 0x1204, iwl5100_agn_cfg)पूर्ण, /* Mini Card */
	अणुIWL_PCI_DEVICE(0x4232, 0x1304, iwl5100_agn_cfg)पूर्ण, /* Half Mini Card */
	अणुIWL_PCI_DEVICE(0x4232, 0x1205, iwl5100_bgn_cfg)पूर्ण, /* Mini Card */
	अणुIWL_PCI_DEVICE(0x4232, 0x1305, iwl5100_bgn_cfg)पूर्ण, /* Half Mini Card */
	अणुIWL_PCI_DEVICE(0x4232, 0x1206, iwl5100_abg_cfg)पूर्ण, /* Mini Card */
	अणुIWL_PCI_DEVICE(0x4232, 0x1306, iwl5100_abg_cfg)पूर्ण, /* Half Mini Card */
	अणुIWL_PCI_DEVICE(0x4232, 0x1221, iwl5100_agn_cfg)पूर्ण, /* Mini Card */
	अणुIWL_PCI_DEVICE(0x4232, 0x1321, iwl5100_agn_cfg)पूर्ण, /* Half Mini Card */
	अणुIWL_PCI_DEVICE(0x4232, 0x1224, iwl5100_agn_cfg)पूर्ण, /* Mini Card */
	अणुIWL_PCI_DEVICE(0x4232, 0x1324, iwl5100_agn_cfg)पूर्ण, /* Half Mini Card */
	अणुIWL_PCI_DEVICE(0x4232, 0x1225, iwl5100_bgn_cfg)पूर्ण, /* Mini Card */
	अणुIWL_PCI_DEVICE(0x4232, 0x1325, iwl5100_bgn_cfg)पूर्ण, /* Half Mini Card */
	अणुIWL_PCI_DEVICE(0x4232, 0x1226, iwl5100_abg_cfg)पूर्ण, /* Mini Card */
	अणुIWL_PCI_DEVICE(0x4232, 0x1326, iwl5100_abg_cfg)पूर्ण, /* Half Mini Card */
	अणुIWL_PCI_DEVICE(0x4237, 0x1211, iwl5100_agn_cfg)पूर्ण, /* Mini Card */
	अणुIWL_PCI_DEVICE(0x4237, 0x1311, iwl5100_agn_cfg)पूर्ण, /* Half Mini Card */
	अणुIWL_PCI_DEVICE(0x4237, 0x1214, iwl5100_agn_cfg)पूर्ण, /* Mini Card */
	अणुIWL_PCI_DEVICE(0x4237, 0x1314, iwl5100_agn_cfg)पूर्ण, /* Half Mini Card */
	अणुIWL_PCI_DEVICE(0x4237, 0x1215, iwl5100_bgn_cfg)पूर्ण, /* Mini Card */
	अणुIWL_PCI_DEVICE(0x4237, 0x1315, iwl5100_bgn_cfg)पूर्ण, /* Half Mini Card */
	अणुIWL_PCI_DEVICE(0x4237, 0x1216, iwl5100_abg_cfg)पूर्ण, /* Mini Card */
	अणुIWL_PCI_DEVICE(0x4237, 0x1316, iwl5100_abg_cfg)पूर्ण, /* Half Mini Card */

/* 5300 Series WiFi */
	अणुIWL_PCI_DEVICE(0x4235, 0x1021, iwl5300_agn_cfg)पूर्ण, /* Mini Card */
	अणुIWL_PCI_DEVICE(0x4235, 0x1121, iwl5300_agn_cfg)पूर्ण, /* Half Mini Card */
	अणुIWL_PCI_DEVICE(0x4235, 0x1024, iwl5300_agn_cfg)पूर्ण, /* Mini Card */
	अणुIWL_PCI_DEVICE(0x4235, 0x1124, iwl5300_agn_cfg)पूर्ण, /* Half Mini Card */
	अणुIWL_PCI_DEVICE(0x4235, 0x1001, iwl5300_agn_cfg)पूर्ण, /* Mini Card */
	अणुIWL_PCI_DEVICE(0x4235, 0x1101, iwl5300_agn_cfg)पूर्ण, /* Half Mini Card */
	अणुIWL_PCI_DEVICE(0x4235, 0x1004, iwl5300_agn_cfg)पूर्ण, /* Mini Card */
	अणुIWL_PCI_DEVICE(0x4235, 0x1104, iwl5300_agn_cfg)पूर्ण, /* Half Mini Card */
	अणुIWL_PCI_DEVICE(0x4236, 0x1011, iwl5300_agn_cfg)पूर्ण, /* Mini Card */
	अणुIWL_PCI_DEVICE(0x4236, 0x1111, iwl5300_agn_cfg)पूर्ण, /* Half Mini Card */
	अणुIWL_PCI_DEVICE(0x4236, 0x1014, iwl5300_agn_cfg)पूर्ण, /* Mini Card */
	अणुIWL_PCI_DEVICE(0x4236, 0x1114, iwl5300_agn_cfg)पूर्ण, /* Half Mini Card */

/* 5350 Series WiFi/WiMax */
	अणुIWL_PCI_DEVICE(0x423A, 0x1001, iwl5350_agn_cfg)पूर्ण, /* Mini Card */
	अणुIWL_PCI_DEVICE(0x423A, 0x1021, iwl5350_agn_cfg)पूर्ण, /* Mini Card */
	अणुIWL_PCI_DEVICE(0x423B, 0x1011, iwl5350_agn_cfg)पूर्ण, /* Mini Card */

/* 5150 Series Wअगरi/WiMax */
	अणुIWL_PCI_DEVICE(0x423C, 0x1201, iwl5150_agn_cfg)पूर्ण, /* Mini Card */
	अणुIWL_PCI_DEVICE(0x423C, 0x1301, iwl5150_agn_cfg)पूर्ण, /* Half Mini Card */
	अणुIWL_PCI_DEVICE(0x423C, 0x1206, iwl5150_abg_cfg)पूर्ण, /* Mini Card */
	अणुIWL_PCI_DEVICE(0x423C, 0x1306, iwl5150_abg_cfg)पूर्ण, /* Half Mini Card */
	अणुIWL_PCI_DEVICE(0x423C, 0x1221, iwl5150_agn_cfg)पूर्ण, /* Mini Card */
	अणुIWL_PCI_DEVICE(0x423C, 0x1321, iwl5150_agn_cfg)पूर्ण, /* Half Mini Card */
	अणुIWL_PCI_DEVICE(0x423C, 0x1326, iwl5150_abg_cfg)पूर्ण, /* Half Mini Card */

	अणुIWL_PCI_DEVICE(0x423D, 0x1211, iwl5150_agn_cfg)पूर्ण, /* Mini Card */
	अणुIWL_PCI_DEVICE(0x423D, 0x1311, iwl5150_agn_cfg)पूर्ण, /* Half Mini Card */
	अणुIWL_PCI_DEVICE(0x423D, 0x1216, iwl5150_abg_cfg)पूर्ण, /* Mini Card */
	अणुIWL_PCI_DEVICE(0x423D, 0x1316, iwl5150_abg_cfg)पूर्ण, /* Half Mini Card */

/* 6x00 Series */
	अणुIWL_PCI_DEVICE(0x422B, 0x1101, iwl6000_3agn_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x422B, 0x1108, iwl6000_3agn_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x422B, 0x1121, iwl6000_3agn_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x422B, 0x1128, iwl6000_3agn_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x422C, 0x1301, iwl6000i_2agn_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x422C, 0x1306, iwl6000i_2abg_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x422C, 0x1307, iwl6000i_2bg_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x422C, 0x1321, iwl6000i_2agn_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x422C, 0x1326, iwl6000i_2abg_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x4238, 0x1111, iwl6000_3agn_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x4238, 0x1118, iwl6000_3agn_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x4239, 0x1311, iwl6000i_2agn_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x4239, 0x1316, iwl6000i_2abg_cfg)पूर्ण,

/* 6x05 Series */
	अणुIWL_PCI_DEVICE(0x0082, 0x1301, iwl6005_2agn_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x0082, 0x1306, iwl6005_2abg_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x0082, 0x1307, iwl6005_2bg_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x0082, 0x1308, iwl6005_2agn_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x0082, 0x1321, iwl6005_2agn_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x0082, 0x1326, iwl6005_2abg_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x0082, 0x1328, iwl6005_2agn_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x0085, 0x1311, iwl6005_2agn_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x0085, 0x1318, iwl6005_2agn_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x0085, 0x1316, iwl6005_2abg_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x0082, 0xC020, iwl6005_2agn_sff_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x0085, 0xC220, iwl6005_2agn_sff_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x0085, 0xC228, iwl6005_2agn_sff_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x0082, 0x4820, iwl6005_2agn_d_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x0082, 0x1304, iwl6005_2agn_mow1_cfg)पूर्ण,/* low 5GHz active */
	अणुIWL_PCI_DEVICE(0x0082, 0x1305, iwl6005_2agn_mow2_cfg)पूर्ण,/* high 5GHz active */

/* 6x30 Series */
	अणुIWL_PCI_DEVICE(0x008A, 0x5305, iwl1030_bgn_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x008A, 0x5307, iwl1030_bg_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x008A, 0x5325, iwl1030_bgn_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x008A, 0x5327, iwl1030_bg_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x008B, 0x5315, iwl1030_bgn_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x008B, 0x5317, iwl1030_bg_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x0090, 0x5211, iwl6030_2agn_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x0090, 0x5215, iwl6030_2bgn_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x0090, 0x5216, iwl6030_2abg_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x0091, 0x5201, iwl6030_2agn_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x0091, 0x5205, iwl6030_2bgn_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x0091, 0x5206, iwl6030_2abg_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x0091, 0x5207, iwl6030_2bg_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x0091, 0x5221, iwl6030_2agn_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x0091, 0x5225, iwl6030_2bgn_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x0091, 0x5226, iwl6030_2abg_cfg)पूर्ण,

/* 6x50 WiFi/WiMax Series */
	अणुIWL_PCI_DEVICE(0x0087, 0x1301, iwl6050_2agn_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x0087, 0x1306, iwl6050_2abg_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x0087, 0x1321, iwl6050_2agn_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x0087, 0x1326, iwl6050_2abg_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x0089, 0x1311, iwl6050_2agn_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x0089, 0x1316, iwl6050_2abg_cfg)पूर्ण,

/* 6150 WiFi/WiMax Series */
	अणुIWL_PCI_DEVICE(0x0885, 0x1305, iwl6150_bgn_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x0885, 0x1307, iwl6150_bg_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x0885, 0x1325, iwl6150_bgn_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x0885, 0x1327, iwl6150_bg_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x0886, 0x1315, iwl6150_bgn_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x0886, 0x1317, iwl6150_bg_cfg)पूर्ण,

/* 1000 Series WiFi */
	अणुIWL_PCI_DEVICE(0x0083, 0x1205, iwl1000_bgn_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x0083, 0x1305, iwl1000_bgn_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x0083, 0x1225, iwl1000_bgn_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x0083, 0x1325, iwl1000_bgn_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x0084, 0x1215, iwl1000_bgn_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x0084, 0x1315, iwl1000_bgn_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x0083, 0x1206, iwl1000_bg_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x0083, 0x1306, iwl1000_bg_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x0083, 0x1226, iwl1000_bg_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x0083, 0x1326, iwl1000_bg_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x0084, 0x1216, iwl1000_bg_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x0084, 0x1316, iwl1000_bg_cfg)पूर्ण,

/* 100 Series WiFi */
	अणुIWL_PCI_DEVICE(0x08AE, 0x1005, iwl100_bgn_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x08AE, 0x1007, iwl100_bg_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x08AF, 0x1015, iwl100_bgn_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x08AF, 0x1017, iwl100_bg_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x08AE, 0x1025, iwl100_bgn_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x08AE, 0x1027, iwl100_bg_cfg)पूर्ण,

/* 130 Series WiFi */
	अणुIWL_PCI_DEVICE(0x0896, 0x5005, iwl130_bgn_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x0896, 0x5007, iwl130_bg_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x0897, 0x5015, iwl130_bgn_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x0897, 0x5017, iwl130_bg_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x0896, 0x5025, iwl130_bgn_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x0896, 0x5027, iwl130_bg_cfg)पूर्ण,

/* 2x00 Series */
	अणुIWL_PCI_DEVICE(0x0890, 0x4022, iwl2000_2bgn_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x0891, 0x4222, iwl2000_2bgn_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x0890, 0x4422, iwl2000_2bgn_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x0890, 0x4822, iwl2000_2bgn_d_cfg)पूर्ण,

/* 2x30 Series */
	अणुIWL_PCI_DEVICE(0x0887, 0x4062, iwl2030_2bgn_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x0888, 0x4262, iwl2030_2bgn_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x0887, 0x4462, iwl2030_2bgn_cfg)पूर्ण,

/* 6x35 Series */
	अणुIWL_PCI_DEVICE(0x088E, 0x4060, iwl6035_2agn_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x088E, 0x406A, iwl6035_2agn_sff_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x088F, 0x4260, iwl6035_2agn_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x088F, 0x426A, iwl6035_2agn_sff_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x088E, 0x4460, iwl6035_2agn_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x088E, 0x446A, iwl6035_2agn_sff_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x088E, 0x4860, iwl6035_2agn_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x088F, 0x5260, iwl6035_2agn_cfg)पूर्ण,

/* 105 Series */
	अणुIWL_PCI_DEVICE(0x0894, 0x0022, iwl105_bgn_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x0895, 0x0222, iwl105_bgn_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x0894, 0x0422, iwl105_bgn_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x0894, 0x0822, iwl105_bgn_d_cfg)पूर्ण,

/* 135 Series */
	अणुIWL_PCI_DEVICE(0x0892, 0x0062, iwl135_bgn_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x0893, 0x0262, iwl135_bgn_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x0892, 0x0462, iwl135_bgn_cfg)पूर्ण,
#पूर्ण_अगर /* CONFIG_IWLDVM */

#अगर IS_ENABLED(CONFIG_IWLMVM)
/* 7260 Series */
	अणुIWL_PCI_DEVICE(0x08B1, 0x4070, iwl7260_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x08B1, 0x4072, iwl7260_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x08B1, 0x4170, iwl7260_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x08B1, 0x4C60, iwl7260_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x08B1, 0x4C70, iwl7260_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x08B1, 0x4060, iwl7260_2n_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x08B1, 0x406A, iwl7260_2n_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x08B1, 0x4160, iwl7260_2n_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x08B1, 0x4062, iwl7260_n_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x08B1, 0x4162, iwl7260_n_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x08B2, 0x4270, iwl7260_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x08B2, 0x4272, iwl7260_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x08B2, 0x4260, iwl7260_2n_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x08B2, 0x426A, iwl7260_2n_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x08B2, 0x4262, iwl7260_n_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x08B1, 0x4470, iwl7260_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x08B1, 0x4472, iwl7260_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x08B1, 0x4460, iwl7260_2n_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x08B1, 0x446A, iwl7260_2n_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x08B1, 0x4462, iwl7260_n_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x08B1, 0x4870, iwl7260_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x08B1, 0x486E, iwl7260_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x08B1, 0x4A70, iwl7260_2ac_cfg_high_temp)पूर्ण,
	अणुIWL_PCI_DEVICE(0x08B1, 0x4A6E, iwl7260_2ac_cfg_high_temp)पूर्ण,
	अणुIWL_PCI_DEVICE(0x08B1, 0x4A6C, iwl7260_2ac_cfg_high_temp)पूर्ण,
	अणुIWL_PCI_DEVICE(0x08B1, 0x4570, iwl7260_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x08B1, 0x4560, iwl7260_2n_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x08B2, 0x4370, iwl7260_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x08B2, 0x4360, iwl7260_2n_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x08B1, 0x5070, iwl7260_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x08B1, 0x5072, iwl7260_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x08B1, 0x5170, iwl7260_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x08B1, 0x5770, iwl7260_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x08B1, 0x4020, iwl7260_2n_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x08B1, 0x402A, iwl7260_2n_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x08B2, 0x4220, iwl7260_2n_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x08B1, 0x4420, iwl7260_2n_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x08B1, 0xC070, iwl7260_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x08B1, 0xC072, iwl7260_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x08B1, 0xC170, iwl7260_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x08B1, 0xC060, iwl7260_2n_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x08B1, 0xC06A, iwl7260_2n_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x08B1, 0xC160, iwl7260_2n_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x08B1, 0xC062, iwl7260_n_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x08B1, 0xC162, iwl7260_n_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x08B1, 0xC770, iwl7260_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x08B1, 0xC760, iwl7260_2n_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x08B2, 0xC270, iwl7260_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x08B1, 0xCC70, iwl7260_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x08B1, 0xCC60, iwl7260_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x08B2, 0xC272, iwl7260_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x08B2, 0xC260, iwl7260_2n_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x08B2, 0xC26A, iwl7260_n_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x08B2, 0xC262, iwl7260_n_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x08B1, 0xC470, iwl7260_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x08B1, 0xC472, iwl7260_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x08B1, 0xC460, iwl7260_2n_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x08B1, 0xC462, iwl7260_n_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x08B1, 0xC570, iwl7260_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x08B1, 0xC560, iwl7260_2n_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x08B2, 0xC370, iwl7260_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x08B1, 0xC360, iwl7260_2n_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x08B1, 0xC020, iwl7260_2n_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x08B1, 0xC02A, iwl7260_2n_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x08B2, 0xC220, iwl7260_2n_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x08B1, 0xC420, iwl7260_2n_cfg)पूर्ण,

/* 3160 Series */
	अणुIWL_PCI_DEVICE(0x08B3, 0x0070, iwl3160_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x08B3, 0x0072, iwl3160_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x08B3, 0x0170, iwl3160_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x08B3, 0x0172, iwl3160_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x08B3, 0x0060, iwl3160_2n_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x08B3, 0x0062, iwl3160_n_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x08B4, 0x0270, iwl3160_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x08B4, 0x0272, iwl3160_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x08B3, 0x0470, iwl3160_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x08B3, 0x0472, iwl3160_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x08B4, 0x0370, iwl3160_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x08B3, 0x8070, iwl3160_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x08B3, 0x8072, iwl3160_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x08B3, 0x8170, iwl3160_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x08B3, 0x8172, iwl3160_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x08B3, 0x8060, iwl3160_2n_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x08B3, 0x8062, iwl3160_n_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x08B4, 0x8270, iwl3160_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x08B4, 0x8370, iwl3160_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x08B4, 0x8272, iwl3160_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x08B3, 0x8470, iwl3160_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x08B3, 0x8570, iwl3160_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x08B3, 0x1070, iwl3160_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x08B3, 0x1170, iwl3160_2ac_cfg)पूर्ण,

/* 3165 Series */
	अणुIWL_PCI_DEVICE(0x3165, 0x4010, iwl3165_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x3165, 0x4012, iwl3165_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x3166, 0x4212, iwl3165_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x3165, 0x4410, iwl3165_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x3165, 0x4510, iwl3165_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x3165, 0x4110, iwl3165_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x3166, 0x4310, iwl3165_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x3166, 0x4210, iwl3165_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x3165, 0x8010, iwl3165_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x3165, 0x8110, iwl3165_2ac_cfg)पूर्ण,

/* 3168 Series */
	अणुIWL_PCI_DEVICE(0x24FB, 0x2010, iwl3168_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x24FB, 0x2110, iwl3168_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x24FB, 0x2050, iwl3168_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x24FB, 0x2150, iwl3168_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x24FB, 0x0000, iwl3168_2ac_cfg)पूर्ण,

/* 7265 Series */
	अणुIWL_PCI_DEVICE(0x095A, 0x5010, iwl7265_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x095A, 0x5110, iwl7265_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x095A, 0x5100, iwl7265_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x095B, 0x5310, iwl7265_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x095B, 0x5302, iwl7265_n_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x095B, 0x5210, iwl7265_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x095A, 0x5C10, iwl7265_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x095A, 0x5012, iwl7265_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x095A, 0x5412, iwl7265_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x095A, 0x5410, iwl7265_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x095A, 0x5510, iwl7265_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x095A, 0x5400, iwl7265_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x095A, 0x1010, iwl7265_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x095A, 0x5000, iwl7265_2n_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x095A, 0x500A, iwl7265_2n_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x095B, 0x5200, iwl7265_2n_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x095A, 0x5002, iwl7265_n_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x095A, 0x5102, iwl7265_n_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x095B, 0x5202, iwl7265_n_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x095A, 0x9010, iwl7265_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x095A, 0x9012, iwl7265_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x095A, 0x900A, iwl7265_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x095A, 0x9110, iwl7265_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x095A, 0x9112, iwl7265_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x095B, 0x9210, iwl7265_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x095B, 0x9200, iwl7265_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x095A, 0x9510, iwl7265_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x095B, 0x9310, iwl7265_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x095A, 0x9410, iwl7265_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x095A, 0x5020, iwl7265_2n_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x095A, 0x502A, iwl7265_2n_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x095A, 0x5420, iwl7265_2n_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x095A, 0x5090, iwl7265_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x095A, 0x5190, iwl7265_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x095A, 0x5590, iwl7265_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x095B, 0x5290, iwl7265_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x095A, 0x5490, iwl7265_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x095A, 0x5F10, iwl7265_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x095B, 0x5212, iwl7265_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x095B, 0x520A, iwl7265_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x095A, 0x9000, iwl7265_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x095A, 0x9400, iwl7265_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x095A, 0x9E10, iwl7265_2ac_cfg)पूर्ण,

/* 8000 Series */
	अणुIWL_PCI_DEVICE(0x24F3, 0x0010, iwl8260_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x24F3, 0x1010, iwl8260_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x24F3, 0x10B0, iwl8260_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x24F3, 0x0130, iwl8260_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x24F3, 0x1130, iwl8260_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x24F3, 0x0132, iwl8260_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x24F3, 0x1132, iwl8260_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x24F3, 0x0110, iwl8260_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x24F3, 0x01F0, iwl8260_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x24F3, 0x0012, iwl8260_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x24F3, 0x1012, iwl8260_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x24F3, 0x1110, iwl8260_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x24F3, 0x0050, iwl8260_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x24F3, 0x0250, iwl8260_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x24F3, 0x1050, iwl8260_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x24F3, 0x0150, iwl8260_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x24F3, 0x1150, iwl8260_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x24F4, 0x0030, iwl8260_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x24F4, 0x1030, iwl8260_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x24F3, 0xC010, iwl8260_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x24F3, 0xC110, iwl8260_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x24F3, 0xD010, iwl8260_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x24F3, 0xC050, iwl8260_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x24F3, 0xD050, iwl8260_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x24F3, 0xD0B0, iwl8260_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x24F3, 0xB0B0, iwl8260_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x24F3, 0x8010, iwl8260_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x24F3, 0x8110, iwl8260_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x24F3, 0x9010, iwl8260_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x24F3, 0x9110, iwl8260_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x24F4, 0x8030, iwl8260_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x24F4, 0x9030, iwl8260_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x24F4, 0xC030, iwl8260_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x24F4, 0xD030, iwl8260_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x24F3, 0x8130, iwl8260_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x24F3, 0x9130, iwl8260_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x24F3, 0x8132, iwl8260_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x24F3, 0x9132, iwl8260_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x24F3, 0x8050, iwl8260_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x24F3, 0x8150, iwl8260_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x24F3, 0x9050, iwl8260_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x24F3, 0x9150, iwl8260_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x24F3, 0x0004, iwl8260_2n_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x24F3, 0x0044, iwl8260_2n_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x24F5, 0x0010, iwl4165_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x24F6, 0x0030, iwl4165_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x24F3, 0x0810, iwl8260_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x24F3, 0x0910, iwl8260_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x24F3, 0x0850, iwl8260_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x24F3, 0x0950, iwl8260_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x24F3, 0x0930, iwl8260_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x24F3, 0x0000, iwl8265_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x24F3, 0x4010, iwl8260_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x24FD, 0x0010, iwl8265_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x24FD, 0x0110, iwl8265_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x24FD, 0x1110, iwl8265_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x24FD, 0x1130, iwl8265_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x24FD, 0x0130, iwl8265_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x24FD, 0x1010, iwl8265_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x24FD, 0x10D0, iwl8265_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x24FD, 0x0050, iwl8265_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x24FD, 0x0150, iwl8265_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x24FD, 0x9010, iwl8265_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x24FD, 0x8110, iwl8265_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x24FD, 0x8050, iwl8265_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x24FD, 0x8010, iwl8265_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x24FD, 0x0810, iwl8265_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x24FD, 0x9110, iwl8265_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x24FD, 0x8130, iwl8265_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x24FD, 0x0910, iwl8265_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x24FD, 0x0930, iwl8265_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x24FD, 0x0950, iwl8265_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x24FD, 0x0850, iwl8265_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x24FD, 0x1014, iwl8265_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x24FD, 0x3E02, iwl8275_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x24FD, 0x3E01, iwl8275_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x24FD, 0x1012, iwl8275_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x24FD, 0x0012, iwl8275_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x24FD, 0x0014, iwl8265_2ac_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x24FD, 0x9074, iwl8265_2ac_cfg)पूर्ण,

/* 9000 Series */
	अणुIWL_PCI_DEVICE(0x2526, PCI_ANY_ID, iwl9000_trans_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x271B, PCI_ANY_ID, iwl9000_trans_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x271C, PCI_ANY_ID, iwl9000_trans_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x30DC, PCI_ANY_ID, iwl9560_दीर्घ_latency_trans_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x31DC, PCI_ANY_ID, iwl9560_shared_clk_trans_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x9DF0, PCI_ANY_ID, iwl9560_trans_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0xA370, PCI_ANY_ID, iwl9560_trans_cfg)पूर्ण,

/* Qu devices */
	अणुIWL_PCI_DEVICE(0x02F0, PCI_ANY_ID, iwl_qu_trans_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x06F0, PCI_ANY_ID, iwl_qu_trans_cfg)पूर्ण,

	अणुIWL_PCI_DEVICE(0x34F0, PCI_ANY_ID, iwl_qu_medium_latency_trans_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x3DF0, PCI_ANY_ID, iwl_qu_medium_latency_trans_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x4DF0, PCI_ANY_ID, iwl_qu_medium_latency_trans_cfg)पूर्ण,

	अणुIWL_PCI_DEVICE(0x43F0, PCI_ANY_ID, iwl_qu_दीर्घ_latency_trans_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0xA0F0, PCI_ANY_ID, iwl_qu_दीर्घ_latency_trans_cfg)पूर्ण,

	अणुIWL_PCI_DEVICE(0x2720, PCI_ANY_ID, iwl_qnj_trans_cfg)पूर्ण,

	अणुIWL_PCI_DEVICE(0x2723, PCI_ANY_ID, iwl_ax200_trans_cfg)पूर्ण,

/* So devices */
	अणुIWL_PCI_DEVICE(0x2725, PCI_ANY_ID, iwl_so_trans_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x2726, PCI_ANY_ID, iwl_snj_trans_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x7A70, PCI_ANY_ID, iwl_so_दीर्घ_latency_trans_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x7AF0, PCI_ANY_ID, iwl_so_trans_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x51F0, PCI_ANY_ID, iwl_so_दीर्घ_latency_trans_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x54F0, PCI_ANY_ID, iwl_so_दीर्घ_latency_trans_cfg)पूर्ण,

/* Ma devices */
	अणुIWL_PCI_DEVICE(0x2729, PCI_ANY_ID, iwl_ma_trans_cfg)पूर्ण,
	अणुIWL_PCI_DEVICE(0x7E40, PCI_ANY_ID, iwl_ma_trans_cfg)पूर्ण,

/* Bz devices */
	अणुIWL_PCI_DEVICE(0x2727, PCI_ANY_ID, iwl_bz_trans_cfg)पूर्ण,
#पूर्ण_अगर /* CONFIG_IWLMVM */

	अणु0पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, iwl_hw_card_ids);

#घोषणा _IWL_DEV_INFO(_device, _subdevice, _mac_type, _mac_step, _rf_type, \
		      _rf_id, _no_160, _cores, _cdb, _cfg, _name)		   \
	अणु .device = (_device), .subdevice = (_subdevice), .cfg = &(_cfg),  \
	  .name = _name, .mac_type = _mac_type, .rf_type = _rf_type,	   \
	  .no_160 = _no_160, .cores = _cores, .rf_id = _rf_id,		   \
	  .mac_step = _mac_step, .cdb = _cdb पूर्ण

#घोषणा IWL_DEV_INFO(_device, _subdevice, _cfg, _name) \
	_IWL_DEV_INFO(_device, _subdevice, IWL_CFG_ANY, IWL_CFG_ANY,	   \
		      IWL_CFG_ANY, IWL_CFG_ANY, IWL_CFG_ANY, IWL_CFG_ANY,  \
		      IWL_CFG_NO_CDB, _cfg, _name)

अटल स्थिर काष्ठा iwl_dev_info iwl_dev_info_table[] = अणु
#अगर IS_ENABLED(CONFIG_IWLMVM)
/* 9000 */
	IWL_DEV_INFO(0x2526, 0x1550, iwl9260_2ac_cfg, iwl9260_समाप्तer_1550_name),
	IWL_DEV_INFO(0x2526, 0x1551, iwl9560_2ac_cfg_soc, iwl9560_समाप्तer_1550s_name),
	IWL_DEV_INFO(0x2526, 0x1552, iwl9560_2ac_cfg_soc, iwl9560_समाप्तer_1550i_name),
	IWL_DEV_INFO(0x30DC, 0x1551, iwl9560_2ac_cfg_soc, iwl9560_समाप्तer_1550s_name),
	IWL_DEV_INFO(0x30DC, 0x1552, iwl9560_2ac_cfg_soc, iwl9560_समाप्तer_1550i_name),
	IWL_DEV_INFO(0x31DC, 0x1551, iwl9560_2ac_cfg_soc, iwl9560_समाप्तer_1550s_name),
	IWL_DEV_INFO(0x31DC, 0x1552, iwl9560_2ac_cfg_soc, iwl9560_समाप्तer_1550i_name),
	IWL_DEV_INFO(0xA370, 0x1551, iwl9560_2ac_cfg_soc, iwl9560_समाप्तer_1550s_name),
	IWL_DEV_INFO(0xA370, 0x1552, iwl9560_2ac_cfg_soc, iwl9560_समाप्तer_1550i_name),

	IWL_DEV_INFO(0x271C, 0x0214, iwl9260_2ac_cfg, iwl9260_1_name),

/* AX200 */
	IWL_DEV_INFO(0x2723, 0x1653, iwl_ax200_cfg_cc, iwl_ax200_समाप्तer_1650w_name),
	IWL_DEV_INFO(0x2723, 0x1654, iwl_ax200_cfg_cc, iwl_ax200_समाप्तer_1650x_name),
	IWL_DEV_INFO(0x2723, IWL_CFG_ANY, iwl_ax200_cfg_cc, iwl_ax200_name),

	/* Qu with Hr */
	IWL_DEV_INFO(0x43F0, 0x0070, iwl_ax201_cfg_qu_hr, शून्य),
	IWL_DEV_INFO(0x43F0, 0x0074, iwl_ax201_cfg_qu_hr, शून्य),
	IWL_DEV_INFO(0x43F0, 0x0078, iwl_ax201_cfg_qu_hr, शून्य),
	IWL_DEV_INFO(0x43F0, 0x007C, iwl_ax201_cfg_qu_hr, शून्य),
	IWL_DEV_INFO(0x43F0, 0x2074, iwl_ax201_cfg_qu_hr, शून्य),
	IWL_DEV_INFO(0x43F0, 0x4070, iwl_ax201_cfg_qu_hr, शून्य),
	IWL_DEV_INFO(0xA0F0, 0x0070, iwl_ax201_cfg_qu_hr, शून्य),
	IWL_DEV_INFO(0xA0F0, 0x0074, iwl_ax201_cfg_qu_hr, शून्य),
	IWL_DEV_INFO(0xA0F0, 0x0078, iwl_ax201_cfg_qu_hr, शून्य),
	IWL_DEV_INFO(0xA0F0, 0x007C, iwl_ax201_cfg_qu_hr, शून्य),
	IWL_DEV_INFO(0xA0F0, 0x0A10, iwl_ax201_cfg_qu_hr, शून्य),
	IWL_DEV_INFO(0xA0F0, 0x1651, समाप्तer1650s_2ax_cfg_qu_b0_hr_b0, शून्य),
	IWL_DEV_INFO(0xA0F0, 0x1652, समाप्तer1650i_2ax_cfg_qu_b0_hr_b0, शून्य),
	IWL_DEV_INFO(0xA0F0, 0x2074, iwl_ax201_cfg_qu_hr, शून्य),
	IWL_DEV_INFO(0xA0F0, 0x4070, iwl_ax201_cfg_qu_hr, शून्य),
	IWL_DEV_INFO(0x02F0, 0x0070, iwl_ax201_cfg_quz_hr, शून्य),
	IWL_DEV_INFO(0x02F0, 0x0074, iwl_ax201_cfg_quz_hr, शून्य),
	IWL_DEV_INFO(0x02F0, 0x6074, iwl_ax201_cfg_quz_hr, शून्य),
	IWL_DEV_INFO(0x02F0, 0x0078, iwl_ax201_cfg_quz_hr, शून्य),
	IWL_DEV_INFO(0x02F0, 0x007C, iwl_ax201_cfg_quz_hr, शून्य),
	IWL_DEV_INFO(0x02F0, 0x0310, iwl_ax201_cfg_quz_hr, शून्य),
	IWL_DEV_INFO(0x02F0, 0x1651, iwl_ax1650s_cfg_quz_hr, शून्य),
	IWL_DEV_INFO(0x02F0, 0x1652, iwl_ax1650i_cfg_quz_hr, शून्य),
	IWL_DEV_INFO(0x02F0, 0x2074, iwl_ax201_cfg_quz_hr, शून्य),
	IWL_DEV_INFO(0x02F0, 0x4070, iwl_ax201_cfg_quz_hr, शून्य),
	IWL_DEV_INFO(0x06F0, 0x0070, iwl_ax201_cfg_quz_hr, शून्य),
	IWL_DEV_INFO(0x06F0, 0x0074, iwl_ax201_cfg_quz_hr, शून्य),
	IWL_DEV_INFO(0x06F0, 0x0078, iwl_ax201_cfg_quz_hr, शून्य),
	IWL_DEV_INFO(0x06F0, 0x007C, iwl_ax201_cfg_quz_hr, शून्य),
	IWL_DEV_INFO(0x06F0, 0x0310, iwl_ax201_cfg_quz_hr, शून्य),
	IWL_DEV_INFO(0x06F0, 0x1651, iwl_ax1650s_cfg_quz_hr, शून्य),
	IWL_DEV_INFO(0x06F0, 0x1652, iwl_ax1650i_cfg_quz_hr, शून्य),
	IWL_DEV_INFO(0x06F0, 0x2074, iwl_ax201_cfg_quz_hr, शून्य),
	IWL_DEV_INFO(0x06F0, 0x4070, iwl_ax201_cfg_quz_hr, शून्य),
	IWL_DEV_INFO(0x34F0, 0x0070, iwl_ax201_cfg_qu_hr, शून्य),
	IWL_DEV_INFO(0x34F0, 0x0074, iwl_ax201_cfg_qu_hr, शून्य),
	IWL_DEV_INFO(0x34F0, 0x0078, iwl_ax201_cfg_qu_hr, शून्य),
	IWL_DEV_INFO(0x34F0, 0x007C, iwl_ax201_cfg_qu_hr, शून्य),
	IWL_DEV_INFO(0x34F0, 0x0310, iwl_ax201_cfg_qu_hr, शून्य),
	IWL_DEV_INFO(0x34F0, 0x1651, समाप्तer1650s_2ax_cfg_qu_b0_hr_b0, शून्य),
	IWL_DEV_INFO(0x34F0, 0x1652, समाप्तer1650i_2ax_cfg_qu_b0_hr_b0, शून्य),
	IWL_DEV_INFO(0x34F0, 0x2074, iwl_ax201_cfg_qu_hr, शून्य),
	IWL_DEV_INFO(0x34F0, 0x4070, iwl_ax201_cfg_qu_hr, शून्य),

	IWL_DEV_INFO(0x3DF0, 0x0070, iwl_ax201_cfg_qu_hr, शून्य),
	IWL_DEV_INFO(0x3DF0, 0x0074, iwl_ax201_cfg_qu_hr, शून्य),
	IWL_DEV_INFO(0x3DF0, 0x0078, iwl_ax201_cfg_qu_hr, शून्य),
	IWL_DEV_INFO(0x3DF0, 0x007C, iwl_ax201_cfg_qu_hr, शून्य),
	IWL_DEV_INFO(0x3DF0, 0x0310, iwl_ax201_cfg_qu_hr, शून्य),
	IWL_DEV_INFO(0x3DF0, 0x1651, समाप्तer1650s_2ax_cfg_qu_b0_hr_b0, शून्य),
	IWL_DEV_INFO(0x3DF0, 0x1652, समाप्तer1650i_2ax_cfg_qu_b0_hr_b0, शून्य),
	IWL_DEV_INFO(0x3DF0, 0x2074, iwl_ax201_cfg_qu_hr, शून्य),
	IWL_DEV_INFO(0x3DF0, 0x4070, iwl_ax201_cfg_qu_hr, शून्य),

	IWL_DEV_INFO(0x4DF0, 0x0070, iwl_ax201_cfg_qu_hr, शून्य),
	IWL_DEV_INFO(0x4DF0, 0x0074, iwl_ax201_cfg_qu_hr, शून्य),
	IWL_DEV_INFO(0x4DF0, 0x0078, iwl_ax201_cfg_qu_hr, शून्य),
	IWL_DEV_INFO(0x4DF0, 0x007C, iwl_ax201_cfg_qu_hr, शून्य),
	IWL_DEV_INFO(0x4DF0, 0x0310, iwl_ax201_cfg_qu_hr, शून्य),
	IWL_DEV_INFO(0x4DF0, 0x1651, समाप्तer1650s_2ax_cfg_qu_b0_hr_b0, शून्य),
	IWL_DEV_INFO(0x4DF0, 0x1652, समाप्तer1650i_2ax_cfg_qu_b0_hr_b0, शून्य),
	IWL_DEV_INFO(0x4DF0, 0x2074, iwl_ax201_cfg_qu_hr, शून्य),
	IWL_DEV_INFO(0x4DF0, 0x4070, iwl_ax201_cfg_qu_hr, शून्य),
	IWL_DEV_INFO(0x4DF0, 0x6074, iwl_ax201_cfg_qu_hr, शून्य),

	/* So with HR */
	IWL_DEV_INFO(0x2725, 0x0090, iwlax211_2ax_cfg_so_gf_a0, शून्य),
	IWL_DEV_INFO(0x2725, 0x0020, iwlax210_2ax_cfg_ty_gf_a0, शून्य),
	IWL_DEV_INFO(0x2725, 0x2020, iwlax210_2ax_cfg_ty_gf_a0, शून्य),
	IWL_DEV_INFO(0x2725, 0x0024, iwlax210_2ax_cfg_ty_gf_a0, शून्य),
	IWL_DEV_INFO(0x2725, 0x0310, iwlax210_2ax_cfg_ty_gf_a0, शून्य),
	IWL_DEV_INFO(0x2725, 0x0510, iwlax210_2ax_cfg_ty_gf_a0, शून्य),
	IWL_DEV_INFO(0x2725, 0x0A10, iwlax210_2ax_cfg_ty_gf_a0, शून्य),
	IWL_DEV_INFO(0x2725, 0xE020, iwlax210_2ax_cfg_ty_gf_a0, शून्य),
	IWL_DEV_INFO(0x2725, 0xE024, iwlax210_2ax_cfg_ty_gf_a0, शून्य),
	IWL_DEV_INFO(0x2725, 0x4020, iwlax210_2ax_cfg_ty_gf_a0, शून्य),
	IWL_DEV_INFO(0x2725, 0x6020, iwlax210_2ax_cfg_ty_gf_a0, शून्य),
	IWL_DEV_INFO(0x2725, 0x6024, iwlax210_2ax_cfg_ty_gf_a0, शून्य),
	IWL_DEV_INFO(0x2725, 0x1673, iwlax210_2ax_cfg_ty_gf_a0, iwl_ax210_समाप्तer_1675w_name),
	IWL_DEV_INFO(0x2725, 0x1674, iwlax210_2ax_cfg_ty_gf_a0, iwl_ax210_समाप्तer_1675x_name),
	IWL_DEV_INFO(0x7A70, 0x0090, iwlax211_2ax_cfg_so_gf_a0_दीर्घ, शून्य),
	IWL_DEV_INFO(0x7A70, 0x0098, iwlax211_2ax_cfg_so_gf_a0_दीर्घ, शून्य),
	IWL_DEV_INFO(0x7A70, 0x00B0, iwlax411_2ax_cfg_so_gf4_a0_दीर्घ, शून्य),
	IWL_DEV_INFO(0x7A70, 0x0310, iwlax211_2ax_cfg_so_gf_a0_दीर्घ, शून्य),
	IWL_DEV_INFO(0x7A70, 0x0510, iwlax211_2ax_cfg_so_gf_a0_दीर्घ, शून्य),
	IWL_DEV_INFO(0x7A70, 0x0A10, iwlax211_2ax_cfg_so_gf_a0_दीर्घ, शून्य),
	IWL_DEV_INFO(0x7AF0, 0x0090, iwlax211_2ax_cfg_so_gf_a0, शून्य),
	IWL_DEV_INFO(0x7AF0, 0x0098, iwlax211_2ax_cfg_so_gf_a0, शून्य),
	IWL_DEV_INFO(0x7AF0, 0x00B0, iwlax411_2ax_cfg_so_gf4_a0, शून्य),
	IWL_DEV_INFO(0x7AF0, 0x0310, iwlax211_2ax_cfg_so_gf_a0, शून्य),
	IWL_DEV_INFO(0x7AF0, 0x0510, iwlax211_2ax_cfg_so_gf_a0, शून्य),
	IWL_DEV_INFO(0x7AF0, 0x0A10, iwlax211_2ax_cfg_so_gf_a0, शून्य),

	/* SnJ with HR */
	IWL_DEV_INFO(0x2725, 0x00B0, iwlax411_2ax_cfg_sosnj_gf4_a0, शून्य),
	IWL_DEV_INFO(0x2726, 0x0090, iwlax211_cfg_snj_gf_a0, शून्य),
	IWL_DEV_INFO(0x2726, 0x0098, iwlax211_cfg_snj_gf_a0, शून्य),
	IWL_DEV_INFO(0x2726, 0x00B0, iwlax411_2ax_cfg_sosnj_gf4_a0, शून्य),
	IWL_DEV_INFO(0x2726, 0x00B4, iwlax411_2ax_cfg_sosnj_gf4_a0, शून्य),
	IWL_DEV_INFO(0x2726, 0x0510, iwlax211_cfg_snj_gf_a0, शून्य),
	IWL_DEV_INFO(0x2726, 0x1651, iwl_cfg_snj_hr_b0, iwl_ax201_समाप्तer_1650s_name),
	IWL_DEV_INFO(0x2726, 0x1652, iwl_cfg_snj_hr_b0, iwl_ax201_समाप्तer_1650i_name),

	_IWL_DEV_INFO(IWL_CFG_ANY, IWL_CFG_ANY,
		      IWL_CFG_MAC_TYPE_PU, IWL_CFG_ANY,
		      IWL_CFG_RF_TYPE_JF1, IWL_CFG_RF_ID_JF1,
		      IWL_CFG_160, IWL_CFG_CORES_BT, IWL_CFG_NO_CDB,
		      iwl9560_2ac_cfg_soc, iwl9461_160_name),
	_IWL_DEV_INFO(IWL_CFG_ANY, IWL_CFG_ANY,
		      IWL_CFG_MAC_TYPE_PU, IWL_CFG_ANY,
		      IWL_CFG_RF_TYPE_JF1, IWL_CFG_RF_ID_JF1,
		      IWL_CFG_NO_160, IWL_CFG_CORES_BT, IWL_CFG_NO_CDB,
		      iwl9560_2ac_cfg_soc, iwl9461_name),
	_IWL_DEV_INFO(IWL_CFG_ANY, IWL_CFG_ANY,
		      IWL_CFG_MAC_TYPE_PU, IWL_CFG_ANY,
		      IWL_CFG_RF_TYPE_JF1, IWL_CFG_RF_ID_JF1_DIV,
		      IWL_CFG_160, IWL_CFG_CORES_BT, IWL_CFG_NO_CDB,
		      iwl9560_2ac_cfg_soc, iwl9462_160_name),
	_IWL_DEV_INFO(IWL_CFG_ANY, IWL_CFG_ANY,
		      IWL_CFG_MAC_TYPE_PU, IWL_CFG_ANY,
		      IWL_CFG_RF_TYPE_JF1, IWL_CFG_RF_ID_JF1_DIV,
		      IWL_CFG_NO_160, IWL_CFG_CORES_BT, IWL_CFG_NO_CDB,
		      iwl9560_2ac_cfg_soc, iwl9462_name),

	_IWL_DEV_INFO(IWL_CFG_ANY, IWL_CFG_ANY,
		      IWL_CFG_MAC_TYPE_PU, IWL_CFG_ANY,
		      IWL_CFG_RF_TYPE_JF2, IWL_CFG_RF_ID_JF,
		      IWL_CFG_160, IWL_CFG_CORES_BT, IWL_CFG_NO_CDB,
		      iwl9560_2ac_cfg_soc, iwl9560_160_name),
	_IWL_DEV_INFO(IWL_CFG_ANY, IWL_CFG_ANY,
		      IWL_CFG_MAC_TYPE_PU, IWL_CFG_ANY,
		      IWL_CFG_RF_TYPE_JF2, IWL_CFG_RF_ID_JF,
		      IWL_CFG_NO_160, IWL_CFG_CORES_BT, IWL_CFG_NO_CDB,
		      iwl9560_2ac_cfg_soc, iwl9560_name),

	_IWL_DEV_INFO(0x2526, IWL_CFG_ANY,
		      IWL_CFG_MAC_TYPE_PNJ, IWL_CFG_ANY,
		      IWL_CFG_RF_TYPE_JF1, IWL_CFG_RF_ID_JF1,
		      IWL_CFG_160, IWL_CFG_CORES_BT, IWL_CFG_NO_CDB,
		      iwl9260_2ac_cfg, iwl9461_160_name),
	_IWL_DEV_INFO(0x2526, IWL_CFG_ANY,
		      IWL_CFG_MAC_TYPE_PNJ, IWL_CFG_ANY,
		      IWL_CFG_RF_TYPE_JF1, IWL_CFG_RF_ID_JF1,
		      IWL_CFG_NO_160, IWL_CFG_CORES_BT, IWL_CFG_NO_CDB,
		      iwl9260_2ac_cfg, iwl9461_name),
	_IWL_DEV_INFO(0x2526, IWL_CFG_ANY,
		      IWL_CFG_MAC_TYPE_PNJ, IWL_CFG_ANY,
		      IWL_CFG_RF_TYPE_JF1, IWL_CFG_RF_ID_JF1_DIV,
		      IWL_CFG_160, IWL_CFG_CORES_BT, IWL_CFG_NO_CDB,
		      iwl9260_2ac_cfg, iwl9462_160_name),
	_IWL_DEV_INFO(0x2526, IWL_CFG_ANY,
		      IWL_CFG_MAC_TYPE_PNJ, IWL_CFG_ANY,
		      IWL_CFG_RF_TYPE_JF1, IWL_CFG_RF_ID_JF1_DIV,
		      IWL_CFG_NO_160, IWL_CFG_CORES_BT, IWL_CFG_NO_CDB,
		      iwl9260_2ac_cfg, iwl9462_name),

	_IWL_DEV_INFO(0x2526, IWL_CFG_ANY,
		      IWL_CFG_MAC_TYPE_PNJ, IWL_CFG_ANY,
		      IWL_CFG_RF_TYPE_JF2, IWL_CFG_RF_ID_JF,
		      IWL_CFG_160, IWL_CFG_CORES_BT, IWL_CFG_NO_CDB,
		      iwl9260_2ac_cfg, iwl9560_160_name),
	_IWL_DEV_INFO(0x2526, IWL_CFG_ANY,
		      IWL_CFG_MAC_TYPE_PNJ, IWL_CFG_ANY,
		      IWL_CFG_RF_TYPE_JF2, IWL_CFG_RF_ID_JF,
		      IWL_CFG_NO_160, IWL_CFG_CORES_BT, IWL_CFG_NO_CDB,
		      iwl9260_2ac_cfg, iwl9560_name),

	_IWL_DEV_INFO(0x2526, IWL_CFG_ANY,
		      IWL_CFG_MAC_TYPE_TH, IWL_CFG_ANY,
		      IWL_CFG_RF_TYPE_TH, IWL_CFG_ANY,
		      IWL_CFG_160, IWL_CFG_CORES_BT_GNSS, IWL_CFG_NO_CDB,
		      iwl9260_2ac_cfg, iwl9270_160_name),
	_IWL_DEV_INFO(0x2526, IWL_CFG_ANY,
		      IWL_CFG_MAC_TYPE_TH, IWL_CFG_ANY,
		      IWL_CFG_RF_TYPE_TH, IWL_CFG_ANY,
		      IWL_CFG_NO_160, IWL_CFG_CORES_BT_GNSS, IWL_CFG_NO_CDB,
		      iwl9260_2ac_cfg, iwl9270_name),

	_IWL_DEV_INFO(0x271B, IWL_CFG_ANY,
		      IWL_CFG_MAC_TYPE_TH, IWL_CFG_ANY,
		      IWL_CFG_RF_TYPE_TH1, IWL_CFG_ANY,
		      IWL_CFG_160, IWL_CFG_CORES_BT, IWL_CFG_NO_CDB,
		      iwl9260_2ac_cfg, iwl9162_160_name),
	_IWL_DEV_INFO(0x271B, IWL_CFG_ANY,
		      IWL_CFG_MAC_TYPE_TH, IWL_CFG_ANY,
		      IWL_CFG_RF_TYPE_TH1, IWL_CFG_ANY,
		      IWL_CFG_NO_160, IWL_CFG_CORES_BT, IWL_CFG_NO_CDB,
		      iwl9260_2ac_cfg, iwl9162_name),

	_IWL_DEV_INFO(0x2526, IWL_CFG_ANY,
		      IWL_CFG_MAC_TYPE_TH, IWL_CFG_ANY,
		      IWL_CFG_RF_TYPE_TH, IWL_CFG_ANY,
		      IWL_CFG_160, IWL_CFG_CORES_BT, IWL_CFG_NO_CDB,
		      iwl9260_2ac_cfg, iwl9260_160_name),
	_IWL_DEV_INFO(0x2526, IWL_CFG_ANY,
		      IWL_CFG_MAC_TYPE_TH, IWL_CFG_ANY,
		      IWL_CFG_RF_TYPE_TH, IWL_CFG_ANY,
		      IWL_CFG_NO_160, IWL_CFG_CORES_BT, IWL_CFG_NO_CDB,
		      iwl9260_2ac_cfg, iwl9260_name),

/* Qu with Jf */
	/* Qu B step */
	_IWL_DEV_INFO(IWL_CFG_ANY, IWL_CFG_ANY,
		      IWL_CFG_MAC_TYPE_QU, SILICON_B_STEP,
		      IWL_CFG_RF_TYPE_JF1, IWL_CFG_RF_ID_JF1,
		      IWL_CFG_160, IWL_CFG_CORES_BT, IWL_CFG_NO_CDB,
		      iwl9560_qu_b0_jf_b0_cfg, iwl9461_160_name),
	_IWL_DEV_INFO(IWL_CFG_ANY, IWL_CFG_ANY,
		      IWL_CFG_MAC_TYPE_QU, SILICON_B_STEP,
		      IWL_CFG_RF_TYPE_JF1, IWL_CFG_RF_ID_JF1,
		      IWL_CFG_NO_160, IWL_CFG_CORES_BT, IWL_CFG_NO_CDB,
		      iwl9560_qu_b0_jf_b0_cfg, iwl9461_name),
	_IWL_DEV_INFO(IWL_CFG_ANY, IWL_CFG_ANY,
		      IWL_CFG_MAC_TYPE_QU, SILICON_B_STEP,
		      IWL_CFG_RF_TYPE_JF1, IWL_CFG_RF_ID_JF1_DIV,
		      IWL_CFG_160, IWL_CFG_CORES_BT, IWL_CFG_NO_CDB,
		      iwl9560_qu_b0_jf_b0_cfg, iwl9462_160_name),
	_IWL_DEV_INFO(IWL_CFG_ANY, IWL_CFG_ANY,
		      IWL_CFG_MAC_TYPE_QU, SILICON_B_STEP,
		      IWL_CFG_RF_TYPE_JF1, IWL_CFG_RF_ID_JF1_DIV,
		      IWL_CFG_NO_160, IWL_CFG_CORES_BT, IWL_CFG_NO_CDB,
		      iwl9560_qu_b0_jf_b0_cfg, iwl9462_name),

	_IWL_DEV_INFO(IWL_CFG_ANY, IWL_CFG_ANY,
		      IWL_CFG_MAC_TYPE_QU, SILICON_B_STEP,
		      IWL_CFG_RF_TYPE_JF2, IWL_CFG_RF_ID_JF,
		      IWL_CFG_160, IWL_CFG_CORES_BT, IWL_CFG_NO_CDB,
		      iwl9560_qu_b0_jf_b0_cfg, iwl9560_160_name),
	_IWL_DEV_INFO(IWL_CFG_ANY, IWL_CFG_ANY,
		      IWL_CFG_MAC_TYPE_QU, SILICON_B_STEP,
		      IWL_CFG_RF_TYPE_JF2, IWL_CFG_RF_ID_JF,
		      IWL_CFG_NO_160, IWL_CFG_CORES_BT, IWL_CFG_NO_CDB,
		      iwl9560_qu_b0_jf_b0_cfg, iwl9560_name),

	_IWL_DEV_INFO(IWL_CFG_ANY, 0x1551,
		      IWL_CFG_MAC_TYPE_QU, SILICON_B_STEP,
		      IWL_CFG_RF_TYPE_JF2, IWL_CFG_RF_ID_JF,
		      IWL_CFG_NO_160, IWL_CFG_CORES_BT, IWL_CFG_NO_CDB,
		      iwl9560_qu_b0_jf_b0_cfg, iwl9560_समाप्तer_1550s_name),
	_IWL_DEV_INFO(IWL_CFG_ANY, 0x1552,
		      IWL_CFG_MAC_TYPE_QU, SILICON_B_STEP,
		      IWL_CFG_RF_TYPE_JF2, IWL_CFG_RF_ID_JF,
		      IWL_CFG_NO_160, IWL_CFG_CORES_BT, IWL_CFG_NO_CDB,
		      iwl9560_qu_b0_jf_b0_cfg, iwl9560_समाप्तer_1550i_name),

	/* Qu C step */
	_IWL_DEV_INFO(IWL_CFG_ANY, IWL_CFG_ANY,
		      IWL_CFG_MAC_TYPE_QU, SILICON_C_STEP,
		      IWL_CFG_RF_TYPE_JF1, IWL_CFG_RF_ID_JF1,
		      IWL_CFG_160, IWL_CFG_CORES_BT, IWL_CFG_NO_CDB,
		      iwl9560_qu_c0_jf_b0_cfg, iwl9461_160_name),
	_IWL_DEV_INFO(IWL_CFG_ANY, IWL_CFG_ANY,
		      IWL_CFG_MAC_TYPE_QU, SILICON_C_STEP,
		      IWL_CFG_RF_TYPE_JF1, IWL_CFG_RF_ID_JF1,
		      IWL_CFG_NO_160, IWL_CFG_CORES_BT, IWL_CFG_NO_CDB,
		      iwl9560_qu_c0_jf_b0_cfg, iwl9461_name),
	_IWL_DEV_INFO(IWL_CFG_ANY, IWL_CFG_ANY,
		      IWL_CFG_MAC_TYPE_QU, SILICON_C_STEP,
		      IWL_CFG_RF_TYPE_JF1, IWL_CFG_RF_ID_JF1_DIV,
		      IWL_CFG_160, IWL_CFG_CORES_BT, IWL_CFG_NO_CDB,
		      iwl9560_qu_c0_jf_b0_cfg, iwl9462_160_name),
	_IWL_DEV_INFO(IWL_CFG_ANY, IWL_CFG_ANY,
		      IWL_CFG_MAC_TYPE_QU, SILICON_C_STEP,
		      IWL_CFG_RF_TYPE_JF1, IWL_CFG_RF_ID_JF1_DIV,
		      IWL_CFG_NO_160, IWL_CFG_CORES_BT, IWL_CFG_NO_CDB,
		      iwl9560_qu_c0_jf_b0_cfg, iwl9462_name),

	_IWL_DEV_INFO(IWL_CFG_ANY, IWL_CFG_ANY,
		      IWL_CFG_MAC_TYPE_QU, SILICON_C_STEP,
		      IWL_CFG_RF_TYPE_JF2, IWL_CFG_RF_ID_JF,
		      IWL_CFG_160, IWL_CFG_CORES_BT, IWL_CFG_NO_CDB,
		      iwl9560_qu_c0_jf_b0_cfg, iwl9560_160_name),
	_IWL_DEV_INFO(IWL_CFG_ANY, IWL_CFG_ANY,
		      IWL_CFG_MAC_TYPE_QU, SILICON_C_STEP,
		      IWL_CFG_RF_TYPE_JF2, IWL_CFG_RF_ID_JF,
		      IWL_CFG_NO_160, IWL_CFG_CORES_BT, IWL_CFG_NO_CDB,
		      iwl9560_qu_c0_jf_b0_cfg, iwl9560_name),

	_IWL_DEV_INFO(IWL_CFG_ANY, 0x1551,
		      IWL_CFG_MAC_TYPE_QU, SILICON_C_STEP,
		      IWL_CFG_RF_TYPE_JF2, IWL_CFG_RF_ID_JF,
		      IWL_CFG_160, IWL_CFG_CORES_BT, IWL_CFG_NO_CDB,
		      iwl9560_qu_c0_jf_b0_cfg, iwl9560_समाप्तer_1550s_name),
	_IWL_DEV_INFO(IWL_CFG_ANY, 0x1552,
		      IWL_CFG_MAC_TYPE_QU, SILICON_C_STEP,
		      IWL_CFG_RF_TYPE_JF2, IWL_CFG_RF_ID_JF,
		      IWL_CFG_NO_160, IWL_CFG_CORES_BT, IWL_CFG_NO_CDB,
		      iwl9560_qu_c0_jf_b0_cfg, iwl9560_समाप्तer_1550i_name),

	/* QuZ */
	_IWL_DEV_INFO(IWL_CFG_ANY, IWL_CFG_ANY,
		      IWL_CFG_MAC_TYPE_QUZ, IWL_CFG_ANY,
		      IWL_CFG_RF_TYPE_JF1, IWL_CFG_RF_ID_JF1,
		      IWL_CFG_160, IWL_CFG_CORES_BT, IWL_CFG_NO_CDB,
		      iwl9560_quz_a0_jf_b0_cfg, iwl9461_160_name),
	_IWL_DEV_INFO(IWL_CFG_ANY, IWL_CFG_ANY,
		      IWL_CFG_MAC_TYPE_QUZ, IWL_CFG_ANY,
		      IWL_CFG_RF_TYPE_JF1, IWL_CFG_RF_ID_JF1,
		      IWL_CFG_NO_160, IWL_CFG_CORES_BT, IWL_CFG_NO_CDB,
		      iwl9560_quz_a0_jf_b0_cfg, iwl9461_name),
	_IWL_DEV_INFO(IWL_CFG_ANY, IWL_CFG_ANY,
		      IWL_CFG_MAC_TYPE_QUZ, IWL_CFG_ANY,
		      IWL_CFG_RF_TYPE_JF1, IWL_CFG_RF_ID_JF1_DIV,
		      IWL_CFG_160, IWL_CFG_CORES_BT, IWL_CFG_NO_CDB,
		      iwl9560_quz_a0_jf_b0_cfg, iwl9462_160_name),
	_IWL_DEV_INFO(IWL_CFG_ANY, IWL_CFG_ANY,
		      IWL_CFG_MAC_TYPE_QUZ, IWL_CFG_ANY,
		      IWL_CFG_RF_TYPE_JF1, IWL_CFG_RF_ID_JF1_DIV,
		      IWL_CFG_NO_160, IWL_CFG_CORES_BT, IWL_CFG_NO_CDB,
		      iwl9560_quz_a0_jf_b0_cfg, iwl9462_name),

	_IWL_DEV_INFO(IWL_CFG_ANY, IWL_CFG_ANY,
		      IWL_CFG_MAC_TYPE_QUZ, IWL_CFG_ANY,
		      IWL_CFG_RF_TYPE_JF2, IWL_CFG_RF_ID_JF,
		      IWL_CFG_160, IWL_CFG_CORES_BT, IWL_CFG_NO_CDB,
		      iwl9560_quz_a0_jf_b0_cfg, iwl9560_160_name),
	_IWL_DEV_INFO(IWL_CFG_ANY, IWL_CFG_ANY,
		      IWL_CFG_MAC_TYPE_QUZ, IWL_CFG_ANY,
		      IWL_CFG_RF_TYPE_JF2, IWL_CFG_RF_ID_JF,
		      IWL_CFG_NO_160, IWL_CFG_CORES_BT, IWL_CFG_NO_CDB,
		      iwl9560_quz_a0_jf_b0_cfg, iwl9560_name),

	_IWL_DEV_INFO(IWL_CFG_ANY, 0x1551,
		      IWL_CFG_MAC_TYPE_QUZ, IWL_CFG_ANY,
		      IWL_CFG_RF_TYPE_JF2, IWL_CFG_RF_ID_JF,
		      IWL_CFG_160, IWL_CFG_CORES_BT, IWL_CFG_NO_CDB,
		      iwl9560_quz_a0_jf_b0_cfg, iwl9560_समाप्तer_1550s_name),
	_IWL_DEV_INFO(IWL_CFG_ANY, 0x1552,
		      IWL_CFG_MAC_TYPE_QUZ, IWL_CFG_ANY,
		      IWL_CFG_RF_TYPE_JF2, IWL_CFG_RF_ID_JF,
		      IWL_CFG_NO_160, IWL_CFG_CORES_BT, IWL_CFG_NO_CDB,
		      iwl9560_quz_a0_jf_b0_cfg, iwl9560_समाप्तer_1550i_name),

	/* QnJ */
	_IWL_DEV_INFO(IWL_CFG_ANY, IWL_CFG_ANY,
		      IWL_CFG_MAC_TYPE_QNJ, IWL_CFG_ANY,
		      IWL_CFG_RF_TYPE_JF1, IWL_CFG_RF_ID_JF1,
		      IWL_CFG_160, IWL_CFG_CORES_BT, IWL_CFG_NO_CDB,
		      iwl9560_qnj_b0_jf_b0_cfg, iwl9461_160_name),
	_IWL_DEV_INFO(IWL_CFG_ANY, IWL_CFG_ANY,
		      IWL_CFG_MAC_TYPE_QNJ, IWL_CFG_ANY,
		      IWL_CFG_RF_TYPE_JF1, IWL_CFG_RF_ID_JF1,
		      IWL_CFG_NO_160, IWL_CFG_CORES_BT, IWL_CFG_NO_CDB,
		      iwl9560_qnj_b0_jf_b0_cfg, iwl9461_name),
	_IWL_DEV_INFO(IWL_CFG_ANY, IWL_CFG_ANY,
		      IWL_CFG_MAC_TYPE_QNJ, IWL_CFG_ANY,
		      IWL_CFG_RF_TYPE_JF1, IWL_CFG_RF_ID_JF1_DIV,
		      IWL_CFG_160, IWL_CFG_CORES_BT, IWL_CFG_NO_CDB,
		      iwl9560_qnj_b0_jf_b0_cfg, iwl9462_160_name),
	_IWL_DEV_INFO(IWL_CFG_ANY, IWL_CFG_ANY,
		      IWL_CFG_MAC_TYPE_QNJ, IWL_CFG_ANY,
		      IWL_CFG_RF_TYPE_JF1, IWL_CFG_RF_ID_JF1_DIV,
		      IWL_CFG_NO_160, IWL_CFG_CORES_BT, IWL_CFG_NO_CDB,
		      iwl9560_qnj_b0_jf_b0_cfg, iwl9462_name),

	_IWL_DEV_INFO(IWL_CFG_ANY, IWL_CFG_ANY,
		      IWL_CFG_MAC_TYPE_QNJ, IWL_CFG_ANY,
		      IWL_CFG_RF_TYPE_JF2, IWL_CFG_RF_ID_JF,
		      IWL_CFG_160, IWL_CFG_CORES_BT, IWL_CFG_NO_CDB,
		      iwl9560_qnj_b0_jf_b0_cfg, iwl9560_160_name),
	_IWL_DEV_INFO(IWL_CFG_ANY, IWL_CFG_ANY,
		      IWL_CFG_MAC_TYPE_QNJ, IWL_CFG_ANY,
		      IWL_CFG_RF_TYPE_JF2, IWL_CFG_RF_ID_JF,
		      IWL_CFG_NO_160, IWL_CFG_CORES_BT, IWL_CFG_NO_CDB,
		      iwl9560_qnj_b0_jf_b0_cfg, iwl9560_name),

	_IWL_DEV_INFO(IWL_CFG_ANY, 0x1551,
		      IWL_CFG_MAC_TYPE_QNJ, IWL_CFG_ANY,
		      IWL_CFG_RF_TYPE_JF2, IWL_CFG_RF_ID_JF,
		      IWL_CFG_160, IWL_CFG_CORES_BT, IWL_CFG_NO_CDB,
		      iwl9560_qnj_b0_jf_b0_cfg, iwl9560_समाप्तer_1550s_name),
	_IWL_DEV_INFO(IWL_CFG_ANY, 0x1552,
		      IWL_CFG_MAC_TYPE_QNJ, IWL_CFG_ANY,
		      IWL_CFG_RF_TYPE_JF2, IWL_CFG_RF_ID_JF,
		      IWL_CFG_NO_160, IWL_CFG_CORES_BT, IWL_CFG_NO_CDB,
		      iwl9560_qnj_b0_jf_b0_cfg, iwl9560_समाप्तer_1550i_name),

/* Qu with Hr */
	/* Qu B step */
	_IWL_DEV_INFO(IWL_CFG_ANY, IWL_CFG_ANY,
		      IWL_CFG_MAC_TYPE_QU, SILICON_B_STEP,
		      IWL_CFG_RF_TYPE_HR1, IWL_CFG_ANY,
		      IWL_CFG_ANY, IWL_CFG_ANY, IWL_CFG_NO_CDB,
		      iwl_qu_b0_hr1_b0, iwl_ax101_name),
	_IWL_DEV_INFO(IWL_CFG_ANY, IWL_CFG_ANY,
		      IWL_CFG_MAC_TYPE_QU, SILICON_C_STEP,
		      IWL_CFG_RF_TYPE_HR2, IWL_CFG_ANY,
		      IWL_CFG_ANY, IWL_CFG_ANY, IWL_CFG_NO_CDB,
		      iwl_qu_b0_hr_b0, iwl_ax203_name),

	/* Qu C step */
	_IWL_DEV_INFO(IWL_CFG_ANY, IWL_CFG_ANY,
		      IWL_CFG_MAC_TYPE_QU, SILICON_C_STEP,
		      IWL_CFG_RF_TYPE_HR1, IWL_CFG_ANY,
		      IWL_CFG_ANY, IWL_CFG_ANY, IWL_CFG_NO_CDB,
		      iwl_qu_c0_hr1_b0, iwl_ax101_name),
	_IWL_DEV_INFO(IWL_CFG_ANY, IWL_CFG_ANY,
		      IWL_CFG_MAC_TYPE_QU, SILICON_C_STEP,
		      IWL_CFG_RF_TYPE_HR2, IWL_CFG_ANY,
		      IWL_CFG_ANY, IWL_CFG_ANY, IWL_CFG_NO_CDB,
		      iwl_qu_c0_hr_b0, iwl_ax203_name),

	/* QuZ */
	_IWL_DEV_INFO(IWL_CFG_ANY, IWL_CFG_ANY,
		      IWL_CFG_MAC_TYPE_QUZ, IWL_CFG_ANY,
		      IWL_CFG_RF_TYPE_HR1, IWL_CFG_ANY,
		      IWL_CFG_ANY, IWL_CFG_ANY, IWL_CFG_NO_CDB,
		      iwl_quz_a0_hr1_b0, iwl_ax101_name),
	_IWL_DEV_INFO(IWL_CFG_ANY, IWL_CFG_ANY,
		      IWL_CFG_MAC_TYPE_QUZ, SILICON_B_STEP,
		      IWL_CFG_RF_TYPE_HR2, IWL_CFG_ANY,
		      IWL_CFG_NO_160, IWL_CFG_ANY, IWL_CFG_NO_CDB,
		      iwl_cfg_quz_a0_hr_b0, iwl_ax203_name),

/* QnJ with Hr */
	_IWL_DEV_INFO(IWL_CFG_ANY, IWL_CFG_ANY,
		      IWL_CFG_MAC_TYPE_QNJ, IWL_CFG_ANY,
		      IWL_CFG_RF_TYPE_HR2, IWL_CFG_ANY,
		      IWL_CFG_ANY, IWL_CFG_ANY, IWL_CFG_NO_CDB,
		      iwl_qnj_b0_hr_b0_cfg, iwl_ax201_name),

/* SnJ with Jf */
	_IWL_DEV_INFO(IWL_CFG_ANY, IWL_CFG_ANY,
		      IWL_CFG_MAC_TYPE_SNJ, IWL_CFG_ANY,
		      IWL_CFG_RF_TYPE_JF1, IWL_CFG_RF_ID_JF1,
		      IWL_CFG_160, IWL_CFG_CORES_BT, IWL_CFG_NO_CDB,
		      iwl_cfg_snj_a0_jf_b0, iwl9461_160_name),
	_IWL_DEV_INFO(IWL_CFG_ANY, IWL_CFG_ANY,
		      IWL_CFG_MAC_TYPE_SNJ, IWL_CFG_ANY,
		      IWL_CFG_RF_TYPE_JF1, IWL_CFG_RF_ID_JF1,
		      IWL_CFG_NO_160, IWL_CFG_CORES_BT, IWL_CFG_NO_CDB,
		      iwl_cfg_snj_a0_jf_b0, iwl9461_name),
	_IWL_DEV_INFO(IWL_CFG_ANY, IWL_CFG_ANY,
		      IWL_CFG_MAC_TYPE_SNJ, IWL_CFG_ANY,
		      IWL_CFG_RF_TYPE_JF1, IWL_CFG_RF_ID_JF1_DIV,
		      IWL_CFG_160, IWL_CFG_CORES_BT, IWL_CFG_NO_CDB,
		      iwl_cfg_snj_a0_jf_b0, iwl9462_160_name),
	_IWL_DEV_INFO(IWL_CFG_ANY, IWL_CFG_ANY,
		      IWL_CFG_MAC_TYPE_SNJ, IWL_CFG_ANY,
		      IWL_CFG_RF_TYPE_JF1, IWL_CFG_RF_ID_JF1_DIV,
		      IWL_CFG_NO_160, IWL_CFG_CORES_BT, IWL_CFG_NO_CDB,
		      iwl_cfg_snj_a0_jf_b0, iwl9462_name),

	_IWL_DEV_INFO(IWL_CFG_ANY, IWL_CFG_ANY,
		      IWL_CFG_MAC_TYPE_SNJ, IWL_CFG_ANY,
		      IWL_CFG_RF_TYPE_JF2, IWL_CFG_RF_ID_JF,
		      IWL_CFG_160, IWL_CFG_CORES_BT, IWL_CFG_NO_CDB,
		      iwl_cfg_snj_a0_jf_b0, iwl9560_160_name),
	_IWL_DEV_INFO(IWL_CFG_ANY, IWL_CFG_ANY,
		      IWL_CFG_MAC_TYPE_SNJ, IWL_CFG_ANY,
		      IWL_CFG_RF_TYPE_JF2, IWL_CFG_RF_ID_JF,
		      IWL_CFG_NO_160, IWL_CFG_CORES_BT, IWL_CFG_NO_CDB,
		      iwl_cfg_snj_a0_jf_b0, iwl9560_name),

/* SnJ with Hr */
	_IWL_DEV_INFO(IWL_CFG_ANY, IWL_CFG_ANY,
		      IWL_CFG_MAC_TYPE_SNJ, IWL_CFG_ANY,
		      IWL_CFG_RF_TYPE_HR1, IWL_CFG_ANY,
		      IWL_CFG_ANY, IWL_CFG_ANY, IWL_CFG_NO_CDB,
		      iwl_cfg_snj_hr_b0, iwl_ax101_name),

	_IWL_DEV_INFO(IWL_CFG_ANY, IWL_CFG_ANY,
		      IWL_CFG_MAC_TYPE_SNJ, IWL_CFG_ANY,
		      IWL_CFG_RF_TYPE_HR2, IWL_CFG_ANY,
		      IWL_CFG_ANY, IWL_CFG_ANY, IWL_CFG_NO_CDB,
		      iwl_cfg_snj_hr_b0, iwl_ax201_name),

/* Ma */
	_IWL_DEV_INFO(IWL_CFG_ANY, IWL_CFG_ANY,
		      IWL_CFG_MAC_TYPE_MA, IWL_CFG_ANY,
		      IWL_CFG_RF_TYPE_HR2, IWL_CFG_ANY,
		      IWL_CFG_ANY, IWL_CFG_ANY, IWL_CFG_NO_CDB,
		      iwl_cfg_ma_a0_hr_b0, iwl_ax201_name),
	_IWL_DEV_INFO(IWL_CFG_ANY, IWL_CFG_ANY,
		      IWL_CFG_MAC_TYPE_MA, IWL_CFG_ANY,
		      IWL_CFG_RF_TYPE_GF, IWL_CFG_ANY,
		      IWL_CFG_ANY, IWL_CFG_ANY, IWL_CFG_NO_CDB,
		      iwl_cfg_ma_a0_gf_a0, iwl_ax211_name),
	_IWL_DEV_INFO(IWL_CFG_ANY, IWL_CFG_ANY,
		      IWL_CFG_MAC_TYPE_MA, IWL_CFG_ANY,
		      IWL_CFG_RF_TYPE_GF, IWL_CFG_ANY,
		      IWL_CFG_ANY, IWL_CFG_ANY, IWL_CFG_CDB,
		      iwl_cfg_ma_a0_gf4_a0, iwl_ax211_name),
	_IWL_DEV_INFO(IWL_CFG_ANY, IWL_CFG_ANY,
		      IWL_CFG_MAC_TYPE_MA, IWL_CFG_ANY,
		      IWL_CFG_RF_TYPE_MR, IWL_CFG_ANY,
		      IWL_CFG_ANY, IWL_CFG_ANY, IWL_CFG_NO_CDB,
		      iwl_cfg_ma_a0_mr_a0, iwl_ax221_name),
	_IWL_DEV_INFO(IWL_CFG_ANY, IWL_CFG_ANY,
		      IWL_CFG_MAC_TYPE_SNJ, IWL_CFG_ANY,
		      IWL_CFG_RF_TYPE_MR, IWL_CFG_ANY,
		      IWL_CFG_ANY, IWL_CFG_ANY, IWL_CFG_NO_CDB,
		      iwl_cfg_snj_a0_mr_a0, iwl_ax221_name),

/* So with Hr */
	_IWL_DEV_INFO(IWL_CFG_ANY, IWL_CFG_ANY,
		      IWL_CFG_MAC_TYPE_SO, IWL_CFG_ANY,
		      IWL_CFG_RF_TYPE_HR2, IWL_CFG_ANY,
		      IWL_CFG_NO_160, IWL_CFG_ANY, IWL_CFG_NO_CDB,
		      iwl_cfg_so_a0_hr_a0, iwl_ax203_name),
	_IWL_DEV_INFO(IWL_CFG_ANY, IWL_CFG_ANY,
		      IWL_CFG_MAC_TYPE_SO, IWL_CFG_ANY,
		      IWL_CFG_RF_TYPE_HR2, IWL_CFG_ANY,
		      IWL_CFG_NO_160, IWL_CFG_ANY, IWL_CFG_NO_CDB,
		      iwl_cfg_so_a0_hr_a0, iwl_ax203_name),
	_IWL_DEV_INFO(IWL_CFG_ANY, IWL_CFG_ANY,
		      IWL_CFG_MAC_TYPE_SO, IWL_CFG_ANY,
		      IWL_CFG_RF_TYPE_HR1, IWL_CFG_ANY,
		      IWL_CFG_160, IWL_CFG_ANY, IWL_CFG_NO_CDB,
		      iwl_cfg_so_a0_hr_a0, iwl_ax101_name),
	_IWL_DEV_INFO(IWL_CFG_ANY, IWL_CFG_ANY,
		      IWL_CFG_MAC_TYPE_SO, IWL_CFG_ANY,
		      IWL_CFG_RF_TYPE_HR2, IWL_CFG_ANY,
		      IWL_CFG_160, IWL_CFG_ANY, IWL_CFG_NO_CDB,
		      iwl_cfg_so_a0_hr_a0, iwl_ax201_name),

/* So-F with Hr */
	_IWL_DEV_INFO(IWL_CFG_ANY, IWL_CFG_ANY,
		      IWL_CFG_MAC_TYPE_SOF, IWL_CFG_ANY,
		      IWL_CFG_RF_TYPE_HR2, IWL_CFG_ANY,
		      IWL_CFG_NO_160, IWL_CFG_ANY, IWL_CFG_NO_CDB,
		      iwl_cfg_so_a0_hr_a0, iwl_ax203_name),
	_IWL_DEV_INFO(IWL_CFG_ANY, IWL_CFG_ANY,
		      IWL_CFG_MAC_TYPE_SOF, IWL_CFG_ANY,
		      IWL_CFG_RF_TYPE_HR1, IWL_CFG_ANY,
		      IWL_CFG_160, IWL_CFG_ANY, IWL_CFG_NO_CDB,
		      iwl_cfg_so_a0_hr_a0, iwl_ax101_name),
	_IWL_DEV_INFO(IWL_CFG_ANY, IWL_CFG_ANY,
		      IWL_CFG_MAC_TYPE_SOF, IWL_CFG_ANY,
		      IWL_CFG_RF_TYPE_HR2, IWL_CFG_ANY,
		      IWL_CFG_160, IWL_CFG_ANY, IWL_CFG_NO_CDB,
		      iwl_cfg_so_a0_hr_a0, iwl_ax201_name),

/* So-F with Gf */
	_IWL_DEV_INFO(IWL_CFG_ANY, IWL_CFG_ANY,
		      IWL_CFG_MAC_TYPE_SOF, IWL_CFG_ANY,
		      IWL_CFG_RF_TYPE_GF, IWL_CFG_ANY,
		      IWL_CFG_160, IWL_CFG_ANY, IWL_CFG_NO_CDB,
		      iwlax211_2ax_cfg_so_gf_a0, iwl_ax211_name),

/* Bz */
	_IWL_DEV_INFO(IWL_CFG_ANY, IWL_CFG_ANY,
		      IWL_CFG_MAC_TYPE_BZ, IWL_CFG_ANY,
		      IWL_CFG_RF_TYPE_HR2, IWL_CFG_ANY,
		      IWL_CFG_ANY, IWL_CFG_ANY, IWL_CFG_NO_CDB,
		      iwl_cfg_bz_a0_hr_b0, iwl_ax201_name),
	_IWL_DEV_INFO(IWL_CFG_ANY, IWL_CFG_ANY,
		      IWL_CFG_MAC_TYPE_BZ, IWL_CFG_ANY,
		      IWL_CFG_RF_TYPE_GF, IWL_CFG_ANY,
		      IWL_CFG_ANY, IWL_CFG_ANY, IWL_CFG_NO_CDB,
		      iwl_cfg_bz_a0_gf_a0, iwl_ax211_name),
	_IWL_DEV_INFO(IWL_CFG_ANY, IWL_CFG_ANY,
		      IWL_CFG_MAC_TYPE_BZ, IWL_CFG_ANY,
		      IWL_CFG_RF_TYPE_GF, IWL_CFG_ANY,
		      IWL_CFG_ANY, IWL_CFG_ANY, IWL_CFG_CDB,
		      iwl_cfg_bz_a0_gf4_a0, iwl_ax211_name),
	_IWL_DEV_INFO(IWL_CFG_ANY, IWL_CFG_ANY,
		      IWL_CFG_MAC_TYPE_BZ, IWL_CFG_ANY,
		      IWL_CFG_RF_TYPE_MR, IWL_CFG_ANY,
		      IWL_CFG_ANY, IWL_CFG_ANY, IWL_CFG_NO_CDB,
		      iwl_cfg_bz_a0_mr_a0, iwl_ax211_name),

/* So with GF */
	_IWL_DEV_INFO(IWL_CFG_ANY, IWL_CFG_ANY,
		      IWL_CFG_MAC_TYPE_SO, IWL_CFG_ANY,
		      IWL_CFG_RF_TYPE_GF, IWL_CFG_ANY,
		      IWL_CFG_160, IWL_CFG_ANY, IWL_CFG_NO_CDB,
		      iwlax211_2ax_cfg_so_gf_a0, iwl_ax211_name)

#पूर्ण_अगर /* CONFIG_IWLMVM */
पूर्ण;

/* PCI रेजिस्टरs */
#घोषणा PCI_CFG_RETRY_TIMEOUT	0x041

अटल पूर्णांक iwl_pci_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	स्थिर काष्ठा iwl_cfg_trans_params *trans;
	स्थिर काष्ठा iwl_cfg *cfg_7265d __maybe_unused = शून्य;
	काष्ठा iwl_trans *iwl_trans;
	काष्ठा iwl_trans_pcie *trans_pcie;
	पूर्णांक i, ret;
	स्थिर काष्ठा iwl_cfg *cfg;

	trans = (व्योम *)(ent->driver_data & ~TRANS_CFG_MARKER);

	/*
	 * This is needed क्रम backwards compatibility with the old
	 * tables, so we करोn't need to change all the config काष्ठाs
	 * at the same समय.  The cfg is used to compare with the old
	 * full cfg काष्ठाs.
	 */
	cfg = (व्योम *)(ent->driver_data & ~TRANS_CFG_MARKER);

	/* make sure trans is the first element in iwl_cfg */
	BUILD_BUG_ON(दुरत्व(काष्ठा iwl_cfg, trans));

	iwl_trans = iwl_trans_pcie_alloc(pdev, ent, trans);
	अगर (IS_ERR(iwl_trans))
		वापस PTR_ERR(iwl_trans);

	trans_pcie = IWL_TRANS_GET_PCIE_TRANS(iwl_trans);

	iwl_trans->hw_rf_id = iwl_पढ़ो32(iwl_trans, CSR_HW_RF_ID);

	क्रम (i = 0; i < ARRAY_SIZE(iwl_dev_info_table); i++) अणु
		स्थिर काष्ठा iwl_dev_info *dev_info = &iwl_dev_info_table[i];
		अगर ((dev_info->device == (u16)IWL_CFG_ANY ||
		     dev_info->device == pdev->device) &&
		    (dev_info->subdevice == (u16)IWL_CFG_ANY ||
		     dev_info->subdevice == pdev->subप्रणाली_device) &&
		    (dev_info->mac_type == (u16)IWL_CFG_ANY ||
		     dev_info->mac_type ==
		     CSR_HW_REV_TYPE(iwl_trans->hw_rev)) &&
		    (dev_info->mac_step == (u8)IWL_CFG_ANY ||
		     dev_info->mac_step ==
		     CSR_HW_REV_STEP(iwl_trans->hw_rev)) &&
		    (dev_info->rf_type == (u16)IWL_CFG_ANY ||
		     dev_info->rf_type ==
		     CSR_HW_RFID_TYPE(iwl_trans->hw_rf_id)) &&
		    (dev_info->cdb == IWL_CFG_NO_CDB ||
		     CSR_HW_RFID_IS_CDB(iwl_trans->hw_rf_id)) &&
		    (dev_info->rf_id == (u8)IWL_CFG_ANY ||
		     dev_info->rf_id ==
		     IWL_SUBDEVICE_RF_ID(pdev->subप्रणाली_device)) &&
		    (dev_info->no_160 == (u8)IWL_CFG_ANY ||
		     dev_info->no_160 ==
		     IWL_SUBDEVICE_NO_160(pdev->subप्रणाली_device)) &&
		    (dev_info->cores == (u8)IWL_CFG_ANY ||
		     dev_info->cores ==
		     IWL_SUBDEVICE_CORES(pdev->subप्रणाली_device))) अणु
			iwl_trans->cfg = dev_info->cfg;
			iwl_trans->name = dev_info->name;
		पूर्ण
	पूर्ण

#अगर IS_ENABLED(CONFIG_IWLMVM)

	/*
	 * Workaround क्रम problematic SnJ device: someबार when
	 * certain RF modules are connected to SnJ, the device ID
	 * changes to QnJ's ID.  So we are using QnJ's trans_cfg until
	 * here.  But अगर we detect that the MAC type is actually SnJ,
	 * we should चयन to it here to aव्योम problems later.
	 */
	अगर (CSR_HW_REV_TYPE(iwl_trans->hw_rev) == IWL_CFG_MAC_TYPE_SNJ)
		iwl_trans->trans_cfg = &iwl_so_trans_cfg;

	/*
	 * special-हाल 7265D, it has the same PCI IDs.
	 *
	 * Note that because we alपढ़ोy pass the cfg to the transport above,
	 * all the parameters that the transport uses must, until that is
	 * changed, be identical to the ones in the 7265D configuration.
	 */
	अगर (cfg == &iwl7265_2ac_cfg)
		cfg_7265d = &iwl7265d_2ac_cfg;
	अन्यथा अगर (cfg == &iwl7265_2n_cfg)
		cfg_7265d = &iwl7265d_2n_cfg;
	अन्यथा अगर (cfg == &iwl7265_n_cfg)
		cfg_7265d = &iwl7265d_n_cfg;
	अगर (cfg_7265d &&
	    (iwl_trans->hw_rev & CSR_HW_REV_TYPE_MSK) == CSR_HW_REV_TYPE_7265D)
		iwl_trans->cfg = cfg_7265d;

	अगर (cfg == &iwlax210_2ax_cfg_so_hr_a0) अणु
		अगर (iwl_trans->hw_rev == CSR_HW_REV_TYPE_TY) अणु
			iwl_trans->cfg = &iwlax210_2ax_cfg_ty_gf_a0;
		पूर्ण अन्यथा अगर (CSR_HW_RF_ID_TYPE_CHIP_ID(iwl_trans->hw_rf_id) ==
			   CSR_HW_RF_ID_TYPE_CHIP_ID(CSR_HW_RF_ID_TYPE_JF)) अणु
			iwl_trans->cfg = &iwlax210_2ax_cfg_so_jf_b0;
		पूर्ण अन्यथा अगर (CSR_HW_RF_ID_TYPE_CHIP_ID(iwl_trans->hw_rf_id) ==
			   CSR_HW_RF_ID_TYPE_CHIP_ID(CSR_HW_RF_ID_TYPE_GF)) अणु
			iwl_trans->cfg = &iwlax211_2ax_cfg_so_gf_a0;
		पूर्ण अन्यथा अगर (CSR_HW_RF_ID_TYPE_CHIP_ID(iwl_trans->hw_rf_id) ==
			   CSR_HW_RF_ID_TYPE_CHIP_ID(CSR_HW_RF_ID_TYPE_GF4)) अणु
			iwl_trans->cfg = &iwlax411_2ax_cfg_so_gf4_a0;
		पूर्ण
	पूर्ण

	/*
	 * This is a hack to चयन from Qu B0 to Qu C0.  We need to
	 * करो this क्रम all cfgs that use Qu B0, except क्रम those using
	 * Jf, which have alपढ़ोy been moved to the new table.  The
	 * rest must be हटाओd once we convert Qu with Hr as well.
	 */
	अगर (iwl_trans->hw_rev == CSR_HW_REV_TYPE_QU_C0) अणु
		अगर (iwl_trans->cfg == &iwl_ax201_cfg_qu_hr)
			iwl_trans->cfg = &iwl_ax201_cfg_qu_c0_hr_b0;
		अन्यथा अगर (iwl_trans->cfg == &समाप्तer1650s_2ax_cfg_qu_b0_hr_b0)
			iwl_trans->cfg = &समाप्तer1650s_2ax_cfg_qu_c0_hr_b0;
		अन्यथा अगर (iwl_trans->cfg == &समाप्तer1650i_2ax_cfg_qu_b0_hr_b0)
			iwl_trans->cfg = &समाप्तer1650i_2ax_cfg_qu_c0_hr_b0;
	पूर्ण

	/* same thing क्रम QuZ... */
	अगर (iwl_trans->hw_rev == CSR_HW_REV_TYPE_QUZ) अणु
		अगर (iwl_trans->cfg == &iwl_ax201_cfg_qu_hr)
			iwl_trans->cfg = &iwl_ax201_cfg_quz_hr;
		अन्यथा अगर (iwl_trans->cfg == &समाप्तer1650s_2ax_cfg_qu_b0_hr_b0)
			iwl_trans->cfg = &iwl_ax1650s_cfg_quz_hr;
		अन्यथा अगर (iwl_trans->cfg == &समाप्तer1650i_2ax_cfg_qu_b0_hr_b0)
			iwl_trans->cfg = &iwl_ax1650i_cfg_quz_hr;
	पूर्ण

#पूर्ण_अगर
	/*
	 * If we didn't set the cfg yet, the PCI ID table entry should have
	 * been a full config - अगर yes, use it, otherwise fail.
	 */
	अगर (!iwl_trans->cfg) अणु
		अगर (ent->driver_data & TRANS_CFG_MARKER) अणु
			pr_err("No config found for PCI dev %04x/%04x, rev=0x%x, rfid=0x%x\n",
			       pdev->device, pdev->subप्रणाली_device,
			       iwl_trans->hw_rev, iwl_trans->hw_rf_id);
			ret = -EINVAL;
			जाओ out_मुक्त_trans;
		पूर्ण
		iwl_trans->cfg = cfg;
	पूर्ण

	/* अगर we करोn't have a name yet, copy name from the old cfg */
	अगर (!iwl_trans->name)
		iwl_trans->name = iwl_trans->cfg->name;

	अगर (iwl_trans->trans_cfg->mq_rx_supported) अणु
		अगर (WARN_ON(!iwl_trans->cfg->num_rbds)) अणु
			ret = -EINVAL;
			जाओ out_मुक्त_trans;
		पूर्ण
		trans_pcie->num_rx_bufs = iwl_trans->cfg->num_rbds;
	पूर्ण अन्यथा अणु
		trans_pcie->num_rx_bufs = RX_QUEUE_SIZE;
	पूर्ण

	ret = iwl_trans_init(iwl_trans);
	अगर (ret)
		जाओ out_मुक्त_trans;

	pci_set_drvdata(pdev, iwl_trans);
	iwl_trans->drv = iwl_drv_start(iwl_trans);

	अगर (IS_ERR(iwl_trans->drv)) अणु
		ret = PTR_ERR(iwl_trans->drv);
		जाओ out_मुक्त_trans;
	पूर्ण

	/* रेजिस्टर transport layer debugfs here */
	iwl_trans_pcie_dbgfs_रेजिस्टर(iwl_trans);

	वापस 0;

out_मुक्त_trans:
	iwl_trans_pcie_मुक्त(iwl_trans);
	वापस ret;
पूर्ण

अटल व्योम iwl_pci_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा iwl_trans *trans = pci_get_drvdata(pdev);

	iwl_drv_stop(trans->drv);

	iwl_trans_pcie_मुक्त(trans);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP

अटल पूर्णांक iwl_pci_suspend(काष्ठा device *device)
अणु
	/* Beक्रमe you put code here, think about WoWLAN. You cannot check here
	 * whether WoWLAN is enabled or not, and your code will run even अगर
	 * WoWLAN is enabled - करोn't समाप्त the NIC, someone may need it in Sx.
	 */

	वापस 0;
पूर्ण

अटल पूर्णांक iwl_pci_resume(काष्ठा device *device)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(device);
	काष्ठा iwl_trans *trans = pci_get_drvdata(pdev);
	काष्ठा iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);

	/* Beक्रमe you put code here, think about WoWLAN. You cannot check here
	 * whether WoWLAN is enabled or not, and your code will run even अगर
	 * WoWLAN is enabled - the NIC may be alive.
	 */

	/*
	 * We disable the RETRY_TIMEOUT रेजिस्टर (0x41) to keep
	 * PCI Tx retries from पूर्णांकerfering with C3 CPU state.
	 */
	pci_ग_लिखो_config_byte(pdev, PCI_CFG_RETRY_TIMEOUT, 0x00);

	अगर (!trans->op_mode)
		वापस 0;

	/* In WOWLAN, let iwl_trans_pcie_d3_resume करो the rest of the work */
	अगर (test_bit(STATUS_DEVICE_ENABLED, &trans->status))
		वापस 0;

	/* reconfigure the MSI-X mapping to get the correct IRQ क्रम rfसमाप्त */
	iwl_pcie_conf_msix_hw(trans_pcie);

	/*
	 * Enable rfसमाप्त पूर्णांकerrupt (in order to keep track of the rfसमाप्त
	 * status). Must be locked to aव्योम processing a possible rfसमाप्त
	 * पूर्णांकerrupt जबतक in iwl_pcie_check_hw_rf_समाप्त().
	 */
	mutex_lock(&trans_pcie->mutex);
	iwl_enable_rfसमाप्त_पूर्णांक(trans);
	iwl_pcie_check_hw_rf_समाप्त(trans);
	mutex_unlock(&trans_pcie->mutex);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops iwl_dev_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(iwl_pci_suspend,
				iwl_pci_resume)
पूर्ण;

#घोषणा IWL_PM_OPS	(&iwl_dev_pm_ops)

#अन्यथा /* CONFIG_PM_SLEEP */

#घोषणा IWL_PM_OPS	शून्य

#पूर्ण_अगर /* CONFIG_PM_SLEEP */

अटल काष्ठा pci_driver iwl_pci_driver = अणु
	.name = DRV_NAME,
	.id_table = iwl_hw_card_ids,
	.probe = iwl_pci_probe,
	.हटाओ = iwl_pci_हटाओ,
	.driver.pm = IWL_PM_OPS,
पूर्ण;

पूर्णांक __must_check iwl_pci_रेजिस्टर_driver(व्योम)
अणु
	पूर्णांक ret;
	ret = pci_रेजिस्टर_driver(&iwl_pci_driver);
	अगर (ret)
		pr_err("Unable to initialize PCI module\n");

	वापस ret;
पूर्ण

व्योम iwl_pci_unरेजिस्टर_driver(व्योम)
अणु
	pci_unरेजिस्टर_driver(&iwl_pci_driver);
पूर्ण
