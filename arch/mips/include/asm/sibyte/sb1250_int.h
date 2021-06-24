<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*  *********************************************************************
    *  SB1250 Board Support Package
    *
    *  Interrupt Mapper definitions		File: sb1250_पूर्णांक.h
    *
    *  This module contains स्थिरants क्रम manipulating the SB1250's
    *  पूर्णांकerrupt mapper and definitions क्रम the पूर्णांकerrupt sources.
    *
    *  SB1250 specअगरication level:  User's manual 1/02/02
    *
    *********************************************************************
    *
    *  Copyright 2000, 2001, 2002, 2003
    *  Broadcom Corporation. All rights reserved.
    *
    ********************************************************************* */


#अगर_अघोषित _SB1250_INT_H
#घोषणा _SB1250_INT_H

#समावेश <यंत्र/sibyte/sb1250_defs.h>

/*  *********************************************************************
    *  Interrupt Mapper Constants
    ********************************************************************* */

/*
 * Interrupt sources (Table 4-8, UM 0.2)
 *
 * First, the पूर्णांकerrupt numbers.
 */

#घोषणा K_INT_SOURCES		    64

#घोषणा K_INT_WATCHDOG_TIMER_0	    0
#घोषणा K_INT_WATCHDOG_TIMER_1	    1
#घोषणा K_INT_TIMER_0		    2
#घोषणा K_INT_TIMER_1		    3
#घोषणा K_INT_TIMER_2		    4
#घोषणा K_INT_TIMER_3		    5
#घोषणा K_INT_SMB_0		    6
#घोषणा K_INT_SMB_1		    7
#घोषणा K_INT_UART_0		    8
#घोषणा K_INT_UART_1		    9
#घोषणा K_INT_SER_0		    10
#घोषणा K_INT_SER_1		    11
#घोषणा K_INT_PCMCIA		    12
#घोषणा K_INT_ADDR_TRAP		    13
#घोषणा K_INT_PERF_CNT		    14
#घोषणा K_INT_TRACE_FREEZE	    15
#घोषणा K_INT_BAD_ECC		    16
#घोषणा K_INT_COR_ECC		    17
#घोषणा K_INT_IO_BUS		    18
#घोषणा K_INT_MAC_0		    19
#घोषणा K_INT_MAC_1		    20
#घोषणा K_INT_MAC_2		    21
#घोषणा K_INT_DM_CH_0		    22
#घोषणा K_INT_DM_CH_1		    23
#घोषणा K_INT_DM_CH_2		    24
#घोषणा K_INT_DM_CH_3		    25
#घोषणा K_INT_MBOX_0		    26
#घोषणा K_INT_MBOX_1		    27
#घोषणा K_INT_MBOX_2		    28
#घोषणा K_INT_MBOX_3		    29
#अगर SIBYTE_HDR_FEATURE(1250, PASS2) || SIBYTE_HDR_FEATURE(112x, PASS1)
#घोषणा K_INT_CYCLE_CP0_INT	    30
#घोषणा K_INT_CYCLE_CP1_INT	    31
#पूर्ण_अगर /* 1250 PASS2 || 112x PASS1 */
#घोषणा K_INT_GPIO_0		    32
#घोषणा K_INT_GPIO_1		    33
#घोषणा K_INT_GPIO_2		    34
#घोषणा K_INT_GPIO_3		    35
#घोषणा K_INT_GPIO_4		    36
#घोषणा K_INT_GPIO_5		    37
#घोषणा K_INT_GPIO_6		    38
#घोषणा K_INT_GPIO_7		    39
#घोषणा K_INT_GPIO_8		    40
#घोषणा K_INT_GPIO_9		    41
#घोषणा K_INT_GPIO_10		    42
#घोषणा K_INT_GPIO_11		    43
#घोषणा K_INT_GPIO_12		    44
#घोषणा K_INT_GPIO_13		    45
#घोषणा K_INT_GPIO_14		    46
#घोषणा K_INT_GPIO_15		    47
#घोषणा K_INT_LDT_FATAL		    48
#घोषणा K_INT_LDT_NONFATAL	    49
#घोषणा K_INT_LDT_SMI		    50
#घोषणा K_INT_LDT_NMI		    51
#घोषणा K_INT_LDT_INIT		    52
#घोषणा K_INT_LDT_STARTUP	    53
#घोषणा K_INT_LDT_EXT		    54
#घोषणा K_INT_PCI_ERROR		    55
#घोषणा K_INT_PCI_INTA		    56
#घोषणा K_INT_PCI_INTB		    57
#घोषणा K_INT_PCI_INTC		    58
#घोषणा K_INT_PCI_INTD		    59
#घोषणा K_INT_SPARE_2		    60
#अगर SIBYTE_HDR_FEATURE(1250, PASS2) || SIBYTE_HDR_FEATURE(112x, PASS1)
#घोषणा K_INT_MAC_0_CH1		    61
#घोषणा K_INT_MAC_1_CH1		    62
#घोषणा K_INT_MAC_2_CH1		    63
#पूर्ण_अगर /* 1250 PASS2 || 112x PASS1 */

/*
 * Mask values क्रम each पूर्णांकerrupt
 */

#घोषणा M_INT_WATCHDOG_TIMER_0	    _SB_MAKEMASK1(K_INT_WATCHDOG_TIMER_0)
#घोषणा M_INT_WATCHDOG_TIMER_1	    _SB_MAKEMASK1(K_INT_WATCHDOG_TIMER_1)
#घोषणा M_INT_TIMER_0		    _SB_MAKEMASK1(K_INT_TIMER_0)
#घोषणा M_INT_TIMER_1		    _SB_MAKEMASK1(K_INT_TIMER_1)
#घोषणा M_INT_TIMER_2		    _SB_MAKEMASK1(K_INT_TIMER_2)
#घोषणा M_INT_TIMER_3		    _SB_MAKEMASK1(K_INT_TIMER_3)
#घोषणा M_INT_SMB_0		    _SB_MAKEMASK1(K_INT_SMB_0)
#घोषणा M_INT_SMB_1		    _SB_MAKEMASK1(K_INT_SMB_1)
#घोषणा M_INT_UART_0		    _SB_MAKEMASK1(K_INT_UART_0)
#घोषणा M_INT_UART_1		    _SB_MAKEMASK1(K_INT_UART_1)
#घोषणा M_INT_SER_0		    _SB_MAKEMASK1(K_INT_SER_0)
#घोषणा M_INT_SER_1		    _SB_MAKEMASK1(K_INT_SER_1)
#घोषणा M_INT_PCMCIA		    _SB_MAKEMASK1(K_INT_PCMCIA)
#घोषणा M_INT_ADDR_TRAP		    _SB_MAKEMASK1(K_INT_ADDR_TRAP)
#घोषणा M_INT_PERF_CNT		    _SB_MAKEMASK1(K_INT_PERF_CNT)
#घोषणा M_INT_TRACE_FREEZE	    _SB_MAKEMASK1(K_INT_TRACE_FREEZE)
#घोषणा M_INT_BAD_ECC		    _SB_MAKEMASK1(K_INT_BAD_ECC)
#घोषणा M_INT_COR_ECC		    _SB_MAKEMASK1(K_INT_COR_ECC)
#घोषणा M_INT_IO_BUS		    _SB_MAKEMASK1(K_INT_IO_BUS)
#घोषणा M_INT_MAC_0		    _SB_MAKEMASK1(K_INT_MAC_0)
#घोषणा M_INT_MAC_1		    _SB_MAKEMASK1(K_INT_MAC_1)
#घोषणा M_INT_MAC_2		    _SB_MAKEMASK1(K_INT_MAC_2)
#घोषणा M_INT_DM_CH_0		    _SB_MAKEMASK1(K_INT_DM_CH_0)
#घोषणा M_INT_DM_CH_1		    _SB_MAKEMASK1(K_INT_DM_CH_1)
#घोषणा M_INT_DM_CH_2		    _SB_MAKEMASK1(K_INT_DM_CH_2)
#घोषणा M_INT_DM_CH_3		    _SB_MAKEMASK1(K_INT_DM_CH_3)
#घोषणा M_INT_MBOX_0		    _SB_MAKEMASK1(K_INT_MBOX_0)
#घोषणा M_INT_MBOX_1		    _SB_MAKEMASK1(K_INT_MBOX_1)
#घोषणा M_INT_MBOX_2		    _SB_MAKEMASK1(K_INT_MBOX_2)
#घोषणा M_INT_MBOX_3		    _SB_MAKEMASK1(K_INT_MBOX_3)
#घोषणा M_INT_MBOX_ALL		    _SB_MAKEMASK(4, K_INT_MBOX_0)
#अगर SIBYTE_HDR_FEATURE(1250, PASS2) || SIBYTE_HDR_FEATURE(112x, PASS1)
#घोषणा M_INT_CYCLE_CP0_INT	    _SB_MAKEMASK1(K_INT_CYCLE_CP0_INT)
#घोषणा M_INT_CYCLE_CP1_INT	    _SB_MAKEMASK1(K_INT_CYCLE_CP1_INT)
#पूर्ण_अगर /* 1250 PASS2 || 112x PASS1 */
#घोषणा M_INT_GPIO_0		    _SB_MAKEMASK1(K_INT_GPIO_0)
#घोषणा M_INT_GPIO_1		    _SB_MAKEMASK1(K_INT_GPIO_1)
#घोषणा M_INT_GPIO_2		    _SB_MAKEMASK1(K_INT_GPIO_2)
#घोषणा M_INT_GPIO_3		    _SB_MAKEMASK1(K_INT_GPIO_3)
#घोषणा M_INT_GPIO_4		    _SB_MAKEMASK1(K_INT_GPIO_4)
#घोषणा M_INT_GPIO_5		    _SB_MAKEMASK1(K_INT_GPIO_5)
#घोषणा M_INT_GPIO_6		    _SB_MAKEMASK1(K_INT_GPIO_6)
#घोषणा M_INT_GPIO_7		    _SB_MAKEMASK1(K_INT_GPIO_7)
#घोषणा M_INT_GPIO_8		    _SB_MAKEMASK1(K_INT_GPIO_8)
#घोषणा M_INT_GPIO_9		    _SB_MAKEMASK1(K_INT_GPIO_9)
#घोषणा M_INT_GPIO_10		    _SB_MAKEMASK1(K_INT_GPIO_10)
#घोषणा M_INT_GPIO_11		    _SB_MAKEMASK1(K_INT_GPIO_11)
#घोषणा M_INT_GPIO_12		    _SB_MAKEMASK1(K_INT_GPIO_12)
#घोषणा M_INT_GPIO_13		    _SB_MAKEMASK1(K_INT_GPIO_13)
#घोषणा M_INT_GPIO_14		    _SB_MAKEMASK1(K_INT_GPIO_14)
#घोषणा M_INT_GPIO_15		    _SB_MAKEMASK1(K_INT_GPIO_15)
#घोषणा M_INT_LDT_FATAL		    _SB_MAKEMASK1(K_INT_LDT_FATAL)
#घोषणा M_INT_LDT_NONFATAL	    _SB_MAKEMASK1(K_INT_LDT_NONFATAL)
#घोषणा M_INT_LDT_SMI		    _SB_MAKEMASK1(K_INT_LDT_SMI)
#घोषणा M_INT_LDT_NMI		    _SB_MAKEMASK1(K_INT_LDT_NMI)
#घोषणा M_INT_LDT_INIT		    _SB_MAKEMASK1(K_INT_LDT_INIT)
#घोषणा M_INT_LDT_STARTUP	    _SB_MAKEMASK1(K_INT_LDT_STARTUP)
#घोषणा M_INT_LDT_EXT		    _SB_MAKEMASK1(K_INT_LDT_EXT)
#घोषणा M_INT_PCI_ERROR		    _SB_MAKEMASK1(K_INT_PCI_ERROR)
#घोषणा M_INT_PCI_INTA		    _SB_MAKEMASK1(K_INT_PCI_INTA)
#घोषणा M_INT_PCI_INTB		    _SB_MAKEMASK1(K_INT_PCI_INTB)
#घोषणा M_INT_PCI_INTC		    _SB_MAKEMASK1(K_INT_PCI_INTC)
#घोषणा M_INT_PCI_INTD		    _SB_MAKEMASK1(K_INT_PCI_INTD)
#घोषणा M_INT_SPARE_2		    _SB_MAKEMASK1(K_INT_SPARE_2)
#अगर SIBYTE_HDR_FEATURE(1250, PASS2) || SIBYTE_HDR_FEATURE(112x, PASS1)
#घोषणा M_INT_MAC_0_CH1		    _SB_MAKEMASK1(K_INT_MAC_0_CH1)
#घोषणा M_INT_MAC_1_CH1		    _SB_MAKEMASK1(K_INT_MAC_1_CH1)
#घोषणा M_INT_MAC_2_CH1		    _SB_MAKEMASK1(K_INT_MAC_2_CH1)
#पूर्ण_अगर /* 1250 PASS2 || 112x PASS1 */

/*
 * Interrupt mappings
 */

#घोषणा K_INT_MAP_I0	0		/* पूर्णांकerrupt pins on processor */
#घोषणा K_INT_MAP_I1	1
#घोषणा K_INT_MAP_I2	2
#घोषणा K_INT_MAP_I3	3
#घोषणा K_INT_MAP_I4	4
#घोषणा K_INT_MAP_I5	5
#घोषणा K_INT_MAP_NMI	6		/* nonmaskable */
#घोषणा K_INT_MAP_DINT	7		/* debug पूर्णांकerrupt */

/*
 * LDT Interrupt Set Register (table 4-5)
 */

#घोषणा S_INT_LDT_INTMSG	      0
#घोषणा M_INT_LDT_INTMSG	      _SB_MAKEMASK(3, S_INT_LDT_INTMSG)
#घोषणा V_INT_LDT_INTMSG(x)	      _SB_MAKEVALUE(x, S_INT_LDT_INTMSG)
#घोषणा G_INT_LDT_INTMSG(x)	      _SB_GETVALUE(x, S_INT_LDT_INTMSG, M_INT_LDT_INTMSG)

#घोषणा K_INT_LDT_INTMSG_FIXED	      0
#घोषणा K_INT_LDT_INTMSG_ARBITRATED   1
#घोषणा K_INT_LDT_INTMSG_SMI	      2
#घोषणा K_INT_LDT_INTMSG_NMI	      3
#घोषणा K_INT_LDT_INTMSG_INIT	      4
#घोषणा K_INT_LDT_INTMSG_STARTUP      5
#घोषणा K_INT_LDT_INTMSG_EXTINT	      6
#घोषणा K_INT_LDT_INTMSG_RESERVED     7

#घोषणा M_INT_LDT_EDGETRIGGER	      0
#घोषणा M_INT_LDT_LEVELTRIGGER	      _SB_MAKEMASK1(3)

#घोषणा M_INT_LDT_PHYSICALDEST	      0
#घोषणा M_INT_LDT_LOGICALDEST	      _SB_MAKEMASK1(4)

#घोषणा S_INT_LDT_INTDEST	      5
#घोषणा M_INT_LDT_INTDEST	      _SB_MAKEMASK(10, S_INT_LDT_INTDEST)
#घोषणा V_INT_LDT_INTDEST(x)	      _SB_MAKEVALUE(x, S_INT_LDT_INTDEST)
#घोषणा G_INT_LDT_INTDEST(x)	      _SB_GETVALUE(x, S_INT_LDT_INTDEST, M_INT_LDT_INTDEST)

#घोषणा S_INT_LDT_VECTOR	      13
#घोषणा M_INT_LDT_VECTOR	      _SB_MAKEMASK(8, S_INT_LDT_VECTOR)
#घोषणा V_INT_LDT_VECTOR(x)	      _SB_MAKEVALUE(x, S_INT_LDT_VECTOR)
#घोषणा G_INT_LDT_VECTOR(x)	      _SB_GETVALUE(x, S_INT_LDT_VECTOR, M_INT_LDT_VECTOR)

/*
 * Vector क्रमmat (Table 4-6)
 */

#घोषणा M_LDTVECT_RAISEINT		0x00
#घोषणा M_LDTVECT_RAISEMBOX		0x40


#पूर्ण_अगर	/* 1250/112x */
