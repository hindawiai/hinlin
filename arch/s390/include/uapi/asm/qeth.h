<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * ioctl definitions क्रम qeth driver
 *
 * Copyright IBM Corp. 2004
 *
 * Author(s):	Thomas Spatzier <tspat@de.ibm.com>
 *
 */
#अगर_अघोषित __ASM_S390_QETH_IOCTL_H__
#घोषणा __ASM_S390_QETH_IOCTL_H__
#समावेश <linux/types.h>
#समावेश <linux/ioctl.h>

#घोषणा SIOC_QETH_ARP_SET_NO_ENTRIES    (SIOCDEVPRIVATE)
#घोषणा SIOC_QETH_ARP_QUERY_INFO        (SIOCDEVPRIVATE + 1)
#घोषणा SIOC_QETH_ARP_ADD_ENTRY         (SIOCDEVPRIVATE + 2)
#घोषणा SIOC_QETH_ARP_REMOVE_ENTRY      (SIOCDEVPRIVATE + 3)
#घोषणा SIOC_QETH_ARP_FLUSH_CACHE       (SIOCDEVPRIVATE + 4)
#घोषणा SIOC_QETH_ADP_SET_SNMP_CONTROL  (SIOCDEVPRIVATE + 5)
#घोषणा SIOC_QETH_GET_CARD_TYPE         (SIOCDEVPRIVATE + 6)
#घोषणा SIOC_QETH_QUERY_OAT		(SIOCDEVPRIVATE + 7)

काष्ठा qeth_arp_cache_entry अणु
	__u8  macaddr[6];
	__u8  reserved1[2];
	__u8  ipaddr[16]; /* क्रम both  IPv4 and IPv6 */
	__u8  reserved2[32];
पूर्ण __attribute__ ((packed));

क्रमागत qeth_arp_ipaddrtype अणु
	QETHARP_IP_ADDR_V4 = 1,
	QETHARP_IP_ADDR_V6 = 2,
पूर्ण;
काष्ठा qeth_arp_entrytype अणु
	__u8 mac;
	__u8 ip;
पूर्ण __attribute__((packed));

#घोषणा QETH_QARP_MEDIASPECIFIC_BYTES 32
#घोषणा QETH_QARP_MACADDRTYPE_BYTES 1
काष्ठा qeth_arp_qi_entry7 अणु
	__u8 media_specअगरic[QETH_QARP_MEDIASPECIFIC_BYTES];
	काष्ठा qeth_arp_entrytype type;
	__u8 macaddr[6];
	__u8 ipaddr[4];
पूर्ण __attribute__((packed));

काष्ठा qeth_arp_qi_entry7_ipv6 अणु
	__u8 media_specअगरic[QETH_QARP_MEDIASPECIFIC_BYTES];
	काष्ठा qeth_arp_entrytype type;
	__u8 macaddr[6];
	__u8 ipaddr[16];
पूर्ण __attribute__((packed));

काष्ठा qeth_arp_qi_entry7_लघु अणु
	काष्ठा qeth_arp_entrytype type;
	__u8 macaddr[6];
	__u8 ipaddr[4];
पूर्ण __attribute__((packed));

काष्ठा qeth_arp_qi_entry7_लघु_ipv6 अणु
	काष्ठा qeth_arp_entrytype type;
	__u8 macaddr[6];
	__u8 ipaddr[16];
पूर्ण __attribute__((packed));

काष्ठा qeth_arp_qi_entry5 अणु
	__u8 media_specअगरic[QETH_QARP_MEDIASPECIFIC_BYTES];
	काष्ठा qeth_arp_entrytype type;
	__u8 ipaddr[4];
पूर्ण __attribute__((packed));

काष्ठा qeth_arp_qi_entry5_ipv6 अणु
	__u8 media_specअगरic[QETH_QARP_MEDIASPECIFIC_BYTES];
	काष्ठा qeth_arp_entrytype type;
	__u8 ipaddr[16];
पूर्ण __attribute__((packed));

काष्ठा qeth_arp_qi_entry5_लघु अणु
	काष्ठा qeth_arp_entrytype type;
	__u8 ipaddr[4];
पूर्ण __attribute__((packed));

काष्ठा qeth_arp_qi_entry5_लघु_ipv6 अणु
	काष्ठा qeth_arp_entrytype type;
	__u8 ipaddr[16];
पूर्ण __attribute__((packed));
/*
 * can be set by user अगर no "media specific information" is wanted
 * -> saves a lot of space in user space buffer
 */
#घोषणा QETH_QARP_STRIP_ENTRIES  0x8000
#घोषणा QETH_QARP_WITH_IPV6	 0x4000
#घोषणा QETH_QARP_REQUEST_MASK   0x00ff

/* data sent to user space as result of query arp ioctl */
#घोषणा QETH_QARP_USER_DATA_SIZE 20000
#घोषणा QETH_QARP_MASK_OFFSET    4
#घोषणा QETH_QARP_ENTRIES_OFFSET 6
काष्ठा qeth_arp_query_user_data अणु
	जोड़ अणु
		__u32 data_len;		/* set by user space program */
		__u32 no_entries;	/* set by kernel */
	पूर्ण u;
	__u16 mask_bits;
	अक्षर *entries;
पूर्ण __attribute__((packed));

काष्ठा qeth_query_oat_data अणु
	__u32 command;
	__u32 buffer_len;
	__u32 response_len;
	__u64 ptr;
पूर्ण;
#पूर्ण_अगर /* __ASM_S390_QETH_IOCTL_H__ */
