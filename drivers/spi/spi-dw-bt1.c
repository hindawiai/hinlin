<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
//
// Copyright (C) 2020 BAIKAL ELECTRONICS, JSC
//
// Authors:
//   Ramil Zaripov <Ramil.Zaripov@baikalelectronics.ru>
//   Serge Semin <Sergey.Semin@baikalelectronics.ru>
//
// Baikal-T1 DW APB SPI and System Boot SPI driver
//

#समावेश <linux/clk.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/err.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/mux/consumer.h>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/property.h>
#समावेश <linux/slab.h>
#समावेश <linux/spi/spi-स्मृति.स>
#समावेश <linux/spi/spi.h>

#समावेश "spi-dw.h"

#घोषणा BT1_BOOT_सूचीMAP		0
#घोषणा BT1_BOOT_REGS		1

काष्ठा dw_spi_bt1 अणु
	काष्ठा dw_spi		dws;
	काष्ठा clk		*clk;
	काष्ठा mux_control	*mux;

#अगर_घोषित CONFIG_SPI_DW_BT1_सूचीMAP
	व्योम __iomem		*map;
	resource_माप_प्रकार		map_len;
#पूर्ण_अगर
पूर्ण;
#घोषणा to_dw_spi_bt1(_ctlr) \
	container_of(spi_controller_get_devdata(_ctlr), काष्ठा dw_spi_bt1, dws)

प्रकार पूर्णांक (*dw_spi_bt1_init_cb)(काष्ठा platक्रमm_device *pdev,
				    काष्ठा dw_spi_bt1 *dwsbt1);

#अगर_घोषित CONFIG_SPI_DW_BT1_सूचीMAP

अटल पूर्णांक dw_spi_bt1_dirmap_create(काष्ठा spi_mem_dirmap_desc *desc)
अणु
	काष्ठा dw_spi_bt1 *dwsbt1 = to_dw_spi_bt1(desc->mem->spi->controller);

	अगर (!dwsbt1->map ||
	    !dwsbt1->dws.mem_ops.supports_op(desc->mem, &desc->info.op_पंचांगpl))
		वापस -EOPNOTSUPP;

	/*
	 * Make sure the requested region करोesn't go out of the physically
	 * mapped flash memory bounds and the operation is पढ़ो-only.
	 */
	अगर (desc->info.offset + desc->info.length > dwsbt1->map_len ||
	    desc->info.op_पंचांगpl.data.dir != SPI_MEM_DATA_IN)
		वापस -EOPNOTSUPP;

	वापस 0;
पूर्ण

/*
 * Directly mapped SPI memory region is only accessible in the dword chunks.
 * That's why we have to create a dedicated पढ़ो-method to copy data from there
 * to the passed buffer.
 */
अटल व्योम dw_spi_bt1_dirmap_copy_from_map(व्योम *to, व्योम __iomem *from, माप_प्रकार len)
अणु
	माप_प्रकार shअगरt, chunk;
	u32 data;

	/*
	 * We split the copying up पूर्णांकo the next three stages: unaligned head,
	 * aligned body, unaligned tail.
	 */
	shअगरt = (माप_प्रकार)from & 0x3;
	अगर (shअगरt) अणु
		chunk = min_t(माप_प्रकार, 4 - shअगरt, len);
		data = पढ़ोl_relaxed(from - shअगरt);
		स_नकल(to, (अक्षर *)&data + shअगरt, chunk);
		from += chunk;
		to += chunk;
		len -= chunk;
	पूर्ण

	जबतक (len >= 4) अणु
		data = पढ़ोl_relaxed(from);
		स_नकल(to, &data, 4);
		from += 4;
		to += 4;
		len -= 4;
	पूर्ण

	अगर (len) अणु
		data = पढ़ोl_relaxed(from);
		स_नकल(to, &data, len);
	पूर्ण
पूर्ण

अटल sमाप_प्रकार dw_spi_bt1_dirmap_पढ़ो(काष्ठा spi_mem_dirmap_desc *desc,
				      u64 offs, माप_प्रकार len, व्योम *buf)
अणु
	काष्ठा dw_spi_bt1 *dwsbt1 = to_dw_spi_bt1(desc->mem->spi->controller);
	काष्ठा dw_spi *dws = &dwsbt1->dws;
	काष्ठा spi_mem *mem = desc->mem;
	काष्ठा dw_spi_cfg cfg;
	पूर्णांक ret;

	/*
	 * Make sure the requested operation length is valid. Truncate the
	 * length अगर it's greater than the length of the MMIO region.
	 */
	अगर (offs >= dwsbt1->map_len || !len)
		वापस 0;

	len = min_t(माप_प्रकार, len, dwsbt1->map_len - offs);

	/* Collect the controller configuration required by the operation */
	cfg.पंचांगode = SPI_TMOD_EPROMREAD;
	cfg.dfs = 8;
	cfg.ndf = 4;
	cfg.freq = mem->spi->max_speed_hz;

	/* Make sure the corresponding CS is de-निश्चितed on transmission */
	dw_spi_set_cs(mem->spi, false);

	spi_enable_chip(dws, 0);

	dw_spi_update_config(dws, mem->spi, &cfg);

	spi_umask_पूर्णांकr(dws, SPI_INT_RXFI);

	spi_enable_chip(dws, 1);

	/*
	 * Enable the transparent mode of the System Boot Controller.
	 * The SPI core IO should have been locked beक्रमe calling this method
	 * so noone would be touching the controller' रेजिस्टरs during the
	 * dirmap operation.
	 */
	ret = mux_control_select(dwsbt1->mux, BT1_BOOT_सूचीMAP);
	अगर (ret)
		वापस ret;

	dw_spi_bt1_dirmap_copy_from_map(buf, dwsbt1->map + offs, len);

	mux_control_deselect(dwsbt1->mux);

	dw_spi_set_cs(mem->spi, true);

	ret = dw_spi_check_status(dws, true);

	वापस ret ?: len;
पूर्ण

#पूर्ण_अगर /* CONFIG_SPI_DW_BT1_सूचीMAP */

अटल पूर्णांक dw_spi_bt1_std_init(काष्ठा platक्रमm_device *pdev,
			       काष्ठा dw_spi_bt1 *dwsbt1)
अणु
	काष्ठा dw_spi *dws = &dwsbt1->dws;

	dws->irq = platक्रमm_get_irq(pdev, 0);
	अगर (dws->irq < 0)
		वापस dws->irq;

	dws->num_cs = 4;

	/*
	 * Baikal-T1 Normal SPI Controllers करोn't always keep up with full SPI
	 * bus speed especially when it comes to the concurrent access to the
	 * APB bus resources. Thus we have no choice but to set a स्थिरraपूर्णांक on
	 * the SPI bus frequency क्रम the memory operations which require to
	 * पढ़ो/ग_लिखो data as fast as possible.
	 */
	dws->max_mem_freq = 20000000U;

	dw_spi_dma_setup_generic(dws);

	वापस 0;
पूर्ण

अटल पूर्णांक dw_spi_bt1_sys_init(काष्ठा platक्रमm_device *pdev,
			       काष्ठा dw_spi_bt1 *dwsbt1)
अणु
	काष्ठा resource *mem __maybe_unused;
	काष्ठा dw_spi *dws = &dwsbt1->dws;

	/*
	 * Baikal-T1 System Boot Controller is equipped with a mux, which
	 * चयनes between the directly mapped SPI flash access mode and
	 * IO access to the DW APB SSI रेजिस्टरs. Note the mux controller
	 * must be setup to preserve the रेजिस्टरs being accessible by शेष
	 * (on idle-state).
	 */
	dwsbt1->mux = devm_mux_control_get(&pdev->dev, शून्य);
	अगर (IS_ERR(dwsbt1->mux))
		वापस PTR_ERR(dwsbt1->mux);

	/*
	 * Directly mapped SPI flash memory is a 16MB MMIO region, which can be
	 * used to access a peripheral memory device just by पढ़ोing/writing
	 * data from/to it. Note the प्रणाली APB bus will stall during each IO
	 * from/to the dirmap region until the operation is finished. So करोn't
	 * use it concurrently with समय-critical tasks (like the SPI memory
	 * operations implemented in the DW APB SSI driver).
	 */
#अगर_घोषित CONFIG_SPI_DW_BT1_सूचीMAP
	mem = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 1);
	अगर (mem) अणु
		dwsbt1->map = devm_ioremap_resource(&pdev->dev, mem);
		अगर (!IS_ERR(dwsbt1->map)) अणु
			dwsbt1->map_len = resource_size(mem);
			dws->mem_ops.dirmap_create = dw_spi_bt1_dirmap_create;
			dws->mem_ops.dirmap_पढ़ो = dw_spi_bt1_dirmap_पढ़ो;
		पूर्ण अन्यथा अणु
			dwsbt1->map = शून्य;
		पूर्ण
	पूर्ण
#पूर्ण_अगर /* CONFIG_SPI_DW_BT1_सूचीMAP */

	/*
	 * There is no IRQ, no DMA and just one CS available on the System Boot
	 * SPI controller.
	 */
	dws->irq = IRQ_NOTCONNECTED;
	dws->num_cs = 1;

	/*
	 * Baikal-T1 System Boot SPI Controller करोesn't keep up with the full
	 * SPI bus speed due to relatively slow APB bus and races क्रम it'
	 * resources from dअगरferent CPUs. The situation is worsen by a small
	 * FIFOs depth (just 8 words). It works better in a single CPU mode
	 * though, but still tends to be not fast enough at low CPU
	 * frequencies.
	 */
	अगर (num_possible_cpus() > 1)
		dws->max_mem_freq = 10000000U;
	अन्यथा
		dws->max_mem_freq = 20000000U;

	वापस 0;
पूर्ण

अटल पूर्णांक dw_spi_bt1_probe(काष्ठा platक्रमm_device *pdev)
अणु
	dw_spi_bt1_init_cb init_func;
	काष्ठा dw_spi_bt1 *dwsbt1;
	काष्ठा resource *mem;
	काष्ठा dw_spi *dws;
	पूर्णांक ret;

	dwsbt1 = devm_kzalloc(&pdev->dev, माप(काष्ठा dw_spi_bt1), GFP_KERNEL);
	अगर (!dwsbt1)
		वापस -ENOMEM;

	dws = &dwsbt1->dws;

	dws->regs = devm_platक्रमm_get_and_ioremap_resource(pdev, 0, &mem);
	अगर (IS_ERR(dws->regs))
		वापस PTR_ERR(dws->regs);

	dws->paddr = mem->start;

	dwsbt1->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(dwsbt1->clk))
		वापस PTR_ERR(dwsbt1->clk);

	ret = clk_prepare_enable(dwsbt1->clk);
	अगर (ret)
		वापस ret;

	dws->bus_num = pdev->id;
	dws->reg_io_width = 4;
	dws->max_freq = clk_get_rate(dwsbt1->clk);
	अगर (!dws->max_freq) अणु
		ret = -EINVAL;
		जाओ err_disable_clk;
	पूर्ण

	init_func = device_get_match_data(&pdev->dev);
	ret = init_func(pdev, dwsbt1);
	अगर (ret)
		जाओ err_disable_clk;

	pm_runसमय_enable(&pdev->dev);

	ret = dw_spi_add_host(&pdev->dev, dws);
	अगर (ret)
		जाओ err_disable_clk;

	platक्रमm_set_drvdata(pdev, dwsbt1);

	वापस 0;

err_disable_clk:
	clk_disable_unprepare(dwsbt1->clk);

	वापस ret;
पूर्ण

अटल पूर्णांक dw_spi_bt1_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा dw_spi_bt1 *dwsbt1 = platक्रमm_get_drvdata(pdev);

	dw_spi_हटाओ_host(&dwsbt1->dws);

	pm_runसमय_disable(&pdev->dev);

	clk_disable_unprepare(dwsbt1->clk);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id dw_spi_bt1_of_match[] = अणु
	अणु .compatible = "baikal,bt1-ssi", .data = dw_spi_bt1_std_initपूर्ण,
	अणु .compatible = "baikal,bt1-sys-ssi", .data = dw_spi_bt1_sys_initपूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, dw_spi_bt1_of_match);

अटल काष्ठा platक्रमm_driver dw_spi_bt1_driver = अणु
	.probe	= dw_spi_bt1_probe,
	.हटाओ	= dw_spi_bt1_हटाओ,
	.driver	= अणु
		.name		= "bt1-sys-ssi",
		.of_match_table	= dw_spi_bt1_of_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(dw_spi_bt1_driver);

MODULE_AUTHOR("Serge Semin <Sergey.Semin@baikalelectronics.ru>");
MODULE_DESCRIPTION("Baikal-T1 System Boot SPI Controller driver");
MODULE_LICENSE("GPL v2");
