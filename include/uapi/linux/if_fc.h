<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ WITH Linux-syscall-note */
/*
 * INET		An implementation of the TCP/IP protocol suite क्रम the LINUX
 *		operating प्रणाली.  INET is implemented using the  BSD Socket
 *		पूर्णांकerface as the means of communication with the user level.
 *
 *		Global definitions क्रम Fibre Channel.
 *
 * Version:	@(#)अगर_fc.h	0.0	11/20/98
 *
 * Author:	Fred N. van Kempen, <waltje@uWalt.NL.Mugnet.ORG>
 *		Donald Becker, <becker@super.org>
 *    Peter De Schrijver, <stud11@cc4.kuleuven.ac.be>
 *	  Vineet Abraham, <vma@iol.unh.edu>
 *
 *		This program is मुक्त software; you can redistribute it and/or
 *		modअगरy it under the terms of the GNU General Public License
 *		as published by the Free Software Foundation; either version
 *		2 of the License, or (at your option) any later version.
 */
#अगर_अघोषित _LINUX_IF_FC_H
#घोषणा _LINUX_IF_FC_H

#समावेश <linux/types.h>

#घोषणा FC_ALEN	6		/* Octets in one ethernet addr	 */
#घोषणा FC_HLEN   (माप(काष्ठा fch_hdr)+माप(काष्ठा fcllc))
#घोषणा FC_ID_LEN 3		/* Octets in a Fibre Channel Address */

/* LLC and SNAP स्थिरants */
#घोषणा EXTENDED_SAP 0xAA
#घोषणा UI_CMD       0x03

/* This is NOT the Fibre Channel frame header. The FC frame header is
 *  स्थिरructed in the driver as the Tachyon needs certain fields in
 *  certains positions. So, it can't be generalized here.*/

काष्ठा fch_hdr अणु
	__u8  daddr[FC_ALEN];		/* destination address */
	__u8  saddr[FC_ALEN];		/* source address */
पूर्ण;

/* This is a Fibre Channel LLC काष्ठाure */
काष्ठा fcllc अणु
	__u8  dsap;			/* destination SAP */
	__u8  ssap;			/* source SAP */
	__u8  llc;			/* LLC control field */
	__u8  protid[3];		/* protocol id */
	__be16 ethertype;		/* ether type field */
पूर्ण;

#पूर्ण_अगर	/* _LINUX_IF_FC_H */
