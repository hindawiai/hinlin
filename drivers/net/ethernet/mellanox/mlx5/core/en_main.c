<शैली गुरु>
/*
 * Copyright (c) 2015-2016, Mellanox Technologies. All rights reserved.
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

#समावेश <net/tc_act/tc_gact.h>
#समावेश <net/pkt_cls.h>
#समावेश <linux/mlx5/fs.h>
#समावेश <net/vxlan.h>
#समावेश <net/geneve.h>
#समावेश <linux/bpf.h>
#समावेश <linux/अगर_bridge.h>
#समावेश <net/page_pool.h>
#समावेश <net/xdp_sock_drv.h>
#समावेश "eswitch.h"
#समावेश "en.h"
#समावेश "en/txrx.h"
#समावेश "en_tc.h"
#समावेश "en_rep.h"
#समावेश "en_accel/ipsec.h"
#समावेश "en_accel/en_accel.h"
#समावेश "en_accel/tls.h"
#समावेश "accel/ipsec.h"
#समावेश "accel/tls.h"
#समावेश "lib/vxlan.h"
#समावेश "lib/clock.h"
#समावेश "en/port.h"
#समावेश "en/xdp.h"
#समावेश "lib/eq.h"
#समावेश "en/monitor_stats.h"
#समावेश "en/health.h"
#समावेश "en/params.h"
#समावेश "en/xsk/pool.h"
#समावेश "en/xsk/setup.h"
#समावेश "en/xsk/rx.h"
#समावेश "en/xsk/tx.h"
#समावेश "en/hv_vhca_stats.h"
#समावेश "en/devlink.h"
#समावेश "lib/mlx5.h"
#समावेश "en/ptp.h"
#समावेश "qos.h"
#समावेश "en/trap.h"
#समावेश "fpga/ipsec.h"

bool mlx5e_check_fragmented_striding_rq_cap(काष्ठा mlx5_core_dev *mdev)
अणु
	bool striding_rq_umr = MLX5_CAP_GEN(mdev, striding_rq) &&
		MLX5_CAP_GEN(mdev, umr_ptr_rlky) &&
		MLX5_CAP_ETH(mdev, reg_umr_sq);
	u16 max_wqe_sz_cap = MLX5_CAP_GEN(mdev, max_wqe_sz_sq);
	bool अंतरभूत_umr = MLX5E_UMR_WQE_INLINE_SZ <= max_wqe_sz_cap;

	अगर (!striding_rq_umr)
		वापस false;
	अगर (!अंतरभूत_umr) अणु
		mlx5_core_warn(mdev, "Cannot support Striding RQ: UMR WQE size (%d) exceeds maximum supported (%d).\n",
			       (पूर्णांक)MLX5E_UMR_WQE_INLINE_SZ, max_wqe_sz_cap);
		वापस false;
	पूर्ण
	वापस true;
पूर्ण

व्योम mlx5e_update_carrier(काष्ठा mlx5e_priv *priv)
अणु
	काष्ठा mlx5_core_dev *mdev = priv->mdev;
	u8 port_state;

	port_state = mlx5_query_vport_state(mdev,
					    MLX5_VPORT_STATE_OP_MOD_VNIC_VPORT,
					    0);

	अगर (port_state == VPORT_STATE_UP) अणु
		netdev_info(priv->netdev, "Link up\n");
		netअगर_carrier_on(priv->netdev);
	पूर्ण अन्यथा अणु
		netdev_info(priv->netdev, "Link down\n");
		netअगर_carrier_off(priv->netdev);
	पूर्ण
पूर्ण

अटल व्योम mlx5e_update_carrier_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mlx5e_priv *priv = container_of(work, काष्ठा mlx5e_priv,
					       update_carrier_work);

	mutex_lock(&priv->state_lock);
	अगर (test_bit(MLX5E_STATE_OPENED, &priv->state))
		अगर (priv->profile->update_carrier)
			priv->profile->update_carrier(priv);
	mutex_unlock(&priv->state_lock);
पूर्ण

अटल व्योम mlx5e_update_stats_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mlx5e_priv *priv = container_of(work, काष्ठा mlx5e_priv,
					       update_stats_work);

	mutex_lock(&priv->state_lock);
	priv->profile->update_stats(priv);
	mutex_unlock(&priv->state_lock);
पूर्ण

व्योम mlx5e_queue_update_stats(काष्ठा mlx5e_priv *priv)
अणु
	अगर (!priv->profile->update_stats)
		वापस;

	अगर (unlikely(test_bit(MLX5E_STATE_DESTROYING, &priv->state)))
		वापस;

	queue_work(priv->wq, &priv->update_stats_work);
पूर्ण

अटल पूर्णांक async_event(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ event, व्योम *data)
अणु
	काष्ठा mlx5e_priv *priv = container_of(nb, काष्ठा mlx5e_priv, events_nb);
	काष्ठा mlx5_eqe   *eqe = data;

	अगर (event != MLX5_EVENT_TYPE_PORT_CHANGE)
		वापस NOTIFY_DONE;

	चयन (eqe->sub_type) अणु
	हाल MLX5_PORT_CHANGE_SUBTYPE_DOWN:
	हाल MLX5_PORT_CHANGE_SUBTYPE_ACTIVE:
		queue_work(priv->wq, &priv->update_carrier_work);
		अवरोध;
	शेष:
		वापस NOTIFY_DONE;
	पूर्ण

	वापस NOTIFY_OK;
पूर्ण

अटल व्योम mlx5e_enable_async_events(काष्ठा mlx5e_priv *priv)
अणु
	priv->events_nb.notअगरier_call = async_event;
	mlx5_notअगरier_रेजिस्टर(priv->mdev, &priv->events_nb);
पूर्ण

अटल व्योम mlx5e_disable_async_events(काष्ठा mlx5e_priv *priv)
अणु
	mlx5_notअगरier_unरेजिस्टर(priv->mdev, &priv->events_nb);
पूर्ण

अटल पूर्णांक blocking_event(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ event, व्योम *data)
अणु
	काष्ठा mlx5e_priv *priv = container_of(nb, काष्ठा mlx5e_priv, blocking_events_nb);
	पूर्णांक err;

	चयन (event) अणु
	हाल MLX5_DRIVER_EVENT_TYPE_TRAP:
		err = mlx5e_handle_trap_event(priv, data);
		अवरोध;
	शेष:
		netdev_warn(priv->netdev, "Sync event: Unknown event %ld\n", event);
		err = -EINVAL;
	पूर्ण
	वापस err;
पूर्ण

अटल व्योम mlx5e_enable_blocking_events(काष्ठा mlx5e_priv *priv)
अणु
	priv->blocking_events_nb.notअगरier_call = blocking_event;
	mlx5_blocking_notअगरier_रेजिस्टर(priv->mdev, &priv->blocking_events_nb);
पूर्ण

अटल व्योम mlx5e_disable_blocking_events(काष्ठा mlx5e_priv *priv)
अणु
	mlx5_blocking_notअगरier_unरेजिस्टर(priv->mdev, &priv->blocking_events_nb);
पूर्ण

अटल अंतरभूत व्योम mlx5e_build_umr_wqe(काष्ठा mlx5e_rq *rq,
				       काष्ठा mlx5e_icosq *sq,
				       काष्ठा mlx5e_umr_wqe *wqe)
अणु
	काष्ठा mlx5_wqe_ctrl_seg      *cseg = &wqe->ctrl;
	काष्ठा mlx5_wqe_umr_ctrl_seg *ucseg = &wqe->uctrl;
	u8 ds_cnt = DIV_ROUND_UP(MLX5E_UMR_WQE_INLINE_SZ, MLX5_SEND_WQE_DS);

	cseg->qpn_ds    = cpu_to_be32((sq->sqn << MLX5_WQE_CTRL_QPN_SHIFT) |
				      ds_cnt);
	cseg->umr_mkey  = rq->mkey_be;

	ucseg->flags = MLX5_UMR_TRANSLATION_OFFSET_EN | MLX5_UMR_INLINE;
	ucseg->xlt_octowords =
		cpu_to_be16(MLX5_MTT_OCTW(MLX5_MPWRQ_PAGES_PER_WQE));
	ucseg->mkey_mask     = cpu_to_be64(MLX5_MKEY_MASK_FREE);
पूर्ण

अटल पूर्णांक mlx5e_rq_alloc_mpwqe_info(काष्ठा mlx5e_rq *rq, पूर्णांक node)
अणु
	पूर्णांक wq_sz = mlx5_wq_ll_get_size(&rq->mpwqe.wq);

	rq->mpwqe.info = kvzalloc_node(array_size(wq_sz,
						  माप(*rq->mpwqe.info)),
				       GFP_KERNEL, node);
	अगर (!rq->mpwqe.info)
		वापस -ENOMEM;

	mlx5e_build_umr_wqe(rq, rq->icosq, &rq->mpwqe.umr_wqe);

	वापस 0;
पूर्ण

अटल पूर्णांक mlx5e_create_umr_mkey(काष्ठा mlx5_core_dev *mdev,
				 u64 npages, u8 page_shअगरt,
				 काष्ठा mlx5_core_mkey *umr_mkey,
				 dma_addr_t filler_addr)
अणु
	काष्ठा mlx5_mtt *mtt;
	पूर्णांक inlen;
	व्योम *mkc;
	u32 *in;
	पूर्णांक err;
	पूर्णांक i;

	inlen = MLX5_ST_SZ_BYTES(create_mkey_in) + माप(*mtt) * npages;

	in = kvzalloc(inlen, GFP_KERNEL);
	अगर (!in)
		वापस -ENOMEM;

	mkc = MLX5_ADDR_OF(create_mkey_in, in, memory_key_mkey_entry);

	MLX5_SET(mkc, mkc, मुक्त, 1);
	MLX5_SET(mkc, mkc, umr_en, 1);
	MLX5_SET(mkc, mkc, lw, 1);
	MLX5_SET(mkc, mkc, lr, 1);
	MLX5_SET(mkc, mkc, access_mode_1_0, MLX5_MKC_ACCESS_MODE_MTT);
	mlx5e_mkey_set_relaxed_ordering(mdev, mkc);
	MLX5_SET(mkc, mkc, qpn, 0xffffff);
	MLX5_SET(mkc, mkc, pd, mdev->mlx5e_res.hw_objs.pdn);
	MLX5_SET64(mkc, mkc, len, npages << page_shअगरt);
	MLX5_SET(mkc, mkc, translations_octword_size,
		 MLX5_MTT_OCTW(npages));
	MLX5_SET(mkc, mkc, log_page_size, page_shअगरt);
	MLX5_SET(create_mkey_in, in, translations_octword_actual_size,
		 MLX5_MTT_OCTW(npages));

	/* Initialize the mkey with all MTTs poपूर्णांकing to a शेष
	 * page (filler_addr). When the channels are activated, UMR
	 * WQEs will redirect the RX WQEs to the actual memory from
	 * the RQ's pool, जबतक the gaps (wqe_overflow) reमुख्य mapped
	 * to the शेष page.
	 */
	mtt = MLX5_ADDR_OF(create_mkey_in, in, klm_pas_mtt);
	क्रम (i = 0 ; i < npages ; i++)
		mtt[i].ptag = cpu_to_be64(filler_addr);

	err = mlx5_core_create_mkey(mdev, umr_mkey, in, inlen);

	kvमुक्त(in);
	वापस err;
पूर्ण

अटल पूर्णांक mlx5e_create_rq_umr_mkey(काष्ठा mlx5_core_dev *mdev, काष्ठा mlx5e_rq *rq)
अणु
	u64 num_mtts = MLX5E_REQUIRED_MTTS(mlx5_wq_ll_get_size(&rq->mpwqe.wq));

	वापस mlx5e_create_umr_mkey(mdev, num_mtts, PAGE_SHIFT, &rq->umr_mkey,
				     rq->wqe_overflow.addr);
पूर्ण

अटल u64 mlx5e_get_mpwqe_offset(u16 wqe_ix)
अणु
	वापस MLX5E_REQUIRED_MTTS(wqe_ix) << PAGE_SHIFT;
पूर्ण

अटल व्योम mlx5e_init_frags_partition(काष्ठा mlx5e_rq *rq)
अणु
	काष्ठा mlx5e_wqe_frag_info next_frag = अणुपूर्ण;
	काष्ठा mlx5e_wqe_frag_info *prev = शून्य;
	पूर्णांक i;

	next_frag.di = &rq->wqe.di[0];

	क्रम (i = 0; i < mlx5_wq_cyc_get_size(&rq->wqe.wq); i++) अणु
		काष्ठा mlx5e_rq_frag_info *frag_info = &rq->wqe.info.arr[0];
		काष्ठा mlx5e_wqe_frag_info *frag =
			&rq->wqe.frags[i << rq->wqe.info.log_num_frags];
		पूर्णांक f;

		क्रम (f = 0; f < rq->wqe.info.num_frags; f++, frag++) अणु
			अगर (next_frag.offset + frag_info[f].frag_stride > PAGE_SIZE) अणु
				next_frag.di++;
				next_frag.offset = 0;
				अगर (prev)
					prev->last_in_page = true;
			पूर्ण
			*frag = next_frag;

			/* prepare next */
			next_frag.offset += frag_info[f].frag_stride;
			prev = frag;
		पूर्ण
	पूर्ण

	अगर (prev)
		prev->last_in_page = true;
पूर्ण

पूर्णांक mlx5e_init_di_list(काष्ठा mlx5e_rq *rq, पूर्णांक wq_sz, पूर्णांक node)
अणु
	पूर्णांक len = wq_sz << rq->wqe.info.log_num_frags;

	rq->wqe.di = kvzalloc_node(array_size(len, माप(*rq->wqe.di)), GFP_KERNEL, node);
	अगर (!rq->wqe.di)
		वापस -ENOMEM;

	mlx5e_init_frags_partition(rq);

	वापस 0;
पूर्ण

व्योम mlx5e_मुक्त_di_list(काष्ठा mlx5e_rq *rq)
अणु
	kvमुक्त(rq->wqe.di);
पूर्ण

अटल व्योम mlx5e_rq_err_cqe_work(काष्ठा work_काष्ठा *recover_work)
अणु
	काष्ठा mlx5e_rq *rq = container_of(recover_work, काष्ठा mlx5e_rq, recover_work);

	mlx5e_reporter_rq_cqe_err(rq);
पूर्ण

अटल पूर्णांक mlx5e_alloc_mpwqe_rq_drop_page(काष्ठा mlx5e_rq *rq)
अणु
	rq->wqe_overflow.page = alloc_page(GFP_KERNEL);
	अगर (!rq->wqe_overflow.page)
		वापस -ENOMEM;

	rq->wqe_overflow.addr = dma_map_page(rq->pdev, rq->wqe_overflow.page, 0,
					     PAGE_SIZE, rq->buff.map_dir);
	अगर (dma_mapping_error(rq->pdev, rq->wqe_overflow.addr)) अणु
		__मुक्त_page(rq->wqe_overflow.page);
		वापस -ENOMEM;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम mlx5e_मुक्त_mpwqe_rq_drop_page(काष्ठा mlx5e_rq *rq)
अणु
	 dma_unmap_page(rq->pdev, rq->wqe_overflow.addr, PAGE_SIZE,
			rq->buff.map_dir);
	 __मुक्त_page(rq->wqe_overflow.page);
पूर्ण

अटल पूर्णांक mlx5e_init_rxq_rq(काष्ठा mlx5e_channel *c, काष्ठा mlx5e_params *params,
			     काष्ठा mlx5e_rq *rq)
अणु
	काष्ठा mlx5_core_dev *mdev = c->mdev;
	पूर्णांक err;

	rq->wq_type      = params->rq_wq_type;
	rq->pdev         = c->pdev;
	rq->netdev       = c->netdev;
	rq->priv         = c->priv;
	rq->tstamp       = c->tstamp;
	rq->घड़ी        = &mdev->घड़ी;
	rq->icosq        = &c->icosq;
	rq->ix           = c->ix;
	rq->mdev         = mdev;
	rq->hw_mtu       = MLX5E_SW2HW_MTU(params, params->sw_mtu);
	rq->xdpsq        = &c->rq_xdpsq;
	rq->stats        = &c->priv->channel_stats[c->ix].rq;
	rq->ptp_cyc2समय = mlx5_rq_ts_translator(mdev);
	err = mlx5e_rq_set_handlers(rq, params, शून्य);
	अगर (err)
		वापस err;

	वापस xdp_rxq_info_reg(&rq->xdp_rxq, rq->netdev, rq->ix, 0);
पूर्ण

अटल पूर्णांक mlx5e_alloc_rq(काष्ठा mlx5e_params *params,
			  काष्ठा mlx5e_xsk_param *xsk,
			  काष्ठा mlx5e_rq_param *rqp,
			  पूर्णांक node, काष्ठा mlx5e_rq *rq)
अणु
	काष्ठा page_pool_params pp_params = अणु 0 पूर्ण;
	काष्ठा mlx5_core_dev *mdev = rq->mdev;
	व्योम *rqc = rqp->rqc;
	व्योम *rqc_wq = MLX5_ADDR_OF(rqc, rqc, wq);
	u32 pool_size;
	पूर्णांक wq_sz;
	पूर्णांक err;
	पूर्णांक i;

	rqp->wq.db_numa_node = node;
	INIT_WORK(&rq->recover_work, mlx5e_rq_err_cqe_work);

	अगर (params->xdp_prog)
		bpf_prog_inc(params->xdp_prog);
	RCU_INIT_POINTER(rq->xdp_prog, params->xdp_prog);

	rq->buff.map_dir = params->xdp_prog ? DMA_BIसूचीECTIONAL : DMA_FROM_DEVICE;
	rq->buff.headroom = mlx5e_get_rq_headroom(mdev, params, xsk);
	pool_size = 1 << params->log_rq_mtu_frames;

	चयन (rq->wq_type) अणु
	हाल MLX5_WQ_TYPE_LINKED_LIST_STRIDING_RQ:
		err = mlx5_wq_ll_create(mdev, &rqp->wq, rqc_wq, &rq->mpwqe.wq,
					&rq->wq_ctrl);
		अगर (err)
			जाओ err_rq_xdp_prog;

		err = mlx5e_alloc_mpwqe_rq_drop_page(rq);
		अगर (err)
			जाओ err_rq_wq_destroy;

		rq->mpwqe.wq.db = &rq->mpwqe.wq.db[MLX5_RCV_DBR];

		wq_sz = mlx5_wq_ll_get_size(&rq->mpwqe.wq);

		pool_size = MLX5_MPWRQ_PAGES_PER_WQE <<
			mlx5e_mpwqe_get_log_rq_size(params, xsk);

		rq->mpwqe.log_stride_sz = mlx5e_mpwqe_get_log_stride_size(mdev, params, xsk);
		rq->mpwqe.num_strides =
			BIT(mlx5e_mpwqe_get_log_num_strides(mdev, params, xsk));

		rq->buff.frame0_sz = (1 << rq->mpwqe.log_stride_sz);

		err = mlx5e_create_rq_umr_mkey(mdev, rq);
		अगर (err)
			जाओ err_rq_drop_page;
		rq->mkey_be = cpu_to_be32(rq->umr_mkey.key);

		err = mlx5e_rq_alloc_mpwqe_info(rq, node);
		अगर (err)
			जाओ err_rq_mkey;
		अवरोध;
	शेष: /* MLX5_WQ_TYPE_CYCLIC */
		err = mlx5_wq_cyc_create(mdev, &rqp->wq, rqc_wq, &rq->wqe.wq,
					 &rq->wq_ctrl);
		अगर (err)
			जाओ err_rq_xdp_prog;

		rq->wqe.wq.db = &rq->wqe.wq.db[MLX5_RCV_DBR];

		wq_sz = mlx5_wq_cyc_get_size(&rq->wqe.wq);

		rq->wqe.info = rqp->frags_info;
		rq->buff.frame0_sz = rq->wqe.info.arr[0].frag_stride;

		rq->wqe.frags =
			kvzalloc_node(array_size(माप(*rq->wqe.frags),
					(wq_sz << rq->wqe.info.log_num_frags)),
				      GFP_KERNEL, node);
		अगर (!rq->wqe.frags) अणु
			err = -ENOMEM;
			जाओ err_rq_wq_destroy;
		पूर्ण

		err = mlx5e_init_di_list(rq, wq_sz, node);
		अगर (err)
			जाओ err_rq_frags;

		rq->mkey_be = cpu_to_be32(mdev->mlx5e_res.hw_objs.mkey.key);
	पूर्ण

	अगर (xsk) अणु
		err = xdp_rxq_info_reg_mem_model(&rq->xdp_rxq,
						 MEM_TYPE_XSK_BUFF_POOL, शून्य);
		xsk_pool_set_rxq_info(rq->xsk_pool, &rq->xdp_rxq);
	पूर्ण अन्यथा अणु
		/* Create a page_pool and रेजिस्टर it with rxq */
		pp_params.order     = 0;
		pp_params.flags     = 0; /* No-पूर्णांकernal DMA mapping in page_pool */
		pp_params.pool_size = pool_size;
		pp_params.nid       = node;
		pp_params.dev       = rq->pdev;
		pp_params.dma_dir   = rq->buff.map_dir;

		/* page_pool can be used even when there is no rq->xdp_prog,
		 * given page_pool करोes not handle DMA mapping there is no
		 * required state to clear. And page_pool gracefully handle
		 * elevated refcnt.
		 */
		rq->page_pool = page_pool_create(&pp_params);
		अगर (IS_ERR(rq->page_pool)) अणु
			err = PTR_ERR(rq->page_pool);
			rq->page_pool = शून्य;
			जाओ err_मुक्त_by_rq_type;
		पूर्ण
		अगर (xdp_rxq_info_is_reg(&rq->xdp_rxq))
			err = xdp_rxq_info_reg_mem_model(&rq->xdp_rxq,
							 MEM_TYPE_PAGE_POOL, rq->page_pool);
	पूर्ण
	अगर (err)
		जाओ err_मुक्त_by_rq_type;

	क्रम (i = 0; i < wq_sz; i++) अणु
		अगर (rq->wq_type == MLX5_WQ_TYPE_LINKED_LIST_STRIDING_RQ) अणु
			काष्ठा mlx5e_rx_wqe_ll *wqe =
				mlx5_wq_ll_get_wqe(&rq->mpwqe.wq, i);
			u32 byte_count =
				rq->mpwqe.num_strides << rq->mpwqe.log_stride_sz;
			u64 dma_offset = mlx5e_get_mpwqe_offset(i);

			wqe->data[0].addr = cpu_to_be64(dma_offset + rq->buff.headroom);
			wqe->data[0].byte_count = cpu_to_be32(byte_count);
			wqe->data[0].lkey = rq->mkey_be;
		पूर्ण अन्यथा अणु
			काष्ठा mlx5e_rx_wqe_cyc *wqe =
				mlx5_wq_cyc_get_wqe(&rq->wqe.wq, i);
			पूर्णांक f;

			क्रम (f = 0; f < rq->wqe.info.num_frags; f++) अणु
				u32 frag_size = rq->wqe.info.arr[f].frag_size |
					MLX5_HW_START_PADDING;

				wqe->data[f].byte_count = cpu_to_be32(frag_size);
				wqe->data[f].lkey = rq->mkey_be;
			पूर्ण
			/* check अगर num_frags is not a घात of two */
			अगर (rq->wqe.info.num_frags < (1 << rq->wqe.info.log_num_frags)) अणु
				wqe->data[f].byte_count = 0;
				wqe->data[f].lkey = cpu_to_be32(MLX5_INVALID_LKEY);
				wqe->data[f].addr = 0;
			पूर्ण
		पूर्ण
	पूर्ण

	INIT_WORK(&rq->dim.work, mlx5e_rx_dim_work);

	चयन (params->rx_cq_moderation.cq_period_mode) अणु
	हाल MLX5_CQ_PERIOD_MODE_START_FROM_CQE:
		rq->dim.mode = DIM_CQ_PERIOD_MODE_START_FROM_CQE;
		अवरोध;
	हाल MLX5_CQ_PERIOD_MODE_START_FROM_EQE:
	शेष:
		rq->dim.mode = DIM_CQ_PERIOD_MODE_START_FROM_EQE;
	पूर्ण

	rq->page_cache.head = 0;
	rq->page_cache.tail = 0;

	वापस 0;

err_मुक्त_by_rq_type:
	चयन (rq->wq_type) अणु
	हाल MLX5_WQ_TYPE_LINKED_LIST_STRIDING_RQ:
		kvमुक्त(rq->mpwqe.info);
err_rq_mkey:
		mlx5_core_destroy_mkey(mdev, &rq->umr_mkey);
err_rq_drop_page:
		mlx5e_मुक्त_mpwqe_rq_drop_page(rq);
		अवरोध;
	शेष: /* MLX5_WQ_TYPE_CYCLIC */
		mlx5e_मुक्त_di_list(rq);
err_rq_frags:
		kvमुक्त(rq->wqe.frags);
	पूर्ण
err_rq_wq_destroy:
	mlx5_wq_destroy(&rq->wq_ctrl);
err_rq_xdp_prog:
	अगर (params->xdp_prog)
		bpf_prog_put(params->xdp_prog);

	वापस err;
पूर्ण

अटल व्योम mlx5e_मुक्त_rq(काष्ठा mlx5e_rq *rq)
अणु
	काष्ठा bpf_prog *old_prog;
	पूर्णांक i;

	अगर (xdp_rxq_info_is_reg(&rq->xdp_rxq)) अणु
		old_prog = rcu_dereference_रक्षित(rq->xdp_prog,
						     lockdep_is_held(&rq->priv->state_lock));
		अगर (old_prog)
			bpf_prog_put(old_prog);
	पूर्ण

	चयन (rq->wq_type) अणु
	हाल MLX5_WQ_TYPE_LINKED_LIST_STRIDING_RQ:
		kvमुक्त(rq->mpwqe.info);
		mlx5_core_destroy_mkey(rq->mdev, &rq->umr_mkey);
		mlx5e_मुक्त_mpwqe_rq_drop_page(rq);
		अवरोध;
	शेष: /* MLX5_WQ_TYPE_CYCLIC */
		kvमुक्त(rq->wqe.frags);
		mlx5e_मुक्त_di_list(rq);
	पूर्ण

	क्रम (i = rq->page_cache.head; i != rq->page_cache.tail;
	     i = (i + 1) & (MLX5E_CACHE_SIZE - 1)) अणु
		काष्ठा mlx5e_dma_info *dma_info = &rq->page_cache.page_cache[i];

		/* With AF_XDP, page_cache is not used, so this loop is not
		 * entered, and it's safe to call mlx5e_page_release_dynamic
		 * directly.
		 */
		mlx5e_page_release_dynamic(rq, dma_info, false);
	पूर्ण

	xdp_rxq_info_unreg(&rq->xdp_rxq);
	page_pool_destroy(rq->page_pool);
	mlx5_wq_destroy(&rq->wq_ctrl);
पूर्ण

पूर्णांक mlx5e_create_rq(काष्ठा mlx5e_rq *rq, काष्ठा mlx5e_rq_param *param)
अणु
	काष्ठा mlx5_core_dev *mdev = rq->mdev;
	u8 ts_क्रमmat;
	व्योम *in;
	व्योम *rqc;
	व्योम *wq;
	पूर्णांक inlen;
	पूर्णांक err;

	inlen = MLX5_ST_SZ_BYTES(create_rq_in) +
		माप(u64) * rq->wq_ctrl.buf.npages;
	in = kvzalloc(inlen, GFP_KERNEL);
	अगर (!in)
		वापस -ENOMEM;

	ts_क्रमmat = mlx5_is_real_समय_rq(mdev) ?
		    MLX5_RQC_TIMESTAMP_FORMAT_REAL_TIME :
		    MLX5_RQC_TIMESTAMP_FORMAT_FREE_RUNNING;
	rqc = MLX5_ADDR_OF(create_rq_in, in, ctx);
	wq  = MLX5_ADDR_OF(rqc, rqc, wq);

	स_नकल(rqc, param->rqc, माप(param->rqc));

	MLX5_SET(rqc,  rqc, cqn,		rq->cq.mcq.cqn);
	MLX5_SET(rqc,  rqc, state,		MLX5_RQC_STATE_RST);
	MLX5_SET(rqc,  rqc, ts_क्रमmat,		ts_क्रमmat);
	MLX5_SET(wq,   wq,  log_wq_pg_sz,	rq->wq_ctrl.buf.page_shअगरt -
						MLX5_ADAPTER_PAGE_SHIFT);
	MLX5_SET64(wq, wq,  dbr_addr,		rq->wq_ctrl.db.dma);

	mlx5_fill_page_frag_array(&rq->wq_ctrl.buf,
				  (__be64 *)MLX5_ADDR_OF(wq, wq, pas));

	err = mlx5_core_create_rq(mdev, in, inlen, &rq->rqn);

	kvमुक्त(in);

	वापस err;
पूर्ण

पूर्णांक mlx5e_modअगरy_rq_state(काष्ठा mlx5e_rq *rq, पूर्णांक curr_state, पूर्णांक next_state)
अणु
	काष्ठा mlx5_core_dev *mdev = rq->mdev;

	व्योम *in;
	व्योम *rqc;
	पूर्णांक inlen;
	पूर्णांक err;

	inlen = MLX5_ST_SZ_BYTES(modअगरy_rq_in);
	in = kvzalloc(inlen, GFP_KERNEL);
	अगर (!in)
		वापस -ENOMEM;

	अगर (curr_state == MLX5_RQC_STATE_RST && next_state == MLX5_RQC_STATE_RDY)
		mlx5e_rqwq_reset(rq);

	rqc = MLX5_ADDR_OF(modअगरy_rq_in, in, ctx);

	MLX5_SET(modअगरy_rq_in, in, rq_state, curr_state);
	MLX5_SET(rqc, rqc, state, next_state);

	err = mlx5_core_modअगरy_rq(mdev, rq->rqn, in);

	kvमुक्त(in);

	वापस err;
पूर्ण

अटल पूर्णांक mlx5e_modअगरy_rq_scatter_fcs(काष्ठा mlx5e_rq *rq, bool enable)
अणु
	काष्ठा mlx5_core_dev *mdev = rq->mdev;

	व्योम *in;
	व्योम *rqc;
	पूर्णांक inlen;
	पूर्णांक err;

	inlen = MLX5_ST_SZ_BYTES(modअगरy_rq_in);
	in = kvzalloc(inlen, GFP_KERNEL);
	अगर (!in)
		वापस -ENOMEM;

	rqc = MLX5_ADDR_OF(modअगरy_rq_in, in, ctx);

	MLX5_SET(modअगरy_rq_in, in, rq_state, MLX5_RQC_STATE_RDY);
	MLX5_SET64(modअगरy_rq_in, in, modअगरy_biपंचांगask,
		   MLX5_MODIFY_RQ_IN_MODIFY_BITMASK_SCATTER_FCS);
	MLX5_SET(rqc, rqc, scatter_fcs, enable);
	MLX5_SET(rqc, rqc, state, MLX5_RQC_STATE_RDY);

	err = mlx5_core_modअगरy_rq(mdev, rq->rqn, in);

	kvमुक्त(in);

	वापस err;
पूर्ण

अटल पूर्णांक mlx5e_modअगरy_rq_vsd(काष्ठा mlx5e_rq *rq, bool vsd)
अणु
	काष्ठा mlx5_core_dev *mdev = rq->mdev;
	व्योम *in;
	व्योम *rqc;
	पूर्णांक inlen;
	पूर्णांक err;

	inlen = MLX5_ST_SZ_BYTES(modअगरy_rq_in);
	in = kvzalloc(inlen, GFP_KERNEL);
	अगर (!in)
		वापस -ENOMEM;

	rqc = MLX5_ADDR_OF(modअगरy_rq_in, in, ctx);

	MLX5_SET(modअगरy_rq_in, in, rq_state, MLX5_RQC_STATE_RDY);
	MLX5_SET64(modअगरy_rq_in, in, modअगरy_biपंचांगask,
		   MLX5_MODIFY_RQ_IN_MODIFY_BITMASK_VSD);
	MLX5_SET(rqc, rqc, vsd, vsd);
	MLX5_SET(rqc, rqc, state, MLX5_RQC_STATE_RDY);

	err = mlx5_core_modअगरy_rq(mdev, rq->rqn, in);

	kvमुक्त(in);

	वापस err;
पूर्ण

व्योम mlx5e_destroy_rq(काष्ठा mlx5e_rq *rq)
अणु
	mlx5_core_destroy_rq(rq->mdev, rq->rqn);
पूर्ण

पूर्णांक mlx5e_रुको_क्रम_min_rx_wqes(काष्ठा mlx5e_rq *rq, पूर्णांक रुको_समय)
अणु
	अचिन्हित दीर्घ exp_समय = jअगरfies + msecs_to_jअगरfies(रुको_समय);

	u16 min_wqes = mlx5_min_rx_wqes(rq->wq_type, mlx5e_rqwq_get_size(rq));

	करो अणु
		अगर (mlx5e_rqwq_get_cur_sz(rq) >= min_wqes)
			वापस 0;

		msleep(20);
	पूर्ण जबतक (समय_beक्रमe(jअगरfies, exp_समय));

	netdev_warn(rq->netdev, "Failed to get min RX wqes on Channel[%d] RQN[0x%x] wq cur_sz(%d) min_rx_wqes(%d)\n",
		    rq->ix, rq->rqn, mlx5e_rqwq_get_cur_sz(rq), min_wqes);

	mlx5e_reporter_rx_समयout(rq);
	वापस -ETIMEDOUT;
पूर्ण

व्योम mlx5e_मुक्त_rx_in_progress_descs(काष्ठा mlx5e_rq *rq)
अणु
	काष्ठा mlx5_wq_ll *wq;
	u16 head;
	पूर्णांक i;

	अगर (rq->wq_type != MLX5_WQ_TYPE_LINKED_LIST_STRIDING_RQ)
		वापस;

	wq = &rq->mpwqe.wq;
	head = wq->head;

	/* Outstanding UMR WQEs (in progress) start at wq->head */
	क्रम (i = 0; i < rq->mpwqe.umr_in_progress; i++) अणु
		rq->dealloc_wqe(rq, head);
		head = mlx5_wq_ll_get_wqe_next_ix(wq, head);
	पूर्ण

	rq->mpwqe.actual_wq_head = wq->head;
	rq->mpwqe.umr_in_progress = 0;
	rq->mpwqe.umr_completed = 0;
पूर्ण

व्योम mlx5e_मुक्त_rx_descs(काष्ठा mlx5e_rq *rq)
अणु
	__be16 wqe_ix_be;
	u16 wqe_ix;

	अगर (rq->wq_type == MLX5_WQ_TYPE_LINKED_LIST_STRIDING_RQ) अणु
		काष्ठा mlx5_wq_ll *wq = &rq->mpwqe.wq;

		mlx5e_मुक्त_rx_in_progress_descs(rq);

		जबतक (!mlx5_wq_ll_is_empty(wq)) अणु
			काष्ठा mlx5e_rx_wqe_ll *wqe;

			wqe_ix_be = *wq->tail_next;
			wqe_ix    = be16_to_cpu(wqe_ix_be);
			wqe       = mlx5_wq_ll_get_wqe(wq, wqe_ix);
			rq->dealloc_wqe(rq, wqe_ix);
			mlx5_wq_ll_pop(wq, wqe_ix_be,
				       &wqe->next.next_wqe_index);
		पूर्ण
	पूर्ण अन्यथा अणु
		काष्ठा mlx5_wq_cyc *wq = &rq->wqe.wq;

		जबतक (!mlx5_wq_cyc_is_empty(wq)) अणु
			wqe_ix = mlx5_wq_cyc_get_tail(wq);
			rq->dealloc_wqe(rq, wqe_ix);
			mlx5_wq_cyc_pop(wq);
		पूर्ण
	पूर्ण

पूर्ण

पूर्णांक mlx5e_खोलो_rq(काष्ठा mlx5e_params *params, काष्ठा mlx5e_rq_param *param,
		  काष्ठा mlx5e_xsk_param *xsk, पूर्णांक node,
		  काष्ठा mlx5e_rq *rq)
अणु
	काष्ठा mlx5_core_dev *mdev = rq->mdev;
	पूर्णांक err;

	err = mlx5e_alloc_rq(params, xsk, param, node, rq);
	अगर (err)
		वापस err;

	err = mlx5e_create_rq(rq, param);
	अगर (err)
		जाओ err_मुक्त_rq;

	err = mlx5e_modअगरy_rq_state(rq, MLX5_RQC_STATE_RST, MLX5_RQC_STATE_RDY);
	अगर (err)
		जाओ err_destroy_rq;

	अगर (mlx5e_is_tls_on(rq->priv) && !mlx5_accel_is_ktls_device(mdev))
		__set_bit(MLX5E_RQ_STATE_FPGA_TLS, &rq->state); /* must be FPGA */

	अगर (MLX5_CAP_ETH(mdev, cqe_checksum_full))
		__set_bit(MLX5E_RQ_STATE_CSUM_FULL, &rq->state);

	अगर (params->rx_dim_enabled)
		__set_bit(MLX5E_RQ_STATE_AM, &rq->state);

	/* We disable csum_complete when XDP is enabled since
	 * XDP programs might manipulate packets which will render
	 * skb->checksum incorrect.
	 */
	अगर (MLX5E_GET_PFLAG(params, MLX5E_PFLAG_RX_NO_CSUM_COMPLETE) || params->xdp_prog)
		__set_bit(MLX5E_RQ_STATE_NO_CSUM_COMPLETE, &rq->state);

	/* For CQE compression on striding RQ, use stride index provided by
	 * HW अगर capability is supported.
	 */
	अगर (MLX5E_GET_PFLAG(params, MLX5E_PFLAG_RX_STRIDING_RQ) &&
	    MLX5_CAP_GEN(mdev, mini_cqe_resp_stride_index))
		__set_bit(MLX5E_RQ_STATE_MINI_CQE_HW_STRIDX, &rq->state);

	वापस 0;

err_destroy_rq:
	mlx5e_destroy_rq(rq);
err_मुक्त_rq:
	mlx5e_मुक्त_rq(rq);

	वापस err;
पूर्ण

व्योम mlx5e_activate_rq(काष्ठा mlx5e_rq *rq)
अणु
	set_bit(MLX5E_RQ_STATE_ENABLED, &rq->state);
	अगर (rq->icosq) अणु
		mlx5e_trigger_irq(rq->icosq);
	पूर्ण अन्यथा अणु
		local_bh_disable();
		napi_schedule(rq->cq.napi);
		local_bh_enable();
	पूर्ण
पूर्ण

व्योम mlx5e_deactivate_rq(काष्ठा mlx5e_rq *rq)
अणु
	clear_bit(MLX5E_RQ_STATE_ENABLED, &rq->state);
	synchronize_net(); /* Sync with NAPI to prevent mlx5e_post_rx_wqes. */
पूर्ण

व्योम mlx5e_बंद_rq(काष्ठा mlx5e_rq *rq)
अणु
	cancel_work_sync(&rq->dim.work);
	अगर (rq->icosq)
		cancel_work_sync(&rq->icosq->recover_work);
	cancel_work_sync(&rq->recover_work);
	mlx5e_destroy_rq(rq);
	mlx5e_मुक्त_rx_descs(rq);
	mlx5e_मुक्त_rq(rq);
पूर्ण

अटल व्योम mlx5e_मुक्त_xdpsq_db(काष्ठा mlx5e_xdpsq *sq)
अणु
	kvमुक्त(sq->db.xdpi_fअगरo.xi);
	kvमुक्त(sq->db.wqe_info);
पूर्ण

अटल पूर्णांक mlx5e_alloc_xdpsq_fअगरo(काष्ठा mlx5e_xdpsq *sq, पूर्णांक numa)
अणु
	काष्ठा mlx5e_xdp_info_fअगरo *xdpi_fअगरo = &sq->db.xdpi_fअगरo;
	पूर्णांक wq_sz        = mlx5_wq_cyc_get_size(&sq->wq);
	पूर्णांक dsegs_per_wq = wq_sz * MLX5_SEND_WQEBB_NUM_DS;

	xdpi_fअगरo->xi = kvzalloc_node(माप(*xdpi_fअगरo->xi) * dsegs_per_wq,
				      GFP_KERNEL, numa);
	अगर (!xdpi_fअगरo->xi)
		वापस -ENOMEM;

	xdpi_fअगरo->pc   = &sq->xdpi_fअगरo_pc;
	xdpi_fअगरo->cc   = &sq->xdpi_fअगरo_cc;
	xdpi_fअगरo->mask = dsegs_per_wq - 1;

	वापस 0;
पूर्ण

अटल पूर्णांक mlx5e_alloc_xdpsq_db(काष्ठा mlx5e_xdpsq *sq, पूर्णांक numa)
अणु
	पूर्णांक wq_sz = mlx5_wq_cyc_get_size(&sq->wq);
	पूर्णांक err;

	sq->db.wqe_info = kvzalloc_node(माप(*sq->db.wqe_info) * wq_sz,
					GFP_KERNEL, numa);
	अगर (!sq->db.wqe_info)
		वापस -ENOMEM;

	err = mlx5e_alloc_xdpsq_fअगरo(sq, numa);
	अगर (err) अणु
		mlx5e_मुक्त_xdpsq_db(sq);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mlx5e_alloc_xdpsq(काष्ठा mlx5e_channel *c,
			     काष्ठा mlx5e_params *params,
			     काष्ठा xsk_buff_pool *xsk_pool,
			     काष्ठा mlx5e_sq_param *param,
			     काष्ठा mlx5e_xdpsq *sq,
			     bool is_redirect)
अणु
	व्योम *sqc_wq               = MLX5_ADDR_OF(sqc, param->sqc, wq);
	काष्ठा mlx5_core_dev *mdev = c->mdev;
	काष्ठा mlx5_wq_cyc *wq = &sq->wq;
	पूर्णांक err;

	sq->pdev      = c->pdev;
	sq->mkey_be   = c->mkey_be;
	sq->channel   = c;
	sq->uar_map   = mdev->mlx5e_res.hw_objs.bfreg.map;
	sq->min_अंतरभूत_mode = params->tx_min_अंतरभूत_mode;
	sq->hw_mtu    = MLX5E_SW2HW_MTU(params, params->sw_mtu);
	sq->xsk_pool  = xsk_pool;

	sq->stats = sq->xsk_pool ?
		&c->priv->channel_stats[c->ix].xsksq :
		is_redirect ?
			&c->priv->channel_stats[c->ix].xdpsq :
			&c->priv->channel_stats[c->ix].rq_xdpsq;

	param->wq.db_numa_node = cpu_to_node(c->cpu);
	err = mlx5_wq_cyc_create(mdev, &param->wq, sqc_wq, wq, &sq->wq_ctrl);
	अगर (err)
		वापस err;
	wq->db = &wq->db[MLX5_SND_DBR];

	err = mlx5e_alloc_xdpsq_db(sq, cpu_to_node(c->cpu));
	अगर (err)
		जाओ err_sq_wq_destroy;

	वापस 0;

err_sq_wq_destroy:
	mlx5_wq_destroy(&sq->wq_ctrl);

	वापस err;
पूर्ण

अटल व्योम mlx5e_मुक्त_xdpsq(काष्ठा mlx5e_xdpsq *sq)
अणु
	mlx5e_मुक्त_xdpsq_db(sq);
	mlx5_wq_destroy(&sq->wq_ctrl);
पूर्ण

अटल व्योम mlx5e_मुक्त_icosq_db(काष्ठा mlx5e_icosq *sq)
अणु
	kvमुक्त(sq->db.wqe_info);
पूर्ण

अटल पूर्णांक mlx5e_alloc_icosq_db(काष्ठा mlx5e_icosq *sq, पूर्णांक numa)
अणु
	पूर्णांक wq_sz = mlx5_wq_cyc_get_size(&sq->wq);
	माप_प्रकार size;

	size = array_size(wq_sz, माप(*sq->db.wqe_info));
	sq->db.wqe_info = kvzalloc_node(size, GFP_KERNEL, numa);
	अगर (!sq->db.wqe_info)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल व्योम mlx5e_icosq_err_cqe_work(काष्ठा work_काष्ठा *recover_work)
अणु
	काष्ठा mlx5e_icosq *sq = container_of(recover_work, काष्ठा mlx5e_icosq,
					      recover_work);

	mlx5e_reporter_icosq_cqe_err(sq);
पूर्ण

अटल पूर्णांक mlx5e_alloc_icosq(काष्ठा mlx5e_channel *c,
			     काष्ठा mlx5e_sq_param *param,
			     काष्ठा mlx5e_icosq *sq)
अणु
	व्योम *sqc_wq               = MLX5_ADDR_OF(sqc, param->sqc, wq);
	काष्ठा mlx5_core_dev *mdev = c->mdev;
	काष्ठा mlx5_wq_cyc *wq = &sq->wq;
	पूर्णांक err;

	sq->channel   = c;
	sq->uar_map   = mdev->mlx5e_res.hw_objs.bfreg.map;
	sq->reserved_room = param->stop_room;

	param->wq.db_numa_node = cpu_to_node(c->cpu);
	err = mlx5_wq_cyc_create(mdev, &param->wq, sqc_wq, wq, &sq->wq_ctrl);
	अगर (err)
		वापस err;
	wq->db = &wq->db[MLX5_SND_DBR];

	err = mlx5e_alloc_icosq_db(sq, cpu_to_node(c->cpu));
	अगर (err)
		जाओ err_sq_wq_destroy;

	INIT_WORK(&sq->recover_work, mlx5e_icosq_err_cqe_work);

	वापस 0;

err_sq_wq_destroy:
	mlx5_wq_destroy(&sq->wq_ctrl);

	वापस err;
पूर्ण

अटल व्योम mlx5e_मुक्त_icosq(काष्ठा mlx5e_icosq *sq)
अणु
	mlx5e_मुक्त_icosq_db(sq);
	mlx5_wq_destroy(&sq->wq_ctrl);
पूर्ण

व्योम mlx5e_मुक्त_txqsq_db(काष्ठा mlx5e_txqsq *sq)
अणु
	kvमुक्त(sq->db.wqe_info);
	kvमुक्त(sq->db.skb_fअगरo.fअगरo);
	kvमुक्त(sq->db.dma_fअगरo);
पूर्ण

पूर्णांक mlx5e_alloc_txqsq_db(काष्ठा mlx5e_txqsq *sq, पूर्णांक numa)
अणु
	पूर्णांक wq_sz = mlx5_wq_cyc_get_size(&sq->wq);
	पूर्णांक df_sz = wq_sz * MLX5_SEND_WQEBB_NUM_DS;

	sq->db.dma_fअगरo = kvzalloc_node(array_size(df_sz,
						   माप(*sq->db.dma_fअगरo)),
					GFP_KERNEL, numa);
	sq->db.skb_fअगरo.fअगरo = kvzalloc_node(array_size(df_sz,
							माप(*sq->db.skb_fअगरo.fअगरo)),
					GFP_KERNEL, numa);
	sq->db.wqe_info = kvzalloc_node(array_size(wq_sz,
						   माप(*sq->db.wqe_info)),
					GFP_KERNEL, numa);
	अगर (!sq->db.dma_fअगरo || !sq->db.skb_fअगरo.fअगरo || !sq->db.wqe_info) अणु
		mlx5e_मुक्त_txqsq_db(sq);
		वापस -ENOMEM;
	पूर्ण

	sq->dma_fअगरo_mask = df_sz - 1;

	sq->db.skb_fअगरo.pc   = &sq->skb_fअगरo_pc;
	sq->db.skb_fअगरo.cc   = &sq->skb_fअगरo_cc;
	sq->db.skb_fअगरo.mask = df_sz - 1;

	वापस 0;
पूर्ण

अटल पूर्णांक mlx5e_alloc_txqsq(काष्ठा mlx5e_channel *c,
			     पूर्णांक txq_ix,
			     काष्ठा mlx5e_params *params,
			     काष्ठा mlx5e_sq_param *param,
			     काष्ठा mlx5e_txqsq *sq,
			     पूर्णांक tc)
अणु
	व्योम *sqc_wq               = MLX5_ADDR_OF(sqc, param->sqc, wq);
	काष्ठा mlx5_core_dev *mdev = c->mdev;
	काष्ठा mlx5_wq_cyc *wq = &sq->wq;
	पूर्णांक err;

	sq->pdev      = c->pdev;
	sq->tstamp    = c->tstamp;
	sq->घड़ी     = &mdev->घड़ी;
	sq->mkey_be   = c->mkey_be;
	sq->netdev    = c->netdev;
	sq->mdev      = c->mdev;
	sq->priv      = c->priv;
	sq->ch_ix     = c->ix;
	sq->txq_ix    = txq_ix;
	sq->uar_map   = mdev->mlx5e_res.hw_objs.bfreg.map;
	sq->min_अंतरभूत_mode = params->tx_min_अंतरभूत_mode;
	sq->hw_mtu    = MLX5E_SW2HW_MTU(params, params->sw_mtu);
	INIT_WORK(&sq->recover_work, mlx5e_tx_err_cqe_work);
	अगर (!MLX5_CAP_ETH(mdev, wqe_vlan_insert))
		set_bit(MLX5E_SQ_STATE_VLAN_NEED_L2_INLINE, &sq->state);
	अगर (MLX5_IPSEC_DEV(c->priv->mdev))
		set_bit(MLX5E_SQ_STATE_IPSEC, &sq->state);
	अगर (param->is_mpw)
		set_bit(MLX5E_SQ_STATE_MPWQE, &sq->state);
	sq->stop_room = param->stop_room;
	sq->ptp_cyc2समय = mlx5_sq_ts_translator(mdev);

	param->wq.db_numa_node = cpu_to_node(c->cpu);
	err = mlx5_wq_cyc_create(mdev, &param->wq, sqc_wq, wq, &sq->wq_ctrl);
	अगर (err)
		वापस err;
	wq->db    = &wq->db[MLX5_SND_DBR];

	err = mlx5e_alloc_txqsq_db(sq, cpu_to_node(c->cpu));
	अगर (err)
		जाओ err_sq_wq_destroy;

	INIT_WORK(&sq->dim.work, mlx5e_tx_dim_work);
	sq->dim.mode = params->tx_cq_moderation.cq_period_mode;

	वापस 0;

err_sq_wq_destroy:
	mlx5_wq_destroy(&sq->wq_ctrl);

	वापस err;
पूर्ण

व्योम mlx5e_मुक्त_txqsq(काष्ठा mlx5e_txqsq *sq)
अणु
	mlx5e_मुक्त_txqsq_db(sq);
	mlx5_wq_destroy(&sq->wq_ctrl);
पूर्ण

अटल पूर्णांक mlx5e_create_sq(काष्ठा mlx5_core_dev *mdev,
			   काष्ठा mlx5e_sq_param *param,
			   काष्ठा mlx5e_create_sq_param *csp,
			   u32 *sqn)
अणु
	u8 ts_क्रमmat;
	व्योम *in;
	व्योम *sqc;
	व्योम *wq;
	पूर्णांक inlen;
	पूर्णांक err;

	inlen = MLX5_ST_SZ_BYTES(create_sq_in) +
		माप(u64) * csp->wq_ctrl->buf.npages;
	in = kvzalloc(inlen, GFP_KERNEL);
	अगर (!in)
		वापस -ENOMEM;

	ts_क्रमmat = mlx5_is_real_समय_sq(mdev) ?
		    MLX5_SQC_TIMESTAMP_FORMAT_REAL_TIME :
		    MLX5_SQC_TIMESTAMP_FORMAT_FREE_RUNNING;
	sqc = MLX5_ADDR_OF(create_sq_in, in, ctx);
	wq = MLX5_ADDR_OF(sqc, sqc, wq);

	स_नकल(sqc, param->sqc, माप(param->sqc));
	MLX5_SET(sqc,  sqc, tis_lst_sz, csp->tis_lst_sz);
	MLX5_SET(sqc,  sqc, tis_num_0, csp->tisn);
	MLX5_SET(sqc,  sqc, cqn, csp->cqn);
	MLX5_SET(sqc,  sqc, ts_cqe_to_dest_cqn, csp->ts_cqe_to_dest_cqn);
	MLX5_SET(sqc,  sqc, ts_क्रमmat, ts_क्रमmat);


	अगर (MLX5_CAP_ETH(mdev, wqe_अंतरभूत_mode) == MLX5_CAP_INLINE_MODE_VPORT_CONTEXT)
		MLX5_SET(sqc,  sqc, min_wqe_अंतरभूत_mode, csp->min_अंतरभूत_mode);

	MLX5_SET(sqc,  sqc, state, MLX5_SQC_STATE_RST);
	MLX5_SET(sqc,  sqc, flush_in_error_en, 1);

	MLX5_SET(wq,   wq, wq_type,       MLX5_WQ_TYPE_CYCLIC);
	MLX5_SET(wq,   wq, uar_page,      mdev->mlx5e_res.hw_objs.bfreg.index);
	MLX5_SET(wq,   wq, log_wq_pg_sz,  csp->wq_ctrl->buf.page_shअगरt -
					  MLX5_ADAPTER_PAGE_SHIFT);
	MLX5_SET64(wq, wq, dbr_addr,      csp->wq_ctrl->db.dma);

	mlx5_fill_page_frag_array(&csp->wq_ctrl->buf,
				  (__be64 *)MLX5_ADDR_OF(wq, wq, pas));

	err = mlx5_core_create_sq(mdev, in, inlen, sqn);

	kvमुक्त(in);

	वापस err;
पूर्ण

पूर्णांक mlx5e_modअगरy_sq(काष्ठा mlx5_core_dev *mdev, u32 sqn,
		    काष्ठा mlx5e_modअगरy_sq_param *p)
अणु
	u64 biपंचांगask = 0;
	व्योम *in;
	व्योम *sqc;
	पूर्णांक inlen;
	पूर्णांक err;

	inlen = MLX5_ST_SZ_BYTES(modअगरy_sq_in);
	in = kvzalloc(inlen, GFP_KERNEL);
	अगर (!in)
		वापस -ENOMEM;

	sqc = MLX5_ADDR_OF(modअगरy_sq_in, in, ctx);

	MLX5_SET(modअगरy_sq_in, in, sq_state, p->curr_state);
	MLX5_SET(sqc, sqc, state, p->next_state);
	अगर (p->rl_update && p->next_state == MLX5_SQC_STATE_RDY) अणु
		biपंचांगask |= 1;
		MLX5_SET(sqc, sqc, packet_pacing_rate_limit_index, p->rl_index);
	पूर्ण
	अगर (p->qos_update && p->next_state == MLX5_SQC_STATE_RDY) अणु
		biपंचांगask |= 1 << 2;
		MLX5_SET(sqc, sqc, qos_queue_group_id, p->qos_queue_group_id);
	पूर्ण
	MLX5_SET64(modअगरy_sq_in, in, modअगरy_biपंचांगask, biपंचांगask);

	err = mlx5_core_modअगरy_sq(mdev, sqn, in);

	kvमुक्त(in);

	वापस err;
पूर्ण

अटल व्योम mlx5e_destroy_sq(काष्ठा mlx5_core_dev *mdev, u32 sqn)
अणु
	mlx5_core_destroy_sq(mdev, sqn);
पूर्ण

पूर्णांक mlx5e_create_sq_rdy(काष्ठा mlx5_core_dev *mdev,
			काष्ठा mlx5e_sq_param *param,
			काष्ठा mlx5e_create_sq_param *csp,
			u16 qos_queue_group_id,
			u32 *sqn)
अणु
	काष्ठा mlx5e_modअगरy_sq_param msp = अणु0पूर्ण;
	पूर्णांक err;

	err = mlx5e_create_sq(mdev, param, csp, sqn);
	अगर (err)
		वापस err;

	msp.curr_state = MLX5_SQC_STATE_RST;
	msp.next_state = MLX5_SQC_STATE_RDY;
	अगर (qos_queue_group_id) अणु
		msp.qos_update = true;
		msp.qos_queue_group_id = qos_queue_group_id;
	पूर्ण
	err = mlx5e_modअगरy_sq(mdev, *sqn, &msp);
	अगर (err)
		mlx5e_destroy_sq(mdev, *sqn);

	वापस err;
पूर्ण

अटल पूर्णांक mlx5e_set_sq_maxrate(काष्ठा net_device *dev,
				काष्ठा mlx5e_txqsq *sq, u32 rate);

पूर्णांक mlx5e_खोलो_txqsq(काष्ठा mlx5e_channel *c, u32 tisn, पूर्णांक txq_ix,
		     काष्ठा mlx5e_params *params, काष्ठा mlx5e_sq_param *param,
		     काष्ठा mlx5e_txqsq *sq, पूर्णांक tc, u16 qos_queue_group_id, u16 qos_qid)
अणु
	काष्ठा mlx5e_create_sq_param csp = अणुपूर्ण;
	u32 tx_rate;
	पूर्णांक err;

	err = mlx5e_alloc_txqsq(c, txq_ix, params, param, sq, tc);
	अगर (err)
		वापस err;

	अगर (qos_queue_group_id)
		sq->stats = c->priv->htb.qos_sq_stats[qos_qid];
	अन्यथा
		sq->stats = &c->priv->channel_stats[c->ix].sq[tc];

	csp.tisn            = tisn;
	csp.tis_lst_sz      = 1;
	csp.cqn             = sq->cq.mcq.cqn;
	csp.wq_ctrl         = &sq->wq_ctrl;
	csp.min_अंतरभूत_mode = sq->min_अंतरभूत_mode;
	err = mlx5e_create_sq_rdy(c->mdev, param, &csp, qos_queue_group_id, &sq->sqn);
	अगर (err)
		जाओ err_मुक्त_txqsq;

	tx_rate = c->priv->tx_rates[sq->txq_ix];
	अगर (tx_rate)
		mlx5e_set_sq_maxrate(c->netdev, sq, tx_rate);

	अगर (params->tx_dim_enabled)
		sq->state |= BIT(MLX5E_SQ_STATE_AM);

	वापस 0;

err_मुक्त_txqsq:
	mlx5e_मुक्त_txqsq(sq);

	वापस err;
पूर्ण

व्योम mlx5e_activate_txqsq(काष्ठा mlx5e_txqsq *sq)
अणु
	sq->txq = netdev_get_tx_queue(sq->netdev, sq->txq_ix);
	set_bit(MLX5E_SQ_STATE_ENABLED, &sq->state);
	netdev_tx_reset_queue(sq->txq);
	netअगर_tx_start_queue(sq->txq);
पूर्ण

व्योम mlx5e_tx_disable_queue(काष्ठा netdev_queue *txq)
अणु
	__netअगर_tx_lock_bh(txq);
	netअगर_tx_stop_queue(txq);
	__netअगर_tx_unlock_bh(txq);
पूर्ण

व्योम mlx5e_deactivate_txqsq(काष्ठा mlx5e_txqsq *sq)
अणु
	काष्ठा mlx5_wq_cyc *wq = &sq->wq;

	clear_bit(MLX5E_SQ_STATE_ENABLED, &sq->state);
	synchronize_net(); /* Sync with NAPI to prevent netअगर_tx_wake_queue. */

	mlx5e_tx_disable_queue(sq->txq);

	/* last करोorbell out, godspeed .. */
	अगर (mlx5e_wqc_has_room_क्रम(wq, sq->cc, sq->pc, 1)) अणु
		u16 pi = mlx5_wq_cyc_ctr2ix(wq, sq->pc);
		काष्ठा mlx5e_tx_wqe *nop;

		sq->db.wqe_info[pi] = (काष्ठा mlx5e_tx_wqe_info) अणु
			.num_wqebbs = 1,
		पूर्ण;

		nop = mlx5e_post_nop(wq, sq->sqn, &sq->pc);
		mlx5e_notअगरy_hw(wq, sq->pc, sq->uar_map, &nop->ctrl);
	पूर्ण
पूर्ण

व्योम mlx5e_बंद_txqsq(काष्ठा mlx5e_txqsq *sq)
अणु
	काष्ठा mlx5_core_dev *mdev = sq->mdev;
	काष्ठा mlx5_rate_limit rl = अणु0पूर्ण;

	cancel_work_sync(&sq->dim.work);
	cancel_work_sync(&sq->recover_work);
	mlx5e_destroy_sq(mdev, sq->sqn);
	अगर (sq->rate_limit) अणु
		rl.rate = sq->rate_limit;
		mlx5_rl_हटाओ_rate(mdev, &rl);
	पूर्ण
	mlx5e_मुक्त_txqsq_descs(sq);
	mlx5e_मुक्त_txqsq(sq);
पूर्ण

व्योम mlx5e_tx_err_cqe_work(काष्ठा work_काष्ठा *recover_work)
अणु
	काष्ठा mlx5e_txqsq *sq = container_of(recover_work, काष्ठा mlx5e_txqsq,
					      recover_work);

	mlx5e_reporter_tx_err_cqe(sq);
पूर्ण

पूर्णांक mlx5e_खोलो_icosq(काष्ठा mlx5e_channel *c, काष्ठा mlx5e_params *params,
		     काष्ठा mlx5e_sq_param *param, काष्ठा mlx5e_icosq *sq)
अणु
	काष्ठा mlx5e_create_sq_param csp = अणुपूर्ण;
	पूर्णांक err;

	err = mlx5e_alloc_icosq(c, param, sq);
	अगर (err)
		वापस err;

	csp.cqn             = sq->cq.mcq.cqn;
	csp.wq_ctrl         = &sq->wq_ctrl;
	csp.min_अंतरभूत_mode = params->tx_min_अंतरभूत_mode;
	err = mlx5e_create_sq_rdy(c->mdev, param, &csp, 0, &sq->sqn);
	अगर (err)
		जाओ err_मुक्त_icosq;

	अगर (param->is_tls) अणु
		sq->ktls_resync = mlx5e_ktls_rx_resync_create_resp_list();
		अगर (IS_ERR(sq->ktls_resync)) अणु
			err = PTR_ERR(sq->ktls_resync);
			जाओ err_destroy_icosq;
		पूर्ण
	पूर्ण
	वापस 0;

err_destroy_icosq:
	mlx5e_destroy_sq(c->mdev, sq->sqn);
err_मुक्त_icosq:
	mlx5e_मुक्त_icosq(sq);

	वापस err;
पूर्ण

व्योम mlx5e_activate_icosq(काष्ठा mlx5e_icosq *icosq)
अणु
	set_bit(MLX5E_SQ_STATE_ENABLED, &icosq->state);
पूर्ण

व्योम mlx5e_deactivate_icosq(काष्ठा mlx5e_icosq *icosq)
अणु
	clear_bit(MLX5E_SQ_STATE_ENABLED, &icosq->state);
	synchronize_net(); /* Sync with NAPI. */
पूर्ण

व्योम mlx5e_बंद_icosq(काष्ठा mlx5e_icosq *sq)
अणु
	काष्ठा mlx5e_channel *c = sq->channel;

	अगर (sq->ktls_resync)
		mlx5e_ktls_rx_resync_destroy_resp_list(sq->ktls_resync);
	mlx5e_destroy_sq(c->mdev, sq->sqn);
	mlx5e_मुक्त_icosq_descs(sq);
	mlx5e_मुक्त_icosq(sq);
पूर्ण

पूर्णांक mlx5e_खोलो_xdpsq(काष्ठा mlx5e_channel *c, काष्ठा mlx5e_params *params,
		     काष्ठा mlx5e_sq_param *param, काष्ठा xsk_buff_pool *xsk_pool,
		     काष्ठा mlx5e_xdpsq *sq, bool is_redirect)
अणु
	काष्ठा mlx5e_create_sq_param csp = अणुपूर्ण;
	पूर्णांक err;

	err = mlx5e_alloc_xdpsq(c, params, xsk_pool, param, sq, is_redirect);
	अगर (err)
		वापस err;

	csp.tis_lst_sz      = 1;
	csp.tisn            = c->priv->tisn[c->lag_port][0]; /* tc = 0 */
	csp.cqn             = sq->cq.mcq.cqn;
	csp.wq_ctrl         = &sq->wq_ctrl;
	csp.min_अंतरभूत_mode = sq->min_अंतरभूत_mode;
	set_bit(MLX5E_SQ_STATE_ENABLED, &sq->state);
	err = mlx5e_create_sq_rdy(c->mdev, param, &csp, 0, &sq->sqn);
	अगर (err)
		जाओ err_मुक्त_xdpsq;

	mlx5e_set_xmit_fp(sq, param->is_mpw);

	अगर (!param->is_mpw) अणु
		अचिन्हित पूर्णांक ds_cnt = MLX5E_XDP_TX_DS_COUNT;
		अचिन्हित पूर्णांक अंतरभूत_hdr_sz = 0;
		पूर्णांक i;

		अगर (sq->min_अंतरभूत_mode != MLX5_INLINE_MODE_NONE) अणु
			अंतरभूत_hdr_sz = MLX5E_XDP_MIN_INLINE;
			ds_cnt++;
		पूर्ण

		/* Pre initialize fixed WQE fields */
		क्रम (i = 0; i < mlx5_wq_cyc_get_size(&sq->wq); i++) अणु
			काष्ठा mlx5e_tx_wqe      *wqe  = mlx5_wq_cyc_get_wqe(&sq->wq, i);
			काष्ठा mlx5_wqe_ctrl_seg *cseg = &wqe->ctrl;
			काष्ठा mlx5_wqe_eth_seg  *eseg = &wqe->eth;
			काष्ठा mlx5_wqe_data_seg *dseg;

			sq->db.wqe_info[i] = (काष्ठा mlx5e_xdp_wqe_info) अणु
				.num_wqebbs = 1,
				.num_pkts   = 1,
			पूर्ण;

			cseg->qpn_ds = cpu_to_be32((sq->sqn << 8) | ds_cnt);
			eseg->अंतरभूत_hdr.sz = cpu_to_be16(अंतरभूत_hdr_sz);

			dseg = (काष्ठा mlx5_wqe_data_seg *)cseg + (ds_cnt - 1);
			dseg->lkey = sq->mkey_be;
		पूर्ण
	पूर्ण

	वापस 0;

err_मुक्त_xdpsq:
	clear_bit(MLX5E_SQ_STATE_ENABLED, &sq->state);
	mlx5e_मुक्त_xdpsq(sq);

	वापस err;
पूर्ण

व्योम mlx5e_बंद_xdpsq(काष्ठा mlx5e_xdpsq *sq)
अणु
	काष्ठा mlx5e_channel *c = sq->channel;

	clear_bit(MLX5E_SQ_STATE_ENABLED, &sq->state);
	synchronize_net(); /* Sync with NAPI. */

	mlx5e_destroy_sq(c->mdev, sq->sqn);
	mlx5e_मुक्त_xdpsq_descs(sq);
	mlx5e_मुक्त_xdpsq(sq);
पूर्ण

अटल पूर्णांक mlx5e_alloc_cq_common(काष्ठा mlx5e_priv *priv,
				 काष्ठा mlx5e_cq_param *param,
				 काष्ठा mlx5e_cq *cq)
अणु
	काष्ठा mlx5_core_dev *mdev = priv->mdev;
	काष्ठा mlx5_core_cq *mcq = &cq->mcq;
	पूर्णांक eqn_not_used;
	अचिन्हित पूर्णांक irqn;
	पूर्णांक err;
	u32 i;

	err = mlx5_vector2eqn(mdev, param->eq_ix, &eqn_not_used, &irqn);
	अगर (err)
		वापस err;

	err = mlx5_cqwq_create(mdev, &param->wq, param->cqc, &cq->wq,
			       &cq->wq_ctrl);
	अगर (err)
		वापस err;

	mcq->cqe_sz     = 64;
	mcq->set_ci_db  = cq->wq_ctrl.db.db;
	mcq->arm_db     = cq->wq_ctrl.db.db + 1;
	*mcq->set_ci_db = 0;
	*mcq->arm_db    = 0;
	mcq->vector     = param->eq_ix;
	mcq->comp       = mlx5e_completion_event;
	mcq->event      = mlx5e_cq_error_event;
	mcq->irqn       = irqn;

	क्रम (i = 0; i < mlx5_cqwq_get_size(&cq->wq); i++) अणु
		काष्ठा mlx5_cqe64 *cqe = mlx5_cqwq_get_wqe(&cq->wq, i);

		cqe->op_own = 0xf1;
	पूर्ण

	cq->mdev = mdev;
	cq->netdev = priv->netdev;
	cq->priv = priv;

	वापस 0;
पूर्ण

अटल पूर्णांक mlx5e_alloc_cq(काष्ठा mlx5e_priv *priv,
			  काष्ठा mlx5e_cq_param *param,
			  काष्ठा mlx5e_create_cq_param *ccp,
			  काष्ठा mlx5e_cq *cq)
अणु
	पूर्णांक err;

	param->wq.buf_numa_node = ccp->node;
	param->wq.db_numa_node  = ccp->node;
	param->eq_ix            = ccp->ix;

	err = mlx5e_alloc_cq_common(priv, param, cq);

	cq->napi     = ccp->napi;
	cq->ch_stats = ccp->ch_stats;

	वापस err;
पूर्ण

अटल व्योम mlx5e_मुक्त_cq(काष्ठा mlx5e_cq *cq)
अणु
	mlx5_wq_destroy(&cq->wq_ctrl);
पूर्ण

अटल पूर्णांक mlx5e_create_cq(काष्ठा mlx5e_cq *cq, काष्ठा mlx5e_cq_param *param)
अणु
	u32 out[MLX5_ST_SZ_DW(create_cq_out)];
	काष्ठा mlx5_core_dev *mdev = cq->mdev;
	काष्ठा mlx5_core_cq *mcq = &cq->mcq;

	व्योम *in;
	व्योम *cqc;
	पूर्णांक inlen;
	अचिन्हित पूर्णांक irqn_not_used;
	पूर्णांक eqn;
	पूर्णांक err;

	err = mlx5_vector2eqn(mdev, param->eq_ix, &eqn, &irqn_not_used);
	अगर (err)
		वापस err;

	inlen = MLX5_ST_SZ_BYTES(create_cq_in) +
		माप(u64) * cq->wq_ctrl.buf.npages;
	in = kvzalloc(inlen, GFP_KERNEL);
	अगर (!in)
		वापस -ENOMEM;

	cqc = MLX5_ADDR_OF(create_cq_in, in, cq_context);

	स_नकल(cqc, param->cqc, माप(param->cqc));

	mlx5_fill_page_frag_array(&cq->wq_ctrl.buf,
				  (__be64 *)MLX5_ADDR_OF(create_cq_in, in, pas));

	MLX5_SET(cqc,   cqc, cq_period_mode, param->cq_period_mode);
	MLX5_SET(cqc,   cqc, c_eqn,         eqn);
	MLX5_SET(cqc,   cqc, uar_page,      mdev->priv.uar->index);
	MLX5_SET(cqc,   cqc, log_page_size, cq->wq_ctrl.buf.page_shअगरt -
					    MLX5_ADAPTER_PAGE_SHIFT);
	MLX5_SET64(cqc, cqc, dbr_addr,      cq->wq_ctrl.db.dma);

	err = mlx5_core_create_cq(mdev, mcq, in, inlen, out, माप(out));

	kvमुक्त(in);

	अगर (err)
		वापस err;

	mlx5e_cq_arm(cq);

	वापस 0;
पूर्ण

अटल व्योम mlx5e_destroy_cq(काष्ठा mlx5e_cq *cq)
अणु
	mlx5_core_destroy_cq(cq->mdev, &cq->mcq);
पूर्ण

पूर्णांक mlx5e_खोलो_cq(काष्ठा mlx5e_priv *priv, काष्ठा dim_cq_moder moder,
		  काष्ठा mlx5e_cq_param *param, काष्ठा mlx5e_create_cq_param *ccp,
		  काष्ठा mlx5e_cq *cq)
अणु
	काष्ठा mlx5_core_dev *mdev = priv->mdev;
	पूर्णांक err;

	err = mlx5e_alloc_cq(priv, param, ccp, cq);
	अगर (err)
		वापस err;

	err = mlx5e_create_cq(cq, param);
	अगर (err)
		जाओ err_मुक्त_cq;

	अगर (MLX5_CAP_GEN(mdev, cq_moderation))
		mlx5_core_modअगरy_cq_moderation(mdev, &cq->mcq, moder.usec, moder.pkts);
	वापस 0;

err_मुक्त_cq:
	mlx5e_मुक्त_cq(cq);

	वापस err;
पूर्ण

व्योम mlx5e_बंद_cq(काष्ठा mlx5e_cq *cq)
अणु
	mlx5e_destroy_cq(cq);
	mlx5e_मुक्त_cq(cq);
पूर्ण

अटल पूर्णांक mlx5e_खोलो_tx_cqs(काष्ठा mlx5e_channel *c,
			     काष्ठा mlx5e_params *params,
			     काष्ठा mlx5e_create_cq_param *ccp,
			     काष्ठा mlx5e_channel_param *cparam)
अणु
	पूर्णांक err;
	पूर्णांक tc;

	क्रम (tc = 0; tc < c->num_tc; tc++) अणु
		err = mlx5e_खोलो_cq(c->priv, params->tx_cq_moderation, &cparam->txq_sq.cqp,
				    ccp, &c->sq[tc].cq);
		अगर (err)
			जाओ err_बंद_tx_cqs;
	पूर्ण

	वापस 0;

err_बंद_tx_cqs:
	क्रम (tc--; tc >= 0; tc--)
		mlx5e_बंद_cq(&c->sq[tc].cq);

	वापस err;
पूर्ण

अटल व्योम mlx5e_बंद_tx_cqs(काष्ठा mlx5e_channel *c)
अणु
	पूर्णांक tc;

	क्रम (tc = 0; tc < c->num_tc; tc++)
		mlx5e_बंद_cq(&c->sq[tc].cq);
पूर्ण

अटल पूर्णांक mlx5e_खोलो_sqs(काष्ठा mlx5e_channel *c,
			  काष्ठा mlx5e_params *params,
			  काष्ठा mlx5e_channel_param *cparam)
अणु
	पूर्णांक err, tc;

	क्रम (tc = 0; tc < params->num_tc; tc++) अणु
		पूर्णांक txq_ix = c->ix + tc * params->num_channels;

		err = mlx5e_खोलो_txqsq(c, c->priv->tisn[c->lag_port][tc], txq_ix,
				       params, &cparam->txq_sq, &c->sq[tc], tc, 0, 0);
		अगर (err)
			जाओ err_बंद_sqs;
	पूर्ण

	वापस 0;

err_बंद_sqs:
	क्रम (tc--; tc >= 0; tc--)
		mlx5e_बंद_txqsq(&c->sq[tc]);

	वापस err;
पूर्ण

अटल व्योम mlx5e_बंद_sqs(काष्ठा mlx5e_channel *c)
अणु
	पूर्णांक tc;

	क्रम (tc = 0; tc < c->num_tc; tc++)
		mlx5e_बंद_txqsq(&c->sq[tc]);
पूर्ण

अटल पूर्णांक mlx5e_set_sq_maxrate(काष्ठा net_device *dev,
				काष्ठा mlx5e_txqsq *sq, u32 rate)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(dev);
	काष्ठा mlx5_core_dev *mdev = priv->mdev;
	काष्ठा mlx5e_modअगरy_sq_param msp = अणु0पूर्ण;
	काष्ठा mlx5_rate_limit rl = अणु0पूर्ण;
	u16 rl_index = 0;
	पूर्णांक err;

	अगर (rate == sq->rate_limit)
		/* nothing to करो */
		वापस 0;

	अगर (sq->rate_limit) अणु
		rl.rate = sq->rate_limit;
		/* हटाओ current rl index to मुक्त space to next ones */
		mlx5_rl_हटाओ_rate(mdev, &rl);
	पूर्ण

	sq->rate_limit = 0;

	अगर (rate) अणु
		rl.rate = rate;
		err = mlx5_rl_add_rate(mdev, &rl_index, &rl);
		अगर (err) अणु
			netdev_err(dev, "Failed configuring rate %u: %d\n",
				   rate, err);
			वापस err;
		पूर्ण
	पूर्ण

	msp.curr_state = MLX5_SQC_STATE_RDY;
	msp.next_state = MLX5_SQC_STATE_RDY;
	msp.rl_index   = rl_index;
	msp.rl_update  = true;
	err = mlx5e_modअगरy_sq(mdev, sq->sqn, &msp);
	अगर (err) अणु
		netdev_err(dev, "Failed configuring rate %u: %d\n",
			   rate, err);
		/* हटाओ the rate from the table */
		अगर (rate)
			mlx5_rl_हटाओ_rate(mdev, &rl);
		वापस err;
	पूर्ण

	sq->rate_limit = rate;
	वापस 0;
पूर्ण

अटल पूर्णांक mlx5e_set_tx_maxrate(काष्ठा net_device *dev, पूर्णांक index, u32 rate)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(dev);
	काष्ठा mlx5_core_dev *mdev = priv->mdev;
	काष्ठा mlx5e_txqsq *sq = priv->txq2sq[index];
	पूर्णांक err = 0;

	अगर (!mlx5_rl_is_supported(mdev)) अणु
		netdev_err(dev, "Rate limiting is not supported on this device\n");
		वापस -EINVAL;
	पूर्ण

	/* rate is given in Mb/sec, HW config is in Kb/sec */
	rate = rate << 10;

	/* Check whether rate in valid range, 0 is always valid */
	अगर (rate && !mlx5_rl_is_in_range(mdev, rate)) अणु
		netdev_err(dev, "TX rate %u, is not in range\n", rate);
		वापस -दुस्फल;
	पूर्ण

	mutex_lock(&priv->state_lock);
	अगर (test_bit(MLX5E_STATE_OPENED, &priv->state))
		err = mlx5e_set_sq_maxrate(dev, sq, rate);
	अगर (!err)
		priv->tx_rates[index] = rate;
	mutex_unlock(&priv->state_lock);

	वापस err;
पूर्ण

अटल पूर्णांक mlx5e_खोलो_rxq_rq(काष्ठा mlx5e_channel *c, काष्ठा mlx5e_params *params,
			     काष्ठा mlx5e_rq_param *rq_params)
अणु
	पूर्णांक err;

	err = mlx5e_init_rxq_rq(c, params, &c->rq);
	अगर (err)
		वापस err;

	वापस mlx5e_खोलो_rq(params, rq_params, शून्य, cpu_to_node(c->cpu), &c->rq);
पूर्ण

अटल पूर्णांक mlx5e_खोलो_queues(काष्ठा mlx5e_channel *c,
			     काष्ठा mlx5e_params *params,
			     काष्ठा mlx5e_channel_param *cparam)
अणु
	काष्ठा dim_cq_moder icocq_moder = अणु0, 0पूर्ण;
	काष्ठा mlx5e_create_cq_param ccp;
	पूर्णांक err;

	mlx5e_build_create_cq_param(&ccp, c);

	err = mlx5e_खोलो_cq(c->priv, icocq_moder, &cparam->async_icosq.cqp, &ccp,
			    &c->async_icosq.cq);
	अगर (err)
		वापस err;

	err = mlx5e_खोलो_cq(c->priv, icocq_moder, &cparam->icosq.cqp, &ccp,
			    &c->icosq.cq);
	अगर (err)
		जाओ err_बंद_async_icosq_cq;

	err = mlx5e_खोलो_tx_cqs(c, params, &ccp, cparam);
	अगर (err)
		जाओ err_बंद_icosq_cq;

	err = mlx5e_खोलो_cq(c->priv, params->tx_cq_moderation, &cparam->xdp_sq.cqp, &ccp,
			    &c->xdpsq.cq);
	अगर (err)
		जाओ err_बंद_tx_cqs;

	err = mlx5e_खोलो_cq(c->priv, params->rx_cq_moderation, &cparam->rq.cqp, &ccp,
			    &c->rq.cq);
	अगर (err)
		जाओ err_बंद_xdp_tx_cqs;

	err = c->xdp ? mlx5e_खोलो_cq(c->priv, params->tx_cq_moderation, &cparam->xdp_sq.cqp,
				     &ccp, &c->rq_xdpsq.cq) : 0;
	अगर (err)
		जाओ err_बंद_rx_cq;

	spin_lock_init(&c->async_icosq_lock);

	err = mlx5e_खोलो_icosq(c, params, &cparam->async_icosq, &c->async_icosq);
	अगर (err)
		जाओ err_बंद_xdpsq_cq;

	err = mlx5e_खोलो_icosq(c, params, &cparam->icosq, &c->icosq);
	अगर (err)
		जाओ err_बंद_async_icosq;

	err = mlx5e_खोलो_sqs(c, params, cparam);
	अगर (err)
		जाओ err_बंद_icosq;

	अगर (c->xdp) अणु
		err = mlx5e_खोलो_xdpsq(c, params, &cparam->xdp_sq, शून्य,
				       &c->rq_xdpsq, false);
		अगर (err)
			जाओ err_बंद_sqs;
	पूर्ण

	err = mlx5e_खोलो_rxq_rq(c, params, &cparam->rq);
	अगर (err)
		जाओ err_बंद_xdp_sq;

	err = mlx5e_खोलो_xdpsq(c, params, &cparam->xdp_sq, शून्य, &c->xdpsq, true);
	अगर (err)
		जाओ err_बंद_rq;

	वापस 0;

err_बंद_rq:
	mlx5e_बंद_rq(&c->rq);

err_बंद_xdp_sq:
	अगर (c->xdp)
		mlx5e_बंद_xdpsq(&c->rq_xdpsq);

err_बंद_sqs:
	mlx5e_बंद_sqs(c);

err_बंद_icosq:
	mlx5e_बंद_icosq(&c->icosq);

err_बंद_async_icosq:
	mlx5e_बंद_icosq(&c->async_icosq);

err_बंद_xdpsq_cq:
	अगर (c->xdp)
		mlx5e_बंद_cq(&c->rq_xdpsq.cq);

err_बंद_rx_cq:
	mlx5e_बंद_cq(&c->rq.cq);

err_बंद_xdp_tx_cqs:
	mlx5e_बंद_cq(&c->xdpsq.cq);

err_बंद_tx_cqs:
	mlx5e_बंद_tx_cqs(c);

err_बंद_icosq_cq:
	mlx5e_बंद_cq(&c->icosq.cq);

err_बंद_async_icosq_cq:
	mlx5e_बंद_cq(&c->async_icosq.cq);

	वापस err;
पूर्ण

अटल व्योम mlx5e_बंद_queues(काष्ठा mlx5e_channel *c)
अणु
	mlx5e_बंद_xdpsq(&c->xdpsq);
	mlx5e_बंद_rq(&c->rq);
	अगर (c->xdp)
		mlx5e_बंद_xdpsq(&c->rq_xdpsq);
	mlx5e_बंद_sqs(c);
	mlx5e_बंद_icosq(&c->icosq);
	mlx5e_बंद_icosq(&c->async_icosq);
	अगर (c->xdp)
		mlx5e_बंद_cq(&c->rq_xdpsq.cq);
	mlx5e_बंद_cq(&c->rq.cq);
	mlx5e_बंद_cq(&c->xdpsq.cq);
	mlx5e_बंद_tx_cqs(c);
	mlx5e_बंद_cq(&c->icosq.cq);
	mlx5e_बंद_cq(&c->async_icosq.cq);
पूर्ण

अटल u8 mlx5e_क्रमागतerate_lag_port(काष्ठा mlx5_core_dev *mdev, पूर्णांक ix)
अणु
	u16 port_aff_bias = mlx5_core_is_pf(mdev) ? 0 : MLX5_CAP_GEN(mdev, vhca_id);

	वापस (ix + port_aff_bias) % mlx5e_get_num_lag_ports(mdev);
पूर्ण

अटल पूर्णांक mlx5e_खोलो_channel(काष्ठा mlx5e_priv *priv, पूर्णांक ix,
			      काष्ठा mlx5e_params *params,
			      काष्ठा mlx5e_channel_param *cparam,
			      काष्ठा xsk_buff_pool *xsk_pool,
			      काष्ठा mlx5e_channel **cp)
अणु
	पूर्णांक cpu = cpumask_first(mlx5_comp_irq_get_affinity_mask(priv->mdev, ix));
	काष्ठा net_device *netdev = priv->netdev;
	काष्ठा mlx5e_xsk_param xsk;
	काष्ठा mlx5e_channel *c;
	अचिन्हित पूर्णांक irq;
	पूर्णांक err;
	पूर्णांक eqn;

	err = mlx5_vector2eqn(priv->mdev, ix, &eqn, &irq);
	अगर (err)
		वापस err;

	c = kvzalloc_node(माप(*c), GFP_KERNEL, cpu_to_node(cpu));
	अगर (!c)
		वापस -ENOMEM;

	c->priv     = priv;
	c->mdev     = priv->mdev;
	c->tstamp   = &priv->tstamp;
	c->ix       = ix;
	c->cpu      = cpu;
	c->pdev     = mlx5_core_dma_dev(priv->mdev);
	c->netdev   = priv->netdev;
	c->mkey_be  = cpu_to_be32(priv->mdev->mlx5e_res.hw_objs.mkey.key);
	c->num_tc   = params->num_tc;
	c->xdp      = !!params->xdp_prog;
	c->stats    = &priv->channel_stats[ix].ch;
	c->aff_mask = irq_get_effective_affinity_mask(irq);
	c->lag_port = mlx5e_क्रमागतerate_lag_port(priv->mdev, ix);

	netअगर_napi_add(netdev, &c->napi, mlx5e_napi_poll, 64);

	err = mlx5e_खोलो_queues(c, params, cparam);
	अगर (unlikely(err))
		जाओ err_napi_del;

	अगर (xsk_pool) अणु
		mlx5e_build_xsk_param(xsk_pool, &xsk);
		err = mlx5e_खोलो_xsk(priv, params, &xsk, xsk_pool, c);
		अगर (unlikely(err))
			जाओ err_बंद_queues;
	पूर्ण

	*cp = c;

	वापस 0;

err_बंद_queues:
	mlx5e_बंद_queues(c);

err_napi_del:
	netअगर_napi_del(&c->napi);

	kvमुक्त(c);

	वापस err;
पूर्ण

अटल व्योम mlx5e_activate_channel(काष्ठा mlx5e_channel *c)
अणु
	पूर्णांक tc;

	napi_enable(&c->napi);

	क्रम (tc = 0; tc < c->num_tc; tc++)
		mlx5e_activate_txqsq(&c->sq[tc]);
	mlx5e_activate_icosq(&c->icosq);
	mlx5e_activate_icosq(&c->async_icosq);
	mlx5e_activate_rq(&c->rq);

	अगर (test_bit(MLX5E_CHANNEL_STATE_XSK, c->state))
		mlx5e_activate_xsk(c);
पूर्ण

अटल व्योम mlx5e_deactivate_channel(काष्ठा mlx5e_channel *c)
अणु
	पूर्णांक tc;

	अगर (test_bit(MLX5E_CHANNEL_STATE_XSK, c->state))
		mlx5e_deactivate_xsk(c);

	mlx5e_deactivate_rq(&c->rq);
	mlx5e_deactivate_icosq(&c->async_icosq);
	mlx5e_deactivate_icosq(&c->icosq);
	क्रम (tc = 0; tc < c->num_tc; tc++)
		mlx5e_deactivate_txqsq(&c->sq[tc]);
	mlx5e_qos_deactivate_queues(c);

	napi_disable(&c->napi);
पूर्ण

अटल व्योम mlx5e_बंद_channel(काष्ठा mlx5e_channel *c)
अणु
	अगर (test_bit(MLX5E_CHANNEL_STATE_XSK, c->state))
		mlx5e_बंद_xsk(c);
	mlx5e_बंद_queues(c);
	mlx5e_qos_बंद_queues(c);
	netअगर_napi_del(&c->napi);

	kvमुक्त(c);
पूर्ण

पूर्णांक mlx5e_खोलो_channels(काष्ठा mlx5e_priv *priv,
			काष्ठा mlx5e_channels *chs)
अणु
	काष्ठा mlx5e_channel_param *cparam;
	पूर्णांक err = -ENOMEM;
	पूर्णांक i;

	chs->num = chs->params.num_channels;

	chs->c = kसुस्मृति(chs->num, माप(काष्ठा mlx5e_channel *), GFP_KERNEL);
	cparam = kvzalloc(माप(काष्ठा mlx5e_channel_param), GFP_KERNEL);
	अगर (!chs->c || !cparam)
		जाओ err_मुक्त;

	err = mlx5e_build_channel_param(priv->mdev, &chs->params, priv->q_counter, cparam);
	अगर (err)
		जाओ err_मुक्त;

	क्रम (i = 0; i < chs->num; i++) अणु
		काष्ठा xsk_buff_pool *xsk_pool = शून्य;

		अगर (chs->params.xdp_prog)
			xsk_pool = mlx5e_xsk_get_pool(&chs->params, chs->params.xsk, i);

		err = mlx5e_खोलो_channel(priv, i, &chs->params, cparam, xsk_pool, &chs->c[i]);
		अगर (err)
			जाओ err_बंद_channels;
	पूर्ण

	अगर (MLX5E_GET_PFLAG(&chs->params, MLX5E_PFLAG_TX_PORT_TS) || chs->params.ptp_rx) अणु
		err = mlx5e_ptp_खोलो(priv, &chs->params, chs->c[0]->lag_port, &chs->ptp);
		अगर (err)
			जाओ err_बंद_channels;
	पूर्ण

	err = mlx5e_qos_खोलो_queues(priv, chs);
	अगर (err)
		जाओ err_बंद_ptp;

	mlx5e_health_channels_update(priv);
	kvमुक्त(cparam);
	वापस 0;

err_बंद_ptp:
	अगर (chs->ptp)
		mlx5e_ptp_बंद(chs->ptp);

err_बंद_channels:
	क्रम (i--; i >= 0; i--)
		mlx5e_बंद_channel(chs->c[i]);

err_मुक्त:
	kमुक्त(chs->c);
	kvमुक्त(cparam);
	chs->num = 0;
	वापस err;
पूर्ण

अटल व्योम mlx5e_activate_channels(काष्ठा mlx5e_channels *chs)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < chs->num; i++)
		mlx5e_activate_channel(chs->c[i]);

	अगर (chs->ptp)
		mlx5e_ptp_activate_channel(chs->ptp);
पूर्ण

#घोषणा MLX5E_RQ_WQES_TIMEOUT 20000 /* msecs */

अटल पूर्णांक mlx5e_रुको_channels_min_rx_wqes(काष्ठा mlx5e_channels *chs)
अणु
	पूर्णांक err = 0;
	पूर्णांक i;

	क्रम (i = 0; i < chs->num; i++) अणु
		पूर्णांक समयout = err ? 0 : MLX5E_RQ_WQES_TIMEOUT;

		err |= mlx5e_रुको_क्रम_min_rx_wqes(&chs->c[i]->rq, समयout);

		/* Don't रुको on the XSK RQ, because the newer xdpsock sample
		 * करोesn't provide any Fill Ring entries at the setup stage.
		 */
	पूर्ण

	वापस err ? -ETIMEDOUT : 0;
पूर्ण

अटल व्योम mlx5e_deactivate_channels(काष्ठा mlx5e_channels *chs)
अणु
	पूर्णांक i;

	अगर (chs->ptp)
		mlx5e_ptp_deactivate_channel(chs->ptp);

	क्रम (i = 0; i < chs->num; i++)
		mlx5e_deactivate_channel(chs->c[i]);
पूर्ण

व्योम mlx5e_बंद_channels(काष्ठा mlx5e_channels *chs)
अणु
	पूर्णांक i;

	अगर (chs->ptp) अणु
		mlx5e_ptp_बंद(chs->ptp);
		chs->ptp = शून्य;
	पूर्ण
	क्रम (i = 0; i < chs->num; i++)
		mlx5e_बंद_channel(chs->c[i]);

	kमुक्त(chs->c);
	chs->num = 0;
पूर्ण

अटल पूर्णांक
mlx5e_create_rqt(काष्ठा mlx5e_priv *priv, पूर्णांक sz, काष्ठा mlx5e_rqt *rqt)
अणु
	काष्ठा mlx5_core_dev *mdev = priv->mdev;
	व्योम *rqtc;
	पूर्णांक inlen;
	पूर्णांक err;
	u32 *in;
	पूर्णांक i;

	inlen = MLX5_ST_SZ_BYTES(create_rqt_in) + माप(u32) * sz;
	in = kvzalloc(inlen, GFP_KERNEL);
	अगर (!in)
		वापस -ENOMEM;

	rqtc = MLX5_ADDR_OF(create_rqt_in, in, rqt_context);

	MLX5_SET(rqtc, rqtc, rqt_actual_size, sz);
	MLX5_SET(rqtc, rqtc, rqt_max_size, sz);

	क्रम (i = 0; i < sz; i++)
		MLX5_SET(rqtc, rqtc, rq_num[i], priv->drop_rq.rqn);

	err = mlx5_core_create_rqt(mdev, in, inlen, &rqt->rqtn);
	अगर (!err)
		rqt->enabled = true;

	kvमुक्त(in);
	वापस err;
पूर्ण

व्योम mlx5e_destroy_rqt(काष्ठा mlx5e_priv *priv, काष्ठा mlx5e_rqt *rqt)
अणु
	rqt->enabled = false;
	mlx5_core_destroy_rqt(priv->mdev, rqt->rqtn);
पूर्ण

पूर्णांक mlx5e_create_indirect_rqt(काष्ठा mlx5e_priv *priv)
अणु
	काष्ठा mlx5e_rqt *rqt = &priv->indir_rqt;
	पूर्णांक err;

	err = mlx5e_create_rqt(priv, MLX5E_INसूची_RQT_SIZE, rqt);
	अगर (err)
		mlx5_core_warn(priv->mdev, "create indirect rqts failed, %d\n", err);
	वापस err;
पूर्ण

पूर्णांक mlx5e_create_direct_rqts(काष्ठा mlx5e_priv *priv, काष्ठा mlx5e_tir *tirs, पूर्णांक n)
अणु
	पूर्णांक err;
	पूर्णांक ix;

	क्रम (ix = 0; ix < n; ix++) अणु
		err = mlx5e_create_rqt(priv, 1 /*size */, &tirs[ix].rqt);
		अगर (unlikely(err))
			जाओ err_destroy_rqts;
	पूर्ण

	वापस 0;

err_destroy_rqts:
	mlx5_core_warn(priv->mdev, "create rqts failed, %d\n", err);
	क्रम (ix--; ix >= 0; ix--)
		mlx5e_destroy_rqt(priv, &tirs[ix].rqt);

	वापस err;
पूर्ण

व्योम mlx5e_destroy_direct_rqts(काष्ठा mlx5e_priv *priv, काष्ठा mlx5e_tir *tirs, पूर्णांक n)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < n; i++)
		mlx5e_destroy_rqt(priv, &tirs[i].rqt);
पूर्ण

अटल पूर्णांक mlx5e_rx_hash_fn(पूर्णांक hfunc)
अणु
	वापस (hfunc == ETH_RSS_HASH_TOP) ?
	       MLX5_RX_HASH_FN_TOEPLITZ :
	       MLX5_RX_HASH_FN_INVERTED_XOR8;
पूर्ण

पूर्णांक mlx5e_bits_invert(अचिन्हित दीर्घ a, पूर्णांक size)
अणु
	पूर्णांक inv = 0;
	पूर्णांक i;

	क्रम (i = 0; i < size; i++)
		inv |= (test_bit(size - i - 1, &a) ? 1 : 0) << i;

	वापस inv;
पूर्ण

अटल व्योम mlx5e_fill_rqt_rqns(काष्ठा mlx5e_priv *priv, पूर्णांक sz,
				काष्ठा mlx5e_redirect_rqt_param rrp, व्योम *rqtc)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < sz; i++) अणु
		u32 rqn;

		अगर (rrp.is_rss) अणु
			पूर्णांक ix = i;

			अगर (rrp.rss.hfunc == ETH_RSS_HASH_XOR)
				ix = mlx5e_bits_invert(i, ilog2(sz));

			ix = priv->rss_params.indirection_rqt[ix];
			rqn = rrp.rss.channels->c[ix]->rq.rqn;
		पूर्ण अन्यथा अणु
			rqn = rrp.rqn;
		पूर्ण
		MLX5_SET(rqtc, rqtc, rq_num[i], rqn);
	पूर्ण
पूर्ण

पूर्णांक mlx5e_redirect_rqt(काष्ठा mlx5e_priv *priv, u32 rqtn, पूर्णांक sz,
		       काष्ठा mlx5e_redirect_rqt_param rrp)
अणु
	काष्ठा mlx5_core_dev *mdev = priv->mdev;
	व्योम *rqtc;
	पूर्णांक inlen;
	u32 *in;
	पूर्णांक err;

	inlen = MLX5_ST_SZ_BYTES(modअगरy_rqt_in) + माप(u32) * sz;
	in = kvzalloc(inlen, GFP_KERNEL);
	अगर (!in)
		वापस -ENOMEM;

	rqtc = MLX5_ADDR_OF(modअगरy_rqt_in, in, ctx);

	MLX5_SET(rqtc, rqtc, rqt_actual_size, sz);
	MLX5_SET(modअगरy_rqt_in, in, biपंचांगask.rqn_list, 1);
	mlx5e_fill_rqt_rqns(priv, sz, rrp, rqtc);
	err = mlx5_core_modअगरy_rqt(mdev, rqtn, in, inlen);

	kvमुक्त(in);
	वापस err;
पूर्ण

अटल u32 mlx5e_get_direct_rqn(काष्ठा mlx5e_priv *priv, पूर्णांक ix,
				काष्ठा mlx5e_redirect_rqt_param rrp)
अणु
	अगर (!rrp.is_rss)
		वापस rrp.rqn;

	अगर (ix >= rrp.rss.channels->num)
		वापस priv->drop_rq.rqn;

	वापस rrp.rss.channels->c[ix]->rq.rqn;
पूर्ण

अटल व्योम mlx5e_redirect_rqts(काष्ठा mlx5e_priv *priv,
				काष्ठा mlx5e_redirect_rqt_param rrp,
				काष्ठा mlx5e_redirect_rqt_param *ptp_rrp)
अणु
	u32 rqtn;
	पूर्णांक ix;

	अगर (priv->indir_rqt.enabled) अणु
		/* RSS RQ table */
		rqtn = priv->indir_rqt.rqtn;
		mlx5e_redirect_rqt(priv, rqtn, MLX5E_INसूची_RQT_SIZE, rrp);
	पूर्ण

	क्रम (ix = 0; ix < priv->max_nch; ix++) अणु
		काष्ठा mlx5e_redirect_rqt_param direct_rrp = अणु
			.is_rss = false,
			अणु
				.rqn    = mlx5e_get_direct_rqn(priv, ix, rrp)
			पूर्ण,
		पूर्ण;

		/* Direct RQ Tables */
		अगर (!priv->direct_tir[ix].rqt.enabled)
			जारी;

		rqtn = priv->direct_tir[ix].rqt.rqtn;
		mlx5e_redirect_rqt(priv, rqtn, 1, direct_rrp);
	पूर्ण
	अगर (ptp_rrp) अणु
		rqtn = priv->ptp_tir.rqt.rqtn;
		mlx5e_redirect_rqt(priv, rqtn, 1, *ptp_rrp);
	पूर्ण
पूर्ण

अटल व्योम mlx5e_redirect_rqts_to_channels(काष्ठा mlx5e_priv *priv,
					    काष्ठा mlx5e_channels *chs)
अणु
	bool rx_ptp_support = priv->profile->rx_ptp_support;
	काष्ठा mlx5e_redirect_rqt_param *ptp_rrp_p = शून्य;
	काष्ठा mlx5e_redirect_rqt_param rrp = अणु
		.is_rss        = true,
		अणु
			.rss = अणु
				.channels  = chs,
				.hfunc     = priv->rss_params.hfunc,
			पूर्ण
		पूर्ण,
	पूर्ण;
	काष्ठा mlx5e_redirect_rqt_param ptp_rrp;

	अगर (rx_ptp_support) अणु
		u32 ptp_rqn;

		ptp_rrp.is_rss = false;
		ptp_rrp.rqn = mlx5e_ptp_get_rqn(priv->channels.ptp, &ptp_rqn) ?
			      priv->drop_rq.rqn : ptp_rqn;
		ptp_rrp_p = &ptp_rrp;
	पूर्ण
	mlx5e_redirect_rqts(priv, rrp, ptp_rrp_p);
पूर्ण

अटल व्योम mlx5e_redirect_rqts_to_drop(काष्ठा mlx5e_priv *priv)
अणु
	bool rx_ptp_support = priv->profile->rx_ptp_support;
	काष्ठा mlx5e_redirect_rqt_param drop_rrp = अणु
		.is_rss = false,
		अणु
			.rqn = priv->drop_rq.rqn,
		पूर्ण,
	पूर्ण;

	mlx5e_redirect_rqts(priv, drop_rrp, rx_ptp_support ? &drop_rrp : शून्य);
पूर्ण

अटल स्थिर काष्ठा mlx5e_tirc_config tirc_शेष_config[MLX5E_NUM_INसूची_TIRS] = अणु
	[MLX5E_TT_IPV4_TCP] = अणु .l3_prot_type = MLX5_L3_PROT_TYPE_IPV4,
				.l4_prot_type = MLX5_L4_PROT_TYPE_TCP,
				.rx_hash_fields = MLX5_HASH_IP_L4PORTS,
	पूर्ण,
	[MLX5E_TT_IPV6_TCP] = अणु .l3_prot_type = MLX5_L3_PROT_TYPE_IPV6,
				.l4_prot_type = MLX5_L4_PROT_TYPE_TCP,
				.rx_hash_fields = MLX5_HASH_IP_L4PORTS,
	पूर्ण,
	[MLX5E_TT_IPV4_UDP] = अणु .l3_prot_type = MLX5_L3_PROT_TYPE_IPV4,
				.l4_prot_type = MLX5_L4_PROT_TYPE_UDP,
				.rx_hash_fields = MLX5_HASH_IP_L4PORTS,
	पूर्ण,
	[MLX5E_TT_IPV6_UDP] = अणु .l3_prot_type = MLX5_L3_PROT_TYPE_IPV6,
				.l4_prot_type = MLX5_L4_PROT_TYPE_UDP,
				.rx_hash_fields = MLX5_HASH_IP_L4PORTS,
	पूर्ण,
	[MLX5E_TT_IPV4_IPSEC_AH] = अणु .l3_prot_type = MLX5_L3_PROT_TYPE_IPV4,
				     .l4_prot_type = 0,
				     .rx_hash_fields = MLX5_HASH_IP_IPSEC_SPI,
	पूर्ण,
	[MLX5E_TT_IPV6_IPSEC_AH] = अणु .l3_prot_type = MLX5_L3_PROT_TYPE_IPV6,
				     .l4_prot_type = 0,
				     .rx_hash_fields = MLX5_HASH_IP_IPSEC_SPI,
	पूर्ण,
	[MLX5E_TT_IPV4_IPSEC_ESP] = अणु .l3_prot_type = MLX5_L3_PROT_TYPE_IPV4,
				      .l4_prot_type = 0,
				      .rx_hash_fields = MLX5_HASH_IP_IPSEC_SPI,
	पूर्ण,
	[MLX5E_TT_IPV6_IPSEC_ESP] = अणु .l3_prot_type = MLX5_L3_PROT_TYPE_IPV6,
				      .l4_prot_type = 0,
				      .rx_hash_fields = MLX5_HASH_IP_IPSEC_SPI,
	पूर्ण,
	[MLX5E_TT_IPV4] = अणु .l3_prot_type = MLX5_L3_PROT_TYPE_IPV4,
			    .l4_prot_type = 0,
			    .rx_hash_fields = MLX5_HASH_IP,
	पूर्ण,
	[MLX5E_TT_IPV6] = अणु .l3_prot_type = MLX5_L3_PROT_TYPE_IPV6,
			    .l4_prot_type = 0,
			    .rx_hash_fields = MLX5_HASH_IP,
	पूर्ण,
पूर्ण;

काष्ठा mlx5e_tirc_config mlx5e_tirc_get_शेष_config(क्रमागत mlx5e_traffic_types tt)
अणु
	वापस tirc_शेष_config[tt];
पूर्ण

अटल व्योम mlx5e_build_tir_ctx_lro(काष्ठा mlx5e_params *params, व्योम *tirc)
अणु
	अगर (!params->lro_en)
		वापस;

#घोषणा ROUGH_MAX_L2_L3_HDR_SZ 256

	MLX5_SET(tirc, tirc, lro_enable_mask,
		 MLX5_TIRC_LRO_ENABLE_MASK_IPV4_LRO |
		 MLX5_TIRC_LRO_ENABLE_MASK_IPV6_LRO);
	MLX5_SET(tirc, tirc, lro_max_ip_payload_size,
		 (MLX5E_PARAMS_DEFAULT_LRO_WQE_SZ - ROUGH_MAX_L2_L3_HDR_SZ) >> 8);
	MLX5_SET(tirc, tirc, lro_समयout_period_usecs, params->lro_समयout);
पूर्ण

व्योम mlx5e_build_indir_tir_ctx_hash(काष्ठा mlx5e_rss_params *rss_params,
				    स्थिर काष्ठा mlx5e_tirc_config *ttconfig,
				    व्योम *tirc, bool inner)
अणु
	व्योम *hfso = inner ? MLX5_ADDR_OF(tirc, tirc, rx_hash_field_selector_inner) :
			     MLX5_ADDR_OF(tirc, tirc, rx_hash_field_selector_outer);

	MLX5_SET(tirc, tirc, rx_hash_fn, mlx5e_rx_hash_fn(rss_params->hfunc));
	अगर (rss_params->hfunc == ETH_RSS_HASH_TOP) अणु
		व्योम *rss_key = MLX5_ADDR_OF(tirc, tirc,
					     rx_hash_toeplitz_key);
		माप_प्रकार len = MLX5_FLD_SZ_BYTES(tirc,
					       rx_hash_toeplitz_key);

		MLX5_SET(tirc, tirc, rx_hash_symmetric, 1);
		स_नकल(rss_key, rss_params->toeplitz_hash_key, len);
	पूर्ण
	MLX5_SET(rx_hash_field_select, hfso, l3_prot_type,
		 ttconfig->l3_prot_type);
	MLX5_SET(rx_hash_field_select, hfso, l4_prot_type,
		 ttconfig->l4_prot_type);
	MLX5_SET(rx_hash_field_select, hfso, selected_fields,
		 ttconfig->rx_hash_fields);
पूर्ण

अटल व्योम mlx5e_update_rx_hash_fields(काष्ठा mlx5e_tirc_config *ttconfig,
					क्रमागत mlx5e_traffic_types tt,
					u32 rx_hash_fields)
अणु
	*ttconfig                = tirc_शेष_config[tt];
	ttconfig->rx_hash_fields = rx_hash_fields;
पूर्ण

व्योम mlx5e_modअगरy_tirs_hash(काष्ठा mlx5e_priv *priv, व्योम *in)
अणु
	व्योम *tirc = MLX5_ADDR_OF(modअगरy_tir_in, in, ctx);
	काष्ठा mlx5e_rss_params *rss = &priv->rss_params;
	काष्ठा mlx5_core_dev *mdev = priv->mdev;
	पूर्णांक ctxlen = MLX5_ST_SZ_BYTES(tirc);
	काष्ठा mlx5e_tirc_config ttconfig;
	पूर्णांक tt;

	MLX5_SET(modअगरy_tir_in, in, biपंचांगask.hash, 1);

	क्रम (tt = 0; tt < MLX5E_NUM_INसूची_TIRS; tt++) अणु
		स_रखो(tirc, 0, ctxlen);
		mlx5e_update_rx_hash_fields(&ttconfig, tt,
					    rss->rx_hash_fields[tt]);
		mlx5e_build_indir_tir_ctx_hash(rss, &ttconfig, tirc, false);
		mlx5_core_modअगरy_tir(mdev, priv->indir_tir[tt].tirn, in);
	पूर्ण

	/* Verअगरy inner tirs resources allocated */
	अगर (!priv->inner_indir_tir[0].tirn)
		वापस;

	क्रम (tt = 0; tt < MLX5E_NUM_INसूची_TIRS; tt++) अणु
		स_रखो(tirc, 0, ctxlen);
		mlx5e_update_rx_hash_fields(&ttconfig, tt,
					    rss->rx_hash_fields[tt]);
		mlx5e_build_indir_tir_ctx_hash(rss, &ttconfig, tirc, true);
		mlx5_core_modअगरy_tir(mdev, priv->inner_indir_tir[tt].tirn, in);
	पूर्ण
पूर्ण

अटल पूर्णांक mlx5e_modअगरy_tirs_lro(काष्ठा mlx5e_priv *priv)
अणु
	काष्ठा mlx5_core_dev *mdev = priv->mdev;

	व्योम *in;
	व्योम *tirc;
	पूर्णांक inlen;
	पूर्णांक err;
	पूर्णांक tt;
	पूर्णांक ix;

	inlen = MLX5_ST_SZ_BYTES(modअगरy_tir_in);
	in = kvzalloc(inlen, GFP_KERNEL);
	अगर (!in)
		वापस -ENOMEM;

	MLX5_SET(modअगरy_tir_in, in, biपंचांगask.lro, 1);
	tirc = MLX5_ADDR_OF(modअगरy_tir_in, in, ctx);

	mlx5e_build_tir_ctx_lro(&priv->channels.params, tirc);

	क्रम (tt = 0; tt < MLX5E_NUM_INसूची_TIRS; tt++) अणु
		err = mlx5_core_modअगरy_tir(mdev, priv->indir_tir[tt].tirn, in);
		अगर (err)
			जाओ मुक्त_in;
	पूर्ण

	क्रम (ix = 0; ix < priv->max_nch; ix++) अणु
		err = mlx5_core_modअगरy_tir(mdev, priv->direct_tir[ix].tirn, in);
		अगर (err)
			जाओ मुक्त_in;
	पूर्ण

मुक्त_in:
	kvमुक्त(in);

	वापस err;
पूर्ण

अटल MLX5E_DEFINE_PREACTIVATE_WRAPPER_CTX(mlx5e_modअगरy_tirs_lro);

अटल पूर्णांक mlx5e_set_mtu(काष्ठा mlx5_core_dev *mdev,
			 काष्ठा mlx5e_params *params, u16 mtu)
अणु
	u16 hw_mtu = MLX5E_SW2HW_MTU(params, mtu);
	पूर्णांक err;

	err = mlx5_set_port_mtu(mdev, hw_mtu, 1);
	अगर (err)
		वापस err;

	/* Update vport context MTU */
	mlx5_modअगरy_nic_vport_mtu(mdev, hw_mtu);
	वापस 0;
पूर्ण

अटल व्योम mlx5e_query_mtu(काष्ठा mlx5_core_dev *mdev,
			    काष्ठा mlx5e_params *params, u16 *mtu)
अणु
	u16 hw_mtu = 0;
	पूर्णांक err;

	err = mlx5_query_nic_vport_mtu(mdev, &hw_mtu);
	अगर (err || !hw_mtu) /* fallback to port oper mtu */
		mlx5_query_port_oper_mtu(mdev, &hw_mtu, 1);

	*mtu = MLX5E_HW2SW_MTU(params, hw_mtu);
पूर्ण

पूर्णांक mlx5e_set_dev_port_mtu(काष्ठा mlx5e_priv *priv)
अणु
	काष्ठा mlx5e_params *params = &priv->channels.params;
	काष्ठा net_device *netdev = priv->netdev;
	काष्ठा mlx5_core_dev *mdev = priv->mdev;
	u16 mtu;
	पूर्णांक err;

	err = mlx5e_set_mtu(mdev, params, params->sw_mtu);
	अगर (err)
		वापस err;

	mlx5e_query_mtu(mdev, params, &mtu);
	अगर (mtu != params->sw_mtu)
		netdev_warn(netdev, "%s: VPort MTU %d is different than netdev mtu %d\n",
			    __func__, mtu, params->sw_mtu);

	params->sw_mtu = mtu;
	वापस 0;
पूर्ण

MLX5E_DEFINE_PREACTIVATE_WRAPPER_CTX(mlx5e_set_dev_port_mtu);

व्योम mlx5e_set_netdev_mtu_boundaries(काष्ठा mlx5e_priv *priv)
अणु
	काष्ठा mlx5e_params *params = &priv->channels.params;
	काष्ठा net_device *netdev   = priv->netdev;
	काष्ठा mlx5_core_dev *mdev  = priv->mdev;
	u16 max_mtu;

	/* MTU range: 68 - hw-specअगरic max */
	netdev->min_mtu = ETH_MIN_MTU;

	mlx5_query_port_max_mtu(mdev, &max_mtu, 1);
	netdev->max_mtu = min_t(अचिन्हित पूर्णांक, MLX5E_HW2SW_MTU(params, max_mtu),
				ETH_MAX_MTU);
पूर्ण

अटल व्योम mlx5e_netdev_set_tcs(काष्ठा net_device *netdev, u16 nch, u8 ntc)
अणु
	पूर्णांक tc;

	netdev_reset_tc(netdev);

	अगर (ntc == 1)
		वापस;

	netdev_set_num_tc(netdev, ntc);

	/* Map netdev TCs to offset 0
	 * We have our own UP to TXQ mapping क्रम QoS
	 */
	क्रम (tc = 0; tc < ntc; tc++)
		netdev_set_tc_queue(netdev, tc, nch, 0);
पूर्ण

पूर्णांक mlx5e_update_tx_netdev_queues(काष्ठा mlx5e_priv *priv)
अणु
	पूर्णांक qos_queues, nch, ntc, num_txqs, err;

	qos_queues = mlx5e_qos_cur_leaf_nodes(priv);

	nch = priv->channels.params.num_channels;
	ntc = priv->channels.params.num_tc;
	num_txqs = nch * ntc + qos_queues;
	अगर (MLX5E_GET_PFLAG(&priv->channels.params, MLX5E_PFLAG_TX_PORT_TS))
		num_txqs += ntc;

	mlx5e_dbg(DRV, priv, "Setting num_txqs %d\n", num_txqs);
	err = netअगर_set_real_num_tx_queues(priv->netdev, num_txqs);
	अगर (err)
		netdev_warn(priv->netdev, "netif_set_real_num_tx_queues failed, %d\n", err);

	वापस err;
पूर्ण

अटल पूर्णांक mlx5e_update_netdev_queues(काष्ठा mlx5e_priv *priv)
अणु
	काष्ठा net_device *netdev = priv->netdev;
	पूर्णांक old_num_txqs, old_ntc;
	पूर्णांक num_rxqs, nch, ntc;
	पूर्णांक err;

	old_num_txqs = netdev->real_num_tx_queues;
	old_ntc = netdev->num_tc ? : 1;

	nch = priv->channels.params.num_channels;
	ntc = priv->channels.params.num_tc;
	num_rxqs = nch * priv->profile->rq_groups;

	mlx5e_netdev_set_tcs(netdev, nch, ntc);

	err = mlx5e_update_tx_netdev_queues(priv);
	अगर (err)
		जाओ err_tcs;
	err = netअगर_set_real_num_rx_queues(netdev, num_rxqs);
	अगर (err) अणु
		netdev_warn(netdev, "netif_set_real_num_rx_queues failed, %d\n", err);
		जाओ err_txqs;
	पूर्ण

	वापस 0;

err_txqs:
	/* netअगर_set_real_num_rx_queues could fail only when nch increased. Only
	 * one of nch and ntc is changed in this function. That means, the call
	 * to netअगर_set_real_num_tx_queues below should not fail, because it
	 * decreases the number of TX queues.
	 */
	WARN_ON_ONCE(netअगर_set_real_num_tx_queues(netdev, old_num_txqs));

err_tcs:
	mlx5e_netdev_set_tcs(netdev, old_num_txqs / old_ntc, old_ntc);
	वापस err;
पूर्ण

अटल व्योम mlx5e_set_शेष_xps_cpumasks(काष्ठा mlx5e_priv *priv,
					   काष्ठा mlx5e_params *params)
अणु
	काष्ठा mlx5_core_dev *mdev = priv->mdev;
	पूर्णांक num_comp_vectors, ix, irq;

	num_comp_vectors = mlx5_comp_vectors_count(mdev);

	क्रम (ix = 0; ix < params->num_channels; ix++) अणु
		cpumask_clear(priv->scratchpad.cpumask);

		क्रम (irq = ix; irq < num_comp_vectors; irq += params->num_channels) अणु
			पूर्णांक cpu = cpumask_first(mlx5_comp_irq_get_affinity_mask(mdev, irq));

			cpumask_set_cpu(cpu, priv->scratchpad.cpumask);
		पूर्ण

		netअगर_set_xps_queue(priv->netdev, priv->scratchpad.cpumask, ix);
	पूर्ण
पूर्ण

पूर्णांक mlx5e_num_channels_changed(काष्ठा mlx5e_priv *priv)
अणु
	u16 count = priv->channels.params.num_channels;
	पूर्णांक err;

	err = mlx5e_update_netdev_queues(priv);
	अगर (err)
		वापस err;

	mlx5e_set_शेष_xps_cpumasks(priv, &priv->channels.params);

	अगर (!netअगर_is_rxfh_configured(priv->netdev))
		mlx5e_build_शेष_indir_rqt(priv->rss_params.indirection_rqt,
					      MLX5E_INसूची_RQT_SIZE, count);

	वापस 0;
पूर्ण

MLX5E_DEFINE_PREACTIVATE_WRAPPER_CTX(mlx5e_num_channels_changed);

अटल व्योम mlx5e_build_txq_maps(काष्ठा mlx5e_priv *priv)
अणु
	पूर्णांक i, ch, tc, num_tc;

	ch = priv->channels.num;
	num_tc = priv->channels.params.num_tc;

	क्रम (i = 0; i < ch; i++) अणु
		क्रम (tc = 0; tc < num_tc; tc++) अणु
			काष्ठा mlx5e_channel *c = priv->channels.c[i];
			काष्ठा mlx5e_txqsq *sq = &c->sq[tc];

			priv->txq2sq[sq->txq_ix] = sq;
			priv->channel_tc2realtxq[i][tc] = i + tc * ch;
		पूर्ण
	पूर्ण

	अगर (!priv->channels.ptp)
		वापस;

	अगर (!test_bit(MLX5E_PTP_STATE_TX, priv->channels.ptp->state))
		वापस;

	क्रम (tc = 0; tc < num_tc; tc++) अणु
		काष्ठा mlx5e_ptp *c = priv->channels.ptp;
		काष्ठा mlx5e_txqsq *sq = &c->ptpsq[tc].txqsq;

		priv->txq2sq[sq->txq_ix] = sq;
		priv->port_ptp_tc2realtxq[tc] = priv->num_tc_x_num_ch + tc;
	पूर्ण
पूर्ण

अटल व्योम mlx5e_update_num_tc_x_num_ch(काष्ठा mlx5e_priv *priv)
अणु
	/* Sync with mlx5e_select_queue. */
	WRITE_ONCE(priv->num_tc_x_num_ch,
		   priv->channels.params.num_tc * priv->channels.num);
पूर्ण

व्योम mlx5e_activate_priv_channels(काष्ठा mlx5e_priv *priv)
अणु
	mlx5e_update_num_tc_x_num_ch(priv);
	mlx5e_build_txq_maps(priv);
	mlx5e_activate_channels(&priv->channels);
	mlx5e_qos_activate_queues(priv);
	mlx5e_xdp_tx_enable(priv);
	netअगर_tx_start_all_queues(priv->netdev);

	अगर (mlx5e_is_vport_rep(priv))
		mlx5e_add_sqs_fwd_rules(priv);

	mlx5e_रुको_channels_min_rx_wqes(&priv->channels);
	mlx5e_redirect_rqts_to_channels(priv, &priv->channels);

	mlx5e_xsk_redirect_rqts_to_channels(priv, &priv->channels);
पूर्ण

व्योम mlx5e_deactivate_priv_channels(काष्ठा mlx5e_priv *priv)
अणु
	mlx5e_xsk_redirect_rqts_to_drop(priv, &priv->channels);

	mlx5e_redirect_rqts_to_drop(priv);

	अगर (mlx5e_is_vport_rep(priv))
		mlx5e_हटाओ_sqs_fwd_rules(priv);

	/* FIXME: This is a W/A only क्रम tx समयout watch करोg false alarm when
	 * polling क्रम inactive tx queues.
	 */
	netअगर_tx_stop_all_queues(priv->netdev);
	netअगर_tx_disable(priv->netdev);
	mlx5e_xdp_tx_disable(priv);
	mlx5e_deactivate_channels(&priv->channels);
पूर्ण

अटल पूर्णांक mlx5e_चयन_priv_params(काष्ठा mlx5e_priv *priv,
				    काष्ठा mlx5e_params *new_params,
				    mlx5e_fp_preactivate preactivate,
				    व्योम *context)
अणु
	काष्ठा mlx5e_params old_params;

	old_params = priv->channels.params;
	priv->channels.params = *new_params;

	अगर (preactivate) अणु
		पूर्णांक err;

		err = preactivate(priv, context);
		अगर (err) अणु
			priv->channels.params = old_params;
			वापस err;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mlx5e_चयन_priv_channels(काष्ठा mlx5e_priv *priv,
				      काष्ठा mlx5e_channels *new_chs,
				      mlx5e_fp_preactivate preactivate,
				      व्योम *context)
अणु
	काष्ठा net_device *netdev = priv->netdev;
	काष्ठा mlx5e_channels old_chs;
	पूर्णांक carrier_ok;
	पूर्णांक err = 0;

	carrier_ok = netअगर_carrier_ok(netdev);
	netअगर_carrier_off(netdev);

	mlx5e_deactivate_priv_channels(priv);

	old_chs = priv->channels;
	priv->channels = *new_chs;

	/* New channels are पढ़ोy to roll, call the preactivate hook अगर needed
	 * to modअगरy HW settings or update kernel parameters.
	 */
	अगर (preactivate) अणु
		err = preactivate(priv, context);
		अगर (err) अणु
			priv->channels = old_chs;
			जाओ out;
		पूर्ण
	पूर्ण

	mlx5e_बंद_channels(&old_chs);
	priv->profile->update_rx(priv);

out:
	mlx5e_activate_priv_channels(priv);

	/* वापस carrier back अगर needed */
	अगर (carrier_ok)
		netअगर_carrier_on(netdev);

	वापस err;
पूर्ण

पूर्णांक mlx5e_safe_चयन_params(काष्ठा mlx5e_priv *priv,
			     काष्ठा mlx5e_params *params,
			     mlx5e_fp_preactivate preactivate,
			     व्योम *context, bool reset)
अणु
	काष्ठा mlx5e_channels new_chs = अणुपूर्ण;
	पूर्णांक err;

	reset &= test_bit(MLX5E_STATE_OPENED, &priv->state);
	अगर (!reset)
		वापस mlx5e_चयन_priv_params(priv, params, preactivate, context);

	new_chs.params = *params;
	err = mlx5e_खोलो_channels(priv, &new_chs);
	अगर (err)
		वापस err;
	err = mlx5e_चयन_priv_channels(priv, &new_chs, preactivate, context);
	अगर (err)
		mlx5e_बंद_channels(&new_chs);

	वापस err;
पूर्ण

पूर्णांक mlx5e_safe_reखोलो_channels(काष्ठा mlx5e_priv *priv)
अणु
	वापस mlx5e_safe_चयन_params(priv, &priv->channels.params, शून्य, शून्य, true);
पूर्ण

व्योम mlx5e_बारtamp_init(काष्ठा mlx5e_priv *priv)
अणु
	priv->tstamp.tx_type   = HWTSTAMP_TX_OFF;
	priv->tstamp.rx_filter = HWTSTAMP_FILTER_NONE;
पूर्ण

अटल व्योम mlx5e_modअगरy_admin_state(काष्ठा mlx5_core_dev *mdev,
				     क्रमागत mlx5_port_status state)
अणु
	काष्ठा mlx5_eचयन *esw = mdev->priv.eचयन;
	पूर्णांक vport_admin_state;

	mlx5_set_port_admin_status(mdev, state);

	अगर (mlx5_eचयन_mode(mdev) == MLX5_ESWITCH_OFFLOADS ||
	    !MLX5_CAP_GEN(mdev, uplink_follow))
		वापस;

	अगर (state == MLX5_PORT_UP)
		vport_admin_state = MLX5_VPORT_ADMIN_STATE_AUTO;
	अन्यथा
		vport_admin_state = MLX5_VPORT_ADMIN_STATE_DOWN;

	mlx5_eचयन_set_vport_state(esw, MLX5_VPORT_UPLINK, vport_admin_state);
पूर्ण

पूर्णांक mlx5e_खोलो_locked(काष्ठा net_device *netdev)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(netdev);
	पूर्णांक err;

	set_bit(MLX5E_STATE_OPENED, &priv->state);

	err = mlx5e_खोलो_channels(priv, &priv->channels);
	अगर (err)
		जाओ err_clear_state_खोलोed_flag;

	priv->profile->update_rx(priv);
	mlx5e_activate_priv_channels(priv);
	mlx5e_apply_traps(priv, true);
	अगर (priv->profile->update_carrier)
		priv->profile->update_carrier(priv);

	mlx5e_queue_update_stats(priv);
	वापस 0;

err_clear_state_खोलोed_flag:
	clear_bit(MLX5E_STATE_OPENED, &priv->state);
	वापस err;
पूर्ण

पूर्णांक mlx5e_खोलो(काष्ठा net_device *netdev)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(netdev);
	पूर्णांक err;

	mutex_lock(&priv->state_lock);
	err = mlx5e_खोलो_locked(netdev);
	अगर (!err)
		mlx5e_modअगरy_admin_state(priv->mdev, MLX5_PORT_UP);
	mutex_unlock(&priv->state_lock);

	वापस err;
पूर्ण

पूर्णांक mlx5e_बंद_locked(काष्ठा net_device *netdev)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(netdev);

	/* May alपढ़ोy be CLOSED in हाल a previous configuration operation
	 * (e.g RX/TX queue size change) that involves बंद&खोलो failed.
	 */
	अगर (!test_bit(MLX5E_STATE_OPENED, &priv->state))
		वापस 0;

	mlx5e_apply_traps(priv, false);
	clear_bit(MLX5E_STATE_OPENED, &priv->state);

	netअगर_carrier_off(priv->netdev);
	mlx5e_deactivate_priv_channels(priv);
	mlx5e_बंद_channels(&priv->channels);

	वापस 0;
पूर्ण

पूर्णांक mlx5e_बंद(काष्ठा net_device *netdev)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(netdev);
	पूर्णांक err;

	अगर (!netअगर_device_present(netdev))
		वापस -ENODEV;

	mutex_lock(&priv->state_lock);
	mlx5e_modअगरy_admin_state(priv->mdev, MLX5_PORT_DOWN);
	err = mlx5e_बंद_locked(netdev);
	mutex_unlock(&priv->state_lock);

	वापस err;
पूर्ण

अटल व्योम mlx5e_मुक्त_drop_rq(काष्ठा mlx5e_rq *rq)
अणु
	mlx5_wq_destroy(&rq->wq_ctrl);
पूर्ण

अटल पूर्णांक mlx5e_alloc_drop_rq(काष्ठा mlx5_core_dev *mdev,
			       काष्ठा mlx5e_rq *rq,
			       काष्ठा mlx5e_rq_param *param)
अणु
	व्योम *rqc = param->rqc;
	व्योम *rqc_wq = MLX5_ADDR_OF(rqc, rqc, wq);
	पूर्णांक err;

	param->wq.db_numa_node = param->wq.buf_numa_node;

	err = mlx5_wq_cyc_create(mdev, &param->wq, rqc_wq, &rq->wqe.wq,
				 &rq->wq_ctrl);
	अगर (err)
		वापस err;

	/* Mark as unused given "Drop-RQ" packets never reach XDP */
	xdp_rxq_info_unused(&rq->xdp_rxq);

	rq->mdev = mdev;

	वापस 0;
पूर्ण

अटल पूर्णांक mlx5e_alloc_drop_cq(काष्ठा mlx5e_priv *priv,
			       काष्ठा mlx5e_cq *cq,
			       काष्ठा mlx5e_cq_param *param)
अणु
	काष्ठा mlx5_core_dev *mdev = priv->mdev;

	param->wq.buf_numa_node = dev_to_node(mlx5_core_dma_dev(mdev));
	param->wq.db_numa_node  = dev_to_node(mlx5_core_dma_dev(mdev));

	वापस mlx5e_alloc_cq_common(priv, param, cq);
पूर्ण

पूर्णांक mlx5e_खोलो_drop_rq(काष्ठा mlx5e_priv *priv,
		       काष्ठा mlx5e_rq *drop_rq)
अणु
	काष्ठा mlx5_core_dev *mdev = priv->mdev;
	काष्ठा mlx5e_cq_param cq_param = अणुपूर्ण;
	काष्ठा mlx5e_rq_param rq_param = अणुपूर्ण;
	काष्ठा mlx5e_cq *cq = &drop_rq->cq;
	पूर्णांक err;

	mlx5e_build_drop_rq_param(mdev, priv->drop_rq_q_counter, &rq_param);

	err = mlx5e_alloc_drop_cq(priv, cq, &cq_param);
	अगर (err)
		वापस err;

	err = mlx5e_create_cq(cq, &cq_param);
	अगर (err)
		जाओ err_मुक्त_cq;

	err = mlx5e_alloc_drop_rq(mdev, drop_rq, &rq_param);
	अगर (err)
		जाओ err_destroy_cq;

	err = mlx5e_create_rq(drop_rq, &rq_param);
	अगर (err)
		जाओ err_मुक्त_rq;

	err = mlx5e_modअगरy_rq_state(drop_rq, MLX5_RQC_STATE_RST, MLX5_RQC_STATE_RDY);
	अगर (err)
		mlx5_core_warn(priv->mdev, "modify_rq_state failed, rx_if_down_packets won't be counted %d\n", err);

	वापस 0;

err_मुक्त_rq:
	mlx5e_मुक्त_drop_rq(drop_rq);

err_destroy_cq:
	mlx5e_destroy_cq(cq);

err_मुक्त_cq:
	mlx5e_मुक्त_cq(cq);

	वापस err;
पूर्ण

व्योम mlx5e_बंद_drop_rq(काष्ठा mlx5e_rq *drop_rq)
अणु
	mlx5e_destroy_rq(drop_rq);
	mlx5e_मुक्त_drop_rq(drop_rq);
	mlx5e_destroy_cq(&drop_rq->cq);
	mlx5e_मुक्त_cq(&drop_rq->cq);
पूर्ण

पूर्णांक mlx5e_create_tis(काष्ठा mlx5_core_dev *mdev, व्योम *in, u32 *tisn)
अणु
	व्योम *tisc = MLX5_ADDR_OF(create_tis_in, in, ctx);

	MLX5_SET(tisc, tisc, transport_करोमुख्य, mdev->mlx5e_res.hw_objs.td.tdn);

	अगर (MLX5_GET(tisc, tisc, tls_en))
		MLX5_SET(tisc, tisc, pd, mdev->mlx5e_res.hw_objs.pdn);

	अगर (mlx5_lag_is_lacp_owner(mdev))
		MLX5_SET(tisc, tisc, strict_lag_tx_port_affinity, 1);

	वापस mlx5_core_create_tis(mdev, in, tisn);
पूर्ण

व्योम mlx5e_destroy_tis(काष्ठा mlx5_core_dev *mdev, u32 tisn)
अणु
	mlx5_core_destroy_tis(mdev, tisn);
पूर्ण

व्योम mlx5e_destroy_tises(काष्ठा mlx5e_priv *priv)
अणु
	पूर्णांक tc, i;

	क्रम (i = 0; i < mlx5e_get_num_lag_ports(priv->mdev); i++)
		क्रम (tc = 0; tc < priv->profile->max_tc; tc++)
			mlx5e_destroy_tis(priv->mdev, priv->tisn[i][tc]);
पूर्ण

अटल bool mlx5e_lag_should_assign_affinity(काष्ठा mlx5_core_dev *mdev)
अणु
	वापस MLX5_CAP_GEN(mdev, lag_tx_port_affinity) && mlx5e_get_num_lag_ports(mdev) > 1;
पूर्ण

पूर्णांक mlx5e_create_tises(काष्ठा mlx5e_priv *priv)
अणु
	पूर्णांक tc, i;
	पूर्णांक err;

	क्रम (i = 0; i < mlx5e_get_num_lag_ports(priv->mdev); i++) अणु
		क्रम (tc = 0; tc < priv->profile->max_tc; tc++) अणु
			u32 in[MLX5_ST_SZ_DW(create_tis_in)] = अणुपूर्ण;
			व्योम *tisc;

			tisc = MLX5_ADDR_OF(create_tis_in, in, ctx);

			MLX5_SET(tisc, tisc, prio, tc << 1);

			अगर (mlx5e_lag_should_assign_affinity(priv->mdev))
				MLX5_SET(tisc, tisc, lag_tx_port_affinity, i + 1);

			err = mlx5e_create_tis(priv->mdev, in, &priv->tisn[i][tc]);
			अगर (err)
				जाओ err_बंद_tises;
		पूर्ण
	पूर्ण

	वापस 0;

err_बंद_tises:
	क्रम (; i >= 0; i--) अणु
		क्रम (tc--; tc >= 0; tc--)
			mlx5e_destroy_tis(priv->mdev, priv->tisn[i][tc]);
		tc = priv->profile->max_tc;
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम mlx5e_cleanup_nic_tx(काष्ठा mlx5e_priv *priv)
अणु
	mlx5e_destroy_tises(priv);
पूर्ण

अटल व्योम mlx5e_build_indir_tir_ctx_common(काष्ठा mlx5e_priv *priv,
					     u32 rqtn, u32 *tirc)
अणु
	MLX5_SET(tirc, tirc, transport_करोमुख्य, priv->mdev->mlx5e_res.hw_objs.td.tdn);
	MLX5_SET(tirc, tirc, disp_type, MLX5_TIRC_DISP_TYPE_INसूचीECT);
	MLX5_SET(tirc, tirc, indirect_table, rqtn);
	MLX5_SET(tirc, tirc, tunneled_offload_en,
		 priv->channels.params.tunneled_offload_en);

	mlx5e_build_tir_ctx_lro(&priv->channels.params, tirc);
पूर्ण

अटल व्योम mlx5e_build_indir_tir_ctx(काष्ठा mlx5e_priv *priv,
				      क्रमागत mlx5e_traffic_types tt,
				      u32 *tirc)
अणु
	mlx5e_build_indir_tir_ctx_common(priv, priv->indir_rqt.rqtn, tirc);
	mlx5e_build_indir_tir_ctx_hash(&priv->rss_params,
				       &tirc_शेष_config[tt], tirc, false);
पूर्ण

अटल व्योम mlx5e_build_direct_tir_ctx(काष्ठा mlx5e_priv *priv, u32 rqtn, u32 *tirc)
अणु
	mlx5e_build_indir_tir_ctx_common(priv, rqtn, tirc);
	MLX5_SET(tirc, tirc, rx_hash_fn, MLX5_RX_HASH_FN_INVERTED_XOR8);
पूर्ण

अटल व्योम mlx5e_build_inner_indir_tir_ctx(काष्ठा mlx5e_priv *priv,
					    क्रमागत mlx5e_traffic_types tt,
					    u32 *tirc)
अणु
	mlx5e_build_indir_tir_ctx_common(priv, priv->indir_rqt.rqtn, tirc);
	mlx5e_build_indir_tir_ctx_hash(&priv->rss_params,
				       &tirc_शेष_config[tt], tirc, true);
पूर्ण

पूर्णांक mlx5e_create_indirect_tirs(काष्ठा mlx5e_priv *priv, bool inner_ttc)
अणु
	काष्ठा mlx5e_tir *tir;
	व्योम *tirc;
	पूर्णांक inlen;
	पूर्णांक i = 0;
	पूर्णांक err;
	u32 *in;
	पूर्णांक tt;

	inlen = MLX5_ST_SZ_BYTES(create_tir_in);
	in = kvzalloc(inlen, GFP_KERNEL);
	अगर (!in)
		वापस -ENOMEM;

	क्रम (tt = 0; tt < MLX5E_NUM_INसूची_TIRS; tt++) अणु
		स_रखो(in, 0, inlen);
		tir = &priv->indir_tir[tt];
		tirc = MLX5_ADDR_OF(create_tir_in, in, ctx);
		mlx5e_build_indir_tir_ctx(priv, tt, tirc);
		err = mlx5e_create_tir(priv->mdev, tir, in);
		अगर (err) अणु
			mlx5_core_warn(priv->mdev, "create indirect tirs failed, %d\n", err);
			जाओ err_destroy_inner_tirs;
		पूर्ण
	पूर्ण

	अगर (!inner_ttc || !mlx5e_tunnel_inner_ft_supported(priv->mdev))
		जाओ out;

	क्रम (i = 0; i < MLX5E_NUM_INसूची_TIRS; i++) अणु
		स_रखो(in, 0, inlen);
		tir = &priv->inner_indir_tir[i];
		tirc = MLX5_ADDR_OF(create_tir_in, in, ctx);
		mlx5e_build_inner_indir_tir_ctx(priv, i, tirc);
		err = mlx5e_create_tir(priv->mdev, tir, in);
		अगर (err) अणु
			mlx5_core_warn(priv->mdev, "create inner indirect tirs failed, %d\n", err);
			जाओ err_destroy_inner_tirs;
		पूर्ण
	पूर्ण

out:
	kvमुक्त(in);

	वापस 0;

err_destroy_inner_tirs:
	क्रम (i--; i >= 0; i--)
		mlx5e_destroy_tir(priv->mdev, &priv->inner_indir_tir[i]);

	क्रम (tt--; tt >= 0; tt--)
		mlx5e_destroy_tir(priv->mdev, &priv->indir_tir[tt]);

	kvमुक्त(in);

	वापस err;
पूर्ण

पूर्णांक mlx5e_create_direct_tirs(काष्ठा mlx5e_priv *priv, काष्ठा mlx5e_tir *tirs, पूर्णांक n)
अणु
	काष्ठा mlx5e_tir *tir;
	व्योम *tirc;
	पूर्णांक inlen;
	पूर्णांक err = 0;
	u32 *in;
	पूर्णांक ix;

	inlen = MLX5_ST_SZ_BYTES(create_tir_in);
	in = kvzalloc(inlen, GFP_KERNEL);
	अगर (!in)
		वापस -ENOMEM;

	क्रम (ix = 0; ix < n; ix++) अणु
		स_रखो(in, 0, inlen);
		tir = &tirs[ix];
		tirc = MLX5_ADDR_OF(create_tir_in, in, ctx);
		mlx5e_build_direct_tir_ctx(priv, tir->rqt.rqtn, tirc);
		err = mlx5e_create_tir(priv->mdev, tir, in);
		अगर (unlikely(err))
			जाओ err_destroy_ch_tirs;
	पूर्ण

	जाओ out;

err_destroy_ch_tirs:
	mlx5_core_warn(priv->mdev, "create tirs failed, %d\n", err);
	क्रम (ix--; ix >= 0; ix--)
		mlx5e_destroy_tir(priv->mdev, &tirs[ix]);

out:
	kvमुक्त(in);

	वापस err;
पूर्ण

व्योम mlx5e_destroy_indirect_tirs(काष्ठा mlx5e_priv *priv)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < MLX5E_NUM_INसूची_TIRS; i++)
		mlx5e_destroy_tir(priv->mdev, &priv->indir_tir[i]);

	/* Verअगरy inner tirs resources allocated */
	अगर (!priv->inner_indir_tir[0].tirn)
		वापस;

	क्रम (i = 0; i < MLX5E_NUM_INसूची_TIRS; i++)
		mlx5e_destroy_tir(priv->mdev, &priv->inner_indir_tir[i]);
पूर्ण

व्योम mlx5e_destroy_direct_tirs(काष्ठा mlx5e_priv *priv, काष्ठा mlx5e_tir *tirs, पूर्णांक n)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < n; i++)
		mlx5e_destroy_tir(priv->mdev, &tirs[i]);
पूर्ण

अटल पूर्णांक mlx5e_modअगरy_channels_scatter_fcs(काष्ठा mlx5e_channels *chs, bool enable)
अणु
	पूर्णांक err = 0;
	पूर्णांक i;

	क्रम (i = 0; i < chs->num; i++) अणु
		err = mlx5e_modअगरy_rq_scatter_fcs(&chs->c[i]->rq, enable);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mlx5e_modअगरy_channels_vsd(काष्ठा mlx5e_channels *chs, bool vsd)
अणु
	पूर्णांक err = 0;
	पूर्णांक i;

	क्रम (i = 0; i < chs->num; i++) अणु
		err = mlx5e_modअगरy_rq_vsd(&chs->c[i]->rq, vsd);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mlx5e_setup_tc_mqprio(काष्ठा mlx5e_priv *priv,
				 काष्ठा tc_mqprio_qopt *mqprio)
अणु
	काष्ठा mlx5e_params new_params;
	u8 tc = mqprio->num_tc;
	पूर्णांक err = 0;

	mqprio->hw = TC_MQPRIO_HW_OFFLOAD_TCS;

	अगर (tc && tc != MLX5E_MAX_NUM_TC)
		वापस -EINVAL;

	mutex_lock(&priv->state_lock);

	/* MQPRIO is another toplevel qdisc that can't be attached
	 * simultaneously with the offloaded HTB.
	 */
	अगर (WARN_ON(priv->htb.maj_id)) अणु
		err = -EINVAL;
		जाओ out;
	पूर्ण

	new_params = priv->channels.params;
	new_params.num_tc = tc ? tc : 1;

	err = mlx5e_safe_चयन_params(priv, &new_params,
				       mlx5e_num_channels_changed_ctx, शून्य, true);

out:
	priv->max_खोलोed_tc = max_t(u8, priv->max_खोलोed_tc,
				    priv->channels.params.num_tc);
	mutex_unlock(&priv->state_lock);
	वापस err;
पूर्ण

अटल पूर्णांक mlx5e_setup_tc_htb(काष्ठा mlx5e_priv *priv, काष्ठा tc_htb_qopt_offload *htb)
अणु
	पूर्णांक res;

	चयन (htb->command) अणु
	हाल TC_HTB_CREATE:
		वापस mlx5e_htb_root_add(priv, htb->parent_classid, htb->classid,
					  htb->extack);
	हाल TC_HTB_DESTROY:
		वापस mlx5e_htb_root_del(priv);
	हाल TC_HTB_LEAF_ALLOC_QUEUE:
		res = mlx5e_htb_leaf_alloc_queue(priv, htb->classid, htb->parent_classid,
						 htb->rate, htb->उच्चमान, htb->extack);
		अगर (res < 0)
			वापस res;
		htb->qid = res;
		वापस 0;
	हाल TC_HTB_LEAF_TO_INNER:
		वापस mlx5e_htb_leaf_to_inner(priv, htb->parent_classid, htb->classid,
					       htb->rate, htb->उच्चमान, htb->extack);
	हाल TC_HTB_LEAF_DEL:
		वापस mlx5e_htb_leaf_del(priv, htb->classid, &htb->moved_qid, &htb->qid,
					  htb->extack);
	हाल TC_HTB_LEAF_DEL_LAST:
	हाल TC_HTB_LEAF_DEL_LAST_FORCE:
		वापस mlx5e_htb_leaf_del_last(priv, htb->classid,
					       htb->command == TC_HTB_LEAF_DEL_LAST_FORCE,
					       htb->extack);
	हाल TC_HTB_NODE_MODIFY:
		वापस mlx5e_htb_node_modअगरy(priv, htb->classid, htb->rate, htb->उच्चमान,
					     htb->extack);
	हाल TC_HTB_LEAF_QUERY_QUEUE:
		res = mlx5e_get_txq_by_classid(priv, htb->classid);
		अगर (res < 0)
			वापस res;
		htb->qid = res;
		वापस 0;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल LIST_HEAD(mlx5e_block_cb_list);

अटल पूर्णांक mlx5e_setup_tc(काष्ठा net_device *dev, क्रमागत tc_setup_type type,
			  व्योम *type_data)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(dev);
	bool tc_unbind = false;
	पूर्णांक err;

	अगर (type == TC_SETUP_BLOCK &&
	    ((काष्ठा flow_block_offload *)type_data)->command == FLOW_BLOCK_UNBIND)
		tc_unbind = true;

	अगर (!netअगर_device_present(dev) && !tc_unbind)
		वापस -ENODEV;

	चयन (type) अणु
	हाल TC_SETUP_BLOCK: अणु
		काष्ठा flow_block_offload *f = type_data;

		f->unlocked_driver_cb = true;
		वापस flow_block_cb_setup_simple(type_data,
						  &mlx5e_block_cb_list,
						  mlx5e_setup_tc_block_cb,
						  priv, priv, true);
	पूर्ण
	हाल TC_SETUP_QDISC_MQPRIO:
		वापस mlx5e_setup_tc_mqprio(priv, type_data);
	हाल TC_SETUP_QDISC_HTB:
		mutex_lock(&priv->state_lock);
		err = mlx5e_setup_tc_htb(priv, type_data);
		mutex_unlock(&priv->state_lock);
		वापस err;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

व्योम mlx5e_fold_sw_stats64(काष्ठा mlx5e_priv *priv, काष्ठा rtnl_link_stats64 *s)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < priv->max_nch; i++) अणु
		काष्ठा mlx5e_channel_stats *channel_stats = &priv->channel_stats[i];
		काष्ठा mlx5e_rq_stats *xskrq_stats = &channel_stats->xskrq;
		काष्ठा mlx5e_rq_stats *rq_stats = &channel_stats->rq;
		पूर्णांक j;

		s->rx_packets   += rq_stats->packets + xskrq_stats->packets;
		s->rx_bytes     += rq_stats->bytes + xskrq_stats->bytes;
		s->multicast    += rq_stats->mcast_packets + xskrq_stats->mcast_packets;

		क्रम (j = 0; j < priv->max_खोलोed_tc; j++) अणु
			काष्ठा mlx5e_sq_stats *sq_stats = &channel_stats->sq[j];

			s->tx_packets    += sq_stats->packets;
			s->tx_bytes      += sq_stats->bytes;
			s->tx_dropped    += sq_stats->dropped;
		पूर्ण
	पूर्ण
	अगर (priv->tx_ptp_खोलोed) अणु
		क्रम (i = 0; i < priv->max_खोलोed_tc; i++) अणु
			काष्ठा mlx5e_sq_stats *sq_stats = &priv->ptp_stats.sq[i];

			s->tx_packets    += sq_stats->packets;
			s->tx_bytes      += sq_stats->bytes;
			s->tx_dropped    += sq_stats->dropped;
		पूर्ण
	पूर्ण
	अगर (priv->rx_ptp_खोलोed) अणु
		काष्ठा mlx5e_rq_stats *rq_stats = &priv->ptp_stats.rq;

		s->rx_packets   += rq_stats->packets;
		s->rx_bytes     += rq_stats->bytes;
		s->multicast    += rq_stats->mcast_packets;
	पूर्ण
पूर्ण

व्योम
mlx5e_get_stats(काष्ठा net_device *dev, काष्ठा rtnl_link_stats64 *stats)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(dev);
	काष्ठा mlx5e_pport_stats *pstats = &priv->stats.pport;

	अगर (!netअगर_device_present(dev))
		वापस;

	/* In चयनdev mode, monitor counters करोesn't monitor
	 * rx/tx stats of 802_3. The update stats mechanism
	 * should keep the 802_3 layout counters updated
	 */
	अगर (!mlx5e_monitor_counter_supported(priv) ||
	    mlx5e_is_uplink_rep(priv)) अणु
		/* update HW stats in background क्रम next समय */
		mlx5e_queue_update_stats(priv);
	पूर्ण

	अगर (mlx5e_is_uplink_rep(priv)) अणु
		काष्ठा mlx5e_vport_stats *vstats = &priv->stats.vport;

		stats->rx_packets = PPORT_802_3_GET(pstats, a_frames_received_ok);
		stats->rx_bytes   = PPORT_802_3_GET(pstats, a_octets_received_ok);
		stats->tx_packets = PPORT_802_3_GET(pstats, a_frames_transmitted_ok);
		stats->tx_bytes   = PPORT_802_3_GET(pstats, a_octets_transmitted_ok);

		/* vport multicast also counts packets that are dropped due to steering
		 * or rx out of buffer
		 */
		stats->multicast = VPORT_COUNTER_GET(vstats, received_eth_multicast.packets);
	पूर्ण अन्यथा अणु
		mlx5e_fold_sw_stats64(priv, stats);
	पूर्ण

	stats->rx_dropped = priv->stats.qcnt.rx_out_of_buffer;

	stats->rx_length_errors =
		PPORT_802_3_GET(pstats, a_in_range_length_errors) +
		PPORT_802_3_GET(pstats, a_out_of_range_length_field) +
		PPORT_802_3_GET(pstats, a_frame_too_दीर्घ_errors);
	stats->rx_crc_errors =
		PPORT_802_3_GET(pstats, a_frame_check_sequence_errors);
	stats->rx_frame_errors = PPORT_802_3_GET(pstats, a_alignment_errors);
	stats->tx_पातed_errors = PPORT_2863_GET(pstats, अगर_out_discards);
	stats->rx_errors = stats->rx_length_errors + stats->rx_crc_errors +
			   stats->rx_frame_errors;
	stats->tx_errors = stats->tx_पातed_errors + stats->tx_carrier_errors;
पूर्ण

अटल व्योम mlx5e_nic_set_rx_mode(काष्ठा mlx5e_priv *priv)
अणु
	अगर (mlx5e_is_uplink_rep(priv))
		वापस; /* no rx mode क्रम uplink rep */

	queue_work(priv->wq, &priv->set_rx_mode_work);
पूर्ण

अटल व्योम mlx5e_set_rx_mode(काष्ठा net_device *dev)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(dev);

	mlx5e_nic_set_rx_mode(priv);
पूर्ण

अटल पूर्णांक mlx5e_set_mac(काष्ठा net_device *netdev, व्योम *addr)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(netdev);
	काष्ठा sockaddr *saddr = addr;

	अगर (!is_valid_ether_addr(saddr->sa_data))
		वापस -EADDRNOTAVAIL;

	netअगर_addr_lock_bh(netdev);
	ether_addr_copy(netdev->dev_addr, saddr->sa_data);
	netअगर_addr_unlock_bh(netdev);

	mlx5e_nic_set_rx_mode(priv);

	वापस 0;
पूर्ण

#घोषणा MLX5E_SET_FEATURE(features, feature, enable)	\
	करो अणु						\
		अगर (enable)				\
			*features |= feature;		\
		अन्यथा					\
			*features &= ~feature;		\
	पूर्ण जबतक (0)

प्रकार पूर्णांक (*mlx5e_feature_handler)(काष्ठा net_device *netdev, bool enable);

अटल पूर्णांक set_feature_lro(काष्ठा net_device *netdev, bool enable)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(netdev);
	काष्ठा mlx5_core_dev *mdev = priv->mdev;
	काष्ठा mlx5e_params *cur_params;
	काष्ठा mlx5e_params new_params;
	bool reset = true;
	पूर्णांक err = 0;

	mutex_lock(&priv->state_lock);

	अगर (enable && priv->xsk.refcnt) अणु
		netdev_warn(netdev, "LRO is incompatible with AF_XDP (%u XSKs are active)\n",
			    priv->xsk.refcnt);
		err = -EINVAL;
		जाओ out;
	पूर्ण

	cur_params = &priv->channels.params;
	अगर (enable && !MLX5E_GET_PFLAG(cur_params, MLX5E_PFLAG_RX_STRIDING_RQ)) अणु
		netdev_warn(netdev, "can't set LRO with legacy RQ\n");
		err = -EINVAL;
		जाओ out;
	पूर्ण

	new_params = *cur_params;
	new_params.lro_en = enable;

	अगर (cur_params->rq_wq_type == MLX5_WQ_TYPE_LINKED_LIST_STRIDING_RQ) अणु
		अगर (mlx5e_rx_mpwqe_is_linear_skb(mdev, cur_params, शून्य) ==
		    mlx5e_rx_mpwqe_is_linear_skb(mdev, &new_params, शून्य))
			reset = false;
	पूर्ण

	err = mlx5e_safe_चयन_params(priv, &new_params,
				       mlx5e_modअगरy_tirs_lro_ctx, शून्य, reset);
out:
	mutex_unlock(&priv->state_lock);
	वापस err;
पूर्ण

अटल पूर्णांक set_feature_cvlan_filter(काष्ठा net_device *netdev, bool enable)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(netdev);

	अगर (enable)
		mlx5e_enable_cvlan_filter(priv);
	अन्यथा
		mlx5e_disable_cvlan_filter(priv);

	वापस 0;
पूर्ण

अटल पूर्णांक set_feature_hw_tc(काष्ठा net_device *netdev, bool enable)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(netdev);

#अगर IS_ENABLED(CONFIG_MLX5_CLS_ACT)
	अगर (!enable && mlx5e_tc_num_filters(priv, MLX5_TC_FLAG(NIC_OFFLOAD))) अणु
		netdev_err(netdev,
			   "Active offloaded tc filters, can't turn hw_tc_offload off\n");
		वापस -EINVAL;
	पूर्ण
#पूर्ण_अगर

	अगर (!enable && priv->htb.maj_id) अणु
		netdev_err(netdev, "Active HTB offload, can't turn hw_tc_offload off\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक set_feature_rx_all(काष्ठा net_device *netdev, bool enable)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(netdev);
	काष्ठा mlx5_core_dev *mdev = priv->mdev;

	वापस mlx5_set_port_fcs(mdev, !enable);
पूर्ण

अटल पूर्णांक set_feature_rx_fcs(काष्ठा net_device *netdev, bool enable)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(netdev);
	पूर्णांक err;

	mutex_lock(&priv->state_lock);

	priv->channels.params.scatter_fcs_en = enable;
	err = mlx5e_modअगरy_channels_scatter_fcs(&priv->channels, enable);
	अगर (err)
		priv->channels.params.scatter_fcs_en = !enable;

	mutex_unlock(&priv->state_lock);

	वापस err;
पूर्ण

अटल पूर्णांक set_feature_rx_vlan(काष्ठा net_device *netdev, bool enable)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(netdev);
	पूर्णांक err = 0;

	mutex_lock(&priv->state_lock);

	priv->channels.params.vlan_strip_disable = !enable;
	अगर (!test_bit(MLX5E_STATE_OPENED, &priv->state))
		जाओ unlock;

	err = mlx5e_modअगरy_channels_vsd(&priv->channels, !enable);
	अगर (err)
		priv->channels.params.vlan_strip_disable = enable;

unlock:
	mutex_unlock(&priv->state_lock);

	वापस err;
पूर्ण

#अगर_घोषित CONFIG_MLX5_EN_ARFS
अटल पूर्णांक set_feature_arfs(काष्ठा net_device *netdev, bool enable)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(netdev);
	पूर्णांक err;

	अगर (enable)
		err = mlx5e_arfs_enable(priv);
	अन्यथा
		err = mlx5e_arfs_disable(priv);

	वापस err;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक mlx5e_handle_feature(काष्ठा net_device *netdev,
				netdev_features_t *features,
				netdev_features_t wanted_features,
				netdev_features_t feature,
				mlx5e_feature_handler feature_handler)
अणु
	netdev_features_t changes = wanted_features ^ netdev->features;
	bool enable = !!(wanted_features & feature);
	पूर्णांक err;

	अगर (!(changes & feature))
		वापस 0;

	err = feature_handler(netdev, enable);
	अगर (err) अणु
		netdev_err(netdev, "%s feature %pNF failed, err %d\n",
			   enable ? "Enable" : "Disable", &feature, err);
		वापस err;
	पूर्ण

	MLX5E_SET_FEATURE(features, feature, enable);
	वापस 0;
पूर्ण

पूर्णांक mlx5e_set_features(काष्ठा net_device *netdev, netdev_features_t features)
अणु
	netdev_features_t oper_features = netdev->features;
	पूर्णांक err = 0;

#घोषणा MLX5E_HANDLE_FEATURE(feature, handler) \
	mlx5e_handle_feature(netdev, &oper_features, features, feature, handler)

	err |= MLX5E_HANDLE_FEATURE(NETIF_F_LRO, set_feature_lro);
	err |= MLX5E_HANDLE_FEATURE(NETIF_F_HW_VLAN_CTAG_FILTER,
				    set_feature_cvlan_filter);
	err |= MLX5E_HANDLE_FEATURE(NETIF_F_HW_TC, set_feature_hw_tc);
	err |= MLX5E_HANDLE_FEATURE(NETIF_F_RXALL, set_feature_rx_all);
	err |= MLX5E_HANDLE_FEATURE(NETIF_F_RXFCS, set_feature_rx_fcs);
	err |= MLX5E_HANDLE_FEATURE(NETIF_F_HW_VLAN_CTAG_RX, set_feature_rx_vlan);
#अगर_घोषित CONFIG_MLX5_EN_ARFS
	err |= MLX5E_HANDLE_FEATURE(NETIF_F_NTUPLE, set_feature_arfs);
#पूर्ण_अगर
	err |= MLX5E_HANDLE_FEATURE(NETIF_F_HW_TLS_RX, mlx5e_ktls_set_feature_rx);

	अगर (err) अणु
		netdev->features = oper_features;
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल netdev_features_t mlx5e_fix_features(काष्ठा net_device *netdev,
					    netdev_features_t features)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(netdev);
	काष्ठा mlx5e_params *params;

	mutex_lock(&priv->state_lock);
	params = &priv->channels.params;
	अगर (!priv->fs.vlan ||
	    !biपंचांगap_empty(mlx5e_vlan_get_active_svlans(priv->fs.vlan), VLAN_N_VID)) अणु
		/* HW strips the outer C-tag header, this is a problem
		 * क्रम S-tag traffic.
		 */
		features &= ~NETIF_F_HW_VLAN_CTAG_RX;
		अगर (!params->vlan_strip_disable)
			netdev_warn(netdev, "Dropping C-tag vlan stripping offload due to S-tag vlan\n");
	पूर्ण

	अगर (!MLX5E_GET_PFLAG(params, MLX5E_PFLAG_RX_STRIDING_RQ)) अणु
		अगर (features & NETIF_F_LRO) अणु
			netdev_warn(netdev, "Disabling LRO, not supported in legacy RQ\n");
			features &= ~NETIF_F_LRO;
		पूर्ण
	पूर्ण

	अगर (MLX5E_GET_PFLAG(params, MLX5E_PFLAG_RX_CQE_COMPRESS)) अणु
		features &= ~NETIF_F_RXHASH;
		अगर (netdev->features & NETIF_F_RXHASH)
			netdev_warn(netdev, "Disabling rxhash, not supported when CQE compress is active\n");
	पूर्ण

	अगर (mlx5e_is_uplink_rep(priv)) अणु
		features &= ~NETIF_F_HW_TLS_RX;
		अगर (netdev->features & NETIF_F_HW_TLS_RX)
			netdev_warn(netdev, "Disabling hw_tls_rx, not supported in switchdev mode\n");

		features &= ~NETIF_F_HW_TLS_TX;
		अगर (netdev->features & NETIF_F_HW_TLS_TX)
			netdev_warn(netdev, "Disabling hw_tls_tx, not supported in switchdev mode\n");
	पूर्ण

	mutex_unlock(&priv->state_lock);

	वापस features;
पूर्ण

अटल bool mlx5e_xsk_validate_mtu(काष्ठा net_device *netdev,
				   काष्ठा mlx5e_channels *chs,
				   काष्ठा mlx5e_params *new_params,
				   काष्ठा mlx5_core_dev *mdev)
अणु
	u16 ix;

	क्रम (ix = 0; ix < chs->params.num_channels; ix++) अणु
		काष्ठा xsk_buff_pool *xsk_pool =
			mlx5e_xsk_get_pool(&chs->params, chs->params.xsk, ix);
		काष्ठा mlx5e_xsk_param xsk;

		अगर (!xsk_pool)
			जारी;

		mlx5e_build_xsk_param(xsk_pool, &xsk);

		अगर (!mlx5e_validate_xsk_param(new_params, &xsk, mdev)) अणु
			u32 hr = mlx5e_get_linear_rq_headroom(new_params, &xsk);
			पूर्णांक max_mtu_frame, max_mtu_page, max_mtu;

			/* Two criteria must be met:
			 * 1. HW MTU + all headrooms <= XSK frame size.
			 * 2. Size of SKBs allocated on XDP_PASS <= PAGE_SIZE.
			 */
			max_mtu_frame = MLX5E_HW2SW_MTU(new_params, xsk.chunk_size - hr);
			max_mtu_page = mlx5e_xdp_max_mtu(new_params, &xsk);
			max_mtu = min(max_mtu_frame, max_mtu_page);

			netdev_err(netdev, "MTU %d is too big for an XSK running on channel %u. Try MTU <= %d\n",
				   new_params->sw_mtu, ix, max_mtu);
			वापस false;
		पूर्ण
	पूर्ण

	वापस true;
पूर्ण

पूर्णांक mlx5e_change_mtu(काष्ठा net_device *netdev, पूर्णांक new_mtu,
		     mlx5e_fp_preactivate preactivate)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(netdev);
	काष्ठा mlx5e_params new_params;
	काष्ठा mlx5e_params *params;
	bool reset = true;
	पूर्णांक err = 0;

	mutex_lock(&priv->state_lock);

	params = &priv->channels.params;

	new_params = *params;
	new_params.sw_mtu = new_mtu;
	err = mlx5e_validate_params(priv->mdev, &new_params);
	अगर (err)
		जाओ out;

	अगर (params->xdp_prog &&
	    !mlx5e_rx_is_linear_skb(&new_params, शून्य)) अणु
		netdev_err(netdev, "MTU(%d) > %d is not allowed while XDP enabled\n",
			   new_mtu, mlx5e_xdp_max_mtu(params, शून्य));
		err = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (priv->xsk.refcnt &&
	    !mlx5e_xsk_validate_mtu(netdev, &priv->channels,
				    &new_params, priv->mdev)) अणु
		err = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (params->lro_en)
		reset = false;

	अगर (params->rq_wq_type == MLX5_WQ_TYPE_LINKED_LIST_STRIDING_RQ) अणु
		bool is_linear_old = mlx5e_rx_mpwqe_is_linear_skb(priv->mdev, params, शून्य);
		bool is_linear_new = mlx5e_rx_mpwqe_is_linear_skb(priv->mdev,
								  &new_params, शून्य);
		u8 ppw_old = mlx5e_mpwqe_log_pkts_per_wqe(params, शून्य);
		u8 ppw_new = mlx5e_mpwqe_log_pkts_per_wqe(&new_params, शून्य);

		/* Always reset in linear mode - hw_mtu is used in data path.
		 * Check that the mode was non-linear and didn't change.
		 * If XSK is active, XSK RQs are linear.
		 */
		अगर (!is_linear_old && !is_linear_new && !priv->xsk.refcnt &&
		    ppw_old == ppw_new)
			reset = false;
	पूर्ण

	err = mlx5e_safe_चयन_params(priv, &new_params, preactivate, शून्य, reset);

out:
	netdev->mtu = params->sw_mtu;
	mutex_unlock(&priv->state_lock);
	वापस err;
पूर्ण

अटल पूर्णांक mlx5e_change_nic_mtu(काष्ठा net_device *netdev, पूर्णांक new_mtu)
अणु
	वापस mlx5e_change_mtu(netdev, new_mtu, mlx5e_set_dev_port_mtu_ctx);
पूर्ण

पूर्णांक mlx5e_ptp_rx_manage_fs_ctx(काष्ठा mlx5e_priv *priv, व्योम *ctx)
अणु
	bool set  = *(bool *)ctx;

	वापस mlx5e_ptp_rx_manage_fs(priv, set);
पूर्ण

अटल पूर्णांक mlx5e_hwstamp_config_no_ptp_rx(काष्ठा mlx5e_priv *priv, bool rx_filter)
अणु
	bool rx_cqe_compress_def = priv->channels.params.rx_cqe_compress_def;
	पूर्णांक err;

	अगर (!rx_filter)
		/* Reset CQE compression to Admin शेष */
		वापस mlx5e_modअगरy_rx_cqe_compression_locked(priv, rx_cqe_compress_def);

	अगर (!MLX5E_GET_PFLAG(&priv->channels.params, MLX5E_PFLAG_RX_CQE_COMPRESS))
		वापस 0;

	/* Disable CQE compression */
	netdev_warn(priv->netdev, "Disabling RX cqe compression\n");
	err = mlx5e_modअगरy_rx_cqe_compression_locked(priv, false);
	अगर (err)
		netdev_err(priv->netdev, "Failed disabling cqe compression err=%d\n", err);

	वापस err;
पूर्ण

अटल पूर्णांक mlx5e_hwstamp_config_ptp_rx(काष्ठा mlx5e_priv *priv, bool ptp_rx)
अणु
	काष्ठा mlx5e_params new_params;

	अगर (ptp_rx == priv->channels.params.ptp_rx)
		वापस 0;

	new_params = priv->channels.params;
	new_params.ptp_rx = ptp_rx;
	वापस mlx5e_safe_चयन_params(priv, &new_params, mlx5e_ptp_rx_manage_fs_ctx,
					&new_params.ptp_rx, true);
पूर्ण

पूर्णांक mlx5e_hwstamp_set(काष्ठा mlx5e_priv *priv, काष्ठा अगरreq *अगरr)
अणु
	काष्ठा hwtstamp_config config;
	bool rx_cqe_compress_def;
	bool ptp_rx;
	पूर्णांक err;

	अगर (!MLX5_CAP_GEN(priv->mdev, device_frequency_khz) ||
	    (mlx5_घड़ी_get_ptp_index(priv->mdev) == -1))
		वापस -EOPNOTSUPP;

	अगर (copy_from_user(&config, अगरr->अगरr_data, माप(config)))
		वापस -EFAULT;

	/* TX HW बारtamp */
	चयन (config.tx_type) अणु
	हाल HWTSTAMP_TX_OFF:
	हाल HWTSTAMP_TX_ON:
		अवरोध;
	शेष:
		वापस -दुस्फल;
	पूर्ण

	mutex_lock(&priv->state_lock);
	rx_cqe_compress_def = priv->channels.params.rx_cqe_compress_def;

	/* RX HW बारtamp */
	चयन (config.rx_filter) अणु
	हाल HWTSTAMP_FILTER_NONE:
		ptp_rx = false;
		अवरोध;
	हाल HWTSTAMP_FILTER_ALL:
	हाल HWTSTAMP_FILTER_SOME:
	हाल HWTSTAMP_FILTER_PTP_V1_L4_EVENT:
	हाल HWTSTAMP_FILTER_PTP_V1_L4_SYNC:
	हाल HWTSTAMP_FILTER_PTP_V1_L4_DELAY_REQ:
	हाल HWTSTAMP_FILTER_PTP_V2_L4_EVENT:
	हाल HWTSTAMP_FILTER_PTP_V2_L4_SYNC:
	हाल HWTSTAMP_FILTER_PTP_V2_L4_DELAY_REQ:
	हाल HWTSTAMP_FILTER_PTP_V2_L2_EVENT:
	हाल HWTSTAMP_FILTER_PTP_V2_L2_SYNC:
	हाल HWTSTAMP_FILTER_PTP_V2_L2_DELAY_REQ:
	हाल HWTSTAMP_FILTER_PTP_V2_EVENT:
	हाल HWTSTAMP_FILTER_PTP_V2_SYNC:
	हाल HWTSTAMP_FILTER_PTP_V2_DELAY_REQ:
	हाल HWTSTAMP_FILTER_NTP_ALL:
		config.rx_filter = HWTSTAMP_FILTER_ALL;
		/* ptp_rx is set अगर both HW TS is set and CQE
		 * compression is set
		 */
		ptp_rx = rx_cqe_compress_def;
		अवरोध;
	शेष:
		err = -दुस्फल;
		जाओ err_unlock;
	पूर्ण

	अगर (!priv->profile->rx_ptp_support)
		err = mlx5e_hwstamp_config_no_ptp_rx(priv,
						     config.rx_filter != HWTSTAMP_FILTER_NONE);
	अन्यथा
		err = mlx5e_hwstamp_config_ptp_rx(priv, ptp_rx);
	अगर (err)
		जाओ err_unlock;

	स_नकल(&priv->tstamp, &config, माप(config));
	mutex_unlock(&priv->state_lock);

	/* might need to fix some features */
	netdev_update_features(priv->netdev);

	वापस copy_to_user(अगरr->अगरr_data, &config,
			    माप(config)) ? -EFAULT : 0;
err_unlock:
	mutex_unlock(&priv->state_lock);
	वापस err;
पूर्ण

पूर्णांक mlx5e_hwstamp_get(काष्ठा mlx5e_priv *priv, काष्ठा अगरreq *अगरr)
अणु
	काष्ठा hwtstamp_config *cfg = &priv->tstamp;

	अगर (!MLX5_CAP_GEN(priv->mdev, device_frequency_khz))
		वापस -EOPNOTSUPP;

	वापस copy_to_user(अगरr->अगरr_data, cfg, माप(*cfg)) ? -EFAULT : 0;
पूर्ण

अटल पूर्णांक mlx5e_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *अगरr, पूर्णांक cmd)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(dev);

	चयन (cmd) अणु
	हाल SIOCSHWTSTAMP:
		वापस mlx5e_hwstamp_set(priv, अगरr);
	हाल SIOCGHWTSTAMP:
		वापस mlx5e_hwstamp_get(priv, अगरr);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_MLX5_ESWITCH
पूर्णांक mlx5e_set_vf_mac(काष्ठा net_device *dev, पूर्णांक vf, u8 *mac)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(dev);
	काष्ठा mlx5_core_dev *mdev = priv->mdev;

	वापस mlx5_eचयन_set_vport_mac(mdev->priv.eचयन, vf + 1, mac);
पूर्ण

अटल पूर्णांक mlx5e_set_vf_vlan(काष्ठा net_device *dev, पूर्णांक vf, u16 vlan, u8 qos,
			     __be16 vlan_proto)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(dev);
	काष्ठा mlx5_core_dev *mdev = priv->mdev;

	अगर (vlan_proto != htons(ETH_P_8021Q))
		वापस -EPROTONOSUPPORT;

	वापस mlx5_eचयन_set_vport_vlan(mdev->priv.eचयन, vf + 1,
					   vlan, qos);
पूर्ण

अटल पूर्णांक mlx5e_set_vf_spoofchk(काष्ठा net_device *dev, पूर्णांक vf, bool setting)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(dev);
	काष्ठा mlx5_core_dev *mdev = priv->mdev;

	वापस mlx5_eचयन_set_vport_spoofchk(mdev->priv.eचयन, vf + 1, setting);
पूर्ण

अटल पूर्णांक mlx5e_set_vf_trust(काष्ठा net_device *dev, पूर्णांक vf, bool setting)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(dev);
	काष्ठा mlx5_core_dev *mdev = priv->mdev;

	वापस mlx5_eचयन_set_vport_trust(mdev->priv.eचयन, vf + 1, setting);
पूर्ण

पूर्णांक mlx5e_set_vf_rate(काष्ठा net_device *dev, पूर्णांक vf, पूर्णांक min_tx_rate,
		      पूर्णांक max_tx_rate)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(dev);
	काष्ठा mlx5_core_dev *mdev = priv->mdev;

	वापस mlx5_eचयन_set_vport_rate(mdev->priv.eचयन, vf + 1,
					   max_tx_rate, min_tx_rate);
पूर्ण

अटल पूर्णांक mlx5_vport_link2अगरla(u8 esw_link)
अणु
	चयन (esw_link) अणु
	हाल MLX5_VPORT_ADMIN_STATE_DOWN:
		वापस IFLA_VF_LINK_STATE_DISABLE;
	हाल MLX5_VPORT_ADMIN_STATE_UP:
		वापस IFLA_VF_LINK_STATE_ENABLE;
	पूर्ण
	वापस IFLA_VF_LINK_STATE_AUTO;
पूर्ण

अटल पूर्णांक mlx5_अगरla_link2vport(u8 अगरla_link)
अणु
	चयन (अगरla_link) अणु
	हाल IFLA_VF_LINK_STATE_DISABLE:
		वापस MLX5_VPORT_ADMIN_STATE_DOWN;
	हाल IFLA_VF_LINK_STATE_ENABLE:
		वापस MLX5_VPORT_ADMIN_STATE_UP;
	पूर्ण
	वापस MLX5_VPORT_ADMIN_STATE_AUTO;
पूर्ण

अटल पूर्णांक mlx5e_set_vf_link_state(काष्ठा net_device *dev, पूर्णांक vf,
				   पूर्णांक link_state)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(dev);
	काष्ठा mlx5_core_dev *mdev = priv->mdev;

	अगर (mlx5e_is_uplink_rep(priv))
		वापस -EOPNOTSUPP;

	वापस mlx5_eचयन_set_vport_state(mdev->priv.eचयन, vf + 1,
					    mlx5_अगरla_link2vport(link_state));
पूर्ण

पूर्णांक mlx5e_get_vf_config(काष्ठा net_device *dev,
			पूर्णांक vf, काष्ठा अगरla_vf_info *ivi)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(dev);
	काष्ठा mlx5_core_dev *mdev = priv->mdev;
	पूर्णांक err;

	अगर (!netअगर_device_present(dev))
		वापस -EOPNOTSUPP;

	err = mlx5_eचयन_get_vport_config(mdev->priv.eचयन, vf + 1, ivi);
	अगर (err)
		वापस err;
	ivi->linkstate = mlx5_vport_link2अगरla(ivi->linkstate);
	वापस 0;
पूर्ण

पूर्णांक mlx5e_get_vf_stats(काष्ठा net_device *dev,
		       पूर्णांक vf, काष्ठा अगरla_vf_stats *vf_stats)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(dev);
	काष्ठा mlx5_core_dev *mdev = priv->mdev;

	वापस mlx5_eचयन_get_vport_stats(mdev->priv.eचयन, vf + 1,
					    vf_stats);
पूर्ण

अटल bool
mlx5e_has_offload_stats(स्थिर काष्ठा net_device *dev, पूर्णांक attr_id)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(dev);

	अगर (!netअगर_device_present(dev))
		वापस false;

	अगर (!mlx5e_is_uplink_rep(priv))
		वापस false;

	वापस mlx5e_rep_has_offload_stats(dev, attr_id);
पूर्ण

अटल पूर्णांक
mlx5e_get_offload_stats(पूर्णांक attr_id, स्थिर काष्ठा net_device *dev,
			व्योम *sp)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(dev);

	अगर (!mlx5e_is_uplink_rep(priv))
		वापस -EOPNOTSUPP;

	वापस mlx5e_rep_get_offload_stats(attr_id, dev, sp);
पूर्ण
#पूर्ण_अगर

अटल bool mlx5e_tunnel_proto_supported_tx(काष्ठा mlx5_core_dev *mdev, u8 proto_type)
अणु
	चयन (proto_type) अणु
	हाल IPPROTO_GRE:
		वापस MLX5_CAP_ETH(mdev, tunnel_stateless_gre);
	हाल IPPROTO_IPIP:
	हाल IPPROTO_IPV6:
		वापस (MLX5_CAP_ETH(mdev, tunnel_stateless_ip_over_ip) ||
			MLX5_CAP_ETH(mdev, tunnel_stateless_ip_over_ip_tx));
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool mlx5e_gre_tunnel_inner_proto_offload_supported(काष्ठा mlx5_core_dev *mdev,
							   काष्ठा sk_buff *skb)
अणु
	चयन (skb->inner_protocol) अणु
	हाल htons(ETH_P_IP):
	हाल htons(ETH_P_IPV6):
	हाल htons(ETH_P_TEB):
		वापस true;
	हाल htons(ETH_P_MPLS_UC):
	हाल htons(ETH_P_MPLS_MC):
		वापस MLX5_CAP_ETH(mdev, tunnel_stateless_mpls_over_gre);
	पूर्ण
	वापस false;
पूर्ण

अटल netdev_features_t mlx5e_tunnel_features_check(काष्ठा mlx5e_priv *priv,
						     काष्ठा sk_buff *skb,
						     netdev_features_t features)
अणु
	अचिन्हित पूर्णांक offset = 0;
	काष्ठा udphdr *udph;
	u8 proto;
	u16 port;

	चयन (vlan_get_protocol(skb)) अणु
	हाल htons(ETH_P_IP):
		proto = ip_hdr(skb)->protocol;
		अवरोध;
	हाल htons(ETH_P_IPV6):
		proto = ipv6_find_hdr(skb, &offset, -1, शून्य, शून्य);
		अवरोध;
	शेष:
		जाओ out;
	पूर्ण

	चयन (proto) अणु
	हाल IPPROTO_GRE:
		अगर (mlx5e_gre_tunnel_inner_proto_offload_supported(priv->mdev, skb))
			वापस features;
		अवरोध;
	हाल IPPROTO_IPIP:
	हाल IPPROTO_IPV6:
		अगर (mlx5e_tunnel_proto_supported_tx(priv->mdev, IPPROTO_IPIP))
			वापस features;
		अवरोध;
	हाल IPPROTO_UDP:
		udph = udp_hdr(skb);
		port = be16_to_cpu(udph->dest);

		/* Verअगरy अगर UDP port is being offloaded by HW */
		अगर (mlx5_vxlan_lookup_port(priv->mdev->vxlan, port))
			वापस features;

#अगर IS_ENABLED(CONFIG_GENEVE)
		/* Support Geneve offload क्रम शेष UDP port */
		अगर (port == GENEVE_UDP_PORT && mlx5_geneve_tx_allowed(priv->mdev))
			वापस features;
#पूर्ण_अगर
	पूर्ण

out:
	/* Disable CSUM and GSO अगर the udp dport is not offloaded by HW */
	वापस features & ~(NETIF_F_CSUM_MASK | NETIF_F_GSO_MASK);
पूर्ण

netdev_features_t mlx5e_features_check(काष्ठा sk_buff *skb,
				       काष्ठा net_device *netdev,
				       netdev_features_t features)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(netdev);

	features = vlan_features_check(skb, features);
	features = vxlan_features_check(skb, features);

	अगर (mlx5e_ipsec_feature_check(skb, netdev, features))
		वापस features;

	/* Validate अगर the tunneled packet is being offloaded by HW */
	अगर (skb->encapsulation &&
	    (features & NETIF_F_CSUM_MASK || features & NETIF_F_GSO_MASK))
		वापस mlx5e_tunnel_features_check(priv, skb, features);

	वापस features;
पूर्ण

अटल व्योम mlx5e_tx_समयout_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mlx5e_priv *priv = container_of(work, काष्ठा mlx5e_priv,
					       tx_समयout_work);
	काष्ठा net_device *netdev = priv->netdev;
	पूर्णांक i;

	rtnl_lock();
	mutex_lock(&priv->state_lock);

	अगर (!test_bit(MLX5E_STATE_OPENED, &priv->state))
		जाओ unlock;

	क्रम (i = 0; i < netdev->real_num_tx_queues; i++) अणु
		काष्ठा netdev_queue *dev_queue =
			netdev_get_tx_queue(netdev, i);
		काष्ठा mlx5e_txqsq *sq = priv->txq2sq[i];

		अगर (!netअगर_xmit_stopped(dev_queue))
			जारी;

		अगर (mlx5e_reporter_tx_समयout(sq))
		/* अवरोध अगर tried to reखोलोed channels */
			अवरोध;
	पूर्ण

unlock:
	mutex_unlock(&priv->state_lock);
	rtnl_unlock();
पूर्ण

अटल व्योम mlx5e_tx_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(dev);

	netdev_err(dev, "TX timeout detected\n");
	queue_work(priv->wq, &priv->tx_समयout_work);
पूर्ण

अटल पूर्णांक mlx5e_xdp_allowed(काष्ठा mlx5e_priv *priv, काष्ठा bpf_prog *prog)
अणु
	काष्ठा net_device *netdev = priv->netdev;
	काष्ठा mlx5e_params new_params;

	अगर (priv->channels.params.lro_en) अणु
		netdev_warn(netdev, "can't set XDP while LRO is on, disable LRO first\n");
		वापस -EINVAL;
	पूर्ण

	अगर (mlx5_fpga_is_ipsec_device(priv->mdev)) अणु
		netdev_warn(netdev,
			    "XDP is not available on Innova cards with IPsec support\n");
		वापस -EINVAL;
	पूर्ण

	new_params = priv->channels.params;
	new_params.xdp_prog = prog;

	/* No XSK params: AF_XDP can't be enabled yet at the poपूर्णांक of setting
	 * the XDP program.
	 */
	अगर (!mlx5e_rx_is_linear_skb(&new_params, शून्य)) अणु
		netdev_warn(netdev, "XDP is not allowed with MTU(%d) > %d\n",
			    new_params.sw_mtu,
			    mlx5e_xdp_max_mtu(&new_params, शून्य));
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम mlx5e_rq_replace_xdp_prog(काष्ठा mlx5e_rq *rq, काष्ठा bpf_prog *prog)
अणु
	काष्ठा bpf_prog *old_prog;

	old_prog = rcu_replace_poपूर्णांकer(rq->xdp_prog, prog,
				       lockdep_is_held(&rq->priv->state_lock));
	अगर (old_prog)
		bpf_prog_put(old_prog);
पूर्ण

अटल पूर्णांक mlx5e_xdp_set(काष्ठा net_device *netdev, काष्ठा bpf_prog *prog)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(netdev);
	काष्ठा mlx5e_params new_params;
	काष्ठा bpf_prog *old_prog;
	पूर्णांक err = 0;
	bool reset;
	पूर्णांक i;

	mutex_lock(&priv->state_lock);

	अगर (prog) अणु
		err = mlx5e_xdp_allowed(priv, prog);
		अगर (err)
			जाओ unlock;
	पूर्ण

	/* no need क्रम full reset when exchanging programs */
	reset = (!priv->channels.params.xdp_prog || !prog);

	new_params = priv->channels.params;
	new_params.xdp_prog = prog;
	अगर (reset)
		mlx5e_set_rq_type(priv->mdev, &new_params);
	old_prog = priv->channels.params.xdp_prog;

	err = mlx5e_safe_चयन_params(priv, &new_params, शून्य, शून्य, reset);
	अगर (err)
		जाओ unlock;

	अगर (old_prog)
		bpf_prog_put(old_prog);

	अगर (!test_bit(MLX5E_STATE_OPENED, &priv->state) || reset)
		जाओ unlock;

	/* exchanging programs w/o reset, we update ref counts on behalf
	 * of the channels RQs here.
	 */
	bpf_prog_add(prog, priv->channels.num);
	क्रम (i = 0; i < priv->channels.num; i++) अणु
		काष्ठा mlx5e_channel *c = priv->channels.c[i];

		mlx5e_rq_replace_xdp_prog(&c->rq, prog);
		अगर (test_bit(MLX5E_CHANNEL_STATE_XSK, c->state)) अणु
			bpf_prog_inc(prog);
			mlx5e_rq_replace_xdp_prog(&c->xskrq, prog);
		पूर्ण
	पूर्ण

unlock:
	mutex_unlock(&priv->state_lock);
	वापस err;
पूर्ण

अटल पूर्णांक mlx5e_xdp(काष्ठा net_device *dev, काष्ठा netdev_bpf *xdp)
अणु
	चयन (xdp->command) अणु
	हाल XDP_SETUP_PROG:
		वापस mlx5e_xdp_set(dev, xdp->prog);
	हाल XDP_SETUP_XSK_POOL:
		वापस mlx5e_xsk_setup_pool(dev, xdp->xsk.pool,
					    xdp->xsk.queue_id);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_MLX5_ESWITCH
अटल पूर्णांक mlx5e_bridge_getlink(काष्ठा sk_buff *skb, u32 pid, u32 seq,
				काष्ठा net_device *dev, u32 filter_mask,
				पूर्णांक nlflags)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(dev);
	काष्ठा mlx5_core_dev *mdev = priv->mdev;
	u8 mode, setting;
	पूर्णांक err;

	err = mlx5_eचयन_get_vepa(mdev->priv.eचयन, &setting);
	अगर (err)
		वापस err;
	mode = setting ? BRIDGE_MODE_VEPA : BRIDGE_MODE_VEB;
	वापस nकरो_dflt_bridge_getlink(skb, pid, seq, dev,
				       mode,
				       0, 0, nlflags, filter_mask, शून्य);
पूर्ण

अटल पूर्णांक mlx5e_bridge_setlink(काष्ठा net_device *dev, काष्ठा nlmsghdr *nlh,
				u16 flags, काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(dev);
	काष्ठा mlx5_core_dev *mdev = priv->mdev;
	काष्ठा nlattr *attr, *br_spec;
	u16 mode = BRIDGE_MODE_UNDEF;
	u8 setting;
	पूर्णांक rem;

	br_spec = nlmsg_find_attr(nlh, माप(काष्ठा अगरinfomsg), IFLA_AF_SPEC);
	अगर (!br_spec)
		वापस -EINVAL;

	nla_क्रम_each_nested(attr, br_spec, rem) अणु
		अगर (nla_type(attr) != IFLA_BRIDGE_MODE)
			जारी;

		अगर (nla_len(attr) < माप(mode))
			वापस -EINVAL;

		mode = nla_get_u16(attr);
		अगर (mode > BRIDGE_MODE_VEPA)
			वापस -EINVAL;

		अवरोध;
	पूर्ण

	अगर (mode == BRIDGE_MODE_UNDEF)
		वापस -EINVAL;

	setting = (mode == BRIDGE_MODE_VEPA) ?  1 : 0;
	वापस mlx5_eचयन_set_vepa(mdev->priv.eचयन, setting);
पूर्ण
#पूर्ण_अगर

स्थिर काष्ठा net_device_ops mlx5e_netdev_ops = अणु
	.nकरो_खोलो                = mlx5e_खोलो,
	.nकरो_stop                = mlx5e_बंद,
	.nकरो_start_xmit          = mlx5e_xmit,
	.nकरो_setup_tc            = mlx5e_setup_tc,
	.nकरो_select_queue        = mlx5e_select_queue,
	.nकरो_get_stats64         = mlx5e_get_stats,
	.nकरो_set_rx_mode         = mlx5e_set_rx_mode,
	.nकरो_set_mac_address     = mlx5e_set_mac,
	.nकरो_vlan_rx_add_vid     = mlx5e_vlan_rx_add_vid,
	.nकरो_vlan_rx_समाप्त_vid    = mlx5e_vlan_rx_समाप्त_vid,
	.nकरो_set_features        = mlx5e_set_features,
	.nकरो_fix_features        = mlx5e_fix_features,
	.nकरो_change_mtu          = mlx5e_change_nic_mtu,
	.nकरो_करो_ioctl            = mlx5e_ioctl,
	.nकरो_set_tx_maxrate      = mlx5e_set_tx_maxrate,
	.nकरो_features_check      = mlx5e_features_check,
	.nकरो_tx_समयout          = mlx5e_tx_समयout,
	.nकरो_bpf		 = mlx5e_xdp,
	.nकरो_xdp_xmit            = mlx5e_xdp_xmit,
	.nकरो_xsk_wakeup          = mlx5e_xsk_wakeup,
#अगर_घोषित CONFIG_MLX5_EN_ARFS
	.nकरो_rx_flow_steer	 = mlx5e_rx_flow_steer,
#पूर्ण_अगर
#अगर_घोषित CONFIG_MLX5_ESWITCH
	.nकरो_bridge_setlink      = mlx5e_bridge_setlink,
	.nकरो_bridge_getlink      = mlx5e_bridge_getlink,

	/* SRIOV E-Switch NDOs */
	.nकरो_set_vf_mac          = mlx5e_set_vf_mac,
	.nकरो_set_vf_vlan         = mlx5e_set_vf_vlan,
	.nकरो_set_vf_spoofchk     = mlx5e_set_vf_spoofchk,
	.nकरो_set_vf_trust        = mlx5e_set_vf_trust,
	.nकरो_set_vf_rate         = mlx5e_set_vf_rate,
	.nकरो_get_vf_config       = mlx5e_get_vf_config,
	.nकरो_set_vf_link_state   = mlx5e_set_vf_link_state,
	.nकरो_get_vf_stats        = mlx5e_get_vf_stats,
	.nकरो_has_offload_stats   = mlx5e_has_offload_stats,
	.nकरो_get_offload_stats   = mlx5e_get_offload_stats,
#पूर्ण_अगर
	.nकरो_get_devlink_port    = mlx5e_get_devlink_port,
पूर्ण;

व्योम mlx5e_build_शेष_indir_rqt(u32 *indirection_rqt, पूर्णांक len,
				   पूर्णांक num_channels)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < len; i++)
		indirection_rqt[i] = i % num_channels;
पूर्ण

अटल u32 mlx5e_choose_lro_समयout(काष्ठा mlx5_core_dev *mdev, u32 wanted_समयout)
अणु
	पूर्णांक i;

	/* The supported periods are organized in ascending order */
	क्रम (i = 0; i < MLX5E_LRO_TIMEOUT_ARR_SIZE - 1; i++)
		अगर (MLX5_CAP_ETH(mdev, lro_समयr_supported_periods[i]) >= wanted_समयout)
			अवरोध;

	वापस MLX5_CAP_ETH(mdev, lro_समयr_supported_periods[i]);
पूर्ण

व्योम mlx5e_build_rss_params(काष्ठा mlx5e_rss_params *rss_params,
			    u16 num_channels)
अणु
	क्रमागत mlx5e_traffic_types tt;

	rss_params->hfunc = ETH_RSS_HASH_TOP;
	netdev_rss_key_fill(rss_params->toeplitz_hash_key,
			    माप(rss_params->toeplitz_hash_key));
	mlx5e_build_शेष_indir_rqt(rss_params->indirection_rqt,
				      MLX5E_INसूची_RQT_SIZE, num_channels);
	क्रम (tt = 0; tt < MLX5E_NUM_INसूची_TIRS; tt++)
		rss_params->rx_hash_fields[tt] =
			tirc_शेष_config[tt].rx_hash_fields;
पूर्ण

व्योम mlx5e_build_nic_params(काष्ठा mlx5e_priv *priv, काष्ठा mlx5e_xsk *xsk, u16 mtu)
अणु
	काष्ठा mlx5e_rss_params *rss_params = &priv->rss_params;
	काष्ठा mlx5e_params *params = &priv->channels.params;
	काष्ठा mlx5_core_dev *mdev = priv->mdev;
	u8 rx_cq_period_mode;

	priv->max_nch = mlx5e_calc_max_nch(priv, priv->profile);

	params->sw_mtu = mtu;
	params->hard_mtu = MLX5E_ETH_HARD_MTU;
	params->num_channels = min_t(अचिन्हित पूर्णांक, MLX5E_MAX_NUM_CHANNELS / 2,
				     priv->max_nch);
	params->num_tc       = 1;

	/* Set an initial non-zero value, so that mlx5e_select_queue won't
	 * भागide by zero अगर called beक्रमe first activating channels.
	 */
	priv->num_tc_x_num_ch = params->num_channels * params->num_tc;

	/* SQ */
	params->log_sq_size = is_kdump_kernel() ?
		MLX5E_PARAMS_MINIMUM_LOG_SQ_SIZE :
		MLX5E_PARAMS_DEFAULT_LOG_SQ_SIZE;
	MLX5E_SET_PFLAG(params, MLX5E_PFLAG_SKB_TX_MPWQE,
			MLX5_CAP_ETH(mdev, enhanced_multi_pkt_send_wqe));

	/* XDP SQ */
	MLX5E_SET_PFLAG(params, MLX5E_PFLAG_XDP_TX_MPWQE,
			MLX5_CAP_ETH(mdev, enhanced_multi_pkt_send_wqe));

	/* set CQE compression */
	params->rx_cqe_compress_def = false;
	अगर (MLX5_CAP_GEN(mdev, cqe_compression) &&
	    MLX5_CAP_GEN(mdev, vport_group_manager))
		params->rx_cqe_compress_def = slow_pci_heuristic(mdev);

	MLX5E_SET_PFLAG(params, MLX5E_PFLAG_RX_CQE_COMPRESS, params->rx_cqe_compress_def);
	MLX5E_SET_PFLAG(params, MLX5E_PFLAG_RX_NO_CSUM_COMPLETE, false);

	/* RQ */
	mlx5e_build_rq_params(mdev, params);

	/* HW LRO */
	अगर (MLX5_CAP_ETH(mdev, lro_cap) &&
	    params->rq_wq_type == MLX5_WQ_TYPE_LINKED_LIST_STRIDING_RQ) अणु
		/* No XSK params: checking the availability of striding RQ in general. */
		अगर (!mlx5e_rx_mpwqe_is_linear_skb(mdev, params, शून्य))
			params->lro_en = !slow_pci_heuristic(mdev);
	पूर्ण
	params->lro_समयout = mlx5e_choose_lro_समयout(mdev, MLX5E_DEFAULT_LRO_TIMEOUT);

	/* CQ moderation params */
	rx_cq_period_mode = MLX5_CAP_GEN(mdev, cq_period_start_from_cqe) ?
			MLX5_CQ_PERIOD_MODE_START_FROM_CQE :
			MLX5_CQ_PERIOD_MODE_START_FROM_EQE;
	params->rx_dim_enabled = MLX5_CAP_GEN(mdev, cq_moderation);
	params->tx_dim_enabled = MLX5_CAP_GEN(mdev, cq_moderation);
	mlx5e_set_rx_cq_mode_params(params, rx_cq_period_mode);
	mlx5e_set_tx_cq_mode_params(params, MLX5_CQ_PERIOD_MODE_START_FROM_EQE);

	/* TX अंतरभूत */
	mlx5_query_min_अंतरभूत(mdev, &params->tx_min_अंतरभूत_mode);

	/* RSS */
	mlx5e_build_rss_params(rss_params, params->num_channels);
	params->tunneled_offload_en =
		mlx5e_tunnel_inner_ft_supported(mdev);

	/* AF_XDP */
	params->xsk = xsk;

	/* Do not update netdev->features directly in here
	 * on mlx5e_attach_netdev() we will call mlx5e_update_features()
	 * To update netdev->features please modअगरy mlx5e_fix_features()
	 */
पूर्ण

अटल व्योम mlx5e_set_netdev_dev_addr(काष्ठा net_device *netdev)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(netdev);

	mlx5_query_mac_address(priv->mdev, netdev->dev_addr);
	अगर (is_zero_ether_addr(netdev->dev_addr) &&
	    !MLX5_CAP_GEN(priv->mdev, vport_group_manager)) अणु
		eth_hw_addr_अक्रमom(netdev);
		mlx5_core_info(priv->mdev, "Assigned random MAC address %pM\n", netdev->dev_addr);
	पूर्ण
पूर्ण

अटल पूर्णांक mlx5e_vxlan_set_port(काष्ठा net_device *netdev, अचिन्हित पूर्णांक table,
				अचिन्हित पूर्णांक entry, काष्ठा udp_tunnel_info *ti)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(netdev);

	वापस mlx5_vxlan_add_port(priv->mdev->vxlan, ntohs(ti->port));
पूर्ण

अटल पूर्णांक mlx5e_vxlan_unset_port(काष्ठा net_device *netdev, अचिन्हित पूर्णांक table,
				  अचिन्हित पूर्णांक entry, काष्ठा udp_tunnel_info *ti)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(netdev);

	वापस mlx5_vxlan_del_port(priv->mdev->vxlan, ntohs(ti->port));
पूर्ण

व्योम mlx5e_vxlan_set_netdev_info(काष्ठा mlx5e_priv *priv)
अणु
	अगर (!mlx5_vxlan_allowed(priv->mdev->vxlan))
		वापस;

	priv->nic_info.set_port = mlx5e_vxlan_set_port;
	priv->nic_info.unset_port = mlx5e_vxlan_unset_port;
	priv->nic_info.flags = UDP_TUNNEL_NIC_INFO_MAY_SLEEP |
				UDP_TUNNEL_NIC_INFO_STATIC_IANA_VXLAN;
	priv->nic_info.tables[0].tunnel_types = UDP_TUNNEL_TYPE_VXLAN;
	/* Don't count the space hard-coded to the IANA port */
	priv->nic_info.tables[0].n_entries =
		mlx5_vxlan_max_udp_ports(priv->mdev) - 1;

	priv->netdev->udp_tunnel_nic_info = &priv->nic_info;
पूर्ण

अटल bool mlx5e_tunnel_any_tx_proto_supported(काष्ठा mlx5_core_dev *mdev)
अणु
	पूर्णांक tt;

	क्रम (tt = 0; tt < MLX5E_NUM_TUNNEL_TT; tt++) अणु
		अगर (mlx5e_tunnel_proto_supported_tx(mdev, mlx5e_get_proto_by_tunnel_type(tt)))
			वापस true;
	पूर्ण
	वापस (mlx5_vxlan_allowed(mdev->vxlan) || mlx5_geneve_tx_allowed(mdev));
पूर्ण

अटल व्योम mlx5e_build_nic_netdev(काष्ठा net_device *netdev)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(netdev);
	काष्ठा mlx5_core_dev *mdev = priv->mdev;
	bool fcs_supported;
	bool fcs_enabled;

	SET_NETDEV_DEV(netdev, mdev->device);

	netdev->netdev_ops = &mlx5e_netdev_ops;

	mlx5e_dcbnl_build_netdev(netdev);

	netdev->watchकरोg_समयo    = 15 * HZ;

	netdev->ethtool_ops	  = &mlx5e_ethtool_ops;

	netdev->vlan_features    |= NETIF_F_SG;
	netdev->vlan_features    |= NETIF_F_HW_CSUM;
	netdev->vlan_features    |= NETIF_F_GRO;
	netdev->vlan_features    |= NETIF_F_TSO;
	netdev->vlan_features    |= NETIF_F_TSO6;
	netdev->vlan_features    |= NETIF_F_RXCSUM;
	netdev->vlan_features    |= NETIF_F_RXHASH;

	netdev->mpls_features    |= NETIF_F_SG;
	netdev->mpls_features    |= NETIF_F_HW_CSUM;
	netdev->mpls_features    |= NETIF_F_TSO;
	netdev->mpls_features    |= NETIF_F_TSO6;

	netdev->hw_enc_features  |= NETIF_F_HW_VLAN_CTAG_TX;
	netdev->hw_enc_features  |= NETIF_F_HW_VLAN_CTAG_RX;

	अगर (!!MLX5_CAP_ETH(mdev, lro_cap) &&
	    mlx5e_check_fragmented_striding_rq_cap(mdev))
		netdev->vlan_features    |= NETIF_F_LRO;

	netdev->hw_features       = netdev->vlan_features;
	netdev->hw_features      |= NETIF_F_HW_VLAN_CTAG_TX;
	netdev->hw_features      |= NETIF_F_HW_VLAN_CTAG_RX;
	netdev->hw_features      |= NETIF_F_HW_VLAN_CTAG_FILTER;
	netdev->hw_features      |= NETIF_F_HW_VLAN_STAG_TX;

	अगर (mlx5e_tunnel_any_tx_proto_supported(mdev)) अणु
		netdev->hw_enc_features |= NETIF_F_HW_CSUM;
		netdev->hw_enc_features |= NETIF_F_TSO;
		netdev->hw_enc_features |= NETIF_F_TSO6;
		netdev->hw_enc_features |= NETIF_F_GSO_PARTIAL;
	पूर्ण

	अगर (mlx5_vxlan_allowed(mdev->vxlan) || mlx5_geneve_tx_allowed(mdev)) अणु
		netdev->hw_features     |= NETIF_F_GSO_UDP_TUNNEL;
		netdev->hw_enc_features |= NETIF_F_GSO_UDP_TUNNEL;
		netdev->vlan_features |= NETIF_F_GSO_UDP_TUNNEL;
	पूर्ण

	अगर (mlx5e_tunnel_proto_supported_tx(mdev, IPPROTO_GRE)) अणु
		netdev->hw_features     |= NETIF_F_GSO_GRE;
		netdev->hw_enc_features |= NETIF_F_GSO_GRE;
		netdev->gso_partial_features |= NETIF_F_GSO_GRE;
	पूर्ण

	अगर (mlx5e_tunnel_proto_supported_tx(mdev, IPPROTO_IPIP)) अणु
		netdev->hw_features |= NETIF_F_GSO_IPXIP4 |
				       NETIF_F_GSO_IPXIP6;
		netdev->hw_enc_features |= NETIF_F_GSO_IPXIP4 |
					   NETIF_F_GSO_IPXIP6;
		netdev->gso_partial_features |= NETIF_F_GSO_IPXIP4 |
						NETIF_F_GSO_IPXIP6;
	पूर्ण

	netdev->hw_features	                 |= NETIF_F_GSO_PARTIAL;
	netdev->gso_partial_features             |= NETIF_F_GSO_UDP_L4;
	netdev->hw_features                      |= NETIF_F_GSO_UDP_L4;
	netdev->features                         |= NETIF_F_GSO_UDP_L4;

	mlx5_query_port_fcs(mdev, &fcs_supported, &fcs_enabled);

	अगर (fcs_supported)
		netdev->hw_features |= NETIF_F_RXALL;

	अगर (MLX5_CAP_ETH(mdev, scatter_fcs))
		netdev->hw_features |= NETIF_F_RXFCS;

	netdev->features          = netdev->hw_features;

	/* Defaults */
	अगर (fcs_enabled)
		netdev->features  &= ~NETIF_F_RXALL;
	netdev->features  &= ~NETIF_F_LRO;
	netdev->features  &= ~NETIF_F_RXFCS;

#घोषणा FT_CAP(f) MLX5_CAP_FLOWTABLE(mdev, flow_table_properties_nic_receive.f)
	अगर (FT_CAP(flow_modअगरy_en) &&
	    FT_CAP(modअगरy_root) &&
	    FT_CAP(identअगरied_miss_table_mode) &&
	    FT_CAP(flow_table_modअगरy)) अणु
#अगर IS_ENABLED(CONFIG_MLX5_CLS_ACT)
		netdev->hw_features      |= NETIF_F_HW_TC;
#पूर्ण_अगर
#अगर_घोषित CONFIG_MLX5_EN_ARFS
		netdev->hw_features	 |= NETIF_F_NTUPLE;
#पूर्ण_अगर
	पूर्ण
	अगर (mlx5_qos_is_supported(mdev))
		netdev->features |= NETIF_F_HW_TC;

	netdev->features         |= NETIF_F_HIGHDMA;
	netdev->features         |= NETIF_F_HW_VLAN_STAG_FILTER;

	netdev->priv_flags       |= IFF_UNICAST_FLT;

	mlx5e_set_netdev_dev_addr(netdev);
	mlx5e_ipsec_build_netdev(priv);
	mlx5e_tls_build_netdev(priv);
पूर्ण

व्योम mlx5e_create_q_counters(काष्ठा mlx5e_priv *priv)
अणु
	u32 out[MLX5_ST_SZ_DW(alloc_q_counter_out)] = अणुपूर्ण;
	u32 in[MLX5_ST_SZ_DW(alloc_q_counter_in)] = अणुपूर्ण;
	काष्ठा mlx5_core_dev *mdev = priv->mdev;
	पूर्णांक err;

	MLX5_SET(alloc_q_counter_in, in, opcode, MLX5_CMD_OP_ALLOC_Q_COUNTER);
	err = mlx5_cmd_exec_inout(mdev, alloc_q_counter, in, out);
	अगर (!err)
		priv->q_counter =
			MLX5_GET(alloc_q_counter_out, out, counter_set_id);

	err = mlx5_cmd_exec_inout(mdev, alloc_q_counter, in, out);
	अगर (!err)
		priv->drop_rq_q_counter =
			MLX5_GET(alloc_q_counter_out, out, counter_set_id);
पूर्ण

व्योम mlx5e_destroy_q_counters(काष्ठा mlx5e_priv *priv)
अणु
	u32 in[MLX5_ST_SZ_DW(dealloc_q_counter_in)] = अणुपूर्ण;

	MLX5_SET(dealloc_q_counter_in, in, opcode,
		 MLX5_CMD_OP_DEALLOC_Q_COUNTER);
	अगर (priv->q_counter) अणु
		MLX5_SET(dealloc_q_counter_in, in, counter_set_id,
			 priv->q_counter);
		mlx5_cmd_exec_in(priv->mdev, dealloc_q_counter, in);
	पूर्ण

	अगर (priv->drop_rq_q_counter) अणु
		MLX5_SET(dealloc_q_counter_in, in, counter_set_id,
			 priv->drop_rq_q_counter);
		mlx5_cmd_exec_in(priv->mdev, dealloc_q_counter, in);
	पूर्ण
पूर्ण

अटल पूर्णांक mlx5e_nic_init(काष्ठा mlx5_core_dev *mdev,
			  काष्ठा net_device *netdev)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(netdev);
	काष्ठा devlink_port *dl_port;
	पूर्णांक err;

	mlx5e_build_nic_params(priv, &priv->xsk, netdev->mtu);
	mlx5e_vxlan_set_netdev_info(priv);

	mlx5e_बारtamp_init(priv);

	err = mlx5e_ipsec_init(priv);
	अगर (err)
		mlx5_core_err(mdev, "IPSec initialization failed, %d\n", err);

	err = mlx5e_tls_init(priv);
	अगर (err)
		mlx5_core_err(mdev, "TLS initialization failed, %d\n", err);

	dl_port = mlx5e_devlink_get_dl_port(priv);
	अगर (dl_port->रेजिस्टरed)
		mlx5e_health_create_reporters(priv);

	वापस 0;
पूर्ण

अटल व्योम mlx5e_nic_cleanup(काष्ठा mlx5e_priv *priv)
अणु
	काष्ठा devlink_port *dl_port = mlx5e_devlink_get_dl_port(priv);

	अगर (dl_port->रेजिस्टरed)
		mlx5e_health_destroy_reporters(priv);
	mlx5e_tls_cleanup(priv);
	mlx5e_ipsec_cleanup(priv);
पूर्ण

अटल पूर्णांक mlx5e_init_nic_rx(काष्ठा mlx5e_priv *priv)
अणु
	काष्ठा mlx5_core_dev *mdev = priv->mdev;
	u16 max_nch = priv->max_nch;
	पूर्णांक err;

	mlx5e_create_q_counters(priv);

	err = mlx5e_खोलो_drop_rq(priv, &priv->drop_rq);
	अगर (err) अणु
		mlx5_core_err(mdev, "open drop rq failed, %d\n", err);
		जाओ err_destroy_q_counters;
	पूर्ण

	err = mlx5e_create_indirect_rqt(priv);
	अगर (err)
		जाओ err_बंद_drop_rq;

	err = mlx5e_create_direct_rqts(priv, priv->direct_tir, max_nch);
	अगर (err)
		जाओ err_destroy_indirect_rqts;

	err = mlx5e_create_indirect_tirs(priv, true);
	अगर (err)
		जाओ err_destroy_direct_rqts;

	err = mlx5e_create_direct_tirs(priv, priv->direct_tir, max_nch);
	अगर (err)
		जाओ err_destroy_indirect_tirs;

	err = mlx5e_create_direct_rqts(priv, priv->xsk_tir, max_nch);
	अगर (unlikely(err))
		जाओ err_destroy_direct_tirs;

	err = mlx5e_create_direct_tirs(priv, priv->xsk_tir, max_nch);
	अगर (unlikely(err))
		जाओ err_destroy_xsk_rqts;

	err = mlx5e_create_direct_rqts(priv, &priv->ptp_tir, 1);
	अगर (err)
		जाओ err_destroy_xsk_tirs;

	err = mlx5e_create_direct_tirs(priv, &priv->ptp_tir, 1);
	अगर (err)
		जाओ err_destroy_ptp_rqt;

	err = mlx5e_create_flow_steering(priv);
	अगर (err) अणु
		mlx5_core_warn(mdev, "create flow steering failed, %d\n", err);
		जाओ err_destroy_ptp_direct_tir;
	पूर्ण

	err = mlx5e_tc_nic_init(priv);
	अगर (err)
		जाओ err_destroy_flow_steering;

	err = mlx5e_accel_init_rx(priv);
	अगर (err)
		जाओ err_tc_nic_cleanup;

#अगर_घोषित CONFIG_MLX5_EN_ARFS
	priv->netdev->rx_cpu_rmap =  mlx5_eq_table_get_rmap(priv->mdev);
#पूर्ण_अगर

	वापस 0;

err_tc_nic_cleanup:
	mlx5e_tc_nic_cleanup(priv);
err_destroy_flow_steering:
	mlx5e_destroy_flow_steering(priv);
err_destroy_ptp_direct_tir:
	mlx5e_destroy_direct_tirs(priv, &priv->ptp_tir, 1);
err_destroy_ptp_rqt:
	mlx5e_destroy_direct_rqts(priv, &priv->ptp_tir, 1);
err_destroy_xsk_tirs:
	mlx5e_destroy_direct_tirs(priv, priv->xsk_tir, max_nch);
err_destroy_xsk_rqts:
	mlx5e_destroy_direct_rqts(priv, priv->xsk_tir, max_nch);
err_destroy_direct_tirs:
	mlx5e_destroy_direct_tirs(priv, priv->direct_tir, max_nch);
err_destroy_indirect_tirs:
	mlx5e_destroy_indirect_tirs(priv);
err_destroy_direct_rqts:
	mlx5e_destroy_direct_rqts(priv, priv->direct_tir, max_nch);
err_destroy_indirect_rqts:
	mlx5e_destroy_rqt(priv, &priv->indir_rqt);
err_बंद_drop_rq:
	mlx5e_बंद_drop_rq(&priv->drop_rq);
err_destroy_q_counters:
	mlx5e_destroy_q_counters(priv);
	वापस err;
पूर्ण

अटल व्योम mlx5e_cleanup_nic_rx(काष्ठा mlx5e_priv *priv)
अणु
	u16 max_nch = priv->max_nch;

	mlx5e_accel_cleanup_rx(priv);
	mlx5e_tc_nic_cleanup(priv);
	mlx5e_destroy_flow_steering(priv);
	mlx5e_destroy_direct_tirs(priv, &priv->ptp_tir, 1);
	mlx5e_destroy_direct_rqts(priv, &priv->ptp_tir, 1);
	mlx5e_destroy_direct_tirs(priv, priv->xsk_tir, max_nch);
	mlx5e_destroy_direct_rqts(priv, priv->xsk_tir, max_nch);
	mlx5e_destroy_direct_tirs(priv, priv->direct_tir, max_nch);
	mlx5e_destroy_indirect_tirs(priv);
	mlx5e_destroy_direct_rqts(priv, priv->direct_tir, max_nch);
	mlx5e_destroy_rqt(priv, &priv->indir_rqt);
	mlx5e_बंद_drop_rq(&priv->drop_rq);
	mlx5e_destroy_q_counters(priv);
पूर्ण

अटल पूर्णांक mlx5e_init_nic_tx(काष्ठा mlx5e_priv *priv)
अणु
	पूर्णांक err;

	err = mlx5e_create_tises(priv);
	अगर (err) अणु
		mlx5_core_warn(priv->mdev, "create tises failed, %d\n", err);
		वापस err;
	पूर्ण

	mlx5e_dcbnl_initialize(priv);
	वापस 0;
पूर्ण

अटल व्योम mlx5e_nic_enable(काष्ठा mlx5e_priv *priv)
अणु
	काष्ठा net_device *netdev = priv->netdev;
	काष्ठा mlx5_core_dev *mdev = priv->mdev;

	mlx5e_init_l2_addr(priv);

	/* Marking the link as currently not needed by the Driver */
	अगर (!netअगर_running(netdev))
		mlx5e_modअगरy_admin_state(mdev, MLX5_PORT_DOWN);

	mlx5e_set_netdev_mtu_boundaries(priv);
	mlx5e_set_dev_port_mtu(priv);

	mlx5_lag_add(mdev, netdev);

	mlx5e_enable_async_events(priv);
	mlx5e_enable_blocking_events(priv);
	अगर (mlx5e_monitor_counter_supported(priv))
		mlx5e_monitor_counter_init(priv);

	mlx5e_hv_vhca_stats_create(priv);
	अगर (netdev->reg_state != NETREG_REGISTERED)
		वापस;
	mlx5e_dcbnl_init_app(priv);

	mlx5e_nic_set_rx_mode(priv);

	rtnl_lock();
	अगर (netअगर_running(netdev))
		mlx5e_खोलो(netdev);
	udp_tunnel_nic_reset_ntf(priv->netdev);
	netअगर_device_attach(netdev);
	rtnl_unlock();
पूर्ण

अटल व्योम mlx5e_nic_disable(काष्ठा mlx5e_priv *priv)
अणु
	काष्ठा mlx5_core_dev *mdev = priv->mdev;

	अगर (priv->netdev->reg_state == NETREG_REGISTERED)
		mlx5e_dcbnl_delete_app(priv);

	rtnl_lock();
	अगर (netअगर_running(priv->netdev))
		mlx5e_बंद(priv->netdev);
	netअगर_device_detach(priv->netdev);
	rtnl_unlock();

	mlx5e_nic_set_rx_mode(priv);

	mlx5e_hv_vhca_stats_destroy(priv);
	अगर (mlx5e_monitor_counter_supported(priv))
		mlx5e_monitor_counter_cleanup(priv);

	mlx5e_disable_blocking_events(priv);
	अगर (priv->en_trap) अणु
		mlx5e_deactivate_trap(priv);
		mlx5e_बंद_trap(priv->en_trap);
		priv->en_trap = शून्य;
	पूर्ण
	mlx5e_disable_async_events(priv);
	mlx5_lag_हटाओ(mdev);
	mlx5_vxlan_reset_to_शेष(mdev->vxlan);
पूर्ण

पूर्णांक mlx5e_update_nic_rx(काष्ठा mlx5e_priv *priv)
अणु
	वापस mlx5e_refresh_tirs(priv, false, false);
पूर्ण

अटल स्थिर काष्ठा mlx5e_profile mlx5e_nic_profile = अणु
	.init		   = mlx5e_nic_init,
	.cleanup	   = mlx5e_nic_cleanup,
	.init_rx	   = mlx5e_init_nic_rx,
	.cleanup_rx	   = mlx5e_cleanup_nic_rx,
	.init_tx	   = mlx5e_init_nic_tx,
	.cleanup_tx	   = mlx5e_cleanup_nic_tx,
	.enable		   = mlx5e_nic_enable,
	.disable	   = mlx5e_nic_disable,
	.update_rx	   = mlx5e_update_nic_rx,
	.update_stats	   = mlx5e_stats_update_nकरो_stats,
	.update_carrier	   = mlx5e_update_carrier,
	.rx_handlers       = &mlx5e_rx_handlers_nic,
	.max_tc		   = MLX5E_MAX_NUM_TC,
	.rq_groups	   = MLX5E_NUM_RQ_GROUPS(XSK),
	.stats_grps	   = mlx5e_nic_stats_grps,
	.stats_grps_num	   = mlx5e_nic_stats_grps_num,
	.rx_ptp_support    = true,
पूर्ण;

/* mlx5e generic netdev management API (move to en_common.c) */
पूर्णांक mlx5e_priv_init(काष्ठा mlx5e_priv *priv,
		    काष्ठा net_device *netdev,
		    काष्ठा mlx5_core_dev *mdev)
अणु
	/* priv init */
	priv->mdev        = mdev;
	priv->netdev      = netdev;
	priv->msglevel    = MLX5E_MSG_LEVEL;
	priv->max_खोलोed_tc = 1;

	अगर (!alloc_cpumask_var(&priv->scratchpad.cpumask, GFP_KERNEL))
		वापस -ENOMEM;

	mutex_init(&priv->state_lock);
	hash_init(priv->htb.qos_tc2node);
	INIT_WORK(&priv->update_carrier_work, mlx5e_update_carrier_work);
	INIT_WORK(&priv->set_rx_mode_work, mlx5e_set_rx_mode_work);
	INIT_WORK(&priv->tx_समयout_work, mlx5e_tx_समयout_work);
	INIT_WORK(&priv->update_stats_work, mlx5e_update_stats_work);

	priv->wq = create_singlethपढ़ो_workqueue("mlx5e");
	अगर (!priv->wq)
		जाओ err_मुक्त_cpumask;

	वापस 0;

err_मुक्त_cpumask:
	मुक्त_cpumask_var(priv->scratchpad.cpumask);

	वापस -ENOMEM;
पूर्ण

व्योम mlx5e_priv_cleanup(काष्ठा mlx5e_priv *priv)
अणु
	पूर्णांक i;

	/* bail अगर change profile failed and also rollback failed */
	अगर (!priv->mdev)
		वापस;

	destroy_workqueue(priv->wq);
	मुक्त_cpumask_var(priv->scratchpad.cpumask);

	क्रम (i = 0; i < priv->htb.max_qos_sqs; i++)
		kमुक्त(priv->htb.qos_sq_stats[i]);
	kvमुक्त(priv->htb.qos_sq_stats);

	स_रखो(priv, 0, माप(*priv));
पूर्ण

काष्ठा net_device *
mlx5e_create_netdev(काष्ठा mlx5_core_dev *mdev, अचिन्हित पूर्णांक txqs, अचिन्हित पूर्णांक rxqs)
अणु
	काष्ठा net_device *netdev;
	पूर्णांक err;

	netdev = alloc_etherdev_mqs(माप(काष्ठा mlx5e_priv), txqs, rxqs);
	अगर (!netdev) अणु
		mlx5_core_err(mdev, "alloc_etherdev_mqs() failed\n");
		वापस शून्य;
	पूर्ण

	err = mlx5e_priv_init(netdev_priv(netdev), netdev, mdev);
	अगर (err) अणु
		mlx5_core_err(mdev, "mlx5e_priv_init failed, err=%d\n", err);
		जाओ err_मुक्त_netdev;
	पूर्ण

	netअगर_carrier_off(netdev);
	dev_net_set(netdev, mlx5_core_net(mdev));

	वापस netdev;

err_मुक्त_netdev:
	मुक्त_netdev(netdev);

	वापस शून्य;
पूर्ण

अटल व्योम mlx5e_update_features(काष्ठा net_device *netdev)
अणु
	अगर (netdev->reg_state != NETREG_REGISTERED)
		वापस; /* features will be updated on netdev registration */

	rtnl_lock();
	netdev_update_features(netdev);
	rtnl_unlock();
पूर्ण

अटल व्योम mlx5e_reset_channels(काष्ठा net_device *netdev)
अणु
	netdev_reset_tc(netdev);
पूर्ण

पूर्णांक mlx5e_attach_netdev(काष्ठा mlx5e_priv *priv)
अणु
	स्थिर bool take_rtnl = priv->netdev->reg_state == NETREG_REGISTERED;
	स्थिर काष्ठा mlx5e_profile *profile = priv->profile;
	पूर्णांक max_nch;
	पूर्णांक err;

	clear_bit(MLX5E_STATE_DESTROYING, &priv->state);

	/* max number of channels may have changed */
	max_nch = mlx5e_get_max_num_channels(priv->mdev);
	अगर (priv->channels.params.num_channels > max_nch) अणु
		mlx5_core_warn(priv->mdev, "MLX5E: Reducing number of channels to %d\n", max_nch);
		/* Reducing the number of channels - RXFH has to be reset, and
		 * mlx5e_num_channels_changed below will build the RQT.
		 */
		priv->netdev->priv_flags &= ~IFF_RXFH_CONFIGURED;
		priv->channels.params.num_channels = max_nch;
	पूर्ण
	/* 1. Set the real number of queues in the kernel the first समय.
	 * 2. Set our शेष XPS cpumask.
	 * 3. Build the RQT.
	 *
	 * rtnl_lock is required by netअगर_set_real_num_*_queues in हाल the
	 * netdev has been रेजिस्टरed by this poपूर्णांक (अगर this function was called
	 * in the reload or resume flow).
	 */
	अगर (take_rtnl)
		rtnl_lock();
	err = mlx5e_num_channels_changed(priv);
	अगर (take_rtnl)
		rtnl_unlock();
	अगर (err)
		जाओ out;

	err = profile->init_tx(priv);
	अगर (err)
		जाओ out;

	err = profile->init_rx(priv);
	अगर (err)
		जाओ err_cleanup_tx;

	अगर (profile->enable)
		profile->enable(priv);

	mlx5e_update_features(priv->netdev);

	वापस 0;

err_cleanup_tx:
	profile->cleanup_tx(priv);

out:
	mlx5e_reset_channels(priv->netdev);
	set_bit(MLX5E_STATE_DESTROYING, &priv->state);
	cancel_work_sync(&priv->update_stats_work);
	वापस err;
पूर्ण

व्योम mlx5e_detach_netdev(काष्ठा mlx5e_priv *priv)
अणु
	स्थिर काष्ठा mlx5e_profile *profile = priv->profile;

	set_bit(MLX5E_STATE_DESTROYING, &priv->state);

	अगर (profile->disable)
		profile->disable(priv);
	flush_workqueue(priv->wq);

	profile->cleanup_rx(priv);
	profile->cleanup_tx(priv);
	mlx5e_reset_channels(priv->netdev);
	cancel_work_sync(&priv->update_stats_work);
पूर्ण

अटल पूर्णांक
mlx5e_netdev_attach_profile(काष्ठा net_device *netdev, काष्ठा mlx5_core_dev *mdev,
			    स्थिर काष्ठा mlx5e_profile *new_profile, व्योम *new_ppriv)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(netdev);
	पूर्णांक err;

	err = mlx5e_priv_init(priv, netdev, mdev);
	अगर (err) अणु
		mlx5_core_err(mdev, "mlx5e_priv_init failed, err=%d\n", err);
		वापस err;
	पूर्ण
	netअगर_carrier_off(netdev);
	priv->profile = new_profile;
	priv->ppriv = new_ppriv;
	err = new_profile->init(priv->mdev, priv->netdev);
	अगर (err)
		जाओ priv_cleanup;
	err = mlx5e_attach_netdev(priv);
	अगर (err)
		जाओ profile_cleanup;
	वापस err;

profile_cleanup:
	new_profile->cleanup(priv);
priv_cleanup:
	mlx5e_priv_cleanup(priv);
	वापस err;
पूर्ण

पूर्णांक mlx5e_netdev_change_profile(काष्ठा mlx5e_priv *priv,
				स्थिर काष्ठा mlx5e_profile *new_profile, व्योम *new_ppriv)
अणु
	अचिन्हित पूर्णांक new_max_nch = mlx5e_calc_max_nch(priv, new_profile);
	स्थिर काष्ठा mlx5e_profile *orig_profile = priv->profile;
	काष्ठा net_device *netdev = priv->netdev;
	काष्ठा mlx5_core_dev *mdev = priv->mdev;
	व्योम *orig_ppriv = priv->ppriv;
	पूर्णांक err, rollback_err;

	/* sanity */
	अगर (new_max_nch != priv->max_nch) अणु
		netdev_warn(netdev, "%s: Replacing profile with different max channels\n",
			    __func__);
		वापस -EINVAL;
	पूर्ण

	/* cleanup old profile */
	mlx5e_detach_netdev(priv);
	priv->profile->cleanup(priv);
	mlx5e_priv_cleanup(priv);

	err = mlx5e_netdev_attach_profile(netdev, mdev, new_profile, new_ppriv);
	अगर (err) अणु /* roll back to original profile */
		netdev_warn(netdev, "%s: new profile init failed, %d\n", __func__, err);
		जाओ rollback;
	पूर्ण

	वापस 0;

rollback:
	rollback_err = mlx5e_netdev_attach_profile(netdev, mdev, orig_profile, orig_ppriv);
	अगर (rollback_err)
		netdev_err(netdev, "%s: failed to rollback to orig profile, %d\n",
			   __func__, rollback_err);
	वापस err;
पूर्ण

व्योम mlx5e_netdev_attach_nic_profile(काष्ठा mlx5e_priv *priv)
अणु
	mlx5e_netdev_change_profile(priv, &mlx5e_nic_profile, शून्य);
पूर्ण

व्योम mlx5e_destroy_netdev(काष्ठा mlx5e_priv *priv)
अणु
	काष्ठा net_device *netdev = priv->netdev;

	mlx5e_priv_cleanup(priv);
	मुक्त_netdev(netdev);
पूर्ण

अटल पूर्णांक mlx5e_resume(काष्ठा auxiliary_device *adev)
अणु
	काष्ठा mlx5_adev *edev = container_of(adev, काष्ठा mlx5_adev, adev);
	काष्ठा mlx5e_priv *priv = dev_get_drvdata(&adev->dev);
	काष्ठा net_device *netdev = priv->netdev;
	काष्ठा mlx5_core_dev *mdev = edev->mdev;
	पूर्णांक err;

	अगर (netअगर_device_present(netdev))
		वापस 0;

	err = mlx5e_create_mdev_resources(mdev);
	अगर (err)
		वापस err;

	err = mlx5e_attach_netdev(priv);
	अगर (err) अणु
		mlx5e_destroy_mdev_resources(mdev);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mlx5e_suspend(काष्ठा auxiliary_device *adev, pm_message_t state)
अणु
	काष्ठा mlx5e_priv *priv = dev_get_drvdata(&adev->dev);
	काष्ठा net_device *netdev = priv->netdev;
	काष्ठा mlx5_core_dev *mdev = priv->mdev;

	अगर (!netअगर_device_present(netdev))
		वापस -ENODEV;

	mlx5e_detach_netdev(priv);
	mlx5e_destroy_mdev_resources(mdev);
	वापस 0;
पूर्ण

अटल पूर्णांक mlx5e_probe(काष्ठा auxiliary_device *adev,
		       स्थिर काष्ठा auxiliary_device_id *id)
अणु
	काष्ठा mlx5_adev *edev = container_of(adev, काष्ठा mlx5_adev, adev);
	स्थिर काष्ठा mlx5e_profile *profile = &mlx5e_nic_profile;
	काष्ठा mlx5_core_dev *mdev = edev->mdev;
	काष्ठा net_device *netdev;
	pm_message_t state = अणुपूर्ण;
	अचिन्हित पूर्णांक txqs, rxqs, ptp_txqs = 0;
	काष्ठा mlx5e_priv *priv;
	पूर्णांक qos_sqs = 0;
	पूर्णांक err;
	पूर्णांक nch;

	अगर (MLX5_CAP_GEN(mdev, ts_cqe_to_dest_cqn))
		ptp_txqs = profile->max_tc;

	अगर (mlx5_qos_is_supported(mdev))
		qos_sqs = mlx5e_qos_max_leaf_nodes(mdev);

	nch = mlx5e_get_max_num_channels(mdev);
	txqs = nch * profile->max_tc + ptp_txqs + qos_sqs;
	rxqs = nch * profile->rq_groups;
	netdev = mlx5e_create_netdev(mdev, txqs, rxqs);
	अगर (!netdev) अणु
		mlx5_core_err(mdev, "mlx5e_create_netdev failed\n");
		वापस -ENOMEM;
	पूर्ण

	mlx5e_build_nic_netdev(netdev);

	priv = netdev_priv(netdev);
	dev_set_drvdata(&adev->dev, priv);

	priv->profile = profile;
	priv->ppriv = शून्य;

	err = mlx5e_devlink_port_रेजिस्टर(priv);
	अगर (err) अणु
		mlx5_core_err(mdev, "mlx5e_devlink_port_register failed, %d\n", err);
		जाओ err_destroy_netdev;
	पूर्ण

	err = profile->init(mdev, netdev);
	अगर (err) अणु
		mlx5_core_err(mdev, "mlx5e_nic_profile init failed, %d\n", err);
		जाओ err_devlink_cleanup;
	पूर्ण

	err = mlx5e_resume(adev);
	अगर (err) अणु
		mlx5_core_err(mdev, "mlx5e_resume failed, %d\n", err);
		जाओ err_profile_cleanup;
	पूर्ण

	err = रेजिस्टर_netdev(netdev);
	अगर (err) अणु
		mlx5_core_err(mdev, "register_netdev failed, %d\n", err);
		जाओ err_resume;
	पूर्ण

	mlx5e_devlink_port_type_eth_set(priv);

	mlx5e_dcbnl_init_app(priv);
	mlx5_uplink_netdev_set(mdev, netdev);
	वापस 0;

err_resume:
	mlx5e_suspend(adev, state);
err_profile_cleanup:
	profile->cleanup(priv);
err_devlink_cleanup:
	mlx5e_devlink_port_unरेजिस्टर(priv);
err_destroy_netdev:
	mlx5e_destroy_netdev(priv);
	वापस err;
पूर्ण

अटल व्योम mlx5e_हटाओ(काष्ठा auxiliary_device *adev)
अणु
	काष्ठा mlx5e_priv *priv = dev_get_drvdata(&adev->dev);
	pm_message_t state = अणुपूर्ण;

	mlx5e_dcbnl_delete_app(priv);
	unरेजिस्टर_netdev(priv->netdev);
	mlx5e_suspend(adev, state);
	priv->profile->cleanup(priv);
	mlx5e_devlink_port_unरेजिस्टर(priv);
	mlx5e_destroy_netdev(priv);
पूर्ण

अटल स्थिर काष्ठा auxiliary_device_id mlx5e_id_table[] = अणु
	अणु .name = MLX5_ADEV_NAME ".eth", पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(auxiliary, mlx5e_id_table);

अटल काष्ठा auxiliary_driver mlx5e_driver = अणु
	.name = "eth",
	.probe = mlx5e_probe,
	.हटाओ = mlx5e_हटाओ,
	.suspend = mlx5e_suspend,
	.resume = mlx5e_resume,
	.id_table = mlx5e_id_table,
पूर्ण;

पूर्णांक mlx5e_init(व्योम)
अणु
	पूर्णांक ret;

	mlx5e_ipsec_build_inverse_table();
	mlx5e_build_ptys2ethtool_map();
	ret = auxiliary_driver_रेजिस्टर(&mlx5e_driver);
	अगर (ret)
		वापस ret;

	ret = mlx5e_rep_init();
	अगर (ret)
		auxiliary_driver_unरेजिस्टर(&mlx5e_driver);
	वापस ret;
पूर्ण

व्योम mlx5e_cleanup(व्योम)
अणु
	mlx5e_rep_cleanup();
	auxiliary_driver_unरेजिस्टर(&mlx5e_driver);
पूर्ण
