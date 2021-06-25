<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Header क्रम Bestcomm General Buffer Descriptor tasks driver
 *
 * Copyright (C) 2007 Sylvain Munaut <tnt@246tNt.com>
 * Copyright (C) 2006 AppSpec Computer Technologies Corp.
 *                    Jeff Gibbons <jeff.gibbons@appspec.com>
 */

#अगर_अघोषित __BESTCOMM_GEN_BD_H__
#घोषणा __BESTCOMM_GEN_BD_H__

काष्ठा bcom_gen_bd अणु
	u32	status;
	u32	buf_pa;
पूर्ण;


बाह्य काष्ठा bcom_task *
bcom_gen_bd_rx_init(पूर्णांक queue_len, phys_addr_t fअगरo,
			पूर्णांक initiator, पूर्णांक ipr, पूर्णांक maxbufsize);

बाह्य पूर्णांक
bcom_gen_bd_rx_reset(काष्ठा bcom_task *tsk);

बाह्य व्योम
bcom_gen_bd_rx_release(काष्ठा bcom_task *tsk);


बाह्य काष्ठा bcom_task *
bcom_gen_bd_tx_init(पूर्णांक queue_len, phys_addr_t fअगरo,
			पूर्णांक initiator, पूर्णांक ipr);

बाह्य पूर्णांक
bcom_gen_bd_tx_reset(काष्ठा bcom_task *tsk);

बाह्य व्योम
bcom_gen_bd_tx_release(काष्ठा bcom_task *tsk);


/* PSC support utility wrappers */
काष्ठा bcom_task * bcom_psc_gen_bd_rx_init(अचिन्हित psc_num, पूर्णांक queue_len,
					   phys_addr_t fअगरo, पूर्णांक maxbufsize);
काष्ठा bcom_task * bcom_psc_gen_bd_tx_init(अचिन्हित psc_num, पूर्णांक queue_len,
					   phys_addr_t fअगरo);
#पूर्ण_अगर  /* __BESTCOMM_GEN_BD_H__ */

