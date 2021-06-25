<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright 2008  by Karsten Keil <kkeil@novell.com>
 */

#अगर_अघोषित mISDN_CORE_H
#घोषणा mISDN_CORE_H

बाह्य काष्ठा mISDNdevice	*get_mdevice(u_पूर्णांक);
बाह्य पूर्णांक			get_mdevice_count(व्योम);

/* stack status flag */
#घोषणा mISDN_STACK_ACTION_MASK		0x0000ffff
#घोषणा mISDN_STACK_COMMAND_MASK	0x000f0000
#घोषणा mISDN_STACK_STATUS_MASK		0xfff00000
/* action bits 0-15 */
#घोषणा mISDN_STACK_WORK	0
#घोषणा mISDN_STACK_SETUP	1
#घोषणा mISDN_STACK_CLEARING	2
#घोषणा mISDN_STACK_RESTART	3
#घोषणा mISDN_STACK_WAKEUP	4
#घोषणा mISDN_STACK_ABORT	15
/* command bits 16-19 */
#घोषणा mISDN_STACK_STOPPED	16
#घोषणा mISDN_STACK_INIT	17
#घोषणा mISDN_STACK_THREADSTART	18
/* status bits 20-31 */
#घोषणा mISDN_STACK_BCHANNEL	20
#घोषणा mISDN_STACK_ACTIVE      29
#घोषणा mISDN_STACK_RUNNING     30
#घोषणा mISDN_STACK_KILLED      31


/* manager options */
#घोषणा MGR_OPT_USER		24
#घोषणा MGR_OPT_NETWORK		25

बाह्य पूर्णांक	connect_Bstack(काष्ठा mISDNdevice *, काष्ठा mISDNchannel *,
			       u_पूर्णांक, काष्ठा sockaddr_mISDN *);
बाह्य पूर्णांक	connect_layer1(काष्ठा mISDNdevice *, काष्ठा mISDNchannel *,
			       u_पूर्णांक, काष्ठा sockaddr_mISDN *);
बाह्य पूर्णांक	create_l2entity(काष्ठा mISDNdevice *, काष्ठा mISDNchannel *,
				u_पूर्णांक, काष्ठा sockaddr_mISDN *);

बाह्य पूर्णांक	create_stack(काष्ठा mISDNdevice *);
बाह्य पूर्णांक	create_teimanager(काष्ठा mISDNdevice *);
बाह्य व्योम	delete_teimanager(काष्ठा mISDNchannel *);
बाह्य व्योम	delete_channel(काष्ठा mISDNchannel *);
बाह्य व्योम	delete_stack(काष्ठा mISDNdevice *);
बाह्य व्योम	mISDN_initstack(u_पूर्णांक *);
बाह्य पूर्णांक      misdn_sock_init(u_पूर्णांक *);
बाह्य व्योम     misdn_sock_cleanup(व्योम);
बाह्य व्योम	add_layer2(काष्ठा mISDNchannel *, काष्ठा mISDNstack *);
बाह्य व्योम	__add_layer2(काष्ठा mISDNchannel *, काष्ठा mISDNstack *);

बाह्य u_पूर्णांक		get_all_Bprotocols(व्योम);
काष्ठा Bprotocol	*get_Bprotocol4mask(u_पूर्णांक);
काष्ठा Bprotocol	*get_Bprotocol4id(u_पूर्णांक);

बाह्य पूर्णांक	mISDN_initसमयr(u_पूर्णांक *);
बाह्य व्योम	mISDN_समयr_cleanup(व्योम);

बाह्य पूर्णांक	l1_init(u_पूर्णांक *);
बाह्य व्योम	l1_cleanup(व्योम);
बाह्य पूर्णांक	Isdnl2_Init(u_पूर्णांक *);
बाह्य व्योम	Isdnl2_cleanup(व्योम);

बाह्य व्योम	mISDN_init_घड़ी(u_पूर्णांक *);

#पूर्ण_अगर
