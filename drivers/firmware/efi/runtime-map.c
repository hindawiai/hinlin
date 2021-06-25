<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * linux/drivers/efi/runसमय-map.c
 * Copyright (C) 2013 Red Hat, Inc., Dave Young <dyoung@redhat.com>
 */

#समावेश <linux/माला.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/efi.h>
#समावेश <linux/slab.h>

#समावेश <यंत्र/setup.h>

काष्ठा efi_runसमय_map_entry अणु
	efi_memory_desc_t md;
	काष्ठा kobject kobj;   /* kobject क्रम each entry */
पूर्ण;

अटल काष्ठा efi_runसमय_map_entry **map_entries;

काष्ठा map_attribute अणु
	काष्ठा attribute attr;
	sमाप_प्रकार (*show)(काष्ठा efi_runसमय_map_entry *entry, अक्षर *buf);
पूर्ण;

अटल अंतरभूत काष्ठा map_attribute *to_map_attr(काष्ठा attribute *attr)
अणु
	वापस container_of(attr, काष्ठा map_attribute, attr);
पूर्ण

अटल sमाप_प्रकार type_show(काष्ठा efi_runसमय_map_entry *entry, अक्षर *buf)
अणु
	वापस snम_लिखो(buf, PAGE_SIZE, "0x%x\n", entry->md.type);
पूर्ण

#घोषणा EFI_RUNTIME_FIELD(var) entry->md.var

#घोषणा EFI_RUNTIME_U64_ATTR_SHOW(name) \
अटल sमाप_प्रकार name##_show(काष्ठा efi_runसमय_map_entry *entry, अक्षर *buf) \
अणु \
	वापस snम_लिखो(buf, PAGE_SIZE, "0x%llx\n", EFI_RUNTIME_FIELD(name)); \
पूर्ण

EFI_RUNTIME_U64_ATTR_SHOW(phys_addr);
EFI_RUNTIME_U64_ATTR_SHOW(virt_addr);
EFI_RUNTIME_U64_ATTR_SHOW(num_pages);
EFI_RUNTIME_U64_ATTR_SHOW(attribute);

अटल अंतरभूत काष्ठा efi_runसमय_map_entry *to_map_entry(काष्ठा kobject *kobj)
अणु
	वापस container_of(kobj, काष्ठा efi_runसमय_map_entry, kobj);
पूर्ण

अटल sमाप_प्रकार map_attr_show(काष्ठा kobject *kobj, काष्ठा attribute *attr,
			      अक्षर *buf)
अणु
	काष्ठा efi_runसमय_map_entry *entry = to_map_entry(kobj);
	काष्ठा map_attribute *map_attr = to_map_attr(attr);

	वापस map_attr->show(entry, buf);
पूर्ण

अटल काष्ठा map_attribute map_type_attr = __ATTR_RO_MODE(type, 0400);
अटल काष्ठा map_attribute map_phys_addr_attr = __ATTR_RO_MODE(phys_addr, 0400);
अटल काष्ठा map_attribute map_virt_addr_attr = __ATTR_RO_MODE(virt_addr, 0400);
अटल काष्ठा map_attribute map_num_pages_attr = __ATTR_RO_MODE(num_pages, 0400);
अटल काष्ठा map_attribute map_attribute_attr = __ATTR_RO_MODE(attribute, 0400);

/*
 * These are शेष attributes that are added क्रम every memmap entry.
 */
अटल काष्ठा attribute *def_attrs[] = अणु
	&map_type_attr.attr,
	&map_phys_addr_attr.attr,
	&map_virt_addr_attr.attr,
	&map_num_pages_attr.attr,
	&map_attribute_attr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा sysfs_ops map_attr_ops = अणु
	.show = map_attr_show,
पूर्ण;

अटल व्योम map_release(काष्ठा kobject *kobj)
अणु
	काष्ठा efi_runसमय_map_entry *entry;

	entry = to_map_entry(kobj);
	kमुक्त(entry);
पूर्ण

अटल काष्ठा kobj_type __refdata map_ktype = अणु
	.sysfs_ops	= &map_attr_ops,
	.शेष_attrs	= def_attrs,
	.release	= map_release,
पूर्ण;

अटल काष्ठा kset *map_kset;

अटल काष्ठा efi_runसमय_map_entry *
add_sysfs_runसमय_map_entry(काष्ठा kobject *kobj, पूर्णांक nr,
			    efi_memory_desc_t *md)
अणु
	पूर्णांक ret;
	काष्ठा efi_runसमय_map_entry *entry;

	अगर (!map_kset) अणु
		map_kset = kset_create_and_add("runtime-map", शून्य, kobj);
		अगर (!map_kset)
			वापस ERR_PTR(-ENOMEM);
	पूर्ण

	entry = kzalloc(माप(*entry), GFP_KERNEL);
	अगर (!entry) अणु
		kset_unरेजिस्टर(map_kset);
		map_kset = शून्य;
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	स_नकल(&entry->md, md, माप(efi_memory_desc_t));

	kobject_init(&entry->kobj, &map_ktype);
	entry->kobj.kset = map_kset;
	ret = kobject_add(&entry->kobj, शून्य, "%d", nr);
	अगर (ret) अणु
		kobject_put(&entry->kobj);
		kset_unरेजिस्टर(map_kset);
		map_kset = शून्य;
		वापस ERR_PTR(ret);
	पूर्ण

	वापस entry;
पूर्ण

पूर्णांक efi_get_runसमय_map_size(व्योम)
अणु
	वापस efi.memmap.nr_map * efi.memmap.desc_size;
पूर्ण

पूर्णांक efi_get_runसमय_map_desc_size(व्योम)
अणु
	वापस efi.memmap.desc_size;
पूर्ण

पूर्णांक efi_runसमय_map_copy(व्योम *buf, माप_प्रकार bufsz)
अणु
	माप_प्रकार sz = efi_get_runसमय_map_size();

	अगर (sz > bufsz)
		sz = bufsz;

	स_नकल(buf, efi.memmap.map, sz);
	वापस 0;
पूर्ण

पूर्णांक __init efi_runसमय_map_init(काष्ठा kobject *efi_kobj)
अणु
	पूर्णांक i, j, ret = 0;
	काष्ठा efi_runसमय_map_entry *entry;
	efi_memory_desc_t *md;

	अगर (!efi_enabled(EFI_MEMMAP))
		वापस 0;

	map_entries = kसुस्मृति(efi.memmap.nr_map, माप(entry), GFP_KERNEL);
	अगर (!map_entries) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	i = 0;
	क्रम_each_efi_memory_desc(md) अणु
		entry = add_sysfs_runसमय_map_entry(efi_kobj, i, md);
		अगर (IS_ERR(entry)) अणु
			ret = PTR_ERR(entry);
			जाओ out_add_entry;
		पूर्ण
		*(map_entries + i++) = entry;
	पूर्ण

	वापस 0;
out_add_entry:
	क्रम (j = i - 1; j >= 0; j--) अणु
		entry = *(map_entries + j);
		kobject_put(&entry->kobj);
	पूर्ण
out:
	वापस ret;
पूर्ण
