<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/


#अगर_अघोषित	__ODM_INTERFACE_H__
#घोषणा __ODM_INTERFACE_H__



/*  =========== Macro Define */

#घोषणा _reg_all(_name)			ODM_##_name
#घोषणा _reg_ic(_name, _ic)		ODM_##_name##_ic
#घोषणा _bit_all(_name)			BIT_##_name
#घोषणा _bit_ic(_name, _ic)		BIT_##_name##_ic

/*===================================

#घोषणा ODM_REG_DIG_11N		0xC50
#घोषणा ODM_REG_DIG_11AC	0xDDD

ODM_REG(DIG, _pDM_Odm)
=====================================*/

#घोषणा _reg_11N(_name)			ODM_REG_##_name##_11N
#घोषणा _bit_11N(_name)			ODM_BIT_##_name##_11N

#घोषणा _cat(_name, _ic_type, _func) _func##_11N(_name)

/*  _name: name of रेजिस्टर or bit. */
/*  Example: "ODM_REG(R_A_AGC_CORE1, pDM_Odm)" */
/*         माला_लो "ODM_R_A_AGC_CORE1" or "ODM_R_A_AGC_CORE1_8192C", depends on SupportICType. */
#घोषणा ODM_REG(_name, _pDM_Odm)	_cat(_name, _pDM_Odm->SupportICType, _reg)
#घोषणा ODM_BIT(_name, _pDM_Odm)	_cat(_name, _pDM_Odm->SupportICType, _bit)

#पूर्ण_अगर	/*  __ODM_INTERFACE_H__ */
