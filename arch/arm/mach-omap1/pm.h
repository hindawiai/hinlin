<शैली गुरु>
/*
 * arch/arm/mach-omap1/pm.h
 *
 * Header file क्रम OMAP1 Power Management Routines
 *
 * Author: MontaVista Software, Inc.
 *	   support@mvista.com
 *
 * Copyright 2002 MontaVista Software Inc.
 *
 * Cleanup 2004 क्रम Linux 2.6 by Dirk Behme <dirk.behme@de.bosch.com>
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN
 * NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY सूचीECT, INसूचीECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
 * USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * You should have received a copy of the GNU General Public License aदीर्घ
 * with this program; अगर not, ग_लिखो to the Free Software Foundation, Inc.,
 * 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#अगर_अघोषित __ARCH_ARM_MACH_OMAP1_PM_H
#घोषणा __ARCH_ARM_MACH_OMAP1_PM_H

/*
 * ----------------------------------------------------------------------------
 * Register and offset definitions to be used in PM assembler code
 * ----------------------------------------------------------------------------
 */
#घोषणा CLKGEN_REG_ASM_BASE		OMAP1_IO_ADDRESS(0xfffece00)
#घोषणा ARM_IDLECT1_ASM_OFFSET		0x04
#घोषणा ARM_IDLECT2_ASM_OFFSET		0x08

#घोषणा TCMIF_ASM_BASE			OMAP1_IO_ADDRESS(0xfffecc00)
#घोषणा EMIFS_CONFIG_ASM_OFFSET		0x0c
#घोषणा EMIFF_SDRAM_CONFIG_ASM_OFFSET	0x20

/*
 * ----------------------------------------------------------------------------
 * Power management biपंचांगasks
 * ----------------------------------------------------------------------------
 */
#घोषणा IDLE_WAIT_CYCLES		0x00000fff
#घोषणा PERIPHERAL_ENABLE		0x2

#घोषणा SELF_REFRESH_MODE		0x0c000001
#घोषणा IDLE_EMIFS_REQUEST		0xc
#घोषणा MODEM_32K_EN			0x1
#घोषणा PER_EN				0x1

#घोषणा CPU_SUSPEND_SIZE		200
#घोषणा ULPD_LOW_PWR_EN			0x0001
#घोषणा ULPD_DEEP_SLEEP_TRANSITION_EN	0x0010
#घोषणा ULPD_SETUP_ANALOG_CELL_3_VAL	0
#घोषणा ULPD_POWER_CTRL_REG_VAL		0x0219

#घोषणा DSP_IDLE_DELAY			10
#घोषणा DSP_IDLE			0x0040
#घोषणा DSP_RST				0x0004
#घोषणा DSP_ENABLE			0x0002
#घोषणा SUFFICIENT_DSP_RESET_TIME	1000
#घोषणा DEFAULT_MPUI_CONFIG		0x05cf
#घोषणा ENABLE_XORCLK			0x2
#घोषणा DSP_CLOCK_ENABLE		0x2000
#घोषणा DSP_IDLE_MODE			0x2
#घोषणा TC_IDLE_REQUEST			(0x0000000c)

#घोषणा IRQ_LEVEL2			(1<<0)
#घोषणा IRQ_KEYBOARD			(1<<1)
#घोषणा IRQ_UART2			(1<<15)

#घोषणा PDE_BIT				0x08
#घोषणा PWD_EN_BIT			0x04
#घोषणा EN_PERCK_BIT			0x04

#घोषणा OMAP1510_DEEP_SLEEP_REQUEST	0x0ec7
#घोषणा OMAP1510_BIG_SLEEP_REQUEST	0x0cc5
#घोषणा OMAP1510_IDLE_LOOP_REQUEST	0x0c00
#घोषणा OMAP1510_IDLE_CLOCK_DOMAINS	0x2

/* Both big sleep and deep sleep use same values. Dअगरference is in ULPD. */
#घोषणा OMAP1610_IDLECT1_SLEEP_VAL	0x13c7
#घोषणा OMAP1610_IDLECT2_SLEEP_VAL	0x09c7
#घोषणा OMAP1610_IDLECT3_VAL		0x3f
#घोषणा OMAP1610_IDLECT3_SLEEP_ORMASK	0x2c
#घोषणा OMAP1610_IDLECT3		0xfffece24
#घोषणा OMAP1610_IDLE_LOOP_REQUEST	0x0400

#घोषणा OMAP7XX_IDLECT1_SLEEP_VAL	0x16c7
#घोषणा OMAP7XX_IDLECT2_SLEEP_VAL	0x09c7
#घोषणा OMAP7XX_IDLECT3_VAL		0x3f
#घोषणा OMAP7XX_IDLECT3		0xfffece24
#घोषणा OMAP7XX_IDLE_LOOP_REQUEST	0x0C00

#अगर     !defined(CONFIG_ARCH_OMAP730) && \
	!defined(CONFIG_ARCH_OMAP850) && \
	!defined(CONFIG_ARCH_OMAP15XX) && \
	!defined(CONFIG_ARCH_OMAP16XX)
#warning "Power management for this processor not implemented yet"
#पूर्ण_अगर

#अगर_अघोषित __ASSEMBLER__

#समावेश <linux/clk.h>

बाह्य काष्ठा kset घातer_subsys;

बाह्य व्योम prevent_idle_sleep(व्योम);
बाह्य व्योम allow_idle_sleep(व्योम);

बाह्य व्योम omap1_pm_idle(व्योम);
बाह्य व्योम omap1_pm_suspend(व्योम);

बाह्य व्योम omap7xx_cpu_suspend(अचिन्हित दीर्घ, अचिन्हित दीर्घ);
बाह्य व्योम omap1510_cpu_suspend(अचिन्हित दीर्घ, अचिन्हित दीर्घ);
बाह्य व्योम omap1610_cpu_suspend(अचिन्हित दीर्घ, अचिन्हित दीर्घ);
बाह्य व्योम omap7xx_idle_loop_suspend(व्योम);
बाह्य व्योम omap1510_idle_loop_suspend(व्योम);
बाह्य व्योम omap1610_idle_loop_suspend(व्योम);

बाह्य अचिन्हित पूर्णांक omap7xx_cpu_suspend_sz;
बाह्य अचिन्हित पूर्णांक omap1510_cpu_suspend_sz;
बाह्य अचिन्हित पूर्णांक omap1610_cpu_suspend_sz;
बाह्य अचिन्हित पूर्णांक omap7xx_idle_loop_suspend_sz;
बाह्य अचिन्हित पूर्णांक omap1510_idle_loop_suspend_sz;
बाह्य अचिन्हित पूर्णांक omap1610_idle_loop_suspend_sz;

#अगर_घोषित CONFIG_OMAP_SERIAL_WAKE
बाह्य व्योम omap_serial_wake_trigger(पूर्णांक enable);
#अन्यथा
#घोषणा omap_serial_wakeup_init()	अणुपूर्ण
#घोषणा omap_serial_wake_trigger(x)	अणुपूर्ण
#पूर्ण_अगर	/* CONFIG_OMAP_SERIAL_WAKE */

#घोषणा ARM_SAVE(x) arm_sleep_save[ARM_SLEEP_SAVE_##x] = omap_पढ़ोl(x)
#घोषणा ARM_RESTORE(x) omap_ग_लिखोl((arm_sleep_save[ARM_SLEEP_SAVE_##x]), (x))
#घोषणा ARM_SHOW(x) arm_sleep_save[ARM_SLEEP_SAVE_##x]

#घोषणा DSP_SAVE(x) dsp_sleep_save[DSP_SLEEP_SAVE_##x] = __raw_पढ़ोw(x)
#घोषणा DSP_RESTORE(x) __raw_ग_लिखोw((dsp_sleep_save[DSP_SLEEP_SAVE_##x]), (x))
#घोषणा DSP_SHOW(x) dsp_sleep_save[DSP_SLEEP_SAVE_##x]

#घोषणा ULPD_SAVE(x) ulpd_sleep_save[ULPD_SLEEP_SAVE_##x] = omap_पढ़ोw(x)
#घोषणा ULPD_RESTORE(x) omap_ग_लिखोw((ulpd_sleep_save[ULPD_SLEEP_SAVE_##x]), (x))
#घोषणा ULPD_SHOW(x) ulpd_sleep_save[ULPD_SLEEP_SAVE_##x]

#घोषणा MPUI7XX_SAVE(x) mpui7xx_sleep_save[MPUI7XX_SLEEP_SAVE_##x] = omap_पढ़ोl(x)
#घोषणा MPUI7XX_RESTORE(x) omap_ग_लिखोl((mpui7xx_sleep_save[MPUI7XX_SLEEP_SAVE_##x]), (x))
#घोषणा MPUI7XX_SHOW(x) mpui7xx_sleep_save[MPUI7XX_SLEEP_SAVE_##x]

#घोषणा MPUI1510_SAVE(x) mpui1510_sleep_save[MPUI1510_SLEEP_SAVE_##x] = omap_पढ़ोl(x)
#घोषणा MPUI1510_RESTORE(x) omap_ग_लिखोl((mpui1510_sleep_save[MPUI1510_SLEEP_SAVE_##x]), (x))
#घोषणा MPUI1510_SHOW(x) mpui1510_sleep_save[MPUI1510_SLEEP_SAVE_##x]

#घोषणा MPUI1610_SAVE(x) mpui1610_sleep_save[MPUI1610_SLEEP_SAVE_##x] = omap_पढ़ोl(x)
#घोषणा MPUI1610_RESTORE(x) omap_ग_लिखोl((mpui1610_sleep_save[MPUI1610_SLEEP_SAVE_##x]), (x))
#घोषणा MPUI1610_SHOW(x) mpui1610_sleep_save[MPUI1610_SLEEP_SAVE_##x]

/*
 * List of global OMAP रेजिस्टरs to preserve.
 * More ones like CP and general purpose रेजिस्टर values are preserved
 * with the stack poपूर्णांकer in sleep.S.
 */

क्रमागत arm_save_state अणु
	ARM_SLEEP_SAVE_START = 0,
	/*
	 * MPU control रेजिस्टरs 32 bits
	 */
	ARM_SLEEP_SAVE_ARM_CKCTL,
	ARM_SLEEP_SAVE_ARM_IDLECT1,
	ARM_SLEEP_SAVE_ARM_IDLECT2,
	ARM_SLEEP_SAVE_ARM_IDLECT3,
	ARM_SLEEP_SAVE_ARM_EWUPCT,
	ARM_SLEEP_SAVE_ARM_RSTCT1,
	ARM_SLEEP_SAVE_ARM_RSTCT2,
	ARM_SLEEP_SAVE_ARM_SYSST,
	ARM_SLEEP_SAVE_SIZE
पूर्ण;

क्रमागत dsp_save_state अणु
	DSP_SLEEP_SAVE_START = 0,
	/*
	 * DSP रेजिस्टरs 16 bits
	 */
	DSP_SLEEP_SAVE_DSP_IDLECT2,
	DSP_SLEEP_SAVE_SIZE
पूर्ण;

क्रमागत ulpd_save_state अणु
	ULPD_SLEEP_SAVE_START = 0,
	/*
	 * ULPD रेजिस्टरs 16 bits
	 */
	ULPD_SLEEP_SAVE_ULPD_IT_STATUS,
	ULPD_SLEEP_SAVE_ULPD_CLOCK_CTRL,
	ULPD_SLEEP_SAVE_ULPD_SOFT_REQ,
	ULPD_SLEEP_SAVE_ULPD_STATUS_REQ,
	ULPD_SLEEP_SAVE_ULPD_DPLL_CTRL,
	ULPD_SLEEP_SAVE_ULPD_POWER_CTRL,
	ULPD_SLEEP_SAVE_SIZE
पूर्ण;

क्रमागत mpui1510_save_state अणु
	MPUI1510_SLEEP_SAVE_START = 0,
	/*
	 * MPUI रेजिस्टरs 32 bits
	 */
	MPUI1510_SLEEP_SAVE_MPUI_CTRL,
	MPUI1510_SLEEP_SAVE_MPUI_DSP_BOOT_CONFIG,
	MPUI1510_SLEEP_SAVE_MPUI_DSP_API_CONFIG,
	MPUI1510_SLEEP_SAVE_MPUI_DSP_STATUS,
	MPUI1510_SLEEP_SAVE_EMIFF_SDRAM_CONFIG,
	MPUI1510_SLEEP_SAVE_EMIFS_CONFIG,
	MPUI1510_SLEEP_SAVE_OMAP_IH1_MIR,
	MPUI1510_SLEEP_SAVE_OMAP_IH2_MIR,
#अगर defined(CONFIG_ARCH_OMAP15XX)
	MPUI1510_SLEEP_SAVE_SIZE
#अन्यथा
	MPUI1510_SLEEP_SAVE_SIZE = 0
#पूर्ण_अगर
पूर्ण;

क्रमागत mpui7xx_save_state अणु
	MPUI7XX_SLEEP_SAVE_START = 0,
	/*
	 * MPUI रेजिस्टरs 32 bits
	 */
	MPUI7XX_SLEEP_SAVE_MPUI_CTRL,
	MPUI7XX_SLEEP_SAVE_MPUI_DSP_BOOT_CONFIG,
	MPUI7XX_SLEEP_SAVE_MPUI_DSP_API_CONFIG,
	MPUI7XX_SLEEP_SAVE_MPUI_DSP_STATUS,
	MPUI7XX_SLEEP_SAVE_EMIFF_SDRAM_CONFIG,
	MPUI7XX_SLEEP_SAVE_EMIFS_CONFIG,
	MPUI7XX_SLEEP_SAVE_OMAP_IH1_MIR,
	MPUI7XX_SLEEP_SAVE_OMAP_IH2_0_MIR,
	MPUI7XX_SLEEP_SAVE_OMAP_IH2_1_MIR,
#अगर defined(CONFIG_ARCH_OMAP730) || defined(CONFIG_ARCH_OMAP850)
	MPUI7XX_SLEEP_SAVE_SIZE
#अन्यथा
	MPUI7XX_SLEEP_SAVE_SIZE = 0
#पूर्ण_अगर
पूर्ण;

क्रमागत mpui1610_save_state अणु
	MPUI1610_SLEEP_SAVE_START = 0,
	/*
	 * MPUI रेजिस्टरs 32 bits
	 */
	MPUI1610_SLEEP_SAVE_MPUI_CTRL,
	MPUI1610_SLEEP_SAVE_MPUI_DSP_BOOT_CONFIG,
	MPUI1610_SLEEP_SAVE_MPUI_DSP_API_CONFIG,
	MPUI1610_SLEEP_SAVE_MPUI_DSP_STATUS,
	MPUI1610_SLEEP_SAVE_EMIFF_SDRAM_CONFIG,
	MPUI1610_SLEEP_SAVE_EMIFS_CONFIG,
	MPUI1610_SLEEP_SAVE_OMAP_IH1_MIR,
	MPUI1610_SLEEP_SAVE_OMAP_IH2_0_MIR,
	MPUI1610_SLEEP_SAVE_OMAP_IH2_1_MIR,
	MPUI1610_SLEEP_SAVE_OMAP_IH2_2_MIR,
	MPUI1610_SLEEP_SAVE_OMAP_IH2_3_MIR,
#अगर defined(CONFIG_ARCH_OMAP16XX)
	MPUI1610_SLEEP_SAVE_SIZE
#अन्यथा
	MPUI1610_SLEEP_SAVE_SIZE = 0
#पूर्ण_अगर
पूर्ण;

#पूर्ण_अगर /* ASSEMBLER */
#पूर्ण_अगर /* __ASM_ARCH_OMAP_PM_H */
