<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 *	Swansea University Computer Society	NET3
 *	
 *	This file declares the स्थिरants of special use with the SLIP/CSLIP/
 *	KISS TNC driver.
 */
 
#अगर_अघोषित __LINUX_SLIP_H
#घोषणा __LINUX_SLIP_H

#घोषणा		SL_MODE_SLIP		0
#घोषणा		SL_MODE_CSLIP		1
#घोषणा 	SL_MODE_KISS		4

#घोषणा		SL_OPT_SIXBIT		2
#घोषणा		SL_OPT_ADAPTIVE		8

/*
 *	VSV = ioctl क्रम keepalive & outfill in SLIP driver 
 */
 
#घोषणा SIOCSKEEPALIVE	(SIOCDEVPRIVATE)		/* Set keepalive समयout in sec */
#घोषणा SIOCGKEEPALIVE	(SIOCDEVPRIVATE+1)		/* Get keepalive समयout */
#घोषणा SIOCSOUTFILL	(SIOCDEVPRIVATE+2)		/* Set outfill समयout */
#घोषणा	SIOCGOUTFILL	(SIOCDEVPRIVATE+3)		/* Get outfill समयout */
#घोषणा SIOCSLEASE	(SIOCDEVPRIVATE+4)		/* Set "leased" line type */
#घोषणा	SIOCGLEASE	(SIOCDEVPRIVATE+5)		/* Get line type */


#पूर्ण_अगर
