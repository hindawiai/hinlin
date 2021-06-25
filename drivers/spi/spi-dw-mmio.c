<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Memory-mapped पूर्णांकerface driver क्रम DW SPI Core
 *
 * Copyright (c) 2010, Octasic semiconductor.
 */

#समावेश <linux/clk.h>
#समावेश <linux/err.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/slab.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/acpi.h>
#समावेश <linux/property.h>
#समावेश <linux/regmap.h>
#समावेश <linux/reset.h>

#समावेश "spi-dw.h"

#घोषणा DRIVER_NAME "dw_spi_mmio"

काष्ठा dw_spi_mmio अणु
	काष्ठा dw_spi  dws;
	काष्ठा clk     *clk;
	काष्ठा clk     *pclk;
	व्योम           *priv;
	काष्ठा reset_control *rstc;
पूर्ण;

#घोषणा MSCC_CPU_SYSTEM_CTRL_GENERAL_CTRL	0x24
#घोषणा OCELOT_IF_SI_OWNER_OFFSET		4
#घोषणा JAGUAR2_IF_SI_OWNER_OFFSET		6
#घोषणा MSCC_IF_SI_OWNER_MASK			GENMASK(1, 0)
#घोषणा MSCC_IF_SI_OWNER_SISL			0
#घोषणा MSCC_IF_SI_OWNER_SIBM			1
#घोषणा MSCC_IF_SI_OWNER_SIMC			2

#घोषणा MSCC_SPI_MST_SW_MODE			0x14
#घोषणा MSCC_SPI_MST_SW_MODE_SW_PIN_CTRL_MODE	BIT(13)
#घोषणा MSCC_SPI_MST_SW_MODE_SW_SPI_CS(x)	(x << 5)

#घोषणा SPARX5_FORCE_ENA			0xa4
#घोषणा SPARX5_FORCE_VAL			0xa8

काष्ठा dw_spi_mscc अणु
	काष्ठा regmap       *syscon;
	व्योम __iomem        *spi_mst; /* Not sparx5 */
पूर्ण;

/*
 * The Designware SPI controller (referred to as master in the करोcumentation)
 * स्वतःmatically deनिश्चितs chip select when the tx fअगरo is empty. The chip
 * selects then needs to be either driven as GPIOs or, क्रम the first 4 using the
 * the SPI boot controller रेजिस्टरs. the final chip select is an OR gate
 * between the Designware SPI controller and the SPI boot controller.
 */
अटल व्योम dw_spi_mscc_set_cs(काष्ठा spi_device *spi, bool enable)
अणु
	काष्ठा dw_spi *dws = spi_master_get_devdata(spi->master);
	काष्ठा dw_spi_mmio *dwsmmio = container_of(dws, काष्ठा dw_spi_mmio, dws);
	काष्ठा dw_spi_mscc *dwsmscc = dwsmmio->priv;
	u32 cs = spi->chip_select;

	अगर (cs < 4) अणु
		u32 sw_mode = MSCC_SPI_MST_SW_MODE_SW_PIN_CTRL_MODE;

		अगर (!enable)
			sw_mode |= MSCC_SPI_MST_SW_MODE_SW_SPI_CS(BIT(cs));

		ग_लिखोl(sw_mode, dwsmscc->spi_mst + MSCC_SPI_MST_SW_MODE);
	पूर्ण

	dw_spi_set_cs(spi, enable);
पूर्ण

अटल पूर्णांक dw_spi_mscc_init(काष्ठा platक्रमm_device *pdev,
			    काष्ठा dw_spi_mmio *dwsmmio,
			    स्थिर अक्षर *cpu_syscon, u32 अगर_si_owner_offset)
अणु
	काष्ठा dw_spi_mscc *dwsmscc;

	dwsmscc = devm_kzalloc(&pdev->dev, माप(*dwsmscc), GFP_KERNEL);
	अगर (!dwsmscc)
		वापस -ENOMEM;

	dwsmscc->spi_mst = devm_platक्रमm_ioremap_resource(pdev, 1);
	अगर (IS_ERR(dwsmscc->spi_mst)) अणु
		dev_err(&pdev->dev, "SPI_MST region map failed\n");
		वापस PTR_ERR(dwsmscc->spi_mst);
	पूर्ण

	dwsmscc->syscon = syscon_regmap_lookup_by_compatible(cpu_syscon);
	अगर (IS_ERR(dwsmscc->syscon))
		वापस PTR_ERR(dwsmscc->syscon);

	/* Deनिश्चित all CS */
	ग_लिखोl(0, dwsmscc->spi_mst + MSCC_SPI_MST_SW_MODE);

	/* Select the owner of the SI पूर्णांकerface */
	regmap_update_bits(dwsmscc->syscon, MSCC_CPU_SYSTEM_CTRL_GENERAL_CTRL,
			   MSCC_IF_SI_OWNER_MASK << अगर_si_owner_offset,
			   MSCC_IF_SI_OWNER_SIMC << अगर_si_owner_offset);

	dwsmmio->dws.set_cs = dw_spi_mscc_set_cs;
	dwsmmio->priv = dwsmscc;

	वापस 0;
पूर्ण

अटल पूर्णांक dw_spi_mscc_ocelot_init(काष्ठा platक्रमm_device *pdev,
				   काष्ठा dw_spi_mmio *dwsmmio)
अणु
	वापस dw_spi_mscc_init(pdev, dwsmmio, "mscc,ocelot-cpu-syscon",
				OCELOT_IF_SI_OWNER_OFFSET);
पूर्ण

अटल पूर्णांक dw_spi_mscc_jaguar2_init(काष्ठा platक्रमm_device *pdev,
				    काष्ठा dw_spi_mmio *dwsmmio)
अणु
	वापस dw_spi_mscc_init(pdev, dwsmmio, "mscc,jaguar2-cpu-syscon",
				JAGUAR2_IF_SI_OWNER_OFFSET);
पूर्ण

/*
 * The Designware SPI controller (referred to as master in the
 * करोcumentation) स्वतःmatically deनिश्चितs chip select when the tx fअगरo
 * is empty. The chip selects then needs to be driven by a CS override
 * रेजिस्टर. enable is an active low संकेत.
 */
अटल व्योम dw_spi_sparx5_set_cs(काष्ठा spi_device *spi, bool enable)
अणु
	काष्ठा dw_spi *dws = spi_master_get_devdata(spi->master);
	काष्ठा dw_spi_mmio *dwsmmio = container_of(dws, काष्ठा dw_spi_mmio, dws);
	काष्ठा dw_spi_mscc *dwsmscc = dwsmmio->priv;
	u8 cs = spi->chip_select;

	अगर (!enable) अणु
		/* CS override drive enable */
		regmap_ग_लिखो(dwsmscc->syscon, SPARX5_FORCE_ENA, 1);
		/* Now set CSx enabled */
		regmap_ग_लिखो(dwsmscc->syscon, SPARX5_FORCE_VAL, ~BIT(cs));
		/* Allow settle */
		usleep_range(1, 5);
	पूर्ण अन्यथा अणु
		/* CS value */
		regmap_ग_लिखो(dwsmscc->syscon, SPARX5_FORCE_VAL, ~0);
		/* Allow settle */
		usleep_range(1, 5);
		/* CS override drive disable */
		regmap_ग_लिखो(dwsmscc->syscon, SPARX5_FORCE_ENA, 0);
	पूर्ण

	dw_spi_set_cs(spi, enable);
पूर्ण

अटल पूर्णांक dw_spi_mscc_sparx5_init(काष्ठा platक्रमm_device *pdev,
				   काष्ठा dw_spi_mmio *dwsmmio)
अणु
	स्थिर अक्षर *syscon_name = "microchip,sparx5-cpu-syscon";
	काष्ठा device *dev = &pdev->dev;
	काष्ठा dw_spi_mscc *dwsmscc;

	अगर (!IS_ENABLED(CONFIG_SPI_MUX)) अणु
		dev_err(dev, "This driver needs CONFIG_SPI_MUX\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	dwsmscc = devm_kzalloc(dev, माप(*dwsmscc), GFP_KERNEL);
	अगर (!dwsmscc)
		वापस -ENOMEM;

	dwsmscc->syscon =
		syscon_regmap_lookup_by_compatible(syscon_name);
	अगर (IS_ERR(dwsmscc->syscon)) अणु
		dev_err(dev, "No syscon map %s\n", syscon_name);
		वापस PTR_ERR(dwsmscc->syscon);
	पूर्ण

	dwsmmio->dws.set_cs = dw_spi_sparx5_set_cs;
	dwsmmio->priv = dwsmscc;

	वापस 0;
पूर्ण

अटल पूर्णांक dw_spi_alpine_init(काष्ठा platक्रमm_device *pdev,
			      काष्ठा dw_spi_mmio *dwsmmio)
अणु
	dwsmmio->dws.caps = DW_SPI_CAP_CS_OVERRIDE;

	वापस 0;
पूर्ण

अटल पूर्णांक dw_spi_dw_apb_init(काष्ठा platक्रमm_device *pdev,
			      काष्ठा dw_spi_mmio *dwsmmio)
अणु
	dw_spi_dma_setup_generic(&dwsmmio->dws);

	वापस 0;
पूर्ण

अटल पूर्णांक dw_spi_dwc_ssi_init(काष्ठा platक्रमm_device *pdev,
			       काष्ठा dw_spi_mmio *dwsmmio)
अणु
	dwsmmio->dws.caps = DW_SPI_CAP_DWC_SSI;

	dw_spi_dma_setup_generic(&dwsmmio->dws);

	वापस 0;
पूर्ण

अटल पूर्णांक dw_spi_keembay_init(काष्ठा platक्रमm_device *pdev,
			       काष्ठा dw_spi_mmio *dwsmmio)
अणु
	dwsmmio->dws.caps = DW_SPI_CAP_KEEMBAY_MST | DW_SPI_CAP_DWC_SSI;

	वापस 0;
पूर्ण

अटल पूर्णांक dw_spi_canaan_k210_init(काष्ठा platक्रमm_device *pdev,
				   काष्ठा dw_spi_mmio *dwsmmio)
अणु
	/*
	 * The Canaan Kendryte K210 SoC DW apb_ssi v4 spi controller is
	 * करोcumented to have a 32 word deep TX and RX FIFO, which
	 * spi_hw_init() detects. However, when the RX FIFO is filled up to
	 * 32 entries (RXFLR = 32), an RX FIFO overrun error occurs. Aव्योम this
	 * problem by क्रमce setting fअगरo_len to 31.
	 */
	dwsmmio->dws.fअगरo_len = 31;

	वापस 0;
पूर्ण

अटल पूर्णांक dw_spi_mmio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक (*init_func)(काष्ठा platक्रमm_device *pdev,
			 काष्ठा dw_spi_mmio *dwsmmio);
	काष्ठा dw_spi_mmio *dwsmmio;
	काष्ठा resource *mem;
	काष्ठा dw_spi *dws;
	पूर्णांक ret;
	पूर्णांक num_cs;

	dwsmmio = devm_kzalloc(&pdev->dev, माप(काष्ठा dw_spi_mmio),
			GFP_KERNEL);
	अगर (!dwsmmio)
		वापस -ENOMEM;

	dws = &dwsmmio->dws;

	/* Get basic io resource and map it */
	dws->regs = devm_platक्रमm_get_and_ioremap_resource(pdev, 0, &mem);
	अगर (IS_ERR(dws->regs))
		वापस PTR_ERR(dws->regs);

	dws->paddr = mem->start;

	dws->irq = platक्रमm_get_irq(pdev, 0);
	अगर (dws->irq < 0)
		वापस dws->irq; /* -ENXIO */

	dwsmmio->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(dwsmmio->clk))
		वापस PTR_ERR(dwsmmio->clk);
	ret = clk_prepare_enable(dwsmmio->clk);
	अगर (ret)
		वापस ret;

	/* Optional घड़ी needed to access the रेजिस्टरs */
	dwsmmio->pclk = devm_clk_get_optional(&pdev->dev, "pclk");
	अगर (IS_ERR(dwsmmio->pclk)) अणु
		ret = PTR_ERR(dwsmmio->pclk);
		जाओ out_clk;
	पूर्ण
	ret = clk_prepare_enable(dwsmmio->pclk);
	अगर (ret)
		जाओ out_clk;

	/* find an optional reset controller */
	dwsmmio->rstc = devm_reset_control_get_optional_exclusive(&pdev->dev, "spi");
	अगर (IS_ERR(dwsmmio->rstc)) अणु
		ret = PTR_ERR(dwsmmio->rstc);
		जाओ out_clk;
	पूर्ण
	reset_control_deनिश्चित(dwsmmio->rstc);

	dws->bus_num = pdev->id;

	dws->max_freq = clk_get_rate(dwsmmio->clk);

	device_property_पढ़ो_u32(&pdev->dev, "reg-io-width", &dws->reg_io_width);

	num_cs = 4;

	device_property_पढ़ो_u32(&pdev->dev, "num-cs", &num_cs);

	dws->num_cs = num_cs;

	init_func = device_get_match_data(&pdev->dev);
	अगर (init_func) अणु
		ret = init_func(pdev, dwsmmio);
		अगर (ret)
			जाओ out;
	पूर्ण

	pm_runसमय_enable(&pdev->dev);

	ret = dw_spi_add_host(&pdev->dev, dws);
	अगर (ret)
		जाओ out;

	platक्रमm_set_drvdata(pdev, dwsmmio);
	वापस 0;

out:
	pm_runसमय_disable(&pdev->dev);
	clk_disable_unprepare(dwsmmio->pclk);
out_clk:
	clk_disable_unprepare(dwsmmio->clk);
	reset_control_निश्चित(dwsmmio->rstc);

	वापस ret;
पूर्ण

अटल पूर्णांक dw_spi_mmio_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा dw_spi_mmio *dwsmmio = platक्रमm_get_drvdata(pdev);

	dw_spi_हटाओ_host(&dwsmmio->dws);
	pm_runसमय_disable(&pdev->dev);
	clk_disable_unprepare(dwsmmio->pclk);
	clk_disable_unprepare(dwsmmio->clk);
	reset_control_निश्चित(dwsmmio->rstc);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id dw_spi_mmio_of_match[] = अणु
	अणु .compatible = "snps,dw-apb-ssi", .data = dw_spi_dw_apb_initपूर्ण,
	अणु .compatible = "mscc,ocelot-spi", .data = dw_spi_mscc_ocelot_initपूर्ण,
	अणु .compatible = "mscc,jaguar2-spi", .data = dw_spi_mscc_jaguar2_initपूर्ण,
	अणु .compatible = "amazon,alpine-dw-apb-ssi", .data = dw_spi_alpine_initपूर्ण,
	अणु .compatible = "renesas,rzn1-spi", .data = dw_spi_dw_apb_initपूर्ण,
	अणु .compatible = "snps,dwc-ssi-1.01a", .data = dw_spi_dwc_ssi_initपूर्ण,
	अणु .compatible = "intel,keembay-ssi", .data = dw_spi_keembay_initपूर्ण,
	अणु .compatible = "microchip,sparx5-spi", dw_spi_mscc_sparx5_initपूर्ण,
	अणु .compatible = "canaan,k210-spi", dw_spi_canaan_k210_initपूर्ण,
	अणु /* end of table */पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, dw_spi_mmio_of_match);

#अगर_घोषित CONFIG_ACPI
अटल स्थिर काष्ठा acpi_device_id dw_spi_mmio_acpi_match[] = अणु
	अणु"HISI0173", (kernel_uदीर्घ_t)dw_spi_dw_apb_initपूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, dw_spi_mmio_acpi_match);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver dw_spi_mmio_driver = अणु
	.probe		= dw_spi_mmio_probe,
	.हटाओ		= dw_spi_mmio_हटाओ,
	.driver		= अणु
		.name	= DRIVER_NAME,
		.of_match_table = dw_spi_mmio_of_match,
		.acpi_match_table = ACPI_PTR(dw_spi_mmio_acpi_match),
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(dw_spi_mmio_driver);

MODULE_AUTHOR("Jean-Hugues Deschenes <jean-hugues.deschenes@octasic.com>");
MODULE_DESCRIPTION("Memory-mapped I/O interface driver for DW SPI Core");
MODULE_LICENSE("GPL v2");
