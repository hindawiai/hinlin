<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * TXx9 SoC DMA Controller
 */

#अगर_अघोषित __ASM_TXX9_DMAC_H
#घोषणा __ASM_TXX9_DMAC_H

#समावेश <linux/dmaengine.h>

#घोषणा TXX9_DMA_MAX_NR_CHANNELS	4

/**
 * काष्ठा txx9dmac_platक्रमm_data - Controller configuration parameters
 * @स_नकल_chan: Channel used क्रम DMA_MEMCPY
 * @have_64bit_regs: DMAC have 64 bit रेजिस्टरs
 */
काष्ठा txx9dmac_platक्रमm_data अणु
	पूर्णांक	स_नकल_chan;
	bool	have_64bit_regs;
पूर्ण;

/**
 * काष्ठा txx9dmac_chan_platक्रमm_data - Channel configuration parameters
 * @dmac_dev: A platक्रमm device क्रम DMAC
 */
काष्ठा txx9dmac_chan_platक्रमm_data अणु
	काष्ठा platक्रमm_device *dmac_dev;
पूर्ण;

/**
 * काष्ठा txx9dmac_slave - Controller-specअगरic inक्रमmation about a slave
 * @tx_reg: physical address of data रेजिस्टर used क्रम
 *	memory-to-peripheral transfers
 * @rx_reg: physical address of data रेजिस्टर used क्रम
 *	peripheral-to-memory transfers
 * @reg_width: peripheral रेजिस्टर width
 */
काष्ठा txx9dmac_slave अणु
	u64		tx_reg;
	u64		rx_reg;
	अचिन्हित पूर्णांक	reg_width;
पूर्ण;

व्योम txx9_dmac_init(पूर्णांक id, अचिन्हित दीर्घ baseaddr, पूर्णांक irq,
		    स्थिर काष्ठा txx9dmac_platक्रमm_data *pdata);

#पूर्ण_अगर /* __ASM_TXX9_DMAC_H */
