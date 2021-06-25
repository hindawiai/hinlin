<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/ptrace.h>

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

/**
 * regs_query_रेजिस्टर_name() - query रेजिस्टर name from its offset
 * @offset:	the offset of a रेजिस्टर in काष्ठा pt_regs.
 *
 * regs_query_रेजिस्टर_name() वापसs the name of a रेजिस्टर from its
 * offset in काष्ठा pt_regs. If the @offset is invalid, this वापसs शून्य;
 */
स्थिर अक्षर *regs_query_रेजिस्टर_name(अचिन्हित पूर्णांक offset)
अणु
	स्थिर काष्ठा pt_regs_offset *roff;
	क्रम (roff = regoffset_table; roff->name != शून्य; roff++)
		अगर (roff->offset == offset)
			वापस roff->name;
	वापस शून्य;
पूर्ण
