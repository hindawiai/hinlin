<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Seccomp BPF example using a macro-based generator.
 *
 * Copyright (c) 2012 The Chromium OS Authors <chromium-os-dev@chromium.org>
 * Author: Will Drewry <wad@chromium.org>
 *
 * The code may be used by anyone क्रम any purpose,
 * and can serve as a starting poपूर्णांक क्रम developing
 * applications using prctl(PR_ATTACH_SECCOMP_FILTER).
 */

#समावेश <linux/filter.h>
#समावेश <linux/seccomp.h>
#समावेश <linux/unistd.h>
#समावेश <मानकपन.स>
#समावेश <माला.स>
#समावेश <sys/prctl.h>
#समावेश <unistd.h>

#समावेश "bpf-helper.h"

#अगर_अघोषित PR_SET_NO_NEW_PRIVS
#घोषणा PR_SET_NO_NEW_PRIVS 38
#पूर्ण_अगर

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	काष्ठा bpf_labels l = अणु
		.count = 0,
	पूर्ण;
	अटल स्थिर अक्षर msg1[] = "Please type something: ";
	अटल स्थिर अक्षर msg2[] = "You typed: ";
	अक्षर buf[256];
	काष्ठा sock_filter filter[] = अणु
		/* TODO: LOAD_SYSCALL_NR(arch) and enक्रमce an arch */
		LOAD_SYSCALL_NR,
		SYSCALL(__NR_निकास, ALLOW),
		SYSCALL(__NR_निकास_group, ALLOW),
		SYSCALL(__NR_ग_लिखो, JUMP(&l, ग_लिखो_fd)),
		SYSCALL(__NR_पढ़ो, JUMP(&l, पढ़ो)),
		DENY,  /* Don't passthrough पूर्णांकo a label */

		LABEL(&l, पढ़ो),
		ARG(0),
		JNE(STDIN_खाताNO, DENY),
		ARG(1),
		JNE((अचिन्हित दीर्घ)buf, DENY),
		ARG(2),
		JGE(माप(buf), DENY),
		ALLOW,

		LABEL(&l, ग_लिखो_fd),
		ARG(0),
		JEQ(STDOUT_खाताNO, JUMP(&l, ग_लिखो_buf)),
		JEQ(STDERR_खाताNO, JUMP(&l, ग_लिखो_buf)),
		DENY,

		LABEL(&l, ग_लिखो_buf),
		ARG(1),
		JEQ((अचिन्हित दीर्घ)msg1, JUMP(&l, msg1_len)),
		JEQ((अचिन्हित दीर्घ)msg2, JUMP(&l, msg2_len)),
		JEQ((अचिन्हित दीर्घ)buf, JUMP(&l, buf_len)),
		DENY,

		LABEL(&l, msg1_len),
		ARG(2),
		JLT(माप(msg1), ALLOW),
		DENY,

		LABEL(&l, msg2_len),
		ARG(2),
		JLT(माप(msg2), ALLOW),
		DENY,

		LABEL(&l, buf_len),
		ARG(2),
		JLT(माप(buf), ALLOW),
		DENY,
	पूर्ण;
	काष्ठा sock_fprog prog = अणु
		.filter = filter,
		.len = (अचिन्हित लघु)(माप(filter)/माप(filter[0])),
	पूर्ण;
	sमाप_प्रकार bytes;
	bpf_resolve_jumps(&l, filter, माप(filter)/माप(*filter));

	अगर (prctl(PR_SET_NO_NEW_PRIVS, 1, 0, 0, 0)) अणु
		लिखो_त्रुटि("prctl(NO_NEW_PRIVS)");
		वापस 1;
	पूर्ण

	अगर (prctl(PR_SET_SECCOMP, SECCOMP_MODE_FILTER, &prog)) अणु
		लिखो_त्रुटि("prctl(SECCOMP)");
		वापस 1;
	पूर्ण
	syscall(__NR_ग_लिखो, STDOUT_खाताNO, msg1, म_माप(msg1));
	bytes = syscall(__NR_पढ़ो, STDIN_खाताNO, buf, माप(buf)-1);
	bytes = (bytes > 0 ? bytes : 0);
	syscall(__NR_ग_लिखो, STDERR_खाताNO, msg2, म_माप(msg2));
	syscall(__NR_ग_लिखो, STDERR_खाताNO, buf, bytes);
	/* Now get समाप्तed */
	syscall(__NR_ग_लिखो, STDERR_खाताNO, msg2, म_माप(msg2)+2);
	वापस 0;
पूर्ण
