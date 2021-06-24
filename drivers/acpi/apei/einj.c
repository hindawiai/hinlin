<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * APEI Error INJection support
 *
 * EINJ provides a hardware error injection mechanism, this is useful
 * क्रम debugging and testing of other APEI and RAS features.
 *
 * For more inक्रमmation about EINJ, please refer to ACPI Specअगरication
 * version 4.0, section 17.5.
 *
 * Copyright 2009-2010 Intel Corp.
 *   Author: Huang Ying <ying.huang@पूर्णांकel.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/debugfs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/nmi.h>
#समावेश <linux/delay.h>
#समावेश <linux/mm.h>
#समावेश <यंत्र/unaligned.h>

#समावेश "apei-internal.h"

#अघोषित pr_fmt
#घोषणा pr_fmt(fmt) "EINJ: " fmt

#घोषणा SPIN_UNIT		100			/* 100ns */
/* Firmware should respond within 1 milliseconds */
#घोषणा FIRMWARE_TIMEOUT	(1 * NSEC_PER_MSEC)
#घोषणा ACPI5_VENDOR_BIT	BIT(31)
#घोषणा MEM_ERROR_MASK		(ACPI_EINJ_MEMORY_CORRECTABLE | \
				ACPI_EINJ_MEMORY_UNCORRECTABLE | \
				ACPI_EINJ_MEMORY_FATAL)

/*
 * ACPI version 5 provides a SET_ERROR_TYPE_WITH_ADDRESS action.
 */
अटल पूर्णांक acpi5;

काष्ठा set_error_type_with_address अणु
	u32	type;
	u32	venकरोr_extension;
	u32	flags;
	u32	apicid;
	u64	memory_address;
	u64	memory_address_range;
	u32	pcie_sbdf;
पूर्ण;
क्रमागत अणु
	SETWA_FLAGS_APICID = 1,
	SETWA_FLAGS_MEM = 2,
	SETWA_FLAGS_PCIE_SBDF = 4,
पूर्ण;

/*
 * Venकरोr extensions क्रम platक्रमm specअगरic operations
 */
काष्ठा venकरोr_error_type_extension अणु
	u32	length;
	u32	pcie_sbdf;
	u16	venकरोr_id;
	u16	device_id;
	u8	rev_id;
	u8	reserved[3];
पूर्ण;

अटल u32 notrigger;

अटल u32 venकरोr_flags;
अटल काष्ठा debugfs_blob_wrapper venकरोr_blob;
अटल अक्षर venकरोr_dev[64];

/*
 * Some BIOSes allow parameters to the SET_ERROR_TYPE entries in the
 * EINJ table through an unpublished extension. Use with caution as
 * most will ignore the parameter and make their own choice of address
 * क्रम error injection.  This extension is used only अगर
 * param_extension module parameter is specअगरied.
 */
काष्ठा einj_parameter अणु
	u64 type;
	u64 reserved1;
	u64 reserved2;
	u64 param1;
	u64 param2;
पूर्ण;

#घोषणा EINJ_OP_BUSY			0x1
#घोषणा EINJ_STATUS_SUCCESS		0x0
#घोषणा EINJ_STATUS_FAIL		0x1
#घोषणा EINJ_STATUS_INVAL		0x2

#घोषणा EINJ_TAB_ENTRY(tab)						\
	((काष्ठा acpi_whea_header *)((अक्षर *)(tab) +			\
				    माप(काष्ठा acpi_table_einj)))

अटल bool param_extension;
module_param(param_extension, bool, 0);

अटल काष्ठा acpi_table_einj *einj_tab;

अटल काष्ठा apei_resources einj_resources;

अटल काष्ठा apei_exec_ins_type einj_ins_type[] = अणु
	[ACPI_EINJ_READ_REGISTER] = अणु
		.flags = APEI_EXEC_INS_ACCESS_REGISTER,
		.run   = apei_exec_पढ़ो_रेजिस्टर,
	पूर्ण,
	[ACPI_EINJ_READ_REGISTER_VALUE] = अणु
		.flags = APEI_EXEC_INS_ACCESS_REGISTER,
		.run   = apei_exec_पढ़ो_रेजिस्टर_value,
	पूर्ण,
	[ACPI_EINJ_WRITE_REGISTER] = अणु
		.flags = APEI_EXEC_INS_ACCESS_REGISTER,
		.run   = apei_exec_ग_लिखो_रेजिस्टर,
	पूर्ण,
	[ACPI_EINJ_WRITE_REGISTER_VALUE] = अणु
		.flags = APEI_EXEC_INS_ACCESS_REGISTER,
		.run   = apei_exec_ग_लिखो_रेजिस्टर_value,
	पूर्ण,
	[ACPI_EINJ_NOOP] = अणु
		.flags = 0,
		.run   = apei_exec_noop,
	पूर्ण,
पूर्ण;

/*
 * Prevent EINJ पूर्णांकerpreter to run simultaneously, because the
 * corresponding firmware implementation may not work properly when
 * invoked simultaneously.
 */
अटल DEFINE_MUTEX(einj_mutex);

अटल व्योम *einj_param;

अटल व्योम einj_exec_ctx_init(काष्ठा apei_exec_context *ctx)
अणु
	apei_exec_ctx_init(ctx, einj_ins_type, ARRAY_SIZE(einj_ins_type),
			   EINJ_TAB_ENTRY(einj_tab), einj_tab->entries);
पूर्ण

अटल पूर्णांक __einj_get_available_error_type(u32 *type)
अणु
	काष्ठा apei_exec_context ctx;
	पूर्णांक rc;

	einj_exec_ctx_init(&ctx);
	rc = apei_exec_run(&ctx, ACPI_EINJ_GET_ERROR_TYPE);
	अगर (rc)
		वापस rc;
	*type = apei_exec_ctx_get_output(&ctx);

	वापस 0;
पूर्ण

/* Get error injection capabilities of the platक्रमm */
अटल पूर्णांक einj_get_available_error_type(u32 *type)
अणु
	पूर्णांक rc;

	mutex_lock(&einj_mutex);
	rc = __einj_get_available_error_type(type);
	mutex_unlock(&einj_mutex);

	वापस rc;
पूर्ण

अटल पूर्णांक einj_समयकरोut(u64 *t)
अणु
	अगर ((s64)*t < SPIN_UNIT) अणु
		pr_warn(FW_WARN "Firmware does not respond in time\n");
		वापस 1;
	पूर्ण
	*t -= SPIN_UNIT;
	ndelay(SPIN_UNIT);
	touch_nmi_watchकरोg();
	वापस 0;
पूर्ण

अटल व्योम check_venकरोr_extension(u64 paddr,
				   काष्ठा set_error_type_with_address *v5param)
अणु
	पूर्णांक	offset = v5param->venकरोr_extension;
	काष्ठा	venकरोr_error_type_extension *v;
	u32	sbdf;

	अगर (!offset)
		वापस;
	v = acpi_os_map_iomem(paddr + offset, माप(*v));
	अगर (!v)
		वापस;
	sbdf = v->pcie_sbdf;
	प्र_लिखो(venकरोr_dev, "%x:%x:%x.%x vendor_id=%x device_id=%x rev_id=%x\n",
		sbdf >> 24, (sbdf >> 16) & 0xff,
		(sbdf >> 11) & 0x1f, (sbdf >> 8) & 0x7,
		 v->venकरोr_id, v->device_id, v->rev_id);
	acpi_os_unmap_iomem(v, माप(*v));
पूर्ण

अटल व्योम *einj_get_parameter_address(व्योम)
अणु
	पूर्णांक i;
	u64 pa_v4 = 0, pa_v5 = 0;
	काष्ठा acpi_whea_header *entry;

	entry = EINJ_TAB_ENTRY(einj_tab);
	क्रम (i = 0; i < einj_tab->entries; i++) अणु
		अगर (entry->action == ACPI_EINJ_SET_ERROR_TYPE &&
		    entry->inकाष्ठाion == ACPI_EINJ_WRITE_REGISTER &&
		    entry->रेजिस्टर_region.space_id ==
		    ACPI_ADR_SPACE_SYSTEM_MEMORY)
			pa_v4 = get_unaligned(&entry->रेजिस्टर_region.address);
		अगर (entry->action == ACPI_EINJ_SET_ERROR_TYPE_WITH_ADDRESS &&
		    entry->inकाष्ठाion == ACPI_EINJ_WRITE_REGISTER &&
		    entry->रेजिस्टर_region.space_id ==
		    ACPI_ADR_SPACE_SYSTEM_MEMORY)
			pa_v5 = get_unaligned(&entry->रेजिस्टर_region.address);
		entry++;
	पूर्ण
	अगर (pa_v5) अणु
		काष्ठा set_error_type_with_address *v5param;

		v5param = acpi_os_map_iomem(pa_v5, माप(*v5param));
		अगर (v5param) अणु
			acpi5 = 1;
			check_venकरोr_extension(pa_v5, v5param);
			वापस v5param;
		पूर्ण
	पूर्ण
	अगर (param_extension && pa_v4) अणु
		काष्ठा einj_parameter *v4param;

		v4param = acpi_os_map_iomem(pa_v4, माप(*v4param));
		अगर (!v4param)
			वापस शून्य;
		अगर (v4param->reserved1 || v4param->reserved2) अणु
			acpi_os_unmap_iomem(v4param, माप(*v4param));
			वापस शून्य;
		पूर्ण
		वापस v4param;
	पूर्ण

	वापस शून्य;
पूर्ण

/* करो sanity check to trigger table */
अटल पूर्णांक einj_check_trigger_header(काष्ठा acpi_einj_trigger *trigger_tab)
अणु
	अगर (trigger_tab->header_size != माप(काष्ठा acpi_einj_trigger))
		वापस -EINVAL;
	अगर (trigger_tab->table_size > PAGE_SIZE ||
	    trigger_tab->table_size < trigger_tab->header_size)
		वापस -EINVAL;
	अगर (trigger_tab->entry_count !=
	    (trigger_tab->table_size - trigger_tab->header_size) /
	    माप(काष्ठा acpi_einj_entry))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल काष्ठा acpi_generic_address *einj_get_trigger_parameter_region(
	काष्ठा acpi_einj_trigger *trigger_tab, u64 param1, u64 param2)
अणु
	पूर्णांक i;
	काष्ठा acpi_whea_header *entry;

	entry = (काष्ठा acpi_whea_header *)
		((अक्षर *)trigger_tab + माप(काष्ठा acpi_einj_trigger));
	क्रम (i = 0; i < trigger_tab->entry_count; i++) अणु
		अगर (entry->action == ACPI_EINJ_TRIGGER_ERROR &&
		entry->inकाष्ठाion <= ACPI_EINJ_WRITE_REGISTER_VALUE &&
		entry->रेजिस्टर_region.space_id ==
			ACPI_ADR_SPACE_SYSTEM_MEMORY &&
		(entry->रेजिस्टर_region.address & param2) == (param1 & param2))
			वापस &entry->रेजिस्टर_region;
		entry++;
	पूर्ण

	वापस शून्य;
पूर्ण
/* Execute inकाष्ठाions in trigger error action table */
अटल पूर्णांक __einj_error_trigger(u64 trigger_paddr, u32 type,
				u64 param1, u64 param2)
अणु
	काष्ठा acpi_einj_trigger *trigger_tab = शून्य;
	काष्ठा apei_exec_context trigger_ctx;
	काष्ठा apei_resources trigger_resources;
	काष्ठा acpi_whea_header *trigger_entry;
	काष्ठा resource *r;
	u32 table_size;
	पूर्णांक rc = -EIO;
	काष्ठा acpi_generic_address *trigger_param_region = शून्य;

	r = request_mem_region(trigger_paddr, माप(*trigger_tab),
			       "APEI EINJ Trigger Table");
	अगर (!r) अणु
		pr_err("Can not request [mem %#010llx-%#010llx] for Trigger table\n",
		       (अचिन्हित दीर्घ दीर्घ)trigger_paddr,
		       (अचिन्हित दीर्घ दीर्घ)trigger_paddr +
			    माप(*trigger_tab) - 1);
		जाओ out;
	पूर्ण
	trigger_tab = ioremap_cache(trigger_paddr, माप(*trigger_tab));
	अगर (!trigger_tab) अणु
		pr_err("Failed to map trigger table!\n");
		जाओ out_rel_header;
	पूर्ण
	rc = einj_check_trigger_header(trigger_tab);
	अगर (rc) अणु
		pr_warn(FW_BUG "Invalid trigger error action table.\n");
		जाओ out_rel_header;
	पूर्ण

	/* No action काष्ठाures in the TRIGGER_ERROR table, nothing to करो */
	अगर (!trigger_tab->entry_count)
		जाओ out_rel_header;

	rc = -EIO;
	table_size = trigger_tab->table_size;
	r = request_mem_region(trigger_paddr + माप(*trigger_tab),
			       table_size - माप(*trigger_tab),
			       "APEI EINJ Trigger Table");
	अगर (!r) अणु
		pr_err("Can not request [mem %#010llx-%#010llx] for Trigger Table Entry\n",
		       (अचिन्हित दीर्घ दीर्घ)trigger_paddr + माप(*trigger_tab),
		       (अचिन्हित दीर्घ दीर्घ)trigger_paddr + table_size - 1);
		जाओ out_rel_header;
	पूर्ण
	iounmap(trigger_tab);
	trigger_tab = ioremap_cache(trigger_paddr, table_size);
	अगर (!trigger_tab) अणु
		pr_err("Failed to map trigger table!\n");
		जाओ out_rel_entry;
	पूर्ण
	trigger_entry = (काष्ठा acpi_whea_header *)
		((अक्षर *)trigger_tab + माप(काष्ठा acpi_einj_trigger));
	apei_resources_init(&trigger_resources);
	apei_exec_ctx_init(&trigger_ctx, einj_ins_type,
			   ARRAY_SIZE(einj_ins_type),
			   trigger_entry, trigger_tab->entry_count);
	rc = apei_exec_collect_resources(&trigger_ctx, &trigger_resources);
	अगर (rc)
		जाओ out_fini;
	rc = apei_resources_sub(&trigger_resources, &einj_resources);
	अगर (rc)
		जाओ out_fini;
	/*
	 * Some firmware will access target address specअगरied in
	 * param1 to trigger the error when injecting memory error.
	 * This will cause resource conflict with regular memory.  So
	 * हटाओ it from trigger table resources.
	 */
	अगर ((param_extension || acpi5) && (type & MEM_ERROR_MASK) && param2) अणु
		काष्ठा apei_resources addr_resources;
		apei_resources_init(&addr_resources);
		trigger_param_region = einj_get_trigger_parameter_region(
			trigger_tab, param1, param2);
		अगर (trigger_param_region) अणु
			rc = apei_resources_add(&addr_resources,
				trigger_param_region->address,
				trigger_param_region->bit_width/8, true);
			अगर (rc)
				जाओ out_fini;
			rc = apei_resources_sub(&trigger_resources,
					&addr_resources);
		पूर्ण
		apei_resources_fini(&addr_resources);
		अगर (rc)
			जाओ out_fini;
	पूर्ण
	rc = apei_resources_request(&trigger_resources, "APEI EINJ Trigger");
	अगर (rc)
		जाओ out_fini;
	rc = apei_exec_pre_map_gars(&trigger_ctx);
	अगर (rc)
		जाओ out_release;

	rc = apei_exec_run(&trigger_ctx, ACPI_EINJ_TRIGGER_ERROR);

	apei_exec_post_unmap_gars(&trigger_ctx);
out_release:
	apei_resources_release(&trigger_resources);
out_fini:
	apei_resources_fini(&trigger_resources);
out_rel_entry:
	release_mem_region(trigger_paddr + माप(*trigger_tab),
			   table_size - माप(*trigger_tab));
out_rel_header:
	release_mem_region(trigger_paddr, माप(*trigger_tab));
out:
	अगर (trigger_tab)
		iounmap(trigger_tab);

	वापस rc;
पूर्ण

अटल पूर्णांक __einj_error_inject(u32 type, u32 flags, u64 param1, u64 param2,
			       u64 param3, u64 param4)
अणु
	काष्ठा apei_exec_context ctx;
	u64 val, trigger_paddr, समयout = FIRMWARE_TIMEOUT;
	पूर्णांक rc;

	einj_exec_ctx_init(&ctx);

	rc = apei_exec_run_optional(&ctx, ACPI_EINJ_BEGIN_OPERATION);
	अगर (rc)
		वापस rc;
	apei_exec_ctx_set_input(&ctx, type);
	अगर (acpi5) अणु
		काष्ठा set_error_type_with_address *v5param = einj_param;

		v5param->type = type;
		अगर (type & ACPI5_VENDOR_BIT) अणु
			चयन (venकरोr_flags) अणु
			हाल SETWA_FLAGS_APICID:
				v5param->apicid = param1;
				अवरोध;
			हाल SETWA_FLAGS_MEM:
				v5param->memory_address = param1;
				v5param->memory_address_range = param2;
				अवरोध;
			हाल SETWA_FLAGS_PCIE_SBDF:
				v5param->pcie_sbdf = param1;
				अवरोध;
			पूर्ण
			v5param->flags = venकरोr_flags;
		पूर्ण अन्यथा अगर (flags) अणु
				v5param->flags = flags;
				v5param->memory_address = param1;
				v5param->memory_address_range = param2;
				v5param->apicid = param3;
				v5param->pcie_sbdf = param4;
		पूर्ण अन्यथा अणु
			चयन (type) अणु
			हाल ACPI_EINJ_PROCESSOR_CORRECTABLE:
			हाल ACPI_EINJ_PROCESSOR_UNCORRECTABLE:
			हाल ACPI_EINJ_PROCESSOR_FATAL:
				v5param->apicid = param1;
				v5param->flags = SETWA_FLAGS_APICID;
				अवरोध;
			हाल ACPI_EINJ_MEMORY_CORRECTABLE:
			हाल ACPI_EINJ_MEMORY_UNCORRECTABLE:
			हाल ACPI_EINJ_MEMORY_FATAL:
				v5param->memory_address = param1;
				v5param->memory_address_range = param2;
				v5param->flags = SETWA_FLAGS_MEM;
				अवरोध;
			हाल ACPI_EINJ_PCIX_CORRECTABLE:
			हाल ACPI_EINJ_PCIX_UNCORRECTABLE:
			हाल ACPI_EINJ_PCIX_FATAL:
				v5param->pcie_sbdf = param1;
				v5param->flags = SETWA_FLAGS_PCIE_SBDF;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		rc = apei_exec_run(&ctx, ACPI_EINJ_SET_ERROR_TYPE);
		अगर (rc)
			वापस rc;
		अगर (einj_param) अणु
			काष्ठा einj_parameter *v4param = einj_param;
			v4param->param1 = param1;
			v4param->param2 = param2;
		पूर्ण
	पूर्ण
	rc = apei_exec_run(&ctx, ACPI_EINJ_EXECUTE_OPERATION);
	अगर (rc)
		वापस rc;
	क्रम (;;) अणु
		rc = apei_exec_run(&ctx, ACPI_EINJ_CHECK_BUSY_STATUS);
		अगर (rc)
			वापस rc;
		val = apei_exec_ctx_get_output(&ctx);
		अगर (!(val & EINJ_OP_BUSY))
			अवरोध;
		अगर (einj_समयकरोut(&समयout))
			वापस -EIO;
	पूर्ण
	rc = apei_exec_run(&ctx, ACPI_EINJ_GET_COMMAND_STATUS);
	अगर (rc)
		वापस rc;
	val = apei_exec_ctx_get_output(&ctx);
	अगर (val != EINJ_STATUS_SUCCESS)
		वापस -EBUSY;

	rc = apei_exec_run(&ctx, ACPI_EINJ_GET_TRIGGER_TABLE);
	अगर (rc)
		वापस rc;
	trigger_paddr = apei_exec_ctx_get_output(&ctx);
	अगर (notrigger == 0) अणु
		rc = __einj_error_trigger(trigger_paddr, type, param1, param2);
		अगर (rc)
			वापस rc;
	पूर्ण
	rc = apei_exec_run_optional(&ctx, ACPI_EINJ_END_OPERATION);

	वापस rc;
पूर्ण

/* Inject the specअगरied hardware error */
अटल पूर्णांक einj_error_inject(u32 type, u32 flags, u64 param1, u64 param2,
			     u64 param3, u64 param4)
अणु
	पूर्णांक rc;
	u64 base_addr, size;

	/* If user manually set "flags", make sure it is legal */
	अगर (flags && (flags &
		~(SETWA_FLAGS_APICID|SETWA_FLAGS_MEM|SETWA_FLAGS_PCIE_SBDF)))
		वापस -EINVAL;

	/*
	 * We need extra sanity checks क्रम memory errors.
	 * Other types leap directly to injection.
	 */

	/* ensure param1/param2 existed */
	अगर (!(param_extension || acpi5))
		जाओ inject;

	/* ensure injection is memory related */
	अगर (type & ACPI5_VENDOR_BIT) अणु
		अगर (venकरोr_flags != SETWA_FLAGS_MEM)
			जाओ inject;
	पूर्ण अन्यथा अगर (!(type & MEM_ERROR_MASK) && !(flags & SETWA_FLAGS_MEM))
		जाओ inject;

	/*
	 * Disallow crazy address masks that give BIOS leeway to pick
	 * injection address almost anywhere. Insist on page or
	 * better granularity and that target address is normal RAM or
	 * NVDIMM.
	 */
	base_addr = param1 & param2;
	size = ~param2 + 1;

	अगर (((param2 & PAGE_MASK) != PAGE_MASK) ||
	    ((region_पूर्णांकersects(base_addr, size, IORESOURCE_SYSTEM_RAM, IORES_DESC_NONE)
				!= REGION_INTERSECTS) &&
	     (region_पूर्णांकersects(base_addr, size, IORESOURCE_MEM, IORES_DESC_PERSISTENT_MEMORY)
				!= REGION_INTERSECTS)))
		वापस -EINVAL;

inject:
	mutex_lock(&einj_mutex);
	rc = __einj_error_inject(type, flags, param1, param2, param3, param4);
	mutex_unlock(&einj_mutex);

	वापस rc;
पूर्ण

अटल u32 error_type;
अटल u32 error_flags;
अटल u64 error_param1;
अटल u64 error_param2;
अटल u64 error_param3;
अटल u64 error_param4;
अटल काष्ठा dentry *einj_debug_dir;

अटल पूर्णांक available_error_type_show(काष्ठा seq_file *m, व्योम *v)
अणु
	पूर्णांक rc;
	u32 available_error_type = 0;

	rc = einj_get_available_error_type(&available_error_type);
	अगर (rc)
		वापस rc;
	अगर (available_error_type & 0x0001)
		seq_म_लिखो(m, "0x00000001\tProcessor Correctable\n");
	अगर (available_error_type & 0x0002)
		seq_म_लिखो(m, "0x00000002\tProcessor Uncorrectable non-fatal\n");
	अगर (available_error_type & 0x0004)
		seq_म_लिखो(m, "0x00000004\tProcessor Uncorrectable fatal\n");
	अगर (available_error_type & 0x0008)
		seq_म_लिखो(m, "0x00000008\tMemory Correctable\n");
	अगर (available_error_type & 0x0010)
		seq_म_लिखो(m, "0x00000010\tMemory Uncorrectable non-fatal\n");
	अगर (available_error_type & 0x0020)
		seq_म_लिखो(m, "0x00000020\tMemory Uncorrectable fatal\n");
	अगर (available_error_type & 0x0040)
		seq_म_लिखो(m, "0x00000040\tPCI Express Correctable\n");
	अगर (available_error_type & 0x0080)
		seq_म_लिखो(m, "0x00000080\tPCI Express Uncorrectable non-fatal\n");
	अगर (available_error_type & 0x0100)
		seq_म_लिखो(m, "0x00000100\tPCI Express Uncorrectable fatal\n");
	अगर (available_error_type & 0x0200)
		seq_म_लिखो(m, "0x00000200\tPlatform Correctable\n");
	अगर (available_error_type & 0x0400)
		seq_म_लिखो(m, "0x00000400\tPlatform Uncorrectable non-fatal\n");
	अगर (available_error_type & 0x0800)
		seq_म_लिखो(m, "0x00000800\tPlatform Uncorrectable fatal\n");

	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(available_error_type);

अटल पूर्णांक error_type_get(व्योम *data, u64 *val)
अणु
	*val = error_type;

	वापस 0;
पूर्ण

अटल पूर्णांक error_type_set(व्योम *data, u64 val)
अणु
	पूर्णांक rc;
	u32 available_error_type = 0;
	u32 tval, venकरोr;

	/*
	 * Venकरोr defined types have 0x80000000 bit set, and
	 * are not क्रमागतerated by ACPI_EINJ_GET_ERROR_TYPE
	 */
	venकरोr = val & ACPI5_VENDOR_BIT;
	tval = val & 0x7fffffff;

	/* Only one error type can be specअगरied */
	अगर (tval & (tval - 1))
		वापस -EINVAL;
	अगर (!venकरोr) अणु
		rc = einj_get_available_error_type(&available_error_type);
		अगर (rc)
			वापस rc;
		अगर (!(val & available_error_type))
			वापस -EINVAL;
	पूर्ण
	error_type = val;

	वापस 0;
पूर्ण

DEFINE_DEBUGFS_ATTRIBUTE(error_type_fops, error_type_get, error_type_set,
			 "0x%llx\n");

अटल पूर्णांक error_inject_set(व्योम *data, u64 val)
अणु
	अगर (!error_type)
		वापस -EINVAL;

	वापस einj_error_inject(error_type, error_flags, error_param1, error_param2,
		error_param3, error_param4);
पूर्ण

DEFINE_DEBUGFS_ATTRIBUTE(error_inject_fops, शून्य, error_inject_set, "%llu\n");

अटल पूर्णांक einj_check_table(काष्ठा acpi_table_einj *einj_tab)
अणु
	अगर ((einj_tab->header_length !=
	     (माप(काष्ठा acpi_table_einj) - माप(einj_tab->header)))
	    && (einj_tab->header_length != माप(काष्ठा acpi_table_einj)))
		वापस -EINVAL;
	अगर (einj_tab->header.length < माप(काष्ठा acpi_table_einj))
		वापस -EINVAL;
	अगर (einj_tab->entries !=
	    (einj_tab->header.length - माप(काष्ठा acpi_table_einj)) /
	    माप(काष्ठा acpi_einj_entry))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक __init einj_init(व्योम)
अणु
	पूर्णांक rc;
	acpi_status status;
	काष्ठा apei_exec_context ctx;

	अगर (acpi_disabled) अणु
		pr_warn("ACPI disabled.\n");
		वापस -ENODEV;
	पूर्ण

	status = acpi_get_table(ACPI_SIG_EINJ, 0,
				(काष्ठा acpi_table_header **)&einj_tab);
	अगर (status == AE_NOT_FOUND) अणु
		pr_warn("EINJ table not found.\n");
		वापस -ENODEV;
	पूर्ण
	अन्यथा अगर (ACPI_FAILURE(status)) अणु
		pr_err("Failed to get EINJ table: %s\n",
				acpi_क्रमmat_exception(status));
		वापस -EINVAL;
	पूर्ण

	rc = einj_check_table(einj_tab);
	अगर (rc) अणु
		pr_warn(FW_BUG "Invalid EINJ table.\n");
		जाओ err_put_table;
	पूर्ण

	rc = -ENOMEM;
	einj_debug_dir = debugfs_create_dir("einj", apei_get_debugfs_dir());

	debugfs_create_file("available_error_type", S_IRUSR, einj_debug_dir,
			    शून्य, &available_error_type_fops);
	debugfs_create_file_unsafe("error_type", 0600, einj_debug_dir,
				   शून्य, &error_type_fops);
	debugfs_create_file_unsafe("error_inject", 0200, einj_debug_dir,
				   शून्य, &error_inject_fops);

	apei_resources_init(&einj_resources);
	einj_exec_ctx_init(&ctx);
	rc = apei_exec_collect_resources(&ctx, &einj_resources);
	अगर (rc) अणु
		pr_err("Error collecting EINJ resources.\n");
		जाओ err_fini;
	पूर्ण

	rc = apei_resources_request(&einj_resources, "APEI EINJ");
	अगर (rc) अणु
		pr_err("Error requesting memory/port resources.\n");
		जाओ err_fini;
	पूर्ण

	rc = apei_exec_pre_map_gars(&ctx);
	अगर (rc) अणु
		pr_err("Error pre-mapping GARs.\n");
		जाओ err_release;
	पूर्ण

	einj_param = einj_get_parameter_address();
	अगर ((param_extension || acpi5) && einj_param) अणु
		debugfs_create_x32("flags", S_IRUSR | S_IWUSR, einj_debug_dir,
				   &error_flags);
		debugfs_create_x64("param1", S_IRUSR | S_IWUSR, einj_debug_dir,
				   &error_param1);
		debugfs_create_x64("param2", S_IRUSR | S_IWUSR, einj_debug_dir,
				   &error_param2);
		debugfs_create_x64("param3", S_IRUSR | S_IWUSR, einj_debug_dir,
				   &error_param3);
		debugfs_create_x64("param4", S_IRUSR | S_IWUSR, einj_debug_dir,
				   &error_param4);
		debugfs_create_x32("notrigger", S_IRUSR | S_IWUSR,
				   einj_debug_dir, &notrigger);
	पूर्ण

	अगर (venकरोr_dev[0]) अणु
		venकरोr_blob.data = venकरोr_dev;
		venकरोr_blob.size = म_माप(venकरोr_dev);
		debugfs_create_blob("vendor", S_IRUSR, einj_debug_dir,
				    &venकरोr_blob);
		debugfs_create_x32("vendor_flags", S_IRUSR | S_IWUSR,
				   einj_debug_dir, &venकरोr_flags);
	पूर्ण

	pr_info("Error INJection is initialized.\n");

	वापस 0;

err_release:
	apei_resources_release(&einj_resources);
err_fini:
	apei_resources_fini(&einj_resources);
	debugfs_हटाओ_recursive(einj_debug_dir);
err_put_table:
	acpi_put_table((काष्ठा acpi_table_header *)einj_tab);

	वापस rc;
पूर्ण

अटल व्योम __निकास einj_निकास(व्योम)
अणु
	काष्ठा apei_exec_context ctx;

	अगर (einj_param) अणु
		acpi_size size = (acpi5) ?
			माप(काष्ठा set_error_type_with_address) :
			माप(काष्ठा einj_parameter);

		acpi_os_unmap_iomem(einj_param, size);
	पूर्ण
	einj_exec_ctx_init(&ctx);
	apei_exec_post_unmap_gars(&ctx);
	apei_resources_release(&einj_resources);
	apei_resources_fini(&einj_resources);
	debugfs_हटाओ_recursive(einj_debug_dir);
	acpi_put_table((काष्ठा acpi_table_header *)einj_tab);
पूर्ण

module_init(einj_init);
module_निकास(einj_निकास);

MODULE_AUTHOR("Huang Ying");
MODULE_DESCRIPTION("APEI Error INJection support");
MODULE_LICENSE("GPL");
