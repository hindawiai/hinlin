<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB
/* Copyright (c) 2020 Mellanox Technologies Ltd. */

#समावेश <linux/vdpa.h>
#समावेश <linux/gcd.h>
#समावेश <linux/माला.स>
#समावेश <linux/mlx5/qp.h>
#समावेश "mlx5_vdpa.h"

/* DIV_ROUND_UP where the भागider is a घातer of 2 give by its log base 2 value */
#घोषणा MLX5_DIV_ROUND_UP_POW2(_n, _s) \
(अणु \
	u64 __s = _s; \
	u64 _res; \
	_res = (((_n) + (1 << (__s)) - 1) >> (__s)); \
	_res; \
पूर्ण)

अटल पूर्णांक get_octo_len(u64 len, पूर्णांक page_shअगरt)
अणु
	u64 page_size = 1ULL << page_shअगरt;
	पूर्णांक npages;

	npages = ALIGN(len, page_size) >> page_shअगरt;
	वापस (npages + 1) / 2;
पूर्ण

अटल व्योम mlx5_set_access_mode(व्योम *mkc, पूर्णांक mode)
अणु
	MLX5_SET(mkc, mkc, access_mode_1_0, mode & 0x3);
	MLX5_SET(mkc, mkc, access_mode_4_2, mode >> 2);
पूर्ण

अटल व्योम populate_mtts(काष्ठा mlx5_vdpa_direct_mr *mr, __be64 *mtt)
अणु
	काष्ठा scatterlist *sg;
	पूर्णांक nsg = mr->nsg;
	u64 dma_addr;
	u64 dma_len;
	पूर्णांक j = 0;
	पूर्णांक i;

	क्रम_each_sg(mr->sg_head.sgl, sg, mr->nent, i) अणु
		क्रम (dma_addr = sg_dma_address(sg), dma_len = sg_dma_len(sg);
		     nsg && dma_len;
		     nsg--, dma_addr += BIT(mr->log_size), dma_len -= BIT(mr->log_size))
			mtt[j++] = cpu_to_be64(dma_addr);
	पूर्ण
पूर्ण

अटल पूर्णांक create_direct_mr(काष्ठा mlx5_vdpa_dev *mvdev, काष्ठा mlx5_vdpa_direct_mr *mr)
अणु
	पूर्णांक inlen;
	व्योम *mkc;
	व्योम *in;
	पूर्णांक err;

	inlen = MLX5_ST_SZ_BYTES(create_mkey_in) + roundup(MLX5_ST_SZ_BYTES(mtt) * mr->nsg, 16);
	in = kvzalloc(inlen, GFP_KERNEL);
	अगर (!in)
		वापस -ENOMEM;

	MLX5_SET(create_mkey_in, in, uid, mvdev->res.uid);
	mkc = MLX5_ADDR_OF(create_mkey_in, in, memory_key_mkey_entry);
	MLX5_SET(mkc, mkc, lw, !!(mr->perm & VHOST_MAP_WO));
	MLX5_SET(mkc, mkc, lr, !!(mr->perm & VHOST_MAP_RO));
	mlx5_set_access_mode(mkc, MLX5_MKC_ACCESS_MODE_MTT);
	MLX5_SET(mkc, mkc, qpn, 0xffffff);
	MLX5_SET(mkc, mkc, pd, mvdev->res.pdn);
	MLX5_SET64(mkc, mkc, start_addr, mr->offset);
	MLX5_SET64(mkc, mkc, len, mr->end - mr->start);
	MLX5_SET(mkc, mkc, log_page_size, mr->log_size);
	MLX5_SET(mkc, mkc, translations_octword_size,
		 get_octo_len(mr->end - mr->start, mr->log_size));
	MLX5_SET(create_mkey_in, in, translations_octword_actual_size,
		 get_octo_len(mr->end - mr->start, mr->log_size));
	populate_mtts(mr, MLX5_ADDR_OF(create_mkey_in, in, klm_pas_mtt));
	err = mlx5_vdpa_create_mkey(mvdev, &mr->mr, in, inlen);
	kvमुक्त(in);
	अगर (err) अणु
		mlx5_vdpa_warn(mvdev, "Failed to create direct MR\n");
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम destroy_direct_mr(काष्ठा mlx5_vdpa_dev *mvdev, काष्ठा mlx5_vdpa_direct_mr *mr)
अणु
	mlx5_vdpa_destroy_mkey(mvdev, &mr->mr);
पूर्ण

अटल u64 map_start(काष्ठा vhost_iotlb_map *map, काष्ठा mlx5_vdpa_direct_mr *mr)
अणु
	वापस max_t(u64, map->start, mr->start);
पूर्ण

अटल u64 map_end(काष्ठा vhost_iotlb_map *map, काष्ठा mlx5_vdpa_direct_mr *mr)
अणु
	वापस min_t(u64, map->last + 1, mr->end);
पूर्ण

अटल u64 maplen(काष्ठा vhost_iotlb_map *map, काष्ठा mlx5_vdpa_direct_mr *mr)
अणु
	वापस map_end(map, mr) - map_start(map, mr);
पूर्ण

#घोषणा MLX5_VDPA_INVALID_START_ADDR ((u64)-1)
#घोषणा MLX5_VDPA_INVALID_LEN ((u64)-1)

अटल u64 indir_start_addr(काष्ठा mlx5_vdpa_mr *mkey)
अणु
	काष्ठा mlx5_vdpa_direct_mr *s;

	s = list_first_entry_or_null(&mkey->head, काष्ठा mlx5_vdpa_direct_mr, list);
	अगर (!s)
		वापस MLX5_VDPA_INVALID_START_ADDR;

	वापस s->start;
पूर्ण

अटल u64 indir_len(काष्ठा mlx5_vdpa_mr *mkey)
अणु
	काष्ठा mlx5_vdpa_direct_mr *s;
	काष्ठा mlx5_vdpa_direct_mr *e;

	s = list_first_entry_or_null(&mkey->head, काष्ठा mlx5_vdpa_direct_mr, list);
	अगर (!s)
		वापस MLX5_VDPA_INVALID_LEN;

	e = list_last_entry(&mkey->head, काष्ठा mlx5_vdpa_direct_mr, list);

	वापस e->end - s->start;
पूर्ण

#घोषणा LOG_MAX_KLM_SIZE 30
#घोषणा MAX_KLM_SIZE BIT(LOG_MAX_KLM_SIZE)

अटल u32 klm_bcount(u64 size)
अणु
	वापस (u32)size;
पूर्ण

अटल व्योम fill_indir(काष्ठा mlx5_vdpa_dev *mvdev, काष्ठा mlx5_vdpa_mr *mkey, व्योम *in)
अणु
	काष्ठा mlx5_vdpa_direct_mr *dmr;
	काष्ठा mlx5_klm *klmarr;
	काष्ठा mlx5_klm *klm;
	bool first = true;
	u64 preve;
	पूर्णांक i;

	klmarr = MLX5_ADDR_OF(create_mkey_in, in, klm_pas_mtt);
	i = 0;
	list_क्रम_each_entry(dmr, &mkey->head, list) अणु
again:
		klm = &klmarr[i++];
		अगर (first) अणु
			preve = dmr->start;
			first = false;
		पूर्ण

		अगर (preve == dmr->start) अणु
			klm->key = cpu_to_be32(dmr->mr.key);
			klm->bcount = cpu_to_be32(klm_bcount(dmr->end - dmr->start));
			preve = dmr->end;
		पूर्ण अन्यथा अणु
			klm->key = cpu_to_be32(mvdev->res.null_mkey);
			klm->bcount = cpu_to_be32(klm_bcount(dmr->start - preve));
			preve = dmr->start;
			जाओ again;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक klm_byte_size(पूर्णांक nklms)
अणु
	वापस 16 * ALIGN(nklms, 4);
पूर्ण

अटल पूर्णांक create_indirect_key(काष्ठा mlx5_vdpa_dev *mvdev, काष्ठा mlx5_vdpa_mr *mr)
अणु
	पूर्णांक inlen;
	व्योम *mkc;
	व्योम *in;
	पूर्णांक err;
	u64 start;
	u64 len;

	start = indir_start_addr(mr);
	len = indir_len(mr);
	अगर (start == MLX5_VDPA_INVALID_START_ADDR || len == MLX5_VDPA_INVALID_LEN)
		वापस -EINVAL;

	inlen = MLX5_ST_SZ_BYTES(create_mkey_in) + klm_byte_size(mr->num_klms);
	in = kzalloc(inlen, GFP_KERNEL);
	अगर (!in)
		वापस -ENOMEM;

	MLX5_SET(create_mkey_in, in, uid, mvdev->res.uid);
	mkc = MLX5_ADDR_OF(create_mkey_in, in, memory_key_mkey_entry);
	MLX5_SET(mkc, mkc, lw, 1);
	MLX5_SET(mkc, mkc, lr, 1);
	mlx5_set_access_mode(mkc, MLX5_MKC_ACCESS_MODE_KLMS);
	MLX5_SET(mkc, mkc, qpn, 0xffffff);
	MLX5_SET(mkc, mkc, pd, mvdev->res.pdn);
	MLX5_SET64(mkc, mkc, start_addr, start);
	MLX5_SET64(mkc, mkc, len, len);
	MLX5_SET(mkc, mkc, translations_octword_size, klm_byte_size(mr->num_klms) / 16);
	MLX5_SET(create_mkey_in, in, translations_octword_actual_size, mr->num_klms);
	fill_indir(mvdev, mr, in);
	err = mlx5_vdpa_create_mkey(mvdev, &mr->mkey, in, inlen);
	kमुक्त(in);
	वापस err;
पूर्ण

अटल व्योम destroy_indirect_key(काष्ठा mlx5_vdpa_dev *mvdev, काष्ठा mlx5_vdpa_mr *mkey)
अणु
	mlx5_vdpa_destroy_mkey(mvdev, &mkey->mkey);
पूर्ण

अटल काष्ठा device *get_dma_device(काष्ठा mlx5_vdpa_dev *mvdev)
अणु
	वापस &mvdev->mdev->pdev->dev;
पूर्ण

अटल पूर्णांक map_direct_mr(काष्ठा mlx5_vdpa_dev *mvdev, काष्ठा mlx5_vdpa_direct_mr *mr,
			 काष्ठा vhost_iotlb *iotlb)
अणु
	काष्ठा vhost_iotlb_map *map;
	अचिन्हित दीर्घ lgcd = 0;
	पूर्णांक log_entity_size;
	अचिन्हित दीर्घ size;
	u64 start = 0;
	पूर्णांक err;
	काष्ठा page *pg;
	अचिन्हित पूर्णांक nsg;
	पूर्णांक sglen;
	u64 pa;
	u64 paend;
	काष्ठा scatterlist *sg;
	काष्ठा device *dma = get_dma_device(mvdev);

	क्रम (map = vhost_iotlb_itree_first(iotlb, mr->start, mr->end - 1);
	     map; map = vhost_iotlb_itree_next(map, start, mr->end - 1)) अणु
		size = maplen(map, mr);
		lgcd = gcd(lgcd, size);
		start += size;
	पूर्ण
	log_entity_size = ilog2(lgcd);

	sglen = 1 << log_entity_size;
	nsg = MLX5_DIV_ROUND_UP_POW2(mr->end - mr->start, log_entity_size);

	err = sg_alloc_table(&mr->sg_head, nsg, GFP_KERNEL);
	अगर (err)
		वापस err;

	sg = mr->sg_head.sgl;
	क्रम (map = vhost_iotlb_itree_first(iotlb, mr->start, mr->end - 1);
	     map; map = vhost_iotlb_itree_next(map, mr->start, mr->end - 1)) अणु
		paend = map->addr + maplen(map, mr);
		क्रम (pa = map->addr; pa < paend; pa += sglen) अणु
			pg = pfn_to_page(__phys_to_pfn(pa));
			अगर (!sg) अणु
				mlx5_vdpa_warn(mvdev, "sg null. start 0x%llx, end 0x%llx\n",
					       map->start, map->last + 1);
				err = -ENOMEM;
				जाओ err_map;
			पूर्ण
			sg_set_page(sg, pg, sglen, 0);
			sg = sg_next(sg);
			अगर (!sg)
				जाओ करोne;
		पूर्ण
	पूर्ण
करोne:
	mr->log_size = log_entity_size;
	mr->nsg = nsg;
	mr->nent = dma_map_sg_attrs(dma, mr->sg_head.sgl, mr->nsg, DMA_BIसूचीECTIONAL, 0);
	अगर (!mr->nent) अणु
		err = -ENOMEM;
		जाओ err_map;
	पूर्ण

	err = create_direct_mr(mvdev, mr);
	अगर (err)
		जाओ err_direct;

	वापस 0;

err_direct:
	dma_unmap_sg_attrs(dma, mr->sg_head.sgl, mr->nsg, DMA_BIसूचीECTIONAL, 0);
err_map:
	sg_मुक्त_table(&mr->sg_head);
	वापस err;
पूर्ण

अटल व्योम unmap_direct_mr(काष्ठा mlx5_vdpa_dev *mvdev, काष्ठा mlx5_vdpa_direct_mr *mr)
अणु
	काष्ठा device *dma = get_dma_device(mvdev);

	destroy_direct_mr(mvdev, mr);
	dma_unmap_sg_attrs(dma, mr->sg_head.sgl, mr->nsg, DMA_BIसूचीECTIONAL, 0);
	sg_मुक्त_table(&mr->sg_head);
पूर्ण

अटल पूर्णांक add_direct_chain(काष्ठा mlx5_vdpa_dev *mvdev, u64 start, u64 size, u8 perm,
			    काष्ठा vhost_iotlb *iotlb)
अणु
	काष्ठा mlx5_vdpa_mr *mr = &mvdev->mr;
	काष्ठा mlx5_vdpa_direct_mr *dmr;
	काष्ठा mlx5_vdpa_direct_mr *n;
	LIST_HEAD(पंचांगp);
	u64 st;
	u64 sz;
	पूर्णांक err;
	पूर्णांक i = 0;

	st = start;
	जबतक (size) अणु
		sz = (u32)min_t(u64, MAX_KLM_SIZE, size);
		dmr = kzalloc(माप(*dmr), GFP_KERNEL);
		अगर (!dmr) अणु
			err = -ENOMEM;
			जाओ err_alloc;
		पूर्ण

		dmr->start = st;
		dmr->end = st + sz;
		dmr->perm = perm;
		err = map_direct_mr(mvdev, dmr, iotlb);
		अगर (err) अणु
			kमुक्त(dmr);
			जाओ err_alloc;
		पूर्ण

		list_add_tail(&dmr->list, &पंचांगp);
		size -= sz;
		mr->num_directs++;
		mr->num_klms++;
		st += sz;
		i++;
	पूर्ण
	list_splice_tail(&पंचांगp, &mr->head);
	वापस 0;

err_alloc:
	list_क्रम_each_entry_safe(dmr, n, &mr->head, list) अणु
		list_del_init(&dmr->list);
		unmap_direct_mr(mvdev, dmr);
		kमुक्त(dmr);
	पूर्ण
	वापस err;
पूर्ण

/* The iotlb poपूर्णांकer contains a list of maps. Go over the maps, possibly
 * merging mergeable maps, and create direct memory keys that provide the
 * device access to memory. The direct mkeys are then referred to by the
 * indirect memory key that provides access to the enitre address space given
 * by iotlb.
 */
अटल पूर्णांक _mlx5_vdpa_create_mr(काष्ठा mlx5_vdpa_dev *mvdev, काष्ठा vhost_iotlb *iotlb)
अणु
	काष्ठा mlx5_vdpa_mr *mr = &mvdev->mr;
	काष्ठा mlx5_vdpa_direct_mr *dmr;
	काष्ठा mlx5_vdpa_direct_mr *n;
	काष्ठा vhost_iotlb_map *map;
	u32 pperm = U16_MAX;
	u64 last = U64_MAX;
	u64 ps = U64_MAX;
	u64 pe = U64_MAX;
	u64 start = 0;
	पूर्णांक err = 0;
	पूर्णांक nnuls;

	अगर (mr->initialized)
		वापस 0;

	INIT_LIST_HEAD(&mr->head);
	क्रम (map = vhost_iotlb_itree_first(iotlb, start, last); map;
	     map = vhost_iotlb_itree_next(map, start, last)) अणु
		start = map->start;
		अगर (pe == map->start && pperm == map->perm) अणु
			pe = map->last + 1;
		पूर्ण अन्यथा अणु
			अगर (ps != U64_MAX) अणु
				अगर (pe < map->start) अणु
					/* We have a hole in the map. Check how
					 * many null keys are required to fill it.
					 */
					nnuls = MLX5_DIV_ROUND_UP_POW2(map->start - pe,
								       LOG_MAX_KLM_SIZE);
					mr->num_klms += nnuls;
				पूर्ण
				err = add_direct_chain(mvdev, ps, pe - ps, pperm, iotlb);
				अगर (err)
					जाओ err_chain;
			पूर्ण
			ps = map->start;
			pe = map->last + 1;
			pperm = map->perm;
		पूर्ण
	पूर्ण
	err = add_direct_chain(mvdev, ps, pe - ps, pperm, iotlb);
	अगर (err)
		जाओ err_chain;

	/* Create the memory key that defines the guests's address space. This
	 * memory key refers to the direct keys that contain the MTT
	 * translations
	 */
	err = create_indirect_key(mvdev, mr);
	अगर (err)
		जाओ err_chain;

	mr->initialized = true;
	वापस 0;

err_chain:
	list_क्रम_each_entry_safe_reverse(dmr, n, &mr->head, list) अणु
		list_del_init(&dmr->list);
		unmap_direct_mr(mvdev, dmr);
		kमुक्त(dmr);
	पूर्ण
	वापस err;
पूर्ण

पूर्णांक mlx5_vdpa_create_mr(काष्ठा mlx5_vdpa_dev *mvdev, काष्ठा vhost_iotlb *iotlb)
अणु
	काष्ठा mlx5_vdpa_mr *mr = &mvdev->mr;
	पूर्णांक err;

	mutex_lock(&mr->mkey_mtx);
	err = _mlx5_vdpa_create_mr(mvdev, iotlb);
	mutex_unlock(&mr->mkey_mtx);
	वापस err;
पूर्ण

व्योम mlx5_vdpa_destroy_mr(काष्ठा mlx5_vdpa_dev *mvdev)
अणु
	काष्ठा mlx5_vdpa_mr *mr = &mvdev->mr;
	काष्ठा mlx5_vdpa_direct_mr *dmr;
	काष्ठा mlx5_vdpa_direct_mr *n;

	mutex_lock(&mr->mkey_mtx);
	अगर (!mr->initialized)
		जाओ out;

	destroy_indirect_key(mvdev, mr);
	list_क्रम_each_entry_safe_reverse(dmr, n, &mr->head, list) अणु
		list_del_init(&dmr->list);
		unmap_direct_mr(mvdev, dmr);
		kमुक्त(dmr);
	पूर्ण
	स_रखो(mr, 0, माप(*mr));
	mr->initialized = false;
out:
	mutex_unlock(&mr->mkey_mtx);
पूर्ण

अटल bool map_empty(काष्ठा vhost_iotlb *iotlb)
अणु
	वापस !vhost_iotlb_itree_first(iotlb, 0, U64_MAX);
पूर्ण

पूर्णांक mlx5_vdpa_handle_set_map(काष्ठा mlx5_vdpa_dev *mvdev, काष्ठा vhost_iotlb *iotlb,
			     bool *change_map)
अणु
	काष्ठा mlx5_vdpa_mr *mr = &mvdev->mr;
	पूर्णांक err = 0;

	*change_map = false;
	अगर (map_empty(iotlb)) अणु
		mlx5_vdpa_destroy_mr(mvdev);
		वापस 0;
	पूर्ण
	mutex_lock(&mr->mkey_mtx);
	अगर (mr->initialized) अणु
		mlx5_vdpa_info(mvdev, "memory map update\n");
		*change_map = true;
	पूर्ण
	अगर (!*change_map)
		err = _mlx5_vdpa_create_mr(mvdev, iotlb);
	mutex_unlock(&mr->mkey_mtx);

	वापस err;
पूर्ण
