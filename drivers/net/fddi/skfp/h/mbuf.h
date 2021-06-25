<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/******************************************************************************
 *
 *	(C)Copyright 1998,1999 SysKonnect,
 *	a business unit of Schneider & Koch & Co. Datenप्रणालीe GmbH.
 *
 *	The inक्रमmation in this file is provided "AS IS" without warranty.
 *
 ******************************************************************************/

#अगर_अघोषित	_MBUF_
#घोषणा _MBUF_

#घोषणा M_SIZE	4504

#अगर_अघोषित MAX_MBUF
#घोषणा MAX_MBUF	4
#पूर्ण_अगर

#अगर_अघोषित NO_STD_MBUF
#घोषणा sm_next         m_next
#घोषणा sm_off          m_off
#घोषणा sm_len          m_len
#घोषणा sm_data         m_data
#घोषणा SMbuf           Mbuf
#घोषणा mtod		smtod
#घोषणा mtoकरोff		smtoकरोff
#पूर्ण_अगर

काष्ठा s_mbuf अणु
	काष्ठा s_mbuf	*sm_next ;		/* low level linked list */
	लघु		sm_off ;			/* offset in m_data */
	u_पूर्णांक		sm_len ;			/* len of data */
#अगर_घोषित	PCI
	पूर्णांक		sm_use_count ;
#पूर्ण_अगर
	अक्षर		sm_data[M_SIZE] ;
पूर्ण ;

प्रकार काष्ठा s_mbuf SMbuf ;

/* mbuf head, to typed data */
#घोषणा	smtod(x,t)	((t)((x)->sm_data + (x)->sm_off))
#घोषणा	smtoकरोff(x,t,o)	((t)((x)->sm_data + (o)))

#पूर्ण_अगर	/* _MBUF_ */
