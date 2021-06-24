<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित __TI_SYSC_DATA_H__
#घोषणा __TI_SYSC_DATA_H__

क्रमागत ti_sysc_module_type अणु
	TI_SYSC_OMAP2,
	TI_SYSC_OMAP2_TIMER,
	TI_SYSC_OMAP3_SHAM,
	TI_SYSC_OMAP3_AES,
	TI_SYSC_OMAP4,
	TI_SYSC_OMAP4_TIMER,
	TI_SYSC_OMAP4_SIMPLE,
	TI_SYSC_OMAP34XX_SR,
	TI_SYSC_OMAP36XX_SR,
	TI_SYSC_OMAP4_SR,
	TI_SYSC_OMAP4_MCASP,
	TI_SYSC_OMAP4_USB_HOST_FS,
	TI_SYSC_DRA7_MCAN,
	TI_SYSC_PRUSS,
पूर्ण;

काष्ठा ti_sysc_cookie अणु
	व्योम *data;
	व्योम *clkdm;
पूर्ण;

/**
 * काष्ठा sysc_regbits - TI OCP_SYSCONFIG रेजिस्टर field offsets
 * @midle_shअगरt: Offset of the midle bit
 * @clkact_shअगरt: Offset of the घड़ीactivity bit
 * @sidle_shअगरt: Offset of the sidle bit
 * @enwkup_shअगरt: Offset of the enawakeup bit
 * @srst_shअगरt: Offset of the softreset bit
 * @स्वतःidle_shअगरt: Offset of the स्वतःidle bit
 * @dmadisable_shअगरt: Offset of the dmadisable bit
 * @emuमुक्त_shअगरt; Offset of the emuमुक्त bit
 *
 * Note that 0 is a valid shअगरt, and क्रम ti-sysc.c -ENODEV can be used अगर a
 * feature is not available.
 */
काष्ठा sysc_regbits अणु
	s8 midle_shअगरt;
	s8 clkact_shअगरt;
	s8 sidle_shअगरt;
	s8 enwkup_shअगरt;
	s8 srst_shअगरt;
	s8 स्वतःidle_shअगरt;
	s8 dmadisable_shअगरt;
	s8 emuमुक्त_shअगरt;
पूर्ण;

#घोषणा SYSC_QUIRK_REINIT_ON_RESUME	BIT(27)
#घोषणा SYSC_QUIRK_GPMC_DEBUG		BIT(26)
#घोषणा SYSC_MODULE_QUIRK_ENA_RESETDONE	BIT(25)
#घोषणा SYSC_MODULE_QUIRK_PRUSS		BIT(24)
#घोषणा SYSC_MODULE_QUIRK_DSS_RESET	BIT(23)
#घोषणा SYSC_MODULE_QUIRK_RTC_UNLOCK	BIT(22)
#घोषणा SYSC_QUIRK_CLKDM_NOAUTO		BIT(21)
#घोषणा SYSC_QUIRK_FORCE_MSTANDBY	BIT(20)
#घोषणा SYSC_MODULE_QUIRK_AESS		BIT(19)
#घोषणा SYSC_MODULE_QUIRK_SGX		BIT(18)
#घोषणा SYSC_MODULE_QUIRK_HDQ1W		BIT(17)
#घोषणा SYSC_MODULE_QUIRK_I2C		BIT(16)
#घोषणा SYSC_MODULE_QUIRK_WDT		BIT(15)
#घोषणा SYSS_QUIRK_RESETDONE_INVERTED	BIT(14)
#घोषणा SYSC_QUIRK_SWSUP_MSTANDBY	BIT(13)
#घोषणा SYSC_QUIRK_SWSUP_SIDLE_ACT	BIT(12)
#घोषणा SYSC_QUIRK_SWSUP_SIDLE		BIT(11)
#घोषणा SYSC_QUIRK_EXT_OPT_CLOCK	BIT(10)
#घोषणा SYSC_QUIRK_LEGACY_IDLE		BIT(9)
#घोषणा SYSC_QUIRK_RESET_STATUS		BIT(8)
#घोषणा SYSC_QUIRK_NO_IDLE		BIT(7)
#घोषणा SYSC_QUIRK_NO_IDLE_ON_INIT	BIT(6)
#घोषणा SYSC_QUIRK_NO_RESET_ON_INIT	BIT(5)
#घोषणा SYSC_QUIRK_OPT_CLKS_NEEDED	BIT(4)
#घोषणा SYSC_QUIRK_OPT_CLKS_IN_RESET	BIT(3)
#घोषणा SYSC_QUIRK_16BIT		BIT(2)
#घोषणा SYSC_QUIRK_UNCACHED		BIT(1)
#घोषणा SYSC_QUIRK_USE_CLOCKACT		BIT(0)

#घोषणा SYSC_NR_IDLEMODES		4

/**
 * काष्ठा sysc_capabilities - capabilities क्रम an पूर्णांकerconnect target module
 * @type: sysc type identअगरier क्रम the module
 * @sysc_mask: biपंचांगask of supported SYSCONFIG रेजिस्टर bits
 * @regbits: biपंचांगask of SYSCONFIG रेजिस्टर bits
 * @mod_quirks: biपंचांगask of module specअगरic quirks
 */
काष्ठा sysc_capabilities अणु
	स्थिर क्रमागत ti_sysc_module_type type;
	स्थिर u32 sysc_mask;
	स्थिर काष्ठा sysc_regbits *regbits;
	स्थिर u32 mod_quirks;
पूर्ण;

/**
 * काष्ठा sysc_config - configuration क्रम an पूर्णांकerconnect target module
 * @sysc_val: configured value क्रम sysc रेजिस्टर
 * @syss_mask: configured mask value क्रम SYSSTATUS रेजिस्टर
 * @midlemodes: biपंचांगask of supported master idle modes
 * @sidlemodes: biपंचांगask of supported slave idle modes
 * @srst_udelay: optional delay needed after OCP soft reset
 * @quirks: biपंचांगask of enabled quirks
 */
काष्ठा sysc_config अणु
	u32 sysc_val;
	u32 syss_mask;
	u8 midlemodes;
	u8 sidlemodes;
	u8 srst_udelay;
	u32 quirks;
पूर्ण;

क्रमागत sysc_रेजिस्टरs अणु
	SYSC_REVISION,
	SYSC_SYSCONFIG,
	SYSC_SYSSTATUS,
	SYSC_MAX_REGS,
पूर्ण;

/**
 * काष्ठा ti_sysc_module_data - ti-sysc to hwmod translation data क्रम a module
 * @name: legacy "ti,hwmods" module name
 * @module_pa: physical address of the पूर्णांकerconnect target module
 * @module_size: size of the पूर्णांकerconnect target module
 * @offsets: array of रेजिस्टर offsets as listed in क्रमागत sysc_रेजिस्टरs
 * @nr_offsets: number of रेजिस्टरs
 * @cap: पूर्णांकerconnect target module capabilities
 * @cfg: पूर्णांकerconnect target module configuration
 *
 * This data is enough to allocate a new काष्ठा omap_hwmod_class_sysconfig
 * based on device tree data parsed by ti-sysc driver.
 */
काष्ठा ti_sysc_module_data अणु
	स्थिर अक्षर *name;
	u64 module_pa;
	u32 module_size;
	पूर्णांक *offsets;
	पूर्णांक nr_offsets;
	स्थिर काष्ठा sysc_capabilities *cap;
	काष्ठा sysc_config *cfg;
पूर्ण;

काष्ठा device;
काष्ठा clk;

काष्ठा ti_sysc_platक्रमm_data अणु
	काष्ठा of_dev_auxdata *auxdata;
	bool (*soc_type_gp)(व्योम);
	पूर्णांक (*init_घड़ीकरोमुख्य)(काष्ठा device *dev, काष्ठा clk *fck,
				काष्ठा clk *ick, काष्ठा ti_sysc_cookie *cookie);
	व्योम (*clkdm_deny_idle)(काष्ठा device *dev,
				स्थिर काष्ठा ti_sysc_cookie *cookie);
	व्योम (*clkdm_allow_idle)(काष्ठा device *dev,
				 स्थिर काष्ठा ti_sysc_cookie *cookie);
	पूर्णांक (*init_module)(काष्ठा device *dev,
			   स्थिर काष्ठा ti_sysc_module_data *data,
			   काष्ठा ti_sysc_cookie *cookie);
	पूर्णांक (*enable_module)(काष्ठा device *dev,
			     स्थिर काष्ठा ti_sysc_cookie *cookie);
	पूर्णांक (*idle_module)(काष्ठा device *dev,
			   स्थिर काष्ठा ti_sysc_cookie *cookie);
	पूर्णांक (*shutकरोwn_module)(काष्ठा device *dev,
			       स्थिर काष्ठा ti_sysc_cookie *cookie);
पूर्ण;

#पूर्ण_अगर	/* __TI_SYSC_DATA_H__ */
