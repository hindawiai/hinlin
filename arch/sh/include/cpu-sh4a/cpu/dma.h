<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_SH_CPU_SH4_DMA_SH7780_H
#घोषणा __ASM_SH_CPU_SH4_DMA_SH7780_H

#समावेश <linux/sh_पूर्णांकc.h>

#अगर defined(CONFIG_CPU_SUBTYPE_SH7343) || \
	defined(CONFIG_CPU_SUBTYPE_SH7730)
#घोषणा DMTE0_IRQ	evt2irq(0x800)
#घोषणा DMTE4_IRQ	evt2irq(0xb80)
#घोषणा DMAE0_IRQ	evt2irq(0xbc0)	/* DMA Error IRQ*/
#घोषणा SH_DMAC_BASE0	0xFE008020
#या_अगर defined(CONFIG_CPU_SUBTYPE_SH7722)
#घोषणा DMTE0_IRQ	evt2irq(0x800)
#घोषणा DMTE4_IRQ	evt2irq(0xb80)
#घोषणा DMAE0_IRQ	evt2irq(0xbc0)	/* DMA Error IRQ*/
#घोषणा SH_DMAC_BASE0	0xFE008020
#या_अगर defined(CONFIG_CPU_SUBTYPE_SH7763)
#घोषणा DMTE0_IRQ	evt2irq(0x640)
#घोषणा DMTE4_IRQ	evt2irq(0x780)
#घोषणा DMAE0_IRQ	evt2irq(0x6c0)
#घोषणा SH_DMAC_BASE0	0xFF608020
#या_अगर defined(CONFIG_CPU_SUBTYPE_SH7723)
#घोषणा DMTE0_IRQ	evt2irq(0x800)	/* DMAC0A*/
#घोषणा DMTE4_IRQ	evt2irq(0xb80)	/* DMAC0B */
#घोषणा DMTE6_IRQ	evt2irq(0x700)
#घोषणा DMTE8_IRQ	evt2irq(0x740)	/* DMAC1A */
#घोषणा DMTE9_IRQ	evt2irq(0x760)
#घोषणा DMTE10_IRQ	evt2irq(0xb00)	/* DMAC1B */
#घोषणा DMTE11_IRQ	evt2irq(0xb20)
#घोषणा DMAE0_IRQ	evt2irq(0xbc0)	/* DMA Error IRQ*/
#घोषणा DMAE1_IRQ	evt2irq(0xb40)	/* DMA Error IRQ*/
#घोषणा SH_DMAC_BASE0	0xFE008020
#घोषणा SH_DMAC_BASE1	0xFDC08020
#या_अगर defined(CONFIG_CPU_SUBTYPE_SH7724)
#घोषणा DMTE0_IRQ	evt2irq(0x800)	/* DMAC0A*/
#घोषणा DMTE4_IRQ	evt2irq(0xb80)	/* DMAC0B */
#घोषणा DMTE6_IRQ	evt2irq(0x700)
#घोषणा DMTE8_IRQ	evt2irq(0x740)	/* DMAC1A */
#घोषणा DMTE9_IRQ	evt2irq(0x760)
#घोषणा DMTE10_IRQ	evt2irq(0xb00)	/* DMAC1B */
#घोषणा DMTE11_IRQ	evt2irq(0xb20)
#घोषणा DMAE0_IRQ	evt2irq(0xbc0)	/* DMA Error IRQ*/
#घोषणा DMAE1_IRQ	evt2irq(0xb40)	/* DMA Error IRQ*/
#घोषणा SH_DMAC_BASE0	0xFE008020
#घोषणा SH_DMAC_BASE1	0xFDC08020
#या_अगर defined(CONFIG_CPU_SUBTYPE_SH7780)
#घोषणा DMTE0_IRQ	evt2irq(0x640)
#घोषणा DMTE4_IRQ	evt2irq(0x780)
#घोषणा DMTE6_IRQ	evt2irq(0x7c0)
#घोषणा DMTE8_IRQ	evt2irq(0xd80)
#घोषणा DMTE9_IRQ	evt2irq(0xda0)
#घोषणा DMTE10_IRQ	evt2irq(0xdc0)
#घोषणा DMTE11_IRQ	evt2irq(0xde0)
#घोषणा DMAE0_IRQ	evt2irq(0x6c0)	/* DMA Error IRQ */
#घोषणा SH_DMAC_BASE0	0xFC808020
#घोषणा SH_DMAC_BASE1	0xFC818020
#अन्यथा /* SH7785 */
#घोषणा DMTE0_IRQ	evt2irq(0x620)
#घोषणा DMTE4_IRQ	evt2irq(0x6a0)
#घोषणा DMTE6_IRQ	evt2irq(0x880)
#घोषणा DMTE8_IRQ	evt2irq(0x8c0)
#घोषणा DMTE9_IRQ	evt2irq(0x8e0)
#घोषणा DMTE10_IRQ	evt2irq(0x900)
#घोषणा DMTE11_IRQ	evt2irq(0x920)
#घोषणा DMAE0_IRQ	evt2irq(0x6e0)	/* DMA Error IRQ0 */
#घोषणा DMAE1_IRQ	evt2irq(0x940)	/* DMA Error IRQ1 */
#घोषणा SH_DMAC_BASE0	0xFC808020
#घोषणा SH_DMAC_BASE1	0xFCC08020
#पूर्ण_अगर

#पूर्ण_अगर /* __ASM_SH_CPU_SH4_DMA_SH7780_H */
