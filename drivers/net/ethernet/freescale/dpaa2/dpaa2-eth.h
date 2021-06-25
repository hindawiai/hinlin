<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0+ OR BSD-3-Clause) */
/* Copyright 2014-2016 Freescale Semiconductor Inc.
 * Copyright 2016-2020 NXP
 */

#अगर_अघोषित __DPAA2_ETH_H
#घोषणा __DPAA2_ETH_H

#समावेश <linux/dcbnl.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/fsl/mc.h>
#समावेश <linux/net_tstamp.h>
#समावेश <net/devlink.h>

#समावेश <soc/fsl/dpaa2-पन.स>
#समावेश <soc/fsl/dpaa2-fd.h>
#समावेश "dpni.h"
#समावेश "dpni-cmd.h"

#समावेश "dpaa2-eth-trace.h"
#समावेश "dpaa2-eth-debugfs.h"
#समावेश "dpaa2-mac.h"

#घोषणा DPAA2_WRIOP_VERSION(x, y, z) ((x) << 10 | (y) << 5 | (z) << 0)

#घोषणा DPAA2_ETH_STORE_SIZE		16

/* Maximum number of scatter-gather entries in an ingress frame,
 * considering the maximum receive frame size is 64K
 */
#घोषणा DPAA2_ETH_MAX_SG_ENTRIES	((64 * 1024) / DPAA2_ETH_RX_BUF_SIZE)

/* Maximum acceptable MTU value. It is in direct relation with the hardware
 * enक्रमced Max Frame Length (currently 10k).
 */
#घोषणा DPAA2_ETH_MFL			(10 * 1024)
#घोषणा DPAA2_ETH_MAX_MTU		(DPAA2_ETH_MFL - VLAN_ETH_HLEN)
/* Convert L3 MTU to L2 MFL */
#घोषणा DPAA2_ETH_L2_MAX_FRM(mtu)	((mtu) + VLAN_ETH_HLEN)

/* Set the taildrop threshold (in bytes) to allow the enqueue of a large
 * enough number of jumbo frames in the Rx queues (length of the current
 * frame is not taken पूर्णांकo account when making the taildrop decision)
 */
#घोषणा DPAA2_ETH_FQ_TAILDROP_THRESH	(1024 * 1024)

/* Maximum burst size value क्रम Tx shaping */
#घोषणा DPAA2_ETH_MAX_BURST_SIZE	0xF7FF

/* Maximum number of Tx confirmation frames to be processed
 * in a single NAPI call
 */
#घोषणा DPAA2_ETH_TXCONF_PER_NAPI	256

/* Buffer qouta per channel. We want to keep in check number of ingress frames
 * in flight: क्रम small sized frames, congestion group taildrop may kick in
 * first; क्रम large sizes, Rx FQ taildrop threshold will ensure only a
 * reasonable number of frames will be pending at any given समय.
 * Ingress frame drop due to buffer pool depletion should be a corner हाल only
 */
#घोषणा DPAA2_ETH_NUM_BUFS		1280
#घोषणा DPAA2_ETH_REFILL_THRESH \
	(DPAA2_ETH_NUM_BUFS - DPAA2_ETH_BUFS_PER_CMD)

/* Congestion group taildrop threshold: number of frames allowed to accumulate
 * at any moment in a group of Rx queues beदीर्घing to the same traffic class.
 * Choose value such that we करोn't risk depleting the buffer pool beक्रमe the
 * taildrop kicks in
 */
#घोषणा DPAA2_ETH_CG_TAILDROP_THRESH(priv)				\
	(1024 * dpaa2_eth_queue_count(priv) / dpaa2_eth_tc_count(priv))

/* Congestion group notअगरication threshold: when this many frames accumulate
 * on the Rx queues beदीर्घing to the same TC, the MAC is inकाष्ठाed to send
 * PFC frames क्रम that TC.
 * When number of pending frames drops below निकास threshold transmission of
 * PFC frames is stopped.
 */
#घोषणा DPAA2_ETH_CN_THRESH_ENTRY(priv) \
	(DPAA2_ETH_CG_TAILDROP_THRESH(priv) / 2)
#घोषणा DPAA2_ETH_CN_THRESH_EXIT(priv) \
	(DPAA2_ETH_CN_THRESH_ENTRY(priv) * 3 / 4)

/* Maximum number of buffers that can be acquired/released through a single
 * QBMan command
 */
#घोषणा DPAA2_ETH_BUFS_PER_CMD		7

/* Hardware requires alignment क्रम ingress/egress buffer addresses */
#घोषणा DPAA2_ETH_TX_BUF_ALIGN		64

#घोषणा DPAA2_ETH_RX_BUF_RAW_SIZE	PAGE_SIZE
#घोषणा DPAA2_ETH_RX_BUF_TAILROOM \
	SKB_DATA_ALIGN(माप(काष्ठा skb_shared_info))
#घोषणा DPAA2_ETH_RX_BUF_SIZE \
	(DPAA2_ETH_RX_BUF_RAW_SIZE - DPAA2_ETH_RX_BUF_TAILROOM)

/* Hardware annotation area in RX/TX buffers */
#घोषणा DPAA2_ETH_RX_HWA_SIZE		64
#घोषणा DPAA2_ETH_TX_HWA_SIZE		128

/* PTP nominal frequency 1GHz */
#घोषणा DPAA2_PTP_CLK_PERIOD_NS		1

/* Due to a limitation in WRIOP 1.0.0, the RX buffer data must be aligned
 * to 256B. For newer revisions, the requirement is only क्रम 64B alignment
 */
#घोषणा DPAA2_ETH_RX_BUF_ALIGN_REV1	256
#घोषणा DPAA2_ETH_RX_BUF_ALIGN		64

/* We are accommodating a skb backpoपूर्णांकer and some S/G info
 * in the frame's software annotation. The hardware
 * options are either 0 or 64, so we choose the latter.
 */
#घोषणा DPAA2_ETH_SWA_SIZE		64

/* We store dअगरferent inक्रमmation in the software annotation area of a Tx frame
 * based on what type of frame it is
 */
क्रमागत dpaa2_eth_swa_type अणु
	DPAA2_ETH_SWA_SINGLE,
	DPAA2_ETH_SWA_SG,
	DPAA2_ETH_SWA_XDP,
पूर्ण;

/* Must keep this काष्ठा smaller than DPAA2_ETH_SWA_SIZE */
काष्ठा dpaa2_eth_swa अणु
	क्रमागत dpaa2_eth_swa_type type;
	जोड़ अणु
		काष्ठा अणु
			काष्ठा sk_buff *skb;
			पूर्णांक sgt_size;
		पूर्ण single;
		काष्ठा अणु
			काष्ठा sk_buff *skb;
			काष्ठा scatterlist *scl;
			पूर्णांक num_sg;
			पूर्णांक sgt_size;
		पूर्ण sg;
		काष्ठा अणु
			पूर्णांक dma_size;
			काष्ठा xdp_frame *xdpf;
		पूर्ण xdp;
	पूर्ण;
पूर्ण;

/* Annotation valid bits in FD FRC */
#घोषणा DPAA2_FD_FRC_FASV		0x8000
#घोषणा DPAA2_FD_FRC_FAEADV		0x4000
#घोषणा DPAA2_FD_FRC_FAPRV		0x2000
#घोषणा DPAA2_FD_FRC_FAIADV		0x1000
#घोषणा DPAA2_FD_FRC_FASWOV		0x0800
#घोषणा DPAA2_FD_FRC_FAICFDV		0x0400

/* Error bits in FD CTRL */
#घोषणा DPAA2_FD_RX_ERR_MASK		(FD_CTRL_SBE | FD_CTRL_FAERR)
#घोषणा DPAA2_FD_TX_ERR_MASK		(FD_CTRL_UFD	| \
					 FD_CTRL_SBE	| \
					 FD_CTRL_FSE	| \
					 FD_CTRL_FAERR)

/* Annotation bits in FD CTRL */
#घोषणा DPAA2_FD_CTRL_ASAL		0x00020000	/* ASAL = 128B */

/* Frame annotation status */
काष्ठा dpaa2_fas अणु
	u8 reserved;
	u8 ppid;
	__le16 अगरpid;
	__le32 status;
पूर्ण;

/* Frame annotation status word is located in the first 8 bytes
 * of the buffer's hardware annoatation area
 */
#घोषणा DPAA2_FAS_OFFSET		0
#घोषणा DPAA2_FAS_SIZE			(माप(काष्ठा dpaa2_fas))

/* Timestamp is located in the next 8 bytes of the buffer's
 * hardware annotation area
 */
#घोषणा DPAA2_TS_OFFSET			0x8

/* Frame annotation parse results */
काष्ठा dpaa2_fapr अणु
	/* 64-bit word 1 */
	__le32 faf_lo;
	__le16 faf_ext;
	__le16 nxt_hdr;
	/* 64-bit word 2 */
	__le64 faf_hi;
	/* 64-bit word 3 */
	u8 last_ethertype_offset;
	u8 vlan_tci_offset_n;
	u8 vlan_tci_offset_1;
	u8 llc_snap_offset;
	u8 eth_offset;
	u8 ip1_pid_offset;
	u8 shim_offset_2;
	u8 shim_offset_1;
	/* 64-bit word 4 */
	u8 l5_offset;
	u8 l4_offset;
	u8 gre_offset;
	u8 l3_offset_n;
	u8 l3_offset_1;
	u8 mpls_offset_n;
	u8 mpls_offset_1;
	u8 pppoe_offset;
	/* 64-bit word 5 */
	__le16 running_sum;
	__le16 gross_running_sum;
	u8 ipv6_frag_offset;
	u8 nxt_hdr_offset;
	u8 routing_hdr_offset_2;
	u8 routing_hdr_offset_1;
	/* 64-bit word 6 */
	u8 reserved[5]; /* Soft-parsing context */
	u8 ip_proto_offset_n;
	u8 nxt_hdr_frag_offset;
	u8 parse_error_code;
पूर्ण;

#घोषणा DPAA2_FAPR_OFFSET		0x10
#घोषणा DPAA2_FAPR_SIZE			माप((काष्ठा dpaa2_fapr))

/* Frame annotation egress action descriptor */
#घोषणा DPAA2_FAEAD_OFFSET		0x58

काष्ठा dpaa2_faead अणु
	__le32 conf_fqid;
	__le32 ctrl;
पूर्ण;

#घोषणा DPAA2_FAEAD_A2V			0x20000000
#घोषणा DPAA2_FAEAD_A4V			0x08000000
#घोषणा DPAA2_FAEAD_UPDV		0x00001000
#घोषणा DPAA2_FAEAD_EBDDV		0x00002000
#घोषणा DPAA2_FAEAD_UPD			0x00000010

काष्ठा ptp_tstamp अणु
	u16 sec_msb;
	u32 sec_lsb;
	u32 nsec;
पूर्ण;

अटल अंतरभूत व्योम ns_to_ptp_tstamp(काष्ठा ptp_tstamp *tstamp, u64 ns)
अणु
	u64 sec, nsec;

	sec = ns;
	nsec = करो_भाग(sec, 1000000000);

	tstamp->sec_lsb = sec & 0xFFFFFFFF;
	tstamp->sec_msb = (sec >> 32) & 0xFFFF;
	tstamp->nsec = nsec;
पूर्ण

/* Accessors क्रम the hardware annotation fields that we use */
अटल अंतरभूत व्योम *dpaa2_get_hwa(व्योम *buf_addr, bool swa)
अणु
	वापस buf_addr + (swa ? DPAA2_ETH_SWA_SIZE : 0);
पूर्ण

अटल अंतरभूत काष्ठा dpaa2_fas *dpaa2_get_fas(व्योम *buf_addr, bool swa)
अणु
	वापस dpaa2_get_hwa(buf_addr, swa) + DPAA2_FAS_OFFSET;
पूर्ण

अटल अंतरभूत __le64 *dpaa2_get_ts(व्योम *buf_addr, bool swa)
अणु
	वापस dpaa2_get_hwa(buf_addr, swa) + DPAA2_TS_OFFSET;
पूर्ण

अटल अंतरभूत काष्ठा dpaa2_fapr *dpaa2_get_fapr(व्योम *buf_addr, bool swa)
अणु
	वापस dpaa2_get_hwa(buf_addr, swa) + DPAA2_FAPR_OFFSET;
पूर्ण

अटल अंतरभूत काष्ठा dpaa2_faead *dpaa2_get_faead(व्योम *buf_addr, bool swa)
अणु
	वापस dpaa2_get_hwa(buf_addr, swa) + DPAA2_FAEAD_OFFSET;
पूर्ण

/* Error and status bits in the frame annotation status word */
/* Debug frame, otherwise supposed to be discarded */
#घोषणा DPAA2_FAS_DISC			0x80000000
/* MACSEC frame */
#घोषणा DPAA2_FAS_MS			0x40000000
#घोषणा DPAA2_FAS_PTP			0x08000000
/* Ethernet multicast frame */
#घोषणा DPAA2_FAS_MC			0x04000000
/* Ethernet broadcast frame */
#घोषणा DPAA2_FAS_BC			0x02000000
#घोषणा DPAA2_FAS_KSE			0x00040000
#घोषणा DPAA2_FAS_खातापूर्णHE			0x00020000
#घोषणा DPAA2_FAS_MNLE			0x00010000
#घोषणा DPAA2_FAS_TIDE			0x00008000
#घोषणा DPAA2_FAS_PIEE			0x00004000
/* Frame length error */
#घोषणा DPAA2_FAS_FLE			0x00002000
/* Frame physical error */
#घोषणा DPAA2_FAS_FPE			0x00001000
#घोषणा DPAA2_FAS_PTE			0x00000080
#घोषणा DPAA2_FAS_ISP			0x00000040
#घोषणा DPAA2_FAS_PHE			0x00000020
#घोषणा DPAA2_FAS_BLE			0x00000010
/* L3 csum validation perक्रमmed */
#घोषणा DPAA2_FAS_L3CV			0x00000008
/* L3 csum error */
#घोषणा DPAA2_FAS_L3CE			0x00000004
/* L4 csum validation perक्रमmed */
#घोषणा DPAA2_FAS_L4CV			0x00000002
/* L4 csum error */
#घोषणा DPAA2_FAS_L4CE			0x00000001
/* Possible errors on the ingress path */
#घोषणा DPAA2_FAS_RX_ERR_MASK		(DPAA2_FAS_KSE		| \
					 DPAA2_FAS_खातापूर्णHE	| \
					 DPAA2_FAS_MNLE		| \
					 DPAA2_FAS_TIDE		| \
					 DPAA2_FAS_PIEE		| \
					 DPAA2_FAS_FLE		| \
					 DPAA2_FAS_FPE		| \
					 DPAA2_FAS_PTE		| \
					 DPAA2_FAS_ISP		| \
					 DPAA2_FAS_PHE		| \
					 DPAA2_FAS_BLE		| \
					 DPAA2_FAS_L3CE		| \
					 DPAA2_FAS_L4CE)

/* Time in milliseconds between link state updates */
#घोषणा DPAA2_ETH_LINK_STATE_REFRESH	1000

/* Number of बार to retry a frame enqueue beक्रमe giving up.
 * Value determined empirically, in order to minimize the number
 * of frames dropped on Tx
 */
#घोषणा DPAA2_ETH_ENQUEUE_RETRIES	10

/* Number of बार to retry DPIO portal operations जबतक रुकोing
 * क्रम portal to finish executing current command and become
 * available. We want to aव्योम being stuck in a जबतक loop in हाल
 * hardware becomes unresponsive, but not give up too easily अगर
 * the portal really is busy क्रम valid reasons
 */
#घोषणा DPAA2_ETH_SWP_BUSY_RETRIES	1000

/* Driver statistics, other than those in काष्ठा rtnl_link_stats64.
 * These are usually collected per-CPU and aggregated by ethtool.
 */
काष्ठा dpaa2_eth_drv_stats अणु
	__u64	tx_conf_frames;
	__u64	tx_conf_bytes;
	__u64	tx_sg_frames;
	__u64	tx_sg_bytes;
	__u64	rx_sg_frames;
	__u64	rx_sg_bytes;
	/* Linear skbs sent as a S/G FD due to insufficient headroom */
	__u64	tx_converted_sg_frames;
	__u64	tx_converted_sg_bytes;
	/* Enqueues retried due to portal busy */
	__u64	tx_portal_busy;
पूर्ण;

/* Per-FQ statistics */
काष्ठा dpaa2_eth_fq_stats अणु
	/* Number of frames received on this queue */
	__u64 frames;
पूर्ण;

/* Per-channel statistics */
काष्ठा dpaa2_eth_ch_stats अणु
	/* Volatile dequeues retried due to portal busy */
	__u64 dequeue_portal_busy;
	/* Pull errors */
	__u64 pull_err;
	/* Number of CDANs; useful to estimate avg NAPI len */
	__u64 cdan;
	/* XDP counters */
	__u64 xdp_drop;
	__u64 xdp_tx;
	__u64 xdp_tx_err;
	__u64 xdp_redirect;
	/* Must be last, करोes not show up in ethtool stats */
	__u64 frames;
पूर्ण;

/* Maximum number of queues associated with a DPNI */
#घोषणा DPAA2_ETH_MAX_TCS		8
#घोषणा DPAA2_ETH_MAX_RX_QUEUES_PER_TC	16
#घोषणा DPAA2_ETH_MAX_RX_QUEUES		\
	(DPAA2_ETH_MAX_RX_QUEUES_PER_TC * DPAA2_ETH_MAX_TCS)
#घोषणा DPAA2_ETH_MAX_TX_QUEUES		16
#घोषणा DPAA2_ETH_MAX_RX_ERR_QUEUES	1
#घोषणा DPAA2_ETH_MAX_QUEUES		(DPAA2_ETH_MAX_RX_QUEUES + \
					DPAA2_ETH_MAX_TX_QUEUES + \
					DPAA2_ETH_MAX_RX_ERR_QUEUES)
#घोषणा DPAA2_ETH_MAX_NETDEV_QUEUES	\
	(DPAA2_ETH_MAX_TX_QUEUES * DPAA2_ETH_MAX_TCS)

#घोषणा DPAA2_ETH_MAX_DPCONS		16

क्रमागत dpaa2_eth_fq_type अणु
	DPAA2_RX_FQ = 0,
	DPAA2_TX_CONF_FQ,
	DPAA2_RX_ERR_FQ
पूर्ण;

काष्ठा dpaa2_eth_priv;

काष्ठा dpaa2_eth_xdp_fds अणु
	काष्ठा dpaa2_fd fds[DEV_MAP_BULK_SIZE];
	sमाप_प्रकार num;
पूर्ण;

काष्ठा dpaa2_eth_fq अणु
	u32 fqid;
	u32 tx_qdbin;
	u32 tx_fqid[DPAA2_ETH_MAX_TCS];
	u16 flowid;
	u8 tc;
	पूर्णांक target_cpu;
	u32 dq_frames;
	u32 dq_bytes;
	काष्ठा dpaa2_eth_channel *channel;
	क्रमागत dpaa2_eth_fq_type type;

	व्योम (*consume)(काष्ठा dpaa2_eth_priv *priv,
			काष्ठा dpaa2_eth_channel *ch,
			स्थिर काष्ठा dpaa2_fd *fd,
			काष्ठा dpaa2_eth_fq *fq);
	काष्ठा dpaa2_eth_fq_stats stats;

	काष्ठा dpaa2_eth_xdp_fds xdp_redirect_fds;
	काष्ठा dpaa2_eth_xdp_fds xdp_tx_fds;
पूर्ण;

काष्ठा dpaa2_eth_ch_xdp अणु
	काष्ठा bpf_prog *prog;
	अचिन्हित पूर्णांक res;
पूर्ण;

काष्ठा dpaa2_eth_channel अणु
	काष्ठा dpaa2_io_notअगरication_ctx nctx;
	काष्ठा fsl_mc_device *dpcon;
	पूर्णांक dpcon_id;
	पूर्णांक ch_id;
	काष्ठा napi_काष्ठा napi;
	काष्ठा dpaa2_io *dpio;
	काष्ठा dpaa2_io_store *store;
	काष्ठा dpaa2_eth_priv *priv;
	पूर्णांक buf_count;
	काष्ठा dpaa2_eth_ch_stats stats;
	काष्ठा dpaa2_eth_ch_xdp xdp;
	काष्ठा xdp_rxq_info xdp_rxq;
	काष्ठा list_head *rx_list;

	/* Buffers to be recycled back in the buffer pool */
	u64 recycled_bufs[DPAA2_ETH_BUFS_PER_CMD];
	पूर्णांक recycled_bufs_cnt;
पूर्ण;

काष्ठा dpaa2_eth_dist_fields अणु
	u64 rxnfc_field;
	क्रमागत net_prot cls_prot;
	पूर्णांक cls_field;
	पूर्णांक size;
	u64 id;
पूर्ण;

काष्ठा dpaa2_eth_cls_rule अणु
	काष्ठा ethtool_rx_flow_spec fs;
	u8 in_use;
पूर्ण;

#घोषणा DPAA2_ETH_SGT_CACHE_SIZE	256
काष्ठा dpaa2_eth_sgt_cache अणु
	व्योम *buf[DPAA2_ETH_SGT_CACHE_SIZE];
	u16 count;
पूर्ण;

काष्ठा dpaa2_eth_trap_item अणु
	व्योम *trap_ctx;
पूर्ण;

काष्ठा dpaa2_eth_trap_data अणु
	काष्ठा dpaa2_eth_trap_item *trap_items_arr;
	काष्ठा dpaa2_eth_priv *priv;
पूर्ण;

#घोषणा DPAA2_ETH_DEFAULT_COPYBREAK	512

/* Driver निजी data */
काष्ठा dpaa2_eth_priv अणु
	काष्ठा net_device *net_dev;

	u8 num_fqs;
	काष्ठा dpaa2_eth_fq fq[DPAA2_ETH_MAX_QUEUES];
	पूर्णांक (*enqueue)(काष्ठा dpaa2_eth_priv *priv,
		       काष्ठा dpaa2_eth_fq *fq,
		       काष्ठा dpaa2_fd *fd, u8 prio,
		       u32 num_frames,
		       पूर्णांक *frames_enqueued);

	u8 num_channels;
	काष्ठा dpaa2_eth_channel *channel[DPAA2_ETH_MAX_DPCONS];
	काष्ठा dpaa2_eth_sgt_cache __percpu *sgt_cache;

	काष्ठा dpni_attr dpni_attrs;
	u16 dpni_ver_major;
	u16 dpni_ver_minor;
	u16 tx_data_offset;

	काष्ठा fsl_mc_device *dpbp_dev;
	u16 rx_buf_size;
	u16 bpid;
	काष्ठा iommu_करोमुख्य *iommu_करोमुख्य;

	क्रमागत hwtstamp_tx_types tx_tstamp_type;	/* Tx बारtamping type */
	bool rx_tstamp;				/* Rx बारtamping enabled */

	u16 tx_qdid;
	काष्ठा fsl_mc_io *mc_io;
	/* Cores which have an affine DPIO/DPCON.
	 * This is the cpu set on which Rx and Tx conf frames are processed
	 */
	काष्ठा cpumask dpio_cpumask;

	/* Standard statistics */
	काष्ठा rtnl_link_stats64 __percpu *percpu_stats;
	/* Extra stats, in addition to the ones known by the kernel */
	काष्ठा dpaa2_eth_drv_stats __percpu *percpu_extras;

	u16 mc_token;
	u8 rx_fqtd_enabled;
	u8 rx_cgtd_enabled;

	काष्ठा dpni_link_state link_state;
	bool करो_link_poll;
	काष्ठा task_काष्ठा *poll_thपढ़ो;

	/* enabled ethtool hashing bits */
	u64 rx_hash_fields;
	u64 rx_cls_fields;
	काष्ठा dpaa2_eth_cls_rule *cls_rules;
	u8 rx_cls_enabled;
	u8 vlan_cls_enabled;
	u8 pfc_enabled;
#अगर_घोषित CONFIG_FSL_DPAA2_ETH_DCB
	u8 dcbx_mode;
	काष्ठा ieee_pfc pfc;
#पूर्ण_अगर
	काष्ठा bpf_prog *xdp_prog;
#अगर_घोषित CONFIG_DEBUG_FS
	काष्ठा dpaa2_debugfs dbg;
#पूर्ण_अगर

	काष्ठा dpaa2_mac *mac;
	काष्ठा workqueue_काष्ठा	*dpaa2_ptp_wq;
	काष्ठा work_काष्ठा	tx_onestep_tstamp;
	काष्ठा sk_buff_head	tx_skbs;
	/* The one-step बारtamping configuration on hardware
	 * रेजिस्टरs could only be करोne when no one-step
	 * बारtamping frames are in flight. So we use a mutex
	 * lock here to make sure the lock is released by last
	 * one-step बारtamping packet through TX confirmation
	 * queue beक्रमe transmit current packet.
	 */
	काष्ठा mutex		onestep_tstamp_lock;
	काष्ठा devlink *devlink;
	काष्ठा dpaa2_eth_trap_data *trap_data;
	काष्ठा devlink_port devlink_port;

	u32 rx_copyअवरोध;
पूर्ण;

काष्ठा dpaa2_eth_devlink_priv अणु
	काष्ठा dpaa2_eth_priv *dpaa2_priv;
पूर्ण;

#घोषणा TX_TSTAMP		0x1
#घोषणा TX_TSTAMP_ONESTEP_SYNC	0x2

#घोषणा DPAA2_RXH_SUPPORTED	(RXH_L2DA | RXH_VLAN | RXH_L3_PROTO \
				| RXH_IP_SRC | RXH_IP_DST | RXH_L4_B_0_1 \
				| RXH_L4_B_2_3)

/* शेष Rx hash options, set during probing */
#घोषणा DPAA2_RXH_DEFAULT	(RXH_L3_PROTO | RXH_IP_SRC | RXH_IP_DST | \
				 RXH_L4_B_0_1 | RXH_L4_B_2_3)

#घोषणा dpaa2_eth_hash_enabled(priv)	\
	((priv)->dpni_attrs.num_queues > 1)

/* Required by काष्ठा dpni_rx_tc_dist_cfg::key_cfg_iova */
#घोषणा DPAA2_CLASSIFIER_DMA_SIZE 256

बाह्य स्थिर काष्ठा ethtool_ops dpaa2_ethtool_ops;
बाह्य पूर्णांक dpaa2_phc_index;
बाह्य काष्ठा ptp_qoriq *dpaa2_ptp;

अटल अंतरभूत पूर्णांक dpaa2_eth_cmp_dpni_ver(काष्ठा dpaa2_eth_priv *priv,
					 u16 ver_major, u16 ver_minor)
अणु
	अगर (priv->dpni_ver_major == ver_major)
		वापस priv->dpni_ver_minor - ver_minor;
	वापस priv->dpni_ver_major - ver_major;
पूर्ण

/* Minimum firmware version that supports a more flexible API
 * क्रम configuring the Rx flow hash key
 */
#घोषणा DPNI_RX_DIST_KEY_VER_MAJOR	7
#घोषणा DPNI_RX_DIST_KEY_VER_MINOR	5

#घोषणा dpaa2_eth_has_legacy_dist(priv)					\
	(dpaa2_eth_cmp_dpni_ver((priv), DPNI_RX_DIST_KEY_VER_MAJOR,	\
				DPNI_RX_DIST_KEY_VER_MINOR) < 0)

#घोषणा dpaa2_eth_fs_enabled(priv)	\
	(!((priv)->dpni_attrs.options & DPNI_OPT_NO_FS))

#घोषणा dpaa2_eth_fs_mask_enabled(priv)	\
	((priv)->dpni_attrs.options & DPNI_OPT_HAS_KEY_MASKING)

#घोषणा dpaa2_eth_fs_count(priv)        \
	((priv)->dpni_attrs.fs_entries)

#घोषणा dpaa2_eth_tc_count(priv)	\
	((priv)->dpni_attrs.num_tcs)

/* We have exactly one अणुRx, Tx confपूर्ण queue per channel */
#घोषणा dpaa2_eth_queue_count(priv)     \
	((priv)->num_channels)

क्रमागत dpaa2_eth_rx_dist अणु
	DPAA2_ETH_RX_DIST_HASH,
	DPAA2_ETH_RX_DIST_CLS
पूर्ण;

/* Unique IDs क्रम the supported Rx classअगरication header fields */
#घोषणा DPAA2_ETH_DIST_ETHDST		BIT(0)
#घोषणा DPAA2_ETH_DIST_ETHSRC		BIT(1)
#घोषणा DPAA2_ETH_DIST_ETHTYPE		BIT(2)
#घोषणा DPAA2_ETH_DIST_VLAN		BIT(3)
#घोषणा DPAA2_ETH_DIST_IPSRC		BIT(4)
#घोषणा DPAA2_ETH_DIST_IPDST		BIT(5)
#घोषणा DPAA2_ETH_DIST_IPPROTO		BIT(6)
#घोषणा DPAA2_ETH_DIST_L4SRC		BIT(7)
#घोषणा DPAA2_ETH_DIST_L4DST		BIT(8)
#घोषणा DPAA2_ETH_DIST_ALL		(~0ULL)

#घोषणा DPNI_PAUSE_VER_MAJOR		7
#घोषणा DPNI_PAUSE_VER_MINOR		13
#घोषणा dpaa2_eth_has_छोड़ो_support(priv)			\
	(dpaa2_eth_cmp_dpni_ver((priv), DPNI_PAUSE_VER_MAJOR,	\
				DPNI_PAUSE_VER_MINOR) >= 0)

अटल अंतरभूत bool dpaa2_eth_tx_छोड़ो_enabled(u64 link_options)
अणु
	वापस !!(link_options & DPNI_LINK_OPT_PAUSE) ^
	       !!(link_options & DPNI_LINK_OPT_ASYM_PAUSE);
पूर्ण

अटल अंतरभूत bool dpaa2_eth_rx_छोड़ो_enabled(u64 link_options)
अणु
	वापस !!(link_options & DPNI_LINK_OPT_PAUSE);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक dpaa2_eth_needed_headroom(काष्ठा sk_buff *skb)
अणु
	अचिन्हित पूर्णांक headroom = DPAA2_ETH_SWA_SIZE;

	/* If we करोn't have an skb (e.g. XDP buffer), we only need space क्रम
	 * the software annotation area
	 */
	अगर (!skb)
		वापस headroom;

	/* For non-linear skbs we have no headroom requirement, as we build a
	 * SG frame with a newly allocated SGT buffer
	 */
	अगर (skb_is_nonlinear(skb))
		वापस 0;

	/* If we have Tx बारtamping, need 128B hardware annotation */
	अगर (skb->cb[0])
		headroom += DPAA2_ETH_TX_HWA_SIZE;

	वापस headroom;
पूर्ण

/* Extra headroom space requested to hardware, in order to make sure there's
 * no पुनः_स्मृति'ing in क्रमwarding scenarios
 */
अटल अंतरभूत अचिन्हित पूर्णांक dpaa2_eth_rx_head_room(काष्ठा dpaa2_eth_priv *priv)
अणु
	वापस priv->tx_data_offset - DPAA2_ETH_RX_HWA_SIZE;
पूर्ण

अटल अंतरभूत bool dpaa2_eth_is_type_phy(काष्ठा dpaa2_eth_priv *priv)
अणु
	अगर (priv->mac &&
	    (priv->mac->attr.link_type == DPMAC_LINK_TYPE_PHY ||
	     priv->mac->attr.link_type == DPMAC_LINK_TYPE_BACKPLANE))
		वापस true;

	वापस false;
पूर्ण

अटल अंतरभूत bool dpaa2_eth_has_mac(काष्ठा dpaa2_eth_priv *priv)
अणु
	वापस priv->mac ? true : false;
पूर्ण

पूर्णांक dpaa2_eth_set_hash(काष्ठा net_device *net_dev, u64 flags);
पूर्णांक dpaa2_eth_set_cls(काष्ठा net_device *net_dev, u64 key);
पूर्णांक dpaa2_eth_cls_key_size(u64 key);
पूर्णांक dpaa2_eth_cls_fld_off(पूर्णांक prot, पूर्णांक field);
व्योम dpaa2_eth_cls_trim_rule(व्योम *key_mem, u64 fields);

व्योम dpaa2_eth_set_rx_taildrop(काष्ठा dpaa2_eth_priv *priv,
			       bool tx_छोड़ो, bool pfc);

बाह्य स्थिर काष्ठा dcbnl_rtnl_ops dpaa2_eth_dcbnl_ops;

पूर्णांक dpaa2_eth_dl_रेजिस्टर(काष्ठा dpaa2_eth_priv *priv);
व्योम dpaa2_eth_dl_unरेजिस्टर(काष्ठा dpaa2_eth_priv *priv);

पूर्णांक dpaa2_eth_dl_port_add(काष्ठा dpaa2_eth_priv *priv);
व्योम dpaa2_eth_dl_port_del(काष्ठा dpaa2_eth_priv *priv);

पूर्णांक dpaa2_eth_dl_traps_रेजिस्टर(काष्ठा dpaa2_eth_priv *priv);
व्योम dpaa2_eth_dl_traps_unरेजिस्टर(काष्ठा dpaa2_eth_priv *priv);

काष्ठा dpaa2_eth_trap_item *dpaa2_eth_dl_get_trap(काष्ठा dpaa2_eth_priv *priv,
						  काष्ठा dpaa2_fapr *fapr);
#पूर्ण_अगर	/* __DPAA2_H */
