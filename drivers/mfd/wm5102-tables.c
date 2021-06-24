<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * wm5102-tables.c  --  WM5102 data tables
 *
 * Copyright 2012 Wolfson Microelectronics plc
 *
 * Author: Mark Brown <broonie@खोलोsource.wolfsonmicro.com>
 */

#समावेश <linux/device.h>
#समावेश <linux/module.h>

#समावेश <linux/mfd/arizona/core.h>
#समावेश <linux/mfd/arizona/रेजिस्टरs.h>

#समावेश "arizona.h"

#घोषणा WM5102_NUM_AOD_ISR 2
#घोषणा WM5102_NUM_ISR 5

अटल स्थिर काष्ठा reg_sequence wm5102_reva_patch[] = अणु
	अणु 0x80, 0x0003 पूर्ण,
	अणु 0x221, 0x0090 पूर्ण,
	अणु 0x211, 0x0014 पूर्ण,
	अणु 0x212, 0x0000 पूर्ण,
	अणु 0x214, 0x000C पूर्ण,
	अणु 0x171, 0x0002 पूर्ण,
	अणु 0x171, 0x0000 पूर्ण,
	अणु 0x461, 0x8000 पूर्ण,
	अणु 0x463, 0x50F0 पूर्ण,
	अणु 0x465, 0x4820 पूर्ण,
	अणु 0x467, 0x4040 पूर्ण,
	अणु 0x469, 0x3940 पूर्ण,
	अणु 0x46B, 0x3310 पूर्ण,
	अणु 0x46D, 0x2D80 पूर्ण,
	अणु 0x46F, 0x2890 पूर्ण,
	अणु 0x471, 0x1990 पूर्ण,
	अणु 0x473, 0x1450 पूर्ण,
	अणु 0x475, 0x1020 पूर्ण,
	अणु 0x477, 0x0CD0 पूर्ण,
	अणु 0x479, 0x0A30 पूर्ण,
	अणु 0x47B, 0x0810 पूर्ण,
	अणु 0x47D, 0x0510 पूर्ण,
	अणु 0x4D1, 0x017F पूर्ण,
	अणु 0x500, 0x000D पूर्ण,
	अणु 0x507, 0x1820 पूर्ण,
	अणु 0x508, 0x1820 पूर्ण,
	अणु 0x540, 0x000D पूर्ण,
	अणु 0x547, 0x1820 पूर्ण,
	अणु 0x548, 0x1820 पूर्ण,
	अणु 0x580, 0x000D पूर्ण,
	अणु 0x587, 0x1820 पूर्ण,
	अणु 0x588, 0x1820 पूर्ण,
	अणु 0x80, 0x0000 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा reg_sequence wm5102_revb_patch[] = अणु
	अणु 0x19, 0x0001 पूर्ण,
	अणु 0x80, 0x0003 पूर्ण,
	अणु 0x081, 0xE022 पूर्ण,
	अणु 0x410, 0x6080 पूर्ण,
	अणु 0x418, 0xa080 पूर्ण,
	अणु 0x420, 0xa080 पूर्ण,
	अणु 0x428, 0xe000 पूर्ण,
	अणु 0x442, 0x3F0A पूर्ण,
	अणु 0x443, 0xDC1F पूर्ण,
	अणु 0x4B0, 0x0066 पूर्ण,
	अणु 0x458, 0x000b पूर्ण,
	अणु 0x212, 0x0000 पूर्ण,
	अणु 0x171, 0x0000 पूर्ण,
	अणु 0x35E, 0x000C पूर्ण,
	अणु 0x2D4, 0x0000 पूर्ण,
	अणु 0x4DC, 0x0900 पूर्ण,
	अणु 0x80, 0x0000 पूर्ण,
पूर्ण;

/* We use a function so we can use ARRAY_SIZE() */
पूर्णांक wm5102_patch(काष्ठा arizona *arizona)
अणु
	स्थिर काष्ठा reg_sequence *wm5102_patch;
	पूर्णांक patch_size;

	चयन (arizona->rev) अणु
	हाल 0:
		wm5102_patch = wm5102_reva_patch;
		patch_size = ARRAY_SIZE(wm5102_reva_patch);
		अवरोध;
	शेष:
		wm5102_patch = wm5102_revb_patch;
		patch_size = ARRAY_SIZE(wm5102_revb_patch);
	पूर्ण

	वापस regmap_multi_reg_ग_लिखो_bypassed(arizona->regmap,
					       wm5102_patch,
					       patch_size);
पूर्ण

अटल स्थिर काष्ठा regmap_irq wm5102_aod_irqs[ARIZONA_NUM_IRQ] = अणु
	[ARIZONA_IRQ_MICD_CLAMP_FALL] = अणु
		.mask = ARIZONA_MICD_CLAMP_FALL_EINT1
	पूर्ण,
	[ARIZONA_IRQ_MICD_CLAMP_RISE] = अणु
		.mask = ARIZONA_MICD_CLAMP_RISE_EINT1
	पूर्ण,
	[ARIZONA_IRQ_GP5_FALL] = अणु .mask = ARIZONA_GP5_FALL_EINT1 पूर्ण,
	[ARIZONA_IRQ_GP5_RISE] = अणु .mask = ARIZONA_GP5_RISE_EINT1 पूर्ण,
	[ARIZONA_IRQ_JD_FALL] = अणु .mask = ARIZONA_JD1_FALL_EINT1 पूर्ण,
	[ARIZONA_IRQ_JD_RISE] = अणु .mask = ARIZONA_JD1_RISE_EINT1 पूर्ण,
पूर्ण;

स्थिर काष्ठा regmap_irq_chip wm5102_aod = अणु
	.name = "wm5102 AOD",
	.status_base = ARIZONA_AOD_IRQ1,
	.mask_base = ARIZONA_AOD_IRQ_MASK_IRQ1,
	.ack_base = ARIZONA_AOD_IRQ1,
	.wake_base = ARIZONA_WAKE_CONTROL,
	.wake_invert = 1,
	.num_regs = 1,
	.irqs = wm5102_aod_irqs,
	.num_irqs = ARRAY_SIZE(wm5102_aod_irqs),
पूर्ण;

अटल स्थिर काष्ठा regmap_irq wm5102_irqs[ARIZONA_NUM_IRQ] = अणु
	[ARIZONA_IRQ_GP4] = अणु .reg_offset = 0, .mask = ARIZONA_GP4_EINT1 पूर्ण,
	[ARIZONA_IRQ_GP3] = अणु .reg_offset = 0, .mask = ARIZONA_GP3_EINT1 पूर्ण,
	[ARIZONA_IRQ_GP2] = अणु .reg_offset = 0, .mask = ARIZONA_GP2_EINT1 पूर्ण,
	[ARIZONA_IRQ_GP1] = अणु .reg_offset = 0, .mask = ARIZONA_GP1_EINT1 पूर्ण,

	[ARIZONA_IRQ_DSP1_RAM_RDY] = अणु
		.reg_offset = 1, .mask = ARIZONA_DSP1_RAM_RDY_EINT1
	पूर्ण,
	[ARIZONA_IRQ_DSP_IRQ2] = अणु
		.reg_offset = 1, .mask = ARIZONA_DSP_IRQ2_EINT1
	पूर्ण,
	[ARIZONA_IRQ_DSP_IRQ1] = अणु
		.reg_offset = 1, .mask = ARIZONA_DSP_IRQ1_EINT1
	पूर्ण,

	[ARIZONA_IRQ_SPK_OVERHEAT_WARN] = अणु
		.reg_offset = 2, .mask = ARIZONA_SPK_OVERHEAT_WARN_EINT1
	पूर्ण,
	[ARIZONA_IRQ_SPK_OVERHEAT] = अणु
		.reg_offset = 2, .mask = ARIZONA_SPK_OVERHEAT_EINT1
	पूर्ण,
	[ARIZONA_IRQ_HPDET] = अणु
		.reg_offset = 2, .mask = ARIZONA_HPDET_EINT1
	पूर्ण,
	[ARIZONA_IRQ_MICDET] = अणु
		.reg_offset = 2, .mask = ARIZONA_MICDET_EINT1
	पूर्ण,
	[ARIZONA_IRQ_WSEQ_DONE] = अणु
		.reg_offset = 2, .mask = ARIZONA_WSEQ_DONE_EINT1
	पूर्ण,
	[ARIZONA_IRQ_DRC2_SIG_DET] = अणु
		.reg_offset = 2, .mask = ARIZONA_DRC2_SIG_DET_EINT1
	पूर्ण,
	[ARIZONA_IRQ_DRC1_SIG_DET] = अणु
		.reg_offset = 2, .mask = ARIZONA_DRC1_SIG_DET_EINT1
	पूर्ण,
	[ARIZONA_IRQ_ASRC2_LOCK] = अणु
		.reg_offset = 2, .mask = ARIZONA_ASRC2_LOCK_EINT1
	पूर्ण,
	[ARIZONA_IRQ_ASRC1_LOCK] = अणु
		.reg_offset = 2, .mask = ARIZONA_ASRC1_LOCK_EINT1
	पूर्ण,
	[ARIZONA_IRQ_UNDERCLOCKED] = अणु
		.reg_offset = 2, .mask = ARIZONA_UNDERCLOCKED_EINT1
	पूर्ण,
	[ARIZONA_IRQ_OVERCLOCKED] = अणु
		.reg_offset = 2, .mask = ARIZONA_OVERCLOCKED_EINT1
	पूर्ण,
	[ARIZONA_IRQ_FLL2_LOCK] = अणु
		.reg_offset = 2, .mask = ARIZONA_FLL2_LOCK_EINT1
	पूर्ण,
	[ARIZONA_IRQ_FLL1_LOCK] = अणु
		.reg_offset = 2, .mask = ARIZONA_FLL1_LOCK_EINT1
	पूर्ण,
	[ARIZONA_IRQ_CLKGEN_ERR] = अणु
		.reg_offset = 2, .mask = ARIZONA_CLKGEN_ERR_EINT1
	पूर्ण,
	[ARIZONA_IRQ_CLKGEN_ERR_ASYNC] = अणु
		.reg_offset = 2, .mask = ARIZONA_CLKGEN_ERR_ASYNC_EINT1
	पूर्ण,

	[ARIZONA_IRQ_ASRC_CFG_ERR] = अणु
		.reg_offset = 3, .mask = ARIZONA_ASRC_CFG_ERR_EINT1
	पूर्ण,
	[ARIZONA_IRQ_AIF3_ERR] = अणु
		.reg_offset = 3, .mask = ARIZONA_AIF3_ERR_EINT1
	पूर्ण,
	[ARIZONA_IRQ_AIF2_ERR] = अणु
		.reg_offset = 3, .mask = ARIZONA_AIF2_ERR_EINT1
	पूर्ण,
	[ARIZONA_IRQ_AIF1_ERR] = अणु
		.reg_offset = 3, .mask = ARIZONA_AIF1_ERR_EINT1
	पूर्ण,
	[ARIZONA_IRQ_CTRLIF_ERR] = अणु
		.reg_offset = 3, .mask = ARIZONA_CTRLIF_ERR_EINT1
	पूर्ण,
	[ARIZONA_IRQ_MIXER_DROPPED_SAMPLES] = अणु
		.reg_offset = 3, .mask = ARIZONA_MIXER_DROPPED_SAMPLE_EINT1
	पूर्ण,
	[ARIZONA_IRQ_ASYNC_CLK_ENA_LOW] = अणु
		.reg_offset = 3, .mask = ARIZONA_ASYNC_CLK_ENA_LOW_EINT1
	पूर्ण,
	[ARIZONA_IRQ_SYSCLK_ENA_LOW] = अणु
		.reg_offset = 3, .mask = ARIZONA_SYSCLK_ENA_LOW_EINT1
	पूर्ण,
	[ARIZONA_IRQ_ISRC1_CFG_ERR] = अणु
		.reg_offset = 3, .mask = ARIZONA_ISRC1_CFG_ERR_EINT1
	पूर्ण,
	[ARIZONA_IRQ_ISRC2_CFG_ERR] = अणु
		.reg_offset = 3, .mask = ARIZONA_ISRC2_CFG_ERR_EINT1
	पूर्ण,

	[ARIZONA_IRQ_BOOT_DONE] = अणु
		.reg_offset = 4, .mask = ARIZONA_BOOT_DONE_EINT1
	पूर्ण,
	[ARIZONA_IRQ_DCS_DAC_DONE] = अणु
		.reg_offset = 4, .mask = ARIZONA_DCS_DAC_DONE_EINT1
	पूर्ण,
	[ARIZONA_IRQ_DCS_HP_DONE] = अणु
		.reg_offset = 4, .mask = ARIZONA_DCS_HP_DONE_EINT1
	पूर्ण,
	[ARIZONA_IRQ_FLL2_CLOCK_OK] = अणु
		.reg_offset = 4, .mask = ARIZONA_FLL2_CLOCK_OK_EINT1
	पूर्ण,
	[ARIZONA_IRQ_FLL1_CLOCK_OK] = अणु
		.reg_offset = 4, .mask = ARIZONA_FLL1_CLOCK_OK_EINT1
	पूर्ण,
पूर्ण;

स्थिर काष्ठा regmap_irq_chip wm5102_irq = अणु
	.name = "wm5102 IRQ",
	.status_base = ARIZONA_INTERRUPT_STATUS_1,
	.mask_base = ARIZONA_INTERRUPT_STATUS_1_MASK,
	.ack_base = ARIZONA_INTERRUPT_STATUS_1,
	.num_regs = 5,
	.irqs = wm5102_irqs,
	.num_irqs = ARRAY_SIZE(wm5102_irqs),
पूर्ण;

अटल स्थिर काष्ठा reg_शेष wm5102_reg_शेष[] = अणु
	अणु 0x00000008, 0x0019 पूर्ण,   /* R8     - Ctrl IF SPI CFG 1 */
	अणु 0x00000009, 0x0001 पूर्ण,   /* R9     - Ctrl IF I2C1 CFG 1 */
	अणु 0x00000020, 0x0000 पूर्ण,   /* R32    - Tone Generator 1 */
	अणु 0x00000021, 0x1000 पूर्ण,   /* R33    - Tone Generator 2 */
	अणु 0x00000022, 0x0000 पूर्ण,   /* R34    - Tone Generator 3 */
	अणु 0x00000023, 0x1000 पूर्ण,   /* R35    - Tone Generator 4 */
	अणु 0x00000024, 0x0000 पूर्ण,   /* R36    - Tone Generator 5 */
	अणु 0x00000030, 0x0000 पूर्ण,   /* R48    - PWM Drive 1 */
	अणु 0x00000031, 0x0100 पूर्ण,   /* R49    - PWM Drive 2 */
	अणु 0x00000032, 0x0100 पूर्ण,   /* R50    - PWM Drive 3 */
	अणु 0x00000040, 0x0000 पूर्ण,   /* R64    - Wake control */
	अणु 0x00000041, 0x0000 पूर्ण,   /* R65    - Sequence control */
	अणु 0x00000061, 0x01FF पूर्ण,   /* R97    - Sample Rate Sequence Select 1 */
	अणु 0x00000062, 0x01FF पूर्ण,   /* R98    - Sample Rate Sequence Select 2 */
	अणु 0x00000063, 0x01FF पूर्ण,   /* R99    - Sample Rate Sequence Select 3 */
	अणु 0x00000064, 0x01FF पूर्ण,   /* R100   - Sample Rate Sequence Select 4 */
	अणु 0x00000066, 0x01FF पूर्ण,   /* R102   - Always On Triggers Sequence Select 1 */
	अणु 0x00000067, 0x01FF पूर्ण,   /* R103   - Always On Triggers Sequence Select 2 */
	अणु 0x00000068, 0x01FF पूर्ण,   /* R104   - Always On Triggers Sequence Select 3 */
	अणु 0x00000069, 0x01FF पूर्ण,   /* R105   - Always On Triggers Sequence Select 4 */
	अणु 0x0000006A, 0x01FF पूर्ण,   /* R106   - Always On Triggers Sequence Select 5 */
	अणु 0x0000006B, 0x01FF पूर्ण,   /* R107   - Always On Triggers Sequence Select 6 */
	अणु 0x00000070, 0x0000 पूर्ण,   /* R112   - Comक्रमt Noise Generator */
	अणु 0x00000090, 0x0000 पूर्ण,   /* R144   - Haptics Control 1 */
	अणु 0x00000091, 0x7FFF पूर्ण,   /* R145   - Haptics Control 2 */
	अणु 0x00000092, 0x0000 पूर्ण,   /* R146   - Haptics phase 1 पूर्णांकensity */
	अणु 0x00000093, 0x0000 पूर्ण,   /* R147   - Haptics phase 1 duration */
	अणु 0x00000094, 0x0000 पूर्ण,   /* R148   - Haptics phase 2 पूर्णांकensity */
	अणु 0x00000095, 0x0000 पूर्ण,   /* R149   - Haptics phase 2 duration */
	अणु 0x00000096, 0x0000 पूर्ण,   /* R150   - Haptics phase 3 पूर्णांकensity */
	अणु 0x00000097, 0x0000 पूर्ण,   /* R151   - Haptics phase 3 duration */
	अणु 0x00000100, 0x0002 पूर्ण,   /* R256   - Clock 32k 1 */
	अणु 0x00000101, 0x0304 पूर्ण,   /* R257   - System Clock 1 */
	अणु 0x00000102, 0x0011 पूर्ण,   /* R258   - Sample rate 1 */
	अणु 0x00000103, 0x0011 पूर्ण,   /* R259   - Sample rate 2 */
	अणु 0x00000104, 0x0011 पूर्ण,   /* R260   - Sample rate 3 */
	अणु 0x00000112, 0x0305 पूर्ण,   /* R274   - Async घड़ी 1 */
	अणु 0x00000113, 0x0011 पूर्ण,   /* R275   - Async sample rate 1 */
	अणु 0x00000114, 0x0011 पूर्ण,   /* R276   - Async sample rate 2 */
	अणु 0x00000149, 0x0000 पूर्ण,   /* R329   - Output प्रणाली घड़ी */
	अणु 0x0000014A, 0x0000 पूर्ण,   /* R330   - Output async घड़ी */
	अणु 0x00000152, 0x0000 पूर्ण,   /* R338   - Rate Estimator 1 */
	अणु 0x00000153, 0x0000 पूर्ण,   /* R339   - Rate Estimator 2 */
	अणु 0x00000154, 0x0000 पूर्ण,   /* R340   - Rate Estimator 3 */
	अणु 0x00000155, 0x0000 पूर्ण,   /* R341   - Rate Estimator 4 */
	अणु 0x00000156, 0x0000 पूर्ण,   /* R342   - Rate Estimator 5 */
	अणु 0x00000161, 0x0000 पूर्ण,   /* R353   - Dynamic Frequency Scaling 1 */
	अणु 0x00000171, 0x0000 पूर्ण,   /* R369   - FLL1 Control 1 */
	अणु 0x00000172, 0x0008 पूर्ण,   /* R370   - FLL1 Control 2 */
	अणु 0x00000173, 0x0018 पूर्ण,   /* R371   - FLL1 Control 3 */
	अणु 0x00000174, 0x007D पूर्ण,   /* R372   - FLL1 Control 4 */
	अणु 0x00000175, 0x0004 पूर्ण,   /* R373   - FLL1 Control 5 */
	अणु 0x00000176, 0x0000 पूर्ण,   /* R374   - FLL1 Control 6 */
	अणु 0x00000179, 0x0000 पूर्ण,   /* R377   - FLL1 Control 7 */
	अणु 0x00000181, 0x0000 पूर्ण,   /* R385   - FLL1 Synchroniser 1 */
	अणु 0x00000182, 0x0000 पूर्ण,   /* R386   - FLL1 Synchroniser 2 */
	अणु 0x00000183, 0x0000 पूर्ण,   /* R387   - FLL1 Synchroniser 3 */
	अणु 0x00000184, 0x0000 पूर्ण,   /* R388   - FLL1 Synchroniser 4 */
	अणु 0x00000185, 0x0000 पूर्ण,   /* R389   - FLL1 Synchroniser 5 */
	अणु 0x00000186, 0x0000 पूर्ण,   /* R390   - FLL1 Synchroniser 6 */
	अणु 0x00000187, 0x0001 पूर्ण,   /* R391   - FLL1 Synchroniser 7 */
	अणु 0x00000189, 0x0000 पूर्ण,   /* R393   - FLL1 Spपढ़ो Spectrum */
	अणु 0x0000018A, 0x0004 पूर्ण,   /* R394   - FLL1 GPIO Clock */
	अणु 0x00000191, 0x0000 पूर्ण,   /* R401   - FLL2 Control 1 */
	अणु 0x00000192, 0x0008 पूर्ण,   /* R402   - FLL2 Control 2 */
	अणु 0x00000193, 0x0018 पूर्ण,   /* R403   - FLL2 Control 3 */
	अणु 0x00000194, 0x007D पूर्ण,   /* R404   - FLL2 Control 4 */
	अणु 0x00000195, 0x0004 पूर्ण,   /* R405   - FLL2 Control 5 */
	अणु 0x00000196, 0x0000 पूर्ण,   /* R406   - FLL2 Control 6 */
	अणु 0x00000199, 0x0000 पूर्ण,   /* R409   - FLL2 Control 7 */
	अणु 0x000001A1, 0x0000 पूर्ण,   /* R417   - FLL2 Synchroniser 1 */
	अणु 0x000001A2, 0x0000 पूर्ण,   /* R418   - FLL2 Synchroniser 2 */
	अणु 0x000001A3, 0x0000 पूर्ण,   /* R419   - FLL2 Synchroniser 3 */
	अणु 0x000001A4, 0x0000 पूर्ण,   /* R420   - FLL2 Synchroniser 4 */
	अणु 0x000001A5, 0x0000 पूर्ण,   /* R421   - FLL2 Synchroniser 5 */
	अणु 0x000001A6, 0x0000 पूर्ण,   /* R422   - FLL2 Synchroniser 6 */
	अणु 0x000001A7, 0x0001 पूर्ण,   /* R423   - FLL2 Synchroniser 7 */
	अणु 0x000001A9, 0x0000 पूर्ण,   /* R425   - FLL2 Spपढ़ो Spectrum */
	अणु 0x000001AA, 0x0004 पूर्ण,   /* R426   - FLL2 GPIO Clock */
	अणु 0x00000200, 0x0006 पूर्ण,   /* R512   - Mic Charge Pump 1 */
	अणु 0x00000210, 0x00D4 पूर्ण,   /* R528   - LDO1 Control 1 */
	अणु 0x00000212, 0x0000 पूर्ण,   /* R530   - LDO1 Control 2 */
	अणु 0x00000213, 0x0344 पूर्ण,   /* R531   - LDO2 Control 1 */
	अणु 0x00000218, 0x01A6 पूर्ण,   /* R536   - Mic Bias Ctrl 1 */
	अणु 0x00000219, 0x01A6 पूर्ण,   /* R537   - Mic Bias Ctrl 2 */
	अणु 0x0000021A, 0x01A6 पूर्ण,   /* R538   - Mic Bias Ctrl 3 */
	अणु 0x00000293, 0x0000 पूर्ण,   /* R659   - Accessory Detect Mode 1 */
	अणु 0x0000029B, 0x0020 पूर्ण,   /* R667   - Headphone Detect 1 */
	अणु 0x000002A2, 0x0000 पूर्ण,   /* R674   - Micd clamp control */
	अणु 0x000002A3, 0x1102 पूर्ण,   /* R675   - Mic Detect 1 */
	अणु 0x000002A4, 0x009F पूर्ण,   /* R676   - Mic Detect 2 */
	अणु 0x000002A6, 0x3737 पूर्ण,   /* R678   - Mic Detect Level 1 */
	अणु 0x000002A7, 0x2C37 पूर्ण,   /* R679   - Mic Detect Level 2 */
	अणु 0x000002A8, 0x1422 पूर्ण,   /* R680   - Mic Detect Level 3 */
	अणु 0x000002A9, 0x030A पूर्ण,   /* R681   - Mic Detect Level 4 */
	अणु 0x000002C3, 0x0000 पूर्ण,   /* R707   - Mic noise mix control 1 */
	अणु 0x000002CB, 0x0000 पूर्ण,   /* R715   - Isolation control */
	अणु 0x000002D3, 0x0000 पूर्ण,   /* R723   - Jack detect analogue */
	अणु 0x00000300, 0x0000 पूर्ण,   /* R768   - Input Enables */
	अणु 0x00000308, 0x0000 पूर्ण,   /* R776   - Input Rate */
	अणु 0x00000309, 0x0022 पूर्ण,   /* R777   - Input Volume Ramp */
	अणु 0x00000310, 0x2080 पूर्ण,   /* R784   - IN1L Control */
	अणु 0x00000311, 0x0180 पूर्ण,   /* R785   - ADC Digital Volume 1L */
	अणु 0x00000312, 0x0000 पूर्ण,   /* R786   - DMIC1L Control */
	अणु 0x00000314, 0x0080 पूर्ण,   /* R788   - IN1R Control */
	अणु 0x00000315, 0x0180 पूर्ण,   /* R789   - ADC Digital Volume 1R */
	अणु 0x00000316, 0x0000 पूर्ण,   /* R790   - DMIC1R Control */
	अणु 0x00000318, 0x2080 पूर्ण,   /* R792   - IN2L Control */
	अणु 0x00000319, 0x0180 पूर्ण,   /* R793   - ADC Digital Volume 2L */
	अणु 0x0000031A, 0x0000 पूर्ण,   /* R794   - DMIC2L Control */
	अणु 0x0000031C, 0x0080 पूर्ण,   /* R796   - IN2R Control */
	अणु 0x0000031D, 0x0180 पूर्ण,   /* R797   - ADC Digital Volume 2R */
	अणु 0x0000031E, 0x0000 पूर्ण,   /* R798   - DMIC2R Control */
	अणु 0x00000320, 0x2080 पूर्ण,   /* R800   - IN3L Control */
	अणु 0x00000321, 0x0180 पूर्ण,   /* R801   - ADC Digital Volume 3L */
	अणु 0x00000322, 0x0000 पूर्ण,   /* R802   - DMIC3L Control */
	अणु 0x00000324, 0x0080 पूर्ण,   /* R804   - IN3R Control */
	अणु 0x00000325, 0x0180 पूर्ण,   /* R805   - ADC Digital Volume 3R */
	अणु 0x00000326, 0x0000 पूर्ण,   /* R806   - DMIC3R Control */
	अणु 0x00000400, 0x0000 पूर्ण,   /* R1024  - Output Enables 1 */
	अणु 0x00000408, 0x0000 पूर्ण,   /* R1032  - Output Rate 1 */
	अणु 0x00000409, 0x0022 पूर्ण,   /* R1033  - Output Volume Ramp */
	अणु 0x00000410, 0x6080 पूर्ण,   /* R1040  - Output Path Config 1L */
	अणु 0x00000411, 0x0180 पूर्ण,   /* R1041  - DAC Digital Volume 1L */
	अणु 0x00000412, 0x0081 पूर्ण,   /* R1042  - DAC Volume Limit 1L */
	अणु 0x00000413, 0x0001 पूर्ण,   /* R1043  - Noise Gate Select 1L */
	अणु 0x00000414, 0x0080 पूर्ण,   /* R1044  - Output Path Config 1R */
	अणु 0x00000415, 0x0180 पूर्ण,   /* R1045  - DAC Digital Volume 1R */
	अणु 0x00000416, 0x0081 पूर्ण,   /* R1046  - DAC Volume Limit 1R */
	अणु 0x00000417, 0x0002 पूर्ण,   /* R1047  - Noise Gate Select 1R */
	अणु 0x00000418, 0xA080 पूर्ण,   /* R1048  - Output Path Config 2L */
	अणु 0x00000419, 0x0180 पूर्ण,   /* R1049  - DAC Digital Volume 2L */
	अणु 0x0000041A, 0x0081 पूर्ण,   /* R1050  - DAC Volume Limit 2L */
	अणु 0x0000041B, 0x0004 पूर्ण,   /* R1051  - Noise Gate Select 2L */
	अणु 0x0000041C, 0x0080 पूर्ण,   /* R1052  - Output Path Config 2R */
	अणु 0x0000041D, 0x0180 पूर्ण,   /* R1053  - DAC Digital Volume 2R */
	अणु 0x0000041E, 0x0081 पूर्ण,   /* R1054  - DAC Volume Limit 2R */
	अणु 0x0000041F, 0x0008 पूर्ण,   /* R1055  - Noise Gate Select 2R */
	अणु 0x00000420, 0xA080 पूर्ण,   /* R1056  - Output Path Config 3L */
	अणु 0x00000421, 0x0180 पूर्ण,   /* R1057  - DAC Digital Volume 3L */
	अणु 0x00000422, 0x0081 पूर्ण,   /* R1058  - DAC Volume Limit 3L */
	अणु 0x00000423, 0x0010 पूर्ण,   /* R1059  - Noise Gate Select 3L */
	अणु 0x00000428, 0xE000 पूर्ण,   /* R1064  - Output Path Config 4L */
	अणु 0x00000429, 0x0180 पूर्ण,   /* R1065  - DAC Digital Volume 4L */
	अणु 0x0000042A, 0x0081 पूर्ण,   /* R1066  - Out Volume 4L */
	अणु 0x0000042B, 0x0040 पूर्ण,   /* R1067  - Noise Gate Select 4L */
	अणु 0x0000042D, 0x0180 पूर्ण,   /* R1069  - DAC Digital Volume 4R */
	अणु 0x0000042E, 0x0081 पूर्ण,   /* R1070  - Out Volume 4R */
	अणु 0x0000042F, 0x0080 पूर्ण,   /* R1071  - Noise Gate Select 4R */
	अणु 0x00000430, 0x0000 पूर्ण,   /* R1072  - Output Path Config 5L */
	अणु 0x00000431, 0x0180 पूर्ण,   /* R1073  - DAC Digital Volume 5L */
	अणु 0x00000432, 0x0081 पूर्ण,   /* R1074  - DAC Volume Limit 5L */
	अणु 0x00000433, 0x0100 पूर्ण,   /* R1075  - Noise Gate Select 5L */
	अणु 0x00000435, 0x0180 पूर्ण,   /* R1077  - DAC Digital Volume 5R */
	अणु 0x00000436, 0x0081 पूर्ण,   /* R1078  - DAC Volume Limit 5R */
	अणु 0x00000437, 0x0200 पूर्ण,   /* R1079  - Noise Gate Select 5R */
	अणु 0x00000440, 0x0FFF पूर्ण,   /* R1088  - DRE Enable */
	अणु 0x00000442, 0x3F0A पूर्ण,   /* R1090  - DRE Control 2 */
	अणु 0x00000443, 0xDC1F पूर्ण,   /* R1090  - DRE Control 3 */
	अणु 0x00000450, 0x0000 पूर्ण,   /* R1104  - DAC AEC Control 1 */
	अणु 0x00000458, 0x000B पूर्ण,   /* R1112  - Noise Gate Control */
	अणु 0x00000490, 0x0069 पूर्ण,   /* R1168  - PDM SPK1 CTRL 1 */
	अणु 0x00000491, 0x0000 पूर्ण,   /* R1169  - PDM SPK1 CTRL 2 */
	अणु 0x00000500, 0x000C पूर्ण,   /* R1280  - AIF1 BCLK Ctrl */
	अणु 0x00000501, 0x0008 पूर्ण,   /* R1281  - AIF1 Tx Pin Ctrl */
	अणु 0x00000502, 0x0000 पूर्ण,   /* R1282  - AIF1 Rx Pin Ctrl */
	अणु 0x00000503, 0x0000 पूर्ण,   /* R1283  - AIF1 Rate Ctrl */
	अणु 0x00000504, 0x0000 पूर्ण,   /* R1284  - AIF1 Format */
	अणु 0x00000505, 0x0040 पूर्ण,   /* R1285  - AIF1 Tx BCLK Rate */
	अणु 0x00000506, 0x0040 पूर्ण,   /* R1286  - AIF1 Rx BCLK Rate */
	अणु 0x00000507, 0x1818 पूर्ण,   /* R1287  - AIF1 Frame Ctrl 1 */
	अणु 0x00000508, 0x1818 पूर्ण,   /* R1288  - AIF1 Frame Ctrl 2 */
	अणु 0x00000509, 0x0000 पूर्ण,   /* R1289  - AIF1 Frame Ctrl 3 */
	अणु 0x0000050A, 0x0001 पूर्ण,   /* R1290  - AIF1 Frame Ctrl 4 */
	अणु 0x0000050B, 0x0002 पूर्ण,   /* R1291  - AIF1 Frame Ctrl 5 */
	अणु 0x0000050C, 0x0003 पूर्ण,   /* R1292  - AIF1 Frame Ctrl 6 */
	अणु 0x0000050D, 0x0004 पूर्ण,   /* R1293  - AIF1 Frame Ctrl 7 */
	अणु 0x0000050E, 0x0005 पूर्ण,   /* R1294  - AIF1 Frame Ctrl 8 */
	अणु 0x0000050F, 0x0006 पूर्ण,   /* R1295  - AIF1 Frame Ctrl 9 */
	अणु 0x00000510, 0x0007 पूर्ण,   /* R1296  - AIF1 Frame Ctrl 10 */
	अणु 0x00000511, 0x0000 पूर्ण,   /* R1297  - AIF1 Frame Ctrl 11 */
	अणु 0x00000512, 0x0001 पूर्ण,   /* R1298  - AIF1 Frame Ctrl 12 */
	अणु 0x00000513, 0x0002 पूर्ण,   /* R1299  - AIF1 Frame Ctrl 13 */
	अणु 0x00000514, 0x0003 पूर्ण,   /* R1300  - AIF1 Frame Ctrl 14 */
	अणु 0x00000515, 0x0004 पूर्ण,   /* R1301  - AIF1 Frame Ctrl 15 */
	अणु 0x00000516, 0x0005 पूर्ण,   /* R1302  - AIF1 Frame Ctrl 16 */
	अणु 0x00000517, 0x0006 पूर्ण,   /* R1303  - AIF1 Frame Ctrl 17 */
	अणु 0x00000518, 0x0007 पूर्ण,   /* R1304  - AIF1 Frame Ctrl 18 */
	अणु 0x00000519, 0x0000 पूर्ण,   /* R1305  - AIF1 Tx Enables */
	अणु 0x0000051A, 0x0000 पूर्ण,   /* R1306  - AIF1 Rx Enables */
	अणु 0x00000540, 0x000C पूर्ण,   /* R1344  - AIF2 BCLK Ctrl */
	अणु 0x00000541, 0x0008 पूर्ण,   /* R1345  - AIF2 Tx Pin Ctrl */
	अणु 0x00000542, 0x0000 पूर्ण,   /* R1346  - AIF2 Rx Pin Ctrl */
	अणु 0x00000543, 0x0000 पूर्ण,   /* R1347  - AIF2 Rate Ctrl */
	अणु 0x00000544, 0x0000 पूर्ण,   /* R1348  - AIF2 Format */
	अणु 0x00000545, 0x0040 पूर्ण,   /* R1349  - AIF2 Tx BCLK Rate */
	अणु 0x00000546, 0x0040 पूर्ण,   /* R1350  - AIF2 Rx BCLK Rate */
	अणु 0x00000547, 0x1818 पूर्ण,   /* R1351  - AIF2 Frame Ctrl 1 */
	अणु 0x00000548, 0x1818 पूर्ण,   /* R1352  - AIF2 Frame Ctrl 2 */
	अणु 0x00000549, 0x0000 पूर्ण,   /* R1353  - AIF2 Frame Ctrl 3 */
	अणु 0x0000054A, 0x0001 पूर्ण,   /* R1354  - AIF2 Frame Ctrl 4 */
	अणु 0x00000551, 0x0000 पूर्ण,   /* R1361  - AIF2 Frame Ctrl 11 */
	अणु 0x00000552, 0x0001 पूर्ण,   /* R1362  - AIF2 Frame Ctrl 12 */
	अणु 0x00000559, 0x0000 पूर्ण,   /* R1369  - AIF2 Tx Enables */
	अणु 0x0000055A, 0x0000 पूर्ण,   /* R1370  - AIF2 Rx Enables */
	अणु 0x00000580, 0x000C पूर्ण,   /* R1408  - AIF3 BCLK Ctrl */
	अणु 0x00000581, 0x0008 पूर्ण,   /* R1409  - AIF3 Tx Pin Ctrl */
	अणु 0x00000582, 0x0000 पूर्ण,   /* R1410  - AIF3 Rx Pin Ctrl */
	अणु 0x00000583, 0x0000 पूर्ण,   /* R1411  - AIF3 Rate Ctrl */
	अणु 0x00000584, 0x0000 पूर्ण,   /* R1412  - AIF3 Format */
	अणु 0x00000585, 0x0040 पूर्ण,   /* R1413  - AIF3 Tx BCLK Rate */
	अणु 0x00000586, 0x0040 पूर्ण,   /* R1414  - AIF3 Rx BCLK Rate */
	अणु 0x00000587, 0x1818 पूर्ण,   /* R1415  - AIF3 Frame Ctrl 1 */
	अणु 0x00000588, 0x1818 पूर्ण,   /* R1416  - AIF3 Frame Ctrl 2 */
	अणु 0x00000589, 0x0000 पूर्ण,   /* R1417  - AIF3 Frame Ctrl 3 */
	अणु 0x0000058A, 0x0001 पूर्ण,   /* R1418  - AIF3 Frame Ctrl 4 */
	अणु 0x00000591, 0x0000 पूर्ण,   /* R1425  - AIF3 Frame Ctrl 11 */
	अणु 0x00000592, 0x0001 पूर्ण,   /* R1426  - AIF3 Frame Ctrl 12 */
	अणु 0x00000599, 0x0000 पूर्ण,   /* R1433  - AIF3 Tx Enables */
	अणु 0x0000059A, 0x0000 पूर्ण,   /* R1434  - AIF3 Rx Enables */
	अणु 0x000005E3, 0x0004 पूर्ण,   /* R1507  - SLIMbus Framer Ref Gear */
	अणु 0x000005E5, 0x0000 पूर्ण,   /* R1509  - SLIMbus Rates 1 */
	अणु 0x000005E6, 0x0000 पूर्ण,   /* R1510  - SLIMbus Rates 2 */
	अणु 0x000005E7, 0x0000 पूर्ण,   /* R1511  - SLIMbus Rates 3 */
	अणु 0x000005E8, 0x0000 पूर्ण,   /* R1512  - SLIMbus Rates 4 */
	अणु 0x000005E9, 0x0000 पूर्ण,   /* R1513  - SLIMbus Rates 5 */
	अणु 0x000005EA, 0x0000 पूर्ण,   /* R1514  - SLIMbus Rates 6 */
	अणु 0x000005EB, 0x0000 पूर्ण,   /* R1515  - SLIMbus Rates 7 */
	अणु 0x000005EC, 0x0000 पूर्ण,   /* R1516  - SLIMbus Rates 8 */
	अणु 0x000005F5, 0x0000 पूर्ण,   /* R1525  - SLIMbus RX Channel Enable */
	अणु 0x000005F6, 0x0000 पूर्ण,   /* R1526  - SLIMbus TX Channel Enable */
	अणु 0x00000640, 0x0000 पूर्ण,   /* R1600  - PWM1MIX Input 1 Source */
	अणु 0x00000641, 0x0080 पूर्ण,   /* R1601  - PWM1MIX Input 1 Volume */
	अणु 0x00000642, 0x0000 पूर्ण,   /* R1602  - PWM1MIX Input 2 Source */
	अणु 0x00000643, 0x0080 पूर्ण,   /* R1603  - PWM1MIX Input 2 Volume */
	अणु 0x00000644, 0x0000 पूर्ण,   /* R1604  - PWM1MIX Input 3 Source */
	अणु 0x00000645, 0x0080 पूर्ण,   /* R1605  - PWM1MIX Input 3 Volume */
	अणु 0x00000646, 0x0000 पूर्ण,   /* R1606  - PWM1MIX Input 4 Source */
	अणु 0x00000647, 0x0080 पूर्ण,   /* R1607  - PWM1MIX Input 4 Volume */
	अणु 0x00000648, 0x0000 पूर्ण,   /* R1608  - PWM2MIX Input 1 Source */
	अणु 0x00000649, 0x0080 पूर्ण,   /* R1609  - PWM2MIX Input 1 Volume */
	अणु 0x0000064A, 0x0000 पूर्ण,   /* R1610  - PWM2MIX Input 2 Source */
	अणु 0x0000064B, 0x0080 पूर्ण,   /* R1611  - PWM2MIX Input 2 Volume */
	अणु 0x0000064C, 0x0000 पूर्ण,   /* R1612  - PWM2MIX Input 3 Source */
	अणु 0x0000064D, 0x0080 पूर्ण,   /* R1613  - PWM2MIX Input 3 Volume */
	अणु 0x0000064E, 0x0000 पूर्ण,   /* R1614  - PWM2MIX Input 4 Source */
	अणु 0x0000064F, 0x0080 पूर्ण,   /* R1615  - PWM2MIX Input 4 Volume */
	अणु 0x00000660, 0x0000 पूर्ण,   /* R1632  - MICMIX Input 1 Source */
	अणु 0x00000661, 0x0080 पूर्ण,   /* R1633  - MICMIX Input 1 Volume */
	अणु 0x00000662, 0x0000 पूर्ण,   /* R1634  - MICMIX Input 2 Source */
	अणु 0x00000663, 0x0080 पूर्ण,   /* R1635  - MICMIX Input 2 Volume */
	अणु 0x00000664, 0x0000 पूर्ण,   /* R1636  - MICMIX Input 3 Source */
	अणु 0x00000665, 0x0080 पूर्ण,   /* R1637  - MICMIX Input 3 Volume */
	अणु 0x00000666, 0x0000 पूर्ण,   /* R1638  - MICMIX Input 4 Source */
	अणु 0x00000667, 0x0080 पूर्ण,   /* R1639  - MICMIX Input 4 Volume */
	अणु 0x00000668, 0x0000 पूर्ण,   /* R1640  - NOISEMIX Input 1 Source */
	अणु 0x00000669, 0x0080 पूर्ण,   /* R1641  - NOISEMIX Input 1 Volume */
	अणु 0x0000066A, 0x0000 पूर्ण,   /* R1642  - NOISEMIX Input 2 Source */
	अणु 0x0000066B, 0x0080 पूर्ण,   /* R1643  - NOISEMIX Input 2 Volume */
	अणु 0x0000066C, 0x0000 पूर्ण,   /* R1644  - NOISEMIX Input 3 Source */
	अणु 0x0000066D, 0x0080 पूर्ण,   /* R1645  - NOISEMIX Input 3 Volume */
	अणु 0x0000066E, 0x0000 पूर्ण,   /* R1646  - NOISEMIX Input 4 Source */
	अणु 0x0000066F, 0x0080 पूर्ण,   /* R1647  - NOISEMIX Input 4 Volume */
	अणु 0x00000680, 0x0000 पूर्ण,   /* R1664  - OUT1LMIX Input 1 Source */
	अणु 0x00000681, 0x0080 पूर्ण,   /* R1665  - OUT1LMIX Input 1 Volume */
	अणु 0x00000682, 0x0000 पूर्ण,   /* R1666  - OUT1LMIX Input 2 Source */
	अणु 0x00000683, 0x0080 पूर्ण,   /* R1667  - OUT1LMIX Input 2 Volume */
	अणु 0x00000684, 0x0000 पूर्ण,   /* R1668  - OUT1LMIX Input 3 Source */
	अणु 0x00000685, 0x0080 पूर्ण,   /* R1669  - OUT1LMIX Input 3 Volume */
	अणु 0x00000686, 0x0000 पूर्ण,   /* R1670  - OUT1LMIX Input 4 Source */
	अणु 0x00000687, 0x0080 पूर्ण,   /* R1671  - OUT1LMIX Input 4 Volume */
	अणु 0x00000688, 0x0000 पूर्ण,   /* R1672  - OUT1RMIX Input 1 Source */
	अणु 0x00000689, 0x0080 पूर्ण,   /* R1673  - OUT1RMIX Input 1 Volume */
	अणु 0x0000068A, 0x0000 पूर्ण,   /* R1674  - OUT1RMIX Input 2 Source */
	अणु 0x0000068B, 0x0080 पूर्ण,   /* R1675  - OUT1RMIX Input 2 Volume */
	अणु 0x0000068C, 0x0000 पूर्ण,   /* R1676  - OUT1RMIX Input 3 Source */
	अणु 0x0000068D, 0x0080 पूर्ण,   /* R1677  - OUT1RMIX Input 3 Volume */
	अणु 0x0000068E, 0x0000 पूर्ण,   /* R1678  - OUT1RMIX Input 4 Source */
	अणु 0x0000068F, 0x0080 पूर्ण,   /* R1679  - OUT1RMIX Input 4 Volume */
	अणु 0x00000690, 0x0000 पूर्ण,   /* R1680  - OUT2LMIX Input 1 Source */
	अणु 0x00000691, 0x0080 पूर्ण,   /* R1681  - OUT2LMIX Input 1 Volume */
	अणु 0x00000692, 0x0000 पूर्ण,   /* R1682  - OUT2LMIX Input 2 Source */
	अणु 0x00000693, 0x0080 पूर्ण,   /* R1683  - OUT2LMIX Input 2 Volume */
	अणु 0x00000694, 0x0000 पूर्ण,   /* R1684  - OUT2LMIX Input 3 Source */
	अणु 0x00000695, 0x0080 पूर्ण,   /* R1685  - OUT2LMIX Input 3 Volume */
	अणु 0x00000696, 0x0000 पूर्ण,   /* R1686  - OUT2LMIX Input 4 Source */
	अणु 0x00000697, 0x0080 पूर्ण,   /* R1687  - OUT2LMIX Input 4 Volume */
	अणु 0x00000698, 0x0000 पूर्ण,   /* R1688  - OUT2RMIX Input 1 Source */
	अणु 0x00000699, 0x0080 पूर्ण,   /* R1689  - OUT2RMIX Input 1 Volume */
	अणु 0x0000069A, 0x0000 पूर्ण,   /* R1690  - OUT2RMIX Input 2 Source */
	अणु 0x0000069B, 0x0080 पूर्ण,   /* R1691  - OUT2RMIX Input 2 Volume */
	अणु 0x0000069C, 0x0000 पूर्ण,   /* R1692  - OUT2RMIX Input 3 Source */
	अणु 0x0000069D, 0x0080 पूर्ण,   /* R1693  - OUT2RMIX Input 3 Volume */
	अणु 0x0000069E, 0x0000 पूर्ण,   /* R1694  - OUT2RMIX Input 4 Source */
	अणु 0x0000069F, 0x0080 पूर्ण,   /* R1695  - OUT2RMIX Input 4 Volume */
	अणु 0x000006A0, 0x0000 पूर्ण,   /* R1696  - OUT3LMIX Input 1 Source */
	अणु 0x000006A1, 0x0080 पूर्ण,   /* R1697  - OUT3LMIX Input 1 Volume */
	अणु 0x000006A2, 0x0000 पूर्ण,   /* R1698  - OUT3LMIX Input 2 Source */
	अणु 0x000006A3, 0x0080 पूर्ण,   /* R1699  - OUT3LMIX Input 2 Volume */
	अणु 0x000006A4, 0x0000 पूर्ण,   /* R1700  - OUT3LMIX Input 3 Source */
	अणु 0x000006A5, 0x0080 पूर्ण,   /* R1701  - OUT3LMIX Input 3 Volume */
	अणु 0x000006A6, 0x0000 पूर्ण,   /* R1702  - OUT3LMIX Input 4 Source */
	अणु 0x000006A7, 0x0080 पूर्ण,   /* R1703  - OUT3LMIX Input 4 Volume */
	अणु 0x000006B0, 0x0000 पूर्ण,   /* R1712  - OUT4LMIX Input 1 Source */
	अणु 0x000006B1, 0x0080 पूर्ण,   /* R1713  - OUT4LMIX Input 1 Volume */
	अणु 0x000006B2, 0x0000 पूर्ण,   /* R1714  - OUT4LMIX Input 2 Source */
	अणु 0x000006B3, 0x0080 पूर्ण,   /* R1715  - OUT4LMIX Input 2 Volume */
	अणु 0x000006B4, 0x0000 पूर्ण,   /* R1716  - OUT4LMIX Input 3 Source */
	अणु 0x000006B5, 0x0080 पूर्ण,   /* R1717  - OUT4LMIX Input 3 Volume */
	अणु 0x000006B6, 0x0000 पूर्ण,   /* R1718  - OUT4LMIX Input 4 Source */
	अणु 0x000006B7, 0x0080 पूर्ण,   /* R1719  - OUT4LMIX Input 4 Volume */
	अणु 0x000006B8, 0x0000 पूर्ण,   /* R1720  - OUT4RMIX Input 1 Source */
	अणु 0x000006B9, 0x0080 पूर्ण,   /* R1721  - OUT4RMIX Input 1 Volume */
	अणु 0x000006BA, 0x0000 पूर्ण,   /* R1722  - OUT4RMIX Input 2 Source */
	अणु 0x000006BB, 0x0080 पूर्ण,   /* R1723  - OUT4RMIX Input 2 Volume */
	अणु 0x000006BC, 0x0000 पूर्ण,   /* R1724  - OUT4RMIX Input 3 Source */
	अणु 0x000006BD, 0x0080 पूर्ण,   /* R1725  - OUT4RMIX Input 3 Volume */
	अणु 0x000006BE, 0x0000 पूर्ण,   /* R1726  - OUT4RMIX Input 4 Source */
	अणु 0x000006BF, 0x0080 पूर्ण,   /* R1727  - OUT4RMIX Input 4 Volume */
	अणु 0x000006C0, 0x0000 पूर्ण,   /* R1728  - OUT5LMIX Input 1 Source */
	अणु 0x000006C1, 0x0080 पूर्ण,   /* R1729  - OUT5LMIX Input 1 Volume */
	अणु 0x000006C2, 0x0000 पूर्ण,   /* R1730  - OUT5LMIX Input 2 Source */
	अणु 0x000006C3, 0x0080 पूर्ण,   /* R1731  - OUT5LMIX Input 2 Volume */
	अणु 0x000006C4, 0x0000 पूर्ण,   /* R1732  - OUT5LMIX Input 3 Source */
	अणु 0x000006C5, 0x0080 पूर्ण,   /* R1733  - OUT5LMIX Input 3 Volume */
	अणु 0x000006C6, 0x0000 पूर्ण,   /* R1734  - OUT5LMIX Input 4 Source */
	अणु 0x000006C7, 0x0080 पूर्ण,   /* R1735  - OUT5LMIX Input 4 Volume */
	अणु 0x000006C8, 0x0000 पूर्ण,   /* R1736  - OUT5RMIX Input 1 Source */
	अणु 0x000006C9, 0x0080 पूर्ण,   /* R1737  - OUT5RMIX Input 1 Volume */
	अणु 0x000006CA, 0x0000 पूर्ण,   /* R1738  - OUT5RMIX Input 2 Source */
	अणु 0x000006CB, 0x0080 पूर्ण,   /* R1739  - OUT5RMIX Input 2 Volume */
	अणु 0x000006CC, 0x0000 पूर्ण,   /* R1740  - OUT5RMIX Input 3 Source */
	अणु 0x000006CD, 0x0080 पूर्ण,   /* R1741  - OUT5RMIX Input 3 Volume */
	अणु 0x000006CE, 0x0000 पूर्ण,   /* R1742  - OUT5RMIX Input 4 Source */
	अणु 0x000006CF, 0x0080 पूर्ण,   /* R1743  - OUT5RMIX Input 4 Volume */
	अणु 0x00000700, 0x0000 पूर्ण,   /* R1792  - AIF1TX1MIX Input 1 Source */
	अणु 0x00000701, 0x0080 पूर्ण,   /* R1793  - AIF1TX1MIX Input 1 Volume */
	अणु 0x00000702, 0x0000 पूर्ण,   /* R1794  - AIF1TX1MIX Input 2 Source */
	अणु 0x00000703, 0x0080 पूर्ण,   /* R1795  - AIF1TX1MIX Input 2 Volume */
	अणु 0x00000704, 0x0000 पूर्ण,   /* R1796  - AIF1TX1MIX Input 3 Source */
	अणु 0x00000705, 0x0080 पूर्ण,   /* R1797  - AIF1TX1MIX Input 3 Volume */
	अणु 0x00000706, 0x0000 पूर्ण,   /* R1798  - AIF1TX1MIX Input 4 Source */
	अणु 0x00000707, 0x0080 पूर्ण,   /* R1799  - AIF1TX1MIX Input 4 Volume */
	अणु 0x00000708, 0x0000 पूर्ण,   /* R1800  - AIF1TX2MIX Input 1 Source */
	अणु 0x00000709, 0x0080 पूर्ण,   /* R1801  - AIF1TX2MIX Input 1 Volume */
	अणु 0x0000070A, 0x0000 पूर्ण,   /* R1802  - AIF1TX2MIX Input 2 Source */
	अणु 0x0000070B, 0x0080 पूर्ण,   /* R1803  - AIF1TX2MIX Input 2 Volume */
	अणु 0x0000070C, 0x0000 पूर्ण,   /* R1804  - AIF1TX2MIX Input 3 Source */
	अणु 0x0000070D, 0x0080 पूर्ण,   /* R1805  - AIF1TX2MIX Input 3 Volume */
	अणु 0x0000070E, 0x0000 पूर्ण,   /* R1806  - AIF1TX2MIX Input 4 Source */
	अणु 0x0000070F, 0x0080 पूर्ण,   /* R1807  - AIF1TX2MIX Input 4 Volume */
	अणु 0x00000710, 0x0000 पूर्ण,   /* R1808  - AIF1TX3MIX Input 1 Source */
	अणु 0x00000711, 0x0080 पूर्ण,   /* R1809  - AIF1TX3MIX Input 1 Volume */
	अणु 0x00000712, 0x0000 पूर्ण,   /* R1810  - AIF1TX3MIX Input 2 Source */
	अणु 0x00000713, 0x0080 पूर्ण,   /* R1811  - AIF1TX3MIX Input 2 Volume */
	अणु 0x00000714, 0x0000 पूर्ण,   /* R1812  - AIF1TX3MIX Input 3 Source */
	अणु 0x00000715, 0x0080 पूर्ण,   /* R1813  - AIF1TX3MIX Input 3 Volume */
	अणु 0x00000716, 0x0000 पूर्ण,   /* R1814  - AIF1TX3MIX Input 4 Source */
	अणु 0x00000717, 0x0080 पूर्ण,   /* R1815  - AIF1TX3MIX Input 4 Volume */
	अणु 0x00000718, 0x0000 पूर्ण,   /* R1816  - AIF1TX4MIX Input 1 Source */
	अणु 0x00000719, 0x0080 पूर्ण,   /* R1817  - AIF1TX4MIX Input 1 Volume */
	अणु 0x0000071A, 0x0000 पूर्ण,   /* R1818  - AIF1TX4MIX Input 2 Source */
	अणु 0x0000071B, 0x0080 पूर्ण,   /* R1819  - AIF1TX4MIX Input 2 Volume */
	अणु 0x0000071C, 0x0000 पूर्ण,   /* R1820  - AIF1TX4MIX Input 3 Source */
	अणु 0x0000071D, 0x0080 पूर्ण,   /* R1821  - AIF1TX4MIX Input 3 Volume */
	अणु 0x0000071E, 0x0000 पूर्ण,   /* R1822  - AIF1TX4MIX Input 4 Source */
	अणु 0x0000071F, 0x0080 पूर्ण,   /* R1823  - AIF1TX4MIX Input 4 Volume */
	अणु 0x00000720, 0x0000 पूर्ण,   /* R1824  - AIF1TX5MIX Input 1 Source */
	अणु 0x00000721, 0x0080 पूर्ण,   /* R1825  - AIF1TX5MIX Input 1 Volume */
	अणु 0x00000722, 0x0000 पूर्ण,   /* R1826  - AIF1TX5MIX Input 2 Source */
	अणु 0x00000723, 0x0080 पूर्ण,   /* R1827  - AIF1TX5MIX Input 2 Volume */
	अणु 0x00000724, 0x0000 पूर्ण,   /* R1828  - AIF1TX5MIX Input 3 Source */
	अणु 0x00000725, 0x0080 पूर्ण,   /* R1829  - AIF1TX5MIX Input 3 Volume */
	अणु 0x00000726, 0x0000 पूर्ण,   /* R1830  - AIF1TX5MIX Input 4 Source */
	अणु 0x00000727, 0x0080 पूर्ण,   /* R1831  - AIF1TX5MIX Input 4 Volume */
	अणु 0x00000728, 0x0000 पूर्ण,   /* R1832  - AIF1TX6MIX Input 1 Source */
	अणु 0x00000729, 0x0080 पूर्ण,   /* R1833  - AIF1TX6MIX Input 1 Volume */
	अणु 0x0000072A, 0x0000 पूर्ण,   /* R1834  - AIF1TX6MIX Input 2 Source */
	अणु 0x0000072B, 0x0080 पूर्ण,   /* R1835  - AIF1TX6MIX Input 2 Volume */
	अणु 0x0000072C, 0x0000 पूर्ण,   /* R1836  - AIF1TX6MIX Input 3 Source */
	अणु 0x0000072D, 0x0080 पूर्ण,   /* R1837  - AIF1TX6MIX Input 3 Volume */
	अणु 0x0000072E, 0x0000 पूर्ण,   /* R1838  - AIF1TX6MIX Input 4 Source */
	अणु 0x0000072F, 0x0080 पूर्ण,   /* R1839  - AIF1TX6MIX Input 4 Volume */
	अणु 0x00000730, 0x0000 पूर्ण,   /* R1840  - AIF1TX7MIX Input 1 Source */
	अणु 0x00000731, 0x0080 पूर्ण,   /* R1841  - AIF1TX7MIX Input 1 Volume */
	अणु 0x00000732, 0x0000 पूर्ण,   /* R1842  - AIF1TX7MIX Input 2 Source */
	अणु 0x00000733, 0x0080 पूर्ण,   /* R1843  - AIF1TX7MIX Input 2 Volume */
	अणु 0x00000734, 0x0000 पूर्ण,   /* R1844  - AIF1TX7MIX Input 3 Source */
	अणु 0x00000735, 0x0080 पूर्ण,   /* R1845  - AIF1TX7MIX Input 3 Volume */
	अणु 0x00000736, 0x0000 पूर्ण,   /* R1846  - AIF1TX7MIX Input 4 Source */
	अणु 0x00000737, 0x0080 पूर्ण,   /* R1847  - AIF1TX7MIX Input 4 Volume */
	अणु 0x00000738, 0x0000 पूर्ण,   /* R1848  - AIF1TX8MIX Input 1 Source */
	अणु 0x00000739, 0x0080 पूर्ण,   /* R1849  - AIF1TX8MIX Input 1 Volume */
	अणु 0x0000073A, 0x0000 पूर्ण,   /* R1850  - AIF1TX8MIX Input 2 Source */
	अणु 0x0000073B, 0x0080 पूर्ण,   /* R1851  - AIF1TX8MIX Input 2 Volume */
	अणु 0x0000073C, 0x0000 पूर्ण,   /* R1852  - AIF1TX8MIX Input 3 Source */
	अणु 0x0000073D, 0x0080 पूर्ण,   /* R1853  - AIF1TX8MIX Input 3 Volume */
	अणु 0x0000073E, 0x0000 पूर्ण,   /* R1854  - AIF1TX8MIX Input 4 Source */
	अणु 0x0000073F, 0x0080 पूर्ण,   /* R1855  - AIF1TX8MIX Input 4 Volume */
	अणु 0x00000740, 0x0000 पूर्ण,   /* R1856  - AIF2TX1MIX Input 1 Source */
	अणु 0x00000741, 0x0080 पूर्ण,   /* R1857  - AIF2TX1MIX Input 1 Volume */
	अणु 0x00000742, 0x0000 पूर्ण,   /* R1858  - AIF2TX1MIX Input 2 Source */
	अणु 0x00000743, 0x0080 पूर्ण,   /* R1859  - AIF2TX1MIX Input 2 Volume */
	अणु 0x00000744, 0x0000 पूर्ण,   /* R1860  - AIF2TX1MIX Input 3 Source */
	अणु 0x00000745, 0x0080 पूर्ण,   /* R1861  - AIF2TX1MIX Input 3 Volume */
	अणु 0x00000746, 0x0000 पूर्ण,   /* R1862  - AIF2TX1MIX Input 4 Source */
	अणु 0x00000747, 0x0080 पूर्ण,   /* R1863  - AIF2TX1MIX Input 4 Volume */
	अणु 0x00000748, 0x0000 पूर्ण,   /* R1864  - AIF2TX2MIX Input 1 Source */
	अणु 0x00000749, 0x0080 पूर्ण,   /* R1865  - AIF2TX2MIX Input 1 Volume */
	अणु 0x0000074A, 0x0000 पूर्ण,   /* R1866  - AIF2TX2MIX Input 2 Source */
	अणु 0x0000074B, 0x0080 पूर्ण,   /* R1867  - AIF2TX2MIX Input 2 Volume */
	अणु 0x0000074C, 0x0000 पूर्ण,   /* R1868  - AIF2TX2MIX Input 3 Source */
	अणु 0x0000074D, 0x0080 पूर्ण,   /* R1869  - AIF2TX2MIX Input 3 Volume */
	अणु 0x0000074E, 0x0000 पूर्ण,   /* R1870  - AIF2TX2MIX Input 4 Source */
	अणु 0x0000074F, 0x0080 पूर्ण,   /* R1871  - AIF2TX2MIX Input 4 Volume */
	अणु 0x00000780, 0x0000 पूर्ण,   /* R1920  - AIF3TX1MIX Input 1 Source */
	अणु 0x00000781, 0x0080 पूर्ण,   /* R1921  - AIF3TX1MIX Input 1 Volume */
	अणु 0x00000782, 0x0000 पूर्ण,   /* R1922  - AIF3TX1MIX Input 2 Source */
	अणु 0x00000783, 0x0080 पूर्ण,   /* R1923  - AIF3TX1MIX Input 2 Volume */
	अणु 0x00000784, 0x0000 पूर्ण,   /* R1924  - AIF3TX1MIX Input 3 Source */
	अणु 0x00000785, 0x0080 पूर्ण,   /* R1925  - AIF3TX1MIX Input 3 Volume */
	अणु 0x00000786, 0x0000 पूर्ण,   /* R1926  - AIF3TX1MIX Input 4 Source */
	अणु 0x00000787, 0x0080 पूर्ण,   /* R1927  - AIF3TX1MIX Input 4 Volume */
	अणु 0x00000788, 0x0000 पूर्ण,   /* R1928  - AIF3TX2MIX Input 1 Source */
	अणु 0x00000789, 0x0080 पूर्ण,   /* R1929  - AIF3TX2MIX Input 1 Volume */
	अणु 0x0000078A, 0x0000 पूर्ण,   /* R1930  - AIF3TX2MIX Input 2 Source */
	अणु 0x0000078B, 0x0080 पूर्ण,   /* R1931  - AIF3TX2MIX Input 2 Volume */
	अणु 0x0000078C, 0x0000 पूर्ण,   /* R1932  - AIF3TX2MIX Input 3 Source */
	अणु 0x0000078D, 0x0080 पूर्ण,   /* R1933  - AIF3TX2MIX Input 3 Volume */
	अणु 0x0000078E, 0x0000 पूर्ण,   /* R1934  - AIF3TX2MIX Input 4 Source */
	अणु 0x0000078F, 0x0080 पूर्ण,   /* R1935  - AIF3TX2MIX Input 4 Volume */
	अणु 0x000007C0, 0x0000 पूर्ण,   /* R1984  - SLIMTX1MIX Input 1 Source */
	अणु 0x000007C1, 0x0080 पूर्ण,   /* R1985  - SLIMTX1MIX Input 1 Volume */
	अणु 0x000007C2, 0x0000 पूर्ण,   /* R1986  - SLIMTX1MIX Input 2 Source */
	अणु 0x000007C3, 0x0080 पूर्ण,   /* R1987  - SLIMTX1MIX Input 2 Volume */
	अणु 0x000007C4, 0x0000 पूर्ण,   /* R1988  - SLIMTX1MIX Input 3 Source */
	अणु 0x000007C5, 0x0080 पूर्ण,   /* R1989  - SLIMTX1MIX Input 3 Volume */
	अणु 0x000007C6, 0x0000 पूर्ण,   /* R1990  - SLIMTX1MIX Input 4 Source */
	अणु 0x000007C7, 0x0080 पूर्ण,   /* R1991  - SLIMTX1MIX Input 4 Volume */
	अणु 0x000007C8, 0x0000 पूर्ण,   /* R1992  - SLIMTX2MIX Input 1 Source */
	अणु 0x000007C9, 0x0080 पूर्ण,   /* R1993  - SLIMTX2MIX Input 1 Volume */
	अणु 0x000007CA, 0x0000 पूर्ण,   /* R1994  - SLIMTX2MIX Input 2 Source */
	अणु 0x000007CB, 0x0080 पूर्ण,   /* R1995  - SLIMTX2MIX Input 2 Volume */
	अणु 0x000007CC, 0x0000 पूर्ण,   /* R1996  - SLIMTX2MIX Input 3 Source */
	अणु 0x000007CD, 0x0080 पूर्ण,   /* R1997  - SLIMTX2MIX Input 3 Volume */
	अणु 0x000007CE, 0x0000 पूर्ण,   /* R1998  - SLIMTX2MIX Input 4 Source */
	अणु 0x000007CF, 0x0080 पूर्ण,   /* R1999  - SLIMTX2MIX Input 4 Volume */
	अणु 0x000007D0, 0x0000 पूर्ण,   /* R2000  - SLIMTX3MIX Input 1 Source */
	अणु 0x000007D1, 0x0080 पूर्ण,   /* R2001  - SLIMTX3MIX Input 1 Volume */
	अणु 0x000007D2, 0x0000 पूर्ण,   /* R2002  - SLIMTX3MIX Input 2 Source */
	अणु 0x000007D3, 0x0080 पूर्ण,   /* R2003  - SLIMTX3MIX Input 2 Volume */
	अणु 0x000007D4, 0x0000 पूर्ण,   /* R2004  - SLIMTX3MIX Input 3 Source */
	अणु 0x000007D5, 0x0080 पूर्ण,   /* R2005  - SLIMTX3MIX Input 3 Volume */
	अणु 0x000007D6, 0x0000 पूर्ण,   /* R2006  - SLIMTX3MIX Input 4 Source */
	अणु 0x000007D7, 0x0080 पूर्ण,   /* R2007  - SLIMTX3MIX Input 4 Volume */
	अणु 0x000007D8, 0x0000 पूर्ण,   /* R2008  - SLIMTX4MIX Input 1 Source */
	अणु 0x000007D9, 0x0080 पूर्ण,   /* R2009  - SLIMTX4MIX Input 1 Volume */
	अणु 0x000007DA, 0x0000 पूर्ण,   /* R2010  - SLIMTX4MIX Input 2 Source */
	अणु 0x000007DB, 0x0080 पूर्ण,   /* R2011  - SLIMTX4MIX Input 2 Volume */
	अणु 0x000007DC, 0x0000 पूर्ण,   /* R2012  - SLIMTX4MIX Input 3 Source */
	अणु 0x000007DD, 0x0080 पूर्ण,   /* R2013  - SLIMTX4MIX Input 3 Volume */
	अणु 0x000007DE, 0x0000 पूर्ण,   /* R2014  - SLIMTX4MIX Input 4 Source */
	अणु 0x000007DF, 0x0080 पूर्ण,   /* R2015  - SLIMTX4MIX Input 4 Volume */
	अणु 0x000007E0, 0x0000 पूर्ण,   /* R2016  - SLIMTX5MIX Input 1 Source */
	अणु 0x000007E1, 0x0080 पूर्ण,   /* R2017  - SLIMTX5MIX Input 1 Volume */
	अणु 0x000007E2, 0x0000 पूर्ण,   /* R2018  - SLIMTX5MIX Input 2 Source */
	अणु 0x000007E3, 0x0080 पूर्ण,   /* R2019  - SLIMTX5MIX Input 2 Volume */
	अणु 0x000007E4, 0x0000 पूर्ण,   /* R2020  - SLIMTX5MIX Input 3 Source */
	अणु 0x000007E5, 0x0080 पूर्ण,   /* R2021  - SLIMTX5MIX Input 3 Volume */
	अणु 0x000007E6, 0x0000 पूर्ण,   /* R2022  - SLIMTX5MIX Input 4 Source */
	अणु 0x000007E7, 0x0080 पूर्ण,   /* R2023  - SLIMTX5MIX Input 4 Volume */
	अणु 0x000007E8, 0x0000 पूर्ण,   /* R2024  - SLIMTX6MIX Input 1 Source */
	अणु 0x000007E9, 0x0080 पूर्ण,   /* R2025  - SLIMTX6MIX Input 1 Volume */
	अणु 0x000007EA, 0x0000 पूर्ण,   /* R2026  - SLIMTX6MIX Input 2 Source */
	अणु 0x000007EB, 0x0080 पूर्ण,   /* R2027  - SLIMTX6MIX Input 2 Volume */
	अणु 0x000007EC, 0x0000 पूर्ण,   /* R2028  - SLIMTX6MIX Input 3 Source */
	अणु 0x000007ED, 0x0080 पूर्ण,   /* R2029  - SLIMTX6MIX Input 3 Volume */
	अणु 0x000007EE, 0x0000 पूर्ण,   /* R2030  - SLIMTX6MIX Input 4 Source */
	अणु 0x000007EF, 0x0080 पूर्ण,   /* R2031  - SLIMTX6MIX Input 4 Volume */
	अणु 0x000007F0, 0x0000 पूर्ण,   /* R2032  - SLIMTX7MIX Input 1 Source */
	अणु 0x000007F1, 0x0080 पूर्ण,   /* R2033  - SLIMTX7MIX Input 1 Volume */
	अणु 0x000007F2, 0x0000 पूर्ण,   /* R2034  - SLIMTX7MIX Input 2 Source */
	अणु 0x000007F3, 0x0080 पूर्ण,   /* R2035  - SLIMTX7MIX Input 2 Volume */
	अणु 0x000007F4, 0x0000 पूर्ण,   /* R2036  - SLIMTX7MIX Input 3 Source */
	अणु 0x000007F5, 0x0080 पूर्ण,   /* R2037  - SLIMTX7MIX Input 3 Volume */
	अणु 0x000007F6, 0x0000 पूर्ण,   /* R2038  - SLIMTX7MIX Input 4 Source */
	अणु 0x000007F7, 0x0080 पूर्ण,   /* R2039  - SLIMTX7MIX Input 4 Volume */
	अणु 0x000007F8, 0x0000 पूर्ण,   /* R2040  - SLIMTX8MIX Input 1 Source */
	अणु 0x000007F9, 0x0080 पूर्ण,   /* R2041  - SLIMTX8MIX Input 1 Volume */
	अणु 0x000007FA, 0x0000 पूर्ण,   /* R2042  - SLIMTX8MIX Input 2 Source */
	अणु 0x000007FB, 0x0080 पूर्ण,   /* R2043  - SLIMTX8MIX Input 2 Volume */
	अणु 0x000007FC, 0x0000 पूर्ण,   /* R2044  - SLIMTX8MIX Input 3 Source */
	अणु 0x000007FD, 0x0080 पूर्ण,   /* R2045  - SLIMTX8MIX Input 3 Volume */
	अणु 0x000007FE, 0x0000 पूर्ण,   /* R2046  - SLIMTX8MIX Input 4 Source */
	अणु 0x000007FF, 0x0080 पूर्ण,   /* R2047  - SLIMTX8MIX Input 4 Volume */
	अणु 0x00000880, 0x0000 पूर्ण,   /* R2176  - EQ1MIX Input 1 Source */
	अणु 0x00000881, 0x0080 पूर्ण,   /* R2177  - EQ1MIX Input 1 Volume */
	अणु 0x00000882, 0x0000 पूर्ण,   /* R2178  - EQ1MIX Input 2 Source */
	अणु 0x00000883, 0x0080 पूर्ण,   /* R2179  - EQ1MIX Input 2 Volume */
	अणु 0x00000884, 0x0000 पूर्ण,   /* R2180  - EQ1MIX Input 3 Source */
	अणु 0x00000885, 0x0080 पूर्ण,   /* R2181  - EQ1MIX Input 3 Volume */
	अणु 0x00000886, 0x0000 पूर्ण,   /* R2182  - EQ1MIX Input 4 Source */
	अणु 0x00000887, 0x0080 पूर्ण,   /* R2183  - EQ1MIX Input 4 Volume */
	अणु 0x00000888, 0x0000 पूर्ण,   /* R2184  - EQ2MIX Input 1 Source */
	अणु 0x00000889, 0x0080 पूर्ण,   /* R2185  - EQ2MIX Input 1 Volume */
	अणु 0x0000088A, 0x0000 पूर्ण,   /* R2186  - EQ2MIX Input 2 Source */
	अणु 0x0000088B, 0x0080 पूर्ण,   /* R2187  - EQ2MIX Input 2 Volume */
	अणु 0x0000088C, 0x0000 पूर्ण,   /* R2188  - EQ2MIX Input 3 Source */
	अणु 0x0000088D, 0x0080 पूर्ण,   /* R2189  - EQ2MIX Input 3 Volume */
	अणु 0x0000088E, 0x0000 पूर्ण,   /* R2190  - EQ2MIX Input 4 Source */
	अणु 0x0000088F, 0x0080 पूर्ण,   /* R2191  - EQ2MIX Input 4 Volume */
	अणु 0x00000890, 0x0000 पूर्ण,   /* R2192  - EQ3MIX Input 1 Source */
	अणु 0x00000891, 0x0080 पूर्ण,   /* R2193  - EQ3MIX Input 1 Volume */
	अणु 0x00000892, 0x0000 पूर्ण,   /* R2194  - EQ3MIX Input 2 Source */
	अणु 0x00000893, 0x0080 पूर्ण,   /* R2195  - EQ3MIX Input 2 Volume */
	अणु 0x00000894, 0x0000 पूर्ण,   /* R2196  - EQ3MIX Input 3 Source */
	अणु 0x00000895, 0x0080 पूर्ण,   /* R2197  - EQ3MIX Input 3 Volume */
	अणु 0x00000896, 0x0000 पूर्ण,   /* R2198  - EQ3MIX Input 4 Source */
	अणु 0x00000897, 0x0080 पूर्ण,   /* R2199  - EQ3MIX Input 4 Volume */
	अणु 0x00000898, 0x0000 पूर्ण,   /* R2200  - EQ4MIX Input 1 Source */
	अणु 0x00000899, 0x0080 पूर्ण,   /* R2201  - EQ4MIX Input 1 Volume */
	अणु 0x0000089A, 0x0000 पूर्ण,   /* R2202  - EQ4MIX Input 2 Source */
	अणु 0x0000089B, 0x0080 पूर्ण,   /* R2203  - EQ4MIX Input 2 Volume */
	अणु 0x0000089C, 0x0000 पूर्ण,   /* R2204  - EQ4MIX Input 3 Source */
	अणु 0x0000089D, 0x0080 पूर्ण,   /* R2205  - EQ4MIX Input 3 Volume */
	अणु 0x0000089E, 0x0000 पूर्ण,   /* R2206  - EQ4MIX Input 4 Source */
	अणु 0x0000089F, 0x0080 पूर्ण,   /* R2207  - EQ4MIX Input 4 Volume */
	अणु 0x000008C0, 0x0000 पूर्ण,   /* R2240  - DRC1LMIX Input 1 Source */
	अणु 0x000008C1, 0x0080 पूर्ण,   /* R2241  - DRC1LMIX Input 1 Volume */
	अणु 0x000008C2, 0x0000 पूर्ण,   /* R2242  - DRC1LMIX Input 2 Source */
	अणु 0x000008C3, 0x0080 पूर्ण,   /* R2243  - DRC1LMIX Input 2 Volume */
	अणु 0x000008C4, 0x0000 पूर्ण,   /* R2244  - DRC1LMIX Input 3 Source */
	अणु 0x000008C5, 0x0080 पूर्ण,   /* R2245  - DRC1LMIX Input 3 Volume */
	अणु 0x000008C6, 0x0000 पूर्ण,   /* R2246  - DRC1LMIX Input 4 Source */
	अणु 0x000008C7, 0x0080 पूर्ण,   /* R2247  - DRC1LMIX Input 4 Volume */
	अणु 0x000008C8, 0x0000 पूर्ण,   /* R2248  - DRC1RMIX Input 1 Source */
	अणु 0x000008C9, 0x0080 पूर्ण,   /* R2249  - DRC1RMIX Input 1 Volume */
	अणु 0x000008CA, 0x0000 पूर्ण,   /* R2250  - DRC1RMIX Input 2 Source */
	अणु 0x000008CB, 0x0080 पूर्ण,   /* R2251  - DRC1RMIX Input 2 Volume */
	अणु 0x000008CC, 0x0000 पूर्ण,   /* R2252  - DRC1RMIX Input 3 Source */
	अणु 0x000008CD, 0x0080 पूर्ण,   /* R2253  - DRC1RMIX Input 3 Volume */
	अणु 0x000008CE, 0x0000 पूर्ण,   /* R2254  - DRC1RMIX Input 4 Source */
	अणु 0x000008CF, 0x0080 पूर्ण,   /* R2255  - DRC1RMIX Input 4 Volume */
	अणु 0x00000900, 0x0000 पूर्ण,   /* R2304  - HPLP1MIX Input 1 Source */
	अणु 0x00000901, 0x0080 पूर्ण,   /* R2305  - HPLP1MIX Input 1 Volume */
	अणु 0x00000902, 0x0000 पूर्ण,   /* R2306  - HPLP1MIX Input 2 Source */
	अणु 0x00000903, 0x0080 पूर्ण,   /* R2307  - HPLP1MIX Input 2 Volume */
	अणु 0x00000904, 0x0000 पूर्ण,   /* R2308  - HPLP1MIX Input 3 Source */
	अणु 0x00000905, 0x0080 पूर्ण,   /* R2309  - HPLP1MIX Input 3 Volume */
	अणु 0x00000906, 0x0000 पूर्ण,   /* R2310  - HPLP1MIX Input 4 Source */
	अणु 0x00000907, 0x0080 पूर्ण,   /* R2311  - HPLP1MIX Input 4 Volume */
	अणु 0x00000908, 0x0000 पूर्ण,   /* R2312  - HPLP2MIX Input 1 Source */
	अणु 0x00000909, 0x0080 पूर्ण,   /* R2313  - HPLP2MIX Input 1 Volume */
	अणु 0x0000090A, 0x0000 पूर्ण,   /* R2314  - HPLP2MIX Input 2 Source */
	अणु 0x0000090B, 0x0080 पूर्ण,   /* R2315  - HPLP2MIX Input 2 Volume */
	अणु 0x0000090C, 0x0000 पूर्ण,   /* R2316  - HPLP2MIX Input 3 Source */
	अणु 0x0000090D, 0x0080 पूर्ण,   /* R2317  - HPLP2MIX Input 3 Volume */
	अणु 0x0000090E, 0x0000 पूर्ण,   /* R2318  - HPLP2MIX Input 4 Source */
	अणु 0x0000090F, 0x0080 पूर्ण,   /* R2319  - HPLP2MIX Input 4 Volume */
	अणु 0x00000910, 0x0000 पूर्ण,   /* R2320  - HPLP3MIX Input 1 Source */
	अणु 0x00000911, 0x0080 पूर्ण,   /* R2321  - HPLP3MIX Input 1 Volume */
	अणु 0x00000912, 0x0000 पूर्ण,   /* R2322  - HPLP3MIX Input 2 Source */
	अणु 0x00000913, 0x0080 पूर्ण,   /* R2323  - HPLP3MIX Input 2 Volume */
	अणु 0x00000914, 0x0000 पूर्ण,   /* R2324  - HPLP3MIX Input 3 Source */
	अणु 0x00000915, 0x0080 पूर्ण,   /* R2325  - HPLP3MIX Input 3 Volume */
	अणु 0x00000916, 0x0000 पूर्ण,   /* R2326  - HPLP3MIX Input 4 Source */
	अणु 0x00000917, 0x0080 पूर्ण,   /* R2327  - HPLP3MIX Input 4 Volume */
	अणु 0x00000918, 0x0000 पूर्ण,   /* R2328  - HPLP4MIX Input 1 Source */
	अणु 0x00000919, 0x0080 पूर्ण,   /* R2329  - HPLP4MIX Input 1 Volume */
	अणु 0x0000091A, 0x0000 पूर्ण,   /* R2330  - HPLP4MIX Input 2 Source */
	अणु 0x0000091B, 0x0080 पूर्ण,   /* R2331  - HPLP4MIX Input 2 Volume */
	अणु 0x0000091C, 0x0000 पूर्ण,   /* R2332  - HPLP4MIX Input 3 Source */
	अणु 0x0000091D, 0x0080 पूर्ण,   /* R2333  - HPLP4MIX Input 3 Volume */
	अणु 0x0000091E, 0x0000 पूर्ण,   /* R2334  - HPLP4MIX Input 4 Source */
	अणु 0x0000091F, 0x0080 पूर्ण,   /* R2335  - HPLP4MIX Input 4 Volume */
	अणु 0x00000940, 0x0000 पूर्ण,   /* R2368  - DSP1LMIX Input 1 Source */
	अणु 0x00000941, 0x0080 पूर्ण,   /* R2369  - DSP1LMIX Input 1 Volume */
	अणु 0x00000942, 0x0000 पूर्ण,   /* R2370  - DSP1LMIX Input 2 Source */
	अणु 0x00000943, 0x0080 पूर्ण,   /* R2371  - DSP1LMIX Input 2 Volume */
	अणु 0x00000944, 0x0000 पूर्ण,   /* R2372  - DSP1LMIX Input 3 Source */
	अणु 0x00000945, 0x0080 पूर्ण,   /* R2373  - DSP1LMIX Input 3 Volume */
	अणु 0x00000946, 0x0000 पूर्ण,   /* R2374  - DSP1LMIX Input 4 Source */
	अणु 0x00000947, 0x0080 पूर्ण,   /* R2375  - DSP1LMIX Input 4 Volume */
	अणु 0x00000948, 0x0000 पूर्ण,   /* R2376  - DSP1RMIX Input 1 Source */
	अणु 0x00000949, 0x0080 पूर्ण,   /* R2377  - DSP1RMIX Input 1 Volume */
	अणु 0x0000094A, 0x0000 पूर्ण,   /* R2378  - DSP1RMIX Input 2 Source */
	अणु 0x0000094B, 0x0080 पूर्ण,   /* R2379  - DSP1RMIX Input 2 Volume */
	अणु 0x0000094C, 0x0000 पूर्ण,   /* R2380  - DSP1RMIX Input 3 Source */
	अणु 0x0000094D, 0x0080 पूर्ण,   /* R2381  - DSP1RMIX Input 3 Volume */
	अणु 0x0000094E, 0x0000 पूर्ण,   /* R2382  - DSP1RMIX Input 4 Source */
	अणु 0x0000094F, 0x0080 पूर्ण,   /* R2383  - DSP1RMIX Input 4 Volume */
	अणु 0x00000950, 0x0000 पूर्ण,   /* R2384  - DSP1AUX1MIX Input 1 Source */
	अणु 0x00000958, 0x0000 पूर्ण,   /* R2392  - DSP1AUX2MIX Input 1 Source */
	अणु 0x00000960, 0x0000 पूर्ण,   /* R2400  - DSP1AUX3MIX Input 1 Source */
	अणु 0x00000968, 0x0000 पूर्ण,   /* R2408  - DSP1AUX4MIX Input 1 Source */
	अणु 0x00000970, 0x0000 पूर्ण,   /* R2416  - DSP1AUX5MIX Input 1 Source */
	अणु 0x00000978, 0x0000 पूर्ण,   /* R2424  - DSP1AUX6MIX Input 1 Source */
	अणु 0x00000A80, 0x0000 पूर्ण,   /* R2688  - ASRC1LMIX Input 1 Source */
	अणु 0x00000A88, 0x0000 पूर्ण,   /* R2696  - ASRC1RMIX Input 1 Source */
	अणु 0x00000A90, 0x0000 पूर्ण,   /* R2704  - ASRC2LMIX Input 1 Source */
	अणु 0x00000A98, 0x0000 पूर्ण,   /* R2712  - ASRC2RMIX Input 1 Source */
	अणु 0x00000B00, 0x0000 पूर्ण,   /* R2816  - ISRC1DEC1MIX Input 1 Source */
	अणु 0x00000B08, 0x0000 पूर्ण,   /* R2824  - ISRC1DEC2MIX Input 1 Source */
	अणु 0x00000B20, 0x0000 पूर्ण,   /* R2848  - ISRC1INT1MIX Input 1 Source */
	अणु 0x00000B28, 0x0000 पूर्ण,   /* R2856  - ISRC1INT2MIX Input 1 Source */
	अणु 0x00000B40, 0x0000 पूर्ण,   /* R2880  - ISRC2DEC1MIX Input 1 Source */
	अणु 0x00000B48, 0x0000 पूर्ण,   /* R2888  - ISRC2DEC2MIX Input 1 Source */
	अणु 0x00000B60, 0x0000 पूर्ण,   /* R2912  - ISRC2INT1MIX Input 1 Source */
	अणु 0x00000B68, 0x0000 पूर्ण,   /* R2920  - ISRC2INT2MIX Input 1 Source */
	अणु 0x00000C00, 0xA101 पूर्ण,   /* R3072  - GPIO1 CTRL */
	अणु 0x00000C01, 0xA101 पूर्ण,   /* R3073  - GPIO2 CTRL */
	अणु 0x00000C02, 0xA101 पूर्ण,   /* R3074  - GPIO3 CTRL */
	अणु 0x00000C03, 0xA101 पूर्ण,   /* R3075  - GPIO4 CTRL */
	अणु 0x00000C04, 0xA101 पूर्ण,   /* R3076  - GPIO5 CTRL */
	अणु 0x00000C0F, 0x0400 पूर्ण,   /* R3087  - IRQ CTRL 1 */
	अणु 0x00000C10, 0x1000 पूर्ण,   /* R3088  - GPIO Debounce Config */
	अणु 0x00000C20, 0x8002 पूर्ण,   /* R3104  - Misc Pad Ctrl 1 */
	अणु 0x00000C21, 0x0001 पूर्ण,   /* R3105  - Misc Pad Ctrl 2 */
	अणु 0x00000C22, 0x0000 पूर्ण,   /* R3106  - Misc Pad Ctrl 3 */
	अणु 0x00000C23, 0x0000 पूर्ण,   /* R3107  - Misc Pad Ctrl 4 */
	अणु 0x00000C24, 0x0000 पूर्ण,   /* R3108  - Misc Pad Ctrl 5 */
	अणु 0x00000C25, 0x0000 पूर्ण,   /* R3109  - Misc Pad Ctrl 6 */
	अणु 0x00000D08, 0xFFFF पूर्ण,   /* R3336  - Interrupt Status 1 Mask */
	अणु 0x00000D09, 0xFFFF पूर्ण,   /* R3337  - Interrupt Status 2 Mask */
	अणु 0x00000D0A, 0xFFFF पूर्ण,   /* R3338  - Interrupt Status 3 Mask */
	अणु 0x00000D0B, 0xFFFF पूर्ण,   /* R3339  - Interrupt Status 4 Mask */
	अणु 0x00000D0C, 0xFEFF पूर्ण,   /* R3340  - Interrupt Status 5 Mask */
	अणु 0x00000D0F, 0x0000 पूर्ण,   /* R3343  - Interrupt Control */
	अणु 0x00000D18, 0xFFFF पूर्ण,   /* R3352  - IRQ2 Status 1 Mask */
	अणु 0x00000D19, 0xFFFF पूर्ण,   /* R3353  - IRQ2 Status 2 Mask */
	अणु 0x00000D1A, 0xFFFF पूर्ण,   /* R3354  - IRQ2 Status 3 Mask */
	अणु 0x00000D1B, 0xFFFF पूर्ण,   /* R3355  - IRQ2 Status 4 Mask */
	अणु 0x00000D1C, 0xFFFF पूर्ण,   /* R3356  - IRQ2 Status 5 Mask */
	अणु 0x00000D1F, 0x0000 पूर्ण,   /* R3359  - IRQ2 Control */
	अणु 0x00000D41, 0x0000 पूर्ण,   /* R3393  - ADSP2 IRQ0 */
	अणु 0x00000D53, 0xFFFF पूर्ण,   /* R3411  - AOD IRQ Mask IRQ1 */
	अणु 0x00000D54, 0xFFFF पूर्ण,   /* R3412  - AOD IRQ Mask IRQ2 */
	अणु 0x00000D56, 0x0000 पूर्ण,   /* R3414  - Jack detect debounce */
	अणु 0x00000E00, 0x0000 पूर्ण,   /* R3584  - FX_Ctrl1 */
	अणु 0x00000E10, 0x6318 पूर्ण,   /* R3600  - EQ1_1 */
	अणु 0x00000E11, 0x6300 पूर्ण,   /* R3601  - EQ1_2 */
	अणु 0x00000E12, 0x0FC8 पूर्ण,   /* R3602  - EQ1_3 */
	अणु 0x00000E13, 0x03FE पूर्ण,   /* R3603  - EQ1_4 */
	अणु 0x00000E14, 0x00E0 पूर्ण,   /* R3604  - EQ1_5 */
	अणु 0x00000E15, 0x1EC4 पूर्ण,   /* R3605  - EQ1_6 */
	अणु 0x00000E16, 0xF136 पूर्ण,   /* R3606  - EQ1_7 */
	अणु 0x00000E17, 0x0409 पूर्ण,   /* R3607  - EQ1_8 */
	अणु 0x00000E18, 0x04CC पूर्ण,   /* R3608  - EQ1_9 */
	अणु 0x00000E19, 0x1C9B पूर्ण,   /* R3609  - EQ1_10 */
	अणु 0x00000E1A, 0xF337 पूर्ण,   /* R3610  - EQ1_11 */
	अणु 0x00000E1B, 0x040B पूर्ण,   /* R3611  - EQ1_12 */
	अणु 0x00000E1C, 0x0CBB पूर्ण,   /* R3612  - EQ1_13 */
	अणु 0x00000E1D, 0x16F8 पूर्ण,   /* R3613  - EQ1_14 */
	अणु 0x00000E1E, 0xF7D9 पूर्ण,   /* R3614  - EQ1_15 */
	अणु 0x00000E1F, 0x040A पूर्ण,   /* R3615  - EQ1_16 */
	अणु 0x00000E20, 0x1F14 पूर्ण,   /* R3616  - EQ1_17 */
	अणु 0x00000E21, 0x058C पूर्ण,   /* R3617  - EQ1_18 */
	अणु 0x00000E22, 0x0563 पूर्ण,   /* R3618  - EQ1_19 */
	अणु 0x00000E23, 0x4000 पूर्ण,   /* R3619  - EQ1_20 */
	अणु 0x00000E24, 0x0B75 पूर्ण,   /* R3620  - EQ1_21 */
	अणु 0x00000E26, 0x6318 पूर्ण,   /* R3622  - EQ2_1 */
	अणु 0x00000E27, 0x6300 पूर्ण,   /* R3623  - EQ2_2 */
	अणु 0x00000E28, 0x0FC8 पूर्ण,   /* R3624  - EQ2_3 */
	अणु 0x00000E29, 0x03FE पूर्ण,   /* R3625  - EQ2_4 */
	अणु 0x00000E2A, 0x00E0 पूर्ण,   /* R3626  - EQ2_5 */
	अणु 0x00000E2B, 0x1EC4 पूर्ण,   /* R3627  - EQ2_6 */
	अणु 0x00000E2C, 0xF136 पूर्ण,   /* R3628  - EQ2_7 */
	अणु 0x00000E2D, 0x0409 पूर्ण,   /* R3629  - EQ2_8 */
	अणु 0x00000E2E, 0x04CC पूर्ण,   /* R3630  - EQ2_9 */
	अणु 0x00000E2F, 0x1C9B पूर्ण,   /* R3631  - EQ2_10 */
	अणु 0x00000E30, 0xF337 पूर्ण,   /* R3632  - EQ2_11 */
	अणु 0x00000E31, 0x040B पूर्ण,   /* R3633  - EQ2_12 */
	अणु 0x00000E32, 0x0CBB पूर्ण,   /* R3634  - EQ2_13 */
	अणु 0x00000E33, 0x16F8 पूर्ण,   /* R3635  - EQ2_14 */
	अणु 0x00000E34, 0xF7D9 पूर्ण,   /* R3636  - EQ2_15 */
	अणु 0x00000E35, 0x040A पूर्ण,   /* R3637  - EQ2_16 */
	अणु 0x00000E36, 0x1F14 पूर्ण,   /* R3638  - EQ2_17 */
	अणु 0x00000E37, 0x058C पूर्ण,   /* R3639  - EQ2_18 */
	अणु 0x00000E38, 0x0563 पूर्ण,   /* R3640  - EQ2_19 */
	अणु 0x00000E39, 0x4000 पूर्ण,   /* R3641  - EQ2_20 */
	अणु 0x00000E3A, 0x0B75 पूर्ण,   /* R3642  - EQ2_21 */
	अणु 0x00000E3C, 0x6318 पूर्ण,   /* R3644  - EQ3_1 */
	अणु 0x00000E3D, 0x6300 पूर्ण,   /* R3645  - EQ3_2 */
	अणु 0x00000E3E, 0x0FC8 पूर्ण,   /* R3646  - EQ3_3 */
	अणु 0x00000E3F, 0x03FE पूर्ण,   /* R3647  - EQ3_4 */
	अणु 0x00000E40, 0x00E0 पूर्ण,   /* R3648  - EQ3_5 */
	अणु 0x00000E41, 0x1EC4 पूर्ण,   /* R3649  - EQ3_6 */
	अणु 0x00000E42, 0xF136 पूर्ण,   /* R3650  - EQ3_7 */
	अणु 0x00000E43, 0x0409 पूर्ण,   /* R3651  - EQ3_8 */
	अणु 0x00000E44, 0x04CC पूर्ण,   /* R3652  - EQ3_9 */
	अणु 0x00000E45, 0x1C9B पूर्ण,   /* R3653  - EQ3_10 */
	अणु 0x00000E46, 0xF337 पूर्ण,   /* R3654  - EQ3_11 */
	अणु 0x00000E47, 0x040B पूर्ण,   /* R3655  - EQ3_12 */
	अणु 0x00000E48, 0x0CBB पूर्ण,   /* R3656  - EQ3_13 */
	अणु 0x00000E49, 0x16F8 पूर्ण,   /* R3657  - EQ3_14 */
	अणु 0x00000E4A, 0xF7D9 पूर्ण,   /* R3658  - EQ3_15 */
	अणु 0x00000E4B, 0x040A पूर्ण,   /* R3659  - EQ3_16 */
	अणु 0x00000E4C, 0x1F14 पूर्ण,   /* R3660  - EQ3_17 */
	अणु 0x00000E4D, 0x058C पूर्ण,   /* R3661  - EQ3_18 */
	अणु 0x00000E4E, 0x0563 पूर्ण,   /* R3662  - EQ3_19 */
	अणु 0x00000E4F, 0x4000 पूर्ण,   /* R3663  - EQ3_20 */
	अणु 0x00000E50, 0x0B75 पूर्ण,   /* R3664  - EQ3_21 */
	अणु 0x00000E52, 0x6318 पूर्ण,   /* R3666  - EQ4_1 */
	अणु 0x00000E53, 0x6300 पूर्ण,   /* R3667  - EQ4_2 */
	अणु 0x00000E54, 0x0FC8 पूर्ण,   /* R3668  - EQ4_3 */
	अणु 0x00000E55, 0x03FE पूर्ण,   /* R3669  - EQ4_4 */
	अणु 0x00000E56, 0x00E0 पूर्ण,   /* R3670  - EQ4_5 */
	अणु 0x00000E57, 0x1EC4 पूर्ण,   /* R3671  - EQ4_6 */
	अणु 0x00000E58, 0xF136 पूर्ण,   /* R3672  - EQ4_7 */
	अणु 0x00000E59, 0x0409 पूर्ण,   /* R3673  - EQ4_8 */
	अणु 0x00000E5A, 0x04CC पूर्ण,   /* R3674  - EQ4_9 */
	अणु 0x00000E5B, 0x1C9B पूर्ण,   /* R3675  - EQ4_10 */
	अणु 0x00000E5C, 0xF337 पूर्ण,   /* R3676  - EQ4_11 */
	अणु 0x00000E5D, 0x040B पूर्ण,   /* R3677  - EQ4_12 */
	अणु 0x00000E5E, 0x0CBB पूर्ण,   /* R3678  - EQ4_13 */
	अणु 0x00000E5F, 0x16F8 पूर्ण,   /* R3679  - EQ4_14 */
	अणु 0x00000E60, 0xF7D9 पूर्ण,   /* R3680  - EQ4_15 */
	अणु 0x00000E61, 0x040A पूर्ण,   /* R3681  - EQ4_16 */
	अणु 0x00000E62, 0x1F14 पूर्ण,   /* R3682  - EQ4_17 */
	अणु 0x00000E63, 0x058C पूर्ण,   /* R3683  - EQ4_18 */
	अणु 0x00000E64, 0x0563 पूर्ण,   /* R3684  - EQ4_19 */
	अणु 0x00000E65, 0x4000 पूर्ण,   /* R3685  - EQ4_20 */
	अणु 0x00000E66, 0x0B75 पूर्ण,   /* R3686  - EQ4_21 */
	अणु 0x00000E80, 0x0018 पूर्ण,   /* R3712  - DRC1 ctrl1 */
	अणु 0x00000E81, 0x0933 पूर्ण,   /* R3713  - DRC1 ctrl2 */
	अणु 0x00000E82, 0x0018 पूर्ण,   /* R3714  - DRC1 ctrl3 */
	अणु 0x00000E83, 0x0000 पूर्ण,   /* R3715  - DRC1 ctrl4 */
	अणु 0x00000E84, 0x0000 पूर्ण,   /* R3716  - DRC1 ctrl5 */
	अणु 0x00000EC0, 0x0000 पूर्ण,   /* R3776  - HPLPF1_1 */
	अणु 0x00000EC1, 0x0000 पूर्ण,   /* R3777  - HPLPF1_2 */
	अणु 0x00000EC4, 0x0000 पूर्ण,   /* R3780  - HPLPF2_1 */
	अणु 0x00000EC5, 0x0000 पूर्ण,   /* R3781  - HPLPF2_2 */
	अणु 0x00000EC8, 0x0000 पूर्ण,   /* R3784  - HPLPF3_1 */
	अणु 0x00000EC9, 0x0000 पूर्ण,   /* R3785  - HPLPF3_2 */
	अणु 0x00000ECC, 0x0000 पूर्ण,   /* R3788  - HPLPF4_1 */
	अणु 0x00000ECD, 0x0000 पूर्ण,   /* R3789  - HPLPF4_2 */
	अणु 0x00000EE0, 0x0000 पूर्ण,   /* R3808  - ASRC_ENABLE */
	अणु 0x00000EE2, 0x0000 पूर्ण,   /* R3810  - ASRC_RATE1 */
	अणु 0x00000EE3, 0x4000 पूर्ण,   /* R3811  - ASRC_RATE2 */
	अणु 0x00000EF0, 0x0000 पूर्ण,   /* R3824  - ISRC 1 CTRL 1 */
	अणु 0x00000EF1, 0x0000 पूर्ण,   /* R3825  - ISRC 1 CTRL 2 */
	अणु 0x00000EF2, 0x0000 पूर्ण,   /* R3826  - ISRC 1 CTRL 3 */
	अणु 0x00000EF3, 0x0000 पूर्ण,   /* R3827  - ISRC 2 CTRL 1 */
	अणु 0x00000EF4, 0x0000 पूर्ण,   /* R3828  - ISRC 2 CTRL 2 */
	अणु 0x00000EF5, 0x0000 पूर्ण,   /* R3829  - ISRC 2 CTRL 3 */
	अणु 0x00001100, 0x0010 पूर्ण,   /* R4352  - DSP1 Control 1 */
पूर्ण;

अटल bool wm5102_पढ़ोable_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल ARIZONA_SOFTWARE_RESET:
	हाल ARIZONA_DEVICE_REVISION:
	हाल ARIZONA_CTRL_IF_SPI_CFG_1:
	हाल ARIZONA_CTRL_IF_I2C1_CFG_1:
	हाल ARIZONA_WRITE_SEQUENCER_CTRL_0:
	हाल ARIZONA_WRITE_SEQUENCER_CTRL_1:
	हाल ARIZONA_WRITE_SEQUENCER_CTRL_2:
	हाल ARIZONA_WRITE_SEQUENCER_CTRL_3:
	हाल ARIZONA_TONE_GENERATOR_1:
	हाल ARIZONA_TONE_GENERATOR_2:
	हाल ARIZONA_TONE_GENERATOR_3:
	हाल ARIZONA_TONE_GENERATOR_4:
	हाल ARIZONA_TONE_GENERATOR_5:
	हाल ARIZONA_PWM_DRIVE_1:
	हाल ARIZONA_PWM_DRIVE_2:
	हाल ARIZONA_PWM_DRIVE_3:
	हाल ARIZONA_WAKE_CONTROL:
	हाल ARIZONA_SEQUENCE_CONTROL:
	हाल ARIZONA_SAMPLE_RATE_SEQUENCE_SELECT_1:
	हाल ARIZONA_SAMPLE_RATE_SEQUENCE_SELECT_2:
	हाल ARIZONA_SAMPLE_RATE_SEQUENCE_SELECT_3:
	हाल ARIZONA_SAMPLE_RATE_SEQUENCE_SELECT_4:
	हाल ARIZONA_ALWAYS_ON_TRIGGERS_SEQUENCE_SELECT_1:
	हाल ARIZONA_ALWAYS_ON_TRIGGERS_SEQUENCE_SELECT_2:
	हाल ARIZONA_ALWAYS_ON_TRIGGERS_SEQUENCE_SELECT_3:
	हाल ARIZONA_ALWAYS_ON_TRIGGERS_SEQUENCE_SELECT_4:
	हाल ARIZONA_ALWAYS_ON_TRIGGERS_SEQUENCE_SELECT_5:
	हाल ARIZONA_ALWAYS_ON_TRIGGERS_SEQUENCE_SELECT_6:
	हाल ARIZONA_COMFORT_NOISE_GENERATOR:
	हाल ARIZONA_HAPTICS_CONTROL_1:
	हाल ARIZONA_HAPTICS_CONTROL_2:
	हाल ARIZONA_HAPTICS_PHASE_1_INTENSITY:
	हाल ARIZONA_HAPTICS_PHASE_1_DURATION:
	हाल ARIZONA_HAPTICS_PHASE_2_INTENSITY:
	हाल ARIZONA_HAPTICS_PHASE_2_DURATION:
	हाल ARIZONA_HAPTICS_PHASE_3_INTENSITY:
	हाल ARIZONA_HAPTICS_PHASE_3_DURATION:
	हाल ARIZONA_HAPTICS_STATUS:
	हाल ARIZONA_CLOCK_32K_1:
	हाल ARIZONA_SYSTEM_CLOCK_1:
	हाल ARIZONA_SAMPLE_RATE_1:
	हाल ARIZONA_SAMPLE_RATE_2:
	हाल ARIZONA_SAMPLE_RATE_3:
	हाल ARIZONA_SAMPLE_RATE_1_STATUS:
	हाल ARIZONA_SAMPLE_RATE_2_STATUS:
	हाल ARIZONA_SAMPLE_RATE_3_STATUS:
	हाल ARIZONA_ASYNC_CLOCK_1:
	हाल ARIZONA_ASYNC_SAMPLE_RATE_1:
	हाल ARIZONA_ASYNC_SAMPLE_RATE_1_STATUS:
	हाल ARIZONA_ASYNC_SAMPLE_RATE_2:
	हाल ARIZONA_ASYNC_SAMPLE_RATE_2_STATUS:
	हाल ARIZONA_OUTPUT_SYSTEM_CLOCK:
	हाल ARIZONA_OUTPUT_ASYNC_CLOCK:
	हाल ARIZONA_RATE_ESTIMATOR_1:
	हाल ARIZONA_RATE_ESTIMATOR_2:
	हाल ARIZONA_RATE_ESTIMATOR_3:
	हाल ARIZONA_RATE_ESTIMATOR_4:
	हाल ARIZONA_RATE_ESTIMATOR_5:
	हाल ARIZONA_DYNAMIC_FREQUENCY_SCALING_1:
	हाल ARIZONA_FLL1_CONTROL_1:
	हाल ARIZONA_FLL1_CONTROL_2:
	हाल ARIZONA_FLL1_CONTROL_3:
	हाल ARIZONA_FLL1_CONTROL_4:
	हाल ARIZONA_FLL1_CONTROL_5:
	हाल ARIZONA_FLL1_CONTROL_6:
	हाल ARIZONA_FLL1_CONTROL_7:
	हाल ARIZONA_FLL1_SYNCHRONISER_1:
	हाल ARIZONA_FLL1_SYNCHRONISER_2:
	हाल ARIZONA_FLL1_SYNCHRONISER_3:
	हाल ARIZONA_FLL1_SYNCHRONISER_4:
	हाल ARIZONA_FLL1_SYNCHRONISER_5:
	हाल ARIZONA_FLL1_SYNCHRONISER_6:
	हाल ARIZONA_FLL1_SYNCHRONISER_7:
	हाल ARIZONA_FLL1_SPREAD_SPECTRUM:
	हाल ARIZONA_FLL1_GPIO_CLOCK:
	हाल ARIZONA_FLL2_CONTROL_1:
	हाल ARIZONA_FLL2_CONTROL_2:
	हाल ARIZONA_FLL2_CONTROL_3:
	हाल ARIZONA_FLL2_CONTROL_4:
	हाल ARIZONA_FLL2_CONTROL_5:
	हाल ARIZONA_FLL2_CONTROL_6:
	हाल ARIZONA_FLL2_CONTROL_7:
	हाल ARIZONA_FLL2_SYNCHRONISER_1:
	हाल ARIZONA_FLL2_SYNCHRONISER_2:
	हाल ARIZONA_FLL2_SYNCHRONISER_3:
	हाल ARIZONA_FLL2_SYNCHRONISER_4:
	हाल ARIZONA_FLL2_SYNCHRONISER_5:
	हाल ARIZONA_FLL2_SYNCHRONISER_6:
	हाल ARIZONA_FLL2_SYNCHRONISER_7:
	हाल ARIZONA_FLL2_SPREAD_SPECTRUM:
	हाल ARIZONA_FLL2_GPIO_CLOCK:
	हाल ARIZONA_MIC_CHARGE_PUMP_1:
	हाल ARIZONA_LDO1_CONTROL_1:
	हाल ARIZONA_LDO1_CONTROL_2:
	हाल ARIZONA_LDO2_CONTROL_1:
	हाल ARIZONA_MIC_BIAS_CTRL_1:
	हाल ARIZONA_MIC_BIAS_CTRL_2:
	हाल ARIZONA_MIC_BIAS_CTRL_3:
	हाल ARIZONA_HP_CTRL_1L:
	हाल ARIZONA_HP_CTRL_1R:
	हाल ARIZONA_ACCESSORY_DETECT_MODE_1:
	हाल ARIZONA_HEADPHONE_DETECT_1:
	हाल ARIZONA_HEADPHONE_DETECT_2:
	हाल ARIZONA_HP_DACVAL:
	हाल ARIZONA_MICD_CLAMP_CONTROL:
	हाल ARIZONA_MIC_DETECT_1:
	हाल ARIZONA_MIC_DETECT_2:
	हाल ARIZONA_MIC_DETECT_3:
	हाल ARIZONA_MIC_DETECT_LEVEL_1:
	हाल ARIZONA_MIC_DETECT_LEVEL_2:
	हाल ARIZONA_MIC_DETECT_LEVEL_3:
	हाल ARIZONA_MIC_DETECT_LEVEL_4:
	हाल ARIZONA_MIC_NOISE_MIX_CONTROL_1:
	हाल ARIZONA_ISOLATION_CONTROL:
	हाल ARIZONA_JACK_DETECT_ANALOGUE:
	हाल ARIZONA_INPUT_ENABLES:
	हाल ARIZONA_INPUT_RATE:
	हाल ARIZONA_INPUT_VOLUME_RAMP:
	हाल ARIZONA_IN1L_CONTROL:
	हाल ARIZONA_ADC_DIGITAL_VOLUME_1L:
	हाल ARIZONA_DMIC1L_CONTROL:
	हाल ARIZONA_IN1R_CONTROL:
	हाल ARIZONA_ADC_DIGITAL_VOLUME_1R:
	हाल ARIZONA_DMIC1R_CONTROL:
	हाल ARIZONA_IN2L_CONTROL:
	हाल ARIZONA_ADC_DIGITAL_VOLUME_2L:
	हाल ARIZONA_DMIC2L_CONTROL:
	हाल ARIZONA_IN2R_CONTROL:
	हाल ARIZONA_ADC_DIGITAL_VOLUME_2R:
	हाल ARIZONA_DMIC2R_CONTROL:
	हाल ARIZONA_IN3L_CONTROL:
	हाल ARIZONA_ADC_DIGITAL_VOLUME_3L:
	हाल ARIZONA_DMIC3L_CONTROL:
	हाल ARIZONA_IN3R_CONTROL:
	हाल ARIZONA_ADC_DIGITAL_VOLUME_3R:
	हाल ARIZONA_DMIC3R_CONTROL:
	हाल ARIZONA_OUTPUT_ENABLES_1:
	हाल ARIZONA_OUTPUT_STATUS_1:
	हाल ARIZONA_OUTPUT_RATE_1:
	हाल ARIZONA_OUTPUT_VOLUME_RAMP:
	हाल ARIZONA_OUTPUT_PATH_CONFIG_1L:
	हाल ARIZONA_DAC_DIGITAL_VOLUME_1L:
	हाल ARIZONA_DAC_VOLUME_LIMIT_1L:
	हाल ARIZONA_NOISE_GATE_SELECT_1L:
	हाल ARIZONA_OUTPUT_PATH_CONFIG_1R:
	हाल ARIZONA_DAC_DIGITAL_VOLUME_1R:
	हाल ARIZONA_DAC_VOLUME_LIMIT_1R:
	हाल ARIZONA_NOISE_GATE_SELECT_1R:
	हाल ARIZONA_OUTPUT_PATH_CONFIG_2L:
	हाल ARIZONA_DAC_DIGITAL_VOLUME_2L:
	हाल ARIZONA_DAC_VOLUME_LIMIT_2L:
	हाल ARIZONA_NOISE_GATE_SELECT_2L:
	हाल ARIZONA_OUTPUT_PATH_CONFIG_2R:
	हाल ARIZONA_DAC_DIGITAL_VOLUME_2R:
	हाल ARIZONA_DAC_VOLUME_LIMIT_2R:
	हाल ARIZONA_NOISE_GATE_SELECT_2R:
	हाल ARIZONA_OUTPUT_PATH_CONFIG_3L:
	हाल ARIZONA_DAC_DIGITAL_VOLUME_3L:
	हाल ARIZONA_DAC_VOLUME_LIMIT_3L:
	हाल ARIZONA_NOISE_GATE_SELECT_3L:
	हाल ARIZONA_OUTPUT_PATH_CONFIG_4L:
	हाल ARIZONA_DAC_DIGITAL_VOLUME_4L:
	हाल ARIZONA_OUT_VOLUME_4L:
	हाल ARIZONA_NOISE_GATE_SELECT_4L:
	हाल ARIZONA_DAC_DIGITAL_VOLUME_4R:
	हाल ARIZONA_OUT_VOLUME_4R:
	हाल ARIZONA_NOISE_GATE_SELECT_4R:
	हाल ARIZONA_OUTPUT_PATH_CONFIG_5L:
	हाल ARIZONA_DAC_DIGITAL_VOLUME_5L:
	हाल ARIZONA_DAC_VOLUME_LIMIT_5L:
	हाल ARIZONA_NOISE_GATE_SELECT_5L:
	हाल ARIZONA_DAC_DIGITAL_VOLUME_5R:
	हाल ARIZONA_DAC_VOLUME_LIMIT_5R:
	हाल ARIZONA_NOISE_GATE_SELECT_5R:
	हाल ARIZONA_DRE_ENABLE:
	हाल ARIZONA_DRE_CONTROL_2:
	हाल ARIZONA_DRE_CONTROL_3:
	हाल ARIZONA_DAC_AEC_CONTROL_1:
	हाल ARIZONA_NOISE_GATE_CONTROL:
	हाल ARIZONA_PDM_SPK1_CTRL_1:
	हाल ARIZONA_PDM_SPK1_CTRL_2:
	हाल ARIZONA_DAC_COMP_1:
	हाल ARIZONA_DAC_COMP_2:
	हाल ARIZONA_DAC_COMP_3:
	हाल ARIZONA_DAC_COMP_4:
	हाल ARIZONA_AIF1_BCLK_CTRL:
	हाल ARIZONA_AIF1_TX_PIN_CTRL:
	हाल ARIZONA_AIF1_RX_PIN_CTRL:
	हाल ARIZONA_AIF1_RATE_CTRL:
	हाल ARIZONA_AIF1_FORMAT:
	हाल ARIZONA_AIF1_TX_BCLK_RATE:
	हाल ARIZONA_AIF1_RX_BCLK_RATE:
	हाल ARIZONA_AIF1_FRAME_CTRL_1:
	हाल ARIZONA_AIF1_FRAME_CTRL_2:
	हाल ARIZONA_AIF1_FRAME_CTRL_3:
	हाल ARIZONA_AIF1_FRAME_CTRL_4:
	हाल ARIZONA_AIF1_FRAME_CTRL_5:
	हाल ARIZONA_AIF1_FRAME_CTRL_6:
	हाल ARIZONA_AIF1_FRAME_CTRL_7:
	हाल ARIZONA_AIF1_FRAME_CTRL_8:
	हाल ARIZONA_AIF1_FRAME_CTRL_9:
	हाल ARIZONA_AIF1_FRAME_CTRL_10:
	हाल ARIZONA_AIF1_FRAME_CTRL_11:
	हाल ARIZONA_AIF1_FRAME_CTRL_12:
	हाल ARIZONA_AIF1_FRAME_CTRL_13:
	हाल ARIZONA_AIF1_FRAME_CTRL_14:
	हाल ARIZONA_AIF1_FRAME_CTRL_15:
	हाल ARIZONA_AIF1_FRAME_CTRL_16:
	हाल ARIZONA_AIF1_FRAME_CTRL_17:
	हाल ARIZONA_AIF1_FRAME_CTRL_18:
	हाल ARIZONA_AIF1_TX_ENABLES:
	हाल ARIZONA_AIF1_RX_ENABLES:
	हाल ARIZONA_AIF2_BCLK_CTRL:
	हाल ARIZONA_AIF2_TX_PIN_CTRL:
	हाल ARIZONA_AIF2_RX_PIN_CTRL:
	हाल ARIZONA_AIF2_RATE_CTRL:
	हाल ARIZONA_AIF2_FORMAT:
	हाल ARIZONA_AIF2_TX_BCLK_RATE:
	हाल ARIZONA_AIF2_RX_BCLK_RATE:
	हाल ARIZONA_AIF2_FRAME_CTRL_1:
	हाल ARIZONA_AIF2_FRAME_CTRL_2:
	हाल ARIZONA_AIF2_FRAME_CTRL_3:
	हाल ARIZONA_AIF2_FRAME_CTRL_4:
	हाल ARIZONA_AIF2_FRAME_CTRL_11:
	हाल ARIZONA_AIF2_FRAME_CTRL_12:
	हाल ARIZONA_AIF2_TX_ENABLES:
	हाल ARIZONA_AIF2_RX_ENABLES:
	हाल ARIZONA_AIF3_BCLK_CTRL:
	हाल ARIZONA_AIF3_TX_PIN_CTRL:
	हाल ARIZONA_AIF3_RX_PIN_CTRL:
	हाल ARIZONA_AIF3_RATE_CTRL:
	हाल ARIZONA_AIF3_FORMAT:
	हाल ARIZONA_AIF3_TX_BCLK_RATE:
	हाल ARIZONA_AIF3_RX_BCLK_RATE:
	हाल ARIZONA_AIF3_FRAME_CTRL_1:
	हाल ARIZONA_AIF3_FRAME_CTRL_2:
	हाल ARIZONA_AIF3_FRAME_CTRL_3:
	हाल ARIZONA_AIF3_FRAME_CTRL_4:
	हाल ARIZONA_AIF3_FRAME_CTRL_11:
	हाल ARIZONA_AIF3_FRAME_CTRL_12:
	हाल ARIZONA_AIF3_TX_ENABLES:
	हाल ARIZONA_AIF3_RX_ENABLES:
	हाल ARIZONA_SLIMBUS_FRAMER_REF_GEAR:
	हाल ARIZONA_SLIMBUS_RATES_1:
	हाल ARIZONA_SLIMBUS_RATES_2:
	हाल ARIZONA_SLIMBUS_RATES_3:
	हाल ARIZONA_SLIMBUS_RATES_4:
	हाल ARIZONA_SLIMBUS_RATES_5:
	हाल ARIZONA_SLIMBUS_RATES_6:
	हाल ARIZONA_SLIMBUS_RATES_7:
	हाल ARIZONA_SLIMBUS_RATES_8:
	हाल ARIZONA_SLIMBUS_RX_CHANNEL_ENABLE:
	हाल ARIZONA_SLIMBUS_TX_CHANNEL_ENABLE:
	हाल ARIZONA_SLIMBUS_RX_PORT_STATUS:
	हाल ARIZONA_SLIMBUS_TX_PORT_STATUS:
	हाल ARIZONA_PWM1MIX_INPUT_1_SOURCE:
	हाल ARIZONA_PWM1MIX_INPUT_1_VOLUME:
	हाल ARIZONA_PWM1MIX_INPUT_2_SOURCE:
	हाल ARIZONA_PWM1MIX_INPUT_2_VOLUME:
	हाल ARIZONA_PWM1MIX_INPUT_3_SOURCE:
	हाल ARIZONA_PWM1MIX_INPUT_3_VOLUME:
	हाल ARIZONA_PWM1MIX_INPUT_4_SOURCE:
	हाल ARIZONA_PWM1MIX_INPUT_4_VOLUME:
	हाल ARIZONA_PWM2MIX_INPUT_1_SOURCE:
	हाल ARIZONA_PWM2MIX_INPUT_1_VOLUME:
	हाल ARIZONA_PWM2MIX_INPUT_2_SOURCE:
	हाल ARIZONA_PWM2MIX_INPUT_2_VOLUME:
	हाल ARIZONA_PWM2MIX_INPUT_3_SOURCE:
	हाल ARIZONA_PWM2MIX_INPUT_3_VOLUME:
	हाल ARIZONA_PWM2MIX_INPUT_4_SOURCE:
	हाल ARIZONA_PWM2MIX_INPUT_4_VOLUME:
	हाल ARIZONA_MICMIX_INPUT_1_SOURCE:
	हाल ARIZONA_MICMIX_INPUT_1_VOLUME:
	हाल ARIZONA_MICMIX_INPUT_2_SOURCE:
	हाल ARIZONA_MICMIX_INPUT_2_VOLUME:
	हाल ARIZONA_MICMIX_INPUT_3_SOURCE:
	हाल ARIZONA_MICMIX_INPUT_3_VOLUME:
	हाल ARIZONA_MICMIX_INPUT_4_SOURCE:
	हाल ARIZONA_MICMIX_INPUT_4_VOLUME:
	हाल ARIZONA_NOISEMIX_INPUT_1_SOURCE:
	हाल ARIZONA_NOISEMIX_INPUT_1_VOLUME:
	हाल ARIZONA_NOISEMIX_INPUT_2_SOURCE:
	हाल ARIZONA_NOISEMIX_INPUT_2_VOLUME:
	हाल ARIZONA_NOISEMIX_INPUT_3_SOURCE:
	हाल ARIZONA_NOISEMIX_INPUT_3_VOLUME:
	हाल ARIZONA_NOISEMIX_INPUT_4_SOURCE:
	हाल ARIZONA_NOISEMIX_INPUT_4_VOLUME:
	हाल ARIZONA_OUT1LMIX_INPUT_1_SOURCE:
	हाल ARIZONA_OUT1LMIX_INPUT_1_VOLUME:
	हाल ARIZONA_OUT1LMIX_INPUT_2_SOURCE:
	हाल ARIZONA_OUT1LMIX_INPUT_2_VOLUME:
	हाल ARIZONA_OUT1LMIX_INPUT_3_SOURCE:
	हाल ARIZONA_OUT1LMIX_INPUT_3_VOLUME:
	हाल ARIZONA_OUT1LMIX_INPUT_4_SOURCE:
	हाल ARIZONA_OUT1LMIX_INPUT_4_VOLUME:
	हाल ARIZONA_OUT1RMIX_INPUT_1_SOURCE:
	हाल ARIZONA_OUT1RMIX_INPUT_1_VOLUME:
	हाल ARIZONA_OUT1RMIX_INPUT_2_SOURCE:
	हाल ARIZONA_OUT1RMIX_INPUT_2_VOLUME:
	हाल ARIZONA_OUT1RMIX_INPUT_3_SOURCE:
	हाल ARIZONA_OUT1RMIX_INPUT_3_VOLUME:
	हाल ARIZONA_OUT1RMIX_INPUT_4_SOURCE:
	हाल ARIZONA_OUT1RMIX_INPUT_4_VOLUME:
	हाल ARIZONA_OUT2LMIX_INPUT_1_SOURCE:
	हाल ARIZONA_OUT2LMIX_INPUT_1_VOLUME:
	हाल ARIZONA_OUT2LMIX_INPUT_2_SOURCE:
	हाल ARIZONA_OUT2LMIX_INPUT_2_VOLUME:
	हाल ARIZONA_OUT2LMIX_INPUT_3_SOURCE:
	हाल ARIZONA_OUT2LMIX_INPUT_3_VOLUME:
	हाल ARIZONA_OUT2LMIX_INPUT_4_SOURCE:
	हाल ARIZONA_OUT2LMIX_INPUT_4_VOLUME:
	हाल ARIZONA_OUT2RMIX_INPUT_1_SOURCE:
	हाल ARIZONA_OUT2RMIX_INPUT_1_VOLUME:
	हाल ARIZONA_OUT2RMIX_INPUT_2_SOURCE:
	हाल ARIZONA_OUT2RMIX_INPUT_2_VOLUME:
	हाल ARIZONA_OUT2RMIX_INPUT_3_SOURCE:
	हाल ARIZONA_OUT2RMIX_INPUT_3_VOLUME:
	हाल ARIZONA_OUT2RMIX_INPUT_4_SOURCE:
	हाल ARIZONA_OUT2RMIX_INPUT_4_VOLUME:
	हाल ARIZONA_OUT3LMIX_INPUT_1_SOURCE:
	हाल ARIZONA_OUT3LMIX_INPUT_1_VOLUME:
	हाल ARIZONA_OUT3LMIX_INPUT_2_SOURCE:
	हाल ARIZONA_OUT3LMIX_INPUT_2_VOLUME:
	हाल ARIZONA_OUT3LMIX_INPUT_3_SOURCE:
	हाल ARIZONA_OUT3LMIX_INPUT_3_VOLUME:
	हाल ARIZONA_OUT3LMIX_INPUT_4_SOURCE:
	हाल ARIZONA_OUT3LMIX_INPUT_4_VOLUME:
	हाल ARIZONA_OUT4LMIX_INPUT_1_SOURCE:
	हाल ARIZONA_OUT4LMIX_INPUT_1_VOLUME:
	हाल ARIZONA_OUT4LMIX_INPUT_2_SOURCE:
	हाल ARIZONA_OUT4LMIX_INPUT_2_VOLUME:
	हाल ARIZONA_OUT4LMIX_INPUT_3_SOURCE:
	हाल ARIZONA_OUT4LMIX_INPUT_3_VOLUME:
	हाल ARIZONA_OUT4LMIX_INPUT_4_SOURCE:
	हाल ARIZONA_OUT4LMIX_INPUT_4_VOLUME:
	हाल ARIZONA_OUT4RMIX_INPUT_1_SOURCE:
	हाल ARIZONA_OUT4RMIX_INPUT_1_VOLUME:
	हाल ARIZONA_OUT4RMIX_INPUT_2_SOURCE:
	हाल ARIZONA_OUT4RMIX_INPUT_2_VOLUME:
	हाल ARIZONA_OUT4RMIX_INPUT_3_SOURCE:
	हाल ARIZONA_OUT4RMIX_INPUT_3_VOLUME:
	हाल ARIZONA_OUT4RMIX_INPUT_4_SOURCE:
	हाल ARIZONA_OUT4RMIX_INPUT_4_VOLUME:
	हाल ARIZONA_OUT5LMIX_INPUT_1_SOURCE:
	हाल ARIZONA_OUT5LMIX_INPUT_1_VOLUME:
	हाल ARIZONA_OUT5LMIX_INPUT_2_SOURCE:
	हाल ARIZONA_OUT5LMIX_INPUT_2_VOLUME:
	हाल ARIZONA_OUT5LMIX_INPUT_3_SOURCE:
	हाल ARIZONA_OUT5LMIX_INPUT_3_VOLUME:
	हाल ARIZONA_OUT5LMIX_INPUT_4_SOURCE:
	हाल ARIZONA_OUT5LMIX_INPUT_4_VOLUME:
	हाल ARIZONA_OUT5RMIX_INPUT_1_SOURCE:
	हाल ARIZONA_OUT5RMIX_INPUT_1_VOLUME:
	हाल ARIZONA_OUT5RMIX_INPUT_2_SOURCE:
	हाल ARIZONA_OUT5RMIX_INPUT_2_VOLUME:
	हाल ARIZONA_OUT5RMIX_INPUT_3_SOURCE:
	हाल ARIZONA_OUT5RMIX_INPUT_3_VOLUME:
	हाल ARIZONA_OUT5RMIX_INPUT_4_SOURCE:
	हाल ARIZONA_OUT5RMIX_INPUT_4_VOLUME:
	हाल ARIZONA_AIF1TX1MIX_INPUT_1_SOURCE:
	हाल ARIZONA_AIF1TX1MIX_INPUT_1_VOLUME:
	हाल ARIZONA_AIF1TX1MIX_INPUT_2_SOURCE:
	हाल ARIZONA_AIF1TX1MIX_INPUT_2_VOLUME:
	हाल ARIZONA_AIF1TX1MIX_INPUT_3_SOURCE:
	हाल ARIZONA_AIF1TX1MIX_INPUT_3_VOLUME:
	हाल ARIZONA_AIF1TX1MIX_INPUT_4_SOURCE:
	हाल ARIZONA_AIF1TX1MIX_INPUT_4_VOLUME:
	हाल ARIZONA_AIF1TX2MIX_INPUT_1_SOURCE:
	हाल ARIZONA_AIF1TX2MIX_INPUT_1_VOLUME:
	हाल ARIZONA_AIF1TX2MIX_INPUT_2_SOURCE:
	हाल ARIZONA_AIF1TX2MIX_INPUT_2_VOLUME:
	हाल ARIZONA_AIF1TX2MIX_INPUT_3_SOURCE:
	हाल ARIZONA_AIF1TX2MIX_INPUT_3_VOLUME:
	हाल ARIZONA_AIF1TX2MIX_INPUT_4_SOURCE:
	हाल ARIZONA_AIF1TX2MIX_INPUT_4_VOLUME:
	हाल ARIZONA_AIF1TX3MIX_INPUT_1_SOURCE:
	हाल ARIZONA_AIF1TX3MIX_INPUT_1_VOLUME:
	हाल ARIZONA_AIF1TX3MIX_INPUT_2_SOURCE:
	हाल ARIZONA_AIF1TX3MIX_INPUT_2_VOLUME:
	हाल ARIZONA_AIF1TX3MIX_INPUT_3_SOURCE:
	हाल ARIZONA_AIF1TX3MIX_INPUT_3_VOLUME:
	हाल ARIZONA_AIF1TX3MIX_INPUT_4_SOURCE:
	हाल ARIZONA_AIF1TX3MIX_INPUT_4_VOLUME:
	हाल ARIZONA_AIF1TX4MIX_INPUT_1_SOURCE:
	हाल ARIZONA_AIF1TX4MIX_INPUT_1_VOLUME:
	हाल ARIZONA_AIF1TX4MIX_INPUT_2_SOURCE:
	हाल ARIZONA_AIF1TX4MIX_INPUT_2_VOLUME:
	हाल ARIZONA_AIF1TX4MIX_INPUT_3_SOURCE:
	हाल ARIZONA_AIF1TX4MIX_INPUT_3_VOLUME:
	हाल ARIZONA_AIF1TX4MIX_INPUT_4_SOURCE:
	हाल ARIZONA_AIF1TX4MIX_INPUT_4_VOLUME:
	हाल ARIZONA_AIF1TX5MIX_INPUT_1_SOURCE:
	हाल ARIZONA_AIF1TX5MIX_INPUT_1_VOLUME:
	हाल ARIZONA_AIF1TX5MIX_INPUT_2_SOURCE:
	हाल ARIZONA_AIF1TX5MIX_INPUT_2_VOLUME:
	हाल ARIZONA_AIF1TX5MIX_INPUT_3_SOURCE:
	हाल ARIZONA_AIF1TX5MIX_INPUT_3_VOLUME:
	हाल ARIZONA_AIF1TX5MIX_INPUT_4_SOURCE:
	हाल ARIZONA_AIF1TX5MIX_INPUT_4_VOLUME:
	हाल ARIZONA_AIF1TX6MIX_INPUT_1_SOURCE:
	हाल ARIZONA_AIF1TX6MIX_INPUT_1_VOLUME:
	हाल ARIZONA_AIF1TX6MIX_INPUT_2_SOURCE:
	हाल ARIZONA_AIF1TX6MIX_INPUT_2_VOLUME:
	हाल ARIZONA_AIF1TX6MIX_INPUT_3_SOURCE:
	हाल ARIZONA_AIF1TX6MIX_INPUT_3_VOLUME:
	हाल ARIZONA_AIF1TX6MIX_INPUT_4_SOURCE:
	हाल ARIZONA_AIF1TX6MIX_INPUT_4_VOLUME:
	हाल ARIZONA_AIF1TX7MIX_INPUT_1_SOURCE:
	हाल ARIZONA_AIF1TX7MIX_INPUT_1_VOLUME:
	हाल ARIZONA_AIF1TX7MIX_INPUT_2_SOURCE:
	हाल ARIZONA_AIF1TX7MIX_INPUT_2_VOLUME:
	हाल ARIZONA_AIF1TX7MIX_INPUT_3_SOURCE:
	हाल ARIZONA_AIF1TX7MIX_INPUT_3_VOLUME:
	हाल ARIZONA_AIF1TX7MIX_INPUT_4_SOURCE:
	हाल ARIZONA_AIF1TX7MIX_INPUT_4_VOLUME:
	हाल ARIZONA_AIF1TX8MIX_INPUT_1_SOURCE:
	हाल ARIZONA_AIF1TX8MIX_INPUT_1_VOLUME:
	हाल ARIZONA_AIF1TX8MIX_INPUT_2_SOURCE:
	हाल ARIZONA_AIF1TX8MIX_INPUT_2_VOLUME:
	हाल ARIZONA_AIF1TX8MIX_INPUT_3_SOURCE:
	हाल ARIZONA_AIF1TX8MIX_INPUT_3_VOLUME:
	हाल ARIZONA_AIF1TX8MIX_INPUT_4_SOURCE:
	हाल ARIZONA_AIF1TX8MIX_INPUT_4_VOLUME:
	हाल ARIZONA_AIF2TX1MIX_INPUT_1_SOURCE:
	हाल ARIZONA_AIF2TX1MIX_INPUT_1_VOLUME:
	हाल ARIZONA_AIF2TX1MIX_INPUT_2_SOURCE:
	हाल ARIZONA_AIF2TX1MIX_INPUT_2_VOLUME:
	हाल ARIZONA_AIF2TX1MIX_INPUT_3_SOURCE:
	हाल ARIZONA_AIF2TX1MIX_INPUT_3_VOLUME:
	हाल ARIZONA_AIF2TX1MIX_INPUT_4_SOURCE:
	हाल ARIZONA_AIF2TX1MIX_INPUT_4_VOLUME:
	हाल ARIZONA_AIF2TX2MIX_INPUT_1_SOURCE:
	हाल ARIZONA_AIF2TX2MIX_INPUT_1_VOLUME:
	हाल ARIZONA_AIF2TX2MIX_INPUT_2_SOURCE:
	हाल ARIZONA_AIF2TX2MIX_INPUT_2_VOLUME:
	हाल ARIZONA_AIF2TX2MIX_INPUT_3_SOURCE:
	हाल ARIZONA_AIF2TX2MIX_INPUT_3_VOLUME:
	हाल ARIZONA_AIF2TX2MIX_INPUT_4_SOURCE:
	हाल ARIZONA_AIF2TX2MIX_INPUT_4_VOLUME:
	हाल ARIZONA_AIF3TX1MIX_INPUT_1_SOURCE:
	हाल ARIZONA_AIF3TX1MIX_INPUT_1_VOLUME:
	हाल ARIZONA_AIF3TX1MIX_INPUT_2_SOURCE:
	हाल ARIZONA_AIF3TX1MIX_INPUT_2_VOLUME:
	हाल ARIZONA_AIF3TX1MIX_INPUT_3_SOURCE:
	हाल ARIZONA_AIF3TX1MIX_INPUT_3_VOLUME:
	हाल ARIZONA_AIF3TX1MIX_INPUT_4_SOURCE:
	हाल ARIZONA_AIF3TX1MIX_INPUT_4_VOLUME:
	हाल ARIZONA_AIF3TX2MIX_INPUT_1_SOURCE:
	हाल ARIZONA_AIF3TX2MIX_INPUT_1_VOLUME:
	हाल ARIZONA_AIF3TX2MIX_INPUT_2_SOURCE:
	हाल ARIZONA_AIF3TX2MIX_INPUT_2_VOLUME:
	हाल ARIZONA_AIF3TX2MIX_INPUT_3_SOURCE:
	हाल ARIZONA_AIF3TX2MIX_INPUT_3_VOLUME:
	हाल ARIZONA_AIF3TX2MIX_INPUT_4_SOURCE:
	हाल ARIZONA_AIF3TX2MIX_INPUT_4_VOLUME:
	हाल ARIZONA_SLIMTX1MIX_INPUT_1_SOURCE:
	हाल ARIZONA_SLIMTX1MIX_INPUT_1_VOLUME:
	हाल ARIZONA_SLIMTX1MIX_INPUT_2_SOURCE:
	हाल ARIZONA_SLIMTX1MIX_INPUT_2_VOLUME:
	हाल ARIZONA_SLIMTX1MIX_INPUT_3_SOURCE:
	हाल ARIZONA_SLIMTX1MIX_INPUT_3_VOLUME:
	हाल ARIZONA_SLIMTX1MIX_INPUT_4_SOURCE:
	हाल ARIZONA_SLIMTX1MIX_INPUT_4_VOLUME:
	हाल ARIZONA_SLIMTX2MIX_INPUT_1_SOURCE:
	हाल ARIZONA_SLIMTX2MIX_INPUT_1_VOLUME:
	हाल ARIZONA_SLIMTX2MIX_INPUT_2_SOURCE:
	हाल ARIZONA_SLIMTX2MIX_INPUT_2_VOLUME:
	हाल ARIZONA_SLIMTX2MIX_INPUT_3_SOURCE:
	हाल ARIZONA_SLIMTX2MIX_INPUT_3_VOLUME:
	हाल ARIZONA_SLIMTX2MIX_INPUT_4_SOURCE:
	हाल ARIZONA_SLIMTX2MIX_INPUT_4_VOLUME:
	हाल ARIZONA_SLIMTX3MIX_INPUT_1_SOURCE:
	हाल ARIZONA_SLIMTX3MIX_INPUT_1_VOLUME:
	हाल ARIZONA_SLIMTX3MIX_INPUT_2_SOURCE:
	हाल ARIZONA_SLIMTX3MIX_INPUT_2_VOLUME:
	हाल ARIZONA_SLIMTX3MIX_INPUT_3_SOURCE:
	हाल ARIZONA_SLIMTX3MIX_INPUT_3_VOLUME:
	हाल ARIZONA_SLIMTX3MIX_INPUT_4_SOURCE:
	हाल ARIZONA_SLIMTX3MIX_INPUT_4_VOLUME:
	हाल ARIZONA_SLIMTX4MIX_INPUT_1_SOURCE:
	हाल ARIZONA_SLIMTX4MIX_INPUT_1_VOLUME:
	हाल ARIZONA_SLIMTX4MIX_INPUT_2_SOURCE:
	हाल ARIZONA_SLIMTX4MIX_INPUT_2_VOLUME:
	हाल ARIZONA_SLIMTX4MIX_INPUT_3_SOURCE:
	हाल ARIZONA_SLIMTX4MIX_INPUT_3_VOLUME:
	हाल ARIZONA_SLIMTX4MIX_INPUT_4_SOURCE:
	हाल ARIZONA_SLIMTX4MIX_INPUT_4_VOLUME:
	हाल ARIZONA_SLIMTX5MIX_INPUT_1_SOURCE:
	हाल ARIZONA_SLIMTX5MIX_INPUT_1_VOLUME:
	हाल ARIZONA_SLIMTX5MIX_INPUT_2_SOURCE:
	हाल ARIZONA_SLIMTX5MIX_INPUT_2_VOLUME:
	हाल ARIZONA_SLIMTX5MIX_INPUT_3_SOURCE:
	हाल ARIZONA_SLIMTX5MIX_INPUT_3_VOLUME:
	हाल ARIZONA_SLIMTX5MIX_INPUT_4_SOURCE:
	हाल ARIZONA_SLIMTX5MIX_INPUT_4_VOLUME:
	हाल ARIZONA_SLIMTX6MIX_INPUT_1_SOURCE:
	हाल ARIZONA_SLIMTX6MIX_INPUT_1_VOLUME:
	हाल ARIZONA_SLIMTX6MIX_INPUT_2_SOURCE:
	हाल ARIZONA_SLIMTX6MIX_INPUT_2_VOLUME:
	हाल ARIZONA_SLIMTX6MIX_INPUT_3_SOURCE:
	हाल ARIZONA_SLIMTX6MIX_INPUT_3_VOLUME:
	हाल ARIZONA_SLIMTX6MIX_INPUT_4_SOURCE:
	हाल ARIZONA_SLIMTX6MIX_INPUT_4_VOLUME:
	हाल ARIZONA_SLIMTX7MIX_INPUT_1_SOURCE:
	हाल ARIZONA_SLIMTX7MIX_INPUT_1_VOLUME:
	हाल ARIZONA_SLIMTX7MIX_INPUT_2_SOURCE:
	हाल ARIZONA_SLIMTX7MIX_INPUT_2_VOLUME:
	हाल ARIZONA_SLIMTX7MIX_INPUT_3_SOURCE:
	हाल ARIZONA_SLIMTX7MIX_INPUT_3_VOLUME:
	हाल ARIZONA_SLIMTX7MIX_INPUT_4_SOURCE:
	हाल ARIZONA_SLIMTX7MIX_INPUT_4_VOLUME:
	हाल ARIZONA_SLIMTX8MIX_INPUT_1_SOURCE:
	हाल ARIZONA_SLIMTX8MIX_INPUT_1_VOLUME:
	हाल ARIZONA_SLIMTX8MIX_INPUT_2_SOURCE:
	हाल ARIZONA_SLIMTX8MIX_INPUT_2_VOLUME:
	हाल ARIZONA_SLIMTX8MIX_INPUT_3_SOURCE:
	हाल ARIZONA_SLIMTX8MIX_INPUT_3_VOLUME:
	हाल ARIZONA_SLIMTX8MIX_INPUT_4_SOURCE:
	हाल ARIZONA_SLIMTX8MIX_INPUT_4_VOLUME:
	हाल ARIZONA_EQ1MIX_INPUT_1_SOURCE:
	हाल ARIZONA_EQ1MIX_INPUT_1_VOLUME:
	हाल ARIZONA_EQ1MIX_INPUT_2_SOURCE:
	हाल ARIZONA_EQ1MIX_INPUT_2_VOLUME:
	हाल ARIZONA_EQ1MIX_INPUT_3_SOURCE:
	हाल ARIZONA_EQ1MIX_INPUT_3_VOLUME:
	हाल ARIZONA_EQ1MIX_INPUT_4_SOURCE:
	हाल ARIZONA_EQ1MIX_INPUT_4_VOLUME:
	हाल ARIZONA_EQ2MIX_INPUT_1_SOURCE:
	हाल ARIZONA_EQ2MIX_INPUT_1_VOLUME:
	हाल ARIZONA_EQ2MIX_INPUT_2_SOURCE:
	हाल ARIZONA_EQ2MIX_INPUT_2_VOLUME:
	हाल ARIZONA_EQ2MIX_INPUT_3_SOURCE:
	हाल ARIZONA_EQ2MIX_INPUT_3_VOLUME:
	हाल ARIZONA_EQ2MIX_INPUT_4_SOURCE:
	हाल ARIZONA_EQ2MIX_INPUT_4_VOLUME:
	हाल ARIZONA_EQ3MIX_INPUT_1_SOURCE:
	हाल ARIZONA_EQ3MIX_INPUT_1_VOLUME:
	हाल ARIZONA_EQ3MIX_INPUT_2_SOURCE:
	हाल ARIZONA_EQ3MIX_INPUT_2_VOLUME:
	हाल ARIZONA_EQ3MIX_INPUT_3_SOURCE:
	हाल ARIZONA_EQ3MIX_INPUT_3_VOLUME:
	हाल ARIZONA_EQ3MIX_INPUT_4_SOURCE:
	हाल ARIZONA_EQ3MIX_INPUT_4_VOLUME:
	हाल ARIZONA_EQ4MIX_INPUT_1_SOURCE:
	हाल ARIZONA_EQ4MIX_INPUT_1_VOLUME:
	हाल ARIZONA_EQ4MIX_INPUT_2_SOURCE:
	हाल ARIZONA_EQ4MIX_INPUT_2_VOLUME:
	हाल ARIZONA_EQ4MIX_INPUT_3_SOURCE:
	हाल ARIZONA_EQ4MIX_INPUT_3_VOLUME:
	हाल ARIZONA_EQ4MIX_INPUT_4_SOURCE:
	हाल ARIZONA_EQ4MIX_INPUT_4_VOLUME:
	हाल ARIZONA_DRC1LMIX_INPUT_1_SOURCE:
	हाल ARIZONA_DRC1LMIX_INPUT_1_VOLUME:
	हाल ARIZONA_DRC1LMIX_INPUT_2_SOURCE:
	हाल ARIZONA_DRC1LMIX_INPUT_2_VOLUME:
	हाल ARIZONA_DRC1LMIX_INPUT_3_SOURCE:
	हाल ARIZONA_DRC1LMIX_INPUT_3_VOLUME:
	हाल ARIZONA_DRC1LMIX_INPUT_4_SOURCE:
	हाल ARIZONA_DRC1LMIX_INPUT_4_VOLUME:
	हाल ARIZONA_DRC1RMIX_INPUT_1_SOURCE:
	हाल ARIZONA_DRC1RMIX_INPUT_1_VOLUME:
	हाल ARIZONA_DRC1RMIX_INPUT_2_SOURCE:
	हाल ARIZONA_DRC1RMIX_INPUT_2_VOLUME:
	हाल ARIZONA_DRC1RMIX_INPUT_3_SOURCE:
	हाल ARIZONA_DRC1RMIX_INPUT_3_VOLUME:
	हाल ARIZONA_DRC1RMIX_INPUT_4_SOURCE:
	हाल ARIZONA_DRC1RMIX_INPUT_4_VOLUME:
	हाल ARIZONA_HPLP1MIX_INPUT_1_SOURCE:
	हाल ARIZONA_HPLP1MIX_INPUT_1_VOLUME:
	हाल ARIZONA_HPLP1MIX_INPUT_2_SOURCE:
	हाल ARIZONA_HPLP1MIX_INPUT_2_VOLUME:
	हाल ARIZONA_HPLP1MIX_INPUT_3_SOURCE:
	हाल ARIZONA_HPLP1MIX_INPUT_3_VOLUME:
	हाल ARIZONA_HPLP1MIX_INPUT_4_SOURCE:
	हाल ARIZONA_HPLP1MIX_INPUT_4_VOLUME:
	हाल ARIZONA_HPLP2MIX_INPUT_1_SOURCE:
	हाल ARIZONA_HPLP2MIX_INPUT_1_VOLUME:
	हाल ARIZONA_HPLP2MIX_INPUT_2_SOURCE:
	हाल ARIZONA_HPLP2MIX_INPUT_2_VOLUME:
	हाल ARIZONA_HPLP2MIX_INPUT_3_SOURCE:
	हाल ARIZONA_HPLP2MIX_INPUT_3_VOLUME:
	हाल ARIZONA_HPLP2MIX_INPUT_4_SOURCE:
	हाल ARIZONA_HPLP2MIX_INPUT_4_VOLUME:
	हाल ARIZONA_HPLP3MIX_INPUT_1_SOURCE:
	हाल ARIZONA_HPLP3MIX_INPUT_1_VOLUME:
	हाल ARIZONA_HPLP3MIX_INPUT_2_SOURCE:
	हाल ARIZONA_HPLP3MIX_INPUT_2_VOLUME:
	हाल ARIZONA_HPLP3MIX_INPUT_3_SOURCE:
	हाल ARIZONA_HPLP3MIX_INPUT_3_VOLUME:
	हाल ARIZONA_HPLP3MIX_INPUT_4_SOURCE:
	हाल ARIZONA_HPLP3MIX_INPUT_4_VOLUME:
	हाल ARIZONA_HPLP4MIX_INPUT_1_SOURCE:
	हाल ARIZONA_HPLP4MIX_INPUT_1_VOLUME:
	हाल ARIZONA_HPLP4MIX_INPUT_2_SOURCE:
	हाल ARIZONA_HPLP4MIX_INPUT_2_VOLUME:
	हाल ARIZONA_HPLP4MIX_INPUT_3_SOURCE:
	हाल ARIZONA_HPLP4MIX_INPUT_3_VOLUME:
	हाल ARIZONA_HPLP4MIX_INPUT_4_SOURCE:
	हाल ARIZONA_HPLP4MIX_INPUT_4_VOLUME:
	हाल ARIZONA_DSP1LMIX_INPUT_1_SOURCE:
	हाल ARIZONA_DSP1LMIX_INPUT_1_VOLUME:
	हाल ARIZONA_DSP1LMIX_INPUT_2_SOURCE:
	हाल ARIZONA_DSP1LMIX_INPUT_2_VOLUME:
	हाल ARIZONA_DSP1LMIX_INPUT_3_SOURCE:
	हाल ARIZONA_DSP1LMIX_INPUT_3_VOLUME:
	हाल ARIZONA_DSP1LMIX_INPUT_4_SOURCE:
	हाल ARIZONA_DSP1LMIX_INPUT_4_VOLUME:
	हाल ARIZONA_DSP1RMIX_INPUT_1_SOURCE:
	हाल ARIZONA_DSP1RMIX_INPUT_1_VOLUME:
	हाल ARIZONA_DSP1RMIX_INPUT_2_SOURCE:
	हाल ARIZONA_DSP1RMIX_INPUT_2_VOLUME:
	हाल ARIZONA_DSP1RMIX_INPUT_3_SOURCE:
	हाल ARIZONA_DSP1RMIX_INPUT_3_VOLUME:
	हाल ARIZONA_DSP1RMIX_INPUT_4_SOURCE:
	हाल ARIZONA_DSP1RMIX_INPUT_4_VOLUME:
	हाल ARIZONA_DSP1AUX1MIX_INPUT_1_SOURCE:
	हाल ARIZONA_DSP1AUX2MIX_INPUT_1_SOURCE:
	हाल ARIZONA_DSP1AUX3MIX_INPUT_1_SOURCE:
	हाल ARIZONA_DSP1AUX4MIX_INPUT_1_SOURCE:
	हाल ARIZONA_DSP1AUX5MIX_INPUT_1_SOURCE:
	हाल ARIZONA_DSP1AUX6MIX_INPUT_1_SOURCE:
	हाल ARIZONA_ASRC1LMIX_INPUT_1_SOURCE:
	हाल ARIZONA_ASRC1RMIX_INPUT_1_SOURCE:
	हाल ARIZONA_ASRC2LMIX_INPUT_1_SOURCE:
	हाल ARIZONA_ASRC2RMIX_INPUT_1_SOURCE:
	हाल ARIZONA_ISRC1DEC1MIX_INPUT_1_SOURCE:
	हाल ARIZONA_ISRC1DEC2MIX_INPUT_1_SOURCE:
	हाल ARIZONA_ISRC1INT1MIX_INPUT_1_SOURCE:
	हाल ARIZONA_ISRC1INT2MIX_INPUT_1_SOURCE:
	हाल ARIZONA_ISRC2DEC1MIX_INPUT_1_SOURCE:
	हाल ARIZONA_ISRC2DEC2MIX_INPUT_1_SOURCE:
	हाल ARIZONA_ISRC2INT1MIX_INPUT_1_SOURCE:
	हाल ARIZONA_ISRC2INT2MIX_INPUT_1_SOURCE:
	हाल ARIZONA_GPIO1_CTRL:
	हाल ARIZONA_GPIO2_CTRL:
	हाल ARIZONA_GPIO3_CTRL:
	हाल ARIZONA_GPIO4_CTRL:
	हाल ARIZONA_GPIO5_CTRL:
	हाल ARIZONA_IRQ_CTRL_1:
	हाल ARIZONA_GPIO_DEBOUNCE_CONFIG:
	हाल ARIZONA_MISC_PAD_CTRL_1:
	हाल ARIZONA_MISC_PAD_CTRL_2:
	हाल ARIZONA_MISC_PAD_CTRL_3:
	हाल ARIZONA_MISC_PAD_CTRL_4:
	हाल ARIZONA_MISC_PAD_CTRL_5:
	हाल ARIZONA_MISC_PAD_CTRL_6:
	हाल ARIZONA_INTERRUPT_STATUS_1:
	हाल ARIZONA_INTERRUPT_STATUS_2:
	हाल ARIZONA_INTERRUPT_STATUS_3:
	हाल ARIZONA_INTERRUPT_STATUS_4:
	हाल ARIZONA_INTERRUPT_STATUS_5:
	हाल ARIZONA_INTERRUPT_STATUS_1_MASK:
	हाल ARIZONA_INTERRUPT_STATUS_2_MASK:
	हाल ARIZONA_INTERRUPT_STATUS_3_MASK:
	हाल ARIZONA_INTERRUPT_STATUS_4_MASK:
	हाल ARIZONA_INTERRUPT_STATUS_5_MASK:
	हाल ARIZONA_INTERRUPT_CONTROL:
	हाल ARIZONA_IRQ2_STATUS_1:
	हाल ARIZONA_IRQ2_STATUS_2:
	हाल ARIZONA_IRQ2_STATUS_3:
	हाल ARIZONA_IRQ2_STATUS_4:
	हाल ARIZONA_IRQ2_STATUS_5:
	हाल ARIZONA_IRQ2_STATUS_1_MASK:
	हाल ARIZONA_IRQ2_STATUS_2_MASK:
	हाल ARIZONA_IRQ2_STATUS_3_MASK:
	हाल ARIZONA_IRQ2_STATUS_4_MASK:
	हाल ARIZONA_IRQ2_STATUS_5_MASK:
	हाल ARIZONA_IRQ2_CONTROL:
	हाल ARIZONA_INTERRUPT_RAW_STATUS_2:
	हाल ARIZONA_INTERRUPT_RAW_STATUS_3:
	हाल ARIZONA_INTERRUPT_RAW_STATUS_4:
	हाल ARIZONA_INTERRUPT_RAW_STATUS_5:
	हाल ARIZONA_INTERRUPT_RAW_STATUS_6:
	हाल ARIZONA_INTERRUPT_RAW_STATUS_7:
	हाल ARIZONA_INTERRUPT_RAW_STATUS_8:
	हाल ARIZONA_IRQ_PIN_STATUS:
	हाल ARIZONA_ADSP2_IRQ0:
	हाल ARIZONA_AOD_WKUP_AND_TRIG:
	हाल ARIZONA_AOD_IRQ1:
	हाल ARIZONA_AOD_IRQ2:
	हाल ARIZONA_AOD_IRQ_MASK_IRQ1:
	हाल ARIZONA_AOD_IRQ_MASK_IRQ2:
	हाल ARIZONA_AOD_IRQ_RAW_STATUS:
	हाल ARIZONA_JACK_DETECT_DEBOUNCE:
	हाल ARIZONA_FX_CTRL1:
	हाल ARIZONA_FX_CTRL2:
	हाल ARIZONA_EQ1_1:
	हाल ARIZONA_EQ1_2:
	हाल ARIZONA_EQ1_3:
	हाल ARIZONA_EQ1_4:
	हाल ARIZONA_EQ1_5:
	हाल ARIZONA_EQ1_6:
	हाल ARIZONA_EQ1_7:
	हाल ARIZONA_EQ1_8:
	हाल ARIZONA_EQ1_9:
	हाल ARIZONA_EQ1_10:
	हाल ARIZONA_EQ1_11:
	हाल ARIZONA_EQ1_12:
	हाल ARIZONA_EQ1_13:
	हाल ARIZONA_EQ1_14:
	हाल ARIZONA_EQ1_15:
	हाल ARIZONA_EQ1_16:
	हाल ARIZONA_EQ1_17:
	हाल ARIZONA_EQ1_18:
	हाल ARIZONA_EQ1_19:
	हाल ARIZONA_EQ1_20:
	हाल ARIZONA_EQ1_21:
	हाल ARIZONA_EQ2_1:
	हाल ARIZONA_EQ2_2:
	हाल ARIZONA_EQ2_3:
	हाल ARIZONA_EQ2_4:
	हाल ARIZONA_EQ2_5:
	हाल ARIZONA_EQ2_6:
	हाल ARIZONA_EQ2_7:
	हाल ARIZONA_EQ2_8:
	हाल ARIZONA_EQ2_9:
	हाल ARIZONA_EQ2_10:
	हाल ARIZONA_EQ2_11:
	हाल ARIZONA_EQ2_12:
	हाल ARIZONA_EQ2_13:
	हाल ARIZONA_EQ2_14:
	हाल ARIZONA_EQ2_15:
	हाल ARIZONA_EQ2_16:
	हाल ARIZONA_EQ2_17:
	हाल ARIZONA_EQ2_18:
	हाल ARIZONA_EQ2_19:
	हाल ARIZONA_EQ2_20:
	हाल ARIZONA_EQ2_21:
	हाल ARIZONA_EQ3_1:
	हाल ARIZONA_EQ3_2:
	हाल ARIZONA_EQ3_3:
	हाल ARIZONA_EQ3_4:
	हाल ARIZONA_EQ3_5:
	हाल ARIZONA_EQ3_6:
	हाल ARIZONA_EQ3_7:
	हाल ARIZONA_EQ3_8:
	हाल ARIZONA_EQ3_9:
	हाल ARIZONA_EQ3_10:
	हाल ARIZONA_EQ3_11:
	हाल ARIZONA_EQ3_12:
	हाल ARIZONA_EQ3_13:
	हाल ARIZONA_EQ3_14:
	हाल ARIZONA_EQ3_15:
	हाल ARIZONA_EQ3_16:
	हाल ARIZONA_EQ3_17:
	हाल ARIZONA_EQ3_18:
	हाल ARIZONA_EQ3_19:
	हाल ARIZONA_EQ3_20:
	हाल ARIZONA_EQ3_21:
	हाल ARIZONA_EQ4_1:
	हाल ARIZONA_EQ4_2:
	हाल ARIZONA_EQ4_3:
	हाल ARIZONA_EQ4_4:
	हाल ARIZONA_EQ4_5:
	हाल ARIZONA_EQ4_6:
	हाल ARIZONA_EQ4_7:
	हाल ARIZONA_EQ4_8:
	हाल ARIZONA_EQ4_9:
	हाल ARIZONA_EQ4_10:
	हाल ARIZONA_EQ4_11:
	हाल ARIZONA_EQ4_12:
	हाल ARIZONA_EQ4_13:
	हाल ARIZONA_EQ4_14:
	हाल ARIZONA_EQ4_15:
	हाल ARIZONA_EQ4_16:
	हाल ARIZONA_EQ4_17:
	हाल ARIZONA_EQ4_18:
	हाल ARIZONA_EQ4_19:
	हाल ARIZONA_EQ4_20:
	हाल ARIZONA_EQ4_21:
	हाल ARIZONA_DRC1_CTRL1:
	हाल ARIZONA_DRC1_CTRL2:
	हाल ARIZONA_DRC1_CTRL3:
	हाल ARIZONA_DRC1_CTRL4:
	हाल ARIZONA_DRC1_CTRL5:
	हाल ARIZONA_HPLPF1_1:
	हाल ARIZONA_HPLPF1_2:
	हाल ARIZONA_HPLPF2_1:
	हाल ARIZONA_HPLPF2_2:
	हाल ARIZONA_HPLPF3_1:
	हाल ARIZONA_HPLPF3_2:
	हाल ARIZONA_HPLPF4_1:
	हाल ARIZONA_HPLPF4_2:
	हाल ARIZONA_ASRC_ENABLE:
	हाल ARIZONA_ASRC_RATE1:
	हाल ARIZONA_ASRC_RATE2:
	हाल ARIZONA_ISRC_1_CTRL_1:
	हाल ARIZONA_ISRC_1_CTRL_2:
	हाल ARIZONA_ISRC_1_CTRL_3:
	हाल ARIZONA_ISRC_2_CTRL_1:
	हाल ARIZONA_ISRC_2_CTRL_2:
	हाल ARIZONA_ISRC_2_CTRL_3:
	हाल ARIZONA_DSP1_CONTROL_1:
	हाल ARIZONA_DSP1_CLOCKING_1:
	हाल ARIZONA_DSP1_STATUS_1:
	हाल ARIZONA_DSP1_STATUS_2:
	हाल ARIZONA_DSP1_STATUS_3:
	हाल ARIZONA_DSP1_WDMA_BUFFER_1:
	हाल ARIZONA_DSP1_WDMA_BUFFER_2:
	हाल ARIZONA_DSP1_WDMA_BUFFER_3:
	हाल ARIZONA_DSP1_WDMA_BUFFER_4:
	हाल ARIZONA_DSP1_WDMA_BUFFER_5:
	हाल ARIZONA_DSP1_WDMA_BUFFER_6:
	हाल ARIZONA_DSP1_WDMA_BUFFER_7:
	हाल ARIZONA_DSP1_WDMA_BUFFER_8:
	हाल ARIZONA_DSP1_RDMA_BUFFER_1:
	हाल ARIZONA_DSP1_RDMA_BUFFER_2:
	हाल ARIZONA_DSP1_RDMA_BUFFER_3:
	हाल ARIZONA_DSP1_RDMA_BUFFER_4:
	हाल ARIZONA_DSP1_RDMA_BUFFER_5:
	हाल ARIZONA_DSP1_RDMA_BUFFER_6:
	हाल ARIZONA_DSP1_WDMA_CONFIG_1:
	हाल ARIZONA_DSP1_WDMA_CONFIG_2:
	हाल ARIZONA_DSP1_RDMA_CONFIG_1:
	हाल ARIZONA_DSP1_SCRATCH_0:
	हाल ARIZONA_DSP1_SCRATCH_1:
	हाल ARIZONA_DSP1_SCRATCH_2:
	हाल ARIZONA_DSP1_SCRATCH_3:
		वापस true;
	शेष:
		अगर ((reg >= 0x100000 && reg < 0x106000) ||
		    (reg >= 0x180000 && reg < 0x180800) ||
		    (reg >= 0x190000 && reg < 0x194800) ||
		    (reg >= 0x1a8000 && reg < 0x1a9800))
			वापस true;
		अन्यथा
			वापस false;
	पूर्ण
पूर्ण

अटल bool wm5102_अस्थिर_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल ARIZONA_SOFTWARE_RESET:
	हाल ARIZONA_DEVICE_REVISION:
	हाल ARIZONA_WRITE_SEQUENCER_CTRL_0:
	हाल ARIZONA_WRITE_SEQUENCER_CTRL_1:
	हाल ARIZONA_WRITE_SEQUENCER_CTRL_2:
	हाल ARIZONA_WRITE_SEQUENCER_CTRL_3:
	हाल ARIZONA_OUTPUT_STATUS_1:
	हाल ARIZONA_SLIMBUS_RX_PORT_STATUS:
	हाल ARIZONA_SLIMBUS_TX_PORT_STATUS:
	हाल ARIZONA_SAMPLE_RATE_1_STATUS:
	हाल ARIZONA_SAMPLE_RATE_2_STATUS:
	हाल ARIZONA_SAMPLE_RATE_3_STATUS:
	हाल ARIZONA_HAPTICS_STATUS:
	हाल ARIZONA_ASYNC_SAMPLE_RATE_1_STATUS:
	हाल ARIZONA_ASYNC_SAMPLE_RATE_2_STATUS:
	हाल ARIZONA_DAC_COMP_1:
	हाल ARIZONA_DAC_COMP_2:
	हाल ARIZONA_DAC_COMP_3:
	हाल ARIZONA_DAC_COMP_4:
	हाल ARIZONA_FX_CTRL2:
	हाल ARIZONA_INTERRUPT_STATUS_1:
	हाल ARIZONA_INTERRUPT_STATUS_2:
	हाल ARIZONA_INTERRUPT_STATUS_3:
	हाल ARIZONA_INTERRUPT_STATUS_4:
	हाल ARIZONA_INTERRUPT_STATUS_5:
	हाल ARIZONA_IRQ2_STATUS_1:
	हाल ARIZONA_IRQ2_STATUS_2:
	हाल ARIZONA_IRQ2_STATUS_3:
	हाल ARIZONA_IRQ2_STATUS_4:
	हाल ARIZONA_IRQ2_STATUS_5:
	हाल ARIZONA_INTERRUPT_RAW_STATUS_2:
	हाल ARIZONA_INTERRUPT_RAW_STATUS_3:
	हाल ARIZONA_INTERRUPT_RAW_STATUS_4:
	हाल ARIZONA_INTERRUPT_RAW_STATUS_5:
	हाल ARIZONA_INTERRUPT_RAW_STATUS_6:
	हाल ARIZONA_INTERRUPT_RAW_STATUS_7:
	हाल ARIZONA_INTERRUPT_RAW_STATUS_8:
	हाल ARIZONA_IRQ_PIN_STATUS:
	हाल ARIZONA_AOD_WKUP_AND_TRIG:
	हाल ARIZONA_AOD_IRQ1:
	हाल ARIZONA_AOD_IRQ2:
	हाल ARIZONA_AOD_IRQ_RAW_STATUS:
	हाल ARIZONA_DSP1_CLOCKING_1:
	हाल ARIZONA_DSP1_STATUS_1:
	हाल ARIZONA_DSP1_STATUS_2:
	हाल ARIZONA_DSP1_STATUS_3:
	हाल ARIZONA_DSP1_WDMA_BUFFER_1:
	हाल ARIZONA_DSP1_WDMA_BUFFER_2:
	हाल ARIZONA_DSP1_WDMA_BUFFER_3:
	हाल ARIZONA_DSP1_WDMA_BUFFER_4:
	हाल ARIZONA_DSP1_WDMA_BUFFER_5:
	हाल ARIZONA_DSP1_WDMA_BUFFER_6:
	हाल ARIZONA_DSP1_WDMA_BUFFER_7:
	हाल ARIZONA_DSP1_WDMA_BUFFER_8:
	हाल ARIZONA_DSP1_RDMA_BUFFER_1:
	हाल ARIZONA_DSP1_RDMA_BUFFER_2:
	हाल ARIZONA_DSP1_RDMA_BUFFER_3:
	हाल ARIZONA_DSP1_RDMA_BUFFER_4:
	हाल ARIZONA_DSP1_RDMA_BUFFER_5:
	हाल ARIZONA_DSP1_RDMA_BUFFER_6:
	हाल ARIZONA_DSP1_WDMA_CONFIG_1:
	हाल ARIZONA_DSP1_WDMA_CONFIG_2:
	हाल ARIZONA_DSP1_RDMA_CONFIG_1:
	हाल ARIZONA_DSP1_SCRATCH_0:
	हाल ARIZONA_DSP1_SCRATCH_1:
	हाल ARIZONA_DSP1_SCRATCH_2:
	हाल ARIZONA_DSP1_SCRATCH_3:
	हाल ARIZONA_HP_CTRL_1L:
	हाल ARIZONA_HP_CTRL_1R:
	हाल ARIZONA_HEADPHONE_DETECT_2:
	हाल ARIZONA_HP_DACVAL:
	हाल ARIZONA_MIC_DETECT_3:
		वापस true;
	शेष:
		अगर ((reg >= 0x100000 && reg < 0x106000) ||
		    (reg >= 0x180000 && reg < 0x180800) ||
		    (reg >= 0x190000 && reg < 0x194800) ||
		    (reg >= 0x1a8000 && reg < 0x1a9800))
			वापस true;
		अन्यथा
			वापस false;
	पूर्ण
पूर्ण

#घोषणा WM5102_MAX_REGISTER 0x1a9800

स्थिर काष्ठा regmap_config wm5102_spi_regmap = अणु
	.reg_bits = 32,
	.pad_bits = 16,
	.val_bits = 16,
	.reg_क्रमmat_endian = REGMAP_ENDIAN_BIG,
	.val_क्रमmat_endian = REGMAP_ENDIAN_BIG,

	.max_रेजिस्टर = WM5102_MAX_REGISTER,
	.पढ़ोable_reg = wm5102_पढ़ोable_रेजिस्टर,
	.अस्थिर_reg = wm5102_अस्थिर_रेजिस्टर,

	.cache_type = REGCACHE_RBTREE,
	.reg_शेषs = wm5102_reg_शेष,
	.num_reg_शेषs = ARRAY_SIZE(wm5102_reg_शेष),
पूर्ण;
EXPORT_SYMBOL_GPL(wm5102_spi_regmap);

स्थिर काष्ठा regmap_config wm5102_i2c_regmap = अणु
	.reg_bits = 32,
	.val_bits = 16,
	.reg_क्रमmat_endian = REGMAP_ENDIAN_BIG,
	.val_क्रमmat_endian = REGMAP_ENDIAN_BIG,

	.max_रेजिस्टर = WM5102_MAX_REGISTER,
	.पढ़ोable_reg = wm5102_पढ़ोable_रेजिस्टर,
	.अस्थिर_reg = wm5102_अस्थिर_रेजिस्टर,

	.cache_type = REGCACHE_RBTREE,
	.reg_शेषs = wm5102_reg_शेष,
	.num_reg_शेषs = ARRAY_SIZE(wm5102_reg_शेष),
पूर्ण;
EXPORT_SYMBOL_GPL(wm5102_i2c_regmap);
