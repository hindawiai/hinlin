<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2010 Werner Fink, Jiri Slaby
 */

#समावेश <linux/console.h>
#समावेश <linux/kernel.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/tty_driver.h>

/*
 * This is handler क्रम /proc/consoles
 */
अटल पूर्णांक show_console_dev(काष्ठा seq_file *m, व्योम *v)
अणु
	अटल स्थिर काष्ठा अणु
		लघु flag;
		अक्षर name;
	पूर्ण con_flags[] = अणु
		अणु CON_ENABLED,		'E' पूर्ण,
		अणु CON_CONSDEV,		'C' पूर्ण,
		अणु CON_BOOT,		'B' पूर्ण,
		अणु CON_PRINTBUFFER,	'p' पूर्ण,
		अणु CON_BRL,		'b' पूर्ण,
		अणु CON_ANYTIME,		'a' पूर्ण,
	पूर्ण;
	अक्षर flags[ARRAY_SIZE(con_flags) + 1];
	काष्ठा console *con = v;
	अचिन्हित पूर्णांक a;
	dev_t dev = 0;

	अगर (con->device) अणु
		स्थिर काष्ठा tty_driver *driver;
		पूर्णांक index;
		driver = con->device(con, &index);
		अगर (driver) अणु
			dev = MKDEV(driver->major, driver->minor_start);
			dev += index;
		पूर्ण
	पूर्ण

	क्रम (a = 0; a < ARRAY_SIZE(con_flags); a++)
		flags[a] = (con->flags & con_flags[a].flag) ?
			con_flags[a].name : ' ';
	flags[a] = 0;

	seq_setwidth(m, 21 - 1);
	seq_म_लिखो(m, "%s%d", con->name, con->index);
	seq_pad(m, ' ');
	seq_म_लिखो(m, "%c%c%c (%s)", con->पढ़ो ? 'R' : '-',
			con->ग_लिखो ? 'W' : '-', con->unblank ? 'U' : '-',
			flags);
	अगर (dev)
		seq_म_लिखो(m, " %4d:%d", MAJOR(dev), MINOR(dev));

	seq_अ_दो(m, '\n');
	वापस 0;
पूर्ण

अटल व्योम *c_start(काष्ठा seq_file *m, loff_t *pos)
अणु
	काष्ठा console *con;
	loff_t off = 0;

	console_lock();
	क्रम_each_console(con)
		अगर (off++ == *pos)
			अवरोध;

	वापस con;
पूर्ण

अटल व्योम *c_next(काष्ठा seq_file *m, व्योम *v, loff_t *pos)
अणु
	काष्ठा console *con = v;
	++*pos;
	वापस con->next;
पूर्ण

अटल व्योम c_stop(काष्ठा seq_file *m, व्योम *v)
अणु
	console_unlock();
पूर्ण

अटल स्थिर काष्ठा seq_operations consoles_op = अणु
	.start	= c_start,
	.next	= c_next,
	.stop	= c_stop,
	.show	= show_console_dev
पूर्ण;

अटल पूर्णांक __init proc_consoles_init(व्योम)
अणु
	proc_create_seq("consoles", 0, शून्य, &consoles_op);
	वापस 0;
पूर्ण
fs_initcall(proc_consoles_init);
