<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * The Linux BAYCOM driver क्रम the Baycom serial 1200 baud modem
 * and the parallel 9600 baud modem
 * (C) 1997-1998 by Thomas Sailer, HB9JNX/AE4WA
 */

#अगर_अघोषित _BAYCOM_H
#घोषणा _BAYCOM_H

/* -------------------------------------------------------------------- */
/*
 * काष्ठाs क्रम the IOCTL commands
 */

काष्ठा baycom_debug_data अणु
	अचिन्हित दीर्घ debug1;
	अचिन्हित दीर्घ debug2;
	दीर्घ debug3;
पूर्ण;

काष्ठा baycom_ioctl अणु
	पूर्णांक cmd;
	जोड़ अणु
		काष्ठा baycom_debug_data dbg;
	पूर्ण data;
पूर्ण;

/* -------------------------------------------------------------------- */

/*
 * ioctl values change क्रम baycom
 */
#घोषणा BAYCOMCTL_GETDEBUG       0x92

/* -------------------------------------------------------------------- */

#पूर्ण_अगर /* _BAYCOM_H */

/* --------------------------------------------------------------------- */
