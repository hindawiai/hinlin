<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *    ebcdic keycode functions क्रम s390 console drivers
 *
 *    Copyright IBM Corp. 2003
 *    Author(s): Martin Schwidefsky (schwidefsky@de.ibm.com),
 */

#समावेश <linux/tty.h>
#समावेश <linux/tty_flip.h>
#समावेश <linux/keyboard.h>

#घोषणा NR_FN_HANDLER	20

काष्ठा kbd_data;

बाह्य पूर्णांक ebc_funcbufsize, ebc_funcbufleft;
बाह्य अक्षर *ebc_func_table[MAX_NR_FUNC];
बाह्य अक्षर ebc_func_buf[];
बाह्य अक्षर *ebc_funcbufptr;
बाह्य अचिन्हित पूर्णांक ebc_keymap_count;

बाह्य काष्ठा kbdiacruc ebc_accent_table[];
बाह्य अचिन्हित पूर्णांक ebc_accent_table_size;
बाह्य अचिन्हित लघु *ebc_key_maps[MAX_NR_KEYMAPS];
बाह्य अचिन्हित लघु ebc_plain_map[NR_KEYS];

प्रकार व्योम (fn_handler_fn)(काष्ठा kbd_data *);

/*
 * FIXME: explain key_maps tricks.
 */

काष्ठा kbd_data अणु
	काष्ठा tty_port *port;
	अचिन्हित लघु **key_maps;
	अक्षर **func_table;
	fn_handler_fn **fn_handler;
	काष्ठा kbdiacruc *accent_table;
	अचिन्हित पूर्णांक accent_table_size;
	अचिन्हित पूर्णांक diacr;
	अचिन्हित लघु sysrq;
पूर्ण;

काष्ठा kbd_data *kbd_alloc(व्योम);
व्योम kbd_मुक्त(काष्ठा kbd_data *);
व्योम kbd_ascebc(काष्ठा kbd_data *, अचिन्हित अक्षर *);

व्योम kbd_keycode(काष्ठा kbd_data *, अचिन्हित पूर्णांक);
पूर्णांक kbd_ioctl(काष्ठा kbd_data *, अचिन्हित पूर्णांक, अचिन्हित दीर्घ);

/*
 * Helper Functions.
 */
अटल अंतरभूत व्योम
kbd_put_queue(काष्ठा tty_port *port, पूर्णांक ch)
अणु
	tty_insert_flip_अक्षर(port, ch, 0);
	tty_schedule_flip(port);
पूर्ण

अटल अंतरभूत व्योम
kbd_माला_दो_queue(काष्ठा tty_port *port, अक्षर *cp)
अणु
	जबतक (*cp)
		tty_insert_flip_अक्षर(port, *cp++, 0);
	tty_schedule_flip(port);
पूर्ण
