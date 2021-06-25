<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * twl4030.h - header क्रम TWL4030 PM and audio CODEC device
 *
 * Copyright (C) 2005-2006 Texas Instruments, Inc.
 *
 * Based on tlv320aic23.c:
 * Copyright (c) by Kai Svahn <kai.svahn@nokia.com>
 */

#अगर_अघोषित __TWL_H_
#घोषणा __TWL_H_

#समावेश <linux/types.h>
#समावेश <linux/input/matrix_keypad.h>

/*
 * Using the twl4030 core we address रेजिस्टरs using a pair
 *	अणु module id, relative रेजिस्टर offset पूर्ण
 * which that core then maps to the relevant
 *	अणु i2c slave, असलolute रेजिस्टर address पूर्ण
 *
 * The module IDs are meaningful only to the twl4030 core code,
 * which uses them as array indices to look up the first रेजिस्टर
 * address each module uses within a given i2c slave.
 */

/* Module IDs क्रम similar functionalities found in twl4030/twl6030 */
क्रमागत twl_module_ids अणु
	TWL_MODULE_USB,
	TWL_MODULE_PIH,
	TWL_MODULE_MAIN_CHARGE,
	TWL_MODULE_PM_MASTER,
	TWL_MODULE_PM_RECEIVER,

	TWL_MODULE_RTC,
	TWL_MODULE_PWM,
	TWL_MODULE_LED,
	TWL_MODULE_SECURED_REG,

	TWL_MODULE_LAST,
पूर्ण;

/* Modules only available in twl4030 series */
क्रमागत twl4030_module_ids अणु
	TWL4030_MODULE_AUDIO_VOICE = TWL_MODULE_LAST,
	TWL4030_MODULE_GPIO,
	TWL4030_MODULE_INTBR,
	TWL4030_MODULE_TEST,
	TWL4030_MODULE_KEYPAD,

	TWL4030_MODULE_MADC,
	TWL4030_MODULE_INTERRUPTS,
	TWL4030_MODULE_PRECHARGE,
	TWL4030_MODULE_BACKUP,
	TWL4030_MODULE_INT,

	TWL5031_MODULE_ACCESSORY,
	TWL5031_MODULE_INTERRUPTS,

	TWL4030_MODULE_LAST,
पूर्ण;

/* Modules only available in twl6030 series */
क्रमागत twl6030_module_ids अणु
	TWL6030_MODULE_ID0 = TWL_MODULE_LAST,
	TWL6030_MODULE_ID1,
	TWL6030_MODULE_ID2,
	TWL6030_MODULE_GPADC,
	TWL6030_MODULE_GASGAUGE,

	TWL6030_MODULE_LAST,
पूर्ण;

/* Until the clients has been converted to use TWL_MODULE_LED */
#घोषणा TWL4030_MODULE_LED	TWL_MODULE_LED

#घोषणा GPIO_INTR_OFFSET	0
#घोषणा KEYPAD_INTR_OFFSET	1
#घोषणा BCI_INTR_OFFSET		2
#घोषणा MADC_INTR_OFFSET	3
#घोषणा USB_INTR_OFFSET		4
#घोषणा CHARGERFAULT_INTR_OFFSET 5
#घोषणा BCI_PRES_INTR_OFFSET	9
#घोषणा USB_PRES_INTR_OFFSET	10
#घोषणा RTC_INTR_OFFSET		11

/*
 * Offset from TWL6030_IRQ_BASE / pdata->irq_base
 */
#घोषणा PWR_INTR_OFFSET		0
#घोषणा HOTDIE_INTR_OFFSET	12
#घोषणा SMPSLDO_INTR_OFFSET	13
#घोषणा BATDETECT_INTR_OFFSET	14
#घोषणा SIMDETECT_INTR_OFFSET	15
#घोषणा MMCDETECT_INTR_OFFSET	16
#घोषणा GASGAUGE_INTR_OFFSET	17
#घोषणा USBOTG_INTR_OFFSET	4
#घोषणा CHARGER_INTR_OFFSET	2
#घोषणा RSV_INTR_OFFSET		0

/* INT रेजिस्टर offsets */
#घोषणा REG_INT_STS_A			0x00
#घोषणा REG_INT_STS_B			0x01
#घोषणा REG_INT_STS_C			0x02

#घोषणा REG_INT_MSK_LINE_A		0x03
#घोषणा REG_INT_MSK_LINE_B		0x04
#घोषणा REG_INT_MSK_LINE_C		0x05

#घोषणा REG_INT_MSK_STS_A		0x06
#घोषणा REG_INT_MSK_STS_B		0x07
#घोषणा REG_INT_MSK_STS_C		0x08

/* MASK INT REG GROUP A */
#घोषणा TWL6030_PWR_INT_MASK 		0x07
#घोषणा TWL6030_RTC_INT_MASK 		0x18
#घोषणा TWL6030_HOTDIE_INT_MASK 	0x20
#घोषणा TWL6030_SMPSLDOA_INT_MASK	0xC0

/* MASK INT REG GROUP B */
#घोषणा TWL6030_SMPSLDOB_INT_MASK 	0x01
#घोषणा TWL6030_BATDETECT_INT_MASK 	0x02
#घोषणा TWL6030_SIMDETECT_INT_MASK 	0x04
#घोषणा TWL6030_MMCDETECT_INT_MASK 	0x08
#घोषणा TWL6030_GPADC_INT_MASK 		0x60
#घोषणा TWL6030_GASGAUGE_INT_MASK 	0x80

/* MASK INT REG GROUP C */
#घोषणा TWL6030_USBOTG_INT_MASK  	0x0F
#घोषणा TWL6030_CHARGER_CTRL_INT_MASK 	0x10
#घोषणा TWL6030_CHARGER_FAULT_INT_MASK 	0x60

#घोषणा TWL6030_MMCCTRL		0xEE
#घोषणा VMMC_AUTO_OFF			(0x1 << 3)
#घोषणा SW_FC				(0x1 << 2)
#घोषणा STS_MMC			0x1

#घोषणा TWL6030_CFG_INPUT_PUPD3	0xF2
#घोषणा MMC_PU				(0x1 << 3)
#घोषणा MMC_PD				(0x1 << 2)

#घोषणा TWL_SIL_TYPE(rev)		((rev) & 0x00FFFFFF)
#घोषणा TWL_SIL_REV(rev)		((rev) >> 24)
#घोषणा TWL_SIL_5030			0x09002F
#घोषणा TWL5030_REV_1_0			0x00
#घोषणा TWL5030_REV_1_1			0x10
#घोषणा TWL5030_REV_1_2			0x30

#घोषणा TWL4030_CLASS_ID 		0x4030
#घोषणा TWL6030_CLASS_ID 		0x6030
अचिन्हित पूर्णांक twl_rev(व्योम);
#घोषणा GET_TWL_REV (twl_rev())
#घोषणा TWL_CLASS_IS(class, id)			\
अटल अंतरभूत पूर्णांक twl_class_is_ ##class(व्योम)	\
अणु						\
	वापस ((id) == (GET_TWL_REV)) ? 1 : 0;	\
पूर्ण

TWL_CLASS_IS(4030, TWL4030_CLASS_ID)
TWL_CLASS_IS(6030, TWL6030_CLASS_ID)

/* Set the regcache bypass क्रम the regmap associated with the nodule */
पूर्णांक twl_set_regcache_bypass(u8 mod_no, bool enable);

/*
 * Read and ग_लिखो several 8-bit रेजिस्टरs at once.
 */
पूर्णांक twl_i2c_ग_लिखो(u8 mod_no, u8 *value, u8 reg, अचिन्हित num_bytes);
पूर्णांक twl_i2c_पढ़ो(u8 mod_no, u8 *value, u8 reg, अचिन्हित num_bytes);

/*
 * Read and ग_लिखो single 8-bit रेजिस्टरs
 */
अटल अंतरभूत पूर्णांक twl_i2c_ग_लिखो_u8(u8 mod_no, u8 val, u8 reg) अणु
	वापस twl_i2c_ग_लिखो(mod_no, &val, reg, 1);
पूर्ण

अटल अंतरभूत पूर्णांक twl_i2c_पढ़ो_u8(u8 mod_no, u8 *val, u8 reg) अणु
	वापस twl_i2c_पढ़ो(mod_no, val, reg, 1);
पूर्ण

अटल अंतरभूत पूर्णांक twl_i2c_ग_लिखो_u16(u8 mod_no, u16 val, u8 reg) अणु
	__le16 value;

	value = cpu_to_le16(val);
	वापस twl_i2c_ग_लिखो(mod_no, (u8 *) &value, reg, 2);
पूर्ण

अटल अंतरभूत पूर्णांक twl_i2c_पढ़ो_u16(u8 mod_no, u16 *val, u8 reg) अणु
	पूर्णांक ret;
	__le16 value;

	ret = twl_i2c_पढ़ो(mod_no, (u8 *) &value, reg, 2);
	*val = le16_to_cpu(value);
	वापस ret;
पूर्ण

पूर्णांक twl_get_type(व्योम);
पूर्णांक twl_get_version(व्योम);
पूर्णांक twl_get_hfclk_rate(व्योम);

पूर्णांक twl6030_पूर्णांकerrupt_unmask(u8 bit_mask, u8 offset);
पूर्णांक twl6030_पूर्णांकerrupt_mask(u8 bit_mask, u8 offset);

/* Card detect Configuration क्रम MMC1 Controller on OMAP4 */
#अगर_घोषित CONFIG_TWL4030_CORE
पूर्णांक twl6030_mmc_card_detect_config(व्योम);
#अन्यथा
अटल अंतरभूत पूर्णांक twl6030_mmc_card_detect_config(व्योम)
अणु
	pr_debug("twl6030_mmc_card_detect_config not supported\n");
	वापस 0;
पूर्ण
#पूर्ण_अगर

/* MMC1 Controller on OMAP4 uses Phoenix irq क्रम Card detect */
#अगर_घोषित CONFIG_TWL4030_CORE
पूर्णांक twl6030_mmc_card_detect(काष्ठा device *dev, पूर्णांक slot);
#अन्यथा
अटल अंतरभूत पूर्णांक twl6030_mmc_card_detect(काष्ठा device *dev, पूर्णांक slot)
अणु
	pr_debug("Call back twl6030_mmc_card_detect not supported\n");
	वापस -EIO;
पूर्ण
#पूर्ण_अगर
/*----------------------------------------------------------------------*/

/*
 * NOTE:  at up to 1024 रेजिस्टरs, this is a big chip.
 *
 * Aव्योम putting रेजिस्टर declarations in this file, instead of पूर्णांकo
 * a driver-निजी file, unless some of the रेजिस्टरs in a block
 * need to be shared with other drivers.  One example is blocks that
 * have Secondary IRQ Handler (SIH) रेजिस्टरs.
 */

#घोषणा TWL4030_SIH_CTRL_EXCLEN_MASK	BIT(0)
#घोषणा TWL4030_SIH_CTRL_PENDDIS_MASK	BIT(1)
#घोषणा TWL4030_SIH_CTRL_COR_MASK	BIT(2)

/*----------------------------------------------------------------------*/

/*
 * GPIO Block Register offsets (use TWL4030_MODULE_GPIO)
 */

#घोषणा REG_GPIODATAIN1			0x0
#घोषणा REG_GPIODATAIN2			0x1
#घोषणा REG_GPIODATAIN3			0x2
#घोषणा REG_GPIODATAसूची1		0x3
#घोषणा REG_GPIODATAसूची2		0x4
#घोषणा REG_GPIODATAसूची3		0x5
#घोषणा REG_GPIODATAOUT1		0x6
#घोषणा REG_GPIODATAOUT2		0x7
#घोषणा REG_GPIODATAOUT3		0x8
#घोषणा REG_CLEARGPIODATAOUT1		0x9
#घोषणा REG_CLEARGPIODATAOUT2		0xA
#घोषणा REG_CLEARGPIODATAOUT3		0xB
#घोषणा REG_SETGPIODATAOUT1		0xC
#घोषणा REG_SETGPIODATAOUT2		0xD
#घोषणा REG_SETGPIODATAOUT3		0xE
#घोषणा REG_GPIO_DEBEN1			0xF
#घोषणा REG_GPIO_DEBEN2			0x10
#घोषणा REG_GPIO_DEBEN3			0x11
#घोषणा REG_GPIO_CTRL			0x12
#घोषणा REG_GPIOPUPDCTR1		0x13
#घोषणा REG_GPIOPUPDCTR2		0x14
#घोषणा REG_GPIOPUPDCTR3		0x15
#घोषणा REG_GPIOPUPDCTR4		0x16
#घोषणा REG_GPIOPUPDCTR5		0x17
#घोषणा REG_GPIO_ISR1A			0x19
#घोषणा REG_GPIO_ISR2A			0x1A
#घोषणा REG_GPIO_ISR3A			0x1B
#घोषणा REG_GPIO_IMR1A			0x1C
#घोषणा REG_GPIO_IMR2A			0x1D
#घोषणा REG_GPIO_IMR3A			0x1E
#घोषणा REG_GPIO_ISR1B			0x1F
#घोषणा REG_GPIO_ISR2B			0x20
#घोषणा REG_GPIO_ISR3B			0x21
#घोषणा REG_GPIO_IMR1B			0x22
#घोषणा REG_GPIO_IMR2B			0x23
#घोषणा REG_GPIO_IMR3B			0x24
#घोषणा REG_GPIO_EDR1			0x28
#घोषणा REG_GPIO_EDR2			0x29
#घोषणा REG_GPIO_EDR3			0x2A
#घोषणा REG_GPIO_EDR4			0x2B
#घोषणा REG_GPIO_EDR5			0x2C
#घोषणा REG_GPIO_SIH_CTRL		0x2D

/* Up to 18 संकेतs are available as GPIOs, when their
 * pins are not asचिन्हित to another use (such as ULPI/USB).
 */
#घोषणा TWL4030_GPIO_MAX		18

/*----------------------------------------------------------------------*/

/*Interface Bit Register (INTBR) offsets
 *(Use TWL_4030_MODULE_INTBR)
 */

#घोषणा REG_IDCODE_7_0			0x00
#घोषणा REG_IDCODE_15_8			0x01
#घोषणा REG_IDCODE_16_23		0x02
#घोषणा REG_IDCODE_31_24		0x03
#घोषणा REG_GPPUPDCTR1			0x0F
#घोषणा REG_UNLOCK_TEST_REG		0x12

/*I2C1 and I2C4(SR) SDA/SCL pull-up control bits */

#घोषणा I2C_SCL_CTRL_PU			BIT(0)
#घोषणा I2C_SDA_CTRL_PU			BIT(2)
#घोषणा SR_I2C_SCL_CTRL_PU		BIT(4)
#घोषणा SR_I2C_SDA_CTRL_PU		BIT(6)

#घोषणा TWL_EEPROM_R_UNLOCK		0x49

/*----------------------------------------------------------------------*/

/*
 * Keypad रेजिस्टर offsets (use TWL4030_MODULE_KEYPAD)
 * ... SIH/पूर्णांकerrupt only
 */

#घोषणा TWL4030_KEYPAD_KEYP_ISR1	0x11
#घोषणा TWL4030_KEYPAD_KEYP_IMR1	0x12
#घोषणा TWL4030_KEYPAD_KEYP_ISR2	0x13
#घोषणा TWL4030_KEYPAD_KEYP_IMR2	0x14
#घोषणा TWL4030_KEYPAD_KEYP_SIR		0x15	/* test रेजिस्टर */
#घोषणा TWL4030_KEYPAD_KEYP_EDR		0x16
#घोषणा TWL4030_KEYPAD_KEYP_SIH_CTRL	0x17

/*----------------------------------------------------------------------*/

/*
 * Multichannel ADC रेजिस्टर offsets (use TWL4030_MODULE_MADC)
 * ... SIH/पूर्णांकerrupt only
 */

#घोषणा TWL4030_MADC_ISR1		0x61
#घोषणा TWL4030_MADC_IMR1		0x62
#घोषणा TWL4030_MADC_ISR2		0x63
#घोषणा TWL4030_MADC_IMR2		0x64
#घोषणा TWL4030_MADC_SIR		0x65	/* test रेजिस्टर */
#घोषणा TWL4030_MADC_EDR		0x66
#घोषणा TWL4030_MADC_SIH_CTRL		0x67

/*----------------------------------------------------------------------*/

/*
 * Battery अक्षरger रेजिस्टर offsets (use TWL4030_MODULE_INTERRUPTS)
 */

#घोषणा TWL4030_INTERRUPTS_BCIISR1A	0x0
#घोषणा TWL4030_INTERRUPTS_BCIISR2A	0x1
#घोषणा TWL4030_INTERRUPTS_BCIIMR1A	0x2
#घोषणा TWL4030_INTERRUPTS_BCIIMR2A	0x3
#घोषणा TWL4030_INTERRUPTS_BCIISR1B	0x4
#घोषणा TWL4030_INTERRUPTS_BCIISR2B	0x5
#घोषणा TWL4030_INTERRUPTS_BCIIMR1B	0x6
#घोषणा TWL4030_INTERRUPTS_BCIIMR2B	0x7
#घोषणा TWL4030_INTERRUPTS_BCISIR1	0x8	/* test रेजिस्टर */
#घोषणा TWL4030_INTERRUPTS_BCISIR2	0x9	/* test रेजिस्टर */
#घोषणा TWL4030_INTERRUPTS_BCIEDR1	0xa
#घोषणा TWL4030_INTERRUPTS_BCIEDR2	0xb
#घोषणा TWL4030_INTERRUPTS_BCIEDR3	0xc
#घोषणा TWL4030_INTERRUPTS_BCISIHCTRL	0xd

/*----------------------------------------------------------------------*/

/*
 * Power Interrupt block रेजिस्टर offsets (use TWL4030_MODULE_INT)
 */

#घोषणा TWL4030_INT_PWR_ISR1		0x0
#घोषणा TWL4030_INT_PWR_IMR1		0x1
#घोषणा TWL4030_INT_PWR_ISR2		0x2
#घोषणा TWL4030_INT_PWR_IMR2		0x3
#घोषणा TWL4030_INT_PWR_SIR		0x4	/* test रेजिस्टर */
#घोषणा TWL4030_INT_PWR_EDR1		0x5
#घोषणा TWL4030_INT_PWR_EDR2		0x6
#घोषणा TWL4030_INT_PWR_SIH_CTRL	0x7

/*----------------------------------------------------------------------*/

/*
 * Accessory Interrupts
 */
#घोषणा TWL5031_ACIIMR_LSB		0x05
#घोषणा TWL5031_ACIIMR_MSB		0x06
#घोषणा TWL5031_ACIIDR_LSB		0x07
#घोषणा TWL5031_ACIIDR_MSB		0x08
#घोषणा TWL5031_ACCISR1			0x0F
#घोषणा TWL5031_ACCIMR1			0x10
#घोषणा TWL5031_ACCISR2			0x11
#घोषणा TWL5031_ACCIMR2			0x12
#घोषणा TWL5031_ACCSIR			0x13
#घोषणा TWL5031_ACCEDR1			0x14
#घोषणा TWL5031_ACCSIHCTRL		0x15

/*----------------------------------------------------------------------*/

/*
 * Battery Charger Controller
 */

#घोषणा TWL5031_INTERRUPTS_BCIISR1	0x0
#घोषणा TWL5031_INTERRUPTS_BCIIMR1	0x1
#घोषणा TWL5031_INTERRUPTS_BCIISR2	0x2
#घोषणा TWL5031_INTERRUPTS_BCIIMR2	0x3
#घोषणा TWL5031_INTERRUPTS_BCISIR	0x4
#घोषणा TWL5031_INTERRUPTS_BCIEDR1	0x5
#घोषणा TWL5031_INTERRUPTS_BCIEDR2	0x6
#घोषणा TWL5031_INTERRUPTS_BCISIHCTRL	0x7

/*----------------------------------------------------------------------*/

/*
 * PM Master module रेजिस्टर offsets (use TWL4030_MODULE_PM_MASTER)
 */

#घोषणा TWL4030_PM_MASTER_CFG_P1_TRANSITION	0x00
#घोषणा TWL4030_PM_MASTER_CFG_P2_TRANSITION	0x01
#घोषणा TWL4030_PM_MASTER_CFG_P3_TRANSITION	0x02
#घोषणा TWL4030_PM_MASTER_CFG_P123_TRANSITION	0x03
#घोषणा TWL4030_PM_MASTER_STS_BOOT		0x04
#घोषणा TWL4030_PM_MASTER_CFG_BOOT		0x05
#घोषणा TWL4030_PM_MASTER_SHUNDAN		0x06
#घोषणा TWL4030_PM_MASTER_BOOT_BCI		0x07
#घोषणा TWL4030_PM_MASTER_CFG_PWRANA1		0x08
#घोषणा TWL4030_PM_MASTER_CFG_PWRANA2		0x09
#घोषणा TWL4030_PM_MASTER_BACKUP_MISC_STS	0x0b
#घोषणा TWL4030_PM_MASTER_BACKUP_MISC_CFG	0x0c
#घोषणा TWL4030_PM_MASTER_BACKUP_MISC_TST	0x0d
#घोषणा TWL4030_PM_MASTER_PROTECT_KEY		0x0e
#घोषणा TWL4030_PM_MASTER_STS_HW_CONDITIONS	0x0f
#घोषणा TWL4030_PM_MASTER_P1_SW_EVENTS		0x10
#घोषणा TWL4030_PM_MASTER_P2_SW_EVENTS		0x11
#घोषणा TWL4030_PM_MASTER_P3_SW_EVENTS		0x12
#घोषणा TWL4030_PM_MASTER_STS_P123_STATE	0x13
#घोषणा TWL4030_PM_MASTER_PB_CFG		0x14
#घोषणा TWL4030_PM_MASTER_PB_WORD_MSB		0x15
#घोषणा TWL4030_PM_MASTER_PB_WORD_LSB		0x16
#घोषणा TWL4030_PM_MASTER_SEQ_ADD_W2P		0x1c
#घोषणा TWL4030_PM_MASTER_SEQ_ADD_P2A		0x1d
#घोषणा TWL4030_PM_MASTER_SEQ_ADD_A2W		0x1e
#घोषणा TWL4030_PM_MASTER_SEQ_ADD_A2S		0x1f
#घोषणा TWL4030_PM_MASTER_SEQ_ADD_S2A12		0x20
#घोषणा TWL4030_PM_MASTER_SEQ_ADD_S2A3		0x21
#घोषणा TWL4030_PM_MASTER_SEQ_ADD_WARM		0x22
#घोषणा TWL4030_PM_MASTER_MEMORY_ADDRESS	0x23
#घोषणा TWL4030_PM_MASTER_MEMORY_DATA		0x24

#घोषणा TWL4030_PM_MASTER_KEY_CFG1		0xc0
#घोषणा TWL4030_PM_MASTER_KEY_CFG2		0x0c

#घोषणा TWL4030_PM_MASTER_KEY_TST1		0xe0
#घोषणा TWL4030_PM_MASTER_KEY_TST2		0x0e

#घोषणा TWL4030_PM_MASTER_GLOBAL_TST		0xb6

/*----------------------------------------------------------------------*/

/* Power bus message definitions */

/* The TWL4030/5030 splits its घातer-management resources (the various
 * regulators, घड़ी and reset lines) पूर्णांकo 3 processor groups - P1, P2 and
 * P3. These groups can then be configured to transition between sleep, रुको-on
 * and active states by sending messages to the घातer bus.  See Section 5.4.2
 * Power Resources of TWL4030 TRM
 */

/* Processor groups */
#घोषणा DEV_GRP_शून्य		0x0
#घोषणा DEV_GRP_P1		0x1	/* P1: all OMAP devices */
#घोषणा DEV_GRP_P2		0x2	/* P2: all Modem devices */
#घोषणा DEV_GRP_P3		0x4	/* P3: all peripheral devices */

/* Resource groups */
#घोषणा RES_GRP_RES		0x0	/* Reserved */
#घोषणा RES_GRP_PP		0x1	/* Power providers */
#घोषणा RES_GRP_RC		0x2	/* Reset and control */
#घोषणा RES_GRP_PP_RC		0x3
#घोषणा RES_GRP_PR		0x4	/* Power references */
#घोषणा RES_GRP_PP_PR		0x5
#घोषणा RES_GRP_RC_PR		0x6
#घोषणा RES_GRP_ALL		0x7	/* All resource groups */

#घोषणा RES_TYPE2_R0		0x0
#घोषणा RES_TYPE2_R1		0x1
#घोषणा RES_TYPE2_R2		0x2

#घोषणा RES_TYPE_R0		0x0
#घोषणा RES_TYPE_ALL		0x7

/* Resource states */
#घोषणा RES_STATE_WRST		0xF
#घोषणा RES_STATE_ACTIVE	0xE
#घोषणा RES_STATE_SLEEP		0x8
#घोषणा RES_STATE_OFF		0x0

/* Power resources */

/* Power providers */
#घोषणा RES_VAUX1               1
#घोषणा RES_VAUX2               2
#घोषणा RES_VAUX3               3
#घोषणा RES_VAUX4               4
#घोषणा RES_VMMC1               5
#घोषणा RES_VMMC2               6
#घोषणा RES_VPLL1               7
#घोषणा RES_VPLL2               8
#घोषणा RES_VSIM                9
#घोषणा RES_VDAC                10
#घोषणा RES_VINTANA1            11
#घोषणा RES_VINTANA2            12
#घोषणा RES_VINTDIG             13
#घोषणा RES_VIO                 14
#घोषणा RES_VDD1                15
#घोषणा RES_VDD2                16
#घोषणा RES_VUSB_1V5            17
#घोषणा RES_VUSB_1V8            18
#घोषणा RES_VUSB_3V1            19
#घोषणा RES_VUSBCP              20
#घोषणा RES_REGEN               21
/* Reset and control */
#घोषणा RES_NRES_PWRON          22
#घोषणा RES_CLKEN               23
#घोषणा RES_SYSEN               24
#घोषणा RES_HFCLKOUT            25
#घोषणा RES_32KCLKOUT           26
#घोषणा RES_RESET               27
/* Power Reference */
#घोषणा RES_MAIN_REF            28

#घोषणा TOTAL_RESOURCES		28
/*
 * Power Bus Message Format ... these can be sent inभागidually by Linux,
 * but are usually part of करोwnloaded scripts that are run when various
 * घातer events are triggered.
 *
 *  Broadcast Message (16 Bits):
 *    DEV_GRP[15:13] MT[12]  RES_GRP[11:9]  RES_TYPE2[8:7] RES_TYPE[6:4]
 *    RES_STATE[3:0]
 *
 *  Singular Message (16 Bits):
 *    DEV_GRP[15:13] MT[12]  RES_ID[11:4]  RES_STATE[3:0]
 */

#घोषणा MSG_BROADCAST(devgrp, grp, type, type2, state) \
	( (devgrp) << 13 | 1 << 12 | (grp) << 9 | (type2) << 7 \
	| (type) << 4 | (state))

#घोषणा MSG_SINGULAR(devgrp, id, state) \
	((devgrp) << 13 | 0 << 12 | (id) << 4 | (state))

#घोषणा MSG_BROADCAST_ALL(devgrp, state) \
	((devgrp) << 5 | (state))

#घोषणा MSG_BROADCAST_REF MSG_BROADCAST_ALL
#घोषणा MSG_BROADCAST_PROV MSG_BROADCAST_ALL
#घोषणा MSG_BROADCAST__CLK_RST MSG_BROADCAST_ALL
/*----------------------------------------------------------------------*/

काष्ठा twl4030_घड़ी_init_data अणु
	bool ck32k_lowpwr_enable;
पूर्ण;

काष्ठा twl4030_bci_platक्रमm_data अणु
	पूर्णांक *battery_पंचांगp_tbl;
	अचिन्हित पूर्णांक tblsize;
	पूर्णांक	bb_uvolt;	/* voltage to अक्षरge backup battery */
	पूर्णांक	bb_uamp;	/* current क्रम backup battery अक्षरging */
पूर्ण;

/* TWL4030_GPIO_MAX (18) GPIOs, with पूर्णांकerrupts */
काष्ठा twl4030_gpio_platक्रमm_data अणु
	/* package the two LED संकेतs as output-only GPIOs? */
	bool		use_leds;

	/* gpio-n should control VMMC(n+1) अगर BIT(n) in mmc_cd is set */
	u8		mmc_cd;

	/* अगर BIT(N) is set, or VMMC(n+1) is linked, debounce GPIO-N */
	u32		debounce;

	/* For gpio-N, bit (1 << N) in "pullups" is set अगर that pullup
	 * should be enabled.  Else, अगर that bit is set in "pulldowns",
	 * that pullकरोwn is enabled.  Don't waste घातer by letting any
	 * digital inमाला_दो भग्न...
	 */
	u32		pullups;
	u32		pullकरोwns;

	पूर्णांक		(*setup)(काष्ठा device *dev,
				अचिन्हित gpio, अचिन्हित ngpio);
	पूर्णांक		(*tearकरोwn)(काष्ठा device *dev,
				अचिन्हित gpio, अचिन्हित ngpio);
पूर्ण;

काष्ठा twl4030_madc_platक्रमm_data अणु
	पूर्णांक		irq_line;
पूर्ण;

/* Boards have unique mappings of अणुrow, colपूर्ण --> keycode.
 * Column and row are 8 bits each, but range only from 0..7.
 * a PERSISTENT_KEY is "always on" and never reported.
 */
#घोषणा PERSISTENT_KEY(r, c)	KEY((r), (c), KEY_RESERVED)

काष्ठा twl4030_keypad_data अणु
	स्थिर काष्ठा matrix_keymap_data *keymap_data;
	अचिन्हित rows;
	अचिन्हित cols;
	bool rep;
पूर्ण;

क्रमागत twl4030_usb_mode अणु
	T2_USB_MODE_ULPI = 1,
	T2_USB_MODE_CEA2011_3PIN = 2,
पूर्ण;

काष्ठा twl4030_usb_data अणु
	क्रमागत twl4030_usb_mode	usb_mode;
	अचिन्हित दीर्घ		features;

	पूर्णांक		(*phy_init)(काष्ठा device *dev);
	पूर्णांक		(*phy_निकास)(काष्ठा device *dev);
	/* Power on/off the PHY */
	पूर्णांक		(*phy_घातer)(काष्ठा device *dev, पूर्णांक iD, पूर्णांक on);
	/* enable/disable  phy घड़ीs */
	पूर्णांक		(*phy_set_घड़ी)(काष्ठा device *dev, पूर्णांक on);
	/* suspend/resume of phy */
	पूर्णांक		(*phy_suspend)(काष्ठा device *dev, पूर्णांक suspend);
पूर्ण;

काष्ठा twl4030_ins अणु
	u16 pmb_message;
	u8 delay;
पूर्ण;

काष्ठा twl4030_script अणु
	काष्ठा twl4030_ins *script;
	अचिन्हित size;
	u8 flags;
#घोषणा TWL4030_WRST_SCRIPT	(1<<0)
#घोषणा TWL4030_WAKEUP12_SCRIPT	(1<<1)
#घोषणा TWL4030_WAKEUP3_SCRIPT	(1<<2)
#घोषणा TWL4030_SLEEP_SCRIPT	(1<<3)
पूर्ण;

काष्ठा twl4030_resconfig अणु
	u8 resource;
	u8 devgroup;	/* Processor group that Power resource beदीर्घs to */
	u8 type;	/* Power resource addressed, 6 / broadcast message */
	u8 type2;	/* Power resource addressed, 3 / broadcast message */
	u8 remap_off;	/* off state remapping */
	u8 remap_sleep;	/* sleep state remapping */
पूर्ण;

काष्ठा twl4030_घातer_data अणु
	काष्ठा twl4030_script **scripts;
	अचिन्हित num;
	काष्ठा twl4030_resconfig *resource_config;
	काष्ठा twl4030_resconfig *board_config;
#घोषणा TWL4030_RESCONFIG_UNDEF	((u8)-1)
	bool use_घातeroff;	/* Board is wired क्रम TWL घातeroff */
	bool ac_अक्षरger_quirk;	/* Disable AC अक्षरger on board */
पूर्ण;

बाह्य पूर्णांक twl4030_हटाओ_script(u8 flags);
बाह्य व्योम twl4030_घातer_off(व्योम);

काष्ठा twl4030_codec_data अणु
	अचिन्हित पूर्णांक digimic_delay; /* in ms */
	अचिन्हित पूर्णांक ramp_delay_value;
	अचिन्हित पूर्णांक offset_cncl_path;
	अचिन्हित पूर्णांक hs_exपंचांगute:1;
	पूर्णांक hs_exपंचांगute_gpio;
पूर्ण;

काष्ठा twl4030_vibra_data अणु
	अचिन्हित पूर्णांक	coexist;
पूर्ण;

काष्ठा twl4030_audio_data अणु
	अचिन्हित पूर्णांक	audio_mclk;
	काष्ठा twl4030_codec_data *codec;
	काष्ठा twl4030_vibra_data *vibra;

	/* twl6040 */
	पूर्णांक audpwron_gpio;	/* audio घातer-on gpio */
	पूर्णांक naudपूर्णांक_irq;	/* audio पूर्णांकerrupt */
	अचिन्हित पूर्णांक irq_base;
पूर्ण;

काष्ठा twl4030_platक्रमm_data अणु
	काष्ठा twl4030_घड़ी_init_data		*घड़ी;
	काष्ठा twl4030_bci_platक्रमm_data	*bci;
	काष्ठा twl4030_gpio_platक्रमm_data	*gpio;
	काष्ठा twl4030_madc_platक्रमm_data	*madc;
	काष्ठा twl4030_keypad_data		*keypad;
	काष्ठा twl4030_usb_data			*usb;
	काष्ठा twl4030_घातer_data		*घातer;
	काष्ठा twl4030_audio_data		*audio;

	/* Common LDO regulators क्रम TWL4030/TWL6030 */
	काष्ठा regulator_init_data		*vdac;
	काष्ठा regulator_init_data		*vaux1;
	काष्ठा regulator_init_data		*vaux2;
	काष्ठा regulator_init_data		*vaux3;
	काष्ठा regulator_init_data		*vdd1;
	काष्ठा regulator_init_data		*vdd2;
	काष्ठा regulator_init_data		*vdd3;
	/* TWL4030 LDO regulators */
	काष्ठा regulator_init_data		*vpll1;
	काष्ठा regulator_init_data		*vpll2;
	काष्ठा regulator_init_data		*vmmc1;
	काष्ठा regulator_init_data		*vmmc2;
	काष्ठा regulator_init_data		*vsim;
	काष्ठा regulator_init_data		*vaux4;
	काष्ठा regulator_init_data		*vio;
	काष्ठा regulator_init_data		*vपूर्णांकana1;
	काष्ठा regulator_init_data		*vपूर्णांकana2;
	काष्ठा regulator_init_data		*vपूर्णांकdig;
	/* TWL6030 LDO regulators */
	काष्ठा regulator_init_data              *vmmc;
	काष्ठा regulator_init_data              *vpp;
	काष्ठा regulator_init_data              *vusim;
	काष्ठा regulator_init_data              *vana;
	काष्ठा regulator_init_data              *vcxio;
	काष्ठा regulator_init_data              *vusb;
	काष्ठा regulator_init_data		*clk32kg;
	काष्ठा regulator_init_data              *v1v8;
	काष्ठा regulator_init_data              *v2v1;
	/* TWL6032 LDO regulators */
	काष्ठा regulator_init_data		*lकरो1;
	काष्ठा regulator_init_data		*lकरो2;
	काष्ठा regulator_init_data		*lकरो3;
	काष्ठा regulator_init_data		*lकरो4;
	काष्ठा regulator_init_data		*lकरो5;
	काष्ठा regulator_init_data		*lकरो6;
	काष्ठा regulator_init_data		*lकरो7;
	काष्ठा regulator_init_data		*lकरोln;
	काष्ठा regulator_init_data		*lकरोusb;
	/* TWL6032 DCDC regulators */
	काष्ठा regulator_init_data		*smps3;
	काष्ठा regulator_init_data		*smps4;
	काष्ठा regulator_init_data		*vio6025;
पूर्ण;

काष्ठा twl_regulator_driver_data अणु
	पूर्णांक		(*set_voltage)(व्योम *data, पूर्णांक target_uV);
	पूर्णांक		(*get_voltage)(व्योम *data);
	व्योम		*data;
	अचिन्हित दीर्घ	features;
पूर्ण;
/* chip-specअगरic feature flags, क्रम twl_regulator_driver_data.features */
#घोषणा TWL4030_VAUX2		BIT(0)	/* pre-5030 voltage ranges */
#घोषणा TPS_SUBSET		BIT(1)	/* tps659[23]0 have fewer LDOs */
#घोषणा TWL5031			BIT(2)  /* twl5031 has dअगरferent रेजिस्टरs */
#घोषणा TWL6030_CLASS		BIT(3)	/* TWL6030 class */
#घोषणा TWL6032_SUBCLASS	BIT(4)  /* TWL6032 has changed रेजिस्टरs */
#घोषणा TWL4030_ALLOW_UNSUPPORTED BIT(5) /* Some voltages are possible
					  * but not officially supported.
					  * This flag is necessary to
					  * enable them.
					  */

/*----------------------------------------------------------------------*/

पूर्णांक twl4030_sih_setup(काष्ठा device *dev, पूर्णांक module, पूर्णांक irq_base);

/* Offsets to Power Registers */
#घोषणा TWL4030_VDAC_DEV_GRP		0x3B
#घोषणा TWL4030_VDAC_DEDICATED		0x3E
#घोषणा TWL4030_VAUX1_DEV_GRP		0x17
#घोषणा TWL4030_VAUX1_DEDICATED		0x1A
#घोषणा TWL4030_VAUX2_DEV_GRP		0x1B
#घोषणा TWL4030_VAUX2_DEDICATED		0x1E
#घोषणा TWL4030_VAUX3_DEV_GRP		0x1F
#घोषणा TWL4030_VAUX3_DEDICATED		0x22

/*----------------------------------------------------------------------*/

/* Linux-specअगरic regulator identअगरiers ... क्रम now, we only support
 * the LDOs, and leave the three buck converters alone.  VDD1 and VDD2
 * need to tie पूर्णांकo hardware based voltage scaling (cpufreq etc), जबतक
 * VIO is generally fixed.
 */

/* TWL4030 SMPS/LDO's */
/* EXTERNAL dc-to-dc buck converters */
#घोषणा TWL4030_REG_VDD1	0
#घोषणा TWL4030_REG_VDD2	1
#घोषणा TWL4030_REG_VIO		2

/* EXTERNAL LDOs */
#घोषणा TWL4030_REG_VDAC	3
#घोषणा TWL4030_REG_VPLL1	4
#घोषणा TWL4030_REG_VPLL2	5	/* not on all chips */
#घोषणा TWL4030_REG_VMMC1	6
#घोषणा TWL4030_REG_VMMC2	7	/* not on all chips */
#घोषणा TWL4030_REG_VSIM	8	/* not on all chips */
#घोषणा TWL4030_REG_VAUX1	9	/* not on all chips */
#घोषणा TWL4030_REG_VAUX2_4030	10	/* (twl4030-specअगरic) */
#घोषणा TWL4030_REG_VAUX2	11	/* (twl5030 and newer) */
#घोषणा TWL4030_REG_VAUX3	12	/* not on all chips */
#घोषणा TWL4030_REG_VAUX4	13	/* not on all chips */

/* INTERNAL LDOs */
#घोषणा TWL4030_REG_VINTANA1	14
#घोषणा TWL4030_REG_VINTANA2	15
#घोषणा TWL4030_REG_VINTDIG	16
#घोषणा TWL4030_REG_VUSB1V5	17
#घोषणा TWL4030_REG_VUSB1V8	18
#घोषणा TWL4030_REG_VUSB3V1	19

/* TWL6030 SMPS/LDO's */
/* EXTERNAL dc-to-dc buck convertor controllable via SR */
#घोषणा TWL6030_REG_VDD1	30
#घोषणा TWL6030_REG_VDD2	31
#घोषणा TWL6030_REG_VDD3	32

/* Non SR compliant dc-to-dc buck convertors */
#घोषणा TWL6030_REG_VMEM	33
#घोषणा TWL6030_REG_V2V1	34
#घोषणा TWL6030_REG_V1V29	35
#घोषणा TWL6030_REG_V1V8	36

/* EXTERNAL LDOs */
#घोषणा TWL6030_REG_VAUX1_6030	37
#घोषणा TWL6030_REG_VAUX2_6030	38
#घोषणा TWL6030_REG_VAUX3_6030	39
#घोषणा TWL6030_REG_VMMC	40
#घोषणा TWL6030_REG_VPP		41
#घोषणा TWL6030_REG_VUSIM	42
#घोषणा TWL6030_REG_VANA	43
#घोषणा TWL6030_REG_VCXIO	44
#घोषणा TWL6030_REG_VDAC	45
#घोषणा TWL6030_REG_VUSB	46

/* INTERNAL LDOs */
#घोषणा TWL6030_REG_VRTC	47
#घोषणा TWL6030_REG_CLK32KG	48

/* LDOs on 6025 have dअगरferent names */
#घोषणा TWL6032_REG_LDO2	49
#घोषणा TWL6032_REG_LDO4	50
#घोषणा TWL6032_REG_LDO3	51
#घोषणा TWL6032_REG_LDO5	52
#घोषणा TWL6032_REG_LDO1	53
#घोषणा TWL6032_REG_LDO7	54
#घोषणा TWL6032_REG_LDO6	55
#घोषणा TWL6032_REG_LDOLN	56
#घोषणा TWL6032_REG_LDOUSB	57

/* 6025 DCDC supplies */
#घोषणा TWL6032_REG_SMPS3	58
#घोषणा TWL6032_REG_SMPS4	59
#घोषणा TWL6032_REG_VIO		60


#पूर्ण_अगर /* End of __TWL4030_H */
