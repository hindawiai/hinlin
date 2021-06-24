<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/kmsg_dump.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/console.h>
#समावेश <linux/माला.स>
#समावेश <shared/init.h>
#समावेश <shared/kern.h>
#समावेश <os.h>

अटल व्योम kmsg_dumper_मानक_निकास(काष्ठा kmsg_dumper *dumper,
				क्रमागत kmsg_dump_reason reason)
अणु
	अटल काष्ठा kmsg_dump_iter iter;
	अटल DEFINE_SPINLOCK(lock);
	अटल अक्षर line[1024];
	काष्ठा console *con;
	अचिन्हित दीर्घ flags;
	माप_प्रकार len = 0;

	/* only dump kmsg when no console is available */
	अगर (!console_trylock())
		वापस;

	क्रम_each_console(con) अणु
		अगर(म_भेद(con->name, "tty") == 0 &&
		   (con->flags & (CON_ENABLED | CON_CONSDEV)) != 0) अणु
			अवरोध;
		पूर्ण
	पूर्ण

	console_unlock();

	अगर (con)
		वापस;

	अगर (!spin_trylock_irqsave(&lock, flags))
		वापस;

	kmsg_dump_शुरुआत(&iter);

	म_लिखो("kmsg_dump:\n");
	जबतक (kmsg_dump_get_line(&iter, true, line, माप(line), &len)) अणु
		line[len] = '\0';
		म_लिखो("%s", line);
	पूर्ण

	spin_unlock_irqrestore(&lock, flags);
पूर्ण

अटल काष्ठा kmsg_dumper kmsg_dumper = अणु
	.dump = kmsg_dumper_मानक_निकास
पूर्ण;

पूर्णांक __init kmsg_dumper_मानक_निकास_init(व्योम)
अणु
	वापस kmsg_dump_रेजिस्टर(&kmsg_dumper);
पूर्ण

__uml_postsetup(kmsg_dumper_मानक_निकास_init);
