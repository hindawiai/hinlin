<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *  S390 version
 *
 *  Derived from "include/asm-i386/termios.h"
 */
#अगर_अघोषित _S390_TERMIOS_H
#घोषणा _S390_TERMIOS_H

#समावेश <uapi/यंत्र/termios.h>


/*	पूर्णांकr=^C		quit=^\		erase=del	समाप्त=^U
	eof=^D		vसमय=\0	vmin=\1		sxtc=\0
	start=^Q	stop=^S		susp=^Z		eol=\0
	reprपूर्णांक=^R	discard=^U	werase=^W	lnext=^V
	eol2=\0
*/
#घोषणा INIT_C_CC "\003\034\177\025\004\0\1\0\021\023\032\0\022\017\027\026\0"

#घोषणा user_termios_to_kernel_termios(k, u) copy_from_user(k, u, माप(काष्ठा termios2))
#घोषणा kernel_termios_to_user_termios(u, k) copy_to_user(u, k, माप(काष्ठा termios2))

#समावेश <यंत्र-generic/termios-base.h>

#पूर्ण_अगर	/* _S390_TERMIOS_H */
