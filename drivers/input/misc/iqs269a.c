<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Azoteq IQS269A Capacitive Touch Controller
 *
 * Copyright (C) 2020 Jeff LaBundy <jeff@labundy.com>
 *
 * This driver रेजिस्टरs up to 3 input devices: one representing capacitive or
 * inductive keys as well as Hall-effect चयनes, and one क्रम each of the two
 * axial sliders presented by the device.
 */

#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/i2c.h>
#समावेश <linux/input.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/of_device.h>
#समावेश <linux/property.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>

#घोषणा IQS269_VER_INFO				0x00
#घोषणा IQS269_VER_INFO_PROD_NUM		0x4F

#घोषणा IQS269_SYS_FLAGS			0x02
#घोषणा IQS269_SYS_FLAGS_SHOW_RESET		BIT(15)
#घोषणा IQS269_SYS_FLAGS_PWR_MODE_MASK		GENMASK(12, 11)
#घोषणा IQS269_SYS_FLAGS_PWR_MODE_SHIFT		11
#घोषणा IQS269_SYS_FLAGS_IN_ATI			BIT(10)

#घोषणा IQS269_CHx_COUNTS			0x08

#घोषणा IQS269_SLIDER_X				0x30

#घोषणा IQS269_CAL_DATA_A			0x35
#घोषणा IQS269_CAL_DATA_A_HALL_BIN_L_MASK	GENMASK(15, 12)
#घोषणा IQS269_CAL_DATA_A_HALL_BIN_L_SHIFT	12
#घोषणा IQS269_CAL_DATA_A_HALL_BIN_R_MASK	GENMASK(11, 8)
#घोषणा IQS269_CAL_DATA_A_HALL_BIN_R_SHIFT	8

#घोषणा IQS269_SYS_SETTINGS			0x80
#घोषणा IQS269_SYS_SETTINGS_CLK_DIV		BIT(15)
#घोषणा IQS269_SYS_SETTINGS_ULP_AUTO		BIT(14)
#घोषणा IQS269_SYS_SETTINGS_DIS_AUTO		BIT(13)
#घोषणा IQS269_SYS_SETTINGS_PWR_MODE_MASK	GENMASK(12, 11)
#घोषणा IQS269_SYS_SETTINGS_PWR_MODE_SHIFT	11
#घोषणा IQS269_SYS_SETTINGS_PWR_MODE_MAX	3
#घोषणा IQS269_SYS_SETTINGS_ULP_UPDATE_MASK	GENMASK(10, 8)
#घोषणा IQS269_SYS_SETTINGS_ULP_UPDATE_SHIFT	8
#घोषणा IQS269_SYS_SETTINGS_ULP_UPDATE_MAX	7
#घोषणा IQS269_SYS_SETTINGS_RESEED_OFFSET	BIT(6)
#घोषणा IQS269_SYS_SETTINGS_EVENT_MODE		BIT(5)
#घोषणा IQS269_SYS_SETTINGS_EVENT_MODE_LP	BIT(4)
#घोषणा IQS269_SYS_SETTINGS_REDO_ATI		BIT(2)
#घोषणा IQS269_SYS_SETTINGS_ACK_RESET		BIT(0)

#घोषणा IQS269_FILT_STR_LP_LTA_MASK		GENMASK(7, 6)
#घोषणा IQS269_FILT_STR_LP_LTA_SHIFT		6
#घोषणा IQS269_FILT_STR_LP_CNT_MASK		GENMASK(5, 4)
#घोषणा IQS269_FILT_STR_LP_CNT_SHIFT		4
#घोषणा IQS269_FILT_STR_NP_LTA_MASK		GENMASK(3, 2)
#घोषणा IQS269_FILT_STR_NP_LTA_SHIFT		2
#घोषणा IQS269_FILT_STR_NP_CNT_MASK		GENMASK(1, 0)
#घोषणा IQS269_FILT_STR_MAX			3

#घोषणा IQS269_EVENT_MASK_SYS			BIT(6)
#घोषणा IQS269_EVENT_MASK_DEEP			BIT(2)
#घोषणा IQS269_EVENT_MASK_TOUCH			BIT(1)
#घोषणा IQS269_EVENT_MASK_PROX			BIT(0)

#घोषणा IQS269_RATE_NP_MS_MAX			255
#घोषणा IQS269_RATE_LP_MS_MAX			255
#घोषणा IQS269_RATE_ULP_MS_MAX			4080
#घोषणा IQS269_TIMEOUT_PWR_MS_MAX		130560
#घोषणा IQS269_TIMEOUT_LTA_MS_MAX		130560

#घोषणा IQS269_MISC_A_ATI_BAND_DISABLE		BIT(15)
#घोषणा IQS269_MISC_A_ATI_LP_ONLY		BIT(14)
#घोषणा IQS269_MISC_A_ATI_BAND_TIGHTEN		BIT(13)
#घोषणा IQS269_MISC_A_FILT_DISABLE		BIT(12)
#घोषणा IQS269_MISC_A_GPIO3_SELECT_MASK		GENMASK(10, 8)
#घोषणा IQS269_MISC_A_GPIO3_SELECT_SHIFT	8
#घोषणा IQS269_MISC_A_DUAL_सूची			BIT(6)
#घोषणा IQS269_MISC_A_TX_FREQ_MASK		GENMASK(5, 4)
#घोषणा IQS269_MISC_A_TX_FREQ_SHIFT		4
#घोषणा IQS269_MISC_A_TX_FREQ_MAX		3
#घोषणा IQS269_MISC_A_GLOBAL_CAP_SIZE		BIT(0)

#घोषणा IQS269_MISC_B_RESEED_UI_SEL_MASK	GENMASK(7, 6)
#घोषणा IQS269_MISC_B_RESEED_UI_SEL_SHIFT	6
#घोषणा IQS269_MISC_B_RESEED_UI_SEL_MAX		3
#घोषणा IQS269_MISC_B_TRACKING_UI_ENABLE	BIT(4)
#घोषणा IQS269_MISC_B_FILT_STR_SLIDER		GENMASK(1, 0)

#घोषणा IQS269_CHx_SETTINGS			0x8C

#घोषणा IQS269_CHx_ENG_A_MEAS_CAP_SIZE		BIT(15)
#घोषणा IQS269_CHx_ENG_A_RX_GND_INACTIVE	BIT(13)
#घोषणा IQS269_CHx_ENG_A_LOCAL_CAP_SIZE		BIT(12)
#घोषणा IQS269_CHx_ENG_A_ATI_MODE_MASK		GENMASK(9, 8)
#घोषणा IQS269_CHx_ENG_A_ATI_MODE_SHIFT		8
#घोषणा IQS269_CHx_ENG_A_ATI_MODE_MAX		3
#घोषणा IQS269_CHx_ENG_A_INV_LOGIC		BIT(7)
#घोषणा IQS269_CHx_ENG_A_PROJ_BIAS_MASK		GENMASK(6, 5)
#घोषणा IQS269_CHx_ENG_A_PROJ_BIAS_SHIFT	5
#घोषणा IQS269_CHx_ENG_A_PROJ_BIAS_MAX		3
#घोषणा IQS269_CHx_ENG_A_SENSE_MODE_MASK	GENMASK(3, 0)
#घोषणा IQS269_CHx_ENG_A_SENSE_MODE_MAX		15

#घोषणा IQS269_CHx_ENG_B_LOCAL_CAP_ENABLE	BIT(13)
#घोषणा IQS269_CHx_ENG_B_SENSE_FREQ_MASK	GENMASK(10, 9)
#घोषणा IQS269_CHx_ENG_B_SENSE_FREQ_SHIFT	9
#घोषणा IQS269_CHx_ENG_B_SENSE_FREQ_MAX		3
#घोषणा IQS269_CHx_ENG_B_STATIC_ENABLE		BIT(8)
#घोषणा IQS269_CHx_ENG_B_ATI_BASE_MASK		GENMASK(7, 6)
#घोषणा IQS269_CHx_ENG_B_ATI_BASE_75		0x00
#घोषणा IQS269_CHx_ENG_B_ATI_BASE_100		0x40
#घोषणा IQS269_CHx_ENG_B_ATI_BASE_150		0x80
#घोषणा IQS269_CHx_ENG_B_ATI_BASE_200		0xC0
#घोषणा IQS269_CHx_ENG_B_ATI_TARGET_MASK	GENMASK(5, 0)
#घोषणा IQS269_CHx_ENG_B_ATI_TARGET_MAX		2016

#घोषणा IQS269_CHx_WEIGHT_MAX			255
#घोषणा IQS269_CHx_THRESH_MAX			255
#घोषणा IQS269_CHx_HYST_DEEP_MASK		GENMASK(7, 4)
#घोषणा IQS269_CHx_HYST_DEEP_SHIFT		4
#घोषणा IQS269_CHx_HYST_TOUCH_MASK		GENMASK(3, 0)
#घोषणा IQS269_CHx_HYST_MAX			15

#घोषणा IQS269_CHx_HALL_INACTIVE		6
#घोषणा IQS269_CHx_HALL_ACTIVE			7

#घोषणा IQS269_HALL_PAD_R			BIT(0)
#घोषणा IQS269_HALL_PAD_L			BIT(1)
#घोषणा IQS269_HALL_PAD_INV			BIT(6)

#घोषणा IQS269_HALL_UI				0xF5
#घोषणा IQS269_HALL_UI_ENABLE			BIT(15)

#घोषणा IQS269_MAX_REG				0xFF

#घोषणा IQS269_NUM_CH				8
#घोषणा IQS269_NUM_SL				2

#घोषणा IQS269_ATI_POLL_SLEEP_US		(iqs269->delay_mult * 10000)
#घोषणा IQS269_ATI_POLL_TIMEOUT_US		(iqs269->delay_mult * 500000)
#घोषणा IQS269_ATI_STABLE_DELAY_MS		(iqs269->delay_mult * 150)

#घोषणा IQS269_PWR_MODE_POLL_SLEEP_US		IQS269_ATI_POLL_SLEEP_US
#घोषणा IQS269_PWR_MODE_POLL_TIMEOUT_US		IQS269_ATI_POLL_TIMEOUT_US

#घोषणा iqs269_irq_रुको()			usleep_range(100, 150)

क्रमागत iqs269_local_cap_size अणु
	IQS269_LOCAL_CAP_SIZE_0,
	IQS269_LOCAL_CAP_SIZE_GLOBAL_ONLY,
	IQS269_LOCAL_CAP_SIZE_GLOBAL_0pF5,
पूर्ण;

क्रमागत iqs269_st_offs अणु
	IQS269_ST_OFFS_PROX,
	IQS269_ST_OFFS_सूची,
	IQS269_ST_OFFS_TOUCH,
	IQS269_ST_OFFS_DEEP,
पूर्ण;

क्रमागत iqs269_th_offs अणु
	IQS269_TH_OFFS_PROX,
	IQS269_TH_OFFS_TOUCH,
	IQS269_TH_OFFS_DEEP,
पूर्ण;

क्रमागत iqs269_event_id अणु
	IQS269_EVENT_PROX_DN,
	IQS269_EVENT_PROX_UP,
	IQS269_EVENT_TOUCH_DN,
	IQS269_EVENT_TOUCH_UP,
	IQS269_EVENT_DEEP_DN,
	IQS269_EVENT_DEEP_UP,
पूर्ण;

काष्ठा iqs269_चयन_desc अणु
	अचिन्हित पूर्णांक code;
	bool enabled;
पूर्ण;

काष्ठा iqs269_event_desc अणु
	स्थिर अक्षर *name;
	क्रमागत iqs269_st_offs st_offs;
	क्रमागत iqs269_th_offs th_offs;
	bool dir_up;
	u8 mask;
पूर्ण;

अटल स्थिर काष्ठा iqs269_event_desc iqs269_events[] = अणु
	[IQS269_EVENT_PROX_DN] = अणु
		.name = "event-prox",
		.st_offs = IQS269_ST_OFFS_PROX,
		.th_offs = IQS269_TH_OFFS_PROX,
		.mask = IQS269_EVENT_MASK_PROX,
	पूर्ण,
	[IQS269_EVENT_PROX_UP] = अणु
		.name = "event-prox-alt",
		.st_offs = IQS269_ST_OFFS_PROX,
		.th_offs = IQS269_TH_OFFS_PROX,
		.dir_up = true,
		.mask = IQS269_EVENT_MASK_PROX,
	पूर्ण,
	[IQS269_EVENT_TOUCH_DN] = अणु
		.name = "event-touch",
		.st_offs = IQS269_ST_OFFS_TOUCH,
		.th_offs = IQS269_TH_OFFS_TOUCH,
		.mask = IQS269_EVENT_MASK_TOUCH,
	पूर्ण,
	[IQS269_EVENT_TOUCH_UP] = अणु
		.name = "event-touch-alt",
		.st_offs = IQS269_ST_OFFS_TOUCH,
		.th_offs = IQS269_TH_OFFS_TOUCH,
		.dir_up = true,
		.mask = IQS269_EVENT_MASK_TOUCH,
	पूर्ण,
	[IQS269_EVENT_DEEP_DN] = अणु
		.name = "event-deep",
		.st_offs = IQS269_ST_OFFS_DEEP,
		.th_offs = IQS269_TH_OFFS_DEEP,
		.mask = IQS269_EVENT_MASK_DEEP,
	पूर्ण,
	[IQS269_EVENT_DEEP_UP] = अणु
		.name = "event-deep-alt",
		.st_offs = IQS269_ST_OFFS_DEEP,
		.th_offs = IQS269_TH_OFFS_DEEP,
		.dir_up = true,
		.mask = IQS269_EVENT_MASK_DEEP,
	पूर्ण,
पूर्ण;

काष्ठा iqs269_ver_info अणु
	u8 prod_num;
	u8 sw_num;
	u8 hw_num;
	u8 padding;
पूर्ण __packed;

काष्ठा iqs269_sys_reg अणु
	__be16 general;
	u8 active;
	u8 filter;
	u8 reseed;
	u8 event_mask;
	u8 rate_np;
	u8 rate_lp;
	u8 rate_ulp;
	u8 समयout_pwr;
	u8 समयout_rdy;
	u8 समयout_lta;
	__be16 misc_a;
	__be16 misc_b;
	u8 blocking;
	u8 padding;
	u8 slider_select[IQS269_NUM_SL];
	u8 समयout_tap;
	u8 समयout_swipe;
	u8 thresh_swipe;
	u8 reकरो_ati;
पूर्ण __packed;

काष्ठा iqs269_ch_reg अणु
	u8 rx_enable;
	u8 tx_enable;
	__be16 engine_a;
	__be16 engine_b;
	__be16 ati_comp;
	u8 thresh[3];
	u8 hyst;
	u8 assoc_select;
	u8 assoc_weight;
पूर्ण __packed;

काष्ठा iqs269_flags अणु
	__be16 प्रणाली;
	u8 gesture;
	u8 padding;
	u8 states[4];
पूर्ण __packed;

काष्ठा iqs269_निजी अणु
	काष्ठा i2c_client *client;
	काष्ठा regmap *regmap;
	काष्ठा mutex lock;
	काष्ठा iqs269_चयन_desc चयनes[ARRAY_SIZE(iqs269_events)];
	काष्ठा iqs269_ch_reg ch_reg[IQS269_NUM_CH];
	काष्ठा iqs269_sys_reg sys_reg;
	काष्ठा input_dev *keypad;
	काष्ठा input_dev *slider[IQS269_NUM_SL];
	अचिन्हित पूर्णांक keycode[ARRAY_SIZE(iqs269_events) * IQS269_NUM_CH];
	अचिन्हित पूर्णांक suspend_mode;
	अचिन्हित पूर्णांक delay_mult;
	अचिन्हित पूर्णांक ch_num;
	bool hall_enable;
	bool ati_current;
पूर्ण;

अटल पूर्णांक iqs269_ati_mode_set(काष्ठा iqs269_निजी *iqs269,
			       अचिन्हित पूर्णांक ch_num, अचिन्हित पूर्णांक mode)
अणु
	u16 engine_a;

	अगर (ch_num >= IQS269_NUM_CH)
		वापस -EINVAL;

	अगर (mode > IQS269_CHx_ENG_A_ATI_MODE_MAX)
		वापस -EINVAL;

	mutex_lock(&iqs269->lock);

	engine_a = be16_to_cpu(iqs269->ch_reg[ch_num].engine_a);

	engine_a &= ~IQS269_CHx_ENG_A_ATI_MODE_MASK;
	engine_a |= (mode << IQS269_CHx_ENG_A_ATI_MODE_SHIFT);

	iqs269->ch_reg[ch_num].engine_a = cpu_to_be16(engine_a);
	iqs269->ati_current = false;

	mutex_unlock(&iqs269->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक iqs269_ati_mode_get(काष्ठा iqs269_निजी *iqs269,
			       अचिन्हित पूर्णांक ch_num, अचिन्हित पूर्णांक *mode)
अणु
	u16 engine_a;

	अगर (ch_num >= IQS269_NUM_CH)
		वापस -EINVAL;

	mutex_lock(&iqs269->lock);
	engine_a = be16_to_cpu(iqs269->ch_reg[ch_num].engine_a);
	mutex_unlock(&iqs269->lock);

	engine_a &= IQS269_CHx_ENG_A_ATI_MODE_MASK;
	*mode = (engine_a >> IQS269_CHx_ENG_A_ATI_MODE_SHIFT);

	वापस 0;
पूर्ण

अटल पूर्णांक iqs269_ati_base_set(काष्ठा iqs269_निजी *iqs269,
			       अचिन्हित पूर्णांक ch_num, अचिन्हित पूर्णांक base)
अणु
	u16 engine_b;

	अगर (ch_num >= IQS269_NUM_CH)
		वापस -EINVAL;

	चयन (base) अणु
	हाल 75:
		base = IQS269_CHx_ENG_B_ATI_BASE_75;
		अवरोध;

	हाल 100:
		base = IQS269_CHx_ENG_B_ATI_BASE_100;
		अवरोध;

	हाल 150:
		base = IQS269_CHx_ENG_B_ATI_BASE_150;
		अवरोध;

	हाल 200:
		base = IQS269_CHx_ENG_B_ATI_BASE_200;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	mutex_lock(&iqs269->lock);

	engine_b = be16_to_cpu(iqs269->ch_reg[ch_num].engine_b);

	engine_b &= ~IQS269_CHx_ENG_B_ATI_BASE_MASK;
	engine_b |= base;

	iqs269->ch_reg[ch_num].engine_b = cpu_to_be16(engine_b);
	iqs269->ati_current = false;

	mutex_unlock(&iqs269->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक iqs269_ati_base_get(काष्ठा iqs269_निजी *iqs269,
			       अचिन्हित पूर्णांक ch_num, अचिन्हित पूर्णांक *base)
अणु
	u16 engine_b;

	अगर (ch_num >= IQS269_NUM_CH)
		वापस -EINVAL;

	mutex_lock(&iqs269->lock);
	engine_b = be16_to_cpu(iqs269->ch_reg[ch_num].engine_b);
	mutex_unlock(&iqs269->lock);

	चयन (engine_b & IQS269_CHx_ENG_B_ATI_BASE_MASK) अणु
	हाल IQS269_CHx_ENG_B_ATI_BASE_75:
		*base = 75;
		वापस 0;

	हाल IQS269_CHx_ENG_B_ATI_BASE_100:
		*base = 100;
		वापस 0;

	हाल IQS269_CHx_ENG_B_ATI_BASE_150:
		*base = 150;
		वापस 0;

	हाल IQS269_CHx_ENG_B_ATI_BASE_200:
		*base = 200;
		वापस 0;

	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक iqs269_ati_target_set(काष्ठा iqs269_निजी *iqs269,
				 अचिन्हित पूर्णांक ch_num, अचिन्हित पूर्णांक target)
अणु
	u16 engine_b;

	अगर (ch_num >= IQS269_NUM_CH)
		वापस -EINVAL;

	अगर (target > IQS269_CHx_ENG_B_ATI_TARGET_MAX)
		वापस -EINVAL;

	mutex_lock(&iqs269->lock);

	engine_b = be16_to_cpu(iqs269->ch_reg[ch_num].engine_b);

	engine_b &= ~IQS269_CHx_ENG_B_ATI_TARGET_MASK;
	engine_b |= target / 32;

	iqs269->ch_reg[ch_num].engine_b = cpu_to_be16(engine_b);
	iqs269->ati_current = false;

	mutex_unlock(&iqs269->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक iqs269_ati_target_get(काष्ठा iqs269_निजी *iqs269,
				 अचिन्हित पूर्णांक ch_num, अचिन्हित पूर्णांक *target)
अणु
	u16 engine_b;

	अगर (ch_num >= IQS269_NUM_CH)
		वापस -EINVAL;

	mutex_lock(&iqs269->lock);
	engine_b = be16_to_cpu(iqs269->ch_reg[ch_num].engine_b);
	mutex_unlock(&iqs269->lock);

	*target = (engine_b & IQS269_CHx_ENG_B_ATI_TARGET_MASK) * 32;

	वापस 0;
पूर्ण

अटल पूर्णांक iqs269_parse_mask(स्थिर काष्ठा fwnode_handle *fwnode,
			     स्थिर अक्षर *propname, u8 *mask)
अणु
	अचिन्हित पूर्णांक val[IQS269_NUM_CH];
	पूर्णांक count, error, i;

	count = fwnode_property_count_u32(fwnode, propname);
	अगर (count < 0)
		वापस 0;

	अगर (count > IQS269_NUM_CH)
		वापस -EINVAL;

	error = fwnode_property_पढ़ो_u32_array(fwnode, propname, val, count);
	अगर (error)
		वापस error;

	*mask = 0;

	क्रम (i = 0; i < count; i++) अणु
		अगर (val[i] >= IQS269_NUM_CH)
			वापस -EINVAL;

		*mask |= BIT(val[i]);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक iqs269_parse_chan(काष्ठा iqs269_निजी *iqs269,
			     स्थिर काष्ठा fwnode_handle *ch_node)
अणु
	काष्ठा i2c_client *client = iqs269->client;
	काष्ठा fwnode_handle *ev_node;
	काष्ठा iqs269_ch_reg *ch_reg;
	u16 engine_a, engine_b;
	अचिन्हित पूर्णांक reg, val;
	पूर्णांक error, i;

	error = fwnode_property_पढ़ो_u32(ch_node, "reg", &reg);
	अगर (error) अणु
		dev_err(&client->dev, "Failed to read channel number: %d\n",
			error);
		वापस error;
	पूर्ण अन्यथा अगर (reg >= IQS269_NUM_CH) अणु
		dev_err(&client->dev, "Invalid channel number: %u\n", reg);
		वापस -EINVAL;
	पूर्ण

	iqs269->sys_reg.active |= BIT(reg);
	अगर (!fwnode_property_present(ch_node, "azoteq,reseed-disable"))
		iqs269->sys_reg.reseed |= BIT(reg);

	अगर (fwnode_property_present(ch_node, "azoteq,blocking-enable"))
		iqs269->sys_reg.blocking |= BIT(reg);

	अगर (fwnode_property_present(ch_node, "azoteq,slider0-select"))
		iqs269->sys_reg.slider_select[0] |= BIT(reg);

	अगर (fwnode_property_present(ch_node, "azoteq,slider1-select"))
		iqs269->sys_reg.slider_select[1] |= BIT(reg);

	ch_reg = &iqs269->ch_reg[reg];

	error = regmap_raw_पढ़ो(iqs269->regmap,
				IQS269_CHx_SETTINGS + reg * माप(*ch_reg) / 2,
				ch_reg, माप(*ch_reg));
	अगर (error)
		वापस error;

	error = iqs269_parse_mask(ch_node, "azoteq,rx-enable",
				  &ch_reg->rx_enable);
	अगर (error) अणु
		dev_err(&client->dev, "Invalid channel %u RX enable mask: %d\n",
			reg, error);
		वापस error;
	पूर्ण

	error = iqs269_parse_mask(ch_node, "azoteq,tx-enable",
				  &ch_reg->tx_enable);
	अगर (error) अणु
		dev_err(&client->dev, "Invalid channel %u TX enable mask: %d\n",
			reg, error);
		वापस error;
	पूर्ण

	engine_a = be16_to_cpu(ch_reg->engine_a);
	engine_b = be16_to_cpu(ch_reg->engine_b);

	engine_a |= IQS269_CHx_ENG_A_MEAS_CAP_SIZE;
	अगर (fwnode_property_present(ch_node, "azoteq,meas-cap-decrease"))
		engine_a &= ~IQS269_CHx_ENG_A_MEAS_CAP_SIZE;

	engine_a |= IQS269_CHx_ENG_A_RX_GND_INACTIVE;
	अगर (fwnode_property_present(ch_node, "azoteq,rx-float-inactive"))
		engine_a &= ~IQS269_CHx_ENG_A_RX_GND_INACTIVE;

	engine_a &= ~IQS269_CHx_ENG_A_LOCAL_CAP_SIZE;
	engine_b &= ~IQS269_CHx_ENG_B_LOCAL_CAP_ENABLE;
	अगर (!fwnode_property_पढ़ो_u32(ch_node, "azoteq,local-cap-size", &val)) अणु
		चयन (val) अणु
		हाल IQS269_LOCAL_CAP_SIZE_0:
			अवरोध;

		हाल IQS269_LOCAL_CAP_SIZE_GLOBAL_0pF5:
			engine_a |= IQS269_CHx_ENG_A_LOCAL_CAP_SIZE;
			fallthrough;

		हाल IQS269_LOCAL_CAP_SIZE_GLOBAL_ONLY:
			engine_b |= IQS269_CHx_ENG_B_LOCAL_CAP_ENABLE;
			अवरोध;

		शेष:
			dev_err(&client->dev,
				"Invalid channel %u local cap. size: %u\n", reg,
				val);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	engine_a &= ~IQS269_CHx_ENG_A_INV_LOGIC;
	अगर (fwnode_property_present(ch_node, "azoteq,invert-enable"))
		engine_a |= IQS269_CHx_ENG_A_INV_LOGIC;

	अगर (!fwnode_property_पढ़ो_u32(ch_node, "azoteq,proj-bias", &val)) अणु
		अगर (val > IQS269_CHx_ENG_A_PROJ_BIAS_MAX) अणु
			dev_err(&client->dev,
				"Invalid channel %u bias current: %u\n", reg,
				val);
			वापस -EINVAL;
		पूर्ण

		engine_a &= ~IQS269_CHx_ENG_A_PROJ_BIAS_MASK;
		engine_a |= (val << IQS269_CHx_ENG_A_PROJ_BIAS_SHIFT);
	पूर्ण

	अगर (!fwnode_property_पढ़ो_u32(ch_node, "azoteq,sense-mode", &val)) अणु
		अगर (val > IQS269_CHx_ENG_A_SENSE_MODE_MAX) अणु
			dev_err(&client->dev,
				"Invalid channel %u sensing mode: %u\n", reg,
				val);
			वापस -EINVAL;
		पूर्ण

		engine_a &= ~IQS269_CHx_ENG_A_SENSE_MODE_MASK;
		engine_a |= val;
	पूर्ण

	अगर (!fwnode_property_पढ़ो_u32(ch_node, "azoteq,sense-freq", &val)) अणु
		अगर (val > IQS269_CHx_ENG_B_SENSE_FREQ_MAX) अणु
			dev_err(&client->dev,
				"Invalid channel %u sensing frequency: %u\n",
				reg, val);
			वापस -EINVAL;
		पूर्ण

		engine_b &= ~IQS269_CHx_ENG_B_SENSE_FREQ_MASK;
		engine_b |= (val << IQS269_CHx_ENG_B_SENSE_FREQ_SHIFT);
	पूर्ण

	engine_b &= ~IQS269_CHx_ENG_B_STATIC_ENABLE;
	अगर (fwnode_property_present(ch_node, "azoteq,static-enable"))
		engine_b |= IQS269_CHx_ENG_B_STATIC_ENABLE;

	ch_reg->engine_a = cpu_to_be16(engine_a);
	ch_reg->engine_b = cpu_to_be16(engine_b);

	अगर (!fwnode_property_पढ़ो_u32(ch_node, "azoteq,ati-mode", &val)) अणु
		error = iqs269_ati_mode_set(iqs269, reg, val);
		अगर (error) अणु
			dev_err(&client->dev,
				"Invalid channel %u ATI mode: %u\n", reg, val);
			वापस error;
		पूर्ण
	पूर्ण

	अगर (!fwnode_property_पढ़ो_u32(ch_node, "azoteq,ati-base", &val)) अणु
		error = iqs269_ati_base_set(iqs269, reg, val);
		अगर (error) अणु
			dev_err(&client->dev,
				"Invalid channel %u ATI base: %u\n", reg, val);
			वापस error;
		पूर्ण
	पूर्ण

	अगर (!fwnode_property_पढ़ो_u32(ch_node, "azoteq,ati-target", &val)) अणु
		error = iqs269_ati_target_set(iqs269, reg, val);
		अगर (error) अणु
			dev_err(&client->dev,
				"Invalid channel %u ATI target: %u\n", reg,
				val);
			वापस error;
		पूर्ण
	पूर्ण

	error = iqs269_parse_mask(ch_node, "azoteq,assoc-select",
				  &ch_reg->assoc_select);
	अगर (error) अणु
		dev_err(&client->dev, "Invalid channel %u association: %d\n",
			reg, error);
		वापस error;
	पूर्ण

	अगर (!fwnode_property_पढ़ो_u32(ch_node, "azoteq,assoc-weight", &val)) अणु
		अगर (val > IQS269_CHx_WEIGHT_MAX) अणु
			dev_err(&client->dev,
				"Invalid channel %u associated weight: %u\n",
				reg, val);
			वापस -EINVAL;
		पूर्ण

		ch_reg->assoc_weight = val;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(iqs269_events); i++) अणु
		ev_node = fwnode_get_named_child_node(ch_node,
						      iqs269_events[i].name);
		अगर (!ev_node)
			जारी;

		अगर (!fwnode_property_पढ़ो_u32(ev_node, "azoteq,thresh", &val)) अणु
			अगर (val > IQS269_CHx_THRESH_MAX) अणु
				dev_err(&client->dev,
					"Invalid channel %u threshold: %u\n",
					reg, val);
				वापस -EINVAL;
			पूर्ण

			ch_reg->thresh[iqs269_events[i].th_offs] = val;
		पूर्ण

		अगर (!fwnode_property_पढ़ो_u32(ev_node, "azoteq,hyst", &val)) अणु
			u8 *hyst = &ch_reg->hyst;

			अगर (val > IQS269_CHx_HYST_MAX) अणु
				dev_err(&client->dev,
					"Invalid channel %u hysteresis: %u\n",
					reg, val);
				वापस -EINVAL;
			पूर्ण

			अगर (i == IQS269_EVENT_DEEP_DN ||
			    i == IQS269_EVENT_DEEP_UP) अणु
				*hyst &= ~IQS269_CHx_HYST_DEEP_MASK;
				*hyst |= (val << IQS269_CHx_HYST_DEEP_SHIFT);
			पूर्ण अन्यथा अगर (i == IQS269_EVENT_TOUCH_DN ||
				   i == IQS269_EVENT_TOUCH_UP) अणु
				*hyst &= ~IQS269_CHx_HYST_TOUCH_MASK;
				*hyst |= val;
			पूर्ण
		पूर्ण

		अगर (fwnode_property_पढ़ो_u32(ev_node, "linux,code", &val))
			जारी;

		चयन (reg) अणु
		हाल IQS269_CHx_HALL_ACTIVE:
			अगर (iqs269->hall_enable) अणु
				iqs269->चयनes[i].code = val;
				iqs269->चयनes[i].enabled = true;
			पूर्ण
			fallthrough;

		हाल IQS269_CHx_HALL_INACTIVE:
			अगर (iqs269->hall_enable)
				अवरोध;
			fallthrough;

		शेष:
			iqs269->keycode[i * IQS269_NUM_CH + reg] = val;
		पूर्ण

		iqs269->sys_reg.event_mask &= ~iqs269_events[i].mask;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक iqs269_parse_prop(काष्ठा iqs269_निजी *iqs269)
अणु
	काष्ठा iqs269_sys_reg *sys_reg = &iqs269->sys_reg;
	काष्ठा i2c_client *client = iqs269->client;
	काष्ठा fwnode_handle *ch_node;
	u16 general, misc_a, misc_b;
	अचिन्हित पूर्णांक val;
	पूर्णांक error;

	iqs269->hall_enable = device_property_present(&client->dev,
						      "azoteq,hall-enable");

	अगर (!device_property_पढ़ो_u32(&client->dev, "azoteq,suspend-mode",
				      &val)) अणु
		अगर (val > IQS269_SYS_SETTINGS_PWR_MODE_MAX) अणु
			dev_err(&client->dev, "Invalid suspend mode: %u\n",
				val);
			वापस -EINVAL;
		पूर्ण

		iqs269->suspend_mode = val;
	पूर्ण

	error = regmap_raw_पढ़ो(iqs269->regmap, IQS269_SYS_SETTINGS, sys_reg,
				माप(*sys_reg));
	अगर (error)
		वापस error;

	अगर (!device_property_पढ़ो_u32(&client->dev, "azoteq,filt-str-lp-lta",
				      &val)) अणु
		अगर (val > IQS269_FILT_STR_MAX) अणु
			dev_err(&client->dev, "Invalid filter strength: %u\n",
				val);
			वापस -EINVAL;
		पूर्ण

		sys_reg->filter &= ~IQS269_FILT_STR_LP_LTA_MASK;
		sys_reg->filter |= (val << IQS269_FILT_STR_LP_LTA_SHIFT);
	पूर्ण

	अगर (!device_property_पढ़ो_u32(&client->dev, "azoteq,filt-str-lp-cnt",
				      &val)) अणु
		अगर (val > IQS269_FILT_STR_MAX) अणु
			dev_err(&client->dev, "Invalid filter strength: %u\n",
				val);
			वापस -EINVAL;
		पूर्ण

		sys_reg->filter &= ~IQS269_FILT_STR_LP_CNT_MASK;
		sys_reg->filter |= (val << IQS269_FILT_STR_LP_CNT_SHIFT);
	पूर्ण

	अगर (!device_property_पढ़ो_u32(&client->dev, "azoteq,filt-str-np-lta",
				      &val)) अणु
		अगर (val > IQS269_FILT_STR_MAX) अणु
			dev_err(&client->dev, "Invalid filter strength: %u\n",
				val);
			वापस -EINVAL;
		पूर्ण

		sys_reg->filter &= ~IQS269_FILT_STR_NP_LTA_MASK;
		sys_reg->filter |= (val << IQS269_FILT_STR_NP_LTA_SHIFT);
	पूर्ण

	अगर (!device_property_पढ़ो_u32(&client->dev, "azoteq,filt-str-np-cnt",
				      &val)) अणु
		अगर (val > IQS269_FILT_STR_MAX) अणु
			dev_err(&client->dev, "Invalid filter strength: %u\n",
				val);
			वापस -EINVAL;
		पूर्ण

		sys_reg->filter &= ~IQS269_FILT_STR_NP_CNT_MASK;
		sys_reg->filter |= val;
	पूर्ण

	अगर (!device_property_पढ़ो_u32(&client->dev, "azoteq,rate-np-ms",
				      &val)) अणु
		अगर (val > IQS269_RATE_NP_MS_MAX) अणु
			dev_err(&client->dev, "Invalid report rate: %u\n", val);
			वापस -EINVAL;
		पूर्ण

		sys_reg->rate_np = val;
	पूर्ण

	अगर (!device_property_पढ़ो_u32(&client->dev, "azoteq,rate-lp-ms",
				      &val)) अणु
		अगर (val > IQS269_RATE_LP_MS_MAX) अणु
			dev_err(&client->dev, "Invalid report rate: %u\n", val);
			वापस -EINVAL;
		पूर्ण

		sys_reg->rate_lp = val;
	पूर्ण

	अगर (!device_property_पढ़ो_u32(&client->dev, "azoteq,rate-ulp-ms",
				      &val)) अणु
		अगर (val > IQS269_RATE_ULP_MS_MAX) अणु
			dev_err(&client->dev, "Invalid report rate: %u\n", val);
			वापस -EINVAL;
		पूर्ण

		sys_reg->rate_ulp = val / 16;
	पूर्ण

	अगर (!device_property_पढ़ो_u32(&client->dev, "azoteq,timeout-pwr-ms",
				      &val)) अणु
		अगर (val > IQS269_TIMEOUT_PWR_MS_MAX) अणु
			dev_err(&client->dev, "Invalid timeout: %u\n", val);
			वापस -EINVAL;
		पूर्ण

		sys_reg->समयout_pwr = val / 512;
	पूर्ण

	अगर (!device_property_पढ़ो_u32(&client->dev, "azoteq,timeout-lta-ms",
				      &val)) अणु
		अगर (val > IQS269_TIMEOUT_LTA_MS_MAX) अणु
			dev_err(&client->dev, "Invalid timeout: %u\n", val);
			वापस -EINVAL;
		पूर्ण

		sys_reg->समयout_lta = val / 512;
	पूर्ण

	misc_a = be16_to_cpu(sys_reg->misc_a);
	misc_b = be16_to_cpu(sys_reg->misc_b);

	misc_a &= ~IQS269_MISC_A_ATI_BAND_DISABLE;
	अगर (device_property_present(&client->dev, "azoteq,ati-band-disable"))
		misc_a |= IQS269_MISC_A_ATI_BAND_DISABLE;

	misc_a &= ~IQS269_MISC_A_ATI_LP_ONLY;
	अगर (device_property_present(&client->dev, "azoteq,ati-lp-only"))
		misc_a |= IQS269_MISC_A_ATI_LP_ONLY;

	misc_a &= ~IQS269_MISC_A_ATI_BAND_TIGHTEN;
	अगर (device_property_present(&client->dev, "azoteq,ati-band-tighten"))
		misc_a |= IQS269_MISC_A_ATI_BAND_TIGHTEN;

	misc_a &= ~IQS269_MISC_A_FILT_DISABLE;
	अगर (device_property_present(&client->dev, "azoteq,filt-disable"))
		misc_a |= IQS269_MISC_A_FILT_DISABLE;

	अगर (!device_property_पढ़ो_u32(&client->dev, "azoteq,gpio3-select",
				      &val)) अणु
		अगर (val >= IQS269_NUM_CH) अणु
			dev_err(&client->dev, "Invalid GPIO3 selection: %u\n",
				val);
			वापस -EINVAL;
		पूर्ण

		misc_a &= ~IQS269_MISC_A_GPIO3_SELECT_MASK;
		misc_a |= (val << IQS269_MISC_A_GPIO3_SELECT_SHIFT);
	पूर्ण

	misc_a &= ~IQS269_MISC_A_DUAL_सूची;
	अगर (device_property_present(&client->dev, "azoteq,dual-direction"))
		misc_a |= IQS269_MISC_A_DUAL_सूची;

	अगर (!device_property_पढ़ो_u32(&client->dev, "azoteq,tx-freq", &val)) अणु
		अगर (val > IQS269_MISC_A_TX_FREQ_MAX) अणु
			dev_err(&client->dev,
				"Invalid excitation frequency: %u\n", val);
			वापस -EINVAL;
		पूर्ण

		misc_a &= ~IQS269_MISC_A_TX_FREQ_MASK;
		misc_a |= (val << IQS269_MISC_A_TX_FREQ_SHIFT);
	पूर्ण

	misc_a &= ~IQS269_MISC_A_GLOBAL_CAP_SIZE;
	अगर (device_property_present(&client->dev, "azoteq,global-cap-increase"))
		misc_a |= IQS269_MISC_A_GLOBAL_CAP_SIZE;

	अगर (!device_property_पढ़ो_u32(&client->dev, "azoteq,reseed-select",
				      &val)) अणु
		अगर (val > IQS269_MISC_B_RESEED_UI_SEL_MAX) अणु
			dev_err(&client->dev, "Invalid reseed selection: %u\n",
				val);
			वापस -EINVAL;
		पूर्ण

		misc_b &= ~IQS269_MISC_B_RESEED_UI_SEL_MASK;
		misc_b |= (val << IQS269_MISC_B_RESEED_UI_SEL_SHIFT);
	पूर्ण

	misc_b &= ~IQS269_MISC_B_TRACKING_UI_ENABLE;
	अगर (device_property_present(&client->dev, "azoteq,tracking-enable"))
		misc_b |= IQS269_MISC_B_TRACKING_UI_ENABLE;

	अगर (!device_property_पढ़ो_u32(&client->dev, "azoteq,filt-str-slider",
				      &val)) अणु
		अगर (val > IQS269_FILT_STR_MAX) अणु
			dev_err(&client->dev, "Invalid filter strength: %u\n",
				val);
			वापस -EINVAL;
		पूर्ण

		misc_b &= ~IQS269_MISC_B_FILT_STR_SLIDER;
		misc_b |= val;
	पूर्ण

	sys_reg->misc_a = cpu_to_be16(misc_a);
	sys_reg->misc_b = cpu_to_be16(misc_b);

	sys_reg->active = 0;
	sys_reg->reseed = 0;

	sys_reg->blocking = 0;

	sys_reg->slider_select[0] = 0;
	sys_reg->slider_select[1] = 0;

	sys_reg->event_mask = ~((u8)IQS269_EVENT_MASK_SYS);

	device_क्रम_each_child_node(&client->dev, ch_node) अणु
		error = iqs269_parse_chan(iqs269, ch_node);
		अगर (error) अणु
			fwnode_handle_put(ch_node);
			वापस error;
		पूर्ण
	पूर्ण

	/*
	 * Volunteer all active channels to participate in ATI when REDO-ATI is
	 * manually triggered.
	 */
	sys_reg->reकरो_ati = sys_reg->active;

	general = be16_to_cpu(sys_reg->general);

	अगर (device_property_present(&client->dev, "azoteq,clk-div")) अणु
		general |= IQS269_SYS_SETTINGS_CLK_DIV;
		iqs269->delay_mult = 4;
	पूर्ण अन्यथा अणु
		general &= ~IQS269_SYS_SETTINGS_CLK_DIV;
		iqs269->delay_mult = 1;
	पूर्ण

	/*
	 * Configure the device to स्वतःmatically चयन between normal and low-
	 * घातer modes as a function of sensing activity. Ultra-low-घातer mode,
	 * अगर enabled, is reserved क्रम suspend.
	 */
	general &= ~IQS269_SYS_SETTINGS_ULP_AUTO;
	general &= ~IQS269_SYS_SETTINGS_DIS_AUTO;
	general &= ~IQS269_SYS_SETTINGS_PWR_MODE_MASK;

	अगर (!device_property_पढ़ो_u32(&client->dev, "azoteq,ulp-update",
				      &val)) अणु
		अगर (val > IQS269_SYS_SETTINGS_ULP_UPDATE_MAX) अणु
			dev_err(&client->dev, "Invalid update rate: %u\n", val);
			वापस -EINVAL;
		पूर्ण

		general &= ~IQS269_SYS_SETTINGS_ULP_UPDATE_MASK;
		general |= (val << IQS269_SYS_SETTINGS_ULP_UPDATE_SHIFT);
	पूर्ण

	general &= ~IQS269_SYS_SETTINGS_RESEED_OFFSET;
	अगर (device_property_present(&client->dev, "azoteq,reseed-offset"))
		general |= IQS269_SYS_SETTINGS_RESEED_OFFSET;

	general |= IQS269_SYS_SETTINGS_EVENT_MODE;

	/*
	 * As per the datasheet, enable streaming during normal-घातer mode अगर
	 * either slider is in use. In that हाल, the device वापसs to event
	 * mode during low-घातer mode.
	 */
	अगर (sys_reg->slider_select[0] || sys_reg->slider_select[1])
		general |= IQS269_SYS_SETTINGS_EVENT_MODE_LP;

	general |= IQS269_SYS_SETTINGS_REDO_ATI;
	general |= IQS269_SYS_SETTINGS_ACK_RESET;

	sys_reg->general = cpu_to_be16(general);

	वापस 0;
पूर्ण

अटल पूर्णांक iqs269_dev_init(काष्ठा iqs269_निजी *iqs269)
अणु
	काष्ठा iqs269_sys_reg *sys_reg = &iqs269->sys_reg;
	काष्ठा iqs269_ch_reg *ch_reg;
	अचिन्हित पूर्णांक val;
	पूर्णांक error, i;

	mutex_lock(&iqs269->lock);

	error = regmap_update_bits(iqs269->regmap, IQS269_HALL_UI,
				   IQS269_HALL_UI_ENABLE,
				   iqs269->hall_enable ? ~0 : 0);
	अगर (error)
		जाओ err_mutex;

	क्रम (i = 0; i < IQS269_NUM_CH; i++) अणु
		अगर (!(sys_reg->active & BIT(i)))
			जारी;

		ch_reg = &iqs269->ch_reg[i];

		error = regmap_raw_ग_लिखो(iqs269->regmap,
					 IQS269_CHx_SETTINGS + i *
					 माप(*ch_reg) / 2, ch_reg,
					 माप(*ch_reg));
		अगर (error)
			जाओ err_mutex;
	पूर्ण

	/*
	 * The REDO-ATI and ATI channel selection fields must be written in the
	 * same block ग_लिखो, so every field between रेजिस्टरs 0x80 through 0x8B
	 * (inclusive) must be written as well.
	 */
	error = regmap_raw_ग_लिखो(iqs269->regmap, IQS269_SYS_SETTINGS, sys_reg,
				 माप(*sys_reg));
	अगर (error)
		जाओ err_mutex;

	error = regmap_पढ़ो_poll_समयout(iqs269->regmap, IQS269_SYS_FLAGS, val,
					!(val & IQS269_SYS_FLAGS_IN_ATI),
					 IQS269_ATI_POLL_SLEEP_US,
					 IQS269_ATI_POLL_TIMEOUT_US);
	अगर (error)
		जाओ err_mutex;

	msleep(IQS269_ATI_STABLE_DELAY_MS);
	iqs269->ati_current = true;

err_mutex:
	mutex_unlock(&iqs269->lock);

	वापस error;
पूर्ण

अटल पूर्णांक iqs269_input_init(काष्ठा iqs269_निजी *iqs269)
अणु
	काष्ठा i2c_client *client = iqs269->client;
	काष्ठा iqs269_flags flags;
	अचिन्हित पूर्णांक sw_code, keycode;
	पूर्णांक error, i, j;
	u8 dir_mask, state;

	iqs269->keypad = devm_input_allocate_device(&client->dev);
	अगर (!iqs269->keypad)
		वापस -ENOMEM;

	iqs269->keypad->keycodemax = ARRAY_SIZE(iqs269->keycode);
	iqs269->keypad->keycode = iqs269->keycode;
	iqs269->keypad->keycodesize = माप(*iqs269->keycode);

	iqs269->keypad->name = "iqs269a_keypad";
	iqs269->keypad->id.bustype = BUS_I2C;

	अगर (iqs269->hall_enable) अणु
		error = regmap_raw_पढ़ो(iqs269->regmap, IQS269_SYS_FLAGS,
					&flags, माप(flags));
		अगर (error) अणु
			dev_err(&client->dev,
				"Failed to read initial status: %d\n", error);
			वापस error;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(iqs269_events); i++) अणु
		dir_mask = flags.states[IQS269_ST_OFFS_सूची];
		अगर (!iqs269_events[i].dir_up)
			dir_mask = ~dir_mask;

		state = flags.states[iqs269_events[i].st_offs] & dir_mask;

		sw_code = iqs269->चयनes[i].code;

		क्रम (j = 0; j < IQS269_NUM_CH; j++) अणु
			keycode = iqs269->keycode[i * IQS269_NUM_CH + j];

			/*
			 * Hall-effect sensing repurposes a pair of dedicated
			 * channels, only one of which reports events.
			 */
			चयन (j) अणु
			हाल IQS269_CHx_HALL_ACTIVE:
				अगर (iqs269->hall_enable &&
				    iqs269->चयनes[i].enabled) अणु
					input_set_capability(iqs269->keypad,
							     EV_SW, sw_code);
					input_report_चयन(iqs269->keypad,
							    sw_code,
							    state & BIT(j));
				पूर्ण
				fallthrough;

			हाल IQS269_CHx_HALL_INACTIVE:
				अगर (iqs269->hall_enable)
					जारी;
				fallthrough;

			शेष:
				अगर (keycode != KEY_RESERVED)
					input_set_capability(iqs269->keypad,
							     EV_KEY, keycode);
			पूर्ण
		पूर्ण
	पूर्ण

	input_sync(iqs269->keypad);

	error = input_रेजिस्टर_device(iqs269->keypad);
	अगर (error) अणु
		dev_err(&client->dev, "Failed to register keypad: %d\n", error);
		वापस error;
	पूर्ण

	क्रम (i = 0; i < IQS269_NUM_SL; i++) अणु
		अगर (!iqs269->sys_reg.slider_select[i])
			जारी;

		iqs269->slider[i] = devm_input_allocate_device(&client->dev);
		अगर (!iqs269->slider[i])
			वापस -ENOMEM;

		iqs269->slider[i]->name = i ? "iqs269a_slider_1"
					    : "iqs269a_slider_0";
		iqs269->slider[i]->id.bustype = BUS_I2C;

		input_set_capability(iqs269->slider[i], EV_KEY, BTN_TOUCH);
		input_set_असल_params(iqs269->slider[i], ABS_X, 0, 255, 0, 0);

		error = input_रेजिस्टर_device(iqs269->slider[i]);
		अगर (error) अणु
			dev_err(&client->dev,
				"Failed to register slider %d: %d\n", i, error);
			वापस error;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक iqs269_report(काष्ठा iqs269_निजी *iqs269)
अणु
	काष्ठा i2c_client *client = iqs269->client;
	काष्ठा iqs269_flags flags;
	अचिन्हित पूर्णांक sw_code, keycode;
	पूर्णांक error, i, j;
	u8 slider_x[IQS269_NUM_SL];
	u8 dir_mask, state;

	error = regmap_raw_पढ़ो(iqs269->regmap, IQS269_SYS_FLAGS, &flags,
				माप(flags));
	अगर (error) अणु
		dev_err(&client->dev, "Failed to read device status: %d\n",
			error);
		वापस error;
	पूर्ण

	/*
	 * The device resets itself अगर its own watchकरोg bites, which can happen
	 * in the event of an I2C communication error. In this हाल, the device
	 * निश्चितs a SHOW_RESET पूर्णांकerrupt and all रेजिस्टरs must be restored.
	 */
	अगर (be16_to_cpu(flags.प्रणाली) & IQS269_SYS_FLAGS_SHOW_RESET) अणु
		dev_err(&client->dev, "Unexpected device reset\n");

		error = iqs269_dev_init(iqs269);
		अगर (error)
			dev_err(&client->dev,
				"Failed to re-initialize device: %d\n", error);

		वापस error;
	पूर्ण

	error = regmap_raw_पढ़ो(iqs269->regmap, IQS269_SLIDER_X, slider_x,
				माप(slider_x));
	अगर (error) अणु
		dev_err(&client->dev, "Failed to read slider position: %d\n",
			error);
		वापस error;
	पूर्ण

	क्रम (i = 0; i < IQS269_NUM_SL; i++) अणु
		अगर (!iqs269->sys_reg.slider_select[i])
			जारी;

		/*
		 * Report BTN_TOUCH अगर any channel that participates in the
		 * slider is in a state of touch.
		 */
		अगर (flags.states[IQS269_ST_OFFS_TOUCH] &
		    iqs269->sys_reg.slider_select[i]) अणु
			input_report_key(iqs269->slider[i], BTN_TOUCH, 1);
			input_report_असल(iqs269->slider[i], ABS_X, slider_x[i]);
		पूर्ण अन्यथा अणु
			input_report_key(iqs269->slider[i], BTN_TOUCH, 0);
		पूर्ण

		input_sync(iqs269->slider[i]);
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(iqs269_events); i++) अणु
		dir_mask = flags.states[IQS269_ST_OFFS_सूची];
		अगर (!iqs269_events[i].dir_up)
			dir_mask = ~dir_mask;

		state = flags.states[iqs269_events[i].st_offs] & dir_mask;

		sw_code = iqs269->चयनes[i].code;

		क्रम (j = 0; j < IQS269_NUM_CH; j++) अणु
			keycode = iqs269->keycode[i * IQS269_NUM_CH + j];

			चयन (j) अणु
			हाल IQS269_CHx_HALL_ACTIVE:
				अगर (iqs269->hall_enable &&
				    iqs269->चयनes[i].enabled)
					input_report_चयन(iqs269->keypad,
							    sw_code,
							    state & BIT(j));
				fallthrough;

			हाल IQS269_CHx_HALL_INACTIVE:
				अगर (iqs269->hall_enable)
					जारी;
				fallthrough;

			शेष:
				input_report_key(iqs269->keypad, keycode,
						 state & BIT(j));
			पूर्ण
		पूर्ण
	पूर्ण

	input_sync(iqs269->keypad);

	वापस 0;
पूर्ण

अटल irqवापस_t iqs269_irq(पूर्णांक irq, व्योम *context)
अणु
	काष्ठा iqs269_निजी *iqs269 = context;

	अगर (iqs269_report(iqs269))
		वापस IRQ_NONE;

	/*
	 * The device करोes not deनिश्चित its पूर्णांकerrupt (RDY) pin until लघुly
	 * after receiving an I2C stop condition; the following delay ensures
	 * the पूर्णांकerrupt handler करोes not वापस beक्रमe this समय.
	 */
	iqs269_irq_रुको();

	वापस IRQ_HANDLED;
पूर्ण

अटल sमाप_प्रकार counts_show(काष्ठा device *dev,
			   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा iqs269_निजी *iqs269 = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = iqs269->client;
	__le16 counts;
	पूर्णांक error;

	अगर (!iqs269->ati_current || iqs269->hall_enable)
		वापस -EPERM;

	/*
	 * Unsolicited I2C communication prompts the device to निश्चित its RDY
	 * pin, so disable the पूर्णांकerrupt line until the operation is finished
	 * and RDY has been deनिश्चितed.
	 */
	disable_irq(client->irq);

	error = regmap_raw_पढ़ो(iqs269->regmap,
				IQS269_CHx_COUNTS + iqs269->ch_num * 2,
				&counts, माप(counts));

	iqs269_irq_रुको();
	enable_irq(client->irq);

	अगर (error)
		वापस error;

	वापस scnम_लिखो(buf, PAGE_SIZE, "%u\n", le16_to_cpu(counts));
पूर्ण

अटल sमाप_प्रकार hall_bin_show(काष्ठा device *dev,
			     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा iqs269_निजी *iqs269 = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = iqs269->client;
	अचिन्हित पूर्णांक val;
	पूर्णांक error;

	disable_irq(client->irq);

	error = regmap_पढ़ो(iqs269->regmap, IQS269_CAL_DATA_A, &val);

	iqs269_irq_रुको();
	enable_irq(client->irq);

	अगर (error)
		वापस error;

	चयन (iqs269->ch_reg[IQS269_CHx_HALL_ACTIVE].rx_enable &
		iqs269->ch_reg[IQS269_CHx_HALL_INACTIVE].rx_enable) अणु
	हाल IQS269_HALL_PAD_R:
		val &= IQS269_CAL_DATA_A_HALL_BIN_R_MASK;
		val >>= IQS269_CAL_DATA_A_HALL_BIN_R_SHIFT;
		अवरोध;

	हाल IQS269_HALL_PAD_L:
		val &= IQS269_CAL_DATA_A_HALL_BIN_L_MASK;
		val >>= IQS269_CAL_DATA_A_HALL_BIN_L_SHIFT;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस scnम_लिखो(buf, PAGE_SIZE, "%u\n", val);
पूर्ण

अटल sमाप_प्रकार hall_enable_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा iqs269_निजी *iqs269 = dev_get_drvdata(dev);

	वापस scnम_लिखो(buf, PAGE_SIZE, "%u\n", iqs269->hall_enable);
पूर्ण

अटल sमाप_प्रकार hall_enable_store(काष्ठा device *dev,
				 काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
				 माप_प्रकार count)
अणु
	काष्ठा iqs269_निजी *iqs269 = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक val;
	पूर्णांक error;

	error = kstrtouपूर्णांक(buf, 10, &val);
	अगर (error)
		वापस error;

	mutex_lock(&iqs269->lock);

	iqs269->hall_enable = val;
	iqs269->ati_current = false;

	mutex_unlock(&iqs269->lock);

	वापस count;
पूर्ण

अटल sमाप_प्रकार ch_number_show(काष्ठा device *dev,
			      काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा iqs269_निजी *iqs269 = dev_get_drvdata(dev);

	वापस scnम_लिखो(buf, PAGE_SIZE, "%u\n", iqs269->ch_num);
पूर्ण

अटल sमाप_प्रकार ch_number_store(काष्ठा device *dev,
			       काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
			       माप_प्रकार count)
अणु
	काष्ठा iqs269_निजी *iqs269 = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक val;
	पूर्णांक error;

	error = kstrtouपूर्णांक(buf, 10, &val);
	अगर (error)
		वापस error;

	अगर (val >= IQS269_NUM_CH)
		वापस -EINVAL;

	iqs269->ch_num = val;

	वापस count;
पूर्ण

अटल sमाप_प्रकार rx_enable_show(काष्ठा device *dev,
			      काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा iqs269_निजी *iqs269 = dev_get_drvdata(dev);

	वापस scnम_लिखो(buf, PAGE_SIZE, "%u\n",
			 iqs269->ch_reg[iqs269->ch_num].rx_enable);
पूर्ण

अटल sमाप_प्रकार rx_enable_store(काष्ठा device *dev,
			       काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
			       माप_प्रकार count)
अणु
	काष्ठा iqs269_निजी *iqs269 = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक val;
	पूर्णांक error;

	error = kstrtouपूर्णांक(buf, 10, &val);
	अगर (error)
		वापस error;

	अगर (val > 0xFF)
		वापस -EINVAL;

	mutex_lock(&iqs269->lock);

	iqs269->ch_reg[iqs269->ch_num].rx_enable = val;
	iqs269->ati_current = false;

	mutex_unlock(&iqs269->lock);

	वापस count;
पूर्ण

अटल sमाप_प्रकार ati_mode_show(काष्ठा device *dev,
			     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा iqs269_निजी *iqs269 = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक val;
	पूर्णांक error;

	error = iqs269_ati_mode_get(iqs269, iqs269->ch_num, &val);
	अगर (error)
		वापस error;

	वापस scnम_लिखो(buf, PAGE_SIZE, "%u\n", val);
पूर्ण

अटल sमाप_प्रकार ati_mode_store(काष्ठा device *dev,
			      काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
			      माप_प्रकार count)
अणु
	काष्ठा iqs269_निजी *iqs269 = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक val;
	पूर्णांक error;

	error = kstrtouपूर्णांक(buf, 10, &val);
	अगर (error)
		वापस error;

	error = iqs269_ati_mode_set(iqs269, iqs269->ch_num, val);
	अगर (error)
		वापस error;

	वापस count;
पूर्ण

अटल sमाप_प्रकार ati_base_show(काष्ठा device *dev,
			     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा iqs269_निजी *iqs269 = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक val;
	पूर्णांक error;

	error = iqs269_ati_base_get(iqs269, iqs269->ch_num, &val);
	अगर (error)
		वापस error;

	वापस scnम_लिखो(buf, PAGE_SIZE, "%u\n", val);
पूर्ण

अटल sमाप_प्रकार ati_base_store(काष्ठा device *dev,
			      काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
			      माप_प्रकार count)
अणु
	काष्ठा iqs269_निजी *iqs269 = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक val;
	पूर्णांक error;

	error = kstrtouपूर्णांक(buf, 10, &val);
	अगर (error)
		वापस error;

	error = iqs269_ati_base_set(iqs269, iqs269->ch_num, val);
	अगर (error)
		वापस error;

	वापस count;
पूर्ण

अटल sमाप_प्रकार ati_target_show(काष्ठा device *dev,
			       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा iqs269_निजी *iqs269 = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक val;
	पूर्णांक error;

	error = iqs269_ati_target_get(iqs269, iqs269->ch_num, &val);
	अगर (error)
		वापस error;

	वापस scnम_लिखो(buf, PAGE_SIZE, "%u\n", val);
पूर्ण

अटल sमाप_प्रकार ati_target_store(काष्ठा device *dev,
				काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
				माप_प्रकार count)
अणु
	काष्ठा iqs269_निजी *iqs269 = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक val;
	पूर्णांक error;

	error = kstrtouपूर्णांक(buf, 10, &val);
	अगर (error)
		वापस error;

	error = iqs269_ati_target_set(iqs269, iqs269->ch_num, val);
	अगर (error)
		वापस error;

	वापस count;
पूर्ण

अटल sमाप_प्रकार ati_trigger_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा iqs269_निजी *iqs269 = dev_get_drvdata(dev);

	वापस scnम_लिखो(buf, PAGE_SIZE, "%u\n", iqs269->ati_current);
पूर्ण

अटल sमाप_प्रकार ati_trigger_store(काष्ठा device *dev,
				 काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
				 माप_प्रकार count)
अणु
	काष्ठा iqs269_निजी *iqs269 = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = iqs269->client;
	अचिन्हित पूर्णांक val;
	पूर्णांक error;

	error = kstrtouपूर्णांक(buf, 10, &val);
	अगर (error)
		वापस error;

	अगर (!val)
		वापस count;

	disable_irq(client->irq);

	error = iqs269_dev_init(iqs269);

	iqs269_irq_रुको();
	enable_irq(client->irq);

	अगर (error)
		वापस error;

	वापस count;
पूर्ण

अटल DEVICE_ATTR_RO(counts);
अटल DEVICE_ATTR_RO(hall_bin);
अटल DEVICE_ATTR_RW(hall_enable);
अटल DEVICE_ATTR_RW(ch_number);
अटल DEVICE_ATTR_RW(rx_enable);
अटल DEVICE_ATTR_RW(ati_mode);
अटल DEVICE_ATTR_RW(ati_base);
अटल DEVICE_ATTR_RW(ati_target);
अटल DEVICE_ATTR_RW(ati_trigger);

अटल काष्ठा attribute *iqs269_attrs[] = अणु
	&dev_attr_counts.attr,
	&dev_attr_hall_bin.attr,
	&dev_attr_hall_enable.attr,
	&dev_attr_ch_number.attr,
	&dev_attr_rx_enable.attr,
	&dev_attr_ati_mode.attr,
	&dev_attr_ati_base.attr,
	&dev_attr_ati_target.attr,
	&dev_attr_ati_trigger.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group iqs269_attr_group = अणु
	.attrs = iqs269_attrs,
पूर्ण;

अटल स्थिर काष्ठा regmap_config iqs269_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 16,
	.max_रेजिस्टर = IQS269_MAX_REG,
पूर्ण;

अटल पूर्णांक iqs269_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा iqs269_ver_info ver_info;
	काष्ठा iqs269_निजी *iqs269;
	पूर्णांक error;

	iqs269 = devm_kzalloc(&client->dev, माप(*iqs269), GFP_KERNEL);
	अगर (!iqs269)
		वापस -ENOMEM;

	i2c_set_clientdata(client, iqs269);
	iqs269->client = client;

	iqs269->regmap = devm_regmap_init_i2c(client, &iqs269_regmap_config);
	अगर (IS_ERR(iqs269->regmap)) अणु
		error = PTR_ERR(iqs269->regmap);
		dev_err(&client->dev, "Failed to initialize register map: %d\n",
			error);
		वापस error;
	पूर्ण

	mutex_init(&iqs269->lock);

	error = regmap_raw_पढ़ो(iqs269->regmap, IQS269_VER_INFO, &ver_info,
				माप(ver_info));
	अगर (error)
		वापस error;

	अगर (ver_info.prod_num != IQS269_VER_INFO_PROD_NUM) अणु
		dev_err(&client->dev, "Unrecognized product number: 0x%02X\n",
			ver_info.prod_num);
		वापस -EINVAL;
	पूर्ण

	error = iqs269_parse_prop(iqs269);
	अगर (error)
		वापस error;

	error = iqs269_dev_init(iqs269);
	अगर (error) अणु
		dev_err(&client->dev, "Failed to initialize device: %d\n",
			error);
		वापस error;
	पूर्ण

	error = iqs269_input_init(iqs269);
	अगर (error)
		वापस error;

	error = devm_request_thपढ़ोed_irq(&client->dev, client->irq,
					  शून्य, iqs269_irq, IRQF_ONESHOT,
					  client->name, iqs269);
	अगर (error) अणु
		dev_err(&client->dev, "Failed to request IRQ: %d\n", error);
		वापस error;
	पूर्ण

	error = devm_device_add_group(&client->dev, &iqs269_attr_group);
	अगर (error)
		dev_err(&client->dev, "Failed to add attributes: %d\n", error);

	वापस error;
पूर्ण

अटल पूर्णांक __maybe_unused iqs269_suspend(काष्ठा device *dev)
अणु
	काष्ठा iqs269_निजी *iqs269 = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = iqs269->client;
	अचिन्हित पूर्णांक val;
	पूर्णांक error;

	अगर (!iqs269->suspend_mode)
		वापस 0;

	disable_irq(client->irq);

	/*
	 * Automatic घातer mode चयनing must be disabled beक्रमe the device is
	 * क्रमced पूर्णांकo any particular घातer mode. In this हाल, the device will
	 * transition पूर्णांकo normal-घातer mode.
	 */
	error = regmap_update_bits(iqs269->regmap, IQS269_SYS_SETTINGS,
				   IQS269_SYS_SETTINGS_DIS_AUTO, ~0);
	अगर (error)
		जाओ err_irq;

	/*
	 * The following check ensures the device has completed its transition
	 * पूर्णांकo normal-घातer mode beक्रमe a manual mode चयन is perक्रमmed.
	 */
	error = regmap_पढ़ो_poll_समयout(iqs269->regmap, IQS269_SYS_FLAGS, val,
					!(val & IQS269_SYS_FLAGS_PWR_MODE_MASK),
					 IQS269_PWR_MODE_POLL_SLEEP_US,
					 IQS269_PWR_MODE_POLL_TIMEOUT_US);
	अगर (error)
		जाओ err_irq;

	error = regmap_update_bits(iqs269->regmap, IQS269_SYS_SETTINGS,
				   IQS269_SYS_SETTINGS_PWR_MODE_MASK,
				   iqs269->suspend_mode <<
				   IQS269_SYS_SETTINGS_PWR_MODE_SHIFT);
	अगर (error)
		जाओ err_irq;

	/*
	 * This last check ensures the device has completed its transition पूर्णांकo
	 * the desired घातer mode to prevent any spurious पूर्णांकerrupts from being
	 * triggered after iqs269_suspend has alपढ़ोy वापसed.
	 */
	error = regmap_पढ़ो_poll_समयout(iqs269->regmap, IQS269_SYS_FLAGS, val,
					 (val & IQS269_SYS_FLAGS_PWR_MODE_MASK)
					 == (iqs269->suspend_mode <<
					     IQS269_SYS_FLAGS_PWR_MODE_SHIFT),
					 IQS269_PWR_MODE_POLL_SLEEP_US,
					 IQS269_PWR_MODE_POLL_TIMEOUT_US);

err_irq:
	iqs269_irq_रुको();
	enable_irq(client->irq);

	वापस error;
पूर्ण

अटल पूर्णांक __maybe_unused iqs269_resume(काष्ठा device *dev)
अणु
	काष्ठा iqs269_निजी *iqs269 = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = iqs269->client;
	अचिन्हित पूर्णांक val;
	पूर्णांक error;

	अगर (!iqs269->suspend_mode)
		वापस 0;

	disable_irq(client->irq);

	error = regmap_update_bits(iqs269->regmap, IQS269_SYS_SETTINGS,
				   IQS269_SYS_SETTINGS_PWR_MODE_MASK, 0);
	अगर (error)
		जाओ err_irq;

	/*
	 * This check ensures the device has वापसed to normal-घातer mode
	 * beक्रमe स्वतःmatic घातer mode चयनing is re-enabled.
	 */
	error = regmap_पढ़ो_poll_समयout(iqs269->regmap, IQS269_SYS_FLAGS, val,
					!(val & IQS269_SYS_FLAGS_PWR_MODE_MASK),
					 IQS269_PWR_MODE_POLL_SLEEP_US,
					 IQS269_PWR_MODE_POLL_TIMEOUT_US);
	अगर (error)
		जाओ err_irq;

	error = regmap_update_bits(iqs269->regmap, IQS269_SYS_SETTINGS,
				   IQS269_SYS_SETTINGS_DIS_AUTO, 0);
	अगर (error)
		जाओ err_irq;

	/*
	 * This step reports any events that may have been "swallowed" as a
	 * result of polling PWR_MODE (which स्वतःmatically acknowledges any
	 * pending पूर्णांकerrupts).
	 */
	error = iqs269_report(iqs269);

err_irq:
	iqs269_irq_रुको();
	enable_irq(client->irq);

	वापस error;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(iqs269_pm, iqs269_suspend, iqs269_resume);

अटल स्थिर काष्ठा of_device_id iqs269_of_match[] = अणु
	अणु .compatible = "azoteq,iqs269a" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, iqs269_of_match);

अटल काष्ठा i2c_driver iqs269_i2c_driver = अणु
	.driver = अणु
		.name = "iqs269a",
		.of_match_table = iqs269_of_match,
		.pm = &iqs269_pm,
	पूर्ण,
	.probe_new = iqs269_probe,
पूर्ण;
module_i2c_driver(iqs269_i2c_driver);

MODULE_AUTHOR("Jeff LaBundy <jeff@labundy.com>");
MODULE_DESCRIPTION("Azoteq IQS269A Capacitive Touch Controller");
MODULE_LICENSE("GPL");
