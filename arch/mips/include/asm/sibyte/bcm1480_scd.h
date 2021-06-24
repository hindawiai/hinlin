<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*  *********************************************************************
    *  BCM1280/BCM1400 Board Support Package
    *
    *  SCD Constants and Macros			    File: bcm1480_scd.h
    *
    *  This module contains स्थिरants and macros useful क्रम
    *  manipulating the System Control and Debug module.
    *
    *  BCM1400 specअगरication level: 1X55_1X80-UM100-R (12/18/03)
    *
    *********************************************************************
    *
    *  Copyright 2000,2001,2002,2003,2004,2005
    *  Broadcom Corporation. All rights reserved.
    *
    ********************************************************************* */

#अगर_अघोषित _BCM1480_SCD_H
#घोषणा _BCM1480_SCD_H

#समावेश <यंत्र/sibyte/sb1250_defs.h>

/*  *********************************************************************
    *  Pull in the BCM1250's SCD since lots of stuff is the same.
    ********************************************************************* */

#समावेश <यंत्र/sibyte/sb1250_scd.h>

/*  *********************************************************************
    *  Some general notes:
    *
    *  This file is basically a "what's new" header file.  Since the
    *  BCM1250 and the new BCM1480 (and derivatives) share many common
    *  features, this file contains only what's new or changed from
    *  the 1250.  (above, you can see that we include the 1250 symbols
    *  to get the base functionality).
    *
    *  In software, be sure to use the correct symbols, particularly
    *  क्रम blocks that are dअगरferent between the two chip families.
    *  All BCM1480-specअगरic symbols have _BCM1480_ in their names,
    *  and all BCM1250-specअगरic and "base" functions that are common in
    *  both chips have no special names (this is क्रम compatibility with
    *  older include files).  Thereक्रमe, अगर you're working with the
    *  SCD, which is very dअगरferent on each chip, A_SCD_xxx implies
    *  the BCM1250 version and A_BCM1480_SCD_xxx implies the BCM1480
    *  version.
    ********************************************************************* */

/*  *********************************************************************
    *  System control/debug रेजिस्टरs
    ********************************************************************* */

/*
 * System Identअगरication and Revision Register (Table 12)
 * Register: SCD_SYSTEM_REVISION
 * This रेजिस्टर is field compatible with the 1250.
 */

/*
 * New part definitions
 */

#घोषणा K_SYS_PART_BCM1480	    0x1406
#घोषणा K_SYS_PART_BCM1280	    0x1206
#घोषणा K_SYS_PART_BCM1455	    0x1407
#घोषणा K_SYS_PART_BCM1255	    0x1257
#घोषणा K_SYS_PART_BCM1158	    0x1156

/*
 * Manufacturing Inक्रमmation Register (Table 14)
 * Register: SCD_SYSTEM_MANUF
 */

/*
 * System Configuration Register (Table 15)
 * Register: SCD_SYSTEM_CFG
 * Entire रेजिस्टर is dअगरferent from 1250, all new स्थिरants below
 */

#घोषणा M_BCM1480_SYS_RESERVED0		    _SB_MAKEMASK1(0)
#घोषणा M_BCM1480_SYS_HT_MINRSTCNT	    _SB_MAKEMASK1(1)
#घोषणा M_BCM1480_SYS_RESERVED2		    _SB_MAKEMASK1(2)
#घोषणा M_BCM1480_SYS_RESERVED3		    _SB_MAKEMASK1(3)
#घोषणा M_BCM1480_SYS_RESERVED4		    _SB_MAKEMASK1(4)
#घोषणा M_BCM1480_SYS_IOB_DIV		    _SB_MAKEMASK1(5)

#घोषणा S_BCM1480_SYS_PLL_DIV		    _SB_MAKE64(6)
#घोषणा M_BCM1480_SYS_PLL_DIV		    _SB_MAKEMASK(5, S_BCM1480_SYS_PLL_DIV)
#घोषणा V_BCM1480_SYS_PLL_DIV(x)	    _SB_MAKEVALUE(x, S_BCM1480_SYS_PLL_DIV)
#घोषणा G_BCM1480_SYS_PLL_DIV(x)	    _SB_GETVALUE(x, S_BCM1480_SYS_PLL_DIV, M_BCM1480_SYS_PLL_DIV)

#घोषणा S_BCM1480_SYS_SW_DIV		    _SB_MAKE64(11)
#घोषणा M_BCM1480_SYS_SW_DIV		    _SB_MAKEMASK(5, S_BCM1480_SYS_SW_DIV)
#घोषणा V_BCM1480_SYS_SW_DIV(x)		    _SB_MAKEVALUE(x, S_BCM1480_SYS_SW_DIV)
#घोषणा G_BCM1480_SYS_SW_DIV(x)		    _SB_GETVALUE(x, S_BCM1480_SYS_SW_DIV, M_BCM1480_SYS_SW_DIV)

#घोषणा M_BCM1480_SYS_PCMCIA_ENABLE	    _SB_MAKEMASK1(16)
#घोषणा M_BCM1480_SYS_DUART1_ENABLE	    _SB_MAKEMASK1(17)

#घोषणा S_BCM1480_SYS_BOOT_MODE		    _SB_MAKE64(18)
#घोषणा M_BCM1480_SYS_BOOT_MODE		    _SB_MAKEMASK(2, S_BCM1480_SYS_BOOT_MODE)
#घोषणा V_BCM1480_SYS_BOOT_MODE(x)	    _SB_MAKEVALUE(x, S_BCM1480_SYS_BOOT_MODE)
#घोषणा G_BCM1480_SYS_BOOT_MODE(x)	    _SB_GETVALUE(x, S_BCM1480_SYS_BOOT_MODE, M_BCM1480_SYS_BOOT_MODE)
#घोषणा K_BCM1480_SYS_BOOT_MODE_ROM32	    0
#घोषणा K_BCM1480_SYS_BOOT_MODE_ROM8	    1
#घोषणा K_BCM1480_SYS_BOOT_MODE_SMBUS_SMALL 2
#घोषणा K_BCM1480_SYS_BOOT_MODE_SMBUS_BIG   3
#घोषणा M_BCM1480_SYS_BOOT_MODE_SMBUS	    _SB_MAKEMASK1(19)

#घोषणा M_BCM1480_SYS_PCI_HOST		    _SB_MAKEMASK1(20)
#घोषणा M_BCM1480_SYS_PCI_ARBITER	    _SB_MAKEMASK1(21)
#घोषणा M_BCM1480_SYS_BIG_ENDIAN	    _SB_MAKEMASK1(22)
#घोषणा M_BCM1480_SYS_GENCLK_EN		    _SB_MAKEMASK1(23)
#घोषणा M_BCM1480_SYS_GEN_PARITY_EN	    _SB_MAKEMASK1(24)
#घोषणा M_BCM1480_SYS_RESERVED25	    _SB_MAKEMASK1(25)

#घोषणा S_BCM1480_SYS_CONFIG		    26
#घोषणा M_BCM1480_SYS_CONFIG		    _SB_MAKEMASK(6, S_BCM1480_SYS_CONFIG)
#घोषणा V_BCM1480_SYS_CONFIG(x)		    _SB_MAKEVALUE(x, S_BCM1480_SYS_CONFIG)
#घोषणा G_BCM1480_SYS_CONFIG(x)		    _SB_GETVALUE(x, S_BCM1480_SYS_CONFIG, M_BCM1480_SYS_CONFIG)

#घोषणा M_BCM1480_SYS_RESERVED32	    _SB_MAKEMASK(32, 15)

#घोषणा S_BCM1480_SYS_NODEID		    47
#घोषणा M_BCM1480_SYS_NODEID		    _SB_MAKEMASK(4, S_BCM1480_SYS_NODEID)
#घोषणा V_BCM1480_SYS_NODEID(x)		    _SB_MAKEVALUE(x, S_BCM1480_SYS_NODEID)
#घोषणा G_BCM1480_SYS_NODEID(x)		    _SB_GETVALUE(x, S_BCM1480_SYS_NODEID, M_BCM1480_SYS_NODEID)

#घोषणा M_BCM1480_SYS_CCNUMA_EN		    _SB_MAKEMASK1(51)
#घोषणा M_BCM1480_SYS_CPU_RESET_0	    _SB_MAKEMASK1(52)
#घोषणा M_BCM1480_SYS_CPU_RESET_1	    _SB_MAKEMASK1(53)
#घोषणा M_BCM1480_SYS_CPU_RESET_2	    _SB_MAKEMASK1(54)
#घोषणा M_BCM1480_SYS_CPU_RESET_3	    _SB_MAKEMASK1(55)
#घोषणा S_BCM1480_SYS_DISABLECPU0	    56
#घोषणा M_BCM1480_SYS_DISABLECPU0	    _SB_MAKEMASK1(S_BCM1480_SYS_DISABLECPU0)
#घोषणा S_BCM1480_SYS_DISABLECPU1	    57
#घोषणा M_BCM1480_SYS_DISABLECPU1	    _SB_MAKEMASK1(S_BCM1480_SYS_DISABLECPU1)
#घोषणा S_BCM1480_SYS_DISABLECPU2	    58
#घोषणा M_BCM1480_SYS_DISABLECPU2	    _SB_MAKEMASK1(S_BCM1480_SYS_DISABLECPU2)
#घोषणा S_BCM1480_SYS_DISABLECPU3	    59
#घोषणा M_BCM1480_SYS_DISABLECPU3	    _SB_MAKEMASK1(S_BCM1480_SYS_DISABLECPU3)

#घोषणा M_BCM1480_SYS_SB_SOFTRES	    _SB_MAKEMASK1(60)
#घोषणा M_BCM1480_SYS_EXT_RESET		    _SB_MAKEMASK1(61)
#घोषणा M_BCM1480_SYS_SYSTEM_RESET	    _SB_MAKEMASK1(62)
#घोषणा M_BCM1480_SYS_SW_FLAG		    _SB_MAKEMASK1(63)

/*
 * Scratch Register (Table 16)
 * Register: SCD_SYSTEM_SCRATCH
 * Same as BCM1250
 */


/*
 * Mailbox Registers (Table 17)
 * Registers: SCD_MBOX_अणु0,1पूर्ण_CPU_x
 * Same as BCM1250
 */


/*
 * See bcm1480_पूर्णांक.h क्रम पूर्णांकerrupt mapper रेजिस्टरs.
 */


/*
 * Watchकरोg Timer Initial Count Registers (Table 23)
 * Registers: SCD_WDOG_INIT_CNT_x
 *
 * The watchकरोgs are almost the same as the 1250, except
 * the configuration रेजिस्टर has more bits to control the
 * other CPUs.
 */


/*
 * Watchकरोg Timer Configuration Registers (Table 25)
 * Registers: SCD_WDOG_CFG_x
 */

#घोषणा M_BCM1480_SCD_WDOG_ENABLE	    _SB_MAKEMASK1(0)

#घोषणा S_BCM1480_SCD_WDOG_RESET_TYPE	    2
#घोषणा M_BCM1480_SCD_WDOG_RESET_TYPE	    _SB_MAKEMASK(5, S_BCM1480_SCD_WDOG_RESET_TYPE)
#घोषणा V_BCM1480_SCD_WDOG_RESET_TYPE(x)    _SB_MAKEVALUE(x, S_BCM1480_SCD_WDOG_RESET_TYPE)
#घोषणा G_BCM1480_SCD_WDOG_RESET_TYPE(x)    _SB_GETVALUE(x, S_BCM1480_SCD_WDOG_RESET_TYPE, M_BCM1480_SCD_WDOG_RESET_TYPE)

#घोषणा K_BCM1480_SCD_WDOG_RESET_FULL	    0	/* actually, (x & 1) == 0  */
#घोषणा K_BCM1480_SCD_WDOG_RESET_SOFT	    1
#घोषणा K_BCM1480_SCD_WDOG_RESET_CPU0	    3
#घोषणा K_BCM1480_SCD_WDOG_RESET_CPU1	    5
#घोषणा K_BCM1480_SCD_WDOG_RESET_CPU2	    9
#घोषणा K_BCM1480_SCD_WDOG_RESET_CPU3	    17
#घोषणा K_BCM1480_SCD_WDOG_RESET_ALL_CPUS   31


#घोषणा M_BCM1480_SCD_WDOG_HAS_RESET	    _SB_MAKEMASK1(8)

/*
 * General Timer Initial Count Registers (Table 26)
 * Registers: SCD_TIMER_INIT_x
 *
 * The समयr रेजिस्टरs are the same as the BCM1250
 */


/*
 * ZBbus Count Register (Table 29)
 * Register: ZBBUS_CYCLE_COUNT
 *
 * Same as BCM1250
 */

/*
 * ZBbus Compare Registers (Table 30)
 * Registers: ZBBUS_CYCLE_CPx
 *
 * Same as BCM1250
 */


/*
 * System Perक्रमmance Counter Configuration Register (Table 31)
 * Register: PERF_CNT_CFG_0
 *
 * SPC_CFG_SRC[0-3] is the same as the 1250.
 * SPC_CFG_SRC[4-7] only exist on the 1480
 * The clear/enable bits are in dअगरferent locations on the 1250 and 1480.
 */

#घोषणा S_SPC_CFG_SRC4		    32
#घोषणा M_SPC_CFG_SRC4		    _SB_MAKEMASK(8, S_SPC_CFG_SRC4)
#घोषणा V_SPC_CFG_SRC4(x)	    _SB_MAKEVALUE(x, S_SPC_CFG_SRC4)
#घोषणा G_SPC_CFG_SRC4(x)	    _SB_GETVALUE(x, S_SPC_CFG_SRC4, M_SPC_CFG_SRC4)

#घोषणा S_SPC_CFG_SRC5		    40
#घोषणा M_SPC_CFG_SRC5		    _SB_MAKEMASK(8, S_SPC_CFG_SRC5)
#घोषणा V_SPC_CFG_SRC5(x)	    _SB_MAKEVALUE(x, S_SPC_CFG_SRC5)
#घोषणा G_SPC_CFG_SRC5(x)	    _SB_GETVALUE(x, S_SPC_CFG_SRC5, M_SPC_CFG_SRC5)

#घोषणा S_SPC_CFG_SRC6		    48
#घोषणा M_SPC_CFG_SRC6		    _SB_MAKEMASK(8, S_SPC_CFG_SRC6)
#घोषणा V_SPC_CFG_SRC6(x)	    _SB_MAKEVALUE(x, S_SPC_CFG_SRC6)
#घोषणा G_SPC_CFG_SRC6(x)	    _SB_GETVALUE(x, S_SPC_CFG_SRC6, M_SPC_CFG_SRC6)

#घोषणा S_SPC_CFG_SRC7		    56
#घोषणा M_SPC_CFG_SRC7		    _SB_MAKEMASK(8, S_SPC_CFG_SRC7)
#घोषणा V_SPC_CFG_SRC7(x)	    _SB_MAKEVALUE(x, S_SPC_CFG_SRC7)
#घोषणा G_SPC_CFG_SRC7(x)	    _SB_GETVALUE(x, S_SPC_CFG_SRC7, M_SPC_CFG_SRC7)

/*
 * System Perक्रमmance Counter Control Register (Table 32)
 * Register: PERF_CNT_CFG_1
 * BCM1480 specअगरic
 */
#घोषणा M_BCM1480_SPC_CFG_CLEAR	    _SB_MAKEMASK1(0)
#घोषणा M_BCM1480_SPC_CFG_ENABLE    _SB_MAKEMASK1(1)
#अगर SIBYTE_HDR_FEATURE_CHIP(1480)
#घोषणा M_SPC_CFG_CLEAR			M_BCM1480_SPC_CFG_CLEAR
#घोषणा M_SPC_CFG_ENABLE		M_BCM1480_SPC_CFG_ENABLE
#पूर्ण_अगर

/*
 * System Perक्रमmance Counters (Table 33)
 * Registers: PERF_CNT_x
 */

#घोषणा S_BCM1480_SPC_CNT_COUNT		    0
#घोषणा M_BCM1480_SPC_CNT_COUNT		    _SB_MAKEMASK(40, S_BCM1480_SPC_CNT_COUNT)
#घोषणा V_BCM1480_SPC_CNT_COUNT(x)	    _SB_MAKEVALUE(x, S_BCM1480_SPC_CNT_COUNT)
#घोषणा G_BCM1480_SPC_CNT_COUNT(x)	    _SB_GETVALUE(x, S_BCM1480_SPC_CNT_COUNT, M_BCM1480_SPC_CNT_COUNT)

#घोषणा M_BCM1480_SPC_CNT_OFLOW		    _SB_MAKEMASK1(40)


/*
 * Bus Watcher Error Status Register (Tables 36, 37)
 * Registers: BUS_ERR_STATUS, BUS_ERR_STATUS_DEBUG
 * Same as BCM1250.
 */

/*
 * Bus Watcher Error Data Registers (Table 38)
 * Registers: BUS_ERR_DATA_x
 * Same as BCM1250.
 */

/*
 * Bus Watcher L2 ECC Counter Register (Table 39)
 * Register: BUS_L2_ERRORS
 * Same as BCM1250.
 */


/*
 * Bus Watcher Memory and I/O Error Counter Register (Table 40)
 * Register: BUS_MEM_IO_ERRORS
 * Same as BCM1250.
 */


/*
 * Address Trap Registers
 *
 * Register layout same as BCM1250, almost.  The bus agents
 * are dअगरferent, and the address trap configuration bits are
 * slightly dअगरferent.
 */

#घोषणा M_BCM1480_ATRAP_INDEX		  _SB_MAKEMASK(4, 0)
#घोषणा M_BCM1480_ATRAP_ADDRESS		  _SB_MAKEMASK(40, 0)

#घोषणा S_BCM1480_ATRAP_CFG_CNT		   0
#घोषणा M_BCM1480_ATRAP_CFG_CNT		   _SB_MAKEMASK(3, S_BCM1480_ATRAP_CFG_CNT)
#घोषणा V_BCM1480_ATRAP_CFG_CNT(x)	   _SB_MAKEVALUE(x, S_BCM1480_ATRAP_CFG_CNT)
#घोषणा G_BCM1480_ATRAP_CFG_CNT(x)	   _SB_GETVALUE(x, S_BCM1480_ATRAP_CFG_CNT, M_BCM1480_ATRAP_CFG_CNT)

#घोषणा M_BCM1480_ATRAP_CFG_WRITE	   _SB_MAKEMASK1(3)
#घोषणा M_BCM1480_ATRAP_CFG_ALL		   _SB_MAKEMASK1(4)
#घोषणा M_BCM1480_ATRAP_CFG_INV		   _SB_MAKEMASK1(5)
#घोषणा M_BCM1480_ATRAP_CFG_USESRC	   _SB_MAKEMASK1(6)
#घोषणा M_BCM1480_ATRAP_CFG_SRCINV	   _SB_MAKEMASK1(7)

#घोषणा S_BCM1480_ATRAP_CFG_AGENTID	8
#घोषणा M_BCM1480_ATRAP_CFG_AGENTID	_SB_MAKEMASK(4, S_BCM1480_ATRAP_CFG_AGENTID)
#घोषणा V_BCM1480_ATRAP_CFG_AGENTID(x)	_SB_MAKEVALUE(x, S_BCM1480_ATRAP_CFG_AGENTID)
#घोषणा G_BCM1480_ATRAP_CFG_AGENTID(x)	_SB_GETVALUE(x, S_BCM1480_ATRAP_CFG_AGENTID, M_BCM1480_ATRAP_CFG_AGENTID)


#घोषणा K_BCM1480_BUS_AGENT_CPU0	    0
#घोषणा K_BCM1480_BUS_AGENT_CPU1	    1
#घोषणा K_BCM1480_BUS_AGENT_NC		    2
#घोषणा K_BCM1480_BUS_AGENT_IOB		    3
#घोषणा K_BCM1480_BUS_AGENT_SCD		    4
#घोषणा K_BCM1480_BUS_AGENT_L2C		    6
#घोषणा K_BCM1480_BUS_AGENT_MC		    7
#घोषणा K_BCM1480_BUS_AGENT_CPU2	    8
#घोषणा K_BCM1480_BUS_AGENT_CPU3	    9
#घोषणा K_BCM1480_BUS_AGENT_PM		    10

#घोषणा S_BCM1480_ATRAP_CFG_CATTR	    12
#घोषणा M_BCM1480_ATRAP_CFG_CATTR	    _SB_MAKEMASK(2, S_BCM1480_ATRAP_CFG_CATTR)
#घोषणा V_BCM1480_ATRAP_CFG_CATTR(x)	    _SB_MAKEVALUE(x, S_BCM1480_ATRAP_CFG_CATTR)
#घोषणा G_BCM1480_ATRAP_CFG_CATTR(x)	    _SB_GETVALUE(x, S_BCM1480_ATRAP_CFG_CATTR, M_BCM1480_ATRAP_CFG_CATTR)

#घोषणा K_BCM1480_ATRAP_CFG_CATTR_IGNORE    0
#घोषणा K_BCM1480_ATRAP_CFG_CATTR_UNC	    1
#घोषणा K_BCM1480_ATRAP_CFG_CATTR_NONCOH    2
#घोषणा K_BCM1480_ATRAP_CFG_CATTR_COHERENT  3

#घोषणा M_BCM1480_ATRAP_CFG_CATTRINV	    _SB_MAKEMASK1(14)


/*
 * Trace Event Registers (Table 47)
 * Same as BCM1250.
 */

/*
 * Trace Sequence Control Registers (Table 48)
 * Registers: TRACE_SEQUENCE_x
 *
 * Same as BCM1250 except क्रम two new fields.
 */


#घोषणा M_BCM1480_SCD_TRSEQ_TID_MATCH_EN    _SB_MAKEMASK1(25)

#घोषणा S_BCM1480_SCD_TRSEQ_SWFUNC	    26
#घोषणा M_BCM1480_SCD_TRSEQ_SWFUNC	    _SB_MAKEMASK(2, S_BCM1480_SCD_TRSEQ_SWFUNC)
#घोषणा V_BCM1480_SCD_TRSEQ_SWFUNC(x)	    _SB_MAKEVALUE(x, S_BCM1480_SCD_TRSEQ_SWFUNC)
#घोषणा G_BCM1480_SCD_TRSEQ_SWFUNC(x)	    _SB_GETVALUE(x, S_BCM1480_SCD_TRSEQ_SWFUNC, M_BCM1480_SCD_TRSEQ_SWFUNC)

/*
 * Trace Control Register (Table 49)
 * Register: TRACE_CFG
 *
 * BCM1480 changes to this रेजिस्टर (other than location of the CUR_ADDR field)
 * are defined below.
 */

#घोषणा S_BCM1480_SCD_TRACE_CFG_MODE	    16
#घोषणा M_BCM1480_SCD_TRACE_CFG_MODE	    _SB_MAKEMASK(2, S_BCM1480_SCD_TRACE_CFG_MODE)
#घोषणा V_BCM1480_SCD_TRACE_CFG_MODE(x)	    _SB_MAKEVALUE(x, S_BCM1480_SCD_TRACE_CFG_MODE)
#घोषणा G_BCM1480_SCD_TRACE_CFG_MODE(x)	    _SB_GETVALUE(x, S_BCM1480_SCD_TRACE_CFG_MODE, M_BCM1480_SCD_TRACE_CFG_MODE)

#घोषणा K_BCM1480_SCD_TRACE_CFG_MODE_BLOCKERS	0
#घोषणा K_BCM1480_SCD_TRACE_CFG_MODE_BYTEEN_INT 1
#घोषणा K_BCM1480_SCD_TRACE_CFG_MODE_FLOW_ID	2

#पूर्ण_अगर /* _BCM1480_SCD_H */
