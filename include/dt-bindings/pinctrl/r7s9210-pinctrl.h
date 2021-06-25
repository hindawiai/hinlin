<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Defines macros and स्थिरants क्रम Renesas RZ/A2 pin controller pin
 * muxing functions.
 */
#अगर_अघोषित __DT_BINDINGS_PINCTRL_RENESAS_RZA2_H
#घोषणा __DT_BINDINGS_PINCTRL_RENESAS_RZA2_H

#घोषणा RZA2_PINS_PER_PORT	8

/* Port names as labeled in the Hardware Manual */
#घोषणा PORT0 0
#घोषणा PORT1 1
#घोषणा PORT2 2
#घोषणा PORT3 3
#घोषणा PORT4 4
#घोषणा PORT5 5
#घोषणा PORT6 6
#घोषणा PORT7 7
#घोषणा PORT8 8
#घोषणा PORT9 9
#घोषणा PORTA 10
#घोषणा PORTB 11
#घोषणा PORTC 12
#घोषणा PORTD 13
#घोषणा PORTE 14
#घोषणा PORTF 15
#घोषणा PORTG 16
#घोषणा PORTH 17
/* No I */
#घोषणा PORTJ 18
#घोषणा PORTK 19
#घोषणा PORTL 20
#घोषणा PORTM 21	/* Pins PM_0/1 are labeled JP_0/1 in HW manual */

/*
 * Create the pin index from its bank and position numbers and store in
 * the upper 16 bits the alternate function identअगरier
 */
#घोषणा RZA2_PINMUX(b, p, f)	((b) * RZA2_PINS_PER_PORT + (p) | (f << 16))

/*
 * Convert a port and pin label to its global pin index
 */
 #घोषणा RZA2_PIN(port, pin)	((port) * RZA2_PINS_PER_PORT + (pin))

#पूर्ण_अगर /* __DT_BINDINGS_PINCTRL_RENESAS_RZA2_H */
