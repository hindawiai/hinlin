<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *   Copyright (C) International Business Machines Corp., 2000-2004
 *   Portions Copyright (C) Christoph Hellwig, 2001-2002
 */

#समावेश <linux/fs.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/module.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/uaccess.h>
#समावेश "jfs_incore.h"
#समावेश "jfs_filsys.h"
#समावेश "jfs_debug.h"

#अगर_घोषित PROC_FS_JFS /* see jfs_debug.h */

#अगर_घोषित CONFIG_JFS_DEBUG
अटल पूर्णांक jfs_loglevel_proc_show(काष्ठा seq_file *m, व्योम *v)
अणु
	seq_म_लिखो(m, "%d\n", jfsloglevel);
	वापस 0;
पूर्ण

अटल पूर्णांक jfs_loglevel_proc_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, jfs_loglevel_proc_show, शून्य);
पूर्ण

अटल sमाप_प्रकार jfs_loglevel_proc_ग_लिखो(काष्ठा file *file,
		स्थिर अक्षर __user *buffer, माप_प्रकार count, loff_t *ppos)
अणु
	अक्षर c;

	अगर (get_user(c, buffer))
		वापस -EFAULT;

	/* yes, I know this is an ASCIIism.  --hch */
	अगर (c < '0' || c > '9')
		वापस -EINVAL;
	jfsloglevel = c - '0';
	वापस count;
पूर्ण

अटल स्थिर काष्ठा proc_ops jfs_loglevel_proc_ops = अणु
	.proc_खोलो	= jfs_loglevel_proc_खोलो,
	.proc_पढ़ो	= seq_पढ़ो,
	.proc_lseek	= seq_lseek,
	.proc_release	= single_release,
	.proc_ग_लिखो	= jfs_loglevel_proc_ग_लिखो,
पूर्ण;
#पूर्ण_अगर

व्योम jfs_proc_init(व्योम)
अणु
	काष्ठा proc_dir_entry *base;

	base = proc_सूची_गढ़ो("fs/jfs", शून्य);
	अगर (!base)
		वापस;

#अगर_घोषित CONFIG_JFS_STATISTICS
	proc_create_single("lmstats", 0, base, jfs_lmstats_proc_show);
	proc_create_single("txstats", 0, base, jfs_txstats_proc_show);
	proc_create_single("xtstat", 0, base, jfs_xtstat_proc_show);
	proc_create_single("mpstat", 0, base, jfs_mpstat_proc_show);
#पूर्ण_अगर
#अगर_घोषित CONFIG_JFS_DEBUG
	proc_create_single("TxAnchor", 0, base, jfs_txanchor_proc_show);
	proc_create("loglevel", 0, base, &jfs_loglevel_proc_ops);
#पूर्ण_अगर
पूर्ण

व्योम jfs_proc_clean(व्योम)
अणु
	हटाओ_proc_subtree("fs/jfs", शून्य);
पूर्ण

#पूर्ण_अगर /* PROC_FS_JFS */
