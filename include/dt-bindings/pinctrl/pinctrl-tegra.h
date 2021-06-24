<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * This header provides स्थिरants क्रम Tegra pinctrl bindings.
 *
 * Copyright (c) 2013, NVIDIA CORPORATION.  All rights reserved.
 *
 * Author: Laxman Dewangan <ldewangan@nvidia.com>
 */

#अगर_अघोषित _DT_BINDINGS_PINCTRL_TEGRA_H
#घोषणा _DT_BINDINGS_PINCTRL_TEGRA_H

/*
 * Enable/disable क्रम dअगरfeent dt properties. This is applicable क्रम
 * properties nvidia,enable-input, nvidia,tristate, nvidia,खोलो-drain,
 * nvidia,lock, nvidia,rcv-sel, nvidia,high-speed-mode, nvidia,schmitt.
 */
#घोषणा TEGRA_PIN_DISABLE				0
#घोषणा TEGRA_PIN_ENABLE				1

#घोषणा TEGRA_PIN_PULL_NONE				0
#घोषणा TEGRA_PIN_PULL_DOWN				1
#घोषणा TEGRA_PIN_PULL_UP				2

/* Low घातer mode driver */
#घोषणा TEGRA_PIN_LP_DRIVE_DIV_8			0
#घोषणा TEGRA_PIN_LP_DRIVE_DIV_4			1
#घोषणा TEGRA_PIN_LP_DRIVE_DIV_2			2
#घोषणा TEGRA_PIN_LP_DRIVE_DIV_1			3

/* Rising/Falling slew rate */
#घोषणा TEGRA_PIN_SLEW_RATE_FASTEST			0
#घोषणा TEGRA_PIN_SLEW_RATE_FAST			1
#घोषणा TEGRA_PIN_SLEW_RATE_SLOW			2
#घोषणा TEGRA_PIN_SLEW_RATE_SLOWEST			3

#पूर्ण_अगर
