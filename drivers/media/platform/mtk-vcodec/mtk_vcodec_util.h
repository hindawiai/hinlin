<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
* Copyright (c) 2016 MediaTek Inc.
* Author: PC Chen <pc.chen@mediatek.com>
*	Tअगरfany Lin <tअगरfany.lin@mediatek.com>
*/

#अगर_अघोषित _MTK_VCODEC_UTIL_H_
#घोषणा _MTK_VCODEC_UTIL_H_

#समावेश <linux/types.h>
#समावेश <linux/dma-direction.h>

काष्ठा mtk_vcodec_mem अणु
	माप_प्रकार size;
	व्योम *va;
	dma_addr_t dma_addr;
पूर्ण;

काष्ठा mtk_vcodec_fb अणु
	माप_प्रकार size;
	dma_addr_t dma_addr;
पूर्ण;

काष्ठा mtk_vcodec_ctx;
काष्ठा mtk_vcodec_dev;

बाह्य पूर्णांक mtk_v4l2_dbg_level;
बाह्य bool mtk_vcodec_dbg;


#घोषणा mtk_v4l2_err(fmt, args...)                \
	pr_err("[MTK_V4L2][ERROR] %s:%d: " fmt "\n", __func__, __LINE__, \
	       ##args)

#घोषणा mtk_vcodec_err(h, fmt, args...)					\
	pr_err("[MTK_VCODEC][ERROR][%d]: %s() " fmt "\n",		\
	       ((काष्ठा mtk_vcodec_ctx *)h->ctx)->id, __func__, ##args)


#अगर defined(DEBUG)

#घोषणा mtk_v4l2_debug(level, fmt, args...)				 \
	करो अणु								 \
		अगर (mtk_v4l2_dbg_level >= level)			 \
			pr_info("[MTK_V4L2] level=%d %s(),%d: " fmt "\n",\
				level, __func__, __LINE__, ##args);	 \
	पूर्ण जबतक (0)

#घोषणा mtk_v4l2_debug_enter()  mtk_v4l2_debug(3, "+")
#घोषणा mtk_v4l2_debug_leave()  mtk_v4l2_debug(3, "-")

#घोषणा mtk_vcodec_debug(h, fmt, args...)				\
	करो अणु								\
		अगर (mtk_vcodec_dbg)					\
			pr_info("[MTK_VCODEC][%d]: %s() " fmt "\n",	\
				((काष्ठा mtk_vcodec_ctx *)h->ctx)->id, \
				__func__, ##args);			\
	पूर्ण जबतक (0)

#घोषणा mtk_vcodec_debug_enter(h)  mtk_vcodec_debug(h, "+")
#घोषणा mtk_vcodec_debug_leave(h)  mtk_vcodec_debug(h, "-")

#अन्यथा

#घोषणा mtk_v4l2_debug(level, fmt, args...) अणुपूर्ण
#घोषणा mtk_v4l2_debug_enter() अणुपूर्ण
#घोषणा mtk_v4l2_debug_leave() अणुपूर्ण

#घोषणा mtk_vcodec_debug(h, fmt, args...) अणुपूर्ण
#घोषणा mtk_vcodec_debug_enter(h) अणुपूर्ण
#घोषणा mtk_vcodec_debug_leave(h) अणुपूर्ण

#पूर्ण_अगर

व्योम __iomem *mtk_vcodec_get_reg_addr(काष्ठा mtk_vcodec_ctx *data,
				अचिन्हित पूर्णांक reg_idx);
पूर्णांक mtk_vcodec_mem_alloc(काष्ठा mtk_vcodec_ctx *data,
				काष्ठा mtk_vcodec_mem *mem);
व्योम mtk_vcodec_mem_मुक्त(काष्ठा mtk_vcodec_ctx *data,
				काष्ठा mtk_vcodec_mem *mem);
व्योम mtk_vcodec_set_curr_ctx(काष्ठा mtk_vcodec_dev *dev,
	काष्ठा mtk_vcodec_ctx *ctx);
काष्ठा mtk_vcodec_ctx *mtk_vcodec_get_curr_ctx(काष्ठा mtk_vcodec_dev *dev);

#पूर्ण_अगर /* _MTK_VCODEC_UTIL_H_ */
