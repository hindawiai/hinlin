<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * APEI Boot Error Record Table (BERT) support
 *
 * Copyright 2011 Intel Corp.
 *   Author: Huang Ying <ying.huang@पूर्णांकel.com>
 *
 * Under normal circumstances, when a hardware error occurs, the error
 * handler receives control and processes the error. This gives OSPM a
 * chance to process the error condition, report it, and optionally attempt
 * recovery. In some हालs, the प्रणाली is unable to process an error.
 * For example, प्रणाली firmware or a management controller may choose to
 * reset the प्रणाली or the प्रणाली might experience an uncontrolled crash
 * or reset.The boot error source is used to report unhandled errors that
 * occurred in a previous boot. This mechanism is described in the BERT
 * table.
 *
 * For more inक्रमmation about BERT, please refer to ACPI Specअगरication
 * version 4.0, section 17.3.1
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/acpi.h>
#समावेश <linux/पन.स>

#समावेश "apei-internal.h"

#अघोषित pr_fmt
#घोषणा pr_fmt(fmt) "BERT: " fmt

अटल पूर्णांक bert_disable;

अटल व्योम __init bert_prपूर्णांक_all(काष्ठा acpi_bert_region *region,
				  अचिन्हित पूर्णांक region_len)
अणु
	काष्ठा acpi_hest_generic_status *estatus =
		(काष्ठा acpi_hest_generic_status *)region;
	पूर्णांक reमुख्य = region_len;
	u32 estatus_len;

	जबतक (reमुख्य >= माप(काष्ठा acpi_bert_region)) अणु
		estatus_len = cper_estatus_len(estatus);
		अगर (reमुख्य < estatus_len) अणु
			pr_err(FW_BUG "Truncated status block (length: %u).\n",
			       estatus_len);
			वापस;
		पूर्ण

		/* No more error records. */
		अगर (!estatus->block_status)
			वापस;

		अगर (cper_estatus_check(estatus)) अणु
			pr_err(FW_BUG "Invalid error record.\n");
			वापस;
		पूर्ण

		pr_info_once("Error records from previous boot:\n");

		cper_estatus_prपूर्णांक(KERN_INFO HW_ERR, estatus);

		/*
		 * Because the boot error source is "one-time polled" type,
		 * clear Block Status of current Generic Error Status Block,
		 * once it's prपूर्णांकed.
		 */
		estatus->block_status = 0;

		estatus = (व्योम *)estatus + estatus_len;
		reमुख्य -= estatus_len;
	पूर्ण
पूर्ण

अटल पूर्णांक __init setup_bert_disable(अक्षर *str)
अणु
	bert_disable = 1;

	वापस 0;
पूर्ण
__setup("bert_disable", setup_bert_disable);

अटल पूर्णांक __init bert_check_table(काष्ठा acpi_table_bert *bert_tab)
अणु
	अगर (bert_tab->header.length < माप(काष्ठा acpi_table_bert) ||
	    bert_tab->region_length < माप(काष्ठा acpi_bert_region))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक __init bert_init(व्योम)
अणु
	काष्ठा apei_resources bert_resources;
	काष्ठा acpi_bert_region *boot_error_region;
	काष्ठा acpi_table_bert *bert_tab;
	अचिन्हित पूर्णांक region_len;
	acpi_status status;
	पूर्णांक rc = 0;

	अगर (acpi_disabled)
		वापस 0;

	अगर (bert_disable) अणु
		pr_info("Boot Error Record Table support is disabled.\n");
		वापस 0;
	पूर्ण

	status = acpi_get_table(ACPI_SIG_BERT, 0, (काष्ठा acpi_table_header **)&bert_tab);
	अगर (status == AE_NOT_FOUND)
		वापस 0;

	अगर (ACPI_FAILURE(status)) अणु
		pr_err("get table failed, %s.\n", acpi_क्रमmat_exception(status));
		वापस -EINVAL;
	पूर्ण

	rc = bert_check_table(bert_tab);
	अगर (rc) अणु
		pr_err(FW_BUG "table invalid.\n");
		जाओ out_put_bert_tab;
	पूर्ण

	region_len = bert_tab->region_length;
	apei_resources_init(&bert_resources);
	rc = apei_resources_add(&bert_resources, bert_tab->address,
				region_len, true);
	अगर (rc)
		जाओ out_put_bert_tab;
	rc = apei_resources_request(&bert_resources, "APEI BERT");
	अगर (rc)
		जाओ out_fini;
	boot_error_region = ioremap_cache(bert_tab->address, region_len);
	अगर (boot_error_region) अणु
		bert_prपूर्णांक_all(boot_error_region, region_len);
		iounmap(boot_error_region);
	पूर्ण अन्यथा अणु
		rc = -ENOMEM;
	पूर्ण

	apei_resources_release(&bert_resources);
out_fini:
	apei_resources_fini(&bert_resources);
out_put_bert_tab:
	acpi_put_table((काष्ठा acpi_table_header *)bert_tab);

	वापस rc;
पूर्ण

late_initcall(bert_init);
