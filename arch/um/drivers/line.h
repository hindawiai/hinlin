<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* 
 * Copyright (C) 2001, 2002 Jeff Dike (jdike@karaya.com)
 */

#अगर_अघोषित __LINE_H__
#घोषणा __LINE_H__

#समावेश <linux/list.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/tty.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/mutex.h>
#समावेश "chan_user.h"
#समावेश "mconsole_kern.h"

/* There's only two modअगरiable fields in this - .mc.list and .driver */
काष्ठा line_driver अणु
	स्थिर अक्षर *name;
	स्थिर अक्षर *device_name;
	स्थिर लघु major;
	स्थिर लघु minor_start;
	स्थिर लघु type;
	स्थिर लघु subtype;
	स्थिर पूर्णांक पढ़ो_irq;
	स्थिर अक्षर *पढ़ो_irq_name;
	स्थिर पूर्णांक ग_लिखो_irq;
	स्थिर अक्षर *ग_लिखो_irq_name;
	काष्ठा mc_device mc;
	काष्ठा tty_driver *driver;
पूर्ण;

काष्ठा line अणु
	काष्ठा tty_port port;
	पूर्णांक valid;

	अक्षर *init_str;
	काष्ठा list_head chan_list;
	काष्ठा chan *chan_in, *chan_out;

	/*This lock is actually, mostly, local to*/
	spinlock_t lock;
	पूर्णांक throttled;
	/* Yes, this is a real circular buffer.
	 * XXX: And this should become a काष्ठा kfअगरo!
	 *
	 * buffer poपूर्णांकs to a buffer allocated on demand, of length
	 * LINE_बफ_मानE, head to the start of the ring, tail to the end.*/
	अक्षर *buffer;
	अक्षर *head;
	अक्षर *tail;

	पूर्णांक sigio;
	काष्ठा delayed_work task;
	स्थिर काष्ठा line_driver *driver;
पूर्ण;

बाह्य व्योम line_बंद(काष्ठा tty_काष्ठा *tty, काष्ठा file * filp);
बाह्य पूर्णांक line_खोलो(काष्ठा tty_काष्ठा *tty, काष्ठा file *filp);
बाह्य पूर्णांक line_install(काष्ठा tty_driver *driver, काष्ठा tty_काष्ठा *tty,
	काष्ठा line *line);
बाह्य व्योम line_cleanup(काष्ठा tty_काष्ठा *tty);
बाह्य व्योम line_hangup(काष्ठा tty_काष्ठा *tty);
बाह्य पूर्णांक line_setup(अक्षर **conf, अचिन्हित nlines, अक्षर **def,
		      अक्षर *init, अक्षर *name);
बाह्य पूर्णांक line_ग_लिखो(काष्ठा tty_काष्ठा *tty, स्थिर अचिन्हित अक्षर *buf,
		      पूर्णांक len);
बाह्य व्योम line_set_termios(काष्ठा tty_काष्ठा *tty, काष्ठा ktermios * old);
बाह्य पूर्णांक line_अक्षरs_in_buffer(काष्ठा tty_काष्ठा *tty);
बाह्य व्योम line_flush_buffer(काष्ठा tty_काष्ठा *tty);
बाह्य व्योम line_flush_अक्षरs(काष्ठा tty_काष्ठा *tty);
बाह्य पूर्णांक line_ग_लिखो_room(काष्ठा tty_काष्ठा *tty);
बाह्य व्योम line_throttle(काष्ठा tty_काष्ठा *tty);
बाह्य व्योम line_unthrottle(काष्ठा tty_काष्ठा *tty);

बाह्य अक्षर *add_xterm_umid(अक्षर *base);
बाह्य पूर्णांक line_setup_irq(पूर्णांक fd, पूर्णांक input, पूर्णांक output, काष्ठा line *line,
			  व्योम *data);
बाह्य व्योम line_बंद_chan(काष्ठा line *line);
बाह्य पूर्णांक रेजिस्टर_lines(काष्ठा line_driver *line_driver,
			  स्थिर काष्ठा tty_operations *driver,
			  काष्ठा line *lines, पूर्णांक nlines);
बाह्य पूर्णांक setup_one_line(काष्ठा line *lines, पूर्णांक n, अक्षर *init,
			  स्थिर काष्ठा chan_opts *opts, अक्षर **error_out);
बाह्य व्योम बंद_lines(काष्ठा line *lines, पूर्णांक nlines);

बाह्य पूर्णांक line_config(काष्ठा line *lines, अचिन्हित पूर्णांक माप_lines,
		       अक्षर *str, स्थिर काष्ठा chan_opts *opts,
		       अक्षर **error_out);
बाह्य पूर्णांक line_id(अक्षर **str, पूर्णांक *start_out, पूर्णांक *end_out);
बाह्य पूर्णांक line_हटाओ(काष्ठा line *lines, अचिन्हित पूर्णांक माप_lines, पूर्णांक n,
		       अक्षर **error_out);
बाह्य पूर्णांक line_get_config(अक्षर *dev, काष्ठा line *lines,
			   अचिन्हित पूर्णांक माप_lines, अक्षर *str,
			   पूर्णांक size, अक्षर **error_out);

#पूर्ण_अगर
