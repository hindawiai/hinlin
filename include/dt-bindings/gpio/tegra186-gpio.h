<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * This header provides स्थिरants क्रम binding nvidia,tegra186-gpio*.
 *
 * The first cell in Tegra's GPIO specअगरier is the GPIO ID. The macros below
 * provide names क्रम this.
 *
 * The second cell contains standard flag values specअगरied in gpपन.स.
 */

#अगर_अघोषित _DT_BINDINGS_GPIO_TEGRA186_GPIO_H
#घोषणा _DT_BINDINGS_GPIO_TEGRA186_GPIO_H

#समावेश <dt-bindings/gpio/gpपन.स>

/* GPIOs implemented by मुख्य GPIO controller */
#घोषणा TEGRA186_MAIN_GPIO_PORT_A 0
#घोषणा TEGRA186_MAIN_GPIO_PORT_B 1
#घोषणा TEGRA186_MAIN_GPIO_PORT_C 2
#घोषणा TEGRA186_MAIN_GPIO_PORT_D 3
#घोषणा TEGRA186_MAIN_GPIO_PORT_E 4
#घोषणा TEGRA186_MAIN_GPIO_PORT_F 5
#घोषणा TEGRA186_MAIN_GPIO_PORT_G 6
#घोषणा TEGRA186_MAIN_GPIO_PORT_H 7
#घोषणा TEGRA186_MAIN_GPIO_PORT_I 8
#घोषणा TEGRA186_MAIN_GPIO_PORT_J 9
#घोषणा TEGRA186_MAIN_GPIO_PORT_K 10
#घोषणा TEGRA186_MAIN_GPIO_PORT_L 11
#घोषणा TEGRA186_MAIN_GPIO_PORT_M 12
#घोषणा TEGRA186_MAIN_GPIO_PORT_N 13
#घोषणा TEGRA186_MAIN_GPIO_PORT_O 14
#घोषणा TEGRA186_MAIN_GPIO_PORT_P 15
#घोषणा TEGRA186_MAIN_GPIO_PORT_Q 16
#घोषणा TEGRA186_MAIN_GPIO_PORT_R 17
#घोषणा TEGRA186_MAIN_GPIO_PORT_T 18
#घोषणा TEGRA186_MAIN_GPIO_PORT_X 19
#घोषणा TEGRA186_MAIN_GPIO_PORT_Y 20
#घोषणा TEGRA186_MAIN_GPIO_PORT_BB 21
#घोषणा TEGRA186_MAIN_GPIO_PORT_CC 22

#घोषणा TEGRA186_MAIN_GPIO(port, offset) \
	((TEGRA186_MAIN_GPIO_PORT_##port * 8) + offset)

/* GPIOs implemented by AON GPIO controller */
#घोषणा TEGRA186_AON_GPIO_PORT_S 0
#घोषणा TEGRA186_AON_GPIO_PORT_U 1
#घोषणा TEGRA186_AON_GPIO_PORT_V 2
#घोषणा TEGRA186_AON_GPIO_PORT_W 3
#घोषणा TEGRA186_AON_GPIO_PORT_Z 4
#घोषणा TEGRA186_AON_GPIO_PORT_AA 5
#घोषणा TEGRA186_AON_GPIO_PORT_EE 6
#घोषणा TEGRA186_AON_GPIO_PORT_FF 7

#घोषणा TEGRA186_AON_GPIO(port, offset) \
	((TEGRA186_AON_GPIO_PORT_##port * 8) + offset)

#पूर्ण_अगर
