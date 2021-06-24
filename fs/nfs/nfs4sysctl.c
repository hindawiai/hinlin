<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * linux/fs/nfs/nfs4sysctl.c
 *
 * Sysctl पूर्णांकerface to NFS v4 parameters
 *
 * Copyright (c) 2006 Trond Myklebust <Trond.Myklebust@netapp.com>
 */
#समावेश <linux/sysctl.h>
#समावेश <linux/nfs_fs.h>

#समावेश "nfs4_fs.h"
#समावेश "nfs4idmap.h"
#समावेश "callback.h"

अटल स्थिर पूर्णांक nfs_set_port_min;
अटल स्थिर पूर्णांक nfs_set_port_max = 65535;
अटल काष्ठा ctl_table_header *nfs4_callback_sysctl_table;

अटल काष्ठा ctl_table nfs4_cb_sysctls[] = अणु
	अणु
		.procname = "nfs_callback_tcpport",
		.data = &nfs_callback_set_tcpport,
		.maxlen = माप(पूर्णांक),
		.mode = 0644,
		.proc_handler = proc_करोपूर्णांकvec_minmax,
		.extra1 = (पूर्णांक *)&nfs_set_port_min,
		.extra2 = (पूर्णांक *)&nfs_set_port_max,
	पूर्ण,
	अणु
		.procname = "idmap_cache_timeout",
		.data = &nfs_idmap_cache_समयout,
		.maxlen = माप(पूर्णांक),
		.mode = 0644,
		.proc_handler = proc_करोपूर्णांकvec,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा ctl_table nfs4_cb_sysctl_dir[] = अणु
	अणु
		.procname = "nfs",
		.mode = 0555,
		.child = nfs4_cb_sysctls,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा ctl_table nfs4_cb_sysctl_root[] = अणु
	अणु
		.procname = "fs",
		.mode = 0555,
		.child = nfs4_cb_sysctl_dir,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

पूर्णांक nfs4_रेजिस्टर_sysctl(व्योम)
अणु
	nfs4_callback_sysctl_table = रेजिस्टर_sysctl_table(nfs4_cb_sysctl_root);
	अगर (nfs4_callback_sysctl_table == शून्य)
		वापस -ENOMEM;
	वापस 0;
पूर्ण

व्योम nfs4_unरेजिस्टर_sysctl(व्योम)
अणु
	unरेजिस्टर_sysctl_table(nfs4_callback_sysctl_table);
	nfs4_callback_sysctl_table = शून्य;
पूर्ण
