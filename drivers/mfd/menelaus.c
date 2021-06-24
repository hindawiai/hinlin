<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2004 Texas Instruments, Inc.
 *
 * Some parts based tps65010.c:
 * Copyright (C) 2004 Texas Instruments and
 * Copyright (C) 2004-2005 David Brownell
 *
 * Some parts based on tlv320aic24.c:
 * Copyright (C) by Kai Svahn <kai.svahn@nokia.com>
 *
 * Changes क्रम पूर्णांकerrupt handling and clean-up by
 * Tony Lindgren <tony@atomide.com> and Imre Deak <imre.deak@nokia.com>
 * Cleanup and generalized support क्रम voltage setting by
 * Juha Yrjola
 * Added support क्रम controlling VCORE and regulator sleep states,
 * Amit Kucheria <amit.kucheria@nokia.com>
 * Copyright (C) 2005, 2006 Nokia Corporation
 */

#समावेश <linux/module.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/sched.h>
#समावेश <linux/mutex.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/delay.h>
#समावेश <linux/rtc.h>
#समावेश <linux/bcd.h>
#समावेश <linux/slab.h>
#समावेश <linux/mfd/menelaus.h>
#समावेश <linux/gpपन.स>

#समावेश <यंत्र/mach/irq.h>


#घोषणा DRIVER_NAME			"menelaus"

#घोषणा MENELAUS_I2C_ADDRESS		0x72

#घोषणा MENELAUS_REV			0x01
#घोषणा MENELAUS_VCORE_CTRL1		0x02
#घोषणा MENELAUS_VCORE_CTRL2		0x03
#घोषणा MENELAUS_VCORE_CTRL3		0x04
#घोषणा MENELAUS_VCORE_CTRL4		0x05
#घोषणा MENELAUS_VCORE_CTRL5		0x06
#घोषणा MENELAUS_DCDC_CTRL1		0x07
#घोषणा MENELAUS_DCDC_CTRL2		0x08
#घोषणा MENELAUS_DCDC_CTRL3		0x09
#घोषणा MENELAUS_LDO_CTRL1		0x0A
#घोषणा MENELAUS_LDO_CTRL2		0x0B
#घोषणा MENELAUS_LDO_CTRL3		0x0C
#घोषणा MENELAUS_LDO_CTRL4		0x0D
#घोषणा MENELAUS_LDO_CTRL5		0x0E
#घोषणा MENELAUS_LDO_CTRL6		0x0F
#घोषणा MENELAUS_LDO_CTRL7		0x10
#घोषणा MENELAUS_LDO_CTRL8		0x11
#घोषणा MENELAUS_SLEEP_CTRL1		0x12
#घोषणा MENELAUS_SLEEP_CTRL2		0x13
#घोषणा MENELAUS_DEVICE_OFF		0x14
#घोषणा MENELAUS_OSC_CTRL		0x15
#घोषणा MENELAUS_DETECT_CTRL		0x16
#घोषणा MENELAUS_INT_MASK1		0x17
#घोषणा MENELAUS_INT_MASK2		0x18
#घोषणा MENELAUS_INT_STATUS1		0x19
#घोषणा MENELAUS_INT_STATUS2		0x1A
#घोषणा MENELAUS_INT_ACK1		0x1B
#घोषणा MENELAUS_INT_ACK2		0x1C
#घोषणा MENELAUS_GPIO_CTRL		0x1D
#घोषणा MENELAUS_GPIO_IN		0x1E
#घोषणा MENELAUS_GPIO_OUT		0x1F
#घोषणा MENELAUS_BBSMS			0x20
#घोषणा MENELAUS_RTC_CTRL		0x21
#घोषणा MENELAUS_RTC_UPDATE		0x22
#घोषणा MENELAUS_RTC_SEC		0x23
#घोषणा MENELAUS_RTC_MIN		0x24
#घोषणा MENELAUS_RTC_HR			0x25
#घोषणा MENELAUS_RTC_DAY		0x26
#घोषणा MENELAUS_RTC_MON		0x27
#घोषणा MENELAUS_RTC_YR			0x28
#घोषणा MENELAUS_RTC_WKDAY		0x29
#घोषणा MENELAUS_RTC_AL_SEC		0x2A
#घोषणा MENELAUS_RTC_AL_MIN		0x2B
#घोषणा MENELAUS_RTC_AL_HR		0x2C
#घोषणा MENELAUS_RTC_AL_DAY		0x2D
#घोषणा MENELAUS_RTC_AL_MON		0x2E
#घोषणा MENELAUS_RTC_AL_YR		0x2F
#घोषणा MENELAUS_RTC_COMP_MSB		0x30
#घोषणा MENELAUS_RTC_COMP_LSB		0x31
#घोषणा MENELAUS_S1_PULL_EN		0x32
#घोषणा MENELAUS_S1_PULL_सूची		0x33
#घोषणा MENELAUS_S2_PULL_EN		0x34
#घोषणा MENELAUS_S2_PULL_सूची		0x35
#घोषणा MENELAUS_MCT_CTRL1		0x36
#घोषणा MENELAUS_MCT_CTRL2		0x37
#घोषणा MENELAUS_MCT_CTRL3		0x38
#घोषणा MENELAUS_MCT_PIN_ST		0x39
#घोषणा MENELAUS_DEBOUNCE1		0x3A

#घोषणा IH_MENELAUS_IRQS		12
#घोषणा MENELAUS_MMC_S1CD_IRQ		0	/* MMC slot 1 card change */
#घोषणा MENELAUS_MMC_S2CD_IRQ		1	/* MMC slot 2 card change */
#घोषणा MENELAUS_MMC_S1D1_IRQ		2	/* MMC DAT1 low in slot 1 */
#घोषणा MENELAUS_MMC_S2D1_IRQ		3	/* MMC DAT1 low in slot 2 */
#घोषणा MENELAUS_LOWBAT_IRQ		4	/* Low battery */
#घोषणा MENELAUS_HOTDIE_IRQ		5	/* Hot die detect */
#घोषणा MENELAUS_UVLO_IRQ		6	/* UVLO detect */
#घोषणा MENELAUS_TSHUT_IRQ		7	/* Thermal shutकरोwn */
#घोषणा MENELAUS_RTCTMR_IRQ		8	/* RTC समयr */
#घोषणा MENELAUS_RTCALM_IRQ		9	/* RTC alarm */
#घोषणा MENELAUS_RTCERR_IRQ		10	/* RTC error */
#घोषणा MENELAUS_PSHBTN_IRQ		11	/* Push button */
#घोषणा MENELAUS_RESERVED12_IRQ		12	/* Reserved */
#घोषणा MENELAUS_RESERVED13_IRQ		13	/* Reserved */
#घोषणा MENELAUS_RESERVED14_IRQ		14	/* Reserved */
#घोषणा MENELAUS_RESERVED15_IRQ		15	/* Reserved */

/* VCORE_CTRL1 रेजिस्टर */
#घोषणा VCORE_CTRL1_BYP_COMP		(1 << 5)
#घोषणा VCORE_CTRL1_HW_NSW		(1 << 7)

/* GPIO_CTRL रेजिस्टर */
#घोषणा GPIO_CTRL_SLOTSELEN		(1 << 5)
#घोषणा GPIO_CTRL_SLPCTLEN		(1 << 6)
#घोषणा GPIO1_सूची_INPUT			(1 << 0)
#घोषणा GPIO2_सूची_INPUT			(1 << 1)
#घोषणा GPIO3_सूची_INPUT			(1 << 2)

/* MCT_CTRL1 रेजिस्टर */
#घोषणा MCT_CTRL1_S1_CMD_OD		(1 << 2)
#घोषणा MCT_CTRL1_S2_CMD_OD		(1 << 3)

/* MCT_CTRL2 रेजिस्टर */
#घोषणा MCT_CTRL2_VS2_SEL_D0		(1 << 0)
#घोषणा MCT_CTRL2_VS2_SEL_D1		(1 << 1)
#घोषणा MCT_CTRL2_S1CD_BUFEN		(1 << 4)
#घोषणा MCT_CTRL2_S2CD_BUFEN		(1 << 5)
#घोषणा MCT_CTRL2_S1CD_DBEN		(1 << 6)
#घोषणा MCT_CTRL2_S2CD_BEN		(1 << 7)

/* MCT_CTRL3 रेजिस्टर */
#घोषणा MCT_CTRL3_SLOT1_EN		(1 << 0)
#घोषणा MCT_CTRL3_SLOT2_EN		(1 << 1)
#घोषणा MCT_CTRL3_S1_AUTO_EN		(1 << 2)
#घोषणा MCT_CTRL3_S2_AUTO_EN		(1 << 3)

/* MCT_PIN_ST रेजिस्टर */
#घोषणा MCT_PIN_ST_S1_CD_ST		(1 << 0)
#घोषणा MCT_PIN_ST_S2_CD_ST		(1 << 1)

अटल व्योम menelaus_work(काष्ठा work_काष्ठा *_menelaus);

काष्ठा menelaus_chip अणु
	काष्ठा mutex		lock;
	काष्ठा i2c_client	*client;
	काष्ठा work_काष्ठा	work;
#अगर_घोषित CONFIG_RTC_DRV_TWL92330
	काष्ठा rtc_device	*rtc;
	u8			rtc_control;
	अचिन्हित		uie:1;
#पूर्ण_अगर
	अचिन्हित		vcore_hw_mode:1;
	u8			mask1, mask2;
	व्योम			(*handlers[16])(काष्ठा menelaus_chip *);
	व्योम			(*mmc_callback)(व्योम *data, u8 mask);
	व्योम			*mmc_callback_data;
पूर्ण;

अटल काष्ठा menelaus_chip *the_menelaus;

अटल पूर्णांक menelaus_ग_लिखो_reg(पूर्णांक reg, u8 value)
अणु
	पूर्णांक val = i2c_smbus_ग_लिखो_byte_data(the_menelaus->client, reg, value);

	अगर (val < 0) अणु
		pr_err(DRIVER_NAME ": write error");
		वापस val;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक menelaus_पढ़ो_reg(पूर्णांक reg)
अणु
	पूर्णांक val = i2c_smbus_पढ़ो_byte_data(the_menelaus->client, reg);

	अगर (val < 0)
		pr_err(DRIVER_NAME ": read error");

	वापस val;
पूर्ण

अटल पूर्णांक menelaus_enable_irq(पूर्णांक irq)
अणु
	अगर (irq > 7) अणु
		irq -= 8;
		the_menelaus->mask2 &= ~(1 << irq);
		वापस menelaus_ग_लिखो_reg(MENELAUS_INT_MASK2,
				the_menelaus->mask2);
	पूर्ण अन्यथा अणु
		the_menelaus->mask1 &= ~(1 << irq);
		वापस menelaus_ग_लिखो_reg(MENELAUS_INT_MASK1,
				the_menelaus->mask1);
	पूर्ण
पूर्ण

अटल पूर्णांक menelaus_disable_irq(पूर्णांक irq)
अणु
	अगर (irq > 7) अणु
		irq -= 8;
		the_menelaus->mask2 |= (1 << irq);
		वापस menelaus_ग_लिखो_reg(MENELAUS_INT_MASK2,
				the_menelaus->mask2);
	पूर्ण अन्यथा अणु
		the_menelaus->mask1 |= (1 << irq);
		वापस menelaus_ग_लिखो_reg(MENELAUS_INT_MASK1,
				the_menelaus->mask1);
	पूर्ण
पूर्ण

अटल पूर्णांक menelaus_ack_irq(पूर्णांक irq)
अणु
	अगर (irq > 7)
		वापस menelaus_ग_लिखो_reg(MENELAUS_INT_ACK2, 1 << (irq - 8));
	अन्यथा
		वापस menelaus_ग_लिखो_reg(MENELAUS_INT_ACK1, 1 << irq);
पूर्ण

/* Adds a handler क्रम an पूर्णांकerrupt. Does not run in पूर्णांकerrupt context */
अटल पूर्णांक menelaus_add_irq_work(पूर्णांक irq,
		व्योम (*handler)(काष्ठा menelaus_chip *))
अणु
	पूर्णांक ret = 0;

	mutex_lock(&the_menelaus->lock);
	the_menelaus->handlers[irq] = handler;
	ret = menelaus_enable_irq(irq);
	mutex_unlock(&the_menelaus->lock);

	वापस ret;
पूर्ण

/* Removes handler क्रम an पूर्णांकerrupt */
अटल पूर्णांक menelaus_हटाओ_irq_work(पूर्णांक irq)
अणु
	पूर्णांक ret = 0;

	mutex_lock(&the_menelaus->lock);
	ret = menelaus_disable_irq(irq);
	the_menelaus->handlers[irq] = शून्य;
	mutex_unlock(&the_menelaus->lock);

	वापस ret;
पूर्ण

/*
 * Gets scheduled when a card detect पूर्णांकerrupt happens. Note that in some हालs
 * this line is wired to card cover चयन rather than the card detect चयन
 * in each slot. In this हाल the cards are not seen by menelaus.
 * FIXME: Add handling क्रम D1 too
 */
अटल व्योम menelaus_mmc_cd_work(काष्ठा menelaus_chip *menelaus_hw)
अणु
	पूर्णांक reg;
	अचिन्हित अक्षर card_mask = 0;

	reg = menelaus_पढ़ो_reg(MENELAUS_MCT_PIN_ST);
	अगर (reg < 0)
		वापस;

	अगर (!(reg & 0x1))
		card_mask |= MCT_PIN_ST_S1_CD_ST;

	अगर (!(reg & 0x2))
		card_mask |= MCT_PIN_ST_S2_CD_ST;

	अगर (menelaus_hw->mmc_callback)
		menelaus_hw->mmc_callback(menelaus_hw->mmc_callback_data,
					  card_mask);
पूर्ण

/*
 * Toggles the MMC slots between खोलो-drain and push-pull mode.
 */
पूर्णांक menelaus_set_mmc_खोलोdrain(पूर्णांक slot, पूर्णांक enable)
अणु
	पूर्णांक ret, val;

	अगर (slot != 1 && slot != 2)
		वापस -EINVAL;
	mutex_lock(&the_menelaus->lock);
	ret = menelaus_पढ़ो_reg(MENELAUS_MCT_CTRL1);
	अगर (ret < 0) अणु
		mutex_unlock(&the_menelaus->lock);
		वापस ret;
	पूर्ण
	val = ret;
	अगर (slot == 1) अणु
		अगर (enable)
			val |= MCT_CTRL1_S1_CMD_OD;
		अन्यथा
			val &= ~MCT_CTRL1_S1_CMD_OD;
	पूर्ण अन्यथा अणु
		अगर (enable)
			val |= MCT_CTRL1_S2_CMD_OD;
		अन्यथा
			val &= ~MCT_CTRL1_S2_CMD_OD;
	पूर्ण
	ret = menelaus_ग_लिखो_reg(MENELAUS_MCT_CTRL1, val);
	mutex_unlock(&the_menelaus->lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(menelaus_set_mmc_खोलोdrain);

पूर्णांक menelaus_set_slot_sel(पूर्णांक enable)
अणु
	पूर्णांक ret;

	mutex_lock(&the_menelaus->lock);
	ret = menelaus_पढ़ो_reg(MENELAUS_GPIO_CTRL);
	अगर (ret < 0)
		जाओ out;
	ret |= GPIO2_सूची_INPUT;
	अगर (enable)
		ret |= GPIO_CTRL_SLOTSELEN;
	अन्यथा
		ret &= ~GPIO_CTRL_SLOTSELEN;
	ret = menelaus_ग_लिखो_reg(MENELAUS_GPIO_CTRL, ret);
out:
	mutex_unlock(&the_menelaus->lock);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(menelaus_set_slot_sel);

पूर्णांक menelaus_set_mmc_slot(पूर्णांक slot, पूर्णांक enable, पूर्णांक घातer, पूर्णांक cd_en)
अणु
	पूर्णांक ret, val;

	अगर (slot != 1 && slot != 2)
		वापस -EINVAL;
	अगर (घातer >= 3)
		वापस -EINVAL;

	mutex_lock(&the_menelaus->lock);

	ret = menelaus_पढ़ो_reg(MENELAUS_MCT_CTRL2);
	अगर (ret < 0)
		जाओ out;
	val = ret;
	अगर (slot == 1) अणु
		अगर (cd_en)
			val |= MCT_CTRL2_S1CD_BUFEN | MCT_CTRL2_S1CD_DBEN;
		अन्यथा
			val &= ~(MCT_CTRL2_S1CD_BUFEN | MCT_CTRL2_S1CD_DBEN);
	पूर्ण अन्यथा अणु
		अगर (cd_en)
			val |= MCT_CTRL2_S2CD_BUFEN | MCT_CTRL2_S2CD_BEN;
		अन्यथा
			val &= ~(MCT_CTRL2_S2CD_BUFEN | MCT_CTRL2_S2CD_BEN);
	पूर्ण
	ret = menelaus_ग_लिखो_reg(MENELAUS_MCT_CTRL2, val);
	अगर (ret < 0)
		जाओ out;

	ret = menelaus_पढ़ो_reg(MENELAUS_MCT_CTRL3);
	अगर (ret < 0)
		जाओ out;
	val = ret;
	अगर (slot == 1) अणु
		अगर (enable)
			val |= MCT_CTRL3_SLOT1_EN;
		अन्यथा
			val &= ~MCT_CTRL3_SLOT1_EN;
	पूर्ण अन्यथा अणु
		पूर्णांक b;

		अगर (enable)
			val |= MCT_CTRL3_SLOT2_EN;
		अन्यथा
			val &= ~MCT_CTRL3_SLOT2_EN;
		b = menelaus_पढ़ो_reg(MENELAUS_MCT_CTRL2);
		b &= ~(MCT_CTRL2_VS2_SEL_D0 | MCT_CTRL2_VS2_SEL_D1);
		b |= घातer;
		ret = menelaus_ग_लिखो_reg(MENELAUS_MCT_CTRL2, b);
		अगर (ret < 0)
			जाओ out;
	पूर्ण
	/* Disable स्वतःnomous shutकरोwn */
	val &= ~(MCT_CTRL3_S1_AUTO_EN | MCT_CTRL3_S2_AUTO_EN);
	ret = menelaus_ग_लिखो_reg(MENELAUS_MCT_CTRL3, val);
out:
	mutex_unlock(&the_menelaus->lock);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(menelaus_set_mmc_slot);

पूर्णांक menelaus_रेजिस्टर_mmc_callback(व्योम (*callback)(व्योम *data, u8 card_mask),
				   व्योम *data)
अणु
	पूर्णांक ret = 0;

	the_menelaus->mmc_callback_data = data;
	the_menelaus->mmc_callback = callback;
	ret = menelaus_add_irq_work(MENELAUS_MMC_S1CD_IRQ,
				    menelaus_mmc_cd_work);
	अगर (ret < 0)
		वापस ret;
	ret = menelaus_add_irq_work(MENELAUS_MMC_S2CD_IRQ,
				    menelaus_mmc_cd_work);
	अगर (ret < 0)
		वापस ret;
	ret = menelaus_add_irq_work(MENELAUS_MMC_S1D1_IRQ,
				    menelaus_mmc_cd_work);
	अगर (ret < 0)
		वापस ret;
	ret = menelaus_add_irq_work(MENELAUS_MMC_S2D1_IRQ,
				    menelaus_mmc_cd_work);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(menelaus_रेजिस्टर_mmc_callback);

व्योम menelaus_unरेजिस्टर_mmc_callback(व्योम)
अणु
	menelaus_हटाओ_irq_work(MENELAUS_MMC_S1CD_IRQ);
	menelaus_हटाओ_irq_work(MENELAUS_MMC_S2CD_IRQ);
	menelaus_हटाओ_irq_work(MENELAUS_MMC_S1D1_IRQ);
	menelaus_हटाओ_irq_work(MENELAUS_MMC_S2D1_IRQ);

	the_menelaus->mmc_callback = शून्य;
	the_menelaus->mmc_callback_data = शून्य;
पूर्ण
EXPORT_SYMBOL(menelaus_unरेजिस्टर_mmc_callback);

काष्ठा menelaus_vtg अणु
	स्थिर अक्षर *name;
	u8 vtg_reg;
	u8 vtg_shअगरt;
	u8 vtg_bits;
	u8 mode_reg;
पूर्ण;

काष्ठा menelaus_vtg_value अणु
	u16 vtg;
	u16 val;
पूर्ण;

अटल पूर्णांक menelaus_set_voltage(स्थिर काष्ठा menelaus_vtg *vtg, पूर्णांक mV,
				पूर्णांक vtg_val, पूर्णांक mode)
अणु
	पूर्णांक val, ret;
	काष्ठा i2c_client *c = the_menelaus->client;

	mutex_lock(&the_menelaus->lock);

	ret = menelaus_पढ़ो_reg(vtg->vtg_reg);
	अगर (ret < 0)
		जाओ out;
	val = ret & ~(((1 << vtg->vtg_bits) - 1) << vtg->vtg_shअगरt);
	val |= vtg_val << vtg->vtg_shअगरt;

	dev_dbg(&c->dev, "Setting voltage '%s'"
			 "to %d mV (reg 0x%02x, val 0x%02x)\n",
			vtg->name, mV, vtg->vtg_reg, val);

	ret = menelaus_ग_लिखो_reg(vtg->vtg_reg, val);
	अगर (ret < 0)
		जाओ out;
	ret = menelaus_ग_लिखो_reg(vtg->mode_reg, mode);
out:
	mutex_unlock(&the_menelaus->lock);
	अगर (ret == 0) अणु
		/* Wait क्रम voltage to stabilize */
		msleep(1);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक menelaus_get_vtg_value(पूर्णांक vtg, स्थिर काष्ठा menelaus_vtg_value *tbl,
				  पूर्णांक n)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < n; i++, tbl++)
		अगर (tbl->vtg == vtg)
			वापस tbl->val;
	वापस -EINVAL;
पूर्ण

/*
 * Vcore can be programmed in two ways:
 * SW-controlled: Required voltage is programmed पूर्णांकo VCORE_CTRL1
 * HW-controlled: Required range (roof-न्यूनमान) is programmed पूर्णांकo VCORE_CTRL3
 * and VCORE_CTRL4
 *
 * Call correct 'set' function accordingly
 */

अटल स्थिर काष्ठा menelaus_vtg_value vcore_values[] = अणु
	अणु 1000, 0 पूर्ण,
	अणु 1025, 1 पूर्ण,
	अणु 1050, 2 पूर्ण,
	अणु 1075, 3 पूर्ण,
	अणु 1100, 4 पूर्ण,
	अणु 1125, 5 पूर्ण,
	अणु 1150, 6 पूर्ण,
	अणु 1175, 7 पूर्ण,
	अणु 1200, 8 पूर्ण,
	अणु 1225, 9 पूर्ण,
	अणु 1250, 10 पूर्ण,
	अणु 1275, 11 पूर्ण,
	अणु 1300, 12 पूर्ण,
	अणु 1325, 13 पूर्ण,
	अणु 1350, 14 पूर्ण,
	अणु 1375, 15 पूर्ण,
	अणु 1400, 16 पूर्ण,
	अणु 1425, 17 पूर्ण,
	अणु 1450, 18 पूर्ण,
पूर्ण;

पूर्णांक menelaus_set_vcore_hw(अचिन्हित पूर्णांक roof_mV, अचिन्हित पूर्णांक न्यूनमान_mV)
अणु
	पूर्णांक fval, rval, val, ret;
	काष्ठा i2c_client *c = the_menelaus->client;

	rval = menelaus_get_vtg_value(roof_mV, vcore_values,
				      ARRAY_SIZE(vcore_values));
	अगर (rval < 0)
		वापस -EINVAL;
	fval = menelaus_get_vtg_value(न्यूनमान_mV, vcore_values,
				      ARRAY_SIZE(vcore_values));
	अगर (fval < 0)
		वापस -EINVAL;

	dev_dbg(&c->dev, "Setting VCORE FLOOR to %d mV and ROOF to %d mV\n",
	       न्यूनमान_mV, roof_mV);

	mutex_lock(&the_menelaus->lock);
	ret = menelaus_ग_लिखो_reg(MENELAUS_VCORE_CTRL3, fval);
	अगर (ret < 0)
		जाओ out;
	ret = menelaus_ग_लिखो_reg(MENELAUS_VCORE_CTRL4, rval);
	अगर (ret < 0)
		जाओ out;
	अगर (!the_menelaus->vcore_hw_mode) अणु
		val = menelaus_पढ़ो_reg(MENELAUS_VCORE_CTRL1);
		/* HW mode, turn OFF byte comparator */
		val |= (VCORE_CTRL1_HW_NSW | VCORE_CTRL1_BYP_COMP);
		ret = menelaus_ग_लिखो_reg(MENELAUS_VCORE_CTRL1, val);
		the_menelaus->vcore_hw_mode = 1;
	पूर्ण
	msleep(1);
out:
	mutex_unlock(&the_menelaus->lock);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा menelaus_vtg vmem_vtg = अणु
	.name = "VMEM",
	.vtg_reg = MENELAUS_LDO_CTRL1,
	.vtg_shअगरt = 0,
	.vtg_bits = 2,
	.mode_reg = MENELAUS_LDO_CTRL3,
पूर्ण;

अटल स्थिर काष्ठा menelaus_vtg_value vmem_values[] = अणु
	अणु 1500, 0 पूर्ण,
	अणु 1800, 1 पूर्ण,
	अणु 1900, 2 पूर्ण,
	अणु 2500, 3 पूर्ण,
पूर्ण;

पूर्णांक menelaus_set_vmem(अचिन्हित पूर्णांक mV)
अणु
	पूर्णांक val;

	अगर (mV == 0)
		वापस menelaus_set_voltage(&vmem_vtg, 0, 0, 0);

	val = menelaus_get_vtg_value(mV, vmem_values, ARRAY_SIZE(vmem_values));
	अगर (val < 0)
		वापस -EINVAL;
	वापस menelaus_set_voltage(&vmem_vtg, mV, val, 0x02);
पूर्ण
EXPORT_SYMBOL(menelaus_set_vmem);

अटल स्थिर काष्ठा menelaus_vtg vio_vtg = अणु
	.name = "VIO",
	.vtg_reg = MENELAUS_LDO_CTRL1,
	.vtg_shअगरt = 2,
	.vtg_bits = 2,
	.mode_reg = MENELAUS_LDO_CTRL4,
पूर्ण;

अटल स्थिर काष्ठा menelaus_vtg_value vio_values[] = अणु
	अणु 1500, 0 पूर्ण,
	अणु 1800, 1 पूर्ण,
	अणु 2500, 2 पूर्ण,
	अणु 2800, 3 पूर्ण,
पूर्ण;

पूर्णांक menelaus_set_vio(अचिन्हित पूर्णांक mV)
अणु
	पूर्णांक val;

	अगर (mV == 0)
		वापस menelaus_set_voltage(&vio_vtg, 0, 0, 0);

	val = menelaus_get_vtg_value(mV, vio_values, ARRAY_SIZE(vio_values));
	अगर (val < 0)
		वापस -EINVAL;
	वापस menelaus_set_voltage(&vio_vtg, mV, val, 0x02);
पूर्ण
EXPORT_SYMBOL(menelaus_set_vio);

अटल स्थिर काष्ठा menelaus_vtg_value vdcdc_values[] = अणु
	अणु 1500, 0 पूर्ण,
	अणु 1800, 1 पूर्ण,
	अणु 2000, 2 पूर्ण,
	अणु 2200, 3 पूर्ण,
	अणु 2400, 4 पूर्ण,
	अणु 2800, 5 पूर्ण,
	अणु 3000, 6 पूर्ण,
	अणु 3300, 7 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा menelaus_vtg vdcdc2_vtg = अणु
	.name = "VDCDC2",
	.vtg_reg = MENELAUS_DCDC_CTRL1,
	.vtg_shअगरt = 0,
	.vtg_bits = 3,
	.mode_reg = MENELAUS_DCDC_CTRL2,
पूर्ण;

अटल स्थिर काष्ठा menelaus_vtg vdcdc3_vtg = अणु
	.name = "VDCDC3",
	.vtg_reg = MENELAUS_DCDC_CTRL1,
	.vtg_shअगरt = 3,
	.vtg_bits = 3,
	.mode_reg = MENELAUS_DCDC_CTRL3,
पूर्ण;

पूर्णांक menelaus_set_vdcdc(पूर्णांक dcdc, अचिन्हित पूर्णांक mV)
अणु
	स्थिर काष्ठा menelaus_vtg *vtg;
	पूर्णांक val;

	अगर (dcdc != 2 && dcdc != 3)
		वापस -EINVAL;
	अगर (dcdc == 2)
		vtg = &vdcdc2_vtg;
	अन्यथा
		vtg = &vdcdc3_vtg;

	अगर (mV == 0)
		वापस menelaus_set_voltage(vtg, 0, 0, 0);

	val = menelaus_get_vtg_value(mV, vdcdc_values,
				     ARRAY_SIZE(vdcdc_values));
	अगर (val < 0)
		वापस -EINVAL;
	वापस menelaus_set_voltage(vtg, mV, val, 0x03);
पूर्ण

अटल स्थिर काष्ठा menelaus_vtg_value vmmc_values[] = अणु
	अणु 1850, 0 पूर्ण,
	अणु 2800, 1 पूर्ण,
	अणु 3000, 2 पूर्ण,
	अणु 3100, 3 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा menelaus_vtg vmmc_vtg = अणु
	.name = "VMMC",
	.vtg_reg = MENELAUS_LDO_CTRL1,
	.vtg_shअगरt = 6,
	.vtg_bits = 2,
	.mode_reg = MENELAUS_LDO_CTRL7,
पूर्ण;

पूर्णांक menelaus_set_vmmc(अचिन्हित पूर्णांक mV)
अणु
	पूर्णांक val;

	अगर (mV == 0)
		वापस menelaus_set_voltage(&vmmc_vtg, 0, 0, 0);

	val = menelaus_get_vtg_value(mV, vmmc_values, ARRAY_SIZE(vmmc_values));
	अगर (val < 0)
		वापस -EINVAL;
	वापस menelaus_set_voltage(&vmmc_vtg, mV, val, 0x02);
पूर्ण
EXPORT_SYMBOL(menelaus_set_vmmc);


अटल स्थिर काष्ठा menelaus_vtg_value vaux_values[] = अणु
	अणु 1500, 0 पूर्ण,
	अणु 1800, 1 पूर्ण,
	अणु 2500, 2 पूर्ण,
	अणु 2800, 3 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा menelaus_vtg vaux_vtg = अणु
	.name = "VAUX",
	.vtg_reg = MENELAUS_LDO_CTRL1,
	.vtg_shअगरt = 4,
	.vtg_bits = 2,
	.mode_reg = MENELAUS_LDO_CTRL6,
पूर्ण;

पूर्णांक menelaus_set_vaux(अचिन्हित पूर्णांक mV)
अणु
	पूर्णांक val;

	अगर (mV == 0)
		वापस menelaus_set_voltage(&vaux_vtg, 0, 0, 0);

	val = menelaus_get_vtg_value(mV, vaux_values, ARRAY_SIZE(vaux_values));
	अगर (val < 0)
		वापस -EINVAL;
	वापस menelaus_set_voltage(&vaux_vtg, mV, val, 0x02);
पूर्ण
EXPORT_SYMBOL(menelaus_set_vaux);

पूर्णांक menelaus_get_slot_pin_states(व्योम)
अणु
	वापस menelaus_पढ़ो_reg(MENELAUS_MCT_PIN_ST);
पूर्ण
EXPORT_SYMBOL(menelaus_get_slot_pin_states);

पूर्णांक menelaus_set_regulator_sleep(पूर्णांक enable, u32 val)
अणु
	पूर्णांक t, ret;
	काष्ठा i2c_client *c = the_menelaus->client;

	mutex_lock(&the_menelaus->lock);
	ret = menelaus_ग_लिखो_reg(MENELAUS_SLEEP_CTRL2, val);
	अगर (ret < 0)
		जाओ out;

	dev_dbg(&c->dev, "regulator sleep configuration: %02x\n", val);

	ret = menelaus_पढ़ो_reg(MENELAUS_GPIO_CTRL);
	अगर (ret < 0)
		जाओ out;
	t = (GPIO_CTRL_SLPCTLEN | GPIO3_सूची_INPUT);
	अगर (enable)
		ret |= t;
	अन्यथा
		ret &= ~t;
	ret = menelaus_ग_लिखो_reg(MENELAUS_GPIO_CTRL, ret);
out:
	mutex_unlock(&the_menelaus->lock);
	वापस ret;
पूर्ण

/*-----------------------------------------------------------------------*/

/* Handles Menelaus पूर्णांकerrupts. Does not run in पूर्णांकerrupt context */
अटल व्योम menelaus_work(काष्ठा work_काष्ठा *_menelaus)
अणु
	काष्ठा menelaus_chip *menelaus =
			container_of(_menelaus, काष्ठा menelaus_chip, work);
	व्योम (*handler)(काष्ठा menelaus_chip *menelaus);

	जबतक (1) अणु
		अचिन्हित isr;

		isr = (menelaus_पढ़ो_reg(MENELAUS_INT_STATUS2)
				& ~menelaus->mask2) << 8;
		isr |= menelaus_पढ़ो_reg(MENELAUS_INT_STATUS1)
				& ~menelaus->mask1;
		अगर (!isr)
			अवरोध;

		जबतक (isr) अणु
			पूर्णांक irq = fls(isr) - 1;
			isr &= ~(1 << irq);

			mutex_lock(&menelaus->lock);
			menelaus_disable_irq(irq);
			menelaus_ack_irq(irq);
			handler = menelaus->handlers[irq];
			अगर (handler)
				handler(menelaus);
			menelaus_enable_irq(irq);
			mutex_unlock(&menelaus->lock);
		पूर्ण
	पूर्ण
	enable_irq(menelaus->client->irq);
पूर्ण

/*
 * We cannot use I2C in पूर्णांकerrupt context, so we just schedule work.
 */
अटल irqवापस_t menelaus_irq(पूर्णांक irq, व्योम *_menelaus)
अणु
	काष्ठा menelaus_chip *menelaus = _menelaus;

	disable_irq_nosync(irq);
	(व्योम)schedule_work(&menelaus->work);

	वापस IRQ_HANDLED;
पूर्ण

/*-----------------------------------------------------------------------*/

/*
 * The RTC needs to be set once, then it runs on backup battery घातer.
 * It supports alarms, including प्रणाली wake alarms (from some modes);
 * and 1/second IRQs अगर requested.
 */
#अगर_घोषित CONFIG_RTC_DRV_TWL92330

#घोषणा RTC_CTRL_RTC_EN		(1 << 0)
#घोषणा RTC_CTRL_AL_EN		(1 << 1)
#घोषणा RTC_CTRL_MODE12		(1 << 2)
#घोषणा RTC_CTRL_EVERY_MASK	(3 << 3)
#घोषणा RTC_CTRL_EVERY_SEC	(0 << 3)
#घोषणा RTC_CTRL_EVERY_MIN	(1 << 3)
#घोषणा RTC_CTRL_EVERY_HR	(2 << 3)
#घोषणा RTC_CTRL_EVERY_DAY	(3 << 3)

#घोषणा RTC_UPDATE_EVERY	0x08

#घोषणा RTC_HR_PM		(1 << 7)

अटल व्योम menelaus_to_समय(अक्षर *regs, काष्ठा rtc_समय *t)
अणु
	t->पंचांग_sec = bcd2bin(regs[0]);
	t->पंचांग_min = bcd2bin(regs[1]);
	अगर (the_menelaus->rtc_control & RTC_CTRL_MODE12) अणु
		t->पंचांग_hour = bcd2bin(regs[2] & 0x1f) - 1;
		अगर (regs[2] & RTC_HR_PM)
			t->पंचांग_hour += 12;
	पूर्ण अन्यथा
		t->पंचांग_hour = bcd2bin(regs[2] & 0x3f);
	t->पंचांग_mday = bcd2bin(regs[3]);
	t->पंचांग_mon = bcd2bin(regs[4]) - 1;
	t->पंचांग_year = bcd2bin(regs[5]) + 100;
पूर्ण

अटल पूर्णांक समय_प्रकारo_menelaus(काष्ठा rtc_समय *t, पूर्णांक regnum)
अणु
	पूर्णांक	hour, status;

	status = menelaus_ग_लिखो_reg(regnum++, bin2bcd(t->पंचांग_sec));
	अगर (status < 0)
		जाओ fail;

	status = menelaus_ग_लिखो_reg(regnum++, bin2bcd(t->पंचांग_min));
	अगर (status < 0)
		जाओ fail;

	अगर (the_menelaus->rtc_control & RTC_CTRL_MODE12) अणु
		hour = t->पंचांग_hour + 1;
		अगर (hour > 12)
			hour = RTC_HR_PM | bin2bcd(hour - 12);
		अन्यथा
			hour = bin2bcd(hour);
	पूर्ण अन्यथा
		hour = bin2bcd(t->पंचांग_hour);
	status = menelaus_ग_लिखो_reg(regnum++, hour);
	अगर (status < 0)
		जाओ fail;

	status = menelaus_ग_लिखो_reg(regnum++, bin2bcd(t->पंचांग_mday));
	अगर (status < 0)
		जाओ fail;

	status = menelaus_ग_लिखो_reg(regnum++, bin2bcd(t->पंचांग_mon + 1));
	अगर (status < 0)
		जाओ fail;

	status = menelaus_ग_लिखो_reg(regnum++, bin2bcd(t->पंचांग_year - 100));
	अगर (status < 0)
		जाओ fail;

	वापस 0;
fail:
	dev_err(&the_menelaus->client->dev, "rtc write reg %02x, err %d\n",
			--regnum, status);
	वापस status;
पूर्ण

अटल पूर्णांक menelaus_पढ़ो_समय(काष्ठा device *dev, काष्ठा rtc_समय *t)
अणु
	काष्ठा i2c_msg	msg[2];
	अक्षर		regs[7];
	पूर्णांक		status;

	/* block पढ़ो date and समय रेजिस्टरs */
	regs[0] = MENELAUS_RTC_SEC;

	msg[0].addr = MENELAUS_I2C_ADDRESS;
	msg[0].flags = 0;
	msg[0].len = 1;
	msg[0].buf = regs;

	msg[1].addr = MENELAUS_I2C_ADDRESS;
	msg[1].flags = I2C_M_RD;
	msg[1].len = माप(regs);
	msg[1].buf = regs;

	status = i2c_transfer(the_menelaus->client->adapter, msg, 2);
	अगर (status != 2) अणु
		dev_err(dev, "%s error %d\n", "read", status);
		वापस -EIO;
	पूर्ण

	menelaus_to_समय(regs, t);
	t->पंचांग_wday = bcd2bin(regs[6]);

	वापस 0;
पूर्ण

अटल पूर्णांक menelaus_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *t)
अणु
	पूर्णांक		status;

	/* ग_लिखो date and समय रेजिस्टरs */
	status = समय_प्रकारo_menelaus(t, MENELAUS_RTC_SEC);
	अगर (status < 0)
		वापस status;
	status = menelaus_ग_लिखो_reg(MENELAUS_RTC_WKDAY, bin2bcd(t->पंचांग_wday));
	अगर (status < 0) अणु
		dev_err(&the_menelaus->client->dev, "rtc write reg %02x "
				"err %d\n", MENELAUS_RTC_WKDAY, status);
		वापस status;
	पूर्ण

	/* now commit the ग_लिखो */
	status = menelaus_ग_लिखो_reg(MENELAUS_RTC_UPDATE, RTC_UPDATE_EVERY);
	अगर (status < 0)
		dev_err(&the_menelaus->client->dev, "rtc commit time, err %d\n",
				status);

	वापस 0;
पूर्ण

अटल पूर्णांक menelaus_पढ़ो_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *w)
अणु
	काष्ठा i2c_msg	msg[2];
	अक्षर		regs[6];
	पूर्णांक		status;

	/* block पढ़ो alarm रेजिस्टरs */
	regs[0] = MENELAUS_RTC_AL_SEC;

	msg[0].addr = MENELAUS_I2C_ADDRESS;
	msg[0].flags = 0;
	msg[0].len = 1;
	msg[0].buf = regs;

	msg[1].addr = MENELAUS_I2C_ADDRESS;
	msg[1].flags = I2C_M_RD;
	msg[1].len = माप(regs);
	msg[1].buf = regs;

	status = i2c_transfer(the_menelaus->client->adapter, msg, 2);
	अगर (status != 2) अणु
		dev_err(dev, "%s error %d\n", "alarm read", status);
		वापस -EIO;
	पूर्ण

	menelaus_to_समय(regs, &w->समय);

	w->enabled = !!(the_menelaus->rtc_control & RTC_CTRL_AL_EN);

	/* NOTE we *could* check अगर actually pending... */
	w->pending = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक menelaus_set_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *w)
अणु
	पूर्णांक		status;

	अगर (the_menelaus->client->irq <= 0 && w->enabled)
		वापस -ENODEV;

	/* clear previous alarm enable */
	अगर (the_menelaus->rtc_control & RTC_CTRL_AL_EN) अणु
		the_menelaus->rtc_control &= ~RTC_CTRL_AL_EN;
		status = menelaus_ग_लिखो_reg(MENELAUS_RTC_CTRL,
				the_menelaus->rtc_control);
		अगर (status < 0)
			वापस status;
	पूर्ण

	/* ग_लिखो alarm रेजिस्टरs */
	status = समय_प्रकारo_menelaus(&w->समय, MENELAUS_RTC_AL_SEC);
	अगर (status < 0)
		वापस status;

	/* enable alarm अगर requested */
	अगर (w->enabled) अणु
		the_menelaus->rtc_control |= RTC_CTRL_AL_EN;
		status = menelaus_ग_लिखो_reg(MENELAUS_RTC_CTRL,
				the_menelaus->rtc_control);
	पूर्ण

	वापस status;
पूर्ण

#अगर_घोषित CONFIG_RTC_INTF_DEV

अटल व्योम menelaus_rtc_update_work(काष्ठा menelaus_chip *m)
अणु
	/* report 1/sec update */
	rtc_update_irq(m->rtc, 1, RTC_IRQF | RTC_UF);
पूर्ण

अटल पूर्णांक menelaus_ioctl(काष्ठा device *dev, अचिन्हित cmd, अचिन्हित दीर्घ arg)
अणु
	पूर्णांक	status;

	अगर (the_menelaus->client->irq <= 0)
		वापस -ENOIOCTLCMD;

	चयन (cmd) अणु
	/* alarm IRQ */
	हाल RTC_AIE_ON:
		अगर (the_menelaus->rtc_control & RTC_CTRL_AL_EN)
			वापस 0;
		the_menelaus->rtc_control |= RTC_CTRL_AL_EN;
		अवरोध;
	हाल RTC_AIE_OFF:
		अगर (!(the_menelaus->rtc_control & RTC_CTRL_AL_EN))
			वापस 0;
		the_menelaus->rtc_control &= ~RTC_CTRL_AL_EN;
		अवरोध;
	/* 1/second "update" IRQ */
	हाल RTC_UIE_ON:
		अगर (the_menelaus->uie)
			वापस 0;
		status = menelaus_हटाओ_irq_work(MENELAUS_RTCTMR_IRQ);
		status = menelaus_add_irq_work(MENELAUS_RTCTMR_IRQ,
				menelaus_rtc_update_work);
		अगर (status == 0)
			the_menelaus->uie = 1;
		वापस status;
	हाल RTC_UIE_OFF:
		अगर (!the_menelaus->uie)
			वापस 0;
		status = menelaus_हटाओ_irq_work(MENELAUS_RTCTMR_IRQ);
		अगर (status == 0)
			the_menelaus->uie = 0;
		वापस status;
	शेष:
		वापस -ENOIOCTLCMD;
	पूर्ण
	वापस menelaus_ग_लिखो_reg(MENELAUS_RTC_CTRL, the_menelaus->rtc_control);
पूर्ण

#अन्यथा
#घोषणा menelaus_ioctl	शून्य
#पूर्ण_अगर

/* REVISIT no compensation रेजिस्टर support ... */

अटल स्थिर काष्ठा rtc_class_ops menelaus_rtc_ops = अणु
	.ioctl			= menelaus_ioctl,
	.पढ़ो_समय		= menelaus_पढ़ो_समय,
	.set_समय		= menelaus_set_समय,
	.पढ़ो_alarm		= menelaus_पढ़ो_alarm,
	.set_alarm		= menelaus_set_alarm,
पूर्ण;

अटल व्योम menelaus_rtc_alarm_work(काष्ठा menelaus_chip *m)
अणु
	/* report alarm */
	rtc_update_irq(m->rtc, 1, RTC_IRQF | RTC_AF);

	/* then disable it; alarms are oneshot */
	the_menelaus->rtc_control &= ~RTC_CTRL_AL_EN;
	menelaus_ग_लिखो_reg(MENELAUS_RTC_CTRL, the_menelaus->rtc_control);
पूर्ण

अटल अंतरभूत व्योम menelaus_rtc_init(काष्ठा menelaus_chip *m)
अणु
	पूर्णांक	alarm = (m->client->irq > 0);
	पूर्णांक	err;

	/* assume 32KDETEN pin is pulled high */
	अगर (!(menelaus_पढ़ो_reg(MENELAUS_OSC_CTRL) & 0x80)) अणु
		dev_dbg(&m->client->dev, "no 32k oscillator\n");
		वापस;
	पूर्ण

	m->rtc = devm_rtc_allocate_device(&m->client->dev);
	अगर (IS_ERR(m->rtc))
		वापस;

	m->rtc->ops = &menelaus_rtc_ops;

	/* support RTC alarm; it can issue wakeups */
	अगर (alarm) अणु
		अगर (menelaus_add_irq_work(MENELAUS_RTCALM_IRQ,
				menelaus_rtc_alarm_work) < 0) अणु
			dev_err(&m->client->dev, "can't handle RTC alarm\n");
			वापस;
		पूर्ण
		device_init_wakeup(&m->client->dev, 1);
	पूर्ण

	/* be sure RTC is enabled; allow 1/sec irqs; leave 12hr mode alone */
	m->rtc_control = menelaus_पढ़ो_reg(MENELAUS_RTC_CTRL);
	अगर (!(m->rtc_control & RTC_CTRL_RTC_EN)
			|| (m->rtc_control & RTC_CTRL_AL_EN)
			|| (m->rtc_control & RTC_CTRL_EVERY_MASK)) अणु
		अगर (!(m->rtc_control & RTC_CTRL_RTC_EN)) अणु
			dev_warn(&m->client->dev, "rtc clock needs setting\n");
			m->rtc_control |= RTC_CTRL_RTC_EN;
		पूर्ण
		m->rtc_control &= ~RTC_CTRL_EVERY_MASK;
		m->rtc_control &= ~RTC_CTRL_AL_EN;
		menelaus_ग_लिखो_reg(MENELAUS_RTC_CTRL, m->rtc_control);
	पूर्ण

	err = devm_rtc_रेजिस्टर_device(m->rtc);
	अगर (err) अणु
		अगर (alarm) अणु
			menelaus_हटाओ_irq_work(MENELAUS_RTCALM_IRQ);
			device_init_wakeup(&m->client->dev, 0);
		पूर्ण
		the_menelaus->rtc = शून्य;
	पूर्ण
पूर्ण

#अन्यथा

अटल अंतरभूत व्योम menelaus_rtc_init(काष्ठा menelaus_chip *m)
अणु
	/* nothing */
पूर्ण

#पूर्ण_अगर

/*-----------------------------------------------------------------------*/

अटल काष्ठा i2c_driver menelaus_i2c_driver;

अटल पूर्णांक menelaus_probe(काष्ठा i2c_client *client,
			  स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा menelaus_chip	*menelaus;
	पूर्णांक			rev = 0;
	पूर्णांक			err = 0;
	काष्ठा menelaus_platक्रमm_data *menelaus_pdata =
					dev_get_platdata(&client->dev);

	अगर (the_menelaus) अणु
		dev_dbg(&client->dev, "only one %s for now\n",
				DRIVER_NAME);
		वापस -ENODEV;
	पूर्ण

	menelaus = devm_kzalloc(&client->dev, माप(*menelaus), GFP_KERNEL);
	अगर (!menelaus)
		वापस -ENOMEM;

	i2c_set_clientdata(client, menelaus);

	the_menelaus = menelaus;
	menelaus->client = client;

	/* If a true probe check the device */
	rev = menelaus_पढ़ो_reg(MENELAUS_REV);
	अगर (rev < 0) अणु
		pr_err(DRIVER_NAME ": device not found");
		वापस -ENODEV;
	पूर्ण

	/* Ack and disable all Menelaus पूर्णांकerrupts */
	menelaus_ग_लिखो_reg(MENELAUS_INT_ACK1, 0xff);
	menelaus_ग_लिखो_reg(MENELAUS_INT_ACK2, 0xff);
	menelaus_ग_लिखो_reg(MENELAUS_INT_MASK1, 0xff);
	menelaus_ग_लिखो_reg(MENELAUS_INT_MASK2, 0xff);
	menelaus->mask1 = 0xff;
	menelaus->mask2 = 0xff;

	/* Set output buffer strengths */
	menelaus_ग_लिखो_reg(MENELAUS_MCT_CTRL1, 0x73);

	अगर (client->irq > 0) अणु
		err = request_irq(client->irq, menelaus_irq, 0,
				  DRIVER_NAME, menelaus);
		अगर (err) अणु
			dev_dbg(&client->dev,  "can't get IRQ %d, err %d\n",
					client->irq, err);
			वापस err;
		पूर्ण
	पूर्ण

	mutex_init(&menelaus->lock);
	INIT_WORK(&menelaus->work, menelaus_work);

	pr_info("Menelaus rev %d.%d\n", rev >> 4, rev & 0x0f);

	err = menelaus_पढ़ो_reg(MENELAUS_VCORE_CTRL1);
	अगर (err < 0)
		जाओ fail;
	अगर (err & VCORE_CTRL1_HW_NSW)
		menelaus->vcore_hw_mode = 1;
	अन्यथा
		menelaus->vcore_hw_mode = 0;

	अगर (menelaus_pdata != शून्य && menelaus_pdata->late_init != शून्य) अणु
		err = menelaus_pdata->late_init(&client->dev);
		अगर (err < 0)
			जाओ fail;
	पूर्ण

	menelaus_rtc_init(menelaus);

	वापस 0;
fail:
	मुक्त_irq(client->irq, menelaus);
	flush_work(&menelaus->work);
	वापस err;
पूर्ण

अटल पूर्णांक menelaus_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा menelaus_chip	*menelaus = i2c_get_clientdata(client);

	मुक्त_irq(client->irq, menelaus);
	flush_work(&menelaus->work);
	the_menelaus = शून्य;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id menelaus_id[] = अणु
	अणु "menelaus", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, menelaus_id);

अटल काष्ठा i2c_driver menelaus_i2c_driver = अणु
	.driver = अणु
		.name		= DRIVER_NAME,
	पूर्ण,
	.probe		= menelaus_probe,
	.हटाओ		= menelaus_हटाओ,
	.id_table	= menelaus_id,
पूर्ण;

module_i2c_driver(menelaus_i2c_driver);

MODULE_AUTHOR("Texas Instruments, Inc. (and others)");
MODULE_DESCRIPTION("I2C interface for Menelaus.");
MODULE_LICENSE("GPL");
