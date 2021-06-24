<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * TWL4030/TPS65950 BCI (Battery Charger Interface) driver
 *
 * Copyright (C) 2010 Graधठvydas Ignotas <notasas@gmail.com>
 *
 * based on twl4030_bci_battery.c by TI
 * Copyright (C) 2008 Texas Instruments, Inc.
 */

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/err.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mfd/twl.h>
#समावेश <linux/घातer_supply.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/usb/otg.h>
#समावेश <linux/iio/consumer.h>

#घोषणा TWL4030_BCIMDEN		0x00
#घोषणा TWL4030_BCIMDKEY	0x01
#घोषणा TWL4030_BCIMSTATEC	0x02
#घोषणा TWL4030_BCIICHG		0x08
#घोषणा TWL4030_BCIVAC		0x0a
#घोषणा TWL4030_BCIVBUS		0x0c
#घोषणा TWL4030_BCIMFSTS3	0x0F
#घोषणा TWL4030_BCIMFSTS4	0x10
#घोषणा TWL4030_BCICTL1		0x23
#घोषणा TWL4030_BB_CFG		0x12
#घोषणा TWL4030_BCIIREF1	0x27
#घोषणा TWL4030_BCIIREF2	0x28
#घोषणा TWL4030_BCIMFKEY	0x11
#घोषणा TWL4030_BCIMFEN3	0x14
#घोषणा TWL4030_BCIMFTH8	0x1d
#घोषणा TWL4030_BCIMFTH9	0x1e
#घोषणा TWL4030_BCIWDKEY	0x21

#घोषणा TWL4030_BCIMFSTS1	0x01

#घोषणा TWL4030_BCIAUTOWEN	BIT(5)
#घोषणा TWL4030_CONFIG_DONE	BIT(4)
#घोषणा TWL4030_CVENAC		BIT(2)
#घोषणा TWL4030_BCIAUTOUSB	BIT(1)
#घोषणा TWL4030_BCIAUTOAC	BIT(0)
#घोषणा TWL4030_CGAIN		BIT(5)
#घोषणा TWL4030_USBFASTMCHG	BIT(2)
#घोषणा TWL4030_STS_VBUS	BIT(7)
#घोषणा TWL4030_STS_USB_ID	BIT(2)
#घोषणा TWL4030_BBCHEN		BIT(4)
#घोषणा TWL4030_BBSEL_MASK	0x0c
#घोषणा TWL4030_BBSEL_2V5	0x00
#घोषणा TWL4030_BBSEL_3V0	0x04
#घोषणा TWL4030_BBSEL_3V1	0x08
#घोषणा TWL4030_BBSEL_3V2	0x0c
#घोषणा TWL4030_BBISEL_MASK	0x03
#घोषणा TWL4030_BBISEL_25uA	0x00
#घोषणा TWL4030_BBISEL_150uA	0x01
#घोषणा TWL4030_BBISEL_500uA	0x02
#घोषणा TWL4030_BBISEL_1000uA	0x03

#घोषणा TWL4030_BATSTSPCHG	BIT(2)
#घोषणा TWL4030_BATSTSMCHG	BIT(6)

/* BCI पूर्णांकerrupts */
#घोषणा TWL4030_WOVF		BIT(0) /* Watchकरोg overflow */
#घोषणा TWL4030_TMOVF		BIT(1) /* Timer overflow */
#घोषणा TWL4030_ICHGHIGH	BIT(2) /* Battery अक्षरge current high */
#घोषणा TWL4030_ICHGLOW		BIT(3) /* Battery cc. low / FSM state change */
#घोषणा TWL4030_ICHGEOC		BIT(4) /* Battery current end-of-अक्षरge */
#घोषणा TWL4030_TBATOR2		BIT(5) /* Battery temperature out of range 2 */
#घोषणा TWL4030_TBATOR1		BIT(6) /* Battery temperature out of range 1 */
#घोषणा TWL4030_BATSTS		BIT(7) /* Battery status */

#घोषणा TWL4030_VBATLVL		BIT(0) /* VBAT level */
#घोषणा TWL4030_VBATOV		BIT(1) /* VBAT overvoltage */
#घोषणा TWL4030_VBUSOV		BIT(2) /* VBUS overvoltage */
#घोषणा TWL4030_ACCHGOV		BIT(3) /* Ac अक्षरger overvoltage */

#घोषणा TWL4030_MSTATEC_USB		BIT(4)
#घोषणा TWL4030_MSTATEC_AC		BIT(5)
#घोषणा TWL4030_MSTATEC_MASK		0x0f
#घोषणा TWL4030_MSTATEC_QUICK1		0x02
#घोषणा TWL4030_MSTATEC_QUICK7		0x07
#घोषणा TWL4030_MSTATEC_COMPLETE1	0x0b
#घोषणा TWL4030_MSTATEC_COMPLETE4	0x0e

/*
 * If AC (Accessory Charger) voltage exceeds 4.5V (MADC 11)
 * then AC is available.
 */
अटल अंतरभूत पूर्णांक ac_available(काष्ठा iio_channel *channel_vac)
अणु
	पूर्णांक val, err;

	अगर (!channel_vac)
		वापस 0;

	err = iio_पढ़ो_channel_processed(channel_vac, &val);
	अगर (err < 0)
		वापस 0;
	वापस val > 4500;
पूर्ण

अटल bool allow_usb;
module_param(allow_usb, bool, 0644);
MODULE_PARM_DESC(allow_usb, "Allow USB charge drawing default current");

काष्ठा twl4030_bci अणु
	काष्ठा device		*dev;
	काष्ठा घातer_supply	*ac;
	काष्ठा घातer_supply	*usb;
	काष्ठा usb_phy		*transceiver;
	काष्ठा notअगरier_block	usb_nb;
	काष्ठा work_काष्ठा	work;
	पूर्णांक			irq_chg;
	पूर्णांक			irq_bci;
	पूर्णांक			usb_enabled;

	/*
	 * ichg_* and *_cur values in uA. If any are 'large', we set
	 * CGAIN to '1' which द्विगुनs the range क्रम half the
	 * precision.
	 */
	अचिन्हित पूर्णांक		ichg_eoc, ichg_lo, ichg_hi;
	अचिन्हित पूर्णांक		usb_cur, ac_cur;
	काष्ठा iio_channel	*channel_vac;
	bool			ac_is_active;
	पूर्णांक			usb_mode, ac_mode; /* अक्षरging mode requested */
#घोषणा	CHARGE_OFF	0
#घोषणा	CHARGE_AUTO	1
#घोषणा	CHARGE_LINEAR	2

	/* When setting the USB current we slowly increase the
	 * requested current until target is reached or the voltage
	 * drops below 4.75V.  In the latter हाल we step back one
	 * step.
	 */
	अचिन्हित पूर्णांक		usb_cur_target;
	काष्ठा delayed_work	current_worker;
#घोषणा	USB_CUR_STEP	20000	/* 20mA at a समय */
#घोषणा	USB_MIN_VOLT	4750000	/* 4.75V */
#घोषणा	USB_CUR_DELAY	msecs_to_jअगरfies(100)
#घोषणा	USB_MAX_CURRENT	1700000 /* TWL4030 caps at 1.7A */

	अचिन्हित दीर्घ		event;
पूर्ण;

/* strings क्रम 'usb_mode' values */
अटल स्थिर अक्षर *modes[] = अणु "off", "auto", "continuous" पूर्ण;

/*
 * clear and set bits on an given रेजिस्टर on a given module
 */
अटल पूर्णांक twl4030_clear_set(u8 mod_no, u8 clear, u8 set, u8 reg)
अणु
	u8 val = 0;
	पूर्णांक ret;

	ret = twl_i2c_पढ़ो_u8(mod_no, &val, reg);
	अगर (ret)
		वापस ret;

	val &= ~clear;
	val |= set;

	वापस twl_i2c_ग_लिखो_u8(mod_no, val, reg);
पूर्ण

अटल पूर्णांक twl4030_bci_पढ़ो(u8 reg, u8 *val)
अणु
	वापस twl_i2c_पढ़ो_u8(TWL_MODULE_MAIN_CHARGE, val, reg);
पूर्ण

अटल पूर्णांक twl4030_clear_set_boot_bci(u8 clear, u8 set)
अणु
	वापस twl4030_clear_set(TWL_MODULE_PM_MASTER, clear,
			TWL4030_CONFIG_DONE | TWL4030_BCIAUTOWEN | set,
			TWL4030_PM_MASTER_BOOT_BCI);
पूर्ण

अटल पूर्णांक twl4030bci_पढ़ो_adc_val(u8 reg)
अणु
	पूर्णांक ret, temp;
	u8 val;

	/* पढ़ो MSB */
	ret = twl4030_bci_पढ़ो(reg + 1, &val);
	अगर (ret)
		वापस ret;

	temp = (पूर्णांक)(val & 0x03) << 8;

	/* पढ़ो LSB */
	ret = twl4030_bci_पढ़ो(reg, &val);
	अगर (ret)
		वापस ret;

	वापस temp | val;
पूर्ण

/*
 * TI provided क्रमmulas:
 * CGAIN == 0: ICHG = (BCIICHG * 1.7) / (2^10 - 1) - 0.85
 * CGAIN == 1: ICHG = (BCIICHG * 3.4) / (2^10 - 1) - 1.7
 * Here we use पूर्णांकeger approximation of:
 * CGAIN == 0: val * 1.6618 - 0.85 * 1000
 * CGAIN == 1: (val * 1.6618 - 0.85 * 1000) * 2
 */
/*
 * convert twl रेजिस्टर value क्रम currents पूर्णांकo uA
 */
अटल पूर्णांक regval2ua(पूर्णांक regval, bool cgain)
अणु
	अगर (cgain)
		वापस (regval * 16618 - 8500 * 1000) / 5;
	अन्यथा
		वापस (regval * 16618 - 8500 * 1000) / 10;
पूर्ण

/*
 * convert uA currents पूर्णांकo twl रेजिस्टर value
 */
अटल पूर्णांक ua2regval(पूर्णांक ua, bool cgain)
अणु
	पूर्णांक ret;
	अगर (cgain)
		ua /= 2;
	ret = (ua * 10 + 8500 * 1000) / 16618;
	/* rounding problems */
	अगर (ret < 512)
		ret = 512;
	वापस ret;
पूर्ण

अटल पूर्णांक twl4030_अक्षरger_update_current(काष्ठा twl4030_bci *bci)
अणु
	पूर्णांक status;
	पूर्णांक cur;
	अचिन्हित reg, cur_reg;
	u8 bcictl1, oldreg, fullreg;
	bool cgain = false;
	u8 boot_bci;

	/*
	 * If AC (Accessory Charger) voltage exceeds 4.5V (MADC 11)
	 * and AC is enabled, set current क्रम 'ac'
	 */
	अगर (ac_available(bci->channel_vac)) अणु
		cur = bci->ac_cur;
		bci->ac_is_active = true;
	पूर्ण अन्यथा अणु
		cur = bci->usb_cur;
		bci->ac_is_active = false;
		अगर (cur > bci->usb_cur_target) अणु
			cur = bci->usb_cur_target;
			bci->usb_cur = cur;
		पूर्ण
		अगर (cur < bci->usb_cur_target)
			schedule_delayed_work(&bci->current_worker, USB_CUR_DELAY);
	पूर्ण

	/* First, check thresholds and see अगर cgain is needed */
	अगर (bci->ichg_eoc >= 200000)
		cgain = true;
	अगर (bci->ichg_lo >= 400000)
		cgain = true;
	अगर (bci->ichg_hi >= 820000)
		cgain = true;
	अगर (cur > 852000)
		cgain = true;

	status = twl4030_bci_पढ़ो(TWL4030_BCICTL1, &bcictl1);
	अगर (status < 0)
		वापस status;
	अगर (twl_i2c_पढ़ो_u8(TWL_MODULE_PM_MASTER, &boot_bci,
			    TWL4030_PM_MASTER_BOOT_BCI) < 0)
		boot_bci = 0;
	boot_bci &= 7;

	अगर ((!!cgain) != !!(bcictl1 & TWL4030_CGAIN))
		/* Need to turn क्रम अक्षरging जबतक we change the
		 * CGAIN bit.  Leave it off जबतक everything is
		 * updated.
		 */
		twl4030_clear_set_boot_bci(boot_bci, 0);

	/*
	 * For ichg_eoc, the hardware only supports reg values matching
	 * 100XXXX000, and requires the XXXX be stored in the high nibble
	 * of TWL4030_BCIMFTH8.
	 */
	reg = ua2regval(bci->ichg_eoc, cgain);
	अगर (reg > 0x278)
		reg = 0x278;
	अगर (reg < 0x200)
		reg = 0x200;
	reg = (reg >> 3) & 0xf;
	fullreg = reg << 4;

	/*
	 * For ichg_lo, reg value must match 10XXXX0000.
	 * XXXX is stored in low nibble of TWL4030_BCIMFTH8.
	 */
	reg = ua2regval(bci->ichg_lo, cgain);
	अगर (reg > 0x2F0)
		reg = 0x2F0;
	अगर (reg < 0x200)
		reg = 0x200;
	reg = (reg >> 4) & 0xf;
	fullreg |= reg;

	/* ichg_eoc and ichg_lo live in same रेजिस्टर */
	status = twl4030_bci_पढ़ो(TWL4030_BCIMFTH8, &oldreg);
	अगर (status < 0)
		वापस status;
	अगर (oldreg != fullreg) अणु
		status = twl_i2c_ग_लिखो_u8(TWL_MODULE_MAIN_CHARGE, 0xF4,
					  TWL4030_BCIMFKEY);
		अगर (status < 0)
			वापस status;
		twl_i2c_ग_लिखो_u8(TWL_MODULE_MAIN_CHARGE,
				 fullreg, TWL4030_BCIMFTH8);
	पूर्ण

	/* ichg_hi threshold must be 1XXXX01100 (I think) */
	reg = ua2regval(bci->ichg_hi, cgain);
	अगर (reg > 0x3E0)
		reg = 0x3E0;
	अगर (reg < 0x200)
		reg = 0x200;
	fullreg = (reg >> 5) & 0xF;
	fullreg <<= 4;
	status = twl4030_bci_पढ़ो(TWL4030_BCIMFTH9, &oldreg);
	अगर (status < 0)
		वापस status;
	अगर ((oldreg & 0xF0) != fullreg) अणु
		fullreg |= (oldreg & 0x0F);
		status = twl_i2c_ग_लिखो_u8(TWL_MODULE_MAIN_CHARGE, 0xE7,
					  TWL4030_BCIMFKEY);
		अगर (status < 0)
			वापस status;
		twl_i2c_ग_लिखो_u8(TWL_MODULE_MAIN_CHARGE,
				 fullreg, TWL4030_BCIMFTH9);
	पूर्ण

	/*
	 * And finally, set the current.  This is stored in
	 * two रेजिस्टरs.
	 */
	reg = ua2regval(cur, cgain);
	/* we have only 10 bits */
	अगर (reg > 0x3ff)
		reg = 0x3ff;
	status = twl4030_bci_पढ़ो(TWL4030_BCIIREF1, &oldreg);
	अगर (status < 0)
		वापस status;
	cur_reg = oldreg;
	status = twl4030_bci_पढ़ो(TWL4030_BCIIREF2, &oldreg);
	अगर (status < 0)
		वापस status;
	cur_reg |= oldreg << 8;
	अगर (reg != oldreg) अणु
		/* disable ग_लिखो protection क्रम one ग_लिखो access क्रम
		 * BCIIREF */
		status = twl_i2c_ग_लिखो_u8(TWL_MODULE_MAIN_CHARGE, 0xE7,
					  TWL4030_BCIMFKEY);
		अगर (status < 0)
			वापस status;
		status = twl_i2c_ग_लिखो_u8(TWL_MODULE_MAIN_CHARGE,
					  (reg & 0x100) ? 3 : 2,
					  TWL4030_BCIIREF2);
		अगर (status < 0)
			वापस status;
		/* disable ग_लिखो protection क्रम one ग_लिखो access क्रम
		 * BCIIREF */
		status = twl_i2c_ग_लिखो_u8(TWL_MODULE_MAIN_CHARGE, 0xE7,
					  TWL4030_BCIMFKEY);
		अगर (status < 0)
			वापस status;
		status = twl_i2c_ग_लिखो_u8(TWL_MODULE_MAIN_CHARGE,
					  reg & 0xff,
					  TWL4030_BCIIREF1);
	पूर्ण
	अगर ((!!cgain) != !!(bcictl1 & TWL4030_CGAIN)) अणु
		/* Flip CGAIN and re-enable अक्षरging */
		bcictl1 ^= TWL4030_CGAIN;
		twl_i2c_ग_लिखो_u8(TWL_MODULE_MAIN_CHARGE,
				 bcictl1, TWL4030_BCICTL1);
		twl4030_clear_set_boot_bci(0, boot_bci);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक twl4030_अक्षरger_get_current(व्योम);

अटल व्योम twl4030_current_worker(काष्ठा work_काष्ठा *data)
अणु
	पूर्णांक v, curr;
	पूर्णांक res;
	काष्ठा twl4030_bci *bci = container_of(data, काष्ठा twl4030_bci,
					       current_worker.work);

	res = twl4030bci_पढ़ो_adc_val(TWL4030_BCIVBUS);
	अगर (res < 0)
		v = 0;
	अन्यथा
		/* BCIVBUS uses ADCIN8, 7/1023 V/step */
		v = res * 6843;
	curr = twl4030_अक्षरger_get_current();

	dev_dbg(bci->dev, "v=%d cur=%d limit=%d target=%d\n", v, curr,
		bci->usb_cur, bci->usb_cur_target);

	अगर (v < USB_MIN_VOLT) अणु
		/* Back up and stop adjusting. */
		अगर (bci->usb_cur >= USB_CUR_STEP)
			bci->usb_cur -= USB_CUR_STEP;
		bci->usb_cur_target = bci->usb_cur;
	पूर्ण अन्यथा अगर (bci->usb_cur >= bci->usb_cur_target ||
		   bci->usb_cur + USB_CUR_STEP > USB_MAX_CURRENT) अणु
		/* Reached target and voltage is OK - stop */
		वापस;
	पूर्ण अन्यथा अणु
		bci->usb_cur += USB_CUR_STEP;
		schedule_delayed_work(&bci->current_worker, USB_CUR_DELAY);
	पूर्ण
	twl4030_अक्षरger_update_current(bci);
पूर्ण

/*
 * Enable/Disable USB Charge functionality.
 */
अटल पूर्णांक twl4030_अक्षरger_enable_usb(काष्ठा twl4030_bci *bci, bool enable)
अणु
	पूर्णांक ret;
	u32 reg;

	अगर (bci->usb_mode == CHARGE_OFF)
		enable = false;
	अगर (enable && !IS_ERR_OR_शून्य(bci->transceiver)) अणु

		twl4030_अक्षरger_update_current(bci);

		/* Need to keep phy घातered */
		अगर (!bci->usb_enabled) अणु
			pm_runसमय_get_sync(bci->transceiver->dev);
			bci->usb_enabled = 1;
		पूर्ण

		अगर (bci->usb_mode == CHARGE_AUTO) अणु
			/* Enable पूर्णांकerrupts now. */
			reg = ~(u32)(TWL4030_ICHGLOW | TWL4030_ICHGEOC |
					TWL4030_TBATOR2 | TWL4030_TBATOR1 |
					TWL4030_BATSTS);
			ret = twl_i2c_ग_लिखो_u8(TWL4030_MODULE_INTERRUPTS, reg,
				       TWL4030_INTERRUPTS_BCIIMR1A);
			अगर (ret < 0) अणु
				dev_err(bci->dev,
					"failed to unmask interrupts: %d\n",
					ret);
				वापस ret;
			पूर्ण
			/* क्रमcing the field BCIAUTOUSB (BOOT_BCI[1]) to 1 */
			ret = twl4030_clear_set_boot_bci(0, TWL4030_BCIAUTOUSB);
		पूर्ण

		/* क्रमcing USBFASTMCHG(BCIMFSTS4[2]) to 1 */
		ret = twl4030_clear_set(TWL_MODULE_MAIN_CHARGE, 0,
			TWL4030_USBFASTMCHG, TWL4030_BCIMFSTS4);
		अगर (bci->usb_mode == CHARGE_LINEAR) अणु
			/* Enable पूर्णांकerrupts now. */
			reg = ~(u32)(TWL4030_ICHGLOW | TWL4030_TBATOR2 |
					TWL4030_TBATOR1 | TWL4030_BATSTS);
			ret = twl_i2c_ग_लिखो_u8(TWL4030_MODULE_INTERRUPTS, reg,
				       TWL4030_INTERRUPTS_BCIIMR1A);
			अगर (ret < 0) अणु
				dev_err(bci->dev,
					"failed to unmask interrupts: %d\n",
					ret);
				वापस ret;
			पूर्ण
			twl4030_clear_set_boot_bci(TWL4030_BCIAUTOAC|TWL4030_CVENAC, 0);
			/* Watch करोg key: WOVF acknowledge */
			ret = twl_i2c_ग_लिखो_u8(TWL_MODULE_MAIN_CHARGE, 0x33,
					       TWL4030_BCIWDKEY);
			/* 0x24 + EKEY6: off mode */
			ret = twl_i2c_ग_लिखो_u8(TWL_MODULE_MAIN_CHARGE, 0x2a,
					       TWL4030_BCIMDKEY);
			/* EKEY2: Linear अक्षरge: USB path */
			ret = twl_i2c_ग_लिखो_u8(TWL_MODULE_MAIN_CHARGE, 0x26,
					       TWL4030_BCIMDKEY);
			/* WDKEY5: stop watchकरोg count */
			ret = twl_i2c_ग_लिखो_u8(TWL_MODULE_MAIN_CHARGE, 0xf3,
					       TWL4030_BCIWDKEY);
			/* enable MFEN3 access */
			ret = twl_i2c_ग_लिखो_u8(TWL_MODULE_MAIN_CHARGE, 0x9c,
					       TWL4030_BCIMFKEY);
			 /* ICHGEOCEN - end-of-अक्षरge monitor (current < 80mA)
			  *                      (अक्षरging जारीs)
			  * ICHGLOWEN - current level monitor (अक्षरge जारीs)
			  * करोn't monitor over-current or heat save
			  */
			ret = twl_i2c_ग_लिखो_u8(TWL_MODULE_MAIN_CHARGE, 0xf0,
					       TWL4030_BCIMFEN3);
		पूर्ण
	पूर्ण अन्यथा अणु
		ret = twl4030_clear_set_boot_bci(TWL4030_BCIAUTOUSB, 0);
		ret |= twl_i2c_ग_लिखो_u8(TWL_MODULE_MAIN_CHARGE, 0x2a,
					TWL4030_BCIMDKEY);
		अगर (bci->usb_enabled) अणु
			pm_runसमय_mark_last_busy(bci->transceiver->dev);
			pm_runसमय_put_स्वतःsuspend(bci->transceiver->dev);
			bci->usb_enabled = 0;
		पूर्ण
		bci->usb_cur = 0;
	पूर्ण

	वापस ret;
पूर्ण

/*
 * Enable/Disable AC Charge funtionality.
 */
अटल पूर्णांक twl4030_अक्षरger_enable_ac(काष्ठा twl4030_bci *bci, bool enable)
अणु
	पूर्णांक ret;

	अगर (bci->ac_mode == CHARGE_OFF)
		enable = false;

	अगर (enable)
		ret = twl4030_clear_set_boot_bci(0, TWL4030_BCIAUTOAC);
	अन्यथा
		ret = twl4030_clear_set_boot_bci(TWL4030_BCIAUTOAC, 0);

	वापस ret;
पूर्ण

/*
 * Enable/Disable अक्षरging of Backup Battery.
 */
अटल पूर्णांक twl4030_अक्षरger_enable_backup(पूर्णांक uvolt, पूर्णांक uamp)
अणु
	पूर्णांक ret;
	u8 flags;

	अगर (uvolt < 2500000 ||
	    uamp < 25) अणु
		/* disable अक्षरging of backup battery */
		ret = twl4030_clear_set(TWL_MODULE_PM_RECEIVER,
					TWL4030_BBCHEN, 0, TWL4030_BB_CFG);
		वापस ret;
	पूर्ण

	flags = TWL4030_BBCHEN;
	अगर (uvolt >= 3200000)
		flags |= TWL4030_BBSEL_3V2;
	अन्यथा अगर (uvolt >= 3100000)
		flags |= TWL4030_BBSEL_3V1;
	अन्यथा अगर (uvolt >= 3000000)
		flags |= TWL4030_BBSEL_3V0;
	अन्यथा
		flags |= TWL4030_BBSEL_2V5;

	अगर (uamp >= 1000)
		flags |= TWL4030_BBISEL_1000uA;
	अन्यथा अगर (uamp >= 500)
		flags |= TWL4030_BBISEL_500uA;
	अन्यथा अगर (uamp >= 150)
		flags |= TWL4030_BBISEL_150uA;
	अन्यथा
		flags |= TWL4030_BBISEL_25uA;

	ret = twl4030_clear_set(TWL_MODULE_PM_RECEIVER,
				TWL4030_BBSEL_MASK | TWL4030_BBISEL_MASK,
				flags,
				TWL4030_BB_CFG);

	वापस ret;
पूर्ण

/*
 * TWL4030 CHG_PRES (AC अक्षरger presence) events
 */
अटल irqवापस_t twl4030_अक्षरger_पूर्णांकerrupt(पूर्णांक irq, व्योम *arg)
अणु
	काष्ठा twl4030_bci *bci = arg;

	dev_dbg(bci->dev, "CHG_PRES irq\n");
	/* reset current on each 'plug' event */
	bci->ac_cur = 500000;
	twl4030_अक्षरger_update_current(bci);
	घातer_supply_changed(bci->ac);
	घातer_supply_changed(bci->usb);

	वापस IRQ_HANDLED;
पूर्ण

/*
 * TWL4030 BCI monitoring events
 */
अटल irqवापस_t twl4030_bci_पूर्णांकerrupt(पूर्णांक irq, व्योम *arg)
अणु
	काष्ठा twl4030_bci *bci = arg;
	u8 irqs1, irqs2;
	पूर्णांक ret;

	ret = twl_i2c_पढ़ो_u8(TWL4030_MODULE_INTERRUPTS, &irqs1,
			      TWL4030_INTERRUPTS_BCIISR1A);
	अगर (ret < 0)
		वापस IRQ_HANDLED;

	ret = twl_i2c_पढ़ो_u8(TWL4030_MODULE_INTERRUPTS, &irqs2,
			      TWL4030_INTERRUPTS_BCIISR2A);
	अगर (ret < 0)
		वापस IRQ_HANDLED;

	dev_dbg(bci->dev, "BCI irq %02x %02x\n", irqs2, irqs1);

	अगर (irqs1 & (TWL4030_ICHGLOW | TWL4030_ICHGEOC)) अणु
		/* अक्षरger state change, inक्रमm the core */
		घातer_supply_changed(bci->ac);
		घातer_supply_changed(bci->usb);
	पूर्ण
	twl4030_अक्षरger_update_current(bci);

	/* various monitoring events, क्रम now we just log them here */
	अगर (irqs1 & (TWL4030_TBATOR2 | TWL4030_TBATOR1))
		dev_warn(bci->dev, "battery temperature out of range\n");

	अगर (irqs1 & TWL4030_BATSTS)
		dev_crit(bci->dev, "battery disconnected\n");

	अगर (irqs2 & TWL4030_VBATOV)
		dev_crit(bci->dev, "VBAT overvoltage\n");

	अगर (irqs2 & TWL4030_VBUSOV)
		dev_crit(bci->dev, "VBUS overvoltage\n");

	अगर (irqs2 & TWL4030_ACCHGOV)
		dev_crit(bci->dev, "Ac charger overvoltage\n");

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम twl4030_bci_usb_work(काष्ठा work_काष्ठा *data)
अणु
	काष्ठा twl4030_bci *bci = container_of(data, काष्ठा twl4030_bci, work);

	चयन (bci->event) अणु
	हाल USB_EVENT_VBUS:
	हाल USB_EVENT_CHARGER:
		twl4030_अक्षरger_enable_usb(bci, true);
		अवरोध;
	हाल USB_EVENT_NONE:
		twl4030_अक्षरger_enable_usb(bci, false);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक twl4030_bci_usb_ncb(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ val,
			       व्योम *priv)
अणु
	काष्ठा twl4030_bci *bci = container_of(nb, काष्ठा twl4030_bci, usb_nb);

	dev_dbg(bci->dev, "OTG notify %lu\n", val);

	/* reset current on each 'plug' event */
	अगर (allow_usb)
		bci->usb_cur_target = 500000;
	अन्यथा
		bci->usb_cur_target = 100000;

	bci->event = val;
	schedule_work(&bci->work);

	वापस NOTIFY_OK;
पूर्ण

/*
 * sysfs अक्षरger enabled store
 */
अटल sमाप_प्रकार
twl4030_bci_mode_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  स्थिर अक्षर *buf, माप_प्रकार n)
अणु
	काष्ठा twl4030_bci *bci = dev_get_drvdata(dev->parent);
	पूर्णांक mode;
	पूर्णांक status;

	mode = sysfs_match_string(modes, buf);
	अगर (mode < 0)
		वापस mode;

	अगर (dev == &bci->ac->dev) अणु
		अगर (mode == 2)
			वापस -EINVAL;
		twl4030_अक्षरger_enable_ac(bci, false);
		bci->ac_mode = mode;
		status = twl4030_अक्षरger_enable_ac(bci, true);
	पूर्ण अन्यथा अणु
		twl4030_अक्षरger_enable_usb(bci, false);
		bci->usb_mode = mode;
		status = twl4030_अक्षरger_enable_usb(bci, true);
	पूर्ण
	वापस (status == 0) ? n : status;
पूर्ण

/*
 * sysfs अक्षरger enabled show
 */
अटल sमाप_प्रकार
twl4030_bci_mode_show(काष्ठा device *dev,
			     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा twl4030_bci *bci = dev_get_drvdata(dev->parent);
	पूर्णांक len = 0;
	पूर्णांक i;
	पूर्णांक mode = bci->usb_mode;

	अगर (dev == &bci->ac->dev)
		mode = bci->ac_mode;

	क्रम (i = 0; i < ARRAY_SIZE(modes); i++)
		अगर (mode == i)
			len += scnम_लिखो(buf+len, PAGE_SIZE-len,
					"[%s] ", modes[i]);
		अन्यथा
			len += scnम_लिखो(buf+len, PAGE_SIZE-len,
					"%s ", modes[i]);
	buf[len-1] = '\n';
	वापस len;
पूर्ण
अटल DEVICE_ATTR(mode, 0644, twl4030_bci_mode_show,
		   twl4030_bci_mode_store);

अटल पूर्णांक twl4030_अक्षरger_get_current(व्योम)
अणु
	पूर्णांक curr;
	पूर्णांक ret;
	u8 bcictl1;

	curr = twl4030bci_पढ़ो_adc_val(TWL4030_BCIICHG);
	अगर (curr < 0)
		वापस curr;

	ret = twl4030_bci_पढ़ो(TWL4030_BCICTL1, &bcictl1);
	अगर (ret)
		वापस ret;

	वापस regval2ua(curr, bcictl1 & TWL4030_CGAIN);
पूर्ण

/*
 * Returns the मुख्य अक्षरge FSM state
 * Or < 0 on failure.
 */
अटल पूर्णांक twl4030bci_state(काष्ठा twl4030_bci *bci)
अणु
	पूर्णांक ret;
	u8 state;

	ret = twl4030_bci_पढ़ो(TWL4030_BCIMSTATEC, &state);
	अगर (ret) अणु
		dev_err(bci->dev, "error reading BCIMSTATEC\n");
		वापस ret;
	पूर्ण

	dev_dbg(bci->dev, "state: %02x\n", state);

	वापस state;
पूर्ण

अटल पूर्णांक twl4030_bci_state_to_status(पूर्णांक state)
अणु
	state &= TWL4030_MSTATEC_MASK;
	अगर (TWL4030_MSTATEC_QUICK1 <= state && state <= TWL4030_MSTATEC_QUICK7)
		वापस POWER_SUPPLY_STATUS_CHARGING;
	अन्यथा अगर (TWL4030_MSTATEC_COMPLETE1 <= state &&
					state <= TWL4030_MSTATEC_COMPLETE4)
		वापस POWER_SUPPLY_STATUS_FULL;
	अन्यथा
		वापस POWER_SUPPLY_STATUS_NOT_CHARGING;
पूर्ण

अटल पूर्णांक twl4030_bci_get_property(काष्ठा घातer_supply *psy,
				    क्रमागत घातer_supply_property psp,
				    जोड़ घातer_supply_propval *val)
अणु
	काष्ठा twl4030_bci *bci = dev_get_drvdata(psy->dev.parent);
	पूर्णांक is_अक्षरging;
	पूर्णांक state;
	पूर्णांक ret;

	state = twl4030bci_state(bci);
	अगर (state < 0)
		वापस state;

	अगर (psy->desc->type == POWER_SUPPLY_TYPE_USB)
		is_अक्षरging = state & TWL4030_MSTATEC_USB;
	अन्यथा
		is_अक्षरging = state & TWL4030_MSTATEC_AC;
	अगर (!is_अक्षरging) अणु
		u8 s;
		ret = twl4030_bci_पढ़ो(TWL4030_BCIMDEN, &s);
		अगर (ret < 0)
			वापस ret;
		अगर (psy->desc->type == POWER_SUPPLY_TYPE_USB)
			is_अक्षरging = s & 1;
		अन्यथा
			is_अक्षरging = s & 2;
		अगर (is_अक्षरging)
			/* A little white lie */
			state = TWL4030_MSTATEC_QUICK1;
	पूर्ण

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_STATUS:
		अगर (is_अक्षरging)
			val->पूर्णांकval = twl4030_bci_state_to_status(state);
		अन्यथा
			val->पूर्णांकval = POWER_SUPPLY_STATUS_NOT_CHARGING;
		अवरोध;
	हाल POWER_SUPPLY_PROP_VOLTAGE_NOW:
		/* अक्षरging must be active क्रम meaningful result */
		अगर (!is_अक्षरging)
			वापस -ENODATA;
		अगर (psy->desc->type == POWER_SUPPLY_TYPE_USB) अणु
			ret = twl4030bci_पढ़ो_adc_val(TWL4030_BCIVBUS);
			अगर (ret < 0)
				वापस ret;
			/* BCIVBUS uses ADCIN8, 7/1023 V/step */
			val->पूर्णांकval = ret * 6843;
		पूर्ण अन्यथा अणु
			ret = twl4030bci_पढ़ो_adc_val(TWL4030_BCIVAC);
			अगर (ret < 0)
				वापस ret;
			/* BCIVAC uses ADCIN11, 10/1023 V/step */
			val->पूर्णांकval = ret * 9775;
		पूर्ण
		अवरोध;
	हाल POWER_SUPPLY_PROP_CURRENT_NOW:
		अगर (!is_अक्षरging)
			वापस -ENODATA;
		/* current measurement is shared between AC and USB */
		ret = twl4030_अक्षरger_get_current();
		अगर (ret < 0)
			वापस ret;
		val->पूर्णांकval = ret;
		अवरोध;
	हाल POWER_SUPPLY_PROP_ONLINE:
		val->पूर्णांकval = is_अक्षरging &&
			twl4030_bci_state_to_status(state) !=
				POWER_SUPPLY_STATUS_NOT_CHARGING;
		अवरोध;
	हाल POWER_SUPPLY_PROP_INPUT_CURRENT_LIMIT:
		val->पूर्णांकval = -1;
		अगर (psy->desc->type != POWER_SUPPLY_TYPE_USB) अणु
			अगर (!bci->ac_is_active)
				val->पूर्णांकval = bci->ac_cur;
		पूर्ण अन्यथा अणु
			अगर (bci->ac_is_active)
				val->पूर्णांकval = bci->usb_cur_target;
		पूर्ण
		अगर (val->पूर्णांकval < 0) अणु
			u8 bcictl1;

			val->पूर्णांकval = twl4030bci_पढ़ो_adc_val(TWL4030_BCIIREF1);
			अगर (val->पूर्णांकval < 0)
				वापस val->पूर्णांकval;
			ret = twl4030_bci_पढ़ो(TWL4030_BCICTL1, &bcictl1);
			अगर (ret < 0)
				वापस ret;
			val->पूर्णांकval = regval2ua(val->पूर्णांकval, bcictl1 &
							TWL4030_CGAIN);
		पूर्ण
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक twl4030_bci_set_property(काष्ठा घातer_supply *psy,
				    क्रमागत घातer_supply_property psp,
				    स्थिर जोड़ घातer_supply_propval *val)
अणु
	काष्ठा twl4030_bci *bci = dev_get_drvdata(psy->dev.parent);

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_INPUT_CURRENT_LIMIT:
		अगर (psy->desc->type == POWER_SUPPLY_TYPE_USB)
			bci->usb_cur_target = val->पूर्णांकval;
		अन्यथा
			bci->ac_cur = val->पूर्णांकval;
		twl4030_अक्षरger_update_current(bci);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक twl4030_bci_property_is_ग_लिखोable(काष्ठा घातer_supply *psy,
				      क्रमागत घातer_supply_property psp)
अणु
	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_INPUT_CURRENT_LIMIT:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल क्रमागत घातer_supply_property twl4030_अक्षरger_props[] = अणु
	POWER_SUPPLY_PROP_STATUS,
	POWER_SUPPLY_PROP_ONLINE,
	POWER_SUPPLY_PROP_VOLTAGE_NOW,
	POWER_SUPPLY_PROP_CURRENT_NOW,
	POWER_SUPPLY_PROP_INPUT_CURRENT_LIMIT,
पूर्ण;

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा twl4030_bci_platक्रमm_data *
twl4030_bci_parse_dt(काष्ठा device *dev)
अणु
	काष्ठा device_node *np = dev->of_node;
	काष्ठा twl4030_bci_platक्रमm_data *pdata;
	u32 num;

	अगर (!np)
		वापस शून्य;
	pdata = devm_kzalloc(dev, माप(*pdata), GFP_KERNEL);
	अगर (!pdata)
		वापस pdata;

	अगर (of_property_पढ़ो_u32(np, "ti,bb-uvolt", &num) == 0)
		pdata->bb_uvolt = num;
	अगर (of_property_पढ़ो_u32(np, "ti,bb-uamp", &num) == 0)
		pdata->bb_uamp = num;
	वापस pdata;
पूर्ण
#अन्यथा
अटल अंतरभूत स्थिर काष्ठा twl4030_bci_platक्रमm_data *
twl4030_bci_parse_dt(काष्ठा device *dev)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा घातer_supply_desc twl4030_bci_ac_desc = अणु
	.name		= "twl4030_ac",
	.type		= POWER_SUPPLY_TYPE_MAINS,
	.properties	= twl4030_अक्षरger_props,
	.num_properties	= ARRAY_SIZE(twl4030_अक्षरger_props),
	.get_property	= twl4030_bci_get_property,
	.set_property	= twl4030_bci_set_property,
	.property_is_ग_लिखोable	= twl4030_bci_property_is_ग_लिखोable,
पूर्ण;

अटल स्थिर काष्ठा घातer_supply_desc twl4030_bci_usb_desc = अणु
	.name		= "twl4030_usb",
	.type		= POWER_SUPPLY_TYPE_USB,
	.properties	= twl4030_अक्षरger_props,
	.num_properties	= ARRAY_SIZE(twl4030_अक्षरger_props),
	.get_property	= twl4030_bci_get_property,
	.set_property	= twl4030_bci_set_property,
	.property_is_ग_लिखोable	= twl4030_bci_property_is_ग_लिखोable,
पूर्ण;

अटल पूर्णांक twl4030_bci_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा twl4030_bci *bci;
	स्थिर काष्ठा twl4030_bci_platक्रमm_data *pdata = pdev->dev.platक्रमm_data;
	पूर्णांक ret;
	u32 reg;

	bci = devm_kzalloc(&pdev->dev, माप(*bci), GFP_KERNEL);
	अगर (bci == शून्य)
		वापस -ENOMEM;

	अगर (!pdata)
		pdata = twl4030_bci_parse_dt(&pdev->dev);

	bci->ichg_eoc = 80100; /* Stop अक्षरging when current drops to here */
	bci->ichg_lo = 241000; /* Low threshold */
	bci->ichg_hi = 500000; /* High threshold */
	bci->ac_cur = 500000; /* 500mA */
	अगर (allow_usb)
		bci->usb_cur_target = 500000;  /* 500mA */
	अन्यथा
		bci->usb_cur_target = 100000;  /* 100mA */
	bci->usb_mode = CHARGE_AUTO;
	bci->ac_mode = CHARGE_AUTO;

	bci->dev = &pdev->dev;
	bci->irq_chg = platक्रमm_get_irq(pdev, 0);
	bci->irq_bci = platक्रमm_get_irq(pdev, 1);

	platक्रमm_set_drvdata(pdev, bci);

	INIT_WORK(&bci->work, twl4030_bci_usb_work);
	INIT_DELAYED_WORK(&bci->current_worker, twl4030_current_worker);

	bci->channel_vac = devm_iio_channel_get(&pdev->dev, "vac");
	अगर (IS_ERR(bci->channel_vac)) अणु
		ret = PTR_ERR(bci->channel_vac);
		अगर (ret == -EPROBE_DEFER)
			वापस ret;	/* iio not पढ़ोy */
		dev_warn(&pdev->dev, "could not request vac iio channel (%d)",
			ret);
		bci->channel_vac = शून्य;
	पूर्ण

	अगर (bci->dev->of_node) अणु
		काष्ठा device_node *phynode;

		phynode = of_get_compatible_child(bci->dev->of_node->parent,
						  "ti,twl4030-usb");
		अगर (phynode) अणु
			bci->usb_nb.notअगरier_call = twl4030_bci_usb_ncb;
			bci->transceiver = devm_usb_get_phy_by_node(
				bci->dev, phynode, &bci->usb_nb);
			of_node_put(phynode);
			अगर (IS_ERR(bci->transceiver)) अणु
				ret = PTR_ERR(bci->transceiver);
				अगर (ret == -EPROBE_DEFER)
					वापस ret;	/* phy not पढ़ोy */
				dev_warn(&pdev->dev, "could not request transceiver (%d)",
					ret);
				bci->transceiver = शून्य;
			पूर्ण
		पूर्ण
	पूर्ण

	bci->ac = devm_घातer_supply_रेजिस्टर(&pdev->dev, &twl4030_bci_ac_desc,
					     शून्य);
	अगर (IS_ERR(bci->ac)) अणु
		ret = PTR_ERR(bci->ac);
		dev_err(&pdev->dev, "failed to register ac: %d\n", ret);
		वापस ret;
	पूर्ण

	bci->usb = devm_घातer_supply_रेजिस्टर(&pdev->dev, &twl4030_bci_usb_desc,
					      शून्य);
	अगर (IS_ERR(bci->usb)) अणु
		ret = PTR_ERR(bci->usb);
		dev_err(&pdev->dev, "failed to register usb: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = devm_request_thपढ़ोed_irq(&pdev->dev, bci->irq_chg, शून्य,
			twl4030_अक्षरger_पूर्णांकerrupt, IRQF_ONESHOT, pdev->name,
			bci);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "could not request irq %d, status %d\n",
			bci->irq_chg, ret);
		वापस ret;
	पूर्ण

	ret = devm_request_thपढ़ोed_irq(&pdev->dev, bci->irq_bci, शून्य,
			twl4030_bci_पूर्णांकerrupt, IRQF_ONESHOT, pdev->name, bci);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "could not request irq %d, status %d\n",
			bci->irq_bci, ret);
		वापस ret;
	पूर्ण

	/* Enable पूर्णांकerrupts now. */
	reg = ~(u32)(TWL4030_ICHGLOW | TWL4030_ICHGEOC | TWL4030_TBATOR2 |
		TWL4030_TBATOR1 | TWL4030_BATSTS);
	ret = twl_i2c_ग_लिखो_u8(TWL4030_MODULE_INTERRUPTS, reg,
			       TWL4030_INTERRUPTS_BCIIMR1A);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "failed to unmask interrupts: %d\n", ret);
		वापस ret;
	पूर्ण

	reg = ~(u32)(TWL4030_VBATOV | TWL4030_VBUSOV | TWL4030_ACCHGOV);
	ret = twl_i2c_ग_लिखो_u8(TWL4030_MODULE_INTERRUPTS, reg,
			       TWL4030_INTERRUPTS_BCIIMR2A);
	अगर (ret < 0)
		dev_warn(&pdev->dev, "failed to unmask interrupts: %d\n", ret);

	twl4030_अक्षरger_update_current(bci);
	अगर (device_create_file(&bci->usb->dev, &dev_attr_mode))
		dev_warn(&pdev->dev, "could not create sysfs file\n");
	अगर (device_create_file(&bci->ac->dev, &dev_attr_mode))
		dev_warn(&pdev->dev, "could not create sysfs file\n");

	twl4030_अक्षरger_enable_ac(bci, true);
	अगर (!IS_ERR_OR_शून्य(bci->transceiver))
		twl4030_bci_usb_ncb(&bci->usb_nb,
				    bci->transceiver->last_event,
				    शून्य);
	अन्यथा
		twl4030_अक्षरger_enable_usb(bci, false);
	अगर (pdata)
		twl4030_अक्षरger_enable_backup(pdata->bb_uvolt,
					      pdata->bb_uamp);
	अन्यथा
		twl4030_अक्षरger_enable_backup(0, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक twl4030_bci_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा twl4030_bci *bci = platक्रमm_get_drvdata(pdev);

	twl4030_अक्षरger_enable_ac(bci, false);
	twl4030_अक्षरger_enable_usb(bci, false);
	twl4030_अक्षरger_enable_backup(0, 0);

	device_हटाओ_file(&bci->usb->dev, &dev_attr_mode);
	device_हटाओ_file(&bci->ac->dev, &dev_attr_mode);
	/* mask पूर्णांकerrupts */
	twl_i2c_ग_लिखो_u8(TWL4030_MODULE_INTERRUPTS, 0xff,
			 TWL4030_INTERRUPTS_BCIIMR1A);
	twl_i2c_ग_लिखो_u8(TWL4030_MODULE_INTERRUPTS, 0xff,
			 TWL4030_INTERRUPTS_BCIIMR2A);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id twl_bci_of_match[] = अणु
	अणु.compatible = "ti,twl4030-bci", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, twl_bci_of_match);

अटल काष्ठा platक्रमm_driver twl4030_bci_driver = अणु
	.probe = twl4030_bci_probe,
	.हटाओ	= twl4030_bci_हटाओ,
	.driver	= अणु
		.name	= "twl4030_bci",
		.of_match_table = of_match_ptr(twl_bci_of_match),
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(twl4030_bci_driver);

MODULE_AUTHOR("Graधठvydas Ignotas");
MODULE_DESCRIPTION("TWL4030 Battery Charger Interface driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:twl4030_bci");
