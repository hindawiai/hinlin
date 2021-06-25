<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Mapping of DWARF debug रेजिस्टर numbers पूर्णांकo रेजिस्टर names.
 *
 * Copyright (C) 2010 Will Deacon, ARM Ltd.
 */

#समावेश <त्रुटिसं.स>
#समावेश <मानकघोष.स>
#समावेश <माला.स>
#समावेश <dwarf-regs.h>
#समावेश <linux/ptrace.h> /* क्रम काष्ठा user_pt_regs */
#समावेश <linux/stringअगरy.h>

काष्ठा pt_regs_dwarfnum अणु
	स्थिर अक्षर *name;
	अचिन्हित पूर्णांक dwarfnum;
पूर्ण;

#घोषणा REG_DWARFNUM_NAME(r, num) अणु.name = r, .dwarfnum = numपूर्ण
#घोषणा GPR_DWARFNUM_NAME(num) \
	अणु.name = __stringअगरy(%x##num), .dwarfnum = numपूर्ण
#घोषणा REG_DWARFNUM_END अणु.name = शून्य, .dwarfnum = 0पूर्ण
#घोषणा DWARFNUM2OFFSET(index) \
	(index * माप((काष्ठा user_pt_regs *)0)->regs[0])

/*
 * Reference:
 * http://infocenter.arm.com/help/topic/com.arm.करोc.ihi0057b/IHI0057B_aadwarf64.pdf
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
	REG_DWARFNUM_NAME("%lr", 30),
	REG_DWARFNUM_NAME("%sp", 31),
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
			वापस DWARFNUM2OFFSET(roff->dwarfnum);
	वापस -EINVAL;
पूर्ण
