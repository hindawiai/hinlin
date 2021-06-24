<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2005-2014 Brocade Communications Systems, Inc.
 * Copyright (c) 2014- QLogic Corporation.
 * All rights reserved
 * www.qlogic.com
 *
 * Linux driver क्रम QLogic BR-series Fibre Channel Host Bus Adapter.
 */
#अगर_अघोषित BFAD_BSG_H
#घोषणा BFAD_BSG_H

#समावेश "bfa_defs.h"
#समावेश "bfa_defs_fcs.h"

/* Definitions of venकरोr unique काष्ठाures and command codes passed in
 * using FC_BSG_HST_VENDOR message code.
 */
क्रमागत अणु
	IOCMD_IOC_ENABLE = 0x1,
	IOCMD_IOC_DISABLE,
	IOCMD_IOC_GET_ATTR,
	IOCMD_IOC_GET_INFO,
	IOCMD_IOC_GET_STATS,
	IOCMD_IOC_GET_FWSTATS,
	IOCMD_IOC_RESET_STATS,
	IOCMD_IOC_RESET_FWSTATS,
	IOCMD_IOC_SET_ADAPTER_NAME,
	IOCMD_IOC_SET_PORT_NAME,
	IOCMD_IOC_FW_SIG_INV,
	IOCMD_IOCFC_GET_ATTR,
	IOCMD_IOCFC_SET_INTR,
	IOCMD_PORT_ENABLE,
	IOCMD_PORT_DISABLE,
	IOCMD_PORT_GET_ATTR,
	IOCMD_PORT_GET_STATS,
	IOCMD_PORT_RESET_STATS,
	IOCMD_PORT_CFG_TOPO,
	IOCMD_PORT_CFG_SPEED,
	IOCMD_PORT_CFG_ALPA,
	IOCMD_PORT_CFG_MAXFRSZ,
	IOCMD_PORT_CLR_ALPA,
	IOCMD_PORT_BBCR_ENABLE,
	IOCMD_PORT_BBCR_DISABLE,
	IOCMD_PORT_BBCR_GET_ATTR,
	IOCMD_LPORT_GET_ATTR,
	IOCMD_LPORT_GET_RPORTS,
	IOCMD_LPORT_GET_STATS,
	IOCMD_LPORT_RESET_STATS,
	IOCMD_LPORT_GET_IOSTATS,
	IOCMD_RPORT_GET_ATTR,
	IOCMD_RPORT_GET_ADDR,
	IOCMD_RPORT_GET_STATS,
	IOCMD_RPORT_RESET_STATS,
	IOCMD_RPORT_SET_SPEED,
	IOCMD_VPORT_GET_ATTR,
	IOCMD_VPORT_GET_STATS,
	IOCMD_VPORT_RESET_STATS,
	IOCMD_FABRIC_GET_LPORTS,
	IOCMD_RATELIM_ENABLE,
	IOCMD_RATELIM_DISABLE,
	IOCMD_RATELIM_DEF_SPEED,
	IOCMD_FCPIM_FAILOVER,
	IOCMD_FCPIM_MODSTATS,
	IOCMD_FCPIM_MODSTATSCLR,
	IOCMD_FCPIM_DEL_ITN_STATS,
	IOCMD_ITNIM_GET_ATTR,
	IOCMD_ITNIM_GET_IOSTATS,
	IOCMD_ITNIM_RESET_STATS,
	IOCMD_ITNIM_GET_ITNSTATS,
	IOCMD_IOC_PCIFN_CFG,
	IOCMD_FCPORT_ENABLE,
	IOCMD_FCPORT_DISABLE,
	IOCMD_PCIFN_CREATE,
	IOCMD_PCIFN_DELETE,
	IOCMD_PCIFN_BW,
	IOCMD_ADAPTER_CFG_MODE,
	IOCMD_PORT_CFG_MODE,
	IOCMD_FLASH_ENABLE_OPTROM,
	IOCMD_FLASH_DISABLE_OPTROM,
	IOCMD_FAA_QUERY,
	IOCMD_CEE_GET_ATTR,
	IOCMD_CEE_GET_STATS,
	IOCMD_CEE_RESET_STATS,
	IOCMD_SFP_MEDIA,
	IOCMD_SFP_SPEED,
	IOCMD_FLASH_GET_ATTR,
	IOCMD_FLASH_ERASE_PART,
	IOCMD_FLASH_UPDATE_PART,
	IOCMD_FLASH_READ_PART,
	IOCMD_DIAG_TEMP,
	IOCMD_DIAG_MEMTEST,
	IOCMD_DIAG_LOOPBACK,
	IOCMD_DIAG_FWPING,
	IOCMD_DIAG_QUEUETEST,
	IOCMD_DIAG_SFP,
	IOCMD_DIAG_LED,
	IOCMD_DIAG_BEACON_LPORT,
	IOCMD_DIAG_LB_STAT,
	IOCMD_PHY_GET_ATTR,
	IOCMD_PHY_GET_STATS,
	IOCMD_PHY_UPDATE_FW,
	IOCMD_PHY_READ_FW,
	IOCMD_VHBA_QUERY,
	IOCMD_DEBUG_PORTLOG,
	IOCMD_DEBUG_FW_CORE,
	IOCMD_DEBUG_FW_STATE_CLR,
	IOCMD_DEBUG_PORTLOG_CLR,
	IOCMD_DEBUG_START_DTRC,
	IOCMD_DEBUG_STOP_DTRC,
	IOCMD_DEBUG_PORTLOG_CTL,
	IOCMD_FCPIM_PROखाता_ON,
	IOCMD_FCPIM_PROखाता_OFF,
	IOCMD_ITNIM_GET_IOPROखाता,
	IOCMD_FCPORT_GET_STATS,
	IOCMD_FCPORT_RESET_STATS,
	IOCMD_BOOT_CFG,
	IOCMD_BOOT_QUERY,
	IOCMD_PREBOOT_QUERY,
	IOCMD_ETHBOOT_CFG,
	IOCMD_ETHBOOT_QUERY,
	IOCMD_TRUNK_ENABLE,
	IOCMD_TRUNK_DISABLE,
	IOCMD_TRUNK_GET_ATTR,
	IOCMD_QOS_ENABLE,
	IOCMD_QOS_DISABLE,
	IOCMD_QOS_GET_ATTR,
	IOCMD_QOS_GET_VC_ATTR,
	IOCMD_QOS_GET_STATS,
	IOCMD_QOS_RESET_STATS,
	IOCMD_VF_GET_STATS,
	IOCMD_VF_RESET_STATS,
	IOCMD_FCPIM_LUNMASK_ENABLE,
	IOCMD_FCPIM_LUNMASK_DISABLE,
	IOCMD_FCPIM_LUNMASK_CLEAR,
	IOCMD_FCPIM_LUNMASK_QUERY,
	IOCMD_FCPIM_LUNMASK_ADD,
	IOCMD_FCPIM_LUNMASK_DELETE,
	IOCMD_DIAG_DPORT_ENABLE,
	IOCMD_DIAG_DPORT_DISABLE,
	IOCMD_QOS_SET_BW,
	IOCMD_FCPIM_THROTTLE_QUERY,
	IOCMD_FCPIM_THROTTLE_SET,
	IOCMD_TFRU_READ,
	IOCMD_TFRU_WRITE,
	IOCMD_FRUVPD_READ,
	IOCMD_FRUVPD_UPDATE,
	IOCMD_FRUVPD_GET_MAX_SIZE,
	IOCMD_DIAG_DPORT_SHOW,
	IOCMD_DIAG_DPORT_START,
पूर्ण;

काष्ठा bfa_bsg_gen_s अणु
	bfa_status_t	status;
	u16		bfad_num;
	u16		rsvd;
पूर्ण;

काष्ठा bfa_bsg_portlogctl_s अणु
	bfa_status_t	status;
	u16		bfad_num;
	u16		rsvd;
	bfa_boolean_t	ctl;
	पूर्णांक		inst_no;
पूर्ण;

काष्ठा bfa_bsg_fcpim_profile_s अणु
	bfa_status_t    status;
	u16		bfad_num;
	u16		rsvd;
पूर्ण;

काष्ठा bfa_bsg_itnim_ioprofile_s अणु
	bfa_status_t	status;
	u16		bfad_num;
	u16		vf_id;
	wwn_t		lpwwn;
	wwn_t		rpwwn;
	काष्ठा bfa_itnim_ioprofile_s ioprofile;
पूर्ण;

काष्ठा bfa_bsg_fcport_stats_s अणु
	bfa_status_t	status;
	u16		bfad_num;
	u16		rsvd;
	जोड़ bfa_fcport_stats_u stats;
पूर्ण;

काष्ठा bfa_bsg_ioc_name_s अणु
	bfa_status_t	status;
	u16		bfad_num;
	u16		rsvd;
	अक्षर		name[BFA_ADAPTER_SYM_NAME_LEN];
पूर्ण;

काष्ठा bfa_bsg_ioc_info_s अणु
	bfa_status_t	status;
	u16		bfad_num;
	u16		rsvd;
	अक्षर		serialnum[64];
	अक्षर		hwpath[BFA_STRING_32];
	अक्षर		adapter_hwpath[BFA_STRING_32];
	अक्षर		guid[BFA_ADAPTER_SYM_NAME_LEN*2];
	अक्षर		name[BFA_ADAPTER_SYM_NAME_LEN];
	अक्षर		port_name[BFA_ADAPTER_SYM_NAME_LEN];
	अक्षर		eth_name[BFA_ADAPTER_SYM_NAME_LEN];
	wwn_t		pwwn;
	wwn_t		nwwn;
	wwn_t		factorypwwn;
	wwn_t		factorynwwn;
	mac_t		mac;
	mac_t		factory_mac; /* Factory mac address */
	mac_t		current_mac; /* Currently asचिन्हित mac address */
	क्रमागत bfa_ioc_type_e	ioc_type;
	u16		pvid; /* Port vlan id */
	u16		rsvd1;
	u32		host;
	u32		bandwidth; /* For PF support */
	u32		rsvd2;
पूर्ण;

काष्ठा bfa_bsg_ioc_attr_s अणु
	bfa_status_t	status;
	u16		bfad_num;
	u16		rsvd;
	काष्ठा bfa_ioc_attr_s  ioc_attr;
पूर्ण;

काष्ठा bfa_bsg_ioc_stats_s अणु
	bfa_status_t	status;
	u16		bfad_num;
	u16		rsvd;
	काष्ठा bfa_ioc_stats_s ioc_stats;
पूर्ण;

काष्ठा bfa_bsg_ioc_fwstats_s अणु
	bfa_status_t	status;
	u16		bfad_num;
	u16		rsvd;
	u32		buf_size;
	u32		rsvd1;
	u64		buf_ptr;
पूर्ण;

काष्ठा bfa_bsg_iocfc_attr_s अणु
	bfa_status_t	status;
	u16		bfad_num;
	u16		rsvd;
	काष्ठा bfa_iocfc_attr_s	iocfc_attr;
पूर्ण;

काष्ठा bfa_bsg_iocfc_पूर्णांकr_s अणु
	bfa_status_t	status;
	u16		bfad_num;
	u16		rsvd;
	काष्ठा bfa_iocfc_पूर्णांकr_attr_s attr;
पूर्ण;

काष्ठा bfa_bsg_port_attr_s अणु
	bfa_status_t	status;
	u16		bfad_num;
	u16		rsvd;
	काष्ठा bfa_port_attr_s	attr;
पूर्ण;

काष्ठा bfa_bsg_port_cfg_s अणु
	bfa_status_t	status;
	u16		bfad_num;
	u16		rsvd;
	u32		param;
	u32		rsvd1;
पूर्ण;

काष्ठा bfa_bsg_port_cfg_maxfrsize_s अणु
	bfa_status_t	status;
	u16		bfad_num;
	u16		maxfrsize;
पूर्ण;

काष्ठा bfa_bsg_port_stats_s अणु
	bfa_status_t	status;
	u16		bfad_num;
	u16		rsvd;
	u32		buf_size;
	u32		rsvd1;
	u64		buf_ptr;
पूर्ण;

काष्ठा bfa_bsg_lport_attr_s अणु
	bfa_status_t	status;
	u16		bfad_num;
	u16		vf_id;
	wwn_t		pwwn;
	काष्ठा bfa_lport_attr_s port_attr;
पूर्ण;

काष्ठा bfa_bsg_lport_stats_s अणु
	bfa_status_t	status;
	u16		bfad_num;
	u16		vf_id;
	wwn_t		pwwn;
	काष्ठा bfa_lport_stats_s port_stats;
पूर्ण;

काष्ठा bfa_bsg_lport_iostats_s अणु
	bfa_status_t	status;
	u16		bfad_num;
	u16		vf_id;
	wwn_t		pwwn;
	काष्ठा bfa_itnim_iostats_s iostats;
पूर्ण;

काष्ठा bfa_bsg_lport_get_rports_s अणु
	bfa_status_t	status;
	u16		bfad_num;
	u16		vf_id;
	wwn_t		pwwn;
	u64		rbuf_ptr;
	u32		nrports;
	u32		rsvd;
पूर्ण;

काष्ठा bfa_bsg_rport_attr_s अणु
	bfa_status_t	status;
	u16		bfad_num;
	u16		vf_id;
	wwn_t		pwwn;
	wwn_t		rpwwn;
	u32		pid;
	u32		rsvd;
	काष्ठा bfa_rport_attr_s attr;
पूर्ण;

काष्ठा bfa_bsg_rport_stats_s अणु
	bfa_status_t	status;
	u16		bfad_num;
	u16		vf_id;
	wwn_t		pwwn;
	wwn_t		rpwwn;
	काष्ठा bfa_rport_stats_s stats;
पूर्ण;

काष्ठा bfa_bsg_rport_scsi_addr_s अणु
	bfa_status_t	status;
	u16		bfad_num;
	u16		vf_id;
	wwn_t		pwwn;
	wwn_t		rpwwn;
	u32		host;
	u32		bus;
	u32		target;
	u32		lun;
पूर्ण;

काष्ठा bfa_bsg_rport_reset_stats_s अणु
	bfa_status_t	status;
	u16		bfad_num;
	u16		vf_id;
	wwn_t		pwwn;
	wwn_t		rpwwn;
पूर्ण;

काष्ठा bfa_bsg_rport_set_speed_s अणु
	bfa_status_t		status;
	u16			bfad_num;
	u16			vf_id;
	क्रमागत bfa_port_speed	speed;
	u32			rsvd;
	wwn_t			pwwn;
	wwn_t			rpwwn;
पूर्ण;

काष्ठा bfa_bsg_vport_attr_s अणु
	bfa_status_t	status;
	u16		bfad_num;
	u16		vf_id;
	wwn_t		vpwwn;
	काष्ठा bfa_vport_attr_s vport_attr;
पूर्ण;

काष्ठा bfa_bsg_vport_stats_s अणु
	bfa_status_t	status;
	u16		bfad_num;
	u16		vf_id;
	wwn_t		vpwwn;
	काष्ठा bfa_vport_stats_s vport_stats;
पूर्ण;

काष्ठा bfa_bsg_reset_stats_s अणु
	bfa_status_t	status;
	u16		bfad_num;
	u16		vf_id;
	wwn_t		vpwwn;
पूर्ण;

काष्ठा bfa_bsg_fabric_get_lports_s अणु
	bfa_status_t	status;
	u16		bfad_num;
	u16		vf_id;
	u64		buf_ptr;
	u32		nports;
	u32		rsvd;
पूर्ण;

काष्ठा bfa_bsg_trl_speed_s अणु
	bfa_status_t	status;
	u16		bfad_num;
	u16		rsvd;
	क्रमागत bfa_port_speed speed;
पूर्ण;

काष्ठा bfa_bsg_fcpim_s अणु
	bfa_status_t	status;
	u16		bfad_num;
	u16		param;
पूर्ण;

काष्ठा bfa_bsg_fcpim_modstats_s अणु
	bfa_status_t	status;
	u16		bfad_num;
	काष्ठा bfa_itnim_iostats_s modstats;
पूर्ण;

काष्ठा bfa_bsg_fcpim_del_itn_stats_s अणु
	bfa_status_t	status;
	u16		bfad_num;
	काष्ठा bfa_fcpim_del_itn_stats_s modstats;
पूर्ण;

काष्ठा bfa_bsg_fcpim_modstatsclr_s अणु
	bfa_status_t	status;
	u16		bfad_num;
पूर्ण;

काष्ठा bfa_bsg_itnim_attr_s अणु
	bfa_status_t	status;
	u16		bfad_num;
	u16		vf_id;
	wwn_t		lpwwn;
	wwn_t		rpwwn;
	काष्ठा bfa_itnim_attr_s	attr;
पूर्ण;

काष्ठा bfa_bsg_itnim_iostats_s अणु
	bfa_status_t	status;
	u16		bfad_num;
	u16		vf_id;
	wwn_t		lpwwn;
	wwn_t		rpwwn;
	काष्ठा bfa_itnim_iostats_s iostats;
पूर्ण;

काष्ठा bfa_bsg_itnim_itnstats_s अणु
	bfa_status_t	status;
	u16		bfad_num;
	u16		vf_id;
	wwn_t		lpwwn;
	wwn_t		rpwwn;
	काष्ठा bfa_itnim_stats_s itnstats;
पूर्ण;

काष्ठा bfa_bsg_pcअगरn_cfg_s अणु
	bfa_status_t		status;
	u16			bfad_num;
	u16			rsvd;
	काष्ठा bfa_ablk_cfg_s	pcअगरn_cfg;
पूर्ण;

काष्ठा bfa_bsg_pcअगरn_s अणु
	bfa_status_t		status;
	u16			bfad_num;
	u16			pcअगरn_id;
	u16			bw_min;
	u16			bw_max;
	u8			port;
	क्रमागत bfi_pcअगरn_class	pcअगरn_class;
	u8			rsvd[1];
पूर्ण;

काष्ठा bfa_bsg_adapter_cfg_mode_s अणु
	bfa_status_t	status;
	u16		bfad_num;
	u16		rsvd;
	काष्ठा bfa_adapter_cfg_mode_s	cfg;
पूर्ण;

काष्ठा bfa_bsg_port_cfg_mode_s अणु
	bfa_status_t	status;
	u16		bfad_num;
	u16		instance;
	काष्ठा bfa_port_cfg_mode_s cfg;
पूर्ण;

काष्ठा bfa_bsg_bbcr_enable_s अणु
	bfa_status_t    status;
	u16		bfad_num;
	u8		bb_scn;
	u8		rsvd;
पूर्ण;

काष्ठा bfa_bsg_bbcr_attr_s अणु
	bfa_status_t    status;
	u16		bfad_num;
	u16		rsvd;
	काष्ठा bfa_bbcr_attr_s attr;
पूर्ण;

काष्ठा bfa_bsg_faa_attr_s अणु
	bfa_status_t		status;
	u16			bfad_num;
	u16			rsvd;
	काष्ठा bfa_faa_attr_s	faa_attr;
पूर्ण;

काष्ठा bfa_bsg_cee_attr_s अणु
	bfa_status_t	status;
	u16		bfad_num;
	u16		rsvd;
	u32		buf_size;
	u32		rsvd1;
	u64		buf_ptr;
पूर्ण;

काष्ठा bfa_bsg_cee_stats_s अणु
	bfa_status_t	status;
	u16		bfad_num;
	u16		rsvd;
	u32		buf_size;
	u32		rsvd1;
	u64		buf_ptr;
पूर्ण;

काष्ठा bfa_bsg_sfp_media_s अणु
	bfa_status_t	status;
	u16		bfad_num;
	u16		rsvd;
	क्रमागत bfa_defs_sfp_media_e media;
पूर्ण;

काष्ठा bfa_bsg_sfp_speed_s अणु
	bfa_status_t	status;
	u16		bfad_num;
	u16		rsvd;
	क्रमागत bfa_port_speed speed;
पूर्ण;

काष्ठा bfa_bsg_flash_attr_s अणु
	bfa_status_t	status;
	u16		bfad_num;
	u16		rsvd;
	काष्ठा bfa_flash_attr_s attr;
पूर्ण;

काष्ठा bfa_bsg_flash_s अणु
	bfa_status_t	status;
	u16		bfad_num;
	u8		instance;
	u8		rsvd;
	क्रमागत  bfa_flash_part_type type;
	पूर्णांक		bufsz;
	u64		buf_ptr;
पूर्ण;

काष्ठा bfa_bsg_diag_get_temp_s अणु
	bfa_status_t	status;
	u16		bfad_num;
	u16		rsvd;
	काष्ठा bfa_diag_results_tempsensor_s result;
पूर्ण;

काष्ठा bfa_bsg_diag_memtest_s अणु
	bfa_status_t	status;
	u16		bfad_num;
	u16		rsvd[3];
	u32		pat;
	काष्ठा bfa_diag_memtest_result result;
	काष्ठा bfa_diag_memtest_s memtest;
पूर्ण;

काष्ठा bfa_bsg_diag_loopback_s अणु
	bfa_status_t	status;
	u16		bfad_num;
	u16		rsvd;
	क्रमागत bfa_port_opmode opmode;
	क्रमागत bfa_port_speed speed;
	u32		lpcnt;
	u32		pat;
	काष्ठा bfa_diag_loopback_result_s result;
पूर्ण;

काष्ठा bfa_bsg_diag_dport_show_s अणु
	bfa_status_t	status;
	u16		bfad_num;
	u16		rsvd;
	काष्ठा bfa_diag_dport_result_s result;
पूर्ण;

काष्ठा bfa_bsg_dport_enable_s अणु
	bfa_status_t	status;
	u16		bfad_num;
	u16		rsvd;
	u16		lpcnt;
	u16		pat;
पूर्ण;

काष्ठा bfa_bsg_diag_fwping_s अणु
	bfa_status_t	status;
	u16		bfad_num;
	u16		rsvd;
	u32		cnt;
	u32		pattern;
	काष्ठा bfa_diag_results_fwping result;
पूर्ण;

काष्ठा bfa_bsg_diag_qtest_s अणु
	bfa_status_t	status;
	u16	bfad_num;
	u16	rsvd;
	u32	क्रमce;
	u32	queue;
	काष्ठा bfa_diag_qtest_result_s result;
पूर्ण;

काष्ठा bfa_bsg_sfp_show_s अणु
	bfa_status_t	status;
	u16		bfad_num;
	u16		rsvd;
	काष्ठा sfp_mem_s sfp;
पूर्ण;

काष्ठा bfa_bsg_diag_led_s अणु
	bfa_status_t	status;
	u16		bfad_num;
	u16		rsvd;
	काष्ठा bfa_diag_ledtest_s ledtest;
पूर्ण;

काष्ठा bfa_bsg_diag_beacon_s अणु
	bfa_status_t	status;
	u16		bfad_num;
	u16		rsvd;
	bfa_boolean_t   beacon;
	bfa_boolean_t   link_e2e_beacon;
	u32		second;
पूर्ण;

काष्ठा bfa_bsg_diag_lb_stat_s अणु
	bfa_status_t	status;
	u16		bfad_num;
	u16		rsvd;
पूर्ण;

काष्ठा bfa_bsg_phy_attr_s अणु
	bfa_status_t	status;
	u16	bfad_num;
	u16	instance;
	काष्ठा bfa_phy_attr_s	attr;
पूर्ण;

काष्ठा bfa_bsg_phy_s अणु
	bfa_status_t	status;
	u16	bfad_num;
	u16	instance;
	u64	bufsz;
	u64	buf_ptr;
पूर्ण;

काष्ठा bfa_bsg_debug_s अणु
	bfa_status_t	status;
	u16		bfad_num;
	u16		rsvd;
	u32		bufsz;
	पूर्णांक		inst_no;
	u64		buf_ptr;
	u64		offset;
पूर्ण;

काष्ठा bfa_bsg_phy_stats_s अणु
	bfa_status_t	status;
	u16	bfad_num;
	u16	instance;
	काष्ठा bfa_phy_stats_s	stats;
पूर्ण;

काष्ठा bfa_bsg_vhba_attr_s अणु
	bfa_status_t	status;
	u16		bfad_num;
	u16		pcअगरn_id;
	काष्ठा bfa_vhba_attr_s	attr;
पूर्ण;

काष्ठा bfa_bsg_boot_s अणु
	bfa_status_t	status;
	u16		bfad_num;
	u16		rsvd;
	काष्ठा bfa_boot_cfg_s	cfg;
पूर्ण;

काष्ठा bfa_bsg_preboot_s अणु
	bfa_status_t	status;
	u16		bfad_num;
	u16		rsvd;
	काष्ठा bfa_boot_pbc_s	cfg;
पूर्ण;

काष्ठा bfa_bsg_ethboot_s अणु
	bfa_status_t	status;
	u16		bfad_num;
	u16		rsvd;
	काष्ठा  bfa_ethboot_cfg_s  cfg;
पूर्ण;

काष्ठा bfa_bsg_trunk_attr_s अणु
	bfa_status_t	status;
	u16		bfad_num;
	u16		rsvd;
	काष्ठा bfa_trunk_attr_s attr;
पूर्ण;

काष्ठा bfa_bsg_qos_attr_s अणु
	bfa_status_t	status;
	u16		bfad_num;
	u16		rsvd;
	काष्ठा bfa_qos_attr_s	attr;
पूर्ण;

काष्ठा bfa_bsg_qos_vc_attr_s अणु
	bfa_status_t	status;
	u16		bfad_num;
	u16		rsvd;
	काष्ठा bfa_qos_vc_attr_s attr;
पूर्ण;

काष्ठा bfa_bsg_qos_bw_s अणु
	bfa_status_t	status;
	u16		bfad_num;
	u16		rsvd;
	काष्ठा bfa_qos_bw_s qos_bw;
पूर्ण;

काष्ठा bfa_bsg_vf_stats_s अणु
	bfa_status_t	status;
	u16		bfad_num;
	u16		vf_id;
	काष्ठा bfa_vf_stats_s	stats;
पूर्ण;

काष्ठा bfa_bsg_vf_reset_stats_s अणु
	bfa_status_t	status;
	u16		bfad_num;
	u16		vf_id;
पूर्ण;

काष्ठा bfa_bsg_fcpim_lunmask_query_s अणु
	bfa_status_t	status;
	u16		bfad_num;
	काष्ठा bfa_lunmask_cfg_s lun_mask;
पूर्ण;

काष्ठा bfa_bsg_fcpim_lunmask_s अणु
	bfa_status_t	status;
	u16		bfad_num;
	u16		vf_id;
	wwn_t		pwwn;
	wwn_t		rpwwn;
	काष्ठा scsi_lun	lun;
पूर्ण;

काष्ठा bfa_bsg_fcpim_throttle_s अणु
	bfa_status_t	status;
	u16		bfad_num;
	u16		vf_id;
	काष्ठा bfa_defs_fcpim_throttle_s throttle;
पूर्ण;

#घोषणा BFA_TFRU_DATA_SIZE		64
#घोषणा BFA_MAX_FRUVPD_TRANSFER_SIZE	0x1000

काष्ठा bfa_bsg_tfru_s अणु
	bfa_status_t	status;
	u16		bfad_num;
	u16		rsvd;
	u32		offset;
	u32		len;
	u8		data[BFA_TFRU_DATA_SIZE];
पूर्ण;

काष्ठा bfa_bsg_fruvpd_s अणु
	bfa_status_t	status;
	u16		bfad_num;
	u16		rsvd1;
	u32		offset;
	u32		len;
	u8		data[BFA_MAX_FRUVPD_TRANSFER_SIZE];
	u8		trfr_cmpl;
	u8		rsvd2[3];
पूर्ण;

काष्ठा bfa_bsg_fruvpd_max_size_s अणु
	bfa_status_t	status;
	u16		bfad_num;
	u16		rsvd;
	u32		max_size;
पूर्ण;

काष्ठा bfa_bsg_fcpt_s अणु
	bfa_status_t    status;
	u16		vf_id;
	wwn_t		lpwwn;
	wwn_t		dpwwn;
	u32		tsecs;
	पूर्णांक		cts;
	क्रमागत fc_cos	cos;
	काष्ठा fchs_s	fchs;
पूर्ण;
#घोषणा bfa_bsg_fcpt_t काष्ठा bfa_bsg_fcpt_s

#आशय pack(1)
काष्ठा bfa_bsg_data अणु
	पूर्णांक payload_len;
	u64 payload;
पूर्ण;
#आशय pack()

#घोषणा bfad_chk_iocmd_sz(__payload_len, __hdrsz, __bufsz)	\
	(((__payload_len) != ((__hdrsz) + (__bufsz))) ?		\
	 BFA_STATUS_FAILED : BFA_STATUS_OK)

#पूर्ण_अगर /* BFAD_BSG_H */
