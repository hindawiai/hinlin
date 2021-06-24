<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Procfs support क्रम lockd
 *
 * Copyright (c) 2014 Jeff Layton <jlayton@primarydata.com>
 */

#समावेश <linux/fs.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/module.h>
#समावेश <linux/nsproxy.h>
#समावेश <net/net_namespace.h>

#समावेश "netns.h"
#समावेश "procfs.h"

/*
 * We only allow strings that start with 'Y', 'y', or '1'.
 */
अटल sमाप_प्रकार
nlm_end_grace_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf, माप_प्रकार size,
		    loff_t *pos)
अणु
	अक्षर *data;
	काष्ठा lockd_net *ln = net_generic(current->nsproxy->net_ns,
					   lockd_net_id);

	अगर (size < 1)
		वापस -EINVAL;

	data = simple_transaction_get(file, buf, size);
	अगर (IS_ERR(data))
		वापस PTR_ERR(data);

	चयन(data[0]) अणु
	हाल 'Y':
	हाल 'y':
	हाल '1':
		locks_end_grace(&ln->lockd_manager);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस size;
पूर्ण

अटल sमाप_प्रकार
nlm_end_grace_पढ़ो(काष्ठा file *file, अक्षर __user *buf, माप_प्रकार size,
		   loff_t *pos)
अणु
	काष्ठा lockd_net *ln = net_generic(current->nsproxy->net_ns,
					   lockd_net_id);
	अक्षर resp[3];

	resp[0] = list_empty(&ln->lockd_manager.list) ? 'Y' : 'N';
	resp[1] = '\n';
	resp[2] = '\0';

	वापस simple_पढ़ो_from_buffer(buf, size, pos, resp, माप(resp));
पूर्ण

अटल स्थिर काष्ठा proc_ops lockd_end_grace_proc_ops = अणु
	.proc_ग_लिखो	= nlm_end_grace_ग_लिखो,
	.proc_पढ़ो	= nlm_end_grace_पढ़ो,
	.proc_lseek	= शेष_llseek,
	.proc_release	= simple_transaction_release,
पूर्ण;

पूर्णांक __init
lockd_create_procfs(व्योम)
अणु
	काष्ठा proc_dir_entry *entry;

	entry = proc_सूची_गढ़ो("fs/lockd", शून्य);
	अगर (!entry)
		वापस -ENOMEM;
	entry = proc_create("nlm_end_grace", S_IRUGO|S_IWUSR, entry,
			    &lockd_end_grace_proc_ops);
	अगर (!entry) अणु
		हटाओ_proc_entry("fs/lockd", शून्य);
		वापस -ENOMEM;
	पूर्ण
	वापस 0;
पूर्ण

व्योम __निकास
lockd_हटाओ_procfs(व्योम)
अणु
	हटाओ_proc_entry("fs/lockd/nlm_end_grace", शून्य);
	हटाओ_proc_entry("fs/lockd", शून्य);
पूर्ण
