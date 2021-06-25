<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * twl4030_usb - TWL4030 USB transceiver, talking to OMAP OTG controller
 *
 * Copyright (C) 2004-2007 Texas Instruments
 * Copyright (C) 2008 Nokia Corporation
 * Contact: Felipe Balbi <felipe.balbi@nokia.com>
 *
 * Current status:
 *	- HS USB ULPI mode works.
 *	- 3-pin mode support may be added in future.
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/पन.स>
#समावेश <linux/delay.h>
#समावेश <linux/usb/otg.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/usb/musb.h>
#समावेश <linux/usb/ulpi.h>
#समावेश <linux/mfd/twl.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/err.h>
#समावेश <linux/slab.h>

/* Register defines */

#घोषणा MCPC_CTRL			0x30
#घोषणा MCPC_CTRL_RTSOL			(1 << 7)
#घोषणा MCPC_CTRL_EXTSWR		(1 << 6)
#घोषणा MCPC_CTRL_EXTSWC		(1 << 5)
#घोषणा MCPC_CTRL_VOICESW		(1 << 4)
#घोषणा MCPC_CTRL_OUT64K		(1 << 3)
#घोषणा MCPC_CTRL_RTSCTSSW		(1 << 2)
#घोषणा MCPC_CTRL_HS_UART		(1 << 0)

#घोषणा MCPC_IO_CTRL			0x33
#घोषणा MCPC_IO_CTRL_MICBIASEN		(1 << 5)
#घोषणा MCPC_IO_CTRL_CTS_NPU		(1 << 4)
#घोषणा MCPC_IO_CTRL_RXD_PU		(1 << 3)
#घोषणा MCPC_IO_CTRL_TXDTYP		(1 << 2)
#घोषणा MCPC_IO_CTRL_CTSTYP		(1 << 1)
#घोषणा MCPC_IO_CTRL_RTSTYP		(1 << 0)

#घोषणा MCPC_CTRL2			0x36
#घोषणा MCPC_CTRL2_MCPC_CK_EN		(1 << 0)

#घोषणा OTHER_FUNC_CTRL			0x80
#घोषणा OTHER_FUNC_CTRL_BDIS_ACON_EN	(1 << 4)
#घोषणा OTHER_FUNC_CTRL_FIVEWIRE_MODE	(1 << 2)

#घोषणा OTHER_IFC_CTRL			0x83
#घोषणा OTHER_IFC_CTRL_OE_INT_EN	(1 << 6)
#घोषणा OTHER_IFC_CTRL_CEA2011_MODE	(1 << 5)
#घोषणा OTHER_IFC_CTRL_FSLSSERIALMODE_4PIN	(1 << 4)
#घोषणा OTHER_IFC_CTRL_HIZ_ULPI_60MHZ_OUT	(1 << 3)
#घोषणा OTHER_IFC_CTRL_HIZ_ULPI		(1 << 2)
#घोषणा OTHER_IFC_CTRL_ALT_INT_REROUTE	(1 << 0)

#घोषणा OTHER_INT_EN_RISE		0x86
#घोषणा OTHER_INT_EN_FALL		0x89
#घोषणा OTHER_INT_STS			0x8C
#घोषणा OTHER_INT_LATCH			0x8D
#घोषणा OTHER_INT_VB_SESS_VLD		(1 << 7)
#घोषणा OTHER_INT_DM_HI			(1 << 6) /* not valid क्रम "latch" reg */
#घोषणा OTHER_INT_DP_HI			(1 << 5) /* not valid क्रम "latch" reg */
#घोषणा OTHER_INT_BDIS_ACON		(1 << 3) /* not valid क्रम "fall" regs */
#घोषणा OTHER_INT_MANU			(1 << 1)
#घोषणा OTHER_INT_ABNORMAL_STRESS	(1 << 0)

#घोषणा ID_STATUS			0x96
#घोषणा ID_RES_FLOAT			(1 << 4)
#घोषणा ID_RES_440K			(1 << 3)
#घोषणा ID_RES_200K			(1 << 2)
#घोषणा ID_RES_102K			(1 << 1)
#घोषणा ID_RES_GND			(1 << 0)

#घोषणा POWER_CTRL			0xAC
#घोषणा POWER_CTRL_OTG_ENAB		(1 << 5)

#घोषणा OTHER_IFC_CTRL2			0xAF
#घोषणा OTHER_IFC_CTRL2_ULPI_STP_LOW	(1 << 4)
#घोषणा OTHER_IFC_CTRL2_ULPI_TXEN_POL	(1 << 3)
#घोषणा OTHER_IFC_CTRL2_ULPI_4PIN_2430	(1 << 2)
#घोषणा OTHER_IFC_CTRL2_USB_INT_OUTSEL_MASK	(3 << 0) /* bits 0 and 1 */
#घोषणा OTHER_IFC_CTRL2_USB_INT_OUTSEL_INT1N	(0 << 0)
#घोषणा OTHER_IFC_CTRL2_USB_INT_OUTSEL_INT2N	(1 << 0)

#घोषणा REG_CTRL_EN			0xB2
#घोषणा REG_CTRL_ERROR			0xB5
#घोषणा ULPI_I2C_CONFLICT_INTEN		(1 << 0)

#घोषणा OTHER_FUNC_CTRL2		0xB8
#घोषणा OTHER_FUNC_CTRL2_VBAT_TIMER_EN	(1 << 0)

/* following रेजिस्टरs करो not have separate _clr and _set रेजिस्टरs */
#घोषणा VBUS_DEBOUNCE			0xC0
#घोषणा ID_DEBOUNCE			0xC1
#घोषणा VBAT_TIMER			0xD3
#घोषणा PHY_PWR_CTRL			0xFD
#घोषणा PHY_PWR_PHYPWD			(1 << 0)
#घोषणा PHY_CLK_CTRL			0xFE
#घोषणा PHY_CLK_CTRL_CLOCKGATING_EN	(1 << 2)
#घोषणा PHY_CLK_CTRL_CLK32K_EN		(1 << 1)
#घोषणा REQ_PHY_DPLL_CLK		(1 << 0)
#घोषणा PHY_CLK_CTRL_STS		0xFF
#घोषणा PHY_DPLL_CLK			(1 << 0)

/* In module TWL_MODULE_PM_MASTER */
#घोषणा STS_HW_CONDITIONS		0x0F

/* In module TWL_MODULE_PM_RECEIVER */
#घोषणा VUSB_DEDICATED1			0x7D
#घोषणा VUSB_DEDICATED2			0x7E
#घोषणा VUSB1V5_DEV_GRP			0x71
#घोषणा VUSB1V5_TYPE			0x72
#घोषणा VUSB1V5_REMAP			0x73
#घोषणा VUSB1V8_DEV_GRP			0x74
#घोषणा VUSB1V8_TYPE			0x75
#घोषणा VUSB1V8_REMAP			0x76
#घोषणा VUSB3V1_DEV_GRP			0x77
#घोषणा VUSB3V1_TYPE			0x78
#घोषणा VUSB3V1_REMAP			0x79

/* In module TWL4030_MODULE_INTBR */
#घोषणा PMBR1				0x0D
#घोषणा GPIO_USB_4PIN_ULPI_2430C	(3 << 0)

अटल irqवापस_t twl4030_usb_irq(पूर्णांक irq, व्योम *_twl);
/*
 * If VBUS is valid or ID is ground, then we know a
 * cable is present and we need to be runसमय-enabled
 */
अटल अंतरभूत bool cable_present(क्रमागत musb_vbus_id_status stat)
अणु
	वापस stat == MUSB_VBUS_VALID ||
		stat == MUSB_ID_GROUND;
पूर्ण

काष्ठा twl4030_usb अणु
	काष्ठा usb_phy		phy;
	काष्ठा device		*dev;

	/* TWL4030 पूर्णांकernal USB regulator supplies */
	काष्ठा regulator	*usb1v5;
	काष्ठा regulator	*usb1v8;
	काष्ठा regulator	*usb3v1;

	/* क्रम vbus reporting with irqs disabled */
	काष्ठा mutex		lock;

	/* pin configuration */
	क्रमागत twl4030_usb_mode	usb_mode;

	पूर्णांक			irq;
	क्रमागत musb_vbus_id_status linkstat;
	atomic_t		connected;
	bool			vbus_supplied;
	bool			musb_mailbox_pending;

	काष्ठा delayed_work	id_workaround_work;
पूर्ण;

/* पूर्णांकernal define on top of container_of */
#घोषणा phy_to_twl(x)		container_of((x), काष्ठा twl4030_usb, phy)

/*-------------------------------------------------------------------------*/

अटल पूर्णांक twl4030_i2c_ग_लिखो_u8_verअगरy(काष्ठा twl4030_usb *twl,
		u8 module, u8 data, u8 address)
अणु
	u8 check = 0xFF;

	अगर ((twl_i2c_ग_लिखो_u8(module, data, address) >= 0) &&
	    (twl_i2c_पढ़ो_u8(module, &check, address) >= 0) &&
						(check == data))
		वापस 0;
	dev_dbg(twl->dev, "Write%d[%d,0x%x] wrote %02x but read %02x\n",
			1, module, address, check, data);

	/* Failed once: Try again */
	अगर ((twl_i2c_ग_लिखो_u8(module, data, address) >= 0) &&
	    (twl_i2c_पढ़ो_u8(module, &check, address) >= 0) &&
						(check == data))
		वापस 0;
	dev_dbg(twl->dev, "Write%d[%d,0x%x] wrote %02x but read %02x\n",
			2, module, address, check, data);

	/* Failed again: Return error */
	वापस -EBUSY;
पूर्ण

#घोषणा twl4030_usb_ग_लिखो_verअगरy(twl, address, data)	\
	twl4030_i2c_ग_लिखो_u8_verअगरy(twl, TWL_MODULE_USB, (data), (address))

अटल अंतरभूत पूर्णांक twl4030_usb_ग_लिखो(काष्ठा twl4030_usb *twl,
		u8 address, u8 data)
अणु
	पूर्णांक ret = 0;

	ret = twl_i2c_ग_लिखो_u8(TWL_MODULE_USB, data, address);
	अगर (ret < 0)
		dev_dbg(twl->dev,
			"TWL4030:USB:Write[0x%x] Error %d\n", address, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक twl4030_पढ़ोb(काष्ठा twl4030_usb *twl, u8 module, u8 address)
अणु
	u8 data;
	पूर्णांक ret = 0;

	ret = twl_i2c_पढ़ो_u8(module, &data, address);
	अगर (ret >= 0)
		ret = data;
	अन्यथा
		dev_dbg(twl->dev,
			"TWL4030:readb[0x%x,0x%x] Error %d\n",
					module, address, ret);

	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक twl4030_usb_पढ़ो(काष्ठा twl4030_usb *twl, u8 address)
अणु
	वापस twl4030_पढ़ोb(twl, TWL_MODULE_USB, address);
पूर्ण

/*-------------------------------------------------------------------------*/

अटल अंतरभूत पूर्णांक
twl4030_usb_set_bits(काष्ठा twl4030_usb *twl, u8 reg, u8 bits)
अणु
	वापस twl4030_usb_ग_लिखो(twl, ULPI_SET(reg), bits);
पूर्ण

अटल अंतरभूत पूर्णांक
twl4030_usb_clear_bits(काष्ठा twl4030_usb *twl, u8 reg, u8 bits)
अणु
	वापस twl4030_usb_ग_लिखो(twl, ULPI_CLR(reg), bits);
पूर्ण

/*-------------------------------------------------------------------------*/

अटल bool twl4030_is_driving_vbus(काष्ठा twl4030_usb *twl)
अणु
	पूर्णांक ret;

	ret = twl4030_usb_पढ़ो(twl, PHY_CLK_CTRL_STS);
	अगर (ret < 0 || !(ret & PHY_DPLL_CLK))
		/*
		 * अगर घड़ीs are off, रेजिस्टरs are not updated,
		 * but we can assume we करोn't drive VBUS in this हाल
		 */
		वापस false;

	ret = twl4030_usb_पढ़ो(twl, ULPI_OTG_CTRL);
	अगर (ret < 0)
		वापस false;

	वापस (ret & (ULPI_OTG_DRVVBUS | ULPI_OTG_CHRGVBUS)) ? true : false;
पूर्ण

अटल क्रमागत musb_vbus_id_status
	twl4030_usb_linkstat(काष्ठा twl4030_usb *twl)
अणु
	पूर्णांक	status;
	क्रमागत musb_vbus_id_status linkstat = MUSB_UNKNOWN;

	twl->vbus_supplied = false;

	/*
	 * For ID/VBUS sensing, see manual section 15.4.8 ...
	 * except when using only battery backup घातer, two
	 * comparators produce VBUS_PRES and ID_PRES संकेतs,
	 * which करोn't match करोcs अन्यथाwhere.  But ... BIT(7)
	 * and BIT(2) of STS_HW_CONDITIONS, respectively, करो
	 * seem to match up.  If either is true the USB_PRES
	 * संकेत is active, the OTG module is activated, and
	 * its पूर्णांकerrupt may be उठाओd (may wake the प्रणाली).
	 */
	status = twl4030_पढ़ोb(twl, TWL_MODULE_PM_MASTER, STS_HW_CONDITIONS);
	अगर (status < 0)
		dev_err(twl->dev, "USB link status err %d\n", status);
	अन्यथा अगर (status & (BIT(7) | BIT(2))) अणु
		अगर (status & BIT(7)) अणु
			अगर (twl4030_is_driving_vbus(twl))
				status &= ~BIT(7);
			अन्यथा
				twl->vbus_supplied = true;
		पूर्ण

		अगर (status & BIT(2))
			linkstat = MUSB_ID_GROUND;
		अन्यथा अगर (status & BIT(7))
			linkstat = MUSB_VBUS_VALID;
		अन्यथा
			linkstat = MUSB_VBUS_OFF;
	पूर्ण अन्यथा अणु
		अगर (twl->linkstat != MUSB_UNKNOWN)
			linkstat = MUSB_VBUS_OFF;
	पूर्ण

	kobject_uevent(&twl->dev->kobj, linkstat == MUSB_VBUS_VALID
					? KOBJ_ONLINE : KOBJ_OFFLINE);

	dev_dbg(twl->dev, "HW_CONDITIONS 0x%02x/%d; link %d\n",
			status, status, linkstat);

	/* REVISIT this assumes host and peripheral controllers
	 * are रेजिस्टरed, and that both are active...
	 */

	वापस linkstat;
पूर्ण

अटल व्योम twl4030_usb_set_mode(काष्ठा twl4030_usb *twl, पूर्णांक mode)
अणु
	twl->usb_mode = mode;

	चयन (mode) अणु
	हाल T2_USB_MODE_ULPI:
		twl4030_usb_clear_bits(twl, ULPI_IFC_CTRL,
					ULPI_IFC_CTRL_CARKITMODE);
		twl4030_usb_set_bits(twl, POWER_CTRL, POWER_CTRL_OTG_ENAB);
		twl4030_usb_clear_bits(twl, ULPI_FUNC_CTRL,
					ULPI_FUNC_CTRL_XCVRSEL_MASK |
					ULPI_FUNC_CTRL_OPMODE_MASK);
		अवरोध;
	हाल -1:
		/* FIXME: घातer on शेषs */
		अवरोध;
	शेष:
		dev_err(twl->dev, "unsupported T2 transceiver mode %d\n",
				mode);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम twl4030_i2c_access(काष्ठा twl4030_usb *twl, पूर्णांक on)
अणु
	अचिन्हित दीर्घ समयout;
	पूर्णांक val = twl4030_usb_पढ़ो(twl, PHY_CLK_CTRL);

	अगर (val >= 0) अणु
		अगर (on) अणु
			/* enable DPLL to access PHY रेजिस्टरs over I2C */
			val |= REQ_PHY_DPLL_CLK;
			WARN_ON(twl4030_usb_ग_लिखो_verअगरy(twl, PHY_CLK_CTRL,
						(u8)val) < 0);

			समयout = jअगरfies + HZ;
			जबतक (!(twl4030_usb_पढ़ो(twl, PHY_CLK_CTRL_STS) &
							PHY_DPLL_CLK)
				&& समय_beक्रमe(jअगरfies, समयout))
					udelay(10);
			अगर (!(twl4030_usb_पढ़ो(twl, PHY_CLK_CTRL_STS) &
							PHY_DPLL_CLK))
				dev_err(twl->dev, "Timeout setting T2 HSUSB "
						"PHY DPLL clock\n");
		पूर्ण अन्यथा अणु
			/* let ULPI control the DPLL घड़ी */
			val &= ~REQ_PHY_DPLL_CLK;
			WARN_ON(twl4030_usb_ग_लिखो_verअगरy(twl, PHY_CLK_CTRL,
						(u8)val) < 0);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम __twl4030_phy_घातer(काष्ठा twl4030_usb *twl, पूर्णांक on)
अणु
	u8 pwr = twl4030_usb_पढ़ो(twl, PHY_PWR_CTRL);

	अगर (on)
		pwr &= ~PHY_PWR_PHYPWD;
	अन्यथा
		pwr |= PHY_PWR_PHYPWD;

	WARN_ON(twl4030_usb_ग_लिखो_verअगरy(twl, PHY_PWR_CTRL, pwr) < 0);
पूर्ण

अटल पूर्णांक __maybe_unused twl4030_usb_suspend(काष्ठा device *dev)
अणु
	काष्ठा twl4030_usb *twl = dev_get_drvdata(dev);

	/*
	 * we need enabled runसमय on resume,
	 * so turn irq off here, so we करो not get it early
	 * note: wakeup on usb plug works independently of this
	 */
	dev_dbg(twl->dev, "%s\n", __func__);
	disable_irq(twl->irq);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused twl4030_usb_resume(काष्ठा device *dev)
अणु
	काष्ठा twl4030_usb *twl = dev_get_drvdata(dev);

	dev_dbg(twl->dev, "%s\n", __func__);
	enable_irq(twl->irq);
	/* check whether cable status changed */
	twl4030_usb_irq(0, twl);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused twl4030_usb_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा twl4030_usb *twl = dev_get_drvdata(dev);

	dev_dbg(twl->dev, "%s\n", __func__);

	__twl4030_phy_घातer(twl, 0);
	regulator_disable(twl->usb1v5);
	regulator_disable(twl->usb1v8);
	regulator_disable(twl->usb3v1);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused twl4030_usb_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा twl4030_usb *twl = dev_get_drvdata(dev);
	पूर्णांक res;

	dev_dbg(twl->dev, "%s\n", __func__);

	res = regulator_enable(twl->usb3v1);
	अगर (res)
		dev_err(twl->dev, "Failed to enable usb3v1\n");

	res = regulator_enable(twl->usb1v8);
	अगर (res)
		dev_err(twl->dev, "Failed to enable usb1v8\n");

	/*
	 * Disabling usb3v1 regulator (= writing 0 to VUSB3V1_DEV_GRP
	 * in twl4030) resets the VUSB_DEDICATED2 रेजिस्टर. This reset
	 * enables VUSB3V1_SLEEP bit that remaps usb3v1 ACTIVE state to
	 * SLEEP. We work around this by clearing the bit after usv3v1
	 * is re-activated. This ensures that VUSB3V1 is really active.
	 */
	twl_i2c_ग_लिखो_u8(TWL_MODULE_PM_RECEIVER, 0, VUSB_DEDICATED2);

	res = regulator_enable(twl->usb1v5);
	अगर (res)
		dev_err(twl->dev, "Failed to enable usb1v5\n");

	__twl4030_phy_घातer(twl, 1);
	twl4030_usb_ग_लिखो(twl, PHY_CLK_CTRL,
			  twl4030_usb_पढ़ो(twl, PHY_CLK_CTRL) |
			  (PHY_CLK_CTRL_CLOCKGATING_EN |
			   PHY_CLK_CTRL_CLK32K_EN));

	twl4030_i2c_access(twl, 1);
	twl4030_usb_set_mode(twl, twl->usb_mode);
	अगर (twl->usb_mode == T2_USB_MODE_ULPI)
		twl4030_i2c_access(twl, 0);
	/*
	 * According to the TPS65950 TRM, there has to be at least 50ms
	 * delay between setting POWER_CTRL_OTG_ENAB and enabling अक्षरging
	 * so रुको here so that a fully enabled phy can be expected after
	 * resume
	 */
	msleep(50);
	वापस 0;
पूर्ण

अटल पूर्णांक twl4030_phy_घातer_off(काष्ठा phy *phy)
अणु
	काष्ठा twl4030_usb *twl = phy_get_drvdata(phy);

	dev_dbg(twl->dev, "%s\n", __func__);

	वापस 0;
पूर्ण

अटल पूर्णांक twl4030_phy_घातer_on(काष्ठा phy *phy)
अणु
	काष्ठा twl4030_usb *twl = phy_get_drvdata(phy);

	dev_dbg(twl->dev, "%s\n", __func__);
	pm_runसमय_get_sync(twl->dev);
	schedule_delayed_work(&twl->id_workaround_work, HZ);
	pm_runसमय_mark_last_busy(twl->dev);
	pm_runसमय_put_स्वतःsuspend(twl->dev);

	वापस 0;
पूर्ण

अटल पूर्णांक twl4030_usb_lकरो_init(काष्ठा twl4030_usb *twl)
अणु
	/* Enable writing to घातer configuration रेजिस्टरs */
	twl_i2c_ग_लिखो_u8(TWL_MODULE_PM_MASTER, TWL4030_PM_MASTER_KEY_CFG1,
			 TWL4030_PM_MASTER_PROTECT_KEY);

	twl_i2c_ग_लिखो_u8(TWL_MODULE_PM_MASTER, TWL4030_PM_MASTER_KEY_CFG2,
			 TWL4030_PM_MASTER_PROTECT_KEY);

	/* Keep VUSB3V1 LDO in sleep state until VBUS/ID change detected*/
	/*twl_i2c_ग_लिखो_u8(TWL_MODULE_PM_RECEIVER, 0, VUSB_DEDICATED2);*/

	/* input to VUSB3V1 LDO is from VBAT, not VBUS */
	twl_i2c_ग_लिखो_u8(TWL_MODULE_PM_RECEIVER, 0x14, VUSB_DEDICATED1);

	/* Initialize 3.1V regulator */
	twl_i2c_ग_लिखो_u8(TWL_MODULE_PM_RECEIVER, 0, VUSB3V1_DEV_GRP);

	twl->usb3v1 = devm_regulator_get(twl->dev, "usb3v1");
	अगर (IS_ERR(twl->usb3v1))
		वापस -ENODEV;

	twl_i2c_ग_लिखो_u8(TWL_MODULE_PM_RECEIVER, 0, VUSB3V1_TYPE);

	/* Initialize 1.5V regulator */
	twl_i2c_ग_लिखो_u8(TWL_MODULE_PM_RECEIVER, 0, VUSB1V5_DEV_GRP);

	twl->usb1v5 = devm_regulator_get(twl->dev, "usb1v5");
	अगर (IS_ERR(twl->usb1v5))
		वापस -ENODEV;

	twl_i2c_ग_लिखो_u8(TWL_MODULE_PM_RECEIVER, 0, VUSB1V5_TYPE);

	/* Initialize 1.8V regulator */
	twl_i2c_ग_लिखो_u8(TWL_MODULE_PM_RECEIVER, 0, VUSB1V8_DEV_GRP);

	twl->usb1v8 = devm_regulator_get(twl->dev, "usb1v8");
	अगर (IS_ERR(twl->usb1v8))
		वापस -ENODEV;

	twl_i2c_ग_लिखो_u8(TWL_MODULE_PM_RECEIVER, 0, VUSB1V8_TYPE);

	/* disable access to घातer configuration रेजिस्टरs */
	twl_i2c_ग_लिखो_u8(TWL_MODULE_PM_MASTER, 0,
			 TWL4030_PM_MASTER_PROTECT_KEY);

	वापस 0;
पूर्ण

अटल sमाप_प्रकार twl4030_usb_vbus_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा twl4030_usb *twl = dev_get_drvdata(dev);
	पूर्णांक ret = -EINVAL;

	mutex_lock(&twl->lock);
	ret = प्र_लिखो(buf, "%s\n",
			twl->vbus_supplied ? "on" : "off");
	mutex_unlock(&twl->lock);

	वापस ret;
पूर्ण
अटल DEVICE_ATTR(vbus, 0444, twl4030_usb_vbus_show, शून्य);

अटल irqवापस_t twl4030_usb_irq(पूर्णांक irq, व्योम *_twl)
अणु
	काष्ठा twl4030_usb *twl = _twl;
	क्रमागत musb_vbus_id_status status;
	पूर्णांक err;

	status = twl4030_usb_linkstat(twl);

	mutex_lock(&twl->lock);
	twl->linkstat = status;
	mutex_unlock(&twl->lock);

	अगर (cable_present(status)) अणु
		अगर (atomic_add_unless(&twl->connected, 1, 1)) अणु
			dev_dbg(twl->dev, "%s: cable connected %i\n",
				__func__, status);
			pm_runसमय_get_sync(twl->dev);
			twl->musb_mailbox_pending = true;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (atomic_add_unless(&twl->connected, -1, 0)) अणु
			dev_dbg(twl->dev, "%s: cable disconnected %i\n",
				__func__, status);
			pm_runसमय_mark_last_busy(twl->dev);
			pm_runसमय_put_स्वतःsuspend(twl->dev);
			twl->musb_mailbox_pending = true;
		पूर्ण
	पूर्ण
	अगर (twl->musb_mailbox_pending) अणु
		err = musb_mailbox(status);
		अगर (!err)
			twl->musb_mailbox_pending = false;
	पूर्ण

	/* करोn't schedule during sleep - irq works right then */
	अगर (status == MUSB_ID_GROUND && pm_runसमय_active(twl->dev)) अणु
		cancel_delayed_work(&twl->id_workaround_work);
		schedule_delayed_work(&twl->id_workaround_work, HZ);
	पूर्ण

	अगर (irq)
		sysfs_notअगरy(&twl->dev->kobj, शून्य, "vbus");

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम twl4030_id_workaround_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा twl4030_usb *twl = container_of(work, काष्ठा twl4030_usb,
		id_workaround_work.work);

	twl4030_usb_irq(0, twl);
पूर्ण

अटल पूर्णांक twl4030_phy_init(काष्ठा phy *phy)
अणु
	काष्ठा twl4030_usb *twl = phy_get_drvdata(phy);

	pm_runसमय_get_sync(twl->dev);
	twl->linkstat = MUSB_UNKNOWN;
	schedule_delayed_work(&twl->id_workaround_work, HZ);
	pm_runसमय_mark_last_busy(twl->dev);
	pm_runसमय_put_स्वतःsuspend(twl->dev);

	वापस 0;
पूर्ण

अटल पूर्णांक twl4030_set_peripheral(काष्ठा usb_otg *otg,
					काष्ठा usb_gadget *gadget)
अणु
	अगर (!otg)
		वापस -ENODEV;

	otg->gadget = gadget;
	अगर (!gadget)
		otg->state = OTG_STATE_UNDEFINED;

	वापस 0;
पूर्ण

अटल पूर्णांक twl4030_set_host(काष्ठा usb_otg *otg, काष्ठा usb_bus *host)
अणु
	अगर (!otg)
		वापस -ENODEV;

	otg->host = host;
	अगर (!host)
		otg->state = OTG_STATE_UNDEFINED;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा phy_ops ops = अणु
	.init		= twl4030_phy_init,
	.घातer_on	= twl4030_phy_घातer_on,
	.घातer_off	= twl4030_phy_घातer_off,
	.owner		= THIS_MODULE,
पूर्ण;

अटल स्थिर काष्ठा dev_pm_ops twl4030_usb_pm_ops = अणु
	SET_RUNTIME_PM_OPS(twl4030_usb_runसमय_suspend,
			   twl4030_usb_runसमय_resume, शून्य)
	SET_SYSTEM_SLEEP_PM_OPS(twl4030_usb_suspend, twl4030_usb_resume)
पूर्ण;

अटल पूर्णांक twl4030_usb_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा twl4030_usb_data *pdata = dev_get_platdata(&pdev->dev);
	काष्ठा twl4030_usb	*twl;
	काष्ठा phy		*phy;
	पूर्णांक			status, err;
	काष्ठा usb_otg		*otg;
	काष्ठा device_node	*np = pdev->dev.of_node;
	काष्ठा phy_provider	*phy_provider;

	twl = devm_kzalloc(&pdev->dev, माप(*twl), GFP_KERNEL);
	अगर (!twl)
		वापस -ENOMEM;

	अगर (np)
		of_property_पढ़ो_u32(np, "usb_mode",
				(क्रमागत twl4030_usb_mode *)&twl->usb_mode);
	अन्यथा अगर (pdata) अणु
		twl->usb_mode = pdata->usb_mode;
	पूर्ण अन्यथा अणु
		dev_err(&pdev->dev, "twl4030 initialized without pdata\n");
		वापस -EINVAL;
	पूर्ण

	otg = devm_kzalloc(&pdev->dev, माप(*otg), GFP_KERNEL);
	अगर (!otg)
		वापस -ENOMEM;

	twl->dev		= &pdev->dev;
	twl->irq		= platक्रमm_get_irq(pdev, 0);
	twl->vbus_supplied	= false;
	twl->linkstat		= MUSB_UNKNOWN;
	twl->musb_mailbox_pending = false;

	twl->phy.dev		= twl->dev;
	twl->phy.label		= "twl4030";
	twl->phy.otg		= otg;
	twl->phy.type		= USB_PHY_TYPE_USB2;

	otg->usb_phy		= &twl->phy;
	otg->set_host		= twl4030_set_host;
	otg->set_peripheral	= twl4030_set_peripheral;

	phy = devm_phy_create(twl->dev, शून्य, &ops);
	अगर (IS_ERR(phy)) अणु
		dev_dbg(&pdev->dev, "Failed to create PHY\n");
		वापस PTR_ERR(phy);
	पूर्ण

	phy_set_drvdata(phy, twl);

	phy_provider = devm_of_phy_provider_रेजिस्टर(twl->dev,
		of_phy_simple_xlate);
	अगर (IS_ERR(phy_provider))
		वापस PTR_ERR(phy_provider);

	/* init mutex क्रम workqueue */
	mutex_init(&twl->lock);

	INIT_DELAYED_WORK(&twl->id_workaround_work, twl4030_id_workaround_work);

	err = twl4030_usb_lकरो_init(twl);
	अगर (err) अणु
		dev_err(&pdev->dev, "ldo init failed\n");
		वापस err;
	पूर्ण
	usb_add_phy_dev(&twl->phy);

	platक्रमm_set_drvdata(pdev, twl);
	अगर (device_create_file(&pdev->dev, &dev_attr_vbus))
		dev_warn(&pdev->dev, "could not create sysfs file\n");

	ATOMIC_INIT_NOTIFIER_HEAD(&twl->phy.notअगरier);

	pm_runसमय_use_स्वतःsuspend(&pdev->dev);
	pm_runसमय_set_स्वतःsuspend_delay(&pdev->dev, 2000);
	pm_runसमय_enable(&pdev->dev);
	pm_runसमय_get_sync(&pdev->dev);

	/* Our job is to use irqs and status from the घातer module
	 * to keep the transceiver disabled when nothing's connected.
	 *
	 * FIXME we actually shouldn't start enabling it until the
	 * USB controller drivers have said they're पढ़ोy, by calling
	 * set_host() and/or set_peripheral() ... OTG_capable boards
	 * need both handles, otherwise just one suffices.
	 */
	status = devm_request_thपढ़ोed_irq(twl->dev, twl->irq, शून्य,
			twl4030_usb_irq, IRQF_TRIGGER_FALLING |
			IRQF_TRIGGER_RISING | IRQF_ONESHOT, "twl4030_usb", twl);
	अगर (status < 0) अणु
		dev_dbg(&pdev->dev, "can't get IRQ %d, err %d\n",
			twl->irq, status);
		वापस status;
	पूर्ण

	अगर (pdata)
		err = phy_create_lookup(phy, "usb", "musb-hdrc.0");
	अगर (err)
		वापस err;

	pm_runसमय_mark_last_busy(&pdev->dev);
	pm_runसमय_put_स्वतःsuspend(twl->dev);

	dev_info(&pdev->dev, "Initialized TWL4030 USB module\n");
	वापस 0;
पूर्ण

अटल पूर्णांक twl4030_usb_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा twl4030_usb *twl = platक्रमm_get_drvdata(pdev);
	पूर्णांक val;

	usb_हटाओ_phy(&twl->phy);
	pm_runसमय_get_sync(twl->dev);
	cancel_delayed_work_sync(&twl->id_workaround_work);
	device_हटाओ_file(twl->dev, &dev_attr_vbus);

	/* set transceiver mode to घातer on शेषs */
	twl4030_usb_set_mode(twl, -1);

	/* idle ulpi beक्रमe घातering off */
	अगर (cable_present(twl->linkstat))
		pm_runसमय_put_noidle(twl->dev);
	pm_runसमय_mark_last_busy(twl->dev);
	pm_runसमय_करोnt_use_स्वतःsuspend(&pdev->dev);
	pm_runसमय_put_sync(twl->dev);
	pm_runसमय_disable(twl->dev);

	/* स्वतःgate 60MHz ULPI घड़ी,
	 * clear dpll घड़ी request क्रम i2c access,
	 * disable 32KHz
	 */
	val = twl4030_usb_पढ़ो(twl, PHY_CLK_CTRL);
	अगर (val >= 0) अणु
		val |= PHY_CLK_CTRL_CLOCKGATING_EN;
		val &= ~(PHY_CLK_CTRL_CLK32K_EN | REQ_PHY_DPLL_CLK);
		twl4030_usb_ग_लिखो(twl, PHY_CLK_CTRL, (u8)val);
	पूर्ण

	/* disable complete OTG block */
	twl4030_usb_clear_bits(twl, POWER_CTRL, POWER_CTRL_OTG_ENAB);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id twl4030_usb_id_table[] = अणु
	अणु .compatible = "ti,twl4030-usb" पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, twl4030_usb_id_table);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver twl4030_usb_driver = अणु
	.probe		= twl4030_usb_probe,
	.हटाओ		= twl4030_usb_हटाओ,
	.driver		= अणु
		.name	= "twl4030_usb",
		.pm	= &twl4030_usb_pm_ops,
		.of_match_table = of_match_ptr(twl4030_usb_id_table),
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init twl4030_usb_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&twl4030_usb_driver);
पूर्ण
subsys_initcall(twl4030_usb_init);

अटल व्योम __निकास twl4030_usb_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&twl4030_usb_driver);
पूर्ण
module_निकास(twl4030_usb_निकास);

MODULE_ALIAS("platform:twl4030_usb");
MODULE_AUTHOR("Texas Instruments, Inc, Nokia Corporation");
MODULE_DESCRIPTION("TWL4030 USB transceiver driver");
MODULE_LICENSE("GPL");
