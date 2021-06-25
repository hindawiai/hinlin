<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _UAPI_LINUX_NEXTHOP_H
#घोषणा _UAPI_LINUX_NEXTHOP_H

#समावेश <linux/types.h>

काष्ठा nhmsg अणु
	अचिन्हित अक्षर	nh_family;
	अचिन्हित अक्षर	nh_scope;     /* वापस only */
	अचिन्हित अक्षर	nh_protocol;  /* Routing protocol that installed nh */
	अचिन्हित अक्षर	resvd;
	अचिन्हित पूर्णांक	nh_flags;     /* RTNH_F flags */
पूर्ण;

/* entry in a nexthop group */
काष्ठा nexthop_grp अणु
	__u32	id;	  /* nexthop id - must exist */
	__u8	weight;   /* weight of this nexthop */
	__u8	resvd1;
	__u16	resvd2;
पूर्ण;

क्रमागत अणु
	NEXTHOP_GRP_TYPE_MPATH,  /* hash-threshold nexthop group
				  * शेष type अगर not specअगरied
				  */
	NEXTHOP_GRP_TYPE_RES,    /* resilient nexthop group */
	__NEXTHOP_GRP_TYPE_MAX,
पूर्ण;

#घोषणा NEXTHOP_GRP_TYPE_MAX (__NEXTHOP_GRP_TYPE_MAX - 1)

क्रमागत अणु
	NHA_UNSPEC,
	NHA_ID,		/* u32; id क्रम nexthop. id == 0 means स्वतः-assign */

	NHA_GROUP,	/* array of nexthop_grp */
	NHA_GROUP_TYPE,	/* u16 one of NEXTHOP_GRP_TYPE */
	/* अगर NHA_GROUP attribute is added, no other attributes can be set */

	NHA_BLACKHOLE,	/* flag; nexthop used to blackhole packets */
	/* अगर NHA_BLACKHOLE is added, OIF, GATEWAY, ENCAP can not be set */

	NHA_OIF,	/* u32; nexthop device */
	NHA_GATEWAY,	/* be32 (IPv4) or in6_addr (IPv6) gw address */
	NHA_ENCAP_TYPE, /* u16; lwt encap type */
	NHA_ENCAP,	/* lwt encap data */

	/* NHA_OIF can be appended to dump request to वापस only
	 * nexthops using given device
	 */
	NHA_GROUPS,	/* flag; only वापस nexthop groups in dump */
	NHA_MASTER,	/* u32;  only वापस nexthops with given master dev */

	NHA_FDB,	/* flag; nexthop beदीर्घs to a bridge fdb */
	/* अगर NHA_FDB is added, OIF, BLACKHOLE, ENCAP cannot be set */

	/* nested; resilient nexthop group attributes */
	NHA_RES_GROUP,
	/* nested; nexthop bucket attributes */
	NHA_RES_BUCKET,

	__NHA_MAX,
पूर्ण;

#घोषणा NHA_MAX	(__NHA_MAX - 1)

क्रमागत अणु
	NHA_RES_GROUP_UNSPEC,
	/* Pad attribute क्रम 64-bit alignment. */
	NHA_RES_GROUP_PAD = NHA_RES_GROUP_UNSPEC,

	/* u16; number of nexthop buckets in a resilient nexthop group */
	NHA_RES_GROUP_BUCKETS,
	/* घड़ी_प्रकार as u32; nexthop bucket idle समयr (per-group) */
	NHA_RES_GROUP_IDLE_TIMER,
	/* घड़ी_प्रकार as u32; nexthop unbalanced समयr */
	NHA_RES_GROUP_UNBALANCED_TIMER,
	/* घड़ी_प्रकार as u64; nexthop unbalanced समय */
	NHA_RES_GROUP_UNBALANCED_TIME,

	__NHA_RES_GROUP_MAX,
पूर्ण;

#घोषणा NHA_RES_GROUP_MAX	(__NHA_RES_GROUP_MAX - 1)

क्रमागत अणु
	NHA_RES_BUCKET_UNSPEC,
	/* Pad attribute क्रम 64-bit alignment. */
	NHA_RES_BUCKET_PAD = NHA_RES_BUCKET_UNSPEC,

	/* u16; nexthop bucket index */
	NHA_RES_BUCKET_INDEX,
	/* घड़ी_प्रकार as u64; nexthop bucket idle समय */
	NHA_RES_BUCKET_IDLE_TIME,
	/* u32; nexthop id asचिन्हित to the nexthop bucket */
	NHA_RES_BUCKET_NH_ID,

	__NHA_RES_BUCKET_MAX,
पूर्ण;

#घोषणा NHA_RES_BUCKET_MAX	(__NHA_RES_BUCKET_MAX - 1)

#पूर्ण_अगर
