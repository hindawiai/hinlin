<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Record and handle CPU attributes.
 *
 * Copyright (C) 2014 ARM Ltd.
 */
#समावेश <यंत्र/arch_समयr.h>
#समावेश <यंत्र/cache.h>
#समावेश <यंत्र/cpu.h>
#समावेश <यंत्र/cputype.h>
#समावेश <यंत्र/cpufeature.h>
#समावेश <यंत्र/fpsimd.h>

#समावेश <linux/bitops.h>
#समावेश <linux/bug.h>
#समावेश <linux/compat.h>
#समावेश <linux/elf.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/personality.h>
#समावेश <linux/preempt.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/sched.h>
#समावेश <linux/smp.h>
#समावेश <linux/delay.h>

/*
 * In हाल the boot CPU is hotpluggable, we record its initial state and
 * current state separately. Certain प्रणाली रेजिस्टरs may contain dअगरferent
 * values depending on configuration at or after reset.
 */
DEFINE_PER_CPU(काष्ठा cpuinfo_arm64, cpu_data);
अटल काष्ठा cpuinfo_arm64 boot_cpu_data;

अटल स्थिर अक्षर *icache_policy_str[] = अणु
	[ICACHE_POLICY_VPIPT]		= "VPIPT",
	[ICACHE_POLICY_RESERVED]	= "RESERVED/UNKNOWN",
	[ICACHE_POLICY_VIPT]		= "VIPT",
	[ICACHE_POLICY_PIPT]		= "PIPT",
पूर्ण;

अचिन्हित दीर्घ __icache_flags;

अटल स्थिर अक्षर *स्थिर hwcap_str[] = अणु
	[KERNEL_HWCAP_FP]		= "fp",
	[KERNEL_HWCAP_ASIMD]		= "asimd",
	[KERNEL_HWCAP_EVTSTRM]		= "evtstrm",
	[KERNEL_HWCAP_AES]		= "aes",
	[KERNEL_HWCAP_PMULL]		= "pmull",
	[KERNEL_HWCAP_SHA1]		= "sha1",
	[KERNEL_HWCAP_SHA2]		= "sha2",
	[KERNEL_HWCAP_CRC32]		= "crc32",
	[KERNEL_HWCAP_ATOMICS]		= "atomics",
	[KERNEL_HWCAP_FPHP]		= "fphp",
	[KERNEL_HWCAP_ASIMDHP]		= "asimdhp",
	[KERNEL_HWCAP_CPUID]		= "cpuid",
	[KERNEL_HWCAP_ASIMDRDM]		= "asimdrdm",
	[KERNEL_HWCAP_JSCVT]		= "jscvt",
	[KERNEL_HWCAP_FCMA]		= "fcma",
	[KERNEL_HWCAP_LRCPC]		= "lrcpc",
	[KERNEL_HWCAP_DCPOP]		= "dcpop",
	[KERNEL_HWCAP_SHA3]		= "sha3",
	[KERNEL_HWCAP_SM3]		= "sm3",
	[KERNEL_HWCAP_SM4]		= "sm4",
	[KERNEL_HWCAP_ASIMDDP]		= "asimddp",
	[KERNEL_HWCAP_SHA512]		= "sha512",
	[KERNEL_HWCAP_SVE]		= "sve",
	[KERNEL_HWCAP_ASIMDFHM]		= "asimdfhm",
	[KERNEL_HWCAP_DIT]		= "dit",
	[KERNEL_HWCAP_USCAT]		= "uscat",
	[KERNEL_HWCAP_ILRCPC]		= "ilrcpc",
	[KERNEL_HWCAP_FLAGM]		= "flagm",
	[KERNEL_HWCAP_SSBS]		= "ssbs",
	[KERNEL_HWCAP_SB]		= "sb",
	[KERNEL_HWCAP_PACA]		= "paca",
	[KERNEL_HWCAP_PACG]		= "pacg",
	[KERNEL_HWCAP_DCPODP]		= "dcpodp",
	[KERNEL_HWCAP_SVE2]		= "sve2",
	[KERNEL_HWCAP_SVEAES]		= "sveaes",
	[KERNEL_HWCAP_SVEPMULL]		= "svepmull",
	[KERNEL_HWCAP_SVEBITPERM]	= "svebitperm",
	[KERNEL_HWCAP_SVESHA3]		= "svesha3",
	[KERNEL_HWCAP_SVESM4]		= "svesm4",
	[KERNEL_HWCAP_FLAGM2]		= "flagm2",
	[KERNEL_HWCAP_FRINT]		= "frint",
	[KERNEL_HWCAP_SVEI8MM]		= "svei8mm",
	[KERNEL_HWCAP_SVEF32MM]		= "svef32mm",
	[KERNEL_HWCAP_SVEF64MM]		= "svef64mm",
	[KERNEL_HWCAP_SVEBF16]		= "svebf16",
	[KERNEL_HWCAP_I8MM]		= "i8mm",
	[KERNEL_HWCAP_BF16]		= "bf16",
	[KERNEL_HWCAP_DGH]		= "dgh",
	[KERNEL_HWCAP_RNG]		= "rng",
	[KERNEL_HWCAP_BTI]		= "bti",
	[KERNEL_HWCAP_MTE]		= "mte",
पूर्ण;

#अगर_घोषित CONFIG_COMPAT
#घोषणा COMPAT_KERNEL_HWCAP(x)	स्थिर_ilog2(COMPAT_HWCAP_ ## x)
अटल स्थिर अक्षर *स्थिर compat_hwcap_str[] = अणु
	[COMPAT_KERNEL_HWCAP(SWP)]	= "swp",
	[COMPAT_KERNEL_HWCAP(HALF)]	= "half",
	[COMPAT_KERNEL_HWCAP(THUMB)]	= "thumb",
	[COMPAT_KERNEL_HWCAP(26BIT)]	= शून्य,	/* Not possible on arm64 */
	[COMPAT_KERNEL_HWCAP(FAST_MULT)] = "fastmult",
	[COMPAT_KERNEL_HWCAP(FPA)]	= शून्य,	/* Not possible on arm64 */
	[COMPAT_KERNEL_HWCAP(VFP)]	= "vfp",
	[COMPAT_KERNEL_HWCAP(EDSP)]	= "edsp",
	[COMPAT_KERNEL_HWCAP(JAVA)]	= शून्य,	/* Not possible on arm64 */
	[COMPAT_KERNEL_HWCAP(IWMMXT)]	= शून्य,	/* Not possible on arm64 */
	[COMPAT_KERNEL_HWCAP(CRUNCH)]	= शून्य,	/* Not possible on arm64 */
	[COMPAT_KERNEL_HWCAP(THUMBEE)]	= शून्य,	/* Not possible on arm64 */
	[COMPAT_KERNEL_HWCAP(NEON)]	= "neon",
	[COMPAT_KERNEL_HWCAP(VFPv3)]	= "vfpv3",
	[COMPAT_KERNEL_HWCAP(VFPV3D16)]	= शून्य,	/* Not possible on arm64 */
	[COMPAT_KERNEL_HWCAP(TLS)]	= "tls",
	[COMPAT_KERNEL_HWCAP(VFPv4)]	= "vfpv4",
	[COMPAT_KERNEL_HWCAP(IDIVA)]	= "idiva",
	[COMPAT_KERNEL_HWCAP(IDIVT)]	= "idivt",
	[COMPAT_KERNEL_HWCAP(VFPD32)]	= शून्य,	/* Not possible on arm64 */
	[COMPAT_KERNEL_HWCAP(LPAE)]	= "lpae",
	[COMPAT_KERNEL_HWCAP(EVTSTRM)]	= "evtstrm",
पूर्ण;

#घोषणा COMPAT_KERNEL_HWCAP2(x)	स्थिर_ilog2(COMPAT_HWCAP2_ ## x)
अटल स्थिर अक्षर *स्थिर compat_hwcap2_str[] = अणु
	[COMPAT_KERNEL_HWCAP2(AES)]	= "aes",
	[COMPAT_KERNEL_HWCAP2(PMULL)]	= "pmull",
	[COMPAT_KERNEL_HWCAP2(SHA1)]	= "sha1",
	[COMPAT_KERNEL_HWCAP2(SHA2)]	= "sha2",
	[COMPAT_KERNEL_HWCAP2(CRC32)]	= "crc32",
पूर्ण;
#पूर्ण_अगर /* CONFIG_COMPAT */

अटल पूर्णांक c_show(काष्ठा seq_file *m, व्योम *v)
अणु
	पूर्णांक i, j;
	bool compat = personality(current->personality) == PER_LINUX32;

	क्रम_each_online_cpu(i) अणु
		काष्ठा cpuinfo_arm64 *cpuinfo = &per_cpu(cpu_data, i);
		u32 midr = cpuinfo->reg_midr;

		/*
		 * glibc पढ़ोs /proc/cpuinfo to determine the number of
		 * online processors, looking क्रम lines beginning with
		 * "processor".  Give glibc what it expects.
		 */
		seq_म_लिखो(m, "processor\t: %d\n", i);
		अगर (compat)
			seq_म_लिखो(m, "model name\t: ARMv8 Processor rev %d (%s)\n",
				   MIDR_REVISION(midr), COMPAT_ELF_PLATFORM);

		seq_म_लिखो(m, "BogoMIPS\t: %lu.%02lu\n",
			   loops_per_jअगरfy / (500000UL/HZ),
			   loops_per_jअगरfy / (5000UL/HZ) % 100);

		/*
		 * Dump out the common processor features in a single line.
		 * Userspace should पढ़ो the hwcaps with getauxval(AT_HWCAP)
		 * rather than attempting to parse this, but there's a body of
		 * software which करोes alपढ़ोy (at least क्रम 32-bit).
		 */
		seq_माला_दो(m, "Features\t:");
		अगर (compat) अणु
#अगर_घोषित CONFIG_COMPAT
			क्रम (j = 0; j < ARRAY_SIZE(compat_hwcap_str); j++) अणु
				अगर (compat_elf_hwcap & (1 << j)) अणु
					/*
					 * Warn once अगर any feature should not
					 * have been present on arm64 platक्रमm.
					 */
					अगर (WARN_ON_ONCE(!compat_hwcap_str[j]))
						जारी;

					seq_म_लिखो(m, " %s", compat_hwcap_str[j]);
				पूर्ण
			पूर्ण

			क्रम (j = 0; j < ARRAY_SIZE(compat_hwcap2_str); j++)
				अगर (compat_elf_hwcap2 & (1 << j))
					seq_म_लिखो(m, " %s", compat_hwcap2_str[j]);
#पूर्ण_अगर /* CONFIG_COMPAT */
		पूर्ण अन्यथा अणु
			क्रम (j = 0; j < ARRAY_SIZE(hwcap_str); j++)
				अगर (cpu_have_feature(j))
					seq_म_लिखो(m, " %s", hwcap_str[j]);
		पूर्ण
		seq_माला_दो(m, "\n");

		seq_म_लिखो(m, "CPU implementer\t: 0x%02x\n",
			   MIDR_IMPLEMENTOR(midr));
		seq_म_लिखो(m, "CPU architecture: 8\n");
		seq_म_लिखो(m, "CPU variant\t: 0x%x\n", MIDR_VARIANT(midr));
		seq_म_लिखो(m, "CPU part\t: 0x%03x\n", MIDR_PARTNUM(midr));
		seq_म_लिखो(m, "CPU revision\t: %d\n\n", MIDR_REVISION(midr));
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम *c_start(काष्ठा seq_file *m, loff_t *pos)
अणु
	वापस *pos < 1 ? (व्योम *)1 : शून्य;
पूर्ण

अटल व्योम *c_next(काष्ठा seq_file *m, व्योम *v, loff_t *pos)
अणु
	++*pos;
	वापस शून्य;
पूर्ण

अटल व्योम c_stop(काष्ठा seq_file *m, व्योम *v)
अणु
पूर्ण

स्थिर काष्ठा seq_operations cpuinfo_op = अणु
	.start	= c_start,
	.next	= c_next,
	.stop	= c_stop,
	.show	= c_show
पूर्ण;


अटल काष्ठा kobj_type cpuregs_kobj_type = अणु
	.sysfs_ops = &kobj_sysfs_ops,
पूर्ण;

/*
 * The ARM ARM uses the phrase "32-bit register" to describe a रेजिस्टर
 * whose upper 32 bits are RES0 (per C5.1.1, ARM DDI 0487A.i), however
 * no statement is made as to whether the upper 32 bits will or will not
 * be made use of in future, and between ARM DDI 0487A.c and ARM DDI
 * 0487A.d CLIDR_EL1 was expanded from 32-bit to 64-bit.
 *
 * Thus, जबतक both MIDR_EL1 and REVIDR_EL1 are described as 32-bit
 * रेजिस्टरs, we expose them both as 64 bit values to cater क्रम possible
 * future expansion without an ABI अवरोध.
 */
#घोषणा kobj_to_cpuinfo(kobj)	container_of(kobj, काष्ठा cpuinfo_arm64, kobj)
#घोषणा CPUREGS_ATTR_RO(_name, _field)						\
	अटल sमाप_प्रकार _name##_show(काष्ठा kobject *kobj,			\
			काष्ठा kobj_attribute *attr, अक्षर *buf)			\
	अणु									\
		काष्ठा cpuinfo_arm64 *info = kobj_to_cpuinfo(kobj);		\
										\
		अगर (info->reg_midr)						\
			वापस प्र_लिखो(buf, "0x%016x\n", info->reg_##_field);	\
		अन्यथा								\
			वापस 0;						\
	पूर्ण									\
	अटल काष्ठा kobj_attribute cpuregs_attr_##_name = __ATTR_RO(_name)

CPUREGS_ATTR_RO(midr_el1, midr);
CPUREGS_ATTR_RO(revidr_el1, revidr);

अटल काष्ठा attribute *cpuregs_id_attrs[] = अणु
	&cpuregs_attr_midr_el1.attr,
	&cpuregs_attr_revidr_el1.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group cpuregs_attr_group = अणु
	.attrs = cpuregs_id_attrs,
	.name = "identification"
पूर्ण;

अटल पूर्णांक cpuid_cpu_online(अचिन्हित पूर्णांक cpu)
अणु
	पूर्णांक rc;
	काष्ठा device *dev;
	काष्ठा cpuinfo_arm64 *info = &per_cpu(cpu_data, cpu);

	dev = get_cpu_device(cpu);
	अगर (!dev) अणु
		rc = -ENODEV;
		जाओ out;
	पूर्ण
	rc = kobject_add(&info->kobj, &dev->kobj, "regs");
	अगर (rc)
		जाओ out;
	rc = sysfs_create_group(&info->kobj, &cpuregs_attr_group);
	अगर (rc)
		kobject_del(&info->kobj);
out:
	वापस rc;
पूर्ण

अटल पूर्णांक cpuid_cpu_offline(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा device *dev;
	काष्ठा cpuinfo_arm64 *info = &per_cpu(cpu_data, cpu);

	dev = get_cpu_device(cpu);
	अगर (!dev)
		वापस -ENODEV;
	अगर (info->kobj.parent) अणु
		sysfs_हटाओ_group(&info->kobj, &cpuregs_attr_group);
		kobject_del(&info->kobj);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __init cpuinfo_regs_init(व्योम)
अणु
	पूर्णांक cpu, ret;

	क्रम_each_possible_cpu(cpu) अणु
		काष्ठा cpuinfo_arm64 *info = &per_cpu(cpu_data, cpu);

		kobject_init(&info->kobj, &cpuregs_kobj_type);
	पूर्ण

	ret = cpuhp_setup_state(CPUHP_AP_ONLINE_DYN, "arm64/cpuinfo:online",
				cpuid_cpu_online, cpuid_cpu_offline);
	अगर (ret < 0) अणु
		pr_err("cpuinfo: failed to register hotplug callbacks.\n");
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण
device_initcall(cpuinfo_regs_init);

अटल व्योम cpuinfo_detect_icache_policy(काष्ठा cpuinfo_arm64 *info)
अणु
	अचिन्हित पूर्णांक cpu = smp_processor_id();
	u32 l1ip = CTR_L1IP(info->reg_ctr);

	चयन (l1ip) अणु
	हाल ICACHE_POLICY_PIPT:
		अवरोध;
	हाल ICACHE_POLICY_VPIPT:
		set_bit(ICACHEF_VPIPT, &__icache_flags);
		अवरोध;
	हाल ICACHE_POLICY_RESERVED:
	हाल ICACHE_POLICY_VIPT:
		/* Assume aliasing */
		set_bit(ICACHEF_ALIASING, &__icache_flags);
		अवरोध;
	पूर्ण

	pr_info("Detected %s I-cache on CPU%d\n", icache_policy_str[l1ip], cpu);
पूर्ण

अटल व्योम __cpuinfo_store_cpu(काष्ठा cpuinfo_arm64 *info)
अणु
	info->reg_cntfrq = arch_समयr_get_cntfrq();
	/*
	 * Use the effective value of the CTR_EL0 than the raw value
	 * exposed by the CPU. CTR_EL0.IDC field value must be पूर्णांकerpreted
	 * with the CLIDR_EL1 fields to aव्योम triggering false warnings
	 * when there is a mismatch across the CPUs. Keep track of the
	 * effective value of the CTR_EL0 in our पूर्णांकernal records क्रम
	 * accurate sanity check and feature enablement.
	 */
	info->reg_ctr = पढ़ो_cpuid_effective_cachetype();
	info->reg_dczid = पढ़ो_cpuid(DCZID_EL0);
	info->reg_midr = पढ़ो_cpuid_id();
	info->reg_revidr = पढ़ो_cpuid(REVIDR_EL1);

	info->reg_id_aa64dfr0 = पढ़ो_cpuid(ID_AA64DFR0_EL1);
	info->reg_id_aa64dfr1 = पढ़ो_cpuid(ID_AA64DFR1_EL1);
	info->reg_id_aa64isar0 = पढ़ो_cpuid(ID_AA64ISAR0_EL1);
	info->reg_id_aa64isar1 = पढ़ो_cpuid(ID_AA64ISAR1_EL1);
	info->reg_id_aa64mmfr0 = पढ़ो_cpuid(ID_AA64MMFR0_EL1);
	info->reg_id_aa64mmfr1 = पढ़ो_cpuid(ID_AA64MMFR1_EL1);
	info->reg_id_aa64mmfr2 = पढ़ो_cpuid(ID_AA64MMFR2_EL1);
	info->reg_id_aa64pfr0 = पढ़ो_cpuid(ID_AA64PFR0_EL1);
	info->reg_id_aa64pfr1 = पढ़ो_cpuid(ID_AA64PFR1_EL1);
	info->reg_id_aa64zfr0 = पढ़ो_cpuid(ID_AA64ZFR0_EL1);

	/* Update the 32bit ID रेजिस्टरs only अगर AArch32 is implemented */
	अगर (id_aa64pfr0_32bit_el0(info->reg_id_aa64pfr0)) अणु
		info->reg_id_dfr0 = पढ़ो_cpuid(ID_DFR0_EL1);
		info->reg_id_dfr1 = पढ़ो_cpuid(ID_DFR1_EL1);
		info->reg_id_isar0 = पढ़ो_cpuid(ID_ISAR0_EL1);
		info->reg_id_isar1 = पढ़ो_cpuid(ID_ISAR1_EL1);
		info->reg_id_isar2 = पढ़ो_cpuid(ID_ISAR2_EL1);
		info->reg_id_isar3 = पढ़ो_cpuid(ID_ISAR3_EL1);
		info->reg_id_isar4 = पढ़ो_cpuid(ID_ISAR4_EL1);
		info->reg_id_isar5 = पढ़ो_cpuid(ID_ISAR5_EL1);
		info->reg_id_isar6 = पढ़ो_cpuid(ID_ISAR6_EL1);
		info->reg_id_mmfr0 = पढ़ो_cpuid(ID_MMFR0_EL1);
		info->reg_id_mmfr1 = पढ़ो_cpuid(ID_MMFR1_EL1);
		info->reg_id_mmfr2 = पढ़ो_cpuid(ID_MMFR2_EL1);
		info->reg_id_mmfr3 = पढ़ो_cpuid(ID_MMFR3_EL1);
		info->reg_id_mmfr4 = पढ़ो_cpuid(ID_MMFR4_EL1);
		info->reg_id_mmfr5 = पढ़ो_cpuid(ID_MMFR5_EL1);
		info->reg_id_pfr0 = पढ़ो_cpuid(ID_PFR0_EL1);
		info->reg_id_pfr1 = पढ़ो_cpuid(ID_PFR1_EL1);
		info->reg_id_pfr2 = पढ़ो_cpuid(ID_PFR2_EL1);

		info->reg_mvfr0 = पढ़ो_cpuid(MVFR0_EL1);
		info->reg_mvfr1 = पढ़ो_cpuid(MVFR1_EL1);
		info->reg_mvfr2 = पढ़ो_cpuid(MVFR2_EL1);
	पूर्ण

	अगर (IS_ENABLED(CONFIG_ARM64_SVE) &&
	    id_aa64pfr0_sve(info->reg_id_aa64pfr0))
		info->reg_zcr = पढ़ो_zcr_features();

	cpuinfo_detect_icache_policy(info);
पूर्ण

व्योम cpuinfo_store_cpu(व्योम)
अणु
	काष्ठा cpuinfo_arm64 *info = this_cpu_ptr(&cpu_data);
	__cpuinfo_store_cpu(info);
	update_cpu_features(smp_processor_id(), info, &boot_cpu_data);
पूर्ण

व्योम __init cpuinfo_store_boot_cpu(व्योम)
अणु
	काष्ठा cpuinfo_arm64 *info = &per_cpu(cpu_data, 0);
	__cpuinfo_store_cpu(info);

	boot_cpu_data = *info;
	init_cpu_features(&boot_cpu_data);
पूर्ण
