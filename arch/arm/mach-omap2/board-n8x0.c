<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/arch/arm/mach-omap2/board-n8x0.c
 *
 * Copyright (C) 2005-2009 Nokia Corporation
 * Author: Juha Yrjola <juha.yrjola@nokia.com>
 *
 * Modअगरied from mach-omap2/board-generic.c
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/irq.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/i2c.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/usb/musb.h>
#समावेश <linux/mmc/host.h>
#समावेश <linux/platक्रमm_data/spi-omap2-mcspi.h>
#समावेश <linux/platक्रमm_data/mmc-omap.h>
#समावेश <linux/mfd/menelaus.h>
#समावेश <sound/tlv320aic3x.h>

#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach-types.h>

#समावेश "common.h"
#समावेश "mmc.h"
#समावेश "soc.h"
#समावेश "common-board-devices.h"

#घोषणा TUSB6010_ASYNC_CS	1
#घोषणा TUSB6010_SYNC_CS	4
#घोषणा TUSB6010_GPIO_INT	58
#घोषणा TUSB6010_GPIO_ENABLE	0
#घोषणा TUSB6010_DMACHAN	0x3f

#घोषणा NOKIA_N810_WIMAX	(1 << 2)
#घोषणा NOKIA_N810		(1 << 1)
#घोषणा NOKIA_N800		(1 << 0)

अटल u32 board_caps;

#घोषणा board_is_n800()		(board_caps & NOKIA_N800)
#घोषणा board_is_n810()		(board_caps & NOKIA_N810)
#घोषणा board_is_n810_wimax()	(board_caps & NOKIA_N810_WIMAX)

अटल व्योम board_check_revision(व्योम)
अणु
	अगर (of_machine_is_compatible("nokia,n800"))
		board_caps = NOKIA_N800;
	अन्यथा अगर (of_machine_is_compatible("nokia,n810"))
		board_caps = NOKIA_N810;
	अन्यथा अगर (of_machine_is_compatible("nokia,n810-wimax"))
		board_caps = NOKIA_N810_WIMAX;

	अगर (!board_caps)
		pr_err("Unknown board\n");
पूर्ण

#अगर IS_ENABLED(CONFIG_USB_MUSB_TUSB6010)
/*
 * Enable or disable घातer to TUSB6010. When enabling, turn on 3.3 V and
 * 1.5 V voltage regulators of PM companion chip. Companion chip will then
 * provide then PGOOD संकेत to TUSB6010 which will release it from reset.
 */
अटल पूर्णांक tusb_set_घातer(पूर्णांक state)
अणु
	पूर्णांक i, retval = 0;

	अगर (state) अणु
		gpio_set_value(TUSB6010_GPIO_ENABLE, 1);
		msleep(1);

		/* Wait until TUSB6010 pulls INT pin करोwn */
		i = 100;
		जबतक (i && gpio_get_value(TUSB6010_GPIO_INT)) अणु
			msleep(1);
			i--;
		पूर्ण

		अगर (!i) अणु
			prपूर्णांकk(KERN_ERR "tusb: powerup failed\n");
			retval = -ENODEV;
		पूर्ण
	पूर्ण अन्यथा अणु
		gpio_set_value(TUSB6010_GPIO_ENABLE, 0);
		msleep(10);
	पूर्ण

	वापस retval;
पूर्ण

अटल काष्ठा musb_hdrc_config musb_config = अणु
	.multipoपूर्णांक	= 1,
	.dyn_fअगरo	= 1,
	.num_eps	= 16,
	.ram_bits	= 12,
पूर्ण;

अटल काष्ठा musb_hdrc_platक्रमm_data tusb_data = अणु
	.mode		= MUSB_OTG,
	.set_घातer	= tusb_set_घातer,
	.min_घातer	= 25,	/* x2 = 50 mA drawn from VBUS as peripheral */
	.घातer		= 100,	/* Max 100 mA VBUS क्रम host mode */
	.config		= &musb_config,
पूर्ण;

अटल व्योम __init n8x0_usb_init(व्योम)
अणु
	पूर्णांक ret = 0;
	अटल स्थिर अक्षर announce[] __initस्थिर = KERN_INFO "TUSB 6010\n";

	/* PM companion chip घातer control pin */
	ret = gpio_request_one(TUSB6010_GPIO_ENABLE, GPIOF_OUT_INIT_LOW,
			       "TUSB6010 enable");
	अगर (ret != 0) अणु
		prपूर्णांकk(KERN_ERR "Could not get TUSB power GPIO%i\n",
		       TUSB6010_GPIO_ENABLE);
		वापस;
	पूर्ण
	tusb_set_घातer(0);

	ret = tusb6010_setup_पूर्णांकerface(&tusb_data, TUSB6010_REFCLK_19, 2,
					TUSB6010_ASYNC_CS, TUSB6010_SYNC_CS,
					TUSB6010_GPIO_INT, TUSB6010_DMACHAN);
	अगर (ret != 0)
		जाओ err;

	prपूर्णांकk(announce);

	वापस;

err:
	gpio_मुक्त(TUSB6010_GPIO_ENABLE);
पूर्ण
#अन्यथा

अटल व्योम __init n8x0_usb_init(व्योम) अणुपूर्ण

#पूर्ण_अगर /*CONFIG_USB_MUSB_TUSB6010 */


अटल काष्ठा omap2_mcspi_device_config p54spi_mcspi_config = अणु
	.turbo_mode	= 0,
पूर्ण;

अटल काष्ठा spi_board_info n800_spi_board_info[] __initdata = अणु
	अणु
		.modalias	= "p54spi",
		.bus_num	= 2,
		.chip_select	= 0,
		.max_speed_hz   = 48000000,
		.controller_data = &p54spi_mcspi_config,
	पूर्ण,
पूर्ण;

#अगर defined(CONFIG_MENELAUS) && IS_ENABLED(CONFIG_MMC_OMAP)

/*
 * On both N800 and N810, only the first of the two MMC controllers is in use.
 * The two MMC slots are multiplexed via Menelaus companion chip over I2C.
 * On N800, both slots are घातered via Menelaus. On N810, only one of the
 * slots is घातered via Menelaus. The N810 EMMC is घातered via GPIO.
 *
 * VMMC				slot 1 on both N800 and N810
 * VDCDC3_APE and VMCS2_APE	slot 2 on N800
 * GPIO23 and GPIO9		slot 2 EMMC on N810
 *
 */
#घोषणा N8X0_SLOT_SWITCH_GPIO	96
#घोषणा N810_EMMC_VSD_GPIO	23
#घोषणा N810_EMMC_VIO_GPIO	9

अटल पूर्णांक slot1_cover_खोलो;
अटल पूर्णांक slot2_cover_खोलो;
अटल काष्ठा device *mmc_device;

अटल पूर्णांक n8x0_mmc_चयन_slot(काष्ठा device *dev, पूर्णांक slot)
अणु
#अगर_घोषित CONFIG_MMC_DEBUG
	dev_dbg(dev, "Choose slot %d\n", slot + 1);
#पूर्ण_अगर
	gpio_set_value(N8X0_SLOT_SWITCH_GPIO, slot);
	वापस 0;
पूर्ण

अटल पूर्णांक n8x0_mmc_set_घातer_menelaus(काष्ठा device *dev, पूर्णांक slot,
					पूर्णांक घातer_on, पूर्णांक vdd)
अणु
	पूर्णांक mV;

#अगर_घोषित CONFIG_MMC_DEBUG
	dev_dbg(dev, "Set slot %d power: %s (vdd %d)\n", slot + 1,
		घातer_on ? "on" : "off", vdd);
#पूर्ण_अगर
	अगर (slot == 0) अणु
		अगर (!घातer_on)
			वापस menelaus_set_vmmc(0);
		चयन (1 << vdd) अणु
		हाल MMC_VDD_33_34:
		हाल MMC_VDD_32_33:
		हाल MMC_VDD_31_32:
			mV = 3100;
			अवरोध;
		हाल MMC_VDD_30_31:
			mV = 3000;
			अवरोध;
		हाल MMC_VDD_28_29:
			mV = 2800;
			अवरोध;
		हाल MMC_VDD_165_195:
			mV = 1850;
			अवरोध;
		शेष:
			BUG();
		पूर्ण
		वापस menelaus_set_vmmc(mV);
	पूर्ण अन्यथा अणु
		अगर (!घातer_on)
			वापस menelaus_set_vdcdc(3, 0);
		चयन (1 << vdd) अणु
		हाल MMC_VDD_33_34:
		हाल MMC_VDD_32_33:
			mV = 3300;
			अवरोध;
		हाल MMC_VDD_30_31:
		हाल MMC_VDD_29_30:
			mV = 3000;
			अवरोध;
		हाल MMC_VDD_28_29:
		हाल MMC_VDD_27_28:
			mV = 2800;
			अवरोध;
		हाल MMC_VDD_24_25:
		हाल MMC_VDD_23_24:
			mV = 2400;
			अवरोध;
		हाल MMC_VDD_22_23:
		हाल MMC_VDD_21_22:
			mV = 2200;
			अवरोध;
		हाल MMC_VDD_20_21:
			mV = 2000;
			अवरोध;
		हाल MMC_VDD_165_195:
			mV = 1800;
			अवरोध;
		शेष:
			BUG();
		पूर्ण
		वापस menelaus_set_vdcdc(3, mV);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम n810_set_घातer_emmc(काष्ठा device *dev,
					 पूर्णांक घातer_on)
अणु
	dev_dbg(dev, "Set EMMC power %s\n", घातer_on ? "on" : "off");

	अगर (घातer_on) अणु
		gpio_set_value(N810_EMMC_VSD_GPIO, 1);
		msleep(1);
		gpio_set_value(N810_EMMC_VIO_GPIO, 1);
		msleep(1);
	पूर्ण अन्यथा अणु
		gpio_set_value(N810_EMMC_VIO_GPIO, 0);
		msleep(50);
		gpio_set_value(N810_EMMC_VSD_GPIO, 0);
		msleep(50);
	पूर्ण
पूर्ण

अटल पूर्णांक n8x0_mmc_set_घातer(काष्ठा device *dev, पूर्णांक slot, पूर्णांक घातer_on,
			      पूर्णांक vdd)
अणु
	अगर (board_is_n800() || slot == 0)
		वापस n8x0_mmc_set_घातer_menelaus(dev, slot, घातer_on, vdd);

	n810_set_घातer_emmc(dev, घातer_on);

	वापस 0;
पूर्ण

अटल पूर्णांक n8x0_mmc_set_bus_mode(काष्ठा device *dev, पूर्णांक slot, पूर्णांक bus_mode)
अणु
	पूर्णांक r;

	dev_dbg(dev, "Set slot %d bus mode %s\n", slot + 1,
		bus_mode == MMC_BUSMODE_OPENDRAIN ? "open-drain" : "push-pull");
	BUG_ON(slot != 0 && slot != 1);
	slot++;
	चयन (bus_mode) अणु
	हाल MMC_BUSMODE_OPENDRAIN:
		r = menelaus_set_mmc_खोलोdrain(slot, 1);
		अवरोध;
	हाल MMC_BUSMODE_PUSHPULL:
		r = menelaus_set_mmc_खोलोdrain(slot, 0);
		अवरोध;
	शेष:
		BUG();
	पूर्ण
	अगर (r != 0 && prपूर्णांकk_ratelimit())
		dev_err(dev, "MMC: unable to set bus mode for slot %d\n",
			slot);
	वापस r;
पूर्ण

अटल पूर्णांक n8x0_mmc_get_cover_state(काष्ठा device *dev, पूर्णांक slot)
अणु
	slot++;
	BUG_ON(slot != 1 && slot != 2);
	अगर (slot == 1)
		वापस slot1_cover_खोलो;
	अन्यथा
		वापस slot2_cover_खोलो;
पूर्ण

अटल व्योम n8x0_mmc_callback(व्योम *data, u8 card_mask)
अणु
#अगर_घोषित CONFIG_MMC_OMAP
	पूर्णांक bit, *खोलोp, index;

	अगर (board_is_n800()) अणु
		bit = 1 << 1;
		खोलोp = &slot2_cover_खोलो;
		index = 1;
	पूर्ण अन्यथा अणु
		bit = 1;
		खोलोp = &slot1_cover_खोलो;
		index = 0;
	पूर्ण

	अगर (card_mask & bit)
		*खोलोp = 1;
	अन्यथा
		*खोलोp = 0;

	omap_mmc_notअगरy_cover_event(mmc_device, index, *खोलोp);
#अन्यथा
	pr_warn("MMC: notify cover event not available\n");
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक n8x0_mmc_late_init(काष्ठा device *dev)
अणु
	पूर्णांक r, bit, *खोलोp;
	पूर्णांक vs2sel;

	mmc_device = dev;

	r = menelaus_set_slot_sel(1);
	अगर (r < 0)
		वापस r;

	अगर (board_is_n800())
		vs2sel = 0;
	अन्यथा
		vs2sel = 2;

	r = menelaus_set_mmc_slot(2, 0, vs2sel, 1);
	अगर (r < 0)
		वापस r;

	n8x0_mmc_set_घातer(dev, 0, MMC_POWER_ON, 16); /* MMC_VDD_28_29 */
	n8x0_mmc_set_घातer(dev, 1, MMC_POWER_ON, 16);

	r = menelaus_set_mmc_slot(1, 1, 0, 1);
	अगर (r < 0)
		वापस r;
	r = menelaus_set_mmc_slot(2, 1, vs2sel, 1);
	अगर (r < 0)
		वापस r;

	r = menelaus_get_slot_pin_states();
	अगर (r < 0)
		वापस r;

	अगर (board_is_n800()) अणु
		bit = 1 << 1;
		खोलोp = &slot2_cover_खोलो;
	पूर्ण अन्यथा अणु
		bit = 1;
		खोलोp = &slot1_cover_खोलो;
		slot2_cover_खोलो = 0;
	पूर्ण

	/* All slot pin bits seem to be inversed until first चयन change */
	अगर (r == 0xf || r == (0xf & ~bit))
		r = ~r;

	अगर (r & bit)
		*खोलोp = 1;
	अन्यथा
		*खोलोp = 0;

	r = menelaus_रेजिस्टर_mmc_callback(n8x0_mmc_callback, शून्य);

	वापस r;
पूर्ण

अटल व्योम n8x0_mmc_shutकरोwn(काष्ठा device *dev)
अणु
	पूर्णांक vs2sel;

	अगर (board_is_n800())
		vs2sel = 0;
	अन्यथा
		vs2sel = 2;

	menelaus_set_mmc_slot(1, 0, 0, 0);
	menelaus_set_mmc_slot(2, 0, vs2sel, 0);
पूर्ण

अटल व्योम n8x0_mmc_cleanup(काष्ठा device *dev)
अणु
	menelaus_unरेजिस्टर_mmc_callback();

	gpio_मुक्त(N8X0_SLOT_SWITCH_GPIO);

	अगर (board_is_n810()) अणु
		gpio_मुक्त(N810_EMMC_VSD_GPIO);
		gpio_मुक्त(N810_EMMC_VIO_GPIO);
	पूर्ण
पूर्ण

/*
 * MMC controller1 has two slots that are multiplexed via I2C.
 * MMC controller2 is not in use.
 */
अटल काष्ठा omap_mmc_platक्रमm_data mmc1_data = अणु
	.nr_slots			= 0,
	.चयन_slot			= n8x0_mmc_चयन_slot,
	.init				= n8x0_mmc_late_init,
	.cleanup			= n8x0_mmc_cleanup,
	.shutकरोwn			= n8x0_mmc_shutकरोwn,
	.max_freq			= 24000000,
	.slots[0] = अणु
		.wires			= 4,
		.set_घातer		= n8x0_mmc_set_घातer,
		.set_bus_mode		= n8x0_mmc_set_bus_mode,
		.get_cover_state	= n8x0_mmc_get_cover_state,
		.ocr_mask		= MMC_VDD_165_195 | MMC_VDD_30_31 |
						MMC_VDD_32_33   | MMC_VDD_33_34,
		.name			= "internal",
	पूर्ण,
	.slots[1] = अणु
		.set_घातer		= n8x0_mmc_set_घातer,
		.set_bus_mode		= n8x0_mmc_set_bus_mode,
		.get_cover_state	= n8x0_mmc_get_cover_state,
		.ocr_mask		= MMC_VDD_165_195 | MMC_VDD_20_21 |
						MMC_VDD_21_22 | MMC_VDD_22_23 |
						MMC_VDD_23_24 | MMC_VDD_24_25 |
						MMC_VDD_27_28 | MMC_VDD_28_29 |
						MMC_VDD_29_30 | MMC_VDD_30_31 |
						MMC_VDD_32_33 | MMC_VDD_33_34,
		.name			= "external",
	पूर्ण,
पूर्ण;

अटल काष्ठा omap_mmc_platक्रमm_data *mmc_data[OMAP24XX_NR_MMC];

अटल काष्ठा gpio n810_emmc_gpios[] __initdata = अणु
	अणु N810_EMMC_VSD_GPIO, GPIOF_OUT_INIT_LOW,  "MMC slot 2 Vddf" पूर्ण,
	अणु N810_EMMC_VIO_GPIO, GPIOF_OUT_INIT_LOW,  "MMC slot 2 Vdd"  पूर्ण,
पूर्ण;

अटल व्योम __init n8x0_mmc_init(व्योम)
अणु
	पूर्णांक err;

	अगर (board_is_n810()) अणु
		mmc1_data.slots[0].name = "external";

		/*
		 * Some Samsung Movinand chips करो not like खोलो-ended
		 * multi-block पढ़ोs and fall to braind-dead state
		 * जबतक करोing so. Reducing the number of blocks in
		 * the transfer or delays in घड़ी disable करो not help
		 */
		mmc1_data.slots[1].name = "internal";
		mmc1_data.slots[1].ban_खोलोended = 1;
	पूर्ण

	err = gpio_request_one(N8X0_SLOT_SWITCH_GPIO, GPIOF_OUT_INIT_LOW,
			       "MMC slot switch");
	अगर (err)
		वापस;

	अगर (board_is_n810()) अणु
		err = gpio_request_array(n810_emmc_gpios,
					 ARRAY_SIZE(n810_emmc_gpios));
		अगर (err) अणु
			gpio_मुक्त(N8X0_SLOT_SWITCH_GPIO);
			वापस;
		पूर्ण
	पूर्ण

	mmc1_data.nr_slots = 2;
	mmc_data[0] = &mmc1_data;
पूर्ण
#अन्यथा
अटल काष्ठा omap_mmc_platक्रमm_data mmc1_data;
व्योम __init n8x0_mmc_init(व्योम)
अणु
पूर्ण
#पूर्ण_अगर	/* CONFIG_MMC_OMAP */

#अगर_घोषित CONFIG_MENELAUS

अटल पूर्णांक n8x0_स्वतः_sleep_regulators(व्योम)
अणु
	u32 val;
	पूर्णांक ret;

	val = EN_VPLL_SLEEP | EN_VMMC_SLEEP    \
		| EN_VAUX_SLEEP | EN_VIO_SLEEP \
		| EN_VMEM_SLEEP | EN_DC3_SLEEP \
		| EN_VC_SLEEP | EN_DC2_SLEEP;

	ret = menelaus_set_regulator_sleep(1, val);
	अगर (ret < 0) अणु
		pr_err("Could not set regulators to sleep on menelaus: %u\n",
		       ret);
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक n8x0_स्वतः_voltage_scale(व्योम)
अणु
	पूर्णांक ret;

	ret = menelaus_set_vcore_hw(1400, 1050);
	अगर (ret < 0) अणु
		pr_err("Could not set VCORE voltage on menelaus: %u\n", ret);
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक n8x0_menelaus_late_init(काष्ठा device *dev)
अणु
	पूर्णांक ret;

	ret = n8x0_स्वतः_voltage_scale();
	अगर (ret < 0)
		वापस ret;
	ret = n8x0_स्वतः_sleep_regulators();
	अगर (ret < 0)
		वापस ret;
	वापस 0;
पूर्ण

#अन्यथा
अटल पूर्णांक n8x0_menelaus_late_init(काष्ठा device *dev)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

काष्ठा menelaus_platक्रमm_data n8x0_menelaus_platक्रमm_data = अणु
	.late_init = n8x0_menelaus_late_init,
पूर्ण;

काष्ठा aic3x_pdata n810_aic33_data = अणु
	.gpio_reset = 118,
पूर्ण;

अटल पूर्णांक __init n8x0_late_initcall(व्योम)
अणु
	अगर (!board_caps)
		वापस -ENODEV;

	n8x0_mmc_init();
	n8x0_usb_init();

	वापस 0;
पूर्ण
omap_late_initcall(n8x0_late_initcall);

/*
 * Legacy init pdata init क्रम n8x0. Note that we want to follow the
 * I2C bus numbering starting at 0 क्रम device tree like other omaps.
 */
व्योम * __init n8x0_legacy_init(व्योम)
अणु
	board_check_revision();
	spi_रेजिस्टर_board_info(n800_spi_board_info,
				ARRAY_SIZE(n800_spi_board_info));
	वापस &mmc1_data;
पूर्ण
