<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-2-Clause)
/* Copyright (C) 2016-2018 Netronome Systems, Inc. */

/*
 * nfp_net_offload.c
 * Netronome network device driver: TC offload functions क्रम PF and VF
 */

#घोषणा pr_fmt(fmt)	"NFP net bpf: " fmt

#समावेश <linux/bpf.h>
#समावेश <linux/kernel.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/pci.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/समयr.h>
#समावेश <linux/list.h>
#समावेश <linux/mm.h>

#समावेश <net/pkt_cls.h>
#समावेश <net/tc_act/tc_gact.h>
#समावेश <net/tc_act/tc_mirred.h>

#समावेश "main.h"
#समावेश "../ccm.h"
#समावेश "../nfp_app.h"
#समावेश "../nfp_net_ctrl.h"
#समावेश "../nfp_net.h"

अटल पूर्णांक
nfp_map_ptr_record(काष्ठा nfp_app_bpf *bpf, काष्ठा nfp_prog *nfp_prog,
		   काष्ठा bpf_map *map)
अणु
	काष्ठा nfp_bpf_neutral_map *record;
	पूर्णांक err;

	/* Reuse path - other offloaded program is alपढ़ोy tracking this map. */
	record = rhashtable_lookup_fast(&bpf->maps_neutral, &map->id,
					nfp_bpf_maps_neutral_params);
	अगर (record) अणु
		nfp_prog->map_records[nfp_prog->map_records_cnt++] = record;
		record->count++;
		वापस 0;
	पूर्ण

	/* Grab a single ref to the map क्रम our record.  The prog destroy nकरो
	 * happens after मुक्त_used_maps().
	 */
	bpf_map_inc(map);

	record = kदो_स्मृति(माप(*record), GFP_KERNEL);
	अगर (!record) अणु
		err = -ENOMEM;
		जाओ err_map_put;
	पूर्ण

	record->ptr = map;
	record->map_id = map->id;
	record->count = 1;

	err = rhashtable_insert_fast(&bpf->maps_neutral, &record->l,
				     nfp_bpf_maps_neutral_params);
	अगर (err)
		जाओ err_मुक्त_rec;

	nfp_prog->map_records[nfp_prog->map_records_cnt++] = record;

	वापस 0;

err_मुक्त_rec:
	kमुक्त(record);
err_map_put:
	bpf_map_put(map);
	वापस err;
पूर्ण

अटल व्योम
nfp_map_ptrs_क्रमget(काष्ठा nfp_app_bpf *bpf, काष्ठा nfp_prog *nfp_prog)
अणु
	bool मुक्तd = false;
	पूर्णांक i;

	क्रम (i = 0; i < nfp_prog->map_records_cnt; i++) अणु
		अगर (--nfp_prog->map_records[i]->count) अणु
			nfp_prog->map_records[i] = शून्य;
			जारी;
		पूर्ण

		WARN_ON(rhashtable_हटाओ_fast(&bpf->maps_neutral,
					       &nfp_prog->map_records[i]->l,
					       nfp_bpf_maps_neutral_params));
		मुक्तd = true;
	पूर्ण

	अगर (मुक्तd) अणु
		synchronize_rcu();

		क्रम (i = 0; i < nfp_prog->map_records_cnt; i++)
			अगर (nfp_prog->map_records[i]) अणु
				bpf_map_put(nfp_prog->map_records[i]->ptr);
				kमुक्त(nfp_prog->map_records[i]);
			पूर्ण
	पूर्ण

	kमुक्त(nfp_prog->map_records);
	nfp_prog->map_records = शून्य;
	nfp_prog->map_records_cnt = 0;
पूर्ण

अटल पूर्णांक
nfp_map_ptrs_record(काष्ठा nfp_app_bpf *bpf, काष्ठा nfp_prog *nfp_prog,
		    काष्ठा bpf_prog *prog)
अणु
	पूर्णांक i, cnt, err = 0;

	mutex_lock(&prog->aux->used_maps_mutex);

	/* Quickly count the maps we will have to remember */
	cnt = 0;
	क्रम (i = 0; i < prog->aux->used_map_cnt; i++)
		अगर (bpf_map_offload_neutral(prog->aux->used_maps[i]))
			cnt++;
	अगर (!cnt)
		जाओ out;

	nfp_prog->map_records = kदो_स्मृति_array(cnt,
					      माप(nfp_prog->map_records[0]),
					      GFP_KERNEL);
	अगर (!nfp_prog->map_records) अणु
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	क्रम (i = 0; i < prog->aux->used_map_cnt; i++)
		अगर (bpf_map_offload_neutral(prog->aux->used_maps[i])) अणु
			err = nfp_map_ptr_record(bpf, nfp_prog,
						 prog->aux->used_maps[i]);
			अगर (err) अणु
				nfp_map_ptrs_क्रमget(bpf, nfp_prog);
				जाओ out;
			पूर्ण
		पूर्ण
	WARN_ON(cnt != nfp_prog->map_records_cnt);

out:
	mutex_unlock(&prog->aux->used_maps_mutex);
	वापस err;
पूर्ण

अटल पूर्णांक
nfp_prog_prepare(काष्ठा nfp_prog *nfp_prog, स्थिर काष्ठा bpf_insn *prog,
		 अचिन्हित पूर्णांक cnt)
अणु
	काष्ठा nfp_insn_meta *meta;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < cnt; i++) अणु
		meta = kzalloc(माप(*meta), GFP_KERNEL);
		अगर (!meta)
			वापस -ENOMEM;

		meta->insn = prog[i];
		meta->n = i;
		अगर (is_mbpf_alu(meta)) अणु
			meta->umin_src = U64_MAX;
			meta->umin_dst = U64_MAX;
		पूर्ण

		list_add_tail(&meta->l, &nfp_prog->insns);
	पूर्ण
	nfp_prog->n_insns = cnt;

	nfp_bpf_jit_prepare(nfp_prog);

	वापस 0;
पूर्ण

अटल व्योम nfp_prog_मुक्त(काष्ठा nfp_prog *nfp_prog)
अणु
	काष्ठा nfp_insn_meta *meta, *पंचांगp;

	kमुक्त(nfp_prog->subprog);

	list_क्रम_each_entry_safe(meta, पंचांगp, &nfp_prog->insns, l) अणु
		list_del(&meta->l);
		kमुक्त(meta);
	पूर्ण
	kमुक्त(nfp_prog);
पूर्ण

अटल पूर्णांक nfp_bpf_verअगरier_prep(काष्ठा bpf_prog *prog)
अणु
	काष्ठा nfp_prog *nfp_prog;
	पूर्णांक ret;

	nfp_prog = kzalloc(माप(*nfp_prog), GFP_KERNEL);
	अगर (!nfp_prog)
		वापस -ENOMEM;
	prog->aux->offload->dev_priv = nfp_prog;

	INIT_LIST_HEAD(&nfp_prog->insns);
	nfp_prog->type = prog->type;
	nfp_prog->bpf = bpf_offload_dev_priv(prog->aux->offload->offdev);

	ret = nfp_prog_prepare(nfp_prog, prog->insnsi, prog->len);
	अगर (ret)
		जाओ err_मुक्त;

	nfp_prog->verअगरier_meta = nfp_prog_first_meta(nfp_prog);

	वापस 0;

err_मुक्त:
	nfp_prog_मुक्त(nfp_prog);

	वापस ret;
पूर्ण

अटल पूर्णांक nfp_bpf_translate(काष्ठा bpf_prog *prog)
अणु
	काष्ठा nfp_net *nn = netdev_priv(prog->aux->offload->netdev);
	काष्ठा nfp_prog *nfp_prog = prog->aux->offload->dev_priv;
	अचिन्हित पूर्णांक max_instr;
	पूर्णांक err;

	/* We depend on dead code elimination succeeding */
	अगर (prog->aux->offload->opt_failed)
		वापस -EINVAL;

	max_instr = nn_पढ़ोw(nn, NFP_NET_CFG_BPF_MAX_LEN);
	nfp_prog->__prog_alloc_len = max_instr * माप(u64);

	nfp_prog->prog = kvदो_स्मृति(nfp_prog->__prog_alloc_len, GFP_KERNEL);
	अगर (!nfp_prog->prog)
		वापस -ENOMEM;

	err = nfp_bpf_jit(nfp_prog);
	अगर (err)
		वापस err;

	prog->aux->offload->jited_len = nfp_prog->prog_len * माप(u64);
	prog->aux->offload->jited_image = nfp_prog->prog;

	वापस nfp_map_ptrs_record(nfp_prog->bpf, nfp_prog, prog);
पूर्ण

अटल व्योम nfp_bpf_destroy(काष्ठा bpf_prog *prog)
अणु
	काष्ठा nfp_prog *nfp_prog = prog->aux->offload->dev_priv;

	kvमुक्त(nfp_prog->prog);
	nfp_map_ptrs_क्रमget(nfp_prog->bpf, nfp_prog);
	nfp_prog_मुक्त(nfp_prog);
पूर्ण

/* Atomic engine requires values to be in big endian, we need to byte swap
 * the value words used with xadd.
 */
अटल व्योम nfp_map_bpf_byte_swap(काष्ठा nfp_bpf_map *nfp_map, व्योम *value)
अणु
	u32 *word = value;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < DIV_ROUND_UP(nfp_map->offmap->map.value_size, 4); i++)
		अगर (nfp_map->use_map[i].type == NFP_MAP_USE_ATOMIC_CNT)
			word[i] = (__क्रमce u32)cpu_to_be32(word[i]);
पूर्ण

/* Mark value as unsafely initialized in हाल it becomes atomic later
 * and we didn't byte swap something non-byte swap neutral.
 */
अटल व्योम
nfp_map_bpf_byte_swap_record(काष्ठा nfp_bpf_map *nfp_map, व्योम *value)
अणु
	u32 *word = value;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < DIV_ROUND_UP(nfp_map->offmap->map.value_size, 4); i++)
		अगर (nfp_map->use_map[i].type == NFP_MAP_UNUSED &&
		    word[i] != (__क्रमce u32)cpu_to_be32(word[i]))
			nfp_map->use_map[i].non_zero_update = 1;
पूर्ण

अटल पूर्णांक
nfp_bpf_map_lookup_entry(काष्ठा bpf_offloaded_map *offmap,
			 व्योम *key, व्योम *value)
अणु
	पूर्णांक err;

	err = nfp_bpf_ctrl_lookup_entry(offmap, key, value);
	अगर (err)
		वापस err;

	nfp_map_bpf_byte_swap(offmap->dev_priv, value);
	वापस 0;
पूर्ण

अटल पूर्णांक
nfp_bpf_map_update_entry(काष्ठा bpf_offloaded_map *offmap,
			 व्योम *key, व्योम *value, u64 flags)
अणु
	nfp_map_bpf_byte_swap(offmap->dev_priv, value);
	nfp_map_bpf_byte_swap_record(offmap->dev_priv, value);
	वापस nfp_bpf_ctrl_update_entry(offmap, key, value, flags);
पूर्ण

अटल पूर्णांक
nfp_bpf_map_get_next_key(काष्ठा bpf_offloaded_map *offmap,
			 व्योम *key, व्योम *next_key)
अणु
	अगर (!key)
		वापस nfp_bpf_ctrl_getfirst_entry(offmap, next_key);
	वापस nfp_bpf_ctrl_getnext_entry(offmap, key, next_key);
पूर्ण

अटल पूर्णांक
nfp_bpf_map_delete_elem(काष्ठा bpf_offloaded_map *offmap, व्योम *key)
अणु
	अगर (offmap->map.map_type == BPF_MAP_TYPE_ARRAY)
		वापस -EINVAL;
	वापस nfp_bpf_ctrl_del_entry(offmap, key);
पूर्ण

अटल स्थिर काष्ठा bpf_map_dev_ops nfp_bpf_map_ops = अणु
	.map_get_next_key	= nfp_bpf_map_get_next_key,
	.map_lookup_elem	= nfp_bpf_map_lookup_entry,
	.map_update_elem	= nfp_bpf_map_update_entry,
	.map_delete_elem	= nfp_bpf_map_delete_elem,
पूर्ण;

अटल पूर्णांक
nfp_bpf_map_alloc(काष्ठा nfp_app_bpf *bpf, काष्ठा bpf_offloaded_map *offmap)
अणु
	काष्ठा nfp_bpf_map *nfp_map;
	अचिन्हित पूर्णांक use_map_size;
	दीर्घ दीर्घ पूर्णांक res;

	अगर (!bpf->maps.types)
		वापस -EOPNOTSUPP;

	अगर (offmap->map.map_flags ||
	    offmap->map.numa_node != NUMA_NO_NODE) अणु
		pr_info("map flags are not supported\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!(bpf->maps.types & 1 << offmap->map.map_type)) अणु
		pr_info("map type not supported\n");
		वापस -EOPNOTSUPP;
	पूर्ण
	अगर (bpf->maps.max_maps == bpf->maps_in_use) अणु
		pr_info("too many maps for a device\n");
		वापस -ENOMEM;
	पूर्ण
	अगर (bpf->maps.max_elems - bpf->map_elems_in_use <
	    offmap->map.max_entries) अणु
		pr_info("map with too many elements: %u, left: %u\n",
			offmap->map.max_entries,
			bpf->maps.max_elems - bpf->map_elems_in_use);
		वापस -ENOMEM;
	पूर्ण

	अगर (round_up(offmap->map.key_size, 8) +
	    round_up(offmap->map.value_size, 8) > bpf->maps.max_elem_sz) अणु
		pr_info("map elements too large: %u, FW max element size (key+value): %u\n",
			round_up(offmap->map.key_size, 8) +
			round_up(offmap->map.value_size, 8),
			bpf->maps.max_elem_sz);
		वापस -ENOMEM;
	पूर्ण
	अगर (offmap->map.key_size > bpf->maps.max_key_sz) अणु
		pr_info("map key size %u, FW max is %u\n",
			offmap->map.key_size, bpf->maps.max_key_sz);
		वापस -ENOMEM;
	पूर्ण
	अगर (offmap->map.value_size > bpf->maps.max_val_sz) अणु
		pr_info("map value size %u, FW max is %u\n",
			offmap->map.value_size, bpf->maps.max_val_sz);
		वापस -ENOMEM;
	पूर्ण

	use_map_size = DIV_ROUND_UP(offmap->map.value_size, 4) *
		       माप_field(काष्ठा nfp_bpf_map, use_map[0]);

	nfp_map = kzalloc(माप(*nfp_map) + use_map_size, GFP_USER);
	अगर (!nfp_map)
		वापस -ENOMEM;

	offmap->dev_priv = nfp_map;
	nfp_map->offmap = offmap;
	nfp_map->bpf = bpf;
	spin_lock_init(&nfp_map->cache_lock);

	res = nfp_bpf_ctrl_alloc_map(bpf, &offmap->map);
	अगर (res < 0) अणु
		kमुक्त(nfp_map);
		वापस res;
	पूर्ण

	nfp_map->tid = res;
	offmap->dev_ops = &nfp_bpf_map_ops;
	bpf->maps_in_use++;
	bpf->map_elems_in_use += offmap->map.max_entries;
	list_add_tail(&nfp_map->l, &bpf->map_list);

	वापस 0;
पूर्ण

अटल पूर्णांक
nfp_bpf_map_मुक्त(काष्ठा nfp_app_bpf *bpf, काष्ठा bpf_offloaded_map *offmap)
अणु
	काष्ठा nfp_bpf_map *nfp_map = offmap->dev_priv;

	nfp_bpf_ctrl_मुक्त_map(bpf, nfp_map);
	dev_consume_skb_any(nfp_map->cache);
	WARN_ON_ONCE(nfp_map->cache_blockers);
	list_del_init(&nfp_map->l);
	bpf->map_elems_in_use -= offmap->map.max_entries;
	bpf->maps_in_use--;
	kमुक्त(nfp_map);

	वापस 0;
पूर्ण

पूर्णांक nfp_nकरो_bpf(काष्ठा nfp_app *app, काष्ठा nfp_net *nn, काष्ठा netdev_bpf *bpf)
अणु
	चयन (bpf->command) अणु
	हाल BPF_OFFLOAD_MAP_ALLOC:
		वापस nfp_bpf_map_alloc(app->priv, bpf->offmap);
	हाल BPF_OFFLOAD_MAP_FREE:
		वापस nfp_bpf_map_मुक्त(app->priv, bpf->offmap);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल अचिन्हित दीर्घ
nfp_bpf_perf_event_copy(व्योम *dst, स्थिर व्योम *src,
			अचिन्हित दीर्घ off, अचिन्हित दीर्घ len)
अणु
	स_नकल(dst, src + off, len);
	वापस 0;
पूर्ण

पूर्णांक nfp_bpf_event_output(काष्ठा nfp_app_bpf *bpf, स्थिर व्योम *data,
			 अचिन्हित पूर्णांक len)
अणु
	काष्ठा cmsg_bpf_event *cbe = (व्योम *)data;
	काष्ठा nfp_bpf_neutral_map *record;
	u32 pkt_size, data_size, map_id;
	u64 map_id_full;

	अगर (len < माप(काष्ठा cmsg_bpf_event))
		वापस -EINVAL;

	pkt_size = be32_to_cpu(cbe->pkt_size);
	data_size = be32_to_cpu(cbe->data_size);
	map_id_full = be64_to_cpu(cbe->map_ptr);
	map_id = map_id_full;

	अगर (len < माप(काष्ठा cmsg_bpf_event) + pkt_size + data_size)
		वापस -EINVAL;
	अगर (cbe->hdr.ver != NFP_CCM_ABI_VERSION)
		वापस -EINVAL;

	rcu_पढ़ो_lock();
	record = rhashtable_lookup(&bpf->maps_neutral, &map_id,
				   nfp_bpf_maps_neutral_params);
	अगर (!record || map_id_full > U32_MAX) अणु
		rcu_पढ़ो_unlock();
		cmsg_warn(bpf, "perf event: map id %lld (0x%llx) not recognized, dropping event\n",
			  map_id_full, map_id_full);
		वापस -EINVAL;
	पूर्ण

	bpf_event_output(record->ptr, be32_to_cpu(cbe->cpu_id),
			 &cbe->data[round_up(pkt_size, 4)], data_size,
			 cbe->data, pkt_size, nfp_bpf_perf_event_copy);
	rcu_पढ़ो_unlock();

	वापस 0;
पूर्ण

अटल पूर्णांक
nfp_net_bpf_load(काष्ठा nfp_net *nn, काष्ठा bpf_prog *prog,
		 काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा nfp_prog *nfp_prog = prog->aux->offload->dev_priv;
	अचिन्हित पूर्णांक fw_mtu, pkt_off, max_stack, max_prog_len;
	dma_addr_t dma_addr;
	व्योम *img;
	पूर्णांक err;

	fw_mtu = nn_पढ़ोb(nn, NFP_NET_CFG_BPF_INL_MTU) * 64 - 32;
	pkt_off = min(prog->aux->max_pkt_offset, nn->dp.netdev->mtu);
	अगर (fw_mtu < pkt_off) अणु
		NL_SET_ERR_MSG_MOD(extack, "BPF offload not supported with potential packet access beyond HW packet split boundary");
		वापस -EOPNOTSUPP;
	पूर्ण

	max_stack = nn_पढ़ोb(nn, NFP_NET_CFG_BPF_STACK_SZ) * 64;
	अगर (nfp_prog->stack_size > max_stack) अणु
		NL_SET_ERR_MSG_MOD(extack, "stack too large");
		वापस -EOPNOTSUPP;
	पूर्ण

	max_prog_len = nn_पढ़ोw(nn, NFP_NET_CFG_BPF_MAX_LEN);
	अगर (nfp_prog->prog_len > max_prog_len) अणु
		NL_SET_ERR_MSG_MOD(extack, "program too long");
		वापस -EOPNOTSUPP;
	पूर्ण

	img = nfp_bpf_relo_क्रम_vnic(nfp_prog, nn->app_priv);
	अगर (IS_ERR(img))
		वापस PTR_ERR(img);

	dma_addr = dma_map_single(nn->dp.dev, img,
				  nfp_prog->prog_len * माप(u64),
				  DMA_TO_DEVICE);
	अगर (dma_mapping_error(nn->dp.dev, dma_addr)) अणु
		kमुक्त(img);
		वापस -ENOMEM;
	पूर्ण

	nn_ग_लिखोw(nn, NFP_NET_CFG_BPF_SIZE, nfp_prog->prog_len);
	nn_ग_लिखोq(nn, NFP_NET_CFG_BPF_ADDR, dma_addr);

	/* Load up the JITed code */
	err = nfp_net_reconfig(nn, NFP_NET_CFG_UPDATE_BPF);
	अगर (err)
		NL_SET_ERR_MSG_MOD(extack,
				   "FW command error while loading BPF");

	dma_unmap_single(nn->dp.dev, dma_addr, nfp_prog->prog_len * माप(u64),
			 DMA_TO_DEVICE);
	kमुक्त(img);

	वापस err;
पूर्ण

अटल व्योम
nfp_net_bpf_start(काष्ठा nfp_net *nn, काष्ठा netlink_ext_ack *extack)
अणु
	पूर्णांक err;

	/* Enable passing packets through BPF function */
	nn->dp.ctrl |= NFP_NET_CFG_CTRL_BPF;
	nn_ग_लिखोl(nn, NFP_NET_CFG_CTRL, nn->dp.ctrl);
	err = nfp_net_reconfig(nn, NFP_NET_CFG_UPDATE_GEN);
	अगर (err)
		NL_SET_ERR_MSG_MOD(extack,
				   "FW command error while enabling BPF");
पूर्ण

अटल पूर्णांक nfp_net_bpf_stop(काष्ठा nfp_net *nn)
अणु
	अगर (!(nn->dp.ctrl & NFP_NET_CFG_CTRL_BPF))
		वापस 0;

	nn->dp.ctrl &= ~NFP_NET_CFG_CTRL_BPF;
	nn_ग_लिखोl(nn, NFP_NET_CFG_CTRL, nn->dp.ctrl);

	वापस nfp_net_reconfig(nn, NFP_NET_CFG_UPDATE_GEN);
पूर्ण

पूर्णांक nfp_net_bpf_offload(काष्ठा nfp_net *nn, काष्ठा bpf_prog *prog,
			bool old_prog, काष्ठा netlink_ext_ack *extack)
अणु
	पूर्णांक err;

	अगर (prog && !bpf_offload_dev_match(prog, nn->dp.netdev))
		वापस -EINVAL;

	अगर (prog && old_prog) अणु
		u8 cap;

		cap = nn_पढ़ोb(nn, NFP_NET_CFG_BPF_CAP);
		अगर (!(cap & NFP_NET_BPF_CAP_RELO)) अणु
			NL_SET_ERR_MSG_MOD(extack,
					   "FW does not support live reload");
			वापस -EBUSY;
		पूर्ण
	पूर्ण

	/* Something अन्यथा is loaded, dअगरferent program type? */
	अगर (!old_prog && nn->dp.ctrl & NFP_NET_CFG_CTRL_BPF)
		वापस -EBUSY;

	अगर (old_prog && !prog)
		वापस nfp_net_bpf_stop(nn);

	err = nfp_net_bpf_load(nn, prog, extack);
	अगर (err)
		वापस err;

	अगर (!old_prog)
		nfp_net_bpf_start(nn, extack);

	वापस 0;
पूर्ण

स्थिर काष्ठा bpf_prog_offload_ops nfp_bpf_dev_ops = अणु
	.insn_hook	= nfp_verअगरy_insn,
	.finalize	= nfp_bpf_finalize,
	.replace_insn	= nfp_bpf_opt_replace_insn,
	.हटाओ_insns	= nfp_bpf_opt_हटाओ_insns,
	.prepare	= nfp_bpf_verअगरier_prep,
	.translate	= nfp_bpf_translate,
	.destroy	= nfp_bpf_destroy,
पूर्ण;
