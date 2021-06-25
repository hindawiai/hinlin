<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * twl_core.c - driver क्रम TWL4030/TWL5030/TWL60X0/TPS659x0 PM
 * and audio CODEC devices
 *
 * Copyright (C) 2005-2006 Texas Instruments, Inc.
 *
 * Modअगरications to defer पूर्णांकerrupt handling to a kernel thपढ़ो:
 * Copyright (C) 2006 MontaVista Software, Inc.
 *
 * Based on tlv320aic23.c:
 * Copyright (c) by Kai Svahn <kai.svahn@nokia.com>
 *
 * Code cleanup and modअगरications to IRQ handler.
 * by syed khasim <x0khasim@ti.com>
 */

#समावेश <linux/init.h>
#समावेश <linux/mutex.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/clk.h>
#समावेश <linux/err.h>
#समावेश <linux/device.h>
#समावेश <linux/of.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/irq.h>
#समावेश <linux/irqकरोमुख्य.h>

#समावेश <linux/regulator/machine.h>

#समावेश <linux/i2c.h>
#समावेश <linux/mfd/twl.h>

/* Register descriptions क्रम audio */
#समावेश <linux/mfd/twl4030-audपन.स>

#समावेश "twl-core.h"

/*
 * The TWL4030 "Triton 2" is one of a family of a multi-function "Power
 * Management and System Companion Device" chips originally deचिन्हित क्रम
 * use in OMAP2 and OMAP 3 based प्रणालीs.  Its control पूर्णांकerfaces use I2C,
 * often at around 3 Mbit/sec, including क्रम पूर्णांकerrupt handling.
 *
 * This driver core provides genirq support क्रम the पूर्णांकerrupts emitted,
 * by the various modules, and exports रेजिस्टर access primitives.
 *
 * FIXME this driver currently requires use of the first पूर्णांकerrupt line
 * (and associated रेजिस्टरs).
 */

#घोषणा DRIVER_NAME			"twl"

/* Triton Core पूर्णांकernal inक्रमmation (BEGIN) */

/* Base Address defns क्रम twl4030_map[] */

/* subchip/slave 0 - USB ID */
#घोषणा TWL4030_BASEADD_USB		0x0000

/* subchip/slave 1 - AUD ID */
#घोषणा TWL4030_BASEADD_AUDIO_VOICE	0x0000
#घोषणा TWL4030_BASEADD_GPIO		0x0098
#घोषणा TWL4030_BASEADD_INTBR		0x0085
#घोषणा TWL4030_BASEADD_PIH		0x0080
#घोषणा TWL4030_BASEADD_TEST		0x004C

/* subchip/slave 2 - AUX ID */
#घोषणा TWL4030_BASEADD_INTERRUPTS	0x00B9
#घोषणा TWL4030_BASEADD_LED		0x00EE
#घोषणा TWL4030_BASEADD_MADC		0x0000
#घोषणा TWL4030_BASEADD_MAIN_CHARGE	0x0074
#घोषणा TWL4030_BASEADD_PRECHARGE	0x00AA
#घोषणा TWL4030_BASEADD_PWM		0x00F8
#घोषणा TWL4030_BASEADD_KEYPAD		0x00D2

#घोषणा TWL5031_BASEADD_ACCESSORY	0x0074 /* Replaces Main Charge */
#घोषणा TWL5031_BASEADD_INTERRUPTS	0x00B9 /* Dअगरferent than TWL4030's
						  one */

/* subchip/slave 3 - POWER ID */
#घोषणा TWL4030_BASEADD_BACKUP		0x0014
#घोषणा TWL4030_BASEADD_INT		0x002E
#घोषणा TWL4030_BASEADD_PM_MASTER	0x0036

#घोषणा TWL4030_BASEADD_PM_RECEIVER	0x005B
#घोषणा TWL4030_DCDC_GLOBAL_CFG		0x06
#घोषणा SMARTREFLEX_ENABLE		BIT(3)

#घोषणा TWL4030_BASEADD_RTC		0x001C
#घोषणा TWL4030_BASEADD_SECURED_REG	0x0000

/* Triton Core पूर्णांकernal inक्रमmation (END) */


/* subchip/slave 0 0x48 - POWER */
#घोषणा TWL6030_BASEADD_RTC		0x0000
#घोषणा TWL6030_BASEADD_SECURED_REG	0x0017
#घोषणा TWL6030_BASEADD_PM_MASTER	0x001F
#घोषणा TWL6030_BASEADD_PM_SLAVE_MISC	0x0030 /* PM_RECEIVER */
#घोषणा TWL6030_BASEADD_PM_MISC		0x00E2
#घोषणा TWL6030_BASEADD_PM_PUPD		0x00F0

/* subchip/slave 1 0x49 - FEATURE */
#घोषणा TWL6030_BASEADD_USB		0x0000
#घोषणा TWL6030_BASEADD_GPADC_CTRL	0x002E
#घोषणा TWL6030_BASEADD_AUX		0x0090
#घोषणा TWL6030_BASEADD_PWM		0x00BA
#घोषणा TWL6030_BASEADD_GASGAUGE	0x00C0
#घोषणा TWL6030_BASEADD_PIH		0x00D0
#घोषणा TWL6030_BASEADD_CHARGER		0x00E0
#घोषणा TWL6032_BASEADD_CHARGER		0x00DA
#घोषणा TWL6030_BASEADD_LED		0x00F4

/* subchip/slave 2 0x4A - DFT */
#घोषणा TWL6030_BASEADD_DIEID		0x00C0

/* subchip/slave 3 0x4B - AUDIO */
#घोषणा TWL6030_BASEADD_AUDIO		0x0000
#घोषणा TWL6030_BASEADD_RSV		0x0000
#घोषणा TWL6030_BASEADD_ZERO		0x0000

/* Few घातer values */
#घोषणा R_CFG_BOOT			0x05

/* some fields in R_CFG_BOOT */
#घोषणा HFCLK_FREQ_19p2_MHZ		(1 << 0)
#घोषणा HFCLK_FREQ_26_MHZ		(2 << 0)
#घोषणा HFCLK_FREQ_38p4_MHZ		(3 << 0)
#घोषणा HIGH_PERF_SQ			(1 << 3)
#घोषणा CK32K_LOWPWR_EN			(1 << 7)

/*----------------------------------------------------------------------*/

/* Structure क्रम each TWL4030/TWL6030 Slave */
काष्ठा twl_client अणु
	काष्ठा i2c_client *client;
	काष्ठा regmap *regmap;
पूर्ण;

/* mapping the module id to slave id and base address */
काष्ठा twl_mapping अणु
	अचिन्हित अक्षर sid;	/* Slave ID */
	अचिन्हित अक्षर base;	/* base address */
पूर्ण;

काष्ठा twl_निजी अणु
	bool पढ़ोy; /* The core driver is पढ़ोy to be used */
	u32 twl_idcode; /* TWL IDCODE Register value */
	अचिन्हित पूर्णांक twl_id;

	काष्ठा twl_mapping *twl_map;
	काष्ठा twl_client *twl_modules;
पूर्ण;

अटल काष्ठा twl_निजी *twl_priv;

अटल काष्ठा twl_mapping twl4030_map[] = अणु
	/*
	 * NOTE:  करोn't change this table without updating the
	 * <linux/mfd/twl.h> defines क्रम TWL4030_MODULE_*
	 * so they जारी to match the order in this table.
	 */

	/* Common IPs */
	अणु 0, TWL4030_BASEADD_USB पूर्ण,
	अणु 1, TWL4030_BASEADD_PIH पूर्ण,
	अणु 2, TWL4030_BASEADD_MAIN_CHARGE पूर्ण,
	अणु 3, TWL4030_BASEADD_PM_MASTER पूर्ण,
	अणु 3, TWL4030_BASEADD_PM_RECEIVER पूर्ण,

	अणु 3, TWL4030_BASEADD_RTC पूर्ण,
	अणु 2, TWL4030_BASEADD_PWM पूर्ण,
	अणु 2, TWL4030_BASEADD_LED पूर्ण,
	अणु 3, TWL4030_BASEADD_SECURED_REG पूर्ण,

	/* TWL4030 specअगरic IPs */
	अणु 1, TWL4030_BASEADD_AUDIO_VOICE पूर्ण,
	अणु 1, TWL4030_BASEADD_GPIO पूर्ण,
	अणु 1, TWL4030_BASEADD_INTBR पूर्ण,
	अणु 1, TWL4030_BASEADD_TEST पूर्ण,
	अणु 2, TWL4030_BASEADD_KEYPAD पूर्ण,

	अणु 2, TWL4030_BASEADD_MADC पूर्ण,
	अणु 2, TWL4030_BASEADD_INTERRUPTS पूर्ण,
	अणु 2, TWL4030_BASEADD_PRECHARGE पूर्ण,
	अणु 3, TWL4030_BASEADD_BACKUP पूर्ण,
	अणु 3, TWL4030_BASEADD_INT पूर्ण,

	अणु 2, TWL5031_BASEADD_ACCESSORY पूर्ण,
	अणु 2, TWL5031_BASEADD_INTERRUPTS पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा reg_शेष twl4030_49_शेषs[] = अणु
	/* Audio Registers */
	अणु 0x01, 0x00पूर्ण, /* CODEC_MODE	*/
	अणु 0x02, 0x00पूर्ण, /* OPTION	*/
	/* 0x03  Unused	*/
	अणु 0x04, 0x00पूर्ण, /* MICBIAS_CTL	*/
	अणु 0x05, 0x00पूर्ण, /* ANAMICL	*/
	अणु 0x06, 0x00पूर्ण, /* ANAMICR	*/
	अणु 0x07, 0x00पूर्ण, /* AVADC_CTL	*/
	अणु 0x08, 0x00पूर्ण, /* ADCMICSEL	*/
	अणु 0x09, 0x00पूर्ण, /* DIGMIXING	*/
	अणु 0x0a, 0x0fपूर्ण, /* ATXL1PGA	*/
	अणु 0x0b, 0x0fपूर्ण, /* ATXR1PGA	*/
	अणु 0x0c, 0x0fपूर्ण, /* AVTXL2PGA	*/
	अणु 0x0d, 0x0fपूर्ण, /* AVTXR2PGA	*/
	अणु 0x0e, 0x00पूर्ण, /* AUDIO_IF	*/
	अणु 0x0f, 0x00पूर्ण, /* VOICE_IF	*/
	अणु 0x10, 0x3fपूर्ण, /* ARXR1PGA	*/
	अणु 0x11, 0x3fपूर्ण, /* ARXL1PGA	*/
	अणु 0x12, 0x3fपूर्ण, /* ARXR2PGA	*/
	अणु 0x13, 0x3fपूर्ण, /* ARXL2PGA	*/
	अणु 0x14, 0x25पूर्ण, /* VRXPGA	*/
	अणु 0x15, 0x00पूर्ण, /* VSTPGA	*/
	अणु 0x16, 0x00पूर्ण, /* VRX2ARXPGA	*/
	अणु 0x17, 0x00पूर्ण, /* AVDAC_CTL	*/
	अणु 0x18, 0x00पूर्ण, /* ARX2VTXPGA	*/
	अणु 0x19, 0x32पूर्ण, /* ARXL1_APGA_CTL*/
	अणु 0x1a, 0x32पूर्ण, /* ARXR1_APGA_CTL*/
	अणु 0x1b, 0x32पूर्ण, /* ARXL2_APGA_CTL*/
	अणु 0x1c, 0x32पूर्ण, /* ARXR2_APGA_CTL*/
	अणु 0x1d, 0x00पूर्ण, /* ATX2ARXPGA	*/
	अणु 0x1e, 0x00पूर्ण, /* BT_IF		*/
	अणु 0x1f, 0x55पूर्ण, /* BTPGA		*/
	अणु 0x20, 0x00पूर्ण, /* BTSTPGA	*/
	अणु 0x21, 0x00पूर्ण, /* EAR_CTL	*/
	अणु 0x22, 0x00पूर्ण, /* HS_SEL	*/
	अणु 0x23, 0x00पूर्ण, /* HS_GAIN_SET	*/
	अणु 0x24, 0x00पूर्ण, /* HS_POPN_SET	*/
	अणु 0x25, 0x00पूर्ण, /* PREDL_CTL	*/
	अणु 0x26, 0x00पूर्ण, /* PREDR_CTL	*/
	अणु 0x27, 0x00पूर्ण, /* PRECKL_CTL	*/
	अणु 0x28, 0x00पूर्ण, /* PRECKR_CTL	*/
	अणु 0x29, 0x00पूर्ण, /* HFL_CTL	*/
	अणु 0x2a, 0x00पूर्ण, /* HFR_CTL	*/
	अणु 0x2b, 0x05पूर्ण, /* ALC_CTL	*/
	अणु 0x2c, 0x00पूर्ण, /* ALC_SET1	*/
	अणु 0x2d, 0x00पूर्ण, /* ALC_SET2	*/
	अणु 0x2e, 0x00पूर्ण, /* BOOST_CTL	*/
	अणु 0x2f, 0x00पूर्ण, /* SOFTVOL_CTL	*/
	अणु 0x30, 0x13पूर्ण, /* DTMF_FREQSEL	*/
	अणु 0x31, 0x00पूर्ण, /* DTMF_TONEXT1H	*/
	अणु 0x32, 0x00पूर्ण, /* DTMF_TONEXT1L	*/
	अणु 0x33, 0x00पूर्ण, /* DTMF_TONEXT2H	*/
	अणु 0x34, 0x00पूर्ण, /* DTMF_TONEXT2L	*/
	अणु 0x35, 0x79पूर्ण, /* DTMF_TONOFF	*/
	अणु 0x36, 0x11पूर्ण, /* DTMF_WANONOFF	*/
	अणु 0x37, 0x00पूर्ण, /* I2S_RX_SCRAMBLE_H */
	अणु 0x38, 0x00पूर्ण, /* I2S_RX_SCRAMBLE_M */
	अणु 0x39, 0x00पूर्ण, /* I2S_RX_SCRAMBLE_L */
	अणु 0x3a, 0x06पूर्ण, /* APLL_CTL */
	अणु 0x3b, 0x00पूर्ण, /* DTMF_CTL */
	अणु 0x3c, 0x44पूर्ण, /* DTMF_PGA_CTL2	(0x3C) */
	अणु 0x3d, 0x69पूर्ण, /* DTMF_PGA_CTL1	(0x3D) */
	अणु 0x3e, 0x00पूर्ण, /* MISC_SET_1 */
	अणु 0x3f, 0x00पूर्ण, /* PCMBTMUX */
	/* 0x40 - 0x42  Unused */
	अणु 0x43, 0x00पूर्ण, /* RX_PATH_SEL */
	अणु 0x44, 0x32पूर्ण, /* VDL_APGA_CTL */
	अणु 0x45, 0x00पूर्ण, /* VIBRA_CTL */
	अणु 0x46, 0x00पूर्ण, /* VIBRA_SET */
	अणु 0x47, 0x00पूर्ण, /* VIBRA_PWM_SET	*/
	अणु 0x48, 0x00पूर्ण, /* ANAMIC_GAIN	*/
	अणु 0x49, 0x00पूर्ण, /* MISC_SET_2	*/
	/* End of Audio Registers */
पूर्ण;

अटल bool twl4030_49_nop_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल 0x00:
	हाल 0x03:
	हाल 0x40:
	हाल 0x41:
	हाल 0x42:
		वापस false;
	शेष:
		वापस true;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा regmap_range twl4030_49_अस्थिर_ranges[] = अणु
	regmap_reg_range(TWL4030_BASEADD_TEST, 0xff),
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table twl4030_49_अस्थिर_table = अणु
	.yes_ranges = twl4030_49_अस्थिर_ranges,
	.n_yes_ranges = ARRAY_SIZE(twl4030_49_अस्थिर_ranges),
पूर्ण;

अटल स्थिर काष्ठा regmap_config twl4030_regmap_config[4] = अणु
	अणु
		/* Address 0x48 */
		.reg_bits = 8,
		.val_bits = 8,
		.max_रेजिस्टर = 0xff,
	पूर्ण,
	अणु
		/* Address 0x49 */
		.reg_bits = 8,
		.val_bits = 8,
		.max_रेजिस्टर = 0xff,

		.पढ़ोable_reg = twl4030_49_nop_reg,
		.ग_लिखोable_reg = twl4030_49_nop_reg,

		.अस्थिर_table = &twl4030_49_अस्थिर_table,

		.reg_शेषs = twl4030_49_शेषs,
		.num_reg_शेषs = ARRAY_SIZE(twl4030_49_शेषs),
		.cache_type = REGCACHE_RBTREE,
	पूर्ण,
	अणु
		/* Address 0x4a */
		.reg_bits = 8,
		.val_bits = 8,
		.max_रेजिस्टर = 0xff,
	पूर्ण,
	अणु
		/* Address 0x4b */
		.reg_bits = 8,
		.val_bits = 8,
		.max_रेजिस्टर = 0xff,
	पूर्ण,
पूर्ण;

अटल काष्ठा twl_mapping twl6030_map[] = अणु
	/*
	 * NOTE:  करोn't change this table without updating the
	 * <linux/mfd/twl.h> defines क्रम TWL4030_MODULE_*
	 * so they जारी to match the order in this table.
	 */

	/* Common IPs */
	अणु 1, TWL6030_BASEADD_USB पूर्ण,
	अणु 1, TWL6030_BASEADD_PIH पूर्ण,
	अणु 1, TWL6030_BASEADD_CHARGER पूर्ण,
	अणु 0, TWL6030_BASEADD_PM_MASTER पूर्ण,
	अणु 0, TWL6030_BASEADD_PM_SLAVE_MISC पूर्ण,

	अणु 0, TWL6030_BASEADD_RTC पूर्ण,
	अणु 1, TWL6030_BASEADD_PWM पूर्ण,
	अणु 1, TWL6030_BASEADD_LED पूर्ण,
	अणु 0, TWL6030_BASEADD_SECURED_REG पूर्ण,

	/* TWL6030 specअगरic IPs */
	अणु 0, TWL6030_BASEADD_ZERO पूर्ण,
	अणु 1, TWL6030_BASEADD_ZERO पूर्ण,
	अणु 2, TWL6030_BASEADD_ZERO पूर्ण,
	अणु 1, TWL6030_BASEADD_GPADC_CTRL पूर्ण,
	अणु 1, TWL6030_BASEADD_GASGAUGE पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_config twl6030_regmap_config[3] = अणु
	अणु
		/* Address 0x48 */
		.reg_bits = 8,
		.val_bits = 8,
		.max_रेजिस्टर = 0xff,
	पूर्ण,
	अणु
		/* Address 0x49 */
		.reg_bits = 8,
		.val_bits = 8,
		.max_रेजिस्टर = 0xff,
	पूर्ण,
	अणु
		/* Address 0x4a */
		.reg_bits = 8,
		.val_bits = 8,
		.max_रेजिस्टर = 0xff,
	पूर्ण,
पूर्ण;

/*----------------------------------------------------------------------*/

अटल अंतरभूत पूर्णांक twl_get_num_slaves(व्योम)
अणु
	अगर (twl_class_is_4030())
		वापस 4; /* TWL4030 class have four slave address */
	अन्यथा
		वापस 3; /* TWL6030 class have three slave address */
पूर्ण

अटल अंतरभूत पूर्णांक twl_get_last_module(व्योम)
अणु
	अगर (twl_class_is_4030())
		वापस TWL4030_MODULE_LAST;
	अन्यथा
		वापस TWL6030_MODULE_LAST;
पूर्ण

/* Exported Functions */

अचिन्हित पूर्णांक twl_rev(व्योम)
अणु
	वापस twl_priv ? twl_priv->twl_id : 0;
पूर्ण
EXPORT_SYMBOL(twl_rev);

/**
 * twl_get_regmap - Get the regmap associated with the given module
 * @mod_no: module number
 *
 * Returns the regmap poपूर्णांकer or शून्य in हाल of failure.
 */
अटल काष्ठा regmap *twl_get_regmap(u8 mod_no)
अणु
	पूर्णांक sid;
	काष्ठा twl_client *twl;

	अगर (unlikely(!twl_priv || !twl_priv->पढ़ोy)) अणु
		pr_err("%s: not initialized\n", DRIVER_NAME);
		वापस शून्य;
	पूर्ण
	अगर (unlikely(mod_no >= twl_get_last_module())) अणु
		pr_err("%s: invalid module number %d\n", DRIVER_NAME, mod_no);
		वापस शून्य;
	पूर्ण

	sid = twl_priv->twl_map[mod_no].sid;
	twl = &twl_priv->twl_modules[sid];

	वापस twl->regmap;
पूर्ण

/**
 * twl_i2c_ग_लिखो - Writes a n bit रेजिस्टर in TWL4030/TWL5030/TWL60X0
 * @mod_no: module number
 * @value: an array of num_bytes+1 containing data to ग_लिखो
 * @reg: रेजिस्टर address (just offset will करो)
 * @num_bytes: number of bytes to transfer
 *
 * Returns 0 on success or अन्यथा a negative error code.
 */
पूर्णांक twl_i2c_ग_लिखो(u8 mod_no, u8 *value, u8 reg, अचिन्हित num_bytes)
अणु
	काष्ठा regmap *regmap = twl_get_regmap(mod_no);
	पूर्णांक ret;

	अगर (!regmap)
		वापस -EPERM;

	ret = regmap_bulk_ग_लिखो(regmap, twl_priv->twl_map[mod_no].base + reg,
				value, num_bytes);

	अगर (ret)
		pr_err("%s: Write failed (mod %d, reg 0x%02x count %d)\n",
		       DRIVER_NAME, mod_no, reg, num_bytes);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(twl_i2c_ग_लिखो);

/**
 * twl_i2c_पढ़ो - Reads a n bit रेजिस्टर in TWL4030/TWL5030/TWL60X0
 * @mod_no: module number
 * @value: an array of num_bytes containing data to be पढ़ो
 * @reg: रेजिस्टर address (just offset will करो)
 * @num_bytes: number of bytes to transfer
 *
 * Returns 0 on success or अन्यथा a negative error code.
 */
पूर्णांक twl_i2c_पढ़ो(u8 mod_no, u8 *value, u8 reg, अचिन्हित num_bytes)
अणु
	काष्ठा regmap *regmap = twl_get_regmap(mod_no);
	पूर्णांक ret;

	अगर (!regmap)
		वापस -EPERM;

	ret = regmap_bulk_पढ़ो(regmap, twl_priv->twl_map[mod_no].base + reg,
			       value, num_bytes);

	अगर (ret)
		pr_err("%s: Read failed (mod %d, reg 0x%02x count %d)\n",
		       DRIVER_NAME, mod_no, reg, num_bytes);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(twl_i2c_पढ़ो);

/**
 * twl_regcache_bypass - Configure the regcache bypass क्रम the regmap associated
 *			 with the module
 * @mod_no: module number
 * @enable: Regcache bypass state
 *
 * Returns 0 अन्यथा failure.
 */
पूर्णांक twl_set_regcache_bypass(u8 mod_no, bool enable)
अणु
	काष्ठा regmap *regmap = twl_get_regmap(mod_no);

	अगर (!regmap)
		वापस -EPERM;

	regcache_cache_bypass(regmap, enable);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(twl_set_regcache_bypass);

/*----------------------------------------------------------------------*/

/**
 * twl_पढ़ो_idcode_रेजिस्टर - API to पढ़ो the IDCODE रेजिस्टर.
 *
 * Unlocks the IDCODE रेजिस्टर and पढ़ो the 32 bit value.
 */
अटल पूर्णांक twl_पढ़ो_idcode_रेजिस्टर(व्योम)
अणु
	पूर्णांक err;

	err = twl_i2c_ग_लिखो_u8(TWL4030_MODULE_INTBR, TWL_EEPROM_R_UNLOCK,
						REG_UNLOCK_TEST_REG);
	अगर (err) अणु
		pr_err("TWL4030 Unable to unlock IDCODE registers -%d\n", err);
		जाओ fail;
	पूर्ण

	err = twl_i2c_पढ़ो(TWL4030_MODULE_INTBR, (u8 *)(&twl_priv->twl_idcode),
						REG_IDCODE_7_0, 4);
	अगर (err) अणु
		pr_err("TWL4030: unable to read IDCODE -%d\n", err);
		जाओ fail;
	पूर्ण

	err = twl_i2c_ग_लिखो_u8(TWL4030_MODULE_INTBR, 0x0, REG_UNLOCK_TEST_REG);
	अगर (err)
		pr_err("TWL4030 Unable to relock IDCODE registers -%d\n", err);
fail:
	वापस err;
पूर्ण

/**
 * twl_get_type - API to get TWL Si type.
 *
 * Api to get the TWL Si type from IDCODE value.
 */
पूर्णांक twl_get_type(व्योम)
अणु
	वापस TWL_SIL_TYPE(twl_priv->twl_idcode);
पूर्ण
EXPORT_SYMBOL_GPL(twl_get_type);

/**
 * twl_get_version - API to get TWL Si version.
 *
 * Api to get the TWL Si version from IDCODE value.
 */
पूर्णांक twl_get_version(व्योम)
अणु
	वापस TWL_SIL_REV(twl_priv->twl_idcode);
पूर्ण
EXPORT_SYMBOL_GPL(twl_get_version);

/**
 * twl_get_hfclk_rate - API to get TWL बाह्यal HFCLK घड़ी rate.
 *
 * Api to get the TWL HFCLK rate based on BOOT_CFG रेजिस्टर.
 */
पूर्णांक twl_get_hfclk_rate(व्योम)
अणु
	u8 ctrl;
	पूर्णांक rate;

	twl_i2c_पढ़ो_u8(TWL_MODULE_PM_MASTER, &ctrl, R_CFG_BOOT);

	चयन (ctrl & 0x3) अणु
	हाल HFCLK_FREQ_19p2_MHZ:
		rate = 19200000;
		अवरोध;
	हाल HFCLK_FREQ_26_MHZ:
		rate = 26000000;
		अवरोध;
	हाल HFCLK_FREQ_38p4_MHZ:
		rate = 38400000;
		अवरोध;
	शेष:
		pr_err("TWL4030: HFCLK is not configured\n");
		rate = -EINVAL;
		अवरोध;
	पूर्ण

	वापस rate;
पूर्ण
EXPORT_SYMBOL_GPL(twl_get_hfclk_rate);

अटल काष्ठा device *
add_numbered_child(अचिन्हित mod_no, स्थिर अक्षर *name, पूर्णांक num,
		व्योम *pdata, अचिन्हित pdata_len,
		bool can_wakeup, पूर्णांक irq0, पूर्णांक irq1)
अणु
	काष्ठा platक्रमm_device	*pdev;
	काष्ठा twl_client	*twl;
	पूर्णांक			status, sid;

	अगर (unlikely(mod_no >= twl_get_last_module())) अणु
		pr_err("%s: invalid module number %d\n", DRIVER_NAME, mod_no);
		वापस ERR_PTR(-EPERM);
	पूर्ण
	sid = twl_priv->twl_map[mod_no].sid;
	twl = &twl_priv->twl_modules[sid];

	pdev = platक्रमm_device_alloc(name, num);
	अगर (!pdev)
		वापस ERR_PTR(-ENOMEM);

	pdev->dev.parent = &twl->client->dev;

	अगर (pdata) अणु
		status = platक्रमm_device_add_data(pdev, pdata, pdata_len);
		अगर (status < 0) अणु
			dev_dbg(&pdev->dev, "can't add platform_data\n");
			जाओ put_device;
		पूर्ण
	पूर्ण

	अगर (irq0) अणु
		काष्ठा resource r[2] = अणु
			अणु .start = irq0, .flags = IORESOURCE_IRQ, पूर्ण,
			अणु .start = irq1, .flags = IORESOURCE_IRQ, पूर्ण,
		पूर्ण;

		status = platक्रमm_device_add_resources(pdev, r, irq1 ? 2 : 1);
		अगर (status < 0) अणु
			dev_dbg(&pdev->dev, "can't add irqs\n");
			जाओ put_device;
		पूर्ण
	पूर्ण

	status = platक्रमm_device_add(pdev);
	अगर (status)
		जाओ put_device;

	device_init_wakeup(&pdev->dev, can_wakeup);

	वापस &pdev->dev;

put_device:
	platक्रमm_device_put(pdev);
	dev_err(&twl->client->dev, "failed to add device %s\n", name);
	वापस ERR_PTR(status);
पूर्ण

अटल अंतरभूत काष्ठा device *add_child(अचिन्हित mod_no, स्थिर अक्षर *name,
		व्योम *pdata, अचिन्हित pdata_len,
		bool can_wakeup, पूर्णांक irq0, पूर्णांक irq1)
अणु
	वापस add_numbered_child(mod_no, name, -1, pdata, pdata_len,
		can_wakeup, irq0, irq1);
पूर्ण

अटल काष्ठा device *
add_regulator_linked(पूर्णांक num, काष्ठा regulator_init_data *pdata,
		काष्ठा regulator_consumer_supply *consumers,
		अचिन्हित num_consumers, अचिन्हित दीर्घ features)
अणु
	काष्ठा twl_regulator_driver_data drv_data;

	/* regulator framework demands init_data ... */
	अगर (!pdata)
		वापस शून्य;

	अगर (consumers) अणु
		pdata->consumer_supplies = consumers;
		pdata->num_consumer_supplies = num_consumers;
	पूर्ण

	अगर (pdata->driver_data) अणु
		/* If we have existing drv_data, just add the flags */
		काष्ठा twl_regulator_driver_data *पंचांगp;
		पंचांगp = pdata->driver_data;
		पंचांगp->features |= features;
	पूर्ण अन्यथा अणु
		/* add new driver data काष्ठा, used only during init */
		drv_data.features = features;
		drv_data.set_voltage = शून्य;
		drv_data.get_voltage = शून्य;
		drv_data.data = शून्य;
		pdata->driver_data = &drv_data;
	पूर्ण

	/* NOTE:  we currently ignore regulator IRQs, e.g. क्रम लघु circuits */
	वापस add_numbered_child(TWL_MODULE_PM_MASTER, "twl_reg", num,
		pdata, माप(*pdata), false, 0, 0);
पूर्ण

अटल काष्ठा device *
add_regulator(पूर्णांक num, काष्ठा regulator_init_data *pdata,
		अचिन्हित दीर्घ features)
अणु
	वापस add_regulator_linked(num, pdata, शून्य, 0, features);
पूर्ण

/*
 * NOTE:  We know the first 8 IRQs after pdata->base_irq are
 * क्रम the PIH, and the next are क्रम the PWR_INT SIH, since
 * that's how twl_init_irq() sets things up.
 */

अटल पूर्णांक
add_children(काष्ठा twl4030_platक्रमm_data *pdata, अचिन्हित irq_base,
		अचिन्हित दीर्घ features)
अणु
	काष्ठा device	*child;

	अगर (IS_ENABLED(CONFIG_GPIO_TWL4030) && pdata->gpio) अणु
		child = add_child(TWL4030_MODULE_GPIO, "twl4030_gpio",
				pdata->gpio, माप(*pdata->gpio),
				false, irq_base + GPIO_INTR_OFFSET, 0);
		अगर (IS_ERR(child))
			वापस PTR_ERR(child);
	पूर्ण

	अगर (IS_ENABLED(CONFIG_KEYBOARD_TWL4030) && pdata->keypad) अणु
		child = add_child(TWL4030_MODULE_KEYPAD, "twl4030_keypad",
				pdata->keypad, माप(*pdata->keypad),
				true, irq_base + KEYPAD_INTR_OFFSET, 0);
		अगर (IS_ERR(child))
			वापस PTR_ERR(child);
	पूर्ण

	अगर (IS_ENABLED(CONFIG_TWL4030_MADC) && pdata->madc &&
	    twl_class_is_4030()) अणु
		child = add_child(TWL4030_MODULE_MADC, "twl4030_madc",
				pdata->madc, माप(*pdata->madc),
				true, irq_base + MADC_INTR_OFFSET, 0);
		अगर (IS_ERR(child))
			वापस PTR_ERR(child);
	पूर्ण

	अगर (IS_ENABLED(CONFIG_RTC_DRV_TWL4030)) अणु
		/*
		 * REVISIT platक्रमm_data here currently might expose the
		 * "msecure" line ... but क्रम now we just expect board
		 * setup to tell the chip "it's always ok to SET_TIME".
		 * Eventually, Linux might become more aware of such
		 * HW security concerns, and "least privilege".
		 */
		child = add_child(TWL_MODULE_RTC, "twl_rtc", शून्य, 0,
				true, irq_base + RTC_INTR_OFFSET, 0);
		अगर (IS_ERR(child))
			वापस PTR_ERR(child);
	पूर्ण

	अगर (IS_ENABLED(CONFIG_PWM_TWL)) अणु
		child = add_child(TWL_MODULE_PWM, "twl-pwm", शून्य, 0,
				  false, 0, 0);
		अगर (IS_ERR(child))
			वापस PTR_ERR(child);
	पूर्ण

	अगर (IS_ENABLED(CONFIG_PWM_TWL_LED)) अणु
		child = add_child(TWL_MODULE_LED, "twl-pwmled", शून्य, 0,
				  false, 0, 0);
		अगर (IS_ERR(child))
			वापस PTR_ERR(child);
	पूर्ण

	अगर (IS_ENABLED(CONFIG_TWL4030_USB) && pdata->usb &&
	    twl_class_is_4030()) अणु

		अटल काष्ठा regulator_consumer_supply usb1v5 = अणु
			.supply =	"usb1v5",
		पूर्ण;
		अटल काष्ठा regulator_consumer_supply usb1v8 = अणु
			.supply =	"usb1v8",
		पूर्ण;
		अटल काष्ठा regulator_consumer_supply usb3v1 = अणु
			.supply =	"usb3v1",
		पूर्ण;

	/* First add the regulators so that they can be used by transceiver */
		अगर (IS_ENABLED(CONFIG_REGULATOR_TWL4030)) अणु
			/* this is a ढाँचा that माला_लो copied */
			काष्ठा regulator_init_data usb_fixed = अणु
				.स्थिरraपूर्णांकs.valid_modes_mask =
					REGULATOR_MODE_NORMAL
					| REGULATOR_MODE_STANDBY,
				.स्थिरraपूर्णांकs.valid_ops_mask =
					REGULATOR_CHANGE_MODE
					| REGULATOR_CHANGE_STATUS,
			पूर्ण;

			child = add_regulator_linked(TWL4030_REG_VUSB1V5,
						      &usb_fixed, &usb1v5, 1,
						      features);
			अगर (IS_ERR(child))
				वापस PTR_ERR(child);

			child = add_regulator_linked(TWL4030_REG_VUSB1V8,
						      &usb_fixed, &usb1v8, 1,
						      features);
			अगर (IS_ERR(child))
				वापस PTR_ERR(child);

			child = add_regulator_linked(TWL4030_REG_VUSB3V1,
						      &usb_fixed, &usb3v1, 1,
						      features);
			अगर (IS_ERR(child))
				वापस PTR_ERR(child);

		पूर्ण

		child = add_child(TWL_MODULE_USB, "twl4030_usb",
				pdata->usb, माप(*pdata->usb), true,
				/* irq0 = USB_PRES, irq1 = USB */
				irq_base + USB_PRES_INTR_OFFSET,
				irq_base + USB_INTR_OFFSET);

		अगर (IS_ERR(child))
			वापस PTR_ERR(child);

		/* we need to connect regulators to this transceiver */
		अगर (IS_ENABLED(CONFIG_REGULATOR_TWL4030) && child) अणु
			usb1v5.dev_name = dev_name(child);
			usb1v8.dev_name = dev_name(child);
			usb3v1.dev_name = dev_name(child);
		पूर्ण
	पूर्ण

	अगर (IS_ENABLED(CONFIG_TWL4030_WATCHDOG) && twl_class_is_4030()) अणु
		child = add_child(TWL_MODULE_PM_RECEIVER, "twl4030_wdt", शून्य,
				  0, false, 0, 0);
		अगर (IS_ERR(child))
			वापस PTR_ERR(child);
	पूर्ण

	अगर (IS_ENABLED(CONFIG_INPUT_TWL4030_PWRBUTTON) && twl_class_is_4030()) अणु
		child = add_child(TWL_MODULE_PM_MASTER, "twl4030_pwrbutton",
				  शून्य, 0, true, irq_base + 8 + 0, 0);
		अगर (IS_ERR(child))
			वापस PTR_ERR(child);
	पूर्ण

	अगर (IS_ENABLED(CONFIG_MFD_TWL4030_AUDIO) && pdata->audio &&
	    twl_class_is_4030()) अणु
		child = add_child(TWL4030_MODULE_AUDIO_VOICE, "twl4030-audio",
				pdata->audio, माप(*pdata->audio),
				false, 0, 0);
		अगर (IS_ERR(child))
			वापस PTR_ERR(child);
	पूर्ण

	/* twl4030 regulators */
	अगर (IS_ENABLED(CONFIG_REGULATOR_TWL4030) && twl_class_is_4030()) अणु
		child = add_regulator(TWL4030_REG_VPLL1, pdata->vpll1,
					features);
		अगर (IS_ERR(child))
			वापस PTR_ERR(child);

		child = add_regulator(TWL4030_REG_VIO, pdata->vio,
					features);
		अगर (IS_ERR(child))
			वापस PTR_ERR(child);

		child = add_regulator(TWL4030_REG_VDD1, pdata->vdd1,
					features);
		अगर (IS_ERR(child))
			वापस PTR_ERR(child);

		child = add_regulator(TWL4030_REG_VDD2, pdata->vdd2,
					features);
		अगर (IS_ERR(child))
			वापस PTR_ERR(child);

		child = add_regulator(TWL4030_REG_VMMC1, pdata->vmmc1,
					features);
		अगर (IS_ERR(child))
			वापस PTR_ERR(child);

		child = add_regulator(TWL4030_REG_VDAC, pdata->vdac,
					features);
		अगर (IS_ERR(child))
			वापस PTR_ERR(child);

		child = add_regulator((features & TWL4030_VAUX2)
					? TWL4030_REG_VAUX2_4030
					: TWL4030_REG_VAUX2,
				pdata->vaux2, features);
		अगर (IS_ERR(child))
			वापस PTR_ERR(child);

		child = add_regulator(TWL4030_REG_VINTANA1, pdata->vपूर्णांकana1,
					features);
		अगर (IS_ERR(child))
			वापस PTR_ERR(child);

		child = add_regulator(TWL4030_REG_VINTANA2, pdata->vपूर्णांकana2,
					features);
		अगर (IS_ERR(child))
			वापस PTR_ERR(child);

		child = add_regulator(TWL4030_REG_VINTDIG, pdata->vपूर्णांकdig,
					features);
		अगर (IS_ERR(child))
			वापस PTR_ERR(child);
	पूर्ण

	/* maybe add LDOs that are omitted on cost-reduced parts */
	अगर (IS_ENABLED(CONFIG_REGULATOR_TWL4030) && !(features & TPS_SUBSET)
	  && twl_class_is_4030()) अणु
		child = add_regulator(TWL4030_REG_VPLL2, pdata->vpll2,
					features);
		अगर (IS_ERR(child))
			वापस PTR_ERR(child);

		child = add_regulator(TWL4030_REG_VMMC2, pdata->vmmc2,
					features);
		अगर (IS_ERR(child))
			वापस PTR_ERR(child);

		child = add_regulator(TWL4030_REG_VSIM, pdata->vsim,
					features);
		अगर (IS_ERR(child))
			वापस PTR_ERR(child);

		child = add_regulator(TWL4030_REG_VAUX1, pdata->vaux1,
					features);
		अगर (IS_ERR(child))
			वापस PTR_ERR(child);

		child = add_regulator(TWL4030_REG_VAUX3, pdata->vaux3,
					features);
		अगर (IS_ERR(child))
			वापस PTR_ERR(child);

		child = add_regulator(TWL4030_REG_VAUX4, pdata->vaux4,
					features);
		अगर (IS_ERR(child))
			वापस PTR_ERR(child);
	पूर्ण

	अगर (IS_ENABLED(CONFIG_CHARGER_TWL4030) && pdata->bci &&
			!(features & (TPS_SUBSET | TWL5031))) अणु
		child = add_child(TWL_MODULE_MAIN_CHARGE, "twl4030_bci",
				pdata->bci, माप(*pdata->bci), false,
				/* irq0 = CHG_PRES, irq1 = BCI */
				irq_base + BCI_PRES_INTR_OFFSET,
				irq_base + BCI_INTR_OFFSET);
		अगर (IS_ERR(child))
			वापस PTR_ERR(child);
	पूर्ण

	अगर (IS_ENABLED(CONFIG_TWL4030_POWER) && pdata->घातer) अणु
		child = add_child(TWL_MODULE_PM_MASTER, "twl4030_power",
				  pdata->घातer, माप(*pdata->घातer), false,
				  0, 0);
		अगर (IS_ERR(child))
			वापस PTR_ERR(child);
	पूर्ण

	वापस 0;
पूर्ण

/*----------------------------------------------------------------------*/

/*
 * These three functions initialize the on-chip घड़ी framework,
 * letting it generate the right frequencies क्रम USB, MADC, and
 * other purposes.
 */
अटल अंतरभूत पूर्णांक protect_pm_master(व्योम)
अणु
	पूर्णांक e = 0;

	e = twl_i2c_ग_लिखो_u8(TWL_MODULE_PM_MASTER, 0,
			     TWL4030_PM_MASTER_PROTECT_KEY);
	वापस e;
पूर्ण

अटल अंतरभूत पूर्णांक unprotect_pm_master(व्योम)
अणु
	पूर्णांक e = 0;

	e |= twl_i2c_ग_लिखो_u8(TWL_MODULE_PM_MASTER, TWL4030_PM_MASTER_KEY_CFG1,
			      TWL4030_PM_MASTER_PROTECT_KEY);
	e |= twl_i2c_ग_लिखो_u8(TWL_MODULE_PM_MASTER, TWL4030_PM_MASTER_KEY_CFG2,
			      TWL4030_PM_MASTER_PROTECT_KEY);

	वापस e;
पूर्ण

अटल व्योम घड़ीs_init(काष्ठा device *dev,
			काष्ठा twl4030_घड़ी_init_data *घड़ी)
अणु
	पूर्णांक e = 0;
	काष्ठा clk *osc;
	u32 rate;
	u8 ctrl = HFCLK_FREQ_26_MHZ;

	osc = clk_get(dev, "fck");
	अगर (IS_ERR(osc)) अणु
		prपूर्णांकk(KERN_WARNING "Skipping twl internal clock init and "
				"using bootloader value (unknown osc rate)\n");
		वापस;
	पूर्ण

	rate = clk_get_rate(osc);
	clk_put(osc);

	चयन (rate) अणु
	हाल 19200000:
		ctrl = HFCLK_FREQ_19p2_MHZ;
		अवरोध;
	हाल 26000000:
		ctrl = HFCLK_FREQ_26_MHZ;
		अवरोध;
	हाल 38400000:
		ctrl = HFCLK_FREQ_38p4_MHZ;
		अवरोध;
	पूर्ण

	ctrl |= HIGH_PERF_SQ;
	अगर (घड़ी && घड़ी->ck32k_lowpwr_enable)
		ctrl |= CK32K_LOWPWR_EN;

	e |= unprotect_pm_master();
	/* effect->MADC+USB ck en */
	e |= twl_i2c_ग_लिखो_u8(TWL_MODULE_PM_MASTER, ctrl, R_CFG_BOOT);
	e |= protect_pm_master();

	अगर (e < 0)
		pr_err("%s: clock init err [%d]\n", DRIVER_NAME, e);
पूर्ण

/*----------------------------------------------------------------------*/


अटल पूर्णांक twl_हटाओ(काष्ठा i2c_client *client)
अणु
	अचिन्हित i, num_slaves;
	पूर्णांक status;

	अगर (twl_class_is_4030())
		status = twl4030_निकास_irq();
	अन्यथा
		status = twl6030_निकास_irq();

	अगर (status < 0)
		वापस status;

	num_slaves = twl_get_num_slaves();
	क्रम (i = 0; i < num_slaves; i++) अणु
		काष्ठा twl_client	*twl = &twl_priv->twl_modules[i];

		अगर (twl->client && twl->client != client)
			i2c_unरेजिस्टर_device(twl->client);
		twl->client = शून्य;
	पूर्ण
	twl_priv->पढ़ोy = false;
	वापस 0;
पूर्ण

अटल काष्ठा of_dev_auxdata twl_auxdata_lookup[] = अणु
	OF_DEV_AUXDATA("ti,twl4030-gpio", 0, "twl4030-gpio", शून्य),
	अणु /* sentinel */ पूर्ण,
पूर्ण;

/* NOTE: This driver only handles a single twl4030/tps659x0 chip */
अटल पूर्णांक
twl_probe(काष्ठा i2c_client *client, स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा twl4030_platक्रमm_data	*pdata = dev_get_platdata(&client->dev);
	काष्ठा device_node		*node = client->dev.of_node;
	काष्ठा platक्रमm_device		*pdev;
	स्थिर काष्ठा regmap_config	*twl_regmap_config;
	पूर्णांक				irq_base = 0;
	पूर्णांक				status;
	अचिन्हित			i, num_slaves;

	अगर (!node && !pdata) अणु
		dev_err(&client->dev, "no platform data\n");
		वापस -EINVAL;
	पूर्ण

	अगर (twl_priv) अणु
		dev_dbg(&client->dev, "only one instance of %s allowed\n",
			DRIVER_NAME);
		वापस -EBUSY;
	पूर्ण

	pdev = platक्रमm_device_alloc(DRIVER_NAME, -1);
	अगर (!pdev) अणु
		dev_err(&client->dev, "can't alloc pdev\n");
		वापस -ENOMEM;
	पूर्ण

	status = platक्रमm_device_add(pdev);
	अगर (status) अणु
		platक्रमm_device_put(pdev);
		वापस status;
	पूर्ण

	अगर (i2c_check_functionality(client->adapter, I2C_FUNC_I2C) == 0) अणु
		dev_dbg(&client->dev, "can't talk I2C?\n");
		status = -EIO;
		जाओ मुक्त;
	पूर्ण

	twl_priv = devm_kzalloc(&client->dev, माप(काष्ठा twl_निजी),
				GFP_KERNEL);
	अगर (!twl_priv) अणु
		status = -ENOMEM;
		जाओ मुक्त;
	पूर्ण

	अगर ((id->driver_data) & TWL6030_CLASS) अणु
		twl_priv->twl_id = TWL6030_CLASS_ID;
		twl_priv->twl_map = &twl6030_map[0];
		/* The अक्षरger base address is dअगरferent in twl6032 */
		अगर ((id->driver_data) & TWL6032_SUBCLASS)
			twl_priv->twl_map[TWL_MODULE_MAIN_CHARGE].base =
							TWL6032_BASEADD_CHARGER;
		twl_regmap_config = twl6030_regmap_config;
	पूर्ण अन्यथा अणु
		twl_priv->twl_id = TWL4030_CLASS_ID;
		twl_priv->twl_map = &twl4030_map[0];
		twl_regmap_config = twl4030_regmap_config;
	पूर्ण

	num_slaves = twl_get_num_slaves();
	twl_priv->twl_modules = devm_kसुस्मृति(&client->dev,
					 num_slaves,
					 माप(काष्ठा twl_client),
					 GFP_KERNEL);
	अगर (!twl_priv->twl_modules) अणु
		status = -ENOMEM;
		जाओ मुक्त;
	पूर्ण

	क्रम (i = 0; i < num_slaves; i++) अणु
		काष्ठा twl_client *twl = &twl_priv->twl_modules[i];

		अगर (i == 0) अणु
			twl->client = client;
		पूर्ण अन्यथा अणु
			twl->client = i2c_new_dummy_device(client->adapter,
						    client->addr + i);
			अगर (IS_ERR(twl->client)) अणु
				dev_err(&client->dev,
					"can't attach client %d\n", i);
				status = PTR_ERR(twl->client);
				जाओ fail;
			पूर्ण
		पूर्ण

		twl->regmap = devm_regmap_init_i2c(twl->client,
						   &twl_regmap_config[i]);
		अगर (IS_ERR(twl->regmap)) अणु
			status = PTR_ERR(twl->regmap);
			dev_err(&client->dev,
				"Failed to allocate regmap %d, err: %d\n", i,
				status);
			जाओ fail;
		पूर्ण
	पूर्ण

	twl_priv->पढ़ोy = true;

	/* setup घड़ी framework */
	घड़ीs_init(&client->dev, pdata ? pdata->घड़ी : शून्य);

	/* पढ़ो TWL IDCODE Register */
	अगर (twl_class_is_4030()) अणु
		status = twl_पढ़ो_idcode_रेजिस्टर();
		WARN(status < 0, "Error: reading twl_idcode register value\n");
	पूर्ण

	/* Maybe init the T2 Interrupt subप्रणाली */
	अगर (client->irq) अणु
		अगर (twl_class_is_4030()) अणु
			twl4030_init_chip_irq(id->name);
			irq_base = twl4030_init_irq(&client->dev, client->irq);
		पूर्ण अन्यथा अणु
			irq_base = twl6030_init_irq(&client->dev, client->irq);
		पूर्ण

		अगर (irq_base < 0) अणु
			status = irq_base;
			जाओ fail;
		पूर्ण
	पूर्ण

	/*
	 * Disable TWL4030/TWL5030 I2C Pull-up on I2C1 and I2C4(SR) पूर्णांकerface.
	 * Program I2C_SCL_CTRL_PU(bit 0)=0, I2C_SDA_CTRL_PU (bit 2)=0,
	 * SR_I2C_SCL_CTRL_PU(bit 4)=0 and SR_I2C_SDA_CTRL_PU(bit 6)=0.
	 *
	 * Also, always enable SmartReflex bit as that's needed क्रम omaps to
	 * to करो anything over I2C4 क्रम voltage scaling even अगर SmartReflex
	 * is disabled. Without the SmartReflex bit omap sys_clkreq idle
	 * संकेत will never trigger क्रम retention idle.
	 */
	अगर (twl_class_is_4030()) अणु
		u8 temp;

		twl_i2c_पढ़ो_u8(TWL4030_MODULE_INTBR, &temp, REG_GPPUPDCTR1);
		temp &= ~(SR_I2C_SDA_CTRL_PU | SR_I2C_SCL_CTRL_PU | \
			I2C_SDA_CTRL_PU | I2C_SCL_CTRL_PU);
		twl_i2c_ग_लिखो_u8(TWL4030_MODULE_INTBR, temp, REG_GPPUPDCTR1);

		twl_i2c_पढ़ो_u8(TWL_MODULE_PM_RECEIVER, &temp,
				TWL4030_DCDC_GLOBAL_CFG);
		temp |= SMARTREFLEX_ENABLE;
		twl_i2c_ग_लिखो_u8(TWL_MODULE_PM_RECEIVER, temp,
				 TWL4030_DCDC_GLOBAL_CFG);
	पूर्ण

	अगर (node) अणु
		अगर (pdata)
			twl_auxdata_lookup[0].platक्रमm_data = pdata->gpio;
		status = of_platक्रमm_populate(node, शून्य, twl_auxdata_lookup,
					      &client->dev);
	पूर्ण अन्यथा अणु
		status = add_children(pdata, irq_base, id->driver_data);
	पूर्ण

fail:
	अगर (status < 0)
		twl_हटाओ(client);
मुक्त:
	अगर (status < 0)
		platक्रमm_device_unरेजिस्टर(pdev);

	वापस status;
पूर्ण

अटल पूर्णांक __maybe_unused twl_suspend(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);

	अगर (client->irq)
		disable_irq(client->irq);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused twl_resume(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);

	अगर (client->irq)
		enable_irq(client->irq);

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(twl_dev_pm_ops, twl_suspend, twl_resume);

अटल स्थिर काष्ठा i2c_device_id twl_ids[] = अणु
	अणु "twl4030", TWL4030_VAUX2 पूर्ण,	/* "Triton 2" */
	अणु "twl5030", 0 पूर्ण,		/* T2 updated */
	अणु "twl5031", TWL5031 पूर्ण,		/* TWL5030 updated */
	अणु "tps65950", 0 पूर्ण,		/* catalog version of twl5030 */
	अणु "tps65930", TPS_SUBSET पूर्ण,	/* fewer LDOs and DACs; no अक्षरger */
	अणु "tps65920", TPS_SUBSET पूर्ण,	/* fewer LDOs; no codec or अक्षरger */
	अणु "tps65921", TPS_SUBSET पूर्ण,	/* fewer LDOs; no codec, no LED
					   and vibrator. Charger in USB module*/
	अणु "twl6030", TWL6030_CLASS पूर्ण,	/* "Phoenix power chip" */
	अणु "twl6032", TWL6030_CLASS | TWL6032_SUBCLASS पूर्ण, /* "Phoenix lite" */
	अणु /* end of list */ पूर्ण,
पूर्ण;

/* One Client Driver , 4 Clients */
अटल काष्ठा i2c_driver twl_driver = अणु
	.driver.name	= DRIVER_NAME,
	.driver.pm	= &twl_dev_pm_ops,
	.id_table	= twl_ids,
	.probe		= twl_probe,
	.हटाओ		= twl_हटाओ,
पूर्ण;
builtin_i2c_driver(twl_driver);
