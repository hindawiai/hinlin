<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _FS_CEPH_MDSMAP_H
#घोषणा _FS_CEPH_MDSMAP_H

#समावेश <linux/bug.h>
#समावेश <linux/ceph/types.h>

/*
 * mds map - describe servers in the mds cluster.
 *
 * we limit fields to those the client actually xcares about
 */
काष्ठा ceph_mds_info अणु
	u64 global_id;
	काष्ठा ceph_entity_addr addr;
	s32 state;
	पूर्णांक num_export_tarमाला_लो;
	bool laggy;
	u32 *export_tarमाला_लो;
पूर्ण;

काष्ठा ceph_mdsmap अणु
	u32 m_epoch, m_client_epoch, m_last_failure;
	u32 m_root;
	u32 m_session_समयout;          /* seconds */
	u32 m_session_स्वतःबंद;        /* seconds */
	u64 m_max_file_size;
	u32 m_max_mds;			/* expected up:active mds number */
	u32 m_num_active_mds;		/* actual up:active mds number */
	u32 possible_max_rank;		/* possible max rank index */
	काष्ठा ceph_mds_info *m_info;

	/* which object pools file data can be stored in */
	पूर्णांक m_num_data_pg_pools;
	u64 *m_data_pg_pools;
	u64 m_cas_pg_pool;

	bool m_enabled;
	bool m_damaged;
	पूर्णांक m_num_laggy;
पूर्ण;

अटल अंतरभूत काष्ठा ceph_entity_addr *
ceph_mdsmap_get_addr(काष्ठा ceph_mdsmap *m, पूर्णांक w)
अणु
	अगर (w >= m->possible_max_rank)
		वापस शून्य;
	वापस &m->m_info[w].addr;
पूर्ण

अटल अंतरभूत पूर्णांक ceph_mdsmap_get_state(काष्ठा ceph_mdsmap *m, पूर्णांक w)
अणु
	BUG_ON(w < 0);
	अगर (w >= m->possible_max_rank)
		वापस CEPH_MDS_STATE_DNE;
	वापस m->m_info[w].state;
पूर्ण

अटल अंतरभूत bool ceph_mdsmap_is_laggy(काष्ठा ceph_mdsmap *m, पूर्णांक w)
अणु
	अगर (w >= 0 && w < m->possible_max_rank)
		वापस m->m_info[w].laggy;
	वापस false;
पूर्ण

बाह्य पूर्णांक ceph_mdsmap_get_अक्रमom_mds(काष्ठा ceph_mdsmap *m);
काष्ठा ceph_mdsmap *ceph_mdsmap_decode(व्योम **p, व्योम *end, bool msgr2);
बाह्य व्योम ceph_mdsmap_destroy(काष्ठा ceph_mdsmap *m);
बाह्य bool ceph_mdsmap_is_cluster_available(काष्ठा ceph_mdsmap *m);

#पूर्ण_अगर
