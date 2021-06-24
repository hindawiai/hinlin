<शैली गुरु>
/*
 * Dynamic function tracing support.
 *
 * Copyright (C) 2008 Shaohua Li <shaohua.li@पूर्णांकel.com>
 *
 * For licencing details, see COPYING.
 *
 * Defines low-level handling of mcount calls when the kernel
 * is compiled with the -pg flag. When using dynamic ftrace, the
 * mcount call-sites get patched lazily with NOP till they are
 * enabled. All code mutation routines here take effect atomically.
 */

#समावेश <linux/uaccess.h>
#समावेश <linux/ftrace.h>

#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/patch.h>

/* In IA64, each function will be added below two bundles with -pg option */
अटल अचिन्हित अक्षर __attribute__((aligned(8)))
ftrace_orig_code[MCOUNT_INSN_SIZE] = अणु
	0x02, 0x40, 0x31, 0x10, 0x80, 0x05, /* alloc r40=ar.pfs,12,8,0 */
	0xb0, 0x02, 0x00, 0x00, 0x42, 0x40, /* mov r43=r0;; */
	0x05, 0x00, 0xc4, 0x00,             /* mov r42=b0 */
	0x11, 0x48, 0x01, 0x02, 0x00, 0x21, /* mov r41=r1 */
	0x00, 0x00, 0x00, 0x02, 0x00, 0x00, /* nop.i 0x0 */
	0x08, 0x00, 0x00, 0x50              /* br.call.sptk.many b0 = _mcount;; */
पूर्ण;

काष्ठा ftrace_orig_insn अणु
	u64 dummy1, dummy2, dummy3;
	u64 dummy4:64-41+13;
	u64 imm20:20;
	u64 dummy5:3;
	u64 sign:1;
	u64 dummy6:4;
पूर्ण;

/* mcount stub will be converted below क्रम nop */
अटल अचिन्हित अक्षर ftrace_nop_code[MCOUNT_INSN_SIZE] = अणु
	0x00, 0x00, 0x00, 0x00, 0x01, 0x00, /* [MII] nop.m 0x0 */
	0x30, 0x00, 0x00, 0x60, 0x00, 0x00, /* mov r3=ip */
	0x00, 0x00, 0x04, 0x00,             /* nop.i 0x0 */
	0x05, 0x00, 0x00, 0x00, 0x01, 0x00, /* [MLX] nop.m 0x0 */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* nop.x 0x0;; */
	0x00, 0x00, 0x04, 0x00
पूर्ण;

अटल अचिन्हित अक्षर *ftrace_nop_replace(व्योम)
अणु
	वापस ftrace_nop_code;
पूर्ण

/*
 * mcount stub will be converted below क्रम call
 * Note: Just the last inकाष्ठाion is changed against nop
 * */
अटल अचिन्हित अक्षर __attribute__((aligned(8)))
ftrace_call_code[MCOUNT_INSN_SIZE] = अणु
	0x00, 0x00, 0x00, 0x00, 0x01, 0x00, /* [MII] nop.m 0x0 */
	0x30, 0x00, 0x00, 0x60, 0x00, 0x00, /* mov r3=ip */
	0x00, 0x00, 0x04, 0x00,             /* nop.i 0x0 */
	0x05, 0x00, 0x00, 0x00, 0x01, 0x00, /* [MLX] nop.m 0x0 */
	0xff, 0xff, 0xff, 0xff, 0x7f, 0x00, /* brl.many .;;*/
	0xf8, 0xff, 0xff, 0xc8
पूर्ण;

काष्ठा ftrace_call_insn अणु
	u64 dummy1, dummy2;
	u64 dummy3:48;
	u64 imm39_l:16;
	u64 imm39_h:23;
	u64 dummy4:13;
	u64 imm20:20;
	u64 dummy5:3;
	u64 i:1;
	u64 dummy6:4;
पूर्ण;

अटल अचिन्हित अक्षर *ftrace_call_replace(अचिन्हित दीर्घ ip, अचिन्हित दीर्घ addr)
अणु
	काष्ठा ftrace_call_insn *code = (व्योम *)ftrace_call_code;
	अचिन्हित दीर्घ offset = addr - (ip + 0x10);

	code->imm39_l = offset >> 24;
	code->imm39_h = offset >> 40;
	code->imm20 = offset >> 4;
	code->i = offset >> 63;
	वापस ftrace_call_code;
पूर्ण

अटल पूर्णांक
ftrace_modअगरy_code(अचिन्हित दीर्घ ip, अचिन्हित अक्षर *old_code,
		   अचिन्हित अक्षर *new_code, पूर्णांक करो_check)
अणु
	अचिन्हित अक्षर replaced[MCOUNT_INSN_SIZE];

	/*
	 * Note:
	 * We are paranoid about modअगरying text, as अगर a bug was to happen, it
	 * could cause us to पढ़ो or ग_लिखो to someplace that could cause harm.
	 * Carefully पढ़ो and modअगरy the code with probe_kernel_*(), and make
	 * sure what we पढ़ो is what we expected it to be beक्रमe modअगरying it.
	 */

	अगर (!करो_check)
		जाओ skip_check;

	/* पढ़ो the text we want to modअगरy */
	अगर (copy_from_kernel_nofault(replaced, (व्योम *)ip, MCOUNT_INSN_SIZE))
		वापस -EFAULT;

	/* Make sure it is what we expect it to be */
	अगर (स_भेद(replaced, old_code, MCOUNT_INSN_SIZE) != 0)
		वापस -EINVAL;

skip_check:
	/* replace the text with the new text */
	अगर (copy_to_kernel_nofault(((व्योम *)ip), new_code, MCOUNT_INSN_SIZE))
		वापस -EPERM;
	flush_icache_range(ip, ip + MCOUNT_INSN_SIZE);

	वापस 0;
पूर्ण

अटल पूर्णांक ftrace_make_nop_check(काष्ठा dyn_ftrace *rec, अचिन्हित दीर्घ addr)
अणु
	अचिन्हित अक्षर __attribute__((aligned(8))) replaced[MCOUNT_INSN_SIZE];
	अचिन्हित दीर्घ ip = rec->ip;

	अगर (copy_from_kernel_nofault(replaced, (व्योम *)ip, MCOUNT_INSN_SIZE))
		वापस -EFAULT;
	अगर (rec->flags & FTRACE_FL_CONVERTED) अणु
		काष्ठा ftrace_call_insn *call_insn, *पंचांगp_call;

		call_insn = (व्योम *)ftrace_call_code;
		पंचांगp_call = (व्योम *)replaced;
		call_insn->imm39_l = पंचांगp_call->imm39_l;
		call_insn->imm39_h = पंचांगp_call->imm39_h;
		call_insn->imm20 = पंचांगp_call->imm20;
		call_insn->i = पंचांगp_call->i;
		अगर (स_भेद(replaced, ftrace_call_code, MCOUNT_INSN_SIZE) != 0)
			वापस -EINVAL;
		वापस 0;
	पूर्ण अन्यथा अणु
		काष्ठा ftrace_orig_insn *call_insn, *पंचांगp_call;

		call_insn = (व्योम *)ftrace_orig_code;
		पंचांगp_call = (व्योम *)replaced;
		call_insn->sign = पंचांगp_call->sign;
		call_insn->imm20 = पंचांगp_call->imm20;
		अगर (स_भेद(replaced, ftrace_orig_code, MCOUNT_INSN_SIZE) != 0)
			वापस -EINVAL;
		वापस 0;
	पूर्ण
पूर्ण

पूर्णांक ftrace_make_nop(काष्ठा module *mod,
		    काष्ठा dyn_ftrace *rec, अचिन्हित दीर्घ addr)
अणु
	पूर्णांक ret;
	अक्षर *new;

	ret = ftrace_make_nop_check(rec, addr);
	अगर (ret)
		वापस ret;
	new = ftrace_nop_replace();
	वापस ftrace_modअगरy_code(rec->ip, शून्य, new, 0);
पूर्ण

पूर्णांक ftrace_make_call(काष्ठा dyn_ftrace *rec, अचिन्हित दीर्घ addr)
अणु
	अचिन्हित दीर्घ ip = rec->ip;
	अचिन्हित अक्षर *old, *new;

	old=  ftrace_nop_replace();
	new = ftrace_call_replace(ip, addr);
	वापस ftrace_modअगरy_code(ip, old, new, 1);
पूर्ण

/* in IA64, _mcount can't directly call ftrace_stub. Only jump is ok */
पूर्णांक ftrace_update_ftrace_func(ftrace_func_t func)
अणु
	अचिन्हित दीर्घ ip;
	अचिन्हित दीर्घ addr = ((काष्ठा fnptr *)ftrace_call)->ip;

	अगर (func == ftrace_stub)
		वापस 0;
	ip = ((काष्ठा fnptr *)func)->ip;

	ia64_patch_imm64(addr + 2, ip);

	flush_icache_range(addr, addr + 16);
	वापस 0;
पूर्ण

/* run from kstop_machine */
पूर्णांक __init ftrace_dyn_arch_init(व्योम)
अणु
	वापस 0;
पूर्ण
