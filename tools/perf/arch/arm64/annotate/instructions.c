<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/compiler.h>
#समावेश <sys/types.h>
#समावेश <regex.h>
#समावेश <मानककोष.स>

काष्ठा arm64_annotate अणु
	regex_t call_insn,
		jump_insn;
पूर्ण;

अटल पूर्णांक arm64_mov__parse(काष्ठा arch *arch __maybe_unused,
			    काष्ठा ins_opeअक्रमs *ops,
			    काष्ठा map_symbol *ms __maybe_unused)
अणु
	अक्षर *s = म_अक्षर(ops->raw, ','), *target, *endptr;

	अगर (s == शून्य)
		वापस -1;

	*s = '\0';
	ops->source.raw = strdup(ops->raw);
	*s = ',';

	अगर (ops->source.raw == शून्य)
		वापस -1;

	target = ++s;
	ops->target.raw = strdup(target);
	अगर (ops->target.raw == शून्य)
		जाओ out_मुक्त_source;

	ops->target.addr = म_से_अदीर्घl(target, &endptr, 16);
	अगर (endptr == target)
		जाओ out_मुक्त_target;

	s = म_अक्षर(endptr, '<');
	अगर (s == शून्य)
		जाओ out_मुक्त_target;
	endptr = म_अक्षर(s + 1, '>');
	अगर (endptr == शून्य)
		जाओ out_मुक्त_target;

	*endptr = '\0';
	*s = ' ';
	ops->target.name = strdup(s);
	*s = '<';
	*endptr = '>';
	अगर (ops->target.name == शून्य)
		जाओ out_मुक्त_target;

	वापस 0;

out_मुक्त_target:
	zमुक्त(&ops->target.raw);
out_मुक्त_source:
	zमुक्त(&ops->source.raw);
	वापस -1;
पूर्ण

अटल पूर्णांक mov__scnम_लिखो(काष्ठा ins *ins, अक्षर *bf, माप_प्रकार size,
			  काष्ठा ins_opeअक्रमs *ops, पूर्णांक max_ins_name);

अटल काष्ठा ins_ops arm64_mov_ops = अणु
	.parse	   = arm64_mov__parse,
	.scnम_लिखो = mov__scnम_लिखो,
पूर्ण;

अटल काष्ठा ins_ops *arm64__associate_inकाष्ठाion_ops(काष्ठा arch *arch, स्थिर अक्षर *name)
अणु
	काष्ठा arm64_annotate *arm = arch->priv;
	काष्ठा ins_ops *ops;
	regmatch_t match[2];

	अगर (!regexec(&arm->jump_insn, name, 2, match, 0))
		ops = &jump_ops;
	अन्यथा अगर (!regexec(&arm->call_insn, name, 2, match, 0))
		ops = &call_ops;
	अन्यथा अगर (!म_भेद(name, "ret"))
		ops = &ret_ops;
	अन्यथा
		ops = &arm64_mov_ops;

	arch__associate_ins_ops(arch, name, ops);
	वापस ops;
पूर्ण

अटल पूर्णांक arm64__annotate_init(काष्ठा arch *arch, अक्षर *cpuid __maybe_unused)
अणु
	काष्ठा arm64_annotate *arm;
	पूर्णांक err;

	अगर (arch->initialized)
		वापस 0;

	arm = zalloc(माप(*arm));
	अगर (!arm)
		वापस ENOMEM;

	/* bl, blr */
	err = regcomp(&arm->call_insn, "^blr?$", REG_EXTENDED);
	अगर (err)
		जाओ out_मुक्त_arm;
	/* b, b.cond, br, cbz/cbnz, tbz/tbnz */
	err = regcomp(&arm->jump_insn, "^[ct]?br?\\.?(cc|cs|eq|ge|gt|hi|le|ls|lt|mi|ne|pl)?n?z?$",
		      REG_EXTENDED);
	अगर (err)
		जाओ out_मुक्त_call;

	arch->initialized = true;
	arch->priv	  = arm;
	arch->associate_inकाष्ठाion_ops   = arm64__associate_inकाष्ठाion_ops;
	arch->objdump.comment_अक्षर	  = '/';
	arch->objdump.skip_functions_अक्षर = '+';
	वापस 0;

out_मुक्त_call:
	regमुक्त(&arm->call_insn);
out_मुक्त_arm:
	मुक्त(arm);
	वापस SYMBOL_ANNOTATE_ERRNO__ARCH_INIT_REGEXP;
पूर्ण
