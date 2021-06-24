<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Interconnect framework driver क्रम i.MX8MM SoC
 *
 * Copyright (c) 2019, BayLibre
 * Copyright (c) 2019-2020, NXP
 * Author: Alexandre Bailon <abailon@baylibre.com>
 * Author: Leonard Crestez <leonard.crestez@nxp.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <dt-bindings/पूर्णांकerconnect/imx8mm.h>

#समावेश "imx.h"

अटल स्थिर काष्ठा imx_icc_node_adj_desc imx8mm_dram_adj = अणु
	.bw_mul = 1,
	.bw_भाग = 16,
	.phandle_name = "fsl,ddrc",
पूर्ण;

अटल स्थिर काष्ठा imx_icc_node_adj_desc imx8mm_noc_adj = अणु
	.bw_mul = 1,
	.bw_भाग = 16,
	.मुख्य_noc = true,
पूर्ण;

/*
 * Describe bus masters, slaves and connections between them
 *
 * This is a simplअगरied subset of the bus diagram, there are several other
 * PL301 nics which are skipped/merged पूर्णांकo PL301_MAIN
 */
अटल काष्ठा imx_icc_node_desc nodes[] = अणु
	DEFINE_BUS_INTERCONNECT("NOC", IMX8MM_ICN_NOC, &imx8mm_noc_adj,
			IMX8MM_ICS_DRAM, IMX8MM_ICN_MAIN),

	DEFINE_BUS_SLAVE("DRAM", IMX8MM_ICS_DRAM, &imx8mm_dram_adj),
	DEFINE_BUS_SLAVE("OCRAM", IMX8MM_ICS_OCRAM, शून्य),
	DEFINE_BUS_MASTER("A53", IMX8MM_ICM_A53, IMX8MM_ICN_NOC),

	/* VPUMIX */
	DEFINE_BUS_MASTER("VPU H1", IMX8MM_ICM_VPU_H1, IMX8MM_ICN_VIDEO),
	DEFINE_BUS_MASTER("VPU G1", IMX8MM_ICM_VPU_G1, IMX8MM_ICN_VIDEO),
	DEFINE_BUS_MASTER("VPU G2", IMX8MM_ICM_VPU_G2, IMX8MM_ICN_VIDEO),
	DEFINE_BUS_INTERCONNECT("PL301_VIDEO", IMX8MM_ICN_VIDEO, शून्य, IMX8MM_ICN_NOC),

	/* GPUMIX */
	DEFINE_BUS_MASTER("GPU 2D", IMX8MM_ICM_GPU2D, IMX8MM_ICN_GPU),
	DEFINE_BUS_MASTER("GPU 3D", IMX8MM_ICM_GPU3D, IMX8MM_ICN_GPU),
	DEFINE_BUS_INTERCONNECT("PL301_GPU", IMX8MM_ICN_GPU, शून्य, IMX8MM_ICN_NOC),

	/* DISPLAYMIX */
	DEFINE_BUS_MASTER("CSI", IMX8MM_ICM_CSI, IMX8MM_ICN_MIPI),
	DEFINE_BUS_MASTER("LCDIF", IMX8MM_ICM_LCDIF, IMX8MM_ICN_MIPI),
	DEFINE_BUS_INTERCONNECT("PL301_MIPI", IMX8MM_ICN_MIPI, शून्य, IMX8MM_ICN_NOC),

	/* HSIO */
	DEFINE_BUS_MASTER("USB1", IMX8MM_ICM_USB1, IMX8MM_ICN_HSIO),
	DEFINE_BUS_MASTER("USB2", IMX8MM_ICM_USB2, IMX8MM_ICN_HSIO),
	DEFINE_BUS_MASTER("PCIE", IMX8MM_ICM_PCIE, IMX8MM_ICN_HSIO),
	DEFINE_BUS_INTERCONNECT("PL301_HSIO", IMX8MM_ICN_HSIO, शून्य, IMX8MM_ICN_NOC),

	/* Audio */
	DEFINE_BUS_MASTER("SDMA2", IMX8MM_ICM_SDMA2, IMX8MM_ICN_AUDIO),
	DEFINE_BUS_MASTER("SDMA3", IMX8MM_ICM_SDMA3, IMX8MM_ICN_AUDIO),
	DEFINE_BUS_INTERCONNECT("PL301_AUDIO", IMX8MM_ICN_AUDIO, शून्य, IMX8MM_ICN_MAIN),

	/* Ethernet */
	DEFINE_BUS_MASTER("ENET", IMX8MM_ICM_ENET, IMX8MM_ICN_ENET),
	DEFINE_BUS_INTERCONNECT("PL301_ENET", IMX8MM_ICN_ENET, शून्य, IMX8MM_ICN_MAIN),

	/* Other */
	DEFINE_BUS_MASTER("SDMA1", IMX8MM_ICM_SDMA1, IMX8MM_ICN_MAIN),
	DEFINE_BUS_MASTER("NAND", IMX8MM_ICM_न_अंकD, IMX8MM_ICN_MAIN),
	DEFINE_BUS_MASTER("USDHC1", IMX8MM_ICM_USDHC1, IMX8MM_ICN_MAIN),
	DEFINE_BUS_MASTER("USDHC2", IMX8MM_ICM_USDHC2, IMX8MM_ICN_MAIN),
	DEFINE_BUS_MASTER("USDHC3", IMX8MM_ICM_USDHC3, IMX8MM_ICN_MAIN),
	DEFINE_BUS_INTERCONNECT("PL301_MAIN", IMX8MM_ICN_MAIN, शून्य,
			IMX8MM_ICN_NOC, IMX8MM_ICS_OCRAM),
पूर्ण;

अटल पूर्णांक imx8mm_icc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	वापस imx_icc_रेजिस्टर(pdev, nodes, ARRAY_SIZE(nodes));
पूर्ण

अटल पूर्णांक imx8mm_icc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	वापस imx_icc_unरेजिस्टर(pdev);
पूर्ण

अटल काष्ठा platक्रमm_driver imx8mm_icc_driver = अणु
	.probe = imx8mm_icc_probe,
	.हटाओ = imx8mm_icc_हटाओ,
	.driver = अणु
		.name = "imx8mm-interconnect",
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(imx8mm_icc_driver);
MODULE_AUTHOR("Alexandre Bailon <abailon@baylibre.com>");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:imx8mm-interconnect");
