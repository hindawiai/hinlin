<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#अगर_अघोषित __ODM_TYPES_H__
#घोषणा __ODM_TYPES_H__

#समावेश <drv_types.h>

/*  Deअगरne HW endian support */
#घोषणा	ODM_ENDIAN_BIG	0
#घोषणा	ODM_ENDIAN_LITTLE	1

#घोषणा GET_ODM(__padapter)	((PDM_ODM_T)(&((GET_HAL_DATA(__padapter))->odmpriv)))

क्रमागत hal_status अणु
	HAL_STATUS_SUCCESS,
	HAL_STATUS_FAILURE,
	/*RT_STATUS_PENDING,
	RT_STATUS_RESOURCE,
	RT_STATUS_INVALID_CONTEXT,
	RT_STATUS_INVALID_PARAMETER,
	RT_STATUS_NOT_SUPPORT,
	RT_STATUS_OS_API_FAILED,*/
पूर्ण;


	#अगर defined(__LITTLE_ENDIAN)
		#घोषणा	ODM_ENDIAN_TYPE			ODM_ENDIAN_LITTLE
	#अन्यथा
		#घोषणा	ODM_ENDIAN_TYPE			ODM_ENDIAN_BIG
	#पूर्ण_अगर

	#घोषणा	STA_INFO_T			काष्ठा sta_info
	#घोषणा	PSTA_INFO_T		काष्ठा sta_info *

	#घोषणा SET_TX_DESC_ANTSEL_A_88E(__pTxDesc, __Value) SET_BITS_TO_LE_4BYTE(__pTxDesc+8, 24, 1, __Value)
	#घोषणा SET_TX_DESC_ANTSEL_B_88E(__pTxDesc, __Value) SET_BITS_TO_LE_4BYTE(__pTxDesc+8, 25, 1, __Value)
	#घोषणा SET_TX_DESC_ANTSEL_C_88E(__pTxDesc, __Value) SET_BITS_TO_LE_4BYTE(__pTxDesc+28, 29, 1, __Value)

	/* define useless flag to aव्योम compile warning */
	#घोषणा	USE_WORKITEM 0
	#घोषणा   FPGA_TWO_MAC_VERIFICATION	0

#घोषणा READ_NEXT_PAIR(v1, v2, i) करो अणु अगर (i+2 >= ArrayLen) अवरोध; i += 2; v1 = Array[i]; v2 = Array[i+1]; पूर्ण जबतक (0)
#घोषणा COND_ELSE  2
#घोषणा COND_ENDIF 3

#पूर्ण_अगर /*  __ODM_TYPES_H__ */
