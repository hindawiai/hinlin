<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * esrt.c
 *
 * This module exports EFI System Resource Table (ESRT) entries पूर्णांकo userspace
 * through the sysfs file प्रणाली. The ESRT provides a पढ़ो-only catalog of
 * प्रणाली components क्रम which the प्रणाली accepts firmware upgrades via UEFI's
 * "Capsule Update" feature. This module allows userland utilities to evaluate
 * what firmware updates can be applied to this प्रणाली, and potentially arrange
 * क्रम those updates to occur.
 *
 * Data is currently found below /sys/firmware/efi/esrt/...
 */
#घोषणा pr_fmt(fmt) "esrt: " fmt

#समावेश <linux/capability.h>
#समावेश <linux/device.h>
#समावेश <linux/efi.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/kobject.h>
#समावेश <linux/list.h>
#समावेश <linux/memblock.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/early_ioremap.h>

काष्ठा efi_प्रणाली_resource_entry_v1 अणु
	efi_guid_t	fw_class;
	u32		fw_type;
	u32		fw_version;
	u32		lowest_supported_fw_version;
	u32		capsule_flags;
	u32		last_attempt_version;
	u32		last_attempt_status;
पूर्ण;

/*
 * _count and _version are what they seem like.  _max is actually just
 * accounting info क्रम the firmware when creating the table; it should never
 * have been exposed to us.  To wit, the spec says:
 * The maximum number of resource array entries that can be within the
 * table without पुनः_स्मृतिating the table, must not be zero.
 * Since there's no guidance about what that means in terms of memory layout,
 * it means nothing to us.
 */
काष्ठा efi_प्रणाली_resource_table अणु
	u32	fw_resource_count;
	u32	fw_resource_count_max;
	u64	fw_resource_version;
	u8	entries[];
पूर्ण;

अटल phys_addr_t esrt_data;
अटल माप_प्रकार esrt_data_size;

अटल काष्ठा efi_प्रणाली_resource_table *esrt;

काष्ठा esre_entry अणु
	जोड़ अणु
		काष्ठा efi_प्रणाली_resource_entry_v1 *esre1;
	पूर्ण esre;

	काष्ठा kobject kobj;
	काष्ठा list_head list;
पूर्ण;

/* global list of esre_entry. */
अटल LIST_HEAD(entry_list);

/* entry attribute */
काष्ठा esre_attribute अणु
	काष्ठा attribute attr;
	sमाप_प्रकार (*show)(काष्ठा esre_entry *entry, अक्षर *buf);
	sमाप_प्रकार (*store)(काष्ठा esre_entry *entry,
			 स्थिर अक्षर *buf, माप_प्रकार count);
पूर्ण;

अटल काष्ठा esre_entry *to_entry(काष्ठा kobject *kobj)
अणु
	वापस container_of(kobj, काष्ठा esre_entry, kobj);
पूर्ण

अटल काष्ठा esre_attribute *to_attr(काष्ठा attribute *attr)
अणु
	वापस container_of(attr, काष्ठा esre_attribute, attr);
पूर्ण

अटल sमाप_प्रकार esre_attr_show(काष्ठा kobject *kobj,
			      काष्ठा attribute *_attr, अक्षर *buf)
अणु
	काष्ठा esre_entry *entry = to_entry(kobj);
	काष्ठा esre_attribute *attr = to_attr(_attr);

	/* Don't tell normal users what firmware versions we've got... */
	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EACCES;

	वापस attr->show(entry, buf);
पूर्ण

अटल स्थिर काष्ठा sysfs_ops esre_attr_ops = अणु
	.show = esre_attr_show,
पूर्ण;

/* Generic ESRT Entry ("ESRE") support. */
अटल sमाप_प्रकार fw_class_show(काष्ठा esre_entry *entry, अक्षर *buf)
अणु
	अक्षर *str = buf;

	efi_guid_to_str(&entry->esre.esre1->fw_class, str);
	str += म_माप(str);
	str += प्र_लिखो(str, "\n");

	वापस str - buf;
पूर्ण

अटल काष्ठा esre_attribute esre_fw_class = __ATTR_RO_MODE(fw_class, 0400);

#घोषणा esre_attr_decl(name, size, fmt) \
अटल sमाप_प्रकार name##_show(काष्ठा esre_entry *entry, अक्षर *buf) \
अणु \
	वापस प्र_लिखो(buf, fmt "\n", \
		       le##size##_to_cpu(entry->esre.esre1->name)); \
पूर्ण \
\
अटल काष्ठा esre_attribute esre_##name = __ATTR_RO_MODE(name, 0400)

esre_attr_decl(fw_type, 32, "%u");
esre_attr_decl(fw_version, 32, "%u");
esre_attr_decl(lowest_supported_fw_version, 32, "%u");
esre_attr_decl(capsule_flags, 32, "0x%x");
esre_attr_decl(last_attempt_version, 32, "%u");
esre_attr_decl(last_attempt_status, 32, "%u");

अटल काष्ठा attribute *esre1_attrs[] = अणु
	&esre_fw_class.attr,
	&esre_fw_type.attr,
	&esre_fw_version.attr,
	&esre_lowest_supported_fw_version.attr,
	&esre_capsule_flags.attr,
	&esre_last_attempt_version.attr,
	&esre_last_attempt_status.attr,
	शून्य
पूर्ण;
अटल व्योम esre_release(काष्ठा kobject *kobj)
अणु
	काष्ठा esre_entry *entry = to_entry(kobj);

	list_del(&entry->list);
	kमुक्त(entry);
पूर्ण

अटल काष्ठा kobj_type esre1_ktype = अणु
	.release = esre_release,
	.sysfs_ops = &esre_attr_ops,
	.शेष_attrs = esre1_attrs,
पूर्ण;


अटल काष्ठा kobject *esrt_kobj;
अटल काष्ठा kset *esrt_kset;

अटल पूर्णांक esre_create_sysfs_entry(व्योम *esre, पूर्णांक entry_num)
अणु
	काष्ठा esre_entry *entry;

	entry = kzalloc(माप(*entry), GFP_KERNEL);
	अगर (!entry)
		वापस -ENOMEM;

	entry->kobj.kset = esrt_kset;

	अगर (esrt->fw_resource_version == 1) अणु
		पूर्णांक rc = 0;

		entry->esre.esre1 = esre;
		rc = kobject_init_and_add(&entry->kobj, &esre1_ktype, शून्य,
					  "entry%d", entry_num);
		अगर (rc) अणु
			kobject_put(&entry->kobj);
			वापस rc;
		पूर्ण
	पूर्ण

	list_add_tail(&entry->list, &entry_list);
	वापस 0;
पूर्ण

/* support क्रम displaying ESRT fields at the top level */
#घोषणा esrt_attr_decl(name, size, fmt) \
अटल sमाप_प्रकार name##_show(काष्ठा kobject *kobj, \
				  काष्ठा kobj_attribute *attr, अक्षर *buf)\
अणु \
	वापस प्र_लिखो(buf, fmt "\n", le##size##_to_cpu(esrt->name)); \
पूर्ण \
\
अटल काष्ठा kobj_attribute esrt_##name = __ATTR_RO_MODE(name, 0400)

esrt_attr_decl(fw_resource_count, 32, "%u");
esrt_attr_decl(fw_resource_count_max, 32, "%u");
esrt_attr_decl(fw_resource_version, 64, "%llu");

अटल काष्ठा attribute *esrt_attrs[] = अणु
	&esrt_fw_resource_count.attr,
	&esrt_fw_resource_count_max.attr,
	&esrt_fw_resource_version.attr,
	शून्य,
पूर्ण;

अटल अंतरभूत पूर्णांक esrt_table_exists(व्योम)
अणु
	अगर (!efi_enabled(EFI_CONFIG_TABLES))
		वापस 0;
	अगर (efi.esrt == EFI_INVALID_TABLE_ADDR)
		वापस 0;
	वापस 1;
पूर्ण

अटल umode_t esrt_attr_is_visible(काष्ठा kobject *kobj,
				    काष्ठा attribute *attr, पूर्णांक n)
अणु
	अगर (!esrt_table_exists())
		वापस 0;
	वापस attr->mode;
पूर्ण

अटल स्थिर काष्ठा attribute_group esrt_attr_group = अणु
	.attrs = esrt_attrs,
	.is_visible = esrt_attr_is_visible,
पूर्ण;

/*
 * remap the table, validate it, mark it reserved and unmap it.
 */
व्योम __init efi_esrt_init(व्योम)
अणु
	व्योम *va;
	काष्ठा efi_प्रणाली_resource_table पंचांगpesrt;
	माप_प्रकार size, max, entry_size, entries_size;
	efi_memory_desc_t md;
	पूर्णांक rc;
	phys_addr_t end;

	अगर (!efi_enabled(EFI_MEMMAP))
		वापस;

	pr_debug("esrt-init: loading.\n");
	अगर (!esrt_table_exists())
		वापस;

	rc = efi_mem_desc_lookup(efi.esrt, &md);
	अगर (rc < 0 ||
	    (!(md.attribute & EFI_MEMORY_RUNTIME) &&
	     md.type != EFI_BOOT_SERVICES_DATA &&
	     md.type != EFI_RUNTIME_SERVICES_DATA)) अणु
		pr_warn("ESRT header is not in the memory map.\n");
		वापस;
	पूर्ण

	max = efi_mem_desc_end(&md);
	अगर (max < efi.esrt) अणु
		pr_err("EFI memory descriptor is invalid. (esrt: %p max: %p)\n",
		       (व्योम *)efi.esrt, (व्योम *)max);
		वापस;
	पूर्ण

	size = माप(*esrt);
	max -= efi.esrt;

	अगर (max < size) अणु
		pr_err("ESRT header doesn't fit on single memory map entry. (size: %zu max: %zu)\n",
		       size, max);
		वापस;
	पूर्ण

	va = early_memremap(efi.esrt, size);
	अगर (!va) अणु
		pr_err("early_memremap(%p, %zu) failed.\n", (व्योम *)efi.esrt,
		       size);
		वापस;
	पूर्ण

	स_नकल(&पंचांगpesrt, va, माप(पंचांगpesrt));
	early_memunmap(va, size);

	अगर (पंचांगpesrt.fw_resource_version != 1) अणु
		pr_err("Unsupported ESRT version %lld.\n",
		       पंचांगpesrt.fw_resource_version);
		वापस;
	पूर्ण

	entry_size = माप(काष्ठा efi_प्रणाली_resource_entry_v1);
	अगर (पंचांगpesrt.fw_resource_count > 0 && max - size < entry_size) अणु
		pr_err("ESRT memory map entry can only hold the header. (max: %zu size: %zu)\n",
		       max - size, entry_size);
		वापस;
	पूर्ण

	/*
	 * The क्रमmat करोesn't really give us any boundary to test here,
	 * so I'm making up 128 as the max number of inभागidually updatable
	 * components we support.
	 * 128 should be pretty excessive, but there's still some chance
	 * somebody will करो that someday and we'll need to उठाओ this.
	 */
	अगर (पंचांगpesrt.fw_resource_count > 128) अणु
		pr_err("ESRT says fw_resource_count has very large value %d.\n",
		       पंचांगpesrt.fw_resource_count);
		वापस;
	पूर्ण

	/*
	 * We know it can't be larger than N * माप() here, and N is limited
	 * by the previous test to a small number, so there's no overflow.
	 */
	entries_size = पंचांगpesrt.fw_resource_count * entry_size;
	अगर (max < size + entries_size) अणु
		pr_err("ESRT does not fit on single memory map entry (size: %zu max: %zu)\n",
		       size, max);
		वापस;
	पूर्ण

	size += entries_size;

	esrt_data = (phys_addr_t)efi.esrt;
	esrt_data_size = size;

	end = esrt_data + size;
	pr_info("Reserving ESRT space from %pa to %pa.\n", &esrt_data, &end);
	अगर (md.type == EFI_BOOT_SERVICES_DATA)
		efi_mem_reserve(esrt_data, esrt_data_size);

	pr_debug("esrt-init: loaded.\n");
पूर्ण

अटल पूर्णांक __init रेजिस्टर_entries(व्योम)
अणु
	काष्ठा efi_प्रणाली_resource_entry_v1 *v1_entries = (व्योम *)esrt->entries;
	पूर्णांक i, rc;

	अगर (!esrt_table_exists())
		वापस 0;

	क्रम (i = 0; i < le32_to_cpu(esrt->fw_resource_count); i++) अणु
		व्योम *esre = शून्य;
		अगर (esrt->fw_resource_version == 1) अणु
			esre = &v1_entries[i];
		पूर्ण अन्यथा अणु
			pr_err("Unsupported ESRT version %lld.\n",
			       esrt->fw_resource_version);
			वापस -EINVAL;
		पूर्ण

		rc = esre_create_sysfs_entry(esre, i);
		अगर (rc < 0) अणु
			pr_err("ESRT entry creation failed with error %d.\n",
			       rc);
			वापस rc;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम cleanup_entry_list(व्योम)
अणु
	काष्ठा esre_entry *entry, *next;

	list_क्रम_each_entry_safe(entry, next, &entry_list, list) अणु
		kobject_put(&entry->kobj);
	पूर्ण
पूर्ण

अटल पूर्णांक __init esrt_sysfs_init(व्योम)
अणु
	पूर्णांक error;

	pr_debug("esrt-sysfs: loading.\n");
	अगर (!esrt_data || !esrt_data_size)
		वापस -ENOSYS;

	esrt = memremap(esrt_data, esrt_data_size, MEMREMAP_WB);
	अगर (!esrt) अणु
		pr_err("memremap(%pa, %zu) failed.\n", &esrt_data,
		       esrt_data_size);
		वापस -ENOMEM;
	पूर्ण

	esrt_kobj = kobject_create_and_add("esrt", efi_kobj);
	अगर (!esrt_kobj) अणु
		pr_err("Firmware table registration failed.\n");
		error = -ENOMEM;
		जाओ err;
	पूर्ण

	error = sysfs_create_group(esrt_kobj, &esrt_attr_group);
	अगर (error) अणु
		pr_err("Sysfs attribute export failed with error %d.\n",
		       error);
		जाओ err_हटाओ_esrt;
	पूर्ण

	esrt_kset = kset_create_and_add("entries", शून्य, esrt_kobj);
	अगर (!esrt_kset) अणु
		pr_err("kset creation failed.\n");
		error = -ENOMEM;
		जाओ err_हटाओ_group;
	पूर्ण

	error = रेजिस्टर_entries();
	अगर (error)
		जाओ err_cleanup_list;

	pr_debug("esrt-sysfs: loaded.\n");

	वापस 0;
err_cleanup_list:
	cleanup_entry_list();
	kset_unरेजिस्टर(esrt_kset);
err_हटाओ_group:
	sysfs_हटाओ_group(esrt_kobj, &esrt_attr_group);
err_हटाओ_esrt:
	kobject_put(esrt_kobj);
err:
	memunmap(esrt);
	esrt = शून्य;
	वापस error;
पूर्ण
device_initcall(esrt_sysfs_init);

/*
MODULE_AUTHOR("Peter Jones <pjones@redhat.com>");
MODULE_DESCRIPTION("EFI System Resource Table support");
MODULE_LICENSE("GPL");
*/
