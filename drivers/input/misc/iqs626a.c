<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Azoteq IQS626A Capacitive Touch Controller
 *
 * Copyright (C) 2020 Jeff LaBundy <jeff@labundy.com>
 *
 * This driver रेजिस्टरs up to 2 input devices: one representing capacitive or
 * inductive keys as well as Hall-effect चयनes, and one क्रम a trackpad that
 * can express various gestures.
 */

#समावेश <linux/bits.h>
#समावेश <linux/completion.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/i2c.h>
#समावेश <linux/input.h>
#समावेश <linux/input/touchscreen.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/property.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>

#घोषणा IQS626_VER_INFO				0x00
#घोषणा IQS626_VER_INFO_PROD_NUM		0x51

#घोषणा IQS626_SYS_FLAGS			0x02
#घोषणा IQS626_SYS_FLAGS_SHOW_RESET		BIT(15)
#घोषणा IQS626_SYS_FLAGS_IN_ATI			BIT(12)
#घोषणा IQS626_SYS_FLAGS_PWR_MODE_MASK		GENMASK(9, 8)
#घोषणा IQS626_SYS_FLAGS_PWR_MODE_SHIFT		8

#घोषणा IQS626_HALL_OUTPUT			0x23

#घोषणा IQS626_SYS_SETTINGS			0x80
#घोषणा IQS626_SYS_SETTINGS_CLK_DIV		BIT(15)
#घोषणा IQS626_SYS_SETTINGS_ULP_AUTO		BIT(14)
#घोषणा IQS626_SYS_SETTINGS_DIS_AUTO		BIT(13)
#घोषणा IQS626_SYS_SETTINGS_PWR_MODE_MASK	GENMASK(12, 11)
#घोषणा IQS626_SYS_SETTINGS_PWR_MODE_SHIFT	11
#घोषणा IQS626_SYS_SETTINGS_PWR_MODE_MAX	3
#घोषणा IQS626_SYS_SETTINGS_ULP_UPDATE_MASK	GENMASK(10, 8)
#घोषणा IQS626_SYS_SETTINGS_ULP_UPDATE_SHIFT	8
#घोषणा IQS626_SYS_SETTINGS_ULP_UPDATE_MAX	7
#घोषणा IQS626_SYS_SETTINGS_EVENT_MODE		BIT(5)
#घोषणा IQS626_SYS_SETTINGS_EVENT_MODE_LP	BIT(4)
#घोषणा IQS626_SYS_SETTINGS_REDO_ATI		BIT(2)
#घोषणा IQS626_SYS_SETTINGS_ACK_RESET		BIT(0)

#घोषणा IQS626_MISC_A_ATI_BAND_DISABLE		BIT(7)
#घोषणा IQS626_MISC_A_TPx_LTA_UPDATE_MASK	GENMASK(6, 4)
#घोषणा IQS626_MISC_A_TPx_LTA_UPDATE_SHIFT	4
#घोषणा IQS626_MISC_A_TPx_LTA_UPDATE_MAX	7
#घोषणा IQS626_MISC_A_ATI_LP_ONLY		BIT(3)
#घोषणा IQS626_MISC_A_GPIO3_SELECT_MASK		GENMASK(2, 0)
#घोषणा IQS626_MISC_A_GPIO3_SELECT_MAX		7

#घोषणा IQS626_EVENT_MASK_SYS			BIT(6)
#घोषणा IQS626_EVENT_MASK_GESTURE		BIT(3)
#घोषणा IQS626_EVENT_MASK_DEEP			BIT(2)
#घोषणा IQS626_EVENT_MASK_TOUCH			BIT(1)
#घोषणा IQS626_EVENT_MASK_PROX			BIT(0)

#घोषणा IQS626_RATE_NP_MS_MAX			255
#घोषणा IQS626_RATE_LP_MS_MAX			255
#घोषणा IQS626_RATE_ULP_MS_MAX			4080
#घोषणा IQS626_TIMEOUT_PWR_MS_MAX		130560
#घोषणा IQS626_TIMEOUT_LTA_MS_MAX		130560

#घोषणा IQS626_MISC_B_RESEED_UI_SEL_MASK	GENMASK(7, 6)
#घोषणा IQS626_MISC_B_RESEED_UI_SEL_SHIFT	6
#घोषणा IQS626_MISC_B_RESEED_UI_SEL_MAX		3
#घोषणा IQS626_MISC_B_THRESH_EXTEND		BIT(5)
#घोषणा IQS626_MISC_B_TRACKING_UI_ENABLE	BIT(4)
#घोषणा IQS626_MISC_B_TPx_SWIPE			BIT(3)
#घोषणा IQS626_MISC_B_RESEED_OFFSET		BIT(2)
#घोषणा IQS626_MISC_B_FILT_STR_TPx		GENMASK(1, 0)

#घोषणा IQS626_THRESH_SWIPE_MAX			255
#घोषणा IQS626_TIMEOUT_TAP_MS_MAX		4080
#घोषणा IQS626_TIMEOUT_SWIPE_MS_MAX		4080

#घोषणा IQS626_CHx_ENG_0_MEAS_CAP_SIZE		BIT(7)
#घोषणा IQS626_CHx_ENG_0_RX_TERM_VSS		BIT(5)
#घोषणा IQS626_CHx_ENG_0_LINEARIZE		BIT(4)
#घोषणा IQS626_CHx_ENG_0_DUAL_सूची		BIT(3)
#घोषणा IQS626_CHx_ENG_0_FILT_DISABLE		BIT(2)
#घोषणा IQS626_CHx_ENG_0_ATI_MODE_MASK		GENMASK(1, 0)
#घोषणा IQS626_CHx_ENG_0_ATI_MODE_MAX		3

#घोषणा IQS626_CHx_ENG_1_CCT_HIGH_1		BIT(7)
#घोषणा IQS626_CHx_ENG_1_CCT_HIGH_0		BIT(6)
#घोषणा IQS626_CHx_ENG_1_PROJ_BIAS_MASK		GENMASK(5, 4)
#घोषणा IQS626_CHx_ENG_1_PROJ_BIAS_SHIFT	4
#घोषणा IQS626_CHx_ENG_1_PROJ_BIAS_MAX		3
#घोषणा IQS626_CHx_ENG_1_CCT_ENABLE		BIT(3)
#घोषणा IQS626_CHx_ENG_1_SENSE_FREQ_MASK	GENMASK(2, 1)
#घोषणा IQS626_CHx_ENG_1_SENSE_FREQ_SHIFT	1
#घोषणा IQS626_CHx_ENG_1_SENSE_FREQ_MAX		3
#घोषणा IQS626_CHx_ENG_1_ATI_BAND_TIGHTEN	BIT(0)

#घोषणा IQS626_CHx_ENG_2_LOCAL_CAP_MASK		GENMASK(7, 6)
#घोषणा IQS626_CHx_ENG_2_LOCAL_CAP_SHIFT	6
#घोषणा IQS626_CHx_ENG_2_LOCAL_CAP_MAX		3
#घोषणा IQS626_CHx_ENG_2_LOCAL_CAP_ENABLE	BIT(5)
#घोषणा IQS626_CHx_ENG_2_SENSE_MODE_MASK	GENMASK(3, 0)
#घोषणा IQS626_CHx_ENG_2_SENSE_MODE_MAX		15

#घोषणा IQS626_CHx_ENG_3_TX_FREQ_MASK		GENMASK(5, 4)
#घोषणा IQS626_CHx_ENG_3_TX_FREQ_SHIFT		4
#घोषणा IQS626_CHx_ENG_3_TX_FREQ_MAX		3
#घोषणा IQS626_CHx_ENG_3_INV_LOGIC		BIT(0)

#घोषणा IQS626_CHx_ENG_4_RX_TERM_VREG		BIT(6)
#घोषणा IQS626_CHx_ENG_4_CCT_LOW_1		BIT(5)
#घोषणा IQS626_CHx_ENG_4_CCT_LOW_0		BIT(4)
#घोषणा IQS626_CHx_ENG_4_COMP_DISABLE		BIT(1)
#घोषणा IQS626_CHx_ENG_4_STATIC_ENABLE		BIT(0)

#घोषणा IQS626_TPx_ATI_BASE_MIN			45
#घोषणा IQS626_TPx_ATI_BASE_MAX			300
#घोषणा IQS626_CHx_ATI_BASE_MASK		GENMASK(7, 6)
#घोषणा IQS626_CHx_ATI_BASE_75			0x00
#घोषणा IQS626_CHx_ATI_BASE_100			0x40
#घोषणा IQS626_CHx_ATI_BASE_150			0x80
#घोषणा IQS626_CHx_ATI_BASE_200			0xC0
#घोषणा IQS626_CHx_ATI_TARGET_MASK		GENMASK(5, 0)
#घोषणा IQS626_CHx_ATI_TARGET_MAX		2016

#घोषणा IQS626_CHx_THRESH_MAX			255
#घोषणा IQS626_CHx_HYST_DEEP_MASK		GENMASK(7, 4)
#घोषणा IQS626_CHx_HYST_DEEP_SHIFT		4
#घोषणा IQS626_CHx_HYST_TOUCH_MASK		GENMASK(3, 0)
#घोषणा IQS626_CHx_HYST_MAX			15

#घोषणा IQS626_FILT_STR_NP_TPx_MASK		GENMASK(7, 6)
#घोषणा IQS626_FILT_STR_NP_TPx_SHIFT		6
#घोषणा IQS626_FILT_STR_LP_TPx_MASK		GENMASK(5, 4)
#घोषणा IQS626_FILT_STR_LP_TPx_SHIFT		4

#घोषणा IQS626_FILT_STR_NP_CNT_MASK		GENMASK(7, 6)
#घोषणा IQS626_FILT_STR_NP_CNT_SHIFT		6
#घोषणा IQS626_FILT_STR_LP_CNT_MASK		GENMASK(5, 4)
#घोषणा IQS626_FILT_STR_LP_CNT_SHIFT		4
#घोषणा IQS626_FILT_STR_NP_LTA_MASK		GENMASK(3, 2)
#घोषणा IQS626_FILT_STR_NP_LTA_SHIFT		2
#घोषणा IQS626_FILT_STR_LP_LTA_MASK		GENMASK(1, 0)
#घोषणा IQS626_FILT_STR_MAX			3

#घोषणा IQS626_ULP_PROJ_ENABLE			BIT(4)
#घोषणा IQS626_GEN_WEIGHT_MAX			255

#घोषणा IQS626_MAX_REG				0xFF

#घोषणा IQS626_NUM_CH_TP_3			9
#घोषणा IQS626_NUM_CH_TP_2			6
#घोषणा IQS626_NUM_CH_GEN			3
#घोषणा IQS626_NUM_CRx_TX			8

#घोषणा IQS626_PWR_MODE_POLL_SLEEP_US		50000
#घोषणा IQS626_PWR_MODE_POLL_TIMEOUT_US		500000

#घोषणा iqs626_irq_रुको()			usleep_range(350, 400)

क्रमागत iqs626_ch_id अणु
	IQS626_CH_ULP_0,
	IQS626_CH_TP_2,
	IQS626_CH_TP_3,
	IQS626_CH_GEN_0,
	IQS626_CH_GEN_1,
	IQS626_CH_GEN_2,
	IQS626_CH_HALL,
पूर्ण;

क्रमागत iqs626_rx_inactive अणु
	IQS626_RX_INACTIVE_VSS,
	IQS626_RX_INACTIVE_FLOAT,
	IQS626_RX_INACTIVE_VREG,
पूर्ण;

क्रमागत iqs626_st_offs अणु
	IQS626_ST_OFFS_PROX,
	IQS626_ST_OFFS_सूची,
	IQS626_ST_OFFS_TOUCH,
	IQS626_ST_OFFS_DEEP,
पूर्ण;

क्रमागत iqs626_th_offs अणु
	IQS626_TH_OFFS_PROX,
	IQS626_TH_OFFS_TOUCH,
	IQS626_TH_OFFS_DEEP,
पूर्ण;

क्रमागत iqs626_event_id अणु
	IQS626_EVENT_PROX_DN,
	IQS626_EVENT_PROX_UP,
	IQS626_EVENT_TOUCH_DN,
	IQS626_EVENT_TOUCH_UP,
	IQS626_EVENT_DEEP_DN,
	IQS626_EVENT_DEEP_UP,
पूर्ण;

क्रमागत iqs626_gesture_id अणु
	IQS626_GESTURE_FLICK_X_POS,
	IQS626_GESTURE_FLICK_X_NEG,
	IQS626_GESTURE_FLICK_Y_POS,
	IQS626_GESTURE_FLICK_Y_NEG,
	IQS626_GESTURE_TAP,
	IQS626_GESTURE_HOLD,
	IQS626_NUM_GESTURES,
पूर्ण;

काष्ठा iqs626_event_desc अणु
	स्थिर अक्षर *name;
	क्रमागत iqs626_st_offs st_offs;
	क्रमागत iqs626_th_offs th_offs;
	bool dir_up;
	u8 mask;
पूर्ण;

अटल स्थिर काष्ठा iqs626_event_desc iqs626_events[] = अणु
	[IQS626_EVENT_PROX_DN] = अणु
		.name = "event-prox",
		.st_offs = IQS626_ST_OFFS_PROX,
		.th_offs = IQS626_TH_OFFS_PROX,
		.mask = IQS626_EVENT_MASK_PROX,
	पूर्ण,
	[IQS626_EVENT_PROX_UP] = अणु
		.name = "event-prox-alt",
		.st_offs = IQS626_ST_OFFS_PROX,
		.th_offs = IQS626_TH_OFFS_PROX,
		.dir_up = true,
		.mask = IQS626_EVENT_MASK_PROX,
	पूर्ण,
	[IQS626_EVENT_TOUCH_DN] = अणु
		.name = "event-touch",
		.st_offs = IQS626_ST_OFFS_TOUCH,
		.th_offs = IQS626_TH_OFFS_TOUCH,
		.mask = IQS626_EVENT_MASK_TOUCH,
	पूर्ण,
	[IQS626_EVENT_TOUCH_UP] = अणु
		.name = "event-touch-alt",
		.st_offs = IQS626_ST_OFFS_TOUCH,
		.th_offs = IQS626_TH_OFFS_TOUCH,
		.dir_up = true,
		.mask = IQS626_EVENT_MASK_TOUCH,
	पूर्ण,
	[IQS626_EVENT_DEEP_DN] = अणु
		.name = "event-deep",
		.st_offs = IQS626_ST_OFFS_DEEP,
		.th_offs = IQS626_TH_OFFS_DEEP,
		.mask = IQS626_EVENT_MASK_DEEP,
	पूर्ण,
	[IQS626_EVENT_DEEP_UP] = अणु
		.name = "event-deep-alt",
		.st_offs = IQS626_ST_OFFS_DEEP,
		.th_offs = IQS626_TH_OFFS_DEEP,
		.dir_up = true,
		.mask = IQS626_EVENT_MASK_DEEP,
	पूर्ण,
पूर्ण;

काष्ठा iqs626_ver_info अणु
	u8 prod_num;
	u8 sw_num;
	u8 hw_num;
	u8 padding;
पूर्ण __packed;

काष्ठा iqs626_flags अणु
	__be16 प्रणाली;
	u8 gesture;
	u8 padding_a;
	u8 states[4];
	u8 ref_active;
	u8 padding_b;
	u8 comp_min;
	u8 comp_max;
	u8 trackpad_x;
	u8 trackpad_y;
पूर्ण __packed;

काष्ठा iqs626_ch_reg_ulp अणु
	u8 thresh[2];
	u8 hyst;
	u8 filter;
	u8 engine[2];
	u8 ati_target;
	u8 padding;
	__be16 ati_comp;
	u8 rx_enable;
	u8 tx_enable;
पूर्ण __packed;

काष्ठा iqs626_ch_reg_tp अणु
	u8 thresh;
	u8 ati_base;
	__be16 ati_comp;
पूर्ण __packed;

काष्ठा iqs626_tp_grp_reg अणु
	u8 hyst;
	u8 ati_target;
	u8 engine[2];
	काष्ठा iqs626_ch_reg_tp ch_reg_tp[IQS626_NUM_CH_TP_3];
पूर्ण __packed;

काष्ठा iqs626_ch_reg_gen अणु
	u8 thresh[3];
	u8 padding;
	u8 hyst;
	u8 ati_target;
	__be16 ati_comp;
	u8 engine[5];
	u8 filter;
	u8 rx_enable;
	u8 tx_enable;
	u8 assoc_select;
	u8 assoc_weight;
पूर्ण __packed;

काष्ठा iqs626_ch_reg_hall अणु
	u8 engine;
	u8 thresh;
	u8 hyst;
	u8 ati_target;
	__be16 ati_comp;
पूर्ण __packed;

काष्ठा iqs626_sys_reg अणु
	__be16 general;
	u8 misc_a;
	u8 event_mask;
	u8 active;
	u8 reseed;
	u8 rate_np;
	u8 rate_lp;
	u8 rate_ulp;
	u8 समयout_pwr;
	u8 समयout_rdy;
	u8 समयout_lta;
	u8 misc_b;
	u8 thresh_swipe;
	u8 समयout_tap;
	u8 समयout_swipe;
	u8 reकरो_ati;
	u8 padding;
	काष्ठा iqs626_ch_reg_ulp ch_reg_ulp;
	काष्ठा iqs626_tp_grp_reg tp_grp_reg;
	काष्ठा iqs626_ch_reg_gen ch_reg_gen[IQS626_NUM_CH_GEN];
	काष्ठा iqs626_ch_reg_hall ch_reg_hall;
पूर्ण __packed;

काष्ठा iqs626_channel_desc अणु
	स्थिर अक्षर *name;
	पूर्णांक num_ch;
	u8 active;
	bool events[ARRAY_SIZE(iqs626_events)];
पूर्ण;

अटल स्थिर काष्ठा iqs626_channel_desc iqs626_channels[] = अणु
	[IQS626_CH_ULP_0] = अणु
		.name = "ulp-0",
		.num_ch = 1,
		.active = BIT(0),
		.events = अणु
			[IQS626_EVENT_PROX_DN] = true,
			[IQS626_EVENT_PROX_UP] = true,
			[IQS626_EVENT_TOUCH_DN] = true,
			[IQS626_EVENT_TOUCH_UP] = true,
		पूर्ण,
	पूर्ण,
	[IQS626_CH_TP_2] = अणु
		.name = "trackpad-3x2",
		.num_ch = IQS626_NUM_CH_TP_2,
		.active = BIT(1),
		.events = अणु
			[IQS626_EVENT_TOUCH_DN] = true,
		पूर्ण,
	पूर्ण,
	[IQS626_CH_TP_3] = अणु
		.name = "trackpad-3x3",
		.num_ch = IQS626_NUM_CH_TP_3,
		.active = BIT(2) | BIT(1),
		.events = अणु
			[IQS626_EVENT_TOUCH_DN] = true,
		पूर्ण,
	पूर्ण,
	[IQS626_CH_GEN_0] = अणु
		.name = "generic-0",
		.num_ch = 1,
		.active = BIT(4),
		.events = अणु
			[IQS626_EVENT_PROX_DN] = true,
			[IQS626_EVENT_PROX_UP] = true,
			[IQS626_EVENT_TOUCH_DN] = true,
			[IQS626_EVENT_TOUCH_UP] = true,
			[IQS626_EVENT_DEEP_DN] = true,
			[IQS626_EVENT_DEEP_UP] = true,
		पूर्ण,
	पूर्ण,
	[IQS626_CH_GEN_1] = अणु
		.name = "generic-1",
		.num_ch = 1,
		.active = BIT(5),
		.events = अणु
			[IQS626_EVENT_PROX_DN] = true,
			[IQS626_EVENT_PROX_UP] = true,
			[IQS626_EVENT_TOUCH_DN] = true,
			[IQS626_EVENT_TOUCH_UP] = true,
			[IQS626_EVENT_DEEP_DN] = true,
			[IQS626_EVENT_DEEP_UP] = true,
		पूर्ण,
	पूर्ण,
	[IQS626_CH_GEN_2] = अणु
		.name = "generic-2",
		.num_ch = 1,
		.active = BIT(6),
		.events = अणु
			[IQS626_EVENT_PROX_DN] = true,
			[IQS626_EVENT_PROX_UP] = true,
			[IQS626_EVENT_TOUCH_DN] = true,
			[IQS626_EVENT_TOUCH_UP] = true,
			[IQS626_EVENT_DEEP_DN] = true,
			[IQS626_EVENT_DEEP_UP] = true,
		पूर्ण,
	पूर्ण,
	[IQS626_CH_HALL] = अणु
		.name = "hall",
		.num_ch = 1,
		.active = BIT(7),
		.events = अणु
			[IQS626_EVENT_TOUCH_DN] = true,
			[IQS626_EVENT_TOUCH_UP] = true,
		पूर्ण,
	पूर्ण,
पूर्ण;

काष्ठा iqs626_निजी अणु
	काष्ठा i2c_client *client;
	काष्ठा regmap *regmap;
	काष्ठा iqs626_sys_reg sys_reg;
	काष्ठा completion ati_करोne;
	काष्ठा input_dev *keypad;
	काष्ठा input_dev *trackpad;
	काष्ठा touchscreen_properties prop;
	अचिन्हित पूर्णांक kp_type[ARRAY_SIZE(iqs626_channels)]
			    [ARRAY_SIZE(iqs626_events)];
	अचिन्हित पूर्णांक kp_code[ARRAY_SIZE(iqs626_channels)]
			    [ARRAY_SIZE(iqs626_events)];
	अचिन्हित पूर्णांक tp_code[IQS626_NUM_GESTURES];
	अचिन्हित पूर्णांक suspend_mode;
पूर्ण;

अटल पूर्णांक iqs626_parse_events(काष्ठा iqs626_निजी *iqs626,
			       स्थिर काष्ठा fwnode_handle *ch_node,
			       क्रमागत iqs626_ch_id ch_id)
अणु
	काष्ठा iqs626_sys_reg *sys_reg = &iqs626->sys_reg;
	काष्ठा i2c_client *client = iqs626->client;
	स्थिर काष्ठा fwnode_handle *ev_node;
	स्थिर अक्षर *ev_name;
	u8 *thresh, *hyst;
	अचिन्हित पूर्णांक thresh_tp[IQS626_NUM_CH_TP_3];
	अचिन्हित पूर्णांक val;
	पूर्णांक num_ch = iqs626_channels[ch_id].num_ch;
	पूर्णांक error, i, j;

	चयन (ch_id) अणु
	हाल IQS626_CH_ULP_0:
		thresh = sys_reg->ch_reg_ulp.thresh;
		hyst = &sys_reg->ch_reg_ulp.hyst;
		अवरोध;

	हाल IQS626_CH_TP_2:
	हाल IQS626_CH_TP_3:
		thresh = &sys_reg->tp_grp_reg.ch_reg_tp[0].thresh;
		hyst = &sys_reg->tp_grp_reg.hyst;
		अवरोध;

	हाल IQS626_CH_GEN_0:
	हाल IQS626_CH_GEN_1:
	हाल IQS626_CH_GEN_2:
		i = ch_id - IQS626_CH_GEN_0;
		thresh = sys_reg->ch_reg_gen[i].thresh;
		hyst = &sys_reg->ch_reg_gen[i].hyst;
		अवरोध;

	हाल IQS626_CH_HALL:
		thresh = &sys_reg->ch_reg_hall.thresh;
		hyst = &sys_reg->ch_reg_hall.hyst;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(iqs626_events); i++) अणु
		अगर (!iqs626_channels[ch_id].events[i])
			जारी;

		अगर (ch_id == IQS626_CH_TP_2 || ch_id == IQS626_CH_TP_3) अणु
			/*
			 * Trackpad touch events are simply described under the
			 * trackpad child node.
			 */
			ev_node = ch_node;
		पूर्ण अन्यथा अणु
			ev_name = iqs626_events[i].name;
			ev_node = fwnode_get_named_child_node(ch_node, ev_name);
			अगर (!ev_node)
				जारी;

			अगर (!fwnode_property_पढ़ो_u32(ev_node, "linux,code",
						      &val)) अणु
				iqs626->kp_code[ch_id][i] = val;

				अगर (fwnode_property_पढ़ो_u32(ev_node,
							     "linux,input-type",
							     &val)) अणु
					अगर (ch_id == IQS626_CH_HALL)
						val = EV_SW;
					अन्यथा
						val = EV_KEY;
				पूर्ण

				अगर (val != EV_KEY && val != EV_SW) अणु
					dev_err(&client->dev,
						"Invalid input type: %u\n",
						val);
					वापस -EINVAL;
				पूर्ण

				iqs626->kp_type[ch_id][i] = val;

				sys_reg->event_mask &= ~iqs626_events[i].mask;
			पूर्ण
		पूर्ण

		अगर (!fwnode_property_पढ़ो_u32(ev_node, "azoteq,hyst", &val)) अणु
			अगर (val > IQS626_CHx_HYST_MAX) अणु
				dev_err(&client->dev,
					"Invalid %s channel hysteresis: %u\n",
					fwnode_get_name(ch_node), val);
				वापस -EINVAL;
			पूर्ण

			अगर (i == IQS626_EVENT_DEEP_DN ||
			    i == IQS626_EVENT_DEEP_UP) अणु
				*hyst &= ~IQS626_CHx_HYST_DEEP_MASK;
				*hyst |= (val << IQS626_CHx_HYST_DEEP_SHIFT);
			पूर्ण अन्यथा अगर (i == IQS626_EVENT_TOUCH_DN ||
				   i == IQS626_EVENT_TOUCH_UP) अणु
				*hyst &= ~IQS626_CHx_HYST_TOUCH_MASK;
				*hyst |= val;
			पूर्ण
		पूर्ण

		अगर (ch_id != IQS626_CH_TP_2 && ch_id != IQS626_CH_TP_3 &&
		    !fwnode_property_पढ़ो_u32(ev_node, "azoteq,thresh", &val)) अणु
			अगर (val > IQS626_CHx_THRESH_MAX) अणु
				dev_err(&client->dev,
					"Invalid %s channel threshold: %u\n",
					fwnode_get_name(ch_node), val);
				वापस -EINVAL;
			पूर्ण

			अगर (ch_id == IQS626_CH_HALL)
				*thresh = val;
			अन्यथा
				*(thresh + iqs626_events[i].th_offs) = val;

			जारी;
		पूर्ण

		अगर (!fwnode_property_present(ev_node, "azoteq,thresh"))
			जारी;

		error = fwnode_property_पढ़ो_u32_array(ev_node, "azoteq,thresh",
						       thresh_tp, num_ch);
		अगर (error) अणु
			dev_err(&client->dev,
				"Failed to read %s channel thresholds: %d\n",
				fwnode_get_name(ch_node), error);
			वापस error;
		पूर्ण

		क्रम (j = 0; j < num_ch; j++) अणु
			अगर (thresh_tp[j] > IQS626_CHx_THRESH_MAX) अणु
				dev_err(&client->dev,
					"Invalid %s channel threshold: %u\n",
					fwnode_get_name(ch_node), thresh_tp[j]);
				वापस -EINVAL;
			पूर्ण

			sys_reg->tp_grp_reg.ch_reg_tp[j].thresh = thresh_tp[j];
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक iqs626_parse_ati_target(काष्ठा iqs626_निजी *iqs626,
				   स्थिर काष्ठा fwnode_handle *ch_node,
				   क्रमागत iqs626_ch_id ch_id)
अणु
	काष्ठा iqs626_sys_reg *sys_reg = &iqs626->sys_reg;
	काष्ठा i2c_client *client = iqs626->client;
	अचिन्हित पूर्णांक ati_base[IQS626_NUM_CH_TP_3];
	अचिन्हित पूर्णांक val;
	u8 *ati_target;
	पूर्णांक num_ch = iqs626_channels[ch_id].num_ch;
	पूर्णांक error, i;

	चयन (ch_id) अणु
	हाल IQS626_CH_ULP_0:
		ati_target = &sys_reg->ch_reg_ulp.ati_target;
		अवरोध;

	हाल IQS626_CH_TP_2:
	हाल IQS626_CH_TP_3:
		ati_target = &sys_reg->tp_grp_reg.ati_target;
		अवरोध;

	हाल IQS626_CH_GEN_0:
	हाल IQS626_CH_GEN_1:
	हाल IQS626_CH_GEN_2:
		i = ch_id - IQS626_CH_GEN_0;
		ati_target = &sys_reg->ch_reg_gen[i].ati_target;
		अवरोध;

	हाल IQS626_CH_HALL:
		ati_target = &sys_reg->ch_reg_hall.ati_target;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (!fwnode_property_पढ़ो_u32(ch_node, "azoteq,ati-target", &val)) अणु
		अगर (val > IQS626_CHx_ATI_TARGET_MAX) अणु
			dev_err(&client->dev,
				"Invalid %s channel ATI target: %u\n",
				fwnode_get_name(ch_node), val);
			वापस -EINVAL;
		पूर्ण

		*ati_target &= ~IQS626_CHx_ATI_TARGET_MASK;
		*ati_target |= (val / 32);
	पूर्ण

	अगर (ch_id != IQS626_CH_TP_2 && ch_id != IQS626_CH_TP_3 &&
	    !fwnode_property_पढ़ो_u32(ch_node, "azoteq,ati-base", &val)) अणु
		चयन (val) अणु
		हाल 75:
			val = IQS626_CHx_ATI_BASE_75;
			अवरोध;

		हाल 100:
			val = IQS626_CHx_ATI_BASE_100;
			अवरोध;

		हाल 150:
			val = IQS626_CHx_ATI_BASE_150;
			अवरोध;

		हाल 200:
			val = IQS626_CHx_ATI_BASE_200;
			अवरोध;

		शेष:
			dev_err(&client->dev,
				"Invalid %s channel ATI base: %u\n",
				fwnode_get_name(ch_node), val);
			वापस -EINVAL;
		पूर्ण

		*ati_target &= ~IQS626_CHx_ATI_BASE_MASK;
		*ati_target |= val;

		वापस 0;
	पूर्ण

	अगर (!fwnode_property_present(ch_node, "azoteq,ati-base"))
		वापस 0;

	error = fwnode_property_पढ़ो_u32_array(ch_node, "azoteq,ati-base",
					       ati_base, num_ch);
	अगर (error) अणु
		dev_err(&client->dev,
			"Failed to read %s channel ATI bases: %d\n",
			fwnode_get_name(ch_node), error);
		वापस error;
	पूर्ण

	क्रम (i = 0; i < num_ch; i++) अणु
		अगर (ati_base[i] < IQS626_TPx_ATI_BASE_MIN ||
		    ati_base[i] > IQS626_TPx_ATI_BASE_MAX) अणु
			dev_err(&client->dev,
				"Invalid %s channel ATI base: %u\n",
				fwnode_get_name(ch_node), ati_base[i]);
			वापस -EINVAL;
		पूर्ण

		ati_base[i] -= IQS626_TPx_ATI_BASE_MIN;
		sys_reg->tp_grp_reg.ch_reg_tp[i].ati_base = ati_base[i];
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक iqs626_parse_pins(काष्ठा iqs626_निजी *iqs626,
			     स्थिर काष्ठा fwnode_handle *ch_node,
			     स्थिर अक्षर *propname, u8 *enable)
अणु
	काष्ठा i2c_client *client = iqs626->client;
	अचिन्हित पूर्णांक val[IQS626_NUM_CRx_TX];
	पूर्णांक error, count, i;

	अगर (!fwnode_property_present(ch_node, propname))
		वापस 0;

	count = fwnode_property_count_u32(ch_node, propname);
	अगर (count > IQS626_NUM_CRx_TX) अणु
		dev_err(&client->dev,
			"Too many %s channel CRX/TX pins present\n",
			fwnode_get_name(ch_node));
		वापस -EINVAL;
	पूर्ण अन्यथा अगर (count < 0) अणु
		dev_err(&client->dev,
			"Failed to count %s channel CRX/TX pins: %d\n",
			fwnode_get_name(ch_node), count);
		वापस count;
	पूर्ण

	error = fwnode_property_पढ़ो_u32_array(ch_node, propname, val, count);
	अगर (error) अणु
		dev_err(&client->dev,
			"Failed to read %s channel CRX/TX pins: %d\n",
			fwnode_get_name(ch_node), error);
		वापस error;
	पूर्ण

	*enable = 0;

	क्रम (i = 0; i < count; i++) अणु
		अगर (val[i] >= IQS626_NUM_CRx_TX) अणु
			dev_err(&client->dev,
				"Invalid %s channel CRX/TX pin: %u\n",
				fwnode_get_name(ch_node), val[i]);
			वापस -EINVAL;
		पूर्ण

		*enable |= BIT(val[i]);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक iqs626_parse_trackpad(काष्ठा iqs626_निजी *iqs626,
				 स्थिर काष्ठा fwnode_handle *ch_node)
अणु
	काष्ठा iqs626_sys_reg *sys_reg = &iqs626->sys_reg;
	काष्ठा i2c_client *client = iqs626->client;
	u8 *hyst = &sys_reg->tp_grp_reg.hyst;
	अचिन्हित पूर्णांक val;
	पूर्णांक error, count;

	अगर (!fwnode_property_पढ़ो_u32(ch_node, "azoteq,lta-update", &val)) अणु
		अगर (val > IQS626_MISC_A_TPx_LTA_UPDATE_MAX) अणु
			dev_err(&client->dev,
				"Invalid %s channel update rate: %u\n",
				fwnode_get_name(ch_node), val);
			वापस -EINVAL;
		पूर्ण

		sys_reg->misc_a &= ~IQS626_MISC_A_TPx_LTA_UPDATE_MASK;
		sys_reg->misc_a |= (val << IQS626_MISC_A_TPx_LTA_UPDATE_SHIFT);
	पूर्ण

	अगर (!fwnode_property_पढ़ो_u32(ch_node, "azoteq,filt-str-trackpad",
				      &val)) अणु
		अगर (val > IQS626_FILT_STR_MAX) अणु
			dev_err(&client->dev,
				"Invalid %s channel filter strength: %u\n",
				fwnode_get_name(ch_node), val);
			वापस -EINVAL;
		पूर्ण

		sys_reg->misc_b &= ~IQS626_MISC_B_FILT_STR_TPx;
		sys_reg->misc_b |= val;
	पूर्ण

	अगर (!fwnode_property_पढ़ो_u32(ch_node, "azoteq,filt-str-np-cnt",
				      &val)) अणु
		अगर (val > IQS626_FILT_STR_MAX) अणु
			dev_err(&client->dev,
				"Invalid %s channel filter strength: %u\n",
				fwnode_get_name(ch_node), val);
			वापस -EINVAL;
		पूर्ण

		*hyst &= ~IQS626_FILT_STR_NP_TPx_MASK;
		*hyst |= (val << IQS626_FILT_STR_NP_TPx_SHIFT);
	पूर्ण

	अगर (!fwnode_property_पढ़ो_u32(ch_node, "azoteq,filt-str-lp-cnt",
				      &val)) अणु
		अगर (val > IQS626_FILT_STR_MAX) अणु
			dev_err(&client->dev,
				"Invalid %s channel filter strength: %u\n",
				fwnode_get_name(ch_node), val);
			वापस -EINVAL;
		पूर्ण

		*hyst &= ~IQS626_FILT_STR_LP_TPx_MASK;
		*hyst |= (val << IQS626_FILT_STR_LP_TPx_SHIFT);
	पूर्ण

	अगर (!fwnode_property_present(ch_node, "linux,keycodes"))
		वापस 0;

	count = fwnode_property_count_u32(ch_node, "linux,keycodes");
	अगर (count > IQS626_NUM_GESTURES) अणु
		dev_err(&client->dev, "Too many keycodes present\n");
		वापस -EINVAL;
	पूर्ण अन्यथा अगर (count < 0) अणु
		dev_err(&client->dev, "Failed to count keycodes: %d\n", count);
		वापस count;
	पूर्ण

	error = fwnode_property_पढ़ो_u32_array(ch_node, "linux,keycodes",
					       iqs626->tp_code, count);
	अगर (error) अणु
		dev_err(&client->dev, "Failed to read keycodes: %d\n", error);
		वापस error;
	पूर्ण

	sys_reg->misc_b &= ~IQS626_MISC_B_TPx_SWIPE;
	अगर (fwnode_property_present(ch_node, "azoteq,gesture-swipe"))
		sys_reg->misc_b |= IQS626_MISC_B_TPx_SWIPE;

	अगर (!fwnode_property_पढ़ो_u32(ch_node, "azoteq,timeout-tap-ms",
				      &val)) अणु
		अगर (val > IQS626_TIMEOUT_TAP_MS_MAX) अणु
			dev_err(&client->dev,
				"Invalid %s channel timeout: %u\n",
				fwnode_get_name(ch_node), val);
			वापस -EINVAL;
		पूर्ण

		sys_reg->समयout_tap = val / 16;
	पूर्ण

	अगर (!fwnode_property_पढ़ो_u32(ch_node, "azoteq,timeout-swipe-ms",
				      &val)) अणु
		अगर (val > IQS626_TIMEOUT_SWIPE_MS_MAX) अणु
			dev_err(&client->dev,
				"Invalid %s channel timeout: %u\n",
				fwnode_get_name(ch_node), val);
			वापस -EINVAL;
		पूर्ण

		sys_reg->समयout_swipe = val / 16;
	पूर्ण

	अगर (!fwnode_property_पढ़ो_u32(ch_node, "azoteq,thresh-swipe",
				      &val)) अणु
		अगर (val > IQS626_THRESH_SWIPE_MAX) अणु
			dev_err(&client->dev,
				"Invalid %s channel threshold: %u\n",
				fwnode_get_name(ch_node), val);
			वापस -EINVAL;
		पूर्ण

		sys_reg->thresh_swipe = val;
	पूर्ण

	sys_reg->event_mask &= ~IQS626_EVENT_MASK_GESTURE;

	वापस 0;
पूर्ण

अटल पूर्णांक iqs626_parse_channel(काष्ठा iqs626_निजी *iqs626,
				स्थिर काष्ठा fwnode_handle *ch_node,
				क्रमागत iqs626_ch_id ch_id)
अणु
	काष्ठा iqs626_sys_reg *sys_reg = &iqs626->sys_reg;
	काष्ठा i2c_client *client = iqs626->client;
	u8 *engine, *filter, *rx_enable, *tx_enable;
	u8 *assoc_select, *assoc_weight;
	अचिन्हित पूर्णांक val;
	पूर्णांक error, i;

	चयन (ch_id) अणु
	हाल IQS626_CH_ULP_0:
		engine = sys_reg->ch_reg_ulp.engine;
		अवरोध;

	हाल IQS626_CH_TP_2:
	हाल IQS626_CH_TP_3:
		engine = sys_reg->tp_grp_reg.engine;
		अवरोध;

	हाल IQS626_CH_GEN_0:
	हाल IQS626_CH_GEN_1:
	हाल IQS626_CH_GEN_2:
		i = ch_id - IQS626_CH_GEN_0;
		engine = sys_reg->ch_reg_gen[i].engine;
		अवरोध;

	हाल IQS626_CH_HALL:
		engine = &sys_reg->ch_reg_hall.engine;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	*engine |= IQS626_CHx_ENG_0_MEAS_CAP_SIZE;
	अगर (fwnode_property_present(ch_node, "azoteq,meas-cap-decrease"))
		*engine &= ~IQS626_CHx_ENG_0_MEAS_CAP_SIZE;

	*engine |= IQS626_CHx_ENG_0_RX_TERM_VSS;
	अगर (!fwnode_property_पढ़ो_u32(ch_node, "azoteq,rx-inactive", &val)) अणु
		चयन (val) अणु
		हाल IQS626_RX_INACTIVE_VSS:
			अवरोध;

		हाल IQS626_RX_INACTIVE_FLOAT:
			*engine &= ~IQS626_CHx_ENG_0_RX_TERM_VSS;
			अगर (ch_id == IQS626_CH_GEN_0 ||
			    ch_id == IQS626_CH_GEN_1 ||
			    ch_id == IQS626_CH_GEN_2)
				*(engine + 4) &= ~IQS626_CHx_ENG_4_RX_TERM_VREG;
			अवरोध;

		हाल IQS626_RX_INACTIVE_VREG:
			अगर (ch_id == IQS626_CH_GEN_0 ||
			    ch_id == IQS626_CH_GEN_1 ||
			    ch_id == IQS626_CH_GEN_2) अणु
				*engine &= ~IQS626_CHx_ENG_0_RX_TERM_VSS;
				*(engine + 4) |= IQS626_CHx_ENG_4_RX_TERM_VREG;
				अवरोध;
			पूर्ण
			fallthrough;

		शेष:
			dev_err(&client->dev,
				"Invalid %s channel CRX pin termination: %u\n",
				fwnode_get_name(ch_node), val);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	*engine &= ~IQS626_CHx_ENG_0_LINEARIZE;
	अगर (fwnode_property_present(ch_node, "azoteq,linearize"))
		*engine |= IQS626_CHx_ENG_0_LINEARIZE;

	*engine &= ~IQS626_CHx_ENG_0_DUAL_सूची;
	अगर (fwnode_property_present(ch_node, "azoteq,dual-direction"))
		*engine |= IQS626_CHx_ENG_0_DUAL_सूची;

	*engine &= ~IQS626_CHx_ENG_0_FILT_DISABLE;
	अगर (fwnode_property_present(ch_node, "azoteq,filt-disable"))
		*engine |= IQS626_CHx_ENG_0_FILT_DISABLE;

	अगर (!fwnode_property_पढ़ो_u32(ch_node, "azoteq,ati-mode", &val)) अणु
		अगर (val > IQS626_CHx_ENG_0_ATI_MODE_MAX) अणु
			dev_err(&client->dev,
				"Invalid %s channel ATI mode: %u\n",
				fwnode_get_name(ch_node), val);
			वापस -EINVAL;
		पूर्ण

		*engine &= ~IQS626_CHx_ENG_0_ATI_MODE_MASK;
		*engine |= val;
	पूर्ण

	अगर (ch_id == IQS626_CH_HALL)
		वापस 0;

	*(engine + 1) &= ~IQS626_CHx_ENG_1_CCT_ENABLE;
	अगर (!fwnode_property_पढ़ो_u32(ch_node, "azoteq,cct-increase",
				      &val) && val) अणु
		अचिन्हित पूर्णांक orig_val = val--;

		/*
		 * In the हाल of the generic channels, the अक्षरge cycle समय
		 * field द्विगुनs in size and straddles two separate रेजिस्टरs.
		 */
		अगर (ch_id == IQS626_CH_GEN_0 ||
		    ch_id == IQS626_CH_GEN_1 ||
		    ch_id == IQS626_CH_GEN_2) अणु
			*(engine + 4) &= ~IQS626_CHx_ENG_4_CCT_LOW_1;
			अगर (val & BIT(1))
				*(engine + 4) |= IQS626_CHx_ENG_4_CCT_LOW_1;

			*(engine + 4) &= ~IQS626_CHx_ENG_4_CCT_LOW_0;
			अगर (val & BIT(0))
				*(engine + 4) |= IQS626_CHx_ENG_4_CCT_LOW_0;

			val >>= 2;
		पूर्ण

		अगर (val & ~GENMASK(1, 0)) अणु
			dev_err(&client->dev,
				"Invalid %s channel charge cycle time: %u\n",
				fwnode_get_name(ch_node), orig_val);
			वापस -EINVAL;
		पूर्ण

		*(engine + 1) &= ~IQS626_CHx_ENG_1_CCT_HIGH_1;
		अगर (val & BIT(1))
			*(engine + 1) |= IQS626_CHx_ENG_1_CCT_HIGH_1;

		*(engine + 1) &= ~IQS626_CHx_ENG_1_CCT_HIGH_0;
		अगर (val & BIT(0))
			*(engine + 1) |= IQS626_CHx_ENG_1_CCT_HIGH_0;

		*(engine + 1) |= IQS626_CHx_ENG_1_CCT_ENABLE;
	पूर्ण

	अगर (!fwnode_property_पढ़ो_u32(ch_node, "azoteq,proj-bias", &val)) अणु
		अगर (val > IQS626_CHx_ENG_1_PROJ_BIAS_MAX) अणु
			dev_err(&client->dev,
				"Invalid %s channel bias current: %u\n",
				fwnode_get_name(ch_node), val);
			वापस -EINVAL;
		पूर्ण

		*(engine + 1) &= ~IQS626_CHx_ENG_1_PROJ_BIAS_MASK;
		*(engine + 1) |= (val << IQS626_CHx_ENG_1_PROJ_BIAS_SHIFT);
	पूर्ण

	अगर (!fwnode_property_पढ़ो_u32(ch_node, "azoteq,sense-freq", &val)) अणु
		अगर (val > IQS626_CHx_ENG_1_SENSE_FREQ_MAX) अणु
			dev_err(&client->dev,
				"Invalid %s channel sensing frequency: %u\n",
				fwnode_get_name(ch_node), val);
			वापस -EINVAL;
		पूर्ण

		*(engine + 1) &= ~IQS626_CHx_ENG_1_SENSE_FREQ_MASK;
		*(engine + 1) |= (val << IQS626_CHx_ENG_1_SENSE_FREQ_SHIFT);
	पूर्ण

	*(engine + 1) &= ~IQS626_CHx_ENG_1_ATI_BAND_TIGHTEN;
	अगर (fwnode_property_present(ch_node, "azoteq,ati-band-tighten"))
		*(engine + 1) |= IQS626_CHx_ENG_1_ATI_BAND_TIGHTEN;

	अगर (ch_id == IQS626_CH_TP_2 || ch_id == IQS626_CH_TP_3)
		वापस iqs626_parse_trackpad(iqs626, ch_node);

	अगर (ch_id == IQS626_CH_ULP_0) अणु
		sys_reg->ch_reg_ulp.hyst &= ~IQS626_ULP_PROJ_ENABLE;
		अगर (fwnode_property_present(ch_node, "azoteq,proj-enable"))
			sys_reg->ch_reg_ulp.hyst |= IQS626_ULP_PROJ_ENABLE;

		filter = &sys_reg->ch_reg_ulp.filter;

		rx_enable = &sys_reg->ch_reg_ulp.rx_enable;
		tx_enable = &sys_reg->ch_reg_ulp.tx_enable;
	पूर्ण अन्यथा अणु
		i = ch_id - IQS626_CH_GEN_0;
		filter = &sys_reg->ch_reg_gen[i].filter;

		rx_enable = &sys_reg->ch_reg_gen[i].rx_enable;
		tx_enable = &sys_reg->ch_reg_gen[i].tx_enable;
	पूर्ण

	अगर (!fwnode_property_पढ़ो_u32(ch_node, "azoteq,filt-str-np-cnt",
				      &val)) अणु
		अगर (val > IQS626_FILT_STR_MAX) अणु
			dev_err(&client->dev,
				"Invalid %s channel filter strength: %u\n",
				fwnode_get_name(ch_node), val);
			वापस -EINVAL;
		पूर्ण

		*filter &= ~IQS626_FILT_STR_NP_CNT_MASK;
		*filter |= (val << IQS626_FILT_STR_NP_CNT_SHIFT);
	पूर्ण

	अगर (!fwnode_property_पढ़ो_u32(ch_node, "azoteq,filt-str-lp-cnt",
				      &val)) अणु
		अगर (val > IQS626_FILT_STR_MAX) अणु
			dev_err(&client->dev,
				"Invalid %s channel filter strength: %u\n",
				fwnode_get_name(ch_node), val);
			वापस -EINVAL;
		पूर्ण

		*filter &= ~IQS626_FILT_STR_LP_CNT_MASK;
		*filter |= (val << IQS626_FILT_STR_LP_CNT_SHIFT);
	पूर्ण

	अगर (!fwnode_property_पढ़ो_u32(ch_node, "azoteq,filt-str-np-lta",
				      &val)) अणु
		अगर (val > IQS626_FILT_STR_MAX) अणु
			dev_err(&client->dev,
				"Invalid %s channel filter strength: %u\n",
				fwnode_get_name(ch_node), val);
			वापस -EINVAL;
		पूर्ण

		*filter &= ~IQS626_FILT_STR_NP_LTA_MASK;
		*filter |= (val << IQS626_FILT_STR_NP_LTA_SHIFT);
	पूर्ण

	अगर (!fwnode_property_पढ़ो_u32(ch_node, "azoteq,filt-str-lp-lta",
				      &val)) अणु
		अगर (val > IQS626_FILT_STR_MAX) अणु
			dev_err(&client->dev,
				"Invalid %s channel filter strength: %u\n",
				fwnode_get_name(ch_node), val);
			वापस -EINVAL;
		पूर्ण

		*filter &= ~IQS626_FILT_STR_LP_LTA_MASK;
		*filter |= val;
	पूर्ण

	error = iqs626_parse_pins(iqs626, ch_node, "azoteq,rx-enable",
				  rx_enable);
	अगर (error)
		वापस error;

	error = iqs626_parse_pins(iqs626, ch_node, "azoteq,tx-enable",
				  tx_enable);
	अगर (error)
		वापस error;

	अगर (ch_id == IQS626_CH_ULP_0)
		वापस 0;

	*(engine + 2) &= ~IQS626_CHx_ENG_2_LOCAL_CAP_ENABLE;
	अगर (!fwnode_property_पढ़ो_u32(ch_node, "azoteq,local-cap-size",
				      &val) && val) अणु
		अचिन्हित पूर्णांक orig_val = val--;

		अगर (val > IQS626_CHx_ENG_2_LOCAL_CAP_MAX) अणु
			dev_err(&client->dev,
				"Invalid %s channel local cap. size: %u\n",
				fwnode_get_name(ch_node), orig_val);
			वापस -EINVAL;
		पूर्ण

		*(engine + 2) &= ~IQS626_CHx_ENG_2_LOCAL_CAP_MASK;
		*(engine + 2) |= (val << IQS626_CHx_ENG_2_LOCAL_CAP_SHIFT);

		*(engine + 2) |= IQS626_CHx_ENG_2_LOCAL_CAP_ENABLE;
	पूर्ण

	अगर (!fwnode_property_पढ़ो_u32(ch_node, "azoteq,sense-mode", &val)) अणु
		अगर (val > IQS626_CHx_ENG_2_SENSE_MODE_MAX) अणु
			dev_err(&client->dev,
				"Invalid %s channel sensing mode: %u\n",
				fwnode_get_name(ch_node), val);
			वापस -EINVAL;
		पूर्ण

		*(engine + 2) &= ~IQS626_CHx_ENG_2_SENSE_MODE_MASK;
		*(engine + 2) |= val;
	पूर्ण

	अगर (!fwnode_property_पढ़ो_u32(ch_node, "azoteq,tx-freq", &val)) अणु
		अगर (val > IQS626_CHx_ENG_3_TX_FREQ_MAX) अणु
			dev_err(&client->dev,
				"Invalid %s channel excitation frequency: %u\n",
				fwnode_get_name(ch_node), val);
			वापस -EINVAL;
		पूर्ण

		*(engine + 3) &= ~IQS626_CHx_ENG_3_TX_FREQ_MASK;
		*(engine + 3) |= (val << IQS626_CHx_ENG_3_TX_FREQ_SHIFT);
	पूर्ण

	*(engine + 3) &= ~IQS626_CHx_ENG_3_INV_LOGIC;
	अगर (fwnode_property_present(ch_node, "azoteq,invert-enable"))
		*(engine + 3) |= IQS626_CHx_ENG_3_INV_LOGIC;

	*(engine + 4) &= ~IQS626_CHx_ENG_4_COMP_DISABLE;
	अगर (fwnode_property_present(ch_node, "azoteq,comp-disable"))
		*(engine + 4) |= IQS626_CHx_ENG_4_COMP_DISABLE;

	*(engine + 4) &= ~IQS626_CHx_ENG_4_STATIC_ENABLE;
	अगर (fwnode_property_present(ch_node, "azoteq,static-enable"))
		*(engine + 4) |= IQS626_CHx_ENG_4_STATIC_ENABLE;

	i = ch_id - IQS626_CH_GEN_0;
	assoc_select = &sys_reg->ch_reg_gen[i].assoc_select;
	assoc_weight = &sys_reg->ch_reg_gen[i].assoc_weight;

	*assoc_select = 0;
	अगर (!fwnode_property_present(ch_node, "azoteq,assoc-select"))
		वापस 0;

	क्रम (i = 0; i < ARRAY_SIZE(iqs626_channels); i++) अणु
		अगर (fwnode_property_match_string(ch_node, "azoteq,assoc-select",
						 iqs626_channels[i].name) < 0)
			जारी;

		*assoc_select |= iqs626_channels[i].active;
	पूर्ण

	अगर (fwnode_property_पढ़ो_u32(ch_node, "azoteq,assoc-weight", &val))
		वापस 0;

	अगर (val > IQS626_GEN_WEIGHT_MAX) अणु
		dev_err(&client->dev,
			"Invalid %s channel associated weight: %u\n",
			fwnode_get_name(ch_node), val);
		वापस -EINVAL;
	पूर्ण

	*assoc_weight = val;

	वापस 0;
पूर्ण

अटल पूर्णांक iqs626_parse_prop(काष्ठा iqs626_निजी *iqs626)
अणु
	काष्ठा iqs626_sys_reg *sys_reg = &iqs626->sys_reg;
	काष्ठा i2c_client *client = iqs626->client;
	काष्ठा fwnode_handle *ch_node;
	अचिन्हित पूर्णांक val;
	पूर्णांक error, i;
	u16 general;

	अगर (!device_property_पढ़ो_u32(&client->dev, "azoteq,suspend-mode",
				      &val)) अणु
		अगर (val > IQS626_SYS_SETTINGS_PWR_MODE_MAX) अणु
			dev_err(&client->dev, "Invalid suspend mode: %u\n",
				val);
			वापस -EINVAL;
		पूर्ण

		iqs626->suspend_mode = val;
	पूर्ण

	error = regmap_raw_पढ़ो(iqs626->regmap, IQS626_SYS_SETTINGS, sys_reg,
				माप(*sys_reg));
	अगर (error)
		वापस error;

	general = be16_to_cpu(sys_reg->general);
	general &= IQS626_SYS_SETTINGS_ULP_UPDATE_MASK;

	अगर (device_property_present(&client->dev, "azoteq,clk-div"))
		general |= IQS626_SYS_SETTINGS_CLK_DIV;

	अगर (device_property_present(&client->dev, "azoteq,ulp-enable"))
		general |= IQS626_SYS_SETTINGS_ULP_AUTO;

	अगर (!device_property_पढ़ो_u32(&client->dev, "azoteq,ulp-update",
				      &val)) अणु
		अगर (val > IQS626_SYS_SETTINGS_ULP_UPDATE_MAX) अणु
			dev_err(&client->dev, "Invalid update rate: %u\n", val);
			वापस -EINVAL;
		पूर्ण

		general &= ~IQS626_SYS_SETTINGS_ULP_UPDATE_MASK;
		general |= (val << IQS626_SYS_SETTINGS_ULP_UPDATE_SHIFT);
	पूर्ण

	sys_reg->misc_a &= ~IQS626_MISC_A_ATI_BAND_DISABLE;
	अगर (device_property_present(&client->dev, "azoteq,ati-band-disable"))
		sys_reg->misc_a |= IQS626_MISC_A_ATI_BAND_DISABLE;

	sys_reg->misc_a &= ~IQS626_MISC_A_ATI_LP_ONLY;
	अगर (device_property_present(&client->dev, "azoteq,ati-lp-only"))
		sys_reg->misc_a |= IQS626_MISC_A_ATI_LP_ONLY;

	अगर (!device_property_पढ़ो_u32(&client->dev, "azoteq,gpio3-select",
				      &val)) अणु
		अगर (val > IQS626_MISC_A_GPIO3_SELECT_MAX) अणु
			dev_err(&client->dev, "Invalid GPIO3 selection: %u\n",
				val);
			वापस -EINVAL;
		पूर्ण

		sys_reg->misc_a &= ~IQS626_MISC_A_GPIO3_SELECT_MASK;
		sys_reg->misc_a |= val;
	पूर्ण

	अगर (!device_property_पढ़ो_u32(&client->dev, "azoteq,reseed-select",
				      &val)) अणु
		अगर (val > IQS626_MISC_B_RESEED_UI_SEL_MAX) अणु
			dev_err(&client->dev, "Invalid reseed selection: %u\n",
				val);
			वापस -EINVAL;
		पूर्ण

		sys_reg->misc_b &= ~IQS626_MISC_B_RESEED_UI_SEL_MASK;
		sys_reg->misc_b |= (val << IQS626_MISC_B_RESEED_UI_SEL_SHIFT);
	पूर्ण

	sys_reg->misc_b &= ~IQS626_MISC_B_THRESH_EXTEND;
	अगर (device_property_present(&client->dev, "azoteq,thresh-extend"))
		sys_reg->misc_b |= IQS626_MISC_B_THRESH_EXTEND;

	sys_reg->misc_b &= ~IQS626_MISC_B_TRACKING_UI_ENABLE;
	अगर (device_property_present(&client->dev, "azoteq,tracking-enable"))
		sys_reg->misc_b |= IQS626_MISC_B_TRACKING_UI_ENABLE;

	sys_reg->misc_b &= ~IQS626_MISC_B_RESEED_OFFSET;
	अगर (device_property_present(&client->dev, "azoteq,reseed-offset"))
		sys_reg->misc_b |= IQS626_MISC_B_RESEED_OFFSET;

	अगर (!device_property_पढ़ो_u32(&client->dev, "azoteq,rate-np-ms",
				      &val)) अणु
		अगर (val > IQS626_RATE_NP_MS_MAX) अणु
			dev_err(&client->dev, "Invalid report rate: %u\n", val);
			वापस -EINVAL;
		पूर्ण

		sys_reg->rate_np = val;
	पूर्ण

	अगर (!device_property_पढ़ो_u32(&client->dev, "azoteq,rate-lp-ms",
				      &val)) अणु
		अगर (val > IQS626_RATE_LP_MS_MAX) अणु
			dev_err(&client->dev, "Invalid report rate: %u\n", val);
			वापस -EINVAL;
		पूर्ण

		sys_reg->rate_lp = val;
	पूर्ण

	अगर (!device_property_पढ़ो_u32(&client->dev, "azoteq,rate-ulp-ms",
				      &val)) अणु
		अगर (val > IQS626_RATE_ULP_MS_MAX) अणु
			dev_err(&client->dev, "Invalid report rate: %u\n", val);
			वापस -EINVAL;
		पूर्ण

		sys_reg->rate_ulp = val / 16;
	पूर्ण

	अगर (!device_property_पढ़ो_u32(&client->dev, "azoteq,timeout-pwr-ms",
				      &val)) अणु
		अगर (val > IQS626_TIMEOUT_PWR_MS_MAX) अणु
			dev_err(&client->dev, "Invalid timeout: %u\n", val);
			वापस -EINVAL;
		पूर्ण

		sys_reg->समयout_pwr = val / 512;
	पूर्ण

	अगर (!device_property_पढ़ो_u32(&client->dev, "azoteq,timeout-lta-ms",
				      &val)) अणु
		अगर (val > IQS626_TIMEOUT_LTA_MS_MAX) अणु
			dev_err(&client->dev, "Invalid timeout: %u\n", val);
			वापस -EINVAL;
		पूर्ण

		sys_reg->समयout_lta = val / 512;
	पूर्ण

	sys_reg->event_mask = ~((u8)IQS626_EVENT_MASK_SYS);
	sys_reg->reकरो_ati = 0;

	sys_reg->reseed = 0;
	sys_reg->active = 0;

	क्रम (i = 0; i < ARRAY_SIZE(iqs626_channels); i++) अणु
		ch_node = device_get_named_child_node(&client->dev,
						      iqs626_channels[i].name);
		अगर (!ch_node)
			जारी;

		error = iqs626_parse_channel(iqs626, ch_node, i);
		अगर (error)
			वापस error;

		error = iqs626_parse_ati_target(iqs626, ch_node, i);
		अगर (error)
			वापस error;

		error = iqs626_parse_events(iqs626, ch_node, i);
		अगर (error)
			वापस error;

		अगर (!fwnode_property_present(ch_node, "azoteq,ati-exclude"))
			sys_reg->reकरो_ati |= iqs626_channels[i].active;

		अगर (!fwnode_property_present(ch_node, "azoteq,reseed-disable"))
			sys_reg->reseed |= iqs626_channels[i].active;

		sys_reg->active |= iqs626_channels[i].active;
	पूर्ण

	general |= IQS626_SYS_SETTINGS_EVENT_MODE;

	/*
	 * Enable streaming during normal-घातer mode अगर the trackpad is used to
	 * report raw coordinates instead of gestures. In that हाल, the device
	 * वापसs to event mode during low-घातer mode.
	 */
	अगर (sys_reg->active & iqs626_channels[IQS626_CH_TP_2].active &&
	    sys_reg->event_mask & IQS626_EVENT_MASK_GESTURE)
		general |= IQS626_SYS_SETTINGS_EVENT_MODE_LP;

	general |= IQS626_SYS_SETTINGS_REDO_ATI;
	general |= IQS626_SYS_SETTINGS_ACK_RESET;

	sys_reg->general = cpu_to_be16(general);

	error = regmap_raw_ग_लिखो(iqs626->regmap, IQS626_SYS_SETTINGS,
				 &iqs626->sys_reg, माप(iqs626->sys_reg));
	अगर (error)
		वापस error;

	iqs626_irq_रुको();

	वापस 0;
पूर्ण

अटल पूर्णांक iqs626_input_init(काष्ठा iqs626_निजी *iqs626)
अणु
	काष्ठा iqs626_sys_reg *sys_reg = &iqs626->sys_reg;
	काष्ठा i2c_client *client = iqs626->client;
	पूर्णांक error, i, j;

	iqs626->keypad = devm_input_allocate_device(&client->dev);
	अगर (!iqs626->keypad)
		वापस -ENOMEM;

	iqs626->keypad->keycodemax = ARRAY_SIZE(iqs626->kp_code);
	iqs626->keypad->keycode = iqs626->kp_code;
	iqs626->keypad->keycodesize = माप(**iqs626->kp_code);

	iqs626->keypad->name = "iqs626a_keypad";
	iqs626->keypad->id.bustype = BUS_I2C;

	क्रम (i = 0; i < ARRAY_SIZE(iqs626_channels); i++) अणु
		अगर (!(sys_reg->active & iqs626_channels[i].active))
			जारी;

		क्रम (j = 0; j < ARRAY_SIZE(iqs626_events); j++) अणु
			अगर (!iqs626->kp_type[i][j])
				जारी;

			input_set_capability(iqs626->keypad,
					     iqs626->kp_type[i][j],
					     iqs626->kp_code[i][j]);
		पूर्ण
	पूर्ण

	अगर (!(sys_reg->active & iqs626_channels[IQS626_CH_TP_2].active))
		वापस 0;

	iqs626->trackpad = devm_input_allocate_device(&client->dev);
	अगर (!iqs626->trackpad)
		वापस -ENOMEM;

	iqs626->trackpad->keycodemax = ARRAY_SIZE(iqs626->tp_code);
	iqs626->trackpad->keycode = iqs626->tp_code;
	iqs626->trackpad->keycodesize = माप(*iqs626->tp_code);

	iqs626->trackpad->name = "iqs626a_trackpad";
	iqs626->trackpad->id.bustype = BUS_I2C;

	/*
	 * Present the trackpad as a traditional poपूर्णांकing device अगर no gestures
	 * have been mapped to a keycode.
	 */
	अगर (sys_reg->event_mask & IQS626_EVENT_MASK_GESTURE) अणु
		u8 tp_mask = iqs626_channels[IQS626_CH_TP_3].active;

		input_set_capability(iqs626->trackpad, EV_KEY, BTN_TOUCH);
		input_set_असल_params(iqs626->trackpad, ABS_Y, 0, 255, 0, 0);

		अगर ((sys_reg->active & tp_mask) == tp_mask)
			input_set_असल_params(iqs626->trackpad,
					     ABS_X, 0, 255, 0, 0);
		अन्यथा
			input_set_असल_params(iqs626->trackpad,
					     ABS_X, 0, 128, 0, 0);

		touchscreen_parse_properties(iqs626->trackpad, false,
					     &iqs626->prop);
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < IQS626_NUM_GESTURES; i++)
			अगर (iqs626->tp_code[i] != KEY_RESERVED)
				input_set_capability(iqs626->trackpad, EV_KEY,
						     iqs626->tp_code[i]);
	पूर्ण

	error = input_रेजिस्टर_device(iqs626->trackpad);
	अगर (error)
		dev_err(&client->dev, "Failed to register trackpad: %d\n",
			error);

	वापस error;
पूर्ण

अटल पूर्णांक iqs626_report(काष्ठा iqs626_निजी *iqs626)
अणु
	काष्ठा iqs626_sys_reg *sys_reg = &iqs626->sys_reg;
	काष्ठा i2c_client *client = iqs626->client;
	काष्ठा iqs626_flags flags;
	__le16 hall_output;
	पूर्णांक error, i, j;
	u8 state;
	u8 *dir_mask = &flags.states[IQS626_ST_OFFS_सूची];

	error = regmap_raw_पढ़ो(iqs626->regmap, IQS626_SYS_FLAGS, &flags,
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
	अगर (be16_to_cpu(flags.प्रणाली) & IQS626_SYS_FLAGS_SHOW_RESET) अणु
		dev_err(&client->dev, "Unexpected device reset\n");

		error = regmap_raw_ग_लिखो(iqs626->regmap, IQS626_SYS_SETTINGS,
					 sys_reg, माप(*sys_reg));
		अगर (error)
			dev_err(&client->dev,
				"Failed to re-initialize device: %d\n", error);

		वापस error;
	पूर्ण

	अगर (be16_to_cpu(flags.प्रणाली) & IQS626_SYS_FLAGS_IN_ATI)
		वापस 0;

	/*
	 * Unlike the ULP or generic channels, the Hall channel करोes not have a
	 * direction flag. Instead, the direction (i.e. magnet polarity) can be
	 * derived based on the sign of the 2's complement dअगरferential output.
	 */
	अगर (sys_reg->active & iqs626_channels[IQS626_CH_HALL].active) अणु
		error = regmap_raw_पढ़ो(iqs626->regmap, IQS626_HALL_OUTPUT,
					&hall_output, माप(hall_output));
		अगर (error) अणु
			dev_err(&client->dev,
				"Failed to read Hall output: %d\n", error);
			वापस error;
		पूर्ण

		*dir_mask &= ~iqs626_channels[IQS626_CH_HALL].active;
		अगर (le16_to_cpu(hall_output) < 0x8000)
			*dir_mask |= iqs626_channels[IQS626_CH_HALL].active;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(iqs626_channels); i++) अणु
		अगर (!(sys_reg->active & iqs626_channels[i].active))
			जारी;

		क्रम (j = 0; j < ARRAY_SIZE(iqs626_events); j++) अणु
			अगर (!iqs626->kp_type[i][j])
				जारी;

			state = flags.states[iqs626_events[j].st_offs];
			state &= iqs626_events[j].dir_up ? *dir_mask
							 : ~(*dir_mask);
			state &= iqs626_channels[i].active;

			input_event(iqs626->keypad, iqs626->kp_type[i][j],
				    iqs626->kp_code[i][j], !!state);
		पूर्ण
	पूर्ण

	input_sync(iqs626->keypad);

	/*
	 * The following completion संकेतs that ATI has finished, any initial
	 * चयन states have been reported and the keypad can be रेजिस्टरed.
	 */
	complete_all(&iqs626->ati_करोne);

	अगर (!(sys_reg->active & iqs626_channels[IQS626_CH_TP_2].active))
		वापस 0;

	अगर (sys_reg->event_mask & IQS626_EVENT_MASK_GESTURE) अणु
		state = flags.states[IQS626_ST_OFFS_TOUCH];
		state &= iqs626_channels[IQS626_CH_TP_2].active;

		input_report_key(iqs626->trackpad, BTN_TOUCH, state);

		अगर (state)
			touchscreen_report_pos(iqs626->trackpad, &iqs626->prop,
					       flags.trackpad_x,
					       flags.trackpad_y, false);
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < IQS626_NUM_GESTURES; i++)
			input_report_key(iqs626->trackpad, iqs626->tp_code[i],
					 flags.gesture & BIT(i));

		अगर (flags.gesture & GENMASK(IQS626_GESTURE_TAP, 0)) अणु
			input_sync(iqs626->trackpad);

			/*
			 * Momentary gestures are followed by a complementary
			 * release cycle so as to emulate a full keystroke.
			 */
			क्रम (i = 0; i < IQS626_GESTURE_HOLD; i++)
				input_report_key(iqs626->trackpad,
						 iqs626->tp_code[i], 0);
		पूर्ण
	पूर्ण

	input_sync(iqs626->trackpad);

	वापस 0;
पूर्ण

अटल irqवापस_t iqs626_irq(पूर्णांक irq, व्योम *context)
अणु
	काष्ठा iqs626_निजी *iqs626 = context;

	अगर (iqs626_report(iqs626))
		वापस IRQ_NONE;

	/*
	 * The device करोes not deनिश्चित its पूर्णांकerrupt (RDY) pin until लघुly
	 * after receiving an I2C stop condition; the following delay ensures
	 * the पूर्णांकerrupt handler करोes not वापस beक्रमe this समय.
	 */
	iqs626_irq_रुको();

	वापस IRQ_HANDLED;
पूर्ण

अटल स्थिर काष्ठा regmap_config iqs626_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 16,
	.max_रेजिस्टर = IQS626_MAX_REG,
पूर्ण;

अटल पूर्णांक iqs626_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा iqs626_ver_info ver_info;
	काष्ठा iqs626_निजी *iqs626;
	पूर्णांक error;

	iqs626 = devm_kzalloc(&client->dev, माप(*iqs626), GFP_KERNEL);
	अगर (!iqs626)
		वापस -ENOMEM;

	i2c_set_clientdata(client, iqs626);
	iqs626->client = client;

	iqs626->regmap = devm_regmap_init_i2c(client, &iqs626_regmap_config);
	अगर (IS_ERR(iqs626->regmap)) अणु
		error = PTR_ERR(iqs626->regmap);
		dev_err(&client->dev, "Failed to initialize register map: %d\n",
			error);
		वापस error;
	पूर्ण

	init_completion(&iqs626->ati_करोne);

	error = regmap_raw_पढ़ो(iqs626->regmap, IQS626_VER_INFO, &ver_info,
				माप(ver_info));
	अगर (error)
		वापस error;

	अगर (ver_info.prod_num != IQS626_VER_INFO_PROD_NUM) अणु
		dev_err(&client->dev, "Unrecognized product number: 0x%02X\n",
			ver_info.prod_num);
		वापस -EINVAL;
	पूर्ण

	error = iqs626_parse_prop(iqs626);
	अगर (error)
		वापस error;

	error = iqs626_input_init(iqs626);
	अगर (error)
		वापस error;

	error = devm_request_thपढ़ोed_irq(&client->dev, client->irq,
					  शून्य, iqs626_irq, IRQF_ONESHOT,
					  client->name, iqs626);
	अगर (error) अणु
		dev_err(&client->dev, "Failed to request IRQ: %d\n", error);
		वापस error;
	पूर्ण

	अगर (!रुको_क्रम_completion_समयout(&iqs626->ati_करोne,
					 msecs_to_jअगरfies(2000))) अणु
		dev_err(&client->dev, "Failed to complete ATI\n");
		वापस -ETIMEDOUT;
	पूर्ण

	/*
	 * The keypad may include one or more चयनes and is not रेजिस्टरed
	 * until ATI is complete and the initial चयन states are पढ़ो.
	 */
	error = input_रेजिस्टर_device(iqs626->keypad);
	अगर (error)
		dev_err(&client->dev, "Failed to register keypad: %d\n", error);

	वापस error;
पूर्ण

अटल पूर्णांक __maybe_unused iqs626_suspend(काष्ठा device *dev)
अणु
	काष्ठा iqs626_निजी *iqs626 = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = iqs626->client;
	अचिन्हित पूर्णांक val;
	पूर्णांक error;

	अगर (!iqs626->suspend_mode)
		वापस 0;

	disable_irq(client->irq);

	/*
	 * Automatic घातer mode चयनing must be disabled beक्रमe the device is
	 * क्रमced पूर्णांकo any particular घातer mode. In this हाल, the device will
	 * transition पूर्णांकo normal-घातer mode.
	 */
	error = regmap_update_bits(iqs626->regmap, IQS626_SYS_SETTINGS,
				   IQS626_SYS_SETTINGS_DIS_AUTO, ~0);
	अगर (error)
		जाओ err_irq;

	/*
	 * The following check ensures the device has completed its transition
	 * पूर्णांकo normal-घातer mode beक्रमe a manual mode चयन is perक्रमmed.
	 */
	error = regmap_पढ़ो_poll_समयout(iqs626->regmap, IQS626_SYS_FLAGS, val,
					!(val & IQS626_SYS_FLAGS_PWR_MODE_MASK),
					 IQS626_PWR_MODE_POLL_SLEEP_US,
					 IQS626_PWR_MODE_POLL_TIMEOUT_US);
	अगर (error)
		जाओ err_irq;

	error = regmap_update_bits(iqs626->regmap, IQS626_SYS_SETTINGS,
				   IQS626_SYS_SETTINGS_PWR_MODE_MASK,
				   iqs626->suspend_mode <<
				   IQS626_SYS_SETTINGS_PWR_MODE_SHIFT);
	अगर (error)
		जाओ err_irq;

	/*
	 * This last check ensures the device has completed its transition पूर्णांकo
	 * the desired घातer mode to prevent any spurious पूर्णांकerrupts from being
	 * triggered after iqs626_suspend has alपढ़ोy वापसed.
	 */
	error = regmap_पढ़ो_poll_समयout(iqs626->regmap, IQS626_SYS_FLAGS, val,
					 (val & IQS626_SYS_FLAGS_PWR_MODE_MASK)
					 == (iqs626->suspend_mode <<
					     IQS626_SYS_FLAGS_PWR_MODE_SHIFT),
					 IQS626_PWR_MODE_POLL_SLEEP_US,
					 IQS626_PWR_MODE_POLL_TIMEOUT_US);

err_irq:
	iqs626_irq_रुको();
	enable_irq(client->irq);

	वापस error;
पूर्ण

अटल पूर्णांक __maybe_unused iqs626_resume(काष्ठा device *dev)
अणु
	काष्ठा iqs626_निजी *iqs626 = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = iqs626->client;
	अचिन्हित पूर्णांक val;
	पूर्णांक error;

	अगर (!iqs626->suspend_mode)
		वापस 0;

	disable_irq(client->irq);

	error = regmap_update_bits(iqs626->regmap, IQS626_SYS_SETTINGS,
				   IQS626_SYS_SETTINGS_PWR_MODE_MASK, 0);
	अगर (error)
		जाओ err_irq;

	/*
	 * This check ensures the device has वापसed to normal-घातer mode
	 * beक्रमe स्वतःmatic घातer mode चयनing is re-enabled.
	 */
	error = regmap_पढ़ो_poll_समयout(iqs626->regmap, IQS626_SYS_FLAGS, val,
					!(val & IQS626_SYS_FLAGS_PWR_MODE_MASK),
					 IQS626_PWR_MODE_POLL_SLEEP_US,
					 IQS626_PWR_MODE_POLL_TIMEOUT_US);
	अगर (error)
		जाओ err_irq;

	error = regmap_update_bits(iqs626->regmap, IQS626_SYS_SETTINGS,
				   IQS626_SYS_SETTINGS_DIS_AUTO, 0);
	अगर (error)
		जाओ err_irq;

	/*
	 * This step reports any events that may have been "swallowed" as a
	 * result of polling PWR_MODE (which स्वतःmatically acknowledges any
	 * pending पूर्णांकerrupts).
	 */
	error = iqs626_report(iqs626);

err_irq:
	iqs626_irq_रुको();
	enable_irq(client->irq);

	वापस error;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(iqs626_pm, iqs626_suspend, iqs626_resume);

अटल स्थिर काष्ठा of_device_id iqs626_of_match[] = अणु
	अणु .compatible = "azoteq,iqs626a" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, iqs626_of_match);

अटल काष्ठा i2c_driver iqs626_i2c_driver = अणु
	.driver = अणु
		.name = "iqs626a",
		.of_match_table = iqs626_of_match,
		.pm = &iqs626_pm,
	पूर्ण,
	.probe_new = iqs626_probe,
पूर्ण;
module_i2c_driver(iqs626_i2c_driver);

MODULE_AUTHOR("Jeff LaBundy <jeff@labundy.com>");
MODULE_DESCRIPTION("Azoteq IQS626A Capacitive Touch Controller");
MODULE_LICENSE("GPL");
