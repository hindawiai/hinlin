<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2017 Google, Inc.
 *     Thiebaud Weksteen <tweek@google.com>
 */

#घोषणा TPM_MEMREMAP(start, size) early_memremap(start, size)
#घोषणा TPM_MEMUNMAP(start, size) early_memunmap(start, size)

#समावेश <यंत्र/early_ioremap.h>
#समावेश <linux/efi.h>
#समावेश <linux/init.h>
#समावेश <linux/memblock.h>
#समावेश <linux/tpm_eventlog.h>

पूर्णांक efi_tpm_final_log_size;
EXPORT_SYMBOL(efi_tpm_final_log_size);

अटल पूर्णांक __init tpm2_calc_event_log_size(व्योम *data, पूर्णांक count, व्योम *size_info)
अणु
	काष्ठा tcg_pcr_event2_head *header;
	पूर्णांक event_size, size = 0;

	जबतक (count > 0) अणु
		header = data + size;
		event_size = __calc_tpm2_event_size(header, size_info, true);
		अगर (event_size == 0)
			वापस -1;
		size += event_size;
		count--;
	पूर्ण

	वापस size;
पूर्ण

/*
 * Reserve the memory associated with the TPM Event Log configuration table.
 */
पूर्णांक __init efi_tpm_eventlog_init(व्योम)
अणु
	काष्ठा linux_efi_tpm_eventlog *log_tbl;
	काष्ठा efi_tcg2_final_events_table *final_tbl;
	पूर्णांक tbl_size;
	पूर्णांक ret = 0;

	अगर (efi.tpm_log == EFI_INVALID_TABLE_ADDR) अणु
		/*
		 * We can't calculate the size of the final events without the
		 * first entry in the TPM log, so bail here.
		 */
		वापस 0;
	पूर्ण

	log_tbl = early_memremap(efi.tpm_log, माप(*log_tbl));
	अगर (!log_tbl) अणु
		pr_err("Failed to map TPM Event Log table @ 0x%lx\n",
		       efi.tpm_log);
		efi.tpm_log = EFI_INVALID_TABLE_ADDR;
		वापस -ENOMEM;
	पूर्ण

	tbl_size = माप(*log_tbl) + log_tbl->size;
	memblock_reserve(efi.tpm_log, tbl_size);

	अगर (efi.tpm_final_log == EFI_INVALID_TABLE_ADDR ||
	    log_tbl->version != EFI_TCG2_EVENT_LOG_FORMAT_TCG_2) अणु
		pr_warn(FW_BUG "TPM Final Events table missing or invalid\n");
		जाओ out;
	पूर्ण

	final_tbl = early_memremap(efi.tpm_final_log, माप(*final_tbl));

	अगर (!final_tbl) अणु
		pr_err("Failed to map TPM Final Event Log table @ 0x%lx\n",
		       efi.tpm_final_log);
		efi.tpm_final_log = EFI_INVALID_TABLE_ADDR;
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	tbl_size = 0;
	अगर (final_tbl->nr_events != 0) अणु
		व्योम *events = (व्योम *)efi.tpm_final_log
				+ माप(final_tbl->version)
				+ माप(final_tbl->nr_events);

		tbl_size = tpm2_calc_event_log_size(events,
						    final_tbl->nr_events,
						    log_tbl->log);
	पूर्ण

	अगर (tbl_size < 0) अणु
		pr_err(FW_BUG "Failed to parse event in TPM Final Events Log\n");
		ret = -EINVAL;
		जाओ out_calc;
	पूर्ण

	memblock_reserve((अचिन्हित दीर्घ)final_tbl,
			 tbl_size + माप(*final_tbl));
	efi_tpm_final_log_size = tbl_size;

out_calc:
	early_memunmap(final_tbl, माप(*final_tbl));
out:
	early_memunmap(log_tbl, माप(*log_tbl));
	वापस ret;
पूर्ण

