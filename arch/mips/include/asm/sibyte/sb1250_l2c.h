<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*  *********************************************************************
    *  SB1250 Board Support Package
    *
    *  L2 Cache स्थिरants and macros		File: sb1250_l2c.h
    *
    *  This module contains स्थिरants useful क्रम manipulating the
    *  level 2 cache.
    *
    *  SB1250 specअगरication level:  User's manual 1/02/02
    *
    *********************************************************************
    *
    *  Copyright 2000,2001,2002,2003
    *  Broadcom Corporation. All rights reserved.
    *
    ********************************************************************* */


#अगर_अघोषित _SB1250_L2C_H
#घोषणा _SB1250_L2C_H

#समावेश <यंत्र/sibyte/sb1250_defs.h>

/*
 * Level 2 Cache Tag रेजिस्टर (Table 5-3)
 */

#घोषणा S_L2C_TAG_MBZ		    0
#घोषणा M_L2C_TAG_MBZ		    _SB_MAKEMASK(5, S_L2C_TAG_MBZ)

#घोषणा S_L2C_TAG_INDEX		    5
#घोषणा M_L2C_TAG_INDEX		    _SB_MAKEMASK(12, S_L2C_TAG_INDEX)
#घोषणा V_L2C_TAG_INDEX(x)	    _SB_MAKEVALUE(x, S_L2C_TAG_INDEX)
#घोषणा G_L2C_TAG_INDEX(x)	    _SB_GETVALUE(x, S_L2C_TAG_INDEX, M_L2C_TAG_INDEX)

#घोषणा S_L2C_TAG_TAG		    17
#घोषणा M_L2C_TAG_TAG		    _SB_MAKEMASK(23, S_L2C_TAG_TAG)
#घोषणा V_L2C_TAG_TAG(x)	    _SB_MAKEVALUE(x, S_L2C_TAG_TAG)
#घोषणा G_L2C_TAG_TAG(x)	    _SB_GETVALUE(x, S_L2C_TAG_TAG, M_L2C_TAG_TAG)

#घोषणा S_L2C_TAG_ECC		    40
#घोषणा M_L2C_TAG_ECC		    _SB_MAKEMASK(6, S_L2C_TAG_ECC)
#घोषणा V_L2C_TAG_ECC(x)	    _SB_MAKEVALUE(x, S_L2C_TAG_ECC)
#घोषणा G_L2C_TAG_ECC(x)	    _SB_GETVALUE(x, S_L2C_TAG_ECC, M_L2C_TAG_ECC)

#घोषणा S_L2C_TAG_WAY		    46
#घोषणा M_L2C_TAG_WAY		    _SB_MAKEMASK(2, S_L2C_TAG_WAY)
#घोषणा V_L2C_TAG_WAY(x)	    _SB_MAKEVALUE(x, S_L2C_TAG_WAY)
#घोषणा G_L2C_TAG_WAY(x)	    _SB_GETVALUE(x, S_L2C_TAG_WAY, M_L2C_TAG_WAY)

#घोषणा M_L2C_TAG_सूचीTY		    _SB_MAKEMASK1(48)
#घोषणा M_L2C_TAG_VALID		    _SB_MAKEMASK1(49)

/*
 * Format of level 2 cache management address (table 5-2)
 */

#घोषणा S_L2C_MGMT_INDEX	    5
#घोषणा M_L2C_MGMT_INDEX	    _SB_MAKEMASK(12, S_L2C_MGMT_INDEX)
#घोषणा V_L2C_MGMT_INDEX(x)	    _SB_MAKEVALUE(x, S_L2C_MGMT_INDEX)
#घोषणा G_L2C_MGMT_INDEX(x)	    _SB_GETVALUE(x, S_L2C_MGMT_INDEX, M_L2C_MGMT_INDEX)

#घोषणा S_L2C_MGMT_QUADRANT	    15
#घोषणा M_L2C_MGMT_QUADRANT	    _SB_MAKEMASK(2, S_L2C_MGMT_QUADRANT)
#घोषणा V_L2C_MGMT_QUADRANT(x)	    _SB_MAKEVALUE(x, S_L2C_MGMT_QUADRANT)
#घोषणा G_L2C_MGMT_QUADRANT(x)	    _SB_GETVALUE(x, S_L2C_MGMT_QUADRANT, M_L2C_MGMT_QUADRANT)

#घोषणा S_L2C_MGMT_HALF		    16
#घोषणा M_L2C_MGMT_HALF		    _SB_MAKEMASK(1, S_L2C_MGMT_HALF)

#घोषणा S_L2C_MGMT_WAY		    17
#घोषणा M_L2C_MGMT_WAY		    _SB_MAKEMASK(2, S_L2C_MGMT_WAY)
#घोषणा V_L2C_MGMT_WAY(x)	    _SB_MAKEVALUE(x, S_L2C_MGMT_WAY)
#घोषणा G_L2C_MGMT_WAY(x)	    _SB_GETVALUE(x, S_L2C_MGMT_WAY, M_L2C_MGMT_WAY)

#घोषणा S_L2C_MGMT_ECC_DIAG	    21
#घोषणा M_L2C_MGMT_ECC_DIAG	    _SB_MAKEMASK(2, S_L2C_MGMT_ECC_DIAG)
#घोषणा V_L2C_MGMT_ECC_DIAG(x)	    _SB_MAKEVALUE(x, S_L2C_MGMT_ECC_DIAG)
#घोषणा G_L2C_MGMT_ECC_DIAG(x)	    _SB_GETVALUE(x, S_L2C_MGMT_ECC_DIAG, M_L2C_MGMT_ECC_DIAG)

#घोषणा S_L2C_MGMT_TAG		    23
#घोषणा M_L2C_MGMT_TAG		    _SB_MAKEMASK(4, S_L2C_MGMT_TAG)
#घोषणा V_L2C_MGMT_TAG(x)	    _SB_MAKEVALUE(x, S_L2C_MGMT_TAG)
#घोषणा G_L2C_MGMT_TAG(x)	    _SB_GETVALUE(x, S_L2C_MGMT_TAG, M_L2C_MGMT_TAG)

#घोषणा M_L2C_MGMT_सूचीTY	    _SB_MAKEMASK1(19)
#घोषणा M_L2C_MGMT_VALID	    _SB_MAKEMASK1(20)

#घोषणा A_L2C_MGMT_TAG_BASE	    0x00D0000000

#घोषणा L2C_ENTRIES_PER_WAY	  4096
#घोषणा L2C_NUM_WAYS		  4


#अगर SIBYTE_HDR_FEATURE(1250, PASS3) || SIBYTE_HDR_FEATURE(112x, PASS1)
/*
 * L2 Read Misc. रेजिस्टर (A_L2_READ_MISC)
 */
#घोषणा S_L2C_MISC_NO_WAY		10
#घोषणा M_L2C_MISC_NO_WAY		_SB_MAKEMASK(4, S_L2C_MISC_NO_WAY)
#घोषणा V_L2C_MISC_NO_WAY(x)		_SB_MAKEVALUE(x, S_L2C_MISC_NO_WAY)
#घोषणा G_L2C_MISC_NO_WAY(x)		_SB_GETVALUE(x, S_L2C_MISC_NO_WAY, M_L2C_MISC_NO_WAY)

#घोषणा M_L2C_MISC_ECC_CLEANUP_DIS	_SB_MAKEMASK1(9)
#घोषणा M_L2C_MISC_MC_PRIO_LOW		_SB_MAKEMASK1(8)
#घोषणा M_L2C_MISC_SOFT_DISABLE_T	_SB_MAKEMASK1(7)
#घोषणा M_L2C_MISC_SOFT_DISABLE_B	_SB_MAKEMASK1(6)
#घोषणा M_L2C_MISC_SOFT_DISABLE_R	_SB_MAKEMASK1(5)
#घोषणा M_L2C_MISC_SOFT_DISABLE_L	_SB_MAKEMASK1(4)
#घोषणा M_L2C_MISC_SCACHE_DISABLE_T	_SB_MAKEMASK1(3)
#घोषणा M_L2C_MISC_SCACHE_DISABLE_B	_SB_MAKEMASK1(2)
#घोषणा M_L2C_MISC_SCACHE_DISABLE_R	_SB_MAKEMASK1(1)
#घोषणा M_L2C_MISC_SCACHE_DISABLE_L	_SB_MAKEMASK1(0)
#पूर्ण_अगर /* 1250 PASS3 || 112x PASS1 */


#पूर्ण_अगर
