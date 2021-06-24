<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * sysctl.c - Code क्रम sysctl handling in NTFS Linux kernel driver. Part of
 *	      the Linux-NTFS project. Adapted from the old NTFS driver,
 *	      Copyright (C) 1997 Martin von Lथघwis, Rथऊgis Duchesne
 *
 * Copyright (c) 2002-2005 Anton Altaparmakov
 */

#अगर_घोषित DEBUG

#समावेश <linux/module.h>

#अगर_घोषित CONFIG_SYSCTL

#समावेश <linux/proc_fs.h>
#समावेश <linux/sysctl.h>

#समावेश "sysctl.h"
#समावेश "debug.h"

/* Definition of the ntfs sysctl. */
अटल काष्ठा ctl_table ntfs_sysctls[] = अणु
	अणु
		.procname	= "ntfs-debug",
		.data		= &debug_msgs,		/* Data poपूर्णांकer and size. */
		.maxlen		= माप(debug_msgs),
		.mode		= 0644,			/* Mode, proc handler. */
		.proc_handler	= proc_करोपूर्णांकvec
	पूर्ण,
	अणुपूर्ण
पूर्ण;

/* Define the parent directory /proc/sys/fs. */
अटल काष्ठा ctl_table sysctls_root[] = अणु
	अणु
		.procname	= "fs",
		.mode		= 0555,
		.child		= ntfs_sysctls
	पूर्ण,
	अणुपूर्ण
पूर्ण;

/* Storage क्रम the sysctls header. */
अटल काष्ठा ctl_table_header *sysctls_root_table;

/**
 * ntfs_sysctl - add or हटाओ the debug sysctl
 * @add:	add (1) or हटाओ (0) the sysctl
 *
 * Add or हटाओ the debug sysctl. Return 0 on success or -त्रुटि_सं on error.
 */
पूर्णांक ntfs_sysctl(पूर्णांक add)
अणु
	अगर (add) अणु
		BUG_ON(sysctls_root_table);
		sysctls_root_table = रेजिस्टर_sysctl_table(sysctls_root);
		अगर (!sysctls_root_table)
			वापस -ENOMEM;
	पूर्ण अन्यथा अणु
		BUG_ON(!sysctls_root_table);
		unरेजिस्टर_sysctl_table(sysctls_root_table);
		sysctls_root_table = शून्य;
	पूर्ण
	वापस 0;
पूर्ण

#पूर्ण_अगर /* CONFIG_SYSCTL */
#पूर्ण_अगर /* DEBUG */
