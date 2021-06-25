<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * eCryptfs: Linux fileप्रणाली encryption layer
 *
 * Copyright (C) 2008 International Business Machines Corp.
 *   Author(s): Michael A. Halcrow <mahalcro@us.ibm.com>
 */

#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/मुक्तzer.h>
#समावेश <linux/slab.h>
#समावेश <linux/रुको.h>
#समावेश <linux/mount.h>
#समावेश "ecryptfs_kernel.h"

काष्ठा ecryptfs_खोलो_req अणु
	काष्ठा file **lower_file;
	काष्ठा path path;
	काष्ठा completion करोne;
	काष्ठा list_head kthपढ़ो_ctl_list;
पूर्ण;

अटल काष्ठा ecryptfs_kthपढ़ो_ctl अणु
#घोषणा ECRYPTFS_KTHREAD_ZOMBIE 0x00000001
	u32 flags;
	काष्ठा mutex mux;
	काष्ठा list_head req_list;
	रुको_queue_head_t रुको;
पूर्ण ecryptfs_kthपढ़ो_ctl;

अटल काष्ठा task_काष्ठा *ecryptfs_kthपढ़ो;

/**
 * ecryptfs_thपढ़ोfn
 * @ignored: ignored
 *
 * The eCryptfs kernel thपढ़ो that has the responsibility of getting
 * the lower file with RW permissions.
 *
 * Returns zero on success; non-zero otherwise
 */
अटल पूर्णांक ecryptfs_thपढ़ोfn(व्योम *ignored)
अणु
	set_मुक्तzable();
	जबतक (1)  अणु
		काष्ठा ecryptfs_खोलो_req *req;

		रुको_event_मुक्तzable(
			ecryptfs_kthपढ़ो_ctl.रुको,
			(!list_empty(&ecryptfs_kthपढ़ो_ctl.req_list)
			 || kthपढ़ो_should_stop()));
		mutex_lock(&ecryptfs_kthपढ़ो_ctl.mux);
		अगर (ecryptfs_kthपढ़ो_ctl.flags & ECRYPTFS_KTHREAD_ZOMBIE) अणु
			mutex_unlock(&ecryptfs_kthपढ़ो_ctl.mux);
			जाओ out;
		पूर्ण
		जबतक (!list_empty(&ecryptfs_kthपढ़ो_ctl.req_list)) अणु
			req = list_first_entry(&ecryptfs_kthपढ़ो_ctl.req_list,
					       काष्ठा ecryptfs_खोलो_req,
					       kthपढ़ो_ctl_list);
			list_del(&req->kthपढ़ो_ctl_list);
			*req->lower_file = dentry_खोलो(&req->path,
				(O_RDWR | O_LARGEखाता), current_cred());
			complete(&req->करोne);
		पूर्ण
		mutex_unlock(&ecryptfs_kthपढ़ो_ctl.mux);
	पूर्ण
out:
	वापस 0;
पूर्ण

पूर्णांक __init ecryptfs_init_kthपढ़ो(व्योम)
अणु
	पूर्णांक rc = 0;

	mutex_init(&ecryptfs_kthपढ़ो_ctl.mux);
	init_रुकोqueue_head(&ecryptfs_kthपढ़ो_ctl.रुको);
	INIT_LIST_HEAD(&ecryptfs_kthपढ़ो_ctl.req_list);
	ecryptfs_kthपढ़ो = kthपढ़ो_run(&ecryptfs_thपढ़ोfn, शून्य,
				       "ecryptfs-kthread");
	अगर (IS_ERR(ecryptfs_kthपढ़ो)) अणु
		rc = PTR_ERR(ecryptfs_kthपढ़ो);
		prपूर्णांकk(KERN_ERR "%s: Failed to create kernel thread; rc = [%d]"
		       "\n", __func__, rc);
	पूर्ण
	वापस rc;
पूर्ण

व्योम ecryptfs_destroy_kthपढ़ो(व्योम)
अणु
	काष्ठा ecryptfs_खोलो_req *req, *पंचांगp;

	mutex_lock(&ecryptfs_kthपढ़ो_ctl.mux);
	ecryptfs_kthपढ़ो_ctl.flags |= ECRYPTFS_KTHREAD_ZOMBIE;
	list_क्रम_each_entry_safe(req, पंचांगp, &ecryptfs_kthपढ़ो_ctl.req_list,
				 kthपढ़ो_ctl_list) अणु
		list_del(&req->kthपढ़ो_ctl_list);
		*req->lower_file = ERR_PTR(-EIO);
		complete(&req->करोne);
	पूर्ण
	mutex_unlock(&ecryptfs_kthपढ़ो_ctl.mux);
	kthपढ़ो_stop(ecryptfs_kthपढ़ो);
	wake_up(&ecryptfs_kthपढ़ो_ctl.रुको);
पूर्ण

/**
 * ecryptfs_privileged_खोलो
 * @lower_file: Result of dentry_खोलो by root on lower dentry
 * @lower_dentry: Lower dentry क्रम file to खोलो
 * @lower_mnt: Lower vfsmount क्रम file to खोलो
 * @cred: credential to use क्रम this call
 *
 * This function माला_लो a r/w file खोलोed against the lower dentry.
 *
 * Returns zero on success; non-zero otherwise
 */
पूर्णांक ecryptfs_privileged_खोलो(काष्ठा file **lower_file,
			     काष्ठा dentry *lower_dentry,
			     काष्ठा vfsmount *lower_mnt,
			     स्थिर काष्ठा cred *cred)
अणु
	काष्ठा ecryptfs_खोलो_req req;
	पूर्णांक flags = O_LARGEखाता;
	पूर्णांक rc = 0;

	init_completion(&req.करोne);
	req.lower_file = lower_file;
	req.path.dentry = lower_dentry;
	req.path.mnt = lower_mnt;

	/* Corresponding dput() and mntput() are करोne when the
	 * lower file is fput() when all eCryptfs files क्रम the inode are
	 * released. */
	flags |= IS_RDONLY(d_inode(lower_dentry)) ? O_RDONLY : O_RDWR;
	(*lower_file) = dentry_खोलो(&req.path, flags, cred);
	अगर (!IS_ERR(*lower_file))
		जाओ out;
	अगर ((flags & O_ACCMODE) == O_RDONLY) अणु
		rc = PTR_ERR((*lower_file));
		जाओ out;
	पूर्ण
	mutex_lock(&ecryptfs_kthपढ़ो_ctl.mux);
	अगर (ecryptfs_kthपढ़ो_ctl.flags & ECRYPTFS_KTHREAD_ZOMBIE) अणु
		rc = -EIO;
		mutex_unlock(&ecryptfs_kthपढ़ो_ctl.mux);
		prपूर्णांकk(KERN_ERR "%s: We are in the middle of shutting down; "
		       "aborting privileged request to open lower file\n",
			__func__);
		जाओ out;
	पूर्ण
	list_add_tail(&req.kthपढ़ो_ctl_list, &ecryptfs_kthपढ़ो_ctl.req_list);
	mutex_unlock(&ecryptfs_kthपढ़ो_ctl.mux);
	wake_up(&ecryptfs_kthपढ़ो_ctl.रुको);
	रुको_क्रम_completion(&req.करोne);
	अगर (IS_ERR(*lower_file))
		rc = PTR_ERR(*lower_file);
out:
	वापस rc;
पूर्ण
