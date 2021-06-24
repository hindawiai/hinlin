<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/* aपंचांगclip.h - Classical IP over ATM */
 
/* Written 1995-1998 by Werner Almesberger, EPFL LRC/ICA */
 

#अगर_अघोषित LINUX_ATMCLIP_H
#घोषणा LINUX_ATMCLIP_H

#समावेश <linux/sockios.h>
#समावेश <linux/aपंचांगioc.h>


#घोषणा RFC1483LLC_LEN	8		/* LLC+OUI+PID = 8 */
#घोषणा RFC1626_MTU	9180		/* RFC1626 शेष MTU */

#घोषणा CLIP_DEFAULT_IDLETIMER 1200	/* 20 minutes, see RFC1755 */
#घोषणा CLIP_CHECK_INTERVAL	 10	/* check every ten seconds */

#घोषणा	SIOCMKCLIP	_IO('a',ATMIOC_CLIP)	/* create IP पूर्णांकerface */

#पूर्ण_अगर
