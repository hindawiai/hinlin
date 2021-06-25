<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ WITH Linux-syscall-note */
/*
 * INET		An implementation of the TCP/IP protocol suite क्रम the LINUX
 *		operating प्रणाली.  INET is implemented using the  BSD Socket
 *		पूर्णांकerface as the means of communication with the user level.
 *
 *		Global definitions क्रम the ARP (RFC 826) protocol.
 *
 * Version:	@(#)अगर_arp.h	1.0.1	04/16/93
 *
 * Authors:	Original taken from Berkeley UNIX 4.3, (c) UCB 1986-1988
 *		Portions taken from the KA9Q/NOS (v2.00m PA0GRI) source.
 *		Ross Biro
 *		Fred N. van Kempen, <waltje@uWalt.NL.Mugnet.ORG>
 *		Florian La Roche,
 *		Jonathan Layes <layes@loran.com>
 *		Arnalकरो Carvalho de Melo <acme@conectiva.com.br> ARPHRD_HWX25
 *
 *		This program is मुक्त software; you can redistribute it and/or
 *		modअगरy it under the terms of the GNU General Public License
 *		as published by the Free Software Foundation; either version
 *		2 of the License, or (at your option) any later version.
 */
#अगर_अघोषित _UAPI_LINUX_IF_ARP_H
#घोषणा _UAPI_LINUX_IF_ARP_H

#समावेश <linux/netdevice.h>

/* ARP protocol HARDWARE identअगरiers. */
#घोषणा ARPHRD_NETROM	0		/* from KA9Q: NET/ROM pseuकरो	*/
#घोषणा ARPHRD_ETHER 	1		/* Ethernet 10Mbps		*/
#घोषणा	ARPHRD_EETHER	2		/* Experimental Ethernet	*/
#घोषणा	ARPHRD_AX25	3		/* AX.25 Level 2		*/
#घोषणा	ARPHRD_PRONET	4		/* PROnet token ring		*/
#घोषणा	ARPHRD_CHAOS	5		/* Chaosnet			*/
#घोषणा	ARPHRD_IEEE802	6		/* IEEE 802.2 Ethernet/TR/TB	*/
#घोषणा	ARPHRD_ARCNET	7		/* ARCnet			*/
#घोषणा	ARPHRD_APPLETLK	8		/* APPLEtalk			*/
#घोषणा ARPHRD_DLCI	15		/* Frame Relay DLCI		*/
#घोषणा ARPHRD_ATM	19		/* ATM 				*/
#घोषणा ARPHRD_METRICOM	23		/* Metricom STRIP (new IANA id)	*/
#घोषणा	ARPHRD_IEEE1394	24		/* IEEE 1394 IPv4 - RFC 2734	*/
#घोषणा ARPHRD_EUI64	27		/* EUI-64                       */
#घोषणा ARPHRD_INFINIBAND 32		/* InfiniBand			*/

/* Dummy types क्रम non ARP hardware */
#घोषणा ARPHRD_SLIP	256
#घोषणा ARPHRD_CSLIP	257
#घोषणा ARPHRD_SLIP6	258
#घोषणा ARPHRD_CSLIP6	259
#घोषणा ARPHRD_RSRVD	260		/* Notional KISS type 		*/
#घोषणा ARPHRD_ADAPT	264
#घोषणा ARPHRD_ROSE	270
#घोषणा ARPHRD_X25	271		/* CCITT X.25			*/
#घोषणा ARPHRD_HWX25	272		/* Boards with X.25 in firmware	*/
#घोषणा ARPHRD_CAN	280		/* Controller Area Network      */
#घोषणा ARPHRD_PPP	512
#घोषणा ARPHRD_CISCO	513		/* Cisco HDLC	 		*/
#घोषणा ARPHRD_HDLC	ARPHRD_CISCO
#घोषणा ARPHRD_LAPB	516		/* LAPB				*/
#घोषणा ARPHRD_DDCMP    517		/* Digital's DDCMP protocol     */
#घोषणा ARPHRD_RAWHDLC	518		/* Raw HDLC			*/
#घोषणा ARPHRD_RAWIP    519		/* Raw IP                       */

#घोषणा ARPHRD_TUNNEL	768		/* IPIP tunnel			*/
#घोषणा ARPHRD_TUNNEL6	769		/* IP6IP6 tunnel       		*/
#घोषणा ARPHRD_FRAD	770             /* Frame Relay Access Device    */
#घोषणा ARPHRD_SKIP	771		/* SKIP vअगर			*/
#घोषणा ARPHRD_LOOPBACK	772		/* Loopback device		*/
#घोषणा ARPHRD_LOCALTLK 773		/* Localtalk device		*/
#घोषणा ARPHRD_FDDI	774		/* Fiber Distributed Data Interface */
#घोषणा ARPHRD_BIF      775             /* AP1000 BIF                   */
#घोषणा ARPHRD_SIT	776		/* sit0 device - IPv6-in-IPv4	*/
#घोषणा ARPHRD_IPDDP	777		/* IP over DDP tunneller	*/
#घोषणा ARPHRD_IPGRE	778		/* GRE over IP			*/
#घोषणा ARPHRD_PIMREG	779		/* PIMSM रेजिस्टर पूर्णांकerface	*/
#घोषणा ARPHRD_HIPPI	780		/* High Perक्रमmance Parallel Interface */
#घोषणा ARPHRD_ASH	781		/* Nexus 64Mbps Ash		*/
#घोषणा ARPHRD_ECONET	782		/* Acorn Econet			*/
#घोषणा ARPHRD_IRDA 	783		/* Linux-IrDA			*/
/* ARP works dअगरferently on dअगरferent FC media .. so  */
#घोषणा ARPHRD_FCPP	784		/* Poपूर्णांक to poपूर्णांक fibrechannel	*/
#घोषणा ARPHRD_FCAL	785		/* Fibrechannel arbitrated loop */
#घोषणा ARPHRD_FCPL	786		/* Fibrechannel खुला loop	*/
#घोषणा ARPHRD_FCFABRIC	787		/* Fibrechannel fabric		*/
	/* 787->799 reserved क्रम fibrechannel media types */
#घोषणा ARPHRD_IEEE802_TR 800		/* Magic type ident क्रम TR	*/
#घोषणा ARPHRD_IEEE80211 801		/* IEEE 802.11			*/
#घोषणा ARPHRD_IEEE80211_PRISM 802	/* IEEE 802.11 + Prism2 header  */
#घोषणा ARPHRD_IEEE80211_RADIOTAP 803	/* IEEE 802.11 + radiotap header */
#घोषणा ARPHRD_IEEE802154	  804
#घोषणा ARPHRD_IEEE802154_MONITOR 805	/* IEEE 802.15.4 network monitor */

#घोषणा ARPHRD_PHONET	820		/* PhoNet media type		*/
#घोषणा ARPHRD_PHONET_PIPE 821		/* PhoNet pipe header		*/
#घोषणा ARPHRD_CAIF	822		/* CAIF media type		*/
#घोषणा ARPHRD_IP6GRE	823		/* GRE over IPv6		*/
#घोषणा ARPHRD_NETLINK	824		/* Netlink header		*/
#घोषणा ARPHRD_6LOWPAN	825		/* IPv6 over LoWPAN             */
#घोषणा ARPHRD_VSOCKMON	826		/* Vsock monitor header		*/

#घोषणा ARPHRD_VOID	  0xFFFF	/* Void type, nothing is known */
#घोषणा ARPHRD_NONE	  0xFFFE	/* zero header length */

/* ARP protocol opcodes. */
#घोषणा	ARPOP_REQUEST	1		/* ARP request			*/
#घोषणा	ARPOP_REPLY	2		/* ARP reply			*/
#घोषणा	ARPOP_RREQUEST	3		/* RARP request			*/
#घोषणा	ARPOP_RREPLY	4		/* RARP reply			*/
#घोषणा	ARPOP_InREQUEST	8		/* InARP request		*/
#घोषणा	ARPOP_InREPLY	9		/* InARP reply			*/
#घोषणा	ARPOP_NAK	10		/* (ATM)ARP NAK			*/


/* ARP ioctl request. */
काष्ठा arpreq अणु
	काष्ठा sockaddr	arp_pa;		/* protocol address		 */
	काष्ठा sockaddr	arp_ha;		/* hardware address		 */
	पूर्णांक		arp_flags;	/* flags			 */
	काष्ठा sockaddr arp_neपंचांगask;    /* neपंचांगask (only क्रम proxy arps) */
	अक्षर		arp_dev[IFNAMSIZ];
पूर्ण;

काष्ठा arpreq_old अणु
	काष्ठा sockaddr	arp_pa;		/* protocol address		 */
	काष्ठा sockaddr	arp_ha;		/* hardware address		 */
	पूर्णांक		arp_flags;	/* flags			 */
	काष्ठा sockaddr	arp_neपंचांगask;    /* neपंचांगask (only क्रम proxy arps) */
पूर्ण;

/* ARP Flag values. */
#घोषणा ATF_COM		0x02		/* completed entry (ha valid)	*/
#घोषणा	ATF_PERM	0x04		/* permanent entry		*/
#घोषणा	ATF_PUBL	0x08		/* publish entry		*/
#घोषणा	ATF_USETRAILERS	0x10		/* has requested trailers	*/
#घोषणा ATF_NETMASK     0x20            /* want to use a neपंचांगask (only
					   क्रम proxy entries) */
#घोषणा ATF_DONTPUB	0x40		/* करोn't answer this addresses	*/

/*
 *	This काष्ठाure defines an ethernet arp header.
 */

काष्ठा arphdr अणु
	__be16		ar_hrd;		/* क्रमmat of hardware address	*/
	__be16		ar_pro;		/* क्रमmat of protocol address	*/
	अचिन्हित अक्षर	ar_hln;		/* length of hardware address	*/
	अचिन्हित अक्षर	ar_pln;		/* length of protocol address	*/
	__be16		ar_op;		/* ARP opcode (command)		*/

#अगर 0
	 /*
	  *	 Ethernet looks like this : This bit is variable sized however...
	  */
	अचिन्हित अक्षर		ar_sha[ETH_ALEN];	/* sender hardware address	*/
	अचिन्हित अक्षर		ar_sip[4];		/* sender IP address		*/
	अचिन्हित अक्षर		ar_tha[ETH_ALEN];	/* target hardware address	*/
	अचिन्हित अक्षर		ar_tip[4];		/* target IP address		*/
#पूर्ण_अगर

पूर्ण;


#पूर्ण_अगर /* _UAPI_LINUX_IF_ARP_H */
