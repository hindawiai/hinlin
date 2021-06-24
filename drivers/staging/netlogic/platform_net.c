<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0 OR BSD-2-Clause)
/*
 * Copyright (c) 2003-2012 Broadcom Corporation
 * All Rights Reserved
 */

#समावेश <linux/device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/delay.h>
#समावेश <linux/ioport.h>
#समावेश <linux/resource.h>
#समावेश <linux/phy.h>

#समावेश <यंत्र/netlogic/haldefs.h>
#समावेश <यंत्र/netlogic/common.h>
#समावेश <यंत्र/netlogic/xlr/fmn.h>
#समावेश <यंत्र/netlogic/xlr/xlr.h>
#समावेश <यंत्र/netlogic/psb-bootinfo.h>
#समावेश <यंत्र/netlogic/xlr/pic.h>
#समावेश <यंत्र/netlogic/xlr/iomap.h>

#समावेश "platform_net.h"

/* Linux Net */
#घोषणा MAX_NUM_GMAC		8
#घोषणा MAX_NUM_XLS_GMAC	8
#घोषणा MAX_NUM_XLR_GMAC	4

अटल u32 xlr_gmac_offsets[] = अणु
	NETLOGIC_IO_GMAC_0_OFFSET, NETLOGIC_IO_GMAC_1_OFFSET,
	NETLOGIC_IO_GMAC_2_OFFSET, NETLOGIC_IO_GMAC_3_OFFSET,
	NETLOGIC_IO_GMAC_4_OFFSET, NETLOGIC_IO_GMAC_5_OFFSET,
	NETLOGIC_IO_GMAC_6_OFFSET, NETLOGIC_IO_GMAC_7_OFFSET
पूर्ण;

अटल u32 xlr_gmac_irqs[] = अणु PIC_GMAC_0_IRQ, PIC_GMAC_1_IRQ,
	PIC_GMAC_2_IRQ, PIC_GMAC_3_IRQ,
	PIC_GMAC_4_IRQ, PIC_GMAC_5_IRQ,
	PIC_GMAC_6_IRQ, PIC_GMAC_7_IRQ
पूर्ण;

अटल काष्ठा resource xlr_net0_res[8];
अटल काष्ठा resource xlr_net1_res[8];
अटल u32 __iomem *gmac4_addr;
अटल u32 __iomem *gpio_addr;

अटल व्योम xlr_resource_init(काष्ठा resource *res, पूर्णांक offset, पूर्णांक irq)
अणु
	res->name = "gmac";

	res->start = CPHYSADDR(nlm_mmio_base(offset));
	res->end = res->start + 0xfff;
	res->flags = IORESOURCE_MEM;

	res++;
	res->name = "gmac";
	res->start = irq;
	res->end = irq;
	res->flags = IORESOURCE_IRQ;
पूर्ण

अटल काष्ठा platक्रमm_device *gmac_controller2_init(व्योम *gmac0_addr)
अणु
	पूर्णांक mac;
	अटल काष्ठा xlr_net_data ndata1 = अणु
		.phy_पूर्णांकerface	= PHY_INTERFACE_MODE_SGMII,
		.rfr_station	= FMN_STNID_GMAC1_FR_0,
		.bucket_size	= xlr_board_fmn_config.bucket_size,
		.gmac_fmn_info	= &xlr_board_fmn_config.gmac[1],
	पूर्ण;

	अटल काष्ठा platक्रमm_device xlr_net_dev1 = अणु
		.name		= "xlr-net",
		.id		= 1,
		.dev.platक्रमm_data = &ndata1,
	पूर्ण;

	gmac4_addr =
		ioremap(CPHYSADDR(nlm_mmio_base(NETLOGIC_IO_GMAC_4_OFFSET)),
			0xfff);
	ndata1.serdes_addr = gmac4_addr;
	ndata1.pcs_addr	= gmac4_addr;
	ndata1.mii_addr	= gmac0_addr;
	ndata1.gpio_addr = gpio_addr;
	ndata1.cpu_mask = nlm_current_node()->coremask;

	xlr_net_dev1.resource = xlr_net1_res;

	क्रम (mac = 0; mac < 4; mac++) अणु
		ndata1.tx_stnid[mac] = FMN_STNID_GMAC1_TX0 + mac;
		ndata1.phy_addr[mac] = mac + 4 + 0x10;

		xlr_resource_init(&xlr_net1_res[mac * 2],
				  xlr_gmac_offsets[mac + 4],
				  xlr_gmac_irqs[mac + 4]);
	पूर्ण
	xlr_net_dev1.num_resources = 8;

	वापस &xlr_net_dev1;
पूर्ण

अटल व्योम xls_gmac_init(व्योम)
अणु
	पूर्णांक mac;
	काष्ठा platक्रमm_device *xlr_net_dev1;
	व्योम __iomem *gmac0_addr =
		ioremap(CPHYSADDR(nlm_mmio_base(NETLOGIC_IO_GMAC_0_OFFSET)),
			0xfff);

	अटल काष्ठा xlr_net_data ndata0 = अणु
		.rfr_station	= FMN_STNID_GMACRFR_0,
		.bucket_size	= xlr_board_fmn_config.bucket_size,
		.gmac_fmn_info	= &xlr_board_fmn_config.gmac[0],
	पूर्ण;

	अटल काष्ठा platक्रमm_device xlr_net_dev0 = अणु
		.name		= "xlr-net",
		.id		= 0,
	पूर्ण;
	xlr_net_dev0.dev.platक्रमm_data = &ndata0;
	ndata0.serdes_addr = gmac0_addr;
	ndata0.pcs_addr	= gmac0_addr;
	ndata0.mii_addr	= gmac0_addr;

	/* Passing GPIO base क्रम serdes init. Only needed on sgmii ports */
	gpio_addr =
		ioremap(CPHYSADDR(nlm_mmio_base(NETLOGIC_IO_GPIO_OFFSET)),
			0xfff);
	ndata0.gpio_addr = gpio_addr;
	ndata0.cpu_mask = nlm_current_node()->coremask;

	xlr_net_dev0.resource = xlr_net0_res;

	चयन (nlm_prom_info.board_major_version) अणु
	हाल 12:
		/* first block RGMII or XAUI, use RGMII */
		ndata0.phy_पूर्णांकerface = PHY_INTERFACE_MODE_RGMII;
		ndata0.tx_stnid[0] = FMN_STNID_GMAC0_TX0;
		ndata0.phy_addr[0] = 0;

		xlr_net_dev0.num_resources = 2;

		xlr_resource_init(&xlr_net0_res[0], xlr_gmac_offsets[0],
				  xlr_gmac_irqs[0]);
		platक्रमm_device_रेजिस्टर(&xlr_net_dev0);

		/* second block is XAUI, not supported yet */
		अवरोध;
	शेष:
		/* शेष XLS config, all ports SGMII */
		ndata0.phy_पूर्णांकerface = PHY_INTERFACE_MODE_SGMII;
		क्रम (mac = 0; mac < 4; mac++) अणु
			ndata0.tx_stnid[mac] = FMN_STNID_GMAC0_TX0 + mac;
			ndata0.phy_addr[mac] = mac + 0x10;

			xlr_resource_init(&xlr_net0_res[mac * 2],
					  xlr_gmac_offsets[mac],
					xlr_gmac_irqs[mac]);
		पूर्ण
		xlr_net_dev0.num_resources = 8;
		platक्रमm_device_रेजिस्टर(&xlr_net_dev0);

		xlr_net_dev1 = gmac_controller2_init(gmac0_addr);
		platक्रमm_device_रेजिस्टर(xlr_net_dev1);
	पूर्ण
पूर्ण

अटल व्योम xlr_gmac_init(व्योम)
अणु
	पूर्णांक mac;

	/* assume all GMACs क्रम now */
	अटल काष्ठा xlr_net_data ndata0 = अणु
		.phy_पूर्णांकerface	= PHY_INTERFACE_MODE_RGMII,
		.serdes_addr	= शून्य,
		.pcs_addr	= शून्य,
		.rfr_station	= FMN_STNID_GMACRFR_0,
		.bucket_size	= xlr_board_fmn_config.bucket_size,
		.gmac_fmn_info	= &xlr_board_fmn_config.gmac[0],
		.gpio_addr	= शून्य,
	पूर्ण;

	अटल काष्ठा platक्रमm_device xlr_net_dev0 = अणु
		.name		= "xlr-net",
		.id		= 0,
		.dev.platक्रमm_data = &ndata0,
	पूर्ण;
	ndata0.mii_addr =
		ioremap(CPHYSADDR(nlm_mmio_base(NETLOGIC_IO_GMAC_0_OFFSET)),
			0xfff);

	ndata0.cpu_mask = nlm_current_node()->coremask;

	क्रम (mac = 0; mac < MAX_NUM_XLR_GMAC; mac++) अणु
		ndata0.tx_stnid[mac] = FMN_STNID_GMAC0_TX0 + mac;
		ndata0.phy_addr[mac] = mac;
		xlr_resource_init(&xlr_net0_res[mac * 2], xlr_gmac_offsets[mac],
				  xlr_gmac_irqs[mac]);
	पूर्ण
	xlr_net_dev0.num_resources = 8;
	xlr_net_dev0.resource = xlr_net0_res;

	platक्रमm_device_रेजिस्टर(&xlr_net_dev0);
पूर्ण

अटल पूर्णांक __init xlr_net_init(व्योम)
अणु
	अगर (nlm_chip_is_xls())
		xls_gmac_init();
	अन्यथा
		xlr_gmac_init();

	वापस 0;
पूर्ण

arch_initcall(xlr_net_init);
