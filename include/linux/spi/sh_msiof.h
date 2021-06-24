<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __SPI_SH_MSIOF_H__
#घोषणा __SPI_SH_MSIOF_H__

क्रमागत अणु
	MSIOF_SPI_MASTER,
	MSIOF_SPI_SLAVE,
पूर्ण;

काष्ठा sh_msiof_spi_info अणु
	पूर्णांक tx_fअगरo_override;
	पूर्णांक rx_fअगरo_override;
	u16 num_chipselect;
	पूर्णांक mode;
	अचिन्हित पूर्णांक dma_tx_id;
	अचिन्हित पूर्णांक dma_rx_id;
	u32 dtdl;
	u32 syncdl;
पूर्ण;

#पूर्ण_अगर /* __SPI_SH_MSIOF_H__ */
