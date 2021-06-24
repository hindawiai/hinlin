<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _FS_CEPH_OSDMAP_H
#घोषणा _FS_CEPH_OSDMAP_H

#समावेश <linux/rbtree.h>
#समावेश <linux/ceph/types.h>
#समावेश <linux/ceph/decode.h>
#समावेश <linux/crush/crush.h>

/*
 * The osd map describes the current membership of the osd cluster and
 * specअगरies the mapping of objects to placement groups and placement
 * groups to (sets of) osds.  That is, it completely specअगरies the
 * (desired) distribution of all data objects in the प्रणाली at some
 * poपूर्णांक in समय.
 *
 * Each map version is identअगरied by an epoch, which increases monotonically.
 *
 * The map can be updated either via an incremental map (dअगरf) describing
 * the change between two successive epochs, or as a fully encoded map.
 */
काष्ठा ceph_pg अणु
	uपूर्णांक64_t pool;
	uपूर्णांक32_t seed;
पूर्ण;

#घोषणा CEPH_SPG_NOSHARD	-1

काष्ठा ceph_spg अणु
	काष्ठा ceph_pg pgid;
	s8 shard;
पूर्ण;

पूर्णांक ceph_pg_compare(स्थिर काष्ठा ceph_pg *lhs, स्थिर काष्ठा ceph_pg *rhs);
पूर्णांक ceph_spg_compare(स्थिर काष्ठा ceph_spg *lhs, स्थिर काष्ठा ceph_spg *rhs);

#घोषणा CEPH_POOL_FLAG_HASHPSPOOL	(1ULL << 0) /* hash pg seed and pool id
						       together */
#घोषणा CEPH_POOL_FLAG_FULL		(1ULL << 1) /* pool is full */
#घोषणा CEPH_POOL_FLAG_FULL_QUOTA	(1ULL << 10) /* pool ran out of quota,
							will set FULL too */
#घोषणा CEPH_POOL_FLAG_NEARFULL		(1ULL << 11) /* pool is nearfull */

काष्ठा ceph_pg_pool_info अणु
	काष्ठा rb_node node;
	s64 id;
	u8 type; /* CEPH_POOL_TYPE_* */
	u8 size;
	u8 min_size;
	u8 crush_ruleset;
	u8 object_hash;
	u32 last_क्रमce_request_resend;
	u32 pg_num, pgp_num;
	पूर्णांक pg_num_mask, pgp_num_mask;
	s64 पढ़ो_tier;
	s64 ग_लिखो_tier; /* wins क्रम पढ़ो+ग_लिखो ops */
	u64 flags; /* CEPH_POOL_FLAG_* */
	अक्षर *name;

	bool was_full;  /* क्रम handle_one_map() */
पूर्ण;

अटल अंतरभूत bool ceph_can_shअगरt_osds(काष्ठा ceph_pg_pool_info *pool)
अणु
	चयन (pool->type) अणु
	हाल CEPH_POOL_TYPE_REP:
		वापस true;
	हाल CEPH_POOL_TYPE_EC:
		वापस false;
	शेष:
		BUG();
	पूर्ण
पूर्ण

काष्ठा ceph_object_locator अणु
	s64 pool;
	काष्ठा ceph_string *pool_ns;
पूर्ण;

अटल अंतरभूत व्योम ceph_oloc_init(काष्ठा ceph_object_locator *oloc)
अणु
	oloc->pool = -1;
	oloc->pool_ns = शून्य;
पूर्ण

अटल अंतरभूत bool ceph_oloc_empty(स्थिर काष्ठा ceph_object_locator *oloc)
अणु
	वापस oloc->pool == -1;
पूर्ण

व्योम ceph_oloc_copy(काष्ठा ceph_object_locator *dest,
		    स्थिर काष्ठा ceph_object_locator *src);
व्योम ceph_oloc_destroy(काष्ठा ceph_object_locator *oloc);

/*
 * 51-अक्षर अंतरभूत_name is दीर्घ enough क्रम all cephfs and all but one
 * rbd requests: <imgname> in "<imgname>.rbd"/"rbd_id.<imgname>" can be
 * arbitrarily दीर्घ (~PAGE_SIZE).  It's करोne once during rbd map; all
 * other rbd requests fit पूर्णांकo अंतरभूत_name.
 *
 * Makes ceph_object_id 64 bytes on 64-bit.
 */
#घोषणा CEPH_OID_INLINE_LEN 52

/*
 * Both अंतरभूत and बाह्यal buffers have space क्रम a NUL-terminator,
 * which is carried around.  It's not required though - RADOS object
 * names करोn't have to be NUL-terminated and may contain NULs.
 */
काष्ठा ceph_object_id अणु
	अक्षर *name;
	अक्षर अंतरभूत_name[CEPH_OID_INLINE_LEN];
	पूर्णांक name_len;
पूर्ण;

#घोषणा __CEPH_OID_INITIALIZER(oid) अणु .name = (oid).अंतरभूत_name पूर्ण

#घोषणा CEPH_DEFINE_OID_ONSTACK(oid)				\
	काष्ठा ceph_object_id oid = __CEPH_OID_INITIALIZER(oid)

अटल अंतरभूत व्योम ceph_oid_init(काष्ठा ceph_object_id *oid)
अणु
	*oid = (काष्ठा ceph_object_id) __CEPH_OID_INITIALIZER(*oid);
पूर्ण

अटल अंतरभूत bool ceph_oid_empty(स्थिर काष्ठा ceph_object_id *oid)
अणु
	वापस oid->name == oid->अंतरभूत_name && !oid->name_len;
पूर्ण

व्योम ceph_oid_copy(काष्ठा ceph_object_id *dest,
		   स्थिर काष्ठा ceph_object_id *src);
__म_लिखो(2, 3)
व्योम ceph_oid_म_लिखो(काष्ठा ceph_object_id *oid, स्थिर अक्षर *fmt, ...);
__म_लिखो(3, 4)
पूर्णांक ceph_oid_aम_लिखो(काष्ठा ceph_object_id *oid, gfp_t gfp,
		     स्थिर अक्षर *fmt, ...);
व्योम ceph_oid_destroy(काष्ठा ceph_object_id *oid);

काष्ठा workspace_manager अणु
	काष्ठा list_head idle_ws;
	spinlock_t ws_lock;
	/* Number of मुक्त workspaces */
	पूर्णांक मुक्त_ws;
	/* Total number of allocated workspaces */
	atomic_t total_ws;
	/* Waiters क्रम a मुक्त workspace */
	रुको_queue_head_t ws_रुको;
पूर्ण;

काष्ठा ceph_pg_mapping अणु
	काष्ठा rb_node node;
	काष्ठा ceph_pg pgid;

	जोड़ अणु
		काष्ठा अणु
			पूर्णांक len;
			पूर्णांक osds[];
		पूर्ण pg_temp, pg_upmap;
		काष्ठा अणु
			पूर्णांक osd;
		पूर्ण primary_temp;
		काष्ठा अणु
			पूर्णांक len;
			पूर्णांक from_to[][2];
		पूर्ण pg_upmap_items;
	पूर्ण;
पूर्ण;

काष्ठा ceph_osdmap अणु
	काष्ठा ceph_fsid fsid;
	u32 epoch;
	काष्ठा ceph_बारpec created, modअगरied;

	u32 flags;         /* CEPH_OSDMAP_* */

	u32 max_osd;       /* size of osd_state, _offload, _addr arrays */
	u32 *osd_state;    /* CEPH_OSD_* */
	u32 *osd_weight;   /* 0 = failed, 0x10000 = 100% normal */
	काष्ठा ceph_entity_addr *osd_addr;

	काष्ठा rb_root pg_temp;
	काष्ठा rb_root primary_temp;

	/* remap (post-CRUSH, pre-up) */
	काष्ठा rb_root pg_upmap;	/* PG := raw set */
	काष्ठा rb_root pg_upmap_items;	/* from -> to within raw set */

	u32 *osd_primary_affinity;

	काष्ठा rb_root pg_pools;
	u32 pool_max;

	/* the CRUSH map specअगरies the mapping of placement groups to
	 * the list of osds that store+replicate them. */
	काष्ठा crush_map *crush;

	काष्ठा workspace_manager crush_wsm;
पूर्ण;

अटल अंतरभूत bool ceph_osd_exists(काष्ठा ceph_osdmap *map, पूर्णांक osd)
अणु
	वापस osd >= 0 && osd < map->max_osd &&
	       (map->osd_state[osd] & CEPH_OSD_EXISTS);
पूर्ण

अटल अंतरभूत bool ceph_osd_is_up(काष्ठा ceph_osdmap *map, पूर्णांक osd)
अणु
	वापस ceph_osd_exists(map, osd) &&
	       (map->osd_state[osd] & CEPH_OSD_UP);
पूर्ण

अटल अंतरभूत bool ceph_osd_is_करोwn(काष्ठा ceph_osdmap *map, पूर्णांक osd)
अणु
	वापस !ceph_osd_is_up(map, osd);
पूर्ण

अक्षर *ceph_osdmap_state_str(अक्षर *str, पूर्णांक len, u32 state);
बाह्य u32 ceph_get_primary_affinity(काष्ठा ceph_osdmap *map, पूर्णांक osd);

अटल अंतरभूत काष्ठा ceph_entity_addr *ceph_osd_addr(काष्ठा ceph_osdmap *map,
						     पूर्णांक osd)
अणु
	अगर (osd >= map->max_osd)
		वापस शून्य;
	वापस &map->osd_addr[osd];
पूर्ण

#घोषणा CEPH_PGID_ENCODING_LEN		(1 + 8 + 4 + 4)

अटल अंतरभूत पूर्णांक ceph_decode_pgid(व्योम **p, व्योम *end, काष्ठा ceph_pg *pgid)
अणु
	__u8 version;

	अगर (!ceph_has_room(p, end, CEPH_PGID_ENCODING_LEN)) अणु
		pr_warn("incomplete pg encoding\n");
		वापस -EINVAL;
	पूर्ण
	version = ceph_decode_8(p);
	अगर (version > 1) अणु
		pr_warn("do not understand pg encoding %d > 1\n",
			(पूर्णांक)version);
		वापस -EINVAL;
	पूर्ण

	pgid->pool = ceph_decode_64(p);
	pgid->seed = ceph_decode_32(p);
	*p += 4;	/* skip deprecated preferred value */

	वापस 0;
पूर्ण

काष्ठा ceph_osdmap *ceph_osdmap_alloc(व्योम);
काष्ठा ceph_osdmap *ceph_osdmap_decode(व्योम **p, व्योम *end, bool msgr2);
काष्ठा ceph_osdmap *osdmap_apply_incremental(व्योम **p, व्योम *end, bool msgr2,
					     काष्ठा ceph_osdmap *map);
बाह्य व्योम ceph_osdmap_destroy(काष्ठा ceph_osdmap *map);

काष्ठा ceph_osds अणु
	पूर्णांक osds[CEPH_PG_MAX_SIZE];
	पूर्णांक size;
	पूर्णांक primary; /* id, NOT index */
पूर्ण;

अटल अंतरभूत व्योम ceph_osds_init(काष्ठा ceph_osds *set)
अणु
	set->size = 0;
	set->primary = -1;
पूर्ण

व्योम ceph_osds_copy(काष्ठा ceph_osds *dest, स्थिर काष्ठा ceph_osds *src);

bool ceph_pg_is_split(स्थिर काष्ठा ceph_pg *pgid, u32 old_pg_num,
		      u32 new_pg_num);
bool ceph_is_new_पूर्णांकerval(स्थिर काष्ठा ceph_osds *old_acting,
			  स्थिर काष्ठा ceph_osds *new_acting,
			  स्थिर काष्ठा ceph_osds *old_up,
			  स्थिर काष्ठा ceph_osds *new_up,
			  पूर्णांक old_size,
			  पूर्णांक new_size,
			  पूर्णांक old_min_size,
			  पूर्णांक new_min_size,
			  u32 old_pg_num,
			  u32 new_pg_num,
			  bool old_sort_bitwise,
			  bool new_sort_bitwise,
			  bool old_recovery_deletes,
			  bool new_recovery_deletes,
			  स्थिर काष्ठा ceph_pg *pgid);
bool ceph_osds_changed(स्थिर काष्ठा ceph_osds *old_acting,
		       स्थिर काष्ठा ceph_osds *new_acting,
		       bool any_change);

व्योम __ceph_object_locator_to_pg(काष्ठा ceph_pg_pool_info *pi,
				 स्थिर काष्ठा ceph_object_id *oid,
				 स्थिर काष्ठा ceph_object_locator *oloc,
				 काष्ठा ceph_pg *raw_pgid);
पूर्णांक ceph_object_locator_to_pg(काष्ठा ceph_osdmap *osdmap,
			      स्थिर काष्ठा ceph_object_id *oid,
			      स्थिर काष्ठा ceph_object_locator *oloc,
			      काष्ठा ceph_pg *raw_pgid);

व्योम ceph_pg_to_up_acting_osds(काष्ठा ceph_osdmap *osdmap,
			       काष्ठा ceph_pg_pool_info *pi,
			       स्थिर काष्ठा ceph_pg *raw_pgid,
			       काष्ठा ceph_osds *up,
			       काष्ठा ceph_osds *acting);
bool ceph_pg_to_primary_shard(काष्ठा ceph_osdmap *osdmap,
			      काष्ठा ceph_pg_pool_info *pi,
			      स्थिर काष्ठा ceph_pg *raw_pgid,
			      काष्ठा ceph_spg *spgid);
पूर्णांक ceph_pg_to_acting_primary(काष्ठा ceph_osdmap *osdmap,
			      स्थिर काष्ठा ceph_pg *raw_pgid);

काष्ठा crush_loc अणु
	अक्षर *cl_type_name;
	अक्षर *cl_name;
पूर्ण;

काष्ठा crush_loc_node अणु
	काष्ठा rb_node cl_node;
	काष्ठा crush_loc cl_loc;  /* poपूर्णांकers पूर्णांकo cl_data */
	अक्षर cl_data[];
पूर्ण;

पूर्णांक ceph_parse_crush_location(अक्षर *crush_location, काष्ठा rb_root *locs);
पूर्णांक ceph_compare_crush_locs(काष्ठा rb_root *locs1, काष्ठा rb_root *locs2);
व्योम ceph_clear_crush_locs(काष्ठा rb_root *locs);

पूर्णांक ceph_get_crush_locality(काष्ठा ceph_osdmap *osdmap, पूर्णांक id,
			    काष्ठा rb_root *locs);

बाह्य काष्ठा ceph_pg_pool_info *ceph_pg_pool_by_id(काष्ठा ceph_osdmap *map,
						    u64 id);
बाह्य स्थिर अक्षर *ceph_pg_pool_name_by_id(काष्ठा ceph_osdmap *map, u64 id);
बाह्य पूर्णांक ceph_pg_poolid_by_name(काष्ठा ceph_osdmap *map, स्थिर अक्षर *name);
u64 ceph_pg_pool_flags(काष्ठा ceph_osdmap *map, u64 id);

#पूर्ण_अगर
