<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Marvell Orion pinctrl driver based on mvebu pinctrl core
 *
 * Author: Thomas Petazzoni <thomas.petazzoni@मुक्त-electrons.com>
 *
 * The first 16 MPP pins on Orion are easy to handle: they are
 * configured through 2 consecutive रेजिस्टरs, located at the base
 * address of the MPP device.
 *
 * However the last 4 MPP pins are handled by a रेजिस्टर at offset
 * 0x50 from the base address, so it is not consecutive with the first
 * two रेजिस्टरs.
 */

#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/clk.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/pinctrl/pinctrl.h>

#समावेश "pinctrl-mvebu.h"

अटल व्योम __iomem *mpp_base;
अटल व्योम __iomem *high_mpp_base;

अटल पूर्णांक orion_mpp_ctrl_get(काष्ठा mvebu_mpp_ctrl_data *data,
			      अचिन्हित pid, अचिन्हित दीर्घ *config)
अणु
	अचिन्हित shअगरt = (pid % MVEBU_MPPS_PER_REG) * MVEBU_MPP_BITS;

	अगर (pid < 16) अणु
		अचिन्हित off = (pid / MVEBU_MPPS_PER_REG) * MVEBU_MPP_BITS;
		*config = (पढ़ोl(mpp_base + off) >> shअगरt) & MVEBU_MPP_MASK;
	पूर्ण
	अन्यथा अणु
		*config = (पढ़ोl(high_mpp_base) >> shअगरt) & MVEBU_MPP_MASK;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक orion_mpp_ctrl_set(काष्ठा mvebu_mpp_ctrl_data *data,
			      अचिन्हित pid, अचिन्हित दीर्घ config)
अणु
	अचिन्हित shअगरt = (pid % MVEBU_MPPS_PER_REG) * MVEBU_MPP_BITS;

	अगर (pid < 16) अणु
		अचिन्हित off = (pid / MVEBU_MPPS_PER_REG) * MVEBU_MPP_BITS;
		u32 reg = पढ़ोl(mpp_base + off) & ~(MVEBU_MPP_MASK << shअगरt);
		ग_लिखोl(reg | (config << shअगरt), mpp_base + off);
	पूर्ण
	अन्यथा अणु
		u32 reg = पढ़ोl(high_mpp_base) & ~(MVEBU_MPP_MASK << shअगरt);
		ग_लिखोl(reg | (config << shअगरt), high_mpp_base);
	पूर्ण

	वापस 0;
पूर्ण

#घोषणा V(f5181, f5182, f5281) \
	((f5181 << 0) | (f5182 << 1) | (f5281 << 2))

क्रमागत orion_variant अणु
	V_5181  = V(1, 0, 0),
	V_5182  = V(0, 1, 0),
	V_5281  = V(0, 0, 1),
	V_ALL   = V(1, 1, 1),
पूर्ण;

अटल काष्ठा mvebu_mpp_mode orion_mpp_modes[] = अणु
	MPP_MODE(0,
		 MPP_VAR_FUNCTION(0x0, "pcie", "rstout",    V_ALL),
		 MPP_VAR_FUNCTION(0x2, "pci", "req2",       V_ALL),
		 MPP_VAR_FUNCTION(0x3, "gpio", शून्य,        V_ALL)),
	MPP_MODE(1,
		 MPP_VAR_FUNCTION(0x0, "gpio", शून्य,        V_ALL),
		 MPP_VAR_FUNCTION(0x2, "pci", "gnt2",       V_ALL)),
	MPP_MODE(2,
		 MPP_VAR_FUNCTION(0x0, "gpio", शून्य,        V_ALL),
		 MPP_VAR_FUNCTION(0x2, "pci", "req3",       V_ALL),
		 MPP_VAR_FUNCTION(0x3, "pci-1", "pme",      V_ALL)),
	MPP_MODE(3,
		 MPP_VAR_FUNCTION(0x0, "gpio", शून्य,        V_ALL),
		 MPP_VAR_FUNCTION(0x2, "pci", "gnt3",       V_ALL)),
	MPP_MODE(4,
		 MPP_VAR_FUNCTION(0x0, "gpio", शून्य,        V_ALL),
		 MPP_VAR_FUNCTION(0x2, "pci", "req4",       V_ALL),
		 MPP_VAR_FUNCTION(0x4, "bootnand", "re",    V_5182 | V_5281),
		 MPP_VAR_FUNCTION(0x5, "sata0", "prsnt",    V_5182)),
	MPP_MODE(5,
		 MPP_VAR_FUNCTION(0x0, "gpio", शून्य,        V_ALL),
		 MPP_VAR_FUNCTION(0x2, "pci", "gnt4",       V_ALL),
		 MPP_VAR_FUNCTION(0x4, "bootnand", "we",    V_5182 | V_5281),
		 MPP_VAR_FUNCTION(0x5, "sata1", "prsnt",    V_5182)),
	MPP_MODE(6,
		 MPP_VAR_FUNCTION(0x0, "gpio", शून्य,        V_ALL),
		 MPP_VAR_FUNCTION(0x2, "pci", "req5",       V_ALL),
		 MPP_VAR_FUNCTION(0x4, "nand", "re0",       V_5182 | V_5281),
		 MPP_VAR_FUNCTION(0x5, "pci-1", "clk",      V_5181),
		 MPP_VAR_FUNCTION(0x5, "sata0", "act",      V_5182)),
	MPP_MODE(7,
		 MPP_VAR_FUNCTION(0x0, "gpio", शून्य,        V_ALL),
		 MPP_VAR_FUNCTION(0x2, "pci", "gnt5",       V_ALL),
		 MPP_VAR_FUNCTION(0x4, "nand", "we0",       V_5182 | V_5281),
		 MPP_VAR_FUNCTION(0x5, "pci-1", "clk",      V_5181),
		 MPP_VAR_FUNCTION(0x5, "sata1", "act",      V_5182)),
	MPP_MODE(8,
		 MPP_VAR_FUNCTION(0x0, "gpio", शून्य,        V_ALL),
		 MPP_VAR_FUNCTION(0x1, "ge", "col",         V_ALL)),
	MPP_MODE(9,
		 MPP_VAR_FUNCTION(0x0, "gpio", शून्य,        V_ALL),
		 MPP_VAR_FUNCTION(0x1, "ge", "rxerr",       V_ALL)),
	MPP_MODE(10,
		 MPP_VAR_FUNCTION(0x0, "gpio", शून्य,        V_ALL),
		 MPP_VAR_FUNCTION(0x1, "ge", "crs",         V_ALL)),
	MPP_MODE(11,
		 MPP_VAR_FUNCTION(0x0, "gpio", शून्य,        V_ALL),
		 MPP_VAR_FUNCTION(0x1, "ge", "txerr",       V_ALL)),
	MPP_MODE(12,
		 MPP_VAR_FUNCTION(0x0, "gpio", शून्य,        V_ALL),
		 MPP_VAR_FUNCTION(0x1, "ge", "txd4",        V_ALL),
		 MPP_VAR_FUNCTION(0x4, "nand", "re1",       V_5182 | V_5281),
		 MPP_VAR_FUNCTION(0x5, "sata0", "ledprsnt", V_5182)),
	MPP_MODE(13,
		 MPP_VAR_FUNCTION(0x0, "gpio", शून्य,        V_ALL),
		 MPP_VAR_FUNCTION(0x1, "ge", "txd5",        V_ALL),
		 MPP_VAR_FUNCTION(0x4, "nand", "we1",       V_5182 | V_5281),
		 MPP_VAR_FUNCTION(0x5, "sata1", "ledprsnt", V_5182)),
	MPP_MODE(14,
		 MPP_VAR_FUNCTION(0x0, "gpio", शून्य,        V_ALL),
		 MPP_VAR_FUNCTION(0x1, "ge", "txd6",        V_ALL),
		 MPP_VAR_FUNCTION(0x4, "nand", "re2",       V_5182 | V_5281),
		 MPP_VAR_FUNCTION(0x5, "sata0", "ledact",   V_5182)),
	MPP_MODE(15,
		 MPP_VAR_FUNCTION(0x0, "gpio", शून्य,        V_ALL),
		 MPP_VAR_FUNCTION(0x1, "ge", "txd7",        V_ALL),
		 MPP_VAR_FUNCTION(0x4, "nand", "we2",       V_5182 | V_5281),
		 MPP_VAR_FUNCTION(0x5, "sata1", "ledact",   V_5182)),
	MPP_MODE(16,
		 MPP_VAR_FUNCTION(0x0, "uart1", "rxd",      V_5182 | V_5281),
		 MPP_VAR_FUNCTION(0x1, "ge", "rxd4",        V_ALL),
		 MPP_VAR_FUNCTION(0x5, "gpio", शून्य,        V_5182)),
	MPP_MODE(17,
		 MPP_VAR_FUNCTION(0x0, "uart1", "txd",      V_5182 | V_5281),
		 MPP_VAR_FUNCTION(0x1, "ge", "rxd5",        V_ALL),
		 MPP_VAR_FUNCTION(0x5, "gpio", शून्य,        V_5182)),
	MPP_MODE(18,
		 MPP_VAR_FUNCTION(0x0, "uart1", "cts",      V_5182 | V_5281),
		 MPP_VAR_FUNCTION(0x1, "ge", "rxd6",        V_ALL),
		 MPP_VAR_FUNCTION(0x5, "gpio", शून्य,        V_5182)),
	MPP_MODE(19,
		 MPP_VAR_FUNCTION(0x0, "uart1", "rts",      V_5182 | V_5281),
		 MPP_VAR_FUNCTION(0x1, "ge", "rxd7",        V_ALL),
		 MPP_VAR_FUNCTION(0x5, "gpio", शून्य,        V_5182)),
पूर्ण;

अटल स्थिर काष्ठा mvebu_mpp_ctrl orion_mpp_controls[] = अणु
	MPP_FUNC_CTRL(0, 19, शून्य, orion_mpp_ctrl),
पूर्ण;

अटल काष्ठा pinctrl_gpio_range mv88f5181_gpio_ranges[] = अणु
	MPP_GPIO_RANGE(0, 0, 0, 16),
पूर्ण;

अटल काष्ठा pinctrl_gpio_range mv88f5182_gpio_ranges[] = अणु
	MPP_GPIO_RANGE(0, 0, 0, 19),
पूर्ण;

अटल काष्ठा pinctrl_gpio_range mv88f5281_gpio_ranges[] = अणु
	MPP_GPIO_RANGE(0, 0, 0, 16),
पूर्ण;

अटल काष्ठा mvebu_pinctrl_soc_info mv88f5181_info = अणु
	.variant = V_5181,
	.controls = orion_mpp_controls,
	.ncontrols = ARRAY_SIZE(orion_mpp_controls),
	.modes = orion_mpp_modes,
	.nmodes = ARRAY_SIZE(orion_mpp_modes),
	.gpioranges = mv88f5181_gpio_ranges,
	.ngpioranges = ARRAY_SIZE(mv88f5181_gpio_ranges),
पूर्ण;

अटल काष्ठा mvebu_pinctrl_soc_info mv88f5182_info = अणु
	.variant = V_5182,
	.controls = orion_mpp_controls,
	.ncontrols = ARRAY_SIZE(orion_mpp_controls),
	.modes = orion_mpp_modes,
	.nmodes = ARRAY_SIZE(orion_mpp_modes),
	.gpioranges = mv88f5182_gpio_ranges,
	.ngpioranges = ARRAY_SIZE(mv88f5182_gpio_ranges),
पूर्ण;

अटल काष्ठा mvebu_pinctrl_soc_info mv88f5281_info = अणु
	.variant = V_5281,
	.controls = orion_mpp_controls,
	.ncontrols = ARRAY_SIZE(orion_mpp_controls),
	.modes = orion_mpp_modes,
	.nmodes = ARRAY_SIZE(orion_mpp_modes),
	.gpioranges = mv88f5281_gpio_ranges,
	.ngpioranges = ARRAY_SIZE(mv88f5281_gpio_ranges),
पूर्ण;

/*
 * There are multiple variants of the Orion SoCs, but in terms of pin
 * muxing, they are identical.
 */
अटल स्थिर काष्ठा of_device_id orion_pinctrl_of_match[] = अणु
	अणु .compatible = "marvell,88f5181-pinctrl", .data = &mv88f5181_info पूर्ण,
	अणु .compatible = "marvell,88f5181l-pinctrl", .data = &mv88f5181_info पूर्ण,
	अणु .compatible = "marvell,88f5182-pinctrl", .data = &mv88f5182_info पूर्ण,
	अणु .compatible = "marvell,88f5281-pinctrl", .data = &mv88f5281_info पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल पूर्णांक orion_pinctrl_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा of_device_id *match =
		of_match_device(orion_pinctrl_of_match, &pdev->dev);

	pdev->dev.platक्रमm_data = (व्योम*)match->data;

	mpp_base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(mpp_base))
		वापस PTR_ERR(mpp_base);

	high_mpp_base = devm_platक्रमm_ioremap_resource(pdev, 1);
	अगर (IS_ERR(high_mpp_base))
		वापस PTR_ERR(high_mpp_base);

	वापस mvebu_pinctrl_probe(pdev);
पूर्ण

अटल काष्ठा platक्रमm_driver orion_pinctrl_driver = अणु
	.driver = अणु
		.name = "orion-pinctrl",
		.of_match_table = of_match_ptr(orion_pinctrl_of_match),
	पूर्ण,
	.probe = orion_pinctrl_probe,
पूर्ण;
builtin_platक्रमm_driver(orion_pinctrl_driver);
