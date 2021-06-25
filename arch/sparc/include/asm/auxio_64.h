<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * auxपन.स:  Definitions and code क्रम the Auxiliary I/O रेजिस्टरs.
 *
 * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)
 *
 * Refactoring क्रम unअगरied NCR/PCIO support 2002 Eric Brower (ebrower@usa.net)
 */
#अगर_अघोषित _SPARC64_AUXIO_H
#घोषणा _SPARC64_AUXIO_H

/* AUXIO implementations:
 * sbus-based NCR89C105 "Slavio"
 *	LED/Floppy (AUX1) रेजिस्टर
 *	Power (AUX2) रेजिस्टर
 *
 * ebus-based auxio on PCIO
 *	LED Auxio Register
 *	Power Auxio Register
 *
 * Register definitions from NCR _NCR89C105 Chip Specअगरication_
 *
 * SLAVIO AUX1 @ 0x1900000
 * -------------------------------------------------
 * | (R) | (R) |  D  | (R) |  E  |  M  |  T  |  L  |
 * -------------------------------------------------
 * (R) - bit 7:6,4 are reserved and should be masked in s/w
 *  D  - Floppy Density Sense (1=high density) R/O
 *  E  - Link Test Enable, directly reflected on AT&T 7213 LTE pin
 *  M  - Monitor/Mouse Mux, directly reflected on MON_MSE_MUX pin
 *  T  - Terminal Count: sends TC pulse to 82077 floppy controller
 *  L  - System LED on front panel (0=off, 1=on)
 */
#घोषणा AUXIO_AUX1_MASK		0xc0 /* Mask bits 		*/
#घोषणा AUXIO_AUX1_FDENS	0x20 /* Floppy Density Sense	*/
#घोषणा AUXIO_AUX1_LTE 		0x08 /* Link Test Enable 	*/
#घोषणा AUXIO_AUX1_MMUX		0x04 /* Monitor/Mouse Mux	*/
#घोषणा AUXIO_AUX1_FTCNT	0x02 /* Terminal Count, 	*/
#घोषणा AUXIO_AUX1_LED		0x01 /* System LED		*/

/* SLAVIO AUX2 @ 0x1910000
 * -------------------------------------------------
 * | (R) | (R) |  D  | (R) | (R) | (R) |  C  |  F  |
 * -------------------------------------------------
 * (R) - bits 7:6,4:2 are reserved and should be masked in s/w
 *  D  - Power Failure Detect (1=घातer fail)
 *  C  - Clear Power Failure Detect Int (1=clear)
 *  F  - Power Off (1=घातer off)
 */
#घोषणा AUXIO_AUX2_MASK		0xdc /* Mask Bits		*/
#घोषणा AUXIO_AUX2_PFAILDET	0x20 /* Power Fail Detect	*/
#घोषणा AUXIO_AUX2_PFAILCLR 	0x02 /* Clear Pwr Fail Det Intr	*/
#घोषणा AUXIO_AUX2_PWR_OFF	0x01 /* Power Off		*/

/* Register definitions from Sun Microप्रणालीs _PCIO_ p/n 802-7837
 *
 * PCIO LED Auxio @ 0x726000
 * -------------------------------------------------
 * |             31:1 Unused                 | LED |
 * -------------------------------------------------
 * Bits 31:1 unused
 * LED - System LED on front panel (0=off, 1=on)
 */
#घोषणा AUXIO_PCIO_LED		0x01 /* System LED 		*/

/* PCIO Power Auxio @ 0x724000
 * -------------------------------------------------
 * |             31:2 Unused           | CPO | SPO |
 * -------------------------------------------------
 * Bits 31:2 unused
 * CPO - Courtesy Power Off (1=off)
 * SPO - System Power Off   (1=off)
 */
#घोषणा AUXIO_PCIO_CPWR_OFF	0x02 /* Courtesy Power Off	*/
#घोषणा AUXIO_PCIO_SPWR_OFF	0x01 /* System Power Off	*/

#अगर_अघोषित __ASSEMBLY__

#घोषणा AUXIO_LTE_ON	1
#घोषणा AUXIO_LTE_OFF	0

/* auxio_set_lte - Set Link Test Enable (TPE Link Detect)
 *
 * on - AUXIO_LTE_ON or AUXIO_LTE_OFF
 */
व्योम auxio_set_lte(पूर्णांक on);

#घोषणा AUXIO_LED_ON	1
#घोषणा AUXIO_LED_OFF	0

/* auxio_set_led - Set प्रणाली front panel LED
 *
 * on - AUXIO_LED_ON or AUXIO_LED_OFF
 */
व्योम auxio_set_led(पूर्णांक on);

#पूर्ण_अगर /* अगरndef __ASSEMBLY__ */

#पूर्ण_अगर /* !(_SPARC64_AUXIO_H) */
