<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2004-2017 Cavium, Inc.
 * Copyright (C) 2008 Wind River Systems
 */

#समावेश <linux/etherdevice.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/of_fdt.h>
#समावेश <linux/libfdt.h>

#समावेश <यंत्र/octeon/octeon.h>
#समावेश <यंत्र/octeon/cvmx-helper-board.h>

#अगर_घोषित CONFIG_USB
#समावेश <linux/usb/ehci_def.h>
#समावेश <linux/usb/ehci_pdriver.h>
#समावेश <linux/usb/ohci_pdriver.h>
#समावेश <यंत्र/octeon/cvmx-uctlx-defs.h>

#घोषणा CVMX_UAHCX_EHCI_USBCMD	(CVMX_ADD_IO_SEG(0x00016F0000000010ull))
#घोषणा CVMX_UAHCX_OHCI_USBCMD	(CVMX_ADD_IO_SEG(0x00016F0000000408ull))

अटल DEFINE_MUTEX(octeon2_usb_घड़ीs_mutex);

अटल पूर्णांक octeon2_usb_घड़ी_start_cnt;

अटल पूर्णांक __init octeon2_usb_reset(व्योम)
अणु
	जोड़ cvmx_uctlx_clk_rst_ctl clk_rst_ctl;
	u32 ucmd;

	अगर (!OCTEON_IS_OCTEON2())
		वापस 0;

	clk_rst_ctl.u64 = cvmx_पढ़ो_csr(CVMX_UCTLX_CLK_RST_CTL(0));
	अगर (clk_rst_ctl.s.hrst) अणु
		ucmd = cvmx_पढ़ो64_uपूर्णांक32(CVMX_UAHCX_EHCI_USBCMD);
		ucmd &= ~CMD_RUN;
		cvmx_ग_लिखो64_uपूर्णांक32(CVMX_UAHCX_EHCI_USBCMD, ucmd);
		mdelay(2);
		ucmd |= CMD_RESET;
		cvmx_ग_लिखो64_uपूर्णांक32(CVMX_UAHCX_EHCI_USBCMD, ucmd);
		ucmd = cvmx_पढ़ो64_uपूर्णांक32(CVMX_UAHCX_OHCI_USBCMD);
		ucmd |= CMD_RUN;
		cvmx_ग_लिखो64_uपूर्णांक32(CVMX_UAHCX_OHCI_USBCMD, ucmd);
	पूर्ण

	वापस 0;
पूर्ण
arch_initcall(octeon2_usb_reset);

अटल व्योम octeon2_usb_घड़ीs_start(काष्ठा device *dev)
अणु
	u64 भाग;
	जोड़ cvmx_uctlx_अगर_ena अगर_ena;
	जोड़ cvmx_uctlx_clk_rst_ctl clk_rst_ctl;
	जोड़ cvmx_uctlx_uphy_portx_ctl_status port_ctl_status;
	पूर्णांक i;
	अचिन्हित दीर्घ io_clk_64_to_ns;
	u32 घड़ी_rate = 12000000;
	bool is_crystal_घड़ी = false;


	mutex_lock(&octeon2_usb_घड़ीs_mutex);

	octeon2_usb_घड़ी_start_cnt++;
	अगर (octeon2_usb_घड़ी_start_cnt != 1)
		जाओ निकास;

	io_clk_64_to_ns = 64000000000ull / octeon_get_io_घड़ी_rate();

	अगर (dev->of_node) अणु
		काष्ठा device_node *uctl_node;
		स्थिर अक्षर *घड़ी_प्रकारype;

		uctl_node = of_get_parent(dev->of_node);
		अगर (!uctl_node) अणु
			dev_err(dev, "No UCTL device node\n");
			जाओ निकास;
		पूर्ण
		i = of_property_पढ़ो_u32(uctl_node,
					 "refclk-frequency", &घड़ी_rate);
		अगर (i) अणु
			dev_err(dev, "No UCTL \"refclk-frequency\"\n");
			जाओ निकास;
		पूर्ण
		i = of_property_पढ़ो_string(uctl_node,
					    "refclk-type", &घड़ी_प्रकारype);

		अगर (!i && म_भेद("crystal", घड़ी_प्रकारype) == 0)
			is_crystal_घड़ी = true;
	पूर्ण

	/*
	 * Step 1: Wait क्रम voltages stable.  That surely happened
	 * beक्रमe starting the kernel.
	 *
	 * Step 2: Enable  SCLK of UCTL by writing UCTL0_IF_ENA[EN] = 1
	 */
	अगर_ena.u64 = 0;
	अगर_ena.s.en = 1;
	cvmx_ग_लिखो_csr(CVMX_UCTLX_IF_ENA(0), अगर_ena.u64);

	क्रम (i = 0; i <= 1; i++) अणु
		port_ctl_status.u64 =
			cvmx_पढ़ो_csr(CVMX_UCTLX_UPHY_PORTX_CTL_STATUS(i, 0));
		/* Set txvreftune to 15 to obtain compliant 'eye' diagram. */
		port_ctl_status.s.txvreftune = 15;
		port_ctl_status.s.txrisetune = 1;
		port_ctl_status.s.txpreemphasistune = 1;
		cvmx_ग_लिखो_csr(CVMX_UCTLX_UPHY_PORTX_CTL_STATUS(i, 0),
			       port_ctl_status.u64);
	पूर्ण

	/* Step 3: Configure the reference घड़ी, PHY, and HCLK */
	clk_rst_ctl.u64 = cvmx_पढ़ो_csr(CVMX_UCTLX_CLK_RST_CTL(0));

	/*
	 * If the UCTL looks like it has alपढ़ोy been started, skip
	 * the initialization, otherwise bus errors are obtained.
	 */
	अगर (clk_rst_ctl.s.hrst)
		जाओ end_घड़ी;
	/* 3a */
	clk_rst_ctl.s.p_por = 1;
	clk_rst_ctl.s.hrst = 0;
	clk_rst_ctl.s.p_prst = 0;
	clk_rst_ctl.s.h_clkभाग_rst = 0;
	clk_rst_ctl.s.o_clkभाग_rst = 0;
	clk_rst_ctl.s.h_clkभाग_en = 0;
	clk_rst_ctl.s.o_clkभाग_en = 0;
	cvmx_ग_लिखो_csr(CVMX_UCTLX_CLK_RST_CTL(0), clk_rst_ctl.u64);

	/* 3b */
	clk_rst_ctl.s.p_refclk_sel = is_crystal_घड़ी ? 0 : 1;
	चयन (घड़ी_rate) अणु
	शेष:
		pr_err("Invalid UCTL clock rate of %u, using 12000000 instead\n",
			घड़ी_rate);
		fallthrough;
	हाल 12000000:
		clk_rst_ctl.s.p_refclk_भाग = 0;
		अवरोध;
	हाल 24000000:
		clk_rst_ctl.s.p_refclk_भाग = 1;
		अवरोध;
	हाल 48000000:
		clk_rst_ctl.s.p_refclk_भाग = 2;
		अवरोध;
	पूर्ण
	cvmx_ग_लिखो_csr(CVMX_UCTLX_CLK_RST_CTL(0), clk_rst_ctl.u64);

	/* 3c */
	भाग = octeon_get_io_घड़ी_rate() / 130000000ull;

	चयन (भाग) अणु
	हाल 0:
		भाग = 1;
		अवरोध;
	हाल 1:
	हाल 2:
	हाल 3:
	हाल 4:
		अवरोध;
	हाल 5:
		भाग = 4;
		अवरोध;
	हाल 6:
	हाल 7:
		भाग = 6;
		अवरोध;
	हाल 8:
	हाल 9:
	हाल 10:
	हाल 11:
		भाग = 8;
		अवरोध;
	शेष:
		भाग = 12;
		अवरोध;
	पूर्ण
	clk_rst_ctl.s.h_भाग = भाग;
	cvmx_ग_लिखो_csr(CVMX_UCTLX_CLK_RST_CTL(0), clk_rst_ctl.u64);
	/* Read it back, */
	clk_rst_ctl.u64 = cvmx_पढ़ो_csr(CVMX_UCTLX_CLK_RST_CTL(0));
	clk_rst_ctl.s.h_clkभाग_en = 1;
	cvmx_ग_लिखो_csr(CVMX_UCTLX_CLK_RST_CTL(0), clk_rst_ctl.u64);
	/* 3d */
	clk_rst_ctl.s.h_clkभाग_rst = 1;
	cvmx_ग_लिखो_csr(CVMX_UCTLX_CLK_RST_CTL(0), clk_rst_ctl.u64);

	/* 3e: delay 64 io घड़ीs */
	ndelay(io_clk_64_to_ns);

	/*
	 * Step 4: Program the घातer-on reset field in the UCTL
	 * घड़ी-reset-control रेजिस्टर.
	 */
	clk_rst_ctl.s.p_por = 0;
	cvmx_ग_लिखो_csr(CVMX_UCTLX_CLK_RST_CTL(0), clk_rst_ctl.u64);

	/* Step 5:    Wait 3 ms क्रम the PHY घड़ी to start. */
	mdelay(3);

	/* Steps 6..9 क्रम ATE only, are skipped. */

	/* Step 10: Configure the OHCI_CLK48 and OHCI_CLK12 घड़ीs. */
	/* 10a */
	clk_rst_ctl.s.o_clkभाग_rst = 1;
	cvmx_ग_लिखो_csr(CVMX_UCTLX_CLK_RST_CTL(0), clk_rst_ctl.u64);

	/* 10b */
	clk_rst_ctl.s.o_clkभाग_en = 1;
	cvmx_ग_लिखो_csr(CVMX_UCTLX_CLK_RST_CTL(0), clk_rst_ctl.u64);

	/* 10c */
	ndelay(io_clk_64_to_ns);

	/*
	 * Step 11: Program the PHY reset field:
	 * UCTL0_CLK_RST_CTL[P_PRST] = 1
	 */
	clk_rst_ctl.s.p_prst = 1;
	cvmx_ग_लिखो_csr(CVMX_UCTLX_CLK_RST_CTL(0), clk_rst_ctl.u64);

	/* Step 11b */
	udelay(1);

	/* Step 11c */
	clk_rst_ctl.s.p_prst = 0;
	cvmx_ग_लिखो_csr(CVMX_UCTLX_CLK_RST_CTL(0), clk_rst_ctl.u64);

	/* Step 11d */
	mdelay(1);

	/* Step 11e */
	clk_rst_ctl.s.p_prst = 1;
	cvmx_ग_लिखो_csr(CVMX_UCTLX_CLK_RST_CTL(0), clk_rst_ctl.u64);

	/* Step 12: Wait 1 uS. */
	udelay(1);

	/* Step 13: Program the HRESET_N field: UCTL0_CLK_RST_CTL[HRST] = 1 */
	clk_rst_ctl.s.hrst = 1;
	cvmx_ग_लिखो_csr(CVMX_UCTLX_CLK_RST_CTL(0), clk_rst_ctl.u64);

end_घड़ी:
	/* Set uSOF cycle period to 60,000 bits. */
	cvmx_ग_लिखो_csr(CVMX_UCTLX_EHCI_FLA(0), 0x20ull);

निकास:
	mutex_unlock(&octeon2_usb_घड़ीs_mutex);
पूर्ण

अटल व्योम octeon2_usb_घड़ीs_stop(व्योम)
अणु
	mutex_lock(&octeon2_usb_घड़ीs_mutex);
	octeon2_usb_घड़ी_start_cnt--;
	mutex_unlock(&octeon2_usb_घड़ीs_mutex);
पूर्ण

अटल पूर्णांक octeon_ehci_घातer_on(काष्ठा platक्रमm_device *pdev)
अणु
	octeon2_usb_घड़ीs_start(&pdev->dev);
	वापस 0;
पूर्ण

अटल व्योम octeon_ehci_घातer_off(काष्ठा platक्रमm_device *pdev)
अणु
	octeon2_usb_घड़ीs_stop();
पूर्ण

अटल काष्ठा usb_ehci_pdata octeon_ehci_pdata = अणु
	/* Octeon EHCI matches CPU endianness. */
#अगर_घोषित __BIG_ENDIAN
	.big_endian_mmio	= 1,
#पूर्ण_अगर
	/*
	 * We can DMA from anywhere. But the descriptors must be in
	 * the lower 4GB.
	 */
	.dma_mask_64	= 0,
	.घातer_on	= octeon_ehci_घातer_on,
	.घातer_off	= octeon_ehci_घातer_off,
पूर्ण;

अटल व्योम __init octeon_ehci_hw_start(काष्ठा device *dev)
अणु
	जोड़ cvmx_uctlx_ehci_ctl ehci_ctl;

	octeon2_usb_घड़ीs_start(dev);

	ehci_ctl.u64 = cvmx_पढ़ो_csr(CVMX_UCTLX_EHCI_CTL(0));
	/* Use 64-bit addressing. */
	ehci_ctl.s.ehci_64b_addr_en = 1;
	ehci_ctl.s.l2c_addr_msb = 0;
#अगर_घोषित __BIG_ENDIAN
	ehci_ctl.s.l2c_buff_emod = 1; /* Byte swapped. */
	ehci_ctl.s.l2c_desc_emod = 1; /* Byte swapped. */
#अन्यथा
	ehci_ctl.s.l2c_buff_emod = 0; /* not swapped. */
	ehci_ctl.s.l2c_desc_emod = 0; /* not swapped. */
	ehci_ctl.s.inv_reg_a2 = 1;
#पूर्ण_अगर
	cvmx_ग_लिखो_csr(CVMX_UCTLX_EHCI_CTL(0), ehci_ctl.u64);

	octeon2_usb_घड़ीs_stop();
पूर्ण

अटल पूर्णांक __init octeon_ehci_device_init(व्योम)
अणु
	काष्ठा platक्रमm_device *pd;
	काष्ठा device_node *ehci_node;
	पूर्णांक ret = 0;

	ehci_node = of_find_node_by_name(शून्य, "ehci");
	अगर (!ehci_node)
		वापस 0;

	pd = of_find_device_by_node(ehci_node);
	of_node_put(ehci_node);
	अगर (!pd)
		वापस 0;

	pd->dev.platक्रमm_data = &octeon_ehci_pdata;
	octeon_ehci_hw_start(&pd->dev);

	वापस ret;
पूर्ण
device_initcall(octeon_ehci_device_init);

अटल पूर्णांक octeon_ohci_घातer_on(काष्ठा platक्रमm_device *pdev)
अणु
	octeon2_usb_घड़ीs_start(&pdev->dev);
	वापस 0;
पूर्ण

अटल व्योम octeon_ohci_घातer_off(काष्ठा platक्रमm_device *pdev)
अणु
	octeon2_usb_घड़ीs_stop();
पूर्ण

अटल काष्ठा usb_ohci_pdata octeon_ohci_pdata = अणु
	/* Octeon OHCI matches CPU endianness. */
#अगर_घोषित __BIG_ENDIAN
	.big_endian_mmio	= 1,
#पूर्ण_अगर
	.घातer_on	= octeon_ohci_घातer_on,
	.घातer_off	= octeon_ohci_घातer_off,
पूर्ण;

अटल व्योम __init octeon_ohci_hw_start(काष्ठा device *dev)
अणु
	जोड़ cvmx_uctlx_ohci_ctl ohci_ctl;

	octeon2_usb_घड़ीs_start(dev);

	ohci_ctl.u64 = cvmx_पढ़ो_csr(CVMX_UCTLX_OHCI_CTL(0));
	ohci_ctl.s.l2c_addr_msb = 0;
#अगर_घोषित __BIG_ENDIAN
	ohci_ctl.s.l2c_buff_emod = 1; /* Byte swapped. */
	ohci_ctl.s.l2c_desc_emod = 1; /* Byte swapped. */
#अन्यथा
	ohci_ctl.s.l2c_buff_emod = 0; /* not swapped. */
	ohci_ctl.s.l2c_desc_emod = 0; /* not swapped. */
	ohci_ctl.s.inv_reg_a2 = 1;
#पूर्ण_अगर
	cvmx_ग_लिखो_csr(CVMX_UCTLX_OHCI_CTL(0), ohci_ctl.u64);

	octeon2_usb_घड़ीs_stop();
पूर्ण

अटल पूर्णांक __init octeon_ohci_device_init(व्योम)
अणु
	काष्ठा platक्रमm_device *pd;
	काष्ठा device_node *ohci_node;
	पूर्णांक ret = 0;

	ohci_node = of_find_node_by_name(शून्य, "ohci");
	अगर (!ohci_node)
		वापस 0;

	pd = of_find_device_by_node(ohci_node);
	of_node_put(ohci_node);
	अगर (!pd)
		वापस 0;

	pd->dev.platक्रमm_data = &octeon_ohci_pdata;
	octeon_ohci_hw_start(&pd->dev);

	वापस ret;
पूर्ण
device_initcall(octeon_ohci_device_init);

#पूर्ण_अगर /* CONFIG_USB */

/* Octeon Ranकरोm Number Generator.  */
अटल पूर्णांक __init octeon_rng_device_init(व्योम)
अणु
	काष्ठा platक्रमm_device *pd;
	पूर्णांक ret = 0;

	काष्ठा resource rng_resources[] = अणु
		अणु
			.flags	= IORESOURCE_MEM,
			.start	= XKPHYS_TO_PHYS(CVMX_RNM_CTL_STATUS),
			.end	= XKPHYS_TO_PHYS(CVMX_RNM_CTL_STATUS) + 0xf
		पूर्ण, अणु
			.flags	= IORESOURCE_MEM,
			.start	= cvmx_build_io_address(8, 0),
			.end	= cvmx_build_io_address(8, 0) + 0x7
		पूर्ण
	पूर्ण;

	pd = platक्रमm_device_alloc("octeon_rng", -1);
	अगर (!pd) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	ret = platक्रमm_device_add_resources(pd, rng_resources,
					    ARRAY_SIZE(rng_resources));
	अगर (ret)
		जाओ fail;

	ret = platक्रमm_device_add(pd);
	अगर (ret)
		जाओ fail;

	वापस ret;
fail:
	platक्रमm_device_put(pd);

out:
	वापस ret;
पूर्ण
device_initcall(octeon_rng_device_init);

अटल स्थिर काष्ठा of_device_id octeon_ids[] __initस्थिर = अणु
	अणु .compatible = "simple-bus", पूर्ण,
	अणु .compatible = "cavium,octeon-6335-uctl", पूर्ण,
	अणु .compatible = "cavium,octeon-5750-usbn", पूर्ण,
	अणु .compatible = "cavium,octeon-3860-bootbus", पूर्ण,
	अणु .compatible = "cavium,mdio-mux", पूर्ण,
	अणु .compatible = "gpio-leds", पूर्ण,
	अणु .compatible = "cavium,octeon-7130-usb-uctl", पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल bool __init octeon_has_88e1145(व्योम)
अणु
	वापस !OCTEON_IS_MODEL(OCTEON_CN52XX) &&
	       !OCTEON_IS_MODEL(OCTEON_CN6XXX) &&
	       !OCTEON_IS_MODEL(OCTEON_CN56XX);
पूर्ण

अटल bool __init octeon_has_fixed_link(पूर्णांक ipd_port)
अणु
	चयन (cvmx_sysinfo_get()->board_type) अणु
	हाल CVMX_BOARD_TYPE_CN3005_EVB_HS5:
	हाल CVMX_BOARD_TYPE_CN3010_EVB_HS5:
	हाल CVMX_BOARD_TYPE_CN3020_EVB_HS5:
	हाल CVMX_BOARD_TYPE_CUST_NB5:
	हाल CVMX_BOARD_TYPE_EBH3100:
		/* Port 1 on these boards is always gigabit. */
		वापस ipd_port == 1;
	हाल CVMX_BOARD_TYPE_BBGW_REF:
		/* Ports 0 and 1 connect to the चयन. */
		वापस ipd_port == 0 || ipd_port == 1;
	पूर्ण
	वापस false;
पूर्ण

अटल व्योम __init octeon_fdt_set_phy(पूर्णांक eth, पूर्णांक phy_addr)
अणु
	स्थिर __be32 *phy_handle;
	स्थिर __be32 *alt_phy_handle;
	स्थिर __be32 *reg;
	u32 phandle;
	पूर्णांक phy;
	पूर्णांक alt_phy;
	स्थिर अक्षर *p;
	पूर्णांक current_len;
	अक्षर new_name[20];

	phy_handle = fdt_getprop(initial_boot_params, eth, "phy-handle", शून्य);
	अगर (!phy_handle)
		वापस;

	phandle = be32_to_cpup(phy_handle);
	phy = fdt_node_offset_by_phandle(initial_boot_params, phandle);

	alt_phy_handle = fdt_getprop(initial_boot_params, eth, "cavium,alt-phy-handle", शून्य);
	अगर (alt_phy_handle) अणु
		u32 alt_phandle = be32_to_cpup(alt_phy_handle);

		alt_phy = fdt_node_offset_by_phandle(initial_boot_params, alt_phandle);
	पूर्ण अन्यथा अणु
		alt_phy = -1;
	पूर्ण

	अगर (phy_addr < 0 || phy < 0) अणु
		/* Delete the PHY things */
		fdt_nop_property(initial_boot_params, eth, "phy-handle");
		/* This one may fail */
		fdt_nop_property(initial_boot_params, eth, "cavium,alt-phy-handle");
		अगर (phy >= 0)
			fdt_nop_node(initial_boot_params, phy);
		अगर (alt_phy >= 0)
			fdt_nop_node(initial_boot_params, alt_phy);
		वापस;
	पूर्ण

	अगर (phy_addr >= 256 && alt_phy > 0) अणु
		स्थिर काष्ठा fdt_property *phy_prop;
		काष्ठा fdt_property *alt_prop;
		fdt32_t phy_handle_name;

		/* Use the alt phy node instead.*/
		phy_prop = fdt_get_property(initial_boot_params, eth, "phy-handle", शून्य);
		phy_handle_name = phy_prop->nameoff;
		fdt_nop_node(initial_boot_params, phy);
		fdt_nop_property(initial_boot_params, eth, "phy-handle");
		alt_prop = fdt_get_property_w(initial_boot_params, eth, "cavium,alt-phy-handle", शून्य);
		alt_prop->nameoff = phy_handle_name;
		phy = alt_phy;
	पूर्ण

	phy_addr &= 0xff;

	अगर (octeon_has_88e1145()) अणु
		fdt_nop_property(initial_boot_params, phy, "marvell,reg-init");
		स_रखो(new_name, 0, माप(new_name));
		म_नकल(new_name, "marvell,88e1145");
		p = fdt_getprop(initial_boot_params, phy, "compatible",
				&current_len);
		अगर (p && current_len >= म_माप(new_name))
			fdt_setprop_inplace(initial_boot_params, phy,
					"compatible", new_name, current_len);
	पूर्ण

	reg = fdt_getprop(initial_boot_params, phy, "reg", शून्य);
	अगर (phy_addr == be32_to_cpup(reg))
		वापस;

	fdt_setprop_inplace_cell(initial_boot_params, phy, "reg", phy_addr);

	snम_लिखो(new_name, माप(new_name), "ethernet-phy@%x", phy_addr);

	p = fdt_get_name(initial_boot_params, phy, &current_len);
	अगर (p && current_len == म_माप(new_name))
		fdt_set_name(initial_boot_params, phy, new_name);
	अन्यथा
		pr_err("Error: could not rename ethernet phy: <%s>", p);
पूर्ण

अटल व्योम __init octeon_fdt_set_mac_addr(पूर्णांक n, u64 *pmac)
अणु
	स्थिर u8 *old_mac;
	पूर्णांक old_len;
	u8 new_mac[6];
	u64 mac = *pmac;
	पूर्णांक r;

	old_mac = fdt_getprop(initial_boot_params, n, "local-mac-address",
			      &old_len);
	अगर (!old_mac || old_len != 6 || is_valid_ether_addr(old_mac))
		वापस;

	new_mac[0] = (mac >> 40) & 0xff;
	new_mac[1] = (mac >> 32) & 0xff;
	new_mac[2] = (mac >> 24) & 0xff;
	new_mac[3] = (mac >> 16) & 0xff;
	new_mac[4] = (mac >> 8) & 0xff;
	new_mac[5] = mac & 0xff;

	r = fdt_setprop_inplace(initial_boot_params, n, "local-mac-address",
				new_mac, माप(new_mac));

	अगर (r) अणु
		pr_err("Setting \"local-mac-address\" failed %d", r);
		वापस;
	पूर्ण
	*pmac = mac + 1;
पूर्ण

अटल व्योम __init octeon_fdt_rm_ethernet(पूर्णांक node)
अणु
	स्थिर __be32 *phy_handle;

	phy_handle = fdt_getprop(initial_boot_params, node, "phy-handle", शून्य);
	अगर (phy_handle) अणु
		u32 ph = be32_to_cpup(phy_handle);
		पूर्णांक p = fdt_node_offset_by_phandle(initial_boot_params, ph);

		अगर (p >= 0)
			fdt_nop_node(initial_boot_params, p);
	पूर्ण
	fdt_nop_node(initial_boot_params, node);
पूर्ण

अटल व्योम __init _octeon_rx_tx_delay(पूर्णांक eth, पूर्णांक rx_delay, पूर्णांक tx_delay)
अणु
	fdt_setprop_inplace_cell(initial_boot_params, eth, "rx-delay",
				 rx_delay);
	fdt_setprop_inplace_cell(initial_boot_params, eth, "tx-delay",
				 tx_delay);
पूर्ण

अटल व्योम __init octeon_rx_tx_delay(पूर्णांक eth, पूर्णांक अगरace, पूर्णांक port)
अणु
	चयन (cvmx_sysinfo_get()->board_type) अणु
	हाल CVMX_BOARD_TYPE_CN3005_EVB_HS5:
		अगर (अगरace == 0) अणु
			अगर (port == 0) अणु
				/*
				 * Boards with gigabit WAN ports need a
				 * dअगरferent setting that is compatible with
				 * 100 Mbit settings
				 */
				_octeon_rx_tx_delay(eth, 0xc, 0x0c);
				वापस;
			पूर्ण अन्यथा अगर (port == 1) अणु
				/* Dअगरferent config क्रम चयन port. */
				_octeon_rx_tx_delay(eth, 0x0, 0x0);
				वापस;
			पूर्ण
		पूर्ण
		अवरोध;
	हाल CVMX_BOARD_TYPE_UBNT_E100:
		अगर (अगरace == 0 && port <= 2) अणु
			_octeon_rx_tx_delay(eth, 0x0, 0x10);
			वापस;
		पूर्ण
		अवरोध;
	पूर्ण
	fdt_nop_property(initial_boot_params, eth, "rx-delay");
	fdt_nop_property(initial_boot_params, eth, "tx-delay");
पूर्ण

अटल व्योम __init octeon_fdt_pip_port(पूर्णांक अगरace, पूर्णांक i, पूर्णांक p, पूर्णांक max)
अणु
	अक्षर name_buffer[20];
	पूर्णांक eth;
	पूर्णांक phy_addr;
	पूर्णांक ipd_port;
	पूर्णांक fixed_link;

	snम_लिखो(name_buffer, माप(name_buffer), "ethernet@%x", p);
	eth = fdt_subnode_offset(initial_boot_params, अगरace, name_buffer);
	अगर (eth < 0)
		वापस;
	अगर (p > max) अणु
		pr_debug("Deleting port %x:%x\n", i, p);
		octeon_fdt_rm_ethernet(eth);
		वापस;
	पूर्ण
	अगर (OCTEON_IS_MODEL(OCTEON_CN68XX))
		ipd_port = (0x100 * i) + (0x10 * p) + 0x800;
	अन्यथा
		ipd_port = 16 * i + p;

	phy_addr = cvmx_helper_board_get_mii_address(ipd_port);
	octeon_fdt_set_phy(eth, phy_addr);

	fixed_link = fdt_subnode_offset(initial_boot_params, eth, "fixed-link");
	अगर (fixed_link < 0)
		WARN_ON(octeon_has_fixed_link(ipd_port));
	अन्यथा अगर (!octeon_has_fixed_link(ipd_port))
		fdt_nop_node(initial_boot_params, fixed_link);
	octeon_rx_tx_delay(eth, i, p);
पूर्ण

अटल व्योम __init octeon_fdt_pip_अगरace(पूर्णांक pip, पूर्णांक idx)
अणु
	अक्षर name_buffer[20];
	पूर्णांक अगरace;
	पूर्णांक p;
	पूर्णांक count = 0;

	snम_लिखो(name_buffer, माप(name_buffer), "interface@%d", idx);
	अगरace = fdt_subnode_offset(initial_boot_params, pip, name_buffer);
	अगर (अगरace < 0)
		वापस;

	अगर (cvmx_helper_पूर्णांकerface_क्रमागतerate(idx) == 0)
		count = cvmx_helper_ports_on_पूर्णांकerface(idx);

	क्रम (p = 0; p < 16; p++)
		octeon_fdt_pip_port(अगरace, idx, p, count - 1);
पूर्ण

व्योम __init octeon_fill_mac_addresses(व्योम)
अणु
	स्थिर अक्षर *alias_prop;
	अक्षर name_buffer[20];
	u64 mac_addr_base;
	पूर्णांक aliases;
	पूर्णांक pip;
	पूर्णांक i;

	aliases = fdt_path_offset(initial_boot_params, "/aliases");
	अगर (aliases < 0)
		वापस;

	mac_addr_base =
		((octeon_bootinfo->mac_addr_base[0] & 0xffull)) << 40 |
		((octeon_bootinfo->mac_addr_base[1] & 0xffull)) << 32 |
		((octeon_bootinfo->mac_addr_base[2] & 0xffull)) << 24 |
		((octeon_bootinfo->mac_addr_base[3] & 0xffull)) << 16 |
		((octeon_bootinfo->mac_addr_base[4] & 0xffull)) << 8 |
		 (octeon_bootinfo->mac_addr_base[5] & 0xffull);

	क्रम (i = 0; i < 2; i++) अणु
		पूर्णांक mgmt;

		snम_लिखो(name_buffer, माप(name_buffer), "mix%d", i);
		alias_prop = fdt_getprop(initial_boot_params, aliases,
					 name_buffer, शून्य);
		अगर (!alias_prop)
			जारी;
		mgmt = fdt_path_offset(initial_boot_params, alias_prop);
		अगर (mgmt < 0)
			जारी;
		octeon_fdt_set_mac_addr(mgmt, &mac_addr_base);
	पूर्ण

	alias_prop = fdt_getprop(initial_boot_params, aliases, "pip", शून्य);
	अगर (!alias_prop)
		वापस;

	pip = fdt_path_offset(initial_boot_params, alias_prop);
	अगर (pip < 0)
		वापस;

	क्रम (i = 0; i <= 4; i++) अणु
		पूर्णांक अगरace;
		पूर्णांक p;

		snम_लिखो(name_buffer, माप(name_buffer), "interface@%d", i);
		अगरace = fdt_subnode_offset(initial_boot_params, pip,
					   name_buffer);
		अगर (अगरace < 0)
			जारी;
		क्रम (p = 0; p < 16; p++) अणु
			पूर्णांक eth;

			snम_लिखो(name_buffer, माप(name_buffer),
				 "ethernet@%x", p);
			eth = fdt_subnode_offset(initial_boot_params, अगरace,
						 name_buffer);
			अगर (eth < 0)
				जारी;
			octeon_fdt_set_mac_addr(eth, &mac_addr_base);
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक __init octeon_prune_device_tree(व्योम)
अणु
	पूर्णांक i, max_port, uart_mask;
	स्थिर अक्षर *pip_path;
	स्थिर अक्षर *alias_prop;
	अक्षर name_buffer[20];
	पूर्णांक aliases;

	अगर (fdt_check_header(initial_boot_params))
		panic("Corrupt Device Tree.");

	WARN(octeon_bootinfo->board_type == CVMX_BOARD_TYPE_CUST_DSR1000N,
	     "Built-in DTB booting is deprecated on %s. Please switch to use appended DTB.",
	     cvmx_board_type_to_string(octeon_bootinfo->board_type));

	aliases = fdt_path_offset(initial_boot_params, "/aliases");
	अगर (aliases < 0) अणु
		pr_err("Error: No /aliases node in device tree.");
		वापस -EINVAL;
	पूर्ण

	अगर (OCTEON_IS_MODEL(OCTEON_CN52XX) || OCTEON_IS_MODEL(OCTEON_CN63XX))
		max_port = 2;
	अन्यथा अगर (OCTEON_IS_MODEL(OCTEON_CN56XX) || OCTEON_IS_MODEL(OCTEON_CN68XX))
		max_port = 1;
	अन्यथा
		max_port = 0;

	अगर (octeon_bootinfo->board_type == CVMX_BOARD_TYPE_NIC10E)
		max_port = 0;

	क्रम (i = 0; i < 2; i++) अणु
		पूर्णांक mgmt;

		snम_लिखो(name_buffer, माप(name_buffer),
			 "mix%d", i);
		alias_prop = fdt_getprop(initial_boot_params, aliases,
					name_buffer, शून्य);
		अगर (alias_prop) अणु
			mgmt = fdt_path_offset(initial_boot_params, alias_prop);
			अगर (mgmt < 0)
				जारी;
			अगर (i >= max_port) अणु
				pr_debug("Deleting mix%d\n", i);
				octeon_fdt_rm_ethernet(mgmt);
				fdt_nop_property(initial_boot_params, aliases,
						 name_buffer);
			पूर्ण अन्यथा अणु
				पूर्णांक phy_addr = cvmx_helper_board_get_mii_address(CVMX_HELPER_BOARD_MGMT_IPD_PORT + i);

				octeon_fdt_set_phy(mgmt, phy_addr);
			पूर्ण
		पूर्ण
	पूर्ण

	pip_path = fdt_getprop(initial_boot_params, aliases, "pip", शून्य);
	अगर (pip_path) अणु
		पूर्णांक pip = fdt_path_offset(initial_boot_params, pip_path);

		अगर (pip	 >= 0)
			क्रम (i = 0; i <= 4; i++)
				octeon_fdt_pip_अगरace(pip, i);
	पूर्ण

	/* I2C */
	अगर (OCTEON_IS_MODEL(OCTEON_CN52XX) ||
	    OCTEON_IS_MODEL(OCTEON_CN63XX) ||
	    OCTEON_IS_MODEL(OCTEON_CN68XX) ||
	    OCTEON_IS_MODEL(OCTEON_CN56XX))
		max_port = 2;
	अन्यथा
		max_port = 1;

	क्रम (i = 0; i < 2; i++) अणु
		पूर्णांक i2c;

		snम_लिखो(name_buffer, माप(name_buffer),
			 "twsi%d", i);
		alias_prop = fdt_getprop(initial_boot_params, aliases,
					name_buffer, शून्य);

		अगर (alias_prop) अणु
			i2c = fdt_path_offset(initial_boot_params, alias_prop);
			अगर (i2c < 0)
				जारी;
			अगर (i >= max_port) अणु
				pr_debug("Deleting twsi%d\n", i);
				fdt_nop_node(initial_boot_params, i2c);
				fdt_nop_property(initial_boot_params, aliases,
						 name_buffer);
			पूर्ण
		पूर्ण
	पूर्ण

	/* SMI/MDIO */
	अगर (OCTEON_IS_MODEL(OCTEON_CN68XX))
		max_port = 4;
	अन्यथा अगर (OCTEON_IS_MODEL(OCTEON_CN52XX) ||
		 OCTEON_IS_MODEL(OCTEON_CN63XX) ||
		 OCTEON_IS_MODEL(OCTEON_CN56XX))
		max_port = 2;
	अन्यथा
		max_port = 1;

	क्रम (i = 0; i < 2; i++) अणु
		पूर्णांक i2c;

		snम_लिखो(name_buffer, माप(name_buffer),
			 "smi%d", i);
		alias_prop = fdt_getprop(initial_boot_params, aliases,
					name_buffer, शून्य);
		अगर (alias_prop) अणु
			i2c = fdt_path_offset(initial_boot_params, alias_prop);
			अगर (i2c < 0)
				जारी;
			अगर (i >= max_port) अणु
				pr_debug("Deleting smi%d\n", i);
				fdt_nop_node(initial_boot_params, i2c);
				fdt_nop_property(initial_boot_params, aliases,
						 name_buffer);
			पूर्ण
		पूर्ण
	पूर्ण

	/* Serial */
	uart_mask = 3;

	/* Right now CN52XX is the only chip with a third uart */
	अगर (OCTEON_IS_MODEL(OCTEON_CN52XX))
		uart_mask |= 4; /* uart2 */

	क्रम (i = 0; i < 3; i++) अणु
		पूर्णांक uart;

		snम_लिखो(name_buffer, माप(name_buffer),
			 "uart%d", i);
		alias_prop = fdt_getprop(initial_boot_params, aliases,
					name_buffer, शून्य);

		अगर (alias_prop) अणु
			uart = fdt_path_offset(initial_boot_params, alias_prop);
			अगर (uart_mask & (1 << i)) अणु
				__be32 f;

				f = cpu_to_be32(octeon_get_io_घड़ी_rate());
				fdt_setprop_inplace(initial_boot_params,
						    uart, "clock-frequency",
						    &f, माप(f));
				जारी;
			पूर्ण
			pr_debug("Deleting uart%d\n", i);
			fdt_nop_node(initial_boot_params, uart);
			fdt_nop_property(initial_boot_params, aliases,
					 name_buffer);
		पूर्ण
	पूर्ण

	/* Compact Flash */
	alias_prop = fdt_getprop(initial_boot_params, aliases,
				 "cf0", शून्य);
	अगर (alias_prop) अणु
		जोड़ cvmx_mio_boot_reg_cfgx mio_boot_reg_cfg;
		अचिन्हित दीर्घ base_ptr, region_base, region_size;
		अचिन्हित दीर्घ region1_base = 0;
		अचिन्हित दीर्घ region1_size = 0;
		पूर्णांक cs, bootbus;
		bool is_16bit = false;
		bool is_true_ide = false;
		__be32 new_reg[6];
		__be32 *ranges;
		पूर्णांक len;

		पूर्णांक cf = fdt_path_offset(initial_boot_params, alias_prop);

		base_ptr = 0;
		अगर (octeon_bootinfo->major_version == 1
			&& octeon_bootinfo->minor_version >= 1) अणु
			अगर (octeon_bootinfo->compact_flash_common_base_addr)
				base_ptr = octeon_bootinfo->compact_flash_common_base_addr;
		पूर्ण अन्यथा अणु
			base_ptr = 0x1d000800;
		पूर्ण

		अगर (!base_ptr)
			जाओ no_cf;

		/* Find CS0 region. */
		क्रम (cs = 0; cs < 8; cs++) अणु
			mio_boot_reg_cfg.u64 = cvmx_पढ़ो_csr(CVMX_MIO_BOOT_REG_CFGX(cs));
			region_base = mio_boot_reg_cfg.s.base << 16;
			region_size = (mio_boot_reg_cfg.s.size + 1) << 16;
			अगर (mio_boot_reg_cfg.s.en && base_ptr >= region_base
				&& base_ptr < region_base + region_size) अणु
				is_16bit = mio_boot_reg_cfg.s.width;
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (cs >= 7) अणु
			/* cs and cs + 1 are CS0 and CS1, both must be less than 8. */
			जाओ no_cf;
		पूर्ण

		अगर (!(base_ptr & 0xfffful)) अणु
			/*
			 * Boot loader संकेतs availability of DMA (true_ide
			 * mode) by setting low order bits of base_ptr to
			 * zero.
			 */

			/* Asume that CS1 immediately follows. */
			mio_boot_reg_cfg.u64 =
				cvmx_पढ़ो_csr(CVMX_MIO_BOOT_REG_CFGX(cs + 1));
			region1_base = mio_boot_reg_cfg.s.base << 16;
			region1_size = (mio_boot_reg_cfg.s.size + 1) << 16;
			अगर (!mio_boot_reg_cfg.s.en)
				जाओ no_cf;
			is_true_ide = true;

		पूर्ण अन्यथा अणु
			fdt_nop_property(initial_boot_params, cf, "cavium,true-ide");
			fdt_nop_property(initial_boot_params, cf, "cavium,dma-engine-handle");
			अगर (!is_16bit) अणु
				__be32 width = cpu_to_be32(8);

				fdt_setprop_inplace(initial_boot_params, cf,
						"cavium,bus-width", &width, माप(width));
			पूर्ण
		पूर्ण
		new_reg[0] = cpu_to_be32(cs);
		new_reg[1] = cpu_to_be32(0);
		new_reg[2] = cpu_to_be32(0x10000);
		new_reg[3] = cpu_to_be32(cs + 1);
		new_reg[4] = cpu_to_be32(0);
		new_reg[5] = cpu_to_be32(0x10000);
		fdt_setprop_inplace(initial_boot_params, cf,
				    "reg",  new_reg, माप(new_reg));

		bootbus = fdt_parent_offset(initial_boot_params, cf);
		अगर (bootbus < 0)
			जाओ no_cf;
		ranges = fdt_getprop_w(initial_boot_params, bootbus, "ranges", &len);
		अगर (!ranges || len < (5 * 8 * माप(__be32)))
			जाओ no_cf;

		ranges[(cs * 5) + 2] = cpu_to_be32(region_base >> 32);
		ranges[(cs * 5) + 3] = cpu_to_be32(region_base & 0xffffffff);
		ranges[(cs * 5) + 4] = cpu_to_be32(region_size);
		अगर (is_true_ide) अणु
			cs++;
			ranges[(cs * 5) + 2] = cpu_to_be32(region1_base >> 32);
			ranges[(cs * 5) + 3] = cpu_to_be32(region1_base & 0xffffffff);
			ranges[(cs * 5) + 4] = cpu_to_be32(region1_size);
		पूर्ण
		जाओ end_cf;
no_cf:
		fdt_nop_node(initial_boot_params, cf);

end_cf:
		;
	पूर्ण

	/* 8 अक्षर LED */
	alias_prop = fdt_getprop(initial_boot_params, aliases,
				 "led0", शून्य);
	अगर (alias_prop) अणु
		जोड़ cvmx_mio_boot_reg_cfgx mio_boot_reg_cfg;
		अचिन्हित दीर्घ base_ptr, region_base, region_size;
		पूर्णांक cs, bootbus;
		__be32 new_reg[6];
		__be32 *ranges;
		पूर्णांक len;
		पूर्णांक led = fdt_path_offset(initial_boot_params, alias_prop);

		base_ptr = octeon_bootinfo->led_display_base_addr;
		अगर (base_ptr == 0)
			जाओ no_led;
		/* Find CS0 region. */
		क्रम (cs = 0; cs < 8; cs++) अणु
			mio_boot_reg_cfg.u64 = cvmx_पढ़ो_csr(CVMX_MIO_BOOT_REG_CFGX(cs));
			region_base = mio_boot_reg_cfg.s.base << 16;
			region_size = (mio_boot_reg_cfg.s.size + 1) << 16;
			अगर (mio_boot_reg_cfg.s.en && base_ptr >= region_base
				&& base_ptr < region_base + region_size)
				अवरोध;
		पूर्ण

		अगर (cs > 7)
			जाओ no_led;

		new_reg[0] = cpu_to_be32(cs);
		new_reg[1] = cpu_to_be32(0x20);
		new_reg[2] = cpu_to_be32(0x20);
		new_reg[3] = cpu_to_be32(cs);
		new_reg[4] = cpu_to_be32(0);
		new_reg[5] = cpu_to_be32(0x20);
		fdt_setprop_inplace(initial_boot_params, led,
				    "reg",  new_reg, माप(new_reg));

		bootbus = fdt_parent_offset(initial_boot_params, led);
		अगर (bootbus < 0)
			जाओ no_led;
		ranges = fdt_getprop_w(initial_boot_params, bootbus, "ranges", &len);
		अगर (!ranges || len < (5 * 8 * माप(__be32)))
			जाओ no_led;

		ranges[(cs * 5) + 2] = cpu_to_be32(region_base >> 32);
		ranges[(cs * 5) + 3] = cpu_to_be32(region_base & 0xffffffff);
		ranges[(cs * 5) + 4] = cpu_to_be32(region_size);
		जाओ end_led;

no_led:
		fdt_nop_node(initial_boot_params, led);
end_led:
		;
	पूर्ण

#अगर_घोषित CONFIG_USB
	/* OHCI/UHCI USB */
	alias_prop = fdt_getprop(initial_boot_params, aliases,
				 "uctl", शून्य);
	अगर (alias_prop) अणु
		पूर्णांक uctl = fdt_path_offset(initial_boot_params, alias_prop);

		अगर (uctl >= 0 && (!OCTEON_IS_MODEL(OCTEON_CN6XXX) ||
				  octeon_bootinfo->board_type == CVMX_BOARD_TYPE_NIC2E)) अणु
			pr_debug("Deleting uctl\n");
			fdt_nop_node(initial_boot_params, uctl);
			fdt_nop_property(initial_boot_params, aliases, "uctl");
		पूर्ण अन्यथा अगर (octeon_bootinfo->board_type == CVMX_BOARD_TYPE_NIC10E ||
			   octeon_bootinfo->board_type == CVMX_BOARD_TYPE_NIC4E) अणु
			/* Missing "refclk-type" शेषs to crystal. */
			fdt_nop_property(initial_boot_params, uctl, "refclk-type");
		पूर्ण
	पूर्ण

	/* DWC2 USB */
	alias_prop = fdt_getprop(initial_boot_params, aliases,
				 "usbn", शून्य);
	अगर (alias_prop) अणु
		पूर्णांक usbn = fdt_path_offset(initial_boot_params, alias_prop);

		अगर (usbn >= 0 && (current_cpu_type() == CPU_CAVIUM_OCTEON2 ||
				  !octeon_has_feature(OCTEON_FEATURE_USB))) अणु
			pr_debug("Deleting usbn\n");
			fdt_nop_node(initial_boot_params, usbn);
			fdt_nop_property(initial_boot_params, aliases, "usbn");
		पूर्ण अन्यथा  अणु
			__be32 new_f[1];
			क्रमागत cvmx_helper_board_usb_घड़ी_प्रकारypes c;

			c = __cvmx_helper_board_usb_get_घड़ी_प्रकारype();
			चयन (c) अणु
			हाल USB_CLOCK_TYPE_REF_48:
				new_f[0] = cpu_to_be32(48000000);
				fdt_setprop_inplace(initial_boot_params, usbn,
						    "refclk-frequency",  new_f, माप(new_f));
				fallthrough;
			हाल USB_CLOCK_TYPE_REF_12:
				/* Missing "refclk-type" शेषs to बाह्यal. */
				fdt_nop_property(initial_boot_params, usbn, "refclk-type");
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	वापस 0;
पूर्ण

अटल पूर्णांक __init octeon_publish_devices(व्योम)
अणु
	वापस of_platक्रमm_populate(शून्य, octeon_ids, शून्य, शून्य);
पूर्ण
arch_initcall(octeon_publish_devices);
