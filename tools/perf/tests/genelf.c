<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <सीमा.स>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <unistd.h>
#समावेश <linux/compiler.h>

#समावेश "debug.h"
#समावेश "tests.h"

#अगर_घोषित HAVE_JITDUMP
#समावेश <libelf.h>
#समावेश "../util/genelf.h"
#पूर्ण_अगर

#घोषणा TEMPL "/tmp/perf-test-XXXXXX"

पूर्णांक test__jit_ग_लिखो_elf(काष्ठा test *test __maybe_unused,
			पूर्णांक subtest __maybe_unused)
अणु
#अगर_घोषित HAVE_JITDUMP
	अटल अचिन्हित अक्षर x86_code[] = अणु
		0xBB, 0x2A, 0x00, 0x00, 0x00, /* movl $42, %ebx */
		0xB8, 0x01, 0x00, 0x00, 0x00, /* movl $1, %eax */
		0xCD, 0x80            /* पूर्णांक $0x80 */
	पूर्ण;
	अक्षर path[PATH_MAX];
	पूर्णांक fd, ret;

	म_नकल(path, TEMPL);

	fd = mkstemp(path);
	अगर (fd < 0) अणु
		लिखो_त्रुटि("mkstemp failed");
		वापस TEST_FAIL;
	पूर्ण

	pr_info("Writing jit code to: %s\n", path);

	ret = jit_ग_लिखो_elf(fd, 0, "main", x86_code, माप(x86_code),
			शून्य, 0, शून्य, 0, 0);
	बंद(fd);

	unlink(path);

	वापस ret ? TEST_FAIL : 0;
#अन्यथा
	वापस TEST_SKIP;
#पूर्ण_अगर
पूर्ण
