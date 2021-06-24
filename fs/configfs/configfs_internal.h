<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * configfs_पूर्णांकernal.h - Internal stuff क्रम configfs
 *
 * Based on sysfs:
 * 	sysfs is Copyright (C) 2001, 2002, 2003 Patrick Mochel
 *
 * configfs Copyright (C) 2005 Oracle.  All rights reserved.
 */

#अगर_घोषित pr_fmt
#अघोषित pr_fmt
#पूर्ण_अगर

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/slab.h>
#समावेश <linux/list.h>
#समावेश <linux/spinlock.h>

काष्ठा configfs_fragment अणु
	atomic_t frag_count;
	काष्ठा rw_semaphore frag_sem;
	bool frag_dead;
पूर्ण;

व्योम put_fragment(काष्ठा configfs_fragment *);
काष्ठा configfs_fragment *get_fragment(काष्ठा configfs_fragment *);

काष्ठा configfs_dirent अणु
	atomic_t		s_count;
	पूर्णांक			s_dependent_count;
	काष्ठा list_head	s_sibling;
	काष्ठा list_head	s_children;
	पूर्णांक			s_links;
	व्योम			* s_element;
	पूर्णांक			s_type;
	umode_t			s_mode;
	काष्ठा dentry		* s_dentry;
	काष्ठा iattr		* s_iattr;
#अगर_घोषित CONFIG_LOCKDEP
	पूर्णांक			s_depth;
#पूर्ण_अगर
	काष्ठा configfs_fragment *s_frag;
पूर्ण;

#घोषणा CONFIGFS_ROOT		0x0001
#घोषणा CONFIGFS_सूची		0x0002
#घोषणा CONFIGFS_ITEM_ATTR	0x0004
#घोषणा CONFIGFS_ITEM_BIN_ATTR	0x0008
#घोषणा CONFIGFS_ITEM_LINK	0x0020
#घोषणा CONFIGFS_USET_सूची	0x0040
#घोषणा CONFIGFS_USET_DEFAULT	0x0080
#घोषणा CONFIGFS_USET_DROPPING	0x0100
#घोषणा CONFIGFS_USET_IN_MKसूची	0x0200
#घोषणा CONFIGFS_USET_CREATING	0x0400
#घोषणा CONFIGFS_NOT_PINNED	(CONFIGFS_ITEM_ATTR | CONFIGFS_ITEM_BIN_ATTR)

बाह्य काष्ठा mutex configfs_symlink_mutex;
बाह्य spinlock_t configfs_dirent_lock;

बाह्य काष्ठा kmem_cache *configfs_dir_cachep;

बाह्य पूर्णांक configfs_is_root(काष्ठा config_item *item);

बाह्य काष्ठा inode * configfs_new_inode(umode_t mode, काष्ठा configfs_dirent *, काष्ठा super_block *);
बाह्य काष्ठा inode *configfs_create(काष्ठा dentry *, umode_t mode);

बाह्य पूर्णांक configfs_create_file(काष्ठा config_item *, स्थिर काष्ठा configfs_attribute *);
बाह्य पूर्णांक configfs_create_bin_file(काष्ठा config_item *,
				    स्थिर काष्ठा configfs_bin_attribute *);
बाह्य पूर्णांक configfs_make_dirent(काष्ठा configfs_dirent *, काष्ठा dentry *,
				व्योम *, umode_t, पूर्णांक, काष्ठा configfs_fragment *);
बाह्य पूर्णांक configfs_dirent_is_पढ़ोy(काष्ठा configfs_dirent *);

बाह्य व्योम configfs_hash_and_हटाओ(काष्ठा dentry * dir, स्थिर अक्षर * name);

बाह्य स्थिर अचिन्हित अक्षर * configfs_get_name(काष्ठा configfs_dirent *sd);
बाह्य व्योम configfs_drop_dentry(काष्ठा configfs_dirent *sd, काष्ठा dentry *parent);
बाह्य पूर्णांक configfs_setattr(काष्ठा user_namespace *mnt_userns,
			    काष्ठा dentry *dentry, काष्ठा iattr *iattr);

बाह्य काष्ठा dentry *configfs_pin_fs(व्योम);
बाह्य व्योम configfs_release_fs(व्योम);

बाह्य स्थिर काष्ठा file_operations configfs_dir_operations;
बाह्य स्थिर काष्ठा file_operations configfs_file_operations;
बाह्य स्थिर काष्ठा file_operations configfs_bin_file_operations;
बाह्य स्थिर काष्ठा inode_operations configfs_dir_inode_operations;
बाह्य स्थिर काष्ठा inode_operations configfs_root_inode_operations;
बाह्य स्थिर काष्ठा inode_operations configfs_symlink_inode_operations;
बाह्य स्थिर काष्ठा dentry_operations configfs_dentry_ops;

बाह्य पूर्णांक configfs_symlink(काष्ठा user_namespace *mnt_userns,
			    काष्ठा inode *dir, काष्ठा dentry *dentry,
			    स्थिर अक्षर *symname);
बाह्य पूर्णांक configfs_unlink(काष्ठा inode *dir, काष्ठा dentry *dentry);

पूर्णांक configfs_create_link(काष्ठा configfs_dirent *target, काष्ठा dentry *parent,
		काष्ठा dentry *dentry, अक्षर *body);

अटल अंतरभूत काष्ठा config_item * to_item(काष्ठा dentry * dentry)
अणु
	काष्ठा configfs_dirent * sd = dentry->d_fsdata;
	वापस ((काष्ठा config_item *) sd->s_element);
पूर्ण

अटल अंतरभूत काष्ठा configfs_attribute * to_attr(काष्ठा dentry * dentry)
अणु
	काष्ठा configfs_dirent * sd = dentry->d_fsdata;
	वापस ((काष्ठा configfs_attribute *) sd->s_element);
पूर्ण

अटल अंतरभूत काष्ठा configfs_bin_attribute *to_bin_attr(काष्ठा dentry *dentry)
अणु
	काष्ठा configfs_attribute *attr = to_attr(dentry);

	वापस container_of(attr, काष्ठा configfs_bin_attribute, cb_attr);
पूर्ण

अटल अंतरभूत काष्ठा config_item *configfs_get_config_item(काष्ठा dentry *dentry)
अणु
	काष्ठा config_item * item = शून्य;

	spin_lock(&dentry->d_lock);
	अगर (!d_unhashed(dentry)) अणु
		काष्ठा configfs_dirent * sd = dentry->d_fsdata;
		item = config_item_get(sd->s_element);
	पूर्ण
	spin_unlock(&dentry->d_lock);

	वापस item;
पूर्ण

अटल अंतरभूत व्योम release_configfs_dirent(काष्ठा configfs_dirent * sd)
अणु
	अगर (!(sd->s_type & CONFIGFS_ROOT)) अणु
		kमुक्त(sd->s_iattr);
		put_fragment(sd->s_frag);
		kmem_cache_मुक्त(configfs_dir_cachep, sd);
	पूर्ण
पूर्ण

अटल अंतरभूत काष्ठा configfs_dirent * configfs_get(काष्ठा configfs_dirent * sd)
अणु
	अगर (sd) अणु
		WARN_ON(!atomic_पढ़ो(&sd->s_count));
		atomic_inc(&sd->s_count);
	पूर्ण
	वापस sd;
पूर्ण

अटल अंतरभूत व्योम configfs_put(काष्ठा configfs_dirent * sd)
अणु
	WARN_ON(!atomic_पढ़ो(&sd->s_count));
	अगर (atomic_dec_and_test(&sd->s_count))
		release_configfs_dirent(sd);
पूर्ण

