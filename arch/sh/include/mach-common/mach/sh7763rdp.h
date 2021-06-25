<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_SH_SH7763RDP_H
#घोषणा __ASM_SH_SH7763RDP_H

/*
 * linux/include/यंत्र-sh/sh7763drp.h
 *
 * Copyright (C) 2008 Renesas Solutions
 * Copyright (C) 2008 Nobuhiro Iwamatsu <iwamatsu.nobuhiro@renesas.com>
 */
#समावेश <यंत्र/addrspace.h>

/* घड़ी control */
#घोषणा MSTPCR1 0xFFC80038

/* PORT */
#घोषणा PORT_PSEL0	0xFFEF0070
#घोषणा PORT_PSEL1	0xFFEF0072
#घोषणा PORT_PSEL2	0xFFEF0074
#घोषणा PORT_PSEL3	0xFFEF0076
#घोषणा PORT_PSEL4	0xFFEF0078

#घोषणा PORT_PACR	0xFFEF0000
#घोषणा PORT_PCCR	0xFFEF0004
#घोषणा PORT_PFCR	0xFFEF000A
#घोषणा PORT_PGCR	0xFFEF000C
#घोषणा PORT_PHCR	0xFFEF000E
#घोषणा PORT_PICR	0xFFEF0010
#घोषणा PORT_PJCR	0xFFEF0012
#घोषणा PORT_PKCR	0xFFEF0014
#घोषणा PORT_PLCR	0xFFEF0016
#घोषणा PORT_PMCR	0xFFEF0018
#घोषणा PORT_PNCR	0xFFEF001A

/* FPGA */
#घोषणा CPLD_BOARD_ID_ERV_REG	0xB1000000
#घोषणा CPLD_CPLD_CMD_REG		0xB1000006

/*
 * USB SH7763RDP board can use Host only.
 */
#घोषणा USB_USBHSC	0xFFEC80f0

/* arch/sh/boards/renesas/sh7763rdp/irq.c */
व्योम init_sh7763rdp_IRQ(व्योम);
पूर्णांक sh7763rdp_irq_demux(पूर्णांक irq);
#घोषणा __IO_PREFIX	sh7763rdp
#समावेश <यंत्र/io_generic.h>

#पूर्ण_अगर /* __ASM_SH_SH7763RDP_H */
