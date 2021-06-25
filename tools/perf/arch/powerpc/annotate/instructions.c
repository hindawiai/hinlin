<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/compiler.h>

अटल काष्ठा ins_ops *घातerpc__associate_inकाष्ठाion_ops(काष्ठा arch *arch, स्थिर अक्षर *name)
अणु
	पूर्णांक i;
	काष्ठा ins_ops *ops;

	/*
	 * - Interested only अगर inकाष्ठाion starts with 'b'.
	 * - Few start with 'b', but aren't branch inकाष्ठाions.
	 */
	अगर (name[0] != 'b'             ||
	    !म_भेदन(name, "bcd", 3)   ||
	    !म_भेदन(name, "brinc", 5) ||
	    !म_भेदन(name, "bper", 4))
		वापस शून्य;

	ops = &jump_ops;

	i = म_माप(name) - 1;
	अगर (i < 0)
		वापस शून्य;

	/* ignore optional hपूर्णांकs at the end of the inकाष्ठाions */
	अगर (name[i] == '+' || name[i] == '-')
		i--;

	अगर (name[i] == 'l' || (name[i] == 'a' && name[i-1] == 'l')) अणु
		/*
		 * अगर the inकाष्ठाion ends up with 'l' or 'la', then
		 * those are considered 'calls' since they update LR.
		 * ... except क्रम 'bnl' which is branch अगर not less than
		 * and the असलolute क्रमm of the same.
		 */
		अगर (म_भेद(name, "bnl") && म_भेद(name, "bnl+") &&
		    म_भेद(name, "bnl-") && म_भेद(name, "bnla") &&
		    म_भेद(name, "bnla+") && म_भेद(name, "bnla-"))
			ops = &call_ops;
	पूर्ण
	अगर (name[i] == 'r' && name[i-1] == 'l')
		/*
		 * inकाष्ठाions ending with 'lr' are considered to be
		 * वापस inकाष्ठाions
		 */
		ops = &ret_ops;

	arch__associate_ins_ops(arch, name, ops);
	वापस ops;
पूर्ण

अटल पूर्णांक घातerpc__annotate_init(काष्ठा arch *arch, अक्षर *cpuid __maybe_unused)
अणु
	अगर (!arch->initialized) अणु
		arch->initialized = true;
		arch->associate_inकाष्ठाion_ops = घातerpc__associate_inकाष्ठाion_ops;
		arch->objdump.comment_अक्षर      = '#';
	पूर्ण

	वापस 0;
पूर्ण
