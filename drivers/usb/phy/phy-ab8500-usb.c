<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * USB transceiver driver क्रम AB8500 family chips
 *
 * Copyright (C) 2010-2013 ST-Ericsson AB
 * Mian Yousaf Kaukab <mian.yousaf.kaukab@stericsson.com>
 * Avinash Kumar <avinash.kumar@stericsson.com>
 * Thirupathi Chippakurthy <thirupathi.chippakurthy@stericsson.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/usb/otg.h>
#समावेश <linux/slab.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <linux/clk.h>
#समावेश <linux/err.h>
#समावेश <linux/mfd/abx500.h>
#समावेश <linux/mfd/abx500/ab8500.h>
#समावेश <linux/usb/musb-ux500.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/pinctrl/consumer.h>

/* Bank AB8500_SYS_CTRL2_BLOCK */
#घोषणा AB8500_MAIN_WD_CTRL_REG 0x01

/* Bank AB8500_USB */
#घोषणा AB8500_USB_LINE_STAT_REG 0x80
#घोषणा AB8505_USB_LINE_STAT_REG 0x94
#घोषणा AB8500_USB_PHY_CTRL_REG 0x8A

/* Bank AB8500_DEVELOPMENT */
#घोषणा AB8500_BANK12_ACCESS 0x00

/* Bank AB8500_DEBUG */
#घोषणा AB8500_USB_PHY_TUNE1 0x05
#घोषणा AB8500_USB_PHY_TUNE2 0x06
#घोषणा AB8500_USB_PHY_TUNE3 0x07

/* Bank AB8500_INTERRUPT */
#घोषणा AB8500_IT_SOURCE2_REG 0x01

#घोषणा AB8500_BIT_OTG_STAT_ID (1 << 0)
#घोषणा AB8500_BIT_PHY_CTRL_HOST_EN (1 << 0)
#घोषणा AB8500_BIT_PHY_CTRL_DEVICE_EN (1 << 1)
#घोषणा AB8500_BIT_WD_CTRL_ENABLE (1 << 0)
#घोषणा AB8500_BIT_WD_CTRL_KICK (1 << 1)
#घोषणा AB8500_BIT_SOURCE2_VBUSDET (1 << 7)

#घोषणा AB8500_WD_KICK_DELAY_US 100 /* usec */
#घोषणा AB8500_WD_V11_DISABLE_DELAY_US 100 /* usec */
#घोषणा AB8500_V20_31952_DISABLE_DELAY_US 100 /* usec */

/* Usb line status रेजिस्टर */
क्रमागत ab8500_usb_link_status अणु
	USB_LINK_NOT_CONFIGURED_8500 = 0,
	USB_LINK_STD_HOST_NC_8500,
	USB_LINK_STD_HOST_C_NS_8500,
	USB_LINK_STD_HOST_C_S_8500,
	USB_LINK_HOST_CHG_NM_8500,
	USB_LINK_HOST_CHG_HS_8500,
	USB_LINK_HOST_CHG_HS_CHIRP_8500,
	USB_LINK_DEDICATED_CHG_8500,
	USB_LINK_ACA_RID_A_8500,
	USB_LINK_ACA_RID_B_8500,
	USB_LINK_ACA_RID_C_NM_8500,
	USB_LINK_ACA_RID_C_HS_8500,
	USB_LINK_ACA_RID_C_HS_CHIRP_8500,
	USB_LINK_HM_IDGND_8500,
	USB_LINK_RESERVED_8500,
	USB_LINK_NOT_VALID_LINK_8500,
पूर्ण;

क्रमागत ab8505_usb_link_status अणु
	USB_LINK_NOT_CONFIGURED_8505 = 0,
	USB_LINK_STD_HOST_NC_8505,
	USB_LINK_STD_HOST_C_NS_8505,
	USB_LINK_STD_HOST_C_S_8505,
	USB_LINK_CDP_8505,
	USB_LINK_RESERVED0_8505,
	USB_LINK_RESERVED1_8505,
	USB_LINK_DEDICATED_CHG_8505,
	USB_LINK_ACA_RID_A_8505,
	USB_LINK_ACA_RID_B_8505,
	USB_LINK_ACA_RID_C_NM_8505,
	USB_LINK_RESERVED2_8505,
	USB_LINK_RESERVED3_8505,
	USB_LINK_HM_IDGND_8505,
	USB_LINK_CHARGERPORT_NOT_OK_8505,
	USB_LINK_CHARGER_DM_HIGH_8505,
	USB_LINK_PHYEN_NO_VBUS_NO_IDGND_8505,
	USB_LINK_STD_UPSTREAM_NO_IDGNG_NO_VBUS_8505,
	USB_LINK_STD_UPSTREAM_8505,
	USB_LINK_CHARGER_SE1_8505,
	USB_LINK_CARKIT_CHGR_1_8505,
	USB_LINK_CARKIT_CHGR_2_8505,
	USB_LINK_ACA_DOCK_CHGR_8505,
	USB_LINK_SAMSUNG_BOOT_CBL_PHY_EN_8505,
	USB_LINK_SAMSUNG_BOOT_CBL_PHY_DISB_8505,
	USB_LINK_SAMSUNG_UART_CBL_PHY_EN_8505,
	USB_LINK_SAMSUNG_UART_CBL_PHY_DISB_8505,
	USB_LINK_MOTOROLA_FACTORY_CBL_PHY_EN_8505,
पूर्ण;

क्रमागत ab8500_usb_mode अणु
	USB_IDLE = 0,
	USB_PERIPHERAL,
	USB_HOST,
	USB_DEDICATED_CHG,
	USB_UART
पूर्ण;

/* Register USB_LINK_STATUS पूर्णांकerrupt */
#घोषणा AB8500_USB_FLAG_USE_LINK_STATUS_IRQ	(1 << 0)
/* Register ID_WAKEUP_F पूर्णांकerrupt */
#घोषणा AB8500_USB_FLAG_USE_ID_WAKEUP_IRQ	(1 << 1)
/* Register VBUS_DET_F पूर्णांकerrupt */
#घोषणा AB8500_USB_FLAG_USE_VBUS_DET_IRQ	(1 << 2)
/* Driver is using the ab-iddet driver*/
#घोषणा AB8500_USB_FLAG_USE_AB_IDDET		(1 << 3)
/* Enable setting regulators voltage */
#घोषणा AB8500_USB_FLAG_REGULATOR_SET_VOLTAGE	(1 << 4)

काष्ठा ab8500_usb अणु
	काष्ठा usb_phy phy;
	काष्ठा device *dev;
	काष्ठा ab8500 *ab8500;
	अचिन्हित vbus_draw;
	काष्ठा work_काष्ठा phy_dis_work;
	क्रमागत ab8500_usb_mode mode;
	काष्ठा clk *sysclk;
	काष्ठा regulator *v_ape;
	काष्ठा regulator *v_musb;
	काष्ठा regulator *v_ulpi;
	पूर्णांक saved_v_ulpi;
	पूर्णांक previous_link_status_state;
	काष्ठा pinctrl *pinctrl;
	काष्ठा pinctrl_state *pins_sleep;
	bool enabled_अक्षरging_detection;
	अचिन्हित पूर्णांक flags;
पूर्ण;

अटल अंतरभूत काष्ठा ab8500_usb *phy_to_ab(काष्ठा usb_phy *x)
अणु
	वापस container_of(x, काष्ठा ab8500_usb, phy);
पूर्ण

अटल व्योम ab8500_usb_wd_workaround(काष्ठा ab8500_usb *ab)
अणु
	abx500_set_रेजिस्टर_पूर्णांकerruptible(ab->dev,
		AB8500_SYS_CTRL2_BLOCK,
		AB8500_MAIN_WD_CTRL_REG,
		AB8500_BIT_WD_CTRL_ENABLE);

	udelay(AB8500_WD_KICK_DELAY_US);

	abx500_set_रेजिस्टर_पूर्णांकerruptible(ab->dev,
		AB8500_SYS_CTRL2_BLOCK,
		AB8500_MAIN_WD_CTRL_REG,
		(AB8500_BIT_WD_CTRL_ENABLE
		| AB8500_BIT_WD_CTRL_KICK));

	udelay(AB8500_WD_V11_DISABLE_DELAY_US);

	abx500_set_रेजिस्टर_पूर्णांकerruptible(ab->dev,
		AB8500_SYS_CTRL2_BLOCK,
		AB8500_MAIN_WD_CTRL_REG,
		0);
पूर्ण

अटल व्योम ab8500_usb_regulator_enable(काष्ठा ab8500_usb *ab)
अणु
	पूर्णांक ret, volt;

	ret = regulator_enable(ab->v_ape);
	अगर (ret)
		dev_err(ab->dev, "Failed to enable v-ape\n");

	अगर (ab->flags & AB8500_USB_FLAG_REGULATOR_SET_VOLTAGE) अणु
		ab->saved_v_ulpi = regulator_get_voltage(ab->v_ulpi);
		अगर (ab->saved_v_ulpi < 0)
			dev_err(ab->dev, "Failed to get v_ulpi voltage\n");

		ret = regulator_set_voltage(ab->v_ulpi, 1300000, 1350000);
		अगर (ret < 0)
			dev_err(ab->dev, "Failed to set the Vintcore to 1.3V, ret=%d\n",
					ret);

		ret = regulator_set_load(ab->v_ulpi, 28000);
		अगर (ret < 0)
			dev_err(ab->dev, "Failed to set optimum mode (ret=%d)\n",
					ret);
	पूर्ण

	ret = regulator_enable(ab->v_ulpi);
	अगर (ret)
		dev_err(ab->dev, "Failed to enable vddulpivio18\n");

	अगर (ab->flags & AB8500_USB_FLAG_REGULATOR_SET_VOLTAGE) अणु
		volt = regulator_get_voltage(ab->v_ulpi);
		अगर ((volt != 1300000) && (volt != 1350000))
			dev_err(ab->dev, "Vintcore is not set to 1.3V volt=%d\n",
					volt);
	पूर्ण

	ret = regulator_enable(ab->v_musb);
	अगर (ret)
		dev_err(ab->dev, "Failed to enable musb_1v8\n");
पूर्ण

अटल व्योम ab8500_usb_regulator_disable(काष्ठा ab8500_usb *ab)
अणु
	पूर्णांक ret;

	regulator_disable(ab->v_musb);

	regulator_disable(ab->v_ulpi);

	/* USB is not the only consumer of Vपूर्णांकcore, restore old settings */
	अगर (ab->flags & AB8500_USB_FLAG_REGULATOR_SET_VOLTAGE) अणु
		अगर (ab->saved_v_ulpi > 0) अणु
			ret = regulator_set_voltage(ab->v_ulpi,
					ab->saved_v_ulpi, ab->saved_v_ulpi);
			अगर (ret < 0)
				dev_err(ab->dev, "Failed to set the Vintcore to %duV, ret=%d\n",
						ab->saved_v_ulpi, ret);
		पूर्ण

		ret = regulator_set_load(ab->v_ulpi, 0);
		अगर (ret < 0)
			dev_err(ab->dev, "Failed to set optimum mode (ret=%d)\n",
					ret);
	पूर्ण

	regulator_disable(ab->v_ape);
पूर्ण

अटल व्योम ab8500_usb_wd_linkstatus(काष्ठा ab8500_usb *ab, u8 bit)
अणु
	/* Workaround क्रम v2.0 bug # 31952 */
	अगर (is_ab8500_2p0(ab->ab8500)) अणु
		abx500_mask_and_set_रेजिस्टर_पूर्णांकerruptible(ab->dev,
				AB8500_USB, AB8500_USB_PHY_CTRL_REG,
				bit, bit);
		udelay(AB8500_V20_31952_DISABLE_DELAY_US);
	पूर्ण
पूर्ण

अटल व्योम ab8500_usb_phy_enable(काष्ठा ab8500_usb *ab, bool sel_host)
अणु
	u8 bit;
	bit = sel_host ? AB8500_BIT_PHY_CTRL_HOST_EN :
		AB8500_BIT_PHY_CTRL_DEVICE_EN;

	/* mux and configure USB pins to DEFAULT state */
	ab->pinctrl = pinctrl_get_select(ab->dev, PINCTRL_STATE_DEFAULT);
	अगर (IS_ERR(ab->pinctrl))
		dev_err(ab->dev, "could not get/set default pinstate\n");

	अगर (clk_prepare_enable(ab->sysclk))
		dev_err(ab->dev, "can't prepare/enable clock\n");

	ab8500_usb_regulator_enable(ab);

	abx500_mask_and_set_रेजिस्टर_पूर्णांकerruptible(ab->dev,
			AB8500_USB, AB8500_USB_PHY_CTRL_REG,
			bit, bit);
पूर्ण

अटल व्योम ab8500_usb_phy_disable(काष्ठा ab8500_usb *ab, bool sel_host)
अणु
	u8 bit;
	bit = sel_host ? AB8500_BIT_PHY_CTRL_HOST_EN :
		AB8500_BIT_PHY_CTRL_DEVICE_EN;

	ab8500_usb_wd_linkstatus(ab, bit);

	abx500_mask_and_set_रेजिस्टर_पूर्णांकerruptible(ab->dev,
			AB8500_USB, AB8500_USB_PHY_CTRL_REG,
			bit, 0);

	/* Needed to disable the phy.*/
	ab8500_usb_wd_workaround(ab);

	clk_disable_unprepare(ab->sysclk);

	ab8500_usb_regulator_disable(ab);

	अगर (!IS_ERR(ab->pinctrl)) अणु
		/* configure USB pins to SLEEP state */
		ab->pins_sleep = pinctrl_lookup_state(ab->pinctrl,
				PINCTRL_STATE_SLEEP);

		अगर (IS_ERR(ab->pins_sleep))
			dev_dbg(ab->dev, "could not get sleep pinstate\n");
		अन्यथा अगर (pinctrl_select_state(ab->pinctrl, ab->pins_sleep))
			dev_err(ab->dev, "could not set pins to sleep state\n");

		/*
		 * as USB pins are shared with iddet, release them to allow
		 * iddet to request them
		 */
		pinctrl_put(ab->pinctrl);
	पूर्ण
पूर्ण

#घोषणा ab8500_usb_host_phy_en(ab)	ab8500_usb_phy_enable(ab, true)
#घोषणा ab8500_usb_host_phy_dis(ab)	ab8500_usb_phy_disable(ab, true)
#घोषणा ab8500_usb_peri_phy_en(ab)	ab8500_usb_phy_enable(ab, false)
#घोषणा ab8500_usb_peri_phy_dis(ab)	ab8500_usb_phy_disable(ab, false)

अटल पूर्णांक ab8505_usb_link_status_update(काष्ठा ab8500_usb *ab,
		क्रमागत ab8505_usb_link_status lsts)
अणु
	क्रमागत ux500_musb_vbus_id_status event = 0;

	dev_dbg(ab->dev, "ab8505_usb_link_status_update %d\n", lsts);

	/*
	 * Spurious link_status पूर्णांकerrupts are seen at the समय of
	 * disconnection of a device in RIDA state
	 */
	अगर (ab->previous_link_status_state == USB_LINK_ACA_RID_A_8505 &&
			(lsts == USB_LINK_STD_HOST_NC_8505))
		वापस 0;

	ab->previous_link_status_state = lsts;

	चयन (lsts) अणु
	हाल USB_LINK_ACA_RID_B_8505:
		event = UX500_MUSB_RIDB;
		fallthrough;
	हाल USB_LINK_NOT_CONFIGURED_8505:
	हाल USB_LINK_RESERVED0_8505:
	हाल USB_LINK_RESERVED1_8505:
	हाल USB_LINK_RESERVED2_8505:
	हाल USB_LINK_RESERVED3_8505:
		ab->mode = USB_IDLE;
		ab->phy.otg->शेष_a = false;
		ab->vbus_draw = 0;
		अगर (event != UX500_MUSB_RIDB)
			event = UX500_MUSB_NONE;
		/*
		 * Fallback to शेष B_IDLE as nothing
		 * is connected
		 */
		ab->phy.otg->state = OTG_STATE_B_IDLE;
		usb_phy_set_event(&ab->phy, USB_EVENT_NONE);
		अवरोध;

	हाल USB_LINK_ACA_RID_C_NM_8505:
		event = UX500_MUSB_RIDC;
		fallthrough;
	हाल USB_LINK_STD_HOST_NC_8505:
	हाल USB_LINK_STD_HOST_C_NS_8505:
	हाल USB_LINK_STD_HOST_C_S_8505:
	हाल USB_LINK_CDP_8505:
		अगर (ab->mode == USB_IDLE) अणु
			ab->mode = USB_PERIPHERAL;
			ab8500_usb_peri_phy_en(ab);
			atomic_notअगरier_call_chain(&ab->phy.notअगरier,
					UX500_MUSB_PREPARE, &ab->vbus_draw);
			usb_phy_set_event(&ab->phy, USB_EVENT_ENUMERATED);
		पूर्ण
		अगर (event != UX500_MUSB_RIDC)
			event = UX500_MUSB_VBUS;
		अवरोध;

	हाल USB_LINK_ACA_RID_A_8505:
	हाल USB_LINK_ACA_DOCK_CHGR_8505:
		event = UX500_MUSB_RIDA;
		fallthrough;
	हाल USB_LINK_HM_IDGND_8505:
		अगर (ab->mode == USB_IDLE) अणु
			ab->mode = USB_HOST;
			ab8500_usb_host_phy_en(ab);
			atomic_notअगरier_call_chain(&ab->phy.notअगरier,
					UX500_MUSB_PREPARE, &ab->vbus_draw);
		पूर्ण
		ab->phy.otg->शेष_a = true;
		अगर (event != UX500_MUSB_RIDA)
			event = UX500_MUSB_ID;
		atomic_notअगरier_call_chain(&ab->phy.notअगरier,
				event, &ab->vbus_draw);
		अवरोध;

	हाल USB_LINK_DEDICATED_CHG_8505:
		ab->mode = USB_DEDICATED_CHG;
		event = UX500_MUSB_CHARGER;
		atomic_notअगरier_call_chain(&ab->phy.notअगरier,
				event, &ab->vbus_draw);
		usb_phy_set_event(&ab->phy, USB_EVENT_CHARGER);
		अवरोध;

	/*
	 * FIXME: For now we rely on the boot firmware to set up the necessary
	 * PHY/pin configuration क्रम UART mode.
	 *
	 * AB8505 करोes not seem to report any status change क्रम UART cables,
	 * possibly because it cannot detect them स्वतःnomously.
	 * We may need to measure the ID resistance manually to reliably
	 * detect UART cables after bootup.
	 */
	हाल USB_LINK_SAMSUNG_UART_CBL_PHY_EN_8505:
	हाल USB_LINK_SAMSUNG_UART_CBL_PHY_DISB_8505:
		अगर (ab->mode == USB_IDLE) अणु
			ab->mode = USB_UART;
			ab8500_usb_peri_phy_en(ab);
		पूर्ण

		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ab8500_usb_link_status_update(काष्ठा ab8500_usb *ab,
		क्रमागत ab8500_usb_link_status lsts)
अणु
	क्रमागत ux500_musb_vbus_id_status event = 0;

	dev_dbg(ab->dev, "ab8500_usb_link_status_update %d\n", lsts);

	/*
	 * Spurious link_status पूर्णांकerrupts are seen in हाल of a
	 * disconnection of a device in IDGND and RIDA stage
	 */
	अगर (ab->previous_link_status_state == USB_LINK_HM_IDGND_8500 &&
			(lsts == USB_LINK_STD_HOST_C_NS_8500 ||
			 lsts == USB_LINK_STD_HOST_NC_8500))
		वापस 0;

	अगर (ab->previous_link_status_state == USB_LINK_ACA_RID_A_8500 &&
			lsts == USB_LINK_STD_HOST_NC_8500)
		वापस 0;

	ab->previous_link_status_state = lsts;

	चयन (lsts) अणु
	हाल USB_LINK_ACA_RID_B_8500:
		event = UX500_MUSB_RIDB;
		fallthrough;
	हाल USB_LINK_NOT_CONFIGURED_8500:
	हाल USB_LINK_NOT_VALID_LINK_8500:
		ab->mode = USB_IDLE;
		ab->phy.otg->शेष_a = false;
		ab->vbus_draw = 0;
		अगर (event != UX500_MUSB_RIDB)
			event = UX500_MUSB_NONE;
		/* Fallback to शेष B_IDLE as nothing is connected */
		ab->phy.otg->state = OTG_STATE_B_IDLE;
		usb_phy_set_event(&ab->phy, USB_EVENT_NONE);
		अवरोध;

	हाल USB_LINK_ACA_RID_C_NM_8500:
	हाल USB_LINK_ACA_RID_C_HS_8500:
	हाल USB_LINK_ACA_RID_C_HS_CHIRP_8500:
		event = UX500_MUSB_RIDC;
		fallthrough;
	हाल USB_LINK_STD_HOST_NC_8500:
	हाल USB_LINK_STD_HOST_C_NS_8500:
	हाल USB_LINK_STD_HOST_C_S_8500:
	हाल USB_LINK_HOST_CHG_NM_8500:
	हाल USB_LINK_HOST_CHG_HS_8500:
	हाल USB_LINK_HOST_CHG_HS_CHIRP_8500:
		अगर (ab->mode == USB_IDLE) अणु
			ab->mode = USB_PERIPHERAL;
			ab8500_usb_peri_phy_en(ab);
			atomic_notअगरier_call_chain(&ab->phy.notअगरier,
					UX500_MUSB_PREPARE, &ab->vbus_draw);
			usb_phy_set_event(&ab->phy, USB_EVENT_ENUMERATED);
		पूर्ण
		अगर (event != UX500_MUSB_RIDC)
			event = UX500_MUSB_VBUS;
		अवरोध;

	हाल USB_LINK_ACA_RID_A_8500:
		event = UX500_MUSB_RIDA;
		fallthrough;
	हाल USB_LINK_HM_IDGND_8500:
		अगर (ab->mode == USB_IDLE) अणु
			ab->mode = USB_HOST;
			ab8500_usb_host_phy_en(ab);
			atomic_notअगरier_call_chain(&ab->phy.notअगरier,
					UX500_MUSB_PREPARE, &ab->vbus_draw);
		पूर्ण
		ab->phy.otg->शेष_a = true;
		अगर (event != UX500_MUSB_RIDA)
			event = UX500_MUSB_ID;
		atomic_notअगरier_call_chain(&ab->phy.notअगरier,
				event, &ab->vbus_draw);
		अवरोध;

	हाल USB_LINK_DEDICATED_CHG_8500:
		ab->mode = USB_DEDICATED_CHG;
		event = UX500_MUSB_CHARGER;
		atomic_notअगरier_call_chain(&ab->phy.notअगरier,
				event, &ab->vbus_draw);
		usb_phy_set_event(&ab->phy, USB_EVENT_CHARGER);
		अवरोध;

	हाल USB_LINK_RESERVED_8500:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Connection Sequence:
 *   1. Link Status Interrupt
 *   2. Enable AB घड़ी
 *   3. Enable AB regulators
 *   4. Enable USB phy
 *   5. Reset the musb controller
 *   6. Switch the ULPI GPIO pins to function mode
 *   7. Enable the musb Peripheral5 घड़ी
 *   8. Restore MUSB context
 */
अटल पूर्णांक abx500_usb_link_status_update(काष्ठा ab8500_usb *ab)
अणु
	u8 reg;
	पूर्णांक ret = 0;

	अगर (is_ab8500(ab->ab8500)) अणु
		क्रमागत ab8500_usb_link_status lsts;

		ret = abx500_get_रेजिस्टर_पूर्णांकerruptible(ab->dev,
				AB8500_USB, AB8500_USB_LINE_STAT_REG, &reg);
		अगर (ret < 0)
			वापस ret;
		lsts = (reg >> 3) & 0x0F;
		ret = ab8500_usb_link_status_update(ab, lsts);
	पूर्ण अन्यथा अगर (is_ab8505(ab->ab8500)) अणु
		क्रमागत ab8505_usb_link_status lsts;

		ret = abx500_get_रेजिस्टर_पूर्णांकerruptible(ab->dev,
				AB8500_USB, AB8505_USB_LINE_STAT_REG, &reg);
		अगर (ret < 0)
			वापस ret;
		lsts = (reg >> 3) & 0x1F;
		ret = ab8505_usb_link_status_update(ab, lsts);
	पूर्ण

	वापस ret;
पूर्ण

/*
 * Disconnection Sequence:
 *   1. Disconnect Interrupt
 *   2. Disable regulators
 *   3. Disable AB घड़ी
 *   4. Disable the Phy
 *   5. Link Status Interrupt
 *   6. Disable Musb Clock
 */
अटल irqवापस_t ab8500_usb_disconnect_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा ab8500_usb *ab = (काष्ठा ab8500_usb *) data;
	क्रमागत usb_phy_events event = USB_EVENT_NONE;

	/* Link status will not be updated till phy is disabled. */
	अगर (ab->mode == USB_HOST) अणु
		ab->phy.otg->शेष_a = false;
		ab->vbus_draw = 0;
		atomic_notअगरier_call_chain(&ab->phy.notअगरier,
				event, &ab->vbus_draw);
		ab8500_usb_host_phy_dis(ab);
		ab->mode = USB_IDLE;
	पूर्ण

	अगर (ab->mode == USB_PERIPHERAL) अणु
		atomic_notअगरier_call_chain(&ab->phy.notअगरier,
				event, &ab->vbus_draw);
		ab8500_usb_peri_phy_dis(ab);
		atomic_notअगरier_call_chain(&ab->phy.notअगरier,
				UX500_MUSB_CLEAN, &ab->vbus_draw);
		ab->mode = USB_IDLE;
		ab->phy.otg->शेष_a = false;
		ab->vbus_draw = 0;
	पूर्ण

	अगर (ab->mode == USB_UART) अणु
		ab8500_usb_peri_phy_dis(ab);
		ab->mode = USB_IDLE;
	पूर्ण

	अगर (is_ab8500_2p0(ab->ab8500)) अणु
		अगर (ab->mode == USB_DEDICATED_CHG) अणु
			ab8500_usb_wd_linkstatus(ab,
					AB8500_BIT_PHY_CTRL_DEVICE_EN);
			abx500_mask_and_set_रेजिस्टर_पूर्णांकerruptible(ab->dev,
					AB8500_USB, AB8500_USB_PHY_CTRL_REG,
					AB8500_BIT_PHY_CTRL_DEVICE_EN, 0);
		पूर्ण
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t ab8500_usb_link_status_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा ab8500_usb *ab = (काष्ठा ab8500_usb *)data;

	abx500_usb_link_status_update(ab);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम ab8500_usb_phy_disable_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ab8500_usb *ab = container_of(work, काष्ठा ab8500_usb,
						phy_dis_work);

	अगर (!ab->phy.otg->host)
		ab8500_usb_host_phy_dis(ab);

	अगर (!ab->phy.otg->gadget)
		ab8500_usb_peri_phy_dis(ab);
पूर्ण

अटल पूर्णांक ab8500_usb_set_suspend(काष्ठा usb_phy *x, पूर्णांक suspend)
अणु
	/* TODO */
	वापस 0;
पूर्ण

अटल पूर्णांक ab8500_usb_set_peripheral(काष्ठा usb_otg *otg,
					काष्ठा usb_gadget *gadget)
अणु
	काष्ठा ab8500_usb *ab;

	अगर (!otg)
		वापस -ENODEV;

	ab = phy_to_ab(otg->usb_phy);

	ab->phy.otg->gadget = gadget;

	/* Some drivers call this function in atomic context.
	 * Do not update ab8500 रेजिस्टरs directly till this
	 * is fixed.
	 */

	अगर ((ab->mode != USB_IDLE) && !gadget) अणु
		ab->mode = USB_IDLE;
		schedule_work(&ab->phy_dis_work);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ab8500_usb_set_host(काष्ठा usb_otg *otg, काष्ठा usb_bus *host)
अणु
	काष्ठा ab8500_usb *ab;

	अगर (!otg)
		वापस -ENODEV;

	ab = phy_to_ab(otg->usb_phy);

	ab->phy.otg->host = host;

	/* Some drivers call this function in atomic context.
	 * Do not update ab8500 रेजिस्टरs directly till this
	 * is fixed.
	 */

	अगर ((ab->mode != USB_IDLE) && !host) अणु
		ab->mode = USB_IDLE;
		schedule_work(&ab->phy_dis_work);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ab8500_usb_restart_phy(काष्ठा ab8500_usb *ab)
अणु
	abx500_mask_and_set_रेजिस्टर_पूर्णांकerruptible(ab->dev,
			AB8500_USB, AB8500_USB_PHY_CTRL_REG,
			AB8500_BIT_PHY_CTRL_DEVICE_EN,
			AB8500_BIT_PHY_CTRL_DEVICE_EN);

	udelay(100);

	abx500_mask_and_set_रेजिस्टर_पूर्णांकerruptible(ab->dev,
			AB8500_USB, AB8500_USB_PHY_CTRL_REG,
			AB8500_BIT_PHY_CTRL_DEVICE_EN,
			0);

	abx500_mask_and_set_रेजिस्टर_पूर्णांकerruptible(ab->dev,
			AB8500_USB, AB8500_USB_PHY_CTRL_REG,
			AB8500_BIT_PHY_CTRL_HOST_EN,
			AB8500_BIT_PHY_CTRL_HOST_EN);

	udelay(100);

	abx500_mask_and_set_रेजिस्टर_पूर्णांकerruptible(ab->dev,
			AB8500_USB, AB8500_USB_PHY_CTRL_REG,
			AB8500_BIT_PHY_CTRL_HOST_EN,
			0);
पूर्ण

अटल पूर्णांक ab8500_usb_regulator_get(काष्ठा ab8500_usb *ab)
अणु
	पूर्णांक err;

	ab->v_ape = devm_regulator_get(ab->dev, "v-ape");
	अगर (IS_ERR(ab->v_ape)) अणु
		dev_err(ab->dev, "Could not get v-ape supply\n");
		err = PTR_ERR(ab->v_ape);
		वापस err;
	पूर्ण

	ab->v_ulpi = devm_regulator_get(ab->dev, "vddulpivio18");
	अगर (IS_ERR(ab->v_ulpi)) अणु
		dev_err(ab->dev, "Could not get vddulpivio18 supply\n");
		err = PTR_ERR(ab->v_ulpi);
		वापस err;
	पूर्ण

	ab->v_musb = devm_regulator_get(ab->dev, "musb_1v8");
	अगर (IS_ERR(ab->v_musb)) अणु
		dev_err(ab->dev, "Could not get musb_1v8 supply\n");
		err = PTR_ERR(ab->v_musb);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ab8500_usb_irq_setup(काष्ठा platक्रमm_device *pdev,
		काष्ठा ab8500_usb *ab)
अणु
	पूर्णांक err;
	पूर्णांक irq;

	अगर (ab->flags & AB8500_USB_FLAG_USE_LINK_STATUS_IRQ) अणु
		irq = platक्रमm_get_irq_byname(pdev, "USB_LINK_STATUS");
		अगर (irq < 0)
			वापस irq;
		err = devm_request_thपढ़ोed_irq(&pdev->dev, irq, शून्य,
				ab8500_usb_link_status_irq,
				IRQF_NO_SUSPEND | IRQF_SHARED | IRQF_ONESHOT,
				"usb-link-status", ab);
		अगर (err < 0) अणु
			dev_err(ab->dev, "request_irq failed for link status irq\n");
			वापस err;
		पूर्ण
	पूर्ण

	अगर (ab->flags & AB8500_USB_FLAG_USE_ID_WAKEUP_IRQ) अणु
		irq = platक्रमm_get_irq_byname(pdev, "ID_WAKEUP_F");
		अगर (irq < 0)
			वापस irq;
		err = devm_request_thपढ़ोed_irq(&pdev->dev, irq, शून्य,
				ab8500_usb_disconnect_irq,
				IRQF_NO_SUSPEND | IRQF_SHARED | IRQF_ONESHOT,
				"usb-id-fall", ab);
		अगर (err < 0) अणु
			dev_err(ab->dev, "request_irq failed for ID fall irq\n");
			वापस err;
		पूर्ण
	पूर्ण

	अगर (ab->flags & AB8500_USB_FLAG_USE_VBUS_DET_IRQ) अणु
		irq = platक्रमm_get_irq_byname(pdev, "VBUS_DET_F");
		अगर (irq < 0)
			वापस irq;
		err = devm_request_thपढ़ोed_irq(&pdev->dev, irq, शून्य,
				ab8500_usb_disconnect_irq,
				IRQF_NO_SUSPEND | IRQF_SHARED | IRQF_ONESHOT,
				"usb-vbus-fall", ab);
		अगर (err < 0) अणु
			dev_err(ab->dev, "request_irq failed for Vbus fall irq\n");
			वापस err;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ab8500_usb_set_ab8500_tuning_values(काष्ठा ab8500_usb *ab)
अणु
	पूर्णांक err;

	/* Enable the PBT/Bank 0x12 access */
	err = abx500_set_रेजिस्टर_पूर्णांकerruptible(ab->dev,
			AB8500_DEVELOPMENT, AB8500_BANK12_ACCESS, 0x01);
	अगर (err < 0)
		dev_err(ab->dev, "Failed to enable bank12 access err=%d\n",
				err);

	err = abx500_set_रेजिस्टर_पूर्णांकerruptible(ab->dev,
			AB8500_DEBUG, AB8500_USB_PHY_TUNE1, 0xC8);
	अगर (err < 0)
		dev_err(ab->dev, "Failed to set PHY_TUNE1 register err=%d\n",
				err);

	err = abx500_set_रेजिस्टर_पूर्णांकerruptible(ab->dev,
			AB8500_DEBUG, AB8500_USB_PHY_TUNE2, 0x00);
	अगर (err < 0)
		dev_err(ab->dev, "Failed to set PHY_TUNE2 register err=%d\n",
				err);

	err = abx500_set_रेजिस्टर_पूर्णांकerruptible(ab->dev,
			AB8500_DEBUG, AB8500_USB_PHY_TUNE3, 0x78);
	अगर (err < 0)
		dev_err(ab->dev, "Failed to set PHY_TUNE3 register err=%d\n",
				err);

	/* Switch to normal mode/disable Bank 0x12 access */
	err = abx500_set_रेजिस्टर_पूर्णांकerruptible(ab->dev,
			AB8500_DEVELOPMENT, AB8500_BANK12_ACCESS, 0x00);
	अगर (err < 0)
		dev_err(ab->dev, "Failed to switch bank12 access err=%d\n",
				err);
पूर्ण

अटल व्योम ab8500_usb_set_ab8505_tuning_values(काष्ठा ab8500_usb *ab)
अणु
	पूर्णांक err;

	/* Enable the PBT/Bank 0x12 access */
	err = abx500_mask_and_set_रेजिस्टर_पूर्णांकerruptible(ab->dev,
			AB8500_DEVELOPMENT, AB8500_BANK12_ACCESS,
			0x01, 0x01);
	अगर (err < 0)
		dev_err(ab->dev, "Failed to enable bank12 access err=%d\n",
				err);

	err = abx500_mask_and_set_रेजिस्टर_पूर्णांकerruptible(ab->dev,
			AB8500_DEBUG, AB8500_USB_PHY_TUNE1,
			0xC8, 0xC8);
	अगर (err < 0)
		dev_err(ab->dev, "Failed to set PHY_TUNE1 register err=%d\n",
				err);

	err = abx500_mask_and_set_रेजिस्टर_पूर्णांकerruptible(ab->dev,
			AB8500_DEBUG, AB8500_USB_PHY_TUNE2,
			0x60, 0x60);
	अगर (err < 0)
		dev_err(ab->dev, "Failed to set PHY_TUNE2 register err=%d\n",
				err);

	err = abx500_mask_and_set_रेजिस्टर_पूर्णांकerruptible(ab->dev,
			AB8500_DEBUG, AB8500_USB_PHY_TUNE3,
			0xFC, 0x80);

	अगर (err < 0)
		dev_err(ab->dev, "Failed to set PHY_TUNE3 register err=%d\n",
				err);

	/* Switch to normal mode/disable Bank 0x12 access */
	err = abx500_mask_and_set_रेजिस्टर_पूर्णांकerruptible(ab->dev,
			AB8500_DEVELOPMENT, AB8500_BANK12_ACCESS,
			0x00, 0x00);
	अगर (err < 0)
		dev_err(ab->dev, "Failed to switch bank12 access err=%d\n",
				err);
पूर्ण

अटल पूर्णांक ab8500_usb_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ab8500_usb	*ab;
	काष्ठा ab8500		*ab8500;
	काष्ठा usb_otg		*otg;
	पूर्णांक err;
	पूर्णांक rev;

	ab8500 = dev_get_drvdata(pdev->dev.parent);
	rev = abx500_get_chip_id(&pdev->dev);

	अगर (is_ab8500_1p1_or_earlier(ab8500)) अणु
		dev_err(&pdev->dev, "Unsupported AB8500 chip rev=%d\n", rev);
		वापस -ENODEV;
	पूर्ण

	ab = devm_kzalloc(&pdev->dev, माप(*ab), GFP_KERNEL);
	अगर (!ab)
		वापस -ENOMEM;

	otg = devm_kzalloc(&pdev->dev, माप(*otg), GFP_KERNEL);
	अगर (!otg)
		वापस -ENOMEM;

	ab->dev			= &pdev->dev;
	ab->ab8500		= ab8500;
	ab->phy.dev		= ab->dev;
	ab->phy.otg		= otg;
	ab->phy.label		= "ab8500";
	ab->phy.set_suspend	= ab8500_usb_set_suspend;
	ab->phy.otg->state	= OTG_STATE_UNDEFINED;

	otg->usb_phy		= &ab->phy;
	otg->set_host		= ab8500_usb_set_host;
	otg->set_peripheral	= ab8500_usb_set_peripheral;

	अगर (is_ab8500(ab->ab8500)) अणु
		ab->flags |= AB8500_USB_FLAG_USE_LINK_STATUS_IRQ |
			AB8500_USB_FLAG_USE_ID_WAKEUP_IRQ |
			AB8500_USB_FLAG_USE_VBUS_DET_IRQ |
			AB8500_USB_FLAG_REGULATOR_SET_VOLTAGE;
	पूर्ण अन्यथा अगर (is_ab8505(ab->ab8500)) अणु
		ab->flags |= AB8500_USB_FLAG_USE_LINK_STATUS_IRQ |
			AB8500_USB_FLAG_USE_ID_WAKEUP_IRQ |
			AB8500_USB_FLAG_USE_VBUS_DET_IRQ |
			AB8500_USB_FLAG_REGULATOR_SET_VOLTAGE;
	पूर्ण

	/* Disable regulator voltage setting क्रम AB8500 <= v2.0 */
	अगर (is_ab8500_2p0_or_earlier(ab->ab8500))
		ab->flags &= ~AB8500_USB_FLAG_REGULATOR_SET_VOLTAGE;

	platक्रमm_set_drvdata(pdev, ab);

	/* all: Disable phy when called from set_host and set_peripheral */
	INIT_WORK(&ab->phy_dis_work, ab8500_usb_phy_disable_work);

	err = ab8500_usb_regulator_get(ab);
	अगर (err)
		वापस err;

	ab->sysclk = devm_clk_get(ab->dev, "sysclk");
	अगर (IS_ERR(ab->sysclk)) अणु
		dev_err(ab->dev, "Could not get sysclk.\n");
		वापस PTR_ERR(ab->sysclk);
	पूर्ण

	err = ab8500_usb_irq_setup(pdev, ab);
	अगर (err < 0)
		वापस err;

	err = usb_add_phy(&ab->phy, USB_PHY_TYPE_USB2);
	अगर (err) अणु
		dev_err(&pdev->dev, "Can't register transceiver\n");
		वापस err;
	पूर्ण

	अगर (is_ab8500(ab->ab8500) && !is_ab8500_2p0_or_earlier(ab->ab8500))
		/* Phy tuning values क्रम AB8500 > v2.0 */
		ab8500_usb_set_ab8500_tuning_values(ab);
	अन्यथा अगर (is_ab8505(ab->ab8500))
		/* Phy tuning values क्रम AB8505 */
		ab8500_usb_set_ab8505_tuning_values(ab);

	/* Needed to enable ID detection. */
	ab8500_usb_wd_workaround(ab);

	/*
	 * This is required क्रम usb-link-status to work properly when a
	 * cable is connected at boot समय.
	 */
	ab8500_usb_restart_phy(ab);

	abx500_usb_link_status_update(ab);

	dev_info(&pdev->dev, "revision 0x%2x driver initialized\n", rev);

	वापस 0;
पूर्ण

अटल पूर्णांक ab8500_usb_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ab8500_usb *ab = platक्रमm_get_drvdata(pdev);

	cancel_work_sync(&ab->phy_dis_work);

	usb_हटाओ_phy(&ab->phy);

	अगर (ab->mode == USB_HOST)
		ab8500_usb_host_phy_dis(ab);
	अन्यथा अगर (ab->mode == USB_PERIPHERAL)
		ab8500_usb_peri_phy_dis(ab);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_id ab8500_usb_devtype[] = अणु
	अणु .name = "ab8500-usb", पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, ab8500_usb_devtype);

अटल काष्ठा platक्रमm_driver ab8500_usb_driver = अणु
	.probe		= ab8500_usb_probe,
	.हटाओ		= ab8500_usb_हटाओ,
	.id_table	= ab8500_usb_devtype,
	.driver		= अणु
		.name	= "abx5x0-usb",
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init ab8500_usb_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&ab8500_usb_driver);
पूर्ण
subsys_initcall(ab8500_usb_init);

अटल व्योम __निकास ab8500_usb_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&ab8500_usb_driver);
पूर्ण
module_निकास(ab8500_usb_निकास);

MODULE_AUTHOR("ST-Ericsson AB");
MODULE_DESCRIPTION("AB8500 family usb transceiver driver");
MODULE_LICENSE("GPL");
