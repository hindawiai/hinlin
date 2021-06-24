<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *pxa168 ethernet platक्रमm device data definition file.
 */
#अगर_अघोषित __LINUX_PXA168_ETH_H
#घोषणा __LINUX_PXA168_ETH_H

#समावेश <linux/phy.h>

काष्ठा pxa168_eth_platक्रमm_data अणु
	पूर्णांक	port_number;
	पूर्णांक	phy_addr;

	/*
	 * If speed is 0, then speed and duplex are स्वतःnegotiated.
	 */
	पूर्णांक	speed;		/* 0, SPEED_10, SPEED_100 */
	पूर्णांक	duplex;		/* DUPLEX_HALF or DUPLEX_FULL */
	phy_पूर्णांकerface_t पूर्णांकf;

	/*
	 * Override शेष RX/TX queue sizes अगर nonzero.
	 */
	पूर्णांक	rx_queue_size;
	पूर्णांक	tx_queue_size;

	/*
	 * init callback is used क्रम board specअगरic initialization
	 * e.g on Aspenite its used to initialize the PHY transceiver.
	 */
	पूर्णांक (*init)(व्योम);
पूर्ण;

#पूर्ण_अगर /* __LINUX_PXA168_ETH_H */
