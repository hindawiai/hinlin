<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Definitions क्रम TI EMIF device platक्रमm data
 *
 * Copyright (C) 2012 Texas Instruments, Inc.
 *
 * Aneesh V <aneesh@ti.com>
 */
#अगर_अघोषित __EMIF_PLAT_H
#घोषणा __EMIF_PLAT_H

/* Low घातer modes - EMIF_PWR_MGMT_CTRL */
#घोषणा EMIF_LP_MODE_DISABLE				0
#घोषणा EMIF_LP_MODE_CLOCK_STOP				1
#घोषणा EMIF_LP_MODE_SELF_REFRESH			2
#घोषणा EMIF_LP_MODE_PWR_DN				4

/* Hardware capabilities */
#घोषणा	EMIF_HW_CAPS_LL_INTERFACE			0x00000001

/*
 * EMIF IP Revisions
 *	EMIF4D  - Used in OMAP4
 *	EMIF4D5 - Used in OMAP5
 */
#घोषणा	EMIF_4D						1
#घोषणा	EMIF_4D5					2

/*
 * PHY types
 *	ATTILAPHY  - Used in OMAP4
 *	INTELLIPHY - Used in OMAP5
 */
#घोषणा	EMIF_PHY_TYPE_ATTILAPHY				1
#घोषणा	EMIF_PHY_TYPE_INTELLIPHY			2

/* Custom config requests */
#घोषणा EMIF_CUSTOM_CONFIG_LPMODE			0x00000001
#घोषणा EMIF_CUSTOM_CONFIG_TEMP_ALERT_POLL_INTERVAL	0x00000002
#घोषणा EMIF_CUSTOM_CONFIG_EXTENDED_TEMP_PART		0x00000004

#अगर_अघोषित __ASSEMBLY__
/**
 * काष्ठा ddr_device_info - All inक्रमmation about the DDR device except AC
 *		timing parameters
 * @type:	Device type (LPDDR2-S4, LPDDR2-S2 etc)
 * @density:	Device density
 * @io_width:	Bus width
 * @cs1_used:	Whether there is a DDR device attached to the second
 *		chip-select(CS1) of this EMIF instance
 * @cal_resistors_per_cs: Whether there is one calibration resistor per
 *		chip-select or whether it's a single one क्रम both
 * @manufacturer: Manufacturer name string
 */
काष्ठा ddr_device_info अणु
	u32	type;
	u32	density;
	u32	io_width;
	u32	cs1_used;
	u32	cal_resistors_per_cs;
	अक्षर	manufacturer[10];
पूर्ण;

/**
 * काष्ठा emअगर_custom_configs - Custom configuration parameters/policies
 *		passed from the platक्रमm layer
 * @mask:	Mask to indicate which configs are requested
 * @lpmode:	LPMODE to be used in PWR_MGMT_CTRL रेजिस्टर
 * @lpmode_समयout_perक्रमmance: Timeout beक्रमe LPMODE entry when higher
 *		perक्रमmance is desired at the cost of घातer (typically
 *		at higher OPPs)
 * @lpmode_समयout_घातer: Timeout beक्रमe LPMODE entry when better घातer
 *		savings is desired and perक्रमmance is not important
 *		(typically at lower loads indicated by lower OPPs)
 * @lpmode_freq_threshold: The DDR frequency threshold to identअगरy between
 *		the above two हालs:
 *		समयout = (freq >= lpmode_freq_threshold) ?
 *			lpmode_समयout_perक्रमmance :
 *			lpmode_समयout_घातer;
 * @temp_alert_poll_पूर्णांकerval_ms: LPDDR2 MR4 polling पूर्णांकerval at nominal
 *		temperature(in milliseconds). When temperature is high
 *		polling is करोne 4 बार as frequently.
 */
काष्ठा emअगर_custom_configs अणु
	u32 mask;
	u32 lpmode;
	u32 lpmode_समयout_perक्रमmance;
	u32 lpmode_समयout_घातer;
	u32 lpmode_freq_threshold;
	u32 temp_alert_poll_पूर्णांकerval_ms;
पूर्ण;

/**
 * काष्ठा emअगर_platक्रमm_data - Platक्रमm data passed on EMIF platक्रमm
 *				device creation. Used by the driver.
 * @hw_caps:		Hw capabilities of the EMIF IP in the respective SoC
 * @device_info:	Device info काष्ठाure containing inक्रमmation such
 *			as type, bus width, density etc
 * @timings:		Timings inक्रमmation from device datasheet passed
 *			as an array of 'struct lpddr2_timings'. Can be शून्य
 *			अगर अगर शेष timings are ok
 * @timings_arr_size:	Size of the timings array. Depends on the number
 *			of dअगरferent frequencies क्रम which timings data
 *			is provided
 * @min_tck:		Minimum value of some timing parameters in terms
 *			of number of cycles. Can be शून्य अगर शेष values
 *			are ok
 * @custom_configs:	Custom configurations requested by SoC or board
 *			code and the data क्रम them. Can be शून्य अगर शेष
 *			configurations करोne by the driver are ok. See
 *			करोcumentation क्रम 'struct emif_custom_configs' क्रम
 *			more details
 */
काष्ठा emअगर_platक्रमm_data अणु
	u32 hw_caps;
	काष्ठा ddr_device_info *device_info;
	स्थिर काष्ठा lpddr2_timings *timings;
	u32 timings_arr_size;
	स्थिर काष्ठा lpddr2_min_tck *min_tck;
	काष्ठा emअगर_custom_configs *custom_configs;
	u32 ip_rev;
	u32 phy_type;
पूर्ण;
#पूर्ण_अगर /* __ASSEMBLY__ */

#पूर्ण_अगर /* __LINUX_EMIF_H */
