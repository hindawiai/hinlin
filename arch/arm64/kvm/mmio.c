<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2012 - Virtual Open Systems and Columbia University
 * Author: Christoffer Dall <c.dall@भवखोलोप्रणालीs.com>
 */

#समावेश <linux/kvm_host.h>
#समावेश <यंत्र/kvm_emulate.h>
#समावेश <trace/events/kvm.h>

#समावेश "trace.h"

व्योम kvm_mmio_ग_लिखो_buf(व्योम *buf, अचिन्हित पूर्णांक len, अचिन्हित दीर्घ data)
अणु
	व्योम *datap = शून्य;
	जोड़ अणु
		u8	byte;
		u16	hword;
		u32	word;
		u64	dword;
	पूर्ण पंचांगp;

	चयन (len) अणु
	हाल 1:
		पंचांगp.byte	= data;
		datap		= &पंचांगp.byte;
		अवरोध;
	हाल 2:
		पंचांगp.hword	= data;
		datap		= &पंचांगp.hword;
		अवरोध;
	हाल 4:
		पंचांगp.word	= data;
		datap		= &पंचांगp.word;
		अवरोध;
	हाल 8:
		पंचांगp.dword	= data;
		datap		= &पंचांगp.dword;
		अवरोध;
	पूर्ण

	स_नकल(buf, datap, len);
पूर्ण

अचिन्हित दीर्घ kvm_mmio_पढ़ो_buf(स्थिर व्योम *buf, अचिन्हित पूर्णांक len)
अणु
	अचिन्हित दीर्घ data = 0;
	जोड़ अणु
		u16	hword;
		u32	word;
		u64	dword;
	पूर्ण पंचांगp;

	चयन (len) अणु
	हाल 1:
		data = *(u8 *)buf;
		अवरोध;
	हाल 2:
		स_नकल(&पंचांगp.hword, buf, len);
		data = पंचांगp.hword;
		अवरोध;
	हाल 4:
		स_नकल(&पंचांगp.word, buf, len);
		data = पंचांगp.word;
		अवरोध;
	हाल 8:
		स_नकल(&पंचांगp.dword, buf, len);
		data = पंचांगp.dword;
		अवरोध;
	पूर्ण

	वापस data;
पूर्ण

/**
 * kvm_handle_mmio_वापस -- Handle MMIO loads after user space emulation
 *			     or in-kernel IO emulation
 *
 * @vcpu: The VCPU poपूर्णांकer
 */
पूर्णांक kvm_handle_mmio_वापस(काष्ठा kvm_vcpu *vcpu)
अणु
	अचिन्हित दीर्घ data;
	अचिन्हित पूर्णांक len;
	पूर्णांक mask;

	/* Detect an alपढ़ोy handled MMIO वापस */
	अगर (unlikely(!vcpu->mmio_needed))
		वापस 0;

	vcpu->mmio_needed = 0;

	अगर (!kvm_vcpu_dabt_isग_लिखो(vcpu)) अणु
		काष्ठा kvm_run *run = vcpu->run;

		len = kvm_vcpu_dabt_get_as(vcpu);
		data = kvm_mmio_पढ़ो_buf(run->mmio.data, len);

		अगर (kvm_vcpu_dabt_issext(vcpu) &&
		    len < माप(अचिन्हित दीर्घ)) अणु
			mask = 1U << ((len * 8) - 1);
			data = (data ^ mask) - mask;
		पूर्ण

		अगर (!kvm_vcpu_dabt_issf(vcpu))
			data = data & 0xffffffff;

		trace_kvm_mmio(KVM_TRACE_MMIO_READ, len, run->mmio.phys_addr,
			       &data);
		data = vcpu_data_host_to_guest(vcpu, data, len);
		vcpu_set_reg(vcpu, kvm_vcpu_dabt_get_rd(vcpu), data);
	पूर्ण

	/*
	 * The MMIO inकाष्ठाion is emulated and should not be re-executed
	 * in the guest.
	 */
	kvm_incr_pc(vcpu);

	वापस 0;
पूर्ण

पूर्णांक io_mem_पात(काष्ठा kvm_vcpu *vcpu, phys_addr_t fault_ipa)
अणु
	काष्ठा kvm_run *run = vcpu->run;
	अचिन्हित दीर्घ data;
	अचिन्हित दीर्घ rt;
	पूर्णांक ret;
	bool is_ग_लिखो;
	पूर्णांक len;
	u8 data_buf[8];

	/*
	 * No valid syndrome? Ask userspace क्रम help अगर it has
	 * volunteered to करो so, and bail out otherwise.
	 */
	अगर (!kvm_vcpu_dabt_isvalid(vcpu)) अणु
		अगर (vcpu->kvm->arch.वापस_nisv_io_पात_to_user) अणु
			run->निकास_reason = KVM_EXIT_ARM_NISV;
			run->arm_nisv.esr_iss = kvm_vcpu_dabt_iss_nisv_sanitized(vcpu);
			run->arm_nisv.fault_ipa = fault_ipa;
			वापस 0;
		पूर्ण

		kvm_pr_unimpl("Data abort outside memslots with no valid syndrome info\n");
		वापस -ENOSYS;
	पूर्ण

	/*
	 * Prepare MMIO operation. First decode the syndrome data we get
	 * from the CPU. Then try अगर some in-kernel emulation feels
	 * responsible, otherwise let user space करो its magic.
	 */
	is_ग_लिखो = kvm_vcpu_dabt_isग_लिखो(vcpu);
	len = kvm_vcpu_dabt_get_as(vcpu);
	rt = kvm_vcpu_dabt_get_rd(vcpu);

	अगर (is_ग_लिखो) अणु
		data = vcpu_data_guest_to_host(vcpu, vcpu_get_reg(vcpu, rt),
					       len);

		trace_kvm_mmio(KVM_TRACE_MMIO_WRITE, len, fault_ipa, &data);
		kvm_mmio_ग_लिखो_buf(data_buf, len, data);

		ret = kvm_io_bus_ग_लिखो(vcpu, KVM_MMIO_BUS, fault_ipa, len,
				       data_buf);
	पूर्ण अन्यथा अणु
		trace_kvm_mmio(KVM_TRACE_MMIO_READ_UNSATISFIED, len,
			       fault_ipa, शून्य);

		ret = kvm_io_bus_पढ़ो(vcpu, KVM_MMIO_BUS, fault_ipa, len,
				      data_buf);
	पूर्ण

	/* Now prepare kvm_run क्रम the potential वापस to userland. */
	run->mmio.is_ग_लिखो	= is_ग_लिखो;
	run->mmio.phys_addr	= fault_ipa;
	run->mmio.len		= len;
	vcpu->mmio_needed	= 1;

	अगर (!ret) अणु
		/* We handled the access successfully in the kernel. */
		अगर (!is_ग_लिखो)
			स_नकल(run->mmio.data, data_buf, len);
		vcpu->stat.mmio_निकास_kernel++;
		kvm_handle_mmio_वापस(vcpu);
		वापस 1;
	पूर्ण

	अगर (is_ग_लिखो)
		स_नकल(run->mmio.data, data_buf, len);
	vcpu->stat.mmio_निकास_user++;
	run->निकास_reason	= KVM_EXIT_MMIO;
	वापस 0;
पूर्ण
