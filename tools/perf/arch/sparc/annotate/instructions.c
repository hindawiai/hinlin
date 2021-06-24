<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

अटल पूर्णांक is_branch_cond(स्थिर अक्षर *cond)
अणु
	अगर (cond[0] == '\0')
		वापस 1;

	अगर (cond[0] == 'a' && cond[1] == '\0')
		वापस 1;

	अगर (cond[0] == 'c' &&
	    (cond[1] == 'c' || cond[1] == 's') &&
	    cond[2] == '\0')
		वापस 1;

	अगर (cond[0] == 'e' &&
	    (cond[1] == '\0' ||
	     (cond[1] == 'q' && cond[2] == '\0')))
		वापस 1;

	अगर (cond[0] == 'g' &&
	    (cond[1] == '\0' ||
	     (cond[1] == 't' && cond[2] == '\0') ||
	     (cond[1] == 'e' && cond[2] == '\0') ||
	     (cond[1] == 'e' && cond[2] == 'u' && cond[3] == '\0')))
		वापस 1;

	अगर (cond[0] == 'l' &&
	    (cond[1] == '\0' ||
	     (cond[1] == 't' && cond[2] == '\0') ||
	     (cond[1] == 'u' && cond[2] == '\0') ||
	     (cond[1] == 'e' && cond[2] == '\0') ||
	     (cond[1] == 'e' && cond[2] == 'u' && cond[3] == '\0')))
		वापस 1;

	अगर (cond[0] == 'n' &&
	    (cond[1] == '\0' ||
	     (cond[1] == 'e' && cond[2] == '\0') ||
	     (cond[1] == 'z' && cond[2] == '\0') ||
	     (cond[1] == 'e' && cond[2] == 'g' && cond[3] == '\0')))
		वापस 1;

	अगर (cond[0] == 'b' &&
	    cond[1] == 'p' &&
	    cond[2] == 'o' &&
	    cond[3] == 's' &&
	    cond[4] == '\0')
		वापस 1;

	अगर (cond[0] == 'v' &&
	    (cond[1] == 'c' || cond[1] == 's') &&
	    cond[2] == '\0')
		वापस 1;

	अगर (cond[0] == 'b' &&
	    cond[1] == 'z' &&
	    cond[2] == '\0')
		वापस 1;

	वापस 0;
पूर्ण

अटल पूर्णांक is_branch_reg_cond(स्थिर अक्षर *cond)
अणु
	अगर ((cond[0] == 'n' || cond[0] == 'l') &&
	    cond[1] == 'z' &&
	    cond[2] == '\0')
		वापस 1;

	अगर (cond[0] == 'z' &&
	    cond[1] == '\0')
		वापस 1;

	अगर ((cond[0] == 'g' || cond[0] == 'l') &&
	    cond[1] == 'e' &&
	    cond[2] == 'z' &&
	    cond[3] == '\0')
		वापस 1;

	अगर (cond[0] == 'g' &&
	    cond[1] == 'z' &&
	    cond[2] == '\0')
		वापस 1;

	वापस 0;
पूर्ण

अटल पूर्णांक is_branch_भग्न_cond(स्थिर अक्षर *cond)
अणु
	अगर (cond[0] == '\0')
		वापस 1;

	अगर ((cond[0] == 'a' || cond[0] == 'e' ||
	     cond[0] == 'z' || cond[0] == 'g' ||
	     cond[0] == 'l' || cond[0] == 'n' ||
	     cond[0] == 'o' || cond[0] == 'u') &&
	    cond[1] == '\0')
		वापस 1;

	अगर (((cond[0] == 'g' && cond[1] == 'e') ||
	     (cond[0] == 'l' && (cond[1] == 'e' ||
				 cond[1] == 'g')) ||
	     (cond[0] == 'n' && (cond[1] == 'e' ||
				 cond[1] == 'z')) ||
	     (cond[0] == 'u' && (cond[1] == 'e' ||
				 cond[1] == 'g' ||
				 cond[1] == 'l'))) &&
	    cond[2] == '\0')
		वापस 1;

	अगर (cond[0] == 'u' &&
	    (cond[1] == 'g' || cond[1] == 'l') &&
	    cond[2] == 'e' &&
	    cond[3] == '\0')
		वापस 1;

	वापस 0;
पूर्ण

अटल काष्ठा ins_ops *sparc__associate_inकाष्ठाion_ops(काष्ठा arch *arch, स्थिर अक्षर *name)
अणु
	काष्ठा ins_ops *ops = शून्य;

	अगर (!म_भेद(name, "call") ||
	    !म_भेद(name, "jmp") ||
	    !म_भेद(name, "jmpl")) अणु
		ops = &call_ops;
	पूर्ण अन्यथा अगर (!म_भेद(name, "ret") ||
		   !म_भेद(name, "retl") ||
		   !म_भेद(name, "return")) अणु
		ops = &ret_ops;
	पूर्ण अन्यथा अगर (!म_भेद(name, "mov")) अणु
		ops = &mov_ops;
	पूर्ण अन्यथा अणु
		अगर (name[0] == 'c' &&
		    (name[1] == 'w' || name[1] == 'x'))
			name += 2;

		अगर (name[0] == 'b') अणु
			स्थिर अक्षर *cond = name + 1;

			अगर (cond[0] == 'r') अणु
				अगर (is_branch_reg_cond(cond + 1))
					ops = &jump_ops;
			पूर्ण अन्यथा अगर (is_branch_cond(cond)) अणु
				ops = &jump_ops;
			पूर्ण
		पूर्ण अन्यथा अगर (name[0] == 'f' && name[1] == 'b') अणु
			अगर (is_branch_भग्न_cond(name + 2))
				ops = &jump_ops;
		पूर्ण
	पूर्ण

	अगर (ops)
		arch__associate_ins_ops(arch, name, ops);

	वापस ops;
पूर्ण

अटल पूर्णांक sparc__annotate_init(काष्ठा arch *arch, अक्षर *cpuid __maybe_unused)
अणु
	अगर (!arch->initialized) अणु
		arch->initialized = true;
		arch->associate_inकाष्ठाion_ops = sparc__associate_inकाष्ठाion_ops;
		arch->objdump.comment_अक्षर = '#';
	पूर्ण

	वापस 0;
पूर्ण
