<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*  *********************************************************************
    *  SB1250 Board Support Package
    *
    *  MAC स्थिरants and macros			File: sb1250_mac.h
    *
    *  This module contains स्थिरants and macros क्रम the SB1250's
    *  ethernet controllers.
    *
    *  SB1250 specअगरication level:  User's manual 1/02/02
    *
    *********************************************************************
    *
    *  Copyright 2000,2001,2002,2003
    *  Broadcom Corporation. All rights reserved.
    *
    ********************************************************************* */


#अगर_अघोषित _SB1250_MAC_H
#घोषणा _SB1250_MAC_H

#समावेश <यंत्र/sibyte/sb1250_defs.h>

/*  *********************************************************************
    *  Ethernet MAC Registers
    ********************************************************************* */

/*
 * MAC Configuration Register (Table 9-13)
 * Register: MAC_CFG_0
 * Register: MAC_CFG_1
 * Register: MAC_CFG_2
 */


#घोषणा M_MAC_RESERVED0		    _SB_MAKEMASK1(0)
#घोषणा M_MAC_TX_HOLD_SOP_EN	    _SB_MAKEMASK1(1)
#घोषणा M_MAC_RETRY_EN		    _SB_MAKEMASK1(2)
#घोषणा M_MAC_RET_DRPREQ_EN	    _SB_MAKEMASK1(3)
#घोषणा M_MAC_RET_UFL_EN	    _SB_MAKEMASK1(4)
#घोषणा M_MAC_BURST_EN		    _SB_MAKEMASK1(5)

#घोषणा S_MAC_TX_PAUSE		    _SB_MAKE64(6)
#घोषणा M_MAC_TX_PAUSE_CNT	    _SB_MAKEMASK(3, S_MAC_TX_PAUSE)
#घोषणा V_MAC_TX_PAUSE_CNT(x)	    _SB_MAKEVALUE(x, S_MAC_TX_PAUSE)

#घोषणा K_MAC_TX_PAUSE_CNT_512	    0
#घोषणा K_MAC_TX_PAUSE_CNT_1K	    1
#घोषणा K_MAC_TX_PAUSE_CNT_2K	    2
#घोषणा K_MAC_TX_PAUSE_CNT_4K	    3
#घोषणा K_MAC_TX_PAUSE_CNT_8K	    4
#घोषणा K_MAC_TX_PAUSE_CNT_16K	    5
#घोषणा K_MAC_TX_PAUSE_CNT_32K	    6
#घोषणा K_MAC_TX_PAUSE_CNT_64K	    7

#घोषणा V_MAC_TX_PAUSE_CNT_512	    V_MAC_TX_PAUSE_CNT(K_MAC_TX_PAUSE_CNT_512)
#घोषणा V_MAC_TX_PAUSE_CNT_1K	    V_MAC_TX_PAUSE_CNT(K_MAC_TX_PAUSE_CNT_1K)
#घोषणा V_MAC_TX_PAUSE_CNT_2K	    V_MAC_TX_PAUSE_CNT(K_MAC_TX_PAUSE_CNT_2K)
#घोषणा V_MAC_TX_PAUSE_CNT_4K	    V_MAC_TX_PAUSE_CNT(K_MAC_TX_PAUSE_CNT_4K)
#घोषणा V_MAC_TX_PAUSE_CNT_8K	    V_MAC_TX_PAUSE_CNT(K_MAC_TX_PAUSE_CNT_8K)
#घोषणा V_MAC_TX_PAUSE_CNT_16K	    V_MAC_TX_PAUSE_CNT(K_MAC_TX_PAUSE_CNT_16K)
#घोषणा V_MAC_TX_PAUSE_CNT_32K	    V_MAC_TX_PAUSE_CNT(K_MAC_TX_PAUSE_CNT_32K)
#घोषणा V_MAC_TX_PAUSE_CNT_64K	    V_MAC_TX_PAUSE_CNT(K_MAC_TX_PAUSE_CNT_64K)

#घोषणा M_MAC_RESERVED1		    _SB_MAKEMASK(8, 9)

#घोषणा M_MAC_AP_STAT_EN	    _SB_MAKEMASK1(17)

#अगर SIBYTE_HDR_FEATURE_CHIP(1480)
#घोषणा M_MAC_TIMESTAMP		    _SB_MAKEMASK1(18)
#पूर्ण_अगर
#घोषणा M_MAC_DRP_ERRPKT_EN	    _SB_MAKEMASK1(19)
#घोषणा M_MAC_DRP_FCSERRPKT_EN	    _SB_MAKEMASK1(20)
#घोषणा M_MAC_DRP_CODEERRPKT_EN	    _SB_MAKEMASK1(21)
#घोषणा M_MAC_DRP_DRBLERRPKT_EN	    _SB_MAKEMASK1(22)
#घोषणा M_MAC_DRP_RNTPKT_EN	    _SB_MAKEMASK1(23)
#घोषणा M_MAC_DRP_OSZPKT_EN	    _SB_MAKEMASK1(24)
#घोषणा M_MAC_DRP_LENERRPKT_EN	    _SB_MAKEMASK1(25)

#घोषणा M_MAC_RESERVED3		    _SB_MAKEMASK(6, 26)

#घोषणा M_MAC_BYPASS_SEL	    _SB_MAKEMASK1(32)
#घोषणा M_MAC_HDX_EN		    _SB_MAKEMASK1(33)

#घोषणा S_MAC_SPEED_SEL		    _SB_MAKE64(34)
#घोषणा M_MAC_SPEED_SEL		    _SB_MAKEMASK(2, S_MAC_SPEED_SEL)
#घोषणा V_MAC_SPEED_SEL(x)	    _SB_MAKEVALUE(x, S_MAC_SPEED_SEL)
#घोषणा G_MAC_SPEED_SEL(x)	    _SB_GETVALUE(x, S_MAC_SPEED_SEL, M_MAC_SPEED_SEL)

#घोषणा K_MAC_SPEED_SEL_10MBPS	    0
#घोषणा K_MAC_SPEED_SEL_100MBPS	    1
#घोषणा K_MAC_SPEED_SEL_1000MBPS    2
#घोषणा K_MAC_SPEED_SEL_RESERVED    3

#घोषणा V_MAC_SPEED_SEL_10MBPS	    V_MAC_SPEED_SEL(K_MAC_SPEED_SEL_10MBPS)
#घोषणा V_MAC_SPEED_SEL_100MBPS	    V_MAC_SPEED_SEL(K_MAC_SPEED_SEL_100MBPS)
#घोषणा V_MAC_SPEED_SEL_1000MBPS    V_MAC_SPEED_SEL(K_MAC_SPEED_SEL_1000MBPS)
#घोषणा V_MAC_SPEED_SEL_RESERVED    V_MAC_SPEED_SEL(K_MAC_SPEED_SEL_RESERVED)

#घोषणा M_MAC_TX_CLK_EDGE_SEL	    _SB_MAKEMASK1(36)
#घोषणा M_MAC_LOOPBACK_SEL	    _SB_MAKEMASK1(37)
#घोषणा M_MAC_FAST_SYNC		    _SB_MAKEMASK1(38)
#घोषणा M_MAC_SS_EN		    _SB_MAKEMASK1(39)

#घोषणा S_MAC_BYPASS_CFG	    _SB_MAKE64(40)
#घोषणा M_MAC_BYPASS_CFG	    _SB_MAKEMASK(2, S_MAC_BYPASS_CFG)
#घोषणा V_MAC_BYPASS_CFG(x)	    _SB_MAKEVALUE(x, S_MAC_BYPASS_CFG)
#घोषणा G_MAC_BYPASS_CFG(x)	    _SB_GETVALUE(x, S_MAC_BYPASS_CFG, M_MAC_BYPASS_CFG)

#घोषणा K_MAC_BYPASS_GMII	    0
#घोषणा K_MAC_BYPASS_ENCODED	    1
#घोषणा K_MAC_BYPASS_SOP	    2
#घोषणा K_MAC_BYPASS_EOP	    3

#घोषणा M_MAC_BYPASS_16		    _SB_MAKEMASK1(42)
#घोषणा M_MAC_BYPASS_FCS_CHK	    _SB_MAKEMASK1(43)

#अगर SIBYTE_HDR_FEATURE(1250, PASS2) || SIBYTE_HDR_FEATURE(112x, PASS1) || SIBYTE_HDR_FEATURE_CHIP(1480)
#घोषणा M_MAC_RX_CH_SEL_MSB	    _SB_MAKEMASK1(44)
#पूर्ण_अगर /* 1250 PASS2 || 112x PASS1 || 1480*/

#अगर SIBYTE_HDR_FEATURE(1250, PASS3) || SIBYTE_HDR_FEATURE(112x, PASS1) || SIBYTE_HDR_FEATURE_CHIP(1480)
#घोषणा M_MAC_SPLIT_CH_SEL	    _SB_MAKEMASK1(45)
#पूर्ण_अगर /* 1250 PASS3 || 112x PASS1 || 1480 */

#घोषणा S_MAC_BYPASS_IFG	    _SB_MAKE64(46)
#घोषणा M_MAC_BYPASS_IFG	    _SB_MAKEMASK(8, S_MAC_BYPASS_IFG)
#घोषणा V_MAC_BYPASS_IFG(x)	    _SB_MAKEVALUE(x, S_MAC_BYPASS_IFG)
#घोषणा G_MAC_BYPASS_IFG(x)	    _SB_GETVALUE(x, S_MAC_BYPASS_IFG, M_MAC_BYPASS_IFG)

#घोषणा K_MAC_FC_CMD_DISABLED	    0
#घोषणा K_MAC_FC_CMD_ENABLED	    1
#घोषणा K_MAC_FC_CMD_ENAB_FALSECARR 2

#घोषणा V_MAC_FC_CMD_DISABLED	    V_MAC_FC_CMD(K_MAC_FC_CMD_DISABLED)
#घोषणा V_MAC_FC_CMD_ENABLED	    V_MAC_FC_CMD(K_MAC_FC_CMD_ENABLED)
#घोषणा V_MAC_FC_CMD_ENAB_FALSECARR V_MAC_FC_CMD(K_MAC_FC_CMD_ENAB_FALSECARR)

#घोषणा M_MAC_FC_SEL		    _SB_MAKEMASK1(54)

#घोषणा S_MAC_FC_CMD		    _SB_MAKE64(55)
#घोषणा M_MAC_FC_CMD		    _SB_MAKEMASK(2, S_MAC_FC_CMD)
#घोषणा V_MAC_FC_CMD(x)		    _SB_MAKEVALUE(x, S_MAC_FC_CMD)
#घोषणा G_MAC_FC_CMD(x)		    _SB_GETVALUE(x, S_MAC_FC_CMD, M_MAC_FC_CMD)

#घोषणा S_MAC_RX_CH_SEL		    _SB_MAKE64(57)
#घोषणा M_MAC_RX_CH_SEL		    _SB_MAKEMASK(7, S_MAC_RX_CH_SEL)
#घोषणा V_MAC_RX_CH_SEL(x)	    _SB_MAKEVALUE(x, S_MAC_RX_CH_SEL)
#घोषणा G_MAC_RX_CH_SEL(x)	    _SB_GETVALUE(x, S_MAC_RX_CH_SEL, M_MAC_RX_CH_SEL)


/*
 * MAC Enable Registers
 * Register: MAC_ENABLE_0
 * Register: MAC_ENABLE_1
 * Register: MAC_ENABLE_2
 */

#घोषणा M_MAC_RXDMA_EN0		    _SB_MAKEMASK1(0)
#घोषणा M_MAC_RXDMA_EN1		    _SB_MAKEMASK1(1)
#घोषणा M_MAC_TXDMA_EN0		    _SB_MAKEMASK1(4)
#घोषणा M_MAC_TXDMA_EN1		    _SB_MAKEMASK1(5)

#घोषणा M_MAC_PORT_RESET	    _SB_MAKEMASK1(8)

#अगर (SIBYTE_HDR_FEATURE_CHIP(1250) || SIBYTE_HDR_FEATURE_CHIP(112x))
#घोषणा M_MAC_RX_ENABLE		    _SB_MAKEMASK1(10)
#घोषणा M_MAC_TX_ENABLE		    _SB_MAKEMASK1(11)
#घोषणा M_MAC_BYP_RX_ENABLE	    _SB_MAKEMASK1(12)
#घोषणा M_MAC_BYP_TX_ENABLE	    _SB_MAKEMASK1(13)
#पूर्ण_अगर

/*
 * MAC reset inक्रमmation रेजिस्टर (1280/1255)
 */
#अगर SIBYTE_HDR_FEATURE_CHIP(1480)
#घोषणा M_MAC_RX_CH0_PAUSE_ON	_SB_MAKEMASK1(8)
#घोषणा M_MAC_RX_CH1_PAUSE_ON	_SB_MAKEMASK1(16)
#घोषणा M_MAC_TX_CH0_PAUSE_ON	_SB_MAKEMASK1(24)
#घोषणा M_MAC_TX_CH1_PAUSE_ON	_SB_MAKEMASK1(32)
#पूर्ण_अगर

/*
 * MAC DMA Control Register
 * Register: MAC_TXD_CTL_0
 * Register: MAC_TXD_CTL_1
 * Register: MAC_TXD_CTL_2
 */

#घोषणा S_MAC_TXD_WEIGHT0	    _SB_MAKE64(0)
#घोषणा M_MAC_TXD_WEIGHT0	    _SB_MAKEMASK(4, S_MAC_TXD_WEIGHT0)
#घोषणा V_MAC_TXD_WEIGHT0(x)	    _SB_MAKEVALUE(x, S_MAC_TXD_WEIGHT0)
#घोषणा G_MAC_TXD_WEIGHT0(x)	    _SB_GETVALUE(x, S_MAC_TXD_WEIGHT0, M_MAC_TXD_WEIGHT0)

#घोषणा S_MAC_TXD_WEIGHT1	    _SB_MAKE64(4)
#घोषणा M_MAC_TXD_WEIGHT1	    _SB_MAKEMASK(4, S_MAC_TXD_WEIGHT1)
#घोषणा V_MAC_TXD_WEIGHT1(x)	    _SB_MAKEVALUE(x, S_MAC_TXD_WEIGHT1)
#घोषणा G_MAC_TXD_WEIGHT1(x)	    _SB_GETVALUE(x, S_MAC_TXD_WEIGHT1, M_MAC_TXD_WEIGHT1)

/*
 * MAC Fअगरo Threshold रेजिस्टरs (Table 9-14)
 * Register: MAC_THRSH_CFG_0
 * Register: MAC_THRSH_CFG_1
 * Register: MAC_THRSH_CFG_2
 */

#घोषणा S_MAC_TX_WR_THRSH	    _SB_MAKE64(0)
#अगर SIBYTE_HDR_FEATURE_UP_TO(1250, PASS1)
/* XXX: Can't enable, as it has the same name as a pass2+ define below.	 */
/* #घोषणा M_MAC_TX_WR_THRSH	       _SB_MAKEMASK(6, S_MAC_TX_WR_THRSH) */
#पूर्ण_अगर /* up to 1250 PASS1 */
#अगर SIBYTE_HDR_FEATURE(1250, PASS2) || SIBYTE_HDR_FEATURE(112x, PASS1) || SIBYTE_HDR_FEATURE_CHIP(1480)
#घोषणा M_MAC_TX_WR_THRSH	    _SB_MAKEMASK(7, S_MAC_TX_WR_THRSH)
#पूर्ण_अगर /* 1250 PASS2 || 112x PASS1 || 1480 */
#घोषणा V_MAC_TX_WR_THRSH(x)	    _SB_MAKEVALUE(x, S_MAC_TX_WR_THRSH)
#घोषणा G_MAC_TX_WR_THRSH(x)	    _SB_GETVALUE(x, S_MAC_TX_WR_THRSH, M_MAC_TX_WR_THRSH)

#घोषणा S_MAC_TX_RD_THRSH	    _SB_MAKE64(8)
#अगर SIBYTE_HDR_FEATURE_UP_TO(1250, PASS1)
/* XXX: Can't enable, as it has the same name as a pass2+ define below.	 */
/* #घोषणा M_MAC_TX_RD_THRSH	       _SB_MAKEMASK(6, S_MAC_TX_RD_THRSH) */
#पूर्ण_अगर /* up to 1250 PASS1 */
#अगर SIBYTE_HDR_FEATURE(1250, PASS2) || SIBYTE_HDR_FEATURE(112x, PASS1) || SIBYTE_HDR_FEATURE_CHIP(1480)
#घोषणा M_MAC_TX_RD_THRSH	    _SB_MAKEMASK(7, S_MAC_TX_RD_THRSH)
#पूर्ण_अगर /* 1250 PASS2 || 112x PASS1 || 1480 */
#घोषणा V_MAC_TX_RD_THRSH(x)	    _SB_MAKEVALUE(x, S_MAC_TX_RD_THRSH)
#घोषणा G_MAC_TX_RD_THRSH(x)	    _SB_GETVALUE(x, S_MAC_TX_RD_THRSH, M_MAC_TX_RD_THRSH)

#घोषणा S_MAC_TX_RL_THRSH	    _SB_MAKE64(16)
#घोषणा M_MAC_TX_RL_THRSH	    _SB_MAKEMASK(4, S_MAC_TX_RL_THRSH)
#घोषणा V_MAC_TX_RL_THRSH(x)	    _SB_MAKEVALUE(x, S_MAC_TX_RL_THRSH)
#घोषणा G_MAC_TX_RL_THRSH(x)	    _SB_GETVALUE(x, S_MAC_TX_RL_THRSH, M_MAC_TX_RL_THRSH)

#घोषणा S_MAC_RX_PL_THRSH	    _SB_MAKE64(24)
#घोषणा M_MAC_RX_PL_THRSH	    _SB_MAKEMASK(6, S_MAC_RX_PL_THRSH)
#घोषणा V_MAC_RX_PL_THRSH(x)	    _SB_MAKEVALUE(x, S_MAC_RX_PL_THRSH)
#घोषणा G_MAC_RX_PL_THRSH(x)	    _SB_GETVALUE(x, S_MAC_RX_PL_THRSH, M_MAC_RX_PL_THRSH)

#घोषणा S_MAC_RX_RD_THRSH	    _SB_MAKE64(32)
#घोषणा M_MAC_RX_RD_THRSH	    _SB_MAKEMASK(6, S_MAC_RX_RD_THRSH)
#घोषणा V_MAC_RX_RD_THRSH(x)	    _SB_MAKEVALUE(x, S_MAC_RX_RD_THRSH)
#घोषणा G_MAC_RX_RD_THRSH(x)	    _SB_GETVALUE(x, S_MAC_RX_RD_THRSH, M_MAC_RX_RD_THRSH)

#घोषणा S_MAC_RX_RL_THRSH	    _SB_MAKE64(40)
#घोषणा M_MAC_RX_RL_THRSH	    _SB_MAKEMASK(6, S_MAC_RX_RL_THRSH)
#घोषणा V_MAC_RX_RL_THRSH(x)	    _SB_MAKEVALUE(x, S_MAC_RX_RL_THRSH)
#घोषणा G_MAC_RX_RL_THRSH(x)	    _SB_GETVALUE(x, S_MAC_RX_RL_THRSH, M_MAC_RX_RL_THRSH)

#अगर SIBYTE_HDR_FEATURE(1250, PASS2) || SIBYTE_HDR_FEATURE(112x, PASS1) || SIBYTE_HDR_FEATURE_CHIP(1480)
#घोषणा S_MAC_ENC_FC_THRSH	     _SB_MAKE64(56)
#घोषणा M_MAC_ENC_FC_THRSH	     _SB_MAKEMASK(6, S_MAC_ENC_FC_THRSH)
#घोषणा V_MAC_ENC_FC_THRSH(x)	     _SB_MAKEVALUE(x, S_MAC_ENC_FC_THRSH)
#घोषणा G_MAC_ENC_FC_THRSH(x)	     _SB_GETVALUE(x, S_MAC_ENC_FC_THRSH, M_MAC_ENC_FC_THRSH)
#पूर्ण_अगर /* 1250 PASS2 || 112x PASS1 || 1480 */

/*
 * MAC Frame Configuration Registers (Table 9-15)
 * Register: MAC_FRAME_CFG_0
 * Register: MAC_FRAME_CFG_1
 * Register: MAC_FRAME_CFG_2
 */

/* XXXCGD: ??? Unused in pass2? */
#घोषणा S_MAC_IFG_RX		    _SB_MAKE64(0)
#घोषणा M_MAC_IFG_RX		    _SB_MAKEMASK(6, S_MAC_IFG_RX)
#घोषणा V_MAC_IFG_RX(x)		    _SB_MAKEVALUE(x, S_MAC_IFG_RX)
#घोषणा G_MAC_IFG_RX(x)		    _SB_GETVALUE(x, S_MAC_IFG_RX, M_MAC_IFG_RX)

#अगर SIBYTE_HDR_FEATURE(1250, PASS3) || SIBYTE_HDR_FEATURE(112x, PASS1) || SIBYTE_HDR_FEATURE_CHIP(1480)
#घोषणा S_MAC_PRE_LEN		    _SB_MAKE64(0)
#घोषणा M_MAC_PRE_LEN		    _SB_MAKEMASK(6, S_MAC_PRE_LEN)
#घोषणा V_MAC_PRE_LEN(x)	    _SB_MAKEVALUE(x, S_MAC_PRE_LEN)
#घोषणा G_MAC_PRE_LEN(x)	    _SB_GETVALUE(x, S_MAC_PRE_LEN, M_MAC_PRE_LEN)
#पूर्ण_अगर /* 1250 PASS3 || 112x PASS1 || 1480 */

#घोषणा S_MAC_IFG_TX		    _SB_MAKE64(6)
#घोषणा M_MAC_IFG_TX		    _SB_MAKEMASK(6, S_MAC_IFG_TX)
#घोषणा V_MAC_IFG_TX(x)		    _SB_MAKEVALUE(x, S_MAC_IFG_TX)
#घोषणा G_MAC_IFG_TX(x)		    _SB_GETVALUE(x, S_MAC_IFG_TX, M_MAC_IFG_TX)

#घोषणा S_MAC_IFG_THRSH		    _SB_MAKE64(12)
#घोषणा M_MAC_IFG_THRSH		    _SB_MAKEMASK(6, S_MAC_IFG_THRSH)
#घोषणा V_MAC_IFG_THRSH(x)	    _SB_MAKEVALUE(x, S_MAC_IFG_THRSH)
#घोषणा G_MAC_IFG_THRSH(x)	    _SB_GETVALUE(x, S_MAC_IFG_THRSH, M_MAC_IFG_THRSH)

#घोषणा S_MAC_BACKOFF_SEL	    _SB_MAKE64(18)
#घोषणा M_MAC_BACKOFF_SEL	    _SB_MAKEMASK(4, S_MAC_BACKOFF_SEL)
#घोषणा V_MAC_BACKOFF_SEL(x)	    _SB_MAKEVALUE(x, S_MAC_BACKOFF_SEL)
#घोषणा G_MAC_BACKOFF_SEL(x)	    _SB_GETVALUE(x, S_MAC_BACKOFF_SEL, M_MAC_BACKOFF_SEL)

#घोषणा S_MAC_LFSR_SEED		    _SB_MAKE64(22)
#घोषणा M_MAC_LFSR_SEED		    _SB_MAKEMASK(8, S_MAC_LFSR_SEED)
#घोषणा V_MAC_LFSR_SEED(x)	    _SB_MAKEVALUE(x, S_MAC_LFSR_SEED)
#घोषणा G_MAC_LFSR_SEED(x)	    _SB_GETVALUE(x, S_MAC_LFSR_SEED, M_MAC_LFSR_SEED)

#घोषणा S_MAC_SLOT_SIZE		    _SB_MAKE64(30)
#घोषणा M_MAC_SLOT_SIZE		    _SB_MAKEMASK(10, S_MAC_SLOT_SIZE)
#घोषणा V_MAC_SLOT_SIZE(x)	    _SB_MAKEVALUE(x, S_MAC_SLOT_SIZE)
#घोषणा G_MAC_SLOT_SIZE(x)	    _SB_GETVALUE(x, S_MAC_SLOT_SIZE, M_MAC_SLOT_SIZE)

#घोषणा S_MAC_MIN_FRAMESZ	    _SB_MAKE64(40)
#घोषणा M_MAC_MIN_FRAMESZ	    _SB_MAKEMASK(8, S_MAC_MIN_FRAMESZ)
#घोषणा V_MAC_MIN_FRAMESZ(x)	    _SB_MAKEVALUE(x, S_MAC_MIN_FRAMESZ)
#घोषणा G_MAC_MIN_FRAMESZ(x)	    _SB_GETVALUE(x, S_MAC_MIN_FRAMESZ, M_MAC_MIN_FRAMESZ)

#घोषणा S_MAC_MAX_FRAMESZ	    _SB_MAKE64(48)
#घोषणा M_MAC_MAX_FRAMESZ	    _SB_MAKEMASK(16, S_MAC_MAX_FRAMESZ)
#घोषणा V_MAC_MAX_FRAMESZ(x)	    _SB_MAKEVALUE(x, S_MAC_MAX_FRAMESZ)
#घोषणा G_MAC_MAX_FRAMESZ(x)	    _SB_GETVALUE(x, S_MAC_MAX_FRAMESZ, M_MAC_MAX_FRAMESZ)

/*
 * These स्थिरants are used to configure the fields within the Frame
 * Configuration Register.
 */

#घोषणा K_MAC_IFG_RX_10		    _SB_MAKE64(0)	/* See table 176, not used */
#घोषणा K_MAC_IFG_RX_100	    _SB_MAKE64(0)
#घोषणा K_MAC_IFG_RX_1000	    _SB_MAKE64(0)

#घोषणा K_MAC_IFG_TX_10		    _SB_MAKE64(20)
#घोषणा K_MAC_IFG_TX_100	    _SB_MAKE64(20)
#घोषणा K_MAC_IFG_TX_1000	    _SB_MAKE64(8)

#घोषणा K_MAC_IFG_THRSH_10	    _SB_MAKE64(4)
#घोषणा K_MAC_IFG_THRSH_100	    _SB_MAKE64(4)
#घोषणा K_MAC_IFG_THRSH_1000	    _SB_MAKE64(0)

#घोषणा K_MAC_SLOT_SIZE_10	    _SB_MAKE64(0)
#घोषणा K_MAC_SLOT_SIZE_100	    _SB_MAKE64(0)
#घोषणा K_MAC_SLOT_SIZE_1000	    _SB_MAKE64(0)

#घोषणा V_MAC_IFG_RX_10	       V_MAC_IFG_RX(K_MAC_IFG_RX_10)
#घोषणा V_MAC_IFG_RX_100       V_MAC_IFG_RX(K_MAC_IFG_RX_100)
#घोषणा V_MAC_IFG_RX_1000      V_MAC_IFG_RX(K_MAC_IFG_RX_1000)

#घोषणा V_MAC_IFG_TX_10	       V_MAC_IFG_TX(K_MAC_IFG_TX_10)
#घोषणा V_MAC_IFG_TX_100       V_MAC_IFG_TX(K_MAC_IFG_TX_100)
#घोषणा V_MAC_IFG_TX_1000      V_MAC_IFG_TX(K_MAC_IFG_TX_1000)

#घोषणा V_MAC_IFG_THRSH_10     V_MAC_IFG_THRSH(K_MAC_IFG_THRSH_10)
#घोषणा V_MAC_IFG_THRSH_100    V_MAC_IFG_THRSH(K_MAC_IFG_THRSH_100)
#घोषणा V_MAC_IFG_THRSH_1000   V_MAC_IFG_THRSH(K_MAC_IFG_THRSH_1000)

#घोषणा V_MAC_SLOT_SIZE_10     V_MAC_SLOT_SIZE(K_MAC_SLOT_SIZE_10)
#घोषणा V_MAC_SLOT_SIZE_100    V_MAC_SLOT_SIZE(K_MAC_SLOT_SIZE_100)
#घोषणा V_MAC_SLOT_SIZE_1000   V_MAC_SLOT_SIZE(K_MAC_SLOT_SIZE_1000)

#घोषणा K_MAC_MIN_FRAMESZ_FIFO	    _SB_MAKE64(9)
#घोषणा K_MAC_MIN_FRAMESZ_DEFAULT   _SB_MAKE64(64)
#घोषणा K_MAC_MAX_FRAMESZ_DEFAULT   _SB_MAKE64(1518)
#घोषणा K_MAC_MAX_FRAMESZ_JUMBO	    _SB_MAKE64(9216)

#घोषणा V_MAC_MIN_FRAMESZ_FIFO	    V_MAC_MIN_FRAMESZ(K_MAC_MIN_FRAMESZ_FIFO)
#घोषणा V_MAC_MIN_FRAMESZ_DEFAULT   V_MAC_MIN_FRAMESZ(K_MAC_MIN_FRAMESZ_DEFAULT)
#घोषणा V_MAC_MAX_FRAMESZ_DEFAULT   V_MAC_MAX_FRAMESZ(K_MAC_MAX_FRAMESZ_DEFAULT)
#घोषणा V_MAC_MAX_FRAMESZ_JUMBO	    V_MAC_MAX_FRAMESZ(K_MAC_MAX_FRAMESZ_JUMBO)

/*
 * MAC VLAN Tag Registers (Table 9-16)
 * Register: MAC_VLANTAG_0
 * Register: MAC_VLANTAG_1
 * Register: MAC_VLANTAG_2
 */

#घोषणा S_MAC_VLAN_TAG		 _SB_MAKE64(0)
#घोषणा M_MAC_VLAN_TAG		 _SB_MAKEMASK(32, S_MAC_VLAN_TAG)
#घोषणा V_MAC_VLAN_TAG(x)	 _SB_MAKEVALUE(x, S_MAC_VLAN_TAG)
#घोषणा G_MAC_VLAN_TAG(x)	 _SB_GETVALUE(x, S_MAC_VLAN_TAG, M_MAC_VLAN_TAG)

#अगर SIBYTE_HDR_FEATURE(1250, PASS3) || SIBYTE_HDR_FEATURE(112x, PASS1)
#घोषणा S_MAC_TX_PKT_OFFSET	 _SB_MAKE64(32)
#घोषणा M_MAC_TX_PKT_OFFSET	 _SB_MAKEMASK(8, S_MAC_TX_PKT_OFFSET)
#घोषणा V_MAC_TX_PKT_OFFSET(x)	 _SB_MAKEVALUE(x, S_MAC_TX_PKT_OFFSET)
#घोषणा G_MAC_TX_PKT_OFFSET(x)	 _SB_GETVALUE(x, S_MAC_TX_PKT_OFFSET, M_MAC_TX_PKT_OFFSET)

#घोषणा S_MAC_TX_CRC_OFFSET	 _SB_MAKE64(40)
#घोषणा M_MAC_TX_CRC_OFFSET	 _SB_MAKEMASK(8, S_MAC_TX_CRC_OFFSET)
#घोषणा V_MAC_TX_CRC_OFFSET(x)	 _SB_MAKEVALUE(x, S_MAC_TX_CRC_OFFSET)
#घोषणा G_MAC_TX_CRC_OFFSET(x)	 _SB_GETVALUE(x, S_MAC_TX_CRC_OFFSET, M_MAC_TX_CRC_OFFSET)

#घोषणा M_MAC_CH_BASE_FC_EN	 _SB_MAKEMASK1(48)
#पूर्ण_अगर /* 1250 PASS3 || 112x PASS1 */

/*
 * MAC Status Registers (Table 9-17)
 * Also used क्रम the MAC Interrupt Mask Register (Table 9-18)
 * Register: MAC_STATUS_0
 * Register: MAC_STATUS_1
 * Register: MAC_STATUS_2
 * Register: MAC_INT_MASK_0
 * Register: MAC_INT_MASK_1
 * Register: MAC_INT_MASK_2
 */

/*
 * Use these स्थिरants to shअगरt the appropriate channel
 * पूर्णांकo the CH0 position so the same tests can be used
 * on each channel.
 */

#घोषणा S_MAC_RX_CH0		    _SB_MAKE64(0)
#घोषणा S_MAC_RX_CH1		    _SB_MAKE64(8)
#घोषणा S_MAC_TX_CH0		    _SB_MAKE64(16)
#घोषणा S_MAC_TX_CH1		    _SB_MAKE64(24)

#घोषणा S_MAC_TXCHANNELS	    _SB_MAKE64(16)	/* this is 1st TX chan */
#घोषणा S_MAC_CHANWIDTH		    _SB_MAKE64(8)	/* bits between channels */

/*
 *  These are the same as RX channel 0.	 The idea here
 *  is that you'll use one of the "S_" things above
 *  and pass just the six bits to a DMA-channel-specअगरic ISR
 */
#घोषणा M_MAC_INT_CHANNEL	    _SB_MAKEMASK(8, 0)
#घोषणा M_MAC_INT_EOP_COUNT	    _SB_MAKEMASK1(0)
#घोषणा M_MAC_INT_EOP_TIMER	    _SB_MAKEMASK1(1)
#घोषणा M_MAC_INT_EOP_SEEN	    _SB_MAKEMASK1(2)
#घोषणा M_MAC_INT_HWM		    _SB_MAKEMASK1(3)
#घोषणा M_MAC_INT_LWM		    _SB_MAKEMASK1(4)
#घोषणा M_MAC_INT_DSCR		    _SB_MAKEMASK1(5)
#घोषणा M_MAC_INT_ERR		    _SB_MAKEMASK1(6)
#घोषणा M_MAC_INT_DZERO		    _SB_MAKEMASK1(7)	/* only क्रम TX channels */
#घोषणा M_MAC_INT_DROP		    _SB_MAKEMASK1(7)	/* only क्रम RX channels */

/*
 * In the following definitions we use ch (0/1) and txrx (TX=1, RX=0, see
 * also DMA_TX/DMA_RX in sb_regs.h).
 */
#घोषणा S_MAC_STATUS_CH_OFFSET(ch, txrx) _SB_MAKE64(((ch) + 2 * (txrx)) * S_MAC_CHANWIDTH)

#घोषणा M_MAC_STATUS_CHANNEL(ch, txrx)	 _SB_MAKEVALUE(_SB_MAKEMASK(8, 0), S_MAC_STATUS_CH_OFFSET(ch, txrx))
#घोषणा M_MAC_STATUS_EOP_COUNT(ch, txrx) _SB_MAKEVALUE(M_MAC_INT_EOP_COUNT, S_MAC_STATUS_CH_OFFSET(ch, txrx))
#घोषणा M_MAC_STATUS_EOP_TIMER(ch, txrx) _SB_MAKEVALUE(M_MAC_INT_EOP_TIMER, S_MAC_STATUS_CH_OFFSET(ch, txrx))
#घोषणा M_MAC_STATUS_EOP_SEEN(ch, txrx)	 _SB_MAKEVALUE(M_MAC_INT_EOP_SEEN, S_MAC_STATUS_CH_OFFSET(ch, txrx))
#घोषणा M_MAC_STATUS_HWM(ch, txrx)	 _SB_MAKEVALUE(M_MAC_INT_HWM, S_MAC_STATUS_CH_OFFSET(ch, txrx))
#घोषणा M_MAC_STATUS_LWM(ch, txrx)	 _SB_MAKEVALUE(M_MAC_INT_LWM, S_MAC_STATUS_CH_OFFSET(ch, txrx))
#घोषणा M_MAC_STATUS_DSCR(ch, txrx)	 _SB_MAKEVALUE(M_MAC_INT_DSCR, S_MAC_STATUS_CH_OFFSET(ch, txrx))
#घोषणा M_MAC_STATUS_ERR(ch, txrx)	 _SB_MAKEVALUE(M_MAC_INT_ERR, S_MAC_STATUS_CH_OFFSET(ch, txrx))
#घोषणा M_MAC_STATUS_DZERO(ch, txrx)	 _SB_MAKEVALUE(M_MAC_INT_DZERO, S_MAC_STATUS_CH_OFFSET(ch, txrx))
#घोषणा M_MAC_STATUS_DROP(ch, txrx)	 _SB_MAKEVALUE(M_MAC_INT_DROP, S_MAC_STATUS_CH_OFFSET(ch, txrx))
#घोषणा M_MAC_STATUS_OTHER_ERR		 _SB_MAKEVALUE(_SB_MAKEMASK(7, 0), 40)


#घोषणा M_MAC_RX_UNDRFL		    _SB_MAKEMASK1(40)
#घोषणा M_MAC_RX_OVRFL		    _SB_MAKEMASK1(41)
#घोषणा M_MAC_TX_UNDRFL		    _SB_MAKEMASK1(42)
#घोषणा M_MAC_TX_OVRFL		    _SB_MAKEMASK1(43)
#घोषणा M_MAC_LTCOL_ERR		    _SB_MAKEMASK1(44)
#घोषणा M_MAC_EXCOL_ERR		    _SB_MAKEMASK1(45)
#घोषणा M_MAC_CNTR_OVRFL_ERR	    _SB_MAKEMASK1(46)
#अगर SIBYTE_HDR_FEATURE(1250, PASS2) || SIBYTE_HDR_FEATURE(112x, PASS1) || SIBYTE_HDR_FEATURE_CHIP(1480)
#घोषणा M_MAC_SPLIT_EN		    _SB_MAKEMASK1(47)	/* पूर्णांकerrupt mask only */
#पूर्ण_अगर /* 1250 PASS2 || 112x PASS1 || 1480 */

#घोषणा S_MAC_COUNTER_ADDR	    _SB_MAKE64(47)
#घोषणा M_MAC_COUNTER_ADDR	    _SB_MAKEMASK(5, S_MAC_COUNTER_ADDR)
#घोषणा V_MAC_COUNTER_ADDR(x)	    _SB_MAKEVALUE(x, S_MAC_COUNTER_ADDR)
#घोषणा G_MAC_COUNTER_ADDR(x)	    _SB_GETVALUE(x, S_MAC_COUNTER_ADDR, M_MAC_COUNTER_ADDR)

#अगर SIBYTE_HDR_FEATURE(1250, PASS3) || SIBYTE_HDR_FEATURE(112x, PASS1) || SIBYTE_HDR_FEATURE_CHIP(1480)
#घोषणा M_MAC_TX_PAUSE_ON	    _SB_MAKEMASK1(52)
#पूर्ण_अगर /* 1250 PASS3 || 112x PASS1 || 1480 */

/*
 * MAC Fअगरo Poपूर्णांकer Registers (Table 9-19)    [Debug रेजिस्टर]
 * Register: MAC_FIFO_PTRS_0
 * Register: MAC_FIFO_PTRS_1
 * Register: MAC_FIFO_PTRS_2
 */

#घोषणा S_MAC_TX_WRPTR		    _SB_MAKE64(0)
#घोषणा M_MAC_TX_WRPTR		    _SB_MAKEMASK(6, S_MAC_TX_WRPTR)
#घोषणा V_MAC_TX_WRPTR(x)	    _SB_MAKEVALUE(x, S_MAC_TX_WRPTR)
#घोषणा G_MAC_TX_WRPTR(x)	    _SB_GETVALUE(x, S_MAC_TX_WRPTR, M_MAC_TX_WRPTR)

#घोषणा S_MAC_TX_RDPTR		    _SB_MAKE64(8)
#घोषणा M_MAC_TX_RDPTR		    _SB_MAKEMASK(6, S_MAC_TX_RDPTR)
#घोषणा V_MAC_TX_RDPTR(x)	    _SB_MAKEVALUE(x, S_MAC_TX_RDPTR)
#घोषणा G_MAC_TX_RDPTR(x)	    _SB_GETVALUE(x, S_MAC_TX_RDPTR, M_MAC_TX_RDPTR)

#घोषणा S_MAC_RX_WRPTR		    _SB_MAKE64(16)
#घोषणा M_MAC_RX_WRPTR		    _SB_MAKEMASK(6, S_MAC_RX_WRPTR)
#घोषणा V_MAC_RX_WRPTR(x)	    _SB_MAKEVALUE(x, S_MAC_RX_WRPTR)
#घोषणा G_MAC_RX_WRPTR(x)	    _SB_GETVALUE(x, S_MAC_RX_WRPTR, M_MAC_TX_WRPTR)

#घोषणा S_MAC_RX_RDPTR		    _SB_MAKE64(24)
#घोषणा M_MAC_RX_RDPTR		    _SB_MAKEMASK(6, S_MAC_RX_RDPTR)
#घोषणा V_MAC_RX_RDPTR(x)	    _SB_MAKEVALUE(x, S_MAC_RX_RDPTR)
#घोषणा G_MAC_RX_RDPTR(x)	    _SB_GETVALUE(x, S_MAC_RX_RDPTR, M_MAC_TX_RDPTR)

/*
 * MAC Fअगरo End Of Packet Count Registers (Table 9-20)	[Debug रेजिस्टर]
 * Register: MAC_EOPCNT_0
 * Register: MAC_EOPCNT_1
 * Register: MAC_EOPCNT_2
 */

#घोषणा S_MAC_TX_EOP_COUNTER	    _SB_MAKE64(0)
#घोषणा M_MAC_TX_EOP_COUNTER	    _SB_MAKEMASK(6, S_MAC_TX_EOP_COUNTER)
#घोषणा V_MAC_TX_EOP_COUNTER(x)	    _SB_MAKEVALUE(x, S_MAC_TX_EOP_COUNTER)
#घोषणा G_MAC_TX_EOP_COUNTER(x)	    _SB_GETVALUE(x, S_MAC_TX_EOP_COUNTER, M_MAC_TX_EOP_COUNTER)

#घोषणा S_MAC_RX_EOP_COUNTER	    _SB_MAKE64(8)
#घोषणा M_MAC_RX_EOP_COUNTER	    _SB_MAKEMASK(6, S_MAC_RX_EOP_COUNTER)
#घोषणा V_MAC_RX_EOP_COUNTER(x)	    _SB_MAKEVALUE(x, S_MAC_RX_EOP_COUNTER)
#घोषणा G_MAC_RX_EOP_COUNTER(x)	    _SB_GETVALUE(x, S_MAC_RX_EOP_COUNTER, M_MAC_RX_EOP_COUNTER)

/*
 * MAC Receive Address Filter Exact Match Registers (Table 9-21)
 * Registers: MAC_ADDR0_0 through MAC_ADDR7_0
 * Registers: MAC_ADDR0_1 through MAC_ADDR7_1
 * Registers: MAC_ADDR0_2 through MAC_ADDR7_2
 */

/* No bitfields */

/*
 * MAC Receive Address Filter Mask Registers
 * Registers: MAC_ADDRMASK0_0 and MAC_ADDRMASK0_1
 * Registers: MAC_ADDRMASK1_0 and MAC_ADDRMASK1_1
 * Registers: MAC_ADDRMASK2_0 and MAC_ADDRMASK2_1
 */

/* No bitfields */

/*
 * MAC Receive Address Filter Hash Match Registers (Table 9-22)
 * Registers: MAC_HASH0_0 through MAC_HASH7_0
 * Registers: MAC_HASH0_1 through MAC_HASH7_1
 * Registers: MAC_HASH0_2 through MAC_HASH7_2
 */

/* No bitfields */

/*
 * MAC Transmit Source Address Registers (Table 9-23)
 * Register: MAC_ETHERNET_ADDR_0
 * Register: MAC_ETHERNET_ADDR_1
 * Register: MAC_ETHERNET_ADDR_2
 */

/* No bitfields */

/*
 * MAC Packet Type Configuration Register
 * Register: MAC_TYPE_CFG_0
 * Register: MAC_TYPE_CFG_1
 * Register: MAC_TYPE_CFG_2
 */

#घोषणा S_TYPECFG_TYPESIZE	_SB_MAKE64(16)

#घोषणा S_TYPECFG_TYPE0		_SB_MAKE64(0)
#घोषणा M_TYPECFG_TYPE0		_SB_MAKEMASK(16, S_TYPECFG_TYPE0)
#घोषणा V_TYPECFG_TYPE0(x)	_SB_MAKEVALUE(x, S_TYPECFG_TYPE0)
#घोषणा G_TYPECFG_TYPE0(x)	_SB_GETVALUE(x, S_TYPECFG_TYPE0, M_TYPECFG_TYPE0)

#घोषणा S_TYPECFG_TYPE1		_SB_MAKE64(0)
#घोषणा M_TYPECFG_TYPE1		_SB_MAKEMASK(16, S_TYPECFG_TYPE1)
#घोषणा V_TYPECFG_TYPE1(x)	_SB_MAKEVALUE(x, S_TYPECFG_TYPE1)
#घोषणा G_TYPECFG_TYPE1(x)	_SB_GETVALUE(x, S_TYPECFG_TYPE1, M_TYPECFG_TYPE1)

#घोषणा S_TYPECFG_TYPE2		_SB_MAKE64(0)
#घोषणा M_TYPECFG_TYPE2		_SB_MAKEMASK(16, S_TYPECFG_TYPE2)
#घोषणा V_TYPECFG_TYPE2(x)	_SB_MAKEVALUE(x, S_TYPECFG_TYPE2)
#घोषणा G_TYPECFG_TYPE2(x)	_SB_GETVALUE(x, S_TYPECFG_TYPE2, M_TYPECFG_TYPE2)

#घोषणा S_TYPECFG_TYPE3		_SB_MAKE64(0)
#घोषणा M_TYPECFG_TYPE3		_SB_MAKEMASK(16, S_TYPECFG_TYPE3)
#घोषणा V_TYPECFG_TYPE3(x)	_SB_MAKEVALUE(x, S_TYPECFG_TYPE3)
#घोषणा G_TYPECFG_TYPE3(x)	_SB_GETVALUE(x, S_TYPECFG_TYPE3, M_TYPECFG_TYPE3)

/*
 * MAC Receive Address Filter Control Registers (Table 9-24)
 * Register: MAC_ADFILTER_CFG_0
 * Register: MAC_ADFILTER_CFG_1
 * Register: MAC_ADFILTER_CFG_2
 */

#घोषणा M_MAC_ALLPKT_EN		_SB_MAKEMASK1(0)
#घोषणा M_MAC_UCAST_EN		_SB_MAKEMASK1(1)
#घोषणा M_MAC_UCAST_INV		_SB_MAKEMASK1(2)
#घोषणा M_MAC_MCAST_EN		_SB_MAKEMASK1(3)
#घोषणा M_MAC_MCAST_INV		_SB_MAKEMASK1(4)
#घोषणा M_MAC_BCAST_EN		_SB_MAKEMASK1(5)
#घोषणा M_MAC_सूचीECT_INV	_SB_MAKEMASK1(6)
#अगर SIBYTE_HDR_FEATURE(1250, PASS2) || SIBYTE_HDR_FEATURE(112x, PASS1) || SIBYTE_HDR_FEATURE_CHIP(1480)
#घोषणा M_MAC_ALLMCAST_EN	_SB_MAKEMASK1(7)
#पूर्ण_अगर /* 1250 PASS2 || 112x PASS1 || 1480 */

#घोषणा S_MAC_IPHDR_OFFSET	_SB_MAKE64(8)
#घोषणा M_MAC_IPHDR_OFFSET	_SB_MAKEMASK(8, S_MAC_IPHDR_OFFSET)
#घोषणा V_MAC_IPHDR_OFFSET(x)	_SB_MAKEVALUE(x, S_MAC_IPHDR_OFFSET)
#घोषणा G_MAC_IPHDR_OFFSET(x)	_SB_GETVALUE(x, S_MAC_IPHDR_OFFSET, M_MAC_IPHDR_OFFSET)

#अगर SIBYTE_HDR_FEATURE(1250, PASS3) || SIBYTE_HDR_FEATURE(112x, PASS1) || SIBYTE_HDR_FEATURE_CHIP(1480)
#घोषणा S_MAC_RX_CRC_OFFSET	_SB_MAKE64(16)
#घोषणा M_MAC_RX_CRC_OFFSET	_SB_MAKEMASK(8, S_MAC_RX_CRC_OFFSET)
#घोषणा V_MAC_RX_CRC_OFFSET(x)	_SB_MAKEVALUE(x, S_MAC_RX_CRC_OFFSET)
#घोषणा G_MAC_RX_CRC_OFFSET(x)	_SB_GETVALUE(x, S_MAC_RX_CRC_OFFSET, M_MAC_RX_CRC_OFFSET)

#घोषणा S_MAC_RX_PKT_OFFSET	_SB_MAKE64(24)
#घोषणा M_MAC_RX_PKT_OFFSET	_SB_MAKEMASK(8, S_MAC_RX_PKT_OFFSET)
#घोषणा V_MAC_RX_PKT_OFFSET(x)	_SB_MAKEVALUE(x, S_MAC_RX_PKT_OFFSET)
#घोषणा G_MAC_RX_PKT_OFFSET(x)	_SB_GETVALUE(x, S_MAC_RX_PKT_OFFSET, M_MAC_RX_PKT_OFFSET)

#घोषणा M_MAC_FWDPAUSE_EN	_SB_MAKEMASK1(32)
#घोषणा M_MAC_VLAN_DET_EN	_SB_MAKEMASK1(33)

#घोषणा S_MAC_RX_CH_MSN_SEL	_SB_MAKE64(34)
#घोषणा M_MAC_RX_CH_MSN_SEL	_SB_MAKEMASK(8, S_MAC_RX_CH_MSN_SEL)
#घोषणा V_MAC_RX_CH_MSN_SEL(x)	_SB_MAKEVALUE(x, S_MAC_RX_CH_MSN_SEL)
#घोषणा G_MAC_RX_CH_MSN_SEL(x)	_SB_GETVALUE(x, S_MAC_RX_CH_MSN_SEL, M_MAC_RX_CH_MSN_SEL)
#पूर्ण_अगर /* 1250 PASS3 || 112x PASS1 || 1480 */

/*
 * MAC Receive Channel Select Registers (Table 9-25)
 */

/* no bitfields */

/*
 * MAC MII Management Interface Registers (Table 9-26)
 * Register: MAC_MDIO_0
 * Register: MAC_MDIO_1
 * Register: MAC_MDIO_2
 */

#घोषणा S_MAC_MDC		0
#घोषणा S_MAC_MDIO_सूची		1
#घोषणा S_MAC_MDIO_OUT		2
#घोषणा S_MAC_GENC		3
#घोषणा S_MAC_MDIO_IN		4

#घोषणा M_MAC_MDC		_SB_MAKEMASK1(S_MAC_MDC)
#घोषणा M_MAC_MDIO_सूची		_SB_MAKEMASK1(S_MAC_MDIO_सूची)
#घोषणा M_MAC_MDIO_सूची_INPUT	_SB_MAKEMASK1(S_MAC_MDIO_सूची)
#घोषणा M_MAC_MDIO_OUT		_SB_MAKEMASK1(S_MAC_MDIO_OUT)
#घोषणा M_MAC_GENC		_SB_MAKEMASK1(S_MAC_GENC)
#घोषणा M_MAC_MDIO_IN		_SB_MAKEMASK1(S_MAC_MDIO_IN)

#पूर्ण_अगर
