<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Platक्रमm data क्रम Arizona devices
 *
 * Copyright 2012 Wolfson Microelectronics. PLC.
 */

#अगर_अघोषित _ARIZONA_PDATA_H
#घोषणा _ARIZONA_PDATA_H

#समावेश <dt-bindings/mfd/arizona.h>
#समावेश <linux/regulator/arizona-lकरो1.h>
#समावेश <linux/regulator/arizona-micsupp.h>

#घोषणा ARIZONA_GPN_सूची_MASK                     0x8000  /* GPN_सूची */
#घोषणा ARIZONA_GPN_सूची_SHIFT                        15  /* GPN_सूची */
#घोषणा ARIZONA_GPN_सूची_WIDTH                         1  /* GPN_सूची */
#घोषणा ARIZONA_GPN_PU_MASK                      0x4000  /* GPN_PU */
#घोषणा ARIZONA_GPN_PU_SHIFT                         14  /* GPN_PU */
#घोषणा ARIZONA_GPN_PU_WIDTH                          1  /* GPN_PU */
#घोषणा ARIZONA_GPN_PD_MASK                      0x2000  /* GPN_PD */
#घोषणा ARIZONA_GPN_PD_SHIFT                         13  /* GPN_PD */
#घोषणा ARIZONA_GPN_PD_WIDTH                          1  /* GPN_PD */
#घोषणा ARIZONA_GPN_LVL_MASK                     0x0800  /* GPN_LVL */
#घोषणा ARIZONA_GPN_LVL_SHIFT                        11  /* GPN_LVL */
#घोषणा ARIZONA_GPN_LVL_WIDTH                         1  /* GPN_LVL */
#घोषणा ARIZONA_GPN_POL_MASK                     0x0400  /* GPN_POL */
#घोषणा ARIZONA_GPN_POL_SHIFT                        10  /* GPN_POL */
#घोषणा ARIZONA_GPN_POL_WIDTH                         1  /* GPN_POL */
#घोषणा ARIZONA_GPN_OP_CFG_MASK                  0x0200  /* GPN_OP_CFG */
#घोषणा ARIZONA_GPN_OP_CFG_SHIFT                      9  /* GPN_OP_CFG */
#घोषणा ARIZONA_GPN_OP_CFG_WIDTH                      1  /* GPN_OP_CFG */
#घोषणा ARIZONA_GPN_DB_MASK                      0x0100  /* GPN_DB */
#घोषणा ARIZONA_GPN_DB_SHIFT                          8  /* GPN_DB */
#घोषणा ARIZONA_GPN_DB_WIDTH                          1  /* GPN_DB */
#घोषणा ARIZONA_GPN_FN_MASK                      0x007F  /* GPN_FN - [6:0] */
#घोषणा ARIZONA_GPN_FN_SHIFT                          0  /* GPN_FN - [6:0] */
#घोषणा ARIZONA_GPN_FN_WIDTH                          7  /* GPN_FN - [6:0] */

#घोषणा ARIZONA_MAX_GPIO 5

#घोषणा ARIZONA_MAX_INPUT 4

#घोषणा ARIZONA_MAX_MICBIAS 3

#घोषणा ARIZONA_MAX_OUTPUT 6

#घोषणा ARIZONA_MAX_AIF 3

#घोषणा ARIZONA_HAP_ACT_ERM 0
#घोषणा ARIZONA_HAP_ACT_LRA 2

#घोषणा ARIZONA_MAX_PDM_SPK 2

काष्ठा regulator_init_data;
काष्ठा gpio_desc;

काष्ठा arizona_micbias अणु
	पूर्णांक mV;                    /** Regulated voltage */
	अचिन्हित पूर्णांक ext_cap:1;    /** External capacitor fitted */
	अचिन्हित पूर्णांक disअक्षरge:1;  /** Actively disअक्षरge */
	अचिन्हित पूर्णांक soft_start:1; /** Disable aggressive startup ramp rate */
	अचिन्हित पूर्णांक bypass:1;     /** Use bypass mode */
पूर्ण;

काष्ठा arizona_micd_config अणु
	अचिन्हित पूर्णांक src;
	अचिन्हित पूर्णांक bias;
	bool gpio;
पूर्ण;

काष्ठा arizona_micd_range अणु
	पूर्णांक max;  /** Ohms */
	पूर्णांक key;  /** Key to report to input layer */
पूर्ण;

काष्ठा arizona_pdata अणु
	काष्ठा gpio_desc *reset;      /** GPIO controlling /RESET, अगर any */

	/** Regulator configuration क्रम MICVDD */
	काष्ठा arizona_micsupp_pdata micvdd;

	/** Regulator configuration क्रम LDO1 */
	काष्ठा arizona_lकरो1_pdata lकरो1;

	/** If a direct 32kHz घड़ी is provided on an MCLK specअगरy it here */
	पूर्णांक clk32k_src;

	/** Mode क्रम primary IRQ (शेषs to active low) */
	अचिन्हित पूर्णांक irq_flags;

	/* Base GPIO */
	पूर्णांक gpio_base;

	/** Pin state क्रम GPIO pins */
	अचिन्हित पूर्णांक gpio_शेषs[ARIZONA_MAX_GPIO];

	/**
	 * Maximum number of channels घड़ीs will be generated क्रम,
	 * useful क्रम प्रणालीs where and I2S bus with multiple data
	 * lines is mastered.
	 */
	अचिन्हित पूर्णांक max_channels_घड़ीed[ARIZONA_MAX_AIF];

	/** GPIO5 is used क्रम jack detection */
	bool jd_gpio5;

	/** Internal pull on GPIO5 is disabled when used क्रम jack detection */
	bool jd_gpio5_nopull;

	/** set to true अगर jackdet contact खोलोs on insert */
	bool jd_invert;

	/** Use the headphone detect circuit to identअगरy the accessory */
	bool hpdet_acc_id;

	/** Check क्रम line output with HPDET method */
	bool hpdet_acc_id_line;

	/** GPIO used क्रम mic isolation with HPDET */
	पूर्णांक hpdet_id_gpio;

	/** Channel to use क्रम headphone detection */
	अचिन्हित पूर्णांक hpdet_channel;

	/** Use software comparison to determine mic presence */
	bool micd_software_compare;

	/** Extra debounce समयout used during initial mic detection (ms) */
	अचिन्हित पूर्णांक micd_detect_debounce;

	/** GPIO क्रम mic detection polarity */
	पूर्णांक micd_pol_gpio;

	/** Mic detect ramp rate */
	अचिन्हित पूर्णांक micd_bias_start_समय;

	/** Mic detect sample rate */
	अचिन्हित पूर्णांक micd_rate;

	/** Mic detect debounce level */
	अचिन्हित पूर्णांक micd_dbसमय;

	/** Mic detect समयout (ms) */
	अचिन्हित पूर्णांक micd_समयout;

	/** Force MICBIAS on क्रम mic detect */
	bool micd_क्रमce_micbias;

	/** Mic detect level parameters */
	स्थिर काष्ठा arizona_micd_range *micd_ranges;
	पूर्णांक num_micd_ranges;

	/** Headset polarity configurations */
	काष्ठा arizona_micd_config *micd_configs;
	पूर्णांक num_micd_configs;

	/** Reference voltage क्रम DMIC inमाला_दो */
	पूर्णांक dmic_ref[ARIZONA_MAX_INPUT];

	/** MICBIAS configurations */
	काष्ठा arizona_micbias micbias[ARIZONA_MAX_MICBIAS];

	/**
	 * Mode of input काष्ठाures
	 * One of the ARIZONA_INMODE_xxx values
	 * wm5102/wm5110/wm8280/wm8997: [0]=IN1 [1]=IN2 [2]=IN3 [3]=IN4
	 * wm8998: [0]=IN1A [1]=IN2A [2]=IN1B [3]=IN2B
	 */
	पूर्णांक inmode[ARIZONA_MAX_INPUT];

	/** Mode क्रम outमाला_दो */
	पूर्णांक out_mono[ARIZONA_MAX_OUTPUT];

	/** Limit output volumes */
	अचिन्हित पूर्णांक out_vol_limit[2 * ARIZONA_MAX_OUTPUT];

	/** PDM speaker mute setting */
	अचिन्हित पूर्णांक spk_mute[ARIZONA_MAX_PDM_SPK];

	/** PDM speaker क्रमmat */
	अचिन्हित पूर्णांक spk_fmt[ARIZONA_MAX_PDM_SPK];

	/** Haptic actuator type */
	अचिन्हित पूर्णांक hap_act;

	/** GPIO क्रम primary IRQ (used क्रम edge triggered emulation) */
	पूर्णांक irq_gpio;

	/** General purpose चयन control */
	अचिन्हित पूर्णांक gpsw;
पूर्ण;

#पूर्ण_अगर
