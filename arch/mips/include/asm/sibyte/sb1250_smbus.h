<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*  *********************************************************************
    *  SB1250 Board Support Package
    *
    *  SMBUS Constants				File: sb1250_smbus.h
    *
    *  This module contains स्थिरants and macros useful क्रम
    *  manipulating the SB1250's SMbus devices.
    *
    *  SB1250 specअगरication level:  10/21/02
    *  BCM1280 specअगरication level:  11/24/03
    *
    *********************************************************************
    *
    *  Copyright 2000,2001,2002,2003
    *  Broadcom Corporation. All rights reserved.
    *
    ********************************************************************* */


#अगर_अघोषित _SB1250_SMBUS_H
#घोषणा _SB1250_SMBUS_H

#समावेश <यंत्र/sibyte/sb1250_defs.h>

/*
 * SMBus Clock Frequency Register (Table 14-2)
 */

#घोषणा S_SMB_FREQ_DIV		    0
#घोषणा M_SMB_FREQ_DIV		    _SB_MAKEMASK(13, S_SMB_FREQ_DIV)
#घोषणा V_SMB_FREQ_DIV(x)	    _SB_MAKEVALUE(x, S_SMB_FREQ_DIV)

#घोषणा K_SMB_FREQ_400KHZ	    0x1F
#घोषणा K_SMB_FREQ_100KHZ	    0x7D
#घोषणा K_SMB_FREQ_10KHZ	    1250

#घोषणा S_SMB_CMD		    0
#घोषणा M_SMB_CMD		    _SB_MAKEMASK(8, S_SMB_CMD)
#घोषणा V_SMB_CMD(x)		    _SB_MAKEVALUE(x, S_SMB_CMD)

/*
 * SMBus control रेजिस्टर (Table 14-4)
 */

#घोषणा M_SMB_ERR_INTR		    _SB_MAKEMASK1(0)
#घोषणा M_SMB_FINISH_INTR	    _SB_MAKEMASK1(1)

#घोषणा S_SMB_DATA_OUT		    4
#घोषणा M_SMB_DATA_OUT		    _SB_MAKEMASK1(S_SMB_DATA_OUT)
#घोषणा V_SMB_DATA_OUT(x)	    _SB_MAKEVALUE(x, S_SMB_DATA_OUT)

#घोषणा M_SMB_DATA_सूची		    _SB_MAKEMASK1(5)
#घोषणा M_SMB_DATA_सूची_OUTPUT	    M_SMB_DATA_सूची
#घोषणा M_SMB_CLK_OUT		    _SB_MAKEMASK1(6)
#घोषणा M_SMB_सूचीECT_ENABLE	    _SB_MAKEMASK1(7)

/*
 * SMBus status रेजिस्टरs (Table 14-5)
 */

#घोषणा M_SMB_BUSY		    _SB_MAKEMASK1(0)
#घोषणा M_SMB_ERROR		    _SB_MAKEMASK1(1)
#घोषणा M_SMB_ERROR_TYPE	    _SB_MAKEMASK1(2)

#अगर SIBYTE_HDR_FEATURE(1250, PASS3) || SIBYTE_HDR_FEATURE(112x, PASS1) || SIBYTE_HDR_FEATURE_CHIP(1480)
#घोषणा S_SMB_SCL_IN		    5
#घोषणा M_SMB_SCL_IN		    _SB_MAKEMASK1(S_SMB_SCL_IN)
#घोषणा V_SMB_SCL_IN(x)		    _SB_MAKEVALUE(x, S_SMB_SCL_IN)
#घोषणा G_SMB_SCL_IN(x)		    _SB_GETVALUE(x, S_SMB_SCL_IN, M_SMB_SCL_IN)
#पूर्ण_अगर /* 1250 PASS3 || 112x PASS1 || 1480 */

#घोषणा S_SMB_REF		    6
#घोषणा M_SMB_REF		    _SB_MAKEMASK1(S_SMB_REF)
#घोषणा V_SMB_REF(x)		    _SB_MAKEVALUE(x, S_SMB_REF)
#घोषणा G_SMB_REF(x)		    _SB_GETVALUE(x, S_SMB_REF, M_SMB_REF)

#घोषणा S_SMB_DATA_IN		    7
#घोषणा M_SMB_DATA_IN		    _SB_MAKEMASK1(S_SMB_DATA_IN)
#घोषणा V_SMB_DATA_IN(x)	    _SB_MAKEVALUE(x, S_SMB_DATA_IN)
#घोषणा G_SMB_DATA_IN(x)	    _SB_GETVALUE(x, S_SMB_DATA_IN, M_SMB_DATA_IN)

/*
 * SMBus Start/Command रेजिस्टरs (Table 14-9)
 */

#घोषणा S_SMB_ADDR		    0
#घोषणा M_SMB_ADDR		    _SB_MAKEMASK(7, S_SMB_ADDR)
#घोषणा V_SMB_ADDR(x)		    _SB_MAKEVALUE(x, S_SMB_ADDR)
#घोषणा G_SMB_ADDR(x)		    _SB_GETVALUE(x, S_SMB_ADDR, M_SMB_ADDR)

#घोषणा M_SMB_QDATA		    _SB_MAKEMASK1(7)

#घोषणा S_SMB_TT		    8
#घोषणा M_SMB_TT		    _SB_MAKEMASK(3, S_SMB_TT)
#घोषणा V_SMB_TT(x)		    _SB_MAKEVALUE(x, S_SMB_TT)
#घोषणा G_SMB_TT(x)		    _SB_GETVALUE(x, S_SMB_TT, M_SMB_TT)

#घोषणा K_SMB_TT_WR1BYTE	    0
#घोषणा K_SMB_TT_WR2BYTE	    1
#घोषणा K_SMB_TT_WR3BYTE	    2
#घोषणा K_SMB_TT_CMD_RD1BYTE	    3
#घोषणा K_SMB_TT_CMD_RD2BYTE	    4
#घोषणा K_SMB_TT_RD1BYTE	    5
#घोषणा K_SMB_TT_QUICKCMD	    6
#घोषणा K_SMB_TT_EEPROMREAD	    7

#घोषणा V_SMB_TT_WR1BYTE	    V_SMB_TT(K_SMB_TT_WR1BYTE)
#घोषणा V_SMB_TT_WR2BYTE	    V_SMB_TT(K_SMB_TT_WR2BYTE)
#घोषणा V_SMB_TT_WR3BYTE	    V_SMB_TT(K_SMB_TT_WR3BYTE)
#घोषणा V_SMB_TT_CMD_RD1BYTE	    V_SMB_TT(K_SMB_TT_CMD_RD1BYTE)
#घोषणा V_SMB_TT_CMD_RD2BYTE	    V_SMB_TT(K_SMB_TT_CMD_RD2BYTE)
#घोषणा V_SMB_TT_RD1BYTE	    V_SMB_TT(K_SMB_TT_RD1BYTE)
#घोषणा V_SMB_TT_QUICKCMD	    V_SMB_TT(K_SMB_TT_QUICKCMD)
#घोषणा V_SMB_TT_EEPROMREAD	    V_SMB_TT(K_SMB_TT_EEPROMREAD)

#घोषणा M_SMB_PEC		    _SB_MAKEMASK1(15)

/*
 * SMBus Data Register (Table 14-6) and SMBus Extra Register (Table 14-7)
 */

#घोषणा S_SMB_LB		    0
#घोषणा M_SMB_LB		    _SB_MAKEMASK(8, S_SMB_LB)
#घोषणा V_SMB_LB(x)		    _SB_MAKEVALUE(x, S_SMB_LB)

#घोषणा S_SMB_MB		    8
#घोषणा M_SMB_MB		    _SB_MAKEMASK(8, S_SMB_MB)
#घोषणा V_SMB_MB(x)		    _SB_MAKEVALUE(x, S_SMB_MB)


/*
 * SMBus Packet Error Check रेजिस्टर (Table 14-8)
 */

#घोषणा S_SPEC_PEC		    0
#घोषणा M_SPEC_PEC		    _SB_MAKEMASK(8, S_SPEC_PEC)
#घोषणा V_SPEC_MB(x)		    _SB_MAKEVALUE(x, S_SPEC_PEC)


#अगर SIBYTE_HDR_FEATURE(1250, PASS2) || SIBYTE_HDR_FEATURE(112x, PASS1) || SIBYTE_HDR_FEATURE_CHIP(1480)

#घोषणा S_SMB_CMDH		    8
#घोषणा M_SMB_CMDH		    _SB_MAKEMASK(8, S_SMB_CMDH)
#घोषणा V_SMB_CMDH(x)		    _SB_MAKEVALUE(x, S_SMB_CMDH)

#घोषणा M_SMB_EXTEND		    _SB_MAKEMASK1(14)

#घोषणा S_SMB_DFMT		    8
#घोषणा M_SMB_DFMT		    _SB_MAKEMASK(3, S_SMB_DFMT)
#घोषणा V_SMB_DFMT(x)		    _SB_MAKEVALUE(x, S_SMB_DFMT)
#घोषणा G_SMB_DFMT(x)		    _SB_GETVALUE(x, S_SMB_DFMT, M_SMB_DFMT)

#घोषणा K_SMB_DFMT_1BYTE	    0
#घोषणा K_SMB_DFMT_2BYTE	    1
#घोषणा K_SMB_DFMT_3BYTE	    2
#घोषणा K_SMB_DFMT_4BYTE	    3
#घोषणा K_SMB_DFMT_NODATA	    4
#घोषणा K_SMB_DFMT_CMD4BYTE	    5
#घोषणा K_SMB_DFMT_CMD5BYTE	    6
#घोषणा K_SMB_DFMT_RESERVED	    7

#घोषणा V_SMB_DFMT_1BYTE	    V_SMB_DFMT(K_SMB_DFMT_1BYTE)
#घोषणा V_SMB_DFMT_2BYTE	    V_SMB_DFMT(K_SMB_DFMT_2BYTE)
#घोषणा V_SMB_DFMT_3BYTE	    V_SMB_DFMT(K_SMB_DFMT_3BYTE)
#घोषणा V_SMB_DFMT_4BYTE	    V_SMB_DFMT(K_SMB_DFMT_4BYTE)
#घोषणा V_SMB_DFMT_NODATA	    V_SMB_DFMT(K_SMB_DFMT_NODATA)
#घोषणा V_SMB_DFMT_CMD4BYTE	    V_SMB_DFMT(K_SMB_DFMT_CMD4BYTE)
#घोषणा V_SMB_DFMT_CMD5BYTE	    V_SMB_DFMT(K_SMB_DFMT_CMD5BYTE)
#घोषणा V_SMB_DFMT_RESERVED	    V_SMB_DFMT(K_SMB_DFMT_RESERVED)

#घोषणा S_SMB_AFMT		    11
#घोषणा M_SMB_AFMT		    _SB_MAKEMASK(2, S_SMB_AFMT)
#घोषणा V_SMB_AFMT(x)		    _SB_MAKEVALUE(x, S_SMB_AFMT)
#घोषणा G_SMB_AFMT(x)		    _SB_GETVALUE(x, S_SMB_AFMT, M_SMB_AFMT)

#घोषणा K_SMB_AFMT_NONE		    0
#घोषणा K_SMB_AFMT_ADDR		    1
#घोषणा K_SMB_AFMT_ADDR_CMD1BYTE    2
#घोषणा K_SMB_AFMT_ADDR_CMD2BYTE    3

#घोषणा V_SMB_AFMT_NONE		    V_SMB_AFMT(K_SMB_AFMT_NONE)
#घोषणा V_SMB_AFMT_ADDR		    V_SMB_AFMT(K_SMB_AFMT_ADDR)
#घोषणा V_SMB_AFMT_ADDR_CMD1BYTE    V_SMB_AFMT(K_SMB_AFMT_ADDR_CMD1BYTE)
#घोषणा V_SMB_AFMT_ADDR_CMD2BYTE    V_SMB_AFMT(K_SMB_AFMT_ADDR_CMD2BYTE)

#घोषणा M_SMB_सूची		    _SB_MAKEMASK1(13)

#पूर्ण_अगर /* 1250 PASS2 || 112x PASS1 || 1480 */

#पूर्ण_अगर
