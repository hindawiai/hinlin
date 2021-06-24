<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2016 MediaTek Inc.
 * Author: Daniel Hsiao <daniel.hsiao@mediatek.com>
 *	Jungchang Tsao <jungchang.tsao@mediatek.com>
 *	Tअगरfany Lin <tअगरfany.lin@mediatek.com>
 */

#अगर_अघोषित _VENC_DRV_BASE_
#घोषणा _VENC_DRV_BASE_

#समावेश "mtk_vcodec_drv.h"

#समावेश "venc_drv_if.h"

काष्ठा venc_common_अगर अणु
	/**
	 * (*init)() - initialize driver
	 * @ctx:	[in] mtk v4l2 context
	 * @handle: [out] driver handle
	 */
	पूर्णांक (*init)(काष्ठा mtk_vcodec_ctx *ctx);

	/**
	 * (*encode)() - trigger encode
	 * @handle: [in] driver handle
	 * @opt: [in] encode option
	 * @frm_buf: [in] frame buffer to store input frame
	 * @bs_buf: [in] bitstream buffer to store output bitstream
	 * @result: [out] encode result
	 */
	पूर्णांक (*encode)(व्योम *handle, क्रमागत venc_start_opt opt,
		      काष्ठा venc_frm_buf *frm_buf,
		      काष्ठा mtk_vcodec_mem *bs_buf,
		      काष्ठा venc_करोne_result *result);

	/**
	 * (*set_param)() - set driver's parameter
	 * @handle: [in] driver handle
	 * @type: [in] parameter type
	 * @in: [in] buffer to store the parameter
	 */
	पूर्णांक (*set_param)(व्योम *handle, क्रमागत venc_set_param_type type,
			 काष्ठा venc_enc_param *in);

	/**
	 * (*deinit)() - deinitialize driver.
	 * @handle: [in] driver handle
	 */
	पूर्णांक (*deinit)(व्योम *handle);
पूर्ण;

#पूर्ण_अगर
