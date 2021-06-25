<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
  Generic support क्रम BUG()

  This respects the following config options:

  CONFIG_BUG - emit BUG traps.  Nothing happens without this.
  CONFIG_GENERIC_BUG - enable this code.
  CONFIG_GENERIC_BUG_RELATIVE_POINTERS - use 32-bit poपूर्णांकers relative to
	the containing काष्ठा bug_entry क्रम bug_addr and file.
  CONFIG_DEBUG_BUGVERBOSE - emit full file+line inक्रमmation क्रम each BUG

  CONFIG_BUG and CONFIG_DEBUG_BUGVERBOSE are potentially user-settable
  (though they're generally always on).

  CONFIG_GENERIC_BUG is set by each architecture using this code.

  To use this, your architecture must:

  1. Set up the config options:
     - Enable CONFIG_GENERIC_BUG अगर CONFIG_BUG

  2. Implement BUG (and optionally BUG_ON, WARN, WARN_ON)
     - Define HAVE_ARCH_BUG
     - Implement BUG() to generate a faulting inकाष्ठाion
     - NOTE: काष्ठा bug_entry करोes not have "file" or "line" entries
       when CONFIG_DEBUG_BUGVERBOSE is not enabled, so you must generate
       the values accordingly.

  3. Implement the trap
     - In the illegal inकाष्ठाion trap handler (typically), verअगरy
       that the fault was in kernel mode, and call report_bug()
     - report_bug() will वापस whether it was a false alarm, a warning,
       or an actual bug.
     - You must implement the is_valid_bugaddr(bugaddr) callback which
       वापसs true अगर the eip is a real kernel address, and it poपूर्णांकs
       to the expected BUG trap inकाष्ठाion.

    Jeremy Fitzhardinge <jeremy@goop.org> 2006
 */

#घोषणा pr_fmt(fmt) fmt

#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/bug.h>
#समावेश <linux/sched.h>
#समावेश <linux/rculist.h>
#समावेश <linux/ftrace.h>

बाह्य काष्ठा bug_entry __start___bug_table[], __stop___bug_table[];

अटल अंतरभूत अचिन्हित दीर्घ bug_addr(स्थिर काष्ठा bug_entry *bug)
अणु
#अगर_अघोषित CONFIG_GENERIC_BUG_RELATIVE_POINTERS
	वापस bug->bug_addr;
#अन्यथा
	वापस (अचिन्हित दीर्घ)bug + bug->bug_addr_disp;
#पूर्ण_अगर
पूर्ण

#अगर_घोषित CONFIG_MODULES
/* Updates are रक्षित by module mutex */
अटल LIST_HEAD(module_bug_list);

अटल काष्ठा bug_entry *module_find_bug(अचिन्हित दीर्घ bugaddr)
अणु
	काष्ठा module *mod;
	काष्ठा bug_entry *bug = शून्य;

	rcu_पढ़ो_lock_sched();
	list_क्रम_each_entry_rcu(mod, &module_bug_list, bug_list) अणु
		अचिन्हित i;

		bug = mod->bug_table;
		क्रम (i = 0; i < mod->num_bugs; ++i, ++bug)
			अगर (bugaddr == bug_addr(bug))
				जाओ out;
	पूर्ण
	bug = शून्य;
out:
	rcu_पढ़ो_unlock_sched();

	वापस bug;
पूर्ण

व्योम module_bug_finalize(स्थिर Elf_Ehdr *hdr, स्थिर Elf_Shdr *sechdrs,
			 काष्ठा module *mod)
अणु
	अक्षर *secstrings;
	अचिन्हित पूर्णांक i;

	mod->bug_table = शून्य;
	mod->num_bugs = 0;

	/* Find the __bug_table section, अगर present */
	secstrings = (अक्षर *)hdr + sechdrs[hdr->e_shstrndx].sh_offset;
	क्रम (i = 1; i < hdr->e_shnum; i++) अणु
		अगर (म_भेद(secstrings+sechdrs[i].sh_name, "__bug_table"))
			जारी;
		mod->bug_table = (व्योम *) sechdrs[i].sh_addr;
		mod->num_bugs = sechdrs[i].sh_size / माप(काष्ठा bug_entry);
		अवरोध;
	पूर्ण

	/*
	 * Strictly speaking this should have a spinlock to protect against
	 * traversals, but since we only traverse on BUG()s, a spinlock
	 * could potentially lead to deadlock and thus be counter-productive.
	 * Thus, this uses RCU to safely manipulate the bug list, since BUG
	 * must run in non-पूर्णांकerruptive state.
	 */
	list_add_rcu(&mod->bug_list, &module_bug_list);
पूर्ण

व्योम module_bug_cleanup(काष्ठा module *mod)
अणु
	list_del_rcu(&mod->bug_list);
पूर्ण

#अन्यथा

अटल अंतरभूत काष्ठा bug_entry *module_find_bug(अचिन्हित दीर्घ bugaddr)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

व्योम bug_get_file_line(काष्ठा bug_entry *bug, स्थिर अक्षर **file,
		       अचिन्हित पूर्णांक *line)
अणु
#अगर_घोषित CONFIG_DEBUG_BUGVERBOSE
#अगर_अघोषित CONFIG_GENERIC_BUG_RELATIVE_POINTERS
	*file = bug->file;
#अन्यथा
	*file = (स्थिर अक्षर *)bug + bug->file_disp;
#पूर्ण_अगर
	*line = bug->line;
#अन्यथा
	*file = शून्य;
	*line = 0;
#पूर्ण_अगर
पूर्ण

काष्ठा bug_entry *find_bug(अचिन्हित दीर्घ bugaddr)
अणु
	काष्ठा bug_entry *bug;

	क्रम (bug = __start___bug_table; bug < __stop___bug_table; ++bug)
		अगर (bugaddr == bug_addr(bug))
			वापस bug;

	वापस module_find_bug(bugaddr);
पूर्ण

क्रमागत bug_trap_type report_bug(अचिन्हित दीर्घ bugaddr, काष्ठा pt_regs *regs)
अणु
	काष्ठा bug_entry *bug;
	स्थिर अक्षर *file;
	अचिन्हित line, warning, once, करोne;

	अगर (!is_valid_bugaddr(bugaddr))
		वापस BUG_TRAP_TYPE_NONE;

	bug = find_bug(bugaddr);
	अगर (!bug)
		वापस BUG_TRAP_TYPE_NONE;

	disable_trace_on_warning();

	bug_get_file_line(bug, &file, &line);

	warning = (bug->flags & BUGFLAG_WARNING) != 0;
	once = (bug->flags & BUGFLAG_ONCE) != 0;
	करोne = (bug->flags & BUGFLAG_DONE) != 0;

	अगर (warning && once) अणु
		अगर (करोne)
			वापस BUG_TRAP_TYPE_WARN;

		/*
		 * Since this is the only store, concurrency is not an issue.
		 */
		bug->flags |= BUGFLAG_DONE;
	पूर्ण

	/*
	 * BUG() and WARN_ON() families करोn't prपूर्णांक a custom debug message
	 * beक्रमe triggering the exception handler, so we must add the
	 * "cut here" line now. WARN() issues its own "cut here" beक्रमe the
	 * extra debugging message it ग_लिखोs beक्रमe triggering the handler.
	 */
	अगर ((bug->flags & BUGFLAG_NO_CUT_HERE) == 0)
		prपूर्णांकk(KERN_DEFAULT CUT_HERE);

	अगर (warning) अणु
		/* this is a WARN_ON rather than BUG/BUG_ON */
		__warn(file, line, (व्योम *)bugaddr, BUG_GET_TAINT(bug), regs,
		       शून्य);
		वापस BUG_TRAP_TYPE_WARN;
	पूर्ण

	अगर (file)
		pr_crit("kernel BUG at %s:%u!\n", file, line);
	अन्यथा
		pr_crit("Kernel BUG at %pB [verbose debug info unavailable]\n",
			(व्योम *)bugaddr);

	वापस BUG_TRAP_TYPE_BUG;
पूर्ण

अटल व्योम clear_once_table(काष्ठा bug_entry *start, काष्ठा bug_entry *end)
अणु
	काष्ठा bug_entry *bug;

	क्रम (bug = start; bug < end; bug++)
		bug->flags &= ~BUGFLAG_DONE;
पूर्ण

व्योम generic_bug_clear_once(व्योम)
अणु
#अगर_घोषित CONFIG_MODULES
	काष्ठा module *mod;

	rcu_पढ़ो_lock_sched();
	list_क्रम_each_entry_rcu(mod, &module_bug_list, bug_list)
		clear_once_table(mod->bug_table,
				 mod->bug_table + mod->num_bugs);
	rcu_पढ़ो_unlock_sched();
#पूर्ण_अगर

	clear_once_table(__start___bug_table, __stop___bug_table);
पूर्ण
