<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Naive प्रणाली call dropper built on seccomp_filter.
 *
 * Copyright (c) 2012 The Chromium OS Authors <chromium-os-dev@chromium.org>
 * Author: Will Drewry <wad@chromium.org>
 *
 * The code may be used by anyone क्रम any purpose,
 * and can serve as a starting poपूर्णांक क्रम developing
 * applications using prctl(PR_SET_SECCOMP, 2, ...).
 *
 * When run, वापसs the specअगरied त्रुटि_सं क्रम the specअगरied
 * प्रणाली call number against the given architecture.
 *
 */

#समावेश <त्रुटिसं.स>
#समावेश <linux/audit.h>
#समावेश <linux/filter.h>
#समावेश <linux/seccomp.h>
#समावेश <linux/unistd.h>
#समावेश <मानकपन.स>
#समावेश <मानकघोष.स>
#समावेश <मानककोष.स>
#समावेश <sys/prctl.h>
#समावेश <unistd.h>

अटल पूर्णांक install_filter(पूर्णांक nr, पूर्णांक arch, पूर्णांक error)
अणु
	काष्ठा sock_filter filter[] = अणु
		BPF_STMT(BPF_LD+BPF_W+BPF_ABS,
			 (दुरत्व(काष्ठा seccomp_data, arch))),
		BPF_JUMP(BPF_JMP+BPF_JEQ+BPF_K, arch, 0, 3),
		BPF_STMT(BPF_LD+BPF_W+BPF_ABS,
			 (दुरत्व(काष्ठा seccomp_data, nr))),
		BPF_JUMP(BPF_JMP+BPF_JEQ+BPF_K, nr, 0, 1),
		BPF_STMT(BPF_RET+BPF_K,
			 SECCOMP_RET_ERRNO|(error & SECCOMP_RET_DATA)),
		BPF_STMT(BPF_RET+BPF_K, SECCOMP_RET_ALLOW),
	पूर्ण;
	काष्ठा sock_fprog prog = अणु
		.len = (अचिन्हित लघु)(माप(filter)/माप(filter[0])),
		.filter = filter,
	पूर्ण;
	अगर (prctl(PR_SET_NO_NEW_PRIVS, 1, 0, 0, 0)) अणु
		लिखो_त्रुटि("prctl(NO_NEW_PRIVS)");
		वापस 1;
	पूर्ण
	अगर (prctl(PR_SET_SECCOMP, 2, &prog)) अणु
		लिखो_त्रुटि("prctl(PR_SET_SECCOMP)");
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	अगर (argc < 5) अणु
		ख_लिखो(मानक_त्रुटि, "Usage:\n"
			"dropper <syscall_nr> <arch> <errno> <prog> [<args>]\n"
			"Hint:	AUDIT_ARCH_I386: 0x%X\n"
			"	AUDIT_ARCH_X86_64: 0x%X\n"
			"\n", AUDIT_ARCH_I386, AUDIT_ARCH_X86_64);
		वापस 1;
	पूर्ण
	अगर (install_filter(म_से_दीर्घ(argv[1], शून्य, 0), म_से_दीर्घ(argv[2], शून्य, 0),
			   म_से_दीर्घ(argv[3], शून्य, 0)))
		वापस 1;
	execv(argv[4], &argv[4]);
	म_लिखो("Failed to execv\n");
	वापस 255;
पूर्ण
