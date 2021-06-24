<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *
 *	Generic पूर्णांकernet FLOW.
 *
 */

#अगर_अघोषित _NET_FLOW_H
#घोषणा _NET_FLOW_H

#समावेश <linux/socket.h>
#समावेश <linux/in6.h>
#समावेश <linux/atomic.h>
#समावेश <net/flow_dissector.h>
#समावेश <linux/uidgid.h>

/*
 * अगरindex generation is per-net namespace, and loopback is
 * always the 1st device in ns (see net_dev_init), thus any
 * loopback device should get अगरindex 1
 */

#घोषणा LOOPBACK_IFINDEX	1

काष्ठा flowi_tunnel अणु
	__be64			tun_id;
पूर्ण;

काष्ठा flowi_common अणु
	पूर्णांक	flowic_oअगर;
	पूर्णांक	flowic_iअगर;
	__u32	flowic_mark;
	__u8	flowic_tos;
	__u8	flowic_scope;
	__u8	flowic_proto;
	__u8	flowic_flags;
#घोषणा FLOWI_FLAG_ANYSRC		0x01
#घोषणा FLOWI_FLAG_KNOWN_NH		0x02
#घोषणा FLOWI_FLAG_SKIP_NH_OIF		0x04
	__u32	flowic_secid;
	kuid_t  flowic_uid;
	काष्ठा flowi_tunnel flowic_tun_key;
	__u32		flowic_multipath_hash;
पूर्ण;

जोड़ flowi_uli अणु
	काष्ठा अणु
		__be16	dport;
		__be16	sport;
	पूर्ण ports;

	काष्ठा अणु
		__u8	type;
		__u8	code;
	पूर्ण icmpt;

	काष्ठा अणु
		__le16	dport;
		__le16	sport;
	पूर्ण dnports;

	__be32		gre_key;

	काष्ठा अणु
		__u8	type;
	पूर्ण mht;
पूर्ण;

काष्ठा flowi4 अणु
	काष्ठा flowi_common	__fl_common;
#घोषणा flowi4_oअगर		__fl_common.flowic_oअगर
#घोषणा flowi4_iअगर		__fl_common.flowic_iअगर
#घोषणा flowi4_mark		__fl_common.flowic_mark
#घोषणा flowi4_tos		__fl_common.flowic_tos
#घोषणा flowi4_scope		__fl_common.flowic_scope
#घोषणा flowi4_proto		__fl_common.flowic_proto
#घोषणा flowi4_flags		__fl_common.flowic_flags
#घोषणा flowi4_secid		__fl_common.flowic_secid
#घोषणा flowi4_tun_key		__fl_common.flowic_tun_key
#घोषणा flowi4_uid		__fl_common.flowic_uid
#घोषणा flowi4_multipath_hash	__fl_common.flowic_multipath_hash

	/* (saddr,daddr) must be grouped, same order as in IP header */
	__be32			saddr;
	__be32			daddr;

	जोड़ flowi_uli		uli;
#घोषणा fl4_sport		uli.ports.sport
#घोषणा fl4_dport		uli.ports.dport
#घोषणा fl4_icmp_type		uli.icmpt.type
#घोषणा fl4_icmp_code		uli.icmpt.code
#घोषणा fl4_mh_type		uli.mht.type
#घोषणा fl4_gre_key		uli.gre_key
पूर्ण __attribute__((__aligned__(BITS_PER_LONG/8)));

अटल अंतरभूत व्योम flowi4_init_output(काष्ठा flowi4 *fl4, पूर्णांक oअगर,
				      __u32 mark, __u8 tos, __u8 scope,
				      __u8 proto, __u8 flags,
				      __be32 daddr, __be32 saddr,
				      __be16 dport, __be16 sport,
				      kuid_t uid)
अणु
	fl4->flowi4_oअगर = oअगर;
	fl4->flowi4_iअगर = LOOPBACK_IFINDEX;
	fl4->flowi4_mark = mark;
	fl4->flowi4_tos = tos;
	fl4->flowi4_scope = scope;
	fl4->flowi4_proto = proto;
	fl4->flowi4_flags = flags;
	fl4->flowi4_secid = 0;
	fl4->flowi4_tun_key.tun_id = 0;
	fl4->flowi4_uid = uid;
	fl4->daddr = daddr;
	fl4->saddr = saddr;
	fl4->fl4_dport = dport;
	fl4->fl4_sport = sport;
	fl4->flowi4_multipath_hash = 0;
पूर्ण

/* Reset some input parameters after previous lookup */
अटल अंतरभूत व्योम flowi4_update_output(काष्ठा flowi4 *fl4, पूर्णांक oअगर, __u8 tos,
					__be32 daddr, __be32 saddr)
अणु
	fl4->flowi4_oअगर = oअगर;
	fl4->flowi4_tos = tos;
	fl4->daddr = daddr;
	fl4->saddr = saddr;
पूर्ण


काष्ठा flowi6 अणु
	काष्ठा flowi_common	__fl_common;
#घोषणा flowi6_oअगर		__fl_common.flowic_oअगर
#घोषणा flowi6_iअगर		__fl_common.flowic_iअगर
#घोषणा flowi6_mark		__fl_common.flowic_mark
#घोषणा flowi6_scope		__fl_common.flowic_scope
#घोषणा flowi6_proto		__fl_common.flowic_proto
#घोषणा flowi6_flags		__fl_common.flowic_flags
#घोषणा flowi6_secid		__fl_common.flowic_secid
#घोषणा flowi6_tun_key		__fl_common.flowic_tun_key
#घोषणा flowi6_uid		__fl_common.flowic_uid
	काष्ठा in6_addr		daddr;
	काष्ठा in6_addr		saddr;
	/* Note: flowi6_tos is encoded in flowlabel, too. */
	__be32			flowlabel;
	जोड़ flowi_uli		uli;
#घोषणा fl6_sport		uli.ports.sport
#घोषणा fl6_dport		uli.ports.dport
#घोषणा fl6_icmp_type		uli.icmpt.type
#घोषणा fl6_icmp_code		uli.icmpt.code
#घोषणा fl6_mh_type		uli.mht.type
#घोषणा fl6_gre_key		uli.gre_key
	__u32			mp_hash;
पूर्ण __attribute__((__aligned__(BITS_PER_LONG/8)));

काष्ठा flowidn अणु
	काष्ठा flowi_common	__fl_common;
#घोषणा flowidn_oअगर		__fl_common.flowic_oअगर
#घोषणा flowidn_iअगर		__fl_common.flowic_iअगर
#घोषणा flowidn_mark		__fl_common.flowic_mark
#घोषणा flowidn_scope		__fl_common.flowic_scope
#घोषणा flowidn_proto		__fl_common.flowic_proto
#घोषणा flowidn_flags		__fl_common.flowic_flags
	__le16			daddr;
	__le16			saddr;
	जोड़ flowi_uli		uli;
#घोषणा fld_sport		uli.ports.sport
#घोषणा fld_dport		uli.ports.dport
पूर्ण __attribute__((__aligned__(BITS_PER_LONG/8)));

काष्ठा flowi अणु
	जोड़ अणु
		काष्ठा flowi_common	__fl_common;
		काष्ठा flowi4		ip4;
		काष्ठा flowi6		ip6;
		काष्ठा flowidn		dn;
	पूर्ण u;
#घोषणा flowi_oअगर	u.__fl_common.flowic_oअगर
#घोषणा flowi_iअगर	u.__fl_common.flowic_iअगर
#घोषणा flowi_mark	u.__fl_common.flowic_mark
#घोषणा flowi_tos	u.__fl_common.flowic_tos
#घोषणा flowi_scope	u.__fl_common.flowic_scope
#घोषणा flowi_proto	u.__fl_common.flowic_proto
#घोषणा flowi_flags	u.__fl_common.flowic_flags
#घोषणा flowi_secid	u.__fl_common.flowic_secid
#घोषणा flowi_tun_key	u.__fl_common.flowic_tun_key
#घोषणा flowi_uid	u.__fl_common.flowic_uid
पूर्ण __attribute__((__aligned__(BITS_PER_LONG/8)));

अटल अंतरभूत काष्ठा flowi *flowi4_to_flowi(काष्ठा flowi4 *fl4)
अणु
	वापस container_of(fl4, काष्ठा flowi, u.ip4);
पूर्ण

अटल अंतरभूत काष्ठा flowi_common *flowi4_to_flowi_common(काष्ठा flowi4 *fl4)
अणु
	वापस &(flowi4_to_flowi(fl4)->u.__fl_common);
पूर्ण

अटल अंतरभूत काष्ठा flowi *flowi6_to_flowi(काष्ठा flowi6 *fl6)
अणु
	वापस container_of(fl6, काष्ठा flowi, u.ip6);
पूर्ण

अटल अंतरभूत काष्ठा flowi_common *flowi6_to_flowi_common(काष्ठा flowi6 *fl6)
अणु
	वापस &(flowi6_to_flowi(fl6)->u.__fl_common);
पूर्ण

अटल अंतरभूत काष्ठा flowi *flowidn_to_flowi(काष्ठा flowidn *fldn)
अणु
	वापस container_of(fldn, काष्ठा flowi, u.dn);
पूर्ण

__u32 __get_hash_from_flowi6(स्थिर काष्ठा flowi6 *fl6, काष्ठा flow_keys *keys);

#पूर्ण_अगर
