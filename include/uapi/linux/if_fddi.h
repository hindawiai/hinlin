<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ WITH Linux-syscall-note */
/*
 * INET		An implementation of the TCP/IP protocol suite क्रम the LINUX
 *		operating प्रणाली.  INET is implemented using the BSD Socket
 *		पूर्णांकerface as the means of communication with the user level.
 *
 *		Global definitions क्रम the ANSI FDDI पूर्णांकerface.
 *
 * Version:	@(#)अगर_fddi.h	1.0.3	Oct  6 2018
 *
 * Author:	Lawrence V. Stefani, <stefani@yahoo.com>
 * Maपूर्णांकainer:	Maciej W. Rozycki, <macro@orcam.me.uk>
 *
 *		अगर_fddi.h is based on previous अगर_ether.h and अगर_tr.h work by
 *			Fred N. van Kempen, <waltje@uWalt.NL.Mugnet.ORG>
 *			Donald Becker, <becker@super.org>
 *			Alan Cox, <alan@lxorguk.ukuu.org.uk>
 *			Steve Whitehouse, <gw7rrm@eeshack3.swan.ac.uk>
 *			Peter De Schrijver, <stud11@cc4.kuleuven.ac.be>
 *
 *		This program is मुक्त software; you can redistribute it and/or
 *		modअगरy it under the terms of the GNU General Public License
 *		as published by the Free Software Foundation; either version
 *		2 of the License, or (at your option) any later version.
 */
#अगर_अघोषित _UAPI_LINUX_IF_FDDI_H
#घोषणा _UAPI_LINUX_IF_FDDI_H

#समावेश <linux/types.h>

/*
 *  Define max and min legal sizes.  The frame sizes करो not include
 *  4 byte FCS/CRC (frame check sequence).
 */
#घोषणा FDDI_K_ALEN		6	/* Octets in one FDDI address */
#घोषणा FDDI_K_8022_HLEN	16	/* Total octets in 802.2 header */
#घोषणा FDDI_K_SNAP_HLEN	21	/* Total octets in 802.2 SNAP header */
#घोषणा FDDI_K_8022_ZLEN	16	/* Min octets in 802.2 frame sans
					   FCS */
#घोषणा FDDI_K_SNAP_ZLEN	21	/* Min octets in 802.2 SNAP frame sans
					   FCS */
#घोषणा FDDI_K_8022_DLEN	4475	/* Max octets in 802.2 payload */
#घोषणा FDDI_K_SNAP_DLEN	4470	/* Max octets in 802.2 SNAP payload */
#घोषणा FDDI_K_LLC_ZLEN		13	/* Min octets in LLC frame sans FCS */
#घोषणा FDDI_K_LLC_LEN		4491	/* Max octets in LLC frame sans FCS */
#घोषणा FDDI_K_OUI_LEN		3	/* Octets in OUI in 802.2 SNAP
					   header */

/* Define FDDI Frame Control (FC) Byte masks */
#घोषणा FDDI_FC_K_CLASS_MASK		0x80	/* class bit */
#घोषणा FDDI_FC_K_CLASS_SYNC		0x80
#घोषणा FDDI_FC_K_CLASS_ASYNC		0x00
#घोषणा FDDI_FC_K_ALEN_MASK		0x40	/* address length bit */
#घोषणा FDDI_FC_K_ALEN_48		0x40
#घोषणा FDDI_FC_K_ALEN_16		0x00
#घोषणा FDDI_FC_K_FORMAT_MASK		0x30	/* क्रमmat bits */
#घोषणा FDDI_FC_K_FORMAT_FUTURE		0x30
#घोषणा FDDI_FC_K_FORMAT_IMPLEMENTOR	0x20
#घोषणा FDDI_FC_K_FORMAT_LLC		0x10
#घोषणा FDDI_FC_K_FORMAT_MANAGEMENT	0x00
#घोषणा FDDI_FC_K_CONTROL_MASK		0x0f	/* control bits */

/* Define FDDI Frame Control (FC) Byte specअगरic values */
#घोषणा FDDI_FC_K_VOID			0x00
#घोषणा FDDI_FC_K_NON_RESTRICTED_TOKEN	0x80
#घोषणा FDDI_FC_K_RESTRICTED_TOKEN	0xC0
#घोषणा FDDI_FC_K_SMT_MIN		0x41
#घोषणा FDDI_FC_K_SMT_MAX		0x4F
#घोषणा FDDI_FC_K_MAC_MIN		0xC1
#घोषणा FDDI_FC_K_MAC_MAX		0xCF
#घोषणा FDDI_FC_K_ASYNC_LLC_MIN		0x50
#घोषणा FDDI_FC_K_ASYNC_LLC_DEF		0x54
#घोषणा FDDI_FC_K_ASYNC_LLC_MAX		0x5F
#घोषणा FDDI_FC_K_SYNC_LLC_MIN		0xD0
#घोषणा FDDI_FC_K_SYNC_LLC_MAX		0xD7
#घोषणा FDDI_FC_K_IMPLEMENTOR_MIN	0x60
#घोषणा FDDI_FC_K_IMPLEMENTOR_MAX	0x6F
#घोषणा FDDI_FC_K_RESERVED_MIN		0x70
#घोषणा FDDI_FC_K_RESERVED_MAX		0x7F

/* Define LLC and SNAP स्थिरants */
#घोषणा FDDI_EXTENDED_SAP		0xAA
#घोषणा FDDI_UI_CMD			0x03

/* Define 802.2 Type 1 header */
काष्ठा fddi_8022_1_hdr अणु
	__u8	dsap;			/* destination service access poपूर्णांक */
	__u8	ssap;			/* source service access poपूर्णांक */
	__u8	ctrl;			/* control byte #1 */
पूर्ण __attribute__((packed));

/* Define 802.2 Type 2 header */
काष्ठा fddi_8022_2_hdr अणु
	__u8	dsap;			/* destination service access poपूर्णांक */
	__u8	ssap;			/* source service access poपूर्णांक */
	__u8	ctrl_1;			/* control byte #1 */
	__u8	ctrl_2;			/* control byte #2 */
पूर्ण __attribute__((packed));

/* Define 802.2 SNAP header */
काष्ठा fddi_snap_hdr अणु
	__u8	dsap;			/* always 0xAA */
	__u8	ssap;			/* always 0xAA */
	__u8	ctrl;			/* always 0x03 */
	__u8	oui[FDDI_K_OUI_LEN];	/* organizational universal id */
	__be16	ethertype;		/* packet type ID field */
पूर्ण __attribute__((packed));

/* Define FDDI LLC frame header */
काष्ठा fddihdr अणु
	__u8	fc;			/* frame control */
	__u8	daddr[FDDI_K_ALEN];	/* destination address */
	__u8	saddr[FDDI_K_ALEN];	/* source address */
	जोड़ अणु
		काष्ठा fddi_8022_1_hdr	llc_8022_1;
		काष्ठा fddi_8022_2_hdr	llc_8022_2;
		काष्ठा fddi_snap_hdr	llc_snap;
	पूर्ण hdr;
पूर्ण __attribute__((packed));


#पूर्ण_अगर /* _UAPI_LINUX_IF_FDDI_H */
