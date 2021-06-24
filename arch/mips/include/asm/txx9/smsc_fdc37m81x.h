<शैली गुरु>
/*
 * Interface क्रम smsc fdc48m81x Super IO chip
 *
 * Author: MontaVista Software, Inc. source@mvista.com
 *
 * 2001-2003 (c) MontaVista Software, Inc. This file is licensed under
 * the terms of the GNU General Public License version 2. This program
 * is licensed "as is" without any warranty of any kind, whether express
 * or implied.
 *
 * Copyright (C) 2004 MontaVista Software Inc.
 * Manish Lachwani, mlachwani@mvista.com
 */

#अगर_अघोषित _SMSC_FDC37M81X_H_
#घोषणा _SMSC_FDC37M81X_H_

/* Common Registers */
#घोषणा SMSC_FDC37M81X_CONFIG_INDEX  0x00
#घोषणा SMSC_FDC37M81X_CONFIG_DATA   0x01
#घोषणा SMSC_FDC37M81X_CONF	     0x02
#घोषणा SMSC_FDC37M81X_INDEX	     0x03
#घोषणा SMSC_FDC37M81X_DNUM	     0x07
#घोषणा SMSC_FDC37M81X_DID	     0x20
#घोषणा SMSC_FDC37M81X_DREV	     0x21
#घोषणा SMSC_FDC37M81X_PCNT	     0x22
#घोषणा SMSC_FDC37M81X_PMGT	     0x23
#घोषणा SMSC_FDC37M81X_OSC	     0x24
#घोषणा SMSC_FDC37M81X_CONFPA0	     0x26
#घोषणा SMSC_FDC37M81X_CONFPA1	     0x27
#घोषणा SMSC_FDC37M81X_TEST4	     0x2B
#घोषणा SMSC_FDC37M81X_TEST5	     0x2C
#घोषणा SMSC_FDC37M81X_TEST1	     0x2D
#घोषणा SMSC_FDC37M81X_TEST2	     0x2E
#घोषणा SMSC_FDC37M81X_TEST3	     0x2F

/* Logical device numbers */
#घोषणा SMSC_FDC37M81X_FDD	     0x00
#घोषणा SMSC_FDC37M81X_PARALLEL	     0x03
#घोषणा SMSC_FDC37M81X_SERIAL1	     0x04
#घोषणा SMSC_FDC37M81X_SERIAL2	     0x05
#घोषणा SMSC_FDC37M81X_KBD	     0x07
#घोषणा SMSC_FDC37M81X_AUXIO	     0x08
#घोषणा SMSC_FDC37M81X_NONE	     0xff

/* Logical device Config Registers */
#घोषणा SMSC_FDC37M81X_ACTIVE	     0x30
#घोषणा SMSC_FDC37M81X_BASEADDR0     0x60
#घोषणा SMSC_FDC37M81X_BASEADDR1     0x61
#घोषणा SMSC_FDC37M81X_INT	     0x70
#घोषणा SMSC_FDC37M81X_INT2	     0x72
#घोषणा SMSC_FDC37M81X_LDCR_F0	     0xF0

/* Chip Config Values */
#घोषणा SMSC_FDC37M81X_CONFIG_ENTER  0x55
#घोषणा SMSC_FDC37M81X_CONFIG_EXIT   0xaa
#घोषणा SMSC_FDC37M81X_CHIP_ID	     0x4d

अचिन्हित दीर्घ smsc_fdc37m81x_init(अचिन्हित दीर्घ port);

व्योम smsc_fdc37m81x_config_beg(व्योम);

व्योम smsc_fdc37m81x_config_end(व्योम);

u8 smsc_fdc37m81x_config_get(u8 reg);
व्योम smsc_fdc37m81x_config_set(u8 reg, u8 val);

#पूर्ण_अगर
