<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * data_अवरोधpoपूर्णांक.c - Sample HW Breakpoपूर्णांक file to watch kernel data address
 *
 * usage: insmod data_अवरोधpoपूर्णांक.ko ksym=<ksym_name>
 *
 * This file is a kernel module that places a अवरोधpoपूर्णांक over ksym_name kernel
 * variable using Hardware Breakpoपूर्णांक रेजिस्टर. The corresponding handler which
 * prपूर्णांकs a backtrace is invoked every समय a ग_लिखो operation is perक्रमmed on
 * that variable.
 *
 * Copyright (C) IBM Corporation, 2009
 *
 * Author: K.Prasad <prasad@linux.vnet.ibm.com>
 */
#समावेश <linux/module.h>	/* Needed by all modules */
#समावेश <linux/kernel.h>	/* Needed क्रम KERN_INFO */
#समावेश <linux/init.h>		/* Needed क्रम the macros */
#समावेश <linux/kallsyms.h>

#समावेश <linux/perf_event.h>
#समावेश <linux/hw_अवरोधpoपूर्णांक.h>

काष्ठा perf_event * __percpu *sample_hbp;

अटल अक्षर ksym_name[KSYM_NAME_LEN] = "jiffies";
module_param_string(ksym, ksym_name, KSYM_NAME_LEN, S_IRUGO);
MODULE_PARM_DESC(ksym, "Kernel symbol to monitor; this module will report any"
			" write operations on the kernel symbol");

अटल व्योम sample_hbp_handler(काष्ठा perf_event *bp,
			       काष्ठा perf_sample_data *data,
			       काष्ठा pt_regs *regs)
अणु
	prपूर्णांकk(KERN_INFO "%s value is changed\n", ksym_name);
	dump_stack();
	prपूर्णांकk(KERN_INFO "Dump stack from sample_hbp_handler\n");
पूर्ण

अटल पूर्णांक __init hw_अवरोध_module_init(व्योम)
अणु
	पूर्णांक ret;
	काष्ठा perf_event_attr attr;
	व्योम *addr = __symbol_get(ksym_name);

	अगर (!addr)
		वापस -ENXIO;

	hw_अवरोधpoपूर्णांक_init(&attr);
	attr.bp_addr = (अचिन्हित दीर्घ)addr;
	attr.bp_len = HW_BREAKPOINT_LEN_4;
	attr.bp_type = HW_BREAKPOINT_W;

	sample_hbp = रेजिस्टर_wide_hw_अवरोधpoपूर्णांक(&attr, sample_hbp_handler, शून्य);
	अगर (IS_ERR((व्योम __क्रमce *)sample_hbp)) अणु
		ret = PTR_ERR((व्योम __क्रमce *)sample_hbp);
		जाओ fail;
	पूर्ण

	prपूर्णांकk(KERN_INFO "HW Breakpoint for %s write installed\n", ksym_name);

	वापस 0;

fail:
	prपूर्णांकk(KERN_INFO "Breakpoint registration failed\n");

	वापस ret;
पूर्ण

अटल व्योम __निकास hw_अवरोध_module_निकास(व्योम)
अणु
	unरेजिस्टर_wide_hw_अवरोधpoपूर्णांक(sample_hbp);
	symbol_put(ksym_name);
	prपूर्णांकk(KERN_INFO "HW Breakpoint for %s write uninstalled\n", ksym_name);
पूर्ण

module_init(hw_अवरोध_module_init);
module_निकास(hw_अवरोध_module_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("K.Prasad");
MODULE_DESCRIPTION("ksym breakpoint");
