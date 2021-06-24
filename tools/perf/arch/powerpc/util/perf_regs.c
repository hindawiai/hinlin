<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <त्रुटिसं.स>
#समावेश <माला.स>
#समावेश <regex.h>
#समावेश <linux/zभाग.स>

#समावेश "../../../util/perf_regs.h"
#समावेश "../../../util/debug.h"
#समावेश "../../../util/event.h"
#समावेश "../../../util/header.h"
#समावेश "../../../perf-sys.h"
#समावेश "utils_header.h"

#समावेश <linux/kernel.h>

#घोषणा PVR_POWER9		0x004E
#घोषणा PVR_POWER10		0x0080

स्थिर काष्ठा sample_reg sample_reg_masks[] = अणु
	SMPL_REG(r0, PERF_REG_POWERPC_R0),
	SMPL_REG(r1, PERF_REG_POWERPC_R1),
	SMPL_REG(r2, PERF_REG_POWERPC_R2),
	SMPL_REG(r3, PERF_REG_POWERPC_R3),
	SMPL_REG(r4, PERF_REG_POWERPC_R4),
	SMPL_REG(r5, PERF_REG_POWERPC_R5),
	SMPL_REG(r6, PERF_REG_POWERPC_R6),
	SMPL_REG(r7, PERF_REG_POWERPC_R7),
	SMPL_REG(r8, PERF_REG_POWERPC_R8),
	SMPL_REG(r9, PERF_REG_POWERPC_R9),
	SMPL_REG(r10, PERF_REG_POWERPC_R10),
	SMPL_REG(r11, PERF_REG_POWERPC_R11),
	SMPL_REG(r12, PERF_REG_POWERPC_R12),
	SMPL_REG(r13, PERF_REG_POWERPC_R13),
	SMPL_REG(r14, PERF_REG_POWERPC_R14),
	SMPL_REG(r15, PERF_REG_POWERPC_R15),
	SMPL_REG(r16, PERF_REG_POWERPC_R16),
	SMPL_REG(r17, PERF_REG_POWERPC_R17),
	SMPL_REG(r18, PERF_REG_POWERPC_R18),
	SMPL_REG(r19, PERF_REG_POWERPC_R19),
	SMPL_REG(r20, PERF_REG_POWERPC_R20),
	SMPL_REG(r21, PERF_REG_POWERPC_R21),
	SMPL_REG(r22, PERF_REG_POWERPC_R22),
	SMPL_REG(r23, PERF_REG_POWERPC_R23),
	SMPL_REG(r24, PERF_REG_POWERPC_R24),
	SMPL_REG(r25, PERF_REG_POWERPC_R25),
	SMPL_REG(r26, PERF_REG_POWERPC_R26),
	SMPL_REG(r27, PERF_REG_POWERPC_R27),
	SMPL_REG(r28, PERF_REG_POWERPC_R28),
	SMPL_REG(r29, PERF_REG_POWERPC_R29),
	SMPL_REG(r30, PERF_REG_POWERPC_R30),
	SMPL_REG(r31, PERF_REG_POWERPC_R31),
	SMPL_REG(nip, PERF_REG_POWERPC_NIP),
	SMPL_REG(msr, PERF_REG_POWERPC_MSR),
	SMPL_REG(orig_r3, PERF_REG_POWERPC_ORIG_R3),
	SMPL_REG(ctr, PERF_REG_POWERPC_CTR),
	SMPL_REG(link, PERF_REG_POWERPC_LINK),
	SMPL_REG(xer, PERF_REG_POWERPC_XER),
	SMPL_REG(ccr, PERF_REG_POWERPC_CCR),
	SMPL_REG(softe, PERF_REG_POWERPC_SOFTE),
	SMPL_REG(trap, PERF_REG_POWERPC_TRAP),
	SMPL_REG(dar, PERF_REG_POWERPC_DAR),
	SMPL_REG(dsisr, PERF_REG_POWERPC_DSISR),
	SMPL_REG(sier, PERF_REG_POWERPC_SIER),
	SMPL_REG(mmcra, PERF_REG_POWERPC_MMCRA),
	SMPL_REG(mmcr0, PERF_REG_POWERPC_MMCR0),
	SMPL_REG(mmcr1, PERF_REG_POWERPC_MMCR1),
	SMPL_REG(mmcr2, PERF_REG_POWERPC_MMCR2),
	SMPL_REG(mmcr3, PERF_REG_POWERPC_MMCR3),
	SMPL_REG(sier2, PERF_REG_POWERPC_SIER2),
	SMPL_REG(sier3, PERF_REG_POWERPC_SIER3),
	SMPL_REG(pmc1, PERF_REG_POWERPC_PMC1),
	SMPL_REG(pmc2, PERF_REG_POWERPC_PMC2),
	SMPL_REG(pmc3, PERF_REG_POWERPC_PMC3),
	SMPL_REG(pmc4, PERF_REG_POWERPC_PMC4),
	SMPL_REG(pmc5, PERF_REG_POWERPC_PMC5),
	SMPL_REG(pmc6, PERF_REG_POWERPC_PMC6),
	SMPL_REG_END
पूर्ण;

/* REG or %rREG */
#घोषणा SDT_OP_REGEX1  "^(%r)?([1-2]?[0-9]|3[0-1])$"

/* -NUM(REG) or NUM(REG) or -NUM(%rREG) or NUM(%rREG) */
#घोषणा SDT_OP_REGEX2  "^(\\-)?([0-9]+)\\((%r)?([1-2]?[0-9]|3[0-1])\\)$"

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
 * Parse OP and convert it पूर्णांकo uprobe क्रमmat, which is, +/-NUM(%gprREG).
 * Possible variants of OP are:
 *	Format		Example
 *	-------------------------
 *	NUM(REG)	48(18)
 *	-NUM(REG)	-48(18)
 *	NUM(%rREG)	48(%r18)
 *	-NUM(%rREG)	-48(%r18)
 *	REG		18
 *	%rREG		%r18
 *	iNUM		i0
 *	i-NUM		i-1
 *
 * SDT marker arguments on Powerpc uses %rREG क्रमm with -mregnames flag
 * and REG क्रमm with -mno-regnames. Here REG is general purpose रेजिस्टर,
 * which is in 0 to 31 range.
 */
पूर्णांक arch_sdt_arg_parse_op(अक्षर *old_op, अक्षर **new_op)
अणु
	पूर्णांक ret, new_len;
	regmatch_t rm[5];
	अक्षर prefix;

	/* Constant argument. Uprobe करोes not support it */
	अगर (old_op[0] == 'i') अणु
		pr_debug4("Skipping unsupported SDT argument: %s\n", old_op);
		वापस SDT_ARG_SKIP;
	पूर्ण

	ret = sdt_init_op_regex();
	अगर (ret < 0)
		वापस ret;

	अगर (!regexec(&sdt_op_regex1, old_op, 3, rm, 0)) अणु
		/* REG or %rREG --> %gprREG */

		new_len = 5;	/* % g p r शून्य */
		new_len += (पूर्णांक)(rm[2].rm_eo - rm[2].rm_so);

		*new_op = zalloc(new_len);
		अगर (!*new_op)
			वापस -ENOMEM;

		scnम_लिखो(*new_op, new_len, "%%gpr%.*s",
			(पूर्णांक)(rm[2].rm_eo - rm[2].rm_so), old_op + rm[2].rm_so);
	पूर्ण अन्यथा अगर (!regexec(&sdt_op_regex2, old_op, 5, rm, 0)) अणु
		/*
		 * -NUM(REG) or NUM(REG) or -NUM(%rREG) or NUM(%rREG) -->
		 *	+/-NUM(%gprREG)
		 */
		prefix = (rm[1].rm_so == -1) ? '+' : '-';

		new_len = 8;	/* +/- ( % g p r ) शून्य */
		new_len += (पूर्णांक)(rm[2].rm_eo - rm[2].rm_so);
		new_len += (पूर्णांक)(rm[4].rm_eo - rm[4].rm_so);

		*new_op = zalloc(new_len);
		अगर (!*new_op)
			वापस -ENOMEM;

		scnम_लिखो(*new_op, new_len, "%c%.*s(%%gpr%.*s)", prefix,
			(पूर्णांक)(rm[2].rm_eo - rm[2].rm_so), old_op + rm[2].rm_so,
			(पूर्णांक)(rm[4].rm_eo - rm[4].rm_so), old_op + rm[4].rm_so);
	पूर्ण अन्यथा अणु
		pr_debug4("Skipping unsupported SDT argument: %s\n", old_op);
		वापस SDT_ARG_SKIP;
	पूर्ण

	वापस SDT_ARG_VALID;
पूर्ण

uपूर्णांक64_t arch__पूर्णांकr_reg_mask(व्योम)
अणु
	काष्ठा perf_event_attr attr = अणु
		.type                   = PERF_TYPE_HARDWARE,
		.config                 = PERF_COUNT_HW_CPU_CYCLES,
		.sample_type            = PERF_SAMPLE_REGS_INTR,
		.precise_ip             = 1,
		.disabled               = 1,
		.exclude_kernel         = 1,
	पूर्ण;
	पूर्णांक fd;
	u32 version;
	u64 extended_mask = 0, mask = PERF_REGS_MASK;

	/*
	 * Get the PVR value to set the extended
	 * mask specअगरic to platक्रमm.
	 */
	version = (((mfspr(SPRN_PVR)) >>  16) & 0xFFFF);
	अगर (version == PVR_POWER9)
		extended_mask = PERF_REG_PMU_MASK_300;
	अन्यथा अगर (version == PVR_POWER10)
		extended_mask = PERF_REG_PMU_MASK_31;
	अन्यथा
		वापस mask;

	attr.sample_regs_पूर्णांकr = extended_mask;
	attr.sample_period = 1;
	event_attr_init(&attr);

	/*
	 * check अगर the pmu supports perf extended regs, beक्रमe
	 * वापसing the रेजिस्टर mask to sample.
	 */
	fd = sys_perf_event_खोलो(&attr, 0, -1, -1, 0);
	अगर (fd != -1) अणु
		बंद(fd);
		mask |= extended_mask;
	पूर्ण
	वापस mask;
पूर्ण
