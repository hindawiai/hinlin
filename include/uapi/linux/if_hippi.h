<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ WITH Linux-syscall-note */
/*
 * INET		An implementation of the TCP/IP protocol suite क्रम the LINUX
 *		operating प्रणाली.  INET is implemented using the  BSD Socket
 *		पूर्णांकerface as the means of communication with the user level.
 *
 *		Global definitions क्रम the HIPPI पूर्णांकerface.
 *
 * Version:	@(#)अगर_hippi.h	1.0.0	05/26/97
 *
 * Author:	Fred N. van Kempen, <waltje@uWalt.NL.Mugnet.ORG>
 *		Donald Becker, <becker@super.org>
 *		Alan Cox, <alan@lxorguk.ukuu.org.uk>
 *		Steve Whitehouse, <gw7rrm@eeshack3.swan.ac.uk>
 *		Jes Sorensen, <Jes.Sorensen@cern.ch>
 *
 *		This program is मुक्त software; you can redistribute it and/or
 *		modअगरy it under the terms of the GNU General Public License
 *		as published by the Free Software Foundation; either version
 *		2 of the License, or (at your option) any later version.
 */
 
#अगर_अघोषित _LINUX_IF_HIPPI_H
#घोषणा _LINUX_IF_HIPPI_H

#समावेश <linux/types.h>
#समावेश <यंत्र/byteorder.h>

/*
 *	HIPPI magic स्थिरants.
 */

#घोषणा HIPPI_ALEN	6		/* Bytes in one HIPPI hw-addr	   */
#घोषणा HIPPI_HLEN	माप(काष्ठा hippi_hdr)
#घोषणा HIPPI_ZLEN	0		/* Min. bytes in frame without FCS */
#घोषणा HIPPI_DATA_LEN	65280		/* Max. bytes in payload	   */
#घोषणा HIPPI_FRAME_LEN	(HIPPI_DATA_LEN + HIPPI_HLEN)
					/* Max. bytes in frame without FCS */

/*
 * Define LLC and SNAP स्थिरants.
 */
#घोषणा HIPPI_EXTENDED_SAP	0xAA
#घोषणा HIPPI_UI_CMD		0x03


/*
 *	Do we need to list some sort of ID's here?
 */

/*
 *	HIPPI statistics collection data. 
 */
 
काष्ठा hipnet_statistics अणु
	पूर्णांक	rx_packets;		/* total packets received	*/
	पूर्णांक	tx_packets;		/* total packets transmitted	*/
	पूर्णांक	rx_errors;		/* bad packets received		*/
	पूर्णांक	tx_errors;		/* packet transmit problems	*/
	पूर्णांक	rx_dropped;		/* no space in linux buffers	*/
	पूर्णांक	tx_dropped;		/* no space available in linux	*/

	/* detailed rx_errors: */
	पूर्णांक	rx_length_errors;
	पूर्णांक	rx_over_errors;		/* receiver ring buff overflow	*/
	पूर्णांक	rx_crc_errors;		/* recved pkt with crc error	*/
	पूर्णांक	rx_frame_errors;	/* recv'd frame alignment error */
	पूर्णांक	rx_fअगरo_errors;		/* recv'r fअगरo overrun		*/
	पूर्णांक	rx_missed_errors;	/* receiver missed packet	*/

	/* detailed tx_errors */
	पूर्णांक	tx_पातed_errors;
	पूर्णांक	tx_carrier_errors;
	पूर्णांक	tx_fअगरo_errors;
	पूर्णांक	tx_heartbeat_errors;
	पूर्णांक	tx_winकरोw_errors;
पूर्ण;


काष्ठा hippi_fp_hdr अणु
#अगर 0
	__u8		ulp;				/* must contain 4 */
#अगर defined (__BIG_ENDIAN_BITFIELD)
	__u8		d1_data_present:1;		/* must be 1 */
	__u8		start_d2_burst_boundary:1;	/* must be zero */
	__u8		reserved:6;			/* must be zero */
#अगर 0
	__u16		reserved1:5;
	__u16		d1_area_size:8;			/* must be 3 */
	__u16		d2_offset:3;			/* must be zero */
#पूर्ण_अगर
#या_अगर defined(__LITTLE_ENDIAN_BITFIELD)
	__u8		reserved:6;			/* must be zero */
	__u8	 	start_d2_burst_boundary:1;	/* must be zero */
	__u8		d1_data_present:1;		/* must be 1 */
#अगर 0
	__u16		d2_offset:3;			/* must be zero */
	__u16		d1_area_size:8;			/* must be 3 */
	__u16		reserved1:5;			/* must be zero */
#पूर्ण_अगर
#अन्यथा
#त्रुटि	"Please fix <asm/byteorder.h>"
#पूर्ण_अगर
#अन्यथा
	__be32		fixed;
#पूर्ण_अगर
	__be32		d2_size;
पूर्ण __attribute__((packed));

काष्ठा hippi_le_hdr अणु
#अगर defined (__BIG_ENDIAN_BITFIELD)
	__u8		fc:3;
	__u8		द्विगुन_wide:1;
	__u8		message_type:4;
#या_अगर defined(__LITTLE_ENDIAN_BITFIELD)
	__u8		message_type:4;
	__u8		द्विगुन_wide:1;
	__u8		fc:3;
#पूर्ण_अगर
	__u8		dest_चयन_addr[3];
#अगर defined (__BIG_ENDIAN_BITFIELD)
	__u8		dest_addr_type:4,
			src_addr_type:4;
#या_अगर defined(__LITTLE_ENDIAN_BITFIELD)
	__u8		src_addr_type:4,
			dest_addr_type:4;
#पूर्ण_अगर
	__u8		src_चयन_addr[3];
	__u16		reserved;
	__u8		daddr[HIPPI_ALEN];
	__u16		locally_administered;
	__u8		saddr[HIPPI_ALEN];
पूर्ण __attribute__((packed));

#घोषणा HIPPI_OUI_LEN	3
/*
 * Looks like the dsap and ssap fields have been swapped by mistake in
 * RFC 2067 "IP over HIPPI".
 */
काष्ठा hippi_snap_hdr अणु
	__u8	dsap;			/* always 0xAA */
	__u8	ssap;			/* always 0xAA */
	__u8	ctrl;			/* always 0x03 */
	__u8	oui[HIPPI_OUI_LEN];	/* organizational universal id (zero)*/
	__be16	ethertype;		/* packet type ID field */
पूर्ण __attribute__((packed));

काष्ठा hippi_hdr अणु
	काष्ठा hippi_fp_hdr	fp;
	काष्ठा hippi_le_hdr	le;
	काष्ठा hippi_snap_hdr	snap;
पूर्ण __attribute__((packed));

#पूर्ण_अगर	/* _LINUX_IF_HIPPI_H */
