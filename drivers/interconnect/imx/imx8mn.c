<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Interconnect framework driver क्रम i.MX8MN SoC
 *
 * Copyright (c) 2019-2020, NXP
 */

#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <dt-bindings/पूर्णांकerconnect/imx8mn.h>

#समावेश "imx.h"

अटल स्थिर काष्ठा imx_icc_node_adj_desc imx8mn_dram_adj = अणु
	.bw_mul = 1,
	.bw_भाग = 4,
	.phandle_name = "fsl,ddrc",
पूर्ण;

अटल स्थिर काष्ठा imx_icc_node_adj_desc imx8mn_noc_adj = अणु
	.bw_mul = 1,
	.bw_भाग = 4,
	.मुख्य_noc = true,
पूर्ण;

/*
 * Describe bus masters, slaves and connections between them
 *
 * This is a simplअगरied subset of the bus diagram, there are several other
 * PL301 nics which are skipped/merged पूर्णांकo PL301_MAIN
 */
अटल काष्ठा imx_icc_node_desc nodes[] = अणु
	DEFINE_BUS_INTERCONNECT("NOC", IMX8MN_ICN_NOC, &imx8mn_noc_adj,
			IMX8MN_ICS_DRAM, IMX8MN_ICN_MAIN),

	DEFINE_BUS_SLAVE("DRAM", IMX8MN_ICS_DRAM, &imx8mn_dram_adj),
	DEFINE_BUS_SLAVE("OCRAM", IMX8MN_ICS_OCRAM, शून्य),
	DEFINE_BUS_MASTER("A53", IMX8MN_ICM_A53, IMX8MN_ICN_NOC),

	/* GPUMIX */
	DEFINE_BUS_MASTER("GPU", IMX8MN_ICM_GPU, IMX8MN_ICN_GPU),
	DEFINE_BUS_INTERCONNECT("PL301_GPU", IMX8MN_ICN_GPU, शून्य, IMX8MN_ICN_NOC),

	/* DISPLAYMIX */
	DEFINE_BUS_MASTER("CSI1", IMX8MN_ICM_CSI1, IMX8MN_ICN_MIPI),
	DEFINE_BUS_MASTER("CSI2", IMX8MN_ICM_CSI2, IMX8MN_ICN_MIPI),
	DEFINE_BUS_MASTER("ISI", IMX8MN_ICM_ISI, IMX8MN_ICN_MIPI),
	DEFINE_BUS_MASTER("LCDIF", IMX8MN_ICM_LCDIF, IMX8MN_ICN_MIPI),
	DEFINE_BUS_INTERCONNECT("PL301_MIPI", IMX8MN_ICN_MIPI, शून्य, IMX8MN_ICN_NOC),

	/* USB goes straight to NOC */
	DEFINE_BUS_MASTER("USB", IMX8MN_ICM_USB, IMX8MN_ICN_NOC),

	/* Audio */
	DEFINE_BUS_MASTER("SDMA2", IMX8MN_ICM_SDMA2, IMX8MN_ICN_AUDIO),
	DEFINE_BUS_MASTER("SDMA3", IMX8MN_ICM_SDMA3, IMX8MN_ICN_AUDIO),
	DEFINE_BUS_INTERCONNECT("PL301_AUDIO", IMX8MN_ICN_AUDIO, शून्य, IMX8MN_ICN_MAIN),

	/* Ethernet */
	DEFINE_BUS_MASTER("ENET", IMX8MN_ICM_ENET, IMX8MN_ICN_ENET),
	DEFINE_BUS_INTERCONNECT("PL301_ENET", IMX8MN_ICN_ENET, शून्य, IMX8MN_ICN_MAIN),

	/* Other */
	DEFINE_BUS_MASTER("SDMA1", IMX8MN_ICM_SDMA1, IMX8MN_ICN_MAIN),
	DEFINE_BUS_MASTER("NAND", IMX8MN_ICM_न_अंकD, IMX8MN_ICN_MAIN),
	DEFINE_BUS_MASTER("USDHC1", IMX8MN_ICM_USDHC1, IMX8MN_ICN_MAIN),
	DEFINE_BUS_MASTER("USDHC2", IMX8MN_ICM_USDHC2, IMX8MN_ICN_MAIN),
	DEFINE_BUS_MASTER("USDHC3", IMX8MN_ICM_USDHC3, IMX8MN_ICN_MAIN),
	DEFINE_BUS_INTERCONNECT("PL301_MAIN", IMX8MN_ICN_MAIN, शून्य,
			IMX8MN_ICN_NOC, IMX8MN_ICS_OCRAM),
पूर्ण;

अटल पूर्णांक imx8mn_icc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	वापस imx_icc_रेजिस्टर(pdev, nodes, ARRAY_SIZE(nodes));
पूर्ण

अटल पूर्णांक imx8mn_icc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	वापस imx_icc_unरेजिस्टर(pdev);
पूर्ण

अटल काष्ठा platक्रमm_driver imx8mn_icc_driver = अणु
	.probe = imx8mn_icc_probe,
	.हटाओ = imx8mn_icc_हटाओ,
	.driver = अणु
		.name = "imx8mn-interconnect",
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(imx8mn_icc_driver);
MODULE_ALIAS("platform:imx8mn-interconnect");
MODULE_AUTHOR("Leonard Crestez <leonard.crestez@nxp.com>");
MODULE_LICENSE("GPL v2");
