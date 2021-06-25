<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_CPU_SH3_DMA_H
#घोषणा __ASM_CPU_SH3_DMA_H

#समावेश <linux/sh_पूर्णांकc.h>

#अगर defined(CONFIG_CPU_SUBTYPE_SH7720) || \
    defined(CONFIG_CPU_SUBTYPE_SH7721) || \
    defined(CONFIG_CPU_SUBTYPE_SH7710) || \
    defined(CONFIG_CPU_SUBTYPE_SH7712)
#घोषणा SH_DMAC_BASE0	0xa4010020
#अन्यथा /* SH7705/06/07/09 */
#घोषणा SH_DMAC_BASE0	0xa4000020
#पूर्ण_अगर

#घोषणा DMTE0_IRQ	evt2irq(0x800)
#घोषणा DMTE4_IRQ	evt2irq(0xb80)

#पूर्ण_अगर /* __ASM_CPU_SH3_DMA_H */
