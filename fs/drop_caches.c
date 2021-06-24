<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Implement the manual drop-all-pagecache function
 */

#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/fs.h>
#समावेश <linux/ग_लिखोback.h>
#समावेश <linux/sysctl.h>
#समावेश <linux/gfp.h>
#समावेश "internal.h"

/* A global variable is a bit ugly, but it keeps the code simple */
पूर्णांक sysctl_drop_caches;

अटल व्योम drop_pagecache_sb(काष्ठा super_block *sb, व्योम *unused)
अणु
	काष्ठा inode *inode, *toput_inode = शून्य;

	spin_lock(&sb->s_inode_list_lock);
	list_क्रम_each_entry(inode, &sb->s_inodes, i_sb_list) अणु
		spin_lock(&inode->i_lock);
		/*
		 * We must skip inodes in unusual state. We may also skip
		 * inodes without pages but we deliberately won't in हाल
		 * we need to reschedule to aव्योम softlockups.
		 */
		अगर ((inode->i_state & (I_FREEING|I_WILL_FREE|I_NEW)) ||
		    (inode->i_mapping->nrpages == 0 && !need_resched())) अणु
			spin_unlock(&inode->i_lock);
			जारी;
		पूर्ण
		__iget(inode);
		spin_unlock(&inode->i_lock);
		spin_unlock(&sb->s_inode_list_lock);

		invalidate_mapping_pages(inode->i_mapping, 0, -1);
		iput(toput_inode);
		toput_inode = inode;

		cond_resched();
		spin_lock(&sb->s_inode_list_lock);
	पूर्ण
	spin_unlock(&sb->s_inode_list_lock);
	iput(toput_inode);
पूर्ण

पूर्णांक drop_caches_sysctl_handler(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
		व्योम *buffer, माप_प्रकार *length, loff_t *ppos)
अणु
	पूर्णांक ret;

	ret = proc_करोपूर्णांकvec_minmax(table, ग_लिखो, buffer, length, ppos);
	अगर (ret)
		वापस ret;
	अगर (ग_लिखो) अणु
		अटल पूर्णांक stfu;

		अगर (sysctl_drop_caches & 1) अणु
			iterate_supers(drop_pagecache_sb, शून्य);
			count_vm_event(DROP_PAGECACHE);
		पूर्ण
		अगर (sysctl_drop_caches & 2) अणु
			drop_slab();
			count_vm_event(DROP_SLAB);
		पूर्ण
		अगर (!stfu) अणु
			pr_info("%s (%d): drop_caches: %d\n",
				current->comm, task_pid_nr(current),
				sysctl_drop_caches);
		पूर्ण
		stfu |= sysctl_drop_caches & 4;
	पूर्ण
	वापस 0;
पूर्ण
