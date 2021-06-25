<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __PERF_REGS_H
#घोषणा __PERF_REGS_H

#समावेश <linux/types.h>
#समावेश <linux/compiler.h>

काष्ठा regs_dump;

काष्ठा sample_reg अणु
	स्थिर अक्षर *name;
	uपूर्णांक64_t mask;
पूर्ण;
#घोषणा SMPL_REG(n, b) अणु .name = #n, .mask = 1ULL << (b) पूर्ण
#घोषणा SMPL_REG2(n, b) अणु .name = #n, .mask = 3ULL << (b) पूर्ण
#घोषणा SMPL_REG_END अणु .name = शून्य पूर्ण

क्रमागत अणु
	SDT_ARG_VALID = 0,
	SDT_ARG_SKIP,
पूर्ण;

पूर्णांक arch_sdt_arg_parse_op(अक्षर *old_op, अक्षर **new_op);
uपूर्णांक64_t arch__पूर्णांकr_reg_mask(व्योम);
uपूर्णांक64_t arch__user_reg_mask(व्योम);

#अगर_घोषित HAVE_PERF_REGS_SUPPORT
बाह्य स्थिर काष्ठा sample_reg sample_reg_masks[];

#समावेश <perf_regs.h>

#घोषणा DWARF_MINIMAL_REGS ((1ULL << PERF_REG_IP) | (1ULL << PERF_REG_SP))

पूर्णांक perf_reg_value(u64 *valp, काष्ठा regs_dump *regs, पूर्णांक id);

अटल अंतरभूत स्थिर अक्षर *perf_reg_name(पूर्णांक id)
अणु
	स्थिर अक्षर *reg_name = __perf_reg_name(id);

	वापस reg_name ?: "unknown";
पूर्ण

#अन्यथा
#घोषणा PERF_REGS_MASK	0
#घोषणा PERF_REGS_MAX	0

#घोषणा DWARF_MINIMAL_REGS PERF_REGS_MASK

अटल अंतरभूत स्थिर अक्षर *perf_reg_name(पूर्णांक id __maybe_unused)
अणु
	वापस "unknown";
पूर्ण

अटल अंतरभूत पूर्णांक perf_reg_value(u64 *valp __maybe_unused,
				 काष्ठा regs_dump *regs __maybe_unused,
				 पूर्णांक id __maybe_unused)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर /* HAVE_PERF_REGS_SUPPORT */
#पूर्ण_अगर /* __PERF_REGS_H */
