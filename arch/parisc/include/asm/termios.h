<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _PARISC_TERMIOS_H
#घोषणा _PARISC_TERMIOS_H

#समावेश <uapi/यंत्र/termios.h>


/*	पूर्णांकr=^C		quit=^\		erase=del	समाप्त=^U
	eof=^D		vसमय=\0	vmin=\1		sxtc=\0
	start=^Q	stop=^S		susp=^Z		eol=\0
	reprपूर्णांक=^R	discard=^U	werase=^W	lnext=^V
	eol2=\0
*/
#घोषणा INIT_C_CC "\003\034\177\025\004\0\1\0\021\023\032\0\022\017\027\026\0"

/*
 * Translate a "termio" काष्ठाure पूर्णांकo a "termios". Ugh.
 */
#घोषणा SET_LOW_TERMIOS_BITS(termios, termio, x) अणु \
	अचिन्हित लघु __पंचांगp; \
	get_user(__पंचांगp,&(termio)->x); \
	*(अचिन्हित लघु *) &(termios)->x = __पंचांगp; \
पूर्ण

#घोषणा user_termio_to_kernel_termios(termios, termio) \
(अणु \
	SET_LOW_TERMIOS_BITS(termios, termio, c_अगरlag); \
	SET_LOW_TERMIOS_BITS(termios, termio, c_oflag); \
	SET_LOW_TERMIOS_BITS(termios, termio, c_cflag); \
	SET_LOW_TERMIOS_BITS(termios, termio, c_lflag); \
	copy_from_user((termios)->c_cc, (termio)->c_cc, NCC); \
पूर्ण)

/*
 * Translate a "termios" काष्ठाure पूर्णांकo a "termio". Ugh.
 */
#घोषणा kernel_termios_to_user_termio(termio, termios) \
(अणु \
	put_user((termios)->c_अगरlag, &(termio)->c_अगरlag); \
	put_user((termios)->c_oflag, &(termio)->c_oflag); \
	put_user((termios)->c_cflag, &(termio)->c_cflag); \
	put_user((termios)->c_lflag, &(termio)->c_lflag); \
	put_user((termios)->c_line,  &(termio)->c_line); \
	copy_to_user((termio)->c_cc, (termios)->c_cc, NCC); \
पूर्ण)

#घोषणा user_termios_to_kernel_termios(k, u) copy_from_user(k, u, माप(काष्ठा termios2))
#घोषणा kernel_termios_to_user_termios(u, k) copy_to_user(u, k, माप(काष्ठा termios2))
#घोषणा user_termios_to_kernel_termios_1(k, u) copy_from_user(k, u, माप(काष्ठा termios))
#घोषणा kernel_termios_to_user_termios_1(u, k) copy_to_user(u, k, माप(काष्ठा termios))

#पूर्ण_अगर	/* _PARISC_TERMIOS_H */
