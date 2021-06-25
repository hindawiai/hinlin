<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/debugfs.h>
#समावेश <linux/memory_hotplug.h>
#समावेश <linux/seq_file.h>

#समावेश <यंत्र/ptdump.h>

अटल पूर्णांक ptdump_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा ptdump_info *info = m->निजी;

	get_online_mems();
	ptdump_walk(m, info);
	put_online_mems();
	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(ptdump);

व्योम __init ptdump_debugfs_रेजिस्टर(काष्ठा ptdump_info *info, स्थिर अक्षर *name)
अणु
	debugfs_create_file(name, 0400, शून्य, info, &ptdump_fops);
पूर्ण
