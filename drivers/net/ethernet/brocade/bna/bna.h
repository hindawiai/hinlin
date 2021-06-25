<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Linux network driver क्रम QLogic BR-series Converged Network Adapter.
 */
/*
 * Copyright (c) 2005-2014 Brocade Communications Systems, Inc.
 * Copyright (c) 2014-2015 QLogic Corporation
 * All rights reserved
 * www.qlogic.com
 */
#अगर_अघोषित __BNA_H__
#घोषणा __BNA_H__

#समावेश "bfa_defs.h"
#समावेश "bfa_ioc.h"
#समावेश "bfi_enet.h"
#समावेश "bna_types.h"

बाह्य स्थिर u32 bna_napi_dim_vector[][BNA_BIAS_T_MAX];

/*  Macros and स्थिरants  */

#घोषणा bna_is_small_rxq(_id) ((_id) & 0x1)

/*
 * input : _addr-> os dma addr in host endian क्रमmat,
 * output : _bna_dma_addr-> poपूर्णांकer to hw dma addr
 */
#घोषणा BNA_SET_DMA_ADDR(_addr, _bna_dma_addr)				\
करो अणु									\
	u64 पंचांगp_addr =						\
	cpu_to_be64((u64)(_addr));				\
	(_bna_dma_addr)->msb = ((काष्ठा bna_dma_addr *)&पंचांगp_addr)->msb; \
	(_bna_dma_addr)->lsb = ((काष्ठा bna_dma_addr *)&पंचांगp_addr)->lsb; \
पूर्ण जबतक (0)

/*
 * input : _bna_dma_addr-> poपूर्णांकer to hw dma addr
 * output : _addr-> os dma addr in host endian क्रमmat
 */
#घोषणा BNA_GET_DMA_ADDR(_bna_dma_addr, _addr)			\
करो अणु								\
	(_addr) = ((((u64)ntohl((_bna_dma_addr)->msb))) << 32)		\
	| ((ntohl((_bna_dma_addr)->lsb) & 0xffffffff));	\
पूर्ण जबतक (0)

#घोषणा BNA_TXQ_WI_NEEDED(_vectors)	(((_vectors) + 3) >> 2)

#घोषणा BNA_QE_INDX_ADD(_qe_idx, _qe_num, _q_depth)			\
	((_qe_idx) = ((_qe_idx) + (_qe_num)) & ((_q_depth) - 1))

#घोषणा BNA_QE_INDX_INC(_idx, _q_depth) BNA_QE_INDX_ADD(_idx, 1, _q_depth)

#घोषणा BNA_Q_INDEX_CHANGE(_old_idx, _updated_idx, _q_depth)		\
	(((_updated_idx) - (_old_idx)) & ((_q_depth) - 1))

#घोषणा BNA_QE_FREE_CNT(_q_ptr, _q_depth)				\
	(((_q_ptr)->consumer_index - (_q_ptr)->producer_index - 1) &	\
	 ((_q_depth) - 1))
#घोषणा BNA_QE_IN_USE_CNT(_q_ptr, _q_depth)				\
	((((_q_ptr)->producer_index - (_q_ptr)->consumer_index)) &	\
	 (_q_depth - 1))

#घोषणा BNA_LARGE_PKT_SIZE		1000

#घोषणा BNA_UPDATE_PKT_CNT(_pkt, _len)					\
करो अणु									\
	अगर ((_len) > BNA_LARGE_PKT_SIZE) अणु				\
		(_pkt)->large_pkt_cnt++;				\
	पूर्ण अन्यथा अणु							\
		(_pkt)->small_pkt_cnt++;				\
	पूर्ण								\
पूर्ण जबतक (0)

#घोषणा	call_rxf_stop_cbfn(rxf)						\
करो अणु									\
	अगर ((rxf)->stop_cbfn) अणु						\
		व्योम (*cbfn)(काष्ठा bna_rx *);			\
		काष्ठा bna_rx *cbarg;					\
		cbfn = (rxf)->stop_cbfn;				\
		cbarg = (rxf)->stop_cbarg;				\
		(rxf)->stop_cbfn = शून्य;				\
		(rxf)->stop_cbarg = शून्य;				\
		cbfn(cbarg);						\
	पूर्ण								\
पूर्ण जबतक (0)

#घोषणा	call_rxf_start_cbfn(rxf)					\
करो अणु									\
	अगर ((rxf)->start_cbfn) अणु					\
		व्योम (*cbfn)(काष्ठा bna_rx *);			\
		काष्ठा bna_rx *cbarg;					\
		cbfn = (rxf)->start_cbfn;				\
		cbarg = (rxf)->start_cbarg;				\
		(rxf)->start_cbfn = शून्य;				\
		(rxf)->start_cbarg = शून्य;				\
		cbfn(cbarg);						\
	पूर्ण								\
पूर्ण जबतक (0)

#घोषणा	call_rxf_cam_fltr_cbfn(rxf)					\
करो अणु									\
	अगर ((rxf)->cam_fltr_cbfn) अणु					\
		व्योम (*cbfn)(काष्ठा bnad *, काष्ठा bna_rx *);	\
		काष्ठा bnad *cbarg;					\
		cbfn = (rxf)->cam_fltr_cbfn;				\
		cbarg = (rxf)->cam_fltr_cbarg;				\
		(rxf)->cam_fltr_cbfn = शून्य;				\
		(rxf)->cam_fltr_cbarg = शून्य;				\
		cbfn(cbarg, rxf->rx);					\
	पूर्ण								\
पूर्ण जबतक (0)

#घोषणा is_xxx_enable(mode, biपंचांगask, xxx) ((biपंचांगask & xxx) && (mode & xxx))

#घोषणा is_xxx_disable(mode, biपंचांगask, xxx) ((biपंचांगask & xxx) && !(mode & xxx))

#घोषणा xxx_enable(mode, biपंचांगask, xxx)					\
करो अणु									\
	biपंचांगask |= xxx;							\
	mode |= xxx;							\
पूर्ण जबतक (0)

#घोषणा xxx_disable(mode, biपंचांगask, xxx)					\
करो अणु									\
	biपंचांगask |= xxx;							\
	mode &= ~xxx;							\
पूर्ण जबतक (0)

#घोषणा xxx_inactive(mode, biपंचांगask, xxx)				\
करो अणु									\
	biपंचांगask &= ~xxx;						\
	mode &= ~xxx;							\
पूर्ण जबतक (0)

#घोषणा is_promisc_enable(mode, biपंचांगask)				\
	is_xxx_enable(mode, biपंचांगask, BNA_RXMODE_PROMISC)

#घोषणा is_promisc_disable(mode, biपंचांगask)				\
	is_xxx_disable(mode, biपंचांगask, BNA_RXMODE_PROMISC)

#घोषणा promisc_enable(mode, biपंचांगask)					\
	xxx_enable(mode, biपंचांगask, BNA_RXMODE_PROMISC)

#घोषणा promisc_disable(mode, biपंचांगask)					\
	xxx_disable(mode, biपंचांगask, BNA_RXMODE_PROMISC)

#घोषणा promisc_inactive(mode, biपंचांगask)					\
	xxx_inactive(mode, biपंचांगask, BNA_RXMODE_PROMISC)

#घोषणा is_शेष_enable(mode, biपंचांगask)				\
	is_xxx_enable(mode, biपंचांगask, BNA_RXMODE_DEFAULT)

#घोषणा is_शेष_disable(mode, biपंचांगask)				\
	is_xxx_disable(mode, biपंचांगask, BNA_RXMODE_DEFAULT)

#घोषणा शेष_enable(mode, biपंचांगask)					\
	xxx_enable(mode, biपंचांगask, BNA_RXMODE_DEFAULT)

#घोषणा शेष_disable(mode, biपंचांगask)					\
	xxx_disable(mode, biपंचांगask, BNA_RXMODE_DEFAULT)

#घोषणा शेष_inactive(mode, biपंचांगask)					\
	xxx_inactive(mode, biपंचांगask, BNA_RXMODE_DEFAULT)

#घोषणा is_allmulti_enable(mode, biपंचांगask)				\
	is_xxx_enable(mode, biपंचांगask, BNA_RXMODE_ALLMULTI)

#घोषणा is_allmulti_disable(mode, biपंचांगask)				\
	is_xxx_disable(mode, biपंचांगask, BNA_RXMODE_ALLMULTI)

#घोषणा allmulti_enable(mode, biपंचांगask)					\
	xxx_enable(mode, biपंचांगask, BNA_RXMODE_ALLMULTI)

#घोषणा allmulti_disable(mode, biपंचांगask)					\
	xxx_disable(mode, biपंचांगask, BNA_RXMODE_ALLMULTI)

#घोषणा allmulti_inactive(mode, biपंचांगask)				\
	xxx_inactive(mode, biपंचांगask, BNA_RXMODE_ALLMULTI)

#घोषणा	GET_RXQS(rxp, q0, q1)	करो अणु					\
	चयन ((rxp)->type) अणु						\
	हाल BNA_RXP_SINGLE:						\
		(q0) = rxp->rxq.single.only;				\
		(q1) = शून्य;						\
		अवरोध;							\
	हाल BNA_RXP_SLR:						\
		(q0) = rxp->rxq.slr.large;				\
		(q1) = rxp->rxq.slr.small;				\
		अवरोध;							\
	हाल BNA_RXP_HDS:						\
		(q0) = rxp->rxq.hds.data;				\
		(q1) = rxp->rxq.hds.hdr;				\
		अवरोध;							\
	पूर्ण								\
पूर्ण जबतक (0)

#घोषणा bna_tx_rid_mask(_bna) ((_bna)->tx_mod.rid_mask)

#घोषणा bna_rx_rid_mask(_bna) ((_bna)->rx_mod.rid_mask)

#घोषणा bna_tx_from_rid(_bna, _rid, _tx)				\
करो अणु									\
	काष्ठा bna_tx_mod *__tx_mod = &(_bna)->tx_mod;			\
	काष्ठा bna_tx *__tx;						\
	_tx = शून्य;							\
	list_क्रम_each_entry(__tx, &__tx_mod->tx_active_q, qe) अणु		\
		अगर (__tx->rid == (_rid)) अणु				\
			(_tx) = __tx;					\
			अवरोध;						\
		पूर्ण							\
	पूर्ण								\
पूर्ण जबतक (0)

#घोषणा bna_rx_from_rid(_bna, _rid, _rx)				\
करो अणु									\
	काष्ठा bna_rx_mod *__rx_mod = &(_bna)->rx_mod;			\
	काष्ठा bna_rx *__rx;						\
	_rx = शून्य;							\
	list_क्रम_each_entry(__rx, &__rx_mod->rx_active_q, qe) अणु		\
		अगर (__rx->rid == (_rid)) अणु				\
			(_rx) = __rx;					\
			अवरोध;						\
		पूर्ण							\
	पूर्ण								\
पूर्ण जबतक (0)

#घोषणा bna_mcam_mod_मुक्त_q(_bna) (&(_bna)->mcam_mod.मुक्त_q)

#घोषणा bna_mcam_mod_del_q(_bna) (&(_bna)->mcam_mod.del_q)

#घोषणा bna_ucam_mod_मुक्त_q(_bna) (&(_bna)->ucam_mod.मुक्त_q)

#घोषणा bna_ucam_mod_del_q(_bna) (&(_bna)->ucam_mod.del_q)

/*  Inline functions  */

अटल अंतरभूत काष्ठा bna_mac *bna_mac_find(काष्ठा list_head *q, स्थिर u8 *addr)
अणु
	काष्ठा bna_mac *mac;

	list_क्रम_each_entry(mac, q, qe)
		अगर (ether_addr_equal(mac->addr, addr))
			वापस mac;
	वापस शून्य;
पूर्ण

#घोषणा bna_attr(_bna) (&(_bna)->ioceth.attr)

/* Function prototypes */

/* BNA */

/* FW response handlers */
व्योम bna_bfi_stats_clr_rsp(काष्ठा bna *bna, काष्ठा bfi_msgq_mhdr *msghdr);

/* APIs क्रम BNAD */
व्योम bna_res_req(काष्ठा bna_res_info *res_info);
व्योम bna_mod_res_req(काष्ठा bna *bna, काष्ठा bna_res_info *res_info);
व्योम bna_init(काष्ठा bna *bna, काष्ठा bnad *bnad,
			काष्ठा bfa_pcidev *pcidev,
			काष्ठा bna_res_info *res_info);
व्योम bna_mod_init(काष्ठा bna *bna, काष्ठा bna_res_info *res_info);
व्योम bna_uninit(काष्ठा bna *bna);
पूर्णांक bna_num_txq_set(काष्ठा bna *bna, पूर्णांक num_txq);
पूर्णांक bna_num_rxp_set(काष्ठा bna *bna, पूर्णांक num_rxp);
व्योम bna_hw_stats_get(काष्ठा bna *bna);

/* APIs क्रम RxF */
काष्ठा bna_mac *bna_cam_mod_mac_get(काष्ठा list_head *head);
काष्ठा bna_mcam_handle *bna_mcam_mod_handle_get(काष्ठा bna_mcam_mod *mod);
व्योम bna_mcam_mod_handle_put(काष्ठा bna_mcam_mod *mcam_mod,
			  काष्ठा bna_mcam_handle *handle);

/* MBOX */

/* API क्रम BNAD */
व्योम bna_mbox_handler(काष्ठा bna *bna, u32 पूर्णांकr_status);

/* ETHPORT */

/* Callbacks क्रम RX */
व्योम bna_ethport_cb_rx_started(काष्ठा bna_ethport *ethport);
व्योम bna_ethport_cb_rx_stopped(काष्ठा bna_ethport *ethport);

/* TX MODULE AND TX */

/* FW response handelrs */
व्योम bna_bfi_tx_enet_start_rsp(काष्ठा bna_tx *tx,
			       काष्ठा bfi_msgq_mhdr *msghdr);
व्योम bna_bfi_tx_enet_stop_rsp(काष्ठा bna_tx *tx,
			      काष्ठा bfi_msgq_mhdr *msghdr);
व्योम bna_bfi_bw_update_aen(काष्ठा bna_tx_mod *tx_mod);

/* APIs क्रम BNA */
व्योम bna_tx_mod_init(काष्ठा bna_tx_mod *tx_mod, काष्ठा bna *bna,
		     काष्ठा bna_res_info *res_info);
व्योम bna_tx_mod_uninit(काष्ठा bna_tx_mod *tx_mod);

/* APIs क्रम ENET */
व्योम bna_tx_mod_start(काष्ठा bna_tx_mod *tx_mod, क्रमागत bna_tx_type type);
व्योम bna_tx_mod_stop(काष्ठा bna_tx_mod *tx_mod, क्रमागत bna_tx_type type);
व्योम bna_tx_mod_fail(काष्ठा bna_tx_mod *tx_mod);

/* APIs क्रम BNAD */
व्योम bna_tx_res_req(पूर्णांक num_txq, पूर्णांक txq_depth,
		    काष्ठा bna_res_info *res_info);
काष्ठा bna_tx *bna_tx_create(काष्ठा bna *bna, काष्ठा bnad *bnad,
			       काष्ठा bna_tx_config *tx_cfg,
			       स्थिर काष्ठा bna_tx_event_cbfn *tx_cbfn,
			       काष्ठा bna_res_info *res_info, व्योम *priv);
व्योम bna_tx_destroy(काष्ठा bna_tx *tx);
व्योम bna_tx_enable(काष्ठा bna_tx *tx);
व्योम bna_tx_disable(काष्ठा bna_tx *tx, क्रमागत bna_cleanup_type type,
		    व्योम (*cbfn)(व्योम *, काष्ठा bna_tx *));
व्योम bna_tx_cleanup_complete(काष्ठा bna_tx *tx);
व्योम bna_tx_coalescing_समयo_set(काष्ठा bna_tx *tx, पूर्णांक coalescing_समयo);

/* RX MODULE, RX, RXF */

/* FW response handlers */
व्योम bna_bfi_rx_enet_start_rsp(काष्ठा bna_rx *rx,
			       काष्ठा bfi_msgq_mhdr *msghdr);
व्योम bna_bfi_rx_enet_stop_rsp(काष्ठा bna_rx *rx,
			      काष्ठा bfi_msgq_mhdr *msghdr);
व्योम bna_bfi_rxf_cfg_rsp(काष्ठा bna_rxf *rxf, काष्ठा bfi_msgq_mhdr *msghdr);
व्योम bna_bfi_rxf_mcast_add_rsp(काष्ठा bna_rxf *rxf,
			       काष्ठा bfi_msgq_mhdr *msghdr);
व्योम bna_bfi_rxf_ucast_set_rsp(काष्ठा bna_rxf *rxf,
			       काष्ठा bfi_msgq_mhdr *msghdr);

/* APIs क्रम BNA */
व्योम bna_rx_mod_init(काष्ठा bna_rx_mod *rx_mod, काष्ठा bna *bna,
		     काष्ठा bna_res_info *res_info);
व्योम bna_rx_mod_uninit(काष्ठा bna_rx_mod *rx_mod);

/* APIs क्रम ENET */
व्योम bna_rx_mod_start(काष्ठा bna_rx_mod *rx_mod, क्रमागत bna_rx_type type);
व्योम bna_rx_mod_stop(काष्ठा bna_rx_mod *rx_mod, क्रमागत bna_rx_type type);
व्योम bna_rx_mod_fail(काष्ठा bna_rx_mod *rx_mod);

/* APIs क्रम BNAD */
व्योम bna_rx_res_req(काष्ठा bna_rx_config *rx_config,
		    काष्ठा bna_res_info *res_info);
काष्ठा bna_rx *bna_rx_create(काष्ठा bna *bna, काष्ठा bnad *bnad,
			       काष्ठा bna_rx_config *rx_cfg,
			       स्थिर काष्ठा bna_rx_event_cbfn *rx_cbfn,
			       काष्ठा bna_res_info *res_info, व्योम *priv);
व्योम bna_rx_destroy(काष्ठा bna_rx *rx);
व्योम bna_rx_enable(काष्ठा bna_rx *rx);
व्योम bna_rx_disable(काष्ठा bna_rx *rx, क्रमागत bna_cleanup_type type,
		    व्योम (*cbfn)(व्योम *, काष्ठा bna_rx *));
व्योम bna_rx_cleanup_complete(काष्ठा bna_rx *rx);
व्योम bna_rx_coalescing_समयo_set(काष्ठा bna_rx *rx, पूर्णांक coalescing_समयo);
व्योम bna_rx_dim_reconfig(काष्ठा bna *bna, स्थिर u32 vector[][BNA_BIAS_T_MAX]);
व्योम bna_rx_dim_update(काष्ठा bna_ccb *ccb);
क्रमागत bna_cb_status bna_rx_ucast_set(काष्ठा bna_rx *rx, स्थिर u8 *ucmac);
क्रमागत bna_cb_status bna_rx_ucast_listset(काष्ठा bna_rx *rx, पूर्णांक count,
					स्थिर u8 *uclist);
क्रमागत bna_cb_status bna_rx_mcast_add(काष्ठा bna_rx *rx, स्थिर u8 *mcmac,
				    व्योम (*cbfn)(काष्ठा bnad *,
						 काष्ठा bna_rx *));
क्रमागत bna_cb_status bna_rx_mcast_listset(काष्ठा bna_rx *rx, पूर्णांक count,
					स्थिर u8 *mcmac);
व्योम
bna_rx_mcast_delall(काष्ठा bna_rx *rx);
क्रमागत bna_cb_status
bna_rx_mode_set(काष्ठा bna_rx *rx, क्रमागत bna_rxmode rxmode,
		क्रमागत bna_rxmode biपंचांगask);
व्योम bna_rx_vlan_add(काष्ठा bna_rx *rx, पूर्णांक vlan_id);
व्योम bna_rx_vlan_del(काष्ठा bna_rx *rx, पूर्णांक vlan_id);
व्योम bna_rx_vlanfilter_enable(काष्ठा bna_rx *rx);
व्योम bna_rx_vlan_strip_enable(काष्ठा bna_rx *rx);
व्योम bna_rx_vlan_strip_disable(काष्ठा bna_rx *rx);
/* ENET */

/* API क्रम RX */
पूर्णांक bna_enet_mtu_get(काष्ठा bna_enet *enet);

/* Callbacks क्रम TX, RX */
व्योम bna_enet_cb_tx_stopped(काष्ठा bna_enet *enet);
व्योम bna_enet_cb_rx_stopped(काष्ठा bna_enet *enet);

/* API क्रम BNAD */
व्योम bna_enet_enable(काष्ठा bna_enet *enet);
व्योम bna_enet_disable(काष्ठा bna_enet *enet, क्रमागत bna_cleanup_type type,
		      व्योम (*cbfn)(व्योम *));
व्योम bna_enet_छोड़ो_config(काष्ठा bna_enet *enet,
			   काष्ठा bna_छोड़ो_config *छोड़ो_config);
व्योम bna_enet_mtu_set(काष्ठा bna_enet *enet, पूर्णांक mtu,
		      व्योम (*cbfn)(काष्ठा bnad *));
व्योम bna_enet_perm_mac_get(काष्ठा bna_enet *enet, u8 *mac);

/* IOCETH */

/* APIs क्रम BNAD */
व्योम bna_ioceth_enable(काष्ठा bna_ioceth *ioceth);
व्योम bna_ioceth_disable(काष्ठा bna_ioceth *ioceth,
			क्रमागत bna_cleanup_type type);

/* BNAD */

/* Callbacks क्रम ENET */
व्योम bnad_cb_ethport_link_status(काष्ठा bnad *bnad,
			      क्रमागत bna_link_status status);

/* Callbacks क्रम IOCETH */
व्योम bnad_cb_ioceth_पढ़ोy(काष्ठा bnad *bnad);
व्योम bnad_cb_ioceth_failed(काष्ठा bnad *bnad);
व्योम bnad_cb_ioceth_disabled(काष्ठा bnad *bnad);
व्योम bnad_cb_mbox_पूर्णांकr_enable(काष्ठा bnad *bnad);
व्योम bnad_cb_mbox_पूर्णांकr_disable(काष्ठा bnad *bnad);

/* Callbacks क्रम BNA */
व्योम bnad_cb_stats_get(काष्ठा bnad *bnad, क्रमागत bna_cb_status status,
		       काष्ठा bna_stats *stats);

#पूर्ण_अगर  /* __BNA_H__ */
