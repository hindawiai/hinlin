<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Originally from efivars.c
 *
 * Copyright (C) 2001,2003,2004 Dell <Matt_Domsch@dell.com>
 * Copyright (C) 2004 Intel Corporation <matthew.e.tolentino@पूर्णांकel.com>
 */

#समावेश <linux/capability.h>
#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/mm.h>
#समावेश <linux/module.h>
#समावेश <linux/माला.स>
#समावेश <linux/smp.h>
#समावेश <linux/efi.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/device.h>
#समावेश <linux/slab.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/ucs2_माला.स>

/* Private poपूर्णांकer to रेजिस्टरed efivars */
अटल काष्ठा efivars *__efivars;

/*
 * efivars_lock protects three things:
 * 1) efivarfs_list and efivars_sysfs_list
 * 2) ->ops calls
 * 3) (un)registration of __efivars
 */
अटल DEFINE_SEMAPHORE(efivars_lock);

अटल bool
validate_device_path(efi_अक्षर16_t *var_name, पूर्णांक match, u8 *buffer,
		     अचिन्हित दीर्घ len)
अणु
	काष्ठा efi_generic_dev_path *node;
	पूर्णांक offset = 0;

	node = (काष्ठा efi_generic_dev_path *)buffer;

	अगर (len < माप(*node))
		वापस false;

	जबतक (offset <= len - माप(*node) &&
	       node->length >= माप(*node) &&
		node->length <= len - offset) अणु
		offset += node->length;

		अगर ((node->type == EFI_DEV_END_PATH ||
		     node->type == EFI_DEV_END_PATH2) &&
		    node->sub_type == EFI_DEV_END_ENTIRE)
			वापस true;

		node = (काष्ठा efi_generic_dev_path *)(buffer + offset);
	पूर्ण

	/*
	 * If we're here then either node->length poपूर्णांकed past the end
	 * of the buffer or we reached the end of the buffer without
	 * finding a device path end node.
	 */
	वापस false;
पूर्ण

अटल bool
validate_boot_order(efi_अक्षर16_t *var_name, पूर्णांक match, u8 *buffer,
		    अचिन्हित दीर्घ len)
अणु
	/* An array of 16-bit पूर्णांकegers */
	अगर ((len % 2) != 0)
		वापस false;

	वापस true;
पूर्ण

अटल bool
validate_load_option(efi_अक्षर16_t *var_name, पूर्णांक match, u8 *buffer,
		     अचिन्हित दीर्घ len)
अणु
	u16 filepathlength;
	पूर्णांक i, desclength = 0, namelen;

	namelen = ucs2_strnlen(var_name, EFI_VAR_NAME_LEN);

	/* Either "Boot" or "Driver" followed by four digits of hex */
	क्रम (i = match; i < match+4; i++) अणु
		अगर (var_name[i] > 127 ||
		    hex_to_bin(var_name[i] & 0xff) < 0)
			वापस true;
	पूर्ण

	/* Reject it अगर there's 4 digits of hex and then further content */
	अगर (namelen > match + 4)
		वापस false;

	/* A valid entry must be at least 8 bytes */
	अगर (len < 8)
		वापस false;

	filepathlength = buffer[4] | buffer[5] << 8;

	/*
	 * There's no stored length क्रम the description, so it has to be
	 * found by hand
	 */
	desclength = ucs2_strsize((efi_अक्षर16_t *)(buffer + 6), len - 6) + 2;

	/* Each boot entry must have a descriptor */
	अगर (!desclength)
		वापस false;

	/*
	 * If the sum of the length of the description, the claimed filepath
	 * length and the original header are greater than the length of the
	 * variable, it's malक्रमmed
	 */
	अगर ((desclength + filepathlength + 6) > len)
		वापस false;

	/*
	 * And, finally, check the filepath
	 */
	वापस validate_device_path(var_name, match, buffer + desclength + 6,
				    filepathlength);
पूर्ण

अटल bool
validate_uपूर्णांक16(efi_अक्षर16_t *var_name, पूर्णांक match, u8 *buffer,
		अचिन्हित दीर्घ len)
अणु
	/* A single 16-bit पूर्णांकeger */
	अगर (len != 2)
		वापस false;

	वापस true;
पूर्ण

अटल bool
validate_ascii_string(efi_अक्षर16_t *var_name, पूर्णांक match, u8 *buffer,
		      अचिन्हित दीर्घ len)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < len; i++) अणु
		अगर (buffer[i] > 127)
			वापस false;

		अगर (buffer[i] == 0)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

काष्ठा variable_validate अणु
	efi_guid_t venकरोr;
	अक्षर *name;
	bool (*validate)(efi_अक्षर16_t *var_name, पूर्णांक match, u8 *data,
			 अचिन्हित दीर्घ len);
पूर्ण;

/*
 * This is the list of variables we need to validate, as well as the
 * whitelist क्रम what we think is safe not to शेष to immutable.
 *
 * If it has a validate() method that's not NULL, it'll go पूर्णांकo the
 * validation routine.  If not, it is assumed valid, but still used क्रम
 * whitelisting.
 *
 * Note that it's sorted by अणुvenकरोr,nameपूर्ण, but globbed names must come after
 * any other name with the same prefix.
 */
अटल स्थिर काष्ठा variable_validate variable_validate[] = अणु
	अणु EFI_GLOBAL_VARIABLE_GUID, "BootNext", validate_uपूर्णांक16 पूर्ण,
	अणु EFI_GLOBAL_VARIABLE_GUID, "BootOrder", validate_boot_order पूर्ण,
	अणु EFI_GLOBAL_VARIABLE_GUID, "Boot*", validate_load_option पूर्ण,
	अणु EFI_GLOBAL_VARIABLE_GUID, "DriverOrder", validate_boot_order पूर्ण,
	अणु EFI_GLOBAL_VARIABLE_GUID, "Driver*", validate_load_option पूर्ण,
	अणु EFI_GLOBAL_VARIABLE_GUID, "ConIn", validate_device_path पूर्ण,
	अणु EFI_GLOBAL_VARIABLE_GUID, "ConInDev", validate_device_path पूर्ण,
	अणु EFI_GLOBAL_VARIABLE_GUID, "ConOut", validate_device_path पूर्ण,
	अणु EFI_GLOBAL_VARIABLE_GUID, "ConOutDev", validate_device_path पूर्ण,
	अणु EFI_GLOBAL_VARIABLE_GUID, "ErrOut", validate_device_path पूर्ण,
	अणु EFI_GLOBAL_VARIABLE_GUID, "ErrOutDev", validate_device_path पूर्ण,
	अणु EFI_GLOBAL_VARIABLE_GUID, "Lang", validate_ascii_string पूर्ण,
	अणु EFI_GLOBAL_VARIABLE_GUID, "OsIndications", शून्य पूर्ण,
	अणु EFI_GLOBAL_VARIABLE_GUID, "PlatformLang", validate_ascii_string पूर्ण,
	अणु EFI_GLOBAL_VARIABLE_GUID, "Timeout", validate_uपूर्णांक16 पूर्ण,
	अणु LINUX_EFI_CRASH_GUID, "*", शून्य पूर्ण,
	अणु शून्य_GUID, "", शून्य पूर्ण,
पूर्ण;

/*
 * Check अगर @var_name matches the pattern given in @match_name.
 *
 * @var_name: an array of @len non-NUL अक्षरacters.
 * @match_name: a NUL-terminated pattern string, optionally ending in "*". A
 *              final "*" अक्षरacter matches any trailing अक्षरacters @var_name,
 *              including the हाल when there are none left in @var_name.
 * @match: on output, the number of non-wildcard अक्षरacters in @match_name
 *         that @var_name matches, regardless of the वापस value.
 * @वापस: whether @var_name fully matches @match_name.
 */
अटल bool
variable_matches(स्थिर अक्षर *var_name, माप_प्रकार len, स्थिर अक्षर *match_name,
		 पूर्णांक *match)
अणु
	क्रम (*match = 0; ; (*match)++) अणु
		अक्षर c = match_name[*match];

		चयन (c) अणु
		हाल '*':
			/* Wildcard in @match_name means we've matched. */
			वापस true;

		हाल '\0':
			/* @match_name has ended. Has @var_name too? */
			वापस (*match == len);

		शेष:
			/*
			 * We've reached a non-wildcard अक्षर in @match_name.
			 * Continue only अगर there's an identical अक्षरacter in
			 * @var_name.
			 */
			अगर (*match < len && c == var_name[*match])
				जारी;
			वापस false;
		पूर्ण
	पूर्ण
पूर्ण

bool
efivar_validate(efi_guid_t venकरोr, efi_अक्षर16_t *var_name, u8 *data,
		अचिन्हित दीर्घ data_size)
अणु
	पूर्णांक i;
	अचिन्हित दीर्घ utf8_size;
	u8 *utf8_name;

	utf8_size = ucs2_utf8size(var_name);
	utf8_name = kदो_स्मृति(utf8_size + 1, GFP_KERNEL);
	अगर (!utf8_name)
		वापस false;

	ucs2_as_utf8(utf8_name, var_name, utf8_size);
	utf8_name[utf8_size] = '\0';

	क्रम (i = 0; variable_validate[i].name[0] != '\0'; i++) अणु
		स्थिर अक्षर *name = variable_validate[i].name;
		पूर्णांक match = 0;

		अगर (efi_guidcmp(venकरोr, variable_validate[i].venकरोr))
			जारी;

		अगर (variable_matches(utf8_name, utf8_size+1, name, &match)) अणु
			अगर (variable_validate[i].validate == शून्य)
				अवरोध;
			kमुक्त(utf8_name);
			वापस variable_validate[i].validate(var_name, match,
							     data, data_size);
		पूर्ण
	पूर्ण
	kमुक्त(utf8_name);
	वापस true;
पूर्ण
EXPORT_SYMBOL_GPL(efivar_validate);

bool
efivar_variable_is_removable(efi_guid_t venकरोr, स्थिर अक्षर *var_name,
			     माप_प्रकार len)
अणु
	पूर्णांक i;
	bool found = false;
	पूर्णांक match = 0;

	/*
	 * Check अगर our variable is in the validated variables list
	 */
	क्रम (i = 0; variable_validate[i].name[0] != '\0'; i++) अणु
		अगर (efi_guidcmp(variable_validate[i].venकरोr, venकरोr))
			जारी;

		अगर (variable_matches(var_name, len,
				     variable_validate[i].name, &match)) अणु
			found = true;
			अवरोध;
		पूर्ण
	पूर्ण

	/*
	 * If it's in our list, it is removable.
	 */
	वापस found;
पूर्ण
EXPORT_SYMBOL_GPL(efivar_variable_is_removable);

अटल efi_status_t
check_var_size(u32 attributes, अचिन्हित दीर्घ size)
अणु
	स्थिर काष्ठा efivar_operations *fops;

	अगर (!__efivars)
		वापस EFI_UNSUPPORTED;

	fops = __efivars->ops;

	अगर (!fops->query_variable_store)
		वापस EFI_UNSUPPORTED;

	वापस fops->query_variable_store(attributes, size, false);
पूर्ण

अटल efi_status_t
check_var_size_nonblocking(u32 attributes, अचिन्हित दीर्घ size)
अणु
	स्थिर काष्ठा efivar_operations *fops;

	अगर (!__efivars)
		वापस EFI_UNSUPPORTED;

	fops = __efivars->ops;

	अगर (!fops->query_variable_store)
		वापस EFI_UNSUPPORTED;

	वापस fops->query_variable_store(attributes, size, true);
पूर्ण

अटल bool variable_is_present(efi_अक्षर16_t *variable_name, efi_guid_t *venकरोr,
				काष्ठा list_head *head)
अणु
	काष्ठा efivar_entry *entry, *n;
	अचिन्हित दीर्घ strsize1, strsize2;
	bool found = false;

	strsize1 = ucs2_strsize(variable_name, 1024);
	list_क्रम_each_entry_safe(entry, n, head, list) अणु
		strsize2 = ucs2_strsize(entry->var.VariableName, 1024);
		अगर (strsize1 == strsize2 &&
			!स_भेद(variable_name, &(entry->var.VariableName),
				strsize2) &&
			!efi_guidcmp(entry->var.VenकरोrGuid,
				*venकरोr)) अणु
			found = true;
			अवरोध;
		पूर्ण
	पूर्ण
	वापस found;
पूर्ण

/*
 * Returns the size of variable_name, in bytes, including the
 * terminating शून्य अक्षरacter, or variable_name_size अगर no शून्य
 * अक्षरacter is found among the first variable_name_size bytes.
 */
अटल अचिन्हित दीर्घ var_name_strnsize(efi_अक्षर16_t *variable_name,
				       अचिन्हित दीर्घ variable_name_size)
अणु
	अचिन्हित दीर्घ len;
	efi_अक्षर16_t c;

	/*
	 * The variable name is, by definition, a शून्य-terminated
	 * string, so make असलolutely sure that variable_name_size is
	 * the value we expect it to be. If not, वापस the real size.
	 */
	क्रम (len = 2; len <= variable_name_size; len += माप(c)) अणु
		c = variable_name[(len / माप(c)) - 1];
		अगर (!c)
			अवरोध;
	पूर्ण

	वापस min(len, variable_name_size);
पूर्ण

/*
 * Prपूर्णांक a warning when duplicate EFI variables are encountered and
 * disable the sysfs workqueue since the firmware is buggy.
 */
अटल व्योम dup_variable_bug(efi_अक्षर16_t *str16, efi_guid_t *venकरोr_guid,
			     अचिन्हित दीर्घ len16)
अणु
	माप_प्रकार i, len8 = len16 / माप(efi_अक्षर16_t);
	अक्षर *str8;

	str8 = kzalloc(len8, GFP_KERNEL);
	अगर (!str8)
		वापस;

	क्रम (i = 0; i < len8; i++)
		str8[i] = str16[i];

	prपूर्णांकk(KERN_WARNING "efivars: duplicate variable: %s-%pUl\n",
	       str8, venकरोr_guid);
	kमुक्त(str8);
पूर्ण

/**
 * efivar_init - build the initial list of EFI variables
 * @func: callback function to invoke क्रम every variable
 * @data: function-specअगरic data to pass to @func
 * @duplicates: error अगर we encounter duplicates on @head?
 * @head: initialised head of variable list
 *
 * Get every EFI variable from the firmware and invoke @func. @func
 * should call efivar_entry_add() to build the list of variables.
 *
 * Returns 0 on success, or a kernel error code on failure.
 */
पूर्णांक efivar_init(पूर्णांक (*func)(efi_अक्षर16_t *, efi_guid_t, अचिन्हित दीर्घ, व्योम *),
		व्योम *data, bool duplicates, काष्ठा list_head *head)
अणु
	स्थिर काष्ठा efivar_operations *ops;
	अचिन्हित दीर्घ variable_name_size = 1024;
	efi_अक्षर16_t *variable_name;
	efi_status_t status;
	efi_guid_t venकरोr_guid;
	पूर्णांक err = 0;

	अगर (!__efivars)
		वापस -EFAULT;

	ops = __efivars->ops;

	variable_name = kzalloc(variable_name_size, GFP_KERNEL);
	अगर (!variable_name) अणु
		prपूर्णांकk(KERN_ERR "efivars: Memory allocation failed.\n");
		वापस -ENOMEM;
	पूर्ण

	अगर (करोwn_पूर्णांकerruptible(&efivars_lock)) अणु
		err = -EINTR;
		जाओ मुक्त;
	पूर्ण

	/*
	 * Per EFI spec, the maximum storage allocated क्रम both
	 * the variable name and variable data is 1024 bytes.
	 */

	करो अणु
		variable_name_size = 1024;

		status = ops->get_next_variable(&variable_name_size,
						variable_name,
						&venकरोr_guid);
		चयन (status) अणु
		हाल EFI_SUCCESS:
			अगर (duplicates)
				up(&efivars_lock);

			variable_name_size = var_name_strnsize(variable_name,
							       variable_name_size);

			/*
			 * Some firmware implementations वापस the
			 * same variable name on multiple calls to
			 * get_next_variable(). Terminate the loop
			 * immediately as there is no guarantee that
			 * we'll ever see a dअगरferent variable name,
			 * and may end up looping here क्रमever.
			 */
			अगर (duplicates &&
			    variable_is_present(variable_name, &venकरोr_guid,
						head)) अणु
				dup_variable_bug(variable_name, &venकरोr_guid,
						 variable_name_size);
				status = EFI_NOT_FOUND;
			पूर्ण अन्यथा अणु
				err = func(variable_name, venकरोr_guid,
					   variable_name_size, data);
				अगर (err)
					status = EFI_NOT_FOUND;
			पूर्ण

			अगर (duplicates) अणु
				अगर (करोwn_पूर्णांकerruptible(&efivars_lock)) अणु
					err = -EINTR;
					जाओ मुक्त;
				पूर्ण
			पूर्ण

			अवरोध;
		हाल EFI_UNSUPPORTED:
			err = -EOPNOTSUPP;
			status = EFI_NOT_FOUND;
			अवरोध;
		हाल EFI_NOT_FOUND:
			अवरोध;
		शेष:
			prपूर्णांकk(KERN_WARNING "efivars: get_next_variable: status=%lx\n",
				status);
			status = EFI_NOT_FOUND;
			अवरोध;
		पूर्ण

	पूर्ण जबतक (status != EFI_NOT_FOUND);

	up(&efivars_lock);
मुक्त:
	kमुक्त(variable_name);

	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(efivar_init);

/**
 * efivar_entry_add - add entry to variable list
 * @entry: entry to add to list
 * @head: list head
 *
 * Returns 0 on success, or a kernel error code on failure.
 */
पूर्णांक efivar_entry_add(काष्ठा efivar_entry *entry, काष्ठा list_head *head)
अणु
	अगर (करोwn_पूर्णांकerruptible(&efivars_lock))
		वापस -EINTR;
	list_add(&entry->list, head);
	up(&efivars_lock);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(efivar_entry_add);

/**
 * efivar_entry_हटाओ - हटाओ entry from variable list
 * @entry: entry to हटाओ from list
 *
 * Returns 0 on success, or a kernel error code on failure.
 */
पूर्णांक efivar_entry_हटाओ(काष्ठा efivar_entry *entry)
अणु
	अगर (करोwn_पूर्णांकerruptible(&efivars_lock))
		वापस -EINTR;
	list_del(&entry->list);
	up(&efivars_lock);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(efivar_entry_हटाओ);

/*
 * efivar_entry_list_del_unlock - हटाओ entry from variable list
 * @entry: entry to हटाओ
 *
 * Remove @entry from the variable list and release the list lock.
 *
 * NOTE: slightly weird locking semantics here - we expect to be
 * called with the efivars lock alपढ़ोy held, and we release it beक्रमe
 * वापसing. This is because this function is usually called after
 * set_variable() जबतक the lock is still held.
 */
अटल व्योम efivar_entry_list_del_unlock(काष्ठा efivar_entry *entry)
अणु
	list_del(&entry->list);
	up(&efivars_lock);
पूर्ण

/**
 * __efivar_entry_delete - delete an EFI variable
 * @entry: entry containing EFI variable to delete
 *
 * Delete the variable from the firmware but leave @entry on the
 * variable list.
 *
 * This function dअगरfers from efivar_entry_delete() because it करोes
 * not हटाओ @entry from the variable list. Also, it is safe to be
 * called from within a efivar_entry_iter_begin() and
 * efivar_entry_iter_end() region, unlike efivar_entry_delete().
 *
 * Returns 0 on success, or a converted EFI status code अगर
 * set_variable() fails.
 */
पूर्णांक __efivar_entry_delete(काष्ठा efivar_entry *entry)
अणु
	efi_status_t status;

	अगर (!__efivars)
		वापस -EINVAL;

	status = __efivars->ops->set_variable(entry->var.VariableName,
					      &entry->var.VenकरोrGuid,
					      0, 0, शून्य);

	वापस efi_status_to_err(status);
पूर्ण
EXPORT_SYMBOL_GPL(__efivar_entry_delete);

/**
 * efivar_entry_delete - delete variable and हटाओ entry from list
 * @entry: entry containing variable to delete
 *
 * Delete the variable from the firmware and हटाओ @entry from the
 * variable list. It is the caller's responsibility to मुक्त @entry
 * once we वापस.
 *
 * Returns 0 on success, -EINTR अगर we can't grab the semaphore,
 * converted EFI status code अगर set_variable() fails.
 */
पूर्णांक efivar_entry_delete(काष्ठा efivar_entry *entry)
अणु
	स्थिर काष्ठा efivar_operations *ops;
	efi_status_t status;

	अगर (करोwn_पूर्णांकerruptible(&efivars_lock))
		वापस -EINTR;

	अगर (!__efivars) अणु
		up(&efivars_lock);
		वापस -EINVAL;
	पूर्ण
	ops = __efivars->ops;
	status = ops->set_variable(entry->var.VariableName,
				   &entry->var.VenकरोrGuid,
				   0, 0, शून्य);
	अगर (!(status == EFI_SUCCESS || status == EFI_NOT_FOUND)) अणु
		up(&efivars_lock);
		वापस efi_status_to_err(status);
	पूर्ण

	efivar_entry_list_del_unlock(entry);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(efivar_entry_delete);

/**
 * efivar_entry_set - call set_variable()
 * @entry: entry containing the EFI variable to ग_लिखो
 * @attributes: variable attributes
 * @size: size of @data buffer
 * @data: buffer containing variable data
 * @head: head of variable list
 *
 * Calls set_variable() क्रम an EFI variable. If creating a new EFI
 * variable, this function is usually followed by efivar_entry_add().
 *
 * Beक्रमe writing the variable, the reमुख्यing EFI variable storage
 * space is checked to ensure there is enough room available.
 *
 * If @head is not शून्य a lookup is perक्रमmed to determine whether
 * the entry is alपढ़ोy on the list.
 *
 * Returns 0 on success, -EINTR अगर we can't grab the semaphore,
 * -EEXIST अगर a lookup is perक्रमmed and the entry alपढ़ोy exists on
 * the list, or a converted EFI status code अगर set_variable() fails.
 */
पूर्णांक efivar_entry_set(काष्ठा efivar_entry *entry, u32 attributes,
		     अचिन्हित दीर्घ size, व्योम *data, काष्ठा list_head *head)
अणु
	स्थिर काष्ठा efivar_operations *ops;
	efi_status_t status;
	efi_अक्षर16_t *name = entry->var.VariableName;
	efi_guid_t venकरोr = entry->var.VenकरोrGuid;

	अगर (करोwn_पूर्णांकerruptible(&efivars_lock))
		वापस -EINTR;

	अगर (!__efivars) अणु
		up(&efivars_lock);
		वापस -EINVAL;
	पूर्ण
	ops = __efivars->ops;
	अगर (head && efivar_entry_find(name, venकरोr, head, false)) अणु
		up(&efivars_lock);
		वापस -EEXIST;
	पूर्ण

	status = check_var_size(attributes, size + ucs2_strsize(name, 1024));
	अगर (status == EFI_SUCCESS || status == EFI_UNSUPPORTED)
		status = ops->set_variable(name, &venकरोr,
					   attributes, size, data);

	up(&efivars_lock);

	वापस efi_status_to_err(status);

पूर्ण
EXPORT_SYMBOL_GPL(efivar_entry_set);

/*
 * efivar_entry_set_nonblocking - call set_variable_nonblocking()
 *
 * This function is guaranteed to not block and is suitable क्रम calling
 * from crash/panic handlers.
 *
 * Crucially, this function will not block अगर it cannot acquire
 * efivars_lock. Instead, it वापसs -EBUSY.
 */
अटल पूर्णांक
efivar_entry_set_nonblocking(efi_अक्षर16_t *name, efi_guid_t venकरोr,
			     u32 attributes, अचिन्हित दीर्घ size, व्योम *data)
अणु
	स्थिर काष्ठा efivar_operations *ops;
	efi_status_t status;

	अगर (करोwn_trylock(&efivars_lock))
		वापस -EBUSY;

	अगर (!__efivars) अणु
		up(&efivars_lock);
		वापस -EINVAL;
	पूर्ण

	status = check_var_size_nonblocking(attributes,
					    size + ucs2_strsize(name, 1024));
	अगर (status != EFI_SUCCESS) अणु
		up(&efivars_lock);
		वापस -ENOSPC;
	पूर्ण

	ops = __efivars->ops;
	status = ops->set_variable_nonblocking(name, &venकरोr, attributes,
					       size, data);

	up(&efivars_lock);
	वापस efi_status_to_err(status);
पूर्ण

/**
 * efivar_entry_set_safe - call set_variable() अगर enough space in firmware
 * @name: buffer containing the variable name
 * @venकरोr: variable venकरोr guid
 * @attributes: variable attributes
 * @block: can we block in this context?
 * @size: size of @data buffer
 * @data: buffer containing variable data
 *
 * Ensures there is enough मुक्त storage in the firmware क्रम this variable, and
 * अगर so, calls set_variable(). If creating a new EFI variable, this function
 * is usually followed by efivar_entry_add().
 *
 * Returns 0 on success, -ENOSPC अगर the firmware करोes not have enough
 * space क्रम set_variable() to succeed, or a converted EFI status code
 * अगर set_variable() fails.
 */
पूर्णांक efivar_entry_set_safe(efi_अक्षर16_t *name, efi_guid_t venकरोr, u32 attributes,
			  bool block, अचिन्हित दीर्घ size, व्योम *data)
अणु
	स्थिर काष्ठा efivar_operations *ops;
	efi_status_t status;

	अगर (!__efivars)
		वापस -EINVAL;

	ops = __efivars->ops;
	अगर (!ops->query_variable_store)
		वापस -ENOSYS;

	/*
	 * If the EFI variable backend provides a non-blocking
	 * ->set_variable() operation and we're in a context where we
	 * cannot block, then we need to use it to aव्योम live-locks,
	 * since the implication is that the regular ->set_variable()
	 * will block.
	 *
	 * If no ->set_variable_nonblocking() is provided then
	 * ->set_variable() is assumed to be non-blocking.
	 */
	अगर (!block && ops->set_variable_nonblocking)
		वापस efivar_entry_set_nonblocking(name, venकरोr, attributes,
						    size, data);

	अगर (!block) अणु
		अगर (करोwn_trylock(&efivars_lock))
			वापस -EBUSY;
	पूर्ण अन्यथा अणु
		अगर (करोwn_पूर्णांकerruptible(&efivars_lock))
			वापस -EINTR;
	पूर्ण

	status = check_var_size(attributes, size + ucs2_strsize(name, 1024));
	अगर (status != EFI_SUCCESS) अणु
		up(&efivars_lock);
		वापस -ENOSPC;
	पूर्ण

	status = ops->set_variable(name, &venकरोr, attributes, size, data);

	up(&efivars_lock);

	वापस efi_status_to_err(status);
पूर्ण
EXPORT_SYMBOL_GPL(efivar_entry_set_safe);

/**
 * efivar_entry_find - search क्रम an entry
 * @name: the EFI variable name
 * @guid: the EFI variable venकरोr's guid
 * @head: head of the variable list
 * @हटाओ: should we हटाओ the entry from the list?
 *
 * Search क्रम an entry on the variable list that has the EFI variable
 * name @name and venकरोr guid @guid. If an entry is found on the list
 * and @हटाओ is true, the entry is हटाओd from the list.
 *
 * The caller MUST call efivar_entry_iter_begin() and
 * efivar_entry_iter_end() beक्रमe and after the invocation of this
 * function, respectively.
 *
 * Returns the entry अगर found on the list, %शून्य otherwise.
 */
काष्ठा efivar_entry *efivar_entry_find(efi_अक्षर16_t *name, efi_guid_t guid,
				       काष्ठा list_head *head, bool हटाओ)
अणु
	काष्ठा efivar_entry *entry, *n;
	पूर्णांक strsize1, strsize2;
	bool found = false;

	list_क्रम_each_entry_safe(entry, n, head, list) अणु
		strsize1 = ucs2_strsize(name, 1024);
		strsize2 = ucs2_strsize(entry->var.VariableName, 1024);
		अगर (strsize1 == strsize2 &&
		    !स_भेद(name, &(entry->var.VariableName), strsize1) &&
		    !efi_guidcmp(guid, entry->var.VenकरोrGuid)) अणु
			found = true;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!found)
		वापस शून्य;

	अगर (हटाओ) अणु
		अगर (entry->scanning) अणु
			/*
			 * The entry will be deleted
			 * after scanning is completed.
			 */
			entry->deleting = true;
		पूर्ण अन्यथा
			list_del(&entry->list);
	पूर्ण

	वापस entry;
पूर्ण
EXPORT_SYMBOL_GPL(efivar_entry_find);

/**
 * efivar_entry_size - obtain the size of a variable
 * @entry: entry क्रम this variable
 * @size: location to store the variable's size
 */
पूर्णांक efivar_entry_size(काष्ठा efivar_entry *entry, अचिन्हित दीर्घ *size)
अणु
	स्थिर काष्ठा efivar_operations *ops;
	efi_status_t status;

	*size = 0;

	अगर (करोwn_पूर्णांकerruptible(&efivars_lock))
		वापस -EINTR;
	अगर (!__efivars) अणु
		up(&efivars_lock);
		वापस -EINVAL;
	पूर्ण
	ops = __efivars->ops;
	status = ops->get_variable(entry->var.VariableName,
				   &entry->var.VenकरोrGuid, शून्य, size, शून्य);
	up(&efivars_lock);

	अगर (status != EFI_BUFFER_TOO_SMALL)
		वापस efi_status_to_err(status);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(efivar_entry_size);

/**
 * __efivar_entry_get - call get_variable()
 * @entry: पढ़ो data क्रम this variable
 * @attributes: variable attributes
 * @size: size of @data buffer
 * @data: buffer to store variable data
 *
 * The caller MUST call efivar_entry_iter_begin() and
 * efivar_entry_iter_end() beक्रमe and after the invocation of this
 * function, respectively.
 */
पूर्णांक __efivar_entry_get(काष्ठा efivar_entry *entry, u32 *attributes,
		       अचिन्हित दीर्घ *size, व्योम *data)
अणु
	efi_status_t status;

	अगर (!__efivars)
		वापस -EINVAL;

	status = __efivars->ops->get_variable(entry->var.VariableName,
					      &entry->var.VenकरोrGuid,
					      attributes, size, data);

	वापस efi_status_to_err(status);
पूर्ण
EXPORT_SYMBOL_GPL(__efivar_entry_get);

/**
 * efivar_entry_get - call get_variable()
 * @entry: पढ़ो data क्रम this variable
 * @attributes: variable attributes
 * @size: size of @data buffer
 * @data: buffer to store variable data
 */
पूर्णांक efivar_entry_get(काष्ठा efivar_entry *entry, u32 *attributes,
		     अचिन्हित दीर्घ *size, व्योम *data)
अणु
	efi_status_t status;

	अगर (करोwn_पूर्णांकerruptible(&efivars_lock))
		वापस -EINTR;

	अगर (!__efivars) अणु
		up(&efivars_lock);
		वापस -EINVAL;
	पूर्ण

	status = __efivars->ops->get_variable(entry->var.VariableName,
					      &entry->var.VenकरोrGuid,
					      attributes, size, data);
	up(&efivars_lock);

	वापस efi_status_to_err(status);
पूर्ण
EXPORT_SYMBOL_GPL(efivar_entry_get);

/**
 * efivar_entry_set_get_size - call set_variable() and get new size (atomic)
 * @entry: entry containing variable to set and get
 * @attributes: attributes of variable to be written
 * @size: size of data buffer
 * @data: buffer containing data to ग_लिखो
 * @set: did the set_variable() call succeed?
 *
 * This is a pretty special (complex) function. See efivarfs_file_ग_लिखो().
 *
 * Atomically call set_variable() क्रम @entry and अगर the call is
 * successful, वापस the new size of the variable from get_variable()
 * in @size. The success of set_variable() is indicated by @set.
 *
 * Returns 0 on success, -EINVAL अगर the variable data is invalid,
 * -ENOSPC अगर the firmware करोes not have enough available space, or a
 * converted EFI status code अगर either of set_variable() or
 * get_variable() fail.
 *
 * If the EFI variable करोes not exist when calling set_variable()
 * (EFI_NOT_FOUND), @entry is हटाओd from the variable list.
 */
पूर्णांक efivar_entry_set_get_size(काष्ठा efivar_entry *entry, u32 attributes,
			      अचिन्हित दीर्घ *size, व्योम *data, bool *set)
अणु
	स्थिर काष्ठा efivar_operations *ops;
	efi_अक्षर16_t *name = entry->var.VariableName;
	efi_guid_t *venकरोr = &entry->var.VenकरोrGuid;
	efi_status_t status;
	पूर्णांक err;

	*set = false;

	अगर (efivar_validate(*venकरोr, name, data, *size) == false)
		वापस -EINVAL;

	/*
	 * The lock here protects the get_variable call, the conditional
	 * set_variable call, and removal of the variable from the efivars
	 * list (in the हाल of an authenticated delete).
	 */
	अगर (करोwn_पूर्णांकerruptible(&efivars_lock))
		वापस -EINTR;

	अगर (!__efivars) अणु
		err = -EINVAL;
		जाओ out;
	पूर्ण

	/*
	 * Ensure that the available space hasn't shrunk below the safe level
	 */
	status = check_var_size(attributes, *size + ucs2_strsize(name, 1024));
	अगर (status != EFI_SUCCESS) अणु
		अगर (status != EFI_UNSUPPORTED) अणु
			err = efi_status_to_err(status);
			जाओ out;
		पूर्ण

		अगर (*size > 65536) अणु
			err = -ENOSPC;
			जाओ out;
		पूर्ण
	पूर्ण

	ops = __efivars->ops;

	status = ops->set_variable(name, venकरोr, attributes, *size, data);
	अगर (status != EFI_SUCCESS) अणु
		err = efi_status_to_err(status);
		जाओ out;
	पूर्ण

	*set = true;

	/*
	 * Writing to the variable may have caused a change in size (which
	 * could either be an append or an overग_लिखो), or the variable to be
	 * deleted. Perक्रमm a GetVariable() so we can tell what actually
	 * happened.
	 */
	*size = 0;
	status = ops->get_variable(entry->var.VariableName,
				   &entry->var.VenकरोrGuid,
				   शून्य, size, शून्य);

	अगर (status == EFI_NOT_FOUND)
		efivar_entry_list_del_unlock(entry);
	अन्यथा
		up(&efivars_lock);

	अगर (status && status != EFI_BUFFER_TOO_SMALL)
		वापस efi_status_to_err(status);

	वापस 0;

out:
	up(&efivars_lock);
	वापस err;

पूर्ण
EXPORT_SYMBOL_GPL(efivar_entry_set_get_size);

/**
 * efivar_entry_iter_begin - begin iterating the variable list
 *
 * Lock the variable list to prevent entry insertion and removal until
 * efivar_entry_iter_end() is called. This function is usually used in
 * conjunction with __efivar_entry_iter() or efivar_entry_iter().
 */
पूर्णांक efivar_entry_iter_begin(व्योम)
अणु
	वापस करोwn_पूर्णांकerruptible(&efivars_lock);
पूर्ण
EXPORT_SYMBOL_GPL(efivar_entry_iter_begin);

/**
 * efivar_entry_iter_end - finish iterating the variable list
 *
 * Unlock the variable list and allow modअगरications to the list again.
 */
व्योम efivar_entry_iter_end(व्योम)
अणु
	up(&efivars_lock);
पूर्ण
EXPORT_SYMBOL_GPL(efivar_entry_iter_end);

/**
 * __efivar_entry_iter - iterate over variable list
 * @func: callback function
 * @head: head of the variable list
 * @data: function-specअगरic data to pass to callback
 * @prev: entry to begin iterating from
 *
 * Iterate over the list of EFI variables and call @func with every
 * entry on the list. It is safe क्रम @func to हटाओ entries in the
 * list via efivar_entry_delete().
 *
 * You MUST call efivar_entry_iter_begin() beक्रमe this function, and
 * efivar_entry_iter_end() afterwards.
 *
 * It is possible to begin iteration from an arbitrary entry within
 * the list by passing @prev. @prev is updated on वापस to poपूर्णांक to
 * the last entry passed to @func. To begin iterating from the
 * beginning of the list @prev must be %शून्य.
 *
 * The restrictions क्रम @func are the same as करोcumented क्रम
 * efivar_entry_iter().
 */
पूर्णांक __efivar_entry_iter(पूर्णांक (*func)(काष्ठा efivar_entry *, व्योम *),
			काष्ठा list_head *head, व्योम *data,
			काष्ठा efivar_entry **prev)
अणु
	काष्ठा efivar_entry *entry, *n;
	पूर्णांक err = 0;

	अगर (!prev || !*prev) अणु
		list_क्रम_each_entry_safe(entry, n, head, list) अणु
			err = func(entry, data);
			अगर (err)
				अवरोध;
		पूर्ण

		अगर (prev)
			*prev = entry;

		वापस err;
	पूर्ण


	list_क्रम_each_entry_safe_जारी((*prev), n, head, list) अणु
		err = func(*prev, data);
		अगर (err)
			अवरोध;
	पूर्ण

	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(__efivar_entry_iter);

/**
 * efivar_entry_iter - iterate over variable list
 * @func: callback function
 * @head: head of variable list
 * @data: function-specअगरic data to pass to callback
 *
 * Iterate over the list of EFI variables and call @func with every
 * entry on the list. It is safe क्रम @func to हटाओ entries in the
 * list via efivar_entry_delete() जबतक iterating.
 *
 * Some notes क्रम the callback function:
 *  - a non-zero वापस value indicates an error and terminates the loop
 *  - @func is called from atomic context
 */
पूर्णांक efivar_entry_iter(पूर्णांक (*func)(काष्ठा efivar_entry *, व्योम *),
		      काष्ठा list_head *head, व्योम *data)
अणु
	पूर्णांक err = 0;

	err = efivar_entry_iter_begin();
	अगर (err)
		वापस err;
	err = __efivar_entry_iter(func, head, data, शून्य);
	efivar_entry_iter_end();

	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(efivar_entry_iter);

/**
 * efivars_kobject - get the kobject क्रम the रेजिस्टरed efivars
 *
 * If efivars_रेजिस्टर() has not been called we वापस शून्य,
 * otherwise वापस the kobject used at registration समय.
 */
काष्ठा kobject *efivars_kobject(व्योम)
अणु
	अगर (!__efivars)
		वापस शून्य;

	वापस __efivars->kobject;
पूर्ण
EXPORT_SYMBOL_GPL(efivars_kobject);

/**
 * efivars_रेजिस्टर - रेजिस्टर an efivars
 * @efivars: efivars to रेजिस्टर
 * @ops: efivars operations
 * @kobject: @efivars-specअगरic kobject
 *
 * Only a single efivars can be रेजिस्टरed at any समय.
 */
पूर्णांक efivars_रेजिस्टर(काष्ठा efivars *efivars,
		     स्थिर काष्ठा efivar_operations *ops,
		     काष्ठा kobject *kobject)
अणु
	अगर (करोwn_पूर्णांकerruptible(&efivars_lock))
		वापस -EINTR;

	efivars->ops = ops;
	efivars->kobject = kobject;

	__efivars = efivars;

	pr_info("Registered efivars operations\n");

	up(&efivars_lock);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(efivars_रेजिस्टर);

/**
 * efivars_unरेजिस्टर - unरेजिस्टर an efivars
 * @efivars: efivars to unरेजिस्टर
 *
 * The caller must have alपढ़ोy हटाओd every entry from the list,
 * failure to करो so is an error.
 */
पूर्णांक efivars_unरेजिस्टर(काष्ठा efivars *efivars)
अणु
	पूर्णांक rv;

	अगर (करोwn_पूर्णांकerruptible(&efivars_lock))
		वापस -EINTR;

	अगर (!__efivars) अणु
		prपूर्णांकk(KERN_ERR "efivars not registered\n");
		rv = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (__efivars != efivars) अणु
		rv = -EINVAL;
		जाओ out;
	पूर्ण

	pr_info("Unregistered efivars operations\n");
	__efivars = शून्य;

	rv = 0;
out:
	up(&efivars_lock);
	वापस rv;
पूर्ण
EXPORT_SYMBOL_GPL(efivars_unरेजिस्टर);

पूर्णांक efivar_supports_ग_लिखोs(व्योम)
अणु
	वापस __efivars && __efivars->ops->set_variable;
पूर्ण
EXPORT_SYMBOL_GPL(efivar_supports_ग_लिखोs);
