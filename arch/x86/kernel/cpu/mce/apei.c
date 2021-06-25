<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Bridge between MCE and APEI
 *
 * On some machine, corrected memory errors are reported via APEI
 * generic hardware error source (GHES) instead of corrected Machine
 * Check. These corrected memory errors can be reported to user space
 * through /dev/mcelog via faking a corrected Machine Check, so that
 * the error memory page can be offlined by /sbin/mcelog अगर the error
 * count क्रम one page is beyond the threshold.
 *
 * For fatal MCE, save MCE record पूर्णांकo persistent storage via ERST, so
 * that the MCE record can be logged after reboot via ERST.
 *
 * Copyright 2010 Intel Corp.
 *   Author: Huang Ying <ying.huang@पूर्णांकel.com>
 */

#समावेश <linux/export.h>
#समावेश <linux/kernel.h>
#समावेश <linux/acpi.h>
#समावेश <linux/cper.h>
#समावेश <acpi/apei.h>
#समावेश <acpi/ghes.h>
#समावेश <यंत्र/mce.h>

#समावेश "internal.h"

व्योम apei_mce_report_mem_error(पूर्णांक severity, काष्ठा cper_sec_mem_err *mem_err)
अणु
	काष्ठा mce m;

	अगर (!(mem_err->validation_bits & CPER_MEM_VALID_PA))
		वापस;

	mce_setup(&m);
	m.bank = -1;
	/* Fake a memory पढ़ो error with unknown channel */
	m.status = MCI_STATUS_VAL | MCI_STATUS_EN | MCI_STATUS_ADDRV | 0x9f;

	अगर (severity >= GHES_SEV_RECOVERABLE)
		m.status |= MCI_STATUS_UC;

	अगर (severity >= GHES_SEV_PANIC) अणु
		m.status |= MCI_STATUS_PCC;
		m.tsc = rdtsc();
	पूर्ण

	m.addr = mem_err->physical_addr;
	mce_log(&m);
पूर्ण
EXPORT_SYMBOL_GPL(apei_mce_report_mem_error);

पूर्णांक apei_smca_report_x86_error(काष्ठा cper_ia_proc_ctx *ctx_info, u64 lapic_id)
अणु
	स्थिर u64 *i_mce = ((स्थिर u64 *) (ctx_info + 1));
	अचिन्हित पूर्णांक cpu;
	काष्ठा mce m;

	अगर (!boot_cpu_has(X86_FEATURE_SMCA))
		वापस -EINVAL;

	/*
	 * The starting address of the रेजिस्टर array extracted from BERT must
	 * match with the first expected रेजिस्टर in the रेजिस्टर layout of
	 * SMCA address space. This address corresponds to banks's MCA_STATUS
	 * रेजिस्टर.
	 *
	 * Match any MCi_STATUS रेजिस्टर by turning off bank numbers.
	 */
	अगर ((ctx_info->msr_addr & MSR_AMD64_SMCA_MC0_STATUS) !=
				  MSR_AMD64_SMCA_MC0_STATUS)
		वापस -EINVAL;

	/*
	 * The रेजिस्टर array size must be large enough to include all the
	 * SMCA रेजिस्टरs which need to be extracted.
	 *
	 * The number of रेजिस्टरs in the रेजिस्टर array is determined by
	 * Register Array Size/8 as defined in UEFI spec v2.8, sec N.2.4.2.2.
	 * The रेजिस्टर layout is fixed and currently the raw data in the
	 * रेजिस्टर array includes 6 SMCA रेजिस्टरs which the kernel can
	 * extract.
	 */
	अगर (ctx_info->reg_arr_size < 48)
		वापस -EINVAL;

	mce_setup(&m);

	m.extcpu = -1;
	m.socketid = -1;

	क्रम_each_possible_cpu(cpu) अणु
		अगर (cpu_data(cpu).initial_apicid == lapic_id) अणु
			m.extcpu = cpu;
			m.socketid = cpu_data(m.extcpu).phys_proc_id;
			अवरोध;
		पूर्ण
	पूर्ण

	m.apicid = lapic_id;
	m.bank = (ctx_info->msr_addr >> 4) & 0xFF;
	m.status = *i_mce;
	m.addr = *(i_mce + 1);
	m.misc = *(i_mce + 2);
	/* Skipping MCA_CONFIG */
	m.ipid = *(i_mce + 4);
	m.synd = *(i_mce + 5);

	mce_log(&m);

	वापस 0;
पूर्ण

#घोषणा CPER_CREATOR_MCE						\
	GUID_INIT(0x75a574e3, 0x5052, 0x4b29, 0x8a, 0x8e, 0xbe, 0x2c,	\
		  0x64, 0x90, 0xb8, 0x9d)
#घोषणा CPER_SECTION_TYPE_MCE						\
	GUID_INIT(0xfe08ffbe, 0x95e4, 0x4be7, 0xbc, 0x73, 0x40, 0x96,	\
		  0x04, 0x4a, 0x38, 0xfc)

/*
 * CPER specअगरication (in UEFI specअगरication 2.3 appendix N) requires
 * byte-packed.
 */
काष्ठा cper_mce_record अणु
	काष्ठा cper_record_header hdr;
	काष्ठा cper_section_descriptor sec_hdr;
	काष्ठा mce mce;
पूर्ण __packed;

पूर्णांक apei_ग_लिखो_mce(काष्ठा mce *m)
अणु
	काष्ठा cper_mce_record rcd;

	स_रखो(&rcd, 0, माप(rcd));
	स_नकल(rcd.hdr.signature, CPER_SIG_RECORD, CPER_SIG_SIZE);
	rcd.hdr.revision = CPER_RECORD_REV;
	rcd.hdr.signature_end = CPER_SIG_END;
	rcd.hdr.section_count = 1;
	rcd.hdr.error_severity = CPER_SEV_FATAL;
	/* बारtamp, platक्रमm_id, partition_id are all invalid */
	rcd.hdr.validation_bits = 0;
	rcd.hdr.record_length = माप(rcd);
	rcd.hdr.creator_id = CPER_CREATOR_MCE;
	rcd.hdr.notअगरication_type = CPER_NOTIFY_MCE;
	rcd.hdr.record_id = cper_next_record_id();
	rcd.hdr.flags = CPER_HW_ERROR_FLAGS_PREVERR;

	rcd.sec_hdr.section_offset = (व्योम *)&rcd.mce - (व्योम *)&rcd;
	rcd.sec_hdr.section_length = माप(rcd.mce);
	rcd.sec_hdr.revision = CPER_SEC_REV;
	/* fru_id and fru_text is invalid */
	rcd.sec_hdr.validation_bits = 0;
	rcd.sec_hdr.flags = CPER_SEC_PRIMARY;
	rcd.sec_hdr.section_type = CPER_SECTION_TYPE_MCE;
	rcd.sec_hdr.section_severity = CPER_SEV_FATAL;

	स_नकल(&rcd.mce, m, माप(*m));

	वापस erst_ग_लिखो(&rcd.hdr);
पूर्ण

sमाप_प्रकार apei_पढ़ो_mce(काष्ठा mce *m, u64 *record_id)
अणु
	काष्ठा cper_mce_record rcd;
	पूर्णांक rc, pos;

	rc = erst_get_record_id_begin(&pos);
	अगर (rc)
		वापस rc;
retry:
	rc = erst_get_record_id_next(&pos, record_id);
	अगर (rc)
		जाओ out;
	/* no more record */
	अगर (*record_id == APEI_ERST_INVALID_RECORD_ID)
		जाओ out;
	rc = erst_पढ़ो(*record_id, &rcd.hdr, माप(rcd));
	/* someone अन्यथा has cleared the record, try next one */
	अगर (rc == -ENOENT)
		जाओ retry;
	अन्यथा अगर (rc < 0)
		जाओ out;
	/* try to skip other type records in storage */
	अन्यथा अगर (rc != माप(rcd) ||
		 !guid_equal(&rcd.hdr.creator_id, &CPER_CREATOR_MCE))
		जाओ retry;
	स_नकल(m, &rcd.mce, माप(*m));
	rc = माप(*m);
out:
	erst_get_record_id_end();

	वापस rc;
पूर्ण

/* Check whether there is record in ERST */
पूर्णांक apei_check_mce(व्योम)
अणु
	वापस erst_get_record_count();
पूर्ण

पूर्णांक apei_clear_mce(u64 record_id)
अणु
	वापस erst_clear(record_id);
पूर्ण
