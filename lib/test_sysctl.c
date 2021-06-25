<शैली गुरु>
/*
 * proc sysctl test driver
 *
 * Copyright (C) 2017 Luis R. Rodriguez <mcgrof@kernel.org>
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or at your option any
 * later version; or, when distributed separately from the Linux kernel or
 * when incorporated पूर्णांकo other software packages, subject to the following
 * license:
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms of copyleft-next (version 0.3.1 or later) as published
 * at http://copyleft-next.org/.
 */

/*
 * This module provides an पूर्णांकerface to the proc sysctl पूर्णांकerfaces.  This
 * driver requires CONFIG_PROC_SYSCTL. It will not normally be loaded by the
 * प्रणाली unless explicitly requested by name. You can also build this driver
 * पूर्णांकo your kernel.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/init.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/fs.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/async.h>
#समावेश <linux/delay.h>
#समावेश <linux/vदो_स्मृति.h>

अटल पूर्णांक i_zero;
अटल पूर्णांक i_one_hundred = 100;

काष्ठा test_sysctl_data अणु
	पूर्णांक पूर्णांक_0001;
	पूर्णांक पूर्णांक_0002;
	पूर्णांक पूर्णांक_0003[4];

	पूर्णांक boot_पूर्णांक;

	अचिन्हित पूर्णांक uपूर्णांक_0001;

	अक्षर string_0001[65];

#घोषणा SYSCTL_TEST_BITMAP_SIZE	65536
	अचिन्हित दीर्घ *biपंचांगap_0001;
पूर्ण;

अटल काष्ठा test_sysctl_data test_data = अणु
	.पूर्णांक_0001 = 60,
	.पूर्णांक_0002 = 1,

	.पूर्णांक_0003[0] = 0,
	.पूर्णांक_0003[1] = 1,
	.पूर्णांक_0003[2] = 2,
	.पूर्णांक_0003[3] = 3,

	.boot_पूर्णांक = 0,

	.uपूर्णांक_0001 = 314,

	.string_0001 = "(none)",
पूर्ण;

/* These are all under /proc/sys/debug/test_sysctl/ */
अटल काष्ठा ctl_table test_table[] = अणु
	अणु
		.procname	= "int_0001",
		.data		= &test_data.पूर्णांक_0001,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= &i_zero,
		.extra2         = &i_one_hundred,
	पूर्ण,
	अणु
		.procname	= "int_0002",
		.data		= &test_data.पूर्णांक_0002,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
	अणु
		.procname	= "int_0003",
		.data		= &test_data.पूर्णांक_0003,
		.maxlen		= माप(test_data.पूर्णांक_0003),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
	अणु
		.procname	= "boot_int",
		.data		= &test_data.boot_पूर्णांक,
		.maxlen		= माप(test_data.boot_पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
		.extra1		= SYSCTL_ZERO,
		.extra2         = SYSCTL_ONE,
	पूर्ण,
	अणु
		.procname	= "uint_0001",
		.data		= &test_data.uपूर्णांक_0001,
		.maxlen		= माप(अचिन्हित पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोuपूर्णांकvec,
	पूर्ण,
	अणु
		.procname	= "string_0001",
		.data		= &test_data.string_0001,
		.maxlen		= माप(test_data.string_0001),
		.mode		= 0644,
		.proc_handler	= proc_करोstring,
	पूर्ण,
	अणु
		.procname	= "bitmap_0001",
		.data		= &test_data.biपंचांगap_0001,
		.maxlen		= SYSCTL_TEST_BITMAP_SIZE,
		.mode		= 0644,
		.proc_handler	= proc_करो_large_biपंचांगap,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा ctl_table test_sysctl_table[] = अणु
	अणु
		.procname	= "test_sysctl",
		.maxlen		= 0,
		.mode		= 0555,
		.child		= test_table,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा ctl_table test_sysctl_root_table[] = अणु
	अणु
		.procname	= "debug",
		.maxlen		= 0,
		.mode		= 0555,
		.child		= test_sysctl_table,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा ctl_table_header *test_sysctl_header;

अटल पूर्णांक __init test_sysctl_init(व्योम)
अणु
	test_data.biपंचांगap_0001 = kzalloc(SYSCTL_TEST_BITMAP_SIZE/8, GFP_KERNEL);
	अगर (!test_data.biपंचांगap_0001)
		वापस -ENOMEM;
	test_sysctl_header = रेजिस्टर_sysctl_table(test_sysctl_root_table);
	अगर (!test_sysctl_header) अणु
		kमुक्त(test_data.biपंचांगap_0001);
		वापस -ENOMEM;
	पूर्ण
	वापस 0;
पूर्ण
module_init(test_sysctl_init);

अटल व्योम __निकास test_sysctl_निकास(व्योम)
अणु
	kमुक्त(test_data.biपंचांगap_0001);
	अगर (test_sysctl_header)
		unरेजिस्टर_sysctl_table(test_sysctl_header);
पूर्ण

module_निकास(test_sysctl_निकास);

MODULE_AUTHOR("Luis R. Rodriguez <mcgrof@kernel.org>");
MODULE_LICENSE("GPL");
