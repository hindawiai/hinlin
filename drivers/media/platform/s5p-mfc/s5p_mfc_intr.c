<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * drivers/media/platक्रमm/samsung/mfc5/s5p_mfc_पूर्णांकr.c
 *
 * C file क्रम Samsung MFC (Multi Function Codec - FIMV) driver
 * This file contains functions used to रुको क्रम command completion.
 *
 * Kamil Debski, Copyright (C) 2011 Samsung Electronics Co., Ltd.
 * http://www.samsung.com/
 */

#समावेश <linux/delay.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/पन.स>
#समावेश <linux/sched.h>
#समावेश <linux/रुको.h>
#समावेश "s5p_mfc_common.h"
#समावेश "s5p_mfc_debug.h"
#समावेश "s5p_mfc_intr.h"

पूर्णांक s5p_mfc_रुको_क्रम_करोne_dev(काष्ठा s5p_mfc_dev *dev, पूर्णांक command)
अणु
	पूर्णांक ret;

	ret = रुको_event_पूर्णांकerruptible_समयout(dev->queue,
		(dev->पूर्णांक_cond && (dev->पूर्णांक_type == command
		|| dev->पूर्णांक_type == S5P_MFC_R2H_CMD_ERR_RET)),
		msecs_to_jअगरfies(MFC_INT_TIMEOUT));
	अगर (ret == 0) अणु
		mfc_err("Interrupt (dev->int_type:%d, command:%d) timed out\n",
							dev->पूर्णांक_type, command);
		वापस 1;
	पूर्ण अन्यथा अगर (ret == -ERESTARTSYS) अणु
		mfc_err("Interrupted by a signal\n");
		वापस 1;
	पूर्ण
	mfc_debug(1, "Finished waiting (dev->int_type:%d, command: %d)\n",
							dev->पूर्णांक_type, command);
	अगर (dev->पूर्णांक_type == S5P_MFC_R2H_CMD_ERR_RET)
		वापस 1;
	वापस 0;
पूर्ण

व्योम s5p_mfc_clean_dev_पूर्णांक_flags(काष्ठा s5p_mfc_dev *dev)
अणु
	dev->पूर्णांक_cond = 0;
	dev->पूर्णांक_type = 0;
	dev->पूर्णांक_err = 0;
पूर्ण

पूर्णांक s5p_mfc_रुको_क्रम_करोne_ctx(काष्ठा s5p_mfc_ctx *ctx,
				    पूर्णांक command, पूर्णांक पूर्णांकerrupt)
अणु
	पूर्णांक ret;

	अगर (पूर्णांकerrupt) अणु
		ret = रुको_event_पूर्णांकerruptible_समयout(ctx->queue,
				(ctx->पूर्णांक_cond && (ctx->पूर्णांक_type == command
			|| ctx->पूर्णांक_type == S5P_MFC_R2H_CMD_ERR_RET)),
					msecs_to_jअगरfies(MFC_INT_TIMEOUT));
	पूर्ण अन्यथा अणु
		ret = रुको_event_समयout(ctx->queue,
				(ctx->पूर्णांक_cond && (ctx->पूर्णांक_type == command
			|| ctx->पूर्णांक_type == S5P_MFC_R2H_CMD_ERR_RET)),
					msecs_to_jअगरfies(MFC_INT_TIMEOUT));
	पूर्ण
	अगर (ret == 0) अणु
		mfc_err("Interrupt (ctx->int_type:%d, command:%d) timed out\n",
							ctx->पूर्णांक_type, command);
		वापस 1;
	पूर्ण अन्यथा अगर (ret == -ERESTARTSYS) अणु
		mfc_err("Interrupted by a signal\n");
		वापस 1;
	पूर्ण
	mfc_debug(1, "Finished waiting (ctx->int_type:%d, command: %d)\n",
							ctx->पूर्णांक_type, command);
	अगर (ctx->पूर्णांक_type == S5P_MFC_R2H_CMD_ERR_RET)
		वापस 1;
	वापस 0;
पूर्ण

व्योम s5p_mfc_clean_ctx_पूर्णांक_flags(काष्ठा s5p_mfc_ctx *ctx)
अणु
	ctx->पूर्णांक_cond = 0;
	ctx->पूर्णांक_type = 0;
	ctx->पूर्णांक_err = 0;
पूर्ण

