<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0
 *
 * Copyright 2016-2018 HabanaLअसल, Ltd.
 * All Rights Reserved.
 *
 */

#अगर_अघोषित QMAN_IF_H
#घोषणा QMAN_IF_H

#समावेश <linux/types.h>

/*
 * PRIMARY QUEUE
 */

काष्ठा hl_bd अणु
	__le64	ptr;
	__le32	len;
	__le32	ctl;
पूर्ण;

#घोषणा HL_BD_SIZE			माप(काष्ठा hl_bd)

/*
 * S/W CTL FIELDS.
 *
 * BD_CTL_REPEAT_VALID tells the CP whether the repeat field in the BD CTL is
 * valid. 1 means the repeat field is valid, 0 means not-valid,
 * i.e. repeat == 1
 */
#घोषणा BD_CTL_REPEAT_VALID_SHIFT	24
#घोषणा BD_CTL_REPEAT_VALID_MASK	0x01000000

#घोषणा BD_CTL_SHADOW_INDEX_SHIFT	0
#घोषणा BD_CTL_SHADOW_INDEX_MASK	0x00000FFF

/*
 * H/W CTL FIELDS
 */

#घोषणा BD_CTL_COMP_OFFSET_SHIFT	16
#घोषणा BD_CTL_COMP_OFFSET_MASK		0x0FFF0000

#घोषणा BD_CTL_COMP_DATA_SHIFT		0
#घोषणा BD_CTL_COMP_DATA_MASK		0x0000FFFF

/*
 * COMPLETION QUEUE
 */

काष्ठा hl_cq_entry अणु
	__le32	data;
पूर्ण;

#घोषणा HL_CQ_ENTRY_SIZE		माप(काष्ठा hl_cq_entry)

#घोषणा CQ_ENTRY_READY_SHIFT			31
#घोषणा CQ_ENTRY_READY_MASK			0x80000000

#घोषणा CQ_ENTRY_SHADOW_INDEX_VALID_SHIFT	30
#घोषणा CQ_ENTRY_SHADOW_INDEX_VALID_MASK	0x40000000

#घोषणा CQ_ENTRY_SHADOW_INDEX_SHIFT		BD_CTL_SHADOW_INDEX_SHIFT
#घोषणा CQ_ENTRY_SHADOW_INDEX_MASK		BD_CTL_SHADOW_INDEX_MASK


#पूर्ण_अगर /* QMAN_IF_H */
