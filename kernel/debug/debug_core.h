<शैली गुरु>
/*
 * Created by: Jason Wessel <jason.wessel@windriver.com>
 *
 * Copyright (c) 2009 Wind River Systems, Inc.  All Rights Reserved.
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#अगर_अघोषित _DEBUG_CORE_H_
#घोषणा _DEBUG_CORE_H_
/*
 * These are the निजी implementation headers between the kernel
 * debugger core and the debugger front end code.
 */

/* kernel debug core data काष्ठाures */
काष्ठा kgdb_state अणु
	पूर्णांक			ex_vector;
	पूर्णांक			signo;
	पूर्णांक			err_code;
	पूर्णांक			cpu;
	पूर्णांक			pass_exception;
	अचिन्हित दीर्घ		thr_query;
	अचिन्हित दीर्घ		thपढ़ोid;
	दीर्घ			kgdb_usethपढ़ोid;
	काष्ठा pt_regs		*linux_regs;
	atomic_t		*send_पढ़ोy;
पूर्ण;

/* Exception state values */
#घोषणा DCPU_WANT_MASTER 0x1 /* Waiting to become a master kgdb cpu */
#घोषणा DCPU_NEXT_MASTER 0x2 /* Transition from one master cpu to another */
#घोषणा DCPU_IS_SLAVE    0x4 /* Slave cpu enter exception */
#घोषणा DCPU_WANT_BT     0x8 /* Slave cpu should backtrace then clear flag */

काष्ठा debuggerinfo_काष्ठा अणु
	व्योम			*debuggerinfo;
	काष्ठा task_काष्ठा	*task;
	पूर्णांक			exception_state;
	पूर्णांक			ret_state;
	पूर्णांक			irq_depth;
	पूर्णांक			enter_kgdb;
	bool			rounding_up;
पूर्ण;

बाह्य काष्ठा debuggerinfo_काष्ठा kgdb_info[];

/* kernel debug core अवरोध poपूर्णांक routines */
बाह्य पूर्णांक dbg_हटाओ_all_अवरोध(व्योम);
बाह्य पूर्णांक dbg_set_sw_अवरोध(अचिन्हित दीर्घ addr);
बाह्य पूर्णांक dbg_हटाओ_sw_अवरोध(अचिन्हित दीर्घ addr);
बाह्य पूर्णांक dbg_activate_sw_अवरोधpoपूर्णांकs(व्योम);
बाह्य पूर्णांक dbg_deactivate_sw_अवरोधpoपूर्णांकs(व्योम);

/* polled अक्षरacter access to i/o module */
बाह्य पूर्णांक dbg_io_get_अक्षर(व्योम);

/* stub वापस value क्रम चयनing between the gdbstub and kdb */
#घोषणा DBG_PASS_EVENT -12345
/* Switch from one cpu to another */
#घोषणा DBG_SWITCH_CPU_EVENT -123456
बाह्य पूर्णांक dbg_चयन_cpu;

/* gdbstub पूर्णांकerface functions */
बाह्य पूर्णांक gdb_serial_stub(काष्ठा kgdb_state *ks);
बाह्य व्योम gdbstub_msg_ग_लिखो(स्थिर अक्षर *s, पूर्णांक len);

/* gdbstub functions used क्रम kdb <-> gdbstub transition */
बाह्य पूर्णांक gdbstub_state(काष्ठा kgdb_state *ks, अक्षर *cmd);
बाह्य पूर्णांक dbg_kdb_mode;

#अगर_घोषित CONFIG_KGDB_KDB
बाह्य पूर्णांक kdb_stub(काष्ठा kgdb_state *ks);
बाह्य पूर्णांक kdb_parse(स्थिर अक्षर *cmdstr);
बाह्य पूर्णांक kdb_common_init_state(काष्ठा kgdb_state *ks);
बाह्य पूर्णांक kdb_common_deinit_state(व्योम);
बाह्य व्योम kdb_dump_stack_on_cpu(पूर्णांक cpu);
#अन्यथा /* ! CONFIG_KGDB_KDB */
अटल अंतरभूत पूर्णांक kdb_stub(काष्ठा kgdb_state *ks)
अणु
	वापस DBG_PASS_EVENT;
पूर्ण
#पूर्ण_अगर /* CONFIG_KGDB_KDB */

#पूर्ण_अगर /* _DEBUG_CORE_H_ */
