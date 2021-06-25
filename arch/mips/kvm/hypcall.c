<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * KVM/MIPS: Hypercall handling.
 *
 * Copyright (C) 2015  Imagination Technologies Ltd.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/kvm_host.h>
#समावेश <linux/kvm_para.h>

#घोषणा MAX_HYPCALL_ARGS	4

क्रमागत emulation_result kvm_mips_emul_hypcall(काष्ठा kvm_vcpu *vcpu,
					    जोड़ mips_inकाष्ठाion inst)
अणु
	अचिन्हित पूर्णांक code = (inst.co_क्रमmat.code >> 5) & 0x3ff;

	kvm_debug("[%#lx] HYPCALL %#03x\n", vcpu->arch.pc, code);

	चयन (code) अणु
	हाल 0:
		वापस EMULATE_HYPERCALL;
	शेष:
		वापस EMULATE_FAIL;
	पूर्ण;
पूर्ण

अटल पूर्णांक kvm_mips_hypercall(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ num,
			      स्थिर अचिन्हित दीर्घ *args, अचिन्हित दीर्घ *hret)
अणु
	/* Report unimplemented hypercall to guest */
	*hret = -KVM_ENOSYS;
	वापस RESUME_GUEST;
पूर्ण

पूर्णांक kvm_mips_handle_hypcall(काष्ठा kvm_vcpu *vcpu)
अणु
	अचिन्हित दीर्घ num, args[MAX_HYPCALL_ARGS];

	/* पढ़ो hypcall number and arguments */
	num = vcpu->arch.gprs[2];	/* v0 */
	args[0] = vcpu->arch.gprs[4];	/* a0 */
	args[1] = vcpu->arch.gprs[5];	/* a1 */
	args[2] = vcpu->arch.gprs[6];	/* a2 */
	args[3] = vcpu->arch.gprs[7];	/* a3 */

	वापस kvm_mips_hypercall(vcpu, num,
				  args, &vcpu->arch.gprs[2] /* v0 */);
पूर्ण
