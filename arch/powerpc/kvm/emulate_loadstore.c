<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 * Copyright IBM Corp. 2007
 * Copyright 2011 Freescale Semiconductor, Inc.
 *
 * Authors: Hollis Blanअक्षरd <hollisb@us.ibm.com>
 */

#समावेश <linux/jअगरfies.h>
#समावेश <linux/hrसमयr.h>
#समावेश <linux/types.h>
#समावेश <linux/माला.स>
#समावेश <linux/kvm_host.h>
#समावेश <linux/घड़ीchips.h>

#समावेश <यंत्र/reg.h>
#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/byteorder.h>
#समावेश <यंत्र/kvm_ppc.h>
#समावेश <यंत्र/disassemble.h>
#समावेश <यंत्र/ppc-opcode.h>
#समावेश <यंत्र/sstep.h>
#समावेश "timing.h"
#समावेश "trace.h"

#अगर_घोषित CONFIG_PPC_FPU
अटल bool kvmppc_check_fp_disabled(काष्ठा kvm_vcpu *vcpu)
अणु
	अगर (!(kvmppc_get_msr(vcpu) & MSR_FP)) अणु
		kvmppc_core_queue_fpunavail(vcpu);
		वापस true;
	पूर्ण

	वापस false;
पूर्ण
#पूर्ण_अगर /* CONFIG_PPC_FPU */

#अगर_घोषित CONFIG_VSX
अटल bool kvmppc_check_vsx_disabled(काष्ठा kvm_vcpu *vcpu)
अणु
	अगर (!(kvmppc_get_msr(vcpu) & MSR_VSX)) अणु
		kvmppc_core_queue_vsx_unavail(vcpu);
		वापस true;
	पूर्ण

	वापस false;
पूर्ण
#पूर्ण_अगर /* CONFIG_VSX */

#अगर_घोषित CONFIG_ALTIVEC
अटल bool kvmppc_check_altivec_disabled(काष्ठा kvm_vcpu *vcpu)
अणु
	अगर (!(kvmppc_get_msr(vcpu) & MSR_VEC)) अणु
		kvmppc_core_queue_vec_unavail(vcpu);
		वापस true;
	पूर्ण

	वापस false;
पूर्ण
#पूर्ण_अगर /* CONFIG_ALTIVEC */

/*
 * XXX to करो:
 * lfiwax, lfiwzx
 * vector loads and stores
 *
 * Inकाष्ठाions that trap when used on cache-inhibited mappings
 * are not emulated here: multiple and string inकाष्ठाions,
 * lq/stq, and the load-reserve/store-conditional inकाष्ठाions.
 */
पूर्णांक kvmppc_emulate_loadstore(काष्ठा kvm_vcpu *vcpu)
अणु
	u32 inst;
	क्रमागत emulation_result emulated = EMULATE_FAIL;
	पूर्णांक advance = 1;
	काष्ठा inकाष्ठाion_op op;

	/* this शेष type might be overwritten by subcategories */
	kvmppc_set_निकास_type(vcpu, EMULATED_INST_EXITS);

	emulated = kvmppc_get_last_inst(vcpu, INST_GENERIC, &inst);
	अगर (emulated != EMULATE_DONE)
		वापस emulated;

	vcpu->arch.mmio_vsx_copy_nums = 0;
	vcpu->arch.mmio_vsx_offset = 0;
	vcpu->arch.mmio_copy_type = KVMPPC_VSX_COPY_NONE;
	vcpu->arch.mmio_sp64_extend = 0;
	vcpu->arch.mmio_sign_extend = 0;
	vcpu->arch.mmio_vmx_copy_nums = 0;
	vcpu->arch.mmio_vmx_offset = 0;
	vcpu->arch.mmio_host_swabbed = 0;

	emulated = EMULATE_FAIL;
	vcpu->arch.regs.msr = vcpu->arch.shared->msr;
	अगर (analyse_instr(&op, &vcpu->arch.regs, ppc_inst(inst)) == 0) अणु
		पूर्णांक type = op.type & INSTR_TYPE_MASK;
		पूर्णांक size = GETSIZE(op.type);

		चयन (type) अणु
		हाल LOAD:  अणु
			पूर्णांक instr_byte_swap = op.type & BYTEREV;

			अगर (op.type & SIGNEXT)
				emulated = kvmppc_handle_loads(vcpu,
						op.reg, size, !instr_byte_swap);
			अन्यथा
				emulated = kvmppc_handle_load(vcpu,
						op.reg, size, !instr_byte_swap);

			अगर ((op.type & UPDATE) && (emulated != EMULATE_FAIL))
				kvmppc_set_gpr(vcpu, op.update_reg, op.ea);

			अवरोध;
		पूर्ण
#अगर_घोषित CONFIG_PPC_FPU
		हाल LOAD_FP:
			अगर (kvmppc_check_fp_disabled(vcpu))
				वापस EMULATE_DONE;

			अगर (op.type & FPCONV)
				vcpu->arch.mmio_sp64_extend = 1;

			अगर (op.type & SIGNEXT)
				emulated = kvmppc_handle_loads(vcpu,
					     KVM_MMIO_REG_FPR|op.reg, size, 1);
			अन्यथा
				emulated = kvmppc_handle_load(vcpu,
					     KVM_MMIO_REG_FPR|op.reg, size, 1);

			अगर ((op.type & UPDATE) && (emulated != EMULATE_FAIL))
				kvmppc_set_gpr(vcpu, op.update_reg, op.ea);

			अवरोध;
#पूर्ण_अगर
#अगर_घोषित CONFIG_ALTIVEC
		हाल LOAD_VMX:
			अगर (kvmppc_check_altivec_disabled(vcpu))
				वापस EMULATE_DONE;

			/* Hardware enक्रमces alignment of VMX accesses */
			vcpu->arch.vaddr_accessed &= ~((अचिन्हित दीर्घ)size - 1);
			vcpu->arch.paddr_accessed &= ~((अचिन्हित दीर्घ)size - 1);

			अगर (size == 16) अणु /* lvx */
				vcpu->arch.mmio_copy_type =
						KVMPPC_VMX_COPY_DWORD;
			पूर्ण अन्यथा अगर (size == 4) अणु /* lvewx  */
				vcpu->arch.mmio_copy_type =
						KVMPPC_VMX_COPY_WORD;
			पूर्ण अन्यथा अगर (size == 2) अणु /* lvehx  */
				vcpu->arch.mmio_copy_type =
						KVMPPC_VMX_COPY_HWORD;
			पूर्ण अन्यथा अगर (size == 1) अणु /* lvebx  */
				vcpu->arch.mmio_copy_type =
						KVMPPC_VMX_COPY_BYTE;
			पूर्ण अन्यथा
				अवरोध;

			vcpu->arch.mmio_vmx_offset =
				(vcpu->arch.vaddr_accessed & 0xf)/size;

			अगर (size == 16) अणु
				vcpu->arch.mmio_vmx_copy_nums = 2;
				emulated = kvmppc_handle_vmx_load(vcpu,
						KVM_MMIO_REG_VMX|op.reg,
						8, 1);
			पूर्ण अन्यथा अणु
				vcpu->arch.mmio_vmx_copy_nums = 1;
				emulated = kvmppc_handle_vmx_load(vcpu,
						KVM_MMIO_REG_VMX|op.reg,
						size, 1);
			पूर्ण
			अवरोध;
#पूर्ण_अगर
#अगर_घोषित CONFIG_VSX
		हाल LOAD_VSX: अणु
			पूर्णांक io_size_each;

			अगर (op.vsx_flags & VSX_CHECK_VEC) अणु
				अगर (kvmppc_check_altivec_disabled(vcpu))
					वापस EMULATE_DONE;
			पूर्ण अन्यथा अणु
				अगर (kvmppc_check_vsx_disabled(vcpu))
					वापस EMULATE_DONE;
			पूर्ण

			अगर (op.vsx_flags & VSX_FPCONV)
				vcpu->arch.mmio_sp64_extend = 1;

			अगर (op.element_size == 8)  अणु
				अगर (op.vsx_flags & VSX_SPLAT)
					vcpu->arch.mmio_copy_type =
						KVMPPC_VSX_COPY_DWORD_LOAD_DUMP;
				अन्यथा
					vcpu->arch.mmio_copy_type =
						KVMPPC_VSX_COPY_DWORD;
			पूर्ण अन्यथा अगर (op.element_size == 4) अणु
				अगर (op.vsx_flags & VSX_SPLAT)
					vcpu->arch.mmio_copy_type =
						KVMPPC_VSX_COPY_WORD_LOAD_DUMP;
				अन्यथा
					vcpu->arch.mmio_copy_type =
						KVMPPC_VSX_COPY_WORD;
			पूर्ण अन्यथा
				अवरोध;

			अगर (size < op.element_size) अणु
				/* precision convert हाल: lxsspx, etc */
				vcpu->arch.mmio_vsx_copy_nums = 1;
				io_size_each = size;
			पूर्ण अन्यथा अणु /* lxvw4x, lxvd2x, etc */
				vcpu->arch.mmio_vsx_copy_nums =
					size/op.element_size;
				io_size_each = op.element_size;
			पूर्ण

			emulated = kvmppc_handle_vsx_load(vcpu,
					KVM_MMIO_REG_VSX|op.reg, io_size_each,
					1, op.type & SIGNEXT);
			अवरोध;
		पूर्ण
#पूर्ण_अगर
		हाल STORE:
			/* अगर need byte reverse, op.val has been reversed by
			 * analyse_instr().
			 */
			emulated = kvmppc_handle_store(vcpu, op.val, size, 1);

			अगर ((op.type & UPDATE) && (emulated != EMULATE_FAIL))
				kvmppc_set_gpr(vcpu, op.update_reg, op.ea);

			अवरोध;
#अगर_घोषित CONFIG_PPC_FPU
		हाल STORE_FP:
			अगर (kvmppc_check_fp_disabled(vcpu))
				वापस EMULATE_DONE;

			/* The FP रेजिस्टरs need to be flushed so that
			 * kvmppc_handle_store() can पढ़ो actual FP vals
			 * from vcpu->arch.
			 */
			अगर (vcpu->kvm->arch.kvm_ops->giveup_ext)
				vcpu->kvm->arch.kvm_ops->giveup_ext(vcpu,
						MSR_FP);

			अगर (op.type & FPCONV)
				vcpu->arch.mmio_sp64_extend = 1;

			emulated = kvmppc_handle_store(vcpu,
					VCPU_FPR(vcpu, op.reg), size, 1);

			अगर ((op.type & UPDATE) && (emulated != EMULATE_FAIL))
				kvmppc_set_gpr(vcpu, op.update_reg, op.ea);

			अवरोध;
#पूर्ण_अगर
#अगर_घोषित CONFIG_ALTIVEC
		हाल STORE_VMX:
			अगर (kvmppc_check_altivec_disabled(vcpu))
				वापस EMULATE_DONE;

			/* Hardware enक्रमces alignment of VMX accesses. */
			vcpu->arch.vaddr_accessed &= ~((अचिन्हित दीर्घ)size - 1);
			vcpu->arch.paddr_accessed &= ~((अचिन्हित दीर्घ)size - 1);

			अगर (vcpu->kvm->arch.kvm_ops->giveup_ext)
				vcpu->kvm->arch.kvm_ops->giveup_ext(vcpu,
						MSR_VEC);
			अगर (size == 16) अणु /* stvx */
				vcpu->arch.mmio_copy_type =
						KVMPPC_VMX_COPY_DWORD;
			पूर्ण अन्यथा अगर (size == 4) अणु /* stvewx  */
				vcpu->arch.mmio_copy_type =
						KVMPPC_VMX_COPY_WORD;
			पूर्ण अन्यथा अगर (size == 2) अणु /* stvehx  */
				vcpu->arch.mmio_copy_type =
						KVMPPC_VMX_COPY_HWORD;
			पूर्ण अन्यथा अगर (size == 1) अणु /* stvebx  */
				vcpu->arch.mmio_copy_type =
						KVMPPC_VMX_COPY_BYTE;
			पूर्ण अन्यथा
				अवरोध;

			vcpu->arch.mmio_vmx_offset =
				(vcpu->arch.vaddr_accessed & 0xf)/size;

			अगर (size == 16) अणु
				vcpu->arch.mmio_vmx_copy_nums = 2;
				emulated = kvmppc_handle_vmx_store(vcpu,
						op.reg, 8, 1);
			पूर्ण अन्यथा अणु
				vcpu->arch.mmio_vmx_copy_nums = 1;
				emulated = kvmppc_handle_vmx_store(vcpu,
						op.reg, size, 1);
			पूर्ण

			अवरोध;
#पूर्ण_अगर
#अगर_घोषित CONFIG_VSX
		हाल STORE_VSX: अणु
			पूर्णांक io_size_each;

			अगर (op.vsx_flags & VSX_CHECK_VEC) अणु
				अगर (kvmppc_check_altivec_disabled(vcpu))
					वापस EMULATE_DONE;
			पूर्ण अन्यथा अणु
				अगर (kvmppc_check_vsx_disabled(vcpu))
					वापस EMULATE_DONE;
			पूर्ण

			अगर (vcpu->kvm->arch.kvm_ops->giveup_ext)
				vcpu->kvm->arch.kvm_ops->giveup_ext(vcpu,
						MSR_VSX);

			अगर (op.vsx_flags & VSX_FPCONV)
				vcpu->arch.mmio_sp64_extend = 1;

			अगर (op.element_size == 8)
				vcpu->arch.mmio_copy_type =
						KVMPPC_VSX_COPY_DWORD;
			अन्यथा अगर (op.element_size == 4)
				vcpu->arch.mmio_copy_type =
						KVMPPC_VSX_COPY_WORD;
			अन्यथा
				अवरोध;

			अगर (size < op.element_size) अणु
				/* precise conversion हाल, like stxsspx */
				vcpu->arch.mmio_vsx_copy_nums = 1;
				io_size_each = size;
			पूर्ण अन्यथा अणु /* stxvw4x, stxvd2x, etc */
				vcpu->arch.mmio_vsx_copy_nums =
						size/op.element_size;
				io_size_each = op.element_size;
			पूर्ण

			emulated = kvmppc_handle_vsx_store(vcpu,
					op.reg, io_size_each, 1);
			अवरोध;
		पूर्ण
#पूर्ण_अगर
		हाल CACHEOP:
			/* Do nothing. The guest is perक्रमming dcbi because
			 * hardware DMA is not snooped by the dcache, but
			 * emulated DMA either goes through the dcache as
			 * normal ग_लिखोs, or the host kernel has handled dcache
			 * coherence.
			 */
			emulated = EMULATE_DONE;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (emulated == EMULATE_FAIL) अणु
		advance = 0;
		kvmppc_core_queue_program(vcpu, 0);
	पूर्ण

	trace_kvm_ppc_instr(inst, kvmppc_get_pc(vcpu), emulated);

	/* Advance past emulated inकाष्ठाion. */
	अगर (advance)
		kvmppc_set_pc(vcpu, kvmppc_get_pc(vcpu) + 4);

	वापस emulated;
पूर्ण
