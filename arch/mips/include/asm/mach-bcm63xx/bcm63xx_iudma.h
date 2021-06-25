<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित BCM63XX_IUDMA_H_
#घोषणा BCM63XX_IUDMA_H_

#समावेश <linux/types.h>

/*
 * rx/tx dma descriptor
 */
काष्ठा bcm_enet_desc अणु
	u32 len_stat;
	u32 address;
पूर्ण;

/* control */
#घोषणा DMADESC_LENGTH_SHIFT	16
#घोषणा DMADESC_LENGTH_MASK	(0xfff << DMADESC_LENGTH_SHIFT)
#घोषणा DMADESC_OWNER_MASK	(1 << 15)
#घोषणा DMADESC_EOP_MASK	(1 << 14)
#घोषणा DMADESC_SOP_MASK	(1 << 13)
#घोषणा DMADESC_ESOP_MASK	(DMADESC_EOP_MASK | DMADESC_SOP_MASK)
#घोषणा DMADESC_WRAP_MASK	(1 << 12)
#घोषणा DMADESC_USB_NOZERO_MASK (1 << 1)
#घोषणा DMADESC_USB_ZERO_MASK	(1 << 0)

/* status */
#घोषणा DMADESC_UNDER_MASK	(1 << 9)
#घोषणा DMADESC_APPEND_CRC	(1 << 8)
#घोषणा DMADESC_OVSIZE_MASK	(1 << 4)
#घोषणा DMADESC_RXER_MASK	(1 << 2)
#घोषणा DMADESC_CRC_MASK	(1 << 1)
#घोषणा DMADESC_OV_MASK		(1 << 0)
#घोषणा DMADESC_ERR_MASK	(DMADESC_UNDER_MASK | \
				DMADESC_OVSIZE_MASK | \
				DMADESC_RXER_MASK | \
				DMADESC_CRC_MASK | \
				DMADESC_OV_MASK)

#पूर्ण_अगर /* ! BCM63XX_IUDMA_H_ */
