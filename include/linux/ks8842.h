<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * ks8842.h KS8842 platक्रमm data काष्ठा definition
 * Copyright (c) 2010 Intel Corporation
 */

#अगर_अघोषित _LINUX_KS8842_H
#घोषणा _LINUX_KS8842_H

#समावेश <linux/अगर_ether.h>

/**
 * काष्ठा ks8842_platक्रमm_data - Platक्रमm data of the KS8842 network driver
 * @macaddr:	The MAC address of the device, set to all 0:s to use the on in
 *		the chip.
 * @rx_dma_channel:	The DMA channel to use क्रम RX, -1 क्रम none.
 * @tx_dma_channel:	The DMA channel to use क्रम TX, -1 क्रम none.
 *
 */
काष्ठा ks8842_platक्रमm_data अणु
	u8 macaddr[ETH_ALEN];
	पूर्णांक rx_dma_channel;
	पूर्णांक tx_dma_channel;
पूर्ण;

#पूर्ण_अगर
