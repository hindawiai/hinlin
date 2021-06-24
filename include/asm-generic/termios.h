<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_GENERIC_TERMIOS_H
#घोषणा _ASM_GENERIC_TERMIOS_H


#समावेश <linux/uaccess.h>
#समावेश <uapi/यंत्र-generic/termios.h>

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
अटल अंतरभूत पूर्णांक user_termio_to_kernel_termios(काष्ठा ktermios *termios,
						स्थिर काष्ठा termio __user *termio)
अणु
	अचिन्हित लघु पंचांगp;

	अगर (get_user(पंचांगp, &termio->c_अगरlag) < 0)
		जाओ fault;
	termios->c_अगरlag = (0xffff0000 & termios->c_अगरlag) | पंचांगp;

	अगर (get_user(पंचांगp, &termio->c_oflag) < 0)
		जाओ fault;
	termios->c_oflag = (0xffff0000 & termios->c_oflag) | पंचांगp;

	अगर (get_user(पंचांगp, &termio->c_cflag) < 0)
		जाओ fault;
	termios->c_cflag = (0xffff0000 & termios->c_cflag) | पंचांगp;

	अगर (get_user(पंचांगp, &termio->c_lflag) < 0)
		जाओ fault;
	termios->c_lflag = (0xffff0000 & termios->c_lflag) | पंचांगp;

	अगर (get_user(termios->c_line, &termio->c_line) < 0)
		जाओ fault;

	अगर (copy_from_user(termios->c_cc, termio->c_cc, NCC) != 0)
		जाओ fault;

	वापस 0;

 fault:
	वापस -EFAULT;
पूर्ण

/*
 * Translate a "termios" काष्ठाure पूर्णांकo a "termio". Ugh.
 */
अटल अंतरभूत पूर्णांक kernel_termios_to_user_termio(काष्ठा termio __user *termio,
						काष्ठा ktermios *termios)
अणु
	अगर (put_user(termios->c_अगरlag, &termio->c_अगरlag) < 0 ||
	    put_user(termios->c_oflag, &termio->c_oflag) < 0 ||
	    put_user(termios->c_cflag, &termio->c_cflag) < 0 ||
	    put_user(termios->c_lflag, &termio->c_lflag) < 0 ||
	    put_user(termios->c_line,  &termio->c_line) < 0 ||
	    copy_to_user(termio->c_cc, termios->c_cc, NCC) != 0)
		वापस -EFAULT;

	वापस 0;
पूर्ण

#अगर_घोषित TCGETS2
अटल अंतरभूत पूर्णांक user_termios_to_kernel_termios(काष्ठा ktermios *k,
						 काष्ठा termios2 __user *u)
अणु
	वापस copy_from_user(k, u, माप(काष्ठा termios2));
पूर्ण

अटल अंतरभूत पूर्णांक kernel_termios_to_user_termios(काष्ठा termios2 __user *u,
						 काष्ठा ktermios *k)
अणु
	वापस copy_to_user(u, k, माप(काष्ठा termios2));
पूर्ण

अटल अंतरभूत पूर्णांक user_termios_to_kernel_termios_1(काष्ठा ktermios *k,
						   काष्ठा termios __user *u)
अणु
	वापस copy_from_user(k, u, माप(काष्ठा termios));
पूर्ण

अटल अंतरभूत पूर्णांक kernel_termios_to_user_termios_1(काष्ठा termios __user *u,
						   काष्ठा ktermios *k)
अणु
	वापस copy_to_user(u, k, माप(काष्ठा termios));
पूर्ण
#अन्यथा /* TCGETS2 */
अटल अंतरभूत पूर्णांक user_termios_to_kernel_termios(काष्ठा ktermios *k,
						 काष्ठा termios __user *u)
अणु
	वापस copy_from_user(k, u, माप(काष्ठा termios));
पूर्ण

अटल अंतरभूत पूर्णांक kernel_termios_to_user_termios(काष्ठा termios __user *u,
						 काष्ठा ktermios *k)
अणु
	वापस copy_to_user(u, k, माप(काष्ठा termios));
पूर्ण
#पूर्ण_अगर /* TCGETS2 */

#पूर्ण_अगर /* _ASM_GENERIC_TERMIOS_H */
