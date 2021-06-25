<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/compiler.h>
#समावेश <linux/zभाग.स>
#समावेश <sys/types.h>
#समावेश <regex.h>
#समावेश <मानककोष.स>

काष्ठा arm_annotate अणु
	regex_t call_insn,
		jump_insn;
पूर्ण;

अटल काष्ठा ins_ops *arm__associate_inकाष्ठाion_ops(काष्ठा arch *arch, स्थिर अक्षर *name)
अणु
	काष्ठा arm_annotate *arm = arch->priv;
	काष्ठा ins_ops *ops;
	regmatch_t match[2];

	अगर (!regexec(&arm->call_insn, name, 2, match, 0))
		ops = &call_ops;
	अन्यथा अगर (!regexec(&arm->jump_insn, name, 2, match, 0))
		ops = &jump_ops;
	अन्यथा
		वापस शून्य;

	arch__associate_ins_ops(arch, name, ops);
	वापस ops;
पूर्ण

अटल पूर्णांक arm__annotate_init(काष्ठा arch *arch, अक्षर *cpuid __maybe_unused)
अणु
	काष्ठा arm_annotate *arm;
	पूर्णांक err;

	अगर (arch->initialized)
		वापस 0;

	arm = zalloc(माप(*arm));
	अगर (!arm)
		वापस ENOMEM;

#घोषणा ARM_CONDS "(cc|cs|eq|ge|gt|hi|le|ls|lt|mi|ne|pl|vc|vs)"
	err = regcomp(&arm->call_insn, "^blx?" ARM_CONDS "?$", REG_EXTENDED);
	अगर (err)
		जाओ out_मुक्त_arm;
	err = regcomp(&arm->jump_insn, "^bx?" ARM_CONDS "?$", REG_EXTENDED);
	अगर (err)
		जाओ out_मुक्त_call;
#अघोषित ARM_CONDS

	arch->initialized = true;
	arch->priv	  = arm;
	arch->associate_inकाष्ठाion_ops   = arm__associate_inकाष्ठाion_ops;
	arch->objdump.comment_अक्षर	  = ';';
	arch->objdump.skip_functions_अक्षर = '+';
	वापस 0;

out_मुक्त_call:
	regमुक्त(&arm->call_insn);
out_मुक्त_arm:
	मुक्त(arm);
	वापस SYMBOL_ANNOTATE_ERRNO__ARCH_INIT_REGEXP;
पूर्ण
