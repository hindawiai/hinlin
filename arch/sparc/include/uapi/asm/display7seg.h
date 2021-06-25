<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 *
 * display7seg - Driver पूर्णांकerface क्रम the 7-segment display
 * present on Sun Microप्रणालीs CP1400 and CP1500
 *
 * Copyright (c) 2000 Eric Brower <ebrower@usa.net>
 *
 */

#अगर_अघोषित __display7seg_h__
#घोषणा __display7seg_h__

#घोषणा D7S_IOC	'p'

#घोषणा D7SIOCRD _IOR(D7S_IOC, 0x45, पूर्णांक)	/* Read device state	*/
#घोषणा D7SIOCWR _IOW(D7S_IOC, 0x46, पूर्णांक)	/* Write device state	*/
#घोषणा D7SIOCTM _IO (D7S_IOC, 0x47)		/* Translate mode (FLIP)*/

/*
 * ioctl flag definitions
 *
 * POINT	- Toggle decimal poपूर्णांक	(0=असलent 1=present)
 * ALARM	- Toggle alarm LED 		(0=green  1=red)
 * FLIP		- Toggle inverted mode 	(0=normal 1=flipped)
 * bits 0-4	- Character displayed	(see definitions below)
 *
 * Display segments are defined as follows,
 * subject to D7S_FLIP रेजिस्टर state:
 *
 *    a
 *   ---
 * f|   |b
 *   -g-
 * e|   |c
 *   ---
 *    d
 */

#घोषणा D7S_POINT	(1 << 7)	/* Decimal poपूर्णांक*/
#घोषणा D7S_ALARM	(1 << 6)	/* Alarm LED 	*/
#घोषणा D7S_FLIP	(1 << 5)	/* Flip display */

#घोषणा D7S_0		0x00		/* Numerals 0-9 */
#घोषणा D7S_1		0x01
#घोषणा D7S_2		0x02
#घोषणा D7S_3		0x03
#घोषणा D7S_4		0x04
#घोषणा D7S_5		0x05
#घोषणा D7S_6		0x06
#घोषणा D7S_7		0x07
#घोषणा D7S_8		0x08
#घोषणा D7S_9		0x09
#घोषणा D7S_A		0x0A		/* Letters A-F, H, L, P */
#घोषणा D7S_B		0x0B
#घोषणा D7S_C		0x0C
#घोषणा D7S_D		0x0D
#घोषणा D7S_E		0x0E
#घोषणा D7S_F		0x0F
#घोषणा D7S_H		0x10
#घोषणा D7S_E2		0x11
#घोषणा D7S_L		0x12
#घोषणा D7S_P		0x13
#घोषणा D7S_SEGA	0x14		/* Inभागidual segments */
#घोषणा D7S_SEGB	0x15
#घोषणा D7S_SEGC	0x16
#घोषणा D7S_SEGD	0x17
#घोषणा D7S_SEGE	0x18
#घोषणा D7S_SEGF	0x19
#घोषणा D7S_SEGG	0x1A
#घोषणा D7S_SEGABFG 0x1B		/* Segment groupings */
#घोषणा D7S_SEGCDEG	0x1C
#घोषणा D7S_SEGBCEF 0x1D
#घोषणा D7S_SEGADG	0x1E
#घोषणा D7S_BLANK	0x1F		/* Clear all segments */

#घोषणा D7S_MIN_VAL	0x0
#घोषणा D7S_MAX_VAL	0x1F

#पूर्ण_अगर /* अगरndef __display7seg_h__ */
