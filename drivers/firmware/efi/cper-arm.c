<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * UEFI Common Platक्रमm Error Record (CPER) support
 *
 * Copyright (C) 2017, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/समय.स>
#समावेश <linux/cper.h>
#समावेश <linux/dmi.h>
#समावेश <linux/acpi.h>
#समावेश <linux/pci.h>
#समावेश <linux/aer.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/bcd.h>
#समावेश <acpi/ghes.h>
#समावेश <ras/ras_event.h>

अटल स्थिर अक्षर * स्थिर arm_reg_ctx_strs[] = अणु
	"AArch32 general purpose registers",
	"AArch32 EL1 context registers",
	"AArch32 EL2 context registers",
	"AArch32 secure context registers",
	"AArch64 general purpose registers",
	"AArch64 EL1 context registers",
	"AArch64 EL2 context registers",
	"AArch64 EL3 context registers",
	"Misc. system register structure",
पूर्ण;

अटल स्थिर अक्षर * स्थिर arm_err_trans_type_strs[] = अणु
	"Instruction",
	"Data Access",
	"Generic",
पूर्ण;

अटल स्थिर अक्षर * स्थिर arm_bus_err_op_strs[] = अणु
	"Generic error (type cannot be determined)",
	"Generic read (type of instruction or data request cannot be determined)",
	"Generic write (type of instruction of data request cannot be determined)",
	"Data read",
	"Data write",
	"Instruction fetch",
	"Prefetch",
पूर्ण;

अटल स्थिर अक्षर * स्थिर arm_cache_err_op_strs[] = अणु
	"Generic error (type cannot be determined)",
	"Generic read (type of instruction or data request cannot be determined)",
	"Generic write (type of instruction of data request cannot be determined)",
	"Data read",
	"Data write",
	"Instruction fetch",
	"Prefetch",
	"Eviction",
	"Snooping (processor initiated a cache snoop that resulted in an error)",
	"Snooped (processor raised a cache error caused by another processor or device snooping its cache)",
	"Management",
पूर्ण;

अटल स्थिर अक्षर * स्थिर arm_tlb_err_op_strs[] = अणु
	"Generic error (type cannot be determined)",
	"Generic read (type of instruction or data request cannot be determined)",
	"Generic write (type of instruction of data request cannot be determined)",
	"Data read",
	"Data write",
	"Instruction fetch",
	"Prefetch",
	"Local management operation (processor initiated a TLB management operation that resulted in an error)",
	"External management operation (processor raised a TLB error caused by another processor or device broadcasting TLB operations)",
पूर्ण;

अटल स्थिर अक्षर * स्थिर arm_bus_err_part_type_strs[] = अणु
	"Local processor originated request",
	"Local processor responded to request",
	"Local processor observed",
	"Generic",
पूर्ण;

अटल स्थिर अक्षर * स्थिर arm_bus_err_addr_space_strs[] = अणु
	"External Memory Access",
	"Internal Memory Access",
	"Unknown",
	"Device Memory Access",
पूर्ण;

अटल व्योम cper_prपूर्णांक_arm_err_info(स्थिर अक्षर *pfx, u32 type,
				    u64 error_info)
अणु
	u8 trans_type, op_type, level, participation_type, address_space;
	u16 mem_attributes;
	bool proc_context_corrupt, corrected, precise_pc, restartable_pc;
	bool समय_out, access_mode;

	/* If the type is unknown, bail. */
	अगर (type > CPER_ARM_MAX_TYPE)
		वापस;

	/*
	 * Venकरोr type errors have error inक्रमmation values that are venकरोr
	 * specअगरic.
	 */
	अगर (type == CPER_ARM_VENDOR_ERROR)
		वापस;

	अगर (error_info & CPER_ARM_ERR_VALID_TRANSACTION_TYPE) अणु
		trans_type = ((error_info >> CPER_ARM_ERR_TRANSACTION_SHIFT)
			      & CPER_ARM_ERR_TRANSACTION_MASK);
		अगर (trans_type < ARRAY_SIZE(arm_err_trans_type_strs)) अणु
			prपूर्णांकk("%stransaction type: %s\n", pfx,
			       arm_err_trans_type_strs[trans_type]);
		पूर्ण
	पूर्ण

	अगर (error_info & CPER_ARM_ERR_VALID_OPERATION_TYPE) अणु
		op_type = ((error_info >> CPER_ARM_ERR_OPERATION_SHIFT)
			   & CPER_ARM_ERR_OPERATION_MASK);
		चयन (type) अणु
		हाल CPER_ARM_CACHE_ERROR:
			अगर (op_type < ARRAY_SIZE(arm_cache_err_op_strs)) अणु
				prपूर्णांकk("%soperation type: %s\n", pfx,
				       arm_cache_err_op_strs[op_type]);
			पूर्ण
			अवरोध;
		हाल CPER_ARM_TLB_ERROR:
			अगर (op_type < ARRAY_SIZE(arm_tlb_err_op_strs)) अणु
				prपूर्णांकk("%soperation type: %s\n", pfx,
				       arm_tlb_err_op_strs[op_type]);
			पूर्ण
			अवरोध;
		हाल CPER_ARM_BUS_ERROR:
			अगर (op_type < ARRAY_SIZE(arm_bus_err_op_strs)) अणु
				prपूर्णांकk("%soperation type: %s\n", pfx,
				       arm_bus_err_op_strs[op_type]);
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (error_info & CPER_ARM_ERR_VALID_LEVEL) अणु
		level = ((error_info >> CPER_ARM_ERR_LEVEL_SHIFT)
			 & CPER_ARM_ERR_LEVEL_MASK);
		चयन (type) अणु
		हाल CPER_ARM_CACHE_ERROR:
			prपूर्णांकk("%scache level: %d\n", pfx, level);
			अवरोध;
		हाल CPER_ARM_TLB_ERROR:
			prपूर्णांकk("%sTLB level: %d\n", pfx, level);
			अवरोध;
		हाल CPER_ARM_BUS_ERROR:
			prपूर्णांकk("%saffinity level at which the bus error occurred: %d\n",
			       pfx, level);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (error_info & CPER_ARM_ERR_VALID_PROC_CONTEXT_CORRUPT) अणु
		proc_context_corrupt = ((error_info >> CPER_ARM_ERR_PC_CORRUPT_SHIFT)
					& CPER_ARM_ERR_PC_CORRUPT_MASK);
		अगर (proc_context_corrupt)
			prपूर्णांकk("%sprocessor context corrupted\n", pfx);
		अन्यथा
			prपूर्णांकk("%sprocessor context not corrupted\n", pfx);
	पूर्ण

	अगर (error_info & CPER_ARM_ERR_VALID_CORRECTED) अणु
		corrected = ((error_info >> CPER_ARM_ERR_CORRECTED_SHIFT)
			     & CPER_ARM_ERR_CORRECTED_MASK);
		अगर (corrected)
			prपूर्णांकk("%sthe error has been corrected\n", pfx);
		अन्यथा
			prपूर्णांकk("%sthe error has not been corrected\n", pfx);
	पूर्ण

	अगर (error_info & CPER_ARM_ERR_VALID_PRECISE_PC) अणु
		precise_pc = ((error_info >> CPER_ARM_ERR_PRECISE_PC_SHIFT)
			      & CPER_ARM_ERR_PRECISE_PC_MASK);
		अगर (precise_pc)
			prपूर्णांकk("%sPC is precise\n", pfx);
		अन्यथा
			prपूर्णांकk("%sPC is imprecise\n", pfx);
	पूर्ण

	अगर (error_info & CPER_ARM_ERR_VALID_RESTARTABLE_PC) अणु
		restartable_pc = ((error_info >> CPER_ARM_ERR_RESTARTABLE_PC_SHIFT)
				  & CPER_ARM_ERR_RESTARTABLE_PC_MASK);
		अगर (restartable_pc)
			prपूर्णांकk("%sProgram execution can be restarted reliably at the PC associated with the error.\n", pfx);
	पूर्ण

	/* The rest of the fields are specअगरic to bus errors */
	अगर (type != CPER_ARM_BUS_ERROR)
		वापस;

	अगर (error_info & CPER_ARM_ERR_VALID_PARTICIPATION_TYPE) अणु
		participation_type = ((error_info >> CPER_ARM_ERR_PARTICIPATION_TYPE_SHIFT)
				      & CPER_ARM_ERR_PARTICIPATION_TYPE_MASK);
		अगर (participation_type < ARRAY_SIZE(arm_bus_err_part_type_strs)) अणु
			prपूर्णांकk("%sparticipation type: %s\n", pfx,
			       arm_bus_err_part_type_strs[participation_type]);
		पूर्ण
	पूर्ण

	अगर (error_info & CPER_ARM_ERR_VALID_TIME_OUT) अणु
		समय_out = ((error_info >> CPER_ARM_ERR_TIME_OUT_SHIFT)
			    & CPER_ARM_ERR_TIME_OUT_MASK);
		अगर (समय_out)
			prपूर्णांकk("%srequest timed out\n", pfx);
	पूर्ण

	अगर (error_info & CPER_ARM_ERR_VALID_ADDRESS_SPACE) अणु
		address_space = ((error_info >> CPER_ARM_ERR_ADDRESS_SPACE_SHIFT)
				 & CPER_ARM_ERR_ADDRESS_SPACE_MASK);
		अगर (address_space < ARRAY_SIZE(arm_bus_err_addr_space_strs)) अणु
			prपूर्णांकk("%saddress space: %s\n", pfx,
			       arm_bus_err_addr_space_strs[address_space]);
		पूर्ण
	पूर्ण

	अगर (error_info & CPER_ARM_ERR_VALID_MEM_ATTRIBUTES) अणु
		mem_attributes = ((error_info >> CPER_ARM_ERR_MEM_ATTRIBUTES_SHIFT)
				  & CPER_ARM_ERR_MEM_ATTRIBUTES_MASK);
		prपूर्णांकk("%smemory access attributes:0x%x\n", pfx, mem_attributes);
	पूर्ण

	अगर (error_info & CPER_ARM_ERR_VALID_ACCESS_MODE) अणु
		access_mode = ((error_info >> CPER_ARM_ERR_ACCESS_MODE_SHIFT)
			       & CPER_ARM_ERR_ACCESS_MODE_MASK);
		अगर (access_mode)
			prपूर्णांकk("%saccess mode: normal\n", pfx);
		अन्यथा
			prपूर्णांकk("%saccess mode: secure\n", pfx);
	पूर्ण
पूर्ण

व्योम cper_prपूर्णांक_proc_arm(स्थिर अक्षर *pfx,
			 स्थिर काष्ठा cper_sec_proc_arm *proc)
अणु
	पूर्णांक i, len, max_ctx_type;
	काष्ठा cper_arm_err_info *err_info;
	काष्ठा cper_arm_ctx_info *ctx_info;
	अक्षर newpfx[64], infopfx[64];

	prपूर्णांकk("%sMIDR: 0x%016llx\n", pfx, proc->midr);

	len = proc->section_length - (माप(*proc) +
		proc->err_info_num * (माप(*err_info)));
	अगर (len < 0) अणु
		prपूर्णांकk("%ssection length: %d\n", pfx, proc->section_length);
		prपूर्णांकk("%ssection length is too small\n", pfx);
		prपूर्णांकk("%sfirmware-generated error record is incorrect\n", pfx);
		prपूर्णांकk("%sERR_INFO_NUM is %d\n", pfx, proc->err_info_num);
		वापस;
	पूर्ण

	अगर (proc->validation_bits & CPER_ARM_VALID_MPIDR)
		prपूर्णांकk("%sMultiprocessor Affinity Register (MPIDR): 0x%016llx\n",
			pfx, proc->mpidr);

	अगर (proc->validation_bits & CPER_ARM_VALID_AFFINITY_LEVEL)
		prपूर्णांकk("%serror affinity level: %d\n", pfx,
			proc->affinity_level);

	अगर (proc->validation_bits & CPER_ARM_VALID_RUNNING_STATE) अणु
		prपूर्णांकk("%srunning state: 0x%x\n", pfx, proc->running_state);
		prपूर्णांकk("%sPower State Coordination Interface state: %d\n",
			pfx, proc->psci_state);
	पूर्ण

	snम_लिखो(newpfx, माप(newpfx), "%s ", pfx);

	err_info = (काष्ठा cper_arm_err_info *)(proc + 1);
	क्रम (i = 0; i < proc->err_info_num; i++) अणु
		prपूर्णांकk("%sError info structure %d:\n", pfx, i);

		prपूर्णांकk("%snum errors: %d\n", pfx, err_info->multiple_error + 1);

		अगर (err_info->validation_bits & CPER_ARM_INFO_VALID_FLAGS) अणु
			अगर (err_info->flags & CPER_ARM_INFO_FLAGS_FIRST)
				prपूर्णांकk("%sfirst error captured\n", newpfx);
			अगर (err_info->flags & CPER_ARM_INFO_FLAGS_LAST)
				prपूर्णांकk("%slast error captured\n", newpfx);
			अगर (err_info->flags & CPER_ARM_INFO_FLAGS_PROPAGATED)
				prपूर्णांकk("%spropagated error captured\n",
				       newpfx);
			अगर (err_info->flags & CPER_ARM_INFO_FLAGS_OVERFLOW)
				prपूर्णांकk("%soverflow occurred, error info is incomplete\n",
				       newpfx);
		पूर्ण

		prपूर्णांकk("%serror_type: %d, %s\n", newpfx, err_info->type,
			err_info->type < ARRAY_SIZE(cper_proc_error_type_strs) ?
			cper_proc_error_type_strs[err_info->type] : "unknown");
		अगर (err_info->validation_bits & CPER_ARM_INFO_VALID_ERR_INFO) अणु
			prपूर्णांकk("%serror_info: 0x%016llx\n", newpfx,
			       err_info->error_info);
			snम_लिखो(infopfx, माप(infopfx), "%s ", newpfx);
			cper_prपूर्णांक_arm_err_info(infopfx, err_info->type,
						err_info->error_info);
		पूर्ण
		अगर (err_info->validation_bits & CPER_ARM_INFO_VALID_VIRT_ADDR)
			prपूर्णांकk("%svirtual fault address: 0x%016llx\n",
				newpfx, err_info->virt_fault_addr);
		अगर (err_info->validation_bits & CPER_ARM_INFO_VALID_PHYSICAL_ADDR)
			prपूर्णांकk("%sphysical fault address: 0x%016llx\n",
				newpfx, err_info->physical_fault_addr);
		err_info += 1;
	पूर्ण

	ctx_info = (काष्ठा cper_arm_ctx_info *)err_info;
	max_ctx_type = ARRAY_SIZE(arm_reg_ctx_strs) - 1;
	क्रम (i = 0; i < proc->context_info_num; i++) अणु
		पूर्णांक size = माप(*ctx_info) + ctx_info->size;

		prपूर्णांकk("%sContext info structure %d:\n", pfx, i);
		अगर (len < size) अणु
			prपूर्णांकk("%ssection length is too small\n", newpfx);
			prपूर्णांकk("%sfirmware-generated error record is incorrect\n", pfx);
			वापस;
		पूर्ण
		अगर (ctx_info->type > max_ctx_type) अणु
			prपूर्णांकk("%sInvalid context type: %d (max: %d)\n",
				newpfx, ctx_info->type, max_ctx_type);
			वापस;
		पूर्ण
		prपूर्णांकk("%sregister context type: %s\n", newpfx,
			arm_reg_ctx_strs[ctx_info->type]);
		prपूर्णांक_hex_dump(newpfx, "", DUMP_PREFIX_OFFSET, 16, 4,
				(ctx_info + 1), ctx_info->size, 0);
		len -= size;
		ctx_info = (काष्ठा cper_arm_ctx_info *)((दीर्घ)ctx_info + size);
	पूर्ण

	अगर (len > 0) अणु
		prपूर्णांकk("%sVendor specific error info has %u bytes:\n", pfx,
		       len);
		prपूर्णांक_hex_dump(newpfx, "", DUMP_PREFIX_OFFSET, 16, 4, ctx_info,
				len, true);
	पूर्ण
पूर्ण
