<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_BUG_H
#घोषणा _LINUX_BUG_H

#समावेश <यंत्र/bug.h>
#समावेश <linux/compiler.h>
#समावेश <linux/build_bug.h>

क्रमागत bug_trap_type अणु
	BUG_TRAP_TYPE_NONE = 0,
	BUG_TRAP_TYPE_WARN = 1,
	BUG_TRAP_TYPE_BUG = 2,
पूर्ण;

काष्ठा pt_regs;

#अगर_घोषित __CHECKER__
#घोषणा MAYBE_BUILD_BUG_ON(cond) (0)
#अन्यथा /* __CHECKER__ */

#घोषणा MAYBE_BUILD_BUG_ON(cond)			\
	करो अणु						\
		अगर (__builtin_स्थिरant_p((cond)))       \
			BUILD_BUG_ON(cond);             \
		अन्यथा                                    \
			BUG_ON(cond);                   \
	पूर्ण जबतक (0)

#पूर्ण_अगर	/* __CHECKER__ */

#अगर_घोषित CONFIG_GENERIC_BUG
#समावेश <यंत्र-generic/bug.h>

अटल अंतरभूत पूर्णांक is_warning_bug(स्थिर काष्ठा bug_entry *bug)
अणु
	वापस bug->flags & BUGFLAG_WARNING;
पूर्ण

व्योम bug_get_file_line(काष्ठा bug_entry *bug, स्थिर अक्षर **file,
		       अचिन्हित पूर्णांक *line);

काष्ठा bug_entry *find_bug(अचिन्हित दीर्घ bugaddr);

क्रमागत bug_trap_type report_bug(अचिन्हित दीर्घ bug_addr, काष्ठा pt_regs *regs);

/* These are defined by the architecture */
पूर्णांक is_valid_bugaddr(अचिन्हित दीर्घ addr);

व्योम generic_bug_clear_once(व्योम);

#अन्यथा	/* !CONFIG_GENERIC_BUG */

अटल अंतरभूत व्योम *find_bug(अचिन्हित दीर्घ bugaddr)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत क्रमागत bug_trap_type report_bug(अचिन्हित दीर्घ bug_addr,
					    काष्ठा pt_regs *regs)
अणु
	वापस BUG_TRAP_TYPE_BUG;
पूर्ण

काष्ठा bug_entry;
अटल अंतरभूत व्योम bug_get_file_line(काष्ठा bug_entry *bug, स्थिर अक्षर **file,
				     अचिन्हित पूर्णांक *line)
अणु
	*file = शून्य;
	*line = 0;
पूर्ण

अटल अंतरभूत व्योम generic_bug_clear_once(व्योम) अणुपूर्ण

#पूर्ण_अगर	/* CONFIG_GENERIC_BUG */

/*
 * Since detected data corruption should stop operation on the affected
 * काष्ठाures. Return value must be checked and sanely acted on by caller.
 */
अटल अंतरभूत __must_check bool check_data_corruption(bool v) अणु वापस v; पूर्ण
#घोषणा CHECK_DATA_CORRUPTION(condition, fmt, ...)			 \
	check_data_corruption((अणु					 \
		bool corruption = unlikely(condition);			 \
		अगर (corruption) अणु					 \
			अगर (IS_ENABLED(CONFIG_BUG_ON_DATA_CORRUPTION)) अणु \
				pr_err(fmt, ##__VA_ARGS__);		 \
				BUG();					 \
			पूर्ण अन्यथा						 \
				WARN(1, fmt, ##__VA_ARGS__);		 \
		पूर्ण							 \
		corruption;						 \
	पूर्ण))

#पूर्ण_अगर	/* _LINUX_BUG_H */
