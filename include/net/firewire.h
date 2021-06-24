<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _NET_FIREWIRE_H
#घोषणा _NET_FIREWIRE_H

/* Pseuकरो L2 address */
#घोषणा FWNET_ALEN	16
जोड़ fwnet_hwaddr अणु
	u8 u[FWNET_ALEN];
	/* "Hardware address" defined in RFC2734/RF3146 */
	काष्ठा अणु
		__be64 uniq_id;		/* EUI-64			*/
		u8 max_rec;		/* max packet size		*/
		u8 sspd;		/* max speed			*/
		__be16 fअगरo_hi;		/* hi 16bits of FIFO addr	*/
		__be32 fअगरo_lo;		/* lo 32bits of FIFO addr	*/
	पूर्ण __packed uc;
पूर्ण;

/* Pseuकरो L2 Header */
#घोषणा FWNET_HLEN	18
काष्ठा fwnet_header अणु
	u8 h_dest[FWNET_ALEN];	/* destination address */
	__be16 h_proto;		/* packet type ID field */
पूर्ण __packed;

#पूर्ण_अगर
