<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-2-Clause)
/* Copyright (C) 2017-2018 Netronome Systems, Inc. */

#समावेश <net/pkt_cls.h>

#समावेश "../nfpcore/nfp_cpp.h"
#समावेश "../nfpcore/nfp_nffw.h"
#समावेश "../nfpcore/nfp_nsp.h"
#समावेश "../nfp_app.h"
#समावेश "../nfp_main.h"
#समावेश "../nfp_net.h"
#समावेश "../nfp_port.h"
#समावेश "fw.h"
#समावेश "main.h"

स्थिर काष्ठा rhashtable_params nfp_bpf_maps_neutral_params = अणु
	.nelem_hपूर्णांक		= 4,
	.key_len		= माप_field(काष्ठा bpf_map, id),
	.key_offset		= दुरत्व(काष्ठा nfp_bpf_neutral_map, map_id),
	.head_offset		= दुरत्व(काष्ठा nfp_bpf_neutral_map, l),
	.स्वतःmatic_shrinking	= true,
पूर्ण;

अटल bool nfp_net_ebpf_capable(काष्ठा nfp_net *nn)
अणु
#अगर_घोषित __LITTLE_ENDIAN
	काष्ठा nfp_app_bpf *bpf = nn->app->priv;

	वापस nn->cap & NFP_NET_CFG_CTRL_BPF &&
	       bpf->abi_version &&
	       nn_पढ़ोb(nn, NFP_NET_CFG_BPF_ABI) == bpf->abi_version;
#अन्यथा
	वापस false;
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक
nfp_bpf_xdp_offload(काष्ठा nfp_app *app, काष्ठा nfp_net *nn,
		    काष्ठा bpf_prog *prog, काष्ठा netlink_ext_ack *extack)
अणु
	bool running, xdp_running;

	अगर (!nfp_net_ebpf_capable(nn))
		वापस -EINVAL;

	running = nn->dp.ctrl & NFP_NET_CFG_CTRL_BPF;
	xdp_running = running && nn->xdp_hw.prog;

	अगर (!prog && !xdp_running)
		वापस 0;
	अगर (prog && running && !xdp_running)
		वापस -EBUSY;

	वापस nfp_net_bpf_offload(nn, prog, running, extack);
पूर्ण

अटल स्थिर अक्षर *nfp_bpf_extra_cap(काष्ठा nfp_app *app, काष्ठा nfp_net *nn)
अणु
	वापस nfp_net_ebpf_capable(nn) ? "BPF" : "";
पूर्ण

अटल पूर्णांक
nfp_bpf_vnic_alloc(काष्ठा nfp_app *app, काष्ठा nfp_net *nn, अचिन्हित पूर्णांक id)
अणु
	काष्ठा nfp_pf *pf = app->pf;
	काष्ठा nfp_bpf_vnic *bv;
	पूर्णांक err;

	अगर (!pf->eth_tbl) अणु
		nfp_err(pf->cpp, "No ETH table\n");
		वापस -EINVAL;
	पूर्ण
	अगर (pf->max_data_vnics != pf->eth_tbl->count) अणु
		nfp_err(pf->cpp, "ETH entries don't match vNICs (%d vs %d)\n",
			pf->max_data_vnics, pf->eth_tbl->count);
		वापस -EINVAL;
	पूर्ण

	bv = kzalloc(माप(*bv), GFP_KERNEL);
	अगर (!bv)
		वापस -ENOMEM;
	nn->app_priv = bv;

	err = nfp_app_nic_vnic_alloc(app, nn, id);
	अगर (err)
		जाओ err_मुक्त_priv;

	bv->start_off = nn_पढ़ोw(nn, NFP_NET_CFG_BPF_START);
	bv->tgt_करोne = nn_पढ़ोw(nn, NFP_NET_CFG_BPF_DONE);

	वापस 0;
err_मुक्त_priv:
	kमुक्त(nn->app_priv);
	वापस err;
पूर्ण

अटल व्योम nfp_bpf_vnic_मुक्त(काष्ठा nfp_app *app, काष्ठा nfp_net *nn)
अणु
	काष्ठा nfp_bpf_vnic *bv = nn->app_priv;

	WARN_ON(bv->tc_prog);
	kमुक्त(bv);
पूर्ण

अटल पूर्णांक nfp_bpf_setup_tc_block_cb(क्रमागत tc_setup_type type,
				     व्योम *type_data, व्योम *cb_priv)
अणु
	काष्ठा tc_cls_bpf_offload *cls_bpf = type_data;
	काष्ठा nfp_net *nn = cb_priv;
	काष्ठा bpf_prog *oldprog;
	काष्ठा nfp_bpf_vnic *bv;
	पूर्णांक err;

	अगर (type != TC_SETUP_CLSBPF) अणु
		NL_SET_ERR_MSG_MOD(cls_bpf->common.extack,
				   "only offload of BPF classifiers supported");
		वापस -EOPNOTSUPP;
	पूर्ण
	अगर (!tc_cls_can_offload_and_chain0(nn->dp.netdev, &cls_bpf->common))
		वापस -EOPNOTSUPP;
	अगर (!nfp_net_ebpf_capable(nn)) अणु
		NL_SET_ERR_MSG_MOD(cls_bpf->common.extack,
				   "NFP firmware does not support eBPF offload");
		वापस -EOPNOTSUPP;
	पूर्ण
	अगर (cls_bpf->common.protocol != htons(ETH_P_ALL)) अणु
		NL_SET_ERR_MSG_MOD(cls_bpf->common.extack,
				   "only ETH_P_ALL supported as filter protocol");
		वापस -EOPNOTSUPP;
	पूर्ण

	/* Only support TC direct action */
	अगर (!cls_bpf->exts_पूर्णांकegrated ||
	    tcf_exts_has_actions(cls_bpf->exts)) अणु
		NL_SET_ERR_MSG_MOD(cls_bpf->common.extack,
				   "only direct action with no legacy actions supported");
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (cls_bpf->command != TC_CLSBPF_OFFLOAD)
		वापस -EOPNOTSUPP;

	bv = nn->app_priv;
	oldprog = cls_bpf->oldprog;

	/* Don't remove if oldprog doesn't match driver's state */
	अगर (bv->tc_prog != oldprog) अणु
		oldprog = शून्य;
		अगर (!cls_bpf->prog)
			वापस 0;
	पूर्ण

	err = nfp_net_bpf_offload(nn, cls_bpf->prog, oldprog,
				  cls_bpf->common.extack);
	अगर (err)
		वापस err;

	bv->tc_prog = cls_bpf->prog;
	nn->port->tc_offload_cnt = !!bv->tc_prog;
	वापस 0;
पूर्ण

अटल LIST_HEAD(nfp_bpf_block_cb_list);

अटल पूर्णांक nfp_bpf_setup_tc(काष्ठा nfp_app *app, काष्ठा net_device *netdev,
			    क्रमागत tc_setup_type type, व्योम *type_data)
अणु
	काष्ठा nfp_net *nn = netdev_priv(netdev);

	चयन (type) अणु
	हाल TC_SETUP_BLOCK:
		वापस flow_block_cb_setup_simple(type_data,
						  &nfp_bpf_block_cb_list,
						  nfp_bpf_setup_tc_block_cb,
						  nn, nn, true);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक
nfp_bpf_check_mtu(काष्ठा nfp_app *app, काष्ठा net_device *netdev, पूर्णांक new_mtu)
अणु
	काष्ठा nfp_net *nn = netdev_priv(netdev);
	अचिन्हित पूर्णांक max_mtu;

	अगर (~nn->dp.ctrl & NFP_NET_CFG_CTRL_BPF)
		वापस 0;

	max_mtu = nn_पढ़ोb(nn, NFP_NET_CFG_BPF_INL_MTU) * 64 - 32;
	अगर (new_mtu > max_mtu) अणु
		nn_info(nn, "BPF offload active, MTU over %u not supported\n",
			max_mtu);
		वापस -EBUSY;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक
nfp_bpf_parse_cap_adjust_head(काष्ठा nfp_app_bpf *bpf, व्योम __iomem *value,
			      u32 length)
अणु
	काष्ठा nfp_bpf_cap_tlv_adjust_head __iomem *cap = value;
	काष्ठा nfp_cpp *cpp = bpf->app->pf->cpp;

	अगर (length < माप(*cap)) अणु
		nfp_err(cpp, "truncated adjust_head TLV: %d\n", length);
		वापस -EINVAL;
	पूर्ण

	bpf->adjust_head.flags = पढ़ोl(&cap->flags);
	bpf->adjust_head.off_min = पढ़ोl(&cap->off_min);
	bpf->adjust_head.off_max = पढ़ोl(&cap->off_max);
	bpf->adjust_head.guaranteed_sub = पढ़ोl(&cap->guaranteed_sub);
	bpf->adjust_head.guaranteed_add = पढ़ोl(&cap->guaranteed_add);

	अगर (bpf->adjust_head.off_min > bpf->adjust_head.off_max) अणु
		nfp_err(cpp, "invalid adjust_head TLV: min > max\n");
		वापस -EINVAL;
	पूर्ण
	अगर (!FIELD_FIT(UR_REG_IMM_MAX, bpf->adjust_head.off_min) ||
	    !FIELD_FIT(UR_REG_IMM_MAX, bpf->adjust_head.off_max)) अणु
		nfp_warn(cpp, "disabling adjust_head - driver expects min/max to fit in as immediates\n");
		स_रखो(&bpf->adjust_head, 0, माप(bpf->adjust_head));
		वापस 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
nfp_bpf_parse_cap_func(काष्ठा nfp_app_bpf *bpf, व्योम __iomem *value, u32 length)
अणु
	काष्ठा nfp_bpf_cap_tlv_func __iomem *cap = value;

	अगर (length < माप(*cap)) अणु
		nfp_err(bpf->app->cpp, "truncated function TLV: %d\n", length);
		वापस -EINVAL;
	पूर्ण

	चयन (पढ़ोl(&cap->func_id)) अणु
	हाल BPF_FUNC_map_lookup_elem:
		bpf->helpers.map_lookup = पढ़ोl(&cap->func_addr);
		अवरोध;
	हाल BPF_FUNC_map_update_elem:
		bpf->helpers.map_update = पढ़ोl(&cap->func_addr);
		अवरोध;
	हाल BPF_FUNC_map_delete_elem:
		bpf->helpers.map_delete = पढ़ोl(&cap->func_addr);
		अवरोध;
	हाल BPF_FUNC_perf_event_output:
		bpf->helpers.perf_event_output = पढ़ोl(&cap->func_addr);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
nfp_bpf_parse_cap_maps(काष्ठा nfp_app_bpf *bpf, व्योम __iomem *value, u32 length)
अणु
	काष्ठा nfp_bpf_cap_tlv_maps __iomem *cap = value;

	अगर (length < माप(*cap)) अणु
		nfp_err(bpf->app->cpp, "truncated maps TLV: %d\n", length);
		वापस -EINVAL;
	पूर्ण

	bpf->maps.types = पढ़ोl(&cap->types);
	bpf->maps.max_maps = पढ़ोl(&cap->max_maps);
	bpf->maps.max_elems = पढ़ोl(&cap->max_elems);
	bpf->maps.max_key_sz = पढ़ोl(&cap->max_key_sz);
	bpf->maps.max_val_sz = पढ़ोl(&cap->max_val_sz);
	bpf->maps.max_elem_sz = पढ़ोl(&cap->max_elem_sz);

	वापस 0;
पूर्ण

अटल पूर्णांक
nfp_bpf_parse_cap_अक्रमom(काष्ठा nfp_app_bpf *bpf, व्योम __iomem *value,
			 u32 length)
अणु
	bpf->pseuकरो_अक्रमom = true;
	वापस 0;
पूर्ण

अटल पूर्णांक
nfp_bpf_parse_cap_qsel(काष्ठा nfp_app_bpf *bpf, व्योम __iomem *value, u32 length)
अणु
	bpf->queue_select = true;
	वापस 0;
पूर्ण

अटल पूर्णांक
nfp_bpf_parse_cap_adjust_tail(काष्ठा nfp_app_bpf *bpf, व्योम __iomem *value,
			      u32 length)
अणु
	bpf->adjust_tail = true;
	वापस 0;
पूर्ण

अटल पूर्णांक
nfp_bpf_parse_cap_cmsg_multi_ent(काष्ठा nfp_app_bpf *bpf, व्योम __iomem *value,
				 u32 length)
अणु
	bpf->cmsg_multi_ent = true;
	वापस 0;
पूर्ण

अटल पूर्णांक
nfp_bpf_parse_cap_abi_version(काष्ठा nfp_app_bpf *bpf, व्योम __iomem *value,
			      u32 length)
अणु
	अगर (length < 4) अणु
		nfp_err(bpf->app->cpp, "truncated ABI version TLV: %d\n",
			length);
		वापस -EINVAL;
	पूर्ण

	bpf->abi_version = पढ़ोl(value);
	अगर (bpf->abi_version < 2 || bpf->abi_version > 3) अणु
		nfp_warn(bpf->app->cpp, "unsupported BPF ABI version: %d\n",
			 bpf->abi_version);
		bpf->abi_version = 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक nfp_bpf_parse_capabilities(काष्ठा nfp_app *app)
अणु
	काष्ठा nfp_cpp *cpp = app->pf->cpp;
	काष्ठा nfp_cpp_area *area;
	u8 __iomem *mem, *start;

	mem = nfp_rtsym_map(app->pf->rtbl, "_abi_bpf_capabilities", "bpf.cap",
			    8, &area);
	अगर (IS_ERR(mem))
		वापस PTR_ERR(mem) == -ENOENT ? 0 : PTR_ERR(mem);

	start = mem;
	जबतक (mem - start + 8 <= nfp_cpp_area_size(area)) अणु
		u8 __iomem *value;
		u32 type, length;

		type = पढ़ोl(mem);
		length = पढ़ोl(mem + 4);
		value = mem + 8;

		mem += 8 + length;
		अगर (mem - start > nfp_cpp_area_size(area))
			जाओ err_release_मुक्त;

		चयन (type) अणु
		हाल NFP_BPF_CAP_TYPE_FUNC:
			अगर (nfp_bpf_parse_cap_func(app->priv, value, length))
				जाओ err_release_मुक्त;
			अवरोध;
		हाल NFP_BPF_CAP_TYPE_ADJUST_HEAD:
			अगर (nfp_bpf_parse_cap_adjust_head(app->priv, value,
							  length))
				जाओ err_release_मुक्त;
			अवरोध;
		हाल NFP_BPF_CAP_TYPE_MAPS:
			अगर (nfp_bpf_parse_cap_maps(app->priv, value, length))
				जाओ err_release_मुक्त;
			अवरोध;
		हाल NFP_BPF_CAP_TYPE_RANDOM:
			अगर (nfp_bpf_parse_cap_अक्रमom(app->priv, value, length))
				जाओ err_release_मुक्त;
			अवरोध;
		हाल NFP_BPF_CAP_TYPE_QUEUE_SELECT:
			अगर (nfp_bpf_parse_cap_qsel(app->priv, value, length))
				जाओ err_release_मुक्त;
			अवरोध;
		हाल NFP_BPF_CAP_TYPE_ADJUST_TAIL:
			अगर (nfp_bpf_parse_cap_adjust_tail(app->priv, value,
							  length))
				जाओ err_release_मुक्त;
			अवरोध;
		हाल NFP_BPF_CAP_TYPE_ABI_VERSION:
			अगर (nfp_bpf_parse_cap_abi_version(app->priv, value,
							  length))
				जाओ err_release_मुक्त;
			अवरोध;
		हाल NFP_BPF_CAP_TYPE_CMSG_MULTI_ENT:
			अगर (nfp_bpf_parse_cap_cmsg_multi_ent(app->priv, value,
							     length))
				जाओ err_release_मुक्त;
			अवरोध;
		शेष:
			nfp_dbg(cpp, "unknown BPF capability: %d\n", type);
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (mem - start != nfp_cpp_area_size(area)) अणु
		nfp_err(cpp, "BPF capabilities left after parsing, parsed:%zd total length:%zu\n",
			mem - start, nfp_cpp_area_size(area));
		जाओ err_release_मुक्त;
	पूर्ण

	nfp_cpp_area_release_मुक्त(area);

	वापस 0;

err_release_मुक्त:
	nfp_err(cpp, "invalid BPF capabilities at offset:%zd\n", mem - start);
	nfp_cpp_area_release_मुक्त(area);
	वापस -EINVAL;
पूर्ण

अटल व्योम nfp_bpf_init_capabilities(काष्ठा nfp_app_bpf *bpf)
अणु
	bpf->abi_version = 2; /* Original BPF ABI version */
पूर्ण

अटल पूर्णांक nfp_bpf_nकरो_init(काष्ठा nfp_app *app, काष्ठा net_device *netdev)
अणु
	काष्ठा nfp_app_bpf *bpf = app->priv;

	वापस bpf_offload_dev_netdev_रेजिस्टर(bpf->bpf_dev, netdev);
पूर्ण

अटल व्योम nfp_bpf_nकरो_uninit(काष्ठा nfp_app *app, काष्ठा net_device *netdev)
अणु
	काष्ठा nfp_app_bpf *bpf = app->priv;

	bpf_offload_dev_netdev_unरेजिस्टर(bpf->bpf_dev, netdev);
पूर्ण

अटल पूर्णांक nfp_bpf_start(काष्ठा nfp_app *app)
अणु
	काष्ठा nfp_app_bpf *bpf = app->priv;

	अगर (app->ctrl->dp.mtu < nfp_bpf_ctrl_cmsg_min_mtu(bpf)) अणु
		nfp_err(bpf->app->cpp,
			"ctrl channel MTU below min required %u < %u\n",
			app->ctrl->dp.mtu, nfp_bpf_ctrl_cmsg_min_mtu(bpf));
		वापस -EINVAL;
	पूर्ण

	अगर (bpf->cmsg_multi_ent)
		bpf->cmsg_cache_cnt = nfp_bpf_ctrl_cmsg_cache_cnt(bpf);
	अन्यथा
		bpf->cmsg_cache_cnt = 1;

	वापस 0;
पूर्ण

अटल पूर्णांक nfp_bpf_init(काष्ठा nfp_app *app)
अणु
	काष्ठा nfp_app_bpf *bpf;
	पूर्णांक err;

	bpf = kzalloc(माप(*bpf), GFP_KERNEL);
	अगर (!bpf)
		वापस -ENOMEM;
	bpf->app = app;
	app->priv = bpf;

	INIT_LIST_HEAD(&bpf->map_list);

	err = nfp_ccm_init(&bpf->ccm, app);
	अगर (err)
		जाओ err_मुक्त_bpf;

	err = rhashtable_init(&bpf->maps_neutral, &nfp_bpf_maps_neutral_params);
	अगर (err)
		जाओ err_clean_ccm;

	nfp_bpf_init_capabilities(bpf);

	err = nfp_bpf_parse_capabilities(app);
	अगर (err)
		जाओ err_मुक्त_neutral_maps;

	अगर (bpf->abi_version < 3) अणु
		bpf->cmsg_key_sz = CMSG_MAP_KEY_LW * 4;
		bpf->cmsg_val_sz = CMSG_MAP_VALUE_LW * 4;
	पूर्ण अन्यथा अणु
		bpf->cmsg_key_sz = bpf->maps.max_key_sz;
		bpf->cmsg_val_sz = bpf->maps.max_val_sz;
		app->ctrl_mtu = nfp_bpf_ctrl_cmsg_mtu(bpf);
	पूर्ण

	bpf->bpf_dev = bpf_offload_dev_create(&nfp_bpf_dev_ops, bpf);
	err = PTR_ERR_OR_ZERO(bpf->bpf_dev);
	अगर (err)
		जाओ err_मुक्त_neutral_maps;

	वापस 0;

err_मुक्त_neutral_maps:
	rhashtable_destroy(&bpf->maps_neutral);
err_clean_ccm:
	nfp_ccm_clean(&bpf->ccm);
err_मुक्त_bpf:
	kमुक्त(bpf);
	वापस err;
पूर्ण

अटल व्योम nfp_bpf_clean(काष्ठा nfp_app *app)
अणु
	काष्ठा nfp_app_bpf *bpf = app->priv;

	bpf_offload_dev_destroy(bpf->bpf_dev);
	nfp_ccm_clean(&bpf->ccm);
	WARN_ON(!list_empty(&bpf->map_list));
	WARN_ON(bpf->maps_in_use || bpf->map_elems_in_use);
	rhashtable_मुक्त_and_destroy(&bpf->maps_neutral,
				    nfp_check_rhashtable_empty, शून्य);
	kमुक्त(bpf);
पूर्ण

स्थिर काष्ठा nfp_app_type app_bpf = अणु
	.id		= NFP_APP_BPF_NIC,
	.name		= "ebpf",

	.ctrl_cap_mask	= 0,

	.init		= nfp_bpf_init,
	.clean		= nfp_bpf_clean,
	.start		= nfp_bpf_start,

	.check_mtu	= nfp_bpf_check_mtu,

	.extra_cap	= nfp_bpf_extra_cap,

	.nकरो_init	= nfp_bpf_nकरो_init,
	.nकरो_uninit	= nfp_bpf_nकरो_uninit,

	.vnic_alloc	= nfp_bpf_vnic_alloc,
	.vnic_मुक्त	= nfp_bpf_vnic_मुक्त,

	.ctrl_msg_rx	= nfp_bpf_ctrl_msg_rx,
	.ctrl_msg_rx_raw	= nfp_bpf_ctrl_msg_rx_raw,

	.setup_tc	= nfp_bpf_setup_tc,
	.bpf		= nfp_nकरो_bpf,
	.xdp_offload	= nfp_bpf_xdp_offload,
पूर्ण;
