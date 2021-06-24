<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * This header provides स्थिरants क्रम binding nvidia,tegra*-gpio.
 *
 * The first cell in Tegra's GPIO specअगरier is the GPIO ID. The macros below
 * provide names क्रम this.
 *
 * The second cell contains standard flag values specअगरied in gpपन.स.
 */

#अगर_अघोषित _DT_BINDINGS_GPIO_TEGRA_GPIO_H
#घोषणा _DT_BINDINGS_GPIO_TEGRA_GPIO_H

#समावेश <dt-bindings/gpio/gpपन.स>

#घोषणा TEGRA_GPIO_PORT_A 0
#घोषणा TEGRA_GPIO_PORT_B 1
#घोषणा TEGRA_GPIO_PORT_C 2
#घोषणा TEGRA_GPIO_PORT_D 3
#घोषणा TEGRA_GPIO_PORT_E 4
#घोषणा TEGRA_GPIO_PORT_F 5
#घोषणा TEGRA_GPIO_PORT_G 6
#घोषणा TEGRA_GPIO_PORT_H 7
#घोषणा TEGRA_GPIO_PORT_I 8
#घोषणा TEGRA_GPIO_PORT_J 9
#घोषणा TEGRA_GPIO_PORT_K 10
#घोषणा TEGRA_GPIO_PORT_L 11
#घोषणा TEGRA_GPIO_PORT_M 12
#घोषणा TEGRA_GPIO_PORT_N 13
#घोषणा TEGRA_GPIO_PORT_O 14
#घोषणा TEGRA_GPIO_PORT_P 15
#घोषणा TEGRA_GPIO_PORT_Q 16
#घोषणा TEGRA_GPIO_PORT_R 17
#घोषणा TEGRA_GPIO_PORT_S 18
#घोषणा TEGRA_GPIO_PORT_T 19
#घोषणा TEGRA_GPIO_PORT_U 20
#घोषणा TEGRA_GPIO_PORT_V 21
#घोषणा TEGRA_GPIO_PORT_W 22
#घोषणा TEGRA_GPIO_PORT_X 23
#घोषणा TEGRA_GPIO_PORT_Y 24
#घोषणा TEGRA_GPIO_PORT_Z 25
#घोषणा TEGRA_GPIO_PORT_AA 26
#घोषणा TEGRA_GPIO_PORT_BB 27
#घोषणा TEGRA_GPIO_PORT_CC 28
#घोषणा TEGRA_GPIO_PORT_DD 29
#घोषणा TEGRA_GPIO_PORT_EE 30
#घोषणा TEGRA_GPIO_PORT_FF 31

#घोषणा TEGRA_GPIO(port, offset) \
	((TEGRA_GPIO_PORT_##port * 8) + offset)

#पूर्ण_अगर
