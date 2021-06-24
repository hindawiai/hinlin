<शैली गुरु>
/*
 * XHCI HCD glue क्रम Cavium Octeon III SOCs.
 *
 * Copyright (C) 2010-2017 Cavium Networks
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 */

#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/mutex.h>
#समावेश <linux/delay.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/पन.स>

#समावेश <यंत्र/octeon/octeon.h>

/* USB Control Register */
जोड़ cvm_usbdrd_uctl_ctl अणु
	uपूर्णांक64_t u64;
	काष्ठा cvm_usbdrd_uctl_ctl_s अणु
	/* 1 = BIST and set all USB RAMs to 0x0, 0 = BIST */
	__BITFIELD_FIELD(uपूर्णांक64_t clear_bist:1,
	/* 1 = Start BIST and cleared by hardware */
	__BITFIELD_FIELD(uपूर्णांक64_t start_bist:1,
	/* Reference घड़ी select क्रम SuperSpeed and HighSpeed PLLs:
	 *	0x0 = Both PLLs use DLMC_REF_CLK0 क्रम reference घड़ी
	 *	0x1 = Both PLLs use DLMC_REF_CLK1 क्रम reference घड़ी
	 *	0x2 = SuperSpeed PLL uses DLMC_REF_CLK0 क्रम reference घड़ी &
	 *	      HighSpeed PLL uses PLL_REF_CLK क्रम reference clck
	 *	0x3 = SuperSpeed PLL uses DLMC_REF_CLK1 क्रम reference घड़ी &
	 *	      HighSpeed PLL uses PLL_REF_CLK क्रम reference clck
	 */
	__BITFIELD_FIELD(uपूर्णांक64_t ref_clk_sel:2,
	/* 1 = Spपढ़ो-spectrum घड़ी enable, 0 = SS घड़ी disable */
	__BITFIELD_FIELD(uपूर्णांक64_t ssc_en:1,
	/* Spपढ़ो-spectrum घड़ी modulation range:
	 *	0x0 = -4980 ppm करोwnspपढ़ो
	 *	0x1 = -4492 ppm करोwnspपढ़ो
	 *	0x2 = -4003 ppm करोwnspपढ़ो
	 *	0x3 - 0x7 = Reserved
	 */
	__BITFIELD_FIELD(uपूर्णांक64_t ssc_range:3,
	/* Enable non-standard oscillator frequencies:
	 *	[55:53] = modules -1
	 *	[52:47] = 2's complement push amount, 0 = Feature disabled
	 */
	__BITFIELD_FIELD(uपूर्णांक64_t ssc_ref_clk_sel:9,
	/* Reference घड़ी multiplier क्रम non-standard frequencies:
	 *	0x19 = 100MHz on DLMC_REF_CLK* अगर REF_CLK_SEL = 0x0 or 0x1
	 *	0x28 = 125MHz on DLMC_REF_CLK* अगर REF_CLK_SEL = 0x0 or 0x1
	 *	0x32 =  50MHz on DLMC_REF_CLK* अगर REF_CLK_SEL = 0x0 or 0x1
	 *	Other Values = Reserved
	 */
	__BITFIELD_FIELD(uपूर्णांक64_t mpll_multiplier:7,
	/* Enable reference घड़ी to prescaler क्रम SuperSpeed functionality.
	 * Should always be set to "1"
	 */
	__BITFIELD_FIELD(uपूर्णांक64_t ref_ssp_en:1,
	/* Divide the reference घड़ी by 2 beक्रमe entering the
	 * REF_CLK_FSEL भागider:
	 *	If REF_CLK_SEL = 0x0 or 0x1, then only 0x0 is legal
	 *	If REF_CLK_SEL = 0x2 or 0x3, then:
	 *		0x1 = DLMC_REF_CLK* is 125MHz
	 *		0x0 = DLMC_REF_CLK* is another supported frequency
	 */
	__BITFIELD_FIELD(uपूर्णांक64_t ref_clk_भाग2:1,
	/* Select reference घड़ी freqnuency क्रम both PLL blocks:
	 *	0x27 = REF_CLK_SEL is 0x0 or 0x1
	 *	0x07 = REF_CLK_SEL is 0x2 or 0x3
	 */
	__BITFIELD_FIELD(uपूर्णांक64_t ref_clk_fsel:6,
	/* Reserved */
	__BITFIELD_FIELD(uपूर्णांक64_t reserved_31_31:1,
	/* Controller घड़ी enable. */
	__BITFIELD_FIELD(uपूर्णांक64_t h_clk_en:1,
	/* Select bypass input to controller घड़ी भागider:
	 *	0x0 = Use भागided coprocessor घड़ी from H_CLKDIV
	 *	0x1 = Use घड़ी from GPIO pins
	 */
	__BITFIELD_FIELD(uपूर्णांक64_t h_clk_byp_sel:1,
	/* Reset controller घड़ी भागider. */
	__BITFIELD_FIELD(uपूर्णांक64_t h_clkभाग_rst:1,
	/* Reserved */
	__BITFIELD_FIELD(uपूर्णांक64_t reserved_27_27:1,
	/* Clock भागider select:
	 *	0x0 = भागide by 1
	 *	0x1 = भागide by 2
	 *	0x2 = भागide by 4
	 *	0x3 = भागide by 6
	 *	0x4 = भागide by 8
	 *	0x5 = भागide by 16
	 *	0x6 = भागide by 24
	 *	0x7 = भागide by 32
	 */
	__BITFIELD_FIELD(uपूर्णांक64_t h_clkभाग_sel:3,
	/* Reserved */
	__BITFIELD_FIELD(uपूर्णांक64_t reserved_22_23:2,
	/* USB3 port permanently attached: 0x0 = No, 0x1 = Yes */
	__BITFIELD_FIELD(uपूर्णांक64_t usb3_port_perm_attach:1,
	/* USB2 port permanently attached: 0x0 = No, 0x1 = Yes */
	__BITFIELD_FIELD(uपूर्णांक64_t usb2_port_perm_attach:1,
	/* Reserved */
	__BITFIELD_FIELD(uपूर्णांक64_t reserved_19_19:1,
	/* Disable SuperSpeed PHY: 0x0 = No, 0x1 = Yes */
	__BITFIELD_FIELD(uपूर्णांक64_t usb3_port_disable:1,
	/* Reserved */
	__BITFIELD_FIELD(uपूर्णांक64_t reserved_17_17:1,
	/* Disable HighSpeed PHY: 0x0 = No, 0x1 = Yes */
	__BITFIELD_FIELD(uपूर्णांक64_t usb2_port_disable:1,
	/* Reserved */
	__BITFIELD_FIELD(uपूर्णांक64_t reserved_15_15:1,
	/* Enable PHY SuperSpeed block घातer: 0x0 = No, 0x1 = Yes */
	__BITFIELD_FIELD(uपूर्णांक64_t ss_घातer_en:1,
	/* Reserved */
	__BITFIELD_FIELD(uपूर्णांक64_t reserved_13_13:1,
	/* Enable PHY HighSpeed block घातer: 0x0 = No, 0x1 = Yes */
	__BITFIELD_FIELD(uपूर्णांक64_t hs_घातer_en:1,
	/* Reserved */
	__BITFIELD_FIELD(uपूर्णांक64_t reserved_5_11:7,
	/* Enable USB UCTL पूर्णांकerface घड़ी: 0xx = No, 0x1 = Yes */
	__BITFIELD_FIELD(uपूर्णांक64_t csclk_en:1,
	/* Controller mode: 0x0 = Host, 0x1 = Device */
	__BITFIELD_FIELD(uपूर्णांक64_t drd_mode:1,
	/* PHY reset */
	__BITFIELD_FIELD(uपूर्णांक64_t uphy_rst:1,
	/* Software reset UAHC */
	__BITFIELD_FIELD(uपूर्णांक64_t uahc_rst:1,
	/* Software resets UCTL */
	__BITFIELD_FIELD(uपूर्णांक64_t uctl_rst:1,
	;)))))))))))))))))))))))))))))))))
	पूर्ण s;
पूर्ण;

/* UAHC Configuration Register */
जोड़ cvm_usbdrd_uctl_host_cfg अणु
	uपूर्णांक64_t u64;
	काष्ठा cvm_usbdrd_uctl_host_cfg_s अणु
	/* Reserved */
	__BITFIELD_FIELD(uपूर्णांक64_t reserved_60_63:4,
	/* Indicates minimum value of all received BELT values */
	__BITFIELD_FIELD(uपूर्णांक64_t host_current_belt:12,
	/* Reserved */
	__BITFIELD_FIELD(uपूर्णांक64_t reserved_38_47:10,
	/* HS jitter adjusपंचांगent */
	__BITFIELD_FIELD(uपूर्णांक64_t fla:6,
	/* Reserved */
	__BITFIELD_FIELD(uपूर्णांक64_t reserved_29_31:3,
	/* Bus-master enable: 0x0 = Disabled (stall DMAs), 0x1 = enabled */
	__BITFIELD_FIELD(uपूर्णांक64_t bme:1,
	/* Overcurrent protection enable: 0x0 = unavailable, 0x1 = available */
	__BITFIELD_FIELD(uपूर्णांक64_t oci_en:1,
	/* Overcurrent sene selection:
	 *	0x0 = Overcurrent indication from off-chip is active-low
	 *	0x1 = Overcurrent indication from off-chip is active-high
	 */
	__BITFIELD_FIELD(uपूर्णांक64_t oci_active_high_en:1,
	/* Port घातer control enable: 0x0 = unavailable, 0x1 = available */
	__BITFIELD_FIELD(uपूर्णांक64_t ppc_en:1,
	/* Port घातer control sense selection:
	 *	0x0 = Port घातer to off-chip is active-low
	 *	0x1 = Port घातer to off-chip is active-high
	 */
	__BITFIELD_FIELD(uपूर्णांक64_t ppc_active_high_en:1,
	/* Reserved */
	__BITFIELD_FIELD(uपूर्णांक64_t reserved_0_23:24,
	;)))))))))))
	पूर्ण s;
पूर्ण;

/* UCTL Shim Features Register */
जोड़ cvm_usbdrd_uctl_shim_cfg अणु
	uपूर्णांक64_t u64;
	काष्ठा cvm_usbdrd_uctl_shim_cfg_s अणु
	/* Out-of-bound UAHC रेजिस्टर access: 0 = पढ़ो, 1 = ग_लिखो */
	__BITFIELD_FIELD(uपूर्णांक64_t xs_ncb_oob_wrn:1,
	/* Reserved */
	__BITFIELD_FIELD(uपूर्णांक64_t reserved_60_62:3,
	/* SRCID error log क्रम out-of-bound UAHC रेजिस्टर access:
	 *	[59:58] = chipID
	 *	[57] = Request source: 0 = core, 1 = NCB-device
	 *	[56:51] = Core/NCB-device number, [56] always 0 क्रम NCB devices
	 *	[50:48] = SubID
	 */
	__BITFIELD_FIELD(uपूर्णांक64_t xs_ncb_oob_osrc:12,
	/* Error log क्रम bad UAHC DMA access: 0 = Read log, 1 = Write log */
	__BITFIELD_FIELD(uपूर्णांक64_t xm_bad_dma_wrn:1,
	/* Reserved */
	__BITFIELD_FIELD(uपूर्णांक64_t reserved_44_46:3,
	/* Encoded error type क्रम bad UAHC DMA */
	__BITFIELD_FIELD(uपूर्णांक64_t xm_bad_dma_type:4,
	/* Reserved */
	__BITFIELD_FIELD(uपूर्णांक64_t reserved_13_39:27,
	/* Select the IOI पढ़ो command used by DMA accesses */
	__BITFIELD_FIELD(uपूर्णांक64_t dma_पढ़ो_cmd:1,
	/* Reserved */
	__BITFIELD_FIELD(uपूर्णांक64_t reserved_10_11:2,
	/* Select endian क्रमmat क्रम DMA accesses to the L2c:
	 *	0x0 = Little endian
	 *`	0x1 = Big endian
	 *	0x2 = Reserved
	 *	0x3 = Reserved
	 */
	__BITFIELD_FIELD(uपूर्णांक64_t dma_endian_mode:2,
	/* Reserved */
	__BITFIELD_FIELD(uपूर्णांक64_t reserved_2_7:6,
	/* Select endian क्रमmat क्रम IOI CSR access to UAHC:
	 *	0x0 = Little endian
	 *`	0x1 = Big endian
	 *	0x2 = Reserved
	 *	0x3 = Reserved
	 */
	__BITFIELD_FIELD(uपूर्णांक64_t csr_endian_mode:2,
	;))))))))))))
	पूर्ण s;
पूर्ण;

#घोषणा OCTEON_H_CLKDIV_SEL		8
#घोषणा OCTEON_MIN_H_CLK_RATE		150000000
#घोषणा OCTEON_MAX_H_CLK_RATE		300000000

अटल DEFINE_MUTEX(dwc3_octeon_घड़ीs_mutex);
अटल uपूर्णांक8_t clk_भाग[OCTEON_H_CLKDIV_SEL] = अणु1, 2, 4, 6, 8, 16, 24, 32पूर्ण;


अटल पूर्णांक dwc3_octeon_config_घातer(काष्ठा device *dev, u64 base)
अणु
#घोषणा UCTL_HOST_CFG	0xe0
	जोड़ cvm_usbdrd_uctl_host_cfg uctl_host_cfg;
	जोड़ cvmx_gpio_bit_cfgx gpio_bit;
	uपूर्णांक32_t gpio_pwr[3];
	पूर्णांक gpio, len, घातer_active_low;
	काष्ठा device_node *node = dev->of_node;
	पूर्णांक index = (base >> 24) & 1;

	अगर (of_find_property(node, "power", &len) != शून्य) अणु
		अगर (len == 12) अणु
			of_property_पढ़ो_u32_array(node, "power", gpio_pwr, 3);
			घातer_active_low = gpio_pwr[2] & 0x01;
			gpio = gpio_pwr[1];
		पूर्ण अन्यथा अगर (len == 8) अणु
			of_property_पढ़ो_u32_array(node, "power", gpio_pwr, 2);
			घातer_active_low = 0;
			gpio = gpio_pwr[1];
		पूर्ण अन्यथा अणु
			dev_err(dev, "dwc3 controller clock init failure.\n");
			वापस -EINVAL;
		पूर्ण
		अगर ((OCTEON_IS_MODEL(OCTEON_CN73XX) ||
		    OCTEON_IS_MODEL(OCTEON_CNF75XX))
		    && gpio <= 31) अणु
			gpio_bit.u64 = cvmx_पढ़ो_csr(CVMX_GPIO_BIT_CFGX(gpio));
			gpio_bit.s.tx_oe = 1;
			gpio_bit.s.output_sel = (index == 0 ? 0x14 : 0x15);
			cvmx_ग_लिखो_csr(CVMX_GPIO_BIT_CFGX(gpio), gpio_bit.u64);
		पूर्ण अन्यथा अगर (gpio <= 15) अणु
			gpio_bit.u64 = cvmx_पढ़ो_csr(CVMX_GPIO_BIT_CFGX(gpio));
			gpio_bit.s.tx_oe = 1;
			gpio_bit.s.output_sel = (index == 0 ? 0x14 : 0x19);
			cvmx_ग_लिखो_csr(CVMX_GPIO_BIT_CFGX(gpio), gpio_bit.u64);
		पूर्ण अन्यथा अणु
			gpio_bit.u64 = cvmx_पढ़ो_csr(CVMX_GPIO_XBIT_CFGX(gpio));
			gpio_bit.s.tx_oe = 1;
			gpio_bit.s.output_sel = (index == 0 ? 0x14 : 0x19);
			cvmx_ग_लिखो_csr(CVMX_GPIO_XBIT_CFGX(gpio), gpio_bit.u64);
		पूर्ण

		/* Enable XHCI घातer control and set अगर active high or low. */
		uctl_host_cfg.u64 = cvmx_पढ़ो_csr(base + UCTL_HOST_CFG);
		uctl_host_cfg.s.ppc_en = 1;
		uctl_host_cfg.s.ppc_active_high_en = !घातer_active_low;
		cvmx_ग_लिखो_csr(base + UCTL_HOST_CFG, uctl_host_cfg.u64);
	पूर्ण अन्यथा अणु
		/* Disable XHCI घातer control and set अगर active high. */
		uctl_host_cfg.u64 = cvmx_पढ़ो_csr(base + UCTL_HOST_CFG);
		uctl_host_cfg.s.ppc_en = 0;
		uctl_host_cfg.s.ppc_active_high_en = 0;
		cvmx_ग_लिखो_csr(base + UCTL_HOST_CFG, uctl_host_cfg.u64);
		dev_warn(dev, "dwc3 controller clock init failure.\n");
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक dwc3_octeon_घड़ीs_start(काष्ठा device *dev, u64 base)
अणु
	जोड़ cvm_usbdrd_uctl_ctl uctl_ctl;
	पूर्णांक ref_clk_sel = 2;
	u64 भाग;
	u32 घड़ी_rate;
	पूर्णांक mpll_mul;
	पूर्णांक i;
	u64 h_clk_rate;
	u64 uctl_ctl_reg = base;

	अगर (dev->of_node) अणु
		स्थिर अक्षर *ss_घड़ी_प्रकारype;
		स्थिर अक्षर *hs_घड़ी_प्रकारype;

		i = of_property_पढ़ो_u32(dev->of_node,
					 "refclk-frequency", &घड़ी_rate);
		अगर (i) अणु
			pr_err("No UCTL \"refclk-frequency\"\n");
			वापस -EINVAL;
		पूर्ण
		i = of_property_पढ़ो_string(dev->of_node,
					    "refclk-type-ss", &ss_घड़ी_प्रकारype);
		अगर (i) अणु
			pr_err("No UCTL \"refclk-type-ss\"\n");
			वापस -EINVAL;
		पूर्ण
		i = of_property_पढ़ो_string(dev->of_node,
					    "refclk-type-hs", &hs_घड़ी_प्रकारype);
		अगर (i) अणु
			pr_err("No UCTL \"refclk-type-hs\"\n");
			वापस -EINVAL;
		पूर्ण
		अगर (म_भेद("dlmc_ref_clk0", ss_घड़ी_प्रकारype) == 0) अणु
			अगर (म_भेद(hs_घड़ी_प्रकारype, "dlmc_ref_clk0") == 0)
				ref_clk_sel = 0;
			अन्यथा अगर (म_भेद(hs_घड़ी_प्रकारype, "pll_ref_clk") == 0)
				ref_clk_sel = 2;
			अन्यथा
				pr_err("Invalid HS clock type %s, using  pll_ref_clk instead\n",
				       hs_घड़ी_प्रकारype);
		पूर्ण अन्यथा अगर (म_भेद(ss_घड़ी_प्रकारype, "dlmc_ref_clk1") == 0) अणु
			अगर (म_भेद(hs_घड़ी_प्रकारype, "dlmc_ref_clk1") == 0)
				ref_clk_sel = 1;
			अन्यथा अगर (म_भेद(hs_घड़ी_प्रकारype, "pll_ref_clk") == 0)
				ref_clk_sel = 3;
			अन्यथा अणु
				pr_err("Invalid HS clock type %s, using  pll_ref_clk instead\n",
				       hs_घड़ी_प्रकारype);
				ref_clk_sel = 3;
			पूर्ण
		पूर्ण अन्यथा
			pr_err("Invalid SS clock type %s, using  dlmc_ref_clk0 instead\n",
			       ss_घड़ी_प्रकारype);

		अगर ((ref_clk_sel == 0 || ref_clk_sel == 1) &&
				  (घड़ी_rate != 100000000))
			pr_err("Invalid UCTL clock rate of %u, using 100000000 instead\n",
			       घड़ी_rate);

	पूर्ण अन्यथा अणु
		pr_err("No USB UCTL device node\n");
		वापस -EINVAL;
	पूर्ण

	/*
	 * Step 1: Wait क्रम all voltages to be stable...that surely
	 *         happened beक्रमe starting the kernel. SKIP
	 */

	/* Step 2: Select GPIO क्रम overcurrent indication, अगर desired. SKIP */

	/* Step 3: Assert all resets. */
	uctl_ctl.u64 = cvmx_पढ़ो_csr(uctl_ctl_reg);
	uctl_ctl.s.uphy_rst = 1;
	uctl_ctl.s.uahc_rst = 1;
	uctl_ctl.s.uctl_rst = 1;
	cvmx_ग_लिखो_csr(uctl_ctl_reg, uctl_ctl.u64);

	/* Step 4a: Reset the घड़ी भागiders. */
	uctl_ctl.u64 = cvmx_पढ़ो_csr(uctl_ctl_reg);
	uctl_ctl.s.h_clkभाग_rst = 1;
	cvmx_ग_लिखो_csr(uctl_ctl_reg, uctl_ctl.u64);

	/* Step 4b: Select controller घड़ी frequency. */
	क्रम (भाग = 0; भाग < OCTEON_H_CLKDIV_SEL; भाग++) अणु
		h_clk_rate = octeon_get_io_घड़ी_rate() / clk_भाग[भाग];
		अगर (h_clk_rate <= OCTEON_MAX_H_CLK_RATE &&
				 h_clk_rate >= OCTEON_MIN_H_CLK_RATE)
			अवरोध;
	पूर्ण
	uctl_ctl.u64 = cvmx_पढ़ो_csr(uctl_ctl_reg);
	uctl_ctl.s.h_clkभाग_sel = भाग;
	uctl_ctl.s.h_clk_en = 1;
	cvmx_ग_लिखो_csr(uctl_ctl_reg, uctl_ctl.u64);
	uctl_ctl.u64 = cvmx_पढ़ो_csr(uctl_ctl_reg);
	अगर ((भाग != uctl_ctl.s.h_clkभाग_sel) || (!uctl_ctl.s.h_clk_en)) अणु
		dev_err(dev, "dwc3 controller clock init failure.\n");
			वापस -EINVAL;
	पूर्ण

	/* Step 4c: Deनिश्चित the controller घड़ी भागider reset. */
	uctl_ctl.u64 = cvmx_पढ़ो_csr(uctl_ctl_reg);
	uctl_ctl.s.h_clkभाग_rst = 0;
	cvmx_ग_लिखो_csr(uctl_ctl_reg, uctl_ctl.u64);

	/* Step 5a: Reference घड़ी configuration. */
	uctl_ctl.u64 = cvmx_पढ़ो_csr(uctl_ctl_reg);
	uctl_ctl.s.ref_clk_sel = ref_clk_sel;
	uctl_ctl.s.ref_clk_fsel = 0x07;
	uctl_ctl.s.ref_clk_भाग2 = 0;
	चयन (घड़ी_rate) अणु
	शेष:
		dev_err(dev, "Invalid ref_clk %u, using 100000000 instead\n",
			घड़ी_rate);
		fallthrough;
	हाल 100000000:
		mpll_mul = 0x19;
		अगर (ref_clk_sel < 2)
			uctl_ctl.s.ref_clk_fsel = 0x27;
		अवरोध;
	हाल 50000000:
		mpll_mul = 0x32;
		अवरोध;
	हाल 125000000:
		mpll_mul = 0x28;
		अवरोध;
	पूर्ण
	uctl_ctl.s.mpll_multiplier = mpll_mul;

	/* Step 5b: Configure and enable spपढ़ो-spectrum क्रम SuperSpeed. */
	uctl_ctl.s.ssc_en = 1;

	/* Step 5c: Enable SuperSpeed. */
	uctl_ctl.s.ref_ssp_en = 1;

	/* Step 5d: Cofngiure PHYs. SKIP */

	/* Step 6a & 6b: Power up PHYs. */
	uctl_ctl.s.hs_घातer_en = 1;
	uctl_ctl.s.ss_घातer_en = 1;
	cvmx_ग_लिखो_csr(uctl_ctl_reg, uctl_ctl.u64);

	/* Step 7: Wait 10 controller-घड़ी cycles to take effect. */
	udelay(10);

	/* Step 8a: Deनिश्चित UCTL reset संकेत. */
	uctl_ctl.u64 = cvmx_पढ़ो_csr(uctl_ctl_reg);
	uctl_ctl.s.uctl_rst = 0;
	cvmx_ग_लिखो_csr(uctl_ctl_reg, uctl_ctl.u64);

	/* Step 8b: Wait 10 controller-घड़ी cycles. */
	udelay(10);

	/* Steo 8c: Setup घातer-घातer control. */
	अगर (dwc3_octeon_config_घातer(dev, base)) अणु
		dev_err(dev, "Error configuring power.\n");
		वापस -EINVAL;
	पूर्ण

	/* Step 8d: Deनिश्चित UAHC reset संकेत. */
	uctl_ctl.u64 = cvmx_पढ़ो_csr(uctl_ctl_reg);
	uctl_ctl.s.uahc_rst = 0;
	cvmx_ग_लिखो_csr(uctl_ctl_reg, uctl_ctl.u64);

	/* Step 8e: Wait 10 controller-घड़ी cycles. */
	udelay(10);

	/* Step 9: Enable conditional coprocessor घड़ी of UCTL. */
	uctl_ctl.u64 = cvmx_पढ़ो_csr(uctl_ctl_reg);
	uctl_ctl.s.csclk_en = 1;
	cvmx_ग_लिखो_csr(uctl_ctl_reg, uctl_ctl.u64);

	/*Step 10: Set क्रम host mode only. */
	uctl_ctl.u64 = cvmx_पढ़ो_csr(uctl_ctl_reg);
	uctl_ctl.s.drd_mode = 0;
	cvmx_ग_लिखो_csr(uctl_ctl_reg, uctl_ctl.u64);

	वापस 0;
पूर्ण

अटल व्योम __init dwc3_octeon_set_endian_mode(u64 base)
अणु
#घोषणा UCTL_SHIM_CFG	0xe8
	जोड़ cvm_usbdrd_uctl_shim_cfg shim_cfg;

	shim_cfg.u64 = cvmx_पढ़ो_csr(base + UCTL_SHIM_CFG);
#अगर_घोषित __BIG_ENDIAN
	shim_cfg.s.dma_endian_mode = 1;
	shim_cfg.s.csr_endian_mode = 1;
#अन्यथा
	shim_cfg.s.dma_endian_mode = 0;
	shim_cfg.s.csr_endian_mode = 0;
#पूर्ण_अगर
	cvmx_ग_लिखो_csr(base + UCTL_SHIM_CFG, shim_cfg.u64);
पूर्ण

#घोषणा CVMX_USBDRDX_UCTL_CTL(index)				\
		(CVMX_ADD_IO_SEG(0x0001180068000000ull) +	\
		((index & 1) * 0x1000000ull))
अटल व्योम __init dwc3_octeon_phy_reset(u64 base)
अणु
	जोड़ cvm_usbdrd_uctl_ctl uctl_ctl;
	पूर्णांक index = (base >> 24) & 1;

	uctl_ctl.u64 = cvmx_पढ़ो_csr(CVMX_USBDRDX_UCTL_CTL(index));
	uctl_ctl.s.uphy_rst = 0;
	cvmx_ग_लिखो_csr(CVMX_USBDRDX_UCTL_CTL(index), uctl_ctl.u64);
पूर्ण

अटल पूर्णांक __init dwc3_octeon_device_init(व्योम)
अणु
	स्थिर अक्षर compat_node_name[] = "cavium,octeon-7130-usb-uctl";
	काष्ठा platक्रमm_device *pdev;
	काष्ठा device_node *node;
	काष्ठा resource *res;
	व्योम __iomem *base;

	/*
	 * There should only be three universal controllers, "uctl"
	 * in the device tree. Two USB and a SATA, which we ignore.
	 */
	node = शून्य;
	करो अणु
		node = of_find_node_by_name(node, "uctl");
		अगर (!node)
			वापस -ENODEV;

		अगर (of_device_is_compatible(node, compat_node_name)) अणु
			pdev = of_find_device_by_node(node);
			अगर (!pdev)
				वापस -ENODEV;

			res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
			अगर (res == शून्य) अणु
				put_device(&pdev->dev);
				dev_err(&pdev->dev, "No memory resources\n");
				वापस -ENXIO;
			पूर्ण

			/*
			 * The code below maps in the रेजिस्टरs necessary क्रम
			 * setting up the घड़ीs and reseting PHYs. We must
			 * release the resources so the dwc3 subप्रणाली करोesn't
			 * know the dअगरference.
			 */
			base = devm_ioremap_resource(&pdev->dev, res);
			अगर (IS_ERR(base)) अणु
				put_device(&pdev->dev);
				वापस PTR_ERR(base);
			पूर्ण

			mutex_lock(&dwc3_octeon_घड़ीs_mutex);
			dwc3_octeon_घड़ीs_start(&pdev->dev, (u64)base);
			dwc3_octeon_set_endian_mode((u64)base);
			dwc3_octeon_phy_reset((u64)base);
			dev_info(&pdev->dev, "clocks initialized.\n");
			mutex_unlock(&dwc3_octeon_घड़ीs_mutex);
			devm_iounmap(&pdev->dev, base);
			devm_release_mem_region(&pdev->dev, res->start,
						resource_size(res));
		पूर्ण
	पूर्ण जबतक (node != शून्य);

	वापस 0;
पूर्ण
device_initcall(dwc3_octeon_device_init);

MODULE_AUTHOR("David Daney <david.daney@cavium.com>");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("USB driver for OCTEON III SoC");
