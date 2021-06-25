<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2017 Google
 *
 * Authors:
 *      Thiebaud Weksteen <tweek@google.com>
 */

#समावेश <linux/efi.h>
#समावेश <linux/tpm_eventlog.h>

#समावेश "../tpm.h"
#समावेश "common.h"

/* पढ़ो binary bios log from EFI configuration table */
पूर्णांक tpm_पढ़ो_log_efi(काष्ठा tpm_chip *chip)
अणु

	काष्ठा efi_tcg2_final_events_table *final_tbl = शून्य;
	पूर्णांक final_events_log_size = efi_tpm_final_log_size;
	काष्ठा linux_efi_tpm_eventlog *log_tbl;
	काष्ठा tpm_bios_log *log;
	u32 log_size;
	u8 tpm_log_version;
	व्योम *पंचांगp;
	पूर्णांक ret;

	अगर (!(chip->flags & TPM_CHIP_FLAG_TPM2))
		वापस -ENODEV;

	अगर (efi.tpm_log == EFI_INVALID_TABLE_ADDR)
		वापस -ENODEV;

	log = &chip->log;

	log_tbl = memremap(efi.tpm_log, माप(*log_tbl), MEMREMAP_WB);
	अगर (!log_tbl) अणु
		pr_err("Could not map UEFI TPM log table !\n");
		वापस -ENOMEM;
	पूर्ण

	log_size = log_tbl->size;
	memunmap(log_tbl);

	अगर (!log_size) अणु
		pr_warn("UEFI TPM log area empty\n");
		वापस -EIO;
	पूर्ण

	log_tbl = memremap(efi.tpm_log, माप(*log_tbl) + log_size,
			   MEMREMAP_WB);
	अगर (!log_tbl) अणु
		pr_err("Could not map UEFI TPM log table payload!\n");
		वापस -ENOMEM;
	पूर्ण

	/* दो_स्मृति EventLog space */
	log->bios_event_log = kmemdup(log_tbl->log, log_size, GFP_KERNEL);
	अगर (!log->bios_event_log) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	log->bios_event_log_end = log->bios_event_log + log_size;
	tpm_log_version = log_tbl->version;

	ret = tpm_log_version;

	अगर (efi.tpm_final_log == EFI_INVALID_TABLE_ADDR ||
	    final_events_log_size == 0 ||
	    tpm_log_version != EFI_TCG2_EVENT_LOG_FORMAT_TCG_2)
		जाओ out;

	final_tbl = memremap(efi.tpm_final_log,
			     माप(*final_tbl) + final_events_log_size,
			     MEMREMAP_WB);
	अगर (!final_tbl) अणु
		pr_err("Could not map UEFI TPM final log\n");
		kमुक्त(log->bios_event_log);
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	/*
	 * The 'final events log' size excludes the 'final events preboot log'
	 * at its beginning.
	 */
	final_events_log_size -= log_tbl->final_events_preboot_size;

	/*
	 * Allocate memory क्रम the 'combined log' where we will append the
	 * 'final events log' to.
	 */
	पंचांगp = kपुनः_स्मृति(log->bios_event_log,
		       log_size + final_events_log_size,
		       GFP_KERNEL);
	अगर (!पंचांगp) अणु
		kमुक्त(log->bios_event_log);
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	log->bios_event_log = पंचांगp;

	/*
	 * Append any of the 'final events log' that didn't also end up in the
	 * 'main log'. Events can be logged in both अगर events are generated
	 * between GetEventLog() and ExitBootServices().
	 */
	स_नकल((व्योम *)log->bios_event_log + log_size,
	       final_tbl->events + log_tbl->final_events_preboot_size,
	       final_events_log_size);
	/*
	 * The size of the 'combined log' is the size of the 'main log' plus
	 * the size of the 'final events log'.
	 */
	log->bios_event_log_end = log->bios_event_log +
		log_size + final_events_log_size;

out:
	memunmap(final_tbl);
	memunmap(log_tbl);
	वापस ret;
पूर्ण
