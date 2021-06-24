<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only
 *
 * Copyright तऊ 2018-2020 Intel Corporation
 */

#अगर_अघोषित __KMB_PLANE_H__
#घोषणा __KMB_PLANE_H__

#समावेश <drm/drm_fourcc.h>
#समावेश <drm/drm_plane.h>

#घोषणा LCD_INT_VL0_ERR ((LAYER0_DMA_FIFO_UNDERFLOW) | \
			(LAYER0_DMA_FIFO_OVERFLOW) | \
			(LAYER0_DMA_CB_FIFO_OVERFLOW) | \
			(LAYER0_DMA_CB_FIFO_UNDERFLOW) | \
			(LAYER0_DMA_CR_FIFO_OVERFLOW) | \
			(LAYER0_DMA_CR_FIFO_UNDERFLOW))

#घोषणा LCD_INT_VL1_ERR ((LAYER1_DMA_FIFO_UNDERFLOW) | \
			(LAYER1_DMA_FIFO_OVERFLOW) | \
			(LAYER1_DMA_CB_FIFO_OVERFLOW) | \
			(LAYER1_DMA_CB_FIFO_UNDERFLOW) | \
			(LAYER1_DMA_CR_FIFO_OVERFLOW) | \
			(LAYER1_DMA_CR_FIFO_UNDERFLOW))

#घोषणा LCD_INT_GL0_ERR (LAYER2_DMA_FIFO_OVERFLOW | LAYER2_DMA_FIFO_UNDERFLOW)
#घोषणा LCD_INT_GL1_ERR (LAYER3_DMA_FIFO_OVERFLOW | LAYER3_DMA_FIFO_UNDERFLOW)
#घोषणा LCD_INT_VL0 (LAYER0_DMA_DONE | LAYER0_DMA_IDLE | LCD_INT_VL0_ERR)
#घोषणा LCD_INT_VL1 (LAYER1_DMA_DONE | LAYER1_DMA_IDLE | LCD_INT_VL1_ERR)
#घोषणा LCD_INT_GL0 (LAYER2_DMA_DONE | LAYER2_DMA_IDLE | LCD_INT_GL0_ERR)
#घोषणा LCD_INT_GL1 (LAYER3_DMA_DONE | LAYER3_DMA_IDLE | LCD_INT_GL1_ERR)
#घोषणा LCD_INT_DMA_ERR (LCD_INT_VL0_ERR | LCD_INT_VL1_ERR \
		| LCD_INT_GL0_ERR | LCD_INT_GL1_ERR)

#घोषणा POSSIBLE_CRTCS 1
#घोषणा to_kmb_plane(x) container_of(x, काष्ठा kmb_plane, base_plane)

क्रमागत layer_id अणु
	LAYER_0,
	LAYER_1,
	LAYER_2,
	LAYER_3,
	/* KMB_MAX_PLANES */
पूर्ण;

#घोषणा KMB_MAX_PLANES 1

क्रमागत sub_plane_id अणु
	Y_PLANE,
	U_PLANE,
	V_PLANE,
	MAX_SUB_PLANES,
पूर्ण;

काष्ठा kmb_plane अणु
	काष्ठा drm_plane base_plane;
	अचिन्हित अक्षर id;
पूर्ण;

काष्ठा layer_status अणु
	bool disable;
	u32 ctrl;
पूर्ण;

काष्ठा kmb_plane *kmb_plane_init(काष्ठा drm_device *drm);
व्योम kmb_plane_destroy(काष्ठा drm_plane *plane);
#पूर्ण_अगर /* __KMB_PLANE_H__ */
