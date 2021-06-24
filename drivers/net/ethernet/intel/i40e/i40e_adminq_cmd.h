<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright(c) 2013 - 2021 Intel Corporation. */

#अगर_अघोषित _I40E_ADMINQ_CMD_H_
#घोषणा _I40E_ADMINQ_CMD_H_

/* This header file defines the i40e Admin Queue commands and is shared between
 * i40e Firmware and Software.
 *
 * This file needs to comply with the Linux Kernel coding style.
 */

#घोषणा I40E_FW_API_VERSION_MAJOR	0x0001
#घोषणा I40E_FW_API_VERSION_MINOR_X722	0x0009
#घोषणा I40E_FW_API_VERSION_MINOR_X710	0x0009

#घोषणा I40E_FW_MINOR_VERSION(_h) ((_h)->mac.type == I40E_MAC_XL710 ? \
					I40E_FW_API_VERSION_MINOR_X710 : \
					I40E_FW_API_VERSION_MINOR_X722)

/* API version 1.7 implements additional link and PHY-specअगरic APIs  */
#घोषणा I40E_MINOR_VER_GET_LINK_INFO_XL710 0x0007
/* API version 1.9 क्रम X722 implements additional link and PHY-specअगरic APIs */
#घोषणा I40E_MINOR_VER_GET_LINK_INFO_X722 0x0009
/* API version 1.6 क्रम X722 devices adds ability to stop FW LLDP agent */
#घोषणा I40E_MINOR_VER_FW_LLDP_STOPPABLE_X722 0x0006
/* API version 1.10 क्रम X722 devices adds ability to request FEC encoding */
#घोषणा I40E_MINOR_VER_FW_REQUEST_FEC_X722 0x000A

काष्ठा i40e_aq_desc अणु
	__le16 flags;
	__le16 opcode;
	__le16 datalen;
	__le16 retval;
	__le32 cookie_high;
	__le32 cookie_low;
	जोड़ अणु
		काष्ठा अणु
			__le32 param0;
			__le32 param1;
			__le32 param2;
			__le32 param3;
		पूर्ण पूर्णांकernal;
		काष्ठा अणु
			__le32 param0;
			__le32 param1;
			__le32 addr_high;
			__le32 addr_low;
		पूर्ण बाह्यal;
		u8 raw[16];
	पूर्ण params;
पूर्ण;

/* Flags sub-काष्ठाure
 * |0  |1  |2  |3  |4  |5  |6  |7  |8  |9  |10 |11 |12 |13 |14 |15 |
 * |DD |CMP|ERR|VFE| * *  RESERVED * * |LB |RD |VFC|BUF|SI |EI |FE |
 */

/* command flags and offsets*/
#घोषणा I40E_AQ_FLAG_ERR_SHIFT	2
#घोषणा I40E_AQ_FLAG_LB_SHIFT	9
#घोषणा I40E_AQ_FLAG_RD_SHIFT	10
#घोषणा I40E_AQ_FLAG_BUF_SHIFT	12
#घोषणा I40E_AQ_FLAG_SI_SHIFT	13

#घोषणा I40E_AQ_FLAG_ERR	BIT(I40E_AQ_FLAG_ERR_SHIFT) /* 0x4    */
#घोषणा I40E_AQ_FLAG_LB		BIT(I40E_AQ_FLAG_LB_SHIFT)  /* 0x200  */
#घोषणा I40E_AQ_FLAG_RD		BIT(I40E_AQ_FLAG_RD_SHIFT)  /* 0x400  */
#घोषणा I40E_AQ_FLAG_BUF	BIT(I40E_AQ_FLAG_BUF_SHIFT) /* 0x1000 */
#घोषणा I40E_AQ_FLAG_SI		BIT(I40E_AQ_FLAG_SI_SHIFT)  /* 0x2000 */

/* error codes */
क्रमागत i40e_admin_queue_err अणु
	I40E_AQ_RC_OK		= 0,  /* success */
	I40E_AQ_RC_EPERM	= 1,  /* Operation not permitted */
	I40E_AQ_RC_ENOENT	= 2,  /* No such element */
	I40E_AQ_RC_ESRCH	= 3,  /* Bad opcode */
	I40E_AQ_RC_EINTR	= 4,  /* operation पूर्णांकerrupted */
	I40E_AQ_RC_EIO		= 5,  /* I/O error */
	I40E_AQ_RC_ENXIO	= 6,  /* No such resource */
	I40E_AQ_RC_E2BIG	= 7,  /* Arg too दीर्घ */
	I40E_AQ_RC_EAGAIN	= 8,  /* Try again */
	I40E_AQ_RC_ENOMEM	= 9,  /* Out of memory */
	I40E_AQ_RC_EACCES	= 10, /* Permission denied */
	I40E_AQ_RC_EFAULT	= 11, /* Bad address */
	I40E_AQ_RC_EBUSY	= 12, /* Device or resource busy */
	I40E_AQ_RC_EEXIST	= 13, /* object alपढ़ोy exists */
	I40E_AQ_RC_EINVAL	= 14, /* Invalid argument */
	I40E_AQ_RC_ENOTTY	= 15, /* Not a typeग_लिखोr */
	I40E_AQ_RC_ENOSPC	= 16, /* No space left or alloc failure */
	I40E_AQ_RC_ENOSYS	= 17, /* Function not implemented */
	I40E_AQ_RC_दुस्फल	= 18, /* Parameter out of range */
	I40E_AQ_RC_EFLUSHED	= 19, /* Cmd flushed due to prev cmd error */
	I40E_AQ_RC_BAD_ADDR	= 20, /* Descriptor contains a bad poपूर्णांकer */
	I40E_AQ_RC_EMODE	= 21, /* Op not allowed in current dev mode */
	I40E_AQ_RC_EFBIG	= 22, /* File too large */
पूर्ण;

/* Admin Queue command opcodes */
क्रमागत i40e_admin_queue_opc अणु
	/* aq commands */
	i40e_aqc_opc_get_version	= 0x0001,
	i40e_aqc_opc_driver_version	= 0x0002,
	i40e_aqc_opc_queue_shutकरोwn	= 0x0003,
	i40e_aqc_opc_set_pf_context	= 0x0004,

	/* resource ownership */
	i40e_aqc_opc_request_resource	= 0x0008,
	i40e_aqc_opc_release_resource	= 0x0009,

	i40e_aqc_opc_list_func_capabilities	= 0x000A,
	i40e_aqc_opc_list_dev_capabilities	= 0x000B,

	/* Proxy commands */
	i40e_aqc_opc_set_proxy_config		= 0x0104,
	i40e_aqc_opc_set_ns_proxy_table_entry	= 0x0105,

	/* LAA */
	i40e_aqc_opc_mac_address_पढ़ो	= 0x0107,
	i40e_aqc_opc_mac_address_ग_लिखो	= 0x0108,

	/* PXE */
	i40e_aqc_opc_clear_pxe_mode	= 0x0110,

	/* WoL commands */
	i40e_aqc_opc_set_wol_filter	= 0x0120,
	i40e_aqc_opc_get_wake_reason	= 0x0121,

	/* पूर्णांकernal चयन commands */
	i40e_aqc_opc_get_चयन_config		= 0x0200,
	i40e_aqc_opc_add_statistics		= 0x0201,
	i40e_aqc_opc_हटाओ_statistics		= 0x0202,
	i40e_aqc_opc_set_port_parameters	= 0x0203,
	i40e_aqc_opc_get_चयन_resource_alloc	= 0x0204,
	i40e_aqc_opc_set_चयन_config		= 0x0205,
	i40e_aqc_opc_rx_ctl_reg_पढ़ो		= 0x0206,
	i40e_aqc_opc_rx_ctl_reg_ग_लिखो		= 0x0207,

	i40e_aqc_opc_add_vsi			= 0x0210,
	i40e_aqc_opc_update_vsi_parameters	= 0x0211,
	i40e_aqc_opc_get_vsi_parameters		= 0x0212,

	i40e_aqc_opc_add_pv			= 0x0220,
	i40e_aqc_opc_update_pv_parameters	= 0x0221,
	i40e_aqc_opc_get_pv_parameters		= 0x0222,

	i40e_aqc_opc_add_veb			= 0x0230,
	i40e_aqc_opc_update_veb_parameters	= 0x0231,
	i40e_aqc_opc_get_veb_parameters		= 0x0232,

	i40e_aqc_opc_delete_element		= 0x0243,

	i40e_aqc_opc_add_macvlan		= 0x0250,
	i40e_aqc_opc_हटाओ_macvlan		= 0x0251,
	i40e_aqc_opc_add_vlan			= 0x0252,
	i40e_aqc_opc_हटाओ_vlan		= 0x0253,
	i40e_aqc_opc_set_vsi_promiscuous_modes	= 0x0254,
	i40e_aqc_opc_add_tag			= 0x0255,
	i40e_aqc_opc_हटाओ_tag			= 0x0256,
	i40e_aqc_opc_add_multicast_etag		= 0x0257,
	i40e_aqc_opc_हटाओ_multicast_etag	= 0x0258,
	i40e_aqc_opc_update_tag			= 0x0259,
	i40e_aqc_opc_add_control_packet_filter	= 0x025A,
	i40e_aqc_opc_हटाओ_control_packet_filter	= 0x025B,
	i40e_aqc_opc_add_cloud_filters		= 0x025C,
	i40e_aqc_opc_हटाओ_cloud_filters	= 0x025D,
	i40e_aqc_opc_clear_wol_चयन_filters	= 0x025E,

	i40e_aqc_opc_add_mirror_rule	= 0x0260,
	i40e_aqc_opc_delete_mirror_rule	= 0x0261,

	/* Dynamic Device Personalization */
	i40e_aqc_opc_ग_लिखो_personalization_profile	= 0x0270,
	i40e_aqc_opc_get_personalization_profile_list	= 0x0271,

	/* DCB commands */
	i40e_aqc_opc_dcb_ignore_pfc	= 0x0301,
	i40e_aqc_opc_dcb_updated	= 0x0302,
	i40e_aqc_opc_set_dcb_parameters = 0x0303,

	/* TX scheduler */
	i40e_aqc_opc_configure_vsi_bw_limit		= 0x0400,
	i40e_aqc_opc_configure_vsi_ets_sla_bw_limit	= 0x0406,
	i40e_aqc_opc_configure_vsi_tc_bw		= 0x0407,
	i40e_aqc_opc_query_vsi_bw_config		= 0x0408,
	i40e_aqc_opc_query_vsi_ets_sla_config		= 0x040A,
	i40e_aqc_opc_configure_चयनing_comp_bw_limit	= 0x0410,

	i40e_aqc_opc_enable_चयनing_comp_ets			= 0x0413,
	i40e_aqc_opc_modअगरy_चयनing_comp_ets			= 0x0414,
	i40e_aqc_opc_disable_चयनing_comp_ets			= 0x0415,
	i40e_aqc_opc_configure_चयनing_comp_ets_bw_limit	= 0x0416,
	i40e_aqc_opc_configure_चयनing_comp_bw_config		= 0x0417,
	i40e_aqc_opc_query_चयनing_comp_ets_config		= 0x0418,
	i40e_aqc_opc_query_port_ets_config			= 0x0419,
	i40e_aqc_opc_query_चयनing_comp_bw_config		= 0x041A,
	i40e_aqc_opc_suspend_port_tx				= 0x041B,
	i40e_aqc_opc_resume_port_tx				= 0x041C,
	i40e_aqc_opc_configure_partition_bw			= 0x041D,
	/* hmc */
	i40e_aqc_opc_query_hmc_resource_profile	= 0x0500,
	i40e_aqc_opc_set_hmc_resource_profile	= 0x0501,

	/* phy commands*/
	i40e_aqc_opc_get_phy_abilities		= 0x0600,
	i40e_aqc_opc_set_phy_config		= 0x0601,
	i40e_aqc_opc_set_mac_config		= 0x0603,
	i40e_aqc_opc_set_link_restart_an	= 0x0605,
	i40e_aqc_opc_get_link_status		= 0x0607,
	i40e_aqc_opc_set_phy_पूर्णांक_mask		= 0x0613,
	i40e_aqc_opc_get_local_advt_reg		= 0x0614,
	i40e_aqc_opc_set_local_advt_reg		= 0x0615,
	i40e_aqc_opc_get_partner_advt		= 0x0616,
	i40e_aqc_opc_set_lb_modes		= 0x0618,
	i40e_aqc_opc_get_phy_wol_caps		= 0x0621,
	i40e_aqc_opc_set_phy_debug		= 0x0622,
	i40e_aqc_opc_upload_ext_phy_fm		= 0x0625,
	i40e_aqc_opc_run_phy_activity		= 0x0626,
	i40e_aqc_opc_set_phy_रेजिस्टर		= 0x0628,
	i40e_aqc_opc_get_phy_रेजिस्टर		= 0x0629,

	/* NVM commands */
	i40e_aqc_opc_nvm_पढ़ो			= 0x0701,
	i40e_aqc_opc_nvm_erase			= 0x0702,
	i40e_aqc_opc_nvm_update			= 0x0703,
	i40e_aqc_opc_nvm_config_पढ़ो		= 0x0704,
	i40e_aqc_opc_nvm_config_ग_लिखो		= 0x0705,
	i40e_aqc_opc_oem_post_update		= 0x0720,
	i40e_aqc_opc_thermal_sensor		= 0x0721,

	/* भवization commands */
	i40e_aqc_opc_send_msg_to_pf		= 0x0801,
	i40e_aqc_opc_send_msg_to_vf		= 0x0802,
	i40e_aqc_opc_send_msg_to_peer		= 0x0803,

	/* alternate काष्ठाure */
	i40e_aqc_opc_alternate_ग_लिखो		= 0x0900,
	i40e_aqc_opc_alternate_ग_लिखो_indirect	= 0x0901,
	i40e_aqc_opc_alternate_पढ़ो		= 0x0902,
	i40e_aqc_opc_alternate_पढ़ो_indirect	= 0x0903,
	i40e_aqc_opc_alternate_ग_लिखो_करोne	= 0x0904,
	i40e_aqc_opc_alternate_set_mode		= 0x0905,
	i40e_aqc_opc_alternate_clear_port	= 0x0906,

	/* LLDP commands */
	i40e_aqc_opc_lldp_get_mib	= 0x0A00,
	i40e_aqc_opc_lldp_update_mib	= 0x0A01,
	i40e_aqc_opc_lldp_add_tlv	= 0x0A02,
	i40e_aqc_opc_lldp_update_tlv	= 0x0A03,
	i40e_aqc_opc_lldp_delete_tlv	= 0x0A04,
	i40e_aqc_opc_lldp_stop		= 0x0A05,
	i40e_aqc_opc_lldp_start		= 0x0A06,
	i40e_aqc_opc_get_cee_dcb_cfg	= 0x0A07,
	i40e_aqc_opc_lldp_set_local_mib	= 0x0A08,
	i40e_aqc_opc_lldp_stop_start_spec_agent	= 0x0A09,
	i40e_aqc_opc_lldp_restore		= 0x0A0A,

	/* Tunnel commands */
	i40e_aqc_opc_add_udp_tunnel	= 0x0B00,
	i40e_aqc_opc_del_udp_tunnel	= 0x0B01,
	i40e_aqc_opc_set_rss_key	= 0x0B02,
	i40e_aqc_opc_set_rss_lut	= 0x0B03,
	i40e_aqc_opc_get_rss_key	= 0x0B04,
	i40e_aqc_opc_get_rss_lut	= 0x0B05,

	/* Async Events */
	i40e_aqc_opc_event_lan_overflow		= 0x1001,

	/* OEM commands */
	i40e_aqc_opc_oem_parameter_change	= 0xFE00,
	i40e_aqc_opc_oem_device_status_change	= 0xFE01,
	i40e_aqc_opc_oem_ocsd_initialize	= 0xFE02,
	i40e_aqc_opc_oem_ocbb_initialize	= 0xFE03,

	/* debug commands */
	i40e_aqc_opc_debug_पढ़ो_reg		= 0xFF03,
	i40e_aqc_opc_debug_ग_लिखो_reg		= 0xFF04,
	i40e_aqc_opc_debug_modअगरy_reg		= 0xFF07,
	i40e_aqc_opc_debug_dump_पूर्णांकernals	= 0xFF08,
पूर्ण;

/* command काष्ठाures and indirect data काष्ठाures */

/* Structure naming conventions:
 * - no suffix क्रम direct command descriptor काष्ठाures
 * - _data क्रम indirect sent data
 * - _resp क्रम indirect वापस data (data which is both will use _data)
 * - _completion क्रम direct वापस data
 * - _element_ क्रम repeated elements (may also be _data or _resp)
 *
 * Command काष्ठाures are expected to overlay the params.raw member of the basic
 * descriptor, and as such cannot exceed 16 bytes in length.
 */

/* This macro is used to generate a compilation error अगर a काष्ठाure
 * is not exactly the correct length. It gives a भागide by zero error अगर the
 * काष्ठाure is not of the correct size, otherwise it creates an क्रमागत that is
 * never used.
 */
#घोषणा I40E_CHECK_STRUCT_LEN(n, X) क्रमागत i40e_अटल_निश्चित_क्रमागत_##X \
	अणु i40e_अटल_निश्चित_##X = (n)/((माप(काष्ठा X) == (n)) ? 1 : 0) पूर्ण

/* This macro is used extensively to ensure that command काष्ठाures are 16
 * bytes in length as they have to map to the raw array of that size.
 */
#घोषणा I40E_CHECK_CMD_LENGTH(X)	I40E_CHECK_STRUCT_LEN(16, X)

/* पूर्णांकernal (0x00XX) commands */

/* Get version (direct 0x0001) */
काष्ठा i40e_aqc_get_version अणु
	__le32 rom_ver;
	__le32 fw_build;
	__le16 fw_major;
	__le16 fw_minor;
	__le16 api_major;
	__le16 api_minor;
पूर्ण;

I40E_CHECK_CMD_LENGTH(i40e_aqc_get_version);

/* Send driver version (indirect 0x0002) */
काष्ठा i40e_aqc_driver_version अणु
	u8	driver_major_ver;
	u8	driver_minor_ver;
	u8	driver_build_ver;
	u8	driver_subbuild_ver;
	u8	reserved[4];
	__le32	address_high;
	__le32	address_low;
पूर्ण;

I40E_CHECK_CMD_LENGTH(i40e_aqc_driver_version);

/* Queue Shutकरोwn (direct 0x0003) */
काष्ठा i40e_aqc_queue_shutकरोwn अणु
	__le32	driver_unloading;
#घोषणा I40E_AQ_DRIVER_UNLOADING	0x1
	u8	reserved[12];
पूर्ण;

I40E_CHECK_CMD_LENGTH(i40e_aqc_queue_shutकरोwn);

/* Set PF context (0x0004, direct) */
काष्ठा i40e_aqc_set_pf_context अणु
	u8	pf_id;
	u8	reserved[15];
पूर्ण;

I40E_CHECK_CMD_LENGTH(i40e_aqc_set_pf_context);

/* Request resource ownership (direct 0x0008)
 * Release resource ownership (direct 0x0009)
 */
काष्ठा i40e_aqc_request_resource अणु
	__le16	resource_id;
	__le16	access_type;
	__le32	समयout;
	__le32	resource_number;
	u8	reserved[4];
पूर्ण;

I40E_CHECK_CMD_LENGTH(i40e_aqc_request_resource);

/* Get function capabilities (indirect 0x000A)
 * Get device capabilities (indirect 0x000B)
 */
काष्ठा i40e_aqc_list_capabilites अणु
	u8 command_flags;
	u8 pf_index;
	u8 reserved[2];
	__le32 count;
	__le32 addr_high;
	__le32 addr_low;
पूर्ण;

I40E_CHECK_CMD_LENGTH(i40e_aqc_list_capabilites);

काष्ठा i40e_aqc_list_capabilities_element_resp अणु
	__le16	id;
	u8	major_rev;
	u8	minor_rev;
	__le32	number;
	__le32	logical_id;
	__le32	phys_id;
	u8	reserved[16];
पूर्ण;

/* list of caps */

#घोषणा I40E_AQ_CAP_ID_SWITCH_MODE	0x0001
#घोषणा I40E_AQ_CAP_ID_MNG_MODE		0x0002
#घोषणा I40E_AQ_CAP_ID_NPAR_ACTIVE	0x0003
#घोषणा I40E_AQ_CAP_ID_OS2BMC_CAP	0x0004
#घोषणा I40E_AQ_CAP_ID_FUNCTIONS_VALID	0x0005
#घोषणा I40E_AQ_CAP_ID_SRIOV		0x0012
#घोषणा I40E_AQ_CAP_ID_VF		0x0013
#घोषणा I40E_AQ_CAP_ID_VMDQ		0x0014
#घोषणा I40E_AQ_CAP_ID_8021QBG		0x0015
#घोषणा I40E_AQ_CAP_ID_8021QBR		0x0016
#घोषणा I40E_AQ_CAP_ID_VSI		0x0017
#घोषणा I40E_AQ_CAP_ID_DCB		0x0018
#घोषणा I40E_AQ_CAP_ID_FCOE		0x0021
#घोषणा I40E_AQ_CAP_ID_ISCSI		0x0022
#घोषणा I40E_AQ_CAP_ID_RSS		0x0040
#घोषणा I40E_AQ_CAP_ID_RXQ		0x0041
#घोषणा I40E_AQ_CAP_ID_TXQ		0x0042
#घोषणा I40E_AQ_CAP_ID_MSIX		0x0043
#घोषणा I40E_AQ_CAP_ID_VF_MSIX		0x0044
#घोषणा I40E_AQ_CAP_ID_FLOW_सूचीECTOR	0x0045
#घोषणा I40E_AQ_CAP_ID_1588		0x0046
#घोषणा I40E_AQ_CAP_ID_IWARP		0x0051
#घोषणा I40E_AQ_CAP_ID_LED		0x0061
#घोषणा I40E_AQ_CAP_ID_SDP		0x0062
#घोषणा I40E_AQ_CAP_ID_MDIO		0x0063
#घोषणा I40E_AQ_CAP_ID_WSR_PROT		0x0064
#घोषणा I40E_AQ_CAP_ID_NVM_MGMT		0x0080
#घोषणा I40E_AQ_CAP_ID_FLEX10		0x00F1
#घोषणा I40E_AQ_CAP_ID_CEM		0x00F2

/* Set CPPM Configuration (direct 0x0103) */
काष्ठा i40e_aqc_cppm_configuration अणु
	__le16	command_flags;
	__le16	ttlx;
	__le32	dmacr;
	__le16	dmcth;
	u8	hptc;
	u8	reserved;
	__le32	pfltrc;
पूर्ण;

I40E_CHECK_CMD_LENGTH(i40e_aqc_cppm_configuration);

/* Set ARP Proxy command / response (indirect 0x0104) */
काष्ठा i40e_aqc_arp_proxy_data अणु
	__le16	command_flags;
	__le16	table_id;
	__le32	enabled_offloads;
	__le32	ip_addr;
	u8	mac_addr[6];
	u8	reserved[2];
पूर्ण;

I40E_CHECK_STRUCT_LEN(0x14, i40e_aqc_arp_proxy_data);

/* Set NS Proxy Table Entry Command (indirect 0x0105) */
काष्ठा i40e_aqc_ns_proxy_data अणु
	__le16	table_idx_mac_addr_0;
	__le16	table_idx_mac_addr_1;
	__le16	table_idx_ipv6_0;
	__le16	table_idx_ipv6_1;
	__le16	control;
	u8	mac_addr_0[6];
	u8	mac_addr_1[6];
	u8	local_mac_addr[6];
	u8	ipv6_addr_0[16]; /* Warning! spec specअगरies BE byte order */
	u8	ipv6_addr_1[16];
पूर्ण;

I40E_CHECK_STRUCT_LEN(0x3c, i40e_aqc_ns_proxy_data);

/* Manage LAA Command (0x0106) - obsolete */
काष्ठा i40e_aqc_mng_laa अणु
	__le16	command_flags;
	u8	reserved[2];
	__le32	sal;
	__le16	sah;
	u8	reserved2[6];
पूर्ण;

I40E_CHECK_CMD_LENGTH(i40e_aqc_mng_laa);

/* Manage MAC Address Read Command (indirect 0x0107) */
काष्ठा i40e_aqc_mac_address_पढ़ो अणु
	__le16	command_flags;
#घोषणा I40E_AQC_LAN_ADDR_VALID		0x10
#घोषणा I40E_AQC_PORT_ADDR_VALID	0x40
	u8	reserved[6];
	__le32	addr_high;
	__le32	addr_low;
पूर्ण;

I40E_CHECK_CMD_LENGTH(i40e_aqc_mac_address_पढ़ो);

काष्ठा i40e_aqc_mac_address_पढ़ो_data अणु
	u8 pf_lan_mac[6];
	u8 pf_san_mac[6];
	u8 port_mac[6];
	u8 pf_wol_mac[6];
पूर्ण;

I40E_CHECK_STRUCT_LEN(24, i40e_aqc_mac_address_पढ़ो_data);

/* Manage MAC Address Write Command (0x0108) */
काष्ठा i40e_aqc_mac_address_ग_लिखो अणु
	__le16	command_flags;
#घोषणा I40E_AQC_MC_MAG_EN		0x0100
#घोषणा I40E_AQC_WOL_PRESERVE_ON_PFR	0x0200
#घोषणा I40E_AQC_WRITE_TYPE_LAA_ONLY	0x0000
#घोषणा I40E_AQC_WRITE_TYPE_LAA_WOL	0x4000
#घोषणा I40E_AQC_WRITE_TYPE_UPDATE_MC_MAG	0xC000

	__le16	mac_sah;
	__le32	mac_sal;
	u8	reserved[8];
पूर्ण;

I40E_CHECK_CMD_LENGTH(i40e_aqc_mac_address_ग_लिखो);

/* PXE commands (0x011x) */

/* Clear PXE Command and response  (direct 0x0110) */
काष्ठा i40e_aqc_clear_pxe अणु
	u8	rx_cnt;
	u8	reserved[15];
पूर्ण;

I40E_CHECK_CMD_LENGTH(i40e_aqc_clear_pxe);

/* Set WoL Filter (0x0120) */

काष्ठा i40e_aqc_set_wol_filter अणु
	__le16 filter_index;

	__le16 cmd_flags;
	__le16 valid_flags;
	u8 reserved[2];
	__le32	address_high;
	__le32	address_low;
पूर्ण;

I40E_CHECK_CMD_LENGTH(i40e_aqc_set_wol_filter);

काष्ठा i40e_aqc_set_wol_filter_data अणु
	u8 filter[128];
	u8 mask[16];
पूर्ण;

I40E_CHECK_STRUCT_LEN(0x90, i40e_aqc_set_wol_filter_data);

/* Get Wake Reason (0x0121) */

काष्ठा i40e_aqc_get_wake_reason_completion अणु
	u8 reserved_1[2];
	__le16 wake_reason;
	u8 reserved_2[12];
पूर्ण;

I40E_CHECK_CMD_LENGTH(i40e_aqc_get_wake_reason_completion);

/* Switch configuration commands (0x02xx) */

/* Used by many indirect commands that only pass an seid and a buffer in the
 * command
 */
काष्ठा i40e_aqc_चयन_seid अणु
	__le16	seid;
	u8	reserved[6];
	__le32	addr_high;
	__le32	addr_low;
पूर्ण;

I40E_CHECK_CMD_LENGTH(i40e_aqc_चयन_seid);

/* Get Switch Configuration command (indirect 0x0200)
 * uses i40e_aqc_चयन_seid क्रम the descriptor
 */
काष्ठा i40e_aqc_get_चयन_config_header_resp अणु
	__le16	num_reported;
	__le16	num_total;
	u8	reserved[12];
पूर्ण;

I40E_CHECK_CMD_LENGTH(i40e_aqc_get_चयन_config_header_resp);

काष्ठा i40e_aqc_चयन_config_element_resp अणु
	u8	element_type;
	u8	revision;
	__le16	seid;
	__le16	uplink_seid;
	__le16	करोwnlink_seid;
	u8	reserved[3];
	u8	connection_type;
	__le16	scheduler_id;
	__le16	element_info;
पूर्ण;

I40E_CHECK_STRUCT_LEN(0x10, i40e_aqc_चयन_config_element_resp);

/* Get Switch Configuration (indirect 0x0200)
 *    an array of elements are वापसed in the response buffer
 *    the first in the array is the header, reमुख्यder are elements
 */
काष्ठा i40e_aqc_get_चयन_config_resp अणु
	काष्ठा i40e_aqc_get_चयन_config_header_resp	header;
	काष्ठा i40e_aqc_चयन_config_element_resp	element[1];
पूर्ण;

I40E_CHECK_STRUCT_LEN(0x20, i40e_aqc_get_चयन_config_resp);

/* Add Statistics (direct 0x0201)
 * Remove Statistics (direct 0x0202)
 */
काष्ठा i40e_aqc_add_हटाओ_statistics अणु
	__le16	seid;
	__le16	vlan;
	__le16	stat_index;
	u8	reserved[10];
पूर्ण;

I40E_CHECK_CMD_LENGTH(i40e_aqc_add_हटाओ_statistics);

/* Set Port Parameters command (direct 0x0203) */
काष्ठा i40e_aqc_set_port_parameters अणु
	__le16	command_flags;
	__le16	bad_frame_vsi;
	__le16	शेष_seid;        /* reserved क्रम command */
	u8	reserved[10];
पूर्ण;

I40E_CHECK_CMD_LENGTH(i40e_aqc_set_port_parameters);

/* Get Switch Resource Allocation (indirect 0x0204) */
काष्ठा i40e_aqc_get_चयन_resource_alloc अणु
	u8	num_entries;         /* reserved क्रम command */
	u8	reserved[7];
	__le32	addr_high;
	__le32	addr_low;
पूर्ण;

I40E_CHECK_CMD_LENGTH(i40e_aqc_get_चयन_resource_alloc);

/* expect an array of these काष्ठाs in the response buffer */
काष्ठा i40e_aqc_चयन_resource_alloc_element_resp अणु
	u8	resource_type;
	u8	reserved1;
	__le16	guaranteed;
	__le16	total;
	__le16	used;
	__le16	total_unalloced;
	u8	reserved2[6];
पूर्ण;

I40E_CHECK_STRUCT_LEN(0x10, i40e_aqc_चयन_resource_alloc_element_resp);

/* Set Switch Configuration (direct 0x0205) */
काष्ठा i40e_aqc_set_चयन_config अणु
	__le16	flags;
/* flags used क्रम both fields below */
#घोषणा I40E_AQ_SET_SWITCH_CFG_PROMISC		0x0001
	__le16	valid_flags;
	/* The ethertype in चयन_tag is dropped on ingress and used
	 * पूर्णांकernally by the चयन. Set this to zero क्रम the शेष
	 * of 0x88a8 (802.1ad). Should be zero क्रम firmware API
	 * versions lower than 1.7.
	 */
	__le16	चयन_tag;
	/* The ethertypes in first_tag and second_tag are used to
	 * match the outer and inner VLAN tags (respectively) when HW
	 * द्विगुन VLAN tagging is enabled via the set port parameters
	 * AQ command. Otherwise these are both ignored. Set them to
	 * zero क्रम their शेषs of 0x8100 (802.1Q). Should be zero
	 * क्रम firmware API versions lower than 1.7.
	 */
	__le16	first_tag;
	__le16	second_tag;
	/* Next byte is split पूर्णांकo following:
	 * Bit 7    : 0 : No action, 1: Switch to mode defined by bits 6:0
	 * Bit 6    : 0 : Destination Port, 1: source port
	 * Bit 5..4 : L4 type
	 * 0: rsvd
	 * 1: TCP
	 * 2: UDP
	 * 3: Both TCP and UDP
	 * Bits 3:0 Mode
	 * 0: शेष mode
	 * 1: L4 port only mode
	 * 2: non-tunneled mode
	 * 3: tunneled mode
	 */
#घोषणा I40E_AQ_SET_SWITCH_BIT7_VALID		0x80


#घोषणा I40E_AQ_SET_SWITCH_L4_TYPE_TCP		0x10

#घोषणा I40E_AQ_SET_SWITCH_MODE_NON_TUNNEL	0x02
	u8	mode;
	u8	rsvd5[5];
पूर्ण;

I40E_CHECK_CMD_LENGTH(i40e_aqc_set_चयन_config);

/* Read Receive control रेजिस्टरs  (direct 0x0206)
 * Write Receive control रेजिस्टरs (direct 0x0207)
 *     used क्रम accessing Rx control रेजिस्टरs that can be
 *     slow and need special handling when under high Rx load
 */
काष्ठा i40e_aqc_rx_ctl_reg_पढ़ो_ग_लिखो अणु
	__le32 reserved1;
	__le32 address;
	__le32 reserved2;
	__le32 value;
पूर्ण;

I40E_CHECK_CMD_LENGTH(i40e_aqc_rx_ctl_reg_पढ़ो_ग_लिखो);

/* Add VSI (indirect 0x0210)
 *    this indirect command uses काष्ठा i40e_aqc_vsi_properties_data
 *    as the indirect buffer (128 bytes)
 *
 * Update VSI (indirect 0x211)
 *     uses the same data काष्ठाure as Add VSI
 *
 * Get VSI (indirect 0x0212)
 *     uses the same completion and data काष्ठाure as Add VSI
 */
काष्ठा i40e_aqc_add_get_update_vsi अणु
	__le16	uplink_seid;
	u8	connection_type;
#घोषणा I40E_AQ_VSI_CONN_TYPE_NORMAL	0x1
	u8	reserved1;
	u8	vf_id;
	u8	reserved2;
	__le16	vsi_flags;
#घोषणा I40E_AQ_VSI_TYPE_VF		0x0
#घोषणा I40E_AQ_VSI_TYPE_VMDQ2		0x1
#घोषणा I40E_AQ_VSI_TYPE_PF		0x2
	__le32	addr_high;
	__le32	addr_low;
पूर्ण;

I40E_CHECK_CMD_LENGTH(i40e_aqc_add_get_update_vsi);

काष्ठा i40e_aqc_add_get_update_vsi_completion अणु
	__le16 seid;
	__le16 vsi_number;
	__le16 vsi_used;
	__le16 vsi_मुक्त;
	__le32 addr_high;
	__le32 addr_low;
पूर्ण;

I40E_CHECK_CMD_LENGTH(i40e_aqc_add_get_update_vsi_completion);

काष्ठा i40e_aqc_vsi_properties_data अणु
	/* first 96 byte are written by SW */
	__le16	valid_sections;
#घोषणा I40E_AQ_VSI_PROP_SWITCH_VALID		0x0001
#घोषणा I40E_AQ_VSI_PROP_SECURITY_VALID		0x0002
#घोषणा I40E_AQ_VSI_PROP_VLAN_VALID		0x0004
#घोषणा I40E_AQ_VSI_PROP_QUEUE_MAP_VALID	0x0040
#घोषणा I40E_AQ_VSI_PROP_QUEUE_OPT_VALID	0x0080
#घोषणा I40E_AQ_VSI_PROP_SCHED_VALID		0x0200
	/* चयन section */
	__le16	चयन_id; /* 12bit id combined with flags below */
#घोषणा I40E_AQ_VSI_SW_ID_SHIFT		0x0000
#घोषणा I40E_AQ_VSI_SW_ID_MASK		(0xFFF << I40E_AQ_VSI_SW_ID_SHIFT)
#घोषणा I40E_AQ_VSI_SW_ID_FLAG_ALLOW_LB	0x2000
#घोषणा I40E_AQ_VSI_SW_ID_FLAG_LOCAL_LB	0x4000
	u8	sw_reserved[2];
	/* security section */
	u8	sec_flags;
#घोषणा I40E_AQ_VSI_SEC_FLAG_ENABLE_VLAN_CHK	0x02
#घोषणा I40E_AQ_VSI_SEC_FLAG_ENABLE_MAC_CHK	0x04
	u8	sec_reserved;
	/* VLAN section */
	__le16	pvid; /* VLANS include priority bits */
	__le16	fcoe_pvid;
	u8	port_vlan_flags;
#घोषणा I40E_AQ_VSI_PVLAN_MODE_SHIFT	0x00
#घोषणा I40E_AQ_VSI_PVLAN_MODE_MASK	(0x03 << \
					 I40E_AQ_VSI_PVLAN_MODE_SHIFT)
#घोषणा I40E_AQ_VSI_PVLAN_MODE_TAGGED	0x01
#घोषणा I40E_AQ_VSI_PVLAN_MODE_ALL	0x03
#घोषणा I40E_AQ_VSI_PVLAN_INSERT_PVID	0x04
#घोषणा I40E_AQ_VSI_PVLAN_EMOD_SHIFT	0x03
#घोषणा I40E_AQ_VSI_PVLAN_EMOD_MASK	(0x3 << \
					 I40E_AQ_VSI_PVLAN_EMOD_SHIFT)
#घोषणा I40E_AQ_VSI_PVLAN_EMOD_STR_BOTH	0x0
#घोषणा I40E_AQ_VSI_PVLAN_EMOD_STR	0x10
#घोषणा I40E_AQ_VSI_PVLAN_EMOD_NOTHING	0x18
	u8	pvlan_reserved[3];
	/* ingress egress up sections */
	__le32	ingress_table; /* biपंचांगap, 3 bits per up */
	__le32	egress_table;   /* same defines as क्रम ingress table */
	/* cascaded PV section */
	__le16	cas_pv_tag;
	u8	cas_pv_flags;
	u8	cas_pv_reserved;
	/* queue mapping section */
	__le16	mapping_flags;
#घोषणा I40E_AQ_VSI_QUE_MAP_CONTIG	0x0
#घोषणा I40E_AQ_VSI_QUE_MAP_NONCONTIG	0x1
	__le16	queue_mapping[16];
	__le16	tc_mapping[8];
#घोषणा I40E_AQ_VSI_TC_QUE_OFFSET_SHIFT	0
#घोषणा I40E_AQ_VSI_TC_QUE_NUMBER_SHIFT	9
	/* queueing option section */
	u8	queueing_opt_flags;
#घोषणा I40E_AQ_VSI_QUE_OPT_TCP_ENA	0x10
#घोषणा I40E_AQ_VSI_QUE_OPT_RSS_LUT_VSI	0x40
	u8	queueing_opt_reserved[3];
	/* scheduler section */
	u8	up_enable_bits;
	u8	sched_reserved;
	/* outer up section */
	__le32	outer_up_table; /* same काष्ठाure and defines as ingress tbl */
	u8	cmd_reserved[8];
	/* last 32 bytes are written by FW */
	__le16	qs_handle[8];
#घोषणा I40E_AQ_VSI_QS_HANDLE_INVALID	0xFFFF
	__le16	stat_counter_idx;
	__le16	sched_id;
	u8	resp_reserved[12];
पूर्ण;

I40E_CHECK_STRUCT_LEN(128, i40e_aqc_vsi_properties_data);

/* Add Port Virtualizer (direct 0x0220)
 * also used क्रम update PV (direct 0x0221) but only flags are used
 * (IS_CTRL_PORT only works on add PV)
 */
काष्ठा i40e_aqc_add_update_pv अणु
	__le16	command_flags;
	__le16	uplink_seid;
	__le16	connected_seid;
	u8	reserved[10];
पूर्ण;

I40E_CHECK_CMD_LENGTH(i40e_aqc_add_update_pv);

काष्ठा i40e_aqc_add_update_pv_completion अणु
	/* reserved क्रम update; क्रम add also encodes error अगर rc == ENOSPC */
	__le16	pv_seid;
	u8	reserved[14];
पूर्ण;

I40E_CHECK_CMD_LENGTH(i40e_aqc_add_update_pv_completion);

/* Get PV Params (direct 0x0222)
 * uses i40e_aqc_चयन_seid क्रम the descriptor
 */

काष्ठा i40e_aqc_get_pv_params_completion अणु
	__le16	seid;
	__le16	शेष_stag;
	__le16	pv_flags; /* same flags as add_pv */
	u8	reserved[8];
	__le16	शेष_port_seid;
पूर्ण;

I40E_CHECK_CMD_LENGTH(i40e_aqc_get_pv_params_completion);

/* Add VEB (direct 0x0230) */
काष्ठा i40e_aqc_add_veb अणु
	__le16	uplink_seid;
	__le16	करोwnlink_seid;
	__le16	veb_flags;
#घोषणा I40E_AQC_ADD_VEB_FLOATING		0x1
#घोषणा I40E_AQC_ADD_VEB_PORT_TYPE_DEFAULT	0x2
#घोषणा I40E_AQC_ADD_VEB_PORT_TYPE_DATA		0x4
#घोषणा I40E_AQC_ADD_VEB_ENABLE_DISABLE_STATS	0x10
	u8	enable_tcs;
	u8	reserved[9];
पूर्ण;

I40E_CHECK_CMD_LENGTH(i40e_aqc_add_veb);

काष्ठा i40e_aqc_add_veb_completion अणु
	u8	reserved[6];
	__le16	चयन_seid;
	/* also encodes error अगर rc == ENOSPC; codes are the same as add_pv */
	__le16	veb_seid;
	__le16	statistic_index;
	__le16	vebs_used;
	__le16	vebs_मुक्त;
पूर्ण;

I40E_CHECK_CMD_LENGTH(i40e_aqc_add_veb_completion);

/* Get VEB Parameters (direct 0x0232)
 * uses i40e_aqc_चयन_seid क्रम the descriptor
 */
काष्ठा i40e_aqc_get_veb_parameters_completion अणु
	__le16	seid;
	__le16	चयन_id;
	__le16	veb_flags; /* only the first/last flags from 0x0230 is valid */
	__le16	statistic_index;
	__le16	vebs_used;
	__le16	vebs_मुक्त;
	u8	reserved[4];
पूर्ण;

I40E_CHECK_CMD_LENGTH(i40e_aqc_get_veb_parameters_completion);

/* Delete Element (direct 0x0243)
 * uses the generic i40e_aqc_चयन_seid
 */

/* Add MAC-VLAN (indirect 0x0250) */

/* used क्रम the command क्रम most vlan commands */
काष्ठा i40e_aqc_macvlan अणु
	__le16	num_addresses;
	__le16	seid[3];
#घोषणा I40E_AQC_MACVLAN_CMD_SEID_VALID		0x8000
	__le32	addr_high;
	__le32	addr_low;
पूर्ण;

I40E_CHECK_CMD_LENGTH(i40e_aqc_macvlan);

/* indirect data क्रम command and response */
काष्ठा i40e_aqc_add_macvlan_element_data अणु
	u8	mac_addr[6];
	__le16	vlan_tag;
	__le16	flags;
#घोषणा I40E_AQC_MACVLAN_ADD_PERFECT_MATCH	0x0001
#घोषणा I40E_AQC_MACVLAN_ADD_IGNORE_VLAN	0x0004
#घोषणा I40E_AQC_MACVLAN_ADD_USE_SHARED_MAC	0x0010
	__le16	queue_number;
	/* response section */
	u8	match_method;
#घोषणा I40E_AQC_MM_ERR_NO_RES		0xFF
	u8	reserved1[3];
पूर्ण;

काष्ठा i40e_aqc_add_हटाओ_macvlan_completion अणु
	__le16 perfect_mac_used;
	__le16 perfect_mac_मुक्त;
	__le16 unicast_hash_मुक्त;
	__le16 multicast_hash_मुक्त;
	__le32 addr_high;
	__le32 addr_low;
पूर्ण;

I40E_CHECK_CMD_LENGTH(i40e_aqc_add_हटाओ_macvlan_completion);

/* Remove MAC-VLAN (indirect 0x0251)
 * uses i40e_aqc_macvlan क्रम the descriptor
 * data poपूर्णांकs to an array of num_addresses of elements
 */

काष्ठा i40e_aqc_हटाओ_macvlan_element_data अणु
	u8	mac_addr[6];
	__le16	vlan_tag;
	u8	flags;
#घोषणा I40E_AQC_MACVLAN_DEL_PERFECT_MATCH	0x01
#घोषणा I40E_AQC_MACVLAN_DEL_IGNORE_VLAN	0x08
	u8	reserved[3];
	/* reply section */
	u8	error_code;
	u8	reply_reserved[3];
पूर्ण;

/* Add VLAN (indirect 0x0252)
 * Remove VLAN (indirect 0x0253)
 * use the generic i40e_aqc_macvlan क्रम the command
 */
काष्ठा i40e_aqc_add_हटाओ_vlan_element_data अणु
	__le16	vlan_tag;
	u8	vlan_flags;
	u8	reserved;
	u8	result;
	u8	reserved1[3];
पूर्ण;

काष्ठा i40e_aqc_add_हटाओ_vlan_completion अणु
	u8	reserved[4];
	__le16	vlans_used;
	__le16	vlans_मुक्त;
	__le32	addr_high;
	__le32	addr_low;
पूर्ण;

/* Set VSI Promiscuous Modes (direct 0x0254) */
काष्ठा i40e_aqc_set_vsi_promiscuous_modes अणु
	__le16	promiscuous_flags;
	__le16	valid_flags;
/* flags used क्रम both fields above */
#घोषणा I40E_AQC_SET_VSI_PROMISC_UNICAST	0x01
#घोषणा I40E_AQC_SET_VSI_PROMISC_MULTICAST	0x02
#घोषणा I40E_AQC_SET_VSI_PROMISC_BROADCAST	0x04
#घोषणा I40E_AQC_SET_VSI_DEFAULT		0x08
#घोषणा I40E_AQC_SET_VSI_PROMISC_VLAN		0x10
#घोषणा I40E_AQC_SET_VSI_PROMISC_RX_ONLY	0x8000
	__le16	seid;
	__le16	vlan_tag;
#घोषणा I40E_AQC_SET_VSI_VLAN_VALID		0x8000
	u8	reserved[8];
पूर्ण;

I40E_CHECK_CMD_LENGTH(i40e_aqc_set_vsi_promiscuous_modes);

/* Add S/E-tag command (direct 0x0255)
 * Uses generic i40e_aqc_add_हटाओ_tag_completion क्रम completion
 */
काष्ठा i40e_aqc_add_tag अणु
	__le16	flags;
	__le16	seid;
	__le16	tag;
	__le16	queue_number;
	u8	reserved[8];
पूर्ण;

I40E_CHECK_CMD_LENGTH(i40e_aqc_add_tag);

काष्ठा i40e_aqc_add_हटाओ_tag_completion अणु
	u8	reserved[12];
	__le16	tags_used;
	__le16	tags_मुक्त;
पूर्ण;

I40E_CHECK_CMD_LENGTH(i40e_aqc_add_हटाओ_tag_completion);

/* Remove S/E-tag command (direct 0x0256)
 * Uses generic i40e_aqc_add_हटाओ_tag_completion क्रम completion
 */
काष्ठा i40e_aqc_हटाओ_tag अणु
	__le16	seid;
	__le16	tag;
	u8	reserved[12];
पूर्ण;

I40E_CHECK_CMD_LENGTH(i40e_aqc_हटाओ_tag);

/* Add multicast E-Tag (direct 0x0257)
 * del multicast E-Tag (direct 0x0258) only uses pv_seid and etag fields
 * and no बाह्यal data
 */
काष्ठा i40e_aqc_add_हटाओ_mcast_etag अणु
	__le16	pv_seid;
	__le16	etag;
	u8	num_unicast_etags;
	u8	reserved[3];
	__le32	addr_high;          /* address of array of 2-byte s-tags */
	__le32	addr_low;
पूर्ण;

I40E_CHECK_CMD_LENGTH(i40e_aqc_add_हटाओ_mcast_etag);

काष्ठा i40e_aqc_add_हटाओ_mcast_etag_completion अणु
	u8	reserved[4];
	__le16	mcast_etags_used;
	__le16	mcast_etags_मुक्त;
	__le32	addr_high;
	__le32	addr_low;

पूर्ण;

I40E_CHECK_CMD_LENGTH(i40e_aqc_add_हटाओ_mcast_etag_completion);

/* Update S/E-Tag (direct 0x0259) */
काष्ठा i40e_aqc_update_tag अणु
	__le16	seid;
	__le16	old_tag;
	__le16	new_tag;
	u8	reserved[10];
पूर्ण;

I40E_CHECK_CMD_LENGTH(i40e_aqc_update_tag);

काष्ठा i40e_aqc_update_tag_completion अणु
	u8	reserved[12];
	__le16	tags_used;
	__le16	tags_मुक्त;
पूर्ण;

I40E_CHECK_CMD_LENGTH(i40e_aqc_update_tag_completion);

/* Add Control Packet filter (direct 0x025A)
 * Remove Control Packet filter (direct 0x025B)
 * uses the i40e_aqc_add_oveb_cloud,
 * and the generic direct completion काष्ठाure
 */
काष्ठा i40e_aqc_add_हटाओ_control_packet_filter अणु
	u8	mac[6];
	__le16	etype;
	__le16	flags;
#घोषणा I40E_AQC_ADD_CONTROL_PACKET_FLAGS_IGNORE_MAC	0x0001
#घोषणा I40E_AQC_ADD_CONTROL_PACKET_FLAGS_DROP		0x0002
#घोषणा I40E_AQC_ADD_CONTROL_PACKET_FLAGS_TX		0x0008
#घोषणा I40E_AQC_ADD_CONTROL_PACKET_FLAGS_RX		0x0000
	__le16	seid;
	__le16	queue;
	u8	reserved[2];
पूर्ण;

I40E_CHECK_CMD_LENGTH(i40e_aqc_add_हटाओ_control_packet_filter);

काष्ठा i40e_aqc_add_हटाओ_control_packet_filter_completion अणु
	__le16	mac_etype_used;
	__le16	etype_used;
	__le16	mac_etype_मुक्त;
	__le16	etype_मुक्त;
	u8	reserved[8];
पूर्ण;

I40E_CHECK_CMD_LENGTH(i40e_aqc_add_हटाओ_control_packet_filter_completion);

/* Add Cloud filters (indirect 0x025C)
 * Remove Cloud filters (indirect 0x025D)
 * uses the i40e_aqc_add_हटाओ_cloud_filters,
 * and the generic indirect completion काष्ठाure
 */
काष्ठा i40e_aqc_add_हटाओ_cloud_filters अणु
	u8	num_filters;
	u8	reserved;
	__le16	seid;
	u8	big_buffer_flag;
#घोषणा I40E_AQC_ADD_CLOUD_CMD_BB	1
	u8	reserved2[3];
	__le32	addr_high;
	__le32	addr_low;
पूर्ण;

I40E_CHECK_CMD_LENGTH(i40e_aqc_add_हटाओ_cloud_filters);

काष्ठा i40e_aqc_cloud_filters_element_data अणु
	u8	outer_mac[6];
	u8	inner_mac[6];
	__le16	inner_vlan;
	जोड़ अणु
		काष्ठा अणु
			u8 reserved[12];
			u8 data[4];
		पूर्ण v4;
		काष्ठा अणु
			u8 data[16];
		पूर्ण v6;
		काष्ठा अणु
			__le16 data[8];
		पूर्ण raw_v6;
	पूर्ण ipaddr;
	__le16	flags;
/* 0x0000 reserved */
/* 0x0001 reserved */
/* 0x0002 reserved */
#घोषणा I40E_AQC_ADD_CLOUD_FILTER_IMAC_IVLAN		0x0003
#घोषणा I40E_AQC_ADD_CLOUD_FILTER_IMAC_IVLAN_TEN_ID	0x0004
/* 0x0005 reserved */
#घोषणा I40E_AQC_ADD_CLOUD_FILTER_IMAC_TEN_ID		0x0006
/* 0x0007 reserved */
/* 0x0008 reserved */
#घोषणा I40E_AQC_ADD_CLOUD_FILTER_OMAC			0x0009
#घोषणा I40E_AQC_ADD_CLOUD_FILTER_IMAC			0x000A
#घोषणा I40E_AQC_ADD_CLOUD_FILTER_OMAC_TEN_ID_IMAC	0x000B
#घोषणा I40E_AQC_ADD_CLOUD_FILTER_IIP			0x000C
/* 0x000D reserved */
/* 0x000E reserved */
/* 0x000F reserved */
/* 0x0010 to 0x0017 is क्रम custom filters */
#घोषणा I40E_AQC_ADD_CLOUD_FILTER_IP_PORT		0x0010 /* Dest IP + L4 Port */
#घोषणा I40E_AQC_ADD_CLOUD_FILTER_MAC_PORT		0x0011 /* Dest MAC + L4 Port */
#घोषणा I40E_AQC_ADD_CLOUD_FILTER_MAC_VLAN_PORT		0x0012 /* Dest MAC + VLAN + L4 Port */

#घोषणा I40E_AQC_ADD_CLOUD_FLAGS_IPV4			0
#घोषणा I40E_AQC_ADD_CLOUD_FLAGS_IPV6			0x0100

#घोषणा I40E_AQC_ADD_CLOUD_TNL_TYPE_SHIFT		9
#घोषणा I40E_AQC_ADD_CLOUD_TNL_TYPE_MASK		0x1E00
#घोषणा I40E_AQC_ADD_CLOUD_TNL_TYPE_GENEVE		2


	__le32	tenant_id;
	u8	reserved[4];
	__le16	queue_number;
	u8	reserved2[14];
	/* response section */
	u8	allocation_result;
	u8	response_reserved[7];
पूर्ण;

I40E_CHECK_STRUCT_LEN(0x40, i40e_aqc_cloud_filters_element_data);

/* i40e_aqc_cloud_filters_element_bb is used when
 * I40E_AQC_CLOUD_CMD_BB flag is set.
 */
काष्ठा i40e_aqc_cloud_filters_element_bb अणु
	काष्ठा i40e_aqc_cloud_filters_element_data element;
	u16     general_fields[32];
#घोषणा I40E_AQC_ADD_CLOUD_FV_FLU_0X16_WORD0	15
पूर्ण;

I40E_CHECK_STRUCT_LEN(0x80, i40e_aqc_cloud_filters_element_bb);

काष्ठा i40e_aqc_हटाओ_cloud_filters_completion अणु
	__le16 perfect_ovlan_used;
	__le16 perfect_ovlan_मुक्त;
	__le16 vlan_used;
	__le16 vlan_मुक्त;
	__le32 addr_high;
	__le32 addr_low;
पूर्ण;

I40E_CHECK_CMD_LENGTH(i40e_aqc_हटाओ_cloud_filters_completion);

/* Replace filter Command 0x025F
 * uses the i40e_aqc_replace_cloud_filters,
 * and the generic indirect completion काष्ठाure
 */
काष्ठा i40e_filter_data अणु
	u8 filter_type;
	u8 input[3];
पूर्ण;

I40E_CHECK_STRUCT_LEN(4, i40e_filter_data);

काष्ठा i40e_aqc_replace_cloud_filters_cmd अणु
	u8      valid_flags;
	u8      old_filter_type;
	u8      new_filter_type;
	u8      tr_bit;
	u8      reserved[4];
	__le32 addr_high;
	__le32 addr_low;
पूर्ण;

I40E_CHECK_CMD_LENGTH(i40e_aqc_replace_cloud_filters_cmd);

काष्ठा i40e_aqc_replace_cloud_filters_cmd_buf अणु
	u8      data[32];
	काष्ठा i40e_filter_data filters[8];
पूर्ण;

I40E_CHECK_STRUCT_LEN(0x40, i40e_aqc_replace_cloud_filters_cmd_buf);

/* Add Mirror Rule (indirect or direct 0x0260)
 * Delete Mirror Rule (indirect or direct 0x0261)
 * note: some rule types (4,5) करो not use an बाह्यal buffer.
 *       take care to set the flags correctly.
 */
काष्ठा i40e_aqc_add_delete_mirror_rule अणु
	__le16 seid;
	__le16 rule_type;
#घोषणा I40E_AQC_MIRROR_RULE_TYPE_SHIFT		0
#घोषणा I40E_AQC_MIRROR_RULE_TYPE_MASK		(0x7 << \
						I40E_AQC_MIRROR_RULE_TYPE_SHIFT)
#घोषणा I40E_AQC_MIRROR_RULE_TYPE_VLAN		3
#घोषणा I40E_AQC_MIRROR_RULE_TYPE_ALL_INGRESS	4
#घोषणा I40E_AQC_MIRROR_RULE_TYPE_ALL_EGRESS	5
	__le16 num_entries;
	__le16 destination;  /* VSI क्रम add, rule id क्रम delete */
	__le32 addr_high;    /* address of array of 2-byte VSI or VLAN ids */
	__le32 addr_low;
पूर्ण;

I40E_CHECK_CMD_LENGTH(i40e_aqc_add_delete_mirror_rule);

काष्ठा i40e_aqc_add_delete_mirror_rule_completion अणु
	u8	reserved[2];
	__le16	rule_id;  /* only used on add */
	__le16	mirror_rules_used;
	__le16	mirror_rules_मुक्त;
	__le32	addr_high;
	__le32	addr_low;
पूर्ण;

I40E_CHECK_CMD_LENGTH(i40e_aqc_add_delete_mirror_rule_completion);

/* Dynamic Device Personalization */
काष्ठा i40e_aqc_ग_लिखो_personalization_profile अणु
	u8      flags;
	u8      reserved[3];
	__le32  profile_track_id;
	__le32  addr_high;
	__le32  addr_low;
पूर्ण;

I40E_CHECK_CMD_LENGTH(i40e_aqc_ग_लिखो_personalization_profile);

काष्ठा i40e_aqc_ग_लिखो_ddp_resp अणु
	__le32 error_offset;
	__le32 error_info;
	__le32 addr_high;
	__le32 addr_low;
पूर्ण;

काष्ठा i40e_aqc_get_applied_profiles अणु
	u8      flags;
	u8      rsv[3];
	__le32  reserved;
	__le32  addr_high;
	__le32  addr_low;
पूर्ण;

I40E_CHECK_CMD_LENGTH(i40e_aqc_get_applied_profiles);

/* DCB 0x03xx*/

/* PFC Ignore (direct 0x0301)
 *    the command and response use the same descriptor काष्ठाure
 */
काष्ठा i40e_aqc_pfc_ignore अणु
	u8	tc_biपंचांगap;
	u8	command_flags; /* unused on response */
	u8	reserved[14];
पूर्ण;

I40E_CHECK_CMD_LENGTH(i40e_aqc_pfc_ignore);

/* DCB Update (direct 0x0302) uses the i40e_aq_desc काष्ठाure
 * with no parameters
 */

/* TX scheduler 0x04xx */

/* Almost all the indirect commands use
 * this generic काष्ठा to pass the SEID in param0
 */
काष्ठा i40e_aqc_tx_sched_ind अणु
	__le16	vsi_seid;
	u8	reserved[6];
	__le32	addr_high;
	__le32	addr_low;
पूर्ण;

I40E_CHECK_CMD_LENGTH(i40e_aqc_tx_sched_ind);

/* Several commands respond with a set of queue set handles */
काष्ठा i40e_aqc_qs_handles_resp अणु
	__le16 qs_handles[8];
पूर्ण;

/* Configure VSI BW limits (direct 0x0400) */
काष्ठा i40e_aqc_configure_vsi_bw_limit अणु
	__le16	vsi_seid;
	u8	reserved[2];
	__le16	credit;
	u8	reserved1[2];
	u8	max_credit; /* 0-3, limit = 2^max */
	u8	reserved2[7];
पूर्ण;

I40E_CHECK_CMD_LENGTH(i40e_aqc_configure_vsi_bw_limit);

/* Configure VSI Bandwidth Limit per Traffic Type (indirect 0x0406)
 *    responds with i40e_aqc_qs_handles_resp
 */
काष्ठा i40e_aqc_configure_vsi_ets_sla_bw_data अणु
	u8	tc_valid_bits;
	u8	reserved[15];
	__le16	tc_bw_credits[8]; /* FW ग_लिखोsback QS handles here */

	/* 4 bits per tc 0-7, 4th bit is reserved, limit = 2^max */
	__le16	tc_bw_max[2];
	u8	reserved1[28];
पूर्ण;

I40E_CHECK_STRUCT_LEN(0x40, i40e_aqc_configure_vsi_ets_sla_bw_data);

/* Configure VSI Bandwidth Allocation per Traffic Type (indirect 0x0407)
 *    responds with i40e_aqc_qs_handles_resp
 */
काष्ठा i40e_aqc_configure_vsi_tc_bw_data अणु
	u8	tc_valid_bits;
	u8	reserved[3];
	u8	tc_bw_credits[8];
	u8	reserved1[4];
	__le16	qs_handles[8];
पूर्ण;

I40E_CHECK_STRUCT_LEN(0x20, i40e_aqc_configure_vsi_tc_bw_data);

/* Query vsi bw configuration (indirect 0x0408) */
काष्ठा i40e_aqc_query_vsi_bw_config_resp अणु
	u8	tc_valid_bits;
	u8	tc_suspended_bits;
	u8	reserved[14];
	__le16	qs_handles[8];
	u8	reserved1[4];
	__le16	port_bw_limit;
	u8	reserved2[2];
	u8	max_bw; /* 0-3, limit = 2^max */
	u8	reserved3[23];
पूर्ण;

I40E_CHECK_STRUCT_LEN(0x40, i40e_aqc_query_vsi_bw_config_resp);

/* Query VSI Bandwidth Allocation per Traffic Type (indirect 0x040A) */
काष्ठा i40e_aqc_query_vsi_ets_sla_config_resp अणु
	u8	tc_valid_bits;
	u8	reserved[3];
	u8	share_credits[8];
	__le16	credits[8];

	/* 4 bits per tc 0-7, 4th bit is reserved, limit = 2^max */
	__le16	tc_bw_max[2];
पूर्ण;

I40E_CHECK_STRUCT_LEN(0x20, i40e_aqc_query_vsi_ets_sla_config_resp);

/* Configure Switching Component Bandwidth Limit (direct 0x0410) */
काष्ठा i40e_aqc_configure_चयनing_comp_bw_limit अणु
	__le16	seid;
	u8	reserved[2];
	__le16	credit;
	u8	reserved1[2];
	u8	max_bw; /* 0-3, limit = 2^max */
	u8	reserved2[7];
पूर्ण;

I40E_CHECK_CMD_LENGTH(i40e_aqc_configure_चयनing_comp_bw_limit);

/* Enable  Physical Port ETS (indirect 0x0413)
 * Modअगरy  Physical Port ETS (indirect 0x0414)
 * Disable Physical Port ETS (indirect 0x0415)
 */
काष्ठा i40e_aqc_configure_चयनing_comp_ets_data अणु
	u8	reserved[4];
	u8	tc_valid_bits;
	u8	seepage;
	u8	tc_strict_priority_flags;
	u8	reserved1[17];
	u8	tc_bw_share_credits[8];
	u8	reserved2[96];
पूर्ण;

I40E_CHECK_STRUCT_LEN(0x80, i40e_aqc_configure_चयनing_comp_ets_data);

/* Configure Switching Component Bandwidth Limits per Tc (indirect 0x0416) */
काष्ठा i40e_aqc_configure_चयनing_comp_ets_bw_limit_data अणु
	u8	tc_valid_bits;
	u8	reserved[15];
	__le16	tc_bw_credit[8];

	/* 4 bits per tc 0-7, 4th bit is reserved, limit = 2^max */
	__le16	tc_bw_max[2];
	u8	reserved1[28];
पूर्ण;

I40E_CHECK_STRUCT_LEN(0x40,
		      i40e_aqc_configure_चयनing_comp_ets_bw_limit_data);

/* Configure Switching Component Bandwidth Allocation per Tc
 * (indirect 0x0417)
 */
काष्ठा i40e_aqc_configure_चयनing_comp_bw_config_data अणु
	u8	tc_valid_bits;
	u8	reserved[2];
	u8	असलolute_credits; /* bool */
	u8	tc_bw_share_credits[8];
	u8	reserved1[20];
पूर्ण;

I40E_CHECK_STRUCT_LEN(0x20, i40e_aqc_configure_चयनing_comp_bw_config_data);

/* Query Switching Component Configuration (indirect 0x0418) */
काष्ठा i40e_aqc_query_चयनing_comp_ets_config_resp अणु
	u8	tc_valid_bits;
	u8	reserved[35];
	__le16	port_bw_limit;
	u8	reserved1[2];
	u8	tc_bw_max; /* 0-3, limit = 2^max */
	u8	reserved2[23];
पूर्ण;

I40E_CHECK_STRUCT_LEN(0x40, i40e_aqc_query_चयनing_comp_ets_config_resp);

/* Query PhysicalPort ETS Configuration (indirect 0x0419) */
काष्ठा i40e_aqc_query_port_ets_config_resp अणु
	u8	reserved[4];
	u8	tc_valid_bits;
	u8	reserved1;
	u8	tc_strict_priority_bits;
	u8	reserved2;
	u8	tc_bw_share_credits[8];
	__le16	tc_bw_limits[8];

	/* 4 bits per tc 0-7, 4th bit reserved, limit = 2^max */
	__le16	tc_bw_max[2];
	u8	reserved3[32];
पूर्ण;

I40E_CHECK_STRUCT_LEN(0x44, i40e_aqc_query_port_ets_config_resp);

/* Query Switching Component Bandwidth Allocation per Traffic Type
 * (indirect 0x041A)
 */
काष्ठा i40e_aqc_query_चयनing_comp_bw_config_resp अणु
	u8	tc_valid_bits;
	u8	reserved[2];
	u8	असलolute_credits_enable; /* bool */
	u8	tc_bw_share_credits[8];
	__le16	tc_bw_limits[8];

	/* 4 bits per tc 0-7, 4th bit is reserved, limit = 2^max */
	__le16	tc_bw_max[2];
पूर्ण;

I40E_CHECK_STRUCT_LEN(0x20, i40e_aqc_query_चयनing_comp_bw_config_resp);

/* Suspend/resume port TX traffic
 * (direct 0x041B and 0x041C) uses the generic SEID काष्ठा
 */

/* Configure partition BW
 * (indirect 0x041D)
 */
काष्ठा i40e_aqc_configure_partition_bw_data अणु
	__le16	pf_valid_bits;
	u8	min_bw[16];      /* guaranteed bandwidth */
	u8	max_bw[16];      /* bandwidth limit */
पूर्ण;

I40E_CHECK_STRUCT_LEN(0x22, i40e_aqc_configure_partition_bw_data);

/* Get and set the active HMC resource profile and status.
 * (direct 0x0500) and (direct 0x0501)
 */
काष्ठा i40e_aq_get_set_hmc_resource_profile अणु
	u8	pm_profile;
	u8	pe_vf_enabled;
	u8	reserved[14];
पूर्ण;

I40E_CHECK_CMD_LENGTH(i40e_aq_get_set_hmc_resource_profile);

क्रमागत i40e_aq_hmc_profile अणु
	/* I40E_HMC_PROखाता_NO_CHANGE	= 0, reserved */
	I40E_HMC_PROखाता_DEFAULT	= 1,
	I40E_HMC_PROखाता_FAVOR_VF	= 2,
	I40E_HMC_PROखाता_EQUAL		= 3,
पूर्ण;

/* Get PHY Abilities (indirect 0x0600) uses the generic indirect काष्ठा */

/* set in param0 क्रम get phy abilities to report qualअगरied modules */
#घोषणा I40E_AQ_PHY_REPORT_QUALIFIED_MODULES	0x0001
#घोषणा I40E_AQ_PHY_REPORT_INITIAL_VALUES	0x0002

क्रमागत i40e_aq_phy_type अणु
	I40E_PHY_TYPE_SGMII			= 0x0,
	I40E_PHY_TYPE_1000BASE_KX		= 0x1,
	I40E_PHY_TYPE_10GBASE_KX4		= 0x2,
	I40E_PHY_TYPE_10GBASE_KR		= 0x3,
	I40E_PHY_TYPE_40GBASE_KR4		= 0x4,
	I40E_PHY_TYPE_XAUI			= 0x5,
	I40E_PHY_TYPE_XFI			= 0x6,
	I40E_PHY_TYPE_SFI			= 0x7,
	I40E_PHY_TYPE_XLAUI			= 0x8,
	I40E_PHY_TYPE_XLPPI			= 0x9,
	I40E_PHY_TYPE_40GBASE_CR4_CU		= 0xA,
	I40E_PHY_TYPE_10GBASE_CR1_CU		= 0xB,
	I40E_PHY_TYPE_10GBASE_AOC		= 0xC,
	I40E_PHY_TYPE_40GBASE_AOC		= 0xD,
	I40E_PHY_TYPE_UNRECOGNIZED		= 0xE,
	I40E_PHY_TYPE_UNSUPPORTED		= 0xF,
	I40E_PHY_TYPE_100BASE_TX		= 0x11,
	I40E_PHY_TYPE_1000BASE_T		= 0x12,
	I40E_PHY_TYPE_10GBASE_T			= 0x13,
	I40E_PHY_TYPE_10GBASE_SR		= 0x14,
	I40E_PHY_TYPE_10GBASE_LR		= 0x15,
	I40E_PHY_TYPE_10GBASE_SFPP_CU		= 0x16,
	I40E_PHY_TYPE_10GBASE_CR1		= 0x17,
	I40E_PHY_TYPE_40GBASE_CR4		= 0x18,
	I40E_PHY_TYPE_40GBASE_SR4		= 0x19,
	I40E_PHY_TYPE_40GBASE_LR4		= 0x1A,
	I40E_PHY_TYPE_1000BASE_SX		= 0x1B,
	I40E_PHY_TYPE_1000BASE_LX		= 0x1C,
	I40E_PHY_TYPE_1000BASE_T_OPTICAL	= 0x1D,
	I40E_PHY_TYPE_20GBASE_KR2		= 0x1E,
	I40E_PHY_TYPE_25GBASE_KR		= 0x1F,
	I40E_PHY_TYPE_25GBASE_CR		= 0x20,
	I40E_PHY_TYPE_25GBASE_SR		= 0x21,
	I40E_PHY_TYPE_25GBASE_LR		= 0x22,
	I40E_PHY_TYPE_25GBASE_AOC		= 0x23,
	I40E_PHY_TYPE_25GBASE_ACC		= 0x24,
	I40E_PHY_TYPE_2_5GBASE_T		= 0x26,
	I40E_PHY_TYPE_5GBASE_T			= 0x27,
	I40E_PHY_TYPE_2_5GBASE_T_LINK_STATUS	= 0x30,
	I40E_PHY_TYPE_5GBASE_T_LINK_STATUS	= 0x31,
	I40E_PHY_TYPE_MAX,
	I40E_PHY_TYPE_NOT_SUPPORTED_HIGH_TEMP	= 0xFD,
	I40E_PHY_TYPE_EMPTY			= 0xFE,
	I40E_PHY_TYPE_DEFAULT			= 0xFF,
पूर्ण;

#घोषणा I40E_PHY_TYPES_BITMASK (BIT_ULL(I40E_PHY_TYPE_SGMII) | \
				BIT_ULL(I40E_PHY_TYPE_1000BASE_KX) | \
				BIT_ULL(I40E_PHY_TYPE_10GBASE_KX4) | \
				BIT_ULL(I40E_PHY_TYPE_10GBASE_KR) | \
				BIT_ULL(I40E_PHY_TYPE_40GBASE_KR4) | \
				BIT_ULL(I40E_PHY_TYPE_XAUI) | \
				BIT_ULL(I40E_PHY_TYPE_XFI) | \
				BIT_ULL(I40E_PHY_TYPE_SFI) | \
				BIT_ULL(I40E_PHY_TYPE_XLAUI) | \
				BIT_ULL(I40E_PHY_TYPE_XLPPI) | \
				BIT_ULL(I40E_PHY_TYPE_40GBASE_CR4_CU) | \
				BIT_ULL(I40E_PHY_TYPE_10GBASE_CR1_CU) | \
				BIT_ULL(I40E_PHY_TYPE_10GBASE_AOC) | \
				BIT_ULL(I40E_PHY_TYPE_40GBASE_AOC) | \
				BIT_ULL(I40E_PHY_TYPE_UNRECOGNIZED) | \
				BIT_ULL(I40E_PHY_TYPE_UNSUPPORTED) | \
				BIT_ULL(I40E_PHY_TYPE_100BASE_TX) | \
				BIT_ULL(I40E_PHY_TYPE_1000BASE_T) | \
				BIT_ULL(I40E_PHY_TYPE_10GBASE_T) | \
				BIT_ULL(I40E_PHY_TYPE_10GBASE_SR) | \
				BIT_ULL(I40E_PHY_TYPE_10GBASE_LR) | \
				BIT_ULL(I40E_PHY_TYPE_10GBASE_SFPP_CU) | \
				BIT_ULL(I40E_PHY_TYPE_10GBASE_CR1) | \
				BIT_ULL(I40E_PHY_TYPE_40GBASE_CR4) | \
				BIT_ULL(I40E_PHY_TYPE_40GBASE_SR4) | \
				BIT_ULL(I40E_PHY_TYPE_40GBASE_LR4) | \
				BIT_ULL(I40E_PHY_TYPE_1000BASE_SX) | \
				BIT_ULL(I40E_PHY_TYPE_1000BASE_LX) | \
				BIT_ULL(I40E_PHY_TYPE_1000BASE_T_OPTICAL) | \
				BIT_ULL(I40E_PHY_TYPE_20GBASE_KR2) | \
				BIT_ULL(I40E_PHY_TYPE_25GBASE_KR) | \
				BIT_ULL(I40E_PHY_TYPE_25GBASE_CR) | \
				BIT_ULL(I40E_PHY_TYPE_25GBASE_SR) | \
				BIT_ULL(I40E_PHY_TYPE_25GBASE_LR) | \
				BIT_ULL(I40E_PHY_TYPE_25GBASE_AOC) | \
				BIT_ULL(I40E_PHY_TYPE_25GBASE_ACC) | \
				BIT_ULL(I40E_PHY_TYPE_2_5GBASE_T) | \
				BIT_ULL(I40E_PHY_TYPE_5GBASE_T))

#घोषणा I40E_LINK_SPEED_2_5GB_SHIFT	0x0
#घोषणा I40E_LINK_SPEED_100MB_SHIFT	0x1
#घोषणा I40E_LINK_SPEED_1000MB_SHIFT	0x2
#घोषणा I40E_LINK_SPEED_10GB_SHIFT	0x3
#घोषणा I40E_LINK_SPEED_40GB_SHIFT	0x4
#घोषणा I40E_LINK_SPEED_20GB_SHIFT	0x5
#घोषणा I40E_LINK_SPEED_25GB_SHIFT	0x6
#घोषणा I40E_LINK_SPEED_5GB_SHIFT	0x7

क्रमागत i40e_aq_link_speed अणु
	I40E_LINK_SPEED_UNKNOWN	= 0,
	I40E_LINK_SPEED_100MB	= BIT(I40E_LINK_SPEED_100MB_SHIFT),
	I40E_LINK_SPEED_1GB	= BIT(I40E_LINK_SPEED_1000MB_SHIFT),
	I40E_LINK_SPEED_2_5GB	= (1 << I40E_LINK_SPEED_2_5GB_SHIFT),
	I40E_LINK_SPEED_5GB	= (1 << I40E_LINK_SPEED_5GB_SHIFT),
	I40E_LINK_SPEED_10GB	= BIT(I40E_LINK_SPEED_10GB_SHIFT),
	I40E_LINK_SPEED_40GB	= BIT(I40E_LINK_SPEED_40GB_SHIFT),
	I40E_LINK_SPEED_20GB	= BIT(I40E_LINK_SPEED_20GB_SHIFT),
	I40E_LINK_SPEED_25GB	= BIT(I40E_LINK_SPEED_25GB_SHIFT),
पूर्ण;

काष्ठा i40e_aqc_module_desc अणु
	u8 oui[3];
	u8 reserved1;
	u8 part_number[16];
	u8 revision[4];
	u8 reserved2[8];
पूर्ण;

I40E_CHECK_STRUCT_LEN(0x20, i40e_aqc_module_desc);

काष्ठा i40e_aq_get_phy_abilities_resp अणु
	__le32	phy_type;       /* biपंचांगap using the above क्रमागत क्रम offsets */
	u8	link_speed;     /* biपंचांगap using the above क्रमागत bit patterns */
	u8	abilities;
#घोषणा I40E_AQ_PHY_FLAG_PAUSE_TX	0x01
#घोषणा I40E_AQ_PHY_FLAG_PAUSE_RX	0x02
	__le16	eee_capability;
	__le32	eeer_val;
	u8	d3_lpan;
	u8	phy_type_ext;
#घोषणा I40E_AQ_PHY_TYPE_EXT_25G_KR	0X01
#घोषणा I40E_AQ_PHY_TYPE_EXT_25G_CR	0X02
#घोषणा I40E_AQ_PHY_TYPE_EXT_25G_SR	0x04
#घोषणा I40E_AQ_PHY_TYPE_EXT_25G_LR	0x08
	u8	fec_cfg_curr_mod_ext_info;
#घोषणा I40E_AQ_REQUEST_FEC_KR		0x04
#घोषणा I40E_AQ_REQUEST_FEC_RS		0x08
#घोषणा I40E_AQ_ENABLE_FEC_AUTO		0x10

	u8	ext_comp_code;
	u8	phy_id[4];
	u8	module_type[3];
	u8	qualअगरied_module_count;
#घोषणा I40E_AQ_PHY_MAX_QMS		16
	काष्ठा i40e_aqc_module_desc	qualअगरied_module[I40E_AQ_PHY_MAX_QMS];
पूर्ण;

I40E_CHECK_STRUCT_LEN(0x218, i40e_aq_get_phy_abilities_resp);

/* Set PHY Config (direct 0x0601) */
काष्ठा i40e_aq_set_phy_config अणु /* same bits as above in all */
	__le32	phy_type;
	u8	link_speed;
	u8	abilities;
/* bits 0-2 use the values from get_phy_abilities_resp */
#घोषणा I40E_AQ_PHY_ENABLE_LINK		0x08
#घोषणा I40E_AQ_PHY_ENABLE_AN		0x10
#घोषणा I40E_AQ_PHY_ENABLE_ATOMIC_LINK	0x20
	__le16	eee_capability;
	__le32	eeer;
	u8	low_घातer_ctrl;
	u8	phy_type_ext;
#घोषणा I40E_AQ_PHY_TYPE_EXT_25G_KR	0X01
#घोषणा I40E_AQ_PHY_TYPE_EXT_25G_CR	0X02
#घोषणा I40E_AQ_PHY_TYPE_EXT_25G_SR	0x04
#घोषणा I40E_AQ_PHY_TYPE_EXT_25G_LR	0x08
	u8	fec_config;
#घोषणा I40E_AQ_SET_FEC_ABILITY_KR	BIT(0)
#घोषणा I40E_AQ_SET_FEC_ABILITY_RS	BIT(1)
#घोषणा I40E_AQ_SET_FEC_REQUEST_KR	BIT(2)
#घोषणा I40E_AQ_SET_FEC_REQUEST_RS	BIT(3)
#घोषणा I40E_AQ_SET_FEC_AUTO		BIT(4)
#घोषणा I40E_AQ_PHY_FEC_CONFIG_SHIFT	0x0
#घोषणा I40E_AQ_PHY_FEC_CONFIG_MASK	(0x1F << I40E_AQ_PHY_FEC_CONFIG_SHIFT)
	u8	reserved;
पूर्ण;

I40E_CHECK_CMD_LENGTH(i40e_aq_set_phy_config);

/* Set MAC Config command data काष्ठाure (direct 0x0603) */
काष्ठा i40e_aq_set_mac_config अणु
	__le16	max_frame_size;
	u8	params;
	u8	tx_समयr_priority; /* biपंचांगap */
	__le16	tx_समयr_value;
	__le16	fc_refresh_threshold;
	u8	reserved[8];
पूर्ण;

I40E_CHECK_CMD_LENGTH(i40e_aq_set_mac_config);

/* Restart Auto-Negotiation (direct 0x605) */
काष्ठा i40e_aqc_set_link_restart_an अणु
	u8	command;
#घोषणा I40E_AQ_PHY_RESTART_AN	0x02
#घोषणा I40E_AQ_PHY_LINK_ENABLE	0x04
	u8	reserved[15];
पूर्ण;

I40E_CHECK_CMD_LENGTH(i40e_aqc_set_link_restart_an);

/* Get Link Status cmd & response data काष्ठाure (direct 0x0607) */
काष्ठा i40e_aqc_get_link_status अणु
	__le16	command_flags; /* only field set on command */
#घोषणा I40E_AQ_LSE_DISABLE		0x2
#घोषणा I40E_AQ_LSE_ENABLE		0x3
/* only response uses this flag */
#घोषणा I40E_AQ_LSE_IS_ENABLED		0x1
	u8	phy_type;    /* i40e_aq_phy_type   */
	u8	link_speed;  /* i40e_aq_link_speed */
	u8	link_info;
#घोषणा I40E_AQ_LINK_UP			0x01    /* obsolete */
#घोषणा I40E_AQ_MEDIA_AVAILABLE		0x40
	u8	an_info;
#घोषणा I40E_AQ_AN_COMPLETED		0x01
#घोषणा I40E_AQ_LINK_PAUSE_TX		0x20
#घोषणा I40E_AQ_LINK_PAUSE_RX		0x40
#घोषणा I40E_AQ_QUALIFIED_MODULE	0x80
	u8	ext_info;
	u8	loopback; /* use defines from i40e_aqc_set_lb_mode */
/* Since firmware API 1.7 loopback field keeps घातer class info as well */
#घोषणा I40E_AQ_LOOPBACK_MASK		0x07
	__le16	max_frame_size;
	u8	config;
#घोषणा I40E_AQ_CONFIG_FEC_KR_ENA	0x01
#घोषणा I40E_AQ_CONFIG_FEC_RS_ENA	0x02
#घोषणा I40E_AQ_CONFIG_CRC_ENA		0x04
#घोषणा I40E_AQ_CONFIG_PACING_MASK	0x78
	जोड़ अणु
		काष्ठा अणु
			u8	घातer_desc;
			u8	reserved[4];
		पूर्ण;
		काष्ठा अणु
			u8	link_type[4];
			u8	link_type_ext;
		पूर्ण;
	पूर्ण;
पूर्ण;

I40E_CHECK_CMD_LENGTH(i40e_aqc_get_link_status);

/* Set event mask command (direct 0x613) */
काष्ठा i40e_aqc_set_phy_पूर्णांक_mask अणु
	u8	reserved[8];
	__le16	event_mask;
#घोषणा I40E_AQ_EVENT_LINK_UPDOWN	0x0002
#घोषणा I40E_AQ_EVENT_MEDIA_NA		0x0004
#घोषणा I40E_AQ_EVENT_MODULE_QUAL_FAIL	0x0100
	u8	reserved1[6];
पूर्ण;

I40E_CHECK_CMD_LENGTH(i40e_aqc_set_phy_पूर्णांक_mask);

/* Get Local AN advt रेजिस्टर (direct 0x0614)
 * Set Local AN advt रेजिस्टर (direct 0x0615)
 * Get Link Partner AN advt रेजिस्टर (direct 0x0616)
 */
काष्ठा i40e_aqc_an_advt_reg अणु
	__le32	local_an_reg0;
	__le16	local_an_reg1;
	u8	reserved[10];
पूर्ण;

I40E_CHECK_CMD_LENGTH(i40e_aqc_an_advt_reg);

/* Set Loopback mode (0x0618) */
काष्ठा i40e_aqc_set_lb_mode अणु
	__le16	lb_mode;
#घोषणा I40E_AQ_LB_PHY_LOCAL	0x01
#घोषणा I40E_AQ_LB_PHY_REMOTE	0x02
#घोषणा I40E_AQ_LB_MAC_LOCAL	0x04
	u8	reserved[14];
पूर्ण;

I40E_CHECK_CMD_LENGTH(i40e_aqc_set_lb_mode);

/* Set PHY Debug command (0x0622) */
काष्ठा i40e_aqc_set_phy_debug अणु
	u8	command_flags;
/* Disable link manageability on a single port */
#घोषणा I40E_AQ_PHY_DEBUG_DISABLE_LINK_FW	0x10
/* Disable link manageability on all ports */
#घोषणा I40E_AQ_PHY_DEBUG_DISABLE_ALL_LINK_FW	0x20
	u8	reserved[15];
पूर्ण;

I40E_CHECK_CMD_LENGTH(i40e_aqc_set_phy_debug);

क्रमागत i40e_aq_phy_reg_type अणु
	I40E_AQC_PHY_REG_INTERNAL	= 0x1,
	I40E_AQC_PHY_REG_EXERNAL_BASET	= 0x2,
	I40E_AQC_PHY_REG_EXERNAL_MODULE	= 0x3
पूर्ण;

/* Run PHY Activity (0x0626) */
काष्ठा i40e_aqc_run_phy_activity अणु
	__le16  activity_id;
	u8      flags;
	u8      reserved1;
	__le32  control;
	__le32  data;
	u8      reserved2[4];
पूर्ण;

I40E_CHECK_CMD_LENGTH(i40e_aqc_run_phy_activity);

/* Set PHY Register command (0x0628) */
/* Get PHY Register command (0x0629) */
काष्ठा i40e_aqc_phy_रेजिस्टर_access अणु
	u8	phy_पूर्णांकerface;
#घोषणा I40E_AQ_PHY_REG_ACCESS_EXTERNAL	1
#घोषणा I40E_AQ_PHY_REG_ACCESS_EXTERNAL_MODULE	2
	u8	dev_address;
	u8	cmd_flags;
#घोषणा I40E_AQ_PHY_REG_ACCESS_DONT_CHANGE_QSFP_PAGE	0x01
#घोषणा I40E_AQ_PHY_REG_ACCESS_SET_MDIO_IF_NUMBER	0x02
#घोषणा I40E_AQ_PHY_REG_ACCESS_MDIO_IF_NUMBER_SHIFT	2
#घोषणा I40E_AQ_PHY_REG_ACCESS_MDIO_IF_NUMBER_MASK	(0x3 << \
		I40E_AQ_PHY_REG_ACCESS_MDIO_IF_NUMBER_SHIFT)
	u8	reserved1;
	__le32	reg_address;
	__le32	reg_value;
	u8	reserved2[4];
पूर्ण;

I40E_CHECK_CMD_LENGTH(i40e_aqc_phy_रेजिस्टर_access);

/* NVM Read command (indirect 0x0701)
 * NVM Erase commands (direct 0x0702)
 * NVM Update commands (indirect 0x0703)
 */
काष्ठा i40e_aqc_nvm_update अणु
	u8	command_flags;
#घोषणा I40E_AQ_NVM_LAST_CMD			0x01
#घोषणा I40E_AQ_NVM_REARRANGE_TO_FLAT		0x20
#घोषणा I40E_AQ_NVM_REARRANGE_TO_STRUCT		0x40
#घोषणा I40E_AQ_NVM_PRESERVATION_FLAGS_SHIFT	1
#घोषणा I40E_AQ_NVM_PRESERVATION_FLAGS_SELECTED	0x03
#घोषणा I40E_AQ_NVM_PRESERVATION_FLAGS_ALL	0x01
	u8	module_poपूर्णांकer;
	__le16	length;
	__le32	offset;
	__le32	addr_high;
	__le32	addr_low;
पूर्ण;

I40E_CHECK_CMD_LENGTH(i40e_aqc_nvm_update);

/* NVM Config Read (indirect 0x0704) */
काष्ठा i40e_aqc_nvm_config_पढ़ो अणु
	__le16	cmd_flags;
	__le16	element_count;
	__le16	element_id;	/* Feature/field ID */
	__le16	element_id_msw;	/* MSWord of field ID */
	__le32	address_high;
	__le32	address_low;
पूर्ण;

I40E_CHECK_CMD_LENGTH(i40e_aqc_nvm_config_पढ़ो);

/* NVM Config Write (indirect 0x0705) */
काष्ठा i40e_aqc_nvm_config_ग_लिखो अणु
	__le16	cmd_flags;
	__le16	element_count;
	u8	reserved[4];
	__le32	address_high;
	__le32	address_low;
पूर्ण;

I40E_CHECK_CMD_LENGTH(i40e_aqc_nvm_config_ग_लिखो);

/* Used क्रम 0x0704 as well as क्रम 0x0705 commands */
काष्ठा i40e_aqc_nvm_config_data_feature अणु
	__le16 feature_id;
	__le16 feature_options;
	__le16 feature_selection;
पूर्ण;

I40E_CHECK_STRUCT_LEN(0x6, i40e_aqc_nvm_config_data_feature);

काष्ठा i40e_aqc_nvm_config_data_immediate_field अणु
	__le32 field_id;
	__le32 field_value;
	__le16 field_options;
	__le16 reserved;
पूर्ण;

I40E_CHECK_STRUCT_LEN(0xc, i40e_aqc_nvm_config_data_immediate_field);

/* OEM Post Update (indirect 0x0720)
 * no command data काष्ठा used
 */
काष्ठा i40e_aqc_nvm_oem_post_update अणु
	u8 sel_data;
	u8 reserved[7];
पूर्ण;

I40E_CHECK_STRUCT_LEN(0x8, i40e_aqc_nvm_oem_post_update);

काष्ठा i40e_aqc_nvm_oem_post_update_buffer अणु
	u8 str_len;
	u8 dev_addr;
	__le16 eeprom_addr;
	u8 data[36];
पूर्ण;

I40E_CHECK_STRUCT_LEN(0x28, i40e_aqc_nvm_oem_post_update_buffer);

/* Thermal Sensor (indirect 0x0721)
 *     पढ़ो or set thermal sensor configs and values
 *     takes a sensor and command specअगरic data buffer, not detailed here
 */
काष्ठा i40e_aqc_thermal_sensor अणु
	u8 sensor_action;
	u8 reserved[7];
	__le32	addr_high;
	__le32	addr_low;
पूर्ण;

I40E_CHECK_CMD_LENGTH(i40e_aqc_thermal_sensor);

/* Send to PF command (indirect 0x0801) id is only used by PF
 * Send to VF command (indirect 0x0802) id is only used by PF
 * Send to Peer PF command (indirect 0x0803)
 */
काष्ठा i40e_aqc_pf_vf_message अणु
	__le32	id;
	u8	reserved[4];
	__le32	addr_high;
	__le32	addr_low;
पूर्ण;

I40E_CHECK_CMD_LENGTH(i40e_aqc_pf_vf_message);

/* Alternate काष्ठाure */

/* Direct ग_लिखो (direct 0x0900)
 * Direct पढ़ो (direct 0x0902)
 */
काष्ठा i40e_aqc_alternate_ग_लिखो अणु
	__le32 address0;
	__le32 data0;
	__le32 address1;
	__le32 data1;
पूर्ण;

I40E_CHECK_CMD_LENGTH(i40e_aqc_alternate_ग_लिखो);

/* Indirect ग_लिखो (indirect 0x0901)
 * Indirect पढ़ो (indirect 0x0903)
 */

काष्ठा i40e_aqc_alternate_ind_ग_लिखो अणु
	__le32 address;
	__le32 length;
	__le32 addr_high;
	__le32 addr_low;
पूर्ण;

I40E_CHECK_CMD_LENGTH(i40e_aqc_alternate_ind_ग_लिखो);

/* Done alternate ग_लिखो (direct 0x0904)
 * uses i40e_aq_desc
 */
काष्ठा i40e_aqc_alternate_ग_लिखो_करोne अणु
	__le16	cmd_flags;
	u8	reserved[14];
पूर्ण;

I40E_CHECK_CMD_LENGTH(i40e_aqc_alternate_ग_लिखो_करोne);

/* Set OEM mode (direct 0x0905) */
काष्ठा i40e_aqc_alternate_set_mode अणु
	__le32	mode;
	u8	reserved[12];
पूर्ण;

I40E_CHECK_CMD_LENGTH(i40e_aqc_alternate_set_mode);

/* Clear port Alternate RAM (direct 0x0906) uses i40e_aq_desc */

/* async events 0x10xx */

/* Lan Queue Overflow Event (direct, 0x1001) */
काष्ठा i40e_aqc_lan_overflow अणु
	__le32	prtdcb_rupto;
	__le32	otx_ctl;
	u8	reserved[8];
पूर्ण;

I40E_CHECK_CMD_LENGTH(i40e_aqc_lan_overflow);

/* Get LLDP MIB (indirect 0x0A00) */
काष्ठा i40e_aqc_lldp_get_mib अणु
	u8	type;
	u8	reserved1;
#घोषणा I40E_AQ_LLDP_MIB_TYPE_MASK		0x3
#घोषणा I40E_AQ_LLDP_MIB_LOCAL			0x0
#घोषणा I40E_AQ_LLDP_MIB_REMOTE			0x1
#घोषणा I40E_AQ_LLDP_BRIDGE_TYPE_MASK		0xC
#घोषणा I40E_AQ_LLDP_BRIDGE_TYPE_SHIFT		0x2
#घोषणा I40E_AQ_LLDP_BRIDGE_TYPE_NEAREST_BRIDGE	0x0
/* TX छोड़ो flags use I40E_AQ_LINK_TX_* above */
	__le16	local_len;
	__le16	remote_len;
	u8	reserved2[2];
	__le32	addr_high;
	__le32	addr_low;
पूर्ण;

I40E_CHECK_CMD_LENGTH(i40e_aqc_lldp_get_mib);

/* Configure LLDP MIB Change Event (direct 0x0A01)
 * also used क्रम the event (with type in the command field)
 */
काष्ठा i40e_aqc_lldp_update_mib अणु
	u8	command;
#घोषणा I40E_AQ_LLDP_MIB_UPDATE_DISABLE	0x1
	u8	reserved[7];
	__le32	addr_high;
	__le32	addr_low;
पूर्ण;

I40E_CHECK_CMD_LENGTH(i40e_aqc_lldp_update_mib);

/* Add LLDP TLV (indirect 0x0A02)
 * Delete LLDP TLV (indirect 0x0A04)
 */
काष्ठा i40e_aqc_lldp_add_tlv अणु
	u8	type; /* only nearest bridge and non-TPMR from 0x0A00 */
	u8	reserved1[1];
	__le16	len;
	u8	reserved2[4];
	__le32	addr_high;
	__le32	addr_low;
पूर्ण;

I40E_CHECK_CMD_LENGTH(i40e_aqc_lldp_add_tlv);

/* Update LLDP TLV (indirect 0x0A03) */
काष्ठा i40e_aqc_lldp_update_tlv अणु
	u8	type; /* only nearest bridge and non-TPMR from 0x0A00 */
	u8	reserved;
	__le16	old_len;
	__le16	new_offset;
	__le16	new_len;
	__le32	addr_high;
	__le32	addr_low;
पूर्ण;

I40E_CHECK_CMD_LENGTH(i40e_aqc_lldp_update_tlv);

/* Stop LLDP (direct 0x0A05) */
काष्ठा i40e_aqc_lldp_stop अणु
	u8	command;
#घोषणा I40E_AQ_LLDP_AGENT_SHUTDOWN		0x1
#घोषणा I40E_AQ_LLDP_AGENT_STOP_PERSIST		0x2
	u8	reserved[15];
पूर्ण;

I40E_CHECK_CMD_LENGTH(i40e_aqc_lldp_stop);

/* Start LLDP (direct 0x0A06) */
काष्ठा i40e_aqc_lldp_start अणु
	u8	command;
#घोषणा I40E_AQ_LLDP_AGENT_START		0x1
#घोषणा I40E_AQ_LLDP_AGENT_START_PERSIST	0x2
	u8	reserved[15];
पूर्ण;

I40E_CHECK_CMD_LENGTH(i40e_aqc_lldp_start);

/* Set DCB (direct 0x0303) */
काष्ठा i40e_aqc_set_dcb_parameters अणु
	u8 command;
#घोषणा I40E_AQ_DCB_SET_AGENT	0x1
#घोषणा I40E_DCB_VALID		0x1
	u8 valid_flags;
	u8 reserved[14];
पूर्ण;

I40E_CHECK_CMD_LENGTH(i40e_aqc_set_dcb_parameters);

/* Get CEE DCBX Oper Config (0x0A07)
 * uses the generic descriptor काष्ठा
 * वापसs below as indirect response
 */

#घोषणा I40E_AQC_CEE_APP_FCOE_SHIFT	0x0
#घोषणा I40E_AQC_CEE_APP_FCOE_MASK	(0x7 << I40E_AQC_CEE_APP_FCOE_SHIFT)
#घोषणा I40E_AQC_CEE_APP_ISCSI_SHIFT	0x3
#घोषणा I40E_AQC_CEE_APP_ISCSI_MASK	(0x7 << I40E_AQC_CEE_APP_ISCSI_SHIFT)
#घोषणा I40E_AQC_CEE_APP_FIP_SHIFT	0x8
#घोषणा I40E_AQC_CEE_APP_FIP_MASK	(0x7 << I40E_AQC_CEE_APP_FIP_SHIFT)

#घोषणा I40E_AQC_CEE_PG_STATUS_SHIFT	0x0
#घोषणा I40E_AQC_CEE_PG_STATUS_MASK	(0x7 << I40E_AQC_CEE_PG_STATUS_SHIFT)
#घोषणा I40E_AQC_CEE_PFC_STATUS_SHIFT	0x3
#घोषणा I40E_AQC_CEE_PFC_STATUS_MASK	(0x7 << I40E_AQC_CEE_PFC_STATUS_SHIFT)
#घोषणा I40E_AQC_CEE_APP_STATUS_SHIFT	0x8
#घोषणा I40E_AQC_CEE_APP_STATUS_MASK	(0x7 << I40E_AQC_CEE_APP_STATUS_SHIFT)
#घोषणा I40E_AQC_CEE_FCOE_STATUS_SHIFT	0x8
#घोषणा I40E_AQC_CEE_FCOE_STATUS_MASK	(0x7 << I40E_AQC_CEE_FCOE_STATUS_SHIFT)
#घोषणा I40E_AQC_CEE_ISCSI_STATUS_SHIFT	0xB
#घोषणा I40E_AQC_CEE_ISCSI_STATUS_MASK	(0x7 << I40E_AQC_CEE_ISCSI_STATUS_SHIFT)
#घोषणा I40E_AQC_CEE_FIP_STATUS_SHIFT	0x10
#घोषणा I40E_AQC_CEE_FIP_STATUS_MASK	(0x7 << I40E_AQC_CEE_FIP_STATUS_SHIFT)

/* काष्ठा i40e_aqc_get_cee_dcb_cfg_v1_resp was originally defined with
 * word boundary layout issues, which the Linux compilers silently deal
 * with by adding padding, making the actual काष्ठा larger than deचिन्हित.
 * However, the FW compiler क्रम the NIC is less lenient and complains
 * about the काष्ठा.  Hence, the काष्ठा defined here has an extra byte in
 * fields reserved3 and reserved4 to directly acknowledge that padding,
 * and the new length is used in the length check macro.
 */
काष्ठा i40e_aqc_get_cee_dcb_cfg_v1_resp अणु
	u8	reserved1;
	u8	oper_num_tc;
	u8	oper_prio_tc[4];
	u8	reserved2;
	u8	oper_tc_bw[8];
	u8	oper_pfc_en;
	u8	reserved3[2];
	__le16	oper_app_prio;
	u8	reserved4[2];
	__le16	tlv_status;
पूर्ण;

I40E_CHECK_STRUCT_LEN(0x18, i40e_aqc_get_cee_dcb_cfg_v1_resp);

काष्ठा i40e_aqc_get_cee_dcb_cfg_resp अणु
	u8	oper_num_tc;
	u8	oper_prio_tc[4];
	u8	oper_tc_bw[8];
	u8	oper_pfc_en;
	__le16	oper_app_prio;
#घोषणा I40E_AQC_CEE_APP_FCOE_SHIFT	0x0
#घोषणा I40E_AQC_CEE_APP_FCOE_MASK	(0x7 << I40E_AQC_CEE_APP_FCOE_SHIFT)
#घोषणा I40E_AQC_CEE_APP_ISCSI_SHIFT	0x3
#घोषणा I40E_AQC_CEE_APP_ISCSI_MASK	(0x7 << I40E_AQC_CEE_APP_ISCSI_SHIFT)
#घोषणा I40E_AQC_CEE_APP_FIP_SHIFT	0x8
#घोषणा I40E_AQC_CEE_APP_FIP_MASK	(0x7 << I40E_AQC_CEE_APP_FIP_SHIFT)
#घोषणा I40E_AQC_CEE_APP_FIP_MASK	(0x7 << I40E_AQC_CEE_APP_FIP_SHIFT)
	__le32	tlv_status;
#घोषणा I40E_AQC_CEE_PG_STATUS_SHIFT	0x0
#घोषणा I40E_AQC_CEE_PG_STATUS_MASK	(0x7 << I40E_AQC_CEE_PG_STATUS_SHIFT)
#घोषणा I40E_AQC_CEE_PFC_STATUS_SHIFT	0x3
#घोषणा I40E_AQC_CEE_PFC_STATUS_MASK	(0x7 << I40E_AQC_CEE_PFC_STATUS_SHIFT)
#घोषणा I40E_AQC_CEE_APP_STATUS_SHIFT	0x8
#घोषणा I40E_AQC_CEE_APP_STATUS_MASK	(0x7 << I40E_AQC_CEE_APP_STATUS_SHIFT)
	u8	reserved[12];
पूर्ण;

I40E_CHECK_STRUCT_LEN(0x20, i40e_aqc_get_cee_dcb_cfg_resp);

/*	Set Local LLDP MIB (indirect 0x0A08)
 *	Used to replace the local MIB of a given LLDP agent. e.g. DCBx
 */
काष्ठा i40e_aqc_lldp_set_local_mib अणु
#घोषणा SET_LOCAL_MIB_AC_TYPE_DCBX_SHIFT	0
#घोषणा SET_LOCAL_MIB_AC_TYPE_DCBX_MASK	(1 << \
					SET_LOCAL_MIB_AC_TYPE_DCBX_SHIFT)
#घोषणा SET_LOCAL_MIB_AC_TYPE_LOCAL_MIB	0x0
#घोषणा SET_LOCAL_MIB_AC_TYPE_NON_WILLING_APPS_SHIFT	(1)
#घोषणा SET_LOCAL_MIB_AC_TYPE_NON_WILLING_APPS_MASK	(1 << \
				SET_LOCAL_MIB_AC_TYPE_NON_WILLING_APPS_SHIFT)
#घोषणा SET_LOCAL_MIB_AC_TYPE_NON_WILLING_APPS		0x1
	u8	type;
	u8	reserved0;
	__le16	length;
	u8	reserved1[4];
	__le32	address_high;
	__le32	address_low;
पूर्ण;

I40E_CHECK_CMD_LENGTH(i40e_aqc_lldp_set_local_mib);

/*	Stop/Start LLDP Agent (direct 0x0A09)
 *	Used क्रम stopping/starting specअगरic LLDP agent. e.g. DCBx
 */
काष्ठा i40e_aqc_lldp_stop_start_specअगरic_agent अणु
	u8	command;
	u8	reserved[15];
पूर्ण;

I40E_CHECK_CMD_LENGTH(i40e_aqc_lldp_stop_start_specअगरic_agent);

/* Restore LLDP Agent factory settings (direct 0x0A0A) */
काष्ठा i40e_aqc_lldp_restore अणु
	u8	command;
#घोषणा I40E_AQ_LLDP_AGENT_RESTORE		0x1
	u8	reserved[15];
पूर्ण;

I40E_CHECK_CMD_LENGTH(i40e_aqc_lldp_restore);

/* Add Udp Tunnel command and completion (direct 0x0B00) */
काष्ठा i40e_aqc_add_udp_tunnel अणु
	__le16	udp_port;
	u8	reserved0[3];
	u8	protocol_type;
#घोषणा I40E_AQC_TUNNEL_TYPE_VXLAN	0x00
#घोषणा I40E_AQC_TUNNEL_TYPE_NGE	0x01
	u8	reserved1[10];
पूर्ण;

I40E_CHECK_CMD_LENGTH(i40e_aqc_add_udp_tunnel);

काष्ठा i40e_aqc_add_udp_tunnel_completion अणु
	__le16	udp_port;
	u8	filter_entry_index;
	u8	multiple_pfs;
	u8	total_filters;
	u8	reserved[11];
पूर्ण;

I40E_CHECK_CMD_LENGTH(i40e_aqc_add_udp_tunnel_completion);

/* हटाओ UDP Tunnel command (0x0B01) */
काष्ठा i40e_aqc_हटाओ_udp_tunnel अणु
	u8	reserved[2];
	u8	index; /* 0 to 15 */
	u8	reserved2[13];
पूर्ण;

I40E_CHECK_CMD_LENGTH(i40e_aqc_हटाओ_udp_tunnel);

काष्ठा i40e_aqc_del_udp_tunnel_completion अणु
	__le16	udp_port;
	u8	index; /* 0 to 15 */
	u8	multiple_pfs;
	u8	total_filters_used;
	u8	reserved1[11];
पूर्ण;

I40E_CHECK_CMD_LENGTH(i40e_aqc_del_udp_tunnel_completion);

काष्ठा i40e_aqc_get_set_rss_key अणु
#घोषणा I40E_AQC_SET_RSS_KEY_VSI_VALID		BIT(15)
#घोषणा I40E_AQC_SET_RSS_KEY_VSI_ID_SHIFT	0
#घोषणा I40E_AQC_SET_RSS_KEY_VSI_ID_MASK	(0x3FF << \
					I40E_AQC_SET_RSS_KEY_VSI_ID_SHIFT)
	__le16	vsi_id;
	u8	reserved[6];
	__le32	addr_high;
	__le32	addr_low;
पूर्ण;

I40E_CHECK_CMD_LENGTH(i40e_aqc_get_set_rss_key);

काष्ठा i40e_aqc_get_set_rss_key_data अणु
	u8 standard_rss_key[0x28];
	u8 extended_hash_key[0xc];
पूर्ण;

I40E_CHECK_STRUCT_LEN(0x34, i40e_aqc_get_set_rss_key_data);

काष्ठा  i40e_aqc_get_set_rss_lut अणु
#घोषणा I40E_AQC_SET_RSS_LUT_VSI_VALID		BIT(15)
#घोषणा I40E_AQC_SET_RSS_LUT_VSI_ID_SHIFT	0
#घोषणा I40E_AQC_SET_RSS_LUT_VSI_ID_MASK	(0x3FF << \
					I40E_AQC_SET_RSS_LUT_VSI_ID_SHIFT)
	__le16	vsi_id;
#घोषणा I40E_AQC_SET_RSS_LUT_TABLE_TYPE_SHIFT	0
#घोषणा I40E_AQC_SET_RSS_LUT_TABLE_TYPE_MASK	BIT(I40E_AQC_SET_RSS_LUT_TABLE_TYPE_SHIFT)

#घोषणा I40E_AQC_SET_RSS_LUT_TABLE_TYPE_VSI	0
#घोषणा I40E_AQC_SET_RSS_LUT_TABLE_TYPE_PF	1
	__le16	flags;
	u8	reserved[4];
	__le32	addr_high;
	__le32	addr_low;
पूर्ण;

I40E_CHECK_CMD_LENGTH(i40e_aqc_get_set_rss_lut);

/* tunnel key काष्ठाure 0x0B10 */

काष्ठा i40e_aqc_tunnel_key_काष्ठाure अणु
	u8	key1_off;
	u8	key2_off;
	u8	key1_len;  /* 0 to 15 */
	u8	key2_len;  /* 0 to 15 */
	u8	flags;
	u8	network_key_index;
	u8	reserved[10];
पूर्ण;

I40E_CHECK_CMD_LENGTH(i40e_aqc_tunnel_key_काष्ठाure);

/* OEM mode commands (direct 0xFE0x) */
काष्ठा i40e_aqc_oem_param_change अणु
	__le32	param_type;
	__le32	param_value1;
	__le16	param_value2;
	u8	reserved[6];
पूर्ण;

I40E_CHECK_CMD_LENGTH(i40e_aqc_oem_param_change);

काष्ठा i40e_aqc_oem_state_change अणु
	__le32	state;
	u8	reserved[12];
पूर्ण;

I40E_CHECK_CMD_LENGTH(i40e_aqc_oem_state_change);

/* Initialize OCSD (0xFE02, direct) */
काष्ठा i40e_aqc_opc_oem_ocsd_initialize अणु
	u8 type_status;
	u8 reserved1[3];
	__le32 ocsd_memory_block_addr_high;
	__le32 ocsd_memory_block_addr_low;
	__le32 requested_update_पूर्णांकerval;
पूर्ण;

I40E_CHECK_CMD_LENGTH(i40e_aqc_opc_oem_ocsd_initialize);

/* Initialize OCBB  (0xFE03, direct) */
काष्ठा i40e_aqc_opc_oem_ocbb_initialize अणु
	u8 type_status;
	u8 reserved1[3];
	__le32 ocbb_memory_block_addr_high;
	__le32 ocbb_memory_block_addr_low;
	u8 reserved2[4];
पूर्ण;

I40E_CHECK_CMD_LENGTH(i40e_aqc_opc_oem_ocbb_initialize);

/* debug commands */

/* get device id (0xFF00) uses the generic काष्ठाure */

/* set test more (0xFF01, पूर्णांकernal) */

काष्ठा i40e_acq_set_test_mode अणु
	u8	mode;
	u8	reserved[3];
	u8	command;
	u8	reserved2[3];
	__le32	address_high;
	__le32	address_low;
पूर्ण;

I40E_CHECK_CMD_LENGTH(i40e_acq_set_test_mode);

/* Debug Read Register command (0xFF03)
 * Debug Write Register command (0xFF04)
 */
काष्ठा i40e_aqc_debug_reg_पढ़ो_ग_लिखो अणु
	__le32 reserved;
	__le32 address;
	__le32 value_high;
	__le32 value_low;
पूर्ण;

I40E_CHECK_CMD_LENGTH(i40e_aqc_debug_reg_पढ़ो_ग_लिखो);

/* Scatter/gather Reg Read  (indirect 0xFF05)
 * Scatter/gather Reg Write (indirect 0xFF06)
 */

/* i40e_aq_desc is used क्रम the command */
काष्ठा i40e_aqc_debug_reg_sg_element_data अणु
	__le32 address;
	__le32 value;
पूर्ण;

/* Debug Modअगरy रेजिस्टर (direct 0xFF07) */
काष्ठा i40e_aqc_debug_modअगरy_reg अणु
	__le32 address;
	__le32 value;
	__le32 clear_mask;
	__le32 set_mask;
पूर्ण;

I40E_CHECK_CMD_LENGTH(i40e_aqc_debug_modअगरy_reg);

/* dump पूर्णांकernal data (0xFF08, indirect) */
काष्ठा i40e_aqc_debug_dump_पूर्णांकernals अणु
	u8	cluster_id;
	u8	table_id;
	__le16	data_size;
	__le32	idx;
	__le32	address_high;
	__le32	address_low;
पूर्ण;

I40E_CHECK_CMD_LENGTH(i40e_aqc_debug_dump_पूर्णांकernals);

काष्ठा i40e_aqc_debug_modअगरy_पूर्णांकernals अणु
	u8	cluster_id;
	u8	cluster_specअगरic_params[7];
	__le32	address_high;
	__le32	address_low;
पूर्ण;

I40E_CHECK_CMD_LENGTH(i40e_aqc_debug_modअगरy_पूर्णांकernals);

#पूर्ण_अगर /* _I40E_ADMINQ_CMD_H_ */
