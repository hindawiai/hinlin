<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/init/version.c
 *
 *  Copyright (C) 1992  Theoकरोre Ts'o
 *
 *  May be मुक्तly distributed as part of Linux.
 */

#समावेश <generated/compile.h>
#समावेश <linux/build-salt.h>
#समावेश <linux/elfnote-lto.h>
#समावेश <linux/export.h>
#समावेश <linux/uts.h>
#समावेश <linux/utsname.h>
#समावेश <generated/utsrelease.h>
#समावेश <linux/version.h>
#समावेश <linux/proc_ns.h>

काष्ठा uts_namespace init_uts_ns = अणु
	.ns.count = REFCOUNT_INIT(2),
	.name = अणु
		.sysname	= UTS_SYSNAME,
		.nodename	= UTS_NODENAME,
		.release	= UTS_RELEASE,
		.version	= UTS_VERSION,
		.machine	= UTS_MACHINE,
		.करोमुख्यname	= UTS_DOMAINNAME,
	पूर्ण,
	.user_ns = &init_user_ns,
	.ns.inum = PROC_UTS_INIT_INO,
#अगर_घोषित CONFIG_UTS_NS
	.ns.ops = &utsns_operations,
#पूर्ण_अगर
पूर्ण;
EXPORT_SYMBOL_GPL(init_uts_ns);

/* FIXED STRINGS! Don't touch! */
स्थिर अक्षर linux_banner[] =
	"Linux version " UTS_RELEASE " (" LINUX_COMPILE_BY "@"
	LINUX_COMPILE_HOST ") (" LINUX_COMPILER ") " UTS_VERSION "\n";

स्थिर अक्षर linux_proc_banner[] =
	"%s version %s"
	" (" LINUX_COMPILE_BY "@" LINUX_COMPILE_HOST ")"
	" (" LINUX_COMPILER ") %s\n";

BUILD_SALT;
BUILD_LTO_INFO;
