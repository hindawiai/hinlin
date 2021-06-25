<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2016 MediaTek Inc.
 * Author: PC Chen <pc.chen@mediatek.com>
 */

#अगर_अघोषित _VDEC_DRV_BASE_
#घोषणा _VDEC_DRV_BASE_

#समावेश "vdec_drv_if.h"

काष्ठा vdec_common_अगर अणु
	/**
	 * (*init)() - initialize decode driver
	 * @ctx     : [in] mtk v4l2 context
	 * @h_vdec  : [out] driver handle
	 */
	पूर्णांक (*init)(काष्ठा mtk_vcodec_ctx *ctx);

	/**
	 * (*decode)() - trigger decode
	 * @h_vdec  : [in] driver handle
	 * @bs      : [in] input bitstream
	 * @fb      : [in] frame buffer to store decoded frame
	 * @res_chg : [out] resolution change happen
	 */
	पूर्णांक (*decode)(व्योम *h_vdec, काष्ठा mtk_vcodec_mem *bs,
		      काष्ठा vdec_fb *fb, bool *res_chg);

	/**
	 * (*get_param)() - get driver's parameter
	 * @h_vdec : [in] driver handle
	 * @type   : [in] input parameter type
	 * @out    : [out] buffer to store query result
	 */
	पूर्णांक (*get_param)(व्योम *h_vdec, क्रमागत vdec_get_param_type type,
			 व्योम *out);

	/**
	 * (*deinit)() - deinitialize driver.
	 * @h_vdec : [in] driver handle to be deinit
	 */
	व्योम (*deinit)(व्योम *h_vdec);
पूर्ण;

#पूर्ण_अगर
