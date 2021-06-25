<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-3-Clause) */
/* QLogic qed NIC Driver
 * Copyright (c) 2015-2017  QLogic Corporation
 * Copyright (c) 2019-2020 Marvell International Ltd.
 */

#अगर_अघोषित _QED_MCP_H
#घोषणा _QED_MCP_H

#समावेश <linux/types.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/qed/qed_fcoe_अगर.h>
#समावेश "qed_hsi.h"
#समावेश "qed_dev_api.h"

काष्ठा qed_mcp_link_speed_params अणु
	bool					स्वतःneg;

	u32					advertised_speeds;
#घोषणा QED_EXT_SPEED_MASK_RES			0x1
#घोषणा QED_EXT_SPEED_MASK_1G			0x2
#घोषणा QED_EXT_SPEED_MASK_10G			0x4
#घोषणा QED_EXT_SPEED_MASK_20G			0x8
#घोषणा QED_EXT_SPEED_MASK_25G			0x10
#घोषणा QED_EXT_SPEED_MASK_40G			0x20
#घोषणा QED_EXT_SPEED_MASK_50G_R		0x40
#घोषणा QED_EXT_SPEED_MASK_50G_R2		0x80
#घोषणा QED_EXT_SPEED_MASK_100G_R2		0x100
#घोषणा QED_EXT_SPEED_MASK_100G_R4		0x200
#घोषणा QED_EXT_SPEED_MASK_100G_P4		0x400

	u32					क्रमced_speed;	   /* In Mb/s */
#घोषणा QED_EXT_SPEED_1G			0x1
#घोषणा QED_EXT_SPEED_10G			0x2
#घोषणा QED_EXT_SPEED_20G			0x4
#घोषणा QED_EXT_SPEED_25G			0x8
#घोषणा QED_EXT_SPEED_40G			0x10
#घोषणा QED_EXT_SPEED_50G_R			0x20
#घोषणा QED_EXT_SPEED_50G_R2			0x40
#घोषणा QED_EXT_SPEED_100G_R2			0x80
#घोषणा QED_EXT_SPEED_100G_R4			0x100
#घोषणा QED_EXT_SPEED_100G_P4			0x200
पूर्ण;

काष्ठा qed_mcp_link_छोड़ो_params अणु
	bool					स्वतःneg;
	bool					क्रमced_rx;
	bool					क्रमced_tx;
पूर्ण;

क्रमागत qed_mcp_eee_mode अणु
	QED_MCP_EEE_DISABLED,
	QED_MCP_EEE_ENABLED,
	QED_MCP_EEE_UNSUPPORTED
पूर्ण;

काष्ठा qed_mcp_link_params अणु
	काष्ठा qed_mcp_link_speed_params	speed;
	काष्ठा qed_mcp_link_छोड़ो_params	छोड़ो;
	u32					loopback_mode;
	काष्ठा qed_link_eee_params		eee;
	u32					fec;

	काष्ठा qed_mcp_link_speed_params	ext_speed;
	u32					ext_fec_mode;
पूर्ण;

काष्ठा qed_mcp_link_capabilities अणु
	u32					speed_capabilities;
	bool					शेष_speed_स्वतःneg;
	u32					fec_शेष;
	क्रमागत qed_mcp_eee_mode			शेष_eee;
	u32					eee_lpi_समयr;
	u8					eee_speed_caps;

	u32					शेष_ext_speed_caps;
	u32					शेष_ext_स्वतःneg;
	u32					शेष_ext_speed;
	u32					शेष_ext_fec;
पूर्ण;

काष्ठा qed_mcp_link_state अणु
	bool					link_up;
	u32					min_pf_rate;

	/* Actual link speed in Mb/s */
	u32					line_speed;

	/* PF max speed in Mb/s, deduced from line_speed
	 * according to PF max bandwidth configuration.
	 */
	u32					speed;

	bool					full_duplex;
	bool					an;
	bool					an_complete;
	bool					parallel_detection;
	bool					pfc_enabled;

	u32					partner_adv_speed;
#घोषणा QED_LINK_PARTNER_SPEED_1G_HD		BIT(0)
#घोषणा QED_LINK_PARTNER_SPEED_1G_FD		BIT(1)
#घोषणा QED_LINK_PARTNER_SPEED_10G		BIT(2)
#घोषणा QED_LINK_PARTNER_SPEED_20G		BIT(3)
#घोषणा QED_LINK_PARTNER_SPEED_25G		BIT(4)
#घोषणा QED_LINK_PARTNER_SPEED_40G		BIT(5)
#घोषणा QED_LINK_PARTNER_SPEED_50G		BIT(6)
#घोषणा QED_LINK_PARTNER_SPEED_100G		BIT(7)

	bool					partner_tx_flow_ctrl_en;
	bool					partner_rx_flow_ctrl_en;

	u8					partner_adv_छोड़ो;
#घोषणा QED_LINK_PARTNER_SYMMETRIC_PAUSE	0x1
#घोषणा QED_LINK_PARTNER_ASYMMETRIC_PAUSE	0x2
#घोषणा QED_LINK_PARTNER_BOTH_PAUSE		0x3

	bool					sfp_tx_fault;
	bool					eee_active;
	u8					eee_adv_caps;
	u8					eee_lp_adv_caps;

	u32					fec_active;
पूर्ण;

काष्ठा qed_mcp_function_info अणु
	u8				छोड़ो_on_host;

	क्रमागत qed_pci_personality	protocol;

	u8				bandwidth_min;
	u8				bandwidth_max;

	u8				mac[ETH_ALEN];

	u64				wwn_port;
	u64				wwn_node;

#घोषणा QED_MCP_VLAN_UNSET              (0xffff)
	u16				ovlan;

	u16				mtu;
पूर्ण;

काष्ठा qed_mcp_nvm_common अणु
	u32	offset;
	u32	param;
	u32	resp;
	u32	cmd;
पूर्ण;

काष्ठा qed_mcp_drv_version अणु
	u32	version;
	u8	name[MCP_DRV_VER_STR_SIZE - 4];
पूर्ण;

काष्ठा qed_mcp_lan_stats अणु
	u64 ucast_rx_pkts;
	u64 ucast_tx_pkts;
	u32 fcs_err;
पूर्ण;

काष्ठा qed_mcp_fcoe_stats अणु
	u64 rx_pkts;
	u64 tx_pkts;
	u32 fcs_err;
	u32 login_failure;
पूर्ण;

काष्ठा qed_mcp_iscsi_stats अणु
	u64 rx_pdus;
	u64 tx_pdus;
	u64 rx_bytes;
	u64 tx_bytes;
पूर्ण;

काष्ठा qed_mcp_rdma_stats अणु
	u64 rx_pkts;
	u64 tx_pkts;
	u64 rx_bytes;
	u64 tx_byts;
पूर्ण;

क्रमागत qed_mcp_protocol_type अणु
	QED_MCP_LAN_STATS,
	QED_MCP_FCOE_STATS,
	QED_MCP_ISCSI_STATS,
	QED_MCP_RDMA_STATS
पूर्ण;

जोड़ qed_mcp_protocol_stats अणु
	काष्ठा qed_mcp_lan_stats lan_stats;
	काष्ठा qed_mcp_fcoe_stats fcoe_stats;
	काष्ठा qed_mcp_iscsi_stats iscsi_stats;
	काष्ठा qed_mcp_rdma_stats rdma_stats;
पूर्ण;

क्रमागत qed_ov_eचयन अणु
	QED_OV_ESWITCH_NONE,
	QED_OV_ESWITCH_VEB,
	QED_OV_ESWITCH_VEPA
पूर्ण;

क्रमागत qed_ov_client अणु
	QED_OV_CLIENT_DRV,
	QED_OV_CLIENT_USER,
	QED_OV_CLIENT_VENDOR_SPEC
पूर्ण;

क्रमागत qed_ov_driver_state अणु
	QED_OV_DRIVER_STATE_NOT_LOADED,
	QED_OV_DRIVER_STATE_DISABLED,
	QED_OV_DRIVER_STATE_ACTIVE
पूर्ण;

क्रमागत qed_ov_wol अणु
	QED_OV_WOL_DEFAULT,
	QED_OV_WOL_DISABLED,
	QED_OV_WOL_ENABLED
पूर्ण;

क्रमागत qed_mfw_tlv_type अणु
	QED_MFW_TLV_GENERIC = 0x1,	/* Core driver TLVs */
	QED_MFW_TLV_ETH = 0x2,		/* L2 driver TLVs */
	QED_MFW_TLV_FCOE = 0x4,		/* FCoE protocol TLVs */
	QED_MFW_TLV_ISCSI = 0x8,	/* SCSI protocol TLVs */
	QED_MFW_TLV_MAX = 0x16,
पूर्ण;

काष्ठा qed_mfw_tlv_generic अणु
#घोषणा QED_MFW_TLV_FLAGS_SIZE	2
	काष्ठा अणु
		u8 ipv4_csum_offload;
		u8 lso_supported;
		bool b_set;
	पूर्ण flags;

#घोषणा QED_MFW_TLV_MAC_COUNT 3
	/* First entry क्रम primary MAC, 2 secondary MACs possible */
	u8 mac[QED_MFW_TLV_MAC_COUNT][6];
	bool mac_set[QED_MFW_TLV_MAC_COUNT];

	u64 rx_frames;
	bool rx_frames_set;
	u64 rx_bytes;
	bool rx_bytes_set;
	u64 tx_frames;
	bool tx_frames_set;
	u64 tx_bytes;
	bool tx_bytes_set;
पूर्ण;

जोड़ qed_mfw_tlv_data अणु
	काष्ठा qed_mfw_tlv_generic generic;
	काष्ठा qed_mfw_tlv_eth eth;
	काष्ठा qed_mfw_tlv_fcoe fcoe;
	काष्ठा qed_mfw_tlv_iscsi iscsi;
पूर्ण;

#घोषणा QED_NVM_CFG_OPTION_ALL		BIT(0)
#घोषणा QED_NVM_CFG_OPTION_INIT		BIT(1)
#घोषणा QED_NVM_CFG_OPTION_COMMIT       BIT(2)
#घोषणा QED_NVM_CFG_OPTION_FREE		BIT(3)
#घोषणा QED_NVM_CFG_OPTION_ENTITY_SEL	BIT(4)

/**
 * @brief - वापसs the link params of the hw function
 *
 * @param p_hwfn
 *
 * @वापसs poपूर्णांकer to link params
 */
काष्ठा qed_mcp_link_params *qed_mcp_get_link_params(काष्ठा qed_hwfn *);

/**
 * @brief - वापस the link state of the hw function
 *
 * @param p_hwfn
 *
 * @वापसs poपूर्णांकer to link state
 */
काष्ठा qed_mcp_link_state *qed_mcp_get_link_state(काष्ठा qed_hwfn *);

/**
 * @brief - वापस the link capabilities of the hw function
 *
 * @param p_hwfn
 *
 * @वापसs poपूर्णांकer to link capabilities
 */
काष्ठा qed_mcp_link_capabilities
	*qed_mcp_get_link_capabilities(काष्ठा qed_hwfn *p_hwfn);

/**
 * @brief Request the MFW to set the the link according to 'link_input'.
 *
 * @param p_hwfn
 * @param p_ptt
 * @param b_up - उठाओ link अगर `true'. Reset link if `false'.
 *
 * @वापस पूर्णांक
 */
पूर्णांक qed_mcp_set_link(काष्ठा qed_hwfn   *p_hwfn,
		     काष्ठा qed_ptt     *p_ptt,
		     bool               b_up);

/**
 * @brief Get the management firmware version value
 *
 * @param p_hwfn
 * @param p_ptt
 * @param p_mfw_ver    - mfw version value
 * @param p_running_bundle_id	- image id in nvram; Optional.
 *
 * @वापस पूर्णांक - 0 - operation was successful.
 */
पूर्णांक qed_mcp_get_mfw_ver(काष्ठा qed_hwfn *p_hwfn,
			काष्ठा qed_ptt *p_ptt,
			u32 *p_mfw_ver, u32 *p_running_bundle_id);

/**
 * @brief Get the MBI version value
 *
 * @param p_hwfn
 * @param p_ptt
 * @param p_mbi_ver - A poपूर्णांकer to a variable to be filled with the MBI version.
 *
 * @वापस पूर्णांक - 0 - operation was successful.
 */
पूर्णांक qed_mcp_get_mbi_ver(काष्ठा qed_hwfn *p_hwfn,
			काष्ठा qed_ptt *p_ptt, u32 *p_mbi_ver);

/**
 * @brief Get media type value of the port.
 *
 * @param cdev      - qed dev poपूर्णांकer
 * @param p_ptt
 * @param mfw_ver    - media type value
 *
 * @वापस पूर्णांक -
 *      0 - Operation was successul.
 *      -EBUSY - Operation failed
 */
पूर्णांक qed_mcp_get_media_type(काष्ठा qed_hwfn *p_hwfn,
			   काष्ठा qed_ptt *p_ptt, u32 *media_type);

/**
 * @brief Get transceiver data of the port.
 *
 * @param cdev      - qed dev poपूर्णांकer
 * @param p_ptt
 * @param p_transceiver_state - transceiver state.
 * @param p_transceiver_type - media type value
 *
 * @वापस पूर्णांक -
 *      0 - Operation was successful.
 *      -EBUSY - Operation failed
 */
पूर्णांक qed_mcp_get_transceiver_data(काष्ठा qed_hwfn *p_hwfn,
				 काष्ठा qed_ptt *p_ptt,
				 u32 *p_transceiver_state,
				 u32 *p_tranceiver_type);

/**
 * @brief Get transceiver supported speed mask.
 *
 * @param cdev      - qed dev poपूर्णांकer
 * @param p_ptt
 * @param p_speed_mask - Bit mask of all supported speeds.
 *
 * @वापस पूर्णांक -
 *      0 - Operation was successful.
 *      -EBUSY - Operation failed
 */

पूर्णांक qed_mcp_trans_speed_mask(काष्ठा qed_hwfn *p_hwfn,
			     काष्ठा qed_ptt *p_ptt, u32 *p_speed_mask);

/**
 * @brief Get board configuration.
 *
 * @param cdev      - qed dev poपूर्णांकer
 * @param p_ptt
 * @param p_board_config - Board config.
 *
 * @वापस पूर्णांक -
 *      0 - Operation was successful.
 *      -EBUSY - Operation failed
 */
पूर्णांक qed_mcp_get_board_config(काष्ठा qed_hwfn *p_hwfn,
			     काष्ठा qed_ptt *p_ptt, u32 *p_board_config);

/**
 * @brief General function क्रम sending commands to the MCP
 *        mailbox. It acquire mutex lock क्रम the entire
 *        operation, from sending the request until the MCP
 *        response. Waiting क्रम MCP response will be checked up
 *        to 5 seconds every 5ms.
 *
 * @param p_hwfn     - hw function
 * @param p_ptt      - PTT required क्रम रेजिस्टर access
 * @param cmd        - command to be sent to the MCP.
 * @param param      - Optional param
 * @param o_mcp_resp - The MCP response code (exclude sequence).
 * @param o_mcp_param- Optional parameter provided by the MCP
 *                     response
 * @वापस पूर्णांक - 0 - operation
 * was successul.
 */
पूर्णांक qed_mcp_cmd(काष्ठा qed_hwfn *p_hwfn,
		काष्ठा qed_ptt *p_ptt,
		u32 cmd,
		u32 param,
		u32 *o_mcp_resp,
		u32 *o_mcp_param);

/**
 * @brief - drains the nig, allowing completion to pass in हाल of छोड़ोs.
 *          (Should be called only from sleepable context)
 *
 * @param p_hwfn
 * @param p_ptt
 */
पूर्णांक qed_mcp_drain(काष्ठा qed_hwfn *p_hwfn,
		  काष्ठा qed_ptt *p_ptt);

/**
 * @brief Get the flash size value
 *
 * @param p_hwfn
 * @param p_ptt
 * @param p_flash_size  - flash size in bytes to be filled.
 *
 * @वापस पूर्णांक - 0 - operation was successul.
 */
पूर्णांक qed_mcp_get_flash_size(काष्ठा qed_hwfn     *p_hwfn,
			   काष्ठा qed_ptt       *p_ptt,
			   u32 *p_flash_size);

/**
 * @brief Send driver version to MFW
 *
 * @param p_hwfn
 * @param p_ptt
 * @param version - Version value
 * @param name - Protocol driver name
 *
 * @वापस पूर्णांक - 0 - operation was successul.
 */
पूर्णांक
qed_mcp_send_drv_version(काष्ठा qed_hwfn *p_hwfn,
			 काष्ठा qed_ptt *p_ptt,
			 काष्ठा qed_mcp_drv_version *p_ver);

/**
 * @brief Read the MFW process समाप्त counter
 *
 * @param p_hwfn
 * @param p_ptt
 *
 * @वापस u32
 */
u32 qed_get_process_समाप्त_counter(काष्ठा qed_hwfn *p_hwfn,
				 काष्ठा qed_ptt *p_ptt);

/**
 * @brief Trigger a recovery process
 *
 *  @param p_hwfn
 *  @param p_ptt
 *
 * @वापस पूर्णांक
 */
पूर्णांक qed_start_recovery_process(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_ptt *p_ptt);

/**
 * @brief A recovery handler must call this function as its first step.
 *        It is assumed that the handler is not run from an पूर्णांकerrupt context.
 *
 *  @param cdev
 *  @param p_ptt
 *
 * @वापस पूर्णांक
 */
पूर्णांक qed_recovery_prolog(काष्ठा qed_dev *cdev);

/**
 * @brief Notअगरy MFW about the change in base device properties
 *
 *  @param p_hwfn
 *  @param p_ptt
 *  @param client - qed client type
 *
 * @वापस पूर्णांक - 0 - operation was successful.
 */
पूर्णांक qed_mcp_ov_update_current_config(काष्ठा qed_hwfn *p_hwfn,
				     काष्ठा qed_ptt *p_ptt,
				     क्रमागत qed_ov_client client);

/**
 * @brief Notअगरy MFW about the driver state
 *
 *  @param p_hwfn
 *  @param p_ptt
 *  @param drv_state - Driver state
 *
 * @वापस पूर्णांक - 0 - operation was successful.
 */
पूर्णांक qed_mcp_ov_update_driver_state(काष्ठा qed_hwfn *p_hwfn,
				   काष्ठा qed_ptt *p_ptt,
				   क्रमागत qed_ov_driver_state drv_state);

/**
 * @brief Send MTU size to MFW
 *
 *  @param p_hwfn
 *  @param p_ptt
 *  @param mtu - MTU size
 *
 * @वापस पूर्णांक - 0 - operation was successful.
 */
पूर्णांक qed_mcp_ov_update_mtu(काष्ठा qed_hwfn *p_hwfn,
			  काष्ठा qed_ptt *p_ptt, u16 mtu);

/**
 * @brief Send MAC address to MFW
 *
 *  @param p_hwfn
 *  @param p_ptt
 *  @param mac - MAC address
 *
 * @वापस पूर्णांक - 0 - operation was successful.
 */
पूर्णांक qed_mcp_ov_update_mac(काष्ठा qed_hwfn *p_hwfn,
			  काष्ठा qed_ptt *p_ptt, u8 *mac);

/**
 * @brief Send WOL mode to MFW
 *
 *  @param p_hwfn
 *  @param p_ptt
 *  @param wol - WOL mode
 *
 * @वापस पूर्णांक - 0 - operation was successful.
 */
पूर्णांक qed_mcp_ov_update_wol(काष्ठा qed_hwfn *p_hwfn,
			  काष्ठा qed_ptt *p_ptt,
			  क्रमागत qed_ov_wol wol);

/**
 * @brief Set LED status
 *
 *  @param p_hwfn
 *  @param p_ptt
 *  @param mode - LED mode
 *
 * @वापस पूर्णांक - 0 - operation was successful.
 */
पूर्णांक qed_mcp_set_led(काष्ठा qed_hwfn *p_hwfn,
		    काष्ठा qed_ptt *p_ptt,
		    क्रमागत qed_led_mode mode);

/**
 * @brief Read from nvm
 *
 *  @param cdev
 *  @param addr - nvm offset
 *  @param p_buf - nvm पढ़ो buffer
 *  @param len - buffer len
 *
 * @वापस पूर्णांक - 0 - operation was successful.
 */
पूर्णांक qed_mcp_nvm_पढ़ो(काष्ठा qed_dev *cdev, u32 addr, u8 *p_buf, u32 len);

/**
 * @brief Write to nvm
 *
 *  @param cdev
 *  @param addr - nvm offset
 *  @param cmd - nvm command
 *  @param p_buf - nvm ग_लिखो buffer
 *  @param len - buffer len
 *
 * @वापस पूर्णांक - 0 - operation was successful.
 */
पूर्णांक qed_mcp_nvm_ग_लिखो(काष्ठा qed_dev *cdev,
		      u32 cmd, u32 addr, u8 *p_buf, u32 len);

/**
 * @brief Check latest response
 *
 *  @param cdev
 *  @param p_buf - nvm ग_लिखो buffer
 *
 * @वापस पूर्णांक - 0 - operation was successful.
 */
पूर्णांक qed_mcp_nvm_resp(काष्ठा qed_dev *cdev, u8 *p_buf);

काष्ठा qed_nvm_image_att अणु
	u32 start_addr;
	u32 length;
पूर्ण;

/**
 * @brief Allows पढ़ोing a whole nvram image
 *
 * @param p_hwfn
 * @param image_id - image to get attributes क्रम
 * @param p_image_att - image attributes काष्ठाure पूर्णांकo which to fill data
 *
 * @वापस पूर्णांक - 0 - operation was successful.
 */
पूर्णांक
qed_mcp_get_nvm_image_att(काष्ठा qed_hwfn *p_hwfn,
			  क्रमागत qed_nvm_images image_id,
			  काष्ठा qed_nvm_image_att *p_image_att);

/**
 * @brief Allows पढ़ोing a whole nvram image
 *
 * @param p_hwfn
 * @param image_id - image requested क्रम पढ़ोing
 * @param p_buffer - allocated buffer पूर्णांकo which to fill data
 * @param buffer_len - length of the allocated buffer.
 *
 * @वापस 0 अगरf p_buffer now contains the nvram image.
 */
पूर्णांक qed_mcp_get_nvm_image(काष्ठा qed_hwfn *p_hwfn,
			  क्रमागत qed_nvm_images image_id,
			  u8 *p_buffer, u32 buffer_len);

/**
 * @brief Bist रेजिस्टर test
 *
 *  @param p_hwfn    - hw function
 *  @param p_ptt     - PTT required क्रम रेजिस्टर access
 *
 * @वापस पूर्णांक - 0 - operation was successful.
 */
पूर्णांक qed_mcp_bist_रेजिस्टर_test(काष्ठा qed_hwfn *p_hwfn,
			       काष्ठा qed_ptt *p_ptt);

/**
 * @brief Bist घड़ी test
 *
 *  @param p_hwfn    - hw function
 *  @param p_ptt     - PTT required क्रम रेजिस्टर access
 *
 * @वापस पूर्णांक - 0 - operation was successful.
 */
पूर्णांक qed_mcp_bist_घड़ी_प्रकारest(काष्ठा qed_hwfn *p_hwfn,
			    काष्ठा qed_ptt *p_ptt);

/**
 * @brief Bist nvm test - get number of images
 *
 *  @param p_hwfn       - hw function
 *  @param p_ptt        - PTT required क्रम रेजिस्टर access
 *  @param num_images   - number of images अगर operation was
 *			  successful. 0 अगर not.
 *
 * @वापस पूर्णांक - 0 - operation was successful.
 */
पूर्णांक qed_mcp_bist_nvm_get_num_images(काष्ठा qed_hwfn *p_hwfn,
				    काष्ठा qed_ptt *p_ptt,
				    u32 *num_images);

/**
 * @brief Bist nvm test - get image attributes by index
 *
 *  @param p_hwfn      - hw function
 *  @param p_ptt       - PTT required क्रम रेजिस्टर access
 *  @param p_image_att - Attributes of image
 *  @param image_index - Index of image to get inक्रमmation क्रम
 *
 * @वापस पूर्णांक - 0 - operation was successful.
 */
पूर्णांक qed_mcp_bist_nvm_get_image_att(काष्ठा qed_hwfn *p_hwfn,
				   काष्ठा qed_ptt *p_ptt,
				   काष्ठा bist_nvm_image_att *p_image_att,
				   u32 image_index);

/**
 * @brief - Processes the TLV request from MFW i.e., get the required TLV info
 *          from the qed client and send it to the MFW.
 *
 * @param p_hwfn
 * @param p_ptt
 *
 * @param वापस 0 upon success.
 */
पूर्णांक qed_mfw_process_tlv_req(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_ptt *p_ptt);

/**
 * @brief Send raw debug data to the MFW
 *
 * @param p_hwfn
 * @param p_ptt
 * @param p_buf - raw debug data buffer
 * @param size - buffer size
 */
पूर्णांक
qed_mcp_send_raw_debug_data(काष्ठा qed_hwfn *p_hwfn,
			    काष्ठा qed_ptt *p_ptt, u8 *p_buf, u32 size);

/* Using hwfn number (and not pf_num) is required since in CMT mode,
 * same pf_num may be used by two dअगरferent hwfn
 * TODO - this shouldn't really be in .h file, but until all fields
 * required during hw-init will be placed in their correct place in shmem
 * we need it in qed_dev.c [क्रम पढ़ोin the nvram reflection in shmem].
 */
#घोषणा MCP_PF_ID_BY_REL(p_hwfn, rel_pfid) (QED_IS_BB((p_hwfn)->cdev) ?	       \
					    ((rel_pfid) |		       \
					     ((p_hwfn)->असल_pf_id & 1) << 3) : \
					    rel_pfid)
#घोषणा MCP_PF_ID(p_hwfn) MCP_PF_ID_BY_REL(p_hwfn, (p_hwfn)->rel_pf_id)

काष्ठा qed_mcp_info अणु
	/* List क्रम mailbox commands which were sent and रुको क्रम a response */
	काष्ठा list_head			cmd_list;

	/* Spinlock used क्रम protecting the access to the mailbox commands list
	 * and the sending of the commands.
	 */
	spinlock_t				cmd_lock;

	/* Flag to indicate whether sending a MFW mailbox command is blocked */
	bool					b_block_cmd;

	/* Spinlock used क्रम syncing SW link-changes and link-changes
	 * originating from attention context.
	 */
	spinlock_t				link_lock;

	u32					खुला_base;
	u32					drv_mb_addr;
	u32					mfw_mb_addr;
	u32					port_addr;
	u16					drv_mb_seq;
	u16					drv_pulse_seq;
	काष्ठा qed_mcp_link_params		link_input;
	काष्ठा qed_mcp_link_state		link_output;
	काष्ठा qed_mcp_link_capabilities	link_capabilities;
	काष्ठा qed_mcp_function_info		func_info;
	u8					*mfw_mb_cur;
	u8					*mfw_mb_shaकरोw;
	u16					mfw_mb_length;
	u32					mcp_hist;

	/* Capabilties negotiated with the MFW */
	u32					capabilities;

	/* S/N क्रम debug data mailbox commands */
	atomic_t dbg_data_seq;
पूर्ण;

काष्ठा qed_mcp_mb_params अणु
	u32 cmd;
	u32 param;
	व्योम *p_data_src;
	व्योम *p_data_dst;
	u8 data_src_size;
	u8 data_dst_size;
	u32 mcp_resp;
	u32 mcp_param;
	u32 flags;
#घोषणा QED_MB_FLAG_CAN_SLEEP	(0x1 << 0)
#घोषणा QED_MB_FLAG_AVOID_BLOCK	(0x1 << 1)
#घोषणा QED_MB_FLAGS_IS_SET(params, flag) \
	(अणु typeof(params) __params = (params); \
	   (__params && (__params->flags & QED_MB_FLAG_ ## flag)); पूर्ण)
पूर्ण;

काष्ठा qed_drv_tlv_hdr अणु
	u8 tlv_type;
	u8 tlv_length;	/* In dwords - not including this header */
	u8 tlv_reserved;
#घोषणा QED_DRV_TLV_FLAGS_CHANGED 0x01
	u8 tlv_flags;
पूर्ण;

/**
 * qed_mcp_is_ext_speed_supported() - Check अगर management firmware supports
 *                                    extended speeds.
 * @p_hwfn: HW device data.
 *
 * Return: true अगर supported, false otherwise.
 */
अटल अंतरभूत bool
qed_mcp_is_ext_speed_supported(स्थिर काष्ठा qed_hwfn *p_hwfn)
अणु
	वापस !!(p_hwfn->mcp_info->capabilities &
		  FW_MB_PARAM_FEATURE_SUPPORT_EXT_SPEED_FEC_CONTROL);
पूर्ण

/**
 * @brief Initialize the पूर्णांकerface with the MCP
 *
 * @param p_hwfn - HW func
 * @param p_ptt - PTT required क्रम रेजिस्टर access
 *
 * @वापस पूर्णांक
 */
पूर्णांक qed_mcp_cmd_init(काष्ठा qed_hwfn *p_hwfn,
		     काष्ठा qed_ptt *p_ptt);

/**
 * @brief Initialize the port पूर्णांकerface with the MCP
 *
 * @param p_hwfn
 * @param p_ptt
 * Can only be called after `num_ports_in_engines' is set
 */
व्योम qed_mcp_cmd_port_init(काष्ठा qed_hwfn *p_hwfn,
			   काष्ठा qed_ptt *p_ptt);
/**
 * @brief Releases resources allocated during the init process.
 *
 * @param p_hwfn - HW func
 * @param p_ptt - PTT required क्रम रेजिस्टर access
 *
 * @वापस पूर्णांक
 */

पूर्णांक qed_mcp_मुक्त(काष्ठा qed_hwfn *p_hwfn);

/**
 * @brief This function is called from the DPC context. After
 * poपूर्णांकing PTT to the mfw mb, check क्रम events sent by the MCP
 * to the driver and ack them. In हाल a critical event
 * detected, it will be handled here, otherwise the work will be
 * queued to a sleepable work-queue.
 *
 * @param p_hwfn - HW function
 * @param p_ptt - PTT required क्रम रेजिस्टर access
 * @वापस पूर्णांक - 0 - operation
 * was successul.
 */
पूर्णांक qed_mcp_handle_events(काष्ठा qed_hwfn *p_hwfn,
			  काष्ठा qed_ptt *p_ptt);

क्रमागत qed_drv_role अणु
	QED_DRV_ROLE_OS,
	QED_DRV_ROLE_KDUMP,
पूर्ण;

काष्ठा qed_load_req_params अणु
	/* Input params */
	क्रमागत qed_drv_role drv_role;
	u8 समयout_val;
	bool aव्योम_eng_reset;
	क्रमागत qed_override_क्रमce_load override_क्रमce_load;

	/* Output params */
	u32 load_code;
पूर्ण;

/**
 * @brief Sends a LOAD_REQ to the MFW, and in हाल the operation succeeds,
 *        वापसs whether this PF is the first on the engine/port or function.
 *
 * @param p_hwfn
 * @param p_ptt
 * @param p_params
 *
 * @वापस पूर्णांक - 0 - Operation was successful.
 */
पूर्णांक qed_mcp_load_req(काष्ठा qed_hwfn *p_hwfn,
		     काष्ठा qed_ptt *p_ptt,
		     काष्ठा qed_load_req_params *p_params);

/**
 * @brief Sends a LOAD_DONE message to the MFW
 *
 * @param p_hwfn
 * @param p_ptt
 *
 * @वापस पूर्णांक - 0 - Operation was successful.
 */
पूर्णांक qed_mcp_load_करोne(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_ptt *p_ptt);

/**
 * @brief Sends a UNLOAD_REQ message to the MFW
 *
 * @param p_hwfn
 * @param p_ptt
 *
 * @वापस पूर्णांक - 0 - Operation was successful.
 */
पूर्णांक qed_mcp_unload_req(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_ptt *p_ptt);

/**
 * @brief Sends a UNLOAD_DONE message to the MFW
 *
 * @param p_hwfn
 * @param p_ptt
 *
 * @वापस पूर्णांक - 0 - Operation was successful.
 */
पूर्णांक qed_mcp_unload_करोne(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_ptt *p_ptt);

/**
 * @brief Read the MFW mailbox पूर्णांकo Current buffer.
 *
 * @param p_hwfn
 * @param p_ptt
 */
व्योम qed_mcp_पढ़ो_mb(काष्ठा qed_hwfn *p_hwfn,
		     काष्ठा qed_ptt *p_ptt);

/**
 * @brief Ack to mfw that driver finished FLR process क्रम VFs
 *
 * @param p_hwfn
 * @param p_ptt
 * @param vfs_to_ack - bit mask of all engine VFs क्रम which the PF acks.
 *
 * @param वापस पूर्णांक - 0 upon success.
 */
पूर्णांक qed_mcp_ack_vf_flr(काष्ठा qed_hwfn *p_hwfn,
		       काष्ठा qed_ptt *p_ptt, u32 *vfs_to_ack);

/**
 * @brief - calls during init to पढ़ो shmem of all function-related info.
 *
 * @param p_hwfn
 *
 * @param वापस 0 upon success.
 */
पूर्णांक qed_mcp_fill_shmem_func_info(काष्ठा qed_hwfn *p_hwfn,
				 काष्ठा qed_ptt *p_ptt);

/**
 * @brief - Reset the MCP using mailbox command.
 *
 * @param p_hwfn
 * @param p_ptt
 *
 * @param वापस 0 upon success.
 */
पूर्णांक qed_mcp_reset(काष्ठा qed_hwfn *p_hwfn,
		  काष्ठा qed_ptt *p_ptt);

/**
 * @brief - Sends an NVM पढ़ो command request to the MFW to get
 *        a buffer.
 *
 * @param p_hwfn
 * @param p_ptt
 * @param cmd - Command: DRV_MSG_CODE_NVM_GET_खाता_DATA or
 *            DRV_MSG_CODE_NVM_READ_NVRAM commands
 * @param param - [0:23] - Offset [24:31] - Size
 * @param o_mcp_resp - MCP response
 * @param o_mcp_param - MCP response param
 * @param o_txn_size -  Buffer size output
 * @param o_buf - Poपूर्णांकer to the buffer वापसed by the MFW.
 *
 * @param वापस 0 upon success.
 */
पूर्णांक qed_mcp_nvm_rd_cmd(काष्ठा qed_hwfn *p_hwfn,
		       काष्ठा qed_ptt *p_ptt,
		       u32 cmd,
		       u32 param,
		       u32 *o_mcp_resp,
		       u32 *o_mcp_param, u32 *o_txn_size, u32 *o_buf);

/**
 * @brief Read from sfp
 *
 *  @param p_hwfn - hw function
 *  @param p_ptt  - PTT required क्रम रेजिस्टर access
 *  @param port   - transceiver port
 *  @param addr   - I2C address
 *  @param offset - offset in sfp
 *  @param len    - buffer length
 *  @param p_buf  - buffer to पढ़ो पूर्णांकo
 *
 * @वापस पूर्णांक - 0 - operation was successful.
 */
पूर्णांक qed_mcp_phy_sfp_पढ़ो(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_ptt *p_ptt,
			 u32 port, u32 addr, u32 offset, u32 len, u8 *p_buf);

/**
 * @brief indicates whether the MFW objects [under mcp_info] are accessible
 *
 * @param p_hwfn
 *
 * @वापस true अगरf MFW is running and mcp_info is initialized
 */
bool qed_mcp_is_init(काष्ठा qed_hwfn *p_hwfn);

/**
 * @brief request MFW to configure MSI-X क्रम a VF
 *
 * @param p_hwfn
 * @param p_ptt
 * @param vf_id - असलolute inside engine
 * @param num_sbs - number of entries to request
 *
 * @वापस पूर्णांक
 */
पूर्णांक qed_mcp_config_vf_msix(काष्ठा qed_hwfn *p_hwfn,
			   काष्ठा qed_ptt *p_ptt, u8 vf_id, u8 num);

/**
 * @brief - Halt the MCP.
 *
 * @param p_hwfn
 * @param p_ptt
 *
 * @param वापस 0 upon success.
 */
पूर्णांक qed_mcp_halt(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_ptt *p_ptt);

/**
 * @brief - Wake up the MCP.
 *
 * @param p_hwfn
 * @param p_ptt
 *
 * @param वापस 0 upon success.
 */
पूर्णांक qed_mcp_resume(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_ptt *p_ptt);

पूर्णांक qed_configure_pf_min_bandwidth(काष्ठा qed_dev *cdev, u8 min_bw);
पूर्णांक qed_configure_pf_max_bandwidth(काष्ठा qed_dev *cdev, u8 max_bw);
पूर्णांक __qed_configure_pf_max_bandwidth(काष्ठा qed_hwfn *p_hwfn,
				     काष्ठा qed_ptt *p_ptt,
				     काष्ठा qed_mcp_link_state *p_link,
				     u8 max_bw);
पूर्णांक __qed_configure_pf_min_bandwidth(काष्ठा qed_hwfn *p_hwfn,
				     काष्ठा qed_ptt *p_ptt,
				     काष्ठा qed_mcp_link_state *p_link,
				     u8 min_bw);

पूर्णांक qed_mcp_mask_parities(काष्ठा qed_hwfn *p_hwfn,
			  काष्ठा qed_ptt *p_ptt, u32 mask_parities);

/* @brief - Gets the mdump retained data from the MFW.
 *
 * @param p_hwfn
 * @param p_ptt
 * @param p_mdump_retain
 *
 * @param वापस 0 upon success.
 */
पूर्णांक
qed_mcp_mdump_get_retain(काष्ठा qed_hwfn *p_hwfn,
			 काष्ठा qed_ptt *p_ptt,
			 काष्ठा mdump_retain_data_stc *p_mdump_retain);

/**
 * @brief - Sets the MFW's max value क्रम the given resource
 *
 *  @param p_hwfn
 *  @param p_ptt
 *  @param res_id
 *  @param resc_max_val
 *  @param p_mcp_resp
 *
 * @वापस पूर्णांक - 0 - operation was successful.
 */
पूर्णांक
qed_mcp_set_resc_max_val(काष्ठा qed_hwfn *p_hwfn,
			 काष्ठा qed_ptt *p_ptt,
			 क्रमागत qed_resources res_id,
			 u32 resc_max_val, u32 *p_mcp_resp);

/**
 * @brief - Gets the MFW allocation info क्रम the given resource
 *
 *  @param p_hwfn
 *  @param p_ptt
 *  @param res_id
 *  @param p_mcp_resp
 *  @param p_resc_num
 *  @param p_resc_start
 *
 * @वापस पूर्णांक - 0 - operation was successful.
 */
पूर्णांक
qed_mcp_get_resc_info(काष्ठा qed_hwfn *p_hwfn,
		      काष्ठा qed_ptt *p_ptt,
		      क्रमागत qed_resources res_id,
		      u32 *p_mcp_resp, u32 *p_resc_num, u32 *p_resc_start);

/**
 * @brief Send eचयन mode to MFW
 *
 *  @param p_hwfn
 *  @param p_ptt
 *  @param eचयन - eचयन mode
 *
 * @वापस पूर्णांक - 0 - operation was successful.
 */
पूर्णांक qed_mcp_ov_update_eचयन(काष्ठा qed_hwfn *p_hwfn,
			      काष्ठा qed_ptt *p_ptt,
			      क्रमागत qed_ov_eचयन eचयन);

#घोषणा QED_MCP_RESC_LOCK_MIN_VAL       RESOURCE_DUMP
#घोषणा QED_MCP_RESC_LOCK_MAX_VAL       31

क्रमागत qed_resc_lock अणु
	QED_RESC_LOCK_DBG_DUMP = QED_MCP_RESC_LOCK_MIN_VAL,
	QED_RESC_LOCK_PTP_PORT0,
	QED_RESC_LOCK_PTP_PORT1,
	QED_RESC_LOCK_PTP_PORT2,
	QED_RESC_LOCK_PTP_PORT3,
	QED_RESC_LOCK_RESC_ALLOC = QED_MCP_RESC_LOCK_MAX_VAL,
	QED_RESC_LOCK_RESC_INVALID
पूर्ण;

/**
 * @brief - Initiates PF FLR
 *
 *  @param p_hwfn
 *  @param p_ptt
 *
 * @वापस पूर्णांक - 0 - operation was successful.
 */
पूर्णांक qed_mcp_initiate_pf_flr(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_ptt *p_ptt);
काष्ठा qed_resc_lock_params अणु
	/* Resource number [valid values are 0..31] */
	u8 resource;

	/* Lock समयout value in seconds [शेष, none or 1..254] */
	u8 समयout;
#घोषणा QED_MCP_RESC_LOCK_TO_DEFAULT    0
#घोषणा QED_MCP_RESC_LOCK_TO_NONE       255

	/* Number of बार to retry locking */
	u8 retry_num;
#घोषणा QED_MCP_RESC_LOCK_RETRY_CNT_DFLT        10

	/* The पूर्णांकerval in usec between retries */
	u16 retry_पूर्णांकerval;
#घोषणा QED_MCP_RESC_LOCK_RETRY_VAL_DFLT        10000

	/* Use sleep or delay between retries */
	bool sleep_b4_retry;

	/* Will be set as true अगर the resource is मुक्त and granted */
	bool b_granted;

	/* Will be filled with the resource owner.
	 * [0..15 = PF0-15, 16 = MFW]
	 */
	u8 owner;
पूर्ण;

/**
 * @brief Acquires MFW generic resource lock
 *
 *  @param p_hwfn
 *  @param p_ptt
 *  @param p_params
 *
 * @वापस पूर्णांक - 0 - operation was successful.
 */
पूर्णांक
qed_mcp_resc_lock(काष्ठा qed_hwfn *p_hwfn,
		  काष्ठा qed_ptt *p_ptt, काष्ठा qed_resc_lock_params *p_params);

काष्ठा qed_resc_unlock_params अणु
	/* Resource number [valid values are 0..31] */
	u8 resource;

	/* Allow to release a resource even अगर beदीर्घs to another PF */
	bool b_क्रमce;

	/* Will be set as true अगर the resource is released */
	bool b_released;
पूर्ण;

/**
 * @brief Releases MFW generic resource lock
 *
 *  @param p_hwfn
 *  @param p_ptt
 *  @param p_params
 *
 * @वापस पूर्णांक - 0 - operation was successful.
 */
पूर्णांक
qed_mcp_resc_unlock(काष्ठा qed_hwfn *p_hwfn,
		    काष्ठा qed_ptt *p_ptt,
		    काष्ठा qed_resc_unlock_params *p_params);

/**
 * @brief - शेष initialization क्रम lock/unlock resource काष्ठाs
 *
 * @param p_lock - lock params काष्ठा to be initialized; Can be शून्य
 * @param p_unlock - unlock params काष्ठा to be initialized; Can be शून्य
 * @param resource - the requested resource
 * @paral b_is_permanent - disable retries & aging when set
 */
व्योम qed_mcp_resc_lock_शेष_init(काष्ठा qed_resc_lock_params *p_lock,
				    काष्ठा qed_resc_unlock_params *p_unlock,
				    क्रमागत qed_resc_lock
				    resource, bool b_is_permanent);

/**
 * @brief - Return whether management firmware support smart AN
 *
 * @param p_hwfn
 *
 * @वापस bool - true अगर feature is supported.
 */
bool qed_mcp_is_smart_an_supported(काष्ठा qed_hwfn *p_hwfn);

/**
 * @brief Learn of supported MFW features; To be करोne during early init
 *
 * @param p_hwfn
 * @param p_ptt
 */
पूर्णांक qed_mcp_get_capabilities(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_ptt *p_ptt);

/**
 * @brief Inक्रमm MFW of set of features supported by driver. Should be करोne
 * inside the content of the LOAD_REQ.
 *
 * @param p_hwfn
 * @param p_ptt
 */
पूर्णांक qed_mcp_set_capabilities(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_ptt *p_ptt);

/**
 * @brief Read ufp config from the shared memory.
 *
 * @param p_hwfn
 * @param p_ptt
 */
व्योम qed_mcp_पढ़ो_ufp_config(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_ptt *p_ptt);

/**
 * @brief Populate the nvm info shaकरोw in the given hardware function
 *
 * @param p_hwfn
 */
पूर्णांक qed_mcp_nvm_info_populate(काष्ठा qed_hwfn *p_hwfn);

/**
 * @brief Delete nvm info shaकरोw in the given hardware function
 *
 * @param p_hwfn
 */
व्योम qed_mcp_nvm_info_मुक्त(काष्ठा qed_hwfn *p_hwfn);

/**
 * @brief Get the engine affinity configuration.
 *
 * @param p_hwfn
 * @param p_ptt
 */
पूर्णांक qed_mcp_get_engine_config(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_ptt *p_ptt);

/**
 * @brief Get the PPFID biपंचांगap.
 *
 * @param p_hwfn
 * @param p_ptt
 */
पूर्णांक qed_mcp_get_ppfid_biपंचांगap(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_ptt *p_ptt);

/**
 * @brief Get NVM config attribute value.
 *
 * @param p_hwfn
 * @param p_ptt
 * @param option_id
 * @param entity_id
 * @param flags
 * @param p_buf
 * @param p_len
 */
पूर्णांक qed_mcp_nvm_get_cfg(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_ptt *p_ptt,
			u16 option_id, u8 entity_id, u16 flags, u8 *p_buf,
			u32 *p_len);

/**
 * @brief Set NVM config attribute value.
 *
 * @param p_hwfn
 * @param p_ptt
 * @param option_id
 * @param entity_id
 * @param flags
 * @param p_buf
 * @param len
 */
पूर्णांक qed_mcp_nvm_set_cfg(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_ptt *p_ptt,
			u16 option_id, u8 entity_id, u16 flags, u8 *p_buf,
			u32 len);
#पूर्ण_अगर
