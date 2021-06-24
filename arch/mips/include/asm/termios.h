<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 1995, 1996, 2000, 2001 by Ralf Baechle
 * Copyright (C) 2000, 2001 Silicon Graphics, Inc.
 */
#अगर_अघोषित _ASM_TERMIOS_H
#घोषणा _ASM_TERMIOS_H

#समावेश <linux/uaccess.h>
#समावेश <uapi/यंत्र/termios.h>

/*
 *	पूर्णांकr=^C		quit=^\		erase=del	समाप्त=^U
 *	vmin=\1		vसमय=\0	eol2=\0		swtc=\0
 *	start=^Q	stop=^S		susp=^Z		vdsusp=
 *	reprपूर्णांक=^R	discard=^U	werase=^W	lnext=^V
 *	eof=^D		eol=\0
 */
#घोषणा INIT_C_CC "\003\034\177\025\1\0\0\0\021\023\032\0\022\017\027\026\004\0"

#समावेश <linux/माला.स>

/*
 * Translate a "termio" काष्ठाure पूर्णांकo a "termios". Ugh.
 */
अटल अंतरभूत पूर्णांक user_termio_to_kernel_termios(काष्ठा ktermios *termios,
	काष्ठा termio __user *termio)
अणु
	अचिन्हित लघु अगरlag, oflag, cflag, lflag;
	अचिन्हित पूर्णांक err;

	अगर (!access_ok(termio, माप(काष्ठा termio)))
		वापस -EFAULT;

	err = __get_user(अगरlag, &termio->c_अगरlag);
	termios->c_अगरlag = (termios->c_अगरlag & 0xffff0000) | अगरlag;
	err |=__get_user(oflag, &termio->c_oflag);
	termios->c_oflag = (termios->c_oflag & 0xffff0000) | oflag;
	err |=__get_user(cflag, &termio->c_cflag);
	termios->c_cflag = (termios->c_cflag & 0xffff0000) | cflag;
	err |=__get_user(lflag, &termio->c_lflag);
	termios->c_lflag = (termios->c_lflag & 0xffff0000) | lflag;
	err |=__get_user(termios->c_line, &termio->c_line);
	अगर (err)
		वापस -EFAULT;

	अगर (__copy_from_user(termios->c_cc, termio->c_cc, NCC))
		वापस -EFAULT;

	वापस 0;
पूर्ण

/*
 * Translate a "termios" काष्ठाure पूर्णांकo a "termio". Ugh.
 */
अटल अंतरभूत पूर्णांक kernel_termios_to_user_termio(काष्ठा termio __user *termio,
	काष्ठा ktermios *termios)
अणु
	पूर्णांक err;

	अगर (!access_ok(termio, माप(काष्ठा termio)))
		वापस -EFAULT;

	err = __put_user(termios->c_अगरlag, &termio->c_अगरlag);
	err |= __put_user(termios->c_oflag, &termio->c_oflag);
	err |= __put_user(termios->c_cflag, &termio->c_cflag);
	err |= __put_user(termios->c_lflag, &termio->c_lflag);
	err |= __put_user(termios->c_line, &termio->c_line);
	अगर (err)
		वापस -EFAULT;

	अगर (__copy_to_user(termio->c_cc, termios->c_cc, NCC))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक user_termios_to_kernel_termios(काष्ठा ktermios __user *k,
	काष्ठा termios2 *u)
अणु
	वापस copy_from_user(k, u, माप(काष्ठा termios2)) ? -EFAULT : 0;
पूर्ण

अटल अंतरभूत पूर्णांक kernel_termios_to_user_termios(काष्ठा termios2 __user *u,
	काष्ठा ktermios *k)
अणु
	वापस copy_to_user(u, k, माप(काष्ठा termios2)) ? -EFAULT : 0;
पूर्ण

अटल अंतरभूत पूर्णांक user_termios_to_kernel_termios_1(काष्ठा ktermios *k,
	काष्ठा termios __user *u)
अणु
	वापस copy_from_user(k, u, माप(काष्ठा termios)) ? -EFAULT : 0;
पूर्ण

अटल अंतरभूत पूर्णांक kernel_termios_to_user_termios_1(काष्ठा termios __user *u,
	काष्ठा ktermios *k)
अणु
	वापस copy_to_user(u, k, माप(काष्ठा termios)) ? -EFAULT : 0;
पूर्ण

#पूर्ण_अगर /* _ASM_TERMIOS_H */
