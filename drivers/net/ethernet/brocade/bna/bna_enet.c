<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Linux network driver क्रम QLogic BR-series Converged Network Adapter.
 */
/*
 * Copyright (c) 2005-2014 Brocade Communications Systems, Inc.
 * Copyright (c) 2014-2015 QLogic Corporation
 * All rights reserved
 * www.qlogic.com
 */
#समावेश "bna.h"

अटल अंतरभूत पूर्णांक
ethport_can_be_up(काष्ठा bna_ethport *ethport)
अणु
	पूर्णांक पढ़ोy = 0;
	अगर (ethport->bna->enet.type == BNA_ENET_T_REGULAR)
		पढ़ोy = ((ethport->flags & BNA_ETHPORT_F_ADMIN_UP) &&
			 (ethport->flags & BNA_ETHPORT_F_RX_STARTED) &&
			 (ethport->flags & BNA_ETHPORT_F_PORT_ENABLED));
	अन्यथा
		पढ़ोy = ((ethport->flags & BNA_ETHPORT_F_ADMIN_UP) &&
			 (ethport->flags & BNA_ETHPORT_F_RX_STARTED) &&
			 !(ethport->flags & BNA_ETHPORT_F_PORT_ENABLED));
	वापस पढ़ोy;
पूर्ण

#घोषणा ethport_is_up ethport_can_be_up

क्रमागत bna_ethport_event अणु
	ETHPORT_E_START			= 1,
	ETHPORT_E_STOP			= 2,
	ETHPORT_E_FAIL			= 3,
	ETHPORT_E_UP			= 4,
	ETHPORT_E_DOWN			= 5,
	ETHPORT_E_FWRESP_UP_OK		= 6,
	ETHPORT_E_FWRESP_DOWN		= 7,
	ETHPORT_E_FWRESP_UP_FAIL	= 8,
पूर्ण;

क्रमागत bna_enet_event अणु
	ENET_E_START			= 1,
	ENET_E_STOP			= 2,
	ENET_E_FAIL			= 3,
	ENET_E_PAUSE_CFG		= 4,
	ENET_E_MTU_CFG			= 5,
	ENET_E_FWRESP_PAUSE		= 6,
	ENET_E_CHLD_STOPPED		= 7,
पूर्ण;

क्रमागत bna_ioceth_event अणु
	IOCETH_E_ENABLE			= 1,
	IOCETH_E_DISABLE		= 2,
	IOCETH_E_IOC_RESET		= 3,
	IOCETH_E_IOC_FAILED		= 4,
	IOCETH_E_IOC_READY		= 5,
	IOCETH_E_ENET_ATTR_RESP		= 6,
	IOCETH_E_ENET_STOPPED		= 7,
	IOCETH_E_IOC_DISABLED		= 8,
पूर्ण;

#घोषणा bna_stats_copy(_name, _type)					\
करो अणु									\
	count = माप(काष्ठा bfi_enet_stats_ ## _type) / माप(u64);	\
	stats_src = (u64 *)&bna->stats.hw_stats_kva->_name ## _stats;	\
	stats_dst = (u64 *)&bna->stats.hw_stats._name ## _stats;	\
	क्रम (i = 0; i < count; i++)					\
		stats_dst[i] = be64_to_cpu(stats_src[i]);		\
पूर्ण जबतक (0)								\

/*
 * FW response handlers
 */

अटल व्योम
bna_bfi_ethport_enable_aen(काष्ठा bna_ethport *ethport,
				काष्ठा bfi_msgq_mhdr *msghdr)
अणु
	ethport->flags |= BNA_ETHPORT_F_PORT_ENABLED;

	अगर (ethport_can_be_up(ethport))
		bfa_fsm_send_event(ethport, ETHPORT_E_UP);
पूर्ण

अटल व्योम
bna_bfi_ethport_disable_aen(काष्ठा bna_ethport *ethport,
				काष्ठा bfi_msgq_mhdr *msghdr)
अणु
	पूर्णांक ethport_up = ethport_is_up(ethport);

	ethport->flags &= ~BNA_ETHPORT_F_PORT_ENABLED;

	अगर (ethport_up)
		bfa_fsm_send_event(ethport, ETHPORT_E_DOWN);
पूर्ण

अटल व्योम
bna_bfi_ethport_admin_rsp(काष्ठा bna_ethport *ethport,
				काष्ठा bfi_msgq_mhdr *msghdr)
अणु
	काष्ठा bfi_enet_enable_req *admin_req =
		&ethport->bfi_enet_cmd.admin_req;
	काष्ठा bfi_enet_rsp *rsp =
		container_of(msghdr, काष्ठा bfi_enet_rsp, mh);

	चयन (admin_req->enable) अणु
	हाल BNA_STATUS_T_ENABLED:
		अगर (rsp->error == BFI_ENET_CMD_OK)
			bfa_fsm_send_event(ethport, ETHPORT_E_FWRESP_UP_OK);
		अन्यथा अणु
			ethport->flags &= ~BNA_ETHPORT_F_PORT_ENABLED;
			bfa_fsm_send_event(ethport, ETHPORT_E_FWRESP_UP_FAIL);
		पूर्ण
		अवरोध;

	हाल BNA_STATUS_T_DISABLED:
		bfa_fsm_send_event(ethport, ETHPORT_E_FWRESP_DOWN);
		ethport->link_status = BNA_LINK_DOWN;
		ethport->link_cbfn(ethport->bna->bnad, BNA_LINK_DOWN);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम
bna_bfi_ethport_lpbk_rsp(काष्ठा bna_ethport *ethport,
				काष्ठा bfi_msgq_mhdr *msghdr)
अणु
	काष्ठा bfi_enet_diag_lb_req *diag_lb_req =
		&ethport->bfi_enet_cmd.lpbk_req;
	काष्ठा bfi_enet_rsp *rsp =
		container_of(msghdr, काष्ठा bfi_enet_rsp, mh);

	चयन (diag_lb_req->enable) अणु
	हाल BNA_STATUS_T_ENABLED:
		अगर (rsp->error == BFI_ENET_CMD_OK)
			bfa_fsm_send_event(ethport, ETHPORT_E_FWRESP_UP_OK);
		अन्यथा अणु
			ethport->flags &= ~BNA_ETHPORT_F_ADMIN_UP;
			bfa_fsm_send_event(ethport, ETHPORT_E_FWRESP_UP_FAIL);
		पूर्ण
		अवरोध;

	हाल BNA_STATUS_T_DISABLED:
		bfa_fsm_send_event(ethport, ETHPORT_E_FWRESP_DOWN);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम
bna_bfi_छोड़ो_set_rsp(काष्ठा bna_enet *enet, काष्ठा bfi_msgq_mhdr *msghdr)
अणु
	bfa_fsm_send_event(enet, ENET_E_FWRESP_PAUSE);
पूर्ण

अटल व्योम
bna_bfi_attr_get_rsp(काष्ठा bna_ioceth *ioceth,
			काष्ठा bfi_msgq_mhdr *msghdr)
अणु
	काष्ठा bfi_enet_attr_rsp *rsp =
		container_of(msghdr, काष्ठा bfi_enet_attr_rsp, mh);

	/**
	 * Store only अगर not set earlier, since BNAD can override the HW
	 * attributes
	 */
	अगर (!ioceth->attr.fw_query_complete) अणु
		ioceth->attr.num_txq = ntohl(rsp->max_cfg);
		ioceth->attr.num_rxp = ntohl(rsp->max_cfg);
		ioceth->attr.num_ucmac = ntohl(rsp->max_ucmac);
		ioceth->attr.num_mcmac = BFI_ENET_MAX_MCAM;
		ioceth->attr.max_rit_size = ntohl(rsp->rit_size);
		ioceth->attr.fw_query_complete = true;
	पूर्ण

	bfa_fsm_send_event(ioceth, IOCETH_E_ENET_ATTR_RESP);
पूर्ण

अटल व्योम
bna_bfi_stats_get_rsp(काष्ठा bna *bna, काष्ठा bfi_msgq_mhdr *msghdr)
अणु
	काष्ठा bfi_enet_stats_req *stats_req = &bna->stats_mod.stats_get;
	u64 *stats_src;
	u64 *stats_dst;
	u32 tx_enet_mask = ntohl(stats_req->tx_enet_mask);
	u32 rx_enet_mask = ntohl(stats_req->rx_enet_mask);
	पूर्णांक count;
	पूर्णांक i;

	bna_stats_copy(mac, mac);
	bna_stats_copy(bpc, bpc);
	bna_stats_copy(rad, rad);
	bna_stats_copy(rlb, rad);
	bna_stats_copy(fc_rx, fc_rx);
	bna_stats_copy(fc_tx, fc_tx);

	stats_src = (u64 *)&(bna->stats.hw_stats_kva->rxf_stats[0]);

	/* Copy Rxf stats to SW area, scatter them जबतक copying */
	क्रम (i = 0; i < BFI_ENET_CFG_MAX; i++) अणु
		stats_dst = (u64 *)&(bna->stats.hw_stats.rxf_stats[i]);
		स_रखो(stats_dst, 0, माप(काष्ठा bfi_enet_stats_rxf));
		अगर (rx_enet_mask & BIT(i)) अणु
			पूर्णांक k;
			count = माप(काष्ठा bfi_enet_stats_rxf) /
				माप(u64);
			क्रम (k = 0; k < count; k++) अणु
				stats_dst[k] = be64_to_cpu(*stats_src);
				stats_src++;
			पूर्ण
		पूर्ण
	पूर्ण

	/* Copy Txf stats to SW area, scatter them जबतक copying */
	क्रम (i = 0; i < BFI_ENET_CFG_MAX; i++) अणु
		stats_dst = (u64 *)&(bna->stats.hw_stats.txf_stats[i]);
		स_रखो(stats_dst, 0, माप(काष्ठा bfi_enet_stats_txf));
		अगर (tx_enet_mask & BIT(i)) अणु
			पूर्णांक k;
			count = माप(काष्ठा bfi_enet_stats_txf) /
				माप(u64);
			क्रम (k = 0; k < count; k++) अणु
				stats_dst[k] = be64_to_cpu(*stats_src);
				stats_src++;
			पूर्ण
		पूर्ण
	पूर्ण

	bna->stats_mod.stats_get_busy = false;
	bnad_cb_stats_get(bna->bnad, BNA_CB_SUCCESS, &bna->stats);
पूर्ण

अटल व्योम
bna_bfi_ethport_linkup_aen(काष्ठा bna_ethport *ethport,
			काष्ठा bfi_msgq_mhdr *msghdr)
अणु
	ethport->link_status = BNA_LINK_UP;

	/* Dispatch events */
	ethport->link_cbfn(ethport->bna->bnad, ethport->link_status);
पूर्ण

अटल व्योम
bna_bfi_ethport_linkकरोwn_aen(काष्ठा bna_ethport *ethport,
				काष्ठा bfi_msgq_mhdr *msghdr)
अणु
	ethport->link_status = BNA_LINK_DOWN;

	/* Dispatch events */
	ethport->link_cbfn(ethport->bna->bnad, BNA_LINK_DOWN);
पूर्ण

अटल व्योम
bna_err_handler(काष्ठा bna *bna, u32 पूर्णांकr_status)
अणु
	अगर (BNA_IS_HALT_INTR(bna, पूर्णांकr_status))
		bna_halt_clear(bna);

	bfa_nw_ioc_error_isr(&bna->ioceth.ioc);
पूर्ण

व्योम
bna_mbox_handler(काष्ठा bna *bna, u32 पूर्णांकr_status)
अणु
	अगर (BNA_IS_ERR_INTR(bna, पूर्णांकr_status)) अणु
		bna_err_handler(bna, पूर्णांकr_status);
		वापस;
	पूर्ण
	अगर (BNA_IS_MBOX_INTR(bna, पूर्णांकr_status))
		bfa_nw_ioc_mbox_isr(&bna->ioceth.ioc);
पूर्ण

अटल व्योम
bna_msgq_rsp_handler(व्योम *arg, काष्ठा bfi_msgq_mhdr *msghdr)
अणु
	काष्ठा bna *bna = (काष्ठा bna *)arg;
	काष्ठा bna_tx *tx;
	काष्ठा bna_rx *rx;

	चयन (msghdr->msg_id) अणु
	हाल BFI_ENET_I2H_RX_CFG_SET_RSP:
		bna_rx_from_rid(bna, msghdr->enet_id, rx);
		अगर (rx)
			bna_bfi_rx_enet_start_rsp(rx, msghdr);
		अवरोध;

	हाल BFI_ENET_I2H_RX_CFG_CLR_RSP:
		bna_rx_from_rid(bna, msghdr->enet_id, rx);
		अगर (rx)
			bna_bfi_rx_enet_stop_rsp(rx, msghdr);
		अवरोध;

	हाल BFI_ENET_I2H_RIT_CFG_RSP:
	हाल BFI_ENET_I2H_RSS_CFG_RSP:
	हाल BFI_ENET_I2H_RSS_ENABLE_RSP:
	हाल BFI_ENET_I2H_RX_PROMISCUOUS_RSP:
	हाल BFI_ENET_I2H_RX_DEFAULT_RSP:
	हाल BFI_ENET_I2H_MAC_UCAST_CLR_RSP:
	हाल BFI_ENET_I2H_MAC_UCAST_ADD_RSP:
	हाल BFI_ENET_I2H_MAC_UCAST_DEL_RSP:
	हाल BFI_ENET_I2H_MAC_MCAST_DEL_RSP:
	हाल BFI_ENET_I2H_MAC_MCAST_FILTER_RSP:
	हाल BFI_ENET_I2H_RX_VLAN_SET_RSP:
	हाल BFI_ENET_I2H_RX_VLAN_STRIP_ENABLE_RSP:
		bna_rx_from_rid(bna, msghdr->enet_id, rx);
		अगर (rx)
			bna_bfi_rxf_cfg_rsp(&rx->rxf, msghdr);
		अवरोध;

	हाल BFI_ENET_I2H_MAC_UCAST_SET_RSP:
		bna_rx_from_rid(bna, msghdr->enet_id, rx);
		अगर (rx)
			bna_bfi_rxf_ucast_set_rsp(&rx->rxf, msghdr);
		अवरोध;

	हाल BFI_ENET_I2H_MAC_MCAST_ADD_RSP:
		bna_rx_from_rid(bna, msghdr->enet_id, rx);
		अगर (rx)
			bna_bfi_rxf_mcast_add_rsp(&rx->rxf, msghdr);
		अवरोध;

	हाल BFI_ENET_I2H_TX_CFG_SET_RSP:
		bna_tx_from_rid(bna, msghdr->enet_id, tx);
		अगर (tx)
			bna_bfi_tx_enet_start_rsp(tx, msghdr);
		अवरोध;

	हाल BFI_ENET_I2H_TX_CFG_CLR_RSP:
		bna_tx_from_rid(bna, msghdr->enet_id, tx);
		अगर (tx)
			bna_bfi_tx_enet_stop_rsp(tx, msghdr);
		अवरोध;

	हाल BFI_ENET_I2H_PORT_ADMIN_RSP:
		bna_bfi_ethport_admin_rsp(&bna->ethport, msghdr);
		अवरोध;

	हाल BFI_ENET_I2H_DIAG_LOOPBACK_RSP:
		bna_bfi_ethport_lpbk_rsp(&bna->ethport, msghdr);
		अवरोध;

	हाल BFI_ENET_I2H_SET_PAUSE_RSP:
		bna_bfi_छोड़ो_set_rsp(&bna->enet, msghdr);
		अवरोध;

	हाल BFI_ENET_I2H_GET_ATTR_RSP:
		bna_bfi_attr_get_rsp(&bna->ioceth, msghdr);
		अवरोध;

	हाल BFI_ENET_I2H_STATS_GET_RSP:
		bna_bfi_stats_get_rsp(bna, msghdr);
		अवरोध;

	हाल BFI_ENET_I2H_STATS_CLR_RSP:
		/* No-op */
		अवरोध;

	हाल BFI_ENET_I2H_LINK_UP_AEN:
		bna_bfi_ethport_linkup_aen(&bna->ethport, msghdr);
		अवरोध;

	हाल BFI_ENET_I2H_LINK_DOWN_AEN:
		bna_bfi_ethport_linkकरोwn_aen(&bna->ethport, msghdr);
		अवरोध;

	हाल BFI_ENET_I2H_PORT_ENABLE_AEN:
		bna_bfi_ethport_enable_aen(&bna->ethport, msghdr);
		अवरोध;

	हाल BFI_ENET_I2H_PORT_DISABLE_AEN:
		bna_bfi_ethport_disable_aen(&bna->ethport, msghdr);
		अवरोध;

	हाल BFI_ENET_I2H_BW_UPDATE_AEN:
		bna_bfi_bw_update_aen(&bna->tx_mod);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण
पूर्ण

/* ETHPORT */

#घोषणा call_ethport_stop_cbfn(_ethport)				\
करो अणु									\
	अगर ((_ethport)->stop_cbfn) अणु					\
		व्योम (*cbfn)(काष्ठा bna_enet *);			\
		cbfn = (_ethport)->stop_cbfn;				\
		(_ethport)->stop_cbfn = शून्य;				\
		cbfn(&(_ethport)->bna->enet);				\
	पूर्ण								\
पूर्ण जबतक (0)

#घोषणा call_ethport_adminup_cbfn(ethport, status)			\
करो अणु									\
	अगर ((ethport)->adminup_cbfn) अणु					\
		व्योम (*cbfn)(काष्ठा bnad *, क्रमागत bna_cb_status);	\
		cbfn = (ethport)->adminup_cbfn;				\
		(ethport)->adminup_cbfn = शून्य;				\
		cbfn((ethport)->bna->bnad, status);			\
	पूर्ण								\
पूर्ण जबतक (0)

अटल व्योम
bna_bfi_ethport_admin_up(काष्ठा bna_ethport *ethport)
अणु
	काष्ठा bfi_enet_enable_req *admin_up_req =
		&ethport->bfi_enet_cmd.admin_req;

	bfi_msgq_mhdr_set(admin_up_req->mh, BFI_MC_ENET,
		BFI_ENET_H2I_PORT_ADMIN_UP_REQ, 0, 0);
	admin_up_req->mh.num_entries = htons(
		bfi_msgq_num_cmd_entries(माप(काष्ठा bfi_enet_enable_req)));
	admin_up_req->enable = BNA_STATUS_T_ENABLED;

	bfa_msgq_cmd_set(&ethport->msgq_cmd, शून्य, शून्य,
		माप(काष्ठा bfi_enet_enable_req), &admin_up_req->mh);
	bfa_msgq_cmd_post(&ethport->bna->msgq, &ethport->msgq_cmd);
पूर्ण

अटल व्योम
bna_bfi_ethport_admin_करोwn(काष्ठा bna_ethport *ethport)
अणु
	काष्ठा bfi_enet_enable_req *admin_करोwn_req =
		&ethport->bfi_enet_cmd.admin_req;

	bfi_msgq_mhdr_set(admin_करोwn_req->mh, BFI_MC_ENET,
		BFI_ENET_H2I_PORT_ADMIN_UP_REQ, 0, 0);
	admin_करोwn_req->mh.num_entries = htons(
		bfi_msgq_num_cmd_entries(माप(काष्ठा bfi_enet_enable_req)));
	admin_करोwn_req->enable = BNA_STATUS_T_DISABLED;

	bfa_msgq_cmd_set(&ethport->msgq_cmd, शून्य, शून्य,
		माप(काष्ठा bfi_enet_enable_req), &admin_करोwn_req->mh);
	bfa_msgq_cmd_post(&ethport->bna->msgq, &ethport->msgq_cmd);
पूर्ण

अटल व्योम
bna_bfi_ethport_lpbk_up(काष्ठा bna_ethport *ethport)
अणु
	काष्ठा bfi_enet_diag_lb_req *lpbk_up_req =
		&ethport->bfi_enet_cmd.lpbk_req;

	bfi_msgq_mhdr_set(lpbk_up_req->mh, BFI_MC_ENET,
		BFI_ENET_H2I_DIAG_LOOPBACK_REQ, 0, 0);
	lpbk_up_req->mh.num_entries = htons(
		bfi_msgq_num_cmd_entries(माप(काष्ठा bfi_enet_diag_lb_req)));
	lpbk_up_req->mode = (ethport->bna->enet.type ==
				BNA_ENET_T_LOOPBACK_INTERNAL) ?
				BFI_ENET_DIAG_LB_OPMODE_EXT :
				BFI_ENET_DIAG_LB_OPMODE_CBL;
	lpbk_up_req->enable = BNA_STATUS_T_ENABLED;

	bfa_msgq_cmd_set(&ethport->msgq_cmd, शून्य, शून्य,
		माप(काष्ठा bfi_enet_diag_lb_req), &lpbk_up_req->mh);
	bfa_msgq_cmd_post(&ethport->bna->msgq, &ethport->msgq_cmd);
पूर्ण

अटल व्योम
bna_bfi_ethport_lpbk_करोwn(काष्ठा bna_ethport *ethport)
अणु
	काष्ठा bfi_enet_diag_lb_req *lpbk_करोwn_req =
		&ethport->bfi_enet_cmd.lpbk_req;

	bfi_msgq_mhdr_set(lpbk_करोwn_req->mh, BFI_MC_ENET,
		BFI_ENET_H2I_DIAG_LOOPBACK_REQ, 0, 0);
	lpbk_करोwn_req->mh.num_entries = htons(
		bfi_msgq_num_cmd_entries(माप(काष्ठा bfi_enet_diag_lb_req)));
	lpbk_करोwn_req->enable = BNA_STATUS_T_DISABLED;

	bfa_msgq_cmd_set(&ethport->msgq_cmd, शून्य, शून्य,
		माप(काष्ठा bfi_enet_diag_lb_req), &lpbk_करोwn_req->mh);
	bfa_msgq_cmd_post(&ethport->bna->msgq, &ethport->msgq_cmd);
पूर्ण

अटल व्योम
bna_bfi_ethport_up(काष्ठा bna_ethport *ethport)
अणु
	अगर (ethport->bna->enet.type == BNA_ENET_T_REGULAR)
		bna_bfi_ethport_admin_up(ethport);
	अन्यथा
		bna_bfi_ethport_lpbk_up(ethport);
पूर्ण

अटल व्योम
bna_bfi_ethport_करोwn(काष्ठा bna_ethport *ethport)
अणु
	अगर (ethport->bna->enet.type == BNA_ENET_T_REGULAR)
		bna_bfi_ethport_admin_करोwn(ethport);
	अन्यथा
		bna_bfi_ethport_lpbk_करोwn(ethport);
पूर्ण

bfa_fsm_state_decl(bna_ethport, stopped, काष्ठा bna_ethport,
			क्रमागत bna_ethport_event);
bfa_fsm_state_decl(bna_ethport, करोwn, काष्ठा bna_ethport,
			क्रमागत bna_ethport_event);
bfa_fsm_state_decl(bna_ethport, up_resp_रुको, काष्ठा bna_ethport,
			क्रमागत bna_ethport_event);
bfa_fsm_state_decl(bna_ethport, करोwn_resp_रुको, काष्ठा bna_ethport,
			क्रमागत bna_ethport_event);
bfa_fsm_state_decl(bna_ethport, up, काष्ठा bna_ethport,
			क्रमागत bna_ethport_event);
bfa_fsm_state_decl(bna_ethport, last_resp_रुको, काष्ठा bna_ethport,
			क्रमागत bna_ethport_event);

अटल व्योम
bna_ethport_sm_stopped_entry(काष्ठा bna_ethport *ethport)
अणु
	call_ethport_stop_cbfn(ethport);
पूर्ण

अटल व्योम
bna_ethport_sm_stopped(काष्ठा bna_ethport *ethport,
			क्रमागत bna_ethport_event event)
अणु
	चयन (event) अणु
	हाल ETHPORT_E_START:
		bfa_fsm_set_state(ethport, bna_ethport_sm_करोwn);
		अवरोध;

	हाल ETHPORT_E_STOP:
		call_ethport_stop_cbfn(ethport);
		अवरोध;

	हाल ETHPORT_E_FAIL:
		/* No-op */
		अवरोध;

	हाल ETHPORT_E_DOWN:
		/* This event is received due to Rx objects failing */
		/* No-op */
		अवरोध;

	शेष:
		bfa_sm_fault(event);
	पूर्ण
पूर्ण

अटल व्योम
bna_ethport_sm_करोwn_entry(काष्ठा bna_ethport *ethport)
अणु
पूर्ण

अटल व्योम
bna_ethport_sm_करोwn(काष्ठा bna_ethport *ethport,
			क्रमागत bna_ethport_event event)
अणु
	चयन (event) अणु
	हाल ETHPORT_E_STOP:
		bfa_fsm_set_state(ethport, bna_ethport_sm_stopped);
		अवरोध;

	हाल ETHPORT_E_FAIL:
		bfa_fsm_set_state(ethport, bna_ethport_sm_stopped);
		अवरोध;

	हाल ETHPORT_E_UP:
		bfa_fsm_set_state(ethport, bna_ethport_sm_up_resp_रुको);
		bna_bfi_ethport_up(ethport);
		अवरोध;

	शेष:
		bfa_sm_fault(event);
	पूर्ण
पूर्ण

अटल व्योम
bna_ethport_sm_up_resp_रुको_entry(काष्ठा bna_ethport *ethport)
अणु
पूर्ण

अटल व्योम
bna_ethport_sm_up_resp_रुको(काष्ठा bna_ethport *ethport,
			क्रमागत bna_ethport_event event)
अणु
	चयन (event) अणु
	हाल ETHPORT_E_STOP:
		bfa_fsm_set_state(ethport, bna_ethport_sm_last_resp_रुको);
		अवरोध;

	हाल ETHPORT_E_FAIL:
		call_ethport_adminup_cbfn(ethport, BNA_CB_FAIL);
		bfa_fsm_set_state(ethport, bna_ethport_sm_stopped);
		अवरोध;

	हाल ETHPORT_E_DOWN:
		call_ethport_adminup_cbfn(ethport, BNA_CB_INTERRUPT);
		bfa_fsm_set_state(ethport, bna_ethport_sm_करोwn_resp_रुको);
		अवरोध;

	हाल ETHPORT_E_FWRESP_UP_OK:
		call_ethport_adminup_cbfn(ethport, BNA_CB_SUCCESS);
		bfa_fsm_set_state(ethport, bna_ethport_sm_up);
		अवरोध;

	हाल ETHPORT_E_FWRESP_UP_FAIL:
		call_ethport_adminup_cbfn(ethport, BNA_CB_FAIL);
		bfa_fsm_set_state(ethport, bna_ethport_sm_करोwn);
		अवरोध;

	हाल ETHPORT_E_FWRESP_DOWN:
		/* करोwn_resp_रुको -> up_resp_रुको transition on ETHPORT_E_UP */
		bna_bfi_ethport_up(ethport);
		अवरोध;

	शेष:
		bfa_sm_fault(event);
	पूर्ण
पूर्ण

अटल व्योम
bna_ethport_sm_करोwn_resp_रुको_entry(काष्ठा bna_ethport *ethport)
अणु
	/**
	 * NOTE: Do not call bna_bfi_ethport_करोwn() here. That will over step
	 * mbox due to up_resp_रुको -> करोwn_resp_रुको transition on event
	 * ETHPORT_E_DOWN
	 */
पूर्ण

अटल व्योम
bna_ethport_sm_करोwn_resp_रुको(काष्ठा bna_ethport *ethport,
			क्रमागत bna_ethport_event event)
अणु
	चयन (event) अणु
	हाल ETHPORT_E_STOP:
		bfa_fsm_set_state(ethport, bna_ethport_sm_last_resp_रुको);
		अवरोध;

	हाल ETHPORT_E_FAIL:
		bfa_fsm_set_state(ethport, bna_ethport_sm_stopped);
		अवरोध;

	हाल ETHPORT_E_UP:
		bfa_fsm_set_state(ethport, bna_ethport_sm_up_resp_रुको);
		अवरोध;

	हाल ETHPORT_E_FWRESP_UP_OK:
		/* up_resp_रुको->करोwn_resp_रुको transition on ETHPORT_E_DOWN */
		bna_bfi_ethport_करोwn(ethport);
		अवरोध;

	हाल ETHPORT_E_FWRESP_UP_FAIL:
	हाल ETHPORT_E_FWRESP_DOWN:
		bfa_fsm_set_state(ethport, bna_ethport_sm_करोwn);
		अवरोध;

	शेष:
		bfa_sm_fault(event);
	पूर्ण
पूर्ण

अटल व्योम
bna_ethport_sm_up_entry(काष्ठा bna_ethport *ethport)
अणु
पूर्ण

अटल व्योम
bna_ethport_sm_up(काष्ठा bna_ethport *ethport,
			क्रमागत bna_ethport_event event)
अणु
	चयन (event) अणु
	हाल ETHPORT_E_STOP:
		bfa_fsm_set_state(ethport, bna_ethport_sm_last_resp_रुको);
		bna_bfi_ethport_करोwn(ethport);
		अवरोध;

	हाल ETHPORT_E_FAIL:
		bfa_fsm_set_state(ethport, bna_ethport_sm_stopped);
		अवरोध;

	हाल ETHPORT_E_DOWN:
		bfa_fsm_set_state(ethport, bna_ethport_sm_करोwn_resp_रुको);
		bna_bfi_ethport_करोwn(ethport);
		अवरोध;

	शेष:
		bfa_sm_fault(event);
	पूर्ण
पूर्ण

अटल व्योम
bna_ethport_sm_last_resp_रुको_entry(काष्ठा bna_ethport *ethport)
अणु
पूर्ण

अटल व्योम
bna_ethport_sm_last_resp_रुको(काष्ठा bna_ethport *ethport,
			क्रमागत bna_ethport_event event)
अणु
	चयन (event) अणु
	हाल ETHPORT_E_FAIL:
		bfa_fsm_set_state(ethport, bna_ethport_sm_stopped);
		अवरोध;

	हाल ETHPORT_E_DOWN:
		/**
		 * This event is received due to Rx objects stopping in
		 * parallel to ethport
		 */
		/* No-op */
		अवरोध;

	हाल ETHPORT_E_FWRESP_UP_OK:
		/* up_resp_रुको->last_resp_रुको transition on ETHPORT_T_STOP */
		bna_bfi_ethport_करोwn(ethport);
		अवरोध;

	हाल ETHPORT_E_FWRESP_UP_FAIL:
	हाल ETHPORT_E_FWRESP_DOWN:
		bfa_fsm_set_state(ethport, bna_ethport_sm_stopped);
		अवरोध;

	शेष:
		bfa_sm_fault(event);
	पूर्ण
पूर्ण

अटल व्योम
bna_ethport_init(काष्ठा bna_ethport *ethport, काष्ठा bna *bna)
अणु
	ethport->flags |= (BNA_ETHPORT_F_ADMIN_UP | BNA_ETHPORT_F_PORT_ENABLED);
	ethport->bna = bna;

	ethport->link_status = BNA_LINK_DOWN;
	ethport->link_cbfn = bnad_cb_ethport_link_status;

	ethport->rx_started_count = 0;

	ethport->stop_cbfn = शून्य;
	ethport->adminup_cbfn = शून्य;

	bfa_fsm_set_state(ethport, bna_ethport_sm_stopped);
पूर्ण

अटल व्योम
bna_ethport_uninit(काष्ठा bna_ethport *ethport)
अणु
	ethport->flags &= ~BNA_ETHPORT_F_ADMIN_UP;
	ethport->flags &= ~BNA_ETHPORT_F_PORT_ENABLED;

	ethport->bna = शून्य;
पूर्ण

अटल व्योम
bna_ethport_start(काष्ठा bna_ethport *ethport)
अणु
	bfa_fsm_send_event(ethport, ETHPORT_E_START);
पूर्ण

अटल व्योम
bna_enet_cb_ethport_stopped(काष्ठा bna_enet *enet)
अणु
	bfa_wc_करोwn(&enet->chld_stop_wc);
पूर्ण

अटल व्योम
bna_ethport_stop(काष्ठा bna_ethport *ethport)
अणु
	ethport->stop_cbfn = bna_enet_cb_ethport_stopped;
	bfa_fsm_send_event(ethport, ETHPORT_E_STOP);
पूर्ण

अटल व्योम
bna_ethport_fail(काष्ठा bna_ethport *ethport)
अणु
	/* Reset the physical port status to enabled */
	ethport->flags |= BNA_ETHPORT_F_PORT_ENABLED;

	अगर (ethport->link_status != BNA_LINK_DOWN) अणु
		ethport->link_status = BNA_LINK_DOWN;
		ethport->link_cbfn(ethport->bna->bnad, BNA_LINK_DOWN);
	पूर्ण
	bfa_fsm_send_event(ethport, ETHPORT_E_FAIL);
पूर्ण

/* Should be called only when ethport is disabled */
व्योम
bna_ethport_cb_rx_started(काष्ठा bna_ethport *ethport)
अणु
	ethport->rx_started_count++;

	अगर (ethport->rx_started_count == 1) अणु
		ethport->flags |= BNA_ETHPORT_F_RX_STARTED;

		अगर (ethport_can_be_up(ethport))
			bfa_fsm_send_event(ethport, ETHPORT_E_UP);
	पूर्ण
पूर्ण

व्योम
bna_ethport_cb_rx_stopped(काष्ठा bna_ethport *ethport)
अणु
	पूर्णांक ethport_up = ethport_is_up(ethport);

	ethport->rx_started_count--;

	अगर (ethport->rx_started_count == 0) अणु
		ethport->flags &= ~BNA_ETHPORT_F_RX_STARTED;

		अगर (ethport_up)
			bfa_fsm_send_event(ethport, ETHPORT_E_DOWN);
	पूर्ण
पूर्ण

/* ENET */

#घोषणा bna_enet_chld_start(enet)					\
करो अणु									\
	क्रमागत bna_tx_type tx_type =					\
		((enet)->type == BNA_ENET_T_REGULAR) ?			\
		BNA_TX_T_REGULAR : BNA_TX_T_LOOPBACK;			\
	क्रमागत bna_rx_type rx_type =					\
		((enet)->type == BNA_ENET_T_REGULAR) ?			\
		BNA_RX_T_REGULAR : BNA_RX_T_LOOPBACK;			\
	bna_ethport_start(&(enet)->bna->ethport);			\
	bna_tx_mod_start(&(enet)->bna->tx_mod, tx_type);		\
	bna_rx_mod_start(&(enet)->bna->rx_mod, rx_type);		\
पूर्ण जबतक (0)

#घोषणा bna_enet_chld_stop(enet)					\
करो अणु									\
	क्रमागत bna_tx_type tx_type =					\
		((enet)->type == BNA_ENET_T_REGULAR) ?			\
		BNA_TX_T_REGULAR : BNA_TX_T_LOOPBACK;			\
	क्रमागत bna_rx_type rx_type =					\
		((enet)->type == BNA_ENET_T_REGULAR) ?			\
		BNA_RX_T_REGULAR : BNA_RX_T_LOOPBACK;			\
	bfa_wc_init(&(enet)->chld_stop_wc, bna_enet_cb_chld_stopped, (enet));\
	bfa_wc_up(&(enet)->chld_stop_wc);				\
	bna_ethport_stop(&(enet)->bna->ethport);			\
	bfa_wc_up(&(enet)->chld_stop_wc);				\
	bna_tx_mod_stop(&(enet)->bna->tx_mod, tx_type);			\
	bfa_wc_up(&(enet)->chld_stop_wc);				\
	bna_rx_mod_stop(&(enet)->bna->rx_mod, rx_type);			\
	bfa_wc_रुको(&(enet)->chld_stop_wc);				\
पूर्ण जबतक (0)

#घोषणा bna_enet_chld_fail(enet)					\
करो अणु									\
	bna_ethport_fail(&(enet)->bna->ethport);			\
	bna_tx_mod_fail(&(enet)->bna->tx_mod);				\
	bna_rx_mod_fail(&(enet)->bna->rx_mod);				\
पूर्ण जबतक (0)

#घोषणा bna_enet_rx_start(enet)						\
करो अणु									\
	क्रमागत bna_rx_type rx_type =					\
		((enet)->type == BNA_ENET_T_REGULAR) ?			\
		BNA_RX_T_REGULAR : BNA_RX_T_LOOPBACK;			\
	bna_rx_mod_start(&(enet)->bna->rx_mod, rx_type);		\
पूर्ण जबतक (0)

#घोषणा bna_enet_rx_stop(enet)						\
करो अणु									\
	क्रमागत bna_rx_type rx_type =					\
		((enet)->type == BNA_ENET_T_REGULAR) ?			\
		BNA_RX_T_REGULAR : BNA_RX_T_LOOPBACK;			\
	bfa_wc_init(&(enet)->chld_stop_wc, bna_enet_cb_chld_stopped, (enet));\
	bfa_wc_up(&(enet)->chld_stop_wc);				\
	bna_rx_mod_stop(&(enet)->bna->rx_mod, rx_type);			\
	bfa_wc_रुको(&(enet)->chld_stop_wc);				\
पूर्ण जबतक (0)

#घोषणा call_enet_stop_cbfn(enet)					\
करो अणु									\
	अगर ((enet)->stop_cbfn) अणु					\
		व्योम (*cbfn)(व्योम *);					\
		व्योम *cbarg;						\
		cbfn = (enet)->stop_cbfn;				\
		cbarg = (enet)->stop_cbarg;				\
		(enet)->stop_cbfn = शून्य;				\
		(enet)->stop_cbarg = शून्य;				\
		cbfn(cbarg);						\
	पूर्ण								\
पूर्ण जबतक (0)

#घोषणा call_enet_mtu_cbfn(enet)					\
करो अणु									\
	अगर ((enet)->mtu_cbfn) अणु						\
		व्योम (*cbfn)(काष्ठा bnad *);				\
		cbfn = (enet)->mtu_cbfn;				\
		(enet)->mtu_cbfn = शून्य;				\
		cbfn((enet)->bna->bnad);				\
	पूर्ण								\
पूर्ण जबतक (0)

अटल व्योम bna_enet_cb_chld_stopped(व्योम *arg);
अटल व्योम bna_bfi_छोड़ो_set(काष्ठा bna_enet *enet);

bfa_fsm_state_decl(bna_enet, stopped, काष्ठा bna_enet,
			क्रमागत bna_enet_event);
bfa_fsm_state_decl(bna_enet, छोड़ो_init_रुको, काष्ठा bna_enet,
			क्रमागत bna_enet_event);
bfa_fsm_state_decl(bna_enet, last_resp_रुको, काष्ठा bna_enet,
			क्रमागत bna_enet_event);
bfa_fsm_state_decl(bna_enet, started, काष्ठा bna_enet,
			क्रमागत bna_enet_event);
bfa_fsm_state_decl(bna_enet, cfg_रुको, काष्ठा bna_enet,
			क्रमागत bna_enet_event);
bfa_fsm_state_decl(bna_enet, cfg_stop_रुको, काष्ठा bna_enet,
			क्रमागत bna_enet_event);
bfa_fsm_state_decl(bna_enet, chld_stop_रुको, काष्ठा bna_enet,
			क्रमागत bna_enet_event);

अटल व्योम
bna_enet_sm_stopped_entry(काष्ठा bna_enet *enet)
अणु
	call_enet_mtu_cbfn(enet);
	call_enet_stop_cbfn(enet);
पूर्ण

अटल व्योम
bna_enet_sm_stopped(काष्ठा bna_enet *enet, क्रमागत bna_enet_event event)
अणु
	चयन (event) अणु
	हाल ENET_E_START:
		bfa_fsm_set_state(enet, bna_enet_sm_छोड़ो_init_रुको);
		अवरोध;

	हाल ENET_E_STOP:
		call_enet_stop_cbfn(enet);
		अवरोध;

	हाल ENET_E_FAIL:
		/* No-op */
		अवरोध;

	हाल ENET_E_PAUSE_CFG:
		अवरोध;

	हाल ENET_E_MTU_CFG:
		call_enet_mtu_cbfn(enet);
		अवरोध;

	हाल ENET_E_CHLD_STOPPED:
		/**
		 * This event is received due to Ethport, Tx and Rx objects
		 * failing
		 */
		/* No-op */
		अवरोध;

	शेष:
		bfa_sm_fault(event);
	पूर्ण
पूर्ण

अटल व्योम
bna_enet_sm_छोड़ो_init_रुको_entry(काष्ठा bna_enet *enet)
अणु
	bna_bfi_छोड़ो_set(enet);
पूर्ण

अटल व्योम
bna_enet_sm_छोड़ो_init_रुको(काष्ठा bna_enet *enet,
				क्रमागत bna_enet_event event)
अणु
	चयन (event) अणु
	हाल ENET_E_STOP:
		enet->flags &= ~BNA_ENET_F_PAUSE_CHANGED;
		bfa_fsm_set_state(enet, bna_enet_sm_last_resp_रुको);
		अवरोध;

	हाल ENET_E_FAIL:
		enet->flags &= ~BNA_ENET_F_PAUSE_CHANGED;
		bfa_fsm_set_state(enet, bna_enet_sm_stopped);
		अवरोध;

	हाल ENET_E_PAUSE_CFG:
		enet->flags |= BNA_ENET_F_PAUSE_CHANGED;
		अवरोध;

	हाल ENET_E_MTU_CFG:
		/* No-op */
		अवरोध;

	हाल ENET_E_FWRESP_PAUSE:
		अगर (enet->flags & BNA_ENET_F_PAUSE_CHANGED) अणु
			enet->flags &= ~BNA_ENET_F_PAUSE_CHANGED;
			bna_bfi_छोड़ो_set(enet);
		पूर्ण अन्यथा अणु
			bfa_fsm_set_state(enet, bna_enet_sm_started);
			bna_enet_chld_start(enet);
		पूर्ण
		अवरोध;

	शेष:
		bfa_sm_fault(event);
	पूर्ण
पूर्ण

अटल व्योम
bna_enet_sm_last_resp_रुको_entry(काष्ठा bna_enet *enet)
अणु
	enet->flags &= ~BNA_ENET_F_PAUSE_CHANGED;
पूर्ण

अटल व्योम
bna_enet_sm_last_resp_रुको(काष्ठा bna_enet *enet,
				क्रमागत bna_enet_event event)
अणु
	चयन (event) अणु
	हाल ENET_E_FAIL:
	हाल ENET_E_FWRESP_PAUSE:
		bfa_fsm_set_state(enet, bna_enet_sm_stopped);
		अवरोध;

	शेष:
		bfa_sm_fault(event);
	पूर्ण
पूर्ण

अटल व्योम
bna_enet_sm_started_entry(काष्ठा bna_enet *enet)
अणु
	/**
	 * NOTE: Do not call bna_enet_chld_start() here, since it will be
	 * inadvertently called during cfg_रुको->started transition as well
	 */
	call_enet_mtu_cbfn(enet);
पूर्ण

अटल व्योम
bna_enet_sm_started(काष्ठा bna_enet *enet,
			क्रमागत bna_enet_event event)
अणु
	चयन (event) अणु
	हाल ENET_E_STOP:
		bfa_fsm_set_state(enet, bna_enet_sm_chld_stop_रुको);
		अवरोध;

	हाल ENET_E_FAIL:
		bfa_fsm_set_state(enet, bna_enet_sm_stopped);
		bna_enet_chld_fail(enet);
		अवरोध;

	हाल ENET_E_PAUSE_CFG:
		bfa_fsm_set_state(enet, bna_enet_sm_cfg_रुको);
		bna_bfi_छोड़ो_set(enet);
		अवरोध;

	हाल ENET_E_MTU_CFG:
		bfa_fsm_set_state(enet, bna_enet_sm_cfg_रुको);
		bna_enet_rx_stop(enet);
		अवरोध;

	शेष:
		bfa_sm_fault(event);
	पूर्ण
पूर्ण

अटल व्योम
bna_enet_sm_cfg_रुको_entry(काष्ठा bna_enet *enet)
अणु
पूर्ण

अटल व्योम
bna_enet_sm_cfg_रुको(काष्ठा bna_enet *enet,
			क्रमागत bna_enet_event event)
अणु
	चयन (event) अणु
	हाल ENET_E_STOP:
		enet->flags &= ~BNA_ENET_F_PAUSE_CHANGED;
		enet->flags &= ~BNA_ENET_F_MTU_CHANGED;
		bfa_fsm_set_state(enet, bna_enet_sm_cfg_stop_रुको);
		अवरोध;

	हाल ENET_E_FAIL:
		enet->flags &= ~BNA_ENET_F_PAUSE_CHANGED;
		enet->flags &= ~BNA_ENET_F_MTU_CHANGED;
		bfa_fsm_set_state(enet, bna_enet_sm_stopped);
		bna_enet_chld_fail(enet);
		अवरोध;

	हाल ENET_E_PAUSE_CFG:
		enet->flags |= BNA_ENET_F_PAUSE_CHANGED;
		अवरोध;

	हाल ENET_E_MTU_CFG:
		enet->flags |= BNA_ENET_F_MTU_CHANGED;
		अवरोध;

	हाल ENET_E_CHLD_STOPPED:
		bna_enet_rx_start(enet);
		fallthrough;
	हाल ENET_E_FWRESP_PAUSE:
		अगर (enet->flags & BNA_ENET_F_PAUSE_CHANGED) अणु
			enet->flags &= ~BNA_ENET_F_PAUSE_CHANGED;
			bna_bfi_छोड़ो_set(enet);
		पूर्ण अन्यथा अगर (enet->flags & BNA_ENET_F_MTU_CHANGED) अणु
			enet->flags &= ~BNA_ENET_F_MTU_CHANGED;
			bna_enet_rx_stop(enet);
		पूर्ण अन्यथा अणु
			bfa_fsm_set_state(enet, bna_enet_sm_started);
		पूर्ण
		अवरोध;

	शेष:
		bfa_sm_fault(event);
	पूर्ण
पूर्ण

अटल व्योम
bna_enet_sm_cfg_stop_रुको_entry(काष्ठा bna_enet *enet)
अणु
	enet->flags &= ~BNA_ENET_F_PAUSE_CHANGED;
	enet->flags &= ~BNA_ENET_F_MTU_CHANGED;
पूर्ण

अटल व्योम
bna_enet_sm_cfg_stop_रुको(काष्ठा bna_enet *enet,
				क्रमागत bna_enet_event event)
अणु
	चयन (event) अणु
	हाल ENET_E_FAIL:
		bfa_fsm_set_state(enet, bna_enet_sm_stopped);
		bna_enet_chld_fail(enet);
		अवरोध;

	हाल ENET_E_FWRESP_PAUSE:
	हाल ENET_E_CHLD_STOPPED:
		bfa_fsm_set_state(enet, bna_enet_sm_chld_stop_रुको);
		अवरोध;

	शेष:
		bfa_sm_fault(event);
	पूर्ण
पूर्ण

अटल व्योम
bna_enet_sm_chld_stop_रुको_entry(काष्ठा bna_enet *enet)
अणु
	bna_enet_chld_stop(enet);
पूर्ण

अटल व्योम
bna_enet_sm_chld_stop_रुको(काष्ठा bna_enet *enet,
				क्रमागत bna_enet_event event)
अणु
	चयन (event) अणु
	हाल ENET_E_FAIL:
		bfa_fsm_set_state(enet, bna_enet_sm_stopped);
		bna_enet_chld_fail(enet);
		अवरोध;

	हाल ENET_E_CHLD_STOPPED:
		bfa_fsm_set_state(enet, bna_enet_sm_stopped);
		अवरोध;

	शेष:
		bfa_sm_fault(event);
	पूर्ण
पूर्ण

अटल व्योम
bna_bfi_छोड़ो_set(काष्ठा bna_enet *enet)
अणु
	काष्ठा bfi_enet_set_छोड़ो_req *छोड़ो_req = &enet->छोड़ो_req;

	bfi_msgq_mhdr_set(छोड़ो_req->mh, BFI_MC_ENET,
		BFI_ENET_H2I_SET_PAUSE_REQ, 0, 0);
	छोड़ो_req->mh.num_entries = htons(
	bfi_msgq_num_cmd_entries(माप(काष्ठा bfi_enet_set_छोड़ो_req)));
	छोड़ो_req->tx_छोड़ो = enet->छोड़ो_config.tx_छोड़ो;
	छोड़ो_req->rx_छोड़ो = enet->छोड़ो_config.rx_छोड़ो;

	bfa_msgq_cmd_set(&enet->msgq_cmd, शून्य, शून्य,
		माप(काष्ठा bfi_enet_set_छोड़ो_req), &छोड़ो_req->mh);
	bfa_msgq_cmd_post(&enet->bna->msgq, &enet->msgq_cmd);
पूर्ण

अटल व्योम
bna_enet_cb_chld_stopped(व्योम *arg)
अणु
	काष्ठा bna_enet *enet = (काष्ठा bna_enet *)arg;

	bfa_fsm_send_event(enet, ENET_E_CHLD_STOPPED);
पूर्ण

अटल व्योम
bna_enet_init(काष्ठा bna_enet *enet, काष्ठा bna *bna)
अणु
	enet->bna = bna;
	enet->flags = 0;
	enet->mtu = 0;
	enet->type = BNA_ENET_T_REGULAR;

	enet->stop_cbfn = शून्य;
	enet->stop_cbarg = शून्य;

	enet->mtu_cbfn = शून्य;

	bfa_fsm_set_state(enet, bna_enet_sm_stopped);
पूर्ण

अटल व्योम
bna_enet_uninit(काष्ठा bna_enet *enet)
अणु
	enet->flags = 0;

	enet->bna = शून्य;
पूर्ण

अटल व्योम
bna_enet_start(काष्ठा bna_enet *enet)
अणु
	enet->flags |= BNA_ENET_F_IOCETH_READY;
	अगर (enet->flags & BNA_ENET_F_ENABLED)
		bfa_fsm_send_event(enet, ENET_E_START);
पूर्ण

अटल व्योम
bna_ioceth_cb_enet_stopped(व्योम *arg)
अणु
	काष्ठा bna_ioceth *ioceth = (काष्ठा bna_ioceth *)arg;

	bfa_fsm_send_event(ioceth, IOCETH_E_ENET_STOPPED);
पूर्ण

अटल व्योम
bna_enet_stop(काष्ठा bna_enet *enet)
अणु
	enet->stop_cbfn = bna_ioceth_cb_enet_stopped;
	enet->stop_cbarg = &enet->bna->ioceth;

	enet->flags &= ~BNA_ENET_F_IOCETH_READY;
	bfa_fsm_send_event(enet, ENET_E_STOP);
पूर्ण

अटल व्योम
bna_enet_fail(काष्ठा bna_enet *enet)
अणु
	enet->flags &= ~BNA_ENET_F_IOCETH_READY;
	bfa_fsm_send_event(enet, ENET_E_FAIL);
पूर्ण

व्योम
bna_enet_cb_tx_stopped(काष्ठा bna_enet *enet)
अणु
	bfa_wc_करोwn(&enet->chld_stop_wc);
पूर्ण

व्योम
bna_enet_cb_rx_stopped(काष्ठा bna_enet *enet)
अणु
	bfa_wc_करोwn(&enet->chld_stop_wc);
पूर्ण

पूर्णांक
bna_enet_mtu_get(काष्ठा bna_enet *enet)
अणु
	वापस enet->mtu;
पूर्ण

व्योम
bna_enet_enable(काष्ठा bna_enet *enet)
अणु
	अगर (enet->fsm != (bfa_sm_t)bna_enet_sm_stopped)
		वापस;

	enet->flags |= BNA_ENET_F_ENABLED;

	अगर (enet->flags & BNA_ENET_F_IOCETH_READY)
		bfa_fsm_send_event(enet, ENET_E_START);
पूर्ण

व्योम
bna_enet_disable(काष्ठा bna_enet *enet, क्रमागत bna_cleanup_type type,
		 व्योम (*cbfn)(व्योम *))
अणु
	अगर (type == BNA_SOFT_CLEANUP) अणु
		(*cbfn)(enet->bna->bnad);
		वापस;
	पूर्ण

	enet->stop_cbfn = cbfn;
	enet->stop_cbarg = enet->bna->bnad;

	enet->flags &= ~BNA_ENET_F_ENABLED;

	bfa_fsm_send_event(enet, ENET_E_STOP);
पूर्ण

व्योम
bna_enet_छोड़ो_config(काष्ठा bna_enet *enet,
		      काष्ठा bna_छोड़ो_config *छोड़ो_config)
अणु
	enet->छोड़ो_config = *छोड़ो_config;

	bfa_fsm_send_event(enet, ENET_E_PAUSE_CFG);
पूर्ण

व्योम
bna_enet_mtu_set(काष्ठा bna_enet *enet, पूर्णांक mtu,
		 व्योम (*cbfn)(काष्ठा bnad *))
अणु
	enet->mtu = mtu;

	enet->mtu_cbfn = cbfn;

	bfa_fsm_send_event(enet, ENET_E_MTU_CFG);
पूर्ण

व्योम
bna_enet_perm_mac_get(काष्ठा bna_enet *enet, u8 *mac)
अणु
	bfa_nw_ioc_get_mac(&enet->bna->ioceth.ioc, mac);
पूर्ण

/* IOCETH */

#घोषणा enable_mbox_पूर्णांकr(_ioceth)					\
करो अणु									\
	u32 पूर्णांकr_status;						\
	bna_पूर्णांकr_status_get((_ioceth)->bna, पूर्णांकr_status);		\
	bnad_cb_mbox_पूर्णांकr_enable((_ioceth)->bna->bnad);			\
	bna_mbox_पूर्णांकr_enable((_ioceth)->bna);				\
पूर्ण जबतक (0)

#घोषणा disable_mbox_पूर्णांकr(_ioceth)					\
करो अणु									\
	bna_mbox_पूर्णांकr_disable((_ioceth)->bna);				\
	bnad_cb_mbox_पूर्णांकr_disable((_ioceth)->bna->bnad);		\
पूर्ण जबतक (0)

#घोषणा call_ioceth_stop_cbfn(_ioceth)					\
करो अणु									\
	अगर ((_ioceth)->stop_cbfn) अणु					\
		व्योम (*cbfn)(काष्ठा bnad *);				\
		काष्ठा bnad *cbarg;					\
		cbfn = (_ioceth)->stop_cbfn;				\
		cbarg = (_ioceth)->stop_cbarg;				\
		(_ioceth)->stop_cbfn = शून्य;				\
		(_ioceth)->stop_cbarg = शून्य;				\
		cbfn(cbarg);						\
	पूर्ण								\
पूर्ण जबतक (0)

#घोषणा bna_stats_mod_uninit(_stats_mod)				\
करो अणु									\
पूर्ण जबतक (0)

#घोषणा bna_stats_mod_start(_stats_mod)					\
करो अणु									\
	(_stats_mod)->ioc_पढ़ोy = true;					\
पूर्ण जबतक (0)

#घोषणा bna_stats_mod_stop(_stats_mod)					\
करो अणु									\
	(_stats_mod)->ioc_पढ़ोy = false;				\
पूर्ण जबतक (0)

#घोषणा bna_stats_mod_fail(_stats_mod)					\
करो अणु									\
	(_stats_mod)->ioc_पढ़ोy = false;				\
	(_stats_mod)->stats_get_busy = false;				\
	(_stats_mod)->stats_clr_busy = false;				\
पूर्ण जबतक (0)

अटल व्योम bna_bfi_attr_get(काष्ठा bna_ioceth *ioceth);

bfa_fsm_state_decl(bna_ioceth, stopped, काष्ठा bna_ioceth,
			क्रमागत bna_ioceth_event);
bfa_fsm_state_decl(bna_ioceth, ioc_पढ़ोy_रुको, काष्ठा bna_ioceth,
			क्रमागत bna_ioceth_event);
bfa_fsm_state_decl(bna_ioceth, enet_attr_रुको, काष्ठा bna_ioceth,
			क्रमागत bna_ioceth_event);
bfa_fsm_state_decl(bna_ioceth, पढ़ोy, काष्ठा bna_ioceth,
			क्रमागत bna_ioceth_event);
bfa_fsm_state_decl(bna_ioceth, last_resp_रुको, काष्ठा bna_ioceth,
			क्रमागत bna_ioceth_event);
bfa_fsm_state_decl(bna_ioceth, enet_stop_रुको, काष्ठा bna_ioceth,
			क्रमागत bna_ioceth_event);
bfa_fsm_state_decl(bna_ioceth, ioc_disable_रुको, काष्ठा bna_ioceth,
			क्रमागत bna_ioceth_event);
bfa_fsm_state_decl(bna_ioceth, failed, काष्ठा bna_ioceth,
			क्रमागत bna_ioceth_event);

अटल व्योम
bna_ioceth_sm_stopped_entry(काष्ठा bna_ioceth *ioceth)
अणु
	call_ioceth_stop_cbfn(ioceth);
पूर्ण

अटल व्योम
bna_ioceth_sm_stopped(काष्ठा bna_ioceth *ioceth,
			क्रमागत bna_ioceth_event event)
अणु
	चयन (event) अणु
	हाल IOCETH_E_ENABLE:
		bfa_fsm_set_state(ioceth, bna_ioceth_sm_ioc_पढ़ोy_रुको);
		bfa_nw_ioc_enable(&ioceth->ioc);
		अवरोध;

	हाल IOCETH_E_DISABLE:
		bfa_fsm_set_state(ioceth, bna_ioceth_sm_stopped);
		अवरोध;

	हाल IOCETH_E_IOC_RESET:
		enable_mbox_पूर्णांकr(ioceth);
		अवरोध;

	हाल IOCETH_E_IOC_FAILED:
		disable_mbox_पूर्णांकr(ioceth);
		bfa_fsm_set_state(ioceth, bna_ioceth_sm_failed);
		अवरोध;

	शेष:
		bfa_sm_fault(event);
	पूर्ण
पूर्ण

अटल व्योम
bna_ioceth_sm_ioc_पढ़ोy_रुको_entry(काष्ठा bna_ioceth *ioceth)
अणु
	/**
	 * Do not call bfa_nw_ioc_enable() here. It must be called in the
	 * previous state due to failed -> ioc_पढ़ोy_रुको transition.
	 */
पूर्ण

अटल व्योम
bna_ioceth_sm_ioc_पढ़ोy_रुको(काष्ठा bna_ioceth *ioceth,
				क्रमागत bna_ioceth_event event)
अणु
	चयन (event) अणु
	हाल IOCETH_E_DISABLE:
		bfa_fsm_set_state(ioceth, bna_ioceth_sm_ioc_disable_रुको);
		bfa_nw_ioc_disable(&ioceth->ioc);
		अवरोध;

	हाल IOCETH_E_IOC_RESET:
		enable_mbox_पूर्णांकr(ioceth);
		अवरोध;

	हाल IOCETH_E_IOC_FAILED:
		disable_mbox_पूर्णांकr(ioceth);
		bfa_fsm_set_state(ioceth, bna_ioceth_sm_failed);
		अवरोध;

	हाल IOCETH_E_IOC_READY:
		bfa_fsm_set_state(ioceth, bna_ioceth_sm_enet_attr_रुको);
		अवरोध;

	शेष:
		bfa_sm_fault(event);
	पूर्ण
पूर्ण

अटल व्योम
bna_ioceth_sm_enet_attr_रुको_entry(काष्ठा bna_ioceth *ioceth)
अणु
	bna_bfi_attr_get(ioceth);
पूर्ण

अटल व्योम
bna_ioceth_sm_enet_attr_रुको(काष्ठा bna_ioceth *ioceth,
				क्रमागत bna_ioceth_event event)
अणु
	चयन (event) अणु
	हाल IOCETH_E_DISABLE:
		bfa_fsm_set_state(ioceth, bna_ioceth_sm_last_resp_रुको);
		अवरोध;

	हाल IOCETH_E_IOC_FAILED:
		disable_mbox_पूर्णांकr(ioceth);
		bfa_fsm_set_state(ioceth, bna_ioceth_sm_failed);
		अवरोध;

	हाल IOCETH_E_ENET_ATTR_RESP:
		bfa_fsm_set_state(ioceth, bna_ioceth_sm_पढ़ोy);
		अवरोध;

	शेष:
		bfa_sm_fault(event);
	पूर्ण
पूर्ण

अटल व्योम
bna_ioceth_sm_पढ़ोy_entry(काष्ठा bna_ioceth *ioceth)
अणु
	bna_enet_start(&ioceth->bna->enet);
	bna_stats_mod_start(&ioceth->bna->stats_mod);
	bnad_cb_ioceth_पढ़ोy(ioceth->bna->bnad);
पूर्ण

अटल व्योम
bna_ioceth_sm_पढ़ोy(काष्ठा bna_ioceth *ioceth, क्रमागत bna_ioceth_event event)
अणु
	चयन (event) अणु
	हाल IOCETH_E_DISABLE:
		bfa_fsm_set_state(ioceth, bna_ioceth_sm_enet_stop_रुको);
		अवरोध;

	हाल IOCETH_E_IOC_FAILED:
		disable_mbox_पूर्णांकr(ioceth);
		bna_enet_fail(&ioceth->bna->enet);
		bna_stats_mod_fail(&ioceth->bna->stats_mod);
		bfa_fsm_set_state(ioceth, bna_ioceth_sm_failed);
		अवरोध;

	शेष:
		bfa_sm_fault(event);
	पूर्ण
पूर्ण

अटल व्योम
bna_ioceth_sm_last_resp_रुको_entry(काष्ठा bna_ioceth *ioceth)
अणु
पूर्ण

अटल व्योम
bna_ioceth_sm_last_resp_रुको(काष्ठा bna_ioceth *ioceth,
				क्रमागत bna_ioceth_event event)
अणु
	चयन (event) अणु
	हाल IOCETH_E_IOC_FAILED:
		bfa_fsm_set_state(ioceth, bna_ioceth_sm_ioc_disable_रुको);
		disable_mbox_पूर्णांकr(ioceth);
		bfa_nw_ioc_disable(&ioceth->ioc);
		अवरोध;

	हाल IOCETH_E_ENET_ATTR_RESP:
		bfa_fsm_set_state(ioceth, bna_ioceth_sm_ioc_disable_रुको);
		bfa_nw_ioc_disable(&ioceth->ioc);
		अवरोध;

	शेष:
		bfa_sm_fault(event);
	पूर्ण
पूर्ण

अटल व्योम
bna_ioceth_sm_enet_stop_रुको_entry(काष्ठा bna_ioceth *ioceth)
अणु
	bna_stats_mod_stop(&ioceth->bna->stats_mod);
	bna_enet_stop(&ioceth->bna->enet);
पूर्ण

अटल व्योम
bna_ioceth_sm_enet_stop_रुको(काष्ठा bna_ioceth *ioceth,
				क्रमागत bna_ioceth_event event)
अणु
	चयन (event) अणु
	हाल IOCETH_E_IOC_FAILED:
		bfa_fsm_set_state(ioceth, bna_ioceth_sm_ioc_disable_रुको);
		disable_mbox_पूर्णांकr(ioceth);
		bna_enet_fail(&ioceth->bna->enet);
		bna_stats_mod_fail(&ioceth->bna->stats_mod);
		bfa_nw_ioc_disable(&ioceth->ioc);
		अवरोध;

	हाल IOCETH_E_ENET_STOPPED:
		bfa_fsm_set_state(ioceth, bna_ioceth_sm_ioc_disable_रुको);
		bfa_nw_ioc_disable(&ioceth->ioc);
		अवरोध;

	शेष:
		bfa_sm_fault(event);
	पूर्ण
पूर्ण

अटल व्योम
bna_ioceth_sm_ioc_disable_रुको_entry(काष्ठा bna_ioceth *ioceth)
अणु
पूर्ण

अटल व्योम
bna_ioceth_sm_ioc_disable_रुको(काष्ठा bna_ioceth *ioceth,
				क्रमागत bna_ioceth_event event)
अणु
	चयन (event) अणु
	हाल IOCETH_E_IOC_DISABLED:
		disable_mbox_पूर्णांकr(ioceth);
		bfa_fsm_set_state(ioceth, bna_ioceth_sm_stopped);
		अवरोध;

	हाल IOCETH_E_ENET_STOPPED:
		/* This event is received due to enet failing */
		/* No-op */
		अवरोध;

	शेष:
		bfa_sm_fault(event);
	पूर्ण
पूर्ण

अटल व्योम
bna_ioceth_sm_failed_entry(काष्ठा bna_ioceth *ioceth)
अणु
	bnad_cb_ioceth_failed(ioceth->bna->bnad);
पूर्ण

अटल व्योम
bna_ioceth_sm_failed(काष्ठा bna_ioceth *ioceth,
			क्रमागत bna_ioceth_event event)
अणु
	चयन (event) अणु
	हाल IOCETH_E_DISABLE:
		bfa_fsm_set_state(ioceth, bna_ioceth_sm_ioc_disable_रुको);
		bfa_nw_ioc_disable(&ioceth->ioc);
		अवरोध;

	हाल IOCETH_E_IOC_RESET:
		enable_mbox_पूर्णांकr(ioceth);
		bfa_fsm_set_state(ioceth, bna_ioceth_sm_ioc_पढ़ोy_रुको);
		अवरोध;

	हाल IOCETH_E_IOC_FAILED:
		अवरोध;

	शेष:
		bfa_sm_fault(event);
	पूर्ण
पूर्ण

अटल व्योम
bna_bfi_attr_get(काष्ठा bna_ioceth *ioceth)
अणु
	काष्ठा bfi_enet_attr_req *attr_req = &ioceth->attr_req;

	bfi_msgq_mhdr_set(attr_req->mh, BFI_MC_ENET,
		BFI_ENET_H2I_GET_ATTR_REQ, 0, 0);
	attr_req->mh.num_entries = htons(
	bfi_msgq_num_cmd_entries(माप(काष्ठा bfi_enet_attr_req)));
	bfa_msgq_cmd_set(&ioceth->msgq_cmd, शून्य, शून्य,
		माप(काष्ठा bfi_enet_attr_req), &attr_req->mh);
	bfa_msgq_cmd_post(&ioceth->bna->msgq, &ioceth->msgq_cmd);
पूर्ण

/* IOC callback functions */

अटल व्योम
bna_cb_ioceth_enable(व्योम *arg, क्रमागत bfa_status error)
अणु
	काष्ठा bna_ioceth *ioceth = (काष्ठा bna_ioceth *)arg;

	अगर (error)
		bfa_fsm_send_event(ioceth, IOCETH_E_IOC_FAILED);
	अन्यथा
		bfa_fsm_send_event(ioceth, IOCETH_E_IOC_READY);
पूर्ण

अटल व्योम
bna_cb_ioceth_disable(व्योम *arg)
अणु
	काष्ठा bna_ioceth *ioceth = (काष्ठा bna_ioceth *)arg;

	bfa_fsm_send_event(ioceth, IOCETH_E_IOC_DISABLED);
पूर्ण

अटल व्योम
bna_cb_ioceth_hbfail(व्योम *arg)
अणु
	काष्ठा bna_ioceth *ioceth = (काष्ठा bna_ioceth *)arg;

	bfa_fsm_send_event(ioceth, IOCETH_E_IOC_FAILED);
पूर्ण

अटल व्योम
bna_cb_ioceth_reset(व्योम *arg)
अणु
	काष्ठा bna_ioceth *ioceth = (काष्ठा bna_ioceth *)arg;

	bfa_fsm_send_event(ioceth, IOCETH_E_IOC_RESET);
पूर्ण

अटल काष्ठा bfa_ioc_cbfn bna_ioceth_cbfn = अणु
	.enable_cbfn = bna_cb_ioceth_enable,
	.disable_cbfn = bna_cb_ioceth_disable,
	.hbfail_cbfn = bna_cb_ioceth_hbfail,
	.reset_cbfn = bna_cb_ioceth_reset
पूर्ण;

अटल व्योम bna_attr_init(काष्ठा bna_ioceth *ioceth)
अणु
	ioceth->attr.num_txq = BFI_ENET_DEF_TXQ;
	ioceth->attr.num_rxp = BFI_ENET_DEF_RXP;
	ioceth->attr.num_ucmac = BFI_ENET_DEF_UCAM;
	ioceth->attr.num_mcmac = BFI_ENET_MAX_MCAM;
	ioceth->attr.max_rit_size = BFI_ENET_DEF_RITSZ;
	ioceth->attr.fw_query_complete = false;
पूर्ण

अटल व्योम
bna_ioceth_init(काष्ठा bna_ioceth *ioceth, काष्ठा bna *bna,
		काष्ठा bna_res_info *res_info)
अणु
	u64 dma;
	u8 *kva;

	ioceth->bna = bna;

	/**
	 * Attach IOC and claim:
	 *	1. DMA memory क्रम IOC attributes
	 *	2. Kernel memory क्रम FW trace
	 */
	bfa_nw_ioc_attach(&ioceth->ioc, ioceth, &bna_ioceth_cbfn);
	bfa_nw_ioc_pci_init(&ioceth->ioc, &bna->pcidev, BFI_PCIFN_CLASS_ETH);

	BNA_GET_DMA_ADDR(
		&res_info[BNA_RES_MEM_T_ATTR].res_u.mem_info.mdl[0].dma, dma);
	kva = res_info[BNA_RES_MEM_T_ATTR].res_u.mem_info.mdl[0].kva;
	bfa_nw_ioc_mem_claim(&ioceth->ioc, kva, dma);

	kva = res_info[BNA_RES_MEM_T_FWTRC].res_u.mem_info.mdl[0].kva;
	bfa_nw_ioc_debug_memclaim(&ioceth->ioc, kva);

	/**
	 * Attach common modules (Diag, SFP, CEE, Port) and claim respective
	 * DMA memory.
	 */
	BNA_GET_DMA_ADDR(
		&res_info[BNA_RES_MEM_T_COM].res_u.mem_info.mdl[0].dma, dma);
	kva = res_info[BNA_RES_MEM_T_COM].res_u.mem_info.mdl[0].kva;
	bfa_nw_cee_attach(&bna->cee, &ioceth->ioc, bna);
	bfa_nw_cee_mem_claim(&bna->cee, kva, dma);
	kva += bfa_nw_cee_meminfo();
	dma += bfa_nw_cee_meminfo();

	bfa_nw_flash_attach(&bna->flash, &ioceth->ioc, bna);
	bfa_nw_flash_memclaim(&bna->flash, kva, dma);
	kva += bfa_nw_flash_meminfo();
	dma += bfa_nw_flash_meminfo();

	bfa_msgq_attach(&bna->msgq, &ioceth->ioc);
	bfa_msgq_memclaim(&bna->msgq, kva, dma);
	bfa_msgq_regisr(&bna->msgq, BFI_MC_ENET, bna_msgq_rsp_handler, bna);
	kva += bfa_msgq_meminfo();
	dma += bfa_msgq_meminfo();

	ioceth->stop_cbfn = शून्य;
	ioceth->stop_cbarg = शून्य;

	bna_attr_init(ioceth);

	bfa_fsm_set_state(ioceth, bna_ioceth_sm_stopped);
पूर्ण

अटल व्योम
bna_ioceth_uninit(काष्ठा bna_ioceth *ioceth)
अणु
	bfa_nw_ioc_detach(&ioceth->ioc);

	ioceth->bna = शून्य;
पूर्ण

व्योम
bna_ioceth_enable(काष्ठा bna_ioceth *ioceth)
अणु
	अगर (ioceth->fsm == (bfa_fsm_t)bna_ioceth_sm_पढ़ोy) अणु
		bnad_cb_ioceth_पढ़ोy(ioceth->bna->bnad);
		वापस;
	पूर्ण

	अगर (ioceth->fsm == (bfa_fsm_t)bna_ioceth_sm_stopped)
		bfa_fsm_send_event(ioceth, IOCETH_E_ENABLE);
पूर्ण

व्योम
bna_ioceth_disable(काष्ठा bna_ioceth *ioceth, क्रमागत bna_cleanup_type type)
अणु
	अगर (type == BNA_SOFT_CLEANUP) अणु
		bnad_cb_ioceth_disabled(ioceth->bna->bnad);
		वापस;
	पूर्ण

	ioceth->stop_cbfn = bnad_cb_ioceth_disabled;
	ioceth->stop_cbarg = ioceth->bna->bnad;

	bfa_fsm_send_event(ioceth, IOCETH_E_DISABLE);
पूर्ण

अटल व्योम
bna_ucam_mod_init(काष्ठा bna_ucam_mod *ucam_mod, काष्ठा bna *bna,
		  काष्ठा bna_res_info *res_info)
अणु
	पूर्णांक i;

	ucam_mod->ucmac = (काष्ठा bna_mac *)
	res_info[BNA_MOD_RES_MEM_T_UCMAC_ARRAY].res_u.mem_info.mdl[0].kva;

	INIT_LIST_HEAD(&ucam_mod->मुक्त_q);
	क्रम (i = 0; i < bna->ioceth.attr.num_ucmac; i++)
		list_add_tail(&ucam_mod->ucmac[i].qe, &ucam_mod->मुक्त_q);

	/* A separate queue to allow synchronous setting of a list of MACs */
	INIT_LIST_HEAD(&ucam_mod->del_q);
	क्रम (; i < (bna->ioceth.attr.num_ucmac * 2); i++)
		list_add_tail(&ucam_mod->ucmac[i].qe, &ucam_mod->del_q);

	ucam_mod->bna = bna;
पूर्ण

अटल व्योम
bna_ucam_mod_uninit(काष्ठा bna_ucam_mod *ucam_mod)
अणु
	ucam_mod->bna = शून्य;
पूर्ण

अटल व्योम
bna_mcam_mod_init(काष्ठा bna_mcam_mod *mcam_mod, काष्ठा bna *bna,
		  काष्ठा bna_res_info *res_info)
अणु
	पूर्णांक i;

	mcam_mod->mcmac = (काष्ठा bna_mac *)
	res_info[BNA_MOD_RES_MEM_T_MCMAC_ARRAY].res_u.mem_info.mdl[0].kva;

	INIT_LIST_HEAD(&mcam_mod->मुक्त_q);
	क्रम (i = 0; i < bna->ioceth.attr.num_mcmac; i++)
		list_add_tail(&mcam_mod->mcmac[i].qe, &mcam_mod->मुक्त_q);

	mcam_mod->mchandle = (काष्ठा bna_mcam_handle *)
	res_info[BNA_MOD_RES_MEM_T_MCHANDLE_ARRAY].res_u.mem_info.mdl[0].kva;

	INIT_LIST_HEAD(&mcam_mod->मुक्त_handle_q);
	क्रम (i = 0; i < bna->ioceth.attr.num_mcmac; i++)
		list_add_tail(&mcam_mod->mchandle[i].qe,
			      &mcam_mod->मुक्त_handle_q);

	/* A separate queue to allow synchronous setting of a list of MACs */
	INIT_LIST_HEAD(&mcam_mod->del_q);
	क्रम (; i < (bna->ioceth.attr.num_mcmac * 2); i++)
		list_add_tail(&mcam_mod->mcmac[i].qe, &mcam_mod->del_q);

	mcam_mod->bna = bna;
पूर्ण

अटल व्योम
bna_mcam_mod_uninit(काष्ठा bna_mcam_mod *mcam_mod)
अणु
	mcam_mod->bna = शून्य;
पूर्ण

अटल व्योम
bna_bfi_stats_get(काष्ठा bna *bna)
अणु
	काष्ठा bfi_enet_stats_req *stats_req = &bna->stats_mod.stats_get;

	bna->stats_mod.stats_get_busy = true;

	bfi_msgq_mhdr_set(stats_req->mh, BFI_MC_ENET,
		BFI_ENET_H2I_STATS_GET_REQ, 0, 0);
	stats_req->mh.num_entries = htons(
		bfi_msgq_num_cmd_entries(माप(काष्ठा bfi_enet_stats_req)));
	stats_req->stats_mask = htons(BFI_ENET_STATS_ALL);
	stats_req->tx_enet_mask = htonl(bna->tx_mod.rid_mask);
	stats_req->rx_enet_mask = htonl(bna->rx_mod.rid_mask);
	stats_req->host_buffer.a32.addr_hi = bna->stats.hw_stats_dma.msb;
	stats_req->host_buffer.a32.addr_lo = bna->stats.hw_stats_dma.lsb;

	bfa_msgq_cmd_set(&bna->stats_mod.stats_get_cmd, शून्य, शून्य,
		माप(काष्ठा bfi_enet_stats_req), &stats_req->mh);
	bfa_msgq_cmd_post(&bna->msgq, &bna->stats_mod.stats_get_cmd);
पूर्ण

व्योम
bna_res_req(काष्ठा bna_res_info *res_info)
अणु
	/* DMA memory क्रम COMMON_MODULE */
	res_info[BNA_RES_MEM_T_COM].res_type = BNA_RES_T_MEM;
	res_info[BNA_RES_MEM_T_COM].res_u.mem_info.mem_type = BNA_MEM_T_DMA;
	res_info[BNA_RES_MEM_T_COM].res_u.mem_info.num = 1;
	res_info[BNA_RES_MEM_T_COM].res_u.mem_info.len = ALIGN(
				(bfa_nw_cee_meminfo() +
				 bfa_nw_flash_meminfo() +
				 bfa_msgq_meminfo()), PAGE_SIZE);

	/* DMA memory क्रम retrieving IOC attributes */
	res_info[BNA_RES_MEM_T_ATTR].res_type = BNA_RES_T_MEM;
	res_info[BNA_RES_MEM_T_ATTR].res_u.mem_info.mem_type = BNA_MEM_T_DMA;
	res_info[BNA_RES_MEM_T_ATTR].res_u.mem_info.num = 1;
	res_info[BNA_RES_MEM_T_ATTR].res_u.mem_info.len =
				ALIGN(bfa_nw_ioc_meminfo(), PAGE_SIZE);

	/* Virtual memory क्रम retreiving fw_trc */
	res_info[BNA_RES_MEM_T_FWTRC].res_type = BNA_RES_T_MEM;
	res_info[BNA_RES_MEM_T_FWTRC].res_u.mem_info.mem_type = BNA_MEM_T_KVA;
	res_info[BNA_RES_MEM_T_FWTRC].res_u.mem_info.num = 1;
	res_info[BNA_RES_MEM_T_FWTRC].res_u.mem_info.len = BNA_DBG_FWTRC_LEN;

	/* DMA memory क्रम retreiving stats */
	res_info[BNA_RES_MEM_T_STATS].res_type = BNA_RES_T_MEM;
	res_info[BNA_RES_MEM_T_STATS].res_u.mem_info.mem_type = BNA_MEM_T_DMA;
	res_info[BNA_RES_MEM_T_STATS].res_u.mem_info.num = 1;
	res_info[BNA_RES_MEM_T_STATS].res_u.mem_info.len =
				ALIGN(माप(काष्ठा bfi_enet_stats),
					PAGE_SIZE);
पूर्ण

व्योम
bna_mod_res_req(काष्ठा bna *bna, काष्ठा bna_res_info *res_info)
अणु
	काष्ठा bna_attr *attr = &bna->ioceth.attr;

	/* Virtual memory क्रम Tx objects - stored by Tx module */
	res_info[BNA_MOD_RES_MEM_T_TX_ARRAY].res_type = BNA_RES_T_MEM;
	res_info[BNA_MOD_RES_MEM_T_TX_ARRAY].res_u.mem_info.mem_type =
		BNA_MEM_T_KVA;
	res_info[BNA_MOD_RES_MEM_T_TX_ARRAY].res_u.mem_info.num = 1;
	res_info[BNA_MOD_RES_MEM_T_TX_ARRAY].res_u.mem_info.len =
		attr->num_txq * माप(काष्ठा bna_tx);

	/* Virtual memory क्रम TxQ - stored by Tx module */
	res_info[BNA_MOD_RES_MEM_T_TXQ_ARRAY].res_type = BNA_RES_T_MEM;
	res_info[BNA_MOD_RES_MEM_T_TXQ_ARRAY].res_u.mem_info.mem_type =
		BNA_MEM_T_KVA;
	res_info[BNA_MOD_RES_MEM_T_TXQ_ARRAY].res_u.mem_info.num = 1;
	res_info[BNA_MOD_RES_MEM_T_TXQ_ARRAY].res_u.mem_info.len =
		attr->num_txq * माप(काष्ठा bna_txq);

	/* Virtual memory क्रम Rx objects - stored by Rx module */
	res_info[BNA_MOD_RES_MEM_T_RX_ARRAY].res_type = BNA_RES_T_MEM;
	res_info[BNA_MOD_RES_MEM_T_RX_ARRAY].res_u.mem_info.mem_type =
		BNA_MEM_T_KVA;
	res_info[BNA_MOD_RES_MEM_T_RX_ARRAY].res_u.mem_info.num = 1;
	res_info[BNA_MOD_RES_MEM_T_RX_ARRAY].res_u.mem_info.len =
		attr->num_rxp * माप(काष्ठा bna_rx);

	/* Virtual memory क्रम RxPath - stored by Rx module */
	res_info[BNA_MOD_RES_MEM_T_RXP_ARRAY].res_type = BNA_RES_T_MEM;
	res_info[BNA_MOD_RES_MEM_T_RXP_ARRAY].res_u.mem_info.mem_type =
		BNA_MEM_T_KVA;
	res_info[BNA_MOD_RES_MEM_T_RXP_ARRAY].res_u.mem_info.num = 1;
	res_info[BNA_MOD_RES_MEM_T_RXP_ARRAY].res_u.mem_info.len =
		attr->num_rxp * माप(काष्ठा bna_rxp);

	/* Virtual memory क्रम RxQ - stored by Rx module */
	res_info[BNA_MOD_RES_MEM_T_RXQ_ARRAY].res_type = BNA_RES_T_MEM;
	res_info[BNA_MOD_RES_MEM_T_RXQ_ARRAY].res_u.mem_info.mem_type =
		BNA_MEM_T_KVA;
	res_info[BNA_MOD_RES_MEM_T_RXQ_ARRAY].res_u.mem_info.num = 1;
	res_info[BNA_MOD_RES_MEM_T_RXQ_ARRAY].res_u.mem_info.len =
		(attr->num_rxp * 2) * माप(काष्ठा bna_rxq);

	/* Virtual memory क्रम Unicast MAC address - stored by ucam module */
	res_info[BNA_MOD_RES_MEM_T_UCMAC_ARRAY].res_type = BNA_RES_T_MEM;
	res_info[BNA_MOD_RES_MEM_T_UCMAC_ARRAY].res_u.mem_info.mem_type =
		BNA_MEM_T_KVA;
	res_info[BNA_MOD_RES_MEM_T_UCMAC_ARRAY].res_u.mem_info.num = 1;
	res_info[BNA_MOD_RES_MEM_T_UCMAC_ARRAY].res_u.mem_info.len =
		(attr->num_ucmac * 2) * माप(काष्ठा bna_mac);

	/* Virtual memory क्रम Multicast MAC address - stored by mcam module */
	res_info[BNA_MOD_RES_MEM_T_MCMAC_ARRAY].res_type = BNA_RES_T_MEM;
	res_info[BNA_MOD_RES_MEM_T_MCMAC_ARRAY].res_u.mem_info.mem_type =
		BNA_MEM_T_KVA;
	res_info[BNA_MOD_RES_MEM_T_MCMAC_ARRAY].res_u.mem_info.num = 1;
	res_info[BNA_MOD_RES_MEM_T_MCMAC_ARRAY].res_u.mem_info.len =
		(attr->num_mcmac * 2) * माप(काष्ठा bna_mac);

	/* Virtual memory क्रम Multicast handle - stored by mcam module */
	res_info[BNA_MOD_RES_MEM_T_MCHANDLE_ARRAY].res_type = BNA_RES_T_MEM;
	res_info[BNA_MOD_RES_MEM_T_MCHANDLE_ARRAY].res_u.mem_info.mem_type =
		BNA_MEM_T_KVA;
	res_info[BNA_MOD_RES_MEM_T_MCHANDLE_ARRAY].res_u.mem_info.num = 1;
	res_info[BNA_MOD_RES_MEM_T_MCHANDLE_ARRAY].res_u.mem_info.len =
		attr->num_mcmac * माप(काष्ठा bna_mcam_handle);
पूर्ण

व्योम
bna_init(काष्ठा bna *bna, काष्ठा bnad *bnad,
		काष्ठा bfa_pcidev *pcidev, काष्ठा bna_res_info *res_info)
अणु
	bna->bnad = bnad;
	bna->pcidev = *pcidev;

	bna->stats.hw_stats_kva = (काष्ठा bfi_enet_stats *)
		res_info[BNA_RES_MEM_T_STATS].res_u.mem_info.mdl[0].kva;
	bna->stats.hw_stats_dma.msb =
		res_info[BNA_RES_MEM_T_STATS].res_u.mem_info.mdl[0].dma.msb;
	bna->stats.hw_stats_dma.lsb =
		res_info[BNA_RES_MEM_T_STATS].res_u.mem_info.mdl[0].dma.lsb;

	bna_reg_addr_init(bna, &bna->pcidev);

	/* Also initializes diag, cee, sfp, phy_port, msgq */
	bna_ioceth_init(&bna->ioceth, bna, res_info);

	bna_enet_init(&bna->enet, bna);
	bna_ethport_init(&bna->ethport, bna);
पूर्ण

व्योम
bna_mod_init(काष्ठा bna *bna, काष्ठा bna_res_info *res_info)
अणु
	bna_tx_mod_init(&bna->tx_mod, bna, res_info);

	bna_rx_mod_init(&bna->rx_mod, bna, res_info);

	bna_ucam_mod_init(&bna->ucam_mod, bna, res_info);

	bna_mcam_mod_init(&bna->mcam_mod, bna, res_info);

	bna->शेष_mode_rid = BFI_INVALID_RID;
	bna->promisc_rid = BFI_INVALID_RID;

	bna->mod_flags |= BNA_MOD_F_INIT_DONE;
पूर्ण

व्योम
bna_uninit(काष्ठा bna *bna)
अणु
	अगर (bna->mod_flags & BNA_MOD_F_INIT_DONE) अणु
		bna_mcam_mod_uninit(&bna->mcam_mod);
		bna_ucam_mod_uninit(&bna->ucam_mod);
		bna_rx_mod_uninit(&bna->rx_mod);
		bna_tx_mod_uninit(&bna->tx_mod);
		bna->mod_flags &= ~BNA_MOD_F_INIT_DONE;
	पूर्ण

	bna_stats_mod_uninit(&bna->stats_mod);
	bna_ethport_uninit(&bna->ethport);
	bna_enet_uninit(&bna->enet);

	bna_ioceth_uninit(&bna->ioceth);

	bna->bnad = शून्य;
पूर्ण

पूर्णांक
bna_num_txq_set(काष्ठा bna *bna, पूर्णांक num_txq)
अणु
	अगर (bna->ioceth.attr.fw_query_complete &&
		(num_txq <= bna->ioceth.attr.num_txq)) अणु
		bna->ioceth.attr.num_txq = num_txq;
		वापस BNA_CB_SUCCESS;
	पूर्ण

	वापस BNA_CB_FAIL;
पूर्ण

पूर्णांक
bna_num_rxp_set(काष्ठा bna *bna, पूर्णांक num_rxp)
अणु
	अगर (bna->ioceth.attr.fw_query_complete &&
		(num_rxp <= bna->ioceth.attr.num_rxp)) अणु
		bna->ioceth.attr.num_rxp = num_rxp;
		वापस BNA_CB_SUCCESS;
	पूर्ण

	वापस BNA_CB_FAIL;
पूर्ण

काष्ठा bna_mac *
bna_cam_mod_mac_get(काष्ठा list_head *head)
अणु
	काष्ठा bna_mac *mac;

	mac = list_first_entry_or_null(head, काष्ठा bna_mac, qe);
	अगर (mac)
		list_del(&mac->qe);

	वापस mac;
पूर्ण

काष्ठा bna_mcam_handle *
bna_mcam_mod_handle_get(काष्ठा bna_mcam_mod *mcam_mod)
अणु
	काष्ठा bna_mcam_handle *handle;

	handle = list_first_entry_or_null(&mcam_mod->मुक्त_handle_q,
					  काष्ठा bna_mcam_handle, qe);
	अगर (handle)
		list_del(&handle->qe);

	वापस handle;
पूर्ण

व्योम
bna_mcam_mod_handle_put(काष्ठा bna_mcam_mod *mcam_mod,
			काष्ठा bna_mcam_handle *handle)
अणु
	list_add_tail(&handle->qe, &mcam_mod->मुक्त_handle_q);
पूर्ण

व्योम
bna_hw_stats_get(काष्ठा bna *bna)
अणु
	अगर (!bna->stats_mod.ioc_पढ़ोy) अणु
		bnad_cb_stats_get(bna->bnad, BNA_CB_FAIL, &bna->stats);
		वापस;
	पूर्ण
	अगर (bna->stats_mod.stats_get_busy) अणु
		bnad_cb_stats_get(bna->bnad, BNA_CB_BUSY, &bna->stats);
		वापस;
	पूर्ण

	bna_bfi_stats_get(bna);
पूर्ण
