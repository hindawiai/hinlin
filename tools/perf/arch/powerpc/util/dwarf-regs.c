<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Mapping of DWARF debug रेजिस्टर numbers पूर्णांकo रेजिस्टर names.
 *
 * Copyright (C) 2010 Ian Munsie, IBM Corporation.
 */

#समावेश <मानकघोष.स>
#समावेश <त्रुटिसं.स>
#समावेश <माला.स>
#समावेश <dwarf-regs.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/kernel.h>
#समावेश <linux/stringअगरy.h>

काष्ठा pt_regs_dwarfnum अणु
	स्थिर अक्षर *name;
	अचिन्हित पूर्णांक dwarfnum;
	अचिन्हित पूर्णांक ptregs_offset;
पूर्ण;

#घोषणा REG_DWARFNUM_NAME(r, num)					\
		अणु.name = __stringअगरy(%)__stringअगरy(r), .dwarfnum = num,			\
		.ptregs_offset = दुरत्व(काष्ठा pt_regs, r)पूर्ण
#घोषणा GPR_DWARFNUM_NAME(num)						\
		अणु.name = __stringअगरy(%gpr##num), .dwarfnum = num,		\
		.ptregs_offset = दुरत्व(काष्ठा pt_regs, gpr[num])पूर्ण
#घोषणा REG_DWARFNUM_END अणु.name = शून्य, .dwarfnum = 0, .ptregs_offset = 0पूर्ण

/*
 * Reference:
 * http://refspecs.linuxfoundation.org/ELF/ppc64/PPC-elf64abi-1.9.hपंचांगl
 */
अटल स्थिर काष्ठा pt_regs_dwarfnum regdwarfnum_table[] = अणु
	GPR_DWARFNUM_NAME(0),
	GPR_DWARFNUM_NAME(1),
	GPR_DWARFNUM_NAME(2),
	GPR_DWARFNUM_NAME(3),
	GPR_DWARFNUM_NAME(4),
	GPR_DWARFNUM_NAME(5),
	GPR_DWARFNUM_NAME(6),
	GPR_DWARFNUM_NAME(7),
	GPR_DWARFNUM_NAME(8),
	GPR_DWARFNUM_NAME(9),
	GPR_DWARFNUM_NAME(10),
	GPR_DWARFNUM_NAME(11),
	GPR_DWARFNUM_NAME(12),
	GPR_DWARFNUM_NAME(13),
	GPR_DWARFNUM_NAME(14),
	GPR_DWARFNUM_NAME(15),
	GPR_DWARFNUM_NAME(16),
	GPR_DWARFNUM_NAME(17),
	GPR_DWARFNUM_NAME(18),
	GPR_DWARFNUM_NAME(19),
	GPR_DWARFNUM_NAME(20),
	GPR_DWARFNUM_NAME(21),
	GPR_DWARFNUM_NAME(22),
	GPR_DWARFNUM_NAME(23),
	GPR_DWARFNUM_NAME(24),
	GPR_DWARFNUM_NAME(25),
	GPR_DWARFNUM_NAME(26),
	GPR_DWARFNUM_NAME(27),
	GPR_DWARFNUM_NAME(28),
	GPR_DWARFNUM_NAME(29),
	GPR_DWARFNUM_NAME(30),
	GPR_DWARFNUM_NAME(31),
	REG_DWARFNUM_NAME(msr,   66),
	REG_DWARFNUM_NAME(ctr,   109),
	REG_DWARFNUM_NAME(link,  108),
	REG_DWARFNUM_NAME(xer,   101),
	REG_DWARFNUM_NAME(dar,   119),
	REG_DWARFNUM_NAME(dsisr, 118),
	REG_DWARFNUM_END,
पूर्ण;

/**
 * get_arch_regstr() - lookup रेजिस्टर name from it's DWARF रेजिस्टर number
 * @n:	the DWARF रेजिस्टर number
 *
 * get_arch_regstr() वापसs the name of the रेजिस्टर in काष्ठा
 * regdwarfnum_table from it's DWARF रेजिस्टर number. If the रेजिस्टर is not
 * found in the table, this वापसs शून्य;
 */
स्थिर अक्षर *get_arch_regstr(अचिन्हित पूर्णांक n)
अणु
	स्थिर काष्ठा pt_regs_dwarfnum *roff;
	क्रम (roff = regdwarfnum_table; roff->name != शून्य; roff++)
		अगर (roff->dwarfnum == n)
			वापस roff->name;
	वापस शून्य;
पूर्ण

पूर्णांक regs_query_रेजिस्टर_offset(स्थिर अक्षर *name)
अणु
	स्थिर काष्ठा pt_regs_dwarfnum *roff;
	क्रम (roff = regdwarfnum_table; roff->name != शून्य; roff++)
		अगर (!म_भेद(roff->name, name))
			वापस roff->ptregs_offset;
	वापस -EINVAL;
पूर्ण
