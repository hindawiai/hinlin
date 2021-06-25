<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-2-Clause) */
/* Copyright (C) 2015-2018 Netronome Systems, Inc. */

/*
 * nfp_net.h
 * Declarations क्रम Netronome network device driver.
 * Authors: Jakub Kicinski <jakub.kicinski@netronome.com>
 *          Jason McMullan <jason.mcmullan@netronome.com>
 *          Rolf Neugebauer <rolf.neugebauer@netronome.com>
 */

#अगर_अघोषित _NFP_NET_H_
#घोषणा _NFP_NET_H_

#समावेश <linux/atomic.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/list.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/pci.h>
#समावेश <linux/io-64-nonatomic-hi-lo.h>
#समावेश <linux/semaphore.h>
#समावेश <linux/workqueue.h>
#समावेश <net/xdp.h>

#समावेश "nfp_net_ctrl.h"

#घोषणा nn_pr(nn, lvl, fmt, args...)					\
	(अणु								\
		काष्ठा nfp_net *__nn = (nn);				\
									\
		अगर (__nn->dp.netdev)					\
			netdev_prपूर्णांकk(lvl, __nn->dp.netdev, fmt, ## args); \
		अन्यथा							\
			dev_prपूर्णांकk(lvl, __nn->dp.dev, "ctrl: " fmt, ## args); \
	पूर्ण)

#घोषणा nn_err(nn, fmt, args...)	nn_pr(nn, KERN_ERR, fmt, ## args)
#घोषणा nn_warn(nn, fmt, args...)	nn_pr(nn, KERN_WARNING, fmt, ## args)
#घोषणा nn_info(nn, fmt, args...)	nn_pr(nn, KERN_INFO, fmt, ## args)
#घोषणा nn_dbg(nn, fmt, args...)	nn_pr(nn, KERN_DEBUG, fmt, ## args)

#घोषणा nn_dp_warn(dp, fmt, args...)					\
	(अणु								\
		काष्ठा nfp_net_dp *__dp = (dp);				\
									\
		अगर (unlikely(net_ratelimit())) अणु			\
			अगर (__dp->netdev)				\
				netdev_warn(__dp->netdev, fmt, ## args); \
			अन्यथा						\
				dev_warn(__dp->dev, fmt, ## args);	\
		पूर्ण							\
	पूर्ण)

/* Max समय to रुको क्रम NFP to respond on updates (in seconds) */
#घोषणा NFP_NET_POLL_TIMEOUT	5

/* Interval क्रम पढ़ोing offloaded filter stats */
#घोषणा NFP_NET_STAT_POLL_IVL	msecs_to_jअगरfies(100)

/* Bar allocation */
#घोषणा NFP_NET_CTRL_BAR	0
#घोषणा NFP_NET_Q0_BAR		2
#घोषणा NFP_NET_Q1_BAR		4	/* OBSOLETE */

/* Max bits in DMA address */
#घोषणा NFP_NET_MAX_DMA_BITS	40

/* Default size क्रम MTU and मुक्तlist buffer sizes */
#घोषणा NFP_NET_DEFAULT_MTU		1500U

/* Maximum number of bytes prepended to a packet */
#घोषणा NFP_NET_MAX_PREPEND		64

/* Interrupt definitions */
#घोषणा NFP_NET_NON_Q_VECTORS		2
#घोषणा NFP_NET_IRQ_LSC_IDX		0
#घोषणा NFP_NET_IRQ_EXN_IDX		1
#घोषणा NFP_NET_MIN_VNIC_IRQS		(NFP_NET_NON_Q_VECTORS + 1)

/* Queue/Ring definitions */
#घोषणा NFP_NET_MAX_TX_RINGS	64	/* Max. # of Tx rings per device */
#घोषणा NFP_NET_MAX_RX_RINGS	64	/* Max. # of Rx rings per device */
#घोषणा NFP_NET_MAX_R_VECS	(NFP_NET_MAX_TX_RINGS > NFP_NET_MAX_RX_RINGS ? \
				 NFP_NET_MAX_TX_RINGS : NFP_NET_MAX_RX_RINGS)
#घोषणा NFP_NET_MAX_IRQS	(NFP_NET_NON_Q_VECTORS + NFP_NET_MAX_R_VECS)

#घोषणा NFP_NET_MIN_TX_DESCS	256	/* Min. # of Tx descs per ring */
#घोषणा NFP_NET_MIN_RX_DESCS	256	/* Min. # of Rx descs per ring */
#घोषणा NFP_NET_MAX_TX_DESCS	(256 * 1024) /* Max. # of Tx descs per ring */
#घोषणा NFP_NET_MAX_RX_DESCS	(256 * 1024) /* Max. # of Rx descs per ring */

#घोषणा NFP_NET_TX_DESCS_DEFAULT 4096	/* Default # of Tx descs per ring */
#घोषणा NFP_NET_RX_DESCS_DEFAULT 4096	/* Default # of Rx descs per ring */

#घोषणा NFP_NET_FL_BATCH	16	/* Add मुक्तlist in this Batch size */
#घोषणा NFP_NET_XDP_MAX_COMPLETE 2048	/* XDP bufs to reclaim in NAPI poll */

/* Offload definitions */
#घोषणा NFP_NET_N_VXLAN_PORTS	(NFP_NET_CFG_VXLAN_SZ / माप(__be16))

#घोषणा NFP_NET_RX_BUF_HEADROOM	(NET_SKB_PAD + NET_IP_ALIGN)
#घोषणा NFP_NET_RX_BUF_NON_DATA	(NFP_NET_RX_BUF_HEADROOM +		\
				 SKB_DATA_ALIGN(माप(काष्ठा skb_shared_info)))

/* Forward declarations */
काष्ठा nfp_cpp;
काष्ठा nfp_eth_table_port;
काष्ठा nfp_net;
काष्ठा nfp_net_r_vector;
काष्ठा nfp_port;

/* Convenience macro क्रम wrapping descriptor index on ring size */
#घोषणा D_IDX(ring, idx)	((idx) & ((ring)->cnt - 1))

/* Convenience macro क्रम writing dma address पूर्णांकo RX/TX descriptors */
#घोषणा nfp_desc_set_dma_addr(desc, dma_addr)				\
	करो अणु								\
		__typeof(desc) __d = (desc);				\
		dma_addr_t __addr = (dma_addr);				\
									\
		__d->dma_addr_lo = cpu_to_le32(lower_32_bits(__addr));	\
		__d->dma_addr_hi = upper_32_bits(__addr) & 0xff;	\
	पूर्ण जबतक (0)

/* TX descriptor क्रमmat */

#घोषणा PCIE_DESC_TX_EOP		BIT(7)
#घोषणा PCIE_DESC_TX_OFFSET_MASK	GENMASK(6, 0)
#घोषणा PCIE_DESC_TX_MSS_MASK		GENMASK(13, 0)

/* Flags in the host TX descriptor */
#घोषणा PCIE_DESC_TX_CSUM		BIT(7)
#घोषणा PCIE_DESC_TX_IP4_CSUM		BIT(6)
#घोषणा PCIE_DESC_TX_TCP_CSUM		BIT(5)
#घोषणा PCIE_DESC_TX_UDP_CSUM		BIT(4)
#घोषणा PCIE_DESC_TX_VLAN		BIT(3)
#घोषणा PCIE_DESC_TX_LSO		BIT(2)
#घोषणा PCIE_DESC_TX_ENCAP		BIT(1)
#घोषणा PCIE_DESC_TX_O_IP4_CSUM	BIT(0)

काष्ठा nfp_net_tx_desc अणु
	जोड़ अणु
		काष्ठा अणु
			u8 dma_addr_hi; /* High bits of host buf address */
			__le16 dma_len;	/* Length to DMA क्रम this desc */
			u8 offset_eop;	/* Offset in buf where pkt starts +
					 * highest bit is eop flag.
					 */
			__le32 dma_addr_lo; /* Low 32bit of host buf addr */

			__le16 mss;	/* MSS to be used क्रम LSO */
			u8 lso_hdrlen;	/* LSO, TCP payload offset */
			u8 flags;	/* TX Flags, see @PCIE_DESC_TX_* */
			जोड़ अणु
				काष्ठा अणु
					u8 l3_offset; /* L3 header offset */
					u8 l4_offset; /* L4 header offset */
				पूर्ण;
				__le16 vlan; /* VLAN tag to add अगर indicated */
			पूर्ण;
			__le16 data_len; /* Length of frame + meta data */
		पूर्ण __packed;
		__le32 vals[4];
		__le64 vals8[2];
	पूर्ण;
पूर्ण;

/**
 * काष्ठा nfp_net_tx_buf - software TX buffer descriptor
 * @skb:	normal ring, sk_buff associated with this buffer
 * @frag:	XDP ring, page frag associated with this buffer
 * @dma_addr:	DMA mapping address of the buffer
 * @fidx:	Fragment index (-1 क्रम the head and [0..nr_frags-1] क्रम frags)
 * @pkt_cnt:	Number of packets to be produced out of the skb associated
 *		with this buffer (valid only on the head's buffer).
 *		Will be 1 क्रम all non-TSO packets.
 * @real_len:	Number of bytes which to be produced out of the skb (valid only
 *		on the head's buffer). Equal to skb->len क्रम non-TSO packets.
 */
काष्ठा nfp_net_tx_buf अणु
	जोड़ अणु
		काष्ठा sk_buff *skb;
		व्योम *frag;
	पूर्ण;
	dma_addr_t dma_addr;
	लघु पूर्णांक fidx;
	u16 pkt_cnt;
	u32 real_len;
पूर्ण;

/**
 * काष्ठा nfp_net_tx_ring - TX ring काष्ठाure
 * @r_vec:      Back poपूर्णांकer to ring vector काष्ठाure
 * @idx:        Ring index from Linux's perspective
 * @qcidx:      Queue Controller Peripheral (QCP) queue index क्रम the TX queue
 * @qcp_q:      Poपूर्णांकer to base of the QCP TX queue
 * @cnt:        Size of the queue in number of descriptors
 * @wr_p:       TX ring ग_लिखो poपूर्णांकer (मुक्त running)
 * @rd_p:       TX ring पढ़ो poपूर्णांकer (मुक्त running)
 * @qcp_rd_p:   Local copy of QCP TX queue पढ़ो poपूर्णांकer
 * @wr_ptr_add:	Accumulated number of buffers to add to QCP ग_लिखो poपूर्णांकer
 *		(used क्रम .xmit_more delayed kick)
 * @txbufs:     Array of transmitted TX buffers, to मुक्त on transmit
 * @txds:       Virtual address of TX ring in host memory
 * @dma:        DMA address of the TX ring
 * @size:       Size, in bytes, of the TX ring (needed to मुक्त)
 * @is_xdp:	Is this a XDP TX ring?
 */
काष्ठा nfp_net_tx_ring अणु
	काष्ठा nfp_net_r_vector *r_vec;

	u32 idx;
	पूर्णांक qcidx;
	u8 __iomem *qcp_q;

	u32 cnt;
	u32 wr_p;
	u32 rd_p;
	u32 qcp_rd_p;

	u32 wr_ptr_add;

	काष्ठा nfp_net_tx_buf *txbufs;
	काष्ठा nfp_net_tx_desc *txds;

	dma_addr_t dma;
	माप_प्रकार size;
	bool is_xdp;
पूर्ण ____cacheline_aligned;

/* RX and मुक्तlist descriptor क्रमmat */

#घोषणा PCIE_DESC_RX_DD			BIT(7)
#घोषणा PCIE_DESC_RX_META_LEN_MASK	GENMASK(6, 0)

/* Flags in the RX descriptor */
#घोषणा PCIE_DESC_RX_RSS		cpu_to_le16(BIT(15))
#घोषणा PCIE_DESC_RX_I_IP4_CSUM		cpu_to_le16(BIT(14))
#घोषणा PCIE_DESC_RX_I_IP4_CSUM_OK	cpu_to_le16(BIT(13))
#घोषणा PCIE_DESC_RX_I_TCP_CSUM		cpu_to_le16(BIT(12))
#घोषणा PCIE_DESC_RX_I_TCP_CSUM_OK	cpu_to_le16(BIT(11))
#घोषणा PCIE_DESC_RX_I_UDP_CSUM		cpu_to_le16(BIT(10))
#घोषणा PCIE_DESC_RX_I_UDP_CSUM_OK	cpu_to_le16(BIT(9))
#घोषणा PCIE_DESC_RX_DECRYPTED		cpu_to_le16(BIT(8))
#घोषणा PCIE_DESC_RX_EOP		cpu_to_le16(BIT(7))
#घोषणा PCIE_DESC_RX_IP4_CSUM		cpu_to_le16(BIT(6))
#घोषणा PCIE_DESC_RX_IP4_CSUM_OK	cpu_to_le16(BIT(5))
#घोषणा PCIE_DESC_RX_TCP_CSUM		cpu_to_le16(BIT(4))
#घोषणा PCIE_DESC_RX_TCP_CSUM_OK	cpu_to_le16(BIT(3))
#घोषणा PCIE_DESC_RX_UDP_CSUM		cpu_to_le16(BIT(2))
#घोषणा PCIE_DESC_RX_UDP_CSUM_OK	cpu_to_le16(BIT(1))
#घोषणा PCIE_DESC_RX_VLAN		cpu_to_le16(BIT(0))

#घोषणा PCIE_DESC_RX_CSUM_ALL		(PCIE_DESC_RX_IP4_CSUM |	\
					 PCIE_DESC_RX_TCP_CSUM |	\
					 PCIE_DESC_RX_UDP_CSUM |	\
					 PCIE_DESC_RX_I_IP4_CSUM |	\
					 PCIE_DESC_RX_I_TCP_CSUM |	\
					 PCIE_DESC_RX_I_UDP_CSUM)
#घोषणा PCIE_DESC_RX_CSUM_OK_SHIFT	1
#घोषणा __PCIE_DESC_RX_CSUM_ALL		le16_to_cpu(PCIE_DESC_RX_CSUM_ALL)
#घोषणा __PCIE_DESC_RX_CSUM_ALL_OK	(__PCIE_DESC_RX_CSUM_ALL >>	\
					 PCIE_DESC_RX_CSUM_OK_SHIFT)

काष्ठा nfp_net_rx_desc अणु
	जोड़ अणु
		काष्ठा अणु
			u8 dma_addr_hi;	/* High bits of the buf address */
			__le16 reserved; /* Must be zero */
			u8 meta_len_dd; /* Must be zero */

			__le32 dma_addr_lo; /* Low bits of the buffer address */
		पूर्ण __packed fld;

		काष्ठा अणु
			__le16 data_len; /* Length of the frame + meta data */
			u8 reserved;
			u8 meta_len_dd;	/* Length of meta data prepended +
					 * descriptor करोne flag.
					 */

			__le16 flags;	/* RX flags. See @PCIE_DESC_RX_* */
			__le16 vlan;	/* VLAN अगर stripped */
		पूर्ण __packed rxd;

		__le32 vals[2];
	पूर्ण;
पूर्ण;

#घोषणा NFP_NET_META_FIELD_MASK GENMASK(NFP_NET_META_FIELD_SIZE - 1, 0)

काष्ठा nfp_meta_parsed अणु
	u8 hash_type;
	u8 csum_type;
	u32 hash;
	u32 mark;
	u32 portid;
	__wsum csum;
पूर्ण;

काष्ठा nfp_net_rx_hash अणु
	__be32 hash_type;
	__be32 hash;
पूर्ण;

/**
 * काष्ठा nfp_net_rx_buf - software RX buffer descriptor
 * @frag:	page fragment buffer
 * @dma_addr:	DMA mapping address of the buffer
 */
काष्ठा nfp_net_rx_buf अणु
	व्योम *frag;
	dma_addr_t dma_addr;
पूर्ण;

/**
 * काष्ठा nfp_net_rx_ring - RX ring काष्ठाure
 * @r_vec:      Back poपूर्णांकer to ring vector काष्ठाure
 * @cnt:        Size of the queue in number of descriptors
 * @wr_p:       FL/RX ring ग_लिखो poपूर्णांकer (मुक्त running)
 * @rd_p:       FL/RX ring पढ़ो poपूर्णांकer (मुक्त running)
 * @idx:        Ring index from Linux's perspective
 * @fl_qcidx:   Queue Controller Peripheral (QCP) queue index क्रम the मुक्तlist
 * @qcp_fl:     Poपूर्णांकer to base of the QCP मुक्तlist queue
 * @rxbufs:     Array of transmitted FL/RX buffers
 * @rxds:       Virtual address of FL/RX ring in host memory
 * @xdp_rxq:    RX-ring info avail क्रम XDP
 * @dma:        DMA address of the FL/RX ring
 * @size:       Size, in bytes, of the FL/RX ring (needed to मुक्त)
 */
काष्ठा nfp_net_rx_ring अणु
	काष्ठा nfp_net_r_vector *r_vec;

	u32 cnt;
	u32 wr_p;
	u32 rd_p;

	u32 idx;

	पूर्णांक fl_qcidx;
	u8 __iomem *qcp_fl;

	काष्ठा nfp_net_rx_buf *rxbufs;
	काष्ठा nfp_net_rx_desc *rxds;

	काष्ठा xdp_rxq_info xdp_rxq;

	dma_addr_t dma;
	माप_प्रकार size;
पूर्ण ____cacheline_aligned;

/**
 * काष्ठा nfp_net_r_vector - Per ring पूर्णांकerrupt vector configuration
 * @nfp_net:        Backpoपूर्णांकer to nfp_net काष्ठाure
 * @napi:           NAPI काष्ठाure क्रम this ring vec
 * @tasklet:        ctrl vNIC, tasklet क्रम servicing the r_vec
 * @queue:          ctrl vNIC, send queue
 * @lock:           ctrl vNIC, r_vec lock protects @queue
 * @tx_ring:        Poपूर्णांकer to TX ring
 * @rx_ring:        Poपूर्णांकer to RX ring
 * @xdp_ring:	    Poपूर्णांकer to an extra TX ring क्रम XDP
 * @irq_entry:      MSI-X table entry (use क्रम talking to the device)
 * @rx_sync:	    Seqlock क्रम atomic updates of RX stats
 * @rx_pkts:        Number of received packets
 * @rx_bytes:	    Number of received bytes
 * @rx_drops:	    Number of packets dropped on RX due to lack of resources
 * @hw_csum_rx_ok:  Counter of packets where the HW checksum was OK
 * @hw_csum_rx_inner_ok: Counter of packets where the inner HW checksum was OK
 * @hw_csum_rx_complete: Counter of packets with CHECKSUM_COMPLETE reported
 * @hw_csum_rx_error:	 Counter of packets with bad checksums
 * @hw_tls_rx:	    Number of packets with TLS decrypted by hardware
 * @tx_sync:	    Seqlock क्रम atomic updates of TX stats
 * @tx_pkts:	    Number of Transmitted packets
 * @tx_bytes:	    Number of Transmitted bytes
 * @hw_csum_tx:	    Counter of packets with TX checksum offload requested
 * @hw_csum_tx_inner:	 Counter of inner TX checksum offload requests
 * @tx_gather:	    Counter of packets with Gather DMA
 * @tx_lso:	    Counter of LSO packets sent
 * @hw_tls_tx:	    Counter of TLS packets sent with crypto offloaded to HW
 * @tls_tx_fallback:	Counter of TLS packets sent which had to be encrypted
 *			by the fallback path because packets came out of order
 * @tls_tx_no_fallback:	Counter of TLS packets not sent because the fallback
 *			path could not encrypt them
 * @tx_errors:	    How many TX errors were encountered
 * @tx_busy:        How often was TX busy (no space)?
 * @rx_replace_buf_alloc_fail:	Counter of RX buffer allocation failures
 * @irq_vector:     Interrupt vector number (use क्रम talking to the OS)
 * @handler:        Interrupt handler क्रम this ring vector
 * @name:           Name of the पूर्णांकerrupt vector
 * @affinity_mask:  SMP affinity mask क्रम this vector
 *
 * This काष्ठाure ties RX and TX rings to पूर्णांकerrupt vectors and a NAPI
 * context. This currently only supports one RX and TX ring per
 * पूर्णांकerrupt vector but might be extended in the future to allow
 * association of multiple rings per vector.
 */
काष्ठा nfp_net_r_vector अणु
	काष्ठा nfp_net *nfp_net;
	जोड़ अणु
		काष्ठा napi_काष्ठा napi;
		काष्ठा अणु
			काष्ठा tasklet_काष्ठा tasklet;
			काष्ठा sk_buff_head queue;
			spinlock_t lock;
		पूर्ण;
	पूर्ण;

	काष्ठा nfp_net_tx_ring *tx_ring;
	काष्ठा nfp_net_rx_ring *rx_ring;

	u16 irq_entry;

	काष्ठा u64_stats_sync rx_sync;
	u64 rx_pkts;
	u64 rx_bytes;
	u64 rx_drops;
	u64 hw_csum_rx_ok;
	u64 hw_csum_rx_inner_ok;
	u64 hw_csum_rx_complete;
	u64 hw_tls_rx;

	u64 hw_csum_rx_error;
	u64 rx_replace_buf_alloc_fail;

	काष्ठा nfp_net_tx_ring *xdp_ring;

	काष्ठा u64_stats_sync tx_sync;
	u64 tx_pkts;
	u64 tx_bytes;

	u64 ____cacheline_aligned_in_smp hw_csum_tx;
	u64 hw_csum_tx_inner;
	u64 tx_gather;
	u64 tx_lso;
	u64 hw_tls_tx;

	u64 tls_tx_fallback;
	u64 tls_tx_no_fallback;
	u64 tx_errors;
	u64 tx_busy;

	/* Cold data follows */

	u32 irq_vector;
	irq_handler_t handler;
	अक्षर name[IFNAMSIZ + 8];
	cpumask_t affinity_mask;
पूर्ण ____cacheline_aligned;

/* Firmware version as it is written in the 32bit value in the BAR */
काष्ठा nfp_net_fw_version अणु
	u8 minor;
	u8 major;
	u8 class;
	u8 resv;
पूर्ण __packed;

अटल अंतरभूत bool nfp_net_fw_ver_eq(काष्ठा nfp_net_fw_version *fw_ver,
				     u8 resv, u8 class, u8 major, u8 minor)
अणु
	वापस fw_ver->resv == resv &&
	       fw_ver->class == class &&
	       fw_ver->major == major &&
	       fw_ver->minor == minor;
पूर्ण

काष्ठा nfp_stat_pair अणु
	u64 pkts;
	u64 bytes;
पूर्ण;

/**
 * काष्ठा nfp_net_dp - NFP network device datapath data काष्ठाure
 * @dev:		Backpoपूर्णांकer to काष्ठा device
 * @netdev:		Backpoपूर्णांकer to net_device काष्ठाure
 * @is_vf:		Is the driver attached to a VF?
 * @chained_metadata_क्रमmat:  Firemware will use new metadata क्रमmat
 * @ktls_tx:		Is kTLS TX enabled?
 * @rx_dma_dir:		Mapping direction क्रम RX buffers
 * @rx_dma_off:		Offset at which DMA packets (क्रम XDP headroom)
 * @rx_offset:		Offset in the RX buffers where packet data starts
 * @ctrl:		Local copy of the control रेजिस्टर/word.
 * @fl_bufsz:		Currently configured size of the मुक्तlist buffers
 * @xdp_prog:		Installed XDP program
 * @tx_rings:		Array of pre-allocated TX ring काष्ठाures
 * @rx_rings:		Array of pre-allocated RX ring काष्ठाures
 * @ctrl_bar:		Poपूर्णांकer to mapped control BAR
 *
 * @txd_cnt:		Size of the TX ring in number of descriptors
 * @rxd_cnt:		Size of the RX ring in number of descriptors
 * @num_r_vecs:		Number of used ring vectors
 * @num_tx_rings:	Currently configured number of TX rings
 * @num_stack_tx_rings:	Number of TX rings used by the stack (not XDP)
 * @num_rx_rings:	Currently configured number of RX rings
 * @mtu:		Device MTU
 */
काष्ठा nfp_net_dp अणु
	काष्ठा device *dev;
	काष्ठा net_device *netdev;

	u8 is_vf:1;
	u8 chained_metadata_क्रमmat:1;
	u8 ktls_tx:1;

	u8 rx_dma_dir;
	u8 rx_offset;

	u32 rx_dma_off;

	u32 ctrl;
	u32 fl_bufsz;

	काष्ठा bpf_prog *xdp_prog;

	काष्ठा nfp_net_tx_ring *tx_rings;
	काष्ठा nfp_net_rx_ring *rx_rings;

	u8 __iomem *ctrl_bar;

	/* Cold data follows */

	अचिन्हित पूर्णांक txd_cnt;
	अचिन्हित पूर्णांक rxd_cnt;

	अचिन्हित पूर्णांक num_r_vecs;

	अचिन्हित पूर्णांक num_tx_rings;
	अचिन्हित पूर्णांक num_stack_tx_rings;
	अचिन्हित पूर्णांक num_rx_rings;

	अचिन्हित पूर्णांक mtu;
पूर्ण;

/**
 * काष्ठा nfp_net - NFP network device काष्ठाure
 * @dp:			Datapath काष्ठाure
 * @id:			vNIC id within the PF (0 क्रम VFs)
 * @fw_ver:		Firmware version
 * @cap:                Capabilities advertised by the Firmware
 * @max_mtu:            Maximum support MTU advertised by the Firmware
 * @rss_hfunc:		RSS selected hash function
 * @rss_cfg:            RSS configuration
 * @rss_key:            RSS secret key
 * @rss_itbl:           RSS indirection table
 * @xdp:		Inक्रमmation about the driver XDP program
 * @xdp_hw:		Inक्रमmation about the HW XDP program
 * @max_r_vecs:		Number of allocated पूर्णांकerrupt vectors क्रम RX/TX
 * @max_tx_rings:       Maximum number of TX rings supported by the Firmware
 * @max_rx_rings:       Maximum number of RX rings supported by the Firmware
 * @stride_rx:		Queue controller RX queue spacing
 * @stride_tx:		Queue controller TX queue spacing
 * @r_vecs:             Pre-allocated array of ring vectors
 * @irq_entries:        Pre-allocated array of MSI-X entries
 * @lsc_handler:        Handler क्रम Link State Change पूर्णांकerrupt
 * @lsc_name:           Name क्रम Link State Change पूर्णांकerrupt
 * @exn_handler:        Handler क्रम Exception पूर्णांकerrupt
 * @exn_name:           Name क्रम Exception पूर्णांकerrupt
 * @shared_handler:     Handler क्रम shared पूर्णांकerrupts
 * @shared_name:        Name क्रम shared पूर्णांकerrupt
 * @me_freq_mhz:        ME घड़ी_freq (MHz)
 * @reconfig_lock:	Protects @reconfig_posted, @reconfig_समयr_active,
 *			@reconfig_sync_present and HW reconfiguration request
 *			regs/machinery from async requests (sync must take
 *			@bar_lock)
 * @reconfig_posted:	Pending reconfig bits coming from async sources
 * @reconfig_समयr_active:  Timer क्रम पढ़ोing reconfiguration results is pending
 * @reconfig_sync_present:  Some thपढ़ो is perक्रमming synchronous reconfig
 * @reconfig_समयr:	Timer क्रम async पढ़ोing of reconfig results
 * @reconfig_in_progress_update:	Update FW is processing now (debug only)
 * @bar_lock:		vNIC config BAR access lock, protects: update,
 *			mailbox area, crypto TLV
 * @link_up:            Is the link up?
 * @link_status_lock:	Protects @link_* and ensures atomicity with BAR पढ़ोing
 * @rx_coalesce_usecs:      RX पूर्णांकerrupt moderation usecs delay parameter
 * @rx_coalesce_max_frames: RX पूर्णांकerrupt moderation frame count parameter
 * @tx_coalesce_usecs:      TX पूर्णांकerrupt moderation usecs delay parameter
 * @tx_coalesce_max_frames: TX पूर्णांकerrupt moderation frame count parameter
 * @qcp_cfg:            Poपूर्णांकer to QCP queue used क्रम configuration notअगरication
 * @tx_bar:             Poपूर्णांकer to mapped TX queues
 * @rx_bar:             Poपूर्णांकer to mapped FL/RX queues
 * @tlv_caps:		Parsed TLV capabilities
 * @ktls_tx_conn_cnt:	Number of offloaded kTLS TX connections
 * @ktls_rx_conn_cnt:	Number of offloaded kTLS RX connections
 * @ktls_conn_id_gen:	Trivial generator क्रम kTLS connection ids (क्रम TX)
 * @ktls_no_space:	Counter of firmware rejecting kTLS connection due to
 *			lack of space
 * @ktls_rx_resync_req:	Counter of TLS RX resync requested
 * @ktls_rx_resync_ign:	Counter of TLS RX resync requests ignored
 * @ktls_rx_resync_sent:    Counter of TLS RX resync completed
 * @mbox_cmsg:		Common Control Message via vNIC mailbox state
 * @mbox_cmsg.queue:	CCM mbox queue of pending messages
 * @mbox_cmsg.wq:	CCM mbox रुको queue of रुकोing processes
 * @mbox_cmsg.workq:	CCM mbox work queue क्रम @रुको_work and @runq_work
 * @mbox_cmsg.रुको_work:    CCM mbox posted msg reconfig रुको work
 * @mbox_cmsg.runq_work:    CCM mbox posted msg queue runner work
 * @mbox_cmsg.tag:	CCM mbox message tag allocator
 * @debugfs_dir:	Device directory in debugfs
 * @vnic_list:		Entry on device vNIC list
 * @pdev:		Backpoपूर्णांकer to PCI device
 * @app:		APP handle अगर available
 * @vnic_no_name:	For non-port PF vNIC make nकरो_get_phys_port_name वापस
 *			-EOPNOTSUPP to keep backwards compatibility (set by app)
 * @port:		Poपूर्णांकer to nfp_port काष्ठाure अगर vNIC is a port
 * @app_priv:		APP निजी data क्रम this vNIC
 */
काष्ठा nfp_net अणु
	काष्ठा nfp_net_dp dp;

	काष्ठा nfp_net_fw_version fw_ver;

	u32 id;

	u32 cap;
	u32 max_mtu;

	u8 rss_hfunc;
	u32 rss_cfg;
	u8 rss_key[NFP_NET_CFG_RSS_KEY_SZ];
	u8 rss_itbl[NFP_NET_CFG_RSS_ITBL_SZ];

	काष्ठा xdp_attachment_info xdp;
	काष्ठा xdp_attachment_info xdp_hw;

	अचिन्हित पूर्णांक max_tx_rings;
	अचिन्हित पूर्णांक max_rx_rings;

	पूर्णांक stride_tx;
	पूर्णांक stride_rx;

	अचिन्हित पूर्णांक max_r_vecs;
	काष्ठा nfp_net_r_vector r_vecs[NFP_NET_MAX_R_VECS];
	काष्ठा msix_entry irq_entries[NFP_NET_MAX_IRQS];

	irq_handler_t lsc_handler;
	अक्षर lsc_name[IFNAMSIZ + 8];

	irq_handler_t exn_handler;
	अक्षर exn_name[IFNAMSIZ + 8];

	irq_handler_t shared_handler;
	अक्षर shared_name[IFNAMSIZ + 8];

	u32 me_freq_mhz;

	bool link_up;
	spinlock_t link_status_lock;

	spinlock_t reconfig_lock;
	u32 reconfig_posted;
	bool reconfig_समयr_active;
	bool reconfig_sync_present;
	काष्ठा समयr_list reconfig_समयr;
	u32 reconfig_in_progress_update;

	काष्ठा semaphore bar_lock;

	u32 rx_coalesce_usecs;
	u32 rx_coalesce_max_frames;
	u32 tx_coalesce_usecs;
	u32 tx_coalesce_max_frames;

	u8 __iomem *qcp_cfg;

	u8 __iomem *tx_bar;
	u8 __iomem *rx_bar;

	काष्ठा nfp_net_tlv_caps tlv_caps;

	अचिन्हित पूर्णांक ktls_tx_conn_cnt;
	अचिन्हित पूर्णांक ktls_rx_conn_cnt;

	atomic64_t ktls_conn_id_gen;

	atomic_t ktls_no_space;
	atomic_t ktls_rx_resync_req;
	atomic_t ktls_rx_resync_ign;
	atomic_t ktls_rx_resync_sent;

	काष्ठा अणु
		काष्ठा sk_buff_head queue;
		रुको_queue_head_t wq;
		काष्ठा workqueue_काष्ठा *workq;
		काष्ठा work_काष्ठा रुको_work;
		काष्ठा work_काष्ठा runq_work;
		u16 tag;
	पूर्ण mbox_cmsg;

	काष्ठा dentry *debugfs_dir;

	काष्ठा list_head vnic_list;

	काष्ठा pci_dev *pdev;
	काष्ठा nfp_app *app;

	bool vnic_no_name;

	काष्ठा nfp_port *port;

	व्योम *app_priv;
पूर्ण;

/* Functions to पढ़ो/ग_लिखो from/to a BAR
 * Perक्रमms any endian conversion necessary.
 */
अटल अंतरभूत u16 nn_पढ़ोb(काष्ठा nfp_net *nn, पूर्णांक off)
अणु
	वापस पढ़ोb(nn->dp.ctrl_bar + off);
पूर्ण

अटल अंतरभूत व्योम nn_ग_लिखोb(काष्ठा nfp_net *nn, पूर्णांक off, u8 val)
अणु
	ग_लिखोb(val, nn->dp.ctrl_bar + off);
पूर्ण

अटल अंतरभूत u16 nn_पढ़ोw(काष्ठा nfp_net *nn, पूर्णांक off)
अणु
	वापस पढ़ोw(nn->dp.ctrl_bar + off);
पूर्ण

अटल अंतरभूत व्योम nn_ग_लिखोw(काष्ठा nfp_net *nn, पूर्णांक off, u16 val)
अणु
	ग_लिखोw(val, nn->dp.ctrl_bar + off);
पूर्ण

अटल अंतरभूत u32 nn_पढ़ोl(काष्ठा nfp_net *nn, पूर्णांक off)
अणु
	वापस पढ़ोl(nn->dp.ctrl_bar + off);
पूर्ण

अटल अंतरभूत व्योम nn_ग_लिखोl(काष्ठा nfp_net *nn, पूर्णांक off, u32 val)
अणु
	ग_लिखोl(val, nn->dp.ctrl_bar + off);
पूर्ण

अटल अंतरभूत u64 nn_पढ़ोq(काष्ठा nfp_net *nn, पूर्णांक off)
अणु
	वापस पढ़ोq(nn->dp.ctrl_bar + off);
पूर्ण

अटल अंतरभूत व्योम nn_ग_लिखोq(काष्ठा nfp_net *nn, पूर्णांक off, u64 val)
अणु
	ग_लिखोq(val, nn->dp.ctrl_bar + off);
पूर्ण

/* Flush posted PCI ग_लिखोs by पढ़ोing something without side effects */
अटल अंतरभूत व्योम nn_pci_flush(काष्ठा nfp_net *nn)
अणु
	nn_पढ़ोl(nn, NFP_NET_CFG_VERSION);
पूर्ण

/* Queue Controller Peripheral access functions and definitions.
 *
 * Some of the BARs of the NFP are mapped to portions of the Queue
 * Controller Peripheral (QCP) address space on the NFP.  A QCP queue
 * has a पढ़ो and a ग_लिखो poपूर्णांकer (as well as a size and flags,
 * indicating overflow etc).  The QCP offers a number of dअगरferent
 * operation on queue poपूर्णांकers, but here we only offer function to
 * either add to a poपूर्णांकer or to पढ़ो the poपूर्णांकer value.
 */
#घोषणा NFP_QCP_QUEUE_ADDR_SZ			0x800
#घोषणा NFP_QCP_QUEUE_AREA_SZ			0x80000
#घोषणा NFP_QCP_QUEUE_OFF(_x)			((_x) * NFP_QCP_QUEUE_ADDR_SZ)
#घोषणा NFP_QCP_QUEUE_ADD_RPTR			0x0000
#घोषणा NFP_QCP_QUEUE_ADD_WPTR			0x0004
#घोषणा NFP_QCP_QUEUE_STS_LO			0x0008
#घोषणा NFP_QCP_QUEUE_STS_LO_READPTR_mask	0x3ffff
#घोषणा NFP_QCP_QUEUE_STS_HI			0x000c
#घोषणा NFP_QCP_QUEUE_STS_HI_WRITEPTR_mask	0x3ffff

/* The offset of a QCP queues in the PCIe Target */
#घोषणा NFP_PCIE_QUEUE(_q) (0x80000 + (NFP_QCP_QUEUE_ADDR_SZ * ((_q) & 0xff)))

/* nfp_qcp_ptr - Read or Write Poपूर्णांकer of a queue */
क्रमागत nfp_qcp_ptr अणु
	NFP_QCP_READ_PTR = 0,
	NFP_QCP_WRITE_PTR
पूर्ण;

/* There appear to be an *unकरोcumented* upper limit on the value which
 * one can add to a queue and that value is either 0x3f or 0x7f.  We
 * go with 0x3f as a conservative measure.
 */
#घोषणा NFP_QCP_MAX_ADD				0x3f

अटल अंतरभूत व्योम _nfp_qcp_ptr_add(u8 __iomem *q,
				    क्रमागत nfp_qcp_ptr ptr, u32 val)
अणु
	u32 off;

	अगर (ptr == NFP_QCP_READ_PTR)
		off = NFP_QCP_QUEUE_ADD_RPTR;
	अन्यथा
		off = NFP_QCP_QUEUE_ADD_WPTR;

	जबतक (val > NFP_QCP_MAX_ADD) अणु
		ग_लिखोl(NFP_QCP_MAX_ADD, q + off);
		val -= NFP_QCP_MAX_ADD;
	पूर्ण

	ग_लिखोl(val, q + off);
पूर्ण

/**
 * nfp_qcp_rd_ptr_add() - Add the value to the पढ़ो poपूर्णांकer of a queue
 *
 * @q:   Base address क्रम queue काष्ठाure
 * @val: Value to add to the queue poपूर्णांकer
 *
 * If @val is greater than @NFP_QCP_MAX_ADD multiple ग_लिखोs are perक्रमmed.
 */
अटल अंतरभूत व्योम nfp_qcp_rd_ptr_add(u8 __iomem *q, u32 val)
अणु
	_nfp_qcp_ptr_add(q, NFP_QCP_READ_PTR, val);
पूर्ण

/**
 * nfp_qcp_wr_ptr_add() - Add the value to the ग_लिखो poपूर्णांकer of a queue
 *
 * @q:   Base address क्रम queue काष्ठाure
 * @val: Value to add to the queue poपूर्णांकer
 *
 * If @val is greater than @NFP_QCP_MAX_ADD multiple ग_लिखोs are perक्रमmed.
 */
अटल अंतरभूत व्योम nfp_qcp_wr_ptr_add(u8 __iomem *q, u32 val)
अणु
	_nfp_qcp_ptr_add(q, NFP_QCP_WRITE_PTR, val);
पूर्ण

अटल अंतरभूत u32 _nfp_qcp_पढ़ो(u8 __iomem *q, क्रमागत nfp_qcp_ptr ptr)
अणु
	u32 off;
	u32 val;

	अगर (ptr == NFP_QCP_READ_PTR)
		off = NFP_QCP_QUEUE_STS_LO;
	अन्यथा
		off = NFP_QCP_QUEUE_STS_HI;

	val = पढ़ोl(q + off);

	अगर (ptr == NFP_QCP_READ_PTR)
		वापस val & NFP_QCP_QUEUE_STS_LO_READPTR_mask;
	अन्यथा
		वापस val & NFP_QCP_QUEUE_STS_HI_WRITEPTR_mask;
पूर्ण

/**
 * nfp_qcp_rd_ptr_पढ़ो() - Read the current पढ़ो poपूर्णांकer value क्रम a queue
 * @q:  Base address क्रम queue काष्ठाure
 *
 * Return: Value पढ़ो.
 */
अटल अंतरभूत u32 nfp_qcp_rd_ptr_पढ़ो(u8 __iomem *q)
अणु
	वापस _nfp_qcp_पढ़ो(q, NFP_QCP_READ_PTR);
पूर्ण

/**
 * nfp_qcp_wr_ptr_पढ़ो() - Read the current ग_लिखो poपूर्णांकer value क्रम a queue
 * @q:  Base address क्रम queue काष्ठाure
 *
 * Return: Value पढ़ो.
 */
अटल अंतरभूत u32 nfp_qcp_wr_ptr_पढ़ो(u8 __iomem *q)
अणु
	वापस _nfp_qcp_पढ़ो(q, NFP_QCP_WRITE_PTR);
पूर्ण

अटल अंतरभूत bool nfp_net_is_data_vnic(काष्ठा nfp_net *nn)
अणु
	WARN_ON_ONCE(!nn->dp.netdev && nn->port);
	वापस !!nn->dp.netdev;
पूर्ण

अटल अंतरभूत bool nfp_net_running(काष्ठा nfp_net *nn)
अणु
	वापस nn->dp.ctrl & NFP_NET_CFG_CTRL_ENABLE;
पूर्ण

अटल अंतरभूत स्थिर अक्षर *nfp_net_name(काष्ठा nfp_net *nn)
अणु
	वापस nn->dp.netdev ? nn->dp.netdev->name : "ctrl";
पूर्ण

अटल अंतरभूत व्योम nfp_ctrl_lock(काष्ठा nfp_net *nn)
	__acquires(&nn->r_vecs[0].lock)
अणु
	spin_lock_bh(&nn->r_vecs[0].lock);
पूर्ण

अटल अंतरभूत व्योम nfp_ctrl_unlock(काष्ठा nfp_net *nn)
	__releases(&nn->r_vecs[0].lock)
अणु
	spin_unlock_bh(&nn->r_vecs[0].lock);
पूर्ण

अटल अंतरभूत व्योम nn_ctrl_bar_lock(काष्ठा nfp_net *nn)
अणु
	करोwn(&nn->bar_lock);
पूर्ण

अटल अंतरभूत bool nn_ctrl_bar_trylock(काष्ठा nfp_net *nn)
अणु
	वापस !करोwn_trylock(&nn->bar_lock);
पूर्ण

अटल अंतरभूत व्योम nn_ctrl_bar_unlock(काष्ठा nfp_net *nn)
अणु
	up(&nn->bar_lock);
पूर्ण

/* Globals */
बाह्य स्थिर अक्षर nfp_driver_version[];

बाह्य स्थिर काष्ठा net_device_ops nfp_net_netdev_ops;

अटल अंतरभूत bool nfp_netdev_is_nfp_net(काष्ठा net_device *netdev)
अणु
	वापस netdev->netdev_ops == &nfp_net_netdev_ops;
पूर्ण

/* Prototypes */
व्योम nfp_net_get_fw_version(काष्ठा nfp_net_fw_version *fw_ver,
			    व्योम __iomem *ctrl_bar);

काष्ठा nfp_net *
nfp_net_alloc(काष्ठा pci_dev *pdev, व्योम __iomem *ctrl_bar, bool needs_netdev,
	      अचिन्हित पूर्णांक max_tx_rings, अचिन्हित पूर्णांक max_rx_rings);
व्योम nfp_net_मुक्त(काष्ठा nfp_net *nn);

पूर्णांक nfp_net_init(काष्ठा nfp_net *nn);
व्योम nfp_net_clean(काष्ठा nfp_net *nn);

पूर्णांक nfp_ctrl_खोलो(काष्ठा nfp_net *nn);
व्योम nfp_ctrl_बंद(काष्ठा nfp_net *nn);

व्योम nfp_net_set_ethtool_ops(काष्ठा net_device *netdev);
व्योम nfp_net_info(काष्ठा nfp_net *nn);
पूर्णांक __nfp_net_reconfig(काष्ठा nfp_net *nn, u32 update);
पूर्णांक nfp_net_reconfig(काष्ठा nfp_net *nn, u32 update);
अचिन्हित पूर्णांक nfp_net_rss_key_sz(काष्ठा nfp_net *nn);
व्योम nfp_net_rss_ग_लिखो_itbl(काष्ठा nfp_net *nn);
व्योम nfp_net_rss_ग_लिखो_key(काष्ठा nfp_net *nn);
व्योम nfp_net_coalesce_ग_लिखो_cfg(काष्ठा nfp_net *nn);
पूर्णांक nfp_net_mbox_lock(काष्ठा nfp_net *nn, अचिन्हित पूर्णांक data_size);
पूर्णांक nfp_net_mbox_reconfig(काष्ठा nfp_net *nn, u32 mbox_cmd);
पूर्णांक nfp_net_mbox_reconfig_and_unlock(काष्ठा nfp_net *nn, u32 mbox_cmd);
व्योम nfp_net_mbox_reconfig_post(काष्ठा nfp_net *nn, u32 update);
पूर्णांक nfp_net_mbox_reconfig_रुको_posted(काष्ठा nfp_net *nn);

अचिन्हित पूर्णांक
nfp_net_irqs_alloc(काष्ठा pci_dev *pdev, काष्ठा msix_entry *irq_entries,
		   अचिन्हित पूर्णांक min_irqs, अचिन्हित पूर्णांक want_irqs);
व्योम nfp_net_irqs_disable(काष्ठा pci_dev *pdev);
व्योम
nfp_net_irqs_assign(काष्ठा nfp_net *nn, काष्ठा msix_entry *irq_entries,
		    अचिन्हित पूर्णांक n);

काष्ठा nfp_net_dp *nfp_net_clone_dp(काष्ठा nfp_net *nn);
पूर्णांक nfp_net_ring_reconfig(काष्ठा nfp_net *nn, काष्ठा nfp_net_dp *new,
			  काष्ठा netlink_ext_ack *extack);

#अगर_घोषित CONFIG_NFP_DEBUG
व्योम nfp_net_debugfs_create(व्योम);
व्योम nfp_net_debugfs_destroy(व्योम);
काष्ठा dentry *nfp_net_debugfs_device_add(काष्ठा pci_dev *pdev);
व्योम nfp_net_debugfs_vnic_add(काष्ठा nfp_net *nn, काष्ठा dentry *ddir);
व्योम nfp_net_debugfs_dir_clean(काष्ठा dentry **dir);
#अन्यथा
अटल अंतरभूत व्योम nfp_net_debugfs_create(व्योम)
अणु
पूर्ण

अटल अंतरभूत व्योम nfp_net_debugfs_destroy(व्योम)
अणु
पूर्ण

अटल अंतरभूत काष्ठा dentry *nfp_net_debugfs_device_add(काष्ठा pci_dev *pdev)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम
nfp_net_debugfs_vnic_add(काष्ठा nfp_net *nn, काष्ठा dentry *ddir)
अणु
पूर्ण

अटल अंतरभूत व्योम nfp_net_debugfs_dir_clean(काष्ठा dentry **dir)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_NFP_DEBUG */

#पूर्ण_अगर /* _NFP_NET_H_ */
