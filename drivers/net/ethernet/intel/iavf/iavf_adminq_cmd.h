<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright(c) 2013 - 2018 Intel Corporation. */

#अगर_अघोषित _IAVF_ADMINQ_CMD_H_
#घोषणा _IAVF_ADMINQ_CMD_H_

/* This header file defines the iavf Admin Queue commands and is shared between
 * iavf Firmware and Software.
 *
 * This file needs to comply with the Linux Kernel coding style.
 */

#घोषणा IAVF_FW_API_VERSION_MAJOR	0x0001
#घोषणा IAVF_FW_API_VERSION_MINOR_X722	0x0005
#घोषणा IAVF_FW_API_VERSION_MINOR_X710	0x0008

#घोषणा IAVF_FW_MINOR_VERSION(_h) ((_h)->mac.type == IAVF_MAC_XL710 ? \
					IAVF_FW_API_VERSION_MINOR_X710 : \
					IAVF_FW_API_VERSION_MINOR_X722)

/* API version 1.7 implements additional link and PHY-specअगरic APIs  */
#घोषणा IAVF_MINOR_VER_GET_LINK_INFO_XL710 0x0007

काष्ठा iavf_aq_desc अणु
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
#घोषणा IAVF_AQ_FLAG_DD_SHIFT	0
#घोषणा IAVF_AQ_FLAG_CMP_SHIFT	1
#घोषणा IAVF_AQ_FLAG_ERR_SHIFT	2
#घोषणा IAVF_AQ_FLAG_VFE_SHIFT	3
#घोषणा IAVF_AQ_FLAG_LB_SHIFT	9
#घोषणा IAVF_AQ_FLAG_RD_SHIFT	10
#घोषणा IAVF_AQ_FLAG_VFC_SHIFT	11
#घोषणा IAVF_AQ_FLAG_BUF_SHIFT	12
#घोषणा IAVF_AQ_FLAG_SI_SHIFT	13
#घोषणा IAVF_AQ_FLAG_EI_SHIFT	14
#घोषणा IAVF_AQ_FLAG_FE_SHIFT	15

#घोषणा IAVF_AQ_FLAG_DD		BIT(IAVF_AQ_FLAG_DD_SHIFT)  /* 0x1    */
#घोषणा IAVF_AQ_FLAG_CMP	BIT(IAVF_AQ_FLAG_CMP_SHIFT) /* 0x2    */
#घोषणा IAVF_AQ_FLAG_ERR	BIT(IAVF_AQ_FLAG_ERR_SHIFT) /* 0x4    */
#घोषणा IAVF_AQ_FLAG_VFE	BIT(IAVF_AQ_FLAG_VFE_SHIFT) /* 0x8    */
#घोषणा IAVF_AQ_FLAG_LB		BIT(IAVF_AQ_FLAG_LB_SHIFT)  /* 0x200  */
#घोषणा IAVF_AQ_FLAG_RD		BIT(IAVF_AQ_FLAG_RD_SHIFT)  /* 0x400  */
#घोषणा IAVF_AQ_FLAG_VFC	BIT(IAVF_AQ_FLAG_VFC_SHIFT) /* 0x800  */
#घोषणा IAVF_AQ_FLAG_BUF	BIT(IAVF_AQ_FLAG_BUF_SHIFT) /* 0x1000 */
#घोषणा IAVF_AQ_FLAG_SI		BIT(IAVF_AQ_FLAG_SI_SHIFT)  /* 0x2000 */
#घोषणा IAVF_AQ_FLAG_EI		BIT(IAVF_AQ_FLAG_EI_SHIFT)  /* 0x4000 */
#घोषणा IAVF_AQ_FLAG_FE		BIT(IAVF_AQ_FLAG_FE_SHIFT)  /* 0x8000 */

/* error codes */
क्रमागत iavf_admin_queue_err अणु
	IAVF_AQ_RC_OK		= 0,  /* success */
	IAVF_AQ_RC_EPERM	= 1,  /* Operation not permitted */
	IAVF_AQ_RC_ENOENT	= 2,  /* No such element */
	IAVF_AQ_RC_ESRCH	= 3,  /* Bad opcode */
	IAVF_AQ_RC_EINTR	= 4,  /* operation पूर्णांकerrupted */
	IAVF_AQ_RC_EIO		= 5,  /* I/O error */
	IAVF_AQ_RC_ENXIO	= 6,  /* No such resource */
	IAVF_AQ_RC_E2BIG	= 7,  /* Arg too दीर्घ */
	IAVF_AQ_RC_EAGAIN	= 8,  /* Try again */
	IAVF_AQ_RC_ENOMEM	= 9,  /* Out of memory */
	IAVF_AQ_RC_EACCES	= 10, /* Permission denied */
	IAVF_AQ_RC_EFAULT	= 11, /* Bad address */
	IAVF_AQ_RC_EBUSY	= 12, /* Device or resource busy */
	IAVF_AQ_RC_EEXIST	= 13, /* object alपढ़ोy exists */
	IAVF_AQ_RC_EINVAL	= 14, /* Invalid argument */
	IAVF_AQ_RC_ENOTTY	= 15, /* Not a typeग_लिखोr */
	IAVF_AQ_RC_ENOSPC	= 16, /* No space left or alloc failure */
	IAVF_AQ_RC_ENOSYS	= 17, /* Function not implemented */
	IAVF_AQ_RC_दुस्फल	= 18, /* Parameter out of range */
	IAVF_AQ_RC_EFLUSHED	= 19, /* Cmd flushed due to prev cmd error */
	IAVF_AQ_RC_BAD_ADDR	= 20, /* Descriptor contains a bad poपूर्णांकer */
	IAVF_AQ_RC_EMODE	= 21, /* Op not allowed in current dev mode */
	IAVF_AQ_RC_EFBIG	= 22, /* File too large */
पूर्ण;

/* Admin Queue command opcodes */
क्रमागत iavf_admin_queue_opc अणु
	/* aq commands */
	iavf_aqc_opc_get_version	= 0x0001,
	iavf_aqc_opc_driver_version	= 0x0002,
	iavf_aqc_opc_queue_shutकरोwn	= 0x0003,
	iavf_aqc_opc_set_pf_context	= 0x0004,

	/* resource ownership */
	iavf_aqc_opc_request_resource	= 0x0008,
	iavf_aqc_opc_release_resource	= 0x0009,

	iavf_aqc_opc_list_func_capabilities	= 0x000A,
	iavf_aqc_opc_list_dev_capabilities	= 0x000B,

	/* Proxy commands */
	iavf_aqc_opc_set_proxy_config		= 0x0104,
	iavf_aqc_opc_set_ns_proxy_table_entry	= 0x0105,

	/* LAA */
	iavf_aqc_opc_mac_address_पढ़ो	= 0x0107,
	iavf_aqc_opc_mac_address_ग_लिखो	= 0x0108,

	/* PXE */
	iavf_aqc_opc_clear_pxe_mode	= 0x0110,

	/* WoL commands */
	iavf_aqc_opc_set_wol_filter	= 0x0120,
	iavf_aqc_opc_get_wake_reason	= 0x0121,

	/* पूर्णांकernal चयन commands */
	iavf_aqc_opc_get_चयन_config		= 0x0200,
	iavf_aqc_opc_add_statistics		= 0x0201,
	iavf_aqc_opc_हटाओ_statistics		= 0x0202,
	iavf_aqc_opc_set_port_parameters	= 0x0203,
	iavf_aqc_opc_get_चयन_resource_alloc	= 0x0204,
	iavf_aqc_opc_set_चयन_config		= 0x0205,
	iavf_aqc_opc_rx_ctl_reg_पढ़ो		= 0x0206,
	iavf_aqc_opc_rx_ctl_reg_ग_लिखो		= 0x0207,

	iavf_aqc_opc_add_vsi			= 0x0210,
	iavf_aqc_opc_update_vsi_parameters	= 0x0211,
	iavf_aqc_opc_get_vsi_parameters		= 0x0212,

	iavf_aqc_opc_add_pv			= 0x0220,
	iavf_aqc_opc_update_pv_parameters	= 0x0221,
	iavf_aqc_opc_get_pv_parameters		= 0x0222,

	iavf_aqc_opc_add_veb			= 0x0230,
	iavf_aqc_opc_update_veb_parameters	= 0x0231,
	iavf_aqc_opc_get_veb_parameters		= 0x0232,

	iavf_aqc_opc_delete_element		= 0x0243,

	iavf_aqc_opc_add_macvlan		= 0x0250,
	iavf_aqc_opc_हटाओ_macvlan		= 0x0251,
	iavf_aqc_opc_add_vlan			= 0x0252,
	iavf_aqc_opc_हटाओ_vlan		= 0x0253,
	iavf_aqc_opc_set_vsi_promiscuous_modes	= 0x0254,
	iavf_aqc_opc_add_tag			= 0x0255,
	iavf_aqc_opc_हटाओ_tag			= 0x0256,
	iavf_aqc_opc_add_multicast_etag		= 0x0257,
	iavf_aqc_opc_हटाओ_multicast_etag	= 0x0258,
	iavf_aqc_opc_update_tag			= 0x0259,
	iavf_aqc_opc_add_control_packet_filter	= 0x025A,
	iavf_aqc_opc_हटाओ_control_packet_filter	= 0x025B,
	iavf_aqc_opc_add_cloud_filters		= 0x025C,
	iavf_aqc_opc_हटाओ_cloud_filters	= 0x025D,
	iavf_aqc_opc_clear_wol_चयन_filters	= 0x025E,

	iavf_aqc_opc_add_mirror_rule	= 0x0260,
	iavf_aqc_opc_delete_mirror_rule	= 0x0261,

	/* Dynamic Device Personalization */
	iavf_aqc_opc_ग_लिखो_personalization_profile	= 0x0270,
	iavf_aqc_opc_get_personalization_profile_list	= 0x0271,

	/* DCB commands */
	iavf_aqc_opc_dcb_ignore_pfc	= 0x0301,
	iavf_aqc_opc_dcb_updated	= 0x0302,
	iavf_aqc_opc_set_dcb_parameters = 0x0303,

	/* TX scheduler */
	iavf_aqc_opc_configure_vsi_bw_limit		= 0x0400,
	iavf_aqc_opc_configure_vsi_ets_sla_bw_limit	= 0x0406,
	iavf_aqc_opc_configure_vsi_tc_bw		= 0x0407,
	iavf_aqc_opc_query_vsi_bw_config		= 0x0408,
	iavf_aqc_opc_query_vsi_ets_sla_config		= 0x040A,
	iavf_aqc_opc_configure_चयनing_comp_bw_limit	= 0x0410,

	iavf_aqc_opc_enable_चयनing_comp_ets			= 0x0413,
	iavf_aqc_opc_modअगरy_चयनing_comp_ets			= 0x0414,
	iavf_aqc_opc_disable_चयनing_comp_ets			= 0x0415,
	iavf_aqc_opc_configure_चयनing_comp_ets_bw_limit	= 0x0416,
	iavf_aqc_opc_configure_चयनing_comp_bw_config		= 0x0417,
	iavf_aqc_opc_query_चयनing_comp_ets_config		= 0x0418,
	iavf_aqc_opc_query_port_ets_config			= 0x0419,
	iavf_aqc_opc_query_चयनing_comp_bw_config		= 0x041A,
	iavf_aqc_opc_suspend_port_tx				= 0x041B,
	iavf_aqc_opc_resume_port_tx				= 0x041C,
	iavf_aqc_opc_configure_partition_bw			= 0x041D,
	/* hmc */
	iavf_aqc_opc_query_hmc_resource_profile	= 0x0500,
	iavf_aqc_opc_set_hmc_resource_profile	= 0x0501,

	/* phy commands*/
	iavf_aqc_opc_get_phy_abilities		= 0x0600,
	iavf_aqc_opc_set_phy_config		= 0x0601,
	iavf_aqc_opc_set_mac_config		= 0x0603,
	iavf_aqc_opc_set_link_restart_an	= 0x0605,
	iavf_aqc_opc_get_link_status		= 0x0607,
	iavf_aqc_opc_set_phy_पूर्णांक_mask		= 0x0613,
	iavf_aqc_opc_get_local_advt_reg		= 0x0614,
	iavf_aqc_opc_set_local_advt_reg		= 0x0615,
	iavf_aqc_opc_get_partner_advt		= 0x0616,
	iavf_aqc_opc_set_lb_modes		= 0x0618,
	iavf_aqc_opc_get_phy_wol_caps		= 0x0621,
	iavf_aqc_opc_set_phy_debug		= 0x0622,
	iavf_aqc_opc_upload_ext_phy_fm		= 0x0625,
	iavf_aqc_opc_run_phy_activity		= 0x0626,
	iavf_aqc_opc_set_phy_रेजिस्टर		= 0x0628,
	iavf_aqc_opc_get_phy_रेजिस्टर		= 0x0629,

	/* NVM commands */
	iavf_aqc_opc_nvm_पढ़ो			= 0x0701,
	iavf_aqc_opc_nvm_erase			= 0x0702,
	iavf_aqc_opc_nvm_update			= 0x0703,
	iavf_aqc_opc_nvm_config_पढ़ो		= 0x0704,
	iavf_aqc_opc_nvm_config_ग_लिखो		= 0x0705,
	iavf_aqc_opc_oem_post_update		= 0x0720,
	iavf_aqc_opc_thermal_sensor		= 0x0721,

	/* भवization commands */
	iavf_aqc_opc_send_msg_to_pf		= 0x0801,
	iavf_aqc_opc_send_msg_to_vf		= 0x0802,
	iavf_aqc_opc_send_msg_to_peer		= 0x0803,

	/* alternate काष्ठाure */
	iavf_aqc_opc_alternate_ग_लिखो		= 0x0900,
	iavf_aqc_opc_alternate_ग_लिखो_indirect	= 0x0901,
	iavf_aqc_opc_alternate_पढ़ो		= 0x0902,
	iavf_aqc_opc_alternate_पढ़ो_indirect	= 0x0903,
	iavf_aqc_opc_alternate_ग_लिखो_करोne	= 0x0904,
	iavf_aqc_opc_alternate_set_mode		= 0x0905,
	iavf_aqc_opc_alternate_clear_port	= 0x0906,

	/* LLDP commands */
	iavf_aqc_opc_lldp_get_mib	= 0x0A00,
	iavf_aqc_opc_lldp_update_mib	= 0x0A01,
	iavf_aqc_opc_lldp_add_tlv	= 0x0A02,
	iavf_aqc_opc_lldp_update_tlv	= 0x0A03,
	iavf_aqc_opc_lldp_delete_tlv	= 0x0A04,
	iavf_aqc_opc_lldp_stop		= 0x0A05,
	iavf_aqc_opc_lldp_start		= 0x0A06,

	/* Tunnel commands */
	iavf_aqc_opc_add_udp_tunnel	= 0x0B00,
	iavf_aqc_opc_del_udp_tunnel	= 0x0B01,
	iavf_aqc_opc_set_rss_key	= 0x0B02,
	iavf_aqc_opc_set_rss_lut	= 0x0B03,
	iavf_aqc_opc_get_rss_key	= 0x0B04,
	iavf_aqc_opc_get_rss_lut	= 0x0B05,

	/* Async Events */
	iavf_aqc_opc_event_lan_overflow		= 0x1001,

	/* OEM commands */
	iavf_aqc_opc_oem_parameter_change	= 0xFE00,
	iavf_aqc_opc_oem_device_status_change	= 0xFE01,
	iavf_aqc_opc_oem_ocsd_initialize	= 0xFE02,
	iavf_aqc_opc_oem_ocbb_initialize	= 0xFE03,

	/* debug commands */
	iavf_aqc_opc_debug_पढ़ो_reg		= 0xFF03,
	iavf_aqc_opc_debug_ग_लिखो_reg		= 0xFF04,
	iavf_aqc_opc_debug_modअगरy_reg		= 0xFF07,
	iavf_aqc_opc_debug_dump_पूर्णांकernals	= 0xFF08,
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
#घोषणा IAVF_CHECK_STRUCT_LEN(n, X) क्रमागत iavf_अटल_निश्चित_क्रमागत_##X \
	अणु iavf_अटल_निश्चित_##X = (n) / ((माप(काष्ठा X) == (n)) ? 1 : 0) पूर्ण

/* This macro is used extensively to ensure that command काष्ठाures are 16
 * bytes in length as they have to map to the raw array of that size.
 */
#घोषणा IAVF_CHECK_CMD_LENGTH(X)	IAVF_CHECK_STRUCT_LEN(16, X)

/* Queue Shutकरोwn (direct 0x0003) */
काष्ठा iavf_aqc_queue_shutकरोwn अणु
	__le32	driver_unloading;
#घोषणा IAVF_AQ_DRIVER_UNLOADING	0x1
	u8	reserved[12];
पूर्ण;

IAVF_CHECK_CMD_LENGTH(iavf_aqc_queue_shutकरोwn);

काष्ठा iavf_aqc_vsi_properties_data अणु
	/* first 96 byte are written by SW */
	__le16	valid_sections;
#घोषणा IAVF_AQ_VSI_PROP_SWITCH_VALID		0x0001
#घोषणा IAVF_AQ_VSI_PROP_SECURITY_VALID		0x0002
#घोषणा IAVF_AQ_VSI_PROP_VLAN_VALID		0x0004
#घोषणा IAVF_AQ_VSI_PROP_CAS_PV_VALID		0x0008
#घोषणा IAVF_AQ_VSI_PROP_INGRESS_UP_VALID	0x0010
#घोषणा IAVF_AQ_VSI_PROP_EGRESS_UP_VALID	0x0020
#घोषणा IAVF_AQ_VSI_PROP_QUEUE_MAP_VALID	0x0040
#घोषणा IAVF_AQ_VSI_PROP_QUEUE_OPT_VALID	0x0080
#घोषणा IAVF_AQ_VSI_PROP_OUTER_UP_VALID		0x0100
#घोषणा IAVF_AQ_VSI_PROP_SCHED_VALID		0x0200
	/* चयन section */
	__le16	चयन_id; /* 12bit id combined with flags below */
#घोषणा IAVF_AQ_VSI_SW_ID_SHIFT		0x0000
#घोषणा IAVF_AQ_VSI_SW_ID_MASK		(0xFFF << IAVF_AQ_VSI_SW_ID_SHIFT)
#घोषणा IAVF_AQ_VSI_SW_ID_FLAG_NOT_STAG	0x1000
#घोषणा IAVF_AQ_VSI_SW_ID_FLAG_ALLOW_LB	0x2000
#घोषणा IAVF_AQ_VSI_SW_ID_FLAG_LOCAL_LB	0x4000
	u8	sw_reserved[2];
	/* security section */
	u8	sec_flags;
#घोषणा IAVF_AQ_VSI_SEC_FLAG_ALLOW_DEST_OVRD	0x01
#घोषणा IAVF_AQ_VSI_SEC_FLAG_ENABLE_VLAN_CHK	0x02
#घोषणा IAVF_AQ_VSI_SEC_FLAG_ENABLE_MAC_CHK	0x04
	u8	sec_reserved;
	/* VLAN section */
	__le16	pvid; /* VLANS include priority bits */
	__le16	fcoe_pvid;
	u8	port_vlan_flags;
#घोषणा IAVF_AQ_VSI_PVLAN_MODE_SHIFT	0x00
#घोषणा IAVF_AQ_VSI_PVLAN_MODE_MASK	(0x03 << \
					 IAVF_AQ_VSI_PVLAN_MODE_SHIFT)
#घोषणा IAVF_AQ_VSI_PVLAN_MODE_TAGGED	0x01
#घोषणा IAVF_AQ_VSI_PVLAN_MODE_UNTAGGED	0x02
#घोषणा IAVF_AQ_VSI_PVLAN_MODE_ALL	0x03
#घोषणा IAVF_AQ_VSI_PVLAN_INSERT_PVID	0x04
#घोषणा IAVF_AQ_VSI_PVLAN_EMOD_SHIFT	0x03
#घोषणा IAVF_AQ_VSI_PVLAN_EMOD_MASK	(0x3 << \
					 IAVF_AQ_VSI_PVLAN_EMOD_SHIFT)
#घोषणा IAVF_AQ_VSI_PVLAN_EMOD_STR_BOTH	0x0
#घोषणा IAVF_AQ_VSI_PVLAN_EMOD_STR_UP	0x08
#घोषणा IAVF_AQ_VSI_PVLAN_EMOD_STR	0x10
#घोषणा IAVF_AQ_VSI_PVLAN_EMOD_NOTHING	0x18
	u8	pvlan_reserved[3];
	/* ingress egress up sections */
	__le32	ingress_table; /* biपंचांगap, 3 bits per up */
#घोषणा IAVF_AQ_VSI_UP_TABLE_UP0_SHIFT	0
#घोषणा IAVF_AQ_VSI_UP_TABLE_UP0_MASK	(0x7 << \
					 IAVF_AQ_VSI_UP_TABLE_UP0_SHIFT)
#घोषणा IAVF_AQ_VSI_UP_TABLE_UP1_SHIFT	3
#घोषणा IAVF_AQ_VSI_UP_TABLE_UP1_MASK	(0x7 << \
					 IAVF_AQ_VSI_UP_TABLE_UP1_SHIFT)
#घोषणा IAVF_AQ_VSI_UP_TABLE_UP2_SHIFT	6
#घोषणा IAVF_AQ_VSI_UP_TABLE_UP2_MASK	(0x7 << \
					 IAVF_AQ_VSI_UP_TABLE_UP2_SHIFT)
#घोषणा IAVF_AQ_VSI_UP_TABLE_UP3_SHIFT	9
#घोषणा IAVF_AQ_VSI_UP_TABLE_UP3_MASK	(0x7 << \
					 IAVF_AQ_VSI_UP_TABLE_UP3_SHIFT)
#घोषणा IAVF_AQ_VSI_UP_TABLE_UP4_SHIFT	12
#घोषणा IAVF_AQ_VSI_UP_TABLE_UP4_MASK	(0x7 << \
					 IAVF_AQ_VSI_UP_TABLE_UP4_SHIFT)
#घोषणा IAVF_AQ_VSI_UP_TABLE_UP5_SHIFT	15
#घोषणा IAVF_AQ_VSI_UP_TABLE_UP5_MASK	(0x7 << \
					 IAVF_AQ_VSI_UP_TABLE_UP5_SHIFT)
#घोषणा IAVF_AQ_VSI_UP_TABLE_UP6_SHIFT	18
#घोषणा IAVF_AQ_VSI_UP_TABLE_UP6_MASK	(0x7 << \
					 IAVF_AQ_VSI_UP_TABLE_UP6_SHIFT)
#घोषणा IAVF_AQ_VSI_UP_TABLE_UP7_SHIFT	21
#घोषणा IAVF_AQ_VSI_UP_TABLE_UP7_MASK	(0x7 << \
					 IAVF_AQ_VSI_UP_TABLE_UP7_SHIFT)
	__le32	egress_table;   /* same defines as क्रम ingress table */
	/* cascaded PV section */
	__le16	cas_pv_tag;
	u8	cas_pv_flags;
#घोषणा IAVF_AQ_VSI_CAS_PV_TAGX_SHIFT		0x00
#घोषणा IAVF_AQ_VSI_CAS_PV_TAGX_MASK		(0x03 << \
						 IAVF_AQ_VSI_CAS_PV_TAGX_SHIFT)
#घोषणा IAVF_AQ_VSI_CAS_PV_TAGX_LEAVE		0x00
#घोषणा IAVF_AQ_VSI_CAS_PV_TAGX_REMOVE		0x01
#घोषणा IAVF_AQ_VSI_CAS_PV_TAGX_COPY		0x02
#घोषणा IAVF_AQ_VSI_CAS_PV_INSERT_TAG		0x10
#घोषणा IAVF_AQ_VSI_CAS_PV_ETAG_PRUNE		0x20
#घोषणा IAVF_AQ_VSI_CAS_PV_ACCEPT_HOST_TAG	0x40
	u8	cas_pv_reserved;
	/* queue mapping section */
	__le16	mapping_flags;
#घोषणा IAVF_AQ_VSI_QUE_MAP_CONTIG	0x0
#घोषणा IAVF_AQ_VSI_QUE_MAP_NONCONTIG	0x1
	__le16	queue_mapping[16];
#घोषणा IAVF_AQ_VSI_QUEUE_SHIFT		0x0
#घोषणा IAVF_AQ_VSI_QUEUE_MASK		(0x7FF << IAVF_AQ_VSI_QUEUE_SHIFT)
	__le16	tc_mapping[8];
#घोषणा IAVF_AQ_VSI_TC_QUE_OFFSET_SHIFT	0
#घोषणा IAVF_AQ_VSI_TC_QUE_OFFSET_MASK	(0x1FF << \
					 IAVF_AQ_VSI_TC_QUE_OFFSET_SHIFT)
#घोषणा IAVF_AQ_VSI_TC_QUE_NUMBER_SHIFT	9
#घोषणा IAVF_AQ_VSI_TC_QUE_NUMBER_MASK	(0x7 << \
					 IAVF_AQ_VSI_TC_QUE_NUMBER_SHIFT)
	/* queueing option section */
	u8	queueing_opt_flags;
#घोषणा IAVF_AQ_VSI_QUE_OPT_MULTICAST_UDP_ENA	0x04
#घोषणा IAVF_AQ_VSI_QUE_OPT_UNICAST_UDP_ENA	0x08
#घोषणा IAVF_AQ_VSI_QUE_OPT_TCP_ENA	0x10
#घोषणा IAVF_AQ_VSI_QUE_OPT_FCOE_ENA	0x20
#घोषणा IAVF_AQ_VSI_QUE_OPT_RSS_LUT_PF	0x00
#घोषणा IAVF_AQ_VSI_QUE_OPT_RSS_LUT_VSI	0x40
	u8	queueing_opt_reserved[3];
	/* scheduler section */
	u8	up_enable_bits;
	u8	sched_reserved;
	/* outer up section */
	__le32	outer_up_table; /* same काष्ठाure and defines as ingress tbl */
	u8	cmd_reserved[8];
	/* last 32 bytes are written by FW */
	__le16	qs_handle[8];
#घोषणा IAVF_AQ_VSI_QS_HANDLE_INVALID	0xFFFF
	__le16	stat_counter_idx;
	__le16	sched_id;
	u8	resp_reserved[12];
पूर्ण;

IAVF_CHECK_STRUCT_LEN(128, iavf_aqc_vsi_properties_data);

/* Get VEB Parameters (direct 0x0232)
 * uses iavf_aqc_चयन_seid क्रम the descriptor
 */
काष्ठा iavf_aqc_get_veb_parameters_completion अणु
	__le16	seid;
	__le16	चयन_id;
	__le16	veb_flags; /* only the first/last flags from 0x0230 is valid */
	__le16	statistic_index;
	__le16	vebs_used;
	__le16	vebs_मुक्त;
	u8	reserved[4];
पूर्ण;

IAVF_CHECK_CMD_LENGTH(iavf_aqc_get_veb_parameters_completion);

#घोषणा IAVF_LINK_SPEED_100MB_SHIFT	0x1
#घोषणा IAVF_LINK_SPEED_1000MB_SHIFT	0x2
#घोषणा IAVF_LINK_SPEED_10GB_SHIFT	0x3
#घोषणा IAVF_LINK_SPEED_40GB_SHIFT	0x4
#घोषणा IAVF_LINK_SPEED_20GB_SHIFT	0x5
#घोषणा IAVF_LINK_SPEED_25GB_SHIFT	0x6

क्रमागत iavf_aq_link_speed अणु
	IAVF_LINK_SPEED_UNKNOWN	= 0,
	IAVF_LINK_SPEED_100MB	= BIT(IAVF_LINK_SPEED_100MB_SHIFT),
	IAVF_LINK_SPEED_1GB	= BIT(IAVF_LINK_SPEED_1000MB_SHIFT),
	IAVF_LINK_SPEED_10GB	= BIT(IAVF_LINK_SPEED_10GB_SHIFT),
	IAVF_LINK_SPEED_40GB	= BIT(IAVF_LINK_SPEED_40GB_SHIFT),
	IAVF_LINK_SPEED_20GB	= BIT(IAVF_LINK_SPEED_20GB_SHIFT),
	IAVF_LINK_SPEED_25GB	= BIT(IAVF_LINK_SPEED_25GB_SHIFT),
पूर्ण;

/* Send to PF command (indirect 0x0801) id is only used by PF
 * Send to VF command (indirect 0x0802) id is only used by PF
 * Send to Peer PF command (indirect 0x0803)
 */
काष्ठा iavf_aqc_pf_vf_message अणु
	__le32	id;
	u8	reserved[4];
	__le32	addr_high;
	__le32	addr_low;
पूर्ण;

IAVF_CHECK_CMD_LENGTH(iavf_aqc_pf_vf_message);

काष्ठा iavf_aqc_get_set_rss_key अणु
#घोषणा IAVF_AQC_SET_RSS_KEY_VSI_VALID		BIT(15)
#घोषणा IAVF_AQC_SET_RSS_KEY_VSI_ID_SHIFT	0
#घोषणा IAVF_AQC_SET_RSS_KEY_VSI_ID_MASK	(0x3FF << \
					IAVF_AQC_SET_RSS_KEY_VSI_ID_SHIFT)
	__le16	vsi_id;
	u8	reserved[6];
	__le32	addr_high;
	__le32	addr_low;
पूर्ण;

IAVF_CHECK_CMD_LENGTH(iavf_aqc_get_set_rss_key);

काष्ठा iavf_aqc_get_set_rss_key_data अणु
	u8 standard_rss_key[0x28];
	u8 extended_hash_key[0xc];
पूर्ण;

IAVF_CHECK_STRUCT_LEN(0x34, iavf_aqc_get_set_rss_key_data);

काष्ठा  iavf_aqc_get_set_rss_lut अणु
#घोषणा IAVF_AQC_SET_RSS_LUT_VSI_VALID		BIT(15)
#घोषणा IAVF_AQC_SET_RSS_LUT_VSI_ID_SHIFT	0
#घोषणा IAVF_AQC_SET_RSS_LUT_VSI_ID_MASK	(0x3FF << \
					IAVF_AQC_SET_RSS_LUT_VSI_ID_SHIFT)
	__le16	vsi_id;
#घोषणा IAVF_AQC_SET_RSS_LUT_TABLE_TYPE_SHIFT	0
#घोषणा IAVF_AQC_SET_RSS_LUT_TABLE_TYPE_MASK \
				BIT(IAVF_AQC_SET_RSS_LUT_TABLE_TYPE_SHIFT)

#घोषणा IAVF_AQC_SET_RSS_LUT_TABLE_TYPE_VSI	0
#घोषणा IAVF_AQC_SET_RSS_LUT_TABLE_TYPE_PF	1
	__le16	flags;
	u8	reserved[4];
	__le32	addr_high;
	__le32	addr_low;
पूर्ण;

IAVF_CHECK_CMD_LENGTH(iavf_aqc_get_set_rss_lut);
#पूर्ण_अगर /* _IAVF_ADMINQ_CMD_H_ */
