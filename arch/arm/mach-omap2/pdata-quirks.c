<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Legacy platक्रमm_data quirks
 *
 * Copyright (C) 2013 Texas Instruments
 */
#समावेश <linux/clk.h>
#समावेश <linux/davinci_emac.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/wl12xx.h>
#समावेश <linux/mmc/card.h>
#समावेश <linux/mmc/host.h>
#समावेश <linux/घातer/smartreflex.h>
#समावेश <linux/regulator/machine.h>
#समावेश <linux/regulator/fixed.h>

#समावेश <linux/platक्रमm_data/pinctrl-single.h>
#समावेश <linux/platक्रमm_data/hsmmc-omap.h>
#समावेश <linux/platक्रमm_data/iommu-omap.h>
#समावेश <linux/platक्रमm_data/ti-sysc.h>
#समावेश <linux/platक्रमm_data/wkup_m3.h>
#समावेश <linux/platक्रमm_data/asoc-ti-mcbsp.h>
#समावेश <linux/platक्रमm_data/ti-prm.h>

#समावेश "clockdomain.h"
#समावेश "common.h"
#समावेश "common-board-devices.h"
#समावेश "control.h"
#समावेश "omap_device.h"
#समावेश "omap-secure.h"
#समावेश "soc.h"

अटल काष्ठा omap_hsmmc_platक्रमm_data __maybe_unused mmc_pdata[2];

काष्ठा pdata_init अणु
	स्थिर अक्षर *compatible;
	व्योम (*fn)(व्योम);
पूर्ण;

अटल काष्ठा of_dev_auxdata omap_auxdata_lookup[];
अटल काष्ठा twl4030_gpio_platक्रमm_data twl_gpio_auxdata;

#अगर IS_ENABLED(CONFIG_OMAP_IOMMU)
पूर्णांक omap_iommu_set_pwrdm_स्थिरraपूर्णांक(काष्ठा platक्रमm_device *pdev, bool request,
				    u8 *pwrst);
#अन्यथा
अटल अंतरभूत पूर्णांक omap_iommu_set_pwrdm_स्थिरraपूर्णांक(काष्ठा platक्रमm_device *pdev,
						  bool request, u8 *pwrst)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_MACH_NOKIA_N8X0
अटल व्योम __init omap2420_n8x0_legacy_init(व्योम)
अणु
	omap_auxdata_lookup[0].platक्रमm_data = n8x0_legacy_init();
पूर्ण
#अन्यथा
#घोषणा omap2420_n8x0_legacy_init	शून्य
#पूर्ण_अगर

#अगर_घोषित CONFIG_ARCH_OMAP3
/*
 * Configures GPIOs 126, 127 and 129 to 1.8V mode instead of 3.0V
 * mode क्रम MMC1 in हाल bootloader did not configure things.
 * Note that अगर the pins are used क्रम MMC1, pbias-regulator
 * manages the IO voltage.
 */
अटल व्योम __init omap3_gpio126_127_129(व्योम)
अणु
	u32 reg;

	reg = omap_ctrl_पढ़ोl(OMAP343X_CONTROL_PBIAS_LITE);
	reg &= ~OMAP343X_PBIASLITEVMODE1;
	reg |= OMAP343X_PBIASLITEPWRDNZ1;
	omap_ctrl_ग_लिखोl(reg, OMAP343X_CONTROL_PBIAS_LITE);
	अगर (cpu_is_omap3630()) अणु
		reg = omap_ctrl_पढ़ोl(OMAP34XX_CONTROL_WKUP_CTRL);
		reg |= OMAP36XX_GPIO_IO_PWRDNZ;
		omap_ctrl_ग_लिखोl(reg, OMAP34XX_CONTROL_WKUP_CTRL);
	पूर्ण
पूर्ण

अटल व्योम __init hsmmc2_पूर्णांकernal_input_clk(व्योम)
अणु
	u32 reg;

	reg = omap_ctrl_पढ़ोl(OMAP343X_CONTROL_DEVCONF1);
	reg |= OMAP2_MMCSDIO2ADPCLKISEL;
	omap_ctrl_ग_लिखोl(reg, OMAP343X_CONTROL_DEVCONF1);
पूर्ण

#अगर_घोषित CONFIG_OMAP_HWMOD
अटल काष्ठा iommu_platक्रमm_data omap3_iommu_pdata = अणु
	.reset_name = "mmu",
	.निश्चित_reset = omap_device_निश्चित_hardreset,
	.deनिश्चित_reset = omap_device_deनिश्चित_hardreset,
	.device_enable = omap_device_enable,
	.device_idle = omap_device_idle,
पूर्ण;

अटल काष्ठा iommu_platक्रमm_data omap3_iommu_isp_pdata = अणु
	.device_enable = omap_device_enable,
	.device_idle = omap_device_idle,
पूर्ण;
#पूर्ण_अगर

अटल पूर्णांक omap3_sbc_t3730_twl_callback(काष्ठा device *dev,
					   अचिन्हित gpio,
					   अचिन्हित ngpio)
अणु
	पूर्णांक res;

	res = gpio_request_one(gpio + 2, GPIOF_OUT_INIT_HIGH,
			       "wlan pwr");
	अगर (res)
		वापस res;

	gpio_export(gpio, 0);

	वापस 0;
पूर्ण

अटल व्योम __init omap3_sbc_t3x_usb_hub_init(पूर्णांक gpio, अक्षर *hub_name)
अणु
	पूर्णांक err = gpio_request_one(gpio, GPIOF_OUT_INIT_LOW, hub_name);

	अगर (err) अणु
		pr_err("SBC-T3x: %s reset gpio request failed: %d\n",
			hub_name, err);
		वापस;
	पूर्ण

	gpio_export(gpio, 0);

	udelay(10);
	gpio_set_value(gpio, 1);
	msleep(1);
पूर्ण

अटल व्योम __init omap3_sbc_t3730_twl_init(व्योम)
अणु
	twl_gpio_auxdata.setup = omap3_sbc_t3730_twl_callback;
पूर्ण

अटल व्योम __init omap3_sbc_t3730_legacy_init(व्योम)
अणु
	omap3_sbc_t3x_usb_hub_init(167, "sb-t35 usb hub");
पूर्ण

अटल व्योम __init omap3_sbc_t3530_legacy_init(व्योम)
अणु
	omap3_sbc_t3x_usb_hub_init(167, "sb-t35 usb hub");
पूर्ण

अटल व्योम __init omap3_evm_legacy_init(व्योम)
अणु
	hsmmc2_पूर्णांकernal_input_clk();
पूर्ण

अटल व्योम am35xx_enable_emac_पूर्णांक(व्योम)
अणु
	u32 v;

	v = omap_ctrl_पढ़ोl(AM35XX_CONTROL_LVL_INTR_CLEAR);
	v |= (AM35XX_CPGMAC_C0_RX_PULSE_CLR | AM35XX_CPGMAC_C0_TX_PULSE_CLR |
	      AM35XX_CPGMAC_C0_MISC_PULSE_CLR | AM35XX_CPGMAC_C0_RX_THRESH_CLR);
	omap_ctrl_ग_लिखोl(v, AM35XX_CONTROL_LVL_INTR_CLEAR);
	omap_ctrl_पढ़ोl(AM35XX_CONTROL_LVL_INTR_CLEAR); /* OCP barrier */
पूर्ण

अटल व्योम am35xx_disable_emac_पूर्णांक(व्योम)
अणु
	u32 v;

	v = omap_ctrl_पढ़ोl(AM35XX_CONTROL_LVL_INTR_CLEAR);
	v |= (AM35XX_CPGMAC_C0_RX_PULSE_CLR | AM35XX_CPGMAC_C0_TX_PULSE_CLR);
	omap_ctrl_ग_लिखोl(v, AM35XX_CONTROL_LVL_INTR_CLEAR);
	omap_ctrl_पढ़ोl(AM35XX_CONTROL_LVL_INTR_CLEAR); /* OCP barrier */
पूर्ण

अटल काष्ठा emac_platक्रमm_data am35xx_emac_pdata = अणु
	.पूर्णांकerrupt_enable	= am35xx_enable_emac_पूर्णांक,
	.पूर्णांकerrupt_disable	= am35xx_disable_emac_पूर्णांक,
पूर्ण;

अटल व्योम __init am35xx_emac_reset(व्योम)
अणु
	u32 v;

	v = omap_ctrl_पढ़ोl(AM35XX_CONTROL_IP_SW_RESET);
	v &= ~AM35XX_CPGMACSS_SW_RST;
	omap_ctrl_ग_लिखोl(v, AM35XX_CONTROL_IP_SW_RESET);
	omap_ctrl_पढ़ोl(AM35XX_CONTROL_IP_SW_RESET); /* OCP barrier */
पूर्ण

अटल काष्ठा gpio cm_t3517_wlan_gpios[] __initdata = अणु
	अणु 56,	GPIOF_OUT_INIT_HIGH,	"wlan pwr" पूर्ण,
	अणु 4,	GPIOF_OUT_INIT_HIGH,	"xcvr noe" पूर्ण,
पूर्ण;

अटल व्योम __init omap3_sbc_t3517_wअगरi_init(व्योम)
अणु
	पूर्णांक err = gpio_request_array(cm_t3517_wlan_gpios,
				ARRAY_SIZE(cm_t3517_wlan_gpios));
	अगर (err) अणु
		pr_err("SBC-T3517: wl12xx gpios request failed: %d\n", err);
		वापस;
	पूर्ण

	gpio_export(cm_t3517_wlan_gpios[0].gpio, 0);
	gpio_export(cm_t3517_wlan_gpios[1].gpio, 0);

	msleep(100);
	gpio_set_value(cm_t3517_wlan_gpios[1].gpio, 0);
पूर्ण

अटल व्योम __init omap3_sbc_t3517_legacy_init(व्योम)
अणु
	omap3_sbc_t3x_usb_hub_init(152, "cm-t3517 usb hub");
	omap3_sbc_t3x_usb_hub_init(98, "sb-t35 usb hub");
	am35xx_emac_reset();
	hsmmc2_पूर्णांकernal_input_clk();
	omap3_sbc_t3517_wअगरi_init();
पूर्ण

अटल व्योम __init am3517_evm_legacy_init(व्योम)
अणु
	am35xx_emac_reset();
पूर्ण

अटल व्योम __init nokia_n900_legacy_init(व्योम)
अणु
	hsmmc2_पूर्णांकernal_input_clk();
	mmc_pdata[0].name = "external";
	mmc_pdata[1].name = "internal";

	अगर (omap_type() != OMAP2_DEVICE_TYPE_GP) अणु
		अगर (IS_ENABLED(CONFIG_ARM_ERRATA_430973)) अणु
			pr_info("RX-51: Enabling ARM errata 430973 workaround\n");
			/* set IBE to 1 */
			rx51_secure_update_aux_cr(BIT(6), 0);
		पूर्ण अन्यथा अणु
			pr_warn("RX-51: Not enabling ARM errata 430973 workaround\n");
			pr_warn("Thumb binaries may crash randomly without this workaround\n");
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम __init omap3_tao3530_legacy_init(व्योम)
अणु
	hsmmc2_पूर्णांकernal_input_clk();
पूर्ण

अटल व्योम __init omap3_logicpd_torpeकरो_init(व्योम)
अणु
	omap3_gpio126_127_129();
पूर्ण

/* omap3panकरोra legacy devices */

अटल काष्ठा platक्रमm_device panकरोra_backlight = अणु
	.name	= "pandora-backlight",
	.id	= -1,
पूर्ण;

अटल व्योम __init omap3_panकरोra_legacy_init(व्योम)
अणु
	platक्रमm_device_रेजिस्टर(&panकरोra_backlight);
पूर्ण
#पूर्ण_अगर /* CONFIG_ARCH_OMAP3 */

#अगर_घोषित CONFIG_SOC_OMAP5
अटल व्योम __init omap5_uevm_legacy_init(व्योम)
अणु
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_SOC_DRA7XX
अटल काष्ठा iommu_platक्रमm_data dra7_ipu1_dsp_iommu_pdata = अणु
	.set_pwrdm_स्थिरraपूर्णांक = omap_iommu_set_pwrdm_स्थिरraपूर्णांक,
पूर्ण;

अटल काष्ठा omap_hsmmc_platक्रमm_data dra7_hsmmc_data_mmc1;
अटल काष्ठा omap_hsmmc_platक्रमm_data dra7_hsmmc_data_mmc2;
अटल काष्ठा omap_hsmmc_platक्रमm_data dra7_hsmmc_data_mmc3;

अटल व्योम __init dra7x_evm_mmc_quirk(व्योम)
अणु
	अगर (omap_rev() == DRA752_REV_ES1_1 || omap_rev() == DRA752_REV_ES1_0) अणु
		dra7_hsmmc_data_mmc1.version = "rev11";
		dra7_hsmmc_data_mmc1.max_freq = 96000000;

		dra7_hsmmc_data_mmc2.version = "rev11";
		dra7_hsmmc_data_mmc2.max_freq = 48000000;

		dra7_hsmmc_data_mmc3.version = "rev11";
		dra7_hsmmc_data_mmc3.max_freq = 48000000;
	पूर्ण
पूर्ण
#पूर्ण_अगर

अटल काष्ठा घड़ीकरोमुख्य *ti_sysc_find_one_घड़ीकरोमुख्य(काष्ठा clk *clk)
अणु
	काष्ठा clk_hw *hw = __clk_get_hw(clk);
	काष्ठा घड़ीकरोमुख्य *clkdm = शून्य;
	काष्ठा clk_hw_omap *hwclk;

	hwclk = to_clk_hw_omap(hw);
	अगर (!omap2_clk_is_hw_omap(hw))
		वापस शून्य;

	अगर (hwclk && hwclk->clkdm_name)
		clkdm = clkdm_lookup(hwclk->clkdm_name);

	वापस clkdm;
पूर्ण

/**
 * ti_sysc_clkdm_init - find घड़ीकरोमुख्य based on घड़ी
 * @fck: device functional घड़ी
 * @ick: device पूर्णांकerface घड़ी
 * @dev: काष्ठा device
 *
 * Populate घड़ीकरोमुख्य based on घड़ी. It is needed क्रम
 * clkdm_deny_idle() and clkdm_allow_idle() क्रम blocking घड़ीकरोमुख्य
 * घड़ीकरोमुख्य idle during reset, enable and idle.
 *
 * Note that we assume पूर्णांकerconnect driver manages the घड़ीs
 * and करो not need to populate oh->_clk क्रम dynamically
 * allocated modules.
 */
अटल पूर्णांक ti_sysc_clkdm_init(काष्ठा device *dev,
			      काष्ठा clk *fck, काष्ठा clk *ick,
			      काष्ठा ti_sysc_cookie *cookie)
अणु
	अगर (!IS_ERR(fck))
		cookie->clkdm = ti_sysc_find_one_घड़ीकरोमुख्य(fck);
	अगर (cookie->clkdm)
		वापस 0;
	अगर (!IS_ERR(ick))
		cookie->clkdm = ti_sysc_find_one_घड़ीकरोमुख्य(ick);
	अगर (cookie->clkdm)
		वापस 0;

	वापस -ENODEV;
पूर्ण

अटल व्योम ti_sysc_clkdm_deny_idle(काष्ठा device *dev,
				    स्थिर काष्ठा ti_sysc_cookie *cookie)
अणु
	अगर (cookie->clkdm)
		clkdm_deny_idle(cookie->clkdm);
पूर्ण

अटल व्योम ti_sysc_clkdm_allow_idle(काष्ठा device *dev,
				     स्थिर काष्ठा ti_sysc_cookie *cookie)
अणु
	अगर (cookie->clkdm)
		clkdm_allow_idle(cookie->clkdm);
पूर्ण

#अगर_घोषित CONFIG_OMAP_HWMOD
अटल पूर्णांक ti_sysc_enable_module(काष्ठा device *dev,
				 स्थिर काष्ठा ti_sysc_cookie *cookie)
अणु
	अगर (!cookie->data)
		वापस -EINVAL;

	वापस omap_hwmod_enable(cookie->data);
पूर्ण

अटल पूर्णांक ti_sysc_idle_module(काष्ठा device *dev,
			       स्थिर काष्ठा ti_sysc_cookie *cookie)
अणु
	अगर (!cookie->data)
		वापस -EINVAL;

	वापस omap_hwmod_idle(cookie->data);
पूर्ण

अटल पूर्णांक ti_sysc_shutकरोwn_module(काष्ठा device *dev,
				   स्थिर काष्ठा ti_sysc_cookie *cookie)
अणु
	अगर (!cookie->data)
		वापस -EINVAL;

	वापस omap_hwmod_shutकरोwn(cookie->data);
पूर्ण
#पूर्ण_अगर	/* CONFIG_OMAP_HWMOD */

अटल bool ti_sysc_soc_type_gp(व्योम)
अणु
	वापस omap_type() == OMAP2_DEVICE_TYPE_GP;
पूर्ण

अटल काष्ठा of_dev_auxdata omap_auxdata_lookup[];

अटल काष्ठा ti_sysc_platक्रमm_data ti_sysc_pdata = अणु
	.auxdata = omap_auxdata_lookup,
	.soc_type_gp = ti_sysc_soc_type_gp,
	.init_घड़ीकरोमुख्य = ti_sysc_clkdm_init,
	.clkdm_deny_idle = ti_sysc_clkdm_deny_idle,
	.clkdm_allow_idle = ti_sysc_clkdm_allow_idle,
#अगर_घोषित CONFIG_OMAP_HWMOD
	.init_module = omap_hwmod_init_module,
	.enable_module = ti_sysc_enable_module,
	.idle_module = ti_sysc_idle_module,
	.shutकरोwn_module = ti_sysc_shutकरोwn_module,
#पूर्ण_अगर
पूर्ण;

अटल काष्ठा pcs_pdata pcs_pdata;

व्योम omap_pcs_legacy_init(पूर्णांक irq, व्योम (*rearm)(व्योम))
अणु
	pcs_pdata.irq = irq;
	pcs_pdata.rearm = rearm;
पूर्ण

अटल काष्ठा ti_prm_platक्रमm_data ti_prm_pdata = अणु
	.clkdm_deny_idle = clkdm_deny_idle,
	.clkdm_allow_idle = clkdm_allow_idle,
	.clkdm_lookup = clkdm_lookup,
पूर्ण;

/*
 * GPIOs क्रम TWL are initialized by the I2C bus and need custom
 * handing until DSS has device tree bindings.
 */
व्योम omap_auxdata_legacy_init(काष्ठा device *dev)
अणु
	अगर (dev->platक्रमm_data)
		वापस;

	अगर (म_भेद("twl4030-gpio", dev_name(dev)))
		वापस;

	dev->platक्रमm_data = &twl_gpio_auxdata;
पूर्ण

#अगर defined(CONFIG_ARCH_OMAP3) && IS_ENABLED(CONFIG_SND_SOC_OMAP_MCBSP)
अटल काष्ठा omap_mcbsp_platक्रमm_data mcbsp_pdata;
अटल व्योम __init omap3_mcbsp_init(व्योम)
अणु
	omap3_mcbsp_init_pdata_callback(&mcbsp_pdata);
पूर्ण
#अन्यथा
अटल व्योम __init omap3_mcbsp_init(व्योम) अणुपूर्ण
#पूर्ण_अगर

/*
 * Few boards still need auxdata populated beक्रमe we populate
 * the dev entries in of_platक्रमm_populate().
 */
अटल काष्ठा pdata_init auxdata_quirks[] __initdata = अणु
#अगर_घोषित CONFIG_SOC_OMAP2420
	अणु "nokia,n800", omap2420_n8x0_legacy_init, पूर्ण,
	अणु "nokia,n810", omap2420_n8x0_legacy_init, पूर्ण,
	अणु "nokia,n810-wimax", omap2420_n8x0_legacy_init, पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_ARCH_OMAP3
	अणु "compulab,omap3-sbc-t3730", omap3_sbc_t3730_twl_init, पूर्ण,
#पूर्ण_अगर
	अणु /* sentinel */ पूर्ण,
पूर्ण;

काष्ठा omap_sr_data __maybe_unused omap_sr_pdata[OMAP_SR_NR];

अटल काष्ठा of_dev_auxdata omap_auxdata_lookup[] = अणु
#अगर_घोषित CONFIG_MACH_NOKIA_N8X0
	OF_DEV_AUXDATA("ti,omap2420-mmc", 0x4809c000, "mmci-omap.0", शून्य),
	OF_DEV_AUXDATA("menelaus", 0x72, "1-0072", &n8x0_menelaus_platक्रमm_data),
	OF_DEV_AUXDATA("tlv320aic3x", 0x18, "2-0018", &n810_aic33_data),
#पूर्ण_अगर
#अगर_घोषित CONFIG_ARCH_OMAP3
	OF_DEV_AUXDATA("ti,omap2-iommu", 0x5d000000, "5d000000.mmu",
		       &omap3_iommu_pdata),
	OF_DEV_AUXDATA("ti,omap2-iommu", 0x480bd400, "480bd400.mmu",
		       &omap3_iommu_isp_pdata),
	OF_DEV_AUXDATA("ti,omap3-smartreflex-core", 0x480cb000,
		       "480cb000.smartreflex", &omap_sr_pdata[OMAP_SR_CORE]),
	OF_DEV_AUXDATA("ti,omap3-smartreflex-mpu-iva", 0x480c9000,
		       "480c9000.smartreflex", &omap_sr_pdata[OMAP_SR_MPU]),
	OF_DEV_AUXDATA("ti,omap3-hsmmc", 0x4809c000, "4809c000.mmc", &mmc_pdata[0]),
	OF_DEV_AUXDATA("ti,omap3-hsmmc", 0x480b4000, "480b4000.mmc", &mmc_pdata[1]),
	/* Only on am3517 */
	OF_DEV_AUXDATA("ti,davinci_mdio", 0x5c030000, "davinci_mdio.0", शून्य),
	OF_DEV_AUXDATA("ti,am3517-emac", 0x5c000000, "davinci_emac.0",
		       &am35xx_emac_pdata),
	OF_DEV_AUXDATA("nokia,n900-rom-rng", 0, शून्य, rx51_secure_rng_call),
	/* McBSP modules with sidetone core */
#अगर IS_ENABLED(CONFIG_SND_SOC_OMAP_MCBSP)
	OF_DEV_AUXDATA("ti,omap3-mcbsp", 0x49022000, "49022000.mcbsp", &mcbsp_pdata),
	OF_DEV_AUXDATA("ti,omap3-mcbsp", 0x49024000, "49024000.mcbsp", &mcbsp_pdata),
#पूर्ण_अगर
#पूर्ण_अगर
#अगर defined(CONFIG_ARCH_OMAP4) || defined(CONFIG_SOC_OMAP5)
	OF_DEV_AUXDATA("ti,omap4-smartreflex-iva", 0x4a0db000,
		       "4a0db000.smartreflex", &omap_sr_pdata[OMAP_SR_IVA]),
	OF_DEV_AUXDATA("ti,omap4-smartreflex-core", 0x4a0dd000,
		       "4a0dd000.smartreflex", &omap_sr_pdata[OMAP_SR_CORE]),
	OF_DEV_AUXDATA("ti,omap4-smartreflex-mpu", 0x4a0d9000,
		       "4a0d9000.smartreflex", &omap_sr_pdata[OMAP_SR_MPU]),
#पूर्ण_अगर
#अगर_घोषित CONFIG_SOC_DRA7XX
	OF_DEV_AUXDATA("ti,dra7-hsmmc", 0x4809c000, "4809c000.mmc",
		       &dra7_hsmmc_data_mmc1),
	OF_DEV_AUXDATA("ti,dra7-hsmmc", 0x480b4000, "480b4000.mmc",
		       &dra7_hsmmc_data_mmc2),
	OF_DEV_AUXDATA("ti,dra7-hsmmc", 0x480ad000, "480ad000.mmc",
		       &dra7_hsmmc_data_mmc3),
	OF_DEV_AUXDATA("ti,dra7-dsp-iommu", 0x40d01000, "40d01000.mmu",
		       &dra7_ipu1_dsp_iommu_pdata),
	OF_DEV_AUXDATA("ti,dra7-dsp-iommu", 0x41501000, "41501000.mmu",
		       &dra7_ipu1_dsp_iommu_pdata),
	OF_DEV_AUXDATA("ti,dra7-iommu", 0x58882000, "58882000.mmu",
		       &dra7_ipu1_dsp_iommu_pdata),
#पूर्ण_अगर
	/* Common auxdata */
	OF_DEV_AUXDATA("simple-pm-bus", 0, शून्य, omap_auxdata_lookup),
	OF_DEV_AUXDATA("ti,sysc", 0, शून्य, &ti_sysc_pdata),
	OF_DEV_AUXDATA("pinctrl-single", 0, शून्य, &pcs_pdata),
	OF_DEV_AUXDATA("ti,omap-prm-inst", 0, शून्य, &ti_prm_pdata),
	OF_DEV_AUXDATA("ti,omap-sdma", 0, शून्य, &dma_plat_info),
	अणु /* sentinel */ पूर्ण,
पूर्ण;

/*
 * Few boards still need to initialize some legacy devices with
 * platक्रमm data until the drivers support device tree.
 */
अटल काष्ठा pdata_init pdata_quirks[] __initdata = अणु
#अगर_घोषित CONFIG_ARCH_OMAP3
	अणु "compulab,omap3-sbc-t3517", omap3_sbc_t3517_legacy_init, पूर्ण,
	अणु "compulab,omap3-sbc-t3530", omap3_sbc_t3530_legacy_init, पूर्ण,
	अणु "compulab,omap3-sbc-t3730", omap3_sbc_t3730_legacy_init, पूर्ण,
	अणु "nokia,omap3-n900", nokia_n900_legacy_init, पूर्ण,
	अणु "nokia,omap3-n9", hsmmc2_पूर्णांकernal_input_clk, पूर्ण,
	अणु "nokia,omap3-n950", hsmmc2_पूर्णांकernal_input_clk, पूर्ण,
	अणु "logicpd,dm3730-torpedo-devkit", omap3_logicpd_torpeकरो_init, पूर्ण,
	अणु "ti,omap3-evm-37xx", omap3_evm_legacy_init, पूर्ण,
	अणु "ti,am3517-evm", am3517_evm_legacy_init, पूर्ण,
	अणु "technexion,omap3-tao3530", omap3_tao3530_legacy_init, पूर्ण,
	अणु "openpandora,omap3-pandora-600mhz", omap3_panकरोra_legacy_init, पूर्ण,
	अणु "openpandora,omap3-pandora-1ghz", omap3_panकरोra_legacy_init, पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_SOC_OMAP5
	अणु "ti,omap5-uevm", omap5_uevm_legacy_init, पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_SOC_DRA7XX
	अणु "ti,dra7-evm", dra7x_evm_mmc_quirk, पूर्ण,
#पूर्ण_अगर
	अणु /* sentinel */ पूर्ण,
पूर्ण;

अटल व्योम pdata_quirks_check(काष्ठा pdata_init *quirks)
अणु
	जबतक (quirks->compatible) अणु
		अगर (of_machine_is_compatible(quirks->compatible)) अणु
			अगर (quirks->fn)
				quirks->fn();
		पूर्ण
		quirks++;
	पूर्ण
पूर्ण

अटल स्थिर अक्षर * स्थिर pdata_quirks_init_nodes[] = अणु
	"prcm",
	"prm",
पूर्ण;

अटल व्योम __init
pdata_quirks_init_घड़ीs(स्थिर काष्ठा of_device_id *omap_dt_match_table)
अणु
	काष्ठा device_node *np;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(pdata_quirks_init_nodes); i++) अणु
		np = of_find_node_by_name(शून्य, pdata_quirks_init_nodes[i]);
		अगर (!np)
			जारी;

		of_platक्रमm_populate(np, omap_dt_match_table,
				     omap_auxdata_lookup, शून्य);
	पूर्ण
पूर्ण

व्योम __init pdata_quirks_init(स्थिर काष्ठा of_device_id *omap_dt_match_table)
अणु
	/*
	 * We still need this क्रम omap2420 and omap3 PM to work, others are
	 * using drivers/misc/sram.c alपढ़ोy.
	 */
	अगर (of_machine_is_compatible("ti,omap2420") ||
	    of_machine_is_compatible("ti,omap3"))
		omap_sdrc_init(शून्य, शून्य);

	अगर (of_machine_is_compatible("ti,omap3"))
		omap3_mcbsp_init();
	pdata_quirks_check(auxdata_quirks);

	pdata_quirks_init_घड़ीs(omap_dt_match_table);

	of_platक्रमm_populate(शून्य, omap_dt_match_table,
			     omap_auxdata_lookup, शून्य);
	pdata_quirks_check(pdata_quirks);
पूर्ण
