<शैली गुरु>
// SPDX-License-Identअगरier: LGPL-2.1
/*
 * trace/beauty/x86_irq_vectors.c
 *
 *  Copyright (C) 2019, Red Hat Inc, Arnalकरो Carvalho de Melo <acme@redhat.com>
 */

#समावेश "trace/beauty/beauty.h"

#समावेश "trace/beauty/generated/x86_arch_irq_vectors_array.c"

अटल DEFINE_STRARRAY(x86_irq_vectors, "_VECTOR");

अटल माप_प्रकार x86_irq_vectors__scnम_लिखो(अचिन्हित दीर्घ vector, अक्षर *bf, माप_प्रकार size, bool show_prefix)
अणु
	वापस strarray__scnम_लिखो_suffix(&strarray__x86_irq_vectors, bf, size, "%#x", show_prefix, vector);
पूर्ण

माप_प्रकार syscall_arg__scnम_लिखो_x86_irq_vectors(अक्षर *bf, माप_प्रकार size, काष्ठा syscall_arg *arg)
अणु
	अचिन्हित दीर्घ vector = arg->val;

	वापस x86_irq_vectors__scnम_लिखो(vector, bf, size, arg->show_string_prefix);
पूर्ण

bool syscall_arg__म_से_अदीर्घ_x86_irq_vectors(अक्षर *bf, माप_प्रकार size, काष्ठा syscall_arg *arg __maybe_unused, u64 *ret)
अणु
	वापस strarray__म_से_अदीर्घ(&strarray__x86_irq_vectors, bf, size, ret);
पूर्ण
