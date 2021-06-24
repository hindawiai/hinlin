<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/******************************************************************************
*******************************************************************************
**
**  Copyright (C) Sistina Software, Inc.  1997-2003  All rights reserved.
**  Copyright (C) 2004-2011 Red Hat, Inc.  All rights reserved.
**
**
*******************************************************************************
******************************************************************************/

#अगर_अघोषित __DLM_INTERNAL_DOT_H__
#घोषणा __DLM_INTERNAL_DOT_H__

/*
 * This is the मुख्य header file to be included in each DLM source file.
 */

#समावेश <linux/slab.h>
#समावेश <linux/sched.h>
#समावेश <linux/types.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/spinlock.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/list.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/delay.h>
#समावेश <linux/socket.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/kobject.h>
#समावेश <linux/kref.h>
#समावेश <linux/kernel.h>
#समावेश <linux/jhash.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/mutex.h>
#समावेश <linux/idr.h>
#समावेश <linux/ratelimit.h>
#समावेश <linux/uaccess.h>

#समावेश <linux/dlm.h>
#समावेश "config.h"

/* Size of the temp buffer midcomms allocates on the stack.
   We try to make this large enough so most messages fit.
   FIXME: should sctp make this unnecessary? */

#घोषणा DLM_INBUF_LEN		148

काष्ठा dlm_ls;
काष्ठा dlm_lkb;
काष्ठा dlm_rsb;
काष्ठा dlm_member;
काष्ठा dlm_rsbtable;
काष्ठा dlm_recover;
काष्ठा dlm_header;
काष्ठा dlm_message;
काष्ठा dlm_rcom;
काष्ठा dlm_mhandle;

#घोषणा log_prपूर्णांक(fmt, args...) \
	prपूर्णांकk(KERN_ERR "dlm: "fmt"\n" , ##args)
#घोषणा log_error(ls, fmt, args...) \
	prपूर्णांकk(KERN_ERR "dlm: %s: " fmt "\n", (ls)->ls_name , ##args)

#घोषणा log_rinfo(ls, fmt, args...) \
करो अणु \
	अगर (dlm_config.ci_log_info) \
		prपूर्णांकk(KERN_INFO "dlm: %s: " fmt "\n", \
			(ls)->ls_name, ##args); \
	अन्यथा अगर (dlm_config.ci_log_debug) \
		prपूर्णांकk(KERN_DEBUG "dlm: %s: " fmt "\n", \
		       (ls)->ls_name , ##args); \
पूर्ण जबतक (0)

#घोषणा log_debug(ls, fmt, args...) \
करो अणु \
	अगर (dlm_config.ci_log_debug) \
		prपूर्णांकk(KERN_DEBUG "dlm: %s: " fmt "\n", \
		       (ls)->ls_name , ##args); \
पूर्ण जबतक (0)

#घोषणा log_limit(ls, fmt, args...) \
करो अणु \
	अगर (dlm_config.ci_log_debug) \
		prपूर्णांकk_ratelimited(KERN_DEBUG "dlm: %s: " fmt "\n", \
			(ls)->ls_name , ##args); \
पूर्ण जबतक (0)

#घोषणा DLM_ASSERT(x, करो) \
अणु \
  अगर (!(x)) \
  अणु \
    prपूर्णांकk(KERN_ERR "\nDLM:  Assertion failed on line %d of file %s\n" \
               "DLM:  assertion:  \"%s\"\n" \
               "DLM:  time = %lu\n", \
               __LINE__, __खाता__, #x, jअगरfies); \
    अणुकरोपूर्ण \
    prपूर्णांकk("\n"); \
    panic("DLM:  Record message above and reboot.\n"); \
  पूर्ण \
पूर्ण


#घोषणा DLM_RTF_SHRINK		0x00000001

काष्ठा dlm_rsbtable अणु
	काष्ठा rb_root		keep;
	काष्ठा rb_root		toss;
	spinlock_t		lock;
	uपूर्णांक32_t		flags;
पूर्ण;


/*
 * Lockspace member (per node in a ls)
 */

काष्ठा dlm_member अणु
	काष्ठा list_head	list;
	पूर्णांक			nodeid;
	पूर्णांक			weight;
	पूर्णांक			slot;
	पूर्णांक			slot_prev;
	पूर्णांक			comm_seq;
	uपूर्णांक32_t		generation;
पूर्ण;

/*
 * Save and manage recovery state क्रम a lockspace.
 */

काष्ठा dlm_recover अणु
	काष्ठा list_head	list;
	काष्ठा dlm_config_node	*nodes;
	पूर्णांक			nodes_count;
	uपूर्णांक64_t		seq;
पूर्ण;

/*
 * Pass input args to second stage locking function.
 */

काष्ठा dlm_args अणु
	uपूर्णांक32_t		flags;
	व्योम			(*astfn) (व्योम *astparam);
	व्योम			*astparam;
	व्योम			(*bastfn) (व्योम *astparam, पूर्णांक mode);
	पूर्णांक			mode;
	काष्ठा dlm_lksb		*lksb;
	अचिन्हित दीर्घ		समयout;
पूर्ण;


/*
 * Lock block
 *
 * A lock can be one of three types:
 *
 * local copy      lock is mastered locally
 *                 (lkb_nodeid is zero and DLM_LKF_MSTCPY is not set)
 * process copy    lock is mastered on a remote node
 *                 (lkb_nodeid is non-zero and DLM_LKF_MSTCPY is not set)
 * master copy     master node's copy of a lock owned by remote node
 *                 (lkb_nodeid is non-zero and DLM_LKF_MSTCPY is set)
 *
 * lkb_exflags: a copy of the most recent flags arg provided to dlm_lock or
 * dlm_unlock.  The dlm करोes not modअगरy these or use any निजी flags in
 * this field; it only contains DLM_LKF_ flags from dlm.h.  These flags
 * are sent as-is to the remote master when the lock is remote.
 *
 * lkb_flags: पूर्णांकernal dlm flags (DLM_IFL_ prefix) from dlm_पूर्णांकernal.h.
 * Some पूर्णांकernal flags are shared between the master and process nodes;
 * these shared flags are kept in the lower two bytes.  One of these
 * flags set on the master copy will be propagated to the process copy
 * and v.v.  Other पूर्णांकernal flags are निजी to the master or process
 * node (e.g. DLM_IFL_MSTCPY).  These are kept in the high two bytes.
 *
 * lkb_sbflags: status block flags.  These flags are copied directly पूर्णांकo
 * the caller's lksb.sb_flags prior to the dlm_lock/dlm_unlock completion
 * ast.  All defined in dlm.h with DLM_SBF_ prefix.
 *
 * lkb_status: the lock status indicates which rsb queue the lock is
 * on, grant, convert, or रुको.  DLM_LKSTS_ WAITING/GRANTED/CONVERT
 *
 * lkb_रुको_type: the dlm message type (DLM_MSG_ prefix) क्रम which a
 * reply is needed.  Only set when the lkb is on the lockspace रुकोers
 * list aरुकोing a reply from a remote node.
 *
 * lkb_nodeid: when the lkb is a local copy, nodeid is 0; when the lkb
 * is a master copy, nodeid specअगरies the remote lock holder, when the
 * lkb is a process copy, the nodeid specअगरies the lock master.
 */

/* lkb_status */

#घोषणा DLM_LKSTS_WAITING	1
#घोषणा DLM_LKSTS_GRANTED	2
#घोषणा DLM_LKSTS_CONVERT	3

/* lkb_flags */

#घोषणा DLM_IFL_MSTCPY		0x00010000
#घोषणा DLM_IFL_RESEND		0x00020000
#घोषणा DLM_IFL_DEAD		0x00040000
#घोषणा DLM_IFL_OVERLAP_UNLOCK  0x00080000
#घोषणा DLM_IFL_OVERLAP_CANCEL  0x00100000
#घोषणा DLM_IFL_ENDOFLIFE	0x00200000
#घोषणा DLM_IFL_WATCH_TIMEWARN	0x00400000
#घोषणा DLM_IFL_TIMEOUT_CANCEL	0x00800000
#घोषणा DLM_IFL_DEADLOCK_CANCEL	0x01000000
#घोषणा DLM_IFL_STUB_MS		0x02000000 /* magic number क्रम m_flags */
#घोषणा DLM_IFL_USER		0x00000001
#घोषणा DLM_IFL_ORPHAN		0x00000002

#घोषणा DLM_CALLBACKS_SIZE	6

#घोषणा DLM_CB_CAST		0x00000001
#घोषणा DLM_CB_BAST		0x00000002
#घोषणा DLM_CB_SKIP		0x00000004

काष्ठा dlm_callback अणु
	uपूर्णांक64_t		seq;
	uपूर्णांक32_t		flags;		/* DLM_CBF_ */
	पूर्णांक			sb_status;	/* copy to lksb status */
	uपूर्णांक8_t			sb_flags;	/* copy to lksb flags */
	पूर्णांक8_t			mode; /* rq mode of bast, gr mode of cast */
पूर्ण;

काष्ठा dlm_lkb अणु
	काष्ठा dlm_rsb		*lkb_resource;	/* the rsb */
	काष्ठा kref		lkb_ref;
	पूर्णांक			lkb_nodeid;	/* copied from rsb */
	पूर्णांक			lkb_ownpid;	/* pid of lock owner */
	uपूर्णांक32_t		lkb_id;		/* our lock ID */
	uपूर्णांक32_t		lkb_remid;	/* lock ID on remote partner */
	uपूर्णांक32_t		lkb_exflags;	/* बाह्यal flags from caller */
	uपूर्णांक32_t		lkb_sbflags;	/* lksb flags */
	uपूर्णांक32_t		lkb_flags;	/* पूर्णांकernal flags */
	uपूर्णांक32_t		lkb_lvbseq;	/* lvb sequence number */

	पूर्णांक8_t			lkb_status;     /* granted, रुकोing, convert */
	पूर्णांक8_t			lkb_rqmode;	/* requested lock mode */
	पूर्णांक8_t			lkb_grmode;	/* granted lock mode */
	पूर्णांक8_t			lkb_highbast;	/* highest mode bast sent क्रम */

	पूर्णांक8_t			lkb_रुको_type;	/* type of reply रुकोing क्रम */
	पूर्णांक8_t			lkb_रुको_count;
	पूर्णांक			lkb_रुको_nodeid; /* क्रम debugging */

	काष्ठा list_head	lkb_statequeue;	/* rsb g/c/w list */
	काष्ठा list_head	lkb_rsb_lookup;	/* रुकोing क्रम rsb lookup */
	काष्ठा list_head	lkb_रुको_reply;	/* रुकोing क्रम remote reply */
	काष्ठा list_head	lkb_ownqueue;	/* list of locks क्रम a process */
	काष्ठा list_head	lkb_समय_list;
	kसमय_प्रकार			lkb_बारtamp;
	kसमय_प्रकार			lkb_रुको_समय;
	अचिन्हित दीर्घ		lkb_समयout_cs;

	काष्ठा mutex		lkb_cb_mutex;
	काष्ठा work_काष्ठा	lkb_cb_work;
	काष्ठा list_head	lkb_cb_list; /* क्रम ls_cb_delay or proc->asts */
	काष्ठा dlm_callback	lkb_callbacks[DLM_CALLBACKS_SIZE];
	काष्ठा dlm_callback	lkb_last_cast;
	काष्ठा dlm_callback	lkb_last_bast;
	kसमय_प्रकार			lkb_last_cast_समय;	/* क्रम debugging */
	kसमय_प्रकार			lkb_last_bast_समय;	/* क्रम debugging */

	uपूर्णांक64_t		lkb_recover_seq; /* from ls_recover_seq */

	अक्षर			*lkb_lvbptr;
	काष्ठा dlm_lksb		*lkb_lksb;      /* caller's status block */
	व्योम			(*lkb_astfn) (व्योम *astparam);
	व्योम			(*lkb_bastfn) (व्योम *astparam, पूर्णांक mode);
	जोड़ अणु
		व्योम			*lkb_astparam;	/* caller's ast arg */
		काष्ठा dlm_user_args	*lkb_ua;
	पूर्ण;
पूर्ण;

/*
 * res_master_nodeid is "normal": 0 is unset/invalid, non-zero is the real
 * nodeid, even when nodeid is our_nodeid.
 *
 * res_nodeid is "odd": -1 is unset/invalid, zero means our_nodeid,
 * greater than zero when another nodeid.
 *
 * (TODO: हटाओ res_nodeid and only use res_master_nodeid)
 */

काष्ठा dlm_rsb अणु
	काष्ठा dlm_ls		*res_ls;	/* the lockspace */
	काष्ठा kref		res_ref;
	काष्ठा mutex		res_mutex;
	अचिन्हित दीर्घ		res_flags;
	पूर्णांक			res_length;	/* length of rsb name */
	पूर्णांक			res_nodeid;
	पूर्णांक			res_master_nodeid;
	पूर्णांक			res_dir_nodeid;
	पूर्णांक			res_id;		/* क्रम ls_recover_idr */
	uपूर्णांक32_t                res_lvbseq;
	uपूर्णांक32_t		res_hash;
	uपूर्णांक32_t		res_bucket;	/* rsbtbl */
	अचिन्हित दीर्घ		res_toss_समय;
	uपूर्णांक32_t		res_first_lkid;
	काष्ठा list_head	res_lookup;	/* lkbs रुकोing on first */
	जोड़ अणु
		काष्ठा list_head	res_hashchain;
		काष्ठा rb_node		res_hashnode;	/* rsbtbl */
	पूर्ण;
	काष्ठा list_head	res_grantqueue;
	काष्ठा list_head	res_convertqueue;
	काष्ठा list_head	res_रुकोqueue;

	काष्ठा list_head	res_root_list;	    /* used क्रम recovery */
	काष्ठा list_head	res_recover_list;   /* used क्रम recovery */
	पूर्णांक			res_recover_locks_count;

	अक्षर			*res_lvbptr;
	अक्षर			res_name[DLM_RESNAME_MAXLEN+1];
पूर्ण;

/* dlm_master_lookup() flags */

#घोषणा DLM_LU_RECOVER_सूची	1
#घोषणा DLM_LU_RECOVER_MASTER	2

/* dlm_master_lookup() results */

#घोषणा DLM_LU_MATCH		1
#घोषणा DLM_LU_ADD		2

/* find_rsb() flags */

#घोषणा R_REQUEST		0x00000001
#घोषणा R_RECEIVE_REQUEST	0x00000002
#घोषणा R_RECEIVE_RECOVER	0x00000004

/* rsb_flags */

क्रमागत rsb_flags अणु
	RSB_MASTER_UNCERTAIN,
	RSB_VALNOTVALID,
	RSB_VALNOTVALID_PREV,
	RSB_NEW_MASTER,
	RSB_NEW_MASTER2,
	RSB_RECOVER_CONVERT,
	RSB_RECOVER_GRANT,
	RSB_RECOVER_LVB_INVAL,
पूर्ण;

अटल अंतरभूत व्योम rsb_set_flag(काष्ठा dlm_rsb *r, क्रमागत rsb_flags flag)
अणु
	__set_bit(flag, &r->res_flags);
पूर्ण

अटल अंतरभूत व्योम rsb_clear_flag(काष्ठा dlm_rsb *r, क्रमागत rsb_flags flag)
अणु
	__clear_bit(flag, &r->res_flags);
पूर्ण

अटल अंतरभूत पूर्णांक rsb_flag(काष्ठा dlm_rsb *r, क्रमागत rsb_flags flag)
अणु
	वापस test_bit(flag, &r->res_flags);
पूर्ण


/* dlm_header is first element of all काष्ठाs sent between nodes */

#घोषणा DLM_HEADER_MAJOR	0x00030000
#घोषणा DLM_HEADER_MINOR	0x00000001

#घोषणा DLM_HEADER_SLOTS	0x00000001

#घोषणा DLM_MSG			1
#घोषणा DLM_RCOM		2

काष्ठा dlm_header अणु
	uपूर्णांक32_t		h_version;
	uपूर्णांक32_t		h_lockspace;
	uपूर्णांक32_t		h_nodeid;	/* nodeid of sender */
	uपूर्णांक16_t		h_length;
	uपूर्णांक8_t			h_cmd;		/* DLM_MSG, DLM_RCOM */
	uपूर्णांक8_t			h_pad;
पूर्ण;


#घोषणा DLM_MSG_REQUEST		1
#घोषणा DLM_MSG_CONVERT		2
#घोषणा DLM_MSG_UNLOCK		3
#घोषणा DLM_MSG_CANCEL		4
#घोषणा DLM_MSG_REQUEST_REPLY	5
#घोषणा DLM_MSG_CONVERT_REPLY	6
#घोषणा DLM_MSG_UNLOCK_REPLY	7
#घोषणा DLM_MSG_CANCEL_REPLY	8
#घोषणा DLM_MSG_GRANT		9
#घोषणा DLM_MSG_BAST		10
#घोषणा DLM_MSG_LOOKUP		11
#घोषणा DLM_MSG_REMOVE		12
#घोषणा DLM_MSG_LOOKUP_REPLY	13
#घोषणा DLM_MSG_PURGE		14

काष्ठा dlm_message अणु
	काष्ठा dlm_header	m_header;
	uपूर्णांक32_t		m_type;		/* DLM_MSG_ */
	uपूर्णांक32_t		m_nodeid;
	uपूर्णांक32_t		m_pid;
	uपूर्णांक32_t		m_lkid;		/* lkid on sender */
	uपूर्णांक32_t		m_remid;	/* lkid on receiver */
	uपूर्णांक32_t		m_parent_lkid;
	uपूर्णांक32_t		m_parent_remid;
	uपूर्णांक32_t		m_exflags;
	uपूर्णांक32_t		m_sbflags;
	uपूर्णांक32_t		m_flags;
	uपूर्णांक32_t		m_lvbseq;
	uपूर्णांक32_t		m_hash;
	पूर्णांक			m_status;
	पूर्णांक			m_grmode;
	पूर्णांक			m_rqmode;
	पूर्णांक			m_basपंचांगode;
	पूर्णांक			m_asts;
	पूर्णांक			m_result;	/* 0 or -EXXX */
	अक्षर			m_extra[];	/* name or lvb */
पूर्ण;


#घोषणा DLM_RS_NODES		0x00000001
#घोषणा DLM_RS_NODES_ALL	0x00000002
#घोषणा DLM_RS_सूची		0x00000004
#घोषणा DLM_RS_सूची_ALL		0x00000008
#घोषणा DLM_RS_LOCKS		0x00000010
#घोषणा DLM_RS_LOCKS_ALL	0x00000020
#घोषणा DLM_RS_DONE		0x00000040
#घोषणा DLM_RS_DONE_ALL		0x00000080

#घोषणा DLM_RCOM_STATUS		1
#घोषणा DLM_RCOM_NAMES		2
#घोषणा DLM_RCOM_LOOKUP		3
#घोषणा DLM_RCOM_LOCK		4
#घोषणा DLM_RCOM_STATUS_REPLY	5
#घोषणा DLM_RCOM_NAMES_REPLY	6
#घोषणा DLM_RCOM_LOOKUP_REPLY	7
#घोषणा DLM_RCOM_LOCK_REPLY	8

काष्ठा dlm_rcom अणु
	काष्ठा dlm_header	rc_header;
	uपूर्णांक32_t		rc_type;	/* DLM_RCOM_ */
	पूर्णांक			rc_result;	/* multi-purpose */
	uपूर्णांक64_t		rc_id;		/* match reply with request */
	uपूर्णांक64_t		rc_seq;		/* sender's ls_recover_seq */
	uपूर्णांक64_t		rc_seq_reply;	/* remote ls_recover_seq */
	अक्षर			rc_buf[];
पूर्ण;

जोड़ dlm_packet अणु
	काष्ठा dlm_header	header;		/* common to other two */
	काष्ठा dlm_message	message;
	काष्ठा dlm_rcom		rcom;
पूर्ण;

#घोषणा DLM_RSF_NEED_SLOTS	0x00000001

/* RCOM_STATUS data */
काष्ठा rcom_status अणु
	__le32			rs_flags;
	__le32			rs_unused1;
	__le64			rs_unused2;
पूर्ण;

/* RCOM_STATUS_REPLY data */
काष्ठा rcom_config अणु
	__le32			rf_lvblen;
	__le32			rf_lsflags;

	/* DLM_HEADER_SLOTS adds: */
	__le32			rf_flags;
	__le16			rf_our_slot;
	__le16			rf_num_slots;
	__le32			rf_generation;
	__le32			rf_unused1;
	__le64			rf_unused2;
पूर्ण;

काष्ठा rcom_slot अणु
	__le32			ro_nodeid;
	__le16			ro_slot;
	__le16			ro_unused1;
	__le64			ro_unused2;
पूर्ण;

काष्ठा rcom_lock अणु
	__le32			rl_ownpid;
	__le32			rl_lkid;
	__le32			rl_remid;
	__le32			rl_parent_lkid;
	__le32			rl_parent_remid;
	__le32			rl_exflags;
	__le32			rl_flags;
	__le32			rl_lvbseq;
	__le32			rl_result;
	पूर्णांक8_t			rl_rqmode;
	पूर्णांक8_t			rl_grmode;
	पूर्णांक8_t			rl_status;
	पूर्णांक8_t			rl_asts;
	__le16			rl_रुको_type;
	__le16			rl_namelen;
	अक्षर			rl_name[DLM_RESNAME_MAXLEN];
	अक्षर			rl_lvb[];
पूर्ण;

/*
 * The max number of resources per rsbtbl bucket that shrink will attempt
 * to हटाओ in each iteration.
 */

#घोषणा DLM_REMOVE_NAMES_MAX 8

काष्ठा dlm_ls अणु
	काष्ठा list_head	ls_list;	/* list of lockspaces */
	dlm_lockspace_t		*ls_local_handle;
	uपूर्णांक32_t		ls_global_id;	/* global unique lockspace ID */
	uपूर्णांक32_t		ls_generation;
	uपूर्णांक32_t		ls_exflags;
	पूर्णांक			ls_lvblen;
	पूर्णांक			ls_count;	/* refcount of processes in
						   the dlm using this ls */
	पूर्णांक			ls_create_count; /* create/release refcount */
	अचिन्हित दीर्घ		ls_flags;	/* LSFL_ */
	अचिन्हित दीर्घ		ls_scan_समय;
	काष्ठा kobject		ls_kobj;

	काष्ठा idr		ls_lkbidr;
	spinlock_t		ls_lkbidr_spin;

	काष्ठा dlm_rsbtable	*ls_rsbtbl;
	uपूर्णांक32_t		ls_rsbtbl_size;

	काष्ठा mutex		ls_रुकोers_mutex;
	काष्ठा list_head	ls_रुकोers;	/* lkbs needing a reply */

	काष्ठा mutex		ls_orphans_mutex;
	काष्ठा list_head	ls_orphans;

	काष्ठा mutex		ls_समयout_mutex;
	काष्ठा list_head	ls_समयout;

	spinlock_t		ls_new_rsb_spin;
	पूर्णांक			ls_new_rsb_count;
	काष्ठा list_head	ls_new_rsb;	/* new rsb काष्ठाs */

	spinlock_t		ls_हटाओ_spin;
	अक्षर			ls_हटाओ_name[DLM_RESNAME_MAXLEN+1];
	अक्षर			*ls_हटाओ_names[DLM_REMOVE_NAMES_MAX];
	पूर्णांक			ls_हटाओ_len;
	पूर्णांक			ls_हटाओ_lens[DLM_REMOVE_NAMES_MAX];

	काष्ठा list_head	ls_nodes;	/* current nodes in ls */
	काष्ठा list_head	ls_nodes_gone;	/* dead node list, recovery */
	पूर्णांक			ls_num_nodes;	/* number of nodes in ls */
	पूर्णांक			ls_low_nodeid;
	पूर्णांक			ls_total_weight;
	पूर्णांक			*ls_node_array;

	पूर्णांक			ls_slot;
	पूर्णांक			ls_num_slots;
	पूर्णांक			ls_slots_size;
	काष्ठा dlm_slot		*ls_slots;

	काष्ठा dlm_rsb		ls_stub_rsb;	/* क्रम वापसing errors */
	काष्ठा dlm_lkb		ls_stub_lkb;	/* क्रम वापसing errors */
	काष्ठा dlm_message	ls_stub_ms;	/* क्रम faking a reply */

	काष्ठा dentry		*ls_debug_rsb_dentry; /* debugfs */
	काष्ठा dentry		*ls_debug_रुकोers_dentry; /* debugfs */
	काष्ठा dentry		*ls_debug_locks_dentry; /* debugfs */
	काष्ठा dentry		*ls_debug_all_dentry; /* debugfs */
	काष्ठा dentry		*ls_debug_toss_dentry; /* debugfs */

	रुको_queue_head_t	ls_uevent_रुको;	/* user part of join/leave */
	पूर्णांक			ls_uevent_result;
	काष्ठा completion	ls_members_करोne;
	पूर्णांक			ls_members_result;

	काष्ठा miscdevice       ls_device;

	काष्ठा workqueue_काष्ठा	*ls_callback_wq;

	/* recovery related */

	काष्ठा mutex		ls_cb_mutex;
	काष्ठा list_head	ls_cb_delay; /* save क्रम queue_work later */
	काष्ठा समयr_list	ls_समयr;
	काष्ठा task_काष्ठा	*ls_recoverd_task;
	काष्ठा mutex		ls_recoverd_active;
	spinlock_t		ls_recover_lock;
	अचिन्हित दीर्घ		ls_recover_begin; /* jअगरfies बारtamp */
	uपूर्णांक32_t		ls_recover_status; /* DLM_RS_ */
	uपूर्णांक64_t		ls_recover_seq;
	काष्ठा dlm_recover	*ls_recover_args;
	काष्ठा rw_semaphore	ls_in_recovery;	/* block local requests */
	काष्ठा rw_semaphore	ls_recv_active;	/* block dlm_recv */
	काष्ठा list_head	ls_requestqueue;/* queue remote requests */
	काष्ठा mutex		ls_requestqueue_mutex;
	काष्ठा dlm_rcom		*ls_recover_buf;
	पूर्णांक			ls_recover_nodeid; /* क्रम debugging */
	अचिन्हित पूर्णांक		ls_recover_dir_sent_res; /* क्रम log info */
	अचिन्हित पूर्णांक		ls_recover_dir_sent_msg; /* क्रम log info */
	अचिन्हित पूर्णांक		ls_recover_locks_in; /* क्रम log info */
	uपूर्णांक64_t		ls_rcom_seq;
	spinlock_t		ls_rcom_spin;
	काष्ठा list_head	ls_recover_list;
	spinlock_t		ls_recover_list_lock;
	पूर्णांक			ls_recover_list_count;
	काष्ठा idr		ls_recover_idr;
	spinlock_t		ls_recover_idr_lock;
	रुको_queue_head_t	ls_रुको_general;
	रुको_queue_head_t	ls_recover_lock_रुको;
	काष्ठा mutex		ls_clear_proc_locks;

	काष्ठा list_head	ls_root_list;	/* root resources */
	काष्ठा rw_semaphore	ls_root_sem;	/* protect root_list */

	स्थिर काष्ठा dlm_lockspace_ops *ls_ops;
	व्योम			*ls_ops_arg;

	पूर्णांक			ls_namelen;
	अक्षर			ls_name[1];
पूर्ण;

/*
 * LSFL_RECOVER_STOP - dlm_ls_stop() sets this to tell dlm recovery routines
 * that they should पात what they're करोing so new recovery can be started.
 *
 * LSFL_RECOVER_DOWN - dlm_ls_stop() sets this to tell dlm_recoverd that it
 * should करो करोwn_ग_लिखो() on the in_recovery rw_semaphore. (करोing करोwn_ग_लिखो
 * within dlm_ls_stop causes complaपूर्णांकs about the lock acquired/released
 * in dअगरferent contexts.)
 *
 * LSFL_RECOVER_LOCK - dlm_recoverd holds the in_recovery rw_semaphore.
 * It sets this after it is करोne with करोwn_ग_लिखो() on the in_recovery
 * rw_semaphore and clears it after it has released the rw_semaphore.
 *
 * LSFL_RECOVER_WORK - dlm_ls_start() sets this to tell dlm_recoverd that it
 * should begin recovery of the lockspace.
 *
 * LSFL_RUNNING - set when normal locking activity is enabled.
 * dlm_ls_stop() clears this to tell dlm locking routines that they should
 * quit what they are करोing so recovery can run.  dlm_recoverd sets
 * this after recovery is finished.
 */

#घोषणा LSFL_RECOVER_STOP	0
#घोषणा LSFL_RECOVER_DOWN	1
#घोषणा LSFL_RECOVER_LOCK	2
#घोषणा LSFL_RECOVER_WORK	3
#घोषणा LSFL_RUNNING		4

#घोषणा LSFL_RCOM_READY		5
#घोषणा LSFL_RCOM_WAIT		6
#घोषणा LSFL_UEVENT_WAIT	7
#घोषणा LSFL_TIMEWARN		8
#घोषणा LSFL_CB_DELAY		9
#घोषणा LSFL_NOसूची		10

/* much of this is just saving user space poपूर्णांकers associated with the
   lock that we pass back to the user lib with an ast */

काष्ठा dlm_user_args अणु
	काष्ठा dlm_user_proc	*proc; /* each process that खोलोs the lockspace
					  device has निजी data
					  (dlm_user_proc) on the काष्ठा file,
					  the process's locks poपूर्णांक back to it*/
	काष्ठा dlm_lksb		lksb;
	काष्ठा dlm_lksb __user	*user_lksb;
	व्योम __user		*castparam;
	व्योम __user		*castaddr;
	व्योम __user		*bastparam;
	व्योम __user		*bastaddr;
	uपूर्णांक64_t		xid;
पूर्ण;

#घोषणा DLM_PROC_FLAGS_CLOSING 1
#घोषणा DLM_PROC_FLAGS_COMPAT  2

/* locks list is kept so we can हटाओ all a process's locks when it
   निकासs (or orphan those that are persistent) */

काष्ठा dlm_user_proc अणु
	dlm_lockspace_t		*lockspace;
	अचिन्हित दीर्घ		flags; /* DLM_PROC_FLAGS */
	काष्ठा list_head	asts;
	spinlock_t		asts_spin;
	काष्ठा list_head	locks;
	spinlock_t		locks_spin;
	काष्ठा list_head	unlocking;
	रुको_queue_head_t	रुको;
पूर्ण;

अटल अंतरभूत पूर्णांक dlm_locking_stopped(काष्ठा dlm_ls *ls)
अणु
	वापस !test_bit(LSFL_RUNNING, &ls->ls_flags);
पूर्ण

अटल अंतरभूत पूर्णांक dlm_recovery_stopped(काष्ठा dlm_ls *ls)
अणु
	वापस test_bit(LSFL_RECOVER_STOP, &ls->ls_flags);
पूर्ण

अटल अंतरभूत पूर्णांक dlm_no_directory(काष्ठा dlm_ls *ls)
अणु
	वापस test_bit(LSFL_NOसूची, &ls->ls_flags);
पूर्ण

पूर्णांक dlm_netlink_init(व्योम);
व्योम dlm_netlink_निकास(व्योम);
व्योम dlm_समयout_warn(काष्ठा dlm_lkb *lkb);
पूर्णांक dlm_plock_init(व्योम);
व्योम dlm_plock_निकास(व्योम);

#अगर_घोषित CONFIG_DLM_DEBUG
व्योम dlm_रेजिस्टर_debugfs(व्योम);
व्योम dlm_unरेजिस्टर_debugfs(व्योम);
व्योम dlm_create_debug_file(काष्ठा dlm_ls *ls);
व्योम dlm_delete_debug_file(काष्ठा dlm_ls *ls);
#अन्यथा
अटल अंतरभूत व्योम dlm_रेजिस्टर_debugfs(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम dlm_unरेजिस्टर_debugfs(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम dlm_create_debug_file(काष्ठा dlm_ls *ls) अणु पूर्ण
अटल अंतरभूत व्योम dlm_delete_debug_file(काष्ठा dlm_ls *ls) अणु पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर				/* __DLM_INTERNAL_DOT_H__ */

