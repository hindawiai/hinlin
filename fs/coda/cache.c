<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Cache operations क्रम Coda.
 * For Linux 2.1: (C) 1997 Carnegie Mellon University
 * For Linux 2.3: (C) 2000 Carnegie Mellon University
 *
 * Carnegie Mellon encourages users of this code to contribute improvements
 * to the Coda project http://www.coda.cs.cmu.edu/ <coda@cs.cmu.edu>.
 */

#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/समय.स>
#समावेश <linux/fs.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/uaccess.h>
#समावेश <linux/माला.स>
#समावेश <linux/list.h>
#समावेश <linux/sched.h>
#समावेश <linux/spinlock.h>

#समावेश <linux/coda.h>
#समावेश "coda_psdev.h"
#समावेश "coda_linux.h"
#समावेश "coda_cache.h"

अटल atomic_t permission_epoch = ATOMIC_INIT(0);

/* replace or extend an acl cache hit */
व्योम coda_cache_enter(काष्ठा inode *inode, पूर्णांक mask)
अणु
	काष्ठा coda_inode_info *cii = ITOC(inode);

	spin_lock(&cii->c_lock);
	cii->c_cached_epoch = atomic_पढ़ो(&permission_epoch);
	अगर (!uid_eq(cii->c_uid, current_fsuid())) अणु
		cii->c_uid = current_fsuid();
                cii->c_cached_perm = mask;
        पूर्ण अन्यथा
                cii->c_cached_perm |= mask;
	spin_unlock(&cii->c_lock);
पूर्ण

/* हटाओ cached acl from an inode */
व्योम coda_cache_clear_inode(काष्ठा inode *inode)
अणु
	काष्ठा coda_inode_info *cii = ITOC(inode);
	spin_lock(&cii->c_lock);
	cii->c_cached_epoch = atomic_पढ़ो(&permission_epoch) - 1;
	spin_unlock(&cii->c_lock);
पूर्ण

/* हटाओ all acl caches */
व्योम coda_cache_clear_all(काष्ठा super_block *sb)
अणु
	atomic_inc(&permission_epoch);
पूर्ण


/* check अगर the mask has been matched against the acl alपढ़ोy */
पूर्णांक coda_cache_check(काष्ठा inode *inode, पूर्णांक mask)
अणु
	काष्ठा coda_inode_info *cii = ITOC(inode);
	पूर्णांक hit;
	
	spin_lock(&cii->c_lock);
	hit = (mask & cii->c_cached_perm) == mask &&
	    uid_eq(cii->c_uid, current_fsuid()) &&
	    cii->c_cached_epoch == atomic_पढ़ो(&permission_epoch);
	spin_unlock(&cii->c_lock);

	वापस hit;
पूर्ण


/* Purging dentries and children */
/* The following routines drop dentries which are not
   in use and flag dentries which are in use to be 
   zapped later.

   The flags are detected by:
   - coda_dentry_revalidate (क्रम lookups) अगर the flag is C_PURGE
   - coda_dentry_delete: to हटाओ dentry from the cache when d_count
     falls to zero
   - an inode method coda_revalidate (क्रम attributes) अगर the 
     flag is C_VATTR
*/

/* this won't करो any harm: just flag all children */
अटल व्योम coda_flag_children(काष्ठा dentry *parent, पूर्णांक flag)
अणु
	काष्ठा dentry *de;

	spin_lock(&parent->d_lock);
	list_क्रम_each_entry(de, &parent->d_subdirs, d_child) अणु
		/* करोn't know what to करो with negative dentries */
		अगर (d_inode(de) ) 
			coda_flag_inode(d_inode(de), flag);
	पूर्ण
	spin_unlock(&parent->d_lock);
	वापस; 
पूर्ण

व्योम coda_flag_inode_children(काष्ठा inode *inode, पूर्णांक flag)
अणु
	काष्ठा dentry *alias_de;

	अगर ( !inode || !S_ISसूची(inode->i_mode)) 
		वापस; 

	alias_de = d_find_alias(inode);
	अगर (!alias_de)
		वापस;
	coda_flag_children(alias_de, flag);
	shrink_dcache_parent(alias_de);
	dput(alias_de);
पूर्ण

