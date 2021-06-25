<शैली गुरु>
/* SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0 */
/*
 * Copyright (C) 2017-2020 Mellanox Technologies Ltd.
 */

#अगर_अघोषित __LINUX_PLATFORM_DATA_MLXREG_H
#घोषणा __LINUX_PLATFORM_DATA_MLXREG_H

#घोषणा MLXREG_CORE_LABEL_MAX_SIZE	32
#घोषणा MLXREG_CORE_WD_FEATURE_NOWAYOUT		BIT(0)
#घोषणा MLXREG_CORE_WD_FEATURE_START_AT_BOOT	BIT(1)

/**
 * क्रमागत mlxreg_wdt_type - type of HW watchकरोg
 *
 * TYPE1 HW watchकरोg implementation exist in old प्रणालीs.
 * All new प्रणालीs have TYPE2 HW watchकरोg.
 * TYPE3 HW watchकरोg can exist on all प्रणालीs with new CPLD.
 * TYPE3 is selected by WD capability bit.
 */
क्रमागत mlxreg_wdt_type अणु
	MLX_WDT_TYPE1,
	MLX_WDT_TYPE2,
	MLX_WDT_TYPE3,
पूर्ण;

/**
 * काष्ठा mlxreg_hotplug_device - I2C device data:
 *
 * @adapter: I2C device adapter;
 * @client: I2C device client;
 * @brdinfo: device board inक्रमmation;
 * @nr: I2C device adapter number, to which device is to be attached;
 *
 * Structure represents I2C hotplug device अटल data (board topology) and
 * dynamic data (related kernel objects handles).
 */
काष्ठा mlxreg_hotplug_device अणु
	काष्ठा i2c_adapter *adapter;
	काष्ठा i2c_client *client;
	काष्ठा i2c_board_info *brdinfo;
	पूर्णांक nr;
पूर्ण;

/**
 * काष्ठा mlxreg_core_data - attributes control data:
 *
 * @label: attribute label;
 * @reg: attribute रेजिस्टर;
 * @mask: attribute access mask;
 * @bit: attribute effective bit;
 * @capability: attribute capability रेजिस्टर;
 * @reg_prsnt: attribute presence रेजिस्टर;
 * @mode: access mode;
 * @np - poपूर्णांकer to node platक्रमm associated with attribute;
 * @hpdev - hotplug device data;
 * @health_cntr: dynamic device health indication counter;
 * @attached: true अगर device has been attached after good health indication;
 * @regnum: number of रेजिस्टरs occupied by multi-रेजिस्टर attribute;
 */
काष्ठा mlxreg_core_data अणु
	अक्षर label[MLXREG_CORE_LABEL_MAX_SIZE];
	u32 reg;
	u32 mask;
	u32 bit;
	u32 capability;
	u32 reg_prsnt;
	umode_t	mode;
	काष्ठा device_node *np;
	काष्ठा mlxreg_hotplug_device hpdev;
	u32 health_cntr;
	bool attached;
	u8 regnum;
पूर्ण;

/**
 * काष्ठा mlxreg_core_item - same type components controlled by the driver:
 *
 * @data: component data;
 * @aggr_mask: group aggregation mask;
 * @reg: group पूर्णांकerrupt status रेजिस्टर;
 * @mask: group पूर्णांकerrupt mask;
 * @capability: group capability रेजिस्टर;
 * @cache: last status value क्रम elements fro the same group;
 * @count: number of available elements in the group;
 * @ind: element's index inside the group;
 * @inversed: अगर 0: 0 क्रम संकेत status is OK, अगर 1 - 1 is OK;
 * @health: true अगर device has health indication, false in other हाल;
 */
काष्ठा mlxreg_core_item अणु
	काष्ठा mlxreg_core_data *data;
	u32 aggr_mask;
	u32 reg;
	u32 mask;
	u32 capability;
	u32 cache;
	u8 count;
	u8 ind;
	u8 inversed;
	u8 health;
पूर्ण;

/**
 * काष्ठा mlxreg_core_platक्रमm_data - platक्रमm data:
 *
 * @data: instance निजी data;
 * @regmap: रेजिस्टर map of parent device;
 * @counter: number of instances;
 * @features: supported features of device;
 * @version: implementation version;
 * @identity: device identity name;
 * @capability: device capability रेजिस्टर;
 */
काष्ठा mlxreg_core_platक्रमm_data अणु
	काष्ठा mlxreg_core_data *data;
	व्योम *regmap;
	पूर्णांक counter;
	u32 features;
	u32 version;
	अक्षर identity[MLXREG_CORE_LABEL_MAX_SIZE];
	u32 capability;
पूर्ण;

/**
 * काष्ठा mlxreg_core_hotplug_platक्रमm_data - hotplug platक्रमm data:
 *
 * @items: same type components with the hotplug capability;
 * @irq: platक्रमm पूर्णांकerrupt number;
 * @regmap: रेजिस्टर map of parent device;
 * @counter: number of the components with the hotplug capability;
 * @cell: location of top aggregation पूर्णांकerrupt रेजिस्टर;
 * @mask: top aggregation पूर्णांकerrupt common mask;
 * @cell_low: location of low aggregation पूर्णांकerrupt रेजिस्टर;
 * @mask_low: low aggregation पूर्णांकerrupt common mask;
 * @deferred_nr: I2C adapter number must be exist prior probing execution;
 * @shअगरt_nr: I2C adapter numbers must be incremented by this value;
 */
काष्ठा mlxreg_core_hotplug_platक्रमm_data अणु
	काष्ठा mlxreg_core_item *items;
	पूर्णांक irq;
	व्योम *regmap;
	पूर्णांक counter;
	u32 cell;
	u32 mask;
	u32 cell_low;
	u32 mask_low;
	पूर्णांक deferred_nr;
	पूर्णांक shअगरt_nr;
पूर्ण;

#पूर्ण_अगर /* __LINUX_PLATFORM_DATA_MLXREG_H */
