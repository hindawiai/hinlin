<शैली गुरु>
/*****************************************************************************
 *                                                                           *
 * File: elmer0.h                                                            *
 * $Revision: 1.6 $                                                          *
 * $Date: 2005/06/21 22:49:43 $                                              *
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

#अगर_अघोषित _CXGB_ELMER0_H_
#घोषणा _CXGB_ELMER0_H_

/* ELMER0 flavors */
क्रमागत अणु
	ELMER0_XC2S300E_6FT256_C,
	ELMER0_XC2S100E_6TQ144_C
पूर्ण;

/* ELMER0 रेजिस्टरs */
#घोषणा A_ELMER0_VERSION	0x100000
#घोषणा A_ELMER0_PHY_CFG	0x100004
#घोषणा A_ELMER0_INT_ENABLE	0x100008
#घोषणा A_ELMER0_INT_CAUSE	0x10000c
#घोषणा A_ELMER0_GPI_CFG	0x100010
#घोषणा A_ELMER0_GPI_STAT	0x100014
#घोषणा A_ELMER0_GPO		0x100018
#घोषणा A_ELMER0_PORT0_MI1_CFG	0x400000

#घोषणा S_MI1_MDI_ENABLE    0
#घोषणा V_MI1_MDI_ENABLE(x) ((x) << S_MI1_MDI_ENABLE)
#घोषणा F_MI1_MDI_ENABLE    V_MI1_MDI_ENABLE(1U)

#घोषणा S_MI1_MDI_INVERT    1
#घोषणा V_MI1_MDI_INVERT(x) ((x) << S_MI1_MDI_INVERT)
#घोषणा F_MI1_MDI_INVERT    V_MI1_MDI_INVERT(1U)

#घोषणा S_MI1_PREAMBLE_ENABLE    2
#घोषणा V_MI1_PREAMBLE_ENABLE(x) ((x) << S_MI1_PREAMBLE_ENABLE)
#घोषणा F_MI1_PREAMBLE_ENABLE    V_MI1_PREAMBLE_ENABLE(1U)

#घोषणा S_MI1_SOF    3
#घोषणा M_MI1_SOF    0x3
#घोषणा V_MI1_SOF(x) ((x) << S_MI1_SOF)
#घोषणा G_MI1_SOF(x) (((x) >> S_MI1_SOF) & M_MI1_SOF)

#घोषणा S_MI1_CLK_DIV    5
#घोषणा M_MI1_CLK_DIV    0xff
#घोषणा V_MI1_CLK_DIV(x) ((x) << S_MI1_CLK_DIV)
#घोषणा G_MI1_CLK_DIV(x) (((x) >> S_MI1_CLK_DIV) & M_MI1_CLK_DIV)

#घोषणा A_ELMER0_PORT0_MI1_ADDR 0x400004

#घोषणा S_MI1_REG_ADDR    0
#घोषणा M_MI1_REG_ADDR    0x1f
#घोषणा V_MI1_REG_ADDR(x) ((x) << S_MI1_REG_ADDR)
#घोषणा G_MI1_REG_ADDR(x) (((x) >> S_MI1_REG_ADDR) & M_MI1_REG_ADDR)

#घोषणा S_MI1_PHY_ADDR    5
#घोषणा M_MI1_PHY_ADDR    0x1f
#घोषणा V_MI1_PHY_ADDR(x) ((x) << S_MI1_PHY_ADDR)
#घोषणा G_MI1_PHY_ADDR(x) (((x) >> S_MI1_PHY_ADDR) & M_MI1_PHY_ADDR)

#घोषणा A_ELMER0_PORT0_MI1_DATA 0x400008

#घोषणा S_MI1_DATA    0
#घोषणा M_MI1_DATA    0xffff
#घोषणा V_MI1_DATA(x) ((x) << S_MI1_DATA)
#घोषणा G_MI1_DATA(x) (((x) >> S_MI1_DATA) & M_MI1_DATA)

#घोषणा A_ELMER0_PORT0_MI1_OP 0x40000c

#घोषणा S_MI1_OP    0
#घोषणा M_MI1_OP    0x3
#घोषणा V_MI1_OP(x) ((x) << S_MI1_OP)
#घोषणा G_MI1_OP(x) (((x) >> S_MI1_OP) & M_MI1_OP)

#घोषणा S_MI1_ADDR_AUTOINC    2
#घोषणा V_MI1_ADDR_AUTOINC(x) ((x) << S_MI1_ADDR_AUTOINC)
#घोषणा F_MI1_ADDR_AUTOINC    V_MI1_ADDR_AUTOINC(1U)

#घोषणा S_MI1_OP_BUSY    31
#घोषणा V_MI1_OP_BUSY(x) ((x) << S_MI1_OP_BUSY)
#घोषणा F_MI1_OP_BUSY    V_MI1_OP_BUSY(1U)

#घोषणा A_ELMER0_PORT1_MI1_CFG	0x500000
#घोषणा A_ELMER0_PORT1_MI1_ADDR	0x500004
#घोषणा A_ELMER0_PORT1_MI1_DATA	0x500008
#घोषणा A_ELMER0_PORT1_MI1_OP	0x50000c
#घोषणा A_ELMER0_PORT2_MI1_CFG	0x600000
#घोषणा A_ELMER0_PORT2_MI1_ADDR	0x600004
#घोषणा A_ELMER0_PORT2_MI1_DATA	0x600008
#घोषणा A_ELMER0_PORT2_MI1_OP	0x60000c
#घोषणा A_ELMER0_PORT3_MI1_CFG	0x700000
#घोषणा A_ELMER0_PORT3_MI1_ADDR	0x700004
#घोषणा A_ELMER0_PORT3_MI1_DATA	0x700008
#घोषणा A_ELMER0_PORT3_MI1_OP	0x70000c

/* Simple bit definition क्रम GPI and GP0 रेजिस्टरs. */
#घोषणा     ELMER0_GP_BIT0              0x0001
#घोषणा     ELMER0_GP_BIT1              0x0002
#घोषणा     ELMER0_GP_BIT2              0x0004
#घोषणा     ELMER0_GP_BIT3              0x0008
#घोषणा     ELMER0_GP_BIT4              0x0010
#घोषणा     ELMER0_GP_BIT5              0x0020
#घोषणा     ELMER0_GP_BIT6              0x0040
#घोषणा     ELMER0_GP_BIT7              0x0080
#घोषणा     ELMER0_GP_BIT8              0x0100
#घोषणा     ELMER0_GP_BIT9              0x0200
#घोषणा     ELMER0_GP_BIT10             0x0400
#घोषणा     ELMER0_GP_BIT11             0x0800
#घोषणा     ELMER0_GP_BIT12             0x1000
#घोषणा     ELMER0_GP_BIT13             0x2000
#घोषणा     ELMER0_GP_BIT14             0x4000
#घोषणा     ELMER0_GP_BIT15             0x8000
#घोषणा     ELMER0_GP_BIT16             0x10000
#घोषणा     ELMER0_GP_BIT17             0x20000
#घोषणा     ELMER0_GP_BIT18             0x40000
#घोषणा     ELMER0_GP_BIT19             0x80000

#घोषणा MI1_OP_सूचीECT_WRITE 1
#घोषणा MI1_OP_सूचीECT_READ  2

#घोषणा MI1_OP_INसूचीECT_ADDRESS  0
#घोषणा MI1_OP_INसूचीECT_WRITE    1
#घोषणा MI1_OP_INसूचीECT_READ_INC 2
#घोषणा MI1_OP_INसूचीECT_READ     3

#पूर्ण_अगर /* _CXGB_ELMER0_H_ */

