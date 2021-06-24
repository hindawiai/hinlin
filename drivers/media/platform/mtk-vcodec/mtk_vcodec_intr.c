<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
* Copyright (c) 2016 MediaTek Inc.
* Author: Tअगरfany Lin <tअगरfany.lin@mediatek.com>
*/

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/रुको.h>

#समावेश "mtk_vcodec_drv.h"
#समावेश "mtk_vcodec_intr.h"
#समावेश "mtk_vcodec_util.h"

पूर्णांक mtk_vcodec_रुको_क्रम_करोne_ctx(काष्ठा mtk_vcodec_ctx  *ctx, पूर्णांक command,
				 अचिन्हित पूर्णांक समयout_ms)
अणु
	रुको_queue_head_t *रुकोqueue;
	दीर्घ समयout_jअगरf, ret;
	पूर्णांक status = 0;

	रुकोqueue = (रुको_queue_head_t *)&ctx->queue;
	समयout_jअगरf = msecs_to_jअगरfies(समयout_ms);

	ret = रुको_event_पूर्णांकerruptible_समयout(*रुकोqueue,
				ctx->पूर्णांक_cond,
				समयout_jअगरf);

	अगर (!ret) अणु
		status = -1;	/* समयout */
		mtk_v4l2_err("[%d] ctx->type=%d, cmd=%d, wait_event_interruptible_timeout time=%ums out %d %d!",
			     ctx->id, ctx->type, command, समयout_ms,
			     ctx->पूर्णांक_cond, ctx->पूर्णांक_type);
	पूर्ण अन्यथा अगर (-ERESTARTSYS == ret) अणु
		mtk_v4l2_err("[%d] ctx->type=%d, cmd=%d, wait_event_interruptible_timeout interrupted by a signal %d %d",
			     ctx->id, ctx->type, command, ctx->पूर्णांक_cond,
			     ctx->पूर्णांक_type);
		status = -1;
	पूर्ण

	ctx->पूर्णांक_cond = 0;
	ctx->पूर्णांक_type = 0;

	वापस status;
पूर्ण
EXPORT_SYMBOL(mtk_vcodec_रुको_क्रम_करोne_ctx);
