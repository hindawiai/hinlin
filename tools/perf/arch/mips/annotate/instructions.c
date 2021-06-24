<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

अटल
काष्ठा ins_ops *mips__associate_ins_ops(काष्ठा arch *arch, स्थिर अक्षर *name)
अणु
	काष्ठा ins_ops *ops = शून्य;

	अगर (!म_भेदन(name, "bal", 3) ||
	    !म_भेदन(name, "bgezal", 6) ||
	    !म_भेदन(name, "bltzal", 6) ||
	    !म_भेदन(name, "bgtzal", 6) ||
	    !म_भेदन(name, "blezal", 6) ||
	    !म_भेदन(name, "beqzal", 6) ||
	    !म_भेदन(name, "bnezal", 6) ||
	    !म_भेदन(name, "bgtzl", 5) ||
	    !म_भेदन(name, "bltzl", 5) ||
	    !म_भेदन(name, "bgezl", 5) ||
	    !म_भेदन(name, "blezl", 5) ||
	    !म_भेदन(name, "jialc", 5) ||
	    !म_भेदन(name, "beql", 4) ||
	    !म_भेदन(name, "bnel", 4) ||
	    !म_भेदन(name, "jal", 3))
		ops = &call_ops;
	अन्यथा अगर (!म_भेदन(name, "jr", 2))
		ops = &ret_ops;
	अन्यथा अगर (name[0] == 'j' || name[0] == 'b')
		ops = &jump_ops;
	अन्यथा
		वापस शून्य;

	arch__associate_ins_ops(arch, name, ops);

	वापस ops;
पूर्ण

अटल
पूर्णांक mips__annotate_init(काष्ठा arch *arch, अक्षर *cpuid __maybe_unused)
अणु
	अगर (!arch->initialized) अणु
		arch->associate_inकाष्ठाion_ops = mips__associate_ins_ops;
		arch->initialized = true;
		arch->objdump.comment_अक्षर = '#';
	पूर्ण

	वापस 0;
पूर्ण
