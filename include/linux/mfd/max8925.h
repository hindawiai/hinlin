<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Maxim8925 Interface
 *
 * Copyright (C) 2009 Marvell International Ltd.
 *	Haojian Zhuang <haojian.zhuang@marvell.com>
 */

#अगर_अघोषित __LINUX_MFD_MAX8925_H
#घोषणा __LINUX_MFD_MAX8925_H

#समावेश <linux/mutex.h>
#समावेश <linux/पूर्णांकerrupt.h>

/* Unअगरied sub device IDs क्रम MAX8925 */
क्रमागत अणु
	MAX8925_ID_SD1,
	MAX8925_ID_SD2,
	MAX8925_ID_SD3,
	MAX8925_ID_LDO1,
	MAX8925_ID_LDO2,
	MAX8925_ID_LDO3,
	MAX8925_ID_LDO4,
	MAX8925_ID_LDO5,
	MAX8925_ID_LDO6,
	MAX8925_ID_LDO7,
	MAX8925_ID_LDO8,
	MAX8925_ID_LDO9,
	MAX8925_ID_LDO10,
	MAX8925_ID_LDO11,
	MAX8925_ID_LDO12,
	MAX8925_ID_LDO13,
	MAX8925_ID_LDO14,
	MAX8925_ID_LDO15,
	MAX8925_ID_LDO16,
	MAX8925_ID_LDO17,
	MAX8925_ID_LDO18,
	MAX8925_ID_LDO19,
	MAX8925_ID_LDO20,
	MAX8925_ID_MAX,
पूर्ण;

क्रमागत अणु
	/*
	 * Charging current threshold trigger going from fast अक्षरge
	 * to TOPOFF अक्षरge. From 5% to 20% of fasting अक्षरging current.
	 */
	MAX8925_TOPOFF_THR_5PER,
	MAX8925_TOPOFF_THR_10PER,
	MAX8925_TOPOFF_THR_15PER,
	MAX8925_TOPOFF_THR_20PER,
पूर्ण;

क्रमागत अणु
	/* Fast अक्षरging current */
	MAX8925_FCHG_85MA,
	MAX8925_FCHG_300MA,
	MAX8925_FCHG_460MA,
	MAX8925_FCHG_600MA,
	MAX8925_FCHG_700MA,
	MAX8925_FCHG_800MA,
	MAX8925_FCHG_900MA,
	MAX8925_FCHG_1000MA,
पूर्ण;

/* Charger रेजिस्टरs */
#घोषणा MAX8925_CHG_IRQ1		(0x7e)
#घोषणा MAX8925_CHG_IRQ2		(0x7f)
#घोषणा MAX8925_CHG_IRQ1_MASK		(0x80)
#घोषणा MAX8925_CHG_IRQ2_MASK		(0x81)
#घोषणा MAX8925_CHG_STATUS		(0x82)

/* GPM रेजिस्टरs */
#घोषणा MAX8925_SYSENSEL		(0x00)
#घोषणा MAX8925_ON_OFF_IRQ1		(0x01)
#घोषणा MAX8925_ON_OFF_IRQ1_MASK	(0x02)
#घोषणा MAX8925_ON_OFF_STATUS		(0x03)
#घोषणा MAX8925_ON_OFF_IRQ2		(0x0d)
#घोषणा MAX8925_ON_OFF_IRQ2_MASK	(0x0e)
#घोषणा MAX8925_RESET_CNFG		(0x0f)

/* Touch रेजिस्टरs */
#घोषणा MAX8925_TSC_IRQ			(0x00)
#घोषणा MAX8925_TSC_IRQ_MASK		(0x01)
#घोषणा MAX8925_TSC_CNFG1		(0x02)
#घोषणा MAX8925_ADC_SCHED		(0x10)
#घोषणा MAX8925_ADC_RES_END		(0x6f)

#घोषणा MAX8925_NREF_OK			(1 << 4)

/* RTC रेजिस्टरs */
#घोषणा MAX8925_ALARM0_CNTL		(0x18)
#घोषणा MAX8925_ALARM1_CNTL		(0x19)
#घोषणा MAX8925_RTC_IRQ			(0x1c)
#घोषणा MAX8925_RTC_IRQ_MASK		(0x1d)
#घोषणा MAX8925_MPL_CNTL		(0x1e)

/* WLED रेजिस्टरs */
#घोषणा MAX8925_WLED_MODE_CNTL		(0x84)
#घोषणा MAX8925_WLED_CNTL		(0x85)

/* MAX8925 Registers */
#घोषणा MAX8925_SDCTL1			(0x04)
#घोषणा MAX8925_SDCTL2			(0x07)
#घोषणा MAX8925_SDCTL3			(0x0A)
#घोषणा MAX8925_SDV1			(0x06)
#घोषणा MAX8925_SDV2			(0x09)
#घोषणा MAX8925_SDV3			(0x0C)
#घोषणा MAX8925_LDOCTL1			(0x18)
#घोषणा MAX8925_LDOCTL2			(0x1C)
#घोषणा MAX8925_LDOCTL3			(0x20)
#घोषणा MAX8925_LDOCTL4			(0x24)
#घोषणा MAX8925_LDOCTL5			(0x28)
#घोषणा MAX8925_LDOCTL6			(0x2C)
#घोषणा MAX8925_LDOCTL7			(0x30)
#घोषणा MAX8925_LDOCTL8			(0x34)
#घोषणा MAX8925_LDOCTL9			(0x38)
#घोषणा MAX8925_LDOCTL10		(0x3C)
#घोषणा MAX8925_LDOCTL11		(0x40)
#घोषणा MAX8925_LDOCTL12		(0x44)
#घोषणा MAX8925_LDOCTL13		(0x48)
#घोषणा MAX8925_LDOCTL14		(0x4C)
#घोषणा MAX8925_LDOCTL15		(0x50)
#घोषणा MAX8925_LDOCTL16		(0x10)
#घोषणा MAX8925_LDOCTL17		(0x14)
#घोषणा MAX8925_LDOCTL18		(0x72)
#घोषणा MAX8925_LDOCTL19		(0x5C)
#घोषणा MAX8925_LDOCTL20		(0x9C)
#घोषणा MAX8925_LDOVOUT1		(0x1A)
#घोषणा MAX8925_LDOVOUT2		(0x1E)
#घोषणा MAX8925_LDOVOUT3		(0x22)
#घोषणा MAX8925_LDOVOUT4		(0x26)
#घोषणा MAX8925_LDOVOUT5		(0x2A)
#घोषणा MAX8925_LDOVOUT6		(0x2E)
#घोषणा MAX8925_LDOVOUT7		(0x32)
#घोषणा MAX8925_LDOVOUT8		(0x36)
#घोषणा MAX8925_LDOVOUT9		(0x3A)
#घोषणा MAX8925_LDOVOUT10		(0x3E)
#घोषणा MAX8925_LDOVOUT11		(0x42)
#घोषणा MAX8925_LDOVOUT12		(0x46)
#घोषणा MAX8925_LDOVOUT13		(0x4A)
#घोषणा MAX8925_LDOVOUT14		(0x4E)
#घोषणा MAX8925_LDOVOUT15		(0x52)
#घोषणा MAX8925_LDOVOUT16		(0x12)
#घोषणा MAX8925_LDOVOUT17		(0x16)
#घोषणा MAX8925_LDOVOUT18		(0x74)
#घोषणा MAX8925_LDOVOUT19		(0x5E)
#घोषणा MAX8925_LDOVOUT20		(0x9E)

/* bit definitions */
#घोषणा CHG_IRQ1_MASK			(0x07)
#घोषणा CHG_IRQ2_MASK			(0xff)
#घोषणा ON_OFF_IRQ1_MASK		(0xff)
#घोषणा ON_OFF_IRQ2_MASK		(0x03)
#घोषणा TSC_IRQ_MASK			(0x03)
#घोषणा RTC_IRQ_MASK			(0x0c)

#घोषणा MAX8925_NAME_SIZE		(32)

/* IRQ definitions */
क्रमागत अणु
	MAX8925_IRQ_VCHG_DC_OVP,
	MAX8925_IRQ_VCHG_DC_F,
	MAX8925_IRQ_VCHG_DC_R,
	MAX8925_IRQ_VCHG_THM_OK_R,
	MAX8925_IRQ_VCHG_THM_OK_F,
	MAX8925_IRQ_VCHG_SYSLOW_F,
	MAX8925_IRQ_VCHG_SYSLOW_R,
	MAX8925_IRQ_VCHG_RST,
	MAX8925_IRQ_VCHG_DONE,
	MAX8925_IRQ_VCHG_TOPOFF,
	MAX8925_IRQ_VCHG_TMR_FAULT,
	MAX8925_IRQ_GPM_RSTIN,
	MAX8925_IRQ_GPM_MPL,
	MAX8925_IRQ_GPM_SW_3SEC,
	MAX8925_IRQ_GPM_EXTON_F,
	MAX8925_IRQ_GPM_EXTON_R,
	MAX8925_IRQ_GPM_SW_1SEC,
	MAX8925_IRQ_GPM_SW_F,
	MAX8925_IRQ_GPM_SW_R,
	MAX8925_IRQ_GPM_SYSCKEN_F,
	MAX8925_IRQ_GPM_SYSCKEN_R,
	MAX8925_IRQ_RTC_ALARM1,
	MAX8925_IRQ_RTC_ALARM0,
	MAX8925_IRQ_TSC_STICK,
	MAX8925_IRQ_TSC_NSTICK,
	MAX8925_NR_IRQS,
पूर्ण;



काष्ठा max8925_chip अणु
	काष्ठा device		*dev;
	काष्ठा i2c_client	*i2c;
	काष्ठा i2c_client	*adc;
	काष्ठा i2c_client	*rtc;
	काष्ठा mutex		io_lock;
	काष्ठा mutex		irq_lock;

	पूर्णांक			irq_base;
	पूर्णांक			core_irq;
	पूर्णांक			tsc_irq;
	अचिन्हित पूर्णांक            wakeup_flag;
पूर्ण;

काष्ठा max8925_backlight_pdata अणु
	पूर्णांक	lxw_scl;	/* 0/1 -- 0.8Ohm/0.4Ohm */
	पूर्णांक	lxw_freq;	/* 700KHz ~ 1400KHz */
	पूर्णांक	dual_string;	/* 0/1 -- single/dual string */
पूर्ण;

काष्ठा max8925_touch_pdata अणु
	अचिन्हित पूर्णांक		flags;
पूर्ण;

काष्ठा max8925_घातer_pdata अणु
	पूर्णांक		(*set_अक्षरger)(पूर्णांक);
	अचिन्हित	batt_detect:1;
	अचिन्हित	topoff_threshold:2;
	अचिन्हित	fast_अक्षरge:3;	/* अक्षरge current */
	अचिन्हित	no_temp_support:1; /* set अगर no temperature detect */
	अचिन्हित	no_insert_detect:1; /* set अगर no ac insert detect */
	अक्षर		**supplied_to;
	पूर्णांक		num_supplicants;
पूर्ण;

/*
 * irq_base: stores IRQ base number of MAX8925 in platक्रमm
 * tsc_irq: stores IRQ number of MAX8925 TSC
 */
काष्ठा max8925_platक्रमm_data अणु
	काष्ठा max8925_backlight_pdata	*backlight;
	काष्ठा max8925_touch_pdata	*touch;
	काष्ठा max8925_घातer_pdata	*घातer;
	काष्ठा regulator_init_data	*sd1;
	काष्ठा regulator_init_data	*sd2;
	काष्ठा regulator_init_data	*sd3;
	काष्ठा regulator_init_data	*lकरो1;
	काष्ठा regulator_init_data	*lकरो2;
	काष्ठा regulator_init_data	*lकरो3;
	काष्ठा regulator_init_data	*lकरो4;
	काष्ठा regulator_init_data	*lकरो5;
	काष्ठा regulator_init_data	*lकरो6;
	काष्ठा regulator_init_data	*lकरो7;
	काष्ठा regulator_init_data	*lकरो8;
	काष्ठा regulator_init_data	*lकरो9;
	काष्ठा regulator_init_data	*lकरो10;
	काष्ठा regulator_init_data	*lकरो11;
	काष्ठा regulator_init_data	*lकरो12;
	काष्ठा regulator_init_data	*lकरो13;
	काष्ठा regulator_init_data	*lकरो14;
	काष्ठा regulator_init_data	*lकरो15;
	काष्ठा regulator_init_data	*lकरो16;
	काष्ठा regulator_init_data	*lकरो17;
	काष्ठा regulator_init_data	*lकरो18;
	काष्ठा regulator_init_data	*lकरो19;
	काष्ठा regulator_init_data	*lकरो20;

	पूर्णांक		irq_base;
	पूर्णांक		tsc_irq;
पूर्ण;

बाह्य पूर्णांक max8925_reg_पढ़ो(काष्ठा i2c_client *, पूर्णांक);
बाह्य पूर्णांक max8925_reg_ग_लिखो(काष्ठा i2c_client *, पूर्णांक, अचिन्हित अक्षर);
बाह्य पूर्णांक max8925_bulk_पढ़ो(काष्ठा i2c_client *, पूर्णांक, पूर्णांक, अचिन्हित अक्षर *);
बाह्य पूर्णांक max8925_bulk_ग_लिखो(काष्ठा i2c_client *, पूर्णांक, पूर्णांक, अचिन्हित अक्षर *);
बाह्य पूर्णांक max8925_set_bits(काष्ठा i2c_client *, पूर्णांक, अचिन्हित अक्षर,
			अचिन्हित अक्षर);

बाह्य पूर्णांक max8925_device_init(काष्ठा max8925_chip *,
				काष्ठा max8925_platक्रमm_data *);
बाह्य व्योम max8925_device_निकास(काष्ठा max8925_chip *);
#पूर्ण_अगर /* __LINUX_MFD_MAX8925_H */

