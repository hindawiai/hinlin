<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2015, The Linux Foundation. All rights reserved.
 */

#अगर_अघोषित __QCOM_TSENS_H__
#घोषणा __QCOM_TSENS_H__

#घोषणा ONE_PT_CALIB		0x1
#घोषणा ONE_PT_CALIB2		0x2
#घोषणा TWO_PT_CALIB		0x3
#घोषणा CAL_DEGC_PT1		30
#घोषणा CAL_DEGC_PT2		120
#घोषणा SLOPE_FACTOR		1000
#घोषणा SLOPE_DEFAULT		3200
#घोषणा TIMEOUT_US		100
#घोषणा THRESHOLD_MAX_ADC_CODE	0x3ff
#घोषणा THRESHOLD_MIN_ADC_CODE	0x0

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/thermal.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>

काष्ठा tsens_priv;

/* IP version numbers in ascending order */
क्रमागत tsens_ver अणु
	VER_0 = 0,
	VER_0_1,
	VER_1_X,
	VER_2_X,
पूर्ण;

क्रमागत tsens_irq_type अणु
	LOWER,
	UPPER,
	CRITICAL,
पूर्ण;

/**
 * काष्ठा tsens_sensor - data क्रम each sensor connected to the tsens device
 * @priv: tsens device instance that this sensor is connected to
 * @tzd: poपूर्णांकer to the thermal zone that this sensor is in
 * @offset: offset of temperature adjusपंचांगent curve
 * @hw_id: HW ID can be used in हाल of platक्रमm-specअगरic IDs
 * @slope: slope of temperature adjusपंचांगent curve
 * @status: 8960-specअगरic variable to track 8960 and 8660 status रेजिस्टर offset
 */
काष्ठा tsens_sensor अणु
	काष्ठा tsens_priv		*priv;
	काष्ठा thermal_zone_device	*tzd;
	पूर्णांक				offset;
	अचिन्हित पूर्णांक			hw_id;
	पूर्णांक				slope;
	u32				status;
पूर्ण;

/**
 * काष्ठा tsens_ops - operations as supported by the tsens device
 * @init: Function to initialize the tsens device
 * @calibrate: Function to calibrate the tsens device
 * @get_temp: Function which वापसs the temp in millidegC
 * @enable: Function to enable (घड़ीs/घातer) tsens device
 * @disable: Function to disable the tsens device
 * @suspend: Function to suspend the tsens device
 * @resume: Function to resume the tsens device
 * @get_trend: Function to get the thermal/temp trend
 */
काष्ठा tsens_ops अणु
	/* mandatory callbacks */
	पूर्णांक (*init)(काष्ठा tsens_priv *priv);
	पूर्णांक (*calibrate)(काष्ठा tsens_priv *priv);
	पूर्णांक (*get_temp)(स्थिर काष्ठा tsens_sensor *s, पूर्णांक *temp);
	/* optional callbacks */
	पूर्णांक (*enable)(काष्ठा tsens_priv *priv, पूर्णांक i);
	व्योम (*disable)(काष्ठा tsens_priv *priv);
	पूर्णांक (*suspend)(काष्ठा tsens_priv *priv);
	पूर्णांक (*resume)(काष्ठा tsens_priv *priv);
	पूर्णांक (*get_trend)(काष्ठा tsens_sensor *s, क्रमागत thermal_trend *trend);
पूर्ण;

#घोषणा REG_FIELD_FOR_EACH_SENSOR11(_name, _offset, _startbit, _stopbit) \
	[_name##_##0]  = REG_FIELD(_offset,      _startbit, _stopbit),	\
	[_name##_##1]  = REG_FIELD(_offset +  4, _startbit, _stopbit), \
	[_name##_##2]  = REG_FIELD(_offset +  8, _startbit, _stopbit), \
	[_name##_##3]  = REG_FIELD(_offset + 12, _startbit, _stopbit), \
	[_name##_##4]  = REG_FIELD(_offset + 16, _startbit, _stopbit), \
	[_name##_##5]  = REG_FIELD(_offset + 20, _startbit, _stopbit), \
	[_name##_##6]  = REG_FIELD(_offset + 24, _startbit, _stopbit), \
	[_name##_##7]  = REG_FIELD(_offset + 28, _startbit, _stopbit), \
	[_name##_##8]  = REG_FIELD(_offset + 32, _startbit, _stopbit), \
	[_name##_##9]  = REG_FIELD(_offset + 36, _startbit, _stopbit), \
	[_name##_##10] = REG_FIELD(_offset + 40, _startbit, _stopbit)

#घोषणा REG_FIELD_FOR_EACH_SENSOR16(_name, _offset, _startbit, _stopbit) \
	[_name##_##0]  = REG_FIELD(_offset,      _startbit, _stopbit),	\
	[_name##_##1]  = REG_FIELD(_offset +  4, _startbit, _stopbit), \
	[_name##_##2]  = REG_FIELD(_offset +  8, _startbit, _stopbit), \
	[_name##_##3]  = REG_FIELD(_offset + 12, _startbit, _stopbit), \
	[_name##_##4]  = REG_FIELD(_offset + 16, _startbit, _stopbit), \
	[_name##_##5]  = REG_FIELD(_offset + 20, _startbit, _stopbit), \
	[_name##_##6]  = REG_FIELD(_offset + 24, _startbit, _stopbit), \
	[_name##_##7]  = REG_FIELD(_offset + 28, _startbit, _stopbit), \
	[_name##_##8]  = REG_FIELD(_offset + 32, _startbit, _stopbit), \
	[_name##_##9]  = REG_FIELD(_offset + 36, _startbit, _stopbit), \
	[_name##_##10] = REG_FIELD(_offset + 40, _startbit, _stopbit), \
	[_name##_##11] = REG_FIELD(_offset + 44, _startbit, _stopbit), \
	[_name##_##12] = REG_FIELD(_offset + 48, _startbit, _stopbit), \
	[_name##_##13] = REG_FIELD(_offset + 52, _startbit, _stopbit), \
	[_name##_##14] = REG_FIELD(_offset + 56, _startbit, _stopbit), \
	[_name##_##15] = REG_FIELD(_offset + 60, _startbit, _stopbit)

#घोषणा REG_FIELD_SPLIT_BITS_0_15(_name, _offset)		\
	[_name##_##0]  = REG_FIELD(_offset,  0,  0),		\
	[_name##_##1]  = REG_FIELD(_offset,  1,  1),	\
	[_name##_##2]  = REG_FIELD(_offset,  2,  2),	\
	[_name##_##3]  = REG_FIELD(_offset,  3,  3),	\
	[_name##_##4]  = REG_FIELD(_offset,  4,  4),	\
	[_name##_##5]  = REG_FIELD(_offset,  5,  5),	\
	[_name##_##6]  = REG_FIELD(_offset,  6,  6),	\
	[_name##_##7]  = REG_FIELD(_offset,  7,  7),	\
	[_name##_##8]  = REG_FIELD(_offset,  8,  8),	\
	[_name##_##9]  = REG_FIELD(_offset,  9,  9),	\
	[_name##_##10] = REG_FIELD(_offset, 10, 10),	\
	[_name##_##11] = REG_FIELD(_offset, 11, 11),	\
	[_name##_##12] = REG_FIELD(_offset, 12, 12),	\
	[_name##_##13] = REG_FIELD(_offset, 13, 13),	\
	[_name##_##14] = REG_FIELD(_offset, 14, 14),	\
	[_name##_##15] = REG_FIELD(_offset, 15, 15)

#घोषणा REG_FIELD_SPLIT_BITS_16_31(_name, _offset)		\
	[_name##_##0]  = REG_FIELD(_offset, 16, 16),		\
	[_name##_##1]  = REG_FIELD(_offset, 17, 17),	\
	[_name##_##2]  = REG_FIELD(_offset, 18, 18),	\
	[_name##_##3]  = REG_FIELD(_offset, 19, 19),	\
	[_name##_##4]  = REG_FIELD(_offset, 20, 20),	\
	[_name##_##5]  = REG_FIELD(_offset, 21, 21),	\
	[_name##_##6]  = REG_FIELD(_offset, 22, 22),	\
	[_name##_##7]  = REG_FIELD(_offset, 23, 23),	\
	[_name##_##8]  = REG_FIELD(_offset, 24, 24),	\
	[_name##_##9]  = REG_FIELD(_offset, 25, 25),	\
	[_name##_##10] = REG_FIELD(_offset, 26, 26),	\
	[_name##_##11] = REG_FIELD(_offset, 27, 27),	\
	[_name##_##12] = REG_FIELD(_offset, 28, 28),	\
	[_name##_##13] = REG_FIELD(_offset, 29, 29),	\
	[_name##_##14] = REG_FIELD(_offset, 30, 30),	\
	[_name##_##15] = REG_FIELD(_offset, 31, 31)

/*
 * reg_field IDs to use as an index पूर्णांकo an array
 * If you change the order of the entries, check the devm_regmap_field_alloc()
 * calls in init_common()
 */
क्रमागत regfield_ids अणु
	/* ----- SROT ------ */
	/* HW_VER */
	VER_MAJOR,
	VER_MINOR,
	VER_STEP,
	/* CTRL_OFFSET */
	TSENS_EN,
	TSENS_SW_RST,
	SENSOR_EN,
	CODE_OR_TEMP,

	/* ----- TM ------ */
	/* TRDY */
	TRDY,
	/* INTERRUPT ENABLE */
	INT_EN,	/* v2+ has separate enables क्रम crit, upper and lower irq */
	/* STATUS */
	LAST_TEMP_0,	/* Last temperature पढ़ोing */
	LAST_TEMP_1,
	LAST_TEMP_2,
	LAST_TEMP_3,
	LAST_TEMP_4,
	LAST_TEMP_5,
	LAST_TEMP_6,
	LAST_TEMP_7,
	LAST_TEMP_8,
	LAST_TEMP_9,
	LAST_TEMP_10,
	LAST_TEMP_11,
	LAST_TEMP_12,
	LAST_TEMP_13,
	LAST_TEMP_14,
	LAST_TEMP_15,
	VALID_0,		/* VALID पढ़ोing or not */
	VALID_1,
	VALID_2,
	VALID_3,
	VALID_4,
	VALID_5,
	VALID_6,
	VALID_7,
	VALID_8,
	VALID_9,
	VALID_10,
	VALID_11,
	VALID_12,
	VALID_13,
	VALID_14,
	VALID_15,
	LOWER_STATUS_0,	/* LOWER threshold violated */
	LOWER_STATUS_1,
	LOWER_STATUS_2,
	LOWER_STATUS_3,
	LOWER_STATUS_4,
	LOWER_STATUS_5,
	LOWER_STATUS_6,
	LOWER_STATUS_7,
	LOWER_STATUS_8,
	LOWER_STATUS_9,
	LOWER_STATUS_10,
	LOWER_STATUS_11,
	LOWER_STATUS_12,
	LOWER_STATUS_13,
	LOWER_STATUS_14,
	LOWER_STATUS_15,
	LOW_INT_STATUS_0,	/* LOWER पूर्णांकerrupt status */
	LOW_INT_STATUS_1,
	LOW_INT_STATUS_2,
	LOW_INT_STATUS_3,
	LOW_INT_STATUS_4,
	LOW_INT_STATUS_5,
	LOW_INT_STATUS_6,
	LOW_INT_STATUS_7,
	LOW_INT_STATUS_8,
	LOW_INT_STATUS_9,
	LOW_INT_STATUS_10,
	LOW_INT_STATUS_11,
	LOW_INT_STATUS_12,
	LOW_INT_STATUS_13,
	LOW_INT_STATUS_14,
	LOW_INT_STATUS_15,
	LOW_INT_CLEAR_0,	/* LOWER पूर्णांकerrupt clear */
	LOW_INT_CLEAR_1,
	LOW_INT_CLEAR_2,
	LOW_INT_CLEAR_3,
	LOW_INT_CLEAR_4,
	LOW_INT_CLEAR_5,
	LOW_INT_CLEAR_6,
	LOW_INT_CLEAR_7,
	LOW_INT_CLEAR_8,
	LOW_INT_CLEAR_9,
	LOW_INT_CLEAR_10,
	LOW_INT_CLEAR_11,
	LOW_INT_CLEAR_12,
	LOW_INT_CLEAR_13,
	LOW_INT_CLEAR_14,
	LOW_INT_CLEAR_15,
	LOW_INT_MASK_0,	/* LOWER पूर्णांकerrupt mask */
	LOW_INT_MASK_1,
	LOW_INT_MASK_2,
	LOW_INT_MASK_3,
	LOW_INT_MASK_4,
	LOW_INT_MASK_5,
	LOW_INT_MASK_6,
	LOW_INT_MASK_7,
	LOW_INT_MASK_8,
	LOW_INT_MASK_9,
	LOW_INT_MASK_10,
	LOW_INT_MASK_11,
	LOW_INT_MASK_12,
	LOW_INT_MASK_13,
	LOW_INT_MASK_14,
	LOW_INT_MASK_15,
	LOW_THRESH_0,		/* LOWER threshold values */
	LOW_THRESH_1,
	LOW_THRESH_2,
	LOW_THRESH_3,
	LOW_THRESH_4,
	LOW_THRESH_5,
	LOW_THRESH_6,
	LOW_THRESH_7,
	LOW_THRESH_8,
	LOW_THRESH_9,
	LOW_THRESH_10,
	LOW_THRESH_11,
	LOW_THRESH_12,
	LOW_THRESH_13,
	LOW_THRESH_14,
	LOW_THRESH_15,
	UPPER_STATUS_0,	/* UPPER threshold violated */
	UPPER_STATUS_1,
	UPPER_STATUS_2,
	UPPER_STATUS_3,
	UPPER_STATUS_4,
	UPPER_STATUS_5,
	UPPER_STATUS_6,
	UPPER_STATUS_7,
	UPPER_STATUS_8,
	UPPER_STATUS_9,
	UPPER_STATUS_10,
	UPPER_STATUS_11,
	UPPER_STATUS_12,
	UPPER_STATUS_13,
	UPPER_STATUS_14,
	UPPER_STATUS_15,
	UP_INT_STATUS_0,	/* UPPER पूर्णांकerrupt status */
	UP_INT_STATUS_1,
	UP_INT_STATUS_2,
	UP_INT_STATUS_3,
	UP_INT_STATUS_4,
	UP_INT_STATUS_5,
	UP_INT_STATUS_6,
	UP_INT_STATUS_7,
	UP_INT_STATUS_8,
	UP_INT_STATUS_9,
	UP_INT_STATUS_10,
	UP_INT_STATUS_11,
	UP_INT_STATUS_12,
	UP_INT_STATUS_13,
	UP_INT_STATUS_14,
	UP_INT_STATUS_15,
	UP_INT_CLEAR_0,	/* UPPER पूर्णांकerrupt clear */
	UP_INT_CLEAR_1,
	UP_INT_CLEAR_2,
	UP_INT_CLEAR_3,
	UP_INT_CLEAR_4,
	UP_INT_CLEAR_5,
	UP_INT_CLEAR_6,
	UP_INT_CLEAR_7,
	UP_INT_CLEAR_8,
	UP_INT_CLEAR_9,
	UP_INT_CLEAR_10,
	UP_INT_CLEAR_11,
	UP_INT_CLEAR_12,
	UP_INT_CLEAR_13,
	UP_INT_CLEAR_14,
	UP_INT_CLEAR_15,
	UP_INT_MASK_0,		/* UPPER पूर्णांकerrupt mask */
	UP_INT_MASK_1,
	UP_INT_MASK_2,
	UP_INT_MASK_3,
	UP_INT_MASK_4,
	UP_INT_MASK_5,
	UP_INT_MASK_6,
	UP_INT_MASK_7,
	UP_INT_MASK_8,
	UP_INT_MASK_9,
	UP_INT_MASK_10,
	UP_INT_MASK_11,
	UP_INT_MASK_12,
	UP_INT_MASK_13,
	UP_INT_MASK_14,
	UP_INT_MASK_15,
	UP_THRESH_0,		/* UPPER threshold values */
	UP_THRESH_1,
	UP_THRESH_2,
	UP_THRESH_3,
	UP_THRESH_4,
	UP_THRESH_5,
	UP_THRESH_6,
	UP_THRESH_7,
	UP_THRESH_8,
	UP_THRESH_9,
	UP_THRESH_10,
	UP_THRESH_11,
	UP_THRESH_12,
	UP_THRESH_13,
	UP_THRESH_14,
	UP_THRESH_15,
	CRITICAL_STATUS_0,	/* CRITICAL threshold violated */
	CRITICAL_STATUS_1,
	CRITICAL_STATUS_2,
	CRITICAL_STATUS_3,
	CRITICAL_STATUS_4,
	CRITICAL_STATUS_5,
	CRITICAL_STATUS_6,
	CRITICAL_STATUS_7,
	CRITICAL_STATUS_8,
	CRITICAL_STATUS_9,
	CRITICAL_STATUS_10,
	CRITICAL_STATUS_11,
	CRITICAL_STATUS_12,
	CRITICAL_STATUS_13,
	CRITICAL_STATUS_14,
	CRITICAL_STATUS_15,
	CRIT_INT_STATUS_0,	/* CRITICAL पूर्णांकerrupt status */
	CRIT_INT_STATUS_1,
	CRIT_INT_STATUS_2,
	CRIT_INT_STATUS_3,
	CRIT_INT_STATUS_4,
	CRIT_INT_STATUS_5,
	CRIT_INT_STATUS_6,
	CRIT_INT_STATUS_7,
	CRIT_INT_STATUS_8,
	CRIT_INT_STATUS_9,
	CRIT_INT_STATUS_10,
	CRIT_INT_STATUS_11,
	CRIT_INT_STATUS_12,
	CRIT_INT_STATUS_13,
	CRIT_INT_STATUS_14,
	CRIT_INT_STATUS_15,
	CRIT_INT_CLEAR_0,	/* CRITICAL पूर्णांकerrupt clear */
	CRIT_INT_CLEAR_1,
	CRIT_INT_CLEAR_2,
	CRIT_INT_CLEAR_3,
	CRIT_INT_CLEAR_4,
	CRIT_INT_CLEAR_5,
	CRIT_INT_CLEAR_6,
	CRIT_INT_CLEAR_7,
	CRIT_INT_CLEAR_8,
	CRIT_INT_CLEAR_9,
	CRIT_INT_CLEAR_10,
	CRIT_INT_CLEAR_11,
	CRIT_INT_CLEAR_12,
	CRIT_INT_CLEAR_13,
	CRIT_INT_CLEAR_14,
	CRIT_INT_CLEAR_15,
	CRIT_INT_MASK_0,	/* CRITICAL पूर्णांकerrupt mask */
	CRIT_INT_MASK_1,
	CRIT_INT_MASK_2,
	CRIT_INT_MASK_3,
	CRIT_INT_MASK_4,
	CRIT_INT_MASK_5,
	CRIT_INT_MASK_6,
	CRIT_INT_MASK_7,
	CRIT_INT_MASK_8,
	CRIT_INT_MASK_9,
	CRIT_INT_MASK_10,
	CRIT_INT_MASK_11,
	CRIT_INT_MASK_12,
	CRIT_INT_MASK_13,
	CRIT_INT_MASK_14,
	CRIT_INT_MASK_15,
	CRIT_THRESH_0,		/* CRITICAL threshold values */
	CRIT_THRESH_1,
	CRIT_THRESH_2,
	CRIT_THRESH_3,
	CRIT_THRESH_4,
	CRIT_THRESH_5,
	CRIT_THRESH_6,
	CRIT_THRESH_7,
	CRIT_THRESH_8,
	CRIT_THRESH_9,
	CRIT_THRESH_10,
	CRIT_THRESH_11,
	CRIT_THRESH_12,
	CRIT_THRESH_13,
	CRIT_THRESH_14,
	CRIT_THRESH_15,

	/* WATCHDOG */
	WDOG_BARK_STATUS,
	WDOG_BARK_CLEAR,
	WDOG_BARK_MASK,
	WDOG_BARK_COUNT,

	/* CYCLE COMPLETION MONITOR */
	CC_MON_STATUS,
	CC_MON_CLEAR,
	CC_MON_MASK,

	MIN_STATUS_0,		/* MIN threshold violated */
	MIN_STATUS_1,
	MIN_STATUS_2,
	MIN_STATUS_3,
	MIN_STATUS_4,
	MIN_STATUS_5,
	MIN_STATUS_6,
	MIN_STATUS_7,
	MIN_STATUS_8,
	MIN_STATUS_9,
	MIN_STATUS_10,
	MIN_STATUS_11,
	MIN_STATUS_12,
	MIN_STATUS_13,
	MIN_STATUS_14,
	MIN_STATUS_15,
	MAX_STATUS_0,		/* MAX threshold violated */
	MAX_STATUS_1,
	MAX_STATUS_2,
	MAX_STATUS_3,
	MAX_STATUS_4,
	MAX_STATUS_5,
	MAX_STATUS_6,
	MAX_STATUS_7,
	MAX_STATUS_8,
	MAX_STATUS_9,
	MAX_STATUS_10,
	MAX_STATUS_11,
	MAX_STATUS_12,
	MAX_STATUS_13,
	MAX_STATUS_14,
	MAX_STATUS_15,

	/* Keep last */
	MAX_REGFIELDS
पूर्ण;

/**
 * काष्ठा tsens_features - Features supported by the IP
 * @ver_major: Major number of IP version
 * @crit_पूर्णांक: करोes the IP support critical पूर्णांकerrupts?
 * @adc:      करो the sensors only output adc code (instead of temperature)?
 * @srot_split: करोes the IP neatly splits the रेजिस्टर space पूर्णांकo SROT and TM,
 *              with SROT only being available to secure boot firmware?
 * @has_watchकरोg: करोes this IP support watchकरोg functionality?
 * @max_sensors: maximum sensors supported by this version of the IP
 */
काष्ठा tsens_features अणु
	अचिन्हित पूर्णांक ver_major;
	अचिन्हित पूर्णांक crit_पूर्णांक:1;
	अचिन्हित पूर्णांक adc:1;
	अचिन्हित पूर्णांक srot_split:1;
	अचिन्हित पूर्णांक has_watchकरोg:1;
	अचिन्हित पूर्णांक max_sensors;
पूर्ण;

/**
 * काष्ठा tsens_plat_data - tsens compile-समय platक्रमm data
 * @num_sensors: Number of sensors supported by platक्रमm
 * @ops: operations the tsens instance supports
 * @hw_ids: Subset of sensors ids supported by platक्रमm, अगर not the first n
 * @feat: features of the IP
 * @fields: bitfield locations
 */
काष्ठा tsens_plat_data अणु
	स्थिर u32		num_sensors;
	स्थिर काष्ठा tsens_ops	*ops;
	अचिन्हित पूर्णांक		*hw_ids;
	काष्ठा tsens_features	*feat;
	स्थिर काष्ठा reg_field		*fields;
पूर्ण;

/**
 * काष्ठा tsens_context - Registers to be saved/restored across a context loss
 * @threshold: Threshold रेजिस्टर value
 * @control: Control रेजिस्टर value
 */
काष्ठा tsens_context अणु
	पूर्णांक	threshold;
	पूर्णांक	control;
पूर्ण;

/**
 * काष्ठा tsens_priv - निजी data क्रम each instance of the tsens IP
 * @dev: poपूर्णांकer to काष्ठा device
 * @num_sensors: number of sensors enabled on this device
 * @पंचांग_map: poपूर्णांकer to TM रेजिस्टर address space
 * @srot_map: poपूर्णांकer to SROT रेजिस्टर address space
 * @पंचांग_offset: deal with old device trees that करोn't address TM and SROT
 *             address space separately
 * @ul_lock: lock जबतक processing upper/lower threshold पूर्णांकerrupts
 * @crit_lock: lock जबतक processing critical threshold पूर्णांकerrupts
 * @rf: array of regmap_fields used to store value of the field
 * @ctx: रेजिस्टरs to be saved and restored during suspend/resume
 * @feat: features of the IP
 * @fields: bitfield locations
 * @ops: poपूर्णांकer to list of callbacks supported by this device
 * @debug_root: poपूर्णांकer to debugfs dentry क्रम all tsens
 * @debug: poपूर्णांकer to debugfs dentry क्रम tsens controller
 * @sensor: list of sensors attached to this device
 */
काष्ठा tsens_priv अणु
	काष्ठा device			*dev;
	u32				num_sensors;
	काष्ठा regmap			*पंचांग_map;
	काष्ठा regmap			*srot_map;
	u32				पंचांग_offset;

	/* lock क्रम upper/lower threshold पूर्णांकerrupts */
	spinlock_t			ul_lock;

	काष्ठा regmap_field		*rf[MAX_REGFIELDS];
	काष्ठा tsens_context		ctx;
	काष्ठा tsens_features		*feat;
	स्थिर काष्ठा reg_field		*fields;
	स्थिर काष्ठा tsens_ops		*ops;

	काष्ठा dentry			*debug_root;
	काष्ठा dentry			*debug;

	काष्ठा tsens_sensor		sensor[];
पूर्ण;

अक्षर *qfprom_पढ़ो(काष्ठा device *dev, स्थिर अक्षर *cname);
व्योम compute_पूर्णांकercept_slope(काष्ठा tsens_priv *priv, u32 *pt1, u32 *pt2, u32 mode);
पूर्णांक init_common(काष्ठा tsens_priv *priv);
पूर्णांक get_temp_tsens_valid(स्थिर काष्ठा tsens_sensor *s, पूर्णांक *temp);
पूर्णांक get_temp_common(स्थिर काष्ठा tsens_sensor *s, पूर्णांक *temp);

/* TSENS target */
बाह्य काष्ठा tsens_plat_data data_8960;

/* TSENS v0.1 tarमाला_लो */
बाह्य काष्ठा tsens_plat_data data_8916, data_8939, data_8974, data_9607;

/* TSENS v1 tarमाला_लो */
बाह्य काष्ठा tsens_plat_data data_tsens_v1, data_8976;

/* TSENS v2 tarमाला_लो */
बाह्य काष्ठा tsens_plat_data data_8996, data_tsens_v2;

#पूर्ण_अगर /* __QCOM_TSENS_H__ */
