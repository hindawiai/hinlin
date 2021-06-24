<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <linux/debugfs.h>
#समावेश <linux/ras.h>
#समावेश "debugfs.h"

काष्ठा dentry *ras_debugfs_dir;

अटल atomic_t trace_count = ATOMIC_INIT(0);

पूर्णांक ras_userspace_consumers(व्योम)
अणु
	वापस atomic_पढ़ो(&trace_count);
पूर्ण
EXPORT_SYMBOL_GPL(ras_userspace_consumers);

अटल पूर्णांक trace_show(काष्ठा seq_file *m, व्योम *v)
अणु
	वापस atomic_पढ़ो(&trace_count);
पूर्ण

अटल पूर्णांक trace_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	atomic_inc(&trace_count);
	वापस single_खोलो(file, trace_show, शून्य);
पूर्ण

अटल पूर्णांक trace_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	atomic_dec(&trace_count);
	वापस single_release(inode, file);
पूर्ण

अटल स्थिर काष्ठा file_operations trace_fops = अणु
	.खोलो    = trace_खोलो,
	.पढ़ो    = seq_पढ़ो,
	.llseek  = seq_lseek,
	.release = trace_release,
पूर्ण;

पूर्णांक __init ras_add_daemon_trace(व्योम)
अणु
	काष्ठा dentry *fentry;

	अगर (!ras_debugfs_dir)
		वापस -ENOENT;

	fentry = debugfs_create_file("daemon_active", S_IRUSR, ras_debugfs_dir,
				     शून्य, &trace_fops);
	अगर (!fentry)
		वापस -ENODEV;

	वापस 0;

पूर्ण

व्योम __init ras_debugfs_init(व्योम)
अणु
	ras_debugfs_dir = debugfs_create_dir("ras", शून्य);
पूर्ण
