<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* 
 * Copyright (C) 2000, 2001 Jeff Dike (jdike@karaya.com)
 */

#अगर_अघोषित __CHAN_KERN_H__
#घोषणा __CHAN_KERN_H__

#समावेश <linux/tty.h>
#समावेश <linux/list.h>
#समावेश <linux/console.h>
#समावेश "chan_user.h"
#समावेश "line.h"

काष्ठा chan अणु
	काष्ठा list_head list;
	काष्ठा list_head मुक्त_list;
	काष्ठा line *line;
	अक्षर *dev;
	अचिन्हित पूर्णांक primary:1;
	अचिन्हित पूर्णांक input:1;
	अचिन्हित पूर्णांक output:1;
	अचिन्हित पूर्णांक खोलोed:1;
	अचिन्हित पूर्णांक enabled:1;
	पूर्णांक fd;
	स्थिर काष्ठा chan_ops *ops;
	व्योम *data;
पूर्ण;

बाह्य व्योम chan_पूर्णांकerrupt(काष्ठा line *line, पूर्णांक irq);
बाह्य पूर्णांक parse_chan_pair(अक्षर *str, काष्ठा line *line, पूर्णांक device,
			   स्थिर काष्ठा chan_opts *opts, अक्षर **error_out);
बाह्य पूर्णांक ग_लिखो_chan(काष्ठा chan *chan, स्थिर अक्षर *buf, पूर्णांक len,
			     पूर्णांक ग_लिखो_irq);
बाह्य पूर्णांक console_ग_लिखो_chan(काष्ठा chan *chan, स्थिर अक्षर *buf, 
			      पूर्णांक len);
बाह्य पूर्णांक console_खोलो_chan(काष्ठा line *line, काष्ठा console *co);
बाह्य व्योम deactivate_chan(काष्ठा chan *chan, पूर्णांक irq);
बाह्य व्योम reactivate_chan(काष्ठा chan *chan, पूर्णांक irq);
बाह्य व्योम chan_enable_winch(काष्ठा chan *chan, काष्ठा tty_port *port);
बाह्य पूर्णांक enable_chan(काष्ठा line *line);
बाह्य व्योम बंद_chan(काष्ठा line *line);
बाह्य पूर्णांक chan_winकरोw_size(काष्ठा line *line, 
			     अचिन्हित लघु *rows_out, 
			     अचिन्हित लघु *cols_out);
बाह्य पूर्णांक chan_config_string(काष्ठा line *line, अक्षर *str, पूर्णांक size,
			      अक्षर **error_out);

#पूर्ण_अगर
