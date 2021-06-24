<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) ST-Ericsson SA 2011
 *
 * Author: Mian Yousaf Kaukab <mian.yousaf.kaukab@stericsson.com>
 */
#अगर_अघोषित __ASM_ARCH_USB_H
#घोषणा __ASM_ARCH_USB_H

#समावेश <linux/dmaengine.h>

#घोषणा UX500_MUSB_DMA_NUM_RX_TX_CHANNELS 8

काष्ठा ux500_musb_board_data अणु
	व्योम	**dma_rx_param_array;
	व्योम	**dma_tx_param_array;
	bool (*dma_filter)(काष्ठा dma_chan *chan, व्योम *filter_param);
पूर्ण;

व्योम ux500_add_usb(काष्ठा device *parent, resource_माप_प्रकार base,
		   पूर्णांक irq, पूर्णांक *dma_rx_cfg, पूर्णांक *dma_tx_cfg);
#पूर्ण_अगर
