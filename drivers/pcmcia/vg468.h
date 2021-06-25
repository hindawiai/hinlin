<शैली गुरु>
/*
 * vg468.h 1.11 1999/10/25 20:03:34
 *
 * The contents of this file are subject to the Mozilla Public License
 * Version 1.1 (the "License"); you may not use this file except in
 * compliance with the License. You may obtain a copy of the License
 * at http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS"
 * basis, WITHOUT WARRANTY OF ANY KIND, either express or implied. See
 * the License क्रम the specअगरic language governing rights and
 * limitations under the License. 
 *
 * The initial developer of the original code is David A. Hinds
 * <dahinds@users.sourceक्रमge.net>.  Portions created by David A. Hinds
 * are Copyright (C) 1999 David A. Hinds.  All Rights Reserved.
 *
 * Alternatively, the contents of this file may be used under the
 * terms of the GNU General Public License version 2 (the "GPL"), in which
 * हाल the provisions of the GPL are applicable instead of the
 * above.  If you wish to allow the use of your version of this file
 * only under the terms of the GPL and not to allow others to use
 * your version of this file under the MPL, indicate your decision by
 * deleting the provisions above and replace them with the notice and
 * other provisions required by the GPL.  If you करो not delete the
 * provisions above, a recipient may use your version of this file
 * under either the MPL or the GPL.
 */

#अगर_अघोषित _LINUX_VG468_H
#घोषणा _LINUX_VG468_H

/* Special bit in I365_IDENT used क्रम Vadem chip detection */
#घोषणा I365_IDENT_VADEM	0x08

/* Special definitions in I365_POWER */
#घोषणा VG468_VPP2_MASK		0x0c
#घोषणा VG468_VPP2_5V		0x04
#घोषणा VG468_VPP2_12V		0x08

/* Unique Vadem रेजिस्टरs */
#घोषणा VG469_VSENSE		0x1f	/* Card voltage sense */
#घोषणा VG469_VSELECT		0x2f	/* Card voltage select */
#घोषणा VG468_CTL		0x38	/* Control रेजिस्टर */
#घोषणा VG468_TIMER		0x39	/* Timer control */
#घोषणा VG468_MISC		0x3a	/* Miscellaneous */
#घोषणा VG468_GPIO_CFG		0x3b	/* GPIO configuration */
#घोषणा VG469_EXT_MODE		0x3c	/* Extended mode रेजिस्टर */
#घोषणा VG468_SELECT		0x3d	/* Programmable chip select */
#घोषणा VG468_SELECT_CFG	0x3e	/* Chip select configuration */
#घोषणा VG468_ATA		0x3f	/* ATA control */

/* Flags क्रम VG469_VSENSE */
#घोषणा VG469_VSENSE_A_VS1	0x01
#घोषणा VG469_VSENSE_A_VS2	0x02
#घोषणा VG469_VSENSE_B_VS1	0x04
#घोषणा VG469_VSENSE_B_VS2	0x08

/* Flags क्रम VG469_VSELECT */
#घोषणा VG469_VSEL_VCC		0x03
#घोषणा VG469_VSEL_5V		0x00
#घोषणा VG469_VSEL_3V		0x03
#घोषणा VG469_VSEL_MAX		0x0c
#घोषणा VG469_VSEL_EXT_STAT	0x10
#घोषणा VG469_VSEL_EXT_BUS	0x20
#घोषणा VG469_VSEL_MIXED	0x40
#घोषणा VG469_VSEL_ISA		0x80

/* Flags क्रम VG468_CTL */
#घोषणा VG468_CTL_SLOW		0x01	/* 600ns memory timing */
#घोषणा VG468_CTL_ASYNC		0x02	/* Asynchronous bus घड़ीing */
#घोषणा VG468_CTL_TSSI		0x08	/* Tri-state some outमाला_दो */
#घोषणा VG468_CTL_DELAY		0x10	/* Card detect debounce */
#घोषणा VG468_CTL_INPACK	0x20	/* Obey INPACK संकेत? */
#घोषणा VG468_CTL_POLARITY	0x40	/* VCCEN polarity */
#घोषणा VG468_CTL_COMPAT	0x80	/* Compatibility stuff */

#घोषणा VG469_CTL_WS_COMPAT	0x04	/* Wait state compatibility */
#घोषणा VG469_CTL_STRETCH	0x10	/* LED stretch */

/* Flags क्रम VG468_TIMER */
#घोषणा VG468_TIMER_ZEROPWR	0x10	/* Zero घातer control */
#घोषणा VG468_TIMER_SIGEN	0x20	/* Power up */
#घोषणा VG468_TIMER_STATUS	0x40	/* Activity समयr status */
#घोषणा VG468_TIMER_RES		0x80	/* Timer resolution */
#घोषणा VG468_TIMER_MASK	0x0f	/* Activity समयr समयout */

/* Flags क्रम VG468_MISC */
#घोषणा VG468_MISC_GPIO		0x04	/* General-purpose IO */
#घोषणा VG468_MISC_DMAWSB	0x08	/* DMA रुको state control */
#घोषणा VG469_MISC_LEDENA	0x10	/* LED enable */
#घोषणा VG468_MISC_VADEMREV	0x40	/* Vadem revision control */
#घोषणा VG468_MISC_UNLOCK	0x80	/* Unique रेजिस्टर lock */

/* Flags क्रम VG469_EXT_MODE_A */
#घोषणा VG469_MODE_VPPST	0x03	/* Vpp steering control */
#घोषणा VG469_MODE_INT_SENSE	0x04	/* Internal voltage sense */
#घोषणा VG469_MODE_CABLE	0x08
#घोषणा VG469_MODE_COMPAT	0x10	/* i82365sl B or DF step */
#घोषणा VG469_MODE_TEST		0x20
#घोषणा VG469_MODE_RIO		0x40	/* Steer RIO to INTR? */

/* Flags क्रम VG469_EXT_MODE_B */
#घोषणा VG469_MODE_B_3V		0x01	/* 3.3v क्रम socket B */

#पूर्ण_अगर /* _LINUX_VG468_H */
