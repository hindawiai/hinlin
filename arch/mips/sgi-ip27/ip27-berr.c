<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 1994, 1995, 1996, 1999, 2000 by Ralf Baechle
 * Copyright (C) 1999, 2000 by Silicon Graphics
 * Copyright (C) 2002  Maciej W. Rozycki
 */
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/संकेत.स>	/* क्रम SIGBUS */
#समावेश <linux/sched.h>	/* schow_regs(), क्रमce_sig() */
#समावेश <linux/sched/debug.h>
#समावेश <linux/sched/संकेत.स>

#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/sn/addrs.h>
#समावेश <यंत्र/sn/agent.h>
#समावेश <यंत्र/sn/arch.h>
#समावेश <यंत्र/tlbdebug.h>
#समावेश <यंत्र/traps.h>
#समावेश <linux/uaccess.h>

अटल व्योम dump_hub_inक्रमmation(अचिन्हित दीर्घ errst0, अचिन्हित दीर्घ errst1)
अणु
	अटल अक्षर *err_type[2][8] = अणु
		अणु शून्य, "Uncached Partial Read PRERR", "DERR", "Read Timeout",
		  शून्य, शून्य, शून्य, शून्य पूर्ण,
		अणु "WERR", "Uncached Partial Write", "PWERR", "Write Timeout",
		  शून्य, शून्य, शून्य, शून्य पूर्ण
	पूर्ण;
	जोड़ pi_err_stat0 st0;
	जोड़ pi_err_stat1 st1;

	st0.pi_stat0_word = errst0;
	st1.pi_stat1_word = errst1;

	अगर (!st0.pi_stat0_fmt.s0_valid) अणु
		pr_info("Hub does not contain valid error information\n");
		वापस;
	पूर्ण

	pr_info("Hub has valid error information:\n");
	अगर (st0.pi_stat0_fmt.s0_ovr_run)
		pr_info("Overrun is set. Error stack may contain additional "
		       "information.\n");
	pr_info("Hub error address is %08lx\n",
		(अचिन्हित दीर्घ)st0.pi_stat0_fmt.s0_addr);
	pr_info("Incoming message command 0x%lx\n",
		(अचिन्हित दीर्घ)st0.pi_stat0_fmt.s0_cmd);
	pr_info("Supplemental field of incoming message is 0x%lx\n",
		(अचिन्हित दीर्घ)st0.pi_stat0_fmt.s0_supl);
	pr_info("T5 Rn (for RRB only) is 0x%lx\n",
		(अचिन्हित दीर्घ)st0.pi_stat0_fmt.s0_t5_req);
	pr_info("Error type is %s\n", err_type[st1.pi_stat1_fmt.s1_rw_rb]
	       [st0.pi_stat0_fmt.s0_err_type] ? : "invalid");
पूर्ण

पूर्णांक ip27_be_handler(काष्ठा pt_regs *regs, पूर्णांक is_fixup)
अणु
	अचिन्हित दीर्घ errst0, errst1;
	पूर्णांक data = regs->cp0_cause & 4;
	पूर्णांक cpu = LOCAL_HUB_L(PI_CPU_NUM);

	अगर (is_fixup)
		वापस MIPS_BE_FIXUP;

	prपूर्णांकk("Slice %c got %cbe at 0x%lx\n", 'A' + cpu, data ? 'd' : 'i',
	       regs->cp0_epc);
	prपूर्णांकk("Hub information:\n");
	prपूर्णांकk("ERR_INT_PEND = 0x%06llx\n", LOCAL_HUB_L(PI_ERR_INT_PEND));
	errst0 = LOCAL_HUB_L(cpu ? PI_ERR_STATUS0_B : PI_ERR_STATUS0_A);
	errst1 = LOCAL_HUB_L(cpu ? PI_ERR_STATUS1_B : PI_ERR_STATUS1_A);
	dump_hub_inक्रमmation(errst0, errst1);
	show_regs(regs);
	dump_tlb_all();
	जबतक(1);
	क्रमce_sig(SIGBUS);
पूर्ण

व्योम __init ip27_be_init(व्योम)
अणु
	/* XXX Initialize all the Hub & Bridge error handling here.  */
	पूर्णांक cpu = LOCAL_HUB_L(PI_CPU_NUM);
	पूर्णांक cpuoff = cpu << 8;

	board_be_handler = ip27_be_handler;

	LOCAL_HUB_S(PI_ERR_INT_PEND,
		    cpu ? PI_ERR_CLEAR_ALL_B : PI_ERR_CLEAR_ALL_A);
	LOCAL_HUB_S(PI_ERR_INT_MASK_A + cpuoff, 0);
	LOCAL_HUB_S(PI_ERR_STACK_ADDR_A + cpuoff, 0);
	LOCAL_HUB_S(PI_ERR_STACK_SIZE, 0);	/* Disable error stack */
	LOCAL_HUB_S(PI_SYSAD_ERRCHK_EN, PI_SYSAD_CHECK_ALL);
पूर्ण
