<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * General MIPS MT support routines, usable in AP/SP and SMVP.
 * Copyright (C) 2005 Mips Technologies, Inc
 */

#समावेश <linux/device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/export.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/security.h>

#समावेश <यंत्र/cpu.h>
#समावेश <यंत्र/processor.h>
#समावेश <linux/atomic.h>
#समावेश <यंत्र/hardirq.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/mipsmtregs.h>
#समावेश <यंत्र/r4kcache.h>
#समावेश <यंत्र/cacheflush.h>

पूर्णांक vpelimit;

अटल पूर्णांक __init maxvpes(अक्षर *str)
अणु
	get_option(&str, &vpelimit);

	वापस 1;
पूर्ण

__setup("maxvpes=", maxvpes);

पूर्णांक tclimit;

अटल पूर्णांक __init maxtcs(अक्षर *str)
अणु
	get_option(&str, &tclimit);

	वापस 1;
पूर्ण

__setup("maxtcs=", maxtcs);

/*
 * Dump new MIPS MT state क्रम the core. Does not leave TCs halted.
 * Takes an argument which taken to be a pre-call MVPControl value.
 */

व्योम mips_mt_regdump(अचिन्हित दीर्घ mvpctl)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ vpflags;
	अचिन्हित दीर्घ mvpconf0;
	पूर्णांक nvpe;
	पूर्णांक ntc;
	पूर्णांक i;
	पूर्णांक tc;
	अचिन्हित दीर्घ haltval;
	अचिन्हित दीर्घ tcstatval;

	local_irq_save(flags);
	vpflags = dvpe();
	prपूर्णांकk("=== MIPS MT State Dump ===\n");
	prपूर्णांकk("-- Global State --\n");
	prपूर्णांकk("   MVPControl Passed: %08lx\n", mvpctl);
	prपूर्णांकk("   MVPControl Read: %08lx\n", vpflags);
	prपूर्णांकk("   MVPConf0 : %08lx\n", (mvpconf0 = पढ़ो_c0_mvpconf0()));
	nvpe = ((mvpconf0 & MVPCONF0_PVPE) >> MVPCONF0_PVPE_SHIFT) + 1;
	ntc = ((mvpconf0 & MVPCONF0_PTC) >> MVPCONF0_PTC_SHIFT) + 1;
	prपूर्णांकk("-- per-VPE State --\n");
	क्रम (i = 0; i < nvpe; i++) अणु
		क्रम (tc = 0; tc < ntc; tc++) अणु
			settc(tc);
			अगर ((पढ़ो_tc_c0_tcbind() & TCBIND_CURVPE) == i) अणु
				prपूर्णांकk("  VPE %d\n", i);
				prपूर्णांकk("   VPEControl : %08lx\n",
				       पढ़ो_vpe_c0_vpecontrol());
				prपूर्णांकk("   VPEConf0 : %08lx\n",
				       पढ़ो_vpe_c0_vpeconf0());
				prपूर्णांकk("   VPE%d.Status : %08lx\n",
				       i, पढ़ो_vpe_c0_status());
				prपूर्णांकk("   VPE%d.EPC : %08lx %pS\n",
				       i, पढ़ो_vpe_c0_epc(),
				       (व्योम *) पढ़ो_vpe_c0_epc());
				prपूर्णांकk("   VPE%d.Cause : %08lx\n",
				       i, पढ़ो_vpe_c0_cause());
				prपूर्णांकk("   VPE%d.Config7 : %08lx\n",
				       i, पढ़ो_vpe_c0_config7());
				अवरोध; /* Next VPE */
			पूर्ण
		पूर्ण
	पूर्ण
	prपूर्णांकk("-- per-TC State --\n");
	क्रम (tc = 0; tc < ntc; tc++) अणु
		settc(tc);
		अगर (पढ़ो_tc_c0_tcbind() == पढ़ो_c0_tcbind()) अणु
			/* Are we dumping ourself?  */
			haltval = 0; /* Then we're not halted, and mustn't be */
			tcstatval = flags; /* And pre-dump TCStatus is flags */
			prपूर्णांकk("  TC %d (current TC with VPE EPC above)\n", tc);
		पूर्ण अन्यथा अणु
			haltval = पढ़ो_tc_c0_tchalt();
			ग_लिखो_tc_c0_tchalt(1);
			tcstatval = पढ़ो_tc_c0_tcstatus();
			prपूर्णांकk("  TC %d\n", tc);
		पूर्ण
		prपूर्णांकk("   TCStatus : %08lx\n", tcstatval);
		prपूर्णांकk("   TCBind : %08lx\n", पढ़ो_tc_c0_tcbind());
		prपूर्णांकk("   TCRestart : %08lx %pS\n",
		       पढ़ो_tc_c0_tcrestart(), (व्योम *) पढ़ो_tc_c0_tcrestart());
		prपूर्णांकk("   TCHalt : %08lx\n", haltval);
		prपूर्णांकk("   TCContext : %08lx\n", पढ़ो_tc_c0_tccontext());
		अगर (!haltval)
			ग_लिखो_tc_c0_tchalt(0);
	पूर्ण
	prपूर्णांकk("===========================\n");
	evpe(vpflags);
	local_irq_restore(flags);
पूर्ण

अटल पूर्णांक mt_opt_rpsctl = -1;
अटल पूर्णांक mt_opt_nblsu = -1;
अटल पूर्णांक mt_opt_क्रमceconfig7;
अटल पूर्णांक mt_opt_config7 = -1;

अटल पूर्णांक __init rpsctl_set(अक्षर *str)
अणु
	get_option(&str, &mt_opt_rpsctl);
	वापस 1;
पूर्ण
__setup("rpsctl=", rpsctl_set);

अटल पूर्णांक __init nblsu_set(अक्षर *str)
अणु
	get_option(&str, &mt_opt_nblsu);
	वापस 1;
पूर्ण
__setup("nblsu=", nblsu_set);

अटल पूर्णांक __init config7_set(अक्षर *str)
अणु
	get_option(&str, &mt_opt_config7);
	mt_opt_क्रमceconfig7 = 1;
	वापस 1;
पूर्ण
__setup("config7=", config7_set);

अटल अचिन्हित पूर्णांक itc_base;

अटल पूर्णांक __init set_itc_base(अक्षर *str)
अणु
	get_option(&str, &itc_base);
	वापस 1;
पूर्ण

__setup("itcbase=", set_itc_base);

व्योम mips_mt_set_cpuoptions(व्योम)
अणु
	अचिन्हित पूर्णांक oconfig7 = पढ़ो_c0_config7();
	अचिन्हित पूर्णांक nconfig7 = oconfig7;

	अगर (mt_opt_rpsctl >= 0) अणु
		prपूर्णांकk("34K return prediction stack override set to %d.\n",
			mt_opt_rpsctl);
		अगर (mt_opt_rpsctl)
			nconfig7 |= (1 << 2);
		अन्यथा
			nconfig7 &= ~(1 << 2);
	पूर्ण
	अगर (mt_opt_nblsu >= 0) अणु
		prपूर्णांकk("34K ALU/LSU sync override set to %d.\n", mt_opt_nblsu);
		अगर (mt_opt_nblsu)
			nconfig7 |= (1 << 5);
		अन्यथा
			nconfig7 &= ~(1 << 5);
	पूर्ण
	अगर (mt_opt_क्रमceconfig7) अणु
		prपूर्णांकk("CP0.Config7 forced to 0x%08x.\n", mt_opt_config7);
		nconfig7 = mt_opt_config7;
	पूर्ण
	अगर (oconfig7 != nconfig7) अणु
		__यंत्र__ __अस्थिर("sync");
		ग_लिखो_c0_config7(nconfig7);
		ehb();
		prपूर्णांकk("Config7: 0x%08x\n", पढ़ो_c0_config7());
	पूर्ण

	अगर (itc_base != 0) अणु
		/*
		 * Configure ITC mapping.  This code is very
		 * specअगरic to the 34K core family, which uses
		 * a special mode bit ("ITC") in the ErrCtl
		 * रेजिस्टर to enable access to ITC control
		 * रेजिस्टरs via cache "tag" operations.
		 */
		अचिन्हित दीर्घ ectlval;
		अचिन्हित दीर्घ itcblkgrn;

		/* ErrCtl रेजिस्टर is known as "ecc" to Linux */
		ectlval = पढ़ो_c0_ecc();
		ग_लिखो_c0_ecc(ectlval | (0x1 << 26));
		ehb();
#घोषणा INDEX_0 (0x80000000)
#घोषणा INDEX_8 (0x80000008)
		/* Read "cache tag" क्रम Dcache pseuकरो-index 8 */
		cache_op(Index_Load_Tag_D, INDEX_8);
		ehb();
		itcblkgrn = पढ़ो_c0_dtaglo();
		itcblkgrn &= 0xfffe0000;
		/* Set क्रम 128 byte pitch of ITC cells */
		itcblkgrn |= 0x00000c00;
		/* Stage in Tag रेजिस्टर */
		ग_लिखो_c0_dtaglo(itcblkgrn);
		ehb();
		/* Write out to ITU with CACHE op */
		cache_op(Index_Store_Tag_D, INDEX_8);
		/* Now set base address, and turn ITC on with 0x1 bit */
		ग_लिखो_c0_dtaglo((itc_base & 0xfffffc00) | 0x1 );
		ehb();
		/* Write out to ITU with CACHE op */
		cache_op(Index_Store_Tag_D, INDEX_0);
		ग_लिखो_c0_ecc(ectlval);
		ehb();
		prपूर्णांकk("Mapped %ld ITC cells starting at 0x%08x\n",
			((itcblkgrn & 0x7fe00000) >> 20), itc_base);
	पूर्ण
पूर्ण

काष्ठा class *mt_class;

अटल पूर्णांक __init mt_init(व्योम)
अणु
	काष्ठा class *mtc;

	mtc = class_create(THIS_MODULE, "mt");
	अगर (IS_ERR(mtc))
		वापस PTR_ERR(mtc);

	mt_class = mtc;

	वापस 0;
पूर्ण

subsys_initcall(mt_init);
