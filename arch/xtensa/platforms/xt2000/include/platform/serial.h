<शैली गुरु>
/*
 * platक्रमm/serial.h
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2001 Tensilica Inc.
 */

#अगर_अघोषित _XTENSA_XT2000_SERIAL_H
#घोषणा _XTENSA_XT2000_SERIAL_H

#समावेश <यंत्र/core.h>
#समावेश <यंत्र/पन.स>

/*  National-Semi PC16552D DUART:  */

#घोषणा DUART16552_1_INTNUM	XCHAL_EXTINT4_NUM
#घोषणा DUART16552_2_INTNUM	XCHAL_EXTINT5_NUM

#घोषणा DUART16552_1_ADDR	IOADDR(0x0d050020)	/* channel 1 */
#घोषणा DUART16552_2_ADDR	IOADDR(0x0d050000)	/* channel 2 */

#घोषणा DUART16552_XTAL_FREQ	18432000	/* crystal frequency in Hz */
#घोषणा BASE_BAUD ( DUART16552_XTAL_FREQ / 16 )

#पूर्ण_अगर /* _XTENSA_XT2000_SERIAL_H */
