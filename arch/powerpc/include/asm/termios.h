<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Liberally adapted from alpha/termios.h.  In particular, the c_cc[]
 * fields have been reordered so that termio & termios share the
 * common subset in the same order (क्रम brain dead programs that करोn't
 * know or care about the dअगरferences).
 */
#अगर_अघोषित _ASM_POWERPC_TERMIOS_H
#घोषणा _ASM_POWERPC_TERMIOS_H

#समावेश <uapi/यंत्र/termios.h>

/*                   ^C  ^\ del  ^U  ^D   1   0   0   0   0  ^W  ^R  ^Z  ^Q  ^S  ^V  ^U  */
#घोषणा INIT_C_CC "\003\034\177\025\004\001\000\000\000\000\027\022\032\021\023\026\025" 

#समावेश <यंत्र-generic/termios-base.h>

#पूर्ण_अगर	/* _ASM_POWERPC_TERMIOS_H */
