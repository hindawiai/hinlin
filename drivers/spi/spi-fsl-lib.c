<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Freescale SPI/eSPI controller driver library.
 *
 * Maपूर्णांकainer: Kumar Gala
 *
 * Copyright (C) 2006 Polycom, Inc.
 *
 * CPM SPI and QE buffer descriptors mode support:
 * Copyright (c) 2009  MontaVista Software, Inc.
 * Author: Anton Vorontsov <avorontsov@ru.mvista.com>
 *
 * Copyright 2010 Freescale Semiconductor, Inc.
 */
#समावेश <linux/dma-mapping.h>
#समावेश <linux/fsl_devices.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/module.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/spi/spi.h>
#अगर_घोषित CONFIG_FSL_SOC
#समावेश <sysdev/fsl_soc.h>
#पूर्ण_अगर

#समावेश "spi-fsl-lib.h"

#घोषणा MPC8XXX_SPI_RX_BUF(type) 					  \
व्योम mpc8xxx_spi_rx_buf_##type(u32 data, काष्ठा mpc8xxx_spi *mpc8xxx_spi) \
अणु									  \
	type *rx = mpc8xxx_spi->rx;					  \
	*rx++ = (type)(data >> mpc8xxx_spi->rx_shअगरt);			  \
	mpc8xxx_spi->rx = rx;						  \
पूर्ण									  \
EXPORT_SYMBOL_GPL(mpc8xxx_spi_rx_buf_##type);

#घोषणा MPC8XXX_SPI_TX_BUF(type)				\
u32 mpc8xxx_spi_tx_buf_##type(काष्ठा mpc8xxx_spi *mpc8xxx_spi)	\
अणु								\
	u32 data;						\
	स्थिर type *tx = mpc8xxx_spi->tx;			\
	अगर (!tx)						\
		वापस 0;					\
	data = *tx++ << mpc8xxx_spi->tx_shअगरt;			\
	mpc8xxx_spi->tx = tx;					\
	वापस data;						\
पूर्ण								\
EXPORT_SYMBOL_GPL(mpc8xxx_spi_tx_buf_##type);

MPC8XXX_SPI_RX_BUF(u8)
MPC8XXX_SPI_RX_BUF(u16)
MPC8XXX_SPI_RX_BUF(u32)
MPC8XXX_SPI_TX_BUF(u8)
MPC8XXX_SPI_TX_BUF(u16)
MPC8XXX_SPI_TX_BUF(u32)

काष्ठा mpc8xxx_spi_probe_info *to_of_pinfo(काष्ठा fsl_spi_platक्रमm_data *pdata)
अणु
	वापस container_of(pdata, काष्ठा mpc8xxx_spi_probe_info, pdata);
पूर्ण
EXPORT_SYMBOL_GPL(to_of_pinfo);

स्थिर अक्षर *mpc8xxx_spi_strmode(अचिन्हित पूर्णांक flags)
अणु
	अगर (flags & SPI_QE_CPU_MODE) अणु
		वापस "QE CPU";
	पूर्ण अन्यथा अगर (flags & SPI_CPM_MODE) अणु
		अगर (flags & SPI_QE)
			वापस "QE";
		अन्यथा अगर (flags & SPI_CPM2)
			वापस "CPM2";
		अन्यथा
			वापस "CPM1";
	पूर्ण
	वापस "CPU";
पूर्ण
EXPORT_SYMBOL_GPL(mpc8xxx_spi_strmode);

व्योम mpc8xxx_spi_probe(काष्ठा device *dev, काष्ठा resource *mem,
			अचिन्हित पूर्णांक irq)
अणु
	काष्ठा fsl_spi_platक्रमm_data *pdata = dev_get_platdata(dev);
	काष्ठा spi_master *master;
	काष्ठा mpc8xxx_spi *mpc8xxx_spi;

	master = dev_get_drvdata(dev);

	/* the spi->mode bits understood by this driver: */
	master->mode_bits = SPI_CPOL | SPI_CPHA | SPI_CS_HIGH
			| SPI_LSB_FIRST | SPI_LOOP;

	master->dev.of_node = dev->of_node;

	mpc8xxx_spi = spi_master_get_devdata(master);
	mpc8xxx_spi->dev = dev;
	mpc8xxx_spi->get_rx = mpc8xxx_spi_rx_buf_u8;
	mpc8xxx_spi->get_tx = mpc8xxx_spi_tx_buf_u8;
	mpc8xxx_spi->flags = pdata->flags;
	mpc8xxx_spi->spibrg = pdata->sysclk;
	mpc8xxx_spi->irq = irq;

	mpc8xxx_spi->rx_shअगरt = 0;
	mpc8xxx_spi->tx_shअगरt = 0;

	master->bus_num = pdata->bus_num;
	master->num_chipselect = pdata->max_chipselect;

	init_completion(&mpc8xxx_spi->करोne);
पूर्ण
EXPORT_SYMBOL_GPL(mpc8xxx_spi_probe);

पूर्णांक of_mpc8xxx_spi_probe(काष्ठा platक्रमm_device *ofdev)
अणु
	काष्ठा device *dev = &ofdev->dev;
	काष्ठा device_node *np = ofdev->dev.of_node;
	काष्ठा mpc8xxx_spi_probe_info *pinfo;
	काष्ठा fsl_spi_platक्रमm_data *pdata;
	स्थिर व्योम *prop;
	पूर्णांक ret = -ENOMEM;

	pinfo = devm_kzalloc(&ofdev->dev, माप(*pinfo), GFP_KERNEL);
	अगर (!pinfo)
		वापस ret;

	pdata = &pinfo->pdata;
	dev->platक्रमm_data = pdata;

	/* Allocate bus num dynamically. */
	pdata->bus_num = -1;

#अगर_घोषित CONFIG_FSL_SOC
	/* SPI controller is either घड़ीed from QE or SoC घड़ी. */
	pdata->sysclk = get_brgfreq();
	अगर (pdata->sysclk == -1) अणु
		pdata->sysclk = fsl_get_sys_freq();
		अगर (pdata->sysclk == -1)
			वापस -ENODEV;
	पूर्ण
#अन्यथा
	ret = of_property_पढ़ो_u32(np, "clock-frequency", &pdata->sysclk);
	अगर (ret)
		वापस ret;
#पूर्ण_अगर

	prop = of_get_property(np, "mode", शून्य);
	अगर (prop && !म_भेद(prop, "cpu-qe"))
		pdata->flags = SPI_QE_CPU_MODE;
	अन्यथा अगर (prop && !म_भेद(prop, "qe"))
		pdata->flags = SPI_CPM_MODE | SPI_QE;
	अन्यथा अगर (of_device_is_compatible(np, "fsl,cpm2-spi"))
		pdata->flags = SPI_CPM_MODE | SPI_CPM2;
	अन्यथा अगर (of_device_is_compatible(np, "fsl,cpm1-spi"))
		pdata->flags = SPI_CPM_MODE | SPI_CPM1;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(of_mpc8xxx_spi_probe);

MODULE_LICENSE("GPL");
