<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * fs/sysfs/file.c - sysfs regular (text) file implementation
 *
 * Copyright (c) 2001-3 Patrick Mochel
 * Copyright (c) 2007 SUSE Linux Products GmbH
 * Copyright (c) 2007 Tejun Heo <teheo@suse.de>
 *
 * Please see Documentation/fileप्रणालीs/sysfs.rst क्रम more inक्रमmation.
 */

#समावेश <linux/module.h>
#समावेश <linux/kobject.h>
#समावेश <linux/slab.h>
#समावेश <linux/list.h>
#समावेश <linux/mutex.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/mm.h>

#समावेश "sysfs.h"

/*
 * Determine ktype->sysfs_ops क्रम the given kernfs_node.  This function
 * must be called जबतक holding an active reference.
 */
अटल स्थिर काष्ठा sysfs_ops *sysfs_file_ops(काष्ठा kernfs_node *kn)
अणु
	काष्ठा kobject *kobj = kn->parent->priv;

	अगर (kn->flags & KERNFS_LOCKDEP)
		lockdep_निश्चित_held(kn);
	वापस kobj->ktype ? kobj->ktype->sysfs_ops : शून्य;
पूर्ण

/*
 * Reads on sysfs are handled through seq_file, which takes care of hairy
 * details like buffering and seeking.  The following function pipes
 * sysfs_ops->show() result through seq_file.
 */
अटल पूर्णांक sysfs_kf_seq_show(काष्ठा seq_file *sf, व्योम *v)
अणु
	काष्ठा kernfs_खोलो_file *of = sf->निजी;
	काष्ठा kobject *kobj = of->kn->parent->priv;
	स्थिर काष्ठा sysfs_ops *ops = sysfs_file_ops(of->kn);
	sमाप_प्रकार count;
	अक्षर *buf;

	/* acquire buffer and ensure that it's >= PAGE_SIZE and clear */
	count = seq_get_buf(sf, &buf);
	अगर (count < PAGE_SIZE) अणु
		seq_commit(sf, -1);
		वापस 0;
	पूर्ण
	स_रखो(buf, 0, PAGE_SIZE);

	/*
	 * Invoke show().  Control may reach here via seq file lseek even
	 * अगर @ops->show() isn't implemented.
	 */
	अगर (ops->show) अणु
		count = ops->show(kobj, of->kn->priv, buf);
		अगर (count < 0)
			वापस count;
	पूर्ण

	/*
	 * The code works fine with PAGE_SIZE वापस but it's likely to
	 * indicate truncated result or overflow in normal use हालs.
	 */
	अगर (count >= (sमाप_प्रकार)PAGE_SIZE) अणु
		prपूर्णांकk("fill_read_buffer: %pS returned bad count\n",
				ops->show);
		/* Try to struggle aदीर्घ */
		count = PAGE_SIZE - 1;
	पूर्ण
	seq_commit(sf, count);
	वापस 0;
पूर्ण

अटल sमाप_प्रकार sysfs_kf_bin_पढ़ो(काष्ठा kernfs_खोलो_file *of, अक्षर *buf,
				 माप_प्रकार count, loff_t pos)
अणु
	काष्ठा bin_attribute *battr = of->kn->priv;
	काष्ठा kobject *kobj = of->kn->parent->priv;
	loff_t size = file_inode(of->file)->i_size;

	अगर (!count)
		वापस 0;

	अगर (size) अणु
		अगर (pos >= size)
			वापस 0;
		अगर (pos + count > size)
			count = size - pos;
	पूर्ण

	अगर (!battr->पढ़ो)
		वापस -EIO;

	वापस battr->पढ़ो(of->file, kobj, battr, buf, pos, count);
पूर्ण

/* kernfs पढ़ो callback क्रम regular sysfs files with pre-alloc */
अटल sमाप_प्रकार sysfs_kf_पढ़ो(काष्ठा kernfs_खोलो_file *of, अक्षर *buf,
			     माप_प्रकार count, loff_t pos)
अणु
	स्थिर काष्ठा sysfs_ops *ops = sysfs_file_ops(of->kn);
	काष्ठा kobject *kobj = of->kn->parent->priv;
	sमाप_प्रकार len;

	/*
	 * If buf != of->pपुनः_स्मृति_buf, we करोn't know how
	 * large it is, so cannot safely pass it to ->show
	 */
	अगर (WARN_ON_ONCE(buf != of->pपुनः_स्मृति_buf))
		वापस 0;
	len = ops->show(kobj, of->kn->priv, buf);
	अगर (len < 0)
		वापस len;
	अगर (pos) अणु
		अगर (len <= pos)
			वापस 0;
		len -= pos;
		स_हटाओ(buf, buf + pos, len);
	पूर्ण
	वापस min_t(sमाप_प्रकार, count, len);
पूर्ण

/* kernfs ग_लिखो callback क्रम regular sysfs files */
अटल sमाप_प्रकार sysfs_kf_ग_लिखो(काष्ठा kernfs_खोलो_file *of, अक्षर *buf,
			      माप_प्रकार count, loff_t pos)
अणु
	स्थिर काष्ठा sysfs_ops *ops = sysfs_file_ops(of->kn);
	काष्ठा kobject *kobj = of->kn->parent->priv;

	अगर (!count)
		वापस 0;

	वापस ops->store(kobj, of->kn->priv, buf, count);
पूर्ण

/* kernfs ग_लिखो callback क्रम bin sysfs files */
अटल sमाप_प्रकार sysfs_kf_bin_ग_लिखो(काष्ठा kernfs_खोलो_file *of, अक्षर *buf,
				  माप_प्रकार count, loff_t pos)
अणु
	काष्ठा bin_attribute *battr = of->kn->priv;
	काष्ठा kobject *kobj = of->kn->parent->priv;
	loff_t size = file_inode(of->file)->i_size;

	अगर (size) अणु
		अगर (size <= pos)
			वापस -EFBIG;
		count = min_t(sमाप_प्रकार, count, size - pos);
	पूर्ण
	अगर (!count)
		वापस 0;

	अगर (!battr->ग_लिखो)
		वापस -EIO;

	वापस battr->ग_लिखो(of->file, kobj, battr, buf, pos, count);
पूर्ण

अटल पूर्णांक sysfs_kf_bin_mmap(काष्ठा kernfs_खोलो_file *of,
			     काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा bin_attribute *battr = of->kn->priv;
	काष्ठा kobject *kobj = of->kn->parent->priv;

	वापस battr->mmap(of->file, kobj, battr, vma);
पूर्ण

अटल पूर्णांक sysfs_kf_bin_खोलो(काष्ठा kernfs_खोलो_file *of)
अणु
	काष्ठा bin_attribute *battr = of->kn->priv;

	अगर (battr->mapping)
		of->file->f_mapping = battr->mapping;

	वापस 0;
पूर्ण

व्योम sysfs_notअगरy(काष्ठा kobject *kobj, स्थिर अक्षर *dir, स्थिर अक्षर *attr)
अणु
	काष्ठा kernfs_node *kn = kobj->sd, *पंचांगp;

	अगर (kn && dir)
		kn = kernfs_find_and_get(kn, dir);
	अन्यथा
		kernfs_get(kn);

	अगर (kn && attr) अणु
		पंचांगp = kernfs_find_and_get(kn, attr);
		kernfs_put(kn);
		kn = पंचांगp;
	पूर्ण

	अगर (kn) अणु
		kernfs_notअगरy(kn);
		kernfs_put(kn);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(sysfs_notअगरy);

अटल स्थिर काष्ठा kernfs_ops sysfs_file_kfops_empty = अणु
पूर्ण;

अटल स्थिर काष्ठा kernfs_ops sysfs_file_kfops_ro = अणु
	.seq_show	= sysfs_kf_seq_show,
पूर्ण;

अटल स्थिर काष्ठा kernfs_ops sysfs_file_kfops_wo = अणु
	.ग_लिखो		= sysfs_kf_ग_लिखो,
पूर्ण;

अटल स्थिर काष्ठा kernfs_ops sysfs_file_kfops_rw = अणु
	.seq_show	= sysfs_kf_seq_show,
	.ग_लिखो		= sysfs_kf_ग_लिखो,
पूर्ण;

अटल स्थिर काष्ठा kernfs_ops sysfs_pपुनः_स्मृति_kfops_ro = अणु
	.पढ़ो		= sysfs_kf_पढ़ो,
	.pपुनः_स्मृति	= true,
पूर्ण;

अटल स्थिर काष्ठा kernfs_ops sysfs_pपुनः_स्मृति_kfops_wo = अणु
	.ग_लिखो		= sysfs_kf_ग_लिखो,
	.pपुनः_स्मृति	= true,
पूर्ण;

अटल स्थिर काष्ठा kernfs_ops sysfs_pपुनः_स्मृति_kfops_rw = अणु
	.पढ़ो		= sysfs_kf_पढ़ो,
	.ग_लिखो		= sysfs_kf_ग_लिखो,
	.pपुनः_स्मृति	= true,
पूर्ण;

अटल स्थिर काष्ठा kernfs_ops sysfs_bin_kfops_ro = अणु
	.पढ़ो		= sysfs_kf_bin_पढ़ो,
पूर्ण;

अटल स्थिर काष्ठा kernfs_ops sysfs_bin_kfops_wo = अणु
	.ग_लिखो		= sysfs_kf_bin_ग_लिखो,
पूर्ण;

अटल स्थिर काष्ठा kernfs_ops sysfs_bin_kfops_rw = अणु
	.पढ़ो		= sysfs_kf_bin_पढ़ो,
	.ग_लिखो		= sysfs_kf_bin_ग_लिखो,
पूर्ण;

अटल स्थिर काष्ठा kernfs_ops sysfs_bin_kfops_mmap = अणु
	.पढ़ो		= sysfs_kf_bin_पढ़ो,
	.ग_लिखो		= sysfs_kf_bin_ग_लिखो,
	.mmap		= sysfs_kf_bin_mmap,
	.खोलो		= sysfs_kf_bin_खोलो,
पूर्ण;

पूर्णांक sysfs_add_file_mode_ns(काष्ठा kernfs_node *parent,
			   स्थिर काष्ठा attribute *attr, bool is_bin,
			   umode_t mode, kuid_t uid, kgid_t gid, स्थिर व्योम *ns)
अणु
	काष्ठा lock_class_key *key = शून्य;
	स्थिर काष्ठा kernfs_ops *ops;
	काष्ठा kernfs_node *kn;
	loff_t size;

	अगर (!is_bin) अणु
		काष्ठा kobject *kobj = parent->priv;
		स्थिर काष्ठा sysfs_ops *sysfs_ops = kobj->ktype->sysfs_ops;

		/* every kobject with an attribute needs a ktype asचिन्हित */
		अगर (WARN(!sysfs_ops, KERN_ERR
			 "missing sysfs attribute operations for kobject: %s\n",
			 kobject_name(kobj)))
			वापस -EINVAL;

		अगर (sysfs_ops->show && sysfs_ops->store) अणु
			अगर (mode & SYSFS_PREALLOC)
				ops = &sysfs_pपुनः_स्मृति_kfops_rw;
			अन्यथा
				ops = &sysfs_file_kfops_rw;
		पूर्ण अन्यथा अगर (sysfs_ops->show) अणु
			अगर (mode & SYSFS_PREALLOC)
				ops = &sysfs_pपुनः_स्मृति_kfops_ro;
			अन्यथा
				ops = &sysfs_file_kfops_ro;
		पूर्ण अन्यथा अगर (sysfs_ops->store) अणु
			अगर (mode & SYSFS_PREALLOC)
				ops = &sysfs_pपुनः_स्मृति_kfops_wo;
			अन्यथा
				ops = &sysfs_file_kfops_wo;
		पूर्ण अन्यथा
			ops = &sysfs_file_kfops_empty;

		size = PAGE_SIZE;
	पूर्ण अन्यथा अणु
		काष्ठा bin_attribute *battr = (व्योम *)attr;

		अगर (battr->mmap)
			ops = &sysfs_bin_kfops_mmap;
		अन्यथा अगर (battr->पढ़ो && battr->ग_लिखो)
			ops = &sysfs_bin_kfops_rw;
		अन्यथा अगर (battr->पढ़ो)
			ops = &sysfs_bin_kfops_ro;
		अन्यथा अगर (battr->ग_लिखो)
			ops = &sysfs_bin_kfops_wo;
		अन्यथा
			ops = &sysfs_file_kfops_empty;

		size = battr->size;
	पूर्ण

#अगर_घोषित CONFIG_DEBUG_LOCK_ALLOC
	अगर (!attr->ignore_lockdep)
		key = attr->key ?: (काष्ठा lock_class_key *)&attr->skey;
#पूर्ण_अगर

	kn = __kernfs_create_file(parent, attr->name, mode & 0777, uid, gid,
				  size, ops, (व्योम *)attr, ns, key);
	अगर (IS_ERR(kn)) अणु
		अगर (PTR_ERR(kn) == -EEXIST)
			sysfs_warn_dup(parent, attr->name);
		वापस PTR_ERR(kn);
	पूर्ण
	वापस 0;
पूर्ण

/**
 * sysfs_create_file_ns - create an attribute file क्रम an object with custom ns
 * @kobj: object we're creating क्रम
 * @attr: attribute descriptor
 * @ns: namespace the new file should beदीर्घ to
 */
पूर्णांक sysfs_create_file_ns(काष्ठा kobject *kobj, स्थिर काष्ठा attribute *attr,
			 स्थिर व्योम *ns)
अणु
	kuid_t uid;
	kgid_t gid;

	अगर (WARN_ON(!kobj || !kobj->sd || !attr))
		वापस -EINVAL;

	kobject_get_ownership(kobj, &uid, &gid);
	वापस sysfs_add_file_mode_ns(kobj->sd, attr, false, attr->mode,
				      uid, gid, ns);

पूर्ण
EXPORT_SYMBOL_GPL(sysfs_create_file_ns);

पूर्णांक sysfs_create_files(काष्ठा kobject *kobj, स्थिर काष्ठा attribute * स्थिर *ptr)
अणु
	पूर्णांक err = 0;
	पूर्णांक i;

	क्रम (i = 0; ptr[i] && !err; i++)
		err = sysfs_create_file(kobj, ptr[i]);
	अगर (err)
		जबतक (--i >= 0)
			sysfs_हटाओ_file(kobj, ptr[i]);
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(sysfs_create_files);

/**
 * sysfs_add_file_to_group - add an attribute file to a pre-existing group.
 * @kobj: object we're acting क्रम.
 * @attr: attribute descriptor.
 * @group: group name.
 */
पूर्णांक sysfs_add_file_to_group(काष्ठा kobject *kobj,
		स्थिर काष्ठा attribute *attr, स्थिर अक्षर *group)
अणु
	काष्ठा kernfs_node *parent;
	kuid_t uid;
	kgid_t gid;
	पूर्णांक error;

	अगर (group) अणु
		parent = kernfs_find_and_get(kobj->sd, group);
	पूर्ण अन्यथा अणु
		parent = kobj->sd;
		kernfs_get(parent);
	पूर्ण

	अगर (!parent)
		वापस -ENOENT;

	kobject_get_ownership(kobj, &uid, &gid);
	error = sysfs_add_file_mode_ns(parent, attr, false,
				       attr->mode, uid, gid, शून्य);
	kernfs_put(parent);

	वापस error;
पूर्ण
EXPORT_SYMBOL_GPL(sysfs_add_file_to_group);

/**
 * sysfs_chmod_file - update the modअगरied mode value on an object attribute.
 * @kobj: object we're acting क्रम.
 * @attr: attribute descriptor.
 * @mode: file permissions.
 *
 */
पूर्णांक sysfs_chmod_file(काष्ठा kobject *kobj, स्थिर काष्ठा attribute *attr,
		     umode_t mode)
अणु
	काष्ठा kernfs_node *kn;
	काष्ठा iattr newattrs;
	पूर्णांक rc;

	kn = kernfs_find_and_get(kobj->sd, attr->name);
	अगर (!kn)
		वापस -ENOENT;

	newattrs.ia_mode = (mode & S_IALLUGO) | (kn->mode & ~S_IALLUGO);
	newattrs.ia_valid = ATTR_MODE;

	rc = kernfs_setattr(kn, &newattrs);

	kernfs_put(kn);
	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(sysfs_chmod_file);

/**
 * sysfs_अवरोध_active_protection - अवरोध "active" protection
 * @kobj: The kernel object @attr is associated with.
 * @attr: The attribute to अवरोध the "active" protection क्रम.
 *
 * With sysfs, just like kernfs, deletion of an attribute is postponed until
 * all active .show() and .store() callbacks have finished unless this function
 * is called. Hence this function is useful in methods that implement self
 * deletion.
 */
काष्ठा kernfs_node *sysfs_अवरोध_active_protection(काष्ठा kobject *kobj,
						  स्थिर काष्ठा attribute *attr)
अणु
	काष्ठा kernfs_node *kn;

	kobject_get(kobj);
	kn = kernfs_find_and_get(kobj->sd, attr->name);
	अगर (kn)
		kernfs_अवरोध_active_protection(kn);
	वापस kn;
पूर्ण
EXPORT_SYMBOL_GPL(sysfs_अवरोध_active_protection);

/**
 * sysfs_unअवरोध_active_protection - restore "active" protection
 * @kn: Poपूर्णांकer वापसed by sysfs_अवरोध_active_protection().
 *
 * Unकरो the effects of sysfs_अवरोध_active_protection(). Since this function
 * calls kernfs_put() on the kernfs node that corresponds to the 'attr'
 * argument passed to sysfs_अवरोध_active_protection() that attribute may have
 * been हटाओd between the sysfs_अवरोध_active_protection() and
 * sysfs_unअवरोध_active_protection() calls, it is not safe to access @kn after
 * this function has वापसed.
 */
व्योम sysfs_unअवरोध_active_protection(काष्ठा kernfs_node *kn)
अणु
	काष्ठा kobject *kobj = kn->parent->priv;

	kernfs_unअवरोध_active_protection(kn);
	kernfs_put(kn);
	kobject_put(kobj);
पूर्ण
EXPORT_SYMBOL_GPL(sysfs_unअवरोध_active_protection);

/**
 * sysfs_हटाओ_file_ns - हटाओ an object attribute with a custom ns tag
 * @kobj: object we're acting क्रम
 * @attr: attribute descriptor
 * @ns: namespace tag of the file to हटाओ
 *
 * Hash the attribute name and namespace tag and समाप्त the victim.
 */
व्योम sysfs_हटाओ_file_ns(काष्ठा kobject *kobj, स्थिर काष्ठा attribute *attr,
			  स्थिर व्योम *ns)
अणु
	काष्ठा kernfs_node *parent = kobj->sd;

	kernfs_हटाओ_by_name_ns(parent, attr->name, ns);
पूर्ण
EXPORT_SYMBOL_GPL(sysfs_हटाओ_file_ns);

/**
 * sysfs_हटाओ_file_self - हटाओ an object attribute from its own method
 * @kobj: object we're acting क्रम
 * @attr: attribute descriptor
 *
 * See kernfs_हटाओ_self() क्रम details.
 */
bool sysfs_हटाओ_file_self(काष्ठा kobject *kobj, स्थिर काष्ठा attribute *attr)
अणु
	काष्ठा kernfs_node *parent = kobj->sd;
	काष्ठा kernfs_node *kn;
	bool ret;

	kn = kernfs_find_and_get(parent, attr->name);
	अगर (WARN_ON_ONCE(!kn))
		वापस false;

	ret = kernfs_हटाओ_self(kn);

	kernfs_put(kn);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(sysfs_हटाओ_file_self);

व्योम sysfs_हटाओ_files(काष्ठा kobject *kobj, स्थिर काष्ठा attribute * स्थिर *ptr)
अणु
	पूर्णांक i;

	क्रम (i = 0; ptr[i]; i++)
		sysfs_हटाओ_file(kobj, ptr[i]);
पूर्ण
EXPORT_SYMBOL_GPL(sysfs_हटाओ_files);

/**
 * sysfs_हटाओ_file_from_group - हटाओ an attribute file from a group.
 * @kobj: object we're acting क्रम.
 * @attr: attribute descriptor.
 * @group: group name.
 */
व्योम sysfs_हटाओ_file_from_group(काष्ठा kobject *kobj,
		स्थिर काष्ठा attribute *attr, स्थिर अक्षर *group)
अणु
	काष्ठा kernfs_node *parent;

	अगर (group) अणु
		parent = kernfs_find_and_get(kobj->sd, group);
	पूर्ण अन्यथा अणु
		parent = kobj->sd;
		kernfs_get(parent);
	पूर्ण

	अगर (parent) अणु
		kernfs_हटाओ_by_name(parent, attr->name);
		kernfs_put(parent);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(sysfs_हटाओ_file_from_group);

/**
 *	sysfs_create_bin_file - create binary file क्रम object.
 *	@kobj:	object.
 *	@attr:	attribute descriptor.
 */
पूर्णांक sysfs_create_bin_file(काष्ठा kobject *kobj,
			  स्थिर काष्ठा bin_attribute *attr)
अणु
	kuid_t uid;
	kgid_t gid;

	अगर (WARN_ON(!kobj || !kobj->sd || !attr))
		वापस -EINVAL;

	kobject_get_ownership(kobj, &uid, &gid);
	वापस sysfs_add_file_mode_ns(kobj->sd, &attr->attr, true,
				      attr->attr.mode, uid, gid, शून्य);
पूर्ण
EXPORT_SYMBOL_GPL(sysfs_create_bin_file);

/**
 *	sysfs_हटाओ_bin_file - हटाओ binary file क्रम object.
 *	@kobj:	object.
 *	@attr:	attribute descriptor.
 */
व्योम sysfs_हटाओ_bin_file(काष्ठा kobject *kobj,
			   स्थिर काष्ठा bin_attribute *attr)
अणु
	kernfs_हटाओ_by_name(kobj->sd, attr->attr.name);
पूर्ण
EXPORT_SYMBOL_GPL(sysfs_हटाओ_bin_file);

अटल पूर्णांक पूर्णांकernal_change_owner(काष्ठा kernfs_node *kn, kuid_t kuid,
				 kgid_t kgid)
अणु
	काष्ठा iattr newattrs = अणु
		.ia_valid = ATTR_UID | ATTR_GID,
		.ia_uid = kuid,
		.ia_gid = kgid,
	पूर्ण;
	वापस kernfs_setattr(kn, &newattrs);
पूर्ण

/**
 *	sysfs_link_change_owner - change owner of a sysfs file.
 *	@kobj:	object of the kernfs_node the symlink is located in.
 *	@targ:	object of the kernfs_node the symlink poपूर्णांकs to.
 *	@name:	name of the link.
 *	@kuid:	new owner's kuid
 *	@kgid:	new owner's kgid
 *
 * This function looks up the sysfs symlink entry @name under @kobj and changes
 * the ownership to @kuid/@kgid. The symlink is looked up in the namespace of
 * @targ.
 *
 * Returns 0 on success or error code on failure.
 */
पूर्णांक sysfs_link_change_owner(काष्ठा kobject *kobj, काष्ठा kobject *targ,
			    स्थिर अक्षर *name, kuid_t kuid, kgid_t kgid)
अणु
	काष्ठा kernfs_node *kn = शून्य;
	पूर्णांक error;

	अगर (!name || !kobj->state_in_sysfs || !targ->state_in_sysfs)
		वापस -EINVAL;

	error = -ENOENT;
	kn = kernfs_find_and_get_ns(kobj->sd, name, targ->sd->ns);
	अगर (!kn)
		जाओ out;

	error = -EINVAL;
	अगर (kernfs_type(kn) != KERNFS_LINK)
		जाओ out;
	अगर (kn->symlink.target_kn->priv != targ)
		जाओ out;

	error = पूर्णांकernal_change_owner(kn, kuid, kgid);

out:
	kernfs_put(kn);
	वापस error;
पूर्ण

/**
 *	sysfs_file_change_owner - change owner of a sysfs file.
 *	@kobj:	object.
 *	@name:	name of the file to change.
 *	@kuid:	new owner's kuid
 *	@kgid:	new owner's kgid
 *
 * This function looks up the sysfs entry @name under @kobj and changes the
 * ownership to @kuid/@kgid.
 *
 * Returns 0 on success or error code on failure.
 */
पूर्णांक sysfs_file_change_owner(काष्ठा kobject *kobj, स्थिर अक्षर *name, kuid_t kuid,
			    kgid_t kgid)
अणु
	काष्ठा kernfs_node *kn;
	पूर्णांक error;

	अगर (!name)
		वापस -EINVAL;

	अगर (!kobj->state_in_sysfs)
		वापस -EINVAL;

	kn = kernfs_find_and_get(kobj->sd, name);
	अगर (!kn)
		वापस -ENOENT;

	error = पूर्णांकernal_change_owner(kn, kuid, kgid);

	kernfs_put(kn);

	वापस error;
पूर्ण
EXPORT_SYMBOL_GPL(sysfs_file_change_owner);

/**
 *	sysfs_change_owner - change owner of the given object.
 *	@kobj:	object.
 *	@kuid:	new owner's kuid
 *	@kgid:	new owner's kgid
 *
 * Change the owner of the शेष directory, files, groups, and attributes of
 * @kobj to @kuid/@kgid. Note that sysfs_change_owner mirrors how the sysfs
 * entries क्रम a kobject are added by driver core. In summary,
 * sysfs_change_owner() takes care of the शेष directory entry क्रम @kobj,
 * the शेष attributes associated with the ktype of @kobj and the शेष
 * attributes associated with the ktype of @kobj.
 * Additional properties not added by driver core have to be changed by the
 * driver or subप्रणाली which created them. This is similar to how
 * driver/subप्रणाली specअगरic entries are हटाओd.
 *
 * Returns 0 on success or error code on failure.
 */
पूर्णांक sysfs_change_owner(काष्ठा kobject *kobj, kuid_t kuid, kgid_t kgid)
अणु
	पूर्णांक error;
	स्थिर काष्ठा kobj_type *ktype;

	अगर (!kobj->state_in_sysfs)
		वापस -EINVAL;

	/* Change the owner of the kobject itself. */
	error = पूर्णांकernal_change_owner(kobj->sd, kuid, kgid);
	अगर (error)
		वापस error;

	ktype = get_ktype(kobj);
	अगर (ktype) अणु
		काष्ठा attribute **kattr;

		/*
		 * Change owner of the शेष attributes associated with the
		 * ktype of @kobj.
		 */
		क्रम (kattr = ktype->शेष_attrs; kattr && *kattr; kattr++) अणु
			error = sysfs_file_change_owner(kobj, (*kattr)->name,
							kuid, kgid);
			अगर (error)
				वापस error;
		पूर्ण

		/*
		 * Change owner of the शेष groups associated with the
		 * ktype of @kobj.
		 */
		error = sysfs_groups_change_owner(kobj, ktype->शेष_groups,
						  kuid, kgid);
		अगर (error)
			वापस error;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(sysfs_change_owner);

/**
 *	sysfs_emit - scnम_लिखो equivalent, aware of PAGE_SIZE buffer.
 *	@buf:	start of PAGE_SIZE buffer.
 *	@fmt:	क्रमmat
 *	@...:	optional arguments to @क्रमmat
 *
 *
 * Returns number of अक्षरacters written to @buf.
 */
पूर्णांक sysfs_emit(अक्षर *buf, स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची args;
	पूर्णांक len;

	अगर (WARN(!buf || offset_in_page(buf),
		 "invalid sysfs_emit: buf:%p\n", buf))
		वापस 0;

	बहु_शुरू(args, fmt);
	len = vscnम_लिखो(buf, PAGE_SIZE, fmt, args);
	बहु_पूर्ण(args);

	वापस len;
पूर्ण
EXPORT_SYMBOL_GPL(sysfs_emit);

/**
 *	sysfs_emit_at - scnम_लिखो equivalent, aware of PAGE_SIZE buffer.
 *	@buf:	start of PAGE_SIZE buffer.
 *	@at:	offset in @buf to start ग_लिखो in bytes
 *		@at must be >= 0 && < PAGE_SIZE
 *	@fmt:	क्रमmat
 *	@...:	optional arguments to @fmt
 *
 *
 * Returns number of अक्षरacters written starting at &@buf[@at].
 */
पूर्णांक sysfs_emit_at(अक्षर *buf, पूर्णांक at, स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची args;
	पूर्णांक len;

	अगर (WARN(!buf || offset_in_page(buf) || at < 0 || at >= PAGE_SIZE,
		 "invalid sysfs_emit_at: buf:%p at:%d\n", buf, at))
		वापस 0;

	बहु_शुरू(args, fmt);
	len = vscnम_लिखो(buf + at, PAGE_SIZE - at, fmt, args);
	बहु_पूर्ण(args);

	वापस len;
पूर्ण
EXPORT_SYMBOL_GPL(sysfs_emit_at);
