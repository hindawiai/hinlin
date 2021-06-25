<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* termios.h: generic termios/termio user copying/translation
 */

#अगर_अघोषित _ASM_GENERIC_TERMIOS_BASE_H
#घोषणा _ASM_GENERIC_TERMIOS_BASE_H

#समावेश <linux/uaccess.h>

#अगर_अघोषित __ARCH_TERMIO_GETPUT

/*
 * Translate a "termio" काष्ठाure पूर्णांकo a "termios". Ugh.
 */
अटल अंतरभूत पूर्णांक user_termio_to_kernel_termios(काष्ठा ktermios *termios,
						काष्ठा termio __user *termio)
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

#अगर_अघोषित user_termios_to_kernel_termios
#घोषणा user_termios_to_kernel_termios(k, u) copy_from_user(k, u, माप(काष्ठा termios))
#पूर्ण_अगर

#अगर_अघोषित kernel_termios_to_user_termios
#घोषणा kernel_termios_to_user_termios(u, k) copy_to_user(u, k, माप(काष्ठा termios))
#पूर्ण_अगर

#घोषणा user_termios_to_kernel_termios_1(k, u) copy_from_user(k, u, माप(काष्ठा termios))
#घोषणा kernel_termios_to_user_termios_1(u, k) copy_to_user(u, k, माप(काष्ठा termios))

#पूर्ण_अगर	/* __ARCH_TERMIO_GETPUT */

#पूर्ण_अगर /* _ASM_GENERIC_TERMIOS_BASE_H */
