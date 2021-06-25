<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * TPM handling.
 *
 * Copyright (C) 2016 CoreOS, Inc
 * Copyright (C) 2017 Google, Inc.
 *     Matthew Garrett <mjg59@google.com>
 *     Thiebaud Weksteen <tweek@google.com>
 */
#समावेश <linux/efi.h>
#समावेश <linux/tpm_eventlog.h>
#समावेश <यंत्र/efi.h>

#समावेश "efistub.h"

#अगर_घोषित CONFIG_RESET_ATTACK_MITIGATION
अटल स्थिर efi_अक्षर16_t efi_MemoryOverWriteRequest_name[] =
	L"MemoryOverwriteRequestControl";

#घोषणा MEMORY_ONLY_RESET_CONTROL_GUID \
	EFI_GUID(0xe20939be, 0x32d4, 0x41be, 0xa1, 0x50, 0x89, 0x7f, 0x85, 0xd4, 0x98, 0x29)

/*
 * Enable reboot attack mitigation. This requests that the firmware clear the
 * RAM on next reboot beक्रमe proceeding with boot, ensuring that any secrets
 * are cleared. If userland has ensured that all secrets have been हटाओd
 * from RAM beक्रमe reboot it can simply reset this variable.
 */
व्योम efi_enable_reset_attack_mitigation(व्योम)
अणु
	u8 val = 1;
	efi_guid_t var_guid = MEMORY_ONLY_RESET_CONTROL_GUID;
	efi_status_t status;
	अचिन्हित दीर्घ datasize = 0;

	status = get_efi_var(efi_MemoryOverWriteRequest_name, &var_guid,
			     शून्य, &datasize, शून्य);

	अगर (status == EFI_NOT_FOUND)
		वापस;

	set_efi_var(efi_MemoryOverWriteRequest_name, &var_guid,
		    EFI_VARIABLE_NON_VOLATILE |
		    EFI_VARIABLE_BOOTSERVICE_ACCESS |
		    EFI_VARIABLE_RUNTIME_ACCESS, माप(val), &val);
पूर्ण

#पूर्ण_अगर

व्योम efi_retrieve_tpm2_eventlog(व्योम)
अणु
	efi_guid_t tcg2_guid = EFI_TCG2_PROTOCOL_GUID;
	efi_guid_t linux_eventlog_guid = LINUX_EFI_TPM_EVENT_LOG_GUID;
	efi_status_t status;
	efi_physical_addr_t log_location = 0, log_last_entry = 0;
	काष्ठा linux_efi_tpm_eventlog *log_tbl = शून्य;
	काष्ठा efi_tcg2_final_events_table *final_events_table = शून्य;
	अचिन्हित दीर्घ first_entry_addr, last_entry_addr;
	माप_प्रकार log_size, last_entry_size;
	efi_bool_t truncated;
	पूर्णांक version = EFI_TCG2_EVENT_LOG_FORMAT_TCG_2;
	efi_tcg2_protocol_t *tcg2_protocol = शून्य;
	पूर्णांक final_events_size = 0;

	status = efi_bs_call(locate_protocol, &tcg2_guid, शून्य,
			     (व्योम **)&tcg2_protocol);
	अगर (status != EFI_SUCCESS)
		वापस;

	status = efi_call_proto(tcg2_protocol, get_event_log, version,
				&log_location, &log_last_entry, &truncated);

	अगर (status != EFI_SUCCESS || !log_location) अणु
		version = EFI_TCG2_EVENT_LOG_FORMAT_TCG_1_2;
		status = efi_call_proto(tcg2_protocol, get_event_log, version,
					&log_location, &log_last_entry,
					&truncated);
		अगर (status != EFI_SUCCESS || !log_location)
			वापस;

	पूर्ण

	first_entry_addr = (अचिन्हित दीर्घ) log_location;

	/*
	 * We populate the EFI table even अगर the logs are empty.
	 */
	अगर (!log_last_entry) अणु
		log_size = 0;
	पूर्ण अन्यथा अणु
		last_entry_addr = (अचिन्हित दीर्घ) log_last_entry;
		/*
		 * get_event_log only वापसs the address of the last entry.
		 * We need to calculate its size to deduce the full size of
		 * the logs.
		 */
		अगर (version == EFI_TCG2_EVENT_LOG_FORMAT_TCG_2) अणु
			/*
			 * The TCG2 log क्रमmat has variable length entries,
			 * and the inक्रमmation to decode the hash algorithms
			 * back पूर्णांकo a size is contained in the first entry -
			 * pass a poपूर्णांकer to the final entry (to calculate its
			 * size) and the first entry (so we know how दीर्घ each
			 * digest is)
			 */
			last_entry_size =
				__calc_tpm2_event_size((व्योम *)last_entry_addr,
						    (व्योम *)(दीर्घ)log_location,
						    false);
		पूर्ण अन्यथा अणु
			last_entry_size = माप(काष्ठा tcpa_event) +
			   ((काष्ठा tcpa_event *) last_entry_addr)->event_size;
		पूर्ण
		log_size = log_last_entry - log_location + last_entry_size;
	पूर्ण

	/* Allocate space क्रम the logs and copy them. */
	status = efi_bs_call(allocate_pool, EFI_LOADER_DATA,
			     माप(*log_tbl) + log_size, (व्योम **)&log_tbl);

	अगर (status != EFI_SUCCESS) अणु
		efi_err("Unable to allocate memory for event log\n");
		वापस;
	पूर्ण

	/*
	 * Figure out whether any events have alपढ़ोy been logged to the
	 * final events काष्ठाure, and अगर so how much space they take up
	 */
	अगर (version == EFI_TCG2_EVENT_LOG_FORMAT_TCG_2)
		final_events_table = get_efi_config_table(LINUX_EFI_TPM_FINAL_LOG_GUID);
	अगर (final_events_table && final_events_table->nr_events) अणु
		काष्ठा tcg_pcr_event2_head *header;
		पूर्णांक offset;
		व्योम *data;
		पूर्णांक event_size;
		पूर्णांक i = final_events_table->nr_events;

		data = (व्योम *)final_events_table;
		offset = माप(final_events_table->version) +
			माप(final_events_table->nr_events);

		जबतक (i > 0) अणु
			header = data + offset + final_events_size;
			event_size = __calc_tpm2_event_size(header,
						   (व्योम *)(दीर्घ)log_location,
						   false);
			final_events_size += event_size;
			i--;
		पूर्ण
	पूर्ण

	स_रखो(log_tbl, 0, माप(*log_tbl) + log_size);
	log_tbl->size = log_size;
	log_tbl->final_events_preboot_size = final_events_size;
	log_tbl->version = version;
	स_नकल(log_tbl->log, (व्योम *) first_entry_addr, log_size);

	status = efi_bs_call(install_configuration_table,
			     &linux_eventlog_guid, log_tbl);
	अगर (status != EFI_SUCCESS)
		जाओ err_मुक्त;
	वापस;

err_मुक्त:
	efi_bs_call(मुक्त_pool, log_tbl);
पूर्ण
