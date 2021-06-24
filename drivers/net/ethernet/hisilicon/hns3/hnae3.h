<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
// Copyright (c) 2016-2017 Hisilicon Limited.

#अगर_अघोषित __HNAE3_H
#घोषणा __HNAE3_H

/* Names used in this framework:
 *      ae handle (handle):
 *        a set of queues provided by AE
 *      ring buffer queue (rbq):
 *        the channel between upper layer and the AE, can करो tx and rx
 *      ring:
 *        a tx or rx channel within a rbq
 *      ring description (desc):
 *        an element in the ring with packet inक्रमmation
 *      buffer:
 *        a memory region referred by desc with the full packet payload
 *
 * "num" means a अटल number set as a parameter, "count" mean a dynamic
 *   number set जबतक running
 * "cb" means control block
 */

#समावेश <linux/acpi.h>
#समावेश <linux/dcbnl.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/pci.h>
#समावेश <linux/pkt_sched.h>
#समावेश <linux/types.h>
#समावेश <net/pkt_cls.h>

#घोषणा HNAE3_MOD_VERSION "1.0"

#घोषणा HNAE3_MIN_VECTOR_NUM	2 /* first one क्रम misc, another क्रम IO */

/* Device version */
#घोषणा HNAE3_DEVICE_VERSION_V1   0x00020
#घोषणा HNAE3_DEVICE_VERSION_V2   0x00021
#घोषणा HNAE3_DEVICE_VERSION_V3   0x00030

#घोषणा HNAE3_PCI_REVISION_BIT_SIZE		8

/* Device IDs */
#घोषणा HNAE3_DEV_ID_GE				0xA220
#घोषणा HNAE3_DEV_ID_25GE			0xA221
#घोषणा HNAE3_DEV_ID_25GE_RDMA			0xA222
#घोषणा HNAE3_DEV_ID_25GE_RDMA_MACSEC		0xA223
#घोषणा HNAE3_DEV_ID_50GE_RDMA			0xA224
#घोषणा HNAE3_DEV_ID_50GE_RDMA_MACSEC		0xA225
#घोषणा HNAE3_DEV_ID_100G_RDMA_MACSEC		0xA226
#घोषणा HNAE3_DEV_ID_200G_RDMA			0xA228
#घोषणा HNAE3_DEV_ID_VF				0xA22E
#घोषणा HNAE3_DEV_ID_RDMA_DCB_PFC_VF		0xA22F

#घोषणा HNAE3_CLASS_NAME_SIZE 16

#घोषणा HNAE3_DEV_INITED_B			0x0
#घोषणा HNAE3_DEV_SUPPORT_ROCE_B		0x1
#घोषणा HNAE3_DEV_SUPPORT_DCB_B			0x2
#घोषणा HNAE3_KNIC_CLIENT_INITED_B		0x3
#घोषणा HNAE3_UNIC_CLIENT_INITED_B		0x4
#घोषणा HNAE3_ROCE_CLIENT_INITED_B		0x5

#घोषणा HNAE3_DEV_SUPPORT_ROCE_DCB_BITS (BIT(HNAE3_DEV_SUPPORT_DCB_B) |\
		BIT(HNAE3_DEV_SUPPORT_ROCE_B))

#घोषणा hnae3_dev_roce_supported(hdev) \
	hnae3_get_bit((hdev)->ae_dev->flag, HNAE3_DEV_SUPPORT_ROCE_B)

#घोषणा hnae3_dev_dcb_supported(hdev) \
	hnae3_get_bit((hdev)->ae_dev->flag, HNAE3_DEV_SUPPORT_DCB_B)

क्रमागत HNAE3_DEV_CAP_BITS अणु
	HNAE3_DEV_SUPPORT_FD_B,
	HNAE3_DEV_SUPPORT_GRO_B,
	HNAE3_DEV_SUPPORT_FEC_B,
	HNAE3_DEV_SUPPORT_UDP_GSO_B,
	HNAE3_DEV_SUPPORT_QB_B,
	HNAE3_DEV_SUPPORT_FD_FORWARD_TC_B,
	HNAE3_DEV_SUPPORT_PTP_B,
	HNAE3_DEV_SUPPORT_INT_QL_B,
	HNAE3_DEV_SUPPORT_HW_TX_CSUM_B,
	HNAE3_DEV_SUPPORT_TX_PUSH_B,
	HNAE3_DEV_SUPPORT_PHY_IMP_B,
	HNAE3_DEV_SUPPORT_TQP_TXRX_INDEP_B,
	HNAE3_DEV_SUPPORT_HW_PAD_B,
	HNAE3_DEV_SUPPORT_STASH_B,
	HNAE3_DEV_SUPPORT_UDP_TUNNEL_CSUM_B,
	HNAE3_DEV_SUPPORT_PAUSE_B,
पूर्ण;

#घोषणा hnae3_dev_fd_supported(hdev) \
	test_bit(HNAE3_DEV_SUPPORT_FD_B, (hdev)->ae_dev->caps)

#घोषणा hnae3_dev_gro_supported(hdev) \
	test_bit(HNAE3_DEV_SUPPORT_GRO_B, (hdev)->ae_dev->caps)

#घोषणा hnae3_dev_fec_supported(hdev) \
	test_bit(HNAE3_DEV_SUPPORT_FEC_B, (hdev)->ae_dev->caps)

#घोषणा hnae3_dev_udp_gso_supported(hdev) \
	test_bit(HNAE3_DEV_SUPPORT_UDP_GSO_B, (hdev)->ae_dev->caps)

#घोषणा hnae3_dev_qb_supported(hdev) \
	test_bit(HNAE3_DEV_SUPPORT_QB_B, (hdev)->ae_dev->caps)

#घोषणा hnae3_dev_fd_क्रमward_tc_supported(hdev) \
	test_bit(HNAE3_DEV_SUPPORT_FD_FORWARD_TC_B, (hdev)->ae_dev->caps)

#घोषणा hnae3_dev_ptp_supported(hdev) \
	test_bit(HNAE3_DEV_SUPPORT_PTP_B, (hdev)->ae_dev->caps)

#घोषणा hnae3_dev_पूर्णांक_ql_supported(hdev) \
	test_bit(HNAE3_DEV_SUPPORT_INT_QL_B, (hdev)->ae_dev->caps)

#घोषणा hnae3_dev_hw_csum_supported(hdev) \
	test_bit(HNAE3_DEV_SUPPORT_HW_TX_CSUM_B, (hdev)->ae_dev->caps)

#घोषणा hnae3_dev_tx_push_supported(hdev) \
	test_bit(HNAE3_DEV_SUPPORT_TX_PUSH_B, (hdev)->ae_dev->caps)

#घोषणा hnae3_dev_phy_imp_supported(hdev) \
	test_bit(HNAE3_DEV_SUPPORT_PHY_IMP_B, (hdev)->ae_dev->caps)

#घोषणा hnae3_dev_tqp_txrx_indep_supported(hdev) \
	test_bit(HNAE3_DEV_SUPPORT_TQP_TXRX_INDEP_B, (hdev)->ae_dev->caps)

#घोषणा hnae3_dev_hw_pad_supported(hdev) \
	test_bit(HNAE3_DEV_SUPPORT_HW_PAD_B, (hdev)->ae_dev->caps)

#घोषणा hnae3_dev_stash_supported(hdev) \
	test_bit(HNAE3_DEV_SUPPORT_STASH_B, (hdev)->ae_dev->caps)

#घोषणा hnae3_dev_छोड़ो_supported(hdev) \
	test_bit(HNAE3_DEV_SUPPORT_PAUSE_B, (hdev)->ae_dev->caps)

#घोषणा hnae3_ae_dev_tqp_txrx_indep_supported(ae_dev) \
	test_bit(HNAE3_DEV_SUPPORT_TQP_TXRX_INDEP_B, (ae_dev)->caps)

#घोषणा ring_ptr_move_fw(ring, p) \
	((ring)->p = ((ring)->p + 1) % (ring)->desc_num)
#घोषणा ring_ptr_move_bw(ring, p) \
	((ring)->p = ((ring)->p - 1 + (ring)->desc_num) % (ring)->desc_num)

क्रमागत hns_desc_type अणु
	DESC_TYPE_UNKNOWN,
	DESC_TYPE_SKB,
	DESC_TYPE_FRAGLIST_SKB,
	DESC_TYPE_PAGE,
पूर्ण;

काष्ठा hnae3_handle;

काष्ठा hnae3_queue अणु
	व्योम __iomem *io_base;
	काष्ठा hnae3_ae_algo *ae_algo;
	काष्ठा hnae3_handle *handle;
	पूर्णांक tqp_index;		/* index in a handle */
	u32 buf_size;		/* size क्रम hnae_desc->addr, preset by AE */
	u16 tx_desc_num;	/* total number of tx desc */
	u16 rx_desc_num;	/* total number of rx desc */
पूर्ण;

काष्ठा hns3_mac_stats अणु
	u64 tx_छोड़ो_cnt;
	u64 rx_छोड़ो_cnt;
पूर्ण;

/* hnae3 loop mode */
क्रमागत hnae3_loop अणु
	HNAE3_LOOP_APP,
	HNAE3_LOOP_SERIAL_SERDES,
	HNAE3_LOOP_PARALLEL_SERDES,
	HNAE3_LOOP_PHY,
	HNAE3_LOOP_NONE,
पूर्ण;

क्रमागत hnae3_client_type अणु
	HNAE3_CLIENT_KNIC,
	HNAE3_CLIENT_ROCE,
पूर्ण;

/* mac media type */
क्रमागत hnae3_media_type अणु
	HNAE3_MEDIA_TYPE_UNKNOWN,
	HNAE3_MEDIA_TYPE_FIBER,
	HNAE3_MEDIA_TYPE_COPPER,
	HNAE3_MEDIA_TYPE_BACKPLANE,
	HNAE3_MEDIA_TYPE_NONE,
पूर्ण;

/* must be consistent with definition in firmware */
क्रमागत hnae3_module_type अणु
	HNAE3_MODULE_TYPE_UNKNOWN	= 0x00,
	HNAE3_MODULE_TYPE_FIBRE_LR	= 0x01,
	HNAE3_MODULE_TYPE_FIBRE_SR	= 0x02,
	HNAE3_MODULE_TYPE_AOC		= 0x03,
	HNAE3_MODULE_TYPE_CR		= 0x04,
	HNAE3_MODULE_TYPE_KR		= 0x05,
	HNAE3_MODULE_TYPE_TP		= 0x06,
पूर्ण;

क्रमागत hnae3_fec_mode अणु
	HNAE3_FEC_AUTO = 0,
	HNAE3_FEC_BASER,
	HNAE3_FEC_RS,
	HNAE3_FEC_USER_DEF,
पूर्ण;

क्रमागत hnae3_reset_notअगरy_type अणु
	HNAE3_UP_CLIENT,
	HNAE3_DOWN_CLIENT,
	HNAE3_INIT_CLIENT,
	HNAE3_UNINIT_CLIENT,
पूर्ण;

क्रमागत hnae3_hw_error_type अणु
	HNAE3_PPU_POISON_ERROR,
	HNAE3_CMDQ_ECC_ERROR,
	HNAE3_IMP_RD_POISON_ERROR,
	HNAE3_ROCEE_AXI_RESP_ERROR,
पूर्ण;

क्रमागत hnae3_reset_type अणु
	HNAE3_VF_RESET,
	HNAE3_VF_FUNC_RESET,
	HNAE3_VF_PF_FUNC_RESET,
	HNAE3_VF_FULL_RESET,
	HNAE3_FLR_RESET,
	HNAE3_FUNC_RESET,
	HNAE3_GLOBAL_RESET,
	HNAE3_IMP_RESET,
	HNAE3_UNKNOWN_RESET,
	HNAE3_NONE_RESET,
	HNAE3_MAX_RESET,
पूर्ण;

क्रमागत hnae3_port_base_vlan_state अणु
	HNAE3_PORT_BASE_VLAN_DISABLE,
	HNAE3_PORT_BASE_VLAN_ENABLE,
	HNAE3_PORT_BASE_VLAN_MODIFY,
	HNAE3_PORT_BASE_VLAN_NOCHANGE,
पूर्ण;

काष्ठा hnae3_vector_info अणु
	u8 __iomem *io_addr;
	पूर्णांक vector;
पूर्ण;

#घोषणा HNAE3_RING_TYPE_B 0
#घोषणा HNAE3_RING_TYPE_TX 0
#घोषणा HNAE3_RING_TYPE_RX 1
#घोषणा HNAE3_RING_GL_IDX_S 0
#घोषणा HNAE3_RING_GL_IDX_M GENMASK(1, 0)
#घोषणा HNAE3_RING_GL_RX 0
#घोषणा HNAE3_RING_GL_TX 1

#घोषणा HNAE3_FW_VERSION_BYTE3_SHIFT	24
#घोषणा HNAE3_FW_VERSION_BYTE3_MASK	GENMASK(31, 24)
#घोषणा HNAE3_FW_VERSION_BYTE2_SHIFT	16
#घोषणा HNAE3_FW_VERSION_BYTE2_MASK	GENMASK(23, 16)
#घोषणा HNAE3_FW_VERSION_BYTE1_SHIFT	8
#घोषणा HNAE3_FW_VERSION_BYTE1_MASK	GENMASK(15, 8)
#घोषणा HNAE3_FW_VERSION_BYTE0_SHIFT	0
#घोषणा HNAE3_FW_VERSION_BYTE0_MASK	GENMASK(7, 0)

काष्ठा hnae3_ring_chain_node अणु
	काष्ठा hnae3_ring_chain_node *next;
	u32 tqp_index;
	u32 flag;
	u32 पूर्णांक_gl_idx;
पूर्ण;

#घोषणा HNAE3_IS_TX_RING(node) \
	(((node)->flag & 1 << HNAE3_RING_TYPE_B) == HNAE3_RING_TYPE_TX)

/* device specअगरication info from firmware */
काष्ठा hnae3_dev_specs अणु
	u32 mac_entry_num; /* number of mac-vlan table entry */
	u32 mng_entry_num; /* number of manager table entry */
	u32 max_पंचांग_rate;
	u16 rss_ind_tbl_size;
	u16 rss_key_size;
	u16 पूर्णांक_ql_max; /* max value of पूर्णांकerrupt coalesce based on INT_QL */
	u16 max_पूर्णांक_gl; /* max value of पूर्णांकerrupt coalesce based on INT_GL */
	u8 max_non_tso_bd_num; /* max BD number of one non-TSO packet */
	u16 max_frm_size;
	u16 max_qset_num;
पूर्ण;

काष्ठा hnae3_client_ops अणु
	पूर्णांक (*init_instance)(काष्ठा hnae3_handle *handle);
	व्योम (*uninit_instance)(काष्ठा hnae3_handle *handle, bool reset);
	व्योम (*link_status_change)(काष्ठा hnae3_handle *handle, bool state);
	पूर्णांक (*reset_notअगरy)(काष्ठा hnae3_handle *handle,
			    क्रमागत hnae3_reset_notअगरy_type type);
	व्योम (*process_hw_error)(काष्ठा hnae3_handle *handle,
				 क्रमागत hnae3_hw_error_type);
पूर्ण;

#घोषणा HNAE3_CLIENT_NAME_LENGTH 16
काष्ठा hnae3_client अणु
	अक्षर name[HNAE3_CLIENT_NAME_LENGTH];
	अचिन्हित दीर्घ state;
	क्रमागत hnae3_client_type type;
	स्थिर काष्ठा hnae3_client_ops *ops;
	काष्ठा list_head node;
पूर्ण;

#घोषणा HNAE3_DEV_CAPS_MAX_NUM	96
काष्ठा hnae3_ae_dev अणु
	काष्ठा pci_dev *pdev;
	स्थिर काष्ठा hnae3_ae_ops *ops;
	काष्ठा list_head node;
	u32 flag;
	अचिन्हित दीर्घ hw_err_reset_req;
	काष्ठा hnae3_dev_specs dev_specs;
	u32 dev_version;
	अचिन्हित दीर्घ caps[BITS_TO_LONGS(HNAE3_DEV_CAPS_MAX_NUM)];
	व्योम *priv;
पूर्ण;

/* This काष्ठा defines the operation on the handle.
 *
 * init_ae_dev(): (mandatory)
 *   Get PF configure from pci_dev and initialize PF hardware
 * uninit_ae_dev()
 *   Disable PF device and release PF resource
 * रेजिस्टर_client
 *   Register client to ae_dev
 * unरेजिस्टर_client()
 *   Unरेजिस्टर client from ae_dev
 * start()
 *   Enable the hardware
 * stop()
 *   Disable the hardware
 * start_client()
 *   Inक्रमm the hclge that client has been started
 * stop_client()
 *   Inक्रमm the hclge that client has been stopped
 * get_status()
 *   Get the carrier state of the back channel of the handle, 1 क्रम ok, 0 क्रम
 *   non-ok
 * get_ksettings_an_result()
 *   Get negotiation status,speed and duplex
 * get_media_type()
 *   Get media type of MAC
 * check_port_speed()
 *   Check target speed whether is supported
 * adjust_link()
 *   Adjust link status
 * set_loopback()
 *   Set loopback
 * set_promisc_mode
 *   Set promisc mode
 * request_update_promisc_mode
 *   request to hclge(vf) to update promisc mode
 * set_mtu()
 *   set mtu
 * get_छोड़ोparam()
 *   get tx and rx of छोड़ो frame use
 * set_छोड़ोparam()
 *   set tx and rx of छोड़ो frame use
 * set_स्वतःneg()
 *   set स्वतः स्वतःnegotiation of छोड़ो frame use
 * get_स्वतःneg()
 *   get स्वतः स्वतःnegotiation of छोड़ो frame use
 * restart_स्वतःneg()
 *   restart स्वतःnegotiation
 * halt_स्वतःneg()
 *   halt/resume स्वतःnegotiation when स्वतःnegotiation on
 * get_coalesce_usecs()
 *   get usecs to delay a TX पूर्णांकerrupt after a packet is sent
 * get_rx_max_coalesced_frames()
 *   get Maximum number of packets to be sent beक्रमe a TX पूर्णांकerrupt.
 * set_coalesce_usecs()
 *   set usecs to delay a TX पूर्णांकerrupt after a packet is sent
 * set_coalesce_frames()
 *   set Maximum number of packets to be sent beक्रमe a TX पूर्णांकerrupt.
 * get_mac_addr()
 *   get mac address
 * set_mac_addr()
 *   set mac address
 * add_uc_addr
 *   Add unicast addr to mac table
 * rm_uc_addr
 *   Remove unicast addr from mac table
 * set_mc_addr()
 *   Set multicast address
 * add_mc_addr
 *   Add multicast address to mac table
 * rm_mc_addr
 *   Remove multicast address from mac table
 * update_stats()
 *   Update Old network device statistics
 * get_mac_stats()
 *   get mac छोड़ो statistics including tx_cnt and rx_cnt
 * get_ethtool_stats()
 *   Get ethtool network device statistics
 * get_strings()
 *   Get a set of strings that describe the requested objects
 * get_sset_count()
 *   Get number of strings that @get_strings will ग_लिखो
 * update_led_status()
 *   Update the led status
 * set_led_id()
 *   Set led id
 * get_regs()
 *   Get regs dump
 * get_regs_len()
 *   Get the len of the regs dump
 * get_rss_key_size()
 *   Get rss key size
 * get_rss()
 *   Get rss table
 * set_rss()
 *   Set rss table
 * get_tc_size()
 *   Get tc size of handle
 * get_vector()
 *   Get vector number and vector inक्रमmation
 * put_vector()
 *   Put the vector in hdev
 * map_ring_to_vector()
 *   Map rings to vector
 * unmap_ring_from_vector()
 *   Unmap rings from vector
 * reset_queue()
 *   Reset queue
 * get_fw_version()
 *   Get firmware version
 * get_mdix_mode()
 *   Get media typr of phy
 * enable_vlan_filter()
 *   Enable vlan filter
 * set_vlan_filter()
 *   Set vlan filter config of Ports
 * set_vf_vlan_filter()
 *   Set vlan filter config of vf
 * enable_hw_strip_rxvtag()
 *   Enable/disable hardware strip vlan tag of packets received
 * set_gro_en
 *   Enable/disable HW GRO
 * add_arfs_entry
 *   Check the 5-tuples of flow, and create flow director rule
 * get_vf_config
 *   Get the VF configuration setting by the host
 * set_vf_link_state
 *   Set VF link status
 * set_vf_spoofchk
 *   Enable/disable spoof check क्रम specअगरied vf
 * set_vf_trust
 *   Enable/disable trust क्रम specअगरied vf, अगर the vf being trusted, then
 *   it can enable promisc mode
 * set_vf_rate
 *   Set the max tx rate of specअगरied vf.
 * set_vf_mac
 *   Configure the शेष MAC क्रम specअगरied VF
 * get_module_eeprom
 *   Get the optical module eeprom info.
 * add_cls_flower
 *   Add clsflower rule
 * del_cls_flower
 *   Delete clsflower rule
 * cls_flower_active
 *   Check अगर any cls flower rule exist
 * dbg_पढ़ो_cmd
 *   Execute debugfs पढ़ो command.
 */
काष्ठा hnae3_ae_ops अणु
	पूर्णांक (*init_ae_dev)(काष्ठा hnae3_ae_dev *ae_dev);
	व्योम (*uninit_ae_dev)(काष्ठा hnae3_ae_dev *ae_dev);
	व्योम (*reset_prepare)(काष्ठा hnae3_ae_dev *ae_dev,
			      क्रमागत hnae3_reset_type rst_type);
	व्योम (*reset_करोne)(काष्ठा hnae3_ae_dev *ae_dev);
	पूर्णांक (*init_client_instance)(काष्ठा hnae3_client *client,
				    काष्ठा hnae3_ae_dev *ae_dev);
	व्योम (*uninit_client_instance)(काष्ठा hnae3_client *client,
				       काष्ठा hnae3_ae_dev *ae_dev);
	पूर्णांक (*start)(काष्ठा hnae3_handle *handle);
	व्योम (*stop)(काष्ठा hnae3_handle *handle);
	पूर्णांक (*client_start)(काष्ठा hnae3_handle *handle);
	व्योम (*client_stop)(काष्ठा hnae3_handle *handle);
	पूर्णांक (*get_status)(काष्ठा hnae3_handle *handle);
	व्योम (*get_ksettings_an_result)(काष्ठा hnae3_handle *handle,
					u8 *स्वतः_neg, u32 *speed, u8 *duplex);

	पूर्णांक (*cfg_mac_speed_dup_h)(काष्ठा hnae3_handle *handle, पूर्णांक speed,
				   u8 duplex);

	व्योम (*get_media_type)(काष्ठा hnae3_handle *handle, u8 *media_type,
			       u8 *module_type);
	पूर्णांक (*check_port_speed)(काष्ठा hnae3_handle *handle, u32 speed);
	व्योम (*get_fec)(काष्ठा hnae3_handle *handle, u8 *fec_ability,
			u8 *fec_mode);
	पूर्णांक (*set_fec)(काष्ठा hnae3_handle *handle, u32 fec_mode);
	व्योम (*adjust_link)(काष्ठा hnae3_handle *handle, पूर्णांक speed, पूर्णांक duplex);
	पूर्णांक (*set_loopback)(काष्ठा hnae3_handle *handle,
			    क्रमागत hnae3_loop loop_mode, bool en);

	पूर्णांक (*set_promisc_mode)(काष्ठा hnae3_handle *handle, bool en_uc_pmc,
				bool en_mc_pmc);
	व्योम (*request_update_promisc_mode)(काष्ठा hnae3_handle *handle);
	पूर्णांक (*set_mtu)(काष्ठा hnae3_handle *handle, पूर्णांक new_mtu);

	व्योम (*get_छोड़ोparam)(काष्ठा hnae3_handle *handle,
			       u32 *स्वतः_neg, u32 *rx_en, u32 *tx_en);
	पूर्णांक (*set_छोड़ोparam)(काष्ठा hnae3_handle *handle,
			      u32 स्वतः_neg, u32 rx_en, u32 tx_en);

	पूर्णांक (*set_स्वतःneg)(काष्ठा hnae3_handle *handle, bool enable);
	पूर्णांक (*get_स्वतःneg)(काष्ठा hnae3_handle *handle);
	पूर्णांक (*restart_स्वतःneg)(काष्ठा hnae3_handle *handle);
	पूर्णांक (*halt_स्वतःneg)(काष्ठा hnae3_handle *handle, bool halt);

	व्योम (*get_coalesce_usecs)(काष्ठा hnae3_handle *handle,
				   u32 *tx_usecs, u32 *rx_usecs);
	व्योम (*get_rx_max_coalesced_frames)(काष्ठा hnae3_handle *handle,
					    u32 *tx_frames, u32 *rx_frames);
	पूर्णांक (*set_coalesce_usecs)(काष्ठा hnae3_handle *handle, u32 समयout);
	पूर्णांक (*set_coalesce_frames)(काष्ठा hnae3_handle *handle,
				   u32 coalesce_frames);
	व्योम (*get_coalesce_range)(काष्ठा hnae3_handle *handle,
				   u32 *tx_frames_low, u32 *rx_frames_low,
				   u32 *tx_frames_high, u32 *rx_frames_high,
				   u32 *tx_usecs_low, u32 *rx_usecs_low,
				   u32 *tx_usecs_high, u32 *rx_usecs_high);

	व्योम (*get_mac_addr)(काष्ठा hnae3_handle *handle, u8 *p);
	पूर्णांक (*set_mac_addr)(काष्ठा hnae3_handle *handle, व्योम *p,
			    bool is_first);
	पूर्णांक (*करो_ioctl)(काष्ठा hnae3_handle *handle,
			काष्ठा अगरreq *अगरr, पूर्णांक cmd);
	पूर्णांक (*add_uc_addr)(काष्ठा hnae3_handle *handle,
			   स्थिर अचिन्हित अक्षर *addr);
	पूर्णांक (*rm_uc_addr)(काष्ठा hnae3_handle *handle,
			  स्थिर अचिन्हित अक्षर *addr);
	पूर्णांक (*set_mc_addr)(काष्ठा hnae3_handle *handle, व्योम *addr);
	पूर्णांक (*add_mc_addr)(काष्ठा hnae3_handle *handle,
			   स्थिर अचिन्हित अक्षर *addr);
	पूर्णांक (*rm_mc_addr)(काष्ठा hnae3_handle *handle,
			  स्थिर अचिन्हित अक्षर *addr);
	व्योम (*set_tso_stats)(काष्ठा hnae3_handle *handle, पूर्णांक enable);
	व्योम (*update_stats)(काष्ठा hnae3_handle *handle,
			     काष्ठा net_device_stats *net_stats);
	व्योम (*get_stats)(काष्ठा hnae3_handle *handle, u64 *data);
	व्योम (*get_mac_stats)(काष्ठा hnae3_handle *handle,
			      काष्ठा hns3_mac_stats *mac_stats);
	व्योम (*get_strings)(काष्ठा hnae3_handle *handle,
			    u32 stringset, u8 *data);
	पूर्णांक (*get_sset_count)(काष्ठा hnae3_handle *handle, पूर्णांक stringset);

	व्योम (*get_regs)(काष्ठा hnae3_handle *handle, u32 *version,
			 व्योम *data);
	पूर्णांक (*get_regs_len)(काष्ठा hnae3_handle *handle);

	u32 (*get_rss_key_size)(काष्ठा hnae3_handle *handle);
	पूर्णांक (*get_rss)(काष्ठा hnae3_handle *handle, u32 *indir, u8 *key,
		       u8 *hfunc);
	पूर्णांक (*set_rss)(काष्ठा hnae3_handle *handle, स्थिर u32 *indir,
		       स्थिर u8 *key, स्थिर u8 hfunc);
	पूर्णांक (*set_rss_tuple)(काष्ठा hnae3_handle *handle,
			     काष्ठा ethtool_rxnfc *cmd);
	पूर्णांक (*get_rss_tuple)(काष्ठा hnae3_handle *handle,
			     काष्ठा ethtool_rxnfc *cmd);

	पूर्णांक (*get_tc_size)(काष्ठा hnae3_handle *handle);

	पूर्णांक (*get_vector)(काष्ठा hnae3_handle *handle, u16 vector_num,
			  काष्ठा hnae3_vector_info *vector_info);
	पूर्णांक (*put_vector)(काष्ठा hnae3_handle *handle, पूर्णांक vector_num);
	पूर्णांक (*map_ring_to_vector)(काष्ठा hnae3_handle *handle,
				  पूर्णांक vector_num,
				  काष्ठा hnae3_ring_chain_node *vr_chain);
	पूर्णांक (*unmap_ring_from_vector)(काष्ठा hnae3_handle *handle,
				      पूर्णांक vector_num,
				      काष्ठा hnae3_ring_chain_node *vr_chain);

	पूर्णांक (*reset_queue)(काष्ठा hnae3_handle *handle);
	u32 (*get_fw_version)(काष्ठा hnae3_handle *handle);
	व्योम (*get_mdix_mode)(काष्ठा hnae3_handle *handle,
			      u8 *tp_mdix_ctrl, u8 *tp_mdix);

	व्योम (*enable_vlan_filter)(काष्ठा hnae3_handle *handle, bool enable);
	पूर्णांक (*set_vlan_filter)(काष्ठा hnae3_handle *handle, __be16 proto,
			       u16 vlan_id, bool is_समाप्त);
	पूर्णांक (*set_vf_vlan_filter)(काष्ठा hnae3_handle *handle, पूर्णांक vfid,
				  u16 vlan, u8 qos, __be16 proto);
	पूर्णांक (*enable_hw_strip_rxvtag)(काष्ठा hnae3_handle *handle, bool enable);
	व्योम (*reset_event)(काष्ठा pci_dev *pdev, काष्ठा hnae3_handle *handle);
	क्रमागत hnae3_reset_type (*get_reset_level)(काष्ठा hnae3_ae_dev *ae_dev,
						 अचिन्हित दीर्घ *addr);
	व्योम (*set_शेष_reset_request)(काष्ठा hnae3_ae_dev *ae_dev,
					  क्रमागत hnae3_reset_type rst_type);
	व्योम (*get_channels)(काष्ठा hnae3_handle *handle,
			     काष्ठा ethtool_channels *ch);
	व्योम (*get_tqps_and_rss_info)(काष्ठा hnae3_handle *h,
				      u16 *alloc_tqps, u16 *max_rss_size);
	पूर्णांक (*set_channels)(काष्ठा hnae3_handle *handle, u32 new_tqps_num,
			    bool rxfh_configured);
	व्योम (*get_flowctrl_adv)(काष्ठा hnae3_handle *handle,
				 u32 *flowctrl_adv);
	पूर्णांक (*set_led_id)(काष्ठा hnae3_handle *handle,
			  क्रमागत ethtool_phys_id_state status);
	व्योम (*get_link_mode)(काष्ठा hnae3_handle *handle,
			      अचिन्हित दीर्घ *supported,
			      अचिन्हित दीर्घ *advertising);
	पूर्णांक (*add_fd_entry)(काष्ठा hnae3_handle *handle,
			    काष्ठा ethtool_rxnfc *cmd);
	पूर्णांक (*del_fd_entry)(काष्ठा hnae3_handle *handle,
			    काष्ठा ethtool_rxnfc *cmd);
	पूर्णांक (*get_fd_rule_cnt)(काष्ठा hnae3_handle *handle,
			       काष्ठा ethtool_rxnfc *cmd);
	पूर्णांक (*get_fd_rule_info)(काष्ठा hnae3_handle *handle,
				काष्ठा ethtool_rxnfc *cmd);
	पूर्णांक (*get_fd_all_rules)(काष्ठा hnae3_handle *handle,
				काष्ठा ethtool_rxnfc *cmd, u32 *rule_locs);
	व्योम (*enable_fd)(काष्ठा hnae3_handle *handle, bool enable);
	पूर्णांक (*add_arfs_entry)(काष्ठा hnae3_handle *handle, u16 queue_id,
			      u16 flow_id, काष्ठा flow_keys *fkeys);
	पूर्णांक (*dbg_run_cmd)(काष्ठा hnae3_handle *handle, स्थिर अक्षर *cmd_buf);
	पूर्णांक (*dbg_पढ़ो_cmd)(काष्ठा hnae3_handle *handle, स्थिर अक्षर *cmd_buf,
			    अक्षर *buf, पूर्णांक len);
	pci_ers_result_t (*handle_hw_ras_error)(काष्ठा hnae3_ae_dev *ae_dev);
	bool (*get_hw_reset_stat)(काष्ठा hnae3_handle *handle);
	bool (*ae_dev_resetting)(काष्ठा hnae3_handle *handle);
	अचिन्हित दीर्घ (*ae_dev_reset_cnt)(काष्ठा hnae3_handle *handle);
	पूर्णांक (*set_gro_en)(काष्ठा hnae3_handle *handle, bool enable);
	u16 (*get_global_queue_id)(काष्ठा hnae3_handle *handle, u16 queue_id);
	व्योम (*set_समयr_task)(काष्ठा hnae3_handle *handle, bool enable);
	पूर्णांक (*mac_connect_phy)(काष्ठा hnae3_handle *handle);
	व्योम (*mac_disconnect_phy)(काष्ठा hnae3_handle *handle);
	पूर्णांक (*get_vf_config)(काष्ठा hnae3_handle *handle, पूर्णांक vf,
			     काष्ठा अगरla_vf_info *ivf);
	पूर्णांक (*set_vf_link_state)(काष्ठा hnae3_handle *handle, पूर्णांक vf,
				 पूर्णांक link_state);
	पूर्णांक (*set_vf_spoofchk)(काष्ठा hnae3_handle *handle, पूर्णांक vf,
			       bool enable);
	पूर्णांक (*set_vf_trust)(काष्ठा hnae3_handle *handle, पूर्णांक vf, bool enable);
	पूर्णांक (*set_vf_rate)(काष्ठा hnae3_handle *handle, पूर्णांक vf,
			   पूर्णांक min_tx_rate, पूर्णांक max_tx_rate, bool क्रमce);
	पूर्णांक (*set_vf_mac)(काष्ठा hnae3_handle *handle, पूर्णांक vf, u8 *p);
	पूर्णांक (*get_module_eeprom)(काष्ठा hnae3_handle *handle, u32 offset,
				 u32 len, u8 *data);
	bool (*get_cmdq_stat)(काष्ठा hnae3_handle *handle);
	पूर्णांक (*add_cls_flower)(काष्ठा hnae3_handle *handle,
			      काष्ठा flow_cls_offload *cls_flower, पूर्णांक tc);
	पूर्णांक (*del_cls_flower)(काष्ठा hnae3_handle *handle,
			      काष्ठा flow_cls_offload *cls_flower);
	bool (*cls_flower_active)(काष्ठा hnae3_handle *handle);
	पूर्णांक (*get_phy_link_ksettings)(काष्ठा hnae3_handle *handle,
				      काष्ठा ethtool_link_ksettings *cmd);
	पूर्णांक (*set_phy_link_ksettings)(काष्ठा hnae3_handle *handle,
				      स्थिर काष्ठा ethtool_link_ksettings *cmd);
पूर्ण;

काष्ठा hnae3_dcb_ops अणु
	/* IEEE 802.1Qaz std */
	पूर्णांक (*ieee_getets)(काष्ठा hnae3_handle *, काष्ठा ieee_ets *);
	पूर्णांक (*ieee_setets)(काष्ठा hnae3_handle *, काष्ठा ieee_ets *);
	पूर्णांक (*ieee_getpfc)(काष्ठा hnae3_handle *, काष्ठा ieee_pfc *);
	पूर्णांक (*ieee_setpfc)(काष्ठा hnae3_handle *, काष्ठा ieee_pfc *);

	/* DCBX configuration */
	u8   (*getdcbx)(काष्ठा hnae3_handle *);
	u8   (*setdcbx)(काष्ठा hnae3_handle *, u8);

	पूर्णांक (*setup_tc)(काष्ठा hnae3_handle *handle,
			काष्ठा tc_mqprio_qopt_offload *mqprio_qopt);
पूर्ण;

काष्ठा hnae3_ae_algo अणु
	स्थिर काष्ठा hnae3_ae_ops *ops;
	काष्ठा list_head node;
	स्थिर काष्ठा pci_device_id *pdev_id_table;
पूर्ण;

#घोषणा HNAE3_INT_NAME_LEN        32
#घोषणा HNAE3_ITR_COUNTDOWN_START 100

#घोषणा HNAE3_MAX_TC		8
#घोषणा HNAE3_MAX_USER_PRIO	8
काष्ठा hnae3_tc_info अणु
	u8 prio_tc[HNAE3_MAX_USER_PRIO]; /* TC indexed by prio */
	u16 tqp_count[HNAE3_MAX_TC];
	u16 tqp_offset[HNAE3_MAX_TC];
	अचिन्हित दीर्घ tc_en; /* biपंचांगap of TC enabled */
	u8 num_tc; /* Total number of enabled TCs */
	bool mqprio_active;
पूर्ण;

काष्ठा hnae3_knic_निजी_info अणु
	काष्ठा net_device *netdev; /* Set by KNIC client when init instance */
	u16 rss_size;		   /* Allocated RSS queues */
	u16 req_rss_size;
	u16 rx_buf_len;
	u16 num_tx_desc;
	u16 num_rx_desc;

	काष्ठा hnae3_tc_info tc_info;

	u16 num_tqps;		  /* total number of TQPs in this handle */
	काष्ठा hnae3_queue **tqp;  /* array base of all TQPs in this instance */
	स्थिर काष्ठा hnae3_dcb_ops *dcb_ops;

	u16 पूर्णांक_rl_setting;
	क्रमागत pkt_hash_types rss_type;
पूर्ण;

काष्ठा hnae3_roce_निजी_info अणु
	काष्ठा net_device *netdev;
	व्योम __iomem *roce_io_base;
	व्योम __iomem *roce_mem_base;
	पूर्णांक base_vector;
	पूर्णांक num_vectors;

	/* The below attributes defined क्रम RoCE client, hnae3 gives
	 * initial values to them, and RoCE client can modअगरy and use
	 * them.
	 */
	अचिन्हित दीर्घ reset_state;
	अचिन्हित दीर्घ instance_state;
	अचिन्हित दीर्घ state;
पूर्ण;

#घोषणा HNAE3_SUPPORT_APP_LOOPBACK    BIT(0)
#घोषणा HNAE3_SUPPORT_PHY_LOOPBACK    BIT(1)
#घोषणा HNAE3_SUPPORT_SERDES_SERIAL_LOOPBACK	BIT(2)
#घोषणा HNAE3_SUPPORT_VF	      BIT(3)
#घोषणा HNAE3_SUPPORT_SERDES_PARALLEL_LOOPBACK	BIT(4)

#घोषणा HNAE3_USER_UPE		BIT(0)	/* unicast promisc enabled by user */
#घोषणा HNAE3_USER_MPE		BIT(1)	/* mulitcast promisc enabled by user */
#घोषणा HNAE3_BPE		BIT(2)	/* broadcast promisc enable */
#घोषणा HNAE3_OVERFLOW_UPE	BIT(3)	/* unicast mac vlan overflow */
#घोषणा HNAE3_OVERFLOW_MPE	BIT(4)	/* multicast mac vlan overflow */
#घोषणा HNAE3_VLAN_FLTR		BIT(5)	/* enable vlan filter */
#घोषणा HNAE3_UPE		(HNAE3_USER_UPE | HNAE3_OVERFLOW_UPE)
#घोषणा HNAE3_MPE		(HNAE3_USER_MPE | HNAE3_OVERFLOW_MPE)

क्रमागत hnae3_pflag अणु
	HNAE3_PFLAG_LIMIT_PROMISC,
	HNAE3_PFLAG_MAX
पूर्ण;

काष्ठा hnae3_handle अणु
	काष्ठा hnae3_client *client;
	काष्ठा pci_dev *pdev;
	व्योम *priv;
	काष्ठा hnae3_ae_algo *ae_algo;  /* the class who provides this handle */
	u64 flags; /* Indicate the capabilities क्रम this handle */

	जोड़ अणु
		काष्ठा net_device *netdev; /* first member */
		काष्ठा hnae3_knic_निजी_info kinfo;
		काष्ठा hnae3_roce_निजी_info rinfo;
	पूर्ण;

	u32 numa_node_mask;	/* क्रम multi-chip support */

	क्रमागत hnae3_port_base_vlan_state port_base_vlan_state;

	u8 netdev_flags;
	काष्ठा dentry *hnae3_dbgfs;

	/* Network पूर्णांकerface message level enabled bits */
	u32 msg_enable;

	अचिन्हित दीर्घ supported_pflags;
	अचिन्हित दीर्घ priv_flags;
पूर्ण;

#घोषणा hnae3_set_field(origin, mask, shअगरt, val) \
	करो अणु \
		(origin) &= (~(mask)); \
		(origin) |= ((val) << (shअगरt)) & (mask); \
	पूर्ण जबतक (0)
#घोषणा hnae3_get_field(origin, mask, shअगरt) (((origin) & (mask)) >> (shअगरt))

#घोषणा hnae3_set_bit(origin, shअगरt, val) \
	hnae3_set_field(origin, 0x1 << (shअगरt), shअगरt, val)
#घोषणा hnae3_get_bit(origin, shअगरt) \
	hnae3_get_field(origin, 0x1 << (shअगरt), shअगरt)

#घोषणा HNAE3_DBG_TM_NODES		"tm_nodes"
#घोषणा HNAE3_DBG_TM_PRI		"tm_priority"
#घोषणा HNAE3_DBG_TM_QSET		"tm_qset"

पूर्णांक hnae3_रेजिस्टर_ae_dev(काष्ठा hnae3_ae_dev *ae_dev);
व्योम hnae3_unरेजिस्टर_ae_dev(काष्ठा hnae3_ae_dev *ae_dev);

व्योम hnae3_unरेजिस्टर_ae_algo(काष्ठा hnae3_ae_algo *ae_algo);
व्योम hnae3_रेजिस्टर_ae_algo(काष्ठा hnae3_ae_algo *ae_algo);

व्योम hnae3_unरेजिस्टर_client(काष्ठा hnae3_client *client);
पूर्णांक hnae3_रेजिस्टर_client(काष्ठा hnae3_client *client);

व्योम hnae3_set_client_init_flag(काष्ठा hnae3_client *client,
				काष्ठा hnae3_ae_dev *ae_dev,
				अचिन्हित पूर्णांक inited);
#पूर्ण_अगर
