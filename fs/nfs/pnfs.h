<शैली गुरु>
/*
 *  pNFS client data काष्ठाures.
 *
 *  Copyright (c) 2002
 *  The Regents of the University of Michigan
 *  All Rights Reserved
 *
 *  Dean Hildebअक्रम <dhildebz@umich.edu>
 *
 *  Permission is granted to use, copy, create derivative works, and
 *  redistribute this software and such derivative works क्रम any purpose,
 *  so दीर्घ as the name of the University of Michigan is not used in
 *  any advertising or खुलाity pertaining to the use or distribution
 *  of this software without specअगरic, written prior authorization. If
 *  the above copyright notice or any other identअगरication of the
 *  University of Michigan is included in any copy of any portion of
 *  this software, then the disclaimer below must also be included.
 *
 *  This software is provided as is, without representation or warranty
 *  of any kind either express or implied, including without limitation
 *  the implied warranties of merchantability, fitness क्रम a particular
 *  purpose, or noninfringement.  The Regents of the University of
 *  Michigan shall not be liable क्रम any damages, including special,
 *  indirect, incidental, or consequential damages, with respect to any
 *  claim arising out of or in connection with the use of the software,
 *  even अगर it has been or is hereafter advised of the possibility of
 *  such damages.
 */

#अगर_अघोषित FS_NFS_PNFS_H
#घोषणा FS_NFS_PNFS_H

#समावेश <linux/refcount.h>
#समावेश <linux/nfs_fs.h>
#समावेश <linux/nfs_page.h>
#समावेश <linux/workqueue.h>

काष्ठा nfs4_खोलोdata;

क्रमागत अणु
	NFS_LSEG_VALID = 0,	/* cleared when lseg is recalled/वापसed */
	NFS_LSEG_ROC,		/* roc bit received from server */
	NFS_LSEG_LAYOUTCOMMIT,	/* layoutcommit bit set क्रम layoutcommit */
	NFS_LSEG_LAYOUTRETURN,	/* layoutवापस bit set क्रम layoutवापस */
	NFS_LSEG_UNAVAILABLE,	/* unavailable bit set क्रम temporary problem */
पूर्ण;

/* Inभागidual ip address */
काष्ठा nfs4_pnfs_ds_addr अणु
	काष्ठा sockaddr_storage	da_addr;
	माप_प्रकार			da_addrlen;
	काष्ठा list_head	da_node;  /* nfs4_pnfs_dev_hlist dev_dslist */
	अक्षर			*da_remotestr;	/* human पढ़ोable addr+port */
	स्थिर अक्षर		*da_netid;
	पूर्णांक			da_transport;
पूर्ण;

काष्ठा nfs4_pnfs_ds अणु
	काष्ठा list_head	ds_node;  /* nfs4_pnfs_dev_hlist dev_dslist */
	अक्षर			*ds_remotestr;	/* comma sep list of addrs */
	काष्ठा list_head	ds_addrs;
	काष्ठा nfs_client	*ds_clp;
	refcount_t		ds_count;
	अचिन्हित दीर्घ		ds_state;
#घोषणा NFS4DS_CONNECTING	0	/* ds is establishing connection */
पूर्ण;

काष्ठा pnfs_layout_segment अणु
	काष्ठा list_head pls_list;
	काष्ठा list_head pls_lc_list;
	काष्ठा list_head pls_commits;
	काष्ठा pnfs_layout_range pls_range;
	refcount_t pls_refcount;
	u32 pls_seq;
	अचिन्हित दीर्घ pls_flags;
	काष्ठा pnfs_layout_hdr *pls_layout;
पूर्ण;

क्रमागत pnfs_try_status अणु
	PNFS_ATTEMPTED     = 0,
	PNFS_NOT_ATTEMPTED = 1,
	PNFS_TRY_AGAIN     = 2,
पूर्ण;

/* error codes क्रम पूर्णांकernal use */
#घोषणा NFS4ERR_RESET_TO_MDS   12001
#घोषणा NFS4ERR_RESET_TO_PNFS  12002

#अगर_घोषित CONFIG_NFS_V4_1

#घोषणा LAYOUT_NFSV4_1_MODULE_PREFIX "nfs-layouttype4"

/*
 * Default data server connection समयout and retrans vaules.
 * Set by module parameters dataserver_समयo and dataserver_retrans.
 */
#घोषणा NFS4_DEF_DS_TIMEO   600 /* in tenths of a second */
#घोषणा NFS4_DEF_DS_RETRANS 5
#घोषणा PNFS_DEVICE_RETRY_TIMEOUT (120*HZ)

क्रमागत अणु
	NFS_LAYOUT_RO_FAILED = 0,	/* get ro layout failed stop trying */
	NFS_LAYOUT_RW_FAILED,		/* get rw layout failed stop trying */
	NFS_LAYOUT_BULK_RECALL,		/* bulk recall affecting layout */
	NFS_LAYOUT_RETURN,		/* layoutवापस in progress */
	NFS_LAYOUT_RETURN_LOCK,		/* Serialise layoutवापस */
	NFS_LAYOUT_RETURN_REQUESTED,	/* Return this layout ASAP */
	NFS_LAYOUT_INVALID_STID,	/* layout stateid id is invalid */
	NFS_LAYOUT_FIRST_LAYOUTGET,	/* Serialize first layoutget */
	NFS_LAYOUT_INODE_FREEING,	/* The inode is being मुक्तd */
	NFS_LAYOUT_HASHED,		/* The layout visible */
पूर्ण;

क्रमागत layoutdriver_policy_flags अणु
	/* Should the pNFS client commit and वापस the layout upon truncate to
	 * a smaller size */
	PNFS_LAYOUTRET_ON_SETATTR	= 1 << 0,
	PNFS_LAYOUTRET_ON_ERROR		= 1 << 1,
	PNFS_READ_WHOLE_PAGE		= 1 << 2,
	PNFS_LAYOUTGET_ON_OPEN		= 1 << 3,
पूर्ण;

काष्ठा nfs4_deviceid_node;

/* Per-layout driver specअगरic registration काष्ठाure */
काष्ठा pnfs_layoutdriver_type अणु
	काष्ठा list_head pnfs_tblid;
	स्थिर u32 id;
	स्थिर अक्षर *name;
	काष्ठा module *owner;
	अचिन्हित flags;
	अचिन्हित max_deviceinfo_size;
	अचिन्हित max_layoutget_response;

	पूर्णांक (*set_layoutdriver) (काष्ठा nfs_server *, स्थिर काष्ठा nfs_fh *);
	पूर्णांक (*clear_layoutdriver) (काष्ठा nfs_server *);

	काष्ठा pnfs_layout_hdr * (*alloc_layout_hdr) (काष्ठा inode *inode, gfp_t gfp_flags);
	व्योम (*मुक्त_layout_hdr) (काष्ठा pnfs_layout_hdr *);

	काष्ठा pnfs_layout_segment * (*alloc_lseg) (काष्ठा pnfs_layout_hdr *layoutid, काष्ठा nfs4_layoutget_res *lgr, gfp_t gfp_flags);
	व्योम (*मुक्त_lseg) (काष्ठा pnfs_layout_segment *lseg);
	व्योम (*add_lseg) (काष्ठा pnfs_layout_hdr *layoutid,
			काष्ठा pnfs_layout_segment *lseg,
			काष्ठा list_head *मुक्त_me);

	व्योम (*वापस_range) (काष्ठा pnfs_layout_hdr *lo,
			      काष्ठा pnfs_layout_range *range);

	/* test क्रम nfs page cache coalescing */
	स्थिर काष्ठा nfs_pageio_ops *pg_पढ़ो_ops;
	स्थिर काष्ठा nfs_pageio_ops *pg_ग_लिखो_ops;

	काष्ठा pnfs_ds_commit_info *(*get_ds_info) (काष्ठा inode *inode);

	पूर्णांक (*sync)(काष्ठा inode *inode, bool datasync);

	/*
	 * Return PNFS_ATTEMPTED to indicate the layout code has attempted
	 * I/O, अन्यथा वापस PNFS_NOT_ATTEMPTED to fall back to normal NFS
	 */
	क्रमागत pnfs_try_status (*पढ़ो_pagelist)(काष्ठा nfs_pgio_header *);
	क्रमागत pnfs_try_status (*ग_लिखो_pagelist)(काष्ठा nfs_pgio_header *, पूर्णांक);

	व्योम (*मुक्त_deviceid_node) (काष्ठा nfs4_deviceid_node *);
	काष्ठा nfs4_deviceid_node * (*alloc_deviceid_node)
			(काष्ठा nfs_server *server, काष्ठा pnfs_device *pdev,
			gfp_t gfp_flags);

	पूर्णांक (*prepare_layoutवापस) (काष्ठा nfs4_layoutवापस_args *);

	व्योम (*cleanup_layoutcommit) (काष्ठा nfs4_layoutcommit_data *data);
	पूर्णांक (*prepare_layoutcommit) (काष्ठा nfs4_layoutcommit_args *args);
	पूर्णांक (*prepare_layoutstats) (काष्ठा nfs42_layoutstat_args *args);
पूर्ण;

काष्ठा pnfs_commit_ops अणु
	व्योम (*setup_ds_info)(काष्ठा pnfs_ds_commit_info *,
			      काष्ठा pnfs_layout_segment *);
	व्योम (*release_ds_info)(काष्ठा pnfs_ds_commit_info *,
				काष्ठा inode *inode);
	पूर्णांक (*commit_pagelist)(काष्ठा inode *inode,
			       काष्ठा list_head *mds_pages,
			       पूर्णांक how,
			       काष्ठा nfs_commit_info *cinfo);
	व्योम (*mark_request_commit) (काष्ठा nfs_page *req,
				     काष्ठा pnfs_layout_segment *lseg,
				     काष्ठा nfs_commit_info *cinfo,
				     u32 ds_commit_idx);
	व्योम (*clear_request_commit) (काष्ठा nfs_page *req,
				      काष्ठा nfs_commit_info *cinfo);
	पूर्णांक (*scan_commit_lists) (काष्ठा nfs_commit_info *cinfo,
				  पूर्णांक max);
	व्योम (*recover_commit_reqs) (काष्ठा list_head *list,
				     काष्ठा nfs_commit_info *cinfo);
	काष्ठा nfs_page * (*search_commit_reqs)(काष्ठा nfs_commit_info *cinfo,
						काष्ठा page *page);
पूर्ण;

काष्ठा pnfs_layout_hdr अणु
	refcount_t		plh_refcount;
	atomic_t		plh_outstanding; /* number of RPCs out */
	काष्ठा list_head	plh_layouts;   /* other client layouts */
	काष्ठा list_head	plh_bulk_destroy;
	काष्ठा list_head	plh_segs;      /* layout segments list */
	काष्ठा list_head	plh_वापस_segs; /* invalid layout segments */
	अचिन्हित दीर्घ		plh_block_lमाला_लो; /* block LAYOUTGET अगर >0 */
	अचिन्हित दीर्घ		plh_retry_बारtamp;
	अचिन्हित दीर्घ		plh_flags;
	nfs4_stateid		plh_stateid;
	u32			plh_barrier; /* ignore lower seqids */
	u32			plh_वापस_seq;
	क्रमागत pnfs_iomode	plh_वापस_iomode;
	loff_t			plh_lwb; /* last ग_लिखो byte क्रम layoutcommit */
	स्थिर काष्ठा cred	*plh_lc_cred; /* layoutcommit cred */
	काष्ठा inode		*plh_inode;
	काष्ठा rcu_head		plh_rcu;
पूर्ण;

काष्ठा pnfs_device अणु
	काष्ठा nfs4_deviceid dev_id;
	अचिन्हित पूर्णांक  layout_type;
	अचिन्हित पूर्णांक  mincount;
	अचिन्हित पूर्णांक  maxcount;	/* gdia_maxcount */
	काष्ठा page **pages;
	अचिन्हित पूर्णांक  pgbase;
	अचिन्हित पूर्णांक  pglen;	/* reply buffer length */
	अचिन्हित अक्षर nocache : 1;/* May not be cached */
पूर्ण;

#घोषणा NFS4_PNFS_GETDEVLIST_MAXNUM 16

काष्ठा pnfs_devicelist अणु
	अचिन्हित पूर्णांक		eof;
	अचिन्हित पूर्णांक		num_devs;
	काष्ठा nfs4_deviceid	dev_id[NFS4_PNFS_GETDEVLIST_MAXNUM];
पूर्ण;

बाह्य पूर्णांक pnfs_रेजिस्टर_layoutdriver(काष्ठा pnfs_layoutdriver_type *);
बाह्य व्योम pnfs_unरेजिस्टर_layoutdriver(काष्ठा pnfs_layoutdriver_type *);

/* nfs4proc.c */
बाह्य माप_प्रकार max_response_pages(काष्ठा nfs_server *server);
बाह्य पूर्णांक nfs4_proc_getdeviceinfo(काष्ठा nfs_server *server,
				   काष्ठा pnfs_device *dev,
				   स्थिर काष्ठा cred *cred);
बाह्य काष्ठा pnfs_layout_segment* nfs4_proc_layoutget(काष्ठा nfs4_layoutget *lgp, दीर्घ *समयout);
बाह्य पूर्णांक nfs4_proc_layoutवापस(काष्ठा nfs4_layoutवापस *lrp, bool sync);

/* pnfs.c */
व्योम pnfs_get_layout_hdr(काष्ठा pnfs_layout_hdr *lo);
व्योम pnfs_put_lseg(काष्ठा pnfs_layout_segment *lseg);

व्योम set_pnfs_layoutdriver(काष्ठा nfs_server *, स्थिर काष्ठा nfs_fh *, काष्ठा nfs_fsinfo *);
व्योम unset_pnfs_layoutdriver(काष्ठा nfs_server *);
व्योम pnfs_generic_pg_check_layout(काष्ठा nfs_pageio_descriptor *pgio);
व्योम pnfs_generic_pg_check_range(काष्ठा nfs_pageio_descriptor *pgio, काष्ठा nfs_page *req);
व्योम pnfs_generic_pg_init_पढ़ो(काष्ठा nfs_pageio_descriptor *, काष्ठा nfs_page *);
पूर्णांक pnfs_generic_pg_पढ़ोpages(काष्ठा nfs_pageio_descriptor *desc);
व्योम pnfs_generic_pg_init_ग_लिखो(काष्ठा nfs_pageio_descriptor *pgio,
			        काष्ठा nfs_page *req, u64 wb_size);
व्योम pnfs_generic_pg_cleanup(काष्ठा nfs_pageio_descriptor *);
पूर्णांक pnfs_generic_pg_ग_लिखोpages(काष्ठा nfs_pageio_descriptor *desc);
माप_प्रकार pnfs_generic_pg_test(काष्ठा nfs_pageio_descriptor *pgio,
			    काष्ठा nfs_page *prev, काष्ठा nfs_page *req);
व्योम pnfs_set_lo_fail(काष्ठा pnfs_layout_segment *lseg);
काष्ठा pnfs_layout_segment *pnfs_layout_process(काष्ठा nfs4_layoutget *lgp);
व्योम pnfs_layoutget_मुक्त(काष्ठा nfs4_layoutget *lgp);
व्योम pnfs_मुक्त_lseg_list(काष्ठा list_head *पंचांगp_list);
व्योम pnfs_destroy_layout(काष्ठा nfs_inode *);
व्योम pnfs_destroy_layout_final(काष्ठा nfs_inode *);
व्योम pnfs_destroy_all_layouts(काष्ठा nfs_client *);
पूर्णांक pnfs_destroy_layouts_byfsid(काष्ठा nfs_client *clp,
		काष्ठा nfs_fsid *fsid,
		bool is_recall);
पूर्णांक pnfs_destroy_layouts_byclid(काष्ठा nfs_client *clp,
		bool is_recall);
bool nfs4_layout_refresh_old_stateid(nfs4_stateid *dst,
		काष्ठा pnfs_layout_range *dst_range,
		काष्ठा inode *inode);
व्योम pnfs_put_layout_hdr(काष्ठा pnfs_layout_hdr *lo);
व्योम pnfs_set_layout_stateid(काष्ठा pnfs_layout_hdr *lo,
			     स्थिर nfs4_stateid *new,
			     स्थिर काष्ठा cred *cred,
			     bool update_barrier);
पूर्णांक pnfs_mark_matching_lsegs_invalid(काष्ठा pnfs_layout_hdr *lo,
				काष्ठा list_head *पंचांगp_list,
				स्थिर काष्ठा pnfs_layout_range *recall_range,
				u32 seq);
पूर्णांक pnfs_mark_matching_lsegs_वापस(काष्ठा pnfs_layout_hdr *lo,
				काष्ठा list_head *पंचांगp_list,
				स्थिर काष्ठा pnfs_layout_range *recall_range,
				u32 seq);
पूर्णांक pnfs_mark_layout_stateid_invalid(काष्ठा pnfs_layout_hdr *lo,
		काष्ठा list_head *lseg_list);
bool pnfs_roc(काष्ठा inode *ino,
		काष्ठा nfs4_layoutवापस_args *args,
		काष्ठा nfs4_layoutवापस_res *res,
		स्थिर काष्ठा cred *cred);
पूर्णांक pnfs_roc_करोne(काष्ठा rpc_task *task, काष्ठा nfs4_layoutवापस_args **argpp,
		  काष्ठा nfs4_layoutवापस_res **respp, पूर्णांक *ret);
व्योम pnfs_roc_release(काष्ठा nfs4_layoutवापस_args *args,
		काष्ठा nfs4_layoutवापस_res *res,
		पूर्णांक ret);
bool pnfs_रुको_on_layoutवापस(काष्ठा inode *ino, काष्ठा rpc_task *task);
व्योम pnfs_set_layoutcommit(काष्ठा inode *, काष्ठा pnfs_layout_segment *, loff_t);
व्योम pnfs_cleanup_layoutcommit(काष्ठा nfs4_layoutcommit_data *data);
पूर्णांक pnfs_layoutcommit_inode(काष्ठा inode *inode, bool sync);
पूर्णांक pnfs_generic_sync(काष्ठा inode *inode, bool datasync);
पूर्णांक pnfs_nfs_generic_sync(काष्ठा inode *inode, bool datasync);
पूर्णांक _pnfs_वापस_layout(काष्ठा inode *);
पूर्णांक pnfs_commit_and_वापस_layout(काष्ठा inode *);
व्योम pnfs_ld_ग_लिखो_करोne(काष्ठा nfs_pgio_header *);
व्योम pnfs_ld_पढ़ो_करोne(काष्ठा nfs_pgio_header *);
व्योम pnfs_पढ़ो_resend_pnfs(काष्ठा nfs_pgio_header *, अचिन्हित पूर्णांक mirror_idx);
काष्ठा pnfs_layout_segment *pnfs_update_layout(काष्ठा inode *ino,
					       काष्ठा nfs_खोलो_context *ctx,
					       loff_t pos,
					       u64 count,
					       क्रमागत pnfs_iomode iomode,
					       bool strict_iomode,
					       gfp_t gfp_flags);
व्योम pnfs_layoutवापस_मुक्त_lsegs(काष्ठा pnfs_layout_hdr *lo,
		स्थिर nfs4_stateid *arg_stateid,
		स्थिर काष्ठा pnfs_layout_range *range,
		स्थिर nfs4_stateid *stateid);

व्योम pnfs_generic_layout_insert_lseg(काष्ठा pnfs_layout_hdr *lo,
		   काष्ठा pnfs_layout_segment *lseg,
		   bool (*is_after)(स्थिर काष्ठा pnfs_layout_range *lseg_range,
			   स्थिर काष्ठा pnfs_layout_range *old),
		   bool (*करो_merge)(काष्ठा pnfs_layout_segment *lseg,
			   काष्ठा pnfs_layout_segment *old),
		   काष्ठा list_head *मुक्त_me);

व्योम nfs4_deviceid_mark_client_invalid(काष्ठा nfs_client *clp);
पूर्णांक pnfs_पढ़ो_करोne_resend_to_mds(काष्ठा nfs_pgio_header *);
पूर्णांक pnfs_ग_लिखो_करोne_resend_to_mds(काष्ठा nfs_pgio_header *);
काष्ठा nfs4_threshold *pnfs_mdsthreshold_alloc(व्योम);
व्योम pnfs_error_mark_layout_क्रम_वापस(काष्ठा inode *inode,
				       काष्ठा pnfs_layout_segment *lseg);
व्योम pnfs_layout_वापस_unused_byclid(काष्ठा nfs_client *clp,
				      क्रमागत pnfs_iomode iomode);

/* nfs4_deviceid_flags */
क्रमागत अणु
	NFS_DEVICEID_INVALID = 0,       /* set when MDS clientid recalled */
	NFS_DEVICEID_UNAVAILABLE,	/* device temporarily unavailable */
	NFS_DEVICEID_NOCACHE,		/* device may not be cached */
पूर्ण;

/* pnfs_dev.c */
काष्ठा nfs4_deviceid_node अणु
	काष्ठा hlist_node		node;
	काष्ठा hlist_node		पंचांगpnode;
	स्थिर काष्ठा pnfs_layoutdriver_type *ld;
	स्थिर काष्ठा nfs_client		*nfs_client;
	अचिन्हित दीर्घ 			flags;
	अचिन्हित दीर्घ			बारtamp_unavailable;
	काष्ठा nfs4_deviceid		deviceid;
	काष्ठा rcu_head			rcu;
	atomic_t			ref;
पूर्ण;

काष्ठा nfs4_deviceid_node *
nfs4_find_get_deviceid(काष्ठा nfs_server *server,
		स्थिर काष्ठा nfs4_deviceid *id, स्थिर काष्ठा cred *cred,
		gfp_t gfp_mask);
व्योम nfs4_delete_deviceid(स्थिर काष्ठा pnfs_layoutdriver_type *, स्थिर काष्ठा nfs_client *, स्थिर काष्ठा nfs4_deviceid *);
व्योम nfs4_init_deviceid_node(काष्ठा nfs4_deviceid_node *, काष्ठा nfs_server *,
			     स्थिर काष्ठा nfs4_deviceid *);
bool nfs4_put_deviceid_node(काष्ठा nfs4_deviceid_node *);
व्योम nfs4_mark_deviceid_available(काष्ठा nfs4_deviceid_node *node);
व्योम nfs4_mark_deviceid_unavailable(काष्ठा nfs4_deviceid_node *node);
bool nfs4_test_deviceid_unavailable(काष्ठा nfs4_deviceid_node *node);
व्योम nfs4_deviceid_purge_client(स्थिर काष्ठा nfs_client *);

/* pnfs_nfs.c */
काष्ठा pnfs_commit_array *pnfs_alloc_commit_array(माप_प्रकार n, gfp_t gfp_flags);
व्योम pnfs_मुक्त_commit_array(काष्ठा pnfs_commit_array *p);
काष्ठा pnfs_commit_array *pnfs_add_commit_array(काष्ठा pnfs_ds_commit_info *,
						काष्ठा pnfs_commit_array *,
						काष्ठा pnfs_layout_segment *);

व्योम pnfs_generic_ds_cinfo_release_lseg(काष्ठा pnfs_ds_commit_info *fl_cinfo,
		काष्ठा pnfs_layout_segment *lseg);
व्योम pnfs_generic_ds_cinfo_destroy(काष्ठा pnfs_ds_commit_info *fl_cinfo);

व्योम pnfs_generic_clear_request_commit(काष्ठा nfs_page *req,
				       काष्ठा nfs_commit_info *cinfo);
व्योम pnfs_generic_commit_release(व्योम *calldata);
व्योम pnfs_generic_prepare_to_resend_ग_लिखोs(काष्ठा nfs_commit_data *data);
व्योम pnfs_generic_rw_release(व्योम *data);
व्योम pnfs_generic_recover_commit_reqs(काष्ठा list_head *dst,
				      काष्ठा nfs_commit_info *cinfo);
काष्ठा nfs_page *pnfs_generic_search_commit_reqs(काष्ठा nfs_commit_info *cinfo,
						 काष्ठा page *page);
पूर्णांक pnfs_generic_commit_pagelist(काष्ठा inode *inode,
				 काष्ठा list_head *mds_pages,
				 पूर्णांक how,
				 काष्ठा nfs_commit_info *cinfo,
				 पूर्णांक (*initiate_commit)(काष्ठा nfs_commit_data *data,
							पूर्णांक how));
पूर्णांक pnfs_generic_scan_commit_lists(काष्ठा nfs_commit_info *cinfo, पूर्णांक max);
व्योम pnfs_generic_ग_लिखो_commit_करोne(काष्ठा rpc_task *task, व्योम *data);
व्योम nfs4_pnfs_ds_put(काष्ठा nfs4_pnfs_ds *ds);
काष्ठा nfs4_pnfs_ds *nfs4_pnfs_ds_add(काष्ठा list_head *dsaddrs,
				      gfp_t gfp_flags);
व्योम nfs4_pnfs_v3_ds_connect_unload(व्योम);
पूर्णांक nfs4_pnfs_ds_connect(काष्ठा nfs_server *mds_srv, काष्ठा nfs4_pnfs_ds *ds,
			  काष्ठा nfs4_deviceid_node *devid, अचिन्हित पूर्णांक समयo,
			  अचिन्हित पूर्णांक retrans, u32 version, u32 minor_version);
काष्ठा nfs4_pnfs_ds_addr *nfs4_decode_mp_ds_addr(काष्ठा net *net,
						 काष्ठा xdr_stream *xdr,
						 gfp_t gfp_flags);
व्योम pnfs_layout_mark_request_commit(काष्ठा nfs_page *req,
				     काष्ठा pnfs_layout_segment *lseg,
				     काष्ठा nfs_commit_info *cinfo,
				     u32 ds_commit_idx);
व्योम pnfs_lgखोलो_prepare(काष्ठा nfs4_खोलोdata *data,
			 काष्ठा nfs_खोलो_context *ctx);
व्योम pnfs_parse_lgखोलो(काष्ठा inode *ino, काष्ठा nfs4_layoutget *lgp,
		       काष्ठा nfs_खोलो_context *ctx);
व्योम nfs4_lgखोलो_release(काष्ठा nfs4_layoutget *lgp);

अटल अंतरभूत bool nfs_have_layout(काष्ठा inode *inode)
अणु
	वापस NFS_I(inode)->layout != शून्य;
पूर्ण

अटल अंतरभूत bool pnfs_layout_is_valid(स्थिर काष्ठा pnfs_layout_hdr *lo)
अणु
	वापस test_bit(NFS_LAYOUT_INVALID_STID, &lo->plh_flags) == 0;
पूर्ण

अटल अंतरभूत काष्ठा nfs4_deviceid_node *
nfs4_get_deviceid(काष्ठा nfs4_deviceid_node *d)
अणु
	atomic_inc(&d->ref);
	वापस d;
पूर्ण

अटल अंतरभूत काष्ठा pnfs_layout_segment *
pnfs_get_lseg(काष्ठा pnfs_layout_segment *lseg)
अणु
	अगर (lseg) अणु
		refcount_inc(&lseg->pls_refcount);
		smp_mb__after_atomic();
	पूर्ण
	वापस lseg;
पूर्ण

अटल अंतरभूत bool
pnfs_is_valid_lseg(काष्ठा pnfs_layout_segment *lseg)
अणु
	वापस test_bit(NFS_LSEG_VALID, &lseg->pls_flags) != 0;
पूर्ण

/* Return true अगर a layout driver is being used क्रम this mountpoपूर्णांक */
अटल अंतरभूत पूर्णांक pnfs_enabled_sb(काष्ठा nfs_server *nfss)
अणु
	वापस nfss->pnfs_curr_ld != शून्य;
पूर्ण

अटल अंतरभूत पूर्णांक
pnfs_commit_list(काष्ठा inode *inode, काष्ठा list_head *mds_pages, पूर्णांक how,
		 काष्ठा nfs_commit_info *cinfo)
अणु
	काष्ठा pnfs_ds_commit_info *fl_cinfo = cinfo->ds;

	अगर (fl_cinfo == शून्य || fl_cinfo->ncommitting == 0)
		वापस PNFS_NOT_ATTEMPTED;
	वापस fl_cinfo->ops->commit_pagelist(inode, mds_pages, how, cinfo);
पूर्ण

अटल अंतरभूत काष्ठा pnfs_ds_commit_info *
pnfs_get_ds_info(काष्ठा inode *inode)
अणु
	काष्ठा pnfs_layoutdriver_type *ld = NFS_SERVER(inode)->pnfs_curr_ld;

	अगर (ld == शून्य || ld->get_ds_info == शून्य)
		वापस शून्य;
	वापस ld->get_ds_info(inode);
पूर्ण

अटल अंतरभूत व्योम
pnfs_init_ds_commit_info_ops(काष्ठा pnfs_ds_commit_info *fl_cinfo, काष्ठा inode *inode)
अणु
	काष्ठा pnfs_ds_commit_info *inode_cinfo = pnfs_get_ds_info(inode);
	अगर (inode_cinfo != शून्य)
		fl_cinfo->ops = inode_cinfo->ops;
पूर्ण

अटल अंतरभूत व्योम
pnfs_init_ds_commit_info(काष्ठा pnfs_ds_commit_info *fl_cinfo)
अणु
	INIT_LIST_HEAD(&fl_cinfo->commits);
	fl_cinfo->ops = शून्य;
पूर्ण

अटल अंतरभूत व्योम
pnfs_release_ds_info(काष्ठा pnfs_ds_commit_info *fl_cinfo, काष्ठा inode *inode)
अणु
	अगर (fl_cinfo->ops != शून्य && fl_cinfo->ops->release_ds_info != शून्य)
		fl_cinfo->ops->release_ds_info(fl_cinfo, inode);
पूर्ण

अटल अंतरभूत व्योम
pnfs_generic_mark_devid_invalid(काष्ठा nfs4_deviceid_node *node)
अणु
	set_bit(NFS_DEVICEID_INVALID, &node->flags);
पूर्ण

अटल अंतरभूत bool
pnfs_mark_request_commit(काष्ठा nfs_page *req, काष्ठा pnfs_layout_segment *lseg,
			 काष्ठा nfs_commit_info *cinfo, u32 ds_commit_idx)
अणु
	काष्ठा pnfs_ds_commit_info *fl_cinfo = cinfo->ds;

	अगर (!lseg || !fl_cinfo->ops->mark_request_commit)
		वापस false;
	fl_cinfo->ops->mark_request_commit(req, lseg, cinfo, ds_commit_idx);
	वापस true;
पूर्ण

अटल अंतरभूत bool
pnfs_clear_request_commit(काष्ठा nfs_page *req, काष्ठा nfs_commit_info *cinfo)
अणु
	काष्ठा pnfs_ds_commit_info *fl_cinfo = cinfo->ds;

	अगर (!fl_cinfo || !fl_cinfo->ops || !fl_cinfo->ops->clear_request_commit)
		वापस false;
	fl_cinfo->ops->clear_request_commit(req, cinfo);
	वापस true;
पूर्ण

अटल अंतरभूत पूर्णांक
pnfs_scan_commit_lists(काष्ठा inode *inode, काष्ठा nfs_commit_info *cinfo,
		       पूर्णांक max)
अणु
	काष्ठा pnfs_ds_commit_info *fl_cinfo = cinfo->ds;

	अगर (!fl_cinfo || fl_cinfo->nwritten == 0)
		वापस 0;
	वापस fl_cinfo->ops->scan_commit_lists(cinfo, max);
पूर्ण

अटल अंतरभूत व्योम
pnfs_recover_commit_reqs(काष्ठा list_head *head, काष्ठा nfs_commit_info *cinfo)
अणु
	काष्ठा pnfs_ds_commit_info *fl_cinfo = cinfo->ds;

	अगर (fl_cinfo && fl_cinfo->nwritten != 0)
		fl_cinfo->ops->recover_commit_reqs(head, cinfo);
पूर्ण

अटल अंतरभूत काष्ठा nfs_page *
pnfs_search_commit_reqs(काष्ठा inode *inode, काष्ठा nfs_commit_info *cinfo,
			काष्ठा page *page)
अणु
	काष्ठा pnfs_ds_commit_info *fl_cinfo = cinfo->ds;

	अगर (!fl_cinfo->ops || !fl_cinfo->ops->search_commit_reqs)
		वापस शून्य;
	वापस fl_cinfo->ops->search_commit_reqs(cinfo, page);
पूर्ण

/* Should the pNFS client commit and वापस the layout upon a setattr */
अटल अंतरभूत bool
pnfs_ld_layoutret_on_setattr(काष्ठा inode *inode)
अणु
	अगर (!pnfs_enabled_sb(NFS_SERVER(inode)))
		वापस false;
	वापस NFS_SERVER(inode)->pnfs_curr_ld->flags &
		PNFS_LAYOUTRET_ON_SETATTR;
पूर्ण

अटल अंतरभूत bool
pnfs_ld_पढ़ो_whole_page(काष्ठा inode *inode)
अणु
	अगर (!pnfs_enabled_sb(NFS_SERVER(inode)))
		वापस false;
	वापस NFS_SERVER(inode)->pnfs_curr_ld->flags & PNFS_READ_WHOLE_PAGE;
पूर्ण

अटल अंतरभूत पूर्णांक
pnfs_sync_inode(काष्ठा inode *inode, bool datasync)
अणु
	अगर (!pnfs_enabled_sb(NFS_SERVER(inode)))
		वापस 0;
	वापस NFS_SERVER(inode)->pnfs_curr_ld->sync(inode, datasync);
पूर्ण

अटल अंतरभूत bool
pnfs_layoutcommit_outstanding(काष्ठा inode *inode)
अणु
	काष्ठा nfs_inode *nfsi = NFS_I(inode);

	वापस test_bit(NFS_INO_LAYOUTCOMMIT, &nfsi->flags) != 0 ||
		test_bit(NFS_INO_LAYOUTCOMMITTING, &nfsi->flags) != 0;
पूर्ण

अटल अंतरभूत पूर्णांक pnfs_वापस_layout(काष्ठा inode *ino)
अणु
	काष्ठा nfs_inode *nfsi = NFS_I(ino);
	काष्ठा nfs_server *nfss = NFS_SERVER(ino);

	अगर (pnfs_enabled_sb(nfss) && nfsi->layout) अणु
		set_bit(NFS_LAYOUT_RETURN_REQUESTED, &nfsi->layout->plh_flags);
		वापस _pnfs_वापस_layout(ino);
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत bool
pnfs_use_threshold(काष्ठा nfs4_threshold **dst, काष्ठा nfs4_threshold *src,
		   काष्ठा nfs_server *nfss)
अणु
	वापस (dst && src && src->bm != 0 && nfss->pnfs_curr_ld &&
					nfss->pnfs_curr_ld->id == src->l_type);
पूर्ण

अटल अंतरभूत u64
pnfs_calc_offset_end(u64 offset, u64 len)
अणु
	अगर (len == NFS4_MAX_UINT64 || len >= NFS4_MAX_UINT64 - offset)
		वापस NFS4_MAX_UINT64;
	वापस offset + len - 1;
पूर्ण

अटल अंतरभूत u64
pnfs_calc_offset_length(u64 offset, u64 end)
अणु
	अगर (end == NFS4_MAX_UINT64 || end <= offset)
		वापस NFS4_MAX_UINT64;
	वापस 1 + end - offset;
पूर्ण

अटल अंतरभूत व्योम
pnfs_copy_range(काष्ठा pnfs_layout_range *dst,
		स्थिर काष्ठा pnfs_layout_range *src)
अणु
	स_नकल(dst, src, माप(*dst));
पूर्ण

अटल अंतरभूत u64
pnfs_end_offset(u64 start, u64 len)
अणु
	अगर (NFS4_MAX_UINT64 - start <= len)
		वापस NFS4_MAX_UINT64;
	वापस start + len;
पूर्ण

/*
 * Are 2 ranges पूर्णांकersecting?
 *   start1                             end1
 *   [----------------------------------)
 *                                start2           end2
 *                                [----------------)
 */
अटल अंतरभूत bool
pnfs_is_range_पूर्णांकersecting(u64 start1, u64 end1, u64 start2, u64 end2)
अणु
	वापस (end1 == NFS4_MAX_UINT64 || start2 < end1) &&
		(end2 == NFS4_MAX_UINT64 || start1 < end2);
पूर्ण

अटल अंतरभूत bool
pnfs_lseg_range_पूर्णांकersecting(स्थिर काष्ठा pnfs_layout_range *l1,
		स्थिर काष्ठा pnfs_layout_range *l2)
अणु
	u64 end1 = pnfs_end_offset(l1->offset, l1->length);
	u64 end2 = pnfs_end_offset(l2->offset, l2->length);

	वापस pnfs_is_range_पूर्णांकersecting(l1->offset, end1, l2->offset, end2);
पूर्ण

अटल अंतरभूत bool
pnfs_lseg_request_पूर्णांकersecting(काष्ठा pnfs_layout_segment *lseg, काष्ठा nfs_page *req)
अणु
	u64 seg_last = pnfs_end_offset(lseg->pls_range.offset, lseg->pls_range.length);
	u64 req_last = req_offset(req) + req->wb_bytes;

	वापस pnfs_is_range_पूर्णांकersecting(lseg->pls_range.offset, seg_last,
				req_offset(req), req_last);
पूर्ण

बाह्य अचिन्हित पूर्णांक layoutstats_समयr;

#अगर_घोषित NFS_DEBUG
व्योम nfs4_prपूर्णांक_deviceid(स्थिर काष्ठा nfs4_deviceid *dev_id);
#अन्यथा
अटल अंतरभूत व्योम nfs4_prपूर्णांक_deviceid(स्थिर काष्ठा nfs4_deviceid *dev_id)
अणु
पूर्ण

#पूर्ण_अगर /* NFS_DEBUG */
#अन्यथा  /* CONFIG_NFS_V4_1 */

अटल अंतरभूत bool nfs_have_layout(काष्ठा inode *inode)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत व्योम pnfs_destroy_all_layouts(काष्ठा nfs_client *clp)
अणु
पूर्ण

अटल अंतरभूत व्योम pnfs_destroy_layout(काष्ठा nfs_inode *nfsi)
अणु
पूर्ण

अटल अंतरभूत व्योम pnfs_destroy_layout_final(काष्ठा nfs_inode *nfsi)
अणु
पूर्ण

अटल अंतरभूत काष्ठा pnfs_layout_segment *
pnfs_get_lseg(काष्ठा pnfs_layout_segment *lseg)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम pnfs_put_lseg(काष्ठा pnfs_layout_segment *lseg)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक pnfs_वापस_layout(काष्ठा inode *ino)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक pnfs_commit_and_वापस_layout(काष्ठा inode *inode)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत bool
pnfs_ld_layoutret_on_setattr(काष्ठा inode *inode)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत bool
pnfs_ld_पढ़ो_whole_page(काष्ठा inode *inode)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत पूर्णांक
pnfs_sync_inode(काष्ठा inode *inode, bool datasync)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत bool
pnfs_layoutcommit_outstanding(काष्ठा inode *inode)
अणु
	वापस false;
पूर्ण


अटल अंतरभूत bool
pnfs_roc(काष्ठा inode *ino,
		काष्ठा nfs4_layoutवापस_args *args,
		काष्ठा nfs4_layoutवापस_res *res,
		स्थिर काष्ठा cred *cred)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत पूर्णांक
pnfs_roc_करोne(काष्ठा rpc_task *task,
		काष्ठा nfs4_layoutवापस_args **argpp,
		काष्ठा nfs4_layoutवापस_res **respp,
		पूर्णांक *ret)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम
pnfs_roc_release(काष्ठा nfs4_layoutवापस_args *args,
		काष्ठा nfs4_layoutवापस_res *res,
		पूर्णांक ret)
अणु
पूर्ण

अटल अंतरभूत bool
pnfs_रुको_on_layoutवापस(काष्ठा inode *ino, काष्ठा rpc_task *task)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत व्योम set_pnfs_layoutdriver(काष्ठा nfs_server *s,
					 स्थिर काष्ठा nfs_fh *mntfh,
					 काष्ठा nfs_fsinfo *fsinfo)
अणु
पूर्ण

अटल अंतरभूत व्योम unset_pnfs_layoutdriver(काष्ठा nfs_server *s)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक
pnfs_commit_list(काष्ठा inode *inode, काष्ठा list_head *mds_pages, पूर्णांक how,
		 काष्ठा nfs_commit_info *cinfo)
अणु
	वापस PNFS_NOT_ATTEMPTED;
पूर्ण

अटल अंतरभूत काष्ठा pnfs_ds_commit_info *
pnfs_get_ds_info(काष्ठा inode *inode)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम
pnfs_init_ds_commit_info_ops(काष्ठा pnfs_ds_commit_info *fl_cinfo, काष्ठा inode *inode)
अणु
पूर्ण

अटल अंतरभूत व्योम
pnfs_init_ds_commit_info(काष्ठा pnfs_ds_commit_info *fl_cinfo)
अणु
पूर्ण

अटल अंतरभूत व्योम
pnfs_release_ds_info(काष्ठा pnfs_ds_commit_info *fl_cinfo, काष्ठा inode *inode)
अणु
पूर्ण

अटल अंतरभूत bool
pnfs_mark_request_commit(काष्ठा nfs_page *req, काष्ठा pnfs_layout_segment *lseg,
			 काष्ठा nfs_commit_info *cinfo, u32 ds_commit_idx)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत bool
pnfs_clear_request_commit(काष्ठा nfs_page *req, काष्ठा nfs_commit_info *cinfo)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत पूर्णांक
pnfs_scan_commit_lists(काष्ठा inode *inode, काष्ठा nfs_commit_info *cinfo,
		       पूर्णांक max)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम
pnfs_recover_commit_reqs(काष्ठा list_head *head, काष्ठा nfs_commit_info *cinfo)
अणु
पूर्ण

अटल अंतरभूत काष्ठा nfs_page *
pnfs_search_commit_reqs(काष्ठा inode *inode, काष्ठा nfs_commit_info *cinfo,
			काष्ठा page *page)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत पूर्णांक pnfs_layoutcommit_inode(काष्ठा inode *inode, bool sync)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत bool
pnfs_use_threshold(काष्ठा nfs4_threshold **dst, काष्ठा nfs4_threshold *src,
		   काष्ठा nfs_server *nfss)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत काष्ठा nfs4_threshold *pnfs_mdsthreshold_alloc(व्योम)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम nfs4_pnfs_v3_ds_connect_unload(व्योम)
अणु
पूर्ण

अटल अंतरभूत bool nfs4_layout_refresh_old_stateid(nfs4_stateid *dst,
		काष्ठा pnfs_layout_range *dst_range,
		काष्ठा inode *inode)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत व्योम pnfs_lgखोलो_prepare(काष्ठा nfs4_खोलोdata *data,
		काष्ठा nfs_खोलो_context *ctx)
अणु
पूर्ण

अटल अंतरभूत व्योम pnfs_parse_lgखोलो(काष्ठा inode *ino,
		काष्ठा nfs4_layoutget *lgp,
		काष्ठा nfs_खोलो_context *ctx)
अणु
पूर्ण

अटल अंतरभूत व्योम nfs4_lgखोलो_release(काष्ठा nfs4_layoutget *lgp)
अणु
पूर्ण

अटल अंतरभूत bool pnfs_layout_is_valid(स्थिर काष्ठा pnfs_layout_hdr *lo)
अणु
	वापस false;
पूर्ण

#पूर्ण_अगर /* CONFIG_NFS_V4_1 */

#अगर IS_ENABLED(CONFIG_NFS_V4_2)
पूर्णांक pnfs_report_layoutstat(काष्ठा inode *inode, gfp_t gfp_flags);
#अन्यथा
अटल अंतरभूत पूर्णांक
pnfs_report_layoutstat(काष्ठा inode *inode, gfp_t gfp_flags)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* FS_NFS_PNFS_H */
