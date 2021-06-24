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
#अगर_अघोषित __DLM_DOT_H__
#घोषणा __DLM_DOT_H__

#समावेश <uapi/linux/dlm.h>


काष्ठा dlm_slot अणु
	पूर्णांक nodeid; /* 1 to MAX_INT */
	पूर्णांक slot;   /* 1 to MAX_INT */
पूर्ण;

/*
 * recover_prep: called beक्रमe the dlm begins lock recovery.
 *   Notfies lockspace user that locks from failed members will be granted.
 * recover_slot: called after recover_prep and beक्रमe recover_करोne.
 *   Identअगरies a failed lockspace member.
 * recover_करोne: called after the dlm completes lock recovery.
 *   Identअगरies lockspace members and lockspace generation number.
 */

काष्ठा dlm_lockspace_ops अणु
	व्योम (*recover_prep) (व्योम *ops_arg);
	व्योम (*recover_slot) (व्योम *ops_arg, काष्ठा dlm_slot *slot);
	व्योम (*recover_करोne) (व्योम *ops_arg, काष्ठा dlm_slot *slots,
			      पूर्णांक num_slots, पूर्णांक our_slot, uपूर्णांक32_t generation);
पूर्ण;

/*
 * dlm_new_lockspace
 *
 * Create/join a lockspace.
 *
 * name: lockspace name, null terminated, up to DLM_LOCKSPACE_LEN (not
 *   including terminating null).
 *
 * cluster: cluster name, null terminated, up to DLM_LOCKSPACE_LEN (not
 *   including terminating null).  Optional.  When cluster is null, it
 *   is not used.  When set, dlm_new_lockspace() वापसs -EBADR अगर cluster
 *   is not equal to the dlm cluster name.
 *
 * flags:
 * DLM_LSFL_NOसूची
 *   The dlm should not use a resource directory, but अटलally assign
 *   resource mastery to nodes based on the name hash that is otherwise
 *   used to select the directory node.  Must be the same on all nodes.
 * DLM_LSFL_TIMEWARN
 *   The dlm should emit netlink messages अगर locks have been रुकोing
 *   क्रम a configurable amount of समय.  (Unused.)
 * DLM_LSFL_FS
 *   The lockspace user is in the kernel (i.e. fileप्रणाली).  Enables
 *   direct bast/cast callbacks.
 * DLM_LSFL_NEWEXCL
 *   dlm_new_lockspace() should वापस -EEXIST अगर the lockspace exists.
 *
 * lvblen: length of lvb in bytes.  Must be multiple of 8.
 *   dlm_new_lockspace() वापसs an error अगर this करोes not match
 *   what other nodes are using.
 *
 * ops: callbacks that indicate lockspace recovery poपूर्णांकs so the
 *   caller can coordinate its recovery and know lockspace members.
 *   This is only used by the initial dlm_new_lockspace() call.
 *   Optional.
 *
 * ops_arg: arg क्रम ops callbacks.
 *
 * ops_result: tells caller अगर the ops callbacks (अगर provided) will
 *   be used or not.  0: will be used, -EXXX will not be used.
 *   -EOPNOTSUPP: the dlm करोes not have recovery_callbacks enabled.
 *
 * lockspace: handle क्रम dlm functions
 */

पूर्णांक dlm_new_lockspace(स्थिर अक्षर *name, स्थिर अक्षर *cluster,
		      uपूर्णांक32_t flags, पूर्णांक lvblen,
		      स्थिर काष्ठा dlm_lockspace_ops *ops, व्योम *ops_arg,
		      पूर्णांक *ops_result, dlm_lockspace_t **lockspace);

/*
 * dlm_release_lockspace
 *
 * Stop a lockspace.
 */

पूर्णांक dlm_release_lockspace(dlm_lockspace_t *lockspace, पूर्णांक क्रमce);

/*
 * dlm_lock
 *
 * Make an asynchronous request to acquire or convert a lock on a named
 * resource.
 *
 * lockspace: context क्रम the request
 * mode: the requested mode of the lock (DLM_LOCK_)
 * lksb: lock status block क्रम input and async वापस values
 * flags: input flags (DLM_LKF_)
 * name: name of the resource to lock, can be binary
 * namelen: the length in bytes of the resource name (MAX_RESNAME_LEN)
 * parent: the lock ID of a parent lock or 0 अगर none
 * lockast: function DLM executes when it completes processing the request
 * astarg: argument passed to lockast and bast functions
 * bast: function DLM executes when this lock later blocks another request
 *
 * Returns:
 * 0 अगर request is successfully queued क्रम processing
 * -EINVAL अगर any input parameters are invalid
 * -EAGAIN अगर request would block and is flagged DLM_LKF_NOQUEUE
 * -ENOMEM अगर there is no memory to process request
 * -ENOTCONN अगर there is a communication error
 *
 * If the call to dlm_lock वापसs an error then the operation has failed and
 * the AST routine will not be called.  If dlm_lock वापसs 0 it is still
 * possible that the lock operation will fail. The AST routine will be called
 * when the locking is complete and the status is वापसed in the lksb.
 *
 * If the AST routines or parameter are passed to a conversion operation then
 * they will overग_लिखो those values that were passed to a previous dlm_lock
 * call.
 *
 * AST routines should not block (at least not क्रम दीर्घ), but may make
 * any locking calls they please.
 */

पूर्णांक dlm_lock(dlm_lockspace_t *lockspace,
	     पूर्णांक mode,
	     काष्ठा dlm_lksb *lksb,
	     uपूर्णांक32_t flags,
	     व्योम *name,
	     अचिन्हित पूर्णांक namelen,
	     uपूर्णांक32_t parent_lkid,
	     व्योम (*lockast) (व्योम *astarg),
	     व्योम *astarg,
	     व्योम (*bast) (व्योम *astarg, पूर्णांक mode));

/*
 * dlm_unlock
 *
 * Asynchronously release a lock on a resource.  The AST routine is called
 * when the resource is successfully unlocked.
 *
 * lockspace: context क्रम the request
 * lkid: the lock ID as वापसed in the lksb
 * flags: input flags (DLM_LKF_)
 * lksb: अगर शून्य the lksb parameter passed to last lock request is used
 * astarg: the arg used with the completion ast क्रम the unlock
 *
 * Returns:
 * 0 अगर request is successfully queued क्रम processing
 * -EINVAL अगर any input parameters are invalid
 * -ENOTEMPTY अगर the lock still has sublocks
 * -EBUSY अगर the lock is रुकोing क्रम a remote lock operation
 * -ENOTCONN अगर there is a communication error
 */

पूर्णांक dlm_unlock(dlm_lockspace_t *lockspace,
	       uपूर्णांक32_t lkid,
	       uपूर्णांक32_t flags,
	       काष्ठा dlm_lksb *lksb,
	       व्योम *astarg);

#पूर्ण_अगर				/* __DLM_DOT_H__ */
