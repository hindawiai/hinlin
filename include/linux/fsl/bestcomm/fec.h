<शैली गुरु>
/*
 * Header क्रम Bestcomm FEC tasks driver
 *
 *
 * Copyright (C) 2006-2007 Sylvain Munaut <tnt@246tNt.com>
 * Copyright (C) 2003-2004 MontaVista, Software, Inc.
 *                         ( by Dale Farnsworth <dfarnsworth@mvista.com> )
 *
 * This file is licensed under the terms of the GNU General Public License
 * version 2. This program is licensed "as is" without any warranty of any
 * kind, whether express or implied.
 */

#अगर_अघोषित __BESTCOMM_FEC_H__
#घोषणा __BESTCOMM_FEC_H__


काष्ठा bcom_fec_bd अणु
	u32	status;
	u32	skb_pa;
पूर्ण;

#घोषणा BCOM_FEC_TX_BD_TFD	0x08000000ul	/* transmit frame करोne */
#घोषणा BCOM_FEC_TX_BD_TC	0x04000000ul	/* transmit CRC */
#घोषणा BCOM_FEC_TX_BD_ABC	0x02000000ul	/* append bad CRC */

#घोषणा BCOM_FEC_RX_BD_L	0x08000000ul	/* buffer is last in frame */
#घोषणा BCOM_FEC_RX_BD_BC	0x00800000ul	/* DA is broadcast */
#घोषणा BCOM_FEC_RX_BD_MC	0x00400000ul	/* DA is multicast and not broadcast */
#घोषणा BCOM_FEC_RX_BD_LG	0x00200000ul	/* Rx frame length violation */
#घोषणा BCOM_FEC_RX_BD_NO	0x00100000ul	/* Rx non-octet aligned frame */
#घोषणा BCOM_FEC_RX_BD_CR	0x00040000ul	/* Rx CRC error */
#घोषणा BCOM_FEC_RX_BD_OV	0x00020000ul	/* overrun */
#घोषणा BCOM_FEC_RX_BD_TR	0x00010000ul	/* Rx frame truncated */
#घोषणा BCOM_FEC_RX_BD_LEN_MASK	0x000007fful	/* mask क्रम length of received frame */
#घोषणा BCOM_FEC_RX_BD_ERRORS	(BCOM_FEC_RX_BD_LG | BCOM_FEC_RX_BD_NO | \
		BCOM_FEC_RX_BD_CR | BCOM_FEC_RX_BD_OV | BCOM_FEC_RX_BD_TR)


बाह्य काष्ठा bcom_task *
bcom_fec_rx_init(पूर्णांक queue_len, phys_addr_t fअगरo, पूर्णांक maxbufsize);

बाह्य पूर्णांक
bcom_fec_rx_reset(काष्ठा bcom_task *tsk);

बाह्य व्योम
bcom_fec_rx_release(काष्ठा bcom_task *tsk);


बाह्य काष्ठा bcom_task *
bcom_fec_tx_init(पूर्णांक queue_len, phys_addr_t fअगरo);

बाह्य पूर्णांक
bcom_fec_tx_reset(काष्ठा bcom_task *tsk);

बाह्य व्योम
bcom_fec_tx_release(काष्ठा bcom_task *tsk);


#पूर्ण_अगर /* __BESTCOMM_FEC_H__ */

