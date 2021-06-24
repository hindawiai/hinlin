<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Defines macros and स्थिरants क्रम Renesas RZ/A1 pin controller pin
 * muxing functions.
 */
#अगर_अघोषित __DT_BINDINGS_PINCTRL_RENESAS_RZA1_H
#घोषणा __DT_BINDINGS_PINCTRL_RENESAS_RZA1_H

#घोषणा RZA1_PINS_PER_PORT	16

/*
 * Create the pin index from its bank and position numbers and store in
 * the upper 16 bits the alternate function identअगरier
 */
#घोषणा RZA1_PINMUX(b, p, f)	((b) * RZA1_PINS_PER_PORT + (p) | (f << 16))

#पूर्ण_अगर /* __DT_BINDINGS_PINCTRL_RENESAS_RZA1_H */
