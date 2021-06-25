<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/*
 * Copyright तऊ 2019 Intel Corporation
 */

#अगर_अघोषित INTEL_GT_REQUESTS_H
#घोषणा INTEL_GT_REQUESTS_H

काष्ठा पूर्णांकel_engine_cs;
काष्ठा पूर्णांकel_gt;
काष्ठा पूर्णांकel_समयline;

दीर्घ पूर्णांकel_gt_retire_requests_समयout(काष्ठा पूर्णांकel_gt *gt, दीर्घ समयout);
अटल अंतरभूत व्योम पूर्णांकel_gt_retire_requests(काष्ठा पूर्णांकel_gt *gt)
अणु
	पूर्णांकel_gt_retire_requests_समयout(gt, 0);
पूर्ण

व्योम पूर्णांकel_engine_init_retire(काष्ठा पूर्णांकel_engine_cs *engine);
व्योम पूर्णांकel_engine_add_retire(काष्ठा पूर्णांकel_engine_cs *engine,
			     काष्ठा पूर्णांकel_समयline *tl);
व्योम पूर्णांकel_engine_fini_retire(काष्ठा पूर्णांकel_engine_cs *engine);

पूर्णांक पूर्णांकel_gt_रुको_क्रम_idle(काष्ठा पूर्णांकel_gt *gt, दीर्घ समयout);

व्योम पूर्णांकel_gt_init_requests(काष्ठा पूर्णांकel_gt *gt);
व्योम पूर्णांकel_gt_park_requests(काष्ठा पूर्णांकel_gt *gt);
व्योम पूर्णांकel_gt_unpark_requests(काष्ठा पूर्णांकel_gt *gt);
व्योम पूर्णांकel_gt_fini_requests(काष्ठा पूर्णांकel_gt *gt);

#पूर्ण_अगर /* INTEL_GT_REQUESTS_H */
