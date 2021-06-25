<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित ARCH_X86_KVM_REVERSE_CPUID_H
#घोषणा ARCH_X86_KVM_REVERSE_CPUID_H

#समावेश <uapi/यंत्र/kvm.h>
#समावेश <यंत्र/cpufeature.h>
#समावेश <यंत्र/cpufeatures.h>

/*
 * Hardware-defined CPUID leafs that are scattered in the kernel, but need to
 * be directly used by KVM.  Note, these word values conflict with the kernel's
 * "bug" caps, but KVM करोesn't use those.
 */
क्रमागत kvm_only_cpuid_leafs अणु
	CPUID_12_EAX	 = NCAPINTS,
	NR_KVM_CPU_CAPS,

	NKVMCAPINTS = NR_KVM_CPU_CAPS - NCAPINTS,
पूर्ण;

#घोषणा KVM_X86_FEATURE(w, f)		((w)*32 + (f))

/* Intel-defined SGX sub-features, CPUID level 0x12 (EAX). */
#घोषणा KVM_X86_FEATURE_SGX1		KVM_X86_FEATURE(CPUID_12_EAX, 0)
#घोषणा KVM_X86_FEATURE_SGX2		KVM_X86_FEATURE(CPUID_12_EAX, 1)

काष्ठा cpuid_reg अणु
	u32 function;
	u32 index;
	पूर्णांक reg;
पूर्ण;

अटल स्थिर काष्ठा cpuid_reg reverse_cpuid[] = अणु
	[CPUID_1_EDX]         = अणु         1, 0, CPUID_EDXपूर्ण,
	[CPUID_8000_0001_EDX] = अणु0x80000001, 0, CPUID_EDXपूर्ण,
	[CPUID_8086_0001_EDX] = अणु0x80860001, 0, CPUID_EDXपूर्ण,
	[CPUID_1_ECX]         = अणु         1, 0, CPUID_ECXपूर्ण,
	[CPUID_C000_0001_EDX] = अणु0xc0000001, 0, CPUID_EDXपूर्ण,
	[CPUID_8000_0001_ECX] = अणु0x80000001, 0, CPUID_ECXपूर्ण,
	[CPUID_7_0_EBX]       = अणु         7, 0, CPUID_EBXपूर्ण,
	[CPUID_D_1_EAX]       = अणु       0xd, 1, CPUID_EAXपूर्ण,
	[CPUID_8000_0008_EBX] = अणु0x80000008, 0, CPUID_EBXपूर्ण,
	[CPUID_6_EAX]         = अणु         6, 0, CPUID_EAXपूर्ण,
	[CPUID_8000_000A_EDX] = अणु0x8000000a, 0, CPUID_EDXपूर्ण,
	[CPUID_7_ECX]         = अणु         7, 0, CPUID_ECXपूर्ण,
	[CPUID_8000_0007_EBX] = अणु0x80000007, 0, CPUID_EBXपूर्ण,
	[CPUID_7_EDX]         = अणु         7, 0, CPUID_EDXपूर्ण,
	[CPUID_7_1_EAX]       = अणु         7, 1, CPUID_EAXपूर्ण,
	[CPUID_12_EAX]        = अणु0x00000012, 0, CPUID_EAXपूर्ण,
	[CPUID_8000_001F_EAX] = अणु0x8000001f, 0, CPUID_EAXपूर्ण,
पूर्ण;

/*
 * Reverse CPUID and its derivatives can only be used क्रम hardware-defined
 * feature words, i.e. words whose bits directly correspond to a CPUID leaf.
 * Retrieving a feature bit or masking guest CPUID from a Linux-defined word
 * is nonsensical as the bit number/mask is an arbitrary software-defined value
 * and can't be used by KVM to query/control guest capabilities.  And obviously
 * the leaf being queried must have an entry in the lookup table.
 */
अटल __always_अंतरभूत व्योम reverse_cpuid_check(अचिन्हित पूर्णांक x86_leaf)
अणु
	BUILD_BUG_ON(x86_leaf == CPUID_LNX_1);
	BUILD_BUG_ON(x86_leaf == CPUID_LNX_2);
	BUILD_BUG_ON(x86_leaf == CPUID_LNX_3);
	BUILD_BUG_ON(x86_leaf == CPUID_LNX_4);
	BUILD_BUG_ON(x86_leaf >= ARRAY_SIZE(reverse_cpuid));
	BUILD_BUG_ON(reverse_cpuid[x86_leaf].function == 0);
पूर्ण

/*
 * Translate feature bits that are scattered in the kernel's cpufeatures word
 * पूर्णांकo KVM feature words that align with hardware's definitions.
 */
अटल __always_अंतरभूत u32 __feature_translate(पूर्णांक x86_feature)
अणु
	अगर (x86_feature == X86_FEATURE_SGX1)
		वापस KVM_X86_FEATURE_SGX1;
	अन्यथा अगर (x86_feature == X86_FEATURE_SGX2)
		वापस KVM_X86_FEATURE_SGX2;

	वापस x86_feature;
पूर्ण

अटल __always_अंतरभूत u32 __feature_leaf(पूर्णांक x86_feature)
अणु
	वापस __feature_translate(x86_feature) / 32;
पूर्ण

/*
 * Retrieve the bit mask from an X86_FEATURE_* definition.  Features contain
 * the hardware defined bit number (stored in bits 4:0) and a software defined
 * "word" (stored in bits 31:5).  The word is used to index पूर्णांकo arrays of
 * bit masks that hold the per-cpu feature capabilities, e.g. this_cpu_has().
 */
अटल __always_अंतरभूत u32 __feature_bit(पूर्णांक x86_feature)
अणु
	x86_feature = __feature_translate(x86_feature);

	reverse_cpuid_check(x86_feature / 32);
	वापस 1 << (x86_feature & 31);
पूर्ण

#घोषणा feature_bit(name)  __feature_bit(X86_FEATURE_##name)

अटल __always_अंतरभूत काष्ठा cpuid_reg x86_feature_cpuid(अचिन्हित पूर्णांक x86_feature)
अणु
	अचिन्हित पूर्णांक x86_leaf = __feature_leaf(x86_feature);

	reverse_cpuid_check(x86_leaf);
	वापस reverse_cpuid[x86_leaf];
पूर्ण

अटल __always_अंतरभूत u32 *__cpuid_entry_get_reg(काष्ठा kvm_cpuid_entry2 *entry,
						  u32 reg)
अणु
	चयन (reg) अणु
	हाल CPUID_EAX:
		वापस &entry->eax;
	हाल CPUID_EBX:
		वापस &entry->ebx;
	हाल CPUID_ECX:
		वापस &entry->ecx;
	हाल CPUID_EDX:
		वापस &entry->edx;
	शेष:
		BUILD_BUG();
		वापस शून्य;
	पूर्ण
पूर्ण

अटल __always_अंतरभूत u32 *cpuid_entry_get_reg(काष्ठा kvm_cpuid_entry2 *entry,
						अचिन्हित पूर्णांक x86_feature)
अणु
	स्थिर काष्ठा cpuid_reg cpuid = x86_feature_cpuid(x86_feature);

	वापस __cpuid_entry_get_reg(entry, cpuid.reg);
पूर्ण

अटल __always_अंतरभूत u32 cpuid_entry_get(काष्ठा kvm_cpuid_entry2 *entry,
					   अचिन्हित पूर्णांक x86_feature)
अणु
	u32 *reg = cpuid_entry_get_reg(entry, x86_feature);

	वापस *reg & __feature_bit(x86_feature);
पूर्ण

अटल __always_अंतरभूत bool cpuid_entry_has(काष्ठा kvm_cpuid_entry2 *entry,
					    अचिन्हित पूर्णांक x86_feature)
अणु
	वापस cpuid_entry_get(entry, x86_feature);
पूर्ण

अटल __always_अंतरभूत व्योम cpuid_entry_clear(काष्ठा kvm_cpuid_entry2 *entry,
					      अचिन्हित पूर्णांक x86_feature)
अणु
	u32 *reg = cpuid_entry_get_reg(entry, x86_feature);

	*reg &= ~__feature_bit(x86_feature);
पूर्ण

अटल __always_अंतरभूत व्योम cpuid_entry_set(काष्ठा kvm_cpuid_entry2 *entry,
					    अचिन्हित पूर्णांक x86_feature)
अणु
	u32 *reg = cpuid_entry_get_reg(entry, x86_feature);

	*reg |= __feature_bit(x86_feature);
पूर्ण

अटल __always_अंतरभूत व्योम cpuid_entry_change(काष्ठा kvm_cpuid_entry2 *entry,
					       अचिन्हित पूर्णांक x86_feature,
					       bool set)
अणु
	u32 *reg = cpuid_entry_get_reg(entry, x86_feature);

	/*
	 * Open coded instead of using cpuid_entry_अणुclear,setपूर्ण() to coerce the
	 * compiler पूर्णांकo using CMOV instead of Jcc when possible.
	 */
	अगर (set)
		*reg |= __feature_bit(x86_feature);
	अन्यथा
		*reg &= ~__feature_bit(x86_feature);
पूर्ण

#पूर्ण_अगर /* ARCH_X86_KVM_REVERSE_CPUID_H */
