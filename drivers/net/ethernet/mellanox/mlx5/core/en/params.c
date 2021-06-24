<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB
/* Copyright (c) 2019 Mellanox Technologies. */

#समावेश "en/params.h"
#समावेश "en/txrx.h"
#समावेश "en/port.h"
#समावेश "en_accel/en_accel.h"
#समावेश "accel/ipsec.h"
#समावेश "fpga/ipsec.h"

अटल bool mlx5e_rx_is_xdp(काष्ठा mlx5e_params *params,
			    काष्ठा mlx5e_xsk_param *xsk)
अणु
	वापस params->xdp_prog || xsk;
पूर्ण

u16 mlx5e_get_linear_rq_headroom(काष्ठा mlx5e_params *params,
				 काष्ठा mlx5e_xsk_param *xsk)
अणु
	u16 headroom;

	अगर (xsk)
		वापस xsk->headroom;

	headroom = NET_IP_ALIGN;
	अगर (mlx5e_rx_is_xdp(params, xsk))
		headroom += XDP_PACKET_HEADROOM;
	अन्यथा
		headroom += MLX5_RX_HEADROOM;

	वापस headroom;
पूर्ण

u32 mlx5e_rx_get_min_frag_sz(काष्ठा mlx5e_params *params,
			     काष्ठा mlx5e_xsk_param *xsk)
अणु
	u32 hw_mtu = MLX5E_SW2HW_MTU(params, params->sw_mtu);
	u16 linear_rq_headroom = mlx5e_get_linear_rq_headroom(params, xsk);

	वापस linear_rq_headroom + hw_mtu;
पूर्ण

अटल u32 mlx5e_rx_get_linear_frag_sz(काष्ठा mlx5e_params *params,
				       काष्ठा mlx5e_xsk_param *xsk)
अणु
	u32 frag_sz = mlx5e_rx_get_min_frag_sz(params, xsk);

	/* AF_XDP करोesn't build SKBs in place. */
	अगर (!xsk)
		frag_sz = MLX5_SKB_FRAG_SZ(frag_sz);

	/* XDP in mlx5e करोesn't support multiple packets per page. AF_XDP is a
	 * special हाल. It can run with frames smaller than a page, as it
	 * करोesn't allocate pages dynamically. However, here we pretend that
	 * fragments are page-sized: it allows to treat XSK frames like pages
	 * by redirecting alloc and मुक्त operations to XSK rings and by using
	 * the fact there are no multiple packets per "page" (which is a frame).
	 * The latter is important, because frames may come in a अक्रमom order,
	 * and we will have trouble assemblying a real page of multiple frames.
	 */
	अगर (mlx5e_rx_is_xdp(params, xsk))
		frag_sz = max_t(u32, frag_sz, PAGE_SIZE);

	/* Even अगर we can go with a smaller fragment size, we must not put
	 * multiple packets पूर्णांकo a single frame.
	 */
	अगर (xsk)
		frag_sz = max_t(u32, frag_sz, xsk->chunk_size);

	वापस frag_sz;
पूर्ण

u8 mlx5e_mpwqe_log_pkts_per_wqe(काष्ठा mlx5e_params *params,
				काष्ठा mlx5e_xsk_param *xsk)
अणु
	u32 linear_frag_sz = mlx5e_rx_get_linear_frag_sz(params, xsk);

	वापस MLX5_MPWRQ_LOG_WQE_SZ - order_base_2(linear_frag_sz);
पूर्ण

bool mlx5e_rx_is_linear_skb(काष्ठा mlx5e_params *params,
			    काष्ठा mlx5e_xsk_param *xsk)
अणु
	/* AF_XDP allocates SKBs on XDP_PASS - ensure they करोn't occupy more
	 * than one page. For this, check both with and without xsk.
	 */
	u32 linear_frag_sz = max(mlx5e_rx_get_linear_frag_sz(params, xsk),
				 mlx5e_rx_get_linear_frag_sz(params, शून्य));

	वापस !params->lro_en && linear_frag_sz <= PAGE_SIZE;
पूर्ण

bool mlx5e_verअगरy_rx_mpwqe_strides(काष्ठा mlx5_core_dev *mdev,
				   u8 log_stride_sz, u8 log_num_strides)
अणु
	अगर (log_stride_sz + log_num_strides != MLX5_MPWRQ_LOG_WQE_SZ)
		वापस false;

	अगर (log_stride_sz < MLX5_MPWQE_LOG_STRIDE_SZ_BASE ||
	    log_stride_sz > MLX5_MPWQE_LOG_STRIDE_SZ_MAX)
		वापस false;

	अगर (log_num_strides > MLX5_MPWQE_LOG_NUM_STRIDES_MAX)
		वापस false;

	अगर (MLX5_CAP_GEN(mdev, ext_stride_num_range))
		वापस log_num_strides >= MLX5_MPWQE_LOG_NUM_STRIDES_EXT_BASE;

	वापस log_num_strides >= MLX5_MPWQE_LOG_NUM_STRIDES_BASE;
पूर्ण

bool mlx5e_rx_mpwqe_is_linear_skb(काष्ठा mlx5_core_dev *mdev,
				  काष्ठा mlx5e_params *params,
				  काष्ठा mlx5e_xsk_param *xsk)
अणु
	s8 log_num_strides;
	u8 log_stride_sz;

	अगर (!mlx5e_rx_is_linear_skb(params, xsk))
		वापस false;

	log_stride_sz = order_base_2(mlx5e_rx_get_linear_frag_sz(params, xsk));
	log_num_strides = MLX5_MPWRQ_LOG_WQE_SZ - log_stride_sz;

	वापस mlx5e_verअगरy_rx_mpwqe_strides(mdev, log_stride_sz, log_num_strides);
पूर्ण

u8 mlx5e_mpwqe_get_log_rq_size(काष्ठा mlx5e_params *params,
			       काष्ठा mlx5e_xsk_param *xsk)
अणु
	u8 log_pkts_per_wqe = mlx5e_mpwqe_log_pkts_per_wqe(params, xsk);

	/* Numbers are अचिन्हित, करोn't subtract to aव्योम underflow. */
	अगर (params->log_rq_mtu_frames <
	    log_pkts_per_wqe + MLX5E_PARAMS_MINIMUM_LOG_RQ_SIZE_MPW)
		वापस MLX5E_PARAMS_MINIMUM_LOG_RQ_SIZE_MPW;

	वापस params->log_rq_mtu_frames - log_pkts_per_wqe;
पूर्ण

u8 mlx5e_mpwqe_get_log_stride_size(काष्ठा mlx5_core_dev *mdev,
				   काष्ठा mlx5e_params *params,
				   काष्ठा mlx5e_xsk_param *xsk)
अणु
	अगर (mlx5e_rx_mpwqe_is_linear_skb(mdev, params, xsk))
		वापस order_base_2(mlx5e_rx_get_linear_frag_sz(params, xsk));

	वापस MLX5_MPWRQ_DEF_LOG_STRIDE_SZ(mdev);
पूर्ण

u8 mlx5e_mpwqe_get_log_num_strides(काष्ठा mlx5_core_dev *mdev,
				   काष्ठा mlx5e_params *params,
				   काष्ठा mlx5e_xsk_param *xsk)
अणु
	वापस MLX5_MPWRQ_LOG_WQE_SZ -
		mlx5e_mpwqe_get_log_stride_size(mdev, params, xsk);
पूर्ण

u16 mlx5e_get_rq_headroom(काष्ठा mlx5_core_dev *mdev,
			  काष्ठा mlx5e_params *params,
			  काष्ठा mlx5e_xsk_param *xsk)
अणु
	bool is_linear_skb = (params->rq_wq_type == MLX5_WQ_TYPE_CYCLIC) ?
		mlx5e_rx_is_linear_skb(params, xsk) :
		mlx5e_rx_mpwqe_is_linear_skb(mdev, params, xsk);

	वापस is_linear_skb ? mlx5e_get_linear_rq_headroom(params, xsk) : 0;
पूर्ण

u16 mlx5e_calc_sq_stop_room(काष्ठा mlx5_core_dev *mdev, काष्ठा mlx5e_params *params)
अणु
	bool is_mpwqe = MLX5E_GET_PFLAG(params, MLX5E_PFLAG_SKB_TX_MPWQE);
	u16 stop_room;

	stop_room  = mlx5e_tls_get_stop_room(mdev, params);
	stop_room += mlx5e_stop_room_क्रम_wqe(MLX5_SEND_WQE_MAX_WQEBBS);
	अगर (is_mpwqe)
		/* A MPWQE can take up to the maximum-sized WQE + all the normal
		 * stop room can be taken अगर a new packet अवरोधs the active
		 * MPWQE session and allocates its WQEs right away.
		 */
		stop_room += mlx5e_stop_room_क्रम_wqe(MLX5_SEND_WQE_MAX_WQEBBS);

	वापस stop_room;
पूर्ण

पूर्णांक mlx5e_validate_params(काष्ठा mlx5_core_dev *mdev, काष्ठा mlx5e_params *params)
अणु
	माप_प्रकार sq_size = 1 << params->log_sq_size;
	u16 stop_room;

	stop_room = mlx5e_calc_sq_stop_room(mdev, params);
	अगर (stop_room >= sq_size) अणु
		mlx5_core_err(mdev, "Stop room %u is bigger than the SQ size %zu\n",
			      stop_room, sq_size);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा dim_cq_moder mlx5e_get_def_tx_moderation(u8 cq_period_mode)
अणु
	काष्ठा dim_cq_moder moder;

	moder.cq_period_mode = cq_period_mode;
	moder.pkts = MLX5E_PARAMS_DEFAULT_TX_CQ_MODERATION_PKTS;
	moder.usec = MLX5E_PARAMS_DEFAULT_TX_CQ_MODERATION_USEC;
	अगर (cq_period_mode == MLX5_CQ_PERIOD_MODE_START_FROM_CQE)
		moder.usec = MLX5E_PARAMS_DEFAULT_TX_CQ_MODERATION_USEC_FROM_CQE;

	वापस moder;
पूर्ण

अटल काष्ठा dim_cq_moder mlx5e_get_def_rx_moderation(u8 cq_period_mode)
अणु
	काष्ठा dim_cq_moder moder;

	moder.cq_period_mode = cq_period_mode;
	moder.pkts = MLX5E_PARAMS_DEFAULT_RX_CQ_MODERATION_PKTS;
	moder.usec = MLX5E_PARAMS_DEFAULT_RX_CQ_MODERATION_USEC;
	अगर (cq_period_mode == MLX5_CQ_PERIOD_MODE_START_FROM_CQE)
		moder.usec = MLX5E_PARAMS_DEFAULT_RX_CQ_MODERATION_USEC_FROM_CQE;

	वापस moder;
पूर्ण

अटल u8 mlx5_to_net_dim_cq_period_mode(u8 cq_period_mode)
अणु
	वापस cq_period_mode == MLX5_CQ_PERIOD_MODE_START_FROM_CQE ?
		DIM_CQ_PERIOD_MODE_START_FROM_CQE :
		DIM_CQ_PERIOD_MODE_START_FROM_EQE;
पूर्ण

व्योम mlx5e_reset_tx_moderation(काष्ठा mlx5e_params *params, u8 cq_period_mode)
अणु
	अगर (params->tx_dim_enabled) अणु
		u8 dim_period_mode = mlx5_to_net_dim_cq_period_mode(cq_period_mode);

		params->tx_cq_moderation = net_dim_get_def_tx_moderation(dim_period_mode);
	पूर्ण अन्यथा अणु
		params->tx_cq_moderation = mlx5e_get_def_tx_moderation(cq_period_mode);
	पूर्ण
पूर्ण

व्योम mlx5e_reset_rx_moderation(काष्ठा mlx5e_params *params, u8 cq_period_mode)
अणु
	अगर (params->rx_dim_enabled) अणु
		u8 dim_period_mode = mlx5_to_net_dim_cq_period_mode(cq_period_mode);

		params->rx_cq_moderation = net_dim_get_def_rx_moderation(dim_period_mode);
	पूर्ण अन्यथा अणु
		params->rx_cq_moderation = mlx5e_get_def_rx_moderation(cq_period_mode);
	पूर्ण
पूर्ण

व्योम mlx5e_set_tx_cq_mode_params(काष्ठा mlx5e_params *params, u8 cq_period_mode)
अणु
	mlx5e_reset_tx_moderation(params, cq_period_mode);
	MLX5E_SET_PFLAG(params, MLX5E_PFLAG_TX_CQE_BASED_MODER,
			params->tx_cq_moderation.cq_period_mode ==
				MLX5_CQ_PERIOD_MODE_START_FROM_CQE);
पूर्ण

व्योम mlx5e_set_rx_cq_mode_params(काष्ठा mlx5e_params *params, u8 cq_period_mode)
अणु
	mlx5e_reset_rx_moderation(params, cq_period_mode);
	MLX5E_SET_PFLAG(params, MLX5E_PFLAG_RX_CQE_BASED_MODER,
			params->rx_cq_moderation.cq_period_mode ==
				MLX5_CQ_PERIOD_MODE_START_FROM_CQE);
पूर्ण

bool slow_pci_heuristic(काष्ठा mlx5_core_dev *mdev)
अणु
	u32 link_speed = 0;
	u32 pci_bw = 0;

	mlx5e_port_max_linkspeed(mdev, &link_speed);
	pci_bw = pcie_bandwidth_available(mdev->pdev, शून्य, शून्य, शून्य);
	mlx5_core_dbg_once(mdev, "Max link speed = %d, PCI BW = %d\n",
			   link_speed, pci_bw);

#घोषणा MLX5E_SLOW_PCI_RATIO (2)

	वापस link_speed && pci_bw &&
		link_speed > MLX5E_SLOW_PCI_RATIO * pci_bw;
पूर्ण

bool mlx5e_striding_rq_possible(काष्ठा mlx5_core_dev *mdev,
				काष्ठा mlx5e_params *params)
अणु
	अगर (!mlx5e_check_fragmented_striding_rq_cap(mdev))
		वापस false;

	अगर (mlx5_fpga_is_ipsec_device(mdev))
		वापस false;

	अगर (params->xdp_prog) अणु
		/* XSK params are not considered here. If striding RQ is in use,
		 * and an XSK is being खोलोed, mlx5e_rx_mpwqe_is_linear_skb will
		 * be called with the known XSK params.
		 */
		अगर (!mlx5e_rx_mpwqe_is_linear_skb(mdev, params, शून्य))
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

व्योम mlx5e_init_rq_type_params(काष्ठा mlx5_core_dev *mdev,
			       काष्ठा mlx5e_params *params)
अणु
	params->log_rq_mtu_frames = is_kdump_kernel() ?
		MLX5E_PARAMS_MINIMUM_LOG_RQ_SIZE :
		MLX5E_PARAMS_DEFAULT_LOG_RQ_SIZE;

	mlx5_core_info(mdev, "MLX5E: StrdRq(%d) RqSz(%ld) StrdSz(%ld) RxCqeCmprss(%d)\n",
		       params->rq_wq_type == MLX5_WQ_TYPE_LINKED_LIST_STRIDING_RQ,
		       params->rq_wq_type == MLX5_WQ_TYPE_LINKED_LIST_STRIDING_RQ ?
		       BIT(mlx5e_mpwqe_get_log_rq_size(params, शून्य)) :
		       BIT(params->log_rq_mtu_frames),
		       BIT(mlx5e_mpwqe_get_log_stride_size(mdev, params, शून्य)),
		       MLX5E_GET_PFLAG(params, MLX5E_PFLAG_RX_CQE_COMPRESS));
पूर्ण

व्योम mlx5e_set_rq_type(काष्ठा mlx5_core_dev *mdev, काष्ठा mlx5e_params *params)
अणु
	params->rq_wq_type = mlx5e_striding_rq_possible(mdev, params) &&
		MLX5E_GET_PFLAG(params, MLX5E_PFLAG_RX_STRIDING_RQ) ?
		MLX5_WQ_TYPE_LINKED_LIST_STRIDING_RQ :
		MLX5_WQ_TYPE_CYCLIC;
पूर्ण

व्योम mlx5e_build_rq_params(काष्ठा mlx5_core_dev *mdev,
			   काष्ठा mlx5e_params *params)
अणु
	/* Prefer Striding RQ, unless any of the following holds:
	 * - Striding RQ configuration is not possible/supported.
	 * - Slow PCI heuristic.
	 * - Legacy RQ would use linear SKB जबतक Striding RQ would use non-linear.
	 *
	 * No XSK params: checking the availability of striding RQ in general.
	 */
	अगर (!slow_pci_heuristic(mdev) &&
	    mlx5e_striding_rq_possible(mdev, params) &&
	    (mlx5e_rx_mpwqe_is_linear_skb(mdev, params, शून्य) ||
	     !mlx5e_rx_is_linear_skb(params, शून्य)))
		MLX5E_SET_PFLAG(params, MLX5E_PFLAG_RX_STRIDING_RQ, true);
	mlx5e_set_rq_type(mdev, params);
	mlx5e_init_rq_type_params(mdev, params);
पूर्ण

/* Build queue parameters */

व्योम mlx5e_build_create_cq_param(काष्ठा mlx5e_create_cq_param *ccp, काष्ठा mlx5e_channel *c)
अणु
	*ccp = (काष्ठा mlx5e_create_cq_param) अणु
		.napi = &c->napi,
		.ch_stats = c->stats,
		.node = cpu_to_node(c->cpu),
		.ix = c->ix,
	पूर्ण;
पूर्ण

#घोषणा DEFAULT_FRAG_SIZE (2048)

अटल व्योम mlx5e_build_rq_frags_info(काष्ठा mlx5_core_dev *mdev,
				      काष्ठा mlx5e_params *params,
				      काष्ठा mlx5e_xsk_param *xsk,
				      काष्ठा mlx5e_rq_frags_info *info)
अणु
	u32 byte_count = MLX5E_SW2HW_MTU(params, params->sw_mtu);
	पूर्णांक frag_size_max = DEFAULT_FRAG_SIZE;
	u32 buf_size = 0;
	पूर्णांक i;

	अगर (mlx5_fpga_is_ipsec_device(mdev))
		byte_count += MLX5E_METADATA_ETHER_LEN;

	अगर (mlx5e_rx_is_linear_skb(params, xsk)) अणु
		पूर्णांक frag_stride;

		frag_stride = mlx5e_rx_get_linear_frag_sz(params, xsk);
		frag_stride = roundup_घात_of_two(frag_stride);

		info->arr[0].frag_size = byte_count;
		info->arr[0].frag_stride = frag_stride;
		info->num_frags = 1;
		info->wqe_bulk = PAGE_SIZE / frag_stride;
		जाओ out;
	पूर्ण

	अगर (byte_count > PAGE_SIZE +
	    (MLX5E_MAX_RX_FRAGS - 1) * frag_size_max)
		frag_size_max = PAGE_SIZE;

	i = 0;
	जबतक (buf_size < byte_count) अणु
		पूर्णांक frag_size = byte_count - buf_size;

		अगर (i < MLX5E_MAX_RX_FRAGS - 1)
			frag_size = min(frag_size, frag_size_max);

		info->arr[i].frag_size = frag_size;
		info->arr[i].frag_stride = roundup_घात_of_two(frag_size);

		buf_size += frag_size;
		i++;
	पूर्ण
	info->num_frags = i;
	/* number of dअगरferent wqes sharing a page */
	info->wqe_bulk = 1 + (info->num_frags % 2);

out:
	info->wqe_bulk = max_t(u8, info->wqe_bulk, 8);
	info->log_num_frags = order_base_2(info->num_frags);
पूर्ण

अटल u8 mlx5e_get_rqwq_log_stride(u8 wq_type, पूर्णांक ndsegs)
अणु
	पूर्णांक sz = माप(काष्ठा mlx5_wqe_data_seg) * ndsegs;

	चयन (wq_type) अणु
	हाल MLX5_WQ_TYPE_LINKED_LIST_STRIDING_RQ:
		sz += माप(काष्ठा mlx5e_rx_wqe_ll);
		अवरोध;
	शेष: /* MLX5_WQ_TYPE_CYCLIC */
		sz += माप(काष्ठा mlx5e_rx_wqe_cyc);
	पूर्ण

	वापस order_base_2(sz);
पूर्ण

अटल व्योम mlx5e_build_common_cq_param(काष्ठा mlx5_core_dev *mdev,
					काष्ठा mlx5e_cq_param *param)
अणु
	व्योम *cqc = param->cqc;

	MLX5_SET(cqc, cqc, uar_page, mdev->priv.uar->index);
	अगर (MLX5_CAP_GEN(mdev, cqe_128_always) && cache_line_size() >= 128)
		MLX5_SET(cqc, cqc, cqe_sz, CQE_STRIDE_128_PAD);
पूर्ण

अटल व्योम mlx5e_build_rx_cq_param(काष्ठा mlx5_core_dev *mdev,
				    काष्ठा mlx5e_params *params,
				    काष्ठा mlx5e_xsk_param *xsk,
				    काष्ठा mlx5e_cq_param *param)
अणु
	bool hw_stridx = false;
	व्योम *cqc = param->cqc;
	u8 log_cq_size;

	चयन (params->rq_wq_type) अणु
	हाल MLX5_WQ_TYPE_LINKED_LIST_STRIDING_RQ:
		log_cq_size = mlx5e_mpwqe_get_log_rq_size(params, xsk) +
			mlx5e_mpwqe_get_log_num_strides(mdev, params, xsk);
		hw_stridx = MLX5_CAP_GEN(mdev, mini_cqe_resp_stride_index);
		अवरोध;
	शेष: /* MLX5_WQ_TYPE_CYCLIC */
		log_cq_size = params->log_rq_mtu_frames;
	पूर्ण

	MLX5_SET(cqc, cqc, log_cq_size, log_cq_size);
	अगर (MLX5E_GET_PFLAG(params, MLX5E_PFLAG_RX_CQE_COMPRESS)) अणु
		MLX5_SET(cqc, cqc, mini_cqe_res_क्रमmat, hw_stridx ?
			 MLX5_CQE_FORMAT_CSUM_STRIDX : MLX5_CQE_FORMAT_CSUM);
		MLX5_SET(cqc, cqc, cqe_comp_en, 1);
	पूर्ण

	mlx5e_build_common_cq_param(mdev, param);
	param->cq_period_mode = params->rx_cq_moderation.cq_period_mode;
पूर्ण

पूर्णांक mlx5e_build_rq_param(काष्ठा mlx5_core_dev *mdev,
			 काष्ठा mlx5e_params *params,
			 काष्ठा mlx5e_xsk_param *xsk,
			 u16 q_counter,
			 काष्ठा mlx5e_rq_param *param)
अणु
	व्योम *rqc = param->rqc;
	व्योम *wq = MLX5_ADDR_OF(rqc, rqc, wq);
	पूर्णांक ndsegs = 1;

	चयन (params->rq_wq_type) अणु
	हाल MLX5_WQ_TYPE_LINKED_LIST_STRIDING_RQ: अणु
		u8 log_wqe_num_of_strides = mlx5e_mpwqe_get_log_num_strides(mdev, params, xsk);
		u8 log_wqe_stride_size = mlx5e_mpwqe_get_log_stride_size(mdev, params, xsk);

		अगर (!mlx5e_verअगरy_rx_mpwqe_strides(mdev, log_wqe_stride_size,
						   log_wqe_num_of_strides)) अणु
			mlx5_core_err(mdev,
				      "Bad RX MPWQE params: log_stride_size %u, log_num_strides %u\n",
				      log_wqe_stride_size, log_wqe_num_of_strides);
			वापस -EINVAL;
		पूर्ण

		MLX5_SET(wq, wq, log_wqe_num_of_strides,
			 log_wqe_num_of_strides - MLX5_MPWQE_LOG_NUM_STRIDES_BASE);
		MLX5_SET(wq, wq, log_wqe_stride_size,
			 log_wqe_stride_size - MLX5_MPWQE_LOG_STRIDE_SZ_BASE);
		MLX5_SET(wq, wq, log_wq_sz, mlx5e_mpwqe_get_log_rq_size(params, xsk));
		अवरोध;
	पूर्ण
	शेष: /* MLX5_WQ_TYPE_CYCLIC */
		MLX5_SET(wq, wq, log_wq_sz, params->log_rq_mtu_frames);
		mlx5e_build_rq_frags_info(mdev, params, xsk, &param->frags_info);
		ndsegs = param->frags_info.num_frags;
	पूर्ण

	MLX5_SET(wq, wq, wq_type,          params->rq_wq_type);
	MLX5_SET(wq, wq, end_padding_mode, MLX5_WQ_END_PAD_MODE_ALIGN);
	MLX5_SET(wq, wq, log_wq_stride,
		 mlx5e_get_rqwq_log_stride(params->rq_wq_type, ndsegs));
	MLX5_SET(wq, wq, pd,               mdev->mlx5e_res.hw_objs.pdn);
	MLX5_SET(rqc, rqc, counter_set_id, q_counter);
	MLX5_SET(rqc, rqc, vsd,            params->vlan_strip_disable);
	MLX5_SET(rqc, rqc, scatter_fcs,    params->scatter_fcs_en);

	param->wq.buf_numa_node = dev_to_node(mlx5_core_dma_dev(mdev));
	mlx5e_build_rx_cq_param(mdev, params, xsk, &param->cqp);

	वापस 0;
पूर्ण

व्योम mlx5e_build_drop_rq_param(काष्ठा mlx5_core_dev *mdev,
			       u16 q_counter,
			       काष्ठा mlx5e_rq_param *param)
अणु
	व्योम *rqc = param->rqc;
	व्योम *wq = MLX5_ADDR_OF(rqc, rqc, wq);

	MLX5_SET(wq, wq, wq_type, MLX5_WQ_TYPE_CYCLIC);
	MLX5_SET(wq, wq, log_wq_stride,
		 mlx5e_get_rqwq_log_stride(MLX5_WQ_TYPE_CYCLIC, 1));
	MLX5_SET(rqc, rqc, counter_set_id, q_counter);

	param->wq.buf_numa_node = dev_to_node(mlx5_core_dma_dev(mdev));
पूर्ण

व्योम mlx5e_build_tx_cq_param(काष्ठा mlx5_core_dev *mdev,
			     काष्ठा mlx5e_params *params,
			     काष्ठा mlx5e_cq_param *param)
अणु
	व्योम *cqc = param->cqc;

	MLX5_SET(cqc, cqc, log_cq_size, params->log_sq_size);

	mlx5e_build_common_cq_param(mdev, param);
	param->cq_period_mode = params->tx_cq_moderation.cq_period_mode;
पूर्ण

व्योम mlx5e_build_sq_param_common(काष्ठा mlx5_core_dev *mdev,
				 काष्ठा mlx5e_sq_param *param)
अणु
	व्योम *sqc = param->sqc;
	व्योम *wq = MLX5_ADDR_OF(sqc, sqc, wq);

	MLX5_SET(wq, wq, log_wq_stride, ilog2(MLX5_SEND_WQE_BB));
	MLX5_SET(wq, wq, pd,            mdev->mlx5e_res.hw_objs.pdn);

	param->wq.buf_numa_node = dev_to_node(mlx5_core_dma_dev(mdev));
पूर्ण

व्योम mlx5e_build_sq_param(काष्ठा mlx5_core_dev *mdev,
			  काष्ठा mlx5e_params *params,
			  काष्ठा mlx5e_sq_param *param)
अणु
	व्योम *sqc = param->sqc;
	व्योम *wq = MLX5_ADDR_OF(sqc, sqc, wq);
	bool allow_swp;

	allow_swp = mlx5_geneve_tx_allowed(mdev) ||
		    !!MLX5_IPSEC_DEV(mdev);
	mlx5e_build_sq_param_common(mdev, param);
	MLX5_SET(wq, wq, log_wq_sz, params->log_sq_size);
	MLX5_SET(sqc, sqc, allow_swp, allow_swp);
	param->is_mpw = MLX5E_GET_PFLAG(params, MLX5E_PFLAG_SKB_TX_MPWQE);
	param->stop_room = mlx5e_calc_sq_stop_room(mdev, params);
	mlx5e_build_tx_cq_param(mdev, params, &param->cqp);
पूर्ण

अटल व्योम mlx5e_build_ico_cq_param(काष्ठा mlx5_core_dev *mdev,
				     u8 log_wq_size,
				     काष्ठा mlx5e_cq_param *param)
अणु
	व्योम *cqc = param->cqc;

	MLX5_SET(cqc, cqc, log_cq_size, log_wq_size);

	mlx5e_build_common_cq_param(mdev, param);

	param->cq_period_mode = DIM_CQ_PERIOD_MODE_START_FROM_EQE;
पूर्ण

अटल u8 mlx5e_get_rq_log_wq_sz(व्योम *rqc)
अणु
	व्योम *wq = MLX5_ADDR_OF(rqc, rqc, wq);

	वापस MLX5_GET(wq, wq, log_wq_sz);
पूर्ण

अटल u8 mlx5e_build_icosq_log_wq_sz(काष्ठा mlx5e_params *params,
				      काष्ठा mlx5e_rq_param *rqp)
अणु
	चयन (params->rq_wq_type) अणु
	हाल MLX5_WQ_TYPE_LINKED_LIST_STRIDING_RQ:
		वापस max_t(u8, MLX5E_PARAMS_MINIMUM_LOG_SQ_SIZE,
			     order_base_2(MLX5E_UMR_WQEBBS) +
			     mlx5e_get_rq_log_wq_sz(rqp->rqc));
	शेष: /* MLX5_WQ_TYPE_CYCLIC */
		वापस MLX5E_PARAMS_MINIMUM_LOG_SQ_SIZE;
	पूर्ण
पूर्ण

अटल u8 mlx5e_build_async_icosq_log_wq_sz(काष्ठा mlx5_core_dev *mdev)
अणु
	अगर (mlx5_accel_is_ktls_rx(mdev))
		वापस MLX5E_PARAMS_DEFAULT_LOG_SQ_SIZE;

	वापस MLX5E_PARAMS_MINIMUM_LOG_SQ_SIZE;
पूर्ण

अटल व्योम mlx5e_build_icosq_param(काष्ठा mlx5_core_dev *mdev,
				    u8 log_wq_size,
				    काष्ठा mlx5e_sq_param *param)
अणु
	व्योम *sqc = param->sqc;
	व्योम *wq = MLX5_ADDR_OF(sqc, sqc, wq);

	mlx5e_build_sq_param_common(mdev, param);

	MLX5_SET(wq, wq, log_wq_sz, log_wq_size);
	MLX5_SET(sqc, sqc, reg_umr, MLX5_CAP_ETH(mdev, reg_umr_sq));
	mlx5e_build_ico_cq_param(mdev, log_wq_size, &param->cqp);
पूर्ण

अटल व्योम mlx5e_build_async_icosq_param(काष्ठा mlx5_core_dev *mdev,
					  u8 log_wq_size,
					  काष्ठा mlx5e_sq_param *param)
अणु
	व्योम *sqc = param->sqc;
	व्योम *wq = MLX5_ADDR_OF(sqc, sqc, wq);

	mlx5e_build_sq_param_common(mdev, param);
	param->stop_room = mlx5e_stop_room_क्रम_wqe(1); /* क्रम XSK NOP */
	param->is_tls = mlx5_accel_is_ktls_rx(mdev);
	अगर (param->is_tls)
		param->stop_room += mlx5e_stop_room_क्रम_wqe(1); /* क्रम TLS RX resync NOP */
	MLX5_SET(sqc, sqc, reg_umr, MLX5_CAP_ETH(mdev, reg_umr_sq));
	MLX5_SET(wq, wq, log_wq_sz, log_wq_size);
	mlx5e_build_ico_cq_param(mdev, log_wq_size, &param->cqp);
पूर्ण

व्योम mlx5e_build_xdpsq_param(काष्ठा mlx5_core_dev *mdev,
			     काष्ठा mlx5e_params *params,
			     काष्ठा mlx5e_sq_param *param)
अणु
	व्योम *sqc = param->sqc;
	व्योम *wq = MLX5_ADDR_OF(sqc, sqc, wq);

	mlx5e_build_sq_param_common(mdev, param);
	MLX5_SET(wq, wq, log_wq_sz, params->log_sq_size);
	param->is_mpw = MLX5E_GET_PFLAG(params, MLX5E_PFLAG_XDP_TX_MPWQE);
	mlx5e_build_tx_cq_param(mdev, params, &param->cqp);
पूर्ण

पूर्णांक mlx5e_build_channel_param(काष्ठा mlx5_core_dev *mdev,
			      काष्ठा mlx5e_params *params,
			      u16 q_counter,
			      काष्ठा mlx5e_channel_param *cparam)
अणु
	u8 icosq_log_wq_sz, async_icosq_log_wq_sz;
	पूर्णांक err;

	err = mlx5e_build_rq_param(mdev, params, शून्य, q_counter, &cparam->rq);
	अगर (err)
		वापस err;

	icosq_log_wq_sz = mlx5e_build_icosq_log_wq_sz(params, &cparam->rq);
	async_icosq_log_wq_sz = mlx5e_build_async_icosq_log_wq_sz(mdev);

	mlx5e_build_sq_param(mdev, params, &cparam->txq_sq);
	mlx5e_build_xdpsq_param(mdev, params, &cparam->xdp_sq);
	mlx5e_build_icosq_param(mdev, icosq_log_wq_sz, &cparam->icosq);
	mlx5e_build_async_icosq_param(mdev, async_icosq_log_wq_sz, &cparam->async_icosq);

	वापस 0;
पूर्ण
