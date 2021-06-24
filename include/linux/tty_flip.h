<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_TTY_FLIP_H
#घोषणा _LINUX_TTY_FLIP_H

बाह्य पूर्णांक tty_buffer_set_limit(काष्ठा tty_port *port, पूर्णांक limit);
बाह्य पूर्णांक tty_buffer_space_avail(काष्ठा tty_port *port);
बाह्य पूर्णांक tty_buffer_request_room(काष्ठा tty_port *port, माप_प्रकार size);
बाह्य पूर्णांक tty_insert_flip_string_flags(काष्ठा tty_port *port,
		स्थिर अचिन्हित अक्षर *अक्षरs, स्थिर अक्षर *flags, माप_प्रकार size);
बाह्य पूर्णांक tty_insert_flip_string_fixed_flag(काष्ठा tty_port *port,
		स्थिर अचिन्हित अक्षर *अक्षरs, अक्षर flag, माप_प्रकार size);
बाह्य पूर्णांक tty_prepare_flip_string(काष्ठा tty_port *port,
		अचिन्हित अक्षर **अक्षरs, माप_प्रकार size);
बाह्य व्योम tty_flip_buffer_push(काष्ठा tty_port *port);
व्योम tty_schedule_flip(काष्ठा tty_port *port);
पूर्णांक __tty_insert_flip_अक्षर(काष्ठा tty_port *port, अचिन्हित अक्षर ch, अक्षर flag);

अटल अंतरभूत पूर्णांक tty_insert_flip_अक्षर(काष्ठा tty_port *port,
					अचिन्हित अक्षर ch, अक्षर flag)
अणु
	काष्ठा tty_buffer *tb = port->buf.tail;
	पूर्णांक change;

	change = (tb->flags & TTYB_NORMAL) && (flag != TTY_NORMAL);
	अगर (!change && tb->used < tb->size) अणु
		अगर (~tb->flags & TTYB_NORMAL)
			*flag_buf_ptr(tb, tb->used) = flag;
		*अक्षर_buf_ptr(tb, tb->used++) = ch;
		वापस 1;
	पूर्ण
	वापस __tty_insert_flip_अक्षर(port, ch, flag);
पूर्ण

अटल अंतरभूत पूर्णांक tty_insert_flip_string(काष्ठा tty_port *port,
		स्थिर अचिन्हित अक्षर *अक्षरs, माप_प्रकार size)
अणु
	वापस tty_insert_flip_string_fixed_flag(port, अक्षरs, TTY_NORMAL, size);
पूर्ण

बाह्य व्योम tty_buffer_lock_exclusive(काष्ठा tty_port *port);
बाह्य व्योम tty_buffer_unlock_exclusive(काष्ठा tty_port *port);

#पूर्ण_अगर /* _LINUX_TTY_FLIP_H */
