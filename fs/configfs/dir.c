<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * dir.c - Operations क्रम configfs directories.
 *
 * Based on sysfs:
 * 	sysfs is Copyright (C) 2001, 2002, 2003 Patrick Mochel
 *
 * configfs Copyright (C) 2005 Oracle.  All rights reserved.
 */

#अघोषित DEBUG

#समावेश <linux/fs.h>
#समावेश <linux/fsnotअगरy.h>
#समावेश <linux/mount.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/err.h>

#समावेश <linux/configfs.h>
#समावेश "configfs_internal.h"

/*
 * Protects mutations of configfs_dirent linkage together with proper i_mutex
 * Also protects mutations of symlinks linkage to target configfs_dirent
 * Mutators of configfs_dirent linkage must *both* have the proper inode locked
 * and configfs_dirent_lock locked, in that order.
 * This allows one to safely traverse configfs_dirent trees and symlinks without
 * having to lock inodes.
 *
 * Protects setting of CONFIGFS_USET_DROPPING: checking the flag
 * unlocked is not reliable unless in detach_groups() called from
 * सूची_हटाओ()/unरेजिस्टर() and from configfs_attach_group()
 */
DEFINE_SPINLOCK(configfs_dirent_lock);

अटल व्योम configfs_d_iput(काष्ठा dentry * dentry,
			    काष्ठा inode * inode)
अणु
	काष्ठा configfs_dirent *sd = dentry->d_fsdata;

	अगर (sd) अणु
		/* Coordinate with configfs_सूची_पढ़ो */
		spin_lock(&configfs_dirent_lock);
		/*
		 * Set sd->s_dentry to null only when this dentry is the one
		 * that is going to be समाप्तed.  Otherwise configfs_d_iput may
		 * run just after configfs_attach_attr and set sd->s_dentry to
		 * शून्य even it's still in use.
		 */
		अगर (sd->s_dentry == dentry)
			sd->s_dentry = शून्य;

		spin_unlock(&configfs_dirent_lock);
		configfs_put(sd);
	पूर्ण
	iput(inode);
पूर्ण

स्थिर काष्ठा dentry_operations configfs_dentry_ops = अणु
	.d_iput		= configfs_d_iput,
	.d_delete	= always_delete_dentry,
पूर्ण;

#अगर_घोषित CONFIG_LOCKDEP

/*
 * Helpers to make lockdep happy with our recursive locking of शेष groups'
 * inodes (see configfs_attach_group() and configfs_detach_group()).
 * We put शेष groups i_mutexes in separate classes according to their depth
 * from the youngest non-शेष group ancestor.
 *
 * For a non-शेष group A having शेष groups A/B, A/C, and A/C/D, शेष
 * groups A/B and A/C will have their inode's mutex in class
 * शेष_group_class[0], and शेष group A/C/D will be in
 * शेष_group_class[1].
 *
 * The lock classes are declared and asचिन्हित in inode.c, according to the
 * s_depth value.
 * The s_depth value is initialized to -1, adjusted to >= 0 when attaching
 * शेष groups, and reset to -1 when all शेष groups are attached. During
 * attachment, अगर configfs_create() sees s_depth > 0, the lock class of the new
 * inode's mutex is set to शेष_group_class[s_depth - 1].
 */

अटल व्योम configfs_init_dirent_depth(काष्ठा configfs_dirent *sd)
अणु
	sd->s_depth = -1;
पूर्ण

अटल व्योम configfs_set_dir_dirent_depth(काष्ठा configfs_dirent *parent_sd,
					  काष्ठा configfs_dirent *sd)
अणु
	पूर्णांक parent_depth = parent_sd->s_depth;

	अगर (parent_depth >= 0)
		sd->s_depth = parent_depth + 1;
पूर्ण

अटल व्योम
configfs_adjust_dir_dirent_depth_beक्रमe_populate(काष्ठा configfs_dirent *sd)
अणु
	/*
	 * item's i_mutex class is alपढ़ोy setup, so s_depth is now only
	 * used to set new sub-directories s_depth, which is always करोne
	 * with item's i_mutex locked.
	 */
	/*
	 *  sd->s_depth == -1 अगरf we are a non शेष group.
	 *  अन्यथा (we are a शेष group) sd->s_depth > 0 (see
	 *  create_dir()).
	 */
	अगर (sd->s_depth == -1)
		/*
		 * We are a non शेष group and we are going to create
		 * शेष groups.
		 */
		sd->s_depth = 0;
पूर्ण

अटल व्योम
configfs_adjust_dir_dirent_depth_after_populate(काष्ठा configfs_dirent *sd)
अणु
	/* We will not create शेष groups anymore. */
	sd->s_depth = -1;
पूर्ण

#अन्यथा /* CONFIG_LOCKDEP */

अटल व्योम configfs_init_dirent_depth(काष्ठा configfs_dirent *sd)
अणु
पूर्ण

अटल व्योम configfs_set_dir_dirent_depth(काष्ठा configfs_dirent *parent_sd,
					  काष्ठा configfs_dirent *sd)
अणु
पूर्ण

अटल व्योम
configfs_adjust_dir_dirent_depth_beक्रमe_populate(काष्ठा configfs_dirent *sd)
अणु
पूर्ण

अटल व्योम
configfs_adjust_dir_dirent_depth_after_populate(काष्ठा configfs_dirent *sd)
अणु
पूर्ण

#पूर्ण_अगर /* CONFIG_LOCKDEP */

अटल काष्ठा configfs_fragment *new_fragment(व्योम)
अणु
	काष्ठा configfs_fragment *p;

	p = kदो_स्मृति(माप(काष्ठा configfs_fragment), GFP_KERNEL);
	अगर (p) अणु
		atomic_set(&p->frag_count, 1);
		init_rwsem(&p->frag_sem);
		p->frag_dead = false;
	पूर्ण
	वापस p;
पूर्ण

व्योम put_fragment(काष्ठा configfs_fragment *frag)
अणु
	अगर (frag && atomic_dec_and_test(&frag->frag_count))
		kमुक्त(frag);
पूर्ण

काष्ठा configfs_fragment *get_fragment(काष्ठा configfs_fragment *frag)
अणु
	अगर (likely(frag))
		atomic_inc(&frag->frag_count);
	वापस frag;
पूर्ण

/*
 * Allocates a new configfs_dirent and links it to the parent configfs_dirent
 */
अटल काष्ठा configfs_dirent *configfs_new_dirent(काष्ठा configfs_dirent *parent_sd,
						   व्योम *element, पूर्णांक type,
						   काष्ठा configfs_fragment *frag)
अणु
	काष्ठा configfs_dirent * sd;

	sd = kmem_cache_zalloc(configfs_dir_cachep, GFP_KERNEL);
	अगर (!sd)
		वापस ERR_PTR(-ENOMEM);

	atomic_set(&sd->s_count, 1);
	INIT_LIST_HEAD(&sd->s_children);
	sd->s_element = element;
	sd->s_type = type;
	configfs_init_dirent_depth(sd);
	spin_lock(&configfs_dirent_lock);
	अगर (parent_sd->s_type & CONFIGFS_USET_DROPPING) अणु
		spin_unlock(&configfs_dirent_lock);
		kmem_cache_मुक्त(configfs_dir_cachep, sd);
		वापस ERR_PTR(-ENOENT);
	पूर्ण
	sd->s_frag = get_fragment(frag);
	list_add(&sd->s_sibling, &parent_sd->s_children);
	spin_unlock(&configfs_dirent_lock);

	वापस sd;
पूर्ण

/*
 *
 * Return -EEXIST अगर there is alपढ़ोy a configfs element with the same
 * name क्रम the same parent.
 *
 * called with parent inode's i_mutex held
 */
अटल पूर्णांक configfs_dirent_exists(काष्ठा configfs_dirent *parent_sd,
				  स्थिर अचिन्हित अक्षर *new)
अणु
	काष्ठा configfs_dirent * sd;

	list_क्रम_each_entry(sd, &parent_sd->s_children, s_sibling) अणु
		अगर (sd->s_element) अणु
			स्थिर अचिन्हित अक्षर *existing = configfs_get_name(sd);
			अगर (म_भेद(existing, new))
				जारी;
			अन्यथा
				वापस -EEXIST;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण


पूर्णांक configfs_make_dirent(काष्ठा configfs_dirent * parent_sd,
			 काष्ठा dentry * dentry, व्योम * element,
			 umode_t mode, पूर्णांक type, काष्ठा configfs_fragment *frag)
अणु
	काष्ठा configfs_dirent * sd;

	sd = configfs_new_dirent(parent_sd, element, type, frag);
	अगर (IS_ERR(sd))
		वापस PTR_ERR(sd);

	sd->s_mode = mode;
	sd->s_dentry = dentry;
	अगर (dentry)
		dentry->d_fsdata = configfs_get(sd);

	वापस 0;
पूर्ण

अटल व्योम configfs_हटाओ_dirent(काष्ठा dentry *dentry)
अणु
	काष्ठा configfs_dirent *sd = dentry->d_fsdata;

	अगर (!sd)
		वापस;
	spin_lock(&configfs_dirent_lock);
	list_del_init(&sd->s_sibling);
	spin_unlock(&configfs_dirent_lock);
	configfs_put(sd);
पूर्ण

/**
 *	configfs_create_dir - create a directory क्रम an config_item.
 *	@item:		config_itemwe're creating directory क्रम.
 *	@dentry:	config_item's dentry.
 *	@frag:		config_item's fragment.
 *
 *	Note: user-created entries won't be allowed under this new directory
 *	until it is validated by configfs_dir_set_पढ़ोy()
 */

अटल पूर्णांक configfs_create_dir(काष्ठा config_item *item, काष्ठा dentry *dentry,
				काष्ठा configfs_fragment *frag)
अणु
	पूर्णांक error;
	umode_t mode = S_IFसूची| S_IRWXU | S_IRUGO | S_IXUGO;
	काष्ठा dentry *p = dentry->d_parent;
	काष्ठा inode *inode;

	BUG_ON(!item);

	error = configfs_dirent_exists(p->d_fsdata, dentry->d_name.name);
	अगर (unlikely(error))
		वापस error;

	error = configfs_make_dirent(p->d_fsdata, dentry, item, mode,
				     CONFIGFS_सूची | CONFIGFS_USET_CREATING,
				     frag);
	अगर (unlikely(error))
		वापस error;

	configfs_set_dir_dirent_depth(p->d_fsdata, dentry->d_fsdata);
	inode = configfs_create(dentry, mode);
	अगर (IS_ERR(inode))
		जाओ out_हटाओ;

	inode->i_op = &configfs_dir_inode_operations;
	inode->i_fop = &configfs_dir_operations;
	/* directory inodes start off with i_nlink == 2 (क्रम "." entry) */
	inc_nlink(inode);
	d_instantiate(dentry, inode);
	/* alपढ़ोy hashed */
	dget(dentry);  /* pin directory dentries in core */
	inc_nlink(d_inode(p));
	item->ci_dentry = dentry;
	वापस 0;

out_हटाओ:
	configfs_हटाओ_dirent(dentry);
	वापस PTR_ERR(inode);
पूर्ण

/*
 * Allow userspace to create new entries under a new directory created with
 * configfs_create_dir(), and under all of its chidlren directories recursively.
 * @sd		configfs_dirent of the new directory to validate
 *
 * Caller must hold configfs_dirent_lock.
 */
अटल व्योम configfs_dir_set_पढ़ोy(काष्ठा configfs_dirent *sd)
अणु
	काष्ठा configfs_dirent *child_sd;

	sd->s_type &= ~CONFIGFS_USET_CREATING;
	list_क्रम_each_entry(child_sd, &sd->s_children, s_sibling)
		अगर (child_sd->s_type & CONFIGFS_USET_CREATING)
			configfs_dir_set_पढ़ोy(child_sd);
पूर्ण

/*
 * Check that a directory करोes not beदीर्घ to a directory hierarchy being
 * attached and not validated yet.
 * @sd		configfs_dirent of the directory to check
 *
 * @वापस	non-zero अगरf the directory was validated
 *
 * Note: takes configfs_dirent_lock, so the result may change from false to true
 * in two consecutive calls, but never from true to false.
 */
पूर्णांक configfs_dirent_is_पढ़ोy(काष्ठा configfs_dirent *sd)
अणु
	पूर्णांक ret;

	spin_lock(&configfs_dirent_lock);
	ret = !(sd->s_type & CONFIGFS_USET_CREATING);
	spin_unlock(&configfs_dirent_lock);

	वापस ret;
पूर्ण

पूर्णांक configfs_create_link(काष्ठा configfs_dirent *target, काष्ठा dentry *parent,
		काष्ठा dentry *dentry, अक्षर *body)
अणु
	पूर्णांक err = 0;
	umode_t mode = S_IFLNK | S_IRWXUGO;
	काष्ठा configfs_dirent *p = parent->d_fsdata;
	काष्ठा inode *inode;

	err = configfs_make_dirent(p, dentry, target, mode, CONFIGFS_ITEM_LINK,
			p->s_frag);
	अगर (err)
		वापस err;

	inode = configfs_create(dentry, mode);
	अगर (IS_ERR(inode))
		जाओ out_हटाओ;

	inode->i_link = body;
	inode->i_op = &configfs_symlink_inode_operations;
	d_instantiate(dentry, inode);
	dget(dentry);  /* pin link dentries in core */
	वापस 0;

out_हटाओ:
	configfs_हटाओ_dirent(dentry);
	वापस PTR_ERR(inode);
पूर्ण

अटल व्योम हटाओ_dir(काष्ठा dentry * d)
अणु
	काष्ठा dentry * parent = dget(d->d_parent);

	configfs_हटाओ_dirent(d);

	अगर (d_really_is_positive(d))
		simple_सूची_हटाओ(d_inode(parent),d);

	pr_debug(" o %pd removing done (%d)\n", d, d_count(d));

	dput(parent);
पूर्ण

/**
 * configfs_हटाओ_dir - हटाओ an config_item's directory.
 * @item:	config_item we're removing.
 *
 * The only thing special about this is that we हटाओ any files in
 * the directory beक्रमe we हटाओ the directory, and we've अंतरभूतd
 * what used to be configfs_सूची_हटाओ() below, instead of calling separately.
 *
 * Caller holds the mutex of the item's inode
 */

अटल व्योम configfs_हटाओ_dir(काष्ठा config_item * item)
अणु
	काष्ठा dentry * dentry = dget(item->ci_dentry);

	अगर (!dentry)
		वापस;

	हटाओ_dir(dentry);
	/**
	 * Drop reference from dget() on entrance.
	 */
	dput(dentry);
पूर्ण


/* attaches attribute's configfs_dirent to the dentry corresponding to the
 * attribute file
 */
अटल पूर्णांक configfs_attach_attr(काष्ठा configfs_dirent * sd, काष्ठा dentry * dentry)
अणु
	काष्ठा configfs_attribute * attr = sd->s_element;
	काष्ठा inode *inode;

	spin_lock(&configfs_dirent_lock);
	dentry->d_fsdata = configfs_get(sd);
	sd->s_dentry = dentry;
	spin_unlock(&configfs_dirent_lock);

	inode = configfs_create(dentry, (attr->ca_mode & S_IALLUGO) | S_IFREG);
	अगर (IS_ERR(inode)) अणु
		configfs_put(sd);
		वापस PTR_ERR(inode);
	पूर्ण
	अगर (sd->s_type & CONFIGFS_ITEM_BIN_ATTR) अणु
		inode->i_size = 0;
		inode->i_fop = &configfs_bin_file_operations;
	पूर्ण अन्यथा अणु
		inode->i_size = PAGE_SIZE;
		inode->i_fop = &configfs_file_operations;
	पूर्ण
	d_add(dentry, inode);
	वापस 0;
पूर्ण

अटल काष्ठा dentry * configfs_lookup(काष्ठा inode *dir,
				       काष्ठा dentry *dentry,
				       अचिन्हित पूर्णांक flags)
अणु
	काष्ठा configfs_dirent * parent_sd = dentry->d_parent->d_fsdata;
	काष्ठा configfs_dirent * sd;
	पूर्णांक found = 0;
	पूर्णांक err;

	/*
	 * Fake invisibility अगर dir beदीर्घs to a group/शेष groups hierarchy
	 * being attached
	 *
	 * This क्रमbids userspace to पढ़ो/ग_लिखो attributes of items which may
	 * not complete their initialization, since the dentries of the
	 * attributes won't be instantiated.
	 */
	err = -ENOENT;
	अगर (!configfs_dirent_is_पढ़ोy(parent_sd))
		जाओ out;

	list_क्रम_each_entry(sd, &parent_sd->s_children, s_sibling) अणु
		अगर (sd->s_type & CONFIGFS_NOT_PINNED) अणु
			स्थिर अचिन्हित अक्षर * name = configfs_get_name(sd);

			अगर (म_भेद(name, dentry->d_name.name))
				जारी;

			found = 1;
			err = configfs_attach_attr(sd, dentry);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!found) अणु
		/*
		 * If it करोesn't exist and it isn't a NOT_PINNED item,
		 * it must be negative.
		 */
		अगर (dentry->d_name.len > NAME_MAX)
			वापस ERR_PTR(-ENAMETOOLONG);
		d_add(dentry, शून्य);
		वापस शून्य;
	पूर्ण

out:
	वापस ERR_PTR(err);
पूर्ण

/*
 * Only subdirectories count here.  Files (CONFIGFS_NOT_PINNED) are
 * attributes and are हटाओd by सूची_हटाओ().  We recurse, setting
 * CONFIGFS_USET_DROPPING on all children that are candidates क्रम
 * शेष detach.
 * If there is an error, the caller will reset the flags via
 * configfs_detach_rollback().
 */
अटल पूर्णांक configfs_detach_prep(काष्ठा dentry *dentry, काष्ठा dentry **रुको)
अणु
	काष्ठा configfs_dirent *parent_sd = dentry->d_fsdata;
	काष्ठा configfs_dirent *sd;
	पूर्णांक ret;

	/* Mark that we're trying to drop the group */
	parent_sd->s_type |= CONFIGFS_USET_DROPPING;

	ret = -EBUSY;
	अगर (parent_sd->s_links)
		जाओ out;

	ret = 0;
	list_क्रम_each_entry(sd, &parent_sd->s_children, s_sibling) अणु
		अगर (!sd->s_element ||
		    (sd->s_type & CONFIGFS_NOT_PINNED))
			जारी;
		अगर (sd->s_type & CONFIGFS_USET_DEFAULT) अणु
			/* Abort अगर racing with सूची_गढ़ो() */
			अगर (sd->s_type & CONFIGFS_USET_IN_MKसूची) अणु
				अगर (रुको)
					*रुको= dget(sd->s_dentry);
				वापस -EAGAIN;
			पूर्ण

			/*
			 * Yup, recursive.  If there's a problem, blame
			 * deep nesting of शेष_groups
			 */
			ret = configfs_detach_prep(sd->s_dentry, रुको);
			अगर (!ret)
				जारी;
		पूर्ण अन्यथा
			ret = -ENOTEMPTY;

		अवरोध;
	पूर्ण

out:
	वापस ret;
पूर्ण

/*
 * Walk the tree, resetting CONFIGFS_USET_DROPPING wherever it was
 * set.
 */
अटल व्योम configfs_detach_rollback(काष्ठा dentry *dentry)
अणु
	काष्ठा configfs_dirent *parent_sd = dentry->d_fsdata;
	काष्ठा configfs_dirent *sd;

	parent_sd->s_type &= ~CONFIGFS_USET_DROPPING;

	list_क्रम_each_entry(sd, &parent_sd->s_children, s_sibling)
		अगर (sd->s_type & CONFIGFS_USET_DEFAULT)
			configfs_detach_rollback(sd->s_dentry);
पूर्ण

अटल व्योम detach_attrs(काष्ठा config_item * item)
अणु
	काष्ठा dentry * dentry = dget(item->ci_dentry);
	काष्ठा configfs_dirent * parent_sd;
	काष्ठा configfs_dirent * sd, * पंचांगp;

	अगर (!dentry)
		वापस;

	pr_debug("configfs %s: dropping attrs for  dir\n",
		 dentry->d_name.name);

	parent_sd = dentry->d_fsdata;
	list_क्रम_each_entry_safe(sd, पंचांगp, &parent_sd->s_children, s_sibling) अणु
		अगर (!sd->s_element || !(sd->s_type & CONFIGFS_NOT_PINNED))
			जारी;
		spin_lock(&configfs_dirent_lock);
		list_del_init(&sd->s_sibling);
		spin_unlock(&configfs_dirent_lock);
		configfs_drop_dentry(sd, dentry);
		configfs_put(sd);
	पूर्ण

	/**
	 * Drop reference from dget() on entrance.
	 */
	dput(dentry);
पूर्ण

अटल पूर्णांक populate_attrs(काष्ठा config_item *item)
अणु
	स्थिर काष्ठा config_item_type *t = item->ci_type;
	काष्ठा configfs_attribute *attr;
	काष्ठा configfs_bin_attribute *bin_attr;
	पूर्णांक error = 0;
	पूर्णांक i;

	अगर (!t)
		वापस -EINVAL;
	अगर (t->ct_attrs) अणु
		क्रम (i = 0; (attr = t->ct_attrs[i]) != शून्य; i++) अणु
			अगर ((error = configfs_create_file(item, attr)))
				अवरोध;
		पूर्ण
	पूर्ण
	अगर (t->ct_bin_attrs) अणु
		क्रम (i = 0; (bin_attr = t->ct_bin_attrs[i]) != शून्य; i++) अणु
			error = configfs_create_bin_file(item, bin_attr);
			अगर (error)
				अवरोध;
		पूर्ण
	पूर्ण

	अगर (error)
		detach_attrs(item);

	वापस error;
पूर्ण

अटल पूर्णांक configfs_attach_group(काष्ठा config_item *parent_item,
				 काष्ठा config_item *item,
				 काष्ठा dentry *dentry,
				 काष्ठा configfs_fragment *frag);
अटल व्योम configfs_detach_group(काष्ठा config_item *item);

अटल व्योम detach_groups(काष्ठा config_group *group)
अणु
	काष्ठा dentry * dentry = dget(group->cg_item.ci_dentry);
	काष्ठा dentry *child;
	काष्ठा configfs_dirent *parent_sd;
	काष्ठा configfs_dirent *sd, *पंचांगp;

	अगर (!dentry)
		वापस;

	parent_sd = dentry->d_fsdata;
	list_क्रम_each_entry_safe(sd, पंचांगp, &parent_sd->s_children, s_sibling) अणु
		अगर (!sd->s_element ||
		    !(sd->s_type & CONFIGFS_USET_DEFAULT))
			जारी;

		child = sd->s_dentry;

		inode_lock(d_inode(child));

		configfs_detach_group(sd->s_element);
		d_inode(child)->i_flags |= S_DEAD;
		करोnt_mount(child);

		inode_unlock(d_inode(child));

		d_delete(child);
		dput(child);
	पूर्ण

	/**
	 * Drop reference from dget() on entrance.
	 */
	dput(dentry);
पूर्ण

/*
 * This fakes सूची_गढ़ो(2) on a शेष_groups[] entry.  It
 * creates a dentry, attachs it, and then करोes fixup
 * on the sd->s_type.
 *
 * We could, perhaps, tweak our parent's ->सूची_गढ़ो क्रम a minute and
 * try using vfs_सूची_गढ़ो.  Just a thought.
 */
अटल पूर्णांक create_शेष_group(काष्ठा config_group *parent_group,
				काष्ठा config_group *group,
				काष्ठा configfs_fragment *frag)
अणु
	पूर्णांक ret;
	काष्ठा configfs_dirent *sd;
	/* We trust the caller holds a reference to parent */
	काष्ठा dentry *child, *parent = parent_group->cg_item.ci_dentry;

	अगर (!group->cg_item.ci_name)
		group->cg_item.ci_name = group->cg_item.ci_namebuf;

	ret = -ENOMEM;
	child = d_alloc_name(parent, group->cg_item.ci_name);
	अगर (child) अणु
		d_add(child, शून्य);

		ret = configfs_attach_group(&parent_group->cg_item,
					    &group->cg_item, child, frag);
		अगर (!ret) अणु
			sd = child->d_fsdata;
			sd->s_type |= CONFIGFS_USET_DEFAULT;
		पूर्ण अन्यथा अणु
			BUG_ON(d_inode(child));
			d_drop(child);
			dput(child);
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक populate_groups(काष्ठा config_group *group,
			   काष्ठा configfs_fragment *frag)
अणु
	काष्ठा config_group *new_group;
	पूर्णांक ret = 0;

	list_क्रम_each_entry(new_group, &group->शेष_groups, group_entry) अणु
		ret = create_शेष_group(group, new_group, frag);
		अगर (ret) अणु
			detach_groups(group);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

व्योम configfs_हटाओ_शेष_groups(काष्ठा config_group *group)
अणु
	काष्ठा config_group *g, *n;

	list_क्रम_each_entry_safe(g, n, &group->शेष_groups, group_entry) अणु
		list_del(&g->group_entry);
		config_item_put(&g->cg_item);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(configfs_हटाओ_शेष_groups);

/*
 * All of link_obj/unlink_obj/link_group/unlink_group require that
 * subsys->su_mutex is held.
 */

अटल व्योम unlink_obj(काष्ठा config_item *item)
अणु
	काष्ठा config_group *group;

	group = item->ci_group;
	अगर (group) अणु
		list_del_init(&item->ci_entry);

		item->ci_group = शून्य;
		item->ci_parent = शून्य;

		/* Drop the reference क्रम ci_entry */
		config_item_put(item);

		/* Drop the reference क्रम ci_parent */
		config_group_put(group);
	पूर्ण
पूर्ण

अटल व्योम link_obj(काष्ठा config_item *parent_item, काष्ठा config_item *item)
अणु
	/*
	 * Parent seems redundant with group, but it makes certain
	 * traversals much nicer.
	 */
	item->ci_parent = parent_item;

	/*
	 * We hold a reference on the parent क्रम the child's ci_parent
	 * link.
	 */
	item->ci_group = config_group_get(to_config_group(parent_item));
	list_add_tail(&item->ci_entry, &item->ci_group->cg_children);

	/*
	 * We hold a reference on the child क्रम ci_entry on the parent's
	 * cg_children
	 */
	config_item_get(item);
पूर्ण

अटल व्योम unlink_group(काष्ठा config_group *group)
अणु
	काष्ठा config_group *new_group;

	list_क्रम_each_entry(new_group, &group->शेष_groups, group_entry)
		unlink_group(new_group);

	group->cg_subsys = शून्य;
	unlink_obj(&group->cg_item);
पूर्ण

अटल व्योम link_group(काष्ठा config_group *parent_group, काष्ठा config_group *group)
अणु
	काष्ठा config_group *new_group;
	काष्ठा configfs_subप्रणाली *subsys = शून्य; /* gcc is a turd */

	link_obj(&parent_group->cg_item, &group->cg_item);

	अगर (parent_group->cg_subsys)
		subsys = parent_group->cg_subsys;
	अन्यथा अगर (configfs_is_root(&parent_group->cg_item))
		subsys = to_configfs_subप्रणाली(group);
	अन्यथा
		BUG();
	group->cg_subsys = subsys;

	list_क्रम_each_entry(new_group, &group->शेष_groups, group_entry)
		link_group(group, new_group);
पूर्ण

/*
 * The goal is that configfs_attach_item() (and
 * configfs_attach_group()) can be called from either the VFS or this
 * module.  That is, they assume that the items have been created,
 * the dentry allocated, and the dcache is all पढ़ोy to go.
 *
 * If they fail, they must clean up after themselves as अगर they
 * had never been called.  The caller (VFS or local function) will
 * handle cleaning up the dcache bits.
 *
 * configfs_detach_group() and configfs_detach_item() behave similarly on
 * the way out.  They assume that the proper semaphores are held, they
 * clean up the configfs items, and they expect their callers will
 * handle the dcache bits.
 */
अटल पूर्णांक configfs_attach_item(काष्ठा config_item *parent_item,
				काष्ठा config_item *item,
				काष्ठा dentry *dentry,
				काष्ठा configfs_fragment *frag)
अणु
	पूर्णांक ret;

	ret = configfs_create_dir(item, dentry, frag);
	अगर (!ret) अणु
		ret = populate_attrs(item);
		अगर (ret) अणु
			/*
			 * We are going to हटाओ an inode and its dentry but
			 * the VFS may alपढ़ोy have hit and used them. Thus,
			 * we must lock them as सूची_हटाओ() would.
			 */
			inode_lock(d_inode(dentry));
			configfs_हटाओ_dir(item);
			d_inode(dentry)->i_flags |= S_DEAD;
			करोnt_mount(dentry);
			inode_unlock(d_inode(dentry));
			d_delete(dentry);
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

/* Caller holds the mutex of the item's inode */
अटल व्योम configfs_detach_item(काष्ठा config_item *item)
अणु
	detach_attrs(item);
	configfs_हटाओ_dir(item);
पूर्ण

अटल पूर्णांक configfs_attach_group(काष्ठा config_item *parent_item,
				 काष्ठा config_item *item,
				 काष्ठा dentry *dentry,
				 काष्ठा configfs_fragment *frag)
अणु
	पूर्णांक ret;
	काष्ठा configfs_dirent *sd;

	ret = configfs_attach_item(parent_item, item, dentry, frag);
	अगर (!ret) अणु
		sd = dentry->d_fsdata;
		sd->s_type |= CONFIGFS_USET_सूची;

		/*
		 * FYI, we're faking सूची_गढ़ो in populate_groups()
		 * We must lock the group's inode to aव्योम races with the VFS
		 * which can alपढ़ोy hit the inode and try to add/हटाओ entries
		 * under it.
		 *
		 * We must also lock the inode to हटाओ it safely in हाल of
		 * error, as सूची_हटाओ() would.
		 */
		inode_lock_nested(d_inode(dentry), I_MUTEX_CHILD);
		configfs_adjust_dir_dirent_depth_beक्रमe_populate(sd);
		ret = populate_groups(to_config_group(item), frag);
		अगर (ret) अणु
			configfs_detach_item(item);
			d_inode(dentry)->i_flags |= S_DEAD;
			करोnt_mount(dentry);
		पूर्ण
		configfs_adjust_dir_dirent_depth_after_populate(sd);
		inode_unlock(d_inode(dentry));
		अगर (ret)
			d_delete(dentry);
	पूर्ण

	वापस ret;
पूर्ण

/* Caller holds the mutex of the group's inode */
अटल व्योम configfs_detach_group(काष्ठा config_item *item)
अणु
	detach_groups(to_config_group(item));
	configfs_detach_item(item);
पूर्ण

/*
 * After the item has been detached from the fileप्रणाली view, we are
 * पढ़ोy to tear it out of the hierarchy.  Notअगरy the client beक्रमe
 * we करो that so they can perक्रमm any cleanup that requires
 * navigating the hierarchy.  A client करोes not need to provide this
 * callback.  The subप्रणाली semaphore MUST be held by the caller, and
 * references must be valid क्रम both items.  It also assumes the
 * caller has validated ci_type.
 */
अटल व्योम client_disconnect_notअगरy(काष्ठा config_item *parent_item,
				     काष्ठा config_item *item)
अणु
	स्थिर काष्ठा config_item_type *type;

	type = parent_item->ci_type;
	BUG_ON(!type);

	अगर (type->ct_group_ops && type->ct_group_ops->disconnect_notअगरy)
		type->ct_group_ops->disconnect_notअगरy(to_config_group(parent_item),
						      item);
पूर्ण

/*
 * Drop the initial reference from make_item()/make_group()
 * This function assumes that reference is held on item
 * and that item holds a valid reference to the parent.  Also, it
 * assumes the caller has validated ci_type.
 */
अटल व्योम client_drop_item(काष्ठा config_item *parent_item,
			     काष्ठा config_item *item)
अणु
	स्थिर काष्ठा config_item_type *type;

	type = parent_item->ci_type;
	BUG_ON(!type);

	/*
	 * If ->drop_item() exists, it is responsible क्रम the
	 * config_item_put().
	 */
	अगर (type->ct_group_ops && type->ct_group_ops->drop_item)
		type->ct_group_ops->drop_item(to_config_group(parent_item),
					      item);
	अन्यथा
		config_item_put(item);
पूर्ण

#अगर_घोषित DEBUG
अटल व्योम configfs_dump_one(काष्ठा configfs_dirent *sd, पूर्णांक level)
अणु
	pr_info("%*s\"%s\":\n", level, " ", configfs_get_name(sd));

#घोषणा type_prपूर्णांक(_type) अगर (sd->s_type & _type) pr_info("%*s %s\n", level, " ", #_type);
	type_prपूर्णांक(CONFIGFS_ROOT);
	type_prपूर्णांक(CONFIGFS_सूची);
	type_prपूर्णांक(CONFIGFS_ITEM_ATTR);
	type_prपूर्णांक(CONFIGFS_ITEM_LINK);
	type_prपूर्णांक(CONFIGFS_USET_सूची);
	type_prपूर्णांक(CONFIGFS_USET_DEFAULT);
	type_prपूर्णांक(CONFIGFS_USET_DROPPING);
#अघोषित type_prपूर्णांक
पूर्ण

अटल पूर्णांक configfs_dump(काष्ठा configfs_dirent *sd, पूर्णांक level)
अणु
	काष्ठा configfs_dirent *child_sd;
	पूर्णांक ret = 0;

	configfs_dump_one(sd, level);

	अगर (!(sd->s_type & (CONFIGFS_सूची|CONFIGFS_ROOT)))
		वापस 0;

	list_क्रम_each_entry(child_sd, &sd->s_children, s_sibling) अणु
		ret = configfs_dump(child_sd, level + 2);
		अगर (ret)
			अवरोध;
	पूर्ण

	वापस ret;
पूर्ण
#पूर्ण_अगर


/*
 * configfs_depend_item() and configfs_undepend_item()
 *
 * WARNING: Do not call these from a configfs callback!
 *
 * This describes these functions and their helpers.
 *
 * Allow another kernel प्रणाली to depend on a config_item.  If this
 * happens, the item cannot go away until the dependent can live without
 * it.  The idea is to give client modules as simple an पूर्णांकerface as
 * possible.  When a प्रणाली asks them to depend on an item, they just
 * call configfs_depend_item().  If the item is live and the client
 * driver is in good shape, we'll happily करो the work क्रम them.
 *
 * Why is the locking complex?  Because configfs uses the VFS to handle
 * all locking, but this function is called outside the normal
 * VFS->configfs path.  So it must take VFS locks to prevent the
 * VFS->configfs stuff (configfs_सूची_गढ़ो(), configfs_सूची_हटाओ(), etc).  This is
 * why you can't call these functions underneath configfs callbacks.
 *
 * Note, btw, that this can be called at *any* समय, even when a configfs
 * subप्रणाली isn't रेजिस्टरed, or when configfs is loading or unloading.
 * Just like configfs_रेजिस्टर_subप्रणाली().  So we take the same
 * precautions.  We pin the fileप्रणाली.  We lock configfs_dirent_lock.
 * If we can find the target item in the
 * configfs tree, it must be part of the subप्रणाली tree as well, so we
 * करो not need the subप्रणाली semaphore.  Holding configfs_dirent_lock helps
 * locking out सूची_गढ़ो() and सूची_हटाओ(), who might be racing us.
 */

/*
 * configfs_depend_prep()
 *
 * Only subdirectories count here.  Files (CONFIGFS_NOT_PINNED) are
 * attributes.  This is similar but not the same to configfs_detach_prep().
 * Note that configfs_detach_prep() expects the parent to be locked when it
 * is called, but we lock the parent *inside* configfs_depend_prep().  We
 * करो that so we can unlock it अगर we find nothing.
 *
 * Here we करो a depth-first search of the dentry hierarchy looking क्रम
 * our object.
 * We deliberately ignore items tagged as dropping since they are भवly
 * dead, as well as items in the middle of attachment since they भवly
 * करो not exist yet. This completes the locking out of racing सूची_गढ़ो() and
 * सूची_हटाओ().
 * Note: subdirectories in the middle of attachment start with s_type =
 * CONFIGFS_सूची|CONFIGFS_USET_CREATING set by create_dir().  When
 * CONFIGFS_USET_CREATING is set, we ignore the item.  The actual set of
 * s_type is in configfs_new_dirent(), which has configfs_dirent_lock.
 *
 * If the target is not found, -ENOENT is bubbled up.
 *
 * This adds a requirement that all config_items be unique!
 *
 * This is recursive.  There isn't
 * much on the stack, though, so folks that need this function - be careful
 * about your stack!  Patches will be accepted to make it iterative.
 */
अटल पूर्णांक configfs_depend_prep(काष्ठा dentry *origin,
				काष्ठा config_item *target)
अणु
	काष्ठा configfs_dirent *child_sd, *sd;
	पूर्णांक ret = 0;

	BUG_ON(!origin || !origin->d_fsdata);
	sd = origin->d_fsdata;

	अगर (sd->s_element == target)  /* Boo-yah */
		जाओ out;

	list_क्रम_each_entry(child_sd, &sd->s_children, s_sibling) अणु
		अगर ((child_sd->s_type & CONFIGFS_सूची) &&
		    !(child_sd->s_type & CONFIGFS_USET_DROPPING) &&
		    !(child_sd->s_type & CONFIGFS_USET_CREATING)) अणु
			ret = configfs_depend_prep(child_sd->s_dentry,
						   target);
			अगर (!ret)
				जाओ out;  /* Child path boo-yah */
		पूर्ण
	पूर्ण

	/* We looped all our children and didn't find target */
	ret = -ENOENT;

out:
	वापस ret;
पूर्ण

अटल पूर्णांक configfs_करो_depend_item(काष्ठा dentry *subsys_dentry,
				   काष्ठा config_item *target)
अणु
	काष्ठा configfs_dirent *p;
	पूर्णांक ret;

	spin_lock(&configfs_dirent_lock);
	/* Scan the tree, वापस 0 अगर found */
	ret = configfs_depend_prep(subsys_dentry, target);
	अगर (ret)
		जाओ out_unlock_dirent_lock;

	/*
	 * We are sure that the item is not about to be हटाओd by सूची_हटाओ(), and
	 * not in the middle of attachment by सूची_गढ़ो().
	 */
	p = target->ci_dentry->d_fsdata;
	p->s_dependent_count += 1;

out_unlock_dirent_lock:
	spin_unlock(&configfs_dirent_lock);

	वापस ret;
पूर्ण

अटल अंतरभूत काष्ठा configfs_dirent *
configfs_find_subsys_dentry(काष्ठा configfs_dirent *root_sd,
			    काष्ठा config_item *subsys_item)
अणु
	काष्ठा configfs_dirent *p;
	काष्ठा configfs_dirent *ret = शून्य;

	list_क्रम_each_entry(p, &root_sd->s_children, s_sibling) अणु
		अगर (p->s_type & CONFIGFS_सूची &&
		    p->s_element == subsys_item) अणु
			ret = p;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण


पूर्णांक configfs_depend_item(काष्ठा configfs_subप्रणाली *subsys,
			 काष्ठा config_item *target)
अणु
	पूर्णांक ret;
	काष्ठा configfs_dirent *subsys_sd;
	काष्ठा config_item *s_item = &subsys->su_group.cg_item;
	काष्ठा dentry *root;

	/*
	 * Pin the configfs fileप्रणाली.  This means we can safely access
	 * the root of the configfs fileप्रणाली.
	 */
	root = configfs_pin_fs();
	अगर (IS_ERR(root))
		वापस PTR_ERR(root);

	/*
	 * Next, lock the root directory.  We're going to check that the
	 * subप्रणाली is really रेजिस्टरed, and so we need to lock out
	 * configfs_[un]रेजिस्टर_subप्रणाली().
	 */
	inode_lock(d_inode(root));

	subsys_sd = configfs_find_subsys_dentry(root->d_fsdata, s_item);
	अगर (!subsys_sd) अणु
		ret = -ENOENT;
		जाओ out_unlock_fs;
	पूर्ण

	/* Ok, now we can trust subsys/s_item */
	ret = configfs_करो_depend_item(subsys_sd->s_dentry, target);

out_unlock_fs:
	inode_unlock(d_inode(root));

	/*
	 * If we succeeded, the fs is pinned via other methods.  If not,
	 * we're करोne with it anyway.  So release_fs() is always right.
	 */
	configfs_release_fs();

	वापस ret;
पूर्ण
EXPORT_SYMBOL(configfs_depend_item);

/*
 * Release the dependent linkage.  This is much simpler than
 * configfs_depend_item() because we know that the client driver is
 * pinned, thus the subप्रणाली is pinned, and thereक्रमe configfs is pinned.
 */
व्योम configfs_undepend_item(काष्ठा config_item *target)
अणु
	काष्ठा configfs_dirent *sd;

	/*
	 * Since we can trust everything is pinned, we just need
	 * configfs_dirent_lock.
	 */
	spin_lock(&configfs_dirent_lock);

	sd = target->ci_dentry->d_fsdata;
	BUG_ON(sd->s_dependent_count < 1);

	sd->s_dependent_count -= 1;

	/*
	 * After this unlock, we cannot trust the item to stay alive!
	 * DO NOT REFERENCE item after this unlock.
	 */
	spin_unlock(&configfs_dirent_lock);
पूर्ण
EXPORT_SYMBOL(configfs_undepend_item);

/*
 * caller_subsys is a caller's subsystem not target's. This is used to
 * determine अगर we should lock root and check subsys or not. When we are
 * in the same subप्रणाली as our target there is no need to करो locking as
 * we know that subsys is valid and is not unरेजिस्टरed during this function
 * as we are called from callback of one of his children and VFS holds a lock
 * on some inode. Otherwise we have to lock our root to  ensure that target's
 * subप्रणाली it is not unरेजिस्टरed during this function.
 */
पूर्णांक configfs_depend_item_unlocked(काष्ठा configfs_subप्रणाली *caller_subsys,
				  काष्ठा config_item *target)
अणु
	काष्ठा configfs_subप्रणाली *target_subsys;
	काष्ठा config_group *root, *parent;
	काष्ठा configfs_dirent *subsys_sd;
	पूर्णांक ret = -ENOENT;

	/* Disallow this function क्रम configfs root */
	अगर (configfs_is_root(target))
		वापस -EINVAL;

	parent = target->ci_group;
	/*
	 * This may happen when someone is trying to depend root
	 * directory of some subप्रणाली
	 */
	अगर (configfs_is_root(&parent->cg_item)) अणु
		target_subsys = to_configfs_subप्रणाली(to_config_group(target));
		root = parent;
	पूर्ण अन्यथा अणु
		target_subsys = parent->cg_subsys;
		/* Find a cofnigfs root as we may need it क्रम locking */
		क्रम (root = parent; !configfs_is_root(&root->cg_item);
		     root = root->cg_item.ci_group)
			;
	पूर्ण

	अगर (target_subsys != caller_subsys) अणु
		/*
		 * We are in other configfs subप्रणाली, so we have to करो
		 * additional locking to prevent other subप्रणाली from being
		 * unरेजिस्टरed
		 */
		inode_lock(d_inode(root->cg_item.ci_dentry));

		/*
		 * As we are trying to depend item from other subप्रणाली
		 * we have to check अगर this subप्रणाली is still रेजिस्टरed
		 */
		subsys_sd = configfs_find_subsys_dentry(
				root->cg_item.ci_dentry->d_fsdata,
				&target_subsys->su_group.cg_item);
		अगर (!subsys_sd)
			जाओ out_root_unlock;
	पूर्ण अन्यथा अणु
		subsys_sd = target_subsys->su_group.cg_item.ci_dentry->d_fsdata;
	पूर्ण

	/* Now we can execute core of depend item */
	ret = configfs_करो_depend_item(subsys_sd->s_dentry, target);

	अगर (target_subsys != caller_subsys)
out_root_unlock:
		/*
		 * We were called from subप्रणाली other than our target so we
		 * took some locks so now it's समय to release them
		 */
		inode_unlock(d_inode(root->cg_item.ci_dentry));

	वापस ret;
पूर्ण
EXPORT_SYMBOL(configfs_depend_item_unlocked);

अटल पूर्णांक configfs_सूची_गढ़ो(काष्ठा user_namespace *mnt_userns, काष्ठा inode *dir,
			  काष्ठा dentry *dentry, umode_t mode)
अणु
	पूर्णांक ret = 0;
	पूर्णांक module_got = 0;
	काष्ठा config_group *group = शून्य;
	काष्ठा config_item *item = शून्य;
	काष्ठा config_item *parent_item;
	काष्ठा configfs_subप्रणाली *subsys;
	काष्ठा configfs_dirent *sd;
	स्थिर काष्ठा config_item_type *type;
	काष्ठा module *subsys_owner = शून्य, *new_item_owner = शून्य;
	काष्ठा configfs_fragment *frag;
	अक्षर *name;

	sd = dentry->d_parent->d_fsdata;

	/*
	 * Fake invisibility अगर dir beदीर्घs to a group/शेष groups hierarchy
	 * being attached
	 */
	अगर (!configfs_dirent_is_पढ़ोy(sd)) अणु
		ret = -ENOENT;
		जाओ out;
	पूर्ण

	अगर (!(sd->s_type & CONFIGFS_USET_सूची)) अणु
		ret = -EPERM;
		जाओ out;
	पूर्ण

	frag = new_fragment();
	अगर (!frag) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	/* Get a working ref क्रम the duration of this function */
	parent_item = configfs_get_config_item(dentry->d_parent);
	type = parent_item->ci_type;
	subsys = to_config_group(parent_item)->cg_subsys;
	BUG_ON(!subsys);

	अगर (!type || !type->ct_group_ops ||
	    (!type->ct_group_ops->make_group &&
	     !type->ct_group_ops->make_item)) अणु
		ret = -EPERM;  /* Lack-of-सूची_गढ़ो वापसs -EPERM */
		जाओ out_put;
	पूर्ण

	/*
	 * The subप्रणाली may beदीर्घ to a dअगरferent module than the item
	 * being created.  We करोn't want to safely pin the new item but
	 * fail to pin the subप्रणाली it sits under.
	 */
	अगर (!subsys->su_group.cg_item.ci_type) अणु
		ret = -EINVAL;
		जाओ out_put;
	पूर्ण
	subsys_owner = subsys->su_group.cg_item.ci_type->ct_owner;
	अगर (!try_module_get(subsys_owner)) अणु
		ret = -EINVAL;
		जाओ out_put;
	पूर्ण

	name = kदो_स्मृति(dentry->d_name.len + 1, GFP_KERNEL);
	अगर (!name) अणु
		ret = -ENOMEM;
		जाओ out_subsys_put;
	पूर्ण

	snम_लिखो(name, dentry->d_name.len + 1, "%s", dentry->d_name.name);

	mutex_lock(&subsys->su_mutex);
	अगर (type->ct_group_ops->make_group) अणु
		group = type->ct_group_ops->make_group(to_config_group(parent_item), name);
		अगर (!group)
			group = ERR_PTR(-ENOMEM);
		अगर (!IS_ERR(group)) अणु
			link_group(to_config_group(parent_item), group);
			item = &group->cg_item;
		पूर्ण अन्यथा
			ret = PTR_ERR(group);
	पूर्ण अन्यथा अणु
		item = type->ct_group_ops->make_item(to_config_group(parent_item), name);
		अगर (!item)
			item = ERR_PTR(-ENOMEM);
		अगर (!IS_ERR(item))
			link_obj(parent_item, item);
		अन्यथा
			ret = PTR_ERR(item);
	पूर्ण
	mutex_unlock(&subsys->su_mutex);

	kमुक्त(name);
	अगर (ret) अणु
		/*
		 * If ret != 0, then link_obj() was never called.
		 * There are no extra references to clean up.
		 */
		जाओ out_subsys_put;
	पूर्ण

	/*
	 * link_obj() has been called (via link_group() क्रम groups).
	 * From here on out, errors must clean that up.
	 */

	type = item->ci_type;
	अगर (!type) अणु
		ret = -EINVAL;
		जाओ out_unlink;
	पूर्ण

	new_item_owner = type->ct_owner;
	अगर (!try_module_get(new_item_owner)) अणु
		ret = -EINVAL;
		जाओ out_unlink;
	पूर्ण

	/*
	 * I hate करोing it this way, but अगर there is
	 * an error,  module_put() probably should
	 * happen after any cleanup.
	 */
	module_got = 1;

	/*
	 * Make racing सूची_हटाओ() fail अगर it did not tag parent with
	 * CONFIGFS_USET_DROPPING
	 * Note: अगर CONFIGFS_USET_DROPPING is alपढ़ोy set, attach_group() will
	 * fail and let सूची_हटाओ() terminate correctly
	 */
	spin_lock(&configfs_dirent_lock);
	/* This will make configfs_detach_prep() fail */
	sd->s_type |= CONFIGFS_USET_IN_MKसूची;
	spin_unlock(&configfs_dirent_lock);

	अगर (group)
		ret = configfs_attach_group(parent_item, item, dentry, frag);
	अन्यथा
		ret = configfs_attach_item(parent_item, item, dentry, frag);

	spin_lock(&configfs_dirent_lock);
	sd->s_type &= ~CONFIGFS_USET_IN_MKसूची;
	अगर (!ret)
		configfs_dir_set_पढ़ोy(dentry->d_fsdata);
	spin_unlock(&configfs_dirent_lock);

out_unlink:
	अगर (ret) अणु
		/* Tear करोwn everything we built up */
		mutex_lock(&subsys->su_mutex);

		client_disconnect_notअगरy(parent_item, item);
		अगर (group)
			unlink_group(group);
		अन्यथा
			unlink_obj(item);
		client_drop_item(parent_item, item);

		mutex_unlock(&subsys->su_mutex);

		अगर (module_got)
			module_put(new_item_owner);
	पूर्ण

out_subsys_put:
	अगर (ret)
		module_put(subsys_owner);

out_put:
	/*
	 * link_obj()/link_group() took a reference from child->parent,
	 * so the parent is safely pinned.  We can drop our working
	 * reference.
	 */
	config_item_put(parent_item);
	put_fragment(frag);

out:
	वापस ret;
पूर्ण

अटल पूर्णांक configfs_सूची_हटाओ(काष्ठा inode *dir, काष्ठा dentry *dentry)
अणु
	काष्ठा config_item *parent_item;
	काष्ठा config_item *item;
	काष्ठा configfs_subप्रणाली *subsys;
	काष्ठा configfs_dirent *sd;
	काष्ठा configfs_fragment *frag;
	काष्ठा module *subsys_owner = शून्य, *dead_item_owner = शून्य;
	पूर्णांक ret;

	sd = dentry->d_fsdata;
	अगर (sd->s_type & CONFIGFS_USET_DEFAULT)
		वापस -EPERM;

	/* Get a working ref until we have the child */
	parent_item = configfs_get_config_item(dentry->d_parent);
	subsys = to_config_group(parent_item)->cg_subsys;
	BUG_ON(!subsys);

	अगर (!parent_item->ci_type) अणु
		config_item_put(parent_item);
		वापस -EINVAL;
	पूर्ण

	/* configfs_सूची_गढ़ो() shouldn't have allowed this */
	BUG_ON(!subsys->su_group.cg_item.ci_type);
	subsys_owner = subsys->su_group.cg_item.ci_type->ct_owner;

	/*
	 * Ensure that no racing symlink() will make detach_prep() fail जबतक
	 * the new link is temporarily attached
	 */
	करो अणु
		काष्ठा dentry *रुको;

		mutex_lock(&configfs_symlink_mutex);
		spin_lock(&configfs_dirent_lock);
		/*
		 * Here's where we check for dependents.  We're रक्षित by
		 * configfs_dirent_lock.
		 * If no dependent, atomically tag the item as dropping.
		 */
		ret = sd->s_dependent_count ? -EBUSY : 0;
		अगर (!ret) अणु
			ret = configfs_detach_prep(dentry, &रुको);
			अगर (ret)
				configfs_detach_rollback(dentry);
		पूर्ण
		spin_unlock(&configfs_dirent_lock);
		mutex_unlock(&configfs_symlink_mutex);

		अगर (ret) अणु
			अगर (ret != -EAGAIN) अणु
				config_item_put(parent_item);
				वापस ret;
			पूर्ण

			/* Wait until the racing operation terminates */
			inode_lock(d_inode(रुको));
			inode_unlock(d_inode(रुको));
			dput(रुको);
		पूर्ण
	पूर्ण जबतक (ret == -EAGAIN);

	frag = sd->s_frag;
	अगर (करोwn_ग_लिखो_समाप्तable(&frag->frag_sem)) अणु
		spin_lock(&configfs_dirent_lock);
		configfs_detach_rollback(dentry);
		spin_unlock(&configfs_dirent_lock);
		config_item_put(parent_item);
		वापस -EINTR;
	पूर्ण
	frag->frag_dead = true;
	up_ग_लिखो(&frag->frag_sem);

	/* Get a working ref क्रम the duration of this function */
	item = configfs_get_config_item(dentry);

	/* Drop reference from above, item alपढ़ोy holds one. */
	config_item_put(parent_item);

	अगर (item->ci_type)
		dead_item_owner = item->ci_type->ct_owner;

	अगर (sd->s_type & CONFIGFS_USET_सूची) अणु
		configfs_detach_group(item);

		mutex_lock(&subsys->su_mutex);
		client_disconnect_notअगरy(parent_item, item);
		unlink_group(to_config_group(item));
	पूर्ण अन्यथा अणु
		configfs_detach_item(item);

		mutex_lock(&subsys->su_mutex);
		client_disconnect_notअगरy(parent_item, item);
		unlink_obj(item);
	पूर्ण

	client_drop_item(parent_item, item);
	mutex_unlock(&subsys->su_mutex);

	/* Drop our reference from above */
	config_item_put(item);

	module_put(dead_item_owner);
	module_put(subsys_owner);

	वापस 0;
पूर्ण

स्थिर काष्ठा inode_operations configfs_dir_inode_operations = अणु
	.सूची_गढ़ो		= configfs_सूची_गढ़ो,
	.सूची_हटाओ		= configfs_सूची_हटाओ,
	.symlink	= configfs_symlink,
	.unlink		= configfs_unlink,
	.lookup		= configfs_lookup,
	.setattr	= configfs_setattr,
पूर्ण;

स्थिर काष्ठा inode_operations configfs_root_inode_operations = अणु
	.lookup		= configfs_lookup,
	.setattr	= configfs_setattr,
पूर्ण;

अटल पूर्णांक configfs_dir_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा dentry * dentry = file->f_path.dentry;
	काष्ठा configfs_dirent * parent_sd = dentry->d_fsdata;
	पूर्णांक err;

	inode_lock(d_inode(dentry));
	/*
	 * Fake invisibility अगर dir beदीर्घs to a group/शेष groups hierarchy
	 * being attached
	 */
	err = -ENOENT;
	अगर (configfs_dirent_is_पढ़ोy(parent_sd)) अणु
		file->निजी_data = configfs_new_dirent(parent_sd, शून्य, 0, शून्य);
		अगर (IS_ERR(file->निजी_data))
			err = PTR_ERR(file->निजी_data);
		अन्यथा
			err = 0;
	पूर्ण
	inode_unlock(d_inode(dentry));

	वापस err;
पूर्ण

अटल पूर्णांक configfs_dir_बंद(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा dentry * dentry = file->f_path.dentry;
	काष्ठा configfs_dirent * cursor = file->निजी_data;

	inode_lock(d_inode(dentry));
	spin_lock(&configfs_dirent_lock);
	list_del_init(&cursor->s_sibling);
	spin_unlock(&configfs_dirent_lock);
	inode_unlock(d_inode(dentry));

	release_configfs_dirent(cursor);

	वापस 0;
पूर्ण

/* Relationship between s_mode and the DT_xxx types */
अटल अंतरभूत अचिन्हित अक्षर dt_type(काष्ठा configfs_dirent *sd)
अणु
	वापस (sd->s_mode >> 12) & 15;
पूर्ण

अटल पूर्णांक configfs_सूची_पढ़ो(काष्ठा file *file, काष्ठा dir_context *ctx)
अणु
	काष्ठा dentry *dentry = file->f_path.dentry;
	काष्ठा super_block *sb = dentry->d_sb;
	काष्ठा configfs_dirent * parent_sd = dentry->d_fsdata;
	काष्ठा configfs_dirent *cursor = file->निजी_data;
	काष्ठा list_head *p, *q = &cursor->s_sibling;
	ino_t ino = 0;

	अगर (!dir_emit_करोts(file, ctx))
		वापस 0;
	spin_lock(&configfs_dirent_lock);
	अगर (ctx->pos == 2)
		list_move(q, &parent_sd->s_children);
	क्रम (p = q->next; p != &parent_sd->s_children; p = p->next) अणु
		काष्ठा configfs_dirent *next;
		स्थिर अक्षर *name;
		पूर्णांक len;
		काष्ठा inode *inode = शून्य;

		next = list_entry(p, काष्ठा configfs_dirent, s_sibling);
		अगर (!next->s_element)
			जारी;

		/*
		 * We'll have a dentry and an inode क्रम
		 * PINNED items and क्रम खोलो attribute
		 * files.  We lock here to prevent a race
		 * with configfs_d_iput() clearing
		 * s_dentry beक्रमe calling iput().
		 *
		 * Why करो we go to the trouble?  If
		 * someone has an attribute file खोलो,
		 * the inode number should match until
		 * they बंद it.  Beyond that, we करोn't
		 * care.
		 */
		dentry = next->s_dentry;
		अगर (dentry)
			inode = d_inode(dentry);
		अगर (inode)
			ino = inode->i_ino;
		spin_unlock(&configfs_dirent_lock);
		अगर (!inode)
			ino = iunique(sb, 2);

		name = configfs_get_name(next);
		len = म_माप(name);

		अगर (!dir_emit(ctx, name, len, ino, dt_type(next)))
			वापस 0;

		spin_lock(&configfs_dirent_lock);
		list_move(q, p);
		p = q;
		ctx->pos++;
	पूर्ण
	spin_unlock(&configfs_dirent_lock);
	वापस 0;
पूर्ण

अटल loff_t configfs_dir_lseek(काष्ठा file *file, loff_t offset, पूर्णांक whence)
अणु
	काष्ठा dentry * dentry = file->f_path.dentry;

	चयन (whence) अणु
		हाल 1:
			offset += file->f_pos;
			fallthrough;
		हाल 0:
			अगर (offset >= 0)
				अवरोध;
			fallthrough;
		शेष:
			वापस -EINVAL;
	पूर्ण
	अगर (offset != file->f_pos) अणु
		file->f_pos = offset;
		अगर (file->f_pos >= 2) अणु
			काष्ठा configfs_dirent *sd = dentry->d_fsdata;
			काष्ठा configfs_dirent *cursor = file->निजी_data;
			काष्ठा list_head *p;
			loff_t n = file->f_pos - 2;

			spin_lock(&configfs_dirent_lock);
			list_del(&cursor->s_sibling);
			p = sd->s_children.next;
			जबतक (n && p != &sd->s_children) अणु
				काष्ठा configfs_dirent *next;
				next = list_entry(p, काष्ठा configfs_dirent,
						   s_sibling);
				अगर (next->s_element)
					n--;
				p = p->next;
			पूर्ण
			list_add_tail(&cursor->s_sibling, p);
			spin_unlock(&configfs_dirent_lock);
		पूर्ण
	पूर्ण
	वापस offset;
पूर्ण

स्थिर काष्ठा file_operations configfs_dir_operations = अणु
	.खोलो		= configfs_dir_खोलो,
	.release	= configfs_dir_बंद,
	.llseek		= configfs_dir_lseek,
	.पढ़ो		= generic_पढ़ो_dir,
	.iterate_shared	= configfs_सूची_पढ़ो,
पूर्ण;

/**
 * configfs_रेजिस्टर_group - creates a parent-child relation between two groups
 * @parent_group:	parent group
 * @group:		child group
 *
 * link groups, creates dentry क्रम the child and attaches it to the
 * parent dentry.
 *
 * Return: 0 on success, negative त्रुटि_सं code on error
 */
पूर्णांक configfs_रेजिस्टर_group(काष्ठा config_group *parent_group,
			    काष्ठा config_group *group)
अणु
	काष्ठा configfs_subप्रणाली *subsys = parent_group->cg_subsys;
	काष्ठा dentry *parent;
	काष्ठा configfs_fragment *frag;
	पूर्णांक ret;

	frag = new_fragment();
	अगर (!frag)
		वापस -ENOMEM;

	mutex_lock(&subsys->su_mutex);
	link_group(parent_group, group);
	mutex_unlock(&subsys->su_mutex);

	parent = parent_group->cg_item.ci_dentry;

	inode_lock_nested(d_inode(parent), I_MUTEX_PARENT);
	ret = create_शेष_group(parent_group, group, frag);
	अगर (ret)
		जाओ err_out;

	spin_lock(&configfs_dirent_lock);
	configfs_dir_set_पढ़ोy(group->cg_item.ci_dentry->d_fsdata);
	spin_unlock(&configfs_dirent_lock);
	inode_unlock(d_inode(parent));
	put_fragment(frag);
	वापस 0;
err_out:
	inode_unlock(d_inode(parent));
	mutex_lock(&subsys->su_mutex);
	unlink_group(group);
	mutex_unlock(&subsys->su_mutex);
	put_fragment(frag);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(configfs_रेजिस्टर_group);

/**
 * configfs_unरेजिस्टर_group() - unरेजिस्टरs a child group from its parent
 * @group: parent group to be unरेजिस्टरed
 *
 * Unकरोes configfs_रेजिस्टर_group()
 */
व्योम configfs_unरेजिस्टर_group(काष्ठा config_group *group)
अणु
	काष्ठा configfs_subप्रणाली *subsys = group->cg_subsys;
	काष्ठा dentry *dentry = group->cg_item.ci_dentry;
	काष्ठा dentry *parent = group->cg_item.ci_parent->ci_dentry;
	काष्ठा configfs_dirent *sd = dentry->d_fsdata;
	काष्ठा configfs_fragment *frag = sd->s_frag;

	करोwn_ग_लिखो(&frag->frag_sem);
	frag->frag_dead = true;
	up_ग_लिखो(&frag->frag_sem);

	inode_lock_nested(d_inode(parent), I_MUTEX_PARENT);
	spin_lock(&configfs_dirent_lock);
	configfs_detach_prep(dentry, शून्य);
	spin_unlock(&configfs_dirent_lock);

	configfs_detach_group(&group->cg_item);
	d_inode(dentry)->i_flags |= S_DEAD;
	करोnt_mount(dentry);
	fsnotअगरy_सूची_हटाओ(d_inode(parent), dentry);
	d_delete(dentry);
	inode_unlock(d_inode(parent));

	dput(dentry);

	mutex_lock(&subsys->su_mutex);
	unlink_group(group);
	mutex_unlock(&subsys->su_mutex);
पूर्ण
EXPORT_SYMBOL(configfs_unरेजिस्टर_group);

/**
 * configfs_रेजिस्टर_शेष_group() - allocates and रेजिस्टरs a child group
 * @parent_group:	parent group
 * @name:		child group name
 * @item_type:		child item type description
 *
 * boilerplate to allocate and रेजिस्टर a child group with its parent. We need
 * kzalloc'ed memory because child's शेष_group is initially empty.
 *
 * Return: allocated config group or ERR_PTR() on error
 */
काष्ठा config_group *
configfs_रेजिस्टर_शेष_group(काष्ठा config_group *parent_group,
				स्थिर अक्षर *name,
				स्थिर काष्ठा config_item_type *item_type)
अणु
	पूर्णांक ret;
	काष्ठा config_group *group;

	group = kzalloc(माप(*group), GFP_KERNEL);
	अगर (!group)
		वापस ERR_PTR(-ENOMEM);
	config_group_init_type_name(group, name, item_type);

	ret = configfs_रेजिस्टर_group(parent_group, group);
	अगर (ret) अणु
		kमुक्त(group);
		वापस ERR_PTR(ret);
	पूर्ण
	वापस group;
पूर्ण
EXPORT_SYMBOL(configfs_रेजिस्टर_शेष_group);

/**
 * configfs_unरेजिस्टर_शेष_group() - unरेजिस्टरs and मुक्तs a child group
 * @group:	the group to act on
 */
व्योम configfs_unरेजिस्टर_शेष_group(काष्ठा config_group *group)
अणु
	configfs_unरेजिस्टर_group(group);
	kमुक्त(group);
पूर्ण
EXPORT_SYMBOL(configfs_unरेजिस्टर_शेष_group);

पूर्णांक configfs_रेजिस्टर_subप्रणाली(काष्ठा configfs_subप्रणाली *subsys)
अणु
	पूर्णांक err;
	काष्ठा config_group *group = &subsys->su_group;
	काष्ठा dentry *dentry;
	काष्ठा dentry *root;
	काष्ठा configfs_dirent *sd;
	काष्ठा configfs_fragment *frag;

	frag = new_fragment();
	अगर (!frag)
		वापस -ENOMEM;

	root = configfs_pin_fs();
	अगर (IS_ERR(root)) अणु
		put_fragment(frag);
		वापस PTR_ERR(root);
	पूर्ण

	अगर (!group->cg_item.ci_name)
		group->cg_item.ci_name = group->cg_item.ci_namebuf;

	sd = root->d_fsdata;
	link_group(to_config_group(sd->s_element), group);

	inode_lock_nested(d_inode(root), I_MUTEX_PARENT);

	err = -ENOMEM;
	dentry = d_alloc_name(root, group->cg_item.ci_name);
	अगर (dentry) अणु
		d_add(dentry, शून्य);

		err = configfs_attach_group(sd->s_element, &group->cg_item,
					    dentry, frag);
		अगर (err) अणु
			BUG_ON(d_inode(dentry));
			d_drop(dentry);
			dput(dentry);
		पूर्ण अन्यथा अणु
			spin_lock(&configfs_dirent_lock);
			configfs_dir_set_पढ़ोy(dentry->d_fsdata);
			spin_unlock(&configfs_dirent_lock);
		पूर्ण
	पूर्ण

	inode_unlock(d_inode(root));

	अगर (err) अणु
		unlink_group(group);
		configfs_release_fs();
	पूर्ण
	put_fragment(frag);

	वापस err;
पूर्ण

व्योम configfs_unरेजिस्टर_subप्रणाली(काष्ठा configfs_subप्रणाली *subsys)
अणु
	काष्ठा config_group *group = &subsys->su_group;
	काष्ठा dentry *dentry = group->cg_item.ci_dentry;
	काष्ठा dentry *root = dentry->d_sb->s_root;
	काष्ठा configfs_dirent *sd = dentry->d_fsdata;
	काष्ठा configfs_fragment *frag = sd->s_frag;

	अगर (dentry->d_parent != root) अणु
		pr_err("Tried to unregister non-subsystem!\n");
		वापस;
	पूर्ण

	करोwn_ग_लिखो(&frag->frag_sem);
	frag->frag_dead = true;
	up_ग_लिखो(&frag->frag_sem);

	inode_lock_nested(d_inode(root),
			  I_MUTEX_PARENT);
	inode_lock_nested(d_inode(dentry), I_MUTEX_CHILD);
	mutex_lock(&configfs_symlink_mutex);
	spin_lock(&configfs_dirent_lock);
	अगर (configfs_detach_prep(dentry, शून्य)) अणु
		pr_err("Tried to unregister non-empty subsystem!\n");
	पूर्ण
	spin_unlock(&configfs_dirent_lock);
	mutex_unlock(&configfs_symlink_mutex);
	configfs_detach_group(&group->cg_item);
	d_inode(dentry)->i_flags |= S_DEAD;
	करोnt_mount(dentry);
	fsnotअगरy_सूची_हटाओ(d_inode(root), dentry);
	inode_unlock(d_inode(dentry));

	d_delete(dentry);

	inode_unlock(d_inode(root));

	dput(dentry);

	unlink_group(group);
	configfs_release_fs();
पूर्ण

EXPORT_SYMBOL(configfs_रेजिस्टर_subप्रणाली);
EXPORT_SYMBOL(configfs_unरेजिस्टर_subप्रणाली);
