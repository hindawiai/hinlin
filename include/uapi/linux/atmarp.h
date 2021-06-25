<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/* aपंचांगarp.h - ATM ARP protocol and kernel-demon पूर्णांकerface definitions */
 
/* Written 1995-1999 by Werner Almesberger, EPFL LRC/ICA */
 

#अगर_अघोषित _LINUX_ATMARP_H
#घोषणा _LINUX_ATMARP_H

#समावेश <linux/types.h>
#समावेश <linux/aपंचांगapi.h>
#समावेश <linux/aपंचांगioc.h>


#घोषणा ATMARP_RETRY_DELAY 30		/* request next resolution or क्रमget
					   NAK after 30 sec - should go पूर्णांकo
					   aपंचांगclip.h */
#घोषणा ATMARP_MAX_UNRES_PACKETS 5	/* queue that many packets जबतक
					   रुकोing क्रम the resolver */


#घोषणा ATMARPD_CTRL	_IO('a',ATMIOC_CLIP+1)	/* become aपंचांगarpd ctrl sock */
#घोषणा ATMARP_MKIP	_IO('a',ATMIOC_CLIP+2)	/* attach socket to IP */
#घोषणा ATMARP_SETENTRY	_IO('a',ATMIOC_CLIP+3)	/* fill or hide ARP entry */
#घोषणा ATMARP_ENCAP	_IO('a',ATMIOC_CLIP+5)	/* change encapsulation */


क्रमागत aपंचांगarp_ctrl_type अणु
	act_invalid,		/* catch uninitialized काष्ठाures */
	act_need,		/* need address resolution */
	act_up,			/* पूर्णांकerface is coming up */
	act_करोwn,		/* पूर्णांकerface is going करोwn */
	act_change		/* पूर्णांकerface configuration has changed */
पूर्ण;

काष्ठा aपंचांगarp_ctrl अणु
	क्रमागत aपंचांगarp_ctrl_type	type;	/* message type */
	पूर्णांक			itf_num;/* पूर्णांकerface number (अगर present) */
	__be32			ip;	/* IP address (act_need only) */
पूर्ण;

#पूर्ण_अगर
