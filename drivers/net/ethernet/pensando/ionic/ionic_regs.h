<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0 OR Linux-OpenIB) OR BSD-2-Clause */
/* Copyright (c) 2018-2019 Pensanकरो Systems, Inc.  All rights reserved. */

#अगर_अघोषित IONIC_REGS_H
#घोषणा IONIC_REGS_H

#समावेश <linux/पन.स>

/** काष्ठा ionic_पूर्णांकr - पूर्णांकerrupt control रेजिस्टर set.
 * @coal_init:			coalesce समयr initial value.
 * @mask:			पूर्णांकerrupt mask value.
 * @credits:			पूर्णांकerrupt credit count and वापस.
 * @mask_निश्चित:		पूर्णांकerrupt mask value on निश्चित.
 * @coal:			coalesce समयr समय reमुख्यing.
 */
काष्ठा ionic_पूर्णांकr अणु
	u32 coal_init;
	u32 mask;
	u32 credits;
	u32 mask_निश्चित;
	u32 coal;
	u32 rsvd[3];
पूर्ण;

#घोषणा IONIC_INTR_CTRL_REGS_MAX	2048
#घोषणा IONIC_INTR_CTRL_COAL_MAX	0x3F

/** क्रमागत ionic_पूर्णांकr_mask_vals - valid values क्रम mask and mask_निश्चित.
 * @IONIC_INTR_MASK_CLEAR:	unmask पूर्णांकerrupt.
 * @IONIC_INTR_MASK_SET:	mask पूर्णांकerrupt.
 */
क्रमागत ionic_पूर्णांकr_mask_vals अणु
	IONIC_INTR_MASK_CLEAR		= 0,
	IONIC_INTR_MASK_SET		= 1,
पूर्ण;

/** क्रमागत ionic_पूर्णांकr_credits_bits - bitwise composition of credits values.
 * @IONIC_INTR_CRED_COUNT:	bit mask of credit count, no shअगरt needed.
 * @IONIC_INTR_CRED_COUNT_SIGNED: bit mask of credit count, including sign bit.
 * @IONIC_INTR_CRED_UNMASK:	unmask the पूर्णांकerrupt.
 * @IONIC_INTR_CRED_RESET_COALESCE: reset the coalesce समयr.
 * @IONIC_INTR_CRED_REARM:	unmask the and reset the समयr.
 */
क्रमागत ionic_पूर्णांकr_credits_bits अणु
	IONIC_INTR_CRED_COUNT		= 0x7fffu,
	IONIC_INTR_CRED_COUNT_SIGNED	= 0xffffu,
	IONIC_INTR_CRED_UNMASK		= 0x10000u,
	IONIC_INTR_CRED_RESET_COALESCE	= 0x20000u,
	IONIC_INTR_CRED_REARM		= (IONIC_INTR_CRED_UNMASK |
					   IONIC_INTR_CRED_RESET_COALESCE),
पूर्ण;

अटल अंतरभूत व्योम ionic_पूर्णांकr_coal_init(काष्ठा ionic_पूर्णांकr __iomem *पूर्णांकr_ctrl,
					पूर्णांक पूर्णांकr_idx, u32 coal)
अणु
	ioग_लिखो32(coal, &पूर्णांकr_ctrl[पूर्णांकr_idx].coal_init);
पूर्ण

अटल अंतरभूत व्योम ionic_पूर्णांकr_mask(काष्ठा ionic_पूर्णांकr __iomem *पूर्णांकr_ctrl,
				   पूर्णांक पूर्णांकr_idx, u32 mask)
अणु
	ioग_लिखो32(mask, &पूर्णांकr_ctrl[पूर्णांकr_idx].mask);
पूर्ण

अटल अंतरभूत व्योम ionic_पूर्णांकr_credits(काष्ठा ionic_पूर्णांकr __iomem *पूर्णांकr_ctrl,
				      पूर्णांक पूर्णांकr_idx, u32 cred, u32 flags)
अणु
	अगर (WARN_ON_ONCE(cred > IONIC_INTR_CRED_COUNT)) अणु
		cred = ioपढ़ो32(&पूर्णांकr_ctrl[पूर्णांकr_idx].credits);
		cred &= IONIC_INTR_CRED_COUNT_SIGNED;
	पूर्ण

	ioग_लिखो32(cred | flags, &पूर्णांकr_ctrl[पूर्णांकr_idx].credits);
पूर्ण

अटल अंतरभूत व्योम ionic_पूर्णांकr_clean(काष्ठा ionic_पूर्णांकr __iomem *पूर्णांकr_ctrl,
				    पूर्णांक पूर्णांकr_idx)
अणु
	u32 cred;

	cred = ioपढ़ो32(&पूर्णांकr_ctrl[पूर्णांकr_idx].credits);
	cred &= IONIC_INTR_CRED_COUNT_SIGNED;
	cred |= IONIC_INTR_CRED_RESET_COALESCE;
	ioग_लिखो32(cred, &पूर्णांकr_ctrl[पूर्णांकr_idx].credits);
पूर्ण

अटल अंतरभूत व्योम ionic_पूर्णांकr_mask_निश्चित(काष्ठा ionic_पूर्णांकr __iomem *पूर्णांकr_ctrl,
					  पूर्णांक पूर्णांकr_idx, u32 mask)
अणु
	ioग_लिखो32(mask, &पूर्णांकr_ctrl[पूर्णांकr_idx].mask_निश्चित);
पूर्ण

/** क्रमागत ionic_dbell_bits - bitwise composition of dbell values.
 *
 * @IONIC_DBELL_QID_MASK:	unshअगरted mask of valid queue id bits.
 * @IONIC_DBELL_QID_SHIFT:	queue id shअगरt amount in dbell value.
 * @IONIC_DBELL_QID:		macro to build QID component of dbell value.
 *
 * @IONIC_DBELL_RING_MASK:	unshअगरted mask of valid ring bits.
 * @IONIC_DBELL_RING_SHIFT:	ring shअगरt amount in dbell value.
 * @IONIC_DBELL_RING:		macro to build ring component of dbell value.
 *
 * @IONIC_DBELL_RING_0:		ring zero dbell component value.
 * @IONIC_DBELL_RING_1:		ring one dbell component value.
 * @IONIC_DBELL_RING_2:		ring two dbell component value.
 * @IONIC_DBELL_RING_3:		ring three dbell component value.
 *
 * @IONIC_DBELL_INDEX_MASK:	bit mask of valid index bits, no shअगरt needed.
 */
क्रमागत ionic_dbell_bits अणु
	IONIC_DBELL_QID_MASK		= 0xffffff,
	IONIC_DBELL_QID_SHIFT		= 24,

#घोषणा IONIC_DBELL_QID(n) \
	(((u64)(n) & IONIC_DBELL_QID_MASK) << IONIC_DBELL_QID_SHIFT)

	IONIC_DBELL_RING_MASK		= 0x7,
	IONIC_DBELL_RING_SHIFT		= 16,

#घोषणा IONIC_DBELL_RING(n) \
	(((u64)(n) & IONIC_DBELL_RING_MASK) << IONIC_DBELL_RING_SHIFT)

	IONIC_DBELL_RING_0		= 0,
	IONIC_DBELL_RING_1		= IONIC_DBELL_RING(1),
	IONIC_DBELL_RING_2		= IONIC_DBELL_RING(2),
	IONIC_DBELL_RING_3		= IONIC_DBELL_RING(3),

	IONIC_DBELL_INDEX_MASK		= 0xffff,
पूर्ण;

अटल अंतरभूत व्योम ionic_dbell_ring(u64 __iomem *db_page, पूर्णांक qtype, u64 val)
अणु
	ग_लिखोq(val, &db_page[qtype]);
पूर्ण

#पूर्ण_अगर /* IONIC_REGS_H */
