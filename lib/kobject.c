<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * kobject.c - library routines क्रम handling generic kernel objects
 *
 * Copyright (c) 2002-2003 Patrick Mochel <mochel@osdl.org>
 * Copyright (c) 2006-2007 Greg Kroah-Harपंचांगan <greg@kroah.com>
 * Copyright (c) 2006-2007 Novell Inc.
 *
 * Please see the file Documentation/core-api/kobject.rst क्रम critical inक्रमmation
 * about using the kobject पूर्णांकerface.
 */

#समावेश <linux/kobject.h>
#समावेश <linux/माला.स>
#समावेश <linux/export.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/slab.h>
#समावेश <linux/अक्रमom.h>

/**
 * kobject_namespace() - Return @kobj's namespace tag.
 * @kobj: kobject in question
 *
 * Returns namespace tag of @kobj अगर its parent has namespace ops enabled
 * and thus @kobj should have a namespace tag associated with it.  Returns
 * %शून्य otherwise.
 */
स्थिर व्योम *kobject_namespace(काष्ठा kobject *kobj)
अणु
	स्थिर काष्ठा kobj_ns_type_operations *ns_ops = kobj_ns_ops(kobj);

	अगर (!ns_ops || ns_ops->type == KOBJ_NS_TYPE_NONE)
		वापस शून्य;

	वापस kobj->ktype->namespace(kobj);
पूर्ण

/**
 * kobject_get_ownership() - Get sysfs ownership data क्रम @kobj.
 * @kobj: kobject in question
 * @uid: kernel user ID क्रम sysfs objects
 * @gid: kernel group ID क्रम sysfs objects
 *
 * Returns initial uid/gid pair that should be used when creating sysfs
 * representation of given kobject. Normally used to adjust ownership of
 * objects in a container.
 */
व्योम kobject_get_ownership(काष्ठा kobject *kobj, kuid_t *uid, kgid_t *gid)
अणु
	*uid = GLOBAL_ROOT_UID;
	*gid = GLOBAL_ROOT_GID;

	अगर (kobj->ktype->get_ownership)
		kobj->ktype->get_ownership(kobj, uid, gid);
पूर्ण

/*
 * populate_dir - populate directory with attributes.
 * @kobj: object we're working on.
 *
 * Most subप्रणालीs have a set of शेष attributes that are associated
 * with an object that रेजिस्टरs with them.  This is a helper called during
 * object registration that loops through the शेष attributes of the
 * subप्रणाली and creates attributes files क्रम them in sysfs.
 */
अटल पूर्णांक populate_dir(काष्ठा kobject *kobj)
अणु
	काष्ठा kobj_type *t = get_ktype(kobj);
	काष्ठा attribute *attr;
	पूर्णांक error = 0;
	पूर्णांक i;

	अगर (t && t->शेष_attrs) अणु
		क्रम (i = 0; (attr = t->शेष_attrs[i]) != शून्य; i++) अणु
			error = sysfs_create_file(kobj, attr);
			अगर (error)
				अवरोध;
		पूर्ण
	पूर्ण
	वापस error;
पूर्ण

अटल पूर्णांक create_dir(काष्ठा kobject *kobj)
अणु
	स्थिर काष्ठा kobj_type *ktype = get_ktype(kobj);
	स्थिर काष्ठा kobj_ns_type_operations *ops;
	पूर्णांक error;

	error = sysfs_create_dir_ns(kobj, kobject_namespace(kobj));
	अगर (error)
		वापस error;

	error = populate_dir(kobj);
	अगर (error) अणु
		sysfs_हटाओ_dir(kobj);
		वापस error;
	पूर्ण

	अगर (ktype) अणु
		error = sysfs_create_groups(kobj, ktype->शेष_groups);
		अगर (error) अणु
			sysfs_हटाओ_dir(kobj);
			वापस error;
		पूर्ण
	पूर्ण

	/*
	 * @kobj->sd may be deleted by an ancestor going away.  Hold an
	 * extra reference so that it stays until @kobj is gone.
	 */
	sysfs_get(kobj->sd);

	/*
	 * If @kobj has ns_ops, its children need to be filtered based on
	 * their namespace tags.  Enable namespace support on @kobj->sd.
	 */
	ops = kobj_child_ns_ops(kobj);
	अगर (ops) अणु
		BUG_ON(ops->type <= KOBJ_NS_TYPE_NONE);
		BUG_ON(ops->type >= KOBJ_NS_TYPES);
		BUG_ON(!kobj_ns_type_रेजिस्टरed(ops->type));

		sysfs_enable_ns(kobj->sd);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक get_kobj_path_length(काष्ठा kobject *kobj)
अणु
	पूर्णांक length = 1;
	काष्ठा kobject *parent = kobj;

	/* walk up the ancestors until we hit the one poपूर्णांकing to the
	 * root.
	 * Add 1 to म_माप क्रम leading '/' of each level.
	 */
	करो अणु
		अगर (kobject_name(parent) == शून्य)
			वापस 0;
		length += म_माप(kobject_name(parent)) + 1;
		parent = parent->parent;
	पूर्ण जबतक (parent);
	वापस length;
पूर्ण

अटल व्योम fill_kobj_path(काष्ठा kobject *kobj, अक्षर *path, पूर्णांक length)
अणु
	काष्ठा kobject *parent;

	--length;
	क्रम (parent = kobj; parent; parent = parent->parent) अणु
		पूर्णांक cur = म_माप(kobject_name(parent));
		/* back up enough to prपूर्णांक this name with '/' */
		length -= cur;
		स_नकल(path + length, kobject_name(parent), cur);
		*(path + --length) = '/';
	पूर्ण

	pr_debug("kobject: '%s' (%p): %s: path = '%s'\n", kobject_name(kobj),
		 kobj, __func__, path);
पूर्ण

/**
 * kobject_get_path() - Allocate memory and fill in the path क्रम @kobj.
 * @kobj:	kobject in question, with which to build the path
 * @gfp_mask:	the allocation type used to allocate the path
 *
 * Return: The newly allocated memory, caller must मुक्त with kमुक्त().
 */
अक्षर *kobject_get_path(काष्ठा kobject *kobj, gfp_t gfp_mask)
अणु
	अक्षर *path;
	पूर्णांक len;

	len = get_kobj_path_length(kobj);
	अगर (len == 0)
		वापस शून्य;
	path = kzalloc(len, gfp_mask);
	अगर (!path)
		वापस शून्य;
	fill_kobj_path(kobj, path, len);

	वापस path;
पूर्ण
EXPORT_SYMBOL_GPL(kobject_get_path);

/* add the kobject to its kset's list */
अटल व्योम kobj_kset_join(काष्ठा kobject *kobj)
अणु
	अगर (!kobj->kset)
		वापस;

	kset_get(kobj->kset);
	spin_lock(&kobj->kset->list_lock);
	list_add_tail(&kobj->entry, &kobj->kset->list);
	spin_unlock(&kobj->kset->list_lock);
पूर्ण

/* हटाओ the kobject from its kset's list */
अटल व्योम kobj_kset_leave(काष्ठा kobject *kobj)
अणु
	अगर (!kobj->kset)
		वापस;

	spin_lock(&kobj->kset->list_lock);
	list_del_init(&kobj->entry);
	spin_unlock(&kobj->kset->list_lock);
	kset_put(kobj->kset);
पूर्ण

अटल व्योम kobject_init_पूर्णांकernal(काष्ठा kobject *kobj)
अणु
	अगर (!kobj)
		वापस;
	kref_init(&kobj->kref);
	INIT_LIST_HEAD(&kobj->entry);
	kobj->state_in_sysfs = 0;
	kobj->state_add_uevent_sent = 0;
	kobj->state_हटाओ_uevent_sent = 0;
	kobj->state_initialized = 1;
पूर्ण


अटल पूर्णांक kobject_add_पूर्णांकernal(काष्ठा kobject *kobj)
अणु
	पूर्णांक error = 0;
	काष्ठा kobject *parent;

	अगर (!kobj)
		वापस -ENOENT;

	अगर (!kobj->name || !kobj->name[0]) अणु
		WARN(1,
		     "kobject: (%p): attempted to be registered with empty name!\n",
		     kobj);
		वापस -EINVAL;
	पूर्ण

	parent = kobject_get(kobj->parent);

	/* join kset अगर set, use it as parent अगर we करो not alपढ़ोy have one */
	अगर (kobj->kset) अणु
		अगर (!parent)
			parent = kobject_get(&kobj->kset->kobj);
		kobj_kset_join(kobj);
		kobj->parent = parent;
	पूर्ण

	pr_debug("kobject: '%s' (%p): %s: parent: '%s', set: '%s'\n",
		 kobject_name(kobj), kobj, __func__,
		 parent ? kobject_name(parent) : "<NULL>",
		 kobj->kset ? kobject_name(&kobj->kset->kobj) : "<NULL>");

	error = create_dir(kobj);
	अगर (error) अणु
		kobj_kset_leave(kobj);
		kobject_put(parent);
		kobj->parent = शून्य;

		/* be noisy on error issues */
		अगर (error == -EEXIST)
			pr_err("%s failed for %s with -EEXIST, don't try to register things with the same name in the same directory.\n",
			       __func__, kobject_name(kobj));
		अन्यथा
			pr_err("%s failed for %s (error: %d parent: %s)\n",
			       __func__, kobject_name(kobj), error,
			       parent ? kobject_name(parent) : "'none'");
	पूर्ण अन्यथा
		kobj->state_in_sysfs = 1;

	वापस error;
पूर्ण

/**
 * kobject_set_name_vargs() - Set the name of a kobject.
 * @kobj: काष्ठा kobject to set the name of
 * @fmt: क्रमmat string used to build the name
 * @vargs: vargs to क्रमmat the string.
 */
पूर्णांक kobject_set_name_vargs(काष्ठा kobject *kobj, स्थिर अक्षर *fmt,
				  बहु_सूची vargs)
अणु
	स्थिर अक्षर *s;

	अगर (kobj->name && !fmt)
		वापस 0;

	s = kvaप्र_लिखो_स्थिर(GFP_KERNEL, fmt, vargs);
	अगर (!s)
		वापस -ENOMEM;

	/*
	 * ewww... some of these buggers have '/' in the name ... If
	 * that's the हाल, we need to make sure we have an actual
	 * allocated copy to modअगरy, since kvaप्र_लिखो_स्थिर may have
	 * वापसed something from .rodata.
	 */
	अगर (म_अक्षर(s, '/')) अणु
		अक्षर *t;

		t = kstrdup(s, GFP_KERNEL);
		kमुक्त_स्थिर(s);
		अगर (!t)
			वापस -ENOMEM;
		strreplace(t, '/', '!');
		s = t;
	पूर्ण
	kमुक्त_स्थिर(kobj->name);
	kobj->name = s;

	वापस 0;
पूर्ण

/**
 * kobject_set_name() - Set the name of a kobject.
 * @kobj: काष्ठा kobject to set the name of
 * @fmt: क्रमmat string used to build the name
 *
 * This sets the name of the kobject.  If you have alपढ़ोy added the
 * kobject to the प्रणाली, you must call kobject_नाम() in order to
 * change the name of the kobject.
 */
पूर्णांक kobject_set_name(काष्ठा kobject *kobj, स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची vargs;
	पूर्णांक retval;

	बहु_शुरू(vargs, fmt);
	retval = kobject_set_name_vargs(kobj, fmt, vargs);
	बहु_पूर्ण(vargs);

	वापस retval;
पूर्ण
EXPORT_SYMBOL(kobject_set_name);

/**
 * kobject_init() - Initialize a kobject काष्ठाure.
 * @kobj: poपूर्णांकer to the kobject to initialize
 * @ktype: poपूर्णांकer to the ktype क्रम this kobject.
 *
 * This function will properly initialize a kobject such that it can then
 * be passed to the kobject_add() call.
 *
 * After this function is called, the kobject MUST be cleaned up by a call
 * to kobject_put(), not by a call to kमुक्त directly to ensure that all of
 * the memory is cleaned up properly.
 */
व्योम kobject_init(काष्ठा kobject *kobj, काष्ठा kobj_type *ktype)
अणु
	अक्षर *err_str;

	अगर (!kobj) अणु
		err_str = "invalid kobject pointer!";
		जाओ error;
	पूर्ण
	अगर (!ktype) अणु
		err_str = "must have a ktype to be initialized properly!\n";
		जाओ error;
	पूर्ण
	अगर (kobj->state_initialized) अणु
		/* करो not error out as someबार we can recover */
		pr_err("kobject (%p): tried to init an initialized object, something is seriously wrong.\n",
		       kobj);
		dump_stack();
	पूर्ण

	kobject_init_पूर्णांकernal(kobj);
	kobj->ktype = ktype;
	वापस;

error:
	pr_err("kobject (%p): %s\n", kobj, err_str);
	dump_stack();
पूर्ण
EXPORT_SYMBOL(kobject_init);

अटल __म_लिखो(3, 0) पूर्णांक kobject_add_varg(काष्ठा kobject *kobj,
					   काष्ठा kobject *parent,
					   स्थिर अक्षर *fmt, बहु_सूची vargs)
अणु
	पूर्णांक retval;

	retval = kobject_set_name_vargs(kobj, fmt, vargs);
	अगर (retval) अणु
		pr_err("kobject: can not set name properly!\n");
		वापस retval;
	पूर्ण
	kobj->parent = parent;
	वापस kobject_add_पूर्णांकernal(kobj);
पूर्ण

/**
 * kobject_add() - The मुख्य kobject add function.
 * @kobj: the kobject to add
 * @parent: poपूर्णांकer to the parent of the kobject.
 * @fmt: क्रमmat to name the kobject with.
 *
 * The kobject name is set and added to the kobject hierarchy in this
 * function.
 *
 * If @parent is set, then the parent of the @kobj will be set to it.
 * If @parent is शून्य, then the parent of the @kobj will be set to the
 * kobject associated with the kset asचिन्हित to this kobject.  If no kset
 * is asचिन्हित to the kobject, then the kobject will be located in the
 * root of the sysfs tree.
 *
 * Note, no "add" uevent will be created with this call, the caller should set
 * up all of the necessary sysfs files क्रम the object and then call
 * kobject_uevent() with the UEVENT_ADD parameter to ensure that
 * userspace is properly notअगरied of this kobject's creation.
 *
 * Return: If this function वापसs an error, kobject_put() must be
 *         called to properly clean up the memory associated with the
 *         object.  Under no instance should the kobject that is passed
 *         to this function be directly मुक्तd with a call to kमुक्त(),
 *         that can leak memory.
 *
 *         If this function वापसs success, kobject_put() must also be called
 *         in order to properly clean up the memory associated with the object.
 *
 *         In लघु, once this function is called, kobject_put() MUST be called
 *         when the use of the object is finished in order to properly मुक्त
 *         everything.
 */
पूर्णांक kobject_add(काष्ठा kobject *kobj, काष्ठा kobject *parent,
		स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची args;
	पूर्णांक retval;

	अगर (!kobj)
		वापस -EINVAL;

	अगर (!kobj->state_initialized) अणु
		pr_err("kobject '%s' (%p): tried to add an uninitialized object, something is seriously wrong.\n",
		       kobject_name(kobj), kobj);
		dump_stack();
		वापस -EINVAL;
	पूर्ण
	बहु_शुरू(args, fmt);
	retval = kobject_add_varg(kobj, parent, fmt, args);
	बहु_पूर्ण(args);

	वापस retval;
पूर्ण
EXPORT_SYMBOL(kobject_add);

/**
 * kobject_init_and_add() - Initialize a kobject काष्ठाure and add it to
 *                          the kobject hierarchy.
 * @kobj: poपूर्णांकer to the kobject to initialize
 * @ktype: poपूर्णांकer to the ktype क्रम this kobject.
 * @parent: poपूर्णांकer to the parent of this kobject.
 * @fmt: the name of the kobject.
 *
 * This function combines the call to kobject_init() and kobject_add().
 *
 * If this function वापसs an error, kobject_put() must be called to
 * properly clean up the memory associated with the object.  This is the
 * same type of error handling after a call to kobject_add() and kobject
 * lअगरeसमय rules are the same here.
 */
पूर्णांक kobject_init_and_add(काष्ठा kobject *kobj, काष्ठा kobj_type *ktype,
			 काष्ठा kobject *parent, स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची args;
	पूर्णांक retval;

	kobject_init(kobj, ktype);

	बहु_शुरू(args, fmt);
	retval = kobject_add_varg(kobj, parent, fmt, args);
	बहु_पूर्ण(args);

	वापस retval;
पूर्ण
EXPORT_SYMBOL_GPL(kobject_init_and_add);

/**
 * kobject_नाम() - Change the name of an object.
 * @kobj: object in question.
 * @new_name: object's new name
 *
 * It is the responsibility of the caller to provide mutual
 * exclusion between two dअगरferent calls of kobject_नाम
 * on the same kobject and to ensure that new_name is valid and
 * won't conflict with other kobjects.
 */
पूर्णांक kobject_नाम(काष्ठा kobject *kobj, स्थिर अक्षर *new_name)
अणु
	पूर्णांक error = 0;
	स्थिर अक्षर *devpath = शून्य;
	स्थिर अक्षर *dup_name = शून्य, *name;
	अक्षर *devpath_string = शून्य;
	अक्षर *envp[2];

	kobj = kobject_get(kobj);
	अगर (!kobj)
		वापस -EINVAL;
	अगर (!kobj->parent) अणु
		kobject_put(kobj);
		वापस -EINVAL;
	पूर्ण

	devpath = kobject_get_path(kobj, GFP_KERNEL);
	अगर (!devpath) अणु
		error = -ENOMEM;
		जाओ out;
	पूर्ण
	devpath_string = kदो_स्मृति(म_माप(devpath) + 15, GFP_KERNEL);
	अगर (!devpath_string) अणु
		error = -ENOMEM;
		जाओ out;
	पूर्ण
	प्र_लिखो(devpath_string, "DEVPATH_OLD=%s", devpath);
	envp[0] = devpath_string;
	envp[1] = शून्य;

	name = dup_name = kstrdup_स्थिर(new_name, GFP_KERNEL);
	अगर (!name) अणु
		error = -ENOMEM;
		जाओ out;
	पूर्ण

	error = sysfs_नाम_dir_ns(kobj, new_name, kobject_namespace(kobj));
	अगर (error)
		जाओ out;

	/* Install the new kobject name */
	dup_name = kobj->name;
	kobj->name = name;

	/* This function is mostly/only used क्रम network पूर्णांकerface.
	 * Some hotplug package track पूर्णांकerfaces by their name and
	 * thereक्रमe want to know when the name is changed by the user. */
	kobject_uevent_env(kobj, KOBJ_MOVE, envp);

out:
	kमुक्त_स्थिर(dup_name);
	kमुक्त(devpath_string);
	kमुक्त(devpath);
	kobject_put(kobj);

	वापस error;
पूर्ण
EXPORT_SYMBOL_GPL(kobject_नाम);

/**
 * kobject_move() - Move object to another parent.
 * @kobj: object in question.
 * @new_parent: object's new parent (can be शून्य)
 */
पूर्णांक kobject_move(काष्ठा kobject *kobj, काष्ठा kobject *new_parent)
अणु
	पूर्णांक error;
	काष्ठा kobject *old_parent;
	स्थिर अक्षर *devpath = शून्य;
	अक्षर *devpath_string = शून्य;
	अक्षर *envp[2];

	kobj = kobject_get(kobj);
	अगर (!kobj)
		वापस -EINVAL;
	new_parent = kobject_get(new_parent);
	अगर (!new_parent) अणु
		अगर (kobj->kset)
			new_parent = kobject_get(&kobj->kset->kobj);
	पूर्ण

	/* old object path */
	devpath = kobject_get_path(kobj, GFP_KERNEL);
	अगर (!devpath) अणु
		error = -ENOMEM;
		जाओ out;
	पूर्ण
	devpath_string = kदो_स्मृति(म_माप(devpath) + 15, GFP_KERNEL);
	अगर (!devpath_string) अणु
		error = -ENOMEM;
		जाओ out;
	पूर्ण
	प्र_लिखो(devpath_string, "DEVPATH_OLD=%s", devpath);
	envp[0] = devpath_string;
	envp[1] = शून्य;
	error = sysfs_move_dir_ns(kobj, new_parent, kobject_namespace(kobj));
	अगर (error)
		जाओ out;
	old_parent = kobj->parent;
	kobj->parent = new_parent;
	new_parent = शून्य;
	kobject_put(old_parent);
	kobject_uevent_env(kobj, KOBJ_MOVE, envp);
out:
	kobject_put(new_parent);
	kobject_put(kobj);
	kमुक्त(devpath_string);
	kमुक्त(devpath);
	वापस error;
पूर्ण
EXPORT_SYMBOL_GPL(kobject_move);

अटल व्योम __kobject_del(काष्ठा kobject *kobj)
अणु
	काष्ठा kernfs_node *sd;
	स्थिर काष्ठा kobj_type *ktype;

	sd = kobj->sd;
	ktype = get_ktype(kobj);

	अगर (ktype)
		sysfs_हटाओ_groups(kobj, ktype->शेष_groups);

	/* send "remove" अगर the caller did not करो it but sent "add" */
	अगर (kobj->state_add_uevent_sent && !kobj->state_हटाओ_uevent_sent) अणु
		pr_debug("kobject: '%s' (%p): auto cleanup 'remove' event\n",
			 kobject_name(kobj), kobj);
		kobject_uevent(kobj, KOBJ_REMOVE);
	पूर्ण

	sysfs_हटाओ_dir(kobj);
	sysfs_put(sd);

	kobj->state_in_sysfs = 0;
	kobj_kset_leave(kobj);
	kobj->parent = शून्य;
पूर्ण

/**
 * kobject_del() - Unlink kobject from hierarchy.
 * @kobj: object.
 *
 * This is the function that should be called to delete an object
 * successfully added via kobject_add().
 */
व्योम kobject_del(काष्ठा kobject *kobj)
अणु
	काष्ठा kobject *parent;

	अगर (!kobj)
		वापस;

	parent = kobj->parent;
	__kobject_del(kobj);
	kobject_put(parent);
पूर्ण
EXPORT_SYMBOL(kobject_del);

/**
 * kobject_get() - Increment refcount क्रम object.
 * @kobj: object.
 */
काष्ठा kobject *kobject_get(काष्ठा kobject *kobj)
अणु
	अगर (kobj) अणु
		अगर (!kobj->state_initialized)
			WARN(1, KERN_WARNING
				"kobject: '%s' (%p): is not initialized, yet kobject_get() is being called.\n",
			     kobject_name(kobj), kobj);
		kref_get(&kobj->kref);
	पूर्ण
	वापस kobj;
पूर्ण
EXPORT_SYMBOL(kobject_get);

काष्ठा kobject * __must_check kobject_get_unless_zero(काष्ठा kobject *kobj)
अणु
	अगर (!kobj)
		वापस शून्य;
	अगर (!kref_get_unless_zero(&kobj->kref))
		kobj = शून्य;
	वापस kobj;
पूर्ण
EXPORT_SYMBOL(kobject_get_unless_zero);

/*
 * kobject_cleanup - मुक्त kobject resources.
 * @kobj: object to cleanup
 */
अटल व्योम kobject_cleanup(काष्ठा kobject *kobj)
अणु
	काष्ठा kobject *parent = kobj->parent;
	काष्ठा kobj_type *t = get_ktype(kobj);
	स्थिर अक्षर *name = kobj->name;

	pr_debug("kobject: '%s' (%p): %s, parent %p\n",
		 kobject_name(kobj), kobj, __func__, kobj->parent);

	अगर (t && !t->release)
		pr_debug("kobject: '%s' (%p): does not have a release() function, it is broken and must be fixed. See Documentation/core-api/kobject.rst.\n",
			 kobject_name(kobj), kobj);

	/* हटाओ from sysfs अगर the caller did not करो it */
	अगर (kobj->state_in_sysfs) अणु
		pr_debug("kobject: '%s' (%p): auto cleanup kobject_del\n",
			 kobject_name(kobj), kobj);
		__kobject_del(kobj);
	पूर्ण अन्यथा अणु
		/* aव्योम dropping the parent reference unnecessarily */
		parent = शून्य;
	पूर्ण

	अगर (t && t->release) अणु
		pr_debug("kobject: '%s' (%p): calling ktype release\n",
			 kobject_name(kobj), kobj);
		t->release(kobj);
	पूर्ण

	/* मुक्त name अगर we allocated it */
	अगर (name) अणु
		pr_debug("kobject: '%s': free name\n", name);
		kमुक्त_स्थिर(name);
	पूर्ण

	kobject_put(parent);
पूर्ण

#अगर_घोषित CONFIG_DEBUG_KOBJECT_RELEASE
अटल व्योम kobject_delayed_cleanup(काष्ठा work_काष्ठा *work)
अणु
	kobject_cleanup(container_of(to_delayed_work(work),
				     काष्ठा kobject, release));
पूर्ण
#पूर्ण_अगर

अटल व्योम kobject_release(काष्ठा kref *kref)
अणु
	काष्ठा kobject *kobj = container_of(kref, काष्ठा kobject, kref);
#अगर_घोषित CONFIG_DEBUG_KOBJECT_RELEASE
	अचिन्हित दीर्घ delay = HZ + HZ * (get_अक्रमom_पूर्णांक() & 0x3);
	pr_info("kobject: '%s' (%p): %s, parent %p (delayed %ld)\n",
		 kobject_name(kobj), kobj, __func__, kobj->parent, delay);
	INIT_DELAYED_WORK(&kobj->release, kobject_delayed_cleanup);

	schedule_delayed_work(&kobj->release, delay);
#अन्यथा
	kobject_cleanup(kobj);
#पूर्ण_अगर
पूर्ण

/**
 * kobject_put() - Decrement refcount क्रम object.
 * @kobj: object.
 *
 * Decrement the refcount, and अगर 0, call kobject_cleanup().
 */
व्योम kobject_put(काष्ठा kobject *kobj)
अणु
	अगर (kobj) अणु
		अगर (!kobj->state_initialized)
			WARN(1, KERN_WARNING
				"kobject: '%s' (%p): is not initialized, yet kobject_put() is being called.\n",
			     kobject_name(kobj), kobj);
		kref_put(&kobj->kref, kobject_release);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(kobject_put);

अटल व्योम dynamic_kobj_release(काष्ठा kobject *kobj)
अणु
	pr_debug("kobject: (%p): %s\n", kobj, __func__);
	kमुक्त(kobj);
पूर्ण

अटल काष्ठा kobj_type dynamic_kobj_ktype = अणु
	.release	= dynamic_kobj_release,
	.sysfs_ops	= &kobj_sysfs_ops,
पूर्ण;

/**
 * kobject_create() - Create a काष्ठा kobject dynamically.
 *
 * This function creates a kobject काष्ठाure dynamically and sets it up
 * to be a "dynamic" kobject with a शेष release function set up.
 *
 * If the kobject was not able to be created, शून्य will be वापसed.
 * The kobject काष्ठाure वापसed from here must be cleaned up with a
 * call to kobject_put() and not kमुक्त(), as kobject_init() has
 * alपढ़ोy been called on this काष्ठाure.
 */
काष्ठा kobject *kobject_create(व्योम)
अणु
	काष्ठा kobject *kobj;

	kobj = kzalloc(माप(*kobj), GFP_KERNEL);
	अगर (!kobj)
		वापस शून्य;

	kobject_init(kobj, &dynamic_kobj_ktype);
	वापस kobj;
पूर्ण

/**
 * kobject_create_and_add() - Create a काष्ठा kobject dynamically and
 *                            रेजिस्टर it with sysfs.
 * @name: the name क्रम the kobject
 * @parent: the parent kobject of this kobject, अगर any.
 *
 * This function creates a kobject काष्ठाure dynamically and रेजिस्टरs it
 * with sysfs.  When you are finished with this काष्ठाure, call
 * kobject_put() and the काष्ठाure will be dynamically मुक्तd when
 * it is no दीर्घer being used.
 *
 * If the kobject was not able to be created, शून्य will be वापसed.
 */
काष्ठा kobject *kobject_create_and_add(स्थिर अक्षर *name, काष्ठा kobject *parent)
अणु
	काष्ठा kobject *kobj;
	पूर्णांक retval;

	kobj = kobject_create();
	अगर (!kobj)
		वापस शून्य;

	retval = kobject_add(kobj, parent, "%s", name);
	अगर (retval) अणु
		pr_warn("%s: kobject_add error: %d\n", __func__, retval);
		kobject_put(kobj);
		kobj = शून्य;
	पूर्ण
	वापस kobj;
पूर्ण
EXPORT_SYMBOL_GPL(kobject_create_and_add);

/**
 * kset_init() - Initialize a kset क्रम use.
 * @k: kset
 */
व्योम kset_init(काष्ठा kset *k)
अणु
	kobject_init_पूर्णांकernal(&k->kobj);
	INIT_LIST_HEAD(&k->list);
	spin_lock_init(&k->list_lock);
पूर्ण

/* शेष kobject attribute operations */
अटल sमाप_प्रकार kobj_attr_show(काष्ठा kobject *kobj, काष्ठा attribute *attr,
			      अक्षर *buf)
अणु
	काष्ठा kobj_attribute *kattr;
	sमाप_प्रकार ret = -EIO;

	kattr = container_of(attr, काष्ठा kobj_attribute, attr);
	अगर (kattr->show)
		ret = kattr->show(kobj, kattr, buf);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार kobj_attr_store(काष्ठा kobject *kobj, काष्ठा attribute *attr,
			       स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा kobj_attribute *kattr;
	sमाप_प्रकार ret = -EIO;

	kattr = container_of(attr, काष्ठा kobj_attribute, attr);
	अगर (kattr->store)
		ret = kattr->store(kobj, kattr, buf, count);
	वापस ret;
पूर्ण

स्थिर काष्ठा sysfs_ops kobj_sysfs_ops = अणु
	.show	= kobj_attr_show,
	.store	= kobj_attr_store,
पूर्ण;
EXPORT_SYMBOL_GPL(kobj_sysfs_ops);

/**
 * kset_रेजिस्टर() - Initialize and add a kset.
 * @k: kset.
 */
पूर्णांक kset_रेजिस्टर(काष्ठा kset *k)
अणु
	पूर्णांक err;

	अगर (!k)
		वापस -EINVAL;

	kset_init(k);
	err = kobject_add_पूर्णांकernal(&k->kobj);
	अगर (err)
		वापस err;
	kobject_uevent(&k->kobj, KOBJ_ADD);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(kset_रेजिस्टर);

/**
 * kset_unरेजिस्टर() - Remove a kset.
 * @k: kset.
 */
व्योम kset_unरेजिस्टर(काष्ठा kset *k)
अणु
	अगर (!k)
		वापस;
	kobject_del(&k->kobj);
	kobject_put(&k->kobj);
पूर्ण
EXPORT_SYMBOL(kset_unरेजिस्टर);

/**
 * kset_find_obj() - Search क्रम object in kset.
 * @kset: kset we're looking in.
 * @name: object's name.
 *
 * Lock kset via @kset->subsys, and iterate over @kset->list,
 * looking क्रम a matching kobject. If matching object is found
 * take a reference and वापस the object.
 */
काष्ठा kobject *kset_find_obj(काष्ठा kset *kset, स्थिर अक्षर *name)
अणु
	काष्ठा kobject *k;
	काष्ठा kobject *ret = शून्य;

	spin_lock(&kset->list_lock);

	list_क्रम_each_entry(k, &kset->list, entry) अणु
		अगर (kobject_name(k) && !म_भेद(kobject_name(k), name)) अणु
			ret = kobject_get_unless_zero(k);
			अवरोध;
		पूर्ण
	पूर्ण

	spin_unlock(&kset->list_lock);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(kset_find_obj);

अटल व्योम kset_release(काष्ठा kobject *kobj)
अणु
	काष्ठा kset *kset = container_of(kobj, काष्ठा kset, kobj);
	pr_debug("kobject: '%s' (%p): %s\n",
		 kobject_name(kobj), kobj, __func__);
	kमुक्त(kset);
पूर्ण

अटल व्योम kset_get_ownership(काष्ठा kobject *kobj, kuid_t *uid, kgid_t *gid)
अणु
	अगर (kobj->parent)
		kobject_get_ownership(kobj->parent, uid, gid);
पूर्ण

अटल काष्ठा kobj_type kset_ktype = अणु
	.sysfs_ops	= &kobj_sysfs_ops,
	.release	= kset_release,
	.get_ownership	= kset_get_ownership,
पूर्ण;

/**
 * kset_create() - Create a काष्ठा kset dynamically.
 *
 * @name: the name क्रम the kset
 * @uevent_ops: a काष्ठा kset_uevent_ops क्रम the kset
 * @parent_kobj: the parent kobject of this kset, अगर any.
 *
 * This function creates a kset काष्ठाure dynamically.  This काष्ठाure can
 * then be रेजिस्टरed with the प्रणाली and show up in sysfs with a call to
 * kset_रेजिस्टर().  When you are finished with this काष्ठाure, अगर
 * kset_रेजिस्टर() has been called, call kset_unरेजिस्टर() and the
 * काष्ठाure will be dynamically मुक्तd when it is no दीर्घer being used.
 *
 * If the kset was not able to be created, शून्य will be वापसed.
 */
अटल काष्ठा kset *kset_create(स्थिर अक्षर *name,
				स्थिर काष्ठा kset_uevent_ops *uevent_ops,
				काष्ठा kobject *parent_kobj)
अणु
	काष्ठा kset *kset;
	पूर्णांक retval;

	kset = kzalloc(माप(*kset), GFP_KERNEL);
	अगर (!kset)
		वापस शून्य;
	retval = kobject_set_name(&kset->kobj, "%s", name);
	अगर (retval) अणु
		kमुक्त(kset);
		वापस शून्य;
	पूर्ण
	kset->uevent_ops = uevent_ops;
	kset->kobj.parent = parent_kobj;

	/*
	 * The kobject of this kset will have a type of kset_ktype and beदीर्घ to
	 * no kset itself.  That way we can properly मुक्त it when it is
	 * finished being used.
	 */
	kset->kobj.ktype = &kset_ktype;
	kset->kobj.kset = शून्य;

	वापस kset;
पूर्ण

/**
 * kset_create_and_add() - Create a काष्ठा kset dynamically and add it to sysfs.
 *
 * @name: the name क्रम the kset
 * @uevent_ops: a काष्ठा kset_uevent_ops क्रम the kset
 * @parent_kobj: the parent kobject of this kset, अगर any.
 *
 * This function creates a kset काष्ठाure dynamically and रेजिस्टरs it
 * with sysfs.  When you are finished with this काष्ठाure, call
 * kset_unरेजिस्टर() and the काष्ठाure will be dynamically मुक्तd when it
 * is no दीर्घer being used.
 *
 * If the kset was not able to be created, शून्य will be वापसed.
 */
काष्ठा kset *kset_create_and_add(स्थिर अक्षर *name,
				 स्थिर काष्ठा kset_uevent_ops *uevent_ops,
				 काष्ठा kobject *parent_kobj)
अणु
	काष्ठा kset *kset;
	पूर्णांक error;

	kset = kset_create(name, uevent_ops, parent_kobj);
	अगर (!kset)
		वापस शून्य;
	error = kset_रेजिस्टर(kset);
	अगर (error) अणु
		kमुक्त(kset);
		वापस शून्य;
	पूर्ण
	वापस kset;
पूर्ण
EXPORT_SYMBOL_GPL(kset_create_and_add);


अटल DEFINE_SPINLOCK(kobj_ns_type_lock);
अटल स्थिर काष्ठा kobj_ns_type_operations *kobj_ns_ops_tbl[KOBJ_NS_TYPES];

पूर्णांक kobj_ns_type_रेजिस्टर(स्थिर काष्ठा kobj_ns_type_operations *ops)
अणु
	क्रमागत kobj_ns_type type = ops->type;
	पूर्णांक error;

	spin_lock(&kobj_ns_type_lock);

	error = -EINVAL;
	अगर (type >= KOBJ_NS_TYPES)
		जाओ out;

	error = -EINVAL;
	अगर (type <= KOBJ_NS_TYPE_NONE)
		जाओ out;

	error = -EBUSY;
	अगर (kobj_ns_ops_tbl[type])
		जाओ out;

	error = 0;
	kobj_ns_ops_tbl[type] = ops;

out:
	spin_unlock(&kobj_ns_type_lock);
	वापस error;
पूर्ण

पूर्णांक kobj_ns_type_रेजिस्टरed(क्रमागत kobj_ns_type type)
अणु
	पूर्णांक रेजिस्टरed = 0;

	spin_lock(&kobj_ns_type_lock);
	अगर ((type > KOBJ_NS_TYPE_NONE) && (type < KOBJ_NS_TYPES))
		रेजिस्टरed = kobj_ns_ops_tbl[type] != शून्य;
	spin_unlock(&kobj_ns_type_lock);

	वापस रेजिस्टरed;
पूर्ण

स्थिर काष्ठा kobj_ns_type_operations *kobj_child_ns_ops(काष्ठा kobject *parent)
अणु
	स्थिर काष्ठा kobj_ns_type_operations *ops = शून्य;

	अगर (parent && parent->ktype && parent->ktype->child_ns_type)
		ops = parent->ktype->child_ns_type(parent);

	वापस ops;
पूर्ण

स्थिर काष्ठा kobj_ns_type_operations *kobj_ns_ops(काष्ठा kobject *kobj)
अणु
	वापस kobj_child_ns_ops(kobj->parent);
पूर्ण

bool kobj_ns_current_may_mount(क्रमागत kobj_ns_type type)
अणु
	bool may_mount = true;

	spin_lock(&kobj_ns_type_lock);
	अगर ((type > KOBJ_NS_TYPE_NONE) && (type < KOBJ_NS_TYPES) &&
	    kobj_ns_ops_tbl[type])
		may_mount = kobj_ns_ops_tbl[type]->current_may_mount();
	spin_unlock(&kobj_ns_type_lock);

	वापस may_mount;
पूर्ण

व्योम *kobj_ns_grab_current(क्रमागत kobj_ns_type type)
अणु
	व्योम *ns = शून्य;

	spin_lock(&kobj_ns_type_lock);
	अगर ((type > KOBJ_NS_TYPE_NONE) && (type < KOBJ_NS_TYPES) &&
	    kobj_ns_ops_tbl[type])
		ns = kobj_ns_ops_tbl[type]->grab_current_ns();
	spin_unlock(&kobj_ns_type_lock);

	वापस ns;
पूर्ण
EXPORT_SYMBOL_GPL(kobj_ns_grab_current);

स्थिर व्योम *kobj_ns_netlink(क्रमागत kobj_ns_type type, काष्ठा sock *sk)
अणु
	स्थिर व्योम *ns = शून्य;

	spin_lock(&kobj_ns_type_lock);
	अगर ((type > KOBJ_NS_TYPE_NONE) && (type < KOBJ_NS_TYPES) &&
	    kobj_ns_ops_tbl[type])
		ns = kobj_ns_ops_tbl[type]->netlink_ns(sk);
	spin_unlock(&kobj_ns_type_lock);

	वापस ns;
पूर्ण

स्थिर व्योम *kobj_ns_initial(क्रमागत kobj_ns_type type)
अणु
	स्थिर व्योम *ns = शून्य;

	spin_lock(&kobj_ns_type_lock);
	अगर ((type > KOBJ_NS_TYPE_NONE) && (type < KOBJ_NS_TYPES) &&
	    kobj_ns_ops_tbl[type])
		ns = kobj_ns_ops_tbl[type]->initial_ns();
	spin_unlock(&kobj_ns_type_lock);

	वापस ns;
पूर्ण

व्योम kobj_ns_drop(क्रमागत kobj_ns_type type, व्योम *ns)
अणु
	spin_lock(&kobj_ns_type_lock);
	अगर ((type > KOBJ_NS_TYPE_NONE) && (type < KOBJ_NS_TYPES) &&
	    kobj_ns_ops_tbl[type] && kobj_ns_ops_tbl[type]->drop_ns)
		kobj_ns_ops_tbl[type]->drop_ns(ns);
	spin_unlock(&kobj_ns_type_lock);
पूर्ण
EXPORT_SYMBOL_GPL(kobj_ns_drop);
