<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * dwarf-regs.c : Mapping of DWARF debug रेजिस्टर numbers पूर्णांकo रेजिस्टर names.
 * Extracted from probe-finder.c
 *
 * Written by Masami Hiramatsu <mhiramat@redhat.com>
 */

#समावेश <मानकघोष.स>
#समावेश <त्रुटिसं.स> /* क्रम EINVAL */
#समावेश <माला.स> /* क्रम म_भेद */
#समावेश <linux/ptrace.h> /* क्रम काष्ठा pt_regs */
#समावेश <linux/kernel.h> /* क्रम दुरत्व */
#समावेश <dwarf-regs.h>

/*
 * See arch/x86/kernel/ptrace.c.
 * Dअगरferent from it:
 *
 *  - Since काष्ठा pt_regs is defined dअगरferently क्रम user and kernel,
 *    but we want to use 'ax, bx' instead of 'rax, rbx' (which is काष्ठा
 *    field name of user's pt_regs), we make REG_OFFSET_NAME to accept
 *    both string name and reg field name.
 *
 *  - Since accessing x86_32's pt_regs from x86_64 building is dअगरficult
 *    and vise versa, we simply fill offset with -1, so
 *    get_arch_regstr() still works but regs_query_रेजिस्टर_offset()
 *    वापसs error.
 *    The only inconvenience caused by it now is that we are not allowed
 *    to generate BPF prologue क्रम a x86_64 kernel अगर perf is built क्रम
 *    x86_32. This is really a rare useहाल.
 *
 *  - Order is dअगरferent from kernel's ptrace.c क्रम get_arch_regstr(). Use
 *    the order defined by dwarf.
 */

काष्ठा pt_regs_offset अणु
	स्थिर अक्षर *name;
	पूर्णांक offset;
पूर्ण;

#घोषणा REG_OFFSET_END अणु.name = शून्य, .offset = 0पूर्ण

#अगर_घोषित __x86_64__
# define REG_OFFSET_NAME_64(n, r) अणु.name = n, .offset = दुरत्व(काष्ठा pt_regs, r)पूर्ण
# define REG_OFFSET_NAME_32(n, r) अणु.name = n, .offset = -1पूर्ण
#अन्यथा
# define REG_OFFSET_NAME_64(n, r) अणु.name = n, .offset = -1पूर्ण
# define REG_OFFSET_NAME_32(n, r) अणु.name = n, .offset = दुरत्व(काष्ठा pt_regs, r)पूर्ण
#पूर्ण_अगर

/* TODO: चयनing by dwarf address size */
#अगर_अघोषित __x86_64__
अटल स्थिर काष्ठा pt_regs_offset x86_32_regoffset_table[] = अणु
	REG_OFFSET_NAME_32("%ax",	eax),
	REG_OFFSET_NAME_32("%cx",	ecx),
	REG_OFFSET_NAME_32("%dx",	edx),
	REG_OFFSET_NAME_32("%bx",	ebx),
	REG_OFFSET_NAME_32("$stack",	esp),	/* Stack address instead of %sp */
	REG_OFFSET_NAME_32("%bp",	ebp),
	REG_OFFSET_NAME_32("%si",	esi),
	REG_OFFSET_NAME_32("%di",	edi),
	REG_OFFSET_END,
पूर्ण;

#घोषणा regoffset_table x86_32_regoffset_table
#अन्यथा
अटल स्थिर काष्ठा pt_regs_offset x86_64_regoffset_table[] = अणु
	REG_OFFSET_NAME_64("%ax",	rax),
	REG_OFFSET_NAME_64("%dx",	rdx),
	REG_OFFSET_NAME_64("%cx",	rcx),
	REG_OFFSET_NAME_64("%bx",	rbx),
	REG_OFFSET_NAME_64("%si",	rsi),
	REG_OFFSET_NAME_64("%di",	rdi),
	REG_OFFSET_NAME_64("%bp",	rbp),
	REG_OFFSET_NAME_64("%sp",	rsp),
	REG_OFFSET_NAME_64("%r8",	r8),
	REG_OFFSET_NAME_64("%r9",	r9),
	REG_OFFSET_NAME_64("%r10",	r10),
	REG_OFFSET_NAME_64("%r11",	r11),
	REG_OFFSET_NAME_64("%r12",	r12),
	REG_OFFSET_NAME_64("%r13",	r13),
	REG_OFFSET_NAME_64("%r14",	r14),
	REG_OFFSET_NAME_64("%r15",	r15),
	REG_OFFSET_END,
पूर्ण;

#घोषणा regoffset_table x86_64_regoffset_table
#पूर्ण_अगर

/* Minus 1 क्रम the ending REG_OFFSET_END */
#घोषणा ARCH_MAX_REGS ((माप(regoffset_table) / माप(regoffset_table[0])) - 1)

/* Return architecture dependent रेजिस्टर string (क्रम kprobe-tracer) */
स्थिर अक्षर *get_arch_regstr(अचिन्हित पूर्णांक n)
अणु
	वापस (n < ARCH_MAX_REGS) ? regoffset_table[n].name : शून्य;
पूर्ण

/* Reuse code from arch/x86/kernel/ptrace.c */
/**
 * regs_query_रेजिस्टर_offset() - query रेजिस्टर offset from its name
 * @name:	the name of a रेजिस्टर
 *
 * regs_query_रेजिस्टर_offset() वापसs the offset of a रेजिस्टर in काष्ठा
 * pt_regs from its name. If the name is invalid, this वापसs -EINVAL;
 */
पूर्णांक regs_query_रेजिस्टर_offset(स्थिर अक्षर *name)
अणु
	स्थिर काष्ठा pt_regs_offset *roff;
	क्रम (roff = regoffset_table; roff->name != शून्य; roff++)
		अगर (!म_भेद(roff->name, name))
			वापस roff->offset;
	वापस -EINVAL;
पूर्ण
