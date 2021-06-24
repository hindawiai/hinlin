<शैली गुरु>
/*****************************************************************************
 *                                                                           *
 * File: regs.h                                                              *
 * $Revision: 1.8 $                                                          *
 * $Date: 2005/06/21 18:29:48 $                                              *
 * Description:                                                              *
 *  part of the Chelsio 10Gb Ethernet Driver.                                *
 *                                                                           *
 * This program is मुक्त software; you can redistribute it and/or modअगरy      *
 * it under the terms of the GNU General Public License, version 2, as       *
 * published by the Free Software Foundation.                                *
 *                                                                           *
 * You should have received a copy of the GNU General Public License aदीर्घ   *
 * with this program; अगर not, see <http://www.gnu.org/licenses/>.            *
 *                                                                           *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR IMPLIED    *
 * WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED WARRANTIES OF      *
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.                     *
 *                                                                           *
 * http://www.chelsio.com                                                    *
 *                                                                           *
 * Copyright (c) 2003 - 2005 Chelsio Communications, Inc.                    *
 * All rights reserved.                                                      *
 *                                                                           *
 * Maपूर्णांकainers: मुख्यtainers@chelsio.com                                      *
 *                                                                           *
 * Authors: Dimitrios Michailidis   <dm@chelsio.com>                         *
 *          Tina Yang               <tainay@chelsio.com>                     *
 *          Felix Marti             <felix@chelsio.com>                      *
 *          Scott Barकरोne           <sbarकरोne@chelsio.com>                   *
 *          Kurt Ottaway            <kottaway@chelsio.com>                   *
 *          Frank DiMambro          <frank@chelsio.com>                      *
 *                                                                           *
 * History:                                                                  *
 *                                                                           *
 ****************************************************************************/

#अगर_अघोषित _CXGB_REGS_H_
#घोषणा _CXGB_REGS_H_

/* SGE रेजिस्टरs */
#घोषणा A_SG_CONTROL 0x0

#घोषणा S_CMDQ0_ENABLE    0
#घोषणा V_CMDQ0_ENABLE(x) ((x) << S_CMDQ0_ENABLE)
#घोषणा F_CMDQ0_ENABLE    V_CMDQ0_ENABLE(1U)

#घोषणा S_CMDQ1_ENABLE    1
#घोषणा V_CMDQ1_ENABLE(x) ((x) << S_CMDQ1_ENABLE)
#घोषणा F_CMDQ1_ENABLE    V_CMDQ1_ENABLE(1U)

#घोषणा S_FL0_ENABLE    2
#घोषणा V_FL0_ENABLE(x) ((x) << S_FL0_ENABLE)
#घोषणा F_FL0_ENABLE    V_FL0_ENABLE(1U)

#घोषणा S_FL1_ENABLE    3
#घोषणा V_FL1_ENABLE(x) ((x) << S_FL1_ENABLE)
#घोषणा F_FL1_ENABLE    V_FL1_ENABLE(1U)

#घोषणा S_CPL_ENABLE    4
#घोषणा V_CPL_ENABLE(x) ((x) << S_CPL_ENABLE)
#घोषणा F_CPL_ENABLE    V_CPL_ENABLE(1U)

#घोषणा S_RESPONSE_QUEUE_ENABLE    5
#घोषणा V_RESPONSE_QUEUE_ENABLE(x) ((x) << S_RESPONSE_QUEUE_ENABLE)
#घोषणा F_RESPONSE_QUEUE_ENABLE    V_RESPONSE_QUEUE_ENABLE(1U)

#घोषणा S_CMDQ_PRIORITY    6
#घोषणा M_CMDQ_PRIORITY    0x3
#घोषणा V_CMDQ_PRIORITY(x) ((x) << S_CMDQ_PRIORITY)
#घोषणा G_CMDQ_PRIORITY(x) (((x) >> S_CMDQ_PRIORITY) & M_CMDQ_PRIORITY)

#घोषणा S_DISABLE_CMDQ0_GTS    8
#घोषणा V_DISABLE_CMDQ0_GTS(x) ((x) << S_DISABLE_CMDQ0_GTS)
#घोषणा F_DISABLE_CMDQ0_GTS    V_DISABLE_CMDQ0_GTS(1U)

#घोषणा S_DISABLE_CMDQ1_GTS    9
#घोषणा V_DISABLE_CMDQ1_GTS(x) ((x) << S_DISABLE_CMDQ1_GTS)
#घोषणा F_DISABLE_CMDQ1_GTS    V_DISABLE_CMDQ1_GTS(1U)

#घोषणा S_DISABLE_FL0_GTS    10
#घोषणा V_DISABLE_FL0_GTS(x) ((x) << S_DISABLE_FL0_GTS)
#घोषणा F_DISABLE_FL0_GTS    V_DISABLE_FL0_GTS(1U)

#घोषणा S_DISABLE_FL1_GTS    11
#घोषणा V_DISABLE_FL1_GTS(x) ((x) << S_DISABLE_FL1_GTS)
#घोषणा F_DISABLE_FL1_GTS    V_DISABLE_FL1_GTS(1U)

#घोषणा S_ENABLE_BIG_ENDIAN    12
#घोषणा V_ENABLE_BIG_ENDIAN(x) ((x) << S_ENABLE_BIG_ENDIAN)
#घोषणा F_ENABLE_BIG_ENDIAN    V_ENABLE_BIG_ENDIAN(1U)

#घोषणा S_FL_SELECTION_CRITERIA    13
#घोषणा V_FL_SELECTION_CRITERIA(x) ((x) << S_FL_SELECTION_CRITERIA)
#घोषणा F_FL_SELECTION_CRITERIA    V_FL_SELECTION_CRITERIA(1U)

#घोषणा S_ISCSI_COALESCE    14
#घोषणा V_ISCSI_COALESCE(x) ((x) << S_ISCSI_COALESCE)
#घोषणा F_ISCSI_COALESCE    V_ISCSI_COALESCE(1U)

#घोषणा S_RX_PKT_OFFSET    15
#घोषणा M_RX_PKT_OFFSET    0x7
#घोषणा V_RX_PKT_OFFSET(x) ((x) << S_RX_PKT_OFFSET)
#घोषणा G_RX_PKT_OFFSET(x) (((x) >> S_RX_PKT_OFFSET) & M_RX_PKT_OFFSET)

#घोषणा S_VLAN_XTRACT    18
#घोषणा V_VLAN_XTRACT(x) ((x) << S_VLAN_XTRACT)
#घोषणा F_VLAN_XTRACT    V_VLAN_XTRACT(1U)

#घोषणा A_SG_DOORBELL 0x4
#घोषणा A_SG_CMD0BASELWR 0x8
#घोषणा A_SG_CMD0BASEUPR 0xc
#घोषणा A_SG_CMD1BASELWR 0x10
#घोषणा A_SG_CMD1BASEUPR 0x14
#घोषणा A_SG_FL0BASELWR 0x18
#घोषणा A_SG_FL0BASEUPR 0x1c
#घोषणा A_SG_FL1BASELWR 0x20
#घोषणा A_SG_FL1BASEUPR 0x24
#घोषणा A_SG_CMD0SIZE 0x28

#घोषणा S_CMDQ0_SIZE    0
#घोषणा M_CMDQ0_SIZE    0x1ffff
#घोषणा V_CMDQ0_SIZE(x) ((x) << S_CMDQ0_SIZE)
#घोषणा G_CMDQ0_SIZE(x) (((x) >> S_CMDQ0_SIZE) & M_CMDQ0_SIZE)

#घोषणा A_SG_FL0SIZE 0x2c

#घोषणा S_FL0_SIZE    0
#घोषणा M_FL0_SIZE    0x1ffff
#घोषणा V_FL0_SIZE(x) ((x) << S_FL0_SIZE)
#घोषणा G_FL0_SIZE(x) (((x) >> S_FL0_SIZE) & M_FL0_SIZE)

#घोषणा A_SG_RSPSIZE 0x30

#घोषणा S_RESPQ_SIZE    0
#घोषणा M_RESPQ_SIZE    0x1ffff
#घोषणा V_RESPQ_SIZE(x) ((x) << S_RESPQ_SIZE)
#घोषणा G_RESPQ_SIZE(x) (((x) >> S_RESPQ_SIZE) & M_RESPQ_SIZE)

#घोषणा A_SG_RSPBASELWR 0x34
#घोषणा A_SG_RSPBASEUPR 0x38
#घोषणा A_SG_FLTHRESHOLD 0x3c

#घोषणा S_FL_THRESHOLD    0
#घोषणा M_FL_THRESHOLD    0xffff
#घोषणा V_FL_THRESHOLD(x) ((x) << S_FL_THRESHOLD)
#घोषणा G_FL_THRESHOLD(x) (((x) >> S_FL_THRESHOLD) & M_FL_THRESHOLD)

#घोषणा A_SG_RSPQUEUECREDIT 0x40

#घोषणा S_RESPQ_CREDIT    0
#घोषणा M_RESPQ_CREDIT    0x1ffff
#घोषणा V_RESPQ_CREDIT(x) ((x) << S_RESPQ_CREDIT)
#घोषणा G_RESPQ_CREDIT(x) (((x) >> S_RESPQ_CREDIT) & M_RESPQ_CREDIT)

#घोषणा A_SG_SLEEPING 0x48

#घोषणा S_SLEEPING    0
#घोषणा M_SLEEPING    0xffff
#घोषणा V_SLEEPING(x) ((x) << S_SLEEPING)
#घोषणा G_SLEEPING(x) (((x) >> S_SLEEPING) & M_SLEEPING)

#घोषणा A_SG_INTRTIMER 0x4c

#घोषणा S_INTERRUPT_TIMER_COUNT    0
#घोषणा M_INTERRUPT_TIMER_COUNT    0xffffff
#घोषणा V_INTERRUPT_TIMER_COUNT(x) ((x) << S_INTERRUPT_TIMER_COUNT)
#घोषणा G_INTERRUPT_TIMER_COUNT(x) (((x) >> S_INTERRUPT_TIMER_COUNT) & M_INTERRUPT_TIMER_COUNT)

#घोषणा A_SG_CMD0PTR 0x50

#घोषणा S_CMDQ0_POINTER    0
#घोषणा M_CMDQ0_POINTER    0xffff
#घोषणा V_CMDQ0_POINTER(x) ((x) << S_CMDQ0_POINTER)
#घोषणा G_CMDQ0_POINTER(x) (((x) >> S_CMDQ0_POINTER) & M_CMDQ0_POINTER)

#घोषणा S_CURRENT_GENERATION_BIT    16
#घोषणा V_CURRENT_GENERATION_BIT(x) ((x) << S_CURRENT_GENERATION_BIT)
#घोषणा F_CURRENT_GENERATION_BIT    V_CURRENT_GENERATION_BIT(1U)

#घोषणा A_SG_CMD1PTR 0x54

#घोषणा S_CMDQ1_POINTER    0
#घोषणा M_CMDQ1_POINTER    0xffff
#घोषणा V_CMDQ1_POINTER(x) ((x) << S_CMDQ1_POINTER)
#घोषणा G_CMDQ1_POINTER(x) (((x) >> S_CMDQ1_POINTER) & M_CMDQ1_POINTER)

#घोषणा A_SG_FL0PTR 0x58

#घोषणा S_FL0_POINTER    0
#घोषणा M_FL0_POINTER    0xffff
#घोषणा V_FL0_POINTER(x) ((x) << S_FL0_POINTER)
#घोषणा G_FL0_POINTER(x) (((x) >> S_FL0_POINTER) & M_FL0_POINTER)

#घोषणा A_SG_FL1PTR 0x5c

#घोषणा S_FL1_POINTER    0
#घोषणा M_FL1_POINTER    0xffff
#घोषणा V_FL1_POINTER(x) ((x) << S_FL1_POINTER)
#घोषणा G_FL1_POINTER(x) (((x) >> S_FL1_POINTER) & M_FL1_POINTER)

#घोषणा A_SG_VERSION 0x6c

#घोषणा S_DAY    0
#घोषणा M_DAY    0x1f
#घोषणा V_DAY(x) ((x) << S_DAY)
#घोषणा G_DAY(x) (((x) >> S_DAY) & M_DAY)

#घोषणा S_MONTH    5
#घोषणा M_MONTH    0xf
#घोषणा V_MONTH(x) ((x) << S_MONTH)
#घोषणा G_MONTH(x) (((x) >> S_MONTH) & M_MONTH)

#घोषणा A_SG_CMD1SIZE 0xb0

#घोषणा S_CMDQ1_SIZE    0
#घोषणा M_CMDQ1_SIZE    0x1ffff
#घोषणा V_CMDQ1_SIZE(x) ((x) << S_CMDQ1_SIZE)
#घोषणा G_CMDQ1_SIZE(x) (((x) >> S_CMDQ1_SIZE) & M_CMDQ1_SIZE)

#घोषणा A_SG_FL1SIZE 0xb4

#घोषणा S_FL1_SIZE    0
#घोषणा M_FL1_SIZE    0x1ffff
#घोषणा V_FL1_SIZE(x) ((x) << S_FL1_SIZE)
#घोषणा G_FL1_SIZE(x) (((x) >> S_FL1_SIZE) & M_FL1_SIZE)

#घोषणा A_SG_INT_ENABLE 0xb8

#घोषणा S_RESPQ_EXHAUSTED    0
#घोषणा V_RESPQ_EXHAUSTED(x) ((x) << S_RESPQ_EXHAUSTED)
#घोषणा F_RESPQ_EXHAUSTED    V_RESPQ_EXHAUSTED(1U)

#घोषणा S_RESPQ_OVERFLOW    1
#घोषणा V_RESPQ_OVERFLOW(x) ((x) << S_RESPQ_OVERFLOW)
#घोषणा F_RESPQ_OVERFLOW    V_RESPQ_OVERFLOW(1U)

#घोषणा S_FL_EXHAUSTED    2
#घोषणा V_FL_EXHAUSTED(x) ((x) << S_FL_EXHAUSTED)
#घोषणा F_FL_EXHAUSTED    V_FL_EXHAUSTED(1U)

#घोषणा S_PACKET_TOO_BIG    3
#घोषणा V_PACKET_TOO_BIG(x) ((x) << S_PACKET_TOO_BIG)
#घोषणा F_PACKET_TOO_BIG    V_PACKET_TOO_BIG(1U)

#घोषणा S_PACKET_MISMATCH    4
#घोषणा V_PACKET_MISMATCH(x) ((x) << S_PACKET_MISMATCH)
#घोषणा F_PACKET_MISMATCH    V_PACKET_MISMATCH(1U)

#घोषणा A_SG_INT_CAUSE 0xbc
#घोषणा A_SG_RESPACCUTIMER 0xc0

/* MC3 रेजिस्टरs */
#घोषणा A_MC3_CFG 0x100

#घोषणा S_CLK_ENABLE    0
#घोषणा V_CLK_ENABLE(x) ((x) << S_CLK_ENABLE)
#घोषणा F_CLK_ENABLE    V_CLK_ENABLE(1U)

#घोषणा S_READY    1
#घोषणा V_READY(x) ((x) << S_READY)
#घोषणा F_READY    V_READY(1U)

#घोषणा S_READ_TO_WRITE_DELAY    2
#घोषणा M_READ_TO_WRITE_DELAY    0x7
#घोषणा V_READ_TO_WRITE_DELAY(x) ((x) << S_READ_TO_WRITE_DELAY)
#घोषणा G_READ_TO_WRITE_DELAY(x) (((x) >> S_READ_TO_WRITE_DELAY) & M_READ_TO_WRITE_DELAY)

#घोषणा S_WRITE_TO_READ_DELAY    5
#घोषणा M_WRITE_TO_READ_DELAY    0x7
#घोषणा V_WRITE_TO_READ_DELAY(x) ((x) << S_WRITE_TO_READ_DELAY)
#घोषणा G_WRITE_TO_READ_DELAY(x) (((x) >> S_WRITE_TO_READ_DELAY) & M_WRITE_TO_READ_DELAY)

#घोषणा S_MC3_BANK_CYCLE    8
#घोषणा M_MC3_BANK_CYCLE    0xf
#घोषणा V_MC3_BANK_CYCLE(x) ((x) << S_MC3_BANK_CYCLE)
#घोषणा G_MC3_BANK_CYCLE(x) (((x) >> S_MC3_BANK_CYCLE) & M_MC3_BANK_CYCLE)

#घोषणा S_REFRESH_CYCLE    12
#घोषणा M_REFRESH_CYCLE    0xf
#घोषणा V_REFRESH_CYCLE(x) ((x) << S_REFRESH_CYCLE)
#घोषणा G_REFRESH_CYCLE(x) (((x) >> S_REFRESH_CYCLE) & M_REFRESH_CYCLE)

#घोषणा S_PRECHARGE_CYCLE    16
#घोषणा M_PRECHARGE_CYCLE    0x3
#घोषणा V_PRECHARGE_CYCLE(x) ((x) << S_PRECHARGE_CYCLE)
#घोषणा G_PRECHARGE_CYCLE(x) (((x) >> S_PRECHARGE_CYCLE) & M_PRECHARGE_CYCLE)

#घोषणा S_ACTIVE_TO_READ_WRITE_DELAY    18
#घोषणा V_ACTIVE_TO_READ_WRITE_DELAY(x) ((x) << S_ACTIVE_TO_READ_WRITE_DELAY)
#घोषणा F_ACTIVE_TO_READ_WRITE_DELAY    V_ACTIVE_TO_READ_WRITE_DELAY(1U)

#घोषणा S_ACTIVE_TO_PRECHARGE_DELAY    19
#घोषणा M_ACTIVE_TO_PRECHARGE_DELAY    0x7
#घोषणा V_ACTIVE_TO_PRECHARGE_DELAY(x) ((x) << S_ACTIVE_TO_PRECHARGE_DELAY)
#घोषणा G_ACTIVE_TO_PRECHARGE_DELAY(x) (((x) >> S_ACTIVE_TO_PRECHARGE_DELAY) & M_ACTIVE_TO_PRECHARGE_DELAY)

#घोषणा S_WRITE_RECOVERY_DELAY    22
#घोषणा M_WRITE_RECOVERY_DELAY    0x3
#घोषणा V_WRITE_RECOVERY_DELAY(x) ((x) << S_WRITE_RECOVERY_DELAY)
#घोषणा G_WRITE_RECOVERY_DELAY(x) (((x) >> S_WRITE_RECOVERY_DELAY) & M_WRITE_RECOVERY_DELAY)

#घोषणा S_DENSITY    24
#घोषणा M_DENSITY    0x3
#घोषणा V_DENSITY(x) ((x) << S_DENSITY)
#घोषणा G_DENSITY(x) (((x) >> S_DENSITY) & M_DENSITY)

#घोषणा S_ORGANIZATION    26
#घोषणा V_ORGANIZATION(x) ((x) << S_ORGANIZATION)
#घोषणा F_ORGANIZATION    V_ORGANIZATION(1U)

#घोषणा S_BANKS    27
#घोषणा V_BANKS(x) ((x) << S_BANKS)
#घोषणा F_BANKS    V_BANKS(1U)

#घोषणा S_UNREGISTERED    28
#घोषणा V_UNREGISTERED(x) ((x) << S_UNREGISTERED)
#घोषणा F_UNREGISTERED    V_UNREGISTERED(1U)

#घोषणा S_MC3_WIDTH    29
#घोषणा M_MC3_WIDTH    0x3
#घोषणा V_MC3_WIDTH(x) ((x) << S_MC3_WIDTH)
#घोषणा G_MC3_WIDTH(x) (((x) >> S_MC3_WIDTH) & M_MC3_WIDTH)

#घोषणा S_MC3_SLOW    31
#घोषणा V_MC3_SLOW(x) ((x) << S_MC3_SLOW)
#घोषणा F_MC3_SLOW    V_MC3_SLOW(1U)

#घोषणा A_MC3_MODE 0x104

#घोषणा S_MC3_MODE    0
#घोषणा M_MC3_MODE    0x3fff
#घोषणा V_MC3_MODE(x) ((x) << S_MC3_MODE)
#घोषणा G_MC3_MODE(x) (((x) >> S_MC3_MODE) & M_MC3_MODE)

#घोषणा S_BUSY    31
#घोषणा V_BUSY(x) ((x) << S_BUSY)
#घोषणा F_BUSY    V_BUSY(1U)

#घोषणा A_MC3_EXT_MODE 0x108

#घोषणा S_MC3_EXTENDED_MODE    0
#घोषणा M_MC3_EXTENDED_MODE    0x3fff
#घोषणा V_MC3_EXTENDED_MODE(x) ((x) << S_MC3_EXTENDED_MODE)
#घोषणा G_MC3_EXTENDED_MODE(x) (((x) >> S_MC3_EXTENDED_MODE) & M_MC3_EXTENDED_MODE)

#घोषणा A_MC3_PRECHARG 0x10c
#घोषणा A_MC3_REFRESH 0x110

#घोषणा S_REFRESH_ENABLE    0
#घोषणा V_REFRESH_ENABLE(x) ((x) << S_REFRESH_ENABLE)
#घोषणा F_REFRESH_ENABLE    V_REFRESH_ENABLE(1U)

#घोषणा S_REFRESH_DIVISOR    1
#घोषणा M_REFRESH_DIVISOR    0x3fff
#घोषणा V_REFRESH_DIVISOR(x) ((x) << S_REFRESH_DIVISOR)
#घोषणा G_REFRESH_DIVISOR(x) (((x) >> S_REFRESH_DIVISOR) & M_REFRESH_DIVISOR)

#घोषणा A_MC3_STROBE 0x114

#घोषणा S_MASTER_DLL_RESET    0
#घोषणा V_MASTER_DLL_RESET(x) ((x) << S_MASTER_DLL_RESET)
#घोषणा F_MASTER_DLL_RESET    V_MASTER_DLL_RESET(1U)

#घोषणा S_MASTER_DLL_TAP_COUNT    1
#घोषणा M_MASTER_DLL_TAP_COUNT    0xff
#घोषणा V_MASTER_DLL_TAP_COUNT(x) ((x) << S_MASTER_DLL_TAP_COUNT)
#घोषणा G_MASTER_DLL_TAP_COUNT(x) (((x) >> S_MASTER_DLL_TAP_COUNT) & M_MASTER_DLL_TAP_COUNT)

#घोषणा S_MASTER_DLL_LOCKED    9
#घोषणा V_MASTER_DLL_LOCKED(x) ((x) << S_MASTER_DLL_LOCKED)
#घोषणा F_MASTER_DLL_LOCKED    V_MASTER_DLL_LOCKED(1U)

#घोषणा S_MASTER_DLL_MAX_TAP_COUNT    10
#घोषणा V_MASTER_DLL_MAX_TAP_COUNT(x) ((x) << S_MASTER_DLL_MAX_TAP_COUNT)
#घोषणा F_MASTER_DLL_MAX_TAP_COUNT    V_MASTER_DLL_MAX_TAP_COUNT(1U)

#घोषणा S_MASTER_DLL_TAP_COUNT_OFFSET    11
#घोषणा M_MASTER_DLL_TAP_COUNT_OFFSET    0x3f
#घोषणा V_MASTER_DLL_TAP_COUNT_OFFSET(x) ((x) << S_MASTER_DLL_TAP_COUNT_OFFSET)
#घोषणा G_MASTER_DLL_TAP_COUNT_OFFSET(x) (((x) >> S_MASTER_DLL_TAP_COUNT_OFFSET) & M_MASTER_DLL_TAP_COUNT_OFFSET)

#घोषणा S_SLAVE_DLL_RESET    11
#घोषणा V_SLAVE_DLL_RESET(x) ((x) << S_SLAVE_DLL_RESET)
#घोषणा F_SLAVE_DLL_RESET    V_SLAVE_DLL_RESET(1U)

#घोषणा S_SLAVE_DLL_DELTA    12
#घोषणा M_SLAVE_DLL_DELTA    0xf
#घोषणा V_SLAVE_DLL_DELTA(x) ((x) << S_SLAVE_DLL_DELTA)
#घोषणा G_SLAVE_DLL_DELTA(x) (((x) >> S_SLAVE_DLL_DELTA) & M_SLAVE_DLL_DELTA)

#घोषणा S_SLAVE_DELAY_LINE_MANUAL_TAP_COUNT    17
#घोषणा M_SLAVE_DELAY_LINE_MANUAL_TAP_COUNT    0x3f
#घोषणा V_SLAVE_DELAY_LINE_MANUAL_TAP_COUNT(x) ((x) << S_SLAVE_DELAY_LINE_MANUAL_TAP_COUNT)
#घोषणा G_SLAVE_DELAY_LINE_MANUAL_TAP_COUNT(x) (((x) >> S_SLAVE_DELAY_LINE_MANUAL_TAP_COUNT) & M_SLAVE_DELAY_LINE_MANUAL_TAP_COUNT)

#घोषणा S_SLAVE_DELAY_LINE_MANUAL_TAP_COUNT_ENABLE    23
#घोषणा V_SLAVE_DELAY_LINE_MANUAL_TAP_COUNT_ENABLE(x) ((x) << S_SLAVE_DELAY_LINE_MANUAL_TAP_COUNT_ENABLE)
#घोषणा F_SLAVE_DELAY_LINE_MANUAL_TAP_COUNT_ENABLE    V_SLAVE_DELAY_LINE_MANUAL_TAP_COUNT_ENABLE(1U)

#घोषणा S_SLAVE_DELAY_LINE_TAP_COUNT    24
#घोषणा M_SLAVE_DELAY_LINE_TAP_COUNT    0x3f
#घोषणा V_SLAVE_DELAY_LINE_TAP_COUNT(x) ((x) << S_SLAVE_DELAY_LINE_TAP_COUNT)
#घोषणा G_SLAVE_DELAY_LINE_TAP_COUNT(x) (((x) >> S_SLAVE_DELAY_LINE_TAP_COUNT) & M_SLAVE_DELAY_LINE_TAP_COUNT)

#घोषणा A_MC3_ECC_CNTL 0x118

#घोषणा S_ECC_GENERATION_ENABLE    0
#घोषणा V_ECC_GENERATION_ENABLE(x) ((x) << S_ECC_GENERATION_ENABLE)
#घोषणा F_ECC_GENERATION_ENABLE    V_ECC_GENERATION_ENABLE(1U)

#घोषणा S_ECC_CHECK_ENABLE    1
#घोषणा V_ECC_CHECK_ENABLE(x) ((x) << S_ECC_CHECK_ENABLE)
#घोषणा F_ECC_CHECK_ENABLE    V_ECC_CHECK_ENABLE(1U)

#घोषणा S_CORRECTABLE_ERROR_COUNT    2
#घोषणा M_CORRECTABLE_ERROR_COUNT    0xff
#घोषणा V_CORRECTABLE_ERROR_COUNT(x) ((x) << S_CORRECTABLE_ERROR_COUNT)
#घोषणा G_CORRECTABLE_ERROR_COUNT(x) (((x) >> S_CORRECTABLE_ERROR_COUNT) & M_CORRECTABLE_ERROR_COUNT)

#घोषणा S_UNCORRECTABLE_ERROR_COUNT    10
#घोषणा M_UNCORRECTABLE_ERROR_COUNT    0xff
#घोषणा V_UNCORRECTABLE_ERROR_COUNT(x) ((x) << S_UNCORRECTABLE_ERROR_COUNT)
#घोषणा G_UNCORRECTABLE_ERROR_COUNT(x) (((x) >> S_UNCORRECTABLE_ERROR_COUNT) & M_UNCORRECTABLE_ERROR_COUNT)

#घोषणा A_MC3_CE_ADDR 0x11c

#घोषणा S_MC3_CE_ADDR    4
#घोषणा M_MC3_CE_ADDR    0xfffffff
#घोषणा V_MC3_CE_ADDR(x) ((x) << S_MC3_CE_ADDR)
#घोषणा G_MC3_CE_ADDR(x) (((x) >> S_MC3_CE_ADDR) & M_MC3_CE_ADDR)

#घोषणा A_MC3_CE_DATA0 0x120
#घोषणा A_MC3_CE_DATA1 0x124
#घोषणा A_MC3_CE_DATA2 0x128
#घोषणा A_MC3_CE_DATA3 0x12c
#घोषणा A_MC3_CE_DATA4 0x130
#घोषणा A_MC3_UE_ADDR 0x134

#घोषणा S_MC3_UE_ADDR    4
#घोषणा M_MC3_UE_ADDR    0xfffffff
#घोषणा V_MC3_UE_ADDR(x) ((x) << S_MC3_UE_ADDR)
#घोषणा G_MC3_UE_ADDR(x) (((x) >> S_MC3_UE_ADDR) & M_MC3_UE_ADDR)

#घोषणा A_MC3_UE_DATA0 0x138
#घोषणा A_MC3_UE_DATA1 0x13c
#घोषणा A_MC3_UE_DATA2 0x140
#घोषणा A_MC3_UE_DATA3 0x144
#घोषणा A_MC3_UE_DATA4 0x148
#घोषणा A_MC3_BD_ADDR 0x14c
#घोषणा A_MC3_BD_DATA0 0x150
#घोषणा A_MC3_BD_DATA1 0x154
#घोषणा A_MC3_BD_DATA2 0x158
#घोषणा A_MC3_BD_DATA3 0x15c
#घोषणा A_MC3_BD_DATA4 0x160
#घोषणा A_MC3_BD_OP 0x164

#घोषणा S_BACK_DOOR_OPERATION    0
#घोषणा V_BACK_DOOR_OPERATION(x) ((x) << S_BACK_DOOR_OPERATION)
#घोषणा F_BACK_DOOR_OPERATION    V_BACK_DOOR_OPERATION(1U)

#घोषणा A_MC3_BIST_ADDR_BEG 0x168
#घोषणा A_MC3_BIST_ADDR_END 0x16c
#घोषणा A_MC3_BIST_DATA 0x170
#घोषणा A_MC3_BIST_OP 0x174

#घोषणा S_OP    0
#घोषणा V_OP(x) ((x) << S_OP)
#घोषणा F_OP    V_OP(1U)

#घोषणा S_DATA_PATTERN    1
#घोषणा M_DATA_PATTERN    0x3
#घोषणा V_DATA_PATTERN(x) ((x) << S_DATA_PATTERN)
#घोषणा G_DATA_PATTERN(x) (((x) >> S_DATA_PATTERN) & M_DATA_PATTERN)

#घोषणा S_CONTINUOUS    3
#घोषणा V_CONTINUOUS(x) ((x) << S_CONTINUOUS)
#घोषणा F_CONTINUOUS    V_CONTINUOUS(1U)

#घोषणा A_MC3_INT_ENABLE 0x178

#घोषणा S_MC3_CORR_ERR    0
#घोषणा V_MC3_CORR_ERR(x) ((x) << S_MC3_CORR_ERR)
#घोषणा F_MC3_CORR_ERR    V_MC3_CORR_ERR(1U)

#घोषणा S_MC3_UNCORR_ERR    1
#घोषणा V_MC3_UNCORR_ERR(x) ((x) << S_MC3_UNCORR_ERR)
#घोषणा F_MC3_UNCORR_ERR    V_MC3_UNCORR_ERR(1U)

#घोषणा S_MC3_PARITY_ERR    2
#घोषणा M_MC3_PARITY_ERR    0xff
#घोषणा V_MC3_PARITY_ERR(x) ((x) << S_MC3_PARITY_ERR)
#घोषणा G_MC3_PARITY_ERR(x) (((x) >> S_MC3_PARITY_ERR) & M_MC3_PARITY_ERR)

#घोषणा S_MC3_ADDR_ERR    10
#घोषणा V_MC3_ADDR_ERR(x) ((x) << S_MC3_ADDR_ERR)
#घोषणा F_MC3_ADDR_ERR    V_MC3_ADDR_ERR(1U)

#घोषणा A_MC3_INT_CAUSE 0x17c

/* MC4 रेजिस्टरs */
#घोषणा A_MC4_CFG 0x180

#घोषणा S_POWER_UP    0
#घोषणा V_POWER_UP(x) ((x) << S_POWER_UP)
#घोषणा F_POWER_UP    V_POWER_UP(1U)

#घोषणा S_MC4_BANK_CYCLE    8
#घोषणा M_MC4_BANK_CYCLE    0x7
#घोषणा V_MC4_BANK_CYCLE(x) ((x) << S_MC4_BANK_CYCLE)
#घोषणा G_MC4_BANK_CYCLE(x) (((x) >> S_MC4_BANK_CYCLE) & M_MC4_BANK_CYCLE)

#घोषणा S_MC4_NARROW    24
#घोषणा V_MC4_NARROW(x) ((x) << S_MC4_NARROW)
#घोषणा F_MC4_NARROW    V_MC4_NARROW(1U)

#घोषणा S_MC4_SLOW    25
#घोषणा V_MC4_SLOW(x) ((x) << S_MC4_SLOW)
#घोषणा F_MC4_SLOW    V_MC4_SLOW(1U)

#घोषणा S_MC4A_WIDTH    24
#घोषणा M_MC4A_WIDTH    0x3
#घोषणा V_MC4A_WIDTH(x) ((x) << S_MC4A_WIDTH)
#घोषणा G_MC4A_WIDTH(x) (((x) >> S_MC4A_WIDTH) & M_MC4A_WIDTH)

#घोषणा S_MC4A_SLOW    26
#घोषणा V_MC4A_SLOW(x) ((x) << S_MC4A_SLOW)
#घोषणा F_MC4A_SLOW    V_MC4A_SLOW(1U)

#घोषणा A_MC4_MODE 0x184

#घोषणा S_MC4_MODE    0
#घोषणा M_MC4_MODE    0x7fff
#घोषणा V_MC4_MODE(x) ((x) << S_MC4_MODE)
#घोषणा G_MC4_MODE(x) (((x) >> S_MC4_MODE) & M_MC4_MODE)

#घोषणा A_MC4_EXT_MODE 0x188

#घोषणा S_MC4_EXTENDED_MODE    0
#घोषणा M_MC4_EXTENDED_MODE    0x7fff
#घोषणा V_MC4_EXTENDED_MODE(x) ((x) << S_MC4_EXTENDED_MODE)
#घोषणा G_MC4_EXTENDED_MODE(x) (((x) >> S_MC4_EXTENDED_MODE) & M_MC4_EXTENDED_MODE)

#घोषणा A_MC4_REFRESH 0x190
#घोषणा A_MC4_STROBE 0x194
#घोषणा A_MC4_ECC_CNTL 0x198
#घोषणा A_MC4_CE_ADDR 0x19c

#घोषणा S_MC4_CE_ADDR    4
#घोषणा M_MC4_CE_ADDR    0xffffff
#घोषणा V_MC4_CE_ADDR(x) ((x) << S_MC4_CE_ADDR)
#घोषणा G_MC4_CE_ADDR(x) (((x) >> S_MC4_CE_ADDR) & M_MC4_CE_ADDR)

#घोषणा A_MC4_CE_DATA0 0x1a0
#घोषणा A_MC4_CE_DATA1 0x1a4
#घोषणा A_MC4_CE_DATA2 0x1a8
#घोषणा A_MC4_CE_DATA3 0x1ac
#घोषणा A_MC4_CE_DATA4 0x1b0
#घोषणा A_MC4_UE_ADDR 0x1b4

#घोषणा S_MC4_UE_ADDR    4
#घोषणा M_MC4_UE_ADDR    0xffffff
#घोषणा V_MC4_UE_ADDR(x) ((x) << S_MC4_UE_ADDR)
#घोषणा G_MC4_UE_ADDR(x) (((x) >> S_MC4_UE_ADDR) & M_MC4_UE_ADDR)

#घोषणा A_MC4_UE_DATA0 0x1b8
#घोषणा A_MC4_UE_DATA1 0x1bc
#घोषणा A_MC4_UE_DATA2 0x1c0
#घोषणा A_MC4_UE_DATA3 0x1c4
#घोषणा A_MC4_UE_DATA4 0x1c8
#घोषणा A_MC4_BD_ADDR 0x1cc

#घोषणा S_MC4_BACK_DOOR_ADDR    0
#घोषणा M_MC4_BACK_DOOR_ADDR    0xfffffff
#घोषणा V_MC4_BACK_DOOR_ADDR(x) ((x) << S_MC4_BACK_DOOR_ADDR)
#घोषणा G_MC4_BACK_DOOR_ADDR(x) (((x) >> S_MC4_BACK_DOOR_ADDR) & M_MC4_BACK_DOOR_ADDR)

#घोषणा A_MC4_BD_DATA0 0x1d0
#घोषणा A_MC4_BD_DATA1 0x1d4
#घोषणा A_MC4_BD_DATA2 0x1d8
#घोषणा A_MC4_BD_DATA3 0x1dc
#घोषणा A_MC4_BD_DATA4 0x1e0
#घोषणा A_MC4_BD_OP 0x1e4

#घोषणा S_OPERATION    0
#घोषणा V_OPERATION(x) ((x) << S_OPERATION)
#घोषणा F_OPERATION    V_OPERATION(1U)

#घोषणा A_MC4_BIST_ADDR_BEG 0x1e8
#घोषणा A_MC4_BIST_ADDR_END 0x1ec
#घोषणा A_MC4_BIST_DATA 0x1f0
#घोषणा A_MC4_BIST_OP 0x1f4
#घोषणा A_MC4_INT_ENABLE 0x1f8

#घोषणा S_MC4_CORR_ERR    0
#घोषणा V_MC4_CORR_ERR(x) ((x) << S_MC4_CORR_ERR)
#घोषणा F_MC4_CORR_ERR    V_MC4_CORR_ERR(1U)

#घोषणा S_MC4_UNCORR_ERR    1
#घोषणा V_MC4_UNCORR_ERR(x) ((x) << S_MC4_UNCORR_ERR)
#घोषणा F_MC4_UNCORR_ERR    V_MC4_UNCORR_ERR(1U)

#घोषणा S_MC4_ADDR_ERR    2
#घोषणा V_MC4_ADDR_ERR(x) ((x) << S_MC4_ADDR_ERR)
#घोषणा F_MC4_ADDR_ERR    V_MC4_ADDR_ERR(1U)

#घोषणा A_MC4_INT_CAUSE 0x1fc

/* TPI रेजिस्टरs */
#घोषणा A_TPI_ADDR 0x280

#घोषणा S_TPI_ADDRESS    0
#घोषणा M_TPI_ADDRESS    0xffffff
#घोषणा V_TPI_ADDRESS(x) ((x) << S_TPI_ADDRESS)
#घोषणा G_TPI_ADDRESS(x) (((x) >> S_TPI_ADDRESS) & M_TPI_ADDRESS)

#घोषणा A_TPI_WR_DATA 0x284
#घोषणा A_TPI_RD_DATA 0x288
#घोषणा A_TPI_CSR 0x28c

#घोषणा S_TPIWR    0
#घोषणा V_TPIWR(x) ((x) << S_TPIWR)
#घोषणा F_TPIWR    V_TPIWR(1U)

#घोषणा S_TPIRDY    1
#घोषणा V_TPIRDY(x) ((x) << S_TPIRDY)
#घोषणा F_TPIRDY    V_TPIRDY(1U)

#घोषणा S_INT_सूची    31
#घोषणा V_INT_सूची(x) ((x) << S_INT_सूची)
#घोषणा F_INT_सूची    V_INT_सूची(1U)

#घोषणा A_TPI_PAR 0x29c

#घोषणा S_TPIPAR    0
#घोषणा M_TPIPAR    0x7f
#घोषणा V_TPIPAR(x) ((x) << S_TPIPAR)
#घोषणा G_TPIPAR(x) (((x) >> S_TPIPAR) & M_TPIPAR)


/* TP रेजिस्टरs */
#घोषणा A_TP_IN_CONFIG 0x300

#घोषणा S_TP_IN_CSPI_TUNNEL    0
#घोषणा V_TP_IN_CSPI_TUNNEL(x) ((x) << S_TP_IN_CSPI_TUNNEL)
#घोषणा F_TP_IN_CSPI_TUNNEL    V_TP_IN_CSPI_TUNNEL(1U)

#घोषणा S_TP_IN_CSPI_ETHERNET    1
#घोषणा V_TP_IN_CSPI_ETHERNET(x) ((x) << S_TP_IN_CSPI_ETHERNET)
#घोषणा F_TP_IN_CSPI_ETHERNET    V_TP_IN_CSPI_ETHERNET(1U)

#घोषणा S_TP_IN_CSPI_CPL    3
#घोषणा V_TP_IN_CSPI_CPL(x) ((x) << S_TP_IN_CSPI_CPL)
#घोषणा F_TP_IN_CSPI_CPL    V_TP_IN_CSPI_CPL(1U)

#घोषणा S_TP_IN_CSPI_POS    4
#घोषणा V_TP_IN_CSPI_POS(x) ((x) << S_TP_IN_CSPI_POS)
#घोषणा F_TP_IN_CSPI_POS    V_TP_IN_CSPI_POS(1U)

#घोषणा S_TP_IN_CSPI_CHECK_IP_CSUM    5
#घोषणा V_TP_IN_CSPI_CHECK_IP_CSUM(x) ((x) << S_TP_IN_CSPI_CHECK_IP_CSUM)
#घोषणा F_TP_IN_CSPI_CHECK_IP_CSUM    V_TP_IN_CSPI_CHECK_IP_CSUM(1U)

#घोषणा S_TP_IN_CSPI_CHECK_TCP_CSUM    6
#घोषणा V_TP_IN_CSPI_CHECK_TCP_CSUM(x) ((x) << S_TP_IN_CSPI_CHECK_TCP_CSUM)
#घोषणा F_TP_IN_CSPI_CHECK_TCP_CSUM    V_TP_IN_CSPI_CHECK_TCP_CSUM(1U)

#घोषणा S_TP_IN_ESPI_TUNNEL    7
#घोषणा V_TP_IN_ESPI_TUNNEL(x) ((x) << S_TP_IN_ESPI_TUNNEL)
#घोषणा F_TP_IN_ESPI_TUNNEL    V_TP_IN_ESPI_TUNNEL(1U)

#घोषणा S_TP_IN_ESPI_ETHERNET    8
#घोषणा V_TP_IN_ESPI_ETHERNET(x) ((x) << S_TP_IN_ESPI_ETHERNET)
#घोषणा F_TP_IN_ESPI_ETHERNET    V_TP_IN_ESPI_ETHERNET(1U)

#घोषणा S_TP_IN_ESPI_CPL    10
#घोषणा V_TP_IN_ESPI_CPL(x) ((x) << S_TP_IN_ESPI_CPL)
#घोषणा F_TP_IN_ESPI_CPL    V_TP_IN_ESPI_CPL(1U)

#घोषणा S_TP_IN_ESPI_POS    11
#घोषणा V_TP_IN_ESPI_POS(x) ((x) << S_TP_IN_ESPI_POS)
#घोषणा F_TP_IN_ESPI_POS    V_TP_IN_ESPI_POS(1U)

#घोषणा S_TP_IN_ESPI_CHECK_IP_CSUM    12
#घोषणा V_TP_IN_ESPI_CHECK_IP_CSUM(x) ((x) << S_TP_IN_ESPI_CHECK_IP_CSUM)
#घोषणा F_TP_IN_ESPI_CHECK_IP_CSUM    V_TP_IN_ESPI_CHECK_IP_CSUM(1U)

#घोषणा S_TP_IN_ESPI_CHECK_TCP_CSUM    13
#घोषणा V_TP_IN_ESPI_CHECK_TCP_CSUM(x) ((x) << S_TP_IN_ESPI_CHECK_TCP_CSUM)
#घोषणा F_TP_IN_ESPI_CHECK_TCP_CSUM    V_TP_IN_ESPI_CHECK_TCP_CSUM(1U)

#घोषणा S_OFFLOAD_DISABLE    14
#घोषणा V_OFFLOAD_DISABLE(x) ((x) << S_OFFLOAD_DISABLE)
#घोषणा F_OFFLOAD_DISABLE    V_OFFLOAD_DISABLE(1U)

#घोषणा A_TP_OUT_CONFIG 0x304

#घोषणा S_TP_OUT_C_ETH    0
#घोषणा V_TP_OUT_C_ETH(x) ((x) << S_TP_OUT_C_ETH)
#घोषणा F_TP_OUT_C_ETH    V_TP_OUT_C_ETH(1U)

#घोषणा S_TP_OUT_CSPI_CPL    2
#घोषणा V_TP_OUT_CSPI_CPL(x) ((x) << S_TP_OUT_CSPI_CPL)
#घोषणा F_TP_OUT_CSPI_CPL    V_TP_OUT_CSPI_CPL(1U)

#घोषणा S_TP_OUT_CSPI_POS    3
#घोषणा V_TP_OUT_CSPI_POS(x) ((x) << S_TP_OUT_CSPI_POS)
#घोषणा F_TP_OUT_CSPI_POS    V_TP_OUT_CSPI_POS(1U)

#घोषणा S_TP_OUT_CSPI_GENERATE_IP_CSUM    4
#घोषणा V_TP_OUT_CSPI_GENERATE_IP_CSUM(x) ((x) << S_TP_OUT_CSPI_GENERATE_IP_CSUM)
#घोषणा F_TP_OUT_CSPI_GENERATE_IP_CSUM    V_TP_OUT_CSPI_GENERATE_IP_CSUM(1U)

#घोषणा S_TP_OUT_CSPI_GENERATE_TCP_CSUM    5
#घोषणा V_TP_OUT_CSPI_GENERATE_TCP_CSUM(x) ((x) << S_TP_OUT_CSPI_GENERATE_TCP_CSUM)
#घोषणा F_TP_OUT_CSPI_GENERATE_TCP_CSUM    V_TP_OUT_CSPI_GENERATE_TCP_CSUM(1U)

#घोषणा S_TP_OUT_ESPI_ETHERNET    6
#घोषणा V_TP_OUT_ESPI_ETHERNET(x) ((x) << S_TP_OUT_ESPI_ETHERNET)
#घोषणा F_TP_OUT_ESPI_ETHERNET    V_TP_OUT_ESPI_ETHERNET(1U)

#घोषणा S_TP_OUT_ESPI_TAG_ETHERNET    7
#घोषणा V_TP_OUT_ESPI_TAG_ETHERNET(x) ((x) << S_TP_OUT_ESPI_TAG_ETHERNET)
#घोषणा F_TP_OUT_ESPI_TAG_ETHERNET    V_TP_OUT_ESPI_TAG_ETHERNET(1U)

#घोषणा S_TP_OUT_ESPI_CPL    8
#घोषणा V_TP_OUT_ESPI_CPL(x) ((x) << S_TP_OUT_ESPI_CPL)
#घोषणा F_TP_OUT_ESPI_CPL    V_TP_OUT_ESPI_CPL(1U)

#घोषणा S_TP_OUT_ESPI_POS    9
#घोषणा V_TP_OUT_ESPI_POS(x) ((x) << S_TP_OUT_ESPI_POS)
#घोषणा F_TP_OUT_ESPI_POS    V_TP_OUT_ESPI_POS(1U)

#घोषणा S_TP_OUT_ESPI_GENERATE_IP_CSUM    10
#घोषणा V_TP_OUT_ESPI_GENERATE_IP_CSUM(x) ((x) << S_TP_OUT_ESPI_GENERATE_IP_CSUM)
#घोषणा F_TP_OUT_ESPI_GENERATE_IP_CSUM    V_TP_OUT_ESPI_GENERATE_IP_CSUM(1U)

#घोषणा S_TP_OUT_ESPI_GENERATE_TCP_CSUM    11
#घोषणा V_TP_OUT_ESPI_GENERATE_TCP_CSUM(x) ((x) << S_TP_OUT_ESPI_GENERATE_TCP_CSUM)
#घोषणा F_TP_OUT_ESPI_GENERATE_TCP_CSUM    V_TP_OUT_ESPI_GENERATE_TCP_CSUM(1U)

#घोषणा A_TP_GLOBAL_CONFIG 0x308

#घोषणा S_IP_TTL    0
#घोषणा M_IP_TTL    0xff
#घोषणा V_IP_TTL(x) ((x) << S_IP_TTL)
#घोषणा G_IP_TTL(x) (((x) >> S_IP_TTL) & M_IP_TTL)

#घोषणा S_TCAM_SERVER_REGION_USAGE    8
#घोषणा M_TCAM_SERVER_REGION_USAGE    0x3
#घोषणा V_TCAM_SERVER_REGION_USAGE(x) ((x) << S_TCAM_SERVER_REGION_USAGE)
#घोषणा G_TCAM_SERVER_REGION_USAGE(x) (((x) >> S_TCAM_SERVER_REGION_USAGE) & M_TCAM_SERVER_REGION_USAGE)

#घोषणा S_QOS_MAPPING    10
#घोषणा V_QOS_MAPPING(x) ((x) << S_QOS_MAPPING)
#घोषणा F_QOS_MAPPING    V_QOS_MAPPING(1U)

#घोषणा S_TCP_CSUM    11
#घोषणा V_TCP_CSUM(x) ((x) << S_TCP_CSUM)
#घोषणा F_TCP_CSUM    V_TCP_CSUM(1U)

#घोषणा S_UDP_CSUM    12
#घोषणा V_UDP_CSUM(x) ((x) << S_UDP_CSUM)
#घोषणा F_UDP_CSUM    V_UDP_CSUM(1U)

#घोषणा S_IP_CSUM    13
#घोषणा V_IP_CSUM(x) ((x) << S_IP_CSUM)
#घोषणा F_IP_CSUM    V_IP_CSUM(1U)

#घोषणा S_IP_ID_SPLIT    14
#घोषणा V_IP_ID_SPLIT(x) ((x) << S_IP_ID_SPLIT)
#घोषणा F_IP_ID_SPLIT    V_IP_ID_SPLIT(1U)

#घोषणा S_PATH_MTU    15
#घोषणा V_PATH_MTU(x) ((x) << S_PATH_MTU)
#घोषणा F_PATH_MTU    V_PATH_MTU(1U)

#घोषणा S_5TUPLE_LOOKUP    17
#घोषणा M_5TUPLE_LOOKUP    0x3
#घोषणा V_5TUPLE_LOOKUP(x) ((x) << S_5TUPLE_LOOKUP)
#घोषणा G_5TUPLE_LOOKUP(x) (((x) >> S_5TUPLE_LOOKUP) & M_5TUPLE_LOOKUP)

#घोषणा S_IP_FRAGMENT_DROP    19
#घोषणा V_IP_FRAGMENT_DROP(x) ((x) << S_IP_FRAGMENT_DROP)
#घोषणा F_IP_FRAGMENT_DROP    V_IP_FRAGMENT_DROP(1U)

#घोषणा S_PING_DROP    20
#घोषणा V_PING_DROP(x) ((x) << S_PING_DROP)
#घोषणा F_PING_DROP    V_PING_DROP(1U)

#घोषणा S_PROTECT_MODE    21
#घोषणा V_PROTECT_MODE(x) ((x) << S_PROTECT_MODE)
#घोषणा F_PROTECT_MODE    V_PROTECT_MODE(1U)

#घोषणा S_SYN_COOKIE_ALGORITHM    22
#घोषणा V_SYN_COOKIE_ALGORITHM(x) ((x) << S_SYN_COOKIE_ALGORITHM)
#घोषणा F_SYN_COOKIE_ALGORITHM    V_SYN_COOKIE_ALGORITHM(1U)

#घोषणा S_ATTACK_FILTER    23
#घोषणा V_ATTACK_FILTER(x) ((x) << S_ATTACK_FILTER)
#घोषणा F_ATTACK_FILTER    V_ATTACK_FILTER(1U)

#घोषणा S_INTERFACE_TYPE    24
#घोषणा V_INTERFACE_TYPE(x) ((x) << S_INTERFACE_TYPE)
#घोषणा F_INTERFACE_TYPE    V_INTERFACE_TYPE(1U)

#घोषणा S_DISABLE_RX_FLOW_CONTROL    25
#घोषणा V_DISABLE_RX_FLOW_CONTROL(x) ((x) << S_DISABLE_RX_FLOW_CONTROL)
#घोषणा F_DISABLE_RX_FLOW_CONTROL    V_DISABLE_RX_FLOW_CONTROL(1U)

#घोषणा S_SYN_COOKIE_PARAMETER    26
#घोषणा M_SYN_COOKIE_PARAMETER    0x3f
#घोषणा V_SYN_COOKIE_PARAMETER(x) ((x) << S_SYN_COOKIE_PARAMETER)
#घोषणा G_SYN_COOKIE_PARAMETER(x) (((x) >> S_SYN_COOKIE_PARAMETER) & M_SYN_COOKIE_PARAMETER)

#घोषणा A_TP_GLOBAL_RX_CREDITS 0x30c
#घोषणा A_TP_CM_SIZE 0x310
#घोषणा A_TP_CM_MM_BASE 0x314

#घोषणा S_CM_MEMMGR_BASE    0
#घोषणा M_CM_MEMMGR_BASE    0xfffffff
#घोषणा V_CM_MEMMGR_BASE(x) ((x) << S_CM_MEMMGR_BASE)
#घोषणा G_CM_MEMMGR_BASE(x) (((x) >> S_CM_MEMMGR_BASE) & M_CM_MEMMGR_BASE)

#घोषणा A_TP_CM_TIMER_BASE 0x318

#घोषणा S_CM_TIMER_BASE    0
#घोषणा M_CM_TIMER_BASE    0xfffffff
#घोषणा V_CM_TIMER_BASE(x) ((x) << S_CM_TIMER_BASE)
#घोषणा G_CM_TIMER_BASE(x) (((x) >> S_CM_TIMER_BASE) & M_CM_TIMER_BASE)

#घोषणा A_TP_PM_SIZE 0x31c
#घोषणा A_TP_PM_TX_BASE 0x320
#घोषणा A_TP_PM_DEFRAG_BASE 0x324
#घोषणा A_TP_PM_RX_BASE 0x328
#घोषणा A_TP_PM_RX_PG_SIZE 0x32c
#घोषणा A_TP_PM_RX_MAX_PGS 0x330
#घोषणा A_TP_PM_TX_PG_SIZE 0x334
#घोषणा A_TP_PM_TX_MAX_PGS 0x338
#घोषणा A_TP_TCP_OPTIONS 0x340

#घोषणा S_TIMESTAMP    0
#घोषणा M_TIMESTAMP    0x3
#घोषणा V_TIMESTAMP(x) ((x) << S_TIMESTAMP)
#घोषणा G_TIMESTAMP(x) (((x) >> S_TIMESTAMP) & M_TIMESTAMP)

#घोषणा S_WINDOW_SCALE    2
#घोषणा M_WINDOW_SCALE    0x3
#घोषणा V_WINDOW_SCALE(x) ((x) << S_WINDOW_SCALE)
#घोषणा G_WINDOW_SCALE(x) (((x) >> S_WINDOW_SCALE) & M_WINDOW_SCALE)

#घोषणा S_SACK    4
#घोषणा M_SACK    0x3
#घोषणा V_SACK(x) ((x) << S_SACK)
#घोषणा G_SACK(x) (((x) >> S_SACK) & M_SACK)

#घोषणा S_ECN    6
#घोषणा M_ECN    0x3
#घोषणा V_ECN(x) ((x) << S_ECN)
#घोषणा G_ECN(x) (((x) >> S_ECN) & M_ECN)

#घोषणा S_SACK_ALGORITHM    8
#घोषणा M_SACK_ALGORITHM    0x3
#घोषणा V_SACK_ALGORITHM(x) ((x) << S_SACK_ALGORITHM)
#घोषणा G_SACK_ALGORITHM(x) (((x) >> S_SACK_ALGORITHM) & M_SACK_ALGORITHM)

#घोषणा S_MSS    10
#घोषणा V_MSS(x) ((x) << S_MSS)
#घोषणा F_MSS    V_MSS(1U)

#घोषणा S_DEFAULT_PEER_MSS    16
#घोषणा M_DEFAULT_PEER_MSS    0xffff
#घोषणा V_DEFAULT_PEER_MSS(x) ((x) << S_DEFAULT_PEER_MSS)
#घोषणा G_DEFAULT_PEER_MSS(x) (((x) >> S_DEFAULT_PEER_MSS) & M_DEFAULT_PEER_MSS)

#घोषणा A_TP_DACK_CONFIG 0x344

#घोषणा S_DACK_MODE    0
#घोषणा V_DACK_MODE(x) ((x) << S_DACK_MODE)
#घोषणा F_DACK_MODE    V_DACK_MODE(1U)

#घोषणा S_DACK_AUTO_MGMT    1
#घोषणा V_DACK_AUTO_MGMT(x) ((x) << S_DACK_AUTO_MGMT)
#घोषणा F_DACK_AUTO_MGMT    V_DACK_AUTO_MGMT(1U)

#घोषणा S_DACK_AUTO_CAREFUL    2
#घोषणा V_DACK_AUTO_CAREFUL(x) ((x) << S_DACK_AUTO_CAREFUL)
#घोषणा F_DACK_AUTO_CAREFUL    V_DACK_AUTO_CAREFUL(1U)

#घोषणा S_DACK_MSS_SELECTOR    3
#घोषणा M_DACK_MSS_SELECTOR    0x3
#घोषणा V_DACK_MSS_SELECTOR(x) ((x) << S_DACK_MSS_SELECTOR)
#घोषणा G_DACK_MSS_SELECTOR(x) (((x) >> S_DACK_MSS_SELECTOR) & M_DACK_MSS_SELECTOR)

#घोषणा S_DACK_BYTE_THRESHOLD    5
#घोषणा M_DACK_BYTE_THRESHOLD    0xfffff
#घोषणा V_DACK_BYTE_THRESHOLD(x) ((x) << S_DACK_BYTE_THRESHOLD)
#घोषणा G_DACK_BYTE_THRESHOLD(x) (((x) >> S_DACK_BYTE_THRESHOLD) & M_DACK_BYTE_THRESHOLD)

#घोषणा A_TP_PC_CONFIG 0x348

#घोषणा S_TP_ACCESS_LATENCY    0
#घोषणा M_TP_ACCESS_LATENCY    0xf
#घोषणा V_TP_ACCESS_LATENCY(x) ((x) << S_TP_ACCESS_LATENCY)
#घोषणा G_TP_ACCESS_LATENCY(x) (((x) >> S_TP_ACCESS_LATENCY) & M_TP_ACCESS_LATENCY)

#घोषणा S_HELD_FIN_DISABLE    4
#घोषणा V_HELD_FIN_DISABLE(x) ((x) << S_HELD_FIN_DISABLE)
#घोषणा F_HELD_FIN_DISABLE    V_HELD_FIN_DISABLE(1U)

#घोषणा S_DDP_FC_ENABLE    5
#घोषणा V_DDP_FC_ENABLE(x) ((x) << S_DDP_FC_ENABLE)
#घोषणा F_DDP_FC_ENABLE    V_DDP_FC_ENABLE(1U)

#घोषणा S_RDMA_ERR_ENABLE    6
#घोषणा V_RDMA_ERR_ENABLE(x) ((x) << S_RDMA_ERR_ENABLE)
#घोषणा F_RDMA_ERR_ENABLE    V_RDMA_ERR_ENABLE(1U)

#घोषणा S_FAST_PDU_DELIVERY    7
#घोषणा V_FAST_PDU_DELIVERY(x) ((x) << S_FAST_PDU_DELIVERY)
#घोषणा F_FAST_PDU_DELIVERY    V_FAST_PDU_DELIVERY(1U)

#घोषणा S_CLEAR_FIN    8
#घोषणा V_CLEAR_FIN(x) ((x) << S_CLEAR_FIN)
#घोषणा F_CLEAR_FIN    V_CLEAR_FIN(1U)

#घोषणा S_DIS_TX_FILL_WIN_PUSH    12
#घोषणा V_DIS_TX_FILL_WIN_PUSH(x) ((x) << S_DIS_TX_FILL_WIN_PUSH)
#घोषणा F_DIS_TX_FILL_WIN_PUSH    V_DIS_TX_FILL_WIN_PUSH(1U)

#घोषणा S_TP_PC_REV    30
#घोषणा M_TP_PC_REV    0x3
#घोषणा V_TP_PC_REV(x) ((x) << S_TP_PC_REV)
#घोषणा G_TP_PC_REV(x) (((x) >> S_TP_PC_REV) & M_TP_PC_REV)

#घोषणा A_TP_BACKOFF0 0x350

#घोषणा S_ELEMENT0    0
#घोषणा M_ELEMENT0    0xff
#घोषणा V_ELEMENT0(x) ((x) << S_ELEMENT0)
#घोषणा G_ELEMENT0(x) (((x) >> S_ELEMENT0) & M_ELEMENT0)

#घोषणा S_ELEMENT1    8
#घोषणा M_ELEMENT1    0xff
#घोषणा V_ELEMENT1(x) ((x) << S_ELEMENT1)
#घोषणा G_ELEMENT1(x) (((x) >> S_ELEMENT1) & M_ELEMENT1)

#घोषणा S_ELEMENT2    16
#घोषणा M_ELEMENT2    0xff
#घोषणा V_ELEMENT2(x) ((x) << S_ELEMENT2)
#घोषणा G_ELEMENT2(x) (((x) >> S_ELEMENT2) & M_ELEMENT2)

#घोषणा S_ELEMENT3    24
#घोषणा M_ELEMENT3    0xff
#घोषणा V_ELEMENT3(x) ((x) << S_ELEMENT3)
#घोषणा G_ELEMENT3(x) (((x) >> S_ELEMENT3) & M_ELEMENT3)

#घोषणा A_TP_BACKOFF1 0x354
#घोषणा A_TP_BACKOFF2 0x358
#घोषणा A_TP_BACKOFF3 0x35c
#घोषणा A_TP_PARA_REG0 0x360

#घोषणा S_VAR_MULT    0
#घोषणा M_VAR_MULT    0xf
#घोषणा V_VAR_MULT(x) ((x) << S_VAR_MULT)
#घोषणा G_VAR_MULT(x) (((x) >> S_VAR_MULT) & M_VAR_MULT)

#घोषणा S_VAR_GAIN    4
#घोषणा M_VAR_GAIN    0xf
#घोषणा V_VAR_GAIN(x) ((x) << S_VAR_GAIN)
#घोषणा G_VAR_GAIN(x) (((x) >> S_VAR_GAIN) & M_VAR_GAIN)

#घोषणा S_SRTT_GAIN    8
#घोषणा M_SRTT_GAIN    0xf
#घोषणा V_SRTT_GAIN(x) ((x) << S_SRTT_GAIN)
#घोषणा G_SRTT_GAIN(x) (((x) >> S_SRTT_GAIN) & M_SRTT_GAIN)

#घोषणा S_RTTVAR_INIT    12
#घोषणा M_RTTVAR_INIT    0xf
#घोषणा V_RTTVAR_INIT(x) ((x) << S_RTTVAR_INIT)
#घोषणा G_RTTVAR_INIT(x) (((x) >> S_RTTVAR_INIT) & M_RTTVAR_INIT)

#घोषणा S_DUP_THRESH    20
#घोषणा M_DUP_THRESH    0xf
#घोषणा V_DUP_THRESH(x) ((x) << S_DUP_THRESH)
#घोषणा G_DUP_THRESH(x) (((x) >> S_DUP_THRESH) & M_DUP_THRESH)

#घोषणा S_INIT_CONG_WIN    24
#घोषणा M_INIT_CONG_WIN    0x7
#घोषणा V_INIT_CONG_WIN(x) ((x) << S_INIT_CONG_WIN)
#घोषणा G_INIT_CONG_WIN(x) (((x) >> S_INIT_CONG_WIN) & M_INIT_CONG_WIN)

#घोषणा A_TP_PARA_REG1 0x364

#घोषणा S_INITIAL_SLOW_START_THRESHOLD    0
#घोषणा M_INITIAL_SLOW_START_THRESHOLD    0xffff
#घोषणा V_INITIAL_SLOW_START_THRESHOLD(x) ((x) << S_INITIAL_SLOW_START_THRESHOLD)
#घोषणा G_INITIAL_SLOW_START_THRESHOLD(x) (((x) >> S_INITIAL_SLOW_START_THRESHOLD) & M_INITIAL_SLOW_START_THRESHOLD)

#घोषणा S_RECEIVE_BUFFER_SIZE    16
#घोषणा M_RECEIVE_BUFFER_SIZE    0xffff
#घोषणा V_RECEIVE_BUFFER_SIZE(x) ((x) << S_RECEIVE_BUFFER_SIZE)
#घोषणा G_RECEIVE_BUFFER_SIZE(x) (((x) >> S_RECEIVE_BUFFER_SIZE) & M_RECEIVE_BUFFER_SIZE)

#घोषणा A_TP_PARA_REG2 0x368

#घोषणा S_RX_COALESCE_SIZE    0
#घोषणा M_RX_COALESCE_SIZE    0xffff
#घोषणा V_RX_COALESCE_SIZE(x) ((x) << S_RX_COALESCE_SIZE)
#घोषणा G_RX_COALESCE_SIZE(x) (((x) >> S_RX_COALESCE_SIZE) & M_RX_COALESCE_SIZE)

#घोषणा S_MAX_RX_SIZE    16
#घोषणा M_MAX_RX_SIZE    0xffff
#घोषणा V_MAX_RX_SIZE(x) ((x) << S_MAX_RX_SIZE)
#घोषणा G_MAX_RX_SIZE(x) (((x) >> S_MAX_RX_SIZE) & M_MAX_RX_SIZE)

#घोषणा A_TP_PARA_REG3 0x36c

#घोषणा S_RX_COALESCING_PSH_DELIVER    0
#घोषणा V_RX_COALESCING_PSH_DELIVER(x) ((x) << S_RX_COALESCING_PSH_DELIVER)
#घोषणा F_RX_COALESCING_PSH_DELIVER    V_RX_COALESCING_PSH_DELIVER(1U)

#घोषणा S_RX_COALESCING_ENABLE    1
#घोषणा V_RX_COALESCING_ENABLE(x) ((x) << S_RX_COALESCING_ENABLE)
#घोषणा F_RX_COALESCING_ENABLE    V_RX_COALESCING_ENABLE(1U)

#घोषणा S_TAHOE_ENABLE    2
#घोषणा V_TAHOE_ENABLE(x) ((x) << S_TAHOE_ENABLE)
#घोषणा F_TAHOE_ENABLE    V_TAHOE_ENABLE(1U)

#घोषणा S_MAX_REORDER_FRAGMENTS    12
#घोषणा M_MAX_REORDER_FRAGMENTS    0x7
#घोषणा V_MAX_REORDER_FRAGMENTS(x) ((x) << S_MAX_REORDER_FRAGMENTS)
#घोषणा G_MAX_REORDER_FRAGMENTS(x) (((x) >> S_MAX_REORDER_FRAGMENTS) & M_MAX_REORDER_FRAGMENTS)

#घोषणा A_TP_TIMER_RESOLUTION 0x390

#घोषणा S_DELAYED_ACK_TIMER_RESOLUTION    0
#घोषणा M_DELAYED_ACK_TIMER_RESOLUTION    0x3f
#घोषणा V_DELAYED_ACK_TIMER_RESOLUTION(x) ((x) << S_DELAYED_ACK_TIMER_RESOLUTION)
#घोषणा G_DELAYED_ACK_TIMER_RESOLUTION(x) (((x) >> S_DELAYED_ACK_TIMER_RESOLUTION) & M_DELAYED_ACK_TIMER_RESOLUTION)

#घोषणा S_GENERIC_TIMER_RESOLUTION    16
#घोषणा M_GENERIC_TIMER_RESOLUTION    0x3f
#घोषणा V_GENERIC_TIMER_RESOLUTION(x) ((x) << S_GENERIC_TIMER_RESOLUTION)
#घोषणा G_GENERIC_TIMER_RESOLUTION(x) (((x) >> S_GENERIC_TIMER_RESOLUTION) & M_GENERIC_TIMER_RESOLUTION)

#घोषणा A_TP_2MSL 0x394

#घोषणा S_2MSL    0
#घोषणा M_2MSL    0x3fffffff
#घोषणा V_2MSL(x) ((x) << S_2MSL)
#घोषणा G_2MSL(x) (((x) >> S_2MSL) & M_2MSL)

#घोषणा A_TP_RXT_MIN 0x398

#घोषणा S_RETRANSMIT_TIMER_MIN    0
#घोषणा M_RETRANSMIT_TIMER_MIN    0xffff
#घोषणा V_RETRANSMIT_TIMER_MIN(x) ((x) << S_RETRANSMIT_TIMER_MIN)
#घोषणा G_RETRANSMIT_TIMER_MIN(x) (((x) >> S_RETRANSMIT_TIMER_MIN) & M_RETRANSMIT_TIMER_MIN)

#घोषणा A_TP_RXT_MAX 0x39c

#घोषणा S_RETRANSMIT_TIMER_MAX    0
#घोषणा M_RETRANSMIT_TIMER_MAX    0x3fffffff
#घोषणा V_RETRANSMIT_TIMER_MAX(x) ((x) << S_RETRANSMIT_TIMER_MAX)
#घोषणा G_RETRANSMIT_TIMER_MAX(x) (((x) >> S_RETRANSMIT_TIMER_MAX) & M_RETRANSMIT_TIMER_MAX)

#घोषणा A_TP_PERS_MIN 0x3a0

#घोषणा S_PERSIST_TIMER_MIN    0
#घोषणा M_PERSIST_TIMER_MIN    0xffff
#घोषणा V_PERSIST_TIMER_MIN(x) ((x) << S_PERSIST_TIMER_MIN)
#घोषणा G_PERSIST_TIMER_MIN(x) (((x) >> S_PERSIST_TIMER_MIN) & M_PERSIST_TIMER_MIN)

#घोषणा A_TP_PERS_MAX 0x3a4

#घोषणा S_PERSIST_TIMER_MAX    0
#घोषणा M_PERSIST_TIMER_MAX    0x3fffffff
#घोषणा V_PERSIST_TIMER_MAX(x) ((x) << S_PERSIST_TIMER_MAX)
#घोषणा G_PERSIST_TIMER_MAX(x) (((x) >> S_PERSIST_TIMER_MAX) & M_PERSIST_TIMER_MAX)

#घोषणा A_TP_KEEP_IDLE 0x3ac

#घोषणा S_KEEP_ALIVE_IDLE_TIME    0
#घोषणा M_KEEP_ALIVE_IDLE_TIME    0x3fffffff
#घोषणा V_KEEP_ALIVE_IDLE_TIME(x) ((x) << S_KEEP_ALIVE_IDLE_TIME)
#घोषणा G_KEEP_ALIVE_IDLE_TIME(x) (((x) >> S_KEEP_ALIVE_IDLE_TIME) & M_KEEP_ALIVE_IDLE_TIME)

#घोषणा A_TP_KEEP_INTVL 0x3b0

#घोषणा S_KEEP_ALIVE_INTERVAL_TIME    0
#घोषणा M_KEEP_ALIVE_INTERVAL_TIME    0x3fffffff
#घोषणा V_KEEP_ALIVE_INTERVAL_TIME(x) ((x) << S_KEEP_ALIVE_INTERVAL_TIME)
#घोषणा G_KEEP_ALIVE_INTERVAL_TIME(x) (((x) >> S_KEEP_ALIVE_INTERVAL_TIME) & M_KEEP_ALIVE_INTERVAL_TIME)

#घोषणा A_TP_INIT_SRTT 0x3b4

#घोषणा S_INITIAL_SRTT    0
#घोषणा M_INITIAL_SRTT    0xffff
#घोषणा V_INITIAL_SRTT(x) ((x) << S_INITIAL_SRTT)
#घोषणा G_INITIAL_SRTT(x) (((x) >> S_INITIAL_SRTT) & M_INITIAL_SRTT)

#घोषणा A_TP_DACK_TIME 0x3b8

#घोषणा S_DELAYED_ACK_TIME    0
#घोषणा M_DELAYED_ACK_TIME    0x7ff
#घोषणा V_DELAYED_ACK_TIME(x) ((x) << S_DELAYED_ACK_TIME)
#घोषणा G_DELAYED_ACK_TIME(x) (((x) >> S_DELAYED_ACK_TIME) & M_DELAYED_ACK_TIME)

#घोषणा A_TP_FINWAIT2_TIME 0x3bc

#घोषणा S_FINWAIT2_TIME    0
#घोषणा M_FINWAIT2_TIME    0x3fffffff
#घोषणा V_FINWAIT2_TIME(x) ((x) << S_FINWAIT2_TIME)
#घोषणा G_FINWAIT2_TIME(x) (((x) >> S_FINWAIT2_TIME) & M_FINWAIT2_TIME)

#घोषणा A_TP_FAST_FINWAIT2_TIME 0x3c0

#घोषणा S_FAST_FINWAIT2_TIME    0
#घोषणा M_FAST_FINWAIT2_TIME    0x3fffffff
#घोषणा V_FAST_FINWAIT2_TIME(x) ((x) << S_FAST_FINWAIT2_TIME)
#घोषणा G_FAST_FINWAIT2_TIME(x) (((x) >> S_FAST_FINWAIT2_TIME) & M_FAST_FINWAIT2_TIME)

#घोषणा A_TP_SHIFT_CNT 0x3c4

#घोषणा S_KEEPALIVE_MAX    0
#घोषणा M_KEEPALIVE_MAX    0xff
#घोषणा V_KEEPALIVE_MAX(x) ((x) << S_KEEPALIVE_MAX)
#घोषणा G_KEEPALIVE_MAX(x) (((x) >> S_KEEPALIVE_MAX) & M_KEEPALIVE_MAX)

#घोषणा S_WINDOWPROBE_MAX    8
#घोषणा M_WINDOWPROBE_MAX    0xff
#घोषणा V_WINDOWPROBE_MAX(x) ((x) << S_WINDOWPROBE_MAX)
#घोषणा G_WINDOWPROBE_MAX(x) (((x) >> S_WINDOWPROBE_MAX) & M_WINDOWPROBE_MAX)

#घोषणा S_RETRANSMISSION_MAX    16
#घोषणा M_RETRANSMISSION_MAX    0xff
#घोषणा V_RETRANSMISSION_MAX(x) ((x) << S_RETRANSMISSION_MAX)
#घोषणा G_RETRANSMISSION_MAX(x) (((x) >> S_RETRANSMISSION_MAX) & M_RETRANSMISSION_MAX)

#घोषणा S_SYN_MAX    24
#घोषणा M_SYN_MAX    0xff
#घोषणा V_SYN_MAX(x) ((x) << S_SYN_MAX)
#घोषणा G_SYN_MAX(x) (((x) >> S_SYN_MAX) & M_SYN_MAX)

#घोषणा A_TP_QOS_REG0 0x3e0

#घोषणा S_L3_VALUE    0
#घोषणा M_L3_VALUE    0x3f
#घोषणा V_L3_VALUE(x) ((x) << S_L3_VALUE)
#घोषणा G_L3_VALUE(x) (((x) >> S_L3_VALUE) & M_L3_VALUE)

#घोषणा A_TP_QOS_REG1 0x3e4
#घोषणा A_TP_QOS_REG2 0x3e8
#घोषणा A_TP_QOS_REG3 0x3ec
#घोषणा A_TP_QOS_REG4 0x3f0
#घोषणा A_TP_QOS_REG5 0x3f4
#घोषणा A_TP_QOS_REG6 0x3f8
#घोषणा A_TP_QOS_REG7 0x3fc
#घोषणा A_TP_MTU_REG0 0x404
#घोषणा A_TP_MTU_REG1 0x408
#घोषणा A_TP_MTU_REG2 0x40c
#घोषणा A_TP_MTU_REG3 0x410
#घोषणा A_TP_MTU_REG4 0x414
#घोषणा A_TP_MTU_REG5 0x418
#घोषणा A_TP_MTU_REG6 0x41c
#घोषणा A_TP_MTU_REG7 0x420
#घोषणा A_TP_RESET 0x44c

#घोषणा S_TP_RESET    0
#घोषणा V_TP_RESET(x) ((x) << S_TP_RESET)
#घोषणा F_TP_RESET    V_TP_RESET(1U)

#घोषणा S_CM_MEMMGR_INIT    1
#घोषणा V_CM_MEMMGR_INIT(x) ((x) << S_CM_MEMMGR_INIT)
#घोषणा F_CM_MEMMGR_INIT    V_CM_MEMMGR_INIT(1U)

#घोषणा A_TP_MIB_INDEX 0x450
#घोषणा A_TP_MIB_DATA 0x454
#घोषणा A_TP_SYNC_TIME_HI 0x458
#घोषणा A_TP_SYNC_TIME_LO 0x45c
#घोषणा A_TP_CM_MM_RX_FLST_BASE 0x460

#घोषणा S_CM_MEMMGR_RX_FREE_LIST_BASE    0
#घोषणा M_CM_MEMMGR_RX_FREE_LIST_BASE    0xfffffff
#घोषणा V_CM_MEMMGR_RX_FREE_LIST_BASE(x) ((x) << S_CM_MEMMGR_RX_FREE_LIST_BASE)
#घोषणा G_CM_MEMMGR_RX_FREE_LIST_BASE(x) (((x) >> S_CM_MEMMGR_RX_FREE_LIST_BASE) & M_CM_MEMMGR_RX_FREE_LIST_BASE)

#घोषणा A_TP_CM_MM_TX_FLST_BASE 0x464

#घोषणा S_CM_MEMMGR_TX_FREE_LIST_BASE    0
#घोषणा M_CM_MEMMGR_TX_FREE_LIST_BASE    0xfffffff
#घोषणा V_CM_MEMMGR_TX_FREE_LIST_BASE(x) ((x) << S_CM_MEMMGR_TX_FREE_LIST_BASE)
#घोषणा G_CM_MEMMGR_TX_FREE_LIST_BASE(x) (((x) >> S_CM_MEMMGR_TX_FREE_LIST_BASE) & M_CM_MEMMGR_TX_FREE_LIST_BASE)

#घोषणा A_TP_CM_MM_P_FLST_BASE 0x468

#घोषणा S_CM_MEMMGR_PSTRUCT_FREE_LIST_BASE    0
#घोषणा M_CM_MEMMGR_PSTRUCT_FREE_LIST_BASE    0xfffffff
#घोषणा V_CM_MEMMGR_PSTRUCT_FREE_LIST_BASE(x) ((x) << S_CM_MEMMGR_PSTRUCT_FREE_LIST_BASE)
#घोषणा G_CM_MEMMGR_PSTRUCT_FREE_LIST_BASE(x) (((x) >> S_CM_MEMMGR_PSTRUCT_FREE_LIST_BASE) & M_CM_MEMMGR_PSTRUCT_FREE_LIST_BASE)

#घोषणा A_TP_CM_MM_MAX_P 0x46c

#घोषणा S_CM_MEMMGR_MAX_PSTRUCT    0
#घोषणा M_CM_MEMMGR_MAX_PSTRUCT    0xfffffff
#घोषणा V_CM_MEMMGR_MAX_PSTRUCT(x) ((x) << S_CM_MEMMGR_MAX_PSTRUCT)
#घोषणा G_CM_MEMMGR_MAX_PSTRUCT(x) (((x) >> S_CM_MEMMGR_MAX_PSTRUCT) & M_CM_MEMMGR_MAX_PSTRUCT)

#घोषणा A_TP_INT_ENABLE 0x470

#घोषणा S_TX_FREE_LIST_EMPTY    0
#घोषणा V_TX_FREE_LIST_EMPTY(x) ((x) << S_TX_FREE_LIST_EMPTY)
#घोषणा F_TX_FREE_LIST_EMPTY    V_TX_FREE_LIST_EMPTY(1U)

#घोषणा S_RX_FREE_LIST_EMPTY    1
#घोषणा V_RX_FREE_LIST_EMPTY(x) ((x) << S_RX_FREE_LIST_EMPTY)
#घोषणा F_RX_FREE_LIST_EMPTY    V_RX_FREE_LIST_EMPTY(1U)

#घोषणा A_TP_INT_CAUSE 0x474
#घोषणा A_TP_TIMER_SEPARATOR 0x4a4

#घोषणा S_DISABLE_PAST_TIMER_INSERTION    0
#घोषणा V_DISABLE_PAST_TIMER_INSERTION(x) ((x) << S_DISABLE_PAST_TIMER_INSERTION)
#घोषणा F_DISABLE_PAST_TIMER_INSERTION    V_DISABLE_PAST_TIMER_INSERTION(1U)

#घोषणा S_MODULATION_TIMER_SEPARATOR    1
#घोषणा M_MODULATION_TIMER_SEPARATOR    0x7fff
#घोषणा V_MODULATION_TIMER_SEPARATOR(x) ((x) << S_MODULATION_TIMER_SEPARATOR)
#घोषणा G_MODULATION_TIMER_SEPARATOR(x) (((x) >> S_MODULATION_TIMER_SEPARATOR) & M_MODULATION_TIMER_SEPARATOR)

#घोषणा S_GLOBAL_TIMER_SEPARATOR    16
#घोषणा M_GLOBAL_TIMER_SEPARATOR    0xffff
#घोषणा V_GLOBAL_TIMER_SEPARATOR(x) ((x) << S_GLOBAL_TIMER_SEPARATOR)
#घोषणा G_GLOBAL_TIMER_SEPARATOR(x) (((x) >> S_GLOBAL_TIMER_SEPARATOR) & M_GLOBAL_TIMER_SEPARATOR)

#घोषणा A_TP_CM_FC_MODE 0x4b0
#घोषणा A_TP_PC_CONGESTION_CNTL 0x4b4
#घोषणा A_TP_TX_DROP_CONFIG 0x4b8

#घोषणा S_ENABLE_TX_DROP    31
#घोषणा V_ENABLE_TX_DROP(x) ((x) << S_ENABLE_TX_DROP)
#घोषणा F_ENABLE_TX_DROP    V_ENABLE_TX_DROP(1U)

#घोषणा S_ENABLE_TX_ERROR    30
#घोषणा V_ENABLE_TX_ERROR(x) ((x) << S_ENABLE_TX_ERROR)
#घोषणा F_ENABLE_TX_ERROR    V_ENABLE_TX_ERROR(1U)

#घोषणा S_DROP_TICKS_CNT    4
#घोषणा M_DROP_TICKS_CNT    0x3ffffff
#घोषणा V_DROP_TICKS_CNT(x) ((x) << S_DROP_TICKS_CNT)
#घोषणा G_DROP_TICKS_CNT(x) (((x) >> S_DROP_TICKS_CNT) & M_DROP_TICKS_CNT)

#घोषणा S_NUM_PKTS_DROPPED    0
#घोषणा M_NUM_PKTS_DROPPED    0xf
#घोषणा V_NUM_PKTS_DROPPED(x) ((x) << S_NUM_PKTS_DROPPED)
#घोषणा G_NUM_PKTS_DROPPED(x) (((x) >> S_NUM_PKTS_DROPPED) & M_NUM_PKTS_DROPPED)

#घोषणा A_TP_TX_DROP_COUNT 0x4bc

/* RAT रेजिस्टरs */
#घोषणा A_RAT_ROUTE_CONTROL 0x580

#घोषणा S_USE_ROUTE_TABLE    0
#घोषणा V_USE_ROUTE_TABLE(x) ((x) << S_USE_ROUTE_TABLE)
#घोषणा F_USE_ROUTE_TABLE    V_USE_ROUTE_TABLE(1U)

#घोषणा S_ENABLE_CSPI    1
#घोषणा V_ENABLE_CSPI(x) ((x) << S_ENABLE_CSPI)
#घोषणा F_ENABLE_CSPI    V_ENABLE_CSPI(1U)

#घोषणा S_ENABLE_PCIX    2
#घोषणा V_ENABLE_PCIX(x) ((x) << S_ENABLE_PCIX)
#घोषणा F_ENABLE_PCIX    V_ENABLE_PCIX(1U)

#घोषणा A_RAT_ROUTE_TABLE_INDEX 0x584

#घोषणा S_ROUTE_TABLE_INDEX    0
#घोषणा M_ROUTE_TABLE_INDEX    0xf
#घोषणा V_ROUTE_TABLE_INDEX(x) ((x) << S_ROUTE_TABLE_INDEX)
#घोषणा G_ROUTE_TABLE_INDEX(x) (((x) >> S_ROUTE_TABLE_INDEX) & M_ROUTE_TABLE_INDEX)

#घोषणा A_RAT_ROUTE_TABLE_DATA 0x588
#घोषणा A_RAT_NO_ROUTE 0x58c

#घोषणा S_CPL_OPCODE    0
#घोषणा M_CPL_OPCODE    0xff
#घोषणा V_CPL_OPCODE(x) ((x) << S_CPL_OPCODE)
#घोषणा G_CPL_OPCODE(x) (((x) >> S_CPL_OPCODE) & M_CPL_OPCODE)

#घोषणा A_RAT_INTR_ENABLE 0x590

#घोषणा S_ZEROROUTEERROR    0
#घोषणा V_ZEROROUTEERROR(x) ((x) << S_ZEROROUTEERROR)
#घोषणा F_ZEROROUTEERROR    V_ZEROROUTEERROR(1U)

#घोषणा S_CSPIFRAMINGERROR    1
#घोषणा V_CSPIFRAMINGERROR(x) ((x) << S_CSPIFRAMINGERROR)
#घोषणा F_CSPIFRAMINGERROR    V_CSPIFRAMINGERROR(1U)

#घोषणा S_SGEFRAMINGERROR    2
#घोषणा V_SGEFRAMINGERROR(x) ((x) << S_SGEFRAMINGERROR)
#घोषणा F_SGEFRAMINGERROR    V_SGEFRAMINGERROR(1U)

#घोषणा S_TPFRAMINGERROR    3
#घोषणा V_TPFRAMINGERROR(x) ((x) << S_TPFRAMINGERROR)
#घोषणा F_TPFRAMINGERROR    V_TPFRAMINGERROR(1U)

#घोषणा A_RAT_INTR_CAUSE 0x594

/* CSPI रेजिस्टरs */
#घोषणा A_CSPI_RX_AE_WM 0x810
#घोषणा A_CSPI_RX_AF_WM 0x814
#घोषणा A_CSPI_CALENDAR_LEN 0x818

#घोषणा S_CALENDARLENGTH    0
#घोषणा M_CALENDARLENGTH    0xffff
#घोषणा V_CALENDARLENGTH(x) ((x) << S_CALENDARLENGTH)
#घोषणा G_CALENDARLENGTH(x) (((x) >> S_CALENDARLENGTH) & M_CALENDARLENGTH)

#घोषणा A_CSPI_FIFO_STATUS_ENABLE 0x820

#घोषणा S_FIFOSTATUSENABLE    0
#घोषणा V_FIFOSTATUSENABLE(x) ((x) << S_FIFOSTATUSENABLE)
#घोषणा F_FIFOSTATUSENABLE    V_FIFOSTATUSENABLE(1U)

#घोषणा A_CSPI_MAXBURST1_MAXBURST2 0x828

#घोषणा S_MAXBURST1    0
#घोषणा M_MAXBURST1    0xffff
#घोषणा V_MAXBURST1(x) ((x) << S_MAXBURST1)
#घोषणा G_MAXBURST1(x) (((x) >> S_MAXBURST1) & M_MAXBURST1)

#घोषणा S_MAXBURST2    16
#घोषणा M_MAXBURST2    0xffff
#घोषणा V_MAXBURST2(x) ((x) << S_MAXBURST2)
#घोषणा G_MAXBURST2(x) (((x) >> S_MAXBURST2) & M_MAXBURST2)

#घोषणा A_CSPI_TRAIN 0x82c

#घोषणा S_CSPI_TRAIN_ALPHA    0
#घोषणा M_CSPI_TRAIN_ALPHA    0xffff
#घोषणा V_CSPI_TRAIN_ALPHA(x) ((x) << S_CSPI_TRAIN_ALPHA)
#घोषणा G_CSPI_TRAIN_ALPHA(x) (((x) >> S_CSPI_TRAIN_ALPHA) & M_CSPI_TRAIN_ALPHA)

#घोषणा S_CSPI_TRAIN_DATA_MAXT    16
#घोषणा M_CSPI_TRAIN_DATA_MAXT    0xffff
#घोषणा V_CSPI_TRAIN_DATA_MAXT(x) ((x) << S_CSPI_TRAIN_DATA_MAXT)
#घोषणा G_CSPI_TRAIN_DATA_MAXT(x) (((x) >> S_CSPI_TRAIN_DATA_MAXT) & M_CSPI_TRAIN_DATA_MAXT)

#घोषणा A_CSPI_INTR_STATUS 0x848

#घोषणा S_DIP4ERR    0
#घोषणा V_DIP4ERR(x) ((x) << S_DIP4ERR)
#घोषणा F_DIP4ERR    V_DIP4ERR(1U)

#घोषणा S_RXDROP    1
#घोषणा V_RXDROP(x) ((x) << S_RXDROP)
#घोषणा F_RXDROP    V_RXDROP(1U)

#घोषणा S_TXDROP    2
#घोषणा V_TXDROP(x) ((x) << S_TXDROP)
#घोषणा F_TXDROP    V_TXDROP(1U)

#घोषणा S_RXOVERFLOW    3
#घोषणा V_RXOVERFLOW(x) ((x) << S_RXOVERFLOW)
#घोषणा F_RXOVERFLOW    V_RXOVERFLOW(1U)

#घोषणा S_RAMPARITYERR    4
#घोषणा V_RAMPARITYERR(x) ((x) << S_RAMPARITYERR)
#घोषणा F_RAMPARITYERR    V_RAMPARITYERR(1U)

#घोषणा A_CSPI_INTR_ENABLE 0x84c

/* ESPI रेजिस्टरs */
#घोषणा A_ESPI_SCH_TOKEN0 0x880

#घोषणा S_SCHTOKEN0    0
#घोषणा M_SCHTOKEN0    0xffff
#घोषणा V_SCHTOKEN0(x) ((x) << S_SCHTOKEN0)
#घोषणा G_SCHTOKEN0(x) (((x) >> S_SCHTOKEN0) & M_SCHTOKEN0)

#घोषणा A_ESPI_SCH_TOKEN1 0x884

#घोषणा S_SCHTOKEN1    0
#घोषणा M_SCHTOKEN1    0xffff
#घोषणा V_SCHTOKEN1(x) ((x) << S_SCHTOKEN1)
#घोषणा G_SCHTOKEN1(x) (((x) >> S_SCHTOKEN1) & M_SCHTOKEN1)

#घोषणा A_ESPI_SCH_TOKEN2 0x888

#घोषणा S_SCHTOKEN2    0
#घोषणा M_SCHTOKEN2    0xffff
#घोषणा V_SCHTOKEN2(x) ((x) << S_SCHTOKEN2)
#घोषणा G_SCHTOKEN2(x) (((x) >> S_SCHTOKEN2) & M_SCHTOKEN2)

#घोषणा A_ESPI_SCH_TOKEN3 0x88c

#घोषणा S_SCHTOKEN3    0
#घोषणा M_SCHTOKEN3    0xffff
#घोषणा V_SCHTOKEN3(x) ((x) << S_SCHTOKEN3)
#घोषणा G_SCHTOKEN3(x) (((x) >> S_SCHTOKEN3) & M_SCHTOKEN3)

#घोषणा A_ESPI_RX_FIFO_ALMOST_EMPTY_WATERMARK 0x890

#घोषणा S_ALMOSTEMPTY    0
#घोषणा M_ALMOSTEMPTY    0xffff
#घोषणा V_ALMOSTEMPTY(x) ((x) << S_ALMOSTEMPTY)
#घोषणा G_ALMOSTEMPTY(x) (((x) >> S_ALMOSTEMPTY) & M_ALMOSTEMPTY)

#घोषणा A_ESPI_RX_FIFO_ALMOST_FULL_WATERMARK 0x894

#घोषणा S_ALMOSTFULL    0
#घोषणा M_ALMOSTFULL    0xffff
#घोषणा V_ALMOSTFULL(x) ((x) << S_ALMOSTFULL)
#घोषणा G_ALMOSTFULL(x) (((x) >> S_ALMOSTFULL) & M_ALMOSTFULL)

#घोषणा A_ESPI_CALENDAR_LENGTH 0x898
#घोषणा A_PORT_CONFIG 0x89c

#घोषणा S_RX_NPORTS    0
#घोषणा M_RX_NPORTS    0xff
#घोषणा V_RX_NPORTS(x) ((x) << S_RX_NPORTS)
#घोषणा G_RX_NPORTS(x) (((x) >> S_RX_NPORTS) & M_RX_NPORTS)

#घोषणा S_TX_NPORTS    8
#घोषणा M_TX_NPORTS    0xff
#घोषणा V_TX_NPORTS(x) ((x) << S_TX_NPORTS)
#घोषणा G_TX_NPORTS(x) (((x) >> S_TX_NPORTS) & M_TX_NPORTS)

#घोषणा A_ESPI_FIFO_STATUS_ENABLE 0x8a0

#घोषणा S_RXSTATUSENABLE    0
#घोषणा V_RXSTATUSENABLE(x) ((x) << S_RXSTATUSENABLE)
#घोषणा F_RXSTATUSENABLE    V_RXSTATUSENABLE(1U)

#घोषणा S_TXDROPENABLE    1
#घोषणा V_TXDROPENABLE(x) ((x) << S_TXDROPENABLE)
#घोषणा F_TXDROPENABLE    V_TXDROPENABLE(1U)

#घोषणा S_RXENDIANMODE    2
#घोषणा V_RXENDIANMODE(x) ((x) << S_RXENDIANMODE)
#घोषणा F_RXENDIANMODE    V_RXENDIANMODE(1U)

#घोषणा S_TXENDIANMODE    3
#घोषणा V_TXENDIANMODE(x) ((x) << S_TXENDIANMODE)
#घोषणा F_TXENDIANMODE    V_TXENDIANMODE(1U)

#घोषणा S_INTEL1010MODE    4
#घोषणा V_INTEL1010MODE(x) ((x) << S_INTEL1010MODE)
#घोषणा F_INTEL1010MODE    V_INTEL1010MODE(1U)

#घोषणा A_ESPI_MAXBURST1_MAXBURST2 0x8a8
#घोषणा A_ESPI_TRAIN 0x8ac

#घोषणा S_MAXTRAINALPHA    0
#घोषणा M_MAXTRAINALPHA    0xffff
#घोषणा V_MAXTRAINALPHA(x) ((x) << S_MAXTRAINALPHA)
#घोषणा G_MAXTRAINALPHA(x) (((x) >> S_MAXTRAINALPHA) & M_MAXTRAINALPHA)

#घोषणा S_MAXTRAINDATA    16
#घोषणा M_MAXTRAINDATA    0xffff
#घोषणा V_MAXTRAINDATA(x) ((x) << S_MAXTRAINDATA)
#घोषणा G_MAXTRAINDATA(x) (((x) >> S_MAXTRAINDATA) & M_MAXTRAINDATA)

#घोषणा A_RAM_STATUS 0x8b0

#घोषणा S_RXFIFOPARITYERROR    0
#घोषणा M_RXFIFOPARITYERROR    0x3ff
#घोषणा V_RXFIFOPARITYERROR(x) ((x) << S_RXFIFOPARITYERROR)
#घोषणा G_RXFIFOPARITYERROR(x) (((x) >> S_RXFIFOPARITYERROR) & M_RXFIFOPARITYERROR)

#घोषणा S_TXFIFOPARITYERROR    10
#घोषणा M_TXFIFOPARITYERROR    0x3ff
#घोषणा V_TXFIFOPARITYERROR(x) ((x) << S_TXFIFOPARITYERROR)
#घोषणा G_TXFIFOPARITYERROR(x) (((x) >> S_TXFIFOPARITYERROR) & M_TXFIFOPARITYERROR)

#घोषणा S_RXFIFOOVERFLOW    20
#घोषणा M_RXFIFOOVERFLOW    0x3ff
#घोषणा V_RXFIFOOVERFLOW(x) ((x) << S_RXFIFOOVERFLOW)
#घोषणा G_RXFIFOOVERFLOW(x) (((x) >> S_RXFIFOOVERFLOW) & M_RXFIFOOVERFLOW)

#घोषणा A_TX_DROP_COUNT0 0x8b4

#घोषणा S_TXPORT0DROPCNT    0
#घोषणा M_TXPORT0DROPCNT    0xffff
#घोषणा V_TXPORT0DROPCNT(x) ((x) << S_TXPORT0DROPCNT)
#घोषणा G_TXPORT0DROPCNT(x) (((x) >> S_TXPORT0DROPCNT) & M_TXPORT0DROPCNT)

#घोषणा S_TXPORT1DROPCNT    16
#घोषणा M_TXPORT1DROPCNT    0xffff
#घोषणा V_TXPORT1DROPCNT(x) ((x) << S_TXPORT1DROPCNT)
#घोषणा G_TXPORT1DROPCNT(x) (((x) >> S_TXPORT1DROPCNT) & M_TXPORT1DROPCNT)

#घोषणा A_TX_DROP_COUNT1 0x8b8

#घोषणा S_TXPORT2DROPCNT    0
#घोषणा M_TXPORT2DROPCNT    0xffff
#घोषणा V_TXPORT2DROPCNT(x) ((x) << S_TXPORT2DROPCNT)
#घोषणा G_TXPORT2DROPCNT(x) (((x) >> S_TXPORT2DROPCNT) & M_TXPORT2DROPCNT)

#घोषणा S_TXPORT3DROPCNT    16
#घोषणा M_TXPORT3DROPCNT    0xffff
#घोषणा V_TXPORT3DROPCNT(x) ((x) << S_TXPORT3DROPCNT)
#घोषणा G_TXPORT3DROPCNT(x) (((x) >> S_TXPORT3DROPCNT) & M_TXPORT3DROPCNT)

#घोषणा A_RX_DROP_COUNT0 0x8bc

#घोषणा S_RXPORT0DROPCNT    0
#घोषणा M_RXPORT0DROPCNT    0xffff
#घोषणा V_RXPORT0DROPCNT(x) ((x) << S_RXPORT0DROPCNT)
#घोषणा G_RXPORT0DROPCNT(x) (((x) >> S_RXPORT0DROPCNT) & M_RXPORT0DROPCNT)

#घोषणा S_RXPORT1DROPCNT    16
#घोषणा M_RXPORT1DROPCNT    0xffff
#घोषणा V_RXPORT1DROPCNT(x) ((x) << S_RXPORT1DROPCNT)
#घोषणा G_RXPORT1DROPCNT(x) (((x) >> S_RXPORT1DROPCNT) & M_RXPORT1DROPCNT)

#घोषणा A_RX_DROP_COUNT1 0x8c0

#घोषणा S_RXPORT2DROPCNT    0
#घोषणा M_RXPORT2DROPCNT    0xffff
#घोषणा V_RXPORT2DROPCNT(x) ((x) << S_RXPORT2DROPCNT)
#घोषणा G_RXPORT2DROPCNT(x) (((x) >> S_RXPORT2DROPCNT) & M_RXPORT2DROPCNT)

#घोषणा S_RXPORT3DROPCNT    16
#घोषणा M_RXPORT3DROPCNT    0xffff
#घोषणा V_RXPORT3DROPCNT(x) ((x) << S_RXPORT3DROPCNT)
#घोषणा G_RXPORT3DROPCNT(x) (((x) >> S_RXPORT3DROPCNT) & M_RXPORT3DROPCNT)

#घोषणा A_DIP4_ERROR_COUNT 0x8c4

#घोषणा S_DIP4ERRORCNT    0
#घोषणा M_DIP4ERRORCNT    0xfff
#घोषणा V_DIP4ERRORCNT(x) ((x) << S_DIP4ERRORCNT)
#घोषणा G_DIP4ERRORCNT(x) (((x) >> S_DIP4ERRORCNT) & M_DIP4ERRORCNT)

#घोषणा S_DIP4ERRORCNTSHADOW    12
#घोषणा M_DIP4ERRORCNTSHADOW    0xfff
#घोषणा V_DIP4ERRORCNTSHADOW(x) ((x) << S_DIP4ERRORCNTSHADOW)
#घोषणा G_DIP4ERRORCNTSHADOW(x) (((x) >> S_DIP4ERRORCNTSHADOW) & M_DIP4ERRORCNTSHADOW)

#घोषणा S_TRICN_RX_TRAIN_ERR    24
#घोषणा V_TRICN_RX_TRAIN_ERR(x) ((x) << S_TRICN_RX_TRAIN_ERR)
#घोषणा F_TRICN_RX_TRAIN_ERR    V_TRICN_RX_TRAIN_ERR(1U)

#घोषणा S_TRICN_RX_TRAINING    25
#घोषणा V_TRICN_RX_TRAINING(x) ((x) << S_TRICN_RX_TRAINING)
#घोषणा F_TRICN_RX_TRAINING    V_TRICN_RX_TRAINING(1U)

#घोषणा S_TRICN_RX_TRAIN_OK    26
#घोषणा V_TRICN_RX_TRAIN_OK(x) ((x) << S_TRICN_RX_TRAIN_OK)
#घोषणा F_TRICN_RX_TRAIN_OK    V_TRICN_RX_TRAIN_OK(1U)

#घोषणा A_ESPI_INTR_STATUS 0x8c8

#घोषणा S_DIP2PARITYERR    5
#घोषणा V_DIP2PARITYERR(x) ((x) << S_DIP2PARITYERR)
#घोषणा F_DIP2PARITYERR    V_DIP2PARITYERR(1U)

#घोषणा A_ESPI_INTR_ENABLE 0x8cc
#घोषणा A_RX_DROP_THRESHOLD 0x8d0
#घोषणा A_ESPI_RX_RESET 0x8ec

#घोषणा S_ESPI_RX_LNK_RST    0
#घोषणा V_ESPI_RX_LNK_RST(x) ((x) << S_ESPI_RX_LNK_RST)
#घोषणा F_ESPI_RX_LNK_RST    V_ESPI_RX_LNK_RST(1U)

#घोषणा S_ESPI_RX_CORE_RST    1
#घोषणा V_ESPI_RX_CORE_RST(x) ((x) << S_ESPI_RX_CORE_RST)
#घोषणा F_ESPI_RX_CORE_RST    V_ESPI_RX_CORE_RST(1U)

#घोषणा S_RX_CLK_STATUS    2
#घोषणा V_RX_CLK_STATUS(x) ((x) << S_RX_CLK_STATUS)
#घोषणा F_RX_CLK_STATUS    V_RX_CLK_STATUS(1U)

#घोषणा A_ESPI_MISC_CONTROL 0x8f0

#घोषणा S_OUT_OF_SYNC_COUNT    0
#घोषणा M_OUT_OF_SYNC_COUNT    0xf
#घोषणा V_OUT_OF_SYNC_COUNT(x) ((x) << S_OUT_OF_SYNC_COUNT)
#घोषणा G_OUT_OF_SYNC_COUNT(x) (((x) >> S_OUT_OF_SYNC_COUNT) & M_OUT_OF_SYNC_COUNT)

#घोषणा S_DIP2_COUNT_MODE_ENABLE    4
#घोषणा V_DIP2_COUNT_MODE_ENABLE(x) ((x) << S_DIP2_COUNT_MODE_ENABLE)
#घोषणा F_DIP2_COUNT_MODE_ENABLE    V_DIP2_COUNT_MODE_ENABLE(1U)

#घोषणा S_DIP2_PARITY_ERR_THRES    5
#घोषणा M_DIP2_PARITY_ERR_THRES    0xf
#घोषणा V_DIP2_PARITY_ERR_THRES(x) ((x) << S_DIP2_PARITY_ERR_THRES)
#घोषणा G_DIP2_PARITY_ERR_THRES(x) (((x) >> S_DIP2_PARITY_ERR_THRES) & M_DIP2_PARITY_ERR_THRES)

#घोषणा S_DIP4_THRES    9
#घोषणा M_DIP4_THRES    0xfff
#घोषणा V_DIP4_THRES(x) ((x) << S_DIP4_THRES)
#घोषणा G_DIP4_THRES(x) (((x) >> S_DIP4_THRES) & M_DIP4_THRES)

#घोषणा S_DIP4_THRES_ENABLE    21
#घोषणा V_DIP4_THRES_ENABLE(x) ((x) << S_DIP4_THRES_ENABLE)
#घोषणा F_DIP4_THRES_ENABLE    V_DIP4_THRES_ENABLE(1U)

#घोषणा S_FORCE_DISABLE_STATUS    22
#घोषणा V_FORCE_DISABLE_STATUS(x) ((x) << S_FORCE_DISABLE_STATUS)
#घोषणा F_FORCE_DISABLE_STATUS    V_FORCE_DISABLE_STATUS(1U)

#घोषणा S_DYNAMIC_DESKEW    23
#घोषणा V_DYNAMIC_DESKEW(x) ((x) << S_DYNAMIC_DESKEW)
#घोषणा F_DYNAMIC_DESKEW    V_DYNAMIC_DESKEW(1U)

#घोषणा S_MONITORED_PORT_NUM    25
#घोषणा M_MONITORED_PORT_NUM    0x3
#घोषणा V_MONITORED_PORT_NUM(x) ((x) << S_MONITORED_PORT_NUM)
#घोषणा G_MONITORED_PORT_NUM(x) (((x) >> S_MONITORED_PORT_NUM) & M_MONITORED_PORT_NUM)

#घोषणा S_MONITORED_सूचीECTION    27
#घोषणा V_MONITORED_सूचीECTION(x) ((x) << S_MONITORED_सूचीECTION)
#घोषणा F_MONITORED_सूचीECTION    V_MONITORED_सूचीECTION(1U)

#घोषणा S_MONITORED_INTERFACE    28
#घोषणा V_MONITORED_INTERFACE(x) ((x) << S_MONITORED_INTERFACE)
#घोषणा F_MONITORED_INTERFACE    V_MONITORED_INTERFACE(1U)

#घोषणा A_ESPI_DIP2_ERR_COUNT 0x8f4

#घोषणा S_DIP2_ERR_CNT    0
#घोषणा M_DIP2_ERR_CNT    0xf
#घोषणा V_DIP2_ERR_CNT(x) ((x) << S_DIP2_ERR_CNT)
#घोषणा G_DIP2_ERR_CNT(x) (((x) >> S_DIP2_ERR_CNT) & M_DIP2_ERR_CNT)

#घोषणा A_ESPI_CMD_ADDR 0x8f8

#घोषणा S_WRITE_DATA    0
#घोषणा M_WRITE_DATA    0xff
#घोषणा V_WRITE_DATA(x) ((x) << S_WRITE_DATA)
#घोषणा G_WRITE_DATA(x) (((x) >> S_WRITE_DATA) & M_WRITE_DATA)

#घोषणा S_REGISTER_OFFSET    8
#घोषणा M_REGISTER_OFFSET    0xf
#घोषणा V_REGISTER_OFFSET(x) ((x) << S_REGISTER_OFFSET)
#घोषणा G_REGISTER_OFFSET(x) (((x) >> S_REGISTER_OFFSET) & M_REGISTER_OFFSET)

#घोषणा S_CHANNEL_ADDR    12
#घोषणा M_CHANNEL_ADDR    0xf
#घोषणा V_CHANNEL_ADDR(x) ((x) << S_CHANNEL_ADDR)
#घोषणा G_CHANNEL_ADDR(x) (((x) >> S_CHANNEL_ADDR) & M_CHANNEL_ADDR)

#घोषणा S_MODULE_ADDR    16
#घोषणा M_MODULE_ADDR    0x3
#घोषणा V_MODULE_ADDR(x) ((x) << S_MODULE_ADDR)
#घोषणा G_MODULE_ADDR(x) (((x) >> S_MODULE_ADDR) & M_MODULE_ADDR)

#घोषणा S_BUNDLE_ADDR    20
#घोषणा M_BUNDLE_ADDR    0x3
#घोषणा V_BUNDLE_ADDR(x) ((x) << S_BUNDLE_ADDR)
#घोषणा G_BUNDLE_ADDR(x) (((x) >> S_BUNDLE_ADDR) & M_BUNDLE_ADDR)

#घोषणा S_SPI4_COMMAND    24
#घोषणा M_SPI4_COMMAND    0xff
#घोषणा V_SPI4_COMMAND(x) ((x) << S_SPI4_COMMAND)
#घोषणा G_SPI4_COMMAND(x) (((x) >> S_SPI4_COMMAND) & M_SPI4_COMMAND)

#घोषणा A_ESPI_GOSTAT 0x8fc

#घोषणा S_READ_DATA    0
#घोषणा M_READ_DATA    0xff
#घोषणा V_READ_DATA(x) ((x) << S_READ_DATA)
#घोषणा G_READ_DATA(x) (((x) >> S_READ_DATA) & M_READ_DATA)

#घोषणा S_ESPI_CMD_BUSY    8
#घोषणा V_ESPI_CMD_BUSY(x) ((x) << S_ESPI_CMD_BUSY)
#घोषणा F_ESPI_CMD_BUSY    V_ESPI_CMD_BUSY(1U)

#घोषणा S_ERROR_ACK    9
#घोषणा V_ERROR_ACK(x) ((x) << S_ERROR_ACK)
#घोषणा F_ERROR_ACK    V_ERROR_ACK(1U)

#घोषणा S_UNMAPPED_ERR    10
#घोषणा V_UNMAPPED_ERR(x) ((x) << S_UNMAPPED_ERR)
#घोषणा F_UNMAPPED_ERR    V_UNMAPPED_ERR(1U)

#घोषणा S_TRANSACTION_TIMER    16
#घोषणा M_TRANSACTION_TIMER    0xff
#घोषणा V_TRANSACTION_TIMER(x) ((x) << S_TRANSACTION_TIMER)
#घोषणा G_TRANSACTION_TIMER(x) (((x) >> S_TRANSACTION_TIMER) & M_TRANSACTION_TIMER)


/* ULP रेजिस्टरs */
#घोषणा A_ULP_ULIMIT 0x980
#घोषणा A_ULP_TAGMASK 0x984
#घोषणा A_ULP_HREG_INDEX 0x988
#घोषणा A_ULP_HREG_DATA 0x98c
#घोषणा A_ULP_INT_ENABLE 0x990
#घोषणा A_ULP_INT_CAUSE 0x994

#घोषणा S_HREG_PAR_ERR    0
#घोषणा V_HREG_PAR_ERR(x) ((x) << S_HREG_PAR_ERR)
#घोषणा F_HREG_PAR_ERR    V_HREG_PAR_ERR(1U)

#घोषणा S_EGRS_DATA_PAR_ERR    1
#घोषणा V_EGRS_DATA_PAR_ERR(x) ((x) << S_EGRS_DATA_PAR_ERR)
#घोषणा F_EGRS_DATA_PAR_ERR    V_EGRS_DATA_PAR_ERR(1U)

#घोषणा S_INGRS_DATA_PAR_ERR    2
#घोषणा V_INGRS_DATA_PAR_ERR(x) ((x) << S_INGRS_DATA_PAR_ERR)
#घोषणा F_INGRS_DATA_PAR_ERR    V_INGRS_DATA_PAR_ERR(1U)

#घोषणा S_PM_INTR    3
#घोषणा V_PM_INTR(x) ((x) << S_PM_INTR)
#घोषणा F_PM_INTR    V_PM_INTR(1U)

#घोषणा S_PM_E2C_SYNC_ERR    4
#घोषणा V_PM_E2C_SYNC_ERR(x) ((x) << S_PM_E2C_SYNC_ERR)
#घोषणा F_PM_E2C_SYNC_ERR    V_PM_E2C_SYNC_ERR(1U)

#घोषणा S_PM_C2E_SYNC_ERR    5
#घोषणा V_PM_C2E_SYNC_ERR(x) ((x) << S_PM_C2E_SYNC_ERR)
#घोषणा F_PM_C2E_SYNC_ERR    V_PM_C2E_SYNC_ERR(1U)

#घोषणा S_PM_E2C_EMPTY_ERR    6
#घोषणा V_PM_E2C_EMPTY_ERR(x) ((x) << S_PM_E2C_EMPTY_ERR)
#घोषणा F_PM_E2C_EMPTY_ERR    V_PM_E2C_EMPTY_ERR(1U)

#घोषणा S_PM_C2E_EMPTY_ERR    7
#घोषणा V_PM_C2E_EMPTY_ERR(x) ((x) << S_PM_C2E_EMPTY_ERR)
#घोषणा F_PM_C2E_EMPTY_ERR    V_PM_C2E_EMPTY_ERR(1U)

#घोषणा S_PM_PAR_ERR    8
#घोषणा M_PM_PAR_ERR    0xffff
#घोषणा V_PM_PAR_ERR(x) ((x) << S_PM_PAR_ERR)
#घोषणा G_PM_PAR_ERR(x) (((x) >> S_PM_PAR_ERR) & M_PM_PAR_ERR)

#घोषणा S_PM_E2C_WRT_FULL    24
#घोषणा V_PM_E2C_WRT_FULL(x) ((x) << S_PM_E2C_WRT_FULL)
#घोषणा F_PM_E2C_WRT_FULL    V_PM_E2C_WRT_FULL(1U)

#घोषणा S_PM_C2E_WRT_FULL    25
#घोषणा V_PM_C2E_WRT_FULL(x) ((x) << S_PM_C2E_WRT_FULL)
#घोषणा F_PM_C2E_WRT_FULL    V_PM_C2E_WRT_FULL(1U)

#घोषणा A_ULP_PIO_CTRL 0x998

/* PL रेजिस्टरs */
#घोषणा A_PL_ENABLE 0xa00

#घोषणा S_PL_INTR_SGE_ERR    0
#घोषणा V_PL_INTR_SGE_ERR(x) ((x) << S_PL_INTR_SGE_ERR)
#घोषणा F_PL_INTR_SGE_ERR    V_PL_INTR_SGE_ERR(1U)

#घोषणा S_PL_INTR_SGE_DATA    1
#घोषणा V_PL_INTR_SGE_DATA(x) ((x) << S_PL_INTR_SGE_DATA)
#घोषणा F_PL_INTR_SGE_DATA    V_PL_INTR_SGE_DATA(1U)

#घोषणा S_PL_INTR_MC3    2
#घोषणा V_PL_INTR_MC3(x) ((x) << S_PL_INTR_MC3)
#घोषणा F_PL_INTR_MC3    V_PL_INTR_MC3(1U)

#घोषणा S_PL_INTR_MC4    3
#घोषणा V_PL_INTR_MC4(x) ((x) << S_PL_INTR_MC4)
#घोषणा F_PL_INTR_MC4    V_PL_INTR_MC4(1U)

#घोषणा S_PL_INTR_MC5    4
#घोषणा V_PL_INTR_MC5(x) ((x) << S_PL_INTR_MC5)
#घोषणा F_PL_INTR_MC5    V_PL_INTR_MC5(1U)

#घोषणा S_PL_INTR_RAT    5
#घोषणा V_PL_INTR_RAT(x) ((x) << S_PL_INTR_RAT)
#घोषणा F_PL_INTR_RAT    V_PL_INTR_RAT(1U)

#घोषणा S_PL_INTR_TP    6
#घोषणा V_PL_INTR_TP(x) ((x) << S_PL_INTR_TP)
#घोषणा F_PL_INTR_TP    V_PL_INTR_TP(1U)

#घोषणा S_PL_INTR_ULP    7
#घोषणा V_PL_INTR_ULP(x) ((x) << S_PL_INTR_ULP)
#घोषणा F_PL_INTR_ULP    V_PL_INTR_ULP(1U)

#घोषणा S_PL_INTR_ESPI    8
#घोषणा V_PL_INTR_ESPI(x) ((x) << S_PL_INTR_ESPI)
#घोषणा F_PL_INTR_ESPI    V_PL_INTR_ESPI(1U)

#घोषणा S_PL_INTR_CSPI    9
#घोषणा V_PL_INTR_CSPI(x) ((x) << S_PL_INTR_CSPI)
#घोषणा F_PL_INTR_CSPI    V_PL_INTR_CSPI(1U)

#घोषणा S_PL_INTR_PCIX    10
#घोषणा V_PL_INTR_PCIX(x) ((x) << S_PL_INTR_PCIX)
#घोषणा F_PL_INTR_PCIX    V_PL_INTR_PCIX(1U)

#घोषणा S_PL_INTR_EXT    11
#घोषणा V_PL_INTR_EXT(x) ((x) << S_PL_INTR_EXT)
#घोषणा F_PL_INTR_EXT    V_PL_INTR_EXT(1U)

#घोषणा A_PL_CAUSE 0xa04

/* MC5 रेजिस्टरs */
#घोषणा A_MC5_CONFIG 0xc04

#घोषणा S_MODE    0
#घोषणा V_MODE(x) ((x) << S_MODE)
#घोषणा F_MODE    V_MODE(1U)

#घोषणा S_TCAM_RESET    1
#घोषणा V_TCAM_RESET(x) ((x) << S_TCAM_RESET)
#घोषणा F_TCAM_RESET    V_TCAM_RESET(1U)

#घोषणा S_TCAM_READY    2
#घोषणा V_TCAM_READY(x) ((x) << S_TCAM_READY)
#घोषणा F_TCAM_READY    V_TCAM_READY(1U)

#घोषणा S_DBGI_ENABLE    4
#घोषणा V_DBGI_ENABLE(x) ((x) << S_DBGI_ENABLE)
#घोषणा F_DBGI_ENABLE    V_DBGI_ENABLE(1U)

#घोषणा S_M_BUS_ENABLE    5
#घोषणा V_M_BUS_ENABLE(x) ((x) << S_M_BUS_ENABLE)
#घोषणा F_M_BUS_ENABLE    V_M_BUS_ENABLE(1U)

#घोषणा S_PARITY_ENABLE    6
#घोषणा V_PARITY_ENABLE(x) ((x) << S_PARITY_ENABLE)
#घोषणा F_PARITY_ENABLE    V_PARITY_ENABLE(1U)

#घोषणा S_SYN_ISSUE_MODE    7
#घोषणा M_SYN_ISSUE_MODE    0x3
#घोषणा V_SYN_ISSUE_MODE(x) ((x) << S_SYN_ISSUE_MODE)
#घोषणा G_SYN_ISSUE_MODE(x) (((x) >> S_SYN_ISSUE_MODE) & M_SYN_ISSUE_MODE)

#घोषणा S_BUILD    16
#घोषणा V_BUILD(x) ((x) << S_BUILD)
#घोषणा F_BUILD    V_BUILD(1U)

#घोषणा S_COMPRESSION_ENABLE    17
#घोषणा V_COMPRESSION_ENABLE(x) ((x) << S_COMPRESSION_ENABLE)
#घोषणा F_COMPRESSION_ENABLE    V_COMPRESSION_ENABLE(1U)

#घोषणा S_NUM_LIP    18
#घोषणा M_NUM_LIP    0x3f
#घोषणा V_NUM_LIP(x) ((x) << S_NUM_LIP)
#घोषणा G_NUM_LIP(x) (((x) >> S_NUM_LIP) & M_NUM_LIP)

#घोषणा S_TCAM_PART_CNT    24
#घोषणा M_TCAM_PART_CNT    0x3
#घोषणा V_TCAM_PART_CNT(x) ((x) << S_TCAM_PART_CNT)
#घोषणा G_TCAM_PART_CNT(x) (((x) >> S_TCAM_PART_CNT) & M_TCAM_PART_CNT)

#घोषणा S_TCAM_PART_TYPE    26
#घोषणा M_TCAM_PART_TYPE    0x3
#घोषणा V_TCAM_PART_TYPE(x) ((x) << S_TCAM_PART_TYPE)
#घोषणा G_TCAM_PART_TYPE(x) (((x) >> S_TCAM_PART_TYPE) & M_TCAM_PART_TYPE)

#घोषणा S_TCAM_PART_SIZE    28
#घोषणा M_TCAM_PART_SIZE    0x3
#घोषणा V_TCAM_PART_SIZE(x) ((x) << S_TCAM_PART_SIZE)
#घोषणा G_TCAM_PART_SIZE(x) (((x) >> S_TCAM_PART_SIZE) & M_TCAM_PART_SIZE)

#घोषणा S_TCAM_PART_TYPE_HI    30
#घोषणा V_TCAM_PART_TYPE_HI(x) ((x) << S_TCAM_PART_TYPE_HI)
#घोषणा F_TCAM_PART_TYPE_HI    V_TCAM_PART_TYPE_HI(1U)

#घोषणा A_MC5_SIZE 0xc08

#घोषणा S_SIZE    0
#घोषणा M_SIZE    0x3fffff
#घोषणा V_SIZE(x) ((x) << S_SIZE)
#घोषणा G_SIZE(x) (((x) >> S_SIZE) & M_SIZE)

#घोषणा A_MC5_ROUTING_TABLE_INDEX 0xc0c

#घोषणा S_START_OF_ROUTING_TABLE    0
#घोषणा M_START_OF_ROUTING_TABLE    0x3fffff
#घोषणा V_START_OF_ROUTING_TABLE(x) ((x) << S_START_OF_ROUTING_TABLE)
#घोषणा G_START_OF_ROUTING_TABLE(x) (((x) >> S_START_OF_ROUTING_TABLE) & M_START_OF_ROUTING_TABLE)

#घोषणा A_MC5_SERVER_INDEX 0xc14

#घोषणा S_START_OF_SERVER_INDEX    0
#घोषणा M_START_OF_SERVER_INDEX    0x3fffff
#घोषणा V_START_OF_SERVER_INDEX(x) ((x) << S_START_OF_SERVER_INDEX)
#घोषणा G_START_OF_SERVER_INDEX(x) (((x) >> S_START_OF_SERVER_INDEX) & M_START_OF_SERVER_INDEX)

#घोषणा A_MC5_LIP_RAM_ADDR 0xc18

#घोषणा S_LOCAL_IP_RAM_ADDR    0
#घोषणा M_LOCAL_IP_RAM_ADDR    0x3f
#घोषणा V_LOCAL_IP_RAM_ADDR(x) ((x) << S_LOCAL_IP_RAM_ADDR)
#घोषणा G_LOCAL_IP_RAM_ADDR(x) (((x) >> S_LOCAL_IP_RAM_ADDR) & M_LOCAL_IP_RAM_ADDR)

#घोषणा S_RAM_WRITE_ENABLE    8
#घोषणा V_RAM_WRITE_ENABLE(x) ((x) << S_RAM_WRITE_ENABLE)
#घोषणा F_RAM_WRITE_ENABLE    V_RAM_WRITE_ENABLE(1U)

#घोषणा A_MC5_LIP_RAM_DATA 0xc1c
#घोषणा A_MC5_RSP_LATENCY 0xc20

#घोषणा S_SEARCH_RESPONSE_LATENCY    0
#घोषणा M_SEARCH_RESPONSE_LATENCY    0x1f
#घोषणा V_SEARCH_RESPONSE_LATENCY(x) ((x) << S_SEARCH_RESPONSE_LATENCY)
#घोषणा G_SEARCH_RESPONSE_LATENCY(x) (((x) >> S_SEARCH_RESPONSE_LATENCY) & M_SEARCH_RESPONSE_LATENCY)

#घोषणा S_LEARN_RESPONSE_LATENCY    8
#घोषणा M_LEARN_RESPONSE_LATENCY    0x1f
#घोषणा V_LEARN_RESPONSE_LATENCY(x) ((x) << S_LEARN_RESPONSE_LATENCY)
#घोषणा G_LEARN_RESPONSE_LATENCY(x) (((x) >> S_LEARN_RESPONSE_LATENCY) & M_LEARN_RESPONSE_LATENCY)

#घोषणा A_MC5_PARITY_LATENCY 0xc24

#घोषणा S_SRCHLAT    0
#घोषणा M_SRCHLAT    0x1f
#घोषणा V_SRCHLAT(x) ((x) << S_SRCHLAT)
#घोषणा G_SRCHLAT(x) (((x) >> S_SRCHLAT) & M_SRCHLAT)

#घोषणा S_PARLAT    8
#घोषणा M_PARLAT    0x1f
#घोषणा V_PARLAT(x) ((x) << S_PARLAT)
#घोषणा G_PARLAT(x) (((x) >> S_PARLAT) & M_PARLAT)

#घोषणा A_MC5_WR_LRN_VERIFY 0xc28

#घोषणा S_POVEREN    0
#घोषणा V_POVEREN(x) ((x) << S_POVEREN)
#घोषणा F_POVEREN    V_POVEREN(1U)

#घोषणा S_LRNVEREN    1
#घोषणा V_LRNVEREN(x) ((x) << S_LRNVEREN)
#घोषणा F_LRNVEREN    V_LRNVEREN(1U)

#घोषणा S_VWVEREN    2
#घोषणा V_VWVEREN(x) ((x) << S_VWVEREN)
#घोषणा F_VWVEREN    V_VWVEREN(1U)

#घोषणा A_MC5_PART_ID_INDEX 0xc2c

#घोषणा S_IDINDEX    0
#घोषणा M_IDINDEX    0xf
#घोषणा V_IDINDEX(x) ((x) << S_IDINDEX)
#घोषणा G_IDINDEX(x) (((x) >> S_IDINDEX) & M_IDINDEX)

#घोषणा A_MC5_RESET_MAX 0xc30

#घोषणा S_RSTMAX    0
#घोषणा M_RSTMAX    0x1ff
#घोषणा V_RSTMAX(x) ((x) << S_RSTMAX)
#घोषणा G_RSTMAX(x) (((x) >> S_RSTMAX) & M_RSTMAX)

#घोषणा A_MC5_INT_ENABLE 0xc40

#घोषणा S_MC5_INT_HIT_OUT_ACTIVE_REGION_ERR    0
#घोषणा V_MC5_INT_HIT_OUT_ACTIVE_REGION_ERR(x) ((x) << S_MC5_INT_HIT_OUT_ACTIVE_REGION_ERR)
#घोषणा F_MC5_INT_HIT_OUT_ACTIVE_REGION_ERR    V_MC5_INT_HIT_OUT_ACTIVE_REGION_ERR(1U)

#घोषणा S_MC5_INT_HIT_IN_ACTIVE_REGION_ERR    1
#घोषणा V_MC5_INT_HIT_IN_ACTIVE_REGION_ERR(x) ((x) << S_MC5_INT_HIT_IN_ACTIVE_REGION_ERR)
#घोषणा F_MC5_INT_HIT_IN_ACTIVE_REGION_ERR    V_MC5_INT_HIT_IN_ACTIVE_REGION_ERR(1U)

#घोषणा S_MC5_INT_HIT_IN_RT_REGION_ERR    2
#घोषणा V_MC5_INT_HIT_IN_RT_REGION_ERR(x) ((x) << S_MC5_INT_HIT_IN_RT_REGION_ERR)
#घोषणा F_MC5_INT_HIT_IN_RT_REGION_ERR    V_MC5_INT_HIT_IN_RT_REGION_ERR(1U)

#घोषणा S_MC5_INT_MISS_ERR    3
#घोषणा V_MC5_INT_MISS_ERR(x) ((x) << S_MC5_INT_MISS_ERR)
#घोषणा F_MC5_INT_MISS_ERR    V_MC5_INT_MISS_ERR(1U)

#घोषणा S_MC5_INT_LIP0_ERR    4
#घोषणा V_MC5_INT_LIP0_ERR(x) ((x) << S_MC5_INT_LIP0_ERR)
#घोषणा F_MC5_INT_LIP0_ERR    V_MC5_INT_LIP0_ERR(1U)

#घोषणा S_MC5_INT_LIP_MISS_ERR    5
#घोषणा V_MC5_INT_LIP_MISS_ERR(x) ((x) << S_MC5_INT_LIP_MISS_ERR)
#घोषणा F_MC5_INT_LIP_MISS_ERR    V_MC5_INT_LIP_MISS_ERR(1U)

#घोषणा S_MC5_INT_PARITY_ERR    6
#घोषणा V_MC5_INT_PARITY_ERR(x) ((x) << S_MC5_INT_PARITY_ERR)
#घोषणा F_MC5_INT_PARITY_ERR    V_MC5_INT_PARITY_ERR(1U)

#घोषणा S_MC5_INT_ACTIVE_REGION_FULL    7
#घोषणा V_MC5_INT_ACTIVE_REGION_FULL(x) ((x) << S_MC5_INT_ACTIVE_REGION_FULL)
#घोषणा F_MC5_INT_ACTIVE_REGION_FULL    V_MC5_INT_ACTIVE_REGION_FULL(1U)

#घोषणा S_MC5_INT_NFA_SRCH_ERR    8
#घोषणा V_MC5_INT_NFA_SRCH_ERR(x) ((x) << S_MC5_INT_NFA_SRCH_ERR)
#घोषणा F_MC5_INT_NFA_SRCH_ERR    V_MC5_INT_NFA_SRCH_ERR(1U)

#घोषणा S_MC5_INT_SYN_COOKIE    9
#घोषणा V_MC5_INT_SYN_COOKIE(x) ((x) << S_MC5_INT_SYN_COOKIE)
#घोषणा F_MC5_INT_SYN_COOKIE    V_MC5_INT_SYN_COOKIE(1U)

#घोषणा S_MC5_INT_SYN_COOKIE_BAD    10
#घोषणा V_MC5_INT_SYN_COOKIE_BAD(x) ((x) << S_MC5_INT_SYN_COOKIE_BAD)
#घोषणा F_MC5_INT_SYN_COOKIE_BAD    V_MC5_INT_SYN_COOKIE_BAD(1U)

#घोषणा S_MC5_INT_SYN_COOKIE_OFF    11
#घोषणा V_MC5_INT_SYN_COOKIE_OFF(x) ((x) << S_MC5_INT_SYN_COOKIE_OFF)
#घोषणा F_MC5_INT_SYN_COOKIE_OFF    V_MC5_INT_SYN_COOKIE_OFF(1U)

#घोषणा S_MC5_INT_UNKNOWN_CMD    15
#घोषणा V_MC5_INT_UNKNOWN_CMD(x) ((x) << S_MC5_INT_UNKNOWN_CMD)
#घोषणा F_MC5_INT_UNKNOWN_CMD    V_MC5_INT_UNKNOWN_CMD(1U)

#घोषणा S_MC5_INT_REQUESTQ_PARITY_ERR    16
#घोषणा V_MC5_INT_REQUESTQ_PARITY_ERR(x) ((x) << S_MC5_INT_REQUESTQ_PARITY_ERR)
#घोषणा F_MC5_INT_REQUESTQ_PARITY_ERR    V_MC5_INT_REQUESTQ_PARITY_ERR(1U)

#घोषणा S_MC5_INT_DISPATCHQ_PARITY_ERR    17
#घोषणा V_MC5_INT_DISPATCHQ_PARITY_ERR(x) ((x) << S_MC5_INT_DISPATCHQ_PARITY_ERR)
#घोषणा F_MC5_INT_DISPATCHQ_PARITY_ERR    V_MC5_INT_DISPATCHQ_PARITY_ERR(1U)

#घोषणा S_MC5_INT_DEL_ACT_EMPTY    18
#घोषणा V_MC5_INT_DEL_ACT_EMPTY(x) ((x) << S_MC5_INT_DEL_ACT_EMPTY)
#घोषणा F_MC5_INT_DEL_ACT_EMPTY    V_MC5_INT_DEL_ACT_EMPTY(1U)

#घोषणा A_MC5_INT_CAUSE 0xc44
#घोषणा A_MC5_INT_TID 0xc48
#घोषणा A_MC5_INT_PTID 0xc4c
#घोषणा A_MC5_DBGI_CONFIG 0xc74
#घोषणा A_MC5_DBGI_REQ_CMD 0xc78

#घोषणा S_CMDMODE    0
#घोषणा M_CMDMODE    0x7
#घोषणा V_CMDMODE(x) ((x) << S_CMDMODE)
#घोषणा G_CMDMODE(x) (((x) >> S_CMDMODE) & M_CMDMODE)

#घोषणा S_SADRSEL    4
#घोषणा V_SADRSEL(x) ((x) << S_SADRSEL)
#घोषणा F_SADRSEL    V_SADRSEL(1U)

#घोषणा S_WRITE_BURST_SIZE    22
#घोषणा M_WRITE_BURST_SIZE    0x3ff
#घोषणा V_WRITE_BURST_SIZE(x) ((x) << S_WRITE_BURST_SIZE)
#घोषणा G_WRITE_BURST_SIZE(x) (((x) >> S_WRITE_BURST_SIZE) & M_WRITE_BURST_SIZE)

#घोषणा A_MC5_DBGI_REQ_ADDR0 0xc7c
#घोषणा A_MC5_DBGI_REQ_ADDR1 0xc80
#घोषणा A_MC5_DBGI_REQ_ADDR2 0xc84
#घोषणा A_MC5_DBGI_REQ_DATA0 0xc88
#घोषणा A_MC5_DBGI_REQ_DATA1 0xc8c
#घोषणा A_MC5_DBGI_REQ_DATA2 0xc90
#घोषणा A_MC5_DBGI_REQ_DATA3 0xc94
#घोषणा A_MC5_DBGI_REQ_DATA4 0xc98
#घोषणा A_MC5_DBGI_REQ_MASK0 0xc9c
#घोषणा A_MC5_DBGI_REQ_MASK1 0xca0
#घोषणा A_MC5_DBGI_REQ_MASK2 0xca4
#घोषणा A_MC5_DBGI_REQ_MASK3 0xca8
#घोषणा A_MC5_DBGI_REQ_MASK4 0xcac
#घोषणा A_MC5_DBGI_RSP_STATUS 0xcb0

#घोषणा S_DBGI_RSP_VALID    0
#घोषणा V_DBGI_RSP_VALID(x) ((x) << S_DBGI_RSP_VALID)
#घोषणा F_DBGI_RSP_VALID    V_DBGI_RSP_VALID(1U)

#घोषणा S_DBGI_RSP_HIT    1
#घोषणा V_DBGI_RSP_HIT(x) ((x) << S_DBGI_RSP_HIT)
#घोषणा F_DBGI_RSP_HIT    V_DBGI_RSP_HIT(1U)

#घोषणा S_DBGI_RSP_ERR    2
#घोषणा V_DBGI_RSP_ERR(x) ((x) << S_DBGI_RSP_ERR)
#घोषणा F_DBGI_RSP_ERR    V_DBGI_RSP_ERR(1U)

#घोषणा S_DBGI_RSP_ERR_REASON    8
#घोषणा M_DBGI_RSP_ERR_REASON    0x7
#घोषणा V_DBGI_RSP_ERR_REASON(x) ((x) << S_DBGI_RSP_ERR_REASON)
#घोषणा G_DBGI_RSP_ERR_REASON(x) (((x) >> S_DBGI_RSP_ERR_REASON) & M_DBGI_RSP_ERR_REASON)

#घोषणा A_MC5_DBGI_RSP_DATA0 0xcb4
#घोषणा A_MC5_DBGI_RSP_DATA1 0xcb8
#घोषणा A_MC5_DBGI_RSP_DATA2 0xcbc
#घोषणा A_MC5_DBGI_RSP_DATA3 0xcc0
#घोषणा A_MC5_DBGI_RSP_DATA4 0xcc4
#घोषणा A_MC5_DBGI_RSP_LAST_CMD 0xcc8
#घोषणा A_MC5_POPEN_DATA_WR_CMD 0xccc
#घोषणा A_MC5_POPEN_MASK_WR_CMD 0xcd0
#घोषणा A_MC5_AOPEN_SRCH_CMD 0xcd4
#घोषणा A_MC5_AOPEN_LRN_CMD 0xcd8
#घोषणा A_MC5_SYN_SRCH_CMD 0xcdc
#घोषणा A_MC5_SYN_LRN_CMD 0xce0
#घोषणा A_MC5_ACK_SRCH_CMD 0xce4
#घोषणा A_MC5_ACK_LRN_CMD 0xce8
#घोषणा A_MC5_ILOOKUP_CMD 0xcec
#घोषणा A_MC5_ELOOKUP_CMD 0xcf0
#घोषणा A_MC5_DATA_WRITE_CMD 0xcf4
#घोषणा A_MC5_DATA_READ_CMD 0xcf8
#घोषणा A_MC5_MASK_WRITE_CMD 0xcfc

/* PCICFG रेजिस्टरs */
#घोषणा A_PCICFG_PM_CSR 0x44
#घोषणा A_PCICFG_VPD_ADDR 0x4a

#घोषणा S_VPD_ADDR    0
#घोषणा M_VPD_ADDR    0x7fff
#घोषणा V_VPD_ADDR(x) ((x) << S_VPD_ADDR)
#घोषणा G_VPD_ADDR(x) (((x) >> S_VPD_ADDR) & M_VPD_ADDR)

#घोषणा S_VPD_OP_FLAG    15
#घोषणा V_VPD_OP_FLAG(x) ((x) << S_VPD_OP_FLAG)
#घोषणा F_VPD_OP_FLAG    V_VPD_OP_FLAG(1U)

#घोषणा A_PCICFG_VPD_DATA 0x4c
#घोषणा A_PCICFG_PCIX_CMD 0x60
#घोषणा A_PCICFG_INTR_ENABLE 0xf4

#घोषणा S_MASTER_PARITY_ERR    0
#घोषणा V_MASTER_PARITY_ERR(x) ((x) << S_MASTER_PARITY_ERR)
#घोषणा F_MASTER_PARITY_ERR    V_MASTER_PARITY_ERR(1U)

#घोषणा S_SIG_TARGET_ABORT    1
#घोषणा V_SIG_TARGET_ABORT(x) ((x) << S_SIG_TARGET_ABORT)
#घोषणा F_SIG_TARGET_ABORT    V_SIG_TARGET_ABORT(1U)

#घोषणा S_RCV_TARGET_ABORT    2
#घोषणा V_RCV_TARGET_ABORT(x) ((x) << S_RCV_TARGET_ABORT)
#घोषणा F_RCV_TARGET_ABORT    V_RCV_TARGET_ABORT(1U)

#घोषणा S_RCV_MASTER_ABORT    3
#घोषणा V_RCV_MASTER_ABORT(x) ((x) << S_RCV_MASTER_ABORT)
#घोषणा F_RCV_MASTER_ABORT    V_RCV_MASTER_ABORT(1U)

#घोषणा S_SIG_SYS_ERR    4
#घोषणा V_SIG_SYS_ERR(x) ((x) << S_SIG_SYS_ERR)
#घोषणा F_SIG_SYS_ERR    V_SIG_SYS_ERR(1U)

#घोषणा S_DET_PARITY_ERR    5
#घोषणा V_DET_PARITY_ERR(x) ((x) << S_DET_PARITY_ERR)
#घोषणा F_DET_PARITY_ERR    V_DET_PARITY_ERR(1U)

#घोषणा S_PIO_PARITY_ERR    6
#घोषणा V_PIO_PARITY_ERR(x) ((x) << S_PIO_PARITY_ERR)
#घोषणा F_PIO_PARITY_ERR    V_PIO_PARITY_ERR(1U)

#घोषणा S_WF_PARITY_ERR    7
#घोषणा V_WF_PARITY_ERR(x) ((x) << S_WF_PARITY_ERR)
#घोषणा F_WF_PARITY_ERR    V_WF_PARITY_ERR(1U)

#घोषणा S_RF_PARITY_ERR    8
#घोषणा M_RF_PARITY_ERR    0x3
#घोषणा V_RF_PARITY_ERR(x) ((x) << S_RF_PARITY_ERR)
#घोषणा G_RF_PARITY_ERR(x) (((x) >> S_RF_PARITY_ERR) & M_RF_PARITY_ERR)

#घोषणा S_CF_PARITY_ERR    10
#घोषणा M_CF_PARITY_ERR    0x3
#घोषणा V_CF_PARITY_ERR(x) ((x) << S_CF_PARITY_ERR)
#घोषणा G_CF_PARITY_ERR(x) (((x) >> S_CF_PARITY_ERR) & M_CF_PARITY_ERR)

#घोषणा A_PCICFG_INTR_CAUSE 0xf8
#घोषणा A_PCICFG_MODE 0xfc

#घोषणा S_PCI_MODE_64BIT    0
#घोषणा V_PCI_MODE_64BIT(x) ((x) << S_PCI_MODE_64BIT)
#घोषणा F_PCI_MODE_64BIT    V_PCI_MODE_64BIT(1U)

#घोषणा S_PCI_MODE_66MHZ    1
#घोषणा V_PCI_MODE_66MHZ(x) ((x) << S_PCI_MODE_66MHZ)
#घोषणा F_PCI_MODE_66MHZ    V_PCI_MODE_66MHZ(1U)

#घोषणा S_PCI_MODE_PCIX_INITPAT    2
#घोषणा M_PCI_MODE_PCIX_INITPAT    0x7
#घोषणा V_PCI_MODE_PCIX_INITPAT(x) ((x) << S_PCI_MODE_PCIX_INITPAT)
#घोषणा G_PCI_MODE_PCIX_INITPAT(x) (((x) >> S_PCI_MODE_PCIX_INITPAT) & M_PCI_MODE_PCIX_INITPAT)

#घोषणा S_PCI_MODE_PCIX    5
#घोषणा V_PCI_MODE_PCIX(x) ((x) << S_PCI_MODE_PCIX)
#घोषणा F_PCI_MODE_PCIX    V_PCI_MODE_PCIX(1U)

#घोषणा S_PCI_MODE_CLK    6
#घोषणा M_PCI_MODE_CLK    0x3
#घोषणा V_PCI_MODE_CLK(x) ((x) << S_PCI_MODE_CLK)
#घोषणा G_PCI_MODE_CLK(x) (((x) >> S_PCI_MODE_CLK) & M_PCI_MODE_CLK)

#पूर्ण_अगर /* _CXGB_REGS_H_ */
