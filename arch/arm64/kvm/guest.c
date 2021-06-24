<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2012,2013 - ARM Ltd
 * Author: Marc Zyngier <marc.zyngier@arm.com>
 *
 * Derived from arch/arm/kvm/guest.c:
 * Copyright (C) 2012 - Virtual Open Systems and Columbia University
 * Author: Christoffer Dall <c.dall@भवखोलोप्रणालीs.com>
 */

#समावेश <linux/bits.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/err.h>
#समावेश <linux/nospec.h>
#समावेश <linux/kvm_host.h>
#समावेश <linux/module.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/माला.स>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/fs.h>
#समावेश <kvm/arm_psci.h>
#समावेश <यंत्र/cputype.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/fpsimd.h>
#समावेश <यंत्र/kvm.h>
#समावेश <यंत्र/kvm_emulate.h>
#समावेश <यंत्र/sigcontext.h>

#समावेश "trace.h"

काष्ठा kvm_stats_debugfs_item debugfs_entries[] = अणु
	VCPU_STAT("halt_successful_poll", halt_successful_poll),
	VCPU_STAT("halt_attempted_poll", halt_attempted_poll),
	VCPU_STAT("halt_poll_invalid", halt_poll_invalid),
	VCPU_STAT("halt_wakeup", halt_wakeup),
	VCPU_STAT("hvc_exit_stat", hvc_निकास_stat),
	VCPU_STAT("wfe_exit_stat", wfe_निकास_stat),
	VCPU_STAT("wfi_exit_stat", wfi_निकास_stat),
	VCPU_STAT("mmio_exit_user", mmio_निकास_user),
	VCPU_STAT("mmio_exit_kernel", mmio_निकास_kernel),
	VCPU_STAT("exits", निकासs),
	VCPU_STAT("halt_poll_success_ns", halt_poll_success_ns),
	VCPU_STAT("halt_poll_fail_ns", halt_poll_fail_ns),
	अणु शून्य पूर्ण
पूर्ण;

अटल bool core_reg_offset_is_vreg(u64 off)
अणु
	वापस off >= KVM_REG_ARM_CORE_REG(fp_regs.vregs) &&
		off < KVM_REG_ARM_CORE_REG(fp_regs.fpsr);
पूर्ण

अटल u64 core_reg_offset_from_id(u64 id)
अणु
	वापस id & ~(KVM_REG_ARCH_MASK | KVM_REG_SIZE_MASK | KVM_REG_ARM_CORE);
पूर्ण

अटल पूर्णांक core_reg_size_from_offset(स्थिर काष्ठा kvm_vcpu *vcpu, u64 off)
अणु
	पूर्णांक size;

	चयन (off) अणु
	हाल KVM_REG_ARM_CORE_REG(regs.regs[0]) ...
	     KVM_REG_ARM_CORE_REG(regs.regs[30]):
	हाल KVM_REG_ARM_CORE_REG(regs.sp):
	हाल KVM_REG_ARM_CORE_REG(regs.pc):
	हाल KVM_REG_ARM_CORE_REG(regs.pstate):
	हाल KVM_REG_ARM_CORE_REG(sp_el1):
	हाल KVM_REG_ARM_CORE_REG(elr_el1):
	हाल KVM_REG_ARM_CORE_REG(spsr[0]) ...
	     KVM_REG_ARM_CORE_REG(spsr[KVM_NR_SPSR - 1]):
		size = माप(__u64);
		अवरोध;

	हाल KVM_REG_ARM_CORE_REG(fp_regs.vregs[0]) ...
	     KVM_REG_ARM_CORE_REG(fp_regs.vregs[31]):
		size = माप(__uपूर्णांक128_t);
		अवरोध;

	हाल KVM_REG_ARM_CORE_REG(fp_regs.fpsr):
	हाल KVM_REG_ARM_CORE_REG(fp_regs.fpcr):
		size = माप(__u32);
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (!IS_ALIGNED(off, size / माप(__u32)))
		वापस -EINVAL;

	/*
	 * The KVM_REG_ARM64_SVE regs must be used instead of
	 * KVM_REG_ARM_CORE क्रम accessing the FPSIMD V-रेजिस्टरs on
	 * SVE-enabled vcpus:
	 */
	अगर (vcpu_has_sve(vcpu) && core_reg_offset_is_vreg(off))
		वापस -EINVAL;

	वापस size;
पूर्ण

अटल व्योम *core_reg_addr(काष्ठा kvm_vcpu *vcpu, स्थिर काष्ठा kvm_one_reg *reg)
अणु
	u64 off = core_reg_offset_from_id(reg->id);
	पूर्णांक size = core_reg_size_from_offset(vcpu, off);

	अगर (size < 0)
		वापस शून्य;

	अगर (KVM_REG_SIZE(reg->id) != size)
		वापस शून्य;

	चयन (off) अणु
	हाल KVM_REG_ARM_CORE_REG(regs.regs[0]) ...
	     KVM_REG_ARM_CORE_REG(regs.regs[30]):
		off -= KVM_REG_ARM_CORE_REG(regs.regs[0]);
		off /= 2;
		वापस &vcpu->arch.ctxt.regs.regs[off];

	हाल KVM_REG_ARM_CORE_REG(regs.sp):
		वापस &vcpu->arch.ctxt.regs.sp;

	हाल KVM_REG_ARM_CORE_REG(regs.pc):
		वापस &vcpu->arch.ctxt.regs.pc;

	हाल KVM_REG_ARM_CORE_REG(regs.pstate):
		वापस &vcpu->arch.ctxt.regs.pstate;

	हाल KVM_REG_ARM_CORE_REG(sp_el1):
		वापस __ctxt_sys_reg(&vcpu->arch.ctxt, SP_EL1);

	हाल KVM_REG_ARM_CORE_REG(elr_el1):
		वापस __ctxt_sys_reg(&vcpu->arch.ctxt, ELR_EL1);

	हाल KVM_REG_ARM_CORE_REG(spsr[KVM_SPSR_EL1]):
		वापस __ctxt_sys_reg(&vcpu->arch.ctxt, SPSR_EL1);

	हाल KVM_REG_ARM_CORE_REG(spsr[KVM_SPSR_ABT]):
		वापस &vcpu->arch.ctxt.spsr_abt;

	हाल KVM_REG_ARM_CORE_REG(spsr[KVM_SPSR_UND]):
		वापस &vcpu->arch.ctxt.spsr_und;

	हाल KVM_REG_ARM_CORE_REG(spsr[KVM_SPSR_IRQ]):
		वापस &vcpu->arch.ctxt.spsr_irq;

	हाल KVM_REG_ARM_CORE_REG(spsr[KVM_SPSR_FIQ]):
		वापस &vcpu->arch.ctxt.spsr_fiq;

	हाल KVM_REG_ARM_CORE_REG(fp_regs.vregs[0]) ...
	     KVM_REG_ARM_CORE_REG(fp_regs.vregs[31]):
		off -= KVM_REG_ARM_CORE_REG(fp_regs.vregs[0]);
		off /= 4;
		वापस &vcpu->arch.ctxt.fp_regs.vregs[off];

	हाल KVM_REG_ARM_CORE_REG(fp_regs.fpsr):
		वापस &vcpu->arch.ctxt.fp_regs.fpsr;

	हाल KVM_REG_ARM_CORE_REG(fp_regs.fpcr):
		वापस &vcpu->arch.ctxt.fp_regs.fpcr;

	शेष:
		वापस शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक get_core_reg(काष्ठा kvm_vcpu *vcpu, स्थिर काष्ठा kvm_one_reg *reg)
अणु
	/*
	 * Because the kvm_regs काष्ठाure is a mix of 32, 64 and
	 * 128bit fields, we index it as अगर it was a 32bit
	 * array. Hence below, nr_regs is the number of entries, and
	 * off the index in the "array".
	 */
	__u32 __user *uaddr = (__u32 __user *)(अचिन्हित दीर्घ)reg->addr;
	पूर्णांक nr_regs = माप(काष्ठा kvm_regs) / माप(__u32);
	व्योम *addr;
	u32 off;

	/* Our ID is an index पूर्णांकo the kvm_regs काष्ठा. */
	off = core_reg_offset_from_id(reg->id);
	अगर (off >= nr_regs ||
	    (off + (KVM_REG_SIZE(reg->id) / माप(__u32))) >= nr_regs)
		वापस -ENOENT;

	addr = core_reg_addr(vcpu, reg);
	अगर (!addr)
		वापस -EINVAL;

	अगर (copy_to_user(uaddr, addr, KVM_REG_SIZE(reg->id)))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल पूर्णांक set_core_reg(काष्ठा kvm_vcpu *vcpu, स्थिर काष्ठा kvm_one_reg *reg)
अणु
	__u32 __user *uaddr = (__u32 __user *)(अचिन्हित दीर्घ)reg->addr;
	पूर्णांक nr_regs = माप(काष्ठा kvm_regs) / माप(__u32);
	__uपूर्णांक128_t पंचांगp;
	व्योम *valp = &पंचांगp, *addr;
	u64 off;
	पूर्णांक err = 0;

	/* Our ID is an index पूर्णांकo the kvm_regs काष्ठा. */
	off = core_reg_offset_from_id(reg->id);
	अगर (off >= nr_regs ||
	    (off + (KVM_REG_SIZE(reg->id) / माप(__u32))) >= nr_regs)
		वापस -ENOENT;

	addr = core_reg_addr(vcpu, reg);
	अगर (!addr)
		वापस -EINVAL;

	अगर (KVM_REG_SIZE(reg->id) > माप(पंचांगp))
		वापस -EINVAL;

	अगर (copy_from_user(valp, uaddr, KVM_REG_SIZE(reg->id))) अणु
		err = -EFAULT;
		जाओ out;
	पूर्ण

	अगर (off == KVM_REG_ARM_CORE_REG(regs.pstate)) अणु
		u64 mode = (*(u64 *)valp) & PSR_AA32_MODE_MASK;
		चयन (mode) अणु
		हाल PSR_AA32_MODE_USR:
			अगर (!प्रणाली_supports_32bit_el0())
				वापस -EINVAL;
			अवरोध;
		हाल PSR_AA32_MODE_FIQ:
		हाल PSR_AA32_MODE_IRQ:
		हाल PSR_AA32_MODE_SVC:
		हाल PSR_AA32_MODE_ABT:
		हाल PSR_AA32_MODE_UND:
			अगर (!vcpu_el1_is_32bit(vcpu))
				वापस -EINVAL;
			अवरोध;
		हाल PSR_MODE_EL0t:
		हाल PSR_MODE_EL1t:
		हाल PSR_MODE_EL1h:
			अगर (vcpu_el1_is_32bit(vcpu))
				वापस -EINVAL;
			अवरोध;
		शेष:
			err = -EINVAL;
			जाओ out;
		पूर्ण
	पूर्ण

	स_नकल(addr, valp, KVM_REG_SIZE(reg->id));

	अगर (*vcpu_cpsr(vcpu) & PSR_MODE32_BIT) अणु
		पूर्णांक i, nr_reg;

		चयन (*vcpu_cpsr(vcpu)) अणु
		/*
		 * Either we are dealing with user mode, and only the
		 * first 15 रेजिस्टरs (+ PC) must be narrowed to 32bit.
		 * AArch32 r0-r14 conveniently map to AArch64 x0-x14.
		 */
		हाल PSR_AA32_MODE_USR:
		हाल PSR_AA32_MODE_SYS:
			nr_reg = 15;
			अवरोध;

		/*
		 * Otherwide, this is a priviledged mode, and *all* the
		 * रेजिस्टरs must be narrowed to 32bit.
		 */
		शेष:
			nr_reg = 31;
			अवरोध;
		पूर्ण

		क्रम (i = 0; i < nr_reg; i++)
			vcpu_set_reg(vcpu, i, (u32)vcpu_get_reg(vcpu, i));

		*vcpu_pc(vcpu) = (u32)*vcpu_pc(vcpu);
	पूर्ण
out:
	वापस err;
पूर्ण

#घोषणा vq_word(vq) (((vq) - SVE_VQ_MIN) / 64)
#घोषणा vq_mask(vq) ((u64)1 << ((vq) - SVE_VQ_MIN) % 64)
#घोषणा vq_present(vqs, vq) (!!((vqs)[vq_word(vq)] & vq_mask(vq)))

अटल पूर्णांक get_sve_vls(काष्ठा kvm_vcpu *vcpu, स्थिर काष्ठा kvm_one_reg *reg)
अणु
	अचिन्हित पूर्णांक max_vq, vq;
	u64 vqs[KVM_ARM64_SVE_VLS_WORDS];

	अगर (!vcpu_has_sve(vcpu))
		वापस -ENOENT;

	अगर (WARN_ON(!sve_vl_valid(vcpu->arch.sve_max_vl)))
		वापस -EINVAL;

	स_रखो(vqs, 0, माप(vqs));

	max_vq = vcpu_sve_max_vq(vcpu);
	क्रम (vq = SVE_VQ_MIN; vq <= max_vq; ++vq)
		अगर (sve_vq_available(vq))
			vqs[vq_word(vq)] |= vq_mask(vq);

	अगर (copy_to_user((व्योम __user *)reg->addr, vqs, माप(vqs)))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल पूर्णांक set_sve_vls(काष्ठा kvm_vcpu *vcpu, स्थिर काष्ठा kvm_one_reg *reg)
अणु
	अचिन्हित पूर्णांक max_vq, vq;
	u64 vqs[KVM_ARM64_SVE_VLS_WORDS];

	अगर (!vcpu_has_sve(vcpu))
		वापस -ENOENT;

	अगर (kvm_arm_vcpu_sve_finalized(vcpu))
		वापस -EPERM; /* too late! */

	अगर (WARN_ON(vcpu->arch.sve_state))
		वापस -EINVAL;

	अगर (copy_from_user(vqs, (स्थिर व्योम __user *)reg->addr, माप(vqs)))
		वापस -EFAULT;

	max_vq = 0;
	क्रम (vq = SVE_VQ_MIN; vq <= SVE_VQ_MAX; ++vq)
		अगर (vq_present(vqs, vq))
			max_vq = vq;

	अगर (max_vq > sve_vq_from_vl(kvm_sve_max_vl))
		वापस -EINVAL;

	/*
	 * Vector lengths supported by the host can't currently be
	 * hidden from the guest inभागidually: instead we can only set a
	 * maximum via ZCR_EL2.LEN.  So, make sure the available vector
	 * lengths match the set requested exactly up to the requested
	 * maximum:
	 */
	क्रम (vq = SVE_VQ_MIN; vq <= max_vq; ++vq)
		अगर (vq_present(vqs, vq) != sve_vq_available(vq))
			वापस -EINVAL;

	/* Can't run with no vector lengths at all: */
	अगर (max_vq < SVE_VQ_MIN)
		वापस -EINVAL;

	/* vcpu->arch.sve_state will be alloc'd by kvm_vcpu_finalize_sve() */
	vcpu->arch.sve_max_vl = sve_vl_from_vq(max_vq);

	वापस 0;
पूर्ण

#घोषणा SVE_REG_SLICE_SHIFT	0
#घोषणा SVE_REG_SLICE_BITS	5
#घोषणा SVE_REG_ID_SHIFT	(SVE_REG_SLICE_SHIFT + SVE_REG_SLICE_BITS)
#घोषणा SVE_REG_ID_BITS		5

#घोषणा SVE_REG_SLICE_MASK					\
	GENMASK(SVE_REG_SLICE_SHIFT + SVE_REG_SLICE_BITS - 1,	\
		SVE_REG_SLICE_SHIFT)
#घोषणा SVE_REG_ID_MASK							\
	GENMASK(SVE_REG_ID_SHIFT + SVE_REG_ID_BITS - 1, SVE_REG_ID_SHIFT)

#घोषणा SVE_NUM_SLICES (1 << SVE_REG_SLICE_BITS)

#घोषणा KVM_SVE_ZREG_SIZE KVM_REG_SIZE(KVM_REG_ARM64_SVE_ZREG(0, 0))
#घोषणा KVM_SVE_PREG_SIZE KVM_REG_SIZE(KVM_REG_ARM64_SVE_PREG(0, 0))

/*
 * Number of रेजिस्टर slices required to cover each whole SVE रेजिस्टर.
 * NOTE: Only the first slice every exists, क्रम now.
 * If you are tempted to modअगरy this, you must also rework sve_reg_to_region()
 * to match:
 */
#घोषणा vcpu_sve_slices(vcpu) 1

/* Bounds of a single SVE रेजिस्टर slice within vcpu->arch.sve_state */
काष्ठा sve_state_reg_region अणु
	अचिन्हित पूर्णांक koffset;	/* offset पूर्णांकo sve_state in kernel memory */
	अचिन्हित पूर्णांक klen;	/* length in kernel memory */
	अचिन्हित पूर्णांक upad;	/* extra trailing padding in user memory */
पूर्ण;

/*
 * Validate SVE रेजिस्टर ID and get sanitised bounds क्रम user/kernel SVE
 * रेजिस्टर copy
 */
अटल पूर्णांक sve_reg_to_region(काष्ठा sve_state_reg_region *region,
			     काष्ठा kvm_vcpu *vcpu,
			     स्थिर काष्ठा kvm_one_reg *reg)
अणु
	/* reg ID ranges क्रम Z- रेजिस्टरs */
	स्थिर u64 zreg_id_min = KVM_REG_ARM64_SVE_ZREG(0, 0);
	स्थिर u64 zreg_id_max = KVM_REG_ARM64_SVE_ZREG(SVE_NUM_ZREGS - 1,
						       SVE_NUM_SLICES - 1);

	/* reg ID ranges क्रम P- रेजिस्टरs and FFR (which are contiguous) */
	स्थिर u64 preg_id_min = KVM_REG_ARM64_SVE_PREG(0, 0);
	स्थिर u64 preg_id_max = KVM_REG_ARM64_SVE_FFR(SVE_NUM_SLICES - 1);

	अचिन्हित पूर्णांक vq;
	अचिन्हित पूर्णांक reg_num;

	अचिन्हित पूर्णांक reqoffset, reqlen; /* User-requested offset and length */
	अचिन्हित पूर्णांक maxlen; /* Maximum permitted length */

	माप_प्रकार sve_state_size;

	स्थिर u64 last_preg_id = KVM_REG_ARM64_SVE_PREG(SVE_NUM_PREGS - 1,
							SVE_NUM_SLICES - 1);

	/* Verअगरy that the P-regs and FFR really करो have contiguous IDs: */
	BUILD_BUG_ON(KVM_REG_ARM64_SVE_FFR(0) != last_preg_id + 1);

	/* Verअगरy that we match the UAPI header: */
	BUILD_BUG_ON(SVE_NUM_SLICES != KVM_ARM64_SVE_MAX_SLICES);

	reg_num = (reg->id & SVE_REG_ID_MASK) >> SVE_REG_ID_SHIFT;

	अगर (reg->id >= zreg_id_min && reg->id <= zreg_id_max) अणु
		अगर (!vcpu_has_sve(vcpu) || (reg->id & SVE_REG_SLICE_MASK) > 0)
			वापस -ENOENT;

		vq = vcpu_sve_max_vq(vcpu);

		reqoffset = SVE_SIG_ZREG_OFFSET(vq, reg_num) -
				SVE_SIG_REGS_OFFSET;
		reqlen = KVM_SVE_ZREG_SIZE;
		maxlen = SVE_SIG_ZREG_SIZE(vq);
	पूर्ण अन्यथा अगर (reg->id >= preg_id_min && reg->id <= preg_id_max) अणु
		अगर (!vcpu_has_sve(vcpu) || (reg->id & SVE_REG_SLICE_MASK) > 0)
			वापस -ENOENT;

		vq = vcpu_sve_max_vq(vcpu);

		reqoffset = SVE_SIG_PREG_OFFSET(vq, reg_num) -
				SVE_SIG_REGS_OFFSET;
		reqlen = KVM_SVE_PREG_SIZE;
		maxlen = SVE_SIG_PREG_SIZE(vq);
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	sve_state_size = vcpu_sve_state_size(vcpu);
	अगर (WARN_ON(!sve_state_size))
		वापस -EINVAL;

	region->koffset = array_index_nospec(reqoffset, sve_state_size);
	region->klen = min(maxlen, reqlen);
	region->upad = reqlen - region->klen;

	वापस 0;
पूर्ण

अटल पूर्णांक get_sve_reg(काष्ठा kvm_vcpu *vcpu, स्थिर काष्ठा kvm_one_reg *reg)
अणु
	पूर्णांक ret;
	काष्ठा sve_state_reg_region region;
	अक्षर __user *uptr = (अक्षर __user *)reg->addr;

	/* Handle the KVM_REG_ARM64_SVE_VLS pseuकरो-reg as a special हाल: */
	अगर (reg->id == KVM_REG_ARM64_SVE_VLS)
		वापस get_sve_vls(vcpu, reg);

	/* Try to पूर्णांकerpret reg ID as an architectural SVE रेजिस्टर... */
	ret = sve_reg_to_region(&region, vcpu, reg);
	अगर (ret)
		वापस ret;

	अगर (!kvm_arm_vcpu_sve_finalized(vcpu))
		वापस -EPERM;

	अगर (copy_to_user(uptr, vcpu->arch.sve_state + region.koffset,
			 region.klen) ||
	    clear_user(uptr + region.klen, region.upad))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल पूर्णांक set_sve_reg(काष्ठा kvm_vcpu *vcpu, स्थिर काष्ठा kvm_one_reg *reg)
अणु
	पूर्णांक ret;
	काष्ठा sve_state_reg_region region;
	स्थिर अक्षर __user *uptr = (स्थिर अक्षर __user *)reg->addr;

	/* Handle the KVM_REG_ARM64_SVE_VLS pseuकरो-reg as a special हाल: */
	अगर (reg->id == KVM_REG_ARM64_SVE_VLS)
		वापस set_sve_vls(vcpu, reg);

	/* Try to पूर्णांकerpret reg ID as an architectural SVE रेजिस्टर... */
	ret = sve_reg_to_region(&region, vcpu, reg);
	अगर (ret)
		वापस ret;

	अगर (!kvm_arm_vcpu_sve_finalized(vcpu))
		वापस -EPERM;

	अगर (copy_from_user(vcpu->arch.sve_state + region.koffset, uptr,
			   region.klen))
		वापस -EFAULT;

	वापस 0;
पूर्ण

पूर्णांक kvm_arch_vcpu_ioctl_get_regs(काष्ठा kvm_vcpu *vcpu, काष्ठा kvm_regs *regs)
अणु
	वापस -EINVAL;
पूर्ण

पूर्णांक kvm_arch_vcpu_ioctl_set_regs(काष्ठा kvm_vcpu *vcpu, काष्ठा kvm_regs *regs)
अणु
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक copy_core_reg_indices(स्थिर काष्ठा kvm_vcpu *vcpu,
				 u64 __user *uindices)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक n = 0;

	क्रम (i = 0; i < माप(काष्ठा kvm_regs) / माप(__u32); i++) अणु
		u64 reg = KVM_REG_ARM64 | KVM_REG_ARM_CORE | i;
		पूर्णांक size = core_reg_size_from_offset(vcpu, i);

		अगर (size < 0)
			जारी;

		चयन (size) अणु
		हाल माप(__u32):
			reg |= KVM_REG_SIZE_U32;
			अवरोध;

		हाल माप(__u64):
			reg |= KVM_REG_SIZE_U64;
			अवरोध;

		हाल माप(__uपूर्णांक128_t):
			reg |= KVM_REG_SIZE_U128;
			अवरोध;

		शेष:
			WARN_ON(1);
			जारी;
		पूर्ण

		अगर (uindices) अणु
			अगर (put_user(reg, uindices))
				वापस -EFAULT;
			uindices++;
		पूर्ण

		n++;
	पूर्ण

	वापस n;
पूर्ण

अटल अचिन्हित दीर्घ num_core_regs(स्थिर काष्ठा kvm_vcpu *vcpu)
अणु
	वापस copy_core_reg_indices(vcpu, शून्य);
पूर्ण

/**
 * ARM64 versions of the TIMER रेजिस्टरs, always available on arm64
 */

#घोषणा NUM_TIMER_REGS 3

अटल bool is_समयr_reg(u64 index)
अणु
	चयन (index) अणु
	हाल KVM_REG_ARM_TIMER_CTL:
	हाल KVM_REG_ARM_TIMER_CNT:
	हाल KVM_REG_ARM_TIMER_CVAL:
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल पूर्णांक copy_समयr_indices(काष्ठा kvm_vcpu *vcpu, u64 __user *uindices)
अणु
	अगर (put_user(KVM_REG_ARM_TIMER_CTL, uindices))
		वापस -EFAULT;
	uindices++;
	अगर (put_user(KVM_REG_ARM_TIMER_CNT, uindices))
		वापस -EFAULT;
	uindices++;
	अगर (put_user(KVM_REG_ARM_TIMER_CVAL, uindices))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल पूर्णांक set_समयr_reg(काष्ठा kvm_vcpu *vcpu, स्थिर काष्ठा kvm_one_reg *reg)
अणु
	व्योम __user *uaddr = (व्योम __user *)(दीर्घ)reg->addr;
	u64 val;
	पूर्णांक ret;

	ret = copy_from_user(&val, uaddr, KVM_REG_SIZE(reg->id));
	अगर (ret != 0)
		वापस -EFAULT;

	वापस kvm_arm_समयr_set_reg(vcpu, reg->id, val);
पूर्ण

अटल पूर्णांक get_समयr_reg(काष्ठा kvm_vcpu *vcpu, स्थिर काष्ठा kvm_one_reg *reg)
अणु
	व्योम __user *uaddr = (व्योम __user *)(दीर्घ)reg->addr;
	u64 val;

	val = kvm_arm_समयr_get_reg(vcpu, reg->id);
	वापस copy_to_user(uaddr, &val, KVM_REG_SIZE(reg->id)) ? -EFAULT : 0;
पूर्ण

अटल अचिन्हित दीर्घ num_sve_regs(स्थिर काष्ठा kvm_vcpu *vcpu)
अणु
	स्थिर अचिन्हित पूर्णांक slices = vcpu_sve_slices(vcpu);

	अगर (!vcpu_has_sve(vcpu))
		वापस 0;

	/* Policed by KVM_GET_REG_LIST: */
	WARN_ON(!kvm_arm_vcpu_sve_finalized(vcpu));

	वापस slices * (SVE_NUM_PREGS + SVE_NUM_ZREGS + 1 /* FFR */)
		+ 1; /* KVM_REG_ARM64_SVE_VLS */
पूर्ण

अटल पूर्णांक copy_sve_reg_indices(स्थिर काष्ठा kvm_vcpu *vcpu,
				u64 __user *uindices)
अणु
	स्थिर अचिन्हित पूर्णांक slices = vcpu_sve_slices(vcpu);
	u64 reg;
	अचिन्हित पूर्णांक i, n;
	पूर्णांक num_regs = 0;

	अगर (!vcpu_has_sve(vcpu))
		वापस 0;

	/* Policed by KVM_GET_REG_LIST: */
	WARN_ON(!kvm_arm_vcpu_sve_finalized(vcpu));

	/*
	 * Enumerate this first, so that userspace can save/restore in
	 * the order reported by KVM_GET_REG_LIST:
	 */
	reg = KVM_REG_ARM64_SVE_VLS;
	अगर (put_user(reg, uindices++))
		वापस -EFAULT;
	++num_regs;

	क्रम (i = 0; i < slices; i++) अणु
		क्रम (n = 0; n < SVE_NUM_ZREGS; n++) अणु
			reg = KVM_REG_ARM64_SVE_ZREG(n, i);
			अगर (put_user(reg, uindices++))
				वापस -EFAULT;
			num_regs++;
		पूर्ण

		क्रम (n = 0; n < SVE_NUM_PREGS; n++) अणु
			reg = KVM_REG_ARM64_SVE_PREG(n, i);
			अगर (put_user(reg, uindices++))
				वापस -EFAULT;
			num_regs++;
		पूर्ण

		reg = KVM_REG_ARM64_SVE_FFR(i);
		अगर (put_user(reg, uindices++))
			वापस -EFAULT;
		num_regs++;
	पूर्ण

	वापस num_regs;
पूर्ण

/**
 * kvm_arm_num_regs - how many रेजिस्टरs करो we present via KVM_GET_ONE_REG
 *
 * This is क्रम all रेजिस्टरs.
 */
अचिन्हित दीर्घ kvm_arm_num_regs(काष्ठा kvm_vcpu *vcpu)
अणु
	अचिन्हित दीर्घ res = 0;

	res += num_core_regs(vcpu);
	res += num_sve_regs(vcpu);
	res += kvm_arm_num_sys_reg_descs(vcpu);
	res += kvm_arm_get_fw_num_regs(vcpu);
	res += NUM_TIMER_REGS;

	वापस res;
पूर्ण

/**
 * kvm_arm_copy_reg_indices - get indices of all रेजिस्टरs.
 *
 * We करो core रेजिस्टरs right here, then we append प्रणाली regs.
 */
पूर्णांक kvm_arm_copy_reg_indices(काष्ठा kvm_vcpu *vcpu, u64 __user *uindices)
अणु
	पूर्णांक ret;

	ret = copy_core_reg_indices(vcpu, uindices);
	अगर (ret < 0)
		वापस ret;
	uindices += ret;

	ret = copy_sve_reg_indices(vcpu, uindices);
	अगर (ret < 0)
		वापस ret;
	uindices += ret;

	ret = kvm_arm_copy_fw_reg_indices(vcpu, uindices);
	अगर (ret < 0)
		वापस ret;
	uindices += kvm_arm_get_fw_num_regs(vcpu);

	ret = copy_समयr_indices(vcpu, uindices);
	अगर (ret < 0)
		वापस ret;
	uindices += NUM_TIMER_REGS;

	वापस kvm_arm_copy_sys_reg_indices(vcpu, uindices);
पूर्ण

पूर्णांक kvm_arm_get_reg(काष्ठा kvm_vcpu *vcpu, स्थिर काष्ठा kvm_one_reg *reg)
अणु
	/* We currently use nothing arch-specअगरic in upper 32 bits */
	अगर ((reg->id & ~KVM_REG_SIZE_MASK) >> 32 != KVM_REG_ARM64 >> 32)
		वापस -EINVAL;

	चयन (reg->id & KVM_REG_ARM_COPROC_MASK) अणु
	हाल KVM_REG_ARM_CORE:	वापस get_core_reg(vcpu, reg);
	हाल KVM_REG_ARM_FW:	वापस kvm_arm_get_fw_reg(vcpu, reg);
	हाल KVM_REG_ARM64_SVE:	वापस get_sve_reg(vcpu, reg);
	पूर्ण

	अगर (is_समयr_reg(reg->id))
		वापस get_समयr_reg(vcpu, reg);

	वापस kvm_arm_sys_reg_get_reg(vcpu, reg);
पूर्ण

पूर्णांक kvm_arm_set_reg(काष्ठा kvm_vcpu *vcpu, स्थिर काष्ठा kvm_one_reg *reg)
अणु
	/* We currently use nothing arch-specअगरic in upper 32 bits */
	अगर ((reg->id & ~KVM_REG_SIZE_MASK) >> 32 != KVM_REG_ARM64 >> 32)
		वापस -EINVAL;

	चयन (reg->id & KVM_REG_ARM_COPROC_MASK) अणु
	हाल KVM_REG_ARM_CORE:	वापस set_core_reg(vcpu, reg);
	हाल KVM_REG_ARM_FW:	वापस kvm_arm_set_fw_reg(vcpu, reg);
	हाल KVM_REG_ARM64_SVE:	वापस set_sve_reg(vcpu, reg);
	पूर्ण

	अगर (is_समयr_reg(reg->id))
		वापस set_समयr_reg(vcpu, reg);

	वापस kvm_arm_sys_reg_set_reg(vcpu, reg);
पूर्ण

पूर्णांक kvm_arch_vcpu_ioctl_get_sregs(काष्ठा kvm_vcpu *vcpu,
				  काष्ठा kvm_sregs *sregs)
अणु
	वापस -EINVAL;
पूर्ण

पूर्णांक kvm_arch_vcpu_ioctl_set_sregs(काष्ठा kvm_vcpu *vcpu,
				  काष्ठा kvm_sregs *sregs)
अणु
	वापस -EINVAL;
पूर्ण

पूर्णांक __kvm_arm_vcpu_get_events(काष्ठा kvm_vcpu *vcpu,
			      काष्ठा kvm_vcpu_events *events)
अणु
	events->exception.serror_pending = !!(vcpu->arch.hcr_el2 & HCR_VSE);
	events->exception.serror_has_esr = cpus_have_स्थिर_cap(ARM64_HAS_RAS_EXTN);

	अगर (events->exception.serror_pending && events->exception.serror_has_esr)
		events->exception.serror_esr = vcpu_get_vsesr(vcpu);

	/*
	 * We never वापस a pending ext_dabt here because we deliver it to
	 * the भव CPU directly when setting the event and it's no दीर्घer
	 * 'pending' at this poपूर्णांक.
	 */

	वापस 0;
पूर्ण

पूर्णांक __kvm_arm_vcpu_set_events(काष्ठा kvm_vcpu *vcpu,
			      काष्ठा kvm_vcpu_events *events)
अणु
	bool serror_pending = events->exception.serror_pending;
	bool has_esr = events->exception.serror_has_esr;
	bool ext_dabt_pending = events->exception.ext_dabt_pending;

	अगर (serror_pending && has_esr) अणु
		अगर (!cpus_have_स्थिर_cap(ARM64_HAS_RAS_EXTN))
			वापस -EINVAL;

		अगर (!((events->exception.serror_esr) & ~ESR_ELx_ISS_MASK))
			kvm_set_sei_esr(vcpu, events->exception.serror_esr);
		अन्यथा
			वापस -EINVAL;
	पूर्ण अन्यथा अगर (serror_pending) अणु
		kvm_inject_vabt(vcpu);
	पूर्ण

	अगर (ext_dabt_pending)
		kvm_inject_dabt(vcpu, kvm_vcpu_get_hfar(vcpu));

	वापस 0;
पूर्ण

पूर्णांक __attribute_स्थिर__ kvm_target_cpu(व्योम)
अणु
	अचिन्हित दीर्घ implementor = पढ़ो_cpuid_implementor();
	अचिन्हित दीर्घ part_number = पढ़ो_cpuid_part_number();

	चयन (implementor) अणु
	हाल ARM_CPU_IMP_ARM:
		चयन (part_number) अणु
		हाल ARM_CPU_PART_AEM_V8:
			वापस KVM_ARM_TARGET_AEM_V8;
		हाल ARM_CPU_PART_FOUNDATION:
			वापस KVM_ARM_TARGET_FOUNDATION_V8;
		हाल ARM_CPU_PART_CORTEX_A53:
			वापस KVM_ARM_TARGET_CORTEX_A53;
		हाल ARM_CPU_PART_CORTEX_A57:
			वापस KVM_ARM_TARGET_CORTEX_A57;
		पूर्ण
		अवरोध;
	हाल ARM_CPU_IMP_APM:
		चयन (part_number) अणु
		हाल APM_CPU_PART_POTENZA:
			वापस KVM_ARM_TARGET_XGENE_POTENZA;
		पूर्ण
		अवरोध;
	पूर्ण

	/* Return a शेष generic target */
	वापस KVM_ARM_TARGET_GENERIC_V8;
पूर्ण

पूर्णांक kvm_vcpu_preferred_target(काष्ठा kvm_vcpu_init *init)
अणु
	पूर्णांक target = kvm_target_cpu();

	अगर (target < 0)
		वापस -ENODEV;

	स_रखो(init, 0, माप(*init));

	/*
	 * For now, we करोn't वापस any features.
	 * In future, we might use features to वापस target
	 * specअगरic features available क्रम the preferred
	 * target type.
	 */
	init->target = (__u32)target;

	वापस 0;
पूर्ण

पूर्णांक kvm_arch_vcpu_ioctl_get_fpu(काष्ठा kvm_vcpu *vcpu, काष्ठा kvm_fpu *fpu)
अणु
	वापस -EINVAL;
पूर्ण

पूर्णांक kvm_arch_vcpu_ioctl_set_fpu(काष्ठा kvm_vcpu *vcpu, काष्ठा kvm_fpu *fpu)
अणु
	वापस -EINVAL;
पूर्ण

पूर्णांक kvm_arch_vcpu_ioctl_translate(काष्ठा kvm_vcpu *vcpu,
				  काष्ठा kvm_translation *tr)
अणु
	वापस -EINVAL;
पूर्ण

/**
 * kvm_arch_vcpu_ioctl_set_guest_debug - set up guest debugging
 * @kvm:	poपूर्णांकer to the KVM काष्ठा
 * @kvm_guest_debug: the ioctl data buffer
 *
 * This sets up and enables the VM क्रम guest debugging. Userspace
 * passes in a control flag to enable dअगरferent debug types and
 * potentially other architecture specअगरic inक्रमmation in the rest of
 * the काष्ठाure.
 */
पूर्णांक kvm_arch_vcpu_ioctl_set_guest_debug(काष्ठा kvm_vcpu *vcpu,
					काष्ठा kvm_guest_debug *dbg)
अणु
	पूर्णांक ret = 0;

	trace_kvm_set_guest_debug(vcpu, dbg->control);

	अगर (dbg->control & ~KVM_GUESTDBG_VALID_MASK) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (dbg->control & KVM_GUESTDBG_ENABLE) अणु
		vcpu->guest_debug = dbg->control;

		/* Hardware assisted Break and Watch poपूर्णांकs */
		अगर (vcpu->guest_debug & KVM_GUESTDBG_USE_HW) अणु
			vcpu->arch.बाह्यal_debug_state = dbg->arch;
		पूर्ण

	पूर्ण अन्यथा अणु
		/* If not enabled clear all flags */
		vcpu->guest_debug = 0;
	पूर्ण

out:
	वापस ret;
पूर्ण

पूर्णांक kvm_arm_vcpu_arch_set_attr(काष्ठा kvm_vcpu *vcpu,
			       काष्ठा kvm_device_attr *attr)
अणु
	पूर्णांक ret;

	चयन (attr->group) अणु
	हाल KVM_ARM_VCPU_PMU_V3_CTRL:
		ret = kvm_arm_pmu_v3_set_attr(vcpu, attr);
		अवरोध;
	हाल KVM_ARM_VCPU_TIMER_CTRL:
		ret = kvm_arm_समयr_set_attr(vcpu, attr);
		अवरोध;
	हाल KVM_ARM_VCPU_PVTIME_CTRL:
		ret = kvm_arm_pvसमय_set_attr(vcpu, attr);
		अवरोध;
	शेष:
		ret = -ENXIO;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक kvm_arm_vcpu_arch_get_attr(काष्ठा kvm_vcpu *vcpu,
			       काष्ठा kvm_device_attr *attr)
अणु
	पूर्णांक ret;

	चयन (attr->group) अणु
	हाल KVM_ARM_VCPU_PMU_V3_CTRL:
		ret = kvm_arm_pmu_v3_get_attr(vcpu, attr);
		अवरोध;
	हाल KVM_ARM_VCPU_TIMER_CTRL:
		ret = kvm_arm_समयr_get_attr(vcpu, attr);
		अवरोध;
	हाल KVM_ARM_VCPU_PVTIME_CTRL:
		ret = kvm_arm_pvसमय_get_attr(vcpu, attr);
		अवरोध;
	शेष:
		ret = -ENXIO;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक kvm_arm_vcpu_arch_has_attr(काष्ठा kvm_vcpu *vcpu,
			       काष्ठा kvm_device_attr *attr)
अणु
	पूर्णांक ret;

	चयन (attr->group) अणु
	हाल KVM_ARM_VCPU_PMU_V3_CTRL:
		ret = kvm_arm_pmu_v3_has_attr(vcpu, attr);
		अवरोध;
	हाल KVM_ARM_VCPU_TIMER_CTRL:
		ret = kvm_arm_समयr_has_attr(vcpu, attr);
		अवरोध;
	हाल KVM_ARM_VCPU_PVTIME_CTRL:
		ret = kvm_arm_pvसमय_has_attr(vcpu, attr);
		अवरोध;
	शेष:
		ret = -ENXIO;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण
