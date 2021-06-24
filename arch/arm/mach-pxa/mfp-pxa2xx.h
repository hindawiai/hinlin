<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_ARCH_MFP_PXA2XX_H
#घोषणा __ASM_ARCH_MFP_PXA2XX_H

#समावेश <plat/mfp.h>

/*
 * the following MFP_xxx bit definitions in mfp.h are re-used क्रम pxa2xx:
 *
 *  MFP_PIN(x)
 *  MFP_AFx
 *  MFP_LPM_DRIVE_अणुLOW, HIGHपूर्ण
 *  MFP_LPM_EDGE_x
 *
 * other MFP_x bit definitions will be ignored
 *
 * and adds the below two bits specअगरically क्रम pxa2xx:
 *
 * bit     23 - Input/Output (PXA2xx specअगरic)
 * bit     24 - Wakeup Enable(PXA2xx specअगरic)
 * bit     25 - Keep Output  (PXA2xx specअगरic)
 */

#घोषणा MFP_सूची_IN		(0x0 << 23)
#घोषणा MFP_सूची_OUT		(0x1 << 23)
#घोषणा MFP_सूची_MASK		(0x1 << 23)
#घोषणा MFP_सूची(x)		(((x) >> 23) & 0x1)

#घोषणा MFP_LPM_CAN_WAKEUP	(0x1 << 24)

/*
 * MFP_LPM_KEEP_OUTPUT must be specअगरied क्रम pins that need to
 * retain their last output level (low or high).
 * Note: MFP_LPM_KEEP_OUTPUT has no effect on pins configured क्रम input.
 */
#घोषणा MFP_LPM_KEEP_OUTPUT	(0x1 << 25)

#घोषणा WAKEUP_ON_EDGE_RISE	(MFP_LPM_CAN_WAKEUP | MFP_LPM_EDGE_RISE)
#घोषणा WAKEUP_ON_EDGE_FALL	(MFP_LPM_CAN_WAKEUP | MFP_LPM_EDGE_FALL)
#घोषणा WAKEUP_ON_EDGE_BOTH	(MFP_LPM_CAN_WAKEUP | MFP_LPM_EDGE_BOTH)

/* specअगरically क्रम enabling wakeup on keypad GPIOs */
#घोषणा WAKEUP_ON_LEVEL_HIGH	(MFP_LPM_CAN_WAKEUP)

#घोषणा MFP_CFG_IN(pin, af)		\
	((MFP_CFG_DEFAULT & ~(MFP_AF_MASK | MFP_सूची_MASK)) |\
	 (MFP_PIN(MFP_PIN_##pin) | MFP_##af | MFP_सूची_IN))

/* NOTE:  pins configured as output _must_ provide a low घातer state,
 * and this state should help to minimize the घातer dissipation.
 */
#घोषणा MFP_CFG_OUT(pin, af, state)	\
	((MFP_CFG_DEFAULT & ~(MFP_AF_MASK | MFP_सूची_MASK | MFP_LPM_STATE_MASK)) |\
	 (MFP_PIN(MFP_PIN_##pin) | MFP_##af | MFP_सूची_OUT | MFP_LPM_##state))

/* Common configurations क्रम pxa25x and pxa27x
 *
 * Note: pins configured as GPIO are always initialized to input
 * so not to cause any side effect
 */
#घोषणा GPIO0_GPIO	MFP_CFG_IN(GPIO0, AF0)
#घोषणा GPIO1_GPIO	MFP_CFG_IN(GPIO1, AF0)
#घोषणा GPIO9_GPIO	MFP_CFG_IN(GPIO9, AF0)
#घोषणा GPIO10_GPIO	MFP_CFG_IN(GPIO10, AF0)
#घोषणा GPIO11_GPIO	MFP_CFG_IN(GPIO11, AF0)
#घोषणा GPIO12_GPIO	MFP_CFG_IN(GPIO12, AF0)
#घोषणा GPIO13_GPIO	MFP_CFG_IN(GPIO13, AF0)
#घोषणा GPIO14_GPIO	MFP_CFG_IN(GPIO14, AF0)
#घोषणा GPIO15_GPIO	MFP_CFG_IN(GPIO15, AF0)
#घोषणा GPIO16_GPIO	MFP_CFG_IN(GPIO16, AF0)
#घोषणा GPIO17_GPIO	MFP_CFG_IN(GPIO17, AF0)
#घोषणा GPIO18_GPIO	MFP_CFG_IN(GPIO18, AF0)
#घोषणा GPIO19_GPIO	MFP_CFG_IN(GPIO19, AF0)
#घोषणा GPIO20_GPIO	MFP_CFG_IN(GPIO20, AF0)
#घोषणा GPIO21_GPIO	MFP_CFG_IN(GPIO21, AF0)
#घोषणा GPIO22_GPIO	MFP_CFG_IN(GPIO22, AF0)
#घोषणा GPIO23_GPIO	MFP_CFG_IN(GPIO23, AF0)
#घोषणा GPIO24_GPIO	MFP_CFG_IN(GPIO24, AF0)
#घोषणा GPIO25_GPIO	MFP_CFG_IN(GPIO25, AF0)
#घोषणा GPIO26_GPIO	MFP_CFG_IN(GPIO26, AF0)
#घोषणा GPIO27_GPIO	MFP_CFG_IN(GPIO27, AF0)
#घोषणा GPIO28_GPIO	MFP_CFG_IN(GPIO28, AF0)
#घोषणा GPIO29_GPIO	MFP_CFG_IN(GPIO29, AF0)
#घोषणा GPIO30_GPIO	MFP_CFG_IN(GPIO30, AF0)
#घोषणा GPIO31_GPIO	MFP_CFG_IN(GPIO31, AF0)
#घोषणा GPIO32_GPIO	MFP_CFG_IN(GPIO32, AF0)
#घोषणा GPIO33_GPIO	MFP_CFG_IN(GPIO33, AF0)
#घोषणा GPIO34_GPIO	MFP_CFG_IN(GPIO34, AF0)
#घोषणा GPIO35_GPIO	MFP_CFG_IN(GPIO35, AF0)
#घोषणा GPIO36_GPIO	MFP_CFG_IN(GPIO36, AF0)
#घोषणा GPIO37_GPIO	MFP_CFG_IN(GPIO37, AF0)
#घोषणा GPIO38_GPIO	MFP_CFG_IN(GPIO38, AF0)
#घोषणा GPIO39_GPIO	MFP_CFG_IN(GPIO39, AF0)
#घोषणा GPIO40_GPIO	MFP_CFG_IN(GPIO40, AF0)
#घोषणा GPIO41_GPIO	MFP_CFG_IN(GPIO41, AF0)
#घोषणा GPIO42_GPIO	MFP_CFG_IN(GPIO42, AF0)
#घोषणा GPIO43_GPIO	MFP_CFG_IN(GPIO43, AF0)
#घोषणा GPIO44_GPIO	MFP_CFG_IN(GPIO44, AF0)
#घोषणा GPIO45_GPIO	MFP_CFG_IN(GPIO45, AF0)
#घोषणा GPIO46_GPIO	MFP_CFG_IN(GPIO46, AF0)
#घोषणा GPIO47_GPIO	MFP_CFG_IN(GPIO47, AF0)
#घोषणा GPIO48_GPIO	MFP_CFG_IN(GPIO48, AF0)
#घोषणा GPIO49_GPIO	MFP_CFG_IN(GPIO49, AF0)
#घोषणा GPIO50_GPIO	MFP_CFG_IN(GPIO50, AF0)
#घोषणा GPIO51_GPIO	MFP_CFG_IN(GPIO51, AF0)
#घोषणा GPIO52_GPIO	MFP_CFG_IN(GPIO52, AF0)
#घोषणा GPIO53_GPIO	MFP_CFG_IN(GPIO53, AF0)
#घोषणा GPIO54_GPIO	MFP_CFG_IN(GPIO54, AF0)
#घोषणा GPIO55_GPIO	MFP_CFG_IN(GPIO55, AF0)
#घोषणा GPIO56_GPIO	MFP_CFG_IN(GPIO56, AF0)
#घोषणा GPIO57_GPIO	MFP_CFG_IN(GPIO57, AF0)
#घोषणा GPIO58_GPIO	MFP_CFG_IN(GPIO58, AF0)
#घोषणा GPIO59_GPIO	MFP_CFG_IN(GPIO59, AF0)
#घोषणा GPIO60_GPIO	MFP_CFG_IN(GPIO60, AF0)
#घोषणा GPIO61_GPIO	MFP_CFG_IN(GPIO61, AF0)
#घोषणा GPIO62_GPIO	MFP_CFG_IN(GPIO62, AF0)
#घोषणा GPIO63_GPIO	MFP_CFG_IN(GPIO63, AF0)
#घोषणा GPIO64_GPIO	MFP_CFG_IN(GPIO64, AF0)
#घोषणा GPIO65_GPIO	MFP_CFG_IN(GPIO65, AF0)
#घोषणा GPIO66_GPIO	MFP_CFG_IN(GPIO66, AF0)
#घोषणा GPIO67_GPIO	MFP_CFG_IN(GPIO67, AF0)
#घोषणा GPIO68_GPIO	MFP_CFG_IN(GPIO68, AF0)
#घोषणा GPIO69_GPIO	MFP_CFG_IN(GPIO69, AF0)
#घोषणा GPIO70_GPIO	MFP_CFG_IN(GPIO70, AF0)
#घोषणा GPIO71_GPIO	MFP_CFG_IN(GPIO71, AF0)
#घोषणा GPIO72_GPIO	MFP_CFG_IN(GPIO72, AF0)
#घोषणा GPIO73_GPIO	MFP_CFG_IN(GPIO73, AF0)
#घोषणा GPIO74_GPIO	MFP_CFG_IN(GPIO74, AF0)
#घोषणा GPIO75_GPIO	MFP_CFG_IN(GPIO75, AF0)
#घोषणा GPIO76_GPIO	MFP_CFG_IN(GPIO76, AF0)
#घोषणा GPIO77_GPIO	MFP_CFG_IN(GPIO77, AF0)
#घोषणा GPIO78_GPIO	MFP_CFG_IN(GPIO78, AF0)
#घोषणा GPIO79_GPIO	MFP_CFG_IN(GPIO79, AF0)
#घोषणा GPIO80_GPIO	MFP_CFG_IN(GPIO80, AF0)
#घोषणा GPIO81_GPIO	MFP_CFG_IN(GPIO81, AF0)
#घोषणा GPIO82_GPIO	MFP_CFG_IN(GPIO82, AF0)
#घोषणा GPIO83_GPIO	MFP_CFG_IN(GPIO83, AF0)
#घोषणा GPIO84_GPIO	MFP_CFG_IN(GPIO84, AF0)

बाह्य व्योम pxa2xx_mfp_config(अचिन्हित दीर्घ *mfp_cfgs, पूर्णांक num);
बाह्य व्योम pxa2xx_mfp_set_lpm(पूर्णांक mfp, अचिन्हित दीर्घ lpm);
बाह्य पूर्णांक gpio_set_wake(अचिन्हित पूर्णांक gpio, अचिन्हित पूर्णांक on);
#पूर्ण_अगर /* __ASM_ARCH_MFP_PXA2XX_H */
