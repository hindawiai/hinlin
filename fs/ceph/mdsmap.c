<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/ceph/ceph_debug.h>

#समावेश <linux/bug.h>
#समावेश <linux/err.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>

#समावेश <linux/ceph/mdsmap.h>
#समावेश <linux/ceph/messenger.h>
#समावेश <linux/ceph/decode.h>

#समावेश "super.h"

#घोषणा CEPH_MDS_IS_READY(i, ignore_laggy) \
	(m->m_info[i].state > 0 && ignore_laggy ? true : !m->m_info[i].laggy)

अटल पूर्णांक __mdsmap_get_अक्रमom_mds(काष्ठा ceph_mdsmap *m, bool ignore_laggy)
अणु
	पूर्णांक n = 0;
	पूर्णांक i, j;

	/* count */
	क्रम (i = 0; i < m->possible_max_rank; i++)
		अगर (CEPH_MDS_IS_READY(i, ignore_laggy))
			n++;
	अगर (n == 0)
		वापस -1;

	/* pick */
	n = pअक्रमom_u32() % n;
	क्रम (j = 0, i = 0; i < m->possible_max_rank; i++) अणु
		अगर (CEPH_MDS_IS_READY(i, ignore_laggy))
			j++;
		अगर (j > n)
			अवरोध;
	पूर्ण

	वापस i;
पूर्ण

/*
 * choose a अक्रमom mds that is "up" (i.e. has a state > 0), or -1.
 */
पूर्णांक ceph_mdsmap_get_अक्रमom_mds(काष्ठा ceph_mdsmap *m)
अणु
	पूर्णांक mds;

	mds = __mdsmap_get_अक्रमom_mds(m, false);
	अगर (mds == m->possible_max_rank || mds == -1)
		mds = __mdsmap_get_अक्रमom_mds(m, true);

	वापस mds == m->possible_max_rank ? -1 : mds;
पूर्ण

#घोषणा __decode_and_drop_type(p, end, type, bad)		\
	करो अणु							\
		अगर (*p + माप(type) > end)			\
			जाओ bad;				\
		*p += माप(type);				\
	पूर्ण जबतक (0)

#घोषणा __decode_and_drop_set(p, end, type, bad)		\
	करो अणु							\
		u32 n;						\
		माप_प्रकार need;					\
		ceph_decode_32_safe(p, end, n, bad);		\
		need = माप(type) * n;			\
		ceph_decode_need(p, end, need, bad);		\
		*p += need;					\
	पूर्ण जबतक (0)

#घोषणा __decode_and_drop_map(p, end, ktype, vtype, bad)	\
	करो अणु							\
		u32 n;						\
		माप_प्रकार need;					\
		ceph_decode_32_safe(p, end, n, bad);		\
		need = (माप(ktype) + माप(vtype)) * n;	\
		ceph_decode_need(p, end, need, bad);		\
		*p += need;					\
	पूर्ण जबतक (0)


अटल पूर्णांक __decode_and_drop_compat_set(व्योम **p, व्योम* end)
अणु
	पूर्णांक i;
	/* compat, ro_compat, incompat*/
	क्रम (i = 0; i < 3; i++) अणु
		u32 n;
		ceph_decode_need(p, end, माप(u64) + माप(u32), bad);
		/* mask */
		*p += माप(u64);
		/* names (map<u64, string>) */
		n = ceph_decode_32(p);
		जबतक (n-- > 0) अणु
			u32 len;
			ceph_decode_need(p, end, माप(u64) + माप(u32),
					 bad);
			*p += माप(u64);
			len = ceph_decode_32(p);
			ceph_decode_need(p, end, len, bad);
			*p += len;
		पूर्ण
	पूर्ण
	वापस 0;
bad:
	वापस -1;
पूर्ण

/*
 * Decode an MDS map
 *
 * Ignore any fields we करोn't care about (there are quite a few of
 * them).
 */
काष्ठा ceph_mdsmap *ceph_mdsmap_decode(व्योम **p, व्योम *end, bool msgr2)
अणु
	काष्ठा ceph_mdsmap *m;
	स्थिर व्योम *start = *p;
	पूर्णांक i, j, n;
	पूर्णांक err;
	u8 mdsmap_v;
	u16 mdsmap_ev;

	m = kzalloc(माप(*m), GFP_NOFS);
	अगर (!m)
		वापस ERR_PTR(-ENOMEM);

	ceph_decode_need(p, end, 1 + 1, bad);
	mdsmap_v = ceph_decode_8(p);
	*p += माप(u8);			/* mdsmap_cv */
	अगर (mdsmap_v >= 4) अणु
	       u32 mdsmap_len;
	       ceph_decode_32_safe(p, end, mdsmap_len, bad);
	       अगर (end < *p + mdsmap_len)
		       जाओ bad;
	       end = *p + mdsmap_len;
	पूर्ण

	ceph_decode_need(p, end, 8*माप(u32) + माप(u64), bad);
	m->m_epoch = ceph_decode_32(p);
	m->m_client_epoch = ceph_decode_32(p);
	m->m_last_failure = ceph_decode_32(p);
	m->m_root = ceph_decode_32(p);
	m->m_session_समयout = ceph_decode_32(p);
	m->m_session_स्वतःबंद = ceph_decode_32(p);
	m->m_max_file_size = ceph_decode_64(p);
	m->m_max_mds = ceph_decode_32(p);

	/*
	 * pick out the active nodes as the m_num_active_mds, the
	 * m_num_active_mds maybe larger than m_max_mds when decreasing
	 * the max_mds in cluster side, in other हाल it should less
	 * than or equal to m_max_mds.
	 */
	m->m_num_active_mds = n = ceph_decode_32(p);

	/*
	 * the possible max rank, it maybe larger than the m_num_active_mds,
	 * क्रम example अगर the mds_max == 2 in the cluster, when the MDS(0)
	 * was laggy and being replaced by a new MDS, we will temporarily
	 * receive a new mds map with n_num_mds == 1 and the active MDS(1),
	 * and the mds rank >= m_num_active_mds.
	 */
	m->possible_max_rank = max(m->m_num_active_mds, m->m_max_mds);

	m->m_info = kसुस्मृति(m->possible_max_rank, माप(*m->m_info), GFP_NOFS);
	अगर (!m->m_info)
		जाओ nomem;

	/* pick out active nodes from mds_info (state > 0) */
	क्रम (i = 0; i < n; i++) अणु
		u64 global_id;
		u32 namelen;
		s32 mds, inc, state;
		u8 info_v;
		व्योम *info_end = शून्य;
		काष्ठा ceph_entity_addr addr;
		u32 num_export_tarमाला_लो;
		व्योम *pexport_tarमाला_लो = शून्य;
		काष्ठा ceph_बारpec laggy_since;
		काष्ठा ceph_mds_info *info;
		bool laggy;

		ceph_decode_need(p, end, माप(u64) + 1, bad);
		global_id = ceph_decode_64(p);
		info_v= ceph_decode_8(p);
		अगर (info_v >= 4) अणु
			u32 info_len;
			ceph_decode_need(p, end, 1 + माप(u32), bad);
			*p += माप(u8);	/* info_cv */
			info_len = ceph_decode_32(p);
			info_end = *p + info_len;
			अगर (info_end > end)
				जाओ bad;
		पूर्ण

		ceph_decode_need(p, end, माप(u64) + माप(u32), bad);
		*p += माप(u64);
		namelen = ceph_decode_32(p);  /* skip mds name */
		*p += namelen;

		ceph_decode_32_safe(p, end, mds, bad);
		ceph_decode_32_safe(p, end, inc, bad);
		ceph_decode_32_safe(p, end, state, bad);
		*p += माप(u64);		/* state_seq */
		अगर (info_v >= 8)
			err = ceph_decode_entity_addrvec(p, end, msgr2, &addr);
		अन्यथा
			err = ceph_decode_entity_addr(p, end, &addr);
		अगर (err)
			जाओ corrupt;

		ceph_decode_copy_safe(p, end, &laggy_since, माप(laggy_since),
				      bad);
		laggy = laggy_since.tv_sec != 0 || laggy_since.tv_nsec != 0;
		*p += माप(u32);
		ceph_decode_32_safe(p, end, namelen, bad);
		*p += namelen;
		अगर (info_v >= 2) अणु
			ceph_decode_32_safe(p, end, num_export_tarमाला_लो, bad);
			pexport_tarमाला_लो = *p;
			*p += num_export_tarमाला_लो * माप(u32);
		पूर्ण अन्यथा अणु
			num_export_tarमाला_लो = 0;
		पूर्ण

		अगर (info_end && *p != info_end) अणु
			अगर (*p > info_end)
				जाओ bad;
			*p = info_end;
		पूर्ण

		करोut("mdsmap_decode %d/%d %lld mds%d.%d %s %s%s\n",
		     i+1, n, global_id, mds, inc,
		     ceph_pr_addr(&addr),
		     ceph_mds_state_name(state),
		     laggy ? "(laggy)" : "");

		अगर (mds < 0 || mds >= m->possible_max_rank) अणु
			pr_warn("mdsmap_decode got incorrect mds(%d)\n", mds);
			जारी;
		पूर्ण

		अगर (state <= 0) अणु
			करोut("mdsmap_decode got incorrect state(%s)\n",
			     ceph_mds_state_name(state));
			जारी;
		पूर्ण

		info = &m->m_info[mds];
		info->global_id = global_id;
		info->state = state;
		info->addr = addr;
		info->laggy = laggy;
		info->num_export_tarमाला_लो = num_export_tarमाला_लो;
		अगर (num_export_tarमाला_लो) अणु
			info->export_tarमाला_लो = kसुस्मृति(num_export_tarमाला_लो,
						       माप(u32), GFP_NOFS);
			अगर (!info->export_tarमाला_लो)
				जाओ nomem;
			क्रम (j = 0; j < num_export_tarमाला_लो; j++)
				info->export_tarमाला_लो[j] =
				       ceph_decode_32(&pexport_tarमाला_लो);
		पूर्ण अन्यथा अणु
			info->export_tarमाला_लो = शून्य;
		पूर्ण
	पूर्ण

	/* pg_pools */
	ceph_decode_32_safe(p, end, n, bad);
	m->m_num_data_pg_pools = n;
	m->m_data_pg_pools = kसुस्मृति(n, माप(u64), GFP_NOFS);
	अगर (!m->m_data_pg_pools)
		जाओ nomem;
	ceph_decode_need(p, end, माप(u64)*(n+1), bad);
	क्रम (i = 0; i < n; i++)
		m->m_data_pg_pools[i] = ceph_decode_64(p);
	m->m_cas_pg_pool = ceph_decode_64(p);
	m->m_enabled = m->m_epoch > 1;

	mdsmap_ev = 1;
	अगर (mdsmap_v >= 2) अणु
		ceph_decode_16_safe(p, end, mdsmap_ev, bad_ext);
	पूर्ण
	अगर (mdsmap_ev >= 3) अणु
		अगर (__decode_and_drop_compat_set(p, end) < 0)
			जाओ bad_ext;
	पूर्ण
	/* metadata_pool */
	अगर (mdsmap_ev < 5) अणु
		__decode_and_drop_type(p, end, u32, bad_ext);
	पूर्ण अन्यथा अणु
		__decode_and_drop_type(p, end, u64, bad_ext);
	पूर्ण

	/* created + modअगरied + tableserver */
	__decode_and_drop_type(p, end, काष्ठा ceph_बारpec, bad_ext);
	__decode_and_drop_type(p, end, काष्ठा ceph_बारpec, bad_ext);
	__decode_and_drop_type(p, end, u32, bad_ext);

	/* in */
	अणु
		पूर्णांक num_laggy = 0;
		ceph_decode_32_safe(p, end, n, bad_ext);
		ceph_decode_need(p, end, माप(u32) * n, bad_ext);

		क्रम (i = 0; i < n; i++) अणु
			s32 mds = ceph_decode_32(p);
			अगर (mds >= 0 && mds < m->possible_max_rank) अणु
				अगर (m->m_info[mds].laggy)
					num_laggy++;
			पूर्ण
		पूर्ण
		m->m_num_laggy = num_laggy;

		अगर (n > m->possible_max_rank) अणु
			व्योम *new_m_info = kपुनः_स्मृति(m->m_info,
						    n * माप(*m->m_info),
						    GFP_NOFS | __GFP_ZERO);
			अगर (!new_m_info)
				जाओ nomem;
			m->m_info = new_m_info;
		पूर्ण
		m->possible_max_rank = n;
	पूर्ण

	/* inc */
	__decode_and_drop_map(p, end, u32, u32, bad_ext);
	/* up */
	__decode_and_drop_map(p, end, u32, u64, bad_ext);
	/* failed */
	__decode_and_drop_set(p, end, u32, bad_ext);
	/* stopped */
	__decode_and_drop_set(p, end, u32, bad_ext);

	अगर (mdsmap_ev >= 4) अणु
		/* last_failure_osd_epoch */
		__decode_and_drop_type(p, end, u32, bad_ext);
	पूर्ण
	अगर (mdsmap_ev >= 6) अणु
		/* ever_allowed_snaps */
		__decode_and_drop_type(p, end, u8, bad_ext);
		/* explicitly_allowed_snaps */
		__decode_and_drop_type(p, end, u8, bad_ext);
	पूर्ण
	अगर (mdsmap_ev >= 7) अणु
		/* अंतरभूत_data_enabled */
		__decode_and_drop_type(p, end, u8, bad_ext);
	पूर्ण
	अगर (mdsmap_ev >= 8) अणु
		u32 name_len;
		/* enabled */
		ceph_decode_8_safe(p, end, m->m_enabled, bad_ext);
		ceph_decode_32_safe(p, end, name_len, bad_ext);
		ceph_decode_need(p, end, name_len, bad_ext);
		*p += name_len;
	पूर्ण
	/* damaged */
	अगर (mdsmap_ev >= 9) अणु
		माप_प्रकार need;
		ceph_decode_32_safe(p, end, n, bad_ext);
		need = माप(u32) * n;
		ceph_decode_need(p, end, need, bad_ext);
		*p += need;
		m->m_damaged = n > 0;
	पूर्ण अन्यथा अणु
		m->m_damaged = false;
	पूर्ण
bad_ext:
	करोut("mdsmap_decode m_enabled: %d, m_damaged: %d, m_num_laggy: %d\n",
	     !!m->m_enabled, !!m->m_damaged, m->m_num_laggy);
	*p = end;
	करोut("mdsmap_decode success epoch %u\n", m->m_epoch);
	वापस m;
nomem:
	err = -ENOMEM;
	जाओ out_err;
corrupt:
	pr_err("corrupt mdsmap\n");
	prपूर्णांक_hex_dump(KERN_DEBUG, "mdsmap: ",
		       DUMP_PREFIX_OFFSET, 16, 1,
		       start, end - start, true);
out_err:
	ceph_mdsmap_destroy(m);
	वापस ERR_PTR(err);
bad:
	err = -EINVAL;
	जाओ corrupt;
पूर्ण

व्योम ceph_mdsmap_destroy(काष्ठा ceph_mdsmap *m)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < m->possible_max_rank; i++)
		kमुक्त(m->m_info[i].export_tarमाला_लो);
	kमुक्त(m->m_info);
	kमुक्त(m->m_data_pg_pools);
	kमुक्त(m);
पूर्ण

bool ceph_mdsmap_is_cluster_available(काष्ठा ceph_mdsmap *m)
अणु
	पूर्णांक i, nr_active = 0;
	अगर (!m->m_enabled)
		वापस false;
	अगर (m->m_damaged)
		वापस false;
	अगर (m->m_num_laggy == m->m_num_active_mds)
		वापस false;
	क्रम (i = 0; i < m->possible_max_rank; i++) अणु
		अगर (m->m_info[i].state == CEPH_MDS_STATE_ACTIVE)
			nr_active++;
	पूर्ण
	वापस nr_active > 0;
पूर्ण
