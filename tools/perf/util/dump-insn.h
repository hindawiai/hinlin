<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __PERF_DUMP_INSN_H
#घोषणा __PERF_DUMP_INSN_H 1

#घोषणा MAXINSN 15

#समावेश <linux/types.h>

काष्ठा thपढ़ो;

काष्ठा perf_insn अणु
	/* Initialized by callers: */
	काष्ठा thपढ़ो *thपढ़ो;
	u8	      cpumode;
	bool	      is64bit;
	पूर्णांक	      cpu;
	/* Temporary */
	अक्षर	      out[256];
पूर्ण;

स्थिर अक्षर *dump_insn(काष्ठा perf_insn *x, u64 ip,
		      u8 *inbuf, पूर्णांक inlen, पूर्णांक *lenp);
पूर्णांक arch_is_branch(स्थिर अचिन्हित अक्षर *buf, माप_प्रकार len, पूर्णांक x86_64);

#पूर्ण_अगर
