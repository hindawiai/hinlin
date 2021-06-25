<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) 2018 Hangzhou C-SKY Microप्रणालीs co.,ltd.

#समावेश <linux/of.h>
#समावेश <linux/init.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/memblock.h>

#समावेश <abi/reg_ops.h>

अटल व्योम percpu_prपूर्णांक(व्योम *arg)
अणु
	काष्ठा seq_file *m = (काष्ठा seq_file *)arg;
	अचिन्हित पूर्णांक cur, next, i;

	seq_म_लिखो(m, "processor       : %d\n", smp_processor_id());
	seq_म_लिखो(m, "C-SKY CPU model : %s\n", CSKYCPU_DEF_NAME);

	/* पढ़ो processor id, max is 100 */
	cur  = mfcr("cr13");
	क्रम (i = 0; i < 100; i++) अणु
		seq_म_लिखो(m, "product info[%d] : 0x%08x\n", i, cur);

		next = mfcr("cr13");

		/* some CPU only has one id reg */
		अगर (cur == next)
			अवरोध;

		cur = next;

		/* cpid index is 31-28, reset */
		अगर (!(next >> 28)) अणु
			जबतक ((mfcr("cr13") >> 28) != i);
			अवरोध;
		पूर्ण
	पूर्ण

	/* CPU feature regs, setup by bootloader or gdbinit */
	seq_म_लिखो(m, "hint (CPU funcs): 0x%08x\n", mfcr_hपूर्णांक());
	seq_म_लिखो(m, "ccr  (L1C & MMU): 0x%08x\n", mfcr("cr18"));
	seq_म_लिखो(m, "ccr2 (L2C)      : 0x%08x\n", mfcr_ccr2());
	seq_म_लिखो(m, "\n");
पूर्ण

अटल पूर्णांक c_show(काष्ठा seq_file *m, व्योम *v)
अणु
	पूर्णांक cpu;

	क्रम_each_online_cpu(cpu)
		smp_call_function_single(cpu, percpu_prपूर्णांक, m, true);

#अगर_घोषित CSKY_ARCH_VERSION
	seq_म_लिखो(m, "arch-version : %s\n", CSKY_ARCH_VERSION);
	seq_म_लिखो(m, "\n");
#पूर्ण_अगर

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

अटल व्योम c_stop(काष्ठा seq_file *m, व्योम *v) अणुपूर्ण

स्थिर काष्ठा seq_operations cpuinfo_op = अणु
	.start	= c_start,
	.next	= c_next,
	.stop	= c_stop,
	.show	= c_show,
पूर्ण;
