<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/

#समावेश "odm_precomp.h"

व्योम odm_PathDiversityInit(व्योम *pDM_VOID)
अणु
	काष्ठा dm_odm_t *pDM_Odm = (काष्ठा dm_odm_t *)pDM_VOID;

	अगर (!(pDM_Odm->SupportAbility & ODM_BB_PATH_DIV))
		ODM_RT_TRACE(
			pDM_Odm,
			ODM_COMP_PATH_DIV,
			ODM_DBG_LOUD,
			("Return: Not Support PathDiv\n")
		);
पूर्ण

व्योम odm_PathDiversity(व्योम *pDM_VOID)
अणु
	काष्ठा dm_odm_t *pDM_Odm = (काष्ठा dm_odm_t *)pDM_VOID;

	अगर (!(pDM_Odm->SupportAbility & ODM_BB_PATH_DIV))
		ODM_RT_TRACE(
			pDM_Odm,
			ODM_COMP_PATH_DIV,
			ODM_DBG_LOUD,
			("Return: Not Support PathDiv\n")
		);
पूर्ण
