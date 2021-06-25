<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * max8998-निजी.h - Voltage regulator driver क्रम the Maxim 8998
 *
 *  Copyright (C) 2009-2010 Samsung Electrnoics
 *  Kyungmin Park <kyungmin.park@samsung.com>
 *  Marek Szyprowski <m.szyprowski@samsung.com>
 */

#अगर_अघोषित __LINUX_MFD_MAX8998_PRIV_H
#घोषणा __LINUX_MFD_MAX8998_PRIV_H

#घोषणा MAX8998_NUM_IRQ_REGS	4

/* MAX 8998 रेजिस्टरs */
क्रमागत अणु
	MAX8998_REG_IRQ1,
	MAX8998_REG_IRQ2,
	MAX8998_REG_IRQ3,
	MAX8998_REG_IRQ4,
	MAX8998_REG_IRQM1,
	MAX8998_REG_IRQM2,
	MAX8998_REG_IRQM3,
	MAX8998_REG_IRQM4,
	MAX8998_REG_STATUS1,
	MAX8998_REG_STATUS2,
	MAX8998_REG_STATUSM1,
	MAX8998_REG_STATUSM2,
	MAX8998_REG_CHGR1,
	MAX8998_REG_CHGR2,
	MAX8998_REG_LDO_ACTIVE_DISCHARGE1,
	MAX8998_REG_LDO_ACTIVE_DISCHARGE2,
	MAX8998_REG_BUCK_ACTIVE_DISCHARGE3,
	MAX8998_REG_ONOFF1,
	MAX8998_REG_ONOFF2,
	MAX8998_REG_ONOFF3,
	MAX8998_REG_ONOFF4,
	MAX8998_REG_BUCK1_VOLTAGE1,
	MAX8998_REG_BUCK1_VOLTAGE2,
	MAX8998_REG_BUCK1_VOLTAGE3,
	MAX8998_REG_BUCK1_VOLTAGE4,
	MAX8998_REG_BUCK2_VOLTAGE1,
	MAX8998_REG_BUCK2_VOLTAGE2,
	MAX8998_REG_BUCK3,
	MAX8998_REG_BUCK4,
	MAX8998_REG_LDO2_LDO3,
	MAX8998_REG_LDO4,
	MAX8998_REG_LDO5,
	MAX8998_REG_LDO6,
	MAX8998_REG_LDO7,
	MAX8998_REG_LDO8_LDO9,
	MAX8998_REG_LDO10_LDO11,
	MAX8998_REG_LDO12,
	MAX8998_REG_LDO13,
	MAX8998_REG_LDO14,
	MAX8998_REG_LDO15,
	MAX8998_REG_LDO16,
	MAX8998_REG_LDO17,
	MAX8998_REG_BKCHR,
	MAX8998_REG_LBCNFG1,
	MAX8998_REG_LBCNFG2,
पूर्ण;

/* IRQ definitions */
क्रमागत अणु
	MAX8998_IRQ_DCINF,
	MAX8998_IRQ_DCINR,
	MAX8998_IRQ_JIGF,
	MAX8998_IRQ_JIGR,
	MAX8998_IRQ_PWRONF,
	MAX8998_IRQ_PWRONR,

	MAX8998_IRQ_WTSREVNT,
	MAX8998_IRQ_SMPLEVNT,
	MAX8998_IRQ_ALARM1,
	MAX8998_IRQ_ALARM0,

	MAX8998_IRQ_ONKEY1S,
	MAX8998_IRQ_TOPOFFR,
	MAX8998_IRQ_DCINOVPR,
	MAX8998_IRQ_CHGRSTF,
	MAX8998_IRQ_DONER,
	MAX8998_IRQ_CHGFAULT,

	MAX8998_IRQ_LOBAT1,
	MAX8998_IRQ_LOBAT2,

	MAX8998_IRQ_NR,
पूर्ण;

/* MAX8998 various variants */
क्रमागत अणु
	TYPE_MAX8998 = 0, /* Default */
	TYPE_LP3974,	/* National version of MAX8998 */
	TYPE_LP3979,	/* Added AVS */
पूर्ण;

#घोषणा MAX8998_IRQ_DCINF_MASK		(1 << 2)
#घोषणा MAX8998_IRQ_DCINR_MASK		(1 << 3)
#घोषणा MAX8998_IRQ_JIGF_MASK		(1 << 4)
#घोषणा MAX8998_IRQ_JIGR_MASK		(1 << 5)
#घोषणा MAX8998_IRQ_PWRONF_MASK		(1 << 6)
#घोषणा MAX8998_IRQ_PWRONR_MASK		(1 << 7)

#घोषणा MAX8998_IRQ_WTSREVNT_MASK	(1 << 0)
#घोषणा MAX8998_IRQ_SMPLEVNT_MASK	(1 << 1)
#घोषणा MAX8998_IRQ_ALARM1_MASK		(1 << 2)
#घोषणा MAX8998_IRQ_ALARM0_MASK		(1 << 3)

#घोषणा MAX8998_IRQ_ONKEY1S_MASK	(1 << 0)
#घोषणा MAX8998_IRQ_TOPOFFR_MASK	(1 << 2)
#घोषणा MAX8998_IRQ_DCINOVPR_MASK	(1 << 3)
#घोषणा MAX8998_IRQ_CHGRSTF_MASK	(1 << 4)
#घोषणा MAX8998_IRQ_DONER_MASK		(1 << 5)
#घोषणा MAX8998_IRQ_CHGFAULT_MASK	(1 << 7)

#घोषणा MAX8998_IRQ_LOBAT1_MASK		(1 << 0)
#घोषणा MAX8998_IRQ_LOBAT2_MASK		(1 << 1)

#घोषणा MAX8998_ENRAMP                  (1 << 4)

काष्ठा irq_करोमुख्य;

/**
 * काष्ठा max8998_dev - max8998 master device क्रम sub-drivers
 * @dev: master device of the chip (can be used to access platक्रमm data)
 * @pdata: platक्रमm data क्रम the driver and subdrivers
 * @i2c: i2c client निजी data क्रम regulator
 * @rtc: i2c client निजी data क्रम rtc
 * @iolock: mutex क्रम serializing io access
 * @irqlock: mutex क्रम buslock
 * @irq_base: base IRQ number क्रम max8998, required क्रम IRQs
 * @irq: generic IRQ number क्रम max8998
 * @ono: घातer onoff IRQ number क्रम max8998
 * @irq_masks_cur: currently active value
 * @irq_masks_cache: cached hardware value
 * @type: indicate which max8998 "variant" is used
 */
काष्ठा max8998_dev अणु
	काष्ठा device *dev;
	काष्ठा max8998_platक्रमm_data *pdata;
	काष्ठा i2c_client *i2c;
	काष्ठा i2c_client *rtc;
	काष्ठा mutex iolock;
	काष्ठा mutex irqlock;

	अचिन्हित पूर्णांक irq_base;
	काष्ठा irq_करोमुख्य *irq_करोमुख्य;
	पूर्णांक irq;
	पूर्णांक ono;
	u8 irq_masks_cur[MAX8998_NUM_IRQ_REGS];
	u8 irq_masks_cache[MAX8998_NUM_IRQ_REGS];
	अचिन्हित दीर्घ type;
	bool wakeup;
पूर्ण;

पूर्णांक max8998_irq_init(काष्ठा max8998_dev *max8998);
व्योम max8998_irq_निकास(काष्ठा max8998_dev *max8998);
पूर्णांक max8998_irq_resume(काष्ठा max8998_dev *max8998);

बाह्य पूर्णांक max8998_पढ़ो_reg(काष्ठा i2c_client *i2c, u8 reg, u8 *dest);
बाह्य पूर्णांक max8998_bulk_पढ़ो(काष्ठा i2c_client *i2c, u8 reg, पूर्णांक count,
		u8 *buf);
बाह्य पूर्णांक max8998_ग_लिखो_reg(काष्ठा i2c_client *i2c, u8 reg, u8 value);
बाह्य पूर्णांक max8998_bulk_ग_लिखो(काष्ठा i2c_client *i2c, u8 reg, पूर्णांक count,
		u8 *buf);
बाह्य पूर्णांक max8998_update_reg(काष्ठा i2c_client *i2c, u8 reg, u8 val, u8 mask);

#पूर्ण_अगर /*  __LINUX_MFD_MAX8998_PRIV_H */
