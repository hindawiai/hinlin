<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ARC HSDK Platक्रमm support code
 *
 * Copyright (C) 2017 Synopsys, Inc. (www.synopsys.com)
 */

#समावेश <linux/init.h>
#समावेश <linux/of_fdt.h>
#समावेश <linux/libfdt.h>
#समावेश <linux/smp.h>
#समावेश <यंत्र/arcregs.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/mach_desc.h>

पूर्णांक arc_hsdk_axi_dmac_coherent __section(".data") = 0;

#घोषणा ARC_CCM_UNUSED_ADDR	0x60000000


#घोषणा ARC_PERIPHERAL_BASE	0xf0000000
#घोषणा CREG_BASE		(ARC_PERIPHERAL_BASE + 0x1000)

#घोषणा SDIO_BASE		(ARC_PERIPHERAL_BASE + 0xA000)
#घोषणा SDIO_UHS_REG_EXT	(SDIO_BASE + 0x108)
#घोषणा SDIO_UHS_REG_EXT_DIV_2	(2 << 30)

#घोषणा HSDK_GPIO_INTC          (ARC_PERIPHERAL_BASE + 0x3000)

अटल व्योम __init hsdk_enable_gpio_पूर्णांकc_wire(व्योम)
अणु
	/*
	 * Peripherals on CPU Card are wired to cpu पूर्णांकc via पूर्णांकermediate
	 * DW APB GPIO blocks (मुख्यly क्रम debouncing)
	 *
	 *         ---------------------
	 *        |  snps,archs-पूर्णांकc  |
	 *        ---------------------
	 *                  |
	 *        ----------------------
	 *        | snps,archs-idu-पूर्णांकc |
	 *        ----------------------
	 *         |   |     |   |    |
	 *         | [eth] [USB]    [... other peripherals]
	 *         |
	 * -------------------
	 * | snps,dw-apb-पूर्णांकc |
	 * -------------------
	 *  |      |   |   |
	 * [Bt] [HAPS]   [... other peripherals]
	 *
	 * Current implementation of "irq-dw-apb-ictl" driver करोesn't work well
	 * with stacked INTCs. In particular problem happens अगर its master INTC
	 * not yet instantiated. See discussion here -
	 * https://lkml.org/lkml/2015/3/4/755
	 *
	 * So setup the first gpio block as a passive pass thru and hide it from
	 * DT hardware topology - connect पूर्णांकc directly to cpu पूर्णांकc
	 * The GPIO "wire" needs to be init nevertheless (here)
	 *
	 * One side adv is that peripheral पूर्णांकerrupt handling aव्योमs one nested
	 * पूर्णांकc ISR hop
	 *
	 * According to HSDK User's Manual [1], "Table 2 Interrupt Mapping"
	 * we have the following GPIO input lines used as sources of पूर्णांकerrupt:
	 * - GPIO[0] - Bluetooth पूर्णांकerrupt of RS9113 module
	 * - GPIO[2] - HAPS पूर्णांकerrupt (on HapsTrak 3 connector)
	 * - GPIO[3] - Audio codec (MAX9880A) पूर्णांकerrupt
	 * - GPIO[8-23] - Available on Arduino and PMOD_x headers
	 * For now there's no use of Arduino and PMOD_x headers in Linux
	 * use-हाल so we only enable lines 0, 2 and 3.
	 *
	 * [1] https://github.com/foss-क्रम-synopsys-dwc-arc-processors/ARC-Development-Systems-Forum/wiki/करोcs/ARC_HSDK_User_Guide.pdf
	 */
#घोषणा GPIO_INTEN              (HSDK_GPIO_INTC + 0x30)
#घोषणा GPIO_INTMASK            (HSDK_GPIO_INTC + 0x34)
#घोषणा GPIO_INTTYPE_LEVEL      (HSDK_GPIO_INTC + 0x38)
#घोषणा GPIO_INT_POLARITY       (HSDK_GPIO_INTC + 0x3c)
#घोषणा GPIO_INT_CONNECTED_MASK	0x0d

	ioग_लिखो32(0xffffffff, (व्योम __iomem *) GPIO_INTMASK);
	ioग_लिखो32(~GPIO_INT_CONNECTED_MASK, (व्योम __iomem *) GPIO_INTMASK);
	ioग_लिखो32(0x00000000, (व्योम __iomem *) GPIO_INTTYPE_LEVEL);
	ioग_लिखो32(0xffffffff, (व्योम __iomem *) GPIO_INT_POLARITY);
	ioग_लिखो32(GPIO_INT_CONNECTED_MASK, (व्योम __iomem *) GPIO_INTEN);
पूर्ण

अटल पूर्णांक __init hsdk_tweak_node_coherency(स्थिर अक्षर *path, bool coherent)
अणु
	व्योम *fdt = initial_boot_params;
	स्थिर व्योम *prop;
	पूर्णांक node, ret;
	bool dt_coh_set;

	node = fdt_path_offset(fdt, path);
	अगर (node < 0)
		जाओ tweak_fail;

	prop = fdt_getprop(fdt, node, "dma-coherent", &ret);
	अगर (!prop && ret != -FDT_ERR_NOTFOUND)
		जाओ tweak_fail;

	dt_coh_set = ret != -FDT_ERR_NOTFOUND;
	ret = 0;

	/* need to हटाओ "dma-coherent" property */
	अगर (dt_coh_set && !coherent)
		ret = fdt_delprop(fdt, node, "dma-coherent");

	/* need to set "dma-coherent" property */
	अगर (!dt_coh_set && coherent)
		ret = fdt_setprop(fdt, node, "dma-coherent", शून्य, 0);

	अगर (ret < 0)
		जाओ tweak_fail;

	वापस 0;

tweak_fail:
	pr_err("failed to tweak %s to %scoherent\n", path, coherent ? "" : "non");
	वापस -EFAULT;
पूर्ण

क्रमागत hsdk_axi_masters अणु
	M_HS_CORE = 0,
	M_HS_RTT,
	M_AXI_TUN,
	M_HDMI_VIDEO,
	M_HDMI_AUDIO,
	M_USB_HOST,
	M_ETHERNET,
	M_SDIO,
	M_GPU,
	M_DMAC_0,
	M_DMAC_1,
	M_DVFS
पूर्ण;

#घोषणा UPDATE_VAL	1

/*
 * This is modअगरied configuration of AXI bridge. Default settings
 * are specअगरied in "Table 111 CREG Address Decoder register reset values".
 *
 * AXI_M_m_SLVअणु0|1पूर्ण - Slave Select रेजिस्टर क्रम master 'm'.
 * Possible slaves are:
 *  - 0  => no slave selected
 *  - 1  => DDR controller port #1
 *  - 2  => SRAM controller
 *  - 3  => AXI tunnel
 *  - 4  => EBI controller
 *  - 5  => ROM controller
 *  - 6  => AXI2APB bridge
 *  - 7  => DDR controller port #2
 *  - 8  => DDR controller port #3
 *  - 9  => HS38x4 IOC
 *  - 10 => HS38x4 DMI
 * AXI_M_m_OFFSETअणु0|1पूर्ण - Addr Offset रेजिस्टर क्रम master 'm'
 *
 * Please पढ़ो ARC HS Development IC Specअगरication, section 17.2 क्रम more
 * inक्रमmation about apertures configuration.
 *
 * m	master		AXI_M_m_SLV0	AXI_M_m_SLV1	AXI_M_m_OFFSET0	AXI_M_m_OFFSET1
 * 0	HS (CBU)	0x11111111	0x63111111	0xFEDCBA98	0x0E543210
 * 1	HS (RTT)	0x77777777	0x77777777	0xFEDCBA98	0x76543210
 * 2	AXI Tunnel	0x88888888	0x88888888	0xFEDCBA98	0x76543210
 * 3	HDMI-VIDEO	0x77777777	0x77777777	0xFEDCBA98	0x76543210
 * 4	HDMI-ADUIO	0x77777777	0x77777777	0xFEDCBA98	0x76543210
 * 5	USB-HOST	0x77777777	0x77999999	0xFEDCBA98	0x76DCBA98
 * 6	ETHERNET	0x77777777	0x77999999	0xFEDCBA98	0x76DCBA98
 * 7	SDIO		0x77777777	0x77999999	0xFEDCBA98	0x76DCBA98
 * 8	GPU		0x77777777	0x77777777	0xFEDCBA98	0x76543210
 * 9	DMAC (port #1)	0x77777777	0x77777777	0xFEDCBA98	0x76543210
 * 10	DMAC (port #2)	0x77777777	0x77777777	0xFEDCBA98	0x76543210
 * 11	DVFS		0x00000000	0x60000000	0x00000000	0x00000000
 */

#घोषणा CREG_AXI_M_SLV0(m)  ((व्योम __iomem *)(CREG_BASE + 0x20 * (m)))
#घोषणा CREG_AXI_M_SLV1(m)  ((व्योम __iomem *)(CREG_BASE + 0x20 * (m) + 0x04))
#घोषणा CREG_AXI_M_OFT0(m)  ((व्योम __iomem *)(CREG_BASE + 0x20 * (m) + 0x08))
#घोषणा CREG_AXI_M_OFT1(m)  ((व्योम __iomem *)(CREG_BASE + 0x20 * (m) + 0x0C))
#घोषणा CREG_AXI_M_UPDT(m)  ((व्योम __iomem *)(CREG_BASE + 0x20 * (m) + 0x14))

#घोषणा CREG_AXI_M_HS_CORE_BOOT	((व्योम __iomem *)(CREG_BASE + 0x010))

#घोषणा CREG_PAE		((व्योम __iomem *)(CREG_BASE + 0x180))
#घोषणा CREG_PAE_UPDT		((व्योम __iomem *)(CREG_BASE + 0x194))

अटल व्योम __init hsdk_init_memory_bridge_axi_dmac(व्योम)
अणु
	bool coherent = !!arc_hsdk_axi_dmac_coherent;
	u32 axi_m_slv1, axi_m_oft1;

	/*
	 * Don't tweak memory bridge configuration अगर we failed to tweak DTB
	 * as we will end up in a inconsistent state.
	 */
	अगर (hsdk_tweak_node_coherency("/soc/dmac@80000", coherent))
		वापस;

	अगर (coherent) अणु
		axi_m_slv1 = 0x77999999;
		axi_m_oft1 = 0x76DCBA98;
	पूर्ण अन्यथा अणु
		axi_m_slv1 = 0x77777777;
		axi_m_oft1 = 0x76543210;
	पूर्ण

	ग_लिखोl(0x77777777, CREG_AXI_M_SLV0(M_DMAC_0));
	ग_लिखोl(0xFEDCBA98, CREG_AXI_M_OFT0(M_DMAC_0));
	ग_लिखोl(axi_m_slv1, CREG_AXI_M_SLV1(M_DMAC_0));
	ग_लिखोl(axi_m_oft1, CREG_AXI_M_OFT1(M_DMAC_0));
	ग_लिखोl(UPDATE_VAL, CREG_AXI_M_UPDT(M_DMAC_0));

	ग_लिखोl(0x77777777, CREG_AXI_M_SLV0(M_DMAC_1));
	ग_लिखोl(0xFEDCBA98, CREG_AXI_M_OFT0(M_DMAC_1));
	ग_लिखोl(axi_m_slv1, CREG_AXI_M_SLV1(M_DMAC_1));
	ग_लिखोl(axi_m_oft1, CREG_AXI_M_OFT1(M_DMAC_1));
	ग_लिखोl(UPDATE_VAL, CREG_AXI_M_UPDT(M_DMAC_1));
पूर्ण

अटल व्योम __init hsdk_init_memory_bridge(व्योम)
अणु
	u32 reg;

	/*
	 * M_HS_CORE has one unique रेजिस्टर - BOOT.
	 * We need to clean boot mirror (BOOT[1:0]) bits in them to aव्योम first
	 * aperture to be masked by 'boot mirror'.
	 */
	reg = पढ़ोl(CREG_AXI_M_HS_CORE_BOOT) & (~0x3);
	ग_लिखोl(reg, CREG_AXI_M_HS_CORE_BOOT);
	ग_लिखोl(0x11111111, CREG_AXI_M_SLV0(M_HS_CORE));
	ग_लिखोl(0x63111111, CREG_AXI_M_SLV1(M_HS_CORE));
	ग_लिखोl(0xFEDCBA98, CREG_AXI_M_OFT0(M_HS_CORE));
	ग_लिखोl(0x0E543210, CREG_AXI_M_OFT1(M_HS_CORE));
	ग_लिखोl(UPDATE_VAL, CREG_AXI_M_UPDT(M_HS_CORE));

	ग_लिखोl(0x77777777, CREG_AXI_M_SLV0(M_HS_RTT));
	ग_लिखोl(0x77777777, CREG_AXI_M_SLV1(M_HS_RTT));
	ग_लिखोl(0xFEDCBA98, CREG_AXI_M_OFT0(M_HS_RTT));
	ग_लिखोl(0x76543210, CREG_AXI_M_OFT1(M_HS_RTT));
	ग_लिखोl(UPDATE_VAL, CREG_AXI_M_UPDT(M_HS_RTT));

	ग_लिखोl(0x88888888, CREG_AXI_M_SLV0(M_AXI_TUN));
	ग_लिखोl(0x88888888, CREG_AXI_M_SLV1(M_AXI_TUN));
	ग_लिखोl(0xFEDCBA98, CREG_AXI_M_OFT0(M_AXI_TUN));
	ग_लिखोl(0x76543210, CREG_AXI_M_OFT1(M_AXI_TUN));
	ग_लिखोl(UPDATE_VAL, CREG_AXI_M_UPDT(M_AXI_TUN));

	ग_लिखोl(0x77777777, CREG_AXI_M_SLV0(M_HDMI_VIDEO));
	ग_लिखोl(0x77777777, CREG_AXI_M_SLV1(M_HDMI_VIDEO));
	ग_लिखोl(0xFEDCBA98, CREG_AXI_M_OFT0(M_HDMI_VIDEO));
	ग_लिखोl(0x76543210, CREG_AXI_M_OFT1(M_HDMI_VIDEO));
	ग_लिखोl(UPDATE_VAL, CREG_AXI_M_UPDT(M_HDMI_VIDEO));

	ग_लिखोl(0x77777777, CREG_AXI_M_SLV0(M_HDMI_AUDIO));
	ग_लिखोl(0x77777777, CREG_AXI_M_SLV1(M_HDMI_AUDIO));
	ग_लिखोl(0xFEDCBA98, CREG_AXI_M_OFT0(M_HDMI_AUDIO));
	ग_लिखोl(0x76543210, CREG_AXI_M_OFT1(M_HDMI_AUDIO));
	ग_लिखोl(UPDATE_VAL, CREG_AXI_M_UPDT(M_HDMI_AUDIO));

	ग_लिखोl(0x77777777, CREG_AXI_M_SLV0(M_USB_HOST));
	ग_लिखोl(0x77999999, CREG_AXI_M_SLV1(M_USB_HOST));
	ग_लिखोl(0xFEDCBA98, CREG_AXI_M_OFT0(M_USB_HOST));
	ग_लिखोl(0x76DCBA98, CREG_AXI_M_OFT1(M_USB_HOST));
	ग_लिखोl(UPDATE_VAL, CREG_AXI_M_UPDT(M_USB_HOST));

	ग_लिखोl(0x77777777, CREG_AXI_M_SLV0(M_ETHERNET));
	ग_लिखोl(0x77999999, CREG_AXI_M_SLV1(M_ETHERNET));
	ग_लिखोl(0xFEDCBA98, CREG_AXI_M_OFT0(M_ETHERNET));
	ग_लिखोl(0x76DCBA98, CREG_AXI_M_OFT1(M_ETHERNET));
	ग_लिखोl(UPDATE_VAL, CREG_AXI_M_UPDT(M_ETHERNET));

	ग_लिखोl(0x77777777, CREG_AXI_M_SLV0(M_SDIO));
	ग_लिखोl(0x77999999, CREG_AXI_M_SLV1(M_SDIO));
	ग_लिखोl(0xFEDCBA98, CREG_AXI_M_OFT0(M_SDIO));
	ग_लिखोl(0x76DCBA98, CREG_AXI_M_OFT1(M_SDIO));
	ग_लिखोl(UPDATE_VAL, CREG_AXI_M_UPDT(M_SDIO));

	ग_लिखोl(0x77777777, CREG_AXI_M_SLV0(M_GPU));
	ग_लिखोl(0x77777777, CREG_AXI_M_SLV1(M_GPU));
	ग_लिखोl(0xFEDCBA98, CREG_AXI_M_OFT0(M_GPU));
	ग_लिखोl(0x76543210, CREG_AXI_M_OFT1(M_GPU));
	ग_लिखोl(UPDATE_VAL, CREG_AXI_M_UPDT(M_GPU));

	ग_लिखोl(0x00000000, CREG_AXI_M_SLV0(M_DVFS));
	ग_लिखोl(0x60000000, CREG_AXI_M_SLV1(M_DVFS));
	ग_लिखोl(0x00000000, CREG_AXI_M_OFT0(M_DVFS));
	ग_लिखोl(0x00000000, CREG_AXI_M_OFT1(M_DVFS));
	ग_लिखोl(UPDATE_VAL, CREG_AXI_M_UPDT(M_DVFS));

	hsdk_init_memory_bridge_axi_dmac();

	/*
	 * PAE remapping क्रम DMA clients करोes not work due to an RTL bug, so
	 * CREG_PAE रेजिस्टर must be programmed to all zeroes, otherwise it
	 * will cause problems with DMA to/from peripherals even अगर PAE40 is
	 * not used.
	 */
	ग_लिखोl(0x00000000, CREG_PAE);
	ग_लिखोl(UPDATE_VAL, CREG_PAE_UPDT);
पूर्ण

अटल व्योम __init hsdk_init_early(व्योम)
अणु
	hsdk_init_memory_bridge();

	/*
	 * Switch SDIO बाह्यal ciu घड़ी भागider from शेष भाग-by-8 to
	 * minimum possible भाग-by-2.
	 */
	ioग_लिखो32(SDIO_UHS_REG_EXT_DIV_2, (व्योम __iomem *) SDIO_UHS_REG_EXT);

	hsdk_enable_gpio_पूर्णांकc_wire();
पूर्ण

अटल स्थिर अक्षर *hsdk_compat[] __initस्थिर = अणु
	"snps,hsdk",
	शून्य,
पूर्ण;

MACHINE_START(SIMULATION, "hsdk")
	.dt_compat	= hsdk_compat,
	.init_early     = hsdk_init_early,
MACHINE_END
