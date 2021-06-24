<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Thunderbolt driver - NHI रेजिस्टरs
 *
 * Copyright (c) 2014 Andreas Noever <andreas.noever@gmail.com>
 * Copyright (C) 2018, Intel Corporation
 */

#अगर_अघोषित NHI_REGS_H_
#घोषणा NHI_REGS_H_

#समावेश <linux/types.h>

क्रमागत ring_flags अणु
	RING_FLAG_ISOCH_ENABLE = 1 << 27, /* TX only? */
	RING_FLAG_E2E_FLOW_CONTROL = 1 << 28,
	RING_FLAG_PCI_NO_SNOOP = 1 << 29,
	RING_FLAG_RAW = 1 << 30, /* ignore खातापूर्ण/SOF mask, include checksum */
	RING_FLAG_ENABLE = 1 << 31,
पूर्ण;

/**
 * काष्ठा ring_desc - TX/RX ring entry
 *
 * For TX set length/eof/sof.
 * For RX length/eof/sof are set by the NHI.
 */
काष्ठा ring_desc अणु
	u64 phys;
	u32 length:12;
	u32 eof:4;
	u32 sof:4;
	क्रमागत ring_desc_flags flags:12;
	u32 समय; /* ग_लिखो zero */
पूर्ण __packed;

/* NHI रेजिस्टरs in bar 0 */

/*
 * 16 bytes per entry, one entry क्रम every hop (REG_HOP_COUNT)
 * 00: physical poपूर्णांकer to an array of काष्ठा ring_desc
 * 08: ring tail (set by NHI)
 * 10: ring head (index of first non posted descriptor)
 * 12: descriptor count
 */
#घोषणा REG_TX_RING_BASE	0x00000

/*
 * 16 bytes per entry, one entry क्रम every hop (REG_HOP_COUNT)
 * 00: physical poपूर्णांकer to an array of काष्ठा ring_desc
 * 08: ring head (index of first not posted descriptor)
 * 10: ring tail (set by NHI)
 * 12: descriptor count
 * 14: max frame sizes (anything larger than 0x100 has no effect)
 */
#घोषणा REG_RX_RING_BASE	0x08000

/*
 * 32 bytes per entry, one entry क्रम every hop (REG_HOP_COUNT)
 * 00: क्रमागत_ring_flags
 * 04: isoch समय stamp ?? (ग_लिखो 0)
 * ..: unknown
 */
#घोषणा REG_TX_OPTIONS_BASE	0x19800

/*
 * 32 bytes per entry, one entry क्रम every hop (REG_HOP_COUNT)
 * 00: क्रमागत ring_flags
 *     If RING_FLAG_E2E_FLOW_CONTROL is set then bits 13-23 must be set to
 *     the corresponding TX hop id.
 * 04: खातापूर्ण/SOF mask (ignored क्रम RING_FLAG_RAW rings)
 * ..: unknown
 */
#घोषणा REG_RX_OPTIONS_BASE	0x29800
#घोषणा REG_RX_OPTIONS_E2E_HOP_MASK	GENMASK(22, 12)
#घोषणा REG_RX_OPTIONS_E2E_HOP_SHIFT	12

/*
 * three bitfields: tx, rx, rx overflow
 * Every bitfield contains one bit क्रम every hop (REG_HOP_COUNT). Registers are
 * cleared on पढ़ो. New पूर्णांकerrupts are fired only after ALL रेजिस्टरs have been
 * पढ़ो (even those containing only disabled rings).
 */
#घोषणा REG_RING_NOTIFY_BASE	0x37800
#घोषणा RING_NOTIFY_REG_COUNT(nhi) ((31 + 3 * nhi->hop_count) / 32)

/*
 * two bitfields: rx, tx
 * Both bitfields contains one bit क्रम every hop (REG_HOP_COUNT). To
 * enable/disable पूर्णांकerrupts set/clear the corresponding bits.
 */
#घोषणा REG_RING_INTERRUPT_BASE	0x38200
#घोषणा RING_INTERRUPT_REG_COUNT(nhi) ((31 + 2 * nhi->hop_count) / 32)

#घोषणा REG_INT_THROTTLING_RATE	0x38c00

/* Interrupt Vector Allocation */
#घोषणा REG_INT_VEC_ALLOC_BASE	0x38c40
#घोषणा REG_INT_VEC_ALLOC_BITS	4
#घोषणा REG_INT_VEC_ALLOC_MASK	GENMASK(3, 0)
#घोषणा REG_INT_VEC_ALLOC_REGS	(32 / REG_INT_VEC_ALLOC_BITS)

/* The last 11 bits contain the number of hops supported by the NHI port. */
#घोषणा REG_HOP_COUNT		0x39640

#घोषणा REG_DMA_MISC			0x39864
#घोषणा REG_DMA_MISC_INT_AUTO_CLEAR     BIT(2)

#घोषणा REG_INMAIL_DATA			0x39900

#घोषणा REG_INMAIL_CMD			0x39904
#घोषणा REG_INMAIL_CMD_MASK		GENMASK(7, 0)
#घोषणा REG_INMAIL_ERROR		BIT(30)
#घोषणा REG_INMAIL_OP_REQUEST		BIT(31)

#घोषणा REG_OUTMAIL_CMD			0x3990c
#घोषणा REG_OUTMAIL_CMD_OPMODE_SHIFT	8
#घोषणा REG_OUTMAIL_CMD_OPMODE_MASK	GENMASK(11, 8)

#घोषणा REG_FW_STS			0x39944
#घोषणा REG_FW_STS_NVM_AUTH_DONE	BIT(31)
#घोषणा REG_FW_STS_CIO_RESET_REQ	BIT(30)
#घोषणा REG_FW_STS_ICM_EN_CPU		BIT(2)
#घोषणा REG_FW_STS_ICM_EN_INVERT	BIT(1)
#घोषणा REG_FW_STS_ICM_EN		BIT(0)

/* ICL NHI VSEC रेजिस्टरs */

/* FW पढ़ोy */
#घोषणा VS_CAP_9			0xc8
#घोषणा VS_CAP_9_FW_READY		BIT(31)
/* UUID */
#घोषणा VS_CAP_10			0xcc
#घोषणा VS_CAP_11			0xd0
/* LTR */
#घोषणा VS_CAP_15			0xe0
#घोषणा VS_CAP_16			0xe4
/* TBT2PCIe */
#घोषणा VS_CAP_18			0xec
#घोषणा VS_CAP_18_DONE			BIT(0)
/* PCIe2TBT */
#घोषणा VS_CAP_19			0xf0
#घोषणा VS_CAP_19_VALID			BIT(0)
#घोषणा VS_CAP_19_CMD_SHIFT		1
#घोषणा VS_CAP_19_CMD_MASK		GENMASK(7, 1)
/* Force घातer */
#घोषणा VS_CAP_22			0xfc
#घोषणा VS_CAP_22_FORCE_POWER		BIT(1)
#घोषणा VS_CAP_22_DMA_DELAY_MASK	GENMASK(31, 24)
#घोषणा VS_CAP_22_DMA_DELAY_SHIFT	24

/**
 * क्रमागत icl_lc_mailbox_cmd - ICL specअगरic LC mailbox commands
 * @ICL_LC_GO2SX: Ask LC to enter Sx without wake
 * @ICL_LC_GO2SX_NO_WAKE: Ask LC to enter Sx with wake
 * @ICL_LC_PREPARE_FOR_RESET: Prepare LC क्रम reset
 */
क्रमागत icl_lc_mailbox_cmd अणु
	ICL_LC_GO2SX = 0x02,
	ICL_LC_GO2SX_NO_WAKE = 0x03,
	ICL_LC_PREPARE_FOR_RESET = 0x21,
पूर्ण;

#पूर्ण_अगर
