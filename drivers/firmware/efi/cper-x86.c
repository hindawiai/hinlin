<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) 2018, Advanced Micro Devices, Inc.

#समावेश <linux/cper.h>
#समावेश <linux/acpi.h>

/*
 * We करोn't need a "CPER_IA" prefix since these are all locally defined.
 * This will save us a lot of line space.
 */
#घोषणा VALID_LAPIC_ID			BIT_ULL(0)
#घोषणा VALID_CPUID_INFO		BIT_ULL(1)
#घोषणा VALID_PROC_ERR_INFO_NUM(bits)	(((bits) & GENMASK_ULL(7, 2)) >> 2)
#घोषणा VALID_PROC_CXT_INFO_NUM(bits)	(((bits) & GENMASK_ULL(13, 8)) >> 8)

#घोषणा INFO_ERR_STRUCT_TYPE_CACHE					\
	GUID_INIT(0xA55701F5, 0xE3EF, 0x43DE, 0xAC, 0x72, 0x24, 0x9B,	\
		  0x57, 0x3F, 0xAD, 0x2C)
#घोषणा INFO_ERR_STRUCT_TYPE_TLB					\
	GUID_INIT(0xFC06B535, 0x5E1F, 0x4562, 0x9F, 0x25, 0x0A, 0x3B,	\
		  0x9A, 0xDB, 0x63, 0xC3)
#घोषणा INFO_ERR_STRUCT_TYPE_BUS					\
	GUID_INIT(0x1CF3F8B3, 0xC5B1, 0x49a2, 0xAA, 0x59, 0x5E, 0xEF,	\
		  0x92, 0xFF, 0xA6, 0x3C)
#घोषणा INFO_ERR_STRUCT_TYPE_MS						\
	GUID_INIT(0x48AB7F57, 0xDC34, 0x4f6c, 0xA7, 0xD3, 0xB0, 0xB5,	\
		  0xB0, 0xA7, 0x43, 0x14)

#घोषणा INFO_VALID_CHECK_INFO		BIT_ULL(0)
#घोषणा INFO_VALID_TARGET_ID		BIT_ULL(1)
#घोषणा INFO_VALID_REQUESTOR_ID		BIT_ULL(2)
#घोषणा INFO_VALID_RESPONDER_ID		BIT_ULL(3)
#घोषणा INFO_VALID_IP			BIT_ULL(4)

#घोषणा CHECK_VALID_TRANS_TYPE		BIT_ULL(0)
#घोषणा CHECK_VALID_OPERATION		BIT_ULL(1)
#घोषणा CHECK_VALID_LEVEL		BIT_ULL(2)
#घोषणा CHECK_VALID_PCC			BIT_ULL(3)
#घोषणा CHECK_VALID_UNCORRECTED		BIT_ULL(4)
#घोषणा CHECK_VALID_PRECISE_IP		BIT_ULL(5)
#घोषणा CHECK_VALID_RESTARTABLE_IP	BIT_ULL(6)
#घोषणा CHECK_VALID_OVERFLOW		BIT_ULL(7)

#घोषणा CHECK_VALID_BUS_PART_TYPE	BIT_ULL(8)
#घोषणा CHECK_VALID_BUS_TIME_OUT	BIT_ULL(9)
#घोषणा CHECK_VALID_BUS_ADDR_SPACE	BIT_ULL(10)

#घोषणा CHECK_VALID_BITS(check)		(((check) & GENMASK_ULL(15, 0)))
#घोषणा CHECK_TRANS_TYPE(check)		(((check) & GENMASK_ULL(17, 16)) >> 16)
#घोषणा CHECK_OPERATION(check)		(((check) & GENMASK_ULL(21, 18)) >> 18)
#घोषणा CHECK_LEVEL(check)		(((check) & GENMASK_ULL(24, 22)) >> 22)
#घोषणा CHECK_PCC			BIT_ULL(25)
#घोषणा CHECK_UNCORRECTED		BIT_ULL(26)
#घोषणा CHECK_PRECISE_IP		BIT_ULL(27)
#घोषणा CHECK_RESTARTABLE_IP		BIT_ULL(28)
#घोषणा CHECK_OVERFLOW			BIT_ULL(29)

#घोषणा CHECK_BUS_PART_TYPE(check)	(((check) & GENMASK_ULL(31, 30)) >> 30)
#घोषणा CHECK_BUS_TIME_OUT		BIT_ULL(32)
#घोषणा CHECK_BUS_ADDR_SPACE(check)	(((check) & GENMASK_ULL(34, 33)) >> 33)

#घोषणा CHECK_VALID_MS_ERR_TYPE		BIT_ULL(0)
#घोषणा CHECK_VALID_MS_PCC		BIT_ULL(1)
#घोषणा CHECK_VALID_MS_UNCORRECTED	BIT_ULL(2)
#घोषणा CHECK_VALID_MS_PRECISE_IP	BIT_ULL(3)
#घोषणा CHECK_VALID_MS_RESTARTABLE_IP	BIT_ULL(4)
#घोषणा CHECK_VALID_MS_OVERFLOW		BIT_ULL(5)

#घोषणा CHECK_MS_ERR_TYPE(check)	(((check) & GENMASK_ULL(18, 16)) >> 16)
#घोषणा CHECK_MS_PCC			BIT_ULL(19)
#घोषणा CHECK_MS_UNCORRECTED		BIT_ULL(20)
#घोषणा CHECK_MS_PRECISE_IP		BIT_ULL(21)
#घोषणा CHECK_MS_RESTARTABLE_IP		BIT_ULL(22)
#घोषणा CHECK_MS_OVERFLOW		BIT_ULL(23)

#घोषणा CTX_TYPE_MSR			1
#घोषणा CTX_TYPE_MMREG			7

क्रमागत err_types अणु
	ERR_TYPE_CACHE = 0,
	ERR_TYPE_TLB,
	ERR_TYPE_BUS,
	ERR_TYPE_MS,
	N_ERR_TYPES
पूर्ण;

अटल क्रमागत err_types cper_get_err_type(स्थिर guid_t *err_type)
अणु
	अगर (guid_equal(err_type, &INFO_ERR_STRUCT_TYPE_CACHE))
		वापस ERR_TYPE_CACHE;
	अन्यथा अगर (guid_equal(err_type, &INFO_ERR_STRUCT_TYPE_TLB))
		वापस ERR_TYPE_TLB;
	अन्यथा अगर (guid_equal(err_type, &INFO_ERR_STRUCT_TYPE_BUS))
		वापस ERR_TYPE_BUS;
	अन्यथा अगर (guid_equal(err_type, &INFO_ERR_STRUCT_TYPE_MS))
		वापस ERR_TYPE_MS;
	अन्यथा
		वापस N_ERR_TYPES;
पूर्ण

अटल स्थिर अक्षर * स्थिर ia_check_trans_type_strs[] = अणु
	"Instruction",
	"Data Access",
	"Generic",
पूर्ण;

अटल स्थिर अक्षर * स्थिर ia_check_op_strs[] = अणु
	"generic error",
	"generic read",
	"generic write",
	"data read",
	"data write",
	"instruction fetch",
	"prefetch",
	"eviction",
	"snoop",
पूर्ण;

अटल स्थिर अक्षर * स्थिर ia_check_bus_part_type_strs[] = अणु
	"Local Processor originated request",
	"Local Processor responded to request",
	"Local Processor observed",
	"Generic",
पूर्ण;

अटल स्थिर अक्षर * स्थिर ia_check_bus_addr_space_strs[] = अणु
	"Memory Access",
	"Reserved",
	"I/O",
	"Other Transaction",
पूर्ण;

अटल स्थिर अक्षर * स्थिर ia_check_ms_error_type_strs[] = अणु
	"No Error",
	"Unclassified",
	"Microcode ROM Parity Error",
	"External Error",
	"FRC Error",
	"Internal Unclassified",
पूर्ण;

अटल स्थिर अक्षर * स्थिर ia_reg_ctx_strs[] = अणु
	"Unclassified Data",
	"MSR Registers (Machine Check and other MSRs)",
	"32-bit Mode Execution Context",
	"64-bit Mode Execution Context",
	"FXSAVE Context",
	"32-bit Mode Debug Registers (DR0-DR7)",
	"64-bit Mode Debug Registers (DR0-DR7)",
	"Memory Mapped Registers",
पूर्ण;

अटल अंतरभूत व्योम prपूर्णांक_bool(अक्षर *str, स्थिर अक्षर *pfx, u64 check, u64 bit)
अणु
	prपूर्णांकk("%s%s: %s\n", pfx, str, (check & bit) ? "true" : "false");
पूर्ण

अटल व्योम prपूर्णांक_err_info_ms(स्थिर अक्षर *pfx, u16 validation_bits, u64 check)
अणु
	अगर (validation_bits & CHECK_VALID_MS_ERR_TYPE) अणु
		u8 err_type = CHECK_MS_ERR_TYPE(check);

		prपूर्णांकk("%sError Type: %u, %s\n", pfx, err_type,
		       err_type < ARRAY_SIZE(ia_check_ms_error_type_strs) ?
		       ia_check_ms_error_type_strs[err_type] : "unknown");
	पूर्ण

	अगर (validation_bits & CHECK_VALID_MS_PCC)
		prपूर्णांक_bool("Processor Context Corrupt", pfx, check, CHECK_MS_PCC);

	अगर (validation_bits & CHECK_VALID_MS_UNCORRECTED)
		prपूर्णांक_bool("Uncorrected", pfx, check, CHECK_MS_UNCORRECTED);

	अगर (validation_bits & CHECK_VALID_MS_PRECISE_IP)
		prपूर्णांक_bool("Precise IP", pfx, check, CHECK_MS_PRECISE_IP);

	अगर (validation_bits & CHECK_VALID_MS_RESTARTABLE_IP)
		prपूर्णांक_bool("Restartable IP", pfx, check, CHECK_MS_RESTARTABLE_IP);

	अगर (validation_bits & CHECK_VALID_MS_OVERFLOW)
		prपूर्णांक_bool("Overflow", pfx, check, CHECK_MS_OVERFLOW);
पूर्ण

अटल व्योम prपूर्णांक_err_info(स्थिर अक्षर *pfx, u8 err_type, u64 check)
अणु
	u16 validation_bits = CHECK_VALID_BITS(check);

	/*
	 * The MS Check काष्ठाure varies a lot from the others, so use a
	 * separate function क्रम decoding.
	 */
	अगर (err_type == ERR_TYPE_MS)
		वापस prपूर्णांक_err_info_ms(pfx, validation_bits, check);

	अगर (validation_bits & CHECK_VALID_TRANS_TYPE) अणु
		u8 trans_type = CHECK_TRANS_TYPE(check);

		prपूर्णांकk("%sTransaction Type: %u, %s\n", pfx, trans_type,
		       trans_type < ARRAY_SIZE(ia_check_trans_type_strs) ?
		       ia_check_trans_type_strs[trans_type] : "unknown");
	पूर्ण

	अगर (validation_bits & CHECK_VALID_OPERATION) अणु
		u8 op = CHECK_OPERATION(check);

		/*
		 * CACHE has more operation types than TLB or BUS, though the
		 * name and the order are the same.
		 */
		u8 max_ops = (err_type == ERR_TYPE_CACHE) ? 9 : 7;

		prपूर्णांकk("%sOperation: %u, %s\n", pfx, op,
		       op < max_ops ? ia_check_op_strs[op] : "unknown");
	पूर्ण

	अगर (validation_bits & CHECK_VALID_LEVEL)
		prपूर्णांकk("%sLevel: %llu\n", pfx, CHECK_LEVEL(check));

	अगर (validation_bits & CHECK_VALID_PCC)
		prपूर्णांक_bool("Processor Context Corrupt", pfx, check, CHECK_PCC);

	अगर (validation_bits & CHECK_VALID_UNCORRECTED)
		prपूर्णांक_bool("Uncorrected", pfx, check, CHECK_UNCORRECTED);

	अगर (validation_bits & CHECK_VALID_PRECISE_IP)
		prपूर्णांक_bool("Precise IP", pfx, check, CHECK_PRECISE_IP);

	अगर (validation_bits & CHECK_VALID_RESTARTABLE_IP)
		prपूर्णांक_bool("Restartable IP", pfx, check, CHECK_RESTARTABLE_IP);

	अगर (validation_bits & CHECK_VALID_OVERFLOW)
		prपूर्णांक_bool("Overflow", pfx, check, CHECK_OVERFLOW);

	अगर (err_type != ERR_TYPE_BUS)
		वापस;

	अगर (validation_bits & CHECK_VALID_BUS_PART_TYPE) अणु
		u8 part_type = CHECK_BUS_PART_TYPE(check);

		prपूर्णांकk("%sParticipation Type: %u, %s\n", pfx, part_type,
		       part_type < ARRAY_SIZE(ia_check_bus_part_type_strs) ?
		       ia_check_bus_part_type_strs[part_type] : "unknown");
	पूर्ण

	अगर (validation_bits & CHECK_VALID_BUS_TIME_OUT)
		prपूर्णांक_bool("Time Out", pfx, check, CHECK_BUS_TIME_OUT);

	अगर (validation_bits & CHECK_VALID_BUS_ADDR_SPACE) अणु
		u8 addr_space = CHECK_BUS_ADDR_SPACE(check);

		prपूर्णांकk("%sAddress Space: %u, %s\n", pfx, addr_space,
		       addr_space < ARRAY_SIZE(ia_check_bus_addr_space_strs) ?
		       ia_check_bus_addr_space_strs[addr_space] : "unknown");
	पूर्ण
पूर्ण

व्योम cper_prपूर्णांक_proc_ia(स्थिर अक्षर *pfx, स्थिर काष्ठा cper_sec_proc_ia *proc)
अणु
	पूर्णांक i;
	काष्ठा cper_ia_err_info *err_info;
	काष्ठा cper_ia_proc_ctx *ctx_info;
	अक्षर newpfx[64], infopfx[64];
	u8 err_type;

	अगर (proc->validation_bits & VALID_LAPIC_ID)
		prपूर्णांकk("%sLocal APIC_ID: 0x%llx\n", pfx, proc->lapic_id);

	अगर (proc->validation_bits & VALID_CPUID_INFO) अणु
		prपूर्णांकk("%sCPUID Info:\n", pfx);
		prपूर्णांक_hex_dump(pfx, "", DUMP_PREFIX_OFFSET, 16, 4, proc->cpuid,
			       माप(proc->cpuid), 0);
	पूर्ण

	snम_लिखो(newpfx, माप(newpfx), "%s ", pfx);

	err_info = (काष्ठा cper_ia_err_info *)(proc + 1);
	क्रम (i = 0; i < VALID_PROC_ERR_INFO_NUM(proc->validation_bits); i++) अणु
		prपूर्णांकk("%sError Information Structure %d:\n", pfx, i);

		err_type = cper_get_err_type(&err_info->err_type);
		prपूर्णांकk("%sError Structure Type: %s\n", newpfx,
		       err_type < ARRAY_SIZE(cper_proc_error_type_strs) ?
		       cper_proc_error_type_strs[err_type] : "unknown");

		अगर (err_type >= N_ERR_TYPES) अणु
			prपूर्णांकk("%sError Structure Type: %pUl\n", newpfx,
			       &err_info->err_type);
		पूर्ण

		अगर (err_info->validation_bits & INFO_VALID_CHECK_INFO) अणु
			prपूर्णांकk("%sCheck Information: 0x%016llx\n", newpfx,
			       err_info->check_info);

			अगर (err_type < N_ERR_TYPES) अणु
				snम_लिखो(infopfx, माप(infopfx), "%s ",
					 newpfx);

				prपूर्णांक_err_info(infopfx, err_type,
					       err_info->check_info);
			पूर्ण
		पूर्ण

		अगर (err_info->validation_bits & INFO_VALID_TARGET_ID) अणु
			prपूर्णांकk("%sTarget Identifier: 0x%016llx\n",
			       newpfx, err_info->target_id);
		पूर्ण

		अगर (err_info->validation_bits & INFO_VALID_REQUESTOR_ID) अणु
			prपूर्णांकk("%sRequestor Identifier: 0x%016llx\n",
			       newpfx, err_info->requestor_id);
		पूर्ण

		अगर (err_info->validation_bits & INFO_VALID_RESPONDER_ID) अणु
			prपूर्णांकk("%sResponder Identifier: 0x%016llx\n",
			       newpfx, err_info->responder_id);
		पूर्ण

		अगर (err_info->validation_bits & INFO_VALID_IP) अणु
			prपूर्णांकk("%sInstruction Pointer: 0x%016llx\n",
			       newpfx, err_info->ip);
		पूर्ण

		err_info++;
	पूर्ण

	ctx_info = (काष्ठा cper_ia_proc_ctx *)err_info;
	क्रम (i = 0; i < VALID_PROC_CXT_INFO_NUM(proc->validation_bits); i++) अणु
		पूर्णांक size = माप(*ctx_info) + ctx_info->reg_arr_size;
		पूर्णांक groupsize = 4;

		prपूर्णांकk("%sContext Information Structure %d:\n", pfx, i);

		prपूर्णांकk("%sRegister Context Type: %s\n", newpfx,
		       ctx_info->reg_ctx_type < ARRAY_SIZE(ia_reg_ctx_strs) ?
		       ia_reg_ctx_strs[ctx_info->reg_ctx_type] : "unknown");

		prपूर्णांकk("%sRegister Array Size: 0x%04x\n", newpfx,
		       ctx_info->reg_arr_size);

		अगर (ctx_info->reg_ctx_type == CTX_TYPE_MSR) अणु
			groupsize = 8; /* MSRs are 8 bytes wide. */
			prपूर्णांकk("%sMSR Address: 0x%08x\n", newpfx,
			       ctx_info->msr_addr);
		पूर्ण

		अगर (ctx_info->reg_ctx_type == CTX_TYPE_MMREG) अणु
			prपूर्णांकk("%sMM Register Address: 0x%016llx\n", newpfx,
			       ctx_info->mm_reg_addr);
		पूर्ण

		अगर (ctx_info->reg_ctx_type != CTX_TYPE_MSR ||
		    arch_apei_report_x86_error(ctx_info, proc->lapic_id)) अणु
			prपूर्णांकk("%sRegister Array:\n", newpfx);
			prपूर्णांक_hex_dump(newpfx, "", DUMP_PREFIX_OFFSET, 16,
				       groupsize, (ctx_info + 1),
				       ctx_info->reg_arr_size, 0);
		पूर्ण

		ctx_info = (काष्ठा cper_ia_proc_ctx *)((दीर्घ)ctx_info + size);
	पूर्ण
पूर्ण
