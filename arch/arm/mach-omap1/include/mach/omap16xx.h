<शैली गुरु>
/*
 * Hardware definitions क्रम TI OMAP1610/5912/1710 processors.
 *
 * Cleanup क्रम Linux-2.6 by Dirk Behme <dirk.behme@de.bosch.com>
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
 * You should have received a copy of the  GNU General Public License aदीर्घ
 * with this program; अगर not, ग_लिखो  to the Free Software Foundation, Inc.,
 * 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#अगर_अघोषित __ASM_ARCH_OMAP16XX_H
#घोषणा __ASM_ARCH_OMAP16XX_H

/*
 * ----------------------------------------------------------------------------
 * Base addresses
 * ----------------------------------------------------------------------------
 */

/* Syntax: XX_BASE = Virtual base address, XX_START = Physical base address */

#घोषणा OMAP16XX_DSP_BASE	0xE0000000
#घोषणा OMAP16XX_DSP_SIZE	0x28000
#घोषणा OMAP16XX_DSP_START	0xE0000000

#घोषणा OMAP16XX_DSPREG_BASE	0xE1000000
#घोषणा OMAP16XX_DSPREG_SIZE	SZ_128K
#घोषणा OMAP16XX_DSPREG_START	0xE1000000

#घोषणा OMAP16XX_SEC_BASE	0xFFFE4000
#घोषणा OMAP16XX_SEC_DES	(OMAP16XX_SEC_BASE + 0x0000)
#घोषणा OMAP16XX_SEC_SHA1MD5	(OMAP16XX_SEC_BASE + 0x0800)
#घोषणा OMAP16XX_SEC_RNG	(OMAP16XX_SEC_BASE + 0x1000)

/*
 * ---------------------------------------------------------------------------
 * Interrupts
 * ---------------------------------------------------------------------------
 */
#घोषणा OMAP_IH2_0_BASE		(0xfffe0000)
#घोषणा OMAP_IH2_1_BASE		(0xfffe0100)
#घोषणा OMAP_IH2_2_BASE		(0xfffe0200)
#घोषणा OMAP_IH2_3_BASE		(0xfffe0300)

#घोषणा OMAP_IH2_0_ITR		(OMAP_IH2_0_BASE + 0x00)
#घोषणा OMAP_IH2_0_MIR		(OMAP_IH2_0_BASE + 0x04)
#घोषणा OMAP_IH2_0_SIR_IRQ	(OMAP_IH2_0_BASE + 0x10)
#घोषणा OMAP_IH2_0_SIR_FIQ	(OMAP_IH2_0_BASE + 0x14)
#घोषणा OMAP_IH2_0_CONTROL	(OMAP_IH2_0_BASE + 0x18)
#घोषणा OMAP_IH2_0_ILR0		(OMAP_IH2_0_BASE + 0x1c)
#घोषणा OMAP_IH2_0_ISR		(OMAP_IH2_0_BASE + 0x9c)

#घोषणा OMAP_IH2_1_ITR		(OMAP_IH2_1_BASE + 0x00)
#घोषणा OMAP_IH2_1_MIR		(OMAP_IH2_1_BASE + 0x04)
#घोषणा OMAP_IH2_1_SIR_IRQ	(OMAP_IH2_1_BASE + 0x10)
#घोषणा OMAP_IH2_1_SIR_FIQ	(OMAP_IH2_1_BASE + 0x14)
#घोषणा OMAP_IH2_1_CONTROL	(OMAP_IH2_1_BASE + 0x18)
#घोषणा OMAP_IH2_1_ILR1		(OMAP_IH2_1_BASE + 0x1c)
#घोषणा OMAP_IH2_1_ISR		(OMAP_IH2_1_BASE + 0x9c)

#घोषणा OMAP_IH2_2_ITR		(OMAP_IH2_2_BASE + 0x00)
#घोषणा OMAP_IH2_2_MIR		(OMAP_IH2_2_BASE + 0x04)
#घोषणा OMAP_IH2_2_SIR_IRQ	(OMAP_IH2_2_BASE + 0x10)
#घोषणा OMAP_IH2_2_SIR_FIQ	(OMAP_IH2_2_BASE + 0x14)
#घोषणा OMAP_IH2_2_CONTROL	(OMAP_IH2_2_BASE + 0x18)
#घोषणा OMAP_IH2_2_ILR2		(OMAP_IH2_2_BASE + 0x1c)
#घोषणा OMAP_IH2_2_ISR		(OMAP_IH2_2_BASE + 0x9c)

#घोषणा OMAP_IH2_3_ITR		(OMAP_IH2_3_BASE + 0x00)
#घोषणा OMAP_IH2_3_MIR		(OMAP_IH2_3_BASE + 0x04)
#घोषणा OMAP_IH2_3_SIR_IRQ	(OMAP_IH2_3_BASE + 0x10)
#घोषणा OMAP_IH2_3_SIR_FIQ	(OMAP_IH2_3_BASE + 0x14)
#घोषणा OMAP_IH2_3_CONTROL	(OMAP_IH2_3_BASE + 0x18)
#घोषणा OMAP_IH2_3_ILR3		(OMAP_IH2_3_BASE + 0x1c)
#घोषणा OMAP_IH2_3_ISR		(OMAP_IH2_3_BASE + 0x9c)

/*
 * ----------------------------------------------------------------------------
 * Clocks
 * ----------------------------------------------------------------------------
 */
#घोषणा OMAP16XX_ARM_IDLECT3	(CLKGEN_REG_BASE + 0x24)

/*
 * ----------------------------------------------------------------------------
 * Pin configuration रेजिस्टरs
 * ----------------------------------------------------------------------------
 */
#घोषणा OMAP16XX_CONF_VOLTAGE_VDDSHV6	(1 << 8)
#घोषणा OMAP16XX_CONF_VOLTAGE_VDDSHV7	(1 << 9)
#घोषणा OMAP16XX_CONF_VOLTAGE_VDDSHV8	(1 << 10)
#घोषणा OMAP16XX_CONF_VOLTAGE_VDDSHV9	(1 << 11)
#घोषणा OMAP16XX_SUBLVDS_CONF_VALID	(1 << 13)

/*
 * ----------------------------------------------------------------------------
 * System control रेजिस्टरs
 * ----------------------------------------------------------------------------
 */
#घोषणा OMAP1610_RESET_CONTROL  0xfffe1140

/*
 * ---------------------------------------------------------------------------
 * TIPB bus पूर्णांकerface
 * ---------------------------------------------------------------------------
 */
#घोषणा TIPB_SWITCH_BASE		 (0xfffbc800)
#घोषणा OMAP16XX_MMCSD2_SSW_MPU_CONF	(TIPB_SWITCH_BASE + 0x160)

/* UART3 Registers Mapping through MPU bus */
#घोषणा UART3_RHR               (OMAP1_UART3_BASE + 0)
#घोषणा UART3_THR               (OMAP1_UART3_BASE + 0)
#घोषणा UART3_DLL               (OMAP1_UART3_BASE + 0)
#घोषणा UART3_IER               (OMAP1_UART3_BASE + 4)
#घोषणा UART3_DLH               (OMAP1_UART3_BASE + 4)
#घोषणा UART3_IIR               (OMAP1_UART3_BASE + 8)
#घोषणा UART3_FCR               (OMAP1_UART3_BASE + 8)
#घोषणा UART3_EFR               (OMAP1_UART3_BASE + 8)
#घोषणा UART3_LCR               (OMAP1_UART3_BASE + 0x0C)
#घोषणा UART3_MCR               (OMAP1_UART3_BASE + 0x10)
#घोषणा UART3_XON1_ADDR1        (OMAP1_UART3_BASE + 0x10)
#घोषणा UART3_XON2_ADDR2        (OMAP1_UART3_BASE + 0x14)
#घोषणा UART3_LSR               (OMAP1_UART3_BASE + 0x14)
#घोषणा UART3_TCR               (OMAP1_UART3_BASE + 0x18)
#घोषणा UART3_MSR               (OMAP1_UART3_BASE + 0x18)
#घोषणा UART3_XOFF1             (OMAP1_UART3_BASE + 0x18)
#घोषणा UART3_XOFF2             (OMAP1_UART3_BASE + 0x1C)
#घोषणा UART3_SPR               (OMAP1_UART3_BASE + 0x1C)
#घोषणा UART3_TLR               (OMAP1_UART3_BASE + 0x1C)
#घोषणा UART3_MDR1              (OMAP1_UART3_BASE + 0x20)
#घोषणा UART3_MDR2              (OMAP1_UART3_BASE + 0x24)
#घोषणा UART3_SFLSR             (OMAP1_UART3_BASE + 0x28)
#घोषणा UART3_TXFLL             (OMAP1_UART3_BASE + 0x28)
#घोषणा UART3_RESUME            (OMAP1_UART3_BASE + 0x2C)
#घोषणा UART3_TXFLH             (OMAP1_UART3_BASE + 0x2C)
#घोषणा UART3_SFREGL            (OMAP1_UART3_BASE + 0x30)
#घोषणा UART3_RXFLL             (OMAP1_UART3_BASE + 0x30)
#घोषणा UART3_SFREGH            (OMAP1_UART3_BASE + 0x34)
#घोषणा UART3_RXFLH             (OMAP1_UART3_BASE + 0x34)
#घोषणा UART3_BLR               (OMAP1_UART3_BASE + 0x38)
#घोषणा UART3_ACREG             (OMAP1_UART3_BASE + 0x3C)
#घोषणा UART3_DIV16             (OMAP1_UART3_BASE + 0x3C)
#घोषणा UART3_SCR               (OMAP1_UART3_BASE + 0x40)
#घोषणा UART3_SSR               (OMAP1_UART3_BASE + 0x44)
#घोषणा UART3_EBLR              (OMAP1_UART3_BASE + 0x48)
#घोषणा UART3_OSC_12M_SEL       (OMAP1_UART3_BASE + 0x4C)
#घोषणा UART3_MVR               (OMAP1_UART3_BASE + 0x50)

/*
 * ---------------------------------------------------------------------------
 * Watchकरोg समयr
 * ---------------------------------------------------------------------------
 */

/* 32-bit Watchकरोg समयr in OMAP 16XX */
#घोषणा OMAP_16XX_WATCHDOG_BASE        (0xfffeb000)
#घोषणा OMAP_16XX_WIDR         (OMAP_16XX_WATCHDOG_BASE + 0x00)
#घोषणा OMAP_16XX_WD_SYSCONFIG (OMAP_16XX_WATCHDOG_BASE + 0x10)
#घोषणा OMAP_16XX_WD_SYSSTATUS (OMAP_16XX_WATCHDOG_BASE + 0x14)
#घोषणा OMAP_16XX_WCLR         (OMAP_16XX_WATCHDOG_BASE + 0x24)
#घोषणा OMAP_16XX_WCRR         (OMAP_16XX_WATCHDOG_BASE + 0x28)
#घोषणा OMAP_16XX_WLDR         (OMAP_16XX_WATCHDOG_BASE + 0x2c)
#घोषणा OMAP_16XX_WTGR         (OMAP_16XX_WATCHDOG_BASE + 0x30)
#घोषणा OMAP_16XX_WWPS         (OMAP_16XX_WATCHDOG_BASE + 0x34)
#घोषणा OMAP_16XX_WSPR         (OMAP_16XX_WATCHDOG_BASE + 0x48)

#घोषणा WCLR_PRE_SHIFT         5
#घोषणा WCLR_PTV_SHIFT         2

#घोषणा WWPS_W_PEND_WSPR       (1 << 4)
#घोषणा WWPS_W_PEND_WTGR       (1 << 3)
#घोषणा WWPS_W_PEND_WLDR       (1 << 2)
#घोषणा WWPS_W_PEND_WCRR       (1 << 1)
#घोषणा WWPS_W_PEND_WCLR       (1 << 0)

#घोषणा WSPR_ENABLE_0          (0x0000bbbb)
#घोषणा WSPR_ENABLE_1          (0x00004444)
#घोषणा WSPR_DISABLE_0         (0x0000aaaa)
#घोषणा WSPR_DISABLE_1         (0x00005555)

#घोषणा OMAP16XX_DSP_MMU_BASE	(0xfffed200)
#घोषणा OMAP16XX_MAILBOX_BASE	(0xfffcf000)

#पूर्ण_अगर /*  __ASM_ARCH_OMAP16XX_H */

