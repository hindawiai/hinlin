<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * FIPS 200 support.
 *
 * Copyright (c) 2008 Neil Horman <nhorman@tuxdriver.com>
 */

#समावेश <linux/export.h>
#समावेश <linux/fips.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sysctl.h>
#समावेश <linux/notअगरier.h>

पूर्णांक fips_enabled;
EXPORT_SYMBOL_GPL(fips_enabled);

ATOMIC_NOTIFIER_HEAD(fips_fail_notअगर_chain);
EXPORT_SYMBOL_GPL(fips_fail_notअगर_chain);

/* Process kernel command-line parameter at boot समय. fips=0 or fips=1 */
अटल पूर्णांक fips_enable(अक्षर *str)
अणु
	fips_enabled = !!simple_म_से_दीर्घ(str, शून्य, 0);
	prपूर्णांकk(KERN_INFO "fips mode: %s\n",
		fips_enabled ? "enabled" : "disabled");
	वापस 1;
पूर्ण

__setup("fips=", fips_enable);

अटल काष्ठा ctl_table crypto_sysctl_table[] = अणु
	अणु
		.procname       = "fips_enabled",
		.data           = &fips_enabled,
		.maxlen         = माप(पूर्णांक),
		.mode           = 0444,
		.proc_handler   = proc_करोपूर्णांकvec
	पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा ctl_table crypto_dir_table[] = अणु
	अणु
		.procname       = "crypto",
		.mode           = 0555,
		.child          = crypto_sysctl_table
	पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा ctl_table_header *crypto_sysctls;

अटल व्योम crypto_proc_fips_init(व्योम)
अणु
	crypto_sysctls = रेजिस्टर_sysctl_table(crypto_dir_table);
पूर्ण

अटल व्योम crypto_proc_fips_निकास(व्योम)
अणु
	unरेजिस्टर_sysctl_table(crypto_sysctls);
पूर्ण

व्योम fips_fail_notअगरy(व्योम)
अणु
	अगर (fips_enabled)
		atomic_notअगरier_call_chain(&fips_fail_notअगर_chain, 0, शून्य);
पूर्ण
EXPORT_SYMBOL_GPL(fips_fail_notअगरy);

अटल पूर्णांक __init fips_init(व्योम)
अणु
	crypto_proc_fips_init();
	वापस 0;
पूर्ण

अटल व्योम __निकास fips_निकास(व्योम)
अणु
	crypto_proc_fips_निकास();
पूर्ण

subsys_initcall(fips_init);
module_निकास(fips_निकास);
