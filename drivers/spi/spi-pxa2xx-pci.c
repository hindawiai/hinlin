<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * CE4100's SPI device is more or less the same one as found on PXA
 *
 * Copyright (C) 2016, Intel Corporation
 */
#समावेश <linux/clk-provider.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/spi/pxa2xx_spi.h>

#समावेश <linux/dmaengine.h>
#समावेश <linux/platक्रमm_data/dma-dw.h>

क्रमागत अणु
	PORT_QUARK_X1000,
	PORT_BYT,
	PORT_MRFLD,
	PORT_BSW0,
	PORT_BSW1,
	PORT_BSW2,
	PORT_CE4100,
	PORT_LPT0,
	PORT_LPT1,
पूर्ण;

काष्ठा pxa_spi_info अणु
	क्रमागत pxa_ssp_type type;
	पूर्णांक port_id;
	पूर्णांक num_chipselect;
	अचिन्हित दीर्घ max_clk_rate;

	/* DMA channel request parameters */
	bool (*dma_filter)(काष्ठा dma_chan *chan, व्योम *param);
	व्योम *tx_param;
	व्योम *rx_param;

	पूर्णांक dma_burst_size;

	पूर्णांक (*setup)(काष्ठा pci_dev *pdev, काष्ठा pxa_spi_info *c);
पूर्ण;

अटल काष्ठा dw_dma_slave byt_tx_param = अणु .dst_id = 0 पूर्ण;
अटल काष्ठा dw_dma_slave byt_rx_param = अणु .src_id = 1 पूर्ण;

अटल काष्ठा dw_dma_slave mrfld3_tx_param = अणु .dst_id = 15 पूर्ण;
अटल काष्ठा dw_dma_slave mrfld3_rx_param = अणु .src_id = 14 पूर्ण;
अटल काष्ठा dw_dma_slave mrfld5_tx_param = अणु .dst_id = 13 पूर्ण;
अटल काष्ठा dw_dma_slave mrfld5_rx_param = अणु .src_id = 12 पूर्ण;
अटल काष्ठा dw_dma_slave mrfld6_tx_param = अणु .dst_id = 11 पूर्ण;
अटल काष्ठा dw_dma_slave mrfld6_rx_param = अणु .src_id = 10 पूर्ण;

अटल काष्ठा dw_dma_slave bsw0_tx_param = अणु .dst_id = 0 पूर्ण;
अटल काष्ठा dw_dma_slave bsw0_rx_param = अणु .src_id = 1 पूर्ण;
अटल काष्ठा dw_dma_slave bsw1_tx_param = अणु .dst_id = 6 पूर्ण;
अटल काष्ठा dw_dma_slave bsw1_rx_param = अणु .src_id = 7 पूर्ण;
अटल काष्ठा dw_dma_slave bsw2_tx_param = अणु .dst_id = 8 पूर्ण;
अटल काष्ठा dw_dma_slave bsw2_rx_param = अणु .src_id = 9 पूर्ण;

अटल काष्ठा dw_dma_slave lpt1_tx_param = अणु .dst_id = 0 पूर्ण;
अटल काष्ठा dw_dma_slave lpt1_rx_param = अणु .src_id = 1 पूर्ण;
अटल काष्ठा dw_dma_slave lpt0_tx_param = अणु .dst_id = 2 पूर्ण;
अटल काष्ठा dw_dma_slave lpt0_rx_param = अणु .src_id = 3 पूर्ण;

अटल bool lpss_dma_filter(काष्ठा dma_chan *chan, व्योम *param)
अणु
	काष्ठा dw_dma_slave *dws = param;

	अगर (dws->dma_dev != chan->device->dev)
		वापस false;

	chan->निजी = dws;
	वापस true;
पूर्ण

अटल पूर्णांक lpss_spi_setup(काष्ठा pci_dev *dev, काष्ठा pxa_spi_info *c)
अणु
	काष्ठा pci_dev *dma_dev;

	c->num_chipselect = 1;
	c->max_clk_rate = 50000000;

	dma_dev = pci_get_slot(dev->bus, PCI_DEVFN(PCI_SLOT(dev->devfn), 0));

	अगर (c->tx_param) अणु
		काष्ठा dw_dma_slave *slave = c->tx_param;

		slave->dma_dev = &dma_dev->dev;
		slave->m_master = 0;
		slave->p_master = 1;
	पूर्ण

	अगर (c->rx_param) अणु
		काष्ठा dw_dma_slave *slave = c->rx_param;

		slave->dma_dev = &dma_dev->dev;
		slave->m_master = 0;
		slave->p_master = 1;
	पूर्ण

	c->dma_filter = lpss_dma_filter;
	वापस 0;
पूर्ण

अटल पूर्णांक mrfld_spi_setup(काष्ठा pci_dev *dev, काष्ठा pxa_spi_info *c)
अणु
	काष्ठा pci_dev *dma_dev = pci_get_slot(dev->bus, PCI_DEVFN(21, 0));
	काष्ठा dw_dma_slave *tx, *rx;

	चयन (PCI_FUNC(dev->devfn)) अणु
	हाल 0:
		c->port_id = 3;
		c->num_chipselect = 1;
		c->tx_param = &mrfld3_tx_param;
		c->rx_param = &mrfld3_rx_param;
		अवरोध;
	हाल 1:
		c->port_id = 5;
		c->num_chipselect = 4;
		c->tx_param = &mrfld5_tx_param;
		c->rx_param = &mrfld5_rx_param;
		अवरोध;
	हाल 2:
		c->port_id = 6;
		c->num_chipselect = 1;
		c->tx_param = &mrfld6_tx_param;
		c->rx_param = &mrfld6_rx_param;
		अवरोध;
	शेष:
		वापस -ENODEV;
	पूर्ण

	tx = c->tx_param;
	tx->dma_dev = &dma_dev->dev;

	rx = c->rx_param;
	rx->dma_dev = &dma_dev->dev;

	c->dma_filter = lpss_dma_filter;
	c->dma_burst_size = 8;
	वापस 0;
पूर्ण

अटल काष्ठा pxa_spi_info spi_info_configs[] = अणु
	[PORT_CE4100] = अणु
		.type = PXA25x_SSP,
		.port_id =  -1,
		.num_chipselect = -1,
		.max_clk_rate = 3686400,
	पूर्ण,
	[PORT_BYT] = अणु
		.type = LPSS_BYT_SSP,
		.port_id = 0,
		.setup = lpss_spi_setup,
		.tx_param = &byt_tx_param,
		.rx_param = &byt_rx_param,
	पूर्ण,
	[PORT_BSW0] = अणु
		.type = LPSS_BSW_SSP,
		.port_id = 0,
		.setup = lpss_spi_setup,
		.tx_param = &bsw0_tx_param,
		.rx_param = &bsw0_rx_param,
	पूर्ण,
	[PORT_BSW1] = अणु
		.type = LPSS_BSW_SSP,
		.port_id = 1,
		.setup = lpss_spi_setup,
		.tx_param = &bsw1_tx_param,
		.rx_param = &bsw1_rx_param,
	पूर्ण,
	[PORT_BSW2] = अणु
		.type = LPSS_BSW_SSP,
		.port_id = 2,
		.setup = lpss_spi_setup,
		.tx_param = &bsw2_tx_param,
		.rx_param = &bsw2_rx_param,
	पूर्ण,
	[PORT_MRFLD] = अणु
		.type = PXA27x_SSP,
		.max_clk_rate = 25000000,
		.setup = mrfld_spi_setup,
	पूर्ण,
	[PORT_QUARK_X1000] = अणु
		.type = QUARK_X1000_SSP,
		.port_id = -1,
		.num_chipselect = 1,
		.max_clk_rate = 50000000,
	पूर्ण,
	[PORT_LPT0] = अणु
		.type = LPSS_LPT_SSP,
		.port_id = 0,
		.setup = lpss_spi_setup,
		.tx_param = &lpt0_tx_param,
		.rx_param = &lpt0_rx_param,
	पूर्ण,
	[PORT_LPT1] = अणु
		.type = LPSS_LPT_SSP,
		.port_id = 1,
		.setup = lpss_spi_setup,
		.tx_param = &lpt1_tx_param,
		.rx_param = &lpt1_rx_param,
	पूर्ण,
पूर्ण;

अटल पूर्णांक pxa2xx_spi_pci_probe(काष्ठा pci_dev *dev,
		स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा platक्रमm_device_info pi;
	पूर्णांक ret;
	काष्ठा platक्रमm_device *pdev;
	काष्ठा pxa2xx_spi_controller spi_pdata;
	काष्ठा ssp_device *ssp;
	काष्ठा pxa_spi_info *c;
	अक्षर buf[40];

	ret = pcim_enable_device(dev);
	अगर (ret)
		वापस ret;

	ret = pcim_iomap_regions(dev, 1 << 0, "PXA2xx SPI");
	अगर (ret)
		वापस ret;

	c = &spi_info_configs[ent->driver_data];
	अगर (c->setup) अणु
		ret = c->setup(dev, c);
		अगर (ret)
			वापस ret;
	पूर्ण

	स_रखो(&spi_pdata, 0, माप(spi_pdata));
	spi_pdata.num_chipselect = (c->num_chipselect > 0) ? c->num_chipselect : dev->devfn;
	spi_pdata.dma_filter = c->dma_filter;
	spi_pdata.tx_param = c->tx_param;
	spi_pdata.rx_param = c->rx_param;
	spi_pdata.enable_dma = c->rx_param && c->tx_param;
	spi_pdata.dma_burst_size = c->dma_burst_size ? c->dma_burst_size : 1;

	ssp = &spi_pdata.ssp;
	ssp->phys_base = pci_resource_start(dev, 0);
	ssp->mmio_base = pcim_iomap_table(dev)[0];
	ssp->port_id = (c->port_id >= 0) ? c->port_id : dev->devfn;
	ssp->type = c->type;

	pci_set_master(dev);

	ret = pci_alloc_irq_vectors(dev, 1, 1, PCI_IRQ_ALL_TYPES);
	अगर (ret < 0)
		वापस ret;
	ssp->irq = pci_irq_vector(dev, 0);

	snम_लिखो(buf, माप(buf), "pxa2xx-spi.%d", ssp->port_id);
	ssp->clk = clk_रेजिस्टर_fixed_rate(&dev->dev, buf, शून्य, 0,
					   c->max_clk_rate);
	 अगर (IS_ERR(ssp->clk))
		वापस PTR_ERR(ssp->clk);

	स_रखो(&pi, 0, माप(pi));
	pi.fwnode = dev->dev.fwnode;
	pi.parent = &dev->dev;
	pi.name = "pxa2xx-spi";
	pi.id = ssp->port_id;
	pi.data = &spi_pdata;
	pi.size_data = माप(spi_pdata);

	pdev = platक्रमm_device_रेजिस्टर_full(&pi);
	अगर (IS_ERR(pdev)) अणु
		clk_unरेजिस्टर(ssp->clk);
		वापस PTR_ERR(pdev);
	पूर्ण

	pci_set_drvdata(dev, pdev);

	वापस 0;
पूर्ण

अटल व्योम pxa2xx_spi_pci_हटाओ(काष्ठा pci_dev *dev)
अणु
	काष्ठा platक्रमm_device *pdev = pci_get_drvdata(dev);
	काष्ठा pxa2xx_spi_controller *spi_pdata;

	spi_pdata = dev_get_platdata(&pdev->dev);

	platक्रमm_device_unरेजिस्टर(pdev);
	clk_unरेजिस्टर(spi_pdata->ssp.clk);
पूर्ण

अटल स्थिर काष्ठा pci_device_id pxa2xx_spi_pci_devices[] = अणु
	अणु PCI_VDEVICE(INTEL, 0x0935), PORT_QUARK_X1000 पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x0f0e), PORT_BYT पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x1194), PORT_MRFLD पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x228e), PORT_BSW0 पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x2290), PORT_BSW1 पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x22ac), PORT_BSW2 पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x2e6a), PORT_CE4100 पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x9c65), PORT_LPT0 पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x9c66), PORT_LPT1 पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x9ce5), PORT_LPT0 पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x9ce6), PORT_LPT1 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, pxa2xx_spi_pci_devices);

अटल काष्ठा pci_driver pxa2xx_spi_pci_driver = अणु
	.name           = "pxa2xx_spi_pci",
	.id_table       = pxa2xx_spi_pci_devices,
	.probe          = pxa2xx_spi_pci_probe,
	.हटाओ         = pxa2xx_spi_pci_हटाओ,
पूर्ण;

module_pci_driver(pxa2xx_spi_pci_driver);

MODULE_DESCRIPTION("CE4100/LPSS PCI-SPI glue code for PXA's driver");
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Sebastian Andrzej Siewior <bigeasy@linutronix.de>");
