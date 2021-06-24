<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * apei-base.c - ACPI Platक्रमm Error Interface (APEI) supporting
 * infraकाष्ठाure
 *
 * APEI allows to report errors (क्रम example from the chipset) to the
 * the operating प्रणाली. This improves NMI handling especially. In
 * addition it supports error serialization and error injection.
 *
 * For more inक्रमmation about APEI, please refer to ACPI Specअगरication
 * version 4.0, chapter 17.
 *
 * This file has Common functions used by more than one APEI table,
 * including framework of पूर्णांकerpreter क्रम ERST and EINJ; resource
 * management क्रम APEI रेजिस्टरs.
 *
 * Copyright (C) 2009, Intel Corp.
 *	Author: Huang Ying <ying.huang@पूर्णांकel.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/acpi.h>
#समावेश <linux/slab.h>
#समावेश <linux/पन.स>
#समावेश <linux/kref.h>
#समावेश <linux/rculist.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/debugfs.h>
#समावेश <यंत्र/unaligned.h>

#समावेश "apei-internal.h"

#घोषणा APEI_PFX "APEI: "

/*
 * APEI ERST (Error Record Serialization Table) and EINJ (Error
 * INJection) पूर्णांकerpreter framework.
 */

#घोषणा APEI_EXEC_PRESERVE_REGISTER	0x1

व्योम apei_exec_ctx_init(काष्ठा apei_exec_context *ctx,
			काष्ठा apei_exec_ins_type *ins_table,
			u32 inकाष्ठाions,
			काष्ठा acpi_whea_header *action_table,
			u32 entries)
अणु
	ctx->ins_table = ins_table;
	ctx->inकाष्ठाions = inकाष्ठाions;
	ctx->action_table = action_table;
	ctx->entries = entries;
पूर्ण
EXPORT_SYMBOL_GPL(apei_exec_ctx_init);

पूर्णांक __apei_exec_पढ़ो_रेजिस्टर(काष्ठा acpi_whea_header *entry, u64 *val)
अणु
	पूर्णांक rc;

	rc = apei_पढ़ो(val, &entry->रेजिस्टर_region);
	अगर (rc)
		वापस rc;
	*val >>= entry->रेजिस्टर_region.bit_offset;
	*val &= entry->mask;

	वापस 0;
पूर्ण

पूर्णांक apei_exec_पढ़ो_रेजिस्टर(काष्ठा apei_exec_context *ctx,
			    काष्ठा acpi_whea_header *entry)
अणु
	पूर्णांक rc;
	u64 val = 0;

	rc = __apei_exec_पढ़ो_रेजिस्टर(entry, &val);
	अगर (rc)
		वापस rc;
	ctx->value = val;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(apei_exec_पढ़ो_रेजिस्टर);

पूर्णांक apei_exec_पढ़ो_रेजिस्टर_value(काष्ठा apei_exec_context *ctx,
				  काष्ठा acpi_whea_header *entry)
अणु
	पूर्णांक rc;

	rc = apei_exec_पढ़ो_रेजिस्टर(ctx, entry);
	अगर (rc)
		वापस rc;
	ctx->value = (ctx->value == entry->value);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(apei_exec_पढ़ो_रेजिस्टर_value);

पूर्णांक __apei_exec_ग_लिखो_रेजिस्टर(काष्ठा acpi_whea_header *entry, u64 val)
अणु
	पूर्णांक rc;

	val &= entry->mask;
	val <<= entry->रेजिस्टर_region.bit_offset;
	अगर (entry->flags & APEI_EXEC_PRESERVE_REGISTER) अणु
		u64 valr = 0;
		rc = apei_पढ़ो(&valr, &entry->रेजिस्टर_region);
		अगर (rc)
			वापस rc;
		valr &= ~(entry->mask << entry->रेजिस्टर_region.bit_offset);
		val |= valr;
	पूर्ण
	rc = apei_ग_लिखो(val, &entry->रेजिस्टर_region);

	वापस rc;
पूर्ण

पूर्णांक apei_exec_ग_लिखो_रेजिस्टर(काष्ठा apei_exec_context *ctx,
			     काष्ठा acpi_whea_header *entry)
अणु
	वापस __apei_exec_ग_लिखो_रेजिस्टर(entry, ctx->value);
पूर्ण
EXPORT_SYMBOL_GPL(apei_exec_ग_लिखो_रेजिस्टर);

पूर्णांक apei_exec_ग_लिखो_रेजिस्टर_value(काष्ठा apei_exec_context *ctx,
				   काष्ठा acpi_whea_header *entry)
अणु
	पूर्णांक rc;

	ctx->value = entry->value;
	rc = apei_exec_ग_लिखो_रेजिस्टर(ctx, entry);

	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(apei_exec_ग_लिखो_रेजिस्टर_value);

पूर्णांक apei_exec_noop(काष्ठा apei_exec_context *ctx,
		   काष्ठा acpi_whea_header *entry)
अणु
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(apei_exec_noop);

/*
 * Interpret the specअगरied action. Go through whole action table,
 * execute all inकाष्ठाions beदीर्घ to the action.
 */
पूर्णांक __apei_exec_run(काष्ठा apei_exec_context *ctx, u8 action,
		    bool optional)
अणु
	पूर्णांक rc = -ENOENT;
	u32 i, ip;
	काष्ठा acpi_whea_header *entry;
	apei_exec_ins_func_t run;

	ctx->ip = 0;

	/*
	 * "ip" is the inकाष्ठाion poपूर्णांकer of current inकाष्ठाion,
	 * "ctx->ip" specअगरies the next inकाष्ठाion to executed,
	 * inकाष्ठाion "run" function may change the "ctx->ip" to
	 * implement "goto" semantics.
	 */
शुरुआत:
	ip = 0;
	क्रम (i = 0; i < ctx->entries; i++) अणु
		entry = &ctx->action_table[i];
		अगर (entry->action != action)
			जारी;
		अगर (ip == ctx->ip) अणु
			अगर (entry->inकाष्ठाion >= ctx->inकाष्ठाions ||
			    !ctx->ins_table[entry->inकाष्ठाion].run) अणु
				pr_warn(FW_WARN APEI_PFX
					"Invalid action table, unknown instruction type: %d\n",
					entry->inकाष्ठाion);
				वापस -EINVAL;
			पूर्ण
			run = ctx->ins_table[entry->inकाष्ठाion].run;
			rc = run(ctx, entry);
			अगर (rc < 0)
				वापस rc;
			अन्यथा अगर (rc != APEI_EXEC_SET_IP)
				ctx->ip++;
		पूर्ण
		ip++;
		अगर (ctx->ip < ip)
			जाओ शुरुआत;
	पूर्ण

	वापस !optional && rc < 0 ? rc : 0;
पूर्ण
EXPORT_SYMBOL_GPL(__apei_exec_run);

प्रकार पूर्णांक (*apei_exec_entry_func_t)(काष्ठा apei_exec_context *ctx,
				      काष्ठा acpi_whea_header *entry,
				      व्योम *data);

अटल पूर्णांक apei_exec_क्रम_each_entry(काष्ठा apei_exec_context *ctx,
				    apei_exec_entry_func_t func,
				    व्योम *data,
				    पूर्णांक *end)
अणु
	u8 ins;
	पूर्णांक i, rc;
	काष्ठा acpi_whea_header *entry;
	काष्ठा apei_exec_ins_type *ins_table = ctx->ins_table;

	क्रम (i = 0; i < ctx->entries; i++) अणु
		entry = ctx->action_table + i;
		ins = entry->inकाष्ठाion;
		अगर (end)
			*end = i;
		अगर (ins >= ctx->inकाष्ठाions || !ins_table[ins].run) अणु
			pr_warn(FW_WARN APEI_PFX
				"Invalid action table, unknown instruction type: %d\n",
				ins);
			वापस -EINVAL;
		पूर्ण
		rc = func(ctx, entry, data);
		अगर (rc)
			वापस rc;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक pre_map_gar_callback(काष्ठा apei_exec_context *ctx,
				काष्ठा acpi_whea_header *entry,
				व्योम *data)
अणु
	u8 ins = entry->inकाष्ठाion;

	अगर (ctx->ins_table[ins].flags & APEI_EXEC_INS_ACCESS_REGISTER)
		वापस apei_map_generic_address(&entry->रेजिस्टर_region);

	वापस 0;
पूर्ण

/*
 * Pre-map all GARs in action table to make it possible to access them
 * in NMI handler.
 */
पूर्णांक apei_exec_pre_map_gars(काष्ठा apei_exec_context *ctx)
अणु
	पूर्णांक rc, end;

	rc = apei_exec_क्रम_each_entry(ctx, pre_map_gar_callback,
				      शून्य, &end);
	अगर (rc) अणु
		काष्ठा apei_exec_context ctx_unmap;
		स_नकल(&ctx_unmap, ctx, माप(*ctx));
		ctx_unmap.entries = end;
		apei_exec_post_unmap_gars(&ctx_unmap);
	पूर्ण

	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(apei_exec_pre_map_gars);

अटल पूर्णांक post_unmap_gar_callback(काष्ठा apei_exec_context *ctx,
				   काष्ठा acpi_whea_header *entry,
				   व्योम *data)
अणु
	u8 ins = entry->inकाष्ठाion;

	अगर (ctx->ins_table[ins].flags & APEI_EXEC_INS_ACCESS_REGISTER)
		apei_unmap_generic_address(&entry->रेजिस्टर_region);

	वापस 0;
पूर्ण

/* Post-unmap all GAR in action table. */
पूर्णांक apei_exec_post_unmap_gars(काष्ठा apei_exec_context *ctx)
अणु
	वापस apei_exec_क्रम_each_entry(ctx, post_unmap_gar_callback,
					शून्य, शून्य);
पूर्ण
EXPORT_SYMBOL_GPL(apei_exec_post_unmap_gars);

/*
 * Resource management क्रम GARs in APEI
 */
काष्ठा apei_res अणु
	काष्ठा list_head list;
	अचिन्हित दीर्घ start;
	अचिन्हित दीर्घ end;
पूर्ण;

/* Collect all resources requested, to aव्योम conflict */
अटल काष्ठा apei_resources apei_resources_all = अणु
	.iomem = LIST_HEAD_INIT(apei_resources_all.iomem),
	.ioport = LIST_HEAD_INIT(apei_resources_all.ioport),
पूर्ण;

अटल पूर्णांक apei_res_add(काष्ठा list_head *res_list,
			अचिन्हित दीर्घ start, अचिन्हित दीर्घ size)
अणु
	काष्ठा apei_res *res, *resn, *res_ins = शून्य;
	अचिन्हित दीर्घ end = start + size;

	अगर (end <= start)
		वापस 0;
repeat:
	list_क्रम_each_entry_safe(res, resn, res_list, list) अणु
		अगर (res->start > end || res->end < start)
			जारी;
		अन्यथा अगर (end <= res->end && start >= res->start) अणु
			kमुक्त(res_ins);
			वापस 0;
		पूर्ण
		list_del(&res->list);
		res->start = start = min(res->start, start);
		res->end = end = max(res->end, end);
		kमुक्त(res_ins);
		res_ins = res;
		जाओ repeat;
	पूर्ण

	अगर (res_ins)
		list_add(&res_ins->list, res_list);
	अन्यथा अणु
		res_ins = kदो_स्मृति(माप(*res), GFP_KERNEL);
		अगर (!res_ins)
			वापस -ENOMEM;
		res_ins->start = start;
		res_ins->end = end;
		list_add(&res_ins->list, res_list);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक apei_res_sub(काष्ठा list_head *res_list1,
			काष्ठा list_head *res_list2)
अणु
	काष्ठा apei_res *res1, *resn1, *res2, *res;
	res1 = list_entry(res_list1->next, काष्ठा apei_res, list);
	resn1 = list_entry(res1->list.next, काष्ठा apei_res, list);
	जबतक (&res1->list != res_list1) अणु
		list_क्रम_each_entry(res2, res_list2, list) अणु
			अगर (res1->start >= res2->end ||
			    res1->end <= res2->start)
				जारी;
			अन्यथा अगर (res1->end <= res2->end &&
				 res1->start >= res2->start) अणु
				list_del(&res1->list);
				kमुक्त(res1);
				अवरोध;
			पूर्ण अन्यथा अगर (res1->end > res2->end &&
				   res1->start < res2->start) अणु
				res = kदो_स्मृति(माप(*res), GFP_KERNEL);
				अगर (!res)
					वापस -ENOMEM;
				res->start = res2->end;
				res->end = res1->end;
				res1->end = res2->start;
				list_add(&res->list, &res1->list);
				resn1 = res;
			पूर्ण अन्यथा अणु
				अगर (res1->start < res2->start)
					res1->end = res2->start;
				अन्यथा
					res1->start = res2->end;
			पूर्ण
		पूर्ण
		res1 = resn1;
		resn1 = list_entry(resn1->list.next, काष्ठा apei_res, list);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम apei_res_clean(काष्ठा list_head *res_list)
अणु
	काष्ठा apei_res *res, *resn;

	list_क्रम_each_entry_safe(res, resn, res_list, list) अणु
		list_del(&res->list);
		kमुक्त(res);
	पूर्ण
पूर्ण

व्योम apei_resources_fini(काष्ठा apei_resources *resources)
अणु
	apei_res_clean(&resources->iomem);
	apei_res_clean(&resources->ioport);
पूर्ण
EXPORT_SYMBOL_GPL(apei_resources_fini);

अटल पूर्णांक apei_resources_merge(काष्ठा apei_resources *resources1,
				काष्ठा apei_resources *resources2)
अणु
	पूर्णांक rc;
	काष्ठा apei_res *res;

	list_क्रम_each_entry(res, &resources2->iomem, list) अणु
		rc = apei_res_add(&resources1->iomem, res->start,
				  res->end - res->start);
		अगर (rc)
			वापस rc;
	पूर्ण
	list_क्रम_each_entry(res, &resources2->ioport, list) अणु
		rc = apei_res_add(&resources1->ioport, res->start,
				  res->end - res->start);
		अगर (rc)
			वापस rc;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक apei_resources_add(काष्ठा apei_resources *resources,
		       अचिन्हित दीर्घ start, अचिन्हित दीर्घ size,
		       bool iomem)
अणु
	अगर (iomem)
		वापस apei_res_add(&resources->iomem, start, size);
	अन्यथा
		वापस apei_res_add(&resources->ioport, start, size);
पूर्ण
EXPORT_SYMBOL_GPL(apei_resources_add);

/*
 * EINJ has two groups of GARs (EINJ table entry and trigger table
 * entry), so common resources are subtracted from the trigger table
 * resources beक्रमe the second requesting.
 */
पूर्णांक apei_resources_sub(काष्ठा apei_resources *resources1,
		       काष्ठा apei_resources *resources2)
अणु
	पूर्णांक rc;

	rc = apei_res_sub(&resources1->iomem, &resources2->iomem);
	अगर (rc)
		वापस rc;
	वापस apei_res_sub(&resources1->ioport, &resources2->ioport);
पूर्ण
EXPORT_SYMBOL_GPL(apei_resources_sub);

अटल पूर्णांक apei_get_res_callback(__u64 start, __u64 size, व्योम *data)
अणु
	काष्ठा apei_resources *resources = data;
	वापस apei_res_add(&resources->iomem, start, size);
पूर्ण

अटल पूर्णांक apei_get_nvs_resources(काष्ठा apei_resources *resources)
अणु
	वापस acpi_nvs_क्रम_each_region(apei_get_res_callback, resources);
पूर्ण

पूर्णांक (*arch_apei_filter_addr)(पूर्णांक (*func)(__u64 start, __u64 size,
				     व्योम *data), व्योम *data);
अटल पूर्णांक apei_get_arch_resources(काष्ठा apei_resources *resources)

अणु
	वापस arch_apei_filter_addr(apei_get_res_callback, resources);
पूर्ण

/*
 * IO memory/port resource management mechanism is used to check
 * whether memory/port area used by GARs conflicts with normal memory
 * or IO memory/port of devices.
 */
पूर्णांक apei_resources_request(काष्ठा apei_resources *resources,
			   स्थिर अक्षर *desc)
अणु
	काष्ठा apei_res *res, *res_bak = शून्य;
	काष्ठा resource *r;
	काष्ठा apei_resources nvs_resources, arch_res;
	पूर्णांक rc;

	rc = apei_resources_sub(resources, &apei_resources_all);
	अगर (rc)
		वापस rc;

	/*
	 * Some firmware uses ACPI NVS region, that has been marked as
	 * busy, so exclude it from APEI resources to aव्योम false
	 * conflict.
	 */
	apei_resources_init(&nvs_resources);
	rc = apei_get_nvs_resources(&nvs_resources);
	अगर (rc)
		जाओ nvs_res_fini;
	rc = apei_resources_sub(resources, &nvs_resources);
	अगर (rc)
		जाओ nvs_res_fini;

	अगर (arch_apei_filter_addr) अणु
		apei_resources_init(&arch_res);
		rc = apei_get_arch_resources(&arch_res);
		अगर (rc)
			जाओ arch_res_fini;
		rc = apei_resources_sub(resources, &arch_res);
		अगर (rc)
			जाओ arch_res_fini;
	पूर्ण

	rc = -EINVAL;
	list_क्रम_each_entry(res, &resources->iomem, list) अणु
		r = request_mem_region(res->start, res->end - res->start,
				       desc);
		अगर (!r) अणु
			pr_err(APEI_PFX
		"Can not request [mem %#010llx-%#010llx] for %s registers\n",
			       (अचिन्हित दीर्घ दीर्घ)res->start,
			       (अचिन्हित दीर्घ दीर्घ)res->end - 1, desc);
			res_bak = res;
			जाओ err_unmap_iomem;
		पूर्ण
	पूर्ण

	list_क्रम_each_entry(res, &resources->ioport, list) अणु
		r = request_region(res->start, res->end - res->start, desc);
		अगर (!r) अणु
			pr_err(APEI_PFX
		"Can not request [io  %#06llx-%#06llx] for %s registers\n",
			       (अचिन्हित दीर्घ दीर्घ)res->start,
			       (अचिन्हित दीर्घ दीर्घ)res->end - 1, desc);
			res_bak = res;
			जाओ err_unmap_ioport;
		पूर्ण
	पूर्ण

	rc = apei_resources_merge(&apei_resources_all, resources);
	अगर (rc) अणु
		pr_err(APEI_PFX "Fail to merge resources!\n");
		जाओ err_unmap_ioport;
	पूर्ण

	जाओ arch_res_fini;

err_unmap_ioport:
	list_क्रम_each_entry(res, &resources->ioport, list) अणु
		अगर (res == res_bak)
			अवरोध;
		release_region(res->start, res->end - res->start);
	पूर्ण
	res_bak = शून्य;
err_unmap_iomem:
	list_क्रम_each_entry(res, &resources->iomem, list) अणु
		अगर (res == res_bak)
			अवरोध;
		release_mem_region(res->start, res->end - res->start);
	पूर्ण
arch_res_fini:
	अगर (arch_apei_filter_addr)
		apei_resources_fini(&arch_res);
nvs_res_fini:
	apei_resources_fini(&nvs_resources);
	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(apei_resources_request);

व्योम apei_resources_release(काष्ठा apei_resources *resources)
अणु
	पूर्णांक rc;
	काष्ठा apei_res *res;

	list_क्रम_each_entry(res, &resources->iomem, list)
		release_mem_region(res->start, res->end - res->start);
	list_क्रम_each_entry(res, &resources->ioport, list)
		release_region(res->start, res->end - res->start);

	rc = apei_resources_sub(&apei_resources_all, resources);
	अगर (rc)
		pr_err(APEI_PFX "Fail to sub resources!\n");
पूर्ण
EXPORT_SYMBOL_GPL(apei_resources_release);

अटल पूर्णांक apei_check_gar(काष्ठा acpi_generic_address *reg, u64 *paddr,
				u32 *access_bit_width)
अणु
	u32 bit_width, bit_offset, access_size_code, space_id;

	bit_width = reg->bit_width;
	bit_offset = reg->bit_offset;
	access_size_code = reg->access_width;
	space_id = reg->space_id;
	*paddr = get_unaligned(&reg->address);
	अगर (!*paddr) अणु
		pr_warn(FW_BUG APEI_PFX
			"Invalid physical address in GAR [0x%llx/%u/%u/%u/%u]\n",
			*paddr, bit_width, bit_offset, access_size_code,
			space_id);
		वापस -EINVAL;
	पूर्ण

	अगर (access_size_code < 1 || access_size_code > 4) अणु
		pr_warn(FW_BUG APEI_PFX
			"Invalid access size code in GAR [0x%llx/%u/%u/%u/%u]\n",
			*paddr, bit_width, bit_offset, access_size_code,
			space_id);
		वापस -EINVAL;
	पूर्ण
	*access_bit_width = 1UL << (access_size_code + 2);

	/* Fixup common BIOS bug */
	अगर (bit_width == 32 && bit_offset == 0 && (*paddr & 0x03) == 0 &&
	    *access_bit_width < 32)
		*access_bit_width = 32;
	अन्यथा अगर (bit_width == 64 && bit_offset == 0 && (*paddr & 0x07) == 0 &&
	    *access_bit_width < 64)
		*access_bit_width = 64;

	अगर ((bit_width + bit_offset) > *access_bit_width) अणु
		pr_warn(FW_BUG APEI_PFX
			"Invalid bit width + offset in GAR [0x%llx/%u/%u/%u/%u]\n",
			*paddr, bit_width, bit_offset, access_size_code,
			space_id);
		वापस -EINVAL;
	पूर्ण

	अगर (space_id != ACPI_ADR_SPACE_SYSTEM_MEMORY &&
	    space_id != ACPI_ADR_SPACE_SYSTEM_IO) अणु
		pr_warn(FW_BUG APEI_PFX
			"Invalid address space type in GAR [0x%llx/%u/%u/%u/%u]\n",
			*paddr, bit_width, bit_offset, access_size_code,
			space_id);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक apei_map_generic_address(काष्ठा acpi_generic_address *reg)
अणु
	पूर्णांक rc;
	u32 access_bit_width;
	u64 address;

	rc = apei_check_gar(reg, &address, &access_bit_width);
	अगर (rc)
		वापस rc;

	/* IO space करोesn't need mapping */
	अगर (reg->space_id == ACPI_ADR_SPACE_SYSTEM_IO)
		वापस 0;

	अगर (!acpi_os_map_generic_address(reg))
		वापस -ENXIO;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(apei_map_generic_address);

/* पढ़ो GAR in पूर्णांकerrupt (including NMI) or process context */
पूर्णांक apei_पढ़ो(u64 *val, काष्ठा acpi_generic_address *reg)
अणु
	पूर्णांक rc;
	u32 access_bit_width;
	u64 address;
	acpi_status status;

	rc = apei_check_gar(reg, &address, &access_bit_width);
	अगर (rc)
		वापस rc;

	*val = 0;
	चयन(reg->space_id) अणु
	हाल ACPI_ADR_SPACE_SYSTEM_MEMORY:
		status = acpi_os_पढ़ो_memory((acpi_physical_address) address,
					       val, access_bit_width);
		अगर (ACPI_FAILURE(status))
			वापस -EIO;
		अवरोध;
	हाल ACPI_ADR_SPACE_SYSTEM_IO:
		status = acpi_os_पढ़ो_port(address, (u32 *)val,
					   access_bit_width);
		अगर (ACPI_FAILURE(status))
			वापस -EIO;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(apei_पढ़ो);

/* ग_लिखो GAR in पूर्णांकerrupt (including NMI) or process context */
पूर्णांक apei_ग_लिखो(u64 val, काष्ठा acpi_generic_address *reg)
अणु
	पूर्णांक rc;
	u32 access_bit_width;
	u64 address;
	acpi_status status;

	rc = apei_check_gar(reg, &address, &access_bit_width);
	अगर (rc)
		वापस rc;

	चयन (reg->space_id) अणु
	हाल ACPI_ADR_SPACE_SYSTEM_MEMORY:
		status = acpi_os_ग_लिखो_memory((acpi_physical_address) address,
						val, access_bit_width);
		अगर (ACPI_FAILURE(status))
			वापस -EIO;
		अवरोध;
	हाल ACPI_ADR_SPACE_SYSTEM_IO:
		status = acpi_os_ग_लिखो_port(address, val, access_bit_width);
		अगर (ACPI_FAILURE(status))
			वापस -EIO;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(apei_ग_लिखो);

अटल पूर्णांक collect_res_callback(काष्ठा apei_exec_context *ctx,
				काष्ठा acpi_whea_header *entry,
				व्योम *data)
अणु
	काष्ठा apei_resources *resources = data;
	काष्ठा acpi_generic_address *reg = &entry->रेजिस्टर_region;
	u8 ins = entry->inकाष्ठाion;
	u32 access_bit_width;
	u64 paddr;
	पूर्णांक rc;

	अगर (!(ctx->ins_table[ins].flags & APEI_EXEC_INS_ACCESS_REGISTER))
		वापस 0;

	rc = apei_check_gar(reg, &paddr, &access_bit_width);
	अगर (rc)
		वापस rc;

	चयन (reg->space_id) अणु
	हाल ACPI_ADR_SPACE_SYSTEM_MEMORY:
		वापस apei_res_add(&resources->iomem, paddr,
				    access_bit_width / 8);
	हाल ACPI_ADR_SPACE_SYSTEM_IO:
		वापस apei_res_add(&resources->ioport, paddr,
				    access_bit_width / 8);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

/*
 * Same रेजिस्टर may be used by multiple inकाष्ठाions in GARs, so
 * resources are collected beक्रमe requesting.
 */
पूर्णांक apei_exec_collect_resources(काष्ठा apei_exec_context *ctx,
				काष्ठा apei_resources *resources)
अणु
	वापस apei_exec_क्रम_each_entry(ctx, collect_res_callback,
					resources, शून्य);
पूर्ण
EXPORT_SYMBOL_GPL(apei_exec_collect_resources);

काष्ठा dentry *apei_get_debugfs_dir(व्योम)
अणु
	अटल काष्ठा dentry *dapei;

	अगर (!dapei)
		dapei = debugfs_create_dir("apei", शून्य);

	वापस dapei;
पूर्ण
EXPORT_SYMBOL_GPL(apei_get_debugfs_dir);

पूर्णांक __weak arch_apei_enable_cmcff(काष्ठा acpi_hest_header *hest_hdr,
				  व्योम *data)
अणु
	वापस 1;
पूर्ण
EXPORT_SYMBOL_GPL(arch_apei_enable_cmcff);

व्योम __weak arch_apei_report_mem_error(पूर्णांक sev,
				       काष्ठा cper_sec_mem_err *mem_err)
अणु
पूर्ण
EXPORT_SYMBOL_GPL(arch_apei_report_mem_error);

पूर्णांक apei_osc_setup(व्योम)
अणु
	अटल u8 whea_uuid_str[] = "ed855e0c-6c90-47bf-a62a-26de0fc5ad5c";
	acpi_handle handle;
	u32 capbuf[3];
	काष्ठा acpi_osc_context context = अणु
		.uuid_str	= whea_uuid_str,
		.rev		= 1,
		.cap.length	= माप(capbuf),
		.cap.poपूर्णांकer	= capbuf,
	पूर्ण;

	capbuf[OSC_QUERY_DWORD] = OSC_QUERY_ENABLE;
	capbuf[OSC_SUPPORT_DWORD] = 1;
	capbuf[OSC_CONTROL_DWORD] = 0;

	अगर (ACPI_FAILURE(acpi_get_handle(शून्य, "\\_SB", &handle))
	    || ACPI_FAILURE(acpi_run_osc(handle, &context)))
		वापस -EIO;
	अन्यथा अणु
		kमुक्त(context.ret.poपूर्णांकer);
		वापस 0;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(apei_osc_setup);
