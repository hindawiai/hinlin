<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Check क्रम KVM_GET_REG_LIST regressions.
 *
 * Copyright (C) 2020, Red Hat, Inc.
 *
 * When attempting to migrate from a host with an older kernel to a host
 * with a newer kernel we allow the newer kernel on the destination to
 * list new रेजिस्टरs with get-reg-list. We assume they'll be unused, at
 * least until the guest reboots, and so they're relatively harmless.
 * However, अगर the destination host with the newer kernel is missing
 * रेजिस्टरs which the source host with the older kernel has, then that's
 * a regression in get-reg-list. This test checks क्रम that regression by
 * checking the current list against a blessed list. We should never have
 * missing रेजिस्टरs, but अगर new ones appear then they can probably be
 * added to the blessed list. A completely new blessed list can be created
 * by running the test with the --list command line argument.
 *
 * Note, the blessed list should be created from the oldest possible
 * kernel. We can't go older than v4.15, though, because that's the first
 * release to expose the ID प्रणाली रेजिस्टरs in KVM_GET_REG_LIST, see
 * commit 93390c0a1b20 ("arm64: KVM: Hide unsupported AArch64 CPU features
 * from guests"). Also, one must use the --core-reg-fixup command line
 * option when running on an older kernel that करोesn't include df205b5c6328
 * ("KVM: arm64: Filter out invalid core register IDs in KVM_GET_REG_LIST")
 */
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश "kvm_util.h"
#समावेश "test_util.h"
#समावेश "processor.h"

#अगर_घोषित REG_LIST_SVE
#घोषणा reg_list_sve() (true)
#अन्यथा
#घोषणा reg_list_sve() (false)
#पूर्ण_अगर

#घोषणा REG_MASK (KVM_REG_ARCH_MASK | KVM_REG_SIZE_MASK | KVM_REG_ARM_COPROC_MASK)

#घोषणा क्रम_each_reg(i)								\
	क्रम ((i) = 0; (i) < reg_list->n; ++(i))

#घोषणा क्रम_each_reg_filtered(i)						\
	क्रम_each_reg(i)								\
		अगर (!filter_reg(reg_list->reg[i]))

#घोषणा क्रम_each_missing_reg(i)							\
	क्रम ((i) = 0; (i) < blessed_n; ++(i))					\
		अगर (!find_reg(reg_list->reg, reg_list->n, blessed_reg[i]))

#घोषणा क्रम_each_new_reg(i)							\
	क्रम_each_reg_filtered(i)						\
		अगर (!find_reg(blessed_reg, blessed_n, reg_list->reg[i]))


अटल काष्ठा kvm_reg_list *reg_list;

अटल __u64 base_regs[], vregs[], sve_regs[], rejects_set[];
अटल __u64 base_regs_n, vregs_n, sve_regs_n, rejects_set_n;
अटल __u64 *blessed_reg, blessed_n;

अटल bool filter_reg(__u64 reg)
अणु
	/*
	 * DEMUX रेजिस्टर presence depends on the host's CLIDR_EL1.
	 * This means there's no set of them that we can bless.
	 */
	अगर ((reg & KVM_REG_ARM_COPROC_MASK) == KVM_REG_ARM_DEMUX)
		वापस true;

	वापस false;
पूर्ण

अटल bool find_reg(__u64 regs[], __u64 nr_regs, __u64 reg)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < nr_regs; ++i)
		अगर (reg == regs[i])
			वापस true;
	वापस false;
पूर्ण

अटल स्थिर अक्षर *str_with_index(स्थिर अक्षर *ढाँचा, __u64 index)
अणु
	अक्षर *str, *p;
	पूर्णांक n;

	str = strdup(ढाँचा);
	p = म_माला(str, "##");
	n = प्र_लिखो(p, "%lld", index);
	म_जोड़ो(p + n, म_माला(ढाँचा, "##") + 2);

	वापस (स्थिर अक्षर *)str;
पूर्ण

#घोषणा CORE_REGS_XX_NR_WORDS	2
#घोषणा CORE_SPSR_XX_NR_WORDS	2
#घोषणा CORE_FPREGS_XX_NR_WORDS	4

अटल स्थिर अक्षर *core_id_to_str(__u64 id)
अणु
	__u64 core_off = id & ~REG_MASK, idx;

	/*
	 * core_off is the offset पूर्णांकo काष्ठा kvm_regs
	 */
	चयन (core_off) अणु
	हाल KVM_REG_ARM_CORE_REG(regs.regs[0]) ...
	     KVM_REG_ARM_CORE_REG(regs.regs[30]):
		idx = (core_off - KVM_REG_ARM_CORE_REG(regs.regs[0])) / CORE_REGS_XX_NR_WORDS;
		TEST_ASSERT(idx < 31, "Unexpected regs.regs index: %lld", idx);
		वापस str_with_index("KVM_REG_ARM_CORE_REG(regs.regs[##])", idx);
	हाल KVM_REG_ARM_CORE_REG(regs.sp):
		वापस "KVM_REG_ARM_CORE_REG(regs.sp)";
	हाल KVM_REG_ARM_CORE_REG(regs.pc):
		वापस "KVM_REG_ARM_CORE_REG(regs.pc)";
	हाल KVM_REG_ARM_CORE_REG(regs.pstate):
		वापस "KVM_REG_ARM_CORE_REG(regs.pstate)";
	हाल KVM_REG_ARM_CORE_REG(sp_el1):
		वापस "KVM_REG_ARM_CORE_REG(sp_el1)";
	हाल KVM_REG_ARM_CORE_REG(elr_el1):
		वापस "KVM_REG_ARM_CORE_REG(elr_el1)";
	हाल KVM_REG_ARM_CORE_REG(spsr[0]) ...
	     KVM_REG_ARM_CORE_REG(spsr[KVM_NR_SPSR - 1]):
		idx = (core_off - KVM_REG_ARM_CORE_REG(spsr[0])) / CORE_SPSR_XX_NR_WORDS;
		TEST_ASSERT(idx < KVM_NR_SPSR, "Unexpected spsr index: %lld", idx);
		वापस str_with_index("KVM_REG_ARM_CORE_REG(spsr[##])", idx);
	हाल KVM_REG_ARM_CORE_REG(fp_regs.vregs[0]) ...
	     KVM_REG_ARM_CORE_REG(fp_regs.vregs[31]):
		idx = (core_off - KVM_REG_ARM_CORE_REG(fp_regs.vregs[0])) / CORE_FPREGS_XX_NR_WORDS;
		TEST_ASSERT(idx < 32, "Unexpected fp_regs.vregs index: %lld", idx);
		वापस str_with_index("KVM_REG_ARM_CORE_REG(fp_regs.vregs[##])", idx);
	हाल KVM_REG_ARM_CORE_REG(fp_regs.fpsr):
		वापस "KVM_REG_ARM_CORE_REG(fp_regs.fpsr)";
	हाल KVM_REG_ARM_CORE_REG(fp_regs.fpcr):
		वापस "KVM_REG_ARM_CORE_REG(fp_regs.fpcr)";
	पूर्ण

	TEST_FAIL("Unknown core reg id: 0x%llx", id);
	वापस शून्य;
पूर्ण

अटल स्थिर अक्षर *sve_id_to_str(__u64 id)
अणु
	__u64 sve_off, n, i;

	अगर (id == KVM_REG_ARM64_SVE_VLS)
		वापस "KVM_REG_ARM64_SVE_VLS";

	sve_off = id & ~(REG_MASK | ((1ULL << 5) - 1));
	i = id & (KVM_ARM64_SVE_MAX_SLICES - 1);

	TEST_ASSERT(i == 0, "Currently we don't expect slice > 0, reg id 0x%llx", id);

	चयन (sve_off) अणु
	हाल KVM_REG_ARM64_SVE_ZREG_BASE ...
	     KVM_REG_ARM64_SVE_ZREG_BASE + (1ULL << 5) * KVM_ARM64_SVE_NUM_ZREGS - 1:
		n = (id >> 5) & (KVM_ARM64_SVE_NUM_ZREGS - 1);
		TEST_ASSERT(id == KVM_REG_ARM64_SVE_ZREG(n, 0),
			    "Unexpected bits set in SVE ZREG id: 0x%llx", id);
		वापस str_with_index("KVM_REG_ARM64_SVE_ZREG(##, 0)", n);
	हाल KVM_REG_ARM64_SVE_PREG_BASE ...
	     KVM_REG_ARM64_SVE_PREG_BASE + (1ULL << 5) * KVM_ARM64_SVE_NUM_PREGS - 1:
		n = (id >> 5) & (KVM_ARM64_SVE_NUM_PREGS - 1);
		TEST_ASSERT(id == KVM_REG_ARM64_SVE_PREG(n, 0),
			    "Unexpected bits set in SVE PREG id: 0x%llx", id);
		वापस str_with_index("KVM_REG_ARM64_SVE_PREG(##, 0)", n);
	हाल KVM_REG_ARM64_SVE_FFR_BASE:
		TEST_ASSERT(id == KVM_REG_ARM64_SVE_FFR(0),
			    "Unexpected bits set in SVE FFR id: 0x%llx", id);
		वापस "KVM_REG_ARM64_SVE_FFR(0)";
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम prपूर्णांक_reg(__u64 id)
अणु
	अचिन्हित op0, op1, crn, crm, op2;
	स्थिर अक्षर *reg_size = शून्य;

	TEST_ASSERT((id & KVM_REG_ARCH_MASK) == KVM_REG_ARM64,
		    "KVM_REG_ARM64 missing in reg id: 0x%llx", id);

	चयन (id & KVM_REG_SIZE_MASK) अणु
	हाल KVM_REG_SIZE_U8:
		reg_size = "KVM_REG_SIZE_U8";
		अवरोध;
	हाल KVM_REG_SIZE_U16:
		reg_size = "KVM_REG_SIZE_U16";
		अवरोध;
	हाल KVM_REG_SIZE_U32:
		reg_size = "KVM_REG_SIZE_U32";
		अवरोध;
	हाल KVM_REG_SIZE_U64:
		reg_size = "KVM_REG_SIZE_U64";
		अवरोध;
	हाल KVM_REG_SIZE_U128:
		reg_size = "KVM_REG_SIZE_U128";
		अवरोध;
	हाल KVM_REG_SIZE_U256:
		reg_size = "KVM_REG_SIZE_U256";
		अवरोध;
	हाल KVM_REG_SIZE_U512:
		reg_size = "KVM_REG_SIZE_U512";
		अवरोध;
	हाल KVM_REG_SIZE_U1024:
		reg_size = "KVM_REG_SIZE_U1024";
		अवरोध;
	हाल KVM_REG_SIZE_U2048:
		reg_size = "KVM_REG_SIZE_U2048";
		अवरोध;
	शेष:
		TEST_FAIL("Unexpected reg size: 0x%llx in reg id: 0x%llx",
			  (id & KVM_REG_SIZE_MASK) >> KVM_REG_SIZE_SHIFT, id);
	पूर्ण

	चयन (id & KVM_REG_ARM_COPROC_MASK) अणु
	हाल KVM_REG_ARM_CORE:
		म_लिखो("\tKVM_REG_ARM64 | %s | KVM_REG_ARM_CORE | %s,\n", reg_size, core_id_to_str(id));
		अवरोध;
	हाल KVM_REG_ARM_DEMUX:
		TEST_ASSERT(!(id & ~(REG_MASK | KVM_REG_ARM_DEMUX_ID_MASK | KVM_REG_ARM_DEMUX_VAL_MASK)),
			    "Unexpected bits set in DEMUX reg id: 0x%llx", id);
		म_लिखो("\tKVM_REG_ARM64 | %s | KVM_REG_ARM_DEMUX | KVM_REG_ARM_DEMUX_ID_CCSIDR | %lld,\n",
		       reg_size, id & KVM_REG_ARM_DEMUX_VAL_MASK);
		अवरोध;
	हाल KVM_REG_ARM64_SYSREG:
		op0 = (id & KVM_REG_ARM64_SYSREG_OP0_MASK) >> KVM_REG_ARM64_SYSREG_OP0_SHIFT;
		op1 = (id & KVM_REG_ARM64_SYSREG_OP1_MASK) >> KVM_REG_ARM64_SYSREG_OP1_SHIFT;
		crn = (id & KVM_REG_ARM64_SYSREG_CRN_MASK) >> KVM_REG_ARM64_SYSREG_CRN_SHIFT;
		crm = (id & KVM_REG_ARM64_SYSREG_CRM_MASK) >> KVM_REG_ARM64_SYSREG_CRM_SHIFT;
		op2 = (id & KVM_REG_ARM64_SYSREG_OP2_MASK) >> KVM_REG_ARM64_SYSREG_OP2_SHIFT;
		TEST_ASSERT(id == ARM64_SYS_REG(op0, op1, crn, crm, op2),
			    "Unexpected bits set in SYSREG reg id: 0x%llx", id);
		म_लिखो("\tARM64_SYS_REG(%d, %d, %d, %d, %d),\n", op0, op1, crn, crm, op2);
		अवरोध;
	हाल KVM_REG_ARM_FW:
		TEST_ASSERT(id == KVM_REG_ARM_FW_REG(id & 0xffff),
			    "Unexpected bits set in FW reg id: 0x%llx", id);
		म_लिखो("\tKVM_REG_ARM_FW_REG(%lld),\n", id & 0xffff);
		अवरोध;
	हाल KVM_REG_ARM64_SVE:
		अगर (reg_list_sve())
			म_लिखो("\t%s,\n", sve_id_to_str(id));
		अन्यथा
			TEST_FAIL("KVM_REG_ARM64_SVE is an unexpected coproc type in reg id: 0x%llx", id);
		अवरोध;
	शेष:
		TEST_FAIL("Unexpected coproc type: 0x%llx in reg id: 0x%llx",
			  (id & KVM_REG_ARM_COPROC_MASK) >> KVM_REG_ARM_COPROC_SHIFT, id);
	पूर्ण
पूर्ण

/*
 * Older kernels listed each 32-bit word of CORE रेजिस्टरs separately.
 * For 64 and 128-bit रेजिस्टरs we need to ignore the extra words. We
 * also need to fixup the sizes, because the older kernels stated all
 * रेजिस्टरs were 64-bit, even when they weren't.
 */
अटल व्योम core_reg_fixup(व्योम)
अणु
	काष्ठा kvm_reg_list *पंचांगp;
	__u64 id, core_off;
	पूर्णांक i;

	पंचांगp = सुस्मृति(1, माप(*पंचांगp) + reg_list->n * माप(__u64));

	क्रम (i = 0; i < reg_list->n; ++i) अणु
		id = reg_list->reg[i];

		अगर ((id & KVM_REG_ARM_COPROC_MASK) != KVM_REG_ARM_CORE) अणु
			पंचांगp->reg[पंचांगp->n++] = id;
			जारी;
		पूर्ण

		core_off = id & ~REG_MASK;

		चयन (core_off) अणु
		हाल 0x52: हाल 0xd2: हाल 0xd6:
			/*
			 * These offsets are poपूर्णांकing at padding.
			 * We need to ignore them too.
			 */
			जारी;
		हाल KVM_REG_ARM_CORE_REG(fp_regs.vregs[0]) ...
		     KVM_REG_ARM_CORE_REG(fp_regs.vregs[31]):
			अगर (core_off & 3)
				जारी;
			id &= ~KVM_REG_SIZE_MASK;
			id |= KVM_REG_SIZE_U128;
			पंचांगp->reg[पंचांगp->n++] = id;
			जारी;
		हाल KVM_REG_ARM_CORE_REG(fp_regs.fpsr):
		हाल KVM_REG_ARM_CORE_REG(fp_regs.fpcr):
			id &= ~KVM_REG_SIZE_MASK;
			id |= KVM_REG_SIZE_U32;
			पंचांगp->reg[पंचांगp->n++] = id;
			जारी;
		शेष:
			अगर (core_off & 1)
				जारी;
			पंचांगp->reg[पंचांगp->n++] = id;
			अवरोध;
		पूर्ण
	पूर्ण

	मुक्त(reg_list);
	reg_list = पंचांगp;
पूर्ण

अटल व्योम prepare_vcpu_init(काष्ठा kvm_vcpu_init *init)
अणु
	अगर (reg_list_sve())
		init->features[0] |= 1 << KVM_ARM_VCPU_SVE;
पूर्ण

अटल व्योम finalize_vcpu(काष्ठा kvm_vm *vm, uपूर्णांक32_t vcpuid)
अणु
	पूर्णांक feature;

	अगर (reg_list_sve()) अणु
		feature = KVM_ARM_VCPU_SVE;
		vcpu_ioctl(vm, vcpuid, KVM_ARM_VCPU_FINALIZE, &feature);
	पूर्ण
पूर्ण

अटल व्योम check_supported(व्योम)
अणु
	अगर (reg_list_sve() && !kvm_check_cap(KVM_CAP_ARM_SVE)) अणु
		ख_लिखो(मानक_त्रुटि, "SVE not available, skipping tests\n");
		निकास(KSFT_SKIP);
	पूर्ण
पूर्ण

पूर्णांक मुख्य(पूर्णांक ac, अक्षर **av)
अणु
	काष्ठा kvm_vcpu_init init = अणु .target = -1, पूर्ण;
	पूर्णांक new_regs = 0, missing_regs = 0, i;
	पूर्णांक failed_get = 0, failed_set = 0, failed_reject = 0;
	bool prपूर्णांक_list = false, prपूर्णांक_filtered = false, fixup_core_regs = false;
	काष्ठा kvm_vm *vm;
	__u64 *vec_regs;

	check_supported();

	क्रम (i = 1; i < ac; ++i) अणु
		अगर (म_भेद(av[i], "--core-reg-fixup") == 0)
			fixup_core_regs = true;
		अन्यथा अगर (म_भेद(av[i], "--list") == 0)
			prपूर्णांक_list = true;
		अन्यथा अगर (म_भेद(av[i], "--list-filtered") == 0)
			prपूर्णांक_filtered = true;
		अन्यथा
			TEST_FAIL("Unknown option: %s\n", av[i]);
	पूर्ण

	vm = vm_create(VM_MODE_DEFAULT, DEFAULT_GUEST_PHY_PAGES, O_RDWR);
	prepare_vcpu_init(&init);
	aarch64_vcpu_add_शेष(vm, 0, &init, शून्य);
	finalize_vcpu(vm, 0);

	reg_list = vcpu_get_reg_list(vm, 0);

	अगर (fixup_core_regs)
		core_reg_fixup();

	अगर (prपूर्णांक_list || prपूर्णांक_filtered) अणु
		अक्षर_दो('\n');
		क्रम_each_reg(i) अणु
			__u64 id = reg_list->reg[i];
			अगर ((prपूर्णांक_list && !filter_reg(id)) ||
			    (prपूर्णांक_filtered && filter_reg(id)))
				prपूर्णांक_reg(id);
		पूर्ण
		अक्षर_दो('\n');
		वापस 0;
	पूर्ण

	/*
	 * We only test that we can get the रेजिस्टर and then ग_लिखो back the
	 * same value. Some रेजिस्टरs may allow other values to be written
	 * back, but others only allow some bits to be changed, and at least
	 * क्रम ID रेजिस्टरs set will fail अगर the value करोes not exactly match
	 * what was वापसed by get. If रेजिस्टरs that allow other values to
	 * be written need to have the other values tested, then we should
	 * create a new set of tests क्रम those in a new independent test
	 * executable.
	 */
	क्रम_each_reg(i) अणु
		uपूर्णांक8_t addr[2048 / 8];
		काष्ठा kvm_one_reg reg = अणु
			.id = reg_list->reg[i],
			.addr = (__u64)&addr,
		पूर्ण;
		पूर्णांक ret;

		ret = _vcpu_ioctl(vm, 0, KVM_GET_ONE_REG, &reg);
		अगर (ret) अणु
			माला_दो("Failed to get ");
			prपूर्णांक_reg(reg.id);
			अक्षर_दो('\n');
			++failed_get;
		पूर्ण

		/* rejects_set रेजिस्टरs are rejected after KVM_ARM_VCPU_FINALIZE */
		अगर (find_reg(rejects_set, rejects_set_n, reg.id)) अणु
			ret = _vcpu_ioctl(vm, 0, KVM_SET_ONE_REG, &reg);
			अगर (ret != -1 || त्रुटि_सं != EPERM) अणु
				म_लिखो("Failed to reject (ret=%d, errno=%d) ", ret, त्रुटि_सं);
				prपूर्णांक_reg(reg.id);
				अक्षर_दो('\n');
				++failed_reject;
			पूर्ण
			जारी;
		पूर्ण

		ret = _vcpu_ioctl(vm, 0, KVM_SET_ONE_REG, &reg);
		अगर (ret) अणु
			माला_दो("Failed to set ");
			prपूर्णांक_reg(reg.id);
			अक्षर_दो('\n');
			++failed_set;
		पूर्ण
	पूर्ण

	अगर (reg_list_sve()) अणु
		blessed_n = base_regs_n + sve_regs_n;
		vec_regs = sve_regs;
	पूर्ण अन्यथा अणु
		blessed_n = base_regs_n + vregs_n;
		vec_regs = vregs;
	पूर्ण

	blessed_reg = सुस्मृति(blessed_n, माप(__u64));
	क्रम (i = 0; i < base_regs_n; ++i)
		blessed_reg[i] = base_regs[i];
	क्रम (i = 0; i < blessed_n - base_regs_n; ++i)
		blessed_reg[base_regs_n + i] = vec_regs[i];

	क्रम_each_new_reg(i)
		++new_regs;

	क्रम_each_missing_reg(i)
		++missing_regs;

	अगर (new_regs || missing_regs) अणु
		म_लिखो("Number blessed registers: %5lld\n", blessed_n);
		म_लिखो("Number registers:         %5lld\n", reg_list->n);
	पूर्ण

	अगर (new_regs) अणु
		म_लिखो("\nThere are %d new registers.\n"
		       "Consider adding them to the blessed reg "
		       "list with the following lines:\n\n", new_regs);
		क्रम_each_new_reg(i)
			prपूर्णांक_reg(reg_list->reg[i]);
		अक्षर_दो('\n');
	पूर्ण

	अगर (missing_regs) अणु
		म_लिखो("\nThere are %d missing registers.\n"
		       "The following lines are missing registers:\n\n", missing_regs);
		क्रम_each_missing_reg(i)
			prपूर्णांक_reg(blessed_reg[i]);
		अक्षर_दो('\n');
	पूर्ण

	TEST_ASSERT(!missing_regs && !failed_get && !failed_set && !failed_reject,
		    "There are %d missing registers; "
		    "%d registers failed get; %d registers failed set; %d registers failed reject",
		    missing_regs, failed_get, failed_set, failed_reject);

	वापस 0;
पूर्ण

/*
 * The current blessed list was primed with the output of kernel version
 * v4.15 with --core-reg-fixup and then later updated with new रेजिस्टरs.
 *
 * The blessed list is up to date with kernel version v5.10-rc5
 */
अटल __u64 base_regs[] = अणु
	KVM_REG_ARM64 | KVM_REG_SIZE_U64 | KVM_REG_ARM_CORE | KVM_REG_ARM_CORE_REG(regs.regs[0]),
	KVM_REG_ARM64 | KVM_REG_SIZE_U64 | KVM_REG_ARM_CORE | KVM_REG_ARM_CORE_REG(regs.regs[1]),
	KVM_REG_ARM64 | KVM_REG_SIZE_U64 | KVM_REG_ARM_CORE | KVM_REG_ARM_CORE_REG(regs.regs[2]),
	KVM_REG_ARM64 | KVM_REG_SIZE_U64 | KVM_REG_ARM_CORE | KVM_REG_ARM_CORE_REG(regs.regs[3]),
	KVM_REG_ARM64 | KVM_REG_SIZE_U64 | KVM_REG_ARM_CORE | KVM_REG_ARM_CORE_REG(regs.regs[4]),
	KVM_REG_ARM64 | KVM_REG_SIZE_U64 | KVM_REG_ARM_CORE | KVM_REG_ARM_CORE_REG(regs.regs[5]),
	KVM_REG_ARM64 | KVM_REG_SIZE_U64 | KVM_REG_ARM_CORE | KVM_REG_ARM_CORE_REG(regs.regs[6]),
	KVM_REG_ARM64 | KVM_REG_SIZE_U64 | KVM_REG_ARM_CORE | KVM_REG_ARM_CORE_REG(regs.regs[7]),
	KVM_REG_ARM64 | KVM_REG_SIZE_U64 | KVM_REG_ARM_CORE | KVM_REG_ARM_CORE_REG(regs.regs[8]),
	KVM_REG_ARM64 | KVM_REG_SIZE_U64 | KVM_REG_ARM_CORE | KVM_REG_ARM_CORE_REG(regs.regs[9]),
	KVM_REG_ARM64 | KVM_REG_SIZE_U64 | KVM_REG_ARM_CORE | KVM_REG_ARM_CORE_REG(regs.regs[10]),
	KVM_REG_ARM64 | KVM_REG_SIZE_U64 | KVM_REG_ARM_CORE | KVM_REG_ARM_CORE_REG(regs.regs[11]),
	KVM_REG_ARM64 | KVM_REG_SIZE_U64 | KVM_REG_ARM_CORE | KVM_REG_ARM_CORE_REG(regs.regs[12]),
	KVM_REG_ARM64 | KVM_REG_SIZE_U64 | KVM_REG_ARM_CORE | KVM_REG_ARM_CORE_REG(regs.regs[13]),
	KVM_REG_ARM64 | KVM_REG_SIZE_U64 | KVM_REG_ARM_CORE | KVM_REG_ARM_CORE_REG(regs.regs[14]),
	KVM_REG_ARM64 | KVM_REG_SIZE_U64 | KVM_REG_ARM_CORE | KVM_REG_ARM_CORE_REG(regs.regs[15]),
	KVM_REG_ARM64 | KVM_REG_SIZE_U64 | KVM_REG_ARM_CORE | KVM_REG_ARM_CORE_REG(regs.regs[16]),
	KVM_REG_ARM64 | KVM_REG_SIZE_U64 | KVM_REG_ARM_CORE | KVM_REG_ARM_CORE_REG(regs.regs[17]),
	KVM_REG_ARM64 | KVM_REG_SIZE_U64 | KVM_REG_ARM_CORE | KVM_REG_ARM_CORE_REG(regs.regs[18]),
	KVM_REG_ARM64 | KVM_REG_SIZE_U64 | KVM_REG_ARM_CORE | KVM_REG_ARM_CORE_REG(regs.regs[19]),
	KVM_REG_ARM64 | KVM_REG_SIZE_U64 | KVM_REG_ARM_CORE | KVM_REG_ARM_CORE_REG(regs.regs[20]),
	KVM_REG_ARM64 | KVM_REG_SIZE_U64 | KVM_REG_ARM_CORE | KVM_REG_ARM_CORE_REG(regs.regs[21]),
	KVM_REG_ARM64 | KVM_REG_SIZE_U64 | KVM_REG_ARM_CORE | KVM_REG_ARM_CORE_REG(regs.regs[22]),
	KVM_REG_ARM64 | KVM_REG_SIZE_U64 | KVM_REG_ARM_CORE | KVM_REG_ARM_CORE_REG(regs.regs[23]),
	KVM_REG_ARM64 | KVM_REG_SIZE_U64 | KVM_REG_ARM_CORE | KVM_REG_ARM_CORE_REG(regs.regs[24]),
	KVM_REG_ARM64 | KVM_REG_SIZE_U64 | KVM_REG_ARM_CORE | KVM_REG_ARM_CORE_REG(regs.regs[25]),
	KVM_REG_ARM64 | KVM_REG_SIZE_U64 | KVM_REG_ARM_CORE | KVM_REG_ARM_CORE_REG(regs.regs[26]),
	KVM_REG_ARM64 | KVM_REG_SIZE_U64 | KVM_REG_ARM_CORE | KVM_REG_ARM_CORE_REG(regs.regs[27]),
	KVM_REG_ARM64 | KVM_REG_SIZE_U64 | KVM_REG_ARM_CORE | KVM_REG_ARM_CORE_REG(regs.regs[28]),
	KVM_REG_ARM64 | KVM_REG_SIZE_U64 | KVM_REG_ARM_CORE | KVM_REG_ARM_CORE_REG(regs.regs[29]),
	KVM_REG_ARM64 | KVM_REG_SIZE_U64 | KVM_REG_ARM_CORE | KVM_REG_ARM_CORE_REG(regs.regs[30]),
	KVM_REG_ARM64 | KVM_REG_SIZE_U64 | KVM_REG_ARM_CORE | KVM_REG_ARM_CORE_REG(regs.sp),
	KVM_REG_ARM64 | KVM_REG_SIZE_U64 | KVM_REG_ARM_CORE | KVM_REG_ARM_CORE_REG(regs.pc),
	KVM_REG_ARM64 | KVM_REG_SIZE_U64 | KVM_REG_ARM_CORE | KVM_REG_ARM_CORE_REG(regs.pstate),
	KVM_REG_ARM64 | KVM_REG_SIZE_U64 | KVM_REG_ARM_CORE | KVM_REG_ARM_CORE_REG(sp_el1),
	KVM_REG_ARM64 | KVM_REG_SIZE_U64 | KVM_REG_ARM_CORE | KVM_REG_ARM_CORE_REG(elr_el1),
	KVM_REG_ARM64 | KVM_REG_SIZE_U64 | KVM_REG_ARM_CORE | KVM_REG_ARM_CORE_REG(spsr[0]),
	KVM_REG_ARM64 | KVM_REG_SIZE_U64 | KVM_REG_ARM_CORE | KVM_REG_ARM_CORE_REG(spsr[1]),
	KVM_REG_ARM64 | KVM_REG_SIZE_U64 | KVM_REG_ARM_CORE | KVM_REG_ARM_CORE_REG(spsr[2]),
	KVM_REG_ARM64 | KVM_REG_SIZE_U64 | KVM_REG_ARM_CORE | KVM_REG_ARM_CORE_REG(spsr[3]),
	KVM_REG_ARM64 | KVM_REG_SIZE_U64 | KVM_REG_ARM_CORE | KVM_REG_ARM_CORE_REG(spsr[4]),
	KVM_REG_ARM64 | KVM_REG_SIZE_U32 | KVM_REG_ARM_CORE | KVM_REG_ARM_CORE_REG(fp_regs.fpsr),
	KVM_REG_ARM64 | KVM_REG_SIZE_U32 | KVM_REG_ARM_CORE | KVM_REG_ARM_CORE_REG(fp_regs.fpcr),
	KVM_REG_ARM_FW_REG(0),
	KVM_REG_ARM_FW_REG(1),
	KVM_REG_ARM_FW_REG(2),
	ARM64_SYS_REG(3, 3, 14, 3, 1),	/* CNTV_CTL_EL0 */
	ARM64_SYS_REG(3, 3, 14, 3, 2),	/* CNTV_CVAL_EL0 */
	ARM64_SYS_REG(3, 3, 14, 0, 2),
	ARM64_SYS_REG(3, 0, 0, 0, 0),	/* MIDR_EL1 */
	ARM64_SYS_REG(3, 0, 0, 0, 6),	/* REVIDR_EL1 */
	ARM64_SYS_REG(3, 1, 0, 0, 1),	/* CLIDR_EL1 */
	ARM64_SYS_REG(3, 1, 0, 0, 7),	/* AIDR_EL1 */
	ARM64_SYS_REG(3, 3, 0, 0, 1),	/* CTR_EL0 */
	ARM64_SYS_REG(2, 0, 0, 0, 4),
	ARM64_SYS_REG(2, 0, 0, 0, 5),
	ARM64_SYS_REG(2, 0, 0, 0, 6),
	ARM64_SYS_REG(2, 0, 0, 0, 7),
	ARM64_SYS_REG(2, 0, 0, 1, 4),
	ARM64_SYS_REG(2, 0, 0, 1, 5),
	ARM64_SYS_REG(2, 0, 0, 1, 6),
	ARM64_SYS_REG(2, 0, 0, 1, 7),
	ARM64_SYS_REG(2, 0, 0, 2, 0),	/* MDCCINT_EL1 */
	ARM64_SYS_REG(2, 0, 0, 2, 2),	/* MDSCR_EL1 */
	ARM64_SYS_REG(2, 0, 0, 2, 4),
	ARM64_SYS_REG(2, 0, 0, 2, 5),
	ARM64_SYS_REG(2, 0, 0, 2, 6),
	ARM64_SYS_REG(2, 0, 0, 2, 7),
	ARM64_SYS_REG(2, 0, 0, 3, 4),
	ARM64_SYS_REG(2, 0, 0, 3, 5),
	ARM64_SYS_REG(2, 0, 0, 3, 6),
	ARM64_SYS_REG(2, 0, 0, 3, 7),
	ARM64_SYS_REG(2, 0, 0, 4, 4),
	ARM64_SYS_REG(2, 0, 0, 4, 5),
	ARM64_SYS_REG(2, 0, 0, 4, 6),
	ARM64_SYS_REG(2, 0, 0, 4, 7),
	ARM64_SYS_REG(2, 0, 0, 5, 4),
	ARM64_SYS_REG(2, 0, 0, 5, 5),
	ARM64_SYS_REG(2, 0, 0, 5, 6),
	ARM64_SYS_REG(2, 0, 0, 5, 7),
	ARM64_SYS_REG(2, 0, 0, 6, 4),
	ARM64_SYS_REG(2, 0, 0, 6, 5),
	ARM64_SYS_REG(2, 0, 0, 6, 6),
	ARM64_SYS_REG(2, 0, 0, 6, 7),
	ARM64_SYS_REG(2, 0, 0, 7, 4),
	ARM64_SYS_REG(2, 0, 0, 7, 5),
	ARM64_SYS_REG(2, 0, 0, 7, 6),
	ARM64_SYS_REG(2, 0, 0, 7, 7),
	ARM64_SYS_REG(2, 0, 0, 8, 4),
	ARM64_SYS_REG(2, 0, 0, 8, 5),
	ARM64_SYS_REG(2, 0, 0, 8, 6),
	ARM64_SYS_REG(2, 0, 0, 8, 7),
	ARM64_SYS_REG(2, 0, 0, 9, 4),
	ARM64_SYS_REG(2, 0, 0, 9, 5),
	ARM64_SYS_REG(2, 0, 0, 9, 6),
	ARM64_SYS_REG(2, 0, 0, 9, 7),
	ARM64_SYS_REG(2, 0, 0, 10, 4),
	ARM64_SYS_REG(2, 0, 0, 10, 5),
	ARM64_SYS_REG(2, 0, 0, 10, 6),
	ARM64_SYS_REG(2, 0, 0, 10, 7),
	ARM64_SYS_REG(2, 0, 0, 11, 4),
	ARM64_SYS_REG(2, 0, 0, 11, 5),
	ARM64_SYS_REG(2, 0, 0, 11, 6),
	ARM64_SYS_REG(2, 0, 0, 11, 7),
	ARM64_SYS_REG(2, 0, 0, 12, 4),
	ARM64_SYS_REG(2, 0, 0, 12, 5),
	ARM64_SYS_REG(2, 0, 0, 12, 6),
	ARM64_SYS_REG(2, 0, 0, 12, 7),
	ARM64_SYS_REG(2, 0, 0, 13, 4),
	ARM64_SYS_REG(2, 0, 0, 13, 5),
	ARM64_SYS_REG(2, 0, 0, 13, 6),
	ARM64_SYS_REG(2, 0, 0, 13, 7),
	ARM64_SYS_REG(2, 0, 0, 14, 4),
	ARM64_SYS_REG(2, 0, 0, 14, 5),
	ARM64_SYS_REG(2, 0, 0, 14, 6),
	ARM64_SYS_REG(2, 0, 0, 14, 7),
	ARM64_SYS_REG(2, 0, 0, 15, 4),
	ARM64_SYS_REG(2, 0, 0, 15, 5),
	ARM64_SYS_REG(2, 0, 0, 15, 6),
	ARM64_SYS_REG(2, 0, 0, 15, 7),
	ARM64_SYS_REG(2, 4, 0, 7, 0),	/* DBGVCR32_EL2 */
	ARM64_SYS_REG(3, 0, 0, 0, 5),	/* MPIDR_EL1 */
	ARM64_SYS_REG(3, 0, 0, 1, 0),	/* ID_PFR0_EL1 */
	ARM64_SYS_REG(3, 0, 0, 1, 1),	/* ID_PFR1_EL1 */
	ARM64_SYS_REG(3, 0, 0, 1, 2),	/* ID_DFR0_EL1 */
	ARM64_SYS_REG(3, 0, 0, 1, 3),	/* ID_AFR0_EL1 */
	ARM64_SYS_REG(3, 0, 0, 1, 4),	/* ID_MMFR0_EL1 */
	ARM64_SYS_REG(3, 0, 0, 1, 5),	/* ID_MMFR1_EL1 */
	ARM64_SYS_REG(3, 0, 0, 1, 6),	/* ID_MMFR2_EL1 */
	ARM64_SYS_REG(3, 0, 0, 1, 7),	/* ID_MMFR3_EL1 */
	ARM64_SYS_REG(3, 0, 0, 2, 0),	/* ID_ISAR0_EL1 */
	ARM64_SYS_REG(3, 0, 0, 2, 1),	/* ID_ISAR1_EL1 */
	ARM64_SYS_REG(3, 0, 0, 2, 2),	/* ID_ISAR2_EL1 */
	ARM64_SYS_REG(3, 0, 0, 2, 3),	/* ID_ISAR3_EL1 */
	ARM64_SYS_REG(3, 0, 0, 2, 4),	/* ID_ISAR4_EL1 */
	ARM64_SYS_REG(3, 0, 0, 2, 5),	/* ID_ISAR5_EL1 */
	ARM64_SYS_REG(3, 0, 0, 2, 6),	/* ID_MMFR4_EL1 */
	ARM64_SYS_REG(3, 0, 0, 2, 7),	/* ID_ISAR6_EL1 */
	ARM64_SYS_REG(3, 0, 0, 3, 0),	/* MVFR0_EL1 */
	ARM64_SYS_REG(3, 0, 0, 3, 1),	/* MVFR1_EL1 */
	ARM64_SYS_REG(3, 0, 0, 3, 2),	/* MVFR2_EL1 */
	ARM64_SYS_REG(3, 0, 0, 3, 3),
	ARM64_SYS_REG(3, 0, 0, 3, 4),	/* ID_PFR2_EL1 */
	ARM64_SYS_REG(3, 0, 0, 3, 5),	/* ID_DFR1_EL1 */
	ARM64_SYS_REG(3, 0, 0, 3, 6),	/* ID_MMFR5_EL1 */
	ARM64_SYS_REG(3, 0, 0, 3, 7),
	ARM64_SYS_REG(3, 0, 0, 4, 0),	/* ID_AA64PFR0_EL1 */
	ARM64_SYS_REG(3, 0, 0, 4, 1),	/* ID_AA64PFR1_EL1 */
	ARM64_SYS_REG(3, 0, 0, 4, 2),
	ARM64_SYS_REG(3, 0, 0, 4, 3),
	ARM64_SYS_REG(3, 0, 0, 4, 4),	/* ID_AA64ZFR0_EL1 */
	ARM64_SYS_REG(3, 0, 0, 4, 5),
	ARM64_SYS_REG(3, 0, 0, 4, 6),
	ARM64_SYS_REG(3, 0, 0, 4, 7),
	ARM64_SYS_REG(3, 0, 0, 5, 0),	/* ID_AA64DFR0_EL1 */
	ARM64_SYS_REG(3, 0, 0, 5, 1),	/* ID_AA64DFR1_EL1 */
	ARM64_SYS_REG(3, 0, 0, 5, 2),
	ARM64_SYS_REG(3, 0, 0, 5, 3),
	ARM64_SYS_REG(3, 0, 0, 5, 4),	/* ID_AA64AFR0_EL1 */
	ARM64_SYS_REG(3, 0, 0, 5, 5),	/* ID_AA64AFR1_EL1 */
	ARM64_SYS_REG(3, 0, 0, 5, 6),
	ARM64_SYS_REG(3, 0, 0, 5, 7),
	ARM64_SYS_REG(3, 0, 0, 6, 0),	/* ID_AA64ISAR0_EL1 */
	ARM64_SYS_REG(3, 0, 0, 6, 1),	/* ID_AA64ISAR1_EL1 */
	ARM64_SYS_REG(3, 0, 0, 6, 2),
	ARM64_SYS_REG(3, 0, 0, 6, 3),
	ARM64_SYS_REG(3, 0, 0, 6, 4),
	ARM64_SYS_REG(3, 0, 0, 6, 5),
	ARM64_SYS_REG(3, 0, 0, 6, 6),
	ARM64_SYS_REG(3, 0, 0, 6, 7),
	ARM64_SYS_REG(3, 0, 0, 7, 0),	/* ID_AA64MMFR0_EL1 */
	ARM64_SYS_REG(3, 0, 0, 7, 1),	/* ID_AA64MMFR1_EL1 */
	ARM64_SYS_REG(3, 0, 0, 7, 2),	/* ID_AA64MMFR2_EL1 */
	ARM64_SYS_REG(3, 0, 0, 7, 3),
	ARM64_SYS_REG(3, 0, 0, 7, 4),
	ARM64_SYS_REG(3, 0, 0, 7, 5),
	ARM64_SYS_REG(3, 0, 0, 7, 6),
	ARM64_SYS_REG(3, 0, 0, 7, 7),
	ARM64_SYS_REG(3, 0, 1, 0, 0),	/* SCTLR_EL1 */
	ARM64_SYS_REG(3, 0, 1, 0, 1),	/* ACTLR_EL1 */
	ARM64_SYS_REG(3, 0, 1, 0, 2),	/* CPACR_EL1 */
	ARM64_SYS_REG(3, 0, 2, 0, 0),	/* TTBR0_EL1 */
	ARM64_SYS_REG(3, 0, 2, 0, 1),	/* TTBR1_EL1 */
	ARM64_SYS_REG(3, 0, 2, 0, 2),	/* TCR_EL1 */
	ARM64_SYS_REG(3, 0, 5, 1, 0),	/* AFSR0_EL1 */
	ARM64_SYS_REG(3, 0, 5, 1, 1),	/* AFSR1_EL1 */
	ARM64_SYS_REG(3, 0, 5, 2, 0),	/* ESR_EL1 */
	ARM64_SYS_REG(3, 0, 6, 0, 0),	/* FAR_EL1 */
	ARM64_SYS_REG(3, 0, 7, 4, 0),	/* PAR_EL1 */
	ARM64_SYS_REG(3, 0, 9, 14, 1),	/* PMINTENSET_EL1 */
	ARM64_SYS_REG(3, 0, 9, 14, 2),	/* PMINTENCLR_EL1 */
	ARM64_SYS_REG(3, 0, 10, 2, 0),	/* MAIR_EL1 */
	ARM64_SYS_REG(3, 0, 10, 3, 0),	/* AMAIR_EL1 */
	ARM64_SYS_REG(3, 0, 12, 0, 0),	/* VBAR_EL1 */
	ARM64_SYS_REG(3, 0, 12, 1, 1),	/* DISR_EL1 */
	ARM64_SYS_REG(3, 0, 13, 0, 1),	/* CONTEXTIDR_EL1 */
	ARM64_SYS_REG(3, 0, 13, 0, 4),	/* TPIDR_EL1 */
	ARM64_SYS_REG(3, 0, 14, 1, 0),	/* CNTKCTL_EL1 */
	ARM64_SYS_REG(3, 2, 0, 0, 0),	/* CSSELR_EL1 */
	ARM64_SYS_REG(3, 3, 9, 12, 0),	/* PMCR_EL0 */
	ARM64_SYS_REG(3, 3, 9, 12, 1),	/* PMCNTENSET_EL0 */
	ARM64_SYS_REG(3, 3, 9, 12, 2),	/* PMCNTENCLR_EL0 */
	ARM64_SYS_REG(3, 3, 9, 12, 3),	/* PMOVSCLR_EL0 */
	ARM64_SYS_REG(3, 3, 9, 12, 4),	/* PMSWINC_EL0 */
	ARM64_SYS_REG(3, 3, 9, 12, 5),	/* PMSELR_EL0 */
	ARM64_SYS_REG(3, 3, 9, 13, 0),	/* PMCCNTR_EL0 */
	ARM64_SYS_REG(3, 3, 9, 14, 0),	/* PMUSERENR_EL0 */
	ARM64_SYS_REG(3, 3, 9, 14, 3),	/* PMOVSSET_EL0 */
	ARM64_SYS_REG(3, 3, 13, 0, 2),	/* TPIDR_EL0 */
	ARM64_SYS_REG(3, 3, 13, 0, 3),	/* TPIDRRO_EL0 */
	ARM64_SYS_REG(3, 3, 14, 8, 0),
	ARM64_SYS_REG(3, 3, 14, 8, 1),
	ARM64_SYS_REG(3, 3, 14, 8, 2),
	ARM64_SYS_REG(3, 3, 14, 8, 3),
	ARM64_SYS_REG(3, 3, 14, 8, 4),
	ARM64_SYS_REG(3, 3, 14, 8, 5),
	ARM64_SYS_REG(3, 3, 14, 8, 6),
	ARM64_SYS_REG(3, 3, 14, 8, 7),
	ARM64_SYS_REG(3, 3, 14, 9, 0),
	ARM64_SYS_REG(3, 3, 14, 9, 1),
	ARM64_SYS_REG(3, 3, 14, 9, 2),
	ARM64_SYS_REG(3, 3, 14, 9, 3),
	ARM64_SYS_REG(3, 3, 14, 9, 4),
	ARM64_SYS_REG(3, 3, 14, 9, 5),
	ARM64_SYS_REG(3, 3, 14, 9, 6),
	ARM64_SYS_REG(3, 3, 14, 9, 7),
	ARM64_SYS_REG(3, 3, 14, 10, 0),
	ARM64_SYS_REG(3, 3, 14, 10, 1),
	ARM64_SYS_REG(3, 3, 14, 10, 2),
	ARM64_SYS_REG(3, 3, 14, 10, 3),
	ARM64_SYS_REG(3, 3, 14, 10, 4),
	ARM64_SYS_REG(3, 3, 14, 10, 5),
	ARM64_SYS_REG(3, 3, 14, 10, 6),
	ARM64_SYS_REG(3, 3, 14, 10, 7),
	ARM64_SYS_REG(3, 3, 14, 11, 0),
	ARM64_SYS_REG(3, 3, 14, 11, 1),
	ARM64_SYS_REG(3, 3, 14, 11, 2),
	ARM64_SYS_REG(3, 3, 14, 11, 3),
	ARM64_SYS_REG(3, 3, 14, 11, 4),
	ARM64_SYS_REG(3, 3, 14, 11, 5),
	ARM64_SYS_REG(3, 3, 14, 11, 6),
	ARM64_SYS_REG(3, 3, 14, 12, 0),
	ARM64_SYS_REG(3, 3, 14, 12, 1),
	ARM64_SYS_REG(3, 3, 14, 12, 2),
	ARM64_SYS_REG(3, 3, 14, 12, 3),
	ARM64_SYS_REG(3, 3, 14, 12, 4),
	ARM64_SYS_REG(3, 3, 14, 12, 5),
	ARM64_SYS_REG(3, 3, 14, 12, 6),
	ARM64_SYS_REG(3, 3, 14, 12, 7),
	ARM64_SYS_REG(3, 3, 14, 13, 0),
	ARM64_SYS_REG(3, 3, 14, 13, 1),
	ARM64_SYS_REG(3, 3, 14, 13, 2),
	ARM64_SYS_REG(3, 3, 14, 13, 3),
	ARM64_SYS_REG(3, 3, 14, 13, 4),
	ARM64_SYS_REG(3, 3, 14, 13, 5),
	ARM64_SYS_REG(3, 3, 14, 13, 6),
	ARM64_SYS_REG(3, 3, 14, 13, 7),
	ARM64_SYS_REG(3, 3, 14, 14, 0),
	ARM64_SYS_REG(3, 3, 14, 14, 1),
	ARM64_SYS_REG(3, 3, 14, 14, 2),
	ARM64_SYS_REG(3, 3, 14, 14, 3),
	ARM64_SYS_REG(3, 3, 14, 14, 4),
	ARM64_SYS_REG(3, 3, 14, 14, 5),
	ARM64_SYS_REG(3, 3, 14, 14, 6),
	ARM64_SYS_REG(3, 3, 14, 14, 7),
	ARM64_SYS_REG(3, 3, 14, 15, 0),
	ARM64_SYS_REG(3, 3, 14, 15, 1),
	ARM64_SYS_REG(3, 3, 14, 15, 2),
	ARM64_SYS_REG(3, 3, 14, 15, 3),
	ARM64_SYS_REG(3, 3, 14, 15, 4),
	ARM64_SYS_REG(3, 3, 14, 15, 5),
	ARM64_SYS_REG(3, 3, 14, 15, 6),
	ARM64_SYS_REG(3, 3, 14, 15, 7),	/* PMCCFILTR_EL0 */
	ARM64_SYS_REG(3, 4, 3, 0, 0),	/* DACR32_EL2 */
	ARM64_SYS_REG(3, 4, 5, 0, 1),	/* IFSR32_EL2 */
	ARM64_SYS_REG(3, 4, 5, 3, 0),	/* FPEXC32_EL2 */
पूर्ण;
अटल __u64 base_regs_n = ARRAY_SIZE(base_regs);

अटल __u64 vregs[] = अणु
	KVM_REG_ARM64 | KVM_REG_SIZE_U128 | KVM_REG_ARM_CORE | KVM_REG_ARM_CORE_REG(fp_regs.vregs[0]),
	KVM_REG_ARM64 | KVM_REG_SIZE_U128 | KVM_REG_ARM_CORE | KVM_REG_ARM_CORE_REG(fp_regs.vregs[1]),
	KVM_REG_ARM64 | KVM_REG_SIZE_U128 | KVM_REG_ARM_CORE | KVM_REG_ARM_CORE_REG(fp_regs.vregs[2]),
	KVM_REG_ARM64 | KVM_REG_SIZE_U128 | KVM_REG_ARM_CORE | KVM_REG_ARM_CORE_REG(fp_regs.vregs[3]),
	KVM_REG_ARM64 | KVM_REG_SIZE_U128 | KVM_REG_ARM_CORE | KVM_REG_ARM_CORE_REG(fp_regs.vregs[4]),
	KVM_REG_ARM64 | KVM_REG_SIZE_U128 | KVM_REG_ARM_CORE | KVM_REG_ARM_CORE_REG(fp_regs.vregs[5]),
	KVM_REG_ARM64 | KVM_REG_SIZE_U128 | KVM_REG_ARM_CORE | KVM_REG_ARM_CORE_REG(fp_regs.vregs[6]),
	KVM_REG_ARM64 | KVM_REG_SIZE_U128 | KVM_REG_ARM_CORE | KVM_REG_ARM_CORE_REG(fp_regs.vregs[7]),
	KVM_REG_ARM64 | KVM_REG_SIZE_U128 | KVM_REG_ARM_CORE | KVM_REG_ARM_CORE_REG(fp_regs.vregs[8]),
	KVM_REG_ARM64 | KVM_REG_SIZE_U128 | KVM_REG_ARM_CORE | KVM_REG_ARM_CORE_REG(fp_regs.vregs[9]),
	KVM_REG_ARM64 | KVM_REG_SIZE_U128 | KVM_REG_ARM_CORE | KVM_REG_ARM_CORE_REG(fp_regs.vregs[10]),
	KVM_REG_ARM64 | KVM_REG_SIZE_U128 | KVM_REG_ARM_CORE | KVM_REG_ARM_CORE_REG(fp_regs.vregs[11]),
	KVM_REG_ARM64 | KVM_REG_SIZE_U128 | KVM_REG_ARM_CORE | KVM_REG_ARM_CORE_REG(fp_regs.vregs[12]),
	KVM_REG_ARM64 | KVM_REG_SIZE_U128 | KVM_REG_ARM_CORE | KVM_REG_ARM_CORE_REG(fp_regs.vregs[13]),
	KVM_REG_ARM64 | KVM_REG_SIZE_U128 | KVM_REG_ARM_CORE | KVM_REG_ARM_CORE_REG(fp_regs.vregs[14]),
	KVM_REG_ARM64 | KVM_REG_SIZE_U128 | KVM_REG_ARM_CORE | KVM_REG_ARM_CORE_REG(fp_regs.vregs[15]),
	KVM_REG_ARM64 | KVM_REG_SIZE_U128 | KVM_REG_ARM_CORE | KVM_REG_ARM_CORE_REG(fp_regs.vregs[16]),
	KVM_REG_ARM64 | KVM_REG_SIZE_U128 | KVM_REG_ARM_CORE | KVM_REG_ARM_CORE_REG(fp_regs.vregs[17]),
	KVM_REG_ARM64 | KVM_REG_SIZE_U128 | KVM_REG_ARM_CORE | KVM_REG_ARM_CORE_REG(fp_regs.vregs[18]),
	KVM_REG_ARM64 | KVM_REG_SIZE_U128 | KVM_REG_ARM_CORE | KVM_REG_ARM_CORE_REG(fp_regs.vregs[19]),
	KVM_REG_ARM64 | KVM_REG_SIZE_U128 | KVM_REG_ARM_CORE | KVM_REG_ARM_CORE_REG(fp_regs.vregs[20]),
	KVM_REG_ARM64 | KVM_REG_SIZE_U128 | KVM_REG_ARM_CORE | KVM_REG_ARM_CORE_REG(fp_regs.vregs[21]),
	KVM_REG_ARM64 | KVM_REG_SIZE_U128 | KVM_REG_ARM_CORE | KVM_REG_ARM_CORE_REG(fp_regs.vregs[22]),
	KVM_REG_ARM64 | KVM_REG_SIZE_U128 | KVM_REG_ARM_CORE | KVM_REG_ARM_CORE_REG(fp_regs.vregs[23]),
	KVM_REG_ARM64 | KVM_REG_SIZE_U128 | KVM_REG_ARM_CORE | KVM_REG_ARM_CORE_REG(fp_regs.vregs[24]),
	KVM_REG_ARM64 | KVM_REG_SIZE_U128 | KVM_REG_ARM_CORE | KVM_REG_ARM_CORE_REG(fp_regs.vregs[25]),
	KVM_REG_ARM64 | KVM_REG_SIZE_U128 | KVM_REG_ARM_CORE | KVM_REG_ARM_CORE_REG(fp_regs.vregs[26]),
	KVM_REG_ARM64 | KVM_REG_SIZE_U128 | KVM_REG_ARM_CORE | KVM_REG_ARM_CORE_REG(fp_regs.vregs[27]),
	KVM_REG_ARM64 | KVM_REG_SIZE_U128 | KVM_REG_ARM_CORE | KVM_REG_ARM_CORE_REG(fp_regs.vregs[28]),
	KVM_REG_ARM64 | KVM_REG_SIZE_U128 | KVM_REG_ARM_CORE | KVM_REG_ARM_CORE_REG(fp_regs.vregs[29]),
	KVM_REG_ARM64 | KVM_REG_SIZE_U128 | KVM_REG_ARM_CORE | KVM_REG_ARM_CORE_REG(fp_regs.vregs[30]),
	KVM_REG_ARM64 | KVM_REG_SIZE_U128 | KVM_REG_ARM_CORE | KVM_REG_ARM_CORE_REG(fp_regs.vregs[31]),
पूर्ण;
अटल __u64 vregs_n = ARRAY_SIZE(vregs);

अटल __u64 sve_regs[] = अणु
	KVM_REG_ARM64_SVE_VLS,
	KVM_REG_ARM64_SVE_ZREG(0, 0),
	KVM_REG_ARM64_SVE_ZREG(1, 0),
	KVM_REG_ARM64_SVE_ZREG(2, 0),
	KVM_REG_ARM64_SVE_ZREG(3, 0),
	KVM_REG_ARM64_SVE_ZREG(4, 0),
	KVM_REG_ARM64_SVE_ZREG(5, 0),
	KVM_REG_ARM64_SVE_ZREG(6, 0),
	KVM_REG_ARM64_SVE_ZREG(7, 0),
	KVM_REG_ARM64_SVE_ZREG(8, 0),
	KVM_REG_ARM64_SVE_ZREG(9, 0),
	KVM_REG_ARM64_SVE_ZREG(10, 0),
	KVM_REG_ARM64_SVE_ZREG(11, 0),
	KVM_REG_ARM64_SVE_ZREG(12, 0),
	KVM_REG_ARM64_SVE_ZREG(13, 0),
	KVM_REG_ARM64_SVE_ZREG(14, 0),
	KVM_REG_ARM64_SVE_ZREG(15, 0),
	KVM_REG_ARM64_SVE_ZREG(16, 0),
	KVM_REG_ARM64_SVE_ZREG(17, 0),
	KVM_REG_ARM64_SVE_ZREG(18, 0),
	KVM_REG_ARM64_SVE_ZREG(19, 0),
	KVM_REG_ARM64_SVE_ZREG(20, 0),
	KVM_REG_ARM64_SVE_ZREG(21, 0),
	KVM_REG_ARM64_SVE_ZREG(22, 0),
	KVM_REG_ARM64_SVE_ZREG(23, 0),
	KVM_REG_ARM64_SVE_ZREG(24, 0),
	KVM_REG_ARM64_SVE_ZREG(25, 0),
	KVM_REG_ARM64_SVE_ZREG(26, 0),
	KVM_REG_ARM64_SVE_ZREG(27, 0),
	KVM_REG_ARM64_SVE_ZREG(28, 0),
	KVM_REG_ARM64_SVE_ZREG(29, 0),
	KVM_REG_ARM64_SVE_ZREG(30, 0),
	KVM_REG_ARM64_SVE_ZREG(31, 0),
	KVM_REG_ARM64_SVE_PREG(0, 0),
	KVM_REG_ARM64_SVE_PREG(1, 0),
	KVM_REG_ARM64_SVE_PREG(2, 0),
	KVM_REG_ARM64_SVE_PREG(3, 0),
	KVM_REG_ARM64_SVE_PREG(4, 0),
	KVM_REG_ARM64_SVE_PREG(5, 0),
	KVM_REG_ARM64_SVE_PREG(6, 0),
	KVM_REG_ARM64_SVE_PREG(7, 0),
	KVM_REG_ARM64_SVE_PREG(8, 0),
	KVM_REG_ARM64_SVE_PREG(9, 0),
	KVM_REG_ARM64_SVE_PREG(10, 0),
	KVM_REG_ARM64_SVE_PREG(11, 0),
	KVM_REG_ARM64_SVE_PREG(12, 0),
	KVM_REG_ARM64_SVE_PREG(13, 0),
	KVM_REG_ARM64_SVE_PREG(14, 0),
	KVM_REG_ARM64_SVE_PREG(15, 0),
	KVM_REG_ARM64_SVE_FFR(0),
	ARM64_SYS_REG(3, 0, 1, 2, 0),   /* ZCR_EL1 */
पूर्ण;
अटल __u64 sve_regs_n = ARRAY_SIZE(sve_regs);

अटल __u64 rejects_set[] = अणु
#अगर_घोषित REG_LIST_SVE
	KVM_REG_ARM64_SVE_VLS,
#पूर्ण_अगर
पूर्ण;
अटल __u64 rejects_set_n = ARRAY_SIZE(rejects_set);
