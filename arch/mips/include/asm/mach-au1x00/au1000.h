<शैली गुरु>
/*
 *
 * BRIEF MODULE DESCRIPTION
 *	Include file क्रम Alchemy Semiconductor's Au1k CPU.
 *
 * Copyright 2000-2001, 2006-2008 MontaVista Software Inc.
 * Author: MontaVista Software, Inc. <source@mvista.com>
 *
 *  This program is मुक्त software; you can redistribute  it and/or modअगरy it
 *  under  the terms of  the GNU General  Public License as published by the
 *  Free Software Foundation;  either version 2 of the  License, or (at your
 *  option) any later version.
 *
 *  THIS  SOFTWARE  IS PROVIDED   ``AS  IS'' AND   ANY  EXPRESS OR IMPLIED
 *  WARRANTIES,   INCLUDING, BUT NOT  LIMITED  TO, THE IMPLIED WARRANTIES OF
 *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN
 *  NO  EVENT  SHALL   THE AUTHOR  BE    LIABLE FOR ANY   सूचीECT, INसूचीECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 *  NOT LIMITED   TO, PROCUREMENT OF  SUBSTITUTE GOODS  OR SERVICES; LOSS OF
 *  USE, DATA,  OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 *  ANY THEORY OF LIABILITY, WHETHER IN  CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 *  THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *  You should have received a copy of the  GNU General Public License aदीर्घ
 *  with this program; अगर not, ग_लिखो  to the Free Software Foundation, Inc.,
 *  675 Mass Ave, Cambridge, MA 02139, USA.
 */

 /*
  * some definitions add by takuzo@sm.sony.co.jp and sato@sm.sony.co.jp
  */

#अगर_अघोषित _AU1000_H_
#घोषणा _AU1000_H_

/* SOC Interrupt numbers */
/* Au1000-style (IC0/1): 2 controllers with 32 sources each */
#घोषणा AU1000_INTC0_INT_BASE	(MIPS_CPU_IRQ_BASE + 8)
#घोषणा AU1000_INTC0_INT_LAST	(AU1000_INTC0_INT_BASE + 31)
#घोषणा AU1000_INTC1_INT_BASE	(AU1000_INTC0_INT_LAST + 1)
#घोषणा AU1000_INTC1_INT_LAST	(AU1000_INTC1_INT_BASE + 31)
#घोषणा AU1000_MAX_INTR		AU1000_INTC1_INT_LAST

/* Au1300-style (GPIC): 1 controller with up to 128 sources */
#घोषणा ALCHEMY_GPIC_INT_BASE	(MIPS_CPU_IRQ_BASE + 8)
#घोषणा ALCHEMY_GPIC_INT_NUM	128
#घोषणा ALCHEMY_GPIC_INT_LAST	(ALCHEMY_GPIC_INT_BASE + ALCHEMY_GPIC_INT_NUM - 1)

/* common घड़ी names, shared among all variants. AUXPLL2 is Au1300 */
#घोषणा ALCHEMY_ROOT_CLK		"root_clk"
#घोषणा ALCHEMY_CPU_CLK			"cpu_clk"
#घोषणा ALCHEMY_AUXPLL_CLK		"auxpll_clk"
#घोषणा ALCHEMY_AUXPLL2_CLK		"auxpll2_clk"
#घोषणा ALCHEMY_SYSBUS_CLK		"sysbus_clk"
#घोषणा ALCHEMY_PERIPH_CLK		"periph_clk"
#घोषणा ALCHEMY_MEM_CLK			"mem_clk"
#घोषणा ALCHEMY_LR_CLK			"lr_clk"
#घोषणा ALCHEMY_FG0_CLK			"fg0_clk"
#घोषणा ALCHEMY_FG1_CLK			"fg1_clk"
#घोषणा ALCHEMY_FG2_CLK			"fg2_clk"
#घोषणा ALCHEMY_FG3_CLK			"fg3_clk"
#घोषणा ALCHEMY_FG4_CLK			"fg4_clk"
#घोषणा ALCHEMY_FG5_CLK			"fg5_clk"

/* Au1300 peripheral पूर्णांकerrupt numbers */
#घोषणा AU1300_FIRST_INT	(ALCHEMY_GPIC_INT_BASE)
#घोषणा AU1300_UART1_INT	(AU1300_FIRST_INT + 17)
#घोषणा AU1300_UART2_INT	(AU1300_FIRST_INT + 25)
#घोषणा AU1300_UART3_INT	(AU1300_FIRST_INT + 27)
#घोषणा AU1300_SD1_INT		(AU1300_FIRST_INT + 32)
#घोषणा AU1300_SD2_INT		(AU1300_FIRST_INT + 38)
#घोषणा AU1300_PSC0_INT		(AU1300_FIRST_INT + 48)
#घोषणा AU1300_PSC1_INT		(AU1300_FIRST_INT + 52)
#घोषणा AU1300_PSC2_INT		(AU1300_FIRST_INT + 56)
#घोषणा AU1300_PSC3_INT		(AU1300_FIRST_INT + 60)
#घोषणा AU1300_न_अंकD_INT		(AU1300_FIRST_INT + 62)
#घोषणा AU1300_DDMA_INT		(AU1300_FIRST_INT + 75)
#घोषणा AU1300_MMU_INT		(AU1300_FIRST_INT + 76)
#घोषणा AU1300_MPU_INT		(AU1300_FIRST_INT + 77)
#घोषणा AU1300_GPU_INT		(AU1300_FIRST_INT + 78)
#घोषणा AU1300_UDMA_INT		(AU1300_FIRST_INT + 79)
#घोषणा AU1300_TOY_INT		(AU1300_FIRST_INT + 80)
#घोषणा AU1300_TOY_MATCH0_INT	(AU1300_FIRST_INT + 81)
#घोषणा AU1300_TOY_MATCH1_INT	(AU1300_FIRST_INT + 82)
#घोषणा AU1300_TOY_MATCH2_INT	(AU1300_FIRST_INT + 83)
#घोषणा AU1300_RTC_INT		(AU1300_FIRST_INT + 84)
#घोषणा AU1300_RTC_MATCH0_INT	(AU1300_FIRST_INT + 85)
#घोषणा AU1300_RTC_MATCH1_INT	(AU1300_FIRST_INT + 86)
#घोषणा AU1300_RTC_MATCH2_INT	(AU1300_FIRST_INT + 87)
#घोषणा AU1300_UART0_INT	(AU1300_FIRST_INT + 88)
#घोषणा AU1300_SD0_INT		(AU1300_FIRST_INT + 89)
#घोषणा AU1300_USB_INT		(AU1300_FIRST_INT + 90)
#घोषणा AU1300_LCD_INT		(AU1300_FIRST_INT + 91)
#घोषणा AU1300_BSA_INT		(AU1300_FIRST_INT + 92)
#घोषणा AU1300_MPE_INT		(AU1300_FIRST_INT + 93)
#घोषणा AU1300_ITE_INT		(AU1300_FIRST_INT + 94)
#घोषणा AU1300_AES_INT		(AU1300_FIRST_INT + 95)
#घोषणा AU1300_CIM_INT		(AU1300_FIRST_INT + 96)

/**********************************************************************/

/*
 * Physical base addresses क्रम पूर्णांकegrated peripherals
 * 0..au1000 1..au1500 2..au1100 3..au1550 4..au1200 5..au1300
 */

#घोषणा AU1000_AC97_PHYS_ADDR		0x10000000 /* 012 */
#घोषणा AU1300_ROM_PHYS_ADDR		0x10000000 /* 5 */
#घोषणा AU1300_OTP_PHYS_ADDR		0x10002000 /* 5 */
#घोषणा AU1300_VSS_PHYS_ADDR		0x10003000 /* 5 */
#घोषणा AU1300_UART0_PHYS_ADDR		0x10100000 /* 5 */
#घोषणा AU1300_UART1_PHYS_ADDR		0x10101000 /* 5 */
#घोषणा AU1300_UART2_PHYS_ADDR		0x10102000 /* 5 */
#घोषणा AU1300_UART3_PHYS_ADDR		0x10103000 /* 5 */
#घोषणा AU1000_USB_OHCI_PHYS_ADDR	0x10100000 /* 012 */
#घोषणा AU1000_USB_UDC_PHYS_ADDR	0x10200000 /* 0123 */
#घोषणा AU1300_GPIC_PHYS_ADDR		0x10200000 /* 5 */
#घोषणा AU1000_IRDA_PHYS_ADDR		0x10300000 /* 02 */
#घोषणा AU1200_AES_PHYS_ADDR		0x10300000 /* 45 */
#घोषणा AU1000_IC0_PHYS_ADDR		0x10400000 /* 01234 */
#घोषणा AU1300_GPU_PHYS_ADDR		0x10500000 /* 5 */
#घोषणा AU1000_MAC0_PHYS_ADDR		0x10500000 /* 023 */
#घोषणा AU1000_MAC1_PHYS_ADDR		0x10510000 /* 023 */
#घोषणा AU1000_MACEN_PHYS_ADDR		0x10520000 /* 023 */
#घोषणा AU1100_SD0_PHYS_ADDR		0x10600000 /* 245 */
#घोषणा AU1300_SD1_PHYS_ADDR		0x10601000 /* 5 */
#घोषणा AU1300_SD2_PHYS_ADDR		0x10602000 /* 5 */
#घोषणा AU1100_SD1_PHYS_ADDR		0x10680000 /* 24 */
#घोषणा AU1300_SYS_PHYS_ADDR		0x10900000 /* 5 */
#घोषणा AU1550_PSC2_PHYS_ADDR		0x10A00000 /* 3 */
#घोषणा AU1550_PSC3_PHYS_ADDR		0x10B00000 /* 3 */
#घोषणा AU1300_PSC0_PHYS_ADDR		0x10A00000 /* 5 */
#घोषणा AU1300_PSC1_PHYS_ADDR		0x10A01000 /* 5 */
#घोषणा AU1300_PSC2_PHYS_ADDR		0x10A02000 /* 5 */
#घोषणा AU1300_PSC3_PHYS_ADDR		0x10A03000 /* 5 */
#घोषणा AU1000_I2S_PHYS_ADDR		0x11000000 /* 02 */
#घोषणा AU1500_MAC0_PHYS_ADDR		0x11500000 /* 1 */
#घोषणा AU1500_MAC1_PHYS_ADDR		0x11510000 /* 1 */
#घोषणा AU1500_MACEN_PHYS_ADDR		0x11520000 /* 1 */
#घोषणा AU1000_UART0_PHYS_ADDR		0x11100000 /* 01234 */
#घोषणा AU1200_SWCNT_PHYS_ADDR		0x1110010C /* 4 */
#घोषणा AU1000_UART1_PHYS_ADDR		0x11200000 /* 0234 */
#घोषणा AU1000_UART2_PHYS_ADDR		0x11300000 /* 0 */
#घोषणा AU1000_UART3_PHYS_ADDR		0x11400000 /* 0123 */
#घोषणा AU1000_SSI0_PHYS_ADDR		0x11600000 /* 02 */
#घोषणा AU1000_SSI1_PHYS_ADDR		0x11680000 /* 02 */
#घोषणा AU1500_GPIO2_PHYS_ADDR		0x11700000 /* 1234 */
#घोषणा AU1000_IC1_PHYS_ADDR		0x11800000 /* 01234 */
#घोषणा AU1000_SYS_PHYS_ADDR		0x11900000 /* 012345 */
#घोषणा AU1550_PSC0_PHYS_ADDR		0x11A00000 /* 34 */
#घोषणा AU1550_PSC1_PHYS_ADDR		0x11B00000 /* 34 */
#घोषणा AU1000_MEM_PHYS_ADDR		0x14000000 /* 01234 */
#घोषणा AU1000_STATIC_MEM_PHYS_ADDR	0x14001000 /* 01234 */
#घोषणा AU1300_UDMA_PHYS_ADDR		0x14001800 /* 5 */
#घोषणा AU1000_DMA_PHYS_ADDR		0x14002000 /* 012 */
#घोषणा AU1550_DBDMA_PHYS_ADDR		0x14002000 /* 345 */
#घोषणा AU1550_DBDMA_CONF_PHYS_ADDR	0x14003000 /* 345 */
#घोषणा AU1000_MACDMA0_PHYS_ADDR	0x14004000 /* 0123 */
#घोषणा AU1000_MACDMA1_PHYS_ADDR	0x14004200 /* 0123 */
#घोषणा AU1200_CIM_PHYS_ADDR		0x14004000 /* 45 */
#घोषणा AU1500_PCI_PHYS_ADDR		0x14005000 /* 13 */
#घोषणा AU1550_PE_PHYS_ADDR		0x14008000 /* 3 */
#घोषणा AU1200_MAEBE_PHYS_ADDR		0x14010000 /* 4 */
#घोषणा AU1200_MAEFE_PHYS_ADDR		0x14012000 /* 4 */
#घोषणा AU1300_MAEITE_PHYS_ADDR		0x14010000 /* 5 */
#घोषणा AU1300_MAEMPE_PHYS_ADDR		0x14014000 /* 5 */
#घोषणा AU1550_USB_OHCI_PHYS_ADDR	0x14020000 /* 3 */
#घोषणा AU1200_USB_CTL_PHYS_ADDR	0x14020000 /* 4 */
#घोषणा AU1200_USB_OTG_PHYS_ADDR	0x14020020 /* 4 */
#घोषणा AU1200_USB_OHCI_PHYS_ADDR	0x14020100 /* 4 */
#घोषणा AU1200_USB_EHCI_PHYS_ADDR	0x14020200 /* 4 */
#घोषणा AU1200_USB_UDC_PHYS_ADDR	0x14022000 /* 4 */
#घोषणा AU1300_USB_EHCI_PHYS_ADDR	0x14020000 /* 5 */
#घोषणा AU1300_USB_OHCI0_PHYS_ADDR	0x14020400 /* 5 */
#घोषणा AU1300_USB_OHCI1_PHYS_ADDR	0x14020800 /* 5 */
#घोषणा AU1300_USB_CTL_PHYS_ADDR	0x14021000 /* 5 */
#घोषणा AU1300_USB_OTG_PHYS_ADDR	0x14022000 /* 5 */
#घोषणा AU1300_MAEBSA_PHYS_ADDR		0x14030000 /* 5 */
#घोषणा AU1100_LCD_PHYS_ADDR		0x15000000 /* 2 */
#घोषणा AU1200_LCD_PHYS_ADDR		0x15000000 /* 45 */
#घोषणा AU1500_PCI_MEM_PHYS_ADDR	0x400000000ULL /* 13 */
#घोषणा AU1500_PCI_IO_PHYS_ADDR		0x500000000ULL /* 13 */
#घोषणा AU1500_PCI_CONFIG0_PHYS_ADDR	0x600000000ULL /* 13 */
#घोषणा AU1500_PCI_CONFIG1_PHYS_ADDR	0x680000000ULL /* 13 */
#घोषणा AU1000_PCMCIA_IO_PHYS_ADDR	0xF00000000ULL /* 012345 */
#घोषणा AU1000_PCMCIA_ATTR_PHYS_ADDR	0xF40000000ULL /* 012345 */
#घोषणा AU1000_PCMCIA_MEM_PHYS_ADDR	0xF80000000ULL /* 012345 */

/**********************************************************************/


/*
 * Au1300 GPIO+INT controller (GPIC) रेजिस्टर offsets and bits
 * Registers are 128bits (0x10 bytes), भागided पूर्णांकo 4 "banks".
 */
#घोषणा AU1300_GPIC_PINVAL	0x0000
#घोषणा AU1300_GPIC_PINVALCLR	0x0010
#घोषणा AU1300_GPIC_IPEND	0x0020
#घोषणा AU1300_GPIC_PRIENC	0x0030
#घोषणा AU1300_GPIC_IEN		0x0040	/* पूर्णांक_mask in manual */
#घोषणा AU1300_GPIC_IDIS	0x0050	/* पूर्णांक_maskclr in manual */
#घोषणा AU1300_GPIC_DMASEL	0x0060
#घोषणा AU1300_GPIC_DEVSEL	0x0080
#घोषणा AU1300_GPIC_DEVCLR	0x0090
#घोषणा AU1300_GPIC_RSTVAL	0x00a0
/* pin configuration space. one 32bit रेजिस्टर क्रम up to 128 IRQs */
#घोषणा AU1300_GPIC_PINCFG	0x1000

#घोषणा GPIC_GPIO_TO_BIT(gpio)	\
	(1 << ((gpio) & 0x1f))

#घोषणा GPIC_GPIO_BANKOFF(gpio) \
	(((gpio) >> 5) * 4)

/* Pin Control bits: who owns the pin, what करोes it करो */
#घोषणा GPIC_CFG_PC_GPIN		0
#घोषणा GPIC_CFG_PC_DEV			1
#घोषणा GPIC_CFG_PC_GPOLOW		2
#घोषणा GPIC_CFG_PC_GPOHIGH		3
#घोषणा GPIC_CFG_PC_MASK		3

/* assign pin to MIPS IRQ line */
#घोषणा GPIC_CFG_IL_SET(x)	(((x) & 3) << 2)
#घोषणा GPIC_CFG_IL_MASK	(3 << 2)

/* pin पूर्णांकerrupt type setup */
#घोषणा GPIC_CFG_IC_OFF		(0 << 4)
#घोषणा GPIC_CFG_IC_LEVEL_LOW	(1 << 4)
#घोषणा GPIC_CFG_IC_LEVEL_HIGH	(2 << 4)
#घोषणा GPIC_CFG_IC_EDGE_FALL	(5 << 4)
#घोषणा GPIC_CFG_IC_EDGE_RISE	(6 << 4)
#घोषणा GPIC_CFG_IC_EDGE_BOTH	(7 << 4)
#घोषणा GPIC_CFG_IC_MASK	(7 << 4)

/* allow पूर्णांकerrupt to wake cpu from 'wait' */
#घोषणा GPIC_CFG_IDLEWAKE	(1 << 7)

/***********************************************************************/

/* Au1000 SDRAM memory controller रेजिस्टर offsets */
#घोषणा AU1000_MEM_SDMODE0		0x0000
#घोषणा AU1000_MEM_SDMODE1		0x0004
#घोषणा AU1000_MEM_SDMODE2		0x0008
#घोषणा AU1000_MEM_SDADDR0		0x000C
#घोषणा AU1000_MEM_SDADDR1		0x0010
#घोषणा AU1000_MEM_SDADDR2		0x0014
#घोषणा AU1000_MEM_SDREFCFG		0x0018
#घोषणा AU1000_MEM_SDPRECMD		0x001C
#घोषणा AU1000_MEM_SDAUTOREF		0x0020
#घोषणा AU1000_MEM_SDWRMD0		0x0024
#घोषणा AU1000_MEM_SDWRMD1		0x0028
#घोषणा AU1000_MEM_SDWRMD2		0x002C
#घोषणा AU1000_MEM_SDSLEEP		0x0030
#घोषणा AU1000_MEM_SDSMCKE		0x0034

/* MEM_SDMODE रेजिस्टर content definitions */
#घोषणा MEM_SDMODE_F		(1 << 22)
#घोषणा MEM_SDMODE_SR		(1 << 21)
#घोषणा MEM_SDMODE_BS		(1 << 20)
#घोषणा MEM_SDMODE_RS		(3 << 18)
#घोषणा MEM_SDMODE_CS		(7 << 15)
#घोषणा MEM_SDMODE_TRAS		(15 << 11)
#घोषणा MEM_SDMODE_TMRD		(3 << 9)
#घोषणा MEM_SDMODE_TWR		(3 << 7)
#घोषणा MEM_SDMODE_TRP		(3 << 5)
#घोषणा MEM_SDMODE_TRCD		(3 << 3)
#घोषणा MEM_SDMODE_TCL		(7 << 0)

#घोषणा MEM_SDMODE_BS_2Bank	(0 << 20)
#घोषणा MEM_SDMODE_BS_4Bank	(1 << 20)
#घोषणा MEM_SDMODE_RS_11Row	(0 << 18)
#घोषणा MEM_SDMODE_RS_12Row	(1 << 18)
#घोषणा MEM_SDMODE_RS_13Row	(2 << 18)
#घोषणा MEM_SDMODE_RS_N(N)	((N) << 18)
#घोषणा MEM_SDMODE_CS_7Col	(0 << 15)
#घोषणा MEM_SDMODE_CS_8Col	(1 << 15)
#घोषणा MEM_SDMODE_CS_9Col	(2 << 15)
#घोषणा MEM_SDMODE_CS_10Col	(3 << 15)
#घोषणा MEM_SDMODE_CS_11Col	(4 << 15)
#घोषणा MEM_SDMODE_CS_N(N)	((N) << 15)
#घोषणा MEM_SDMODE_TRAS_N(N)	((N) << 11)
#घोषणा MEM_SDMODE_TMRD_N(N)	((N) << 9)
#घोषणा MEM_SDMODE_TWR_N(N)	((N) << 7)
#घोषणा MEM_SDMODE_TRP_N(N)	((N) << 5)
#घोषणा MEM_SDMODE_TRCD_N(N)	((N) << 3)
#घोषणा MEM_SDMODE_TCL_N(N)	((N) << 0)

/* MEM_SDADDR रेजिस्टर contents definitions */
#घोषणा MEM_SDADDR_E		(1 << 20)
#घोषणा MEM_SDADDR_CSBA		(0x03FF << 10)
#घोषणा MEM_SDADDR_CSMASK	(0x03FF << 0)
#घोषणा MEM_SDADDR_CSBA_N(N)	((N) & (0x03FF << 22) >> 12)
#घोषणा MEM_SDADDR_CSMASK_N(N)	((N)&(0x03FF << 22) >> 22)

/* MEM_SDREFCFG रेजिस्टर content definitions */
#घोषणा MEM_SDREFCFG_TRC	(15 << 28)
#घोषणा MEM_SDREFCFG_TRPM	(3 << 26)
#घोषणा MEM_SDREFCFG_E		(1 << 25)
#घोषणा MEM_SDREFCFG_RE		(0x1ffffff << 0)
#घोषणा MEM_SDREFCFG_TRC_N(N)	((N) << MEM_SDREFCFG_TRC)
#घोषणा MEM_SDREFCFG_TRPM_N(N)	((N) << MEM_SDREFCFG_TRPM)
#घोषणा MEM_SDREFCFG_REF_N(N)	(N)

/* Au1550 SDRAM Register Offsets */
#घोषणा AU1550_MEM_SDMODE0		0x0800
#घोषणा AU1550_MEM_SDMODE1		0x0808
#घोषणा AU1550_MEM_SDMODE2		0x0810
#घोषणा AU1550_MEM_SDADDR0		0x0820
#घोषणा AU1550_MEM_SDADDR1		0x0828
#घोषणा AU1550_MEM_SDADDR2		0x0830
#घोषणा AU1550_MEM_SDCONFIGA		0x0840
#घोषणा AU1550_MEM_SDCONFIGB		0x0848
#घोषणा AU1550_MEM_SDSTAT		0x0850
#घोषणा AU1550_MEM_SDERRADDR		0x0858
#घोषणा AU1550_MEM_SDSTRIDE0		0x0860
#घोषणा AU1550_MEM_SDSTRIDE1		0x0868
#घोषणा AU1550_MEM_SDSTRIDE2		0x0870
#घोषणा AU1550_MEM_SDWRMD0		0x0880
#घोषणा AU1550_MEM_SDWRMD1		0x0888
#घोषणा AU1550_MEM_SDWRMD2		0x0890
#घोषणा AU1550_MEM_SDPRECMD		0x08C0
#घोषणा AU1550_MEM_SDAUTOREF		0x08C8
#घोषणा AU1550_MEM_SDSREF		0x08D0
#घोषणा AU1550_MEM_SDSLEEP		MEM_SDSREF

/* Static Bus Controller रेजिस्टर offsets */
#घोषणा AU1000_MEM_STCFG0	0x000
#घोषणा AU1000_MEM_STTIME0	0x004
#घोषणा AU1000_MEM_STADDR0	0x008
#घोषणा AU1000_MEM_STCFG1	0x010
#घोषणा AU1000_MEM_STTIME1	0x014
#घोषणा AU1000_MEM_STADDR1	0x018
#घोषणा AU1000_MEM_STCFG2	0x020
#घोषणा AU1000_MEM_STTIME2	0x024
#घोषणा AU1000_MEM_STADDR2	0x028
#घोषणा AU1000_MEM_STCFG3	0x030
#घोषणा AU1000_MEM_STTIME3	0x034
#घोषणा AU1000_MEM_STADDR3	0x038
#घोषणा AU1000_MEM_STNDCTL	0x100
#घोषणा AU1000_MEM_STSTAT	0x104

#घोषणा MEM_STन_अंकD_CMD		0x0
#घोषणा MEM_STन_अंकD_ADDR		0x4
#घोषणा MEM_STन_अंकD_DATA		0x20


/* Programmable Counters 0 and 1 */
#घोषणा AU1000_SYS_CNTRCTRL	0x14
#  define SYS_CNTRL_E1S		(1 << 23)
#  define SYS_CNTRL_T1S		(1 << 20)
#  define SYS_CNTRL_M21		(1 << 19)
#  define SYS_CNTRL_M11		(1 << 18)
#  define SYS_CNTRL_M01		(1 << 17)
#  define SYS_CNTRL_C1S		(1 << 16)
#  define SYS_CNTRL_BP		(1 << 14)
#  define SYS_CNTRL_EN1		(1 << 13)
#  define SYS_CNTRL_BT1		(1 << 12)
#  define SYS_CNTRL_EN0		(1 << 11)
#  define SYS_CNTRL_BT0		(1 << 10)
#  define SYS_CNTRL_E0		(1 << 8)
#  define SYS_CNTRL_E0S		(1 << 7)
#  define SYS_CNTRL_32S		(1 << 5)
#  define SYS_CNTRL_T0S		(1 << 4)
#  define SYS_CNTRL_M20		(1 << 3)
#  define SYS_CNTRL_M10		(1 << 2)
#  define SYS_CNTRL_M00		(1 << 1)
#  define SYS_CNTRL_C0S		(1 << 0)

/* Programmable Counter 0 Registers */
#घोषणा AU1000_SYS_TOYTRIM	0x00
#घोषणा AU1000_SYS_TOYWRITE	0x04
#घोषणा AU1000_SYS_TOYMATCH0	0x08
#घोषणा AU1000_SYS_TOYMATCH1	0x0c
#घोषणा AU1000_SYS_TOYMATCH2	0x10
#घोषणा AU1000_SYS_TOYREAD	0x40

/* Programmable Counter 1 Registers */
#घोषणा AU1000_SYS_RTCTRIM	0x44
#घोषणा AU1000_SYS_RTCWRITE	0x48
#घोषणा AU1000_SYS_RTCMATCH0	0x4c
#घोषणा AU1000_SYS_RTCMATCH1	0x50
#घोषणा AU1000_SYS_RTCMATCH2	0x54
#घोषणा AU1000_SYS_RTCREAD	0x58


/* GPIO */
#घोषणा AU1000_SYS_PINFUNC	0x2C
#  define SYS_PF_USB		(1 << 15)	/* 2nd USB device/host */
#  define SYS_PF_U3		(1 << 14)	/* GPIO23/U3TXD */
#  define SYS_PF_U2		(1 << 13)	/* GPIO22/U2TXD */
#  define SYS_PF_U1		(1 << 12)	/* GPIO21/U1TXD */
#  define SYS_PF_SRC		(1 << 11)	/* GPIO6/SROMCKE */
#  define SYS_PF_CK5		(1 << 10)	/* GPIO3/CLK5 */
#  define SYS_PF_CK4		(1 << 9)	/* GPIO2/CLK4 */
#  define SYS_PF_IRF		(1 << 8)	/* GPIO15/IRFIRSEL */
#  define SYS_PF_UR3		(1 << 7)	/* GPIO[14:9]/UART3 */
#  define SYS_PF_I2D		(1 << 6)	/* GPIO8/I2SDI */
#  define SYS_PF_I2S		(1 << 5)	/* I2S/GPIO[29:31] */
#  define SYS_PF_NI2		(1 << 4)	/* NI2/GPIO[24:28] */
#  define SYS_PF_U0		(1 << 3)	/* U0TXD/GPIO20 */
#  define SYS_PF_RD		(1 << 2)	/* IRTXD/GPIO19 */
#  define SYS_PF_A97		(1 << 1)	/* AC97/SSL1 */
#  define SYS_PF_S0		(1 << 0)	/* SSI_0/GPIO[16:18] */

/* Au1100 only */
#  define SYS_PF_PC		(1 << 18)	/* PCMCIA/GPIO[207:204] */
#  define SYS_PF_LCD		(1 << 17)	/* बाह्य lcd/GPIO[203:200] */
#  define SYS_PF_CS		(1 << 16)	/* EXTCLK0/32KHz to gpio2 */
#  define SYS_PF_EX0		(1 << 9)	/* GPIO2/घड़ी */

/* Au1550 only.	 Redefines lots of pins */
#  define SYS_PF_PSC2_MASK	(7 << 17)
#  define SYS_PF_PSC2_AC97	0
#  define SYS_PF_PSC2_SPI	0
#  define SYS_PF_PSC2_I2S	(1 << 17)
#  define SYS_PF_PSC2_SMBUS	(3 << 17)
#  define SYS_PF_PSC2_GPIO	(7 << 17)
#  define SYS_PF_PSC3_MASK	(7 << 20)
#  define SYS_PF_PSC3_AC97	0
#  define SYS_PF_PSC3_SPI	0
#  define SYS_PF_PSC3_I2S	(1 << 20)
#  define SYS_PF_PSC3_SMBUS	(3 << 20)
#  define SYS_PF_PSC3_GPIO	(7 << 20)
#  define SYS_PF_PSC1_S1	(1 << 1)
#  define SYS_PF_MUST_BE_SET	((1 << 5) | (1 << 2))

/* Au1200 only */
#घोषणा SYS_PINFUNC_DMA		(1 << 31)
#घोषणा SYS_PINFUNC_S0A		(1 << 30)
#घोषणा SYS_PINFUNC_S1A		(1 << 29)
#घोषणा SYS_PINFUNC_LP0		(1 << 28)
#घोषणा SYS_PINFUNC_LP1		(1 << 27)
#घोषणा SYS_PINFUNC_LD16	(1 << 26)
#घोषणा SYS_PINFUNC_LD8		(1 << 25)
#घोषणा SYS_PINFUNC_LD1		(1 << 24)
#घोषणा SYS_PINFUNC_LD0		(1 << 23)
#घोषणा SYS_PINFUNC_P1A		(3 << 21)
#घोषणा SYS_PINFUNC_P1B		(1 << 20)
#घोषणा SYS_PINFUNC_FS3		(1 << 19)
#घोषणा SYS_PINFUNC_P0A		(3 << 17)
#घोषणा SYS_PINFUNC_CS		(1 << 16)
#घोषणा SYS_PINFUNC_CIM		(1 << 15)
#घोषणा SYS_PINFUNC_P1C		(1 << 14)
#घोषणा SYS_PINFUNC_U1T		(1 << 12)
#घोषणा SYS_PINFUNC_U1R		(1 << 11)
#घोषणा SYS_PINFUNC_EX1		(1 << 10)
#घोषणा SYS_PINFUNC_EX0		(1 << 9)
#घोषणा SYS_PINFUNC_U0R		(1 << 8)
#घोषणा SYS_PINFUNC_MC		(1 << 7)
#घोषणा SYS_PINFUNC_S0B		(1 << 6)
#घोषणा SYS_PINFUNC_S0C		(1 << 5)
#घोषणा SYS_PINFUNC_P0B		(1 << 4)
#घोषणा SYS_PINFUNC_U0T		(1 << 3)
#घोषणा SYS_PINFUNC_S1B		(1 << 2)

/* Power Management */
#घोषणा AU1000_SYS_SCRATCH0	0x18
#घोषणा AU1000_SYS_SCRATCH1	0x1c
#घोषणा AU1000_SYS_WAKEMSK	0x34
#घोषणा AU1000_SYS_ENDIAN	0x38
#घोषणा AU1000_SYS_POWERCTRL	0x3c
#घोषणा AU1000_SYS_WAKESRC	0x5c
#घोषणा AU1000_SYS_SLPPWR	0x78
#घोषणा AU1000_SYS_SLEEP	0x7c

#घोषणा SYS_WAKEMSK_D2		(1 << 9)
#घोषणा SYS_WAKEMSK_M2		(1 << 8)
#घोषणा SYS_WAKEMSK_GPIO(x)	(1 << (x))

/* Clock Controller */
#घोषणा AU1000_SYS_FREQCTRL0	0x20
#घोषणा AU1000_SYS_FREQCTRL1	0x24
#घोषणा AU1000_SYS_CLKSRC	0x28
#घोषणा AU1000_SYS_CPUPLL	0x60
#घोषणा AU1000_SYS_AUXPLL	0x64
#घोषणा AU1300_SYS_AUXPLL2	0x68


/**********************************************************************/


/* The PCI chip selects are outside the 32bit space, and since we can't
 * just program the 36bit addresses पूर्णांकo BARs, we have to take a chunk
 * out of the 32bit space and reserve it क्रम PCI.  When these addresses
 * are ioremap()ed, they'll be fixed up to the real 36bit address beक्रमe
 * being passed to the real ioremap function.
 */
#घोषणा ALCHEMY_PCI_MEMWIN_START	(AU1500_PCI_MEM_PHYS_ADDR >> 4)
#घोषणा ALCHEMY_PCI_MEMWIN_END		(ALCHEMY_PCI_MEMWIN_START + 0x0FFFFFFF)

/* क्रम PCI IO it's simpler because we get to करो the ioremap ourselves and then
 * adjust the device's resources.
 */
#घोषणा ALCHEMY_PCI_IOWIN_START		0x00001000
#घोषणा ALCHEMY_PCI_IOWIN_END		0x0000FFFF

#अगर_घोषित CONFIG_PCI

#घोषणा IOPORT_RESOURCE_START	0x00001000	/* skip legacy probing */
#घोषणा IOPORT_RESOURCE_END	0xffffffff
#घोषणा IOMEM_RESOURCE_START	0x10000000
#घोषणा IOMEM_RESOURCE_END	0xfffffffffULL

#अन्यथा

/* Don't allow any legacy ports probing */
#घोषणा IOPORT_RESOURCE_START	0x10000000
#घोषणा IOPORT_RESOURCE_END	0xffffffff
#घोषणा IOMEM_RESOURCE_START	0x10000000
#घोषणा IOMEM_RESOURCE_END	0xfffffffffULL

#पूर्ण_अगर

/* PCI controller block रेजिस्टर offsets */
#घोषणा PCI_REG_CMEM		0x0000
#घोषणा PCI_REG_CONFIG		0x0004
#घोषणा PCI_REG_B2BMASK_CCH	0x0008
#घोषणा PCI_REG_B2BBASE0_VID	0x000C
#घोषणा PCI_REG_B2BBASE1_SID	0x0010
#घोषणा PCI_REG_MWMASK_DEV	0x0014
#घोषणा PCI_REG_MWBASE_REV_CCL	0x0018
#घोषणा PCI_REG_ERR_ADDR	0x001C
#घोषणा PCI_REG_SPEC_INTACK	0x0020
#घोषणा PCI_REG_ID		0x0100
#घोषणा PCI_REG_STATCMD		0x0104
#घोषणा PCI_REG_CLASSREV	0x0108
#घोषणा PCI_REG_PARAM		0x010C
#घोषणा PCI_REG_MBAR		0x0110
#घोषणा PCI_REG_TIMEOUT		0x0140

/* PCI controller block रेजिस्टर bits */
#घोषणा PCI_CMEM_E		(1 << 28)	/* enable cacheable memory */
#घोषणा PCI_CMEM_CMBASE(x)	(((x) & 0x3fff) << 14)
#घोषणा PCI_CMEM_CMMASK(x)	((x) & 0x3fff)
#घोषणा PCI_CONFIG_ERD		(1 << 27) /* pci error during R/W */
#घोषणा PCI_CONFIG_ET		(1 << 26) /* error in target mode */
#घोषणा PCI_CONFIG_EF		(1 << 25) /* fatal error */
#घोषणा PCI_CONFIG_EP		(1 << 24) /* parity error */
#घोषणा PCI_CONFIG_EM		(1 << 23) /* multiple errors */
#घोषणा PCI_CONFIG_BM		(1 << 22) /* bad master error */
#घोषणा PCI_CONFIG_PD		(1 << 20) /* PCI Disable */
#घोषणा PCI_CONFIG_BME		(1 << 19) /* Byte Mask Enable क्रम पढ़ोs */
#घोषणा PCI_CONFIG_NC		(1 << 16) /* mark mem access non-coherent */
#घोषणा PCI_CONFIG_IA		(1 << 15) /* INTA# enabled (target mode) */
#घोषणा PCI_CONFIG_IP		(1 << 13) /* पूर्णांक on PCI_PERR# */
#घोषणा PCI_CONFIG_IS		(1 << 12) /* पूर्णांक on PCI_SERR# */
#घोषणा PCI_CONFIG_IMM		(1 << 11) /* पूर्णांक on master पात */
#घोषणा PCI_CONFIG_ITM		(1 << 10) /* पूर्णांक on target पात (as master) */
#घोषणा PCI_CONFIG_ITT		(1 << 9)  /* पूर्णांक on target पात (as target) */
#घोषणा PCI_CONFIG_IPB		(1 << 8)  /* पूर्णांक on PERR# in bus master acc */
#घोषणा PCI_CONFIG_SIC_NO	(0 << 6)  /* no byte mask changes */
#घोषणा PCI_CONFIG_SIC_BA_ADR	(1 << 6)  /* on byte/hw acc, invert adr bits */
#घोषणा PCI_CONFIG_SIC_HWA_DAT	(2 << 6)  /* on halfword acc, swap data */
#घोषणा PCI_CONFIG_SIC_ALL	(3 << 6)  /* swap data bytes on all accesses */
#घोषणा PCI_CONFIG_ST		(1 << 5)  /* swap data by target transactions */
#घोषणा PCI_CONFIG_SM		(1 << 4)  /* swap data from PCI ctl */
#घोषणा PCI_CONFIG_AEN		(1 << 3)  /* enable पूर्णांकernal arbiter */
#घोषणा PCI_CONFIG_R2H		(1 << 2)  /* REQ2# to hi-prio arbiter */
#घोषणा PCI_CONFIG_R1H		(1 << 1)  /* REQ1# to hi-prio arbiter */
#घोषणा PCI_CONFIG_CH		(1 << 0)  /* PCI ctl to hi-prio arbiter */
#घोषणा PCI_B2BMASK_B2BMASK(x)	(((x) & 0xffff) << 16)
#घोषणा PCI_B2BMASK_CCH(x)	((x) & 0xffff) /* 16 upper bits of class code */
#घोषणा PCI_B2BBASE0_VID_B0(x)	(((x) & 0xffff) << 16)
#घोषणा PCI_B2BBASE0_VID_SV(x)	((x) & 0xffff)
#घोषणा PCI_B2BBASE1_SID_B1(x)	(((x) & 0xffff) << 16)
#घोषणा PCI_B2BBASE1_SID_SI(x)	((x) & 0xffff)
#घोषणा PCI_MWMASKDEV_MWMASK(x) (((x) & 0xffff) << 16)
#घोषणा PCI_MWMASKDEV_DEVID(x)	((x) & 0xffff)
#घोषणा PCI_MWBASEREVCCL_BASE(x) (((x) & 0xffff) << 16)
#घोषणा PCI_MWBASEREVCCL_REV(x)	 (((x) & 0xff) << 8)
#घोषणा PCI_MWBASEREVCCL_CCL(x)	 ((x) & 0xff)
#घोषणा PCI_ID_DID(x)		(((x) & 0xffff) << 16)
#घोषणा PCI_ID_VID(x)		((x) & 0xffff)
#घोषणा PCI_STATCMD_STATUS(x)	(((x) & 0xffff) << 16)
#घोषणा PCI_STATCMD_CMD(x)	((x) & 0xffff)
#घोषणा PCI_CLASSREV_CLASS(x)	(((x) & 0x00ffffff) << 8)
#घोषणा PCI_CLASSREV_REV(x)	((x) & 0xff)
#घोषणा PCI_PARAM_BIST(x)	(((x) & 0xff) << 24)
#घोषणा PCI_PARAM_HT(x)		(((x) & 0xff) << 16)
#घोषणा PCI_PARAM_LT(x)		(((x) & 0xff) << 8)
#घोषणा PCI_PARAM_CLS(x)	((x) & 0xff)
#घोषणा PCI_TIMEOUT_RETRIES(x)	(((x) & 0xff) << 8)	/* max retries */
#घोषणा PCI_TIMEOUT_TO(x)	((x) & 0xff)	/* target पढ़ोy समयout */


/**********************************************************************/


#अगर_अघोषित _LANGUAGE_ASSEMBLY

#समावेश <linux/delay.h>
#समावेश <linux/types.h>

#समावेश <linux/पन.स>
#समावेश <linux/irq.h>

#समावेश <यंत्र/cpu.h>

/* helpers to access the SYS_* रेजिस्टरs */
अटल अंतरभूत अचिन्हित दीर्घ alchemy_rdsys(पूर्णांक regofs)
अणु
	व्योम __iomem *b = (व्योम __iomem *)KSEG1ADDR(AU1000_SYS_PHYS_ADDR);

	वापस __raw_पढ़ोl(b + regofs);
पूर्ण

अटल अंतरभूत व्योम alchemy_wrsys(अचिन्हित दीर्घ v, पूर्णांक regofs)
अणु
	व्योम __iomem *b = (व्योम __iomem *)KSEG1ADDR(AU1000_SYS_PHYS_ADDR);

	__raw_ग_लिखोl(v, b + regofs);
	wmb(); /* drain ग_लिखोbuffer */
पूर्ण

/* helpers to access अटल memctrl रेजिस्टरs */
अटल अंतरभूत अचिन्हित दीर्घ alchemy_rdsmem(पूर्णांक regofs)
अणु
	व्योम __iomem *b = (व्योम __iomem *)KSEG1ADDR(AU1000_STATIC_MEM_PHYS_ADDR);

	वापस __raw_पढ़ोl(b + regofs);
पूर्ण

अटल अंतरभूत व्योम alchemy_wrsmem(अचिन्हित दीर्घ v, पूर्णांक regofs)
अणु
	व्योम __iomem *b = (व्योम __iomem *)KSEG1ADDR(AU1000_STATIC_MEM_PHYS_ADDR);

	__raw_ग_लिखोl(v, b + regofs);
	wmb(); /* drain ग_लिखोbuffer */
पूर्ण

/* Early Au1000 have a ग_लिखो-only SYS_CPUPLL रेजिस्टर. */
अटल अंतरभूत पूर्णांक au1xxx_cpu_has_pll_wo(व्योम)
अणु
	चयन (पढ़ो_c0_prid()) अणु
	हाल 0x00030100:	/* Au1000 DA */
	हाल 0x00030201:	/* Au1000 HA */
	हाल 0x00030202:	/* Au1000 HB */
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

/* करोes CPU need CONFIG[OD] set to fix tons of errata? */
अटल अंतरभूत पूर्णांक au1xxx_cpu_needs_config_od(व्योम)
अणु
	/*
	 * c0_config.od (bit 19) was ग_लिखो only (and पढ़ो as 0) on the
	 * early revisions of Alchemy SOCs.  It disables the bus trans-
	 * action overlapping and needs to be set to fix various errata.
	 */
	चयन (पढ़ो_c0_prid()) अणु
	हाल 0x00030100: /* Au1000 DA */
	हाल 0x00030201: /* Au1000 HA */
	हाल 0x00030202: /* Au1000 HB */
	हाल 0x01030200: /* Au1500 AB */
	/*
	 * Au1100/Au1200 errata actually keep silence about this bit,
	 * so we set it just in हाल क्रम those revisions that require
	 * it to be set according to the (now gone) cpu_table.
	 */
	हाल 0x02030200: /* Au1100 AB */
	हाल 0x02030201: /* Au1100 BA */
	हाल 0x02030202: /* Au1100 BC */
	हाल 0x04030201: /* Au1200 AC */
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

#घोषणा ALCHEMY_CPU_UNKNOWN	-1
#घोषणा ALCHEMY_CPU_AU1000	0
#घोषणा ALCHEMY_CPU_AU1500	1
#घोषणा ALCHEMY_CPU_AU1100	2
#घोषणा ALCHEMY_CPU_AU1550	3
#घोषणा ALCHEMY_CPU_AU1200	4
#घोषणा ALCHEMY_CPU_AU1300	5

अटल अंतरभूत पूर्णांक alchemy_get_cputype(व्योम)
अणु
	चयन (पढ़ो_c0_prid() & (PRID_OPT_MASK | PRID_COMP_MASK)) अणु
	हाल 0x00030000:
		वापस ALCHEMY_CPU_AU1000;
		अवरोध;
	हाल 0x01030000:
		वापस ALCHEMY_CPU_AU1500;
		अवरोध;
	हाल 0x02030000:
		वापस ALCHEMY_CPU_AU1100;
		अवरोध;
	हाल 0x03030000:
		वापस ALCHEMY_CPU_AU1550;
		अवरोध;
	हाल 0x04030000:
	हाल 0x05030000:
		वापस ALCHEMY_CPU_AU1200;
		अवरोध;
	हाल 0x800c0000:
		वापस ALCHEMY_CPU_AU1300;
		अवरोध;
	पूर्ण

	वापस ALCHEMY_CPU_UNKNOWN;
पूर्ण

/* वापस number of uarts on a given cputype */
अटल अंतरभूत पूर्णांक alchemy_get_uarts(पूर्णांक type)
अणु
	चयन (type) अणु
	हाल ALCHEMY_CPU_AU1000:
	हाल ALCHEMY_CPU_AU1300:
		वापस 4;
	हाल ALCHEMY_CPU_AU1500:
	हाल ALCHEMY_CPU_AU1200:
		वापस 2;
	हाल ALCHEMY_CPU_AU1100:
	हाल ALCHEMY_CPU_AU1550:
		वापस 3;
	पूर्ण
	वापस 0;
पूर्ण

/* enable an UART block अगर it isn't alपढ़ोy */
अटल अंतरभूत व्योम alchemy_uart_enable(u32 uart_phys)
अणु
	व्योम __iomem *addr = (व्योम __iomem *)KSEG1ADDR(uart_phys);

	/* reset, enable घड़ी, deनिश्चित reset */
	अगर ((__raw_पढ़ोl(addr + 0x100) & 3) != 3) अणु
		__raw_ग_लिखोl(0, addr + 0x100);
		wmb(); /* drain ग_लिखोbuffer */
		__raw_ग_लिखोl(1, addr + 0x100);
		wmb(); /* drain ग_लिखोbuffer */
	पूर्ण
	__raw_ग_लिखोl(3, addr + 0x100);
	wmb(); /* drain ग_लिखोbuffer */
पूर्ण

अटल अंतरभूत व्योम alchemy_uart_disable(u32 uart_phys)
अणु
	व्योम __iomem *addr = (व्योम __iomem *)KSEG1ADDR(uart_phys);

	__raw_ग_लिखोl(0, addr + 0x100);	/* UART_MOD_CNTRL */
	wmb(); /* drain ग_लिखोbuffer */
पूर्ण

अटल अंतरभूत व्योम alchemy_uart_अक्षर_दो(u32 uart_phys, u8 c)
अणु
	व्योम __iomem *base = (व्योम __iomem *)KSEG1ADDR(uart_phys);
	पूर्णांक समयout, i;

	/* check LSR TX_EMPTY bit */
	समयout = 0xffffff;
	करो अणु
		अगर (__raw_पढ़ोl(base + 0x1c) & 0x20)
			अवरोध;
		/* slow करोwn */
		क्रम (i = 10000; i; i--)
			यंत्र अस्थिर ("nop");
	पूर्ण जबतक (--समयout);

	__raw_ग_लिखोl(c, base + 0x04);	/* tx */
	wmb(); /* drain ग_लिखोbuffer */
पूर्ण

/* वापस number of ethernet MACs on a given cputype */
अटल अंतरभूत पूर्णांक alchemy_get_macs(पूर्णांक type)
अणु
	चयन (type) अणु
	हाल ALCHEMY_CPU_AU1000:
	हाल ALCHEMY_CPU_AU1500:
	हाल ALCHEMY_CPU_AU1550:
		वापस 2;
	हाल ALCHEMY_CPU_AU1100:
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

/* PM: arch/mips/alchemy/common/sleeper.S, घातer.c, irq.c */
व्योम alchemy_sleep_au1000(व्योम);
व्योम alchemy_sleep_au1550(व्योम);
व्योम alchemy_sleep_au1300(व्योम);
व्योम au_sleep(व्योम);

/* USB: arch/mips/alchemy/common/usb.c */
क्रमागत alchemy_usb_block अणु
	ALCHEMY_USB_OHCI0,
	ALCHEMY_USB_UDC0,
	ALCHEMY_USB_EHCI0,
	ALCHEMY_USB_OTG0,
	ALCHEMY_USB_OHCI1,
पूर्ण;
पूर्णांक alchemy_usb_control(पूर्णांक block, पूर्णांक enable);

/* PCI controller platक्रमm data */
काष्ठा alchemy_pci_platdata अणु
	पूर्णांक (*board_map_irq)(स्थिर काष्ठा pci_dev *d, u8 slot, u8 pin);
	पूर्णांक (*board_pci_idsel)(अचिन्हित पूर्णांक devsel, पूर्णांक निश्चित);
	/* bits to set/clear in PCI_CONFIG रेजिस्टर */
	अचिन्हित दीर्घ pci_cfg_set;
	अचिन्हित दीर्घ pci_cfg_clr;
पूर्ण;

/* The IrDA peripheral has an IRFIRSEL pin, but on the DB/PB boards it's
 * not used to select FIR/SIR mode on the transceiver but as a GPIO.
 * Instead a CPLD has to be told about the mode.  The driver calls the
 * set_phy_mode() function in addition to driving the IRFIRSEL pin.
 */
#घोषणा AU1000_IRDA_PHY_MODE_OFF	0
#घोषणा AU1000_IRDA_PHY_MODE_SIR	1
#घोषणा AU1000_IRDA_PHY_MODE_FIR	2

काष्ठा au1k_irda_platक्रमm_data अणु
	व्योम (*set_phy_mode)(पूर्णांक mode);
पूर्ण;


/* Multअगरunction pins: Each of these pins can either be asचिन्हित to the
 * GPIO controller or a on-chip peripheral.
 * Call "au1300_pinfunc_to_dev()" or "au1300_pinfunc_to_gpio()" to
 * assign one of these to either the GPIO controller or the device.
 */
क्रमागत au1300_multअगरunc_pins अणु
	/* wake-from-str pins 0-3 */
	AU1300_PIN_WAKE0 = 0, AU1300_PIN_WAKE1, AU1300_PIN_WAKE2,
	AU1300_PIN_WAKE3,
	/* बाह्यal घड़ी sources क्रम PSCs: 4-5 */
	AU1300_PIN_EXTCLK0, AU1300_PIN_EXTCLK1,
	/* 8bit MMC पूर्णांकerface on SD0: 6-9 */
	AU1300_PIN_SD0DAT4, AU1300_PIN_SD0DAT5, AU1300_PIN_SD0DAT6,
	AU1300_PIN_SD0DAT7,
	/* aux clk input क्रम freqgen 3: 10 */
	AU1300_PIN_FG3AUX,
	/* UART1 pins: 11-18 */
	AU1300_PIN_U1RI, AU1300_PIN_U1DCD, AU1300_PIN_U1DSR,
	AU1300_PIN_U1CTS, AU1300_PIN_U1RTS, AU1300_PIN_U1DTR,
	AU1300_PIN_U1RX, AU1300_PIN_U1TX,
	/* UART0 pins: 19-24 */
	AU1300_PIN_U0RI, AU1300_PIN_U0DCD, AU1300_PIN_U0DSR,
	AU1300_PIN_U0CTS, AU1300_PIN_U0RTS, AU1300_PIN_U0DTR,
	/* UART2: 25-26 */
	AU1300_PIN_U2RX, AU1300_PIN_U2TX,
	/* UART3: 27-28 */
	AU1300_PIN_U3RX, AU1300_PIN_U3TX,
	/* LCD controller PWMs, ext pixघड़ी: 29-31 */
	AU1300_PIN_LCDPWM0, AU1300_PIN_LCDPWM1, AU1300_PIN_LCDCLKIN,
	/* SD1 पूर्णांकerface: 32-37 */
	AU1300_PIN_SD1DAT0, AU1300_PIN_SD1DAT1, AU1300_PIN_SD1DAT2,
	AU1300_PIN_SD1DAT3, AU1300_PIN_SD1CMD, AU1300_PIN_SD1CLK,
	/* SD2 पूर्णांकerface: 38-43 */
	AU1300_PIN_SD2DAT0, AU1300_PIN_SD2DAT1, AU1300_PIN_SD2DAT2,
	AU1300_PIN_SD2DAT3, AU1300_PIN_SD2CMD, AU1300_PIN_SD2CLK,
	/* PSC0/1 घड़ीs: 44-45 */
	AU1300_PIN_PSC0CLK, AU1300_PIN_PSC1CLK,
	/* PSCs: 46-49/50-53/54-57/58-61 */
	AU1300_PIN_PSC0SYNC0, AU1300_PIN_PSC0SYNC1, AU1300_PIN_PSC0D0,
	AU1300_PIN_PSC0D1,
	AU1300_PIN_PSC1SYNC0, AU1300_PIN_PSC1SYNC1, AU1300_PIN_PSC1D0,
	AU1300_PIN_PSC1D1,
	AU1300_PIN_PSC2SYNC0, AU1300_PIN_PSC2SYNC1, AU1300_PIN_PSC2D0,
	AU1300_PIN_PSC2D1,
	AU1300_PIN_PSC3SYNC0, AU1300_PIN_PSC3SYNC1, AU1300_PIN_PSC3D0,
	AU1300_PIN_PSC3D1,
	/* PCMCIA पूर्णांकerface: 62-70 */
	AU1300_PIN_PCE2, AU1300_PIN_PCE1, AU1300_PIN_PIOS16,
	AU1300_PIN_PIOR, AU1300_PIN_PWE, AU1300_PIN_PWAIT,
	AU1300_PIN_PREG, AU1300_PIN_POE, AU1300_PIN_PIOW,
	/* camera पूर्णांकerface H/V sync inमाला_दो: 71-72 */
	AU1300_PIN_CIMLS, AU1300_PIN_CIMFS,
	/* PSC2/3 घड़ीs: 73-74 */
	AU1300_PIN_PSC2CLK, AU1300_PIN_PSC3CLK,
पूर्ण;

/* GPIC (Au1300) pin management: arch/mips/alchemy/common/gpioपूर्णांक.c */
बाह्य व्योम au1300_pinfunc_to_gpio(क्रमागत au1300_multअगरunc_pins gpio);
बाह्य व्योम au1300_pinfunc_to_dev(क्रमागत au1300_multअगरunc_pins gpio);
बाह्य व्योम au1300_set_irq_priority(अचिन्हित पूर्णांक irq, पूर्णांक p);
बाह्य व्योम au1300_set_dbdma_gpio(पूर्णांक dchan, अचिन्हित पूर्णांक gpio);

/* Au1300 allows to disconnect certain blocks from पूर्णांकernal घातer supply */
क्रमागत au1300_vss_block अणु
	AU1300_VSS_MPE = 0,
	AU1300_VSS_BSA,
	AU1300_VSS_GPE,
	AU1300_VSS_MGP,
पूर्ण;

बाह्य व्योम au1300_vss_block_control(पूर्णांक block, पूर्णांक enable);

क्रमागत soc_au1000_पूर्णांकs अणु
	AU1000_FIRST_INT	= AU1000_INTC0_INT_BASE,
	AU1000_UART0_INT	= AU1000_FIRST_INT,
	AU1000_UART1_INT,
	AU1000_UART2_INT,
	AU1000_UART3_INT,
	AU1000_SSI0_INT,
	AU1000_SSI1_INT,
	AU1000_DMA_INT_BASE,

	AU1000_TOY_INT		= AU1000_FIRST_INT + 14,
	AU1000_TOY_MATCH0_INT,
	AU1000_TOY_MATCH1_INT,
	AU1000_TOY_MATCH2_INT,
	AU1000_RTC_INT,
	AU1000_RTC_MATCH0_INT,
	AU1000_RTC_MATCH1_INT,
	AU1000_RTC_MATCH2_INT,
	AU1000_IRDA_TX_INT,
	AU1000_IRDA_RX_INT,
	AU1000_USB_DEV_REQ_INT,
	AU1000_USB_DEV_SUS_INT,
	AU1000_USB_HOST_INT,
	AU1000_ACSYNC_INT,
	AU1000_MAC0_DMA_INT,
	AU1000_MAC1_DMA_INT,
	AU1000_I2S_UO_INT,
	AU1000_AC97C_INT,
	AU1000_GPIO0_INT,
	AU1000_GPIO1_INT,
	AU1000_GPIO2_INT,
	AU1000_GPIO3_INT,
	AU1000_GPIO4_INT,
	AU1000_GPIO5_INT,
	AU1000_GPIO6_INT,
	AU1000_GPIO7_INT,
	AU1000_GPIO8_INT,
	AU1000_GPIO9_INT,
	AU1000_GPIO10_INT,
	AU1000_GPIO11_INT,
	AU1000_GPIO12_INT,
	AU1000_GPIO13_INT,
	AU1000_GPIO14_INT,
	AU1000_GPIO15_INT,
	AU1000_GPIO16_INT,
	AU1000_GPIO17_INT,
	AU1000_GPIO18_INT,
	AU1000_GPIO19_INT,
	AU1000_GPIO20_INT,
	AU1000_GPIO21_INT,
	AU1000_GPIO22_INT,
	AU1000_GPIO23_INT,
	AU1000_GPIO24_INT,
	AU1000_GPIO25_INT,
	AU1000_GPIO26_INT,
	AU1000_GPIO27_INT,
	AU1000_GPIO28_INT,
	AU1000_GPIO29_INT,
	AU1000_GPIO30_INT,
	AU1000_GPIO31_INT,
पूर्ण;

क्रमागत soc_au1100_पूर्णांकs अणु
	AU1100_FIRST_INT	= AU1000_INTC0_INT_BASE,
	AU1100_UART0_INT	= AU1100_FIRST_INT,
	AU1100_UART1_INT,
	AU1100_SD_INT,
	AU1100_UART3_INT,
	AU1100_SSI0_INT,
	AU1100_SSI1_INT,
	AU1100_DMA_INT_BASE,

	AU1100_TOY_INT		= AU1100_FIRST_INT + 14,
	AU1100_TOY_MATCH0_INT,
	AU1100_TOY_MATCH1_INT,
	AU1100_TOY_MATCH2_INT,
	AU1100_RTC_INT,
	AU1100_RTC_MATCH0_INT,
	AU1100_RTC_MATCH1_INT,
	AU1100_RTC_MATCH2_INT,
	AU1100_IRDA_TX_INT,
	AU1100_IRDA_RX_INT,
	AU1100_USB_DEV_REQ_INT,
	AU1100_USB_DEV_SUS_INT,
	AU1100_USB_HOST_INT,
	AU1100_ACSYNC_INT,
	AU1100_MAC0_DMA_INT,
	AU1100_GPIO208_215_INT,
	AU1100_LCD_INT,
	AU1100_AC97C_INT,
	AU1100_GPIO0_INT,
	AU1100_GPIO1_INT,
	AU1100_GPIO2_INT,
	AU1100_GPIO3_INT,
	AU1100_GPIO4_INT,
	AU1100_GPIO5_INT,
	AU1100_GPIO6_INT,
	AU1100_GPIO7_INT,
	AU1100_GPIO8_INT,
	AU1100_GPIO9_INT,
	AU1100_GPIO10_INT,
	AU1100_GPIO11_INT,
	AU1100_GPIO12_INT,
	AU1100_GPIO13_INT,
	AU1100_GPIO14_INT,
	AU1100_GPIO15_INT,
	AU1100_GPIO16_INT,
	AU1100_GPIO17_INT,
	AU1100_GPIO18_INT,
	AU1100_GPIO19_INT,
	AU1100_GPIO20_INT,
	AU1100_GPIO21_INT,
	AU1100_GPIO22_INT,
	AU1100_GPIO23_INT,
	AU1100_GPIO24_INT,
	AU1100_GPIO25_INT,
	AU1100_GPIO26_INT,
	AU1100_GPIO27_INT,
	AU1100_GPIO28_INT,
	AU1100_GPIO29_INT,
	AU1100_GPIO30_INT,
	AU1100_GPIO31_INT,
पूर्ण;

क्रमागत soc_au1500_पूर्णांकs अणु
	AU1500_FIRST_INT	= AU1000_INTC0_INT_BASE,
	AU1500_UART0_INT	= AU1500_FIRST_INT,
	AU1500_PCI_INTA,
	AU1500_PCI_INTB,
	AU1500_UART3_INT,
	AU1500_PCI_INTC,
	AU1500_PCI_INTD,
	AU1500_DMA_INT_BASE,

	AU1500_TOY_INT		= AU1500_FIRST_INT + 14,
	AU1500_TOY_MATCH0_INT,
	AU1500_TOY_MATCH1_INT,
	AU1500_TOY_MATCH2_INT,
	AU1500_RTC_INT,
	AU1500_RTC_MATCH0_INT,
	AU1500_RTC_MATCH1_INT,
	AU1500_RTC_MATCH2_INT,
	AU1500_PCI_ERR_INT,
	AU1500_RESERVED_INT,
	AU1500_USB_DEV_REQ_INT,
	AU1500_USB_DEV_SUS_INT,
	AU1500_USB_HOST_INT,
	AU1500_ACSYNC_INT,
	AU1500_MAC0_DMA_INT,
	AU1500_MAC1_DMA_INT,
	AU1500_AC97C_INT	= AU1500_FIRST_INT + 31,
	AU1500_GPIO0_INT,
	AU1500_GPIO1_INT,
	AU1500_GPIO2_INT,
	AU1500_GPIO3_INT,
	AU1500_GPIO4_INT,
	AU1500_GPIO5_INT,
	AU1500_GPIO6_INT,
	AU1500_GPIO7_INT,
	AU1500_GPIO8_INT,
	AU1500_GPIO9_INT,
	AU1500_GPIO10_INT,
	AU1500_GPIO11_INT,
	AU1500_GPIO12_INT,
	AU1500_GPIO13_INT,
	AU1500_GPIO14_INT,
	AU1500_GPIO15_INT,
	AU1500_GPIO200_INT,
	AU1500_GPIO201_INT,
	AU1500_GPIO202_INT,
	AU1500_GPIO203_INT,
	AU1500_GPIO20_INT,
	AU1500_GPIO204_INT,
	AU1500_GPIO205_INT,
	AU1500_GPIO23_INT,
	AU1500_GPIO24_INT,
	AU1500_GPIO25_INT,
	AU1500_GPIO26_INT,
	AU1500_GPIO27_INT,
	AU1500_GPIO28_INT,
	AU1500_GPIO206_INT,
	AU1500_GPIO207_INT,
	AU1500_GPIO208_215_INT,
पूर्ण;

क्रमागत soc_au1550_पूर्णांकs अणु
	AU1550_FIRST_INT	= AU1000_INTC0_INT_BASE,
	AU1550_UART0_INT	= AU1550_FIRST_INT,
	AU1550_PCI_INTA,
	AU1550_PCI_INTB,
	AU1550_DDMA_INT,
	AU1550_CRYPTO_INT,
	AU1550_PCI_INTC,
	AU1550_PCI_INTD,
	AU1550_PCI_RST_INT,
	AU1550_UART1_INT,
	AU1550_UART3_INT,
	AU1550_PSC0_INT,
	AU1550_PSC1_INT,
	AU1550_PSC2_INT,
	AU1550_PSC3_INT,
	AU1550_TOY_INT,
	AU1550_TOY_MATCH0_INT,
	AU1550_TOY_MATCH1_INT,
	AU1550_TOY_MATCH2_INT,
	AU1550_RTC_INT,
	AU1550_RTC_MATCH0_INT,
	AU1550_RTC_MATCH1_INT,
	AU1550_RTC_MATCH2_INT,

	AU1550_न_अंकD_INT		= AU1550_FIRST_INT + 23,
	AU1550_USB_DEV_REQ_INT,
	AU1550_USB_DEV_SUS_INT,
	AU1550_USB_HOST_INT,
	AU1550_MAC0_DMA_INT,
	AU1550_MAC1_DMA_INT,
	AU1550_GPIO0_INT	= AU1550_FIRST_INT + 32,
	AU1550_GPIO1_INT,
	AU1550_GPIO2_INT,
	AU1550_GPIO3_INT,
	AU1550_GPIO4_INT,
	AU1550_GPIO5_INT,
	AU1550_GPIO6_INT,
	AU1550_GPIO7_INT,
	AU1550_GPIO8_INT,
	AU1550_GPIO9_INT,
	AU1550_GPIO10_INT,
	AU1550_GPIO11_INT,
	AU1550_GPIO12_INT,
	AU1550_GPIO13_INT,
	AU1550_GPIO14_INT,
	AU1550_GPIO15_INT,
	AU1550_GPIO200_INT,
	AU1550_GPIO201_205_INT, /* Logical or of GPIO201:205 */
	AU1550_GPIO16_INT,
	AU1550_GPIO17_INT,
	AU1550_GPIO20_INT,
	AU1550_GPIO21_INT,
	AU1550_GPIO22_INT,
	AU1550_GPIO23_INT,
	AU1550_GPIO24_INT,
	AU1550_GPIO25_INT,
	AU1550_GPIO26_INT,
	AU1550_GPIO27_INT,
	AU1550_GPIO28_INT,
	AU1550_GPIO206_INT,
	AU1550_GPIO207_INT,
	AU1550_GPIO208_215_INT, /* Logical or of GPIO208:215 */
पूर्ण;

क्रमागत soc_au1200_पूर्णांकs अणु
	AU1200_FIRST_INT	= AU1000_INTC0_INT_BASE,
	AU1200_UART0_INT	= AU1200_FIRST_INT,
	AU1200_SWT_INT,
	AU1200_SD_INT,
	AU1200_DDMA_INT,
	AU1200_MAE_BE_INT,
	AU1200_GPIO200_INT,
	AU1200_GPIO201_INT,
	AU1200_GPIO202_INT,
	AU1200_UART1_INT,
	AU1200_MAE_FE_INT,
	AU1200_PSC0_INT,
	AU1200_PSC1_INT,
	AU1200_AES_INT,
	AU1200_CAMERA_INT,
	AU1200_TOY_INT,
	AU1200_TOY_MATCH0_INT,
	AU1200_TOY_MATCH1_INT,
	AU1200_TOY_MATCH2_INT,
	AU1200_RTC_INT,
	AU1200_RTC_MATCH0_INT,
	AU1200_RTC_MATCH1_INT,
	AU1200_RTC_MATCH2_INT,
	AU1200_GPIO203_INT,
	AU1200_न_अंकD_INT,
	AU1200_GPIO204_INT,
	AU1200_GPIO205_INT,
	AU1200_GPIO206_INT,
	AU1200_GPIO207_INT,
	AU1200_GPIO208_215_INT, /* Logical OR of 208:215 */
	AU1200_USB_INT,
	AU1200_LCD_INT,
	AU1200_MAE_BOTH_INT,
	AU1200_GPIO0_INT,
	AU1200_GPIO1_INT,
	AU1200_GPIO2_INT,
	AU1200_GPIO3_INT,
	AU1200_GPIO4_INT,
	AU1200_GPIO5_INT,
	AU1200_GPIO6_INT,
	AU1200_GPIO7_INT,
	AU1200_GPIO8_INT,
	AU1200_GPIO9_INT,
	AU1200_GPIO10_INT,
	AU1200_GPIO11_INT,
	AU1200_GPIO12_INT,
	AU1200_GPIO13_INT,
	AU1200_GPIO14_INT,
	AU1200_GPIO15_INT,
	AU1200_GPIO16_INT,
	AU1200_GPIO17_INT,
	AU1200_GPIO18_INT,
	AU1200_GPIO19_INT,
	AU1200_GPIO20_INT,
	AU1200_GPIO21_INT,
	AU1200_GPIO22_INT,
	AU1200_GPIO23_INT,
	AU1200_GPIO24_INT,
	AU1200_GPIO25_INT,
	AU1200_GPIO26_INT,
	AU1200_GPIO27_INT,
	AU1200_GPIO28_INT,
	AU1200_GPIO29_INT,
	AU1200_GPIO30_INT,
	AU1200_GPIO31_INT,
पूर्ण;

#पूर्ण_अगर /* !defined (_LANGUAGE_ASSEMBLY) */

#पूर्ण_अगर
