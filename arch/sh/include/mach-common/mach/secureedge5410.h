<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0
 *
 * include/यंत्र-sh/snapgear.h
 *
 * Modअगरied version of io_se.h क्रम the snapgear-specअगरic functions.
 *
 * IO functions क्रम a SnapGear
 */

#अगर_अघोषित _ASM_SH_IO_SNAPGEAR_H
#घोषणा _ASM_SH_IO_SNAPGEAR_H

#घोषणा __IO_PREFIX	snapgear
#समावेश <यंत्र/io_generic.h>

/*
 * We need to remember what was written to the ioport as some bits
 * are shared with other functions and you cannot पढ़ो back what was
 * written :-|
 *
 * Bit        Read                   Write
 * -----------------------------------------------
 * D0         DCD on ttySC1          घातer
 * D1         Reset Switch           heatbeat
 * D2         ttySC0 CTS (7100)      LAN
 * D3         -                      WAN
 * D4         ttySC0 DCD (7100)      CONSOLE
 * D5         -                      ONLINE
 * D6         -                      VPN
 * D7         -                      DTR on ttySC1
 * D8         -                      ttySC0 RTS (7100)
 * D9         -                      ttySC0 DTR (7100)
 * D10        -                      RTC SCLK
 * D11        RTC DATA               RTC DATA
 * D12        -                      RTS RESET
 */

#घोषणा SECUREEDGE_IOPORT_ADDR ((अस्थिर लघु *) 0xb0000000)
बाह्य अचिन्हित लघु secureedge5410_ioport;

#घोषणा SECUREEDGE_WRITE_IOPORT(val, mask) (*SECUREEDGE_IOPORT_ADDR = \
	 (secureedge5410_ioport = \
			((secureedge5410_ioport & ~(mask)) | ((val) & (mask)))))
#घोषणा SECUREEDGE_READ_IOPORT() \
	 ((*SECUREEDGE_IOPORT_ADDR&0x0817) | (secureedge5410_ioport&~0x0817))

#पूर्ण_अगर /* _ASM_SH_IO_SNAPGEAR_H */
