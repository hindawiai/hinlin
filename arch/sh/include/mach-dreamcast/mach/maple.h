<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_MAPLE_H
#घोषणा __ASM_MAPLE_H

#घोषणा MAPLE_PORTS 4
#घोषणा MAPLE_PNP_INTERVAL HZ
#घोषणा MAPLE_MAXPACKETS 8
#घोषणा MAPLE_DMA_ORDER 14
#घोषणा MAPLE_DMA_SIZE (1 << MAPLE_DMA_ORDER)
#घोषणा MAPLE_DMA_PAGES ((MAPLE_DMA_ORDER > PAGE_SHIFT) ? \
			  MAPLE_DMA_ORDER - PAGE_SHIFT : 0)

/* Maple Bus रेजिस्टरs */
#घोषणा MAPLE_BASE     0xa05f6c00
#घोषणा MAPLE_DMAADDR  (MAPLE_BASE+0x04)
#घोषणा MAPLE_TRIGTYPE (MAPLE_BASE+0x10)
#घोषणा MAPLE_ENABLE   (MAPLE_BASE+0x14)
#घोषणा MAPLE_STATE    (MAPLE_BASE+0x18)
#घोषणा MAPLE_SPEED    (MAPLE_BASE+0x80)
#घोषणा MAPLE_RESET    (MAPLE_BASE+0x8c)

#घोषणा MAPLE_MAGIC    0x6155404f
#घोषणा MAPLE_2MBPS    0
#घोषणा MAPLE_TIMEOUT(n) ((n)<<15)

/* Function codes */
#घोषणा MAPLE_FUNC_CONTROLLER 0x001
#घोषणा MAPLE_FUNC_MEMCARD    0x002
#घोषणा MAPLE_FUNC_LCD        0x004
#घोषणा MAPLE_FUNC_CLOCK      0x008
#घोषणा MAPLE_FUNC_MICROPHONE 0x010
#घोषणा MAPLE_FUNC_ARGUN      0x020
#घोषणा MAPLE_FUNC_KEYBOARD   0x040
#घोषणा MAPLE_FUNC_LIGHTGUN   0x080
#घोषणा MAPLE_FUNC_PURUPURU   0x100
#घोषणा MAPLE_FUNC_MOUSE      0x200

#पूर्ण_अगर /* __ASM_MAPLE_H */
