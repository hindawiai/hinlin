<शैली गुरु>
/*
 * This file is part of the Chelsio FCoE driver क्रम Linux.
 *
 * Copyright (c) 2009-2010 Chelsio Communications, Inc. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#अगर_अघोषित _T4FW_API_STOR_H_
#घोषणा _T4FW_API_STOR_H_


/******************************************************************************
 *   R E T U R N   V A L U E S
 ********************************/

क्रमागत fw_fcoe_link_sub_op अणु
	FCOE_LINK_DOWN	= 0x0,
	FCOE_LINK_UP	= 0x1,
	FCOE_LINK_COND	= 0x2,
पूर्ण;

क्रमागत fw_fcoe_link_status अणु
	FCOE_LINKDOWN	= 0x0,
	FCOE_LINKUP	= 0x1,
पूर्ण;

क्रमागत fw_ofld_prot अणु
	PROT_FCOE	= 0x1,
	PROT_ISCSI	= 0x2,
पूर्ण;

क्रमागत rport_type_fcoe अणु
	FLOGI_VFPORT	= 0x1,		/* 0xfffffe */
	FDISC_VFPORT	= 0x2,		/* 0xfffffe */
	NS_VNPORT	= 0x3,		/* 0xfffffc */
	REG_FC4_VNPORT	= 0x4,		/* any FC4 type VN_PORT */
	REG_VNPORT	= 0x5,		/* 0xfffxxx - non FC4 port in चयन */
	FDMI_VNPORT	= 0x6,		/* 0xfffffa */
	FAB_CTLR_VNPORT	= 0x7,		/* 0xfffffd */
पूर्ण;

क्रमागत event_cause_fcoe अणु
	PLOGI_ACC_RCVD		= 0x01,
	PLOGI_RJT_RCVD		= 0x02,
	PLOGI_RCVD		= 0x03,
	PLOGO_RCVD		= 0x04,
	PRLI_ACC_RCVD		= 0x05,
	PRLI_RJT_RCVD		= 0x06,
	PRLI_RCVD		= 0x07,
	PRLO_RCVD		= 0x08,
	NPORT_ID_CHGD		= 0x09,
	FLOGO_RCVD		= 0x0a,
	CLR_VIRT_LNK_RCVD	= 0x0b,
	FLOGI_ACC_RCVD		= 0x0c,
	FLOGI_RJT_RCVD		= 0x0d,
	FDISC_ACC_RCVD		= 0x0e,
	FDISC_RJT_RCVD		= 0x0f,
	FLOGI_TMO_MAX_RETRY	= 0x10,
	IMPL_LOGO_ADISC_ACC	= 0x11,
	IMPL_LOGO_ADISC_RJT	= 0x12,
	IMPL_LOGO_ADISC_CNFLT	= 0x13,
	PRLI_TMO		= 0x14,
	ADISC_TMO		= 0x15,
	RSCN_DEV_LOST		= 0x16,
	SCR_ACC_RCVD		= 0x17,
	ADISC_RJT_RCVD		= 0x18,
	LOGO_SNT		= 0x19,
	PROTO_ERR_IMPL_LOGO	= 0x1a,
पूर्ण;

क्रमागत fcoe_cmn_type अणु
	FCOE_ELS,
	FCOE_CT,
	FCOE_SCSI_CMD,
	FCOE_UNSOL_ELS,
पूर्ण;

क्रमागत fw_wr_stor_opcodes अणु
	FW_RDEV_WR                     = 0x38,
	FW_FCOE_ELS_CT_WR              = 0x30,
	FW_SCSI_WRITE_WR               = 0x31,
	FW_SCSI_READ_WR                = 0x32,
	FW_SCSI_CMD_WR                 = 0x33,
	FW_SCSI_ABRT_CLS_WR            = 0x34,
पूर्ण;

काष्ठा fw_rdev_wr अणु
	__be32 op_to_immdlen;
	__be32 alloc_to_len16;
	__be64 cookie;
	u8     protocol;
	u8     event_cause;
	u8     cur_state;
	u8     prev_state;
	__be32 flags_to_assoc_flowid;
	जोड़ rdev_entry अणु
		काष्ठा fcoe_rdev_entry अणु
			__be32 flowid;
			u8     protocol;
			u8     event_cause;
			u8     flags;
			u8     rjt_reason;
			u8     cur_login_st;
			u8     prev_login_st;
			__be16 rcv_fr_sz;
			u8     rd_xfer_rdy_to_rport_type;
			u8     vft_to_qos;
			u8     org_proc_assoc_to_acc_rsp_code;
			u8     enh_disc_to_tgt;
			u8     wwnn[8];
			u8     wwpn[8];
			__be16 iqid;
			u8     fc_oui[3];
			u8     r_id[3];
		पूर्ण fcoe_rdev;
		काष्ठा iscsi_rdev_entry अणु
			__be32 flowid;
			u8     protocol;
			u8     event_cause;
			u8     flags;
			u8     r3;
			__be16 iscsi_opts;
			__be16 tcp_opts;
			__be16 ip_opts;
			__be16 max_rcv_len;
			__be16 max_snd_len;
			__be16 first_brst_len;
			__be16 max_brst_len;
			__be16 r4;
			__be16 def_समय2रुको;
			__be16 def_समय2ret;
			__be16 nop_out_पूर्णांकrvl;
			__be16 non_scsi_to;
			__be16 isid;
			__be16 tsid;
			__be16 port;
			__be16 tpgt;
			u8     r5[6];
			__be16 iqid;
		पूर्ण iscsi_rdev;
	पूर्ण u;
पूर्ण;

#घोषणा FW_RDEV_WR_FLOWID_GET(x)	(((x) >> 8) & 0xfffff)
#घोषणा FW_RDEV_WR_ASSOC_FLOWID_GET(x)	(((x) >> 0) & 0xfffff)
#घोषणा FW_RDEV_WR_RPORT_TYPE_GET(x)	(((x) >> 0) & 0x1f)
#घोषणा FW_RDEV_WR_NPIV_GET(x)		(((x) >> 6) & 0x1)
#घोषणा FW_RDEV_WR_CLASS_GET(x)		(((x) >> 4) & 0x3)
#घोषणा FW_RDEV_WR_TASK_RETRY_ID_GET(x)	(((x) >> 5) & 0x1)
#घोषणा FW_RDEV_WR_RETRY_GET(x)		(((x) >> 4) & 0x1)
#घोषणा FW_RDEV_WR_CONF_CMPL_GET(x)	(((x) >> 3) & 0x1)
#घोषणा FW_RDEV_WR_INI_GET(x)		(((x) >> 1) & 0x1)
#घोषणा FW_RDEV_WR_TGT_GET(x)		(((x) >> 0) & 0x1)

काष्ठा fw_fcoe_els_ct_wr अणु
	__be32 op_immdlen;
	__be32 flowid_len16;
	u64    cookie;
	__be16 iqid;
	u8     पंचांगo_val;
	u8     els_ct_type;
	u8     ctl_pri;
	u8     cp_en_class;
	__be16 xfer_cnt;
	u8     fl_to_sp;
	u8     l_id[3];
	u8     r5;
	u8     r_id[3];
	__be64 rsp_dmaaddr;
	__be32 rsp_dmalen;
	__be32 r6;
पूर्ण;

#घोषणा FW_FCOE_ELS_CT_WR_OPCODE(x)		((x) << 24)
#घोषणा FW_FCOE_ELS_CT_WR_OPCODE_GET(x)		(((x) >> 24) & 0xff)
#घोषणा FW_FCOE_ELS_CT_WR_IMMDLEN(x)		((x) << 0)
#घोषणा FW_FCOE_ELS_CT_WR_IMMDLEN_GET(x)	(((x) >> 0) & 0xff)
#घोषणा FW_FCOE_ELS_CT_WR_SP(x)			((x) << 0)

काष्ठा fw_scsi_ग_लिखो_wr अणु
	__be32 op_immdlen;
	__be32 flowid_len16;
	u64    cookie;
	__be16 iqid;
	u8     पंचांगo_val;
	u8     use_xfer_cnt;
	जोड़ fw_scsi_ग_लिखो_priv अणु
		काष्ठा fcoe_ग_लिखो_priv अणु
			u8   ctl_pri;
			u8   cp_en_class;
			u8   r3_lo[2];
		पूर्ण fcoe;
		काष्ठा iscsi_ग_लिखो_priv अणु
			u8   r3[4];
		पूर्ण iscsi;
	पूर्ण u;
	__be32 xfer_cnt;
	__be32 ini_xfer_cnt;
	__be64 rsp_dmaaddr;
	__be32 rsp_dmalen;
	__be32 r4;
पूर्ण;

#घोषणा FW_SCSI_WRITE_WR_IMMDLEN(x)	((x) << 0)

काष्ठा fw_scsi_पढ़ो_wr अणु
	__be32 op_immdlen;
	__be32 flowid_len16;
	u64    cookie;
	__be16 iqid;
	u8     पंचांगo_val;
	u8     use_xfer_cnt;
	जोड़ fw_scsi_पढ़ो_priv अणु
		काष्ठा fcoe_पढ़ो_priv अणु
			u8   ctl_pri;
			u8   cp_en_class;
			u8   r3_lo[2];
		पूर्ण fcoe;
		काष्ठा iscsi_पढ़ो_priv अणु
			u8   r3[4];
		पूर्ण iscsi;
	पूर्ण u;
	__be32 xfer_cnt;
	__be32 ini_xfer_cnt;
	__be64 rsp_dmaaddr;
	__be32 rsp_dmalen;
	__be32 r4;
पूर्ण;

#घोषणा FW_SCSI_READ_WR_IMMDLEN(x)	((x) << 0)

काष्ठा fw_scsi_cmd_wr अणु
	__be32 op_immdlen;
	__be32 flowid_len16;
	u64    cookie;
	__be16 iqid;
	u8     पंचांगo_val;
	u8     r3;
	जोड़ fw_scsi_cmd_priv अणु
		काष्ठा fcoe_cmd_priv अणु
			u8   ctl_pri;
			u8   cp_en_class;
			u8   r4_lo[2];
		पूर्ण fcoe;
		काष्ठा iscsi_cmd_priv अणु
			u8   r4[4];
		पूर्ण iscsi;
	पूर्ण u;
	u8     r5[8];
	__be64 rsp_dmaaddr;
	__be32 rsp_dmalen;
	__be32 r6;
पूर्ण;

#घोषणा FW_SCSI_CMD_WR_IMMDLEN(x)	((x) << 0)

#घोषणा SCSI_ABORT 0
#घोषणा SCSI_CLOSE 1

काष्ठा fw_scsi_abrt_cls_wr अणु
	__be32 op_immdlen;
	__be32 flowid_len16;
	u64    cookie;
	__be16 iqid;
	u8     पंचांगo_val;
	u8     sub_opcode_to_chk_all_io;
	u8     r3[4];
	u64    t_cookie;
पूर्ण;

#घोषणा FW_SCSI_ABRT_CLS_WR_SUB_OPCODE(x)	((x) << 2)
#घोषणा FW_SCSI_ABRT_CLS_WR_SUB_OPCODE_GET(x)	(((x) >> 2) & 0x3f)
#घोषणा FW_SCSI_ABRT_CLS_WR_CHK_ALL_IO(x)	((x) << 0)

क्रमागत fw_cmd_stor_opcodes अणु
	FW_FCOE_RES_INFO_CMD           = 0x31,
	FW_FCOE_LINK_CMD               = 0x32,
	FW_FCOE_VNP_CMD                = 0x33,
	FW_FCOE_SPARAMS_CMD            = 0x35,
	FW_FCOE_STATS_CMD              = 0x37,
	FW_FCOE_FCF_CMD                = 0x38,
पूर्ण;

काष्ठा fw_fcoe_res_info_cmd अणु
	__be32 op_to_पढ़ो;
	__be32 retval_len16;
	__be16 e_d_tov;
	__be16 r_a_tov_seq;
	__be16 r_a_tov_els;
	__be16 r_r_tov;
	__be32 max_xchgs;
	__be32 max_ssns;
	__be32 used_xchgs;
	__be32 used_ssns;
	__be32 max_fcfs;
	__be32 max_vnps;
	__be32 used_fcfs;
	__be32 used_vnps;
पूर्ण;

काष्ठा fw_fcoe_link_cmd अणु
	__be32 op_to_portid;
	__be32 retval_len16;
	__be32 sub_opcode_fcfi;
	u8     r3;
	u8     lstatus;
	__be16 flags;
	u8     r4;
	u8     set_vlan;
	__be16 vlan_id;
	__be32 vnpi_pkd;
	__be16 r6;
	u8     phy_mac[6];
	u8     vnport_wwnn[8];
	u8     vnport_wwpn[8];
पूर्ण;

#घोषणा FW_FCOE_LINK_CMD_PORTID(x)	((x) << 0)
#घोषणा FW_FCOE_LINK_CMD_PORTID_GET(x)	(((x) >> 0) & 0xf)
#घोषणा FW_FCOE_LINK_CMD_SUB_OPCODE(x)  ((x) << 24U)
#घोषणा FW_FCOE_LINK_CMD_FCFI(x)	((x) << 0)
#घोषणा FW_FCOE_LINK_CMD_FCFI_GET(x)	(((x) >> 0) & 0xffffff)
#घोषणा FW_FCOE_LINK_CMD_VNPI_GET(x)	(((x) >> 0) & 0xfffff)

काष्ठा fw_fcoe_vnp_cmd अणु
	__be32 op_to_fcfi;
	__be32 alloc_to_len16;
	__be32 gen_wwn_to_vnpi;
	__be32 vf_id;
	__be16 iqid;
	u8   vnport_mac[6];
	u8   vnport_wwnn[8];
	u8   vnport_wwpn[8];
	u8   cmn_srv_parms[16];
	u8   clsp_word_0_1[8];
पूर्ण;

#घोषणा FW_FCOE_VNP_CMD_FCFI(x)		((x) << 0)
#घोषणा FW_FCOE_VNP_CMD_ALLOC		(1U << 31)
#घोषणा FW_FCOE_VNP_CMD_FREE		(1U << 30)
#घोषणा FW_FCOE_VNP_CMD_MODIFY		(1U << 29)
#घोषणा FW_FCOE_VNP_CMD_GEN_WWN		(1U << 22)
#घोषणा FW_FCOE_VNP_CMD_VFID_EN		(1U << 20)
#घोषणा FW_FCOE_VNP_CMD_VNPI(x)		((x) << 0)
#घोषणा FW_FCOE_VNP_CMD_VNPI_GET(x)	(((x) >> 0) & 0xfffff)

काष्ठा fw_fcoe_sparams_cmd अणु
	__be32 op_to_portid;
	__be32 retval_len16;
	u8     r3[7];
	u8     cos;
	u8     lport_wwnn[8];
	u8     lport_wwpn[8];
	u8     cmn_srv_parms[16];
	u8     cls_srv_parms[16];
पूर्ण;

#घोषणा FW_FCOE_SPARAMS_CMD_PORTID(x)	((x) << 0)

काष्ठा fw_fcoe_stats_cmd अणु
	__be32 op_to_flowid;
	__be32 मुक्त_to_len16;
	जोड़ fw_fcoe_stats अणु
		काष्ठा fw_fcoe_stats_ctl अणु
			u8   nstats_port;
			u8   port_valid_ix;
			__be16 r6;
			__be32 r7;
			__be64 stat0;
			__be64 stat1;
			__be64 stat2;
			__be64 stat3;
			__be64 stat4;
			__be64 stat5;
		पूर्ण ctl;
		काष्ठा fw_fcoe_port_stats अणु
			__be64 tx_bcast_bytes;
			__be64 tx_bcast_frames;
			__be64 tx_mcast_bytes;
			__be64 tx_mcast_frames;
			__be64 tx_ucast_bytes;
			__be64 tx_ucast_frames;
			__be64 tx_drop_frames;
			__be64 tx_offload_bytes;
			__be64 tx_offload_frames;
			__be64 rx_bcast_bytes;
			__be64 rx_bcast_frames;
			__be64 rx_mcast_bytes;
			__be64 rx_mcast_frames;
			__be64 rx_ucast_bytes;
			__be64 rx_ucast_frames;
			__be64 rx_err_frames;
		पूर्ण port_stats;
		काष्ठा fw_fcoe_fcf_stats अणु
			__be32 fip_tx_bytes;
			__be32 fip_tx_fr;
			__be64 fcf_ka;
			__be64 mcast_adv_rcvd;
			__be16 ucast_adv_rcvd;
			__be16 sol_sent;
			__be16 vlan_req;
			__be16 vlan_rpl;
			__be16 clr_vlink;
			__be16 link_करोwn;
			__be16 link_up;
			__be16 logo;
			__be16 flogi_req;
			__be16 flogi_rpl;
			__be16 fdisc_req;
			__be16 fdisc_rpl;
			__be16 fka_prd_chg;
			__be16 fc_map_chg;
			__be16 vfid_chg;
			u8   no_fka_req;
			u8   no_vnp;
		पूर्ण fcf_stats;
		काष्ठा fw_fcoe_pcb_stats अणु
			__be64 tx_bytes;
			__be64 tx_frames;
			__be64 rx_bytes;
			__be64 rx_frames;
			__be32 vnp_ka;
			__be32 unsol_els_rcvd;
			__be64 unsol_cmd_rcvd;
			__be16 implicit_logo;
			__be16 flogi_inv_sparm;
			__be16 fdisc_inv_sparm;
			__be16 flogi_rjt;
			__be16 fdisc_rjt;
			__be16 no_ssn;
			__be16 mac_flt_fail;
			__be16 inv_fr_rcvd;
		पूर्ण pcb_stats;
		काष्ठा fw_fcoe_scb_stats अणु
			__be64 tx_bytes;
			__be64 tx_frames;
			__be64 rx_bytes;
			__be64 rx_frames;
			__be32 host_abrt_req;
			__be32 adap_स्वतः_abrt;
			__be32 adap_abrt_rsp;
			__be32 host_ios_req;
			__be16 ssn_offl_ios;
			__be16 ssn_not_rdy_ios;
			u8   rx_data_ddp_err;
			u8   ddp_flt_set_err;
			__be16 rx_data_fr_err;
			u8   bad_st_abrt_req;
			u8   no_io_abrt_req;
			u8   पात_पंचांगo;
			u8   पात_पंचांगo_2;
			__be32 पात_req;
			u8   no_ppod_res_पंचांगo;
			u8   bp_पंचांगo;
			u8   adap_स्वतः_cls;
			u8   no_io_cls_req;
			__be32 host_cls_req;
			__be64 unsol_cmd_rcvd;
			__be32 plogi_req_rcvd;
			__be32 prli_req_rcvd;
			__be16 logo_req_rcvd;
			__be16 prlo_req_rcvd;
			__be16 plogi_rjt_rcvd;
			__be16 prli_rjt_rcvd;
			__be32 adisc_req_rcvd;
			__be32 rscn_rcvd;
			__be32 rrq_req_rcvd;
			__be32 unsol_els_rcvd;
			u8   adisc_rjt_rcvd;
			u8   scr_rjt;
			u8   ct_rjt;
			u8   inval_bls_rcvd;
			__be32 ba_rjt_rcvd;
		पूर्ण scb_stats;
	पूर्ण u;
पूर्ण;

#घोषणा FW_FCOE_STATS_CMD_FLOWID(x)	((x) << 0)
#घोषणा FW_FCOE_STATS_CMD_FREE		(1U << 30)
#घोषणा FW_FCOE_STATS_CMD_NSTATS(x)	((x) << 4)
#घोषणा FW_FCOE_STATS_CMD_PORT(x)	((x) << 0)
#घोषणा FW_FCOE_STATS_CMD_PORT_VALID	(1U << 7)
#घोषणा FW_FCOE_STATS_CMD_IX(x)		((x) << 0)

काष्ठा fw_fcoe_fcf_cmd अणु
	__be32 op_to_fcfi;
	__be32 retval_len16;
	__be16 priority_pkd;
	u8     mac[6];
	u8     name_id[8];
	u8     fabric[8];
	__be16 vf_id;
	__be16 max_fcoe_size;
	u8     vlan_id;
	u8     fc_map[3];
	__be32 fka_adv;
	__be32 r6;
	u8     r7_hi;
	u8     fpma_to_portid;
	u8     spma_mac[6];
	__be64 r8;
पूर्ण;

#घोषणा FW_FCOE_FCF_CMD_FCFI(x)		((x) << 0)
#घोषणा FW_FCOE_FCF_CMD_FCFI_GET(x)	(((x) >> 0) & 0xfffff)
#घोषणा FW_FCOE_FCF_CMD_PRIORITY_GET(x)	(((x) >> 0) & 0xff)
#घोषणा FW_FCOE_FCF_CMD_FPMA_GET(x)	(((x) >> 6) & 0x1)
#घोषणा FW_FCOE_FCF_CMD_SPMA_GET(x)	(((x) >> 5) & 0x1)
#घोषणा FW_FCOE_FCF_CMD_LOGIN_GET(x)	(((x) >> 4) & 0x1)
#घोषणा FW_FCOE_FCF_CMD_PORTID_GET(x)	(((x) >> 0) & 0xf)

#पूर्ण_अगर /* _T4FW_API_STOR_H_ */
