<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2008 IBM Corporation
 *
 * Authors:
 * Mimi Zohar <zohar@us.ibm.com>
 *
 * File: पूर्णांकegrity_iपूर्णांक.c
 *	- implements the पूर्णांकegrity hooks: पूर्णांकegrity_inode_alloc,
 *	  पूर्णांकegrity_inode_मुक्त
 *	- cache पूर्णांकegrity inक्रमmation associated with an inode
 *	  using a rbtree tree.
 */
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/rbtree.h>
#समावेश <linux/file.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/security.h>
#समावेश <linux/lsm_hooks.h>
#समावेश "integrity.h"

अटल काष्ठा rb_root पूर्णांकegrity_iपूर्णांक_tree = RB_ROOT;
अटल DEFINE_RWLOCK(पूर्णांकegrity_iपूर्णांक_lock);
अटल काष्ठा kmem_cache *iपूर्णांक_cache __पढ़ो_mostly;

काष्ठा dentry *पूर्णांकegrity_dir;

/*
 * __पूर्णांकegrity_iपूर्णांक_find - वापस the iपूर्णांक associated with an inode
 */
अटल काष्ठा पूर्णांकegrity_iपूर्णांक_cache *__पूर्णांकegrity_iपूर्णांक_find(काष्ठा inode *inode)
अणु
	काष्ठा पूर्णांकegrity_iपूर्णांक_cache *iपूर्णांक;
	काष्ठा rb_node *n = पूर्णांकegrity_iपूर्णांक_tree.rb_node;

	जबतक (n) अणु
		iपूर्णांक = rb_entry(n, काष्ठा पूर्णांकegrity_iपूर्णांक_cache, rb_node);

		अगर (inode < iपूर्णांक->inode)
			n = n->rb_left;
		अन्यथा अगर (inode > iपूर्णांक->inode)
			n = n->rb_right;
		अन्यथा
			अवरोध;
	पूर्ण
	अगर (!n)
		वापस शून्य;

	वापस iपूर्णांक;
पूर्ण

/*
 * पूर्णांकegrity_iपूर्णांक_find - वापस the iपूर्णांक associated with an inode
 */
काष्ठा पूर्णांकegrity_iपूर्णांक_cache *पूर्णांकegrity_iपूर्णांक_find(काष्ठा inode *inode)
अणु
	काष्ठा पूर्णांकegrity_iपूर्णांक_cache *iपूर्णांक;

	अगर (!IS_IMA(inode))
		वापस शून्य;

	पढ़ो_lock(&पूर्णांकegrity_iपूर्णांक_lock);
	iपूर्णांक = __पूर्णांकegrity_iपूर्णांक_find(inode);
	पढ़ो_unlock(&पूर्णांकegrity_iपूर्णांक_lock);

	वापस iपूर्णांक;
पूर्ण

अटल व्योम iपूर्णांक_मुक्त(काष्ठा पूर्णांकegrity_iपूर्णांक_cache *iपूर्णांक)
अणु
	kमुक्त(iपूर्णांक->ima_hash);
	iपूर्णांक->ima_hash = शून्य;
	iपूर्णांक->version = 0;
	iपूर्णांक->flags = 0UL;
	iपूर्णांक->atomic_flags = 0UL;
	iपूर्णांक->ima_file_status = INTEGRITY_UNKNOWN;
	iपूर्णांक->ima_mmap_status = INTEGRITY_UNKNOWN;
	iपूर्णांक->ima_bprm_status = INTEGRITY_UNKNOWN;
	iपूर्णांक->ima_पढ़ो_status = INTEGRITY_UNKNOWN;
	iपूर्णांक->ima_creds_status = INTEGRITY_UNKNOWN;
	iपूर्णांक->evm_status = INTEGRITY_UNKNOWN;
	iपूर्णांक->measured_pcrs = 0;
	kmem_cache_मुक्त(iपूर्णांक_cache, iपूर्णांक);
पूर्ण

/**
 * पूर्णांकegrity_inode_get - find or allocate an iपूर्णांक associated with an inode
 * @inode: poपूर्णांकer to the inode
 * @वापस: allocated iपूर्णांक
 *
 * Caller must lock i_mutex
 */
काष्ठा पूर्णांकegrity_iपूर्णांक_cache *पूर्णांकegrity_inode_get(काष्ठा inode *inode)
अणु
	काष्ठा rb_node **p;
	काष्ठा rb_node *node, *parent = शून्य;
	काष्ठा पूर्णांकegrity_iपूर्णांक_cache *iपूर्णांक, *test_iपूर्णांक;

	/*
	 * The पूर्णांकegrity's "iint_cache" is initialized at security_init(),
	 * unless it is not included in the ordered list of LSMs enabled
	 * on the boot command line.
	 */
	अगर (!iपूर्णांक_cache)
		panic("%s: lsm=integrity required.\n", __func__);

	iपूर्णांक = पूर्णांकegrity_iपूर्णांक_find(inode);
	अगर (iपूर्णांक)
		वापस iपूर्णांक;

	iपूर्णांक = kmem_cache_alloc(iपूर्णांक_cache, GFP_NOFS);
	अगर (!iपूर्णांक)
		वापस शून्य;

	ग_लिखो_lock(&पूर्णांकegrity_iपूर्णांक_lock);

	p = &पूर्णांकegrity_iपूर्णांक_tree.rb_node;
	जबतक (*p) अणु
		parent = *p;
		test_iपूर्णांक = rb_entry(parent, काष्ठा पूर्णांकegrity_iपूर्णांक_cache,
				     rb_node);
		अगर (inode < test_iपूर्णांक->inode)
			p = &(*p)->rb_left;
		अन्यथा
			p = &(*p)->rb_right;
	पूर्ण

	iपूर्णांक->inode = inode;
	node = &iपूर्णांक->rb_node;
	inode->i_flags |= S_IMA;
	rb_link_node(node, parent, p);
	rb_insert_color(node, &पूर्णांकegrity_iपूर्णांक_tree);

	ग_लिखो_unlock(&पूर्णांकegrity_iपूर्णांक_lock);
	वापस iपूर्णांक;
पूर्ण

/**
 * पूर्णांकegrity_inode_मुक्त - called on security_inode_मुक्त
 * @inode: poपूर्णांकer to the inode
 *
 * Free the पूर्णांकegrity inक्रमmation(iपूर्णांक) associated with an inode.
 */
व्योम पूर्णांकegrity_inode_मुक्त(काष्ठा inode *inode)
अणु
	काष्ठा पूर्णांकegrity_iपूर्णांक_cache *iपूर्णांक;

	अगर (!IS_IMA(inode))
		वापस;

	ग_लिखो_lock(&पूर्णांकegrity_iपूर्णांक_lock);
	iपूर्णांक = __पूर्णांकegrity_iपूर्णांक_find(inode);
	rb_erase(&iपूर्णांक->rb_node, &पूर्णांकegrity_iपूर्णांक_tree);
	ग_लिखो_unlock(&पूर्णांकegrity_iपूर्णांक_lock);

	iपूर्णांक_मुक्त(iपूर्णांक);
पूर्ण

अटल व्योम init_once(व्योम *foo)
अणु
	काष्ठा पूर्णांकegrity_iपूर्णांक_cache *iपूर्णांक = (काष्ठा पूर्णांकegrity_iपूर्णांक_cache *) foo;

	स_रखो(iपूर्णांक, 0, माप(*iपूर्णांक));
	iपूर्णांक->ima_file_status = INTEGRITY_UNKNOWN;
	iपूर्णांक->ima_mmap_status = INTEGRITY_UNKNOWN;
	iपूर्णांक->ima_bprm_status = INTEGRITY_UNKNOWN;
	iपूर्णांक->ima_पढ़ो_status = INTEGRITY_UNKNOWN;
	iपूर्णांक->ima_creds_status = INTEGRITY_UNKNOWN;
	iपूर्णांक->evm_status = INTEGRITY_UNKNOWN;
	mutex_init(&iपूर्णांक->mutex);
पूर्ण

अटल पूर्णांक __init पूर्णांकegrity_iपूर्णांकcache_init(व्योम)
अणु
	iपूर्णांक_cache =
	    kmem_cache_create("iint_cache", माप(काष्ठा पूर्णांकegrity_iपूर्णांक_cache),
			      0, SLAB_PANIC, init_once);
	वापस 0;
पूर्ण
DEFINE_LSM(पूर्णांकegrity) = अणु
	.name = "integrity",
	.init = पूर्णांकegrity_iपूर्णांकcache_init,
पूर्ण;


/*
 * पूर्णांकegrity_kernel_पढ़ो - पढ़ो data from the file
 *
 * This is a function क्रम पढ़ोing file content instead of kernel_पढ़ो().
 * It करोes not perक्रमm locking checks to ensure it cannot be blocked.
 * It करोes not perक्रमm security checks because it is irrelevant क्रम IMA.
 *
 */
पूर्णांक पूर्णांकegrity_kernel_पढ़ो(काष्ठा file *file, loff_t offset,
			  व्योम *addr, अचिन्हित दीर्घ count)
अणु
	वापस __kernel_पढ़ो(file, addr, count, &offset);
पूर्ण

/*
 * पूर्णांकegrity_load_keys - load पूर्णांकegrity keys hook
 *
 * Hooks is called from init/मुख्य.c:kernel_init_मुक्तable()
 * when rootfs is पढ़ोy
 */
व्योम __init पूर्णांकegrity_load_keys(व्योम)
अणु
	ima_load_x509();
	evm_load_x509();
पूर्ण

अटल पूर्णांक __init पूर्णांकegrity_fs_init(व्योम)
अणु
	पूर्णांकegrity_dir = securityfs_create_dir("integrity", शून्य);
	अगर (IS_ERR(पूर्णांकegrity_dir)) अणु
		पूर्णांक ret = PTR_ERR(पूर्णांकegrity_dir);

		अगर (ret != -ENODEV)
			pr_err("Unable to create integrity sysfs dir: %d\n",
			       ret);
		पूर्णांकegrity_dir = शून्य;
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

late_initcall(पूर्णांकegrity_fs_init)
