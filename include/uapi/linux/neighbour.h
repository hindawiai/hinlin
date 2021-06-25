<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित __LINUX_NEIGHBOUR_H
#घोषणा __LINUX_NEIGHBOUR_H

#समावेश <linux/types.h>
#समावेश <linux/netlink.h>

काष्ठा ndmsg अणु
	__u8		ndm_family;
	__u8		ndm_pad1;
	__u16		ndm_pad2;
	__s32		ndm_अगरindex;
	__u16		ndm_state;
	__u8		ndm_flags;
	__u8		ndm_type;
पूर्ण;

क्रमागत अणु
	NDA_UNSPEC,
	NDA_DST,
	NDA_LLADDR,
	NDA_CACHEINFO,
	NDA_PROBES,
	NDA_VLAN,
	NDA_PORT,
	NDA_VNI,
	NDA_IFINDEX,
	NDA_MASTER,
	NDA_LINK_NETNSID,
	NDA_SRC_VNI,
	NDA_PROTOCOL,  /* Originator of entry */
	NDA_NH_ID,
	NDA_FDB_EXT_ATTRS,
	__NDA_MAX
पूर्ण;

#घोषणा NDA_MAX (__NDA_MAX - 1)

/*
 *	Neighbor Cache Entry Flags
 */

#घोषणा NTF_USE		0x01
#घोषणा NTF_SELF	0x02
#घोषणा NTF_MASTER	0x04
#घोषणा NTF_PROXY	0x08	/* == ATF_PUBL */
#घोषणा NTF_EXT_LEARNED	0x10
#घोषणा NTF_OFFLOADED   0x20
#घोषणा NTF_STICKY	0x40
#घोषणा NTF_ROUTER	0x80

/*
 *	Neighbor Cache Entry States.
 */

#घोषणा NUD_INCOMPLETE	0x01
#घोषणा NUD_REACHABLE	0x02
#घोषणा NUD_STALE	0x04
#घोषणा NUD_DELAY	0x08
#घोषणा NUD_PROBE	0x10
#घोषणा NUD_FAILED	0x20

/* Dummy states */
#घोषणा NUD_NOARP	0x40
#घोषणा NUD_PERMANENT	0x80
#घोषणा NUD_NONE	0x00

/* NUD_NOARP & NUD_PERMANENT are pseuकरोstates, they never change
   and make no address resolution or NUD.
   NUD_PERMANENT also cannot be deleted by garbage collectors.
 */

काष्ठा nda_cacheinfo अणु
	__u32		ndm_confirmed;
	__u32		ndm_used;
	__u32		ndm_updated;
	__u32		ndm_refcnt;
पूर्ण;

/*****************************************************************
 *		Neighbour tables specअगरic messages.
 *
 * To retrieve the neighbour tables send RTM_GETNEIGHTBL with the
 * NLM_F_DUMP flag set. Every neighbour table configuration is
 * spपढ़ो over multiple messages to aव्योम running पूर्णांकo message
 * size limits on प्रणालीs with many पूर्णांकerfaces. The first message
 * in the sequence transports all not device specअगरic data such as
 * statistics, configuration, and the शेष parameter set.
 * This message is followed by 0..n messages carrying device
 * specअगरic parameter sets.
 * Although the ordering should be sufficient, NDTA_NAME can be
 * used to identअगरy sequences. The initial message can be identअगरied
 * by checking क्रम NDTA_CONFIG. The device specअगरic messages करो
 * not contain this TLV but have NDTPA_IFINDEX set to the
 * corresponding पूर्णांकerface index.
 *
 * To change neighbour table attributes, send RTM_SETNEIGHTBL
 * with NDTA_NAME set. Changeable attribute include NDTA_THRESH[1-3],
 * NDTA_GC_INTERVAL, and all TLVs in NDTA_PARMS unless marked
 * otherwise. Device specअगरic parameter sets can be changed by
 * setting NDTPA_IFINDEX to the पूर्णांकerface index of the corresponding
 * device.
 ****/

काष्ठा ndt_stats अणु
	__u64		ndts_allocs;
	__u64		ndts_destroys;
	__u64		ndts_hash_grows;
	__u64		ndts_res_failed;
	__u64		ndts_lookups;
	__u64		ndts_hits;
	__u64		ndts_rcv_probes_mcast;
	__u64		ndts_rcv_probes_ucast;
	__u64		ndts_periodic_gc_runs;
	__u64		ndts_क्रमced_gc_runs;
	__u64		ndts_table_fulls;
पूर्ण;

क्रमागत अणु
	NDTPA_UNSPEC,
	NDTPA_IFINDEX,			/* u32, unchangeable */
	NDTPA_REFCNT,			/* u32, पढ़ो-only */
	NDTPA_REACHABLE_TIME,		/* u64, पढ़ो-only, msecs */
	NDTPA_BASE_REACHABLE_TIME,	/* u64, msecs */
	NDTPA_RETRANS_TIME,		/* u64, msecs */
	NDTPA_GC_STALETIME,		/* u64, msecs */
	NDTPA_DELAY_PROBE_TIME,		/* u64, msecs */
	NDTPA_QUEUE_LEN,		/* u32 */
	NDTPA_APP_PROBES,		/* u32 */
	NDTPA_UCAST_PROBES,		/* u32 */
	NDTPA_MCAST_PROBES,		/* u32 */
	NDTPA_ANYCAST_DELAY,		/* u64, msecs */
	NDTPA_PROXY_DELAY,		/* u64, msecs */
	NDTPA_PROXY_QLEN,		/* u32 */
	NDTPA_LOCKTIME,			/* u64, msecs */
	NDTPA_QUEUE_LENBYTES,		/* u32 */
	NDTPA_MCAST_REPROBES,		/* u32 */
	NDTPA_PAD,
	__NDTPA_MAX
पूर्ण;
#घोषणा NDTPA_MAX (__NDTPA_MAX - 1)

काष्ठा ndपंचांगsg अणु
	__u8		ndपंचांग_family;
	__u8		ndपंचांग_pad1;
	__u16		ndपंचांग_pad2;
पूर्ण;

काष्ठा ndt_config अणु
	__u16		ndtc_key_len;
	__u16		ndtc_entry_size;
	__u32		ndtc_entries;
	__u32		ndtc_last_flush;	/* delta to now in msecs */
	__u32		ndtc_last_अक्रम;		/* delta to now in msecs */
	__u32		ndtc_hash_rnd;
	__u32		ndtc_hash_mask;
	__u32		ndtc_hash_chain_gc;
	__u32		ndtc_proxy_qlen;
पूर्ण;

क्रमागत अणु
	NDTA_UNSPEC,
	NDTA_NAME,			/* अक्षर *, unchangeable */
	NDTA_THRESH1,			/* u32 */
	NDTA_THRESH2,			/* u32 */
	NDTA_THRESH3,			/* u32 */
	NDTA_CONFIG,			/* काष्ठा ndt_config, पढ़ो-only */
	NDTA_PARMS,			/* nested TLV NDTPA_* */
	NDTA_STATS,			/* काष्ठा ndt_stats, पढ़ो-only */
	NDTA_GC_INTERVAL,		/* u64, msecs */
	NDTA_PAD,
	__NDTA_MAX
पूर्ण;
#घोषणा NDTA_MAX (__NDTA_MAX - 1)

 /* FDB activity notअगरication bits used in NFEA_ACTIVITY_NOTIFY:
  * - FDB_NOTIFY_BIT - notअगरy on activity/expire क्रम any entry
  * - FDB_NOTIFY_INACTIVE_BIT - mark as inactive to aव्योम multiple notअगरications
  */
क्रमागत अणु
	FDB_NOTIFY_BIT		= (1 << 0),
	FDB_NOTIFY_INACTIVE_BIT	= (1 << 1)
पूर्ण;

/* embedded पूर्णांकo NDA_FDB_EXT_ATTRS:
 * [NDA_FDB_EXT_ATTRS] = अणु
 *     [NFEA_ACTIVITY_NOTIFY]
 *     ...
 * पूर्ण
 */
क्रमागत अणु
	NFEA_UNSPEC,
	NFEA_ACTIVITY_NOTIFY,
	NFEA_DONT_REFRESH,
	__NFEA_MAX
पूर्ण;
#घोषणा NFEA_MAX (__NFEA_MAX - 1)

#पूर्ण_अगर
