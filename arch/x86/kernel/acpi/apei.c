<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Arch-specअगरic APEI-related functions.
 */

#समावेश <acpi/apei.h>

#समावेश <यंत्र/mce.h>
#समावेश <यंत्र/tlbflush.h>

पूर्णांक arch_apei_enable_cmcff(काष्ठा acpi_hest_header *hest_hdr, व्योम *data)
अणु
#अगर_घोषित CONFIG_X86_MCE
	पूर्णांक i;
	काष्ठा acpi_hest_ia_corrected *cmc;
	काष्ठा acpi_hest_ia_error_bank *mc_bank;

	cmc = (काष्ठा acpi_hest_ia_corrected *)hest_hdr;
	अगर (!cmc->enabled)
		वापस 0;

	/*
	 * We expect HEST to provide a list of MC banks that report errors
	 * in firmware first mode. Otherwise, वापस non-zero value to
	 * indicate that we are करोne parsing HEST.
	 */
	अगर (!(cmc->flags & ACPI_HEST_FIRMWARE_FIRST) ||
	    !cmc->num_hardware_banks)
		वापस 1;

	pr_info("HEST: Enabling Firmware First mode for corrected errors.\n");

	mc_bank = (काष्ठा acpi_hest_ia_error_bank *)(cmc + 1);
	क्रम (i = 0; i < cmc->num_hardware_banks; i++, mc_bank++)
		mce_disable_bank(mc_bank->bank_number);
#पूर्ण_अगर
	वापस 1;
पूर्ण

व्योम arch_apei_report_mem_error(पूर्णांक sev, काष्ठा cper_sec_mem_err *mem_err)
अणु
#अगर_घोषित CONFIG_X86_MCE
	apei_mce_report_mem_error(sev, mem_err);
#पूर्ण_अगर
पूर्ण

पूर्णांक arch_apei_report_x86_error(काष्ठा cper_ia_proc_ctx *ctx_info, u64 lapic_id)
अणु
	वापस apei_smca_report_x86_error(ctx_info, lapic_id);
पूर्ण
