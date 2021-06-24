<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <त्रुटिसं.स>
#समावेश <regex.h>
#समावेश <माला.स>
#समावेश <linux/kernel.h>
#समावेश <linux/zभाग.स>

#समावेश "../../../util/debug.h"
#समावेश "../../../util/event.h"
#समावेश "../../../util/perf_regs.h"

स्थिर काष्ठा sample_reg sample_reg_masks[] = अणु
	SMPL_REG(x0, PERF_REG_ARM64_X0),
	SMPL_REG(x1, PERF_REG_ARM64_X1),
	SMPL_REG(x2, PERF_REG_ARM64_X2),
	SMPL_REG(x3, PERF_REG_ARM64_X3),
	SMPL_REG(x4, PERF_REG_ARM64_X4),
	SMPL_REG(x5, PERF_REG_ARM64_X5),
	SMPL_REG(x6, PERF_REG_ARM64_X6),
	SMPL_REG(x7, PERF_REG_ARM64_X7),
	SMPL_REG(x8, PERF_REG_ARM64_X8),
	SMPL_REG(x9, PERF_REG_ARM64_X9),
	SMPL_REG(x10, PERF_REG_ARM64_X10),
	SMPL_REG(x11, PERF_REG_ARM64_X11),
	SMPL_REG(x12, PERF_REG_ARM64_X12),
	SMPL_REG(x13, PERF_REG_ARM64_X13),
	SMPL_REG(x14, PERF_REG_ARM64_X14),
	SMPL_REG(x15, PERF_REG_ARM64_X15),
	SMPL_REG(x16, PERF_REG_ARM64_X16),
	SMPL_REG(x17, PERF_REG_ARM64_X17),
	SMPL_REG(x18, PERF_REG_ARM64_X18),
	SMPL_REG(x19, PERF_REG_ARM64_X19),
	SMPL_REG(x20, PERF_REG_ARM64_X20),
	SMPL_REG(x21, PERF_REG_ARM64_X21),
	SMPL_REG(x22, PERF_REG_ARM64_X22),
	SMPL_REG(x23, PERF_REG_ARM64_X23),
	SMPL_REG(x24, PERF_REG_ARM64_X24),
	SMPL_REG(x25, PERF_REG_ARM64_X25),
	SMPL_REG(x26, PERF_REG_ARM64_X26),
	SMPL_REG(x27, PERF_REG_ARM64_X27),
	SMPL_REG(x28, PERF_REG_ARM64_X28),
	SMPL_REG(x29, PERF_REG_ARM64_X29),
	SMPL_REG(lr, PERF_REG_ARM64_LR),
	SMPL_REG(sp, PERF_REG_ARM64_SP),
	SMPL_REG(pc, PERF_REG_ARM64_PC),
	SMPL_REG_END
पूर्ण;

/* %xNUM */
#घोषणा SDT_OP_REGEX1  "^(x[1-2]?[0-9]|3[0-1])$"

/* [sp], [sp, NUM] */
#घोषणा SDT_OP_REGEX2  "^\\[sp(, )?([0-9]+)?\\]$"

अटल regex_t sdt_op_regex1, sdt_op_regex2;

अटल पूर्णांक sdt_init_op_regex(व्योम)
अणु
	अटल पूर्णांक initialized;
	पूर्णांक ret = 0;

	अगर (initialized)
		वापस 0;

	ret = regcomp(&sdt_op_regex1, SDT_OP_REGEX1, REG_EXTENDED);
	अगर (ret)
		जाओ error;

	ret = regcomp(&sdt_op_regex2, SDT_OP_REGEX2, REG_EXTENDED);
	अगर (ret)
		जाओ मुक्त_regex1;

	initialized = 1;
	वापस 0;

मुक्त_regex1:
	regमुक्त(&sdt_op_regex1);
error:
	pr_debug4("Regex compilation error.\n");
	वापस ret;
पूर्ण

/*
 * SDT marker arguments on Arm64 uses %xREG or [sp, NUM], currently
 * support these two क्रमmats.
 */
पूर्णांक arch_sdt_arg_parse_op(अक्षर *old_op, अक्षर **new_op)
अणु
	पूर्णांक ret, new_len;
	regmatch_t rm[5];

	ret = sdt_init_op_regex();
	अगर (ret < 0)
		वापस ret;

	अगर (!regexec(&sdt_op_regex1, old_op, 3, rm, 0)) अणु
		/* Extract xNUM */
		new_len = 2;	/* % शून्य */
		new_len += (पूर्णांक)(rm[1].rm_eo - rm[1].rm_so);

		*new_op = zalloc(new_len);
		अगर (!*new_op)
			वापस -ENOMEM;

		scnम_लिखो(*new_op, new_len, "%%%.*s",
			(पूर्णांक)(rm[1].rm_eo - rm[1].rm_so), old_op + rm[1].rm_so);
	पूर्ण अन्यथा अगर (!regexec(&sdt_op_regex2, old_op, 5, rm, 0)) अणु
		/* [sp], [sp, NUM] or [sp,NUM] */
		new_len = 7;	/* + ( % s p ) शून्य */

		/* If the argument is [sp], need to fill offset '0' */
		अगर (rm[2].rm_so == -1)
			new_len += 1;
		अन्यथा
			new_len += (पूर्णांक)(rm[2].rm_eo - rm[2].rm_so);

		*new_op = zalloc(new_len);
		अगर (!*new_op)
			वापस -ENOMEM;

		अगर (rm[2].rm_so == -1)
			scnम_लिखो(*new_op, new_len, "+0(%%sp)");
		अन्यथा
			scnम_लिखो(*new_op, new_len, "+%.*s(%%sp)",
				  (पूर्णांक)(rm[2].rm_eo - rm[2].rm_so),
				  old_op + rm[2].rm_so);
	पूर्ण अन्यथा अणु
		pr_debug4("Skipping unsupported SDT argument: %s\n", old_op);
		वापस SDT_ARG_SKIP;
	पूर्ण

	वापस SDT_ARG_VALID;
पूर्ण
