<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause
/*
 * Copyright (c) 2014 Raspberry Pi (Trading) Ltd. All rights reserved.
 * Copyright (c) 2010-2012 Broadcom. All rights reserved.
 */

#समावेश <linux/debugfs.h>
#समावेश "vchiq_core.h"
#समावेश "vchiq_arm.h"
#समावेश "vchiq_debugfs.h"

#अगर_घोषित CONFIG_DEBUG_FS

/****************************************************************************
 *
 *   log category entries
 *
 ***************************************************************************/
#घोषणा DEBUGFS_WRITE_BUF_SIZE 256

#घोषणा VCHIQ_LOG_ERROR_STR   "error"
#घोषणा VCHIQ_LOG_WARNING_STR "warning"
#घोषणा VCHIQ_LOG_INFO_STR    "info"
#घोषणा VCHIQ_LOG_TRACE_STR   "trace"

/* Global 'vchiq' debugfs and clients entry used by all instances */
अटल काष्ठा dentry *vchiq_dbg_dir;
अटल काष्ठा dentry *vchiq_dbg_clients;

/* Log category debugfs entries */
काष्ठा vchiq_debugfs_log_entry अणु
	स्थिर अक्षर *name;
	व्योम *plevel;
पूर्ण;

अटल काष्ठा vchiq_debugfs_log_entry vchiq_debugfs_log_entries[] = अणु
	अणु "core", &vchiq_core_log_level पूर्ण,
	अणु "msg",  &vchiq_core_msg_log_level पूर्ण,
	अणु "sync", &vchiq_sync_log_level पूर्ण,
	अणु "susp", &vchiq_susp_log_level पूर्ण,
	अणु "arm",  &vchiq_arm_log_level पूर्ण,
पूर्ण;
अटल पूर्णांक n_log_entries = ARRAY_SIZE(vchiq_debugfs_log_entries);

अटल पूर्णांक debugfs_log_show(काष्ठा seq_file *f, व्योम *offset)
अणु
	पूर्णांक *levp = f->निजी;
	अक्षर *log_value = शून्य;

	चयन (*levp) अणु
	हाल VCHIQ_LOG_ERROR:
		log_value = VCHIQ_LOG_ERROR_STR;
		अवरोध;
	हाल VCHIQ_LOG_WARNING:
		log_value = VCHIQ_LOG_WARNING_STR;
		अवरोध;
	हाल VCHIQ_LOG_INFO:
		log_value = VCHIQ_LOG_INFO_STR;
		अवरोध;
	हाल VCHIQ_LOG_TRACE:
		log_value = VCHIQ_LOG_TRACE_STR;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	seq_म_लिखो(f, "%s\n", log_value ? log_value : "(null)");

	वापस 0;
पूर्ण

अटल पूर्णांक debugfs_log_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, debugfs_log_show, inode->i_निजी);
पूर्ण

अटल sमाप_प्रकार debugfs_log_ग_लिखो(काष्ठा file *file,
	स्थिर अक्षर __user *buffer,
	माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा seq_file *f = (काष्ठा seq_file *)file->निजी_data;
	पूर्णांक *levp = f->निजी;
	अक्षर kbuf[DEBUGFS_WRITE_BUF_SIZE + 1];

	स_रखो(kbuf, 0, DEBUGFS_WRITE_BUF_SIZE + 1);
	अगर (count >= DEBUGFS_WRITE_BUF_SIZE)
		count = DEBUGFS_WRITE_BUF_SIZE;

	अगर (copy_from_user(kbuf, buffer, count))
		वापस -EFAULT;
	kbuf[count - 1] = 0;

	अगर (म_भेदन("error", kbuf, म_माप("error")) == 0)
		*levp = VCHIQ_LOG_ERROR;
	अन्यथा अगर (म_भेदन("warning", kbuf, म_माप("warning")) == 0)
		*levp = VCHIQ_LOG_WARNING;
	अन्यथा अगर (म_भेदन("info", kbuf, म_माप("info")) == 0)
		*levp = VCHIQ_LOG_INFO;
	अन्यथा अगर (म_भेदन("trace", kbuf, म_माप("trace")) == 0)
		*levp = VCHIQ_LOG_TRACE;
	अन्यथा
		*levp = VCHIQ_LOG_DEFAULT;

	*ppos += count;

	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations debugfs_log_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= debugfs_log_खोलो,
	.ग_लिखो		= debugfs_log_ग_लिखो,
	.पढ़ो		= seq_पढ़ो,
	.llseek		= seq_lseek,
	.release	= single_release,
पूर्ण;

अटल पूर्णांक debugfs_usecount_show(काष्ठा seq_file *f, व्योम *offset)
अणु
	काष्ठा vchiq_instance *instance = f->निजी;
	पूर्णांक use_count;

	use_count = vchiq_instance_get_use_count(instance);
	seq_म_लिखो(f, "%d\n", use_count);

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(debugfs_usecount);

अटल पूर्णांक debugfs_trace_show(काष्ठा seq_file *f, व्योम *offset)
अणु
	काष्ठा vchiq_instance *instance = f->निजी;
	पूर्णांक trace;

	trace = vchiq_instance_get_trace(instance);
	seq_म_लिखो(f, "%s\n", trace ? "Y" : "N");

	वापस 0;
पूर्ण

अटल पूर्णांक debugfs_trace_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, debugfs_trace_show, inode->i_निजी);
पूर्ण

अटल sमाप_प्रकार debugfs_trace_ग_लिखो(काष्ठा file *file,
	स्थिर अक्षर __user *buffer,
	माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा seq_file *f = (काष्ठा seq_file *)file->निजी_data;
	काष्ठा vchiq_instance *instance = f->निजी;
	अक्षर firstअक्षर;

	अगर (copy_from_user(&firstअक्षर, buffer, 1))
		वापस -EFAULT;

	चयन (firstअक्षर) अणु
	हाल 'Y':
	हाल 'y':
	हाल '1':
		vchiq_instance_set_trace(instance, 1);
		अवरोध;
	हाल 'N':
	हाल 'n':
	हाल '0':
		vchiq_instance_set_trace(instance, 0);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	*ppos += count;

	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations debugfs_trace_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= debugfs_trace_खोलो,
	.ग_लिखो		= debugfs_trace_ग_लिखो,
	.पढ़ो		= seq_पढ़ो,
	.llseek		= seq_lseek,
	.release	= single_release,
पूर्ण;

/* add an instance (process) to the debugfs entries */
व्योम vchiq_debugfs_add_instance(काष्ठा vchiq_instance *instance)
अणु
	अक्षर pidstr[16];
	काष्ठा dentry *top;

	snम_लिखो(pidstr, माप(pidstr), "%d",
		 vchiq_instance_get_pid(instance));

	top = debugfs_create_dir(pidstr, vchiq_dbg_clients);

	debugfs_create_file("use_count", 0444, top, instance,
			    &debugfs_usecount_fops);
	debugfs_create_file("trace", 0644, top, instance, &debugfs_trace_fops);

	vchiq_instance_get_debugfs_node(instance)->dentry = top;
पूर्ण

व्योम vchiq_debugfs_हटाओ_instance(काष्ठा vchiq_instance *instance)
अणु
	काष्ठा vchiq_debugfs_node *node =
				vchiq_instance_get_debugfs_node(instance);

	debugfs_हटाओ_recursive(node->dentry);
पूर्ण

व्योम vchiq_debugfs_init(व्योम)
अणु
	काष्ठा dentry *dir;
	पूर्णांक i;

	vchiq_dbg_dir = debugfs_create_dir("vchiq", शून्य);
	vchiq_dbg_clients = debugfs_create_dir("clients", vchiq_dbg_dir);

	/* create an entry under <debugfs>/vchiq/log क्रम each log category */
	dir = debugfs_create_dir("log", vchiq_dbg_dir);

	क्रम (i = 0; i < n_log_entries; i++)
		debugfs_create_file(vchiq_debugfs_log_entries[i].name, 0644,
				    dir, vchiq_debugfs_log_entries[i].plevel,
				    &debugfs_log_fops);
पूर्ण

/* हटाओ all the debugfs entries */
व्योम vchiq_debugfs_deinit(व्योम)
अणु
	debugfs_हटाओ_recursive(vchiq_dbg_dir);
पूर्ण

#अन्यथा /* CONFIG_DEBUG_FS */

व्योम vchiq_debugfs_init(व्योम)
अणु
पूर्ण

व्योम vchiq_debugfs_deinit(व्योम)
अणु
पूर्ण

व्योम vchiq_debugfs_add_instance(काष्ठा vchiq_instance *instance)
अणु
पूर्ण

व्योम vchiq_debugfs_हटाओ_instance(काष्ठा vchiq_instance *instance)
अणु
पूर्ण

#पूर्ण_अगर /* CONFIG_DEBUG_FS */
