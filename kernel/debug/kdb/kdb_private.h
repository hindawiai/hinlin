<शैली गुरु>
#अगर_अघोषित _KDBPRIVATE_H
#घोषणा _KDBPRIVATE_H

/*
 * Kernel Debugger Architecture Independent Private Headers
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (c) 2000-2004 Silicon Graphics, Inc.  All Rights Reserved.
 * Copyright (c) 2009 Wind River Systems, Inc.  All Rights Reserved.
 */

#समावेश <linux/kgdb.h>
#समावेश "../debug_core.h"

/* Kernel Debugger Command codes.  Must not overlap with error codes. */
#घोषणा KDB_CMD_GO	(-1001)
#घोषणा KDB_CMD_CPU	(-1002)
#घोषणा KDB_CMD_SS	(-1003)
#घोषणा KDB_CMD_KGDB (-1005)

/* Internal debug flags */
#घोषणा KDB_DEBUG_FLAG_BP	0x0002	/* Breakpoपूर्णांक subप्रणाली debug */
#घोषणा KDB_DEBUG_FLAG_BB_SUMM	0x0004	/* Basic block analysis, summary only */
#घोषणा KDB_DEBUG_FLAG_AR	0x0008	/* Activation record, generic */
#घोषणा KDB_DEBUG_FLAG_ARA	0x0010	/* Activation record, arch specअगरic */
#घोषणा KDB_DEBUG_FLAG_BB	0x0020	/* All basic block analysis */
#घोषणा KDB_DEBUG_FLAG_STATE	0x0040	/* State flags */
#घोषणा KDB_DEBUG_FLAG_MASK	0xffff	/* All debug flags */
#घोषणा KDB_DEBUG_FLAG_SHIFT	16	/* Shअगरt factor क्रम dbflags */

#घोषणा KDB_DEBUG(flag)	(kdb_flags & \
	(KDB_DEBUG_FLAG_##flag << KDB_DEBUG_FLAG_SHIFT))
#घोषणा KDB_DEBUG_STATE(text, value) अगर (KDB_DEBUG(STATE)) \
		kdb_prपूर्णांक_state(text, value)

#अगर BITS_PER_LONG == 32

#घोषणा KDB_PLATFORM_ENV	"BYTESPERWORD=4"

#घोषणा kdb_machreg_fmt		"0x%lx"
#घोषणा kdb_machreg_fmt0	"0x%08lx"
#घोषणा kdb_bfd_vma_fmt		"0x%lx"
#घोषणा kdb_bfd_vma_fmt0	"0x%08lx"
#घोषणा kdb_elfw_addr_fmt	"0x%x"
#घोषणा kdb_elfw_addr_fmt0	"0x%08x"
#घोषणा kdb_f_count_fmt		"%d"

#या_अगर BITS_PER_LONG == 64

#घोषणा KDB_PLATFORM_ENV	"BYTESPERWORD=8"

#घोषणा kdb_machreg_fmt		"0x%lx"
#घोषणा kdb_machreg_fmt0	"0x%016lx"
#घोषणा kdb_bfd_vma_fmt		"0x%lx"
#घोषणा kdb_bfd_vma_fmt0	"0x%016lx"
#घोषणा kdb_elfw_addr_fmt	"0x%x"
#घोषणा kdb_elfw_addr_fmt0	"0x%016x"
#घोषणा kdb_f_count_fmt		"%ld"

#पूर्ण_अगर

/*
 * KDB_MAXBPT describes the total number of अवरोधpoपूर्णांकs
 * supported by this architecure.
 */
#घोषणा KDB_MAXBPT	16

/* Symbol table क्रमmat वापसed by kallsyms. */
प्रकार काष्ठा __ksymtab अणु
		अचिन्हित दीर्घ value;	/* Address of symbol */
		स्थिर अक्षर *mod_name;	/* Module containing symbol or
					 * "kernel" */
		अचिन्हित दीर्घ mod_start;
		अचिन्हित दीर्घ mod_end;
		स्थिर अक्षर *sec_name;	/* Section containing symbol */
		अचिन्हित दीर्घ sec_start;
		अचिन्हित दीर्घ sec_end;
		स्थिर अक्षर *sym_name;	/* Full symbol name, including
					 * any version */
		अचिन्हित दीर्घ sym_start;
		अचिन्हित दीर्घ sym_end;
		पूर्ण kdb_symtab_t;
बाह्य पूर्णांक kallsyms_symbol_next(अक्षर *prefix_name, पूर्णांक flag, पूर्णांक buf_size);
बाह्य पूर्णांक kallsyms_symbol_complete(अक्षर *prefix_name, पूर्णांक max_len);

/* Exported Symbols क्रम kernel loadable modules to use. */
बाह्य पूर्णांक kdb_getarea_size(व्योम *, अचिन्हित दीर्घ, माप_प्रकार);
बाह्य पूर्णांक kdb_putarea_size(अचिन्हित दीर्घ, व्योम *, माप_प्रकार);

/*
 * Like get_user and put_user, kdb_getarea and kdb_putarea take variable
 * names, not poपूर्णांकers.  The underlying *_size functions take poपूर्णांकers.
 */
#घोषणा kdb_getarea(x, addr) kdb_getarea_size(&(x), addr, माप((x)))
#घोषणा kdb_putarea(addr, x) kdb_putarea_size(addr, &(x), माप((x)))

बाह्य पूर्णांक kdb_getphysword(अचिन्हित दीर्घ *word,
			अचिन्हित दीर्घ addr, माप_प्रकार size);
बाह्य पूर्णांक kdb_getword(अचिन्हित दीर्घ *, अचिन्हित दीर्घ, माप_प्रकार);
बाह्य पूर्णांक kdb_putword(अचिन्हित दीर्घ, अचिन्हित दीर्घ, माप_प्रकार);

बाह्य पूर्णांक kdbgetularg(स्थिर अक्षर *, अचिन्हित दीर्घ *);
बाह्य पूर्णांक kdbgetu64arg(स्थिर अक्षर *, u64 *);
बाह्य अक्षर *kdbदो_पर्या(स्थिर अक्षर *);
बाह्य पूर्णांक kdbgetaddrarg(पूर्णांक, स्थिर अक्षर **, पूर्णांक*, अचिन्हित दीर्घ *,
			 दीर्घ *, अक्षर **);
बाह्य पूर्णांक kdbमाला_लोymval(स्थिर अक्षर *, kdb_symtab_t *);
बाह्य पूर्णांक kdbnearsym(अचिन्हित दीर्घ, kdb_symtab_t *);
बाह्य व्योम kdbnearsym_cleanup(व्योम);
बाह्य अक्षर *kdb_strdup(स्थिर अक्षर *str, gfp_t type);
बाह्य व्योम kdb_symbol_prपूर्णांक(अचिन्हित दीर्घ, स्थिर kdb_symtab_t *, अचिन्हित पूर्णांक);

/* Routine क्रम debugging the debugger state. */
बाह्य व्योम kdb_prपूर्णांक_state(स्थिर अक्षर *, पूर्णांक);

बाह्य पूर्णांक kdb_state;
#घोषणा KDB_STATE_KDB		0x00000001	/* Cpu is inside kdb */
#घोषणा KDB_STATE_LEAVING	0x00000002	/* Cpu is leaving kdb */
#घोषणा KDB_STATE_CMD		0x00000004	/* Running a kdb command */
#घोषणा KDB_STATE_KDB_CONTROL	0x00000008	/* This cpu is under
						 * kdb control */
#घोषणा KDB_STATE_HOLD_CPU	0x00000010	/* Hold this cpu inside kdb */
#घोषणा KDB_STATE_DOING_SS	0x00000020	/* Doing ss command */
#घोषणा KDB_STATE_SSBPT		0x00000080	/* Install अवरोधpoपूर्णांक
						 * after one ss, independent of
						 * DOING_SS */
#घोषणा KDB_STATE_REENTRY	0x00000100	/* Valid re-entry पूर्णांकo kdb */
#घोषणा KDB_STATE_SUPPRESS	0x00000200	/* Suppress error messages */
#घोषणा KDB_STATE_PAGER		0x00000400	/* pager is available */
#घोषणा KDB_STATE_GO_SWITCH	0x00000800	/* go is चयनing
						 * back to initial cpu */
#घोषणा KDB_STATE_WAIT_IPI	0x00002000	/* Waiting क्रम kdb_ipi() NMI */
#घोषणा KDB_STATE_RECURSE	0x00004000	/* Recursive entry to kdb */
#घोषणा KDB_STATE_IP_ADJUSTED	0x00008000	/* Restart IP has been
						 * adjusted */
#घोषणा KDB_STATE_GO1		0x00010000	/* go only releases one cpu */
#घोषणा KDB_STATE_KEYBOARD	0x00020000	/* kdb entered via
						 * keyboard on this cpu */
#घोषणा KDB_STATE_KEXEC		0x00040000	/* kexec issued */
#घोषणा KDB_STATE_DOING_KGDB	0x00080000	/* kgdb enter now issued */
#घोषणा KDB_STATE_KGDB_TRANS	0x00200000	/* Transition to kgdb */
#घोषणा KDB_STATE_ARCH		0xff000000	/* Reserved क्रम arch
						 * specअगरic use */

#घोषणा KDB_STATE(flag) (kdb_state & KDB_STATE_##flag)
#घोषणा KDB_STATE_SET(flag) ((व्योम)(kdb_state |= KDB_STATE_##flag))
#घोषणा KDB_STATE_CLEAR(flag) ((व्योम)(kdb_state &= ~KDB_STATE_##flag))

बाह्य पूर्णांक kdb_nextline; /* Current number of lines displayed */

प्रकार काष्ठा _kdb_bp अणु
	अचिन्हित दीर्घ	bp_addr;	/* Address अवरोधpoपूर्णांक is present at */
	अचिन्हित पूर्णांक	bp_मुक्त:1;	/* This entry is available */
	अचिन्हित पूर्णांक	bp_enabled:1;	/* Breakpoपूर्णांक is active in रेजिस्टर */
	अचिन्हित पूर्णांक	bp_type:4;	/* Uses hardware रेजिस्टर */
	अचिन्हित पूर्णांक	bp_installed:1;	/* Breakpoपूर्णांक is installed */
	अचिन्हित पूर्णांक	bp_delay:1;	/* Do delayed bp handling */
	अचिन्हित पूर्णांक	bp_delayed:1;	/* Delayed अवरोधpoपूर्णांक */
	अचिन्हित पूर्णांक	bph_length;	/* HW अवरोध length */
पूर्ण kdb_bp_t;

#अगर_घोषित CONFIG_KGDB_KDB
बाह्य kdb_bp_t kdb_अवरोधpoपूर्णांकs[/* KDB_MAXBPT */];

/* The KDB shell command table */
प्रकार काष्ठा _kdbtab अणु
	अक्षर    *cmd_name;		/* Command name */
	kdb_func_t cmd_func;		/* Function to execute command */
	अक्षर    *cmd_usage;		/* Usage String क्रम this command */
	अक्षर    *cmd_help;		/* Help message क्रम this command */
	लघु    cmd_minlen;		/* Minimum legal # command
					 * अक्षरs required */
	kdb_cmdflags_t cmd_flags;	/* Command behaviour flags */
	काष्ठा list_head list_node;	/* Command list */
	bool    is_dynamic;		/* Command table allocation type */
पूर्ण kdbtab_t;

बाह्य व्योम kdb_रेजिस्टर_table(kdbtab_t *kp, माप_प्रकार len);
बाह्य पूर्णांक kdb_bt(पूर्णांक, स्थिर अक्षर **);	/* KDB display back trace */

/* KDB अवरोधpoपूर्णांक management functions */
बाह्य व्योम kdb_initbptab(व्योम);
बाह्य व्योम kdb_bp_install(काष्ठा pt_regs *);
बाह्य व्योम kdb_bp_हटाओ(व्योम);

प्रकार क्रमागत अणु
	KDB_DB_BPT,	/* Breakpoपूर्णांक */
	KDB_DB_SS,	/* Single-step trap */
	KDB_DB_SSBPT,	/* Single step over अवरोधpoपूर्णांक */
	KDB_DB_NOBPT	/* Spurious अवरोधpoपूर्णांक */
पूर्ण kdb_dbtrap_t;

बाह्य पूर्णांक kdb_मुख्य_loop(kdb_reason_t, kdb_reason_t,
			 पूर्णांक, kdb_dbtrap_t, काष्ठा pt_regs *);

/* Miscellaneous functions and data areas */
बाह्य पूर्णांक kdb_grepping_flag;
#घोषणा KDB_GREPPING_FLAG_SEARCH 0x8000
बाह्य अक्षर kdb_grep_string[];
#घोषणा KDB_GREP_STRLEN 256
बाह्य पूर्णांक kdb_grep_leading;
बाह्य पूर्णांक kdb_grep_trailing;
बाह्य अक्षर *kdb_cmds[];
बाह्य अचिन्हित दीर्घ kdb_task_state_string(स्थिर अक्षर *);
बाह्य अक्षर kdb_task_state_अक्षर (स्थिर काष्ठा task_काष्ठा *);
बाह्य अचिन्हित दीर्घ kdb_task_state(स्थिर काष्ठा task_काष्ठा *p,
				    अचिन्हित दीर्घ mask);
बाह्य व्योम kdb_ps_suppressed(व्योम);
बाह्य व्योम kdb_ps1(स्थिर काष्ठा task_काष्ठा *p);
बाह्य व्योम kdb_send_sig(काष्ठा task_काष्ठा *p, पूर्णांक sig);
बाह्य अक्षर kdb_अक्षर_लो(व्योम);
बाह्य अक्षर *kdb_माला_लोtr(अक्षर *, माप_प्रकार, स्थिर अक्षर *);
बाह्य व्योम kdb_gdb_state_pass(अक्षर *buf);

/* Defines क्रम kdb_symbol_prपूर्णांक */
#घोषणा KDB_SP_SPACEB	0x0001		/* Space beक्रमe string */
#घोषणा KDB_SP_SPACEA	0x0002		/* Space after string */
#घोषणा KDB_SP_PAREN	0x0004		/* Parenthesis around string */
#घोषणा KDB_SP_VALUE	0x0008		/* Prपूर्णांक the value of the address */
#घोषणा KDB_SP_SYMSIZE	0x0010		/* Prपूर्णांक the size of the symbol */
#घोषणा KDB_SP_NEWLINE	0x0020		/* Newline after string */
#घोषणा KDB_SP_DEFAULT (KDB_SP_VALUE|KDB_SP_PAREN)

#घोषणा KDB_TSK(cpu) kgdb_info[cpu].task
#घोषणा KDB_TSKREGS(cpu) kgdb_info[cpu].debuggerinfo

बाह्य काष्ठा task_काष्ठा *kdb_curr_task(पूर्णांक);

#घोषणा kdb_task_has_cpu(p) (task_curr(p))

#घोषणा GFP_KDB (in_dbg_master() ? GFP_ATOMIC : GFP_KERNEL)

बाह्य व्योम *debug_kदो_स्मृति(माप_प्रकार size, gfp_t flags);
बाह्य व्योम debug_kमुक्त(व्योम *);
बाह्य व्योम debug_kusage(व्योम);

बाह्य काष्ठा task_काष्ठा *kdb_current_task;
बाह्य काष्ठा pt_regs *kdb_current_regs;

#अगर_घोषित CONFIG_KDB_KEYBOARD
बाह्य व्योम kdb_kbd_cleanup_state(व्योम);
#अन्यथा /* ! CONFIG_KDB_KEYBOARD */
#घोषणा kdb_kbd_cleanup_state()
#पूर्ण_अगर /* ! CONFIG_KDB_KEYBOARD */

#अगर_घोषित CONFIG_MODULES
बाह्य काष्ठा list_head *kdb_modules;
#पूर्ण_अगर /* CONFIG_MODULES */

बाह्य अक्षर kdb_prompt_str[];

#घोषणा	KDB_WORD_SIZE	((पूर्णांक)माप(अचिन्हित दीर्घ))

#पूर्ण_अगर /* CONFIG_KGDB_KDB */

#घोषणा kdb_func_म_लिखो(क्रमmat, args...) \
	kdb_म_लिखो("%s: " क्रमmat, __func__, ## args)

#घोषणा kdb_dbg_म_लिखो(mask, क्रमmat, args...) \
	करो अणु \
		अगर (KDB_DEBUG(mask)) \
			kdb_func_म_लिखो(क्रमmat, ## args); \
	पूर्ण जबतक (0)

#पूर्ण_अगर	/* !_KDBPRIVATE_H */
