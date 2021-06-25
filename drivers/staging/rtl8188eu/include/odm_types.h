<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#अगर_अघोषित __ODM_TYPES_H__
#घोषणा __ODM_TYPES_H__

#घोषणा	ODM_CE			0x04	/* BIT2 */

क्रमागत HAL_STATUS अणु
	HAL_STATUS_SUCCESS,
	HAL_STATUS_FAILURE,
पूर्ण;

#घोषणा SET_TX_DESC_ANTSEL_A_88E(__pTxDesc, __Value)			\
	SET_BITS_TO_LE_4BYTE(__pTxDesc + 8, 24, 1, __Value)
#घोषणा SET_TX_DESC_ANTSEL_B_88E(__pTxDesc, __Value)			\
	SET_BITS_TO_LE_4BYTE(__pTxDesc + 8, 25, 1, __Value)
#घोषणा SET_TX_DESC_ANTSEL_C_88E(__pTxDesc, __Value)			\
	SET_BITS_TO_LE_4BYTE(__pTxDesc + 28, 29, 1, __Value)

#पूर्ण_अगर /*  __ODM_TYPES_H__ */
