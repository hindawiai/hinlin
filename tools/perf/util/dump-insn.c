<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/compiler.h>
#समावेश "dump-insn.h"

/* Fallback code */

__weak
स्थिर अक्षर *dump_insn(काष्ठा perf_insn *x __maybe_unused,
		      u64 ip __maybe_unused, u8 *inbuf __maybe_unused,
		      पूर्णांक inlen __maybe_unused, पूर्णांक *lenp)
अणु
	अगर (lenp)
		*lenp = 0;
	वापस "?";
पूर्ण

__weak
पूर्णांक arch_is_branch(स्थिर अचिन्हित अक्षर *buf __maybe_unused,
		   माप_प्रकार len __maybe_unused,
		   पूर्णांक x86_64 __maybe_unused)
अणु
	वापस 0;
पूर्ण
