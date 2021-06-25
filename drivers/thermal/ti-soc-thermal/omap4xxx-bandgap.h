<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * OMAP4xxx bandgap रेजिस्टरs, bitfields and temperature definitions
 *
 * Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/
 * Contact:
 *   Eduarकरो Valentin <eduarकरो.valentin@ti.com>
 */
#अगर_अघोषित __OMAP4XXX_BANDGAP_H
#घोषणा __OMAP4XXX_BANDGAP_H

/**
 * *** OMAP4430 ***
 *
 * Below, in sequence, are the Register definitions,
 * the bitfields and the temperature definitions क्रम OMAP4430.
 */

/**
 * OMAP4430 रेजिस्टर definitions
 *
 * Registers are defined as offsets. The offsets are
 * relative to FUSE_OPP_BGAP on 4430.
 */

/* OMAP4430.FUSE_OPP_BGAP */
#घोषणा OMAP4430_FUSE_OPP_BGAP				0x0

/* OMAP4430.TEMP_SENSOR  */
#घोषणा OMAP4430_TEMP_SENSOR_CTRL_OFFSET		0xCC

/**
 * Register and bit definitions क्रम OMAP4430
 *
 * All the macros bellow define the required bits क्रम
 * controlling temperature on OMAP4430. Bit defines are
 * grouped by रेजिस्टर.
 */

/* OMAP4430.TEMP_SENSOR bits */
#घोषणा OMAP4430_BGAP_TEMPSOFF_MASK			BIT(12)
#घोषणा OMAP4430_BGAP_TSHUT_MASK			BIT(11)
#घोषणा OMAP4430_CONTINUOUS_MODE_MASK			BIT(10)
#घोषणा OMAP4430_BGAP_TEMP_SENSOR_SOC_MASK		BIT(9)
#घोषणा OMAP4430_BGAP_TEMP_SENSOR_EOCZ_MASK		BIT(8)
#घोषणा OMAP4430_BGAP_TEMP_SENSOR_DTEMP_MASK		(0xff << 0)

/**
 * Temperature limits and thresholds क्रम OMAP4430
 *
 * All the macros bellow are definitions क्रम handling the
 * ADC conversions and representation of temperature limits
 * and thresholds क्रम OMAP4430.
 */

/*
 * ADC conversion table limits. Ignore values outside the TRM listed
 * range to aव्योम bogus thermal shutकरोwns. See omap4430 TRM chapter
 * "18.4.10.2.3 ADC Codes Versus Temperature".
 */
#घोषणा OMAP4430_ADC_START_VALUE			13
#घोषणा OMAP4430_ADC_END_VALUE				107
/* bandgap घड़ी limits (no control on 4430) */
#घोषणा OMAP4430_MAX_FREQ				32768
#घोषणा OMAP4430_MIN_FREQ				32768

/**
 * *** OMAP4460 *** Applicable क्रम OMAP4470
 *
 * Below, in sequence, are the Register definitions,
 * the bitfields and the temperature definitions क्रम OMAP4460.
 */

/**
 * OMAP4460 रेजिस्टर definitions
 *
 * Registers are defined as offsets. The offsets are
 * relative to FUSE_OPP_BGAP on 4460.
 */

/* OMAP4460.FUSE_OPP_BGAP */
#घोषणा OMAP4460_FUSE_OPP_BGAP				0x0

/* OMAP4460.TEMP_SENSOR */
#घोषणा OMAP4460_TEMP_SENSOR_CTRL_OFFSET		0xCC

/* OMAP4460.BANDGAP_CTRL */
#घोषणा OMAP4460_BGAP_CTRL_OFFSET			0x118

/* OMAP4460.BANDGAP_COUNTER */
#घोषणा OMAP4460_BGAP_COUNTER_OFFSET			0x11C

/* OMAP4460.BANDGAP_THRESHOLD */
#घोषणा OMAP4460_BGAP_THRESHOLD_OFFSET			0x120

/* OMAP4460.TSHUT_THRESHOLD */
#घोषणा OMAP4460_BGAP_TSHUT_OFFSET			0x124

/* OMAP4460.BANDGAP_STATUS */
#घोषणा OMAP4460_BGAP_STATUS_OFFSET			0x128

/**
 * Register bitfields क्रम OMAP4460
 *
 * All the macros bellow define the required bits क्रम
 * controlling temperature on OMAP4460. Bit defines are
 * grouped by रेजिस्टर.
 */
/* OMAP4460.TEMP_SENSOR bits */
#घोषणा OMAP4460_BGAP_TEMPSOFF_MASK			BIT(13)
#घोषणा OMAP4460_BGAP_TEMP_SENSOR_SOC_MASK		BIT(11)
#घोषणा OMAP4460_BGAP_TEMP_SENSOR_EOCZ_MASK		BIT(10)
#घोषणा OMAP4460_BGAP_TEMP_SENSOR_DTEMP_MASK		(0x3ff << 0)

/* OMAP4460.BANDGAP_CTRL bits */
#घोषणा OMAP4460_CONTINUOUS_MODE_MASK			BIT(31)
#घोषणा OMAP4460_MASK_HOT_MASK				BIT(1)
#घोषणा OMAP4460_MASK_COLD_MASK				BIT(0)

/* OMAP4460.BANDGAP_COUNTER bits */
#घोषणा OMAP4460_COUNTER_MASK				(0xffffff << 0)

/* OMAP4460.BANDGAP_THRESHOLD bits */
#घोषणा OMAP4460_T_HOT_MASK				(0x3ff << 16)
#घोषणा OMAP4460_T_COLD_MASK				(0x3ff << 0)

/* OMAP4460.TSHUT_THRESHOLD bits */
#घोषणा OMAP4460_TSHUT_HOT_MASK				(0x3ff << 16)
#घोषणा OMAP4460_TSHUT_COLD_MASK			(0x3ff << 0)

/* OMAP4460.BANDGAP_STATUS bits */
#घोषणा OMAP4460_HOT_FLAG_MASK				BIT(1)
#घोषणा OMAP4460_COLD_FLAG_MASK				BIT(0)

/**
 * Temperature limits and thresholds क्रम OMAP4460
 *
 * All the macros bellow are definitions क्रम handling the
 * ADC conversions and representation of temperature limits
 * and thresholds क्रम OMAP4460.
 */

/* ADC conversion table limits */
#घोषणा OMAP4460_ADC_START_VALUE			530
#घोषणा OMAP4460_ADC_END_VALUE				932
/* bandgap घड़ी limits */
#घोषणा OMAP4460_MAX_FREQ				1500000
#घोषणा OMAP4460_MIN_FREQ				1000000
/* पूर्णांकerrupts thresholds */
#घोषणा OMAP4460_TSHUT_HOT				900	/* 122 deg C */
#घोषणा OMAP4460_TSHUT_COLD				895	/* 100 deg C */
#घोषणा OMAP4460_T_HOT					800	/* 73 deg C */
#घोषणा OMAP4460_T_COLD					795	/* 71 deg C */

#पूर्ण_अगर /* __OMAP4XXX_BANDGAP_H */
