<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * arch/x86/kernel/nmi-selftest.c
 *
 * Testsuite क्रम NMI: IPIs
 *
 * Started by Don Zickus:
 * (using lib/locking-selftest.c as a guide)
 *
 *   Copyright (C) 2011 Red Hat, Inc., Don Zickus <dzickus@redhat.com>
 */

#समावेश <linux/smp.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/percpu.h>

#समावेश <यंत्र/apic.h>
#समावेश <यंत्र/nmi.h>

#घोषणा SUCCESS		0
#घोषणा FAILURE		1
#घोषणा TIMEOUT		2

अटल पूर्णांक __initdata nmi_fail;

/* check to see अगर NMI IPIs work on this machine */
अटल DECLARE_BITMAP(nmi_ipi_mask, NR_CPUS) __initdata;

अटल पूर्णांक __initdata testहाल_total;
अटल पूर्णांक __initdata testहाल_successes;
अटल पूर्णांक __initdata expected_testहाल_failures;
अटल पूर्णांक __initdata unexpected_testहाल_failures;
अटल पूर्णांक __initdata unexpected_testहाल_unknowns;

अटल पूर्णांक __init nmi_unk_cb(अचिन्हित पूर्णांक val, काष्ठा pt_regs *regs)
अणु
	unexpected_testहाल_unknowns++;
	वापस NMI_HANDLED;
पूर्ण

अटल व्योम __init init_nmi_testsuite(व्योम)
अणु
	/* trap all the unknown NMIs we may generate */
	रेजिस्टर_nmi_handler(NMI_UNKNOWN, nmi_unk_cb, 0, "nmi_selftest_unk",
			__initdata);
पूर्ण

अटल व्योम __init cleanup_nmi_testsuite(व्योम)
अणु
	unरेजिस्टर_nmi_handler(NMI_UNKNOWN, "nmi_selftest_unk");
पूर्ण

अटल पूर्णांक __init test_nmi_ipi_callback(अचिन्हित पूर्णांक val, काष्ठा pt_regs *regs)
अणु
        पूर्णांक cpu = raw_smp_processor_id();

        अगर (cpumask_test_and_clear_cpu(cpu, to_cpumask(nmi_ipi_mask)))
                वापस NMI_HANDLED;

        वापस NMI_DONE;
पूर्ण

अटल व्योम __init test_nmi_ipi(काष्ठा cpumask *mask)
अणु
	अचिन्हित दीर्घ समयout;

	अगर (रेजिस्टर_nmi_handler(NMI_LOCAL, test_nmi_ipi_callback,
				 NMI_FLAG_FIRST, "nmi_selftest", __initdata)) अणु
		nmi_fail = FAILURE;
		वापस;
	पूर्ण

	/* sync above data beक्रमe sending NMI */
	wmb();

	apic->send_IPI_mask(mask, NMI_VECTOR);

	/* Don't रुको दीर्घer than a second */
	समयout = USEC_PER_SEC;
	जबतक (!cpumask_empty(mask) && --समयout)
	        udelay(1);

	/* What happens अगर we समयout, करो we still unरेजिस्टर?? */
	unरेजिस्टर_nmi_handler(NMI_LOCAL, "nmi_selftest");

	अगर (!समयout)
		nmi_fail = TIMEOUT;
	वापस;
पूर्ण

अटल व्योम __init remote_ipi(व्योम)
अणु
	cpumask_copy(to_cpumask(nmi_ipi_mask), cpu_online_mask);
	cpumask_clear_cpu(smp_processor_id(), to_cpumask(nmi_ipi_mask));
	अगर (!cpumask_empty(to_cpumask(nmi_ipi_mask)))
		test_nmi_ipi(to_cpumask(nmi_ipi_mask));
पूर्ण

अटल व्योम __init local_ipi(व्योम)
अणु
	cpumask_clear(to_cpumask(nmi_ipi_mask));
	cpumask_set_cpu(smp_processor_id(), to_cpumask(nmi_ipi_mask));
	test_nmi_ipi(to_cpumask(nmi_ipi_mask));
पूर्ण

अटल व्योम __init reset_nmi(व्योम)
अणु
	nmi_fail = 0;
पूर्ण

अटल व्योम __init करोtest(व्योम (*testहाल_fn)(व्योम), पूर्णांक expected)
अणु
	testहाल_fn();
	/*
	 * Filter out expected failures:
	 */
	अगर (nmi_fail != expected) अणु
		unexpected_testहाल_failures++;

		अगर (nmi_fail == FAILURE)
			prपूर्णांकk(KERN_CONT "FAILED |");
		अन्यथा अगर (nmi_fail == TIMEOUT)
			prपूर्णांकk(KERN_CONT "TIMEOUT|");
		अन्यथा
			prपूर्णांकk(KERN_CONT "ERROR  |");
		dump_stack();
	पूर्ण अन्यथा अणु
		testहाल_successes++;
		prपूर्णांकk(KERN_CONT "  ok  |");
	पूर्ण
	testहाल_total++;

	reset_nmi();
पूर्ण

अटल अंतरभूत व्योम __init prपूर्णांक_testname(स्थिर अक्षर *testname)
अणु
	prपूर्णांकk("%12s:", testname);
पूर्ण

व्योम __init nmi_selftest(व्योम)
अणु
	init_nmi_testsuite();

        /*
	 * Run the testsuite:
	 */
	prपूर्णांकk("----------------\n");
	prपूर्णांकk("| NMI testsuite:\n");
	prपूर्णांकk("--------------------\n");

	prपूर्णांक_testname("remote IPI");
	करोtest(remote_ipi, SUCCESS);
	prपूर्णांकk(KERN_CONT "\n");
	prपूर्णांक_testname("local IPI");
	करोtest(local_ipi, SUCCESS);
	prपूर्णांकk(KERN_CONT "\n");

	cleanup_nmi_testsuite();

	अगर (unexpected_testहाल_failures) अणु
		prपूर्णांकk("--------------------\n");
		prपूर्णांकk("BUG: %3d unexpected failures (out of %3d) - debugging disabled! |\n",
			unexpected_testहाल_failures, testहाल_total);
		prपूर्णांकk("-----------------------------------------------------------------\n");
	पूर्ण अन्यथा अगर (expected_testहाल_failures && testहाल_successes) अणु
		prपूर्णांकk("--------------------\n");
		prपूर्णांकk("%3d out of %3d testcases failed, as expected. |\n",
			expected_testहाल_failures, testहाल_total);
		prपूर्णांकk("----------------------------------------------------\n");
	पूर्ण अन्यथा अगर (expected_testहाल_failures && !testहाल_successes) अणु
		prपूर्णांकk("--------------------\n");
		prपूर्णांकk("All %3d testcases failed, as expected. |\n",
			expected_testहाल_failures);
		prपूर्णांकk("----------------------------------------\n");
	पूर्ण अन्यथा अणु
		prपूर्णांकk("--------------------\n");
		prपूर्णांकk("Good, all %3d testcases passed! |\n",
			testहाल_successes);
		prपूर्णांकk("---------------------------------\n");
	पूर्ण
पूर्ण
