<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _SPARC_TERMIOS_H
#घोषणा _SPARC_TERMIOS_H

#समावेश <uapi/यंत्र/termios.h>


/*
 * c_cc अक्षरacters in the termio काष्ठाure.  Oh, how I love being
 * backwardly compatible.  Notice that अक्षरacter 4 and 5 are
 * पूर्णांकerpreted dअगरferently depending on whether ICANON is set in
 * c_lflag.  If it's set, they are used as _Vखातापूर्ण and _VEOL, otherwise
 * as _VMIN and V_TIME.  This is क्रम compatibility with OSF/1 (which
 * is compatible with sysV)...
 */
#घोषणा _VMIN	4
#घोषणा _VTIME	5

/*	पूर्णांकr=^C		quit=^\		erase=del	समाप्त=^U
	eof=^D		eol=\0		eol2=\0		sxtc=\0
	start=^Q	stop=^S		susp=^Z		dsusp=^Y
	reprपूर्णांक=^R	discard=^U	werase=^W	lnext=^V
	vmin=\1         vसमय=\0
*/
#घोषणा INIT_C_CC "\003\034\177\025\004\000\000\000\021\023\032\031\022\025\027\026\001"

/*
 * Translate a "termio" काष्ठाure पूर्णांकo a "termios". Ugh.
 */
#घोषणा user_termio_to_kernel_termios(termios, termio) \
(अणु \
	अचिन्हित लघु पंचांगp; \
	पूर्णांक err; \
	err = get_user(पंचांगp, &(termio)->c_अगरlag); \
	(termios)->c_अगरlag = (0xffff0000 & ((termios)->c_अगरlag)) | पंचांगp; \
	err |= get_user(पंचांगp, &(termio)->c_oflag); \
	(termios)->c_oflag = (0xffff0000 & ((termios)->c_oflag)) | पंचांगp; \
	err |= get_user(पंचांगp, &(termio)->c_cflag); \
	(termios)->c_cflag = (0xffff0000 & ((termios)->c_cflag)) | पंचांगp; \
	err |= get_user(पंचांगp, &(termio)->c_lflag); \
	(termios)->c_lflag = (0xffff0000 & ((termios)->c_lflag)) | पंचांगp; \
	err |= copy_from_user((termios)->c_cc, (termio)->c_cc, NCC); \
	err; \
पूर्ण)

/*
 * Translate a "termios" काष्ठाure पूर्णांकo a "termio". Ugh.
 *
 * Note the "fun" _VMIN overloading.
 */
#घोषणा kernel_termios_to_user_termio(termio, termios) \
(अणु \
	पूर्णांक err; \
	err  = put_user((termios)->c_अगरlag, &(termio)->c_अगरlag); \
	err |= put_user((termios)->c_oflag, &(termio)->c_oflag); \
	err |= put_user((termios)->c_cflag, &(termio)->c_cflag); \
	err |= put_user((termios)->c_lflag, &(termio)->c_lflag); \
	err |= put_user((termios)->c_line,  &(termio)->c_line); \
	err |= copy_to_user((termio)->c_cc, (termios)->c_cc, NCC); \
	अगर (!((termios)->c_lflag & ICANON)) अणु \
		err |= put_user((termios)->c_cc[VMIN], &(termio)->c_cc[_VMIN]); \
		err |= put_user((termios)->c_cc[VTIME], &(termio)->c_cc[_VTIME]); \
	पूर्ण \
	err; \
पूर्ण)

#घोषणा user_termios_to_kernel_termios(k, u) \
(अणु \
	पूर्णांक err; \
	err  = get_user((k)->c_अगरlag, &(u)->c_अगरlag); \
	err |= get_user((k)->c_oflag, &(u)->c_oflag); \
	err |= get_user((k)->c_cflag, &(u)->c_cflag); \
	err |= get_user((k)->c_lflag, &(u)->c_lflag); \
	err |= get_user((k)->c_line,  &(u)->c_line); \
	err |= copy_from_user((k)->c_cc, (u)->c_cc, NCCS); \
	अगर ((k)->c_lflag & ICANON) अणु \
		err |= get_user((k)->c_cc[Vखातापूर्ण], &(u)->c_cc[Vखातापूर्ण]); \
		err |= get_user((k)->c_cc[VEOL], &(u)->c_cc[VEOL]); \
	पूर्ण अन्यथा अणु \
		err |= get_user((k)->c_cc[VMIN],  &(u)->c_cc[_VMIN]); \
		err |= get_user((k)->c_cc[VTIME], &(u)->c_cc[_VTIME]); \
	पूर्ण \
	err |= get_user((k)->c_ispeed,  &(u)->c_ispeed); \
	err |= get_user((k)->c_ospeed,  &(u)->c_ospeed); \
	err; \
पूर्ण)

#घोषणा kernel_termios_to_user_termios(u, k) \
(अणु \
	पूर्णांक err; \
	err  = put_user((k)->c_अगरlag, &(u)->c_अगरlag); \
	err |= put_user((k)->c_oflag, &(u)->c_oflag); \
	err |= put_user((k)->c_cflag, &(u)->c_cflag); \
	err |= put_user((k)->c_lflag, &(u)->c_lflag); \
	err |= put_user((k)->c_line, &(u)->c_line); \
	err |= copy_to_user((u)->c_cc, (k)->c_cc, NCCS); \
	अगर (!((k)->c_lflag & ICANON)) अणु \
		err |= put_user((k)->c_cc[VMIN],  &(u)->c_cc[_VMIN]); \
		err |= put_user((k)->c_cc[VTIME], &(u)->c_cc[_VTIME]); \
	पूर्ण अन्यथा अणु \
		err |= put_user((k)->c_cc[Vखातापूर्ण], &(u)->c_cc[Vखातापूर्ण]); \
		err |= put_user((k)->c_cc[VEOL], &(u)->c_cc[VEOL]); \
	पूर्ण \
	err |= put_user((k)->c_ispeed, &(u)->c_ispeed); \
	err |= put_user((k)->c_ospeed, &(u)->c_ospeed); \
	err; \
पूर्ण)

#घोषणा user_termios_to_kernel_termios_1(k, u) \
(अणु \
	पूर्णांक err; \
	err  = get_user((k)->c_अगरlag, &(u)->c_अगरlag); \
	err |= get_user((k)->c_oflag, &(u)->c_oflag); \
	err |= get_user((k)->c_cflag, &(u)->c_cflag); \
	err |= get_user((k)->c_lflag, &(u)->c_lflag); \
	err |= get_user((k)->c_line,  &(u)->c_line); \
	err |= copy_from_user((k)->c_cc, (u)->c_cc, NCCS); \
	अगर ((k)->c_lflag & ICANON) अणु \
		err |= get_user((k)->c_cc[Vखातापूर्ण], &(u)->c_cc[Vखातापूर्ण]); \
		err |= get_user((k)->c_cc[VEOL], &(u)->c_cc[VEOL]); \
	पूर्ण अन्यथा अणु \
		err |= get_user((k)->c_cc[VMIN],  &(u)->c_cc[_VMIN]); \
		err |= get_user((k)->c_cc[VTIME], &(u)->c_cc[_VTIME]); \
	पूर्ण \
	err; \
पूर्ण)

#घोषणा kernel_termios_to_user_termios_1(u, k) \
(अणु \
	पूर्णांक err; \
	err  = put_user((k)->c_अगरlag, &(u)->c_अगरlag); \
	err |= put_user((k)->c_oflag, &(u)->c_oflag); \
	err |= put_user((k)->c_cflag, &(u)->c_cflag); \
	err |= put_user((k)->c_lflag, &(u)->c_lflag); \
	err |= put_user((k)->c_line, &(u)->c_line); \
	err |= copy_to_user((u)->c_cc, (k)->c_cc, NCCS); \
	अगर (!((k)->c_lflag & ICANON)) अणु \
		err |= put_user((k)->c_cc[VMIN],  &(u)->c_cc[_VMIN]); \
		err |= put_user((k)->c_cc[VTIME], &(u)->c_cc[_VTIME]); \
	पूर्ण अन्यथा अणु \
		err |= put_user((k)->c_cc[Vखातापूर्ण], &(u)->c_cc[Vखातापूर्ण]); \
		err |= put_user((k)->c_cc[VEOL], &(u)->c_cc[VEOL]); \
	पूर्ण \
	err; \
पूर्ण)

#पूर्ण_अगर /* _SPARC_TERMIOS_H */
