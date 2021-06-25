<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ WITH Linux-syscall-note */
/*
 * INET		An implementation of the TCP/IP protocol suite क्रम the LINUX
 *		operating प्रणाली.  INET is implemented using the  BSD Socket
 *		पूर्णांकerface as the means of communication with the user level.
 *
 *		Definitions क्रम the IP protocol.
 *
 * Version:	@(#)ip.h	1.0.2	04/28/93
 *
 * Authors:	Fred N. van Kempen, <waltje@uWalt.NL.Mugnet.ORG>
 *
 *		This program is मुक्त software; you can redistribute it and/or
 *		modअगरy it under the terms of the GNU General Public License
 *		as published by the Free Software Foundation; either version
 *		2 of the License, or (at your option) any later version.
 */
#अगर_अघोषित _UAPI_LINUX_IP_H
#घोषणा _UAPI_LINUX_IP_H
#समावेश <linux/types.h>
#समावेश <यंत्र/byteorder.h>

#घोषणा IPTOS_TOS_MASK		0x1E
#घोषणा IPTOS_TOS(tos)		((tos)&IPTOS_TOS_MASK)
#घोषणा	IPTOS_LOWDELAY		0x10
#घोषणा	IPTOS_THROUGHPUT	0x08
#घोषणा	IPTOS_RELIABILITY	0x04
#घोषणा	IPTOS_MINCOST		0x02

#घोषणा IPTOS_PREC_MASK		0xE0
#घोषणा IPTOS_PREC(tos)		((tos)&IPTOS_PREC_MASK)
#घोषणा IPTOS_PREC_NETCONTROL           0xe0
#घोषणा IPTOS_PREC_INTERNETCONTROL      0xc0
#घोषणा IPTOS_PREC_CRITIC_ECP           0xa0
#घोषणा IPTOS_PREC_FLASHOVERRIDE        0x80
#घोषणा IPTOS_PREC_FLASH                0x60
#घोषणा IPTOS_PREC_IMMEDIATE            0x40
#घोषणा IPTOS_PREC_PRIORITY             0x20
#घोषणा IPTOS_PREC_ROUTINE              0x00


/* IP options */
#घोषणा IPOPT_COPY		0x80
#घोषणा IPOPT_CLASS_MASK	0x60
#घोषणा IPOPT_NUMBER_MASK	0x1f

#घोषणा	IPOPT_COPIED(o)		((o)&IPOPT_COPY)
#घोषणा	IPOPT_CLASS(o)		((o)&IPOPT_CLASS_MASK)
#घोषणा	IPOPT_NUMBER(o)		((o)&IPOPT_NUMBER_MASK)

#घोषणा	IPOPT_CONTROL		0x00
#घोषणा	IPOPT_RESERVED1		0x20
#घोषणा	IPOPT_MEASUREMENT	0x40
#घोषणा	IPOPT_RESERVED2		0x60

#घोषणा IPOPT_END	(0 |IPOPT_CONTROL)
#घोषणा IPOPT_NOOP	(1 |IPOPT_CONTROL)
#घोषणा IPOPT_SEC	(2 |IPOPT_CONTROL|IPOPT_COPY)
#घोषणा IPOPT_LSRR	(3 |IPOPT_CONTROL|IPOPT_COPY)
#घोषणा IPOPT_TIMESTAMP	(4 |IPOPT_MEASUREMENT)
#घोषणा IPOPT_CIPSO	(6 |IPOPT_CONTROL|IPOPT_COPY)
#घोषणा IPOPT_RR	(7 |IPOPT_CONTROL)
#घोषणा IPOPT_SID	(8 |IPOPT_CONTROL|IPOPT_COPY)
#घोषणा IPOPT_SSRR	(9 |IPOPT_CONTROL|IPOPT_COPY)
#घोषणा IPOPT_RA	(20|IPOPT_CONTROL|IPOPT_COPY)

#घोषणा IPVERSION	4
#घोषणा MAXTTL		255
#घोषणा IPDEFTTL	64

#घोषणा IPOPT_OPTVAL 0
#घोषणा IPOPT_OLEN   1
#घोषणा IPOPT_OFFSET 2
#घोषणा IPOPT_MINOFF 4
#घोषणा MAX_IPOPTLEN 40
#घोषणा IPOPT_NOP IPOPT_NOOP
#घोषणा IPOPT_EOL IPOPT_END
#घोषणा IPOPT_TS  IPOPT_TIMESTAMP

#घोषणा	IPOPT_TS_TSONLY		0		/* बारtamps only */
#घोषणा	IPOPT_TS_TSANDADDR	1		/* बारtamps and addresses */
#घोषणा	IPOPT_TS_PRESPEC	3		/* specअगरied modules only */

#घोषणा IPV4_BEET_PHMAXLEN 8

काष्ठा iphdr अणु
#अगर defined(__LITTLE_ENDIAN_BITFIELD)
	__u8	ihl:4,
		version:4;
#या_अगर defined (__BIG_ENDIAN_BITFIELD)
	__u8	version:4,
  		ihl:4;
#अन्यथा
#त्रुटि	"Please fix <asm/byteorder.h>"
#पूर्ण_अगर
	__u8	tos;
	__be16	tot_len;
	__be16	id;
	__be16	frag_off;
	__u8	ttl;
	__u8	protocol;
	__sum16	check;
	__be32	saddr;
	__be32	daddr;
	/*The options start here. */
पूर्ण;


काष्ठा ip_auth_hdr अणु
	__u8  nexthdr;
	__u8  hdrlen;		/* This one is measured in 32 bit units! */
	__be16 reserved;
	__be32 spi;
	__be32 seq_no;		/* Sequence number */
	__u8  auth_data[0];	/* Variable len but >=4. Mind the 64 bit alignment! */
पूर्ण;

काष्ठा ip_esp_hdr अणु
	__be32 spi;
	__be32 seq_no;		/* Sequence number */
	__u8  enc_data[0];	/* Variable len but >=8. Mind the 64 bit alignment! */
पूर्ण;

काष्ठा ip_comp_hdr अणु
	__u8 nexthdr;
	__u8 flags;
	__be16 cpi;
पूर्ण;

काष्ठा ip_beet_phdr अणु
	__u8 nexthdr;
	__u8 hdrlen;
	__u8 padlen;
	__u8 reserved;
पूर्ण;

/* index values क्रम the variables in ipv4_devconf */
क्रमागत
अणु
	IPV4_DEVCONF_FORWARDING=1,
	IPV4_DEVCONF_MC_FORWARDING,
	IPV4_DEVCONF_PROXY_ARP,
	IPV4_DEVCONF_ACCEPT_REसूचीECTS,
	IPV4_DEVCONF_SECURE_REसूचीECTS,
	IPV4_DEVCONF_SEND_REसूचीECTS,
	IPV4_DEVCONF_SHARED_MEDIA,
	IPV4_DEVCONF_RP_FILTER,
	IPV4_DEVCONF_ACCEPT_SOURCE_ROUTE,
	IPV4_DEVCONF_BOOTP_RELAY,
	IPV4_DEVCONF_LOG_MARTIANS,
	IPV4_DEVCONF_TAG,
	IPV4_DEVCONF_ARPFILTER,
	IPV4_DEVCONF_MEDIUM_ID,
	IPV4_DEVCONF_NOXFRM,
	IPV4_DEVCONF_NOPOLICY,
	IPV4_DEVCONF_FORCE_IGMP_VERSION,
	IPV4_DEVCONF_ARP_ANNOUNCE,
	IPV4_DEVCONF_ARP_IGNORE,
	IPV4_DEVCONF_PROMOTE_SECONDARIES,
	IPV4_DEVCONF_ARP_ACCEPT,
	IPV4_DEVCONF_ARP_NOTIFY,
	IPV4_DEVCONF_ACCEPT_LOCAL,
	IPV4_DEVCONF_SRC_VMARK,
	IPV4_DEVCONF_PROXY_ARP_PVLAN,
	IPV4_DEVCONF_ROUTE_LOCALNET,
	IPV4_DEVCONF_IGMPV2_UNSOLICITED_REPORT_INTERVAL,
	IPV4_DEVCONF_IGMPV3_UNSOLICITED_REPORT_INTERVAL,
	IPV4_DEVCONF_IGNORE_ROUTES_WITH_LINKDOWN,
	IPV4_DEVCONF_DROP_UNICAST_IN_L2_MULTICAST,
	IPV4_DEVCONF_DROP_GRATUITOUS_ARP,
	IPV4_DEVCONF_BC_FORWARDING,
	__IPV4_DEVCONF_MAX
पूर्ण;

#घोषणा IPV4_DEVCONF_MAX (__IPV4_DEVCONF_MAX - 1)

#पूर्ण_अगर /* _UAPI_LINUX_IP_H */
