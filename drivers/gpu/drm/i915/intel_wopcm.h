<शैली गुरु>
/*
 * SPDX-License-Identअगरier: MIT
 *
 * Copyright तऊ 2017-2018 Intel Corporation
 */

#अगर_अघोषित _INTEL_WOPCM_H_
#घोषणा _INTEL_WOPCM_H_

#समावेश <linux/types.h>

/**
 * काष्ठा पूर्णांकel_wopcm - Overall WOPCM info and WOPCM regions.
 * @size: Size of overall WOPCM.
 * @guc: GuC WOPCM Region info.
 * @guc.base: GuC WOPCM base which is offset from WOPCM base.
 * @guc.size: Size of the GuC WOPCM region.
 */
काष्ठा पूर्णांकel_wopcm अणु
	u32 size;
	काष्ठा अणु
		u32 base;
		u32 size;
	पूर्ण guc;
पूर्ण;

/**
 * पूर्णांकel_wopcm_guc_base()
 * @wopcm:	पूर्णांकel_wopcm काष्ठाure
 *
 * Returns the base of the WOPCM shaकरोwed region.
 *
 * Returns:
 * 0 अगर GuC is not present or not in use.
 * Otherwise, the GuC WOPCM base.
 */
अटल अंतरभूत u32 पूर्णांकel_wopcm_guc_base(काष्ठा पूर्णांकel_wopcm *wopcm)
अणु
	वापस wopcm->guc.base;
पूर्ण

/**
 * पूर्णांकel_wopcm_guc_size()
 * @wopcm:	पूर्णांकel_wopcm काष्ठाure
 *
 * Returns size of the WOPCM shaकरोwed region.
 *
 * Returns:
 * 0 अगर GuC is not present or not in use.
 * Otherwise, the GuC WOPCM size.
 */
अटल अंतरभूत u32 पूर्णांकel_wopcm_guc_size(काष्ठा पूर्णांकel_wopcm *wopcm)
अणु
	वापस wopcm->guc.size;
पूर्ण

व्योम पूर्णांकel_wopcm_init_early(काष्ठा पूर्णांकel_wopcm *wopcm);
व्योम पूर्णांकel_wopcm_init(काष्ठा पूर्णांकel_wopcm *wopcm);

#पूर्ण_अगर
