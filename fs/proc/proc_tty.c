<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * proc_tty.c -- handles /proc/tty
 *
 * Copyright 1997, Theoकरोre Ts'o
 */

#समावेश <linux/uaccess.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/समय.स>
#समावेश <linux/proc_fs.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/tty.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/bitops.h>
#समावेश "internal.h"

/*
 * The /proc/tty directory inodes...
 */
अटल काष्ठा proc_dir_entry *proc_tty_driver;

/*
 * This is the handler क्रम /proc/tty/drivers
 */
अटल व्योम show_tty_range(काष्ठा seq_file *m, काष्ठा tty_driver *p,
	dev_t from, पूर्णांक num)
अणु
	seq_म_लिखो(m, "%-20s ", p->driver_name ? p->driver_name : "unknown");
	seq_म_लिखो(m, "/dev/%-8s ", p->name);
	अगर (p->num > 1) अणु
		seq_म_लिखो(m, "%3d %d-%d ", MAJOR(from), MINOR(from),
			MINOR(from) + num - 1);
	पूर्ण अन्यथा अणु
		seq_म_लिखो(m, "%3d %7d ", MAJOR(from), MINOR(from));
	पूर्ण
	चयन (p->type) अणु
	हाल TTY_DRIVER_TYPE_SYSTEM:
		seq_माला_दो(m, "system");
		अगर (p->subtype == SYSTEM_TYPE_TTY)
			seq_माला_दो(m, ":/dev/tty");
		अन्यथा अगर (p->subtype == SYSTEM_TYPE_SYSCONS)
			seq_माला_दो(m, ":console");
		अन्यथा अगर (p->subtype == SYSTEM_TYPE_CONSOLE)
			seq_माला_दो(m, ":vtmaster");
		अवरोध;
	हाल TTY_DRIVER_TYPE_CONSOLE:
		seq_माला_दो(m, "console");
		अवरोध;
	हाल TTY_DRIVER_TYPE_SERIAL:
		seq_माला_दो(m, "serial");
		अवरोध;
	हाल TTY_DRIVER_TYPE_PTY:
		अगर (p->subtype == PTY_TYPE_MASTER)
			seq_माला_दो(m, "pty:master");
		अन्यथा अगर (p->subtype == PTY_TYPE_SLAVE)
			seq_माला_दो(m, "pty:slave");
		अन्यथा
			seq_माला_दो(m, "pty");
		अवरोध;
	शेष:
		seq_म_लिखो(m, "type:%d.%d", p->type, p->subtype);
	पूर्ण
	seq_अ_दो(m, '\n');
पूर्ण

अटल पूर्णांक show_tty_driver(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा tty_driver *p = list_entry(v, काष्ठा tty_driver, tty_drivers);
	dev_t from = MKDEV(p->major, p->minor_start);
	dev_t to = from + p->num;

	अगर (&p->tty_drivers == tty_drivers.next) अणु
		/* pseuकरो-drivers first */
		seq_म_लिखो(m, "%-20s /dev/%-8s ", "/dev/tty", "tty");
		seq_म_लिखो(m, "%3d %7d ", TTYAUX_MAJOR, 0);
		seq_माला_दो(m, "system:/dev/tty\n");
		seq_म_लिखो(m, "%-20s /dev/%-8s ", "/dev/console", "console");
		seq_म_लिखो(m, "%3d %7d ", TTYAUX_MAJOR, 1);
		seq_माला_दो(m, "system:console\n");
#अगर_घोषित CONFIG_UNIX98_PTYS
		seq_म_लिखो(m, "%-20s /dev/%-8s ", "/dev/ptmx", "ptmx");
		seq_म_लिखो(m, "%3d %7d ", TTYAUX_MAJOR, 2);
		seq_माला_दो(m, "system\n");
#पूर्ण_अगर
#अगर_घोषित CONFIG_VT
		seq_म_लिखो(m, "%-20s /dev/%-8s ", "/dev/vc/0", "vc/0");
		seq_म_लिखो(m, "%3d %7d ", TTY_MAJOR, 0);
		seq_माला_दो(m, "system:vtmaster\n");
#पूर्ण_अगर
	पूर्ण

	जबतक (MAJOR(from) < MAJOR(to)) अणु
		dev_t next = MKDEV(MAJOR(from)+1, 0);
		show_tty_range(m, p, from, next - from);
		from = next;
	पूर्ण
	अगर (from != to)
		show_tty_range(m, p, from, to - from);
	वापस 0;
पूर्ण

/* iterator */
अटल व्योम *t_start(काष्ठा seq_file *m, loff_t *pos)
अणु
	mutex_lock(&tty_mutex);
	वापस seq_list_start(&tty_drivers, *pos);
पूर्ण

अटल व्योम *t_next(काष्ठा seq_file *m, व्योम *v, loff_t *pos)
अणु
	वापस seq_list_next(v, &tty_drivers, pos);
पूर्ण

अटल व्योम t_stop(काष्ठा seq_file *m, व्योम *v)
अणु
	mutex_unlock(&tty_mutex);
पूर्ण

अटल स्थिर काष्ठा seq_operations tty_drivers_op = अणु
	.start	= t_start,
	.next	= t_next,
	.stop	= t_stop,
	.show	= show_tty_driver
पूर्ण;

/*
 * This function is called by tty_रेजिस्टर_driver() to handle
 * रेजिस्टरing the driver's /proc handler पूर्णांकo /proc/tty/driver/<foo>
 */
व्योम proc_tty_रेजिस्टर_driver(काष्ठा tty_driver *driver)
अणु
	काष्ठा proc_dir_entry *ent;
		
	अगर (!driver->driver_name || driver->proc_entry ||
	    !driver->ops->proc_show)
		वापस;

	ent = proc_create_single_data(driver->driver_name, 0, proc_tty_driver,
			       driver->ops->proc_show, driver);
	driver->proc_entry = ent;
पूर्ण

/*
 * This function is called by tty_unरेजिस्टर_driver()
 */
व्योम proc_tty_unरेजिस्टर_driver(काष्ठा tty_driver *driver)
अणु
	काष्ठा proc_dir_entry *ent;

	ent = driver->proc_entry;
	अगर (!ent)
		वापस;
		
	हटाओ_proc_entry(ent->name, proc_tty_driver);
	
	driver->proc_entry = शून्य;
पूर्ण

/*
 * Called by proc_root_init() to initialize the /proc/tty subtree
 */
व्योम __init proc_tty_init(व्योम)
अणु
	अगर (!proc_सूची_गढ़ो("tty", शून्य))
		वापस;
	proc_सूची_गढ़ो("tty/ldisc", शून्य);	/* Preserved: it's userspace visible */
	/*
	 * /proc/tty/driver/serial reveals the exact अक्षरacter counts क्रम
	 * serial links which is just too easy to abuse क्रम inferring
	 * password lengths and पूर्णांकer-keystroke timings during password
	 * entry.
	 */
	proc_tty_driver = proc_सूची_गढ़ो_mode("tty/driver", S_IRUSR|S_IXUSR, शून्य);
	proc_create_seq("tty/ldiscs", 0, शून्य, &tty_ldiscs_seq_ops);
	proc_create_seq("tty/drivers", 0, शून्य, &tty_drivers_op);
पूर्ण
