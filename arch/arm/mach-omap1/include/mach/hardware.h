<शैली गुरु>
/*
 * arch/arm/mach-omap1/include/mach/hardware.h
 *
 * Hardware definitions क्रम TI OMAP processors and boards
 *
 * NOTE: Please put device driver specअगरic defines पूर्णांकo a separate header
 *	 file क्रम each driver.
 *
 * Copyright (C) 2001 RidgeRun, Inc.
 * Author: RidgeRun, Inc. Greg Lonnon <glonnon@ridgerun.com>
 *
 * Reorganized क्रम Linux-2.6 by Tony Lindgren <tony@atomide.com>
 *                          and Dirk Behme <dirk.behme@de.bosch.com>
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

#अगर_अघोषित __ASM_ARCH_OMAP_HARDWARE_H
#घोषणा __ASM_ARCH_OMAP_HARDWARE_H

#समावेश <linux/sizes.h>
#अगर_अघोषित __ASSEMBLER__
#समावेश <यंत्र/types.h>
#समावेश <mach/soc.h>

/*
 * NOTE: Please use ioremap + __raw_पढ़ो/ग_लिखो where possible instead of these
 */
बाह्य u8 omap_पढ़ोb(u32 pa);
बाह्य u16 omap_पढ़ोw(u32 pa);
बाह्य u32 omap_पढ़ोl(u32 pa);
बाह्य व्योम omap_ग_लिखोb(u8 v, u32 pa);
बाह्य व्योम omap_ग_लिखोw(u16 v, u32 pa);
बाह्य व्योम omap_ग_लिखोl(u32 v, u32 pa);

#समावेश <mach/tc.h>

/* Almost all करोcumentation क्रम chip and board memory maps assumes
 * BM is clear.  Most devel boards have a चयन to control booting
 * from NOR flash (using बाह्यal chipselect 3) rather than mask ROM,
 * which uses BM to पूर्णांकerchange the physical CS0 and CS3 addresses.
 */
अटल अंतरभूत u32 omap_cs0m_phys(व्योम)
अणु
	वापस (omap_पढ़ोl(EMIFS_CONFIG) & OMAP_EMIFS_CONFIG_BM)
			?  OMAP_CS3_PHYS : 0;
पूर्ण

अटल अंतरभूत u32 omap_cs3_phys(व्योम)
अणु
	वापस (omap_पढ़ोl(EMIFS_CONFIG) & OMAP_EMIFS_CONFIG_BM)
			? 0 : OMAP_CS3_PHYS;
पूर्ण

#पूर्ण_अगर	/* अगरndef __ASSEMBLER__ */

#घोषणा OMAP1_IO_OFFSET		0x01000000	/* Virtual IO = 0xfefb0000 */
#घोषणा OMAP1_IO_ADDRESS(pa)	IOMEM((pa) - OMAP1_IO_OFFSET)

#समावेश <mach/serial.h>

/*
 * ---------------------------------------------------------------------------
 * Common definitions क्रम all OMAP processors
 * NOTE: Put all processor or board specअगरic parts to the special header
 *	 files.
 * ---------------------------------------------------------------------------
 */

/*
 * ----------------------------------------------------------------------------
 * Timers
 * ----------------------------------------------------------------------------
 */
#घोषणा OMAP_MPU_TIMER1_BASE	(0xfffec500)
#घोषणा OMAP_MPU_TIMER2_BASE	(0xfffec600)
#घोषणा OMAP_MPU_TIMER3_BASE	(0xfffec700)
#घोषणा MPU_TIMER_FREE		(1 << 6)
#घोषणा MPU_TIMER_CLOCK_ENABLE	(1 << 5)
#घोषणा MPU_TIMER_AR		(1 << 1)
#घोषणा MPU_TIMER_ST		(1 << 0)

/*
 * ----------------------------------------------------------------------------
 * Clocks
 * ----------------------------------------------------------------------------
 */
#घोषणा CLKGEN_REG_BASE		(0xfffece00)
#घोषणा ARM_CKCTL		(CLKGEN_REG_BASE + 0x0)
#घोषणा ARM_IDLECT1		(CLKGEN_REG_BASE + 0x4)
#घोषणा ARM_IDLECT2		(CLKGEN_REG_BASE + 0x8)
#घोषणा ARM_EWUPCT		(CLKGEN_REG_BASE + 0xC)
#घोषणा ARM_RSTCT1		(CLKGEN_REG_BASE + 0x10)
#घोषणा ARM_RSTCT2		(CLKGEN_REG_BASE + 0x14)
#घोषणा ARM_SYSST		(CLKGEN_REG_BASE + 0x18)
#घोषणा ARM_IDLECT3		(CLKGEN_REG_BASE + 0x24)

#घोषणा CK_RATEF		1
#घोषणा CK_IDLEF		2
#घोषणा CK_ENABLEF		4
#घोषणा CK_SELECTF		8
#घोषणा SETARM_IDLE_SHIFT

/* DPLL control रेजिस्टरs */
#घोषणा DPLL_CTL		(0xfffecf00)

/* DSP घड़ी control. Must use __raw_पढ़ोw() and __raw_ग_लिखोw() with these */
#घोषणा DSP_CONFIG_REG_BASE     IOMEM(0xe1008000)
#घोषणा DSP_CKCTL		(DSP_CONFIG_REG_BASE + 0x0)
#घोषणा DSP_IDLECT1		(DSP_CONFIG_REG_BASE + 0x4)
#घोषणा DSP_IDLECT2		(DSP_CONFIG_REG_BASE + 0x8)
#घोषणा DSP_RSTCT2		(DSP_CONFIG_REG_BASE + 0x14)

/*
 * ---------------------------------------------------------------------------
 * UPLD
 * ---------------------------------------------------------------------------
 */
#घोषणा ULPD_REG_BASE		(0xfffe0800)
#घोषणा ULPD_IT_STATUS		(ULPD_REG_BASE + 0x14)
#घोषणा ULPD_SETUP_ANALOG_CELL_3	(ULPD_REG_BASE + 0x24)
#घोषणा ULPD_CLOCK_CTRL		(ULPD_REG_BASE + 0x30)
#	define DIS_USB_PVCI_CLK		(1 << 5)	/* no USB/FAC synch */
#	define USB_MCLK_EN		(1 << 4)	/* enable W4_USB_CLKO */
#घोषणा ULPD_SOFT_REQ		(ULPD_REG_BASE + 0x34)
#	define SOFT_UDC_REQ		(1 << 4)
#	define SOFT_USB_CLK_REQ		(1 << 3)
#	define SOFT_DPLL_REQ		(1 << 0)
#घोषणा ULPD_DPLL_CTRL		(ULPD_REG_BASE + 0x3c)
#घोषणा ULPD_STATUS_REQ		(ULPD_REG_BASE + 0x40)
#घोषणा ULPD_APLL_CTRL		(ULPD_REG_BASE + 0x4c)
#घोषणा ULPD_POWER_CTRL		(ULPD_REG_BASE + 0x50)
#घोषणा ULPD_SOFT_DISABLE_REQ_REG	(ULPD_REG_BASE + 0x68)
#	define DIS_MMC2_DPLL_REQ	(1 << 11)
#	define DIS_MMC1_DPLL_REQ	(1 << 10)
#	define DIS_UART3_DPLL_REQ	(1 << 9)
#	define DIS_UART2_DPLL_REQ	(1 << 8)
#	define DIS_UART1_DPLL_REQ	(1 << 7)
#	define DIS_USB_HOST_DPLL_REQ	(1 << 6)
#घोषणा ULPD_SDW_CLK_DIV_CTRL_SEL	(ULPD_REG_BASE + 0x74)
#घोषणा ULPD_CAM_CLK_CTRL	(ULPD_REG_BASE + 0x7c)

/*
 * ---------------------------------------------------------------------------
 * Watchकरोg समयr
 * ---------------------------------------------------------------------------
 */

/* Watchकरोg समयr within the OMAP3.2 gigacell */
#घोषणा OMAP_MPU_WATCHDOG_BASE	(0xfffec800)
#घोषणा OMAP_WDT_TIMER		(OMAP_MPU_WATCHDOG_BASE + 0x0)
#घोषणा OMAP_WDT_LOAD_TIM	(OMAP_MPU_WATCHDOG_BASE + 0x4)
#घोषणा OMAP_WDT_READ_TIM	(OMAP_MPU_WATCHDOG_BASE + 0x4)
#घोषणा OMAP_WDT_TIMER_MODE	(OMAP_MPU_WATCHDOG_BASE + 0x8)

/*
 * ---------------------------------------------------------------------------
 * Interrupts
 * ---------------------------------------------------------------------------
 */
#अगर_घोषित CONFIG_ARCH_OMAP1

/*
 * XXX: These probably want to be moved to arch/arm/mach-omap/omap1/irq.c
 * or something similar.. -- PFM.
 */

#घोषणा OMAP_IH1_BASE		0xfffecb00
#घोषणा OMAP_IH2_BASE		0xfffe0000

#घोषणा OMAP_IH1_ITR		(OMAP_IH1_BASE + 0x00)
#घोषणा OMAP_IH1_MIR		(OMAP_IH1_BASE + 0x04)
#घोषणा OMAP_IH1_SIR_IRQ	(OMAP_IH1_BASE + 0x10)
#घोषणा OMAP_IH1_SIR_FIQ	(OMAP_IH1_BASE + 0x14)
#घोषणा OMAP_IH1_CONTROL	(OMAP_IH1_BASE + 0x18)
#घोषणा OMAP_IH1_ILR0		(OMAP_IH1_BASE + 0x1c)
#घोषणा OMAP_IH1_ISR		(OMAP_IH1_BASE + 0x9c)

#घोषणा OMAP_IH2_ITR		(OMAP_IH2_BASE + 0x00)
#घोषणा OMAP_IH2_MIR		(OMAP_IH2_BASE + 0x04)
#घोषणा OMAP_IH2_SIR_IRQ	(OMAP_IH2_BASE + 0x10)
#घोषणा OMAP_IH2_SIR_FIQ	(OMAP_IH2_BASE + 0x14)
#घोषणा OMAP_IH2_CONTROL	(OMAP_IH2_BASE + 0x18)
#घोषणा OMAP_IH2_ILR0		(OMAP_IH2_BASE + 0x1c)
#घोषणा OMAP_IH2_ISR		(OMAP_IH2_BASE + 0x9c)

#घोषणा IRQ_ITR_REG_OFFSET	0x00
#घोषणा IRQ_MIR_REG_OFFSET	0x04
#घोषणा IRQ_SIR_IRQ_REG_OFFSET	0x10
#घोषणा IRQ_SIR_FIQ_REG_OFFSET	0x14
#घोषणा IRQ_CONTROL_REG_OFFSET	0x18
#घोषणा IRQ_ISR_REG_OFFSET	0x9c
#घोषणा IRQ_ILR0_REG_OFFSET	0x1c
#घोषणा IRQ_GMR_REG_OFFSET	0xa0

#पूर्ण_अगर

/*
 * ----------------------------------------------------------------------------
 * System control रेजिस्टरs
 * ----------------------------------------------------------------------------
 */
#घोषणा MOD_CONF_CTRL_0		0xfffe1080
#घोषणा MOD_CONF_CTRL_1		0xfffe1110

/*
 * ----------------------------------------------------------------------------
 * Pin multiplexing रेजिस्टरs
 * ----------------------------------------------------------------------------
 */
#घोषणा FUNC_MUX_CTRL_0		0xfffe1000
#घोषणा FUNC_MUX_CTRL_1		0xfffe1004
#घोषणा FUNC_MUX_CTRL_2		0xfffe1008
#घोषणा COMP_MODE_CTRL_0	0xfffe100c
#घोषणा FUNC_MUX_CTRL_3		0xfffe1010
#घोषणा FUNC_MUX_CTRL_4		0xfffe1014
#घोषणा FUNC_MUX_CTRL_5		0xfffe1018
#घोषणा FUNC_MUX_CTRL_6		0xfffe101C
#घोषणा FUNC_MUX_CTRL_7		0xfffe1020
#घोषणा FUNC_MUX_CTRL_8		0xfffe1024
#घोषणा FUNC_MUX_CTRL_9		0xfffe1028
#घोषणा FUNC_MUX_CTRL_A		0xfffe102C
#घोषणा FUNC_MUX_CTRL_B		0xfffe1030
#घोषणा FUNC_MUX_CTRL_C		0xfffe1034
#घोषणा FUNC_MUX_CTRL_D		0xfffe1038
#घोषणा PULL_DWN_CTRL_0		0xfffe1040
#घोषणा PULL_DWN_CTRL_1		0xfffe1044
#घोषणा PULL_DWN_CTRL_2		0xfffe1048
#घोषणा PULL_DWN_CTRL_3		0xfffe104c
#घोषणा PULL_DWN_CTRL_4		0xfffe10ac

/* OMAP-1610 specअगरic multiplexing रेजिस्टरs */
#घोषणा FUNC_MUX_CTRL_E		0xfffe1090
#घोषणा FUNC_MUX_CTRL_F		0xfffe1094
#घोषणा FUNC_MUX_CTRL_10	0xfffe1098
#घोषणा FUNC_MUX_CTRL_11	0xfffe109c
#घोषणा FUNC_MUX_CTRL_12	0xfffe10a0
#घोषणा PU_PD_SEL_0		0xfffe10b4
#घोषणा PU_PD_SEL_1		0xfffe10b8
#घोषणा PU_PD_SEL_2		0xfffe10bc
#घोषणा PU_PD_SEL_3		0xfffe10c0
#घोषणा PU_PD_SEL_4		0xfffe10c4

/* Timer32K क्रम 1610 and 1710*/
#घोषणा OMAP_TIMER32K_BASE	0xFFFBC400

/*
 * ---------------------------------------------------------------------------
 * TIPB bus पूर्णांकerface
 * ---------------------------------------------------------------------------
 */
#घोषणा TIPB_PUBLIC_CNTL_BASE		0xfffed300
#घोषणा MPU_PUBLIC_TIPB_CNTL		(TIPB_PUBLIC_CNTL_BASE + 0x8)
#घोषणा TIPB_PRIVATE_CNTL_BASE		0xfffeca00
#घोषणा MPU_PRIVATE_TIPB_CNTL		(TIPB_PRIVATE_CNTL_BASE + 0x8)

/*
 * ----------------------------------------------------------------------------
 * MPUI पूर्णांकerface
 * ----------------------------------------------------------------------------
 */
#घोषणा MPUI_BASE			(0xfffec900)
#घोषणा MPUI_CTRL			(MPUI_BASE + 0x0)
#घोषणा MPUI_DEBUG_ADDR			(MPUI_BASE + 0x4)
#घोषणा MPUI_DEBUG_DATA			(MPUI_BASE + 0x8)
#घोषणा MPUI_DEBUG_FLAG			(MPUI_BASE + 0xc)
#घोषणा MPUI_STATUS_REG			(MPUI_BASE + 0x10)
#घोषणा MPUI_DSP_STATUS			(MPUI_BASE + 0x14)
#घोषणा MPUI_DSP_BOOT_CONFIG		(MPUI_BASE + 0x18)
#घोषणा MPUI_DSP_API_CONFIG		(MPUI_BASE + 0x1c)

/*
 * ----------------------------------------------------------------------------
 * LED Pulse Generator
 * ----------------------------------------------------------------------------
 */
#घोषणा OMAP_LPG1_BASE			0xfffbd000
#घोषणा OMAP_LPG2_BASE			0xfffbd800
#घोषणा OMAP_LPG1_LCR			(OMAP_LPG1_BASE + 0x00)
#घोषणा OMAP_LPG1_PMR			(OMAP_LPG1_BASE + 0x04)
#घोषणा OMAP_LPG2_LCR			(OMAP_LPG2_BASE + 0x00)
#घोषणा OMAP_LPG2_PMR			(OMAP_LPG2_BASE + 0x04)

/*
 * ----------------------------------------------------------------------------
 * Pulse-Width Light
 * ----------------------------------------------------------------------------
 */
#घोषणा OMAP_PWL_BASE			0xfffb5800
#घोषणा OMAP_PWL_ENABLE			(OMAP_PWL_BASE + 0x00)
#घोषणा OMAP_PWL_CLK_ENABLE		(OMAP_PWL_BASE + 0x04)

/*
 * ---------------------------------------------------------------------------
 * Processor specअगरic defines
 * ---------------------------------------------------------------------------
 */

#समावेश "omap7xx.h"
#समावेश "omap1510.h"
#समावेश "omap16xx.h"

#पूर्ण_अगर	/* __ASM_ARCH_OMAP_HARDWARE_H */
