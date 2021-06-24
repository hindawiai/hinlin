<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Routines providing a simple monitor क्रम use on the PowerMac.
 *
 * Copyright (C) 1996-2005 Paul Mackerras.
 * Copyright (C) 2001 PPC64 Team, IBM Corp
 * Copyrignt (C) 2006 Michael Ellerman, IBM Corp
 */

#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/smp.h>
#समावेश <linux/mm.h>
#समावेश <linux/reboot.h>
#समावेश <linux/delay.h>
#समावेश <linux/kallsyms.h>
#समावेश <linux/kmsg_dump.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/export.h>
#समावेश <linux/sysrq.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/bug.h>
#समावेश <linux/nmi.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/security.h>

#समावेश <यंत्र/debugfs.h>
#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/smp.h>
#समावेश <यंत्र/माला.स>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/xmon.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/mmu.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/plpar_wrappers.h>
#समावेश <यंत्र/cputable.h>
#समावेश <यंत्र/rtas.h>
#समावेश <यंत्र/sstep.h>
#समावेश <यंत्र/irq_regs.h>
#समावेश <यंत्र/spu.h>
#समावेश <यंत्र/spu_priv1.h>
#समावेश <यंत्र/समलाँघ.स>
#समावेश <यंत्र/reg.h>
#समावेश <यंत्र/debug.h>
#समावेश <यंत्र/hw_अवरोधpoपूर्णांक.h>
#समावेश <यंत्र/xive.h>
#समावेश <यंत्र/opal.h>
#समावेश <यंत्र/firmware.h>
#समावेश <यंत्र/code-patching.h>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/inst.h>
#समावेश <यंत्र/पूर्णांकerrupt.h>

#अगर_घोषित CONFIG_PPC64
#समावेश <यंत्र/hvcall.h>
#समावेश <यंत्र/paca.h>
#पूर्ण_अगर

#समावेश "nonstdio.h"
#समावेश "dis-asm.h"
#समावेश "xmon_bpts.h"

#अगर_घोषित CONFIG_SMP
अटल cpumask_t cpus_in_xmon = CPU_MASK_NONE;
अटल अचिन्हित दीर्घ xmon_taken = 1;
अटल पूर्णांक xmon_owner;
अटल पूर्णांक xmon_gate;
#अन्यथा
#घोषणा xmon_owner 0
#पूर्ण_अगर /* CONFIG_SMP */

#अगर_घोषित CONFIG_PPC_PSERIES
अटल पूर्णांक set_indicator_token = RTAS_UNKNOWN_SERVICE;
#पूर्ण_अगर
अटल अचिन्हित दीर्घ in_xmon __पढ़ो_mostly = 0;
अटल पूर्णांक xmon_on = IS_ENABLED(CONFIG_XMON_DEFAULT);
अटल bool xmon_is_ro = IS_ENABLED(CONFIG_XMON_DEFAULT_RO_MODE);

अटल अचिन्हित दीर्घ adrs;
अटल पूर्णांक size = 1;
#घोषणा MAX_DUMP (64 * 1024)
अटल अचिन्हित दीर्घ ndump = 64;
#घोषणा MAX_IDUMP (MAX_DUMP >> 2)
अटल अचिन्हित दीर्घ nidump = 16;
अटल अचिन्हित दीर्घ ncsum = 4096;
अटल पूर्णांक termch;
अटल अक्षर पंचांगpstr[128];
अटल पूर्णांक tracing_enabled;

अटल दीर्घ bus_error_jmp[JMP_BUF_LEN];
अटल पूर्णांक catch_memory_errors;
अटल पूर्णांक catch_spr_faults;
अटल दीर्घ *xmon_fault_jmp[NR_CPUS];

/* Breakpoपूर्णांक stuff */
काष्ठा bpt अणु
	अचिन्हित दीर्घ	address;
	काष्ठा ppc_inst	*instr;
	atomic_t	ref_count;
	पूर्णांक		enabled;
	अचिन्हित दीर्घ	pad;
पूर्ण;

/* Bits in bpt.enabled */
#घोषणा BP_CIABR	1
#घोषणा BP_TRAP		2
#घोषणा BP_DABR		4

अटल काष्ठा bpt bpts[NBPTS];
अटल काष्ठा bpt dabr[HBP_NUM_MAX];
अटल काष्ठा bpt *iabr;
अटल अचिन्हित bpinstr = 0x7fe00008;	/* trap */

#घोषणा BP_NUM(bp)	((bp) - bpts + 1)

/* Prototypes */
अटल पूर्णांक cmds(काष्ठा pt_regs *);
अटल पूर्णांक mपढ़ो(अचिन्हित दीर्घ, व्योम *, पूर्णांक);
अटल पूर्णांक mग_लिखो(अचिन्हित दीर्घ, व्योम *, पूर्णांक);
अटल पूर्णांक mपढ़ो_instr(अचिन्हित दीर्घ, काष्ठा ppc_inst *);
अटल पूर्णांक handle_fault(काष्ठा pt_regs *);
अटल व्योम byterev(अचिन्हित अक्षर *, पूर्णांक);
अटल व्योम memex(व्योम);
अटल पूर्णांक bsesc(व्योम);
अटल व्योम dump(व्योम);
अटल व्योम show_pte(अचिन्हित दीर्घ);
अटल व्योम prdump(अचिन्हित दीर्घ, दीर्घ);
अटल पूर्णांक ppc_inst_dump(अचिन्हित दीर्घ, दीर्घ, पूर्णांक);
अटल व्योम dump_log_buf(व्योम);

#अगर_घोषित CONFIG_PPC_POWERNV
अटल व्योम dump_opal_msglog(व्योम);
#अन्यथा
अटल अंतरभूत व्योम dump_opal_msglog(व्योम)
अणु
	म_लिखो("Machine is not running OPAL firmware.\n");
पूर्ण
#पूर्ण_अगर

अटल व्योम backtrace(काष्ठा pt_regs *);
अटल व्योम excprपूर्णांक(काष्ठा pt_regs *);
अटल व्योम prregs(काष्ठा pt_regs *);
अटल व्योम memops(पूर्णांक);
अटल व्योम memlocate(व्योम);
अटल व्योम memzcan(व्योम);
अटल व्योम memdअगरfs(अचिन्हित अक्षर *, अचिन्हित अक्षर *, अचिन्हित, अचिन्हित);
पूर्णांक skipbl(व्योम);
पूर्णांक scanhex(अचिन्हित दीर्घ *valp);
अटल व्योम scannl(व्योम);
अटल पूर्णांक hexdigit(पूर्णांक);
व्योम माला_लोtring(अक्षर *, पूर्णांक);
अटल व्योम flush_input(व्योम);
अटल पूर्णांक inअक्षर(व्योम);
अटल व्योम take_input(अक्षर *);
अटल पूर्णांक  पढ़ो_spr(पूर्णांक, अचिन्हित दीर्घ *);
अटल व्योम ग_लिखो_spr(पूर्णांक, अचिन्हित दीर्घ);
अटल व्योम super_regs(व्योम);
अटल व्योम हटाओ_bpts(व्योम);
अटल व्योम insert_bpts(व्योम);
अटल व्योम हटाओ_cpu_bpts(व्योम);
अटल व्योम insert_cpu_bpts(व्योम);
अटल काष्ठा bpt *at_अवरोधpoपूर्णांक(अचिन्हित दीर्घ pc);
अटल काष्ठा bpt *in_अवरोधpoपूर्णांक_table(अचिन्हित दीर्घ pc, अचिन्हित दीर्घ *offp);
अटल पूर्णांक  करो_step(काष्ठा pt_regs *);
अटल व्योम bpt_cmds(व्योम);
अटल व्योम cacheflush(व्योम);
अटल पूर्णांक  cpu_cmd(व्योम);
अटल व्योम csum(व्योम);
अटल व्योम bootcmds(व्योम);
अटल व्योम proccall(व्योम);
अटल व्योम show_tasks(व्योम);
व्योम dump_segments(व्योम);
अटल व्योम symbol_lookup(व्योम);
अटल व्योम xmon_show_stack(अचिन्हित दीर्घ sp, अचिन्हित दीर्घ lr,
			    अचिन्हित दीर्घ pc);
अटल व्योम xmon_prपूर्णांक_symbol(अचिन्हित दीर्घ address, स्थिर अक्षर *mid,
			      स्थिर अक्षर *after);
अटल स्थिर अक्षर *getvecname(अचिन्हित दीर्घ vec);

अटल पूर्णांक करो_spu_cmd(व्योम);

#अगर_घोषित CONFIG_44x
अटल व्योम dump_tlb_44x(व्योम);
#पूर्ण_अगर
#अगर_घोषित CONFIG_PPC_BOOK3E
अटल व्योम dump_tlb_book3e(व्योम);
#पूर्ण_अगर

अटल व्योम clear_all_bpt(व्योम);

#अगर_घोषित CONFIG_PPC64
#घोषणा REG		"%.16lx"
#अन्यथा
#घोषणा REG		"%.8lx"
#पूर्ण_अगर

#अगर_घोषित __LITTLE_ENDIAN__
#घोषणा GETWORD(v)	(((v)[3] << 24) + ((v)[2] << 16) + ((v)[1] << 8) + (v)[0])
#अन्यथा
#घोषणा GETWORD(v)	(((v)[0] << 24) + ((v)[1] << 16) + ((v)[2] << 8) + (v)[3])
#पूर्ण_अगर

अटल स्थिर अक्षर *xmon_ro_msg = "Operation disabled: xmon in read-only mode\n";

अटल अक्षर *help_string = "\
Commands:\न\
  b	show अवरोधpoपूर्णांकs\न\
  bd	set data अवरोधpoपूर्णांक\न\
  bi	set inकाष्ठाion अवरोधpoपूर्णांक\न\
  bc	clear अवरोधpoपूर्णांक\न"
#अगर_घोषित CONFIG_SMP
  "\
  c	prपूर्णांक cpus stopped in xmon\न\
  c#	try to चयन to cpu number h (in hex)\न"
#पूर्ण_अगर
  "\
  C	checksum\न\
  d	dump bytes\न\
  d1	dump 1 byte values\न\
  d2	dump 2 byte values\न\
  d4	dump 4 byte values\न\
  d8	dump 8 byte values\न\
  di	dump inकाष्ठाions\न\
  df	dump भग्न values\न\
  dd	dump द्विगुन values\न\
  dl    dump the kernel log buffer\न"
#अगर_घोषित CONFIG_PPC_POWERNV
  "\
  करो    dump the OPAL message log\न"
#पूर्ण_अगर
#अगर_घोषित CONFIG_PPC64
  "\
  dp[#]	dump paca क्रम current cpu, or cpu #\न\
  dpa	dump paca क्रम all possible cpus\न"
#पूर्ण_अगर
  "\
  dr	dump stream of raw bytes\न\
  dv	dump भव address translation \न\
  dt	dump the tracing buffers (uses prपूर्णांकk)\न\
  dtc	dump the tracing buffers क्रम current CPU (uses prपूर्णांकk)\न\
"
#अगर_घोषित CONFIG_PPC_POWERNV
"  dx#   dump xive on CPU #\न\
  dxi#  dump xive irq state #\न\
  dxa   dump xive on all CPUs\न"
#पूर्ण_अगर
"  e	prपूर्णांक exception inक्रमmation\न\
  f	flush cache\न\
  la	lookup symbol+offset of specअगरied address\न\
  ls	lookup address of specअगरied symbol\न\
  lp s [#]	lookup address of percpu symbol s क्रम current cpu, or cpu #\न\
  m	examine/change memory\न\
  mm	move a block of memory\न\
  ms	set a block of memory\न\
  md	compare two blocks of memory\न\
  ml	locate a block of memory\न\
  mz	zero a block of memory\न\
  mi	show inक्रमmation about memory allocation\न\
  p 	call a procedure\न\
  P 	list processes/tasks\न\
  r	prपूर्णांक रेजिस्टरs\न\
  s	single step\न"
#अगर_घोषित CONFIG_SPU_BASE
"  ss	stop execution on all spus\न\
  sr	restore execution on stopped spus\न\
  sf  #	dump spu fields क्रम spu # (in hex)\न\
  sd  #	dump spu local store क्रम spu # (in hex)\न\
  sdi #	disassemble spu local store क्रम spu # (in hex)\न"
#पूर्ण_अगर
"  S	prपूर्णांक special रेजिस्टरs\न\
  Sa    prपूर्णांक all SPRs\न\
  Sr #	पढ़ो SPR #\न\
  Sw #v ग_लिखो v to SPR #\न\
  t	prपूर्णांक backtrace\न\
  x	निकास monitor and recover\न\
  X	निकास monitor and करोn't recover\न"
#अगर defined(CONFIG_PPC64) && !defined(CONFIG_PPC_BOOK3E)
"  u	dump segment table or SLB\n"
#या_अगर defined(CONFIG_PPC_BOOK3S_32)
"  u	dump segment registers\n"
#या_अगर defined(CONFIG_44x) || defined(CONFIG_PPC_BOOK3E)
"  u	dump TLB\n"
#पूर्ण_अगर
"  U	show uptime information\n"
"  ?	help\n"
"  # n	limit output to n lines per page (for dp, dpa, dl)\n"
"  zr	reboot\n"
"  zh	halt\n"
;

#अगर_घोषित CONFIG_SECURITY
अटल bool xmon_is_locked_करोwn(व्योम)
अणु
	अटल bool lockकरोwn;

	अगर (!lockकरोwn) अणु
		lockकरोwn = !!security_locked_करोwn(LOCKDOWN_XMON_RW);
		अगर (lockकरोwn) अणु
			म_लिखो("xmon: Disabled due to kernel lockdown\n");
			xmon_is_ro = true;
		पूर्ण
	पूर्ण

	अगर (!xmon_is_ro) अणु
		xmon_is_ro = !!security_locked_करोwn(LOCKDOWN_XMON_WR);
		अगर (xmon_is_ro)
			म_लिखो("xmon: Read-only due to kernel lockdown\n");
	पूर्ण

	वापस lockकरोwn;
पूर्ण
#अन्यथा /* CONFIG_SECURITY */
अटल अंतरभूत bool xmon_is_locked_करोwn(व्योम)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर

अटल काष्ठा pt_regs *xmon_regs;

अटल अंतरभूत व्योम sync(व्योम)
अणु
	यंत्र अस्थिर("sync; isync");
पूर्ण

अटल अंतरभूत व्योम cflush(व्योम *p)
अणु
	यंत्र अस्थिर ("dcbf 0,%0; icbi 0,%0" : : "r" (p));
पूर्ण

अटल अंतरभूत व्योम cinval(व्योम *p)
अणु
	यंत्र अस्थिर ("dcbi 0,%0; icbi 0,%0" : : "r" (p));
पूर्ण

/**
 * ग_लिखो_ciabr() - ग_लिखो the CIABR SPR
 * @ciabr:	The value to ग_लिखो.
 *
 * This function ग_लिखोs a value to the CIARB रेजिस्टर either directly
 * through mtspr inकाष्ठाion अगर the kernel is in HV privilege mode or
 * call a hypervisor function to achieve the same in हाल the kernel
 * is in supervisor privilege mode.
 */
अटल व्योम ग_लिखो_ciabr(अचिन्हित दीर्घ ciabr)
अणु
	अगर (!cpu_has_feature(CPU_FTR_ARCH_207S))
		वापस;

	अगर (cpu_has_feature(CPU_FTR_HVMODE)) अणु
		mtspr(SPRN_CIABR, ciabr);
		वापस;
	पूर्ण
	plpar_set_ciabr(ciabr);
पूर्ण

/**
 * set_ciabr() - set the CIABR
 * @addr:	The value to set.
 *
 * This function sets the correct privilege value पूर्णांकo the the HW
 * अवरोधpoपूर्णांक address beक्रमe writing it up in the CIABR रेजिस्टर.
 */
अटल व्योम set_ciabr(अचिन्हित दीर्घ addr)
अणु
	addr &= ~CIABR_PRIV;

	अगर (cpu_has_feature(CPU_FTR_HVMODE))
		addr |= CIABR_PRIV_HYPER;
	अन्यथा
		addr |= CIABR_PRIV_SUPER;
	ग_लिखो_ciabr(addr);
पूर्ण

/*
 * Disable surveillance (the service processor watchकरोg function)
 * जबतक we are in xmon.
 * XXX we should re-enable it when we leave. :)
 */
#घोषणा SURVEILLANCE_TOKEN	9000

अटल अंतरभूत व्योम disable_surveillance(व्योम)
अणु
#अगर_घोषित CONFIG_PPC_PSERIES
	/* Since this can't be a module, args should end up below 4GB. */
	अटल काष्ठा rtas_args args;

	/*
	 * At this poपूर्णांक we have got all the cpus we can पूर्णांकo
	 * xmon, so there is hopefully no other cpu calling RTAS
	 * at the moment, even though we करोn't take rtas.lock.
	 * If we did try to take rtas.lock there would be a
	 * real possibility of deadlock.
	 */
	अगर (set_indicator_token == RTAS_UNKNOWN_SERVICE)
		वापस;

	rtas_call_unlocked(&args, set_indicator_token, 3, 1, शून्य,
			   SURVEILLANCE_TOKEN, 0, 0);

#पूर्ण_अगर /* CONFIG_PPC_PSERIES */
पूर्ण

#अगर_घोषित CONFIG_SMP
अटल पूर्णांक xmon_speaker;

अटल व्योम get_output_lock(व्योम)
अणु
	पूर्णांक me = smp_processor_id() + 0x100;
	पूर्णांक last_speaker = 0, prev;
	दीर्घ समयout;

	अगर (xmon_speaker == me)
		वापस;

	क्रम (;;) अणु
		last_speaker = cmpxchg(&xmon_speaker, 0, me);
		अगर (last_speaker == 0)
			वापस;

		/*
		 * Wait a full second क्रम the lock, we might be on a slow
		 * console, but check every 100us.
		 */
		समयout = 10000;
		जबतक (xmon_speaker == last_speaker) अणु
			अगर (--समयout > 0) अणु
				udelay(100);
				जारी;
			पूर्ण

			/* hostile takeover */
			prev = cmpxchg(&xmon_speaker, last_speaker, me);
			अगर (prev == last_speaker)
				वापस;
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम release_output_lock(व्योम)
अणु
	xmon_speaker = 0;
पूर्ण

पूर्णांक cpus_are_in_xmon(व्योम)
अणु
	वापस !cpumask_empty(&cpus_in_xmon);
पूर्ण

अटल bool रुको_क्रम_other_cpus(पूर्णांक ncpus)
अणु
	अचिन्हित दीर्घ समयout;

	/* We रुको क्रम 2s, which is a metric "little while" */
	क्रम (समयout = 20000; समयout != 0; --समयout) अणु
		अगर (cpumask_weight(&cpus_in_xmon) >= ncpus)
			वापस true;
		udelay(100);
		barrier();
	पूर्ण

	वापस false;
पूर्ण
#अन्यथा /* CONFIG_SMP */
अटल अंतरभूत व्योम get_output_lock(व्योम) अणुपूर्ण
अटल अंतरभूत व्योम release_output_lock(व्योम) अणुपूर्ण
#पूर्ण_अगर

अटल अंतरभूत पूर्णांक unrecoverable_excp(काष्ठा pt_regs *regs)
अणु
#अगर defined(CONFIG_4xx) || defined(CONFIG_PPC_BOOK3E)
	/* We have no MSR_RI bit on 4xx or Book3e, so we simply वापस false */
	वापस 0;
#अन्यथा
	वापस ((regs->msr & MSR_RI) == 0);
#पूर्ण_अगर
पूर्ण

अटल व्योम xmon_touch_watchकरोgs(व्योम)
अणु
	touch_softlockup_watchकरोg_sync();
	rcu_cpu_stall_reset();
	touch_nmi_watchकरोg();
पूर्ण

अटल पूर्णांक xmon_core(काष्ठा pt_regs *regs, पूर्णांक fromipi)
अणु
	पूर्णांक cmd = 0;
	काष्ठा bpt *bp;
	दीर्घ recurse_jmp[JMP_BUF_LEN];
	bool locked_करोwn;
	अचिन्हित दीर्घ offset;
	अचिन्हित दीर्घ flags;
#अगर_घोषित CONFIG_SMP
	पूर्णांक cpu;
	पूर्णांक secondary;
#पूर्ण_अगर

	local_irq_save(flags);
	hard_irq_disable();

	locked_करोwn = xmon_is_locked_करोwn();

	अगर (!fromipi) अणु
		tracing_enabled = tracing_is_on();
		tracing_off();
	पूर्ण

	bp = in_अवरोधpoपूर्णांक_table(regs->nip, &offset);
	अगर (bp != शून्य) अणु
		regs->nip = bp->address + offset;
		atomic_dec(&bp->ref_count);
	पूर्ण

	हटाओ_cpu_bpts();

#अगर_घोषित CONFIG_SMP
	cpu = smp_processor_id();
	अगर (cpumask_test_cpu(cpu, &cpus_in_xmon)) अणु
		/*
		 * We catch SPR पढ़ो/ग_लिखो faults here because the 0x700, 0xf60
		 * etc. handlers करोn't call debugger_fault_handler().
		 */
		अगर (catch_spr_faults)
			दीर्घ_लाँघ(bus_error_jmp, 1);
		get_output_lock();
		excprपूर्णांक(regs);
		म_लिखो("cpu 0x%x: Exception %lx %s in xmon, "
		       "returning to main loop\n",
		       cpu, regs->trap, getvecname(TRAP(regs)));
		release_output_lock();
		दीर्घ_लाँघ(xmon_fault_jmp[cpu], 1);
	पूर्ण

	अगर (बनाओ_लाँघ(recurse_jmp) != 0) अणु
		अगर (!in_xmon || !xmon_gate) अणु
			get_output_lock();
			म_लिखो("xmon: WARNING: bad recursive fault "
			       "on cpu 0x%x\n", cpu);
			release_output_lock();
			जाओ रुकोing;
		पूर्ण
		secondary = !(xmon_taken && cpu == xmon_owner);
		जाओ cmdloop;
	पूर्ण

	xmon_fault_jmp[cpu] = recurse_jmp;

	bp = शून्य;
	अगर ((regs->msr & (MSR_IR|MSR_PR|MSR_64BIT)) == (MSR_IR|MSR_64BIT))
		bp = at_अवरोधpoपूर्णांक(regs->nip);
	अगर (bp || unrecoverable_excp(regs))
		fromipi = 0;

	अगर (!fromipi) अणु
		get_output_lock();
		अगर (!locked_करोwn)
			excprपूर्णांक(regs);
		अगर (bp) अणु
			म_लिखो("cpu 0x%x stopped at breakpoint 0x%tx (",
			       cpu, BP_NUM(bp));
			xmon_prपूर्णांक_symbol(regs->nip, " ", ")\n");
		पूर्ण
		अगर (unrecoverable_excp(regs))
			म_लिखो("WARNING: exception is not recoverable, "
			       "can't continue\n");
		release_output_lock();
	पूर्ण

	cpumask_set_cpu(cpu, &cpus_in_xmon);

 रुकोing:
	secondary = 1;
	spin_begin();
	जबतक (secondary && !xmon_gate) अणु
		अगर (in_xmon == 0) अणु
			अगर (fromipi) अणु
				spin_end();
				जाओ leave;
			पूर्ण
			secondary = test_and_set_bit(0, &in_xmon);
		पूर्ण
		spin_cpu_relax();
		touch_nmi_watchकरोg();
	पूर्ण
	spin_end();

	अगर (!secondary && !xmon_gate) अणु
		/* we are the first cpu to come in */
		/* पूर्णांकerrupt other cpu(s) */
		पूर्णांक ncpus = num_online_cpus();

		xmon_owner = cpu;
		mb();
		अगर (ncpus > 1) अणु
			/*
			 * A प्रणाली reset (trap == 0x100) can be triggered on
			 * all CPUs, so when we come in via 0x100 try रुकोing
			 * क्रम the other CPUs to come in beक्रमe we send the
			 * debugger अवरोध (IPI). This is similar to
			 * crash_kexec_secondary().
			 */
			अगर (TRAP(regs) !=  INTERRUPT_SYSTEM_RESET || !रुको_क्रम_other_cpus(ncpus))
				smp_send_debugger_अवरोध();

			रुको_क्रम_other_cpus(ncpus);
		पूर्ण
		हटाओ_bpts();
		disable_surveillance();

		अगर (!locked_करोwn) अणु
			/* क्रम अवरोधpoपूर्णांक or single step, prपूर्णांक curr insn */
			अगर (bp || TRAP(regs) == INTERRUPT_TRACE)
				ppc_inst_dump(regs->nip, 1, 0);
			म_लिखो("enter ? for help\n");
		पूर्ण

		mb();
		xmon_gate = 1;
		barrier();
		touch_nmi_watchकरोg();
	पूर्ण

 cmdloop:
	जबतक (in_xmon) अणु
		अगर (secondary) अणु
			spin_begin();
			अगर (cpu == xmon_owner) अणु
				अगर (!test_and_set_bit(0, &xmon_taken)) अणु
					secondary = 0;
					spin_end();
					जारी;
				पूर्ण
				/* missed it */
				जबतक (cpu == xmon_owner)
					spin_cpu_relax();
			पूर्ण
			spin_cpu_relax();
			touch_nmi_watchकरोg();
		पूर्ण अन्यथा अणु
			अगर (!locked_करोwn)
				cmd = cmds(regs);
			अगर (locked_करोwn || cmd != 0) अणु
				/* निकासing xmon */
				insert_bpts();
				xmon_gate = 0;
				wmb();
				in_xmon = 0;
				अवरोध;
			पूर्ण
			/* have चयनed to some other cpu */
			secondary = 1;
		पूर्ण
	पूर्ण
 leave:
	cpumask_clear_cpu(cpu, &cpus_in_xmon);
	xmon_fault_jmp[cpu] = शून्य;
#अन्यथा
	/* UP is simple... */
	अगर (in_xmon) अणु
		म_लिखो("Exception %lx %s in xmon, returning to main loop\n",
		       regs->trap, getvecname(TRAP(regs)));
		दीर्घ_लाँघ(xmon_fault_jmp[0], 1);
	पूर्ण
	अगर (बनाओ_लाँघ(recurse_jmp) == 0) अणु
		xmon_fault_jmp[0] = recurse_jmp;
		in_xmon = 1;

		excprपूर्णांक(regs);
		bp = at_अवरोधpoपूर्णांक(regs->nip);
		अगर (bp) अणु
			म_लिखो("Stopped at breakpoint %tx (", BP_NUM(bp));
			xmon_prपूर्णांक_symbol(regs->nip, " ", ")\n");
		पूर्ण
		अगर (unrecoverable_excp(regs))
			म_लिखो("WARNING: exception is not recoverable, "
			       "can't continue\n");
		हटाओ_bpts();
		disable_surveillance();
		अगर (!locked_करोwn) अणु
			/* क्रम अवरोधpoपूर्णांक or single step, prपूर्णांक current insn */
			अगर (bp || TRAP(regs) == INTERRUPT_TRACE)
				ppc_inst_dump(regs->nip, 1, 0);
			म_लिखो("enter ? for help\n");
		पूर्ण
	पूर्ण

	अगर (!locked_करोwn)
		cmd = cmds(regs);

	insert_bpts();
	in_xmon = 0;
#पूर्ण_अगर

#अगर_घोषित CONFIG_BOOKE
	अगर (regs->msr & MSR_DE) अणु
		bp = at_अवरोधpoपूर्णांक(regs->nip);
		अगर (bp != शून्य) अणु
			regs->nip = (अचिन्हित दीर्घ) &bp->instr[0];
			atomic_inc(&bp->ref_count);
		पूर्ण
	पूर्ण
#अन्यथा
	अगर ((regs->msr & (MSR_IR|MSR_PR|MSR_64BIT)) == (MSR_IR|MSR_64BIT)) अणु
		bp = at_अवरोधpoपूर्णांक(regs->nip);
		अगर (bp != शून्य) अणु
			पूर्णांक stepped = emulate_step(regs, ppc_inst_पढ़ो(bp->instr));
			अगर (stepped == 0) अणु
				regs->nip = (अचिन्हित दीर्घ) &bp->instr[0];
				atomic_inc(&bp->ref_count);
			पूर्ण अन्यथा अगर (stepped < 0) अणु
				म_लिखो("Couldn't single-step %s instruction\n",
				    IS_RFID(ppc_inst_पढ़ो(bp->instr))? "rfid": "mtmsrd");
			पूर्ण
		पूर्ण
	पूर्ण
#पूर्ण_अगर
	अगर (locked_करोwn)
		clear_all_bpt();
	अन्यथा
		insert_cpu_bpts();

	xmon_touch_watchकरोgs();
	local_irq_restore(flags);

	वापस cmd != 'X' && cmd != खातापूर्ण;
पूर्ण

पूर्णांक xmon(काष्ठा pt_regs *excp)
अणु
	काष्ठा pt_regs regs;

	अगर (excp == शून्य) अणु
		ppc_save_regs(&regs);
		excp = &regs;
	पूर्ण

	वापस xmon_core(excp, 0);
पूर्ण
EXPORT_SYMBOL(xmon);

irqवापस_t xmon_irq(पूर्णांक irq, व्योम *d)
अणु
	अचिन्हित दीर्घ flags;
	local_irq_save(flags);
	म_लिखो("Keyboard interrupt\n");
	xmon(get_irq_regs());
	local_irq_restore(flags);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक xmon_bpt(काष्ठा pt_regs *regs)
अणु
	काष्ठा bpt *bp;
	अचिन्हित दीर्घ offset;

	अगर ((regs->msr & (MSR_IR|MSR_PR|MSR_64BIT)) != (MSR_IR|MSR_64BIT))
		वापस 0;

	/* Are we at the trap at bp->instr[1] क्रम some bp? */
	bp = in_अवरोधpoपूर्णांक_table(regs->nip, &offset);
	अगर (bp != शून्य && (offset == 4 || offset == 8)) अणु
		regs->nip = bp->address + offset;
		atomic_dec(&bp->ref_count);
		वापस 1;
	पूर्ण

	/* Are we at a अवरोधpoपूर्णांक? */
	bp = at_अवरोधpoपूर्णांक(regs->nip);
	अगर (!bp)
		वापस 0;

	xmon_core(regs, 0);

	वापस 1;
पूर्ण

अटल पूर्णांक xmon_sstep(काष्ठा pt_regs *regs)
अणु
	अगर (user_mode(regs))
		वापस 0;
	xmon_core(regs, 0);
	वापस 1;
पूर्ण

अटल पूर्णांक xmon_अवरोध_match(काष्ठा pt_regs *regs)
अणु
	पूर्णांक i;

	अगर ((regs->msr & (MSR_IR|MSR_PR|MSR_64BIT)) != (MSR_IR|MSR_64BIT))
		वापस 0;
	क्रम (i = 0; i < nr_wp_slots(); i++) अणु
		अगर (dabr[i].enabled)
			जाओ found;
	पूर्ण
	वापस 0;

found:
	xmon_core(regs, 0);
	वापस 1;
पूर्ण

अटल पूर्णांक xmon_iabr_match(काष्ठा pt_regs *regs)
अणु
	अगर ((regs->msr & (MSR_IR|MSR_PR|MSR_64BIT)) != (MSR_IR|MSR_64BIT))
		वापस 0;
	अगर (iabr == शून्य)
		वापस 0;
	xmon_core(regs, 0);
	वापस 1;
पूर्ण

अटल पूर्णांक xmon_ipi(काष्ठा pt_regs *regs)
अणु
#अगर_घोषित CONFIG_SMP
	अगर (in_xmon && !cpumask_test_cpu(smp_processor_id(), &cpus_in_xmon))
		xmon_core(regs, 1);
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल पूर्णांक xmon_fault_handler(काष्ठा pt_regs *regs)
अणु
	काष्ठा bpt *bp;
	अचिन्हित दीर्घ offset;

	अगर (in_xmon && catch_memory_errors)
		handle_fault(regs);	/* करोesn't वापस */

	अगर ((regs->msr & (MSR_IR|MSR_PR|MSR_64BIT)) == (MSR_IR|MSR_64BIT)) अणु
		bp = in_अवरोधpoपूर्णांक_table(regs->nip, &offset);
		अगर (bp != शून्य) अणु
			regs->nip = bp->address + offset;
			atomic_dec(&bp->ref_count);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/* Force enable xmon अगर not alपढ़ोy enabled */
अटल अंतरभूत व्योम क्रमce_enable_xmon(व्योम)
अणु
	/* Enable xmon hooks अगर needed */
	अगर (!xmon_on) अणु
		म_लिखो("xmon: Enabling debugger hooks\n");
		xmon_on = 1;
	पूर्ण
पूर्ण

अटल काष्ठा bpt *at_अवरोधpoपूर्णांक(अचिन्हित दीर्घ pc)
अणु
	पूर्णांक i;
	काष्ठा bpt *bp;

	bp = bpts;
	क्रम (i = 0; i < NBPTS; ++i, ++bp)
		अगर (bp->enabled && pc == bp->address)
			वापस bp;
	वापस शून्य;
पूर्ण

अटल काष्ठा bpt *in_अवरोधpoपूर्णांक_table(अचिन्हित दीर्घ nip, अचिन्हित दीर्घ *offp)
अणु
	अचिन्हित दीर्घ off;

	off = nip - (अचिन्हित दीर्घ)bpt_table;
	अगर (off >= माप(bpt_table))
		वापस शून्य;
	*offp = off & (BPT_SIZE - 1);
	अगर (off & 3)
		वापस शून्य;
	वापस bpts + (off / BPT_SIZE);
पूर्ण

अटल काष्ठा bpt *new_अवरोधpoपूर्णांक(अचिन्हित दीर्घ a)
अणु
	काष्ठा bpt *bp;

	a &= ~3UL;
	bp = at_अवरोधpoपूर्णांक(a);
	अगर (bp)
		वापस bp;

	क्रम (bp = bpts; bp < &bpts[NBPTS]; ++bp) अणु
		अगर (!bp->enabled && atomic_पढ़ो(&bp->ref_count) == 0) अणु
			bp->address = a;
			bp->instr = (व्योम *)(bpt_table + ((bp - bpts) * BPT_WORDS));
			वापस bp;
		पूर्ण
	पूर्ण

	म_लिखो("Sorry, no free breakpoints.  Please clear one first.\n");
	वापस शून्य;
पूर्ण

अटल व्योम insert_bpts(व्योम)
अणु
	पूर्णांक i;
	काष्ठा ppc_inst instr, instr2;
	काष्ठा bpt *bp, *bp2;

	bp = bpts;
	क्रम (i = 0; i < NBPTS; ++i, ++bp) अणु
		अगर ((bp->enabled & (BP_TRAP|BP_CIABR)) == 0)
			जारी;
		अगर (!mपढ़ो_instr(bp->address, &instr)) अणु
			म_लिखो("Couldn't read instruction at %lx, "
			       "disabling breakpoint there\n", bp->address);
			bp->enabled = 0;
			जारी;
		पूर्ण
		अगर (IS_MTMSRD(instr) || IS_RFID(instr)) अणु
			म_लिखो("Breakpoint at %lx is on an mtmsrd or rfid "
			       "instruction, disabling it\n", bp->address);
			bp->enabled = 0;
			जारी;
		पूर्ण
		/*
		 * Check the address is not a suffix by looking क्रम a prefix in
		 * front of it.
		 */
		अगर (mपढ़ो_instr(bp->address - 4, &instr2) == 8) अणु
			म_लिखो("Breakpoint at %lx is on the second word of a prefixed instruction, disabling it\n",
			       bp->address);
			bp->enabled = 0;
			जारी;
		पूर्ण
		/*
		 * We might still be a suffix - अगर the prefix has alपढ़ोy been
		 * replaced by a अवरोधpoपूर्णांक we won't catch it with the above
		 * test.
		 */
		bp2 = at_अवरोधpoपूर्णांक(bp->address - 4);
		अगर (bp2 && ppc_inst_prefixed(ppc_inst_पढ़ो(bp2->instr))) अणु
			म_लिखो("Breakpoint at %lx is on the second word of a prefixed instruction, disabling it\n",
			       bp->address);
			bp->enabled = 0;
			जारी;
		पूर्ण

		patch_inकाष्ठाion(bp->instr, instr);
		patch_inकाष्ठाion(ppc_inst_next(bp->instr, &instr),
				  ppc_inst(bpinstr));
		अगर (bp->enabled & BP_CIABR)
			जारी;
		अगर (patch_inकाष्ठाion((काष्ठा ppc_inst *)bp->address,
				      ppc_inst(bpinstr)) != 0) अणु
			म_लिखो("Couldn't write instruction at %lx, "
			       "disabling breakpoint there\n", bp->address);
			bp->enabled &= ~BP_TRAP;
			जारी;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम insert_cpu_bpts(व्योम)
अणु
	पूर्णांक i;
	काष्ठा arch_hw_अवरोधpoपूर्णांक brk;

	क्रम (i = 0; i < nr_wp_slots(); i++) अणु
		अगर (dabr[i].enabled) अणु
			brk.address = dabr[i].address;
			brk.type = (dabr[i].enabled & HW_BRK_TYPE_DABR) | HW_BRK_TYPE_PRIV_ALL;
			brk.len = 8;
			brk.hw_len = 8;
			__set_अवरोधpoपूर्णांक(i, &brk);
		पूर्ण
	पूर्ण

	अगर (iabr)
		set_ciabr(iabr->address);
पूर्ण

अटल व्योम हटाओ_bpts(व्योम)
अणु
	पूर्णांक i;
	काष्ठा bpt *bp;
	काष्ठा ppc_inst instr;

	bp = bpts;
	क्रम (i = 0; i < NBPTS; ++i, ++bp) अणु
		अगर ((bp->enabled & (BP_TRAP|BP_CIABR)) != BP_TRAP)
			जारी;
		अगर (mपढ़ो_instr(bp->address, &instr)
		    && ppc_inst_equal(instr, ppc_inst(bpinstr))
		    && patch_inकाष्ठाion(
			(काष्ठा ppc_inst *)bp->address, ppc_inst_पढ़ो(bp->instr)) != 0)
			म_लिखो("Couldn't remove breakpoint at %lx\n",
			       bp->address);
	पूर्ण
पूर्ण

अटल व्योम हटाओ_cpu_bpts(व्योम)
अणु
	hw_अवरोधpoपूर्णांक_disable();
	ग_लिखो_ciabr(0);
पूर्ण

/* Based on upसमय_proc_show(). */
अटल व्योम
show_upसमय(व्योम)
अणु
	काष्ठा बारpec64 upसमय;

	अगर (बनाओ_लाँघ(bus_error_jmp) == 0) अणु
		catch_memory_errors = 1;
		sync();

		kसमय_get_coarse_bootसमय_प्रकारs64(&upसमय);
		म_लिखो("Uptime: %lu.%.2lu seconds\n", (अचिन्हित दीर्घ)upसमय.tv_sec,
			((अचिन्हित दीर्घ)upसमय.tv_nsec / (NSEC_PER_SEC/100)));

		sync();
		__delay(200);						\
	पूर्ण
	catch_memory_errors = 0;
पूर्ण

अटल व्योम set_lpp_cmd(व्योम)
अणु
	अचिन्हित दीर्घ lpp;

	अगर (!scanhex(&lpp)) अणु
		म_लिखो("Invalid number.\n");
		lpp = 0;
	पूर्ण
	xmon_set_pagination_lpp(lpp);
पूर्ण
/* Command पूर्णांकerpreting routine */
अटल अक्षर *last_cmd;

अटल पूर्णांक
cmds(काष्ठा pt_regs *excp)
अणु
	पूर्णांक cmd = 0;

	last_cmd = शून्य;
	xmon_regs = excp;

	xmon_show_stack(excp->gpr[1], excp->link, excp->nip);

	क्रम(;;) अणु
#अगर_घोषित CONFIG_SMP
		म_लिखो("%x:", smp_processor_id());
#पूर्ण_अगर /* CONFIG_SMP */
		म_लिखो("mon> ");
		flush_input();
		termch = 0;
		cmd = skipbl();
		अगर( cmd == '\n' ) अणु
			अगर (last_cmd == शून्य)
				जारी;
			take_input(last_cmd);
			last_cmd = शून्य;
			cmd = inअक्षर();
		पूर्ण
		चयन (cmd) अणु
		हाल 'm':
			cmd = inअक्षर();
			चयन (cmd) अणु
			हाल 'm':
			हाल 's':
			हाल 'd':
				memops(cmd);
				अवरोध;
			हाल 'l':
				memlocate();
				अवरोध;
			हाल 'z':
				अगर (xmon_is_ro) अणु
					म_लिखो(xmon_ro_msg);
					अवरोध;
				पूर्ण
				memzcan();
				अवरोध;
			हाल 'i':
				show_mem(0, शून्य);
				अवरोध;
			शेष:
				termch = cmd;
				memex();
			पूर्ण
			अवरोध;
		हाल 'd':
			dump();
			अवरोध;
		हाल 'l':
			symbol_lookup();
			अवरोध;
		हाल 'r':
			prregs(excp);	/* prपूर्णांक regs */
			अवरोध;
		हाल 'e':
			excprपूर्णांक(excp);
			अवरोध;
		हाल 'S':
			super_regs();
			अवरोध;
		हाल 't':
			backtrace(excp);
			अवरोध;
		हाल 'f':
			cacheflush();
			अवरोध;
		हाल 's':
			अगर (करो_spu_cmd() == 0)
				अवरोध;
			अगर (करो_step(excp))
				वापस cmd;
			अवरोध;
		हाल 'x':
		हाल 'X':
			अगर (tracing_enabled)
				tracing_on();
			वापस cmd;
		हाल खातापूर्ण:
			म_लिखो(" <no input ...>\n");
			mdelay(2000);
			वापस cmd;
		हाल '?':
			xmon_माला_दो(help_string);
			अवरोध;
		हाल '#':
			set_lpp_cmd();
			अवरोध;
		हाल 'b':
			bpt_cmds();
			अवरोध;
		हाल 'C':
			csum();
			अवरोध;
		हाल 'c':
			अगर (cpu_cmd())
				वापस 0;
			अवरोध;
		हाल 'z':
			bootcmds();
			अवरोध;
		हाल 'p':
			अगर (xmon_is_ro) अणु
				म_लिखो(xmon_ro_msg);
				अवरोध;
			पूर्ण
			proccall();
			अवरोध;
		हाल 'P':
			show_tasks();
			अवरोध;
#अगर_घोषित CONFIG_PPC_BOOK3S
		हाल 'u':
			dump_segments();
			अवरोध;
#या_अगर defined(CONFIG_44x)
		हाल 'u':
			dump_tlb_44x();
			अवरोध;
#या_अगर defined(CONFIG_PPC_BOOK3E)
		हाल 'u':
			dump_tlb_book3e();
			अवरोध;
#पूर्ण_अगर
		हाल 'U':
			show_upसमय();
			अवरोध;
		शेष:
			म_लिखो("Unrecognized command: ");
			करो अणु
				अगर (' ' < cmd && cmd <= '~')
					अक्षर_दो(cmd);
				अन्यथा
					म_लिखो("\\x%x", cmd);
				cmd = inअक्षर();
			पूर्ण जबतक (cmd != '\n');
			म_लिखो(" (type ? for help)\n");
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_BOOKE
अटल पूर्णांक करो_step(काष्ठा pt_regs *regs)
अणु
	regs->msr |= MSR_DE;
	mtspr(SPRN_DBCR0, mfspr(SPRN_DBCR0) | DBCR0_IC | DBCR0_IDM);
	वापस 1;
पूर्ण
#अन्यथा
/*
 * Step a single inकाष्ठाion.
 * Some inकाष्ठाions we emulate, others we execute with MSR_SE set.
 */
अटल पूर्णांक करो_step(काष्ठा pt_regs *regs)
अणु
	काष्ठा ppc_inst instr;
	पूर्णांक stepped;

	क्रमce_enable_xmon();
	/* check we are in 64-bit kernel mode, translation enabled */
	अगर ((regs->msr & (MSR_64BIT|MSR_PR|MSR_IR)) == (MSR_64BIT|MSR_IR)) अणु
		अगर (mपढ़ो_instr(regs->nip, &instr)) अणु
			stepped = emulate_step(regs, instr);
			अगर (stepped < 0) अणु
				म_लिखो("Couldn't single-step %s instruction\n",
				       (IS_RFID(instr)? "rfid": "mtmsrd"));
				वापस 0;
			पूर्ण
			अगर (stepped > 0) अणु
				set_trap(regs, 0xd00);
				म_लिखो("stepped to ");
				xmon_prपूर्णांक_symbol(regs->nip, " ", "\n");
				ppc_inst_dump(regs->nip, 1, 0);
				वापस 0;
			पूर्ण
		पूर्ण
	पूर्ण
	regs->msr |= MSR_SE;
	वापस 1;
पूर्ण
#पूर्ण_अगर

अटल व्योम bootcmds(व्योम)
अणु
	अक्षर पंचांगp[64];
	पूर्णांक cmd;

	cmd = inअक्षर();
	अगर (cmd == 'r') अणु
		माला_लोtring(पंचांगp, 64);
		ppc_md.restart(पंचांगp);
	पूर्ण अन्यथा अगर (cmd == 'h') अणु
		ppc_md.halt();
	पूर्ण अन्यथा अगर (cmd == 'p') अणु
		अगर (pm_घातer_off)
			pm_घातer_off();
	पूर्ण
पूर्ण

अटल पूर्णांक cpu_cmd(व्योम)
अणु
#अगर_घोषित CONFIG_SMP
	अचिन्हित दीर्घ cpu, first_cpu, last_cpu;
	पूर्णांक समयout;

	अगर (!scanhex(&cpu)) अणु
		/* prपूर्णांक cpus रुकोing or in xmon */
		म_लिखो("cpus stopped:");
		last_cpu = first_cpu = NR_CPUS;
		क्रम_each_possible_cpu(cpu) अणु
			अगर (cpumask_test_cpu(cpu, &cpus_in_xmon)) अणु
				अगर (cpu == last_cpu + 1) अणु
					last_cpu = cpu;
				पूर्ण अन्यथा अणु
					अगर (last_cpu != first_cpu)
						म_लिखो("-0x%lx", last_cpu);
					last_cpu = first_cpu = cpu;
					म_लिखो(" 0x%lx", cpu);
				पूर्ण
			पूर्ण
		पूर्ण
		अगर (last_cpu != first_cpu)
			म_लिखो("-0x%lx", last_cpu);
		म_लिखो("\n");
		वापस 0;
	पूर्ण
	/* try to चयन to cpu specअगरied */
	अगर (!cpumask_test_cpu(cpu, &cpus_in_xmon)) अणु
		म_लिखो("cpu 0x%lx isn't in xmon\n", cpu);
#अगर_घोषित CONFIG_PPC64
		म_लिखो("backtrace of paca[0x%lx].saved_r1 (possibly stale):\n", cpu);
		xmon_show_stack(paca_ptrs[cpu]->saved_r1, 0, 0);
#पूर्ण_अगर
		वापस 0;
	पूर्ण
	xmon_taken = 0;
	mb();
	xmon_owner = cpu;
	समयout = 10000000;
	जबतक (!xmon_taken) अणु
		अगर (--समयout == 0) अणु
			अगर (test_and_set_bit(0, &xmon_taken))
				अवरोध;
			/* take control back */
			mb();
			xmon_owner = smp_processor_id();
			म_लिखो("cpu 0x%lx didn't take control\n", cpu);
			वापस 0;
		पूर्ण
		barrier();
	पूर्ण
	वापस 1;
#अन्यथा
	वापस 0;
#पूर्ण_अगर /* CONFIG_SMP */
पूर्ण

अटल अचिन्हित लघु fcstab[256] = अणु
	0x0000, 0x1189, 0x2312, 0x329b, 0x4624, 0x57ad, 0x6536, 0x74bf,
	0x8c48, 0x9dc1, 0xaf5a, 0xbed3, 0xca6c, 0xdbe5, 0xe97e, 0xf8f7,
	0x1081, 0x0108, 0x3393, 0x221a, 0x56a5, 0x472c, 0x75b7, 0x643e,
	0x9cc9, 0x8d40, 0xbfdb, 0xae52, 0xdaed, 0xcb64, 0xf9ff, 0xe876,
	0x2102, 0x308b, 0x0210, 0x1399, 0x6726, 0x76af, 0x4434, 0x55bd,
	0xad4a, 0xbcc3, 0x8e58, 0x9fd1, 0xeb6e, 0xfae7, 0xc87c, 0xd9f5,
	0x3183, 0x200a, 0x1291, 0x0318, 0x77a7, 0x662e, 0x54b5, 0x453c,
	0xbdcb, 0xac42, 0x9ed9, 0x8f50, 0xfbef, 0xea66, 0xd8fd, 0xc974,
	0x4204, 0x538d, 0x6116, 0x709f, 0x0420, 0x15a9, 0x2732, 0x36bb,
	0xce4c, 0xdfc5, 0xed5e, 0xfcd7, 0x8868, 0x99e1, 0xab7a, 0xbaf3,
	0x5285, 0x430c, 0x7197, 0x601e, 0x14a1, 0x0528, 0x37b3, 0x263a,
	0xdecd, 0xcf44, 0xfddf, 0xec56, 0x98e9, 0x8960, 0xbbfb, 0xaa72,
	0x6306, 0x728f, 0x4014, 0x519d, 0x2522, 0x34ab, 0x0630, 0x17b9,
	0xef4e, 0xfec7, 0xcc5c, 0xddd5, 0xa96a, 0xb8e3, 0x8a78, 0x9bf1,
	0x7387, 0x620e, 0x5095, 0x411c, 0x35a3, 0x242a, 0x16b1, 0x0738,
	0xffcf, 0xee46, 0xdcdd, 0xcd54, 0xb9eb, 0xa862, 0x9af9, 0x8b70,
	0x8408, 0x9581, 0xa71a, 0xb693, 0xc22c, 0xd3a5, 0xe13e, 0xf0b7,
	0x0840, 0x19c9, 0x2b52, 0x3adb, 0x4e64, 0x5fed, 0x6d76, 0x7cff,
	0x9489, 0x8500, 0xb79b, 0xa612, 0xd2ad, 0xc324, 0xf1bf, 0xe036,
	0x18c1, 0x0948, 0x3bd3, 0x2a5a, 0x5ee5, 0x4f6c, 0x7df7, 0x6c7e,
	0xa50a, 0xb483, 0x8618, 0x9791, 0xe32e, 0xf2a7, 0xc03c, 0xd1b5,
	0x2942, 0x38cb, 0x0a50, 0x1bd9, 0x6f66, 0x7eef, 0x4c74, 0x5dfd,
	0xb58b, 0xa402, 0x9699, 0x8710, 0xf3af, 0xe226, 0xd0bd, 0xc134,
	0x39c3, 0x284a, 0x1ad1, 0x0b58, 0x7fe7, 0x6e6e, 0x5cf5, 0x4d7c,
	0xc60c, 0xd785, 0xe51e, 0xf497, 0x8028, 0x91a1, 0xa33a, 0xb2b3,
	0x4a44, 0x5bcd, 0x6956, 0x78df, 0x0c60, 0x1de9, 0x2f72, 0x3efb,
	0xd68d, 0xc704, 0xf59f, 0xe416, 0x90a9, 0x8120, 0xb3bb, 0xa232,
	0x5ac5, 0x4b4c, 0x79d7, 0x685e, 0x1ce1, 0x0d68, 0x3ff3, 0x2e7a,
	0xe70e, 0xf687, 0xc41c, 0xd595, 0xa12a, 0xb0a3, 0x8238, 0x93b1,
	0x6b46, 0x7acf, 0x4854, 0x59dd, 0x2d62, 0x3ceb, 0x0e70, 0x1ff9,
	0xf78f, 0xe606, 0xd49d, 0xc514, 0xb1ab, 0xa022, 0x92b9, 0x8330,
	0x7bc7, 0x6a4e, 0x58d5, 0x495c, 0x3de3, 0x2c6a, 0x1ef1, 0x0f78
पूर्ण;

#घोषणा FCS(fcs, c)	(((fcs) >> 8) ^ fcstab[((fcs) ^ (c)) & 0xff])

अटल व्योम
csum(व्योम)
अणु
	अचिन्हित पूर्णांक i;
	अचिन्हित लघु fcs;
	अचिन्हित अक्षर v;

	अगर (!scanhex(&adrs))
		वापस;
	अगर (!scanhex(&ncsum))
		वापस;
	fcs = 0xffff;
	क्रम (i = 0; i < ncsum; ++i) अणु
		अगर (mपढ़ो(adrs+i, &v, 1) == 0) अणु
			म_लिखो("csum stopped at "REG"\n", adrs+i);
			अवरोध;
		पूर्ण
		fcs = FCS(fcs, v);
	पूर्ण
	म_लिखो("%x\n", fcs);
पूर्ण

/*
 * Check अगर this is a suitable place to put a अवरोधpoपूर्णांक.
 */
अटल दीर्घ check_bp_loc(अचिन्हित दीर्घ addr)
अणु
	काष्ठा ppc_inst instr;

	addr &= ~3;
	अगर (!is_kernel_addr(addr)) अणु
		म_लिखो("Breakpoints may only be placed at kernel addresses\n");
		वापस 0;
	पूर्ण
	अगर (!mपढ़ो_instr(addr, &instr)) अणु
		म_लिखो("Can't read instruction at address %lx\n", addr);
		वापस 0;
	पूर्ण
	अगर (IS_MTMSRD(instr) || IS_RFID(instr)) अणु
		म_लिखो("Breakpoints may not be placed on mtmsrd or rfid "
		       "instructions\n");
		वापस 0;
	पूर्ण
	वापस 1;
पूर्ण

अटल पूर्णांक find_मुक्त_data_bpt(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < nr_wp_slots(); i++) अणु
		अगर (!dabr[i].enabled)
			वापस i;
	पूर्ण
	म_लिखो("Couldn't find free breakpoint register\n");
	वापस -1;
पूर्ण

अटल व्योम prपूर्णांक_data_bpts(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < nr_wp_slots(); i++) अणु
		अगर (!dabr[i].enabled)
			जारी;

		म_लिखो("   data   "REG"  [", dabr[i].address);
		अगर (dabr[i].enabled & 1)
			म_लिखो("r");
		अगर (dabr[i].enabled & 2)
			म_लिखो("w");
		म_लिखो("]\n");
	पूर्ण
पूर्ण

अटल अक्षर *अवरोधpoपूर्णांक_help_string =
    "Breakpoint command usage:\n"
    "b                show breakpoints\n"
    "b <addr> [cnt]   set breakpoint at given instr addr\n"
    "bc               clear all breakpoints\n"
    "bc <n/addr>      clear breakpoint number n or at addr\n"
    "bi <addr> [cnt]  set hardware instr breakpoint (POWER8 only)\n"
    "bd <addr> [cnt]  set hardware data breakpoint\n"
    "";

अटल व्योम
bpt_cmds(व्योम)
अणु
	पूर्णांक cmd;
	अचिन्हित दीर्घ a;
	पूर्णांक i;
	काष्ठा bpt *bp;

	cmd = inअक्षर();

	चयन (cmd) अणु
	अटल स्थिर अक्षर badaddr[] = "Only kernel addresses are permitted for breakpoints\n";
	पूर्णांक mode;
	हाल 'd':	/* bd - hardware data अवरोधpoपूर्णांक */
		अगर (xmon_is_ro) अणु
			म_लिखो(xmon_ro_msg);
			अवरोध;
		पूर्ण
		अगर (!ppc_अवरोधpoपूर्णांक_available()) अणु
			म_लिखो("Hardware data breakpoint not supported on this cpu\n");
			अवरोध;
		पूर्ण
		i = find_मुक्त_data_bpt();
		अगर (i < 0)
			अवरोध;
		mode = 7;
		cmd = inअक्षर();
		अगर (cmd == 'r')
			mode = 5;
		अन्यथा अगर (cmd == 'w')
			mode = 6;
		अन्यथा
			termch = cmd;
		dabr[i].address = 0;
		dabr[i].enabled = 0;
		अगर (scanhex(&dabr[i].address)) अणु
			अगर (!is_kernel_addr(dabr[i].address)) अणु
				म_लिखो(badaddr);
				अवरोध;
			पूर्ण
			dabr[i].address &= ~HW_BRK_TYPE_DABR;
			dabr[i].enabled = mode | BP_DABR;
		पूर्ण

		क्रमce_enable_xmon();
		अवरोध;

	हाल 'i':	/* bi - hardware instr अवरोधpoपूर्णांक */
		अगर (xmon_is_ro) अणु
			म_लिखो(xmon_ro_msg);
			अवरोध;
		पूर्ण
		अगर (!cpu_has_feature(CPU_FTR_ARCH_207S)) अणु
			म_लिखो("Hardware instruction breakpoint "
			       "not supported on this cpu\n");
			अवरोध;
		पूर्ण
		अगर (iabr) अणु
			iabr->enabled &= ~BP_CIABR;
			iabr = शून्य;
		पूर्ण
		अगर (!scanhex(&a))
			अवरोध;
		अगर (!check_bp_loc(a))
			अवरोध;
		bp = new_अवरोधpoपूर्णांक(a);
		अगर (bp != शून्य) अणु
			bp->enabled |= BP_CIABR;
			iabr = bp;
			क्रमce_enable_xmon();
		पूर्ण
		अवरोध;

	हाल 'c':
		अगर (!scanhex(&a)) अणु
			/* clear all अवरोधpoपूर्णांकs */
			क्रम (i = 0; i < NBPTS; ++i)
				bpts[i].enabled = 0;
			iabr = शून्य;
			क्रम (i = 0; i < nr_wp_slots(); i++)
				dabr[i].enabled = 0;

			म_लिखो("All breakpoints cleared\n");
			अवरोध;
		पूर्ण

		अगर (a <= NBPTS && a >= 1) अणु
			/* assume a अवरोधpoपूर्णांक number */
			bp = &bpts[a-1];	/* bp nums are 1 based */
		पूर्ण अन्यथा अणु
			/* assume a अवरोधpoपूर्णांक address */
			bp = at_अवरोधpoपूर्णांक(a);
			अगर (bp == शून्य) अणु
				म_लिखो("No breakpoint at %lx\n", a);
				अवरोध;
			पूर्ण
		पूर्ण

		म_लिखो("Cleared breakpoint %tx (", BP_NUM(bp));
		xmon_prपूर्णांक_symbol(bp->address, " ", ")\n");
		bp->enabled = 0;
		अवरोध;

	शेष:
		termch = cmd;
		cmd = skipbl();
		अगर (cmd == '?') अणु
			म_लिखो(अवरोधpoपूर्णांक_help_string);
			अवरोध;
		पूर्ण
		termch = cmd;

		अगर (xmon_is_ro || !scanhex(&a)) अणु
			/* prपूर्णांक all अवरोधpoपूर्णांकs */
			म_लिखो("   type            address\n");
			prपूर्णांक_data_bpts();
			क्रम (bp = bpts; bp < &bpts[NBPTS]; ++bp) अणु
				अगर (!bp->enabled)
					जारी;
				म_लिखो("%tx %s   ", BP_NUM(bp),
				    (bp->enabled & BP_CIABR) ? "inst": "trap");
				xmon_prपूर्णांक_symbol(bp->address, "  ", "\n");
			पूर्ण
			अवरोध;
		पूर्ण

		अगर (!check_bp_loc(a))
			अवरोध;
		bp = new_अवरोधpoपूर्णांक(a);
		अगर (bp != शून्य) अणु
			bp->enabled |= BP_TRAP;
			क्रमce_enable_xmon();
		पूर्ण
		अवरोध;
	पूर्ण
पूर्ण

/* Very cheap human name क्रम vector lookup. */
अटल
स्थिर अक्षर *getvecname(अचिन्हित दीर्घ vec)
अणु
	अक्षर *ret;

	चयन (vec) अणु
	हाल 0x100:	ret = "(System Reset)"; अवरोध;
	हाल 0x200:	ret = "(Machine Check)"; अवरोध;
	हाल 0x300:	ret = "(Data Access)"; अवरोध;
	हाल 0x380:
		अगर (radix_enabled())
			ret = "(Data Access Out of Range)";
		अन्यथा
			ret = "(Data SLB Access)";
		अवरोध;
	हाल 0x400:	ret = "(Instruction Access)"; अवरोध;
	हाल 0x480:
		अगर (radix_enabled())
			ret = "(Instruction Access Out of Range)";
		अन्यथा
			ret = "(Instruction SLB Access)";
		अवरोध;
	हाल 0x500:	ret = "(Hardware Interrupt)"; अवरोध;
	हाल 0x600:	ret = "(Alignment)"; अवरोध;
	हाल 0x700:	ret = "(Program Check)"; अवरोध;
	हाल 0x800:	ret = "(FPU Unavailable)"; अवरोध;
	हाल 0x900:	ret = "(Decrementer)"; अवरोध;
	हाल 0x980:	ret = "(Hypervisor Decrementer)"; अवरोध;
	हाल 0xa00:	ret = "(Doorbell)"; अवरोध;
	हाल 0xc00:	ret = "(System Call)"; अवरोध;
	हाल 0xd00:	ret = "(Single Step)"; अवरोध;
	हाल 0xe40:	ret = "(Emulation Assist)"; अवरोध;
	हाल 0xe60:	ret = "(HMI)"; अवरोध;
	हाल 0xe80:	ret = "(Hypervisor Doorbell)"; अवरोध;
	हाल 0xf00:	ret = "(Performance Monitor)"; अवरोध;
	हाल 0xf20:	ret = "(Altivec Unavailable)"; अवरोध;
	हाल 0x1300:	ret = "(Instruction Breakpoint)"; अवरोध;
	हाल 0x1500:	ret = "(Denormalisation)"; अवरोध;
	हाल 0x1700:	ret = "(Altivec Assist)"; अवरोध;
	हाल 0x3000:	ret = "(System Call Vectored)"; अवरोध;
	शेष: ret = "";
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम get_function_bounds(अचिन्हित दीर्घ pc, अचिन्हित दीर्घ *startp,
				अचिन्हित दीर्घ *endp)
अणु
	अचिन्हित दीर्घ size, offset;
	स्थिर अक्षर *name;

	*startp = *endp = 0;
	अगर (pc == 0)
		वापस;
	अगर (बनाओ_लाँघ(bus_error_jmp) == 0) अणु
		catch_memory_errors = 1;
		sync();
		name = kallsyms_lookup(pc, &size, &offset, शून्य, पंचांगpstr);
		अगर (name != शून्य) अणु
			*startp = pc - offset;
			*endp = pc - offset + size;
		पूर्ण
		sync();
	पूर्ण
	catch_memory_errors = 0;
पूर्ण

#घोषणा LRSAVE_OFFSET		(STACK_FRAME_LR_SAVE * माप(अचिन्हित दीर्घ))
#घोषणा MARKER_OFFSET		(STACK_FRAME_MARKER * माप(अचिन्हित दीर्घ))

अटल व्योम xmon_show_stack(अचिन्हित दीर्घ sp, अचिन्हित दीर्घ lr,
			    अचिन्हित दीर्घ pc)
अणु
	पूर्णांक max_to_prपूर्णांक = 64;
	अचिन्हित दीर्घ ip;
	अचिन्हित दीर्घ newsp;
	अचिन्हित दीर्घ marker;
	काष्ठा pt_regs regs;

	जबतक (max_to_prपूर्णांक--) अणु
		अगर (!is_kernel_addr(sp)) अणु
			अगर (sp != 0)
				म_लिखो("SP (%lx) is in userspace\n", sp);
			अवरोध;
		पूर्ण

		अगर (!mपढ़ो(sp + LRSAVE_OFFSET, &ip, माप(अचिन्हित दीर्घ))
		    || !mपढ़ो(sp, &newsp, माप(अचिन्हित दीर्घ))) अणु
			म_लिखो("Couldn't read stack frame at %lx\n", sp);
			अवरोध;
		पूर्ण

		/*
		 * For the first stack frame, try to work out अगर
		 * LR and/or the saved LR value in the bottommost
		 * stack frame are valid.
		 */
		अगर ((pc | lr) != 0) अणु
			अचिन्हित दीर्घ fnstart, fnend;
			अचिन्हित दीर्घ nextip;
			पूर्णांक prपूर्णांकip = 1;

			get_function_bounds(pc, &fnstart, &fnend);
			nextip = 0;
			अगर (newsp > sp)
				mपढ़ो(newsp + LRSAVE_OFFSET, &nextip,
				      माप(अचिन्हित दीर्घ));
			अगर (lr == ip) अणु
				अगर (!is_kernel_addr(lr)
				    || (fnstart <= lr && lr < fnend))
					prपूर्णांकip = 0;
			पूर्ण अन्यथा अगर (lr == nextip) अणु
				prपूर्णांकip = 0;
			पूर्ण अन्यथा अगर (is_kernel_addr(lr)
				   && !(fnstart <= lr && lr < fnend)) अणु
				म_लिखो("[link register   ] ");
				xmon_prपूर्णांक_symbol(lr, " ", "\n");
			पूर्ण
			अगर (prपूर्णांकip) अणु
				म_लिखो("["REG"] ", sp);
				xmon_prपूर्णांक_symbol(ip, " ", " (unreliable)\n");
			पूर्ण
			pc = lr = 0;

		पूर्ण अन्यथा अणु
			म_लिखो("["REG"] ", sp);
			xmon_prपूर्णांक_symbol(ip, " ", "\n");
		पूर्ण

		/* Look क्रम "regshere" marker to see अगर this is
		   an exception frame. */
		अगर (mपढ़ो(sp + MARKER_OFFSET, &marker, माप(अचिन्हित दीर्घ))
		    && marker == STACK_FRAME_REGS_MARKER) अणु
			अगर (mपढ़ो(sp + STACK_FRAME_OVERHEAD, &regs, माप(regs))
			    != माप(regs)) अणु
				म_लिखो("Couldn't read registers at %lx\n",
				       sp + STACK_FRAME_OVERHEAD);
				अवरोध;
			पूर्ण
			म_लिखो("--- Exception: %lx %s at ", regs.trap,
			       getvecname(TRAP(&regs)));
			pc = regs.nip;
			lr = regs.link;
			xmon_prपूर्णांक_symbol(pc, " ", "\n");
		पूर्ण

		अगर (newsp == 0)
			अवरोध;

		sp = newsp;
	पूर्ण
पूर्ण

अटल व्योम backtrace(काष्ठा pt_regs *excp)
अणु
	अचिन्हित दीर्घ sp;

	अगर (scanhex(&sp))
		xmon_show_stack(sp, 0, 0);
	अन्यथा
		xmon_show_stack(excp->gpr[1], excp->link, excp->nip);
	scannl();
पूर्ण

अटल व्योम prपूर्णांक_bug_trap(काष्ठा pt_regs *regs)
अणु
#अगर_घोषित CONFIG_BUG
	स्थिर काष्ठा bug_entry *bug;
	अचिन्हित दीर्घ addr;

	अगर (regs->msr & MSR_PR)
		वापस;		/* not in kernel */
	addr = regs->nip;	/* address of trap inकाष्ठाion */
	अगर (!is_kernel_addr(addr))
		वापस;
	bug = find_bug(regs->nip);
	अगर (bug == शून्य)
		वापस;
	अगर (is_warning_bug(bug))
		वापस;

#अगर_घोषित CONFIG_DEBUG_BUGVERBOSE
	म_लिखो("kernel BUG at %s:%u!\n",
	       (अक्षर *)bug + bug->file_disp, bug->line);
#अन्यथा
	म_लिखो("kernel BUG at %px!\n", (व्योम *)bug + bug->bug_addr_disp);
#पूर्ण_अगर
#पूर्ण_अगर /* CONFIG_BUG */
पूर्ण

अटल व्योम excprपूर्णांक(काष्ठा pt_regs *fp)
अणु
	अचिन्हित दीर्घ trap;

#अगर_घोषित CONFIG_SMP
	म_लिखो("cpu 0x%x: ", smp_processor_id());
#पूर्ण_अगर /* CONFIG_SMP */

	trap = TRAP(fp);
	म_लिखो("Vector: %lx %s at [%px]\n", fp->trap, getvecname(trap), fp);
	म_लिखो("    pc: ");
	xmon_prपूर्णांक_symbol(fp->nip, ": ", "\n");

	म_लिखो("    lr: ");
	xmon_prपूर्णांक_symbol(fp->link, ": ", "\n");

	म_लिखो("    sp: %lx\n", fp->gpr[1]);
	म_लिखो("   msr: %lx\n", fp->msr);

	अगर (trap == INTERRUPT_DATA_STORAGE ||
	    trap == INTERRUPT_DATA_SEGMENT ||
	    trap == INTERRUPT_ALIGNMENT ||
	    trap == INTERRUPT_MACHINE_CHECK) अणु
		म_लिखो("   dar: %lx\n", fp->dar);
		अगर (trap != INTERRUPT_DATA_SEGMENT)
			म_लिखो(" dsisr: %lx\n", fp->dsisr);
	पूर्ण

	म_लिखो("  current = 0x%px\n", current);
#अगर_घोषित CONFIG_PPC64
	म_लिखो("  paca    = 0x%px\t irqmask: 0x%02x\t irq_happened: 0x%02x\n",
	       local_paca, local_paca->irq_soft_mask, local_paca->irq_happened);
#पूर्ण_अगर
	अगर (current) अणु
		म_लिखो("    pid   = %d, comm = %s\n",
		       current->pid, current->comm);
	पूर्ण

	अगर (trap == INTERRUPT_PROGRAM)
		prपूर्णांक_bug_trap(fp);

	म_लिखो(linux_banner);
पूर्ण

अटल व्योम prregs(काष्ठा pt_regs *fp)
अणु
	पूर्णांक n, trap;
	अचिन्हित दीर्घ base;
	काष्ठा pt_regs regs;

	अगर (scanhex(&base)) अणु
		अगर (बनाओ_लाँघ(bus_error_jmp) == 0) अणु
			catch_memory_errors = 1;
			sync();
			regs = *(काष्ठा pt_regs *)base;
			sync();
			__delay(200);
		पूर्ण अन्यथा अणु
			catch_memory_errors = 0;
			म_लिखो("*** Error reading registers from "REG"\n",
			       base);
			वापस;
		पूर्ण
		catch_memory_errors = 0;
		fp = &regs;
	पूर्ण

#अगर_घोषित CONFIG_PPC64
#घोषणा R_PER_LINE 2
#अन्यथा
#घोषणा R_PER_LINE 4
#पूर्ण_अगर

	क्रम (n = 0; n < 32; ++n) अणु
		म_लिखो("R%.2d = "REG"%s", n, fp->gpr[n],
			(n % R_PER_LINE) == R_PER_LINE - 1 ? "\n" : "   ");
	पूर्ण

	म_लिखो("pc  = ");
	xmon_prपूर्णांक_symbol(fp->nip, " ", "\n");
	अगर (!trap_is_syscall(fp) && cpu_has_feature(CPU_FTR_CFAR)) अणु
		म_लिखो("cfar= ");
		xmon_prपूर्णांक_symbol(fp->orig_gpr3, " ", "\n");
	पूर्ण
	म_लिखो("lr  = ");
	xmon_prपूर्णांक_symbol(fp->link, " ", "\n");
	म_लिखो("msr = "REG"   cr  = %.8lx\n", fp->msr, fp->ccr);
	म_लिखो("ctr = "REG"   xer = "REG"   trap = %4lx\n",
	       fp->ctr, fp->xer, fp->trap);
	trap = TRAP(fp);
	अगर (trap == INTERRUPT_DATA_STORAGE ||
	    trap == INTERRUPT_DATA_SEGMENT ||
	    trap == INTERRUPT_ALIGNMENT)
		म_लिखो("dar = "REG"   dsisr = %.8lx\n", fp->dar, fp->dsisr);
पूर्ण

अटल व्योम cacheflush(व्योम)
अणु
	पूर्णांक cmd;
	अचिन्हित दीर्घ nflush;

	cmd = inअक्षर();
	अगर (cmd != 'i')
		termch = cmd;
	scanhex((व्योम *)&adrs);
	अगर (termch != '\n')
		termch = 0;
	nflush = 1;
	scanhex(&nflush);
	nflush = (nflush + L1_CACHE_BYTES - 1) / L1_CACHE_BYTES;
	अगर (बनाओ_लाँघ(bus_error_jmp) == 0) अणु
		catch_memory_errors = 1;
		sync();

		अगर (cmd != 'i' || IS_ENABLED(CONFIG_PPC_BOOK3S_64)) अणु
			क्रम (; nflush > 0; --nflush, adrs += L1_CACHE_BYTES)
				cflush((व्योम *) adrs);
		पूर्ण अन्यथा अणु
			क्रम (; nflush > 0; --nflush, adrs += L1_CACHE_BYTES)
				cinval((व्योम *) adrs);
		पूर्ण
		sync();
		/* रुको a little जबतक to see अगर we get a machine check */
		__delay(200);
	पूर्ण
	catch_memory_errors = 0;
पूर्ण

बाह्य अचिन्हित दीर्घ xmon_mfspr(पूर्णांक spr, अचिन्हित दीर्घ शेष_value);
बाह्य व्योम xmon_mtspr(पूर्णांक spr, अचिन्हित दीर्घ value);

अटल पूर्णांक
पढ़ो_spr(पूर्णांक n, अचिन्हित दीर्घ *vp)
अणु
	अचिन्हित दीर्घ ret = -1UL;
	पूर्णांक ok = 0;

	अगर (बनाओ_लाँघ(bus_error_jmp) == 0) अणु
		catch_spr_faults = 1;
		sync();

		ret = xmon_mfspr(n, *vp);

		sync();
		*vp = ret;
		ok = 1;
	पूर्ण
	catch_spr_faults = 0;

	वापस ok;
पूर्ण

अटल व्योम
ग_लिखो_spr(पूर्णांक n, अचिन्हित दीर्घ val)
अणु
	अगर (xmon_is_ro) अणु
		म_लिखो(xmon_ro_msg);
		वापस;
	पूर्ण

	अगर (बनाओ_लाँघ(bus_error_jmp) == 0) अणु
		catch_spr_faults = 1;
		sync();

		xmon_mtspr(n, val);

		sync();
	पूर्ण अन्यथा अणु
		म_लिखो("SPR 0x%03x (%4d) Faulted during write\n", n, n);
	पूर्ण
	catch_spr_faults = 0;
पूर्ण

अटल व्योम dump_206_sprs(व्योम)
अणु
#अगर_घोषित CONFIG_PPC64
	अगर (!cpu_has_feature(CPU_FTR_ARCH_206))
		वापस;

	/* Actually some of these pre-date 2.06, but whatevs */

	म_लिखो("srr0   = %.16lx  srr1  = %.16lx dsisr  = %.8lx\n",
		mfspr(SPRN_SRR0), mfspr(SPRN_SRR1), mfspr(SPRN_DSISR));
	म_लिखो("dscr   = %.16lx  ppr   = %.16lx pir    = %.8lx\n",
		mfspr(SPRN_DSCR), mfspr(SPRN_PPR), mfspr(SPRN_PIR));
	म_लिखो("amr    = %.16lx  uamor = %.16lx\n",
		mfspr(SPRN_AMR), mfspr(SPRN_UAMOR));

	अगर (!(mfmsr() & MSR_HV))
		वापस;

	म_लिखो("sdr1   = %.16lx  hdar  = %.16lx hdsisr = %.8lx\n",
		mfspr(SPRN_SDR1), mfspr(SPRN_HDAR), mfspr(SPRN_HDSISR));
	म_लिखो("hsrr0  = %.16lx hsrr1  = %.16lx hdec   = %.16lx\n",
		mfspr(SPRN_HSRR0), mfspr(SPRN_HSRR1), mfspr(SPRN_HDEC));
	म_लिखो("lpcr   = %.16lx  pcr   = %.16lx lpidr  = %.8lx\n",
		mfspr(SPRN_LPCR), mfspr(SPRN_PCR), mfspr(SPRN_LPID));
	म_लिखो("hsprg0 = %.16lx hsprg1 = %.16lx amor   = %.16lx\n",
		mfspr(SPRN_HSPRG0), mfspr(SPRN_HSPRG1), mfspr(SPRN_AMOR));
	म_लिखो("dabr   = %.16lx dabrx  = %.16lx\n",
		mfspr(SPRN_DABR), mfspr(SPRN_DABRX));
#पूर्ण_अगर
पूर्ण

अटल व्योम dump_207_sprs(व्योम)
अणु
#अगर_घोषित CONFIG_PPC64
	अचिन्हित दीर्घ msr;

	अगर (!cpu_has_feature(CPU_FTR_ARCH_207S))
		वापस;

	म_लिखो("dpdes  = %.16lx  tir   = %.16lx cir    = %.8lx\n",
		mfspr(SPRN_DPDES), mfspr(SPRN_TIR), mfspr(SPRN_CIR));

	म_लिखो("fscr   = %.16lx  tar   = %.16lx pspb   = %.8lx\n",
		mfspr(SPRN_FSCR), mfspr(SPRN_TAR), mfspr(SPRN_PSPB));

	msr = mfmsr();
	अगर (msr & MSR_TM) अणु
		/* Only अगर TM has been enabled in the kernel */
		म_लिखो("tfhar  = %.16lx  tfiar = %.16lx texasr = %.16lx\n",
			mfspr(SPRN_TFHAR), mfspr(SPRN_TFIAR),
			mfspr(SPRN_TEXASR));
	पूर्ण

	म_लिखो("mmcr0  = %.16lx  mmcr1 = %.16lx mmcr2  = %.16lx\n",
		mfspr(SPRN_MMCR0), mfspr(SPRN_MMCR1), mfspr(SPRN_MMCR2));
	म_लिखो("pmc1   = %.8lx pmc2 = %.8lx  pmc3 = %.8lx  pmc4   = %.8lx\n",
		mfspr(SPRN_PMC1), mfspr(SPRN_PMC2),
		mfspr(SPRN_PMC3), mfspr(SPRN_PMC4));
	म_लिखो("mmcra  = %.16lx   siar = %.16lx pmc5   = %.8lx\n",
		mfspr(SPRN_MMCRA), mfspr(SPRN_SIAR), mfspr(SPRN_PMC5));
	म_लिखो("sdar   = %.16lx   sier = %.16lx pmc6   = %.8lx\n",
		mfspr(SPRN_SDAR), mfspr(SPRN_SIER), mfspr(SPRN_PMC6));
	म_लिखो("ebbhr  = %.16lx  ebbrr = %.16lx bescr  = %.16lx\n",
		mfspr(SPRN_EBBHR), mfspr(SPRN_EBBRR), mfspr(SPRN_BESCR));
	म_लिखो("iamr   = %.16lx\n", mfspr(SPRN_IAMR));

	अगर (!(msr & MSR_HV))
		वापस;

	म_लिखो("hfscr  = %.16lx  dhdes = %.16lx rpr    = %.16lx\n",
		mfspr(SPRN_HFSCR), mfspr(SPRN_DHDES), mfspr(SPRN_RPR));
	म_लिखो("dawr0  = %.16lx dawrx0 = %.16lx\n",
	       mfspr(SPRN_DAWR0), mfspr(SPRN_DAWRX0));
	अगर (nr_wp_slots() > 1) अणु
		म_लिखो("dawr1  = %.16lx dawrx1 = %.16lx\n",
		       mfspr(SPRN_DAWR1), mfspr(SPRN_DAWRX1));
	पूर्ण
	म_लिखो("ciabr  = %.16lx\n", mfspr(SPRN_CIABR));
#पूर्ण_अगर
पूर्ण

अटल व्योम dump_300_sprs(व्योम)
अणु
#अगर_घोषित CONFIG_PPC64
	bool hv = mfmsr() & MSR_HV;

	अगर (!cpu_has_feature(CPU_FTR_ARCH_300))
		वापस;

	म_लिखो("pidr   = %.16lx  tidr  = %.16lx\n",
		mfspr(SPRN_PID), mfspr(SPRN_TIDR));
	म_लिखो("psscr  = %.16lx\n",
		hv ? mfspr(SPRN_PSSCR) : mfspr(SPRN_PSSCR_PR));

	अगर (!hv)
		वापस;

	म_लिखो("ptcr   = %.16lx  asdr  = %.16lx\n",
		mfspr(SPRN_PTCR), mfspr(SPRN_ASDR));
#पूर्ण_अगर
पूर्ण

अटल व्योम dump_310_sprs(व्योम)
अणु
#अगर_घोषित CONFIG_PPC64
	अगर (!cpu_has_feature(CPU_FTR_ARCH_31))
		वापस;

	म_लिखो("mmcr3  = %.16lx, sier2  = %.16lx, sier3  = %.16lx\n",
		mfspr(SPRN_MMCR3), mfspr(SPRN_SIER2), mfspr(SPRN_SIER3));

#पूर्ण_अगर
पूर्ण

अटल व्योम dump_one_spr(पूर्णांक spr, bool show_unimplemented)
अणु
	अचिन्हित दीर्घ val;

	val = 0xdeadbeef;
	अगर (!पढ़ो_spr(spr, &val)) अणु
		म_लिखो("SPR 0x%03x (%4d) Faulted during read\n", spr, spr);
		वापस;
	पूर्ण

	अगर (val == 0xdeadbeef) अणु
		/* Looks like पढ़ो was a nop, confirm */
		val = 0x0badcafe;
		अगर (!पढ़ो_spr(spr, &val)) अणु
			म_लिखो("SPR 0x%03x (%4d) Faulted during read\n", spr, spr);
			वापस;
		पूर्ण

		अगर (val == 0x0badcafe) अणु
			अगर (show_unimplemented)
				म_लिखो("SPR 0x%03x (%4d) Unimplemented\n", spr, spr);
			वापस;
		पूर्ण
	पूर्ण

	म_लिखो("SPR 0x%03x (%4d) = 0x%lx\n", spr, spr, val);
पूर्ण

अटल व्योम super_regs(व्योम)
अणु
	अटल अचिन्हित दीर्घ regno;
	पूर्णांक cmd;
	पूर्णांक spr;

	cmd = skipbl();

	चयन (cmd) अणु
	हाल '\n': अणु
		अचिन्हित दीर्घ sp, toc;
		यंत्र("mr %0,1" : "=r" (sp) :);
		यंत्र("mr %0,2" : "=r" (toc) :);

		म_लिखो("msr    = "REG"  sprg0 = "REG"\n",
		       mfmsr(), mfspr(SPRN_SPRG0));
		म_लिखो("pvr    = "REG"  sprg1 = "REG"\n",
		       mfspr(SPRN_PVR), mfspr(SPRN_SPRG1));
		म_लिखो("dec    = "REG"  sprg2 = "REG"\n",
		       mfspr(SPRN_DEC), mfspr(SPRN_SPRG2));
		म_लिखो("sp     = "REG"  sprg3 = "REG"\n", sp, mfspr(SPRN_SPRG3));
		म_लिखो("toc    = "REG"  dar   = "REG"\n", toc, mfspr(SPRN_DAR));

		dump_206_sprs();
		dump_207_sprs();
		dump_300_sprs();
		dump_310_sprs();

		वापस;
	पूर्ण
	हाल 'w': अणु
		अचिन्हित दीर्घ val;
		scanhex(&regno);
		val = 0;
		पढ़ो_spr(regno, &val);
		scanhex(&val);
		ग_लिखो_spr(regno, val);
		dump_one_spr(regno, true);
		अवरोध;
	पूर्ण
	हाल 'r':
		scanhex(&regno);
		dump_one_spr(regno, true);
		अवरोध;
	हाल 'a':
		/* dump ALL SPRs */
		क्रम (spr = 1; spr < 1024; ++spr)
			dump_one_spr(spr, false);
		अवरोध;
	पूर्ण

	scannl();
पूर्ण

/*
 * Stuff क्रम पढ़ोing and writing memory safely
 */
अटल पूर्णांक
mपढ़ो(अचिन्हित दीर्घ adrs, व्योम *buf, पूर्णांक size)
अणु
	अस्थिर पूर्णांक n;
	अक्षर *p, *q;

	n = 0;
	अगर (बनाओ_लाँघ(bus_error_jmp) == 0) अणु
		catch_memory_errors = 1;
		sync();
		p = (अक्षर *)adrs;
		q = (अक्षर *)buf;
		चयन (size) अणु
		हाल 2:
			*(u16 *)q = *(u16 *)p;
			अवरोध;
		हाल 4:
			*(u32 *)q = *(u32 *)p;
			अवरोध;
		हाल 8:
			*(u64 *)q = *(u64 *)p;
			अवरोध;
		शेष:
			क्रम( ; n < size; ++n) अणु
				*q++ = *p++;
				sync();
			पूर्ण
		पूर्ण
		sync();
		/* रुको a little जबतक to see अगर we get a machine check */
		__delay(200);
		n = size;
	पूर्ण
	catch_memory_errors = 0;
	वापस n;
पूर्ण

अटल पूर्णांक
mग_लिखो(अचिन्हित दीर्घ adrs, व्योम *buf, पूर्णांक size)
अणु
	अस्थिर पूर्णांक n;
	अक्षर *p, *q;

	n = 0;

	अगर (xmon_is_ro) अणु
		म_लिखो(xmon_ro_msg);
		वापस n;
	पूर्ण

	अगर (बनाओ_लाँघ(bus_error_jmp) == 0) अणु
		catch_memory_errors = 1;
		sync();
		p = (अक्षर *) adrs;
		q = (अक्षर *) buf;
		चयन (size) अणु
		हाल 2:
			*(u16 *)p = *(u16 *)q;
			अवरोध;
		हाल 4:
			*(u32 *)p = *(u32 *)q;
			अवरोध;
		हाल 8:
			*(u64 *)p = *(u64 *)q;
			अवरोध;
		शेष:
			क्रम ( ; n < size; ++n) अणु
				*p++ = *q++;
				sync();
			पूर्ण
		पूर्ण
		sync();
		/* रुको a little जबतक to see अगर we get a machine check */
		__delay(200);
		n = size;
	पूर्ण अन्यथा अणु
		म_लिखो("*** Error writing address "REG"\n", adrs + n);
	पूर्ण
	catch_memory_errors = 0;
	वापस n;
पूर्ण

अटल पूर्णांक
mपढ़ो_instr(अचिन्हित दीर्घ adrs, काष्ठा ppc_inst *instr)
अणु
	अस्थिर पूर्णांक n;

	n = 0;
	अगर (बनाओ_लाँघ(bus_error_jmp) == 0) अणु
		catch_memory_errors = 1;
		sync();
		*instr = ppc_inst_पढ़ो((काष्ठा ppc_inst *)adrs);
		sync();
		/* रुको a little जबतक to see अगर we get a machine check */
		__delay(200);
		n = ppc_inst_len(*instr);
	पूर्ण
	catch_memory_errors = 0;
	वापस n;
पूर्ण

अटल पूर्णांक fault_type;
अटल पूर्णांक fault_except;
अटल अक्षर *fault_अक्षरs[] = अणु "--", "**", "##" पूर्ण;

अटल पूर्णांक handle_fault(काष्ठा pt_regs *regs)
अणु
	fault_except = TRAP(regs);
	चयन (TRAP(regs)) अणु
	हाल 0x200:
		fault_type = 0;
		अवरोध;
	हाल 0x300:
	हाल 0x380:
		fault_type = 1;
		अवरोध;
	शेष:
		fault_type = 2;
	पूर्ण

	दीर्घ_लाँघ(bus_error_jmp, 1);

	वापस 0;
पूर्ण

#घोषणा SWAP(a, b, t)	((t) = (a), (a) = (b), (b) = (t))

अटल व्योम
byterev(अचिन्हित अक्षर *val, पूर्णांक size)
अणु
	पूर्णांक t;
	
	चयन (size) अणु
	हाल 2:
		SWAP(val[0], val[1], t);
		अवरोध;
	हाल 4:
		SWAP(val[0], val[3], t);
		SWAP(val[1], val[2], t);
		अवरोध;
	हाल 8: /* is there really any use क्रम this? */
		SWAP(val[0], val[7], t);
		SWAP(val[1], val[6], t);
		SWAP(val[2], val[5], t);
		SWAP(val[3], val[4], t);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक brev;
अटल पूर्णांक mnoपढ़ो;

अटल अक्षर *memex_help_string =
    "Memory examine command usage:\n"
    "m [addr] [flags] examine/change memory\n"
    "  addr is optional.  will start where left off.\n"
    "  flags may include chars from this set:\n"
    "    b   modify by bytes (default)\n"
    "    w   modify by words (2 byte)\n"
    "    l   modify by longs (4 byte)\n"
    "    d   modify by doubleword (8 byte)\n"
    "    r   toggle reverse byte order mode\n"
    "    n   do not read memory (for i/o spaces)\n"
    "    .   ok to read (default)\n"
    "NOTE: flags are saved as defaults\n"
    "";

अटल अक्षर *memex_subcmd_help_string =
    "Memory examine subcommands:\n"
    "  hexval   write this val to current location\n"
    "  'string' write chars from string to this location\n"
    "  '        increment address\n"
    "  ^        decrement address\न"
    "  /        increment addr by 0x10.  //=0x100, ///=0x1000, etc\n"
    "  \\        decrement addr by 0x10.  \\\\=0x100, \\\\\\=0x1000, etc\n"
    "  `        clear no-read flag\n"
    "  ;        stay at this addr\n"
    "  v        change to byte mode\n"
    "  w        change to word (2 byte) mode\n"
    "  l        change to long (4 byte) mode\n"
    "  u        change to doubleword (8 byte) mode\n"
    "  m addr   change current addr\n"
    "  n        toggle no-read flag\n"
    "  r        toggle byte reverse flag\n"
    "  < count  back up count bytes\n"
    "  > count  skip forward count bytes\n"
    "  x        exit this mode\n"
    "";

अटल व्योम
memex(व्योम)
अणु
	पूर्णांक cmd, inc, i, nslash;
	अचिन्हित दीर्घ n;
	अचिन्हित अक्षर val[16];

	scanhex((व्योम *)&adrs);
	cmd = skipbl();
	अगर (cmd == '?') अणु
		म_लिखो(memex_help_string);
		वापस;
	पूर्ण अन्यथा अणु
		termch = cmd;
	पूर्ण
	last_cmd = "m\n";
	जबतक ((cmd = skipbl()) != '\n') अणु
		चयन( cmd )अणु
		हाल 'b':	size = 1;	अवरोध;
		हाल 'w':	size = 2;	अवरोध;
		हाल 'l':	size = 4;	अवरोध;
		हाल 'd':	size = 8;	अवरोध;
		हाल 'r': 	brev = !brev;	अवरोध;
		हाल 'n':	mnoपढ़ो = 1;	अवरोध;
		हाल '.':	mnoपढ़ो = 0;	अवरोध;
		पूर्ण
	पूर्ण
	अगर( size <= 0 )
		size = 1;
	अन्यथा अगर( size > 8 )
		size = 8;
	क्रम(;;)अणु
		अगर (!mnoपढ़ो)
			n = mपढ़ो(adrs, val, size);
		म_लिखो(REG"%c", adrs, brev? 'r': ' ');
		अगर (!mnoपढ़ो) अणु
			अगर (brev)
				byterev(val, size);
			अक्षर_दो(' ');
			क्रम (i = 0; i < n; ++i)
				म_लिखो("%.2x", val[i]);
			क्रम (; i < size; ++i)
				म_लिखो("%s", fault_अक्षरs[fault_type]);
		पूर्ण
		अक्षर_दो(' ');
		inc = size;
		nslash = 0;
		क्रम(;;)अणु
			अगर( scanhex(&n) )अणु
				क्रम (i = 0; i < size; ++i)
					val[i] = n >> (i * 8);
				अगर (!brev)
					byterev(val, size);
				mग_लिखो(adrs, val, size);
				inc = size;
			पूर्ण
			cmd = skipbl();
			अगर (cmd == '\n')
				अवरोध;
			inc = 0;
			चयन (cmd) अणु
			हाल '\'':
				क्रम(;;)अणु
					n = inअक्षर();
					अगर( n == '\\' )
						n = bsesc();
					अन्यथा अगर( n == '\'' )
						अवरोध;
					क्रम (i = 0; i < size; ++i)
						val[i] = n >> (i * 8);
					अगर (!brev)
						byterev(val, size);
					mग_लिखो(adrs, val, size);
					adrs += size;
				पूर्ण
				adrs -= size;
				inc = size;
				अवरोध;
			हाल ',':
				adrs += size;
				अवरोध;
			हाल '.':
				mnoपढ़ो = 0;
				अवरोध;
			हाल ';':
				अवरोध;
			हाल 'x':
			हाल खातापूर्ण:
				scannl();
				वापस;
			हाल 'b':
			हाल 'v':
				size = 1;
				अवरोध;
			हाल 'w':
				size = 2;
				अवरोध;
			हाल 'l':
				size = 4;
				अवरोध;
			हाल 'u':
				size = 8;
				अवरोध;
			हाल '^':
				adrs -= size;
				अवरोध;
			हाल '/':
				अगर (nslash > 0)
					adrs -= 1 << nslash;
				अन्यथा
					nslash = 0;
				nslash += 4;
				adrs += 1 << nslash;
				अवरोध;
			हाल '\\':
				अगर (nslash < 0)
					adrs += 1 << -nslash;
				अन्यथा
					nslash = 0;
				nslash -= 4;
				adrs -= 1 << -nslash;
				अवरोध;
			हाल 'm':
				scanhex((व्योम *)&adrs);
				अवरोध;
			हाल 'n':
				mnoपढ़ो = 1;
				अवरोध;
			हाल 'r':
				brev = !brev;
				अवरोध;
			हाल '<':
				n = size;
				scanhex(&n);
				adrs -= n;
				अवरोध;
			हाल '>':
				n = size;
				scanhex(&n);
				adrs += n;
				अवरोध;
			हाल '?':
				म_लिखो(memex_subcmd_help_string);
				अवरोध;
			पूर्ण
		पूर्ण
		adrs += inc;
	पूर्ण
पूर्ण

अटल पूर्णांक
bsesc(व्योम)
अणु
	पूर्णांक c;

	c = inअक्षर();
	चयन( c )अणु
	हाल 'n':	c = '\n';	अवरोध;
	हाल 'r':	c = '\r';	अवरोध;
	हाल 'b':	c = '\b';	अवरोध;
	हाल 't':	c = '\t';	अवरोध;
	पूर्ण
	वापस c;
पूर्ण

अटल व्योम xmon_rawdump (अचिन्हित दीर्घ adrs, दीर्घ ndump)
अणु
	दीर्घ n, m, r, nr;
	अचिन्हित अक्षर temp[16];

	क्रम (n = ndump; n > 0;) अणु
		r = n < 16? n: 16;
		nr = mपढ़ो(adrs, temp, r);
		adrs += nr;
		क्रम (m = 0; m < r; ++m) अणु
			अगर (m < nr)
				म_लिखो("%.2x", temp[m]);
			अन्यथा
				म_लिखो("%s", fault_अक्षरs[fault_type]);
		पूर्ण
		n -= r;
		अगर (nr < r)
			अवरोध;
	पूर्ण
	म_लिखो("\n");
पूर्ण

अटल व्योम dump_tracing(व्योम)
अणु
	पूर्णांक c;

	c = inअक्षर();
	अगर (c == 'c')
		ftrace_dump(DUMP_ORIG);
	अन्यथा
		ftrace_dump(DUMP_ALL);
पूर्ण

#अगर_घोषित CONFIG_PPC64
अटल व्योम dump_one_paca(पूर्णांक cpu)
अणु
	काष्ठा paca_काष्ठा *p;
#अगर_घोषित CONFIG_PPC_BOOK3S_64
	पूर्णांक i = 0;
#पूर्ण_अगर

	अगर (बनाओ_लाँघ(bus_error_jmp) != 0) अणु
		म_लिखो("*** Error dumping paca for cpu 0x%x!\n", cpu);
		वापस;
	पूर्ण

	catch_memory_errors = 1;
	sync();

	p = paca_ptrs[cpu];

	म_लिखो("paca for cpu 0x%x @ %px:\n", cpu, p);

	म_लिखो(" %-*s = %s\n", 25, "possible", cpu_possible(cpu) ? "yes" : "no");
	म_लिखो(" %-*s = %s\n", 25, "present", cpu_present(cpu) ? "yes" : "no");
	म_लिखो(" %-*s = %s\n", 25, "online", cpu_online(cpu) ? "yes" : "no");

#घोषणा DUMP(paca, name, क्रमmat)				\
	म_लिखो(" %-*s = "क्रमmat"\t(0x%lx)\n", 25, #name, 18, paca->name, \
		दुरत्व(काष्ठा paca_काष्ठा, name));

	DUMP(p, lock_token, "%#-*x");
	DUMP(p, paca_index, "%#-*x");
	DUMP(p, kernel_toc, "%#-*llx");
	DUMP(p, kernelbase, "%#-*llx");
	DUMP(p, kernel_msr, "%#-*llx");
	DUMP(p, emergency_sp, "%-*px");
#अगर_घोषित CONFIG_PPC_BOOK3S_64
	DUMP(p, nmi_emergency_sp, "%-*px");
	DUMP(p, mc_emergency_sp, "%-*px");
	DUMP(p, in_nmi, "%#-*x");
	DUMP(p, in_mce, "%#-*x");
	DUMP(p, hmi_event_available, "%#-*x");
#पूर्ण_अगर
	DUMP(p, data_offset, "%#-*llx");
	DUMP(p, hw_cpu_id, "%#-*x");
	DUMP(p, cpu_start, "%#-*x");
	DUMP(p, kexec_state, "%#-*x");
#अगर_घोषित CONFIG_PPC_BOOK3S_64
	अगर (!early_radix_enabled()) अणु
		क्रम (i = 0; i < SLB_NUM_BOLTED; i++) अणु
			u64 esid, vsid;

			अगर (!p->slb_shaकरोw_ptr)
				जारी;

			esid = be64_to_cpu(p->slb_shaकरोw_ptr->save_area[i].esid);
			vsid = be64_to_cpu(p->slb_shaकरोw_ptr->save_area[i].vsid);

			अगर (esid || vsid) अणु
				म_लिखो(" %-*s[%d] = 0x%016llx 0x%016llx\n",
				       22, "slb_shadow", i, esid, vsid);
			पूर्ण
		पूर्ण
		DUMP(p, vदो_स्मृति_sllp, "%#-*x");
		DUMP(p, stab_rr, "%#-*x");
		DUMP(p, slb_used_biपंचांगap, "%#-*x");
		DUMP(p, slb_kern_biपंचांगap, "%#-*x");

		अगर (!early_cpu_has_feature(CPU_FTR_ARCH_300)) अणु
			DUMP(p, slb_cache_ptr, "%#-*x");
			क्रम (i = 0; i < SLB_CACHE_ENTRIES; i++)
				म_लिखो(" %-*s[%d] = 0x%016x\n",
				       22, "slb_cache", i, p->slb_cache[i]);
		पूर्ण
	पूर्ण

	DUMP(p, rfi_flush_fallback_area, "%-*px");
#पूर्ण_अगर
	DUMP(p, dscr_शेष, "%#-*llx");
#अगर_घोषित CONFIG_PPC_BOOK3E
	DUMP(p, pgd, "%-*px");
	DUMP(p, kernel_pgd, "%-*px");
	DUMP(p, tcd_ptr, "%-*px");
	DUMP(p, mc_kstack, "%-*px");
	DUMP(p, crit_kstack, "%-*px");
	DUMP(p, dbg_kstack, "%-*px");
#पूर्ण_अगर
	DUMP(p, __current, "%-*px");
	DUMP(p, kstack, "%#-*llx");
	म_लिखो(" %-*s = 0x%016llx\n", 25, "kstack_base", p->kstack & ~(THREAD_SIZE - 1));
#अगर_घोषित CONFIG_STACKPROTECTOR
	DUMP(p, canary, "%#-*lx");
#पूर्ण_अगर
	DUMP(p, saved_r1, "%#-*llx");
#अगर_घोषित CONFIG_PPC_BOOK3E
	DUMP(p, trap_save, "%#-*x");
#पूर्ण_अगर
	DUMP(p, irq_soft_mask, "%#-*x");
	DUMP(p, irq_happened, "%#-*x");
#अगर_घोषित CONFIG_MMIOWB
	DUMP(p, mmiowb_state.nesting_count, "%#-*x");
	DUMP(p, mmiowb_state.mmiowb_pending, "%#-*x");
#पूर्ण_अगर
	DUMP(p, irq_work_pending, "%#-*x");
	DUMP(p, sprg_vdso, "%#-*llx");

#अगर_घोषित CONFIG_PPC_TRANSACTIONAL_MEM
	DUMP(p, पंचांग_scratch, "%#-*llx");
#पूर्ण_अगर

#अगर_घोषित CONFIG_PPC_POWERNV
	DUMP(p, idle_state, "%#-*lx");
	अगर (!early_cpu_has_feature(CPU_FTR_ARCH_300)) अणु
		DUMP(p, thपढ़ो_idle_state, "%#-*x");
		DUMP(p, subcore_sibling_mask, "%#-*x");
	पूर्ण अन्यथा अणु
#अगर_घोषित CONFIG_KVM_BOOK3S_HV_POSSIBLE
		DUMP(p, requested_psscr, "%#-*llx");
		DUMP(p, करोnt_stop.counter, "%#-*x");
#पूर्ण_अगर
	पूर्ण
#पूर्ण_अगर

	DUMP(p, accounting.uसमय, "%#-*lx");
	DUMP(p, accounting.sसमय, "%#-*lx");
#अगर_घोषित CONFIG_ARCH_HAS_SCALED_CPUTIME
	DUMP(p, accounting.uसमय_scaled, "%#-*lx");
#पूर्ण_अगर
	DUMP(p, accounting.startसमय, "%#-*lx");
	DUMP(p, accounting.startसमय_user, "%#-*lx");
#अगर_घोषित CONFIG_ARCH_HAS_SCALED_CPUTIME
	DUMP(p, accounting.startspurr, "%#-*lx");
	DUMP(p, accounting.uसमय_sspurr, "%#-*lx");
#पूर्ण_अगर
	DUMP(p, accounting.steal_समय, "%#-*lx");
#अघोषित DUMP

	catch_memory_errors = 0;
	sync();
पूर्ण

अटल व्योम dump_all_pacas(व्योम)
अणु
	पूर्णांक cpu;

	अगर (num_possible_cpus() == 0) अणु
		म_लिखो("No possible cpus, use 'dp #' to dump individual cpus\n");
		वापस;
	पूर्ण

	क्रम_each_possible_cpu(cpu)
		dump_one_paca(cpu);
पूर्ण

अटल व्योम dump_pacas(व्योम)
अणु
	अचिन्हित दीर्घ num;
	पूर्णांक c;

	c = inअक्षर();
	अगर (c == 'a') अणु
		dump_all_pacas();
		वापस;
	पूर्ण

	termch = c;	/* Put c back, it wasn't 'a' */

	अगर (scanhex(&num))
		dump_one_paca(num);
	अन्यथा
		dump_one_paca(xmon_owner);
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_PPC_POWERNV
अटल व्योम dump_one_xive(पूर्णांक cpu)
अणु
	अचिन्हित पूर्णांक hwid = get_hard_smp_processor_id(cpu);
	bool hv = cpu_has_feature(CPU_FTR_HVMODE);

	अगर (hv) अणु
		opal_xive_dump(XIVE_DUMP_TM_HYP, hwid);
		opal_xive_dump(XIVE_DUMP_TM_POOL, hwid);
		opal_xive_dump(XIVE_DUMP_TM_OS, hwid);
		opal_xive_dump(XIVE_DUMP_TM_USER, hwid);
		opal_xive_dump(XIVE_DUMP_VP, hwid);
		opal_xive_dump(XIVE_DUMP_EMU_STATE, hwid);
	पूर्ण

	अगर (बनाओ_लाँघ(bus_error_jmp) != 0) अणु
		catch_memory_errors = 0;
		म_लिखो("*** Error dumping xive on cpu %d\n", cpu);
		वापस;
	पूर्ण

	catch_memory_errors = 1;
	sync();
	xmon_xive_करो_dump(cpu);
	sync();
	__delay(200);
	catch_memory_errors = 0;
पूर्ण

अटल व्योम dump_all_xives(व्योम)
अणु
	पूर्णांक cpu;

	अगर (num_possible_cpus() == 0) अणु
		म_लिखो("No possible cpus, use 'dx #' to dump individual cpus\n");
		वापस;
	पूर्ण

	क्रम_each_possible_cpu(cpu)
		dump_one_xive(cpu);
पूर्ण

अटल व्योम dump_xives(व्योम)
अणु
	अचिन्हित दीर्घ num;
	पूर्णांक c;

	अगर (!xive_enabled()) अणु
		म_लिखो("Xive disabled on this system\n");
		वापस;
	पूर्ण

	c = inअक्षर();
	अगर (c == 'a') अणु
		dump_all_xives();
		वापस;
	पूर्ण अन्यथा अगर (c == 'i') अणु
		अगर (scanhex(&num))
			xmon_xive_get_irq_config(num, शून्य);
		अन्यथा
			xmon_xive_get_irq_all();
		वापस;
	पूर्ण

	termch = c;	/* Put c back, it wasn't 'a' */

	अगर (scanhex(&num))
		dump_one_xive(num);
	अन्यथा
		dump_one_xive(xmon_owner);
पूर्ण
#पूर्ण_अगर /* CONFIG_PPC_POWERNV */

अटल व्योम dump_by_size(अचिन्हित दीर्घ addr, दीर्घ count, पूर्णांक size)
अणु
	अचिन्हित अक्षर temp[16];
	पूर्णांक i, j;
	u64 val;

	count = ALIGN(count, 16);

	क्रम (i = 0; i < count; i += 16, addr += 16) अणु
		म_लिखो(REG, addr);

		अगर (mपढ़ो(addr, temp, 16) != 16) अणु
			म_लिखो("\nFaulted reading %d bytes from 0x"REG"\n", 16, addr);
			वापस;
		पूर्ण

		क्रम (j = 0; j < 16; j += size) अणु
			अक्षर_दो(' ');
			चयन (size) अणु
			हाल 1: val = temp[j]; अवरोध;
			हाल 2: val = *(u16 *)&temp[j]; अवरोध;
			हाल 4: val = *(u32 *)&temp[j]; अवरोध;
			हाल 8: val = *(u64 *)&temp[j]; अवरोध;
			शेष: val = 0;
			पूर्ण

			म_लिखो("%0*llx", size * 2, val);
		पूर्ण
		म_लिखो("  |");
		क्रम (j = 0; j < 16; ++j) अणु
			val = temp[j];
			अक्षर_दो(' ' <= val && val <= '~' ? val : '.');
		पूर्ण
		म_लिखो("|\n");
	पूर्ण
पूर्ण

अटल व्योम
dump(व्योम)
अणु
	अटल अक्षर last[] = अणु "d?\n" पूर्ण;
	पूर्णांक c;

	c = inअक्षर();

#अगर_घोषित CONFIG_PPC64
	अगर (c == 'p') अणु
		xmon_start_pagination();
		dump_pacas();
		xmon_end_pagination();
		वापस;
	पूर्ण
#पूर्ण_अगर
#अगर_घोषित CONFIG_PPC_POWERNV
	अगर (c == 'x') अणु
		xmon_start_pagination();
		dump_xives();
		xmon_end_pagination();
		वापस;
	पूर्ण
#पूर्ण_अगर

	अगर (c == 't') अणु
		dump_tracing();
		वापस;
	पूर्ण

	अगर (c == '\n')
		termch = c;

	scanhex((व्योम *)&adrs);
	अगर (termch != '\n')
		termch = 0;
	अगर (c == 'i') अणु
		scanhex(&nidump);
		अगर (nidump == 0)
			nidump = 16;
		अन्यथा अगर (nidump > MAX_IDUMP)
			nidump = MAX_IDUMP;
		adrs += ppc_inst_dump(adrs, nidump, 1);
		last_cmd = "di\n";
	पूर्ण अन्यथा अगर (c == 'l') अणु
		dump_log_buf();
	पूर्ण अन्यथा अगर (c == 'o') अणु
		dump_opal_msglog();
	पूर्ण अन्यथा अगर (c == 'v') अणु
		/* dump भव to physical translation */
		show_pte(adrs);
	पूर्ण अन्यथा अगर (c == 'r') अणु
		scanhex(&ndump);
		अगर (ndump == 0)
			ndump = 64;
		xmon_rawdump(adrs, ndump);
		adrs += ndump;
		last_cmd = "dr\n";
	पूर्ण अन्यथा अणु
		scanhex(&ndump);
		अगर (ndump == 0)
			ndump = 64;
		अन्यथा अगर (ndump > MAX_DUMP)
			ndump = MAX_DUMP;

		चयन (c) अणु
		हाल '8':
		हाल '4':
		हाल '2':
		हाल '1':
			ndump = ALIGN(ndump, 16);
			dump_by_size(adrs, ndump, c - '0');
			last[1] = c;
			last_cmd = last;
			अवरोध;
		शेष:
			prdump(adrs, ndump);
			last_cmd = "d\n";
		पूर्ण

		adrs += ndump;
	पूर्ण
पूर्ण

अटल व्योम
prdump(अचिन्हित दीर्घ adrs, दीर्घ ndump)
अणु
	दीर्घ n, m, c, r, nr;
	अचिन्हित अक्षर temp[16];

	क्रम (n = ndump; n > 0;) अणु
		म_लिखो(REG, adrs);
		अक्षर_दो(' ');
		r = n < 16? n: 16;
		nr = mपढ़ो(adrs, temp, r);
		adrs += nr;
		क्रम (m = 0; m < r; ++m) अणु
			अगर ((m & (माप(दीर्घ) - 1)) == 0 && m > 0)
				अक्षर_दो(' ');
			अगर (m < nr)
				म_लिखो("%.2x", temp[m]);
			अन्यथा
				म_लिखो("%s", fault_अक्षरs[fault_type]);
		पूर्ण
		क्रम (; m < 16; ++m) अणु
			अगर ((m & (माप(दीर्घ) - 1)) == 0)
				अक्षर_दो(' ');
			म_लिखो("  ");
		पूर्ण
		म_लिखो("  |");
		क्रम (m = 0; m < r; ++m) अणु
			अगर (m < nr) अणु
				c = temp[m];
				अक्षर_दो(' ' <= c && c <= '~'? c: '.');
			पूर्ण अन्यथा
				अक्षर_दो(' ');
		पूर्ण
		n -= r;
		क्रम (; m < 16; ++m)
			अक्षर_दो(' ');
		म_लिखो("|\n");
		अगर (nr < r)
			अवरोध;
	पूर्ण
पूर्ण

प्रकार पूर्णांक (*inकाष्ठाion_dump_func)(अचिन्हित दीर्घ inst, अचिन्हित दीर्घ addr);

अटल पूर्णांक
generic_inst_dump(अचिन्हित दीर्घ adr, दीर्घ count, पूर्णांक praddr,
			inकाष्ठाion_dump_func dump_func)
अणु
	पूर्णांक nr, करोtted;
	अचिन्हित दीर्घ first_adr;
	काष्ठा ppc_inst inst, last_inst = ppc_inst(0);

	करोtted = 0;
	क्रम (first_adr = adr; count > 0; --count, adr += ppc_inst_len(inst)) अणु
		nr = mपढ़ो_instr(adr, &inst);
		अगर (nr == 0) अणु
			अगर (praddr) अणु
				स्थिर अक्षर *x = fault_अक्षरs[fault_type];
				म_लिखो(REG"  %s%s%s%s\n", adr, x, x, x, x);
			पूर्ण
			अवरोध;
		पूर्ण
		अगर (adr > first_adr && ppc_inst_equal(inst, last_inst)) अणु
			अगर (!करोtted) अणु
				म_लिखो(" ...\n");
				करोtted = 1;
			पूर्ण
			जारी;
		पूर्ण
		करोtted = 0;
		last_inst = inst;
		अगर (praddr)
			म_लिखो(REG"  %s", adr, ppc_inst_as_str(inst));
		म_लिखो("\t");
		अगर (!ppc_inst_prefixed(inst))
			dump_func(ppc_inst_val(inst), adr);
		अन्यथा
			dump_func(ppc_inst_as_uदीर्घ(inst), adr);
		म_लिखो("\n");
	पूर्ण
	वापस adr - first_adr;
पूर्ण

अटल पूर्णांक
ppc_inst_dump(अचिन्हित दीर्घ adr, दीर्घ count, पूर्णांक praddr)
अणु
	वापस generic_inst_dump(adr, count, praddr, prपूर्णांक_insn_घातerpc);
पूर्ण

व्योम
prपूर्णांक_address(अचिन्हित दीर्घ addr)
अणु
	xmon_prपूर्णांक_symbol(addr, "\t# ", "");
पूर्ण

अटल व्योम
dump_log_buf(व्योम)
अणु
	काष्ठा kmsg_dump_iter iter;
	अचिन्हित अक्षर buf[128];
	माप_प्रकार len;

	अगर (बनाओ_लाँघ(bus_error_jmp) != 0) अणु
		म_लिखो("Error dumping printk buffer!\n");
		वापस;
	पूर्ण

	catch_memory_errors = 1;
	sync();

	kmsg_dump_शुरुआत(&iter);
	xmon_start_pagination();
	जबतक (kmsg_dump_get_line(&iter, false, buf, माप(buf), &len)) अणु
		buf[len] = '\0';
		म_लिखो("%s", buf);
	पूर्ण
	xmon_end_pagination();

	sync();
	/* रुको a little जबतक to see अगर we get a machine check */
	__delay(200);
	catch_memory_errors = 0;
पूर्ण

#अगर_घोषित CONFIG_PPC_POWERNV
अटल व्योम dump_opal_msglog(व्योम)
अणु
	अचिन्हित अक्षर buf[128];
	sमाप_प्रकार res;
	loff_t pos = 0;

	अगर (!firmware_has_feature(FW_FEATURE_OPAL)) अणु
		म_लिखो("Machine is not running OPAL firmware.\n");
		वापस;
	पूर्ण

	अगर (बनाओ_लाँघ(bus_error_jmp) != 0) अणु
		म_लिखो("Error dumping OPAL msglog!\n");
		वापस;
	पूर्ण

	catch_memory_errors = 1;
	sync();

	xmon_start_pagination();
	जबतक ((res = opal_msglog_copy(buf, pos, माप(buf) - 1))) अणु
		अगर (res < 0) अणु
			म_लिखो("Error dumping OPAL msglog! Error: %zd\n", res);
			अवरोध;
		पूर्ण
		buf[res] = '\0';
		म_लिखो("%s", buf);
		pos += res;
	पूर्ण
	xmon_end_pagination();

	sync();
	/* रुको a little जबतक to see अगर we get a machine check */
	__delay(200);
	catch_memory_errors = 0;
पूर्ण
#पूर्ण_अगर

/*
 * Memory operations - move, set, prपूर्णांक dअगरferences
 */
अटल अचिन्हित दीर्घ mdest;		/* destination address */
अटल अचिन्हित दीर्घ msrc;		/* source address */
अटल अचिन्हित दीर्घ mval;		/* byte value to set memory to */
अटल अचिन्हित दीर्घ mcount;		/* # bytes to affect */
अटल अचिन्हित दीर्घ mdअगरfs;		/* max # dअगरferences to prपूर्णांक */

अटल व्योम
memops(पूर्णांक cmd)
अणु
	scanhex((व्योम *)&mdest);
	अगर( termch != '\n' )
		termch = 0;
	scanhex((व्योम *)(cmd == 's'? &mval: &msrc));
	अगर( termch != '\n' )
		termch = 0;
	scanhex((व्योम *)&mcount);
	चयन( cmd )अणु
	हाल 'm':
		अगर (xmon_is_ro) अणु
			म_लिखो(xmon_ro_msg);
			अवरोध;
		पूर्ण
		स_हटाओ((व्योम *)mdest, (व्योम *)msrc, mcount);
		अवरोध;
	हाल 's':
		अगर (xmon_is_ro) अणु
			म_लिखो(xmon_ro_msg);
			अवरोध;
		पूर्ण
		स_रखो((व्योम *)mdest, mval, mcount);
		अवरोध;
	हाल 'd':
		अगर( termch != '\n' )
			termch = 0;
		scanhex((व्योम *)&mdअगरfs);
		memdअगरfs((अचिन्हित अक्षर *)mdest, (अचिन्हित अक्षर *)msrc, mcount, mdअगरfs);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम
memdअगरfs(अचिन्हित अक्षर *p1, अचिन्हित अक्षर *p2, अचिन्हित nb, अचिन्हित maxpr)
अणु
	अचिन्हित n, prt;

	prt = 0;
	क्रम( n = nb; n > 0; --n )
		अगर( *p1++ != *p2++ )
			अगर( ++prt <= maxpr )
				म_लिखो("%px %.2x # %px %.2x\n", p1 - 1,
					p1[-1], p2 - 1, p2[-1]);
	अगर( prt > maxpr )
		म_लिखो("Total of %d differences\n", prt);
पूर्ण

अटल अचिन्हित mend;
अटल अचिन्हित mask;

अटल व्योम
memlocate(व्योम)
अणु
	अचिन्हित a, n;
	अचिन्हित अक्षर val[4];

	last_cmd = "ml";
	scanhex((व्योम *)&mdest);
	अगर (termch != '\n') अणु
		termch = 0;
		scanhex((व्योम *)&mend);
		अगर (termch != '\n') अणु
			termch = 0;
			scanhex((व्योम *)&mval);
			mask = ~0;
			अगर (termch != '\n') termch = 0;
			scanhex((व्योम *)&mask);
		पूर्ण
	पूर्ण
	n = 0;
	क्रम (a = mdest; a < mend; a += 4) अणु
		अगर (mपढ़ो(a, val, 4) == 4
			&& ((GETWORD(val) ^ mval) & mask) == 0) अणु
			म_लिखो("%.16x:  %.16x\n", a, GETWORD(val));
			अगर (++n >= 10)
				अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल अचिन्हित दीर्घ mskip = 0x1000;
अटल अचिन्हित दीर्घ mlim = 0xffffffff;

अटल व्योम
memzcan(व्योम)
अणु
	अचिन्हित अक्षर v;
	अचिन्हित a;
	पूर्णांक ok, ook;

	scanhex(&mdest);
	अगर (termch != '\n') termch = 0;
	scanhex(&mskip);
	अगर (termch != '\n') termch = 0;
	scanhex(&mlim);
	ook = 0;
	क्रम (a = mdest; a < mlim; a += mskip) अणु
		ok = mपढ़ो(a, &v, 1);
		अगर (ok && !ook) अणु
			म_लिखो("%.8x .. ", a);
		पूर्ण अन्यथा अगर (!ok && ook)
			म_लिखो("%.8lx\n", a - mskip);
		ook = ok;
		अगर (a + mskip < a)
			अवरोध;
	पूर्ण
	अगर (ook)
		म_लिखो("%.8lx\n", a - mskip);
पूर्ण

अटल व्योम show_task(काष्ठा task_काष्ठा *tsk)
अणु
	अक्षर state;

	/*
	 * Cloned from kdb_task_state_अक्षर(), which is not entirely
	 * appropriate क्रम calling from xmon. This could be moved
	 * to a common, generic, routine used by both.
	 */
	state = (tsk->state == 0) ? 'R' :
		(tsk->state < 0) ? 'U' :
		(tsk->state & TASK_UNINTERRUPTIBLE) ? 'D' :
		(tsk->state & TASK_STOPPED) ? 'T' :
		(tsk->state & TASK_TRACED) ? 'C' :
		(tsk->निकास_state & EXIT_ZOMBIE) ? 'Z' :
		(tsk->निकास_state & EXIT_DEAD) ? 'E' :
		(tsk->state & TASK_INTERRUPTIBLE) ? 'S' : '?';

	म_लिखो("%16px %16lx %16px %6d %6d %c %2d %s\n", tsk,
		tsk->thपढ़ो.ksp, tsk->thपढ़ो.regs,
		tsk->pid, rcu_dereference(tsk->parent)->pid,
		state, task_cpu(tsk),
		tsk->comm);
पूर्ण

#अगर_घोषित CONFIG_PPC_BOOK3S_64
अटल व्योम क्रमmat_pte(व्योम *ptep, अचिन्हित दीर्घ pte)
अणु
	pte_t entry = __pte(pte);

	म_लिखो("ptep @ 0x%016lx = 0x%016lx\n", (अचिन्हित दीर्घ)ptep, pte);
	म_लिखो("Maps physical address = 0x%016lx\n", pte & PTE_RPN_MASK);

	म_लिखो("Flags = %s%s%s%s%s\n",
	       pte_young(entry) ? "Accessed " : "",
	       pte_dirty(entry) ? "Dirty " : "",
	       pte_पढ़ो(entry)  ? "Read " : "",
	       pte_ग_लिखो(entry) ? "Write " : "",
	       pte_exec(entry)  ? "Exec " : "");
पूर्ण

अटल व्योम show_pte(अचिन्हित दीर्घ addr)
अणु
	अचिन्हित दीर्घ tskv = 0;
	काष्ठा task_काष्ठा *tsk = शून्य;
	काष्ठा mm_काष्ठा *mm;
	pgd_t *pgdp;
	p4d_t *p4dp;
	pud_t *pudp;
	pmd_t *pmdp;
	pte_t *ptep;

	अगर (!scanhex(&tskv))
		mm = &init_mm;
	अन्यथा
		tsk = (काष्ठा task_काष्ठा *)tskv;

	अगर (tsk == शून्य)
		mm = &init_mm;
	अन्यथा
		mm = tsk->active_mm;

	अगर (बनाओ_लाँघ(bus_error_jmp) != 0) अणु
		catch_memory_errors = 0;
		म_लिखो("*** Error dumping pte for task %px\n", tsk);
		वापस;
	पूर्ण

	catch_memory_errors = 1;
	sync();

	अगर (mm == &init_mm)
		pgdp = pgd_offset_k(addr);
	अन्यथा
		pgdp = pgd_offset(mm, addr);

	p4dp = p4d_offset(pgdp, addr);

	अगर (p4d_none(*p4dp)) अणु
		म_लिखो("No valid P4D\n");
		वापस;
	पूर्ण

	अगर (p4d_is_leaf(*p4dp)) अणु
		क्रमmat_pte(p4dp, p4d_val(*p4dp));
		वापस;
	पूर्ण

	म_लिखो("p4dp @ 0x%px = 0x%016lx\n", p4dp, p4d_val(*p4dp));

	pudp = pud_offset(p4dp, addr);

	अगर (pud_none(*pudp)) अणु
		म_लिखो("No valid PUD\n");
		वापस;
	पूर्ण

	अगर (pud_is_leaf(*pudp)) अणु
		क्रमmat_pte(pudp, pud_val(*pudp));
		वापस;
	पूर्ण

	म_लिखो("pudp @ 0x%px = 0x%016lx\n", pudp, pud_val(*pudp));

	pmdp = pmd_offset(pudp, addr);

	अगर (pmd_none(*pmdp)) अणु
		म_लिखो("No valid PMD\n");
		वापस;
	पूर्ण

	अगर (pmd_is_leaf(*pmdp)) अणु
		क्रमmat_pte(pmdp, pmd_val(*pmdp));
		वापस;
	पूर्ण
	म_लिखो("pmdp @ 0x%px = 0x%016lx\n", pmdp, pmd_val(*pmdp));

	ptep = pte_offset_map(pmdp, addr);
	अगर (pte_none(*ptep)) अणु
		म_लिखो("no valid PTE\n");
		वापस;
	पूर्ण

	क्रमmat_pte(ptep, pte_val(*ptep));

	sync();
	__delay(200);
	catch_memory_errors = 0;
पूर्ण
#अन्यथा
अटल व्योम show_pte(अचिन्हित दीर्घ addr)
अणु
	म_लिखो("show_pte not yet implemented\n");
पूर्ण
#पूर्ण_अगर /* CONFIG_PPC_BOOK3S_64 */

अटल व्योम show_tasks(व्योम)
अणु
	अचिन्हित दीर्घ tskv;
	काष्ठा task_काष्ठा *tsk = शून्य;

	म_लिखो("     task_struct     ->thread.ksp    ->thread.regs    PID   PPID S  P CMD\n");

	अगर (scanhex(&tskv))
		tsk = (काष्ठा task_काष्ठा *)tskv;

	अगर (बनाओ_लाँघ(bus_error_jmp) != 0) अणु
		catch_memory_errors = 0;
		म_लिखो("*** Error dumping task %px\n", tsk);
		वापस;
	पूर्ण

	catch_memory_errors = 1;
	sync();

	अगर (tsk)
		show_task(tsk);
	अन्यथा
		क्रम_each_process(tsk)
			show_task(tsk);

	sync();
	__delay(200);
	catch_memory_errors = 0;
पूर्ण

अटल व्योम proccall(व्योम)
अणु
	अचिन्हित दीर्घ args[8];
	अचिन्हित दीर्घ ret;
	पूर्णांक i;
	प्रकार अचिन्हित दीर्घ (*callfunc_t)(अचिन्हित दीर्घ, अचिन्हित दीर्घ,
			अचिन्हित दीर्घ, अचिन्हित दीर्घ, अचिन्हित दीर्घ,
			अचिन्हित दीर्घ, अचिन्हित दीर्घ, अचिन्हित दीर्घ);
	callfunc_t func;

	अगर (!scanhex(&adrs))
		वापस;
	अगर (termch != '\n')
		termch = 0;
	क्रम (i = 0; i < 8; ++i)
		args[i] = 0;
	क्रम (i = 0; i < 8; ++i) अणु
		अगर (!scanhex(&args[i]) || termch == '\n')
			अवरोध;
		termch = 0;
	पूर्ण
	func = (callfunc_t) adrs;
	ret = 0;
	अगर (बनाओ_लाँघ(bus_error_jmp) == 0) अणु
		catch_memory_errors = 1;
		sync();
		ret = func(args[0], args[1], args[2], args[3],
			   args[4], args[5], args[6], args[7]);
		sync();
		म_लिखो("return value is 0x%lx\n", ret);
	पूर्ण अन्यथा अणु
		म_लिखो("*** %x exception occurred\n", fault_except);
	पूर्ण
	catch_memory_errors = 0;
पूर्ण

/* Input scanning routines */
पूर्णांक
skipbl(व्योम)
अणु
	पूर्णांक c;

	अगर( termch != 0 )अणु
		c = termch;
		termch = 0;
	पूर्ण अन्यथा
		c = inअक्षर();
	जबतक( c == ' ' || c == '\t' )
		c = inअक्षर();
	वापस c;
पूर्ण

#घोषणा N_PTREGS	44
अटल स्थिर अक्षर *regnames[N_PTREGS] = अणु
	"r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7",
	"r8", "r9", "r10", "r11", "r12", "r13", "r14", "r15",
	"r16", "r17", "r18", "r19", "r20", "r21", "r22", "r23",
	"r24", "r25", "r26", "r27", "r28", "r29", "r30", "r31",
	"pc", "msr", "or3", "ctr", "lr", "xer", "ccr",
#अगर_घोषित CONFIG_PPC64
	"softe",
#अन्यथा
	"mq",
#पूर्ण_अगर
	"trap", "dar", "dsisr", "res"
पूर्ण;

पूर्णांक
scanhex(अचिन्हित दीर्घ *vp)
अणु
	पूर्णांक c, d;
	अचिन्हित दीर्घ v;

	c = skipbl();
	अगर (c == '%') अणु
		/* parse रेजिस्टर name */
		अक्षर regname[8];
		पूर्णांक i;

		क्रम (i = 0; i < माप(regname) - 1; ++i) अणु
			c = inअक्षर();
			अगर (!है_अक्षर_अंक(c)) अणु
				termch = c;
				अवरोध;
			पूर्ण
			regname[i] = c;
		पूर्ण
		regname[i] = 0;
		i = match_string(regnames, N_PTREGS, regname);
		अगर (i < 0) अणु
			म_लिखो("invalid register name '%%%s'\n", regname);
			वापस 0;
		पूर्ण
		अगर (xmon_regs == शून्य) अणु
			म_लिखो("regs not available\n");
			वापस 0;
		पूर्ण
		*vp = ((अचिन्हित दीर्घ *)xmon_regs)[i];
		वापस 1;
	पूर्ण

	/* skip leading "0x" अगर any */

	अगर (c == '0') अणु
		c = inअक्षर();
		अगर (c == 'x') अणु
			c = inअक्षर();
		पूर्ण अन्यथा अणु
			d = hexdigit(c);
			अगर (d == खातापूर्ण) अणु
				termch = c;
				*vp = 0;
				वापस 1;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (c == '$') अणु
		पूर्णांक i;
		क्रम (i=0; i<63; i++) अणु
			c = inअक्षर();
			अगर (है_खाली(c) || c == '\0') अणु
				termch = c;
				अवरोध;
			पूर्ण
			पंचांगpstr[i] = c;
		पूर्ण
		पंचांगpstr[i++] = 0;
		*vp = 0;
		अगर (बनाओ_लाँघ(bus_error_jmp) == 0) अणु
			catch_memory_errors = 1;
			sync();
			*vp = kallsyms_lookup_name(पंचांगpstr);
			sync();
		पूर्ण
		catch_memory_errors = 0;
		अगर (!(*vp)) अणु
			म_लिखो("unknown symbol '%s'\n", पंचांगpstr);
			वापस 0;
		पूर्ण
		वापस 1;
	पूर्ण

	d = hexdigit(c);
	अगर (d == खातापूर्ण) अणु
		termch = c;
		वापस 0;
	पूर्ण
	v = 0;
	करो अणु
		v = (v << 4) + d;
		c = inअक्षर();
		d = hexdigit(c);
	पूर्ण जबतक (d != खातापूर्ण);
	termch = c;
	*vp = v;
	वापस 1;
पूर्ण

अटल व्योम
scannl(व्योम)
अणु
	पूर्णांक c;

	c = termch;
	termch = 0;
	जबतक( c != '\n' )
		c = inअक्षर();
पूर्ण

अटल पूर्णांक hexdigit(पूर्णांक c)
अणु
	अगर( '0' <= c && c <= '9' )
		वापस c - '0';
	अगर( 'A' <= c && c <= 'F' )
		वापस c - ('A' - 10);
	अगर( 'a' <= c && c <= 'f' )
		वापस c - ('a' - 10);
	वापस खातापूर्ण;
पूर्ण

व्योम
माला_लोtring(अक्षर *s, पूर्णांक size)
अणु
	पूर्णांक c;

	c = skipbl();
	अगर (c == '\n') अणु
		*s = 0;
		वापस;
	पूर्ण

	करो अणु
		अगर( size > 1 )अणु
			*s++ = c;
			--size;
		पूर्ण
		c = inअक्षर();
	पूर्ण जबतक( c != ' ' && c != '\t' && c != '\n' );
	termch = c;
	*s = 0;
पूर्ण

अटल अक्षर line[256];
अटल अक्षर *lineptr;

अटल व्योम
flush_input(व्योम)
अणु
	lineptr = शून्य;
पूर्ण

अटल पूर्णांक
inअक्षर(व्योम)
अणु
	अगर (lineptr == शून्य || *lineptr == 0) अणु
		अगर (xmon_माला_लो(line, माप(line)) == शून्य) अणु
			lineptr = शून्य;
			वापस खातापूर्ण;
		पूर्ण
		lineptr = line;
	पूर्ण
	वापस *lineptr++;
पूर्ण

अटल व्योम
take_input(अक्षर *str)
अणु
	lineptr = str;
पूर्ण


अटल व्योम
symbol_lookup(व्योम)
अणु
	पूर्णांक type = inअक्षर();
	अचिन्हित दीर्घ addr, cpu;
	व्योम __percpu *ptr = शून्य;
	अटल अक्षर पंचांगp[64];

	चयन (type) अणु
	हाल 'a':
		अगर (scanhex(&addr))
			xmon_prपूर्णांक_symbol(addr, ": ", "\n");
		termch = 0;
		अवरोध;
	हाल 's':
		माला_लोtring(पंचांगp, 64);
		अगर (बनाओ_लाँघ(bus_error_jmp) == 0) अणु
			catch_memory_errors = 1;
			sync();
			addr = kallsyms_lookup_name(पंचांगp);
			अगर (addr)
				म_लिखो("%s: %lx\n", पंचांगp, addr);
			अन्यथा
				म_लिखो("Symbol '%s' not found.\n", पंचांगp);
			sync();
		पूर्ण
		catch_memory_errors = 0;
		termch = 0;
		अवरोध;
	हाल 'p':
		माला_लोtring(पंचांगp, 64);
		अगर (बनाओ_लाँघ(bus_error_jmp) == 0) अणु
			catch_memory_errors = 1;
			sync();
			ptr = (व्योम __percpu *)kallsyms_lookup_name(पंचांगp);
			sync();
		पूर्ण

		अगर (ptr &&
		    ptr >= (व्योम __percpu *)__per_cpu_start &&
		    ptr < (व्योम __percpu *)__per_cpu_end)
		अणु
			अगर (scanhex(&cpu) && cpu < num_possible_cpus()) अणु
				addr = (अचिन्हित दीर्घ)per_cpu_ptr(ptr, cpu);
			पूर्ण अन्यथा अणु
				cpu = raw_smp_processor_id();
				addr = (अचिन्हित दीर्घ)this_cpu_ptr(ptr);
			पूर्ण

			म_लिखो("%s for cpu 0x%lx: %lx\n", पंचांगp, cpu, addr);
		पूर्ण अन्यथा अणु
			म_लिखो("Percpu symbol '%s' not found.\n", पंचांगp);
		पूर्ण

		catch_memory_errors = 0;
		termch = 0;
		अवरोध;
	पूर्ण
पूर्ण


/* Prपूर्णांक an address in numeric and symbolic क्रमm (अगर possible) */
अटल व्योम xmon_prपूर्णांक_symbol(अचिन्हित दीर्घ address, स्थिर अक्षर *mid,
			      स्थिर अक्षर *after)
अणु
	अक्षर *modname;
	स्थिर अक्षर *name = शून्य;
	अचिन्हित दीर्घ offset, size;

	म_लिखो(REG, address);
	अगर (बनाओ_लाँघ(bus_error_jmp) == 0) अणु
		catch_memory_errors = 1;
		sync();
		name = kallsyms_lookup(address, &size, &offset, &modname,
				       पंचांगpstr);
		sync();
		/* रुको a little जबतक to see अगर we get a machine check */
		__delay(200);
	पूर्ण

	catch_memory_errors = 0;

	अगर (name) अणु
		म_लिखो("%s%s+%#lx/%#lx", mid, name, offset, size);
		अगर (modname)
			म_लिखो(" [%s]", modname);
	पूर्ण
	म_लिखो("%s", after);
पूर्ण

#अगर_घोषित CONFIG_PPC_BOOK3S_64
व्योम dump_segments(व्योम)
अणु
	पूर्णांक i;
	अचिन्हित दीर्घ esid,vsid;
	अचिन्हित दीर्घ llp;

	म_लिखो("SLB contents of cpu 0x%x\n", smp_processor_id());

	क्रम (i = 0; i < mmu_slb_size; i++) अणु
		यंत्र अस्थिर("slbmfee  %0,%1" : "=r" (esid) : "r" (i));
		यंत्र अस्थिर("slbmfev  %0,%1" : "=r" (vsid) : "r" (i));

		अगर (!esid && !vsid)
			जारी;

		म_लिखो("%02d %016lx %016lx", i, esid, vsid);

		अगर (!(esid & SLB_ESID_V)) अणु
			म_लिखो("\n");
			जारी;
		पूर्ण

		llp = vsid & SLB_VSID_LLP;
		अगर (vsid & SLB_VSID_B_1T) अणु
			म_लिखो("  1T  ESID=%9lx  VSID=%13lx LLP:%3lx \n",
				GET_ESID_1T(esid),
				(vsid & ~SLB_VSID_B) >> SLB_VSID_SHIFT_1T,
				llp);
		पूर्ण अन्यथा अणु
			म_लिखो(" 256M ESID=%9lx  VSID=%13lx LLP:%3lx \n",
				GET_ESID(esid),
				(vsid & ~SLB_VSID_B) >> SLB_VSID_SHIFT,
				llp);
		पूर्ण
	पूर्ण
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_PPC_BOOK3S_32
व्योम dump_segments(व्योम)
अणु
	पूर्णांक i;

	म_लिखो("sr0-15 =");
	क्रम (i = 0; i < 16; ++i)
		म_लिखो(" %x", mfsr(i << 28));
	म_लिखो("\n");
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_44x
अटल व्योम dump_tlb_44x(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < PPC44x_TLB_SIZE; i++) अणु
		अचिन्हित दीर्घ w0,w1,w2;
		यंत्र अस्थिर("tlbre  %0,%1,0" : "=r" (w0) : "r" (i));
		यंत्र अस्थिर("tlbre  %0,%1,1" : "=r" (w1) : "r" (i));
		यंत्र अस्थिर("tlbre  %0,%1,2" : "=r" (w2) : "r" (i));
		म_लिखो("[%02x] %08lx %08lx %08lx ", i, w0, w1, w2);
		अगर (w0 & PPC44x_TLB_VALID) अणु
			म_लिखो("V %08lx -> %01lx%08lx %c%c%c%c%c",
			       w0 & PPC44x_TLB_EPN_MASK,
			       w1 & PPC44x_TLB_ERPN_MASK,
			       w1 & PPC44x_TLB_RPN_MASK,
			       (w2 & PPC44x_TLB_W) ? 'W' : 'w',
			       (w2 & PPC44x_TLB_I) ? 'I' : 'i',
			       (w2 & PPC44x_TLB_M) ? 'M' : 'm',
			       (w2 & PPC44x_TLB_G) ? 'G' : 'g',
			       (w2 & PPC44x_TLB_E) ? 'E' : 'e');
		पूर्ण
		म_लिखो("\n");
	पूर्ण
पूर्ण
#पूर्ण_अगर /* CONFIG_44x */

#अगर_घोषित CONFIG_PPC_BOOK3E
अटल व्योम dump_tlb_book3e(व्योम)
अणु
	u32 mmucfg, pidmask, lpidmask;
	u64 ramask;
	पूर्णांक i, tlb, ntlbs, pidsz, lpidsz, rasz, lrat = 0;
	पूर्णांक mmu_version;
	अटल स्थिर अक्षर *pgsz_names[] = अणु
		"  1K",
		"  2K",
		"  4K",
		"  8K",
		" 16K",
		" 32K",
		" 64K",
		"128K",
		"256K",
		"512K",
		"  1M",
		"  2M",
		"  4M",
		"  8M",
		" 16M",
		" 32M",
		" 64M",
		"128M",
		"256M",
		"512M",
		"  1G",
		"  2G",
		"  4G",
		"  8G",
		" 16G",
		" 32G",
		" 64G",
		"128G",
		"256G",
		"512G",
		"  1T",
		"  2T",
	पूर्ण;

	/* Gather some infos about the MMU */
	mmucfg = mfspr(SPRN_MMUCFG);
	mmu_version = (mmucfg & 3) + 1;
	ntlbs = ((mmucfg >> 2) & 3) + 1;
	pidsz = ((mmucfg >> 6) & 0x1f) + 1;
	lpidsz = (mmucfg >> 24) & 0xf;
	rasz = (mmucfg >> 16) & 0x7f;
	अगर ((mmu_version > 1) && (mmucfg & 0x10000))
		lrat = 1;
	म_लिखो("Book3E MMU MAV=%d.0,%d TLBs,%d-bit PID,%d-bit LPID,%d-bit RA\n",
	       mmu_version, ntlbs, pidsz, lpidsz, rasz);
	pidmask = (1ul << pidsz) - 1;
	lpidmask = (1ul << lpidsz) - 1;
	ramask = (1ull << rasz) - 1;

	क्रम (tlb = 0; tlb < ntlbs; tlb++) अणु
		u32 tlbcfg;
		पूर्णांक nent, assoc, new_cc = 1;
		म_लिखो("TLB %d:\n------\n", tlb);
		चयन(tlb) अणु
		हाल 0:
			tlbcfg = mfspr(SPRN_TLB0CFG);
			अवरोध;
		हाल 1:
			tlbcfg = mfspr(SPRN_TLB1CFG);
			अवरोध;
		हाल 2:
			tlbcfg = mfspr(SPRN_TLB2CFG);
			अवरोध;
		हाल 3:
			tlbcfg = mfspr(SPRN_TLB3CFG);
			अवरोध;
		शेष:
			म_लिखो("Unsupported TLB number !\n");
			जारी;
		पूर्ण
		nent = tlbcfg & 0xfff;
		assoc = (tlbcfg >> 24) & 0xff;
		क्रम (i = 0; i < nent; i++) अणु
			u32 mas0 = MAS0_TLBSEL(tlb);
			u32 mas1 = MAS1_TSIZE(BOOK3E_PAGESZ_4K);
			u64 mas2 = 0;
			u64 mas7_mas3;
			पूर्णांक esel = i, cc = i;

			अगर (assoc != 0) अणु
				cc = i / assoc;
				esel = i % assoc;
				mas2 = cc * 0x1000;
			पूर्ण

			mas0 |= MAS0_ESEL(esel);
			mtspr(SPRN_MAS0, mas0);
			mtspr(SPRN_MAS1, mas1);
			mtspr(SPRN_MAS2, mas2);
			यंत्र अस्थिर("tlbre  0,0,0" : : : "memory");
			mas1 = mfspr(SPRN_MAS1);
			mas2 = mfspr(SPRN_MAS2);
			mas7_mas3 = mfspr(SPRN_MAS7_MAS3);
			अगर (assoc && (i % assoc) == 0)
				new_cc = 1;
			अगर (!(mas1 & MAS1_VALID))
				जारी;
			अगर (assoc == 0)
				म_लिखो("%04x- ", i);
			अन्यथा अगर (new_cc)
				म_लिखो("%04x-%c", cc, 'A' + esel);
			अन्यथा
				म_लिखो("    |%c", 'A' + esel);
			new_cc = 0;
			म_लिखो(" %016llx %04x %s %c%c AS%c",
			       mas2 & ~0x3ffull,
			       (mas1 >> 16) & 0x3fff,
			       pgsz_names[(mas1 >> 7) & 0x1f],
			       mas1 & MAS1_IND ? 'I' : ' ',
			       mas1 & MAS1_IPROT ? 'P' : ' ',
			       mas1 & MAS1_TS ? '1' : '0');
			म_लिखो(" %c%c%c%c%c%c%c",
			       mas2 & MAS2_X0 ? 'a' : ' ',
			       mas2 & MAS2_X1 ? 'v' : ' ',
			       mas2 & MAS2_W  ? 'w' : ' ',
			       mas2 & MAS2_I  ? 'i' : ' ',
			       mas2 & MAS2_M  ? 'm' : ' ',
			       mas2 & MAS2_G  ? 'g' : ' ',
			       mas2 & MAS2_E  ? 'e' : ' ');
			म_लिखो(" %016llx", mas7_mas3 & ramask & ~0x7ffull);
			अगर (mas1 & MAS1_IND)
				म_लिखो(" %s\n",
				       pgsz_names[(mas7_mas3 >> 1) & 0x1f]);
			अन्यथा
				म_लिखो(" U%c%c%c S%c%c%c\n",
				       mas7_mas3 & MAS3_UX ? 'x' : ' ',
				       mas7_mas3 & MAS3_UW ? 'w' : ' ',
				       mas7_mas3 & MAS3_UR ? 'r' : ' ',
				       mas7_mas3 & MAS3_SX ? 'x' : ' ',
				       mas7_mas3 & MAS3_SW ? 'w' : ' ',
				       mas7_mas3 & MAS3_SR ? 'r' : ' ');
		पूर्ण
	पूर्ण
पूर्ण
#पूर्ण_अगर /* CONFIG_PPC_BOOK3E */

अटल व्योम xmon_init(पूर्णांक enable)
अणु
	अगर (enable) अणु
		__debugger = xmon;
		__debugger_ipi = xmon_ipi;
		__debugger_bpt = xmon_bpt;
		__debugger_sstep = xmon_sstep;
		__debugger_iabr_match = xmon_iabr_match;
		__debugger_अवरोध_match = xmon_अवरोध_match;
		__debugger_fault_handler = xmon_fault_handler;

#अगर_घोषित CONFIG_PPC_PSERIES
		/*
		 * Get the token here to aव्योम trying to get a lock
		 * during the crash, causing a deadlock.
		 */
		set_indicator_token = rtas_token("set-indicator");
#पूर्ण_अगर
	पूर्ण अन्यथा अणु
		__debugger = शून्य;
		__debugger_ipi = शून्य;
		__debugger_bpt = शून्य;
		__debugger_sstep = शून्य;
		__debugger_iabr_match = शून्य;
		__debugger_अवरोध_match = शून्य;
		__debugger_fault_handler = शून्य;
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_MAGIC_SYSRQ
अटल व्योम sysrq_handle_xmon(पूर्णांक key)
अणु
	अगर (xmon_is_locked_करोwn()) अणु
		clear_all_bpt();
		xmon_init(0);
		वापस;
	पूर्ण
	/* ensure xmon is enabled */
	xmon_init(1);
	debugger(get_irq_regs());
	अगर (!xmon_on)
		xmon_init(0);
पूर्ण

अटल स्थिर काष्ठा sysrq_key_op sysrq_xmon_op = अणु
	.handler =	sysrq_handle_xmon,
	.help_msg =	"xmon(x)",
	.action_msg =	"Entering xmon",
पूर्ण;

अटल पूर्णांक __init setup_xmon_sysrq(व्योम)
अणु
	रेजिस्टर_sysrq_key('x', &sysrq_xmon_op);
	वापस 0;
पूर्ण
device_initcall(setup_xmon_sysrq);
#पूर्ण_अगर /* CONFIG_MAGIC_SYSRQ */

अटल व्योम clear_all_bpt(व्योम)
अणु
	पूर्णांक i;

	/* clear/unpatch all अवरोधpoपूर्णांकs */
	हटाओ_bpts();
	हटाओ_cpu_bpts();

	/* Disable all अवरोधpoपूर्णांकs */
	क्रम (i = 0; i < NBPTS; ++i)
		bpts[i].enabled = 0;

	/* Clear any data or iabr अवरोधpoपूर्णांकs */
	iabr = शून्य;
	क्रम (i = 0; i < nr_wp_slots(); i++)
		dabr[i].enabled = 0;
पूर्ण

#अगर_घोषित CONFIG_DEBUG_FS
अटल पूर्णांक xmon_dbgfs_set(व्योम *data, u64 val)
अणु
	xmon_on = !!val;
	xmon_init(xmon_on);

	/* make sure all अवरोधpoपूर्णांकs हटाओd when disabling */
	अगर (!xmon_on) अणु
		clear_all_bpt();
		get_output_lock();
		म_लिखो("xmon: All breakpoints cleared\n");
		release_output_lock();
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक xmon_dbgfs_get(व्योम *data, u64 *val)
अणु
	*val = xmon_on;
	वापस 0;
पूर्ण

DEFINE_SIMPLE_ATTRIBUTE(xmon_dbgfs_ops, xmon_dbgfs_get,
			xmon_dbgfs_set, "%llu\n");

अटल पूर्णांक __init setup_xmon_dbgfs(व्योम)
अणु
	debugfs_create_file("xmon", 0600, घातerpc_debugfs_root, शून्य,
				&xmon_dbgfs_ops);
	वापस 0;
पूर्ण
device_initcall(setup_xmon_dbgfs);
#पूर्ण_अगर /* CONFIG_DEBUG_FS */

अटल पूर्णांक xmon_early __initdata;

अटल पूर्णांक __init early_parse_xmon(अक्षर *p)
अणु
	अगर (xmon_is_locked_करोwn()) अणु
		xmon_init(0);
		xmon_early = 0;
		xmon_on = 0;
	पूर्ण अन्यथा अगर (!p || म_भेदन(p, "early", 5) == 0) अणु
		/* just "xmon" is equivalent to "xmon=early" */
		xmon_init(1);
		xmon_early = 1;
		xmon_on = 1;
	पूर्ण अन्यथा अगर (म_भेदन(p, "on", 2) == 0) अणु
		xmon_init(1);
		xmon_on = 1;
	पूर्ण अन्यथा अगर (म_भेदन(p, "rw", 2) == 0) अणु
		xmon_init(1);
		xmon_on = 1;
		xmon_is_ro = false;
	पूर्ण अन्यथा अगर (म_भेदन(p, "ro", 2) == 0) अणु
		xmon_init(1);
		xmon_on = 1;
		xmon_is_ro = true;
	पूर्ण अन्यथा अगर (म_भेदन(p, "off", 3) == 0)
		xmon_on = 0;
	अन्यथा
		वापस 1;

	वापस 0;
पूर्ण
early_param("xmon", early_parse_xmon);

व्योम __init xmon_setup(व्योम)
अणु
	अगर (xmon_on)
		xmon_init(1);
	अगर (xmon_early)
		debugger(शून्य);
पूर्ण

#अगर_घोषित CONFIG_SPU_BASE

काष्ठा spu_info अणु
	काष्ठा spu *spu;
	u64 saved_mfc_sr1_RW;
	u32 saved_spu_runcntl_RW;
	अचिन्हित दीर्घ dump_addr;
	u8 stopped_ok;
पूर्ण;

#घोषणा XMON_NUM_SPUS	16	/* Enough क्रम current hardware */

अटल काष्ठा spu_info spu_info[XMON_NUM_SPUS];

व्योम xmon_रेजिस्टर_spus(काष्ठा list_head *list)
अणु
	काष्ठा spu *spu;

	list_क्रम_each_entry(spu, list, full_list) अणु
		अगर (spu->number >= XMON_NUM_SPUS) अणु
			WARN_ON(1);
			जारी;
		पूर्ण

		spu_info[spu->number].spu = spu;
		spu_info[spu->number].stopped_ok = 0;
		spu_info[spu->number].dump_addr = (अचिन्हित दीर्घ)
				spu_info[spu->number].spu->local_store;
	पूर्ण
पूर्ण

अटल व्योम stop_spus(व्योम)
अणु
	काष्ठा spu *spu;
	पूर्णांक i;
	u64 पंचांगp;

	क्रम (i = 0; i < XMON_NUM_SPUS; i++) अणु
		अगर (!spu_info[i].spu)
			जारी;

		अगर (बनाओ_लाँघ(bus_error_jmp) == 0) अणु
			catch_memory_errors = 1;
			sync();

			spu = spu_info[i].spu;

			spu_info[i].saved_spu_runcntl_RW =
				in_be32(&spu->problem->spu_runcntl_RW);

			पंचांगp = spu_mfc_sr1_get(spu);
			spu_info[i].saved_mfc_sr1_RW = पंचांगp;

			पंचांगp &= ~MFC_STATE1_MASTER_RUN_CONTROL_MASK;
			spu_mfc_sr1_set(spu, पंचांगp);

			sync();
			__delay(200);

			spu_info[i].stopped_ok = 1;

			म_लिखो("Stopped spu %.2d (was %s)\n", i,
					spu_info[i].saved_spu_runcntl_RW ?
					"running" : "stopped");
		पूर्ण अन्यथा अणु
			catch_memory_errors = 0;
			म_लिखो("*** Error stopping spu %.2d\n", i);
		पूर्ण
		catch_memory_errors = 0;
	पूर्ण
पूर्ण

अटल व्योम restart_spus(व्योम)
अणु
	काष्ठा spu *spu;
	पूर्णांक i;

	क्रम (i = 0; i < XMON_NUM_SPUS; i++) अणु
		अगर (!spu_info[i].spu)
			जारी;

		अगर (!spu_info[i].stopped_ok) अणु
			म_लिखो("*** Error, spu %d was not successfully stopped"
					", not restarting\n", i);
			जारी;
		पूर्ण

		अगर (बनाओ_लाँघ(bus_error_jmp) == 0) अणु
			catch_memory_errors = 1;
			sync();

			spu = spu_info[i].spu;
			spu_mfc_sr1_set(spu, spu_info[i].saved_mfc_sr1_RW);
			out_be32(&spu->problem->spu_runcntl_RW,
					spu_info[i].saved_spu_runcntl_RW);

			sync();
			__delay(200);

			म_लिखो("Restarted spu %.2d\n", i);
		पूर्ण अन्यथा अणु
			catch_memory_errors = 0;
			म_लिखो("*** Error restarting spu %.2d\n", i);
		पूर्ण
		catch_memory_errors = 0;
	पूर्ण
पूर्ण

#घोषणा DUMP_WIDTH	23
#घोषणा DUMP_VALUE(क्रमmat, field, value)				\
करो अणु									\
	अगर (बनाओ_लाँघ(bus_error_jmp) == 0) अणु				\
		catch_memory_errors = 1;				\
		sync();							\
		म_लिखो("  %-*s = "क्रमmat"\n", DUMP_WIDTH,		\
				#field, value);				\
		sync();							\
		__delay(200);						\
	पूर्ण अन्यथा अणु							\
		catch_memory_errors = 0;				\
		म_लिखो("  %-*s = *** Error reading field.\n",		\
					DUMP_WIDTH, #field);		\
	पूर्ण								\
	catch_memory_errors = 0;					\
पूर्ण जबतक (0)

#घोषणा DUMP_FIELD(obj, क्रमmat, field)	\
	DUMP_VALUE(क्रमmat, field, obj->field)

अटल व्योम dump_spu_fields(काष्ठा spu *spu)
अणु
	म_लिखो("Dumping spu fields at address %p:\n", spu);

	DUMP_FIELD(spu, "0x%x", number);
	DUMP_FIELD(spu, "%s", name);
	DUMP_FIELD(spu, "0x%lx", local_store_phys);
	DUMP_FIELD(spu, "0x%p", local_store);
	DUMP_FIELD(spu, "0x%lx", ls_size);
	DUMP_FIELD(spu, "0x%x", node);
	DUMP_FIELD(spu, "0x%lx", flags);
	DUMP_FIELD(spu, "%llu", class_0_pending);
	DUMP_FIELD(spu, "0x%llx", class_0_dar);
	DUMP_FIELD(spu, "0x%llx", class_1_dar);
	DUMP_FIELD(spu, "0x%llx", class_1_dsisr);
	DUMP_FIELD(spu, "0x%x", irqs[0]);
	DUMP_FIELD(spu, "0x%x", irqs[1]);
	DUMP_FIELD(spu, "0x%x", irqs[2]);
	DUMP_FIELD(spu, "0x%x", slb_replace);
	DUMP_FIELD(spu, "%d", pid);
	DUMP_FIELD(spu, "0x%p", mm);
	DUMP_FIELD(spu, "0x%p", ctx);
	DUMP_FIELD(spu, "0x%p", rq);
	DUMP_FIELD(spu, "0x%llx", बारtamp);
	DUMP_FIELD(spu, "0x%lx", problem_phys);
	DUMP_FIELD(spu, "0x%p", problem);
	DUMP_VALUE("0x%x", problem->spu_runcntl_RW,
			in_be32(&spu->problem->spu_runcntl_RW));
	DUMP_VALUE("0x%x", problem->spu_status_R,
			in_be32(&spu->problem->spu_status_R));
	DUMP_VALUE("0x%x", problem->spu_npc_RW,
			in_be32(&spu->problem->spu_npc_RW));
	DUMP_FIELD(spu, "0x%p", priv2);
	DUMP_FIELD(spu, "0x%p", pdata);
पूर्ण

अटल पूर्णांक spu_inst_dump(अचिन्हित दीर्घ adr, दीर्घ count, पूर्णांक praddr)
अणु
	वापस generic_inst_dump(adr, count, praddr, prपूर्णांक_insn_spu);
पूर्ण

अटल व्योम dump_spu_ls(अचिन्हित दीर्घ num, पूर्णांक subcmd)
अणु
	अचिन्हित दीर्घ offset, addr, ls_addr;

	अगर (बनाओ_लाँघ(bus_error_jmp) == 0) अणु
		catch_memory_errors = 1;
		sync();
		ls_addr = (अचिन्हित दीर्घ)spu_info[num].spu->local_store;
		sync();
		__delay(200);
	पूर्ण अन्यथा अणु
		catch_memory_errors = 0;
		म_लिखो("*** Error: accessing spu info for spu %ld\n", num);
		वापस;
	पूर्ण
	catch_memory_errors = 0;

	अगर (scanhex(&offset))
		addr = ls_addr + offset;
	अन्यथा
		addr = spu_info[num].dump_addr;

	अगर (addr >= ls_addr + LS_SIZE) अणु
		म_लिखो("*** Error: address outside of local store\n");
		वापस;
	पूर्ण

	चयन (subcmd) अणु
	हाल 'i':
		addr += spu_inst_dump(addr, 16, 1);
		last_cmd = "sdi\n";
		अवरोध;
	शेष:
		prdump(addr, 64);
		addr += 64;
		last_cmd = "sd\n";
		अवरोध;
	पूर्ण

	spu_info[num].dump_addr = addr;
पूर्ण

अटल पूर्णांक करो_spu_cmd(व्योम)
अणु
	अटल अचिन्हित दीर्घ num = 0;
	पूर्णांक cmd, subcmd = 0;

	cmd = inअक्षर();
	चयन (cmd) अणु
	हाल 's':
		stop_spus();
		अवरोध;
	हाल 'r':
		restart_spus();
		अवरोध;
	हाल 'd':
		subcmd = inअक्षर();
		अगर (है_षष्ठादशक(subcmd) || subcmd == '\n')
			termch = subcmd;
		fallthrough;
	हाल 'f':
		scanhex(&num);
		अगर (num >= XMON_NUM_SPUS || !spu_info[num].spu) अणु
			म_लिखो("*** Error: invalid spu number\n");
			वापस 0;
		पूर्ण

		चयन (cmd) अणु
		हाल 'f':
			dump_spu_fields(spu_info[num].spu);
			अवरोध;
		शेष:
			dump_spu_ls(num, subcmd);
			अवरोध;
		पूर्ण

		अवरोध;
	शेष:
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण
#अन्यथा /* ! CONFIG_SPU_BASE */
अटल पूर्णांक करो_spu_cmd(व्योम)
अणु
	वापस -1;
पूर्ण
#पूर्ण_अगर
