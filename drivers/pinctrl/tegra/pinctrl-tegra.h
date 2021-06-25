<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Driver क्रम the NVIDIA Tegra pinmux
 *
 * Copyright (c) 2011, NVIDIA CORPORATION.  All rights reserved.
 */

#अगर_अघोषित __PINMUX_TEGRA_H__
#घोषणा __PINMUX_TEGRA_H__

काष्ठा tegra_pmx अणु
	काष्ठा device *dev;
	काष्ठा pinctrl_dev *pctl;

	स्थिर काष्ठा tegra_pinctrl_soc_data *soc;
	स्थिर अक्षर **group_pins;

	पूर्णांक nbanks;
	व्योम __iomem **regs;
	u32 *backup_regs;
पूर्ण;

क्रमागत tegra_pinconf_param अणु
	/* argument: tegra_pinconf_pull */
	TEGRA_PINCONF_PARAM_PULL,
	/* argument: tegra_pinconf_tristate */
	TEGRA_PINCONF_PARAM_TRISTATE,
	/* argument: Boolean */
	TEGRA_PINCONF_PARAM_ENABLE_INPUT,
	/* argument: Boolean */
	TEGRA_PINCONF_PARAM_OPEN_DRAIN,
	/* argument: Boolean */
	TEGRA_PINCONF_PARAM_LOCK,
	/* argument: Boolean */
	TEGRA_PINCONF_PARAM_IORESET,
	/* argument: Boolean */
	TEGRA_PINCONF_PARAM_RCV_SEL,
	/* argument: Boolean */
	TEGRA_PINCONF_PARAM_HIGH_SPEED_MODE,
	/* argument: Boolean */
	TEGRA_PINCONF_PARAM_SCHMITT,
	/* argument: Boolean */
	TEGRA_PINCONF_PARAM_LOW_POWER_MODE,
	/* argument: Integer, range is HW-dependant */
	TEGRA_PINCONF_PARAM_DRIVE_DOWN_STRENGTH,
	/* argument: Integer, range is HW-dependant */
	TEGRA_PINCONF_PARAM_DRIVE_UP_STRENGTH,
	/* argument: Integer, range is HW-dependant */
	TEGRA_PINCONF_PARAM_SLEW_RATE_FALLING,
	/* argument: Integer, range is HW-dependant */
	TEGRA_PINCONF_PARAM_SLEW_RATE_RISING,
	/* argument: Integer, range is HW-dependant */
	TEGRA_PINCONF_PARAM_DRIVE_TYPE,
पूर्ण;

क्रमागत tegra_pinconf_pull अणु
	TEGRA_PINCONFIG_PULL_NONE,
	TEGRA_PINCONFIG_PULL_DOWN,
	TEGRA_PINCONFIG_PULL_UP,
पूर्ण;

क्रमागत tegra_pinconf_tristate अणु
	TEGRA_PINCONFIG_DRIVEN,
	TEGRA_PINCONFIG_TRISTATE,
पूर्ण;

#घोषणा TEGRA_PINCONF_PACK(_param_, _arg_) ((_param_) << 16 | (_arg_))
#घोषणा TEGRA_PINCONF_UNPACK_PARAM(_conf_) ((_conf_) >> 16)
#घोषणा TEGRA_PINCONF_UNPACK_ARG(_conf_) ((_conf_) & 0xffff)

/**
 * काष्ठा tegra_function - Tegra pinctrl mux function
 * @name: The name of the function, exported to pinctrl core.
 * @groups: An array of pin groups that may select this function.
 * @ngroups: The number of entries in @groups.
 */
काष्ठा tegra_function अणु
	स्थिर अक्षर *name;
	स्थिर अक्षर **groups;
	अचिन्हित ngroups;
पूर्ण;

/**
 * काष्ठा tegra_pingroup - Tegra pin group
 * @name		The name of the pin group.
 * @pins		An array of pin IDs included in this pin group.
 * @npins		The number of entries in @pins.
 * @funcs		The mux functions which can be muxed onto this group.
 * @mux_reg:		Mux रेजिस्टर offset.
 *			This रेजिस्टर contains the mux, einput, odrain, lock,
 *			ioreset, rcv_sel parameters.
 * @mux_bank:		Mux रेजिस्टर bank.
 * @mux_bit:		Mux रेजिस्टर bit.
 * @pupd_reg:		Pull-up/करोwn रेजिस्टर offset.
 * @pupd_bank:		Pull-up/करोwn रेजिस्टर bank.
 * @pupd_bit:		Pull-up/करोwn रेजिस्टर bit.
 * @tri_reg:		Tri-state रेजिस्टर offset.
 * @tri_bank:		Tri-state रेजिस्टर bank.
 * @tri_bit:		Tri-state रेजिस्टर bit.
 * @einput_bit:		Enable-input रेजिस्टर bit.
 * @odrain_bit:		Open-drain रेजिस्टर bit.
 * @lock_bit:		Lock रेजिस्टर bit.
 * @ioreset_bit:	IO reset रेजिस्टर bit.
 * @rcv_sel_bit:	Receiver select bit.
 * @drv_reg:		Drive fields रेजिस्टर offset.
 *			This रेजिस्टर contains hsm, schmitt, lpmd, drvdn,
 *			drvup, slwr, slwf, and drvtype parameters.
 * @drv_bank:		Drive fields रेजिस्टर bank.
 * @hsm_bit:		High Speed Mode रेजिस्टर bit.
 * @sfsel_bit:		GPIO/SFIO selection रेजिस्टर bit.
 * @schmitt_bit:	Schmitt रेजिस्टर bit.
 * @lpmd_bit:		Low Power Mode रेजिस्टर bit.
 * @drvdn_bit:		Drive Down रेजिस्टर bit.
 * @drvdn_width:	Drive Down field width.
 * @drvup_bit:		Drive Up रेजिस्टर bit.
 * @drvup_width:	Drive Up field width.
 * @slwr_bit:		Slew Rising रेजिस्टर bit.
 * @slwr_width:		Slew Rising field width.
 * @slwf_bit:		Slew Falling रेजिस्टर bit.
 * @slwf_width:		Slew Falling field width.
 * @drvtype_bit:	Drive type रेजिस्टर bit.
 * @parked_biपंचांगask:	Parked रेजिस्टर mask. 0 अगर unsupported.
 *
 * -1 in a *_reg field means that feature is unsupported क्रम this group.
 * *_bank and *_reg values are irrelevant when *_reg is -1.
 * When *_reg is valid, *_bit may be -1 to indicate an unsupported feature.
 *
 * A representation of a group of pins (possibly just one pin) in the Tegra
 * pin controller. Each group allows some parameter or parameters to be
 * configured. The most common is mux function selection. Many others exist
 * such as pull-up/करोwn, tri-state, etc. Tegra's pin controller is complex;
 * certain groups may only support configuring certain parameters, hence
 * each parameter is optional.
 */
काष्ठा tegra_pingroup अणु
	स्थिर अक्षर *name;
	स्थिर अचिन्हित *pins;
	u8 npins;
	u8 funcs[4];
	s32 mux_reg;
	s32 pupd_reg;
	s32 tri_reg;
	s32 drv_reg;
	u32 mux_bank:2;
	u32 pupd_bank:2;
	u32 tri_bank:2;
	u32 drv_bank:2;
	s32 mux_bit:6;
	s32 pupd_bit:6;
	s32 tri_bit:6;
	s32 einput_bit:6;
	s32 odrain_bit:6;
	s32 lock_bit:6;
	s32 ioreset_bit:6;
	s32 rcv_sel_bit:6;
	s32 hsm_bit:6;
	s32 sfsel_bit:6;
	s32 schmitt_bit:6;
	s32 lpmd_bit:6;
	s32 drvdn_bit:6;
	s32 drvup_bit:6;
	s32 slwr_bit:6;
	s32 slwf_bit:6;
	s32 drvtype_bit:6;
	s32 drvdn_width:6;
	s32 drvup_width:6;
	s32 slwr_width:6;
	s32 slwf_width:6;
	u32 parked_biपंचांगask;
पूर्ण;

/**
 * काष्ठा tegra_pinctrl_soc_data - Tegra pin controller driver configuration
 * @ngpios:	The number of GPIO pins the pin controller HW affects.
 * @pins:	An array describing all pins the pin controller affects.
 *		All pins which are also GPIOs must be listed first within the
 *		array, and be numbered identically to the GPIO controller's
 *		numbering.
 * @npins:	The numbmer of entries in @pins.
 * @functions:	An array describing all mux functions the SoC supports.
 * @nfunctions:	The numbmer of entries in @functions.
 * @groups:	An array describing all pin groups the pin SoC supports.
 * @ngroups:	The numbmer of entries in @groups.
 */
काष्ठा tegra_pinctrl_soc_data अणु
	अचिन्हित ngpios;
	स्थिर अक्षर *gpio_compatible;
	स्थिर काष्ठा pinctrl_pin_desc *pins;
	अचिन्हित npins;
	काष्ठा tegra_function *functions;
	अचिन्हित nfunctions;
	स्थिर काष्ठा tegra_pingroup *groups;
	अचिन्हित ngroups;
	bool hsm_in_mux;
	bool schmitt_in_mux;
	bool drvtype_in_mux;
	bool sfsel_in_mux;
पूर्ण;

बाह्य स्थिर काष्ठा dev_pm_ops tegra_pinctrl_pm;

पूर्णांक tegra_pinctrl_probe(काष्ठा platक्रमm_device *pdev,
			स्थिर काष्ठा tegra_pinctrl_soc_data *soc_data);
#पूर्ण_अगर
