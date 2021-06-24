<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/* aपंचांगppp.h - RFC2364 PPPoATM */

/* Written 2000 by Mitchell Blank Jr */

#अगर_अघोषित _LINUX_ATMPPP_H
#घोषणा _LINUX_ATMPPP_H

#समावेश <linux/aपंचांग.h>

#घोषणा PPPOATM_ENCAPS_AUTODETECT	(0)
#घोषणा PPPOATM_ENCAPS_VC		(1)
#घोषणा PPPOATM_ENCAPS_LLC		(2)

/*
 * This is क्रम the ATM_SETBACKEND call - these are like socket families:
 * the first element of the काष्ठाure is the backend number and the rest
 * is per-backend specअगरic
 */
काष्ठा aपंचांग_backend_ppp अणु
	aपंचांग_backend_t	backend_num;	/* ATM_BACKEND_PPP */
	पूर्णांक		encaps;		/* PPPOATM_ENCAPS_* */
पूर्ण;

#पूर्ण_अगर	/* _LINUX_ATMPPP_H */
