<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * linux/fs/nfs/sysctl.c
 *
 * Sysctl पूर्णांकerface to NFS parameters
 */
#समावेश <linux/types.h>
#समावेश <linux/linkage.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/fs.h>
#समावेश <linux/sysctl.h>
#समावेश <linux/module.h>
#समावेश <linux/nfs_fs.h>

अटल काष्ठा ctl_table_header *nfs_callback_sysctl_table;

अटल काष्ठा ctl_table nfs_cb_sysctls[] = अणु
	अणु
		.procname	= "nfs_mountpoint_timeout",
		.data		= &nfs_mountpoपूर्णांक_expiry_समयout,
		.maxlen		= माप(nfs_mountpoपूर्णांक_expiry_समयout),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_jअगरfies,
	पूर्ण,
	अणु
		.procname	= "nfs_congestion_kb",
		.data		= &nfs_congestion_kb,
		.maxlen		= माप(nfs_congestion_kb),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा ctl_table nfs_cb_sysctl_dir[] = अणु
	अणु
		.procname = "nfs",
		.mode = 0555,
		.child = nfs_cb_sysctls,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा ctl_table nfs_cb_sysctl_root[] = अणु
	अणु
		.procname = "fs",
		.mode = 0555,
		.child = nfs_cb_sysctl_dir,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

पूर्णांक nfs_रेजिस्टर_sysctl(व्योम)
अणु
	nfs_callback_sysctl_table = रेजिस्टर_sysctl_table(nfs_cb_sysctl_root);
	अगर (nfs_callback_sysctl_table == शून्य)
		वापस -ENOMEM;
	वापस 0;
पूर्ण

व्योम nfs_unरेजिस्टर_sysctl(व्योम)
अणु
	unरेजिस्टर_sysctl_table(nfs_callback_sysctl_table);
	nfs_callback_sysctl_table = शून्य;
पूर्ण
