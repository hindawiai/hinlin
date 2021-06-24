<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * linux/include/linux/nfs_page.h
 *
 * Copyright (C) 2000 Trond Myklebust
 *
 * NFS page cache wrapper.
 */

#अगर_अघोषित _LINUX_NFS_PAGE_H
#घोषणा _LINUX_NFS_PAGE_H


#समावेश <linux/list.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/रुको.h>
#समावेश <linux/sunrpc/auth.h>
#समावेश <linux/nfs_xdr.h>

#समावेश <linux/kref.h>

/*
 * Valid flags क्रम a dirty buffer
 */
क्रमागत अणु
	PG_BUSY = 0,		/* nfs_अणुunपूर्णlock_request */
	PG_MAPPED,		/* page निजी set क्रम buffered io */
	PG_CLEAN,		/* ग_लिखो succeeded */
	PG_COMMIT_TO_DS,	/* used by pnfs layouts */
	PG_INODE_REF,		/* extra ref held by inode when in ग_लिखोback */
	PG_HEADLOCK,		/* page group lock of wb_head */
	PG_TEARDOWN,		/* page group sync क्रम destroy */
	PG_UNLOCKPAGE,		/* page group sync bit in पढ़ो path */
	PG_UPTODATE,		/* page group sync bit in पढ़ो path */
	PG_WB_END,		/* page group sync bit in ग_लिखो path */
	PG_REMOVE,		/* page group sync bit in ग_लिखो path */
	PG_CONTENDED1,		/* Is someone रुकोing क्रम a lock? */
	PG_CONTENDED2,		/* Is someone रुकोing क्रम a lock? */
पूर्ण;

काष्ठा nfs_inode;
काष्ठा nfs_page अणु
	काष्ठा list_head	wb_list;	/* Defines state of page: */
	काष्ठा page		*wb_page;	/* page to पढ़ो in/ग_लिखो out */
	काष्ठा nfs_lock_context	*wb_lock_context;	/* lock context info */
	pgoff_t			wb_index;	/* Offset >> PAGE_SHIFT */
	अचिन्हित पूर्णांक		wb_offset,	/* Offset & ~PAGE_MASK */
				wb_pgbase,	/* Start of page data */
				wb_bytes;	/* Length of request */
	काष्ठा kref		wb_kref;	/* reference count */
	अचिन्हित दीर्घ		wb_flags;
	काष्ठा nfs_ग_लिखो_verअगरier	wb_verf;	/* Commit cookie */
	काष्ठा nfs_page		*wb_this_page;  /* list of reqs क्रम this page */
	काष्ठा nfs_page		*wb_head;       /* head poपूर्णांकer क्रम req list */
	अचिन्हित लघु		wb_nio;		/* Number of I/O attempts */
पूर्ण;

काष्ठा nfs_pgio_mirror;
काष्ठा nfs_pageio_descriptor;
काष्ठा nfs_pageio_ops अणु
	व्योम	(*pg_init)(काष्ठा nfs_pageio_descriptor *, काष्ठा nfs_page *);
	माप_प्रकार	(*pg_test)(काष्ठा nfs_pageio_descriptor *, काष्ठा nfs_page *,
			   काष्ठा nfs_page *);
	पूर्णांक	(*pg_करोio)(काष्ठा nfs_pageio_descriptor *);
	अचिन्हित पूर्णांक	(*pg_get_mirror_count)(काष्ठा nfs_pageio_descriptor *,
				       काष्ठा nfs_page *);
	व्योम	(*pg_cleanup)(काष्ठा nfs_pageio_descriptor *);
	काष्ठा nfs_pgio_mirror *
		(*pg_get_mirror)(काष्ठा nfs_pageio_descriptor *, u32);
	u32	(*pg_set_mirror)(काष्ठा nfs_pageio_descriptor *, u32);
पूर्ण;

काष्ठा nfs_rw_ops अणु
	काष्ठा nfs_pgio_header *(*rw_alloc_header)(व्योम);
	व्योम (*rw_मुक्त_header)(काष्ठा nfs_pgio_header *);
	पूर्णांक  (*rw_करोne)(काष्ठा rpc_task *, काष्ठा nfs_pgio_header *,
			काष्ठा inode *);
	व्योम (*rw_result)(काष्ठा rpc_task *, काष्ठा nfs_pgio_header *);
	व्योम (*rw_initiate)(काष्ठा nfs_pgio_header *, काष्ठा rpc_message *,
			    स्थिर काष्ठा nfs_rpc_ops *,
			    काष्ठा rpc_task_setup *, पूर्णांक);
पूर्ण;

काष्ठा nfs_pgio_mirror अणु
	काष्ठा list_head	pg_list;
	अचिन्हित दीर्घ		pg_bytes_written;
	माप_प्रकार			pg_count;
	माप_प्रकार			pg_bsize;
	अचिन्हित पूर्णांक		pg_base;
	अचिन्हित अक्षर		pg_recoalesce : 1;
पूर्ण;

काष्ठा nfs_pageio_descriptor अणु
	काष्ठा inode		*pg_inode;
	स्थिर काष्ठा nfs_pageio_ops *pg_ops;
	स्थिर काष्ठा nfs_rw_ops *pg_rw_ops;
	पूर्णांक 			pg_ioflags;
	पूर्णांक			pg_error;
	स्थिर काष्ठा rpc_call_ops *pg_rpc_callops;
	स्थिर काष्ठा nfs_pgio_completion_ops *pg_completion_ops;
	काष्ठा pnfs_layout_segment *pg_lseg;
	काष्ठा nfs_io_completion *pg_io_completion;
	काष्ठा nfs_direct_req	*pg_dreq;
	अचिन्हित पूर्णांक		pg_bsize;	/* शेष bsize क्रम mirrors */

	u32			pg_mirror_count;
	काष्ठा nfs_pgio_mirror	*pg_mirrors;
	काष्ठा nfs_pgio_mirror	pg_mirrors_अटल[1];
	काष्ठा nfs_pgio_mirror	*pg_mirrors_dynamic;
	u32			pg_mirror_idx;	/* current mirror */
	अचिन्हित लघु		pg_maxretrans;
	अचिन्हित अक्षर		pg_moreio : 1;
पूर्ण;

/* arbitrarily selected limit to number of mirrors */
#घोषणा NFS_PAGEIO_DESCRIPTOR_MIRROR_MAX 16

#घोषणा NFS_WBACK_BUSY(req)	(test_bit(PG_BUSY,&(req)->wb_flags))

बाह्य	काष्ठा nfs_page *nfs_create_request(काष्ठा nfs_खोलो_context *ctx,
					    काष्ठा page *page,
					    अचिन्हित पूर्णांक offset,
					    अचिन्हित पूर्णांक count);
बाह्य	व्योम nfs_release_request(काष्ठा nfs_page *);


बाह्य	व्योम nfs_pageio_init(काष्ठा nfs_pageio_descriptor *desc,
			     काष्ठा inode *inode,
			     स्थिर काष्ठा nfs_pageio_ops *pg_ops,
			     स्थिर काष्ठा nfs_pgio_completion_ops *compl_ops,
			     स्थिर काष्ठा nfs_rw_ops *rw_ops,
			     माप_प्रकार bsize,
			     पूर्णांक how);
बाह्य	पूर्णांक nfs_pageio_add_request(काष्ठा nfs_pageio_descriptor *,
				   काष्ठा nfs_page *);
बाह्य  पूर्णांक nfs_pageio_resend(काष्ठा nfs_pageio_descriptor *,
			      काष्ठा nfs_pgio_header *);
बाह्य	व्योम nfs_pageio_complete(काष्ठा nfs_pageio_descriptor *desc);
बाह्य	व्योम nfs_pageio_cond_complete(काष्ठा nfs_pageio_descriptor *, pgoff_t);
बाह्य माप_प्रकार nfs_generic_pg_test(काष्ठा nfs_pageio_descriptor *desc,
				काष्ठा nfs_page *prev,
				काष्ठा nfs_page *req);
बाह्य  पूर्णांक nfs_रुको_on_request(काष्ठा nfs_page *);
बाह्य	व्योम nfs_unlock_request(काष्ठा nfs_page *req);
बाह्य	व्योम nfs_unlock_and_release_request(काष्ठा nfs_page *);
बाह्य	काष्ठा nfs_page *nfs_page_group_lock_head(काष्ठा nfs_page *req);
बाह्य	पूर्णांक nfs_page_group_lock_subrequests(काष्ठा nfs_page *head);
बाह्य	व्योम nfs_join_page_group(काष्ठा nfs_page *head, काष्ठा inode *inode);
बाह्य पूर्णांक nfs_page_group_lock(काष्ठा nfs_page *);
बाह्य व्योम nfs_page_group_unlock(काष्ठा nfs_page *);
बाह्य bool nfs_page_group_sync_on_bit(काष्ठा nfs_page *, अचिन्हित पूर्णांक);
बाह्य	पूर्णांक nfs_page_set_headlock(काष्ठा nfs_page *req);
बाह्य व्योम nfs_page_clear_headlock(काष्ठा nfs_page *req);
बाह्य bool nfs_async_iocounter_रुको(काष्ठा rpc_task *, काष्ठा nfs_lock_context *);

/*
 * Lock the page of an asynchronous request
 */
अटल अंतरभूत पूर्णांक
nfs_lock_request(काष्ठा nfs_page *req)
अणु
	वापस !test_and_set_bit(PG_BUSY, &req->wb_flags);
पूर्ण

/**
 * nfs_list_add_request - Insert a request पूर्णांकo a list
 * @req: request
 * @head: head of list पूर्णांकo which to insert the request.
 */
अटल अंतरभूत व्योम
nfs_list_add_request(काष्ठा nfs_page *req, काष्ठा list_head *head)
अणु
	list_add_tail(&req->wb_list, head);
पूर्ण

/**
 * nfs_list_move_request - Move a request to a new list
 * @req: request
 * @head: head of list पूर्णांकo which to insert the request.
 */
अटल अंतरभूत व्योम
nfs_list_move_request(काष्ठा nfs_page *req, काष्ठा list_head *head)
अणु
	list_move_tail(&req->wb_list, head);
पूर्ण

/**
 * nfs_list_हटाओ_request - Remove a request from its wb_list
 * @req: request
 */
अटल अंतरभूत व्योम
nfs_list_हटाओ_request(काष्ठा nfs_page *req)
अणु
	अगर (list_empty(&req->wb_list))
		वापस;
	list_del_init(&req->wb_list);
पूर्ण

अटल अंतरभूत काष्ठा nfs_page *
nfs_list_entry(काष्ठा list_head *head)
अणु
	वापस list_entry(head, काष्ठा nfs_page, wb_list);
पूर्ण

अटल अंतरभूत
loff_t req_offset(काष्ठा nfs_page *req)
अणु
	वापस (((loff_t)req->wb_index) << PAGE_SHIFT) + req->wb_offset;
पूर्ण

अटल अंतरभूत काष्ठा nfs_खोलो_context *
nfs_req_खोलोctx(काष्ठा nfs_page *req)
अणु
	वापस req->wb_lock_context->खोलो_context;
पूर्ण

#पूर्ण_अगर /* _LINUX_NFS_PAGE_H */
