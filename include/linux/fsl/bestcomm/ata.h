<शैली गुरु>
/*
 * Header क्रम Bestcomm ATA task driver
 *
 *
 * Copyright (C) 2006 Freescale - John Rigby
 * Copyright (C) 2006 Sylvain Munaut <tnt@246tNt.com>
 *
 * This file is licensed under the terms of the GNU General Public License
 * version 2. This program is licensed "as is" without any warranty of any
 * kind, whether express or implied.
 */

#अगर_अघोषित __BESTCOMM_ATA_H__
#घोषणा __BESTCOMM_ATA_H__


काष्ठा bcom_ata_bd अणु
	u32	status;
	u32	src_pa;
	u32	dst_pa;
पूर्ण;

बाह्य काष्ठा bcom_task * bcom_ata_init(पूर्णांक queue_len, पूर्णांक maxbufsize);
बाह्य व्योम bcom_ata_rx_prepare(काष्ठा bcom_task *tsk);
बाह्य व्योम bcom_ata_tx_prepare(काष्ठा bcom_task *tsk);
बाह्य व्योम bcom_ata_reset_bd(काष्ठा bcom_task *tsk);
बाह्य व्योम bcom_ata_release(काष्ठा bcom_task *tsk);

#पूर्ण_अगर /* __BESTCOMM_ATA_H__ */

