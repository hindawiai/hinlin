<शैली गुरु>
/*
 * Copyright (C) 2001, 2002 Sistina Software (UK) Limited.
 * Copyright (C) 2004 - 2006 Red Hat, Inc. All rights reserved.
 *
 * This file is released under the GPL.
 */

#समावेश "dm-core.h"

#समावेश <linux/module.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/sched/mm.h>
#समावेश <linux/init.h>
#समावेश <linux/रुको.h>
#समावेश <linux/slab.h>
#समावेश <linux/rbtree.h>
#समावेश <linux/dm-ioctl.h>
#समावेश <linux/hdreg.h>
#समावेश <linux/compat.h>

#समावेश <linux/uaccess.h>

#घोषणा DM_MSG_PREFIX "ioctl"
#घोषणा DM_DRIVER_EMAIL "dm-devel@redhat.com"

काष्ठा dm_file अणु
	/*
	 * poll will रुको until the global event number is greater than
	 * this value.
	 */
	अस्थिर अचिन्हित global_event_nr;
पूर्ण;

/*-----------------------------------------------------------------
 * The ioctl पूर्णांकerface needs to be able to look up devices by
 * name or uuid.
 *---------------------------------------------------------------*/
काष्ठा hash_cell अणु
	काष्ठा rb_node name_node;
	काष्ठा rb_node uuid_node;
	bool name_set;
	bool uuid_set;

	अक्षर *name;
	अक्षर *uuid;
	काष्ठा mapped_device *md;
	काष्ठा dm_table *new_map;
पूर्ण;

काष्ठा vers_iter अणु
    माप_प्रकार param_size;
    काष्ठा dm_target_versions *vers, *old_vers;
    अक्षर *end;
    uपूर्णांक32_t flags;
पूर्ण;


अटल काष्ठा rb_root name_rb_tree = RB_ROOT;
अटल काष्ठा rb_root uuid_rb_tree = RB_ROOT;

अटल व्योम dm_hash_हटाओ_all(bool keep_खोलो_devices, bool mark_deferred, bool only_deferred);

/*
 * Guards access to both hash tables.
 */
अटल DECLARE_RWSEM(_hash_lock);

/*
 * Protects use of mdptr to obtain hash cell name and uuid from mapped device.
 */
अटल DEFINE_MUTEX(dm_hash_cells_mutex);

अटल व्योम dm_hash_निकास(व्योम)
अणु
	dm_hash_हटाओ_all(false, false, false);
पूर्ण

/*-----------------------------------------------------------------
 * Code क्रम looking up a device by name
 *---------------------------------------------------------------*/
अटल काष्ठा hash_cell *__get_name_cell(स्थिर अक्षर *str)
अणु
	काष्ठा rb_node *n = name_rb_tree.rb_node;

	जबतक (n) अणु
		काष्ठा hash_cell *hc = container_of(n, काष्ठा hash_cell, name_node);
		पूर्णांक c = म_भेद(hc->name, str);
		अगर (!c) अणु
			dm_get(hc->md);
			वापस hc;
		पूर्ण
		n = c >= 0 ? n->rb_left : n->rb_right;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा hash_cell *__get_uuid_cell(स्थिर अक्षर *str)
अणु
	काष्ठा rb_node *n = uuid_rb_tree.rb_node;

	जबतक (n) अणु
		काष्ठा hash_cell *hc = container_of(n, काष्ठा hash_cell, uuid_node);
		पूर्णांक c = म_भेद(hc->uuid, str);
		अगर (!c) अणु
			dm_get(hc->md);
			वापस hc;
		पूर्ण
		n = c >= 0 ? n->rb_left : n->rb_right;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम __unlink_name(काष्ठा hash_cell *hc)
अणु
	अगर (hc->name_set) अणु
		hc->name_set = false;
		rb_erase(&hc->name_node, &name_rb_tree);
	पूर्ण
पूर्ण

अटल व्योम __unlink_uuid(काष्ठा hash_cell *hc)
अणु
	अगर (hc->uuid_set) अणु
		hc->uuid_set = false;
		rb_erase(&hc->uuid_node, &uuid_rb_tree);
	पूर्ण
पूर्ण

अटल व्योम __link_name(काष्ठा hash_cell *new_hc)
अणु
	काष्ठा rb_node **n, *parent;

	__unlink_name(new_hc);

	new_hc->name_set = true;

	n = &name_rb_tree.rb_node;
	parent = शून्य;

	जबतक (*n) अणु
		काष्ठा hash_cell *hc = container_of(*n, काष्ठा hash_cell, name_node);
		पूर्णांक c = म_भेद(hc->name, new_hc->name);
		BUG_ON(!c);
		parent = *n;
		n = c >= 0 ? &hc->name_node.rb_left : &hc->name_node.rb_right;
	पूर्ण

	rb_link_node(&new_hc->name_node, parent, n);
	rb_insert_color(&new_hc->name_node, &name_rb_tree);
पूर्ण

अटल व्योम __link_uuid(काष्ठा hash_cell *new_hc)
अणु
	काष्ठा rb_node **n, *parent;

	__unlink_uuid(new_hc);

	new_hc->uuid_set = true;

	n = &uuid_rb_tree.rb_node;
	parent = शून्य;

	जबतक (*n) अणु
		काष्ठा hash_cell *hc = container_of(*n, काष्ठा hash_cell, uuid_node);
		पूर्णांक c = म_भेद(hc->uuid, new_hc->uuid);
		BUG_ON(!c);
		parent = *n;
		n = c > 0 ? &hc->uuid_node.rb_left : &hc->uuid_node.rb_right;
	पूर्ण

	rb_link_node(&new_hc->uuid_node, parent, n);
	rb_insert_color(&new_hc->uuid_node, &uuid_rb_tree);
पूर्ण

अटल काष्ठा hash_cell *__get_dev_cell(uपूर्णांक64_t dev)
अणु
	काष्ठा mapped_device *md;
	काष्ठा hash_cell *hc;

	md = dm_get_md(huge_decode_dev(dev));
	अगर (!md)
		वापस शून्य;

	hc = dm_get_mdptr(md);
	अगर (!hc) अणु
		dm_put(md);
		वापस शून्य;
	पूर्ण

	वापस hc;
पूर्ण

/*-----------------------------------------------------------------
 * Inserting, removing and renaming a device.
 *---------------------------------------------------------------*/
अटल काष्ठा hash_cell *alloc_cell(स्थिर अक्षर *name, स्थिर अक्षर *uuid,
				    काष्ठा mapped_device *md)
अणु
	काष्ठा hash_cell *hc;

	hc = kदो_स्मृति(माप(*hc), GFP_KERNEL);
	अगर (!hc)
		वापस शून्य;

	hc->name = kstrdup(name, GFP_KERNEL);
	अगर (!hc->name) अणु
		kमुक्त(hc);
		वापस शून्य;
	पूर्ण

	अगर (!uuid)
		hc->uuid = शून्य;

	अन्यथा अणु
		hc->uuid = kstrdup(uuid, GFP_KERNEL);
		अगर (!hc->uuid) अणु
			kमुक्त(hc->name);
			kमुक्त(hc);
			वापस शून्य;
		पूर्ण
	पूर्ण

	hc->name_set = hc->uuid_set = false;
	hc->md = md;
	hc->new_map = शून्य;
	वापस hc;
पूर्ण

अटल व्योम मुक्त_cell(काष्ठा hash_cell *hc)
अणु
	अगर (hc) अणु
		kमुक्त(hc->name);
		kमुक्त(hc->uuid);
		kमुक्त(hc);
	पूर्ण
पूर्ण

/*
 * The kdev_t and uuid of a device can never change once it is
 * initially inserted.
 */
अटल पूर्णांक dm_hash_insert(स्थिर अक्षर *name, स्थिर अक्षर *uuid, काष्ठा mapped_device *md)
अणु
	काष्ठा hash_cell *cell, *hc;

	/*
	 * Allocate the new cells.
	 */
	cell = alloc_cell(name, uuid, md);
	अगर (!cell)
		वापस -ENOMEM;

	/*
	 * Insert the cell पूर्णांकo both hash tables.
	 */
	करोwn_ग_लिखो(&_hash_lock);
	hc = __get_name_cell(name);
	अगर (hc) अणु
		dm_put(hc->md);
		जाओ bad;
	पूर्ण

	__link_name(cell);

	अगर (uuid) अणु
		hc = __get_uuid_cell(uuid);
		अगर (hc) अणु
			__unlink_name(cell);
			dm_put(hc->md);
			जाओ bad;
		पूर्ण
		__link_uuid(cell);
	पूर्ण
	dm_get(md);
	mutex_lock(&dm_hash_cells_mutex);
	dm_set_mdptr(md, cell);
	mutex_unlock(&dm_hash_cells_mutex);
	up_ग_लिखो(&_hash_lock);

	वापस 0;

 bad:
	up_ग_लिखो(&_hash_lock);
	मुक्त_cell(cell);
	वापस -EBUSY;
पूर्ण

अटल काष्ठा dm_table *__hash_हटाओ(काष्ठा hash_cell *hc)
अणु
	काष्ठा dm_table *table;
	पूर्णांक srcu_idx;

	/* हटाओ from the dev trees */
	__unlink_name(hc);
	__unlink_uuid(hc);
	mutex_lock(&dm_hash_cells_mutex);
	dm_set_mdptr(hc->md, शून्य);
	mutex_unlock(&dm_hash_cells_mutex);

	table = dm_get_live_table(hc->md, &srcu_idx);
	अगर (table)
		dm_table_event(table);
	dm_put_live_table(hc->md, srcu_idx);

	table = शून्य;
	अगर (hc->new_map)
		table = hc->new_map;
	dm_put(hc->md);
	मुक्त_cell(hc);

	वापस table;
पूर्ण

अटल व्योम dm_hash_हटाओ_all(bool keep_खोलो_devices, bool mark_deferred, bool only_deferred)
अणु
	पूर्णांक dev_skipped;
	काष्ठा rb_node *n;
	काष्ठा hash_cell *hc;
	काष्ठा mapped_device *md;
	काष्ठा dm_table *t;

retry:
	dev_skipped = 0;

	करोwn_ग_लिखो(&_hash_lock);

	क्रम (n = rb_first(&name_rb_tree); n; n = rb_next(n)) अणु
		hc = container_of(n, काष्ठा hash_cell, name_node);
		md = hc->md;
		dm_get(md);

		अगर (keep_खोलो_devices &&
		    dm_lock_क्रम_deletion(md, mark_deferred, only_deferred)) अणु
			dm_put(md);
			dev_skipped++;
			जारी;
		पूर्ण

		t = __hash_हटाओ(hc);

		up_ग_लिखो(&_hash_lock);

		अगर (t) अणु
			dm_sync_table(md);
			dm_table_destroy(t);
		पूर्ण
		dm_put(md);
		अगर (likely(keep_खोलो_devices))
			dm_destroy(md);
		अन्यथा
			dm_destroy_immediate(md);

		/*
		 * Some mapped devices may be using other mapped
		 * devices, so repeat until we make no further
		 * progress.  If a new mapped device is created
		 * here it will also get हटाओd.
		 */
		जाओ retry;
	पूर्ण

	up_ग_लिखो(&_hash_lock);

	अगर (dev_skipped)
		DMWARN("remove_all left %d open device(s)", dev_skipped);
पूर्ण

/*
 * Set the uuid of a hash_cell that isn't alपढ़ोy set.
 */
अटल व्योम __set_cell_uuid(काष्ठा hash_cell *hc, अक्षर *new_uuid)
अणु
	mutex_lock(&dm_hash_cells_mutex);
	hc->uuid = new_uuid;
	mutex_unlock(&dm_hash_cells_mutex);

	__link_uuid(hc);
पूर्ण

/*
 * Changes the name of a hash_cell and वापसs the old name क्रम
 * the caller to मुक्त.
 */
अटल अक्षर *__change_cell_name(काष्ठा hash_cell *hc, अक्षर *new_name)
अणु
	अक्षर *old_name;

	/*
	 * Rename and move the name cell.
	 */
	__unlink_name(hc);
	old_name = hc->name;

	mutex_lock(&dm_hash_cells_mutex);
	hc->name = new_name;
	mutex_unlock(&dm_hash_cells_mutex);

	__link_name(hc);

	वापस old_name;
पूर्ण

अटल काष्ठा mapped_device *dm_hash_नाम(काष्ठा dm_ioctl *param,
					    स्थिर अक्षर *new)
अणु
	अक्षर *new_data, *old_name = शून्य;
	काष्ठा hash_cell *hc;
	काष्ठा dm_table *table;
	काष्ठा mapped_device *md;
	अचिन्हित change_uuid = (param->flags & DM_UUID_FLAG) ? 1 : 0;
	पूर्णांक srcu_idx;

	/*
	 * duplicate new.
	 */
	new_data = kstrdup(new, GFP_KERNEL);
	अगर (!new_data)
		वापस ERR_PTR(-ENOMEM);

	करोwn_ग_लिखो(&_hash_lock);

	/*
	 * Is new मुक्त ?
	 */
	अगर (change_uuid)
		hc = __get_uuid_cell(new);
	अन्यथा
		hc = __get_name_cell(new);

	अगर (hc) अणु
		DMWARN("Unable to change %s on mapped device %s to one that "
		       "already exists: %s",
		       change_uuid ? "uuid" : "name",
		       param->name, new);
		dm_put(hc->md);
		up_ग_लिखो(&_hash_lock);
		kमुक्त(new_data);
		वापस ERR_PTR(-EBUSY);
	पूर्ण

	/*
	 * Is there such a device as 'old' ?
	 */
	hc = __get_name_cell(param->name);
	अगर (!hc) अणु
		DMWARN("Unable to rename non-existent device, %s to %s%s",
		       param->name, change_uuid ? "uuid " : "", new);
		up_ग_लिखो(&_hash_lock);
		kमुक्त(new_data);
		वापस ERR_PTR(-ENXIO);
	पूर्ण

	/*
	 * Does this device alपढ़ोy have a uuid?
	 */
	अगर (change_uuid && hc->uuid) अणु
		DMWARN("Unable to change uuid of mapped device %s to %s "
		       "because uuid is already set to %s",
		       param->name, new, hc->uuid);
		dm_put(hc->md);
		up_ग_लिखो(&_hash_lock);
		kमुक्त(new_data);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	अगर (change_uuid)
		__set_cell_uuid(hc, new_data);
	अन्यथा
		old_name = __change_cell_name(hc, new_data);

	/*
	 * Wake up any dm event रुकोers.
	 */
	table = dm_get_live_table(hc->md, &srcu_idx);
	अगर (table)
		dm_table_event(table);
	dm_put_live_table(hc->md, srcu_idx);

	अगर (!dm_kobject_uevent(hc->md, KOBJ_CHANGE, param->event_nr))
		param->flags |= DM_UEVENT_GENERATED_FLAG;

	md = hc->md;
	up_ग_लिखो(&_hash_lock);
	kमुक्त(old_name);

	वापस md;
पूर्ण

व्योम dm_deferred_हटाओ(व्योम)
अणु
	dm_hash_हटाओ_all(true, false, true);
पूर्ण

/*-----------------------------------------------------------------
 * Implementation of the ioctl commands
 *---------------------------------------------------------------*/
/*
 * All the ioctl commands get dispatched to functions with this
 * prototype.
 */
प्रकार पूर्णांक (*ioctl_fn)(काष्ठा file *filp, काष्ठा dm_ioctl *param, माप_प्रकार param_size);

अटल पूर्णांक हटाओ_all(काष्ठा file *filp, काष्ठा dm_ioctl *param, माप_प्रकार param_size)
अणु
	dm_hash_हटाओ_all(true, !!(param->flags & DM_DEFERRED_REMOVE), false);
	param->data_size = 0;
	वापस 0;
पूर्ण

/*
 * Round up the ptr to an 8-byte boundary.
 */
#घोषणा ALIGN_MASK 7
अटल अंतरभूत माप_प्रकार align_val(माप_प्रकार val)
अणु
	वापस (val + ALIGN_MASK) & ~ALIGN_MASK;
पूर्ण
अटल अंतरभूत व्योम *align_ptr(व्योम *ptr)
अणु
	वापस (व्योम *)align_val((माप_प्रकार)ptr);
पूर्ण

/*
 * Retrieves the data payload buffer from an alपढ़ोy allocated
 * काष्ठा dm_ioctl.
 */
अटल व्योम *get_result_buffer(काष्ठा dm_ioctl *param, माप_प्रकार param_size,
			       माप_प्रकार *len)
अणु
	param->data_start = align_ptr(param + 1) - (व्योम *) param;

	अगर (param->data_start < param_size)
		*len = param_size - param->data_start;
	अन्यथा
		*len = 0;

	वापस ((व्योम *) param) + param->data_start;
पूर्ण

अटल bool filter_device(काष्ठा hash_cell *hc, स्थिर अक्षर *pfx_name, स्थिर अक्षर *pfx_uuid)
अणु
	स्थिर अक्षर *val;
	माप_प्रकार val_len, pfx_len;

	val = hc->name;
	val_len = म_माप(val);
	pfx_len = strnlen(pfx_name, DM_NAME_LEN);
	अगर (pfx_len > val_len)
		वापस false;
	अगर (स_भेद(val, pfx_name, pfx_len))
		वापस false;

	val = hc->uuid ? hc->uuid : "";
	val_len = म_माप(val);
	pfx_len = strnlen(pfx_uuid, DM_UUID_LEN);
	अगर (pfx_len > val_len)
		वापस false;
	अगर (स_भेद(val, pfx_uuid, pfx_len))
		वापस false;

	वापस true;
पूर्ण

अटल पूर्णांक list_devices(काष्ठा file *filp, काष्ठा dm_ioctl *param, माप_प्रकार param_size)
अणु
	काष्ठा rb_node *n;
	काष्ठा hash_cell *hc;
	माप_प्रकार len, needed = 0;
	काष्ठा gendisk *disk;
	काष्ठा dm_name_list *orig_nl, *nl, *old_nl = शून्य;
	uपूर्णांक32_t *event_nr;

	करोwn_ग_लिखो(&_hash_lock);

	/*
	 * Loop through all the devices working out how much
	 * space we need.
	 */
	क्रम (n = rb_first(&name_rb_tree); n; n = rb_next(n)) अणु
		hc = container_of(n, काष्ठा hash_cell, name_node);
		अगर (!filter_device(hc, param->name, param->uuid))
			जारी;
		needed += align_val(दुरत्व(काष्ठा dm_name_list, name) + म_माप(hc->name) + 1);
		needed += align_val(माप(uपूर्णांक32_t) * 2);
		अगर (param->flags & DM_UUID_FLAG && hc->uuid)
			needed += align_val(म_माप(hc->uuid) + 1);
	पूर्ण

	/*
	 * Grab our output buffer.
	 */
	nl = orig_nl = get_result_buffer(param, param_size, &len);
	अगर (len < needed || len < माप(nl->dev)) अणु
		param->flags |= DM_BUFFER_FULL_FLAG;
		जाओ out;
	पूर्ण
	param->data_size = param->data_start + needed;

	nl->dev = 0;	/* Flags no data */

	/*
	 * Now loop through filling out the names.
	 */
	क्रम (n = rb_first(&name_rb_tree); n; n = rb_next(n)) अणु
		व्योम *uuid_ptr;
		hc = container_of(n, काष्ठा hash_cell, name_node);
		अगर (!filter_device(hc, param->name, param->uuid))
			जारी;
		अगर (old_nl)
			old_nl->next = (uपूर्णांक32_t) ((व्योम *) nl -
						   (व्योम *) old_nl);
		disk = dm_disk(hc->md);
		nl->dev = huge_encode_dev(disk_devt(disk));
		nl->next = 0;
		म_नकल(nl->name, hc->name);

		old_nl = nl;
		event_nr = align_ptr(nl->name + म_माप(hc->name) + 1);
		event_nr[0] = dm_get_event_nr(hc->md);
		event_nr[1] = 0;
		uuid_ptr = align_ptr(event_nr + 2);
		अगर (param->flags & DM_UUID_FLAG) अणु
			अगर (hc->uuid) अणु
				event_nr[1] |= DM_NAME_LIST_FLAG_HAS_UUID;
				म_नकल(uuid_ptr, hc->uuid);
				uuid_ptr = align_ptr(uuid_ptr + म_माप(hc->uuid) + 1);
			पूर्ण अन्यथा अणु
				event_nr[1] |= DM_NAME_LIST_FLAG_DOESNT_HAVE_UUID;
			पूर्ण
		पूर्ण
		nl = uuid_ptr;
	पूर्ण
	/*
	 * If mismatch happens, security may be compromised due to buffer
	 * overflow, so it's better to crash.
	 */
	BUG_ON((अक्षर *)nl - (अक्षर *)orig_nl != needed);

 out:
	up_ग_लिखो(&_hash_lock);
	वापस 0;
पूर्ण

अटल व्योम list_version_get_needed(काष्ठा target_type *tt, व्योम *needed_param)
अणु
    माप_प्रकार *needed = needed_param;

    *needed += माप(काष्ठा dm_target_versions);
    *needed += म_माप(tt->name);
    *needed += ALIGN_MASK;
पूर्ण

अटल व्योम list_version_get_info(काष्ठा target_type *tt, व्योम *param)
अणु
    काष्ठा vers_iter *info = param;

    /* Check space - it might have changed since the first iteration */
    अगर ((अक्षर *)info->vers + माप(tt->version) + म_माप(tt->name) + 1 >
	info->end) अणु

	info->flags = DM_BUFFER_FULL_FLAG;
	वापस;
    पूर्ण

    अगर (info->old_vers)
	info->old_vers->next = (uपूर्णांक32_t) ((व्योम *)info->vers -
					   (व्योम *)info->old_vers);
    info->vers->version[0] = tt->version[0];
    info->vers->version[1] = tt->version[1];
    info->vers->version[2] = tt->version[2];
    info->vers->next = 0;
    म_नकल(info->vers->name, tt->name);

    info->old_vers = info->vers;
    info->vers = align_ptr(((व्योम *) ++info->vers) + म_माप(tt->name) + 1);
पूर्ण

अटल पूर्णांक __list_versions(काष्ठा dm_ioctl *param, माप_प्रकार param_size, स्थिर अक्षर *name)
अणु
	माप_प्रकार len, needed = 0;
	काष्ठा dm_target_versions *vers;
	काष्ठा vers_iter iter_info;
	काष्ठा target_type *tt = शून्य;

	अगर (name) अणु
		tt = dm_get_target_type(name);
		अगर (!tt)
			वापस -EINVAL;
	पूर्ण

	/*
	 * Loop through all the devices working out how much
	 * space we need.
	 */
	अगर (!tt)
		dm_target_iterate(list_version_get_needed, &needed);
	अन्यथा
		list_version_get_needed(tt, &needed);

	/*
	 * Grab our output buffer.
	 */
	vers = get_result_buffer(param, param_size, &len);
	अगर (len < needed) अणु
		param->flags |= DM_BUFFER_FULL_FLAG;
		जाओ out;
	पूर्ण
	param->data_size = param->data_start + needed;

	iter_info.param_size = param_size;
	iter_info.old_vers = शून्य;
	iter_info.vers = vers;
	iter_info.flags = 0;
	iter_info.end = (अक्षर *)vers+len;

	/*
	 * Now loop through filling out the names & versions.
	 */
	अगर (!tt)
		dm_target_iterate(list_version_get_info, &iter_info);
	अन्यथा
		list_version_get_info(tt, &iter_info);
	param->flags |= iter_info.flags;

 out:
	अगर (tt)
		dm_put_target_type(tt);
	वापस 0;
पूर्ण

अटल पूर्णांक list_versions(काष्ठा file *filp, काष्ठा dm_ioctl *param, माप_प्रकार param_size)
अणु
	वापस __list_versions(param, param_size, शून्य);
पूर्ण

अटल पूर्णांक get_target_version(काष्ठा file *filp, काष्ठा dm_ioctl *param, माप_प्रकार param_size)
अणु
	वापस __list_versions(param, param_size, param->name);
पूर्ण

अटल पूर्णांक check_name(स्थिर अक्षर *name)
अणु
	अगर (म_अक्षर(name, '/')) अणु
		DMWARN("invalid device name");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * On successful वापस, the caller must not attempt to acquire
 * _hash_lock without first calling dm_put_live_table, because dm_table_destroy
 * रुकोs क्रम this dm_put_live_table and could be called under this lock.
 */
अटल काष्ठा dm_table *dm_get_inactive_table(काष्ठा mapped_device *md, पूर्णांक *srcu_idx)
अणु
	काष्ठा hash_cell *hc;
	काष्ठा dm_table *table = शून्य;

	/* increment rcu count, we करोn't care about the table poपूर्णांकer */
	dm_get_live_table(md, srcu_idx);

	करोwn_पढ़ो(&_hash_lock);
	hc = dm_get_mdptr(md);
	अगर (!hc || hc->md != md) अणु
		DMWARN("device has been removed from the dev hash table.");
		जाओ out;
	पूर्ण

	table = hc->new_map;

out:
	up_पढ़ो(&_hash_lock);

	वापस table;
पूर्ण

अटल काष्ठा dm_table *dm_get_live_or_inactive_table(काष्ठा mapped_device *md,
						      काष्ठा dm_ioctl *param,
						      पूर्णांक *srcu_idx)
अणु
	वापस (param->flags & DM_QUERY_INACTIVE_TABLE_FLAG) ?
		dm_get_inactive_table(md, srcu_idx) : dm_get_live_table(md, srcu_idx);
पूर्ण

/*
 * Fills in a dm_ioctl काष्ठाure, पढ़ोy क्रम sending back to
 * userland.
 */
अटल व्योम __dev_status(काष्ठा mapped_device *md, काष्ठा dm_ioctl *param)
अणु
	काष्ठा gendisk *disk = dm_disk(md);
	काष्ठा dm_table *table;
	पूर्णांक srcu_idx;

	param->flags &= ~(DM_SUSPEND_FLAG | DM_READONLY_FLAG |
			  DM_ACTIVE_PRESENT_FLAG | DM_INTERNAL_SUSPEND_FLAG);

	अगर (dm_suspended_md(md))
		param->flags |= DM_SUSPEND_FLAG;

	अगर (dm_suspended_पूर्णांकernally_md(md))
		param->flags |= DM_INTERNAL_SUSPEND_FLAG;

	अगर (dm_test_deferred_हटाओ_flag(md))
		param->flags |= DM_DEFERRED_REMOVE;

	param->dev = huge_encode_dev(disk_devt(disk));

	/*
	 * Yes, this will be out of date by the समय it माला_लो back
	 * to userland, but it is still very useful क्रम
	 * debugging.
	 */
	param->खोलो_count = dm_खोलो_count(md);

	param->event_nr = dm_get_event_nr(md);
	param->target_count = 0;

	table = dm_get_live_table(md, &srcu_idx);
	अगर (table) अणु
		अगर (!(param->flags & DM_QUERY_INACTIVE_TABLE_FLAG)) अणु
			अगर (get_disk_ro(disk))
				param->flags |= DM_READONLY_FLAG;
			param->target_count = dm_table_get_num_tarमाला_लो(table);
		पूर्ण

		param->flags |= DM_ACTIVE_PRESENT_FLAG;
	पूर्ण
	dm_put_live_table(md, srcu_idx);

	अगर (param->flags & DM_QUERY_INACTIVE_TABLE_FLAG) अणु
		पूर्णांक srcu_idx;
		table = dm_get_inactive_table(md, &srcu_idx);
		अगर (table) अणु
			अगर (!(dm_table_get_mode(table) & FMODE_WRITE))
				param->flags |= DM_READONLY_FLAG;
			param->target_count = dm_table_get_num_tarमाला_लो(table);
		पूर्ण
		dm_put_live_table(md, srcu_idx);
	पूर्ण
पूर्ण

अटल पूर्णांक dev_create(काष्ठा file *filp, काष्ठा dm_ioctl *param, माप_प्रकार param_size)
अणु
	पूर्णांक r, m = DM_ANY_MINOR;
	काष्ठा mapped_device *md;

	r = check_name(param->name);
	अगर (r)
		वापस r;

	अगर (param->flags & DM_PERSISTENT_DEV_FLAG)
		m = MINOR(huge_decode_dev(param->dev));

	r = dm_create(m, &md);
	अगर (r)
		वापस r;

	r = dm_hash_insert(param->name, *param->uuid ? param->uuid : शून्य, md);
	अगर (r) अणु
		dm_put(md);
		dm_destroy(md);
		वापस r;
	पूर्ण

	param->flags &= ~DM_INACTIVE_PRESENT_FLAG;

	__dev_status(md, param);

	dm_put(md);

	वापस 0;
पूर्ण

/*
 * Always use UUID क्रम lookups अगर it's present, otherwise use name or dev.
 */
अटल काष्ठा hash_cell *__find_device_hash_cell(काष्ठा dm_ioctl *param)
अणु
	काष्ठा hash_cell *hc = शून्य;

	अगर (*param->uuid) अणु
		अगर (*param->name || param->dev)
			वापस शून्य;

		hc = __get_uuid_cell(param->uuid);
		अगर (!hc)
			वापस शून्य;
	पूर्ण अन्यथा अगर (*param->name) अणु
		अगर (param->dev)
			वापस शून्य;

		hc = __get_name_cell(param->name);
		अगर (!hc)
			वापस शून्य;
	पूर्ण अन्यथा अगर (param->dev) अणु
		hc = __get_dev_cell(param->dev);
		अगर (!hc)
			वापस शून्य;
	पूर्ण अन्यथा
		वापस शून्य;

	/*
	 * Sneakily ग_लिखो in both the name and the uuid
	 * जबतक we have the cell.
	 */
	strlcpy(param->name, hc->name, माप(param->name));
	अगर (hc->uuid)
		strlcpy(param->uuid, hc->uuid, माप(param->uuid));
	अन्यथा
		param->uuid[0] = '\0';

	अगर (hc->new_map)
		param->flags |= DM_INACTIVE_PRESENT_FLAG;
	अन्यथा
		param->flags &= ~DM_INACTIVE_PRESENT_FLAG;

	वापस hc;
पूर्ण

अटल काष्ठा mapped_device *find_device(काष्ठा dm_ioctl *param)
अणु
	काष्ठा hash_cell *hc;
	काष्ठा mapped_device *md = शून्य;

	करोwn_पढ़ो(&_hash_lock);
	hc = __find_device_hash_cell(param);
	अगर (hc)
		md = hc->md;
	up_पढ़ो(&_hash_lock);

	वापस md;
पूर्ण

अटल पूर्णांक dev_हटाओ(काष्ठा file *filp, काष्ठा dm_ioctl *param, माप_प्रकार param_size)
अणु
	काष्ठा hash_cell *hc;
	काष्ठा mapped_device *md;
	पूर्णांक r;
	काष्ठा dm_table *t;

	करोwn_ग_लिखो(&_hash_lock);
	hc = __find_device_hash_cell(param);

	अगर (!hc) अणु
		DMDEBUG_LIMIT("device doesn't appear to be in the dev hash table.");
		up_ग_लिखो(&_hash_lock);
		वापस -ENXIO;
	पूर्ण

	md = hc->md;

	/*
	 * Ensure the device is not खोलो and nothing further can खोलो it.
	 */
	r = dm_lock_क्रम_deletion(md, !!(param->flags & DM_DEFERRED_REMOVE), false);
	अगर (r) अणु
		अगर (r == -EBUSY && param->flags & DM_DEFERRED_REMOVE) अणु
			up_ग_लिखो(&_hash_lock);
			dm_put(md);
			वापस 0;
		पूर्ण
		DMDEBUG_LIMIT("unable to remove open device %s", hc->name);
		up_ग_लिखो(&_hash_lock);
		dm_put(md);
		वापस r;
	पूर्ण

	t = __hash_हटाओ(hc);
	up_ग_लिखो(&_hash_lock);

	अगर (t) अणु
		dm_sync_table(md);
		dm_table_destroy(t);
	पूर्ण

	param->flags &= ~DM_DEFERRED_REMOVE;

	अगर (!dm_kobject_uevent(md, KOBJ_REMOVE, param->event_nr))
		param->flags |= DM_UEVENT_GENERATED_FLAG;

	dm_put(md);
	dm_destroy(md);
	वापस 0;
पूर्ण

/*
 * Check a string करोesn't overrun the chunk of
 * memory we copied from userland.
 */
अटल पूर्णांक invalid_str(अक्षर *str, व्योम *end)
अणु
	जबतक ((व्योम *) str < end)
		अगर (!*str++)
			वापस 0;

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक dev_नाम(काष्ठा file *filp, काष्ठा dm_ioctl *param, माप_प्रकार param_size)
अणु
	पूर्णांक r;
	अक्षर *new_data = (अक्षर *) param + param->data_start;
	काष्ठा mapped_device *md;
	अचिन्हित change_uuid = (param->flags & DM_UUID_FLAG) ? 1 : 0;

	अगर (new_data < param->data ||
	    invalid_str(new_data, (व्योम *) param + param_size) || !*new_data ||
	    म_माप(new_data) > (change_uuid ? DM_UUID_LEN - 1 : DM_NAME_LEN - 1)) अणु
		DMWARN("Invalid new mapped device name or uuid string supplied.");
		वापस -EINVAL;
	पूर्ण

	अगर (!change_uuid) अणु
		r = check_name(new_data);
		अगर (r)
			वापस r;
	पूर्ण

	md = dm_hash_नाम(param, new_data);
	अगर (IS_ERR(md))
		वापस PTR_ERR(md);

	__dev_status(md, param);
	dm_put(md);

	वापस 0;
पूर्ण

अटल पूर्णांक dev_set_geometry(काष्ठा file *filp, काष्ठा dm_ioctl *param, माप_प्रकार param_size)
अणु
	पूर्णांक r = -EINVAL, x;
	काष्ठा mapped_device *md;
	काष्ठा hd_geometry geometry;
	अचिन्हित दीर्घ indata[4];
	अक्षर *geostr = (अक्षर *) param + param->data_start;
	अक्षर dummy;

	md = find_device(param);
	अगर (!md)
		वापस -ENXIO;

	अगर (geostr < param->data ||
	    invalid_str(geostr, (व्योम *) param + param_size)) अणु
		DMWARN("Invalid geometry supplied.");
		जाओ out;
	पूर्ण

	x = माला_पूछो(geostr, "%lu %lu %lu %lu%c", indata,
		   indata + 1, indata + 2, indata + 3, &dummy);

	अगर (x != 4) अणु
		DMWARN("Unable to interpret geometry settings.");
		जाओ out;
	पूर्ण

	अगर (indata[0] > 65535 || indata[1] > 255 ||
	    indata[2] > 255 || indata[3] > अच_दीर्घ_उच्च) अणु
		DMWARN("Geometry exceeds range limits.");
		जाओ out;
	पूर्ण

	geometry.cylinders = indata[0];
	geometry.heads = indata[1];
	geometry.sectors = indata[2];
	geometry.start = indata[3];

	r = dm_set_geometry(md, &geometry);

	param->data_size = 0;

out:
	dm_put(md);
	वापस r;
पूर्ण

अटल पूर्णांक करो_suspend(काष्ठा dm_ioctl *param)
अणु
	पूर्णांक r = 0;
	अचिन्हित suspend_flags = DM_SUSPEND_LOCKFS_FLAG;
	काष्ठा mapped_device *md;

	md = find_device(param);
	अगर (!md)
		वापस -ENXIO;

	अगर (param->flags & DM_SKIP_LOCKFS_FLAG)
		suspend_flags &= ~DM_SUSPEND_LOCKFS_FLAG;
	अगर (param->flags & DM_NOFLUSH_FLAG)
		suspend_flags |= DM_SUSPEND_NOFLUSH_FLAG;

	अगर (!dm_suspended_md(md)) अणु
		r = dm_suspend(md, suspend_flags);
		अगर (r)
			जाओ out;
	पूर्ण

	__dev_status(md, param);

out:
	dm_put(md);

	वापस r;
पूर्ण

अटल पूर्णांक करो_resume(काष्ठा dm_ioctl *param)
अणु
	पूर्णांक r = 0;
	अचिन्हित suspend_flags = DM_SUSPEND_LOCKFS_FLAG;
	काष्ठा hash_cell *hc;
	काष्ठा mapped_device *md;
	काष्ठा dm_table *new_map, *old_map = शून्य;

	करोwn_ग_लिखो(&_hash_lock);

	hc = __find_device_hash_cell(param);
	अगर (!hc) अणु
		DMDEBUG_LIMIT("device doesn't appear to be in the dev hash table.");
		up_ग_लिखो(&_hash_lock);
		वापस -ENXIO;
	पूर्ण

	md = hc->md;

	new_map = hc->new_map;
	hc->new_map = शून्य;
	param->flags &= ~DM_INACTIVE_PRESENT_FLAG;

	up_ग_लिखो(&_hash_lock);

	/* Do we need to load a new map ? */
	अगर (new_map) अणु
		/* Suspend अगर it isn't alपढ़ोy suspended */
		अगर (param->flags & DM_SKIP_LOCKFS_FLAG)
			suspend_flags &= ~DM_SUSPEND_LOCKFS_FLAG;
		अगर (param->flags & DM_NOFLUSH_FLAG)
			suspend_flags |= DM_SUSPEND_NOFLUSH_FLAG;
		अगर (!dm_suspended_md(md))
			dm_suspend(md, suspend_flags);

		old_map = dm_swap_table(md, new_map);
		अगर (IS_ERR(old_map)) अणु
			dm_sync_table(md);
			dm_table_destroy(new_map);
			dm_put(md);
			वापस PTR_ERR(old_map);
		पूर्ण

		अगर (dm_table_get_mode(new_map) & FMODE_WRITE)
			set_disk_ro(dm_disk(md), 0);
		अन्यथा
			set_disk_ro(dm_disk(md), 1);
	पूर्ण

	अगर (dm_suspended_md(md)) अणु
		r = dm_resume(md);
		अगर (!r && !dm_kobject_uevent(md, KOBJ_CHANGE, param->event_nr))
			param->flags |= DM_UEVENT_GENERATED_FLAG;
	पूर्ण

	/*
	 * Since dm_swap_table synchronizes RCU, nobody should be in
	 * पढ़ो-side critical section alपढ़ोy.
	 */
	अगर (old_map)
		dm_table_destroy(old_map);

	अगर (!r)
		__dev_status(md, param);

	dm_put(md);
	वापस r;
पूर्ण

/*
 * Set or unset the suspension state of a device.
 * If the device alपढ़ोy is in the requested state we just वापस its status.
 */
अटल पूर्णांक dev_suspend(काष्ठा file *filp, काष्ठा dm_ioctl *param, माप_प्रकार param_size)
अणु
	अगर (param->flags & DM_SUSPEND_FLAG)
		वापस करो_suspend(param);

	वापस करो_resume(param);
पूर्ण

/*
 * Copies device info back to user space, used by
 * the create and info ioctls.
 */
अटल पूर्णांक dev_status(काष्ठा file *filp, काष्ठा dm_ioctl *param, माप_प्रकार param_size)
अणु
	काष्ठा mapped_device *md;

	md = find_device(param);
	अगर (!md)
		वापस -ENXIO;

	__dev_status(md, param);
	dm_put(md);

	वापस 0;
पूर्ण

/*
 * Build up the status काष्ठा क्रम each target
 */
अटल व्योम retrieve_status(काष्ठा dm_table *table,
			    काष्ठा dm_ioctl *param, माप_प्रकार param_size)
अणु
	अचिन्हित पूर्णांक i, num_tarमाला_लो;
	काष्ठा dm_target_spec *spec;
	अक्षर *outbuf, *outptr;
	status_type_t type;
	माप_प्रकार reमुख्यing, len, used = 0;
	अचिन्हित status_flags = 0;

	outptr = outbuf = get_result_buffer(param, param_size, &len);

	अगर (param->flags & DM_STATUS_TABLE_FLAG)
		type = STATUSTYPE_TABLE;
	अन्यथा
		type = STATUSTYPE_INFO;

	/* Get all the target info */
	num_tarमाला_लो = dm_table_get_num_tarमाला_लो(table);
	क्रम (i = 0; i < num_tarमाला_लो; i++) अणु
		काष्ठा dm_target *ti = dm_table_get_target(table, i);
		माप_प्रकार l;

		reमुख्यing = len - (outptr - outbuf);
		अगर (reमुख्यing <= माप(काष्ठा dm_target_spec)) अणु
			param->flags |= DM_BUFFER_FULL_FLAG;
			अवरोध;
		पूर्ण

		spec = (काष्ठा dm_target_spec *) outptr;

		spec->status = 0;
		spec->sector_start = ti->begin;
		spec->length = ti->len;
		म_नकलन(spec->target_type, ti->type->name,
			माप(spec->target_type) - 1);

		outptr += माप(काष्ठा dm_target_spec);
		reमुख्यing = len - (outptr - outbuf);
		अगर (reमुख्यing <= 0) अणु
			param->flags |= DM_BUFFER_FULL_FLAG;
			अवरोध;
		पूर्ण

		/* Get the status/table string from the target driver */
		अगर (ti->type->status) अणु
			अगर (param->flags & DM_NOFLUSH_FLAG)
				status_flags |= DM_STATUS_NOFLUSH_FLAG;
			ti->type->status(ti, type, status_flags, outptr, reमुख्यing);
		पूर्ण अन्यथा
			outptr[0] = '\0';

		l = म_माप(outptr) + 1;
		अगर (l == reमुख्यing) अणु
			param->flags |= DM_BUFFER_FULL_FLAG;
			अवरोध;
		पूर्ण

		outptr += l;
		used = param->data_start + (outptr - outbuf);

		outptr = align_ptr(outptr);
		spec->next = outptr - outbuf;
	पूर्ण

	अगर (used)
		param->data_size = used;

	param->target_count = num_tarमाला_लो;
पूर्ण

/*
 * Wait क्रम a device to report an event
 */
अटल पूर्णांक dev_रुको(काष्ठा file *filp, काष्ठा dm_ioctl *param, माप_प्रकार param_size)
अणु
	पूर्णांक r = 0;
	काष्ठा mapped_device *md;
	काष्ठा dm_table *table;
	पूर्णांक srcu_idx;

	md = find_device(param);
	अगर (!md)
		वापस -ENXIO;

	/*
	 * Wait क्रम a notअगरication event
	 */
	अगर (dm_रुको_event(md, param->event_nr)) अणु
		r = -ERESTARTSYS;
		जाओ out;
	पूर्ण

	/*
	 * The userland program is going to want to know what
	 * changed to trigger the event, so we may as well tell
	 * him and save an ioctl.
	 */
	__dev_status(md, param);

	table = dm_get_live_or_inactive_table(md, param, &srcu_idx);
	अगर (table)
		retrieve_status(table, param, param_size);
	dm_put_live_table(md, srcu_idx);

out:
	dm_put(md);

	वापस r;
पूर्ण

/*
 * Remember the global event number and make it possible to poll
 * क्रम further events.
 */
अटल पूर्णांक dev_arm_poll(काष्ठा file *filp, काष्ठा dm_ioctl *param, माप_प्रकार param_size)
अणु
	काष्ठा dm_file *priv = filp->निजी_data;

	priv->global_event_nr = atomic_पढ़ो(&dm_global_event_nr);

	वापस 0;
पूर्ण

अटल अंतरभूत भ_शेषe_t get_mode(काष्ठा dm_ioctl *param)
अणु
	भ_शेषe_t mode = FMODE_READ | FMODE_WRITE;

	अगर (param->flags & DM_READONLY_FLAG)
		mode = FMODE_READ;

	वापस mode;
पूर्ण

अटल पूर्णांक next_target(काष्ठा dm_target_spec *last, uपूर्णांक32_t next, व्योम *end,
		       काष्ठा dm_target_spec **spec, अक्षर **target_params)
अणु
	*spec = (काष्ठा dm_target_spec *) ((अचिन्हित अक्षर *) last + next);
	*target_params = (अक्षर *) (*spec + 1);

	अगर (*spec < (last + 1))
		वापस -EINVAL;

	वापस invalid_str(*target_params, end);
पूर्ण

अटल पूर्णांक populate_table(काष्ठा dm_table *table,
			  काष्ठा dm_ioctl *param, माप_प्रकार param_size)
अणु
	पूर्णांक r;
	अचिन्हित पूर्णांक i = 0;
	काष्ठा dm_target_spec *spec = (काष्ठा dm_target_spec *) param;
	uपूर्णांक32_t next = param->data_start;
	व्योम *end = (व्योम *) param + param_size;
	अक्षर *target_params;

	अगर (!param->target_count) अणु
		DMWARN("populate_table: no targets specified");
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < param->target_count; i++) अणु

		r = next_target(spec, next, end, &spec, &target_params);
		अगर (r) अणु
			DMWARN("unable to find target");
			वापस r;
		पूर्ण

		r = dm_table_add_target(table, spec->target_type,
					(sector_t) spec->sector_start,
					(sector_t) spec->length,
					target_params);
		अगर (r) अणु
			DMWARN("error adding target to table");
			वापस r;
		पूर्ण

		next = spec->next;
	पूर्ण

	वापस dm_table_complete(table);
पूर्ण

अटल bool is_valid_type(क्रमागत dm_queue_mode cur, क्रमागत dm_queue_mode new)
अणु
	अगर (cur == new ||
	    (cur == DM_TYPE_BIO_BASED && new == DM_TYPE_DAX_BIO_BASED))
		वापस true;

	वापस false;
पूर्ण

अटल पूर्णांक table_load(काष्ठा file *filp, काष्ठा dm_ioctl *param, माप_प्रकार param_size)
अणु
	पूर्णांक r;
	काष्ठा hash_cell *hc;
	काष्ठा dm_table *t, *old_map = शून्य;
	काष्ठा mapped_device *md;
	काष्ठा target_type *immutable_target_type;

	md = find_device(param);
	अगर (!md)
		वापस -ENXIO;

	r = dm_table_create(&t, get_mode(param), param->target_count, md);
	अगर (r)
		जाओ err;

	/* Protect md->type and md->queue against concurrent table loads. */
	dm_lock_md_type(md);
	r = populate_table(t, param, param_size);
	अगर (r)
		जाओ err_unlock_md_type;

	immutable_target_type = dm_get_immutable_target_type(md);
	अगर (immutable_target_type &&
	    (immutable_target_type != dm_table_get_immutable_target_type(t)) &&
	    !dm_table_get_wildcard_target(t)) अणु
		DMWARN("can't replace immutable target type %s",
		       immutable_target_type->name);
		r = -EINVAL;
		जाओ err_unlock_md_type;
	पूर्ण

	अगर (dm_get_md_type(md) == DM_TYPE_NONE) अणु
		/* Initial table load: acquire type of table. */
		dm_set_md_type(md, dm_table_get_type(t));

		/* setup md->queue to reflect md's type (may block) */
		r = dm_setup_md_queue(md, t);
		अगर (r) अणु
			DMWARN("unable to set up device queue for new table.");
			जाओ err_unlock_md_type;
		पूर्ण
	पूर्ण अन्यथा अगर (!is_valid_type(dm_get_md_type(md), dm_table_get_type(t))) अणु
		DMWARN("can't change device type (old=%u vs new=%u) after initial table load.",
		       dm_get_md_type(md), dm_table_get_type(t));
		r = -EINVAL;
		जाओ err_unlock_md_type;
	पूर्ण

	dm_unlock_md_type(md);

	/* stage inactive table */
	करोwn_ग_लिखो(&_hash_lock);
	hc = dm_get_mdptr(md);
	अगर (!hc || hc->md != md) अणु
		DMWARN("device has been removed from the dev hash table.");
		up_ग_लिखो(&_hash_lock);
		r = -ENXIO;
		जाओ err_destroy_table;
	पूर्ण

	अगर (hc->new_map)
		old_map = hc->new_map;
	hc->new_map = t;
	up_ग_लिखो(&_hash_lock);

	param->flags |= DM_INACTIVE_PRESENT_FLAG;
	__dev_status(md, param);

	अगर (old_map) अणु
		dm_sync_table(md);
		dm_table_destroy(old_map);
	पूर्ण

	dm_put(md);

	वापस 0;

err_unlock_md_type:
	dm_unlock_md_type(md);
err_destroy_table:
	dm_table_destroy(t);
err:
	dm_put(md);

	वापस r;
पूर्ण

अटल पूर्णांक table_clear(काष्ठा file *filp, काष्ठा dm_ioctl *param, माप_प्रकार param_size)
अणु
	काष्ठा hash_cell *hc;
	काष्ठा mapped_device *md;
	काष्ठा dm_table *old_map = शून्य;

	करोwn_ग_लिखो(&_hash_lock);

	hc = __find_device_hash_cell(param);
	अगर (!hc) अणु
		DMDEBUG_LIMIT("device doesn't appear to be in the dev hash table.");
		up_ग_लिखो(&_hash_lock);
		वापस -ENXIO;
	पूर्ण

	अगर (hc->new_map) अणु
		old_map = hc->new_map;
		hc->new_map = शून्य;
	पूर्ण

	param->flags &= ~DM_INACTIVE_PRESENT_FLAG;

	__dev_status(hc->md, param);
	md = hc->md;
	up_ग_लिखो(&_hash_lock);
	अगर (old_map) अणु
		dm_sync_table(md);
		dm_table_destroy(old_map);
	पूर्ण
	dm_put(md);

	वापस 0;
पूर्ण

/*
 * Retrieves a list of devices used by a particular dm device.
 */
अटल व्योम retrieve_deps(काष्ठा dm_table *table,
			  काष्ठा dm_ioctl *param, माप_प्रकार param_size)
अणु
	अचिन्हित पूर्णांक count = 0;
	काष्ठा list_head *पंचांगp;
	माप_प्रकार len, needed;
	काष्ठा dm_dev_पूर्णांकernal *dd;
	काष्ठा dm_target_deps *deps;

	deps = get_result_buffer(param, param_size, &len);

	/*
	 * Count the devices.
	 */
	list_क्रम_each (पंचांगp, dm_table_get_devices(table))
		count++;

	/*
	 * Check we have enough space.
	 */
	needed = काष्ठा_size(deps, dev, count);
	अगर (len < needed) अणु
		param->flags |= DM_BUFFER_FULL_FLAG;
		वापस;
	पूर्ण

	/*
	 * Fill in the devices.
	 */
	deps->count = count;
	count = 0;
	list_क्रम_each_entry (dd, dm_table_get_devices(table), list)
		deps->dev[count++] = huge_encode_dev(dd->dm_dev->bdev->bd_dev);

	param->data_size = param->data_start + needed;
पूर्ण

अटल पूर्णांक table_deps(काष्ठा file *filp, काष्ठा dm_ioctl *param, माप_प्रकार param_size)
अणु
	काष्ठा mapped_device *md;
	काष्ठा dm_table *table;
	पूर्णांक srcu_idx;

	md = find_device(param);
	अगर (!md)
		वापस -ENXIO;

	__dev_status(md, param);

	table = dm_get_live_or_inactive_table(md, param, &srcu_idx);
	अगर (table)
		retrieve_deps(table, param, param_size);
	dm_put_live_table(md, srcu_idx);

	dm_put(md);

	वापस 0;
पूर्ण

/*
 * Return the status of a device as a text string क्रम each
 * target.
 */
अटल पूर्णांक table_status(काष्ठा file *filp, काष्ठा dm_ioctl *param, माप_प्रकार param_size)
अणु
	काष्ठा mapped_device *md;
	काष्ठा dm_table *table;
	पूर्णांक srcu_idx;

	md = find_device(param);
	अगर (!md)
		वापस -ENXIO;

	__dev_status(md, param);

	table = dm_get_live_or_inactive_table(md, param, &srcu_idx);
	अगर (table)
		retrieve_status(table, param, param_size);
	dm_put_live_table(md, srcu_idx);

	dm_put(md);

	वापस 0;
पूर्ण

/*
 * Process device-mapper dependent messages.  Messages prefixed with '@'
 * are processed by the DM core.  All others are delivered to the target.
 * Returns a number <= 1 अगर message was processed by device mapper.
 * Returns 2 अगर message should be delivered to the target.
 */
अटल पूर्णांक message_क्रम_md(काष्ठा mapped_device *md, अचिन्हित argc, अक्षर **argv,
			  अक्षर *result, अचिन्हित maxlen)
अणु
	पूर्णांक r;

	अगर (**argv != '@')
		वापस 2; /* no '@' prefix, deliver to target */

	अगर (!strहालcmp(argv[0], "@cancel_deferred_remove")) अणु
		अगर (argc != 1) अणु
			DMERR("Invalid arguments for @cancel_deferred_remove");
			वापस -EINVAL;
		पूर्ण
		वापस dm_cancel_deferred_हटाओ(md);
	पूर्ण

	r = dm_stats_message(md, argc, argv, result, maxlen);
	अगर (r < 2)
		वापस r;

	DMERR("Unsupported message sent to DM core: %s", argv[0]);
	वापस -EINVAL;
पूर्ण

/*
 * Pass a message to the target that's at the supplied device offset.
 */
अटल पूर्णांक target_message(काष्ठा file *filp, काष्ठा dm_ioctl *param, माप_प्रकार param_size)
अणु
	पूर्णांक r, argc;
	अक्षर **argv;
	काष्ठा mapped_device *md;
	काष्ठा dm_table *table;
	काष्ठा dm_target *ti;
	काष्ठा dm_target_msg *पंचांगsg = (व्योम *) param + param->data_start;
	माप_प्रकार maxlen;
	अक्षर *result = get_result_buffer(param, param_size, &maxlen);
	पूर्णांक srcu_idx;

	md = find_device(param);
	अगर (!md)
		वापस -ENXIO;

	अगर (पंचांगsg < (काष्ठा dm_target_msg *) param->data ||
	    invalid_str(पंचांगsg->message, (व्योम *) param + param_size)) अणु
		DMWARN("Invalid target message parameters.");
		r = -EINVAL;
		जाओ out;
	पूर्ण

	r = dm_split_args(&argc, &argv, पंचांगsg->message);
	अगर (r) अणु
		DMWARN("Failed to split target message parameters");
		जाओ out;
	पूर्ण

	अगर (!argc) अणु
		DMWARN("Empty message received.");
		r = -EINVAL;
		जाओ out_argv;
	पूर्ण

	r = message_क्रम_md(md, argc, argv, result, maxlen);
	अगर (r <= 1)
		जाओ out_argv;

	table = dm_get_live_table(md, &srcu_idx);
	अगर (!table)
		जाओ out_table;

	अगर (dm_deleting_md(md)) अणु
		r = -ENXIO;
		जाओ out_table;
	पूर्ण

	ti = dm_table_find_target(table, पंचांगsg->sector);
	अगर (!ti) अणु
		DMWARN("Target message sector outside device.");
		r = -EINVAL;
	पूर्ण अन्यथा अगर (ti->type->message)
		r = ti->type->message(ti, argc, argv, result, maxlen);
	अन्यथा अणु
		DMWARN("Target type does not support messages");
		r = -EINVAL;
	पूर्ण

 out_table:
	dm_put_live_table(md, srcu_idx);
 out_argv:
	kमुक्त(argv);
 out:
	अगर (r >= 0)
		__dev_status(md, param);

	अगर (r == 1) अणु
		param->flags |= DM_DATA_OUT_FLAG;
		अगर (dm_message_test_buffer_overflow(result, maxlen))
			param->flags |= DM_BUFFER_FULL_FLAG;
		अन्यथा
			param->data_size = param->data_start + म_माप(result) + 1;
		r = 0;
	पूर्ण

	dm_put(md);
	वापस r;
पूर्ण

/*
 * The ioctl parameter block consists of two parts, a dm_ioctl काष्ठा
 * followed by a data buffer.  This flag is set अगर the second part,
 * which has a variable size, is not used by the function processing
 * the ioctl.
 */
#घोषणा IOCTL_FLAGS_NO_PARAMS		1
#घोषणा IOCTL_FLAGS_ISSUE_GLOBAL_EVENT	2

/*-----------------------------------------------------------------
 * Implementation of खोलो/बंद/ioctl on the special अक्षर
 * device.
 *---------------------------------------------------------------*/
अटल ioctl_fn lookup_ioctl(अचिन्हित पूर्णांक cmd, पूर्णांक *ioctl_flags)
अणु
	अटल स्थिर काष्ठा अणु
		पूर्णांक cmd;
		पूर्णांक flags;
		ioctl_fn fn;
	पूर्ण _ioctls[] = अणु
		अणुDM_VERSION_CMD, 0, शून्यपूर्ण, /* version is dealt with अन्यथाwhere */
		अणुDM_REMOVE_ALL_CMD, IOCTL_FLAGS_NO_PARAMS | IOCTL_FLAGS_ISSUE_GLOBAL_EVENT, हटाओ_allपूर्ण,
		अणुDM_LIST_DEVICES_CMD, 0, list_devicesपूर्ण,

		अणुDM_DEV_CREATE_CMD, IOCTL_FLAGS_NO_PARAMS | IOCTL_FLAGS_ISSUE_GLOBAL_EVENT, dev_createपूर्ण,
		अणुDM_DEV_REMOVE_CMD, IOCTL_FLAGS_NO_PARAMS | IOCTL_FLAGS_ISSUE_GLOBAL_EVENT, dev_हटाओपूर्ण,
		अणुDM_DEV_RENAME_CMD, IOCTL_FLAGS_ISSUE_GLOBAL_EVENT, dev_नामपूर्ण,
		अणुDM_DEV_SUSPEND_CMD, IOCTL_FLAGS_NO_PARAMS, dev_suspendपूर्ण,
		अणुDM_DEV_STATUS_CMD, IOCTL_FLAGS_NO_PARAMS, dev_statusपूर्ण,
		अणुDM_DEV_WAIT_CMD, 0, dev_रुकोपूर्ण,

		अणुDM_TABLE_LOAD_CMD, 0, table_loadपूर्ण,
		अणुDM_TABLE_CLEAR_CMD, IOCTL_FLAGS_NO_PARAMS, table_clearपूर्ण,
		अणुDM_TABLE_DEPS_CMD, 0, table_depsपूर्ण,
		अणुDM_TABLE_STATUS_CMD, 0, table_statusपूर्ण,

		अणुDM_LIST_VERSIONS_CMD, 0, list_versionsपूर्ण,

		अणुDM_TARGET_MSG_CMD, 0, target_messageपूर्ण,
		अणुDM_DEV_SET_GEOMETRY_CMD, 0, dev_set_geometryपूर्ण,
		अणुDM_DEV_ARM_POLL, IOCTL_FLAGS_NO_PARAMS, dev_arm_pollपूर्ण,
		अणुDM_GET_TARGET_VERSION, 0, get_target_versionपूर्ण,
	पूर्ण;

	अगर (unlikely(cmd >= ARRAY_SIZE(_ioctls)))
		वापस शून्य;

	*ioctl_flags = _ioctls[cmd].flags;
	वापस _ioctls[cmd].fn;
पूर्ण

/*
 * As well as checking the version compatibility this always
 * copies the kernel पूर्णांकerface version out.
 */
अटल पूर्णांक check_version(अचिन्हित पूर्णांक cmd, काष्ठा dm_ioctl __user *user)
अणु
	uपूर्णांक32_t version[3];
	पूर्णांक r = 0;

	अगर (copy_from_user(version, user->version, माप(version)))
		वापस -EFAULT;

	अगर ((DM_VERSION_MAJOR != version[0]) ||
	    (DM_VERSION_MINOR < version[1])) अणु
		DMWARN("ioctl interface mismatch: "
		       "kernel(%u.%u.%u), user(%u.%u.%u), cmd(%d)",
		       DM_VERSION_MAJOR, DM_VERSION_MINOR,
		       DM_VERSION_PATCHLEVEL,
		       version[0], version[1], version[2], cmd);
		r = -EINVAL;
	पूर्ण

	/*
	 * Fill in the kernel version.
	 */
	version[0] = DM_VERSION_MAJOR;
	version[1] = DM_VERSION_MINOR;
	version[2] = DM_VERSION_PATCHLEVEL;
	अगर (copy_to_user(user->version, version, माप(version)))
		वापस -EFAULT;

	वापस r;
पूर्ण

#घोषणा DM_PARAMS_MALLOC	0x0001	/* Params allocated with kvदो_स्मृति() */
#घोषणा DM_WIPE_BUFFER		0x0010	/* Wipe input buffer beक्रमe वापसing from ioctl */

अटल व्योम मुक्त_params(काष्ठा dm_ioctl *param, माप_प्रकार param_size, पूर्णांक param_flags)
अणु
	अगर (param_flags & DM_WIPE_BUFFER)
		स_रखो(param, 0, param_size);

	अगर (param_flags & DM_PARAMS_MALLOC)
		kvमुक्त(param);
पूर्ण

अटल पूर्णांक copy_params(काष्ठा dm_ioctl __user *user, काष्ठा dm_ioctl *param_kernel,
		       पूर्णांक ioctl_flags, काष्ठा dm_ioctl **param, पूर्णांक *param_flags)
अणु
	काष्ठा dm_ioctl *dmi;
	पूर्णांक secure_data;
	स्थिर माप_प्रकार minimum_data_size = दुरत्व(काष्ठा dm_ioctl, data);
	अचिन्हित noio_flag;

	अगर (copy_from_user(param_kernel, user, minimum_data_size))
		वापस -EFAULT;

	अगर (param_kernel->data_size < minimum_data_size)
		वापस -EINVAL;

	secure_data = param_kernel->flags & DM_SECURE_DATA_FLAG;

	*param_flags = secure_data ? DM_WIPE_BUFFER : 0;

	अगर (ioctl_flags & IOCTL_FLAGS_NO_PARAMS) अणु
		dmi = param_kernel;
		dmi->data_size = minimum_data_size;
		जाओ data_copied;
	पूर्ण

	/*
	 * Use __GFP_HIGH to aव्योम low memory issues when a device is
	 * suspended and the ioctl is needed to resume it.
	 * Use kदो_स्मृति() rather than vदो_स्मृति() when we can.
	 */
	dmi = शून्य;
	noio_flag = meदो_स्मृति_noio_save();
	dmi = kvदो_स्मृति(param_kernel->data_size, GFP_KERNEL | __GFP_HIGH);
	meदो_स्मृति_noio_restore(noio_flag);

	अगर (!dmi) अणु
		अगर (secure_data && clear_user(user, param_kernel->data_size))
			वापस -EFAULT;
		वापस -ENOMEM;
	पूर्ण

	*param_flags |= DM_PARAMS_MALLOC;

	/* Copy from param_kernel (which was alपढ़ोy copied from user) */
	स_नकल(dmi, param_kernel, minimum_data_size);

	अगर (copy_from_user(&dmi->data, (अक्षर __user *)user + minimum_data_size,
			   param_kernel->data_size - minimum_data_size))
		जाओ bad;
data_copied:
	/* Wipe the user buffer so we करो not वापस it to userspace */
	अगर (secure_data && clear_user(user, param_kernel->data_size))
		जाओ bad;

	*param = dmi;
	वापस 0;

bad:
	मुक्त_params(dmi, param_kernel->data_size, *param_flags);

	वापस -EFAULT;
पूर्ण

अटल पूर्णांक validate_params(uपूर्णांक cmd, काष्ठा dm_ioctl *param)
अणु
	/* Always clear this flag */
	param->flags &= ~DM_BUFFER_FULL_FLAG;
	param->flags &= ~DM_UEVENT_GENERATED_FLAG;
	param->flags &= ~DM_SECURE_DATA_FLAG;
	param->flags &= ~DM_DATA_OUT_FLAG;

	/* Ignores parameters */
	अगर (cmd == DM_REMOVE_ALL_CMD ||
	    cmd == DM_LIST_DEVICES_CMD ||
	    cmd == DM_LIST_VERSIONS_CMD)
		वापस 0;

	अगर (cmd == DM_DEV_CREATE_CMD) अणु
		अगर (!*param->name) अणु
			DMWARN("name not supplied when creating device");
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अगर (*param->uuid && *param->name) अणु
		DMWARN("only supply one of name or uuid, cmd(%u)", cmd);
		वापस -EINVAL;
	पूर्ण

	/* Ensure strings are terminated */
	param->name[DM_NAME_LEN - 1] = '\0';
	param->uuid[DM_UUID_LEN - 1] = '\0';

	वापस 0;
पूर्ण

अटल पूर्णांक ctl_ioctl(काष्ठा file *file, uपूर्णांक command, काष्ठा dm_ioctl __user *user)
अणु
	पूर्णांक r = 0;
	पूर्णांक ioctl_flags;
	पूर्णांक param_flags;
	अचिन्हित पूर्णांक cmd;
	काष्ठा dm_ioctl *param;
	ioctl_fn fn = शून्य;
	माप_प्रकार input_param_size;
	काष्ठा dm_ioctl param_kernel;

	/* only root can play with this */
	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EACCES;

	अगर (_IOC_TYPE(command) != DM_IOCTL)
		वापस -ENOTTY;

	cmd = _IOC_NR(command);

	/*
	 * Check the पूर्णांकerface version passed in.  This also
	 * ग_लिखोs out the kernel's पूर्णांकerface version.
	 */
	r = check_version(cmd, user);
	अगर (r)
		वापस r;

	/*
	 * Nothing more to करो क्रम the version command.
	 */
	अगर (cmd == DM_VERSION_CMD)
		वापस 0;

	fn = lookup_ioctl(cmd, &ioctl_flags);
	अगर (!fn) अणु
		DMWARN("dm_ctl_ioctl: unknown command 0x%x", command);
		वापस -ENOTTY;
	पूर्ण

	/*
	 * Copy the parameters पूर्णांकo kernel space.
	 */
	r = copy_params(user, &param_kernel, ioctl_flags, &param, &param_flags);

	अगर (r)
		वापस r;

	input_param_size = param->data_size;
	r = validate_params(cmd, param);
	अगर (r)
		जाओ out;

	param->data_size = दुरत्व(काष्ठा dm_ioctl, data);
	r = fn(file, param, input_param_size);

	अगर (unlikely(param->flags & DM_BUFFER_FULL_FLAG) &&
	    unlikely(ioctl_flags & IOCTL_FLAGS_NO_PARAMS))
		DMERR("ioctl %d tried to output some data but has IOCTL_FLAGS_NO_PARAMS set", cmd);

	अगर (!r && ioctl_flags & IOCTL_FLAGS_ISSUE_GLOBAL_EVENT)
		dm_issue_global_event();

	/*
	 * Copy the results back to userland.
	 */
	अगर (!r && copy_to_user(user, param, param->data_size))
		r = -EFAULT;

out:
	मुक्त_params(param, input_param_size, param_flags);
	वापस r;
पूर्ण

अटल दीर्घ dm_ctl_ioctl(काष्ठा file *file, uपूर्णांक command, uदीर्घ u)
अणु
	वापस (दीर्घ)ctl_ioctl(file, command, (काष्ठा dm_ioctl __user *)u);
पूर्ण

#अगर_घोषित CONFIG_COMPAT
अटल दीर्घ dm_compat_ctl_ioctl(काष्ठा file *file, uपूर्णांक command, uदीर्घ u)
अणु
	वापस (दीर्घ)dm_ctl_ioctl(file, command, (uदीर्घ) compat_ptr(u));
पूर्ण
#अन्यथा
#घोषणा dm_compat_ctl_ioctl शून्य
#पूर्ण_अगर

अटल पूर्णांक dm_खोलो(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	पूर्णांक r;
	काष्ठा dm_file *priv;

	r = nonseekable_खोलो(inode, filp);
	अगर (unlikely(r))
		वापस r;

	priv = filp->निजी_data = kदो_स्मृति(माप(काष्ठा dm_file), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->global_event_nr = atomic_पढ़ो(&dm_global_event_nr);

	वापस 0;
पूर्ण

अटल पूर्णांक dm_release(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	kमुक्त(filp->निजी_data);
	वापस 0;
पूर्ण

अटल __poll_t dm_poll(काष्ठा file *filp, poll_table *रुको)
अणु
	काष्ठा dm_file *priv = filp->निजी_data;
	__poll_t mask = 0;

	poll_रुको(filp, &dm_global_eventq, रुको);

	अगर ((पूर्णांक)(atomic_पढ़ो(&dm_global_event_nr) - priv->global_event_nr) > 0)
		mask |= EPOLLIN;

	वापस mask;
पूर्ण

अटल स्थिर काष्ठा file_operations _ctl_fops = अणु
	.खोलो    = dm_खोलो,
	.release = dm_release,
	.poll    = dm_poll,
	.unlocked_ioctl	 = dm_ctl_ioctl,
	.compat_ioctl = dm_compat_ctl_ioctl,
	.owner	 = THIS_MODULE,
	.llseek  = noop_llseek,
पूर्ण;

अटल काष्ठा miscdevice _dm_misc = अणु
	.minor		= MAPPER_CTRL_MINOR,
	.name  		= DM_NAME,
	.nodename	= DM_सूची "/" DM_CONTROL_NODE,
	.fops  		= &_ctl_fops
पूर्ण;

MODULE_ALIAS_MISCDEV(MAPPER_CTRL_MINOR);
MODULE_ALIAS("devname:" DM_सूची "/" DM_CONTROL_NODE);

/*
 * Create misc अक्षरacter device and link to DM_सूची/control.
 */
पूर्णांक __init dm_पूर्णांकerface_init(व्योम)
अणु
	पूर्णांक r;

	r = misc_रेजिस्टर(&_dm_misc);
	अगर (r) अणु
		DMERR("misc_register failed for control device");
		वापस r;
	पूर्ण

	DMINFO("%d.%d.%d%s initialised: %s", DM_VERSION_MAJOR,
	       DM_VERSION_MINOR, DM_VERSION_PATCHLEVEL, DM_VERSION_EXTRA,
	       DM_DRIVER_EMAIL);
	वापस 0;
पूर्ण

व्योम dm_पूर्णांकerface_निकास(व्योम)
अणु
	misc_deरेजिस्टर(&_dm_misc);
	dm_hash_निकास();
पूर्ण

/**
 * dm_copy_name_and_uuid - Copy mapped device name & uuid पूर्णांकo supplied buffers
 * @md: Poपूर्णांकer to mapped_device
 * @name: Buffer (size DM_NAME_LEN) क्रम name
 * @uuid: Buffer (size DM_UUID_LEN) क्रम uuid or empty string अगर uuid not defined
 */
पूर्णांक dm_copy_name_and_uuid(काष्ठा mapped_device *md, अक्षर *name, अक्षर *uuid)
अणु
	पूर्णांक r = 0;
	काष्ठा hash_cell *hc;

	अगर (!md)
		वापस -ENXIO;

	mutex_lock(&dm_hash_cells_mutex);
	hc = dm_get_mdptr(md);
	अगर (!hc || hc->md != md) अणु
		r = -ENXIO;
		जाओ out;
	पूर्ण

	अगर (name)
		म_नकल(name, hc->name);
	अगर (uuid)
		म_नकल(uuid, hc->uuid ? : "");

out:
	mutex_unlock(&dm_hash_cells_mutex);

	वापस r;
पूर्ण
EXPORT_SYMBOL_GPL(dm_copy_name_and_uuid);

/**
 * dm_early_create - create a mapped device in early boot.
 *
 * @dmi: Contains मुख्य inक्रमmation of the device mapping to be created.
 * @spec_array: array of poपूर्णांकers to काष्ठा dm_target_spec. Describes the
 * mapping table of the device.
 * @target_params_array: array of strings with the parameters to a specअगरic
 * target.
 *
 * Instead of having the काष्ठा dm_target_spec and the parameters क्रम every
 * target embedded at the end of काष्ठा dm_ioctl (as perक्रमmed in a normal
 * ioctl), pass them as arguments, so the caller करोesn't need to serialize them.
 * The size of the spec_array and target_params_array is given by
 * @dmi->target_count.
 * This function is supposed to be called in early boot, so locking mechanisms
 * to protect against concurrent loads are not required.
 */
पूर्णांक __init dm_early_create(काष्ठा dm_ioctl *dmi,
			   काष्ठा dm_target_spec **spec_array,
			   अक्षर **target_params_array)
अणु
	पूर्णांक r, m = DM_ANY_MINOR;
	काष्ठा dm_table *t, *old_map;
	काष्ठा mapped_device *md;
	अचिन्हित पूर्णांक i;

	अगर (!dmi->target_count)
		वापस -EINVAL;

	r = check_name(dmi->name);
	अगर (r)
		वापस r;

	अगर (dmi->flags & DM_PERSISTENT_DEV_FLAG)
		m = MINOR(huge_decode_dev(dmi->dev));

	/* alloc dm device */
	r = dm_create(m, &md);
	अगर (r)
		वापस r;

	/* hash insert */
	r = dm_hash_insert(dmi->name, *dmi->uuid ? dmi->uuid : शून्य, md);
	अगर (r)
		जाओ err_destroy_dm;

	/* alloc table */
	r = dm_table_create(&t, get_mode(dmi), dmi->target_count, md);
	अगर (r)
		जाओ err_hash_हटाओ;

	/* add tarमाला_लो */
	क्रम (i = 0; i < dmi->target_count; i++) अणु
		r = dm_table_add_target(t, spec_array[i]->target_type,
					(sector_t) spec_array[i]->sector_start,
					(sector_t) spec_array[i]->length,
					target_params_array[i]);
		अगर (r) अणु
			DMWARN("error adding target to table");
			जाओ err_destroy_table;
		पूर्ण
	पूर्ण

	/* finish table */
	r = dm_table_complete(t);
	अगर (r)
		जाओ err_destroy_table;

	md->type = dm_table_get_type(t);
	/* setup md->queue to reflect md's type (may block) */
	r = dm_setup_md_queue(md, t);
	अगर (r) अणु
		DMWARN("unable to set up device queue for new table.");
		जाओ err_destroy_table;
	पूर्ण

	/* Set new map */
	dm_suspend(md, 0);
	old_map = dm_swap_table(md, t);
	अगर (IS_ERR(old_map)) अणु
		r = PTR_ERR(old_map);
		जाओ err_destroy_table;
	पूर्ण
	set_disk_ro(dm_disk(md), !!(dmi->flags & DM_READONLY_FLAG));

	/* resume device */
	r = dm_resume(md);
	अगर (r)
		जाओ err_destroy_table;

	DMINFO("%s (%s) is ready", md->disk->disk_name, dmi->name);
	dm_put(md);
	वापस 0;

err_destroy_table:
	dm_table_destroy(t);
err_hash_हटाओ:
	(व्योम) __hash_हटाओ(__get_name_cell(dmi->name));
	/* release reference from __get_name_cell */
	dm_put(md);
err_destroy_dm:
	dm_put(md);
	dm_destroy(md);
	वापस r;
पूर्ण
