<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/fs/अक्षर_dev.c
 *
 *  Copyright (C) 1991, 1992  Linus Torvalds
 */

#समावेश <linux/init.h>
#समावेश <linux/fs.h>
#समावेश <linux/kdev_t.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>

#समावेश <linux/major.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/module.h>
#समावेश <linux/seq_file.h>

#समावेश <linux/kobject.h>
#समावेश <linux/kobj_map.h>
#समावेश <linux/cdev.h>
#समावेश <linux/mutex.h>
#समावेश <linux/backing-dev.h>
#समावेश <linux/tty.h>

#समावेश "internal.h"

अटल काष्ठा kobj_map *cdev_map;

अटल DEFINE_MUTEX(chrdevs_lock);

#घोषणा CHRDEV_MAJOR_HASH_SIZE 255

अटल काष्ठा अक्षर_device_काष्ठा अणु
	काष्ठा अक्षर_device_काष्ठा *next;
	अचिन्हित पूर्णांक major;
	अचिन्हित पूर्णांक baseminor;
	पूर्णांक minorct;
	अक्षर name[64];
	काष्ठा cdev *cdev;		/* will die */
पूर्ण *chrdevs[CHRDEV_MAJOR_HASH_SIZE];

/* index in the above */
अटल अंतरभूत पूर्णांक major_to_index(अचिन्हित major)
अणु
	वापस major % CHRDEV_MAJOR_HASH_SIZE;
पूर्ण

#अगर_घोषित CONFIG_PROC_FS

व्योम chrdev_show(काष्ठा seq_file *f, off_t offset)
अणु
	काष्ठा अक्षर_device_काष्ठा *cd;

	mutex_lock(&chrdevs_lock);
	क्रम (cd = chrdevs[major_to_index(offset)]; cd; cd = cd->next) अणु
		अगर (cd->major == offset)
			seq_म_लिखो(f, "%3d %s\n", cd->major, cd->name);
	पूर्ण
	mutex_unlock(&chrdevs_lock);
पूर्ण

#पूर्ण_अगर /* CONFIG_PROC_FS */

अटल पूर्णांक find_dynamic_major(व्योम)
अणु
	पूर्णांक i;
	काष्ठा अक्षर_device_काष्ठा *cd;

	क्रम (i = ARRAY_SIZE(chrdevs)-1; i >= CHRDEV_MAJOR_DYN_END; i--) अणु
		अगर (chrdevs[i] == शून्य)
			वापस i;
	पूर्ण

	क्रम (i = CHRDEV_MAJOR_DYN_EXT_START;
	     i >= CHRDEV_MAJOR_DYN_EXT_END; i--) अणु
		क्रम (cd = chrdevs[major_to_index(i)]; cd; cd = cd->next)
			अगर (cd->major == i)
				अवरोध;

		अगर (cd == शून्य)
			वापस i;
	पूर्ण

	वापस -EBUSY;
पूर्ण

/*
 * Register a single major with a specअगरied minor range.
 *
 * If major == 0 this function will dynamically allocate an unused major.
 * If major > 0 this function will attempt to reserve the range of minors
 * with given major.
 *
 */
अटल काष्ठा अक्षर_device_काष्ठा *
__रेजिस्टर_chrdev_region(अचिन्हित पूर्णांक major, अचिन्हित पूर्णांक baseminor,
			   पूर्णांक minorct, स्थिर अक्षर *name)
अणु
	काष्ठा अक्षर_device_काष्ठा *cd, *curr, *prev = शून्य;
	पूर्णांक ret;
	पूर्णांक i;

	अगर (major >= CHRDEV_MAJOR_MAX) अणु
		pr_err("CHRDEV \"%s\" major requested (%u) is greater than the maximum (%u)\n",
		       name, major, CHRDEV_MAJOR_MAX-1);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	अगर (minorct > MINORMASK + 1 - baseminor) अणु
		pr_err("CHRDEV \"%s\" minor range requested (%u-%u) is out of range of maximum range (%u-%u) for a single major\n",
			name, baseminor, baseminor + minorct - 1, 0, MINORMASK);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	cd = kzalloc(माप(काष्ठा अक्षर_device_काष्ठा), GFP_KERNEL);
	अगर (cd == शून्य)
		वापस ERR_PTR(-ENOMEM);

	mutex_lock(&chrdevs_lock);

	अगर (major == 0) अणु
		ret = find_dynamic_major();
		अगर (ret < 0) अणु
			pr_err("CHRDEV \"%s\" dynamic allocation region is full\n",
			       name);
			जाओ out;
		पूर्ण
		major = ret;
	पूर्ण

	ret = -EBUSY;
	i = major_to_index(major);
	क्रम (curr = chrdevs[i]; curr; prev = curr, curr = curr->next) अणु
		अगर (curr->major < major)
			जारी;

		अगर (curr->major > major)
			अवरोध;

		अगर (curr->baseminor + curr->minorct <= baseminor)
			जारी;

		अगर (curr->baseminor >= baseminor + minorct)
			अवरोध;

		जाओ out;
	पूर्ण

	cd->major = major;
	cd->baseminor = baseminor;
	cd->minorct = minorct;
	strlcpy(cd->name, name, माप(cd->name));

	अगर (!prev) अणु
		cd->next = curr;
		chrdevs[i] = cd;
	पूर्ण अन्यथा अणु
		cd->next = prev->next;
		prev->next = cd;
	पूर्ण

	mutex_unlock(&chrdevs_lock);
	वापस cd;
out:
	mutex_unlock(&chrdevs_lock);
	kमुक्त(cd);
	वापस ERR_PTR(ret);
पूर्ण

अटल काष्ठा अक्षर_device_काष्ठा *
__unरेजिस्टर_chrdev_region(अचिन्हित major, अचिन्हित baseminor, पूर्णांक minorct)
अणु
	काष्ठा अक्षर_device_काष्ठा *cd = शून्य, **cp;
	पूर्णांक i = major_to_index(major);

	mutex_lock(&chrdevs_lock);
	क्रम (cp = &chrdevs[i]; *cp; cp = &(*cp)->next)
		अगर ((*cp)->major == major &&
		    (*cp)->baseminor == baseminor &&
		    (*cp)->minorct == minorct)
			अवरोध;
	अगर (*cp) अणु
		cd = *cp;
		*cp = cd->next;
	पूर्ण
	mutex_unlock(&chrdevs_lock);
	वापस cd;
पूर्ण

/**
 * रेजिस्टर_chrdev_region() - रेजिस्टर a range of device numbers
 * @from: the first in the desired range of device numbers; must include
 *        the major number.
 * @count: the number of consecutive device numbers required
 * @name: the name of the device or driver.
 *
 * Return value is zero on success, a negative error code on failure.
 */
पूर्णांक रेजिस्टर_chrdev_region(dev_t from, अचिन्हित count, स्थिर अक्षर *name)
अणु
	काष्ठा अक्षर_device_काष्ठा *cd;
	dev_t to = from + count;
	dev_t n, next;

	क्रम (n = from; n < to; n = next) अणु
		next = MKDEV(MAJOR(n)+1, 0);
		अगर (next > to)
			next = to;
		cd = __रेजिस्टर_chrdev_region(MAJOR(n), MINOR(n),
			       next - n, name);
		अगर (IS_ERR(cd))
			जाओ fail;
	पूर्ण
	वापस 0;
fail:
	to = n;
	क्रम (n = from; n < to; n = next) अणु
		next = MKDEV(MAJOR(n)+1, 0);
		kमुक्त(__unरेजिस्टर_chrdev_region(MAJOR(n), MINOR(n), next - n));
	पूर्ण
	वापस PTR_ERR(cd);
पूर्ण

/**
 * alloc_chrdev_region() - रेजिस्टर a range of अक्षर device numbers
 * @dev: output parameter क्रम first asचिन्हित number
 * @baseminor: first of the requested range of minor numbers
 * @count: the number of minor numbers required
 * @name: the name of the associated device or driver
 *
 * Allocates a range of अक्षर device numbers.  The major number will be
 * chosen dynamically, and वापसed (aदीर्घ with the first minor number)
 * in @dev.  Returns zero or a negative error code.
 */
पूर्णांक alloc_chrdev_region(dev_t *dev, अचिन्हित baseminor, अचिन्हित count,
			स्थिर अक्षर *name)
अणु
	काष्ठा अक्षर_device_काष्ठा *cd;
	cd = __रेजिस्टर_chrdev_region(0, baseminor, count, name);
	अगर (IS_ERR(cd))
		वापस PTR_ERR(cd);
	*dev = MKDEV(cd->major, cd->baseminor);
	वापस 0;
पूर्ण

/**
 * __रेजिस्टर_chrdev() - create and रेजिस्टर a cdev occupying a range of minors
 * @major: major device number or 0 क्रम dynamic allocation
 * @baseminor: first of the requested range of minor numbers
 * @count: the number of minor numbers required
 * @name: name of this range of devices
 * @fops: file operations associated with this devices
 *
 * If @major == 0 this functions will dynamically allocate a major and वापस
 * its number.
 *
 * If @major > 0 this function will attempt to reserve a device with the given
 * major number and will वापस zero on success.
 *
 * Returns a -ve त्रुटि_सं on failure.
 *
 * The name of this device has nothing to करो with the name of the device in
 * /dev. It only helps to keep track of the dअगरferent owners of devices. If
 * your module name has only one type of devices it's ok to use e.g. the name
 * of the module here.
 */
पूर्णांक __रेजिस्टर_chrdev(अचिन्हित पूर्णांक major, अचिन्हित पूर्णांक baseminor,
		      अचिन्हित पूर्णांक count, स्थिर अक्षर *name,
		      स्थिर काष्ठा file_operations *fops)
अणु
	काष्ठा अक्षर_device_काष्ठा *cd;
	काष्ठा cdev *cdev;
	पूर्णांक err = -ENOMEM;

	cd = __रेजिस्टर_chrdev_region(major, baseminor, count, name);
	अगर (IS_ERR(cd))
		वापस PTR_ERR(cd);

	cdev = cdev_alloc();
	अगर (!cdev)
		जाओ out2;

	cdev->owner = fops->owner;
	cdev->ops = fops;
	kobject_set_name(&cdev->kobj, "%s", name);

	err = cdev_add(cdev, MKDEV(cd->major, baseminor), count);
	अगर (err)
		जाओ out;

	cd->cdev = cdev;

	वापस major ? 0 : cd->major;
out:
	kobject_put(&cdev->kobj);
out2:
	kमुक्त(__unरेजिस्टर_chrdev_region(cd->major, baseminor, count));
	वापस err;
पूर्ण

/**
 * unरेजिस्टर_chrdev_region() - unरेजिस्टर a range of device numbers
 * @from: the first in the range of numbers to unरेजिस्टर
 * @count: the number of device numbers to unरेजिस्टर
 *
 * This function will unरेजिस्टर a range of @count device numbers,
 * starting with @from.  The caller should normally be the one who
 * allocated those numbers in the first place...
 */
व्योम unरेजिस्टर_chrdev_region(dev_t from, अचिन्हित count)
अणु
	dev_t to = from + count;
	dev_t n, next;

	क्रम (n = from; n < to; n = next) अणु
		next = MKDEV(MAJOR(n)+1, 0);
		अगर (next > to)
			next = to;
		kमुक्त(__unरेजिस्टर_chrdev_region(MAJOR(n), MINOR(n), next - n));
	पूर्ण
पूर्ण

/**
 * __unरेजिस्टर_chrdev - unरेजिस्टर and destroy a cdev
 * @major: major device number
 * @baseminor: first of the range of minor numbers
 * @count: the number of minor numbers this cdev is occupying
 * @name: name of this range of devices
 *
 * Unरेजिस्टर and destroy the cdev occupying the region described by
 * @major, @baseminor and @count.  This function unकरोes what
 * __रेजिस्टर_chrdev() did.
 */
व्योम __unरेजिस्टर_chrdev(अचिन्हित पूर्णांक major, अचिन्हित पूर्णांक baseminor,
			 अचिन्हित पूर्णांक count, स्थिर अक्षर *name)
अणु
	काष्ठा अक्षर_device_काष्ठा *cd;

	cd = __unरेजिस्टर_chrdev_region(major, baseminor, count);
	अगर (cd && cd->cdev)
		cdev_del(cd->cdev);
	kमुक्त(cd);
पूर्ण

अटल DEFINE_SPINLOCK(cdev_lock);

अटल काष्ठा kobject *cdev_get(काष्ठा cdev *p)
अणु
	काष्ठा module *owner = p->owner;
	काष्ठा kobject *kobj;

	अगर (owner && !try_module_get(owner))
		वापस शून्य;
	kobj = kobject_get_unless_zero(&p->kobj);
	अगर (!kobj)
		module_put(owner);
	वापस kobj;
पूर्ण

व्योम cdev_put(काष्ठा cdev *p)
अणु
	अगर (p) अणु
		काष्ठा module *owner = p->owner;
		kobject_put(&p->kobj);
		module_put(owner);
	पूर्ण
पूर्ण

/*
 * Called every समय a अक्षरacter special file is खोलोed
 */
अटल पूर्णांक chrdev_खोलो(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	स्थिर काष्ठा file_operations *fops;
	काष्ठा cdev *p;
	काष्ठा cdev *new = शून्य;
	पूर्णांक ret = 0;

	spin_lock(&cdev_lock);
	p = inode->i_cdev;
	अगर (!p) अणु
		काष्ठा kobject *kobj;
		पूर्णांक idx;
		spin_unlock(&cdev_lock);
		kobj = kobj_lookup(cdev_map, inode->i_rdev, &idx);
		अगर (!kobj)
			वापस -ENXIO;
		new = container_of(kobj, काष्ठा cdev, kobj);
		spin_lock(&cdev_lock);
		/* Check i_cdev again in हाल somebody beat us to it जबतक
		   we dropped the lock. */
		p = inode->i_cdev;
		अगर (!p) अणु
			inode->i_cdev = p = new;
			list_add(&inode->i_devices, &p->list);
			new = शून्य;
		पूर्ण अन्यथा अगर (!cdev_get(p))
			ret = -ENXIO;
	पूर्ण अन्यथा अगर (!cdev_get(p))
		ret = -ENXIO;
	spin_unlock(&cdev_lock);
	cdev_put(new);
	अगर (ret)
		वापस ret;

	ret = -ENXIO;
	fops = fops_get(p->ops);
	अगर (!fops)
		जाओ out_cdev_put;

	replace_fops(filp, fops);
	अगर (filp->f_op->खोलो) अणु
		ret = filp->f_op->खोलो(inode, filp);
		अगर (ret)
			जाओ out_cdev_put;
	पूर्ण

	वापस 0;

 out_cdev_put:
	cdev_put(p);
	वापस ret;
पूर्ण

व्योम cd_क्रमget(काष्ठा inode *inode)
अणु
	spin_lock(&cdev_lock);
	list_del_init(&inode->i_devices);
	inode->i_cdev = शून्य;
	inode->i_mapping = &inode->i_data;
	spin_unlock(&cdev_lock);
पूर्ण

अटल व्योम cdev_purge(काष्ठा cdev *cdev)
अणु
	spin_lock(&cdev_lock);
	जबतक (!list_empty(&cdev->list)) अणु
		काष्ठा inode *inode;
		inode = container_of(cdev->list.next, काष्ठा inode, i_devices);
		list_del_init(&inode->i_devices);
		inode->i_cdev = शून्य;
	पूर्ण
	spin_unlock(&cdev_lock);
पूर्ण

/*
 * Dummy शेष file-operations: the only thing this करोes
 * is contain the खोलो that then fills in the correct operations
 * depending on the special file...
 */
स्थिर काष्ठा file_operations def_chr_fops = अणु
	.खोलो = chrdev_खोलो,
	.llseek = noop_llseek,
पूर्ण;

अटल काष्ठा kobject *exact_match(dev_t dev, पूर्णांक *part, व्योम *data)
अणु
	काष्ठा cdev *p = data;
	वापस &p->kobj;
पूर्ण

अटल पूर्णांक exact_lock(dev_t dev, व्योम *data)
अणु
	काष्ठा cdev *p = data;
	वापस cdev_get(p) ? 0 : -1;
पूर्ण

/**
 * cdev_add() - add a अक्षर device to the प्रणाली
 * @p: the cdev काष्ठाure क्रम the device
 * @dev: the first device number क्रम which this device is responsible
 * @count: the number of consecutive minor numbers corresponding to this
 *         device
 *
 * cdev_add() adds the device represented by @p to the प्रणाली, making it
 * live immediately.  A negative error code is वापसed on failure.
 */
पूर्णांक cdev_add(काष्ठा cdev *p, dev_t dev, अचिन्हित count)
अणु
	पूर्णांक error;

	p->dev = dev;
	p->count = count;

	अगर (WARN_ON(dev == WHITEOUT_DEV))
		वापस -EBUSY;

	error = kobj_map(cdev_map, dev, count, शून्य,
			 exact_match, exact_lock, p);
	अगर (error)
		वापस error;

	kobject_get(p->kobj.parent);

	वापस 0;
पूर्ण

/**
 * cdev_set_parent() - set the parent kobject क्रम a अक्षर device
 * @p: the cdev काष्ठाure
 * @kobj: the kobject to take a reference to
 *
 * cdev_set_parent() sets a parent kobject which will be referenced
 * appropriately so the parent is not मुक्तd beक्रमe the cdev. This
 * should be called beक्रमe cdev_add.
 */
व्योम cdev_set_parent(काष्ठा cdev *p, काष्ठा kobject *kobj)
अणु
	WARN_ON(!kobj->state_initialized);
	p->kobj.parent = kobj;
पूर्ण

/**
 * cdev_device_add() - add a अक्षर device and it's corresponding
 *	काष्ठा device, linkink
 * @dev: the device काष्ठाure
 * @cdev: the cdev काष्ठाure
 *
 * cdev_device_add() adds the अक्षर device represented by @cdev to the प्रणाली,
 * just as cdev_add करोes. It then adds @dev to the प्रणाली using device_add
 * The dev_t क्रम the अक्षर device will be taken from the काष्ठा device which
 * needs to be initialized first. This helper function correctly takes a
 * reference to the parent device so the parent will not get released until
 * all references to the cdev are released.
 *
 * This helper uses dev->devt क्रम the device number. If it is not set
 * it will not add the cdev and it will be equivalent to device_add.
 *
 * This function should be used whenever the काष्ठा cdev and the
 * काष्ठा device are members of the same काष्ठाure whose lअगरeसमय is
 * managed by the काष्ठा device.
 *
 * NOTE: Callers must assume that userspace was able to खोलो the cdev and
 * can call cdev fops callbacks at any समय, even अगर this function fails.
 */
पूर्णांक cdev_device_add(काष्ठा cdev *cdev, काष्ठा device *dev)
अणु
	पूर्णांक rc = 0;

	अगर (dev->devt) अणु
		cdev_set_parent(cdev, &dev->kobj);

		rc = cdev_add(cdev, dev->devt, 1);
		अगर (rc)
			वापस rc;
	पूर्ण

	rc = device_add(dev);
	अगर (rc)
		cdev_del(cdev);

	वापस rc;
पूर्ण

/**
 * cdev_device_del() - inverse of cdev_device_add
 * @dev: the device काष्ठाure
 * @cdev: the cdev काष्ठाure
 *
 * cdev_device_del() is a helper function to call cdev_del and device_del.
 * It should be used whenever cdev_device_add is used.
 *
 * If dev->devt is not set it will not हटाओ the cdev and will be equivalent
 * to device_del.
 *
 * NOTE: This guarantees that associated sysfs callbacks are not running
 * or runnable, however any cdevs alपढ़ोy खोलो will reमुख्य and their fops
 * will still be callable even after this function वापसs.
 */
व्योम cdev_device_del(काष्ठा cdev *cdev, काष्ठा device *dev)
अणु
	device_del(dev);
	अगर (dev->devt)
		cdev_del(cdev);
पूर्ण

अटल व्योम cdev_unmap(dev_t dev, अचिन्हित count)
अणु
	kobj_unmap(cdev_map, dev, count);
पूर्ण

/**
 * cdev_del() - हटाओ a cdev from the प्रणाली
 * @p: the cdev काष्ठाure to be हटाओd
 *
 * cdev_del() हटाओs @p from the प्रणाली, possibly मुक्तing the काष्ठाure
 * itself.
 *
 * NOTE: This guarantees that cdev device will no दीर्घer be able to be
 * खोलोed, however any cdevs alपढ़ोy खोलो will reमुख्य and their fops will
 * still be callable even after cdev_del वापसs.
 */
व्योम cdev_del(काष्ठा cdev *p)
अणु
	cdev_unmap(p->dev, p->count);
	kobject_put(&p->kobj);
पूर्ण


अटल व्योम cdev_शेष_release(काष्ठा kobject *kobj)
अणु
	काष्ठा cdev *p = container_of(kobj, काष्ठा cdev, kobj);
	काष्ठा kobject *parent = kobj->parent;

	cdev_purge(p);
	kobject_put(parent);
पूर्ण

अटल व्योम cdev_dynamic_release(काष्ठा kobject *kobj)
अणु
	काष्ठा cdev *p = container_of(kobj, काष्ठा cdev, kobj);
	काष्ठा kobject *parent = kobj->parent;

	cdev_purge(p);
	kमुक्त(p);
	kobject_put(parent);
पूर्ण

अटल काष्ठा kobj_type ktype_cdev_शेष = अणु
	.release	= cdev_शेष_release,
पूर्ण;

अटल काष्ठा kobj_type ktype_cdev_dynamic = अणु
	.release	= cdev_dynamic_release,
पूर्ण;

/**
 * cdev_alloc() - allocate a cdev काष्ठाure
 *
 * Allocates and वापसs a cdev काष्ठाure, or शून्य on failure.
 */
काष्ठा cdev *cdev_alloc(व्योम)
अणु
	काष्ठा cdev *p = kzalloc(माप(काष्ठा cdev), GFP_KERNEL);
	अगर (p) अणु
		INIT_LIST_HEAD(&p->list);
		kobject_init(&p->kobj, &ktype_cdev_dynamic);
	पूर्ण
	वापस p;
पूर्ण

/**
 * cdev_init() - initialize a cdev काष्ठाure
 * @cdev: the काष्ठाure to initialize
 * @fops: the file_operations क्रम this device
 *
 * Initializes @cdev, remembering @fops, making it पढ़ोy to add to the
 * प्रणाली with cdev_add().
 */
व्योम cdev_init(काष्ठा cdev *cdev, स्थिर काष्ठा file_operations *fops)
अणु
	स_रखो(cdev, 0, माप *cdev);
	INIT_LIST_HEAD(&cdev->list);
	kobject_init(&cdev->kobj, &ktype_cdev_शेष);
	cdev->ops = fops;
पूर्ण

अटल काष्ठा kobject *base_probe(dev_t dev, पूर्णांक *part, व्योम *data)
अणु
	अगर (request_module("char-major-%d-%d", MAJOR(dev), MINOR(dev)) > 0)
		/* Make old-style 2.4 aliases work */
		request_module("char-major-%d", MAJOR(dev));
	वापस शून्य;
पूर्ण

व्योम __init chrdev_init(व्योम)
अणु
	cdev_map = kobj_map_init(base_probe, &chrdevs_lock);
पूर्ण


/* Let modules करो अक्षर dev stuff */
EXPORT_SYMBOL(रेजिस्टर_chrdev_region);
EXPORT_SYMBOL(unरेजिस्टर_chrdev_region);
EXPORT_SYMBOL(alloc_chrdev_region);
EXPORT_SYMBOL(cdev_init);
EXPORT_SYMBOL(cdev_alloc);
EXPORT_SYMBOL(cdev_del);
EXPORT_SYMBOL(cdev_add);
EXPORT_SYMBOL(cdev_set_parent);
EXPORT_SYMBOL(cdev_device_add);
EXPORT_SYMBOL(cdev_device_del);
EXPORT_SYMBOL(__रेजिस्टर_chrdev);
EXPORT_SYMBOL(__unरेजिस्टर_chrdev);
