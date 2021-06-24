<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Interconnect framework driver क्रम i.MX8MQ SoC
 *
 * Copyright (c) 2019-2020, NXP
 */

#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पूर्णांकerconnect-provider.h>
#समावेश <dt-bindings/पूर्णांकerconnect/imx8mq.h>

#समावेश "imx.h"

अटल स्थिर काष्ठा imx_icc_node_adj_desc imx8mq_dram_adj = अणु
	.bw_mul = 1,
	.bw_भाग = 4,
	.phandle_name = "fsl,ddrc",
पूर्ण;

अटल स्थिर काष्ठा imx_icc_node_adj_desc imx8mq_noc_adj = अणु
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
	DEFINE_BUS_INTERCONNECT("NOC", IMX8MQ_ICN_NOC, &imx8mq_noc_adj,
			IMX8MQ_ICS_DRAM, IMX8MQ_ICN_MAIN),

	DEFINE_BUS_SLAVE("DRAM", IMX8MQ_ICS_DRAM, &imx8mq_dram_adj),
	DEFINE_BUS_SLAVE("OCRAM", IMX8MQ_ICS_OCRAM, शून्य),
	DEFINE_BUS_MASTER("A53", IMX8MQ_ICM_A53, IMX8MQ_ICN_NOC),

	/* VPUMIX */
	DEFINE_BUS_MASTER("VPU", IMX8MQ_ICM_VPU, IMX8MQ_ICN_VIDEO),
	DEFINE_BUS_INTERCONNECT("PL301_VIDEO", IMX8MQ_ICN_VIDEO, शून्य, IMX8MQ_ICN_NOC),

	/* GPUMIX */
	DEFINE_BUS_MASTER("GPU", IMX8MQ_ICM_GPU, IMX8MQ_ICN_GPU),
	DEFINE_BUS_INTERCONNECT("PL301_GPU", IMX8MQ_ICN_GPU, शून्य, IMX8MQ_ICN_NOC),

	/* DISPMIX (only क्रम DCSS) */
	DEFINE_BUS_MASTER("DC", IMX8MQ_ICM_DCSS, IMX8MQ_ICN_DCSS),
	DEFINE_BUS_INTERCONNECT("PL301_DC", IMX8MQ_ICN_DCSS, शून्य, IMX8MQ_ICN_NOC),

	/* USBMIX */
	DEFINE_BUS_MASTER("USB1", IMX8MQ_ICM_USB1, IMX8MQ_ICN_USB),
	DEFINE_BUS_MASTER("USB2", IMX8MQ_ICM_USB2, IMX8MQ_ICN_USB),
	DEFINE_BUS_INTERCONNECT("PL301_USB", IMX8MQ_ICN_USB, शून्य, IMX8MQ_ICN_NOC),

	/* PL301_DISPLAY (IPs other than DCSS, inside SUPERMIX) */
	DEFINE_BUS_MASTER("CSI1", IMX8MQ_ICM_CSI1, IMX8MQ_ICN_DISPLAY),
	DEFINE_BUS_MASTER("CSI2", IMX8MQ_ICM_CSI2, IMX8MQ_ICN_DISPLAY),
	DEFINE_BUS_MASTER("LCDIF", IMX8MQ_ICM_LCDIF, IMX8MQ_ICN_DISPLAY),
	DEFINE_BUS_INTERCONNECT("PL301_DISPLAY", IMX8MQ_ICN_DISPLAY, शून्य, IMX8MQ_ICN_MAIN),

	/* AUDIO */
	DEFINE_BUS_MASTER("SDMA2", IMX8MQ_ICM_SDMA2, IMX8MQ_ICN_AUDIO),
	DEFINE_BUS_INTERCONNECT("PL301_AUDIO", IMX8MQ_ICN_AUDIO, शून्य, IMX8MQ_ICN_DISPLAY),

	/* ENET */
	DEFINE_BUS_MASTER("ENET", IMX8MQ_ICM_ENET, IMX8MQ_ICN_ENET),
	DEFINE_BUS_INTERCONNECT("PL301_ENET", IMX8MQ_ICN_ENET, शून्य, IMX8MQ_ICN_MAIN),

	/* OTHER */
	DEFINE_BUS_MASTER("SDMA1", IMX8MQ_ICM_SDMA1, IMX8MQ_ICN_MAIN),
	DEFINE_BUS_MASTER("NAND", IMX8MQ_ICM_न_अंकD, IMX8MQ_ICN_MAIN),
	DEFINE_BUS_MASTER("USDHC1", IMX8MQ_ICM_USDHC1, IMX8MQ_ICN_MAIN),
	DEFINE_BUS_MASTER("USDHC2", IMX8MQ_ICM_USDHC2, IMX8MQ_ICN_MAIN),
	DEFINE_BUS_MASTER("PCIE1", IMX8MQ_ICM_PCIE1, IMX8MQ_ICN_MAIN),
	DEFINE_BUS_MASTER("PCIE2", IMX8MQ_ICM_PCIE2, IMX8MQ_ICN_MAIN),
	DEFINE_BUS_INTERCONNECT("PL301_MAIN", IMX8MQ_ICN_MAIN, शून्य,
			IMX8MQ_ICN_NOC, IMX8MQ_ICS_OCRAM),
पूर्ण;

अटल पूर्णांक imx8mq_icc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	वापस imx_icc_रेजिस्टर(pdev, nodes, ARRAY_SIZE(nodes));
पूर्ण

अटल पूर्णांक imx8mq_icc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	वापस imx_icc_unरेजिस्टर(pdev);
पूर्ण

अटल काष्ठा platक्रमm_driver imx8mq_icc_driver = अणु
	.probe = imx8mq_icc_probe,
	.हटाओ = imx8mq_icc_हटाओ,
	.driver = अणु
		.name = "imx8mq-interconnect",
		.sync_state = icc_sync_state,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(imx8mq_icc_driver);
MODULE_ALIAS("platform:imx8mq-interconnect");
MODULE_AUTHOR("Leonard Crestez <leonard.crestez@nxp.com>");
MODULE_LICENSE("GPL v2");
