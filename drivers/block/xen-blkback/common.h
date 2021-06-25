<शैली गुरु>
/*
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License version 2
 * as published by the Free Software Foundation; or, when distributed
 * separately from the Linux kernel or incorporated पूर्णांकo other
 * software packages, subject to the following license:
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a copy
 * of this source file (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy, modअगरy,
 * merge, publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to करो so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#अगर_अघोषित __XEN_BLKIF__BACKEND__COMMON_H__
#घोषणा __XEN_BLKIF__BACKEND__COMMON_H__

#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/slab.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/रुको.h>
#समावेश <linux/पन.स>
#समावेश <linux/rbtree.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/hypervisor.h>
#समावेश <xen/grant_table.h>
#समावेश <xen/page.h>
#समावेश <xen/xenbus.h>
#समावेश <xen/पूर्णांकerface/io/ring.h>
#समावेश <xen/पूर्णांकerface/io/blkअगर.h>
#समावेश <xen/पूर्णांकerface/io/protocols.h>

बाह्य अचिन्हित पूर्णांक xen_blkअगर_max_ring_order;
बाह्य अचिन्हित पूर्णांक xenblk_max_queues;
/*
 * This is the maximum number of segments that would be allowed in indirect
 * requests. This value will also be passed to the frontend.
 */
#घोषणा MAX_INसूचीECT_SEGMENTS 256

/*
 * Xen use 4K pages. The guest may use dअगरferent page size (4K or 64K)
 * Number of Xen pages per segment
 */
#घोषणा XEN_PAGES_PER_SEGMENT   (PAGE_SIZE / XEN_PAGE_SIZE)

#घोषणा XEN_PAGES_PER_INसूचीECT_FRAME \
	(XEN_PAGE_SIZE/माप(काष्ठा blkअगर_request_segment))
#घोषणा SEGS_PER_INसूचीECT_FRAME	\
	(XEN_PAGES_PER_INसूचीECT_FRAME / XEN_PAGES_PER_SEGMENT)

#घोषणा MAX_INसूचीECT_PAGES \
	((MAX_INसूचीECT_SEGMENTS + SEGS_PER_INसूचीECT_FRAME - 1)/SEGS_PER_INसूचीECT_FRAME)
#घोषणा INसूचीECT_PAGES(_segs) DIV_ROUND_UP(_segs, XEN_PAGES_PER_INसूचीECT_FRAME)

/* Not a real protocol.  Used to generate ring काष्ठाs which contain
 * the elements common to all protocols only.  This way we get a
 * compiler-checkable way to use common काष्ठा elements, so we can
 * aव्योम using चयन(protocol) in a number of places.  */
काष्ठा blkअगर_common_request अणु
	अक्षर dummy;
पूर्ण;

/* i386 protocol version */

काष्ठा blkअगर_x86_32_request_rw अणु
	uपूर्णांक8_t        nr_segments;  /* number of segments                   */
	blkअगर_vdev_t   handle;       /* only क्रम पढ़ो/ग_लिखो requests         */
	uपूर्णांक64_t       id;           /* निजी guest value, echoed in resp  */
	blkअगर_sector_t sector_number;/* start sector idx on disk (r/w only)  */
	काष्ठा blkअगर_request_segment seg[BLKIF_MAX_SEGMENTS_PER_REQUEST];
पूर्ण __attribute__((__packed__));

काष्ठा blkअगर_x86_32_request_discard अणु
	uपूर्णांक8_t        flag;         /* BLKIF_DISCARD_SECURE or zero         */
	blkअगर_vdev_t   _pad1;        /* was "handle" क्रम पढ़ो/ग_लिखो requests */
	uपूर्णांक64_t       id;           /* निजी guest value, echoed in resp  */
	blkअगर_sector_t sector_number;/* start sector idx on disk (r/w only)  */
	uपूर्णांक64_t       nr_sectors;
पूर्ण __attribute__((__packed__));

काष्ठा blkअगर_x86_32_request_other अणु
	uपूर्णांक8_t        _pad1;
	blkअगर_vdev_t   _pad2;
	uपूर्णांक64_t       id;           /* निजी guest value, echoed in resp  */
पूर्ण __attribute__((__packed__));

काष्ठा blkअगर_x86_32_request_indirect अणु
	uपूर्णांक8_t        indirect_op;
	uपूर्णांक16_t       nr_segments;
	uपूर्णांक64_t       id;
	blkअगर_sector_t sector_number;
	blkअगर_vdev_t   handle;
	uपूर्णांक16_t       _pad1;
	grant_ref_t    indirect_grefs[BLKIF_MAX_INसूचीECT_PAGES_PER_REQUEST];
	/*
	 * The maximum number of indirect segments (and pages) that will
	 * be used is determined by MAX_INसूचीECT_SEGMENTS, this value
	 * is also exported to the guest (via xenstore
	 * feature-max-indirect-segments entry), so the frontend knows how
	 * many indirect segments the backend supports.
	 */
	uपूर्णांक64_t       _pad2;        /* make it 64 byte aligned */
पूर्ण __attribute__((__packed__));

काष्ठा blkअगर_x86_32_request अणु
	uपूर्णांक8_t        operation;    /* BLKIF_OP_???                         */
	जोड़ अणु
		काष्ठा blkअगर_x86_32_request_rw rw;
		काष्ठा blkअगर_x86_32_request_discard discard;
		काष्ठा blkअगर_x86_32_request_other other;
		काष्ठा blkअगर_x86_32_request_indirect indirect;
	पूर्ण u;
पूर्ण __attribute__((__packed__));

/* x86_64 protocol version */

काष्ठा blkअगर_x86_64_request_rw अणु
	uपूर्णांक8_t        nr_segments;  /* number of segments                   */
	blkअगर_vdev_t   handle;       /* only क्रम पढ़ो/ग_लिखो requests         */
	uपूर्णांक32_t       _pad1;        /* दुरत्व(blkअगर_reqest..,u.rw.id)==8  */
	uपूर्णांक64_t       id;
	blkअगर_sector_t sector_number;/* start sector idx on disk (r/w only)  */
	काष्ठा blkअगर_request_segment seg[BLKIF_MAX_SEGMENTS_PER_REQUEST];
पूर्ण __attribute__((__packed__));

काष्ठा blkअगर_x86_64_request_discard अणु
	uपूर्णांक8_t        flag;         /* BLKIF_DISCARD_SECURE or zero         */
	blkअगर_vdev_t   _pad1;        /* was "handle" क्रम पढ़ो/ग_लिखो requests */
        uपूर्णांक32_t       _pad2;        /* दुरत्व(blkअगर_..,u.discard.id)==8   */
	uपूर्णांक64_t       id;
	blkअगर_sector_t sector_number;/* start sector idx on disk (r/w only)  */
	uपूर्णांक64_t       nr_sectors;
पूर्ण __attribute__((__packed__));

काष्ठा blkअगर_x86_64_request_other अणु
	uपूर्णांक8_t        _pad1;
	blkअगर_vdev_t   _pad2;
	uपूर्णांक32_t       _pad3;        /* दुरत्व(blkअगर_..,u.discard.id)==8   */
	uपूर्णांक64_t       id;           /* निजी guest value, echoed in resp  */
पूर्ण __attribute__((__packed__));

काष्ठा blkअगर_x86_64_request_indirect अणु
	uपूर्णांक8_t        indirect_op;
	uपूर्णांक16_t       nr_segments;
	uपूर्णांक32_t       _pad1;        /* दुरत्व(blkअगर_..,u.indirect.id)==8   */
	uपूर्णांक64_t       id;
	blkअगर_sector_t sector_number;
	blkअगर_vdev_t   handle;
	uपूर्णांक16_t       _pad2;
	grant_ref_t    indirect_grefs[BLKIF_MAX_INसूचीECT_PAGES_PER_REQUEST];
	/*
	 * The maximum number of indirect segments (and pages) that will
	 * be used is determined by MAX_INसूचीECT_SEGMENTS, this value
	 * is also exported to the guest (via xenstore
	 * feature-max-indirect-segments entry), so the frontend knows how
	 * many indirect segments the backend supports.
	 */
	uपूर्णांक32_t       _pad3;        /* make it 64 byte aligned */
पूर्ण __attribute__((__packed__));

काष्ठा blkअगर_x86_64_request अणु
	uपूर्णांक8_t        operation;    /* BLKIF_OP_???                         */
	जोड़ अणु
		काष्ठा blkअगर_x86_64_request_rw rw;
		काष्ठा blkअगर_x86_64_request_discard discard;
		काष्ठा blkअगर_x86_64_request_other other;
		काष्ठा blkअगर_x86_64_request_indirect indirect;
	पूर्ण u;
पूर्ण __attribute__((__packed__));

DEFINE_RING_TYPES(blkअगर_common, काष्ठा blkअगर_common_request,
		  काष्ठा blkअगर_response);
DEFINE_RING_TYPES(blkअगर_x86_32, काष्ठा blkअगर_x86_32_request,
		  काष्ठा blkअगर_response __packed);
DEFINE_RING_TYPES(blkअगर_x86_64, काष्ठा blkअगर_x86_64_request,
		  काष्ठा blkअगर_response);

जोड़ blkअगर_back_rings अणु
	काष्ठा blkअगर_back_ring        native;
	काष्ठा blkअगर_common_back_ring common;
	काष्ठा blkअगर_x86_32_back_ring x86_32;
	काष्ठा blkअगर_x86_64_back_ring x86_64;
पूर्ण;

क्रमागत blkअगर_protocol अणु
	BLKIF_PROTOCOL_NATIVE = 1,
	BLKIF_PROTOCOL_X86_32 = 2,
	BLKIF_PROTOCOL_X86_64 = 3,
पूर्ण;

/*
 * Default protocol अगर the frontend करोesn't specअगरy one.
 */
#अगर_घोषित CONFIG_X86
#  define BLKIF_PROTOCOL_DEFAULT BLKIF_PROTOCOL_X86_32
#अन्यथा
#  define BLKIF_PROTOCOL_DEFAULT BLKIF_PROTOCOL_NATIVE
#पूर्ण_अगर

काष्ठा xen_vbd अणु
	/* What the करोमुख्य refers to this vbd as. */
	blkअगर_vdev_t		handle;
	/* Non-zero -> पढ़ो-only */
	अचिन्हित अक्षर		पढ़ोonly;
	/* VDISK_xxx */
	अचिन्हित अक्षर		type;
	/* phys device that this vbd maps to. */
	u32			pdevice;
	काष्ठा block_device	*bdev;
	/* Cached size parameter. */
	sector_t		size;
	अचिन्हित पूर्णांक		flush_support:1;
	अचिन्हित पूर्णांक		discard_secure:1;
	अचिन्हित पूर्णांक		feature_gnt_persistent:1;
	अचिन्हित पूर्णांक		overflow_max_grants:1;
पूर्ण;

काष्ठा backend_info;

/* Number of requests that we can fit in a ring */
#घोषणा XEN_BLKIF_REQS_PER_PAGE		32

काष्ठा persistent_gnt अणु
	काष्ठा page *page;
	grant_ref_t gnt;
	grant_handle_t handle;
	अचिन्हित दीर्घ last_used;
	bool active;
	काष्ठा rb_node node;
	काष्ठा list_head हटाओ_node;
पूर्ण;

/* Per-ring inक्रमmation. */
काष्ठा xen_blkअगर_ring अणु
	/* Physical parameters of the comms winकरोw. */
	अचिन्हित पूर्णांक		irq;
	जोड़ blkअगर_back_rings	blk_rings;
	व्योम			*blk_ring;
	/* Private fields. */
	spinlock_t		blk_ring_lock;

	रुको_queue_head_t	wq;
	atomic_t		inflight;
	bool			active;
	/* One thपढ़ो per blkअगर ring. */
	काष्ठा task_काष्ठा	*xenblkd;
	अचिन्हित पूर्णांक		रुकोing_reqs;

	/* List of all 'pending_req' available */
	काष्ठा list_head	pending_मुक्त;
	/* And its spinlock. */
	spinlock_t		pending_मुक्त_lock;
	रुको_queue_head_t	pending_मुक्त_wq;

	/* Tree to store persistent grants. */
	काष्ठा rb_root		persistent_gnts;
	अचिन्हित पूर्णांक		persistent_gnt_c;
	atomic_t		persistent_gnt_in_use;
	अचिन्हित दीर्घ           next_lru;

	/* Statistics. */
	अचिन्हित दीर्घ		st_prपूर्णांक;
	अचिन्हित दीर्घ दीर्घ	st_rd_req;
	अचिन्हित दीर्घ दीर्घ	st_wr_req;
	अचिन्हित दीर्घ दीर्घ	st_oo_req;
	अचिन्हित दीर्घ दीर्घ	st_f_req;
	अचिन्हित दीर्घ दीर्घ	st_ds_req;
	अचिन्हित दीर्घ दीर्घ	st_rd_sect;
	अचिन्हित दीर्घ दीर्घ	st_wr_sect;

	/* Used by the kworker that offload work from the persistent purge. */
	काष्ठा list_head	persistent_purge_list;
	काष्ठा work_काष्ठा	persistent_purge_work;

	/* Buffer of मुक्त pages to map grant refs. */
	काष्ठा gnttab_page_cache मुक्त_pages;

	काष्ठा work_काष्ठा	मुक्त_work;
	/* Thपढ़ो shutकरोwn रुको queue. */
	रुको_queue_head_t	shutकरोwn_wq;
	काष्ठा xen_blkअगर 	*blkअगर;
पूर्ण;

काष्ठा xen_blkअगर अणु
	/* Unique identअगरier क्रम this पूर्णांकerface. */
	करोmid_t			करोmid;
	अचिन्हित पूर्णांक		handle;
	/* Comms inक्रमmation. */
	क्रमागत blkअगर_protocol	blk_protocol;
	/* The VBD attached to this पूर्णांकerface. */
	काष्ठा xen_vbd		vbd;
	/* Back poपूर्णांकer to the backend_info. */
	काष्ठा backend_info	*be;
	atomic_t		refcnt;
	/* क्रम barrier (drain) requests */
	काष्ठा completion	drain_complete;
	atomic_t		drain;

	काष्ठा work_काष्ठा	मुक्त_work;
	अचिन्हित पूर्णांक 		nr_ring_pages;
	bool			multi_ref;
	/* All rings क्रम this device. */
	काष्ठा xen_blkअगर_ring	*rings;
	अचिन्हित पूर्णांक		nr_rings;
	अचिन्हित दीर्घ		buffer_squeeze_end;
पूर्ण;

काष्ठा seg_buf अणु
	अचिन्हित दीर्घ offset;
	अचिन्हित पूर्णांक nsec;
पूर्ण;

काष्ठा grant_page अणु
	काष्ठा page 		*page;
	काष्ठा persistent_gnt	*persistent_gnt;
	grant_handle_t		handle;
	grant_ref_t		gref;
पूर्ण;

/*
 * Each outstanding request that we've passed to the lower device layers has a
 * 'pending_req' allocated to it. Each buffer_head that completes decrements
 * the pendcnt towards zero. When it hits zero, the specअगरied करोमुख्य has a
 * response queued क्रम it, with the saved 'id' passed back.
 */
काष्ठा pending_req अणु
	काष्ठा xen_blkअगर_ring   *ring;
	u64			id;
	पूर्णांक			nr_segs;
	atomic_t		pendcnt;
	अचिन्हित लघु		operation;
	पूर्णांक			status;
	काष्ठा list_head	मुक्त_list;
	काष्ठा grant_page	*segments[MAX_INसूचीECT_SEGMENTS];
	/* Indirect descriptors */
	काष्ठा grant_page	*indirect_pages[MAX_INसूचीECT_PAGES];
	काष्ठा seg_buf		seg[MAX_INसूचीECT_SEGMENTS];
	काष्ठा bio		*biolist[MAX_INसूचीECT_SEGMENTS];
	काष्ठा gnttab_unmap_grant_ref unmap[MAX_INसूचीECT_SEGMENTS];
	काष्ठा page                   *unmap_pages[MAX_INसूचीECT_SEGMENTS];
	काष्ठा gntab_unmap_queue_data gnttab_unmap_data;
पूर्ण;


#घोषणा vbd_sz(_v)	bdev_nr_sectors((_v)->bdev)

#घोषणा xen_blkअगर_get(_b) (atomic_inc(&(_b)->refcnt))
#घोषणा xen_blkअगर_put(_b)				\
	करो अणु						\
		अगर (atomic_dec_and_test(&(_b)->refcnt))	\
			schedule_work(&(_b)->मुक्त_work);\
	पूर्ण जबतक (0)

काष्ठा phys_req अणु
	अचिन्हित लघु		dev;
	blkअगर_sector_t		nr_sects;
	काष्ठा block_device	*bdev;
	blkअगर_sector_t		sector_number;
पूर्ण;

पूर्णांक xen_blkअगर_पूर्णांकerface_init(व्योम);
व्योम xen_blkअगर_पूर्णांकerface_fini(व्योम);

पूर्णांक xen_blkअगर_xenbus_init(व्योम);
व्योम xen_blkअगर_xenbus_fini(व्योम);

irqवापस_t xen_blkअगर_be_पूर्णांक(पूर्णांक irq, व्योम *dev_id);
पूर्णांक xen_blkअगर_schedule(व्योम *arg);
पूर्णांक xen_blkअगर_purge_persistent(व्योम *arg);
व्योम xen_blkbk_मुक्त_caches(काष्ठा xen_blkअगर_ring *ring);

पूर्णांक xen_blkbk_flush_diskcache(काष्ठा xenbus_transaction xbt,
			      काष्ठा backend_info *be, पूर्णांक state);

पूर्णांक xen_blkbk_barrier(काष्ठा xenbus_transaction xbt,
		      काष्ठा backend_info *be, पूर्णांक state);
काष्ठा xenbus_device *xen_blkbk_xenbus(काष्ठा backend_info *be);
व्योम xen_blkbk_unmap_purged_grants(काष्ठा work_काष्ठा *work);

अटल अंतरभूत व्योम blkअगर_get_x86_32_req(काष्ठा blkअगर_request *dst,
					काष्ठा blkअगर_x86_32_request *src)
अणु
	पूर्णांक i, n = BLKIF_MAX_SEGMENTS_PER_REQUEST, j;
	dst->operation = READ_ONCE(src->operation);
	चयन (dst->operation) अणु
	हाल BLKIF_OP_READ:
	हाल BLKIF_OP_WRITE:
	हाल BLKIF_OP_WRITE_BARRIER:
	हाल BLKIF_OP_FLUSH_DISKCACHE:
		dst->u.rw.nr_segments = src->u.rw.nr_segments;
		dst->u.rw.handle = src->u.rw.handle;
		dst->u.rw.id = src->u.rw.id;
		dst->u.rw.sector_number = src->u.rw.sector_number;
		barrier();
		अगर (n > dst->u.rw.nr_segments)
			n = dst->u.rw.nr_segments;
		क्रम (i = 0; i < n; i++)
			dst->u.rw.seg[i] = src->u.rw.seg[i];
		अवरोध;
	हाल BLKIF_OP_DISCARD:
		dst->u.discard.flag = src->u.discard.flag;
		dst->u.discard.id = src->u.discard.id;
		dst->u.discard.sector_number = src->u.discard.sector_number;
		dst->u.discard.nr_sectors = src->u.discard.nr_sectors;
		अवरोध;
	हाल BLKIF_OP_INसूचीECT:
		dst->u.indirect.indirect_op = src->u.indirect.indirect_op;
		dst->u.indirect.nr_segments = src->u.indirect.nr_segments;
		dst->u.indirect.handle = src->u.indirect.handle;
		dst->u.indirect.id = src->u.indirect.id;
		dst->u.indirect.sector_number = src->u.indirect.sector_number;
		barrier();
		j = min(MAX_INसूचीECT_PAGES, INसूचीECT_PAGES(dst->u.indirect.nr_segments));
		क्रम (i = 0; i < j; i++)
			dst->u.indirect.indirect_grefs[i] =
				src->u.indirect.indirect_grefs[i];
		अवरोध;
	शेष:
		/*
		 * Don't know how to translate this op. Only get the
		 * ID so failure can be reported to the frontend.
		 */
		dst->u.other.id = src->u.other.id;
		अवरोध;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम blkअगर_get_x86_64_req(काष्ठा blkअगर_request *dst,
					काष्ठा blkअगर_x86_64_request *src)
अणु
	पूर्णांक i, n = BLKIF_MAX_SEGMENTS_PER_REQUEST, j;
	dst->operation = READ_ONCE(src->operation);
	चयन (dst->operation) अणु
	हाल BLKIF_OP_READ:
	हाल BLKIF_OP_WRITE:
	हाल BLKIF_OP_WRITE_BARRIER:
	हाल BLKIF_OP_FLUSH_DISKCACHE:
		dst->u.rw.nr_segments = src->u.rw.nr_segments;
		dst->u.rw.handle = src->u.rw.handle;
		dst->u.rw.id = src->u.rw.id;
		dst->u.rw.sector_number = src->u.rw.sector_number;
		barrier();
		अगर (n > dst->u.rw.nr_segments)
			n = dst->u.rw.nr_segments;
		क्रम (i = 0; i < n; i++)
			dst->u.rw.seg[i] = src->u.rw.seg[i];
		अवरोध;
	हाल BLKIF_OP_DISCARD:
		dst->u.discard.flag = src->u.discard.flag;
		dst->u.discard.id = src->u.discard.id;
		dst->u.discard.sector_number = src->u.discard.sector_number;
		dst->u.discard.nr_sectors = src->u.discard.nr_sectors;
		अवरोध;
	हाल BLKIF_OP_INसूचीECT:
		dst->u.indirect.indirect_op = src->u.indirect.indirect_op;
		dst->u.indirect.nr_segments = src->u.indirect.nr_segments;
		dst->u.indirect.handle = src->u.indirect.handle;
		dst->u.indirect.id = src->u.indirect.id;
		dst->u.indirect.sector_number = src->u.indirect.sector_number;
		barrier();
		j = min(MAX_INसूचीECT_PAGES, INसूचीECT_PAGES(dst->u.indirect.nr_segments));
		क्रम (i = 0; i < j; i++)
			dst->u.indirect.indirect_grefs[i] =
				src->u.indirect.indirect_grefs[i];
		अवरोध;
	शेष:
		/*
		 * Don't know how to translate this op. Only get the
		 * ID so failure can be reported to the frontend.
		 */
		dst->u.other.id = src->u.other.id;
		अवरोध;
	पूर्ण
पूर्ण

#पूर्ण_अगर /* __XEN_BLKIF__BACKEND__COMMON_H__ */
