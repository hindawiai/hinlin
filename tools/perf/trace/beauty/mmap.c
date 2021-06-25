<शैली गुरु>
// SPDX-License-Identअगरier: LGPL-2.1
#समावेश <linux/log2.h>

#समावेश "trace/beauty/generated/mmap_prot_array.c"
अटल DEFINE_STRARRAY(mmap_prot, "PROT_");

अटल माप_प्रकार mmap__scnम_लिखो_prot(अचिन्हित दीर्घ prot, अक्षर *bf, माप_प्रकार size, bool show_prefix)
अणु
       वापस strarray__scnम_लिखो_flags(&strarray__mmap_prot, bf, size, show_prefix, prot);
पूर्ण

अटल माप_प्रकार syscall_arg__scnम_लिखो_mmap_prot(अक्षर *bf, माप_प्रकार size, काष्ठा syscall_arg *arg)
अणु
	अचिन्हित दीर्घ prot = arg->val;

	अगर (prot == 0)
		वापस scnम_लिखो(bf, size, "%sNONE", arg->show_string_prefix ? strarray__mmap_prot.prefix : "");

	वापस mmap__scnम_लिखो_prot(prot, bf, size, arg->show_string_prefix);
पूर्ण

#घोषणा SCA_MMAP_PROT syscall_arg__scnम_लिखो_mmap_prot

#समावेश "trace/beauty/generated/mmap_flags_array.c"
अटल DEFINE_STRARRAY(mmap_flags, "MAP_");

अटल माप_प्रकार mmap__scnम_लिखो_flags(अचिन्हित दीर्घ flags, अक्षर *bf, माप_प्रकार size, bool show_prefix)
अणु
       वापस strarray__scnम_लिखो_flags(&strarray__mmap_flags, bf, size, show_prefix, flags);
पूर्ण

अटल माप_प्रकार syscall_arg__scnम_लिखो_mmap_flags(अक्षर *bf, माप_प्रकार size,
						काष्ठा syscall_arg *arg)
अणु
	अचिन्हित दीर्घ flags = arg->val;

	अगर (flags & MAP_ANONYMOUS)
		arg->mask |= (1 << 4) | (1 << 5); /* Mask 4th ('fd') and 5th ('offset') args, ignored */

	वापस mmap__scnम_लिखो_flags(flags, bf, size, arg->show_string_prefix);
पूर्ण

#घोषणा SCA_MMAP_FLAGS syscall_arg__scnम_लिखो_mmap_flags

#समावेश "trace/beauty/generated/mremap_flags_array.c"
अटल DEFINE_STRARRAY(mremap_flags, "MREMAP_");

अटल माप_प्रकार mremap__scnम_लिखो_flags(अचिन्हित दीर्घ flags, अक्षर *bf, माप_प्रकार size, bool show_prefix)
अणु
       वापस strarray__scnम_लिखो_flags(&strarray__mremap_flags, bf, size, show_prefix, flags);
पूर्ण

अटल माप_प्रकार syscall_arg__scnम_लिखो_mremap_flags(अक्षर *bf, माप_प्रकार size, काष्ठा syscall_arg *arg)
अणु
	अचिन्हित दीर्घ flags = arg->val;

	अगर (!(flags & MREMAP_FIXED))
		arg->mask |=  (1 << 5); /* Mask 5th ('new_address') args, ignored */

	वापस mremap__scnम_लिखो_flags(flags, bf, size, arg->show_string_prefix);
पूर्ण

#घोषणा SCA_MREMAP_FLAGS syscall_arg__scnम_लिखो_mremap_flags

अटल माप_प्रकार madvise__scnम_लिखो_behavior(पूर्णांक behavior, अक्षर *bf, माप_प्रकार size)
अणु
#समावेश "trace/beauty/generated/madvise_behavior_array.c"
       अटल DEFINE_STRARRAY(madvise_advices, "MADV_");

       अगर (behavior < strarray__madvise_advices.nr_entries && strarray__madvise_advices.entries[behavior] != शून्य)
               वापस scnम_लिखो(bf, size, "MADV_%s", strarray__madvise_advices.entries[behavior]);

       वापस scnम_लिखो(bf, size, "%#", behavior);
पूर्ण

अटल माप_प्रकार syscall_arg__scnम_लिखो_madvise_behavior(अक्षर *bf, माप_प्रकार size,
						      काष्ठा syscall_arg *arg)
अणु
	वापस madvise__scnम_लिखो_behavior(arg->val, bf, size);
पूर्ण

#घोषणा SCA_MADV_BHV syscall_arg__scnम_लिखो_madvise_behavior
