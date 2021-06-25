<शैली गुरु>
// SPDX-License-Identअगरier: LGPL-2.1
/*
 * trace/beauty/x86_msr.c
 *
 *  Copyright (C) 2019, Red Hat Inc, Arnalकरो Carvalho de Melo <acme@redhat.com>
 */

#समावेश "trace/beauty/beauty.h"

#समावेश "trace/beauty/generated/x86_arch_MSRs_array.c"

अटल DEFINE_STRARRAY(x86_MSRs, "MSR_");
अटल DEFINE_STRARRAY_OFFSET(x86_64_specअगरic_MSRs, "MSR_", x86_64_specअगरic_MSRs_offset);
अटल DEFINE_STRARRAY_OFFSET(x86_AMD_V_KVM_MSRs, "MSR_", x86_AMD_V_KVM_MSRs_offset);

अटल काष्ठा strarray *x86_MSRs_tables[] = अणु
	&strarray__x86_MSRs,
	&strarray__x86_64_specअगरic_MSRs,
	&strarray__x86_AMD_V_KVM_MSRs,
पूर्ण;

अटल DEFINE_STRARRAYS(x86_MSRs_tables);

अटल माप_प्रकार x86_MSR__scnम_लिखो(अचिन्हित दीर्घ msr, अक्षर *bf, माप_प्रकार size, bool show_prefix)
अणु
	वापस strarrays__scnम_लिखो(&strarrays__x86_MSRs_tables, bf, size, "%#x", show_prefix, msr);
पूर्ण

माप_प्रकार syscall_arg__scnम_लिखो_x86_MSR(अक्षर *bf, माप_प्रकार size, काष्ठा syscall_arg *arg)
अणु
	अचिन्हित दीर्घ flags = arg->val;

	वापस x86_MSR__scnम_लिखो(flags, bf, size, arg->show_string_prefix);
पूर्ण

bool syscall_arg__म_से_अदीर्घ_x86_MSR(अक्षर *bf, माप_प्रकार size, काष्ठा syscall_arg *arg __maybe_unused, u64 *ret)
अणु
	वापस strarrays__म_से_अदीर्घ(&strarrays__x86_MSRs_tables, bf, size, ret);
पूर्ण
