<शैली गुरु>
/* Synopsys DesignWare Core Enterprise Ethernet (XLGMAC) Driver
 *
 * Copyright (c) 2017 Synopsys, Inc. (www.synopsys.com)
 *
 * This program is dual-licensed; you may select either version 2 of
 * the GNU General Public License ("GPL") or BSD license ("BSD").
 *
 * This Synopsys DWC XLGMAC software driver and associated करोcumentation
 * (hereinafter the "Software") is an unsupported proprietary work of
 * Synopsys, Inc. unless otherwise expressly agreed to in writing between
 * Synopsys and you. The Software IS NOT an item of Licensed Software or a
 * Licensed Product under any End User Software License Agreement or
 * Agreement क्रम Licensed Products with Synopsys or any supplement thereto.
 * Synopsys is a रेजिस्टरed trademark of Synopsys, Inc. Other names included
 * in the SOFTWARE may be the trademarks of their respective owners.
 */

#अगर_अघोषित __DWC_XLGMAC_H__
#घोषणा __DWC_XLGMAC_H__

#समावेश <linux/dma-mapping.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/phy.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/bitops.h>
#समावेश <linux/समयcounter.h>

#घोषणा XLGMAC_DRV_NAME			"dwc-xlgmac"
#घोषणा XLGMAC_DRV_VERSION		"1.0.0"
#घोषणा XLGMAC_DRV_DESC			"Synopsys DWC XLGMAC Driver"

/* Descriptor related parameters */
#घोषणा XLGMAC_TX_DESC_CNT		1024
#घोषणा XLGMAC_TX_DESC_MIN_FREE		(XLGMAC_TX_DESC_CNT >> 3)
#घोषणा XLGMAC_TX_DESC_MAX_PROC		(XLGMAC_TX_DESC_CNT >> 1)
#घोषणा XLGMAC_RX_DESC_CNT		1024
#घोषणा XLGMAC_RX_DESC_MAX_सूचीTY	(XLGMAC_RX_DESC_CNT >> 3)

/* Descriptors required क्रम maximum contiguous TSO/GSO packet */
#घोषणा XLGMAC_TX_MAX_SPLIT	((GSO_MAX_SIZE / XLGMAC_TX_MAX_BUF_SIZE) + 1)

/* Maximum possible descriptors needed क्रम a SKB */
#घोषणा XLGMAC_TX_MAX_DESC_NR	(MAX_SKB_FRAGS + XLGMAC_TX_MAX_SPLIT + 2)

#घोषणा XLGMAC_TX_MAX_BUF_SIZE	(0x3fff & ~(64 - 1))
#घोषणा XLGMAC_RX_MIN_BUF_SIZE	(ETH_FRAME_LEN + ETH_FCS_LEN + VLAN_HLEN)
#घोषणा XLGMAC_RX_BUF_ALIGN	64

/* Maximum Size क्रम Splitting the Header Data
 * Keep in sync with SKB_ALLOC_SIZE
 * 3'b000: 64 bytes, 3'b001: 128 bytes
 * 3'b010: 256 bytes, 3'b011: 512 bytes
 * 3'b100: 1023 bytes ,   3'b101'3'b111: Reserved
 */
#घोषणा XLGMAC_SPH_HDSMS_SIZE		3
#घोषणा XLGMAC_SKB_ALLOC_SIZE		512

#घोषणा XLGMAC_MAX_FIFO			81920

#घोषणा XLGMAC_MAX_DMA_CHANNELS		16
#घोषणा XLGMAC_DMA_STOP_TIMEOUT		5
#घोषणा XLGMAC_DMA_INTERRUPT_MASK	0x31c7

/* Default coalescing parameters */
#घोषणा XLGMAC_INIT_DMA_TX_USECS	1000
#घोषणा XLGMAC_INIT_DMA_TX_FRAMES	25
#घोषणा XLGMAC_INIT_DMA_RX_USECS	30
#घोषणा XLGMAC_INIT_DMA_RX_FRAMES	25
#घोषणा XLGMAC_MAX_DMA_RIWT		0xff
#घोषणा XLGMAC_MIN_DMA_RIWT		0x01

/* Flow control queue count */
#घोषणा XLGMAC_MAX_FLOW_CONTROL_QUEUES	8

/* System घड़ी is 125 MHz */
#घोषणा XLGMAC_SYSCLOCK			125000000

/* Maximum MAC address hash table size (256 bits = 8 bytes) */
#घोषणा XLGMAC_MAC_HASH_TABLE_SIZE	8

/* Receive Side Scaling */
#घोषणा XLGMAC_RSS_HASH_KEY_SIZE	40
#घोषणा XLGMAC_RSS_MAX_TABLE_SIZE	256
#घोषणा XLGMAC_RSS_LOOKUP_TABLE_TYPE	0
#घोषणा XLGMAC_RSS_HASH_KEY_TYPE	1

#घोषणा XLGMAC_STD_PACKET_MTU		1500
#घोषणा XLGMAC_JUMBO_PACKET_MTU		9000

/* Helper macro क्रम descriptor handling
 *  Always use XLGMAC_GET_DESC_DATA to access the descriptor data
 */
#घोषणा XLGMAC_GET_DESC_DATA(ring, idx) (अणु				\
	typeof(ring) _ring = (ring);					\
	((_ring)->desc_data_head +					\
	 ((idx) & ((_ring)->dma_desc_count - 1)));			\
पूर्ण)

#घोषणा XLGMAC_GET_REG_BITS(var, pos, len) (अणु				\
	typeof(pos) _pos = (pos);					\
	typeof(len) _len = (len);					\
	((var) & GENMASK(_pos + _len - 1, _pos)) >> (_pos);		\
पूर्ण)

#घोषणा XLGMAC_GET_REG_BITS_LE(var, pos, len) (अणु			\
	typeof(pos) _pos = (pos);					\
	typeof(len) _len = (len);					\
	typeof(var) _var = le32_to_cpu((var));				\
	((_var) & GENMASK(_pos + _len - 1, _pos)) >> (_pos);		\
पूर्ण)

#घोषणा XLGMAC_SET_REG_BITS(var, pos, len, val) (अणु			\
	typeof(var) _var = (var);					\
	typeof(pos) _pos = (pos);					\
	typeof(len) _len = (len);					\
	typeof(val) _val = (val);					\
	_val = (_val << _pos) & GENMASK(_pos + _len - 1, _pos);		\
	_var = (_var & ~GENMASK(_pos + _len - 1, _pos)) | _val;		\
पूर्ण)

#घोषणा XLGMAC_SET_REG_BITS_LE(var, pos, len, val) (अणु			\
	typeof(var) _var = (var);					\
	typeof(pos) _pos = (pos);					\
	typeof(len) _len = (len);					\
	typeof(val) _val = (val);					\
	_val = (_val << _pos) & GENMASK(_pos + _len - 1, _pos);		\
	_var = (_var & ~GENMASK(_pos + _len - 1, _pos)) | _val;		\
	cpu_to_le32(_var);						\
पूर्ण)

काष्ठा xlgmac_pdata;

क्रमागत xlgmac_पूर्णांक अणु
	XLGMAC_INT_DMA_CH_SR_TI,
	XLGMAC_INT_DMA_CH_SR_TPS,
	XLGMAC_INT_DMA_CH_SR_TBU,
	XLGMAC_INT_DMA_CH_SR_RI,
	XLGMAC_INT_DMA_CH_SR_RBU,
	XLGMAC_INT_DMA_CH_SR_RPS,
	XLGMAC_INT_DMA_CH_SR_TI_RI,
	XLGMAC_INT_DMA_CH_SR_FBE,
	XLGMAC_INT_DMA_ALL,
पूर्ण;

काष्ठा xlgmac_stats अणु
	/* MMC TX counters */
	u64 txoctetcount_gb;
	u64 txframecount_gb;
	u64 txbroadcastframes_g;
	u64 txmulticastframes_g;
	u64 tx64octets_gb;
	u64 tx65to127octets_gb;
	u64 tx128to255octets_gb;
	u64 tx256to511octets_gb;
	u64 tx512to1023octets_gb;
	u64 tx1024tomaxoctets_gb;
	u64 txunicastframes_gb;
	u64 txmulticastframes_gb;
	u64 txbroadcastframes_gb;
	u64 txunderflowerror;
	u64 txoctetcount_g;
	u64 txframecount_g;
	u64 txछोड़ोframes;
	u64 txvlanframes_g;

	/* MMC RX counters */
	u64 rxframecount_gb;
	u64 rxoctetcount_gb;
	u64 rxoctetcount_g;
	u64 rxbroadcastframes_g;
	u64 rxmulticastframes_g;
	u64 rxcrcerror;
	u64 rxrunterror;
	u64 rxjabbererror;
	u64 rxundersize_g;
	u64 rxoversize_g;
	u64 rx64octets_gb;
	u64 rx65to127octets_gb;
	u64 rx128to255octets_gb;
	u64 rx256to511octets_gb;
	u64 rx512to1023octets_gb;
	u64 rx1024tomaxoctets_gb;
	u64 rxunicastframes_g;
	u64 rxlengtherror;
	u64 rxoutofrangetype;
	u64 rxछोड़ोframes;
	u64 rxfअगरooverflow;
	u64 rxvlanframes_gb;
	u64 rxwatchकरोgerror;

	/* Extra counters */
	u64 tx_tso_packets;
	u64 rx_split_header_packets;
	u64 tx_process_stopped;
	u64 rx_process_stopped;
	u64 tx_buffer_unavailable;
	u64 rx_buffer_unavailable;
	u64 fatal_bus_error;
	u64 tx_vlan_packets;
	u64 rx_vlan_packets;
	u64 napi_poll_isr;
	u64 napi_poll_txसमयr;
पूर्ण;

काष्ठा xlgmac_ring_buf अणु
	काष्ठा sk_buff *skb;
	dma_addr_t skb_dma;
	अचिन्हित पूर्णांक skb_len;
पूर्ण;

/* Common Tx and Rx DMA hardware descriptor */
काष्ठा xlgmac_dma_desc अणु
	__le32 desc0;
	__le32 desc1;
	__le32 desc2;
	__le32 desc3;
पूर्ण;

/* Page allocation related values */
काष्ठा xlgmac_page_alloc अणु
	काष्ठा page *pages;
	अचिन्हित पूर्णांक pages_len;
	अचिन्हित पूर्णांक pages_offset;

	dma_addr_t pages_dma;
पूर्ण;

/* Ring entry buffer data */
काष्ठा xlgmac_buffer_data अणु
	काष्ठा xlgmac_page_alloc pa;
	काष्ठा xlgmac_page_alloc pa_unmap;

	dma_addr_t dma_base;
	अचिन्हित दीर्घ dma_off;
	अचिन्हित पूर्णांक dma_len;
पूर्ण;

/* Tx-related desc data */
काष्ठा xlgmac_tx_desc_data अणु
	अचिन्हित पूर्णांक packets;		/* BQL packet count */
	अचिन्हित पूर्णांक bytes;		/* BQL byte count */
पूर्ण;

/* Rx-related desc data */
काष्ठा xlgmac_rx_desc_data अणु
	काष्ठा xlgmac_buffer_data hdr;	/* Header locations */
	काष्ठा xlgmac_buffer_data buf;	/* Payload locations */

	अचिन्हित लघु hdr_len;		/* Length of received header */
	अचिन्हित लघु len;		/* Length of received packet */
पूर्ण;

काष्ठा xlgmac_pkt_info अणु
	काष्ठा sk_buff *skb;

	अचिन्हित पूर्णांक attributes;

	अचिन्हित पूर्णांक errors;

	/* descriptors needed क्रम this packet */
	अचिन्हित पूर्णांक desc_count;
	अचिन्हित पूर्णांक length;

	अचिन्हित पूर्णांक tx_packets;
	अचिन्हित पूर्णांक tx_bytes;

	अचिन्हित पूर्णांक header_len;
	अचिन्हित पूर्णांक tcp_header_len;
	अचिन्हित पूर्णांक tcp_payload_len;
	अचिन्हित लघु mss;

	अचिन्हित लघु vlan_ctag;

	u64 rx_tstamp;

	u32 rss_hash;
	क्रमागत pkt_hash_types rss_hash_type;
पूर्ण;

काष्ठा xlgmac_desc_data अणु
	/* dma_desc: Virtual address of descriptor
	 *  dma_desc_addr: DMA address of descriptor
	 */
	काष्ठा xlgmac_dma_desc *dma_desc;
	dma_addr_t dma_desc_addr;

	/* skb: Virtual address of SKB
	 *  skb_dma: DMA address of SKB data
	 *  skb_dma_len: Length of SKB DMA area
	 */
	काष्ठा sk_buff *skb;
	dma_addr_t skb_dma;
	अचिन्हित पूर्णांक skb_dma_len;

	/* Tx/Rx -related data */
	काष्ठा xlgmac_tx_desc_data tx;
	काष्ठा xlgmac_rx_desc_data rx;

	अचिन्हित पूर्णांक mapped_as_page;

	/* Incomplete receive save location.  If the budget is exhausted
	 * or the last descriptor (last normal descriptor or a following
	 * context descriptor) has not been DMA'd yet the current state
	 * of the receive processing needs to be saved.
	 */
	अचिन्हित पूर्णांक state_saved;
	काष्ठा अणु
		काष्ठा sk_buff *skb;
		अचिन्हित पूर्णांक len;
		अचिन्हित पूर्णांक error;
	पूर्ण state;
पूर्ण;

काष्ठा xlgmac_ring अणु
	/* Per packet related inक्रमmation */
	काष्ठा xlgmac_pkt_info pkt_info;

	/* Virtual/DMA addresses of DMA descriptor list and the total count */
	काष्ठा xlgmac_dma_desc *dma_desc_head;
	dma_addr_t dma_desc_head_addr;
	अचिन्हित पूर्णांक dma_desc_count;

	/* Array of descriptor data corresponding the DMA descriptor
	 * (always use the XLGMAC_GET_DESC_DATA macro to access this data)
	 */
	काष्ठा xlgmac_desc_data *desc_data_head;

	/* Page allocation क्रम RX buffers */
	काष्ठा xlgmac_page_alloc rx_hdr_pa;
	काष्ठा xlgmac_page_alloc rx_buf_pa;

	/* Ring index values
	 *  cur   - Tx: index of descriptor to be used क्रम current transfer
	 *          Rx: index of descriptor to check क्रम packet availability
	 *  dirty - Tx: index of descriptor to check क्रम transfer complete
	 *          Rx: index of descriptor to check क्रम buffer पुनः_स्मृतिation
	 */
	अचिन्हित पूर्णांक cur;
	अचिन्हित पूर्णांक dirty;

	/* Coalesce frame count used क्रम पूर्णांकerrupt bit setting */
	अचिन्हित पूर्णांक coalesce_count;

	जोड़ अणु
		काष्ठा अणु
			अचिन्हित पूर्णांक xmit_more;
			अचिन्हित पूर्णांक queue_stopped;
			अचिन्हित लघु cur_mss;
			अचिन्हित लघु cur_vlan_ctag;
		पूर्ण tx;
	पूर्ण;
पूर्ण ____cacheline_aligned;

काष्ठा xlgmac_channel अणु
	अक्षर name[16];

	/* Address of निजी data area क्रम device */
	काष्ठा xlgmac_pdata *pdata;

	/* Queue index and base address of queue's DMA रेजिस्टरs */
	अचिन्हित पूर्णांक queue_index;
	व्योम __iomem *dma_regs;

	/* Per channel पूर्णांकerrupt irq number */
	पूर्णांक dma_irq;
	अक्षर dma_irq_name[IFNAMSIZ + 32];

	/* Netdev related settings */
	काष्ठा napi_काष्ठा napi;

	अचिन्हित पूर्णांक saved_ier;

	अचिन्हित पूर्णांक tx_समयr_active;
	काष्ठा समयr_list tx_समयr;

	काष्ठा xlgmac_ring *tx_ring;
	काष्ठा xlgmac_ring *rx_ring;
पूर्ण ____cacheline_aligned;

काष्ठा xlgmac_desc_ops अणु
	पूर्णांक (*alloc_channels_and_rings)(काष्ठा xlgmac_pdata *pdata);
	व्योम (*मुक्त_channels_and_rings)(काष्ठा xlgmac_pdata *pdata);
	पूर्णांक (*map_tx_skb)(काष्ठा xlgmac_channel *channel,
			  काष्ठा sk_buff *skb);
	पूर्णांक (*map_rx_buffer)(काष्ठा xlgmac_pdata *pdata,
			     काष्ठा xlgmac_ring *ring,
			काष्ठा xlgmac_desc_data *desc_data);
	व्योम (*unmap_desc_data)(काष्ठा xlgmac_pdata *pdata,
				काष्ठा xlgmac_desc_data *desc_data);
	व्योम (*tx_desc_init)(काष्ठा xlgmac_pdata *pdata);
	व्योम (*rx_desc_init)(काष्ठा xlgmac_pdata *pdata);
पूर्ण;

काष्ठा xlgmac_hw_ops अणु
	पूर्णांक (*init)(काष्ठा xlgmac_pdata *pdata);
	पूर्णांक (*निकास)(काष्ठा xlgmac_pdata *pdata);

	पूर्णांक (*tx_complete)(काष्ठा xlgmac_dma_desc *dma_desc);

	व्योम (*enable_tx)(काष्ठा xlgmac_pdata *pdata);
	व्योम (*disable_tx)(काष्ठा xlgmac_pdata *pdata);
	व्योम (*enable_rx)(काष्ठा xlgmac_pdata *pdata);
	व्योम (*disable_rx)(काष्ठा xlgmac_pdata *pdata);

	पूर्णांक (*enable_पूर्णांक)(काष्ठा xlgmac_channel *channel,
			  क्रमागत xlgmac_पूर्णांक पूर्णांक_id);
	पूर्णांक (*disable_पूर्णांक)(काष्ठा xlgmac_channel *channel,
			   क्रमागत xlgmac_पूर्णांक पूर्णांक_id);
	व्योम (*dev_xmit)(काष्ठा xlgmac_channel *channel);
	पूर्णांक (*dev_पढ़ो)(काष्ठा xlgmac_channel *channel);

	पूर्णांक (*set_mac_address)(काष्ठा xlgmac_pdata *pdata, u8 *addr);
	पूर्णांक (*config_rx_mode)(काष्ठा xlgmac_pdata *pdata);
	पूर्णांक (*enable_rx_csum)(काष्ठा xlgmac_pdata *pdata);
	पूर्णांक (*disable_rx_csum)(काष्ठा xlgmac_pdata *pdata);

	/* For MII speed configuration */
	पूर्णांक (*set_xlgmii_25000_speed)(काष्ठा xlgmac_pdata *pdata);
	पूर्णांक (*set_xlgmii_40000_speed)(काष्ठा xlgmac_pdata *pdata);
	पूर्णांक (*set_xlgmii_50000_speed)(काष्ठा xlgmac_pdata *pdata);
	पूर्णांक (*set_xlgmii_100000_speed)(काष्ठा xlgmac_pdata *pdata);

	/* For descriptor related operation */
	व्योम (*tx_desc_init)(काष्ठा xlgmac_channel *channel);
	व्योम (*rx_desc_init)(काष्ठा xlgmac_channel *channel);
	व्योम (*tx_desc_reset)(काष्ठा xlgmac_desc_data *desc_data);
	व्योम (*rx_desc_reset)(काष्ठा xlgmac_pdata *pdata,
			      काष्ठा xlgmac_desc_data *desc_data,
			अचिन्हित पूर्णांक index);
	पूर्णांक (*is_last_desc)(काष्ठा xlgmac_dma_desc *dma_desc);
	पूर्णांक (*is_context_desc)(काष्ठा xlgmac_dma_desc *dma_desc);
	व्योम (*tx_start_xmit)(काष्ठा xlgmac_channel *channel,
			      काष्ठा xlgmac_ring *ring);

	/* For Flow Control */
	पूर्णांक (*config_tx_flow_control)(काष्ठा xlgmac_pdata *pdata);
	पूर्णांक (*config_rx_flow_control)(काष्ठा xlgmac_pdata *pdata);

	/* For Vlan related config */
	पूर्णांक (*enable_rx_vlan_stripping)(काष्ठा xlgmac_pdata *pdata);
	पूर्णांक (*disable_rx_vlan_stripping)(काष्ठा xlgmac_pdata *pdata);
	पूर्णांक (*enable_rx_vlan_filtering)(काष्ठा xlgmac_pdata *pdata);
	पूर्णांक (*disable_rx_vlan_filtering)(काष्ठा xlgmac_pdata *pdata);
	पूर्णांक (*update_vlan_hash_table)(काष्ठा xlgmac_pdata *pdata);

	/* For RX coalescing */
	पूर्णांक (*config_rx_coalesce)(काष्ठा xlgmac_pdata *pdata);
	पूर्णांक (*config_tx_coalesce)(काष्ठा xlgmac_pdata *pdata);
	अचिन्हित पूर्णांक (*usec_to_riwt)(काष्ठा xlgmac_pdata *pdata,
				     अचिन्हित पूर्णांक usec);
	अचिन्हित पूर्णांक (*riwt_to_usec)(काष्ठा xlgmac_pdata *pdata,
				     अचिन्हित पूर्णांक riwt);

	/* For RX and TX threshold config */
	पूर्णांक (*config_rx_threshold)(काष्ठा xlgmac_pdata *pdata,
				   अचिन्हित पूर्णांक val);
	पूर्णांक (*config_tx_threshold)(काष्ठा xlgmac_pdata *pdata,
				   अचिन्हित पूर्णांक val);

	/* For RX and TX Store and Forward Mode config */
	पूर्णांक (*config_rsf_mode)(काष्ठा xlgmac_pdata *pdata,
			       अचिन्हित पूर्णांक val);
	पूर्णांक (*config_tsf_mode)(काष्ठा xlgmac_pdata *pdata,
			       अचिन्हित पूर्णांक val);

	/* For TX DMA Operate on Second Frame config */
	पूर्णांक (*config_osp_mode)(काष्ठा xlgmac_pdata *pdata);

	/* For RX and TX PBL config */
	पूर्णांक (*config_rx_pbl_val)(काष्ठा xlgmac_pdata *pdata);
	पूर्णांक (*get_rx_pbl_val)(काष्ठा xlgmac_pdata *pdata);
	पूर्णांक (*config_tx_pbl_val)(काष्ठा xlgmac_pdata *pdata);
	पूर्णांक (*get_tx_pbl_val)(काष्ठा xlgmac_pdata *pdata);
	पूर्णांक (*config_pblx8)(काष्ठा xlgmac_pdata *pdata);

	/* For MMC statistics */
	व्योम (*rx_mmc_पूर्णांक)(काष्ठा xlgmac_pdata *pdata);
	व्योम (*tx_mmc_पूर्णांक)(काष्ठा xlgmac_pdata *pdata);
	व्योम (*पढ़ो_mmc_stats)(काष्ठा xlgmac_pdata *pdata);

	/* For Receive Side Scaling */
	पूर्णांक (*enable_rss)(काष्ठा xlgmac_pdata *pdata);
	पूर्णांक (*disable_rss)(काष्ठा xlgmac_pdata *pdata);
	पूर्णांक (*set_rss_hash_key)(काष्ठा xlgmac_pdata *pdata,
				स्थिर u8 *key);
	पूर्णांक (*set_rss_lookup_table)(काष्ठा xlgmac_pdata *pdata,
				    स्थिर u32 *table);
पूर्ण;

/* This काष्ठाure contains flags that indicate what hardware features
 * or configurations are present in the device.
 */
काष्ठा xlgmac_hw_features अणु
	/* HW Version */
	अचिन्हित पूर्णांक version;

	/* HW Feature Register0 */
	अचिन्हित पूर्णांक phyअगरsel;		/* PHY पूर्णांकerface support */
	अचिन्हित पूर्णांक vlhash;		/* VLAN Hash Filter */
	अचिन्हित पूर्णांक sma;		/* SMA(MDIO) Interface */
	अचिन्हित पूर्णांक rwk;		/* PMT remote wake-up packet */
	अचिन्हित पूर्णांक mgk;		/* PMT magic packet */
	अचिन्हित पूर्णांक mmc;		/* RMON module */
	अचिन्हित पूर्णांक aoe;		/* ARP Offload */
	अचिन्हित पूर्णांक ts;		/* IEEE 1588-2008 Advanced Timestamp */
	अचिन्हित पूर्णांक eee;		/* Energy Efficient Ethernet */
	अचिन्हित पूर्णांक tx_coe;		/* Tx Checksum Offload */
	अचिन्हित पूर्णांक rx_coe;		/* Rx Checksum Offload */
	अचिन्हित पूर्णांक addn_mac;		/* Additional MAC Addresses */
	अचिन्हित पूर्णांक ts_src;		/* Timestamp Source */
	अचिन्हित पूर्णांक sa_vlan_ins;	/* Source Address or VLAN Insertion */

	/* HW Feature Register1 */
	अचिन्हित पूर्णांक rx_fअगरo_size;	/* MTL Receive FIFO Size */
	अचिन्हित पूर्णांक tx_fअगरo_size;	/* MTL Transmit FIFO Size */
	अचिन्हित पूर्णांक adv_ts_hi;		/* Advance Timestamping High Word */
	अचिन्हित पूर्णांक dma_width;		/* DMA width */
	अचिन्हित पूर्णांक dcb;		/* DCB Feature */
	अचिन्हित पूर्णांक sph;		/* Split Header Feature */
	अचिन्हित पूर्णांक tso;		/* TCP Segmentation Offload */
	अचिन्हित पूर्णांक dma_debug;		/* DMA Debug Registers */
	अचिन्हित पूर्णांक rss;		/* Receive Side Scaling */
	अचिन्हित पूर्णांक tc_cnt;		/* Number of Traffic Classes */
	अचिन्हित पूर्णांक hash_table_size;	/* Hash Table Size */
	अचिन्हित पूर्णांक l3l4_filter_num;	/* Number of L3-L4 Filters */

	/* HW Feature Register2 */
	अचिन्हित पूर्णांक rx_q_cnt;		/* Number of MTL Receive Queues */
	अचिन्हित पूर्णांक tx_q_cnt;		/* Number of MTL Transmit Queues */
	अचिन्हित पूर्णांक rx_ch_cnt;		/* Number of DMA Receive Channels */
	अचिन्हित पूर्णांक tx_ch_cnt;		/* Number of DMA Transmit Channels */
	अचिन्हित पूर्णांक pps_out_num;	/* Number of PPS outमाला_दो */
	अचिन्हित पूर्णांक aux_snap_num;	/* Number of Aux snapshot inमाला_दो */
पूर्ण;

काष्ठा xlgmac_resources अणु
	व्योम __iomem *addr;
	पूर्णांक irq;
पूर्ण;

काष्ठा xlgmac_pdata अणु
	काष्ठा net_device *netdev;
	काष्ठा device *dev;

	काष्ठा xlgmac_hw_ops hw_ops;
	काष्ठा xlgmac_desc_ops desc_ops;

	/* Device statistics */
	काष्ठा xlgmac_stats stats;

	u32 msg_enable;

	/* MAC रेजिस्टरs base */
	व्योम __iomem *mac_regs;

	/* Hardware features of the device */
	काष्ठा xlgmac_hw_features hw_feat;

	काष्ठा work_काष्ठा restart_work;

	/* Rings क्रम Tx/Rx on a DMA channel */
	काष्ठा xlgmac_channel *channel_head;
	अचिन्हित पूर्णांक channel_count;
	अचिन्हित पूर्णांक tx_ring_count;
	अचिन्हित पूर्णांक rx_ring_count;
	अचिन्हित पूर्णांक tx_desc_count;
	अचिन्हित पूर्णांक rx_desc_count;
	अचिन्हित पूर्णांक tx_q_count;
	अचिन्हित पूर्णांक rx_q_count;

	/* Tx/Rx common settings */
	अचिन्हित पूर्णांक pblx8;

	/* Tx settings */
	अचिन्हित पूर्णांक tx_sf_mode;
	अचिन्हित पूर्णांक tx_threshold;
	अचिन्हित पूर्णांक tx_pbl;
	अचिन्हित पूर्णांक tx_osp_mode;

	/* Rx settings */
	अचिन्हित पूर्णांक rx_sf_mode;
	अचिन्हित पूर्णांक rx_threshold;
	अचिन्हित पूर्णांक rx_pbl;

	/* Tx coalescing settings */
	अचिन्हित पूर्णांक tx_usecs;
	अचिन्हित पूर्णांक tx_frames;

	/* Rx coalescing settings */
	अचिन्हित पूर्णांक rx_riwt;
	अचिन्हित पूर्णांक rx_usecs;
	अचिन्हित पूर्णांक rx_frames;

	/* Current Rx buffer size */
	अचिन्हित पूर्णांक rx_buf_size;

	/* Flow control settings */
	अचिन्हित पूर्णांक tx_छोड़ो;
	अचिन्हित पूर्णांक rx_छोड़ो;

	/* Device पूर्णांकerrupt number */
	पूर्णांक dev_irq;
	अचिन्हित पूर्णांक per_channel_irq;
	पूर्णांक channel_irq[XLGMAC_MAX_DMA_CHANNELS];

	/* Netdev related settings */
	अचिन्हित अक्षर mac_addr[ETH_ALEN];
	netdev_features_t netdev_features;
	काष्ठा napi_काष्ठा napi;

	/* Filtering support */
	अचिन्हित दीर्घ active_vlans[BITS_TO_LONGS(VLAN_N_VID)];

	/* Device घड़ीs */
	अचिन्हित दीर्घ sysclk_rate;

	/* RSS addressing mutex */
	काष्ठा mutex rss_mutex;

	/* Receive Side Scaling settings */
	u8 rss_key[XLGMAC_RSS_HASH_KEY_SIZE];
	u32 rss_table[XLGMAC_RSS_MAX_TABLE_SIZE];
	u32 rss_options;

	पूर्णांक phy_speed;

	अक्षर drv_name[32];
	अक्षर drv_ver[32];
पूर्ण;

व्योम xlgmac_init_desc_ops(काष्ठा xlgmac_desc_ops *desc_ops);
व्योम xlgmac_init_hw_ops(काष्ठा xlgmac_hw_ops *hw_ops);
स्थिर काष्ठा net_device_ops *xlgmac_get_netdev_ops(व्योम);
स्थिर काष्ठा ethtool_ops *xlgmac_get_ethtool_ops(व्योम);
व्योम xlgmac_dump_tx_desc(काष्ठा xlgmac_pdata *pdata,
			 काष्ठा xlgmac_ring *ring,
			 अचिन्हित पूर्णांक idx,
			 अचिन्हित पूर्णांक count,
			 अचिन्हित पूर्णांक flag);
व्योम xlgmac_dump_rx_desc(काष्ठा xlgmac_pdata *pdata,
			 काष्ठा xlgmac_ring *ring,
			 अचिन्हित पूर्णांक idx);
व्योम xlgmac_prपूर्णांक_pkt(काष्ठा net_device *netdev,
		      काष्ठा sk_buff *skb, bool tx_rx);
व्योम xlgmac_get_all_hw_features(काष्ठा xlgmac_pdata *pdata);
व्योम xlgmac_prपूर्णांक_all_hw_features(काष्ठा xlgmac_pdata *pdata);
पूर्णांक xlgmac_drv_probe(काष्ठा device *dev,
		     काष्ठा xlgmac_resources *res);
पूर्णांक xlgmac_drv_हटाओ(काष्ठा device *dev);

/* For debug prपूर्णांकs */
#अगर_घोषित XLGMAC_DEBUG
#घोषणा XLGMAC_PR(fmt, args...) \
	pr_alert("[%s,%d]:" fmt, __func__, __LINE__, ## args)
#अन्यथा
#घोषणा XLGMAC_PR(x...)		करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

#पूर्ण_अगर /* __DWC_XLGMAC_H__ */
