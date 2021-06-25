<शैली गुरु>
/*
 *  Server-side types क्रम NFSv4.
 *
 *  Copyright (c) 2002 The Regents of the University of Michigan.
 *  All rights reserved.
 *
 *  Kendrick Smith <kmsmith@umich.edu>
 *  Andy Adamson   <andros@umich.edu>
 *
 *  Redistribution and use in source and binary क्रमms, with or without
 *  modअगरication, are permitted provided that the following conditions
 *  are met:
 *
 *  1. Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *  2. Redistributions in binary क्रमm must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     करोcumentation and/or other materials provided with the distribution.
 *  3. Neither the name of the University nor the names of its
 *     contributors may be used to enकरोrse or promote products derived
 *     from this software without specअगरic prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESS OR IMPLIED
 *  WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *  DISCLAIMED. IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 *  FOR ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 *  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 *  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 *  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 *  LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 *  NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 *  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#अगर_अघोषित _LINUX_NFSD_XDR4_H
#घोषणा _LINUX_NFSD_XDR4_H

#समावेश "state.h"
#समावेश "nfsd.h"

#घोषणा NFSD4_MAX_TAGLEN	128
#घोषणा XDR_LEN(n)                     (((n) + 3) & ~3)

#घोषणा CURRENT_STATE_ID_FLAG (1<<0)
#घोषणा SAVED_STATE_ID_FLAG (1<<1)

#घोषणा SET_CSTATE_FLAG(c, f) ((c)->sid_flags |= (f))
#घोषणा HAS_CSTATE_FLAG(c, f) ((c)->sid_flags & (f))
#घोषणा CLEAR_CSTATE_FLAG(c, f) ((c)->sid_flags &= ~(f))

काष्ठा nfsd4_compound_state अणु
	काष्ठा svc_fh		current_fh;
	काष्ठा svc_fh		save_fh;
	काष्ठा nfs4_stateowner	*replay_owner;
	काष्ठा nfs4_client	*clp;
	/* For sessions DRC */
	काष्ठा nfsd4_session	*session;
	काष्ठा nfsd4_slot	*slot;
	पूर्णांक			data_offset;
	bool                    spo_must_allowed;
	माप_प्रकार			iovlen;
	u32			minorversion;
	__be32			status;
	stateid_t	current_stateid;
	stateid_t	save_stateid;
	/* to indicate current and saved state id presents */
	u32		sid_flags;
पूर्ण;

अटल अंतरभूत bool nfsd4_has_session(काष्ठा nfsd4_compound_state *cs)
अणु
	वापस cs->slot != शून्य;
पूर्ण

काष्ठा nfsd4_change_info अणु
	u32		atomic;
	u64		beक्रमe_change;
	u64		after_change;
पूर्ण;

काष्ठा nfsd4_access अणु
	u32		ac_req_access;      /* request */
	u32		ac_supported;       /* response */
	u32		ac_resp_access;     /* response */
पूर्ण;

काष्ठा nfsd4_बंद अणु
	u32		cl_seqid;           /* request */
	stateid_t	cl_stateid;         /* request+response */
पूर्ण;

काष्ठा nfsd4_commit अणु
	u64		co_offset;          /* request */
	u32		co_count;           /* request */
	nfs4_verअगरier	co_verf;            /* response */
पूर्ण;

काष्ठा nfsd4_create अणु
	u32		cr_namelen;         /* request */
	अक्षर *		cr_name;            /* request */
	u32		cr_type;            /* request */
	जोड़ अणु                             /* request */
		काष्ठा अणु
			u32 datalen;
			अक्षर *data;
			काष्ठा kvec first;
		पूर्ण link;   /* NF4LNK */
		काष्ठा अणु
			u32 specdata1;
			u32 specdata2;
		पूर्ण dev;    /* NF4BLK, NF4CHR */
	पूर्ण u;
	u32		cr_bmval[3];        /* request */
	काष्ठा iattr	cr_iattr;           /* request */
	पूर्णांक		cr_umask;           /* request */
	काष्ठा nfsd4_change_info  cr_cinfo; /* response */
	काष्ठा nfs4_acl *cr_acl;
	काष्ठा xdr_netobj cr_label;
पूर्ण;
#घोषणा cr_datalen	u.link.datalen
#घोषणा cr_data		u.link.data
#घोषणा cr_first	u.link.first
#घोषणा cr_specdata1	u.dev.specdata1
#घोषणा cr_specdata2	u.dev.specdata2

काष्ठा nfsd4_delegवापस अणु
	stateid_t	dr_stateid;
पूर्ण;

काष्ठा nfsd4_getattr अणु
	u32		ga_bmval[3];        /* request */
	काष्ठा svc_fh	*ga_fhp;            /* response */
पूर्ण;

काष्ठा nfsd4_link अणु
	u32		li_namelen;         /* request */
	अक्षर *		li_name;            /* request */
	काष्ठा nfsd4_change_info  li_cinfo; /* response */
पूर्ण;

काष्ठा nfsd4_lock_denied अणु
	clientid_t	ld_clientid;
	काष्ठा xdr_netobj	ld_owner;
	u64             ld_start;
	u64             ld_length;
	u32             ld_type;
पूर्ण;

काष्ठा nfsd4_lock अणु
	/* request */
	u32             lk_type;
	u32             lk_reclaim;         /* boolean */
	u64             lk_offset;
	u64             lk_length;
	u32             lk_is_new;
	जोड़ अणु
		काष्ठा अणु
			u32             खोलो_seqid;
			stateid_t       खोलो_stateid;
			u32             lock_seqid;
			clientid_t      clientid;
			काष्ठा xdr_netobj owner;
		पूर्ण new;
		काष्ठा अणु
			stateid_t       lock_stateid;
			u32             lock_seqid;
		पूर्ण old;
	पूर्ण v;

	/* response */
	जोड़ अणु
		काष्ठा अणु
			stateid_t               stateid;
		पूर्ण ok;
		काष्ठा nfsd4_lock_denied        denied;
	पूर्ण u;
पूर्ण;
#घोषणा lk_new_खोलो_seqid       v.new.खोलो_seqid
#घोषणा lk_new_खोलो_stateid     v.new.खोलो_stateid
#घोषणा lk_new_lock_seqid       v.new.lock_seqid
#घोषणा lk_new_clientid         v.new.clientid
#घोषणा lk_new_owner            v.new.owner
#घोषणा lk_old_lock_stateid     v.old.lock_stateid
#घोषणा lk_old_lock_seqid       v.old.lock_seqid

#घोषणा lk_resp_stateid u.ok.stateid
#घोषणा lk_denied       u.denied


काष्ठा nfsd4_lockt अणु
	u32				lt_type;
	clientid_t			lt_clientid;
	काष्ठा xdr_netobj		lt_owner;
	u64				lt_offset;
	u64				lt_length;
	काष्ठा nfsd4_lock_denied  	lt_denied;
पूर्ण;

 
काष्ठा nfsd4_locku अणु
	u32             lu_type;
	u32             lu_seqid;
	stateid_t       lu_stateid;
	u64             lu_offset;
	u64             lu_length;
पूर्ण;


काष्ठा nfsd4_lookup अणु
	u32		lo_len;             /* request */
	अक्षर *		lo_name;            /* request */
पूर्ण;

काष्ठा nfsd4_putfh अणु
	u32		pf_fhlen;           /* request */
	अक्षर		*pf_fhval;          /* request */
	bool		no_verअगरy;	    /* represents क्रमeigh fh */
पूर्ण;

काष्ठा nfsd4_getxattr अणु
	अक्षर		*getxa_name;		/* request */
	u32		getxa_len;		/* request */
	व्योम		*getxa_buf;
पूर्ण;

काष्ठा nfsd4_setxattr अणु
	u32		setxa_flags;		/* request */
	अक्षर		*setxa_name;		/* request */
	अक्षर		*setxa_buf;		/* request */
	u32		setxa_len;		/* request */
	काष्ठा nfsd4_change_info  setxa_cinfo;	/* response */
पूर्ण;

काष्ठा nfsd4_हटाओxattr अणु
	अक्षर		*rmxa_name;		/* request */
	काष्ठा nfsd4_change_info  rmxa_cinfo;	/* response */
पूर्ण;

काष्ठा nfsd4_listxattrs अणु
	u64		lsxa_cookie;		/* request */
	u32		lsxa_maxcount;		/* request */
	अक्षर		*lsxa_buf;		/* unfiltered buffer (reply) */
	u32		lsxa_len;		/* unfiltered len (reply) */
पूर्ण;

काष्ठा nfsd4_खोलो अणु
	u32		op_claim_type;      /* request */
	u32		op_fnamelen;
	अक्षर *		op_fname;	    /* request - everything but CLAIM_PREV */
	u32		op_delegate_type;   /* request - CLAIM_PREV only */
	stateid_t       op_delegate_stateid; /* request - response */
	u32		op_why_no_deleg;    /* response - DELEG_NONE_EXT only */
	u32		op_create;     	    /* request */
	u32		op_createmode;      /* request */
	पूर्णांक		op_umask;           /* request */
	u32		op_bmval[3];        /* request */
	काष्ठा iattr	op_iattr;           /* UNCHECKED4, GUARDED4, EXCLUSIVE4_1 */
	nfs4_verअगरier	op_verf __attribute__((aligned(32)));
					    /* EXCLUSIVE4 */
	clientid_t	op_clientid;        /* request */
	काष्ठा xdr_netobj op_owner;           /* request */
	u32		op_seqid;           /* request */
	u32		op_share_access;    /* request */
	u32		op_share_deny;      /* request */
	u32		op_deleg_want;      /* request */
	stateid_t	op_stateid;         /* response */
	__be32		op_xdr_error;       /* see nfsd4_खोलो_omfg() */
	u32		op_recall;          /* recall */
	काष्ठा nfsd4_change_info  op_cinfo; /* response */
	u32		op_rflags;          /* response */
	bool		op_truncate;        /* used during processing */
	bool		op_created;         /* used during processing */
	काष्ठा nfs4_खोलोowner *op_खोलोowner; /* used during processing */
	काष्ठा nfs4_file *op_file;          /* used during processing */
	काष्ठा nfs4_ol_stateid *op_stp;	    /* used during processing */
	काष्ठा nfs4_clnt_odstate *op_odstate; /* used during processing */
	काष्ठा nfs4_acl *op_acl;
	काष्ठा xdr_netobj op_label;
पूर्ण;

काष्ठा nfsd4_खोलो_confirm अणु
	stateid_t	oc_req_stateid		/* request */;
	u32		oc_seqid    		/* request */;
	stateid_t	oc_resp_stateid		/* response */;
पूर्ण;

काष्ठा nfsd4_खोलो_करोwngrade अणु
	stateid_t       od_stateid;
	u32             od_seqid;
	u32             od_share_access;	/* request */
	u32		od_deleg_want;		/* request */
	u32             od_share_deny;		/* request */
पूर्ण;


काष्ठा nfsd4_पढ़ो अणु
	stateid_t		rd_stateid;         /* request */
	u64			rd_offset;          /* request */
	u32			rd_length;          /* request */
	पूर्णांक			rd_vlen;
	काष्ठा nfsd_file	*rd_nf;
	
	काष्ठा svc_rqst		*rd_rqstp;          /* response */
	काष्ठा svc_fh		*rd_fhp;             /* response */
पूर्ण;

काष्ठा nfsd4_सूची_पढ़ो अणु
	u64		rd_cookie;          /* request */
	nfs4_verअगरier	rd_verf;            /* request */
	u32		rd_dircount;        /* request */
	u32		rd_maxcount;        /* request */
	u32		rd_bmval[3];        /* request */
	काष्ठा svc_rqst *rd_rqstp;          /* response */
	काष्ठा svc_fh * rd_fhp;             /* response */

	काष्ठा सूची_पढ़ो_cd	common;
	काष्ठा xdr_stream	*xdr;
	पूर्णांक			cookie_offset;
पूर्ण;

काष्ठा nfsd4_release_lockowner अणु
	clientid_t        rl_clientid;
	काष्ठा xdr_netobj rl_owner;
पूर्ण;
काष्ठा nfsd4_पढ़ोlink अणु
	काष्ठा svc_rqst *rl_rqstp;          /* request */
	काष्ठा svc_fh *	rl_fhp;             /* request */
पूर्ण;

काष्ठा nfsd4_हटाओ अणु
	u32		rm_namelen;         /* request */
	अक्षर *		rm_name;            /* request */
	काष्ठा nfsd4_change_info  rm_cinfo; /* response */
पूर्ण;

काष्ठा nfsd4_नाम अणु
	u32		rn_snamelen;        /* request */
	अक्षर *		rn_sname;           /* request */
	u32		rn_tnamelen;        /* request */
	अक्षर *		rn_tname;           /* request */
	काष्ठा nfsd4_change_info  rn_sinfo; /* response */
	काष्ठा nfsd4_change_info  rn_tinfo; /* response */
पूर्ण;

काष्ठा nfsd4_secinfo अणु
	u32 si_namelen;					/* request */
	अक्षर *si_name;					/* request */
	काष्ठा svc_export *si_exp;			/* response */
पूर्ण;

काष्ठा nfsd4_secinfo_no_name अणु
	u32 sin_style;					/* request */
	काष्ठा svc_export *sin_exp;			/* response */
पूर्ण;

काष्ठा nfsd4_setattr अणु
	stateid_t	sa_stateid;         /* request */
	u32		sa_bmval[3];        /* request */
	काष्ठा iattr	sa_iattr;           /* request */
	काष्ठा nfs4_acl *sa_acl;
	काष्ठा xdr_netobj sa_label;
पूर्ण;

काष्ठा nfsd4_setclientid अणु
	nfs4_verअगरier	se_verf;            /* request */
	काष्ठा xdr_netobj se_name;
	u32		se_callback_prog;   /* request */
	u32		se_callback_netid_len;  /* request */
	अक्षर *		se_callback_netid_val;  /* request */
	u32		se_callback_addr_len;   /* request */
	अक्षर *		se_callback_addr_val;   /* request */
	u32		se_callback_ident;  /* request */
	clientid_t	se_clientid;        /* response */
	nfs4_verअगरier	se_confirm;         /* response */
पूर्ण;

काष्ठा nfsd4_setclientid_confirm अणु
	clientid_t	sc_clientid;
	nfs4_verअगरier	sc_confirm;
पूर्ण;

काष्ठा nfsd4_test_stateid_id अणु
	__be32			ts_id_status;
	stateid_t		ts_id_stateid;
	काष्ठा list_head	ts_id_list;
पूर्ण;

काष्ठा nfsd4_test_stateid अणु
	u32		ts_num_ids;
	काष्ठा list_head ts_stateid_list;
पूर्ण;

काष्ठा nfsd4_मुक्त_stateid अणु
	stateid_t	fr_stateid;         /* request */
पूर्ण;

/* also used क्रम NVERIFY */
काष्ठा nfsd4_verअगरy अणु
	u32		ve_bmval[3];        /* request */
	u32		ve_attrlen;         /* request */
	अक्षर *		ve_attrval;         /* request */
पूर्ण;

काष्ठा nfsd4_ग_लिखो अणु
	stateid_t	wr_stateid;         /* request */
	u64		wr_offset;          /* request */
	u32		wr_stable_how;      /* request */
	u32		wr_buflen;          /* request */
	काष्ठा xdr_buf	wr_payload;         /* request */

	u32		wr_bytes_written;   /* response */
	u32		wr_how_written;     /* response */
	nfs4_verअगरier	wr_verअगरier;        /* response */
पूर्ण;

काष्ठा nfsd4_exchange_id अणु
	nfs4_verअगरier	verअगरier;
	काष्ठा xdr_netobj clname;
	u32		flags;
	clientid_t	clientid;
	u32		seqid;
	u32		spa_how;
	u32             spo_must_enक्रमce[3];
	u32             spo_must_allow[3];
	काष्ठा xdr_netobj nii_करोमुख्य;
	काष्ठा xdr_netobj nii_name;
	काष्ठा बारpec64 nii_समय;
पूर्ण;

काष्ठा nfsd4_sequence अणु
	काष्ठा nfs4_sessionid	sessionid;		/* request/response */
	u32			seqid;			/* request/response */
	u32			slotid;			/* request/response */
	u32			maxslots;		/* request/response */
	u32			cachethis;		/* request */
#अगर 0
	u32			target_maxslots;	/* response */
#पूर्ण_अगर /* not yet */
	u32			status_flags;		/* response */
पूर्ण;

काष्ठा nfsd4_destroy_session अणु
	काष्ठा nfs4_sessionid	sessionid;
पूर्ण;

काष्ठा nfsd4_destroy_clientid अणु
	clientid_t clientid;
पूर्ण;

काष्ठा nfsd4_reclaim_complete अणु
	u32 rca_one_fs;
पूर्ण;

काष्ठा nfsd4_deviceid अणु
	u64			fsid_idx;
	u32			generation;
	u32			pad;
पूर्ण;

काष्ठा nfsd4_layout_seg अणु
	u32			iomode;
	u64			offset;
	u64			length;
पूर्ण;

काष्ठा nfsd4_getdeviceinfo अणु
	काष्ठा nfsd4_deviceid	gd_devid;	/* request */
	u32			gd_layout_type;	/* request */
	u32			gd_maxcount;	/* request */
	u32			gd_notअगरy_types;/* request - response */
	व्योम			*gd_device;	/* response */
पूर्ण;

काष्ठा nfsd4_layoutget अणु
	u64			lg_minlength;	/* request */
	u32			lg_संकेत;	/* request */
	u32			lg_layout_type;	/* request */
	u32			lg_maxcount;	/* request */
	stateid_t		lg_sid;		/* request/response */
	काष्ठा nfsd4_layout_seg	lg_seg;		/* request/response */
	व्योम			*lg_content;	/* response */
पूर्ण;

काष्ठा nfsd4_layoutcommit अणु
	stateid_t		lc_sid;		/* request */
	काष्ठा nfsd4_layout_seg	lc_seg;		/* request */
	u32			lc_reclaim;	/* request */
	u32			lc_newoffset;	/* request */
	u64			lc_last_wr;	/* request */
	काष्ठा बारpec64	lc_mसमय;	/* request */
	u32			lc_layout_type;	/* request */
	u32			lc_up_len;	/* layout length */
	व्योम			*lc_up_layout;	/* decoded by callback */
	u32			lc_size_chg;	/* boolean क्रम response */
	u64			lc_newsize;	/* response */
पूर्ण;

काष्ठा nfsd4_layoutवापस अणु
	u32			lr_वापस_type;	/* request */
	u32			lr_layout_type;	/* request */
	काष्ठा nfsd4_layout_seg	lr_seg;		/* request */
	u32			lr_reclaim;	/* request */
	u32			lrf_body_len;	/* request */
	व्योम			*lrf_body;	/* request */
	stateid_t		lr_sid;		/* request/response */
	u32			lrs_present;	/* response */
पूर्ण;

काष्ठा nfsd4_fallocate अणु
	/* request */
	stateid_t	falloc_stateid;
	loff_t		falloc_offset;
	u64		falloc_length;
पूर्ण;

काष्ठा nfsd4_clone अणु
	/* request */
	stateid_t	cl_src_stateid;
	stateid_t	cl_dst_stateid;
	u64		cl_src_pos;
	u64		cl_dst_pos;
	u64		cl_count;
पूर्ण;

काष्ठा nfsd42_ग_लिखो_res अणु
	u64			wr_bytes_written;
	u32			wr_stable_how;
	nfs4_verअगरier		wr_verअगरier;
	stateid_t		cb_stateid;
पूर्ण;

काष्ठा nfsd4_copy अणु
	/* request */
	stateid_t		cp_src_stateid;
	stateid_t		cp_dst_stateid;
	u64			cp_src_pos;
	u64			cp_dst_pos;
	u64			cp_count;
	काष्ठा nl4_server	cp_src;
	bool			cp_पूर्णांकra;

	/* both */
	u32			cp_synchronous;

	/* response */
	काष्ठा nfsd42_ग_लिखो_res	cp_res;

	/* क्रम cb_offload */
	काष्ठा nfsd4_callback	cp_cb;
	__be32			nfserr;
	काष्ठा knfsd_fh		fh;

	काष्ठा nfs4_client      *cp_clp;

	काष्ठा nfsd_file        *nf_src;
	काष्ठा nfsd_file        *nf_dst;

	copy_stateid_t		cp_stateid;

	काष्ठा list_head	copies;
	काष्ठा task_काष्ठा	*copy_task;
	refcount_t		refcount;
	bool			stopped;

	काष्ठा vfsmount		*ss_mnt;
	काष्ठा nfs_fh		c_fh;
	nfs4_stateid		stateid;
पूर्ण;

काष्ठा nfsd4_seek अणु
	/* request */
	stateid_t	seek_stateid;
	loff_t		seek_offset;
	u32		seek_whence;

	/* response */
	u32		seek_eof;
	loff_t		seek_pos;
पूर्ण;

काष्ठा nfsd4_offload_status अणु
	/* request */
	stateid_t	stateid;

	/* response */
	u64		count;
	u32		status;
पूर्ण;

काष्ठा nfsd4_copy_notअगरy अणु
	/* request */
	stateid_t		cpn_src_stateid;
	काष्ठा nl4_server	cpn_dst;

	/* response */
	stateid_t		cpn_cnr_stateid;
	u64			cpn_sec;
	u32			cpn_nsec;
	काष्ठा nl4_server	cpn_src;
पूर्ण;

काष्ठा nfsd4_op अणु
	u32					opnum;
	स्थिर काष्ठा nfsd4_operation *		opdesc;
	__be32					status;
	जोड़ nfsd4_op_u अणु
		काष्ठा nfsd4_access		access;
		काष्ठा nfsd4_बंद		बंद;
		काष्ठा nfsd4_commit		commit;
		काष्ठा nfsd4_create		create;
		काष्ठा nfsd4_delegवापस	delegवापस;
		काष्ठा nfsd4_getattr		getattr;
		काष्ठा svc_fh *			getfh;
		काष्ठा nfsd4_link		link;
		काष्ठा nfsd4_lock		lock;
		काष्ठा nfsd4_lockt		lockt;
		काष्ठा nfsd4_locku		locku;
		काष्ठा nfsd4_lookup		lookup;
		काष्ठा nfsd4_verअगरy		nverअगरy;
		काष्ठा nfsd4_खोलो		खोलो;
		काष्ठा nfsd4_खोलो_confirm	खोलो_confirm;
		काष्ठा nfsd4_खोलो_करोwngrade	खोलो_करोwngrade;
		काष्ठा nfsd4_putfh		putfh;
		काष्ठा nfsd4_पढ़ो		पढ़ो;
		काष्ठा nfsd4_सूची_पढ़ो		सूची_पढ़ो;
		काष्ठा nfsd4_पढ़ोlink		पढ़ोlink;
		काष्ठा nfsd4_हटाओ		हटाओ;
		काष्ठा nfsd4_नाम		नाम;
		clientid_t			renew;
		काष्ठा nfsd4_secinfo		secinfo;
		काष्ठा nfsd4_setattr		setattr;
		काष्ठा nfsd4_setclientid	setclientid;
		काष्ठा nfsd4_setclientid_confirm setclientid_confirm;
		काष्ठा nfsd4_verअगरy		verअगरy;
		काष्ठा nfsd4_ग_लिखो		ग_लिखो;
		काष्ठा nfsd4_release_lockowner	release_lockowner;

		/* NFSv4.1 */
		काष्ठा nfsd4_exchange_id	exchange_id;
		काष्ठा nfsd4_backchannel_ctl	backchannel_ctl;
		काष्ठा nfsd4_bind_conn_to_session bind_conn_to_session;
		काष्ठा nfsd4_create_session	create_session;
		काष्ठा nfsd4_destroy_session	destroy_session;
		काष्ठा nfsd4_destroy_clientid	destroy_clientid;
		काष्ठा nfsd4_sequence		sequence;
		काष्ठा nfsd4_reclaim_complete	reclaim_complete;
		काष्ठा nfsd4_test_stateid	test_stateid;
		काष्ठा nfsd4_मुक्त_stateid	मुक्त_stateid;
		काष्ठा nfsd4_getdeviceinfo	getdeviceinfo;
		काष्ठा nfsd4_layoutget		layoutget;
		काष्ठा nfsd4_layoutcommit	layoutcommit;
		काष्ठा nfsd4_layoutवापस	layoutवापस;
		काष्ठा nfsd4_secinfo_no_name	secinfo_no_name;

		/* NFSv4.2 */
		काष्ठा nfsd4_fallocate		allocate;
		काष्ठा nfsd4_fallocate		deallocate;
		काष्ठा nfsd4_clone		clone;
		काष्ठा nfsd4_copy		copy;
		काष्ठा nfsd4_offload_status	offload_status;
		काष्ठा nfsd4_copy_notअगरy	copy_notअगरy;
		काष्ठा nfsd4_seek		seek;

		काष्ठा nfsd4_getxattr		getxattr;
		काष्ठा nfsd4_setxattr		setxattr;
		काष्ठा nfsd4_listxattrs		listxattrs;
		काष्ठा nfsd4_हटाओxattr	हटाओxattr;
	पूर्ण u;
	काष्ठा nfs4_replay *			replay;
पूर्ण;

bool nfsd4_cache_this_op(काष्ठा nfsd4_op *);

/*
 * Memory needed just क्रम the duration of processing one compound:
 */
काष्ठा svcxdr_पंचांगpbuf अणु
	काष्ठा svcxdr_पंचांगpbuf *next;
	अक्षर buf[];
पूर्ण;

काष्ठा nfsd4_compoundargs अणु
	/* scratch variables क्रम XDR decode */
	काष्ठा xdr_stream		*xdr;
	काष्ठा svcxdr_पंचांगpbuf		*to_मुक्त;
	काष्ठा svc_rqst			*rqstp;

	u32				taglen;
	अक्षर *				tag;
	u32				minorversion;
	u32				opcnt;
	काष्ठा nfsd4_op			*ops;
	काष्ठा nfsd4_op			iops[8];
	पूर्णांक				cachetype;
पूर्ण;

काष्ठा nfsd4_compoundres अणु
	/* scratch variables क्रम XDR encode */
	काष्ठा xdr_stream		*xdr;
	काष्ठा svc_rqst *		rqstp;

	u32				taglen;
	अक्षर *				tag;
	u32				opcnt;
	__be32 *			tagp; /* tag, opcount encode location */
	काष्ठा nfsd4_compound_state	cstate;
पूर्ण;

अटल अंतरभूत bool nfsd4_is_solo_sequence(काष्ठा nfsd4_compoundres *resp)
अणु
	काष्ठा nfsd4_compoundargs *args = resp->rqstp->rq_argp;
	वापस resp->opcnt == 1 && args->ops[0].opnum == OP_SEQUENCE;
पूर्ण

/*
 * The session reply cache only needs to cache replies that the client
 * actually asked us to.  But it's almost मुक्त क्रम us to cache compounds
 * consisting of only a SEQUENCE op, so we may as well cache those too.
 * Also, the protocol करोesn't give us a convenient response in the हाल
 * of a replay of a solo SEQUENCE op that wasn't cached
 * (RETRY_UNCACHED_REP can only be वापसed in the second op of a
 * compound).
 */
अटल अंतरभूत bool nfsd4_cache_this(काष्ठा nfsd4_compoundres *resp)
अणु
	वापस (resp->cstate.slot->sl_flags & NFSD4_SLOT_CACHETHIS)
		|| nfsd4_is_solo_sequence(resp);
पूर्ण

अटल अंतरभूत bool nfsd4_last_compound_op(काष्ठा svc_rqst *rqstp)
अणु
	काष्ठा nfsd4_compoundres *resp = rqstp->rq_resp;
	काष्ठा nfsd4_compoundargs *argp = rqstp->rq_argp;

	वापस argp->opcnt == resp->opcnt;
पूर्ण

स्थिर काष्ठा nfsd4_operation *OPDESC(काष्ठा nfsd4_op *op);
पूर्णांक nfsd4_max_reply(काष्ठा svc_rqst *rqstp, काष्ठा nfsd4_op *op);
व्योम warn_on_nonidempotent_op(काष्ठा nfsd4_op *op);

#घोषणा NFS4_SVC_XDRSIZE		माप(काष्ठा nfsd4_compoundargs)

अटल अंतरभूत व्योम
set_change_info(काष्ठा nfsd4_change_info *cinfo, काष्ठा svc_fh *fhp)
अणु
	BUG_ON(!fhp->fh_pre_saved);
	cinfo->atomic = (u32)(fhp->fh_post_saved && !fhp->fh_no_atomic_attr);

	cinfo->beक्रमe_change = fhp->fh_pre_change;
	cinfo->after_change = fhp->fh_post_change;
पूर्ण


bool nfsd4_mach_creds_match(काष्ठा nfs4_client *cl, काष्ठा svc_rqst *rqstp);
पूर्णांक nfs4svc_decode_compoundargs(काष्ठा svc_rqst *, __be32 *);
पूर्णांक nfs4svc_encode_compoundres(काष्ठा svc_rqst *, __be32 *);
__be32 nfsd4_check_resp_size(काष्ठा nfsd4_compoundres *, u32);
व्योम nfsd4_encode_operation(काष्ठा nfsd4_compoundres *, काष्ठा nfsd4_op *);
व्योम nfsd4_encode_replay(काष्ठा xdr_stream *xdr, काष्ठा nfsd4_op *op);
__be32 nfsd4_encode_fattr_to_buf(__be32 **p, पूर्णांक words,
		काष्ठा svc_fh *fhp, काष्ठा svc_export *exp,
		काष्ठा dentry *dentry,
		u32 *bmval, काष्ठा svc_rqst *, पूर्णांक ignore_crossmnt);
बाह्य __be32 nfsd4_setclientid(काष्ठा svc_rqst *rqstp,
		काष्ठा nfsd4_compound_state *, जोड़ nfsd4_op_u *u);
बाह्य __be32 nfsd4_setclientid_confirm(काष्ठा svc_rqst *rqstp,
		काष्ठा nfsd4_compound_state *, जोड़ nfsd4_op_u *u);
बाह्य __be32 nfsd4_exchange_id(काष्ठा svc_rqst *rqstp,
		काष्ठा nfsd4_compound_state *, जोड़ nfsd4_op_u *u);
बाह्य __be32 nfsd4_backchannel_ctl(काष्ठा svc_rqst *,
		काष्ठा nfsd4_compound_state *, जोड़ nfsd4_op_u *u);
बाह्य __be32 nfsd4_bind_conn_to_session(काष्ठा svc_rqst *,
		काष्ठा nfsd4_compound_state *, जोड़ nfsd4_op_u *u);
बाह्य __be32 nfsd4_create_session(काष्ठा svc_rqst *,
		काष्ठा nfsd4_compound_state *, जोड़ nfsd4_op_u *u);
बाह्य __be32 nfsd4_sequence(काष्ठा svc_rqst *,
		काष्ठा nfsd4_compound_state *, जोड़ nfsd4_op_u *u);
बाह्य व्योम nfsd4_sequence_करोne(काष्ठा nfsd4_compoundres *resp);
बाह्य __be32 nfsd4_destroy_session(काष्ठा svc_rqst *,
		काष्ठा nfsd4_compound_state *, जोड़ nfsd4_op_u *u);
बाह्य __be32 nfsd4_destroy_clientid(काष्ठा svc_rqst *, काष्ठा nfsd4_compound_state *,
		जोड़ nfsd4_op_u *u);
__be32 nfsd4_reclaim_complete(काष्ठा svc_rqst *, काष्ठा nfsd4_compound_state *,
		जोड़ nfsd4_op_u *u);
बाह्य __be32 nfsd4_process_खोलो1(काष्ठा nfsd4_compound_state *,
		काष्ठा nfsd4_खोलो *खोलो, काष्ठा nfsd_net *nn);
बाह्य __be32 nfsd4_process_खोलो2(काष्ठा svc_rqst *rqstp,
		काष्ठा svc_fh *current_fh, काष्ठा nfsd4_खोलो *खोलो);
बाह्य व्योम nfsd4_cstate_clear_replay(काष्ठा nfsd4_compound_state *cstate);
बाह्य व्योम nfsd4_cleanup_खोलो_state(काष्ठा nfsd4_compound_state *cstate,
		काष्ठा nfsd4_खोलो *खोलो);
बाह्य __be32 nfsd4_खोलो_confirm(काष्ठा svc_rqst *rqstp,
		काष्ठा nfsd4_compound_state *, जोड़ nfsd4_op_u *u);
बाह्य __be32 nfsd4_बंद(काष्ठा svc_rqst *rqstp, काष्ठा nfsd4_compound_state *,
		जोड़ nfsd4_op_u *u);
बाह्य __be32 nfsd4_खोलो_करोwngrade(काष्ठा svc_rqst *rqstp,
		काष्ठा nfsd4_compound_state *, जोड़ nfsd4_op_u *u);
बाह्य __be32 nfsd4_lock(काष्ठा svc_rqst *rqstp, काष्ठा nfsd4_compound_state *,
		जोड़ nfsd4_op_u *u);
बाह्य __be32 nfsd4_lockt(काष्ठा svc_rqst *rqstp, काष्ठा nfsd4_compound_state *,
		जोड़ nfsd4_op_u *u);
बाह्य __be32 nfsd4_locku(काष्ठा svc_rqst *rqstp, काष्ठा nfsd4_compound_state *,
		जोड़ nfsd4_op_u *u);
बाह्य __be32
nfsd4_release_lockowner(काष्ठा svc_rqst *rqstp,
		काष्ठा nfsd4_compound_state *, जोड़ nfsd4_op_u *u);
बाह्य व्योम nfsd4_release_compoundargs(काष्ठा svc_rqst *rqstp);
बाह्य __be32 nfsd4_delegवापस(काष्ठा svc_rqst *rqstp,
		काष्ठा nfsd4_compound_state *, जोड़ nfsd4_op_u *u);
बाह्य __be32 nfsd4_renew(काष्ठा svc_rqst *rqstp, काष्ठा nfsd4_compound_state *,
		जोड़ nfsd4_op_u *u);
बाह्य __be32 nfsd4_test_stateid(काष्ठा svc_rqst *rqstp,
		काष्ठा nfsd4_compound_state *, जोड़ nfsd4_op_u *);
बाह्य __be32 nfsd4_मुक्त_stateid(काष्ठा svc_rqst *rqstp,
		काष्ठा nfsd4_compound_state *, जोड़ nfsd4_op_u *);
बाह्य व्योम nfsd4_bump_seqid(काष्ठा nfsd4_compound_state *, __be32 nfserr);

क्रमागत nfsd4_op_flags अणु
	ALLOWED_WITHOUT_FH = 1 << 0,    /* No current filehandle required */
	ALLOWED_ON_ABSENT_FS = 1 << 1,  /* ops processed on असलent fs */
	ALLOWED_AS_FIRST_OP = 1 << 2,   /* ops reqired first in compound */
	/* For rfc 5661 section 2.6.3.1.1: */
	OP_HANDLES_WRONGSEC = 1 << 3,
	OP_IS_PUTFH_LIKE = 1 << 4,
	/*
	 * These are the ops whose result size we estimate beक्रमe
	 * encoding, to aव्योम perक्रमming an op then not being able to
	 * respond or cache a response.  This includes ग_लिखोs and setattrs
	 * as well as the operations usually called "nonidempotent":
	 */
	OP_MODIFIES_SOMETHING = 1 << 5,
	/*
	 * Cache compounds containing these ops in the xid-based drc:
	 * We use the DRC क्रम compounds containing non-idempotent
	 * operations, *except* those that are 4.1-specअगरic (since
	 * sessions provide their own EOS), and except क्रम stateful
	 * operations other than setclientid and setclientid_confirm
	 * (since sequence numbers provide EOS क्रम खोलो, lock, etc in
	 * the v4.0 हाल).
	 */
	OP_CACHEME = 1 << 6,
	/*
	 * These are ops which clear current state id.
	 */
	OP_CLEAR_STATEID = 1 << 7,
	/* Most ops वापस only an error on failure; some may करो more: */
	OP_NONTRIVIAL_ERROR_ENCODE = 1 << 8,
पूर्ण;

काष्ठा nfsd4_operation अणु
	__be32 (*op_func)(काष्ठा svc_rqst *, काष्ठा nfsd4_compound_state *,
			जोड़ nfsd4_op_u *);
	व्योम (*op_release)(जोड़ nfsd4_op_u *);
	u32 op_flags;
	अक्षर *op_name;
	/* Try to get response size beक्रमe operation */
	u32 (*op_rsize_bop)(काष्ठा svc_rqst *, काष्ठा nfsd4_op *);
	व्योम (*op_get_currentstateid)(काष्ठा nfsd4_compound_state *,
			जोड़ nfsd4_op_u *);
	व्योम (*op_set_currentstateid)(काष्ठा nfsd4_compound_state *,
			जोड़ nfsd4_op_u *);
पूर्ण;


#पूर्ण_अगर
