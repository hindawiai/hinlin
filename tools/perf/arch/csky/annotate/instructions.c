<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) 2019 Hangzhou C-SKY Microप्रणालीs co.,ltd.

#समावेश <linux/compiler.h>

अटल काष्ठा ins_ops *csky__associate_ins_ops(काष्ठा arch *arch,
					       स्थिर अक्षर *name)
अणु
	काष्ठा ins_ops *ops = शून्य;

	/* catch all kind of jumps */
	अगर (!म_भेद(name, "bt") ||
	    !म_भेद(name, "bf") ||
	    !म_भेद(name, "bez") ||
	    !म_भेद(name, "bnez") ||
	    !म_भेद(name, "bnezad") ||
	    !म_भेद(name, "bhsz") ||
	    !म_भेद(name, "bhz") ||
	    !म_भेद(name, "blsz") ||
	    !म_भेद(name, "blz") ||
	    !म_भेद(name, "br") ||
	    !म_भेद(name, "jmpi") ||
	    !म_भेद(name, "jmp"))
		ops = &jump_ops;

	/* catch function call */
	अगर (!म_भेद(name, "bsr") ||
	    !म_भेद(name, "jsri") ||
	    !म_भेद(name, "jsr"))
		ops = &call_ops;

	/* catch function वापस */
	अगर (!म_भेद(name, "rts"))
		ops = &ret_ops;

	अगर (ops)
		arch__associate_ins_ops(arch, name, ops);
	वापस ops;
पूर्ण

अटल पूर्णांक csky__annotate_init(काष्ठा arch *arch, अक्षर *cpuid __maybe_unused)
अणु
	arch->initialized = true;
	arch->objdump.comment_अक्षर = '/';
	arch->associate_inकाष्ठाion_ops = csky__associate_ins_ops;

	वापस 0;
पूर्ण
