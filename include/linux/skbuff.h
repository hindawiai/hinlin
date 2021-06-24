<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *	Definitions क्रम the 'struct sk_buff' memory handlers.
 *
 *	Authors:
 *		Alan Cox, <gw4pts@gw4pts.ampr.org>
 *		Florian La Roche, <rzsfl@rz.uni-sb.de>
 */

#अगर_अघोषित _LINUX_SKBUFF_H
#घोषणा _LINUX_SKBUFF_H

#समावेश <linux/kernel.h>
#समावेश <linux/compiler.h>
#समावेश <linux/समय.स>
#समावेश <linux/bug.h>
#समावेश <linux/bvec.h>
#समावेश <linux/cache.h>
#समावेश <linux/rbtree.h>
#समावेश <linux/socket.h>
#समावेश <linux/refcount.h>

#समावेश <linux/atomic.h>
#समावेश <यंत्र/types.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/net.h>
#समावेश <linux/textsearch.h>
#समावेश <net/checksum.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/hrसमयr.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/netdev_features.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/घड़ी.h>
#समावेश <net/flow_dissector.h>
#समावेश <linux/splice.h>
#समावेश <linux/in6.h>
#समावेश <linux/अगर_packet.h>
#समावेश <net/flow.h>
#अगर IS_ENABLED(CONFIG_NF_CONNTRACK)
#समावेश <linux/netfilter/nf_conntrack_common.h>
#पूर्ण_अगर

/* The पूर्णांकerface क्रम checksum offload between the stack and networking drivers
 * is as follows...
 *
 * A. IP checksum related features
 *
 * Drivers advertise checksum offload capabilities in the features of a device.
 * From the stack's poपूर्णांक of view these are capabilities offered by the driver.
 * A driver typically only advertises features that it is capable of offloading
 * to its device.
 *
 * The checksum related features are:
 *
 *	NETIF_F_HW_CSUM	- The driver (or its device) is able to compute one
 *			  IP (one's complement) checksum क्रम any combination
 *			  of protocols or protocol layering. The checksum is
 *			  computed and set in a packet per the CHECKSUM_PARTIAL
 *			  पूर्णांकerface (see below).
 *
 *	NETIF_F_IP_CSUM - Driver (device) is only able to checksum plain
 *			  TCP or UDP packets over IPv4. These are specअगरically
 *			  unencapsulated packets of the क्रमm IPv4|TCP or
 *			  IPv4|UDP where the Protocol field in the IPv4 header
 *			  is TCP or UDP. The IPv4 header may contain IP options.
 *			  This feature cannot be set in features क्रम a device
 *			  with NETIF_F_HW_CSUM also set. This feature is being
 *			  DEPRECATED (see below).
 *
 *	NETIF_F_IPV6_CSUM - Driver (device) is only able to checksum plain
 *			  TCP or UDP packets over IPv6. These are specअगरically
 *			  unencapsulated packets of the क्रमm IPv6|TCP or
 *			  IPv6|UDP where the Next Header field in the IPv6
 *			  header is either TCP or UDP. IPv6 extension headers
 *			  are not supported with this feature. This feature
 *			  cannot be set in features क्रम a device with
 *			  NETIF_F_HW_CSUM also set. This feature is being
 *			  DEPRECATED (see below).
 *
 *	NETIF_F_RXCSUM - Driver (device) perक्रमms receive checksum offload.
 *			 This flag is only used to disable the RX checksum
 *			 feature क्रम a device. The stack will accept receive
 *			 checksum indication in packets received on a device
 *			 regardless of whether NETIF_F_RXCSUM is set.
 *
 * B. Checksumming of received packets by device. Indication of checksum
 *    verअगरication is set in skb->ip_summed. Possible values are:
 *
 * CHECKSUM_NONE:
 *
 *   Device did not checksum this packet e.g. due to lack of capabilities.
 *   The packet contains full (though not verअगरied) checksum in packet but
 *   not in skb->csum. Thus, skb->csum is undefined in this हाल.
 *
 * CHECKSUM_UNNECESSARY:
 *
 *   The hardware you're dealing with doesn't calculate the full checksum
 *   (as in CHECKSUM_COMPLETE), but it करोes parse headers and verअगरy checksums
 *   क्रम specअगरic protocols. For such packets it will set CHECKSUM_UNNECESSARY
 *   अगर their checksums are okay. skb->csum is still undefined in this हाल
 *   though. A driver or device must never modअगरy the checksum field in the
 *   packet even अगर checksum is verअगरied.
 *
 *   CHECKSUM_UNNECESSARY is applicable to following protocols:
 *     TCP: IPv6 and IPv4.
 *     UDP: IPv4 and IPv6. A device may apply CHECKSUM_UNNECESSARY to a
 *       zero UDP checksum क्रम either IPv4 or IPv6, the networking stack
 *       may perक्रमm further validation in this हाल.
 *     GRE: only अगर the checksum is present in the header.
 *     SCTP: indicates the CRC in SCTP header has been validated.
 *     FCOE: indicates the CRC in FC frame has been validated.
 *
 *   skb->csum_level indicates the number of consecutive checksums found in
 *   the packet minus one that have been verअगरied as CHECKSUM_UNNECESSARY.
 *   For instance अगर a device receives an IPv6->UDP->GRE->IPv4->TCP packet
 *   and a device is able to verअगरy the checksums क्रम UDP (possibly zero),
 *   GRE (checksum flag is set) and TCP, skb->csum_level would be set to
 *   two. If the device were only able to verअगरy the UDP checksum and not
 *   GRE, either because it करोesn't support GRE checksum or because GRE
 *   checksum is bad, skb->csum_level would be set to zero (TCP checksum is
 *   not considered in this हाल).
 *
 * CHECKSUM_COMPLETE:
 *
 *   This is the most generic way. The device supplied checksum of the _whole_
 *   packet as seen by netअगर_rx() and fills in skb->csum. This means the
 *   hardware करोesn't need to parse L3/L4 headers to implement this.
 *
 *   Notes:
 *   - Even अगर device supports only some protocols, but is able to produce
 *     skb->csum, it MUST use CHECKSUM_COMPLETE, not CHECKSUM_UNNECESSARY.
 *   - CHECKSUM_COMPLETE is not applicable to SCTP and FCoE protocols.
 *
 * CHECKSUM_PARTIAL:
 *
 *   A checksum is set up to be offloaded to a device as described in the
 *   output description क्रम CHECKSUM_PARTIAL. This may occur on a packet
 *   received directly from another Linux OS, e.g., a भवized Linux kernel
 *   on the same host, or it may be set in the input path in GRO or remote
 *   checksum offload. For the purposes of checksum verअगरication, the checksum
 *   referred to by skb->csum_start + skb->csum_offset and any preceding
 *   checksums in the packet are considered verअगरied. Any checksums in the
 *   packet that are after the checksum being offloaded are not considered to
 *   be verअगरied.
 *
 * C. Checksumming on transmit क्रम non-GSO. The stack requests checksum offload
 *    in the skb->ip_summed क्रम a packet. Values are:
 *
 * CHECKSUM_PARTIAL:
 *
 *   The driver is required to checksum the packet as seen by hard_start_xmit()
 *   from skb->csum_start up to the end, and to record/ग_लिखो the checksum at
 *   offset skb->csum_start + skb->csum_offset. A driver may verअगरy that the
 *   csum_start and csum_offset values are valid values given the length and
 *   offset of the packet, but it should not attempt to validate that the
 *   checksum refers to a legitimate transport layer checksum -- it is the
 *   purview of the stack to validate that csum_start and csum_offset are set
 *   correctly.
 *
 *   When the stack requests checksum offload क्रम a packet, the driver MUST
 *   ensure that the checksum is set correctly. A driver can either offload the
 *   checksum calculation to the device, or call skb_checksum_help (in the हाल
 *   that the device करोes not support offload क्रम a particular checksum).
 *
 *   NETIF_F_IP_CSUM and NETIF_F_IPV6_CSUM are being deprecated in favor of
 *   NETIF_F_HW_CSUM. New devices should use NETIF_F_HW_CSUM to indicate
 *   checksum offload capability.
 *   skb_csum_hwoffload_help() can be called to resolve CHECKSUM_PARTIAL based
 *   on network device checksumming capabilities: अगर a packet करोes not match
 *   them, skb_checksum_help or skb_crc32c_help (depending on the value of
 *   csum_not_inet, see item D.) is called to resolve the checksum.
 *
 * CHECKSUM_NONE:
 *
 *   The skb was alपढ़ोy checksummed by the protocol, or a checksum is not
 *   required.
 *
 * CHECKSUM_UNNECESSARY:
 *
 *   This has the same meaning as CHECKSUM_NONE क्रम checksum offload on
 *   output.
 *
 * CHECKSUM_COMPLETE:
 *   Not used in checksum output. If a driver observes a packet with this value
 *   set in skbuff, it should treat the packet as अगर CHECKSUM_NONE were set.
 *
 * D. Non-IP checksum (CRC) offloads
 *
 *   NETIF_F_SCTP_CRC - This feature indicates that a device is capable of
 *     offloading the SCTP CRC in a packet. To perक्रमm this offload the stack
 *     will set csum_start and csum_offset accordingly, set ip_summed to
 *     CHECKSUM_PARTIAL and set csum_not_inet to 1, to provide an indication in
 *     the skbuff that the CHECKSUM_PARTIAL refers to CRC32c.
 *     A driver that supports both IP checksum offload and SCTP CRC32c offload
 *     must verअगरy which offload is configured क्रम a packet by testing the
 *     value of skb->csum_not_inet; skb_crc32c_csum_help is provided to resolve
 *     CHECKSUM_PARTIAL on skbs where csum_not_inet is set to 1.
 *
 *   NETIF_F_FCOE_CRC - This feature indicates that a device is capable of
 *     offloading the FCOE CRC in a packet. To perक्रमm this offload the stack
 *     will set ip_summed to CHECKSUM_PARTIAL and set csum_start and csum_offset
 *     accordingly. Note that there is no indication in the skbuff that the
 *     CHECKSUM_PARTIAL refers to an FCOE checksum, so a driver that supports
 *     both IP checksum offload and FCOE CRC offload must verअगरy which offload
 *     is configured क्रम a packet, presumably by inspecting packet headers.
 *
 * E. Checksumming on output with GSO.
 *
 * In the हाल of a GSO packet (skb_is_gso(skb) is true), checksum offload
 * is implied by the SKB_GSO_* flags in gso_type. Most obviously, अगर the
 * gso_type is SKB_GSO_TCPV4 or SKB_GSO_TCPV6, TCP checksum offload as
 * part of the GSO operation is implied. If a checksum is being offloaded
 * with GSO then ip_summed is CHECKSUM_PARTIAL, and both csum_start and
 * csum_offset are set to refer to the outermost checksum being offloaded
 * (two offloaded checksums are possible with UDP encapsulation).
 */

/* Don't change this without changing skb_csum_unnecessary! */
#घोषणा CHECKSUM_NONE		0
#घोषणा CHECKSUM_UNNECESSARY	1
#घोषणा CHECKSUM_COMPLETE	2
#घोषणा CHECKSUM_PARTIAL	3

/* Maximum value in skb->csum_level */
#घोषणा SKB_MAX_CSUM_LEVEL	3

#घोषणा SKB_DATA_ALIGN(X)	ALIGN(X, SMP_CACHE_BYTES)
#घोषणा SKB_WITH_OVERHEAD(X)	\
	((X) - SKB_DATA_ALIGN(माप(काष्ठा skb_shared_info)))
#घोषणा SKB_MAX_ORDER(X, ORDER) \
	SKB_WITH_OVERHEAD((PAGE_SIZE << (ORDER)) - (X))
#घोषणा SKB_MAX_HEAD(X)		(SKB_MAX_ORDER((X), 0))
#घोषणा SKB_MAX_ALLOC		(SKB_MAX_ORDER(0, 2))

/* वापस minimum truesize of one skb containing X bytes of data */
#घोषणा SKB_TRUESIZE(X) ((X) +						\
			 SKB_DATA_ALIGN(माप(काष्ठा sk_buff)) +	\
			 SKB_DATA_ALIGN(माप(काष्ठा skb_shared_info)))

काष्ठा ahash_request;
काष्ठा net_device;
काष्ठा scatterlist;
काष्ठा pipe_inode_info;
काष्ठा iov_iter;
काष्ठा napi_काष्ठा;
काष्ठा bpf_prog;
जोड़ bpf_attr;
काष्ठा skb_ext;

#अगर IS_ENABLED(CONFIG_BRIDGE_NETFILTER)
काष्ठा nf_bridge_info अणु
	क्रमागत अणु
		BRNF_PROTO_UNCHANGED,
		BRNF_PROTO_8021Q,
		BRNF_PROTO_PPPOE
	पूर्ण orig_proto:8;
	u8			pkt_otherhost:1;
	u8			in_prerouting:1;
	u8			bridged_dnat:1;
	__u16			frag_max_size;
	काष्ठा net_device	*physindev;

	/* always valid & non-शून्य from FORWARD on, क्रम physdev match */
	काष्ठा net_device	*physoutdev;
	जोड़ अणु
		/* prerouting: detect dnat in orig/reply direction */
		__be32          ipv4_daddr;
		काष्ठा in6_addr ipv6_daddr;

		/* after prerouting + nat detected: store original source
		 * mac since neigh resolution overग_लिखोs it, only used जबतक
		 * skb is out in neigh layer.
		 */
		अक्षर neigh_header[8];
	पूर्ण;
पूर्ण;
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_NET_TC_SKB_EXT)
/* Chain in tc_skb_ext will be used to share the tc chain with
 * ovs recirc_id. It will be set to the current chain by tc
 * and पढ़ो by ovs to recirc_id.
 */
काष्ठा tc_skb_ext अणु
	__u32 chain;
	__u16 mru;
	bool post_ct;
पूर्ण;
#पूर्ण_अगर

काष्ठा sk_buff_head अणु
	/* These two members must be first. */
	काष्ठा sk_buff	*next;
	काष्ठा sk_buff	*prev;

	__u32		qlen;
	spinlock_t	lock;
पूर्ण;

काष्ठा sk_buff;

/* To allow 64K frame to be packed as single skb without frag_list we
 * require 64K/PAGE_SIZE pages plus 1 additional page to allow क्रम
 * buffers which करो not start on a page boundary.
 *
 * Since GRO uses frags we allocate at least 16 regardless of page
 * size.
 */
#अगर (65536/PAGE_SIZE + 1) < 16
#घोषणा MAX_SKB_FRAGS 16UL
#अन्यथा
#घोषणा MAX_SKB_FRAGS (65536/PAGE_SIZE + 1)
#पूर्ण_अगर
बाह्य पूर्णांक sysctl_max_skb_frags;

/* Set skb_shinfo(skb)->gso_size to this in हाल you want skb_segment to
 * segment using its current segmentation instead.
 */
#घोषणा GSO_BY_FRAGS	0xFFFF

प्रकार काष्ठा bio_vec skb_frag_t;

/**
 * skb_frag_size() - Returns the size of a skb fragment
 * @frag: skb fragment
 */
अटल अंतरभूत अचिन्हित पूर्णांक skb_frag_size(स्थिर skb_frag_t *frag)
अणु
	वापस frag->bv_len;
पूर्ण

/**
 * skb_frag_size_set() - Sets the size of a skb fragment
 * @frag: skb fragment
 * @size: size of fragment
 */
अटल अंतरभूत व्योम skb_frag_size_set(skb_frag_t *frag, अचिन्हित पूर्णांक size)
अणु
	frag->bv_len = size;
पूर्ण

/**
 * skb_frag_size_add() - Increments the size of a skb fragment by @delta
 * @frag: skb fragment
 * @delta: value to add
 */
अटल अंतरभूत व्योम skb_frag_size_add(skb_frag_t *frag, पूर्णांक delta)
अणु
	frag->bv_len += delta;
पूर्ण

/**
 * skb_frag_size_sub() - Decrements the size of a skb fragment by @delta
 * @frag: skb fragment
 * @delta: value to subtract
 */
अटल अंतरभूत व्योम skb_frag_size_sub(skb_frag_t *frag, पूर्णांक delta)
अणु
	frag->bv_len -= delta;
पूर्ण

/**
 * skb_frag_must_loop - Test अगर %p is a high memory page
 * @p: fragment's page
 */
अटल अंतरभूत bool skb_frag_must_loop(काष्ठा page *p)
अणु
#अगर defined(CONFIG_HIGHMEM)
	अगर (IS_ENABLED(CONFIG_DEBUG_KMAP_LOCAL_FORCE_MAP) || PageHighMem(p))
		वापस true;
#पूर्ण_अगर
	वापस false;
पूर्ण

/**
 *	skb_frag_क्रमeach_page - loop over pages in a fragment
 *
 *	@f:		skb frag to operate on
 *	@f_off:		offset from start of f->bv_page
 *	@f_len:		length from f_off to loop over
 *	@p:		(temp var) current page
 *	@p_off:		(temp var) offset from start of current page,
 *	                           non-zero only on first page.
 *	@p_len:		(temp var) length in current page,
 *				   < PAGE_SIZE only on first and last page.
 *	@copied:	(temp var) length so far, excluding current p_len.
 *
 *	A fragment can hold a compound page, in which हाल per-page
 *	operations, notably kmap_atomic, must be called क्रम each
 *	regular page.
 */
#घोषणा skb_frag_क्रमeach_page(f, f_off, f_len, p, p_off, p_len, copied)	\
	क्रम (p = skb_frag_page(f) + ((f_off) >> PAGE_SHIFT),		\
	     p_off = (f_off) & (PAGE_SIZE - 1),				\
	     p_len = skb_frag_must_loop(p) ?				\
	     min_t(u32, f_len, PAGE_SIZE - p_off) : f_len,		\
	     copied = 0;						\
	     copied < f_len;						\
	     copied += p_len, p++, p_off = 0,				\
	     p_len = min_t(u32, f_len - copied, PAGE_SIZE))		\

#घोषणा HAVE_HW_TIME_STAMP

/**
 * काष्ठा skb_shared_hwtstamps - hardware समय stamps
 * @hwtstamp:	hardware समय stamp transक्रमmed पूर्णांकo duration
 *		since arbitrary poपूर्णांक in समय
 *
 * Software समय stamps generated by kसमय_get_real() are stored in
 * skb->tstamp.
 *
 * hwtstamps can only be compared against other hwtstamps from
 * the same device.
 *
 * This काष्ठाure is attached to packets as part of the
 * &skb_shared_info. Use skb_hwtstamps() to get a poपूर्णांकer.
 */
काष्ठा skb_shared_hwtstamps अणु
	kसमय_प्रकार	hwtstamp;
पूर्ण;

/* Definitions क्रम tx_flags in काष्ठा skb_shared_info */
क्रमागत अणु
	/* generate hardware समय stamp */
	SKBTX_HW_TSTAMP = 1 << 0,

	/* generate software समय stamp when queueing packet to NIC */
	SKBTX_SW_TSTAMP = 1 << 1,

	/* device driver is going to provide hardware समय stamp */
	SKBTX_IN_PROGRESS = 1 << 2,

	/* generate wअगरi status inक्रमmation (where possible) */
	SKBTX_WIFI_STATUS = 1 << 4,

	/* generate software समय stamp when entering packet scheduling */
	SKBTX_SCHED_TSTAMP = 1 << 6,
पूर्ण;

#घोषणा SKBTX_ANY_SW_TSTAMP	(SKBTX_SW_TSTAMP    | \
				 SKBTX_SCHED_TSTAMP)
#घोषणा SKBTX_ANY_TSTAMP	(SKBTX_HW_TSTAMP | SKBTX_ANY_SW_TSTAMP)

/* Definitions क्रम flags in काष्ठा skb_shared_info */
क्रमागत अणु
	/* use zcopy routines */
	SKBFL_ZEROCOPY_ENABLE = BIT(0),

	/* This indicates at least one fragment might be overwritten
	 * (as in vmsplice(), sendfile() ...)
	 * If we need to compute a TX checksum, we'll need to copy
	 * all frags to aव्योम possible bad checksum
	 */
	SKBFL_SHARED_FRAG = BIT(1),
पूर्ण;

#घोषणा SKBFL_ZEROCOPY_FRAG	(SKBFL_ZEROCOPY_ENABLE | SKBFL_SHARED_FRAG)

/*
 * The callback notअगरies userspace to release buffers when skb DMA is करोne in
 * lower device, the skb last reference should be 0 when calling this.
 * The zerocopy_success argument is true अगर zero copy transmit occurred,
 * false on data copy or out of memory error caused by data copy attempt.
 * The ctx field is used to track device context.
 * The desc field is used to track userspace buffer index.
 */
काष्ठा ubuf_info अणु
	व्योम (*callback)(काष्ठा sk_buff *, काष्ठा ubuf_info *,
			 bool zerocopy_success);
	जोड़ अणु
		काष्ठा अणु
			अचिन्हित दीर्घ desc;
			व्योम *ctx;
		पूर्ण;
		काष्ठा अणु
			u32 id;
			u16 len;
			u16 zerocopy:1;
			u32 bytelen;
		पूर्ण;
	पूर्ण;
	refcount_t refcnt;
	u8 flags;

	काष्ठा mmpin अणु
		काष्ठा user_काष्ठा *user;
		अचिन्हित पूर्णांक num_pg;
	पूर्ण mmp;
पूर्ण;

#घोषणा skb_uarg(SKB)	((काष्ठा ubuf_info *)(skb_shinfo(SKB)->deकाष्ठाor_arg))

पूर्णांक mm_account_pinned_pages(काष्ठा mmpin *mmp, माप_प्रकार size);
व्योम mm_unaccount_pinned_pages(काष्ठा mmpin *mmp);

काष्ठा ubuf_info *msg_zerocopy_alloc(काष्ठा sock *sk, माप_प्रकार size);
काष्ठा ubuf_info *msg_zerocopy_पुनः_स्मृति(काष्ठा sock *sk, माप_प्रकार size,
				       काष्ठा ubuf_info *uarg);

व्योम msg_zerocopy_put_पात(काष्ठा ubuf_info *uarg, bool have_uref);

व्योम msg_zerocopy_callback(काष्ठा sk_buff *skb, काष्ठा ubuf_info *uarg,
			   bool success);

पूर्णांक skb_zerocopy_iter_dgram(काष्ठा sk_buff *skb, काष्ठा msghdr *msg, पूर्णांक len);
पूर्णांक skb_zerocopy_iter_stream(काष्ठा sock *sk, काष्ठा sk_buff *skb,
			     काष्ठा msghdr *msg, पूर्णांक len,
			     काष्ठा ubuf_info *uarg);

/* This data is invariant across clones and lives at
 * the end of the header data, ie. at skb->end.
 */
काष्ठा skb_shared_info अणु
	__u8		flags;
	__u8		meta_len;
	__u8		nr_frags;
	__u8		tx_flags;
	अचिन्हित लघु	gso_size;
	/* Warning: this field is not always filled in (UFO)! */
	अचिन्हित लघु	gso_segs;
	काष्ठा sk_buff	*frag_list;
	काष्ठा skb_shared_hwtstamps hwtstamps;
	अचिन्हित पूर्णांक	gso_type;
	u32		tskey;

	/*
	 * Warning : all fields beक्रमe dataref are cleared in __alloc_skb()
	 */
	atomic_t	dataref;

	/* Intermediate layers must ensure that deकाष्ठाor_arg
	 * reमुख्यs valid until skb deकाष्ठाor */
	व्योम *		deकाष्ठाor_arg;

	/* must be last field, see pskb_expand_head() */
	skb_frag_t	frags[MAX_SKB_FRAGS];
पूर्ण;

/* We भागide dataref पूर्णांकo two halves.  The higher 16 bits hold references
 * to the payload part of skb->data.  The lower 16 bits hold references to
 * the entire skb->data.  A clone of a headerless skb holds the length of
 * the header in skb->hdr_len.
 *
 * All users must obey the rule that the skb->data reference count must be
 * greater than or equal to the payload reference count.
 *
 * Holding a reference to the payload part means that the user करोes not
 * care about modअगरications to the header part of skb->data.
 */
#घोषणा SKB_DATAREF_SHIFT 16
#घोषणा SKB_DATAREF_MASK ((1 << SKB_DATAREF_SHIFT) - 1)


क्रमागत अणु
	SKB_FCLONE_UNAVAILABLE,	/* skb has no fclone (from head_cache) */
	SKB_FCLONE_ORIG,	/* orig skb (from fclone_cache) */
	SKB_FCLONE_CLONE,	/* companion fclone skb (from fclone_cache) */
पूर्ण;

क्रमागत अणु
	SKB_GSO_TCPV4 = 1 << 0,

	/* This indicates the skb is from an untrusted source. */
	SKB_GSO_DODGY = 1 << 1,

	/* This indicates the tcp segment has CWR set. */
	SKB_GSO_TCP_ECN = 1 << 2,

	SKB_GSO_TCP_FIXEDID = 1 << 3,

	SKB_GSO_TCPV6 = 1 << 4,

	SKB_GSO_FCOE = 1 << 5,

	SKB_GSO_GRE = 1 << 6,

	SKB_GSO_GRE_CSUM = 1 << 7,

	SKB_GSO_IPXIP4 = 1 << 8,

	SKB_GSO_IPXIP6 = 1 << 9,

	SKB_GSO_UDP_TUNNEL = 1 << 10,

	SKB_GSO_UDP_TUNNEL_CSUM = 1 << 11,

	SKB_GSO_PARTIAL = 1 << 12,

	SKB_GSO_TUNNEL_REMCSUM = 1 << 13,

	SKB_GSO_SCTP = 1 << 14,

	SKB_GSO_ESP = 1 << 15,

	SKB_GSO_UDP = 1 << 16,

	SKB_GSO_UDP_L4 = 1 << 17,

	SKB_GSO_FRAGLIST = 1 << 18,
पूर्ण;

#अगर BITS_PER_LONG > 32
#घोषणा NET_SKBUFF_DATA_USES_OFFSET 1
#पूर्ण_अगर

#अगर_घोषित NET_SKBUFF_DATA_USES_OFFSET
प्रकार अचिन्हित पूर्णांक sk_buff_data_t;
#अन्यथा
प्रकार अचिन्हित अक्षर *sk_buff_data_t;
#पूर्ण_अगर

/**
 *	काष्ठा sk_buff - socket buffer
 *	@next: Next buffer in list
 *	@prev: Previous buffer in list
 *	@tstamp: Time we arrived/left
 *	@skb_mstamp_ns: (aka @tstamp) earliest departure समय; start poपूर्णांक
 *		क्रम retransmit समयr
 *	@rbnode: RB tree node, alternative to next/prev क्रम netem/tcp
 *	@list: queue head
 *	@sk: Socket we are owned by
 *	@ip_defrag_offset: (aka @sk) alternate use of @sk, used in
 *		fragmentation management
 *	@dev: Device we arrived on/are leaving by
 *	@dev_scratch: (aka @dev) alternate use of @dev when @dev would be %शून्य
 *	@cb: Control buffer. Free क्रम use by every layer. Put निजी vars here
 *	@_skb_refdst: destination entry (with norefcount bit)
 *	@sp: the security path, used क्रम xfrm
 *	@len: Length of actual data
 *	@data_len: Data length
 *	@mac_len: Length of link layer header
 *	@hdr_len: writable header length of cloned skb
 *	@csum: Checksum (must include start/offset pair)
 *	@csum_start: Offset from skb->head where checksumming should start
 *	@csum_offset: Offset from csum_start where checksum should be stored
 *	@priority: Packet queueing priority
 *	@ignore_df: allow local fragmentation
 *	@cloned: Head may be cloned (check refcnt to be sure)
 *	@ip_summed: Driver fed us an IP checksum
 *	@nohdr: Payload reference only, must not modअगरy header
 *	@pkt_type: Packet class
 *	@fclone: skbuff clone status
 *	@ipvs_property: skbuff is owned by ipvs
 *	@inner_protocol_type: whether the inner protocol is
 *		ENCAP_TYPE_ETHER or ENCAP_TYPE_IPPROTO
 *	@remcsum_offload: remote checksum offload is enabled
 *	@offload_fwd_mark: Packet was L2-क्रमwarded in hardware
 *	@offload_l3_fwd_mark: Packet was L3-क्रमwarded in hardware
 *	@tc_skip_classअगरy: करो not classअगरy packet. set by IFB device
 *	@tc_at_ingress: used within tc_classअगरy to distinguish in/egress
 *	@redirected: packet was redirected by packet classअगरier
 *	@from_ingress: packet was redirected from the ingress path
 *	@peeked: this packet has been seen alपढ़ोy, so stats have been
 *		करोne क्रम it, करोn't करो them again
 *	@nf_trace: netfilter packet trace flag
 *	@protocol: Packet protocol from driver
 *	@deकाष्ठाor: Deकाष्ठा function
 *	@tcp_tsorted_anchor: list काष्ठाure क्रम TCP (tp->tsorted_sent_queue)
 *	@_sk_redir: socket redirection inक्रमmation क्रम skmsg
 *	@_nfct: Associated connection, अगर any (with nfctinfo bits)
 *	@nf_bridge: Saved data about a bridged frame - see br_netfilter.c
 *	@skb_iअगर: अगरindex of device we arrived on
 *	@tc_index: Traffic control index
 *	@hash: the packet hash
 *	@queue_mapping: Queue mapping क्रम multiqueue devices
 *	@head_frag: skb was allocated from page fragments,
 *		not allocated by kदो_स्मृति() or vदो_स्मृति().
 *	@pfmeदो_स्मृति: skbuff was allocated from PFMEMALLOC reserves
 *	@active_extensions: active extensions (skb_ext_id types)
 *	@ndisc_nodetype: router type (from link layer)
 *	@ooo_okay: allow the mapping of a socket to a queue to be changed
 *	@l4_hash: indicate hash is a canonical 4-tuple hash over transport
 *		ports.
 *	@sw_hash: indicates hash was computed in software stack
 *	@wअगरi_acked_valid: wअगरi_acked was set
 *	@wअगरi_acked: whether frame was acked on wअगरi or not
 *	@no_fcs:  Request NIC to treat last 4 bytes as Ethernet FCS
 *	@encapsulation: indicates the inner headers in the skbuff are valid
 *	@encap_hdr_csum: software checksum is needed
 *	@csum_valid: checksum is alपढ़ोy valid
 *	@csum_not_inet: use CRC32c to resolve CHECKSUM_PARTIAL
 *	@csum_complete_sw: checksum was completed by software
 *	@csum_level: indicates the number of consecutive checksums found in
 *		the packet minus one that have been verअगरied as
 *		CHECKSUM_UNNECESSARY (max 3)
 *	@dst_pending_confirm: need to confirm neighbour
 *	@decrypted: Decrypted SKB
 *	@napi_id: id of the NAPI काष्ठा this skb came from
 *	@sender_cpu: (aka @napi_id) source CPU in XPS
 *	@secmark: security marking
 *	@mark: Generic packet mark
 *	@reserved_tailroom: (aka @mark) number of bytes of मुक्त space available
 *		at the tail of an sk_buff
 *	@vlan_present: VLAN tag is present
 *	@vlan_proto: vlan encapsulation protocol
 *	@vlan_tci: vlan tag control inक्रमmation
 *	@inner_protocol: Protocol (encapsulation)
 *	@inner_ipproto: (aka @inner_protocol) stores ipproto when
 *		skb->inner_protocol_type == ENCAP_TYPE_IPPROTO;
 *	@inner_transport_header: Inner transport layer header (encapsulation)
 *	@inner_network_header: Network layer header (encapsulation)
 *	@inner_mac_header: Link layer header (encapsulation)
 *	@transport_header: Transport layer header
 *	@network_header: Network layer header
 *	@mac_header: Link layer header
 *	@kcov_handle: KCOV remote handle क्रम remote coverage collection
 *	@tail: Tail poपूर्णांकer
 *	@end: End poपूर्णांकer
 *	@head: Head of buffer
 *	@data: Data head poपूर्णांकer
 *	@truesize: Buffer size
 *	@users: User count - see अणुdatagram,tcpपूर्ण.c
 *	@extensions: allocated extensions, valid अगर active_extensions is nonzero
 */

काष्ठा sk_buff अणु
	जोड़ अणु
		काष्ठा अणु
			/* These two members must be first. */
			काष्ठा sk_buff		*next;
			काष्ठा sk_buff		*prev;

			जोड़ अणु
				काष्ठा net_device	*dev;
				/* Some protocols might use this space to store inक्रमmation,
				 * जबतक device poपूर्णांकer would be शून्य.
				 * UDP receive path is one user.
				 */
				अचिन्हित दीर्घ		dev_scratch;
			पूर्ण;
		पूर्ण;
		काष्ठा rb_node		rbnode; /* used in netem, ip4 defrag, and tcp stack */
		काष्ठा list_head	list;
	पूर्ण;

	जोड़ अणु
		काष्ठा sock		*sk;
		पूर्णांक			ip_defrag_offset;
	पूर्ण;

	जोड़ अणु
		kसमय_प्रकार		tstamp;
		u64		skb_mstamp_ns; /* earliest departure समय */
	पूर्ण;
	/*
	 * This is the control buffer. It is मुक्त to use क्रम every
	 * layer. Please put your निजी variables there. If you
	 * want to keep them across layers you have to करो a skb_clone()
	 * first. This is owned by whoever has the skb queued ATM.
	 */
	अक्षर			cb[48] __aligned(8);

	जोड़ अणु
		काष्ठा अणु
			अचिन्हित दीर्घ	_skb_refdst;
			व्योम		(*deकाष्ठाor)(काष्ठा sk_buff *skb);
		पूर्ण;
		काष्ठा list_head	tcp_tsorted_anchor;
#अगर_घोषित CONFIG_NET_SOCK_MSG
		अचिन्हित दीर्घ		_sk_redir;
#पूर्ण_अगर
	पूर्ण;

#अगर defined(CONFIG_NF_CONNTRACK) || defined(CONFIG_NF_CONNTRACK_MODULE)
	अचिन्हित दीर्घ		 _nfct;
#पूर्ण_अगर
	अचिन्हित पूर्णांक		len,
				data_len;
	__u16			mac_len,
				hdr_len;

	/* Following fields are _not_ copied in __copy_skb_header()
	 * Note that queue_mapping is here mostly to fill a hole.
	 */
	__u16			queue_mapping;

/* अगर you move cloned around you also must adapt those स्थिरants */
#अगर_घोषित __BIG_ENDIAN_BITFIELD
#घोषणा CLONED_MASK	(1 << 7)
#अन्यथा
#घोषणा CLONED_MASK	1
#पूर्ण_अगर
#घोषणा CLONED_OFFSET()		दुरत्व(काष्ठा sk_buff, __cloned_offset)

	/* निजी: */
	__u8			__cloned_offset[0];
	/* खुला: */
	__u8			cloned:1,
				nohdr:1,
				fclone:2,
				peeked:1,
				head_frag:1,
				pfmeदो_स्मृति:1;
#अगर_घोषित CONFIG_SKB_EXTENSIONS
	__u8			active_extensions;
#पूर्ण_अगर
	/* fields enबंदd in headers_start/headers_end are copied
	 * using a single स_नकल() in __copy_skb_header()
	 */
	/* निजी: */
	__u32			headers_start[0];
	/* खुला: */

/* अगर you move pkt_type around you also must adapt those स्थिरants */
#अगर_घोषित __BIG_ENDIAN_BITFIELD
#घोषणा PKT_TYPE_MAX	(7 << 5)
#अन्यथा
#घोषणा PKT_TYPE_MAX	7
#पूर्ण_अगर
#घोषणा PKT_TYPE_OFFSET()	दुरत्व(काष्ठा sk_buff, __pkt_type_offset)

	/* निजी: */
	__u8			__pkt_type_offset[0];
	/* खुला: */
	__u8			pkt_type:3;
	__u8			ignore_df:1;
	__u8			nf_trace:1;
	__u8			ip_summed:2;
	__u8			ooo_okay:1;

	__u8			l4_hash:1;
	__u8			sw_hash:1;
	__u8			wअगरi_acked_valid:1;
	__u8			wअगरi_acked:1;
	__u8			no_fcs:1;
	/* Indicates the inner headers are valid in the skbuff. */
	__u8			encapsulation:1;
	__u8			encap_hdr_csum:1;
	__u8			csum_valid:1;

#अगर_घोषित __BIG_ENDIAN_BITFIELD
#घोषणा PKT_VLAN_PRESENT_BIT	7
#अन्यथा
#घोषणा PKT_VLAN_PRESENT_BIT	0
#पूर्ण_अगर
#घोषणा PKT_VLAN_PRESENT_OFFSET()	दुरत्व(काष्ठा sk_buff, __pkt_vlan_present_offset)
	/* निजी: */
	__u8			__pkt_vlan_present_offset[0];
	/* खुला: */
	__u8			vlan_present:1;
	__u8			csum_complete_sw:1;
	__u8			csum_level:2;
	__u8			csum_not_inet:1;
	__u8			dst_pending_confirm:1;
#अगर_घोषित CONFIG_IPV6_NDISC_NODETYPE
	__u8			ndisc_nodetype:2;
#पूर्ण_अगर

	__u8			ipvs_property:1;
	__u8			inner_protocol_type:1;
	__u8			remcsum_offload:1;
#अगर_घोषित CONFIG_NET_SWITCHDEV
	__u8			offload_fwd_mark:1;
	__u8			offload_l3_fwd_mark:1;
#पूर्ण_अगर
#अगर_घोषित CONFIG_NET_CLS_ACT
	__u8			tc_skip_classअगरy:1;
	__u8			tc_at_ingress:1;
#पूर्ण_अगर
#अगर_घोषित CONFIG_NET_REसूचीECT
	__u8			redirected:1;
	__u8			from_ingress:1;
#पूर्ण_अगर
#अगर_घोषित CONFIG_TLS_DEVICE
	__u8			decrypted:1;
#पूर्ण_अगर

#अगर_घोषित CONFIG_NET_SCHED
	__u16			tc_index;	/* traffic control index */
#पूर्ण_अगर

	जोड़ अणु
		__wsum		csum;
		काष्ठा अणु
			__u16	csum_start;
			__u16	csum_offset;
		पूर्ण;
	पूर्ण;
	__u32			priority;
	पूर्णांक			skb_iअगर;
	__u32			hash;
	__be16			vlan_proto;
	__u16			vlan_tci;
#अगर defined(CONFIG_NET_RX_BUSY_POLL) || defined(CONFIG_XPS)
	जोड़ अणु
		अचिन्हित पूर्णांक	napi_id;
		अचिन्हित पूर्णांक	sender_cpu;
	पूर्ण;
#पूर्ण_अगर
#अगर_घोषित CONFIG_NETWORK_SECMARK
	__u32		secmark;
#पूर्ण_अगर

	जोड़ अणु
		__u32		mark;
		__u32		reserved_tailroom;
	पूर्ण;

	जोड़ अणु
		__be16		inner_protocol;
		__u8		inner_ipproto;
	पूर्ण;

	__u16			inner_transport_header;
	__u16			inner_network_header;
	__u16			inner_mac_header;

	__be16			protocol;
	__u16			transport_header;
	__u16			network_header;
	__u16			mac_header;

#अगर_घोषित CONFIG_KCOV
	u64			kcov_handle;
#पूर्ण_अगर

	/* निजी: */
	__u32			headers_end[0];
	/* खुला: */

	/* These elements must be at the end, see alloc_skb() क्रम details.  */
	sk_buff_data_t		tail;
	sk_buff_data_t		end;
	अचिन्हित अक्षर		*head,
				*data;
	अचिन्हित पूर्णांक		truesize;
	refcount_t		users;

#अगर_घोषित CONFIG_SKB_EXTENSIONS
	/* only useable after checking ->active_extensions != 0 */
	काष्ठा skb_ext		*extensions;
#पूर्ण_अगर
पूर्ण;

#अगर_घोषित __KERNEL__
/*
 *	Handling routines are only of पूर्णांकerest to the kernel
 */

#घोषणा SKB_ALLOC_FCLONE	0x01
#घोषणा SKB_ALLOC_RX		0x02
#घोषणा SKB_ALLOC_NAPI		0x04

/**
 * skb_pfmeदो_स्मृति - Test अगर the skb was allocated from PFMEMALLOC reserves
 * @skb: buffer
 */
अटल अंतरभूत bool skb_pfmeदो_स्मृति(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस unlikely(skb->pfmeदो_स्मृति);
पूर्ण

/*
 * skb might have a dst poपूर्णांकer attached, refcounted or not.
 * _skb_refdst low order bit is set अगर refcount was _not_ taken
 */
#घोषणा SKB_DST_NOREF	1UL
#घोषणा SKB_DST_PTRMASK	~(SKB_DST_NOREF)

/**
 * skb_dst - वापसs skb dst_entry
 * @skb: buffer
 *
 * Returns skb dst_entry, regardless of reference taken or not.
 */
अटल अंतरभूत काष्ठा dst_entry *skb_dst(स्थिर काष्ठा sk_buff *skb)
अणु
	/* If refdst was not refcounted, check we still are in a
	 * rcu_पढ़ो_lock section
	 */
	WARN_ON((skb->_skb_refdst & SKB_DST_NOREF) &&
		!rcu_पढ़ो_lock_held() &&
		!rcu_पढ़ो_lock_bh_held());
	वापस (काष्ठा dst_entry *)(skb->_skb_refdst & SKB_DST_PTRMASK);
पूर्ण

/**
 * skb_dst_set - sets skb dst
 * @skb: buffer
 * @dst: dst entry
 *
 * Sets skb dst, assuming a reference was taken on dst and should
 * be released by skb_dst_drop()
 */
अटल अंतरभूत व्योम skb_dst_set(काष्ठा sk_buff *skb, काष्ठा dst_entry *dst)
अणु
	skb->_skb_refdst = (अचिन्हित दीर्घ)dst;
पूर्ण

/**
 * skb_dst_set_noref - sets skb dst, hopefully, without taking reference
 * @skb: buffer
 * @dst: dst entry
 *
 * Sets skb dst, assuming a reference was not taken on dst.
 * If dst entry is cached, we करो not take reference and dst_release
 * will be aव्योमed by refdst_drop. If dst entry is not cached, we take
 * reference, so that last dst_release can destroy the dst immediately.
 */
अटल अंतरभूत व्योम skb_dst_set_noref(काष्ठा sk_buff *skb, काष्ठा dst_entry *dst)
अणु
	WARN_ON(!rcu_पढ़ो_lock_held() && !rcu_पढ़ो_lock_bh_held());
	skb->_skb_refdst = (अचिन्हित दीर्घ)dst | SKB_DST_NOREF;
पूर्ण

/**
 * skb_dst_is_noref - Test अगर skb dst isn't refcounted
 * @skb: buffer
 */
अटल अंतरभूत bool skb_dst_is_noref(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस (skb->_skb_refdst & SKB_DST_NOREF) && skb_dst(skb);
पूर्ण

/**
 * skb_rtable - Returns the skb &rtable
 * @skb: buffer
 */
अटल अंतरभूत काष्ठा rtable *skb_rtable(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस (काष्ठा rtable *)skb_dst(skb);
पूर्ण

/* For mangling skb->pkt_type from user space side from applications
 * such as nft, tc, etc, we only allow a conservative subset of
 * possible pkt_types to be set.
*/
अटल अंतरभूत bool skb_pkt_type_ok(u32 ptype)
अणु
	वापस ptype <= PACKET_OTHERHOST;
पूर्ण

/**
 * skb_napi_id - Returns the skb's NAPI id
 * @skb: buffer
 */
अटल अंतरभूत अचिन्हित पूर्णांक skb_napi_id(स्थिर काष्ठा sk_buff *skb)
अणु
#अगर_घोषित CONFIG_NET_RX_BUSY_POLL
	वापस skb->napi_id;
#अन्यथा
	वापस 0;
#पूर्ण_अगर
पूर्ण

/**
 * skb_unref - decrement the skb's reference count
 * @skb: buffer
 *
 * Returns true अगर we can मुक्त the skb.
 */
अटल अंतरभूत bool skb_unref(काष्ठा sk_buff *skb)
अणु
	अगर (unlikely(!skb))
		वापस false;
	अगर (likely(refcount_पढ़ो(&skb->users) == 1))
		smp_rmb();
	अन्यथा अगर (likely(!refcount_dec_and_test(&skb->users)))
		वापस false;

	वापस true;
पूर्ण

व्योम skb_release_head_state(काष्ठा sk_buff *skb);
व्योम kमुक्त_skb(काष्ठा sk_buff *skb);
व्योम kमुक्त_skb_list(काष्ठा sk_buff *segs);
व्योम skb_dump(स्थिर अक्षर *level, स्थिर काष्ठा sk_buff *skb, bool full_pkt);
व्योम skb_tx_error(काष्ठा sk_buff *skb);

#अगर_घोषित CONFIG_TRACEPOINTS
व्योम consume_skb(काष्ठा sk_buff *skb);
#अन्यथा
अटल अंतरभूत व्योम consume_skb(काष्ठा sk_buff *skb)
अणु
	वापस kमुक्त_skb(skb);
पूर्ण
#पूर्ण_अगर

व्योम __consume_stateless_skb(काष्ठा sk_buff *skb);
व्योम  __kमुक्त_skb(काष्ठा sk_buff *skb);
बाह्य काष्ठा kmem_cache *skbuff_head_cache;

व्योम kमुक्त_skb_partial(काष्ठा sk_buff *skb, bool head_stolen);
bool skb_try_coalesce(काष्ठा sk_buff *to, काष्ठा sk_buff *from,
		      bool *fragstolen, पूर्णांक *delta_truesize);

काष्ठा sk_buff *__alloc_skb(अचिन्हित पूर्णांक size, gfp_t priority, पूर्णांक flags,
			    पूर्णांक node);
काष्ठा sk_buff *__build_skb(व्योम *data, अचिन्हित पूर्णांक frag_size);
काष्ठा sk_buff *build_skb(व्योम *data, अचिन्हित पूर्णांक frag_size);
काष्ठा sk_buff *build_skb_around(काष्ठा sk_buff *skb,
				 व्योम *data, अचिन्हित पूर्णांक frag_size);

काष्ठा sk_buff *napi_build_skb(व्योम *data, अचिन्हित पूर्णांक frag_size);

/**
 * alloc_skb - allocate a network buffer
 * @size: size to allocate
 * @priority: allocation mask
 *
 * This function is a convenient wrapper around __alloc_skb().
 */
अटल अंतरभूत काष्ठा sk_buff *alloc_skb(अचिन्हित पूर्णांक size,
					gfp_t priority)
अणु
	वापस __alloc_skb(size, priority, 0, NUMA_NO_NODE);
पूर्ण

काष्ठा sk_buff *alloc_skb_with_frags(अचिन्हित दीर्घ header_len,
				     अचिन्हित दीर्घ data_len,
				     पूर्णांक max_page_order,
				     पूर्णांक *errcode,
				     gfp_t gfp_mask);
काष्ठा sk_buff *alloc_skb_क्रम_msg(काष्ठा sk_buff *first);

/* Layout of fast clones : [skb1][skb2][fclone_ref] */
काष्ठा sk_buff_fclones अणु
	काष्ठा sk_buff	skb1;

	काष्ठा sk_buff	skb2;

	refcount_t	fclone_ref;
पूर्ण;

/**
 *	skb_fclone_busy - check अगर fclone is busy
 *	@sk: socket
 *	@skb: buffer
 *
 * Returns true अगर skb is a fast clone, and its clone is not मुक्तd.
 * Some drivers call skb_orphan() in their nकरो_start_xmit(),
 * so we also check that this didnt happen.
 */
अटल अंतरभूत bool skb_fclone_busy(स्थिर काष्ठा sock *sk,
				   स्थिर काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा sk_buff_fclones *fclones;

	fclones = container_of(skb, काष्ठा sk_buff_fclones, skb1);

	वापस skb->fclone == SKB_FCLONE_ORIG &&
	       refcount_पढ़ो(&fclones->fclone_ref) > 1 &&
	       READ_ONCE(fclones->skb2.sk) == sk;
पूर्ण

/**
 * alloc_skb_fclone - allocate a network buffer from fclone cache
 * @size: size to allocate
 * @priority: allocation mask
 *
 * This function is a convenient wrapper around __alloc_skb().
 */
अटल अंतरभूत काष्ठा sk_buff *alloc_skb_fclone(अचिन्हित पूर्णांक size,
					       gfp_t priority)
अणु
	वापस __alloc_skb(size, priority, SKB_ALLOC_FCLONE, NUMA_NO_NODE);
पूर्ण

काष्ठा sk_buff *skb_morph(काष्ठा sk_buff *dst, काष्ठा sk_buff *src);
व्योम skb_headers_offset_update(काष्ठा sk_buff *skb, पूर्णांक off);
पूर्णांक skb_copy_ubufs(काष्ठा sk_buff *skb, gfp_t gfp_mask);
काष्ठा sk_buff *skb_clone(काष्ठा sk_buff *skb, gfp_t priority);
व्योम skb_copy_header(काष्ठा sk_buff *new, स्थिर काष्ठा sk_buff *old);
काष्ठा sk_buff *skb_copy(स्थिर काष्ठा sk_buff *skb, gfp_t priority);
काष्ठा sk_buff *__pskb_copy_fclone(काष्ठा sk_buff *skb, पूर्णांक headroom,
				   gfp_t gfp_mask, bool fclone);
अटल अंतरभूत काष्ठा sk_buff *__pskb_copy(काष्ठा sk_buff *skb, पूर्णांक headroom,
					  gfp_t gfp_mask)
अणु
	वापस __pskb_copy_fclone(skb, headroom, gfp_mask, false);
पूर्ण

पूर्णांक pskb_expand_head(काष्ठा sk_buff *skb, पूर्णांक nhead, पूर्णांक ntail, gfp_t gfp_mask);
काष्ठा sk_buff *skb_पुनः_स्मृति_headroom(काष्ठा sk_buff *skb,
				     अचिन्हित पूर्णांक headroom);
काष्ठा sk_buff *skb_copy_expand(स्थिर काष्ठा sk_buff *skb, पूर्णांक newheadroom,
				पूर्णांक newtailroom, gfp_t priority);
पूर्णांक __must_check skb_to_sgvec_nomark(काष्ठा sk_buff *skb, काष्ठा scatterlist *sg,
				     पूर्णांक offset, पूर्णांक len);
पूर्णांक __must_check skb_to_sgvec(काष्ठा sk_buff *skb, काष्ठा scatterlist *sg,
			      पूर्णांक offset, पूर्णांक len);
पूर्णांक skb_cow_data(काष्ठा sk_buff *skb, पूर्णांक tailbits, काष्ठा sk_buff **trailer);
पूर्णांक __skb_pad(काष्ठा sk_buff *skb, पूर्णांक pad, bool मुक्त_on_error);

/**
 *	skb_pad			-	zero pad the tail of an skb
 *	@skb: buffer to pad
 *	@pad: space to pad
 *
 *	Ensure that a buffer is followed by a padding area that is zero
 *	filled. Used by network drivers which may DMA or transfer data
 *	beyond the buffer end onto the wire.
 *
 *	May वापस error in out of memory हालs. The skb is मुक्तd on error.
 */
अटल अंतरभूत पूर्णांक skb_pad(काष्ठा sk_buff *skb, पूर्णांक pad)
अणु
	वापस __skb_pad(skb, pad, true);
पूर्ण
#घोषणा dev_kमुक्त_skb(a)	consume_skb(a)

पूर्णांक skb_append_pagefrags(काष्ठा sk_buff *skb, काष्ठा page *page,
			 पूर्णांक offset, माप_प्रकार size);

काष्ठा skb_seq_state अणु
	__u32		lower_offset;
	__u32		upper_offset;
	__u32		frag_idx;
	__u32		stepped_offset;
	काष्ठा sk_buff	*root_skb;
	काष्ठा sk_buff	*cur_skb;
	__u8		*frag_data;
	__u32		frag_off;
पूर्ण;

व्योम skb_prepare_seq_पढ़ो(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक from,
			  अचिन्हित पूर्णांक to, काष्ठा skb_seq_state *st);
अचिन्हित पूर्णांक skb_seq_पढ़ो(अचिन्हित पूर्णांक consumed, स्थिर u8 **data,
			  काष्ठा skb_seq_state *st);
व्योम skb_पात_seq_पढ़ो(काष्ठा skb_seq_state *st);

अचिन्हित पूर्णांक skb_find_text(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक from,
			   अचिन्हित पूर्णांक to, काष्ठा ts_config *config);

/*
 * Packet hash types specअगरy the type of hash in skb_set_hash.
 *
 * Hash types refer to the protocol layer addresses which are used to
 * स्थिरruct a packet's hash. The hashes are used to dअगरferentiate or identअगरy
 * flows of the protocol layer क्रम the hash type. Hash types are either
 * layer-2 (L2), layer-3 (L3), or layer-4 (L4).
 *
 * Properties of hashes:
 *
 * 1) Two packets in dअगरferent flows have dअगरferent hash values
 * 2) Two packets in the same flow should have the same hash value
 *
 * A hash at a higher layer is considered to be more specअगरic. A driver should
 * set the most specअगरic hash possible.
 *
 * A driver cannot indicate a more specअगरic hash than the layer at which a hash
 * was computed. For instance an L3 hash cannot be set as an L4 hash.
 *
 * A driver may indicate a hash level which is less specअगरic than the
 * actual layer the hash was computed on. For instance, a hash computed
 * at L4 may be considered an L3 hash. This should only be करोne अगर the
 * driver can't unambiguously determine that the HW computed the hash at
 * the higher layer. Note that the "should" in the second property above
 * permits this.
 */
क्रमागत pkt_hash_types अणु
	PKT_HASH_TYPE_NONE,	/* Undefined type */
	PKT_HASH_TYPE_L2,	/* Input: src_MAC, dest_MAC */
	PKT_HASH_TYPE_L3,	/* Input: src_IP, dst_IP */
	PKT_HASH_TYPE_L4,	/* Input: src_IP, dst_IP, src_port, dst_port */
पूर्ण;

अटल अंतरभूत व्योम skb_clear_hash(काष्ठा sk_buff *skb)
अणु
	skb->hash = 0;
	skb->sw_hash = 0;
	skb->l4_hash = 0;
पूर्ण

अटल अंतरभूत व्योम skb_clear_hash_अगर_not_l4(काष्ठा sk_buff *skb)
अणु
	अगर (!skb->l4_hash)
		skb_clear_hash(skb);
पूर्ण

अटल अंतरभूत व्योम
__skb_set_hash(काष्ठा sk_buff *skb, __u32 hash, bool is_sw, bool is_l4)
अणु
	skb->l4_hash = is_l4;
	skb->sw_hash = is_sw;
	skb->hash = hash;
पूर्ण

अटल अंतरभूत व्योम
skb_set_hash(काष्ठा sk_buff *skb, __u32 hash, क्रमागत pkt_hash_types type)
अणु
	/* Used by drivers to set hash from HW */
	__skb_set_hash(skb, hash, false, type == PKT_HASH_TYPE_L4);
पूर्ण

अटल अंतरभूत व्योम
__skb_set_sw_hash(काष्ठा sk_buff *skb, __u32 hash, bool is_l4)
अणु
	__skb_set_hash(skb, hash, true, is_l4);
पूर्ण

व्योम __skb_get_hash(काष्ठा sk_buff *skb);
u32 __skb_get_hash_symmetric(स्थिर काष्ठा sk_buff *skb);
u32 skb_get_poff(स्थिर काष्ठा sk_buff *skb);
u32 __skb_get_poff(स्थिर काष्ठा sk_buff *skb, स्थिर व्योम *data,
		   स्थिर काष्ठा flow_keys_basic *keys, पूर्णांक hlen);
__be32 __skb_flow_get_ports(स्थिर काष्ठा sk_buff *skb, पूर्णांक thoff, u8 ip_proto,
			    स्थिर व्योम *data, पूर्णांक hlen_proto);

अटल अंतरभूत __be32 skb_flow_get_ports(स्थिर काष्ठा sk_buff *skb,
					पूर्णांक thoff, u8 ip_proto)
अणु
	वापस __skb_flow_get_ports(skb, thoff, ip_proto, शून्य, 0);
पूर्ण

व्योम skb_flow_dissector_init(काष्ठा flow_dissector *flow_dissector,
			     स्थिर काष्ठा flow_dissector_key *key,
			     अचिन्हित पूर्णांक key_count);

काष्ठा bpf_flow_dissector;
bool bpf_flow_dissect(काष्ठा bpf_prog *prog, काष्ठा bpf_flow_dissector *ctx,
		      __be16 proto, पूर्णांक nhoff, पूर्णांक hlen, अचिन्हित पूर्णांक flags);

bool __skb_flow_dissect(स्थिर काष्ठा net *net,
			स्थिर काष्ठा sk_buff *skb,
			काष्ठा flow_dissector *flow_dissector,
			व्योम *target_container, स्थिर व्योम *data,
			__be16 proto, पूर्णांक nhoff, पूर्णांक hlen, अचिन्हित पूर्णांक flags);

अटल अंतरभूत bool skb_flow_dissect(स्थिर काष्ठा sk_buff *skb,
				    काष्ठा flow_dissector *flow_dissector,
				    व्योम *target_container, अचिन्हित पूर्णांक flags)
अणु
	वापस __skb_flow_dissect(शून्य, skb, flow_dissector,
				  target_container, शून्य, 0, 0, 0, flags);
पूर्ण

अटल अंतरभूत bool skb_flow_dissect_flow_keys(स्थिर काष्ठा sk_buff *skb,
					      काष्ठा flow_keys *flow,
					      अचिन्हित पूर्णांक flags)
अणु
	स_रखो(flow, 0, माप(*flow));
	वापस __skb_flow_dissect(शून्य, skb, &flow_keys_dissector,
				  flow, शून्य, 0, 0, 0, flags);
पूर्ण

अटल अंतरभूत bool
skb_flow_dissect_flow_keys_basic(स्थिर काष्ठा net *net,
				 स्थिर काष्ठा sk_buff *skb,
				 काष्ठा flow_keys_basic *flow,
				 स्थिर व्योम *data, __be16 proto,
				 पूर्णांक nhoff, पूर्णांक hlen, अचिन्हित पूर्णांक flags)
अणु
	स_रखो(flow, 0, माप(*flow));
	वापस __skb_flow_dissect(net, skb, &flow_keys_basic_dissector, flow,
				  data, proto, nhoff, hlen, flags);
पूर्ण

व्योम skb_flow_dissect_meta(स्थिर काष्ठा sk_buff *skb,
			   काष्ठा flow_dissector *flow_dissector,
			   व्योम *target_container);

/* Gets a skb connection tracking info, ctinfo map should be a
 * map of mapsize to translate क्रमागत ip_conntrack_info states
 * to user states.
 */
व्योम
skb_flow_dissect_ct(स्थिर काष्ठा sk_buff *skb,
		    काष्ठा flow_dissector *flow_dissector,
		    व्योम *target_container,
		    u16 *ctinfo_map, माप_प्रकार mapsize,
		    bool post_ct);
व्योम
skb_flow_dissect_tunnel_info(स्थिर काष्ठा sk_buff *skb,
			     काष्ठा flow_dissector *flow_dissector,
			     व्योम *target_container);

व्योम skb_flow_dissect_hash(स्थिर काष्ठा sk_buff *skb,
			   काष्ठा flow_dissector *flow_dissector,
			   व्योम *target_container);

अटल अंतरभूत __u32 skb_get_hash(काष्ठा sk_buff *skb)
अणु
	अगर (!skb->l4_hash && !skb->sw_hash)
		__skb_get_hash(skb);

	वापस skb->hash;
पूर्ण

अटल अंतरभूत __u32 skb_get_hash_flowi6(काष्ठा sk_buff *skb, स्थिर काष्ठा flowi6 *fl6)
अणु
	अगर (!skb->l4_hash && !skb->sw_hash) अणु
		काष्ठा flow_keys keys;
		__u32 hash = __get_hash_from_flowi6(fl6, &keys);

		__skb_set_sw_hash(skb, hash, flow_keys_have_l4(&keys));
	पूर्ण

	वापस skb->hash;
पूर्ण

__u32 skb_get_hash_perturb(स्थिर काष्ठा sk_buff *skb,
			   स्थिर siphash_key_t *perturb);

अटल अंतरभूत __u32 skb_get_hash_raw(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस skb->hash;
पूर्ण

अटल अंतरभूत व्योम skb_copy_hash(काष्ठा sk_buff *to, स्थिर काष्ठा sk_buff *from)
अणु
	to->hash = from->hash;
	to->sw_hash = from->sw_hash;
	to->l4_hash = from->l4_hash;
पूर्ण;

अटल अंतरभूत व्योम skb_copy_decrypted(काष्ठा sk_buff *to,
				      स्थिर काष्ठा sk_buff *from)
अणु
#अगर_घोषित CONFIG_TLS_DEVICE
	to->decrypted = from->decrypted;
#पूर्ण_अगर
पूर्ण

#अगर_घोषित NET_SKBUFF_DATA_USES_OFFSET
अटल अंतरभूत अचिन्हित अक्षर *skb_end_poपूर्णांकer(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस skb->head + skb->end;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक skb_end_offset(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस skb->end;
पूर्ण
#अन्यथा
अटल अंतरभूत अचिन्हित अक्षर *skb_end_poपूर्णांकer(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस skb->end;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक skb_end_offset(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस skb->end - skb->head;
पूर्ण
#पूर्ण_अगर

/* Internal */
#घोषणा skb_shinfo(SKB)	((काष्ठा skb_shared_info *)(skb_end_poपूर्णांकer(SKB)))

अटल अंतरभूत काष्ठा skb_shared_hwtstamps *skb_hwtstamps(काष्ठा sk_buff *skb)
अणु
	वापस &skb_shinfo(skb)->hwtstamps;
पूर्ण

अटल अंतरभूत काष्ठा ubuf_info *skb_zcopy(काष्ठा sk_buff *skb)
अणु
	bool is_zcopy = skb && skb_shinfo(skb)->flags & SKBFL_ZEROCOPY_ENABLE;

	वापस is_zcopy ? skb_uarg(skb) : शून्य;
पूर्ण

अटल अंतरभूत व्योम net_zcopy_get(काष्ठा ubuf_info *uarg)
अणु
	refcount_inc(&uarg->refcnt);
पूर्ण

अटल अंतरभूत व्योम skb_zcopy_init(काष्ठा sk_buff *skb, काष्ठा ubuf_info *uarg)
अणु
	skb_shinfo(skb)->deकाष्ठाor_arg = uarg;
	skb_shinfo(skb)->flags |= uarg->flags;
पूर्ण

अटल अंतरभूत व्योम skb_zcopy_set(काष्ठा sk_buff *skb, काष्ठा ubuf_info *uarg,
				 bool *have_ref)
अणु
	अगर (skb && uarg && !skb_zcopy(skb)) अणु
		अगर (unlikely(have_ref && *have_ref))
			*have_ref = false;
		अन्यथा
			net_zcopy_get(uarg);
		skb_zcopy_init(skb, uarg);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम skb_zcopy_set_nouarg(काष्ठा sk_buff *skb, व्योम *val)
अणु
	skb_shinfo(skb)->deकाष्ठाor_arg = (व्योम *)((uपूर्णांकptr_t) val | 0x1UL);
	skb_shinfo(skb)->flags |= SKBFL_ZEROCOPY_FRAG;
पूर्ण

अटल अंतरभूत bool skb_zcopy_is_nouarg(काष्ठा sk_buff *skb)
अणु
	वापस (uपूर्णांकptr_t) skb_shinfo(skb)->deकाष्ठाor_arg & 0x1UL;
पूर्ण

अटल अंतरभूत व्योम *skb_zcopy_get_nouarg(काष्ठा sk_buff *skb)
अणु
	वापस (व्योम *)((uपूर्णांकptr_t) skb_shinfo(skb)->deकाष्ठाor_arg & ~0x1UL);
पूर्ण

अटल अंतरभूत व्योम net_zcopy_put(काष्ठा ubuf_info *uarg)
अणु
	अगर (uarg)
		uarg->callback(शून्य, uarg, true);
पूर्ण

अटल अंतरभूत व्योम net_zcopy_put_पात(काष्ठा ubuf_info *uarg, bool have_uref)
अणु
	अगर (uarg) अणु
		अगर (uarg->callback == msg_zerocopy_callback)
			msg_zerocopy_put_पात(uarg, have_uref);
		अन्यथा अगर (have_uref)
			net_zcopy_put(uarg);
	पूर्ण
पूर्ण

/* Release a reference on a zerocopy काष्ठाure */
अटल अंतरभूत व्योम skb_zcopy_clear(काष्ठा sk_buff *skb, bool zerocopy_success)
अणु
	काष्ठा ubuf_info *uarg = skb_zcopy(skb);

	अगर (uarg) अणु
		अगर (!skb_zcopy_is_nouarg(skb))
			uarg->callback(skb, uarg, zerocopy_success);

		skb_shinfo(skb)->flags &= ~SKBFL_ZEROCOPY_FRAG;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम skb_mark_not_on_list(काष्ठा sk_buff *skb)
अणु
	skb->next = शून्य;
पूर्ण

/* Iterate through singly-linked GSO fragments of an skb. */
#घोषणा skb_list_walk_safe(first, skb, next_skb)                               \
	क्रम ((skb) = (first), (next_skb) = (skb) ? (skb)->next : शून्य; (skb);  \
	     (skb) = (next_skb), (next_skb) = (skb) ? (skb)->next : शून्य)

अटल अंतरभूत व्योम skb_list_del_init(काष्ठा sk_buff *skb)
अणु
	__list_del_entry(&skb->list);
	skb_mark_not_on_list(skb);
पूर्ण

/**
 *	skb_queue_empty - check अगर a queue is empty
 *	@list: queue head
 *
 *	Returns true अगर the queue is empty, false otherwise.
 */
अटल अंतरभूत पूर्णांक skb_queue_empty(स्थिर काष्ठा sk_buff_head *list)
अणु
	वापस list->next == (स्थिर काष्ठा sk_buff *) list;
पूर्ण

/**
 *	skb_queue_empty_lockless - check अगर a queue is empty
 *	@list: queue head
 *
 *	Returns true अगर the queue is empty, false otherwise.
 *	This variant can be used in lockless contexts.
 */
अटल अंतरभूत bool skb_queue_empty_lockless(स्थिर काष्ठा sk_buff_head *list)
अणु
	वापस READ_ONCE(list->next) == (स्थिर काष्ठा sk_buff *) list;
पूर्ण


/**
 *	skb_queue_is_last - check अगर skb is the last entry in the queue
 *	@list: queue head
 *	@skb: buffer
 *
 *	Returns true अगर @skb is the last buffer on the list.
 */
अटल अंतरभूत bool skb_queue_is_last(स्थिर काष्ठा sk_buff_head *list,
				     स्थिर काष्ठा sk_buff *skb)
अणु
	वापस skb->next == (स्थिर काष्ठा sk_buff *) list;
पूर्ण

/**
 *	skb_queue_is_first - check अगर skb is the first entry in the queue
 *	@list: queue head
 *	@skb: buffer
 *
 *	Returns true अगर @skb is the first buffer on the list.
 */
अटल अंतरभूत bool skb_queue_is_first(स्थिर काष्ठा sk_buff_head *list,
				      स्थिर काष्ठा sk_buff *skb)
अणु
	वापस skb->prev == (स्थिर काष्ठा sk_buff *) list;
पूर्ण

/**
 *	skb_queue_next - वापस the next packet in the queue
 *	@list: queue head
 *	@skb: current buffer
 *
 *	Return the next packet in @list after @skb.  It is only valid to
 *	call this अगर skb_queue_is_last() evaluates to false.
 */
अटल अंतरभूत काष्ठा sk_buff *skb_queue_next(स्थिर काष्ठा sk_buff_head *list,
					     स्थिर काष्ठा sk_buff *skb)
अणु
	/* This BUG_ON may seem severe, but अगर we just वापस then we
	 * are going to dereference garbage.
	 */
	BUG_ON(skb_queue_is_last(list, skb));
	वापस skb->next;
पूर्ण

/**
 *	skb_queue_prev - वापस the prev packet in the queue
 *	@list: queue head
 *	@skb: current buffer
 *
 *	Return the prev packet in @list beक्रमe @skb.  It is only valid to
 *	call this अगर skb_queue_is_first() evaluates to false.
 */
अटल अंतरभूत काष्ठा sk_buff *skb_queue_prev(स्थिर काष्ठा sk_buff_head *list,
					     स्थिर काष्ठा sk_buff *skb)
अणु
	/* This BUG_ON may seem severe, but अगर we just वापस then we
	 * are going to dereference garbage.
	 */
	BUG_ON(skb_queue_is_first(list, skb));
	वापस skb->prev;
पूर्ण

/**
 *	skb_get - reference buffer
 *	@skb: buffer to reference
 *
 *	Makes another reference to a socket buffer and वापसs a poपूर्णांकer
 *	to the buffer.
 */
अटल अंतरभूत काष्ठा sk_buff *skb_get(काष्ठा sk_buff *skb)
अणु
	refcount_inc(&skb->users);
	वापस skb;
पूर्ण

/*
 * If users == 1, we are the only owner and can aव्योम redundant atomic changes.
 */

/**
 *	skb_cloned - is the buffer a clone
 *	@skb: buffer to check
 *
 *	Returns true अगर the buffer was generated with skb_clone() and is
 *	one of multiple shared copies of the buffer. Cloned buffers are
 *	shared data so must not be written to under normal circumstances.
 */
अटल अंतरभूत पूर्णांक skb_cloned(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस skb->cloned &&
	       (atomic_पढ़ो(&skb_shinfo(skb)->dataref) & SKB_DATAREF_MASK) != 1;
पूर्ण

अटल अंतरभूत पूर्णांक skb_unclone(काष्ठा sk_buff *skb, gfp_t pri)
अणु
	might_sleep_अगर(gfpflags_allow_blocking(pri));

	अगर (skb_cloned(skb))
		वापस pskb_expand_head(skb, 0, 0, pri);

	वापस 0;
पूर्ण

/**
 *	skb_header_cloned - is the header a clone
 *	@skb: buffer to check
 *
 *	Returns true अगर modअगरying the header part of the buffer requires
 *	the data to be copied.
 */
अटल अंतरभूत पूर्णांक skb_header_cloned(स्थिर काष्ठा sk_buff *skb)
अणु
	पूर्णांक dataref;

	अगर (!skb->cloned)
		वापस 0;

	dataref = atomic_पढ़ो(&skb_shinfo(skb)->dataref);
	dataref = (dataref & SKB_DATAREF_MASK) - (dataref >> SKB_DATAREF_SHIFT);
	वापस dataref != 1;
पूर्ण

अटल अंतरभूत पूर्णांक skb_header_unclone(काष्ठा sk_buff *skb, gfp_t pri)
अणु
	might_sleep_अगर(gfpflags_allow_blocking(pri));

	अगर (skb_header_cloned(skb))
		वापस pskb_expand_head(skb, 0, 0, pri);

	वापस 0;
पूर्ण

/**
 *	__skb_header_release - release reference to header
 *	@skb: buffer to operate on
 */
अटल अंतरभूत व्योम __skb_header_release(काष्ठा sk_buff *skb)
अणु
	skb->nohdr = 1;
	atomic_set(&skb_shinfo(skb)->dataref, 1 + (1 << SKB_DATAREF_SHIFT));
पूर्ण


/**
 *	skb_shared - is the buffer shared
 *	@skb: buffer to check
 *
 *	Returns true अगर more than one person has a reference to this
 *	buffer.
 */
अटल अंतरभूत पूर्णांक skb_shared(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस refcount_पढ़ो(&skb->users) != 1;
पूर्ण

/**
 *	skb_share_check - check अगर buffer is shared and अगर so clone it
 *	@skb: buffer to check
 *	@pri: priority क्रम memory allocation
 *
 *	If the buffer is shared the buffer is cloned and the old copy
 *	drops a reference. A new clone with a single reference is वापसed.
 *	If the buffer is not shared the original buffer is वापसed. When
 *	being called from पूर्णांकerrupt status or with spinlocks held pri must
 *	be GFP_ATOMIC.
 *
 *	शून्य is वापसed on a memory allocation failure.
 */
अटल अंतरभूत काष्ठा sk_buff *skb_share_check(काष्ठा sk_buff *skb, gfp_t pri)
अणु
	might_sleep_अगर(gfpflags_allow_blocking(pri));
	अगर (skb_shared(skb)) अणु
		काष्ठा sk_buff *nskb = skb_clone(skb, pri);

		अगर (likely(nskb))
			consume_skb(skb);
		अन्यथा
			kमुक्त_skb(skb);
		skb = nskb;
	पूर्ण
	वापस skb;
पूर्ण

/*
 *	Copy shared buffers पूर्णांकo a new sk_buff. We effectively करो COW on
 *	packets to handle हालs where we have a local पढ़ोer and क्रमward
 *	and a couple of other messy ones. The normal one is tcpdumping
 *	a packet thats being क्रमwarded.
 */

/**
 *	skb_unshare - make a copy of a shared buffer
 *	@skb: buffer to check
 *	@pri: priority क्रम memory allocation
 *
 *	If the socket buffer is a clone then this function creates a new
 *	copy of the data, drops a reference count on the old copy and वापसs
 *	the new copy with the reference count at 1. If the buffer is not a clone
 *	the original buffer is वापसed. When called with a spinlock held or
 *	from पूर्णांकerrupt state @pri must be %GFP_ATOMIC
 *
 *	%शून्य is वापसed on a memory allocation failure.
 */
अटल अंतरभूत काष्ठा sk_buff *skb_unshare(काष्ठा sk_buff *skb,
					  gfp_t pri)
अणु
	might_sleep_अगर(gfpflags_allow_blocking(pri));
	अगर (skb_cloned(skb)) अणु
		काष्ठा sk_buff *nskb = skb_copy(skb, pri);

		/* Free our shared copy */
		अगर (likely(nskb))
			consume_skb(skb);
		अन्यथा
			kमुक्त_skb(skb);
		skb = nskb;
	पूर्ण
	वापस skb;
पूर्ण

/**
 *	skb_peek - peek at the head of an &sk_buff_head
 *	@list_: list to peek at
 *
 *	Peek an &sk_buff. Unlike most other operations you _MUST_
 *	be careful with this one. A peek leaves the buffer on the
 *	list and someone अन्यथा may run off with it. You must hold
 *	the appropriate locks or have a निजी queue to करो this.
 *
 *	Returns %शून्य क्रम an empty list or a poपूर्णांकer to the head element.
 *	The reference count is not incremented and the reference is thereक्रमe
 *	अस्थिर. Use with caution.
 */
अटल अंतरभूत काष्ठा sk_buff *skb_peek(स्थिर काष्ठा sk_buff_head *list_)
अणु
	काष्ठा sk_buff *skb = list_->next;

	अगर (skb == (काष्ठा sk_buff *)list_)
		skb = शून्य;
	वापस skb;
पूर्ण

/**
 *	__skb_peek - peek at the head of a non-empty &sk_buff_head
 *	@list_: list to peek at
 *
 *	Like skb_peek(), but the caller knows that the list is not empty.
 */
अटल अंतरभूत काष्ठा sk_buff *__skb_peek(स्थिर काष्ठा sk_buff_head *list_)
अणु
	वापस list_->next;
पूर्ण

/**
 *	skb_peek_next - peek skb following the given one from a queue
 *	@skb: skb to start from
 *	@list_: list to peek at
 *
 *	Returns %शून्य when the end of the list is met or a poपूर्णांकer to the
 *	next element. The reference count is not incremented and the
 *	reference is thereक्रमe अस्थिर. Use with caution.
 */
अटल अंतरभूत काष्ठा sk_buff *skb_peek_next(काष्ठा sk_buff *skb,
		स्थिर काष्ठा sk_buff_head *list_)
अणु
	काष्ठा sk_buff *next = skb->next;

	अगर (next == (काष्ठा sk_buff *)list_)
		next = शून्य;
	वापस next;
पूर्ण

/**
 *	skb_peek_tail - peek at the tail of an &sk_buff_head
 *	@list_: list to peek at
 *
 *	Peek an &sk_buff. Unlike most other operations you _MUST_
 *	be careful with this one. A peek leaves the buffer on the
 *	list and someone अन्यथा may run off with it. You must hold
 *	the appropriate locks or have a निजी queue to करो this.
 *
 *	Returns %शून्य क्रम an empty list or a poपूर्णांकer to the tail element.
 *	The reference count is not incremented and the reference is thereक्रमe
 *	अस्थिर. Use with caution.
 */
अटल अंतरभूत काष्ठा sk_buff *skb_peek_tail(स्थिर काष्ठा sk_buff_head *list_)
अणु
	काष्ठा sk_buff *skb = READ_ONCE(list_->prev);

	अगर (skb == (काष्ठा sk_buff *)list_)
		skb = शून्य;
	वापस skb;

पूर्ण

/**
 *	skb_queue_len	- get queue length
 *	@list_: list to measure
 *
 *	Return the length of an &sk_buff queue.
 */
अटल अंतरभूत __u32 skb_queue_len(स्थिर काष्ठा sk_buff_head *list_)
अणु
	वापस list_->qlen;
पूर्ण

/**
 *	skb_queue_len_lockless	- get queue length
 *	@list_: list to measure
 *
 *	Return the length of an &sk_buff queue.
 *	This variant can be used in lockless contexts.
 */
अटल अंतरभूत __u32 skb_queue_len_lockless(स्थिर काष्ठा sk_buff_head *list_)
अणु
	वापस READ_ONCE(list_->qlen);
पूर्ण

/**
 *	__skb_queue_head_init - initialize non-spinlock portions of sk_buff_head
 *	@list: queue to initialize
 *
 *	This initializes only the list and queue length aspects of
 *	an sk_buff_head object.  This allows to initialize the list
 *	aspects of an sk_buff_head without reinitializing things like
 *	the spinlock.  It can also be used क्रम on-stack sk_buff_head
 *	objects where the spinlock is known to not be used.
 */
अटल अंतरभूत व्योम __skb_queue_head_init(काष्ठा sk_buff_head *list)
अणु
	list->prev = list->next = (काष्ठा sk_buff *)list;
	list->qlen = 0;
पूर्ण

/*
 * This function creates a split out lock class क्रम each invocation;
 * this is needed क्रम now since a whole lot of users of the skb-queue
 * infraकाष्ठाure in drivers have dअगरferent locking usage (in hardirq)
 * than the networking core (in softirq only). In the दीर्घ run either the
 * network layer or drivers should need annotation to consolidate the
 * मुख्य types of usage पूर्णांकo 3 classes.
 */
अटल अंतरभूत व्योम skb_queue_head_init(काष्ठा sk_buff_head *list)
अणु
	spin_lock_init(&list->lock);
	__skb_queue_head_init(list);
पूर्ण

अटल अंतरभूत व्योम skb_queue_head_init_class(काष्ठा sk_buff_head *list,
		काष्ठा lock_class_key *class)
अणु
	skb_queue_head_init(list);
	lockdep_set_class(&list->lock, class);
पूर्ण

/*
 *	Insert an sk_buff on a list.
 *
 *	The "__skb_xxxx()" functions are the non-atomic ones that
 *	can only be called with पूर्णांकerrupts disabled.
 */
अटल अंतरभूत व्योम __skb_insert(काष्ठा sk_buff *newsk,
				काष्ठा sk_buff *prev, काष्ठा sk_buff *next,
				काष्ठा sk_buff_head *list)
अणु
	/* See skb_queue_empty_lockless() and skb_peek_tail()
	 * क्रम the opposite READ_ONCE()
	 */
	WRITE_ONCE(newsk->next, next);
	WRITE_ONCE(newsk->prev, prev);
	WRITE_ONCE(next->prev, newsk);
	WRITE_ONCE(prev->next, newsk);
	list->qlen++;
पूर्ण

अटल अंतरभूत व्योम __skb_queue_splice(स्थिर काष्ठा sk_buff_head *list,
				      काष्ठा sk_buff *prev,
				      काष्ठा sk_buff *next)
अणु
	काष्ठा sk_buff *first = list->next;
	काष्ठा sk_buff *last = list->prev;

	WRITE_ONCE(first->prev, prev);
	WRITE_ONCE(prev->next, first);

	WRITE_ONCE(last->next, next);
	WRITE_ONCE(next->prev, last);
पूर्ण

/**
 *	skb_queue_splice - join two skb lists, this is deचिन्हित क्रम stacks
 *	@list: the new list to add
 *	@head: the place to add it in the first list
 */
अटल अंतरभूत व्योम skb_queue_splice(स्थिर काष्ठा sk_buff_head *list,
				    काष्ठा sk_buff_head *head)
अणु
	अगर (!skb_queue_empty(list)) अणु
		__skb_queue_splice(list, (काष्ठा sk_buff *) head, head->next);
		head->qlen += list->qlen;
	पूर्ण
पूर्ण

/**
 *	skb_queue_splice_init - join two skb lists and reinitialise the emptied list
 *	@list: the new list to add
 *	@head: the place to add it in the first list
 *
 *	The list at @list is reinitialised
 */
अटल अंतरभूत व्योम skb_queue_splice_init(काष्ठा sk_buff_head *list,
					 काष्ठा sk_buff_head *head)
अणु
	अगर (!skb_queue_empty(list)) अणु
		__skb_queue_splice(list, (काष्ठा sk_buff *) head, head->next);
		head->qlen += list->qlen;
		__skb_queue_head_init(list);
	पूर्ण
पूर्ण

/**
 *	skb_queue_splice_tail - join two skb lists, each list being a queue
 *	@list: the new list to add
 *	@head: the place to add it in the first list
 */
अटल अंतरभूत व्योम skb_queue_splice_tail(स्थिर काष्ठा sk_buff_head *list,
					 काष्ठा sk_buff_head *head)
अणु
	अगर (!skb_queue_empty(list)) अणु
		__skb_queue_splice(list, head->prev, (काष्ठा sk_buff *) head);
		head->qlen += list->qlen;
	पूर्ण
पूर्ण

/**
 *	skb_queue_splice_tail_init - join two skb lists and reinitialise the emptied list
 *	@list: the new list to add
 *	@head: the place to add it in the first list
 *
 *	Each of the lists is a queue.
 *	The list at @list is reinitialised
 */
अटल अंतरभूत व्योम skb_queue_splice_tail_init(काष्ठा sk_buff_head *list,
					      काष्ठा sk_buff_head *head)
अणु
	अगर (!skb_queue_empty(list)) अणु
		__skb_queue_splice(list, head->prev, (काष्ठा sk_buff *) head);
		head->qlen += list->qlen;
		__skb_queue_head_init(list);
	पूर्ण
पूर्ण

/**
 *	__skb_queue_after - queue a buffer at the list head
 *	@list: list to use
 *	@prev: place after this buffer
 *	@newsk: buffer to queue
 *
 *	Queue a buffer पूर्णांक the middle of a list. This function takes no locks
 *	and you must thereक्रमe hold required locks beक्रमe calling it.
 *
 *	A buffer cannot be placed on two lists at the same समय.
 */
अटल अंतरभूत व्योम __skb_queue_after(काष्ठा sk_buff_head *list,
				     काष्ठा sk_buff *prev,
				     काष्ठा sk_buff *newsk)
अणु
	__skb_insert(newsk, prev, prev->next, list);
पूर्ण

व्योम skb_append(काष्ठा sk_buff *old, काष्ठा sk_buff *newsk,
		काष्ठा sk_buff_head *list);

अटल अंतरभूत व्योम __skb_queue_beक्रमe(काष्ठा sk_buff_head *list,
				      काष्ठा sk_buff *next,
				      काष्ठा sk_buff *newsk)
अणु
	__skb_insert(newsk, next->prev, next, list);
पूर्ण

/**
 *	__skb_queue_head - queue a buffer at the list head
 *	@list: list to use
 *	@newsk: buffer to queue
 *
 *	Queue a buffer at the start of a list. This function takes no locks
 *	and you must thereक्रमe hold required locks beक्रमe calling it.
 *
 *	A buffer cannot be placed on two lists at the same समय.
 */
अटल अंतरभूत व्योम __skb_queue_head(काष्ठा sk_buff_head *list,
				    काष्ठा sk_buff *newsk)
अणु
	__skb_queue_after(list, (काष्ठा sk_buff *)list, newsk);
पूर्ण
व्योम skb_queue_head(काष्ठा sk_buff_head *list, काष्ठा sk_buff *newsk);

/**
 *	__skb_queue_tail - queue a buffer at the list tail
 *	@list: list to use
 *	@newsk: buffer to queue
 *
 *	Queue a buffer at the end of a list. This function takes no locks
 *	and you must thereक्रमe hold required locks beक्रमe calling it.
 *
 *	A buffer cannot be placed on two lists at the same समय.
 */
अटल अंतरभूत व्योम __skb_queue_tail(काष्ठा sk_buff_head *list,
				   काष्ठा sk_buff *newsk)
अणु
	__skb_queue_beक्रमe(list, (काष्ठा sk_buff *)list, newsk);
पूर्ण
व्योम skb_queue_tail(काष्ठा sk_buff_head *list, काष्ठा sk_buff *newsk);

/*
 * हटाओ sk_buff from list. _Must_ be called atomically, and with
 * the list known..
 */
व्योम skb_unlink(काष्ठा sk_buff *skb, काष्ठा sk_buff_head *list);
अटल अंतरभूत व्योम __skb_unlink(काष्ठा sk_buff *skb, काष्ठा sk_buff_head *list)
अणु
	काष्ठा sk_buff *next, *prev;

	WRITE_ONCE(list->qlen, list->qlen - 1);
	next	   = skb->next;
	prev	   = skb->prev;
	skb->next  = skb->prev = शून्य;
	WRITE_ONCE(next->prev, prev);
	WRITE_ONCE(prev->next, next);
पूर्ण

/**
 *	__skb_dequeue - हटाओ from the head of the queue
 *	@list: list to dequeue from
 *
 *	Remove the head of the list. This function करोes not take any locks
 *	so must be used with appropriate locks held only. The head item is
 *	वापसed or %शून्य अगर the list is empty.
 */
अटल अंतरभूत काष्ठा sk_buff *__skb_dequeue(काष्ठा sk_buff_head *list)
अणु
	काष्ठा sk_buff *skb = skb_peek(list);
	अगर (skb)
		__skb_unlink(skb, list);
	वापस skb;
पूर्ण
काष्ठा sk_buff *skb_dequeue(काष्ठा sk_buff_head *list);

/**
 *	__skb_dequeue_tail - हटाओ from the tail of the queue
 *	@list: list to dequeue from
 *
 *	Remove the tail of the list. This function करोes not take any locks
 *	so must be used with appropriate locks held only. The tail item is
 *	वापसed or %शून्य अगर the list is empty.
 */
अटल अंतरभूत काष्ठा sk_buff *__skb_dequeue_tail(काष्ठा sk_buff_head *list)
अणु
	काष्ठा sk_buff *skb = skb_peek_tail(list);
	अगर (skb)
		__skb_unlink(skb, list);
	वापस skb;
पूर्ण
काष्ठा sk_buff *skb_dequeue_tail(काष्ठा sk_buff_head *list);


अटल अंतरभूत bool skb_is_nonlinear(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस skb->data_len;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक skb_headlen(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस skb->len - skb->data_len;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक __skb_pagelen(स्थिर काष्ठा sk_buff *skb)
अणु
	अचिन्हित पूर्णांक i, len = 0;

	क्रम (i = skb_shinfo(skb)->nr_frags - 1; (पूर्णांक)i >= 0; i--)
		len += skb_frag_size(&skb_shinfo(skb)->frags[i]);
	वापस len;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक skb_pagelen(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस skb_headlen(skb) + __skb_pagelen(skb);
पूर्ण

/**
 * __skb_fill_page_desc - initialise a paged fragment in an skb
 * @skb: buffer containing fragment to be initialised
 * @i: paged fragment index to initialise
 * @page: the page to use क्रम this fragment
 * @off: the offset to the data with @page
 * @size: the length of the data
 *
 * Initialises the @i'th fragment of @skb to poपूर्णांक to &size bytes at
 * offset @off within @page.
 *
 * Does not take any additional reference on the fragment.
 */
अटल अंतरभूत व्योम __skb_fill_page_desc(काष्ठा sk_buff *skb, पूर्णांक i,
					काष्ठा page *page, पूर्णांक off, पूर्णांक size)
अणु
	skb_frag_t *frag = &skb_shinfo(skb)->frags[i];

	/*
	 * Propagate page pfmeदो_स्मृति to the skb अगर we can. The problem is
	 * that not all callers have unique ownership of the page but rely
	 * on page_is_pfmeदो_स्मृति करोing the right thing(पंचांग).
	 */
	frag->bv_page		  = page;
	frag->bv_offset		  = off;
	skb_frag_size_set(frag, size);

	page = compound_head(page);
	अगर (page_is_pfmeदो_स्मृति(page))
		skb->pfmeदो_स्मृति	= true;
पूर्ण

/**
 * skb_fill_page_desc - initialise a paged fragment in an skb
 * @skb: buffer containing fragment to be initialised
 * @i: paged fragment index to initialise
 * @page: the page to use क्रम this fragment
 * @off: the offset to the data with @page
 * @size: the length of the data
 *
 * As per __skb_fill_page_desc() -- initialises the @i'th fragment of
 * @skb to poपूर्णांक to @size bytes at offset @off within @page. In
 * addition updates @skb such that @i is the last fragment.
 *
 * Does not take any additional reference on the fragment.
 */
अटल अंतरभूत व्योम skb_fill_page_desc(काष्ठा sk_buff *skb, पूर्णांक i,
				      काष्ठा page *page, पूर्णांक off, पूर्णांक size)
अणु
	__skb_fill_page_desc(skb, i, page, off, size);
	skb_shinfo(skb)->nr_frags = i + 1;
पूर्ण

व्योम skb_add_rx_frag(काष्ठा sk_buff *skb, पूर्णांक i, काष्ठा page *page, पूर्णांक off,
		     पूर्णांक size, अचिन्हित पूर्णांक truesize);

व्योम skb_coalesce_rx_frag(काष्ठा sk_buff *skb, पूर्णांक i, पूर्णांक size,
			  अचिन्हित पूर्णांक truesize);

#घोषणा SKB_LINEAR_ASSERT(skb)  BUG_ON(skb_is_nonlinear(skb))

#अगर_घोषित NET_SKBUFF_DATA_USES_OFFSET
अटल अंतरभूत अचिन्हित अक्षर *skb_tail_poपूर्णांकer(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस skb->head + skb->tail;
पूर्ण

अटल अंतरभूत व्योम skb_reset_tail_poपूर्णांकer(काष्ठा sk_buff *skb)
अणु
	skb->tail = skb->data - skb->head;
पूर्ण

अटल अंतरभूत व्योम skb_set_tail_poपूर्णांकer(काष्ठा sk_buff *skb, स्थिर पूर्णांक offset)
अणु
	skb_reset_tail_poपूर्णांकer(skb);
	skb->tail += offset;
पूर्ण

#अन्यथा /* NET_SKBUFF_DATA_USES_OFFSET */
अटल अंतरभूत अचिन्हित अक्षर *skb_tail_poपूर्णांकer(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस skb->tail;
पूर्ण

अटल अंतरभूत व्योम skb_reset_tail_poपूर्णांकer(काष्ठा sk_buff *skb)
अणु
	skb->tail = skb->data;
पूर्ण

अटल अंतरभूत व्योम skb_set_tail_poपूर्णांकer(काष्ठा sk_buff *skb, स्थिर पूर्णांक offset)
अणु
	skb->tail = skb->data + offset;
पूर्ण

#पूर्ण_अगर /* NET_SKBUFF_DATA_USES_OFFSET */

/*
 *	Add data to an sk_buff
 */
व्योम *pskb_put(काष्ठा sk_buff *skb, काष्ठा sk_buff *tail, पूर्णांक len);
व्योम *skb_put(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक len);
अटल अंतरभूत व्योम *__skb_put(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक len)
अणु
	व्योम *पंचांगp = skb_tail_poपूर्णांकer(skb);
	SKB_LINEAR_ASSERT(skb);
	skb->tail += len;
	skb->len  += len;
	वापस पंचांगp;
पूर्ण

अटल अंतरभूत व्योम *__skb_put_zero(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक len)
अणु
	व्योम *पंचांगp = __skb_put(skb, len);

	स_रखो(पंचांगp, 0, len);
	वापस पंचांगp;
पूर्ण

अटल अंतरभूत व्योम *__skb_put_data(काष्ठा sk_buff *skb, स्थिर व्योम *data,
				   अचिन्हित पूर्णांक len)
अणु
	व्योम *पंचांगp = __skb_put(skb, len);

	स_नकल(पंचांगp, data, len);
	वापस पंचांगp;
पूर्ण

अटल अंतरभूत व्योम __skb_put_u8(काष्ठा sk_buff *skb, u8 val)
अणु
	*(u8 *)__skb_put(skb, 1) = val;
पूर्ण

अटल अंतरभूत व्योम *skb_put_zero(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक len)
अणु
	व्योम *पंचांगp = skb_put(skb, len);

	स_रखो(पंचांगp, 0, len);

	वापस पंचांगp;
पूर्ण

अटल अंतरभूत व्योम *skb_put_data(काष्ठा sk_buff *skb, स्थिर व्योम *data,
				 अचिन्हित पूर्णांक len)
अणु
	व्योम *पंचांगp = skb_put(skb, len);

	स_नकल(पंचांगp, data, len);

	वापस पंचांगp;
पूर्ण

अटल अंतरभूत व्योम skb_put_u8(काष्ठा sk_buff *skb, u8 val)
अणु
	*(u8 *)skb_put(skb, 1) = val;
पूर्ण

व्योम *skb_push(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक len);
अटल अंतरभूत व्योम *__skb_push(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक len)
अणु
	skb->data -= len;
	skb->len  += len;
	वापस skb->data;
पूर्ण

व्योम *skb_pull(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक len);
अटल अंतरभूत व्योम *__skb_pull(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक len)
अणु
	skb->len -= len;
	BUG_ON(skb->len < skb->data_len);
	वापस skb->data += len;
पूर्ण

अटल अंतरभूत व्योम *skb_pull_अंतरभूत(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक len)
अणु
	वापस unlikely(len > skb->len) ? शून्य : __skb_pull(skb, len);
पूर्ण

व्योम *__pskb_pull_tail(काष्ठा sk_buff *skb, पूर्णांक delta);

अटल अंतरभूत व्योम *__pskb_pull(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक len)
अणु
	अगर (len > skb_headlen(skb) &&
	    !__pskb_pull_tail(skb, len - skb_headlen(skb)))
		वापस शून्य;
	skb->len -= len;
	वापस skb->data += len;
पूर्ण

अटल अंतरभूत व्योम *pskb_pull(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक len)
अणु
	वापस unlikely(len > skb->len) ? शून्य : __pskb_pull(skb, len);
पूर्ण

अटल अंतरभूत bool pskb_may_pull(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक len)
अणु
	अगर (likely(len <= skb_headlen(skb)))
		वापस true;
	अगर (unlikely(len > skb->len))
		वापस false;
	वापस __pskb_pull_tail(skb, len - skb_headlen(skb)) != शून्य;
पूर्ण

व्योम skb_condense(काष्ठा sk_buff *skb);

/**
 *	skb_headroom - bytes at buffer head
 *	@skb: buffer to check
 *
 *	Return the number of bytes of मुक्त space at the head of an &sk_buff.
 */
अटल अंतरभूत अचिन्हित पूर्णांक skb_headroom(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस skb->data - skb->head;
पूर्ण

/**
 *	skb_tailroom - bytes at buffer end
 *	@skb: buffer to check
 *
 *	Return the number of bytes of मुक्त space at the tail of an sk_buff
 */
अटल अंतरभूत पूर्णांक skb_tailroom(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस skb_is_nonlinear(skb) ? 0 : skb->end - skb->tail;
पूर्ण

/**
 *	skb_availroom - bytes at buffer end
 *	@skb: buffer to check
 *
 *	Return the number of bytes of मुक्त space at the tail of an sk_buff
 *	allocated by sk_stream_alloc()
 */
अटल अंतरभूत पूर्णांक skb_availroom(स्थिर काष्ठा sk_buff *skb)
अणु
	अगर (skb_is_nonlinear(skb))
		वापस 0;

	वापस skb->end - skb->tail - skb->reserved_tailroom;
पूर्ण

/**
 *	skb_reserve - adjust headroom
 *	@skb: buffer to alter
 *	@len: bytes to move
 *
 *	Increase the headroom of an empty &sk_buff by reducing the tail
 *	room. This is only allowed क्रम an empty buffer.
 */
अटल अंतरभूत व्योम skb_reserve(काष्ठा sk_buff *skb, पूर्णांक len)
अणु
	skb->data += len;
	skb->tail += len;
पूर्ण

/**
 *	skb_tailroom_reserve - adjust reserved_tailroom
 *	@skb: buffer to alter
 *	@mtu: maximum amount of headlen permitted
 *	@needed_tailroom: minimum amount of reserved_tailroom
 *
 *	Set reserved_tailroom so that headlen can be as large as possible but
 *	not larger than mtu and tailroom cannot be smaller than
 *	needed_tailroom.
 *	The required headroom should alपढ़ोy have been reserved beक्रमe using
 *	this function.
 */
अटल अंतरभूत व्योम skb_tailroom_reserve(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक mtu,
					अचिन्हित पूर्णांक needed_tailroom)
अणु
	SKB_LINEAR_ASSERT(skb);
	अगर (mtu < skb_tailroom(skb) - needed_tailroom)
		/* use at most mtu */
		skb->reserved_tailroom = skb_tailroom(skb) - mtu;
	अन्यथा
		/* use up to all available space */
		skb->reserved_tailroom = needed_tailroom;
पूर्ण

#घोषणा ENCAP_TYPE_ETHER	0
#घोषणा ENCAP_TYPE_IPPROTO	1

अटल अंतरभूत व्योम skb_set_inner_protocol(काष्ठा sk_buff *skb,
					  __be16 protocol)
अणु
	skb->inner_protocol = protocol;
	skb->inner_protocol_type = ENCAP_TYPE_ETHER;
पूर्ण

अटल अंतरभूत व्योम skb_set_inner_ipproto(काष्ठा sk_buff *skb,
					 __u8 ipproto)
अणु
	skb->inner_ipproto = ipproto;
	skb->inner_protocol_type = ENCAP_TYPE_IPPROTO;
पूर्ण

अटल अंतरभूत व्योम skb_reset_inner_headers(काष्ठा sk_buff *skb)
अणु
	skb->inner_mac_header = skb->mac_header;
	skb->inner_network_header = skb->network_header;
	skb->inner_transport_header = skb->transport_header;
पूर्ण

अटल अंतरभूत व्योम skb_reset_mac_len(काष्ठा sk_buff *skb)
अणु
	skb->mac_len = skb->network_header - skb->mac_header;
पूर्ण

अटल अंतरभूत अचिन्हित अक्षर *skb_inner_transport_header(स्थिर काष्ठा sk_buff
							*skb)
अणु
	वापस skb->head + skb->inner_transport_header;
पूर्ण

अटल अंतरभूत पूर्णांक skb_inner_transport_offset(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस skb_inner_transport_header(skb) - skb->data;
पूर्ण

अटल अंतरभूत व्योम skb_reset_inner_transport_header(काष्ठा sk_buff *skb)
अणु
	skb->inner_transport_header = skb->data - skb->head;
पूर्ण

अटल अंतरभूत व्योम skb_set_inner_transport_header(काष्ठा sk_buff *skb,
						   स्थिर पूर्णांक offset)
अणु
	skb_reset_inner_transport_header(skb);
	skb->inner_transport_header += offset;
पूर्ण

अटल अंतरभूत अचिन्हित अक्षर *skb_inner_network_header(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस skb->head + skb->inner_network_header;
पूर्ण

अटल अंतरभूत व्योम skb_reset_inner_network_header(काष्ठा sk_buff *skb)
अणु
	skb->inner_network_header = skb->data - skb->head;
पूर्ण

अटल अंतरभूत व्योम skb_set_inner_network_header(काष्ठा sk_buff *skb,
						स्थिर पूर्णांक offset)
अणु
	skb_reset_inner_network_header(skb);
	skb->inner_network_header += offset;
पूर्ण

अटल अंतरभूत अचिन्हित अक्षर *skb_inner_mac_header(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस skb->head + skb->inner_mac_header;
पूर्ण

अटल अंतरभूत व्योम skb_reset_inner_mac_header(काष्ठा sk_buff *skb)
अणु
	skb->inner_mac_header = skb->data - skb->head;
पूर्ण

अटल अंतरभूत व्योम skb_set_inner_mac_header(काष्ठा sk_buff *skb,
					    स्थिर पूर्णांक offset)
अणु
	skb_reset_inner_mac_header(skb);
	skb->inner_mac_header += offset;
पूर्ण
अटल अंतरभूत bool skb_transport_header_was_set(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस skb->transport_header != (typeof(skb->transport_header))~0U;
पूर्ण

अटल अंतरभूत अचिन्हित अक्षर *skb_transport_header(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस skb->head + skb->transport_header;
पूर्ण

अटल अंतरभूत व्योम skb_reset_transport_header(काष्ठा sk_buff *skb)
अणु
	skb->transport_header = skb->data - skb->head;
पूर्ण

अटल अंतरभूत व्योम skb_set_transport_header(काष्ठा sk_buff *skb,
					    स्थिर पूर्णांक offset)
अणु
	skb_reset_transport_header(skb);
	skb->transport_header += offset;
पूर्ण

अटल अंतरभूत अचिन्हित अक्षर *skb_network_header(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस skb->head + skb->network_header;
पूर्ण

अटल अंतरभूत व्योम skb_reset_network_header(काष्ठा sk_buff *skb)
अणु
	skb->network_header = skb->data - skb->head;
पूर्ण

अटल अंतरभूत व्योम skb_set_network_header(काष्ठा sk_buff *skb, स्थिर पूर्णांक offset)
अणु
	skb_reset_network_header(skb);
	skb->network_header += offset;
पूर्ण

अटल अंतरभूत अचिन्हित अक्षर *skb_mac_header(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस skb->head + skb->mac_header;
पूर्ण

अटल अंतरभूत पूर्णांक skb_mac_offset(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस skb_mac_header(skb) - skb->data;
पूर्ण

अटल अंतरभूत u32 skb_mac_header_len(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस skb->network_header - skb->mac_header;
पूर्ण

अटल अंतरभूत पूर्णांक skb_mac_header_was_set(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस skb->mac_header != (typeof(skb->mac_header))~0U;
पूर्ण

अटल अंतरभूत व्योम skb_unset_mac_header(काष्ठा sk_buff *skb)
अणु
	skb->mac_header = (typeof(skb->mac_header))~0U;
पूर्ण

अटल अंतरभूत व्योम skb_reset_mac_header(काष्ठा sk_buff *skb)
अणु
	skb->mac_header = skb->data - skb->head;
पूर्ण

अटल अंतरभूत व्योम skb_set_mac_header(काष्ठा sk_buff *skb, स्थिर पूर्णांक offset)
अणु
	skb_reset_mac_header(skb);
	skb->mac_header += offset;
पूर्ण

अटल अंतरभूत व्योम skb_pop_mac_header(काष्ठा sk_buff *skb)
अणु
	skb->mac_header = skb->network_header;
पूर्ण

अटल अंतरभूत व्योम skb_probe_transport_header(काष्ठा sk_buff *skb)
अणु
	काष्ठा flow_keys_basic keys;

	अगर (skb_transport_header_was_set(skb))
		वापस;

	अगर (skb_flow_dissect_flow_keys_basic(शून्य, skb, &keys,
					     शून्य, 0, 0, 0, 0))
		skb_set_transport_header(skb, keys.control.thoff);
पूर्ण

अटल अंतरभूत व्योम skb_mac_header_rebuild(काष्ठा sk_buff *skb)
अणु
	अगर (skb_mac_header_was_set(skb)) अणु
		स्थिर अचिन्हित अक्षर *old_mac = skb_mac_header(skb);

		skb_set_mac_header(skb, -skb->mac_len);
		स_हटाओ(skb_mac_header(skb), old_mac, skb->mac_len);
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक skb_checksum_start_offset(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस skb->csum_start - skb_headroom(skb);
पूर्ण

अटल अंतरभूत अचिन्हित अक्षर *skb_checksum_start(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस skb->head + skb->csum_start;
पूर्ण

अटल अंतरभूत पूर्णांक skb_transport_offset(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस skb_transport_header(skb) - skb->data;
पूर्ण

अटल अंतरभूत u32 skb_network_header_len(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस skb->transport_header - skb->network_header;
पूर्ण

अटल अंतरभूत u32 skb_inner_network_header_len(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस skb->inner_transport_header - skb->inner_network_header;
पूर्ण

अटल अंतरभूत पूर्णांक skb_network_offset(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस skb_network_header(skb) - skb->data;
पूर्ण

अटल अंतरभूत पूर्णांक skb_inner_network_offset(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस skb_inner_network_header(skb) - skb->data;
पूर्ण

अटल अंतरभूत पूर्णांक pskb_network_may_pull(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक len)
अणु
	वापस pskb_may_pull(skb, skb_network_offset(skb) + len);
पूर्ण

/*
 * CPUs often take a perक्रमmance hit when accessing unaligned memory
 * locations. The actual perक्रमmance hit varies, it can be small अगर the
 * hardware handles it or large अगर we have to take an exception and fix it
 * in software.
 *
 * Since an ethernet header is 14 bytes network drivers often end up with
 * the IP header at an unaligned offset. The IP header can be aligned by
 * shअगरting the start of the packet by 2 bytes. Drivers should करो this
 * with:
 *
 * skb_reserve(skb, NET_IP_ALIGN);
 *
 * The करोwnside to this alignment of the IP header is that the DMA is now
 * unaligned. On some architectures the cost of an unaligned DMA is high
 * and this cost outweighs the gains made by aligning the IP header.
 *
 * Since this trade off varies between architectures, we allow NET_IP_ALIGN
 * to be overridden.
 */
#अगर_अघोषित NET_IP_ALIGN
#घोषणा NET_IP_ALIGN	2
#पूर्ण_अगर

/*
 * The networking layer reserves some headroom in skb data (via
 * dev_alloc_skb). This is used to aव्योम having to पुनः_स्मृतिate skb data when
 * the header has to grow. In the शेष हाल, अगर the header has to grow
 * 32 bytes or less we aव्योम the पुनः_स्मृतिation.
 *
 * Unक्रमtunately this headroom changes the DMA alignment of the resulting
 * network packet. As क्रम NET_IP_ALIGN, this unaligned DMA is expensive
 * on some architectures. An architecture can override this value,
 * perhaps setting it to a cacheline in size (since that will मुख्यtain
 * cacheline alignment of the DMA). It must be a घातer of 2.
 *
 * Various parts of the networking layer expect at least 32 bytes of
 * headroom, you should not reduce this.
 *
 * Using max(32, L1_CACHE_BYTES) makes sense (especially with RPS)
 * to reduce average number of cache lines per packet.
 * get_rps_cpu() क्रम example only access one 64 bytes aligned block :
 * NET_IP_ALIGN(2) + ethernet_header(14) + IP_header(20/40) + ports(8)
 */
#अगर_अघोषित NET_SKB_PAD
#घोषणा NET_SKB_PAD	max(32, L1_CACHE_BYTES)
#पूर्ण_अगर

पूर्णांक ___pskb_trim(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक len);

अटल अंतरभूत व्योम __skb_set_length(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक len)
अणु
	अगर (WARN_ON(skb_is_nonlinear(skb)))
		वापस;
	skb->len = len;
	skb_set_tail_poपूर्णांकer(skb, len);
पूर्ण

अटल अंतरभूत व्योम __skb_trim(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक len)
अणु
	__skb_set_length(skb, len);
पूर्ण

व्योम skb_trim(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक len);

अटल अंतरभूत पूर्णांक __pskb_trim(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक len)
अणु
	अगर (skb->data_len)
		वापस ___pskb_trim(skb, len);
	__skb_trim(skb, len);
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक pskb_trim(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक len)
अणु
	वापस (len < skb->len) ? __pskb_trim(skb, len) : 0;
पूर्ण

/**
 *	pskb_trim_unique - हटाओ end from a paged unique (not cloned) buffer
 *	@skb: buffer to alter
 *	@len: new length
 *
 *	This is identical to pskb_trim except that the caller knows that
 *	the skb is not cloned so we should never get an error due to out-
 *	of-memory.
 */
अटल अंतरभूत व्योम pskb_trim_unique(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक len)
अणु
	पूर्णांक err = pskb_trim(skb, len);
	BUG_ON(err);
पूर्ण

अटल अंतरभूत पूर्णांक __skb_grow(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक len)
अणु
	अचिन्हित पूर्णांक dअगरf = len - skb->len;

	अगर (skb_tailroom(skb) < dअगरf) अणु
		पूर्णांक ret = pskb_expand_head(skb, 0, dअगरf - skb_tailroom(skb),
					   GFP_ATOMIC);
		अगर (ret)
			वापस ret;
	पूर्ण
	__skb_set_length(skb, len);
	वापस 0;
पूर्ण

/**
 *	skb_orphan - orphan a buffer
 *	@skb: buffer to orphan
 *
 *	If a buffer currently has an owner then we call the owner's
 *	deकाष्ठाor function and make the @skb unowned. The buffer जारीs
 *	to exist but is no दीर्घer अक्षरged to its क्रमmer owner.
 */
अटल अंतरभूत व्योम skb_orphan(काष्ठा sk_buff *skb)
अणु
	अगर (skb->deकाष्ठाor) अणु
		skb->deकाष्ठाor(skb);
		skb->deकाष्ठाor = शून्य;
		skb->sk		= शून्य;
	पूर्ण अन्यथा अणु
		BUG_ON(skb->sk);
	पूर्ण
पूर्ण

/**
 *	skb_orphan_frags - orphan the frags contained in a buffer
 *	@skb: buffer to orphan frags from
 *	@gfp_mask: allocation mask क्रम replacement pages
 *
 *	For each frag in the SKB which needs a deकाष्ठाor (i.e. has an
 *	owner) create a copy of that frag and release the original
 *	page by calling the deकाष्ठाor.
 */
अटल अंतरभूत पूर्णांक skb_orphan_frags(काष्ठा sk_buff *skb, gfp_t gfp_mask)
अणु
	अगर (likely(!skb_zcopy(skb)))
		वापस 0;
	अगर (!skb_zcopy_is_nouarg(skb) &&
	    skb_uarg(skb)->callback == msg_zerocopy_callback)
		वापस 0;
	वापस skb_copy_ubufs(skb, gfp_mask);
पूर्ण

/* Frags must be orphaned, even अगर refcounted, अगर skb might loop to rx path */
अटल अंतरभूत पूर्णांक skb_orphan_frags_rx(काष्ठा sk_buff *skb, gfp_t gfp_mask)
अणु
	अगर (likely(!skb_zcopy(skb)))
		वापस 0;
	वापस skb_copy_ubufs(skb, gfp_mask);
पूर्ण

/**
 *	__skb_queue_purge - empty a list
 *	@list: list to empty
 *
 *	Delete all buffers on an &sk_buff list. Each buffer is हटाओd from
 *	the list and one reference dropped. This function करोes not take the
 *	list lock and the caller must hold the relevant locks to use it.
 */
अटल अंतरभूत व्योम __skb_queue_purge(काष्ठा sk_buff_head *list)
अणु
	काष्ठा sk_buff *skb;
	जबतक ((skb = __skb_dequeue(list)) != शून्य)
		kमुक्त_skb(skb);
पूर्ण
व्योम skb_queue_purge(काष्ठा sk_buff_head *list);

अचिन्हित पूर्णांक skb_rbtree_purge(काष्ठा rb_root *root);

व्योम *__netdev_alloc_frag_align(अचिन्हित पूर्णांक fragsz, अचिन्हित पूर्णांक align_mask);

/**
 * netdev_alloc_frag - allocate a page fragment
 * @fragsz: fragment size
 *
 * Allocates a frag from a page क्रम receive buffer.
 * Uses GFP_ATOMIC allocations.
 */
अटल अंतरभूत व्योम *netdev_alloc_frag(अचिन्हित पूर्णांक fragsz)
अणु
	वापस __netdev_alloc_frag_align(fragsz, ~0u);
पूर्ण

अटल अंतरभूत व्योम *netdev_alloc_frag_align(अचिन्हित पूर्णांक fragsz,
					    अचिन्हित पूर्णांक align)
अणु
	WARN_ON_ONCE(!is_घातer_of_2(align));
	वापस __netdev_alloc_frag_align(fragsz, -align);
पूर्ण

काष्ठा sk_buff *__netdev_alloc_skb(काष्ठा net_device *dev, अचिन्हित पूर्णांक length,
				   gfp_t gfp_mask);

/**
 *	netdev_alloc_skb - allocate an skbuff क्रम rx on a specअगरic device
 *	@dev: network device to receive on
 *	@length: length to allocate
 *
 *	Allocate a new &sk_buff and assign it a usage count of one. The
 *	buffer has unspecअगरied headroom built in. Users should allocate
 *	the headroom they think they need without accounting क्रम the
 *	built in space. The built in space is used क्रम optimisations.
 *
 *	%शून्य is वापसed अगर there is no मुक्त memory. Although this function
 *	allocates memory it can be called from an पूर्णांकerrupt.
 */
अटल अंतरभूत काष्ठा sk_buff *netdev_alloc_skb(काष्ठा net_device *dev,
					       अचिन्हित पूर्णांक length)
अणु
	वापस __netdev_alloc_skb(dev, length, GFP_ATOMIC);
पूर्ण

/* legacy helper around __netdev_alloc_skb() */
अटल अंतरभूत काष्ठा sk_buff *__dev_alloc_skb(अचिन्हित पूर्णांक length,
					      gfp_t gfp_mask)
अणु
	वापस __netdev_alloc_skb(शून्य, length, gfp_mask);
पूर्ण

/* legacy helper around netdev_alloc_skb() */
अटल अंतरभूत काष्ठा sk_buff *dev_alloc_skb(अचिन्हित पूर्णांक length)
अणु
	वापस netdev_alloc_skb(शून्य, length);
पूर्ण


अटल अंतरभूत काष्ठा sk_buff *__netdev_alloc_skb_ip_align(काष्ठा net_device *dev,
		अचिन्हित पूर्णांक length, gfp_t gfp)
अणु
	काष्ठा sk_buff *skb = __netdev_alloc_skb(dev, length + NET_IP_ALIGN, gfp);

	अगर (NET_IP_ALIGN && skb)
		skb_reserve(skb, NET_IP_ALIGN);
	वापस skb;
पूर्ण

अटल अंतरभूत काष्ठा sk_buff *netdev_alloc_skb_ip_align(काष्ठा net_device *dev,
		अचिन्हित पूर्णांक length)
अणु
	वापस __netdev_alloc_skb_ip_align(dev, length, GFP_ATOMIC);
पूर्ण

अटल अंतरभूत व्योम skb_मुक्त_frag(व्योम *addr)
अणु
	page_frag_मुक्त(addr);
पूर्ण

व्योम *__napi_alloc_frag_align(अचिन्हित पूर्णांक fragsz, अचिन्हित पूर्णांक align_mask);

अटल अंतरभूत व्योम *napi_alloc_frag(अचिन्हित पूर्णांक fragsz)
अणु
	वापस __napi_alloc_frag_align(fragsz, ~0u);
पूर्ण

अटल अंतरभूत व्योम *napi_alloc_frag_align(अचिन्हित पूर्णांक fragsz,
					  अचिन्हित पूर्णांक align)
अणु
	WARN_ON_ONCE(!is_घातer_of_2(align));
	वापस __napi_alloc_frag_align(fragsz, -align);
पूर्ण

काष्ठा sk_buff *__napi_alloc_skb(काष्ठा napi_काष्ठा *napi,
				 अचिन्हित पूर्णांक length, gfp_t gfp_mask);
अटल अंतरभूत काष्ठा sk_buff *napi_alloc_skb(काष्ठा napi_काष्ठा *napi,
					     अचिन्हित पूर्णांक length)
अणु
	वापस __napi_alloc_skb(napi, length, GFP_ATOMIC);
पूर्ण
व्योम napi_consume_skb(काष्ठा sk_buff *skb, पूर्णांक budget);

व्योम napi_skb_मुक्त_stolen_head(काष्ठा sk_buff *skb);
व्योम __kमुक्त_skb_defer(काष्ठा sk_buff *skb);

/**
 * __dev_alloc_pages - allocate page क्रम network Rx
 * @gfp_mask: allocation priority. Set __GFP_NOMEMALLOC अगर not क्रम network Rx
 * @order: size of the allocation
 *
 * Allocate a new page.
 *
 * %शून्य is वापसed अगर there is no मुक्त memory.
*/
अटल अंतरभूत काष्ठा page *__dev_alloc_pages(gfp_t gfp_mask,
					     अचिन्हित पूर्णांक order)
अणु
	/* This piece of code contains several assumptions.
	 * 1.  This is क्रम device Rx, thereक्रम a cold page is preferred.
	 * 2.  The expectation is the user wants a compound page.
	 * 3.  If requesting a order 0 page it will not be compound
	 *     due to the check to see अगर order has a value in prep_new_page
	 * 4.  __GFP_MEMALLOC is ignored अगर __GFP_NOMEMALLOC is set due to
	 *     code in gfp_to_alloc_flags that should be enक्रमcing this.
	 */
	gfp_mask |= __GFP_COMP | __GFP_MEMALLOC;

	वापस alloc_pages_node(NUMA_NO_NODE, gfp_mask, order);
पूर्ण

अटल अंतरभूत काष्ठा page *dev_alloc_pages(अचिन्हित पूर्णांक order)
अणु
	वापस __dev_alloc_pages(GFP_ATOMIC | __GFP_NOWARN, order);
पूर्ण

/**
 * __dev_alloc_page - allocate a page क्रम network Rx
 * @gfp_mask: allocation priority. Set __GFP_NOMEMALLOC अगर not क्रम network Rx
 *
 * Allocate a new page.
 *
 * %शून्य is वापसed अगर there is no मुक्त memory.
 */
अटल अंतरभूत काष्ठा page *__dev_alloc_page(gfp_t gfp_mask)
अणु
	वापस __dev_alloc_pages(gfp_mask, 0);
पूर्ण

अटल अंतरभूत काष्ठा page *dev_alloc_page(व्योम)
अणु
	वापस dev_alloc_pages(0);
पूर्ण

/**
 * dev_page_is_reusable - check whether a page can be reused क्रम network Rx
 * @page: the page to test
 *
 * A page shouldn't be considered क्रम reusing/recycling अगर it was allocated
 * under memory pressure or at a distant memory node.
 *
 * Returns false अगर this page should be वापसed to page allocator, true
 * otherwise.
 */
अटल अंतरभूत bool dev_page_is_reusable(स्थिर काष्ठा page *page)
अणु
	वापस likely(page_to_nid(page) == numa_mem_id() &&
		      !page_is_pfmeदो_स्मृति(page));
पूर्ण

/**
 *	skb_propagate_pfmeदो_स्मृति - Propagate pfmeदो_स्मृति अगर skb is allocated after RX page
 *	@page: The page that was allocated from skb_alloc_page
 *	@skb: The skb that may need pfmeदो_स्मृति set
 */
अटल अंतरभूत व्योम skb_propagate_pfmeदो_स्मृति(स्थिर काष्ठा page *page,
					    काष्ठा sk_buff *skb)
अणु
	अगर (page_is_pfmeदो_स्मृति(page))
		skb->pfmeदो_स्मृति = true;
पूर्ण

/**
 * skb_frag_off() - Returns the offset of a skb fragment
 * @frag: the paged fragment
 */
अटल अंतरभूत अचिन्हित पूर्णांक skb_frag_off(स्थिर skb_frag_t *frag)
अणु
	वापस frag->bv_offset;
पूर्ण

/**
 * skb_frag_off_add() - Increments the offset of a skb fragment by @delta
 * @frag: skb fragment
 * @delta: value to add
 */
अटल अंतरभूत व्योम skb_frag_off_add(skb_frag_t *frag, पूर्णांक delta)
अणु
	frag->bv_offset += delta;
पूर्ण

/**
 * skb_frag_off_set() - Sets the offset of a skb fragment
 * @frag: skb fragment
 * @offset: offset of fragment
 */
अटल अंतरभूत व्योम skb_frag_off_set(skb_frag_t *frag, अचिन्हित पूर्णांक offset)
अणु
	frag->bv_offset = offset;
पूर्ण

/**
 * skb_frag_off_copy() - Sets the offset of a skb fragment from another fragment
 * @fragto: skb fragment where offset is set
 * @fragfrom: skb fragment offset is copied from
 */
अटल अंतरभूत व्योम skb_frag_off_copy(skb_frag_t *fragto,
				     स्थिर skb_frag_t *fragfrom)
अणु
	fragto->bv_offset = fragfrom->bv_offset;
पूर्ण

/**
 * skb_frag_page - retrieve the page referred to by a paged fragment
 * @frag: the paged fragment
 *
 * Returns the &काष्ठा page associated with @frag.
 */
अटल अंतरभूत काष्ठा page *skb_frag_page(स्थिर skb_frag_t *frag)
अणु
	वापस frag->bv_page;
पूर्ण

/**
 * __skb_frag_ref - take an addition reference on a paged fragment.
 * @frag: the paged fragment
 *
 * Takes an additional reference on the paged fragment @frag.
 */
अटल अंतरभूत व्योम __skb_frag_ref(skb_frag_t *frag)
अणु
	get_page(skb_frag_page(frag));
पूर्ण

/**
 * skb_frag_ref - take an addition reference on a paged fragment of an skb.
 * @skb: the buffer
 * @f: the fragment offset.
 *
 * Takes an additional reference on the @f'th paged fragment of @skb.
 */
अटल अंतरभूत व्योम skb_frag_ref(काष्ठा sk_buff *skb, पूर्णांक f)
अणु
	__skb_frag_ref(&skb_shinfo(skb)->frags[f]);
पूर्ण

/**
 * __skb_frag_unref - release a reference on a paged fragment.
 * @frag: the paged fragment
 *
 * Releases a reference on the paged fragment @frag.
 */
अटल अंतरभूत व्योम __skb_frag_unref(skb_frag_t *frag)
अणु
	put_page(skb_frag_page(frag));
पूर्ण

/**
 * skb_frag_unref - release a reference on a paged fragment of an skb.
 * @skb: the buffer
 * @f: the fragment offset
 *
 * Releases a reference on the @f'th paged fragment of @skb.
 */
अटल अंतरभूत व्योम skb_frag_unref(काष्ठा sk_buff *skb, पूर्णांक f)
अणु
	__skb_frag_unref(&skb_shinfo(skb)->frags[f]);
पूर्ण

/**
 * skb_frag_address - माला_लो the address of the data contained in a paged fragment
 * @frag: the paged fragment buffer
 *
 * Returns the address of the data within @frag. The page must alपढ़ोy
 * be mapped.
 */
अटल अंतरभूत व्योम *skb_frag_address(स्थिर skb_frag_t *frag)
अणु
	वापस page_address(skb_frag_page(frag)) + skb_frag_off(frag);
पूर्ण

/**
 * skb_frag_address_safe - माला_लो the address of the data contained in a paged fragment
 * @frag: the paged fragment buffer
 *
 * Returns the address of the data within @frag. Checks that the page
 * is mapped and वापसs %शून्य otherwise.
 */
अटल अंतरभूत व्योम *skb_frag_address_safe(स्थिर skb_frag_t *frag)
अणु
	व्योम *ptr = page_address(skb_frag_page(frag));
	अगर (unlikely(!ptr))
		वापस शून्य;

	वापस ptr + skb_frag_off(frag);
पूर्ण

/**
 * skb_frag_page_copy() - sets the page in a fragment from another fragment
 * @fragto: skb fragment where page is set
 * @fragfrom: skb fragment page is copied from
 */
अटल अंतरभूत व्योम skb_frag_page_copy(skb_frag_t *fragto,
				      स्थिर skb_frag_t *fragfrom)
अणु
	fragto->bv_page = fragfrom->bv_page;
पूर्ण

/**
 * __skb_frag_set_page - sets the page contained in a paged fragment
 * @frag: the paged fragment
 * @page: the page to set
 *
 * Sets the fragment @frag to contain @page.
 */
अटल अंतरभूत व्योम __skb_frag_set_page(skb_frag_t *frag, काष्ठा page *page)
अणु
	frag->bv_page = page;
पूर्ण

/**
 * skb_frag_set_page - sets the page contained in a paged fragment of an skb
 * @skb: the buffer
 * @f: the fragment offset
 * @page: the page to set
 *
 * Sets the @f'th fragment of @skb to contain @page.
 */
अटल अंतरभूत व्योम skb_frag_set_page(काष्ठा sk_buff *skb, पूर्णांक f,
				     काष्ठा page *page)
अणु
	__skb_frag_set_page(&skb_shinfo(skb)->frags[f], page);
पूर्ण

bool skb_page_frag_refill(अचिन्हित पूर्णांक sz, काष्ठा page_frag *pfrag, gfp_t prio);

/**
 * skb_frag_dma_map - maps a paged fragment via the DMA API
 * @dev: the device to map the fragment to
 * @frag: the paged fragment to map
 * @offset: the offset within the fragment (starting at the
 *          fragment's own offset)
 * @size: the number of bytes to map
 * @dir: the direction of the mapping (``PCI_DMA_*``)
 *
 * Maps the page associated with @frag to @device.
 */
अटल अंतरभूत dma_addr_t skb_frag_dma_map(काष्ठा device *dev,
					  स्थिर skb_frag_t *frag,
					  माप_प्रकार offset, माप_प्रकार size,
					  क्रमागत dma_data_direction dir)
अणु
	वापस dma_map_page(dev, skb_frag_page(frag),
			    skb_frag_off(frag) + offset, size, dir);
पूर्ण

अटल अंतरभूत काष्ठा sk_buff *pskb_copy(काष्ठा sk_buff *skb,
					gfp_t gfp_mask)
अणु
	वापस __pskb_copy(skb, skb_headroom(skb), gfp_mask);
पूर्ण


अटल अंतरभूत काष्ठा sk_buff *pskb_copy_क्रम_clone(काष्ठा sk_buff *skb,
						  gfp_t gfp_mask)
अणु
	वापस __pskb_copy_fclone(skb, skb_headroom(skb), gfp_mask, true);
पूर्ण


/**
 *	skb_clone_writable - is the header of a clone writable
 *	@skb: buffer to check
 *	@len: length up to which to ग_लिखो
 *
 *	Returns true अगर modअगरying the header part of the cloned buffer
 *	करोes not requires the data to be copied.
 */
अटल अंतरभूत पूर्णांक skb_clone_writable(स्थिर काष्ठा sk_buff *skb, अचिन्हित पूर्णांक len)
अणु
	वापस !skb_header_cloned(skb) &&
	       skb_headroom(skb) + len <= skb->hdr_len;
पूर्ण

अटल अंतरभूत पूर्णांक skb_try_make_writable(काष्ठा sk_buff *skb,
					अचिन्हित पूर्णांक ग_लिखो_len)
अणु
	वापस skb_cloned(skb) && !skb_clone_writable(skb, ग_लिखो_len) &&
	       pskb_expand_head(skb, 0, 0, GFP_ATOMIC);
पूर्ण

अटल अंतरभूत पूर्णांक __skb_cow(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक headroom,
			    पूर्णांक cloned)
अणु
	पूर्णांक delta = 0;

	अगर (headroom > skb_headroom(skb))
		delta = headroom - skb_headroom(skb);

	अगर (delta || cloned)
		वापस pskb_expand_head(skb, ALIGN(delta, NET_SKB_PAD), 0,
					GFP_ATOMIC);
	वापस 0;
पूर्ण

/**
 *	skb_cow - copy header of skb when it is required
 *	@skb: buffer to cow
 *	@headroom: needed headroom
 *
 *	If the skb passed lacks sufficient headroom or its data part
 *	is shared, data is पुनः_स्मृतिated. If पुनः_स्मृतिation fails, an error
 *	is वापसed and original skb is not changed.
 *
 *	The result is skb with writable area skb->head...skb->tail
 *	and at least @headroom of space at head.
 */
अटल अंतरभूत पूर्णांक skb_cow(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक headroom)
अणु
	वापस __skb_cow(skb, headroom, skb_cloned(skb));
पूर्ण

/**
 *	skb_cow_head - skb_cow but only making the head writable
 *	@skb: buffer to cow
 *	@headroom: needed headroom
 *
 *	This function is identical to skb_cow except that we replace the
 *	skb_cloned check by skb_header_cloned.  It should be used when
 *	you only need to push on some header and करो not need to modअगरy
 *	the data.
 */
अटल अंतरभूत पूर्णांक skb_cow_head(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक headroom)
अणु
	वापस __skb_cow(skb, headroom, skb_header_cloned(skb));
पूर्ण

/**
 *	skb_padto	- pad an skbuff up to a minimal size
 *	@skb: buffer to pad
 *	@len: minimal length
 *
 *	Pads up a buffer to ensure the trailing bytes exist and are
 *	blanked. If the buffer alपढ़ोy contains sufficient data it
 *	is untouched. Otherwise it is extended. Returns zero on
 *	success. The skb is मुक्तd on error.
 */
अटल अंतरभूत पूर्णांक skb_padto(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक len)
अणु
	अचिन्हित पूर्णांक size = skb->len;
	अगर (likely(size >= len))
		वापस 0;
	वापस skb_pad(skb, len - size);
पूर्ण

/**
 *	__skb_put_padto - increase size and pad an skbuff up to a minimal size
 *	@skb: buffer to pad
 *	@len: minimal length
 *	@मुक्त_on_error: मुक्त buffer on error
 *
 *	Pads up a buffer to ensure the trailing bytes exist and are
 *	blanked. If the buffer alपढ़ोy contains sufficient data it
 *	is untouched. Otherwise it is extended. Returns zero on
 *	success. The skb is मुक्तd on error अगर @मुक्त_on_error is true.
 */
अटल अंतरभूत पूर्णांक __must_check __skb_put_padto(काष्ठा sk_buff *skb,
					       अचिन्हित पूर्णांक len,
					       bool मुक्त_on_error)
अणु
	अचिन्हित पूर्णांक size = skb->len;

	अगर (unlikely(size < len)) अणु
		len -= size;
		अगर (__skb_pad(skb, len, मुक्त_on_error))
			वापस -ENOMEM;
		__skb_put(skb, len);
	पूर्ण
	वापस 0;
पूर्ण

/**
 *	skb_put_padto - increase size and pad an skbuff up to a minimal size
 *	@skb: buffer to pad
 *	@len: minimal length
 *
 *	Pads up a buffer to ensure the trailing bytes exist and are
 *	blanked. If the buffer alपढ़ोy contains sufficient data it
 *	is untouched. Otherwise it is extended. Returns zero on
 *	success. The skb is मुक्तd on error.
 */
अटल अंतरभूत पूर्णांक __must_check skb_put_padto(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक len)
अणु
	वापस __skb_put_padto(skb, len, true);
पूर्ण

अटल अंतरभूत पूर्णांक skb_add_data(काष्ठा sk_buff *skb,
			       काष्ठा iov_iter *from, पूर्णांक copy)
अणु
	स्थिर पूर्णांक off = skb->len;

	अगर (skb->ip_summed == CHECKSUM_NONE) अणु
		__wsum csum = 0;
		अगर (csum_and_copy_from_iter_full(skb_put(skb, copy), copy,
					         &csum, from)) अणु
			skb->csum = csum_block_add(skb->csum, csum, off);
			वापस 0;
		पूर्ण
	पूर्ण अन्यथा अगर (copy_from_iter_full(skb_put(skb, copy), copy, from))
		वापस 0;

	__skb_trim(skb, off);
	वापस -EFAULT;
पूर्ण

अटल अंतरभूत bool skb_can_coalesce(काष्ठा sk_buff *skb, पूर्णांक i,
				    स्थिर काष्ठा page *page, पूर्णांक off)
अणु
	अगर (skb_zcopy(skb))
		वापस false;
	अगर (i) अणु
		स्थिर skb_frag_t *frag = &skb_shinfo(skb)->frags[i - 1];

		वापस page == skb_frag_page(frag) &&
		       off == skb_frag_off(frag) + skb_frag_size(frag);
	पूर्ण
	वापस false;
पूर्ण

अटल अंतरभूत पूर्णांक __skb_linearize(काष्ठा sk_buff *skb)
अणु
	वापस __pskb_pull_tail(skb, skb->data_len) ? 0 : -ENOMEM;
पूर्ण

/**
 *	skb_linearize - convert paged skb to linear one
 *	@skb: buffer to linarize
 *
 *	If there is no मुक्त memory -ENOMEM is वापसed, otherwise zero
 *	is वापसed and the old skb data released.
 */
अटल अंतरभूत पूर्णांक skb_linearize(काष्ठा sk_buff *skb)
अणु
	वापस skb_is_nonlinear(skb) ? __skb_linearize(skb) : 0;
पूर्ण

/**
 * skb_has_shared_frag - can any frag be overwritten
 * @skb: buffer to test
 *
 * Return true अगर the skb has at least one frag that might be modअगरied
 * by an बाह्यal entity (as in vmsplice()/sendfile())
 */
अटल अंतरभूत bool skb_has_shared_frag(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस skb_is_nonlinear(skb) &&
	       skb_shinfo(skb)->flags & SKBFL_SHARED_FRAG;
पूर्ण

/**
 *	skb_linearize_cow - make sure skb is linear and writable
 *	@skb: buffer to process
 *
 *	If there is no मुक्त memory -ENOMEM is वापसed, otherwise zero
 *	is वापसed and the old skb data released.
 */
अटल अंतरभूत पूर्णांक skb_linearize_cow(काष्ठा sk_buff *skb)
अणु
	वापस skb_is_nonlinear(skb) || skb_cloned(skb) ?
	       __skb_linearize(skb) : 0;
पूर्ण

अटल __always_अंतरभूत व्योम
__skb_postpull_rcsum(काष्ठा sk_buff *skb, स्थिर व्योम *start, अचिन्हित पूर्णांक len,
		     अचिन्हित पूर्णांक off)
अणु
	अगर (skb->ip_summed == CHECKSUM_COMPLETE)
		skb->csum = csum_block_sub(skb->csum,
					   csum_partial(start, len, 0), off);
	अन्यथा अगर (skb->ip_summed == CHECKSUM_PARTIAL &&
		 skb_checksum_start_offset(skb) < 0)
		skb->ip_summed = CHECKSUM_NONE;
पूर्ण

/**
 *	skb_postpull_rcsum - update checksum क्रम received skb after pull
 *	@skb: buffer to update
 *	@start: start of data beक्रमe pull
 *	@len: length of data pulled
 *
 *	After करोing a pull on a received packet, you need to call this to
 *	update the CHECKSUM_COMPLETE checksum, or set ip_summed to
 *	CHECKSUM_NONE so that it can be recomputed from scratch.
 */
अटल अंतरभूत व्योम skb_postpull_rcsum(काष्ठा sk_buff *skb,
				      स्थिर व्योम *start, अचिन्हित पूर्णांक len)
अणु
	__skb_postpull_rcsum(skb, start, len, 0);
पूर्ण

अटल __always_अंतरभूत व्योम
__skb_postpush_rcsum(काष्ठा sk_buff *skb, स्थिर व्योम *start, अचिन्हित पूर्णांक len,
		     अचिन्हित पूर्णांक off)
अणु
	अगर (skb->ip_summed == CHECKSUM_COMPLETE)
		skb->csum = csum_block_add(skb->csum,
					   csum_partial(start, len, 0), off);
पूर्ण

/**
 *	skb_postpush_rcsum - update checksum क्रम received skb after push
 *	@skb: buffer to update
 *	@start: start of data after push
 *	@len: length of data pushed
 *
 *	After करोing a push on a received packet, you need to call this to
 *	update the CHECKSUM_COMPLETE checksum.
 */
अटल अंतरभूत व्योम skb_postpush_rcsum(काष्ठा sk_buff *skb,
				      स्थिर व्योम *start, अचिन्हित पूर्णांक len)
अणु
	__skb_postpush_rcsum(skb, start, len, 0);
पूर्ण

व्योम *skb_pull_rcsum(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक len);

/**
 *	skb_push_rcsum - push skb and update receive checksum
 *	@skb: buffer to update
 *	@len: length of data pulled
 *
 *	This function perक्रमms an skb_push on the packet and updates
 *	the CHECKSUM_COMPLETE checksum.  It should be used on
 *	receive path processing instead of skb_push unless you know
 *	that the checksum dअगरference is zero (e.g., a valid IP header)
 *	or you are setting ip_summed to CHECKSUM_NONE.
 */
अटल अंतरभूत व्योम *skb_push_rcsum(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक len)
अणु
	skb_push(skb, len);
	skb_postpush_rcsum(skb, skb->data, len);
	वापस skb->data;
पूर्ण

पूर्णांक pskb_trim_rcsum_slow(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक len);
/**
 *	pskb_trim_rcsum - trim received skb and update checksum
 *	@skb: buffer to trim
 *	@len: new length
 *
 *	This is exactly the same as pskb_trim except that it ensures the
 *	checksum of received packets are still valid after the operation.
 *	It can change skb poपूर्णांकers.
 */

अटल अंतरभूत पूर्णांक pskb_trim_rcsum(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक len)
अणु
	अगर (likely(len >= skb->len))
		वापस 0;
	वापस pskb_trim_rcsum_slow(skb, len);
पूर्ण

अटल अंतरभूत पूर्णांक __skb_trim_rcsum(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक len)
अणु
	अगर (skb->ip_summed == CHECKSUM_COMPLETE)
		skb->ip_summed = CHECKSUM_NONE;
	__skb_trim(skb, len);
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक __skb_grow_rcsum(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक len)
अणु
	अगर (skb->ip_summed == CHECKSUM_COMPLETE)
		skb->ip_summed = CHECKSUM_NONE;
	वापस __skb_grow(skb, len);
पूर्ण

#घोषणा rb_to_skb(rb) rb_entry_safe(rb, काष्ठा sk_buff, rbnode)
#घोषणा skb_rb_first(root) rb_to_skb(rb_first(root))
#घोषणा skb_rb_last(root)  rb_to_skb(rb_last(root))
#घोषणा skb_rb_next(skb)   rb_to_skb(rb_next(&(skb)->rbnode))
#घोषणा skb_rb_prev(skb)   rb_to_skb(rb_prev(&(skb)->rbnode))

#घोषणा skb_queue_walk(queue, skb) \
		क्रम (skb = (queue)->next;					\
		     skb != (काष्ठा sk_buff *)(queue);				\
		     skb = skb->next)

#घोषणा skb_queue_walk_safe(queue, skb, पंचांगp)					\
		क्रम (skb = (queue)->next, पंचांगp = skb->next;			\
		     skb != (काष्ठा sk_buff *)(queue);				\
		     skb = पंचांगp, पंचांगp = skb->next)

#घोषणा skb_queue_walk_from(queue, skb)						\
		क्रम (; skb != (काष्ठा sk_buff *)(queue);			\
		     skb = skb->next)

#घोषणा skb_rbtree_walk(skb, root)						\
		क्रम (skb = skb_rb_first(root); skb != शून्य;			\
		     skb = skb_rb_next(skb))

#घोषणा skb_rbtree_walk_from(skb)						\
		क्रम (; skb != शून्य;						\
		     skb = skb_rb_next(skb))

#घोषणा skb_rbtree_walk_from_safe(skb, पंचांगp)					\
		क्रम (; पंचांगp = skb ? skb_rb_next(skb) : शून्य, (skb != शून्य);	\
		     skb = पंचांगp)

#घोषणा skb_queue_walk_from_safe(queue, skb, पंचांगp)				\
		क्रम (पंचांगp = skb->next;						\
		     skb != (काष्ठा sk_buff *)(queue);				\
		     skb = पंचांगp, पंचांगp = skb->next)

#घोषणा skb_queue_reverse_walk(queue, skb) \
		क्रम (skb = (queue)->prev;					\
		     skb != (काष्ठा sk_buff *)(queue);				\
		     skb = skb->prev)

#घोषणा skb_queue_reverse_walk_safe(queue, skb, पंचांगp)				\
		क्रम (skb = (queue)->prev, पंचांगp = skb->prev;			\
		     skb != (काष्ठा sk_buff *)(queue);				\
		     skb = पंचांगp, पंचांगp = skb->prev)

#घोषणा skb_queue_reverse_walk_from_safe(queue, skb, पंचांगp)			\
		क्रम (पंचांगp = skb->prev;						\
		     skb != (काष्ठा sk_buff *)(queue);				\
		     skb = पंचांगp, पंचांगp = skb->prev)

अटल अंतरभूत bool skb_has_frag_list(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस skb_shinfo(skb)->frag_list != शून्य;
पूर्ण

अटल अंतरभूत व्योम skb_frag_list_init(काष्ठा sk_buff *skb)
अणु
	skb_shinfo(skb)->frag_list = शून्य;
पूर्ण

#घोषणा skb_walk_frags(skb, iter)	\
	क्रम (iter = skb_shinfo(skb)->frag_list; iter; iter = iter->next)


पूर्णांक __skb_रुको_क्रम_more_packets(काष्ठा sock *sk, काष्ठा sk_buff_head *queue,
				पूर्णांक *err, दीर्घ *समयo_p,
				स्थिर काष्ठा sk_buff *skb);
काष्ठा sk_buff *__skb_try_recv_from_queue(काष्ठा sock *sk,
					  काष्ठा sk_buff_head *queue,
					  अचिन्हित पूर्णांक flags,
					  पूर्णांक *off, पूर्णांक *err,
					  काष्ठा sk_buff **last);
काष्ठा sk_buff *__skb_try_recv_datagram(काष्ठा sock *sk,
					काष्ठा sk_buff_head *queue,
					अचिन्हित पूर्णांक flags, पूर्णांक *off, पूर्णांक *err,
					काष्ठा sk_buff **last);
काष्ठा sk_buff *__skb_recv_datagram(काष्ठा sock *sk,
				    काष्ठा sk_buff_head *sk_queue,
				    अचिन्हित पूर्णांक flags, पूर्णांक *off, पूर्णांक *err);
काष्ठा sk_buff *skb_recv_datagram(काष्ठा sock *sk, अचिन्हित flags, पूर्णांक noblock,
				  पूर्णांक *err);
__poll_t datagram_poll(काष्ठा file *file, काष्ठा socket *sock,
			   काष्ठा poll_table_काष्ठा *रुको);
पूर्णांक skb_copy_datagram_iter(स्थिर काष्ठा sk_buff *from, पूर्णांक offset,
			   काष्ठा iov_iter *to, पूर्णांक size);
अटल अंतरभूत पूर्णांक skb_copy_datagram_msg(स्थिर काष्ठा sk_buff *from, पूर्णांक offset,
					काष्ठा msghdr *msg, पूर्णांक size)
अणु
	वापस skb_copy_datagram_iter(from, offset, &msg->msg_iter, size);
पूर्ण
पूर्णांक skb_copy_and_csum_datagram_msg(काष्ठा sk_buff *skb, पूर्णांक hlen,
				   काष्ठा msghdr *msg);
पूर्णांक skb_copy_and_hash_datagram_iter(स्थिर काष्ठा sk_buff *skb, पूर्णांक offset,
			   काष्ठा iov_iter *to, पूर्णांक len,
			   काष्ठा ahash_request *hash);
पूर्णांक skb_copy_datagram_from_iter(काष्ठा sk_buff *skb, पूर्णांक offset,
				 काष्ठा iov_iter *from, पूर्णांक len);
पूर्णांक zerocopy_sg_from_iter(काष्ठा sk_buff *skb, काष्ठा iov_iter *frm);
व्योम skb_मुक्त_datagram(काष्ठा sock *sk, काष्ठा sk_buff *skb);
व्योम __skb_मुक्त_datagram_locked(काष्ठा sock *sk, काष्ठा sk_buff *skb, पूर्णांक len);
अटल अंतरभूत व्योम skb_मुक्त_datagram_locked(काष्ठा sock *sk,
					    काष्ठा sk_buff *skb)
अणु
	__skb_मुक्त_datagram_locked(sk, skb, 0);
पूर्ण
पूर्णांक skb_समाप्त_datagram(काष्ठा sock *sk, काष्ठा sk_buff *skb, अचिन्हित पूर्णांक flags);
पूर्णांक skb_copy_bits(स्थिर काष्ठा sk_buff *skb, पूर्णांक offset, व्योम *to, पूर्णांक len);
पूर्णांक skb_store_bits(काष्ठा sk_buff *skb, पूर्णांक offset, स्थिर व्योम *from, पूर्णांक len);
__wsum skb_copy_and_csum_bits(स्थिर काष्ठा sk_buff *skb, पूर्णांक offset, u8 *to,
			      पूर्णांक len);
पूर्णांक skb_splice_bits(काष्ठा sk_buff *skb, काष्ठा sock *sk, अचिन्हित पूर्णांक offset,
		    काष्ठा pipe_inode_info *pipe, अचिन्हित पूर्णांक len,
		    अचिन्हित पूर्णांक flags);
पूर्णांक skb_send_sock_locked(काष्ठा sock *sk, काष्ठा sk_buff *skb, पूर्णांक offset,
			 पूर्णांक len);
पूर्णांक skb_send_sock(काष्ठा sock *sk, काष्ठा sk_buff *skb, पूर्णांक offset, पूर्णांक len);
व्योम skb_copy_and_csum_dev(स्थिर काष्ठा sk_buff *skb, u8 *to);
अचिन्हित पूर्णांक skb_zerocopy_headlen(स्थिर काष्ठा sk_buff *from);
पूर्णांक skb_zerocopy(काष्ठा sk_buff *to, काष्ठा sk_buff *from,
		 पूर्णांक len, पूर्णांक hlen);
व्योम skb_split(काष्ठा sk_buff *skb, काष्ठा sk_buff *skb1, स्थिर u32 len);
पूर्णांक skb_shअगरt(काष्ठा sk_buff *tgt, काष्ठा sk_buff *skb, पूर्णांक shअगरtlen);
व्योम skb_scrub_packet(काष्ठा sk_buff *skb, bool xnet);
bool skb_gso_validate_network_len(स्थिर काष्ठा sk_buff *skb, अचिन्हित पूर्णांक mtu);
bool skb_gso_validate_mac_len(स्थिर काष्ठा sk_buff *skb, अचिन्हित पूर्णांक len);
काष्ठा sk_buff *skb_segment(काष्ठा sk_buff *skb, netdev_features_t features);
काष्ठा sk_buff *skb_segment_list(काष्ठा sk_buff *skb, netdev_features_t features,
				 अचिन्हित पूर्णांक offset);
काष्ठा sk_buff *skb_vlan_untag(काष्ठा sk_buff *skb);
पूर्णांक skb_ensure_writable(काष्ठा sk_buff *skb, पूर्णांक ग_लिखो_len);
पूर्णांक __skb_vlan_pop(काष्ठा sk_buff *skb, u16 *vlan_tci);
पूर्णांक skb_vlan_pop(काष्ठा sk_buff *skb);
पूर्णांक skb_vlan_push(काष्ठा sk_buff *skb, __be16 vlan_proto, u16 vlan_tci);
पूर्णांक skb_eth_pop(काष्ठा sk_buff *skb);
पूर्णांक skb_eth_push(काष्ठा sk_buff *skb, स्थिर अचिन्हित अक्षर *dst,
		 स्थिर अचिन्हित अक्षर *src);
पूर्णांक skb_mpls_push(काष्ठा sk_buff *skb, __be32 mpls_lse, __be16 mpls_proto,
		  पूर्णांक mac_len, bool ethernet);
पूर्णांक skb_mpls_pop(काष्ठा sk_buff *skb, __be16 next_proto, पूर्णांक mac_len,
		 bool ethernet);
पूर्णांक skb_mpls_update_lse(काष्ठा sk_buff *skb, __be32 mpls_lse);
पूर्णांक skb_mpls_dec_ttl(काष्ठा sk_buff *skb);
काष्ठा sk_buff *pskb_extract(काष्ठा sk_buff *skb, पूर्णांक off, पूर्णांक to_copy,
			     gfp_t gfp);

अटल अंतरभूत पूर्णांक स_नकल_from_msg(व्योम *data, काष्ठा msghdr *msg, पूर्णांक len)
अणु
	वापस copy_from_iter_full(data, len, &msg->msg_iter) ? 0 : -EFAULT;
पूर्ण

अटल अंतरभूत पूर्णांक स_नकल_to_msg(काष्ठा msghdr *msg, व्योम *data, पूर्णांक len)
अणु
	वापस copy_to_iter(data, len, &msg->msg_iter) == len ? 0 : -EFAULT;
पूर्ण

काष्ठा skb_checksum_ops अणु
	__wsum (*update)(स्थिर व्योम *mem, पूर्णांक len, __wsum wsum);
	__wsum (*combine)(__wsum csum, __wsum csum2, पूर्णांक offset, पूर्णांक len);
पूर्ण;

बाह्य स्थिर काष्ठा skb_checksum_ops *crc32c_csum_stub __पढ़ो_mostly;

__wsum __skb_checksum(स्थिर काष्ठा sk_buff *skb, पूर्णांक offset, पूर्णांक len,
		      __wsum csum, स्थिर काष्ठा skb_checksum_ops *ops);
__wsum skb_checksum(स्थिर काष्ठा sk_buff *skb, पूर्णांक offset, पूर्णांक len,
		    __wsum csum);

अटल अंतरभूत व्योम * __must_check
__skb_header_poपूर्णांकer(स्थिर काष्ठा sk_buff *skb, पूर्णांक offset, पूर्णांक len,
		     स्थिर व्योम *data, पूर्णांक hlen, व्योम *buffer)
अणु
	अगर (likely(hlen - offset >= len))
		वापस (व्योम *)data + offset;

	अगर (!skb || unlikely(skb_copy_bits(skb, offset, buffer, len) < 0))
		वापस शून्य;

	वापस buffer;
पूर्ण

अटल अंतरभूत व्योम * __must_check
skb_header_poपूर्णांकer(स्थिर काष्ठा sk_buff *skb, पूर्णांक offset, पूर्णांक len, व्योम *buffer)
अणु
	वापस __skb_header_poपूर्णांकer(skb, offset, len, skb->data,
				    skb_headlen(skb), buffer);
पूर्ण

/**
 *	skb_needs_linearize - check अगर we need to linearize a given skb
 *			      depending on the given device features.
 *	@skb: socket buffer to check
 *	@features: net device features
 *
 *	Returns true अगर either:
 *	1. skb has frag_list and the device करोesn't support FRAGLIST, or
 *	2. skb is fragmented and the device करोes not support SG.
 */
अटल अंतरभूत bool skb_needs_linearize(काष्ठा sk_buff *skb,
				       netdev_features_t features)
अणु
	वापस skb_is_nonlinear(skb) &&
	       ((skb_has_frag_list(skb) && !(features & NETIF_F_FRAGLIST)) ||
		(skb_shinfo(skb)->nr_frags && !(features & NETIF_F_SG)));
पूर्ण

अटल अंतरभूत व्योम skb_copy_from_linear_data(स्थिर काष्ठा sk_buff *skb,
					     व्योम *to,
					     स्थिर अचिन्हित पूर्णांक len)
अणु
	स_नकल(to, skb->data, len);
पूर्ण

अटल अंतरभूत व्योम skb_copy_from_linear_data_offset(स्थिर काष्ठा sk_buff *skb,
						    स्थिर पूर्णांक offset, व्योम *to,
						    स्थिर अचिन्हित पूर्णांक len)
अणु
	स_नकल(to, skb->data + offset, len);
पूर्ण

अटल अंतरभूत व्योम skb_copy_to_linear_data(काष्ठा sk_buff *skb,
					   स्थिर व्योम *from,
					   स्थिर अचिन्हित पूर्णांक len)
अणु
	स_नकल(skb->data, from, len);
पूर्ण

अटल अंतरभूत व्योम skb_copy_to_linear_data_offset(काष्ठा sk_buff *skb,
						  स्थिर पूर्णांक offset,
						  स्थिर व्योम *from,
						  स्थिर अचिन्हित पूर्णांक len)
अणु
	स_नकल(skb->data + offset, from, len);
पूर्ण

व्योम skb_init(व्योम);

अटल अंतरभूत kसमय_प्रकार skb_get_kसमय(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस skb->tstamp;
पूर्ण

/**
 *	skb_get_बारtamp - get बारtamp from a skb
 *	@skb: skb to get stamp from
 *	@stamp: poपूर्णांकer to काष्ठा __kernel_old_समयval to store stamp in
 *
 *	Timestamps are stored in the skb as offsets to a base बारtamp.
 *	This function converts the offset back to a काष्ठा समयval and stores
 *	it in stamp.
 */
अटल अंतरभूत व्योम skb_get_बारtamp(स्थिर काष्ठा sk_buff *skb,
				     काष्ठा __kernel_old_समयval *stamp)
अणु
	*stamp = ns_to_kernel_old_समयval(skb->tstamp);
पूर्ण

अटल अंतरभूत व्योम skb_get_new_बारtamp(स्थिर काष्ठा sk_buff *skb,
					 काष्ठा __kernel_sock_समयval *stamp)
अणु
	काष्ठा बारpec64 ts = kसमय_प्रकारo_बारpec64(skb->tstamp);

	stamp->tv_sec = ts.tv_sec;
	stamp->tv_usec = ts.tv_nsec / 1000;
पूर्ण

अटल अंतरभूत व्योम skb_get_बारtampns(स्थिर काष्ठा sk_buff *skb,
				       काष्ठा __kernel_old_बारpec *stamp)
अणु
	काष्ठा बारpec64 ts = kसमय_प्रकारo_बारpec64(skb->tstamp);

	stamp->tv_sec = ts.tv_sec;
	stamp->tv_nsec = ts.tv_nsec;
पूर्ण

अटल अंतरभूत व्योम skb_get_new_बारtampns(स्थिर काष्ठा sk_buff *skb,
					   काष्ठा __kernel_बारpec *stamp)
अणु
	काष्ठा बारpec64 ts = kसमय_प्रकारo_बारpec64(skb->tstamp);

	stamp->tv_sec = ts.tv_sec;
	stamp->tv_nsec = ts.tv_nsec;
पूर्ण

अटल अंतरभूत व्योम __net_बारtamp(काष्ठा sk_buff *skb)
अणु
	skb->tstamp = kसमय_get_real();
पूर्ण

अटल अंतरभूत kसमय_प्रकार net_समयdelta(kसमय_प्रकार t)
अणु
	वापस kसमय_sub(kसमय_get_real(), t);
पूर्ण

अटल अंतरभूत kसमय_प्रकार net_invalid_बारtamp(व्योम)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत u8 skb_metadata_len(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस skb_shinfo(skb)->meta_len;
पूर्ण

अटल अंतरभूत व्योम *skb_metadata_end(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस skb_mac_header(skb);
पूर्ण

अटल अंतरभूत bool __skb_metadata_dअगरfers(स्थिर काष्ठा sk_buff *skb_a,
					  स्थिर काष्ठा sk_buff *skb_b,
					  u8 meta_len)
अणु
	स्थिर व्योम *a = skb_metadata_end(skb_a);
	स्थिर व्योम *b = skb_metadata_end(skb_b);
	/* Using more efficient varaiant than plain call to स_भेद(). */
#अगर defined(CONFIG_HAVE_EFFICIENT_UNALIGNED_ACCESS) && BITS_PER_LONG == 64
	u64 dअगरfs = 0;

	चयन (meta_len) अणु
#घोषणा __it(x, op) (x -= माप(u##op))
#घोषणा __it_dअगरf(a, b, op) (*(u##op *)__it(a, op)) ^ (*(u##op *)__it(b, op))
	हाल 32: dअगरfs |= __it_dअगरf(a, b, 64);
		fallthrough;
	हाल 24: dअगरfs |= __it_dअगरf(a, b, 64);
		fallthrough;
	हाल 16: dअगरfs |= __it_dअगरf(a, b, 64);
		fallthrough;
	हाल  8: dअगरfs |= __it_dअगरf(a, b, 64);
		अवरोध;
	हाल 28: dअगरfs |= __it_dअगरf(a, b, 64);
		fallthrough;
	हाल 20: dअगरfs |= __it_dअगरf(a, b, 64);
		fallthrough;
	हाल 12: dअगरfs |= __it_dअगरf(a, b, 64);
		fallthrough;
	हाल  4: dअगरfs |= __it_dअगरf(a, b, 32);
		अवरोध;
	पूर्ण
	वापस dअगरfs;
#अन्यथा
	वापस स_भेद(a - meta_len, b - meta_len, meta_len);
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत bool skb_metadata_dअगरfers(स्थिर काष्ठा sk_buff *skb_a,
					स्थिर काष्ठा sk_buff *skb_b)
अणु
	u8 len_a = skb_metadata_len(skb_a);
	u8 len_b = skb_metadata_len(skb_b);

	अगर (!(len_a | len_b))
		वापस false;

	वापस len_a != len_b ?
	       true : __skb_metadata_dअगरfers(skb_a, skb_b, len_a);
पूर्ण

अटल अंतरभूत व्योम skb_metadata_set(काष्ठा sk_buff *skb, u8 meta_len)
अणु
	skb_shinfo(skb)->meta_len = meta_len;
पूर्ण

अटल अंतरभूत व्योम skb_metadata_clear(काष्ठा sk_buff *skb)
अणु
	skb_metadata_set(skb, 0);
पूर्ण

काष्ठा sk_buff *skb_clone_sk(काष्ठा sk_buff *skb);

#अगर_घोषित CONFIG_NETWORK_PHY_TIMESTAMPING

व्योम skb_clone_tx_बारtamp(काष्ठा sk_buff *skb);
bool skb_defer_rx_बारtamp(काष्ठा sk_buff *skb);

#अन्यथा /* CONFIG_NETWORK_PHY_TIMESTAMPING */

अटल अंतरभूत व्योम skb_clone_tx_बारtamp(काष्ठा sk_buff *skb)
अणु
पूर्ण

अटल अंतरभूत bool skb_defer_rx_बारtamp(काष्ठा sk_buff *skb)
अणु
	वापस false;
पूर्ण

#पूर्ण_अगर /* !CONFIG_NETWORK_PHY_TIMESTAMPING */

/**
 * skb_complete_tx_बारtamp() - deliver cloned skb with tx बारtamps
 *
 * PHY drivers may accept clones of transmitted packets क्रम
 * बारtamping via their phy_driver.txtstamp method. These drivers
 * must call this function to वापस the skb back to the stack with a
 * बारtamp.
 *
 * @skb: clone of the original outgoing packet
 * @hwtstamps: hardware समय stamps
 *
 */
व्योम skb_complete_tx_बारtamp(काष्ठा sk_buff *skb,
			       काष्ठा skb_shared_hwtstamps *hwtstamps);

व्योम __skb_tstamp_tx(काष्ठा sk_buff *orig_skb, स्थिर काष्ठा sk_buff *ack_skb,
		     काष्ठा skb_shared_hwtstamps *hwtstamps,
		     काष्ठा sock *sk, पूर्णांक tstype);

/**
 * skb_tstamp_tx - queue clone of skb with send समय stamps
 * @orig_skb:	the original outgoing packet
 * @hwtstamps:	hardware समय stamps, may be शून्य अगर not available
 *
 * If the skb has a socket associated, then this function clones the
 * skb (thus sharing the actual data and optional काष्ठाures), stores
 * the optional hardware समय stamping inक्रमmation (अगर non शून्य) or
 * generates a software समय stamp (otherwise), then queues the clone
 * to the error queue of the socket.  Errors are silently ignored.
 */
व्योम skb_tstamp_tx(काष्ठा sk_buff *orig_skb,
		   काष्ठा skb_shared_hwtstamps *hwtstamps);

/**
 * skb_tx_बारtamp() - Driver hook क्रम transmit बारtamping
 *
 * Ethernet MAC Drivers should call this function in their hard_xmit()
 * function immediately beक्रमe giving the sk_buff to the MAC hardware.
 *
 * Specअगरically, one should make असलolutely sure that this function is
 * called beक्रमe TX completion of this packet can trigger.  Otherwise
 * the packet could potentially alपढ़ोy be मुक्तd.
 *
 * @skb: A socket buffer.
 */
अटल अंतरभूत व्योम skb_tx_बारtamp(काष्ठा sk_buff *skb)
अणु
	skb_clone_tx_बारtamp(skb);
	अगर (skb_shinfo(skb)->tx_flags & SKBTX_SW_TSTAMP)
		skb_tstamp_tx(skb, शून्य);
पूर्ण

/**
 * skb_complete_wअगरi_ack - deliver skb with wअगरi status
 *
 * @skb: the original outgoing packet
 * @acked: ack status
 *
 */
व्योम skb_complete_wअगरi_ack(काष्ठा sk_buff *skb, bool acked);

__sum16 __skb_checksum_complete_head(काष्ठा sk_buff *skb, पूर्णांक len);
__sum16 __skb_checksum_complete(काष्ठा sk_buff *skb);

अटल अंतरभूत पूर्णांक skb_csum_unnecessary(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस ((skb->ip_summed == CHECKSUM_UNNECESSARY) ||
		skb->csum_valid ||
		(skb->ip_summed == CHECKSUM_PARTIAL &&
		 skb_checksum_start_offset(skb) >= 0));
पूर्ण

/**
 *	skb_checksum_complete - Calculate checksum of an entire packet
 *	@skb: packet to process
 *
 *	This function calculates the checksum over the entire packet plus
 *	the value of skb->csum.  The latter can be used to supply the
 *	checksum of a pseuकरो header as used by TCP/UDP.  It वापसs the
 *	checksum.
 *
 *	For protocols that contain complete checksums such as ICMP/TCP/UDP,
 *	this function can be used to verअगरy that checksum on received
 *	packets.  In that हाल the function should वापस zero अगर the
 *	checksum is correct.  In particular, this function will वापस zero
 *	अगर skb->ip_summed is CHECKSUM_UNNECESSARY which indicates that the
 *	hardware has alपढ़ोy verअगरied the correctness of the checksum.
 */
अटल अंतरभूत __sum16 skb_checksum_complete(काष्ठा sk_buff *skb)
अणु
	वापस skb_csum_unnecessary(skb) ?
	       0 : __skb_checksum_complete(skb);
पूर्ण

अटल अंतरभूत व्योम __skb_decr_checksum_unnecessary(काष्ठा sk_buff *skb)
अणु
	अगर (skb->ip_summed == CHECKSUM_UNNECESSARY) अणु
		अगर (skb->csum_level == 0)
			skb->ip_summed = CHECKSUM_NONE;
		अन्यथा
			skb->csum_level--;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम __skb_incr_checksum_unnecessary(काष्ठा sk_buff *skb)
अणु
	अगर (skb->ip_summed == CHECKSUM_UNNECESSARY) अणु
		अगर (skb->csum_level < SKB_MAX_CSUM_LEVEL)
			skb->csum_level++;
	पूर्ण अन्यथा अगर (skb->ip_summed == CHECKSUM_NONE) अणु
		skb->ip_summed = CHECKSUM_UNNECESSARY;
		skb->csum_level = 0;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम __skb_reset_checksum_unnecessary(काष्ठा sk_buff *skb)
अणु
	अगर (skb->ip_summed == CHECKSUM_UNNECESSARY) अणु
		skb->ip_summed = CHECKSUM_NONE;
		skb->csum_level = 0;
	पूर्ण
पूर्ण

/* Check अगर we need to perक्रमm checksum complete validation.
 *
 * Returns true अगर checksum complete is needed, false otherwise
 * (either checksum is unnecessary or zero checksum is allowed).
 */
अटल अंतरभूत bool __skb_checksum_validate_needed(काष्ठा sk_buff *skb,
						  bool zero_okay,
						  __sum16 check)
अणु
	अगर (skb_csum_unnecessary(skb) || (zero_okay && !check)) अणु
		skb->csum_valid = 1;
		__skb_decr_checksum_unnecessary(skb);
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

/* For small packets <= CHECKSUM_BREAK perक्रमm checksum complete directly
 * in checksum_init.
 */
#घोषणा CHECKSUM_BREAK 76

/* Unset checksum-complete
 *
 * Unset checksum complete can be करोne when packet is being modअगरied
 * (uncompressed क्रम instance) and checksum-complete value is
 * invalidated.
 */
अटल अंतरभूत व्योम skb_checksum_complete_unset(काष्ठा sk_buff *skb)
अणु
	अगर (skb->ip_summed == CHECKSUM_COMPLETE)
		skb->ip_summed = CHECKSUM_NONE;
पूर्ण

/* Validate (init) checksum based on checksum complete.
 *
 * Return values:
 *   0: checksum is validated or try to in skb_checksum_complete. In the latter
 *	हाल the ip_summed will not be CHECKSUM_UNNECESSARY and the pseuकरो
 *	checksum is stored in skb->csum क्रम use in __skb_checksum_complete
 *   non-zero: value of invalid checksum
 *
 */
अटल अंतरभूत __sum16 __skb_checksum_validate_complete(काष्ठा sk_buff *skb,
						       bool complete,
						       __wsum psum)
अणु
	अगर (skb->ip_summed == CHECKSUM_COMPLETE) अणु
		अगर (!csum_fold(csum_add(psum, skb->csum))) अणु
			skb->csum_valid = 1;
			वापस 0;
		पूर्ण
	पूर्ण

	skb->csum = psum;

	अगर (complete || skb->len <= CHECKSUM_BREAK) अणु
		__sum16 csum;

		csum = __skb_checksum_complete(skb);
		skb->csum_valid = !csum;
		वापस csum;
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत __wsum null_compute_pseuकरो(काष्ठा sk_buff *skb, पूर्णांक proto)
अणु
	वापस 0;
पूर्ण

/* Perक्रमm checksum validate (init). Note that this is a macro since we only
 * want to calculate the pseuकरो header which is an input function अगर necessary.
 * First we try to validate without any computation (checksum unnecessary) and
 * then calculate based on checksum complete calling the function to compute
 * pseuकरो header.
 *
 * Return values:
 *   0: checksum is validated or try to in skb_checksum_complete
 *   non-zero: value of invalid checksum
 */
#घोषणा __skb_checksum_validate(skb, proto, complete,			\
				zero_okay, check, compute_pseuकरो)	\
(अणु									\
	__sum16 __ret = 0;						\
	skb->csum_valid = 0;						\
	अगर (__skb_checksum_validate_needed(skb, zero_okay, check))	\
		__ret = __skb_checksum_validate_complete(skb,		\
				complete, compute_pseuकरो(skb, proto));	\
	__ret;								\
पूर्ण)

#घोषणा skb_checksum_init(skb, proto, compute_pseuकरो)			\
	__skb_checksum_validate(skb, proto, false, false, 0, compute_pseuकरो)

#घोषणा skb_checksum_init_zero_check(skb, proto, check, compute_pseuकरो)	\
	__skb_checksum_validate(skb, proto, false, true, check, compute_pseuकरो)

#घोषणा skb_checksum_validate(skb, proto, compute_pseuकरो)		\
	__skb_checksum_validate(skb, proto, true, false, 0, compute_pseuकरो)

#घोषणा skb_checksum_validate_zero_check(skb, proto, check,		\
					 compute_pseuकरो)		\
	__skb_checksum_validate(skb, proto, true, true, check, compute_pseuकरो)

#घोषणा skb_checksum_simple_validate(skb)				\
	__skb_checksum_validate(skb, 0, true, false, 0, null_compute_pseuकरो)

अटल अंतरभूत bool __skb_checksum_convert_check(काष्ठा sk_buff *skb)
अणु
	वापस (skb->ip_summed == CHECKSUM_NONE && skb->csum_valid);
पूर्ण

अटल अंतरभूत व्योम __skb_checksum_convert(काष्ठा sk_buff *skb, __wsum pseuकरो)
अणु
	skb->csum = ~pseuकरो;
	skb->ip_summed = CHECKSUM_COMPLETE;
पूर्ण

#घोषणा skb_checksum_try_convert(skb, proto, compute_pseuकरो)	\
करो अणु									\
	अगर (__skb_checksum_convert_check(skb))				\
		__skb_checksum_convert(skb, compute_pseuकरो(skb, proto)); \
पूर्ण जबतक (0)

अटल अंतरभूत व्योम skb_remcsum_adjust_partial(काष्ठा sk_buff *skb, व्योम *ptr,
					      u16 start, u16 offset)
अणु
	skb->ip_summed = CHECKSUM_PARTIAL;
	skb->csum_start = ((अचिन्हित अक्षर *)ptr + start) - skb->head;
	skb->csum_offset = offset - start;
पूर्ण

/* Update skbuf and packet to reflect the remote checksum offload operation.
 * When called, ptr indicates the starting poपूर्णांक क्रम skb->csum when
 * ip_summed is CHECKSUM_COMPLETE. If we need create checksum complete
 * here, skb_postpull_rcsum is करोne so skb->csum start is ptr.
 */
अटल अंतरभूत व्योम skb_remcsum_process(काष्ठा sk_buff *skb, व्योम *ptr,
				       पूर्णांक start, पूर्णांक offset, bool nopartial)
अणु
	__wsum delta;

	अगर (!nopartial) अणु
		skb_remcsum_adjust_partial(skb, ptr, start, offset);
		वापस;
	पूर्ण

	 अगर (unlikely(skb->ip_summed != CHECKSUM_COMPLETE)) अणु
		__skb_checksum_complete(skb);
		skb_postpull_rcsum(skb, skb->data, ptr - (व्योम *)skb->data);
	पूर्ण

	delta = remcsum_adjust(ptr, skb->csum, start, offset);

	/* Adjust skb->csum since we changed the packet */
	skb->csum = csum_add(skb->csum, delta);
पूर्ण

अटल अंतरभूत काष्ठा nf_conntrack *skb_nfct(स्थिर काष्ठा sk_buff *skb)
अणु
#अगर IS_ENABLED(CONFIG_NF_CONNTRACK)
	वापस (व्योम *)(skb->_nfct & NFCT_PTRMASK);
#अन्यथा
	वापस शून्य;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ skb_get_nfct(स्थिर काष्ठा sk_buff *skb)
अणु
#अगर IS_ENABLED(CONFIG_NF_CONNTRACK)
	वापस skb->_nfct;
#अन्यथा
	वापस 0UL;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम skb_set_nfct(काष्ठा sk_buff *skb, अचिन्हित दीर्घ nfct)
अणु
#अगर IS_ENABLED(CONFIG_NF_CONNTRACK)
	skb->_nfct = nfct;
#पूर्ण_अगर
पूर्ण

#अगर_घोषित CONFIG_SKB_EXTENSIONS
क्रमागत skb_ext_id अणु
#अगर IS_ENABLED(CONFIG_BRIDGE_NETFILTER)
	SKB_EXT_BRIDGE_NF,
#पूर्ण_अगर
#अगर_घोषित CONFIG_XFRM
	SKB_EXT_SEC_PATH,
#पूर्ण_अगर
#अगर IS_ENABLED(CONFIG_NET_TC_SKB_EXT)
	TC_SKB_EXT,
#पूर्ण_अगर
#अगर IS_ENABLED(CONFIG_MPTCP)
	SKB_EXT_MPTCP,
#पूर्ण_अगर
	SKB_EXT_NUM, /* must be last */
पूर्ण;

/**
 *	काष्ठा skb_ext - sk_buff extensions
 *	@refcnt: 1 on allocation, deallocated on 0
 *	@offset: offset to add to @data to obtain extension address
 *	@chunks: size currently allocated, stored in SKB_EXT_ALIGN_SHIFT units
 *	@data: start of extension data, variable sized
 *
 *	Note: offsets/lengths are stored in chunks of 8 bytes, this allows
 *	to use 'u8' types जबतक allowing up to 2kb worth of extension data.
 */
काष्ठा skb_ext अणु
	refcount_t refcnt;
	u8 offset[SKB_EXT_NUM]; /* in chunks of 8 bytes */
	u8 chunks;		/* same */
	अक्षर data[] __aligned(8);
पूर्ण;

काष्ठा skb_ext *__skb_ext_alloc(gfp_t flags);
व्योम *__skb_ext_set(काष्ठा sk_buff *skb, क्रमागत skb_ext_id id,
		    काष्ठा skb_ext *ext);
व्योम *skb_ext_add(काष्ठा sk_buff *skb, क्रमागत skb_ext_id id);
व्योम __skb_ext_del(काष्ठा sk_buff *skb, क्रमागत skb_ext_id id);
व्योम __skb_ext_put(काष्ठा skb_ext *ext);

अटल अंतरभूत व्योम skb_ext_put(काष्ठा sk_buff *skb)
अणु
	अगर (skb->active_extensions)
		__skb_ext_put(skb->extensions);
पूर्ण

अटल अंतरभूत व्योम __skb_ext_copy(काष्ठा sk_buff *dst,
				  स्थिर काष्ठा sk_buff *src)
अणु
	dst->active_extensions = src->active_extensions;

	अगर (src->active_extensions) अणु
		काष्ठा skb_ext *ext = src->extensions;

		refcount_inc(&ext->refcnt);
		dst->extensions = ext;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम skb_ext_copy(काष्ठा sk_buff *dst, स्थिर काष्ठा sk_buff *src)
अणु
	skb_ext_put(dst);
	__skb_ext_copy(dst, src);
पूर्ण

अटल अंतरभूत bool __skb_ext_exist(स्थिर काष्ठा skb_ext *ext, क्रमागत skb_ext_id i)
अणु
	वापस !!ext->offset[i];
पूर्ण

अटल अंतरभूत bool skb_ext_exist(स्थिर काष्ठा sk_buff *skb, क्रमागत skb_ext_id id)
अणु
	वापस skb->active_extensions & (1 << id);
पूर्ण

अटल अंतरभूत व्योम skb_ext_del(काष्ठा sk_buff *skb, क्रमागत skb_ext_id id)
अणु
	अगर (skb_ext_exist(skb, id))
		__skb_ext_del(skb, id);
पूर्ण

अटल अंतरभूत व्योम *skb_ext_find(स्थिर काष्ठा sk_buff *skb, क्रमागत skb_ext_id id)
अणु
	अगर (skb_ext_exist(skb, id)) अणु
		काष्ठा skb_ext *ext = skb->extensions;

		वापस (व्योम *)ext + (ext->offset[id] << 3);
	पूर्ण

	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम skb_ext_reset(काष्ठा sk_buff *skb)
अणु
	अगर (unlikely(skb->active_extensions)) अणु
		__skb_ext_put(skb->extensions);
		skb->active_extensions = 0;
	पूर्ण
पूर्ण

अटल अंतरभूत bool skb_has_extensions(काष्ठा sk_buff *skb)
अणु
	वापस unlikely(skb->active_extensions);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम skb_ext_put(काष्ठा sk_buff *skb) अणुपूर्ण
अटल अंतरभूत व्योम skb_ext_reset(काष्ठा sk_buff *skb) अणुपूर्ण
अटल अंतरभूत व्योम skb_ext_del(काष्ठा sk_buff *skb, पूर्णांक unused) अणुपूर्ण
अटल अंतरभूत व्योम __skb_ext_copy(काष्ठा sk_buff *d, स्थिर काष्ठा sk_buff *s) अणुपूर्ण
अटल अंतरभूत व्योम skb_ext_copy(काष्ठा sk_buff *dst, स्थिर काष्ठा sk_buff *s) अणुपूर्ण
अटल अंतरभूत bool skb_has_extensions(काष्ठा sk_buff *skb) अणु वापस false; पूर्ण
#पूर्ण_अगर /* CONFIG_SKB_EXTENSIONS */

अटल अंतरभूत व्योम nf_reset_ct(काष्ठा sk_buff *skb)
अणु
#अगर defined(CONFIG_NF_CONNTRACK) || defined(CONFIG_NF_CONNTRACK_MODULE)
	nf_conntrack_put(skb_nfct(skb));
	skb->_nfct = 0;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम nf_reset_trace(काष्ठा sk_buff *skb)
अणु
#अगर IS_ENABLED(CONFIG_NETFILTER_XT_TARGET_TRACE) || defined(CONFIG_NF_TABLES)
	skb->nf_trace = 0;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम ipvs_reset(काष्ठा sk_buff *skb)
अणु
#अगर IS_ENABLED(CONFIG_IP_VS)
	skb->ipvs_property = 0;
#पूर्ण_अगर
पूर्ण

/* Note: This करोesn't put any conntrack info in dst. */
अटल अंतरभूत व्योम __nf_copy(काष्ठा sk_buff *dst, स्थिर काष्ठा sk_buff *src,
			     bool copy)
अणु
#अगर defined(CONFIG_NF_CONNTRACK) || defined(CONFIG_NF_CONNTRACK_MODULE)
	dst->_nfct = src->_nfct;
	nf_conntrack_get(skb_nfct(src));
#पूर्ण_अगर
#अगर IS_ENABLED(CONFIG_NETFILTER_XT_TARGET_TRACE) || defined(CONFIG_NF_TABLES)
	अगर (copy)
		dst->nf_trace = src->nf_trace;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम nf_copy(काष्ठा sk_buff *dst, स्थिर काष्ठा sk_buff *src)
अणु
#अगर defined(CONFIG_NF_CONNTRACK) || defined(CONFIG_NF_CONNTRACK_MODULE)
	nf_conntrack_put(skb_nfct(dst));
#पूर्ण_अगर
	__nf_copy(dst, src, true);
पूर्ण

#अगर_घोषित CONFIG_NETWORK_SECMARK
अटल अंतरभूत व्योम skb_copy_secmark(काष्ठा sk_buff *to, स्थिर काष्ठा sk_buff *from)
अणु
	to->secmark = from->secmark;
पूर्ण

अटल अंतरभूत व्योम skb_init_secmark(काष्ठा sk_buff *skb)
अणु
	skb->secmark = 0;
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम skb_copy_secmark(काष्ठा sk_buff *to, स्थिर काष्ठा sk_buff *from)
अणु पूर्ण

अटल अंतरभूत व्योम skb_init_secmark(काष्ठा sk_buff *skb)
अणु पूर्ण
#पूर्ण_अगर

अटल अंतरभूत पूर्णांक secpath_exists(स्थिर काष्ठा sk_buff *skb)
अणु
#अगर_घोषित CONFIG_XFRM
	वापस skb_ext_exist(skb, SKB_EXT_SEC_PATH);
#अन्यथा
	वापस 0;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत bool skb_irq_मुक्तable(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस !skb->deकाष्ठाor &&
		!secpath_exists(skb) &&
		!skb_nfct(skb) &&
		!skb->_skb_refdst &&
		!skb_has_frag_list(skb);
पूर्ण

अटल अंतरभूत व्योम skb_set_queue_mapping(काष्ठा sk_buff *skb, u16 queue_mapping)
अणु
	skb->queue_mapping = queue_mapping;
पूर्ण

अटल अंतरभूत u16 skb_get_queue_mapping(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस skb->queue_mapping;
पूर्ण

अटल अंतरभूत व्योम skb_copy_queue_mapping(काष्ठा sk_buff *to, स्थिर काष्ठा sk_buff *from)
अणु
	to->queue_mapping = from->queue_mapping;
पूर्ण

अटल अंतरभूत व्योम skb_record_rx_queue(काष्ठा sk_buff *skb, u16 rx_queue)
अणु
	skb->queue_mapping = rx_queue + 1;
पूर्ण

अटल अंतरभूत u16 skb_get_rx_queue(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस skb->queue_mapping - 1;
पूर्ण

अटल अंतरभूत bool skb_rx_queue_recorded(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस skb->queue_mapping != 0;
पूर्ण

अटल अंतरभूत व्योम skb_set_dst_pending_confirm(काष्ठा sk_buff *skb, u32 val)
अणु
	skb->dst_pending_confirm = val;
पूर्ण

अटल अंतरभूत bool skb_get_dst_pending_confirm(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस skb->dst_pending_confirm != 0;
पूर्ण

अटल अंतरभूत काष्ठा sec_path *skb_sec_path(स्थिर काष्ठा sk_buff *skb)
अणु
#अगर_घोषित CONFIG_XFRM
	वापस skb_ext_find(skb, SKB_EXT_SEC_PATH);
#अन्यथा
	वापस शून्य;
#पूर्ण_अगर
पूर्ण

/* Keeps track of mac header offset relative to skb->head.
 * It is useful क्रम TSO of Tunneling protocol. e.g. GRE.
 * For non-tunnel skb it poपूर्णांकs to skb_mac_header() and क्रम
 * tunnel skb it poपूर्णांकs to outer mac header.
 * Keeps track of level of encapsulation of network headers.
 */
काष्ठा skb_gso_cb अणु
	जोड़ अणु
		पूर्णांक	mac_offset;
		पूर्णांक	data_offset;
	पूर्ण;
	पूर्णांक	encap_level;
	__wsum	csum;
	__u16	csum_start;
पूर्ण;
#घोषणा SKB_GSO_CB_OFFSET	32
#घोषणा SKB_GSO_CB(skb) ((काष्ठा skb_gso_cb *)((skb)->cb + SKB_GSO_CB_OFFSET))

अटल अंतरभूत पूर्णांक skb_tnl_header_len(स्थिर काष्ठा sk_buff *inner_skb)
अणु
	वापस (skb_mac_header(inner_skb) - inner_skb->head) -
		SKB_GSO_CB(inner_skb)->mac_offset;
पूर्ण

अटल अंतरभूत पूर्णांक gso_pskb_expand_head(काष्ठा sk_buff *skb, पूर्णांक extra)
अणु
	पूर्णांक new_headroom, headroom;
	पूर्णांक ret;

	headroom = skb_headroom(skb);
	ret = pskb_expand_head(skb, extra, 0, GFP_ATOMIC);
	अगर (ret)
		वापस ret;

	new_headroom = skb_headroom(skb);
	SKB_GSO_CB(skb)->mac_offset += (new_headroom - headroom);
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम gso_reset_checksum(काष्ठा sk_buff *skb, __wsum res)
अणु
	/* Do not update partial checksums अगर remote checksum is enabled. */
	अगर (skb->remcsum_offload)
		वापस;

	SKB_GSO_CB(skb)->csum = res;
	SKB_GSO_CB(skb)->csum_start = skb_checksum_start(skb) - skb->head;
पूर्ण

/* Compute the checksum क्रम a gso segment. First compute the checksum value
 * from the start of transport header to SKB_GSO_CB(skb)->csum_start, and
 * then add in skb->csum (checksum from csum_start to end of packet).
 * skb->csum and csum_start are then updated to reflect the checksum of the
 * resultant packet starting from the transport header-- the resultant checksum
 * is in the res argument (i.e. normally zero or ~ of checksum of a pseuकरो
 * header.
 */
अटल अंतरभूत __sum16 gso_make_checksum(काष्ठा sk_buff *skb, __wsum res)
अणु
	अचिन्हित अक्षर *csum_start = skb_transport_header(skb);
	पूर्णांक plen = (skb->head + SKB_GSO_CB(skb)->csum_start) - csum_start;
	__wsum partial = SKB_GSO_CB(skb)->csum;

	SKB_GSO_CB(skb)->csum = res;
	SKB_GSO_CB(skb)->csum_start = csum_start - skb->head;

	वापस csum_fold(csum_partial(csum_start, plen, partial));
पूर्ण

अटल अंतरभूत bool skb_is_gso(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस skb_shinfo(skb)->gso_size;
पूर्ण

/* Note: Should be called only अगर skb_is_gso(skb) is true */
अटल अंतरभूत bool skb_is_gso_v6(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस skb_shinfo(skb)->gso_type & SKB_GSO_TCPV6;
पूर्ण

/* Note: Should be called only अगर skb_is_gso(skb) is true */
अटल अंतरभूत bool skb_is_gso_sctp(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस skb_shinfo(skb)->gso_type & SKB_GSO_SCTP;
पूर्ण

/* Note: Should be called only अगर skb_is_gso(skb) is true */
अटल अंतरभूत bool skb_is_gso_tcp(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस skb_shinfo(skb)->gso_type & (SKB_GSO_TCPV4 | SKB_GSO_TCPV6);
पूर्ण

अटल अंतरभूत व्योम skb_gso_reset(काष्ठा sk_buff *skb)
अणु
	skb_shinfo(skb)->gso_size = 0;
	skb_shinfo(skb)->gso_segs = 0;
	skb_shinfo(skb)->gso_type = 0;
पूर्ण

अटल अंतरभूत व्योम skb_increase_gso_size(काष्ठा skb_shared_info *shinfo,
					 u16 increment)
अणु
	अगर (WARN_ON_ONCE(shinfo->gso_size == GSO_BY_FRAGS))
		वापस;
	shinfo->gso_size += increment;
पूर्ण

अटल अंतरभूत व्योम skb_decrease_gso_size(काष्ठा skb_shared_info *shinfo,
					 u16 decrement)
अणु
	अगर (WARN_ON_ONCE(shinfo->gso_size == GSO_BY_FRAGS))
		वापस;
	shinfo->gso_size -= decrement;
पूर्ण

व्योम __skb_warn_lro_क्रमwarding(स्थिर काष्ठा sk_buff *skb);

अटल अंतरभूत bool skb_warn_अगर_lro(स्थिर काष्ठा sk_buff *skb)
अणु
	/* LRO sets gso_size but not gso_type, whereas अगर GSO is really
	 * wanted then gso_type will be set. */
	स्थिर काष्ठा skb_shared_info *shinfo = skb_shinfo(skb);

	अगर (skb_is_nonlinear(skb) && shinfo->gso_size != 0 &&
	    unlikely(shinfo->gso_type == 0)) अणु
		__skb_warn_lro_क्रमwarding(skb);
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल अंतरभूत व्योम skb_क्रमward_csum(काष्ठा sk_buff *skb)
अणु
	/* Unक्रमtunately we करोn't support this one.  Any brave souls? */
	अगर (skb->ip_summed == CHECKSUM_COMPLETE)
		skb->ip_summed = CHECKSUM_NONE;
पूर्ण

/**
 * skb_checksum_none_निश्चित - make sure skb ip_summed is CHECKSUM_NONE
 * @skb: skb to check
 *
 * fresh skbs have their ip_summed set to CHECKSUM_NONE.
 * Instead of क्रमcing ip_summed to CHECKSUM_NONE, we can
 * use this helper, to करोcument places where we make this निश्चितion.
 */
अटल अंतरभूत व्योम skb_checksum_none_निश्चित(स्थिर काष्ठा sk_buff *skb)
अणु
#अगर_घोषित DEBUG
	BUG_ON(skb->ip_summed != CHECKSUM_NONE);
#पूर्ण_अगर
पूर्ण

bool skb_partial_csum_set(काष्ठा sk_buff *skb, u16 start, u16 off);

पूर्णांक skb_checksum_setup(काष्ठा sk_buff *skb, bool recalculate);
काष्ठा sk_buff *skb_checksum_trimmed(काष्ठा sk_buff *skb,
				     अचिन्हित पूर्णांक transport_len,
				     __sum16(*skb_chkf)(काष्ठा sk_buff *skb));

/**
 * skb_head_is_locked - Determine अगर the skb->head is locked करोwn
 * @skb: skb to check
 *
 * The head on skbs build around a head frag can be हटाओd अगर they are
 * not cloned.  This function वापसs true अगर the skb head is locked करोwn
 * due to either being allocated via kदो_स्मृति, or by being a clone with
 * multiple references to the head.
 */
अटल अंतरभूत bool skb_head_is_locked(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस !skb->head_frag || skb_cloned(skb);
पूर्ण

/* Local Checksum Offload.
 * Compute outer checksum based on the assumption that the
 * inner checksum will be offloaded later.
 * See Documentation/networking/checksum-offloads.rst क्रम
 * explanation of how this works.
 * Fill in outer checksum adjusपंचांगent (e.g. with sum of outer
 * pseuकरो-header) beक्रमe calling.
 * Also ensure that inner checksum is in linear data area.
 */
अटल अंतरभूत __wsum lco_csum(काष्ठा sk_buff *skb)
अणु
	अचिन्हित अक्षर *csum_start = skb_checksum_start(skb);
	अचिन्हित अक्षर *l4_hdr = skb_transport_header(skb);
	__wsum partial;

	/* Start with complement of inner checksum adjusपंचांगent */
	partial = ~csum_unfold(*(__क्रमce __sum16 *)(csum_start +
						    skb->csum_offset));

	/* Add in checksum of our headers (incl. outer checksum
	 * adjusपंचांगent filled in by caller) and वापस result.
	 */
	वापस csum_partial(l4_hdr, csum_start - l4_hdr, partial);
पूर्ण

अटल अंतरभूत bool skb_is_redirected(स्थिर काष्ठा sk_buff *skb)
अणु
#अगर_घोषित CONFIG_NET_REसूचीECT
	वापस skb->redirected;
#अन्यथा
	वापस false;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम skb_set_redirected(काष्ठा sk_buff *skb, bool from_ingress)
अणु
#अगर_घोषित CONFIG_NET_REसूचीECT
	skb->redirected = 1;
	skb->from_ingress = from_ingress;
	अगर (skb->from_ingress)
		skb->tstamp = 0;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम skb_reset_redirect(काष्ठा sk_buff *skb)
अणु
#अगर_घोषित CONFIG_NET_REसूचीECT
	skb->redirected = 0;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत bool skb_csum_is_sctp(काष्ठा sk_buff *skb)
अणु
	वापस skb->csum_not_inet;
पूर्ण

अटल अंतरभूत व्योम skb_set_kcov_handle(काष्ठा sk_buff *skb,
				       स्थिर u64 kcov_handle)
अणु
#अगर_घोषित CONFIG_KCOV
	skb->kcov_handle = kcov_handle;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत u64 skb_get_kcov_handle(काष्ठा sk_buff *skb)
अणु
#अगर_घोषित CONFIG_KCOV
	वापस skb->kcov_handle;
#अन्यथा
	वापस 0;
#पूर्ण_अगर
पूर्ण

#पूर्ण_अगर	/* __KERNEL__ */
#पूर्ण_अगर	/* _LINUX_SKBUFF_H */
