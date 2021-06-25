<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * arch/arm/mach-sa1100/include/mach/jornada720.h
 *
 * SSP/MCU communication definitions क्रम HP Jornada 710/720/728
 *
 * Copyright 2007,2008 Kristoffer Ericson <Kristoffer.Ericson@gmail.com>
 *  Copyright 2000 John Ankcorn <jca@lcs.mit.edu>
 */

 /* HP Jornada 7xx microprocessor commands */
#घोषणा GETBATTERYDATA		0xc0
#घोषणा GETSCANKEYCODE		0x90
#घोषणा GETTOUCHSAMPLES		0xa0
#घोषणा GETCONTRAST		0xD0
#घोषणा SETCONTRAST		0xD1
#घोषणा GETBRIGHTNESS		0xD2
#घोषणा SETBRIGHTNESS		0xD3
#घोषणा CONTRASTOFF		0xD8
#घोषणा BRIGHTNESSOFF		0xD9
#घोषणा PWMOFF			0xDF
#घोषणा TXDUMMY			0x11
#घोषणा ERRORCODE		0x00

बाह्य व्योम jornada_ssp_start(व्योम);
बाह्य व्योम jornada_ssp_end(व्योम);
बाह्य पूर्णांक jornada_ssp_inout(u8 byte);
बाह्य पूर्णांक jornada_ssp_byte(u8 byte);
