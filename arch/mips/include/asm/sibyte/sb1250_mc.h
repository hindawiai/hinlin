<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*  *********************************************************************
    *  SB1250 Board Support Package
    *
    *  Memory Controller स्थिरants		File: sb1250_mc.h
    *
    *  This module contains स्थिरants and macros useful क्रम
    *  programming the memory controller.
    *
    *  SB1250 specअगरication level:  User's manual 1/02/02
    *
    *********************************************************************
    *
    *  Copyright 2000, 2001, 2002, 2003
    *  Broadcom Corporation. All rights reserved.
    *
    ********************************************************************* */


#अगर_अघोषित _SB1250_MC_H
#घोषणा _SB1250_MC_H

#समावेश <यंत्र/sibyte/sb1250_defs.h>

/*
 * Memory Channel Config Register (table 6-14)
 */

#घोषणा S_MC_RESERVED0		    0
#घोषणा M_MC_RESERVED0		    _SB_MAKEMASK(8, S_MC_RESERVED0)

#घोषणा S_MC_CHANNEL_SEL	    8
#घोषणा M_MC_CHANNEL_SEL	    _SB_MAKEMASK(8, S_MC_CHANNEL_SEL)
#घोषणा V_MC_CHANNEL_SEL(x)	    _SB_MAKEVALUE(x, S_MC_CHANNEL_SEL)
#घोषणा G_MC_CHANNEL_SEL(x)	    _SB_GETVALUE(x, S_MC_CHANNEL_SEL, M_MC_CHANNEL_SEL)

#घोषणा S_MC_BANK0_MAP		    16
#घोषणा M_MC_BANK0_MAP		    _SB_MAKEMASK(4, S_MC_BANK0_MAP)
#घोषणा V_MC_BANK0_MAP(x)	    _SB_MAKEVALUE(x, S_MC_BANK0_MAP)
#घोषणा G_MC_BANK0_MAP(x)	    _SB_GETVALUE(x, S_MC_BANK0_MAP, M_MC_BANK0_MAP)

#घोषणा K_MC_BANK0_MAP_DEFAULT	    0x00
#घोषणा V_MC_BANK0_MAP_DEFAULT	    V_MC_BANK0_MAP(K_MC_BANK0_MAP_DEFAULT)

#घोषणा S_MC_BANK1_MAP		    20
#घोषणा M_MC_BANK1_MAP		    _SB_MAKEMASK(4, S_MC_BANK1_MAP)
#घोषणा V_MC_BANK1_MAP(x)	    _SB_MAKEVALUE(x, S_MC_BANK1_MAP)
#घोषणा G_MC_BANK1_MAP(x)	    _SB_GETVALUE(x, S_MC_BANK1_MAP, M_MC_BANK1_MAP)

#घोषणा K_MC_BANK1_MAP_DEFAULT	    0x08
#घोषणा V_MC_BANK1_MAP_DEFAULT	    V_MC_BANK1_MAP(K_MC_BANK1_MAP_DEFAULT)

#घोषणा S_MC_BANK2_MAP		    24
#घोषणा M_MC_BANK2_MAP		    _SB_MAKEMASK(4, S_MC_BANK2_MAP)
#घोषणा V_MC_BANK2_MAP(x)	    _SB_MAKEVALUE(x, S_MC_BANK2_MAP)
#घोषणा G_MC_BANK2_MAP(x)	    _SB_GETVALUE(x, S_MC_BANK2_MAP, M_MC_BANK2_MAP)

#घोषणा K_MC_BANK2_MAP_DEFAULT	    0x09
#घोषणा V_MC_BANK2_MAP_DEFAULT	    V_MC_BANK2_MAP(K_MC_BANK2_MAP_DEFAULT)

#घोषणा S_MC_BANK3_MAP		    28
#घोषणा M_MC_BANK3_MAP		    _SB_MAKEMASK(4, S_MC_BANK3_MAP)
#घोषणा V_MC_BANK3_MAP(x)	    _SB_MAKEVALUE(x, S_MC_BANK3_MAP)
#घोषणा G_MC_BANK3_MAP(x)	    _SB_GETVALUE(x, S_MC_BANK3_MAP, M_MC_BANK3_MAP)

#घोषणा K_MC_BANK3_MAP_DEFAULT	    0x0C
#घोषणा V_MC_BANK3_MAP_DEFAULT	    V_MC_BANK3_MAP(K_MC_BANK3_MAP_DEFAULT)

#घोषणा M_MC_RESERVED1		    _SB_MAKEMASK(8, 32)

#घोषणा S_MC_QUEUE_SIZE		    40
#घोषणा M_MC_QUEUE_SIZE		    _SB_MAKEMASK(4, S_MC_QUEUE_SIZE)
#घोषणा V_MC_QUEUE_SIZE(x)	    _SB_MAKEVALUE(x, S_MC_QUEUE_SIZE)
#घोषणा G_MC_QUEUE_SIZE(x)	    _SB_GETVALUE(x, S_MC_QUEUE_SIZE, M_MC_QUEUE_SIZE)
#घोषणा V_MC_QUEUE_SIZE_DEFAULT	    V_MC_QUEUE_SIZE(0x0A)

#घोषणा S_MC_AGE_LIMIT		    44
#घोषणा M_MC_AGE_LIMIT		    _SB_MAKEMASK(4, S_MC_AGE_LIMIT)
#घोषणा V_MC_AGE_LIMIT(x)	    _SB_MAKEVALUE(x, S_MC_AGE_LIMIT)
#घोषणा G_MC_AGE_LIMIT(x)	    _SB_GETVALUE(x, S_MC_AGE_LIMIT, M_MC_AGE_LIMIT)
#घोषणा V_MC_AGE_LIMIT_DEFAULT	    V_MC_AGE_LIMIT(8)

#घोषणा S_MC_WR_LIMIT		    48
#घोषणा M_MC_WR_LIMIT		    _SB_MAKEMASK(4, S_MC_WR_LIMIT)
#घोषणा V_MC_WR_LIMIT(x)	    _SB_MAKEVALUE(x, S_MC_WR_LIMIT)
#घोषणा G_MC_WR_LIMIT(x)	    _SB_GETVALUE(x, S_MC_WR_LIMIT, M_MC_WR_LIMIT)
#घोषणा V_MC_WR_LIMIT_DEFAULT	    V_MC_WR_LIMIT(5)

#घोषणा M_MC_IOB1HIGHPRIORITY	    _SB_MAKEMASK1(52)

#घोषणा M_MC_RESERVED2		    _SB_MAKEMASK(3, 53)

#घोषणा S_MC_CS_MODE		    56
#घोषणा M_MC_CS_MODE		    _SB_MAKEMASK(4, S_MC_CS_MODE)
#घोषणा V_MC_CS_MODE(x)		    _SB_MAKEVALUE(x, S_MC_CS_MODE)
#घोषणा G_MC_CS_MODE(x)		    _SB_GETVALUE(x, S_MC_CS_MODE, M_MC_CS_MODE)

#घोषणा K_MC_CS_MODE_MSB_CS	    0
#घोषणा K_MC_CS_MODE_INTLV_CS	    15
#घोषणा K_MC_CS_MODE_MIXED_CS_10    12
#घोषणा K_MC_CS_MODE_MIXED_CS_30    6
#घोषणा K_MC_CS_MODE_MIXED_CS_32    3

#घोषणा V_MC_CS_MODE_MSB_CS	    V_MC_CS_MODE(K_MC_CS_MODE_MSB_CS)
#घोषणा V_MC_CS_MODE_INTLV_CS	    V_MC_CS_MODE(K_MC_CS_MODE_INTLV_CS)
#घोषणा V_MC_CS_MODE_MIXED_CS_10    V_MC_CS_MODE(K_MC_CS_MODE_MIXED_CS_10)
#घोषणा V_MC_CS_MODE_MIXED_CS_30    V_MC_CS_MODE(K_MC_CS_MODE_MIXED_CS_30)
#घोषणा V_MC_CS_MODE_MIXED_CS_32    V_MC_CS_MODE(K_MC_CS_MODE_MIXED_CS_32)

#घोषणा M_MC_ECC_DISABLE	    _SB_MAKEMASK1(60)
#घोषणा M_MC_BERR_DISABLE	    _SB_MAKEMASK1(61)
#घोषणा M_MC_FORCE_SEQ		    _SB_MAKEMASK1(62)
#घोषणा M_MC_DEBUG		    _SB_MAKEMASK1(63)

#घोषणा V_MC_CONFIG_DEFAULT	V_MC_WR_LIMIT_DEFAULT | V_MC_AGE_LIMIT_DEFAULT | \
				V_MC_BANK0_MAP_DEFAULT | V_MC_BANK1_MAP_DEFAULT | \
				V_MC_BANK2_MAP_DEFAULT | V_MC_BANK3_MAP_DEFAULT | V_MC_CHANNEL_SEL(0) | \
				M_MC_IOB1HIGHPRIORITY | V_MC_QUEUE_SIZE_DEFAULT


/*
 * Memory घड़ी config रेजिस्टर (Table 6-15)
 *
 * Note: this field has been updated to be consistent with the errata to 0.2
 */

#घोषणा S_MC_CLK_RATIO		    0
#घोषणा M_MC_CLK_RATIO		    _SB_MAKEMASK(4, S_MC_CLK_RATIO)
#घोषणा V_MC_CLK_RATIO(x)	    _SB_MAKEVALUE(x, S_MC_CLK_RATIO)
#घोषणा G_MC_CLK_RATIO(x)	    _SB_GETVALUE(x, S_MC_CLK_RATIO, M_MC_CLK_RATIO)

#घोषणा K_MC_CLK_RATIO_2X	    4
#घोषणा K_MC_CLK_RATIO_25X	    5
#घोषणा K_MC_CLK_RATIO_3X	    6
#घोषणा K_MC_CLK_RATIO_35X	    7
#घोषणा K_MC_CLK_RATIO_4X	    8
#घोषणा K_MC_CLK_RATIO_45X	    9

#घोषणा V_MC_CLK_RATIO_2X	    V_MC_CLK_RATIO(K_MC_CLK_RATIO_2X)
#घोषणा V_MC_CLK_RATIO_25X	    V_MC_CLK_RATIO(K_MC_CLK_RATIO_25X)
#घोषणा V_MC_CLK_RATIO_3X	    V_MC_CLK_RATIO(K_MC_CLK_RATIO_3X)
#घोषणा V_MC_CLK_RATIO_35X	    V_MC_CLK_RATIO(K_MC_CLK_RATIO_35X)
#घोषणा V_MC_CLK_RATIO_4X	    V_MC_CLK_RATIO(K_MC_CLK_RATIO_4X)
#घोषणा V_MC_CLK_RATIO_45X	    V_MC_CLK_RATIO(K_MC_CLK_RATIO_45X)
#घोषणा V_MC_CLK_RATIO_DEFAULT	    V_MC_CLK_RATIO_25X

#घोषणा S_MC_REF_RATE		     8
#घोषणा M_MC_REF_RATE		     _SB_MAKEMASK(8, S_MC_REF_RATE)
#घोषणा V_MC_REF_RATE(x)	     _SB_MAKEVALUE(x, S_MC_REF_RATE)
#घोषणा G_MC_REF_RATE(x)	     _SB_GETVALUE(x, S_MC_REF_RATE, M_MC_REF_RATE)

#घोषणा K_MC_REF_RATE_100MHz	     0x62
#घोषणा K_MC_REF_RATE_133MHz	     0x81
#घोषणा K_MC_REF_RATE_200MHz	     0xC4

#घोषणा V_MC_REF_RATE_100MHz	     V_MC_REF_RATE(K_MC_REF_RATE_100MHz)
#घोषणा V_MC_REF_RATE_133MHz	     V_MC_REF_RATE(K_MC_REF_RATE_133MHz)
#घोषणा V_MC_REF_RATE_200MHz	     V_MC_REF_RATE(K_MC_REF_RATE_200MHz)
#घोषणा V_MC_REF_RATE_DEFAULT	     V_MC_REF_RATE_100MHz

#घोषणा S_MC_CLOCK_DRIVE	     16
#घोषणा M_MC_CLOCK_DRIVE	     _SB_MAKEMASK(4, S_MC_CLOCK_DRIVE)
#घोषणा V_MC_CLOCK_DRIVE(x)	     _SB_MAKEVALUE(x, S_MC_CLOCK_DRIVE)
#घोषणा G_MC_CLOCK_DRIVE(x)	     _SB_GETVALUE(x, S_MC_CLOCK_DRIVE, M_MC_CLOCK_DRIVE)
#घोषणा V_MC_CLOCK_DRIVE_DEFAULT     V_MC_CLOCK_DRIVE(0xF)

#घोषणा S_MC_DATA_DRIVE		     20
#घोषणा M_MC_DATA_DRIVE		     _SB_MAKEMASK(4, S_MC_DATA_DRIVE)
#घोषणा V_MC_DATA_DRIVE(x)	     _SB_MAKEVALUE(x, S_MC_DATA_DRIVE)
#घोषणा G_MC_DATA_DRIVE(x)	     _SB_GETVALUE(x, S_MC_DATA_DRIVE, M_MC_DATA_DRIVE)
#घोषणा V_MC_DATA_DRIVE_DEFAULT	     V_MC_DATA_DRIVE(0x0)

#घोषणा S_MC_ADDR_DRIVE		     24
#घोषणा M_MC_ADDR_DRIVE		     _SB_MAKEMASK(4, S_MC_ADDR_DRIVE)
#घोषणा V_MC_ADDR_DRIVE(x)	     _SB_MAKEVALUE(x, S_MC_ADDR_DRIVE)
#घोषणा G_MC_ADDR_DRIVE(x)	     _SB_GETVALUE(x, S_MC_ADDR_DRIVE, M_MC_ADDR_DRIVE)
#घोषणा V_MC_ADDR_DRIVE_DEFAULT	     V_MC_ADDR_DRIVE(0x0)

#अगर SIBYTE_HDR_FEATURE(1250, PASS3) || SIBYTE_HDR_FEATURE(112x, PASS1)
#घोषणा M_MC_REF_DISABLE	     _SB_MAKEMASK1(30)
#पूर्ण_अगर /* 1250 PASS3 || 112x PASS1 */

#घोषणा M_MC_DLL_BYPASS		     _SB_MAKEMASK1(31)

#घोषणा S_MC_DQI_SKEW		    32
#घोषणा M_MC_DQI_SKEW		    _SB_MAKEMASK(8, S_MC_DQI_SKEW)
#घोषणा V_MC_DQI_SKEW(x)	    _SB_MAKEVALUE(x, S_MC_DQI_SKEW)
#घोषणा G_MC_DQI_SKEW(x)	    _SB_GETVALUE(x, S_MC_DQI_SKEW, M_MC_DQI_SKEW)
#घोषणा V_MC_DQI_SKEW_DEFAULT	    V_MC_DQI_SKEW(0)

#घोषणा S_MC_DQO_SKEW		    40
#घोषणा M_MC_DQO_SKEW		    _SB_MAKEMASK(8, S_MC_DQO_SKEW)
#घोषणा V_MC_DQO_SKEW(x)	    _SB_MAKEVALUE(x, S_MC_DQO_SKEW)
#घोषणा G_MC_DQO_SKEW(x)	    _SB_GETVALUE(x, S_MC_DQO_SKEW, M_MC_DQO_SKEW)
#घोषणा V_MC_DQO_SKEW_DEFAULT	    V_MC_DQO_SKEW(0)

#घोषणा S_MC_ADDR_SKEW		     48
#घोषणा M_MC_ADDR_SKEW		     _SB_MAKEMASK(8, S_MC_ADDR_SKEW)
#घोषणा V_MC_ADDR_SKEW(x)	     _SB_MAKEVALUE(x, S_MC_ADDR_SKEW)
#घोषणा G_MC_ADDR_SKEW(x)	     _SB_GETVALUE(x, S_MC_ADDR_SKEW, M_MC_ADDR_SKEW)
#घोषणा V_MC_ADDR_SKEW_DEFAULT	     V_MC_ADDR_SKEW(0x0F)

#घोषणा S_MC_DLL_DEFAULT	     56
#घोषणा M_MC_DLL_DEFAULT	     _SB_MAKEMASK(8, S_MC_DLL_DEFAULT)
#घोषणा V_MC_DLL_DEFAULT(x)	     _SB_MAKEVALUE(x, S_MC_DLL_DEFAULT)
#घोषणा G_MC_DLL_DEFAULT(x)	     _SB_GETVALUE(x, S_MC_DLL_DEFAULT, M_MC_DLL_DEFAULT)
#घोषणा V_MC_DLL_DEFAULT_DEFAULT     V_MC_DLL_DEFAULT(0x10)

#घोषणा V_MC_CLKCONFIG_DEFAULT	     V_MC_DLL_DEFAULT_DEFAULT |	 \
				     V_MC_ADDR_SKEW_DEFAULT | \
				     V_MC_DQO_SKEW_DEFAULT | \
				     V_MC_DQI_SKEW_DEFAULT | \
				     V_MC_ADDR_DRIVE_DEFAULT | \
				     V_MC_DATA_DRIVE_DEFAULT | \
				     V_MC_CLOCK_DRIVE_DEFAULT | \
				     V_MC_REF_RATE_DEFAULT



/*
 * DRAM Command Register (Table 6-13)
 */

#घोषणा S_MC_COMMAND		    0
#घोषणा M_MC_COMMAND		    _SB_MAKEMASK(4, S_MC_COMMAND)
#घोषणा V_MC_COMMAND(x)		    _SB_MAKEVALUE(x, S_MC_COMMAND)
#घोषणा G_MC_COMMAND(x)		    _SB_GETVALUE(x, S_MC_COMMAND, M_MC_COMMAND)

#घोषणा K_MC_COMMAND_EMRS	    0
#घोषणा K_MC_COMMAND_MRS	    1
#घोषणा K_MC_COMMAND_PRE	    2
#घोषणा K_MC_COMMAND_AR		    3
#घोषणा K_MC_COMMAND_SETRFSH	    4
#घोषणा K_MC_COMMAND_CLRRFSH	    5
#घोषणा K_MC_COMMAND_SETPWRDN	    6
#घोषणा K_MC_COMMAND_CLRPWRDN	    7

#घोषणा V_MC_COMMAND_EMRS	    V_MC_COMMAND(K_MC_COMMAND_EMRS)
#घोषणा V_MC_COMMAND_MRS	    V_MC_COMMAND(K_MC_COMMAND_MRS)
#घोषणा V_MC_COMMAND_PRE	    V_MC_COMMAND(K_MC_COMMAND_PRE)
#घोषणा V_MC_COMMAND_AR		    V_MC_COMMAND(K_MC_COMMAND_AR)
#घोषणा V_MC_COMMAND_SETRFSH	    V_MC_COMMAND(K_MC_COMMAND_SETRFSH)
#घोषणा V_MC_COMMAND_CLRRFSH	    V_MC_COMMAND(K_MC_COMMAND_CLRRFSH)
#घोषणा V_MC_COMMAND_SETPWRDN	    V_MC_COMMAND(K_MC_COMMAND_SETPWRDN)
#घोषणा V_MC_COMMAND_CLRPWRDN	    V_MC_COMMAND(K_MC_COMMAND_CLRPWRDN)

#घोषणा M_MC_CS0		    _SB_MAKEMASK1(4)
#घोषणा M_MC_CS1		    _SB_MAKEMASK1(5)
#घोषणा M_MC_CS2		    _SB_MAKEMASK1(6)
#घोषणा M_MC_CS3		    _SB_MAKEMASK1(7)

/*
 * DRAM Mode Register (Table 6-14)
 */

#घोषणा S_MC_EMODE		    0
#घोषणा M_MC_EMODE		    _SB_MAKEMASK(15, S_MC_EMODE)
#घोषणा V_MC_EMODE(x)		    _SB_MAKEVALUE(x, S_MC_EMODE)
#घोषणा G_MC_EMODE(x)		    _SB_GETVALUE(x, S_MC_EMODE, M_MC_EMODE)
#घोषणा V_MC_EMODE_DEFAULT	    V_MC_EMODE(0)

#घोषणा S_MC_MODE		    16
#घोषणा M_MC_MODE		    _SB_MAKEMASK(15, S_MC_MODE)
#घोषणा V_MC_MODE(x)		    _SB_MAKEVALUE(x, S_MC_MODE)
#घोषणा G_MC_MODE(x)		    _SB_GETVALUE(x, S_MC_MODE, M_MC_MODE)
#घोषणा V_MC_MODE_DEFAULT	    V_MC_MODE(0x22)

#घोषणा S_MC_DRAM_TYPE		    32
#घोषणा M_MC_DRAM_TYPE		    _SB_MAKEMASK(3, S_MC_DRAM_TYPE)
#घोषणा V_MC_DRAM_TYPE(x)	    _SB_MAKEVALUE(x, S_MC_DRAM_TYPE)
#घोषणा G_MC_DRAM_TYPE(x)	    _SB_GETVALUE(x, S_MC_DRAM_TYPE, M_MC_DRAM_TYPE)

#घोषणा K_MC_DRAM_TYPE_JEDEC	    0
#घोषणा K_MC_DRAM_TYPE_FCRAM	    1
#घोषणा K_MC_DRAM_TYPE_SGRAM	    2

#घोषणा V_MC_DRAM_TYPE_JEDEC	    V_MC_DRAM_TYPE(K_MC_DRAM_TYPE_JEDEC)
#घोषणा V_MC_DRAM_TYPE_FCRAM	    V_MC_DRAM_TYPE(K_MC_DRAM_TYPE_FCRAM)
#घोषणा V_MC_DRAM_TYPE_SGRAM	    V_MC_DRAM_TYPE(K_MC_DRAM_TYPE_SGRAM)

#घोषणा M_MC_EXTERNALDECODE	    _SB_MAKEMASK1(35)

#अगर SIBYTE_HDR_FEATURE(1250, PASS3) || SIBYTE_HDR_FEATURE(112x, PASS1)
#घोषणा M_MC_PRE_ON_A8		    _SB_MAKEMASK1(36)
#घोषणा M_MC_RAM_WITH_A13	    _SB_MAKEMASK1(37)
#पूर्ण_अगर /* 1250 PASS3 || 112x PASS1 */



/*
 * SDRAM Timing Register  (Table 6-15)
 */

#घोषणा M_MC_w2rIDLE_TWOCYCLES	  _SB_MAKEMASK1(60)
#घोषणा M_MC_r2wIDLE_TWOCYCLES	  _SB_MAKEMASK1(61)
#घोषणा M_MC_r2rIDLE_TWOCYCLES	  _SB_MAKEMASK1(62)

#घोषणा S_MC_tFIFO		  56
#घोषणा M_MC_tFIFO		  _SB_MAKEMASK(4, S_MC_tFIFO)
#घोषणा V_MC_tFIFO(x)		  _SB_MAKEVALUE(x, S_MC_tFIFO)
#घोषणा G_MC_tFIFO(x)		  _SB_GETVALUE(x, S_MC_tFIFO, M_MC_tFIFO)
#घोषणा K_MC_tFIFO_DEFAULT	  1
#घोषणा V_MC_tFIFO_DEFAULT	  V_MC_tFIFO(K_MC_tFIFO_DEFAULT)

#घोषणा S_MC_tRFC		  52
#घोषणा M_MC_tRFC		  _SB_MAKEMASK(4, S_MC_tRFC)
#घोषणा V_MC_tRFC(x)		  _SB_MAKEVALUE(x, S_MC_tRFC)
#घोषणा G_MC_tRFC(x)		  _SB_GETVALUE(x, S_MC_tRFC, M_MC_tRFC)
#घोषणा K_MC_tRFC_DEFAULT	  12
#घोषणा V_MC_tRFC_DEFAULT	  V_MC_tRFC(K_MC_tRFC_DEFAULT)

#अगर SIBYTE_HDR_FEATURE(1250, PASS3)
#घोषणा M_MC_tRFC_PLUS16	  _SB_MAKEMASK1(51)	/* 1250C3 and later.  */
#पूर्ण_अगर

#घोषणा S_MC_tCwCr		  40
#घोषणा M_MC_tCwCr		  _SB_MAKEMASK(4, S_MC_tCwCr)
#घोषणा V_MC_tCwCr(x)		  _SB_MAKEVALUE(x, S_MC_tCwCr)
#घोषणा G_MC_tCwCr(x)		  _SB_GETVALUE(x, S_MC_tCwCr, M_MC_tCwCr)
#घोषणा K_MC_tCwCr_DEFAULT	  4
#घोषणा V_MC_tCwCr_DEFAULT	  V_MC_tCwCr(K_MC_tCwCr_DEFAULT)

#घोषणा S_MC_tRCr		  28
#घोषणा M_MC_tRCr		  _SB_MAKEMASK(4, S_MC_tRCr)
#घोषणा V_MC_tRCr(x)		  _SB_MAKEVALUE(x, S_MC_tRCr)
#घोषणा G_MC_tRCr(x)		  _SB_GETVALUE(x, S_MC_tRCr, M_MC_tRCr)
#घोषणा K_MC_tRCr_DEFAULT	  9
#घोषणा V_MC_tRCr_DEFAULT	  V_MC_tRCr(K_MC_tRCr_DEFAULT)

#घोषणा S_MC_tRCw		  24
#घोषणा M_MC_tRCw		  _SB_MAKEMASK(4, S_MC_tRCw)
#घोषणा V_MC_tRCw(x)		  _SB_MAKEVALUE(x, S_MC_tRCw)
#घोषणा G_MC_tRCw(x)		  _SB_GETVALUE(x, S_MC_tRCw, M_MC_tRCw)
#घोषणा K_MC_tRCw_DEFAULT	  10
#घोषणा V_MC_tRCw_DEFAULT	  V_MC_tRCw(K_MC_tRCw_DEFAULT)

#घोषणा S_MC_tRRD		  20
#घोषणा M_MC_tRRD		  _SB_MAKEMASK(4, S_MC_tRRD)
#घोषणा V_MC_tRRD(x)		  _SB_MAKEVALUE(x, S_MC_tRRD)
#घोषणा G_MC_tRRD(x)		  _SB_GETVALUE(x, S_MC_tRRD, M_MC_tRRD)
#घोषणा K_MC_tRRD_DEFAULT	  2
#घोषणा V_MC_tRRD_DEFAULT	  V_MC_tRRD(K_MC_tRRD_DEFAULT)

#घोषणा S_MC_tRP		  16
#घोषणा M_MC_tRP		  _SB_MAKEMASK(4, S_MC_tRP)
#घोषणा V_MC_tRP(x)		  _SB_MAKEVALUE(x, S_MC_tRP)
#घोषणा G_MC_tRP(x)		  _SB_GETVALUE(x, S_MC_tRP, M_MC_tRP)
#घोषणा K_MC_tRP_DEFAULT	  4
#घोषणा V_MC_tRP_DEFAULT	  V_MC_tRP(K_MC_tRP_DEFAULT)

#घोषणा S_MC_tCwD		  8
#घोषणा M_MC_tCwD		  _SB_MAKEMASK(4, S_MC_tCwD)
#घोषणा V_MC_tCwD(x)		  _SB_MAKEVALUE(x, S_MC_tCwD)
#घोषणा G_MC_tCwD(x)		  _SB_GETVALUE(x, S_MC_tCwD, M_MC_tCwD)
#घोषणा K_MC_tCwD_DEFAULT	  1
#घोषणा V_MC_tCwD_DEFAULT	  V_MC_tCwD(K_MC_tCwD_DEFAULT)

#घोषणा M_tCrDh			  _SB_MAKEMASK1(7)
#घोषणा M_MC_tCrDh		  M_tCrDh

#घोषणा S_MC_tCrD		  4
#घोषणा M_MC_tCrD		  _SB_MAKEMASK(3, S_MC_tCrD)
#घोषणा V_MC_tCrD(x)		  _SB_MAKEVALUE(x, S_MC_tCrD)
#घोषणा G_MC_tCrD(x)		  _SB_GETVALUE(x, S_MC_tCrD, M_MC_tCrD)
#घोषणा K_MC_tCrD_DEFAULT	  2
#घोषणा V_MC_tCrD_DEFAULT	  V_MC_tCrD(K_MC_tCrD_DEFAULT)

#घोषणा S_MC_tRCD		  0
#घोषणा M_MC_tRCD		  _SB_MAKEMASK(4, S_MC_tRCD)
#घोषणा V_MC_tRCD(x)		  _SB_MAKEVALUE(x, S_MC_tRCD)
#घोषणा G_MC_tRCD(x)		  _SB_GETVALUE(x, S_MC_tRCD, M_MC_tRCD)
#घोषणा K_MC_tRCD_DEFAULT	  3
#घोषणा V_MC_tRCD_DEFAULT	  V_MC_tRCD(K_MC_tRCD_DEFAULT)

#घोषणा V_MC_TIMING_DEFAULT	V_MC_tFIFO(K_MC_tFIFO_DEFAULT) | \
				V_MC_tRFC(K_MC_tRFC_DEFAULT) | \
				V_MC_tCwCr(K_MC_tCwCr_DEFAULT) | \
				V_MC_tRCr(K_MC_tRCr_DEFAULT) | \
				V_MC_tRCw(K_MC_tRCw_DEFAULT) | \
				V_MC_tRRD(K_MC_tRRD_DEFAULT) | \
				V_MC_tRP(K_MC_tRP_DEFAULT) | \
				V_MC_tCwD(K_MC_tCwD_DEFAULT) | \
				V_MC_tCrD(K_MC_tCrD_DEFAULT) | \
				V_MC_tRCD(K_MC_tRCD_DEFAULT) | \
				M_MC_r2rIDLE_TWOCYCLES

/*
 * Errata says these are not the शेष
 *				 M_MC_w2rIDLE_TWOCYCLES | \
 *				 M_MC_r2wIDLE_TWOCYCLES | \
 */


/*
 * Chip Select Start Address Register (Table 6-17)
 */

#घोषणा S_MC_CS0_START		    0
#घोषणा M_MC_CS0_START		    _SB_MAKEMASK(16, S_MC_CS0_START)
#घोषणा V_MC_CS0_START(x)	    _SB_MAKEVALUE(x, S_MC_CS0_START)
#घोषणा G_MC_CS0_START(x)	    _SB_GETVALUE(x, S_MC_CS0_START, M_MC_CS0_START)

#घोषणा S_MC_CS1_START		    16
#घोषणा M_MC_CS1_START		    _SB_MAKEMASK(16, S_MC_CS1_START)
#घोषणा V_MC_CS1_START(x)	    _SB_MAKEVALUE(x, S_MC_CS1_START)
#घोषणा G_MC_CS1_START(x)	    _SB_GETVALUE(x, S_MC_CS1_START, M_MC_CS1_START)

#घोषणा S_MC_CS2_START		    32
#घोषणा M_MC_CS2_START		    _SB_MAKEMASK(16, S_MC_CS2_START)
#घोषणा V_MC_CS2_START(x)	    _SB_MAKEVALUE(x, S_MC_CS2_START)
#घोषणा G_MC_CS2_START(x)	    _SB_GETVALUE(x, S_MC_CS2_START, M_MC_CS2_START)

#घोषणा S_MC_CS3_START		    48
#घोषणा M_MC_CS3_START		    _SB_MAKEMASK(16, S_MC_CS3_START)
#घोषणा V_MC_CS3_START(x)	    _SB_MAKEVALUE(x, S_MC_CS3_START)
#घोषणा G_MC_CS3_START(x)	    _SB_GETVALUE(x, S_MC_CS3_START, M_MC_CS3_START)

/*
 * Chip Select End Address Register (Table 6-18)
 */

#घोषणा S_MC_CS0_END		    0
#घोषणा M_MC_CS0_END		    _SB_MAKEMASK(16, S_MC_CS0_END)
#घोषणा V_MC_CS0_END(x)		    _SB_MAKEVALUE(x, S_MC_CS0_END)
#घोषणा G_MC_CS0_END(x)		    _SB_GETVALUE(x, S_MC_CS0_END, M_MC_CS0_END)

#घोषणा S_MC_CS1_END		    16
#घोषणा M_MC_CS1_END		    _SB_MAKEMASK(16, S_MC_CS1_END)
#घोषणा V_MC_CS1_END(x)		    _SB_MAKEVALUE(x, S_MC_CS1_END)
#घोषणा G_MC_CS1_END(x)		    _SB_GETVALUE(x, S_MC_CS1_END, M_MC_CS1_END)

#घोषणा S_MC_CS2_END		    32
#घोषणा M_MC_CS2_END		    _SB_MAKEMASK(16, S_MC_CS2_END)
#घोषणा V_MC_CS2_END(x)		    _SB_MAKEVALUE(x, S_MC_CS2_END)
#घोषणा G_MC_CS2_END(x)		    _SB_GETVALUE(x, S_MC_CS2_END, M_MC_CS2_END)

#घोषणा S_MC_CS3_END		    48
#घोषणा M_MC_CS3_END		    _SB_MAKEMASK(16, S_MC_CS3_END)
#घोषणा V_MC_CS3_END(x)		    _SB_MAKEVALUE(x, S_MC_CS3_END)
#घोषणा G_MC_CS3_END(x)		    _SB_GETVALUE(x, S_MC_CS3_END, M_MC_CS3_END)

/*
 * Chip Select Interleave Register (Table 6-19)
 */

#घोषणा S_MC_INTLV_RESERVED	    0
#घोषणा M_MC_INTLV_RESERVED	    _SB_MAKEMASK(5, S_MC_INTLV_RESERVED)

#घोषणा S_MC_INTERLEAVE		    7
#घोषणा M_MC_INTERLEAVE		    _SB_MAKEMASK(18, S_MC_INTERLEAVE)
#घोषणा V_MC_INTERLEAVE(x)	    _SB_MAKEVALUE(x, S_MC_INTERLEAVE)

#घोषणा S_MC_INTLV_MBZ		    25
#घोषणा M_MC_INTLV_MBZ		    _SB_MAKEMASK(39, S_MC_INTLV_MBZ)

/*
 * Row Address Bits Register (Table 6-20)
 */

#घोषणा S_MC_RAS_RESERVED	    0
#घोषणा M_MC_RAS_RESERVED	    _SB_MAKEMASK(5, S_MC_RAS_RESERVED)

#घोषणा S_MC_RAS_SELECT		    12
#घोषणा M_MC_RAS_SELECT		    _SB_MAKEMASK(25, S_MC_RAS_SELECT)
#घोषणा V_MC_RAS_SELECT(x)	    _SB_MAKEVALUE(x, S_MC_RAS_SELECT)

#घोषणा S_MC_RAS_MBZ		    37
#घोषणा M_MC_RAS_MBZ		    _SB_MAKEMASK(27, S_MC_RAS_MBZ)


/*
 * Column Address Bits Register (Table 6-21)
 */

#घोषणा S_MC_CAS_RESERVED	    0
#घोषणा M_MC_CAS_RESERVED	    _SB_MAKEMASK(5, S_MC_CAS_RESERVED)

#घोषणा S_MC_CAS_SELECT		    5
#घोषणा M_MC_CAS_SELECT		    _SB_MAKEMASK(18, S_MC_CAS_SELECT)
#घोषणा V_MC_CAS_SELECT(x)	    _SB_MAKEVALUE(x, S_MC_CAS_SELECT)

#घोषणा S_MC_CAS_MBZ		    23
#घोषणा M_MC_CAS_MBZ		    _SB_MAKEMASK(41, S_MC_CAS_MBZ)


/*
 * Bank Address Address Bits Register (Table 6-22)
 */

#घोषणा S_MC_BA_RESERVED	    0
#घोषणा M_MC_BA_RESERVED	    _SB_MAKEMASK(5, S_MC_BA_RESERVED)

#घोषणा S_MC_BA_SELECT		    5
#घोषणा M_MC_BA_SELECT		    _SB_MAKEMASK(20, S_MC_BA_SELECT)
#घोषणा V_MC_BA_SELECT(x)	    _SB_MAKEVALUE(x, S_MC_BA_SELECT)

#घोषणा S_MC_BA_MBZ		    25
#घोषणा M_MC_BA_MBZ		    _SB_MAKEMASK(39, S_MC_BA_MBZ)

/*
 * Chip Select Attribute Register (Table 6-23)
 */

#घोषणा K_MC_CS_ATTR_CLOSED	    0
#घोषणा K_MC_CS_ATTR_CASCHECK	    1
#घोषणा K_MC_CS_ATTR_HINT	    2
#घोषणा K_MC_CS_ATTR_OPEN	    3

#घोषणा S_MC_CS0_PAGE		    0
#घोषणा M_MC_CS0_PAGE		    _SB_MAKEMASK(2, S_MC_CS0_PAGE)
#घोषणा V_MC_CS0_PAGE(x)	    _SB_MAKEVALUE(x, S_MC_CS0_PAGE)
#घोषणा G_MC_CS0_PAGE(x)	    _SB_GETVALUE(x, S_MC_CS0_PAGE, M_MC_CS0_PAGE)

#घोषणा S_MC_CS1_PAGE		    16
#घोषणा M_MC_CS1_PAGE		    _SB_MAKEMASK(2, S_MC_CS1_PAGE)
#घोषणा V_MC_CS1_PAGE(x)	    _SB_MAKEVALUE(x, S_MC_CS1_PAGE)
#घोषणा G_MC_CS1_PAGE(x)	    _SB_GETVALUE(x, S_MC_CS1_PAGE, M_MC_CS1_PAGE)

#घोषणा S_MC_CS2_PAGE		    32
#घोषणा M_MC_CS2_PAGE		    _SB_MAKEMASK(2, S_MC_CS2_PAGE)
#घोषणा V_MC_CS2_PAGE(x)	    _SB_MAKEVALUE(x, S_MC_CS2_PAGE)
#घोषणा G_MC_CS2_PAGE(x)	    _SB_GETVALUE(x, S_MC_CS2_PAGE, M_MC_CS2_PAGE)

#घोषणा S_MC_CS3_PAGE		    48
#घोषणा M_MC_CS3_PAGE		    _SB_MAKEMASK(2, S_MC_CS3_PAGE)
#घोषणा V_MC_CS3_PAGE(x)	    _SB_MAKEVALUE(x, S_MC_CS3_PAGE)
#घोषणा G_MC_CS3_PAGE(x)	    _SB_GETVALUE(x, S_MC_CS3_PAGE, M_MC_CS3_PAGE)

/*
 * ECC Test ECC Register (Table 6-25)
 */

#घोषणा S_MC_ECC_INVERT		    0
#घोषणा M_MC_ECC_INVERT		    _SB_MAKEMASK(8, S_MC_ECC_INVERT)


#पूर्ण_अगर
