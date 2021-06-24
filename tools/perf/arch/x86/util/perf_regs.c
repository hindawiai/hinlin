<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <त्रुटिसं.स>
#समावेश <माला.स>
#समावेश <regex.h>
#समावेश <linux/kernel.h>
#समावेश <linux/zभाग.स>

#समावेश "../../../perf-sys.h"
#समावेश "../../../util/perf_regs.h"
#समावेश "../../../util/debug.h"
#समावेश "../../../util/event.h"

स्थिर काष्ठा sample_reg sample_reg_masks[] = अणु
	SMPL_REG(AX, PERF_REG_X86_AX),
	SMPL_REG(BX, PERF_REG_X86_BX),
	SMPL_REG(CX, PERF_REG_X86_CX),
	SMPL_REG(DX, PERF_REG_X86_DX),
	SMPL_REG(SI, PERF_REG_X86_SI),
	SMPL_REG(DI, PERF_REG_X86_DI),
	SMPL_REG(BP, PERF_REG_X86_BP),
	SMPL_REG(SP, PERF_REG_X86_SP),
	SMPL_REG(IP, PERF_REG_X86_IP),
	SMPL_REG(FLAGS, PERF_REG_X86_FLAGS),
	SMPL_REG(CS, PERF_REG_X86_CS),
	SMPL_REG(SS, PERF_REG_X86_SS),
#अगर_घोषित HAVE_ARCH_X86_64_SUPPORT
	SMPL_REG(R8, PERF_REG_X86_R8),
	SMPL_REG(R9, PERF_REG_X86_R9),
	SMPL_REG(R10, PERF_REG_X86_R10),
	SMPL_REG(R11, PERF_REG_X86_R11),
	SMPL_REG(R12, PERF_REG_X86_R12),
	SMPL_REG(R13, PERF_REG_X86_R13),
	SMPL_REG(R14, PERF_REG_X86_R14),
	SMPL_REG(R15, PERF_REG_X86_R15),
#पूर्ण_अगर
	SMPL_REG2(XMM0, PERF_REG_X86_XMM0),
	SMPL_REG2(XMM1, PERF_REG_X86_XMM1),
	SMPL_REG2(XMM2, PERF_REG_X86_XMM2),
	SMPL_REG2(XMM3, PERF_REG_X86_XMM3),
	SMPL_REG2(XMM4, PERF_REG_X86_XMM4),
	SMPL_REG2(XMM5, PERF_REG_X86_XMM5),
	SMPL_REG2(XMM6, PERF_REG_X86_XMM6),
	SMPL_REG2(XMM7, PERF_REG_X86_XMM7),
	SMPL_REG2(XMM8, PERF_REG_X86_XMM8),
	SMPL_REG2(XMM9, PERF_REG_X86_XMM9),
	SMPL_REG2(XMM10, PERF_REG_X86_XMM10),
	SMPL_REG2(XMM11, PERF_REG_X86_XMM11),
	SMPL_REG2(XMM12, PERF_REG_X86_XMM12),
	SMPL_REG2(XMM13, PERF_REG_X86_XMM13),
	SMPL_REG2(XMM14, PERF_REG_X86_XMM14),
	SMPL_REG2(XMM15, PERF_REG_X86_XMM15),
	SMPL_REG_END
पूर्ण;

काष्ठा sdt_name_reg अणु
	स्थिर अक्षर *sdt_name;
	स्थिर अक्षर *uprobe_name;
पूर्ण;
#घोषणा SDT_NAME_REG(n, m) अणु.sdt_name = "%" #n, .uprobe_name = "%" #mपूर्ण
#घोषणा SDT_NAME_REG_END अणु.sdt_name = शून्य, .uprobe_name = शून्यपूर्ण

अटल स्थिर काष्ठा sdt_name_reg sdt_reg_tbl[] = अणु
	SDT_NAME_REG(eax, ax),
	SDT_NAME_REG(rax, ax),
	SDT_NAME_REG(al,  ax),
	SDT_NAME_REG(ah,  ax),
	SDT_NAME_REG(ebx, bx),
	SDT_NAME_REG(rbx, bx),
	SDT_NAME_REG(bl,  bx),
	SDT_NAME_REG(bh,  bx),
	SDT_NAME_REG(ecx, cx),
	SDT_NAME_REG(rcx, cx),
	SDT_NAME_REG(cl,  cx),
	SDT_NAME_REG(ch,  cx),
	SDT_NAME_REG(edx, dx),
	SDT_NAME_REG(rdx, dx),
	SDT_NAME_REG(dl,  dx),
	SDT_NAME_REG(dh,  dx),
	SDT_NAME_REG(esi, si),
	SDT_NAME_REG(rsi, si),
	SDT_NAME_REG(sil, si),
	SDT_NAME_REG(edi, di),
	SDT_NAME_REG(rdi, di),
	SDT_NAME_REG(dil, di),
	SDT_NAME_REG(ebp, bp),
	SDT_NAME_REG(rbp, bp),
	SDT_NAME_REG(bpl, bp),
	SDT_NAME_REG(rsp, sp),
	SDT_NAME_REG(esp, sp),
	SDT_NAME_REG(spl, sp),

	/* rNN रेजिस्टरs */
	SDT_NAME_REG(r8b,  r8),
	SDT_NAME_REG(r8w,  r8),
	SDT_NAME_REG(r8d,  r8),
	SDT_NAME_REG(r9b,  r9),
	SDT_NAME_REG(r9w,  r9),
	SDT_NAME_REG(r9d,  r9),
	SDT_NAME_REG(r10b, r10),
	SDT_NAME_REG(r10w, r10),
	SDT_NAME_REG(r10d, r10),
	SDT_NAME_REG(r11b, r11),
	SDT_NAME_REG(r11w, r11),
	SDT_NAME_REG(r11d, r11),
	SDT_NAME_REG(r12b, r12),
	SDT_NAME_REG(r12w, r12),
	SDT_NAME_REG(r12d, r12),
	SDT_NAME_REG(r13b, r13),
	SDT_NAME_REG(r13w, r13),
	SDT_NAME_REG(r13d, r13),
	SDT_NAME_REG(r14b, r14),
	SDT_NAME_REG(r14w, r14),
	SDT_NAME_REG(r14d, r14),
	SDT_NAME_REG(r15b, r15),
	SDT_NAME_REG(r15w, r15),
	SDT_NAME_REG(r15d, r15),
	SDT_NAME_REG_END,
पूर्ण;

/*
 * Perf only supports OP which is in  +/-NUM(REG)  क्रमm.
 * Here plus-minus sign, NUM and parenthesis are optional,
 * only REG is mandatory.
 *
 * SDT events also supports indirect addressing mode with a
 * symbol as offset, scaled mode and स्थिरants in OP. But
 * perf करोes not support them yet. Below are few examples.
 *
 * OP with scaled mode:
 *     (%rax,%rsi,8)
 *     10(%ras,%rsi,8)
 *
 * OP with indirect addressing mode:
 *     check_action(%rip)
 *     mp_+52(%rip)
 *     44+mp_(%rip)
 *
 * OP with स्थिरant values:
 *     $0
 *     $123
 *     $-1
 */
#घोषणा SDT_OP_REGEX  "^([+\\-]?)([0-9]*)(\\(?)(%[a-z][a-z0-9]+)(\\)?)$"

अटल regex_t sdt_op_regex;

अटल पूर्णांक sdt_init_op_regex(व्योम)
अणु
	अटल पूर्णांक initialized;
	पूर्णांक ret = 0;

	अगर (initialized)
		वापस 0;

	ret = regcomp(&sdt_op_regex, SDT_OP_REGEX, REG_EXTENDED);
	अगर (ret < 0) अणु
		pr_debug4("Regex compilation error.\n");
		वापस ret;
	पूर्ण

	initialized = 1;
	वापस 0;
पूर्ण

/*
 * Max x86 रेजिस्टर name length is 5(ex: %r15d). So, 6th अक्षर
 * should always contain शून्य. This helps to find रेजिस्टर name
 * length using म_माप, instead of मुख्यtaining one more variable.
 */
#घोषणा SDT_REG_NAME_SIZE  6

/*
 * The uprobe parser करोes not support all gas रेजिस्टर names;
 * so, we have to replace them (ex. क्रम x86_64: %rax -> %ax).
 * Note: If रेजिस्टर करोes not require renaming, just copy
 * paste as it is, but करोn't leave it empty.
 */
अटल व्योम sdt_नाम_रेजिस्टर(अक्षर *sdt_reg, पूर्णांक sdt_len, अक्षर *uprobe_reg)
अणु
	पूर्णांक i = 0;

	क्रम (i = 0; sdt_reg_tbl[i].sdt_name != शून्य; i++) अणु
		अगर (!म_भेदन(sdt_reg_tbl[i].sdt_name, sdt_reg, sdt_len)) अणु
			म_नकल(uprobe_reg, sdt_reg_tbl[i].uprobe_name);
			वापस;
		पूर्ण
	पूर्ण

	म_नकलन(uprobe_reg, sdt_reg, sdt_len);
पूर्ण

पूर्णांक arch_sdt_arg_parse_op(अक्षर *old_op, अक्षर **new_op)
अणु
	अक्षर new_reg[SDT_REG_NAME_SIZE] = अणु0पूर्ण;
	पूर्णांक new_len = 0, ret;
	/*
	 * rm[0]:  +/-NUM(REG)
	 * rm[1]:  +/-
	 * rm[2]:  NUM
	 * rm[3]:  (
	 * rm[4]:  REG
	 * rm[5]:  )
	 */
	regmatch_t rm[6];
	/*
	 * Max prefix length is 2 as it may contains sign(+/-)
	 * and displacement 0 (Both sign and displacement 0 are
	 * optional so it may be empty). Use one more अक्षरacter
	 * to hold last शून्य so that म_माप can be used to find
	 * prefix length, instead of मुख्यtaining one more variable.
	 */
	अक्षर prefix[3] = अणु0पूर्ण;

	ret = sdt_init_op_regex();
	अगर (ret < 0)
		वापस ret;

	/*
	 * If unsupported OR करोes not match with regex OR
	 * रेजिस्टर name too दीर्घ, skip it.
	 */
	अगर (म_अक्षर(old_op, ',') || strchr(old_op, '$') ||
	    regexec(&sdt_op_regex, old_op, 6, rm, 0)   ||
	    rm[4].rm_eo - rm[4].rm_so > SDT_REG_NAME_SIZE) अणु
		pr_debug4("Skipping unsupported SDT argument: %s\n", old_op);
		वापस SDT_ARG_SKIP;
	पूर्ण

	/*
	 * Prepare prefix.
	 * If SDT OP has parenthesis but करोes not provide
	 * displacement, add 0 क्रम displacement.
	 *     SDT         Uprobe     Prefix
	 *     -----------------------------
	 *     +24(%rdi)   +24(%di)   +
	 *     24(%rdi)    +24(%di)   +
	 *     %rdi        %di
	 *     (%rdi)      +0(%di)    +0
	 *     -80(%rbx)   -80(%bx)   -
	 */
	अगर (rm[3].rm_so != rm[3].rm_eo) अणु
		अगर (rm[1].rm_so != rm[1].rm_eo)
			prefix[0] = *(old_op + rm[1].rm_so);
		अन्यथा अगर (rm[2].rm_so != rm[2].rm_eo)
			prefix[0] = '+';
		अन्यथा
			scnम_लिखो(prefix, माप(prefix), "+0");
	पूर्ण

	/* Rename रेजिस्टर */
	sdt_नाम_रेजिस्टर(old_op + rm[4].rm_so, rm[4].rm_eo - rm[4].rm_so,
			    new_reg);

	/* Prepare final OP which should be valid क्रम uprobe_events */
	new_len = म_माप(prefix)              +
		  (rm[2].rm_eo - rm[2].rm_so) +
		  (rm[3].rm_eo - rm[3].rm_so) +
		  म_माप(new_reg)             +
		  (rm[5].rm_eo - rm[5].rm_so) +
		  1;					/* शून्य */

	*new_op = zalloc(new_len);
	अगर (!*new_op)
		वापस -ENOMEM;

	scnम_लिखो(*new_op, new_len, "%.*s%.*s%.*s%.*s%.*s",
		  म_माप(prefix), prefix,
		  (पूर्णांक)(rm[2].rm_eo - rm[2].rm_so), old_op + rm[2].rm_so,
		  (पूर्णांक)(rm[3].rm_eo - rm[3].rm_so), old_op + rm[3].rm_so,
		  म_माप(new_reg), new_reg,
		  (पूर्णांक)(rm[5].rm_eo - rm[5].rm_so), old_op + rm[5].rm_so);

	वापस SDT_ARG_VALID;
पूर्ण

uपूर्णांक64_t arch__पूर्णांकr_reg_mask(व्योम)
अणु
	काष्ठा perf_event_attr attr = अणु
		.type			= PERF_TYPE_HARDWARE,
		.config			= PERF_COUNT_HW_CPU_CYCLES,
		.sample_type		= PERF_SAMPLE_REGS_INTR,
		.sample_regs_पूर्णांकr	= PERF_REG_EXTENDED_MASK,
		.precise_ip		= 1,
		.disabled 		= 1,
		.exclude_kernel		= 1,
	पूर्ण;
	पूर्णांक fd;
	/*
	 * In an unnamed जोड़, init it here to build on older gcc versions
	 */
	attr.sample_period = 1;

	event_attr_init(&attr);

	fd = sys_perf_event_खोलो(&attr, 0, -1, -1, 0);
	अगर (fd != -1) अणु
		बंद(fd);
		वापस (PERF_REG_EXTENDED_MASK | PERF_REGS_MASK);
	पूर्ण

	वापस PERF_REGS_MASK;
पूर्ण
