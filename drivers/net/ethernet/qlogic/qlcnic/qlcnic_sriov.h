<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * QLogic qlcnic NIC Driver
 * Copyright (c) 2009-2013 QLogic Corporation
 */

#अगर_अघोषित _QLCNIC_83XX_SRIOV_H_
#घोषणा _QLCNIC_83XX_SRIOV_H_

#समावेश <linux/types.h>
#समावेश <linux/pci.h>

#समावेश "qlcnic.h"

बाह्य स्थिर u32 qlcnic_83xx_reg_tbl[];
बाह्य स्थिर u32 qlcnic_83xx_ext_reg_tbl[];

काष्ठा qlcnic_bc_payload अणु
	u64 payload[126];
पूर्ण;

काष्ठा qlcnic_bc_hdr अणु
#अगर defined(__LITTLE_ENDIAN)
	u8	version;
	u8	msg_type:4;
	u8	rsvd1:3;
	u8	op_type:1;
	u8	num_cmds;
	u8	num_frags;
	u8	frag_num;
	u8	cmd_op;
	u16	seq_id;
	u64	rsvd3;
#या_अगर defined(__BIG_ENDIAN)
	u8	num_frags;
	u8	num_cmds;
	u8	op_type:1;
	u8	rsvd1:3;
	u8	msg_type:4;
	u8	version;
	u16	seq_id;
	u8	cmd_op;
	u8	frag_num;
	u64	rsvd3;
#पूर्ण_अगर
पूर्ण;

क्रमागत qlcnic_bc_commands अणु
	QLCNIC_BC_CMD_CHANNEL_INIT = 0x0,
	QLCNIC_BC_CMD_CHANNEL_TERM = 0x1,
	QLCNIC_BC_CMD_GET_ACL = 0x2,
	QLCNIC_BC_CMD_CFG_GUEST_VLAN = 0x3,
पूर्ण;

#घोषणा QLCNIC_83XX_SRIOV_VF_MAX_MAC 2
#घोषणा QLC_BC_CMD 1

काष्ठा qlcnic_trans_list अणु
	/* Lock क्रम manipulating list */
	spinlock_t		lock;
	काष्ठा list_head	रुको_list;
	पूर्णांक			count;
पूर्ण;

क्रमागत qlcnic_trans_state अणु
	QLC_INIT = 0,
	QLC_WAIT_FOR_CHANNEL_FREE,
	QLC_WAIT_FOR_RESP,
	QLC_ABORT,
	QLC_END,
पूर्ण;

काष्ठा qlcnic_bc_trans अणु
	u8				func_id;
	u8				active;
	u8				curr_rsp_frag;
	u8				curr_req_frag;
	u16				cmd_id;
	u16				req_pay_size;
	u16				rsp_pay_size;
	u32				trans_id;
	क्रमागत qlcnic_trans_state		trans_state;
	काष्ठा list_head		list;
	काष्ठा qlcnic_bc_hdr		*req_hdr;
	काष्ठा qlcnic_bc_hdr		*rsp_hdr;
	काष्ठा qlcnic_bc_payload	*req_pay;
	काष्ठा qlcnic_bc_payload	*rsp_pay;
	काष्ठा completion		resp_cmpl;
	काष्ठा qlcnic_vf_info		*vf;
पूर्ण;

क्रमागत qlcnic_vf_state अणु
	QLC_BC_VF_SEND = 0,
	QLC_BC_VF_RECV,
	QLC_BC_VF_CHANNEL,
	QLC_BC_VF_STATE,
	QLC_BC_VF_FLR,
	QLC_BC_VF_SOFT_FLR,
पूर्ण;

क्रमागत qlcnic_vlan_mode अणु
	QLC_NO_VLAN_MODE = 0,
	QLC_PVID_MODE,
	QLC_GUEST_VLAN_MODE,
पूर्ण;

काष्ठा qlcnic_resources अणु
	u16 num_tx_mac_filters;
	u16 num_rx_ucast_mac_filters;
	u16 num_rx_mcast_mac_filters;

	u16 num_txvlan_keys;

	u16 num_rx_queues;
	u16 num_tx_queues;

	u16 num_rx_buf_rings;
	u16 num_rx_status_rings;

	u16 num_destip;
	u32 num_lro_flows_supported;
	u16 max_local_ipv6_addrs;
	u16 max_remote_ipv6_addrs;
पूर्ण;

काष्ठा qlcnic_vport अणु
	u16			handle;
	u16			max_tx_bw;
	u16			min_tx_bw;
	u16			pvid;
	u8			vlan_mode;
	u8			qos;
	bool			spoofchk;
	u8			mac[6];
पूर्ण;

काष्ठा qlcnic_vf_info अणु
	u8				pci_func;
	u16				rx_ctx_id;
	u16				tx_ctx_id;
	u16				*sriov_vlans;
	पूर्णांक				num_vlan;
	अचिन्हित दीर्घ			state;
	काष्ठा completion		ch_मुक्त_cmpl;
	काष्ठा work_काष्ठा		trans_work;
	काष्ठा work_काष्ठा		flr_work;
	/* It synchronizes commands sent from VF */
	काष्ठा mutex			send_cmd_lock;
	काष्ठा qlcnic_bc_trans		*send_cmd;
	काष्ठा qlcnic_bc_trans		*flr_trans;
	काष्ठा qlcnic_trans_list	rcv_act;
	काष्ठा qlcnic_trans_list	rcv_pend;
	काष्ठा qlcnic_adapter		*adapter;
	काष्ठा qlcnic_vport		*vp;
	spinlock_t			vlan_list_lock;	/* Lock क्रम VLAN list */
पूर्ण;

काष्ठा qlcnic_async_cmd अणु
	काष्ठा list_head	list;
	काष्ठा qlcnic_cmd_args	*cmd;
पूर्ण;

काष्ठा qlcnic_back_channel अणु
	u16			trans_counter;
	काष्ठा workqueue_काष्ठा *bc_trans_wq;
	काष्ठा workqueue_काष्ठा *bc_async_wq;
	काष्ठा workqueue_काष्ठा *bc_flr_wq;
	काष्ठा qlcnic_adapter	*adapter;
	काष्ठा list_head	async_cmd_list;
	काष्ठा work_काष्ठा	vf_async_work;
	spinlock_t		queue_lock; /* async_cmd_list queue lock */
पूर्ण;

काष्ठा qlcnic_sriov अणु
	u16				vp_handle;
	u8				num_vfs;
	u8				any_vlan;
	u8				vlan_mode;
	u16				num_allowed_vlans;
	u16				*allowed_vlans;
	u16				vlan;
	काष्ठा qlcnic_resources		ff_max;
	काष्ठा qlcnic_back_channel	bc;
	काष्ठा qlcnic_vf_info		*vf_info;
पूर्ण;

पूर्णांक qlcnic_sriov_init(काष्ठा qlcnic_adapter *, पूर्णांक);
व्योम qlcnic_sriov_cleanup(काष्ठा qlcnic_adapter *);
व्योम __qlcnic_sriov_cleanup(काष्ठा qlcnic_adapter *);
व्योम qlcnic_sriov_vf_रेजिस्टर_map(काष्ठा qlcnic_hardware_context *);
पूर्णांक qlcnic_sriov_vf_init(काष्ठा qlcnic_adapter *, पूर्णांक);
व्योम qlcnic_sriov_vf_set_ops(काष्ठा qlcnic_adapter *);
पूर्णांक qlcnic_sriov_func_to_index(काष्ठा qlcnic_adapter *, u8);
व्योम qlcnic_sriov_handle_bc_event(काष्ठा qlcnic_adapter *, u32);
पूर्णांक qlcnic_sriov_cfg_bc_पूर्णांकr(काष्ठा qlcnic_adapter *, u8);
व्योम qlcnic_sriov_cleanup_async_list(काष्ठा qlcnic_back_channel *);
व्योम qlcnic_sriov_cleanup_list(काष्ठा qlcnic_trans_list *);
पूर्णांक __qlcnic_sriov_add_act_list(काष्ठा qlcnic_sriov *, काष्ठा qlcnic_vf_info *,
				काष्ठा qlcnic_bc_trans *);
पूर्णांक qlcnic_sriov_get_vf_vport_info(काष्ठा qlcnic_adapter *,
				   काष्ठा qlcnic_info *, u16);
पूर्णांक qlcnic_sriov_cfg_vf_guest_vlan(काष्ठा qlcnic_adapter *, u16, u8);
व्योम qlcnic_sriov_मुक्त_vlans(काष्ठा qlcnic_adapter *);
व्योम qlcnic_sriov_alloc_vlans(काष्ठा qlcnic_adapter *);
bool qlcnic_sriov_check_any_vlan(काष्ठा qlcnic_vf_info *);
व्योम qlcnic_sriov_del_vlan_id(काष्ठा qlcnic_sriov *,
			      काष्ठा qlcnic_vf_info *, u16);
व्योम qlcnic_sriov_add_vlan_id(काष्ठा qlcnic_sriov *,
			      काष्ठा qlcnic_vf_info *, u16);

अटल अंतरभूत bool qlcnic_sriov_enable_check(काष्ठा qlcnic_adapter *adapter)
अणु
	वापस test_bit(__QLCNIC_SRIOV_ENABLE, &adapter->state) ? true : false;
पूर्ण

#अगर_घोषित CONFIG_QLCNIC_SRIOV
व्योम qlcnic_sriov_pf_process_bc_cmd(काष्ठा qlcnic_adapter *,
				    काष्ठा qlcnic_bc_trans *,
				    काष्ठा qlcnic_cmd_args *);
व्योम qlcnic_sriov_pf_disable(काष्ठा qlcnic_adapter *);
व्योम qlcnic_sriov_pf_cleanup(काष्ठा qlcnic_adapter *);
पूर्णांक qlcnic_pci_sriov_configure(काष्ठा pci_dev *, पूर्णांक);
व्योम qlcnic_pf_set_पूर्णांकerface_id_create_rx_ctx(काष्ठा qlcnic_adapter *, u32 *);
व्योम qlcnic_pf_set_पूर्णांकerface_id_create_tx_ctx(काष्ठा qlcnic_adapter *, u32 *);
व्योम qlcnic_pf_set_पूर्णांकerface_id_del_rx_ctx(काष्ठा qlcnic_adapter *, u32 *);
व्योम qlcnic_pf_set_पूर्णांकerface_id_del_tx_ctx(काष्ठा qlcnic_adapter *, u32 *);
व्योम qlcnic_pf_set_पूर्णांकerface_id_promisc(काष्ठा qlcnic_adapter *, u32 *);
व्योम qlcnic_pf_set_पूर्णांकerface_id_ipaddr(काष्ठा qlcnic_adapter *, u32 *);
व्योम qlcnic_pf_set_पूर्णांकerface_id_macaddr(काष्ठा qlcnic_adapter *, u32 *);
व्योम qlcnic_sriov_pf_handle_flr(काष्ठा qlcnic_sriov *, काष्ठा qlcnic_vf_info *);
bool qlcnic_sriov_soft_flr_check(काष्ठा qlcnic_adapter *,
				 काष्ठा qlcnic_bc_trans *,
				 काष्ठा qlcnic_vf_info *);
व्योम qlcnic_sriov_pf_reset(काष्ठा qlcnic_adapter *);
पूर्णांक qlcnic_sriov_pf_reinit(काष्ठा qlcnic_adapter *);
पूर्णांक qlcnic_sriov_set_vf_mac(काष्ठा net_device *, पूर्णांक, u8 *);
पूर्णांक qlcnic_sriov_set_vf_tx_rate(काष्ठा net_device *, पूर्णांक, पूर्णांक, पूर्णांक);
पूर्णांक qlcnic_sriov_get_vf_config(काष्ठा net_device *, पूर्णांक ,
			       काष्ठा अगरla_vf_info *);
पूर्णांक qlcnic_sriov_set_vf_vlan(काष्ठा net_device *, पूर्णांक, u16, u8, __be16);
पूर्णांक qlcnic_sriov_set_vf_spoofchk(काष्ठा net_device *, पूर्णांक, bool);
#अन्यथा
अटल अंतरभूत व्योम qlcnic_sriov_pf_disable(काष्ठा qlcnic_adapter *adapter) अणुपूर्ण
अटल अंतरभूत व्योम qlcnic_sriov_pf_cleanup(काष्ठा qlcnic_adapter *adapter) अणुपूर्ण
अटल अंतरभूत व्योम
qlcnic_pf_set_पूर्णांकerface_id_create_rx_ctx(काष्ठा qlcnic_adapter *adapter,
					 u32 *पूर्णांक_id) अणुपूर्ण
अटल अंतरभूत व्योम
qlcnic_pf_set_पूर्णांकerface_id_create_tx_ctx(काष्ठा qlcnic_adapter *adapter,
					 u32 *पूर्णांक_id) अणुपूर्ण
अटल अंतरभूत व्योम
qlcnic_pf_set_पूर्णांकerface_id_del_rx_ctx(काष्ठा qlcnic_adapter *adapter,
				      u32 *पूर्णांक_id) अणुपूर्ण
अटल अंतरभूत व्योम
qlcnic_pf_set_पूर्णांकerface_id_del_tx_ctx(काष्ठा qlcnic_adapter *adapter,
				      u32 *पूर्णांक_id) अणुपूर्ण
अटल अंतरभूत व्योम
qlcnic_pf_set_पूर्णांकerface_id_ipaddr(काष्ठा qlcnic_adapter *adapter, u32 *पूर्णांक_id)
अणुपूर्ण
अटल अंतरभूत व्योम
qlcnic_pf_set_पूर्णांकerface_id_macaddr(काष्ठा qlcnic_adapter *adapter, u32 *पूर्णांक_id)
अणुपूर्ण
अटल अंतरभूत व्योम
qlcnic_pf_set_पूर्णांकerface_id_promisc(काष्ठा qlcnic_adapter *adapter, u32 *पूर्णांक_id)
अणुपूर्ण
अटल अंतरभूत व्योम qlcnic_sriov_pf_handle_flr(काष्ठा qlcnic_sriov *sriov,
					      काष्ठा qlcnic_vf_info *vf) अणुपूर्ण
अटल अंतरभूत bool qlcnic_sriov_soft_flr_check(काष्ठा qlcnic_adapter *adapter,
					       काष्ठा qlcnic_bc_trans *trans,
					       काष्ठा qlcnic_vf_info *vf)
अणु वापस false; पूर्ण
अटल अंतरभूत व्योम qlcnic_sriov_pf_reset(काष्ठा qlcnic_adapter *adapter) अणुपूर्ण
अटल अंतरभूत पूर्णांक qlcnic_sriov_pf_reinit(काष्ठा qlcnic_adapter *adapter)
अणु वापस 0; पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
