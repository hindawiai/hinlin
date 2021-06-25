<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ALPHA_TERMIOS_H
#घोषणा _ALPHA_TERMIOS_H

#समावेश <uapi/यंत्र/termios.h>

/*	eof=^D		eol=\0		eol2=\0		erase=del
	werase=^W	समाप्त=^U		reprपूर्णांक=^R	sxtc=\0
	पूर्णांकr=^C		quit=^\		susp=^Z		<OSF/1 VDSUSP>
	start=^Q	stop=^S		lnext=^V	discard=^U
	vmin=\1		vसमय=\0
*/
#घोषणा INIT_C_CC "\004\000\000\177\027\025\022\000\003\034\032\000\021\023\026\025\001\000"

/*
 * Translate a "termio" काष्ठाure पूर्णांकo a "termios". Ugh.
 */

#घोषणा user_termio_to_kernel_termios(a_termios, u_termio)			\
(अणु										\
	काष्ठा ktermios *k_termios = (a_termios);				\
	काष्ठा termio k_termio;							\
	पूर्णांक canon, ret;								\
										\
	ret = copy_from_user(&k_termio, u_termio, माप(k_termio));		\
	अगर (!ret) अणु								\
		/* Overग_लिखो only the low bits.  */				\
		*(अचिन्हित लघु *)&k_termios->c_अगरlag = k_termio.c_अगरlag;	\
		*(अचिन्हित लघु *)&k_termios->c_oflag = k_termio.c_oflag;	\
		*(अचिन्हित लघु *)&k_termios->c_cflag = k_termio.c_cflag;	\
		*(अचिन्हित लघु *)&k_termios->c_lflag = k_termio.c_lflag;	\
		canon = k_termio.c_lflag & ICANON;				\
										\
		k_termios->c_cc[VINTR]  = k_termio.c_cc[_VINTR];		\
		k_termios->c_cc[VQUIT]  = k_termio.c_cc[_VQUIT];		\
		k_termios->c_cc[VERASE] = k_termio.c_cc[_VERASE];		\
		k_termios->c_cc[VKILL]  = k_termio.c_cc[_VKILL];		\
		k_termios->c_cc[VEOL2]  = k_termio.c_cc[_VEOL2];		\
		k_termios->c_cc[VSWTC]  = k_termio.c_cc[_VSWTC];		\
		k_termios->c_cc[canon ? Vखातापूर्ण : VMIN]  = k_termio.c_cc[_Vखातापूर्ण];	\
		k_termios->c_cc[canon ? VEOL : VTIME] = k_termio.c_cc[_VEOL];	\
	पूर्ण									\
	ret;									\
पूर्ण)

/*
 * Translate a "termios" काष्ठाure पूर्णांकo a "termio". Ugh.
 *
 * Note the "fun" _VMIN overloading.
 */
#घोषणा kernel_termios_to_user_termio(u_termio, a_termios)		\
(अणु									\
	काष्ठा ktermios *k_termios = (a_termios);			\
	काष्ठा termio k_termio;						\
	पूर्णांक canon;							\
									\
	k_termio.c_अगरlag = k_termios->c_अगरlag;				\
	k_termio.c_oflag = k_termios->c_oflag;				\
	k_termio.c_cflag = k_termios->c_cflag;				\
	canon = (k_termio.c_lflag = k_termios->c_lflag) & ICANON;	\
									\
	k_termio.c_line = k_termios->c_line;				\
	k_termio.c_cc[_VINTR]  = k_termios->c_cc[VINTR];		\
	k_termio.c_cc[_VQUIT]  = k_termios->c_cc[VQUIT];		\
	k_termio.c_cc[_VERASE] = k_termios->c_cc[VERASE];		\
	k_termio.c_cc[_VKILL]  = k_termios->c_cc[VKILL];		\
	k_termio.c_cc[_Vखातापूर्ण]   = k_termios->c_cc[canon ? Vखातापूर्ण : VMIN];	\
	k_termio.c_cc[_VEOL]   = k_termios->c_cc[canon ? VEOL : VTIME];	\
	k_termio.c_cc[_VEOL2]  = k_termios->c_cc[VEOL2];		\
	k_termio.c_cc[_VSWTC]  = k_termios->c_cc[VSWTC];		\
									\
	copy_to_user(u_termio, &k_termio, माप(k_termio));		\
पूर्ण)

#घोषणा user_termios_to_kernel_termios(k, u) \
	copy_from_user(k, u, माप(काष्ठा termios2))

#घोषणा kernel_termios_to_user_termios(u, k) \
	copy_to_user(u, k, माप(काष्ठा termios2))

#घोषणा user_termios_to_kernel_termios_1(k, u) \
	copy_from_user(k, u, माप(काष्ठा termios))

#घोषणा kernel_termios_to_user_termios_1(u, k) \
	copy_to_user(u, k, माप(काष्ठा termios))

#पूर्ण_अगर	/* _ALPHA_TERMIOS_H */
