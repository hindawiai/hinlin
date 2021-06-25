<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+

#समावेश <linux/efi.h>
#समावेश <linux/module.h>
#समावेश <linux/pstore.h>
#समावेश <linux/slab.h>
#समावेश <linux/ucs2_माला.स>

#घोषणा DUMP_NAME_LEN 66

#घोषणा EFIVARS_DATA_SIZE_MAX 1024

अटल bool efivars_pstore_disable =
	IS_ENABLED(CONFIG_EFI_VARS_PSTORE_DEFAULT_DISABLE);

module_param_named(pstore_disable, efivars_pstore_disable, bool, 0644);

#घोषणा PSTORE_EFI_ATTRIBUTES \
	(EFI_VARIABLE_NON_VOLATILE | \
	 EFI_VARIABLE_BOOTSERVICE_ACCESS | \
	 EFI_VARIABLE_RUNTIME_ACCESS)

अटल LIST_HEAD(efi_pstore_list);
अटल DECLARE_WORK(efivar_work, शून्य);

अटल पूर्णांक efi_pstore_खोलो(काष्ठा pstore_info *psi)
अणु
	psi->data = शून्य;
	वापस 0;
पूर्ण

अटल पूर्णांक efi_pstore_बंद(काष्ठा pstore_info *psi)
अणु
	psi->data = शून्य;
	वापस 0;
पूर्ण

अटल अंतरभूत u64 generic_id(u64 बारtamp, अचिन्हित पूर्णांक part, पूर्णांक count)
अणु
	वापस (बारtamp * 100 + part) * 1000 + count;
पूर्ण

अटल पूर्णांक efi_pstore_पढ़ो_func(काष्ठा efivar_entry *entry,
				काष्ठा pstore_record *record)
अणु
	efi_guid_t venकरोr = LINUX_EFI_CRASH_GUID;
	अक्षर name[DUMP_NAME_LEN], data_type;
	पूर्णांक i;
	पूर्णांक cnt;
	अचिन्हित पूर्णांक part;
	अचिन्हित दीर्घ size;
	u64 समय;

	अगर (efi_guidcmp(entry->var.VenकरोrGuid, venकरोr))
		वापस 0;

	क्रम (i = 0; i < DUMP_NAME_LEN; i++)
		name[i] = entry->var.VariableName[i];

	अगर (माला_पूछो(name, "dump-type%u-%u-%d-%llu-%c",
		   &record->type, &part, &cnt, &समय, &data_type) == 5) अणु
		record->id = generic_id(समय, part, cnt);
		record->part = part;
		record->count = cnt;
		record->समय.tv_sec = समय;
		record->समय.tv_nsec = 0;
		अगर (data_type == 'C')
			record->compressed = true;
		अन्यथा
			record->compressed = false;
		record->ecc_notice_size = 0;
	पूर्ण अन्यथा अगर (माला_पूछो(name, "dump-type%u-%u-%d-%llu",
		   &record->type, &part, &cnt, &समय) == 4) अणु
		record->id = generic_id(समय, part, cnt);
		record->part = part;
		record->count = cnt;
		record->समय.tv_sec = समय;
		record->समय.tv_nsec = 0;
		record->compressed = false;
		record->ecc_notice_size = 0;
	पूर्ण अन्यथा अगर (माला_पूछो(name, "dump-type%u-%u-%llu",
			  &record->type, &part, &समय) == 3) अणु
		/*
		 * Check अगर an old क्रमmat,
		 * which करोesn't support holding
		 * multiple logs, reमुख्यs.
		 */
		record->id = generic_id(समय, part, 0);
		record->part = part;
		record->count = 0;
		record->समय.tv_sec = समय;
		record->समय.tv_nsec = 0;
		record->compressed = false;
		record->ecc_notice_size = 0;
	पूर्ण अन्यथा
		वापस 0;

	entry->var.DataSize = 1024;
	__efivar_entry_get(entry, &entry->var.Attributes,
			   &entry->var.DataSize, entry->var.Data);
	size = entry->var.DataSize;
	स_नकल(record->buf, entry->var.Data,
	       (माप_प्रकार)min_t(अचिन्हित दीर्घ, EFIVARS_DATA_SIZE_MAX, size));

	वापस size;
पूर्ण

/**
 * efi_pstore_scan_sysfs_enter
 * @pos: scanning entry
 * @next: next entry
 * @head: list head
 */
अटल व्योम efi_pstore_scan_sysfs_enter(काष्ठा efivar_entry *pos,
					काष्ठा efivar_entry *next,
					काष्ठा list_head *head)
अणु
	pos->scanning = true;
	अगर (&next->list != head)
		next->scanning = true;
पूर्ण

/**
 * __efi_pstore_scan_sysfs_निकास
 * @entry: deleting entry
 * @turn_off_scanning: Check अगर a scanning flag should be turned off
 */
अटल अंतरभूत पूर्णांक __efi_pstore_scan_sysfs_निकास(काष्ठा efivar_entry *entry,
						bool turn_off_scanning)
अणु
	अगर (entry->deleting) अणु
		list_del(&entry->list);
		efivar_entry_iter_end();
		kमुक्त(entry);
		अगर (efivar_entry_iter_begin())
			वापस -EINTR;
	पूर्ण अन्यथा अगर (turn_off_scanning)
		entry->scanning = false;

	वापस 0;
पूर्ण

/**
 * efi_pstore_scan_sysfs_निकास
 * @pos: scanning entry
 * @next: next entry
 * @head: list head
 * @stop: a flag checking अगर scanning will stop
 */
अटल पूर्णांक efi_pstore_scan_sysfs_निकास(काष्ठा efivar_entry *pos,
				       काष्ठा efivar_entry *next,
				       काष्ठा list_head *head, bool stop)
अणु
	पूर्णांक ret = __efi_pstore_scan_sysfs_निकास(pos, true);

	अगर (ret)
		वापस ret;

	अगर (stop)
		ret = __efi_pstore_scan_sysfs_निकास(next, &next->list != head);
	वापस ret;
पूर्ण

/**
 * efi_pstore_sysfs_entry_iter
 *
 * @record: pstore record to pass to callback
 *
 * You MUST call efivar_entry_iter_begin() beक्रमe this function, and
 * efivar_entry_iter_end() afterwards.
 *
 */
अटल पूर्णांक efi_pstore_sysfs_entry_iter(काष्ठा pstore_record *record)
अणु
	काष्ठा efivar_entry **pos = (काष्ठा efivar_entry **)&record->psi->data;
	काष्ठा efivar_entry *entry, *n;
	काष्ठा list_head *head = &efi_pstore_list;
	पूर्णांक size = 0;
	पूर्णांक ret;

	अगर (!*pos) अणु
		list_क्रम_each_entry_safe(entry, n, head, list) अणु
			efi_pstore_scan_sysfs_enter(entry, n, head);

			size = efi_pstore_पढ़ो_func(entry, record);
			ret = efi_pstore_scan_sysfs_निकास(entry, n, head,
							 size < 0);
			अगर (ret)
				वापस ret;
			अगर (size)
				अवरोध;
		पूर्ण
		*pos = n;
		वापस size;
	पूर्ण

	list_क्रम_each_entry_safe_from((*pos), n, head, list) अणु
		efi_pstore_scan_sysfs_enter((*pos), n, head);

		size = efi_pstore_पढ़ो_func((*pos), record);
		ret = efi_pstore_scan_sysfs_निकास((*pos), n, head, size < 0);
		अगर (ret)
			वापस ret;
		अगर (size)
			अवरोध;
	पूर्ण
	*pos = n;
	वापस size;
पूर्ण

/**
 * efi_pstore_पढ़ो
 *
 * This function वापसs a size of NVRAM entry logged via efi_pstore_ग_लिखो().
 * The meaning and behavior of efi_pstore/pstore are as below.
 *
 * size > 0: Got data of an entry logged via efi_pstore_ग_लिखो() successfully,
 *           and pstore fileप्रणाली will जारी पढ़ोing subsequent entries.
 * size == 0: Entry was not logged via efi_pstore_ग_लिखो(),
 *            and efi_pstore driver will जारी पढ़ोing subsequent entries.
 * size < 0: Failed to get data of entry logging via efi_pstore_ग_लिखो(),
 *           and pstore will stop पढ़ोing entry.
 */
अटल sमाप_प्रकार efi_pstore_पढ़ो(काष्ठा pstore_record *record)
अणु
	sमाप_प्रकार size;

	record->buf = kzalloc(EFIVARS_DATA_SIZE_MAX, GFP_KERNEL);
	अगर (!record->buf)
		वापस -ENOMEM;

	अगर (efivar_entry_iter_begin()) अणु
		size = -EINTR;
		जाओ out;
	पूर्ण
	size = efi_pstore_sysfs_entry_iter(record);
	efivar_entry_iter_end();

out:
	अगर (size <= 0) अणु
		kमुक्त(record->buf);
		record->buf = शून्य;
	पूर्ण
	वापस size;
पूर्ण

अटल पूर्णांक efi_pstore_ग_लिखो(काष्ठा pstore_record *record)
अणु
	अक्षर name[DUMP_NAME_LEN];
	efi_अक्षर16_t efi_name[DUMP_NAME_LEN];
	efi_guid_t venकरोr = LINUX_EFI_CRASH_GUID;
	पूर्णांक i, ret = 0;

	record->id = generic_id(record->समय.tv_sec, record->part,
				record->count);

	/* Since we copy the entire length of name, make sure it is wiped. */
	स_रखो(name, 0, माप(name));

	snम_लिखो(name, माप(name), "dump-type%u-%u-%d-%lld-%c",
		 record->type, record->part, record->count,
		 (दीर्घ दीर्घ)record->समय.tv_sec,
		 record->compressed ? 'C' : 'D');

	क्रम (i = 0; i < DUMP_NAME_LEN; i++)
		efi_name[i] = name[i];

	ret = efivar_entry_set_safe(efi_name, venकरोr, PSTORE_EFI_ATTRIBUTES,
			      preemptible(), record->size, record->psi->buf);

	अगर (record->reason == KMSG_DUMP_OOPS && try_module_get(THIS_MODULE))
		अगर (!schedule_work(&efivar_work))
			module_put(THIS_MODULE);

	वापस ret;
पूर्ण;

/*
 * Clean up an entry with the same name
 */
अटल पूर्णांक efi_pstore_erase_func(काष्ठा efivar_entry *entry, व्योम *data)
अणु
	efi_अक्षर16_t *efi_name = data;
	efi_guid_t venकरोr = LINUX_EFI_CRASH_GUID;
	अचिन्हित दीर्घ ucs2_len = ucs2_म_माप(efi_name);

	अगर (efi_guidcmp(entry->var.VenकरोrGuid, venकरोr))
		वापस 0;

	अगर (ucs2_म_भेदन(entry->var.VariableName, efi_name, (माप_प्रकार)ucs2_len))
		वापस 0;

	अगर (entry->scanning) अणु
		/*
		 * Skip deletion because this entry will be deleted
		 * after scanning is completed.
		 */
		entry->deleting = true;
	पूर्ण अन्यथा
		list_del(&entry->list);

	/* found */
	__efivar_entry_delete(entry);

	वापस 1;
पूर्ण

अटल पूर्णांक efi_pstore_erase_name(स्थिर अक्षर *name)
अणु
	काष्ठा efivar_entry *entry = शून्य;
	efi_अक्षर16_t efi_name[DUMP_NAME_LEN];
	पूर्णांक found, i;

	क्रम (i = 0; i < DUMP_NAME_LEN; i++) अणु
		efi_name[i] = name[i];
		अगर (name[i] == '\0')
			अवरोध;
	पूर्ण

	अगर (efivar_entry_iter_begin())
		वापस -EINTR;

	found = __efivar_entry_iter(efi_pstore_erase_func, &efi_pstore_list,
				    efi_name, &entry);
	efivar_entry_iter_end();

	अगर (found && !entry->scanning)
		kमुक्त(entry);

	वापस found ? 0 : -ENOENT;
पूर्ण

अटल पूर्णांक efi_pstore_erase(काष्ठा pstore_record *record)
अणु
	अक्षर name[DUMP_NAME_LEN];
	पूर्णांक ret;

	snम_लिखो(name, माप(name), "dump-type%u-%u-%d-%lld",
		 record->type, record->part, record->count,
		 (दीर्घ दीर्घ)record->समय.tv_sec);
	ret = efi_pstore_erase_name(name);
	अगर (ret != -ENOENT)
		वापस ret;

	snम_लिखो(name, माप(name), "dump-type%u-%u-%lld",
		record->type, record->part, (दीर्घ दीर्घ)record->समय.tv_sec);
	ret = efi_pstore_erase_name(name);

	वापस ret;
पूर्ण

अटल काष्ठा pstore_info efi_pstore_info = अणु
	.owner		= THIS_MODULE,
	.name		= "efi",
	.flags		= PSTORE_FLAGS_DMESG,
	.खोलो		= efi_pstore_खोलो,
	.बंद		= efi_pstore_बंद,
	.पढ़ो		= efi_pstore_पढ़ो,
	.ग_लिखो		= efi_pstore_ग_लिखो,
	.erase		= efi_pstore_erase,
पूर्ण;

अटल पूर्णांक efi_pstore_callback(efi_अक्षर16_t *name, efi_guid_t venकरोr,
			       अचिन्हित दीर्घ name_size, व्योम *data)
अणु
	काष्ठा efivar_entry *entry;
	पूर्णांक ret;

	entry = kzalloc(माप(*entry), GFP_KERNEL);
	अगर (!entry)
		वापस -ENOMEM;

	स_नकल(entry->var.VariableName, name, name_size);
	entry->var.VenकरोrGuid = venकरोr;

	ret = efivar_entry_add(entry, &efi_pstore_list);
	अगर (ret)
		kमुक्त(entry);

	वापस ret;
पूर्ण

अटल पूर्णांक efi_pstore_update_entry(efi_अक्षर16_t *name, efi_guid_t venकरोr,
				   अचिन्हित दीर्घ name_size, व्योम *data)
अणु
	काष्ठा efivar_entry *entry = data;

	अगर (efivar_entry_find(name, venकरोr, &efi_pstore_list, false))
		वापस 0;

	स_नकल(entry->var.VariableName, name, name_size);
	स_नकल(&(entry->var.VenकरोrGuid), &venकरोr, माप(efi_guid_t));

	वापस 1;
पूर्ण

अटल व्योम efi_pstore_update_entries(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा efivar_entry *entry;
	पूर्णांक err;

	/* Add new sysfs entries */
	जबतक (1) अणु
		entry = kzalloc(माप(*entry), GFP_KERNEL);
		अगर (!entry)
			वापस;

		err = efivar_init(efi_pstore_update_entry, entry,
				  false, &efi_pstore_list);
		अगर (!err)
			अवरोध;

		efivar_entry_add(entry, &efi_pstore_list);
	पूर्ण

	kमुक्त(entry);
	module_put(THIS_MODULE);
पूर्ण

अटल __init पूर्णांक efivars_pstore_init(व्योम)
अणु
	पूर्णांक ret;

	अगर (!efivars_kobject() || !efivar_supports_ग_लिखोs())
		वापस 0;

	अगर (efivars_pstore_disable)
		वापस 0;

	ret = efivar_init(efi_pstore_callback, शून्य, true, &efi_pstore_list);
	अगर (ret)
		वापस ret;

	efi_pstore_info.buf = kदो_स्मृति(4096, GFP_KERNEL);
	अगर (!efi_pstore_info.buf)
		वापस -ENOMEM;

	efi_pstore_info.bufsize = 1024;

	अगर (pstore_रेजिस्टर(&efi_pstore_info)) अणु
		kमुक्त(efi_pstore_info.buf);
		efi_pstore_info.buf = शून्य;
		efi_pstore_info.bufsize = 0;
	पूर्ण

	INIT_WORK(&efivar_work, efi_pstore_update_entries);

	वापस 0;
पूर्ण

अटल __निकास व्योम efivars_pstore_निकास(व्योम)
अणु
	अगर (!efi_pstore_info.bufsize)
		वापस;

	pstore_unरेजिस्टर(&efi_pstore_info);
	kमुक्त(efi_pstore_info.buf);
	efi_pstore_info.buf = शून्य;
	efi_pstore_info.bufsize = 0;
पूर्ण

module_init(efivars_pstore_init);
module_निकास(efivars_pstore_निकास);

MODULE_DESCRIPTION("EFI variable backend for pstore");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:efivars");
