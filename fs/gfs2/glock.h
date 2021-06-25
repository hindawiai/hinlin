<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) Sistina Software, Inc.  1997-2003 All rights reserved.
 * Copyright (C) 2004-2006 Red Hat, Inc.  All rights reserved.
 */

#अगर_अघोषित __GLOCK_DOT_H__
#घोषणा __GLOCK_DOT_H__

#समावेश <linux/sched.h>
#समावेश <linux/parser.h>
#समावेश "incore.h"
#समावेश "util.h"

/* Options क्रम hostdata parser */

क्रमागत अणु
	Opt_jid,
	Opt_id,
	Opt_first,
	Opt_nodir,
	Opt_err,
पूर्ण;

/*
 * lm_lockname types
 */

#घोषणा LM_TYPE_RESERVED	0x00
#घोषणा LM_TYPE_NONDISK		0x01
#घोषणा LM_TYPE_INODE		0x02
#घोषणा LM_TYPE_RGRP		0x03
#घोषणा LM_TYPE_META		0x04
#घोषणा LM_TYPE_IOPEN		0x05
#घोषणा LM_TYPE_FLOCK		0x06
#घोषणा LM_TYPE_PLOCK		0x07
#घोषणा LM_TYPE_QUOTA		0x08
#घोषणा LM_TYPE_JOURNAL		0x09

/*
 * lm_lock() states
 *
 * SHARED is compatible with SHARED, not with DEFERRED or EX.
 * DEFERRED is compatible with DEFERRED, not with SHARED or EX.
 */

#घोषणा LM_ST_UNLOCKED		0
#घोषणा LM_ST_EXCLUSIVE		1
#घोषणा LM_ST_DEFERRED		2
#घोषणा LM_ST_SHARED		3

/*
 * lm_lock() flags
 *
 * LM_FLAG_TRY
 * Don't wait to acquire the lock if it can't be granted immediately.
 *
 * LM_FLAG_TRY_1CB
 * Send one blocking callback अगर TRY is set and the lock is not granted.
 *
 * LM_FLAG_NOEXP
 * GFS sets this flag on lock requests it makes जबतक करोing journal recovery.
 * These special requests should not be blocked due to the recovery like
 * ordinary locks would be.
 *
 * LM_FLAG_ANY
 * A SHARED request may also be granted in DEFERRED, or a DEFERRED request may
 * also be granted in SHARED.  The preferred state is whichever is compatible
 * with other granted locks, or the specअगरied state अगर no other locks exist.
 *
 * LM_FLAG_PRIORITY
 * Override fairness considerations.  Suppose a lock is held in a shared state
 * and there is a pending request क्रम the deferred state.  A shared lock
 * request with the priority flag would be allowed to bypass the deferred
 * request and directly join the other shared lock.  A shared lock request
 * without the priority flag might be क्रमced to रुको until the deferred
 * requested had acquired and released the lock.
 *
 * LM_FLAG_NODE_SCOPE
 * This holder agrees to share the lock within this node. In other words,
 * the glock is held in EX mode according to DLM, but local holders on the
 * same node can share it.
 */

#घोषणा LM_FLAG_TRY		0x0001
#घोषणा LM_FLAG_TRY_1CB		0x0002
#घोषणा LM_FLAG_NOEXP		0x0004
#घोषणा LM_FLAG_ANY		0x0008
#घोषणा LM_FLAG_PRIORITY	0x0010
#घोषणा LM_FLAG_NODE_SCOPE	0x0020
#घोषणा GL_ASYNC		0x0040
#घोषणा GL_EXACT		0x0080
#घोषणा GL_SKIP			0x0100
#घोषणा GL_NOCACHE		0x0400
  
/*
 * lm_async_cb वापस flags
 *
 * LM_OUT_ST_MASK
 * Masks the lower two bits of lock state in the वापसed value.
 *
 * LM_OUT_CANCELED
 * The lock request was canceled.
 *
 */

#घोषणा LM_OUT_ST_MASK		0x00000003
#घोषणा LM_OUT_CANCELED		0x00000008
#घोषणा LM_OUT_ERROR		0x00000004

/*
 * lm_recovery_करोne() messages
 */

#घोषणा LM_RD_GAVEUP		308
#घोषणा LM_RD_SUCCESS		309

#घोषणा GLR_TRYFAILED		13

#घोषणा GL_GLOCK_MAX_HOLD        (दीर्घ)(HZ / 5)
#घोषणा GL_GLOCK_DFT_HOLD        (दीर्घ)(HZ / 5)
#घोषणा GL_GLOCK_MIN_HOLD        (दीर्घ)(10)
#घोषणा GL_GLOCK_HOLD_INCR       (दीर्घ)(HZ / 20)
#घोषणा GL_GLOCK_HOLD_DECR       (दीर्घ)(HZ / 40)

काष्ठा lm_lockops अणु
	स्थिर अक्षर *lm_proto_name;
	पूर्णांक (*lm_mount) (काष्ठा gfs2_sbd *sdp, स्थिर अक्षर *table);
	व्योम (*lm_first_करोne) (काष्ठा gfs2_sbd *sdp);
	व्योम (*lm_recovery_result) (काष्ठा gfs2_sbd *sdp, अचिन्हित पूर्णांक jid,
				    अचिन्हित पूर्णांक result);
	व्योम (*lm_unmount) (काष्ठा gfs2_sbd *sdp);
	व्योम (*lm_withdraw) (काष्ठा gfs2_sbd *sdp);
	व्योम (*lm_put_lock) (काष्ठा gfs2_glock *gl);
	पूर्णांक (*lm_lock) (काष्ठा gfs2_glock *gl, अचिन्हित पूर्णांक req_state,
			अचिन्हित पूर्णांक flags);
	व्योम (*lm_cancel) (काष्ठा gfs2_glock *gl);
	स्थिर match_table_t *lm_tokens;
पूर्ण;

बाह्य काष्ठा workqueue_काष्ठा *gfs2_delete_workqueue;
अटल अंतरभूत काष्ठा gfs2_holder *gfs2_glock_is_locked_by_me(काष्ठा gfs2_glock *gl)
अणु
	काष्ठा gfs2_holder *gh;
	काष्ठा pid *pid;

	/* Look in glock's list of holders क्रम one with current task as owner */
	spin_lock(&gl->gl_lockref.lock);
	pid = task_pid(current);
	list_क्रम_each_entry(gh, &gl->gl_holders, gh_list) अणु
		अगर (!test_bit(HIF_HOLDER, &gh->gh_अगरlags))
			अवरोध;
		अगर (gh->gh_owner_pid == pid)
			जाओ out;
	पूर्ण
	gh = शून्य;
out:
	spin_unlock(&gl->gl_lockref.lock);

	वापस gh;
पूर्ण

अटल अंतरभूत पूर्णांक gfs2_glock_is_held_excl(काष्ठा gfs2_glock *gl)
अणु
	वापस gl->gl_state == LM_ST_EXCLUSIVE;
पूर्ण

अटल अंतरभूत पूर्णांक gfs2_glock_is_held_dfrd(काष्ठा gfs2_glock *gl)
अणु
	वापस gl->gl_state == LM_ST_DEFERRED;
पूर्ण

अटल अंतरभूत पूर्णांक gfs2_glock_is_held_shrd(काष्ठा gfs2_glock *gl)
अणु
	वापस gl->gl_state == LM_ST_SHARED;
पूर्ण

अटल अंतरभूत काष्ठा address_space *gfs2_glock2aspace(काष्ठा gfs2_glock *gl)
अणु
	अगर (gl->gl_ops->go_flags & GLOF_ASPACE)
		वापस (काष्ठा address_space *)(gl + 1);
	वापस शून्य;
पूर्ण

बाह्य पूर्णांक gfs2_glock_get(काष्ठा gfs2_sbd *sdp, u64 number,
			  स्थिर काष्ठा gfs2_glock_operations *glops,
			  पूर्णांक create, काष्ठा gfs2_glock **glp);
बाह्य व्योम gfs2_glock_hold(काष्ठा gfs2_glock *gl);
बाह्य व्योम gfs2_glock_put(काष्ठा gfs2_glock *gl);
बाह्य व्योम gfs2_glock_queue_put(काष्ठा gfs2_glock *gl);
बाह्य व्योम gfs2_holder_init(काष्ठा gfs2_glock *gl, अचिन्हित पूर्णांक state,
			     u16 flags, काष्ठा gfs2_holder *gh);
बाह्य व्योम gfs2_holder_reinit(अचिन्हित पूर्णांक state, u16 flags,
			       काष्ठा gfs2_holder *gh);
बाह्य व्योम gfs2_holder_uninit(काष्ठा gfs2_holder *gh);
बाह्य पूर्णांक gfs2_glock_nq(काष्ठा gfs2_holder *gh);
बाह्य पूर्णांक gfs2_glock_poll(काष्ठा gfs2_holder *gh);
बाह्य पूर्णांक gfs2_glock_रुको(काष्ठा gfs2_holder *gh);
बाह्य पूर्णांक gfs2_glock_async_रुको(अचिन्हित पूर्णांक num_gh, काष्ठा gfs2_holder *ghs);
बाह्य व्योम gfs2_glock_dq(काष्ठा gfs2_holder *gh);
बाह्य व्योम gfs2_glock_dq_रुको(काष्ठा gfs2_holder *gh);
बाह्य व्योम gfs2_glock_dq_uninit(काष्ठा gfs2_holder *gh);
बाह्य पूर्णांक gfs2_glock_nq_num(काष्ठा gfs2_sbd *sdp, u64 number,
			     स्थिर काष्ठा gfs2_glock_operations *glops,
			     अचिन्हित पूर्णांक state, u16 flags,
			     काष्ठा gfs2_holder *gh);
बाह्य पूर्णांक gfs2_glock_nq_m(अचिन्हित पूर्णांक num_gh, काष्ठा gfs2_holder *ghs);
बाह्य व्योम gfs2_glock_dq_m(अचिन्हित पूर्णांक num_gh, काष्ठा gfs2_holder *ghs);
बाह्य व्योम gfs2_dump_glock(काष्ठा seq_file *seq, काष्ठा gfs2_glock *gl,
			    bool fsid);
#घोषणा GLOCK_BUG_ON(gl,x) करो अणु अगर (unlikely(x)) अणु		\
			gfs2_dump_glock(शून्य, gl, true);	\
			BUG(); पूर्ण पूर्ण जबतक(0)
#घोषणा gfs2_glock_निश्चित_warn(gl, x) करो अणु अगर (unlikely(!(x))) अणु	\
			gfs2_dump_glock(शून्य, gl, true);		\
			gfs2_निश्चित_warn((gl)->gl_name.ln_sbd, (x)); पूर्ण पूर्ण \
	जबतक (0)
#घोषणा gfs2_glock_निश्चित_withdraw(gl, x) करो अणु अगर (unlikely(!(x))) अणु	\
			gfs2_dump_glock(शून्य, gl, true);		\
			gfs2_निश्चित_withdraw((gl)->gl_name.ln_sbd, (x)); पूर्ण पूर्ण \
	जबतक (0)

बाह्य __म_लिखो(2, 3)
व्योम gfs2_prपूर्णांक_dbg(काष्ठा seq_file *seq, स्थिर अक्षर *fmt, ...);

/**
 * gfs2_glock_nq_init - initialize a holder and enqueue it on a glock
 * @gl: the glock
 * @state: the state we're requesting
 * @flags: the modअगरier flags
 * @gh: the holder काष्ठाure
 *
 * Returns: 0, GLR_*, or त्रुटि_सं
 */

अटल अंतरभूत पूर्णांक gfs2_glock_nq_init(काष्ठा gfs2_glock *gl,
				     अचिन्हित पूर्णांक state, u16 flags,
				     काष्ठा gfs2_holder *gh)
अणु
	पूर्णांक error;

	gfs2_holder_init(gl, state, flags, gh);

	error = gfs2_glock_nq(gh);
	अगर (error)
		gfs2_holder_uninit(gh);

	वापस error;
पूर्ण

बाह्य व्योम gfs2_glock_cb(काष्ठा gfs2_glock *gl, अचिन्हित पूर्णांक state);
बाह्य व्योम gfs2_glock_complete(काष्ठा gfs2_glock *gl, पूर्णांक ret);
बाह्य bool gfs2_queue_delete_work(काष्ठा gfs2_glock *gl, अचिन्हित दीर्घ delay);
बाह्य व्योम gfs2_cancel_delete_work(काष्ठा gfs2_glock *gl);
बाह्य bool gfs2_delete_work_queued(स्थिर काष्ठा gfs2_glock *gl);
बाह्य व्योम gfs2_flush_delete_work(काष्ठा gfs2_sbd *sdp);
बाह्य व्योम gfs2_gl_hash_clear(काष्ठा gfs2_sbd *sdp);
बाह्य व्योम gfs2_glock_finish_truncate(काष्ठा gfs2_inode *ip);
बाह्य व्योम gfs2_glock_thaw(काष्ठा gfs2_sbd *sdp);
बाह्य व्योम gfs2_glock_add_to_lru(काष्ठा gfs2_glock *gl);
बाह्य व्योम gfs2_glock_मुक्त(काष्ठा gfs2_glock *gl);

बाह्य पूर्णांक __init gfs2_glock_init(व्योम);
बाह्य व्योम gfs2_glock_निकास(व्योम);

बाह्य व्योम gfs2_create_debugfs_file(काष्ठा gfs2_sbd *sdp);
बाह्य व्योम gfs2_delete_debugfs_file(काष्ठा gfs2_sbd *sdp);
बाह्य व्योम gfs2_रेजिस्टर_debugfs(व्योम);
बाह्य व्योम gfs2_unरेजिस्टर_debugfs(व्योम);

बाह्य स्थिर काष्ठा lm_lockops gfs2_dlm_ops;

अटल अंतरभूत व्योम gfs2_holder_mark_uninitialized(काष्ठा gfs2_holder *gh)
अणु
	gh->gh_gl = शून्य;
पूर्ण

अटल अंतरभूत bool gfs2_holder_initialized(काष्ठा gfs2_holder *gh)
अणु
	वापस gh->gh_gl;
पूर्ण

अटल अंतरभूत bool gfs2_holder_queued(काष्ठा gfs2_holder *gh)
अणु
	वापस !list_empty(&gh->gh_list);
पूर्ण

/**
 * glock_set_object - set the gl_object field of a glock
 * @gl: the glock
 * @object: the object
 */
अटल अंतरभूत व्योम glock_set_object(काष्ठा gfs2_glock *gl, व्योम *object)
अणु
	spin_lock(&gl->gl_lockref.lock);
	अगर (gfs2_निश्चित_warn(gl->gl_name.ln_sbd, gl->gl_object == शून्य))
		gfs2_dump_glock(शून्य, gl, true);
	gl->gl_object = object;
	spin_unlock(&gl->gl_lockref.lock);
पूर्ण

/**
 * glock_clear_object - clear the gl_object field of a glock
 * @gl: the glock
 * @object: the object
 *
 * I'd love to similarly add this:
 *	अन्यथा अगर (gfs2_निश्चित_warn(gl->gl_sbd, gl->gl_object == object))
 *		gfs2_dump_glock(शून्य, gl, true);
 * Unक्रमtunately, that's not possible because as soon as gfs2_delete_inode
 * मुक्तs the block in the rgrp, another process can reassign it क्रम an I_NEW
 * inode in gfs2_create_inode because that calls new_inode, not gfs2_iget.
 * That means gfs2_delete_inode may subsequently try to call this function
 * क्रम a glock that's alपढ़ोy poपूर्णांकing to a bअक्रम new inode. If we clear the
 * new inode's gl_object, we'll पूर्णांकroduce metadata corruption. Function
 * gfs2_delete_inode calls clear_inode which calls gfs2_clear_inode which also
 * tries to clear gl_object, so it's more than just gfs2_delete_inode.
 *
 */
अटल अंतरभूत व्योम glock_clear_object(काष्ठा gfs2_glock *gl, व्योम *object)
अणु
	spin_lock(&gl->gl_lockref.lock);
	अगर (gl->gl_object == object)
		gl->gl_object = शून्य;
	spin_unlock(&gl->gl_lockref.lock);
पूर्ण

बाह्य व्योम gfs2_inode_remember_delete(काष्ठा gfs2_glock *gl, u64 generation);
बाह्य bool gfs2_inode_alपढ़ोy_deleted(काष्ठा gfs2_glock *gl, u64 generation);

#पूर्ण_अगर /* __GLOCK_DOT_H__ */
