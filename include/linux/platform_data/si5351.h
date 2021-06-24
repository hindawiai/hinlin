<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Si5351A/B/C programmable घड़ी generator platक्रमm_data.
 */

#अगर_अघोषित __LINUX_PLATFORM_DATA_SI5351_H__
#घोषणा __LINUX_PLATFORM_DATA_SI5351_H__

/**
 * क्रमागत si5351_pll_src - Si5351 pll घड़ी source
 * @SI5351_PLL_SRC_DEFAULT: शेष, करो not change eeprom config
 * @SI5351_PLL_SRC_XTAL: pll source घड़ी is XTAL input
 * @SI5351_PLL_SRC_CLKIN: pll source घड़ी is CLKIN input (Si5351C only)
 */
क्रमागत si5351_pll_src अणु
	SI5351_PLL_SRC_DEFAULT = 0,
	SI5351_PLL_SRC_XTAL = 1,
	SI5351_PLL_SRC_CLKIN = 2,
पूर्ण;

/**
 * क्रमागत si5351_multisynth_src - Si5351 multisynth घड़ी source
 * @SI5351_MULTISYNTH_SRC_DEFAULT: शेष, करो not change eeprom config
 * @SI5351_MULTISYNTH_SRC_VCO0: multisynth source घड़ी is VCO0
 * @SI5351_MULTISYNTH_SRC_VCO1: multisynth source घड़ी is VCO1/VXCO
 */
क्रमागत si5351_multisynth_src अणु
	SI5351_MULTISYNTH_SRC_DEFAULT = 0,
	SI5351_MULTISYNTH_SRC_VCO0 = 1,
	SI5351_MULTISYNTH_SRC_VCO1 = 2,
पूर्ण;

/**
 * क्रमागत si5351_clkout_src - Si5351 घड़ी output घड़ी source
 * @SI5351_CLKOUT_SRC_DEFAULT: शेष, करो not change eeprom config
 * @SI5351_CLKOUT_SRC_MSYNTH_N: clkout N source घड़ी is multisynth N
 * @SI5351_CLKOUT_SRC_MSYNTH_0_4: clkout N source घड़ी is multisynth 0 (N<4)
 *                                or 4 (N>=4)
 * @SI5351_CLKOUT_SRC_XTAL: clkout N source घड़ी is XTAL
 * @SI5351_CLKOUT_SRC_CLKIN: clkout N source घड़ी is CLKIN (Si5351C only)
 */
क्रमागत si5351_clkout_src अणु
	SI5351_CLKOUT_SRC_DEFAULT = 0,
	SI5351_CLKOUT_SRC_MSYNTH_N = 1,
	SI5351_CLKOUT_SRC_MSYNTH_0_4 = 2,
	SI5351_CLKOUT_SRC_XTAL = 3,
	SI5351_CLKOUT_SRC_CLKIN = 4,
पूर्ण;

/**
 * क्रमागत si5351_drive_strength - Si5351 घड़ी output drive strength
 * @SI5351_DRIVE_DEFAULT: शेष, करो not change eeprom config
 * @SI5351_DRIVE_2MA: 2mA घड़ी output drive strength
 * @SI5351_DRIVE_4MA: 4mA घड़ी output drive strength
 * @SI5351_DRIVE_6MA: 6mA घड़ी output drive strength
 * @SI5351_DRIVE_8MA: 8mA घड़ी output drive strength
 */
क्रमागत si5351_drive_strength अणु
	SI5351_DRIVE_DEFAULT = 0,
	SI5351_DRIVE_2MA = 2,
	SI5351_DRIVE_4MA = 4,
	SI5351_DRIVE_6MA = 6,
	SI5351_DRIVE_8MA = 8,
पूर्ण;

/**
 * क्रमागत si5351_disable_state - Si5351 घड़ी output disable state
 * @SI5351_DISABLE_DEFAULT: शेष, करो not change eeprom config
 * @SI5351_DISABLE_LOW: CLKx is set to a LOW state when disabled
 * @SI5351_DISABLE_HIGH: CLKx is set to a HIGH state when disabled
 * @SI5351_DISABLE_FLOATING: CLKx is set to a FLOATING state when
 *				disabled
 * @SI5351_DISABLE_NEVER: CLKx is NEVER disabled
 */
क्रमागत si5351_disable_state अणु
	SI5351_DISABLE_DEFAULT = 0,
	SI5351_DISABLE_LOW,
	SI5351_DISABLE_HIGH,
	SI5351_DISABLE_FLOATING,
	SI5351_DISABLE_NEVER,
पूर्ण;

/**
 * काष्ठा si5351_clkout_config - Si5351 घड़ी output configuration
 * @clkout: clkout number
 * @multisynth_src: multisynth source घड़ी
 * @clkout_src: clkout source घड़ी
 * @pll_master: अगर true, clkout can also change pll rate
 * @pll_reset: अगर true, clkout can reset its pll
 * @drive: output drive strength
 * @rate: initial clkout rate, or शेष अगर 0
 */
काष्ठा si5351_clkout_config अणु
	क्रमागत si5351_multisynth_src multisynth_src;
	क्रमागत si5351_clkout_src clkout_src;
	क्रमागत si5351_drive_strength drive;
	क्रमागत si5351_disable_state disable_state;
	bool pll_master;
	bool pll_reset;
	अचिन्हित दीर्घ rate;
पूर्ण;

/**
 * काष्ठा si5351_platक्रमm_data - Platक्रमm data क्रम the Si5351 घड़ी driver
 * @clk_xtal: xtal input घड़ी
 * @clk_clkin: clkin input घड़ी
 * @pll_src: array of pll source घड़ी setting
 * @clkout: array of clkout configuration
 */
काष्ठा si5351_platक्रमm_data अणु
	क्रमागत si5351_pll_src pll_src[2];
	काष्ठा si5351_clkout_config clkout[8];
पूर्ण;

#पूर्ण_अगर
