<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <त्रुटिसं.स>
#समावेश "perf_regs.h"
#समावेश "event.h"

पूर्णांक __weak arch_sdt_arg_parse_op(अक्षर *old_op __maybe_unused,
				 अक्षर **new_op __maybe_unused)
अणु
	वापस SDT_ARG_SKIP;
पूर्ण

uपूर्णांक64_t __weak arch__पूर्णांकr_reg_mask(व्योम)
अणु
	वापस PERF_REGS_MASK;
पूर्ण

uपूर्णांक64_t __weak arch__user_reg_mask(व्योम)
अणु
	वापस PERF_REGS_MASK;
पूर्ण

#अगर_घोषित HAVE_PERF_REGS_SUPPORT
पूर्णांक perf_reg_value(u64 *valp, काष्ठा regs_dump *regs, पूर्णांक id)
अणु
	पूर्णांक i, idx = 0;
	u64 mask = regs->mask;

	अगर (regs->cache_mask & (1ULL << id))
		जाओ out;

	अगर (!(mask & (1ULL << id)))
		वापस -EINVAL;

	क्रम (i = 0; i < id; i++) अणु
		अगर (mask & (1ULL << i))
			idx++;
	पूर्ण

	regs->cache_mask |= (1ULL << id);
	regs->cache_regs[id] = regs->regs[idx];

out:
	*valp = regs->cache_regs[id];
	वापस 0;
पूर्ण
#पूर्ण_अगर
