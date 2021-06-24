<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * Azoteq IQS620A/621/622/624/625 Multi-Function Sensors
 *
 * Copyright (C) 2019 Jeff LaBundy <jeff@labundy.com>
 */

#अगर_अघोषित __LINUX_MFD_IQS62X_H
#घोषणा __LINUX_MFD_IQS62X_H

#घोषणा IQS620_PROD_NUM				0x41
#घोषणा IQS621_PROD_NUM				0x46
#घोषणा IQS622_PROD_NUM				0x42
#घोषणा IQS624_PROD_NUM				0x43
#घोषणा IQS625_PROD_NUM				0x4E

#घोषणा IQS621_ALS_FLAGS			0x16
#घोषणा IQS622_ALS_FLAGS			0x14

#घोषणा IQS624_HALL_UI				0x70
#घोषणा IQS624_HALL_UI_WHL_EVENT		BIT(4)
#घोषणा IQS624_HALL_UI_INT_EVENT		BIT(3)
#घोषणा IQS624_HALL_UI_AUTO_CAL			BIT(2)

#घोषणा IQS624_INTERVAL_DIV			0x7D

#घोषणा IQS620_GLBL_EVENT_MASK			0xD7
#घोषणा IQS620_GLBL_EVENT_MASK_PMU		BIT(6)

#घोषणा IQS62X_NUM_KEYS				16
#घोषणा IQS62X_NUM_EVENTS			(IQS62X_NUM_KEYS + 6)

#घोषणा IQS62X_EVENT_SIZE			10

क्रमागत iqs62x_ui_sel अणु
	IQS62X_UI_PROX,
	IQS62X_UI_SAR1,
पूर्ण;

क्रमागत iqs62x_event_reg अणु
	IQS62X_EVENT_NONE,
	IQS62X_EVENT_SYS,
	IQS62X_EVENT_PROX,
	IQS62X_EVENT_HYST,
	IQS62X_EVENT_HALL,
	IQS62X_EVENT_ALS,
	IQS62X_EVENT_IR,
	IQS62X_EVENT_WHEEL,
	IQS62X_EVENT_INTER,
	IQS62X_EVENT_UI_LO,
	IQS62X_EVENT_UI_HI,
पूर्ण;

क्रमागत iqs62x_event_flag अणु
	/* keys */
	IQS62X_EVENT_PROX_CH0_T,
	IQS62X_EVENT_PROX_CH0_P,
	IQS62X_EVENT_PROX_CH1_T,
	IQS62X_EVENT_PROX_CH1_P,
	IQS62X_EVENT_PROX_CH2_T,
	IQS62X_EVENT_PROX_CH2_P,
	IQS62X_EVENT_HYST_POS_T,
	IQS62X_EVENT_HYST_POS_P,
	IQS62X_EVENT_HYST_NEG_T,
	IQS62X_EVENT_HYST_NEG_P,
	IQS62X_EVENT_SAR1_ACT,
	IQS62X_EVENT_SAR1_QRD,
	IQS62X_EVENT_SAR1_MOVE,
	IQS62X_EVENT_SAR1_HALT,
	IQS62X_EVENT_WHEEL_UP,
	IQS62X_EVENT_WHEEL_DN,

	/* चयनes */
	IQS62X_EVENT_HALL_N_T,
	IQS62X_EVENT_HALL_N_P,
	IQS62X_EVENT_HALL_S_T,
	IQS62X_EVENT_HALL_S_P,

	/* everything अन्यथा */
	IQS62X_EVENT_SYS_RESET,
	IQS62X_EVENT_SYS_ATI,
पूर्ण;

काष्ठा iqs62x_event_data अणु
	u16 ui_data;
	u8 als_flags;
	u8 ir_flags;
	u8 पूर्णांकerval;
पूर्ण;

काष्ठा iqs62x_event_desc अणु
	क्रमागत iqs62x_event_reg reg;
	u8 mask;
	u8 val;
पूर्ण;

काष्ठा iqs62x_dev_desc अणु
	स्थिर अक्षर *dev_name;
	स्थिर काष्ठा mfd_cell *sub_devs;
	पूर्णांक num_sub_devs;
	u8 prod_num;
	u8 sw_num;
	स्थिर u8 *cal_regs;
	पूर्णांक num_cal_regs;
	u8 prox_mask;
	u8 sar_mask;
	u8 hall_mask;
	u8 hyst_mask;
	u8 temp_mask;
	u8 als_mask;
	u8 ir_mask;
	u8 prox_settings;
	u8 als_flags;
	u8 hall_flags;
	u8 hyst_shअगरt;
	u8 पूर्णांकerval;
	u8 पूर्णांकerval_भाग;
	स्थिर अक्षर *fw_name;
	स्थिर क्रमागत iqs62x_event_reg (*event_regs)[IQS62X_EVENT_SIZE];
पूर्ण;

काष्ठा iqs62x_core अणु
	स्थिर काष्ठा iqs62x_dev_desc *dev_desc;
	काष्ठा i2c_client *client;
	काष्ठा regmap *regmap;
	काष्ठा blocking_notअगरier_head nh;
	काष्ठा list_head fw_blk_head;
	काष्ठा completion ati_करोne;
	काष्ठा completion fw_करोne;
	क्रमागत iqs62x_ui_sel ui_sel;
	अचिन्हित दीर्घ event_cache;
पूर्ण;

बाह्य स्थिर काष्ठा iqs62x_event_desc iqs62x_events[IQS62X_NUM_EVENTS];

#पूर्ण_अगर /* __LINUX_MFD_IQS62X_H */
