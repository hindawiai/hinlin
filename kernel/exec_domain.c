<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Handling of dअगरferent ABIs (personalities).
 *
 * We group personalities पूर्णांकo execution करोमुख्यs which have their
 * own handlers क्रम kernel entry poपूर्णांकs, संकेत mapping, etc...
 *
 * 2001-05-06	Complete reग_लिखो,  Christoph Hellwig (hch@infradead.org)
 */

#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/kmod.h>
#समावेश <linux/module.h>
#समावेश <linux/personality.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/sched.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/sysctl.h>
#समावेश <linux/types.h>

#अगर_घोषित CONFIG_PROC_FS
अटल पूर्णांक execकरोमुख्यs_proc_show(काष्ठा seq_file *m, व्योम *v)
अणु
	seq_माला_दो(m, "0-0\tLinux           \t[kernel]\n");
	वापस 0;
पूर्ण

अटल पूर्णांक __init proc_execकरोमुख्यs_init(व्योम)
अणु
	proc_create_single("execdomains", 0, शून्य, execकरोमुख्यs_proc_show);
	वापस 0;
पूर्ण
module_init(proc_execकरोमुख्यs_init);
#पूर्ण_अगर

SYSCALL_DEFINE1(personality, अचिन्हित पूर्णांक, personality)
अणु
	अचिन्हित पूर्णांक old = current->personality;

	अगर (personality != 0xffffffff)
		set_personality(personality);

	वापस old;
पूर्ण
