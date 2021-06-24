<शैली गुरु>
/*
 * Copyright 2001, 2007-2008 MontaVista Software Inc.
 * Author: MontaVista Software, Inc. <source@mvista.com>
 *
 * Copyright (C) 2007 Ralf Baechle (ralf@linux-mips.org)
 *
 *  This program is मुक्त software; you can redistribute	 it and/or modअगरy it
 *  under  the terms of	 the GNU General  Public License as published by the
 *  Free Software Foundation;  either version 2 of the	License, or (at your
 *  option) any later version.
 *
 *  THIS  SOFTWARE  IS PROVIDED	  ``AS	IS'' AND   ANY	EXPRESS OR IMPLIED
 *  WARRANTIES,	  INCLUDING, BUT NOT  LIMITED  TO, THE IMPLIED WARRANTIES OF
 *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN
 *  NO	EVENT  SHALL   THE AUTHOR  BE	 LIABLE FOR ANY	  सूचीECT, INसूचीECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 *  NOT LIMITED	  TO, PROCUREMENT OF  SUBSTITUTE GOODS	OR SERVICES; LOSS OF
 *  USE, DATA,	OR PROFITS; OR	BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 *  ANY THEORY OF LIABILITY, WHETHER IN	 CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 *  THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *  You should have received a copy of the  GNU General Public License aदीर्घ
 *  with this program; अगर not, ग_लिखो  to the Free Software Foundation, Inc.,
 *  675 Mass Ave, Cambridge, MA 02139, USA.
 */

#समावेश <linux/export.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/slab.h>
#समावेश <linux/syscore_ops.h>

#समावेश <यंत्र/irq_cpu.h>
#समावेश <यंत्र/mach-au1x00/au1000.h>
#समावेश <यंत्र/mach-au1x00/gpio-au1300.h>

/* Interrupt Controller रेजिस्टर offsets */
#घोषणा IC_CFG0RD	0x40
#घोषणा IC_CFG0SET	0x40
#घोषणा IC_CFG0CLR	0x44
#घोषणा IC_CFG1RD	0x48
#घोषणा IC_CFG1SET	0x48
#घोषणा IC_CFG1CLR	0x4C
#घोषणा IC_CFG2RD	0x50
#घोषणा IC_CFG2SET	0x50
#घोषणा IC_CFG2CLR	0x54
#घोषणा IC_REQ0INT	0x54
#घोषणा IC_SRCRD	0x58
#घोषणा IC_SRCSET	0x58
#घोषणा IC_SRCCLR	0x5C
#घोषणा IC_REQ1INT	0x5C
#घोषणा IC_ASSIGNRD	0x60
#घोषणा IC_ASSIGNSET	0x60
#घोषणा IC_ASSIGNCLR	0x64
#घोषणा IC_WAKERD	0x68
#घोषणा IC_WAKESET	0x68
#घोषणा IC_WAKECLR	0x6C
#घोषणा IC_MASKRD	0x70
#घोषणा IC_MASKSET	0x70
#घोषणा IC_MASKCLR	0x74
#घोषणा IC_RISINGRD	0x78
#घोषणा IC_RISINGCLR	0x78
#घोषणा IC_FALLINGRD	0x7C
#घोषणा IC_FALLINGCLR	0x7C
#घोषणा IC_TESTBIT	0x80

/* per-processor fixed function irqs */
काष्ठा alchemy_irqmap अणु
	पूर्णांक irq;	/* linux IRQ number */
	पूर्णांक type;	/* IRQ_TYPE_ */
	पूर्णांक prio;	/* irq priority, 0 highest, 3 lowest */
	पूर्णांक पूर्णांकernal;	/* GPIC: पूर्णांकernal source (no ext. pin)? */
पूर्ण;

अटल पूर्णांक au1x_ic_settype(काष्ठा irq_data *d, अचिन्हित पूर्णांक type);
अटल पूर्णांक au1300_gpic_settype(काष्ठा irq_data *d, अचिन्हित पूर्णांक type);


/* NOTE on पूर्णांकerrupt priorities: The original ग_लिखोrs of this code said:
 *
 * Because of the tight timing of SETUP token to reply transactions,
 * the USB devices-side packet complete पूर्णांकerrupt (USB_DEV_REQ_INT)
 * needs the highest priority.
 */
काष्ठा alchemy_irqmap au1000_irqmap[] __initdata = अणु
	अणु AU1000_UART0_INT,	  IRQ_TYPE_LEVEL_HIGH,	1, 0 पूर्ण,
	अणु AU1000_UART1_INT,	  IRQ_TYPE_LEVEL_HIGH,	1, 0 पूर्ण,
	अणु AU1000_UART2_INT,	  IRQ_TYPE_LEVEL_HIGH,	1, 0 पूर्ण,
	अणु AU1000_UART3_INT,	  IRQ_TYPE_LEVEL_HIGH,	1, 0 पूर्ण,
	अणु AU1000_SSI0_INT,	  IRQ_TYPE_LEVEL_HIGH,	1, 0 पूर्ण,
	अणु AU1000_SSI1_INT,	  IRQ_TYPE_LEVEL_HIGH,	1, 0 पूर्ण,
	अणु AU1000_DMA_INT_BASE,	  IRQ_TYPE_LEVEL_HIGH,	1, 0 पूर्ण,
	अणु AU1000_DMA_INT_BASE+1,  IRQ_TYPE_LEVEL_HIGH,	1, 0 पूर्ण,
	अणु AU1000_DMA_INT_BASE+2,  IRQ_TYPE_LEVEL_HIGH,	1, 0 पूर्ण,
	अणु AU1000_DMA_INT_BASE+3,  IRQ_TYPE_LEVEL_HIGH,	1, 0 पूर्ण,
	अणु AU1000_DMA_INT_BASE+4,  IRQ_TYPE_LEVEL_HIGH,	1, 0 पूर्ण,
	अणु AU1000_DMA_INT_BASE+5,  IRQ_TYPE_LEVEL_HIGH,	1, 0 पूर्ण,
	अणु AU1000_DMA_INT_BASE+6,  IRQ_TYPE_LEVEL_HIGH,	1, 0 पूर्ण,
	अणु AU1000_DMA_INT_BASE+7,  IRQ_TYPE_LEVEL_HIGH,	1, 0 पूर्ण,
	अणु AU1000_TOY_INT,	  IRQ_TYPE_EDGE_RISING, 1, 0 पूर्ण,
	अणु AU1000_TOY_MATCH0_INT,  IRQ_TYPE_EDGE_RISING, 1, 0 पूर्ण,
	अणु AU1000_TOY_MATCH1_INT,  IRQ_TYPE_EDGE_RISING, 1, 0 पूर्ण,
	अणु AU1000_TOY_MATCH2_INT,  IRQ_TYPE_EDGE_RISING, 1, 0 पूर्ण,
	अणु AU1000_RTC_INT,	  IRQ_TYPE_EDGE_RISING, 1, 0 पूर्ण,
	अणु AU1000_RTC_MATCH0_INT,  IRQ_TYPE_EDGE_RISING, 1, 0 पूर्ण,
	अणु AU1000_RTC_MATCH1_INT,  IRQ_TYPE_EDGE_RISING, 1, 0 पूर्ण,
	अणु AU1000_RTC_MATCH2_INT,  IRQ_TYPE_EDGE_RISING, 0, 0 पूर्ण,
	अणु AU1000_IRDA_TX_INT,	  IRQ_TYPE_LEVEL_HIGH,	1, 0 पूर्ण,
	अणु AU1000_IRDA_RX_INT,	  IRQ_TYPE_LEVEL_HIGH,	1, 0 पूर्ण,
	अणु AU1000_USB_DEV_REQ_INT, IRQ_TYPE_LEVEL_HIGH,	0, 0 पूर्ण,
	अणु AU1000_USB_DEV_SUS_INT, IRQ_TYPE_EDGE_RISING, 1, 0 पूर्ण,
	अणु AU1000_USB_HOST_INT,	  IRQ_TYPE_LEVEL_LOW,	1, 0 पूर्ण,
	अणु AU1000_ACSYNC_INT,	  IRQ_TYPE_EDGE_RISING, 1, 0 पूर्ण,
	अणु AU1000_MAC0_DMA_INT,	  IRQ_TYPE_LEVEL_HIGH,	1, 0 पूर्ण,
	अणु AU1000_MAC1_DMA_INT,	  IRQ_TYPE_LEVEL_HIGH,	1, 0 पूर्ण,
	अणु AU1000_AC97C_INT,	  IRQ_TYPE_EDGE_RISING, 1, 0 पूर्ण,
	अणु -1, पूर्ण,
पूर्ण;

काष्ठा alchemy_irqmap au1500_irqmap[] __initdata = अणु
	अणु AU1500_UART0_INT,	  IRQ_TYPE_LEVEL_HIGH,	1, 0 पूर्ण,
	अणु AU1500_PCI_INTA,	  IRQ_TYPE_LEVEL_LOW,	1, 0 पूर्ण,
	अणु AU1500_PCI_INTB,	  IRQ_TYPE_LEVEL_LOW,	1, 0 पूर्ण,
	अणु AU1500_UART3_INT,	  IRQ_TYPE_LEVEL_HIGH,	1, 0 पूर्ण,
	अणु AU1500_PCI_INTC,	  IRQ_TYPE_LEVEL_LOW,	1, 0 पूर्ण,
	अणु AU1500_PCI_INTD,	  IRQ_TYPE_LEVEL_LOW,	1, 0 पूर्ण,
	अणु AU1500_DMA_INT_BASE,	  IRQ_TYPE_LEVEL_HIGH,	1, 0 पूर्ण,
	अणु AU1500_DMA_INT_BASE+1,  IRQ_TYPE_LEVEL_HIGH,	1, 0 पूर्ण,
	अणु AU1500_DMA_INT_BASE+2,  IRQ_TYPE_LEVEL_HIGH,	1, 0 पूर्ण,
	अणु AU1500_DMA_INT_BASE+3,  IRQ_TYPE_LEVEL_HIGH,	1, 0 पूर्ण,
	अणु AU1500_DMA_INT_BASE+4,  IRQ_TYPE_LEVEL_HIGH,	1, 0 पूर्ण,
	अणु AU1500_DMA_INT_BASE+5,  IRQ_TYPE_LEVEL_HIGH,	1, 0 पूर्ण,
	अणु AU1500_DMA_INT_BASE+6,  IRQ_TYPE_LEVEL_HIGH,	1, 0 पूर्ण,
	अणु AU1500_DMA_INT_BASE+7,  IRQ_TYPE_LEVEL_HIGH,	1, 0 पूर्ण,
	अणु AU1500_TOY_INT,	  IRQ_TYPE_EDGE_RISING, 1, 0 पूर्ण,
	अणु AU1500_TOY_MATCH0_INT,  IRQ_TYPE_EDGE_RISING, 1, 0 पूर्ण,
	अणु AU1500_TOY_MATCH1_INT,  IRQ_TYPE_EDGE_RISING, 1, 0 पूर्ण,
	अणु AU1500_TOY_MATCH2_INT,  IRQ_TYPE_EDGE_RISING, 1, 0 पूर्ण,
	अणु AU1500_RTC_INT,	  IRQ_TYPE_EDGE_RISING, 1, 0 पूर्ण,
	अणु AU1500_RTC_MATCH0_INT,  IRQ_TYPE_EDGE_RISING, 1, 0 पूर्ण,
	अणु AU1500_RTC_MATCH1_INT,  IRQ_TYPE_EDGE_RISING, 1, 0 पूर्ण,
	अणु AU1500_RTC_MATCH2_INT,  IRQ_TYPE_EDGE_RISING, 0, 0 पूर्ण,
	अणु AU1500_USB_DEV_REQ_INT, IRQ_TYPE_LEVEL_HIGH,	0, 0 पूर्ण,
	अणु AU1500_USB_DEV_SUS_INT, IRQ_TYPE_EDGE_RISING, 1, 0 पूर्ण,
	अणु AU1500_USB_HOST_INT,	  IRQ_TYPE_LEVEL_LOW,	1, 0 पूर्ण,
	अणु AU1500_ACSYNC_INT,	  IRQ_TYPE_EDGE_RISING, 1, 0 पूर्ण,
	अणु AU1500_MAC0_DMA_INT,	  IRQ_TYPE_LEVEL_HIGH,	1, 0 पूर्ण,
	अणु AU1500_MAC1_DMA_INT,	  IRQ_TYPE_LEVEL_HIGH,	1, 0 पूर्ण,
	अणु AU1500_AC97C_INT,	  IRQ_TYPE_EDGE_RISING, 1, 0 पूर्ण,
	अणु -1, पूर्ण,
पूर्ण;

काष्ठा alchemy_irqmap au1100_irqmap[] __initdata = अणु
	अणु AU1100_UART0_INT,	  IRQ_TYPE_LEVEL_HIGH,	1, 0 पूर्ण,
	अणु AU1100_UART1_INT,	  IRQ_TYPE_LEVEL_HIGH,	1, 0 पूर्ण,
	अणु AU1100_SD_INT,	  IRQ_TYPE_LEVEL_HIGH,	1, 0 पूर्ण,
	अणु AU1100_UART3_INT,	  IRQ_TYPE_LEVEL_HIGH,	1, 0 पूर्ण,
	अणु AU1100_SSI0_INT,	  IRQ_TYPE_LEVEL_HIGH,	1, 0 पूर्ण,
	अणु AU1100_SSI1_INT,	  IRQ_TYPE_LEVEL_HIGH,	1, 0 पूर्ण,
	अणु AU1100_DMA_INT_BASE,	  IRQ_TYPE_LEVEL_HIGH,	1, 0 पूर्ण,
	अणु AU1100_DMA_INT_BASE+1,  IRQ_TYPE_LEVEL_HIGH,	1, 0 पूर्ण,
	अणु AU1100_DMA_INT_BASE+2,  IRQ_TYPE_LEVEL_HIGH,	1, 0 पूर्ण,
	अणु AU1100_DMA_INT_BASE+3,  IRQ_TYPE_LEVEL_HIGH,	1, 0 पूर्ण,
	अणु AU1100_DMA_INT_BASE+4,  IRQ_TYPE_LEVEL_HIGH,	1, 0 पूर्ण,
	अणु AU1100_DMA_INT_BASE+5,  IRQ_TYPE_LEVEL_HIGH,	1, 0 पूर्ण,
	अणु AU1100_DMA_INT_BASE+6,  IRQ_TYPE_LEVEL_HIGH,	1, 0 पूर्ण,
	अणु AU1100_DMA_INT_BASE+7,  IRQ_TYPE_LEVEL_HIGH,	1, 0 पूर्ण,
	अणु AU1100_TOY_INT,	  IRQ_TYPE_EDGE_RISING, 1, 0 पूर्ण,
	अणु AU1100_TOY_MATCH0_INT,  IRQ_TYPE_EDGE_RISING, 1, 0 पूर्ण,
	अणु AU1100_TOY_MATCH1_INT,  IRQ_TYPE_EDGE_RISING, 1, 0 पूर्ण,
	अणु AU1100_TOY_MATCH2_INT,  IRQ_TYPE_EDGE_RISING, 1, 0 पूर्ण,
	अणु AU1100_RTC_INT,	  IRQ_TYPE_EDGE_RISING, 1, 0 पूर्ण,
	अणु AU1100_RTC_MATCH0_INT,  IRQ_TYPE_EDGE_RISING, 1, 0 पूर्ण,
	अणु AU1100_RTC_MATCH1_INT,  IRQ_TYPE_EDGE_RISING, 1, 0 पूर्ण,
	अणु AU1100_RTC_MATCH2_INT,  IRQ_TYPE_EDGE_RISING, 0, 0 पूर्ण,
	अणु AU1100_IRDA_TX_INT,	  IRQ_TYPE_LEVEL_HIGH,	1, 0 पूर्ण,
	अणु AU1100_IRDA_RX_INT,	  IRQ_TYPE_LEVEL_HIGH,	1, 0 पूर्ण,
	अणु AU1100_USB_DEV_REQ_INT, IRQ_TYPE_LEVEL_HIGH,	0, 0 पूर्ण,
	अणु AU1100_USB_DEV_SUS_INT, IRQ_TYPE_EDGE_RISING, 1, 0 पूर्ण,
	अणु AU1100_USB_HOST_INT,	  IRQ_TYPE_LEVEL_LOW,	1, 0 पूर्ण,
	अणु AU1100_ACSYNC_INT,	  IRQ_TYPE_EDGE_RISING, 1, 0 पूर्ण,
	अणु AU1100_MAC0_DMA_INT,	  IRQ_TYPE_LEVEL_HIGH,	1, 0 पूर्ण,
	अणु AU1100_LCD_INT,	  IRQ_TYPE_LEVEL_HIGH,	1, 0 पूर्ण,
	अणु AU1100_AC97C_INT,	  IRQ_TYPE_EDGE_RISING, 1, 0 पूर्ण,
	अणु -1, पूर्ण,
पूर्ण;

काष्ठा alchemy_irqmap au1550_irqmap[] __initdata = अणु
	अणु AU1550_UART0_INT,	  IRQ_TYPE_LEVEL_HIGH,	1, 0 पूर्ण,
	अणु AU1550_PCI_INTA,	  IRQ_TYPE_LEVEL_LOW,	1, 0 पूर्ण,
	अणु AU1550_PCI_INTB,	  IRQ_TYPE_LEVEL_LOW,	1, 0 पूर्ण,
	अणु AU1550_DDMA_INT,	  IRQ_TYPE_LEVEL_HIGH,	1, 0 पूर्ण,
	अणु AU1550_CRYPTO_INT,	  IRQ_TYPE_LEVEL_HIGH,	1, 0 पूर्ण,
	अणु AU1550_PCI_INTC,	  IRQ_TYPE_LEVEL_LOW,	1, 0 पूर्ण,
	अणु AU1550_PCI_INTD,	  IRQ_TYPE_LEVEL_LOW,	1, 0 पूर्ण,
	अणु AU1550_PCI_RST_INT,	  IRQ_TYPE_LEVEL_LOW,	1, 0 पूर्ण,
	अणु AU1550_UART1_INT,	  IRQ_TYPE_LEVEL_HIGH,	1, 0 पूर्ण,
	अणु AU1550_UART3_INT,	  IRQ_TYPE_LEVEL_HIGH,	1, 0 पूर्ण,
	अणु AU1550_PSC0_INT,	  IRQ_TYPE_LEVEL_HIGH,	1, 0 पूर्ण,
	अणु AU1550_PSC1_INT,	  IRQ_TYPE_LEVEL_HIGH,	1, 0 पूर्ण,
	अणु AU1550_PSC2_INT,	  IRQ_TYPE_LEVEL_HIGH,	1, 0 पूर्ण,
	अणु AU1550_PSC3_INT,	  IRQ_TYPE_LEVEL_HIGH,	1, 0 पूर्ण,
	अणु AU1550_TOY_INT,	  IRQ_TYPE_EDGE_RISING, 1, 0 पूर्ण,
	अणु AU1550_TOY_MATCH0_INT,  IRQ_TYPE_EDGE_RISING, 1, 0 पूर्ण,
	अणु AU1550_TOY_MATCH1_INT,  IRQ_TYPE_EDGE_RISING, 1, 0 पूर्ण,
	अणु AU1550_TOY_MATCH2_INT,  IRQ_TYPE_EDGE_RISING, 1, 0 पूर्ण,
	अणु AU1550_RTC_INT,	  IRQ_TYPE_EDGE_RISING, 1, 0 पूर्ण,
	अणु AU1550_RTC_MATCH0_INT,  IRQ_TYPE_EDGE_RISING, 1, 0 पूर्ण,
	अणु AU1550_RTC_MATCH1_INT,  IRQ_TYPE_EDGE_RISING, 1, 0 पूर्ण,
	अणु AU1550_RTC_MATCH2_INT,  IRQ_TYPE_EDGE_RISING, 0, 0 पूर्ण,
	अणु AU1550_न_अंकD_INT,	  IRQ_TYPE_EDGE_RISING, 1, 0 पूर्ण,
	अणु AU1550_USB_DEV_REQ_INT, IRQ_TYPE_LEVEL_HIGH,	0, 0 पूर्ण,
	अणु AU1550_USB_DEV_SUS_INT, IRQ_TYPE_EDGE_RISING, 1, 0 पूर्ण,
	अणु AU1550_USB_HOST_INT,	  IRQ_TYPE_LEVEL_LOW,	1, 0 पूर्ण,
	अणु AU1550_MAC0_DMA_INT,	  IRQ_TYPE_LEVEL_HIGH,	1, 0 पूर्ण,
	अणु AU1550_MAC1_DMA_INT,	  IRQ_TYPE_LEVEL_HIGH,	1, 0 पूर्ण,
	अणु -1, पूर्ण,
पूर्ण;

काष्ठा alchemy_irqmap au1200_irqmap[] __initdata = अणु
	अणु AU1200_UART0_INT,	  IRQ_TYPE_LEVEL_HIGH,	1, 0 पूर्ण,
	अणु AU1200_SWT_INT,	  IRQ_TYPE_EDGE_RISING, 1, 0 पूर्ण,
	अणु AU1200_SD_INT,	  IRQ_TYPE_LEVEL_HIGH,	1, 0 पूर्ण,
	अणु AU1200_DDMA_INT,	  IRQ_TYPE_LEVEL_HIGH,	1, 0 पूर्ण,
	अणु AU1200_MAE_BE_INT,	  IRQ_TYPE_LEVEL_HIGH,	1, 0 पूर्ण,
	अणु AU1200_UART1_INT,	  IRQ_TYPE_LEVEL_HIGH,	1, 0 पूर्ण,
	अणु AU1200_MAE_FE_INT,	  IRQ_TYPE_LEVEL_HIGH,	1, 0 पूर्ण,
	अणु AU1200_PSC0_INT,	  IRQ_TYPE_LEVEL_HIGH,	1, 0 पूर्ण,
	अणु AU1200_PSC1_INT,	  IRQ_TYPE_LEVEL_HIGH,	1, 0 पूर्ण,
	अणु AU1200_AES_INT,	  IRQ_TYPE_LEVEL_HIGH,	1, 0 पूर्ण,
	अणु AU1200_CAMERA_INT,	  IRQ_TYPE_LEVEL_HIGH,	1, 0 पूर्ण,
	अणु AU1200_TOY_INT,	  IRQ_TYPE_EDGE_RISING, 1, 0 पूर्ण,
	अणु AU1200_TOY_MATCH0_INT,  IRQ_TYPE_EDGE_RISING, 1, 0 पूर्ण,
	अणु AU1200_TOY_MATCH1_INT,  IRQ_TYPE_EDGE_RISING, 1, 0 पूर्ण,
	अणु AU1200_TOY_MATCH2_INT,  IRQ_TYPE_EDGE_RISING, 1, 0 पूर्ण,
	अणु AU1200_RTC_INT,	  IRQ_TYPE_EDGE_RISING, 1, 0 पूर्ण,
	अणु AU1200_RTC_MATCH0_INT,  IRQ_TYPE_EDGE_RISING, 1, 0 पूर्ण,
	अणु AU1200_RTC_MATCH1_INT,  IRQ_TYPE_EDGE_RISING, 1, 0 पूर्ण,
	अणु AU1200_RTC_MATCH2_INT,  IRQ_TYPE_EDGE_RISING, 0, 0 पूर्ण,
	अणु AU1200_न_अंकD_INT,	  IRQ_TYPE_EDGE_RISING, 1, 0 पूर्ण,
	अणु AU1200_USB_INT,	  IRQ_TYPE_LEVEL_HIGH,	1, 0 पूर्ण,
	अणु AU1200_LCD_INT,	  IRQ_TYPE_LEVEL_HIGH,	1, 0 पूर्ण,
	अणु AU1200_MAE_BOTH_INT,	  IRQ_TYPE_LEVEL_HIGH,	1, 0 पूर्ण,
	अणु -1, पूर्ण,
पूर्ण;

अटल काष्ठा alchemy_irqmap au1300_irqmap[] __initdata = अणु
	/* multअगरunction: gpio pin or device */
	अणु AU1300_UART1_INT,	 IRQ_TYPE_LEVEL_HIGH,	1, 0, पूर्ण,
	अणु AU1300_UART2_INT,	 IRQ_TYPE_LEVEL_HIGH,	1, 0, पूर्ण,
	अणु AU1300_UART3_INT,	 IRQ_TYPE_LEVEL_HIGH,	1, 0, पूर्ण,
	अणु AU1300_SD1_INT,	 IRQ_TYPE_LEVEL_HIGH,	1, 0, पूर्ण,
	अणु AU1300_SD2_INT,	 IRQ_TYPE_LEVEL_HIGH,	1, 0, पूर्ण,
	अणु AU1300_PSC0_INT,	 IRQ_TYPE_LEVEL_HIGH,	1, 0, पूर्ण,
	अणु AU1300_PSC1_INT,	 IRQ_TYPE_LEVEL_HIGH,	1, 0, पूर्ण,
	अणु AU1300_PSC2_INT,	 IRQ_TYPE_LEVEL_HIGH,	1, 0, पूर्ण,
	अणु AU1300_PSC3_INT,	 IRQ_TYPE_LEVEL_HIGH,	1, 0, पूर्ण,
	अणु AU1300_न_अंकD_INT,	 IRQ_TYPE_LEVEL_HIGH,	1, 0, पूर्ण,
	/* au1300 पूर्णांकernal */
	अणु AU1300_DDMA_INT,	 IRQ_TYPE_LEVEL_HIGH,	1, 1, पूर्ण,
	अणु AU1300_MMU_INT,	 IRQ_TYPE_LEVEL_HIGH,	1, 1, पूर्ण,
	अणु AU1300_MPU_INT,	 IRQ_TYPE_LEVEL_HIGH,	1, 1, पूर्ण,
	अणु AU1300_GPU_INT,	 IRQ_TYPE_LEVEL_HIGH,	1, 1, पूर्ण,
	अणु AU1300_UDMA_INT,	 IRQ_TYPE_LEVEL_HIGH,	1, 1, पूर्ण,
	अणु AU1300_TOY_INT,	 IRQ_TYPE_EDGE_RISING,	1, 1, पूर्ण,
	अणु AU1300_TOY_MATCH0_INT, IRQ_TYPE_EDGE_RISING,	1, 1, पूर्ण,
	अणु AU1300_TOY_MATCH1_INT, IRQ_TYPE_EDGE_RISING,	1, 1, पूर्ण,
	अणु AU1300_TOY_MATCH2_INT, IRQ_TYPE_EDGE_RISING,	1, 1, पूर्ण,
	अणु AU1300_RTC_INT,	 IRQ_TYPE_EDGE_RISING,	1, 1, पूर्ण,
	अणु AU1300_RTC_MATCH0_INT, IRQ_TYPE_EDGE_RISING,	1, 1, पूर्ण,
	अणु AU1300_RTC_MATCH1_INT, IRQ_TYPE_EDGE_RISING,	1, 1, पूर्ण,
	अणु AU1300_RTC_MATCH2_INT, IRQ_TYPE_EDGE_RISING,	0, 1, पूर्ण,
	अणु AU1300_UART0_INT,	 IRQ_TYPE_LEVEL_HIGH,	1, 1, पूर्ण,
	अणु AU1300_SD0_INT,	 IRQ_TYPE_LEVEL_HIGH,	1, 1, पूर्ण,
	अणु AU1300_USB_INT,	 IRQ_TYPE_LEVEL_HIGH,	1, 1, पूर्ण,
	अणु AU1300_LCD_INT,	 IRQ_TYPE_LEVEL_HIGH,	1, 1, पूर्ण,
	अणु AU1300_BSA_INT,	 IRQ_TYPE_LEVEL_HIGH,	1, 1, पूर्ण,
	अणु AU1300_MPE_INT,	 IRQ_TYPE_EDGE_RISING,	1, 1, पूर्ण,
	अणु AU1300_ITE_INT,	 IRQ_TYPE_LEVEL_HIGH,	1, 1, पूर्ण,
	अणु AU1300_AES_INT,	 IRQ_TYPE_LEVEL_HIGH,	1, 1, पूर्ण,
	अणु AU1300_CIM_INT,	 IRQ_TYPE_LEVEL_HIGH,	1, 1, पूर्ण,
	अणु -1, पूर्ण,	/* terminator */
पूर्ण;

/******************************************************************************/

अटल व्योम au1x_ic0_unmask(काष्ठा irq_data *d)
अणु
	अचिन्हित पूर्णांक bit = d->irq - AU1000_INTC0_INT_BASE;
	व्योम __iomem *base = (व्योम __iomem *)KSEG1ADDR(AU1000_IC0_PHYS_ADDR);

	__raw_ग_लिखोl(1 << bit, base + IC_MASKSET);
	__raw_ग_लिखोl(1 << bit, base + IC_WAKESET);
	wmb();
पूर्ण

अटल व्योम au1x_ic1_unmask(काष्ठा irq_data *d)
अणु
	अचिन्हित पूर्णांक bit = d->irq - AU1000_INTC1_INT_BASE;
	व्योम __iomem *base = (व्योम __iomem *)KSEG1ADDR(AU1000_IC1_PHYS_ADDR);

	__raw_ग_लिखोl(1 << bit, base + IC_MASKSET);
	__raw_ग_लिखोl(1 << bit, base + IC_WAKESET);
	wmb();
पूर्ण

अटल व्योम au1x_ic0_mask(काष्ठा irq_data *d)
अणु
	अचिन्हित पूर्णांक bit = d->irq - AU1000_INTC0_INT_BASE;
	व्योम __iomem *base = (व्योम __iomem *)KSEG1ADDR(AU1000_IC0_PHYS_ADDR);

	__raw_ग_लिखोl(1 << bit, base + IC_MASKCLR);
	__raw_ग_लिखोl(1 << bit, base + IC_WAKECLR);
	wmb();
पूर्ण

अटल व्योम au1x_ic1_mask(काष्ठा irq_data *d)
अणु
	अचिन्हित पूर्णांक bit = d->irq - AU1000_INTC1_INT_BASE;
	व्योम __iomem *base = (व्योम __iomem *)KSEG1ADDR(AU1000_IC1_PHYS_ADDR);

	__raw_ग_लिखोl(1 << bit, base + IC_MASKCLR);
	__raw_ग_लिखोl(1 << bit, base + IC_WAKECLR);
	wmb();
पूर्ण

अटल व्योम au1x_ic0_ack(काष्ठा irq_data *d)
अणु
	अचिन्हित पूर्णांक bit = d->irq - AU1000_INTC0_INT_BASE;
	व्योम __iomem *base = (व्योम __iomem *)KSEG1ADDR(AU1000_IC0_PHYS_ADDR);

	/*
	 * This may assume that we करोn't get पूर्णांकerrupts from
	 * both edges at once, or अगर we करो, that we करोn't care.
	 */
	__raw_ग_लिखोl(1 << bit, base + IC_FALLINGCLR);
	__raw_ग_लिखोl(1 << bit, base + IC_RISINGCLR);
	wmb();
पूर्ण

अटल व्योम au1x_ic1_ack(काष्ठा irq_data *d)
अणु
	अचिन्हित पूर्णांक bit = d->irq - AU1000_INTC1_INT_BASE;
	व्योम __iomem *base = (व्योम __iomem *)KSEG1ADDR(AU1000_IC1_PHYS_ADDR);

	/*
	 * This may assume that we करोn't get पूर्णांकerrupts from
	 * both edges at once, or अगर we करो, that we करोn't care.
	 */
	__raw_ग_लिखोl(1 << bit, base + IC_FALLINGCLR);
	__raw_ग_लिखोl(1 << bit, base + IC_RISINGCLR);
	wmb();
पूर्ण

अटल व्योम au1x_ic0_maskack(काष्ठा irq_data *d)
अणु
	अचिन्हित पूर्णांक bit = d->irq - AU1000_INTC0_INT_BASE;
	व्योम __iomem *base = (व्योम __iomem *)KSEG1ADDR(AU1000_IC0_PHYS_ADDR);

	__raw_ग_लिखोl(1 << bit, base + IC_WAKECLR);
	__raw_ग_लिखोl(1 << bit, base + IC_MASKCLR);
	__raw_ग_लिखोl(1 << bit, base + IC_RISINGCLR);
	__raw_ग_लिखोl(1 << bit, base + IC_FALLINGCLR);
	wmb();
पूर्ण

अटल व्योम au1x_ic1_maskack(काष्ठा irq_data *d)
अणु
	अचिन्हित पूर्णांक bit = d->irq - AU1000_INTC1_INT_BASE;
	व्योम __iomem *base = (व्योम __iomem *)KSEG1ADDR(AU1000_IC1_PHYS_ADDR);

	__raw_ग_लिखोl(1 << bit, base + IC_WAKECLR);
	__raw_ग_लिखोl(1 << bit, base + IC_MASKCLR);
	__raw_ग_लिखोl(1 << bit, base + IC_RISINGCLR);
	__raw_ग_लिखोl(1 << bit, base + IC_FALLINGCLR);
	wmb();
पूर्ण

अटल पूर्णांक au1x_ic1_setwake(काष्ठा irq_data *d, अचिन्हित पूर्णांक on)
अणु
	पूर्णांक bit = d->irq - AU1000_INTC1_INT_BASE;
	अचिन्हित दीर्घ wakemsk, flags;

	/* only GPIO 0-7 can act as wakeup source.  Fortunately these
	 * are wired up identically on all supported variants.
	 */
	अगर ((bit < 0) || (bit > 7))
		वापस -EINVAL;

	local_irq_save(flags);
	wakemsk = alchemy_rdsys(AU1000_SYS_WAKEMSK);
	अगर (on)
		wakemsk |= 1 << bit;
	अन्यथा
		wakemsk &= ~(1 << bit);
	alchemy_wrsys(wakemsk, AU1000_SYS_WAKEMSK);
	local_irq_restore(flags);

	वापस 0;
पूर्ण

/*
 * irq_chips क्रम both ICs; this way the mask handlers can be
 * as लघु as possible.
 */
अटल काष्ठा irq_chip au1x_ic0_chip = अणु
	.name		= "Alchemy-IC0",
	.irq_ack	= au1x_ic0_ack,
	.irq_mask	= au1x_ic0_mask,
	.irq_mask_ack	= au1x_ic0_maskack,
	.irq_unmask	= au1x_ic0_unmask,
	.irq_set_type	= au1x_ic_settype,
पूर्ण;

अटल काष्ठा irq_chip au1x_ic1_chip = अणु
	.name		= "Alchemy-IC1",
	.irq_ack	= au1x_ic1_ack,
	.irq_mask	= au1x_ic1_mask,
	.irq_mask_ack	= au1x_ic1_maskack,
	.irq_unmask	= au1x_ic1_unmask,
	.irq_set_type	= au1x_ic_settype,
	.irq_set_wake	= au1x_ic1_setwake,
पूर्ण;

अटल पूर्णांक au1x_ic_settype(काष्ठा irq_data *d, अचिन्हित पूर्णांक flow_type)
अणु
	काष्ठा irq_chip *chip;
	अचिन्हित पूर्णांक bit, irq = d->irq;
	irq_flow_handler_t handler = शून्य;
	अचिन्हित अक्षर *name = शून्य;
	व्योम __iomem *base;
	पूर्णांक ret;

	अगर (irq >= AU1000_INTC1_INT_BASE) अणु
		bit = irq - AU1000_INTC1_INT_BASE;
		chip = &au1x_ic1_chip;
		base = (व्योम __iomem *)KSEG1ADDR(AU1000_IC1_PHYS_ADDR);
	पूर्ण अन्यथा अणु
		bit = irq - AU1000_INTC0_INT_BASE;
		chip = &au1x_ic0_chip;
		base = (व्योम __iomem *)KSEG1ADDR(AU1000_IC0_PHYS_ADDR);
	पूर्ण

	अगर (bit > 31)
		वापस -EINVAL;

	ret = 0;

	चयन (flow_type) अणु	/* cfgregs 2:1:0 */
	हाल IRQ_TYPE_EDGE_RISING:	/* 0:0:1 */
		__raw_ग_लिखोl(1 << bit, base + IC_CFG2CLR);
		__raw_ग_लिखोl(1 << bit, base + IC_CFG1CLR);
		__raw_ग_लिखोl(1 << bit, base + IC_CFG0SET);
		handler = handle_edge_irq;
		name = "riseedge";
		अवरोध;
	हाल IRQ_TYPE_EDGE_FALLING:	/* 0:1:0 */
		__raw_ग_लिखोl(1 << bit, base + IC_CFG2CLR);
		__raw_ग_लिखोl(1 << bit, base + IC_CFG1SET);
		__raw_ग_लिखोl(1 << bit, base + IC_CFG0CLR);
		handler = handle_edge_irq;
		name = "falledge";
		अवरोध;
	हाल IRQ_TYPE_EDGE_BOTH:	/* 0:1:1 */
		__raw_ग_लिखोl(1 << bit, base + IC_CFG2CLR);
		__raw_ग_लिखोl(1 << bit, base + IC_CFG1SET);
		__raw_ग_लिखोl(1 << bit, base + IC_CFG0SET);
		handler = handle_edge_irq;
		name = "bothedge";
		अवरोध;
	हाल IRQ_TYPE_LEVEL_HIGH:	/* 1:0:1 */
		__raw_ग_लिखोl(1 << bit, base + IC_CFG2SET);
		__raw_ग_लिखोl(1 << bit, base + IC_CFG1CLR);
		__raw_ग_लिखोl(1 << bit, base + IC_CFG0SET);
		handler = handle_level_irq;
		name = "hilevel";
		अवरोध;
	हाल IRQ_TYPE_LEVEL_LOW:	/* 1:1:0 */
		__raw_ग_लिखोl(1 << bit, base + IC_CFG2SET);
		__raw_ग_लिखोl(1 << bit, base + IC_CFG1SET);
		__raw_ग_लिखोl(1 << bit, base + IC_CFG0CLR);
		handler = handle_level_irq;
		name = "lowlevel";
		अवरोध;
	हाल IRQ_TYPE_NONE:		/* 0:0:0 */
		__raw_ग_लिखोl(1 << bit, base + IC_CFG2CLR);
		__raw_ग_लिखोl(1 << bit, base + IC_CFG1CLR);
		__raw_ग_लिखोl(1 << bit, base + IC_CFG0CLR);
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण
	irq_set_chip_handler_name_locked(d, chip, handler, name);

	wmb();

	वापस ret;
पूर्ण

/******************************************************************************/

/*
 * au1300_gpic_chgcfg - change PIN configuration.
 * @gpio:	pin to change (0-based GPIO number from datasheet).
 * @clr:	clear all bits set in 'clr'.
 * @set:	set these bits.
 *
 * modअगरies a pins' configuration रेजिस्टर, bits set in @clr will
 * be cleared in the रेजिस्टर, bits in @set will be set.
 */
अटल अंतरभूत व्योम au1300_gpic_chgcfg(अचिन्हित पूर्णांक gpio,
				      अचिन्हित दीर्घ clr,
				      अचिन्हित दीर्घ set)
अणु
	व्योम __iomem *r = AU1300_GPIC_ADDR;
	अचिन्हित दीर्घ l;

	r += gpio * 4;	/* offset पूर्णांकo pin config array */
	l = __raw_पढ़ोl(r + AU1300_GPIC_PINCFG);
	l &= ~clr;
	l |= set;
	__raw_ग_लिखोl(l, r + AU1300_GPIC_PINCFG);
	wmb();
पूर्ण

/*
 * au1300_pinfunc_to_gpio - assign a pin as GPIO input (GPIO ctrl).
 * @pin:	pin (0-based GPIO number from datasheet).
 *
 * Assigns a GPIO pin to the GPIO controller, so its level can either
 * be पढ़ो or set through the generic GPIO functions.
 * If you need a GPOUT, use au1300_gpio_set_value(pin, 0/1).
 * REVISIT: is this function really necessary?
 */
व्योम au1300_pinfunc_to_gpio(क्रमागत au1300_multअगरunc_pins gpio)
अणु
	au1300_gpio_direction_input(gpio + AU1300_GPIO_BASE);
पूर्ण
EXPORT_SYMBOL_GPL(au1300_pinfunc_to_gpio);

/*
 * au1300_pinfunc_to_dev - assign a pin to the device function.
 * @pin:	pin (0-based GPIO number from datasheet).
 *
 * Assigns a GPIO pin to its associated device function; the pin will be
 * driven by the device and not through GPIO functions.
 */
व्योम au1300_pinfunc_to_dev(क्रमागत au1300_multअगरunc_pins gpio)
अणु
	व्योम __iomem *r = AU1300_GPIC_ADDR;
	अचिन्हित दीर्घ bit;

	r += GPIC_GPIO_BANKOFF(gpio);
	bit = GPIC_GPIO_TO_BIT(gpio);
	__raw_ग_लिखोl(bit, r + AU1300_GPIC_DEVSEL);
	wmb();
पूर्ण
EXPORT_SYMBOL_GPL(au1300_pinfunc_to_dev);

/*
 * au1300_set_irq_priority -  set पूर्णांकernal priority of IRQ.
 * @irq:	irq to set priority (linux irq number).
 * @p:		priority (0 = highest, 3 = lowest).
 */
व्योम au1300_set_irq_priority(अचिन्हित पूर्णांक irq, पूर्णांक p)
अणु
	irq -= ALCHEMY_GPIC_INT_BASE;
	au1300_gpic_chgcfg(irq, GPIC_CFG_IL_MASK, GPIC_CFG_IL_SET(p));
पूर्ण
EXPORT_SYMBOL_GPL(au1300_set_irq_priority);

/*
 * au1300_set_dbdma_gpio - assign a gpio to one of the DBDMA triggers.
 * @dchan:	dbdma trigger select (0, 1).
 * @gpio:	pin to assign as trigger.
 *
 * DBDMA controller has 2 बाह्यal trigger sources; this function
 * assigns a GPIO to the selected trigger.
 */
व्योम au1300_set_dbdma_gpio(पूर्णांक dchan, अचिन्हित पूर्णांक gpio)
अणु
	अचिन्हित दीर्घ r;

	अगर ((dchan >= 0) && (dchan <= 1)) अणु
		r = __raw_पढ़ोl(AU1300_GPIC_ADDR + AU1300_GPIC_DMASEL);
		r &= ~(0xff << (8 * dchan));
		r |= (gpio & 0x7f) << (8 * dchan);
		__raw_ग_लिखोl(r, AU1300_GPIC_ADDR + AU1300_GPIC_DMASEL);
		wmb();
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम gpic_pin_set_idlewake(अचिन्हित पूर्णांक gpio, पूर्णांक allow)
अणु
	au1300_gpic_chgcfg(gpio, GPIC_CFG_IDLEWAKE,
			   allow ? GPIC_CFG_IDLEWAKE : 0);
पूर्ण

अटल व्योम au1300_gpic_mask(काष्ठा irq_data *d)
अणु
	व्योम __iomem *r = AU1300_GPIC_ADDR;
	अचिन्हित दीर्घ bit, irq = d->irq;

	irq -= ALCHEMY_GPIC_INT_BASE;
	r += GPIC_GPIO_BANKOFF(irq);
	bit = GPIC_GPIO_TO_BIT(irq);
	__raw_ग_लिखोl(bit, r + AU1300_GPIC_IDIS);
	wmb();

	gpic_pin_set_idlewake(irq, 0);
पूर्ण

अटल व्योम au1300_gpic_unmask(काष्ठा irq_data *d)
अणु
	व्योम __iomem *r = AU1300_GPIC_ADDR;
	अचिन्हित दीर्घ bit, irq = d->irq;

	irq -= ALCHEMY_GPIC_INT_BASE;

	gpic_pin_set_idlewake(irq, 1);

	r += GPIC_GPIO_BANKOFF(irq);
	bit = GPIC_GPIO_TO_BIT(irq);
	__raw_ग_लिखोl(bit, r + AU1300_GPIC_IEN);
	wmb();
पूर्ण

अटल व्योम au1300_gpic_maskack(काष्ठा irq_data *d)
अणु
	व्योम __iomem *r = AU1300_GPIC_ADDR;
	अचिन्हित दीर्घ bit, irq = d->irq;

	irq -= ALCHEMY_GPIC_INT_BASE;
	r += GPIC_GPIO_BANKOFF(irq);
	bit = GPIC_GPIO_TO_BIT(irq);
	__raw_ग_लिखोl(bit, r + AU1300_GPIC_IPEND);	/* ack */
	__raw_ग_लिखोl(bit, r + AU1300_GPIC_IDIS);	/* mask */
	wmb();

	gpic_pin_set_idlewake(irq, 0);
पूर्ण

अटल व्योम au1300_gpic_ack(काष्ठा irq_data *d)
अणु
	व्योम __iomem *r = AU1300_GPIC_ADDR;
	अचिन्हित दीर्घ bit, irq = d->irq;

	irq -= ALCHEMY_GPIC_INT_BASE;
	r += GPIC_GPIO_BANKOFF(irq);
	bit = GPIC_GPIO_TO_BIT(irq);
	__raw_ग_लिखोl(bit, r + AU1300_GPIC_IPEND);	/* ack */
	wmb();
पूर्ण

अटल काष्ठा irq_chip au1300_gpic = अणु
	.name		= "GPIOINT",
	.irq_ack	= au1300_gpic_ack,
	.irq_mask	= au1300_gpic_mask,
	.irq_mask_ack	= au1300_gpic_maskack,
	.irq_unmask	= au1300_gpic_unmask,
	.irq_set_type	= au1300_gpic_settype,
पूर्ण;

अटल पूर्णांक au1300_gpic_settype(काष्ठा irq_data *d, अचिन्हित पूर्णांक type)
अणु
	अचिन्हित दीर्घ s;
	अचिन्हित अक्षर *name = शून्य;
	irq_flow_handler_t hdl = शून्य;

	चयन (type) अणु
	हाल IRQ_TYPE_LEVEL_HIGH:
		s = GPIC_CFG_IC_LEVEL_HIGH;
		name = "high";
		hdl = handle_level_irq;
		अवरोध;
	हाल IRQ_TYPE_LEVEL_LOW:
		s = GPIC_CFG_IC_LEVEL_LOW;
		name = "low";
		hdl = handle_level_irq;
		अवरोध;
	हाल IRQ_TYPE_EDGE_RISING:
		s = GPIC_CFG_IC_EDGE_RISE;
		name = "posedge";
		hdl = handle_edge_irq;
		अवरोध;
	हाल IRQ_TYPE_EDGE_FALLING:
		s = GPIC_CFG_IC_EDGE_FALL;
		name = "negedge";
		hdl = handle_edge_irq;
		अवरोध;
	हाल IRQ_TYPE_EDGE_BOTH:
		s = GPIC_CFG_IC_EDGE_BOTH;
		name = "bothedge";
		hdl = handle_edge_irq;
		अवरोध;
	हाल IRQ_TYPE_NONE:
		s = GPIC_CFG_IC_OFF;
		name = "disabled";
		hdl = handle_level_irq;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	irq_set_chip_handler_name_locked(d, &au1300_gpic, hdl, name);

	au1300_gpic_chgcfg(d->irq - ALCHEMY_GPIC_INT_BASE, GPIC_CFG_IC_MASK, s);

	वापस 0;
पूर्ण

/******************************************************************************/

अटल अंतरभूत व्योम ic_init(व्योम __iomem *base)
अणु
	/* initialize पूर्णांकerrupt controller to a safe state */
	__raw_ग_लिखोl(0xffffffff, base + IC_CFG0CLR);
	__raw_ग_लिखोl(0xffffffff, base + IC_CFG1CLR);
	__raw_ग_लिखोl(0xffffffff, base + IC_CFG2CLR);
	__raw_ग_लिखोl(0xffffffff, base + IC_MASKCLR);
	__raw_ग_लिखोl(0xffffffff, base + IC_ASSIGNCLR);
	__raw_ग_लिखोl(0xffffffff, base + IC_WAKECLR);
	__raw_ग_लिखोl(0xffffffff, base + IC_SRCSET);
	__raw_ग_लिखोl(0xffffffff, base + IC_FALLINGCLR);
	__raw_ग_लिखोl(0xffffffff, base + IC_RISINGCLR);
	__raw_ग_लिखोl(0x00000000, base + IC_TESTBIT);
	wmb();
पूर्ण

अटल अचिन्हित दीर्घ alchemy_gpic_pmdata[ALCHEMY_GPIC_INT_NUM + 6];

अटल अंतरभूत व्योम alchemy_ic_suspend_one(व्योम __iomem *base, अचिन्हित दीर्घ *d)
अणु
	d[0] = __raw_पढ़ोl(base + IC_CFG0RD);
	d[1] = __raw_पढ़ोl(base + IC_CFG1RD);
	d[2] = __raw_पढ़ोl(base + IC_CFG2RD);
	d[3] = __raw_पढ़ोl(base + IC_SRCRD);
	d[4] = __raw_पढ़ोl(base + IC_ASSIGNRD);
	d[5] = __raw_पढ़ोl(base + IC_WAKERD);
	d[6] = __raw_पढ़ोl(base + IC_MASKRD);
	ic_init(base);		/* shut it up too जबतक at it */
पूर्ण

अटल अंतरभूत व्योम alchemy_ic_resume_one(व्योम __iomem *base, अचिन्हित दीर्घ *d)
अणु
	ic_init(base);

	__raw_ग_लिखोl(d[0], base + IC_CFG0SET);
	__raw_ग_लिखोl(d[1], base + IC_CFG1SET);
	__raw_ग_लिखोl(d[2], base + IC_CFG2SET);
	__raw_ग_लिखोl(d[3], base + IC_SRCSET);
	__raw_ग_लिखोl(d[4], base + IC_ASSIGNSET);
	__raw_ग_लिखोl(d[5], base + IC_WAKESET);
	wmb();

	__raw_ग_लिखोl(d[6], base + IC_MASKSET);
	wmb();
पूर्ण

अटल पूर्णांक alchemy_ic_suspend(व्योम)
अणु
	alchemy_ic_suspend_one((व्योम __iomem *)KSEG1ADDR(AU1000_IC0_PHYS_ADDR),
			       alchemy_gpic_pmdata);
	alchemy_ic_suspend_one((व्योम __iomem *)KSEG1ADDR(AU1000_IC1_PHYS_ADDR),
			       &alchemy_gpic_pmdata[7]);
	वापस 0;
पूर्ण

अटल व्योम alchemy_ic_resume(व्योम)
अणु
	alchemy_ic_resume_one((व्योम __iomem *)KSEG1ADDR(AU1000_IC1_PHYS_ADDR),
			      &alchemy_gpic_pmdata[7]);
	alchemy_ic_resume_one((व्योम __iomem *)KSEG1ADDR(AU1000_IC0_PHYS_ADDR),
			      alchemy_gpic_pmdata);
पूर्ण

अटल पूर्णांक alchemy_gpic_suspend(व्योम)
अणु
	व्योम __iomem *base = (व्योम __iomem *)KSEG1ADDR(AU1300_GPIC_PHYS_ADDR);
	पूर्णांक i;

	/* save 4 पूर्णांकerrupt mask status रेजिस्टरs */
	alchemy_gpic_pmdata[0] = __raw_पढ़ोl(base + AU1300_GPIC_IEN + 0x0);
	alchemy_gpic_pmdata[1] = __raw_पढ़ोl(base + AU1300_GPIC_IEN + 0x4);
	alchemy_gpic_pmdata[2] = __raw_पढ़ोl(base + AU1300_GPIC_IEN + 0x8);
	alchemy_gpic_pmdata[3] = __raw_पढ़ोl(base + AU1300_GPIC_IEN + 0xc);

	/* save misc रेजिस्टर(s) */
	alchemy_gpic_pmdata[4] = __raw_पढ़ोl(base + AU1300_GPIC_DMASEL);

	/* molto silenzioso */
	__raw_ग_लिखोl(~0UL, base + AU1300_GPIC_IDIS + 0x0);
	__raw_ग_लिखोl(~0UL, base + AU1300_GPIC_IDIS + 0x4);
	__raw_ग_लिखोl(~0UL, base + AU1300_GPIC_IDIS + 0x8);
	__raw_ग_लिखोl(~0UL, base + AU1300_GPIC_IDIS + 0xc);
	wmb();

	/* save pin/पूर्णांक-type configuration */
	base += AU1300_GPIC_PINCFG;
	क्रम (i = 0; i < ALCHEMY_GPIC_INT_NUM; i++)
		alchemy_gpic_pmdata[i + 5] = __raw_पढ़ोl(base + (i << 2));

	wmb();

	वापस 0;
पूर्ण

अटल व्योम alchemy_gpic_resume(व्योम)
अणु
	व्योम __iomem *base = (व्योम __iomem *)KSEG1ADDR(AU1300_GPIC_PHYS_ADDR);
	पूर्णांक i;

	/* disable all first */
	__raw_ग_लिखोl(~0UL, base + AU1300_GPIC_IDIS + 0x0);
	__raw_ग_लिखोl(~0UL, base + AU1300_GPIC_IDIS + 0x4);
	__raw_ग_लिखोl(~0UL, base + AU1300_GPIC_IDIS + 0x8);
	__raw_ग_लिखोl(~0UL, base + AU1300_GPIC_IDIS + 0xc);
	wmb();

	/* restore pin/पूर्णांक-type configurations */
	base += AU1300_GPIC_PINCFG;
	क्रम (i = 0; i < ALCHEMY_GPIC_INT_NUM; i++)
		__raw_ग_लिखोl(alchemy_gpic_pmdata[i + 5], base + (i << 2));
	wmb();

	/* restore misc रेजिस्टर(s) */
	base = (व्योम __iomem *)KSEG1ADDR(AU1300_GPIC_PHYS_ADDR);
	__raw_ग_लिखोl(alchemy_gpic_pmdata[4], base + AU1300_GPIC_DMASEL);
	wmb();

	/* finally restore masks */
	__raw_ग_लिखोl(alchemy_gpic_pmdata[0], base + AU1300_GPIC_IEN + 0x0);
	__raw_ग_लिखोl(alchemy_gpic_pmdata[1], base + AU1300_GPIC_IEN + 0x4);
	__raw_ग_लिखोl(alchemy_gpic_pmdata[2], base + AU1300_GPIC_IEN + 0x8);
	__raw_ग_लिखोl(alchemy_gpic_pmdata[3], base + AU1300_GPIC_IEN + 0xc);
	wmb();
पूर्ण

अटल काष्ठा syscore_ops alchemy_ic_pmops = अणु
	.suspend	= alchemy_ic_suspend,
	.resume		= alchemy_ic_resume,
पूर्ण;

अटल काष्ठा syscore_ops alchemy_gpic_pmops = अणु
	.suspend	= alchemy_gpic_suspend,
	.resume		= alchemy_gpic_resume,
पूर्ण;

/******************************************************************************/

/* create chained handlers क्रम the 4 IC requests to the MIPS IRQ ctrl */
#घोषणा DISP(name, base, addr)						      \
अटल व्योम au1000_##name##_dispatch(काष्ठा irq_desc *d)		      \
अणु									      \
	अचिन्हित दीर्घ r = __raw_पढ़ोl((व्योम __iomem *)KSEG1ADDR(addr));	      \
	अगर (likely(r))							      \
		generic_handle_irq(base + __ffs(r));			      \
	अन्यथा								      \
		spurious_पूर्णांकerrupt();					      \
पूर्ण

DISP(ic0r0, AU1000_INTC0_INT_BASE, AU1000_IC0_PHYS_ADDR + IC_REQ0INT)
DISP(ic0r1, AU1000_INTC0_INT_BASE, AU1000_IC0_PHYS_ADDR + IC_REQ1INT)
DISP(ic1r0, AU1000_INTC1_INT_BASE, AU1000_IC1_PHYS_ADDR + IC_REQ0INT)
DISP(ic1r1, AU1000_INTC1_INT_BASE, AU1000_IC1_PHYS_ADDR + IC_REQ1INT)

अटल व्योम alchemy_gpic_dispatch(काष्ठा irq_desc *d)
अणु
	पूर्णांक i = __raw_पढ़ोl(AU1300_GPIC_ADDR + AU1300_GPIC_PRIENC);
	generic_handle_irq(ALCHEMY_GPIC_INT_BASE + i);
पूर्ण

/******************************************************************************/

अटल व्योम __init au1000_init_irq(काष्ठा alchemy_irqmap *map)
अणु
	अचिन्हित पूर्णांक bit, irq_nr;
	व्योम __iomem *base;

	ic_init((व्योम __iomem *)KSEG1ADDR(AU1000_IC0_PHYS_ADDR));
	ic_init((व्योम __iomem *)KSEG1ADDR(AU1000_IC1_PHYS_ADDR));
	रेजिस्टर_syscore_ops(&alchemy_ic_pmops);
	mips_cpu_irq_init();

	/* रेजिस्टर all 64 possible IC0+IC1 irq sources as type "none".
	 * Use set_irq_type() to set edge/level behaviour at runसमय.
	 */
	क्रम (irq_nr = AU1000_INTC0_INT_BASE;
	     (irq_nr < AU1000_INTC0_INT_BASE + 32); irq_nr++)
		au1x_ic_settype(irq_get_irq_data(irq_nr), IRQ_TYPE_NONE);

	क्रम (irq_nr = AU1000_INTC1_INT_BASE;
	     (irq_nr < AU1000_INTC1_INT_BASE + 32); irq_nr++)
		au1x_ic_settype(irq_get_irq_data(irq_nr), IRQ_TYPE_NONE);

	/*
	 * Initialize IC0, which is fixed per processor.
	 */
	जबतक (map->irq != -1) अणु
		irq_nr = map->irq;

		अगर (irq_nr >= AU1000_INTC1_INT_BASE) अणु
			bit = irq_nr - AU1000_INTC1_INT_BASE;
			base = (व्योम __iomem *)KSEG1ADDR(AU1000_IC1_PHYS_ADDR);
		पूर्ण अन्यथा अणु
			bit = irq_nr - AU1000_INTC0_INT_BASE;
			base = (व्योम __iomem *)KSEG1ADDR(AU1000_IC0_PHYS_ADDR);
		पूर्ण
		अगर (map->prio == 0)
			__raw_ग_लिखोl(1 << bit, base + IC_ASSIGNSET);

		au1x_ic_settype(irq_get_irq_data(irq_nr), map->type);
		++map;
	पूर्ण

	irq_set_chained_handler(MIPS_CPU_IRQ_BASE + 2, au1000_ic0r0_dispatch);
	irq_set_chained_handler(MIPS_CPU_IRQ_BASE + 3, au1000_ic0r1_dispatch);
	irq_set_chained_handler(MIPS_CPU_IRQ_BASE + 4, au1000_ic1r0_dispatch);
	irq_set_chained_handler(MIPS_CPU_IRQ_BASE + 5, au1000_ic1r1_dispatch);
पूर्ण

अटल व्योम __init alchemy_gpic_init_irq(स्थिर काष्ठा alchemy_irqmap *dपूर्णांकs)
अणु
	पूर्णांक i;
	व्योम __iomem *bank_base;

	रेजिस्टर_syscore_ops(&alchemy_gpic_pmops);
	mips_cpu_irq_init();

	/* disable & ack all possible पूर्णांकerrupt sources */
	क्रम (i = 0; i < 4; i++) अणु
		bank_base = AU1300_GPIC_ADDR + (i * 4);
		__raw_ग_लिखोl(~0UL, bank_base + AU1300_GPIC_IDIS);
		wmb();
		__raw_ग_लिखोl(~0UL, bank_base + AU1300_GPIC_IPEND);
		wmb();
	पूर्ण

	/* रेजिस्टर an irq_chip क्रम them, with 2nd highest priority */
	क्रम (i = ALCHEMY_GPIC_INT_BASE; i <= ALCHEMY_GPIC_INT_LAST; i++) अणु
		au1300_set_irq_priority(i, 1);
		au1300_gpic_settype(irq_get_irq_data(i), IRQ_TYPE_NONE);
	पूर्ण

	/* setup known on-chip sources */
	जबतक ((i = dपूर्णांकs->irq) != -1) अणु
		au1300_gpic_settype(irq_get_irq_data(i), dपूर्णांकs->type);
		au1300_set_irq_priority(i, dपूर्णांकs->prio);

		अगर (dपूर्णांकs->पूर्णांकernal)
			au1300_pinfunc_to_dev(i - ALCHEMY_GPIC_INT_BASE);

		dपूर्णांकs++;
	पूर्ण

	irq_set_chained_handler(MIPS_CPU_IRQ_BASE + 2, alchemy_gpic_dispatch);
	irq_set_chained_handler(MIPS_CPU_IRQ_BASE + 3, alchemy_gpic_dispatch);
	irq_set_chained_handler(MIPS_CPU_IRQ_BASE + 4, alchemy_gpic_dispatch);
	irq_set_chained_handler(MIPS_CPU_IRQ_BASE + 5, alchemy_gpic_dispatch);
पूर्ण

/******************************************************************************/

व्योम __init arch_init_irq(व्योम)
अणु
	चयन (alchemy_get_cputype()) अणु
	हाल ALCHEMY_CPU_AU1000:
		au1000_init_irq(au1000_irqmap);
		अवरोध;
	हाल ALCHEMY_CPU_AU1500:
		au1000_init_irq(au1500_irqmap);
		अवरोध;
	हाल ALCHEMY_CPU_AU1100:
		au1000_init_irq(au1100_irqmap);
		अवरोध;
	हाल ALCHEMY_CPU_AU1550:
		au1000_init_irq(au1550_irqmap);
		अवरोध;
	हाल ALCHEMY_CPU_AU1200:
		au1000_init_irq(au1200_irqmap);
		अवरोध;
	हाल ALCHEMY_CPU_AU1300:
		alchemy_gpic_init_irq(au1300_irqmap);
		अवरोध;
	शेष:
		pr_err("unknown Alchemy IRQ core\n");
		अवरोध;
	पूर्ण
पूर्ण

यंत्रlinkage व्योम plat_irq_dispatch(व्योम)
अणु
	अचिन्हित दीर्घ r = (पढ़ो_c0_status() & पढ़ो_c0_cause()) >> 8;
	करो_IRQ(MIPS_CPU_IRQ_BASE + __ffs(r & 0xff));
पूर्ण
