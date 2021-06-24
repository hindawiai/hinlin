<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * efi.c - EFI subप्रणाली
 *
 * Copyright (C) 2001,2003,2004 Dell <Matt_Domsch@dell.com>
 * Copyright (C) 2004 Intel Corporation <matthew.e.tolentino@पूर्णांकel.com>
 * Copyright (C) 2013 Tom Gundersen <teg@jklm.no>
 *
 * This code रेजिस्टरs /sys/firmware/efiअणु,/efivarsपूर्ण when EFI is supported,
 * allowing the efivarfs to be mounted or the efivars module to be loaded.
 * The existance of /sys/firmware/efi may also be used by userspace to
 * determine that the प्रणाली supports EFI.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kobject.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/device.h>
#समावेश <linux/efi.h>
#समावेश <linux/of.h>
#समावेश <linux/पन.स>
#समावेश <linux/kexec.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/reboot.h>
#समावेश <linux/slab.h>
#समावेश <linux/acpi.h>
#समावेश <linux/ucs2_माला.स>
#समावेश <linux/memblock.h>
#समावेश <linux/security.h>

#समावेश <यंत्र/early_ioremap.h>

काष्ठा efi __पढ़ो_mostly efi = अणु
	.runसमय_supported_mask = EFI_RT_SUPPORTED_ALL,
	.acpi			= EFI_INVALID_TABLE_ADDR,
	.acpi20			= EFI_INVALID_TABLE_ADDR,
	.smbios			= EFI_INVALID_TABLE_ADDR,
	.smbios3		= EFI_INVALID_TABLE_ADDR,
	.esrt			= EFI_INVALID_TABLE_ADDR,
	.tpm_log		= EFI_INVALID_TABLE_ADDR,
	.tpm_final_log		= EFI_INVALID_TABLE_ADDR,
#अगर_घोषित CONFIG_LOAD_UEFI_KEYS
	.mokvar_table		= EFI_INVALID_TABLE_ADDR,
#पूर्ण_अगर
पूर्ण;
EXPORT_SYMBOL(efi);

अचिन्हित दीर्घ __ro_after_init efi_rng_seed = EFI_INVALID_TABLE_ADDR;
अटल अचिन्हित दीर्घ __initdata mem_reserve = EFI_INVALID_TABLE_ADDR;
अटल अचिन्हित दीर्घ __initdata rt_prop = EFI_INVALID_TABLE_ADDR;

काष्ठा mm_काष्ठा efi_mm = अणु
	.mm_rb			= RB_ROOT,
	.mm_users		= ATOMIC_INIT(2),
	.mm_count		= ATOMIC_INIT(1),
	.ग_लिखो_protect_seq      = SEQCNT_ZERO(efi_mm.ग_लिखो_protect_seq),
	MMAP_LOCK_INITIALIZER(efi_mm)
	.page_table_lock	= __SPIN_LOCK_UNLOCKED(efi_mm.page_table_lock),
	.mmlist			= LIST_HEAD_INIT(efi_mm.mmlist),
	.cpu_biपंचांगap		= अणु [BITS_TO_LONGS(NR_CPUS)] = 0पूर्ण,
पूर्ण;

काष्ठा workqueue_काष्ठा *efi_rts_wq;

अटल bool disable_runसमय;
अटल पूर्णांक __init setup_noefi(अक्षर *arg)
अणु
	disable_runसमय = true;
	वापस 0;
पूर्ण
early_param("noefi", setup_noefi);

bool efi_runसमय_disabled(व्योम)
अणु
	वापस disable_runसमय;
पूर्ण

bool __pure __efi_soft_reserve_enabled(व्योम)
अणु
	वापस !efi_enabled(EFI_MEM_NO_SOFT_RESERVE);
पूर्ण

अटल पूर्णांक __init parse_efi_cmdline(अक्षर *str)
अणु
	अगर (!str) अणु
		pr_warn("need at least one option\n");
		वापस -EINVAL;
	पूर्ण

	अगर (parse_option_str(str, "debug"))
		set_bit(EFI_DBG, &efi.flags);

	अगर (parse_option_str(str, "noruntime"))
		disable_runसमय = true;

	अगर (parse_option_str(str, "nosoftreserve"))
		set_bit(EFI_MEM_NO_SOFT_RESERVE, &efi.flags);

	वापस 0;
पूर्ण
early_param("efi", parse_efi_cmdline);

काष्ठा kobject *efi_kobj;

/*
 * Let's not leave out systab inक्रमmation that snuck पूर्णांकo
 * the efivars driver
 * Note, करो not add more fields in systab sysfs file as it अवरोधs sysfs
 * one value per file rule!
 */
अटल sमाप_प्रकार systab_show(काष्ठा kobject *kobj,
			   काष्ठा kobj_attribute *attr, अक्षर *buf)
अणु
	अक्षर *str = buf;

	अगर (!kobj || !buf)
		वापस -EINVAL;

	अगर (efi.acpi20 != EFI_INVALID_TABLE_ADDR)
		str += प्र_लिखो(str, "ACPI20=0x%lx\n", efi.acpi20);
	अगर (efi.acpi != EFI_INVALID_TABLE_ADDR)
		str += प्र_लिखो(str, "ACPI=0x%lx\n", efi.acpi);
	/*
	 * If both SMBIOS and SMBIOS3 entry poपूर्णांकs are implemented, the
	 * SMBIOS3 entry poपूर्णांक shall be preferred, so we list it first to
	 * let applications stop parsing after the first match.
	 */
	अगर (efi.smbios3 != EFI_INVALID_TABLE_ADDR)
		str += प्र_लिखो(str, "SMBIOS3=0x%lx\n", efi.smbios3);
	अगर (efi.smbios != EFI_INVALID_TABLE_ADDR)
		str += प्र_लिखो(str, "SMBIOS=0x%lx\n", efi.smbios);

	अगर (IS_ENABLED(CONFIG_IA64) || IS_ENABLED(CONFIG_X86))
		str = efi_systab_show_arch(str);

	वापस str - buf;
पूर्ण

अटल काष्ठा kobj_attribute efi_attr_systab = __ATTR_RO_MODE(systab, 0400);

अटल sमाप_प्रकार fw_platक्रमm_size_show(काष्ठा kobject *kobj,
				     काष्ठा kobj_attribute *attr, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%d\n", efi_enabled(EFI_64BIT) ? 64 : 32);
पूर्ण

बाह्य __weak काष्ठा kobj_attribute efi_attr_fw_venकरोr;
बाह्य __weak काष्ठा kobj_attribute efi_attr_runसमय;
बाह्य __weak काष्ठा kobj_attribute efi_attr_config_table;
अटल काष्ठा kobj_attribute efi_attr_fw_platक्रमm_size =
	__ATTR_RO(fw_platक्रमm_size);

अटल काष्ठा attribute *efi_subsys_attrs[] = अणु
	&efi_attr_systab.attr,
	&efi_attr_fw_platक्रमm_size.attr,
	&efi_attr_fw_venकरोr.attr,
	&efi_attr_runसमय.attr,
	&efi_attr_config_table.attr,
	शून्य,
पूर्ण;

umode_t __weak efi_attr_is_visible(काष्ठा kobject *kobj, काष्ठा attribute *attr,
				   पूर्णांक n)
अणु
	वापस attr->mode;
पूर्ण

अटल स्थिर काष्ठा attribute_group efi_subsys_attr_group = अणु
	.attrs = efi_subsys_attrs,
	.is_visible = efi_attr_is_visible,
पूर्ण;

अटल काष्ठा efivars generic_efivars;
अटल काष्ठा efivar_operations generic_ops;

अटल पूर्णांक generic_ops_रेजिस्टर(व्योम)
अणु
	generic_ops.get_variable = efi.get_variable;
	generic_ops.get_next_variable = efi.get_next_variable;
	generic_ops.query_variable_store = efi_query_variable_store;

	अगर (efi_rt_services_supported(EFI_RT_SUPPORTED_SET_VARIABLE)) अणु
		generic_ops.set_variable = efi.set_variable;
		generic_ops.set_variable_nonblocking = efi.set_variable_nonblocking;
	पूर्ण
	वापस efivars_रेजिस्टर(&generic_efivars, &generic_ops, efi_kobj);
पूर्ण

अटल व्योम generic_ops_unरेजिस्टर(व्योम)
अणु
	efivars_unरेजिस्टर(&generic_efivars);
पूर्ण

#अगर_घोषित CONFIG_EFI_CUSTOM_SSDT_OVERLAYS
#घोषणा EFIVAR_SSDT_NAME_MAX	16
अटल अक्षर efivar_ssdt[EFIVAR_SSDT_NAME_MAX] __initdata;
अटल पूर्णांक __init efivar_ssdt_setup(अक्षर *str)
अणु
	पूर्णांक ret = security_locked_करोwn(LOCKDOWN_ACPI_TABLES);

	अगर (ret)
		वापस ret;

	अगर (म_माप(str) < माप(efivar_ssdt))
		स_नकल(efivar_ssdt, str, म_माप(str));
	अन्यथा
		pr_warn("efivar_ssdt: name too long: %s\n", str);
	वापस 0;
पूर्ण
__setup("efivar_ssdt=", efivar_ssdt_setup);

अटल __init पूर्णांक efivar_ssdt_iter(efi_अक्षर16_t *name, efi_guid_t venकरोr,
				   अचिन्हित दीर्घ name_size, व्योम *data)
अणु
	काष्ठा efivar_entry *entry;
	काष्ठा list_head *list = data;
	अक्षर utf8_name[EFIVAR_SSDT_NAME_MAX];
	पूर्णांक limit = min_t(अचिन्हित दीर्घ, EFIVAR_SSDT_NAME_MAX, name_size);

	ucs2_as_utf8(utf8_name, name, limit - 1);
	अगर (म_भेदन(utf8_name, efivar_ssdt, limit) != 0)
		वापस 0;

	entry = kदो_स्मृति(माप(*entry), GFP_KERNEL);
	अगर (!entry)
		वापस 0;

	स_नकल(entry->var.VariableName, name, name_size);
	स_नकल(&entry->var.VenकरोrGuid, &venकरोr, माप(efi_guid_t));

	efivar_entry_add(entry, list);

	वापस 0;
पूर्ण

अटल __init पूर्णांक efivar_ssdt_load(व्योम)
अणु
	LIST_HEAD(entries);
	काष्ठा efivar_entry *entry, *aux;
	अचिन्हित दीर्घ size;
	व्योम *data;
	पूर्णांक ret;

	अगर (!efivar_ssdt[0])
		वापस 0;

	ret = efivar_init(efivar_ssdt_iter, &entries, true, &entries);

	list_क्रम_each_entry_safe(entry, aux, &entries, list) अणु
		pr_info("loading SSDT from variable %s-%pUl\n", efivar_ssdt,
			&entry->var.VenकरोrGuid);

		list_del(&entry->list);

		ret = efivar_entry_size(entry, &size);
		अगर (ret) अणु
			pr_err("failed to get var size\n");
			जाओ मुक्त_entry;
		पूर्ण

		data = kदो_स्मृति(size, GFP_KERNEL);
		अगर (!data) अणु
			ret = -ENOMEM;
			जाओ मुक्त_entry;
		पूर्ण

		ret = efivar_entry_get(entry, शून्य, &size, data);
		अगर (ret) अणु
			pr_err("failed to get var data\n");
			जाओ मुक्त_data;
		पूर्ण

		ret = acpi_load_table(data, शून्य);
		अगर (ret) अणु
			pr_err("failed to load table: %d\n", ret);
			जाओ मुक्त_data;
		पूर्ण

		जाओ मुक्त_entry;

मुक्त_data:
		kमुक्त(data);

मुक्त_entry:
		kमुक्त(entry);
	पूर्ण

	वापस ret;
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक efivar_ssdt_load(व्योम) अणु वापस 0; पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_DEBUG_FS

#घोषणा EFI_DEBUGFS_MAX_BLOBS 32

अटल काष्ठा debugfs_blob_wrapper debugfs_blob[EFI_DEBUGFS_MAX_BLOBS];

अटल व्योम __init efi_debugfs_init(व्योम)
अणु
	काष्ठा dentry *efi_debugfs;
	efi_memory_desc_t *md;
	अक्षर name[32];
	पूर्णांक type_count[EFI_BOOT_SERVICES_DATA + 1] = अणुपूर्ण;
	पूर्णांक i = 0;

	efi_debugfs = debugfs_create_dir("efi", शून्य);
	अगर (IS_ERR_OR_शून्य(efi_debugfs))
		वापस;

	क्रम_each_efi_memory_desc(md) अणु
		चयन (md->type) अणु
		हाल EFI_BOOT_SERVICES_CODE:
			snम_लिखो(name, माप(name), "boot_services_code%d",
				 type_count[md->type]++);
			अवरोध;
		हाल EFI_BOOT_SERVICES_DATA:
			snम_लिखो(name, माप(name), "boot_services_data%d",
				 type_count[md->type]++);
			अवरोध;
		शेष:
			जारी;
		पूर्ण

		अगर (i >= EFI_DEBUGFS_MAX_BLOBS) अणु
			pr_warn("More then %d EFI boot service segments, only showing first %d in debugfs\n",
				EFI_DEBUGFS_MAX_BLOBS, EFI_DEBUGFS_MAX_BLOBS);
			अवरोध;
		पूर्ण

		debugfs_blob[i].size = md->num_pages << EFI_PAGE_SHIFT;
		debugfs_blob[i].data = memremap(md->phys_addr,
						debugfs_blob[i].size,
						MEMREMAP_WB);
		अगर (!debugfs_blob[i].data)
			जारी;

		debugfs_create_blob(name, 0400, efi_debugfs, &debugfs_blob[i]);
		i++;
	पूर्ण
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम efi_debugfs_init(व्योम) अणुपूर्ण
#पूर्ण_अगर

/*
 * We रेजिस्टर the efi subप्रणाली with the firmware subप्रणाली and the
 * efivars subप्रणाली with the efi subप्रणाली, अगर the प्रणाली was booted with
 * EFI.
 */
अटल पूर्णांक __init efisubsys_init(व्योम)
अणु
	पूर्णांक error;

	अगर (!efi_enabled(EFI_RUNTIME_SERVICES))
		efi.runसमय_supported_mask = 0;

	अगर (!efi_enabled(EFI_BOOT))
		वापस 0;

	अगर (efi.runसमय_supported_mask) अणु
		/*
		 * Since we process only one efi_runसमय_service() at a समय, an
		 * ordered workqueue (which creates only one execution context)
		 * should suffice क्रम all our needs.
		 */
		efi_rts_wq = alloc_ordered_workqueue("efi_rts_wq", 0);
		अगर (!efi_rts_wq) अणु
			pr_err("Creating efi_rts_wq failed, EFI runtime services disabled.\n");
			clear_bit(EFI_RUNTIME_SERVICES, &efi.flags);
			efi.runसमय_supported_mask = 0;
			वापस 0;
		पूर्ण
	पूर्ण

	अगर (efi_rt_services_supported(EFI_RT_SUPPORTED_TIME_SERVICES))
		platक्रमm_device_रेजिस्टर_simple("rtc-efi", 0, शून्य, 0);

	/* We रेजिस्टर the efi directory at /sys/firmware/efi */
	efi_kobj = kobject_create_and_add("efi", firmware_kobj);
	अगर (!efi_kobj) अणु
		pr_err("efi: Firmware registration failed.\n");
		destroy_workqueue(efi_rts_wq);
		वापस -ENOMEM;
	पूर्ण

	अगर (efi_rt_services_supported(EFI_RT_SUPPORTED_GET_VARIABLE |
				      EFI_RT_SUPPORTED_GET_NEXT_VARIABLE_NAME)) अणु
		error = generic_ops_रेजिस्टर();
		अगर (error)
			जाओ err_put;
		efivar_ssdt_load();
		platक्रमm_device_रेजिस्टर_simple("efivars", 0, शून्य, 0);
	पूर्ण

	error = sysfs_create_group(efi_kobj, &efi_subsys_attr_group);
	अगर (error) अणु
		pr_err("efi: Sysfs attribute export failed with error %d.\n",
		       error);
		जाओ err_unरेजिस्टर;
	पूर्ण

	error = efi_runसमय_map_init(efi_kobj);
	अगर (error)
		जाओ err_हटाओ_group;

	/* and the standard mountpoपूर्णांक क्रम efivarfs */
	error = sysfs_create_mount_poपूर्णांक(efi_kobj, "efivars");
	अगर (error) अणु
		pr_err("efivars: Subsystem registration failed.\n");
		जाओ err_हटाओ_group;
	पूर्ण

	अगर (efi_enabled(EFI_DBG) && efi_enabled(EFI_PRESERVE_BS_REGIONS))
		efi_debugfs_init();

	वापस 0;

err_हटाओ_group:
	sysfs_हटाओ_group(efi_kobj, &efi_subsys_attr_group);
err_unरेजिस्टर:
	अगर (efi_rt_services_supported(EFI_RT_SUPPORTED_GET_VARIABLE |
				      EFI_RT_SUPPORTED_GET_NEXT_VARIABLE_NAME))
		generic_ops_unरेजिस्टर();
err_put:
	kobject_put(efi_kobj);
	destroy_workqueue(efi_rts_wq);
	वापस error;
पूर्ण

subsys_initcall(efisubsys_init);

/*
 * Find the efi memory descriptor क्रम a given physical address.  Given a
 * physical address, determine अगर it exists within an EFI Memory Map entry,
 * and अगर so, populate the supplied memory descriptor with the appropriate
 * data.
 */
पूर्णांक efi_mem_desc_lookup(u64 phys_addr, efi_memory_desc_t *out_md)
अणु
	efi_memory_desc_t *md;

	अगर (!efi_enabled(EFI_MEMMAP)) अणु
		pr_err_once("EFI_MEMMAP is not enabled.\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!out_md) अणु
		pr_err_once("out_md is null.\n");
		वापस -EINVAL;
        पूर्ण

	क्रम_each_efi_memory_desc(md) अणु
		u64 size;
		u64 end;

		size = md->num_pages << EFI_PAGE_SHIFT;
		end = md->phys_addr + size;
		अगर (phys_addr >= md->phys_addr && phys_addr < end) अणु
			स_नकल(out_md, md, माप(*out_md));
			वापस 0;
		पूर्ण
	पूर्ण
	वापस -ENOENT;
पूर्ण

/*
 * Calculate the highest address of an efi memory descriptor.
 */
u64 __init efi_mem_desc_end(efi_memory_desc_t *md)
अणु
	u64 size = md->num_pages << EFI_PAGE_SHIFT;
	u64 end = md->phys_addr + size;
	वापस end;
पूर्ण

व्योम __init __weak efi_arch_mem_reserve(phys_addr_t addr, u64 size) अणुपूर्ण

/**
 * efi_mem_reserve - Reserve an EFI memory region
 * @addr: Physical address to reserve
 * @size: Size of reservation
 *
 * Mark a region as reserved from general kernel allocation and
 * prevent it being released by efi_मुक्त_boot_services().
 *
 * This function should be called drivers once they've parsed EFI
 * configuration tables to figure out where their data lives, e.g.
 * efi_esrt_init().
 */
व्योम __init efi_mem_reserve(phys_addr_t addr, u64 size)
अणु
	अगर (!memblock_is_region_reserved(addr, size))
		memblock_reserve(addr, size);

	/*
	 * Some architectures (x86) reserve all boot services ranges
	 * until efi_मुक्त_boot_services() because of buggy firmware
	 * implementations. This means the above memblock_reserve() is
	 * superfluous on x86 and instead what it needs to करो is
	 * ensure the @start, @size is not मुक्तd.
	 */
	efi_arch_mem_reserve(addr, size);
पूर्ण

अटल स्थिर efi_config_table_type_t common_tables[] __initस्थिर = अणु
	अणुACPI_20_TABLE_GUID,			&efi.acpi20,		"ACPI 2.0"	पूर्ण,
	अणुACPI_TABLE_GUID,			&efi.acpi,		"ACPI"		पूर्ण,
	अणुSMBIOS_TABLE_GUID,			&efi.smbios,		"SMBIOS"	पूर्ण,
	अणुSMBIOS3_TABLE_GUID,			&efi.smbios3,		"SMBIOS 3.0"	पूर्ण,
	अणुEFI_SYSTEM_RESOURCE_TABLE_GUID,	&efi.esrt,		"ESRT"		पूर्ण,
	अणुEFI_MEMORY_ATTRIBUTES_TABLE_GUID,	&efi_mem_attr_table,	"MEMATTR"	पूर्ण,
	अणुLINUX_EFI_RANDOM_SEED_TABLE_GUID,	&efi_rng_seed,		"RNG"		पूर्ण,
	अणुLINUX_EFI_TPM_EVENT_LOG_GUID,		&efi.tpm_log,		"TPMEventLog"	पूर्ण,
	अणुLINUX_EFI_TPM_FINAL_LOG_GUID,		&efi.tpm_final_log,	"TPMFinalLog"	पूर्ण,
	अणुLINUX_EFI_MEMRESERVE_TABLE_GUID,	&mem_reserve,		"MEMRESERVE"	पूर्ण,
	अणुEFI_RT_PROPERTIES_TABLE_GUID,		&rt_prop,		"RTPROP"	पूर्ण,
#अगर_घोषित CONFIG_EFI_RCI2_TABLE
	अणुDELLEMC_EFI_RCI2_TABLE_GUID,		&rci2_table_phys			पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_LOAD_UEFI_KEYS
	अणुLINUX_EFI_MOK_VARIABLE_TABLE_GUID,	&efi.mokvar_table,	"MOKvar"	पूर्ण,
#पूर्ण_अगर
	अणुपूर्ण,
पूर्ण;

अटल __init पूर्णांक match_config_table(स्थिर efi_guid_t *guid,
				     अचिन्हित दीर्घ table,
				     स्थिर efi_config_table_type_t *table_types)
अणु
	पूर्णांक i;

	क्रम (i = 0; efi_guidcmp(table_types[i].guid, शून्य_GUID); i++) अणु
		अगर (!efi_guidcmp(*guid, table_types[i].guid)) अणु
			*(table_types[i].ptr) = table;
			अगर (table_types[i].name[0])
				pr_cont("%s=0x%lx ",
					table_types[i].name, table);
			वापस 1;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक __init efi_config_parse_tables(स्थिर efi_config_table_t *config_tables,
				   पूर्णांक count,
				   स्थिर efi_config_table_type_t *arch_tables)
अणु
	स्थिर efi_config_table_64_t *tbl64 = (व्योम *)config_tables;
	स्थिर efi_config_table_32_t *tbl32 = (व्योम *)config_tables;
	स्थिर efi_guid_t *guid;
	अचिन्हित दीर्घ table;
	पूर्णांक i;

	pr_info("");
	क्रम (i = 0; i < count; i++) अणु
		अगर (!IS_ENABLED(CONFIG_X86)) अणु
			guid = &config_tables[i].guid;
			table = (अचिन्हित दीर्घ)config_tables[i].table;
		पूर्ण अन्यथा अगर (efi_enabled(EFI_64BIT)) अणु
			guid = &tbl64[i].guid;
			table = tbl64[i].table;

			अगर (IS_ENABLED(CONFIG_X86_32) &&
			    tbl64[i].table > U32_MAX) अणु
				pr_cont("\n");
				pr_err("Table located above 4GB, disabling EFI.\n");
				वापस -EINVAL;
			पूर्ण
		पूर्ण अन्यथा अणु
			guid = &tbl32[i].guid;
			table = tbl32[i].table;
		पूर्ण

		अगर (!match_config_table(guid, table, common_tables) && arch_tables)
			match_config_table(guid, table, arch_tables);
	पूर्ण
	pr_cont("\n");
	set_bit(EFI_CONFIG_TABLES, &efi.flags);

	अगर (efi_rng_seed != EFI_INVALID_TABLE_ADDR) अणु
		काष्ठा linux_efi_अक्रमom_seed *seed;
		u32 size = 0;

		seed = early_memremap(efi_rng_seed, माप(*seed));
		अगर (seed != शून्य) अणु
			size = READ_ONCE(seed->size);
			early_memunmap(seed, माप(*seed));
		पूर्ण अन्यथा अणु
			pr_err("Could not map UEFI random seed!\n");
		पूर्ण
		अगर (size > 0) अणु
			seed = early_memremap(efi_rng_seed,
					      माप(*seed) + size);
			अगर (seed != शून्य) अणु
				pr_notice("seeding entropy pool\n");
				add_bootloader_अक्रमomness(seed->bits, size);
				early_memunmap(seed, माप(*seed) + size);
			पूर्ण अन्यथा अणु
				pr_err("Could not map UEFI random seed!\n");
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (!IS_ENABLED(CONFIG_X86_32) && efi_enabled(EFI_MEMMAP))
		efi_memattr_init();

	efi_tpm_eventlog_init();

	अगर (mem_reserve != EFI_INVALID_TABLE_ADDR) अणु
		अचिन्हित दीर्घ prsv = mem_reserve;

		जबतक (prsv) अणु
			काष्ठा linux_efi_memreserve *rsv;
			u8 *p;

			/*
			 * Just map a full page: that is what we will get
			 * anyway, and it permits us to map the entire entry
			 * beक्रमe knowing its size.
			 */
			p = early_memremap(ALIGN_DOWN(prsv, PAGE_SIZE),
					   PAGE_SIZE);
			अगर (p == शून्य) अणु
				pr_err("Could not map UEFI memreserve entry!\n");
				वापस -ENOMEM;
			पूर्ण

			rsv = (व्योम *)(p + prsv % PAGE_SIZE);

			/* reserve the entry itself */
			memblock_reserve(prsv,
					 काष्ठा_size(rsv, entry, rsv->size));

			क्रम (i = 0; i < atomic_पढ़ो(&rsv->count); i++) अणु
				memblock_reserve(rsv->entry[i].base,
						 rsv->entry[i].size);
			पूर्ण

			prsv = rsv->next;
			early_memunmap(p, PAGE_SIZE);
		पूर्ण
	पूर्ण

	अगर (rt_prop != EFI_INVALID_TABLE_ADDR) अणु
		efi_rt_properties_table_t *tbl;

		tbl = early_memremap(rt_prop, माप(*tbl));
		अगर (tbl) अणु
			efi.runसमय_supported_mask &= tbl->runसमय_services_supported;
			early_memunmap(tbl, माप(*tbl));
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक __init efi_systab_check_header(स्थिर efi_table_hdr_t *systab_hdr,
				   पूर्णांक min_major_version)
अणु
	अगर (systab_hdr->signature != EFI_SYSTEM_TABLE_SIGNATURE) अणु
		pr_err("System table signature incorrect!\n");
		वापस -EINVAL;
	पूर्ण

	अगर ((systab_hdr->revision >> 16) < min_major_version)
		pr_err("Warning: System table version %d.%02d, expected %d.00 or greater!\n",
		       systab_hdr->revision >> 16,
		       systab_hdr->revision & 0xffff,
		       min_major_version);

	वापस 0;
पूर्ण

#अगर_अघोषित CONFIG_IA64
अटल स्थिर efi_अक्षर16_t *__init map_fw_venकरोr(अचिन्हित दीर्घ fw_venकरोr,
						माप_प्रकार size)
अणु
	स्थिर efi_अक्षर16_t *ret;

	ret = early_memremap_ro(fw_venकरोr, size);
	अगर (!ret)
		pr_err("Could not map the firmware vendor!\n");
	वापस ret;
पूर्ण

अटल व्योम __init unmap_fw_venकरोr(स्थिर व्योम *fw_venकरोr, माप_प्रकार size)
अणु
	early_memunmap((व्योम *)fw_venकरोr, size);
पूर्ण
#अन्यथा
#घोषणा map_fw_venकरोr(p, s)	__va(p)
#घोषणा unmap_fw_venकरोr(v, s)
#पूर्ण_अगर

व्योम __init efi_systab_report_header(स्थिर efi_table_hdr_t *systab_hdr,
				     अचिन्हित दीर्घ fw_venकरोr)
अणु
	अक्षर venकरोr[100] = "unknown";
	स्थिर efi_अक्षर16_t *c16;
	माप_प्रकार i;

	c16 = map_fw_venकरोr(fw_venकरोr, माप(venकरोr) * माप(efi_अक्षर16_t));
	अगर (c16) अणु
		क्रम (i = 0; i < माप(venकरोr) - 1 && c16[i]; ++i)
			venकरोr[i] = c16[i];
		venकरोr[i] = '\0';

		unmap_fw_venकरोr(c16, माप(venकरोr) * माप(efi_अक्षर16_t));
	पूर्ण

	pr_info("EFI v%u.%.02u by %s\n",
		systab_hdr->revision >> 16,
		systab_hdr->revision & 0xffff,
		venकरोr);
पूर्ण

अटल __initdata अक्षर memory_type_name[][13] = अणु
	"Reserved",
	"Loader Code",
	"Loader Data",
	"Boot Code",
	"Boot Data",
	"Runtime Code",
	"Runtime Data",
	"Conventional",
	"Unusable",
	"ACPI Reclaim",
	"ACPI Mem NVS",
	"MMIO",
	"MMIO Port",
	"PAL Code",
	"Persistent",
पूर्ण;

अक्षर * __init efi_md_typeattr_क्रमmat(अक्षर *buf, माप_प्रकार size,
				     स्थिर efi_memory_desc_t *md)
अणु
	अक्षर *pos;
	पूर्णांक type_len;
	u64 attr;

	pos = buf;
	अगर (md->type >= ARRAY_SIZE(memory_type_name))
		type_len = snम_लिखो(pos, size, "[type=%u", md->type);
	अन्यथा
		type_len = snम_लिखो(pos, size, "[%-*s",
				    (पूर्णांक)(माप(memory_type_name[0]) - 1),
				    memory_type_name[md->type]);
	अगर (type_len >= size)
		वापस buf;

	pos += type_len;
	size -= type_len;

	attr = md->attribute;
	अगर (attr & ~(EFI_MEMORY_UC | EFI_MEMORY_WC | EFI_MEMORY_WT |
		     EFI_MEMORY_WB | EFI_MEMORY_UCE | EFI_MEMORY_RO |
		     EFI_MEMORY_WP | EFI_MEMORY_RP | EFI_MEMORY_XP |
		     EFI_MEMORY_NV | EFI_MEMORY_SP | EFI_MEMORY_CPU_CRYPTO |
		     EFI_MEMORY_RUNTIME | EFI_MEMORY_MORE_RELIABLE))
		snम_लिखो(pos, size, "|attr=0x%016llx]",
			 (अचिन्हित दीर्घ दीर्घ)attr);
	अन्यथा
		snम_लिखो(pos, size,
			 "|%3s|%2s|%2s|%2s|%2s|%2s|%2s|%2s|%2s|%3s|%2s|%2s|%2s|%2s]",
			 attr & EFI_MEMORY_RUNTIME		? "RUN" : "",
			 attr & EFI_MEMORY_MORE_RELIABLE	? "MR"  : "",
			 attr & EFI_MEMORY_CPU_CRYPTO   	? "CC"  : "",
			 attr & EFI_MEMORY_SP			? "SP"  : "",
			 attr & EFI_MEMORY_NV			? "NV"  : "",
			 attr & EFI_MEMORY_XP			? "XP"  : "",
			 attr & EFI_MEMORY_RP			? "RP"  : "",
			 attr & EFI_MEMORY_WP			? "WP"  : "",
			 attr & EFI_MEMORY_RO			? "RO"  : "",
			 attr & EFI_MEMORY_UCE			? "UCE" : "",
			 attr & EFI_MEMORY_WB			? "WB"  : "",
			 attr & EFI_MEMORY_WT			? "WT"  : "",
			 attr & EFI_MEMORY_WC			? "WC"  : "",
			 attr & EFI_MEMORY_UC			? "UC"  : "");
	वापस buf;
पूर्ण

/*
 * IA64 has a funky EFI memory map that करोesn't work the same way as
 * other architectures.
 */
#अगर_अघोषित CONFIG_IA64
/*
 * efi_mem_attributes - lookup memmap attributes क्रम physical address
 * @phys_addr: the physical address to lookup
 *
 * Search in the EFI memory map क्रम the region covering
 * @phys_addr. Returns the EFI memory attributes अगर the region
 * was found in the memory map, 0 otherwise.
 */
u64 efi_mem_attributes(अचिन्हित दीर्घ phys_addr)
अणु
	efi_memory_desc_t *md;

	अगर (!efi_enabled(EFI_MEMMAP))
		वापस 0;

	क्रम_each_efi_memory_desc(md) अणु
		अगर ((md->phys_addr <= phys_addr) &&
		    (phys_addr < (md->phys_addr +
		    (md->num_pages << EFI_PAGE_SHIFT))))
			वापस md->attribute;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * efi_mem_type - lookup memmap type क्रम physical address
 * @phys_addr: the physical address to lookup
 *
 * Search in the EFI memory map क्रम the region covering @phys_addr.
 * Returns the EFI memory type अगर the region was found in the memory
 * map, -EINVAL otherwise.
 */
पूर्णांक efi_mem_type(अचिन्हित दीर्घ phys_addr)
अणु
	स्थिर efi_memory_desc_t *md;

	अगर (!efi_enabled(EFI_MEMMAP))
		वापस -ENOTSUPP;

	क्रम_each_efi_memory_desc(md) अणु
		अगर ((md->phys_addr <= phys_addr) &&
		    (phys_addr < (md->phys_addr +
				  (md->num_pages << EFI_PAGE_SHIFT))))
			वापस md->type;
	पूर्ण
	वापस -EINVAL;
पूर्ण
#पूर्ण_अगर

पूर्णांक efi_status_to_err(efi_status_t status)
अणु
	पूर्णांक err;

	चयन (status) अणु
	हाल EFI_SUCCESS:
		err = 0;
		अवरोध;
	हाल EFI_INVALID_PARAMETER:
		err = -EINVAL;
		अवरोध;
	हाल EFI_OUT_OF_RESOURCES:
		err = -ENOSPC;
		अवरोध;
	हाल EFI_DEVICE_ERROR:
		err = -EIO;
		अवरोध;
	हाल EFI_WRITE_PROTECTED:
		err = -EROFS;
		अवरोध;
	हाल EFI_SECURITY_VIOLATION:
		err = -EACCES;
		अवरोध;
	हाल EFI_NOT_FOUND:
		err = -ENOENT;
		अवरोध;
	हाल EFI_ABORTED:
		err = -EINTR;
		अवरोध;
	शेष:
		err = -EINVAL;
	पूर्ण

	वापस err;
पूर्ण

अटल DEFINE_SPINLOCK(efi_mem_reserve_persistent_lock);
अटल काष्ठा linux_efi_memreserve *efi_memreserve_root __ro_after_init;

अटल पूर्णांक __init efi_memreserve_map_root(व्योम)
अणु
	अगर (mem_reserve == EFI_INVALID_TABLE_ADDR)
		वापस -ENODEV;

	efi_memreserve_root = memremap(mem_reserve,
				       माप(*efi_memreserve_root),
				       MEMREMAP_WB);
	अगर (WARN_ON_ONCE(!efi_memreserve_root))
		वापस -ENOMEM;
	वापस 0;
पूर्ण

अटल पूर्णांक efi_mem_reserve_iomem(phys_addr_t addr, u64 size)
अणु
	काष्ठा resource *res, *parent;

	res = kzalloc(माप(काष्ठा resource), GFP_ATOMIC);
	अगर (!res)
		वापस -ENOMEM;

	res->name	= "reserved";
	res->flags	= IORESOURCE_MEM;
	res->start	= addr;
	res->end	= addr + size - 1;

	/* we expect a conflict with a 'System RAM' region */
	parent = request_resource_conflict(&iomem_resource, res);
	वापस parent ? request_resource(parent, res) : 0;
पूर्ण

पूर्णांक __ref efi_mem_reserve_persistent(phys_addr_t addr, u64 size)
अणु
	काष्ठा linux_efi_memreserve *rsv;
	अचिन्हित दीर्घ prsv;
	पूर्णांक rc, index;

	अगर (efi_memreserve_root == (व्योम *)अच_दीर्घ_उच्च)
		वापस -ENODEV;

	अगर (!efi_memreserve_root) अणु
		rc = efi_memreserve_map_root();
		अगर (rc)
			वापस rc;
	पूर्ण

	/* first try to find a slot in an existing linked list entry */
	क्रम (prsv = efi_memreserve_root->next; prsv; ) अणु
		rsv = memremap(prsv, माप(*rsv), MEMREMAP_WB);
		index = atomic_fetch_add_unless(&rsv->count, 1, rsv->size);
		अगर (index < rsv->size) अणु
			rsv->entry[index].base = addr;
			rsv->entry[index].size = size;

			memunmap(rsv);
			वापस efi_mem_reserve_iomem(addr, size);
		पूर्ण
		prsv = rsv->next;
		memunmap(rsv);
	पूर्ण

	/* no slot found - allocate a new linked list entry */
	rsv = (काष्ठा linux_efi_memreserve *)__get_मुक्त_page(GFP_ATOMIC);
	अगर (!rsv)
		वापस -ENOMEM;

	rc = efi_mem_reserve_iomem(__pa(rsv), SZ_4K);
	अगर (rc) अणु
		मुक्त_page((अचिन्हित दीर्घ)rsv);
		वापस rc;
	पूर्ण

	/*
	 * The memremap() call above assumes that a linux_efi_memreserve entry
	 * never crosses a page boundary, so let's ensure that this reमुख्यs true
	 * even when kexec'ing a 4k pages kernel from a >4k pages kernel, by
	 * using SZ_4K explicitly in the size calculation below.
	 */
	rsv->size = EFI_MEMRESERVE_COUNT(SZ_4K);
	atomic_set(&rsv->count, 1);
	rsv->entry[0].base = addr;
	rsv->entry[0].size = size;

	spin_lock(&efi_mem_reserve_persistent_lock);
	rsv->next = efi_memreserve_root->next;
	efi_memreserve_root->next = __pa(rsv);
	spin_unlock(&efi_mem_reserve_persistent_lock);

	वापस efi_mem_reserve_iomem(addr, size);
पूर्ण

अटल पूर्णांक __init efi_memreserve_root_init(व्योम)
अणु
	अगर (efi_memreserve_root)
		वापस 0;
	अगर (efi_memreserve_map_root())
		efi_memreserve_root = (व्योम *)अच_दीर्घ_उच्च;
	वापस 0;
पूर्ण
early_initcall(efi_memreserve_root_init);

#अगर_घोषित CONFIG_KEXEC
अटल पूर्णांक update_efi_अक्रमom_seed(काष्ठा notअगरier_block *nb,
				  अचिन्हित दीर्घ code, व्योम *unused)
अणु
	काष्ठा linux_efi_अक्रमom_seed *seed;
	u32 size = 0;

	अगर (!kexec_in_progress)
		वापस NOTIFY_DONE;

	seed = memremap(efi_rng_seed, माप(*seed), MEMREMAP_WB);
	अगर (seed != शून्य) अणु
		size = min(seed->size, EFI_RANDOM_SEED_SIZE);
		memunmap(seed);
	पूर्ण अन्यथा अणु
		pr_err("Could not map UEFI random seed!\n");
	पूर्ण
	अगर (size > 0) अणु
		seed = memremap(efi_rng_seed, माप(*seed) + size,
				MEMREMAP_WB);
		अगर (seed != शून्य) अणु
			seed->size = size;
			get_अक्रमom_bytes(seed->bits, seed->size);
			memunmap(seed);
		पूर्ण अन्यथा अणु
			pr_err("Could not map UEFI random seed!\n");
		पूर्ण
	पूर्ण
	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block efi_अक्रमom_seed_nb = अणु
	.notअगरier_call = update_efi_अक्रमom_seed,
पूर्ण;

अटल पूर्णांक __init रेजिस्टर_update_efi_अक्रमom_seed(व्योम)
अणु
	अगर (efi_rng_seed == EFI_INVALID_TABLE_ADDR)
		वापस 0;
	वापस रेजिस्टर_reboot_notअगरier(&efi_अक्रमom_seed_nb);
पूर्ण
late_initcall(रेजिस्टर_update_efi_अक्रमom_seed);
#पूर्ण_अगर
