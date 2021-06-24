<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <linux/ceph/ceph_debug.h>

#समावेश <linux/module.h>
#समावेश <linux/err.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/mm.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>
#अगर_घोषित CONFIG_BLOCK
#समावेश <linux/bपन.स>
#पूर्ण_अगर

#समावेश <linux/ceph/ceph_features.h>
#समावेश <linux/ceph/libceph.h>
#समावेश <linux/ceph/osd_client.h>
#समावेश <linux/ceph/messenger.h>
#समावेश <linux/ceph/decode.h>
#समावेश <linux/ceph/auth.h>
#समावेश <linux/ceph/pagelist.h>
#समावेश <linux/ceph/striper.h>

#घोषणा OSD_OPREPLY_FRONT_LEN	512

अटल काष्ठा kmem_cache	*ceph_osd_request_cache;

अटल स्थिर काष्ठा ceph_connection_operations osd_con_ops;

/*
 * Implement client access to distributed object storage cluster.
 *
 * All data objects are stored within a cluster/cloud of OSDs, or
 * "object storage devices."  (Note that Ceph OSDs have _nothing_ to
 * करो with the T10 OSD extensions to SCSI.)  Ceph OSDs are simply
 * remote daemons serving up and coordinating consistent and safe
 * access to storage.
 *
 * Cluster membership and the mapping of data objects onto storage devices
 * are described by the osd map.
 *
 * We keep track of pending OSD requests (पढ़ो, ग_लिखो), resubmit
 * requests to dअगरferent OSDs when the cluster topology/data layout
 * change, or retry the affected requests when the communications
 * channel with an OSD is reset.
 */

अटल व्योम link_request(काष्ठा ceph_osd *osd, काष्ठा ceph_osd_request *req);
अटल व्योम unlink_request(काष्ठा ceph_osd *osd, काष्ठा ceph_osd_request *req);
अटल व्योम link_linger(काष्ठा ceph_osd *osd,
			काष्ठा ceph_osd_linger_request *lreq);
अटल व्योम unlink_linger(काष्ठा ceph_osd *osd,
			  काष्ठा ceph_osd_linger_request *lreq);
अटल व्योम clear_backoffs(काष्ठा ceph_osd *osd);

#अगर 1
अटल अंतरभूत bool rwsem_is_wrlocked(काष्ठा rw_semaphore *sem)
अणु
	bool wrlocked = true;

	अगर (unlikely(करोwn_पढ़ो_trylock(sem))) अणु
		wrlocked = false;
		up_पढ़ो(sem);
	पूर्ण

	वापस wrlocked;
पूर्ण
अटल अंतरभूत व्योम verअगरy_osdc_locked(काष्ठा ceph_osd_client *osdc)
अणु
	WARN_ON(!rwsem_is_locked(&osdc->lock));
पूर्ण
अटल अंतरभूत व्योम verअगरy_osdc_wrlocked(काष्ठा ceph_osd_client *osdc)
अणु
	WARN_ON(!rwsem_is_wrlocked(&osdc->lock));
पूर्ण
अटल अंतरभूत व्योम verअगरy_osd_locked(काष्ठा ceph_osd *osd)
अणु
	काष्ठा ceph_osd_client *osdc = osd->o_osdc;

	WARN_ON(!(mutex_is_locked(&osd->lock) &&
		  rwsem_is_locked(&osdc->lock)) &&
		!rwsem_is_wrlocked(&osdc->lock));
पूर्ण
अटल अंतरभूत व्योम verअगरy_lreq_locked(काष्ठा ceph_osd_linger_request *lreq)
अणु
	WARN_ON(!mutex_is_locked(&lreq->lock));
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम verअगरy_osdc_locked(काष्ठा ceph_osd_client *osdc) अणु पूर्ण
अटल अंतरभूत व्योम verअगरy_osdc_wrlocked(काष्ठा ceph_osd_client *osdc) अणु पूर्ण
अटल अंतरभूत व्योम verअगरy_osd_locked(काष्ठा ceph_osd *osd) अणु पूर्ण
अटल अंतरभूत व्योम verअगरy_lreq_locked(काष्ठा ceph_osd_linger_request *lreq) अणु पूर्ण
#पूर्ण_अगर

/*
 * calculate the mapping of a file extent onto an object, and fill out the
 * request accordingly.  लघुen extent as necessary अगर it crosses an
 * object boundary.
 *
 * fill osd op in request message.
 */
अटल पूर्णांक calc_layout(काष्ठा ceph_file_layout *layout, u64 off, u64 *plen,
			u64 *objnum, u64 *objoff, u64 *objlen)
अणु
	u64 orig_len = *plen;
	u32 xlen;

	/* object extent? */
	ceph_calc_file_object_mapping(layout, off, orig_len, objnum,
					  objoff, &xlen);
	*objlen = xlen;
	अगर (*objlen < orig_len) अणु
		*plen = *objlen;
		करोut(" skipping last %llu, final file extent %llu~%llu\n",
		     orig_len - *plen, off, *plen);
	पूर्ण

	करोut("calc_layout objnum=%llx %llu~%llu\n", *objnum, *objoff, *objlen);
	वापस 0;
पूर्ण

अटल व्योम ceph_osd_data_init(काष्ठा ceph_osd_data *osd_data)
अणु
	स_रखो(osd_data, 0, माप (*osd_data));
	osd_data->type = CEPH_OSD_DATA_TYPE_NONE;
पूर्ण

/*
 * Consumes @pages अगर @own_pages is true.
 */
अटल व्योम ceph_osd_data_pages_init(काष्ठा ceph_osd_data *osd_data,
			काष्ठा page **pages, u64 length, u32 alignment,
			bool pages_from_pool, bool own_pages)
अणु
	osd_data->type = CEPH_OSD_DATA_TYPE_PAGES;
	osd_data->pages = pages;
	osd_data->length = length;
	osd_data->alignment = alignment;
	osd_data->pages_from_pool = pages_from_pool;
	osd_data->own_pages = own_pages;
पूर्ण

/*
 * Consumes a ref on @pagelist.
 */
अटल व्योम ceph_osd_data_pagelist_init(काष्ठा ceph_osd_data *osd_data,
			काष्ठा ceph_pagelist *pagelist)
अणु
	osd_data->type = CEPH_OSD_DATA_TYPE_PAGELIST;
	osd_data->pagelist = pagelist;
पूर्ण

#अगर_घोषित CONFIG_BLOCK
अटल व्योम ceph_osd_data_bio_init(काष्ठा ceph_osd_data *osd_data,
				   काष्ठा ceph_bio_iter *bio_pos,
				   u32 bio_length)
अणु
	osd_data->type = CEPH_OSD_DATA_TYPE_BIO;
	osd_data->bio_pos = *bio_pos;
	osd_data->bio_length = bio_length;
पूर्ण
#पूर्ण_अगर /* CONFIG_BLOCK */

अटल व्योम ceph_osd_data_bvecs_init(काष्ठा ceph_osd_data *osd_data,
				     काष्ठा ceph_bvec_iter *bvec_pos,
				     u32 num_bvecs)
अणु
	osd_data->type = CEPH_OSD_DATA_TYPE_BVECS;
	osd_data->bvec_pos = *bvec_pos;
	osd_data->num_bvecs = num_bvecs;
पूर्ण

अटल काष्ठा ceph_osd_data *
osd_req_op_raw_data_in(काष्ठा ceph_osd_request *osd_req, अचिन्हित पूर्णांक which)
अणु
	BUG_ON(which >= osd_req->r_num_ops);

	वापस &osd_req->r_ops[which].raw_data_in;
पूर्ण

काष्ठा ceph_osd_data *
osd_req_op_extent_osd_data(काष्ठा ceph_osd_request *osd_req,
			अचिन्हित पूर्णांक which)
अणु
	वापस osd_req_op_data(osd_req, which, extent, osd_data);
पूर्ण
EXPORT_SYMBOL(osd_req_op_extent_osd_data);

व्योम osd_req_op_raw_data_in_pages(काष्ठा ceph_osd_request *osd_req,
			अचिन्हित पूर्णांक which, काष्ठा page **pages,
			u64 length, u32 alignment,
			bool pages_from_pool, bool own_pages)
अणु
	काष्ठा ceph_osd_data *osd_data;

	osd_data = osd_req_op_raw_data_in(osd_req, which);
	ceph_osd_data_pages_init(osd_data, pages, length, alignment,
				pages_from_pool, own_pages);
पूर्ण
EXPORT_SYMBOL(osd_req_op_raw_data_in_pages);

व्योम osd_req_op_extent_osd_data_pages(काष्ठा ceph_osd_request *osd_req,
			अचिन्हित पूर्णांक which, काष्ठा page **pages,
			u64 length, u32 alignment,
			bool pages_from_pool, bool own_pages)
अणु
	काष्ठा ceph_osd_data *osd_data;

	osd_data = osd_req_op_data(osd_req, which, extent, osd_data);
	ceph_osd_data_pages_init(osd_data, pages, length, alignment,
				pages_from_pool, own_pages);
पूर्ण
EXPORT_SYMBOL(osd_req_op_extent_osd_data_pages);

व्योम osd_req_op_extent_osd_data_pagelist(काष्ठा ceph_osd_request *osd_req,
			अचिन्हित पूर्णांक which, काष्ठा ceph_pagelist *pagelist)
अणु
	काष्ठा ceph_osd_data *osd_data;

	osd_data = osd_req_op_data(osd_req, which, extent, osd_data);
	ceph_osd_data_pagelist_init(osd_data, pagelist);
पूर्ण
EXPORT_SYMBOL(osd_req_op_extent_osd_data_pagelist);

#अगर_घोषित CONFIG_BLOCK
व्योम osd_req_op_extent_osd_data_bio(काष्ठा ceph_osd_request *osd_req,
				    अचिन्हित पूर्णांक which,
				    काष्ठा ceph_bio_iter *bio_pos,
				    u32 bio_length)
अणु
	काष्ठा ceph_osd_data *osd_data;

	osd_data = osd_req_op_data(osd_req, which, extent, osd_data);
	ceph_osd_data_bio_init(osd_data, bio_pos, bio_length);
पूर्ण
EXPORT_SYMBOL(osd_req_op_extent_osd_data_bio);
#पूर्ण_अगर /* CONFIG_BLOCK */

व्योम osd_req_op_extent_osd_data_bvecs(काष्ठा ceph_osd_request *osd_req,
				      अचिन्हित पूर्णांक which,
				      काष्ठा bio_vec *bvecs, u32 num_bvecs,
				      u32 bytes)
अणु
	काष्ठा ceph_osd_data *osd_data;
	काष्ठा ceph_bvec_iter it = अणु
		.bvecs = bvecs,
		.iter = अणु .bi_size = bytes पूर्ण,
	पूर्ण;

	osd_data = osd_req_op_data(osd_req, which, extent, osd_data);
	ceph_osd_data_bvecs_init(osd_data, &it, num_bvecs);
पूर्ण
EXPORT_SYMBOL(osd_req_op_extent_osd_data_bvecs);

व्योम osd_req_op_extent_osd_data_bvec_pos(काष्ठा ceph_osd_request *osd_req,
					 अचिन्हित पूर्णांक which,
					 काष्ठा ceph_bvec_iter *bvec_pos)
अणु
	काष्ठा ceph_osd_data *osd_data;

	osd_data = osd_req_op_data(osd_req, which, extent, osd_data);
	ceph_osd_data_bvecs_init(osd_data, bvec_pos, 0);
पूर्ण
EXPORT_SYMBOL(osd_req_op_extent_osd_data_bvec_pos);

अटल व्योम osd_req_op_cls_request_info_pagelist(
			काष्ठा ceph_osd_request *osd_req,
			अचिन्हित पूर्णांक which, काष्ठा ceph_pagelist *pagelist)
अणु
	काष्ठा ceph_osd_data *osd_data;

	osd_data = osd_req_op_data(osd_req, which, cls, request_info);
	ceph_osd_data_pagelist_init(osd_data, pagelist);
पूर्ण

व्योम osd_req_op_cls_request_data_pagelist(
			काष्ठा ceph_osd_request *osd_req,
			अचिन्हित पूर्णांक which, काष्ठा ceph_pagelist *pagelist)
अणु
	काष्ठा ceph_osd_data *osd_data;

	osd_data = osd_req_op_data(osd_req, which, cls, request_data);
	ceph_osd_data_pagelist_init(osd_data, pagelist);
	osd_req->r_ops[which].cls.indata_len += pagelist->length;
	osd_req->r_ops[which].indata_len += pagelist->length;
पूर्ण
EXPORT_SYMBOL(osd_req_op_cls_request_data_pagelist);

व्योम osd_req_op_cls_request_data_pages(काष्ठा ceph_osd_request *osd_req,
			अचिन्हित पूर्णांक which, काष्ठा page **pages, u64 length,
			u32 alignment, bool pages_from_pool, bool own_pages)
अणु
	काष्ठा ceph_osd_data *osd_data;

	osd_data = osd_req_op_data(osd_req, which, cls, request_data);
	ceph_osd_data_pages_init(osd_data, pages, length, alignment,
				pages_from_pool, own_pages);
	osd_req->r_ops[which].cls.indata_len += length;
	osd_req->r_ops[which].indata_len += length;
पूर्ण
EXPORT_SYMBOL(osd_req_op_cls_request_data_pages);

व्योम osd_req_op_cls_request_data_bvecs(काष्ठा ceph_osd_request *osd_req,
				       अचिन्हित पूर्णांक which,
				       काष्ठा bio_vec *bvecs, u32 num_bvecs,
				       u32 bytes)
अणु
	काष्ठा ceph_osd_data *osd_data;
	काष्ठा ceph_bvec_iter it = अणु
		.bvecs = bvecs,
		.iter = अणु .bi_size = bytes पूर्ण,
	पूर्ण;

	osd_data = osd_req_op_data(osd_req, which, cls, request_data);
	ceph_osd_data_bvecs_init(osd_data, &it, num_bvecs);
	osd_req->r_ops[which].cls.indata_len += bytes;
	osd_req->r_ops[which].indata_len += bytes;
पूर्ण
EXPORT_SYMBOL(osd_req_op_cls_request_data_bvecs);

व्योम osd_req_op_cls_response_data_pages(काष्ठा ceph_osd_request *osd_req,
			अचिन्हित पूर्णांक which, काष्ठा page **pages, u64 length,
			u32 alignment, bool pages_from_pool, bool own_pages)
अणु
	काष्ठा ceph_osd_data *osd_data;

	osd_data = osd_req_op_data(osd_req, which, cls, response_data);
	ceph_osd_data_pages_init(osd_data, pages, length, alignment,
				pages_from_pool, own_pages);
पूर्ण
EXPORT_SYMBOL(osd_req_op_cls_response_data_pages);

अटल u64 ceph_osd_data_length(काष्ठा ceph_osd_data *osd_data)
अणु
	चयन (osd_data->type) अणु
	हाल CEPH_OSD_DATA_TYPE_NONE:
		वापस 0;
	हाल CEPH_OSD_DATA_TYPE_PAGES:
		वापस osd_data->length;
	हाल CEPH_OSD_DATA_TYPE_PAGELIST:
		वापस (u64)osd_data->pagelist->length;
#अगर_घोषित CONFIG_BLOCK
	हाल CEPH_OSD_DATA_TYPE_BIO:
		वापस (u64)osd_data->bio_length;
#पूर्ण_अगर /* CONFIG_BLOCK */
	हाल CEPH_OSD_DATA_TYPE_BVECS:
		वापस osd_data->bvec_pos.iter.bi_size;
	शेष:
		WARN(true, "unrecognized data type %d\n", (पूर्णांक)osd_data->type);
		वापस 0;
	पूर्ण
पूर्ण

अटल व्योम ceph_osd_data_release(काष्ठा ceph_osd_data *osd_data)
अणु
	अगर (osd_data->type == CEPH_OSD_DATA_TYPE_PAGES && osd_data->own_pages) अणु
		पूर्णांक num_pages;

		num_pages = calc_pages_क्रम((u64)osd_data->alignment,
						(u64)osd_data->length);
		ceph_release_page_vector(osd_data->pages, num_pages);
	पूर्ण अन्यथा अगर (osd_data->type == CEPH_OSD_DATA_TYPE_PAGELIST) अणु
		ceph_pagelist_release(osd_data->pagelist);
	पूर्ण
	ceph_osd_data_init(osd_data);
पूर्ण

अटल व्योम osd_req_op_data_release(काष्ठा ceph_osd_request *osd_req,
			अचिन्हित पूर्णांक which)
अणु
	काष्ठा ceph_osd_req_op *op;

	BUG_ON(which >= osd_req->r_num_ops);
	op = &osd_req->r_ops[which];

	चयन (op->op) अणु
	हाल CEPH_OSD_OP_READ:
	हाल CEPH_OSD_OP_WRITE:
	हाल CEPH_OSD_OP_WRITEFULL:
		ceph_osd_data_release(&op->extent.osd_data);
		अवरोध;
	हाल CEPH_OSD_OP_CALL:
		ceph_osd_data_release(&op->cls.request_info);
		ceph_osd_data_release(&op->cls.request_data);
		ceph_osd_data_release(&op->cls.response_data);
		अवरोध;
	हाल CEPH_OSD_OP_SETXATTR:
	हाल CEPH_OSD_OP_CMPXATTR:
		ceph_osd_data_release(&op->xattr.osd_data);
		अवरोध;
	हाल CEPH_OSD_OP_STAT:
		ceph_osd_data_release(&op->raw_data_in);
		अवरोध;
	हाल CEPH_OSD_OP_NOTIFY_ACK:
		ceph_osd_data_release(&op->notअगरy_ack.request_data);
		अवरोध;
	हाल CEPH_OSD_OP_NOTIFY:
		ceph_osd_data_release(&op->notअगरy.request_data);
		ceph_osd_data_release(&op->notअगरy.response_data);
		अवरोध;
	हाल CEPH_OSD_OP_LIST_WATCHERS:
		ceph_osd_data_release(&op->list_watchers.response_data);
		अवरोध;
	हाल CEPH_OSD_OP_COPY_FROM2:
		ceph_osd_data_release(&op->copy_from.osd_data);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

/*
 * Assumes @t is zero-initialized.
 */
अटल व्योम target_init(काष्ठा ceph_osd_request_target *t)
अणु
	ceph_oid_init(&t->base_oid);
	ceph_oloc_init(&t->base_oloc);
	ceph_oid_init(&t->target_oid);
	ceph_oloc_init(&t->target_oloc);

	ceph_osds_init(&t->acting);
	ceph_osds_init(&t->up);
	t->size = -1;
	t->min_size = -1;

	t->osd = CEPH_HOMELESS_OSD;
पूर्ण

अटल व्योम target_copy(काष्ठा ceph_osd_request_target *dest,
			स्थिर काष्ठा ceph_osd_request_target *src)
अणु
	ceph_oid_copy(&dest->base_oid, &src->base_oid);
	ceph_oloc_copy(&dest->base_oloc, &src->base_oloc);
	ceph_oid_copy(&dest->target_oid, &src->target_oid);
	ceph_oloc_copy(&dest->target_oloc, &src->target_oloc);

	dest->pgid = src->pgid; /* काष्ठा */
	dest->spgid = src->spgid; /* काष्ठा */
	dest->pg_num = src->pg_num;
	dest->pg_num_mask = src->pg_num_mask;
	ceph_osds_copy(&dest->acting, &src->acting);
	ceph_osds_copy(&dest->up, &src->up);
	dest->size = src->size;
	dest->min_size = src->min_size;
	dest->sort_bitwise = src->sort_bitwise;
	dest->recovery_deletes = src->recovery_deletes;

	dest->flags = src->flags;
	dest->used_replica = src->used_replica;
	dest->छोड़ोd = src->छोड़ोd;

	dest->epoch = src->epoch;
	dest->last_क्रमce_resend = src->last_क्रमce_resend;

	dest->osd = src->osd;
पूर्ण

अटल व्योम target_destroy(काष्ठा ceph_osd_request_target *t)
अणु
	ceph_oid_destroy(&t->base_oid);
	ceph_oloc_destroy(&t->base_oloc);
	ceph_oid_destroy(&t->target_oid);
	ceph_oloc_destroy(&t->target_oloc);
पूर्ण

/*
 * requests
 */
अटल व्योम request_release_checks(काष्ठा ceph_osd_request *req)
अणु
	WARN_ON(!RB_EMPTY_NODE(&req->r_node));
	WARN_ON(!RB_EMPTY_NODE(&req->r_mc_node));
	WARN_ON(!list_empty(&req->r_निजी_item));
	WARN_ON(req->r_osd);
पूर्ण

अटल व्योम ceph_osdc_release_request(काष्ठा kref *kref)
अणु
	काष्ठा ceph_osd_request *req = container_of(kref,
					    काष्ठा ceph_osd_request, r_kref);
	अचिन्हित पूर्णांक which;

	करोut("%s %p (r_request %p r_reply %p)\n", __func__, req,
	     req->r_request, req->r_reply);
	request_release_checks(req);

	अगर (req->r_request)
		ceph_msg_put(req->r_request);
	अगर (req->r_reply)
		ceph_msg_put(req->r_reply);

	क्रम (which = 0; which < req->r_num_ops; which++)
		osd_req_op_data_release(req, which);

	target_destroy(&req->r_t);
	ceph_put_snap_context(req->r_snapc);

	अगर (req->r_mempool)
		mempool_मुक्त(req, req->r_osdc->req_mempool);
	अन्यथा अगर (req->r_num_ops <= CEPH_OSD_SLAB_OPS)
		kmem_cache_मुक्त(ceph_osd_request_cache, req);
	अन्यथा
		kमुक्त(req);
पूर्ण

व्योम ceph_osdc_get_request(काष्ठा ceph_osd_request *req)
अणु
	करोut("%s %p (was %d)\n", __func__, req,
	     kref_पढ़ो(&req->r_kref));
	kref_get(&req->r_kref);
पूर्ण
EXPORT_SYMBOL(ceph_osdc_get_request);

व्योम ceph_osdc_put_request(काष्ठा ceph_osd_request *req)
अणु
	अगर (req) अणु
		करोut("%s %p (was %d)\n", __func__, req,
		     kref_पढ़ो(&req->r_kref));
		kref_put(&req->r_kref, ceph_osdc_release_request);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(ceph_osdc_put_request);

अटल व्योम request_init(काष्ठा ceph_osd_request *req)
अणु
	/* req only, each op is zeroed in osd_req_op_init() */
	स_रखो(req, 0, माप(*req));

	kref_init(&req->r_kref);
	init_completion(&req->r_completion);
	RB_CLEAR_NODE(&req->r_node);
	RB_CLEAR_NODE(&req->r_mc_node);
	INIT_LIST_HEAD(&req->r_निजी_item);

	target_init(&req->r_t);
पूर्ण

/*
 * This is ugly, but it allows us to reuse linger registration and ping
 * requests, keeping the काष्ठाure of the code around send_lingerअणु_pingपूर्ण()
 * reasonable.  Setting up a min_nr=2 mempool क्रम each linger request
 * and dealing with copying ops (this blasts req only, watch op reमुख्यs
 * पूर्णांकact) isn't any better.
 */
अटल व्योम request_reinit(काष्ठा ceph_osd_request *req)
अणु
	काष्ठा ceph_osd_client *osdc = req->r_osdc;
	bool mempool = req->r_mempool;
	अचिन्हित पूर्णांक num_ops = req->r_num_ops;
	u64 snapid = req->r_snapid;
	काष्ठा ceph_snap_context *snapc = req->r_snapc;
	bool linger = req->r_linger;
	काष्ठा ceph_msg *request_msg = req->r_request;
	काष्ठा ceph_msg *reply_msg = req->r_reply;

	करोut("%s req %p\n", __func__, req);
	WARN_ON(kref_पढ़ो(&req->r_kref) != 1);
	request_release_checks(req);

	WARN_ON(kref_पढ़ो(&request_msg->kref) != 1);
	WARN_ON(kref_पढ़ो(&reply_msg->kref) != 1);
	target_destroy(&req->r_t);

	request_init(req);
	req->r_osdc = osdc;
	req->r_mempool = mempool;
	req->r_num_ops = num_ops;
	req->r_snapid = snapid;
	req->r_snapc = snapc;
	req->r_linger = linger;
	req->r_request = request_msg;
	req->r_reply = reply_msg;
पूर्ण

काष्ठा ceph_osd_request *ceph_osdc_alloc_request(काष्ठा ceph_osd_client *osdc,
					       काष्ठा ceph_snap_context *snapc,
					       अचिन्हित पूर्णांक num_ops,
					       bool use_mempool,
					       gfp_t gfp_flags)
अणु
	काष्ठा ceph_osd_request *req;

	अगर (use_mempool) अणु
		BUG_ON(num_ops > CEPH_OSD_SLAB_OPS);
		req = mempool_alloc(osdc->req_mempool, gfp_flags);
	पूर्ण अन्यथा अगर (num_ops <= CEPH_OSD_SLAB_OPS) अणु
		req = kmem_cache_alloc(ceph_osd_request_cache, gfp_flags);
	पूर्ण अन्यथा अणु
		BUG_ON(num_ops > CEPH_OSD_MAX_OPS);
		req = kदो_स्मृति(काष्ठा_size(req, r_ops, num_ops), gfp_flags);
	पूर्ण
	अगर (unlikely(!req))
		वापस शून्य;

	request_init(req);
	req->r_osdc = osdc;
	req->r_mempool = use_mempool;
	req->r_num_ops = num_ops;
	req->r_snapid = CEPH_NOSNAP;
	req->r_snapc = ceph_get_snap_context(snapc);

	करोut("%s req %p\n", __func__, req);
	वापस req;
पूर्ण
EXPORT_SYMBOL(ceph_osdc_alloc_request);

अटल पूर्णांक ceph_oloc_encoding_size(स्थिर काष्ठा ceph_object_locator *oloc)
अणु
	वापस 8 + 4 + 4 + 4 + (oloc->pool_ns ? oloc->pool_ns->len : 0);
पूर्ण

अटल पूर्णांक __ceph_osdc_alloc_messages(काष्ठा ceph_osd_request *req, gfp_t gfp,
				      पूर्णांक num_request_data_items,
				      पूर्णांक num_reply_data_items)
अणु
	काष्ठा ceph_osd_client *osdc = req->r_osdc;
	काष्ठा ceph_msg *msg;
	पूर्णांक msg_size;

	WARN_ON(req->r_request || req->r_reply);
	WARN_ON(ceph_oid_empty(&req->r_base_oid));
	WARN_ON(ceph_oloc_empty(&req->r_base_oloc));

	/* create request message */
	msg_size = CEPH_ENCODING_START_BLK_LEN +
			CEPH_PGID_ENCODING_LEN + 1; /* spgid */
	msg_size += 4 + 4 + 4; /* hash, osdmap_epoch, flags */
	msg_size += CEPH_ENCODING_START_BLK_LEN +
			माप(काष्ठा ceph_osd_reqid); /* reqid */
	msg_size += माप(काष्ठा ceph_blkin_trace_info); /* trace */
	msg_size += 4 + माप(काष्ठा ceph_बारpec); /* client_inc, mसमय */
	msg_size += CEPH_ENCODING_START_BLK_LEN +
			ceph_oloc_encoding_size(&req->r_base_oloc); /* oloc */
	msg_size += 4 + req->r_base_oid.name_len; /* oid */
	msg_size += 2 + req->r_num_ops * माप(काष्ठा ceph_osd_op);
	msg_size += 8; /* snapid */
	msg_size += 8; /* snap_seq */
	msg_size += 4 + 8 * (req->r_snapc ? req->r_snapc->num_snaps : 0);
	msg_size += 4 + 8; /* retry_attempt, features */

	अगर (req->r_mempool)
		msg = ceph_msgpool_get(&osdc->msgpool_op, msg_size,
				       num_request_data_items);
	अन्यथा
		msg = ceph_msg_new2(CEPH_MSG_OSD_OP, msg_size,
				    num_request_data_items, gfp, true);
	अगर (!msg)
		वापस -ENOMEM;

	स_रखो(msg->front.iov_base, 0, msg->front.iov_len);
	req->r_request = msg;

	/* create reply message */
	msg_size = OSD_OPREPLY_FRONT_LEN;
	msg_size += req->r_base_oid.name_len;
	msg_size += req->r_num_ops * माप(काष्ठा ceph_osd_op);

	अगर (req->r_mempool)
		msg = ceph_msgpool_get(&osdc->msgpool_op_reply, msg_size,
				       num_reply_data_items);
	अन्यथा
		msg = ceph_msg_new2(CEPH_MSG_OSD_OPREPLY, msg_size,
				    num_reply_data_items, gfp, true);
	अगर (!msg)
		वापस -ENOMEM;

	req->r_reply = msg;

	वापस 0;
पूर्ण

अटल bool osd_req_opcode_valid(u16 opcode)
अणु
	चयन (opcode) अणु
#घोषणा GENERATE_CASE(op, opcode, str)	हाल CEPH_OSD_OP_##op: वापस true;
__CEPH_FORALL_OSD_OPS(GENERATE_CASE)
#अघोषित GENERATE_CASE
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल व्योम get_num_data_items(काष्ठा ceph_osd_request *req,
			       पूर्णांक *num_request_data_items,
			       पूर्णांक *num_reply_data_items)
अणु
	काष्ठा ceph_osd_req_op *op;

	*num_request_data_items = 0;
	*num_reply_data_items = 0;

	क्रम (op = req->r_ops; op != &req->r_ops[req->r_num_ops]; op++) अणु
		चयन (op->op) अणु
		/* request */
		हाल CEPH_OSD_OP_WRITE:
		हाल CEPH_OSD_OP_WRITEFULL:
		हाल CEPH_OSD_OP_SETXATTR:
		हाल CEPH_OSD_OP_CMPXATTR:
		हाल CEPH_OSD_OP_NOTIFY_ACK:
		हाल CEPH_OSD_OP_COPY_FROM2:
			*num_request_data_items += 1;
			अवरोध;

		/* reply */
		हाल CEPH_OSD_OP_STAT:
		हाल CEPH_OSD_OP_READ:
		हाल CEPH_OSD_OP_LIST_WATCHERS:
			*num_reply_data_items += 1;
			अवरोध;

		/* both */
		हाल CEPH_OSD_OP_NOTIFY:
			*num_request_data_items += 1;
			*num_reply_data_items += 1;
			अवरोध;
		हाल CEPH_OSD_OP_CALL:
			*num_request_data_items += 2;
			*num_reply_data_items += 1;
			अवरोध;

		शेष:
			WARN_ON(!osd_req_opcode_valid(op->op));
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

/*
 * oid, oloc and OSD op opcode(s) must be filled in beक्रमe this function
 * is called.
 */
पूर्णांक ceph_osdc_alloc_messages(काष्ठा ceph_osd_request *req, gfp_t gfp)
अणु
	पूर्णांक num_request_data_items, num_reply_data_items;

	get_num_data_items(req, &num_request_data_items, &num_reply_data_items);
	वापस __ceph_osdc_alloc_messages(req, gfp, num_request_data_items,
					  num_reply_data_items);
पूर्ण
EXPORT_SYMBOL(ceph_osdc_alloc_messages);

/*
 * This is an osd op init function क्रम opcodes that have no data or
 * other inक्रमmation associated with them.  It also serves as a
 * common init routine क्रम all the other init functions, below.
 */
काष्ठा ceph_osd_req_op *
osd_req_op_init(काष्ठा ceph_osd_request *osd_req, अचिन्हित पूर्णांक which,
		 u16 opcode, u32 flags)
अणु
	काष्ठा ceph_osd_req_op *op;

	BUG_ON(which >= osd_req->r_num_ops);
	BUG_ON(!osd_req_opcode_valid(opcode));

	op = &osd_req->r_ops[which];
	स_रखो(op, 0, माप (*op));
	op->op = opcode;
	op->flags = flags;

	वापस op;
पूर्ण
EXPORT_SYMBOL(osd_req_op_init);

व्योम osd_req_op_extent_init(काष्ठा ceph_osd_request *osd_req,
				अचिन्हित पूर्णांक which, u16 opcode,
				u64 offset, u64 length,
				u64 truncate_size, u32 truncate_seq)
अणु
	काष्ठा ceph_osd_req_op *op = osd_req_op_init(osd_req, which,
						     opcode, 0);
	माप_प्रकार payload_len = 0;

	BUG_ON(opcode != CEPH_OSD_OP_READ && opcode != CEPH_OSD_OP_WRITE &&
	       opcode != CEPH_OSD_OP_WRITEFULL && opcode != CEPH_OSD_OP_ZERO &&
	       opcode != CEPH_OSD_OP_TRUNCATE);

	op->extent.offset = offset;
	op->extent.length = length;
	op->extent.truncate_size = truncate_size;
	op->extent.truncate_seq = truncate_seq;
	अगर (opcode == CEPH_OSD_OP_WRITE || opcode == CEPH_OSD_OP_WRITEFULL)
		payload_len += length;

	op->indata_len = payload_len;
पूर्ण
EXPORT_SYMBOL(osd_req_op_extent_init);

व्योम osd_req_op_extent_update(काष्ठा ceph_osd_request *osd_req,
				अचिन्हित पूर्णांक which, u64 length)
अणु
	काष्ठा ceph_osd_req_op *op;
	u64 previous;

	BUG_ON(which >= osd_req->r_num_ops);
	op = &osd_req->r_ops[which];
	previous = op->extent.length;

	अगर (length == previous)
		वापस;		/* Nothing to करो */
	BUG_ON(length > previous);

	op->extent.length = length;
	अगर (op->op == CEPH_OSD_OP_WRITE || op->op == CEPH_OSD_OP_WRITEFULL)
		op->indata_len -= previous - length;
पूर्ण
EXPORT_SYMBOL(osd_req_op_extent_update);

व्योम osd_req_op_extent_dup_last(काष्ठा ceph_osd_request *osd_req,
				अचिन्हित पूर्णांक which, u64 offset_inc)
अणु
	काष्ठा ceph_osd_req_op *op, *prev_op;

	BUG_ON(which + 1 >= osd_req->r_num_ops);

	prev_op = &osd_req->r_ops[which];
	op = osd_req_op_init(osd_req, which + 1, prev_op->op, prev_op->flags);
	/* dup previous one */
	op->indata_len = prev_op->indata_len;
	op->outdata_len = prev_op->outdata_len;
	op->extent = prev_op->extent;
	/* adjust offset */
	op->extent.offset += offset_inc;
	op->extent.length -= offset_inc;

	अगर (op->op == CEPH_OSD_OP_WRITE || op->op == CEPH_OSD_OP_WRITEFULL)
		op->indata_len -= offset_inc;
पूर्ण
EXPORT_SYMBOL(osd_req_op_extent_dup_last);

पूर्णांक osd_req_op_cls_init(काष्ठा ceph_osd_request *osd_req, अचिन्हित पूर्णांक which,
			स्थिर अक्षर *class, स्थिर अक्षर *method)
अणु
	काष्ठा ceph_osd_req_op *op;
	काष्ठा ceph_pagelist *pagelist;
	माप_प्रकार payload_len = 0;
	माप_प्रकार size;
	पूर्णांक ret;

	op = osd_req_op_init(osd_req, which, CEPH_OSD_OP_CALL, 0);

	pagelist = ceph_pagelist_alloc(GFP_NOFS);
	अगर (!pagelist)
		वापस -ENOMEM;

	op->cls.class_name = class;
	size = म_माप(class);
	BUG_ON(size > (माप_प्रकार) U8_MAX);
	op->cls.class_len = size;
	ret = ceph_pagelist_append(pagelist, class, size);
	अगर (ret)
		जाओ err_pagelist_मुक्त;
	payload_len += size;

	op->cls.method_name = method;
	size = म_माप(method);
	BUG_ON(size > (माप_प्रकार) U8_MAX);
	op->cls.method_len = size;
	ret = ceph_pagelist_append(pagelist, method, size);
	अगर (ret)
		जाओ err_pagelist_मुक्त;
	payload_len += size;

	osd_req_op_cls_request_info_pagelist(osd_req, which, pagelist);
	op->indata_len = payload_len;
	वापस 0;

err_pagelist_मुक्त:
	ceph_pagelist_release(pagelist);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(osd_req_op_cls_init);

पूर्णांक osd_req_op_xattr_init(काष्ठा ceph_osd_request *osd_req, अचिन्हित पूर्णांक which,
			  u16 opcode, स्थिर अक्षर *name, स्थिर व्योम *value,
			  माप_प्रकार size, u8 cmp_op, u8 cmp_mode)
अणु
	काष्ठा ceph_osd_req_op *op = osd_req_op_init(osd_req, which,
						     opcode, 0);
	काष्ठा ceph_pagelist *pagelist;
	माप_प्रकार payload_len;
	पूर्णांक ret;

	BUG_ON(opcode != CEPH_OSD_OP_SETXATTR && opcode != CEPH_OSD_OP_CMPXATTR);

	pagelist = ceph_pagelist_alloc(GFP_NOFS);
	अगर (!pagelist)
		वापस -ENOMEM;

	payload_len = म_माप(name);
	op->xattr.name_len = payload_len;
	ret = ceph_pagelist_append(pagelist, name, payload_len);
	अगर (ret)
		जाओ err_pagelist_मुक्त;

	op->xattr.value_len = size;
	ret = ceph_pagelist_append(pagelist, value, size);
	अगर (ret)
		जाओ err_pagelist_मुक्त;
	payload_len += size;

	op->xattr.cmp_op = cmp_op;
	op->xattr.cmp_mode = cmp_mode;

	ceph_osd_data_pagelist_init(&op->xattr.osd_data, pagelist);
	op->indata_len = payload_len;
	वापस 0;

err_pagelist_मुक्त:
	ceph_pagelist_release(pagelist);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(osd_req_op_xattr_init);

/*
 * @watch_opcode: CEPH_OSD_WATCH_OP_*
 */
अटल व्योम osd_req_op_watch_init(काष्ठा ceph_osd_request *req, पूर्णांक which,
				  u64 cookie, u8 watch_opcode)
अणु
	काष्ठा ceph_osd_req_op *op;

	op = osd_req_op_init(req, which, CEPH_OSD_OP_WATCH, 0);
	op->watch.cookie = cookie;
	op->watch.op = watch_opcode;
	op->watch.gen = 0;
पूर्ण

/*
 * @flags: CEPH_OSD_OP_ALLOC_HINT_FLAG_*
 */
व्योम osd_req_op_alloc_hपूर्णांक_init(काष्ठा ceph_osd_request *osd_req,
				अचिन्हित पूर्णांक which,
				u64 expected_object_size,
				u64 expected_ग_लिखो_size,
				u32 flags)
अणु
	काष्ठा ceph_osd_req_op *op;

	op = osd_req_op_init(osd_req, which, CEPH_OSD_OP_SETALLOCHINT, 0);
	op->alloc_hपूर्णांक.expected_object_size = expected_object_size;
	op->alloc_hपूर्णांक.expected_ग_लिखो_size = expected_ग_लिखो_size;
	op->alloc_hपूर्णांक.flags = flags;

	/*
	 * CEPH_OSD_OP_SETALLOCHINT op is advisory and thereक्रमe deemed
	 * not worth a feature bit.  Set FAILOK per-op flag to make
	 * sure older osds करोn't trip over an unsupported opcode.
	 */
	op->flags |= CEPH_OSD_OP_FLAG_FAILOK;
पूर्ण
EXPORT_SYMBOL(osd_req_op_alloc_hपूर्णांक_init);

अटल व्योम ceph_osdc_msg_data_add(काष्ठा ceph_msg *msg,
				काष्ठा ceph_osd_data *osd_data)
अणु
	u64 length = ceph_osd_data_length(osd_data);

	अगर (osd_data->type == CEPH_OSD_DATA_TYPE_PAGES) अणु
		BUG_ON(length > (u64) SIZE_MAX);
		अगर (length)
			ceph_msg_data_add_pages(msg, osd_data->pages,
					length, osd_data->alignment, false);
	पूर्ण अन्यथा अगर (osd_data->type == CEPH_OSD_DATA_TYPE_PAGELIST) अणु
		BUG_ON(!length);
		ceph_msg_data_add_pagelist(msg, osd_data->pagelist);
#अगर_घोषित CONFIG_BLOCK
	पूर्ण अन्यथा अगर (osd_data->type == CEPH_OSD_DATA_TYPE_BIO) अणु
		ceph_msg_data_add_bio(msg, &osd_data->bio_pos, length);
#पूर्ण_अगर
	पूर्ण अन्यथा अगर (osd_data->type == CEPH_OSD_DATA_TYPE_BVECS) अणु
		ceph_msg_data_add_bvecs(msg, &osd_data->bvec_pos);
	पूर्ण अन्यथा अणु
		BUG_ON(osd_data->type != CEPH_OSD_DATA_TYPE_NONE);
	पूर्ण
पूर्ण

अटल u32 osd_req_encode_op(काष्ठा ceph_osd_op *dst,
			     स्थिर काष्ठा ceph_osd_req_op *src)
अणु
	चयन (src->op) अणु
	हाल CEPH_OSD_OP_STAT:
		अवरोध;
	हाल CEPH_OSD_OP_READ:
	हाल CEPH_OSD_OP_WRITE:
	हाल CEPH_OSD_OP_WRITEFULL:
	हाल CEPH_OSD_OP_ZERO:
	हाल CEPH_OSD_OP_TRUNCATE:
		dst->extent.offset = cpu_to_le64(src->extent.offset);
		dst->extent.length = cpu_to_le64(src->extent.length);
		dst->extent.truncate_size =
			cpu_to_le64(src->extent.truncate_size);
		dst->extent.truncate_seq =
			cpu_to_le32(src->extent.truncate_seq);
		अवरोध;
	हाल CEPH_OSD_OP_CALL:
		dst->cls.class_len = src->cls.class_len;
		dst->cls.method_len = src->cls.method_len;
		dst->cls.indata_len = cpu_to_le32(src->cls.indata_len);
		अवरोध;
	हाल CEPH_OSD_OP_WATCH:
		dst->watch.cookie = cpu_to_le64(src->watch.cookie);
		dst->watch.ver = cpu_to_le64(0);
		dst->watch.op = src->watch.op;
		dst->watch.gen = cpu_to_le32(src->watch.gen);
		अवरोध;
	हाल CEPH_OSD_OP_NOTIFY_ACK:
		अवरोध;
	हाल CEPH_OSD_OP_NOTIFY:
		dst->notअगरy.cookie = cpu_to_le64(src->notअगरy.cookie);
		अवरोध;
	हाल CEPH_OSD_OP_LIST_WATCHERS:
		अवरोध;
	हाल CEPH_OSD_OP_SETALLOCHINT:
		dst->alloc_hपूर्णांक.expected_object_size =
		    cpu_to_le64(src->alloc_hपूर्णांक.expected_object_size);
		dst->alloc_hपूर्णांक.expected_ग_लिखो_size =
		    cpu_to_le64(src->alloc_hपूर्णांक.expected_ग_लिखो_size);
		dst->alloc_hपूर्णांक.flags = cpu_to_le32(src->alloc_hपूर्णांक.flags);
		अवरोध;
	हाल CEPH_OSD_OP_SETXATTR:
	हाल CEPH_OSD_OP_CMPXATTR:
		dst->xattr.name_len = cpu_to_le32(src->xattr.name_len);
		dst->xattr.value_len = cpu_to_le32(src->xattr.value_len);
		dst->xattr.cmp_op = src->xattr.cmp_op;
		dst->xattr.cmp_mode = src->xattr.cmp_mode;
		अवरोध;
	हाल CEPH_OSD_OP_CREATE:
	हाल CEPH_OSD_OP_DELETE:
		अवरोध;
	हाल CEPH_OSD_OP_COPY_FROM2:
		dst->copy_from.snapid = cpu_to_le64(src->copy_from.snapid);
		dst->copy_from.src_version =
			cpu_to_le64(src->copy_from.src_version);
		dst->copy_from.flags = src->copy_from.flags;
		dst->copy_from.src_fadvise_flags =
			cpu_to_le32(src->copy_from.src_fadvise_flags);
		अवरोध;
	शेष:
		pr_err("unsupported osd opcode %s\n",
			ceph_osd_op_name(src->op));
		WARN_ON(1);

		वापस 0;
	पूर्ण

	dst->op = cpu_to_le16(src->op);
	dst->flags = cpu_to_le32(src->flags);
	dst->payload_len = cpu_to_le32(src->indata_len);

	वापस src->indata_len;
पूर्ण

/*
 * build new request AND message, calculate layout, and adjust file
 * extent as needed.
 *
 * अगर the file was recently truncated, we include inक्रमmation about its
 * old and new size so that the object can be updated appropriately.  (we
 * aव्योम synchronously deleting truncated objects because it's slow.)
 */
काष्ठा ceph_osd_request *ceph_osdc_new_request(काष्ठा ceph_osd_client *osdc,
					       काष्ठा ceph_file_layout *layout,
					       काष्ठा ceph_vino vino,
					       u64 off, u64 *plen,
					       अचिन्हित पूर्णांक which, पूर्णांक num_ops,
					       पूर्णांक opcode, पूर्णांक flags,
					       काष्ठा ceph_snap_context *snapc,
					       u32 truncate_seq,
					       u64 truncate_size,
					       bool use_mempool)
अणु
	काष्ठा ceph_osd_request *req;
	u64 objnum = 0;
	u64 objoff = 0;
	u64 objlen = 0;
	पूर्णांक r;

	BUG_ON(opcode != CEPH_OSD_OP_READ && opcode != CEPH_OSD_OP_WRITE &&
	       opcode != CEPH_OSD_OP_ZERO && opcode != CEPH_OSD_OP_TRUNCATE &&
	       opcode != CEPH_OSD_OP_CREATE && opcode != CEPH_OSD_OP_DELETE);

	req = ceph_osdc_alloc_request(osdc, snapc, num_ops, use_mempool,
					GFP_NOFS);
	अगर (!req) अणु
		r = -ENOMEM;
		जाओ fail;
	पूर्ण

	/* calculate max ग_लिखो size */
	r = calc_layout(layout, off, plen, &objnum, &objoff, &objlen);
	अगर (r)
		जाओ fail;

	अगर (opcode == CEPH_OSD_OP_CREATE || opcode == CEPH_OSD_OP_DELETE) अणु
		osd_req_op_init(req, which, opcode, 0);
	पूर्ण अन्यथा अणु
		u32 object_size = layout->object_size;
		u32 object_base = off - objoff;
		अगर (!(truncate_seq == 1 && truncate_size == -1ULL)) अणु
			अगर (truncate_size <= object_base) अणु
				truncate_size = 0;
			पूर्ण अन्यथा अणु
				truncate_size -= object_base;
				अगर (truncate_size > object_size)
					truncate_size = object_size;
			पूर्ण
		पूर्ण
		osd_req_op_extent_init(req, which, opcode, objoff, objlen,
				       truncate_size, truncate_seq);
	पूर्ण

	req->r_base_oloc.pool = layout->pool_id;
	req->r_base_oloc.pool_ns = ceph_try_get_string(layout->pool_ns);
	ceph_oid_म_लिखो(&req->r_base_oid, "%llx.%08llx", vino.ino, objnum);
	req->r_flags = flags | osdc->client->options->पढ़ो_from_replica;

	req->r_snapid = vino.snap;
	अगर (flags & CEPH_OSD_FLAG_WRITE)
		req->r_data_offset = off;

	अगर (num_ops > 1)
		/*
		 * This is a special हाल क्रम ceph_ग_लिखोpages_start(), but it
		 * also covers ceph_unअंतरभूत_data().  If more multi-op request
		 * use हालs emerge, we will need a separate helper.
		 */
		r = __ceph_osdc_alloc_messages(req, GFP_NOFS, num_ops, 0);
	अन्यथा
		r = ceph_osdc_alloc_messages(req, GFP_NOFS);
	अगर (r)
		जाओ fail;

	वापस req;

fail:
	ceph_osdc_put_request(req);
	वापस ERR_PTR(r);
पूर्ण
EXPORT_SYMBOL(ceph_osdc_new_request);

/*
 * We keep osd requests in an rbtree, sorted by ->r_tid.
 */
DEFINE_RB_FUNCS(request, काष्ठा ceph_osd_request, r_tid, r_node)
DEFINE_RB_FUNCS(request_mc, काष्ठा ceph_osd_request, r_tid, r_mc_node)

/*
 * Call @fn on each OSD request as दीर्घ as @fn वापसs 0.
 */
अटल व्योम क्रम_each_request(काष्ठा ceph_osd_client *osdc,
			पूर्णांक (*fn)(काष्ठा ceph_osd_request *req, व्योम *arg),
			व्योम *arg)
अणु
	काष्ठा rb_node *n, *p;

	क्रम (n = rb_first(&osdc->osds); n; n = rb_next(n)) अणु
		काष्ठा ceph_osd *osd = rb_entry(n, काष्ठा ceph_osd, o_node);

		क्रम (p = rb_first(&osd->o_requests); p; ) अणु
			काष्ठा ceph_osd_request *req =
			    rb_entry(p, काष्ठा ceph_osd_request, r_node);

			p = rb_next(p);
			अगर (fn(req, arg))
				वापस;
		पूर्ण
	पूर्ण

	क्रम (p = rb_first(&osdc->homeless_osd.o_requests); p; ) अणु
		काष्ठा ceph_osd_request *req =
		    rb_entry(p, काष्ठा ceph_osd_request, r_node);

		p = rb_next(p);
		अगर (fn(req, arg))
			वापस;
	पूर्ण
पूर्ण

अटल bool osd_homeless(काष्ठा ceph_osd *osd)
अणु
	वापस osd->o_osd == CEPH_HOMELESS_OSD;
पूर्ण

अटल bool osd_रेजिस्टरed(काष्ठा ceph_osd *osd)
अणु
	verअगरy_osdc_locked(osd->o_osdc);

	वापस !RB_EMPTY_NODE(&osd->o_node);
पूर्ण

/*
 * Assumes @osd is zero-initialized.
 */
अटल व्योम osd_init(काष्ठा ceph_osd *osd)
अणु
	refcount_set(&osd->o_ref, 1);
	RB_CLEAR_NODE(&osd->o_node);
	osd->o_requests = RB_ROOT;
	osd->o_linger_requests = RB_ROOT;
	osd->o_backoff_mappings = RB_ROOT;
	osd->o_backoffs_by_id = RB_ROOT;
	INIT_LIST_HEAD(&osd->o_osd_lru);
	INIT_LIST_HEAD(&osd->o_keepalive_item);
	osd->o_incarnation = 1;
	mutex_init(&osd->lock);
पूर्ण

अटल व्योम osd_cleanup(काष्ठा ceph_osd *osd)
अणु
	WARN_ON(!RB_EMPTY_NODE(&osd->o_node));
	WARN_ON(!RB_EMPTY_ROOT(&osd->o_requests));
	WARN_ON(!RB_EMPTY_ROOT(&osd->o_linger_requests));
	WARN_ON(!RB_EMPTY_ROOT(&osd->o_backoff_mappings));
	WARN_ON(!RB_EMPTY_ROOT(&osd->o_backoffs_by_id));
	WARN_ON(!list_empty(&osd->o_osd_lru));
	WARN_ON(!list_empty(&osd->o_keepalive_item));

	अगर (osd->o_auth.authorizer) अणु
		WARN_ON(osd_homeless(osd));
		ceph_auth_destroy_authorizer(osd->o_auth.authorizer);
	पूर्ण
पूर्ण

/*
 * Track खोलो sessions with osds.
 */
अटल काष्ठा ceph_osd *create_osd(काष्ठा ceph_osd_client *osdc, पूर्णांक onum)
अणु
	काष्ठा ceph_osd *osd;

	WARN_ON(onum == CEPH_HOMELESS_OSD);

	osd = kzalloc(माप(*osd), GFP_NOIO | __GFP_NOFAIL);
	osd_init(osd);
	osd->o_osdc = osdc;
	osd->o_osd = onum;

	ceph_con_init(&osd->o_con, osd, &osd_con_ops, &osdc->client->msgr);

	वापस osd;
पूर्ण

अटल काष्ठा ceph_osd *get_osd(काष्ठा ceph_osd *osd)
अणु
	अगर (refcount_inc_not_zero(&osd->o_ref)) अणु
		करोut("get_osd %p %d -> %d\n", osd, refcount_पढ़ो(&osd->o_ref)-1,
		     refcount_पढ़ो(&osd->o_ref));
		वापस osd;
	पूर्ण अन्यथा अणु
		करोut("get_osd %p FAIL\n", osd);
		वापस शून्य;
	पूर्ण
पूर्ण

अटल व्योम put_osd(काष्ठा ceph_osd *osd)
अणु
	करोut("put_osd %p %d -> %d\n", osd, refcount_पढ़ो(&osd->o_ref),
	     refcount_पढ़ो(&osd->o_ref) - 1);
	अगर (refcount_dec_and_test(&osd->o_ref)) अणु
		osd_cleanup(osd);
		kमुक्त(osd);
	पूर्ण
पूर्ण

DEFINE_RB_FUNCS(osd, काष्ठा ceph_osd, o_osd, o_node)

अटल व्योम __move_osd_to_lru(काष्ठा ceph_osd *osd)
अणु
	काष्ठा ceph_osd_client *osdc = osd->o_osdc;

	करोut("%s osd %p osd%d\n", __func__, osd, osd->o_osd);
	BUG_ON(!list_empty(&osd->o_osd_lru));

	spin_lock(&osdc->osd_lru_lock);
	list_add_tail(&osd->o_osd_lru, &osdc->osd_lru);
	spin_unlock(&osdc->osd_lru_lock);

	osd->lru_ttl = jअगरfies + osdc->client->options->osd_idle_ttl;
पूर्ण

अटल व्योम maybe_move_osd_to_lru(काष्ठा ceph_osd *osd)
अणु
	अगर (RB_EMPTY_ROOT(&osd->o_requests) &&
	    RB_EMPTY_ROOT(&osd->o_linger_requests))
		__move_osd_to_lru(osd);
पूर्ण

अटल व्योम __हटाओ_osd_from_lru(काष्ठा ceph_osd *osd)
अणु
	काष्ठा ceph_osd_client *osdc = osd->o_osdc;

	करोut("%s osd %p osd%d\n", __func__, osd, osd->o_osd);

	spin_lock(&osdc->osd_lru_lock);
	अगर (!list_empty(&osd->o_osd_lru))
		list_del_init(&osd->o_osd_lru);
	spin_unlock(&osdc->osd_lru_lock);
पूर्ण

/*
 * Close the connection and assign any leftover requests to the
 * homeless session.
 */
अटल व्योम बंद_osd(काष्ठा ceph_osd *osd)
अणु
	काष्ठा ceph_osd_client *osdc = osd->o_osdc;
	काष्ठा rb_node *n;

	verअगरy_osdc_wrlocked(osdc);
	करोut("%s osd %p osd%d\n", __func__, osd, osd->o_osd);

	ceph_con_बंद(&osd->o_con);

	क्रम (n = rb_first(&osd->o_requests); n; ) अणु
		काष्ठा ceph_osd_request *req =
		    rb_entry(n, काष्ठा ceph_osd_request, r_node);

		n = rb_next(n); /* unlink_request() */

		करोut(" reassigning req %p tid %llu\n", req, req->r_tid);
		unlink_request(osd, req);
		link_request(&osdc->homeless_osd, req);
	पूर्ण
	क्रम (n = rb_first(&osd->o_linger_requests); n; ) अणु
		काष्ठा ceph_osd_linger_request *lreq =
		    rb_entry(n, काष्ठा ceph_osd_linger_request, node);

		n = rb_next(n); /* unlink_linger() */

		करोut(" reassigning lreq %p linger_id %llu\n", lreq,
		     lreq->linger_id);
		unlink_linger(osd, lreq);
		link_linger(&osdc->homeless_osd, lreq);
	पूर्ण
	clear_backoffs(osd);

	__हटाओ_osd_from_lru(osd);
	erase_osd(&osdc->osds, osd);
	put_osd(osd);
पूर्ण

/*
 * reset osd connect
 */
अटल पूर्णांक reखोलो_osd(काष्ठा ceph_osd *osd)
अणु
	काष्ठा ceph_entity_addr *peer_addr;

	करोut("%s osd %p osd%d\n", __func__, osd, osd->o_osd);

	अगर (RB_EMPTY_ROOT(&osd->o_requests) &&
	    RB_EMPTY_ROOT(&osd->o_linger_requests)) अणु
		बंद_osd(osd);
		वापस -ENODEV;
	पूर्ण

	peer_addr = &osd->o_osdc->osdmap->osd_addr[osd->o_osd];
	अगर (!स_भेद(peer_addr, &osd->o_con.peer_addr, माप (*peer_addr)) &&
			!ceph_con_खोलोed(&osd->o_con)) अणु
		काष्ठा rb_node *n;

		करोut("osd addr hasn't changed and connection never opened, "
		     "letting msgr retry\n");
		/* touch each r_stamp क्रम handle_समयout()'s benfit */
		क्रम (n = rb_first(&osd->o_requests); n; n = rb_next(n)) अणु
			काष्ठा ceph_osd_request *req =
			    rb_entry(n, काष्ठा ceph_osd_request, r_node);
			req->r_stamp = jअगरfies;
		पूर्ण

		वापस -EAGAIN;
	पूर्ण

	ceph_con_बंद(&osd->o_con);
	ceph_con_खोलो(&osd->o_con, CEPH_ENTITY_TYPE_OSD, osd->o_osd, peer_addr);
	osd->o_incarnation++;

	वापस 0;
पूर्ण

अटल काष्ठा ceph_osd *lookup_create_osd(काष्ठा ceph_osd_client *osdc, पूर्णांक o,
					  bool wrlocked)
अणु
	काष्ठा ceph_osd *osd;

	अगर (wrlocked)
		verअगरy_osdc_wrlocked(osdc);
	अन्यथा
		verअगरy_osdc_locked(osdc);

	अगर (o != CEPH_HOMELESS_OSD)
		osd = lookup_osd(&osdc->osds, o);
	अन्यथा
		osd = &osdc->homeless_osd;
	अगर (!osd) अणु
		अगर (!wrlocked)
			वापस ERR_PTR(-EAGAIN);

		osd = create_osd(osdc, o);
		insert_osd(&osdc->osds, osd);
		ceph_con_खोलो(&osd->o_con, CEPH_ENTITY_TYPE_OSD, osd->o_osd,
			      &osdc->osdmap->osd_addr[osd->o_osd]);
	पूर्ण

	करोut("%s osdc %p osd%d -> osd %p\n", __func__, osdc, o, osd);
	वापस osd;
पूर्ण

/*
 * Create request <-> OSD session relation.
 *
 * @req has to be asचिन्हित a tid, @osd may be homeless.
 */
अटल व्योम link_request(काष्ठा ceph_osd *osd, काष्ठा ceph_osd_request *req)
अणु
	verअगरy_osd_locked(osd);
	WARN_ON(!req->r_tid || req->r_osd);
	करोut("%s osd %p osd%d req %p tid %llu\n", __func__, osd, osd->o_osd,
	     req, req->r_tid);

	अगर (!osd_homeless(osd))
		__हटाओ_osd_from_lru(osd);
	अन्यथा
		atomic_inc(&osd->o_osdc->num_homeless);

	get_osd(osd);
	insert_request(&osd->o_requests, req);
	req->r_osd = osd;
पूर्ण

अटल व्योम unlink_request(काष्ठा ceph_osd *osd, काष्ठा ceph_osd_request *req)
अणु
	verअगरy_osd_locked(osd);
	WARN_ON(req->r_osd != osd);
	करोut("%s osd %p osd%d req %p tid %llu\n", __func__, osd, osd->o_osd,
	     req, req->r_tid);

	req->r_osd = शून्य;
	erase_request(&osd->o_requests, req);
	put_osd(osd);

	अगर (!osd_homeless(osd))
		maybe_move_osd_to_lru(osd);
	अन्यथा
		atomic_dec(&osd->o_osdc->num_homeless);
पूर्ण

अटल bool __pool_full(काष्ठा ceph_pg_pool_info *pi)
अणु
	वापस pi->flags & CEPH_POOL_FLAG_FULL;
पूर्ण

अटल bool have_pool_full(काष्ठा ceph_osd_client *osdc)
अणु
	काष्ठा rb_node *n;

	क्रम (n = rb_first(&osdc->osdmap->pg_pools); n; n = rb_next(n)) अणु
		काष्ठा ceph_pg_pool_info *pi =
		    rb_entry(n, काष्ठा ceph_pg_pool_info, node);

		अगर (__pool_full(pi))
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल bool pool_full(काष्ठा ceph_osd_client *osdc, s64 pool_id)
अणु
	काष्ठा ceph_pg_pool_info *pi;

	pi = ceph_pg_pool_by_id(osdc->osdmap, pool_id);
	अगर (!pi)
		वापस false;

	वापस __pool_full(pi);
पूर्ण

/*
 * Returns whether a request should be blocked from being sent
 * based on the current osdmap and osd_client settings.
 */
अटल bool target_should_be_छोड़ोd(काष्ठा ceph_osd_client *osdc,
				    स्थिर काष्ठा ceph_osd_request_target *t,
				    काष्ठा ceph_pg_pool_info *pi)
अणु
	bool छोड़ोrd = ceph_osdmap_flag(osdc, CEPH_OSDMAP_PAUSERD);
	bool छोड़ोwr = ceph_osdmap_flag(osdc, CEPH_OSDMAP_PAUSEWR) ||
		       ceph_osdmap_flag(osdc, CEPH_OSDMAP_FULL) ||
		       __pool_full(pi);

	WARN_ON(pi->id != t->target_oloc.pool);
	वापस ((t->flags & CEPH_OSD_FLAG_READ) && छोड़ोrd) ||
	       ((t->flags & CEPH_OSD_FLAG_WRITE) && छोड़ोwr) ||
	       (osdc->osdmap->epoch < osdc->epoch_barrier);
पूर्ण

अटल पूर्णांक pick_अक्रमom_replica(स्थिर काष्ठा ceph_osds *acting)
अणु
	पूर्णांक i = pअक्रमom_u32() % acting->size;

	करोut("%s picked osd%d, primary osd%d\n", __func__,
	     acting->osds[i], acting->primary);
	वापस i;
पूर्ण

/*
 * Picks the बंदst replica based on client's location given by
 * crush_location option.  Prefers the primary अगर the locality is
 * the same.
 */
अटल पूर्णांक pick_बंदst_replica(काष्ठा ceph_osd_client *osdc,
				स्थिर काष्ठा ceph_osds *acting)
अणु
	काष्ठा ceph_options *opt = osdc->client->options;
	पूर्णांक best_i, best_locality;
	पूर्णांक i = 0, locality;

	करो अणु
		locality = ceph_get_crush_locality(osdc->osdmap,
						   acting->osds[i],
						   &opt->crush_locs);
		अगर (i == 0 ||
		    (locality >= 0 && best_locality < 0) ||
		    (locality >= 0 && best_locality >= 0 &&
		     locality < best_locality)) अणु
			best_i = i;
			best_locality = locality;
		पूर्ण
	पूर्ण जबतक (++i < acting->size);

	करोut("%s picked osd%d with locality %d, primary osd%d\n", __func__,
	     acting->osds[best_i], best_locality, acting->primary);
	वापस best_i;
पूर्ण

क्रमागत calc_target_result अणु
	CALC_TARGET_NO_ACTION = 0,
	CALC_TARGET_NEED_RESEND,
	CALC_TARGET_POOL_DNE,
पूर्ण;

अटल क्रमागत calc_target_result calc_target(काष्ठा ceph_osd_client *osdc,
					   काष्ठा ceph_osd_request_target *t,
					   bool any_change)
अणु
	काष्ठा ceph_pg_pool_info *pi;
	काष्ठा ceph_pg pgid, last_pgid;
	काष्ठा ceph_osds up, acting;
	bool is_पढ़ो = t->flags & CEPH_OSD_FLAG_READ;
	bool is_ग_लिखो = t->flags & CEPH_OSD_FLAG_WRITE;
	bool क्रमce_resend = false;
	bool unछोड़ोd = false;
	bool legacy_change = false;
	bool split = false;
	bool sort_bitwise = ceph_osdmap_flag(osdc, CEPH_OSDMAP_SORTBITWISE);
	bool recovery_deletes = ceph_osdmap_flag(osdc,
						 CEPH_OSDMAP_RECOVERY_DELETES);
	क्रमागत calc_target_result ct_res;

	t->epoch = osdc->osdmap->epoch;
	pi = ceph_pg_pool_by_id(osdc->osdmap, t->base_oloc.pool);
	अगर (!pi) अणु
		t->osd = CEPH_HOMELESS_OSD;
		ct_res = CALC_TARGET_POOL_DNE;
		जाओ out;
	पूर्ण

	अगर (osdc->osdmap->epoch == pi->last_क्रमce_request_resend) अणु
		अगर (t->last_क्रमce_resend < pi->last_क्रमce_request_resend) अणु
			t->last_क्रमce_resend = pi->last_क्रमce_request_resend;
			क्रमce_resend = true;
		पूर्ण अन्यथा अगर (t->last_क्रमce_resend == 0) अणु
			क्रमce_resend = true;
		पूर्ण
	पूर्ण

	/* apply tiering */
	ceph_oid_copy(&t->target_oid, &t->base_oid);
	ceph_oloc_copy(&t->target_oloc, &t->base_oloc);
	अगर ((t->flags & CEPH_OSD_FLAG_IGNORE_OVERLAY) == 0) अणु
		अगर (is_पढ़ो && pi->पढ़ो_tier >= 0)
			t->target_oloc.pool = pi->पढ़ो_tier;
		अगर (is_ग_लिखो && pi->ग_लिखो_tier >= 0)
			t->target_oloc.pool = pi->ग_लिखो_tier;

		pi = ceph_pg_pool_by_id(osdc->osdmap, t->target_oloc.pool);
		अगर (!pi) अणु
			t->osd = CEPH_HOMELESS_OSD;
			ct_res = CALC_TARGET_POOL_DNE;
			जाओ out;
		पूर्ण
	पूर्ण

	__ceph_object_locator_to_pg(pi, &t->target_oid, &t->target_oloc, &pgid);
	last_pgid.pool = pgid.pool;
	last_pgid.seed = ceph_stable_mod(pgid.seed, t->pg_num, t->pg_num_mask);

	ceph_pg_to_up_acting_osds(osdc->osdmap, pi, &pgid, &up, &acting);
	अगर (any_change &&
	    ceph_is_new_पूर्णांकerval(&t->acting,
				 &acting,
				 &t->up,
				 &up,
				 t->size,
				 pi->size,
				 t->min_size,
				 pi->min_size,
				 t->pg_num,
				 pi->pg_num,
				 t->sort_bitwise,
				 sort_bitwise,
				 t->recovery_deletes,
				 recovery_deletes,
				 &last_pgid))
		क्रमce_resend = true;

	अगर (t->छोड़ोd && !target_should_be_छोड़ोd(osdc, t, pi)) अणु
		t->छोड़ोd = false;
		unछोड़ोd = true;
	पूर्ण
	legacy_change = ceph_pg_compare(&t->pgid, &pgid) ||
			ceph_osds_changed(&t->acting, &acting,
					  t->used_replica || any_change);
	अगर (t->pg_num)
		split = ceph_pg_is_split(&last_pgid, t->pg_num, pi->pg_num);

	अगर (legacy_change || क्रमce_resend || split) अणु
		t->pgid = pgid; /* काष्ठा */
		ceph_pg_to_primary_shard(osdc->osdmap, pi, &pgid, &t->spgid);
		ceph_osds_copy(&t->acting, &acting);
		ceph_osds_copy(&t->up, &up);
		t->size = pi->size;
		t->min_size = pi->min_size;
		t->pg_num = pi->pg_num;
		t->pg_num_mask = pi->pg_num_mask;
		t->sort_bitwise = sort_bitwise;
		t->recovery_deletes = recovery_deletes;

		अगर ((t->flags & (CEPH_OSD_FLAG_BALANCE_READS |
				 CEPH_OSD_FLAG_LOCALIZE_READS)) &&
		    !is_ग_लिखो && pi->type == CEPH_POOL_TYPE_REP &&
		    acting.size > 1) अणु
			पूर्णांक pos;

			WARN_ON(!is_पढ़ो || acting.osds[0] != acting.primary);
			अगर (t->flags & CEPH_OSD_FLAG_BALANCE_READS) अणु
				pos = pick_अक्रमom_replica(&acting);
			पूर्ण अन्यथा अणु
				pos = pick_बंदst_replica(osdc, &acting);
			पूर्ण
			t->osd = acting.osds[pos];
			t->used_replica = pos > 0;
		पूर्ण अन्यथा अणु
			t->osd = acting.primary;
			t->used_replica = false;
		पूर्ण
	पूर्ण

	अगर (unछोड़ोd || legacy_change || क्रमce_resend || split)
		ct_res = CALC_TARGET_NEED_RESEND;
	अन्यथा
		ct_res = CALC_TARGET_NO_ACTION;

out:
	करोut("%s t %p -> %d%d%d%d ct_res %d osd%d\n", __func__, t, unछोड़ोd,
	     legacy_change, क्रमce_resend, split, ct_res, t->osd);
	वापस ct_res;
पूर्ण

अटल काष्ठा ceph_spg_mapping *alloc_spg_mapping(व्योम)
अणु
	काष्ठा ceph_spg_mapping *spg;

	spg = kदो_स्मृति(माप(*spg), GFP_NOIO);
	अगर (!spg)
		वापस शून्य;

	RB_CLEAR_NODE(&spg->node);
	spg->backoffs = RB_ROOT;
	वापस spg;
पूर्ण

अटल व्योम मुक्त_spg_mapping(काष्ठा ceph_spg_mapping *spg)
अणु
	WARN_ON(!RB_EMPTY_NODE(&spg->node));
	WARN_ON(!RB_EMPTY_ROOT(&spg->backoffs));

	kमुक्त(spg);
पूर्ण

/*
 * rbtree of ceph_spg_mapping क्रम handling map<spg_t, ...>, similar to
 * ceph_pg_mapping.  Used to track OSD backoffs -- a backoff [range] is
 * defined only within a specअगरic spgid; it करोes not pass anything to
 * children on split, or to another primary.
 */
DEFINE_RB_FUNCS2(spg_mapping, काष्ठा ceph_spg_mapping, spgid, ceph_spg_compare,
		 RB_BYPTR, स्थिर काष्ठा ceph_spg *, node)

अटल u64 hoid_get_bitwise_key(स्थिर काष्ठा ceph_hobject_id *hoid)
अणु
	वापस hoid->is_max ? 0x100000000ull : hoid->hash_reverse_bits;
पूर्ण

अटल व्योम hoid_get_effective_key(स्थिर काष्ठा ceph_hobject_id *hoid,
				   व्योम **pkey, माप_प्रकार *pkey_len)
अणु
	अगर (hoid->key_len) अणु
		*pkey = hoid->key;
		*pkey_len = hoid->key_len;
	पूर्ण अन्यथा अणु
		*pkey = hoid->oid;
		*pkey_len = hoid->oid_len;
	पूर्ण
पूर्ण

अटल पूर्णांक compare_names(स्थिर व्योम *name1, माप_प्रकार name1_len,
			 स्थिर व्योम *name2, माप_प्रकार name2_len)
अणु
	पूर्णांक ret;

	ret = स_भेद(name1, name2, min(name1_len, name2_len));
	अगर (!ret) अणु
		अगर (name1_len < name2_len)
			ret = -1;
		अन्यथा अगर (name1_len > name2_len)
			ret = 1;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक hoid_compare(स्थिर काष्ठा ceph_hobject_id *lhs,
			स्थिर काष्ठा ceph_hobject_id *rhs)
अणु
	व्योम *effective_key1, *effective_key2;
	माप_प्रकार effective_key1_len, effective_key2_len;
	पूर्णांक ret;

	अगर (lhs->is_max < rhs->is_max)
		वापस -1;
	अगर (lhs->is_max > rhs->is_max)
		वापस 1;

	अगर (lhs->pool < rhs->pool)
		वापस -1;
	अगर (lhs->pool > rhs->pool)
		वापस 1;

	अगर (hoid_get_bitwise_key(lhs) < hoid_get_bitwise_key(rhs))
		वापस -1;
	अगर (hoid_get_bitwise_key(lhs) > hoid_get_bitwise_key(rhs))
		वापस 1;

	ret = compare_names(lhs->nspace, lhs->nspace_len,
			    rhs->nspace, rhs->nspace_len);
	अगर (ret)
		वापस ret;

	hoid_get_effective_key(lhs, &effective_key1, &effective_key1_len);
	hoid_get_effective_key(rhs, &effective_key2, &effective_key2_len);
	ret = compare_names(effective_key1, effective_key1_len,
			    effective_key2, effective_key2_len);
	अगर (ret)
		वापस ret;

	ret = compare_names(lhs->oid, lhs->oid_len, rhs->oid, rhs->oid_len);
	अगर (ret)
		वापस ret;

	अगर (lhs->snapid < rhs->snapid)
		वापस -1;
	अगर (lhs->snapid > rhs->snapid)
		वापस 1;

	वापस 0;
पूर्ण

/*
 * For decoding ->begin and ->end of MOSDBackoff only -- no MIN/MAX
 * compat stuff here.
 *
 * Assumes @hoid is zero-initialized.
 */
अटल पूर्णांक decode_hoid(व्योम **p, व्योम *end, काष्ठा ceph_hobject_id *hoid)
अणु
	u8 काष्ठा_v;
	u32 काष्ठा_len;
	पूर्णांक ret;

	ret = ceph_start_decoding(p, end, 4, "hobject_t", &काष्ठा_v,
				  &काष्ठा_len);
	अगर (ret)
		वापस ret;

	अगर (काष्ठा_v < 4) अणु
		pr_err("got struct_v %d < 4 of hobject_t\n", काष्ठा_v);
		जाओ e_inval;
	पूर्ण

	hoid->key = ceph_extract_encoded_string(p, end, &hoid->key_len,
						GFP_NOIO);
	अगर (IS_ERR(hoid->key)) अणु
		ret = PTR_ERR(hoid->key);
		hoid->key = शून्य;
		वापस ret;
	पूर्ण

	hoid->oid = ceph_extract_encoded_string(p, end, &hoid->oid_len,
						GFP_NOIO);
	अगर (IS_ERR(hoid->oid)) अणु
		ret = PTR_ERR(hoid->oid);
		hoid->oid = शून्य;
		वापस ret;
	पूर्ण

	ceph_decode_64_safe(p, end, hoid->snapid, e_inval);
	ceph_decode_32_safe(p, end, hoid->hash, e_inval);
	ceph_decode_8_safe(p, end, hoid->is_max, e_inval);

	hoid->nspace = ceph_extract_encoded_string(p, end, &hoid->nspace_len,
						   GFP_NOIO);
	अगर (IS_ERR(hoid->nspace)) अणु
		ret = PTR_ERR(hoid->nspace);
		hoid->nspace = शून्य;
		वापस ret;
	पूर्ण

	ceph_decode_64_safe(p, end, hoid->pool, e_inval);

	ceph_hoid_build_hash_cache(hoid);
	वापस 0;

e_inval:
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक hoid_encoding_size(स्थिर काष्ठा ceph_hobject_id *hoid)
अणु
	वापस 8 + 4 + 1 + 8 + /* snapid, hash, is_max, pool */
	       4 + hoid->key_len + 4 + hoid->oid_len + 4 + hoid->nspace_len;
पूर्ण

अटल व्योम encode_hoid(व्योम **p, व्योम *end, स्थिर काष्ठा ceph_hobject_id *hoid)
अणु
	ceph_start_encoding(p, 4, 3, hoid_encoding_size(hoid));
	ceph_encode_string(p, end, hoid->key, hoid->key_len);
	ceph_encode_string(p, end, hoid->oid, hoid->oid_len);
	ceph_encode_64(p, hoid->snapid);
	ceph_encode_32(p, hoid->hash);
	ceph_encode_8(p, hoid->is_max);
	ceph_encode_string(p, end, hoid->nspace, hoid->nspace_len);
	ceph_encode_64(p, hoid->pool);
पूर्ण

अटल व्योम मुक्त_hoid(काष्ठा ceph_hobject_id *hoid)
अणु
	अगर (hoid) अणु
		kमुक्त(hoid->key);
		kमुक्त(hoid->oid);
		kमुक्त(hoid->nspace);
		kमुक्त(hoid);
	पूर्ण
पूर्ण

अटल काष्ठा ceph_osd_backoff *alloc_backoff(व्योम)
अणु
	काष्ठा ceph_osd_backoff *backoff;

	backoff = kzalloc(माप(*backoff), GFP_NOIO);
	अगर (!backoff)
		वापस शून्य;

	RB_CLEAR_NODE(&backoff->spg_node);
	RB_CLEAR_NODE(&backoff->id_node);
	वापस backoff;
पूर्ण

अटल व्योम मुक्त_backoff(काष्ठा ceph_osd_backoff *backoff)
अणु
	WARN_ON(!RB_EMPTY_NODE(&backoff->spg_node));
	WARN_ON(!RB_EMPTY_NODE(&backoff->id_node));

	मुक्त_hoid(backoff->begin);
	मुक्त_hoid(backoff->end);
	kमुक्त(backoff);
पूर्ण

/*
 * Within a specअगरic spgid, backoffs are managed by ->begin hoid.
 */
DEFINE_RB_INSDEL_FUNCS2(backoff, काष्ठा ceph_osd_backoff, begin, hoid_compare,
			RB_BYVAL, spg_node);

अटल काष्ठा ceph_osd_backoff *lookup_containing_backoff(काष्ठा rb_root *root,
					    स्थिर काष्ठा ceph_hobject_id *hoid)
अणु
	काष्ठा rb_node *n = root->rb_node;

	जबतक (n) अणु
		काष्ठा ceph_osd_backoff *cur =
		    rb_entry(n, काष्ठा ceph_osd_backoff, spg_node);
		पूर्णांक cmp;

		cmp = hoid_compare(hoid, cur->begin);
		अगर (cmp < 0) अणु
			n = n->rb_left;
		पूर्ण अन्यथा अगर (cmp > 0) अणु
			अगर (hoid_compare(hoid, cur->end) < 0)
				वापस cur;

			n = n->rb_right;
		पूर्ण अन्यथा अणु
			वापस cur;
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण

/*
 * Each backoff has a unique id within its OSD session.
 */
DEFINE_RB_FUNCS(backoff_by_id, काष्ठा ceph_osd_backoff, id, id_node)

अटल व्योम clear_backoffs(काष्ठा ceph_osd *osd)
अणु
	जबतक (!RB_EMPTY_ROOT(&osd->o_backoff_mappings)) अणु
		काष्ठा ceph_spg_mapping *spg =
		    rb_entry(rb_first(&osd->o_backoff_mappings),
			     काष्ठा ceph_spg_mapping, node);

		जबतक (!RB_EMPTY_ROOT(&spg->backoffs)) अणु
			काष्ठा ceph_osd_backoff *backoff =
			    rb_entry(rb_first(&spg->backoffs),
				     काष्ठा ceph_osd_backoff, spg_node);

			erase_backoff(&spg->backoffs, backoff);
			erase_backoff_by_id(&osd->o_backoffs_by_id, backoff);
			मुक्त_backoff(backoff);
		पूर्ण
		erase_spg_mapping(&osd->o_backoff_mappings, spg);
		मुक्त_spg_mapping(spg);
	पूर्ण
पूर्ण

/*
 * Set up a temporary, non-owning view पूर्णांकo @t.
 */
अटल व्योम hoid_fill_from_target(काष्ठा ceph_hobject_id *hoid,
				  स्थिर काष्ठा ceph_osd_request_target *t)
अणु
	hoid->key = शून्य;
	hoid->key_len = 0;
	hoid->oid = t->target_oid.name;
	hoid->oid_len = t->target_oid.name_len;
	hoid->snapid = CEPH_NOSNAP;
	hoid->hash = t->pgid.seed;
	hoid->is_max = false;
	अगर (t->target_oloc.pool_ns) अणु
		hoid->nspace = t->target_oloc.pool_ns->str;
		hoid->nspace_len = t->target_oloc.pool_ns->len;
	पूर्ण अन्यथा अणु
		hoid->nspace = शून्य;
		hoid->nspace_len = 0;
	पूर्ण
	hoid->pool = t->target_oloc.pool;
	ceph_hoid_build_hash_cache(hoid);
पूर्ण

अटल bool should_plug_request(काष्ठा ceph_osd_request *req)
अणु
	काष्ठा ceph_osd *osd = req->r_osd;
	काष्ठा ceph_spg_mapping *spg;
	काष्ठा ceph_osd_backoff *backoff;
	काष्ठा ceph_hobject_id hoid;

	spg = lookup_spg_mapping(&osd->o_backoff_mappings, &req->r_t.spgid);
	अगर (!spg)
		वापस false;

	hoid_fill_from_target(&hoid, &req->r_t);
	backoff = lookup_containing_backoff(&spg->backoffs, &hoid);
	अगर (!backoff)
		वापस false;

	करोut("%s req %p tid %llu backoff osd%d spgid %llu.%xs%d id %llu\n",
	     __func__, req, req->r_tid, osd->o_osd, backoff->spgid.pgid.pool,
	     backoff->spgid.pgid.seed, backoff->spgid.shard, backoff->id);
	वापस true;
पूर्ण

/*
 * Keep get_num_data_items() in sync with this function.
 */
अटल व्योम setup_request_data(काष्ठा ceph_osd_request *req)
अणु
	काष्ठा ceph_msg *request_msg = req->r_request;
	काष्ठा ceph_msg *reply_msg = req->r_reply;
	काष्ठा ceph_osd_req_op *op;

	अगर (req->r_request->num_data_items || req->r_reply->num_data_items)
		वापस;

	WARN_ON(request_msg->data_length || reply_msg->data_length);
	क्रम (op = req->r_ops; op != &req->r_ops[req->r_num_ops]; op++) अणु
		चयन (op->op) अणु
		/* request */
		हाल CEPH_OSD_OP_WRITE:
		हाल CEPH_OSD_OP_WRITEFULL:
			WARN_ON(op->indata_len != op->extent.length);
			ceph_osdc_msg_data_add(request_msg,
					       &op->extent.osd_data);
			अवरोध;
		हाल CEPH_OSD_OP_SETXATTR:
		हाल CEPH_OSD_OP_CMPXATTR:
			WARN_ON(op->indata_len != op->xattr.name_len +
						  op->xattr.value_len);
			ceph_osdc_msg_data_add(request_msg,
					       &op->xattr.osd_data);
			अवरोध;
		हाल CEPH_OSD_OP_NOTIFY_ACK:
			ceph_osdc_msg_data_add(request_msg,
					       &op->notअगरy_ack.request_data);
			अवरोध;
		हाल CEPH_OSD_OP_COPY_FROM2:
			ceph_osdc_msg_data_add(request_msg,
					       &op->copy_from.osd_data);
			अवरोध;

		/* reply */
		हाल CEPH_OSD_OP_STAT:
			ceph_osdc_msg_data_add(reply_msg,
					       &op->raw_data_in);
			अवरोध;
		हाल CEPH_OSD_OP_READ:
			ceph_osdc_msg_data_add(reply_msg,
					       &op->extent.osd_data);
			अवरोध;
		हाल CEPH_OSD_OP_LIST_WATCHERS:
			ceph_osdc_msg_data_add(reply_msg,
					       &op->list_watchers.response_data);
			अवरोध;

		/* both */
		हाल CEPH_OSD_OP_CALL:
			WARN_ON(op->indata_len != op->cls.class_len +
						  op->cls.method_len +
						  op->cls.indata_len);
			ceph_osdc_msg_data_add(request_msg,
					       &op->cls.request_info);
			/* optional, can be NONE */
			ceph_osdc_msg_data_add(request_msg,
					       &op->cls.request_data);
			/* optional, can be NONE */
			ceph_osdc_msg_data_add(reply_msg,
					       &op->cls.response_data);
			अवरोध;
		हाल CEPH_OSD_OP_NOTIFY:
			ceph_osdc_msg_data_add(request_msg,
					       &op->notअगरy.request_data);
			ceph_osdc_msg_data_add(reply_msg,
					       &op->notअगरy.response_data);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम encode_pgid(व्योम **p, स्थिर काष्ठा ceph_pg *pgid)
अणु
	ceph_encode_8(p, 1);
	ceph_encode_64(p, pgid->pool);
	ceph_encode_32(p, pgid->seed);
	ceph_encode_32(p, -1); /* preferred */
पूर्ण

अटल व्योम encode_spgid(व्योम **p, स्थिर काष्ठा ceph_spg *spgid)
अणु
	ceph_start_encoding(p, 1, 1, CEPH_PGID_ENCODING_LEN + 1);
	encode_pgid(p, &spgid->pgid);
	ceph_encode_8(p, spgid->shard);
पूर्ण

अटल व्योम encode_oloc(व्योम **p, व्योम *end,
			स्थिर काष्ठा ceph_object_locator *oloc)
अणु
	ceph_start_encoding(p, 5, 4, ceph_oloc_encoding_size(oloc));
	ceph_encode_64(p, oloc->pool);
	ceph_encode_32(p, -1); /* preferred */
	ceph_encode_32(p, 0);  /* key len */
	अगर (oloc->pool_ns)
		ceph_encode_string(p, end, oloc->pool_ns->str,
				   oloc->pool_ns->len);
	अन्यथा
		ceph_encode_32(p, 0);
पूर्ण

अटल व्योम encode_request_partial(काष्ठा ceph_osd_request *req,
				   काष्ठा ceph_msg *msg)
अणु
	व्योम *p = msg->front.iov_base;
	व्योम *स्थिर end = p + msg->front_alloc_len;
	u32 data_len = 0;
	पूर्णांक i;

	अगर (req->r_flags & CEPH_OSD_FLAG_WRITE) अणु
		/* snapshots aren't ग_लिखोable */
		WARN_ON(req->r_snapid != CEPH_NOSNAP);
	पूर्ण अन्यथा अणु
		WARN_ON(req->r_mसमय.tv_sec || req->r_mसमय.tv_nsec ||
			req->r_data_offset || req->r_snapc);
	पूर्ण

	setup_request_data(req);

	encode_spgid(&p, &req->r_t.spgid); /* actual spg */
	ceph_encode_32(&p, req->r_t.pgid.seed); /* raw hash */
	ceph_encode_32(&p, req->r_osdc->osdmap->epoch);
	ceph_encode_32(&p, req->r_flags);

	/* reqid */
	ceph_start_encoding(&p, 2, 2, माप(काष्ठा ceph_osd_reqid));
	स_रखो(p, 0, माप(काष्ठा ceph_osd_reqid));
	p += माप(काष्ठा ceph_osd_reqid);

	/* trace */
	स_रखो(p, 0, माप(काष्ठा ceph_blkin_trace_info));
	p += माप(काष्ठा ceph_blkin_trace_info);

	ceph_encode_32(&p, 0); /* client_inc, always 0 */
	ceph_encode_बारpec64(p, &req->r_mसमय);
	p += माप(काष्ठा ceph_बारpec);

	encode_oloc(&p, end, &req->r_t.target_oloc);
	ceph_encode_string(&p, end, req->r_t.target_oid.name,
			   req->r_t.target_oid.name_len);

	/* ops, can imply data */
	ceph_encode_16(&p, req->r_num_ops);
	क्रम (i = 0; i < req->r_num_ops; i++) अणु
		data_len += osd_req_encode_op(p, &req->r_ops[i]);
		p += माप(काष्ठा ceph_osd_op);
	पूर्ण

	ceph_encode_64(&p, req->r_snapid); /* snapid */
	अगर (req->r_snapc) अणु
		ceph_encode_64(&p, req->r_snapc->seq);
		ceph_encode_32(&p, req->r_snapc->num_snaps);
		क्रम (i = 0; i < req->r_snapc->num_snaps; i++)
			ceph_encode_64(&p, req->r_snapc->snaps[i]);
	पूर्ण अन्यथा अणु
		ceph_encode_64(&p, 0); /* snap_seq */
		ceph_encode_32(&p, 0); /* snaps len */
	पूर्ण

	ceph_encode_32(&p, req->r_attempts); /* retry_attempt */
	BUG_ON(p > end - 8); /* space क्रम features */

	msg->hdr.version = cpu_to_le16(8); /* MOSDOp v8 */
	/* front_len is finalized in encode_request_finish() */
	msg->front.iov_len = p - msg->front.iov_base;
	msg->hdr.front_len = cpu_to_le32(msg->front.iov_len);
	msg->hdr.data_len = cpu_to_le32(data_len);
	/*
	 * The header "data_off" is a hपूर्णांक to the receiver allowing it
	 * to align received data पूर्णांकo its buffers such that there's no
	 * need to re-copy it beक्रमe writing it to disk (direct I/O).
	 */
	msg->hdr.data_off = cpu_to_le16(req->r_data_offset);

	करोut("%s req %p msg %p oid %s oid_len %d\n", __func__, req, msg,
	     req->r_t.target_oid.name, req->r_t.target_oid.name_len);
पूर्ण

अटल व्योम encode_request_finish(काष्ठा ceph_msg *msg)
अणु
	व्योम *p = msg->front.iov_base;
	व्योम *स्थिर partial_end = p + msg->front.iov_len;
	व्योम *स्थिर end = p + msg->front_alloc_len;

	अगर (CEPH_HAVE_FEATURE(msg->con->peer_features, RESEND_ON_SPLIT)) अणु
		/* luminous OSD -- encode features and be करोne */
		p = partial_end;
		ceph_encode_64(&p, msg->con->peer_features);
	पूर्ण अन्यथा अणु
		काष्ठा अणु
			अक्षर spgid[CEPH_ENCODING_START_BLK_LEN +
				   CEPH_PGID_ENCODING_LEN + 1];
			__le32 hash;
			__le32 epoch;
			__le32 flags;
			अक्षर reqid[CEPH_ENCODING_START_BLK_LEN +
				   माप(काष्ठा ceph_osd_reqid)];
			अक्षर trace[माप(काष्ठा ceph_blkin_trace_info)];
			__le32 client_inc;
			काष्ठा ceph_बारpec mसमय;
		पूर्ण __packed head;
		काष्ठा ceph_pg pgid;
		व्योम *oloc, *oid, *tail;
		पूर्णांक oloc_len, oid_len, tail_len;
		पूर्णांक len;

		/*
		 * Pre-luminous OSD -- reencode v8 पूर्णांकo v4 using @head
		 * as a temporary buffer.  Encode the raw PG; the rest
		 * is just a matter of moving oloc, oid and tail blobs
		 * around.
		 */
		स_नकल(&head, p, माप(head));
		p += माप(head);

		oloc = p;
		p += CEPH_ENCODING_START_BLK_LEN;
		pgid.pool = ceph_decode_64(&p);
		p += 4 + 4; /* preferred, key len */
		len = ceph_decode_32(&p);
		p += len;   /* nspace */
		oloc_len = p - oloc;

		oid = p;
		len = ceph_decode_32(&p);
		p += len;
		oid_len = p - oid;

		tail = p;
		tail_len = partial_end - p;

		p = msg->front.iov_base;
		ceph_encode_copy(&p, &head.client_inc, माप(head.client_inc));
		ceph_encode_copy(&p, &head.epoch, माप(head.epoch));
		ceph_encode_copy(&p, &head.flags, माप(head.flags));
		ceph_encode_copy(&p, &head.mसमय, माप(head.mसमय));

		/* reनिश्चित_version */
		स_रखो(p, 0, माप(काष्ठा ceph_eversion));
		p += माप(काष्ठा ceph_eversion);

		BUG_ON(p >= oloc);
		स_हटाओ(p, oloc, oloc_len);
		p += oloc_len;

		pgid.seed = le32_to_cpu(head.hash);
		encode_pgid(&p, &pgid); /* raw pg */

		BUG_ON(p >= oid);
		स_हटाओ(p, oid, oid_len);
		p += oid_len;

		/* tail -- ops, snapid, snapc, retry_attempt */
		BUG_ON(p >= tail);
		स_हटाओ(p, tail, tail_len);
		p += tail_len;

		msg->hdr.version = cpu_to_le16(4); /* MOSDOp v4 */
	पूर्ण

	BUG_ON(p > end);
	msg->front.iov_len = p - msg->front.iov_base;
	msg->hdr.front_len = cpu_to_le32(msg->front.iov_len);

	करोut("%s msg %p tid %llu %u+%u+%u v%d\n", __func__, msg,
	     le64_to_cpu(msg->hdr.tid), le32_to_cpu(msg->hdr.front_len),
	     le32_to_cpu(msg->hdr.middle_len), le32_to_cpu(msg->hdr.data_len),
	     le16_to_cpu(msg->hdr.version));
पूर्ण

/*
 * @req has to be asचिन्हित a tid and रेजिस्टरed.
 */
अटल व्योम send_request(काष्ठा ceph_osd_request *req)
अणु
	काष्ठा ceph_osd *osd = req->r_osd;

	verअगरy_osd_locked(osd);
	WARN_ON(osd->o_osd != req->r_t.osd);

	/* backoff? */
	अगर (should_plug_request(req))
		वापस;

	/*
	 * We may have a previously queued request message hanging
	 * around.  Cancel it to aव्योम corrupting the msgr.
	 */
	अगर (req->r_sent)
		ceph_msg_revoke(req->r_request);

	req->r_flags |= CEPH_OSD_FLAG_KNOWN_REसूची;
	अगर (req->r_attempts)
		req->r_flags |= CEPH_OSD_FLAG_RETRY;
	अन्यथा
		WARN_ON(req->r_flags & CEPH_OSD_FLAG_RETRY);

	encode_request_partial(req, req->r_request);

	करोut("%s req %p tid %llu to pgid %llu.%x spgid %llu.%xs%d osd%d e%u flags 0x%x attempt %d\n",
	     __func__, req, req->r_tid, req->r_t.pgid.pool, req->r_t.pgid.seed,
	     req->r_t.spgid.pgid.pool, req->r_t.spgid.pgid.seed,
	     req->r_t.spgid.shard, osd->o_osd, req->r_t.epoch, req->r_flags,
	     req->r_attempts);

	req->r_t.छोड़ोd = false;
	req->r_stamp = jअगरfies;
	req->r_attempts++;

	req->r_sent = osd->o_incarnation;
	req->r_request->hdr.tid = cpu_to_le64(req->r_tid);
	ceph_con_send(&osd->o_con, ceph_msg_get(req->r_request));
पूर्ण

अटल व्योम maybe_request_map(काष्ठा ceph_osd_client *osdc)
अणु
	bool continuous = false;

	verअगरy_osdc_locked(osdc);
	WARN_ON(!osdc->osdmap->epoch);

	अगर (ceph_osdmap_flag(osdc, CEPH_OSDMAP_FULL) ||
	    ceph_osdmap_flag(osdc, CEPH_OSDMAP_PAUSERD) ||
	    ceph_osdmap_flag(osdc, CEPH_OSDMAP_PAUSEWR)) अणु
		करोut("%s osdc %p continuous\n", __func__, osdc);
		continuous = true;
	पूर्ण अन्यथा अणु
		करोut("%s osdc %p onetime\n", __func__, osdc);
	पूर्ण

	अगर (ceph_monc_want_map(&osdc->client->monc, CEPH_SUB_OSDMAP,
			       osdc->osdmap->epoch + 1, continuous))
		ceph_monc_renew_subs(&osdc->client->monc);
पूर्ण

अटल व्योम complete_request(काष्ठा ceph_osd_request *req, पूर्णांक err);
अटल व्योम send_map_check(काष्ठा ceph_osd_request *req);

अटल व्योम __submit_request(काष्ठा ceph_osd_request *req, bool wrlocked)
अणु
	काष्ठा ceph_osd_client *osdc = req->r_osdc;
	काष्ठा ceph_osd *osd;
	क्रमागत calc_target_result ct_res;
	पूर्णांक err = 0;
	bool need_send = false;
	bool promoted = false;

	WARN_ON(req->r_tid);
	करोut("%s req %p wrlocked %d\n", __func__, req, wrlocked);

again:
	ct_res = calc_target(osdc, &req->r_t, false);
	अगर (ct_res == CALC_TARGET_POOL_DNE && !wrlocked)
		जाओ promote;

	osd = lookup_create_osd(osdc, req->r_t.osd, wrlocked);
	अगर (IS_ERR(osd)) अणु
		WARN_ON(PTR_ERR(osd) != -EAGAIN || wrlocked);
		जाओ promote;
	पूर्ण

	अगर (osdc->पात_err) अणु
		करोut("req %p abort_err %d\n", req, osdc->पात_err);
		err = osdc->पात_err;
	पूर्ण अन्यथा अगर (osdc->osdmap->epoch < osdc->epoch_barrier) अणु
		करोut("req %p epoch %u barrier %u\n", req, osdc->osdmap->epoch,
		     osdc->epoch_barrier);
		req->r_t.छोड़ोd = true;
		maybe_request_map(osdc);
	पूर्ण अन्यथा अगर ((req->r_flags & CEPH_OSD_FLAG_WRITE) &&
		   ceph_osdmap_flag(osdc, CEPH_OSDMAP_PAUSEWR)) अणु
		करोut("req %p pausewr\n", req);
		req->r_t.छोड़ोd = true;
		maybe_request_map(osdc);
	पूर्ण अन्यथा अगर ((req->r_flags & CEPH_OSD_FLAG_READ) &&
		   ceph_osdmap_flag(osdc, CEPH_OSDMAP_PAUSERD)) अणु
		करोut("req %p pauserd\n", req);
		req->r_t.छोड़ोd = true;
		maybe_request_map(osdc);
	पूर्ण अन्यथा अगर ((req->r_flags & CEPH_OSD_FLAG_WRITE) &&
		   !(req->r_flags & (CEPH_OSD_FLAG_FULL_TRY |
				     CEPH_OSD_FLAG_FULL_FORCE)) &&
		   (ceph_osdmap_flag(osdc, CEPH_OSDMAP_FULL) ||
		    pool_full(osdc, req->r_t.base_oloc.pool))) अणु
		करोut("req %p full/pool_full\n", req);
		अगर (ceph_test_opt(osdc->client, ABORT_ON_FULL)) अणु
			err = -ENOSPC;
		पूर्ण अन्यथा अणु
			pr_warn_ratelimited("FULL or reached pool quota\n");
			req->r_t.छोड़ोd = true;
			maybe_request_map(osdc);
		पूर्ण
	पूर्ण अन्यथा अगर (!osd_homeless(osd)) अणु
		need_send = true;
	पूर्ण अन्यथा अणु
		maybe_request_map(osdc);
	पूर्ण

	mutex_lock(&osd->lock);
	/*
	 * Assign the tid atomically with send_request() to protect
	 * multiple ग_लिखोs to the same object from racing with each
	 * other, resulting in out of order ops on the OSDs.
	 */
	req->r_tid = atomic64_inc_वापस(&osdc->last_tid);
	link_request(osd, req);
	अगर (need_send)
		send_request(req);
	अन्यथा अगर (err)
		complete_request(req, err);
	mutex_unlock(&osd->lock);

	अगर (!err && ct_res == CALC_TARGET_POOL_DNE)
		send_map_check(req);

	अगर (promoted)
		करोwngrade_ग_लिखो(&osdc->lock);
	वापस;

promote:
	up_पढ़ो(&osdc->lock);
	करोwn_ग_लिखो(&osdc->lock);
	wrlocked = true;
	promoted = true;
	जाओ again;
पूर्ण

अटल व्योम account_request(काष्ठा ceph_osd_request *req)
अणु
	WARN_ON(req->r_flags & (CEPH_OSD_FLAG_ACK | CEPH_OSD_FLAG_ONDISK));
	WARN_ON(!(req->r_flags & (CEPH_OSD_FLAG_READ | CEPH_OSD_FLAG_WRITE)));

	req->r_flags |= CEPH_OSD_FLAG_ONDISK;
	atomic_inc(&req->r_osdc->num_requests);

	req->r_start_stamp = jअगरfies;
	req->r_start_latency = kसमय_get();
पूर्ण

अटल व्योम submit_request(काष्ठा ceph_osd_request *req, bool wrlocked)
अणु
	ceph_osdc_get_request(req);
	account_request(req);
	__submit_request(req, wrlocked);
पूर्ण

अटल व्योम finish_request(काष्ठा ceph_osd_request *req)
अणु
	काष्ठा ceph_osd_client *osdc = req->r_osdc;

	WARN_ON(lookup_request_mc(&osdc->map_checks, req->r_tid));
	करोut("%s req %p tid %llu\n", __func__, req, req->r_tid);

	req->r_end_latency = kसमय_get();

	अगर (req->r_osd)
		unlink_request(req->r_osd, req);
	atomic_dec(&osdc->num_requests);

	/*
	 * If an OSD has failed or वापसed and a request has been sent
	 * twice, it's possible to get a reply and end up here जबतक the
	 * request message is queued क्रम delivery.  We will ignore the
	 * reply, so not a big deal, but better to try and catch it.
	 */
	ceph_msg_revoke(req->r_request);
	ceph_msg_revoke_incoming(req->r_reply);
पूर्ण

अटल व्योम __complete_request(काष्ठा ceph_osd_request *req)
अणु
	करोut("%s req %p tid %llu cb %ps result %d\n", __func__, req,
	     req->r_tid, req->r_callback, req->r_result);

	अगर (req->r_callback)
		req->r_callback(req);
	complete_all(&req->r_completion);
	ceph_osdc_put_request(req);
पूर्ण

अटल व्योम complete_request_workfn(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ceph_osd_request *req =
	    container_of(work, काष्ठा ceph_osd_request, r_complete_work);

	__complete_request(req);
पूर्ण

/*
 * This is खोलो-coded in handle_reply().
 */
अटल व्योम complete_request(काष्ठा ceph_osd_request *req, पूर्णांक err)
अणु
	करोut("%s req %p tid %llu err %d\n", __func__, req, req->r_tid, err);

	req->r_result = err;
	finish_request(req);

	INIT_WORK(&req->r_complete_work, complete_request_workfn);
	queue_work(req->r_osdc->completion_wq, &req->r_complete_work);
पूर्ण

अटल व्योम cancel_map_check(काष्ठा ceph_osd_request *req)
अणु
	काष्ठा ceph_osd_client *osdc = req->r_osdc;
	काष्ठा ceph_osd_request *lookup_req;

	verअगरy_osdc_wrlocked(osdc);

	lookup_req = lookup_request_mc(&osdc->map_checks, req->r_tid);
	अगर (!lookup_req)
		वापस;

	WARN_ON(lookup_req != req);
	erase_request_mc(&osdc->map_checks, req);
	ceph_osdc_put_request(req);
पूर्ण

अटल व्योम cancel_request(काष्ठा ceph_osd_request *req)
अणु
	करोut("%s req %p tid %llu\n", __func__, req, req->r_tid);

	cancel_map_check(req);
	finish_request(req);
	complete_all(&req->r_completion);
	ceph_osdc_put_request(req);
पूर्ण

अटल व्योम पात_request(काष्ठा ceph_osd_request *req, पूर्णांक err)
अणु
	करोut("%s req %p tid %llu err %d\n", __func__, req, req->r_tid, err);

	cancel_map_check(req);
	complete_request(req, err);
पूर्ण

अटल पूर्णांक पात_fn(काष्ठा ceph_osd_request *req, व्योम *arg)
अणु
	पूर्णांक err = *(पूर्णांक *)arg;

	पात_request(req, err);
	वापस 0; /* जारी iteration */
पूर्ण

/*
 * Abort all in-flight requests with @err and arrange क्रम all future
 * requests to be failed immediately.
 */
व्योम ceph_osdc_पात_requests(काष्ठा ceph_osd_client *osdc, पूर्णांक err)
अणु
	करोut("%s osdc %p err %d\n", __func__, osdc, err);
	करोwn_ग_लिखो(&osdc->lock);
	क्रम_each_request(osdc, पात_fn, &err);
	osdc->पात_err = err;
	up_ग_लिखो(&osdc->lock);
पूर्ण
EXPORT_SYMBOL(ceph_osdc_पात_requests);

व्योम ceph_osdc_clear_पात_err(काष्ठा ceph_osd_client *osdc)
अणु
	करोwn_ग_लिखो(&osdc->lock);
	osdc->पात_err = 0;
	up_ग_लिखो(&osdc->lock);
पूर्ण
EXPORT_SYMBOL(ceph_osdc_clear_पात_err);

अटल व्योम update_epoch_barrier(काष्ठा ceph_osd_client *osdc, u32 eb)
अणु
	अगर (likely(eb > osdc->epoch_barrier)) अणु
		करोut("updating epoch_barrier from %u to %u\n",
				osdc->epoch_barrier, eb);
		osdc->epoch_barrier = eb;
		/* Request map अगर we're not to the barrier yet */
		अगर (eb > osdc->osdmap->epoch)
			maybe_request_map(osdc);
	पूर्ण
पूर्ण

व्योम ceph_osdc_update_epoch_barrier(काष्ठा ceph_osd_client *osdc, u32 eb)
अणु
	करोwn_पढ़ो(&osdc->lock);
	अगर (unlikely(eb > osdc->epoch_barrier)) अणु
		up_पढ़ो(&osdc->lock);
		करोwn_ग_लिखो(&osdc->lock);
		update_epoch_barrier(osdc, eb);
		up_ग_लिखो(&osdc->lock);
	पूर्ण अन्यथा अणु
		up_पढ़ो(&osdc->lock);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(ceph_osdc_update_epoch_barrier);

/*
 * We can end up releasing caps as a result of पात_request().
 * In that हाल, we probably want to ensure that the cap release message
 * has an updated epoch barrier in it, so set the epoch barrier prior to
 * पातing the first request.
 */
अटल पूर्णांक पात_on_full_fn(काष्ठा ceph_osd_request *req, व्योम *arg)
अणु
	काष्ठा ceph_osd_client *osdc = req->r_osdc;
	bool *victims = arg;

	अगर ((req->r_flags & CEPH_OSD_FLAG_WRITE) &&
	    (ceph_osdmap_flag(osdc, CEPH_OSDMAP_FULL) ||
	     pool_full(osdc, req->r_t.base_oloc.pool))) अणु
		अगर (!*victims) अणु
			update_epoch_barrier(osdc, osdc->osdmap->epoch);
			*victims = true;
		पूर्ण
		पात_request(req, -ENOSPC);
	पूर्ण

	वापस 0; /* जारी iteration */
पूर्ण

/*
 * Drop all pending requests that are stalled रुकोing on a full condition to
 * clear, and complete them with ENOSPC as the वापस code. Set the
 * osdc->epoch_barrier to the latest map epoch that we've seen अगर any were
 * cancelled.
 */
अटल व्योम ceph_osdc_पात_on_full(काष्ठा ceph_osd_client *osdc)
अणु
	bool victims = false;

	अगर (ceph_test_opt(osdc->client, ABORT_ON_FULL) &&
	    (ceph_osdmap_flag(osdc, CEPH_OSDMAP_FULL) || have_pool_full(osdc)))
		क्रम_each_request(osdc, पात_on_full_fn, &victims);
पूर्ण

अटल व्योम check_pool_dne(काष्ठा ceph_osd_request *req)
अणु
	काष्ठा ceph_osd_client *osdc = req->r_osdc;
	काष्ठा ceph_osdmap *map = osdc->osdmap;

	verअगरy_osdc_wrlocked(osdc);
	WARN_ON(!map->epoch);

	अगर (req->r_attempts) अणु
		/*
		 * We sent a request earlier, which means that
		 * previously the pool existed, and now it करोes not
		 * (i.e., it was deleted).
		 */
		req->r_map_dne_bound = map->epoch;
		करोut("%s req %p tid %llu pool disappeared\n", __func__, req,
		     req->r_tid);
	पूर्ण अन्यथा अणु
		करोut("%s req %p tid %llu map_dne_bound %u have %u\n", __func__,
		     req, req->r_tid, req->r_map_dne_bound, map->epoch);
	पूर्ण

	अगर (req->r_map_dne_bound) अणु
		अगर (map->epoch >= req->r_map_dne_bound) अणु
			/* we had a new enough map */
			pr_info_ratelimited("tid %llu pool does not exist\n",
					    req->r_tid);
			complete_request(req, -ENOENT);
		पूर्ण
	पूर्ण अन्यथा अणु
		send_map_check(req);
	पूर्ण
पूर्ण

अटल व्योम map_check_cb(काष्ठा ceph_mon_generic_request *greq)
अणु
	काष्ठा ceph_osd_client *osdc = &greq->monc->client->osdc;
	काष्ठा ceph_osd_request *req;
	u64 tid = greq->निजी_data;

	WARN_ON(greq->result || !greq->u.newest);

	करोwn_ग_लिखो(&osdc->lock);
	req = lookup_request_mc(&osdc->map_checks, tid);
	अगर (!req) अणु
		करोut("%s tid %llu dne\n", __func__, tid);
		जाओ out_unlock;
	पूर्ण

	करोut("%s req %p tid %llu map_dne_bound %u newest %llu\n", __func__,
	     req, req->r_tid, req->r_map_dne_bound, greq->u.newest);
	अगर (!req->r_map_dne_bound)
		req->r_map_dne_bound = greq->u.newest;
	erase_request_mc(&osdc->map_checks, req);
	check_pool_dne(req);

	ceph_osdc_put_request(req);
out_unlock:
	up_ग_लिखो(&osdc->lock);
पूर्ण

अटल व्योम send_map_check(काष्ठा ceph_osd_request *req)
अणु
	काष्ठा ceph_osd_client *osdc = req->r_osdc;
	काष्ठा ceph_osd_request *lookup_req;
	पूर्णांक ret;

	verअगरy_osdc_wrlocked(osdc);

	lookup_req = lookup_request_mc(&osdc->map_checks, req->r_tid);
	अगर (lookup_req) अणु
		WARN_ON(lookup_req != req);
		वापस;
	पूर्ण

	ceph_osdc_get_request(req);
	insert_request_mc(&osdc->map_checks, req);
	ret = ceph_monc_get_version_async(&osdc->client->monc, "osdmap",
					  map_check_cb, req->r_tid);
	WARN_ON(ret);
पूर्ण

/*
 * lingering requests, watch/notअगरy v2 infraकाष्ठाure
 */
अटल व्योम linger_release(काष्ठा kref *kref)
अणु
	काष्ठा ceph_osd_linger_request *lreq =
	    container_of(kref, काष्ठा ceph_osd_linger_request, kref);

	करोut("%s lreq %p reg_req %p ping_req %p\n", __func__, lreq,
	     lreq->reg_req, lreq->ping_req);
	WARN_ON(!RB_EMPTY_NODE(&lreq->node));
	WARN_ON(!RB_EMPTY_NODE(&lreq->osdc_node));
	WARN_ON(!RB_EMPTY_NODE(&lreq->mc_node));
	WARN_ON(!list_empty(&lreq->scan_item));
	WARN_ON(!list_empty(&lreq->pending_lworks));
	WARN_ON(lreq->osd);

	अगर (lreq->reg_req)
		ceph_osdc_put_request(lreq->reg_req);
	अगर (lreq->ping_req)
		ceph_osdc_put_request(lreq->ping_req);
	target_destroy(&lreq->t);
	kमुक्त(lreq);
पूर्ण

अटल व्योम linger_put(काष्ठा ceph_osd_linger_request *lreq)
अणु
	अगर (lreq)
		kref_put(&lreq->kref, linger_release);
पूर्ण

अटल काष्ठा ceph_osd_linger_request *
linger_get(काष्ठा ceph_osd_linger_request *lreq)
अणु
	kref_get(&lreq->kref);
	वापस lreq;
पूर्ण

अटल काष्ठा ceph_osd_linger_request *
linger_alloc(काष्ठा ceph_osd_client *osdc)
अणु
	काष्ठा ceph_osd_linger_request *lreq;

	lreq = kzalloc(माप(*lreq), GFP_NOIO);
	अगर (!lreq)
		वापस शून्य;

	kref_init(&lreq->kref);
	mutex_init(&lreq->lock);
	RB_CLEAR_NODE(&lreq->node);
	RB_CLEAR_NODE(&lreq->osdc_node);
	RB_CLEAR_NODE(&lreq->mc_node);
	INIT_LIST_HEAD(&lreq->scan_item);
	INIT_LIST_HEAD(&lreq->pending_lworks);
	init_completion(&lreq->reg_commit_रुको);
	init_completion(&lreq->notअगरy_finish_रुको);

	lreq->osdc = osdc;
	target_init(&lreq->t);

	करोut("%s lreq %p\n", __func__, lreq);
	वापस lreq;
पूर्ण

DEFINE_RB_INSDEL_FUNCS(linger, काष्ठा ceph_osd_linger_request, linger_id, node)
DEFINE_RB_FUNCS(linger_osdc, काष्ठा ceph_osd_linger_request, linger_id, osdc_node)
DEFINE_RB_FUNCS(linger_mc, काष्ठा ceph_osd_linger_request, linger_id, mc_node)

/*
 * Create linger request <-> OSD session relation.
 *
 * @lreq has to be रेजिस्टरed, @osd may be homeless.
 */
अटल व्योम link_linger(काष्ठा ceph_osd *osd,
			काष्ठा ceph_osd_linger_request *lreq)
अणु
	verअगरy_osd_locked(osd);
	WARN_ON(!lreq->linger_id || lreq->osd);
	करोut("%s osd %p osd%d lreq %p linger_id %llu\n", __func__, osd,
	     osd->o_osd, lreq, lreq->linger_id);

	अगर (!osd_homeless(osd))
		__हटाओ_osd_from_lru(osd);
	अन्यथा
		atomic_inc(&osd->o_osdc->num_homeless);

	get_osd(osd);
	insert_linger(&osd->o_linger_requests, lreq);
	lreq->osd = osd;
पूर्ण

अटल व्योम unlink_linger(काष्ठा ceph_osd *osd,
			  काष्ठा ceph_osd_linger_request *lreq)
अणु
	verअगरy_osd_locked(osd);
	WARN_ON(lreq->osd != osd);
	करोut("%s osd %p osd%d lreq %p linger_id %llu\n", __func__, osd,
	     osd->o_osd, lreq, lreq->linger_id);

	lreq->osd = शून्य;
	erase_linger(&osd->o_linger_requests, lreq);
	put_osd(osd);

	अगर (!osd_homeless(osd))
		maybe_move_osd_to_lru(osd);
	अन्यथा
		atomic_dec(&osd->o_osdc->num_homeless);
पूर्ण

अटल bool __linger_रेजिस्टरed(काष्ठा ceph_osd_linger_request *lreq)
अणु
	verअगरy_osdc_locked(lreq->osdc);

	वापस !RB_EMPTY_NODE(&lreq->osdc_node);
पूर्ण

अटल bool linger_रेजिस्टरed(काष्ठा ceph_osd_linger_request *lreq)
अणु
	काष्ठा ceph_osd_client *osdc = lreq->osdc;
	bool रेजिस्टरed;

	करोwn_पढ़ो(&osdc->lock);
	रेजिस्टरed = __linger_रेजिस्टरed(lreq);
	up_पढ़ो(&osdc->lock);

	वापस रेजिस्टरed;
पूर्ण

अटल व्योम linger_रेजिस्टर(काष्ठा ceph_osd_linger_request *lreq)
अणु
	काष्ठा ceph_osd_client *osdc = lreq->osdc;

	verअगरy_osdc_wrlocked(osdc);
	WARN_ON(lreq->linger_id);

	linger_get(lreq);
	lreq->linger_id = ++osdc->last_linger_id;
	insert_linger_osdc(&osdc->linger_requests, lreq);
पूर्ण

अटल व्योम linger_unरेजिस्टर(काष्ठा ceph_osd_linger_request *lreq)
अणु
	काष्ठा ceph_osd_client *osdc = lreq->osdc;

	verअगरy_osdc_wrlocked(osdc);

	erase_linger_osdc(&osdc->linger_requests, lreq);
	linger_put(lreq);
पूर्ण

अटल व्योम cancel_linger_request(काष्ठा ceph_osd_request *req)
अणु
	काष्ठा ceph_osd_linger_request *lreq = req->r_priv;

	WARN_ON(!req->r_linger);
	cancel_request(req);
	linger_put(lreq);
पूर्ण

काष्ठा linger_work अणु
	काष्ठा work_काष्ठा work;
	काष्ठा ceph_osd_linger_request *lreq;
	काष्ठा list_head pending_item;
	अचिन्हित दीर्घ queued_stamp;

	जोड़ अणु
		काष्ठा अणु
			u64 notअगरy_id;
			u64 notअगरier_id;
			व्योम *payload; /* poपूर्णांकs पूर्णांकo @msg front */
			माप_प्रकार payload_len;

			काष्ठा ceph_msg *msg; /* क्रम ceph_msg_put() */
		पूर्ण notअगरy;
		काष्ठा अणु
			पूर्णांक err;
		पूर्ण error;
	पूर्ण;
पूर्ण;

अटल काष्ठा linger_work *lwork_alloc(काष्ठा ceph_osd_linger_request *lreq,
				       work_func_t workfn)
अणु
	काष्ठा linger_work *lwork;

	lwork = kzalloc(माप(*lwork), GFP_NOIO);
	अगर (!lwork)
		वापस शून्य;

	INIT_WORK(&lwork->work, workfn);
	INIT_LIST_HEAD(&lwork->pending_item);
	lwork->lreq = linger_get(lreq);

	वापस lwork;
पूर्ण

अटल व्योम lwork_मुक्त(काष्ठा linger_work *lwork)
अणु
	काष्ठा ceph_osd_linger_request *lreq = lwork->lreq;

	mutex_lock(&lreq->lock);
	list_del(&lwork->pending_item);
	mutex_unlock(&lreq->lock);

	linger_put(lreq);
	kमुक्त(lwork);
पूर्ण

अटल व्योम lwork_queue(काष्ठा linger_work *lwork)
अणु
	काष्ठा ceph_osd_linger_request *lreq = lwork->lreq;
	काष्ठा ceph_osd_client *osdc = lreq->osdc;

	verअगरy_lreq_locked(lreq);
	WARN_ON(!list_empty(&lwork->pending_item));

	lwork->queued_stamp = jअगरfies;
	list_add_tail(&lwork->pending_item, &lreq->pending_lworks);
	queue_work(osdc->notअगरy_wq, &lwork->work);
पूर्ण

अटल व्योम करो_watch_notअगरy(काष्ठा work_काष्ठा *w)
अणु
	काष्ठा linger_work *lwork = container_of(w, काष्ठा linger_work, work);
	काष्ठा ceph_osd_linger_request *lreq = lwork->lreq;

	अगर (!linger_रेजिस्टरed(lreq)) अणु
		करोut("%s lreq %p not registered\n", __func__, lreq);
		जाओ out;
	पूर्ण

	WARN_ON(!lreq->is_watch);
	करोut("%s lreq %p notify_id %llu notifier_id %llu payload_len %zu\n",
	     __func__, lreq, lwork->notअगरy.notअगरy_id, lwork->notअगरy.notअगरier_id,
	     lwork->notअगरy.payload_len);
	lreq->wcb(lreq->data, lwork->notअगरy.notअगरy_id, lreq->linger_id,
		  lwork->notअगरy.notअगरier_id, lwork->notअगरy.payload,
		  lwork->notअगरy.payload_len);

out:
	ceph_msg_put(lwork->notअगरy.msg);
	lwork_मुक्त(lwork);
पूर्ण

अटल व्योम करो_watch_error(काष्ठा work_काष्ठा *w)
अणु
	काष्ठा linger_work *lwork = container_of(w, काष्ठा linger_work, work);
	काष्ठा ceph_osd_linger_request *lreq = lwork->lreq;

	अगर (!linger_रेजिस्टरed(lreq)) अणु
		करोut("%s lreq %p not registered\n", __func__, lreq);
		जाओ out;
	पूर्ण

	करोut("%s lreq %p err %d\n", __func__, lreq, lwork->error.err);
	lreq->errcb(lreq->data, lreq->linger_id, lwork->error.err);

out:
	lwork_मुक्त(lwork);
पूर्ण

अटल व्योम queue_watch_error(काष्ठा ceph_osd_linger_request *lreq)
अणु
	काष्ठा linger_work *lwork;

	lwork = lwork_alloc(lreq, करो_watch_error);
	अगर (!lwork) अणु
		pr_err("failed to allocate error-lwork\n");
		वापस;
	पूर्ण

	lwork->error.err = lreq->last_error;
	lwork_queue(lwork);
पूर्ण

अटल व्योम linger_reg_commit_complete(काष्ठा ceph_osd_linger_request *lreq,
				       पूर्णांक result)
अणु
	अगर (!completion_करोne(&lreq->reg_commit_रुको)) अणु
		lreq->reg_commit_error = (result <= 0 ? result : 0);
		complete_all(&lreq->reg_commit_रुको);
	पूर्ण
पूर्ण

अटल व्योम linger_commit_cb(काष्ठा ceph_osd_request *req)
अणु
	काष्ठा ceph_osd_linger_request *lreq = req->r_priv;

	mutex_lock(&lreq->lock);
	करोut("%s lreq %p linger_id %llu result %d\n", __func__, lreq,
	     lreq->linger_id, req->r_result);
	linger_reg_commit_complete(lreq, req->r_result);
	lreq->committed = true;

	अगर (!lreq->is_watch) अणु
		काष्ठा ceph_osd_data *osd_data =
		    osd_req_op_data(req, 0, notअगरy, response_data);
		व्योम *p = page_address(osd_data->pages[0]);

		WARN_ON(req->r_ops[0].op != CEPH_OSD_OP_NOTIFY ||
			osd_data->type != CEPH_OSD_DATA_TYPE_PAGES);

		/* make note of the notअगरy_id */
		अगर (req->r_ops[0].outdata_len >= माप(u64)) अणु
			lreq->notअगरy_id = ceph_decode_64(&p);
			करोut("lreq %p notify_id %llu\n", lreq,
			     lreq->notअगरy_id);
		पूर्ण अन्यथा अणु
			करोut("lreq %p no notify_id\n", lreq);
		पूर्ण
	पूर्ण

	mutex_unlock(&lreq->lock);
	linger_put(lreq);
पूर्ण

अटल पूर्णांक normalize_watch_error(पूर्णांक err)
अणु
	/*
	 * Translate ENOENT -> ENOTCONN so that a delete->disconnection
	 * notअगरication and a failure to reconnect because we raced with
	 * the delete appear the same to the user.
	 */
	अगर (err == -ENOENT)
		err = -ENOTCONN;

	वापस err;
पूर्ण

अटल व्योम linger_reconnect_cb(काष्ठा ceph_osd_request *req)
अणु
	काष्ठा ceph_osd_linger_request *lreq = req->r_priv;

	mutex_lock(&lreq->lock);
	करोut("%s lreq %p linger_id %llu result %d last_error %d\n", __func__,
	     lreq, lreq->linger_id, req->r_result, lreq->last_error);
	अगर (req->r_result < 0) अणु
		अगर (!lreq->last_error) अणु
			lreq->last_error = normalize_watch_error(req->r_result);
			queue_watch_error(lreq);
		पूर्ण
	पूर्ण

	mutex_unlock(&lreq->lock);
	linger_put(lreq);
पूर्ण

अटल व्योम send_linger(काष्ठा ceph_osd_linger_request *lreq)
अणु
	काष्ठा ceph_osd_request *req = lreq->reg_req;
	काष्ठा ceph_osd_req_op *op = &req->r_ops[0];

	verअगरy_osdc_wrlocked(req->r_osdc);
	करोut("%s lreq %p linger_id %llu\n", __func__, lreq, lreq->linger_id);

	अगर (req->r_osd)
		cancel_linger_request(req);

	request_reinit(req);
	target_copy(&req->r_t, &lreq->t);
	req->r_mसमय = lreq->mसमय;

	mutex_lock(&lreq->lock);
	अगर (lreq->is_watch && lreq->committed) अणु
		WARN_ON(op->op != CEPH_OSD_OP_WATCH ||
			op->watch.cookie != lreq->linger_id);
		op->watch.op = CEPH_OSD_WATCH_OP_RECONNECT;
		op->watch.gen = ++lreq->रेजिस्टर_gen;
		करोut("lreq %p reconnect register_gen %u\n", lreq,
		     op->watch.gen);
		req->r_callback = linger_reconnect_cb;
	पूर्ण अन्यथा अणु
		अगर (!lreq->is_watch)
			lreq->notअगरy_id = 0;
		अन्यथा
			WARN_ON(op->watch.op != CEPH_OSD_WATCH_OP_WATCH);
		करोut("lreq %p register\n", lreq);
		req->r_callback = linger_commit_cb;
	पूर्ण
	mutex_unlock(&lreq->lock);

	req->r_priv = linger_get(lreq);
	req->r_linger = true;

	submit_request(req, true);
पूर्ण

अटल व्योम linger_ping_cb(काष्ठा ceph_osd_request *req)
अणु
	काष्ठा ceph_osd_linger_request *lreq = req->r_priv;

	mutex_lock(&lreq->lock);
	करोut("%s lreq %p linger_id %llu result %d ping_sent %lu last_error %d\n",
	     __func__, lreq, lreq->linger_id, req->r_result, lreq->ping_sent,
	     lreq->last_error);
	अगर (lreq->रेजिस्टर_gen == req->r_ops[0].watch.gen) अणु
		अगर (!req->r_result) अणु
			lreq->watch_valid_thru = lreq->ping_sent;
		पूर्ण अन्यथा अगर (!lreq->last_error) अणु
			lreq->last_error = normalize_watch_error(req->r_result);
			queue_watch_error(lreq);
		पूर्ण
	पूर्ण अन्यथा अणु
		करोut("lreq %p register_gen %u ignoring old pong %u\n", lreq,
		     lreq->रेजिस्टर_gen, req->r_ops[0].watch.gen);
	पूर्ण

	mutex_unlock(&lreq->lock);
	linger_put(lreq);
पूर्ण

अटल व्योम send_linger_ping(काष्ठा ceph_osd_linger_request *lreq)
अणु
	काष्ठा ceph_osd_client *osdc = lreq->osdc;
	काष्ठा ceph_osd_request *req = lreq->ping_req;
	काष्ठा ceph_osd_req_op *op = &req->r_ops[0];

	अगर (ceph_osdmap_flag(osdc, CEPH_OSDMAP_PAUSERD)) अणु
		करोut("%s PAUSERD\n", __func__);
		वापस;
	पूर्ण

	lreq->ping_sent = jअगरfies;
	करोut("%s lreq %p linger_id %llu ping_sent %lu register_gen %u\n",
	     __func__, lreq, lreq->linger_id, lreq->ping_sent,
	     lreq->रेजिस्टर_gen);

	अगर (req->r_osd)
		cancel_linger_request(req);

	request_reinit(req);
	target_copy(&req->r_t, &lreq->t);

	WARN_ON(op->op != CEPH_OSD_OP_WATCH ||
		op->watch.cookie != lreq->linger_id ||
		op->watch.op != CEPH_OSD_WATCH_OP_PING);
	op->watch.gen = lreq->रेजिस्टर_gen;
	req->r_callback = linger_ping_cb;
	req->r_priv = linger_get(lreq);
	req->r_linger = true;

	ceph_osdc_get_request(req);
	account_request(req);
	req->r_tid = atomic64_inc_वापस(&osdc->last_tid);
	link_request(lreq->osd, req);
	send_request(req);
पूर्ण

अटल व्योम linger_submit(काष्ठा ceph_osd_linger_request *lreq)
अणु
	काष्ठा ceph_osd_client *osdc = lreq->osdc;
	काष्ठा ceph_osd *osd;

	करोwn_ग_लिखो(&osdc->lock);
	linger_रेजिस्टर(lreq);
	अगर (lreq->is_watch) अणु
		lreq->reg_req->r_ops[0].watch.cookie = lreq->linger_id;
		lreq->ping_req->r_ops[0].watch.cookie = lreq->linger_id;
	पूर्ण अन्यथा अणु
		lreq->reg_req->r_ops[0].notअगरy.cookie = lreq->linger_id;
	पूर्ण

	calc_target(osdc, &lreq->t, false);
	osd = lookup_create_osd(osdc, lreq->t.osd, true);
	link_linger(osd, lreq);

	send_linger(lreq);
	up_ग_लिखो(&osdc->lock);
पूर्ण

अटल व्योम cancel_linger_map_check(काष्ठा ceph_osd_linger_request *lreq)
अणु
	काष्ठा ceph_osd_client *osdc = lreq->osdc;
	काष्ठा ceph_osd_linger_request *lookup_lreq;

	verअगरy_osdc_wrlocked(osdc);

	lookup_lreq = lookup_linger_mc(&osdc->linger_map_checks,
				       lreq->linger_id);
	अगर (!lookup_lreq)
		वापस;

	WARN_ON(lookup_lreq != lreq);
	erase_linger_mc(&osdc->linger_map_checks, lreq);
	linger_put(lreq);
पूर्ण

/*
 * @lreq has to be both रेजिस्टरed and linked.
 */
अटल व्योम __linger_cancel(काष्ठा ceph_osd_linger_request *lreq)
अणु
	अगर (lreq->is_watch && lreq->ping_req->r_osd)
		cancel_linger_request(lreq->ping_req);
	अगर (lreq->reg_req->r_osd)
		cancel_linger_request(lreq->reg_req);
	cancel_linger_map_check(lreq);
	unlink_linger(lreq->osd, lreq);
	linger_unरेजिस्टर(lreq);
पूर्ण

अटल व्योम linger_cancel(काष्ठा ceph_osd_linger_request *lreq)
अणु
	काष्ठा ceph_osd_client *osdc = lreq->osdc;

	करोwn_ग_लिखो(&osdc->lock);
	अगर (__linger_रेजिस्टरed(lreq))
		__linger_cancel(lreq);
	up_ग_लिखो(&osdc->lock);
पूर्ण

अटल व्योम send_linger_map_check(काष्ठा ceph_osd_linger_request *lreq);

अटल व्योम check_linger_pool_dne(काष्ठा ceph_osd_linger_request *lreq)
अणु
	काष्ठा ceph_osd_client *osdc = lreq->osdc;
	काष्ठा ceph_osdmap *map = osdc->osdmap;

	verअगरy_osdc_wrlocked(osdc);
	WARN_ON(!map->epoch);

	अगर (lreq->रेजिस्टर_gen) अणु
		lreq->map_dne_bound = map->epoch;
		करोut("%s lreq %p linger_id %llu pool disappeared\n", __func__,
		     lreq, lreq->linger_id);
	पूर्ण अन्यथा अणु
		करोut("%s lreq %p linger_id %llu map_dne_bound %u have %u\n",
		     __func__, lreq, lreq->linger_id, lreq->map_dne_bound,
		     map->epoch);
	पूर्ण

	अगर (lreq->map_dne_bound) अणु
		अगर (map->epoch >= lreq->map_dne_bound) अणु
			/* we had a new enough map */
			pr_info("linger_id %llu pool does not exist\n",
				lreq->linger_id);
			linger_reg_commit_complete(lreq, -ENOENT);
			__linger_cancel(lreq);
		पूर्ण
	पूर्ण अन्यथा अणु
		send_linger_map_check(lreq);
	पूर्ण
पूर्ण

अटल व्योम linger_map_check_cb(काष्ठा ceph_mon_generic_request *greq)
अणु
	काष्ठा ceph_osd_client *osdc = &greq->monc->client->osdc;
	काष्ठा ceph_osd_linger_request *lreq;
	u64 linger_id = greq->निजी_data;

	WARN_ON(greq->result || !greq->u.newest);

	करोwn_ग_लिखो(&osdc->lock);
	lreq = lookup_linger_mc(&osdc->linger_map_checks, linger_id);
	अगर (!lreq) अणु
		करोut("%s linger_id %llu dne\n", __func__, linger_id);
		जाओ out_unlock;
	पूर्ण

	करोut("%s lreq %p linger_id %llu map_dne_bound %u newest %llu\n",
	     __func__, lreq, lreq->linger_id, lreq->map_dne_bound,
	     greq->u.newest);
	अगर (!lreq->map_dne_bound)
		lreq->map_dne_bound = greq->u.newest;
	erase_linger_mc(&osdc->linger_map_checks, lreq);
	check_linger_pool_dne(lreq);

	linger_put(lreq);
out_unlock:
	up_ग_लिखो(&osdc->lock);
पूर्ण

अटल व्योम send_linger_map_check(काष्ठा ceph_osd_linger_request *lreq)
अणु
	काष्ठा ceph_osd_client *osdc = lreq->osdc;
	काष्ठा ceph_osd_linger_request *lookup_lreq;
	पूर्णांक ret;

	verअगरy_osdc_wrlocked(osdc);

	lookup_lreq = lookup_linger_mc(&osdc->linger_map_checks,
				       lreq->linger_id);
	अगर (lookup_lreq) अणु
		WARN_ON(lookup_lreq != lreq);
		वापस;
	पूर्ण

	linger_get(lreq);
	insert_linger_mc(&osdc->linger_map_checks, lreq);
	ret = ceph_monc_get_version_async(&osdc->client->monc, "osdmap",
					  linger_map_check_cb, lreq->linger_id);
	WARN_ON(ret);
पूर्ण

अटल पूर्णांक linger_reg_commit_रुको(काष्ठा ceph_osd_linger_request *lreq)
अणु
	पूर्णांक ret;

	करोut("%s lreq %p linger_id %llu\n", __func__, lreq, lreq->linger_id);
	ret = रुको_क्रम_completion_पूर्णांकerruptible(&lreq->reg_commit_रुको);
	वापस ret ?: lreq->reg_commit_error;
पूर्ण

अटल पूर्णांक linger_notअगरy_finish_रुको(काष्ठा ceph_osd_linger_request *lreq)
अणु
	पूर्णांक ret;

	करोut("%s lreq %p linger_id %llu\n", __func__, lreq, lreq->linger_id);
	ret = रुको_क्रम_completion_पूर्णांकerruptible(&lreq->notअगरy_finish_रुको);
	वापस ret ?: lreq->notअगरy_finish_error;
पूर्ण

/*
 * Timeout callback, called every N seconds.  When 1 or more OSD
 * requests has been active क्रम more than N seconds, we send a keepalive
 * (tag + बारtamp) to its OSD to ensure any communications channel
 * reset is detected.
 */
अटल व्योम handle_समयout(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ceph_osd_client *osdc =
		container_of(work, काष्ठा ceph_osd_client, समयout_work.work);
	काष्ठा ceph_options *opts = osdc->client->options;
	अचिन्हित दीर्घ cutoff = jअगरfies - opts->osd_keepalive_समयout;
	अचिन्हित दीर्घ expiry_cutoff = jअगरfies - opts->osd_request_समयout;
	LIST_HEAD(slow_osds);
	काष्ठा rb_node *n, *p;

	करोut("%s osdc %p\n", __func__, osdc);
	करोwn_ग_लिखो(&osdc->lock);

	/*
	 * ping osds that are a bit slow.  this ensures that अगर there
	 * is a अवरोध in the TCP connection we will notice, and reखोलो
	 * a connection with that osd (from the fault callback).
	 */
	क्रम (n = rb_first(&osdc->osds); n; n = rb_next(n)) अणु
		काष्ठा ceph_osd *osd = rb_entry(n, काष्ठा ceph_osd, o_node);
		bool found = false;

		क्रम (p = rb_first(&osd->o_requests); p; ) अणु
			काष्ठा ceph_osd_request *req =
			    rb_entry(p, काष्ठा ceph_osd_request, r_node);

			p = rb_next(p); /* पात_request() */

			अगर (समय_beक्रमe(req->r_stamp, cutoff)) अणु
				करोut(" req %p tid %llu on osd%d is laggy\n",
				     req, req->r_tid, osd->o_osd);
				found = true;
			पूर्ण
			अगर (opts->osd_request_समयout &&
			    समय_beक्रमe(req->r_start_stamp, expiry_cutoff)) अणु
				pr_err_ratelimited("tid %llu on osd%d timeout\n",
				       req->r_tid, osd->o_osd);
				पात_request(req, -ETIMEDOUT);
			पूर्ण
		पूर्ण
		क्रम (p = rb_first(&osd->o_linger_requests); p; p = rb_next(p)) अणु
			काष्ठा ceph_osd_linger_request *lreq =
			    rb_entry(p, काष्ठा ceph_osd_linger_request, node);

			करोut(" lreq %p linger_id %llu is served by osd%d\n",
			     lreq, lreq->linger_id, osd->o_osd);
			found = true;

			mutex_lock(&lreq->lock);
			अगर (lreq->is_watch && lreq->committed && !lreq->last_error)
				send_linger_ping(lreq);
			mutex_unlock(&lreq->lock);
		पूर्ण

		अगर (found)
			list_move_tail(&osd->o_keepalive_item, &slow_osds);
	पूर्ण

	अगर (opts->osd_request_समयout) अणु
		क्रम (p = rb_first(&osdc->homeless_osd.o_requests); p; ) अणु
			काष्ठा ceph_osd_request *req =
			    rb_entry(p, काष्ठा ceph_osd_request, r_node);

			p = rb_next(p); /* पात_request() */

			अगर (समय_beक्रमe(req->r_start_stamp, expiry_cutoff)) अणु
				pr_err_ratelimited("tid %llu on osd%d timeout\n",
				       req->r_tid, osdc->homeless_osd.o_osd);
				पात_request(req, -ETIMEDOUT);
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (atomic_पढ़ो(&osdc->num_homeless) || !list_empty(&slow_osds))
		maybe_request_map(osdc);

	जबतक (!list_empty(&slow_osds)) अणु
		काष्ठा ceph_osd *osd = list_first_entry(&slow_osds,
							काष्ठा ceph_osd,
							o_keepalive_item);
		list_del_init(&osd->o_keepalive_item);
		ceph_con_keepalive(&osd->o_con);
	पूर्ण

	up_ग_लिखो(&osdc->lock);
	schedule_delayed_work(&osdc->समयout_work,
			      osdc->client->options->osd_keepalive_समयout);
पूर्ण

अटल व्योम handle_osds_समयout(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ceph_osd_client *osdc =
		container_of(work, काष्ठा ceph_osd_client,
			     osds_समयout_work.work);
	अचिन्हित दीर्घ delay = osdc->client->options->osd_idle_ttl / 4;
	काष्ठा ceph_osd *osd, *nosd;

	करोut("%s osdc %p\n", __func__, osdc);
	करोwn_ग_लिखो(&osdc->lock);
	list_क्रम_each_entry_safe(osd, nosd, &osdc->osd_lru, o_osd_lru) अणु
		अगर (समय_beक्रमe(jअगरfies, osd->lru_ttl))
			अवरोध;

		WARN_ON(!RB_EMPTY_ROOT(&osd->o_requests));
		WARN_ON(!RB_EMPTY_ROOT(&osd->o_linger_requests));
		बंद_osd(osd);
	पूर्ण

	up_ग_लिखो(&osdc->lock);
	schedule_delayed_work(&osdc->osds_समयout_work,
			      round_jअगरfies_relative(delay));
पूर्ण

अटल पूर्णांक ceph_oloc_decode(व्योम **p, व्योम *end,
			    काष्ठा ceph_object_locator *oloc)
अणु
	u8 काष्ठा_v, काष्ठा_cv;
	u32 len;
	व्योम *काष्ठा_end;
	पूर्णांक ret = 0;

	ceph_decode_need(p, end, 1 + 1 + 4, e_inval);
	काष्ठा_v = ceph_decode_8(p);
	काष्ठा_cv = ceph_decode_8(p);
	अगर (काष्ठा_v < 3) अणु
		pr_warn("got v %d < 3 cv %d of ceph_object_locator\n",
			काष्ठा_v, काष्ठा_cv);
		जाओ e_inval;
	पूर्ण
	अगर (काष्ठा_cv > 6) अणु
		pr_warn("got v %d cv %d > 6 of ceph_object_locator\n",
			काष्ठा_v, काष्ठा_cv);
		जाओ e_inval;
	पूर्ण
	len = ceph_decode_32(p);
	ceph_decode_need(p, end, len, e_inval);
	काष्ठा_end = *p + len;

	oloc->pool = ceph_decode_64(p);
	*p += 4; /* skip preferred */

	len = ceph_decode_32(p);
	अगर (len > 0) अणु
		pr_warn("ceph_object_locator::key is set\n");
		जाओ e_inval;
	पूर्ण

	अगर (काष्ठा_v >= 5) अणु
		bool changed = false;

		len = ceph_decode_32(p);
		अगर (len > 0) अणु
			ceph_decode_need(p, end, len, e_inval);
			अगर (!oloc->pool_ns ||
			    ceph_compare_string(oloc->pool_ns, *p, len))
				changed = true;
			*p += len;
		पूर्ण अन्यथा अणु
			अगर (oloc->pool_ns)
				changed = true;
		पूर्ण
		अगर (changed) अणु
			/* redirect changes namespace */
			pr_warn("ceph_object_locator::nspace is changed\n");
			जाओ e_inval;
		पूर्ण
	पूर्ण

	अगर (काष्ठा_v >= 6) अणु
		s64 hash = ceph_decode_64(p);
		अगर (hash != -1) अणु
			pr_warn("ceph_object_locator::hash is set\n");
			जाओ e_inval;
		पूर्ण
	पूर्ण

	/* skip the rest */
	*p = काष्ठा_end;
out:
	वापस ret;

e_inval:
	ret = -EINVAL;
	जाओ out;
पूर्ण

अटल पूर्णांक ceph_redirect_decode(व्योम **p, व्योम *end,
				काष्ठा ceph_request_redirect *redir)
अणु
	u8 काष्ठा_v, काष्ठा_cv;
	u32 len;
	व्योम *काष्ठा_end;
	पूर्णांक ret;

	ceph_decode_need(p, end, 1 + 1 + 4, e_inval);
	काष्ठा_v = ceph_decode_8(p);
	काष्ठा_cv = ceph_decode_8(p);
	अगर (काष्ठा_cv > 1) अणु
		pr_warn("got v %d cv %d > 1 of ceph_request_redirect\n",
			काष्ठा_v, काष्ठा_cv);
		जाओ e_inval;
	पूर्ण
	len = ceph_decode_32(p);
	ceph_decode_need(p, end, len, e_inval);
	काष्ठा_end = *p + len;

	ret = ceph_oloc_decode(p, end, &redir->oloc);
	अगर (ret)
		जाओ out;

	len = ceph_decode_32(p);
	अगर (len > 0) अणु
		pr_warn("ceph_request_redirect::object_name is set\n");
		जाओ e_inval;
	पूर्ण

	/* skip the rest */
	*p = काष्ठा_end;
out:
	वापस ret;

e_inval:
	ret = -EINVAL;
	जाओ out;
पूर्ण

काष्ठा MOSDOpReply अणु
	काष्ठा ceph_pg pgid;
	u64 flags;
	पूर्णांक result;
	u32 epoch;
	पूर्णांक num_ops;
	u32 outdata_len[CEPH_OSD_MAX_OPS];
	s32 rval[CEPH_OSD_MAX_OPS];
	पूर्णांक retry_attempt;
	काष्ठा ceph_eversion replay_version;
	u64 user_version;
	काष्ठा ceph_request_redirect redirect;
पूर्ण;

अटल पूर्णांक decode_MOSDOpReply(स्थिर काष्ठा ceph_msg *msg, काष्ठा MOSDOpReply *m)
अणु
	व्योम *p = msg->front.iov_base;
	व्योम *स्थिर end = p + msg->front.iov_len;
	u16 version = le16_to_cpu(msg->hdr.version);
	काष्ठा ceph_eversion bad_replay_version;
	u8 decode_redir;
	u32 len;
	पूर्णांक ret;
	पूर्णांक i;

	ceph_decode_32_safe(&p, end, len, e_inval);
	ceph_decode_need(&p, end, len, e_inval);
	p += len; /* skip oid */

	ret = ceph_decode_pgid(&p, end, &m->pgid);
	अगर (ret)
		वापस ret;

	ceph_decode_64_safe(&p, end, m->flags, e_inval);
	ceph_decode_32_safe(&p, end, m->result, e_inval);
	ceph_decode_need(&p, end, माप(bad_replay_version), e_inval);
	स_नकल(&bad_replay_version, p, माप(bad_replay_version));
	p += माप(bad_replay_version);
	ceph_decode_32_safe(&p, end, m->epoch, e_inval);

	ceph_decode_32_safe(&p, end, m->num_ops, e_inval);
	अगर (m->num_ops > ARRAY_SIZE(m->outdata_len))
		जाओ e_inval;

	ceph_decode_need(&p, end, m->num_ops * माप(काष्ठा ceph_osd_op),
			 e_inval);
	क्रम (i = 0; i < m->num_ops; i++) अणु
		काष्ठा ceph_osd_op *op = p;

		m->outdata_len[i] = le32_to_cpu(op->payload_len);
		p += माप(*op);
	पूर्ण

	ceph_decode_32_safe(&p, end, m->retry_attempt, e_inval);
	क्रम (i = 0; i < m->num_ops; i++)
		ceph_decode_32_safe(&p, end, m->rval[i], e_inval);

	अगर (version >= 5) अणु
		ceph_decode_need(&p, end, माप(m->replay_version), e_inval);
		स_नकल(&m->replay_version, p, माप(m->replay_version));
		p += माप(m->replay_version);
		ceph_decode_64_safe(&p, end, m->user_version, e_inval);
	पूर्ण अन्यथा अणु
		m->replay_version = bad_replay_version; /* काष्ठा */
		m->user_version = le64_to_cpu(m->replay_version.version);
	पूर्ण

	अगर (version >= 6) अणु
		अगर (version >= 7)
			ceph_decode_8_safe(&p, end, decode_redir, e_inval);
		अन्यथा
			decode_redir = 1;
	पूर्ण अन्यथा अणु
		decode_redir = 0;
	पूर्ण

	अगर (decode_redir) अणु
		ret = ceph_redirect_decode(&p, end, &m->redirect);
		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा अणु
		ceph_oloc_init(&m->redirect.oloc);
	पूर्ण

	वापस 0;

e_inval:
	वापस -EINVAL;
पूर्ण

/*
 * Handle MOSDOpReply.  Set ->r_result and call the callback अगर it is
 * specअगरied.
 */
अटल व्योम handle_reply(काष्ठा ceph_osd *osd, काष्ठा ceph_msg *msg)
अणु
	काष्ठा ceph_osd_client *osdc = osd->o_osdc;
	काष्ठा ceph_osd_request *req;
	काष्ठा MOSDOpReply m;
	u64 tid = le64_to_cpu(msg->hdr.tid);
	u32 data_len = 0;
	पूर्णांक ret;
	पूर्णांक i;

	करोut("%s msg %p tid %llu\n", __func__, msg, tid);

	करोwn_पढ़ो(&osdc->lock);
	अगर (!osd_रेजिस्टरed(osd)) अणु
		करोut("%s osd%d unknown\n", __func__, osd->o_osd);
		जाओ out_unlock_osdc;
	पूर्ण
	WARN_ON(osd->o_osd != le64_to_cpu(msg->hdr.src.num));

	mutex_lock(&osd->lock);
	req = lookup_request(&osd->o_requests, tid);
	अगर (!req) अणु
		करोut("%s osd%d tid %llu unknown\n", __func__, osd->o_osd, tid);
		जाओ out_unlock_session;
	पूर्ण

	m.redirect.oloc.pool_ns = req->r_t.target_oloc.pool_ns;
	ret = decode_MOSDOpReply(msg, &m);
	m.redirect.oloc.pool_ns = शून्य;
	अगर (ret) अणु
		pr_err("failed to decode MOSDOpReply for tid %llu: %d\n",
		       req->r_tid, ret);
		ceph_msg_dump(msg);
		जाओ fail_request;
	पूर्ण
	करोut("%s req %p tid %llu flags 0x%llx pgid %llu.%x epoch %u attempt %d v %u'%llu uv %llu\n",
	     __func__, req, req->r_tid, m.flags, m.pgid.pool, m.pgid.seed,
	     m.epoch, m.retry_attempt, le32_to_cpu(m.replay_version.epoch),
	     le64_to_cpu(m.replay_version.version), m.user_version);

	अगर (m.retry_attempt >= 0) अणु
		अगर (m.retry_attempt != req->r_attempts - 1) अणु
			करोut("req %p tid %llu retry_attempt %d != %d, ignoring\n",
			     req, req->r_tid, m.retry_attempt,
			     req->r_attempts - 1);
			जाओ out_unlock_session;
		पूर्ण
	पूर्ण अन्यथा अणु
		WARN_ON(1); /* MOSDOpReply v4 is assumed */
	पूर्ण

	अगर (!ceph_oloc_empty(&m.redirect.oloc)) अणु
		करोut("req %p tid %llu redirect pool %lld\n", req, req->r_tid,
		     m.redirect.oloc.pool);
		unlink_request(osd, req);
		mutex_unlock(&osd->lock);

		/*
		 * Not ceph_oloc_copy() - changing pool_ns is not
		 * supported.
		 */
		req->r_t.target_oloc.pool = m.redirect.oloc.pool;
		req->r_flags |= CEPH_OSD_FLAG_REसूचीECTED |
				CEPH_OSD_FLAG_IGNORE_OVERLAY |
				CEPH_OSD_FLAG_IGNORE_CACHE;
		req->r_tid = 0;
		__submit_request(req, false);
		जाओ out_unlock_osdc;
	पूर्ण

	अगर (m.result == -EAGAIN) अणु
		करोut("req %p tid %llu EAGAIN\n", req, req->r_tid);
		unlink_request(osd, req);
		mutex_unlock(&osd->lock);

		/*
		 * The object is missing on the replica or not (yet)
		 * पढ़ोable.  Clear pgid to क्रमce a resend to the primary
		 * via legacy_change.
		 */
		req->r_t.pgid.pool = 0;
		req->r_t.pgid.seed = 0;
		WARN_ON(!req->r_t.used_replica);
		req->r_flags &= ~(CEPH_OSD_FLAG_BALANCE_READS |
				  CEPH_OSD_FLAG_LOCALIZE_READS);
		req->r_tid = 0;
		__submit_request(req, false);
		जाओ out_unlock_osdc;
	पूर्ण

	अगर (m.num_ops != req->r_num_ops) अणु
		pr_err("num_ops %d != %d for tid %llu\n", m.num_ops,
		       req->r_num_ops, req->r_tid);
		जाओ fail_request;
	पूर्ण
	क्रम (i = 0; i < req->r_num_ops; i++) अणु
		करोut(" req %p tid %llu op %d rval %d len %u\n", req,
		     req->r_tid, i, m.rval[i], m.outdata_len[i]);
		req->r_ops[i].rval = m.rval[i];
		req->r_ops[i].outdata_len = m.outdata_len[i];
		data_len += m.outdata_len[i];
	पूर्ण
	अगर (data_len != le32_to_cpu(msg->hdr.data_len)) अणु
		pr_err("sum of lens %u != %u for tid %llu\n", data_len,
		       le32_to_cpu(msg->hdr.data_len), req->r_tid);
		जाओ fail_request;
	पूर्ण
	करोut("%s req %p tid %llu result %d data_len %u\n", __func__,
	     req, req->r_tid, m.result, data_len);

	/*
	 * Since we only ever request ONDISK, we should only ever get
	 * one (type of) reply back.
	 */
	WARN_ON(!(m.flags & CEPH_OSD_FLAG_ONDISK));
	req->r_result = m.result ?: data_len;
	finish_request(req);
	mutex_unlock(&osd->lock);
	up_पढ़ो(&osdc->lock);

	__complete_request(req);
	वापस;

fail_request:
	complete_request(req, -EIO);
out_unlock_session:
	mutex_unlock(&osd->lock);
out_unlock_osdc:
	up_पढ़ो(&osdc->lock);
पूर्ण

अटल व्योम set_pool_was_full(काष्ठा ceph_osd_client *osdc)
अणु
	काष्ठा rb_node *n;

	क्रम (n = rb_first(&osdc->osdmap->pg_pools); n; n = rb_next(n)) अणु
		काष्ठा ceph_pg_pool_info *pi =
		    rb_entry(n, काष्ठा ceph_pg_pool_info, node);

		pi->was_full = __pool_full(pi);
	पूर्ण
पूर्ण

अटल bool pool_cleared_full(काष्ठा ceph_osd_client *osdc, s64 pool_id)
अणु
	काष्ठा ceph_pg_pool_info *pi;

	pi = ceph_pg_pool_by_id(osdc->osdmap, pool_id);
	अगर (!pi)
		वापस false;

	वापस pi->was_full && !__pool_full(pi);
पूर्ण

अटल क्रमागत calc_target_result
recalc_linger_target(काष्ठा ceph_osd_linger_request *lreq)
अणु
	काष्ठा ceph_osd_client *osdc = lreq->osdc;
	क्रमागत calc_target_result ct_res;

	ct_res = calc_target(osdc, &lreq->t, true);
	अगर (ct_res == CALC_TARGET_NEED_RESEND) अणु
		काष्ठा ceph_osd *osd;

		osd = lookup_create_osd(osdc, lreq->t.osd, true);
		अगर (osd != lreq->osd) अणु
			unlink_linger(lreq->osd, lreq);
			link_linger(osd, lreq);
		पूर्ण
	पूर्ण

	वापस ct_res;
पूर्ण

/*
 * Requeue requests whose mapping to an OSD has changed.
 */
अटल व्योम scan_requests(काष्ठा ceph_osd *osd,
			  bool क्रमce_resend,
			  bool cleared_full,
			  bool check_pool_cleared_full,
			  काष्ठा rb_root *need_resend,
			  काष्ठा list_head *need_resend_linger)
अणु
	काष्ठा ceph_osd_client *osdc = osd->o_osdc;
	काष्ठा rb_node *n;
	bool क्रमce_resend_ग_लिखोs;

	क्रम (n = rb_first(&osd->o_linger_requests); n; ) अणु
		काष्ठा ceph_osd_linger_request *lreq =
		    rb_entry(n, काष्ठा ceph_osd_linger_request, node);
		क्रमागत calc_target_result ct_res;

		n = rb_next(n); /* recalc_linger_target() */

		करोut("%s lreq %p linger_id %llu\n", __func__, lreq,
		     lreq->linger_id);
		ct_res = recalc_linger_target(lreq);
		चयन (ct_res) अणु
		हाल CALC_TARGET_NO_ACTION:
			क्रमce_resend_ग_लिखोs = cleared_full ||
			    (check_pool_cleared_full &&
			     pool_cleared_full(osdc, lreq->t.base_oloc.pool));
			अगर (!क्रमce_resend && !क्रमce_resend_ग_लिखोs)
				अवरोध;

			fallthrough;
		हाल CALC_TARGET_NEED_RESEND:
			cancel_linger_map_check(lreq);
			/*
			 * scan_requests() क्रम the previous epoch(s)
			 * may have alपढ़ोy added it to the list, since
			 * it's not unlinked here.
			 */
			अगर (list_empty(&lreq->scan_item))
				list_add_tail(&lreq->scan_item, need_resend_linger);
			अवरोध;
		हाल CALC_TARGET_POOL_DNE:
			list_del_init(&lreq->scan_item);
			check_linger_pool_dne(lreq);
			अवरोध;
		पूर्ण
	पूर्ण

	क्रम (n = rb_first(&osd->o_requests); n; ) अणु
		काष्ठा ceph_osd_request *req =
		    rb_entry(n, काष्ठा ceph_osd_request, r_node);
		क्रमागत calc_target_result ct_res;

		n = rb_next(n); /* unlink_request(), check_pool_dne() */

		करोut("%s req %p tid %llu\n", __func__, req, req->r_tid);
		ct_res = calc_target(osdc, &req->r_t, false);
		चयन (ct_res) अणु
		हाल CALC_TARGET_NO_ACTION:
			क्रमce_resend_ग_लिखोs = cleared_full ||
			    (check_pool_cleared_full &&
			     pool_cleared_full(osdc, req->r_t.base_oloc.pool));
			अगर (!क्रमce_resend &&
			    (!(req->r_flags & CEPH_OSD_FLAG_WRITE) ||
			     !क्रमce_resend_ग_लिखोs))
				अवरोध;

			fallthrough;
		हाल CALC_TARGET_NEED_RESEND:
			cancel_map_check(req);
			unlink_request(osd, req);
			insert_request(need_resend, req);
			अवरोध;
		हाल CALC_TARGET_POOL_DNE:
			check_pool_dne(req);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक handle_one_map(काष्ठा ceph_osd_client *osdc,
			  व्योम *p, व्योम *end, bool incremental,
			  काष्ठा rb_root *need_resend,
			  काष्ठा list_head *need_resend_linger)
अणु
	काष्ठा ceph_osdmap *newmap;
	काष्ठा rb_node *n;
	bool skipped_map = false;
	bool was_full;

	was_full = ceph_osdmap_flag(osdc, CEPH_OSDMAP_FULL);
	set_pool_was_full(osdc);

	अगर (incremental)
		newmap = osdmap_apply_incremental(&p, end,
						  ceph_msgr2(osdc->client),
						  osdc->osdmap);
	अन्यथा
		newmap = ceph_osdmap_decode(&p, end, ceph_msgr2(osdc->client));
	अगर (IS_ERR(newmap))
		वापस PTR_ERR(newmap);

	अगर (newmap != osdc->osdmap) अणु
		/*
		 * Preserve ->was_full beक्रमe destroying the old map.
		 * For pools that weren't in the old map, ->was_full
		 * should be false.
		 */
		क्रम (n = rb_first(&newmap->pg_pools); n; n = rb_next(n)) अणु
			काष्ठा ceph_pg_pool_info *pi =
			    rb_entry(n, काष्ठा ceph_pg_pool_info, node);
			काष्ठा ceph_pg_pool_info *old_pi;

			old_pi = ceph_pg_pool_by_id(osdc->osdmap, pi->id);
			अगर (old_pi)
				pi->was_full = old_pi->was_full;
			अन्यथा
				WARN_ON(pi->was_full);
		पूर्ण

		अगर (osdc->osdmap->epoch &&
		    osdc->osdmap->epoch + 1 < newmap->epoch) अणु
			WARN_ON(incremental);
			skipped_map = true;
		पूर्ण

		ceph_osdmap_destroy(osdc->osdmap);
		osdc->osdmap = newmap;
	पूर्ण

	was_full &= !ceph_osdmap_flag(osdc, CEPH_OSDMAP_FULL);
	scan_requests(&osdc->homeless_osd, skipped_map, was_full, true,
		      need_resend, need_resend_linger);

	क्रम (n = rb_first(&osdc->osds); n; ) अणु
		काष्ठा ceph_osd *osd = rb_entry(n, काष्ठा ceph_osd, o_node);

		n = rb_next(n); /* बंद_osd() */

		scan_requests(osd, skipped_map, was_full, true, need_resend,
			      need_resend_linger);
		अगर (!ceph_osd_is_up(osdc->osdmap, osd->o_osd) ||
		    स_भेद(&osd->o_con.peer_addr,
			   ceph_osd_addr(osdc->osdmap, osd->o_osd),
			   माप(काष्ठा ceph_entity_addr)))
			बंद_osd(osd);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम kick_requests(काष्ठा ceph_osd_client *osdc,
			  काष्ठा rb_root *need_resend,
			  काष्ठा list_head *need_resend_linger)
अणु
	काष्ठा ceph_osd_linger_request *lreq, *nlreq;
	क्रमागत calc_target_result ct_res;
	काष्ठा rb_node *n;

	/* make sure need_resend tarमाला_लो reflect latest map */
	क्रम (n = rb_first(need_resend); n; ) अणु
		काष्ठा ceph_osd_request *req =
		    rb_entry(n, काष्ठा ceph_osd_request, r_node);

		n = rb_next(n);

		अगर (req->r_t.epoch < osdc->osdmap->epoch) अणु
			ct_res = calc_target(osdc, &req->r_t, false);
			अगर (ct_res == CALC_TARGET_POOL_DNE) अणु
				erase_request(need_resend, req);
				check_pool_dne(req);
			पूर्ण
		पूर्ण
	पूर्ण

	क्रम (n = rb_first(need_resend); n; ) अणु
		काष्ठा ceph_osd_request *req =
		    rb_entry(n, काष्ठा ceph_osd_request, r_node);
		काष्ठा ceph_osd *osd;

		n = rb_next(n);
		erase_request(need_resend, req); /* beक्रमe link_request() */

		osd = lookup_create_osd(osdc, req->r_t.osd, true);
		link_request(osd, req);
		अगर (!req->r_linger) अणु
			अगर (!osd_homeless(osd) && !req->r_t.छोड़ोd)
				send_request(req);
		पूर्ण अन्यथा अणु
			cancel_linger_request(req);
		पूर्ण
	पूर्ण

	list_क्रम_each_entry_safe(lreq, nlreq, need_resend_linger, scan_item) अणु
		अगर (!osd_homeless(lreq->osd))
			send_linger(lreq);

		list_del_init(&lreq->scan_item);
	पूर्ण
पूर्ण

/*
 * Process updated osd map.
 *
 * The message contains any number of incremental and full maps, normally
 * indicating some sort of topology change in the cluster.  Kick requests
 * off to dअगरferent OSDs as needed.
 */
व्योम ceph_osdc_handle_map(काष्ठा ceph_osd_client *osdc, काष्ठा ceph_msg *msg)
अणु
	व्योम *p = msg->front.iov_base;
	व्योम *स्थिर end = p + msg->front.iov_len;
	u32 nr_maps, maplen;
	u32 epoch;
	काष्ठा ceph_fsid fsid;
	काष्ठा rb_root need_resend = RB_ROOT;
	LIST_HEAD(need_resend_linger);
	bool handled_incremental = false;
	bool was_छोड़ोrd, was_छोड़ोwr;
	bool छोड़ोrd, छोड़ोwr;
	पूर्णांक err;

	करोut("%s have %u\n", __func__, osdc->osdmap->epoch);
	करोwn_ग_लिखो(&osdc->lock);

	/* verअगरy fsid */
	ceph_decode_need(&p, end, माप(fsid), bad);
	ceph_decode_copy(&p, &fsid, माप(fsid));
	अगर (ceph_check_fsid(osdc->client, &fsid) < 0)
		जाओ bad;

	was_छोड़ोrd = ceph_osdmap_flag(osdc, CEPH_OSDMAP_PAUSERD);
	was_छोड़ोwr = ceph_osdmap_flag(osdc, CEPH_OSDMAP_PAUSEWR) ||
		      ceph_osdmap_flag(osdc, CEPH_OSDMAP_FULL) ||
		      have_pool_full(osdc);

	/* incremental maps */
	ceph_decode_32_safe(&p, end, nr_maps, bad);
	करोut(" %d inc maps\n", nr_maps);
	जबतक (nr_maps > 0) अणु
		ceph_decode_need(&p, end, 2*माप(u32), bad);
		epoch = ceph_decode_32(&p);
		maplen = ceph_decode_32(&p);
		ceph_decode_need(&p, end, maplen, bad);
		अगर (osdc->osdmap->epoch &&
		    osdc->osdmap->epoch + 1 == epoch) अणु
			करोut("applying incremental map %u len %d\n",
			     epoch, maplen);
			err = handle_one_map(osdc, p, p + maplen, true,
					     &need_resend, &need_resend_linger);
			अगर (err)
				जाओ bad;
			handled_incremental = true;
		पूर्ण अन्यथा अणु
			करोut("ignoring incremental map %u len %d\n",
			     epoch, maplen);
		पूर्ण
		p += maplen;
		nr_maps--;
	पूर्ण
	अगर (handled_incremental)
		जाओ करोne;

	/* full maps */
	ceph_decode_32_safe(&p, end, nr_maps, bad);
	करोut(" %d full maps\n", nr_maps);
	जबतक (nr_maps) अणु
		ceph_decode_need(&p, end, 2*माप(u32), bad);
		epoch = ceph_decode_32(&p);
		maplen = ceph_decode_32(&p);
		ceph_decode_need(&p, end, maplen, bad);
		अगर (nr_maps > 1) अणु
			करोut("skipping non-latest full map %u len %d\n",
			     epoch, maplen);
		पूर्ण अन्यथा अगर (osdc->osdmap->epoch >= epoch) अणु
			करोut("skipping full map %u len %d, "
			     "older than our %u\n", epoch, maplen,
			     osdc->osdmap->epoch);
		पूर्ण अन्यथा अणु
			करोut("taking full map %u len %d\n", epoch, maplen);
			err = handle_one_map(osdc, p, p + maplen, false,
					     &need_resend, &need_resend_linger);
			अगर (err)
				जाओ bad;
		पूर्ण
		p += maplen;
		nr_maps--;
	पूर्ण

करोne:
	/*
	 * subscribe to subsequent osdmap updates अगर full to ensure
	 * we find out when we are no दीर्घer full and stop वापसing
	 * ENOSPC.
	 */
	छोड़ोrd = ceph_osdmap_flag(osdc, CEPH_OSDMAP_PAUSERD);
	छोड़ोwr = ceph_osdmap_flag(osdc, CEPH_OSDMAP_PAUSEWR) ||
		  ceph_osdmap_flag(osdc, CEPH_OSDMAP_FULL) ||
		  have_pool_full(osdc);
	अगर (was_छोड़ोrd || was_छोड़ोwr || छोड़ोrd || छोड़ोwr ||
	    osdc->osdmap->epoch < osdc->epoch_barrier)
		maybe_request_map(osdc);

	kick_requests(osdc, &need_resend, &need_resend_linger);

	ceph_osdc_पात_on_full(osdc);
	ceph_monc_got_map(&osdc->client->monc, CEPH_SUB_OSDMAP,
			  osdc->osdmap->epoch);
	up_ग_लिखो(&osdc->lock);
	wake_up_all(&osdc->client->auth_wq);
	वापस;

bad:
	pr_err("osdc handle_map corrupt msg\n");
	ceph_msg_dump(msg);
	up_ग_लिखो(&osdc->lock);
पूर्ण

/*
 * Resubmit requests pending on the given osd.
 */
अटल व्योम kick_osd_requests(काष्ठा ceph_osd *osd)
अणु
	काष्ठा rb_node *n;

	clear_backoffs(osd);

	क्रम (n = rb_first(&osd->o_requests); n; ) अणु
		काष्ठा ceph_osd_request *req =
		    rb_entry(n, काष्ठा ceph_osd_request, r_node);

		n = rb_next(n); /* cancel_linger_request() */

		अगर (!req->r_linger) अणु
			अगर (!req->r_t.छोड़ोd)
				send_request(req);
		पूर्ण अन्यथा अणु
			cancel_linger_request(req);
		पूर्ण
	पूर्ण
	क्रम (n = rb_first(&osd->o_linger_requests); n; n = rb_next(n)) अणु
		काष्ठा ceph_osd_linger_request *lreq =
		    rb_entry(n, काष्ठा ceph_osd_linger_request, node);

		send_linger(lreq);
	पूर्ण
पूर्ण

/*
 * If the osd connection drops, we need to resubmit all requests.
 */
अटल व्योम osd_fault(काष्ठा ceph_connection *con)
अणु
	काष्ठा ceph_osd *osd = con->निजी;
	काष्ठा ceph_osd_client *osdc = osd->o_osdc;

	करोut("%s osd %p osd%d\n", __func__, osd, osd->o_osd);

	करोwn_ग_लिखो(&osdc->lock);
	अगर (!osd_रेजिस्टरed(osd)) अणु
		करोut("%s osd%d unknown\n", __func__, osd->o_osd);
		जाओ out_unlock;
	पूर्ण

	अगर (!reखोलो_osd(osd))
		kick_osd_requests(osd);
	maybe_request_map(osdc);

out_unlock:
	up_ग_लिखो(&osdc->lock);
पूर्ण

काष्ठा MOSDBackoff अणु
	काष्ठा ceph_spg spgid;
	u32 map_epoch;
	u8 op;
	u64 id;
	काष्ठा ceph_hobject_id *begin;
	काष्ठा ceph_hobject_id *end;
पूर्ण;

अटल पूर्णांक decode_MOSDBackoff(स्थिर काष्ठा ceph_msg *msg, काष्ठा MOSDBackoff *m)
अणु
	व्योम *p = msg->front.iov_base;
	व्योम *स्थिर end = p + msg->front.iov_len;
	u8 काष्ठा_v;
	u32 काष्ठा_len;
	पूर्णांक ret;

	ret = ceph_start_decoding(&p, end, 1, "spg_t", &काष्ठा_v, &काष्ठा_len);
	अगर (ret)
		वापस ret;

	ret = ceph_decode_pgid(&p, end, &m->spgid.pgid);
	अगर (ret)
		वापस ret;

	ceph_decode_8_safe(&p, end, m->spgid.shard, e_inval);
	ceph_decode_32_safe(&p, end, m->map_epoch, e_inval);
	ceph_decode_8_safe(&p, end, m->op, e_inval);
	ceph_decode_64_safe(&p, end, m->id, e_inval);

	m->begin = kzalloc(माप(*m->begin), GFP_NOIO);
	अगर (!m->begin)
		वापस -ENOMEM;

	ret = decode_hoid(&p, end, m->begin);
	अगर (ret) अणु
		मुक्त_hoid(m->begin);
		वापस ret;
	पूर्ण

	m->end = kzalloc(माप(*m->end), GFP_NOIO);
	अगर (!m->end) अणु
		मुक्त_hoid(m->begin);
		वापस -ENOMEM;
	पूर्ण

	ret = decode_hoid(&p, end, m->end);
	अगर (ret) अणु
		मुक्त_hoid(m->begin);
		मुक्त_hoid(m->end);
		वापस ret;
	पूर्ण

	वापस 0;

e_inval:
	वापस -EINVAL;
पूर्ण

अटल काष्ठा ceph_msg *create_backoff_message(
				स्थिर काष्ठा ceph_osd_backoff *backoff,
				u32 map_epoch)
अणु
	काष्ठा ceph_msg *msg;
	व्योम *p, *end;
	पूर्णांक msg_size;

	msg_size = CEPH_ENCODING_START_BLK_LEN +
			CEPH_PGID_ENCODING_LEN + 1; /* spgid */
	msg_size += 4 + 1 + 8; /* map_epoch, op, id */
	msg_size += CEPH_ENCODING_START_BLK_LEN +
			hoid_encoding_size(backoff->begin);
	msg_size += CEPH_ENCODING_START_BLK_LEN +
			hoid_encoding_size(backoff->end);

	msg = ceph_msg_new(CEPH_MSG_OSD_BACKOFF, msg_size, GFP_NOIO, true);
	अगर (!msg)
		वापस शून्य;

	p = msg->front.iov_base;
	end = p + msg->front_alloc_len;

	encode_spgid(&p, &backoff->spgid);
	ceph_encode_32(&p, map_epoch);
	ceph_encode_8(&p, CEPH_OSD_BACKOFF_OP_ACK_BLOCK);
	ceph_encode_64(&p, backoff->id);
	encode_hoid(&p, end, backoff->begin);
	encode_hoid(&p, end, backoff->end);
	BUG_ON(p != end);

	msg->front.iov_len = p - msg->front.iov_base;
	msg->hdr.version = cpu_to_le16(1); /* MOSDBackoff v1 */
	msg->hdr.front_len = cpu_to_le32(msg->front.iov_len);

	वापस msg;
पूर्ण

अटल व्योम handle_backoff_block(काष्ठा ceph_osd *osd, काष्ठा MOSDBackoff *m)
अणु
	काष्ठा ceph_spg_mapping *spg;
	काष्ठा ceph_osd_backoff *backoff;
	काष्ठा ceph_msg *msg;

	करोut("%s osd%d spgid %llu.%xs%d id %llu\n", __func__, osd->o_osd,
	     m->spgid.pgid.pool, m->spgid.pgid.seed, m->spgid.shard, m->id);

	spg = lookup_spg_mapping(&osd->o_backoff_mappings, &m->spgid);
	अगर (!spg) अणु
		spg = alloc_spg_mapping();
		अगर (!spg) अणु
			pr_err("%s failed to allocate spg\n", __func__);
			वापस;
		पूर्ण
		spg->spgid = m->spgid; /* काष्ठा */
		insert_spg_mapping(&osd->o_backoff_mappings, spg);
	पूर्ण

	backoff = alloc_backoff();
	अगर (!backoff) अणु
		pr_err("%s failed to allocate backoff\n", __func__);
		वापस;
	पूर्ण
	backoff->spgid = m->spgid; /* काष्ठा */
	backoff->id = m->id;
	backoff->begin = m->begin;
	m->begin = शून्य; /* backoff now owns this */
	backoff->end = m->end;
	m->end = शून्य;   /* ditto */

	insert_backoff(&spg->backoffs, backoff);
	insert_backoff_by_id(&osd->o_backoffs_by_id, backoff);

	/*
	 * Ack with original backoff's epoch so that the OSD can
	 * discard this अगर there was a PG split.
	 */
	msg = create_backoff_message(backoff, m->map_epoch);
	अगर (!msg) अणु
		pr_err("%s failed to allocate msg\n", __func__);
		वापस;
	पूर्ण
	ceph_con_send(&osd->o_con, msg);
पूर्ण

अटल bool target_contained_by(स्थिर काष्ठा ceph_osd_request_target *t,
				स्थिर काष्ठा ceph_hobject_id *begin,
				स्थिर काष्ठा ceph_hobject_id *end)
अणु
	काष्ठा ceph_hobject_id hoid;
	पूर्णांक cmp;

	hoid_fill_from_target(&hoid, t);
	cmp = hoid_compare(&hoid, begin);
	वापस !cmp || (cmp > 0 && hoid_compare(&hoid, end) < 0);
पूर्ण

अटल व्योम handle_backoff_unblock(काष्ठा ceph_osd *osd,
				   स्थिर काष्ठा MOSDBackoff *m)
अणु
	काष्ठा ceph_spg_mapping *spg;
	काष्ठा ceph_osd_backoff *backoff;
	काष्ठा rb_node *n;

	करोut("%s osd%d spgid %llu.%xs%d id %llu\n", __func__, osd->o_osd,
	     m->spgid.pgid.pool, m->spgid.pgid.seed, m->spgid.shard, m->id);

	backoff = lookup_backoff_by_id(&osd->o_backoffs_by_id, m->id);
	अगर (!backoff) अणु
		pr_err("%s osd%d spgid %llu.%xs%d id %llu backoff dne\n",
		       __func__, osd->o_osd, m->spgid.pgid.pool,
		       m->spgid.pgid.seed, m->spgid.shard, m->id);
		वापस;
	पूर्ण

	अगर (hoid_compare(backoff->begin, m->begin) &&
	    hoid_compare(backoff->end, m->end)) अणु
		pr_err("%s osd%d spgid %llu.%xs%d id %llu bad range?\n",
		       __func__, osd->o_osd, m->spgid.pgid.pool,
		       m->spgid.pgid.seed, m->spgid.shard, m->id);
		/* unblock it anyway... */
	पूर्ण

	spg = lookup_spg_mapping(&osd->o_backoff_mappings, &backoff->spgid);
	BUG_ON(!spg);

	erase_backoff(&spg->backoffs, backoff);
	erase_backoff_by_id(&osd->o_backoffs_by_id, backoff);
	मुक्त_backoff(backoff);

	अगर (RB_EMPTY_ROOT(&spg->backoffs)) अणु
		erase_spg_mapping(&osd->o_backoff_mappings, spg);
		मुक्त_spg_mapping(spg);
	पूर्ण

	क्रम (n = rb_first(&osd->o_requests); n; n = rb_next(n)) अणु
		काष्ठा ceph_osd_request *req =
		    rb_entry(n, काष्ठा ceph_osd_request, r_node);

		अगर (!ceph_spg_compare(&req->r_t.spgid, &m->spgid)) अणु
			/*
			 * Match against @m, not @backoff -- the PG may
			 * have split on the OSD.
			 */
			अगर (target_contained_by(&req->r_t, m->begin, m->end)) अणु
				/*
				 * If no other installed backoff applies,
				 * resend.
				 */
				send_request(req);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम handle_backoff(काष्ठा ceph_osd *osd, काष्ठा ceph_msg *msg)
अणु
	काष्ठा ceph_osd_client *osdc = osd->o_osdc;
	काष्ठा MOSDBackoff m;
	पूर्णांक ret;

	करोwn_पढ़ो(&osdc->lock);
	अगर (!osd_रेजिस्टरed(osd)) अणु
		करोut("%s osd%d unknown\n", __func__, osd->o_osd);
		up_पढ़ो(&osdc->lock);
		वापस;
	पूर्ण
	WARN_ON(osd->o_osd != le64_to_cpu(msg->hdr.src.num));

	mutex_lock(&osd->lock);
	ret = decode_MOSDBackoff(msg, &m);
	अगर (ret) अणु
		pr_err("failed to decode MOSDBackoff: %d\n", ret);
		ceph_msg_dump(msg);
		जाओ out_unlock;
	पूर्ण

	चयन (m.op) अणु
	हाल CEPH_OSD_BACKOFF_OP_BLOCK:
		handle_backoff_block(osd, &m);
		अवरोध;
	हाल CEPH_OSD_BACKOFF_OP_UNBLOCK:
		handle_backoff_unblock(osd, &m);
		अवरोध;
	शेष:
		pr_err("%s osd%d unknown op %d\n", __func__, osd->o_osd, m.op);
	पूर्ण

	मुक्त_hoid(m.begin);
	मुक्त_hoid(m.end);

out_unlock:
	mutex_unlock(&osd->lock);
	up_पढ़ो(&osdc->lock);
पूर्ण

/*
 * Process osd watch notअगरications
 */
अटल व्योम handle_watch_notअगरy(काष्ठा ceph_osd_client *osdc,
				काष्ठा ceph_msg *msg)
अणु
	व्योम *p = msg->front.iov_base;
	व्योम *स्थिर end = p + msg->front.iov_len;
	काष्ठा ceph_osd_linger_request *lreq;
	काष्ठा linger_work *lwork;
	u8 proto_ver, opcode;
	u64 cookie, notअगरy_id;
	u64 notअगरier_id = 0;
	s32 वापस_code = 0;
	व्योम *payload = शून्य;
	u32 payload_len = 0;

	ceph_decode_8_safe(&p, end, proto_ver, bad);
	ceph_decode_8_safe(&p, end, opcode, bad);
	ceph_decode_64_safe(&p, end, cookie, bad);
	p += 8; /* skip ver */
	ceph_decode_64_safe(&p, end, notअगरy_id, bad);

	अगर (proto_ver >= 1) अणु
		ceph_decode_32_safe(&p, end, payload_len, bad);
		ceph_decode_need(&p, end, payload_len, bad);
		payload = p;
		p += payload_len;
	पूर्ण

	अगर (le16_to_cpu(msg->hdr.version) >= 2)
		ceph_decode_32_safe(&p, end, वापस_code, bad);

	अगर (le16_to_cpu(msg->hdr.version) >= 3)
		ceph_decode_64_safe(&p, end, notअगरier_id, bad);

	करोwn_पढ़ो(&osdc->lock);
	lreq = lookup_linger_osdc(&osdc->linger_requests, cookie);
	अगर (!lreq) अणु
		करोut("%s opcode %d cookie %llu dne\n", __func__, opcode,
		     cookie);
		जाओ out_unlock_osdc;
	पूर्ण

	mutex_lock(&lreq->lock);
	करोut("%s opcode %d cookie %llu lreq %p is_watch %d\n", __func__,
	     opcode, cookie, lreq, lreq->is_watch);
	अगर (opcode == CEPH_WATCH_EVENT_DISCONNECT) अणु
		अगर (!lreq->last_error) अणु
			lreq->last_error = -ENOTCONN;
			queue_watch_error(lreq);
		पूर्ण
	पूर्ण अन्यथा अगर (!lreq->is_watch) अणु
		/* CEPH_WATCH_EVENT_NOTIFY_COMPLETE */
		अगर (lreq->notअगरy_id && lreq->notअगरy_id != notअगरy_id) अणु
			करोut("lreq %p notify_id %llu != %llu, ignoring\n", lreq,
			     lreq->notअगरy_id, notअगरy_id);
		पूर्ण अन्यथा अगर (!completion_करोne(&lreq->notअगरy_finish_रुको)) अणु
			काष्ठा ceph_msg_data *data =
			    msg->num_data_items ? &msg->data[0] : शून्य;

			अगर (data) अणु
				अगर (lreq->preply_pages) अणु
					WARN_ON(data->type !=
							CEPH_MSG_DATA_PAGES);
					*lreq->preply_pages = data->pages;
					*lreq->preply_len = data->length;
					data->own_pages = false;
				पूर्ण
			पूर्ण
			lreq->notअगरy_finish_error = वापस_code;
			complete_all(&lreq->notअगरy_finish_रुको);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* CEPH_WATCH_EVENT_NOTIFY */
		lwork = lwork_alloc(lreq, करो_watch_notअगरy);
		अगर (!lwork) अणु
			pr_err("failed to allocate notify-lwork\n");
			जाओ out_unlock_lreq;
		पूर्ण

		lwork->notअगरy.notअगरy_id = notअगरy_id;
		lwork->notअगरy.notअगरier_id = notअगरier_id;
		lwork->notअगरy.payload = payload;
		lwork->notअगरy.payload_len = payload_len;
		lwork->notअगरy.msg = ceph_msg_get(msg);
		lwork_queue(lwork);
	पूर्ण

out_unlock_lreq:
	mutex_unlock(&lreq->lock);
out_unlock_osdc:
	up_पढ़ो(&osdc->lock);
	वापस;

bad:
	pr_err("osdc handle_watch_notify corrupt msg\n");
पूर्ण

/*
 * Register request, send initial attempt.
 */
पूर्णांक ceph_osdc_start_request(काष्ठा ceph_osd_client *osdc,
			    काष्ठा ceph_osd_request *req,
			    bool nofail)
अणु
	करोwn_पढ़ो(&osdc->lock);
	submit_request(req, false);
	up_पढ़ो(&osdc->lock);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(ceph_osdc_start_request);

/*
 * Unरेजिस्टर a रेजिस्टरed request.  The request is not completed:
 * ->r_result isn't set and __complete_request() isn't called.
 */
व्योम ceph_osdc_cancel_request(काष्ठा ceph_osd_request *req)
अणु
	काष्ठा ceph_osd_client *osdc = req->r_osdc;

	करोwn_ग_लिखो(&osdc->lock);
	अगर (req->r_osd)
		cancel_request(req);
	up_ग_लिखो(&osdc->lock);
पूर्ण
EXPORT_SYMBOL(ceph_osdc_cancel_request);

/*
 * @समयout: in jअगरfies, 0 means "wait forever"
 */
अटल पूर्णांक रुको_request_समयout(काष्ठा ceph_osd_request *req,
				अचिन्हित दीर्घ समयout)
अणु
	दीर्घ left;

	करोut("%s req %p tid %llu\n", __func__, req, req->r_tid);
	left = रुको_क्रम_completion_समाप्तable_समयout(&req->r_completion,
						ceph_समयout_jअगरfies(समयout));
	अगर (left <= 0) अणु
		left = left ?: -ETIMEDOUT;
		ceph_osdc_cancel_request(req);
	पूर्ण अन्यथा अणु
		left = req->r_result; /* completed */
	पूर्ण

	वापस left;
पूर्ण

/*
 * रुको क्रम a request to complete
 */
पूर्णांक ceph_osdc_रुको_request(काष्ठा ceph_osd_client *osdc,
			   काष्ठा ceph_osd_request *req)
अणु
	वापस रुको_request_समयout(req, 0);
पूर्ण
EXPORT_SYMBOL(ceph_osdc_रुको_request);

/*
 * sync - रुको क्रम all in-flight requests to flush.  aव्योम starvation.
 */
व्योम ceph_osdc_sync(काष्ठा ceph_osd_client *osdc)
अणु
	काष्ठा rb_node *n, *p;
	u64 last_tid = atomic64_पढ़ो(&osdc->last_tid);

again:
	करोwn_पढ़ो(&osdc->lock);
	क्रम (n = rb_first(&osdc->osds); n; n = rb_next(n)) अणु
		काष्ठा ceph_osd *osd = rb_entry(n, काष्ठा ceph_osd, o_node);

		mutex_lock(&osd->lock);
		क्रम (p = rb_first(&osd->o_requests); p; p = rb_next(p)) अणु
			काष्ठा ceph_osd_request *req =
			    rb_entry(p, काष्ठा ceph_osd_request, r_node);

			अगर (req->r_tid > last_tid)
				अवरोध;

			अगर (!(req->r_flags & CEPH_OSD_FLAG_WRITE))
				जारी;

			ceph_osdc_get_request(req);
			mutex_unlock(&osd->lock);
			up_पढ़ो(&osdc->lock);
			करोut("%s waiting on req %p tid %llu last_tid %llu\n",
			     __func__, req, req->r_tid, last_tid);
			रुको_क्रम_completion(&req->r_completion);
			ceph_osdc_put_request(req);
			जाओ again;
		पूर्ण

		mutex_unlock(&osd->lock);
	पूर्ण

	up_पढ़ो(&osdc->lock);
	करोut("%s done last_tid %llu\n", __func__, last_tid);
पूर्ण
EXPORT_SYMBOL(ceph_osdc_sync);

अटल काष्ठा ceph_osd_request *
alloc_linger_request(काष्ठा ceph_osd_linger_request *lreq)
अणु
	काष्ठा ceph_osd_request *req;

	req = ceph_osdc_alloc_request(lreq->osdc, शून्य, 1, false, GFP_NOIO);
	अगर (!req)
		वापस शून्य;

	ceph_oid_copy(&req->r_base_oid, &lreq->t.base_oid);
	ceph_oloc_copy(&req->r_base_oloc, &lreq->t.base_oloc);
	वापस req;
पूर्ण

अटल काष्ठा ceph_osd_request *
alloc_watch_request(काष्ठा ceph_osd_linger_request *lreq, u8 watch_opcode)
अणु
	काष्ठा ceph_osd_request *req;

	req = alloc_linger_request(lreq);
	अगर (!req)
		वापस शून्य;

	/*
	 * Pass 0 क्रम cookie because we करोn't know it yet, it will be
	 * filled in by linger_submit().
	 */
	osd_req_op_watch_init(req, 0, 0, watch_opcode);

	अगर (ceph_osdc_alloc_messages(req, GFP_NOIO)) अणु
		ceph_osdc_put_request(req);
		वापस शून्य;
	पूर्ण

	वापस req;
पूर्ण

/*
 * Returns a handle, caller owns a ref.
 */
काष्ठा ceph_osd_linger_request *
ceph_osdc_watch(काष्ठा ceph_osd_client *osdc,
		काष्ठा ceph_object_id *oid,
		काष्ठा ceph_object_locator *oloc,
		raकरोs_watchcb2_t wcb,
		raकरोs_watcherrcb_t errcb,
		व्योम *data)
अणु
	काष्ठा ceph_osd_linger_request *lreq;
	पूर्णांक ret;

	lreq = linger_alloc(osdc);
	अगर (!lreq)
		वापस ERR_PTR(-ENOMEM);

	lreq->is_watch = true;
	lreq->wcb = wcb;
	lreq->errcb = errcb;
	lreq->data = data;
	lreq->watch_valid_thru = jअगरfies;

	ceph_oid_copy(&lreq->t.base_oid, oid);
	ceph_oloc_copy(&lreq->t.base_oloc, oloc);
	lreq->t.flags = CEPH_OSD_FLAG_WRITE;
	kसमय_get_real_ts64(&lreq->mसमय);

	lreq->reg_req = alloc_watch_request(lreq, CEPH_OSD_WATCH_OP_WATCH);
	अगर (!lreq->reg_req) अणु
		ret = -ENOMEM;
		जाओ err_put_lreq;
	पूर्ण

	lreq->ping_req = alloc_watch_request(lreq, CEPH_OSD_WATCH_OP_PING);
	अगर (!lreq->ping_req) अणु
		ret = -ENOMEM;
		जाओ err_put_lreq;
	पूर्ण

	linger_submit(lreq);
	ret = linger_reg_commit_रुको(lreq);
	अगर (ret) अणु
		linger_cancel(lreq);
		जाओ err_put_lreq;
	पूर्ण

	वापस lreq;

err_put_lreq:
	linger_put(lreq);
	वापस ERR_PTR(ret);
पूर्ण
EXPORT_SYMBOL(ceph_osdc_watch);

/*
 * Releases a ref.
 *
 * Times out after mount_समयout to preserve rbd unmap behaviour
 * पूर्णांकroduced in 2894e1d76974 ("rbd: समयout watch tearकरोwn on unmap
 * with mount_समयout").
 */
पूर्णांक ceph_osdc_unwatch(काष्ठा ceph_osd_client *osdc,
		      काष्ठा ceph_osd_linger_request *lreq)
अणु
	काष्ठा ceph_options *opts = osdc->client->options;
	काष्ठा ceph_osd_request *req;
	पूर्णांक ret;

	req = ceph_osdc_alloc_request(osdc, शून्य, 1, false, GFP_NOIO);
	अगर (!req)
		वापस -ENOMEM;

	ceph_oid_copy(&req->r_base_oid, &lreq->t.base_oid);
	ceph_oloc_copy(&req->r_base_oloc, &lreq->t.base_oloc);
	req->r_flags = CEPH_OSD_FLAG_WRITE;
	kसमय_get_real_ts64(&req->r_mसमय);
	osd_req_op_watch_init(req, 0, lreq->linger_id,
			      CEPH_OSD_WATCH_OP_UNWATCH);

	ret = ceph_osdc_alloc_messages(req, GFP_NOIO);
	अगर (ret)
		जाओ out_put_req;

	ceph_osdc_start_request(osdc, req, false);
	linger_cancel(lreq);
	linger_put(lreq);
	ret = रुको_request_समयout(req, opts->mount_समयout);

out_put_req:
	ceph_osdc_put_request(req);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(ceph_osdc_unwatch);

अटल पूर्णांक osd_req_op_notअगरy_ack_init(काष्ठा ceph_osd_request *req, पूर्णांक which,
				      u64 notअगरy_id, u64 cookie, व्योम *payload,
				      u32 payload_len)
अणु
	काष्ठा ceph_osd_req_op *op;
	काष्ठा ceph_pagelist *pl;
	पूर्णांक ret;

	op = osd_req_op_init(req, which, CEPH_OSD_OP_NOTIFY_ACK, 0);

	pl = ceph_pagelist_alloc(GFP_NOIO);
	अगर (!pl)
		वापस -ENOMEM;

	ret = ceph_pagelist_encode_64(pl, notअगरy_id);
	ret |= ceph_pagelist_encode_64(pl, cookie);
	अगर (payload) अणु
		ret |= ceph_pagelist_encode_32(pl, payload_len);
		ret |= ceph_pagelist_append(pl, payload, payload_len);
	पूर्ण अन्यथा अणु
		ret |= ceph_pagelist_encode_32(pl, 0);
	पूर्ण
	अगर (ret) अणु
		ceph_pagelist_release(pl);
		वापस -ENOMEM;
	पूर्ण

	ceph_osd_data_pagelist_init(&op->notअगरy_ack.request_data, pl);
	op->indata_len = pl->length;
	वापस 0;
पूर्ण

पूर्णांक ceph_osdc_notअगरy_ack(काष्ठा ceph_osd_client *osdc,
			 काष्ठा ceph_object_id *oid,
			 काष्ठा ceph_object_locator *oloc,
			 u64 notअगरy_id,
			 u64 cookie,
			 व्योम *payload,
			 u32 payload_len)
अणु
	काष्ठा ceph_osd_request *req;
	पूर्णांक ret;

	req = ceph_osdc_alloc_request(osdc, शून्य, 1, false, GFP_NOIO);
	अगर (!req)
		वापस -ENOMEM;

	ceph_oid_copy(&req->r_base_oid, oid);
	ceph_oloc_copy(&req->r_base_oloc, oloc);
	req->r_flags = CEPH_OSD_FLAG_READ;

	ret = osd_req_op_notअगरy_ack_init(req, 0, notअगरy_id, cookie, payload,
					 payload_len);
	अगर (ret)
		जाओ out_put_req;

	ret = ceph_osdc_alloc_messages(req, GFP_NOIO);
	अगर (ret)
		जाओ out_put_req;

	ceph_osdc_start_request(osdc, req, false);
	ret = ceph_osdc_रुको_request(osdc, req);

out_put_req:
	ceph_osdc_put_request(req);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(ceph_osdc_notअगरy_ack);

अटल पूर्णांक osd_req_op_notअगरy_init(काष्ठा ceph_osd_request *req, पूर्णांक which,
				  u64 cookie, u32 prot_ver, u32 समयout,
				  व्योम *payload, u32 payload_len)
अणु
	काष्ठा ceph_osd_req_op *op;
	काष्ठा ceph_pagelist *pl;
	पूर्णांक ret;

	op = osd_req_op_init(req, which, CEPH_OSD_OP_NOTIFY, 0);
	op->notअगरy.cookie = cookie;

	pl = ceph_pagelist_alloc(GFP_NOIO);
	अगर (!pl)
		वापस -ENOMEM;

	ret = ceph_pagelist_encode_32(pl, 1); /* prot_ver */
	ret |= ceph_pagelist_encode_32(pl, समयout);
	ret |= ceph_pagelist_encode_32(pl, payload_len);
	ret |= ceph_pagelist_append(pl, payload, payload_len);
	अगर (ret) अणु
		ceph_pagelist_release(pl);
		वापस -ENOMEM;
	पूर्ण

	ceph_osd_data_pagelist_init(&op->notअगरy.request_data, pl);
	op->indata_len = pl->length;
	वापस 0;
पूर्ण

/*
 * @समयout: in seconds
 *
 * @preply_अणुpages,lenपूर्ण are initialized both on success and error.
 * The caller is responsible क्रम:
 *
 *     ceph_release_page_vector(reply_pages, calc_pages_क्रम(0, reply_len))
 */
पूर्णांक ceph_osdc_notअगरy(काष्ठा ceph_osd_client *osdc,
		     काष्ठा ceph_object_id *oid,
		     काष्ठा ceph_object_locator *oloc,
		     व्योम *payload,
		     u32 payload_len,
		     u32 समयout,
		     काष्ठा page ***preply_pages,
		     माप_प्रकार *preply_len)
अणु
	काष्ठा ceph_osd_linger_request *lreq;
	काष्ठा page **pages;
	पूर्णांक ret;

	WARN_ON(!समयout);
	अगर (preply_pages) अणु
		*preply_pages = शून्य;
		*preply_len = 0;
	पूर्ण

	lreq = linger_alloc(osdc);
	अगर (!lreq)
		वापस -ENOMEM;

	lreq->preply_pages = preply_pages;
	lreq->preply_len = preply_len;

	ceph_oid_copy(&lreq->t.base_oid, oid);
	ceph_oloc_copy(&lreq->t.base_oloc, oloc);
	lreq->t.flags = CEPH_OSD_FLAG_READ;

	lreq->reg_req = alloc_linger_request(lreq);
	अगर (!lreq->reg_req) अणु
		ret = -ENOMEM;
		जाओ out_put_lreq;
	पूर्ण

	/*
	 * Pass 0 क्रम cookie because we करोn't know it yet, it will be
	 * filled in by linger_submit().
	 */
	ret = osd_req_op_notअगरy_init(lreq->reg_req, 0, 0, 1, समयout,
				     payload, payload_len);
	अगर (ret)
		जाओ out_put_lreq;

	/* क्रम notअगरy_id */
	pages = ceph_alloc_page_vector(1, GFP_NOIO);
	अगर (IS_ERR(pages)) अणु
		ret = PTR_ERR(pages);
		जाओ out_put_lreq;
	पूर्ण
	ceph_osd_data_pages_init(osd_req_op_data(lreq->reg_req, 0, notअगरy,
						 response_data),
				 pages, PAGE_SIZE, 0, false, true);

	ret = ceph_osdc_alloc_messages(lreq->reg_req, GFP_NOIO);
	अगर (ret)
		जाओ out_put_lreq;

	linger_submit(lreq);
	ret = linger_reg_commit_रुको(lreq);
	अगर (!ret)
		ret = linger_notअगरy_finish_रुको(lreq);
	अन्यथा
		करोut("lreq %p failed to initiate notify %d\n", lreq, ret);

	linger_cancel(lreq);
out_put_lreq:
	linger_put(lreq);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(ceph_osdc_notअगरy);

/*
 * Return the number of milliseconds since the watch was last
 * confirmed, or an error.  If there is an error, the watch is no
 * दीर्घer valid, and should be destroyed with ceph_osdc_unwatch().
 */
पूर्णांक ceph_osdc_watch_check(काष्ठा ceph_osd_client *osdc,
			  काष्ठा ceph_osd_linger_request *lreq)
अणु
	अचिन्हित दीर्घ stamp, age;
	पूर्णांक ret;

	करोwn_पढ़ो(&osdc->lock);
	mutex_lock(&lreq->lock);
	stamp = lreq->watch_valid_thru;
	अगर (!list_empty(&lreq->pending_lworks)) अणु
		काष्ठा linger_work *lwork =
		    list_first_entry(&lreq->pending_lworks,
				     काष्ठा linger_work,
				     pending_item);

		अगर (समय_beक्रमe(lwork->queued_stamp, stamp))
			stamp = lwork->queued_stamp;
	पूर्ण
	age = jअगरfies - stamp;
	करोut("%s lreq %p linger_id %llu age %lu last_error %d\n", __func__,
	     lreq, lreq->linger_id, age, lreq->last_error);
	/* we are truncating to msecs, so वापस a safe upper bound */
	ret = lreq->last_error ?: 1 + jअगरfies_to_msecs(age);

	mutex_unlock(&lreq->lock);
	up_पढ़ो(&osdc->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक decode_watcher(व्योम **p, व्योम *end, काष्ठा ceph_watch_item *item)
अणु
	u8 काष्ठा_v;
	u32 काष्ठा_len;
	पूर्णांक ret;

	ret = ceph_start_decoding(p, end, 2, "watch_item_t",
				  &काष्ठा_v, &काष्ठा_len);
	अगर (ret)
		जाओ bad;

	ret = -EINVAL;
	ceph_decode_copy_safe(p, end, &item->name, माप(item->name), bad);
	ceph_decode_64_safe(p, end, item->cookie, bad);
	ceph_decode_skip_32(p, end, bad); /* skip समयout seconds */

	अगर (काष्ठा_v >= 2) अणु
		ret = ceph_decode_entity_addr(p, end, &item->addr);
		अगर (ret)
			जाओ bad;
	पूर्ण अन्यथा अणु
		ret = 0;
	पूर्ण

	करोut("%s %s%llu cookie %llu addr %s\n", __func__,
	     ENTITY_NAME(item->name), item->cookie,
	     ceph_pr_addr(&item->addr));
bad:
	वापस ret;
पूर्ण

अटल पूर्णांक decode_watchers(व्योम **p, व्योम *end,
			   काष्ठा ceph_watch_item **watchers,
			   u32 *num_watchers)
अणु
	u8 काष्ठा_v;
	u32 काष्ठा_len;
	पूर्णांक i;
	पूर्णांक ret;

	ret = ceph_start_decoding(p, end, 1, "obj_list_watch_response_t",
				  &काष्ठा_v, &काष्ठा_len);
	अगर (ret)
		वापस ret;

	*num_watchers = ceph_decode_32(p);
	*watchers = kसुस्मृति(*num_watchers, माप(**watchers), GFP_NOIO);
	अगर (!*watchers)
		वापस -ENOMEM;

	क्रम (i = 0; i < *num_watchers; i++) अणु
		ret = decode_watcher(p, end, *watchers + i);
		अगर (ret) अणु
			kमुक्त(*watchers);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*
 * On success, the caller is responsible क्रम:
 *
 *     kमुक्त(watchers);
 */
पूर्णांक ceph_osdc_list_watchers(काष्ठा ceph_osd_client *osdc,
			    काष्ठा ceph_object_id *oid,
			    काष्ठा ceph_object_locator *oloc,
			    काष्ठा ceph_watch_item **watchers,
			    u32 *num_watchers)
अणु
	काष्ठा ceph_osd_request *req;
	काष्ठा page **pages;
	पूर्णांक ret;

	req = ceph_osdc_alloc_request(osdc, शून्य, 1, false, GFP_NOIO);
	अगर (!req)
		वापस -ENOMEM;

	ceph_oid_copy(&req->r_base_oid, oid);
	ceph_oloc_copy(&req->r_base_oloc, oloc);
	req->r_flags = CEPH_OSD_FLAG_READ;

	pages = ceph_alloc_page_vector(1, GFP_NOIO);
	अगर (IS_ERR(pages)) अणु
		ret = PTR_ERR(pages);
		जाओ out_put_req;
	पूर्ण

	osd_req_op_init(req, 0, CEPH_OSD_OP_LIST_WATCHERS, 0);
	ceph_osd_data_pages_init(osd_req_op_data(req, 0, list_watchers,
						 response_data),
				 pages, PAGE_SIZE, 0, false, true);

	ret = ceph_osdc_alloc_messages(req, GFP_NOIO);
	अगर (ret)
		जाओ out_put_req;

	ceph_osdc_start_request(osdc, req, false);
	ret = ceph_osdc_रुको_request(osdc, req);
	अगर (ret >= 0) अणु
		व्योम *p = page_address(pages[0]);
		व्योम *स्थिर end = p + req->r_ops[0].outdata_len;

		ret = decode_watchers(&p, end, watchers, num_watchers);
	पूर्ण

out_put_req:
	ceph_osdc_put_request(req);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(ceph_osdc_list_watchers);

/*
 * Call all pending notअगरy callbacks - क्रम use after a watch is
 * unरेजिस्टरed, to make sure no more callbacks क्रम it will be invoked
 */
व्योम ceph_osdc_flush_notअगरies(काष्ठा ceph_osd_client *osdc)
अणु
	करोut("%s osdc %p\n", __func__, osdc);
	flush_workqueue(osdc->notअगरy_wq);
पूर्ण
EXPORT_SYMBOL(ceph_osdc_flush_notअगरies);

व्योम ceph_osdc_maybe_request_map(काष्ठा ceph_osd_client *osdc)
अणु
	करोwn_पढ़ो(&osdc->lock);
	maybe_request_map(osdc);
	up_पढ़ो(&osdc->lock);
पूर्ण
EXPORT_SYMBOL(ceph_osdc_maybe_request_map);

/*
 * Execute an OSD class method on an object.
 *
 * @flags: CEPH_OSD_FLAG_*
 * @resp_len: in/out param क्रम reply length
 */
पूर्णांक ceph_osdc_call(काष्ठा ceph_osd_client *osdc,
		   काष्ठा ceph_object_id *oid,
		   काष्ठा ceph_object_locator *oloc,
		   स्थिर अक्षर *class, स्थिर अक्षर *method,
		   अचिन्हित पूर्णांक flags,
		   काष्ठा page *req_page, माप_प्रकार req_len,
		   काष्ठा page **resp_pages, माप_प्रकार *resp_len)
अणु
	काष्ठा ceph_osd_request *req;
	पूर्णांक ret;

	अगर (req_len > PAGE_SIZE)
		वापस -E2BIG;

	req = ceph_osdc_alloc_request(osdc, शून्य, 1, false, GFP_NOIO);
	अगर (!req)
		वापस -ENOMEM;

	ceph_oid_copy(&req->r_base_oid, oid);
	ceph_oloc_copy(&req->r_base_oloc, oloc);
	req->r_flags = flags;

	ret = osd_req_op_cls_init(req, 0, class, method);
	अगर (ret)
		जाओ out_put_req;

	अगर (req_page)
		osd_req_op_cls_request_data_pages(req, 0, &req_page, req_len,
						  0, false, false);
	अगर (resp_pages)
		osd_req_op_cls_response_data_pages(req, 0, resp_pages,
						   *resp_len, 0, false, false);

	ret = ceph_osdc_alloc_messages(req, GFP_NOIO);
	अगर (ret)
		जाओ out_put_req;

	ceph_osdc_start_request(osdc, req, false);
	ret = ceph_osdc_रुको_request(osdc, req);
	अगर (ret >= 0) अणु
		ret = req->r_ops[0].rval;
		अगर (resp_pages)
			*resp_len = req->r_ops[0].outdata_len;
	पूर्ण

out_put_req:
	ceph_osdc_put_request(req);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(ceph_osdc_call);

/*
 * reset all osd connections
 */
व्योम ceph_osdc_reखोलो_osds(काष्ठा ceph_osd_client *osdc)
अणु
	काष्ठा rb_node *n;

	करोwn_ग_लिखो(&osdc->lock);
	क्रम (n = rb_first(&osdc->osds); n; ) अणु
		काष्ठा ceph_osd *osd = rb_entry(n, काष्ठा ceph_osd, o_node);

		n = rb_next(n);
		अगर (!reखोलो_osd(osd))
			kick_osd_requests(osd);
	पूर्ण
	up_ग_लिखो(&osdc->lock);
पूर्ण

/*
 * init, shutकरोwn
 */
पूर्णांक ceph_osdc_init(काष्ठा ceph_osd_client *osdc, काष्ठा ceph_client *client)
अणु
	पूर्णांक err;

	करोut("init\n");
	osdc->client = client;
	init_rwsem(&osdc->lock);
	osdc->osds = RB_ROOT;
	INIT_LIST_HEAD(&osdc->osd_lru);
	spin_lock_init(&osdc->osd_lru_lock);
	osd_init(&osdc->homeless_osd);
	osdc->homeless_osd.o_osdc = osdc;
	osdc->homeless_osd.o_osd = CEPH_HOMELESS_OSD;
	osdc->last_linger_id = CEPH_LINGER_ID_START;
	osdc->linger_requests = RB_ROOT;
	osdc->map_checks = RB_ROOT;
	osdc->linger_map_checks = RB_ROOT;
	INIT_DELAYED_WORK(&osdc->समयout_work, handle_समयout);
	INIT_DELAYED_WORK(&osdc->osds_समयout_work, handle_osds_समयout);

	err = -ENOMEM;
	osdc->osdmap = ceph_osdmap_alloc();
	अगर (!osdc->osdmap)
		जाओ out;

	osdc->req_mempool = mempool_create_slab_pool(10,
						     ceph_osd_request_cache);
	अगर (!osdc->req_mempool)
		जाओ out_map;

	err = ceph_msgpool_init(&osdc->msgpool_op, CEPH_MSG_OSD_OP,
				PAGE_SIZE, CEPH_OSD_SLAB_OPS, 10, "osd_op");
	अगर (err < 0)
		जाओ out_mempool;
	err = ceph_msgpool_init(&osdc->msgpool_op_reply, CEPH_MSG_OSD_OPREPLY,
				PAGE_SIZE, CEPH_OSD_SLAB_OPS, 10,
				"osd_op_reply");
	अगर (err < 0)
		जाओ out_msgpool;

	err = -ENOMEM;
	osdc->notअगरy_wq = create_singlethपढ़ो_workqueue("ceph-watch-notify");
	अगर (!osdc->notअगरy_wq)
		जाओ out_msgpool_reply;

	osdc->completion_wq = create_singlethपढ़ो_workqueue("ceph-completion");
	अगर (!osdc->completion_wq)
		जाओ out_notअगरy_wq;

	schedule_delayed_work(&osdc->समयout_work,
			      osdc->client->options->osd_keepalive_समयout);
	schedule_delayed_work(&osdc->osds_समयout_work,
	    round_jअगरfies_relative(osdc->client->options->osd_idle_ttl));

	वापस 0;

out_notअगरy_wq:
	destroy_workqueue(osdc->notअगरy_wq);
out_msgpool_reply:
	ceph_msgpool_destroy(&osdc->msgpool_op_reply);
out_msgpool:
	ceph_msgpool_destroy(&osdc->msgpool_op);
out_mempool:
	mempool_destroy(osdc->req_mempool);
out_map:
	ceph_osdmap_destroy(osdc->osdmap);
out:
	वापस err;
पूर्ण

व्योम ceph_osdc_stop(काष्ठा ceph_osd_client *osdc)
अणु
	destroy_workqueue(osdc->completion_wq);
	destroy_workqueue(osdc->notअगरy_wq);
	cancel_delayed_work_sync(&osdc->समयout_work);
	cancel_delayed_work_sync(&osdc->osds_समयout_work);

	करोwn_ग_लिखो(&osdc->lock);
	जबतक (!RB_EMPTY_ROOT(&osdc->osds)) अणु
		काष्ठा ceph_osd *osd = rb_entry(rb_first(&osdc->osds),
						काष्ठा ceph_osd, o_node);
		बंद_osd(osd);
	पूर्ण
	up_ग_लिखो(&osdc->lock);
	WARN_ON(refcount_पढ़ो(&osdc->homeless_osd.o_ref) != 1);
	osd_cleanup(&osdc->homeless_osd);

	WARN_ON(!list_empty(&osdc->osd_lru));
	WARN_ON(!RB_EMPTY_ROOT(&osdc->linger_requests));
	WARN_ON(!RB_EMPTY_ROOT(&osdc->map_checks));
	WARN_ON(!RB_EMPTY_ROOT(&osdc->linger_map_checks));
	WARN_ON(atomic_पढ़ो(&osdc->num_requests));
	WARN_ON(atomic_पढ़ो(&osdc->num_homeless));

	ceph_osdmap_destroy(osdc->osdmap);
	mempool_destroy(osdc->req_mempool);
	ceph_msgpool_destroy(&osdc->msgpool_op);
	ceph_msgpool_destroy(&osdc->msgpool_op_reply);
पूर्ण

अटल पूर्णांक osd_req_op_copy_from_init(काष्ठा ceph_osd_request *req,
				     u64 src_snapid, u64 src_version,
				     काष्ठा ceph_object_id *src_oid,
				     काष्ठा ceph_object_locator *src_oloc,
				     u32 src_fadvise_flags,
				     u32 dst_fadvise_flags,
				     u32 truncate_seq, u64 truncate_size,
				     u8 copy_from_flags)
अणु
	काष्ठा ceph_osd_req_op *op;
	काष्ठा page **pages;
	व्योम *p, *end;

	pages = ceph_alloc_page_vector(1, GFP_KERNEL);
	अगर (IS_ERR(pages))
		वापस PTR_ERR(pages);

	op = osd_req_op_init(req, 0, CEPH_OSD_OP_COPY_FROM2,
			     dst_fadvise_flags);
	op->copy_from.snapid = src_snapid;
	op->copy_from.src_version = src_version;
	op->copy_from.flags = copy_from_flags;
	op->copy_from.src_fadvise_flags = src_fadvise_flags;

	p = page_address(pages[0]);
	end = p + PAGE_SIZE;
	ceph_encode_string(&p, end, src_oid->name, src_oid->name_len);
	encode_oloc(&p, end, src_oloc);
	ceph_encode_32(&p, truncate_seq);
	ceph_encode_64(&p, truncate_size);
	op->indata_len = PAGE_SIZE - (end - p);

	ceph_osd_data_pages_init(&op->copy_from.osd_data, pages,
				 op->indata_len, 0, false, true);
	वापस 0;
पूर्ण

पूर्णांक ceph_osdc_copy_from(काष्ठा ceph_osd_client *osdc,
			u64 src_snapid, u64 src_version,
			काष्ठा ceph_object_id *src_oid,
			काष्ठा ceph_object_locator *src_oloc,
			u32 src_fadvise_flags,
			काष्ठा ceph_object_id *dst_oid,
			काष्ठा ceph_object_locator *dst_oloc,
			u32 dst_fadvise_flags,
			u32 truncate_seq, u64 truncate_size,
			u8 copy_from_flags)
अणु
	काष्ठा ceph_osd_request *req;
	पूर्णांक ret;

	req = ceph_osdc_alloc_request(osdc, शून्य, 1, false, GFP_KERNEL);
	अगर (!req)
		वापस -ENOMEM;

	req->r_flags = CEPH_OSD_FLAG_WRITE;

	ceph_oloc_copy(&req->r_t.base_oloc, dst_oloc);
	ceph_oid_copy(&req->r_t.base_oid, dst_oid);

	ret = osd_req_op_copy_from_init(req, src_snapid, src_version, src_oid,
					src_oloc, src_fadvise_flags,
					dst_fadvise_flags, truncate_seq,
					truncate_size, copy_from_flags);
	अगर (ret)
		जाओ out;

	ret = ceph_osdc_alloc_messages(req, GFP_KERNEL);
	अगर (ret)
		जाओ out;

	ceph_osdc_start_request(osdc, req, false);
	ret = ceph_osdc_रुको_request(osdc, req);

out:
	ceph_osdc_put_request(req);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(ceph_osdc_copy_from);

पूर्णांक __init ceph_osdc_setup(व्योम)
अणु
	माप_प्रकार size = माप(काष्ठा ceph_osd_request) +
	    CEPH_OSD_SLAB_OPS * माप(काष्ठा ceph_osd_req_op);

	BUG_ON(ceph_osd_request_cache);
	ceph_osd_request_cache = kmem_cache_create("ceph_osd_request", size,
						   0, 0, शून्य);

	वापस ceph_osd_request_cache ? 0 : -ENOMEM;
पूर्ण

व्योम ceph_osdc_cleanup(व्योम)
अणु
	BUG_ON(!ceph_osd_request_cache);
	kmem_cache_destroy(ceph_osd_request_cache);
	ceph_osd_request_cache = शून्य;
पूर्ण

/*
 * handle incoming message
 */
अटल व्योम osd_dispatch(काष्ठा ceph_connection *con, काष्ठा ceph_msg *msg)
अणु
	काष्ठा ceph_osd *osd = con->निजी;
	काष्ठा ceph_osd_client *osdc = osd->o_osdc;
	पूर्णांक type = le16_to_cpu(msg->hdr.type);

	चयन (type) अणु
	हाल CEPH_MSG_OSD_MAP:
		ceph_osdc_handle_map(osdc, msg);
		अवरोध;
	हाल CEPH_MSG_OSD_OPREPLY:
		handle_reply(osd, msg);
		अवरोध;
	हाल CEPH_MSG_OSD_BACKOFF:
		handle_backoff(osd, msg);
		अवरोध;
	हाल CEPH_MSG_WATCH_NOTIFY:
		handle_watch_notअगरy(osdc, msg);
		अवरोध;

	शेष:
		pr_err("received unknown message type %d %s\n", type,
		       ceph_msg_type_name(type));
	पूर्ण

	ceph_msg_put(msg);
पूर्ण

/*
 * Lookup and वापस message क्रम incoming reply.  Don't try to करो
 * anything about a larger than pपुनः_स्मृतिated data portion of the
 * message at the moment - क्रम now, just skip the message.
 */
अटल काष्ठा ceph_msg *get_reply(काष्ठा ceph_connection *con,
				  काष्ठा ceph_msg_header *hdr,
				  पूर्णांक *skip)
अणु
	काष्ठा ceph_osd *osd = con->निजी;
	काष्ठा ceph_osd_client *osdc = osd->o_osdc;
	काष्ठा ceph_msg *m = शून्य;
	काष्ठा ceph_osd_request *req;
	पूर्णांक front_len = le32_to_cpu(hdr->front_len);
	पूर्णांक data_len = le32_to_cpu(hdr->data_len);
	u64 tid = le64_to_cpu(hdr->tid);

	करोwn_पढ़ो(&osdc->lock);
	अगर (!osd_रेजिस्टरed(osd)) अणु
		करोut("%s osd%d unknown, skipping\n", __func__, osd->o_osd);
		*skip = 1;
		जाओ out_unlock_osdc;
	पूर्ण
	WARN_ON(osd->o_osd != le64_to_cpu(hdr->src.num));

	mutex_lock(&osd->lock);
	req = lookup_request(&osd->o_requests, tid);
	अगर (!req) अणु
		करोut("%s osd%d tid %llu unknown, skipping\n", __func__,
		     osd->o_osd, tid);
		*skip = 1;
		जाओ out_unlock_session;
	पूर्ण

	ceph_msg_revoke_incoming(req->r_reply);

	अगर (front_len > req->r_reply->front_alloc_len) अणु
		pr_warn("%s osd%d tid %llu front %d > preallocated %d\n",
			__func__, osd->o_osd, req->r_tid, front_len,
			req->r_reply->front_alloc_len);
		m = ceph_msg_new(CEPH_MSG_OSD_OPREPLY, front_len, GFP_NOFS,
				 false);
		अगर (!m)
			जाओ out_unlock_session;
		ceph_msg_put(req->r_reply);
		req->r_reply = m;
	पूर्ण

	अगर (data_len > req->r_reply->data_length) अणु
		pr_warn("%s osd%d tid %llu data %d > preallocated %zu, skipping\n",
			__func__, osd->o_osd, req->r_tid, data_len,
			req->r_reply->data_length);
		m = शून्य;
		*skip = 1;
		जाओ out_unlock_session;
	पूर्ण

	m = ceph_msg_get(req->r_reply);
	करोut("get_reply tid %lld %p\n", tid, m);

out_unlock_session:
	mutex_unlock(&osd->lock);
out_unlock_osdc:
	up_पढ़ो(&osdc->lock);
	वापस m;
पूर्ण

अटल काष्ठा ceph_msg *alloc_msg_with_page_vector(काष्ठा ceph_msg_header *hdr)
अणु
	काष्ठा ceph_msg *m;
	पूर्णांक type = le16_to_cpu(hdr->type);
	u32 front_len = le32_to_cpu(hdr->front_len);
	u32 data_len = le32_to_cpu(hdr->data_len);

	m = ceph_msg_new2(type, front_len, 1, GFP_NOIO, false);
	अगर (!m)
		वापस शून्य;

	अगर (data_len) अणु
		काष्ठा page **pages;

		pages = ceph_alloc_page_vector(calc_pages_क्रम(0, data_len),
					       GFP_NOIO);
		अगर (IS_ERR(pages)) अणु
			ceph_msg_put(m);
			वापस शून्य;
		पूर्ण

		ceph_msg_data_add_pages(m, pages, data_len, 0, true);
	पूर्ण

	वापस m;
पूर्ण

अटल काष्ठा ceph_msg *osd_alloc_msg(काष्ठा ceph_connection *con,
				      काष्ठा ceph_msg_header *hdr,
				      पूर्णांक *skip)
अणु
	काष्ठा ceph_osd *osd = con->निजी;
	पूर्णांक type = le16_to_cpu(hdr->type);

	*skip = 0;
	चयन (type) अणु
	हाल CEPH_MSG_OSD_MAP:
	हाल CEPH_MSG_OSD_BACKOFF:
	हाल CEPH_MSG_WATCH_NOTIFY:
		वापस alloc_msg_with_page_vector(hdr);
	हाल CEPH_MSG_OSD_OPREPLY:
		वापस get_reply(con, hdr, skip);
	शेष:
		pr_warn("%s osd%d unknown msg type %d, skipping\n", __func__,
			osd->o_osd, type);
		*skip = 1;
		वापस शून्य;
	पूर्ण
पूर्ण

/*
 * Wrappers to refcount containing ceph_osd काष्ठा
 */
अटल काष्ठा ceph_connection *osd_get_con(काष्ठा ceph_connection *con)
अणु
	काष्ठा ceph_osd *osd = con->निजी;
	अगर (get_osd(osd))
		वापस con;
	वापस शून्य;
पूर्ण

अटल व्योम osd_put_con(काष्ठा ceph_connection *con)
अणु
	काष्ठा ceph_osd *osd = con->निजी;
	put_osd(osd);
पूर्ण

/*
 * authentication
 */

/*
 * Note: वापसed poपूर्णांकer is the address of a काष्ठाure that's
 * managed separately.  Caller must *not* attempt to मुक्त it.
 */
अटल काष्ठा ceph_auth_handshake *
osd_get_authorizer(काष्ठा ceph_connection *con, पूर्णांक *proto, पूर्णांक क्रमce_new)
अणु
	काष्ठा ceph_osd *o = con->निजी;
	काष्ठा ceph_osd_client *osdc = o->o_osdc;
	काष्ठा ceph_auth_client *ac = osdc->client->monc.auth;
	काष्ठा ceph_auth_handshake *auth = &o->o_auth;
	पूर्णांक ret;

	ret = __ceph_auth_get_authorizer(ac, auth, CEPH_ENTITY_TYPE_OSD,
					 क्रमce_new, proto, शून्य, शून्य);
	अगर (ret)
		वापस ERR_PTR(ret);

	वापस auth;
पूर्ण

अटल पूर्णांक osd_add_authorizer_challenge(काष्ठा ceph_connection *con,
				    व्योम *challenge_buf, पूर्णांक challenge_buf_len)
अणु
	काष्ठा ceph_osd *o = con->निजी;
	काष्ठा ceph_osd_client *osdc = o->o_osdc;
	काष्ठा ceph_auth_client *ac = osdc->client->monc.auth;

	वापस ceph_auth_add_authorizer_challenge(ac, o->o_auth.authorizer,
					    challenge_buf, challenge_buf_len);
पूर्ण

अटल पूर्णांक osd_verअगरy_authorizer_reply(काष्ठा ceph_connection *con)
अणु
	काष्ठा ceph_osd *o = con->निजी;
	काष्ठा ceph_osd_client *osdc = o->o_osdc;
	काष्ठा ceph_auth_client *ac = osdc->client->monc.auth;
	काष्ठा ceph_auth_handshake *auth = &o->o_auth;

	वापस ceph_auth_verअगरy_authorizer_reply(ac, auth->authorizer,
		auth->authorizer_reply_buf, auth->authorizer_reply_buf_len,
		शून्य, शून्य, शून्य, शून्य);
पूर्ण

अटल पूर्णांक osd_invalidate_authorizer(काष्ठा ceph_connection *con)
अणु
	काष्ठा ceph_osd *o = con->निजी;
	काष्ठा ceph_osd_client *osdc = o->o_osdc;
	काष्ठा ceph_auth_client *ac = osdc->client->monc.auth;

	ceph_auth_invalidate_authorizer(ac, CEPH_ENTITY_TYPE_OSD);
	वापस ceph_monc_validate_auth(&osdc->client->monc);
पूर्ण

अटल पूर्णांक osd_get_auth_request(काष्ठा ceph_connection *con,
				व्योम *buf, पूर्णांक *buf_len,
				व्योम **authorizer, पूर्णांक *authorizer_len)
अणु
	काष्ठा ceph_osd *o = con->निजी;
	काष्ठा ceph_auth_client *ac = o->o_osdc->client->monc.auth;
	काष्ठा ceph_auth_handshake *auth = &o->o_auth;
	पूर्णांक ret;

	ret = ceph_auth_get_authorizer(ac, auth, CEPH_ENTITY_TYPE_OSD,
				       buf, buf_len);
	अगर (ret)
		वापस ret;

	*authorizer = auth->authorizer_buf;
	*authorizer_len = auth->authorizer_buf_len;
	वापस 0;
पूर्ण

अटल पूर्णांक osd_handle_auth_reply_more(काष्ठा ceph_connection *con,
				      व्योम *reply, पूर्णांक reply_len,
				      व्योम *buf, पूर्णांक *buf_len,
				      व्योम **authorizer, पूर्णांक *authorizer_len)
अणु
	काष्ठा ceph_osd *o = con->निजी;
	काष्ठा ceph_auth_client *ac = o->o_osdc->client->monc.auth;
	काष्ठा ceph_auth_handshake *auth = &o->o_auth;
	पूर्णांक ret;

	ret = ceph_auth_handle_svc_reply_more(ac, auth, reply, reply_len,
					      buf, buf_len);
	अगर (ret)
		वापस ret;

	*authorizer = auth->authorizer_buf;
	*authorizer_len = auth->authorizer_buf_len;
	वापस 0;
पूर्ण

अटल पूर्णांक osd_handle_auth_करोne(काष्ठा ceph_connection *con,
				u64 global_id, व्योम *reply, पूर्णांक reply_len,
				u8 *session_key, पूर्णांक *session_key_len,
				u8 *con_secret, पूर्णांक *con_secret_len)
अणु
	काष्ठा ceph_osd *o = con->निजी;
	काष्ठा ceph_auth_client *ac = o->o_osdc->client->monc.auth;
	काष्ठा ceph_auth_handshake *auth = &o->o_auth;

	वापस ceph_auth_handle_svc_reply_करोne(ac, auth, reply, reply_len,
					       session_key, session_key_len,
					       con_secret, con_secret_len);
पूर्ण

अटल पूर्णांक osd_handle_auth_bad_method(काष्ठा ceph_connection *con,
				      पूर्णांक used_proto, पूर्णांक result,
				      स्थिर पूर्णांक *allowed_protos, पूर्णांक proto_cnt,
				      स्थिर पूर्णांक *allowed_modes, पूर्णांक mode_cnt)
अणु
	काष्ठा ceph_osd *o = con->निजी;
	काष्ठा ceph_mon_client *monc = &o->o_osdc->client->monc;
	पूर्णांक ret;

	अगर (ceph_auth_handle_bad_authorizer(monc->auth, CEPH_ENTITY_TYPE_OSD,
					    used_proto, result,
					    allowed_protos, proto_cnt,
					    allowed_modes, mode_cnt)) अणु
		ret = ceph_monc_validate_auth(monc);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस -EACCES;
पूर्ण

अटल व्योम osd_reencode_message(काष्ठा ceph_msg *msg)
अणु
	पूर्णांक type = le16_to_cpu(msg->hdr.type);

	अगर (type == CEPH_MSG_OSD_OP)
		encode_request_finish(msg);
पूर्ण

अटल पूर्णांक osd_sign_message(काष्ठा ceph_msg *msg)
अणु
	काष्ठा ceph_osd *o = msg->con->निजी;
	काष्ठा ceph_auth_handshake *auth = &o->o_auth;

	वापस ceph_auth_sign_message(auth, msg);
पूर्ण

अटल पूर्णांक osd_check_message_signature(काष्ठा ceph_msg *msg)
अणु
	काष्ठा ceph_osd *o = msg->con->निजी;
	काष्ठा ceph_auth_handshake *auth = &o->o_auth;

	वापस ceph_auth_check_message_signature(auth, msg);
पूर्ण

अटल स्थिर काष्ठा ceph_connection_operations osd_con_ops = अणु
	.get = osd_get_con,
	.put = osd_put_con,
	.alloc_msg = osd_alloc_msg,
	.dispatch = osd_dispatch,
	.fault = osd_fault,
	.reencode_message = osd_reencode_message,
	.get_authorizer = osd_get_authorizer,
	.add_authorizer_challenge = osd_add_authorizer_challenge,
	.verअगरy_authorizer_reply = osd_verअगरy_authorizer_reply,
	.invalidate_authorizer = osd_invalidate_authorizer,
	.sign_message = osd_sign_message,
	.check_message_signature = osd_check_message_signature,
	.get_auth_request = osd_get_auth_request,
	.handle_auth_reply_more = osd_handle_auth_reply_more,
	.handle_auth_करोne = osd_handle_auth_करोne,
	.handle_auth_bad_method = osd_handle_auth_bad_method,
पूर्ण;
