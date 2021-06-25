<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/fs/proc/kmsg.c
 *
 *  Copyright (C) 1992  by Linus Torvalds
 *
 */

#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/समय.स>
#समावेश <linux/kernel.h>
#समावेश <linux/poll.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/fs.h>
#समावेश <linux/syslog.h>

#समावेश <linux/uaccess.h>
#समावेश <यंत्र/पन.स>

बाह्य रुको_queue_head_t log_रुको;

अटल पूर्णांक kmsg_खोलो(काष्ठा inode * inode, काष्ठा file * file)
अणु
	वापस करो_syslog(SYSLOG_ACTION_OPEN, शून्य, 0, SYSLOG_FROM_PROC);
पूर्ण

अटल पूर्णांक kmsg_release(काष्ठा inode * inode, काष्ठा file * file)
अणु
	(व्योम) करो_syslog(SYSLOG_ACTION_CLOSE, शून्य, 0, SYSLOG_FROM_PROC);
	वापस 0;
पूर्ण

अटल sमाप_प्रकार kmsg_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
			 माप_प्रकार count, loff_t *ppos)
अणु
	अगर ((file->f_flags & O_NONBLOCK) &&
	    !करो_syslog(SYSLOG_ACTION_SIZE_UNREAD, शून्य, 0, SYSLOG_FROM_PROC))
		वापस -EAGAIN;
	वापस करो_syslog(SYSLOG_ACTION_READ, buf, count, SYSLOG_FROM_PROC);
पूर्ण

अटल __poll_t kmsg_poll(काष्ठा file *file, poll_table *रुको)
अणु
	poll_रुको(file, &log_रुको, रुको);
	अगर (करो_syslog(SYSLOG_ACTION_SIZE_UNREAD, शून्य, 0, SYSLOG_FROM_PROC))
		वापस EPOLLIN | EPOLLRDNORM;
	वापस 0;
पूर्ण


अटल स्थिर काष्ठा proc_ops kmsg_proc_ops = अणु
	.proc_flags	= PROC_ENTRY_PERMANENT,
	.proc_पढ़ो	= kmsg_पढ़ो,
	.proc_poll	= kmsg_poll,
	.proc_खोलो	= kmsg_खोलो,
	.proc_release	= kmsg_release,
	.proc_lseek	= generic_file_llseek,
पूर्ण;

अटल पूर्णांक __init proc_kmsg_init(व्योम)
अणु
	proc_create("kmsg", S_IRUSR, शून्य, &kmsg_proc_ops);
	वापस 0;
पूर्ण
fs_initcall(proc_kmsg_init);
