<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Marvell Dove pinctrl driver based on mvebu pinctrl core
 *
 * Author: Sebastian Hesselbarth <sebastian.hesselbarth@gmail.com>
 */

#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/bitops.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/clk.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/pinctrl/pinctrl.h>
#समावेश <linux/regmap.h>

#समावेश "pinctrl-mvebu.h"

/* Internal रेजिस्टरs can be configured at any 1 MiB aligned address */
#घोषणा INT_REGS_MASK		~(SZ_1M - 1)
#घोषणा MPP4_REGS_OFFS		0xd0440
#घोषणा PMU_REGS_OFFS		0xd802c
#घोषणा GC_REGS_OFFS		0xe802c

/* MPP Base रेजिस्टरs */
#घोषणा PMU_MPP_GENERAL_CTRL	0x10
#घोषणा  AU0_AC97_SEL		BIT(16)

/* MPP Control 4 रेजिस्टर */
#घोषणा SPI_GPIO_SEL		BIT(5)
#घोषणा UART1_GPIO_SEL		BIT(4)
#घोषणा AU1_GPIO_SEL		BIT(3)
#घोषणा CAM_GPIO_SEL		BIT(2)
#घोषणा SD1_GPIO_SEL		BIT(1)
#घोषणा SD0_GPIO_SEL		BIT(0)

/* PMU Signal Select रेजिस्टरs */
#घोषणा PMU_SIGNAL_SELECT_0	0x00
#घोषणा PMU_SIGNAL_SELECT_1	0x04

/* Global Config regmap रेजिस्टरs */
#घोषणा GLOBAL_CONFIG_1		0x00
#घोषणा  TWSI_ENABLE_OPTION1	BIT(7)
#घोषणा GLOBAL_CONFIG_2		0x04
#घोषणा  TWSI_ENABLE_OPTION2	BIT(20)
#घोषणा  TWSI_ENABLE_OPTION3	BIT(21)
#घोषणा  TWSI_OPTION3_GPIO	BIT(22)
#घोषणा SSP_CTRL_STATUS_1	0x08
#घोषणा  SSP_ON_AU1		BIT(0)
#घोषणा MPP_GENERAL_CONFIG	0x10
#घोषणा  AU1_SPDIFO_GPIO_EN	BIT(1)
#घोषणा  न_अंकD_GPIO_EN		BIT(0)

#घोषणा CONFIG_PMU	BIT(4)

अटल व्योम __iomem *mpp4_base;
अटल व्योम __iomem *pmu_base;
अटल काष्ठा regmap *gconfmap;

अटल पूर्णांक करोve_pmu_mpp_ctrl_get(काष्ठा mvebu_mpp_ctrl_data *data,
				 अचिन्हित pid, अचिन्हित दीर्घ *config)
अणु
	अचिन्हित off = (pid / MVEBU_MPPS_PER_REG) * MVEBU_MPP_BITS;
	अचिन्हित shअगरt = (pid % MVEBU_MPPS_PER_REG) * MVEBU_MPP_BITS;
	अचिन्हित दीर्घ pmu = पढ़ोl(data->base + PMU_MPP_GENERAL_CTRL);
	अचिन्हित दीर्घ func;

	अगर ((pmu & BIT(pid)) == 0)
		वापस mvebu_mmio_mpp_ctrl_get(data, pid, config);

	func = पढ़ोl(pmu_base + PMU_SIGNAL_SELECT_0 + off);
	*config = (func >> shअगरt) & MVEBU_MPP_MASK;
	*config |= CONFIG_PMU;

	वापस 0;
पूर्ण

अटल पूर्णांक करोve_pmu_mpp_ctrl_set(काष्ठा mvebu_mpp_ctrl_data *data,
				 अचिन्हित pid, अचिन्हित दीर्घ config)
अणु
	अचिन्हित off = (pid / MVEBU_MPPS_PER_REG) * MVEBU_MPP_BITS;
	अचिन्हित shअगरt = (pid % MVEBU_MPPS_PER_REG) * MVEBU_MPP_BITS;
	अचिन्हित दीर्घ pmu = पढ़ोl(data->base + PMU_MPP_GENERAL_CTRL);
	अचिन्हित दीर्घ func;

	अगर ((config & CONFIG_PMU) == 0) अणु
		ग_लिखोl(pmu & ~BIT(pid), data->base + PMU_MPP_GENERAL_CTRL);
		वापस mvebu_mmio_mpp_ctrl_set(data, pid, config);
	पूर्ण

	ग_लिखोl(pmu | BIT(pid), data->base + PMU_MPP_GENERAL_CTRL);
	func = पढ़ोl(pmu_base + PMU_SIGNAL_SELECT_0 + off);
	func &= ~(MVEBU_MPP_MASK << shअगरt);
	func |= (config & MVEBU_MPP_MASK) << shअगरt;
	ग_लिखोl(func, pmu_base + PMU_SIGNAL_SELECT_0 + off);

	वापस 0;
पूर्ण

अटल पूर्णांक करोve_mpp4_ctrl_get(काष्ठा mvebu_mpp_ctrl_data *data, अचिन्हित pid,
			      अचिन्हित दीर्घ *config)
अणु
	अचिन्हित दीर्घ mpp4 = पढ़ोl(mpp4_base);
	अचिन्हित दीर्घ mask;

	चयन (pid) अणु
	हाल 24: /* mpp_camera */
		mask = CAM_GPIO_SEL;
		अवरोध;
	हाल 40: /* mpp_sdio0 */
		mask = SD0_GPIO_SEL;
		अवरोध;
	हाल 46: /* mpp_sdio1 */
		mask = SD1_GPIO_SEL;
		अवरोध;
	हाल 58: /* mpp_spi0 */
		mask = SPI_GPIO_SEL;
		अवरोध;
	हाल 62: /* mpp_uart1 */
		mask = UART1_GPIO_SEL;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	*config = ((mpp4 & mask) != 0);

	वापस 0;
पूर्ण

अटल पूर्णांक करोve_mpp4_ctrl_set(काष्ठा mvebu_mpp_ctrl_data *data, अचिन्हित pid,
			      अचिन्हित दीर्घ config)
अणु
	अचिन्हित दीर्घ mpp4 = पढ़ोl(mpp4_base);
	अचिन्हित दीर्घ mask;

	चयन (pid) अणु
	हाल 24: /* mpp_camera */
		mask = CAM_GPIO_SEL;
		अवरोध;
	हाल 40: /* mpp_sdio0 */
		mask = SD0_GPIO_SEL;
		अवरोध;
	हाल 46: /* mpp_sdio1 */
		mask = SD1_GPIO_SEL;
		अवरोध;
	हाल 58: /* mpp_spi0 */
		mask = SPI_GPIO_SEL;
		अवरोध;
	हाल 62: /* mpp_uart1 */
		mask = UART1_GPIO_SEL;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	mpp4 &= ~mask;
	अगर (config)
		mpp4 |= mask;

	ग_लिखोl(mpp4, mpp4_base);

	वापस 0;
पूर्ण

अटल पूर्णांक करोve_nand_ctrl_get(काष्ठा mvebu_mpp_ctrl_data *data, अचिन्हित pid,
			      अचिन्हित दीर्घ *config)
अणु
	अचिन्हित पूर्णांक gmpp;

	regmap_पढ़ो(gconfmap, MPP_GENERAL_CONFIG, &gmpp);
	*config = ((gmpp & न_अंकD_GPIO_EN) != 0);

	वापस 0;
पूर्ण

अटल पूर्णांक करोve_nand_ctrl_set(काष्ठा mvebu_mpp_ctrl_data *data, अचिन्हित pid,
			      अचिन्हित दीर्घ config)
अणु
	regmap_update_bits(gconfmap, MPP_GENERAL_CONFIG,
			   न_अंकD_GPIO_EN,
			   (config) ? न_अंकD_GPIO_EN : 0);
	वापस 0;
पूर्ण

अटल पूर्णांक करोve_audio0_ctrl_get(काष्ठा mvebu_mpp_ctrl_data *data, अचिन्हित pid,
				अचिन्हित दीर्घ *config)
अणु
	अचिन्हित दीर्घ pmu = पढ़ोl(data->base + PMU_MPP_GENERAL_CTRL);

	*config = ((pmu & AU0_AC97_SEL) != 0);

	वापस 0;
पूर्ण

अटल पूर्णांक करोve_audio0_ctrl_set(काष्ठा mvebu_mpp_ctrl_data *data, अचिन्हित pid,
				अचिन्हित दीर्घ config)
अणु
	अचिन्हित दीर्घ pmu = पढ़ोl(data->base + PMU_MPP_GENERAL_CTRL);

	pmu &= ~AU0_AC97_SEL;
	अगर (config)
		pmu |= AU0_AC97_SEL;
	ग_लिखोl(pmu, data->base + PMU_MPP_GENERAL_CTRL);

	वापस 0;
पूर्ण

अटल पूर्णांक करोve_audio1_ctrl_get(काष्ठा mvebu_mpp_ctrl_data *data, अचिन्हित pid,
				अचिन्हित दीर्घ *config)
अणु
	अचिन्हित पूर्णांक mpp4 = पढ़ोl(mpp4_base);
	अचिन्हित पूर्णांक sspc1;
	अचिन्हित पूर्णांक gmpp;
	अचिन्हित पूर्णांक gcfg2;

	regmap_पढ़ो(gconfmap, SSP_CTRL_STATUS_1, &sspc1);
	regmap_पढ़ो(gconfmap, MPP_GENERAL_CONFIG, &gmpp);
	regmap_पढ़ो(gconfmap, GLOBAL_CONFIG_2, &gcfg2);

	*config = 0;
	अगर (mpp4 & AU1_GPIO_SEL)
		*config |= BIT(3);
	अगर (sspc1 & SSP_ON_AU1)
		*config |= BIT(2);
	अगर (gmpp & AU1_SPDIFO_GPIO_EN)
		*config |= BIT(1);
	अगर (gcfg2 & TWSI_OPTION3_GPIO)
		*config |= BIT(0);

	/* SSP/TWSI only अगर I2S1 not set*/
	अगर ((*config & BIT(3)) == 0)
		*config &= ~(BIT(2) | BIT(0));
	/* TWSI only अगर SPDIFO not set*/
	अगर ((*config & BIT(1)) == 0)
		*config &= ~BIT(0);
	वापस 0;
पूर्ण

अटल पूर्णांक करोve_audio1_ctrl_set(काष्ठा mvebu_mpp_ctrl_data *data, अचिन्हित pid,
				अचिन्हित दीर्घ config)
अणु
	अचिन्हित पूर्णांक mpp4 = पढ़ोl(mpp4_base);

	mpp4 &= ~AU1_GPIO_SEL;
	अगर (config & BIT(3))
		mpp4 |= AU1_GPIO_SEL;
	ग_लिखोl(mpp4, mpp4_base);

	regmap_update_bits(gconfmap, SSP_CTRL_STATUS_1,
			   SSP_ON_AU1,
			   (config & BIT(2)) ? SSP_ON_AU1 : 0);
	regmap_update_bits(gconfmap, MPP_GENERAL_CONFIG,
			   AU1_SPDIFO_GPIO_EN,
			   (config & BIT(1)) ? AU1_SPDIFO_GPIO_EN : 0);
	regmap_update_bits(gconfmap, GLOBAL_CONFIG_2,
			   TWSI_OPTION3_GPIO,
			   (config & BIT(0)) ? TWSI_OPTION3_GPIO : 0);

	वापस 0;
पूर्ण

/* mpp[52:57] gpio pins depend heavily on current config;
 * gpio_req करोes not try to mux in gpio capabilities to not
 * अवरोध other functions. If you require all mpps as gpio
 * enक्रमce gpio setting by pinctrl mapping.
 */
अटल पूर्णांक करोve_audio1_ctrl_gpio_req(काष्ठा mvebu_mpp_ctrl_data *data,
				     अचिन्हित pid)
अणु
	अचिन्हित दीर्घ config;

	करोve_audio1_ctrl_get(data, pid, &config);

	चयन (config) अणु
	हाल 0x02: /* i2s1 : gpio[56:57] */
	हाल 0x0e: /* ssp  : gpio[56:57] */
		अगर (pid >= 56)
			वापस 0;
		वापस -ENOTSUPP;
	हाल 0x08: /* spdअगरo : gpio[52:55] */
	हाल 0x0b: /* twsi   : gpio[52:55] */
		अगर (pid <= 55)
			वापस 0;
		वापस -ENOTSUPP;
	हाल 0x0a: /* all gpio */
		वापस 0;
	/* 0x00 : i2s1/spdअगरo : no gpio */
	/* 0x0c : ssp/spdअगरo  : no gpio */
	/* 0x0f : ssp/twsi    : no gpio */
	पूर्ण
	वापस -ENOTSUPP;
पूर्ण

/* mpp[52:57] has gpio pins capable of in and out */
अटल पूर्णांक करोve_audio1_ctrl_gpio_dir(काष्ठा mvebu_mpp_ctrl_data *data,
				     अचिन्हित pid, bool input)
अणु
	अगर (pid < 52 || pid > 57)
		वापस -ENOTSUPP;
	वापस 0;
पूर्ण

अटल पूर्णांक करोve_twsi_ctrl_get(काष्ठा mvebu_mpp_ctrl_data *data, अचिन्हित pid,
			      अचिन्हित दीर्घ *config)
अणु
	अचिन्हित पूर्णांक gcfg1;
	अचिन्हित पूर्णांक gcfg2;

	regmap_पढ़ो(gconfmap, GLOBAL_CONFIG_1, &gcfg1);
	regmap_पढ़ो(gconfmap, GLOBAL_CONFIG_2, &gcfg2);

	*config = 0;
	अगर (gcfg1 & TWSI_ENABLE_OPTION1)
		*config = 1;
	अन्यथा अगर (gcfg2 & TWSI_ENABLE_OPTION2)
		*config = 2;
	अन्यथा अगर (gcfg2 & TWSI_ENABLE_OPTION3)
		*config = 3;

	वापस 0;
पूर्ण

अटल पूर्णांक करोve_twsi_ctrl_set(काष्ठा mvebu_mpp_ctrl_data *data, अचिन्हित pid,
			      अचिन्हित दीर्घ config)
अणु
	अचिन्हित पूर्णांक gcfg1 = 0;
	अचिन्हित पूर्णांक gcfg2 = 0;

	चयन (config) अणु
	हाल 1:
		gcfg1 = TWSI_ENABLE_OPTION1;
		अवरोध;
	हाल 2:
		gcfg2 = TWSI_ENABLE_OPTION2;
		अवरोध;
	हाल 3:
		gcfg2 = TWSI_ENABLE_OPTION3;
		अवरोध;
	पूर्ण

	regmap_update_bits(gconfmap, GLOBAL_CONFIG_1,
			   TWSI_ENABLE_OPTION1,
			   gcfg1);
	regmap_update_bits(gconfmap, GLOBAL_CONFIG_2,
			   TWSI_ENABLE_OPTION2 | TWSI_ENABLE_OPTION3,
			   gcfg2);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा mvebu_mpp_ctrl करोve_mpp_controls[] = अणु
	MPP_FUNC_CTRL(0, 15, शून्य, करोve_pmu_mpp_ctrl),
	MPP_FUNC_CTRL(16, 23, शून्य, mvebu_mmio_mpp_ctrl),
	MPP_FUNC_CTRL(24, 39, "mpp_camera", करोve_mpp4_ctrl),
	MPP_FUNC_CTRL(40, 45, "mpp_sdio0", करोve_mpp4_ctrl),
	MPP_FUNC_CTRL(46, 51, "mpp_sdio1", करोve_mpp4_ctrl),
	MPP_FUNC_GPIO_CTRL(52, 57, "mpp_audio1", करोve_audio1_ctrl),
	MPP_FUNC_CTRL(58, 61, "mpp_spi0", करोve_mpp4_ctrl),
	MPP_FUNC_CTRL(62, 63, "mpp_uart1", करोve_mpp4_ctrl),
	MPP_FUNC_CTRL(64, 71, "mpp_nand", करोve_nand_ctrl),
	MPP_FUNC_CTRL(72, 72, "audio0", करोve_audio0_ctrl),
	MPP_FUNC_CTRL(73, 73, "twsi", करोve_twsi_ctrl),
पूर्ण;

अटल काष्ठा mvebu_mpp_mode करोve_mpp_modes[] = अणु
	MPP_MODE(0,
		MPP_FUNCTION(0x00, "gpio", शून्य),
		MPP_FUNCTION(0x02, "uart2", "rts"),
		MPP_FUNCTION(0x03, "sdio0", "cd"),
		MPP_FUNCTION(0x0f, "lcd0", "pwm"),
		MPP_FUNCTION(CONFIG_PMU | 0x0, "pmu-nc", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0x1, "pmu-low", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0x2, "pmu-high", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0x3, "pmic", "sdi"),
		MPP_FUNCTION(CONFIG_PMU | 0x4, "cpu-pwr-down", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0x5, "standby-pwr-down", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0x8, "core-pwr-good", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0xa, "bat-fault", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0xb, "ext0-wakeup", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0xc, "ext1-wakeup", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0xd, "ext2-wakeup", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0xe, "pmu-blink", शून्य)),
	MPP_MODE(1,
		MPP_FUNCTION(0x00, "gpio", शून्य),
		MPP_FUNCTION(0x02, "uart2", "cts"),
		MPP_FUNCTION(0x03, "sdio0", "wp"),
		MPP_FUNCTION(0x0f, "lcd1", "pwm"),
		MPP_FUNCTION(CONFIG_PMU | 0x0, "pmu-nc", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0x1, "pmu-low", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0x2, "pmu-high", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0x3, "pmic", "sdi"),
		MPP_FUNCTION(CONFIG_PMU | 0x4, "cpu-pwr-down", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0x5, "standby-pwr-down", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0x8, "core-pwr-good", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0xa, "bat-fault", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0xb, "ext0-wakeup", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0xc, "ext1-wakeup", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0xd, "ext2-wakeup", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0xe, "pmu-blink", शून्य)),
	MPP_MODE(2,
		MPP_FUNCTION(0x00, "gpio", शून्य),
		MPP_FUNCTION(0x01, "sata", "prsnt"),
		MPP_FUNCTION(0x02, "uart2", "txd"),
		MPP_FUNCTION(0x03, "sdio0", "buspwr"),
		MPP_FUNCTION(0x04, "uart1", "rts"),
		MPP_FUNCTION(CONFIG_PMU | 0x0, "pmu-nc", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0x1, "pmu-low", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0x2, "pmu-high", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0x3, "pmic", "sdi"),
		MPP_FUNCTION(CONFIG_PMU | 0x4, "cpu-pwr-down", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0x5, "standby-pwr-down", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0x8, "core-pwr-good", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0xa, "bat-fault", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0xb, "ext0-wakeup", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0xc, "ext1-wakeup", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0xd, "ext2-wakeup", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0xe, "pmu-blink", शून्य)),
	MPP_MODE(3,
		MPP_FUNCTION(0x00, "gpio", शून्य),
		MPP_FUNCTION(0x01, "sata", "act"),
		MPP_FUNCTION(0x02, "uart2", "rxd"),
		MPP_FUNCTION(0x03, "sdio0", "ledctrl"),
		MPP_FUNCTION(0x04, "uart1", "cts"),
		MPP_FUNCTION(0x0f, "lcd-spi", "cs1"),
		MPP_FUNCTION(CONFIG_PMU | 0x0, "pmu-nc", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0x1, "pmu-low", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0x2, "pmu-high", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0x3, "pmic", "sdi"),
		MPP_FUNCTION(CONFIG_PMU | 0x4, "cpu-pwr-down", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0x5, "standby-pwr-down", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0x8, "core-pwr-good", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0xa, "bat-fault", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0xb, "ext0-wakeup", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0xc, "ext1-wakeup", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0xd, "ext2-wakeup", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0xe, "pmu-blink", शून्य)),
	MPP_MODE(4,
		MPP_FUNCTION(0x00, "gpio", शून्य),
		MPP_FUNCTION(0x02, "uart3", "rts"),
		MPP_FUNCTION(0x03, "sdio1", "cd"),
		MPP_FUNCTION(0x04, "spi1", "miso"),
		MPP_FUNCTION(CONFIG_PMU | 0x0, "pmu-nc", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0x1, "pmu-low", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0x2, "pmu-high", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0x3, "pmic", "sdi"),
		MPP_FUNCTION(CONFIG_PMU | 0x4, "cpu-pwr-down", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0x5, "standby-pwr-down", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0x8, "core-pwr-good", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0xa, "bat-fault", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0xb, "ext0-wakeup", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0xc, "ext1-wakeup", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0xd, "ext2-wakeup", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0xe, "pmu-blink", शून्य)),
	MPP_MODE(5,
		MPP_FUNCTION(0x00, "gpio", शून्य),
		MPP_FUNCTION(0x02, "uart3", "cts"),
		MPP_FUNCTION(0x03, "sdio1", "wp"),
		MPP_FUNCTION(0x04, "spi1", "cs"),
		MPP_FUNCTION(CONFIG_PMU | 0x0, "pmu-nc", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0x1, "pmu-low", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0x2, "pmu-high", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0x3, "pmic", "sdi"),
		MPP_FUNCTION(CONFIG_PMU | 0x4, "cpu-pwr-down", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0x5, "standby-pwr-down", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0x8, "core-pwr-good", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0xa, "bat-fault", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0xb, "ext0-wakeup", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0xc, "ext1-wakeup", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0xd, "ext2-wakeup", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0xe, "pmu-blink", शून्य)),
	MPP_MODE(6,
		MPP_FUNCTION(0x00, "gpio", शून्य),
		MPP_FUNCTION(0x02, "uart3", "txd"),
		MPP_FUNCTION(0x03, "sdio1", "buspwr"),
		MPP_FUNCTION(0x04, "spi1", "mosi"),
		MPP_FUNCTION(CONFIG_PMU | 0x0, "pmu-nc", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0x1, "pmu-low", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0x2, "pmu-high", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0x3, "pmic", "sdi"),
		MPP_FUNCTION(CONFIG_PMU | 0x4, "cpu-pwr-down", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0x5, "standby-pwr-down", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0x8, "core-pwr-good", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0xa, "bat-fault", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0xb, "ext0-wakeup", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0xc, "ext1-wakeup", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0xd, "ext2-wakeup", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0xe, "pmu-blink", शून्य)),
	MPP_MODE(7,
		MPP_FUNCTION(0x00, "gpio", शून्य),
		MPP_FUNCTION(0x02, "uart3", "rxd"),
		MPP_FUNCTION(0x03, "sdio1", "ledctrl"),
		MPP_FUNCTION(0x04, "spi1", "sck"),
		MPP_FUNCTION(CONFIG_PMU | 0x0, "pmu-nc", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0x1, "pmu-low", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0x2, "pmu-high", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0x3, "pmic", "sdi"),
		MPP_FUNCTION(CONFIG_PMU | 0x4, "cpu-pwr-down", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0x5, "standby-pwr-down", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0x8, "core-pwr-good", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0xa, "bat-fault", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0xb, "ext0-wakeup", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0xc, "ext1-wakeup", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0xd, "ext2-wakeup", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0xe, "pmu-blink", शून्य)),
	MPP_MODE(8,
		MPP_FUNCTION(0x00, "gpio", शून्य),
		MPP_FUNCTION(0x01, "watchdog", "rstout"),
		MPP_FUNCTION(CONFIG_PMU | 0x0, "pmu-nc", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0x1, "pmu-low", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0x2, "pmu-high", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0x3, "pmic", "sdi"),
		MPP_FUNCTION(CONFIG_PMU | 0x4, "cpu-pwr-down", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0x5, "standby-pwr-down", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0x8, "cpu-pwr-good", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0xa, "bat-fault", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0xb, "ext0-wakeup", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0xc, "ext1-wakeup", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0xd, "ext2-wakeup", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0xe, "pmu-blink", शून्य)),
	MPP_MODE(9,
		MPP_FUNCTION(0x00, "gpio", शून्य),
		MPP_FUNCTION(0x05, "pex1", "clkreq"),
		MPP_FUNCTION(CONFIG_PMU | 0x0, "pmu-nc", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0x1, "pmu-low", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0x2, "pmu-high", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0x3, "pmic", "sdi"),
		MPP_FUNCTION(CONFIG_PMU | 0x4, "cpu-pwr-down", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0x5, "standby-pwr-down", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0x8, "cpu-pwr-good", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0xa, "bat-fault", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0xb, "ext0-wakeup", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0xc, "ext1-wakeup", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0xd, "ext2-wakeup", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0xe, "pmu-blink", शून्य)),
	MPP_MODE(10,
		MPP_FUNCTION(0x00, "gpio", शून्य),
		MPP_FUNCTION(0x05, "ssp", "sclk"),
		MPP_FUNCTION(CONFIG_PMU | 0x0, "pmu-nc", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0x1, "pmu-low", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0x2, "pmu-high", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0x3, "pmic", "sdi"),
		MPP_FUNCTION(CONFIG_PMU | 0x4, "cpu-pwr-down", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0x5, "standby-pwr-down", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0x8, "cpu-pwr-good", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0xa, "bat-fault", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0xb, "ext0-wakeup", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0xc, "ext1-wakeup", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0xd, "ext2-wakeup", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0xe, "pmu-blink", शून्य)),
	MPP_MODE(11,
		MPP_FUNCTION(0x00, "gpio", शून्य),
		MPP_FUNCTION(0x01, "sata", "prsnt"),
		MPP_FUNCTION(0x02, "sata-1", "act"),
		MPP_FUNCTION(0x03, "sdio0", "ledctrl"),
		MPP_FUNCTION(0x04, "sdio1", "ledctrl"),
		MPP_FUNCTION(0x05, "pex0", "clkreq"),
		MPP_FUNCTION(CONFIG_PMU | 0x0, "pmu-nc", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0x1, "pmu-low", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0x2, "pmu-high", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0x3, "pmic", "sdi"),
		MPP_FUNCTION(CONFIG_PMU | 0x4, "cpu-pwr-down", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0x5, "standby-pwr-down", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0x8, "cpu-pwr-good", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0xa, "bat-fault", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0xb, "ext0-wakeup", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0xc, "ext1-wakeup", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0xd, "ext2-wakeup", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0xe, "pmu-blink", शून्य)),
	MPP_MODE(12,
		MPP_FUNCTION(0x00, "gpio", शून्य),
		MPP_FUNCTION(0x01, "sata", "act"),
		MPP_FUNCTION(0x02, "uart2", "rts"),
		MPP_FUNCTION(0x03, "audio0", "extclk"),
		MPP_FUNCTION(0x04, "sdio1", "cd"),
		MPP_FUNCTION(CONFIG_PMU | 0x0, "pmu-nc", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0x1, "pmu-low", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0x2, "pmu-high", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0x3, "pmic", "sdi"),
		MPP_FUNCTION(CONFIG_PMU | 0x4, "cpu-pwr-down", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0x5, "standby-pwr-down", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0x8, "cpu-pwr-good", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0xa, "bat-fault", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0xb, "ext0-wakeup", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0xc, "ext1-wakeup", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0xd, "ext2-wakeup", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0xe, "pmu-blink", शून्य)),
	MPP_MODE(13,
		MPP_FUNCTION(0x00, "gpio", शून्य),
		MPP_FUNCTION(0x02, "uart2", "cts"),
		MPP_FUNCTION(0x03, "audio1", "extclk"),
		MPP_FUNCTION(0x04, "sdio1", "wp"),
		MPP_FUNCTION(0x05, "ssp", "extclk"),
		MPP_FUNCTION(CONFIG_PMU | 0x0, "pmu-nc", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0x1, "pmu-low", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0x2, "pmu-high", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0x3, "pmic", "sdi"),
		MPP_FUNCTION(CONFIG_PMU | 0x4, "cpu-pwr-down", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0x5, "standby-pwr-down", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0x8, "cpu-pwr-good", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0xa, "bat-fault", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0xb, "ext0-wakeup", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0xc, "ext1-wakeup", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0xd, "ext2-wakeup", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0xe, "pmu-blink", शून्य)),
	MPP_MODE(14,
		MPP_FUNCTION(0x00, "gpio", शून्य),
		MPP_FUNCTION(0x02, "uart2", "txd"),
		MPP_FUNCTION(0x04, "sdio1", "buspwr"),
		MPP_FUNCTION(0x05, "ssp", "rxd"),
		MPP_FUNCTION(CONFIG_PMU | 0x0, "pmu-nc", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0x1, "pmu-low", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0x2, "pmu-high", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0x3, "pmic", "sdi"),
		MPP_FUNCTION(CONFIG_PMU | 0x4, "cpu-pwr-down", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0x5, "standby-pwr-down", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0x8, "cpu-pwr-good", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0xa, "bat-fault", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0xb, "ext0-wakeup", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0xc, "ext1-wakeup", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0xd, "ext2-wakeup", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0xe, "pmu-blink", शून्य)),
	MPP_MODE(15,
		MPP_FUNCTION(0x00, "gpio", शून्य),
		MPP_FUNCTION(0x02, "uart2", "rxd"),
		MPP_FUNCTION(0x04, "sdio1", "ledctrl"),
		MPP_FUNCTION(0x05, "ssp", "sfrm"),
		MPP_FUNCTION(CONFIG_PMU | 0x0, "pmu-nc", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0x1, "pmu-low", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0x2, "pmu-high", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0x3, "pmic", "sdi"),
		MPP_FUNCTION(CONFIG_PMU | 0x4, "cpu-pwr-down", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0x5, "standby-pwr-down", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0x8, "cpu-pwr-good", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0xa, "bat-fault", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0xb, "ext0-wakeup", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0xc, "ext1-wakeup", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0xd, "ext2-wakeup", शून्य),
		MPP_FUNCTION(CONFIG_PMU | 0xe, "pmu-blink", शून्य)),
	MPP_MODE(16,
		MPP_FUNCTION(0x00, "gpio", शून्य),
		MPP_FUNCTION(0x02, "uart3", "rts"),
		MPP_FUNCTION(0x03, "sdio0", "cd"),
		MPP_FUNCTION(0x04, "lcd-spi", "cs1"),
		MPP_FUNCTION(0x05, "ac97", "sdi1")),
	MPP_MODE(17,
		MPP_FUNCTION(0x00, "gpio", शून्य),
		MPP_FUNCTION(0x01, "ac97-1", "sysclko"),
		MPP_FUNCTION(0x02, "uart3", "cts"),
		MPP_FUNCTION(0x03, "sdio0", "wp"),
		MPP_FUNCTION(0x04, "twsi", "sda"),
		MPP_FUNCTION(0x05, "ac97", "sdi2")),
	MPP_MODE(18,
		MPP_FUNCTION(0x00, "gpio", शून्य),
		MPP_FUNCTION(0x02, "uart3", "txd"),
		MPP_FUNCTION(0x03, "sdio0", "buspwr"),
		MPP_FUNCTION(0x04, "lcd0", "pwm"),
		MPP_FUNCTION(0x05, "ac97", "sdi3")),
	MPP_MODE(19,
		MPP_FUNCTION(0x00, "gpio", शून्य),
		MPP_FUNCTION(0x02, "uart3", "rxd"),
		MPP_FUNCTION(0x03, "sdio0", "ledctrl"),
		MPP_FUNCTION(0x04, "twsi", "sck")),
	MPP_MODE(20,
		MPP_FUNCTION(0x00, "gpio", शून्य),
		MPP_FUNCTION(0x01, "ac97", "sysclko"),
		MPP_FUNCTION(0x02, "lcd-spi", "miso"),
		MPP_FUNCTION(0x03, "sdio1", "cd"),
		MPP_FUNCTION(0x05, "sdio0", "cd"),
		MPP_FUNCTION(0x06, "spi1", "miso")),
	MPP_MODE(21,
		MPP_FUNCTION(0x00, "gpio", शून्य),
		MPP_FUNCTION(0x01, "uart1", "rts"),
		MPP_FUNCTION(0x02, "lcd-spi", "cs0"),
		MPP_FUNCTION(0x03, "sdio1", "wp"),
		MPP_FUNCTION(0x04, "ssp", "sfrm"),
		MPP_FUNCTION(0x05, "sdio0", "wp"),
		MPP_FUNCTION(0x06, "spi1", "cs")),
	MPP_MODE(22,
		MPP_FUNCTION(0x00, "gpio", शून्य),
		MPP_FUNCTION(0x01, "uart1", "cts"),
		MPP_FUNCTION(0x02, "lcd-spi", "mosi"),
		MPP_FUNCTION(0x03, "sdio1", "buspwr"),
		MPP_FUNCTION(0x04, "ssp", "txd"),
		MPP_FUNCTION(0x05, "sdio0", "buspwr"),
		MPP_FUNCTION(0x06, "spi1", "mosi")),
	MPP_MODE(23,
		MPP_FUNCTION(0x00, "gpio", शून्य),
		MPP_FUNCTION(0x02, "lcd-spi", "sck"),
		MPP_FUNCTION(0x03, "sdio1", "ledctrl"),
		MPP_FUNCTION(0x04, "ssp", "sclk"),
		MPP_FUNCTION(0x05, "sdio0", "ledctrl"),
		MPP_FUNCTION(0x06, "spi1", "sck")),
	MPP_MODE(24,
		MPP_FUNCTION(0x00, "camera", शून्य),
		MPP_FUNCTION(0x01, "gpio", शून्य)),
	MPP_MODE(40,
		MPP_FUNCTION(0x00, "sdio0", शून्य),
		MPP_FUNCTION(0x01, "gpio", शून्य)),
	MPP_MODE(46,
		MPP_FUNCTION(0x00, "sdio1", शून्य),
		MPP_FUNCTION(0x01, "gpio", शून्य)),
	MPP_MODE(52,
		MPP_FUNCTION(0x00, "i2s1/spdifo", शून्य),
		MPP_FUNCTION(0x02, "i2s1", शून्य),
		MPP_FUNCTION(0x08, "spdifo", शून्य),
		MPP_FUNCTION(0x0a, "gpio", शून्य),
		MPP_FUNCTION(0x0b, "twsi", शून्य),
		MPP_FUNCTION(0x0c, "ssp/spdifo", शून्य),
		MPP_FUNCTION(0x0e, "ssp", शून्य),
		MPP_FUNCTION(0x0f, "ssp/twsi", शून्य)),
	MPP_MODE(58,
		MPP_FUNCTION(0x00, "spi0", शून्य),
		MPP_FUNCTION(0x01, "gpio", शून्य)),
	MPP_MODE(62,
		MPP_FUNCTION(0x00, "uart1", शून्य),
		MPP_FUNCTION(0x01, "gpio", शून्य)),
	MPP_MODE(64,
		MPP_FUNCTION(0x00, "nand", शून्य),
		MPP_FUNCTION(0x01, "gpo", शून्य)),
	MPP_MODE(72,
		MPP_FUNCTION(0x00, "i2s", शून्य),
		MPP_FUNCTION(0x01, "ac97", शून्य)),
	MPP_MODE(73,
		MPP_FUNCTION(0x00, "twsi-none", शून्य),
		MPP_FUNCTION(0x01, "twsi-opt1", शून्य),
		MPP_FUNCTION(0x02, "twsi-opt2", शून्य),
		MPP_FUNCTION(0x03, "twsi-opt3", शून्य)),
पूर्ण;

अटल काष्ठा pinctrl_gpio_range करोve_mpp_gpio_ranges[] = अणु
	MPP_GPIO_RANGE(0,  0,  0, 32),
	MPP_GPIO_RANGE(1, 32, 32, 32),
	MPP_GPIO_RANGE(2, 64, 64,  8),
पूर्ण;

अटल काष्ठा mvebu_pinctrl_soc_info करोve_pinctrl_info = अणु
	.controls = करोve_mpp_controls,
	.ncontrols = ARRAY_SIZE(करोve_mpp_controls),
	.modes = करोve_mpp_modes,
	.nmodes = ARRAY_SIZE(करोve_mpp_modes),
	.gpioranges = करोve_mpp_gpio_ranges,
	.ngpioranges = ARRAY_SIZE(करोve_mpp_gpio_ranges),
	.variant = 0,
पूर्ण;

अटल काष्ठा clk *clk;

अटल स्थिर काष्ठा of_device_id करोve_pinctrl_of_match[] = अणु
	अणु .compatible = "marvell,dove-pinctrl", .data = &करोve_pinctrl_info पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल स्थिर काष्ठा regmap_config gc_regmap_config = अणु
	.reg_bits = 32,
	.val_bits = 32,
	.reg_stride = 4,
	.max_रेजिस्टर = 5,
पूर्ण;

अटल पूर्णांक करोve_pinctrl_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource *res, *mpp_res;
	काष्ठा resource fb_res;
	स्थिर काष्ठा of_device_id *match =
		of_match_device(करोve_pinctrl_of_match, &pdev->dev);
	काष्ठा mvebu_mpp_ctrl_data *mpp_data;
	व्योम __iomem *base;
	पूर्णांक i;

	pdev->dev.platक्रमm_data = (व्योम *)match->data;

	/*
	 * General MPP Configuration Register is part of pdma रेजिस्टरs.
	 * grab clk to make sure it is ticking.
	 */
	clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(clk)) अणु
		dev_err(&pdev->dev, "Unable to get pdma clock");
		वापस PTR_ERR(clk);
	पूर्ण
	clk_prepare_enable(clk);

	mpp_res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	base = devm_ioremap_resource(&pdev->dev, mpp_res);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	mpp_data = devm_kसुस्मृति(&pdev->dev, करोve_pinctrl_info.ncontrols,
				माप(*mpp_data), GFP_KERNEL);
	अगर (!mpp_data)
		वापस -ENOMEM;

	करोve_pinctrl_info.control_data = mpp_data;
	क्रम (i = 0; i < ARRAY_SIZE(करोve_mpp_controls); i++)
		mpp_data[i].base = base;

	/* prepare fallback resource */
	स_नकल(&fb_res, mpp_res, माप(काष्ठा resource));
	fb_res.start = 0;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 1);
	अगर (!res) अणु
		dev_warn(&pdev->dev, "falling back to hardcoded MPP4 resource\n");
		adjust_resource(&fb_res,
			(mpp_res->start & INT_REGS_MASK) + MPP4_REGS_OFFS, 0x4);
		res = &fb_res;
	पूर्ण

	mpp4_base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(mpp4_base))
		वापस PTR_ERR(mpp4_base);

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 2);
	अगर (!res) अणु
		dev_warn(&pdev->dev, "falling back to hardcoded PMU resource\n");
		adjust_resource(&fb_res,
			(mpp_res->start & INT_REGS_MASK) + PMU_REGS_OFFS, 0x8);
		res = &fb_res;
	पूर्ण

	pmu_base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(pmu_base))
		वापस PTR_ERR(pmu_base);

	gconfmap = syscon_regmap_lookup_by_compatible("marvell,dove-global-config");
	अगर (IS_ERR(gconfmap)) अणु
		व्योम __iomem *gc_base;

		dev_warn(&pdev->dev, "falling back to hardcoded global registers\n");
		adjust_resource(&fb_res,
			(mpp_res->start & INT_REGS_MASK) + GC_REGS_OFFS, 0x14);
		gc_base = devm_ioremap_resource(&pdev->dev, &fb_res);
		अगर (IS_ERR(gc_base))
			वापस PTR_ERR(gc_base);
		gconfmap = devm_regmap_init_mmio(&pdev->dev,
						 gc_base, &gc_regmap_config);
		अगर (IS_ERR(gconfmap))
			वापस PTR_ERR(gconfmap);
	पूर्ण

	/* Warn on any missing DT resource */
	अगर (fb_res.start)
		dev_warn(&pdev->dev, FW_BUG "Missing pinctrl regs in DTB. Please update your firmware.\n");

	वापस mvebu_pinctrl_probe(pdev);
पूर्ण

अटल काष्ठा platक्रमm_driver करोve_pinctrl_driver = अणु
	.driver = अणु
		.name = "dove-pinctrl",
		.suppress_bind_attrs = true,
		.of_match_table = करोve_pinctrl_of_match,
	पूर्ण,
	.probe = करोve_pinctrl_probe,
पूर्ण;
builtin_platक्रमm_driver(करोve_pinctrl_driver);
