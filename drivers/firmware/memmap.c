<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/drivers/firmware/memmap.c
 *  Copyright (C) 2008 SUSE LINUX Products GmbH
 *  by Bernhard Walle <bernhard.walle@gmx.de>
 */

#समावेश <linux/माला.स>
#समावेश <linux/firmware-map.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/memblock.h>
#समावेश <linux/slab.h>
#समावेश <linux/mm.h>

/*
 * Data types ------------------------------------------------------------------
 */

/*
 * Firmware map entry. Because firmware memory maps are flat and not
 * hierarchical, it's ok to organise them in a linked list. No parent
 * inक्रमmation is necessary as क्रम the resource tree.
 */
काष्ठा firmware_map_entry अणु
	/*
	 * start and end must be u64 rather than resource_माप_प्रकार, because e820
	 * resources can lie at addresses above 4G.
	 */
	u64			start;	/* start of the memory range */
	u64			end;	/* end of the memory range (incl.) */
	स्थिर अक्षर		*type;	/* type of the memory range */
	काष्ठा list_head	list;	/* entry क्रम the linked list */
	काष्ठा kobject		kobj;   /* kobject क्रम each entry */
पूर्ण;

/*
 * Forward declarations --------------------------------------------------------
 */
अटल sमाप_प्रकार memmap_attr_show(काष्ठा kobject *kobj,
				काष्ठा attribute *attr, अक्षर *buf);
अटल sमाप_प्रकार start_show(काष्ठा firmware_map_entry *entry, अक्षर *buf);
अटल sमाप_प्रकार end_show(काष्ठा firmware_map_entry *entry, अक्षर *buf);
अटल sमाप_प्रकार type_show(काष्ठा firmware_map_entry *entry, अक्षर *buf);

अटल काष्ठा firmware_map_entry * __meminit
firmware_map_find_entry(u64 start, u64 end, स्थिर अक्षर *type);

/*
 * Static data -----------------------------------------------------------------
 */

काष्ठा memmap_attribute अणु
	काष्ठा attribute attr;
	sमाप_प्रकार (*show)(काष्ठा firmware_map_entry *entry, अक्षर *buf);
पूर्ण;

अटल काष्ठा memmap_attribute memmap_start_attr = __ATTR_RO(start);
अटल काष्ठा memmap_attribute memmap_end_attr   = __ATTR_RO(end);
अटल काष्ठा memmap_attribute memmap_type_attr  = __ATTR_RO(type);

/*
 * These are शेष attributes that are added क्रम every memmap entry.
 */
अटल काष्ठा attribute *def_attrs[] = अणु
	&memmap_start_attr.attr,
	&memmap_end_attr.attr,
	&memmap_type_attr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा sysfs_ops memmap_attr_ops = अणु
	.show = memmap_attr_show,
पूर्ण;

/* Firmware memory map entries. */
अटल LIST_HEAD(map_entries);
अटल DEFINE_SPINLOCK(map_entries_lock);

/*
 * For memory hotplug, there is no way to मुक्त memory map entries allocated
 * by boot mem after the प्रणाली is up. So when we hot-हटाओ memory whose
 * map entry is allocated by booपंचांगem, we need to remember the storage and
 * reuse it when the memory is hot-added again.
 */
अटल LIST_HEAD(map_entries_booपंचांगem);
अटल DEFINE_SPINLOCK(map_entries_booपंचांगem_lock);


अटल अंतरभूत काष्ठा firmware_map_entry *
to_memmap_entry(काष्ठा kobject *kobj)
अणु
	वापस container_of(kobj, काष्ठा firmware_map_entry, kobj);
पूर्ण

अटल व्योम __meminit release_firmware_map_entry(काष्ठा kobject *kobj)
अणु
	काष्ठा firmware_map_entry *entry = to_memmap_entry(kobj);

	अगर (PageReserved(virt_to_page(entry))) अणु
		/*
		 * Remember the storage allocated by booपंचांगem, and reuse it when
		 * the memory is hot-added again. The entry will be added to
		 * map_entries_booपंचांगem here, and deleted from &map_entries in
		 * firmware_map_हटाओ_entry().
		 */
		spin_lock(&map_entries_booपंचांगem_lock);
		list_add(&entry->list, &map_entries_booपंचांगem);
		spin_unlock(&map_entries_booपंचांगem_lock);

		वापस;
	पूर्ण

	kमुक्त(entry);
पूर्ण

अटल काष्ठा kobj_type __refdata memmap_ktype = अणु
	.release	= release_firmware_map_entry,
	.sysfs_ops	= &memmap_attr_ops,
	.शेष_attrs	= def_attrs,
पूर्ण;

/*
 * Registration functions ------------------------------------------------------
 */

/**
 * firmware_map_add_entry() - Does the real work to add a firmware memmap entry.
 * @start: Start of the memory range.
 * @end:   End of the memory range (exclusive).
 * @type:  Type of the memory range.
 * @entry: Pre-allocated (either kदो_स्मृति() or booपंचांगem allocator), uninitialised
 *         entry.
 *
 * Common implementation of firmware_map_add() and firmware_map_add_early()
 * which expects a pre-allocated काष्ठा firmware_map_entry.
 *
 * Return: 0 always
 */
अटल पूर्णांक firmware_map_add_entry(u64 start, u64 end,
				  स्थिर अक्षर *type,
				  काष्ठा firmware_map_entry *entry)
अणु
	BUG_ON(start > end);

	entry->start = start;
	entry->end = end - 1;
	entry->type = type;
	INIT_LIST_HEAD(&entry->list);
	kobject_init(&entry->kobj, &memmap_ktype);

	spin_lock(&map_entries_lock);
	list_add_tail(&entry->list, &map_entries);
	spin_unlock(&map_entries_lock);

	वापस 0;
पूर्ण

/**
 * firmware_map_हटाओ_entry() - Does the real work to हटाओ a firmware
 * memmap entry.
 * @entry: हटाओd entry.
 *
 * The caller must hold map_entries_lock, and release it properly.
 */
अटल अंतरभूत व्योम firmware_map_हटाओ_entry(काष्ठा firmware_map_entry *entry)
अणु
	list_del(&entry->list);
पूर्ण

/*
 * Add memmap entry on sysfs
 */
अटल पूर्णांक add_sysfs_fw_map_entry(काष्ठा firmware_map_entry *entry)
अणु
	अटल पूर्णांक map_entries_nr;
	अटल काष्ठा kset *mmap_kset;

	अगर (entry->kobj.state_in_sysfs)
		वापस -EEXIST;

	अगर (!mmap_kset) अणु
		mmap_kset = kset_create_and_add("memmap", शून्य, firmware_kobj);
		अगर (!mmap_kset)
			वापस -ENOMEM;
	पूर्ण

	entry->kobj.kset = mmap_kset;
	अगर (kobject_add(&entry->kobj, शून्य, "%d", map_entries_nr++))
		kobject_put(&entry->kobj);

	वापस 0;
पूर्ण

/*
 * Remove memmap entry on sysfs
 */
अटल अंतरभूत व्योम हटाओ_sysfs_fw_map_entry(काष्ठा firmware_map_entry *entry)
अणु
	kobject_put(&entry->kobj);
पूर्ण

/**
 * firmware_map_find_entry_in_list() - Search memmap entry in a given list.
 * @start: Start of the memory range.
 * @end:   End of the memory range (exclusive).
 * @type:  Type of the memory range.
 * @list:  In which to find the entry.
 *
 * This function is to find the memmap entey of a given memory range in a
 * given list. The caller must hold map_entries_lock, and must not release
 * the lock until the processing of the वापसed entry has completed.
 *
 * Return: Poपूर्णांकer to the entry to be found on success, or शून्य on failure.
 */
अटल काष्ठा firmware_map_entry * __meminit
firmware_map_find_entry_in_list(u64 start, u64 end, स्थिर अक्षर *type,
				काष्ठा list_head *list)
अणु
	काष्ठा firmware_map_entry *entry;

	list_क्रम_each_entry(entry, list, list)
		अगर ((entry->start == start) && (entry->end == end) &&
		    (!म_भेद(entry->type, type))) अणु
			वापस entry;
		पूर्ण

	वापस शून्य;
पूर्ण

/**
 * firmware_map_find_entry() - Search memmap entry in map_entries.
 * @start: Start of the memory range.
 * @end:   End of the memory range (exclusive).
 * @type:  Type of the memory range.
 *
 * This function is to find the memmap entey of a given memory range.
 * The caller must hold map_entries_lock, and must not release the lock
 * until the processing of the वापसed entry has completed.
 *
 * Return: Poपूर्णांकer to the entry to be found on success, or शून्य on failure.
 */
अटल काष्ठा firmware_map_entry * __meminit
firmware_map_find_entry(u64 start, u64 end, स्थिर अक्षर *type)
अणु
	वापस firmware_map_find_entry_in_list(start, end, type, &map_entries);
पूर्ण

/**
 * firmware_map_find_entry_booपंचांगem() - Search memmap entry in map_entries_booपंचांगem.
 * @start: Start of the memory range.
 * @end:   End of the memory range (exclusive).
 * @type:  Type of the memory range.
 *
 * This function is similar to firmware_map_find_entry except that it find the
 * given entry in map_entries_booपंचांगem.
 *
 * Return: Poपूर्णांकer to the entry to be found on success, or शून्य on failure.
 */
अटल काष्ठा firmware_map_entry * __meminit
firmware_map_find_entry_booपंचांगem(u64 start, u64 end, स्थिर अक्षर *type)
अणु
	वापस firmware_map_find_entry_in_list(start, end, type,
					       &map_entries_booपंचांगem);
पूर्ण

/**
 * firmware_map_add_hotplug() - Adds a firmware mapping entry when we करो
 * memory hotplug.
 * @start: Start of the memory range.
 * @end:   End of the memory range (exclusive)
 * @type:  Type of the memory range.
 *
 * Adds a firmware mapping entry. This function is क्रम memory hotplug, it is
 * similar to function firmware_map_add_early(). The only dअगरference is that
 * it will create the syfs entry dynamically.
 *
 * Return: 0 on success, or -ENOMEM अगर no memory could be allocated.
 */
पूर्णांक __meminit firmware_map_add_hotplug(u64 start, u64 end, स्थिर अक्षर *type)
अणु
	काष्ठा firmware_map_entry *entry;

	entry = firmware_map_find_entry(start, end - 1, type);
	अगर (entry)
		वापस 0;

	entry = firmware_map_find_entry_booपंचांगem(start, end - 1, type);
	अगर (!entry) अणु
		entry = kzalloc(माप(काष्ठा firmware_map_entry), GFP_ATOMIC);
		अगर (!entry)
			वापस -ENOMEM;
	पूर्ण अन्यथा अणु
		/* Reuse storage allocated by booपंचांगem. */
		spin_lock(&map_entries_booपंचांगem_lock);
		list_del(&entry->list);
		spin_unlock(&map_entries_booपंचांगem_lock);

		स_रखो(entry, 0, माप(*entry));
	पूर्ण

	firmware_map_add_entry(start, end, type, entry);
	/* create the memmap entry */
	add_sysfs_fw_map_entry(entry);

	वापस 0;
पूर्ण

/**
 * firmware_map_add_early() - Adds a firmware mapping entry.
 * @start: Start of the memory range.
 * @end:   End of the memory range.
 * @type:  Type of the memory range.
 *
 * Adds a firmware mapping entry. This function uses the booपंचांगem allocator
 * क्रम memory allocation.
 *
 * That function must be called beक्रमe late_initcall.
 *
 * Return: 0 on success, or -ENOMEM अगर no memory could be allocated.
 */
पूर्णांक __init firmware_map_add_early(u64 start, u64 end, स्थिर अक्षर *type)
अणु
	काष्ठा firmware_map_entry *entry;

	entry = memblock_alloc(माप(काष्ठा firmware_map_entry),
			       SMP_CACHE_BYTES);
	अगर (WARN_ON(!entry))
		वापस -ENOMEM;

	वापस firmware_map_add_entry(start, end, type, entry);
पूर्ण

/**
 * firmware_map_हटाओ() - हटाओ a firmware mapping entry
 * @start: Start of the memory range.
 * @end:   End of the memory range.
 * @type:  Type of the memory range.
 *
 * हटाओs a firmware mapping entry.
 *
 * Return: 0 on success, or -EINVAL अगर no entry.
 */
पूर्णांक __meminit firmware_map_हटाओ(u64 start, u64 end, स्थिर अक्षर *type)
अणु
	काष्ठा firmware_map_entry *entry;

	spin_lock(&map_entries_lock);
	entry = firmware_map_find_entry(start, end - 1, type);
	अगर (!entry) अणु
		spin_unlock(&map_entries_lock);
		वापस -EINVAL;
	पूर्ण

	firmware_map_हटाओ_entry(entry);
	spin_unlock(&map_entries_lock);

	/* हटाओ the memmap entry */
	हटाओ_sysfs_fw_map_entry(entry);

	वापस 0;
पूर्ण

/*
 * Sysfs functions -------------------------------------------------------------
 */

अटल sमाप_प्रकार start_show(काष्ठा firmware_map_entry *entry, अक्षर *buf)
अणु
	वापस snम_लिखो(buf, PAGE_SIZE, "0x%llx\n",
		(अचिन्हित दीर्घ दीर्घ)entry->start);
पूर्ण

अटल sमाप_प्रकार end_show(काष्ठा firmware_map_entry *entry, अक्षर *buf)
अणु
	वापस snम_लिखो(buf, PAGE_SIZE, "0x%llx\n",
		(अचिन्हित दीर्घ दीर्घ)entry->end);
पूर्ण

अटल sमाप_प्रकार type_show(काष्ठा firmware_map_entry *entry, अक्षर *buf)
अणु
	वापस snम_लिखो(buf, PAGE_SIZE, "%s\n", entry->type);
पूर्ण

अटल अंतरभूत काष्ठा memmap_attribute *to_memmap_attr(काष्ठा attribute *attr)
अणु
	वापस container_of(attr, काष्ठा memmap_attribute, attr);
पूर्ण

अटल sमाप_प्रकार memmap_attr_show(काष्ठा kobject *kobj,
				काष्ठा attribute *attr, अक्षर *buf)
अणु
	काष्ठा firmware_map_entry *entry = to_memmap_entry(kobj);
	काष्ठा memmap_attribute *memmap_attr = to_memmap_attr(attr);

	वापस memmap_attr->show(entry, buf);
पूर्ण

/*
 * Initialises stuff and adds the entries in the map_entries list to
 * sysfs. Important is that firmware_map_add() and firmware_map_add_early()
 * must be called beक्रमe late_initcall. That's just because that function
 * is called as late_initcall() function, which means that अगर you call
 * firmware_map_add() or firmware_map_add_early() afterwards, the entries
 * are not added to sysfs.
 */
अटल पूर्णांक __init firmware_memmap_init(व्योम)
अणु
	काष्ठा firmware_map_entry *entry;

	list_क्रम_each_entry(entry, &map_entries, list)
		add_sysfs_fw_map_entry(entry);

	वापस 0;
पूर्ण
late_initcall(firmware_memmap_init);

