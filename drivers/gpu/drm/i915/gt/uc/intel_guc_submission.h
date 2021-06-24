<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/*
 * Copyright तऊ 2014-2019 Intel Corporation
 */

#अगर_अघोषित _INTEL_GUC_SUBMISSION_H_
#घोषणा _INTEL_GUC_SUBMISSION_H_

#समावेश <linux/types.h>

#समावेश "intel_guc.h"

काष्ठा पूर्णांकel_engine_cs;

व्योम पूर्णांकel_guc_submission_init_early(काष्ठा पूर्णांकel_guc *guc);
पूर्णांक पूर्णांकel_guc_submission_init(काष्ठा पूर्णांकel_guc *guc);
व्योम पूर्णांकel_guc_submission_enable(काष्ठा पूर्णांकel_guc *guc);
व्योम पूर्णांकel_guc_submission_disable(काष्ठा पूर्णांकel_guc *guc);
व्योम पूर्णांकel_guc_submission_fini(काष्ठा पूर्णांकel_guc *guc);
पूर्णांक पूर्णांकel_guc_preempt_work_create(काष्ठा पूर्णांकel_guc *guc);
व्योम पूर्णांकel_guc_preempt_work_destroy(काष्ठा पूर्णांकel_guc *guc);
पूर्णांक पूर्णांकel_guc_submission_setup(काष्ठा पूर्णांकel_engine_cs *engine);
bool पूर्णांकel_engine_in_guc_submission_mode(स्थिर काष्ठा पूर्णांकel_engine_cs *engine);

अटल अंतरभूत bool पूर्णांकel_guc_submission_is_supported(काष्ठा पूर्णांकel_guc *guc)
अणु
	/* XXX: GuC submission is unavailable क्रम now */
	वापस false;
पूर्ण

अटल अंतरभूत bool पूर्णांकel_guc_submission_is_wanted(काष्ठा पूर्णांकel_guc *guc)
अणु
	वापस guc->submission_selected;
पूर्ण

अटल अंतरभूत bool पूर्णांकel_guc_submission_is_used(काष्ठा पूर्णांकel_guc *guc)
अणु
	वापस पूर्णांकel_guc_is_used(guc) && पूर्णांकel_guc_submission_is_wanted(guc);
पूर्ण

#पूर्ण_अगर
