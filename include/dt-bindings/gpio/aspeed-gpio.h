<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * This header provides स्थिरants क्रम binding aspeed,*-gpio.
 *
 * The first cell in Aspeed's GPIO specअगरier is the GPIO ID. The macros below
 * provide names क्रम this.
 *
 * The second cell contains standard flag values specअगरied in gpपन.स.
 */

#अगर_अघोषित _DT_BINDINGS_GPIO_ASPEED_GPIO_H
#घोषणा _DT_BINDINGS_GPIO_ASPEED_GPIO_H

#समावेश <dt-bindings/gpio/gpपन.स>

#घोषणा ASPEED_GPIO_PORT_A 0
#घोषणा ASPEED_GPIO_PORT_B 1
#घोषणा ASPEED_GPIO_PORT_C 2
#घोषणा ASPEED_GPIO_PORT_D 3
#घोषणा ASPEED_GPIO_PORT_E 4
#घोषणा ASPEED_GPIO_PORT_F 5
#घोषणा ASPEED_GPIO_PORT_G 6
#घोषणा ASPEED_GPIO_PORT_H 7
#घोषणा ASPEED_GPIO_PORT_I 8
#घोषणा ASPEED_GPIO_PORT_J 9
#घोषणा ASPEED_GPIO_PORT_K 10
#घोषणा ASPEED_GPIO_PORT_L 11
#घोषणा ASPEED_GPIO_PORT_M 12
#घोषणा ASPEED_GPIO_PORT_N 13
#घोषणा ASPEED_GPIO_PORT_O 14
#घोषणा ASPEED_GPIO_PORT_P 15
#घोषणा ASPEED_GPIO_PORT_Q 16
#घोषणा ASPEED_GPIO_PORT_R 17
#घोषणा ASPEED_GPIO_PORT_S 18
#घोषणा ASPEED_GPIO_PORT_T 19
#घोषणा ASPEED_GPIO_PORT_U 20
#घोषणा ASPEED_GPIO_PORT_V 21
#घोषणा ASPEED_GPIO_PORT_W 22
#घोषणा ASPEED_GPIO_PORT_X 23
#घोषणा ASPEED_GPIO_PORT_Y 24
#घोषणा ASPEED_GPIO_PORT_Z 25
#घोषणा ASPEED_GPIO_PORT_AA 26
#घोषणा ASPEED_GPIO_PORT_AB 27
#घोषणा ASPEED_GPIO_PORT_AC 28

#घोषणा ASPEED_GPIO(port, offset) \
	((ASPEED_GPIO_PORT_##port * 8) + offset)

#पूर्ण_अगर
