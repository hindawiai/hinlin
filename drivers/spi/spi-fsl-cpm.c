<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Freescale SPI controller driver cpm functions.
 *
 * Maपूर्णांकainer: Kumar Gala
 *
 * Copyright (C) 2006 Polycom, Inc.
 * Copyright 2010 Freescale Semiconductor, Inc.
 *
 * CPM SPI and QE buffer descriptors mode support:
 * Copyright (c) 2009  MontaVista Software, Inc.
 * Author: Anton Vorontsov <avorontsov@ru.mvista.com>
 */
#समावेश <यंत्र/cpm.h>
#समावेश <soc/fsl/qe/qe.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/fsl_devices.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of_address.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/types.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश "spi-fsl-cpm.h"
#समावेश "spi-fsl-lib.h"
#समावेश "spi-fsl-spi.h"

/* CPM1 and CPM2 are mutually exclusive. */
#अगर_घोषित CONFIG_CPM1
#समावेश <यंत्र/cpm1.h>
#घोषणा CPM_SPI_CMD mk_cr_cmd(CPM_CR_CH_SPI, 0)
#अन्यथा
#समावेश <यंत्र/cpm2.h>
#घोषणा CPM_SPI_CMD mk_cr_cmd(CPM_CR_SPI_PAGE, CPM_CR_SPI_SBLOCK, 0, 0)
#पूर्ण_अगर

#घोषणा	SPIE_TXB	0x00000200	/* Last अक्षर is written to tx fअगरo */
#घोषणा	SPIE_RXB	0x00000100	/* Last अक्षर is written to rx buf */

/* SPCOM रेजिस्टर values */
#घोषणा	SPCOM_STR	(1 << 23)	/* Start transmit */

#घोषणा	SPI_PRAM_SIZE	0x100
#घोषणा	SPI_MRBLR	((अचिन्हित पूर्णांक)PAGE_SIZE)

अटल व्योम *fsl_dummy_rx;
अटल DEFINE_MUTEX(fsl_dummy_rx_lock);
अटल पूर्णांक fsl_dummy_rx_refcnt;

व्योम fsl_spi_cpm_reinit_txrx(काष्ठा mpc8xxx_spi *mspi)
अणु
	अगर (mspi->flags & SPI_QE) अणु
		qe_issue_cmd(QE_INIT_TX_RX, mspi->subblock,
			     QE_CR_PROTOCOL_UNSPECIFIED, 0);
	पूर्ण अन्यथा अणु
		अगर (mspi->flags & SPI_CPM1) अणु
			out_be32(&mspi->pram->rstate, 0);
			out_be16(&mspi->pram->rbptr,
				 in_be16(&mspi->pram->rbase));
			out_be32(&mspi->pram->tstate, 0);
			out_be16(&mspi->pram->tbptr,
				 in_be16(&mspi->pram->tbase));
		पूर्ण अन्यथा अणु
			cpm_command(CPM_SPI_CMD, CPM_CR_INIT_TRX);
		पूर्ण
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(fsl_spi_cpm_reinit_txrx);

अटल व्योम fsl_spi_cpm_bufs_start(काष्ठा mpc8xxx_spi *mspi)
अणु
	काष्ठा cpm_buf_desc __iomem *tx_bd = mspi->tx_bd;
	काष्ठा cpm_buf_desc __iomem *rx_bd = mspi->rx_bd;
	अचिन्हित पूर्णांक xfer_len = min(mspi->count, SPI_MRBLR);
	अचिन्हित पूर्णांक xfer_ofs;
	काष्ठा fsl_spi_reg *reg_base = mspi->reg_base;

	xfer_ofs = mspi->xfer_in_progress->len - mspi->count;

	अगर (mspi->rx_dma == mspi->dma_dummy_rx)
		out_be32(&rx_bd->cbd_bufaddr, mspi->rx_dma);
	अन्यथा
		out_be32(&rx_bd->cbd_bufaddr, mspi->rx_dma + xfer_ofs);
	out_be16(&rx_bd->cbd_datlen, 0);
	out_be16(&rx_bd->cbd_sc, BD_SC_EMPTY | BD_SC_INTRPT | BD_SC_WRAP);

	अगर (mspi->tx_dma == mspi->dma_dummy_tx)
		out_be32(&tx_bd->cbd_bufaddr, mspi->tx_dma);
	अन्यथा
		out_be32(&tx_bd->cbd_bufaddr, mspi->tx_dma + xfer_ofs);
	out_be16(&tx_bd->cbd_datlen, xfer_len);
	out_be16(&tx_bd->cbd_sc, BD_SC_READY | BD_SC_INTRPT | BD_SC_WRAP |
				 BD_SC_LAST);

	/* start transfer */
	mpc8xxx_spi_ग_लिखो_reg(&reg_base->command, SPCOM_STR);
पूर्ण

पूर्णांक fsl_spi_cpm_bufs(काष्ठा mpc8xxx_spi *mspi,
		     काष्ठा spi_transfer *t, bool is_dma_mapped)
अणु
	काष्ठा device *dev = mspi->dev;
	काष्ठा fsl_spi_reg *reg_base = mspi->reg_base;

	अगर (is_dma_mapped) अणु
		mspi->map_tx_dma = 0;
		mspi->map_rx_dma = 0;
	पूर्ण अन्यथा अणु
		mspi->map_tx_dma = 1;
		mspi->map_rx_dma = 1;
	पूर्ण

	अगर (!t->tx_buf) अणु
		mspi->tx_dma = mspi->dma_dummy_tx;
		mspi->map_tx_dma = 0;
	पूर्ण

	अगर (!t->rx_buf) अणु
		mspi->rx_dma = mspi->dma_dummy_rx;
		mspi->map_rx_dma = 0;
	पूर्ण

	अगर (mspi->map_tx_dma) अणु
		व्योम *nonस्थिर_tx = (व्योम *)mspi->tx; /* shut up gcc */

		mspi->tx_dma = dma_map_single(dev, nonस्थिर_tx, t->len,
					      DMA_TO_DEVICE);
		अगर (dma_mapping_error(dev, mspi->tx_dma)) अणु
			dev_err(dev, "unable to map tx dma\n");
			वापस -ENOMEM;
		पूर्ण
	पूर्ण अन्यथा अगर (t->tx_buf) अणु
		mspi->tx_dma = t->tx_dma;
	पूर्ण

	अगर (mspi->map_rx_dma) अणु
		mspi->rx_dma = dma_map_single(dev, mspi->rx, t->len,
					      DMA_FROM_DEVICE);
		अगर (dma_mapping_error(dev, mspi->rx_dma)) अणु
			dev_err(dev, "unable to map rx dma\n");
			जाओ err_rx_dma;
		पूर्ण
	पूर्ण अन्यथा अगर (t->rx_buf) अणु
		mspi->rx_dma = t->rx_dma;
	पूर्ण

	/* enable rx पूर्णांकs */
	mpc8xxx_spi_ग_लिखो_reg(&reg_base->mask, SPIE_RXB);

	mspi->xfer_in_progress = t;
	mspi->count = t->len;

	/* start CPM transfers */
	fsl_spi_cpm_bufs_start(mspi);

	वापस 0;

err_rx_dma:
	अगर (mspi->map_tx_dma)
		dma_unmap_single(dev, mspi->tx_dma, t->len, DMA_TO_DEVICE);
	वापस -ENOMEM;
पूर्ण
EXPORT_SYMBOL_GPL(fsl_spi_cpm_bufs);

व्योम fsl_spi_cpm_bufs_complete(काष्ठा mpc8xxx_spi *mspi)
अणु
	काष्ठा device *dev = mspi->dev;
	काष्ठा spi_transfer *t = mspi->xfer_in_progress;

	अगर (mspi->map_tx_dma)
		dma_unmap_single(dev, mspi->tx_dma, t->len, DMA_TO_DEVICE);
	अगर (mspi->map_rx_dma)
		dma_unmap_single(dev, mspi->rx_dma, t->len, DMA_FROM_DEVICE);
	mspi->xfer_in_progress = शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(fsl_spi_cpm_bufs_complete);

व्योम fsl_spi_cpm_irq(काष्ठा mpc8xxx_spi *mspi, u32 events)
अणु
	u16 len;
	काष्ठा fsl_spi_reg *reg_base = mspi->reg_base;

	dev_dbg(mspi->dev, "%s: bd datlen %d, count %d\n", __func__,
		in_be16(&mspi->rx_bd->cbd_datlen), mspi->count);

	len = in_be16(&mspi->rx_bd->cbd_datlen);
	अगर (len > mspi->count) अणु
		WARN_ON(1);
		len = mspi->count;
	पूर्ण

	/* Clear the events */
	mpc8xxx_spi_ग_लिखो_reg(&reg_base->event, events);

	mspi->count -= len;
	अगर (mspi->count)
		fsl_spi_cpm_bufs_start(mspi);
	अन्यथा
		complete(&mspi->करोne);
पूर्ण
EXPORT_SYMBOL_GPL(fsl_spi_cpm_irq);

अटल व्योम *fsl_spi_alloc_dummy_rx(व्योम)
अणु
	mutex_lock(&fsl_dummy_rx_lock);

	अगर (!fsl_dummy_rx)
		fsl_dummy_rx = kदो_स्मृति(SPI_MRBLR, GFP_KERNEL);
	अगर (fsl_dummy_rx)
		fsl_dummy_rx_refcnt++;

	mutex_unlock(&fsl_dummy_rx_lock);

	वापस fsl_dummy_rx;
पूर्ण

अटल व्योम fsl_spi_मुक्त_dummy_rx(व्योम)
अणु
	mutex_lock(&fsl_dummy_rx_lock);

	चयन (fsl_dummy_rx_refcnt) अणु
	हाल 0:
		WARN_ON(1);
		अवरोध;
	हाल 1:
		kमुक्त(fsl_dummy_rx);
		fsl_dummy_rx = शून्य;
		fallthrough;
	शेष:
		fsl_dummy_rx_refcnt--;
		अवरोध;
	पूर्ण

	mutex_unlock(&fsl_dummy_rx_lock);
पूर्ण

अटल अचिन्हित दीर्घ fsl_spi_cpm_get_pram(काष्ठा mpc8xxx_spi *mspi)
अणु
	काष्ठा device *dev = mspi->dev;
	काष्ठा device_node *np = dev->of_node;
	स्थिर u32 *iprop;
	पूर्णांक size;
	व्योम __iomem *spi_base;
	अचिन्हित दीर्घ pram_ofs = -ENOMEM;

	/* Can't use of_address_to_resource(), QE muram isn't at 0. */
	iprop = of_get_property(np, "reg", &size);

	/* QE with a fixed pram location? */
	अगर (mspi->flags & SPI_QE && iprop && size == माप(*iprop) * 4)
		वापस cpm_muram_alloc_fixed(iprop[2], SPI_PRAM_SIZE);

	/* QE but with a dynamic pram location? */
	अगर (mspi->flags & SPI_QE) अणु
		pram_ofs = cpm_muram_alloc(SPI_PRAM_SIZE, 64);
		qe_issue_cmd(QE_ASSIGN_PAGE_TO_DEVICE, mspi->subblock,
			     QE_CR_PROTOCOL_UNSPECIFIED, pram_ofs);
		वापस pram_ofs;
	पूर्ण

	spi_base = of_iomap(np, 1);
	अगर (spi_base == शून्य)
		वापस -EINVAL;

	अगर (mspi->flags & SPI_CPM2) अणु
		pram_ofs = cpm_muram_alloc(SPI_PRAM_SIZE, 64);
		out_be16(spi_base, pram_ofs);
	पूर्ण

	iounmap(spi_base);
	वापस pram_ofs;
पूर्ण

पूर्णांक fsl_spi_cpm_init(काष्ठा mpc8xxx_spi *mspi)
अणु
	काष्ठा device *dev = mspi->dev;
	काष्ठा device_node *np = dev->of_node;
	स्थिर u32 *iprop;
	पूर्णांक size;
	अचिन्हित दीर्घ bds_ofs;

	अगर (!(mspi->flags & SPI_CPM_MODE))
		वापस 0;

	अगर (!fsl_spi_alloc_dummy_rx())
		वापस -ENOMEM;

	अगर (mspi->flags & SPI_QE) अणु
		iprop = of_get_property(np, "cell-index", &size);
		अगर (iprop && size == माप(*iprop))
			mspi->subblock = *iprop;

		चयन (mspi->subblock) अणु
		शेष:
			dev_warn(dev, "cell-index unspecified, assuming SPI1\n");
			fallthrough;
		हाल 0:
			mspi->subblock = QE_CR_SUBBLOCK_SPI1;
			अवरोध;
		हाल 1:
			mspi->subblock = QE_CR_SUBBLOCK_SPI2;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (mspi->flags & SPI_CPM1) अणु
		व्योम *pram;

		pram = devm_platक्रमm_ioremap_resource(to_platक्रमm_device(dev),
						      1);
		अगर (IS_ERR(pram))
			mspi->pram = शून्य;
		अन्यथा
			mspi->pram = pram;
	पूर्ण अन्यथा अणु
		अचिन्हित दीर्घ pram_ofs = fsl_spi_cpm_get_pram(mspi);

		अगर (IS_ERR_VALUE(pram_ofs))
			mspi->pram = शून्य;
		अन्यथा
			mspi->pram = cpm_muram_addr(pram_ofs);
	पूर्ण
	अगर (mspi->pram == शून्य) अणु
		dev_err(dev, "can't allocate spi parameter ram\n");
		जाओ err_pram;
	पूर्ण

	bds_ofs = cpm_muram_alloc(माप(*mspi->tx_bd) +
				  माप(*mspi->rx_bd), 8);
	अगर (IS_ERR_VALUE(bds_ofs)) अणु
		dev_err(dev, "can't allocate bds\n");
		जाओ err_bds;
	पूर्ण

	mspi->dma_dummy_tx = dma_map_single(dev, empty_zero_page, PAGE_SIZE,
					    DMA_TO_DEVICE);
	अगर (dma_mapping_error(dev, mspi->dma_dummy_tx)) अणु
		dev_err(dev, "unable to map dummy tx buffer\n");
		जाओ err_dummy_tx;
	पूर्ण

	mspi->dma_dummy_rx = dma_map_single(dev, fsl_dummy_rx, SPI_MRBLR,
					    DMA_FROM_DEVICE);
	अगर (dma_mapping_error(dev, mspi->dma_dummy_rx)) अणु
		dev_err(dev, "unable to map dummy rx buffer\n");
		जाओ err_dummy_rx;
	पूर्ण

	mspi->tx_bd = cpm_muram_addr(bds_ofs);
	mspi->rx_bd = cpm_muram_addr(bds_ofs + माप(*mspi->tx_bd));

	/* Initialize parameter ram. */
	out_be16(&mspi->pram->tbase, cpm_muram_offset(mspi->tx_bd));
	out_be16(&mspi->pram->rbase, cpm_muram_offset(mspi->rx_bd));
	out_8(&mspi->pram->tfcr, CPMFCR_EB | CPMFCR_GBL);
	out_8(&mspi->pram->rfcr, CPMFCR_EB | CPMFCR_GBL);
	out_be16(&mspi->pram->mrblr, SPI_MRBLR);
	out_be32(&mspi->pram->rstate, 0);
	out_be32(&mspi->pram->rdp, 0);
	out_be16(&mspi->pram->rbptr, 0);
	out_be16(&mspi->pram->rbc, 0);
	out_be32(&mspi->pram->rxपंचांगp, 0);
	out_be32(&mspi->pram->tstate, 0);
	out_be32(&mspi->pram->tdp, 0);
	out_be16(&mspi->pram->tbptr, 0);
	out_be16(&mspi->pram->tbc, 0);
	out_be32(&mspi->pram->txपंचांगp, 0);

	वापस 0;

err_dummy_rx:
	dma_unmap_single(dev, mspi->dma_dummy_tx, PAGE_SIZE, DMA_TO_DEVICE);
err_dummy_tx:
	cpm_muram_मुक्त(bds_ofs);
err_bds:
	अगर (!(mspi->flags & SPI_CPM1))
		cpm_muram_मुक्त(cpm_muram_offset(mspi->pram));
err_pram:
	fsl_spi_मुक्त_dummy_rx();
	वापस -ENOMEM;
पूर्ण
EXPORT_SYMBOL_GPL(fsl_spi_cpm_init);

व्योम fsl_spi_cpm_मुक्त(काष्ठा mpc8xxx_spi *mspi)
अणु
	काष्ठा device *dev = mspi->dev;

	अगर (!(mspi->flags & SPI_CPM_MODE))
		वापस;

	dma_unmap_single(dev, mspi->dma_dummy_rx, SPI_MRBLR, DMA_FROM_DEVICE);
	dma_unmap_single(dev, mspi->dma_dummy_tx, PAGE_SIZE, DMA_TO_DEVICE);
	cpm_muram_मुक्त(cpm_muram_offset(mspi->tx_bd));
	अगर (!(mspi->flags & SPI_CPM1))
		cpm_muram_मुक्त(cpm_muram_offset(mspi->pram));
	fsl_spi_मुक्त_dummy_rx();
पूर्ण
EXPORT_SYMBOL_GPL(fsl_spi_cpm_मुक्त);

MODULE_LICENSE("GPL");
