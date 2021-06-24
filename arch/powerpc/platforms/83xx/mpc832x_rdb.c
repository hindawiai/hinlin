<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * arch/घातerpc/platक्रमms/83xx/mpc832x_rdb.c
 *
 * Copyright (C) Freescale Semiconductor, Inc. 2007. All rights reserved.
 *
 * Description:
 * MPC832x RDB board specअगरic routines.
 * This file is based on mpc832x_mds.c and mpc8313_rdb.c
 * Author: Michael Barkowski <michael.barkowski@मुक्तscale.com>
 */

#समावेश <linux/pci.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/spi/mmc_spi.h>
#समावेश <linux/mmc/host.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/fsl_devices.h>

#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/ipic.h>
#समावेश <यंत्र/udbg.h>
#समावेश <soc/fsl/qe/qe.h>
#समावेश <sysdev/fsl_soc.h>
#समावेश <sysdev/fsl_pci.h>

#समावेश "mpc83xx.h"

#अघोषित DEBUG
#अगर_घोषित DEBUG
#घोषणा DBG(fmt...) udbg_म_लिखो(fmt)
#अन्यथा
#घोषणा DBG(fmt...)
#पूर्ण_अगर

#अगर_घोषित CONFIG_QUICC_ENGINE
अटल पूर्णांक __init of_fsl_spi_probe(अक्षर *type, अक्षर *compatible, u32 sysclk,
				   काष्ठा spi_board_info *board_infos,
				   अचिन्हित पूर्णांक num_board_infos,
				   व्योम (*cs_control)(काष्ठा spi_device *dev,
						      bool on))
अणु
	काष्ठा device_node *np;
	अचिन्हित पूर्णांक i = 0;

	क्रम_each_compatible_node(np, type, compatible) अणु
		पूर्णांक ret;
		अचिन्हित पूर्णांक j;
		स्थिर व्योम *prop;
		काष्ठा resource res[2];
		काष्ठा platक्रमm_device *pdev;
		काष्ठा fsl_spi_platक्रमm_data pdata = अणु
			.cs_control = cs_control,
		पूर्ण;

		स_रखो(res, 0, माप(res));

		pdata.sysclk = sysclk;

		prop = of_get_property(np, "reg", शून्य);
		अगर (!prop)
			जाओ err;
		pdata.bus_num = *(u32 *)prop;

		prop = of_get_property(np, "cell-index", शून्य);
		अगर (prop)
			i = *(u32 *)prop;

		prop = of_get_property(np, "mode", शून्य);
		अगर (prop && !म_भेद(prop, "cpu-qe"))
			pdata.flags = SPI_QE_CPU_MODE;

		क्रम (j = 0; j < num_board_infos; j++) अणु
			अगर (board_infos[j].bus_num == pdata.bus_num)
				pdata.max_chipselect++;
		पूर्ण

		अगर (!pdata.max_chipselect)
			जारी;

		ret = of_address_to_resource(np, 0, &res[0]);
		अगर (ret)
			जाओ err;

		ret = of_irq_to_resource(np, 0, &res[1]);
		अगर (ret <= 0)
			जाओ err;

		pdev = platक्रमm_device_alloc("mpc83xx_spi", i);
		अगर (!pdev)
			जाओ err;

		ret = platक्रमm_device_add_data(pdev, &pdata, माप(pdata));
		अगर (ret)
			जाओ unreg;

		ret = platक्रमm_device_add_resources(pdev, res,
						    ARRAY_SIZE(res));
		अगर (ret)
			जाओ unreg;

		ret = platक्रमm_device_add(pdev);
		अगर (ret)
			जाओ unreg;

		जाओ next;
unreg:
		platक्रमm_device_del(pdev);
err:
		pr_err("%pOF: registration failed\n", np);
next:
		i++;
	पूर्ण

	वापस i;
पूर्ण

अटल पूर्णांक __init fsl_spi_init(काष्ठा spi_board_info *board_infos,
			       अचिन्हित पूर्णांक num_board_infos,
			       व्योम (*cs_control)(काष्ठा spi_device *spi,
						  bool on))
अणु
	u32 sysclk = -1;
	पूर्णांक ret;

	/* SPI controller is either घड़ीed from QE or SoC घड़ी */
	sysclk = get_brgfreq();
	अगर (sysclk == -1) अणु
		sysclk = fsl_get_sys_freq();
		अगर (sysclk == -1)
			वापस -ENODEV;
	पूर्ण

	ret = of_fsl_spi_probe(शून्य, "fsl,spi", sysclk, board_infos,
			       num_board_infos, cs_control);
	अगर (!ret)
		of_fsl_spi_probe("spi", "fsl_spi", sysclk, board_infos,
				 num_board_infos, cs_control);

	वापस spi_रेजिस्टर_board_info(board_infos, num_board_infos);
पूर्ण

अटल व्योम mpc83xx_spi_cs_control(काष्ठा spi_device *spi, bool on)
अणु
	pr_debug("%s %d %d\n", __func__, spi->chip_select, on);
	par_io_data_set(3, 13, on);
पूर्ण

अटल काष्ठा mmc_spi_platक्रमm_data mpc832x_mmc_pdata = अणु
	.ocr_mask = MMC_VDD_33_34,
पूर्ण;

अटल काष्ठा spi_board_info mpc832x_spi_boardinfo = अणु
	.bus_num = 0x4c0,
	.chip_select = 0,
	.max_speed_hz = 50000000,
	.modalias = "mmc_spi",
	.platक्रमm_data = &mpc832x_mmc_pdata,
पूर्ण;

अटल पूर्णांक __init mpc832x_spi_init(व्योम)
अणु
	par_io_config_pin(3,  0, 3, 0, 1, 0); /* SPI1 MOSI, I/O */
	par_io_config_pin(3,  1, 3, 0, 1, 0); /* SPI1 MISO, I/O */
	par_io_config_pin(3,  2, 3, 0, 1, 0); /* SPI1 CLK,  I/O */
	par_io_config_pin(3,  3, 2, 0, 1, 0); /* SPI1 SEL,  I   */

	par_io_config_pin(3, 13, 1, 0, 0, 0); /* !SD_CS,    O */
	par_io_config_pin(3, 14, 2, 0, 0, 0); /* SD_INSERT, I */
	par_io_config_pin(3, 15, 2, 0, 0, 0); /* SD_PROTECT,I */

	/*
	 * Don't bother with legacy stuff when device tree contains
	 * mmc-spi-slot node.
	 */
	अगर (of_find_compatible_node(शून्य, शून्य, "mmc-spi-slot"))
		वापस 0;
	वापस fsl_spi_init(&mpc832x_spi_boardinfo, 1, mpc83xx_spi_cs_control);
पूर्ण
machine_device_initcall(mpc832x_rdb, mpc832x_spi_init);
#पूर्ण_अगर /* CONFIG_QUICC_ENGINE */

/* ************************************************************************
 *
 * Setup the architecture
 *
 */
अटल व्योम __init mpc832x_rdb_setup_arch(व्योम)
अणु
#अगर defined(CONFIG_QUICC_ENGINE)
	काष्ठा device_node *np;
#पूर्ण_अगर

	mpc83xx_setup_arch();

#अगर_घोषित CONFIG_QUICC_ENGINE
	अगर ((np = of_find_node_by_name(शून्य, "par_io")) != शून्य) अणु
		par_io_init(np);
		of_node_put(np);

		क्रम_each_node_by_name(np, "ucc")
			par_io_of_config(np);
	पूर्ण
#पूर्ण_अगर				/* CONFIG_QUICC_ENGINE */
पूर्ण

machine_device_initcall(mpc832x_rdb, mpc83xx_declare_of_platक्रमm_devices);

/*
 * Called very early, MMU is off, device-tree isn't unflattened
 */
अटल पूर्णांक __init mpc832x_rdb_probe(व्योम)
अणु
	वापस of_machine_is_compatible("MPC832xRDB");
पूर्ण

define_machine(mpc832x_rdb) अणु
	.name		= "MPC832x RDB",
	.probe		= mpc832x_rdb_probe,
	.setup_arch	= mpc832x_rdb_setup_arch,
	.discover_phbs  = mpc83xx_setup_pci,
	.init_IRQ	= mpc83xx_ipic_init_IRQ,
	.get_irq	= ipic_get_irq,
	.restart	= mpc83xx_restart,
	.समय_init	= mpc83xx_समय_init,
	.calibrate_decr	= generic_calibrate_decr,
	.progress	= udbg_progress,
पूर्ण;
