<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _FS_CEPH_OSD_CLIENT_H
#घोषणा _FS_CEPH_OSD_CLIENT_H

#समावेश <linux/bitrev.h>
#समावेश <linux/completion.h>
#समावेश <linux/kref.h>
#समावेश <linux/mempool.h>
#समावेश <linux/rbtree.h>
#समावेश <linux/refcount.h>
#समावेश <linux/kसमय.स>

#समावेश <linux/ceph/types.h>
#समावेश <linux/ceph/osdmap.h>
#समावेश <linux/ceph/messenger.h>
#समावेश <linux/ceph/msgpool.h>
#समावेश <linux/ceph/auth.h>
#समावेश <linux/ceph/pagelist.h>

काष्ठा ceph_msg;
काष्ठा ceph_snap_context;
काष्ठा ceph_osd_request;
काष्ठा ceph_osd_client;

/*
 * completion callback क्रम async ग_लिखोpages
 */
प्रकार व्योम (*ceph_osdc_callback_t)(काष्ठा ceph_osd_request *);

#घोषणा CEPH_HOMELESS_OSD	-1

/* a given osd we're communicating with */
काष्ठा ceph_osd अणु
	refcount_t o_ref;
	काष्ठा ceph_osd_client *o_osdc;
	पूर्णांक o_osd;
	पूर्णांक o_incarnation;
	काष्ठा rb_node o_node;
	काष्ठा ceph_connection o_con;
	काष्ठा rb_root o_requests;
	काष्ठा rb_root o_linger_requests;
	काष्ठा rb_root o_backoff_mappings;
	काष्ठा rb_root o_backoffs_by_id;
	काष्ठा list_head o_osd_lru;
	काष्ठा ceph_auth_handshake o_auth;
	अचिन्हित दीर्घ lru_ttl;
	काष्ठा list_head o_keepalive_item;
	काष्ठा mutex lock;
पूर्ण;

#घोषणा CEPH_OSD_SLAB_OPS	2
#घोषणा CEPH_OSD_MAX_OPS	16

क्रमागत ceph_osd_data_type अणु
	CEPH_OSD_DATA_TYPE_NONE = 0,
	CEPH_OSD_DATA_TYPE_PAGES,
	CEPH_OSD_DATA_TYPE_PAGELIST,
#अगर_घोषित CONFIG_BLOCK
	CEPH_OSD_DATA_TYPE_BIO,
#पूर्ण_अगर /* CONFIG_BLOCK */
	CEPH_OSD_DATA_TYPE_BVECS,
पूर्ण;

काष्ठा ceph_osd_data अणु
	क्रमागत ceph_osd_data_type	type;
	जोड़ अणु
		काष्ठा अणु
			काष्ठा page	**pages;
			u64		length;
			u32		alignment;
			bool		pages_from_pool;
			bool		own_pages;
		पूर्ण;
		काष्ठा ceph_pagelist	*pagelist;
#अगर_घोषित CONFIG_BLOCK
		काष्ठा अणु
			काष्ठा ceph_bio_iter	bio_pos;
			u32			bio_length;
		पूर्ण;
#पूर्ण_अगर /* CONFIG_BLOCK */
		काष्ठा अणु
			काष्ठा ceph_bvec_iter	bvec_pos;
			u32			num_bvecs;
		पूर्ण;
	पूर्ण;
पूर्ण;

काष्ठा ceph_osd_req_op अणु
	u16 op;           /* CEPH_OSD_OP_* */
	u32 flags;        /* CEPH_OSD_OP_FLAG_* */
	u32 indata_len;   /* request */
	u32 outdata_len;  /* reply */
	s32 rval;

	जोड़ अणु
		काष्ठा ceph_osd_data raw_data_in;
		काष्ठा अणु
			u64 offset, length;
			u64 truncate_size;
			u32 truncate_seq;
			काष्ठा ceph_osd_data osd_data;
		पूर्ण extent;
		काष्ठा अणु
			u32 name_len;
			u32 value_len;
			__u8 cmp_op;       /* CEPH_OSD_CMPXATTR_OP_* */
			__u8 cmp_mode;     /* CEPH_OSD_CMPXATTR_MODE_* */
			काष्ठा ceph_osd_data osd_data;
		पूर्ण xattr;
		काष्ठा अणु
			स्थिर अक्षर *class_name;
			स्थिर अक्षर *method_name;
			काष्ठा ceph_osd_data request_info;
			काष्ठा ceph_osd_data request_data;
			काष्ठा ceph_osd_data response_data;
			__u8 class_len;
			__u8 method_len;
			u32 indata_len;
		पूर्ण cls;
		काष्ठा अणु
			u64 cookie;
			__u8 op;           /* CEPH_OSD_WATCH_OP_ */
			u32 gen;
		पूर्ण watch;
		काष्ठा अणु
			काष्ठा ceph_osd_data request_data;
		पूर्ण notअगरy_ack;
		काष्ठा अणु
			u64 cookie;
			काष्ठा ceph_osd_data request_data;
			काष्ठा ceph_osd_data response_data;
		पूर्ण notअगरy;
		काष्ठा अणु
			काष्ठा ceph_osd_data response_data;
		पूर्ण list_watchers;
		काष्ठा अणु
			u64 expected_object_size;
			u64 expected_ग_लिखो_size;
			u32 flags;  /* CEPH_OSD_OP_ALLOC_HINT_FLAG_* */
		पूर्ण alloc_hपूर्णांक;
		काष्ठा अणु
			u64 snapid;
			u64 src_version;
			u8 flags;
			u32 src_fadvise_flags;
			काष्ठा ceph_osd_data osd_data;
		पूर्ण copy_from;
	पूर्ण;
पूर्ण;

काष्ठा ceph_osd_request_target अणु
	काष्ठा ceph_object_id base_oid;
	काष्ठा ceph_object_locator base_oloc;
	काष्ठा ceph_object_id target_oid;
	काष्ठा ceph_object_locator target_oloc;

	काष्ठा ceph_pg pgid;               /* last raw pg we mapped to */
	काष्ठा ceph_spg spgid;             /* last actual spg we mapped to */
	u32 pg_num;
	u32 pg_num_mask;
	काष्ठा ceph_osds acting;
	काष्ठा ceph_osds up;
	पूर्णांक size;
	पूर्णांक min_size;
	bool sort_bitwise;
	bool recovery_deletes;

	अचिन्हित पूर्णांक flags;                /* CEPH_OSD_FLAG_* */
	bool used_replica;
	bool छोड़ोd;

	u32 epoch;
	u32 last_क्रमce_resend;

	पूर्णांक osd;
पूर्ण;

/* an in-flight request */
काष्ठा ceph_osd_request अणु
	u64             r_tid;              /* unique क्रम this client */
	काष्ठा rb_node  r_node;
	काष्ठा rb_node  r_mc_node;          /* map check */
	काष्ठा work_काष्ठा r_complete_work;
	काष्ठा ceph_osd *r_osd;

	काष्ठा ceph_osd_request_target r_t;
#घोषणा r_base_oid	r_t.base_oid
#घोषणा r_base_oloc	r_t.base_oloc
#घोषणा r_flags		r_t.flags

	काष्ठा ceph_msg  *r_request, *r_reply;
	u32               r_sent;      /* >0 अगर r_request is sending/sent */

	/* request osd ops array  */
	अचिन्हित पूर्णांक		r_num_ops;

	पूर्णांक               r_result;

	काष्ठा ceph_osd_client *r_osdc;
	काष्ठा kref       r_kref;
	bool              r_mempool;
	काष्ठा completion r_completion;       /* निजी to osd_client.c */
	ceph_osdc_callback_t r_callback;

	काष्ठा inode *r_inode;         	      /* क्रम use by callbacks */
	काष्ठा list_head r_निजी_item;      /* ditto */
	व्योम *r_priv;			      /* ditto */

	/* set by submitter */
	u64 r_snapid;                         /* क्रम पढ़ोs, CEPH_NOSNAP o/w */
	काष्ठा ceph_snap_context *r_snapc;    /* क्रम ग_लिखोs */
	काष्ठा बारpec64 r_mसमय;            /* ditto */
	u64 r_data_offset;                    /* ditto */
	bool r_linger;                        /* करोn't resend on failure */

	/* पूर्णांकernal */
	अचिन्हित दीर्घ r_stamp;                /* jअगरfies, send or check समय */
	अचिन्हित दीर्घ r_start_stamp;          /* jअगरfies */
	kसमय_प्रकार r_start_latency;              /* kसमय_प्रकार */
	kसमय_प्रकार r_end_latency;                /* kसमय_प्रकार */
	पूर्णांक r_attempts;
	u32 r_map_dne_bound;

	काष्ठा ceph_osd_req_op r_ops[];
पूर्ण;

काष्ठा ceph_request_redirect अणु
	काष्ठा ceph_object_locator oloc;
पूर्ण;

/*
 * osd request identअगरier
 *
 * caller name + incarnation# + tid to unique identअगरy this request
 */
काष्ठा ceph_osd_reqid अणु
	काष्ठा ceph_entity_name name;
	__le64 tid;
	__le32 inc;
पूर्ण __packed;

काष्ठा ceph_blkin_trace_info अणु
	__le64 trace_id;
	__le64 span_id;
	__le64 parent_span_id;
पूर्ण __packed;

प्रकार व्योम (*raकरोs_watchcb2_t)(व्योम *arg, u64 notअगरy_id, u64 cookie,
				 u64 notअगरier_id, व्योम *data, माप_प्रकार data_len);
प्रकार व्योम (*raकरोs_watcherrcb_t)(व्योम *arg, u64 cookie, पूर्णांक err);

काष्ठा ceph_osd_linger_request अणु
	काष्ठा ceph_osd_client *osdc;
	u64 linger_id;
	bool committed;
	bool is_watch;                  /* watch or notअगरy */

	काष्ठा ceph_osd *osd;
	काष्ठा ceph_osd_request *reg_req;
	काष्ठा ceph_osd_request *ping_req;
	अचिन्हित दीर्घ ping_sent;
	अचिन्हित दीर्घ watch_valid_thru;
	काष्ठा list_head pending_lworks;

	काष्ठा ceph_osd_request_target t;
	u32 map_dne_bound;

	काष्ठा बारpec64 mसमय;

	काष्ठा kref kref;
	काष्ठा mutex lock;
	काष्ठा rb_node node;            /* osd */
	काष्ठा rb_node osdc_node;       /* osdc */
	काष्ठा rb_node mc_node;         /* map check */
	काष्ठा list_head scan_item;

	काष्ठा completion reg_commit_रुको;
	काष्ठा completion notअगरy_finish_रुको;
	पूर्णांक reg_commit_error;
	पूर्णांक notअगरy_finish_error;
	पूर्णांक last_error;

	u32 रेजिस्टर_gen;
	u64 notअगरy_id;

	raकरोs_watchcb2_t wcb;
	raकरोs_watcherrcb_t errcb;
	व्योम *data;

	काष्ठा page ***preply_pages;
	माप_प्रकार *preply_len;
पूर्ण;

काष्ठा ceph_watch_item अणु
	काष्ठा ceph_entity_name name;
	u64 cookie;
	काष्ठा ceph_entity_addr addr;
पूर्ण;

काष्ठा ceph_spg_mapping अणु
	काष्ठा rb_node node;
	काष्ठा ceph_spg spgid;

	काष्ठा rb_root backoffs;
पूर्ण;

काष्ठा ceph_hobject_id अणु
	व्योम *key;
	माप_प्रकार key_len;
	व्योम *oid;
	माप_प्रकार oid_len;
	u64 snapid;
	u32 hash;
	u8 is_max;
	व्योम *nspace;
	माप_प्रकार nspace_len;
	s64 pool;

	/* cache */
	u32 hash_reverse_bits;
पूर्ण;

अटल अंतरभूत व्योम ceph_hoid_build_hash_cache(काष्ठा ceph_hobject_id *hoid)
अणु
	hoid->hash_reverse_bits = bitrev32(hoid->hash);
पूर्ण

/*
 * PG-wide backoff: [begin, end)
 * per-object backoff: begin == end
 */
काष्ठा ceph_osd_backoff अणु
	काष्ठा rb_node spg_node;
	काष्ठा rb_node id_node;

	काष्ठा ceph_spg spgid;
	u64 id;
	काष्ठा ceph_hobject_id *begin;
	काष्ठा ceph_hobject_id *end;
पूर्ण;

#घोषणा CEPH_LINGER_ID_START	0xffff000000000000ULL

काष्ठा ceph_osd_client अणु
	काष्ठा ceph_client     *client;

	काष्ठा ceph_osdmap     *osdmap;       /* current map */
	काष्ठा rw_semaphore    lock;

	काष्ठा rb_root         osds;          /* osds */
	काष्ठा list_head       osd_lru;       /* idle osds */
	spinlock_t             osd_lru_lock;
	u32		       epoch_barrier;
	काष्ठा ceph_osd        homeless_osd;
	atomic64_t             last_tid;      /* tid of last request */
	u64                    last_linger_id;
	काष्ठा rb_root         linger_requests; /* lingering requests */
	काष्ठा rb_root         map_checks;
	काष्ठा rb_root         linger_map_checks;
	atomic_t               num_requests;
	atomic_t               num_homeless;
	पूर्णांक                    पात_err;
	काष्ठा delayed_work    समयout_work;
	काष्ठा delayed_work    osds_समयout_work;
#अगर_घोषित CONFIG_DEBUG_FS
	काष्ठा dentry 	       *debugfs_file;
#पूर्ण_अगर

	mempool_t              *req_mempool;

	काष्ठा ceph_msgpool	msgpool_op;
	काष्ठा ceph_msgpool	msgpool_op_reply;

	काष्ठा workqueue_काष्ठा	*notअगरy_wq;
	काष्ठा workqueue_काष्ठा	*completion_wq;
पूर्ण;

अटल अंतरभूत bool ceph_osdmap_flag(काष्ठा ceph_osd_client *osdc, पूर्णांक flag)
अणु
	वापस osdc->osdmap->flags & flag;
पूर्ण

बाह्य पूर्णांक ceph_osdc_setup(व्योम);
बाह्य व्योम ceph_osdc_cleanup(व्योम);

बाह्य पूर्णांक ceph_osdc_init(काष्ठा ceph_osd_client *osdc,
			  काष्ठा ceph_client *client);
बाह्य व्योम ceph_osdc_stop(काष्ठा ceph_osd_client *osdc);
बाह्य व्योम ceph_osdc_reखोलो_osds(काष्ठा ceph_osd_client *osdc);

बाह्य व्योम ceph_osdc_handle_reply(काष्ठा ceph_osd_client *osdc,
				   काष्ठा ceph_msg *msg);
बाह्य व्योम ceph_osdc_handle_map(काष्ठा ceph_osd_client *osdc,
				 काष्ठा ceph_msg *msg);
व्योम ceph_osdc_update_epoch_barrier(काष्ठा ceph_osd_client *osdc, u32 eb);
व्योम ceph_osdc_पात_requests(काष्ठा ceph_osd_client *osdc, पूर्णांक err);
व्योम ceph_osdc_clear_पात_err(काष्ठा ceph_osd_client *osdc);

#घोषणा osd_req_op_data(oreq, whch, typ, fld)				\
(अणु									\
	काष्ठा ceph_osd_request *__oreq = (oreq);			\
	अचिन्हित पूर्णांक __whch = (whch);					\
	BUG_ON(__whch >= __oreq->r_num_ops);				\
	&__oreq->r_ops[__whch].typ.fld;					\
पूर्ण)

काष्ठा ceph_osd_req_op *osd_req_op_init(काष्ठा ceph_osd_request *osd_req,
			    अचिन्हित पूर्णांक which, u16 opcode, u32 flags);

बाह्य व्योम osd_req_op_raw_data_in_pages(काष्ठा ceph_osd_request *,
					अचिन्हित पूर्णांक which,
					काष्ठा page **pages, u64 length,
					u32 alignment, bool pages_from_pool,
					bool own_pages);

बाह्य व्योम osd_req_op_extent_init(काष्ठा ceph_osd_request *osd_req,
					अचिन्हित पूर्णांक which, u16 opcode,
					u64 offset, u64 length,
					u64 truncate_size, u32 truncate_seq);
बाह्य व्योम osd_req_op_extent_update(काष्ठा ceph_osd_request *osd_req,
					अचिन्हित पूर्णांक which, u64 length);
बाह्य व्योम osd_req_op_extent_dup_last(काष्ठा ceph_osd_request *osd_req,
				       अचिन्हित पूर्णांक which, u64 offset_inc);

बाह्य काष्ठा ceph_osd_data *osd_req_op_extent_osd_data(
					काष्ठा ceph_osd_request *osd_req,
					अचिन्हित पूर्णांक which);

बाह्य व्योम osd_req_op_extent_osd_data_pages(काष्ठा ceph_osd_request *,
					अचिन्हित पूर्णांक which,
					काष्ठा page **pages, u64 length,
					u32 alignment, bool pages_from_pool,
					bool own_pages);
बाह्य व्योम osd_req_op_extent_osd_data_pagelist(काष्ठा ceph_osd_request *,
					अचिन्हित पूर्णांक which,
					काष्ठा ceph_pagelist *pagelist);
#अगर_घोषित CONFIG_BLOCK
व्योम osd_req_op_extent_osd_data_bio(काष्ठा ceph_osd_request *osd_req,
				    अचिन्हित पूर्णांक which,
				    काष्ठा ceph_bio_iter *bio_pos,
				    u32 bio_length);
#पूर्ण_अगर /* CONFIG_BLOCK */
व्योम osd_req_op_extent_osd_data_bvecs(काष्ठा ceph_osd_request *osd_req,
				      अचिन्हित पूर्णांक which,
				      काष्ठा bio_vec *bvecs, u32 num_bvecs,
				      u32 bytes);
व्योम osd_req_op_extent_osd_data_bvec_pos(काष्ठा ceph_osd_request *osd_req,
					 अचिन्हित पूर्णांक which,
					 काष्ठा ceph_bvec_iter *bvec_pos);

बाह्य व्योम osd_req_op_cls_request_data_pagelist(काष्ठा ceph_osd_request *,
					अचिन्हित पूर्णांक which,
					काष्ठा ceph_pagelist *pagelist);
बाह्य व्योम osd_req_op_cls_request_data_pages(काष्ठा ceph_osd_request *,
					अचिन्हित पूर्णांक which,
					काष्ठा page **pages, u64 length,
					u32 alignment, bool pages_from_pool,
					bool own_pages);
व्योम osd_req_op_cls_request_data_bvecs(काष्ठा ceph_osd_request *osd_req,
				       अचिन्हित पूर्णांक which,
				       काष्ठा bio_vec *bvecs, u32 num_bvecs,
				       u32 bytes);
बाह्य व्योम osd_req_op_cls_response_data_pages(काष्ठा ceph_osd_request *,
					अचिन्हित पूर्णांक which,
					काष्ठा page **pages, u64 length,
					u32 alignment, bool pages_from_pool,
					bool own_pages);
पूर्णांक osd_req_op_cls_init(काष्ठा ceph_osd_request *osd_req, अचिन्हित पूर्णांक which,
			स्थिर अक्षर *class, स्थिर अक्षर *method);
बाह्य पूर्णांक osd_req_op_xattr_init(काष्ठा ceph_osd_request *osd_req, अचिन्हित पूर्णांक which,
				 u16 opcode, स्थिर अक्षर *name, स्थिर व्योम *value,
				 माप_प्रकार size, u8 cmp_op, u8 cmp_mode);
बाह्य व्योम osd_req_op_alloc_hपूर्णांक_init(काष्ठा ceph_osd_request *osd_req,
				       अचिन्हित पूर्णांक which,
				       u64 expected_object_size,
				       u64 expected_ग_लिखो_size,
				       u32 flags);

बाह्य काष्ठा ceph_osd_request *ceph_osdc_alloc_request(काष्ठा ceph_osd_client *osdc,
					       काष्ठा ceph_snap_context *snapc,
					       अचिन्हित पूर्णांक num_ops,
					       bool use_mempool,
					       gfp_t gfp_flags);
पूर्णांक ceph_osdc_alloc_messages(काष्ठा ceph_osd_request *req, gfp_t gfp);

बाह्य काष्ठा ceph_osd_request *ceph_osdc_new_request(काष्ठा ceph_osd_client *,
				      काष्ठा ceph_file_layout *layout,
				      काष्ठा ceph_vino vino,
				      u64 offset, u64 *len,
				      अचिन्हित पूर्णांक which, पूर्णांक num_ops,
				      पूर्णांक opcode, पूर्णांक flags,
				      काष्ठा ceph_snap_context *snapc,
				      u32 truncate_seq, u64 truncate_size,
				      bool use_mempool);

बाह्य व्योम ceph_osdc_get_request(काष्ठा ceph_osd_request *req);
बाह्य व्योम ceph_osdc_put_request(काष्ठा ceph_osd_request *req);

बाह्य पूर्णांक ceph_osdc_start_request(काष्ठा ceph_osd_client *osdc,
				   काष्ठा ceph_osd_request *req,
				   bool nofail);
बाह्य व्योम ceph_osdc_cancel_request(काष्ठा ceph_osd_request *req);
बाह्य पूर्णांक ceph_osdc_रुको_request(काष्ठा ceph_osd_client *osdc,
				  काष्ठा ceph_osd_request *req);
बाह्य व्योम ceph_osdc_sync(काष्ठा ceph_osd_client *osdc);

बाह्य व्योम ceph_osdc_flush_notअगरies(काष्ठा ceph_osd_client *osdc);
व्योम ceph_osdc_maybe_request_map(काष्ठा ceph_osd_client *osdc);

पूर्णांक ceph_osdc_call(काष्ठा ceph_osd_client *osdc,
		   काष्ठा ceph_object_id *oid,
		   काष्ठा ceph_object_locator *oloc,
		   स्थिर अक्षर *class, स्थिर अक्षर *method,
		   अचिन्हित पूर्णांक flags,
		   काष्ठा page *req_page, माप_प्रकार req_len,
		   काष्ठा page **resp_pages, माप_प्रकार *resp_len);

पूर्णांक ceph_osdc_copy_from(काष्ठा ceph_osd_client *osdc,
			u64 src_snapid, u64 src_version,
			काष्ठा ceph_object_id *src_oid,
			काष्ठा ceph_object_locator *src_oloc,
			u32 src_fadvise_flags,
			काष्ठा ceph_object_id *dst_oid,
			काष्ठा ceph_object_locator *dst_oloc,
			u32 dst_fadvise_flags,
			u32 truncate_seq, u64 truncate_size,
			u8 copy_from_flags);

/* watch/notअगरy */
काष्ठा ceph_osd_linger_request *
ceph_osdc_watch(काष्ठा ceph_osd_client *osdc,
		काष्ठा ceph_object_id *oid,
		काष्ठा ceph_object_locator *oloc,
		raकरोs_watchcb2_t wcb,
		raकरोs_watcherrcb_t errcb,
		व्योम *data);
पूर्णांक ceph_osdc_unwatch(काष्ठा ceph_osd_client *osdc,
		      काष्ठा ceph_osd_linger_request *lreq);

पूर्णांक ceph_osdc_notअगरy_ack(काष्ठा ceph_osd_client *osdc,
			 काष्ठा ceph_object_id *oid,
			 काष्ठा ceph_object_locator *oloc,
			 u64 notअगरy_id,
			 u64 cookie,
			 व्योम *payload,
			 u32 payload_len);
पूर्णांक ceph_osdc_notअगरy(काष्ठा ceph_osd_client *osdc,
		     काष्ठा ceph_object_id *oid,
		     काष्ठा ceph_object_locator *oloc,
		     व्योम *payload,
		     u32 payload_len,
		     u32 समयout,
		     काष्ठा page ***preply_pages,
		     माप_प्रकार *preply_len);
पूर्णांक ceph_osdc_watch_check(काष्ठा ceph_osd_client *osdc,
			  काष्ठा ceph_osd_linger_request *lreq);
पूर्णांक ceph_osdc_list_watchers(काष्ठा ceph_osd_client *osdc,
			    काष्ठा ceph_object_id *oid,
			    काष्ठा ceph_object_locator *oloc,
			    काष्ठा ceph_watch_item **watchers,
			    u32 *num_watchers);
#पूर्ण_अगर

