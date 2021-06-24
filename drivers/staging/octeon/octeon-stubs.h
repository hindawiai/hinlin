<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#घोषणा CONFIG_CAVIUM_OCTEON_CVMSEG_SIZE	512

#अगर_अघोषित XKPHYS_TO_PHYS
# define XKPHYS_TO_PHYS(p)			(p)
#पूर्ण_अगर

#घोषणा OCTEON_IRQ_WORKQ0 0
#घोषणा OCTEON_IRQ_RML 0
#घोषणा OCTEON_IRQ_TIMER1 0
#घोषणा OCTEON_IS_MODEL(x) 0
#घोषणा octeon_has_feature(x)	0
#घोषणा octeon_get_घड़ी_rate()	0

#घोषणा CVMX_SYNCIOBDMA		करो अणु पूर्ण जबतक (0)

#घोषणा CVMX_HELPER_INPUT_TAG_TYPE	0
#घोषणा CVMX_HELPER_FIRST_MBUFF_SKIP	7
#घोषणा CVMX_FAU_REG_END		(2048)
#घोषणा CVMX_FPA_OUTPUT_BUFFER_POOL	    (2)
#घोषणा CVMX_FPA_OUTPUT_BUFFER_POOL_SIZE    16
#घोषणा CVMX_FPA_PACKET_POOL		    (0)
#घोषणा CVMX_FPA_PACKET_POOL_SIZE	    16
#घोषणा CVMX_FPA_WQE_POOL		    (1)
#घोषणा CVMX_FPA_WQE_POOL_SIZE		    16
#घोषणा CVMX_GMXX_RXX_ADR_CAM_EN(a, b)	((a) + (b))
#घोषणा CVMX_GMXX_RXX_ADR_CTL(a, b)	((a) + (b))
#घोषणा CVMX_GMXX_PRTX_CFG(a, b)	((a) + (b))
#घोषणा CVMX_GMXX_RXX_FRM_MAX(a, b)	((a) + (b))
#घोषणा CVMX_GMXX_RXX_JABBER(a, b)	((a) + (b))
#घोषणा CVMX_IPD_CTL_STATUS		0
#घोषणा CVMX_PIP_FRM_LEN_CHKX(a)	(a)
#घोषणा CVMX_PIP_NUM_INPUT_PORTS	1
#घोषणा CVMX_SCR_SCRATCH		0
#घोषणा CVMX_PKO_QUEUES_PER_PORT_INTERFACE0	2
#घोषणा CVMX_PKO_QUEUES_PER_PORT_INTERFACE1	2
#घोषणा CVMX_IPD_SUB_PORT_FCS		0
#घोषणा CVMX_SSO_WQ_IQ_DIS		0
#घोषणा CVMX_SSO_WQ_INT			0
#घोषणा CVMX_POW_WQ_INT			0
#घोषणा CVMX_SSO_WQ_INT_PC		0
#घोषणा CVMX_NPI_RSL_INT_BLOCKS		0
#घोषणा CVMX_POW_WQ_INT_PC		0

जोड़ cvmx_pip_wqe_word2 अणु
	uपूर्णांक64_t u64;
	काष्ठा अणु
		uपूर्णांक64_t bufs:8;
		uपूर्णांक64_t ip_offset:8;
		uपूर्णांक64_t vlan_valid:1;
		uपूर्णांक64_t vlan_stacked:1;
		uपूर्णांक64_t unasचिन्हित:1;
		uपूर्णांक64_t vlan_cfi:1;
		uपूर्णांक64_t vlan_id:12;
		uपूर्णांक64_t pr:4;
		uपूर्णांक64_t unasचिन्हित2:8;
		uपूर्णांक64_t dec_ipcomp:1;
		uपूर्णांक64_t tcp_or_udp:1;
		uपूर्णांक64_t dec_ipsec:1;
		uपूर्णांक64_t is_v6:1;
		uपूर्णांक64_t software:1;
		uपूर्णांक64_t L4_error:1;
		uपूर्णांक64_t is_frag:1;
		uपूर्णांक64_t IP_exc:1;
		uपूर्णांक64_t is_bcast:1;
		uपूर्णांक64_t is_mcast:1;
		uपूर्णांक64_t not_IP:1;
		uपूर्णांक64_t rcv_error:1;
		uपूर्णांक64_t err_code:8;
	पूर्ण s;
	काष्ठा अणु
		uपूर्णांक64_t bufs:8;
		uपूर्णांक64_t ip_offset:8;
		uपूर्णांक64_t vlan_valid:1;
		uपूर्णांक64_t vlan_stacked:1;
		uपूर्णांक64_t unasचिन्हित:1;
		uपूर्णांक64_t vlan_cfi:1;
		uपूर्णांक64_t vlan_id:12;
		uपूर्णांक64_t port:12;
		uपूर्णांक64_t dec_ipcomp:1;
		uपूर्णांक64_t tcp_or_udp:1;
		uपूर्णांक64_t dec_ipsec:1;
		uपूर्णांक64_t is_v6:1;
		uपूर्णांक64_t software:1;
		uपूर्णांक64_t L4_error:1;
		uपूर्णांक64_t is_frag:1;
		uपूर्णांक64_t IP_exc:1;
		uपूर्णांक64_t is_bcast:1;
		uपूर्णांक64_t is_mcast:1;
		uपूर्णांक64_t not_IP:1;
		uपूर्णांक64_t rcv_error:1;
		uपूर्णांक64_t err_code:8;
	पूर्ण s_cn68xx;

	काष्ठा अणु
		uपूर्णांक64_t unused1:16;
		uपूर्णांक64_t vlan:16;
		uपूर्णांक64_t unused2:32;
	पूर्ण svlan;
	काष्ठा अणु
		uपूर्णांक64_t bufs:8;
		uपूर्णांक64_t unused:8;
		uपूर्णांक64_t vlan_valid:1;
		uपूर्णांक64_t vlan_stacked:1;
		uपूर्णांक64_t unasचिन्हित:1;
		uपूर्णांक64_t vlan_cfi:1;
		uपूर्णांक64_t vlan_id:12;
		uपूर्णांक64_t pr:4;
		uपूर्णांक64_t unasचिन्हित2:12;
		uपूर्णांक64_t software:1;
		uपूर्णांक64_t unasचिन्हित3:1;
		uपूर्णांक64_t is_rarp:1;
		uपूर्णांक64_t is_arp:1;
		uपूर्णांक64_t is_bcast:1;
		uपूर्णांक64_t is_mcast:1;
		uपूर्णांक64_t not_IP:1;
		uपूर्णांक64_t rcv_error:1;
		uपूर्णांक64_t err_code:8;
	पूर्ण snoip;

पूर्ण;

जोड़ cvmx_pip_wqe_word0 अणु
	काष्ठा अणु
		uपूर्णांक64_t next_ptr:40;
		uपूर्णांक8_t unused;
		__wsum hw_chksum;
	पूर्ण cn38xx;
	काष्ठा अणु
		uपूर्णांक64_t pknd:6;        /* 0..5 */
		uपूर्णांक64_t unused2:2;     /* 6..7 */
		uपूर्णांक64_t bpid:6;        /* 8..13 */
		uपूर्णांक64_t unused1:18;    /* 14..31 */
		uपूर्णांक64_t l2ptr:8;       /* 32..39 */
		uपूर्णांक64_t l3ptr:8;       /* 40..47 */
		uपूर्णांक64_t unused0:8;     /* 48..55 */
		uपूर्णांक64_t l4ptr:8;       /* 56..63 */
	पूर्ण cn68xx;
पूर्ण;

जोड़ cvmx_wqe_word0 अणु
	uपूर्णांक64_t u64;
	जोड़ cvmx_pip_wqe_word0 pip;
पूर्ण;

जोड़ cvmx_wqe_word1 अणु
	uपूर्णांक64_t u64;
	काष्ठा अणु
		uपूर्णांक64_t tag:32;
		uपूर्णांक64_t tag_type:2;
		uपूर्णांक64_t varies:14;
		uपूर्णांक64_t len:16;
	पूर्ण;
	काष्ठा अणु
		uपूर्णांक64_t tag:32;
		uपूर्णांक64_t tag_type:2;
		uपूर्णांक64_t zero_2:3;
		uपूर्णांक64_t grp:6;
		uपूर्णांक64_t zero_1:1;
		uपूर्णांक64_t qos:3;
		uपूर्णांक64_t zero_0:1;
		uपूर्णांक64_t len:16;
	पूर्ण cn68xx;
	काष्ठा अणु
		uपूर्णांक64_t tag:32;
		uपूर्णांक64_t tag_type:2;
		uपूर्णांक64_t zero_2:1;
		uपूर्णांक64_t grp:4;
		uपूर्णांक64_t qos:3;
		uपूर्णांक64_t ipprt:6;
		uपूर्णांक64_t len:16;
	पूर्ण cn38xx;
पूर्ण;

जोड़ cvmx_buf_ptr अणु
	व्योम *ptr;
	uपूर्णांक64_t u64;
	काष्ठा अणु
		uपूर्णांक64_t i:1;
		uपूर्णांक64_t back:4;
		uपूर्णांक64_t pool:3;
		uपूर्णांक64_t size:16;
		uपूर्णांक64_t addr:40;
	पूर्ण s;
पूर्ण;

काष्ठा cvmx_wqe अणु
	जोड़ cvmx_wqe_word0 word0;
	जोड़ cvmx_wqe_word1 word1;
	जोड़ cvmx_pip_wqe_word2 word2;
	जोड़ cvmx_buf_ptr packet_ptr;
	uपूर्णांक8_t packet_data[96];
पूर्ण;

जोड़ cvmx_helper_link_info अणु
	uपूर्णांक64_t u64;
	काष्ठा अणु
		uपूर्णांक64_t reserved_20_63:44;
		uपूर्णांक64_t link_up:1;	    /**< Is the physical link up? */
		uपूर्णांक64_t full_duplex:1;	    /**< 1 अगर the link is full duplex */
		uपूर्णांक64_t speed:18;	    /**< Speed of the link in Mbps */
	पूर्ण s;
पूर्ण;

क्रमागत cvmx_fau_reg_32 अणु
	CVMX_FAU_REG_32_START	= 0,
पूर्ण;

क्रमागत cvmx_fau_op_size अणु
	CVMX_FAU_OP_SIZE_8 = 0,
	CVMX_FAU_OP_SIZE_16 = 1,
	CVMX_FAU_OP_SIZE_32 = 2,
	CVMX_FAU_OP_SIZE_64 = 3
पूर्ण;

प्रकार क्रमागत अणु
	CVMX_SPI_MODE_UNKNOWN = 0,
	CVMX_SPI_MODE_TX_HALFPLEX = 1,
	CVMX_SPI_MODE_RX_HALFPLEX = 2,
	CVMX_SPI_MODE_DUPLEX = 3
पूर्ण cvmx_spi_mode_t;

प्रकार क्रमागत अणु
	CVMX_HELPER_INTERFACE_MODE_DISABLED,
	CVMX_HELPER_INTERFACE_MODE_RGMII,
	CVMX_HELPER_INTERFACE_MODE_GMII,
	CVMX_HELPER_INTERFACE_MODE_SPI,
	CVMX_HELPER_INTERFACE_MODE_PCIE,
	CVMX_HELPER_INTERFACE_MODE_XAUI,
	CVMX_HELPER_INTERFACE_MODE_SGMII,
	CVMX_HELPER_INTERFACE_MODE_PICMG,
	CVMX_HELPER_INTERFACE_MODE_NPI,
	CVMX_HELPER_INTERFACE_MODE_LOOP,
पूर्ण cvmx_helper_पूर्णांकerface_mode_t;

प्रकार क्रमागत अणु
	CVMX_POW_WAIT = 1,
	CVMX_POW_NO_WAIT = 0,
पूर्ण cvmx_घात_रुको_t;

प्रकार क्रमागत अणु
	CVMX_PKO_LOCK_NONE = 0,
	CVMX_PKO_LOCK_ATOMIC_TAG = 1,
	CVMX_PKO_LOCK_CMD_QUEUE = 2,
पूर्ण cvmx_pko_lock_t;

प्रकार क्रमागत अणु
	CVMX_PKO_SUCCESS,
	CVMX_PKO_INVALID_PORT,
	CVMX_PKO_INVALID_QUEUE,
	CVMX_PKO_INVALID_PRIORITY,
	CVMX_PKO_NO_MEMORY,
	CVMX_PKO_PORT_ALREADY_SETUP,
	CVMX_PKO_CMD_QUEUE_INIT_ERROR
पूर्ण cvmx_pko_status_t;

क्रमागत cvmx_घात_tag_type अणु
	CVMX_POW_TAG_TYPE_ORDERED   = 0L,
	CVMX_POW_TAG_TYPE_ATOMIC    = 1L,
	CVMX_POW_TAG_TYPE_शून्य	    = 2L,
	CVMX_POW_TAG_TYPE_शून्य_शून्य = 3L
पूर्ण;

जोड़ cvmx_ipd_ctl_status अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_ipd_ctl_status_s अणु
		uपूर्णांक64_t reserved_18_63:46;
		uपूर्णांक64_t use_sop:1;
		uपूर्णांक64_t rst_करोne:1;
		uपूर्णांक64_t clken:1;
		uपूर्णांक64_t no_wptr:1;
		uपूर्णांक64_t pq_apkt:1;
		uपूर्णांक64_t pq_nabuf:1;
		uपूर्णांक64_t ipd_full:1;
		uपूर्णांक64_t pkt_off:1;
		uपूर्णांक64_t len_m8:1;
		uपूर्णांक64_t reset:1;
		uपूर्णांक64_t addpkt:1;
		uपूर्णांक64_t naddbuf:1;
		uपूर्णांक64_t pkt_lend:1;
		uपूर्णांक64_t wqe_lend:1;
		uपूर्णांक64_t pbp_en:1;
		uपूर्णांक64_t opc_mode:2;
		uपूर्णांक64_t ipd_en:1;
	पूर्ण s;
	काष्ठा cvmx_ipd_ctl_status_cn30xx अणु
		uपूर्णांक64_t reserved_10_63:54;
		uपूर्णांक64_t len_m8:1;
		uपूर्णांक64_t reset:1;
		uपूर्णांक64_t addpkt:1;
		uपूर्णांक64_t naddbuf:1;
		uपूर्णांक64_t pkt_lend:1;
		uपूर्णांक64_t wqe_lend:1;
		uपूर्णांक64_t pbp_en:1;
		uपूर्णांक64_t opc_mode:2;
		uपूर्णांक64_t ipd_en:1;
	पूर्ण cn30xx;
	काष्ठा cvmx_ipd_ctl_status_cn38xxp2 अणु
		uपूर्णांक64_t reserved_9_63:55;
		uपूर्णांक64_t reset:1;
		uपूर्णांक64_t addpkt:1;
		uपूर्णांक64_t naddbuf:1;
		uपूर्णांक64_t pkt_lend:1;
		uपूर्णांक64_t wqe_lend:1;
		uपूर्णांक64_t pbp_en:1;
		uपूर्णांक64_t opc_mode:2;
		uपूर्णांक64_t ipd_en:1;
	पूर्ण cn38xxp2;
	काष्ठा cvmx_ipd_ctl_status_cn50xx अणु
		uपूर्णांक64_t reserved_15_63:49;
		uपूर्णांक64_t no_wptr:1;
		uपूर्णांक64_t pq_apkt:1;
		uपूर्णांक64_t pq_nabuf:1;
		uपूर्णांक64_t ipd_full:1;
		uपूर्णांक64_t pkt_off:1;
		uपूर्णांक64_t len_m8:1;
		uपूर्णांक64_t reset:1;
		uपूर्णांक64_t addpkt:1;
		uपूर्णांक64_t naddbuf:1;
		uपूर्णांक64_t pkt_lend:1;
		uपूर्णांक64_t wqe_lend:1;
		uपूर्णांक64_t pbp_en:1;
		uपूर्णांक64_t opc_mode:2;
		uपूर्णांक64_t ipd_en:1;
	पूर्ण cn50xx;
	काष्ठा cvmx_ipd_ctl_status_cn58xx अणु
		uपूर्णांक64_t reserved_12_63:52;
		uपूर्णांक64_t ipd_full:1;
		uपूर्णांक64_t pkt_off:1;
		uपूर्णांक64_t len_m8:1;
		uपूर्णांक64_t reset:1;
		uपूर्णांक64_t addpkt:1;
		uपूर्णांक64_t naddbuf:1;
		uपूर्णांक64_t pkt_lend:1;
		uपूर्णांक64_t wqe_lend:1;
		uपूर्णांक64_t pbp_en:1;
		uपूर्णांक64_t opc_mode:2;
		uपूर्णांक64_t ipd_en:1;
	पूर्ण cn58xx;
	काष्ठा cvmx_ipd_ctl_status_cn63xxp1 अणु
		uपूर्णांक64_t reserved_16_63:48;
		uपूर्णांक64_t clken:1;
		uपूर्णांक64_t no_wptr:1;
		uपूर्णांक64_t pq_apkt:1;
		uपूर्णांक64_t pq_nabuf:1;
		uपूर्णांक64_t ipd_full:1;
		uपूर्णांक64_t pkt_off:1;
		uपूर्णांक64_t len_m8:1;
		uपूर्णांक64_t reset:1;
		uपूर्णांक64_t addpkt:1;
		uपूर्णांक64_t naddbuf:1;
		uपूर्णांक64_t pkt_lend:1;
		uपूर्णांक64_t wqe_lend:1;
		uपूर्णांक64_t pbp_en:1;
		uपूर्णांक64_t opc_mode:2;
		uपूर्णांक64_t ipd_en:1;
	पूर्ण cn63xxp1;
पूर्ण;

जोड़ cvmx_ipd_sub_port_fcs अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_ipd_sub_port_fcs_s अणु
		uपूर्णांक64_t port_bit:32;
		uपूर्णांक64_t reserved_32_35:4;
		uपूर्णांक64_t port_bit2:4;
		uपूर्णांक64_t reserved_40_63:24;
	पूर्ण s;
	काष्ठा cvmx_ipd_sub_port_fcs_cn30xx अणु
		uपूर्णांक64_t port_bit:3;
		uपूर्णांक64_t reserved_3_63:61;
	पूर्ण cn30xx;
	काष्ठा cvmx_ipd_sub_port_fcs_cn38xx अणु
		uपूर्णांक64_t port_bit:32;
		uपूर्णांक64_t reserved_32_63:32;
	पूर्ण cn38xx;
पूर्ण;

जोड़ cvmx_ipd_sub_port_qos_cnt अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_ipd_sub_port_qos_cnt_s अणु
		uपूर्णांक64_t cnt:32;
		uपूर्णांक64_t port_qos:9;
		uपूर्णांक64_t reserved_41_63:23;
	पूर्ण s;
पूर्ण;

प्रकार काष्ठा अणु
	uपूर्णांक32_t dropped_octets;
	uपूर्णांक32_t dropped_packets;
	uपूर्णांक32_t pci_raw_packets;
	uपूर्णांक32_t octets;
	uपूर्णांक32_t packets;
	uपूर्णांक32_t multicast_packets;
	uपूर्णांक32_t broadcast_packets;
	uपूर्णांक32_t len_64_packets;
	uपूर्णांक32_t len_65_127_packets;
	uपूर्णांक32_t len_128_255_packets;
	uपूर्णांक32_t len_256_511_packets;
	uपूर्णांक32_t len_512_1023_packets;
	uपूर्णांक32_t len_1024_1518_packets;
	uपूर्णांक32_t len_1519_max_packets;
	uपूर्णांक32_t fcs_align_err_packets;
	uपूर्णांक32_t runt_packets;
	uपूर्णांक32_t runt_crc_packets;
	uपूर्णांक32_t oversize_packets;
	uपूर्णांक32_t oversize_crc_packets;
	uपूर्णांक32_t inb_packets;
	uपूर्णांक64_t inb_octets;
	uपूर्णांक16_t inb_errors;
पूर्ण cvmx_pip_port_status_t;

प्रकार काष्ठा अणु
	uपूर्णांक32_t packets;
	uपूर्णांक64_t octets;
	uपूर्णांक64_t करोorbell;
पूर्ण cvmx_pko_port_status_t;

जोड़ cvmx_pip_frm_len_chkx अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pip_frm_len_chkx_s अणु
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t maxlen:16;
		uपूर्णांक64_t minlen:16;
	पूर्ण s;
पूर्ण;

जोड़ cvmx_gmxx_rxx_frm_ctl अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_gmxx_rxx_frm_ctl_s अणु
		uपूर्णांक64_t pre_chk:1;
		uपूर्णांक64_t pre_strp:1;
		uपूर्णांक64_t ctl_drp:1;
		uपूर्णांक64_t ctl_bck:1;
		uपूर्णांक64_t ctl_mcst:1;
		uपूर्णांक64_t ctl_smac:1;
		uपूर्णांक64_t pre_मुक्त:1;
		uपूर्णांक64_t vlan_len:1;
		uपूर्णांक64_t pad_len:1;
		uपूर्णांक64_t pre_align:1;
		uपूर्णांक64_t null_dis:1;
		uपूर्णांक64_t reserved_11_11:1;
		uपूर्णांक64_t ptp_mode:1;
		uपूर्णांक64_t reserved_13_63:51;
	पूर्ण s;
	काष्ठा cvmx_gmxx_rxx_frm_ctl_cn30xx अणु
		uपूर्णांक64_t pre_chk:1;
		uपूर्णांक64_t pre_strp:1;
		uपूर्णांक64_t ctl_drp:1;
		uपूर्णांक64_t ctl_bck:1;
		uपूर्णांक64_t ctl_mcst:1;
		uपूर्णांक64_t ctl_smac:1;
		uपूर्णांक64_t pre_मुक्त:1;
		uपूर्णांक64_t vlan_len:1;
		uपूर्णांक64_t pad_len:1;
		uपूर्णांक64_t reserved_9_63:55;
	पूर्ण cn30xx;
	काष्ठा cvmx_gmxx_rxx_frm_ctl_cn31xx अणु
		uपूर्णांक64_t pre_chk:1;
		uपूर्णांक64_t pre_strp:1;
		uपूर्णांक64_t ctl_drp:1;
		uपूर्णांक64_t ctl_bck:1;
		uपूर्णांक64_t ctl_mcst:1;
		uपूर्णांक64_t ctl_smac:1;
		uपूर्णांक64_t pre_मुक्त:1;
		uपूर्णांक64_t vlan_len:1;
		uपूर्णांक64_t reserved_8_63:56;
	पूर्ण cn31xx;
	काष्ठा cvmx_gmxx_rxx_frm_ctl_cn50xx अणु
		uपूर्णांक64_t pre_chk:1;
		uपूर्णांक64_t pre_strp:1;
		uपूर्णांक64_t ctl_drp:1;
		uपूर्णांक64_t ctl_bck:1;
		uपूर्णांक64_t ctl_mcst:1;
		uपूर्णांक64_t ctl_smac:1;
		uपूर्णांक64_t pre_मुक्त:1;
		uपूर्णांक64_t reserved_7_8:2;
		uपूर्णांक64_t pre_align:1;
		uपूर्णांक64_t null_dis:1;
		uपूर्णांक64_t reserved_11_63:53;
	पूर्ण cn50xx;
	काष्ठा cvmx_gmxx_rxx_frm_ctl_cn56xxp1 अणु
		uपूर्णांक64_t pre_chk:1;
		uपूर्णांक64_t pre_strp:1;
		uपूर्णांक64_t ctl_drp:1;
		uपूर्णांक64_t ctl_bck:1;
		uपूर्णांक64_t ctl_mcst:1;
		uपूर्णांक64_t ctl_smac:1;
		uपूर्णांक64_t pre_मुक्त:1;
		uपूर्णांक64_t reserved_7_8:2;
		uपूर्णांक64_t pre_align:1;
		uपूर्णांक64_t reserved_10_63:54;
	पूर्ण cn56xxp1;
	काष्ठा cvmx_gmxx_rxx_frm_ctl_cn58xx अणु
		uपूर्णांक64_t pre_chk:1;
		uपूर्णांक64_t pre_strp:1;
		uपूर्णांक64_t ctl_drp:1;
		uपूर्णांक64_t ctl_bck:1;
		uपूर्णांक64_t ctl_mcst:1;
		uपूर्णांक64_t ctl_smac:1;
		uपूर्णांक64_t pre_मुक्त:1;
		uपूर्णांक64_t vlan_len:1;
		uपूर्णांक64_t pad_len:1;
		uपूर्णांक64_t pre_align:1;
		uपूर्णांक64_t null_dis:1;
		uपूर्णांक64_t reserved_11_63:53;
	पूर्ण cn58xx;
	काष्ठा cvmx_gmxx_rxx_frm_ctl_cn61xx अणु
		uपूर्णांक64_t pre_chk:1;
		uपूर्णांक64_t pre_strp:1;
		uपूर्णांक64_t ctl_drp:1;
		uपूर्णांक64_t ctl_bck:1;
		uपूर्णांक64_t ctl_mcst:1;
		uपूर्णांक64_t ctl_smac:1;
		uपूर्णांक64_t pre_मुक्त:1;
		uपूर्णांक64_t reserved_7_8:2;
		uपूर्णांक64_t pre_align:1;
		uपूर्णांक64_t null_dis:1;
		uपूर्णांक64_t reserved_11_11:1;
		uपूर्णांक64_t ptp_mode:1;
		uपूर्णांक64_t reserved_13_63:51;
	पूर्ण cn61xx;
पूर्ण;

जोड़ cvmx_gmxx_rxx_पूर्णांक_reg अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_gmxx_rxx_पूर्णांक_reg_s अणु
		uपूर्णांक64_t minerr:1;
		uपूर्णांक64_t carext:1;
		uपूर्णांक64_t maxerr:1;
		uपूर्णांक64_t jabber:1;
		uपूर्णांक64_t fcserr:1;
		uपूर्णांक64_t alnerr:1;
		uपूर्णांक64_t lenerr:1;
		uपूर्णांक64_t rcverr:1;
		uपूर्णांक64_t skperr:1;
		uपूर्णांक64_t niberr:1;
		uपूर्णांक64_t ovrerr:1;
		uपूर्णांक64_t pcterr:1;
		uपूर्णांक64_t rsverr:1;
		uपूर्णांक64_t falerr:1;
		uपूर्णांक64_t coldet:1;
		uपूर्णांक64_t अगरgerr:1;
		uपूर्णांक64_t phy_link:1;
		uपूर्णांक64_t phy_spd:1;
		uपूर्णांक64_t phy_dupx:1;
		uपूर्णांक64_t छोड़ो_drp:1;
		uपूर्णांक64_t loc_fault:1;
		uपूर्णांक64_t rem_fault:1;
		uपूर्णांक64_t bad_seq:1;
		uपूर्णांक64_t bad_term:1;
		uपूर्णांक64_t unsop:1;
		uपूर्णांक64_t uneop:1;
		uपूर्णांक64_t undat:1;
		uपूर्णांक64_t hg2fld:1;
		uपूर्णांक64_t hg2cc:1;
		uपूर्णांक64_t reserved_29_63:35;
	पूर्ण s;
	काष्ठा cvmx_gmxx_rxx_पूर्णांक_reg_cn30xx अणु
		uपूर्णांक64_t minerr:1;
		uपूर्णांक64_t carext:1;
		uपूर्णांक64_t maxerr:1;
		uपूर्णांक64_t jabber:1;
		uपूर्णांक64_t fcserr:1;
		uपूर्णांक64_t alnerr:1;
		uपूर्णांक64_t lenerr:1;
		uपूर्णांक64_t rcverr:1;
		uपूर्णांक64_t skperr:1;
		uपूर्णांक64_t niberr:1;
		uपूर्णांक64_t ovrerr:1;
		uपूर्णांक64_t pcterr:1;
		uपूर्णांक64_t rsverr:1;
		uपूर्णांक64_t falerr:1;
		uपूर्णांक64_t coldet:1;
		uपूर्णांक64_t अगरgerr:1;
		uपूर्णांक64_t phy_link:1;
		uपूर्णांक64_t phy_spd:1;
		uपूर्णांक64_t phy_dupx:1;
		uपूर्णांक64_t reserved_19_63:45;
	पूर्ण cn30xx;
	काष्ठा cvmx_gmxx_rxx_पूर्णांक_reg_cn50xx अणु
		uपूर्णांक64_t reserved_0_0:1;
		uपूर्णांक64_t carext:1;
		uपूर्णांक64_t reserved_2_2:1;
		uपूर्णांक64_t jabber:1;
		uपूर्णांक64_t fcserr:1;
		uपूर्णांक64_t alnerr:1;
		uपूर्णांक64_t reserved_6_6:1;
		uपूर्णांक64_t rcverr:1;
		uपूर्णांक64_t skperr:1;
		uपूर्णांक64_t niberr:1;
		uपूर्णांक64_t ovrerr:1;
		uपूर्णांक64_t pcterr:1;
		uपूर्णांक64_t rsverr:1;
		uपूर्णांक64_t falerr:1;
		uपूर्णांक64_t coldet:1;
		uपूर्णांक64_t अगरgerr:1;
		uपूर्णांक64_t phy_link:1;
		uपूर्णांक64_t phy_spd:1;
		uपूर्णांक64_t phy_dupx:1;
		uपूर्णांक64_t छोड़ो_drp:1;
		uपूर्णांक64_t reserved_20_63:44;
	पूर्ण cn50xx;
	काष्ठा cvmx_gmxx_rxx_पूर्णांक_reg_cn52xx अणु
		uपूर्णांक64_t reserved_0_0:1;
		uपूर्णांक64_t carext:1;
		uपूर्णांक64_t reserved_2_2:1;
		uपूर्णांक64_t jabber:1;
		uपूर्णांक64_t fcserr:1;
		uपूर्णांक64_t reserved_5_6:2;
		uपूर्णांक64_t rcverr:1;
		uपूर्णांक64_t skperr:1;
		uपूर्णांक64_t reserved_9_9:1;
		uपूर्णांक64_t ovrerr:1;
		uपूर्णांक64_t pcterr:1;
		uपूर्णांक64_t rsverr:1;
		uपूर्णांक64_t falerr:1;
		uपूर्णांक64_t coldet:1;
		uपूर्णांक64_t अगरgerr:1;
		uपूर्णांक64_t reserved_16_18:3;
		uपूर्णांक64_t छोड़ो_drp:1;
		uपूर्णांक64_t loc_fault:1;
		uपूर्णांक64_t rem_fault:1;
		uपूर्णांक64_t bad_seq:1;
		uपूर्णांक64_t bad_term:1;
		uपूर्णांक64_t unsop:1;
		uपूर्णांक64_t uneop:1;
		uपूर्णांक64_t undat:1;
		uपूर्णांक64_t hg2fld:1;
		uपूर्णांक64_t hg2cc:1;
		uपूर्णांक64_t reserved_29_63:35;
	पूर्ण cn52xx;
	काष्ठा cvmx_gmxx_rxx_पूर्णांक_reg_cn56xxp1 अणु
		uपूर्णांक64_t reserved_0_0:1;
		uपूर्णांक64_t carext:1;
		uपूर्णांक64_t reserved_2_2:1;
		uपूर्णांक64_t jabber:1;
		uपूर्णांक64_t fcserr:1;
		uपूर्णांक64_t reserved_5_6:2;
		uपूर्णांक64_t rcverr:1;
		uपूर्णांक64_t skperr:1;
		uपूर्णांक64_t reserved_9_9:1;
		uपूर्णांक64_t ovrerr:1;
		uपूर्णांक64_t pcterr:1;
		uपूर्णांक64_t rsverr:1;
		uपूर्णांक64_t falerr:1;
		uपूर्णांक64_t coldet:1;
		uपूर्णांक64_t अगरgerr:1;
		uपूर्णांक64_t reserved_16_18:3;
		uपूर्णांक64_t छोड़ो_drp:1;
		uपूर्णांक64_t loc_fault:1;
		uपूर्णांक64_t rem_fault:1;
		uपूर्णांक64_t bad_seq:1;
		uपूर्णांक64_t bad_term:1;
		uपूर्णांक64_t unsop:1;
		uपूर्णांक64_t uneop:1;
		uपूर्णांक64_t undat:1;
		uपूर्णांक64_t reserved_27_63:37;
	पूर्ण cn56xxp1;
	काष्ठा cvmx_gmxx_rxx_पूर्णांक_reg_cn58xx अणु
		uपूर्णांक64_t minerr:1;
		uपूर्णांक64_t carext:1;
		uपूर्णांक64_t maxerr:1;
		uपूर्णांक64_t jabber:1;
		uपूर्णांक64_t fcserr:1;
		uपूर्णांक64_t alnerr:1;
		uपूर्णांक64_t lenerr:1;
		uपूर्णांक64_t rcverr:1;
		uपूर्णांक64_t skperr:1;
		uपूर्णांक64_t niberr:1;
		uपूर्णांक64_t ovrerr:1;
		uपूर्णांक64_t pcterr:1;
		uपूर्णांक64_t rsverr:1;
		uपूर्णांक64_t falerr:1;
		uपूर्णांक64_t coldet:1;
		uपूर्णांक64_t अगरgerr:1;
		uपूर्णांक64_t phy_link:1;
		uपूर्णांक64_t phy_spd:1;
		uपूर्णांक64_t phy_dupx:1;
		uपूर्णांक64_t छोड़ो_drp:1;
		uपूर्णांक64_t reserved_20_63:44;
	पूर्ण cn58xx;
	काष्ठा cvmx_gmxx_rxx_पूर्णांक_reg_cn61xx अणु
		uपूर्णांक64_t minerr:1;
		uपूर्णांक64_t carext:1;
		uपूर्णांक64_t reserved_2_2:1;
		uपूर्णांक64_t jabber:1;
		uपूर्णांक64_t fcserr:1;
		uपूर्णांक64_t reserved_5_6:2;
		uपूर्णांक64_t rcverr:1;
		uपूर्णांक64_t skperr:1;
		uपूर्णांक64_t reserved_9_9:1;
		uपूर्णांक64_t ovrerr:1;
		uपूर्णांक64_t pcterr:1;
		uपूर्णांक64_t rsverr:1;
		uपूर्णांक64_t falerr:1;
		uपूर्णांक64_t coldet:1;
		uपूर्णांक64_t अगरgerr:1;
		uपूर्णांक64_t reserved_16_18:3;
		uपूर्णांक64_t छोड़ो_drp:1;
		uपूर्णांक64_t loc_fault:1;
		uपूर्णांक64_t rem_fault:1;
		uपूर्णांक64_t bad_seq:1;
		uपूर्णांक64_t bad_term:1;
		uपूर्णांक64_t unsop:1;
		uपूर्णांक64_t uneop:1;
		uपूर्णांक64_t undat:1;
		uपूर्णांक64_t hg2fld:1;
		uपूर्णांक64_t hg2cc:1;
		uपूर्णांक64_t reserved_29_63:35;
	पूर्ण cn61xx;
पूर्ण;

जोड़ cvmx_gmxx_prtx_cfg अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_gmxx_prtx_cfg_s अणु
		uपूर्णांक64_t reserved_22_63:42;
		uपूर्णांक64_t pknd:6;
		uपूर्णांक64_t reserved_14_15:2;
		uपूर्णांक64_t tx_idle:1;
		uपूर्णांक64_t rx_idle:1;
		uपूर्णांक64_t reserved_9_11:3;
		uपूर्णांक64_t speed_msb:1;
		uपूर्णांक64_t reserved_4_7:4;
		uपूर्णांक64_t slotसमय:1;
		uपूर्णांक64_t duplex:1;
		uपूर्णांक64_t speed:1;
		uपूर्णांक64_t en:1;
	पूर्ण s;
	काष्ठा cvmx_gmxx_prtx_cfg_cn30xx अणु
		uपूर्णांक64_t reserved_4_63:60;
		uपूर्णांक64_t slotसमय:1;
		uपूर्णांक64_t duplex:1;
		uपूर्णांक64_t speed:1;
		uपूर्णांक64_t en:1;
	पूर्ण cn30xx;
	काष्ठा cvmx_gmxx_prtx_cfg_cn52xx अणु
		uपूर्णांक64_t reserved_14_63:50;
		uपूर्णांक64_t tx_idle:1;
		uपूर्णांक64_t rx_idle:1;
		uपूर्णांक64_t reserved_9_11:3;
		uपूर्णांक64_t speed_msb:1;
		uपूर्णांक64_t reserved_4_7:4;
		uपूर्णांक64_t slotसमय:1;
		uपूर्णांक64_t duplex:1;
		uपूर्णांक64_t speed:1;
		uपूर्णांक64_t en:1;
	पूर्ण cn52xx;
पूर्ण;

जोड़ cvmx_gmxx_rxx_adr_ctl अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_gmxx_rxx_adr_ctl_s अणु
		uपूर्णांक64_t reserved_4_63:60;
		uपूर्णांक64_t cam_mode:1;
		uपूर्णांक64_t mcst:2;
		uपूर्णांक64_t bcst:1;
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pip_prt_tagx अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pip_prt_tagx_s अणु
		uपूर्णांक64_t reserved_54_63:10;
		uपूर्णांक64_t portadd_en:1;
		uपूर्णांक64_t inc_hwchk:1;
		uपूर्णांक64_t reserved_50_51:2;
		uपूर्णांक64_t grptagbase_msb:2;
		uपूर्णांक64_t reserved_46_47:2;
		uपूर्णांक64_t grptagmask_msb:2;
		uपूर्णांक64_t reserved_42_43:2;
		uपूर्णांक64_t grp_msb:2;
		uपूर्णांक64_t grptagbase:4;
		uपूर्णांक64_t grptagmask:4;
		uपूर्णांक64_t grptag:1;
		uपूर्णांक64_t grptag_mskip:1;
		uपूर्णांक64_t tag_mode:2;
		uपूर्णांक64_t inc_vs:2;
		uपूर्णांक64_t inc_vlan:1;
		uपूर्णांक64_t inc_prt_flag:1;
		uपूर्णांक64_t ip6_dprt_flag:1;
		uपूर्णांक64_t ip4_dprt_flag:1;
		uपूर्णांक64_t ip6_sprt_flag:1;
		uपूर्णांक64_t ip4_sprt_flag:1;
		uपूर्णांक64_t ip6_nxth_flag:1;
		uपूर्णांक64_t ip4_pctl_flag:1;
		uपूर्णांक64_t ip6_dst_flag:1;
		uपूर्णांक64_t ip4_dst_flag:1;
		uपूर्णांक64_t ip6_src_flag:1;
		uपूर्णांक64_t ip4_src_flag:1;
		uपूर्णांक64_t tcp6_tag_type:2;
		uपूर्णांक64_t tcp4_tag_type:2;
		uपूर्णांक64_t ip6_tag_type:2;
		uपूर्णांक64_t ip4_tag_type:2;
		uपूर्णांक64_t non_tag_type:2;
		uपूर्णांक64_t grp:4;
	पूर्ण s;
	काष्ठा cvmx_pip_prt_tagx_cn30xx अणु
		uपूर्णांक64_t reserved_40_63:24;
		uपूर्णांक64_t grptagbase:4;
		uपूर्णांक64_t grptagmask:4;
		uपूर्णांक64_t grptag:1;
		uपूर्णांक64_t reserved_30_30:1;
		uपूर्णांक64_t tag_mode:2;
		uपूर्णांक64_t inc_vs:2;
		uपूर्णांक64_t inc_vlan:1;
		uपूर्णांक64_t inc_prt_flag:1;
		uपूर्णांक64_t ip6_dprt_flag:1;
		uपूर्णांक64_t ip4_dprt_flag:1;
		uपूर्णांक64_t ip6_sprt_flag:1;
		uपूर्णांक64_t ip4_sprt_flag:1;
		uपूर्णांक64_t ip6_nxth_flag:1;
		uपूर्णांक64_t ip4_pctl_flag:1;
		uपूर्णांक64_t ip6_dst_flag:1;
		uपूर्णांक64_t ip4_dst_flag:1;
		uपूर्णांक64_t ip6_src_flag:1;
		uपूर्णांक64_t ip4_src_flag:1;
		uपूर्णांक64_t tcp6_tag_type:2;
		uपूर्णांक64_t tcp4_tag_type:2;
		uपूर्णांक64_t ip6_tag_type:2;
		uपूर्णांक64_t ip4_tag_type:2;
		uपूर्णांक64_t non_tag_type:2;
		uपूर्णांक64_t grp:4;
	पूर्ण cn30xx;
	काष्ठा cvmx_pip_prt_tagx_cn50xx अणु
		uपूर्णांक64_t reserved_40_63:24;
		uपूर्णांक64_t grptagbase:4;
		uपूर्णांक64_t grptagmask:4;
		uपूर्णांक64_t grptag:1;
		uपूर्णांक64_t grptag_mskip:1;
		uपूर्णांक64_t tag_mode:2;
		uपूर्णांक64_t inc_vs:2;
		uपूर्णांक64_t inc_vlan:1;
		uपूर्णांक64_t inc_prt_flag:1;
		uपूर्णांक64_t ip6_dprt_flag:1;
		uपूर्णांक64_t ip4_dprt_flag:1;
		uपूर्णांक64_t ip6_sprt_flag:1;
		uपूर्णांक64_t ip4_sprt_flag:1;
		uपूर्णांक64_t ip6_nxth_flag:1;
		uपूर्णांक64_t ip4_pctl_flag:1;
		uपूर्णांक64_t ip6_dst_flag:1;
		uपूर्णांक64_t ip4_dst_flag:1;
		uपूर्णांक64_t ip6_src_flag:1;
		uपूर्णांक64_t ip4_src_flag:1;
		uपूर्णांक64_t tcp6_tag_type:2;
		uपूर्णांक64_t tcp4_tag_type:2;
		uपूर्णांक64_t ip6_tag_type:2;
		uपूर्णांक64_t ip4_tag_type:2;
		uपूर्णांक64_t non_tag_type:2;
		uपूर्णांक64_t grp:4;
	पूर्ण cn50xx;
पूर्ण;

जोड़ cvmx_spxx_पूर्णांक_reg अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_spxx_पूर्णांक_reg_s अणु
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t spf:1;
		uपूर्णांक64_t reserved_12_30:19;
		uपूर्णांक64_t calerr:1;
		uपूर्णांक64_t syncerr:1;
		uपूर्णांक64_t diperr:1;
		uपूर्णांक64_t tpaovr:1;
		uपूर्णांक64_t rsverr:1;
		uपूर्णांक64_t drwnng:1;
		uपूर्णांक64_t clserr:1;
		uपूर्णांक64_t spiovr:1;
		uपूर्णांक64_t reserved_2_3:2;
		uपूर्णांक64_t abnorm:1;
		uपूर्णांक64_t prtnxa:1;
	पूर्ण s;
पूर्ण;

जोड़ cvmx_spxx_पूर्णांक_msk अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_spxx_पूर्णांक_msk_s अणु
		uपूर्णांक64_t reserved_12_63:52;
		uपूर्णांक64_t calerr:1;
		uपूर्णांक64_t syncerr:1;
		uपूर्णांक64_t diperr:1;
		uपूर्णांक64_t tpaovr:1;
		uपूर्णांक64_t rsverr:1;
		uपूर्णांक64_t drwnng:1;
		uपूर्णांक64_t clserr:1;
		uपूर्णांक64_t spiovr:1;
		uपूर्णांक64_t reserved_2_3:2;
		uपूर्णांक64_t abnorm:1;
		uपूर्णांक64_t prtnxa:1;
	पूर्ण s;
पूर्ण;

जोड़ cvmx_घात_wq_पूर्णांक अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_घात_wq_पूर्णांक_s अणु
		uपूर्णांक64_t wq_पूर्णांक:16;
		uपूर्णांक64_t iq_dis:16;
		uपूर्णांक64_t reserved_32_63:32;
	पूर्ण s;
पूर्ण;

जोड़ cvmx_sso_wq_पूर्णांक_thrx अणु
	uपूर्णांक64_t u64;
	काष्ठा अणु
		uपूर्णांक64_t iq_thr:12;
		uपूर्णांक64_t reserved_12_13:2;
		uपूर्णांक64_t ds_thr:12;
		uपूर्णांक64_t reserved_26_27:2;
		uपूर्णांक64_t tc_thr:4;
		uपूर्णांक64_t tc_en:1;
		uपूर्णांक64_t reserved_33_63:31;
	पूर्ण s;
पूर्ण;

जोड़ cvmx_stxx_पूर्णांक_reg अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_stxx_पूर्णांक_reg_s अणु
		uपूर्णांक64_t reserved_9_63:55;
		uपूर्णांक64_t syncerr:1;
		uपूर्णांक64_t frmerr:1;
		uपूर्णांक64_t unxfrm:1;
		uपूर्णांक64_t nosync:1;
		uपूर्णांक64_t diperr:1;
		uपूर्णांक64_t datovr:1;
		uपूर्णांक64_t ovrbst:1;
		uपूर्णांक64_t calpar1:1;
		uपूर्णांक64_t calpar0:1;
	पूर्ण s;
पूर्ण;

जोड़ cvmx_stxx_पूर्णांक_msk अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_stxx_पूर्णांक_msk_s अणु
		uपूर्णांक64_t reserved_8_63:56;
		uपूर्णांक64_t frmerr:1;
		uपूर्णांक64_t unxfrm:1;
		uपूर्णांक64_t nosync:1;
		uपूर्णांक64_t diperr:1;
		uपूर्णांक64_t datovr:1;
		uपूर्णांक64_t ovrbst:1;
		uपूर्णांक64_t calpar1:1;
		uपूर्णांक64_t calpar0:1;
	पूर्ण s;
पूर्ण;

जोड़ cvmx_घात_wq_पूर्णांक_pc अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_घात_wq_पूर्णांक_pc_s अणु
		uपूर्णांक64_t reserved_0_7:8;
		uपूर्णांक64_t pc_thr:20;
		uपूर्णांक64_t reserved_28_31:4;
		uपूर्णांक64_t pc:28;
		uपूर्णांक64_t reserved_60_63:4;
	पूर्ण s;
पूर्ण;

जोड़ cvmx_घात_wq_पूर्णांक_thrx अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_घात_wq_पूर्णांक_thrx_s अणु
		uपूर्णांक64_t reserved_29_63:35;
		uपूर्णांक64_t tc_en:1;
		uपूर्णांक64_t tc_thr:4;
		uपूर्णांक64_t reserved_23_23:1;
		uपूर्णांक64_t ds_thr:11;
		uपूर्णांक64_t reserved_11_11:1;
		uपूर्णांक64_t iq_thr:11;
	पूर्ण s;
	काष्ठा cvmx_घात_wq_पूर्णांक_thrx_cn30xx अणु
		uपूर्णांक64_t reserved_29_63:35;
		uपूर्णांक64_t tc_en:1;
		uपूर्णांक64_t tc_thr:4;
		uपूर्णांक64_t reserved_18_23:6;
		uपूर्णांक64_t ds_thr:6;
		uपूर्णांक64_t reserved_6_11:6;
		uपूर्णांक64_t iq_thr:6;
	पूर्ण cn30xx;
	काष्ठा cvmx_घात_wq_पूर्णांक_thrx_cn31xx अणु
		uपूर्णांक64_t reserved_29_63:35;
		uपूर्णांक64_t tc_en:1;
		uपूर्णांक64_t tc_thr:4;
		uपूर्णांक64_t reserved_20_23:4;
		uपूर्णांक64_t ds_thr:8;
		uपूर्णांक64_t reserved_8_11:4;
		uपूर्णांक64_t iq_thr:8;
	पूर्ण cn31xx;
	काष्ठा cvmx_घात_wq_पूर्णांक_thrx_cn52xx अणु
		uपूर्णांक64_t reserved_29_63:35;
		uपूर्णांक64_t tc_en:1;
		uपूर्णांक64_t tc_thr:4;
		uपूर्णांक64_t reserved_21_23:3;
		uपूर्णांक64_t ds_thr:9;
		uपूर्णांक64_t reserved_9_11:3;
		uपूर्णांक64_t iq_thr:9;
	पूर्ण cn52xx;
	काष्ठा cvmx_घात_wq_पूर्णांक_thrx_cn63xx अणु
		uपूर्णांक64_t reserved_29_63:35;
		uपूर्णांक64_t tc_en:1;
		uपूर्णांक64_t tc_thr:4;
		uपूर्णांक64_t reserved_22_23:2;
		uपूर्णांक64_t ds_thr:10;
		uपूर्णांक64_t reserved_10_11:2;
		uपूर्णांक64_t iq_thr:10;
	पूर्ण cn63xx;
पूर्ण;

जोड़ cvmx_npi_rsl_पूर्णांक_blocks अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npi_rsl_पूर्णांक_blocks_s अणु
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t rपूर्णांक_31:1;
		uपूर्णांक64_t iob:1;
		uपूर्णांक64_t reserved_28_29:2;
		uपूर्णांक64_t rपूर्णांक_27:1;
		uपूर्णांक64_t rपूर्णांक_26:1;
		uपूर्णांक64_t rपूर्णांक_25:1;
		uपूर्णांक64_t rपूर्णांक_24:1;
		uपूर्णांक64_t asx1:1;
		uपूर्णांक64_t asx0:1;
		uपूर्णांक64_t rपूर्णांक_21:1;
		uपूर्णांक64_t pip:1;
		uपूर्णांक64_t spx1:1;
		uपूर्णांक64_t spx0:1;
		uपूर्णांक64_t lmc:1;
		uपूर्णांक64_t l2c:1;
		uपूर्णांक64_t rपूर्णांक_15:1;
		uपूर्णांक64_t reserved_13_14:2;
		uपूर्णांक64_t घात:1;
		uपूर्णांक64_t tim:1;
		uपूर्णांक64_t pko:1;
		uपूर्णांक64_t ipd:1;
		uपूर्णांक64_t rपूर्णांक_8:1;
		uपूर्णांक64_t zip:1;
		uपूर्णांक64_t dfa:1;
		uपूर्णांक64_t fpa:1;
		uपूर्णांक64_t key:1;
		uपूर्णांक64_t npi:1;
		uपूर्णांक64_t gmx1:1;
		uपूर्णांक64_t gmx0:1;
		uपूर्णांक64_t mio:1;
	पूर्ण s;
	काष्ठा cvmx_npi_rsl_पूर्णांक_blocks_cn30xx अणु
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t rपूर्णांक_31:1;
		uपूर्णांक64_t iob:1;
		uपूर्णांक64_t rपूर्णांक_29:1;
		uपूर्णांक64_t rपूर्णांक_28:1;
		uपूर्णांक64_t rपूर्णांक_27:1;
		uपूर्णांक64_t rपूर्णांक_26:1;
		uपूर्णांक64_t rपूर्णांक_25:1;
		uपूर्णांक64_t rपूर्णांक_24:1;
		uपूर्णांक64_t asx1:1;
		uपूर्णांक64_t asx0:1;
		uपूर्णांक64_t rपूर्णांक_21:1;
		uपूर्णांक64_t pip:1;
		uपूर्णांक64_t spx1:1;
		uपूर्णांक64_t spx0:1;
		uपूर्णांक64_t lmc:1;
		uपूर्णांक64_t l2c:1;
		uपूर्णांक64_t rपूर्णांक_15:1;
		uपूर्णांक64_t rपूर्णांक_14:1;
		uपूर्णांक64_t usb:1;
		uपूर्णांक64_t घात:1;
		uपूर्णांक64_t tim:1;
		uपूर्णांक64_t pko:1;
		uपूर्णांक64_t ipd:1;
		uपूर्णांक64_t rपूर्णांक_8:1;
		uपूर्णांक64_t zip:1;
		uपूर्णांक64_t dfa:1;
		uपूर्णांक64_t fpa:1;
		uपूर्णांक64_t key:1;
		uपूर्णांक64_t npi:1;
		uपूर्णांक64_t gmx1:1;
		uपूर्णांक64_t gmx0:1;
		uपूर्णांक64_t mio:1;
	पूर्ण cn30xx;
	काष्ठा cvmx_npi_rsl_पूर्णांक_blocks_cn38xx अणु
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t rपूर्णांक_31:1;
		uपूर्णांक64_t iob:1;
		uपूर्णांक64_t rपूर्णांक_29:1;
		uपूर्णांक64_t rपूर्णांक_28:1;
		uपूर्णांक64_t rपूर्णांक_27:1;
		uपूर्णांक64_t rपूर्णांक_26:1;
		uपूर्णांक64_t rपूर्णांक_25:1;
		uपूर्णांक64_t rपूर्णांक_24:1;
		uपूर्णांक64_t asx1:1;
		uपूर्णांक64_t asx0:1;
		uपूर्णांक64_t rपूर्णांक_21:1;
		uपूर्णांक64_t pip:1;
		uपूर्णांक64_t spx1:1;
		uपूर्णांक64_t spx0:1;
		uपूर्णांक64_t lmc:1;
		uपूर्णांक64_t l2c:1;
		uपूर्णांक64_t rपूर्णांक_15:1;
		uपूर्णांक64_t rपूर्णांक_14:1;
		uपूर्णांक64_t rपूर्णांक_13:1;
		uपूर्णांक64_t घात:1;
		uपूर्णांक64_t tim:1;
		uपूर्णांक64_t pko:1;
		uपूर्णांक64_t ipd:1;
		uपूर्णांक64_t rपूर्णांक_8:1;
		uपूर्णांक64_t zip:1;
		uपूर्णांक64_t dfa:1;
		uपूर्णांक64_t fpa:1;
		uपूर्णांक64_t key:1;
		uपूर्णांक64_t npi:1;
		uपूर्णांक64_t gmx1:1;
		uपूर्णांक64_t gmx0:1;
		uपूर्णांक64_t mio:1;
	पूर्ण cn38xx;
	काष्ठा cvmx_npi_rsl_पूर्णांक_blocks_cn50xx अणु
		uपूर्णांक64_t reserved_31_63:33;
		uपूर्णांक64_t iob:1;
		uपूर्णांक64_t lmc1:1;
		uपूर्णांक64_t agl:1;
		uपूर्णांक64_t reserved_24_27:4;
		uपूर्णांक64_t asx1:1;
		uपूर्णांक64_t asx0:1;
		uपूर्णांक64_t reserved_21_21:1;
		uपूर्णांक64_t pip:1;
		uपूर्णांक64_t spx1:1;
		uपूर्णांक64_t spx0:1;
		uपूर्णांक64_t lmc:1;
		uपूर्णांक64_t l2c:1;
		uपूर्णांक64_t reserved_15_15:1;
		uपूर्णांक64_t rad:1;
		uपूर्णांक64_t usb:1;
		uपूर्णांक64_t घात:1;
		uपूर्णांक64_t tim:1;
		uपूर्णांक64_t pko:1;
		uपूर्णांक64_t ipd:1;
		uपूर्णांक64_t reserved_8_8:1;
		uपूर्णांक64_t zip:1;
		uपूर्णांक64_t dfa:1;
		uपूर्णांक64_t fpa:1;
		uपूर्णांक64_t key:1;
		uपूर्णांक64_t npi:1;
		uपूर्णांक64_t gmx1:1;
		uपूर्णांक64_t gmx0:1;
		uपूर्णांक64_t mio:1;
	पूर्ण cn50xx;
पूर्ण;

जोड़ cvmx_pko_command_word0 अणु
	uपूर्णांक64_t u64;
	काष्ठा अणु
		uपूर्णांक64_t total_bytes:16;
		uपूर्णांक64_t segs:6;
		uपूर्णांक64_t करोntमुक्त:1;
		uपूर्णांक64_t ignore_i:1;
		uपूर्णांक64_t ipoffp1:7;
		uपूर्णांक64_t gather:1;
		uपूर्णांक64_t rsp:1;
		uपूर्णांक64_t wqp:1;
		uपूर्णांक64_t n2:1;
		uपूर्णांक64_t le:1;
		uपूर्णांक64_t reg0:11;
		uपूर्णांक64_t subone0:1;
		uपूर्णांक64_t reg1:11;
		uपूर्णांक64_t subone1:1;
		uपूर्णांक64_t size0:2;
		uपूर्णांक64_t size1:2;
	पूर्ण s;
पूर्ण;

जोड़ cvmx_ciu_timx अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_ciu_timx_s अणु
		uपूर्णांक64_t reserved_37_63:27;
		uपूर्णांक64_t one_shot:1;
		uपूर्णांक64_t len:36;
	पूर्ण s;
पूर्ण;

जोड़ cvmx_gmxx_rxx_rx_inbnd अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_gmxx_rxx_rx_inbnd_s अणु
		uपूर्णांक64_t status:1;
		uपूर्णांक64_t speed:2;
		uपूर्णांक64_t duplex:1;
		uपूर्णांक64_t reserved_4_63:60;
	पूर्ण s;
पूर्ण;

अटल अंतरभूत पूर्णांक32_t cvmx_fau_fetch_and_add32(क्रमागत cvmx_fau_reg_32 reg,
					       पूर्णांक32_t value)
अणु
	वापस value;
पूर्ण

अटल अंतरभूत व्योम cvmx_fau_atomic_add32(क्रमागत cvmx_fau_reg_32 reg,
					 पूर्णांक32_t value)
अणु पूर्ण

अटल अंतरभूत व्योम cvmx_fau_atomic_ग_लिखो32(क्रमागत cvmx_fau_reg_32 reg,
					   पूर्णांक32_t value)
अणु पूर्ण

अटल अंतरभूत uपूर्णांक64_t cvmx_scratch_पढ़ो64(uपूर्णांक64_t address)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम cvmx_scratch_ग_लिखो64(uपूर्णांक64_t address, uपूर्णांक64_t value)
अणु पूर्ण

अटल अंतरभूत पूर्णांक cvmx_wqe_get_grp(काष्ठा cvmx_wqe *work)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम *cvmx_phys_to_ptr(uपूर्णांक64_t physical_address)
अणु
	वापस (व्योम *)(uपूर्णांकptr_t)(physical_address);
पूर्ण

अटल अंतरभूत uपूर्णांक64_t cvmx_ptr_to_phys(व्योम *ptr)
अणु
	वापस (अचिन्हित दीर्घ)ptr;
पूर्ण

अटल अंतरभूत पूर्णांक cvmx_helper_get_पूर्णांकerface_num(पूर्णांक ipd_port)
अणु
	वापस ipd_port;
पूर्ण

अटल अंतरभूत पूर्णांक cvmx_helper_get_पूर्णांकerface_index_num(पूर्णांक ipd_port)
अणु
	वापस ipd_port;
पूर्ण

अटल अंतरभूत व्योम cvmx_fpa_enable(व्योम)
अणु पूर्ण

अटल अंतरभूत uपूर्णांक64_t cvmx_पढ़ो_csr(uपूर्णांक64_t csr_addr)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम cvmx_ग_लिखो_csr(uपूर्णांक64_t csr_addr, uपूर्णांक64_t val)
अणु पूर्ण

अटल अंतरभूत पूर्णांक cvmx_helper_setup_red(पूर्णांक pass_thresh, पूर्णांक drop_thresh)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम *cvmx_fpa_alloc(uपूर्णांक64_t pool)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम cvmx_fpa_मुक्त(व्योम *ptr, uपूर्णांक64_t pool,
				 uपूर्णांक64_t num_cache_lines)
अणु पूर्ण

अटल अंतरभूत पूर्णांक octeon_is_simulation(व्योम)
अणु
	वापस 1;
पूर्ण

अटल अंतरभूत व्योम cvmx_pip_get_port_status(uपूर्णांक64_t port_num, uपूर्णांक64_t clear,
					    cvmx_pip_port_status_t *status)
अणु पूर्ण

अटल अंतरभूत व्योम cvmx_pko_get_port_status(uपूर्णांक64_t port_num, uपूर्णांक64_t clear,
					    cvmx_pko_port_status_t *status)
अणु पूर्ण

अटल अंतरभूत cvmx_helper_पूर्णांकerface_mode_t cvmx_helper_पूर्णांकerface_get_mode(पूर्णांक
								   पूर्णांकerface)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत जोड़ cvmx_helper_link_info cvmx_helper_link_get(पूर्णांक ipd_port)
अणु
	जोड़ cvmx_helper_link_info ret = अणु .u64 = 0 पूर्ण;

	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक cvmx_helper_link_set(पूर्णांक ipd_port,
				       जोड़ cvmx_helper_link_info link_info)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक cvmx_helper_initialize_packet_io_global(व्योम)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक cvmx_helper_get_number_of_पूर्णांकerfaces(व्योम)
अणु
	वापस 2;
पूर्ण

अटल अंतरभूत पूर्णांक cvmx_helper_ports_on_पूर्णांकerface(पूर्णांक पूर्णांकerface)
अणु
	वापस 1;
पूर्ण

अटल अंतरभूत पूर्णांक cvmx_helper_get_ipd_port(पूर्णांक पूर्णांकerface, पूर्णांक port)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक cvmx_helper_ipd_and_packet_input_enable(व्योम)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम cvmx_ipd_disable(व्योम)
अणु पूर्ण

अटल अंतरभूत व्योम cvmx_ipd_मुक्त_ptr(व्योम)
अणु पूर्ण

अटल अंतरभूत व्योम cvmx_pko_disable(व्योम)
अणु पूर्ण

अटल अंतरभूत व्योम cvmx_pko_shutकरोwn(व्योम)
अणु पूर्ण

अटल अंतरभूत पूर्णांक cvmx_pko_get_base_queue_per_core(पूर्णांक port, पूर्णांक core)
अणु
	वापस port;
पूर्ण

अटल अंतरभूत पूर्णांक cvmx_pko_get_base_queue(पूर्णांक port)
अणु
	वापस port;
पूर्ण

अटल अंतरभूत पूर्णांक cvmx_pko_get_num_queues(पूर्णांक port)
अणु
	वापस port;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक cvmx_get_core_num(व्योम)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम cvmx_घात_work_request_async_nocheck(पूर्णांक scr_addr,
						       cvmx_घात_रुको_t रुको)
अणु पूर्ण

अटल अंतरभूत व्योम cvmx_घात_work_request_async(पूर्णांक scr_addr,
					       cvmx_घात_रुको_t रुको)
अणु पूर्ण

अटल अंतरभूत काष्ठा cvmx_wqe *cvmx_घात_work_response_async(पूर्णांक scr_addr)
अणु
	काष्ठा cvmx_wqe *wqe = (व्योम *)(अचिन्हित दीर्घ)scr_addr;

	वापस wqe;
पूर्ण

अटल अंतरभूत काष्ठा cvmx_wqe *cvmx_घात_work_request_sync(cvmx_घात_रुको_t रुको)
अणु
	वापस (व्योम *)(अचिन्हित दीर्घ)रुको;
पूर्ण

अटल अंतरभूत पूर्णांक cvmx_spi_restart_पूर्णांकerface(पूर्णांक पूर्णांकerface,
					cvmx_spi_mode_t mode, पूर्णांक समयout)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम cvmx_fau_async_fetch_and_add32(uपूर्णांक64_t scraddr,
						  क्रमागत cvmx_fau_reg_32 reg,
						  पूर्णांक32_t value)
अणु पूर्ण

अटल अंतरभूत जोड़ cvmx_gmxx_rxx_rx_inbnd cvmx_spi4000_check_speed(
	पूर्णांक पूर्णांकerface,
	पूर्णांक port)
अणु
	जोड़ cvmx_gmxx_rxx_rx_inbnd r;

	r.u64 = 0;
	वापस r;
पूर्ण

अटल अंतरभूत व्योम cvmx_pko_send_packet_prepare(uपूर्णांक64_t port, uपूर्णांक64_t queue,
						cvmx_pko_lock_t use_locking)
अणु पूर्ण

अटल अंतरभूत cvmx_pko_status_t cvmx_pko_send_packet_finish(uपूर्णांक64_t port,
		uपूर्णांक64_t queue, जोड़ cvmx_pko_command_word0 pko_command,
		जोड़ cvmx_buf_ptr packet, cvmx_pko_lock_t use_locking)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम cvmx_wqe_set_port(काष्ठा cvmx_wqe *work, पूर्णांक port)
अणु पूर्ण

अटल अंतरभूत व्योम cvmx_wqe_set_qos(काष्ठा cvmx_wqe *work, पूर्णांक qos)
अणु पूर्ण

अटल अंतरभूत पूर्णांक cvmx_wqe_get_qos(काष्ठा cvmx_wqe *work)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम cvmx_wqe_set_grp(काष्ठा cvmx_wqe *work, पूर्णांक grp)
अणु पूर्ण

अटल अंतरभूत व्योम cvmx_घात_work_submit(काष्ठा cvmx_wqe *wqp, uपूर्णांक32_t tag,
					क्रमागत cvmx_घात_tag_type tag_type,
					uपूर्णांक64_t qos, uपूर्णांक64_t grp)
अणु पूर्ण

#घोषणा CVMX_ASXX_RX_CLK_SETX(a, b)	((a) + (b))
#घोषणा CVMX_ASXX_TX_CLK_SETX(a, b)	((a) + (b))
#घोषणा CVMX_CIU_TIMX(a)		(a)
#घोषणा CVMX_GMXX_RXX_ADR_CAM0(a, b)	((a) + (b))
#घोषणा CVMX_GMXX_RXX_ADR_CAM1(a, b)	((a) + (b))
#घोषणा CVMX_GMXX_RXX_ADR_CAM2(a, b)	((a) + (b))
#घोषणा CVMX_GMXX_RXX_ADR_CAM3(a, b)	((a) + (b))
#घोषणा CVMX_GMXX_RXX_ADR_CAM4(a, b)	((a) + (b))
#घोषणा CVMX_GMXX_RXX_ADR_CAM5(a, b)	((a) + (b))
#घोषणा CVMX_GMXX_RXX_FRM_CTL(a, b)	((a) + (b))
#घोषणा CVMX_GMXX_RXX_INT_REG(a, b)	((a) + (b))
#घोषणा CVMX_GMXX_SMACX(a, b)		((a) + (b))
#घोषणा CVMX_PIP_PRT_TAGX(a)		(a)
#घोषणा CVMX_POW_PP_GRP_MSKX(a)		(a)
#घोषणा CVMX_POW_WQ_INT_THRX(a)		(a)
#घोषणा CVMX_SPXX_INT_MSK(a)		(a)
#घोषणा CVMX_SPXX_INT_REG(a)		(a)
#घोषणा CVMX_SSO_PPX_GRP_MSK(a)		(a)
#घोषणा CVMX_SSO_WQ_INT_THRX(a)		(a)
#घोषणा CVMX_STXX_INT_MSK(a)		(a)
#घोषणा CVMX_STXX_INT_REG(a)		(a)
