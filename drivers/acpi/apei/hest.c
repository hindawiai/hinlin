<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * APEI Hardware Error Source Table support
 *
 * HEST describes error sources in detail; communicates operational
 * parameters (i.e. severity levels, masking bits, and threshold
 * values) to Linux as necessary. It also allows the BIOS to report
 * non-standard error sources to Linux (क्रम example, chipset-specअगरic
 * error रेजिस्टरs).
 *
 * For more inक्रमmation about HEST, please refer to ACPI Specअगरication
 * version 4.0, section 17.3.2.
 *
 * Copyright 2009 Intel Corp.
 *   Author: Huang Ying <ying.huang@पूर्णांकel.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/acpi.h>
#समावेश <linux/kdebug.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/पन.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश <acpi/apei.h>
#समावेश <acpi/ghes.h>

#समावेश "apei-internal.h"

#घोषणा HEST_PFX "HEST: "

पूर्णांक hest_disable;
EXPORT_SYMBOL_GPL(hest_disable);

/* HEST table parsing */

अटल काष्ठा acpi_table_hest *__पढ़ो_mostly hest_tab;

अटल स्थिर पूर्णांक hest_esrc_len_tab[ACPI_HEST_TYPE_RESERVED] = अणु
	[ACPI_HEST_TYPE_IA32_CHECK] = -1,	/* need further calculation */
	[ACPI_HEST_TYPE_IA32_CORRECTED_CHECK] = -1,
	[ACPI_HEST_TYPE_IA32_NMI] = माप(काष्ठा acpi_hest_ia_nmi),
	[ACPI_HEST_TYPE_AER_ROOT_PORT] = माप(काष्ठा acpi_hest_aer_root),
	[ACPI_HEST_TYPE_AER_ENDPOINT] = माप(काष्ठा acpi_hest_aer),
	[ACPI_HEST_TYPE_AER_BRIDGE] = माप(काष्ठा acpi_hest_aer_bridge),
	[ACPI_HEST_TYPE_GENERIC_ERROR] = माप(काष्ठा acpi_hest_generic),
	[ACPI_HEST_TYPE_GENERIC_ERROR_V2] = माप(काष्ठा acpi_hest_generic_v2),
	[ACPI_HEST_TYPE_IA32_DEFERRED_CHECK] = -1,
पूर्ण;

अटल अंतरभूत bool is_generic_error(काष्ठा acpi_hest_header *hest_hdr)
अणु
	वापस hest_hdr->type == ACPI_HEST_TYPE_GENERIC_ERROR ||
	       hest_hdr->type == ACPI_HEST_TYPE_GENERIC_ERROR_V2;
पूर्ण

अटल पूर्णांक hest_esrc_len(काष्ठा acpi_hest_header *hest_hdr)
अणु
	u16 hest_type = hest_hdr->type;
	पूर्णांक len;

	अगर (hest_type >= ACPI_HEST_TYPE_RESERVED)
		वापस 0;

	len = hest_esrc_len_tab[hest_type];

	अगर (hest_type == ACPI_HEST_TYPE_IA32_CORRECTED_CHECK) अणु
		काष्ठा acpi_hest_ia_corrected *cmc;
		cmc = (काष्ठा acpi_hest_ia_corrected *)hest_hdr;
		len = माप(*cmc) + cmc->num_hardware_banks *
			माप(काष्ठा acpi_hest_ia_error_bank);
	पूर्ण अन्यथा अगर (hest_type == ACPI_HEST_TYPE_IA32_CHECK) अणु
		काष्ठा acpi_hest_ia_machine_check *mc;
		mc = (काष्ठा acpi_hest_ia_machine_check *)hest_hdr;
		len = माप(*mc) + mc->num_hardware_banks *
			माप(काष्ठा acpi_hest_ia_error_bank);
	पूर्ण अन्यथा अगर (hest_type == ACPI_HEST_TYPE_IA32_DEFERRED_CHECK) अणु
		काष्ठा acpi_hest_ia_deferred_check *mc;
		mc = (काष्ठा acpi_hest_ia_deferred_check *)hest_hdr;
		len = माप(*mc) + mc->num_hardware_banks *
			माप(काष्ठा acpi_hest_ia_error_bank);
	पूर्ण
	BUG_ON(len == -1);

	वापस len;
पूर्ण;

पूर्णांक apei_hest_parse(apei_hest_func_t func, व्योम *data)
अणु
	काष्ठा acpi_hest_header *hest_hdr;
	पूर्णांक i, rc, len;

	अगर (hest_disable || !hest_tab)
		वापस -EINVAL;

	hest_hdr = (काष्ठा acpi_hest_header *)(hest_tab + 1);
	क्रम (i = 0; i < hest_tab->error_source_count; i++) अणु
		len = hest_esrc_len(hest_hdr);
		अगर (!len) अणु
			pr_warn(FW_WARN HEST_PFX
				"Unknown or unused hardware error source "
				"type: %d for hardware error source: %d.\n",
				hest_hdr->type, hest_hdr->source_id);
			वापस -EINVAL;
		पूर्ण
		अगर ((व्योम *)hest_hdr + len >
		    (व्योम *)hest_tab + hest_tab->header.length) अणु
			pr_warn(FW_BUG HEST_PFX
		"Table contents overflow for hardware error source: %d.\n",
				hest_hdr->source_id);
			वापस -EINVAL;
		पूर्ण

		rc = func(hest_hdr, data);
		अगर (rc)
			वापस rc;

		hest_hdr = (व्योम *)hest_hdr + len;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(apei_hest_parse);

/*
 * Check अगर firmware advertises firmware first mode. We need FF bit to be set
 * aदीर्घ with a set of MC banks which work in FF mode.
 */
अटल पूर्णांक __init hest_parse_cmc(काष्ठा acpi_hest_header *hest_hdr, व्योम *data)
अणु
	अगर (hest_hdr->type != ACPI_HEST_TYPE_IA32_CORRECTED_CHECK)
		वापस 0;

	अगर (!acpi_disable_cmcff)
		वापस !arch_apei_enable_cmcff(hest_hdr, data);

	वापस 0;
पूर्ण

काष्ठा ghes_arr अणु
	काष्ठा platक्रमm_device **ghes_devs;
	अचिन्हित पूर्णांक count;
पूर्ण;

अटल पूर्णांक __init hest_parse_ghes_count(काष्ठा acpi_hest_header *hest_hdr, व्योम *data)
अणु
	पूर्णांक *count = data;

	अगर (is_generic_error(hest_hdr))
		(*count)++;
	वापस 0;
पूर्ण

अटल पूर्णांक __init hest_parse_ghes(काष्ठा acpi_hest_header *hest_hdr, व्योम *data)
अणु
	काष्ठा platक्रमm_device *ghes_dev;
	काष्ठा ghes_arr *ghes_arr = data;
	पूर्णांक rc, i;

	अगर (!is_generic_error(hest_hdr))
		वापस 0;

	अगर (!((काष्ठा acpi_hest_generic *)hest_hdr)->enabled)
		वापस 0;
	क्रम (i = 0; i < ghes_arr->count; i++) अणु
		काष्ठा acpi_hest_header *hdr;
		ghes_dev = ghes_arr->ghes_devs[i];
		hdr = *(काष्ठा acpi_hest_header **)ghes_dev->dev.platक्रमm_data;
		अगर (hdr->source_id == hest_hdr->source_id) अणु
			pr_warn(FW_WARN HEST_PFX "Duplicated hardware error source ID: %d.\n",
				hdr->source_id);
			वापस -EIO;
		पूर्ण
	पूर्ण
	ghes_dev = platक्रमm_device_alloc("GHES", hest_hdr->source_id);
	अगर (!ghes_dev)
		वापस -ENOMEM;

	rc = platक्रमm_device_add_data(ghes_dev, &hest_hdr, माप(व्योम *));
	अगर (rc)
		जाओ err;

	rc = platक्रमm_device_add(ghes_dev);
	अगर (rc)
		जाओ err;
	ghes_arr->ghes_devs[ghes_arr->count++] = ghes_dev;

	वापस 0;
err:
	platक्रमm_device_put(ghes_dev);
	वापस rc;
पूर्ण

अटल पूर्णांक __init hest_ghes_dev_रेजिस्टर(अचिन्हित पूर्णांक ghes_count)
अणु
	पूर्णांक rc, i;
	काष्ठा ghes_arr ghes_arr;

	ghes_arr.count = 0;
	ghes_arr.ghes_devs = kदो_स्मृति_array(ghes_count, माप(व्योम *),
					   GFP_KERNEL);
	अगर (!ghes_arr.ghes_devs)
		वापस -ENOMEM;

	rc = apei_hest_parse(hest_parse_ghes, &ghes_arr);
	अगर (rc)
		जाओ err;

	rc = ghes_estatus_pool_init(ghes_count);
	अगर (rc)
		जाओ err;

out:
	kमुक्त(ghes_arr.ghes_devs);
	वापस rc;
err:
	क्रम (i = 0; i < ghes_arr.count; i++)
		platक्रमm_device_unरेजिस्टर(ghes_arr.ghes_devs[i]);
	जाओ out;
पूर्ण

अटल पूर्णांक __init setup_hest_disable(अक्षर *str)
अणु
	hest_disable = HEST_DISABLED;
	वापस 0;
पूर्ण

__setup("hest_disable", setup_hest_disable);

व्योम __init acpi_hest_init(व्योम)
अणु
	acpi_status status;
	पूर्णांक rc;
	अचिन्हित पूर्णांक ghes_count = 0;

	अगर (hest_disable) अणु
		pr_info(HEST_PFX "Table parsing disabled.\n");
		वापस;
	पूर्ण

	status = acpi_get_table(ACPI_SIG_HEST, 0,
				(काष्ठा acpi_table_header **)&hest_tab);
	अगर (status == AE_NOT_FOUND) अणु
		hest_disable = HEST_NOT_FOUND;
		वापस;
	पूर्ण अन्यथा अगर (ACPI_FAILURE(status)) अणु
		स्थिर अक्षर *msg = acpi_क्रमmat_exception(status);
		pr_err(HEST_PFX "Failed to get table, %s\n", msg);
		hest_disable = HEST_DISABLED;
		वापस;
	पूर्ण

	rc = apei_hest_parse(hest_parse_cmc, शून्य);
	अगर (rc)
		जाओ err;

	अगर (!ghes_disable) अणु
		rc = apei_hest_parse(hest_parse_ghes_count, &ghes_count);
		अगर (rc)
			जाओ err;

		अगर (ghes_count)
			rc = hest_ghes_dev_रेजिस्टर(ghes_count);
		अगर (rc)
			जाओ err;
	पूर्ण

	pr_info(HEST_PFX "Table parsing has been initialized.\n");
	वापस;
err:
	hest_disable = HEST_DISABLED;
	acpi_put_table((काष्ठा acpi_table_header *)hest_tab);
पूर्ण
