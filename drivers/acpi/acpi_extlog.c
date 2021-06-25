<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Extended Error Log driver
 *
 * Copyright (C) 2013 Intel Corp.
 * Author: Chen, Gong <gong.chen@पूर्णांकel.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/acpi.h>
#समावेश <linux/cper.h>
#समावेश <linux/ratelimit.h>
#समावेश <linux/edac.h>
#समावेश <linux/ras.h>
#समावेश <यंत्र/cpu.h>
#समावेश <यंत्र/mce.h>

#समावेश "apei/apei-internal.h"
#समावेश <ras/ras_event.h>

#घोषणा EXT_ELOG_ENTRY_MASK	GENMASK_ULL(51, 0) /* elog entry address mask */

#घोषणा EXTLOG_DSM_REV		0x0
#घोषणा	EXTLOG_FN_ADDR		0x1

#घोषणा FLAG_OS_OPTIN		BIT(0)
#घोषणा ELOG_ENTRY_VALID	(1ULL<<63)
#घोषणा ELOG_ENTRY_LEN		0x1000

#घोषणा EMCA_BUG \
	"Can not request iomem region <0x%016llx-0x%016llx> - eMCA disabled\n"

काष्ठा extlog_l1_head अणु
	u32 ver;	/* Header Version */
	u32 hdr_len;	/* Header Length */
	u64 total_len;	/* entire L1 Directory length including this header */
	u64 elog_base;	/* MCA Error Log Directory base address */
	u64 elog_len;	/* MCA Error Log Directory length */
	u32 flags;	/* bit 0 - OS/VMM Opt-in */
	u8  rev0[12];
	u32 entries;	/* Valid L1 Directory entries per logical processor */
	u8  rev1[12];
पूर्ण;

अटल u8 extlog_dsm_uuid[] __initdata = "663E35AF-CC10-41A4-88EA-5470AF055295";

/* L1 table related physical address */
अटल u64 elog_base;
अटल माप_प्रकार elog_size;
अटल u64 l1_dirbase;
अटल माप_प्रकार l1_size;

/* L1 table related भव address */
अटल व्योम __iomem *extlog_l1_addr;
अटल व्योम __iomem *elog_addr;

अटल व्योम *elog_buf;

अटल u64 *l1_entry_base;
अटल u32 l1_percpu_entry;

#घोषणा ELOG_IDX(cpu, bank) \
	(cpu_physical_id(cpu) * l1_percpu_entry + (bank))

#घोषणा ELOG_ENTRY_DATA(idx) \
	(*(l1_entry_base + (idx)))

#घोषणा ELOG_ENTRY_ADDR(phyaddr) \
	(phyaddr - elog_base + (u8 *)elog_addr)

अटल काष्ठा acpi_hest_generic_status *extlog_elog_entry_check(पूर्णांक cpu, पूर्णांक bank)
अणु
	पूर्णांक idx;
	u64 data;
	काष्ठा acpi_hest_generic_status *estatus;

	WARN_ON(cpu < 0);
	idx = ELOG_IDX(cpu, bank);
	data = ELOG_ENTRY_DATA(idx);
	अगर ((data & ELOG_ENTRY_VALID) == 0)
		वापस शून्य;

	data &= EXT_ELOG_ENTRY_MASK;
	estatus = (काष्ठा acpi_hest_generic_status *)ELOG_ENTRY_ADDR(data);

	/* अगर no valid data in elog entry, just वापस */
	अगर (estatus->block_status == 0)
		वापस शून्य;

	वापस estatus;
पूर्ण

अटल व्योम __prपूर्णांक_extlog_rcd(स्थिर अक्षर *pfx,
			       काष्ठा acpi_hest_generic_status *estatus, पूर्णांक cpu)
अणु
	अटल atomic_t seqno;
	अचिन्हित पूर्णांक curr_seqno;
	अक्षर pfx_seq[64];

	अगर (!pfx) अणु
		अगर (estatus->error_severity <= CPER_SEV_CORRECTED)
			pfx = KERN_INFO;
		अन्यथा
			pfx = KERN_ERR;
	पूर्ण
	curr_seqno = atomic_inc_वापस(&seqno);
	snम_लिखो(pfx_seq, माप(pfx_seq), "%s{%u}", pfx, curr_seqno);
	prपूर्णांकk("%s""Hardware error detected on CPU%d\n", pfx_seq, cpu);
	cper_estatus_prपूर्णांक(pfx_seq, estatus);
पूर्ण

अटल पूर्णांक prपूर्णांक_extlog_rcd(स्थिर अक्षर *pfx,
			    काष्ठा acpi_hest_generic_status *estatus, पूर्णांक cpu)
अणु
	/* Not more than 2 messages every 5 seconds */
	अटल DEFINE_RATELIMIT_STATE(ratelimit_corrected, 5*HZ, 2);
	अटल DEFINE_RATELIMIT_STATE(ratelimit_uncorrected, 5*HZ, 2);
	काष्ठा ratelimit_state *ratelimit;

	अगर (estatus->error_severity == CPER_SEV_CORRECTED ||
	    (estatus->error_severity == CPER_SEV_INFORMATIONAL))
		ratelimit = &ratelimit_corrected;
	अन्यथा
		ratelimit = &ratelimit_uncorrected;
	अगर (__ratelimit(ratelimit)) अणु
		__prपूर्णांक_extlog_rcd(pfx, estatus, cpu);
		वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

अटल पूर्णांक extlog_prपूर्णांक(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ val,
			व्योम *data)
अणु
	काष्ठा mce *mce = (काष्ठा mce *)data;
	पूर्णांक	bank = mce->bank;
	पूर्णांक	cpu = mce->extcpu;
	काष्ठा acpi_hest_generic_status *estatus, *पंचांगp;
	काष्ठा acpi_hest_generic_data *gdata;
	स्थिर guid_t *fru_id = &guid_null;
	अक्षर *fru_text = "";
	guid_t *sec_type;
	अटल u32 err_seq;

	estatus = extlog_elog_entry_check(cpu, bank);
	अगर (estatus == शून्य || (mce->kflags & MCE_HANDLED_CEC))
		वापस NOTIFY_DONE;

	स_नकल(elog_buf, (व्योम *)estatus, ELOG_ENTRY_LEN);
	/* clear record status to enable BIOS to update it again */
	estatus->block_status = 0;

	पंचांगp = (काष्ठा acpi_hest_generic_status *)elog_buf;

	अगर (!ras_userspace_consumers()) अणु
		prपूर्णांक_extlog_rcd(शून्य, पंचांगp, cpu);
		जाओ out;
	पूर्ण

	/* log event via trace */
	err_seq++;
	gdata = (काष्ठा acpi_hest_generic_data *)(पंचांगp + 1);
	अगर (gdata->validation_bits & CPER_SEC_VALID_FRU_ID)
		fru_id = (guid_t *)gdata->fru_id;
	अगर (gdata->validation_bits & CPER_SEC_VALID_FRU_TEXT)
		fru_text = gdata->fru_text;
	sec_type = (guid_t *)gdata->section_type;
	अगर (guid_equal(sec_type, &CPER_SEC_PLATFORM_MEM)) अणु
		काष्ठा cper_sec_mem_err *mem = (व्योम *)(gdata + 1);
		अगर (gdata->error_data_length >= माप(*mem))
			trace_extlog_mem_event(mem, err_seq, fru_id, fru_text,
					       (u8)gdata->error_severity);
	पूर्ण

out:
	mce->kflags |= MCE_HANDLED_EXTLOG;
	वापस NOTIFY_OK;
पूर्ण

अटल bool __init extlog_get_l1addr(व्योम)
अणु
	guid_t guid;
	acpi_handle handle;
	जोड़ acpi_object *obj;

	अगर (guid_parse(extlog_dsm_uuid, &guid))
		वापस false;
	अगर (ACPI_FAILURE(acpi_get_handle(शून्य, "\\_SB", &handle)))
		वापस false;
	अगर (!acpi_check_dsm(handle, &guid, EXTLOG_DSM_REV, 1 << EXTLOG_FN_ADDR))
		वापस false;
	obj = acpi_evaluate_dsm_typed(handle, &guid, EXTLOG_DSM_REV,
				      EXTLOG_FN_ADDR, शून्य, ACPI_TYPE_INTEGER);
	अगर (!obj) अणु
		वापस false;
	पूर्ण अन्यथा अणु
		l1_dirbase = obj->पूर्णांकeger.value;
		ACPI_FREE(obj);
	पूर्ण

	/* Spec says L1 directory must be 4K aligned, bail out अगर it isn't */
	अगर (l1_dirbase & ((1 << 12) - 1)) अणु
		pr_warn(FW_BUG "L1 Directory is invalid at physical %llx\n",
			l1_dirbase);
		वापस false;
	पूर्ण

	वापस true;
पूर्ण
अटल काष्ठा notअगरier_block extlog_mce_dec = अणु
	.notअगरier_call	= extlog_prपूर्णांक,
	.priority	= MCE_PRIO_EXTLOG,
पूर्ण;

अटल पूर्णांक __init extlog_init(व्योम)
अणु
	काष्ठा extlog_l1_head *l1_head;
	व्योम __iomem *extlog_l1_hdr;
	माप_प्रकार l1_hdr_size;
	काष्ठा resource *r;
	u64 cap;
	पूर्णांक rc;

	अगर (rdmsrl_safe(MSR_IA32_MCG_CAP, &cap) ||
	    !(cap & MCG_ELOG_P) ||
	    !extlog_get_l1addr())
		वापस -ENODEV;

	rc = -EINVAL;
	/* get L1 header to fetch necessary inक्रमmation */
	l1_hdr_size = माप(काष्ठा extlog_l1_head);
	r = request_mem_region(l1_dirbase, l1_hdr_size, "L1 DIR HDR");
	अगर (!r) अणु
		pr_warn(FW_BUG EMCA_BUG,
			(अचिन्हित दीर्घ दीर्घ)l1_dirbase,
			(अचिन्हित दीर्घ दीर्घ)l1_dirbase + l1_hdr_size);
		जाओ err;
	पूर्ण

	extlog_l1_hdr = acpi_os_map_iomem(l1_dirbase, l1_hdr_size);
	l1_head = (काष्ठा extlog_l1_head *)extlog_l1_hdr;
	l1_size = l1_head->total_len;
	l1_percpu_entry = l1_head->entries;
	elog_base = l1_head->elog_base;
	elog_size = l1_head->elog_len;
	acpi_os_unmap_iomem(extlog_l1_hdr, l1_hdr_size);
	release_mem_region(l1_dirbase, l1_hdr_size);

	/* remap L1 header again based on completed inक्रमmation */
	r = request_mem_region(l1_dirbase, l1_size, "L1 Table");
	अगर (!r) अणु
		pr_warn(FW_BUG EMCA_BUG,
			(अचिन्हित दीर्घ दीर्घ)l1_dirbase,
			(अचिन्हित दीर्घ दीर्घ)l1_dirbase + l1_size);
		जाओ err;
	पूर्ण
	extlog_l1_addr = acpi_os_map_iomem(l1_dirbase, l1_size);
	l1_entry_base = (u64 *)((u8 *)extlog_l1_addr + l1_hdr_size);

	/* remap elog table */
	r = request_mem_region(elog_base, elog_size, "Elog Table");
	अगर (!r) अणु
		pr_warn(FW_BUG EMCA_BUG,
			(अचिन्हित दीर्घ दीर्घ)elog_base,
			(अचिन्हित दीर्घ दीर्घ)elog_base + elog_size);
		जाओ err_release_l1_dir;
	पूर्ण
	elog_addr = acpi_os_map_iomem(elog_base, elog_size);

	rc = -ENOMEM;
	/* allocate buffer to save elog record */
	elog_buf = kदो_स्मृति(ELOG_ENTRY_LEN, GFP_KERNEL);
	अगर (elog_buf == शून्य)
		जाओ err_release_elog;

	mce_रेजिस्टर_decode_chain(&extlog_mce_dec);
	/* enable OS to be involved to take over management from BIOS */
	((काष्ठा extlog_l1_head *)extlog_l1_addr)->flags |= FLAG_OS_OPTIN;

	वापस 0;

err_release_elog:
	अगर (elog_addr)
		acpi_os_unmap_iomem(elog_addr, elog_size);
	release_mem_region(elog_base, elog_size);
err_release_l1_dir:
	अगर (extlog_l1_addr)
		acpi_os_unmap_iomem(extlog_l1_addr, l1_size);
	release_mem_region(l1_dirbase, l1_size);
err:
	pr_warn(FW_BUG "Extended error log disabled because of problems parsing f/w tables\n");
	वापस rc;
पूर्ण

अटल व्योम __निकास extlog_निकास(व्योम)
अणु
	mce_unरेजिस्टर_decode_chain(&extlog_mce_dec);
	((काष्ठा extlog_l1_head *)extlog_l1_addr)->flags &= ~FLAG_OS_OPTIN;
	अगर (extlog_l1_addr)
		acpi_os_unmap_iomem(extlog_l1_addr, l1_size);
	अगर (elog_addr)
		acpi_os_unmap_iomem(elog_addr, elog_size);
	release_mem_region(elog_base, elog_size);
	release_mem_region(l1_dirbase, l1_size);
	kमुक्त(elog_buf);
पूर्ण

module_init(extlog_init);
module_निकास(extlog_निकास);

MODULE_AUTHOR("Chen, Gong <gong.chen@intel.com>");
MODULE_DESCRIPTION("Extended MCA Error Log Driver");
MODULE_LICENSE("GPL");
