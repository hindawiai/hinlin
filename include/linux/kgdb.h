<शैली गुरु>
/*
 * This provides the callbacks and functions that KGDB needs to share between
 * the core, I/O and arch-specअगरic portions.
 *
 * Author: Amit Kale <amitkale@linsyssoft.com> and
 *         Tom Rini <trini@kernel.crashing.org>
 *
 * 2001-2004 (c) Amit S. Kale and 2003-2005 (c) MontaVista Software, Inc.
 * This file is licensed under the terms of the GNU General Public License
 * version 2. This program is licensed "as is" without any warranty of any
 * kind, whether express or implied.
 */
#अगर_अघोषित _KGDB_H_
#घोषणा _KGDB_H_

#समावेश <linux/linkage.h>
#समावेश <linux/init.h>
#समावेश <linux/atomic.h>
#समावेश <linux/kprobes.h>
#अगर_घोषित CONFIG_HAVE_ARCH_KGDB
#समावेश <यंत्र/kgdb.h>
#पूर्ण_अगर

#अगर_घोषित CONFIG_KGDB
काष्ठा pt_regs;

/**
 *	kgdb_skipexception - (optional) निकास kgdb_handle_exception early
 *	@exception: Exception vector number
 *	@regs: Current &काष्ठा pt_regs.
 *
 *	On some architectures it is required to skip a अवरोधpoपूर्णांक
 *	exception when it occurs after a अवरोधpoपूर्णांक has been हटाओd.
 *	This can be implemented in the architecture specअगरic portion of kgdb.
 */
बाह्य पूर्णांक kgdb_skipexception(पूर्णांक exception, काष्ठा pt_regs *regs);

काष्ठा tasklet_काष्ठा;
काष्ठा task_काष्ठा;
काष्ठा uart_port;

/**
 *	kgdb_अवरोधpoपूर्णांक - compiled in अवरोधpoपूर्णांक
 *
 *	This will be implemented as a अटल अंतरभूत per architecture.  This
 *	function is called by the kgdb core to execute an architecture
 *	specअगरic trap to cause kgdb to enter the exception processing.
 *
 */
व्योम kgdb_अवरोधpoपूर्णांक(व्योम);

बाह्य पूर्णांक kgdb_connected;
बाह्य पूर्णांक kgdb_io_module_रेजिस्टरed;

बाह्य atomic_t			kgdb_setting_अवरोधpoपूर्णांक;
बाह्य atomic_t			kgdb_cpu_करोing_single_step;

बाह्य काष्ठा task_काष्ठा	*kgdb_usethपढ़ो;
बाह्य काष्ठा task_काष्ठा	*kgdb_contthपढ़ो;

क्रमागत kgdb_bptype अणु
	BP_BREAKPOINT = 0,
	BP_HARDWARE_BREAKPOINT,
	BP_WRITE_WATCHPOINT,
	BP_READ_WATCHPOINT,
	BP_ACCESS_WATCHPOINT,
	BP_POKE_BREAKPOINT,
पूर्ण;

क्रमागत kgdb_bpstate अणु
	BP_UNDEFINED = 0,
	BP_REMOVED,
	BP_SET,
	BP_ACTIVE
पूर्ण;

काष्ठा kgdb_bkpt अणु
	अचिन्हित दीर्घ		bpt_addr;
	अचिन्हित अक्षर		saved_instr[BREAK_INSTR_SIZE];
	क्रमागत kgdb_bptype	type;
	क्रमागत kgdb_bpstate	state;
पूर्ण;

काष्ठा dbg_reg_def_t अणु
	अक्षर *name;
	पूर्णांक size;
	पूर्णांक offset;
पूर्ण;

#अगर_अघोषित DBG_MAX_REG_NUM
#घोषणा DBG_MAX_REG_NUM 0
#अन्यथा
बाह्य काष्ठा dbg_reg_def_t dbg_reg_def[];
बाह्य अक्षर *dbg_get_reg(पूर्णांक regno, व्योम *mem, काष्ठा pt_regs *regs);
बाह्य पूर्णांक dbg_set_reg(पूर्णांक regno, व्योम *mem, काष्ठा pt_regs *regs);
#पूर्ण_अगर
#अगर_अघोषित KGDB_MAX_BREAKPOINTS
# define KGDB_MAX_BREAKPOINTS	1000
#पूर्ण_अगर

#घोषणा KGDB_HW_BREAKPOINT	1

/*
 * Functions each KGDB-supporting architecture must provide:
 */

/**
 *	kgdb_arch_init - Perक्रमm any architecture specअगरic initalization.
 *
 *	This function will handle the initalization of any architecture
 *	specअगरic callbacks.
 */
बाह्य पूर्णांक kgdb_arch_init(व्योम);

/**
 *	kgdb_arch_निकास - Perक्रमm any architecture specअगरic uninitalization.
 *
 *	This function will handle the uninitalization of any architecture
 *	specअगरic callbacks, क्रम dynamic registration and unregistration.
 */
बाह्य व्योम kgdb_arch_निकास(व्योम);

/**
 *	pt_regs_to_gdb_regs - Convert ptrace regs to GDB regs
 *	@gdb_regs: A poपूर्णांकer to hold the रेजिस्टरs in the order GDB wants.
 *	@regs: The &काष्ठा pt_regs of the current process.
 *
 *	Convert the pt_regs in @regs पूर्णांकo the क्रमmat क्रम रेजिस्टरs that
 *	GDB expects, stored in @gdb_regs.
 */
बाह्य व्योम pt_regs_to_gdb_regs(अचिन्हित दीर्घ *gdb_regs, काष्ठा pt_regs *regs);

/**
 *	sleeping_thपढ़ो_to_gdb_regs - Convert ptrace regs to GDB regs
 *	@gdb_regs: A poपूर्णांकer to hold the रेजिस्टरs in the order GDB wants.
 *	@p: The &काष्ठा task_काष्ठा of the desired process.
 *
 *	Convert the रेजिस्टर values of the sleeping process in @p to
 *	the क्रमmat that GDB expects.
 *	This function is called when kgdb करोes not have access to the
 *	&काष्ठा pt_regs and thereक्रमe it should fill the gdb रेजिस्टरs
 *	@gdb_regs with what has	been saved in &काष्ठा thपढ़ो_काष्ठा
 *	thपढ़ो field during चयन_to.
 */
बाह्य व्योम
sleeping_thपढ़ो_to_gdb_regs(अचिन्हित दीर्घ *gdb_regs, काष्ठा task_काष्ठा *p);

/**
 *	gdb_regs_to_pt_regs - Convert GDB regs to ptrace regs.
 *	@gdb_regs: A poपूर्णांकer to hold the रेजिस्टरs we've received from GDB.
 *	@regs: A poपूर्णांकer to a &काष्ठा pt_regs to hold these values in.
 *
 *	Convert the GDB regs in @gdb_regs पूर्णांकo the pt_regs, and store them
 *	in @regs.
 */
बाह्य व्योम gdb_regs_to_pt_regs(अचिन्हित दीर्घ *gdb_regs, काष्ठा pt_regs *regs);

/**
 *	kgdb_arch_handle_exception - Handle architecture specअगरic GDB packets.
 *	@vector: The error vector of the exception that happened.
 *	@signo: The संकेत number of the exception that happened.
 *	@err_code: The error code of the exception that happened.
 *	@remcom_in_buffer: The buffer of the packet we have पढ़ो.
 *	@remcom_out_buffer: The buffer of %BUFMAX bytes to ग_लिखो a packet पूर्णांकo.
 *	@regs: The &काष्ठा pt_regs of the current process.
 *
 *	This function MUST handle the 'c' and 's' command packets,
 *	as well packets to set / हटाओ a hardware अवरोधpoपूर्णांक, अगर used.
 *	If there are additional packets which the hardware needs to handle,
 *	they are handled here.  The code should वापस -1 अगर it wants to
 *	process more packets, and a %0 or %1 अगर it wants to निकास from the
 *	kgdb callback.
 */
बाह्य पूर्णांक
kgdb_arch_handle_exception(पूर्णांक vector, पूर्णांक signo, पूर्णांक err_code,
			   अक्षर *remcom_in_buffer,
			   अक्षर *remcom_out_buffer,
			   काष्ठा pt_regs *regs);

/**
 *	kgdb_arch_handle_qxfer_pkt - Handle architecture specअगरic GDB XML
 *				     packets.
 *	@remcom_in_buffer: The buffer of the packet we have पढ़ो.
 *	@remcom_out_buffer: The buffer of %BUFMAX bytes to ग_लिखो a packet पूर्णांकo.
 */

बाह्य व्योम
kgdb_arch_handle_qxfer_pkt(अक्षर *remcom_in_buffer,
			   अक्षर *remcom_out_buffer);

/**
 *	kgdb_call_nmi_hook - Call kgdb_nmicallback() on the current CPU
 *	@ignored: This parameter is only here to match the prototype.
 *
 *	If you're using the शेष implementation of kgdb_roundup_cpus()
 *	this function will be called per CPU.  If you करोn't implement
 *	kgdb_call_nmi_hook() a शेष will be used.
 */

बाह्य व्योम kgdb_call_nmi_hook(व्योम *ignored);

/**
 *	kgdb_roundup_cpus - Get other CPUs पूर्णांकo a holding pattern
 *
 *	On SMP प्रणालीs, we need to get the attention of the other CPUs
 *	and get them पूर्णांकo a known state.  This should करो what is needed
 *	to get the other CPUs to call kgdb_रुको(). Note that on some arches,
 *	the NMI approach is not used क्रम rounding up all the CPUs.  Normally
 *	those architectures can just not implement this and get the शेष.
 *
 *	On non-SMP प्रणालीs, this is not called.
 */
बाह्य व्योम kgdb_roundup_cpus(व्योम);

/**
 *	kgdb_arch_set_pc - Generic call back to the program counter
 *	@regs: Current &काष्ठा pt_regs.
 *  @pc: The new value क्रम the program counter
 *
 *	This function handles updating the program counter and requires an
 *	architecture specअगरic implementation.
 */
बाह्य व्योम kgdb_arch_set_pc(काष्ठा pt_regs *regs, अचिन्हित दीर्घ pc);


/* Optional functions. */
बाह्य पूर्णांक kgdb_validate_अवरोध_address(अचिन्हित दीर्घ addr);
बाह्य पूर्णांक kgdb_arch_set_अवरोधpoपूर्णांक(काष्ठा kgdb_bkpt *bpt);
बाह्य पूर्णांक kgdb_arch_हटाओ_अवरोधpoपूर्णांक(काष्ठा kgdb_bkpt *bpt);

/**
 *	kgdb_arch_late - Perक्रमm any architecture specअगरic initalization.
 *
 *	This function will handle the late initalization of any
 *	architecture specअगरic callbacks.  This is an optional function क्रम
 *	handling things like late initialization of hw अवरोधpoपूर्णांकs.  The
 *	शेष implementation करोes nothing.
 */
बाह्य व्योम kgdb_arch_late(व्योम);


/**
 * काष्ठा kgdb_arch - Describe architecture specअगरic values.
 * @gdb_bpt_instr: The inकाष्ठाion to trigger a अवरोधpoपूर्णांक.
 * @flags: Flags क्रम the अवरोधpoपूर्णांक, currently just %KGDB_HW_BREAKPOINT.
 * @set_अवरोधpoपूर्णांक: Allow an architecture to specअगरy how to set a software
 * अवरोधpoपूर्णांक.
 * @हटाओ_अवरोधpoपूर्णांक: Allow an architecture to specअगरy how to हटाओ a
 * software अवरोधpoपूर्णांक.
 * @set_hw_अवरोधpoपूर्णांक: Allow an architecture to specअगरy how to set a hardware
 * अवरोधpoपूर्णांक.
 * @हटाओ_hw_अवरोधpoपूर्णांक: Allow an architecture to specअगरy how to हटाओ a
 * hardware अवरोधpoपूर्णांक.
 * @disable_hw_अवरोध: Allow an architecture to specअगरy how to disable
 * hardware अवरोधpoपूर्णांकs क्रम a single cpu.
 * @हटाओ_all_hw_अवरोध: Allow an architecture to specअगरy how to हटाओ all
 * hardware अवरोधpoपूर्णांकs.
 * @correct_hw_अवरोध: Allow an architecture to specअगरy how to correct the
 * hardware debug रेजिस्टरs.
 * @enable_nmi: Manage NMI-triggered entry to KGDB
 */
काष्ठा kgdb_arch अणु
	अचिन्हित अक्षर		gdb_bpt_instr[BREAK_INSTR_SIZE];
	अचिन्हित दीर्घ		flags;

	पूर्णांक	(*set_अवरोधpoपूर्णांक)(अचिन्हित दीर्घ, अक्षर *);
	पूर्णांक	(*हटाओ_अवरोधpoपूर्णांक)(अचिन्हित दीर्घ, अक्षर *);
	पूर्णांक	(*set_hw_अवरोधpoपूर्णांक)(अचिन्हित दीर्घ, पूर्णांक, क्रमागत kgdb_bptype);
	पूर्णांक	(*हटाओ_hw_अवरोधpoपूर्णांक)(अचिन्हित दीर्घ, पूर्णांक, क्रमागत kgdb_bptype);
	व्योम	(*disable_hw_अवरोध)(काष्ठा pt_regs *regs);
	व्योम	(*हटाओ_all_hw_अवरोध)(व्योम);
	व्योम	(*correct_hw_अवरोध)(व्योम);

	व्योम	(*enable_nmi)(bool on);
पूर्ण;

/**
 * काष्ठा kgdb_io - Describe the पूर्णांकerface क्रम an I/O driver to talk with KGDB.
 * @name: Name of the I/O driver.
 * @पढ़ो_अक्षर: Poपूर्णांकer to a function that will वापस one अक्षर.
 * @ग_लिखो_अक्षर: Poपूर्णांकer to a function that will ग_लिखो one अक्षर.
 * @flush: Poपूर्णांकer to a function that will flush any pending ग_लिखोs.
 * @init: Poपूर्णांकer to a function that will initialize the device.
 * @deinit: Poपूर्णांकer to a function that will deinit the device. Implies that
 * this I/O driver is temporary and expects to be replaced. Called when
 * an I/O driver is replaced or explicitly unरेजिस्टरed.
 * @pre_exception: Poपूर्णांकer to a function that will करो any prep work क्रम
 * the I/O driver.
 * @post_exception: Poपूर्णांकer to a function that will करो any cleanup work
 * क्रम the I/O driver.
 * @cons: valid अगर the I/O device is a console; अन्यथा शून्य.
 */
काष्ठा kgdb_io अणु
	स्थिर अक्षर		*name;
	पूर्णांक			(*पढ़ो_अक्षर) (व्योम);
	व्योम			(*ग_लिखो_अक्षर) (u8);
	व्योम			(*flush) (व्योम);
	पूर्णांक			(*init) (व्योम);
	व्योम			(*deinit) (व्योम);
	व्योम			(*pre_exception) (व्योम);
	व्योम			(*post_exception) (व्योम);
	काष्ठा console		*cons;
पूर्ण;

बाह्य स्थिर काष्ठा kgdb_arch		arch_kgdb_ops;

बाह्य अचिन्हित दीर्घ kgdb_arch_pc(पूर्णांक exception, काष्ठा pt_regs *regs);

#अगर_घोषित CONFIG_SERIAL_KGDB_NMI
बाह्य पूर्णांक kgdb_रेजिस्टर_nmi_console(व्योम);
बाह्य पूर्णांक kgdb_unरेजिस्टर_nmi_console(व्योम);
बाह्य bool kgdb_nmi_poll_knock(व्योम);
#अन्यथा
अटल अंतरभूत पूर्णांक kgdb_रेजिस्टर_nmi_console(व्योम) अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक kgdb_unरेजिस्टर_nmi_console(व्योम) अणु वापस 0; पूर्ण
अटल अंतरभूत bool kgdb_nmi_poll_knock(व्योम) अणु वापस true; पूर्ण
#पूर्ण_अगर

बाह्य पूर्णांक kgdb_रेजिस्टर_io_module(काष्ठा kgdb_io *local_kgdb_io_ops);
बाह्य व्योम kgdb_unरेजिस्टर_io_module(काष्ठा kgdb_io *local_kgdb_io_ops);
बाह्य काष्ठा kgdb_io *dbg_io_ops;

बाह्य पूर्णांक kgdb_hex2दीर्घ(अक्षर **ptr, अचिन्हित दीर्घ *दीर्घ_val);
बाह्य अक्षर *kgdb_mem2hex(अक्षर *mem, अक्षर *buf, पूर्णांक count);
बाह्य पूर्णांक kgdb_hex2mem(अक्षर *buf, अक्षर *mem, पूर्णांक count);

बाह्य पूर्णांक kgdb_isहटाओdअवरोध(अचिन्हित दीर्घ addr);
बाह्य पूर्णांक kgdb_has_hit_अवरोध(अचिन्हित दीर्घ addr);

बाह्य पूर्णांक
kgdb_handle_exception(पूर्णांक ex_vector, पूर्णांक signo, पूर्णांक err_code,
		      काष्ठा pt_regs *regs);
बाह्य पूर्णांक kgdb_nmicallback(पूर्णांक cpu, व्योम *regs);
बाह्य पूर्णांक kgdb_nmicallin(पूर्णांक cpu, पूर्णांक trapnr, व्योम *regs, पूर्णांक err_code,
			  atomic_t *snd_rdy);
बाह्य व्योम gdbstub_निकास(पूर्णांक status);

/*
 * kgdb and kprobes both use the same (kprobe) blocklist (which makes sense
 * given they are both typically hooked up to the same trap meaning on most
 * architectures one cannot be used to debug the other)
 *
 * However on architectures where kprobes is not (yet) implemented we permit
 * अवरोधpoपूर्णांकs everywhere rather than blocking everything by शेष.
 */
अटल अंतरभूत bool kgdb_within_blocklist(अचिन्हित दीर्घ addr)
अणु
#अगर_घोषित CONFIG_KGDB_HONOUR_BLOCKLIST
	वापस within_kprobe_blacklist(addr);
#अन्यथा
	वापस false;
#पूर्ण_अगर
पूर्ण

बाह्य पूर्णांक			kgdb_single_step;
बाह्य atomic_t			kgdb_active;
#घोषणा in_dbg_master() \
	(irqs_disabled() && (smp_processor_id() == atomic_पढ़ो(&kgdb_active)))
बाह्य bool dbg_is_early;
बाह्य व्योम __init dbg_late_init(व्योम);
बाह्य व्योम kgdb_panic(स्थिर अक्षर *msg);
बाह्य व्योम kgdb_मुक्त_init_mem(व्योम);
#अन्यथा /* ! CONFIG_KGDB */
#घोषणा in_dbg_master() (0)
#घोषणा dbg_late_init()
अटल अंतरभूत व्योम kgdb_panic(स्थिर अक्षर *msg) अणुपूर्ण
अटल अंतरभूत व्योम kgdb_मुक्त_init_mem(व्योम) अणु पूर्ण
#पूर्ण_अगर /* ! CONFIG_KGDB */
#पूर्ण_अगर /* _KGDB_H_ */
