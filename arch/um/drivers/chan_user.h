<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2000, 2001 Jeff Dike (jdike@karaya.com)
 */

#अगर_अघोषित __CHAN_USER_H__
#घोषणा __CHAN_USER_H__

#समावेश <init.h>

काष्ठा chan_opts अणु
	व्योम (*स्थिर announce)(अक्षर *dev_name, पूर्णांक dev);
	अक्षर *xterm_title;
	पूर्णांक raw;
पूर्ण;

काष्ठा chan_ops अणु
	अक्षर *type;
	व्योम *(*init)(अक्षर *, पूर्णांक, स्थिर काष्ठा chan_opts *);
	पूर्णांक (*खोलो)(पूर्णांक, पूर्णांक, पूर्णांक, व्योम *, अक्षर **);
	व्योम (*बंद)(पूर्णांक, व्योम *);
	पूर्णांक (*पढ़ो)(पूर्णांक, अक्षर *, व्योम *);
	पूर्णांक (*ग_लिखो)(पूर्णांक, स्थिर अक्षर *, पूर्णांक, व्योम *);
	पूर्णांक (*console_ग_लिखो)(पूर्णांक, स्थिर अक्षर *, पूर्णांक);
	पूर्णांक (*winकरोw_size)(पूर्णांक, व्योम *, अचिन्हित लघु *, अचिन्हित लघु *);
	व्योम (*मुक्त)(व्योम *);
	पूर्णांक winch;
पूर्ण;

बाह्य स्थिर काष्ठा chan_ops fd_ops, null_ops, port_ops, pts_ops, pty_ops,
	tty_ops, xterm_ops;

बाह्य व्योम generic_बंद(पूर्णांक fd, व्योम *unused);
बाह्य पूर्णांक generic_पढ़ो(पूर्णांक fd, अक्षर *c_out, व्योम *unused);
बाह्य पूर्णांक generic_ग_लिखो(पूर्णांक fd, स्थिर अक्षर *buf, पूर्णांक n, व्योम *unused);
बाह्य पूर्णांक generic_console_ग_लिखो(पूर्णांक fd, स्थिर अक्षर *buf, पूर्णांक n);
बाह्य पूर्णांक generic_winकरोw_size(पूर्णांक fd, व्योम *unused, अचिन्हित लघु *rows_out,
			       अचिन्हित लघु *cols_out);
बाह्य व्योम generic_मुक्त(व्योम *data);

काष्ठा tty_port;
बाह्य व्योम रेजिस्टर_winch(पूर्णांक fd,  काष्ठा tty_port *port);
बाह्य व्योम रेजिस्टर_winch_irq(पूर्णांक fd, पूर्णांक tty_fd, पूर्णांक pid,
			       काष्ठा tty_port *port, अचिन्हित दीर्घ stack);

#घोषणा __channel_help(fn, prefix) \
__uml_help(fn, prefix "[0-9]*=<channel description>\n" \
"    Attach a console or serial line to a host channel.  See\n" \
"    http://user-mode-linux.sourceforge.net/old/input.html for a complete\n" \
"    description of this switch.\n\n" \
);

#पूर्ण_अगर
