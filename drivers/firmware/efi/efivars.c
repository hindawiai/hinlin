<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Originally from efivars.c,
 *
 * Copyright (C) 2001,2003,2004 Dell <Matt_Domsch@dell.com>
 * Copyright (C) 2004 Intel Corporation <matthew.e.tolentino@पूर्णांकel.com>
 *
 * This code takes all variables accessible from EFI runसमय and
 *  exports them via sysfs
 */

#समावेश <linux/efi.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/ucs2_माला.स>
#समावेश <linux/compat.h>

#घोषणा EFIVARS_VERSION "0.08"
#घोषणा EFIVARS_DATE "2004-May-17"

MODULE_AUTHOR("Matt Domsch <Matt_Domsch@Dell.com>");
MODULE_DESCRIPTION("sysfs interface to EFI Variables");
MODULE_LICENSE("GPL");
MODULE_VERSION(EFIVARS_VERSION);

अटल LIST_HEAD(efivar_sysfs_list);

अटल काष्ठा kset *efivars_kset;

अटल काष्ठा bin_attribute *efivars_new_var;
अटल काष्ठा bin_attribute *efivars_del_var;

काष्ठा compat_efi_variable अणु
	efi_अक्षर16_t  VariableName[EFI_VAR_NAME_LEN/माप(efi_अक्षर16_t)];
	efi_guid_t    VenकरोrGuid;
	__u32         DataSize;
	__u8          Data[1024];
	__u32         Status;
	__u32         Attributes;
पूर्ण __packed;

काष्ठा efivar_attribute अणु
	काष्ठा attribute attr;
	sमाप_प्रकार (*show) (काष्ठा efivar_entry *entry, अक्षर *buf);
	sमाप_प्रकार (*store)(काष्ठा efivar_entry *entry, स्थिर अक्षर *buf, माप_प्रकार count);
पूर्ण;

#घोषणा EFIVAR_ATTR(_name, _mode, _show, _store) \
काष्ठा efivar_attribute efivar_attr_##_name = अणु \
	.attr = अणु.name = __stringअगरy(_name), .mode = _modeपूर्ण, \
	.show = _show, \
	.store = _store, \
पूर्ण;

#घोषणा to_efivar_attr(_attr) container_of(_attr, काष्ठा efivar_attribute, attr)
#घोषणा to_efivar_entry(obj)  container_of(obj, काष्ठा efivar_entry, kobj)

/*
 * Prototype क्रम sysfs creation function
 */
अटल पूर्णांक
efivar_create_sysfs_entry(काष्ठा efivar_entry *new_var);

अटल sमाप_प्रकार
efivar_guid_पढ़ो(काष्ठा efivar_entry *entry, अक्षर *buf)
अणु
	काष्ठा efi_variable *var = &entry->var;
	अक्षर *str = buf;

	अगर (!entry || !buf)
		वापस 0;

	efi_guid_to_str(&var->VenकरोrGuid, str);
	str += म_माप(str);
	str += प्र_लिखो(str, "\n");

	वापस str - buf;
पूर्ण

अटल sमाप_प्रकार
efivar_attr_पढ़ो(काष्ठा efivar_entry *entry, अक्षर *buf)
अणु
	काष्ठा efi_variable *var = &entry->var;
	अचिन्हित दीर्घ size = माप(var->Data);
	अक्षर *str = buf;
	पूर्णांक ret;

	अगर (!entry || !buf)
		वापस -EINVAL;

	ret = efivar_entry_get(entry, &var->Attributes, &size, var->Data);
	var->DataSize = size;
	अगर (ret)
		वापस -EIO;

	अगर (var->Attributes & EFI_VARIABLE_NON_VOLATILE)
		str += प्र_लिखो(str, "EFI_VARIABLE_NON_VOLATILE\n");
	अगर (var->Attributes & EFI_VARIABLE_BOOTSERVICE_ACCESS)
		str += प्र_लिखो(str, "EFI_VARIABLE_BOOTSERVICE_ACCESS\n");
	अगर (var->Attributes & EFI_VARIABLE_RUNTIME_ACCESS)
		str += प्र_लिखो(str, "EFI_VARIABLE_RUNTIME_ACCESS\n");
	अगर (var->Attributes & EFI_VARIABLE_HARDWARE_ERROR_RECORD)
		str += प्र_लिखो(str, "EFI_VARIABLE_HARDWARE_ERROR_RECORD\n");
	अगर (var->Attributes & EFI_VARIABLE_AUTHENTICATED_WRITE_ACCESS)
		str += प्र_लिखो(str,
			"EFI_VARIABLE_AUTHENTICATED_WRITE_ACCESS\n");
	अगर (var->Attributes &
			EFI_VARIABLE_TIME_BASED_AUTHENTICATED_WRITE_ACCESS)
		str += प्र_लिखो(str,
			"EFI_VARIABLE_TIME_BASED_AUTHENTICATED_WRITE_ACCESS\n");
	अगर (var->Attributes & EFI_VARIABLE_APPEND_WRITE)
		str += प्र_लिखो(str, "EFI_VARIABLE_APPEND_WRITE\n");
	वापस str - buf;
पूर्ण

अटल sमाप_प्रकार
efivar_size_पढ़ो(काष्ठा efivar_entry *entry, अक्षर *buf)
अणु
	काष्ठा efi_variable *var = &entry->var;
	अचिन्हित दीर्घ size = माप(var->Data);
	अक्षर *str = buf;
	पूर्णांक ret;

	अगर (!entry || !buf)
		वापस -EINVAL;

	ret = efivar_entry_get(entry, &var->Attributes, &size, var->Data);
	var->DataSize = size;
	अगर (ret)
		वापस -EIO;

	str += प्र_लिखो(str, "0x%lx\n", var->DataSize);
	वापस str - buf;
पूर्ण

अटल sमाप_प्रकार
efivar_data_पढ़ो(काष्ठा efivar_entry *entry, अक्षर *buf)
अणु
	काष्ठा efi_variable *var = &entry->var;
	अचिन्हित दीर्घ size = माप(var->Data);
	पूर्णांक ret;

	अगर (!entry || !buf)
		वापस -EINVAL;

	ret = efivar_entry_get(entry, &var->Attributes, &size, var->Data);
	var->DataSize = size;
	अगर (ret)
		वापस -EIO;

	स_नकल(buf, var->Data, var->DataSize);
	वापस var->DataSize;
पूर्ण

अटल अंतरभूत पूर्णांक
sanity_check(काष्ठा efi_variable *var, efi_अक्षर16_t *name, efi_guid_t venकरोr,
	     अचिन्हित दीर्घ size, u32 attributes, u8 *data)
अणु
	/*
	 * If only updating the variable data, then the name
	 * and guid should reमुख्य the same
	 */
	अगर (स_भेद(name, var->VariableName, माप(var->VariableName)) ||
		efi_guidcmp(venकरोr, var->VenकरोrGuid)) अणु
		prपूर्णांकk(KERN_ERR "efivars: Cannot edit the wrong variable!\n");
		वापस -EINVAL;
	पूर्ण

	अगर ((size <= 0) || (attributes == 0))अणु
		prपूर्णांकk(KERN_ERR "efivars: DataSize & Attributes must be valid!\n");
		वापस -EINVAL;
	पूर्ण

	अगर ((attributes & ~EFI_VARIABLE_MASK) != 0 ||
	    efivar_validate(venकरोr, name, data, size) == false) अणु
		prपूर्णांकk(KERN_ERR "efivars: Malformed variable content\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम
copy_out_compat(काष्ठा efi_variable *dst, काष्ठा compat_efi_variable *src)
अणु
	स_नकल(dst->VariableName, src->VariableName, EFI_VAR_NAME_LEN);
	स_नकल(dst->Data, src->Data, माप(src->Data));

	dst->VenकरोrGuid = src->VenकरोrGuid;
	dst->DataSize = src->DataSize;
	dst->Attributes = src->Attributes;
पूर्ण

/*
 * We allow each variable to be edited via rewriting the
 * entire efi variable काष्ठाure.
 */
अटल sमाप_प्रकार
efivar_store_raw(काष्ठा efivar_entry *entry, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा efi_variable *new_var, *var = &entry->var;
	efi_अक्षर16_t *name;
	अचिन्हित दीर्घ size;
	efi_guid_t venकरोr;
	u32 attributes;
	u8 *data;
	पूर्णांक err;

	अगर (!entry || !buf)
		वापस -EINVAL;

	अगर (in_compat_syscall()) अणु
		काष्ठा compat_efi_variable *compat;

		अगर (count != माप(*compat))
			वापस -EINVAL;

		compat = (काष्ठा compat_efi_variable *)buf;
		attributes = compat->Attributes;
		venकरोr = compat->VenकरोrGuid;
		name = compat->VariableName;
		size = compat->DataSize;
		data = compat->Data;

		err = sanity_check(var, name, venकरोr, size, attributes, data);
		अगर (err)
			वापस err;

		copy_out_compat(&entry->var, compat);
	पूर्ण अन्यथा अणु
		अगर (count != माप(काष्ठा efi_variable))
			वापस -EINVAL;

		new_var = (काष्ठा efi_variable *)buf;

		attributes = new_var->Attributes;
		venकरोr = new_var->VenकरोrGuid;
		name = new_var->VariableName;
		size = new_var->DataSize;
		data = new_var->Data;

		err = sanity_check(var, name, venकरोr, size, attributes, data);
		अगर (err)
			वापस err;

		स_नकल(&entry->var, new_var, count);
	पूर्ण

	err = efivar_entry_set(entry, attributes, size, data, शून्य);
	अगर (err) अणु
		prपूर्णांकk(KERN_WARNING "efivars: set_variable() failed: status=%d\n", err);
		वापस -EIO;
	पूर्ण

	वापस count;
पूर्ण

अटल sमाप_प्रकार
efivar_show_raw(काष्ठा efivar_entry *entry, अक्षर *buf)
अणु
	काष्ठा efi_variable *var = &entry->var;
	काष्ठा compat_efi_variable *compat;
	अचिन्हित दीर्घ datasize = माप(var->Data);
	माप_प्रकार size;
	पूर्णांक ret;

	अगर (!entry || !buf)
		वापस 0;

	ret = efivar_entry_get(entry, &var->Attributes, &datasize, var->Data);
	var->DataSize = datasize;
	अगर (ret)
		वापस -EIO;

	अगर (in_compat_syscall()) अणु
		compat = (काष्ठा compat_efi_variable *)buf;

		size = माप(*compat);
		स_नकल(compat->VariableName, var->VariableName,
			EFI_VAR_NAME_LEN);
		स_नकल(compat->Data, var->Data, माप(compat->Data));

		compat->VenकरोrGuid = var->VenकरोrGuid;
		compat->DataSize = var->DataSize;
		compat->Attributes = var->Attributes;
	पूर्ण अन्यथा अणु
		size = माप(*var);
		स_नकल(buf, var, size);
	पूर्ण

	वापस size;
पूर्ण

/*
 * Generic पढ़ो/ग_लिखो functions that call the specअगरic functions of
 * the attributes...
 */
अटल sमाप_प्रकार efivar_attr_show(काष्ठा kobject *kobj, काष्ठा attribute *attr,
				अक्षर *buf)
अणु
	काष्ठा efivar_entry *var = to_efivar_entry(kobj);
	काष्ठा efivar_attribute *efivar_attr = to_efivar_attr(attr);
	sमाप_प्रकार ret = -EIO;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EACCES;

	अगर (efivar_attr->show) अणु
		ret = efivar_attr->show(var, buf);
	पूर्ण
	वापस ret;
पूर्ण

अटल sमाप_प्रकार efivar_attr_store(काष्ठा kobject *kobj, काष्ठा attribute *attr,
				स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा efivar_entry *var = to_efivar_entry(kobj);
	काष्ठा efivar_attribute *efivar_attr = to_efivar_attr(attr);
	sमाप_प्रकार ret = -EIO;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EACCES;

	अगर (efivar_attr->store)
		ret = efivar_attr->store(var, buf, count);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा sysfs_ops efivar_attr_ops = अणु
	.show = efivar_attr_show,
	.store = efivar_attr_store,
पूर्ण;

अटल व्योम efivar_release(काष्ठा kobject *kobj)
अणु
	काष्ठा efivar_entry *var = to_efivar_entry(kobj);
	kमुक्त(var);
पूर्ण

अटल EFIVAR_ATTR(guid, 0400, efivar_guid_पढ़ो, शून्य);
अटल EFIVAR_ATTR(attributes, 0400, efivar_attr_पढ़ो, शून्य);
अटल EFIVAR_ATTR(size, 0400, efivar_size_पढ़ो, शून्य);
अटल EFIVAR_ATTR(data, 0400, efivar_data_पढ़ो, शून्य);
अटल EFIVAR_ATTR(raw_var, 0600, efivar_show_raw, efivar_store_raw);

अटल काष्ठा attribute *def_attrs[] = अणु
	&efivar_attr_guid.attr,
	&efivar_attr_size.attr,
	&efivar_attr_attributes.attr,
	&efivar_attr_data.attr,
	&efivar_attr_raw_var.attr,
	शून्य,
पूर्ण;

अटल काष्ठा kobj_type efivar_ktype = अणु
	.release = efivar_release,
	.sysfs_ops = &efivar_attr_ops,
	.शेष_attrs = def_attrs,
पूर्ण;

अटल sमाप_प्रकार efivar_create(काष्ठा file *filp, काष्ठा kobject *kobj,
			     काष्ठा bin_attribute *bin_attr,
			     अक्षर *buf, loff_t pos, माप_प्रकार count)
अणु
	काष्ठा compat_efi_variable *compat = (काष्ठा compat_efi_variable *)buf;
	काष्ठा efi_variable *new_var = (काष्ठा efi_variable *)buf;
	काष्ठा efivar_entry *new_entry;
	bool need_compat = in_compat_syscall();
	efi_अक्षर16_t *name;
	अचिन्हित दीर्घ size;
	u32 attributes;
	u8 *data;
	पूर्णांक err;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EACCES;

	अगर (need_compat) अणु
		अगर (count != माप(*compat))
			वापस -EINVAL;

		attributes = compat->Attributes;
		name = compat->VariableName;
		size = compat->DataSize;
		data = compat->Data;
	पूर्ण अन्यथा अणु
		अगर (count != माप(*new_var))
			वापस -EINVAL;

		attributes = new_var->Attributes;
		name = new_var->VariableName;
		size = new_var->DataSize;
		data = new_var->Data;
	पूर्ण

	अगर ((attributes & ~EFI_VARIABLE_MASK) != 0 ||
	    efivar_validate(new_var->VenकरोrGuid, name, data,
			    size) == false) अणु
		prपूर्णांकk(KERN_ERR "efivars: Malformed variable content\n");
		वापस -EINVAL;
	पूर्ण

	new_entry = kzalloc(माप(*new_entry), GFP_KERNEL);
	अगर (!new_entry)
		वापस -ENOMEM;

	अगर (need_compat)
		copy_out_compat(&new_entry->var, compat);
	अन्यथा
		स_नकल(&new_entry->var, new_var, माप(*new_var));

	err = efivar_entry_set(new_entry, attributes, size,
			       data, &efivar_sysfs_list);
	अगर (err) अणु
		अगर (err == -EEXIST)
			err = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (efivar_create_sysfs_entry(new_entry)) अणु
		prपूर्णांकk(KERN_WARNING "efivars: failed to create sysfs entry.\n");
		kमुक्त(new_entry);
	पूर्ण
	वापस count;

out:
	kमुक्त(new_entry);
	वापस err;
पूर्ण

अटल sमाप_प्रकार efivar_delete(काष्ठा file *filp, काष्ठा kobject *kobj,
			     काष्ठा bin_attribute *bin_attr,
			     अक्षर *buf, loff_t pos, माप_प्रकार count)
अणु
	काष्ठा efi_variable *del_var = (काष्ठा efi_variable *)buf;
	काष्ठा compat_efi_variable *compat;
	काष्ठा efivar_entry *entry;
	efi_अक्षर16_t *name;
	efi_guid_t venकरोr;
	पूर्णांक err = 0;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EACCES;

	अगर (in_compat_syscall()) अणु
		अगर (count != माप(*compat))
			वापस -EINVAL;

		compat = (काष्ठा compat_efi_variable *)buf;
		name = compat->VariableName;
		venकरोr = compat->VenकरोrGuid;
	पूर्ण अन्यथा अणु
		अगर (count != माप(*del_var))
			वापस -EINVAL;

		name = del_var->VariableName;
		venकरोr = del_var->VenकरोrGuid;
	पूर्ण

	अगर (efivar_entry_iter_begin())
		वापस -EINTR;
	entry = efivar_entry_find(name, venकरोr, &efivar_sysfs_list, true);
	अगर (!entry)
		err = -EINVAL;
	अन्यथा अगर (__efivar_entry_delete(entry))
		err = -EIO;

	अगर (err) अणु
		efivar_entry_iter_end();
		वापस err;
	पूर्ण

	अगर (!entry->scanning) अणु
		efivar_entry_iter_end();
		efivar_unरेजिस्टर(entry);
	पूर्ण अन्यथा
		efivar_entry_iter_end();

	/* It's dead Jim.... */
	वापस count;
पूर्ण

/**
 * efivar_create_sysfs_entry - create a new entry in sysfs
 * @new_var: efivar entry to create
 *
 * Returns 0 on success, negative error code on failure
 */
अटल पूर्णांक
efivar_create_sysfs_entry(काष्ठा efivar_entry *new_var)
अणु
	पूर्णांक लघु_name_size;
	अक्षर *लघु_name;
	अचिन्हित दीर्घ utf8_name_size;
	efi_अक्षर16_t *variable_name = new_var->var.VariableName;
	पूर्णांक ret;

	/*
	 * Length of the variable bytes in UTF8, plus the '-' separator,
	 * plus the GUID, plus trailing NUL
	 */
	utf8_name_size = ucs2_utf8size(variable_name);
	लघु_name_size = utf8_name_size + 1 + EFI_VARIABLE_GUID_LEN + 1;

	लघु_name = kदो_स्मृति(लघु_name_size, GFP_KERNEL);
	अगर (!लघु_name)
		वापस -ENOMEM;

	ucs2_as_utf8(लघु_name, variable_name, लघु_name_size);

	/* This is ugly, but necessary to separate one venकरोr's
	   निजी variables from another's.         */
	लघु_name[utf8_name_size] = '-';
	efi_guid_to_str(&new_var->var.VenकरोrGuid,
			 लघु_name + utf8_name_size + 1);

	new_var->kobj.kset = efivars_kset;

	ret = kobject_init_and_add(&new_var->kobj, &efivar_ktype,
				   शून्य, "%s", लघु_name);
	kमुक्त(लघु_name);
	अगर (ret) अणु
		kobject_put(&new_var->kobj);
		वापस ret;
	पूर्ण

	kobject_uevent(&new_var->kobj, KOBJ_ADD);
	अगर (efivar_entry_add(new_var, &efivar_sysfs_list)) अणु
		efivar_unरेजिस्टर(new_var);
		वापस -EINTR;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
create_efivars_bin_attributes(व्योम)
अणु
	काष्ठा bin_attribute *attr;
	पूर्णांक error;

	/* new_var */
	attr = kzalloc(माप(*attr), GFP_KERNEL);
	अगर (!attr)
		वापस -ENOMEM;

	attr->attr.name = "new_var";
	attr->attr.mode = 0200;
	attr->ग_लिखो = efivar_create;
	efivars_new_var = attr;

	/* del_var */
	attr = kzalloc(माप(*attr), GFP_KERNEL);
	अगर (!attr) अणु
		error = -ENOMEM;
		जाओ out_मुक्त;
	पूर्ण
	attr->attr.name = "del_var";
	attr->attr.mode = 0200;
	attr->ग_लिखो = efivar_delete;
	efivars_del_var = attr;

	sysfs_bin_attr_init(efivars_new_var);
	sysfs_bin_attr_init(efivars_del_var);

	/* Register */
	error = sysfs_create_bin_file(&efivars_kset->kobj, efivars_new_var);
	अगर (error) अणु
		prपूर्णांकk(KERN_ERR "efivars: unable to create new_var sysfs file"
			" due to error %d\n", error);
		जाओ out_मुक्त;
	पूर्ण

	error = sysfs_create_bin_file(&efivars_kset->kobj, efivars_del_var);
	अगर (error) अणु
		prपूर्णांकk(KERN_ERR "efivars: unable to create del_var sysfs file"
			" due to error %d\n", error);
		sysfs_हटाओ_bin_file(&efivars_kset->kobj, efivars_new_var);
		जाओ out_मुक्त;
	पूर्ण

	वापस 0;
out_मुक्त:
	kमुक्त(efivars_del_var);
	efivars_del_var = शून्य;
	kमुक्त(efivars_new_var);
	efivars_new_var = शून्य;
	वापस error;
पूर्ण

अटल पूर्णांक efivars_sysfs_callback(efi_अक्षर16_t *name, efi_guid_t venकरोr,
				  अचिन्हित दीर्घ name_size, व्योम *data)
अणु
	काष्ठा efivar_entry *entry;

	entry = kzalloc(माप(*entry), GFP_KERNEL);
	अगर (!entry)
		वापस -ENOMEM;

	स_नकल(entry->var.VariableName, name, name_size);
	स_नकल(&(entry->var.VenकरोrGuid), &venकरोr, माप(efi_guid_t));

	efivar_create_sysfs_entry(entry);

	वापस 0;
पूर्ण

अटल पूर्णांक efivar_sysfs_destroy(काष्ठा efivar_entry *entry, व्योम *data)
अणु
	पूर्णांक err = efivar_entry_हटाओ(entry);

	अगर (err)
		वापस err;
	efivar_unरेजिस्टर(entry);
	वापस 0;
पूर्ण

अटल व्योम efivars_sysfs_निकास(व्योम)
अणु
	/* Remove all entries and destroy */
	पूर्णांक err;

	err = __efivar_entry_iter(efivar_sysfs_destroy, &efivar_sysfs_list,
				  शून्य, शून्य);
	अगर (err) अणु
		pr_err("efivars: Failed to destroy sysfs entries\n");
		वापस;
	पूर्ण

	अगर (efivars_new_var)
		sysfs_हटाओ_bin_file(&efivars_kset->kobj, efivars_new_var);
	अगर (efivars_del_var)
		sysfs_हटाओ_bin_file(&efivars_kset->kobj, efivars_del_var);
	kमुक्त(efivars_new_var);
	kमुक्त(efivars_del_var);
	kset_unरेजिस्टर(efivars_kset);
पूर्ण

अटल पूर्णांक efivars_sysfs_init(व्योम)
अणु
	काष्ठा kobject *parent_kobj = efivars_kobject();
	पूर्णांक error = 0;

	/* No efivars has been रेजिस्टरed yet */
	अगर (!parent_kobj || !efivar_supports_ग_लिखोs())
		वापस 0;

	prपूर्णांकk(KERN_INFO "EFI Variables Facility v%s %s\n", EFIVARS_VERSION,
	       EFIVARS_DATE);

	efivars_kset = kset_create_and_add("vars", शून्य, parent_kobj);
	अगर (!efivars_kset) अणु
		prपूर्णांकk(KERN_ERR "efivars: Subsystem registration failed.\n");
		वापस -ENOMEM;
	पूर्ण

	efivar_init(efivars_sysfs_callback, शून्य, true, &efivar_sysfs_list);

	error = create_efivars_bin_attributes();
	अगर (error) अणु
		efivars_sysfs_निकास();
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

module_init(efivars_sysfs_init);
module_निकास(efivars_sysfs_निकास);
