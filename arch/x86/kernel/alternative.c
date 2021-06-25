<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#घोषणा pr_fmt(fmt) "SMP alternatives: " fmt

#समावेश <linux/module.h>
#समावेश <linux/sched.h>
#समावेश <linux/perf_event.h>
#समावेश <linux/mutex.h>
#समावेश <linux/list.h>
#समावेश <linux/stringअगरy.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/mm.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/memory.h>
#समावेश <linux/stop_machine.h>
#समावेश <linux/slab.h>
#समावेश <linux/kdebug.h>
#समावेश <linux/kprobes.h>
#समावेश <linux/mmu_context.h>
#समावेश <linux/द्वा_खोज.h>
#समावेश <linux/sync_core.h>
#समावेश <यंत्र/text-patching.h>
#समावेश <यंत्र/alternative.h>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/mce.h>
#समावेश <यंत्र/nmi.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र/insn.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/fixmap.h>
#समावेश <यंत्र/paravirt.h>

पूर्णांक __पढ़ो_mostly alternatives_patched;

EXPORT_SYMBOL_GPL(alternatives_patched);

#घोषणा MAX_PATCH_LEN (255-1)

अटल पूर्णांक __initdata_or_module debug_alternative;

अटल पूर्णांक __init debug_alt(अक्षर *str)
अणु
	debug_alternative = 1;
	वापस 1;
पूर्ण
__setup("debug-alternative", debug_alt);

अटल पूर्णांक noreplace_smp;

अटल पूर्णांक __init setup_noreplace_smp(अक्षर *str)
अणु
	noreplace_smp = 1;
	वापस 1;
पूर्ण
__setup("noreplace-smp", setup_noreplace_smp);

#घोषणा DPRINTK(fmt, args...)						\
करो अणु									\
	अगर (debug_alternative)						\
		prपूर्णांकk(KERN_DEBUG pr_fmt(fmt) "\n", ##args);		\
पूर्ण जबतक (0)

#घोषणा DUMP_BYTES(buf, len, fmt, args...)				\
करो अणु									\
	अगर (unlikely(debug_alternative)) अणु				\
		पूर्णांक j;							\
									\
		अगर (!(len))						\
			अवरोध;						\
									\
		prपूर्णांकk(KERN_DEBUG pr_fmt(fmt), ##args);			\
		क्रम (j = 0; j < (len) - 1; j++)				\
			prपूर्णांकk(KERN_CONT "%02hhx ", buf[j]);		\
		prपूर्णांकk(KERN_CONT "%02hhx\n", buf[j]);			\
	पूर्ण								\
पूर्ण जबतक (0)

स्थिर अचिन्हित अक्षर x86nops[] =
अणु
	BYTES_NOP1,
	BYTES_NOP2,
	BYTES_NOP3,
	BYTES_NOP4,
	BYTES_NOP5,
	BYTES_NOP6,
	BYTES_NOP7,
	BYTES_NOP8,
पूर्ण;

स्थिर अचिन्हित अक्षर * स्थिर x86_nops[ASM_NOP_MAX+1] =
अणु
	शून्य,
	x86nops,
	x86nops + 1,
	x86nops + 1 + 2,
	x86nops + 1 + 2 + 3,
	x86nops + 1 + 2 + 3 + 4,
	x86nops + 1 + 2 + 3 + 4 + 5,
	x86nops + 1 + 2 + 3 + 4 + 5 + 6,
	x86nops + 1 + 2 + 3 + 4 + 5 + 6 + 7,
पूर्ण;

/* Use this to add nops to a buffer, then text_poke the whole buffer. */
अटल व्योम __init_or_module add_nops(व्योम *insns, अचिन्हित पूर्णांक len)
अणु
	जबतक (len > 0) अणु
		अचिन्हित पूर्णांक noplen = len;
		अगर (noplen > ASM_NOP_MAX)
			noplen = ASM_NOP_MAX;
		स_नकल(insns, x86_nops[noplen], noplen);
		insns += noplen;
		len -= noplen;
	पूर्ण
पूर्ण

बाह्य काष्ठा alt_instr __alt_inकाष्ठाions[], __alt_inकाष्ठाions_end[];
बाह्य s32 __smp_locks[], __smp_locks_end[];
व्योम text_poke_early(व्योम *addr, स्थिर व्योम *opcode, माप_प्रकार len);

/*
 * Are we looking at a near JMP with a 1 or 4-byte displacement.
 */
अटल अंतरभूत bool is_jmp(स्थिर u8 opcode)
अणु
	वापस opcode == 0xeb || opcode == 0xe9;
पूर्ण

अटल व्योम __init_or_module
recompute_jump(काष्ठा alt_instr *a, u8 *orig_insn, u8 *repl_insn, u8 *insn_buff)
अणु
	u8 *next_rip, *tgt_rip;
	s32 n_dspl, o_dspl;
	पूर्णांक repl_len;

	अगर (a->replacementlen != 5)
		वापस;

	o_dspl = *(s32 *)(insn_buff + 1);

	/* next_rip of the replacement JMP */
	next_rip = repl_insn + a->replacementlen;
	/* target rip of the replacement JMP */
	tgt_rip  = next_rip + o_dspl;
	n_dspl = tgt_rip - orig_insn;

	DPRINTK("target RIP: %px, new_displ: 0x%x", tgt_rip, n_dspl);

	अगर (tgt_rip - orig_insn >= 0) अणु
		अगर (n_dspl - 2 <= 127)
			जाओ two_byte_jmp;
		अन्यथा
			जाओ five_byte_jmp;
	/* negative offset */
	पूर्ण अन्यथा अणु
		अगर (((n_dspl - 2) & 0xff) == (n_dspl - 2))
			जाओ two_byte_jmp;
		अन्यथा
			जाओ five_byte_jmp;
	पूर्ण

two_byte_jmp:
	n_dspl -= 2;

	insn_buff[0] = 0xeb;
	insn_buff[1] = (s8)n_dspl;
	add_nops(insn_buff + 2, 3);

	repl_len = 2;
	जाओ करोne;

five_byte_jmp:
	n_dspl -= 5;

	insn_buff[0] = 0xe9;
	*(s32 *)&insn_buff[1] = n_dspl;

	repl_len = 5;

करोne:

	DPRINTK("final displ: 0x%08x, JMP 0x%lx",
		n_dspl, (अचिन्हित दीर्घ)orig_insn + n_dspl + repl_len);
पूर्ण

/*
 * optimize_nops_range() - Optimize a sequence of single byte NOPs (0x90)
 *
 * @instr: inकाष्ठाion byte stream
 * @inम_माप: length of the above
 * @off: offset within @instr where the first NOP has been detected
 *
 * Return: number of NOPs found (and replaced).
 */
अटल __always_अंतरभूत पूर्णांक optimize_nops_range(u8 *instr, u8 inम_माप, पूर्णांक off)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक i = off, nnops;

	जबतक (i < inम_माप) अणु
		अगर (instr[i] != 0x90)
			अवरोध;

		i++;
	पूर्ण

	nnops = i - off;

	अगर (nnops <= 1)
		वापस nnops;

	local_irq_save(flags);
	add_nops(instr + off, nnops);
	local_irq_restore(flags);

	DUMP_BYTES(instr, inम_माप, "%px: [%d:%d) optimized NOPs: ", instr, off, i);

	वापस nnops;
पूर्ण

/*
 * "noinline" to cause control flow change and thus invalidate I$ and
 * cause refetch after modअगरication.
 */
अटल व्योम __init_or_module noअंतरभूत optimize_nops(काष्ठा alt_instr *a, u8 *instr)
अणु
	काष्ठा insn insn;
	पूर्णांक i = 0;

	/*
	 * Jump over the non-NOP insns and optimize single-byte NOPs पूर्णांकo bigger
	 * ones.
	 */
	क्रम (;;) अणु
		अगर (insn_decode_kernel(&insn, &instr[i]))
			वापस;

		/*
		 * See अगर this and any potentially following NOPs can be
		 * optimized.
		 */
		अगर (insn.length == 1 && insn.opcode.bytes[0] == 0x90)
			i += optimize_nops_range(instr, a->inम_माप, i);
		अन्यथा
			i += insn.length;

		अगर (i >= a->inम_माप)
			वापस;
	पूर्ण
पूर्ण

/*
 * Replace inकाष्ठाions with better alternatives क्रम this CPU type. This runs
 * beक्रमe SMP is initialized to aव्योम SMP problems with self modअगरying code.
 * This implies that asymmetric प्रणालीs where APs have less capabilities than
 * the boot processor are not handled. Tough. Make sure you disable such
 * features by hand.
 *
 * Marked "noinline" to cause control flow change and thus insn cache
 * to refetch changed I$ lines.
 */
व्योम __init_or_module noअंतरभूत apply_alternatives(काष्ठा alt_instr *start,
						  काष्ठा alt_instr *end)
अणु
	काष्ठा alt_instr *a;
	u8 *instr, *replacement;
	u8 insn_buff[MAX_PATCH_LEN];

	DPRINTK("alt table %px, -> %px", start, end);
	/*
	 * The scan order should be from start to end. A later scanned
	 * alternative code can overग_लिखो previously scanned alternative code.
	 * Some kernel functions (e.g. स_नकल, स_रखो, etc) use this order to
	 * patch code.
	 *
	 * So be careful अगर you want to change the scan order to any other
	 * order.
	 */
	क्रम (a = start; a < end; a++) अणु
		पूर्णांक insn_buff_sz = 0;
		/* Mask away "NOT" flag bit क्रम feature to test. */
		u16 feature = a->cpuid & ~ALTINSTR_FLAG_INV;

		instr = (u8 *)&a->instr_offset + a->instr_offset;
		replacement = (u8 *)&a->repl_offset + a->repl_offset;
		BUG_ON(a->inम_माप > माप(insn_buff));
		BUG_ON(feature >= (NCAPINTS + NBUGINTS) * 32);

		/*
		 * Patch अगर either:
		 * - feature is present
		 * - feature not present but ALTINSTR_FLAG_INV is set to mean,
		 *   patch अगर feature is *NOT* present.
		 */
		अगर (!boot_cpu_has(feature) == !(a->cpuid & ALTINSTR_FLAG_INV))
			जाओ next;

		DPRINTK("feat: %s%d*32+%d, old: (%pS (%px) len: %d), repl: (%px, len: %d)",
			(a->cpuid & ALTINSTR_FLAG_INV) ? "!" : "",
			feature >> 5,
			feature & 0x1f,
			instr, instr, a->inम_माप,
			replacement, a->replacementlen);

		DUMP_BYTES(instr, a->inम_माप, "%px: old_insn: ", instr);
		DUMP_BYTES(replacement, a->replacementlen, "%px: rpl_insn: ", replacement);

		स_नकल(insn_buff, replacement, a->replacementlen);
		insn_buff_sz = a->replacementlen;

		/*
		 * 0xe8 is a relative jump; fix the offset.
		 *
		 * Inकाष्ठाion length is checked beक्रमe the opcode to aव्योम
		 * accessing uninitialized bytes क्रम zero-length replacements.
		 */
		अगर (a->replacementlen == 5 && *insn_buff == 0xe8) अणु
			*(s32 *)(insn_buff + 1) += replacement - instr;
			DPRINTK("Fix CALL offset: 0x%x, CALL 0x%lx",
				*(s32 *)(insn_buff + 1),
				(अचिन्हित दीर्घ)instr + *(s32 *)(insn_buff + 1) + 5);
		पूर्ण

		अगर (a->replacementlen && is_jmp(replacement[0]))
			recompute_jump(a, instr, replacement, insn_buff);

		क्रम (; insn_buff_sz < a->inम_माप; insn_buff_sz++)
			insn_buff[insn_buff_sz] = 0x90;

		DUMP_BYTES(insn_buff, insn_buff_sz, "%px: final_insn: ", instr);

		text_poke_early(instr, insn_buff, insn_buff_sz);

next:
		optimize_nops(a, instr);
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_SMP
अटल व्योम alternatives_smp_lock(स्थिर s32 *start, स्थिर s32 *end,
				  u8 *text, u8 *text_end)
अणु
	स्थिर s32 *poff;

	क्रम (poff = start; poff < end; poff++) अणु
		u8 *ptr = (u8 *)poff + *poff;

		अगर (!*poff || ptr < text || ptr >= text_end)
			जारी;
		/* turn DS segment override prefix पूर्णांकo lock prefix */
		अगर (*ptr == 0x3e)
			text_poke(ptr, ((अचिन्हित अक्षर [])अणु0xf0पूर्ण), 1);
	पूर्ण
पूर्ण

अटल व्योम alternatives_smp_unlock(स्थिर s32 *start, स्थिर s32 *end,
				    u8 *text, u8 *text_end)
अणु
	स्थिर s32 *poff;

	क्रम (poff = start; poff < end; poff++) अणु
		u8 *ptr = (u8 *)poff + *poff;

		अगर (!*poff || ptr < text || ptr >= text_end)
			जारी;
		/* turn lock prefix पूर्णांकo DS segment override prefix */
		अगर (*ptr == 0xf0)
			text_poke(ptr, ((अचिन्हित अक्षर [])अणु0x3Eपूर्ण), 1);
	पूर्ण
पूर्ण

काष्ठा smp_alt_module अणु
	/* what is this ??? */
	काष्ठा module	*mod;
	अक्षर		*name;

	/* ptrs to lock prefixes */
	स्थिर s32	*locks;
	स्थिर s32	*locks_end;

	/* .text segment, needed to aव्योम patching init code ;) */
	u8		*text;
	u8		*text_end;

	काष्ठा list_head next;
पूर्ण;
अटल LIST_HEAD(smp_alt_modules);
अटल bool uniproc_patched = false;	/* रक्षित by text_mutex */

व्योम __init_or_module alternatives_smp_module_add(काष्ठा module *mod,
						  अक्षर *name,
						  व्योम *locks, व्योम *locks_end,
						  व्योम *text,  व्योम *text_end)
अणु
	काष्ठा smp_alt_module *smp;

	mutex_lock(&text_mutex);
	अगर (!uniproc_patched)
		जाओ unlock;

	अगर (num_possible_cpus() == 1)
		/* Don't bother remembering, we'll never have to unकरो it. */
		जाओ smp_unlock;

	smp = kzalloc(माप(*smp), GFP_KERNEL);
	अगर (शून्य == smp)
		/* we'll run the (safe but slow) SMP code then ... */
		जाओ unlock;

	smp->mod	= mod;
	smp->name	= name;
	smp->locks	= locks;
	smp->locks_end	= locks_end;
	smp->text	= text;
	smp->text_end	= text_end;
	DPRINTK("locks %p -> %p, text %p -> %p, name %s\n",
		smp->locks, smp->locks_end,
		smp->text, smp->text_end, smp->name);

	list_add_tail(&smp->next, &smp_alt_modules);
smp_unlock:
	alternatives_smp_unlock(locks, locks_end, text, text_end);
unlock:
	mutex_unlock(&text_mutex);
पूर्ण

व्योम __init_or_module alternatives_smp_module_del(काष्ठा module *mod)
अणु
	काष्ठा smp_alt_module *item;

	mutex_lock(&text_mutex);
	list_क्रम_each_entry(item, &smp_alt_modules, next) अणु
		अगर (mod != item->mod)
			जारी;
		list_del(&item->next);
		kमुक्त(item);
		अवरोध;
	पूर्ण
	mutex_unlock(&text_mutex);
पूर्ण

व्योम alternatives_enable_smp(व्योम)
अणु
	काष्ठा smp_alt_module *mod;

	/* Why bother अगर there are no other CPUs? */
	BUG_ON(num_possible_cpus() == 1);

	mutex_lock(&text_mutex);

	अगर (uniproc_patched) अणु
		pr_info("switching to SMP code\n");
		BUG_ON(num_online_cpus() != 1);
		clear_cpu_cap(&boot_cpu_data, X86_FEATURE_UP);
		clear_cpu_cap(&cpu_data(0), X86_FEATURE_UP);
		list_क्रम_each_entry(mod, &smp_alt_modules, next)
			alternatives_smp_lock(mod->locks, mod->locks_end,
					      mod->text, mod->text_end);
		uniproc_patched = false;
	पूर्ण
	mutex_unlock(&text_mutex);
पूर्ण

/*
 * Return 1 अगर the address range is reserved क्रम SMP-alternatives.
 * Must hold text_mutex.
 */
पूर्णांक alternatives_text_reserved(व्योम *start, व्योम *end)
अणु
	काष्ठा smp_alt_module *mod;
	स्थिर s32 *poff;
	u8 *text_start = start;
	u8 *text_end = end;

	lockdep_निश्चित_held(&text_mutex);

	list_क्रम_each_entry(mod, &smp_alt_modules, next) अणु
		अगर (mod->text > text_end || mod->text_end < text_start)
			जारी;
		क्रम (poff = mod->locks; poff < mod->locks_end; poff++) अणु
			स्थिर u8 *ptr = (स्थिर u8 *)poff + *poff;

			अगर (text_start <= ptr && text_end > ptr)
				वापस 1;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_SMP */

#अगर_घोषित CONFIG_PARAVIRT
व्योम __init_or_module apply_paravirt(काष्ठा paravirt_patch_site *start,
				     काष्ठा paravirt_patch_site *end)
अणु
	काष्ठा paravirt_patch_site *p;
	अक्षर insn_buff[MAX_PATCH_LEN];

	क्रम (p = start; p < end; p++) अणु
		अचिन्हित पूर्णांक used;

		BUG_ON(p->len > MAX_PATCH_LEN);
		/* prep the buffer with the original inकाष्ठाions */
		स_नकल(insn_buff, p->instr, p->len);
		used = paravirt_patch(p->type, insn_buff, (अचिन्हित दीर्घ)p->instr, p->len);

		BUG_ON(used > p->len);

		/* Pad the rest with nops */
		add_nops(insn_buff + used, p->len - used);
		text_poke_early(p->instr, insn_buff, p->len);
	पूर्ण
पूर्ण
बाह्य काष्ठा paravirt_patch_site __start_parainकाष्ठाions[],
	__stop_parainकाष्ठाions[];
#पूर्ण_अगर	/* CONFIG_PARAVIRT */

/*
 * Self-test क्रम the INT3 based CALL emulation code.
 *
 * This exercises पूर्णांक3_emulate_call() to make sure INT3 pt_regs are set up
 * properly and that there is a stack gap between the INT3 frame and the
 * previous context. Without this gap करोing a भव PUSH on the पूर्णांकerrupted
 * stack would corrupt the INT3 IRET frame.
 *
 * See entry_अणु32,64पूर्ण.S क्रम more details.
 */

/*
 * We define the पूर्णांक3_magic() function in assembly to control the calling
 * convention such that we can 'call' it from assembly.
 */

बाह्य व्योम पूर्णांक3_magic(अचिन्हित पूर्णांक *ptr); /* defined in यंत्र */

यंत्र (
"	.pushsection	.init.text, \"ax\", @progbits\n"
"	.type		int3_magic, @function\n"
"int3_magic:\n"
"	movl	$1, (%" _ASM_ARG1 ")\n"
"	ret\n"
"	.size		int3_magic, .-int3_magic\n"
"	.popsection\n"
);

बाह्य __initdata अचिन्हित दीर्घ पूर्णांक3_selftest_ip; /* defined in यंत्र below */

अटल पूर्णांक __init
पूर्णांक3_exception_notअगरy(काष्ठा notअगरier_block *self, अचिन्हित दीर्घ val, व्योम *data)
अणु
	काष्ठा die_args *args = data;
	काष्ठा pt_regs *regs = args->regs;

	अगर (!regs || user_mode(regs))
		वापस NOTIFY_DONE;

	अगर (val != DIE_INT3)
		वापस NOTIFY_DONE;

	अगर (regs->ip - INT3_INSN_SIZE != पूर्णांक3_selftest_ip)
		वापस NOTIFY_DONE;

	पूर्णांक3_emulate_call(regs, (अचिन्हित दीर्घ)&पूर्णांक3_magic);
	वापस NOTIFY_STOP;
पूर्ण

अटल व्योम __init पूर्णांक3_selftest(व्योम)
अणु
	अटल __initdata काष्ठा notअगरier_block पूर्णांक3_exception_nb = अणु
		.notअगरier_call	= पूर्णांक3_exception_notअगरy,
		.priority	= पूर्णांक_उच्च-1, /* last */
	पूर्ण;
	अचिन्हित पूर्णांक val = 0;

	BUG_ON(रेजिस्टर_die_notअगरier(&पूर्णांक3_exception_nb));

	/*
	 * Basically: पूर्णांक3_magic(&val); but really complicated :-)
	 *
	 * Stick the address of the INT3 inकाष्ठाion पूर्णांकo पूर्णांक3_selftest_ip,
	 * then trigger the INT3, padded with NOPs to match a CALL inकाष्ठाion
	 * length.
	 */
	यंत्र अस्थिर ("1: int3; nop; nop; nop; nop\n\t"
		      ".pushsection .init.data,\"aw\"\n\t"
		      ".align " __ASM_SEL(4, 8) "\n\t"
		      ".type int3_selftest_ip, @object\n\t"
		      ".size int3_selftest_ip, " __ASM_SEL(4, 8) "\n\t"
		      "int3_selftest_ip:\n\t"
		      __ASM_SEL(.दीर्घ, .quad) " 1b\n\t"
		      ".popsection\n\t"
		      : ASM_CALL_CONSTRAINT
		      : __ASM_SEL_RAW(a, D) (&val)
		      : "memory");

	BUG_ON(val != 1);

	unरेजिस्टर_die_notअगरier(&पूर्णांक3_exception_nb);
पूर्ण

व्योम __init alternative_inकाष्ठाions(व्योम)
अणु
	पूर्णांक3_selftest();

	/*
	 * The patching is not fully atomic, so try to aव्योम local
	 * पूर्णांकerruptions that might execute the to be patched code.
	 * Other CPUs are not running.
	 */
	stop_nmi();

	/*
	 * Don't stop machine check exceptions जबतक patching.
	 * MCEs only happen when something got corrupted and in this
	 * हाल we must करो something about the corruption.
	 * Ignoring it is worse than an unlikely patching race.
	 * Also machine checks tend to be broadcast and अगर one CPU
	 * goes पूर्णांकo machine check the others follow quickly, so we करोn't
	 * expect a machine check to cause undue problems during to code
	 * patching.
	 */

	/*
	 * Paravirt patching and alternative patching can be combined to
	 * replace a function call with a लघु direct code sequence (e.g.
	 * by setting a स्थिरant वापस value instead of करोing that in an
	 * बाह्यal function).
	 * In order to make this work the following sequence is required:
	 * 1. set (artअगरicial) features depending on used paravirt
	 *    functions which can later influence alternative patching
	 * 2. apply paravirt patching (generally replacing an indirect
	 *    function call with a direct one)
	 * 3. apply alternative patching (e.g. replacing a direct function
	 *    call with a custom code sequence)
	 * Doing paravirt patching after alternative patching would clobber
	 * the optimization of the custom code with a function call again.
	 */
	paravirt_set_cap();

	/*
	 * First patch paravirt functions, such that we overग_लिखो the indirect
	 * call with the direct call.
	 */
	apply_paravirt(__parainकाष्ठाions, __parainकाष्ठाions_end);

	/*
	 * Then patch alternatives, such that those paravirt calls that are in
	 * alternatives can be overwritten by their immediate fragments.
	 */
	apply_alternatives(__alt_inकाष्ठाions, __alt_inकाष्ठाions_end);

#अगर_घोषित CONFIG_SMP
	/* Patch to UP अगर other cpus not imminent. */
	अगर (!noreplace_smp && (num_present_cpus() == 1 || setup_max_cpus <= 1)) अणु
		uniproc_patched = true;
		alternatives_smp_module_add(शून्य, "core kernel",
					    __smp_locks, __smp_locks_end,
					    _text, _etext);
	पूर्ण

	अगर (!uniproc_patched || num_possible_cpus() == 1) अणु
		मुक्त_init_pages("SMP alternatives",
				(अचिन्हित दीर्घ)__smp_locks,
				(अचिन्हित दीर्घ)__smp_locks_end);
	पूर्ण
#पूर्ण_अगर

	restart_nmi();
	alternatives_patched = 1;
पूर्ण

/**
 * text_poke_early - Update inकाष्ठाions on a live kernel at boot समय
 * @addr: address to modअगरy
 * @opcode: source of the copy
 * @len: length to copy
 *
 * When you use this code to patch more than one byte of an inकाष्ठाion
 * you need to make sure that other CPUs cannot execute this code in parallel.
 * Also no thपढ़ो must be currently preempted in the middle of these
 * inकाष्ठाions. And on the local CPU you need to be रक्षित against NMI or
 * MCE handlers seeing an inconsistent inकाष्ठाion जबतक you patch.
 */
व्योम __init_or_module text_poke_early(व्योम *addr, स्थिर व्योम *opcode,
				      माप_प्रकार len)
अणु
	अचिन्हित दीर्घ flags;

	अगर (boot_cpu_has(X86_FEATURE_NX) &&
	    is_module_text_address((अचिन्हित दीर्घ)addr)) अणु
		/*
		 * Modules text is marked initially as non-executable, so the
		 * code cannot be running and speculative code-fetches are
		 * prevented. Just change the code.
		 */
		स_नकल(addr, opcode, len);
	पूर्ण अन्यथा अणु
		local_irq_save(flags);
		स_नकल(addr, opcode, len);
		local_irq_restore(flags);
		sync_core();

		/*
		 * Could also करो a CLFLUSH here to speed up CPU recovery; but
		 * that causes hangs on some VIA CPUs.
		 */
	पूर्ण
पूर्ण

प्रकार काष्ठा अणु
	काष्ठा mm_काष्ठा *mm;
पूर्ण temp_mm_state_t;

/*
 * Using a temporary mm allows to set temporary mappings that are not accessible
 * by other CPUs. Such mappings are needed to perक्रमm sensitive memory ग_लिखोs
 * that override the kernel memory protections (e.g., W^X), without exposing the
 * temporary page-table mappings that are required क्रम these ग_लिखो operations to
 * other CPUs. Using a temporary mm also allows to aव्योम TLB shootकरोwns when the
 * mapping is torn करोwn.
 *
 * Context: The temporary mm needs to be used exclusively by a single core. To
 *          harden security IRQs must be disabled जबतक the temporary mm is
 *          loaded, thereby preventing पूर्णांकerrupt handler bugs from overriding
 *          the kernel memory protection.
 */
अटल अंतरभूत temp_mm_state_t use_temporary_mm(काष्ठा mm_काष्ठा *mm)
अणु
	temp_mm_state_t temp_state;

	lockdep_निश्चित_irqs_disabled();

	/*
	 * Make sure not to be in TLB lazy mode, as otherwise we'll end up
	 * with a stale address space WITHOUT being in lazy mode after
	 * restoring the previous mm.
	 */
	अगर (this_cpu_पढ़ो(cpu_tlbstate_shared.is_lazy))
		leave_mm(smp_processor_id());

	temp_state.mm = this_cpu_पढ़ो(cpu_tlbstate.loaded_mm);
	चयन_mm_irqs_off(शून्य, mm, current);

	/*
	 * If अवरोधpoपूर्णांकs are enabled, disable them जबतक the temporary mm is
	 * used. Userspace might set up watchpoपूर्णांकs on addresses that are used
	 * in the temporary mm, which would lead to wrong संकेतs being sent or
	 * crashes.
	 *
	 * Note that अवरोधpoपूर्णांकs are not disabled selectively, which also causes
	 * kernel अवरोधpoपूर्णांकs (e.g., perf's) to be disabled. This might be
	 * undesirable, but still seems reasonable as the code that runs in the
	 * temporary mm should be लघु.
	 */
	अगर (hw_अवरोधpoपूर्णांक_active())
		hw_अवरोधpoपूर्णांक_disable();

	वापस temp_state;
पूर्ण

अटल अंतरभूत व्योम unuse_temporary_mm(temp_mm_state_t prev_state)
अणु
	lockdep_निश्चित_irqs_disabled();
	चयन_mm_irqs_off(शून्य, prev_state.mm, current);

	/*
	 * Restore the अवरोधpoपूर्णांकs अगर they were disabled beक्रमe the temporary mm
	 * was loaded.
	 */
	अगर (hw_अवरोधpoपूर्णांक_active())
		hw_अवरोधpoपूर्णांक_restore();
पूर्ण

__ro_after_init काष्ठा mm_काष्ठा *poking_mm;
__ro_after_init अचिन्हित दीर्घ poking_addr;

अटल व्योम *__text_poke(व्योम *addr, स्थिर व्योम *opcode, माप_प्रकार len)
अणु
	bool cross_page_boundary = offset_in_page(addr) + len > PAGE_SIZE;
	काष्ठा page *pages[2] = अणुशून्यपूर्ण;
	temp_mm_state_t prev;
	अचिन्हित दीर्घ flags;
	pte_t pte, *ptep;
	spinlock_t *ptl;
	pgprot_t pgprot;

	/*
	 * While boot memory allocator is running we cannot use काष्ठा pages as
	 * they are not yet initialized. There is no way to recover.
	 */
	BUG_ON(!after_booपंचांगem);

	अगर (!core_kernel_text((अचिन्हित दीर्घ)addr)) अणु
		pages[0] = vदो_स्मृति_to_page(addr);
		अगर (cross_page_boundary)
			pages[1] = vदो_स्मृति_to_page(addr + PAGE_SIZE);
	पूर्ण अन्यथा अणु
		pages[0] = virt_to_page(addr);
		WARN_ON(!PageReserved(pages[0]));
		अगर (cross_page_boundary)
			pages[1] = virt_to_page(addr + PAGE_SIZE);
	पूर्ण
	/*
	 * If something went wrong, crash and burn since recovery paths are not
	 * implemented.
	 */
	BUG_ON(!pages[0] || (cross_page_boundary && !pages[1]));

	/*
	 * Map the page without the global bit, as TLB flushing is करोne with
	 * flush_tlb_mm_range(), which is पूर्णांकended क्रम non-global PTEs.
	 */
	pgprot = __pgprot(pgprot_val(PAGE_KERNEL) & ~_PAGE_GLOBAL);

	/*
	 * The lock is not really needed, but this allows to aव्योम खोलो-coding.
	 */
	ptep = get_locked_pte(poking_mm, poking_addr, &ptl);

	/*
	 * This must not fail; pपुनः_स्मृतिated in poking_init().
	 */
	VM_BUG_ON(!ptep);

	local_irq_save(flags);

	pte = mk_pte(pages[0], pgprot);
	set_pte_at(poking_mm, poking_addr, ptep, pte);

	अगर (cross_page_boundary) अणु
		pte = mk_pte(pages[1], pgprot);
		set_pte_at(poking_mm, poking_addr + PAGE_SIZE, ptep + 1, pte);
	पूर्ण

	/*
	 * Loading the temporary mm behaves as a compiler barrier, which
	 * guarantees that the PTE will be set at the समय स_नकल() is करोne.
	 */
	prev = use_temporary_mm(poking_mm);

	kasan_disable_current();
	स_नकल((u8 *)poking_addr + offset_in_page(addr), opcode, len);
	kasan_enable_current();

	/*
	 * Ensure that the PTE is only cleared after the inकाष्ठाions of स_नकल
	 * were issued by using a compiler barrier.
	 */
	barrier();

	pte_clear(poking_mm, poking_addr, ptep);
	अगर (cross_page_boundary)
		pte_clear(poking_mm, poking_addr + PAGE_SIZE, ptep + 1);

	/*
	 * Loading the previous page-table hierarchy requires a serializing
	 * inकाष्ठाion that alपढ़ोy allows the core to see the updated version.
	 * Xen-PV is assumed to serialize execution in a similar manner.
	 */
	unuse_temporary_mm(prev);

	/*
	 * Flushing the TLB might involve IPIs, which would require enabled
	 * IRQs, but not अगर the mm is not used, as it is in this poपूर्णांक.
	 */
	flush_tlb_mm_range(poking_mm, poking_addr, poking_addr +
			   (cross_page_boundary ? 2 : 1) * PAGE_SIZE,
			   PAGE_SHIFT, false);

	/*
	 * If the text करोes not match what we just wrote then something is
	 * fundamentally screwy; there's nothing we can really करो about that.
	 */
	BUG_ON(स_भेद(addr, opcode, len));

	local_irq_restore(flags);
	pte_unmap_unlock(ptep, ptl);
	वापस addr;
पूर्ण

/**
 * text_poke - Update inकाष्ठाions on a live kernel
 * @addr: address to modअगरy
 * @opcode: source of the copy
 * @len: length to copy
 *
 * Only atomic text poke/set should be allowed when not करोing early patching.
 * It means the size must be writable atomically and the address must be aligned
 * in a way that permits an atomic ग_लिखो. It also makes sure we fit on a single
 * page.
 *
 * Note that the caller must ensure that अगर the modअगरied code is part of a
 * module, the module would not be हटाओd during poking. This can be achieved
 * by रेजिस्टरing a module notअगरier, and ordering module removal and patching
 * trough a mutex.
 */
व्योम *text_poke(व्योम *addr, स्थिर व्योम *opcode, माप_प्रकार len)
अणु
	lockdep_निश्चित_held(&text_mutex);

	वापस __text_poke(addr, opcode, len);
पूर्ण

/**
 * text_poke_kgdb - Update inकाष्ठाions on a live kernel by kgdb
 * @addr: address to modअगरy
 * @opcode: source of the copy
 * @len: length to copy
 *
 * Only atomic text poke/set should be allowed when not करोing early patching.
 * It means the size must be writable atomically and the address must be aligned
 * in a way that permits an atomic ग_लिखो. It also makes sure we fit on a single
 * page.
 *
 * Context: should only be used by kgdb, which ensures no other core is running,
 *	    despite the fact it करोes not hold the text_mutex.
 */
व्योम *text_poke_kgdb(व्योम *addr, स्थिर व्योम *opcode, माप_प्रकार len)
अणु
	वापस __text_poke(addr, opcode, len);
पूर्ण

अटल व्योम करो_sync_core(व्योम *info)
अणु
	sync_core();
पूर्ण

व्योम text_poke_sync(व्योम)
अणु
	on_each_cpu(करो_sync_core, शून्य, 1);
पूर्ण

काष्ठा text_poke_loc अणु
	s32 rel_addr; /* addr := _stext + rel_addr */
	s32 rel32;
	u8 opcode;
	स्थिर u8 text[POKE_MAX_OPCODE_SIZE];
	u8 old;
पूर्ण;

काष्ठा bp_patching_desc अणु
	काष्ठा text_poke_loc *vec;
	पूर्णांक nr_entries;
	atomic_t refs;
पूर्ण;

अटल काष्ठा bp_patching_desc *bp_desc;

अटल __always_अंतरभूत
काष्ठा bp_patching_desc *try_get_desc(काष्ठा bp_patching_desc **descp)
अणु
	काष्ठा bp_patching_desc *desc = __READ_ONCE(*descp); /* rcu_dereference */

	अगर (!desc || !arch_atomic_inc_not_zero(&desc->refs))
		वापस शून्य;

	वापस desc;
पूर्ण

अटल __always_अंतरभूत व्योम put_desc(काष्ठा bp_patching_desc *desc)
अणु
	smp_mb__beक्रमe_atomic();
	arch_atomic_dec(&desc->refs);
पूर्ण

अटल __always_अंतरभूत व्योम *text_poke_addr(काष्ठा text_poke_loc *tp)
अणु
	वापस _stext + tp->rel_addr;
पूर्ण

अटल __always_अंतरभूत पूर्णांक patch_cmp(स्थिर व्योम *key, स्थिर व्योम *elt)
अणु
	काष्ठा text_poke_loc *tp = (काष्ठा text_poke_loc *) elt;

	अगर (key < text_poke_addr(tp))
		वापस -1;
	अगर (key > text_poke_addr(tp))
		वापस 1;
	वापस 0;
पूर्ण

noinstr पूर्णांक poke_पूर्णांक3_handler(काष्ठा pt_regs *regs)
अणु
	काष्ठा bp_patching_desc *desc;
	काष्ठा text_poke_loc *tp;
	पूर्णांक len, ret = 0;
	व्योम *ip;

	अगर (user_mode(regs))
		वापस 0;

	/*
	 * Having observed our INT3 inकाष्ठाion, we now must observe
	 * bp_desc:
	 *
	 *	bp_desc = desc			INT3
	 *	WMB				RMB
	 *	ग_लिखो INT3			अगर (desc)
	 */
	smp_rmb();

	desc = try_get_desc(&bp_desc);
	अगर (!desc)
		वापस 0;

	/*
	 * Discount the INT3. See text_poke_bp_batch().
	 */
	ip = (व्योम *) regs->ip - INT3_INSN_SIZE;

	/*
	 * Skip the binary search अगर there is a single member in the vector.
	 */
	अगर (unlikely(desc->nr_entries > 1)) अणु
		tp = __अंतरभूत_द्वा_खोज(ip, desc->vec, desc->nr_entries,
				      माप(काष्ठा text_poke_loc),
				      patch_cmp);
		अगर (!tp)
			जाओ out_put;
	पूर्ण अन्यथा अणु
		tp = desc->vec;
		अगर (text_poke_addr(tp) != ip)
			जाओ out_put;
	पूर्ण

	len = text_opcode_size(tp->opcode);
	ip += len;

	चयन (tp->opcode) अणु
	हाल INT3_INSN_OPCODE:
		/*
		 * Someone poked an explicit INT3, they'll want to handle it,
		 * करो not consume.
		 */
		जाओ out_put;

	हाल RET_INSN_OPCODE:
		पूर्णांक3_emulate_ret(regs);
		अवरोध;

	हाल CALL_INSN_OPCODE:
		पूर्णांक3_emulate_call(regs, (दीर्घ)ip + tp->rel32);
		अवरोध;

	हाल JMP32_INSN_OPCODE:
	हाल JMP8_INSN_OPCODE:
		पूर्णांक3_emulate_jmp(regs, (दीर्घ)ip + tp->rel32);
		अवरोध;

	शेष:
		BUG();
	पूर्ण

	ret = 1;

out_put:
	put_desc(desc);
	वापस ret;
पूर्ण

#घोषणा TP_VEC_MAX (PAGE_SIZE / माप(काष्ठा text_poke_loc))
अटल काष्ठा text_poke_loc tp_vec[TP_VEC_MAX];
अटल पूर्णांक tp_vec_nr;

/**
 * text_poke_bp_batch() -- update inकाष्ठाions on live kernel on SMP
 * @tp:			vector of inकाष्ठाions to patch
 * @nr_entries:		number of entries in the vector
 *
 * Modअगरy multi-byte inकाष्ठाion by using पूर्णांक3 अवरोधpoपूर्णांक on SMP.
 * We completely aव्योम stop_machine() here, and achieve the
 * synchronization using पूर्णांक3 अवरोधpoपूर्णांक.
 *
 * The way it is करोne:
 *	- For each entry in the vector:
 *		- add a पूर्णांक3 trap to the address that will be patched
 *	- sync cores
 *	- For each entry in the vector:
 *		- update all but the first byte of the patched range
 *	- sync cores
 *	- For each entry in the vector:
 *		- replace the first byte (पूर्णांक3) by the first byte of
 *		  replacing opcode
 *	- sync cores
 */
अटल व्योम text_poke_bp_batch(काष्ठा text_poke_loc *tp, अचिन्हित पूर्णांक nr_entries)
अणु
	काष्ठा bp_patching_desc desc = अणु
		.vec = tp,
		.nr_entries = nr_entries,
		.refs = ATOMIC_INIT(1),
	पूर्ण;
	अचिन्हित अक्षर पूर्णांक3 = INT3_INSN_OPCODE;
	अचिन्हित पूर्णांक i;
	पूर्णांक करो_sync;

	lockdep_निश्चित_held(&text_mutex);

	smp_store_release(&bp_desc, &desc); /* rcu_assign_poपूर्णांकer */

	/*
	 * Corresponding पढ़ो barrier in पूर्णांक3 notअगरier क्रम making sure the
	 * nr_entries and handler are correctly ordered wrt. patching.
	 */
	smp_wmb();

	/*
	 * First step: add a पूर्णांक3 trap to the address that will be patched.
	 */
	क्रम (i = 0; i < nr_entries; i++) अणु
		tp[i].old = *(u8 *)text_poke_addr(&tp[i]);
		text_poke(text_poke_addr(&tp[i]), &पूर्णांक3, INT3_INSN_SIZE);
	पूर्ण

	text_poke_sync();

	/*
	 * Second step: update all but the first byte of the patched range.
	 */
	क्रम (करो_sync = 0, i = 0; i < nr_entries; i++) अणु
		u8 old[POKE_MAX_OPCODE_SIZE] = अणु tp[i].old, पूर्ण;
		पूर्णांक len = text_opcode_size(tp[i].opcode);

		अगर (len - INT3_INSN_SIZE > 0) अणु
			स_नकल(old + INT3_INSN_SIZE,
			       text_poke_addr(&tp[i]) + INT3_INSN_SIZE,
			       len - INT3_INSN_SIZE);
			text_poke(text_poke_addr(&tp[i]) + INT3_INSN_SIZE,
				  (स्थिर अक्षर *)tp[i].text + INT3_INSN_SIZE,
				  len - INT3_INSN_SIZE);
			करो_sync++;
		पूर्ण

		/*
		 * Emit a perf event to record the text poke, primarily to
		 * support Intel PT decoding which must walk the executable code
		 * to reस्थिरruct the trace. The flow up to here is:
		 *   - ग_लिखो INT3 byte
		 *   - IPI-SYNC
		 *   - ग_लिखो inकाष्ठाion tail
		 * At this poपूर्णांक the actual control flow will be through the
		 * INT3 and handler and not hit the old or new inकाष्ठाion.
		 * Intel PT outमाला_दो FUP/TIP packets क्रम the INT3, so the flow
		 * can still be decoded. Subsequently:
		 *   - emit RECORD_TEXT_POKE with the new inकाष्ठाion
		 *   - IPI-SYNC
		 *   - ग_लिखो first byte
		 *   - IPI-SYNC
		 * So beक्रमe the text poke event बारtamp, the decoder will see
		 * either the old inकाष्ठाion flow or FUP/TIP of INT3. After the
		 * text poke event बारtamp, the decoder will see either the
		 * new inकाष्ठाion flow or FUP/TIP of INT3. Thus decoders can
		 * use the बारtamp as the poपूर्णांक at which to modअगरy the
		 * executable code.
		 * The old inकाष्ठाion is recorded so that the event can be
		 * processed क्रमwards or backwards.
		 */
		perf_event_text_poke(text_poke_addr(&tp[i]), old, len,
				     tp[i].text, len);
	पूर्ण

	अगर (करो_sync) अणु
		/*
		 * According to Intel, this core syncing is very likely
		 * not necessary and we'd be safe even without it. But
		 * better safe than sorry (plus there's not only Intel).
		 */
		text_poke_sync();
	पूर्ण

	/*
	 * Third step: replace the first byte (पूर्णांक3) by the first byte of
	 * replacing opcode.
	 */
	क्रम (करो_sync = 0, i = 0; i < nr_entries; i++) अणु
		अगर (tp[i].text[0] == INT3_INSN_OPCODE)
			जारी;

		text_poke(text_poke_addr(&tp[i]), tp[i].text, INT3_INSN_SIZE);
		करो_sync++;
	पूर्ण

	अगर (करो_sync)
		text_poke_sync();

	/*
	 * Remove and synchronize_rcu(), except we have a very primitive
	 * refcount based completion.
	 */
	WRITE_ONCE(bp_desc, शून्य); /* RCU_INIT_POINTER */
	अगर (!atomic_dec_and_test(&desc.refs))
		atomic_cond_पढ़ो_acquire(&desc.refs, !VAL);
पूर्ण

अटल व्योम text_poke_loc_init(काष्ठा text_poke_loc *tp, व्योम *addr,
			       स्थिर व्योम *opcode, माप_प्रकार len, स्थिर व्योम *emulate)
अणु
	काष्ठा insn insn;
	पूर्णांक ret;

	स_नकल((व्योम *)tp->text, opcode, len);
	अगर (!emulate)
		emulate = opcode;

	ret = insn_decode_kernel(&insn, emulate);

	BUG_ON(ret < 0);
	BUG_ON(len != insn.length);

	tp->rel_addr = addr - (व्योम *)_stext;
	tp->opcode = insn.opcode.bytes[0];

	चयन (tp->opcode) अणु
	हाल INT3_INSN_OPCODE:
	हाल RET_INSN_OPCODE:
		अवरोध;

	हाल CALL_INSN_OPCODE:
	हाल JMP32_INSN_OPCODE:
	हाल JMP8_INSN_OPCODE:
		tp->rel32 = insn.immediate.value;
		अवरोध;

	शेष: /* assume NOP */
		चयन (len) अणु
		हाल 2: /* NOP2 -- emulate as JMP8+0 */
			BUG_ON(स_भेद(emulate, x86_nops[len], len));
			tp->opcode = JMP8_INSN_OPCODE;
			tp->rel32 = 0;
			अवरोध;

		हाल 5: /* NOP5 -- emulate as JMP32+0 */
			BUG_ON(स_भेद(emulate, x86_nops[len], len));
			tp->opcode = JMP32_INSN_OPCODE;
			tp->rel32 = 0;
			अवरोध;

		शेष: /* unknown inकाष्ठाion */
			BUG();
		पूर्ण
		अवरोध;
	पूर्ण
पूर्ण

/*
 * We hard rely on the tp_vec being ordered; ensure this is so by flushing
 * early अगर needed.
 */
अटल bool tp_order_fail(व्योम *addr)
अणु
	काष्ठा text_poke_loc *tp;

	अगर (!tp_vec_nr)
		वापस false;

	अगर (!addr) /* क्रमce */
		वापस true;

	tp = &tp_vec[tp_vec_nr - 1];
	अगर ((अचिन्हित दीर्घ)text_poke_addr(tp) > (अचिन्हित दीर्घ)addr)
		वापस true;

	वापस false;
पूर्ण

अटल व्योम text_poke_flush(व्योम *addr)
अणु
	अगर (tp_vec_nr == TP_VEC_MAX || tp_order_fail(addr)) अणु
		text_poke_bp_batch(tp_vec, tp_vec_nr);
		tp_vec_nr = 0;
	पूर्ण
पूर्ण

व्योम text_poke_finish(व्योम)
अणु
	text_poke_flush(शून्य);
पूर्ण

व्योम __ref text_poke_queue(व्योम *addr, स्थिर व्योम *opcode, माप_प्रकार len, स्थिर व्योम *emulate)
अणु
	काष्ठा text_poke_loc *tp;

	अगर (unlikely(प्रणाली_state == SYSTEM_BOOTING)) अणु
		text_poke_early(addr, opcode, len);
		वापस;
	पूर्ण

	text_poke_flush(addr);

	tp = &tp_vec[tp_vec_nr++];
	text_poke_loc_init(tp, addr, opcode, len, emulate);
पूर्ण

/**
 * text_poke_bp() -- update inकाष्ठाions on live kernel on SMP
 * @addr:	address to patch
 * @opcode:	opcode of new inकाष्ठाion
 * @len:	length to copy
 * @emulate:	inकाष्ठाion to be emulated
 *
 * Update a single inकाष्ठाion with the vector in the stack, aव्योमing
 * dynamically allocated memory. This function should be used when it is
 * not possible to allocate memory.
 */
व्योम __ref text_poke_bp(व्योम *addr, स्थिर व्योम *opcode, माप_प्रकार len, स्थिर व्योम *emulate)
अणु
	काष्ठा text_poke_loc tp;

	अगर (unlikely(प्रणाली_state == SYSTEM_BOOTING)) अणु
		text_poke_early(addr, opcode, len);
		वापस;
	पूर्ण

	text_poke_loc_init(&tp, addr, opcode, len, emulate);
	text_poke_bp_batch(&tp, 1);
पूर्ण
