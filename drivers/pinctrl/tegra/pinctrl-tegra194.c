<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Pinctrl data क्रम the NVIDIA Tegra194 pinmux
 *
 * Copyright (c) 2019, NVIDIA CORPORATION.  All rights reserved.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License क्रम
 * more details.
 */

#समावेश <linux/init.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pinctrl/pinctrl.h>
#समावेश <linux/pinctrl/pinmux.h>

#समावेश "pinctrl-tegra.h"

/* Define unique ID क्रम each pins */
क्रमागत pin_id अणु
	TEGRA_PIN_PEX_L5_CLKREQ_N_PGG0,
	TEGRA_PIN_PEX_L5_RST_N_PGG1,
पूर्ण;

/* Table क्रम pin descriptor */
अटल स्थिर काष्ठा pinctrl_pin_desc tegra194_pins[] = अणु
	PINCTRL_PIN(TEGRA_PIN_PEX_L5_CLKREQ_N_PGG0, "PEX_L5_CLKREQ_N_PGG0"),
	PINCTRL_PIN(TEGRA_PIN_PEX_L5_RST_N_PGG1, "PEX_L5_RST_N_PGG1"),
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक pex_l5_clkreq_n_pgg0_pins[] = अणु
	TEGRA_PIN_PEX_L5_CLKREQ_N_PGG0,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक pex_l5_rst_n_pgg1_pins[] = अणु
	TEGRA_PIN_PEX_L5_RST_N_PGG1,
पूर्ण;

/* Define unique ID क्रम each function */
क्रमागत tegra_mux_dt अणु
	TEGRA_MUX_RSVD0,
	TEGRA_MUX_RSVD1,
	TEGRA_MUX_RSVD2,
	TEGRA_MUX_RSVD3,
	TEGRA_MUX_PE5,
पूर्ण;

/* Make list of each function name */
#घोषणा TEGRA_PIN_FUNCTION(lid)			\
	अणु					\
		.name = #lid,			\
	पूर्ण

अटल काष्ठा tegra_function tegra194_functions[] = अणु
	TEGRA_PIN_FUNCTION(rsvd0),
	TEGRA_PIN_FUNCTION(rsvd1),
	TEGRA_PIN_FUNCTION(rsvd2),
	TEGRA_PIN_FUNCTION(rsvd3),
	TEGRA_PIN_FUNCTION(pe5),
पूर्ण;

#घोषणा DRV_PINGROUP_ENTRY_Y(r, drvdn_b, drvdn_w, drvup_b,	\
			     drvup_w, slwr_b, slwr_w, slwf_b,	\
			     slwf_w, bank)			\
		.drv_reg = ((r)),				\
		.drv_bank = bank,				\
		.drvdn_bit = drvdn_b,				\
		.drvdn_width = drvdn_w,				\
		.drvup_bit = drvup_b,				\
		.drvup_width = drvup_w,				\
		.slwr_bit = slwr_b,				\
		.slwr_width = slwr_w,				\
		.slwf_bit = slwf_b,				\
		.slwf_width = slwf_w

#घोषणा PIN_PINGROUP_ENTRY_Y(r, bank, pupd, e_lpbk, e_input,	\
			     e_od, schmitt_b, drvtype)		\
		.mux_reg = ((r)),				\
		.lpmd_bit = -1,					\
		.lock_bit = -1,					\
		.hsm_bit = -1,					\
		.mux_bank = bank,				\
		.mux_bit = 0,					\
		.pupd_reg = ((r)),				\
		.pupd_bank = bank,				\
		.pupd_bit = 2,					\
		.tri_reg = ((r)),				\
		.tri_bank = bank,				\
		.tri_bit = 4,					\
		.einput_bit = e_input,				\
		.odrain_bit = e_od,				\
		.sfsel_bit = 10,				\
		.schmitt_bit = schmitt_b,			\
		.drvtype_bit = 13,				\
		.parked_biपंचांगask = 0

#घोषणा drive_pex_l5_clkreq_n_pgg0				\
	DRV_PINGROUP_ENTRY_Y(0x14004, 12, 5, 20, 5, -1, -1, -1, -1, 0)
#घोषणा drive_pex_l5_rst_n_pgg1					\
	DRV_PINGROUP_ENTRY_Y(0x1400c, 12, 5, 20, 5, -1, -1, -1, -1, 0)

#घोषणा PINGROUP(pg_name, f0, f1, f2, f3, r, bank, pupd, e_lpbk,	\
		 e_input, e_lpdr, e_od, schmitt_b, drvtype, io_rail)	\
	अणु								\
		.name = #pg_name,					\
		.pins = pg_name##_pins,					\
		.npins = ARRAY_SIZE(pg_name##_pins),			\
			.funcs = अणु					\
				TEGRA_MUX_##f0,				\
				TEGRA_MUX_##f1,				\
				TEGRA_MUX_##f2,				\
				TEGRA_MUX_##f3,				\
			पूर्ण,						\
		PIN_PINGROUP_ENTRY_Y(r, bank, pupd, e_lpbk,		\
				     e_input, e_od,			\
				     schmitt_b, drvtype),		\
		drive_##pg_name,					\
	पूर्ण

अटल स्थिर काष्ठा tegra_pingroup tegra194_groups[] = अणु
	PINGROUP(pex_l5_clkreq_n_pgg0, PE5, RSVD1, RSVD2, RSVD3, 0x14000, 0,
		 Y, -1, 6, 8, 11, 12, N, "vddio_pex_ctl_2"),
	PINGROUP(pex_l5_rst_n_pgg1, PE5, RSVD1, RSVD2, RSVD3, 0x14008, 0,
		 Y, -1, 6, 8, 11, 12, N, "vddio_pex_ctl_2"),
पूर्ण;

अटल स्थिर काष्ठा tegra_pinctrl_soc_data tegra194_pinctrl = अणु
	.pins = tegra194_pins,
	.npins = ARRAY_SIZE(tegra194_pins),
	.functions = tegra194_functions,
	.nfunctions = ARRAY_SIZE(tegra194_functions),
	.groups = tegra194_groups,
	.ngroups = ARRAY_SIZE(tegra194_groups),
	.hsm_in_mux = true,
	.schmitt_in_mux = true,
	.drvtype_in_mux = true,
	.sfsel_in_mux = true,
पूर्ण;

अटल पूर्णांक tegra194_pinctrl_probe(काष्ठा platक्रमm_device *pdev)
अणु
	वापस tegra_pinctrl_probe(pdev, &tegra194_pinctrl);
पूर्ण

अटल स्थिर काष्ठा of_device_id tegra194_pinctrl_of_match[] = अणु
	अणु .compatible = "nvidia,tegra194-pinmux", पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver tegra194_pinctrl_driver = अणु
	.driver = अणु
		.name = "tegra194-pinctrl",
		.of_match_table = tegra194_pinctrl_of_match,
	पूर्ण,
	.probe = tegra194_pinctrl_probe,
पूर्ण;

अटल पूर्णांक __init tegra194_pinctrl_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&tegra194_pinctrl_driver);
पूर्ण
arch_initcall(tegra194_pinctrl_init);
