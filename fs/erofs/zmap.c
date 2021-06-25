<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2018-2019 HUAWEI, Inc.
 *             https://www.huawei.com/
 * Created by Gao Xiang <gaoxiang25@huawei.com>
 */
#समावेश "internal.h"
#समावेश <यंत्र/unaligned.h>
#समावेश <trace/events/erofs.h>

पूर्णांक z_erofs_fill_inode(काष्ठा inode *inode)
अणु
	काष्ठा erofs_inode *स्थिर vi = EROFS_I(inode);
	काष्ठा erofs_sb_info *sbi = EROFS_SB(inode->i_sb);

	अगर (!erofs_sb_has_big_pcluster(sbi) &&
	    vi->datalayout == EROFS_INODE_FLAT_COMPRESSION_LEGACY) अणु
		vi->z_advise = 0;
		vi->z_algorithmtype[0] = 0;
		vi->z_algorithmtype[1] = 0;
		vi->z_logical_clusterbits = LOG_BLOCK_SIZE;
		set_bit(EROFS_I_Z_INITED_BIT, &vi->flags);
	पूर्ण
	inode->i_mapping->a_ops = &z_erofs_aops;
	वापस 0;
पूर्ण

अटल पूर्णांक z_erofs_fill_inode_lazy(काष्ठा inode *inode)
अणु
	काष्ठा erofs_inode *स्थिर vi = EROFS_I(inode);
	काष्ठा super_block *स्थिर sb = inode->i_sb;
	पूर्णांक err;
	erofs_off_t pos;
	काष्ठा page *page;
	व्योम *kaddr;
	काष्ठा z_erofs_map_header *h;

	अगर (test_bit(EROFS_I_Z_INITED_BIT, &vi->flags)) अणु
		/*
		 * paired with smp_mb() at the end of the function to ensure
		 * fields will only be observed after the bit is set.
		 */
		smp_mb();
		वापस 0;
	पूर्ण

	अगर (रुको_on_bit_lock(&vi->flags, EROFS_I_BL_Z_BIT, TASK_KILLABLE))
		वापस -ERESTARTSYS;

	err = 0;
	अगर (test_bit(EROFS_I_Z_INITED_BIT, &vi->flags))
		जाओ out_unlock;

	DBG_BUGON(!erofs_sb_has_big_pcluster(EROFS_SB(sb)) &&
		  vi->datalayout == EROFS_INODE_FLAT_COMPRESSION_LEGACY);

	pos = ALIGN(iloc(EROFS_SB(sb), vi->nid) + vi->inode_isize +
		    vi->xattr_isize, 8);
	page = erofs_get_meta_page(sb, erofs_blknr(pos));
	अगर (IS_ERR(page)) अणु
		err = PTR_ERR(page);
		जाओ out_unlock;
	पूर्ण

	kaddr = kmap_atomic(page);

	h = kaddr + erofs_blkoff(pos);
	vi->z_advise = le16_to_cpu(h->h_advise);
	vi->z_algorithmtype[0] = h->h_algorithmtype & 15;
	vi->z_algorithmtype[1] = h->h_algorithmtype >> 4;

	अगर (vi->z_algorithmtype[0] >= Z_EROFS_COMPRESSION_MAX) अणु
		erofs_err(sb, "unknown compression format %u for nid %llu, please upgrade kernel",
			  vi->z_algorithmtype[0], vi->nid);
		err = -EOPNOTSUPP;
		जाओ unmap_करोne;
	पूर्ण

	vi->z_logical_clusterbits = LOG_BLOCK_SIZE + (h->h_clusterbits & 7);
	अगर (!erofs_sb_has_big_pcluster(EROFS_SB(sb)) &&
	    vi->z_advise & (Z_EROFS_ADVISE_BIG_PCLUSTER_1 |
			    Z_EROFS_ADVISE_BIG_PCLUSTER_2)) अणु
		erofs_err(sb, "per-inode big pcluster without sb feature for nid %llu",
			  vi->nid);
		err = -EFSCORRUPTED;
		जाओ unmap_करोne;
	पूर्ण
	अगर (vi->datalayout == EROFS_INODE_FLAT_COMPRESSION &&
	    !(vi->z_advise & Z_EROFS_ADVISE_BIG_PCLUSTER_1) ^
	    !(vi->z_advise & Z_EROFS_ADVISE_BIG_PCLUSTER_2)) अणु
		erofs_err(sb, "big pcluster head1/2 of compact indexes should be consistent for nid %llu",
			  vi->nid);
		err = -EFSCORRUPTED;
		जाओ unmap_करोne;
	पूर्ण
	/* paired with smp_mb() at the beginning of the function */
	smp_mb();
	set_bit(EROFS_I_Z_INITED_BIT, &vi->flags);
unmap_करोne:
	kunmap_atomic(kaddr);
	unlock_page(page);
	put_page(page);
out_unlock:
	clear_and_wake_up_bit(EROFS_I_BL_Z_BIT, &vi->flags);
	वापस err;
पूर्ण

काष्ठा z_erofs_maprecorder अणु
	काष्ठा inode *inode;
	काष्ठा erofs_map_blocks *map;
	व्योम *kaddr;

	अचिन्हित दीर्घ lcn;
	/* compression extent inक्रमmation gathered */
	u8  type;
	u16 clusterofs;
	u16 delta[2];
	erofs_blk_t pblk, compressedlcs;
पूर्ण;

अटल पूर्णांक z_erofs_reload_indexes(काष्ठा z_erofs_maprecorder *m,
				  erofs_blk_t eblk)
अणु
	काष्ठा super_block *स्थिर sb = m->inode->i_sb;
	काष्ठा erofs_map_blocks *स्थिर map = m->map;
	काष्ठा page *mpage = map->mpage;

	अगर (mpage) अणु
		अगर (mpage->index == eblk) अणु
			अगर (!m->kaddr)
				m->kaddr = kmap_atomic(mpage);
			वापस 0;
		पूर्ण

		अगर (m->kaddr) अणु
			kunmap_atomic(m->kaddr);
			m->kaddr = शून्य;
		पूर्ण
		put_page(mpage);
	पूर्ण

	mpage = erofs_get_meta_page(sb, eblk);
	अगर (IS_ERR(mpage)) अणु
		map->mpage = शून्य;
		वापस PTR_ERR(mpage);
	पूर्ण
	m->kaddr = kmap_atomic(mpage);
	unlock_page(mpage);
	map->mpage = mpage;
	वापस 0;
पूर्ण

अटल पूर्णांक legacy_load_cluster_from_disk(काष्ठा z_erofs_maprecorder *m,
					 अचिन्हित दीर्घ lcn)
अणु
	काष्ठा inode *स्थिर inode = m->inode;
	काष्ठा erofs_inode *स्थिर vi = EROFS_I(inode);
	स्थिर erofs_off_t ibase = iloc(EROFS_I_SB(inode), vi->nid);
	स्थिर erofs_off_t pos =
		Z_EROFS_VLE_LEGACY_INDEX_ALIGN(ibase + vi->inode_isize +
					       vi->xattr_isize) +
		lcn * माप(काष्ठा z_erofs_vle_decompressed_index);
	काष्ठा z_erofs_vle_decompressed_index *di;
	अचिन्हित पूर्णांक advise, type;
	पूर्णांक err;

	err = z_erofs_reload_indexes(m, erofs_blknr(pos));
	अगर (err)
		वापस err;

	m->lcn = lcn;
	di = m->kaddr + erofs_blkoff(pos);

	advise = le16_to_cpu(di->di_advise);
	type = (advise >> Z_EROFS_VLE_DI_CLUSTER_TYPE_BIT) &
		((1 << Z_EROFS_VLE_DI_CLUSTER_TYPE_BITS) - 1);
	चयन (type) अणु
	हाल Z_EROFS_VLE_CLUSTER_TYPE_NONHEAD:
		m->clusterofs = 1 << vi->z_logical_clusterbits;
		m->delta[0] = le16_to_cpu(di->di_u.delta[0]);
		अगर (m->delta[0] & Z_EROFS_VLE_DI_D0_CBLKCNT) अणु
			अगर (!(vi->z_advise & Z_EROFS_ADVISE_BIG_PCLUSTER_1)) अणु
				DBG_BUGON(1);
				वापस -EFSCORRUPTED;
			पूर्ण
			m->compressedlcs = m->delta[0] &
				~Z_EROFS_VLE_DI_D0_CBLKCNT;
			m->delta[0] = 1;
		पूर्ण
		m->delta[1] = le16_to_cpu(di->di_u.delta[1]);
		अवरोध;
	हाल Z_EROFS_VLE_CLUSTER_TYPE_PLAIN:
	हाल Z_EROFS_VLE_CLUSTER_TYPE_HEAD:
		m->clusterofs = le16_to_cpu(di->di_clusterofs);
		m->pblk = le32_to_cpu(di->di_u.blkaddr);
		अवरोध;
	शेष:
		DBG_BUGON(1);
		वापस -EOPNOTSUPP;
	पूर्ण
	m->type = type;
	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक decode_compactedbits(अचिन्हित पूर्णांक lobits,
					 अचिन्हित पूर्णांक lomask,
					 u8 *in, अचिन्हित पूर्णांक pos, u8 *type)
अणु
	स्थिर अचिन्हित पूर्णांक v = get_unaligned_le32(in + pos / 8) >> (pos & 7);
	स्थिर अचिन्हित पूर्णांक lo = v & lomask;

	*type = (v >> lobits) & 3;
	वापस lo;
पूर्ण

अटल पूर्णांक unpack_compacted_index(काष्ठा z_erofs_maprecorder *m,
				  अचिन्हित पूर्णांक amortizedshअगरt,
				  अचिन्हित पूर्णांक eofs)
अणु
	काष्ठा erofs_inode *स्थिर vi = EROFS_I(m->inode);
	स्थिर अचिन्हित पूर्णांक lclusterbits = vi->z_logical_clusterbits;
	स्थिर अचिन्हित पूर्णांक lomask = (1 << lclusterbits) - 1;
	अचिन्हित पूर्णांक vcnt, base, lo, encodebits, nblk;
	पूर्णांक i;
	u8 *in, type;
	bool big_pcluster;

	अगर (1 << amortizedshअगरt == 4)
		vcnt = 2;
	अन्यथा अगर (1 << amortizedshअगरt == 2 && lclusterbits == 12)
		vcnt = 16;
	अन्यथा
		वापस -EOPNOTSUPP;

	big_pcluster = vi->z_advise & Z_EROFS_ADVISE_BIG_PCLUSTER_1;
	encodebits = ((vcnt << amortizedshअगरt) - माप(__le32)) * 8 / vcnt;
	base = round_करोwn(eofs, vcnt << amortizedshअगरt);
	in = m->kaddr + base;

	i = (eofs - base) >> amortizedshअगरt;

	lo = decode_compactedbits(lclusterbits, lomask,
				  in, encodebits * i, &type);
	m->type = type;
	अगर (type == Z_EROFS_VLE_CLUSTER_TYPE_NONHEAD) अणु
		m->clusterofs = 1 << lclusterbits;
		अगर (lo & Z_EROFS_VLE_DI_D0_CBLKCNT) अणु
			अगर (!big_pcluster) अणु
				DBG_BUGON(1);
				वापस -EFSCORRUPTED;
			पूर्ण
			m->compressedlcs = lo & ~Z_EROFS_VLE_DI_D0_CBLKCNT;
			m->delta[0] = 1;
			वापस 0;
		पूर्ण अन्यथा अगर (i + 1 != (पूर्णांक)vcnt) अणु
			m->delta[0] = lo;
			वापस 0;
		पूर्ण
		/*
		 * since the last lcluster in the pack is special,
		 * of which lo saves delta[1] rather than delta[0].
		 * Hence, get delta[0] by the previous lcluster indirectly.
		 */
		lo = decode_compactedbits(lclusterbits, lomask,
					  in, encodebits * (i - 1), &type);
		अगर (type != Z_EROFS_VLE_CLUSTER_TYPE_NONHEAD)
			lo = 0;
		अन्यथा अगर (lo & Z_EROFS_VLE_DI_D0_CBLKCNT)
			lo = 1;
		m->delta[0] = lo + 1;
		वापस 0;
	पूर्ण
	m->clusterofs = lo;
	m->delta[0] = 0;
	/* figout out blkaddr (pblk) क्रम HEAD lclusters */
	अगर (!big_pcluster) अणु
		nblk = 1;
		जबतक (i > 0) अणु
			--i;
			lo = decode_compactedbits(lclusterbits, lomask,
						  in, encodebits * i, &type);
			अगर (type == Z_EROFS_VLE_CLUSTER_TYPE_NONHEAD)
				i -= lo;

			अगर (i >= 0)
				++nblk;
		पूर्ण
	पूर्ण अन्यथा अणु
		nblk = 0;
		जबतक (i > 0) अणु
			--i;
			lo = decode_compactedbits(lclusterbits, lomask,
						  in, encodebits * i, &type);
			अगर (type == Z_EROFS_VLE_CLUSTER_TYPE_NONHEAD) अणु
				अगर (lo & Z_EROFS_VLE_DI_D0_CBLKCNT) अणु
					--i;
					nblk += lo & ~Z_EROFS_VLE_DI_D0_CBLKCNT;
					जारी;
				पूर्ण
				/* bigpcluster shouldn't have plain d0 == 1 */
				अगर (lo <= 1) अणु
					DBG_BUGON(1);
					वापस -EFSCORRUPTED;
				पूर्ण
				i -= lo - 2;
				जारी;
			पूर्ण
			++nblk;
		पूर्ण
	पूर्ण
	in += (vcnt << amortizedshअगरt) - माप(__le32);
	m->pblk = le32_to_cpu(*(__le32 *)in) + nblk;
	वापस 0;
पूर्ण

अटल पूर्णांक compacted_load_cluster_from_disk(काष्ठा z_erofs_maprecorder *m,
					    अचिन्हित दीर्घ lcn)
अणु
	काष्ठा inode *स्थिर inode = m->inode;
	काष्ठा erofs_inode *स्थिर vi = EROFS_I(inode);
	स्थिर अचिन्हित पूर्णांक lclusterbits = vi->z_logical_clusterbits;
	स्थिर erofs_off_t ebase = ALIGN(iloc(EROFS_I_SB(inode), vi->nid) +
					vi->inode_isize + vi->xattr_isize, 8) +
		माप(काष्ठा z_erofs_map_header);
	स्थिर अचिन्हित पूर्णांक totalidx = DIV_ROUND_UP(inode->i_size, EROFS_BLKSIZ);
	अचिन्हित पूर्णांक compacted_4b_initial, compacted_2b;
	अचिन्हित पूर्णांक amortizedshअगरt;
	erofs_off_t pos;
	पूर्णांक err;

	अगर (lclusterbits != 12)
		वापस -EOPNOTSUPP;

	अगर (lcn >= totalidx)
		वापस -EINVAL;

	m->lcn = lcn;
	/* used to align to 32-byte (compacted_2b) alignment */
	compacted_4b_initial = (32 - ebase % 32) / 4;
	अगर (compacted_4b_initial == 32 / 4)
		compacted_4b_initial = 0;

	अगर (vi->z_advise & Z_EROFS_ADVISE_COMPACTED_2B)
		compacted_2b = roundकरोwn(totalidx - compacted_4b_initial, 16);
	अन्यथा
		compacted_2b = 0;

	pos = ebase;
	अगर (lcn < compacted_4b_initial) अणु
		amortizedshअगरt = 2;
		जाओ out;
	पूर्ण
	pos += compacted_4b_initial * 4;
	lcn -= compacted_4b_initial;

	अगर (lcn < compacted_2b) अणु
		amortizedshअगरt = 1;
		जाओ out;
	पूर्ण
	pos += compacted_2b * 2;
	lcn -= compacted_2b;
	amortizedshअगरt = 2;
out:
	pos += lcn * (1 << amortizedshअगरt);
	err = z_erofs_reload_indexes(m, erofs_blknr(pos));
	अगर (err)
		वापस err;
	वापस unpack_compacted_index(m, amortizedshअगरt, erofs_blkoff(pos));
पूर्ण

अटल पूर्णांक z_erofs_load_cluster_from_disk(काष्ठा z_erofs_maprecorder *m,
					  अचिन्हित पूर्णांक lcn)
अणु
	स्थिर अचिन्हित पूर्णांक datamode = EROFS_I(m->inode)->datalayout;

	अगर (datamode == EROFS_INODE_FLAT_COMPRESSION_LEGACY)
		वापस legacy_load_cluster_from_disk(m, lcn);

	अगर (datamode == EROFS_INODE_FLAT_COMPRESSION)
		वापस compacted_load_cluster_from_disk(m, lcn);

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक z_erofs_extent_lookback(काष्ठा z_erofs_maprecorder *m,
				   अचिन्हित पूर्णांक lookback_distance)
अणु
	काष्ठा erofs_inode *स्थिर vi = EROFS_I(m->inode);
	काष्ठा erofs_map_blocks *स्थिर map = m->map;
	स्थिर अचिन्हित पूर्णांक lclusterbits = vi->z_logical_clusterbits;
	अचिन्हित दीर्घ lcn = m->lcn;
	पूर्णांक err;

	अगर (lcn < lookback_distance) अणु
		erofs_err(m->inode->i_sb,
			  "bogus lookback distance @ nid %llu", vi->nid);
		DBG_BUGON(1);
		वापस -EFSCORRUPTED;
	पूर्ण

	/* load extent head logical cluster अगर needed */
	lcn -= lookback_distance;
	err = z_erofs_load_cluster_from_disk(m, lcn);
	अगर (err)
		वापस err;

	चयन (m->type) अणु
	हाल Z_EROFS_VLE_CLUSTER_TYPE_NONHEAD:
		अगर (!m->delta[0]) अणु
			erofs_err(m->inode->i_sb,
				  "invalid lookback distance 0 @ nid %llu",
				  vi->nid);
			DBG_BUGON(1);
			वापस -EFSCORRUPTED;
		पूर्ण
		वापस z_erofs_extent_lookback(m, m->delta[0]);
	हाल Z_EROFS_VLE_CLUSTER_TYPE_PLAIN:
		map->m_flags &= ~EROFS_MAP_ZIPPED;
		fallthrough;
	हाल Z_EROFS_VLE_CLUSTER_TYPE_HEAD:
		map->m_la = (lcn << lclusterbits) | m->clusterofs;
		अवरोध;
	शेष:
		erofs_err(m->inode->i_sb,
			  "unknown type %u @ lcn %lu of nid %llu",
			  m->type, lcn, vi->nid);
		DBG_BUGON(1);
		वापस -EOPNOTSUPP;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक z_erofs_get_extent_compressedlen(काष्ठा z_erofs_maprecorder *m,
					    अचिन्हित पूर्णांक initial_lcn)
अणु
	काष्ठा erofs_inode *स्थिर vi = EROFS_I(m->inode);
	काष्ठा erofs_map_blocks *स्थिर map = m->map;
	स्थिर अचिन्हित पूर्णांक lclusterbits = vi->z_logical_clusterbits;
	अचिन्हित दीर्घ lcn;
	पूर्णांक err;

	DBG_BUGON(m->type != Z_EROFS_VLE_CLUSTER_TYPE_PLAIN &&
		  m->type != Z_EROFS_VLE_CLUSTER_TYPE_HEAD);
	अगर (!(map->m_flags & EROFS_MAP_ZIPPED) ||
	    !(vi->z_advise & Z_EROFS_ADVISE_BIG_PCLUSTER_1)) अणु
		map->m_plen = 1 << lclusterbits;
		वापस 0;
	पूर्ण

	lcn = m->lcn + 1;
	अगर (m->compressedlcs)
		जाओ out;

	err = z_erofs_load_cluster_from_disk(m, lcn);
	अगर (err)
		वापस err;

	/*
	 * If the 1st NONHEAD lcluster has alपढ़ोy been handled initially w/o
	 * valid compressedlcs, which means at least it mustn't be CBLKCNT, or
	 * an पूर्णांकernal implemenatation error is detected.
	 *
	 * The following code can also handle it properly anyway, but let's
	 * BUG_ON in the debugging mode only क्रम developers to notice that.
	 */
	DBG_BUGON(lcn == initial_lcn &&
		  m->type == Z_EROFS_VLE_CLUSTER_TYPE_NONHEAD);

	चयन (m->type) अणु
	हाल Z_EROFS_VLE_CLUSTER_TYPE_PLAIN:
	हाल Z_EROFS_VLE_CLUSTER_TYPE_HEAD:
		/*
		 * अगर the 1st NONHEAD lcluster is actually PLAIN or HEAD type
		 * rather than CBLKCNT, it's a 1 lcluster-sized pcluster.
		 */
		m->compressedlcs = 1;
		अवरोध;
	हाल Z_EROFS_VLE_CLUSTER_TYPE_NONHEAD:
		अगर (m->delta[0] != 1)
			जाओ err_bonus_cblkcnt;
		अगर (m->compressedlcs)
			अवरोध;
		fallthrough;
	शेष:
		erofs_err(m->inode->i_sb,
			  "cannot found CBLKCNT @ lcn %lu of nid %llu",
			  lcn, vi->nid);
		DBG_BUGON(1);
		वापस -EFSCORRUPTED;
	पूर्ण
out:
	map->m_plen = m->compressedlcs << lclusterbits;
	वापस 0;
err_bonus_cblkcnt:
	erofs_err(m->inode->i_sb,
		  "bogus CBLKCNT @ lcn %lu of nid %llu",
		  lcn, vi->nid);
	DBG_BUGON(1);
	वापस -EFSCORRUPTED;
पूर्ण

पूर्णांक z_erofs_map_blocks_iter(काष्ठा inode *inode,
			    काष्ठा erofs_map_blocks *map,
			    पूर्णांक flags)
अणु
	काष्ठा erofs_inode *स्थिर vi = EROFS_I(inode);
	काष्ठा z_erofs_maprecorder m = अणु
		.inode = inode,
		.map = map,
	पूर्ण;
	पूर्णांक err = 0;
	अचिन्हित पूर्णांक lclusterbits, enकरोff;
	अचिन्हित दीर्घ initial_lcn;
	अचिन्हित दीर्घ दीर्घ ofs, end;

	trace_z_erofs_map_blocks_iter_enter(inode, map, flags);

	/* when trying to पढ़ो beyond खातापूर्ण, leave it unmapped */
	अगर (map->m_la >= inode->i_size) अणु
		map->m_llen = map->m_la + 1 - inode->i_size;
		map->m_la = inode->i_size;
		map->m_flags = 0;
		जाओ out;
	पूर्ण

	err = z_erofs_fill_inode_lazy(inode);
	अगर (err)
		जाओ out;

	lclusterbits = vi->z_logical_clusterbits;
	ofs = map->m_la;
	initial_lcn = ofs >> lclusterbits;
	enकरोff = ofs & ((1 << lclusterbits) - 1);

	err = z_erofs_load_cluster_from_disk(&m, initial_lcn);
	अगर (err)
		जाओ unmap_out;

	map->m_flags = EROFS_MAP_ZIPPED;	/* by शेष, compressed */
	end = (m.lcn + 1ULL) << lclusterbits;

	चयन (m.type) अणु
	हाल Z_EROFS_VLE_CLUSTER_TYPE_PLAIN:
		अगर (enकरोff >= m.clusterofs)
			map->m_flags &= ~EROFS_MAP_ZIPPED;
		fallthrough;
	हाल Z_EROFS_VLE_CLUSTER_TYPE_HEAD:
		अगर (enकरोff >= m.clusterofs) अणु
			map->m_la = (m.lcn << lclusterbits) | m.clusterofs;
			अवरोध;
		पूर्ण
		/* m.lcn should be >= 1 अगर enकरोff < m.clusterofs */
		अगर (!m.lcn) अणु
			erofs_err(inode->i_sb,
				  "invalid logical cluster 0 at nid %llu",
				  vi->nid);
			err = -EFSCORRUPTED;
			जाओ unmap_out;
		पूर्ण
		end = (m.lcn << lclusterbits) | m.clusterofs;
		map->m_flags |= EROFS_MAP_FULL_MAPPED;
		m.delta[0] = 1;
		fallthrough;
	हाल Z_EROFS_VLE_CLUSTER_TYPE_NONHEAD:
		/* get the corresponding first chunk */
		err = z_erofs_extent_lookback(&m, m.delta[0]);
		अगर (err)
			जाओ unmap_out;
		अवरोध;
	शेष:
		erofs_err(inode->i_sb,
			  "unknown type %u @ offset %llu of nid %llu",
			  m.type, ofs, vi->nid);
		err = -EOPNOTSUPP;
		जाओ unmap_out;
	पूर्ण

	map->m_llen = end - map->m_la;
	map->m_pa = blknr_to_addr(m.pblk);
	map->m_flags |= EROFS_MAP_MAPPED;

	err = z_erofs_get_extent_compressedlen(&m, initial_lcn);
	अगर (err)
		जाओ out;
unmap_out:
	अगर (m.kaddr)
		kunmap_atomic(m.kaddr);

out:
	erofs_dbg("%s, m_la %llu m_pa %llu m_llen %llu m_plen %llu m_flags 0%o",
		  __func__, map->m_la, map->m_pa,
		  map->m_llen, map->m_plen, map->m_flags);

	trace_z_erofs_map_blocks_iter_निकास(inode, map, flags, err);

	/* aggressively BUG_ON अगरf CONFIG_EROFS_FS_DEBUG is on */
	DBG_BUGON(err < 0 && err != -ENOMEM);
	वापस err;
पूर्ण

