<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * userdlm.h
 *
 * Userspace dlm defines
 *
 * Copyright (C) 2002, 2004 Oracle.  All rights reserved.
 */


#अगर_अघोषित USERDLM_H
#घोषणा USERDLM_H

#समावेश <linux/module.h>
#समावेश <linux/fs.h>
#समावेश <linux/types.h>
#समावेश <linux/workqueue.h>

/* user_lock_res->l_flags flags. */
#घोषणा USER_LOCK_ATTACHED      (0x00000001) /* we have initialized
					       * the lvb */
#घोषणा USER_LOCK_BUSY          (0x00000002) /* we are currently in
					       * dlm_lock */
#घोषणा USER_LOCK_BLOCKED       (0x00000004) /* blocked रुकोing to
					      * करोwnconvert*/
#घोषणा USER_LOCK_IN_TEARDOWN   (0x00000008) /* we're currently
					      * destroying this
					      * lock. */
#घोषणा USER_LOCK_QUEUED        (0x00000010) /* lock is on the
					      * workqueue */
#घोषणा USER_LOCK_IN_CANCEL     (0x00000020)

काष्ठा user_lock_res अणु
	spinlock_t               l_lock;

	पूर्णांक                      l_flags;

#घोषणा USER_DLM_LOCK_ID_MAX_LEN  32
	अक्षर                     l_name[USER_DLM_LOCK_ID_MAX_LEN];
	पूर्णांक                      l_namelen;
	पूर्णांक                      l_level;
	अचिन्हित पूर्णांक             l_ro_holders;
	अचिन्हित पूर्णांक             l_ex_holders;
	काष्ठा ocfs2_dlm_lksb    l_lksb;

	पूर्णांक                      l_requested;
	पूर्णांक                      l_blocking;

	रुको_queue_head_t        l_event;

	काष्ठा work_काष्ठा       l_work;
पूर्ण;

बाह्य काष्ठा workqueue_काष्ठा *user_dlm_worker;

व्योम user_dlm_lock_res_init(काष्ठा user_lock_res *lockres,
			    काष्ठा dentry *dentry);
पूर्णांक user_dlm_destroy_lock(काष्ठा user_lock_res *lockres);
पूर्णांक user_dlm_cluster_lock(काष्ठा user_lock_res *lockres,
			  पूर्णांक level,
			  पूर्णांक lkm_flags);
व्योम user_dlm_cluster_unlock(काष्ठा user_lock_res *lockres,
			     पूर्णांक level);
व्योम user_dlm_ग_लिखो_lvb(काष्ठा inode *inode,
			स्थिर अक्षर *val,
			अचिन्हित पूर्णांक len);
bool user_dlm_पढ़ो_lvb(काष्ठा inode *inode, अक्षर *val);
काष्ठा ocfs2_cluster_connection *user_dlm_रेजिस्टर(स्थिर काष्ठा qstr *name);
व्योम user_dlm_unरेजिस्टर(काष्ठा ocfs2_cluster_connection *conn);
व्योम user_dlm_set_locking_protocol(व्योम);

काष्ठा dlmfs_inode_निजी अणु
	काष्ठा ocfs2_cluster_connection	*ip_conn;

	काष्ठा user_lock_res ip_lockres; /* unused क्रम directories. */
	काष्ठा inode         *ip_parent;

	काष्ठा inode         ip_vfs_inode;
पूर्ण;

अटल अंतरभूत काष्ठा dlmfs_inode_निजी *
DLMFS_I(काष्ठा inode *inode)
अणु
        वापस container_of(inode,
			    काष्ठा dlmfs_inode_निजी,
			    ip_vfs_inode);
पूर्ण

काष्ठा dlmfs_filp_निजी अणु
	पूर्णांक                  fp_lock_level;
पूर्ण;

#घोषणा DLMFS_MAGIC	0x76a9f425

#पूर्ण_अगर /* USERDLM_H */
