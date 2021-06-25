<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2012 Samsung Electronics Co.Ltd
 * Authors:
 *	Eunchul Kim <chulspro.kim@samsung.com>
 *	Jinyoung Jeon <jy0.jeon@samsung.com>
 *	Sangmin Lee <lsmin.lee@samsung.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/component.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regmap.h>

#समावेश <drm/drm_fourcc.h>
#समावेश <drm/drm_prपूर्णांक.h>
#समावेश <drm/exynos_drm.h>

#समावेश "exynos_drm_drv.h"
#समावेश "exynos_drm_ipp.h"
#समावेश "regs-gsc.h"

/*
 * GSC stands क्रम General SCaler and
 * supports image scaler/rotator and input/output DMA operations.
 * input DMA पढ़ोs image data from the memory.
 * output DMA ग_लिखोs image data to memory.
 * GSC supports image rotation and image effect functions.
 */


#घोषणा GSC_MAX_CLOCKS	8
#घोषणा GSC_MAX_SRC		4
#घोषणा GSC_MAX_DST		16
#घोषणा GSC_RESET_TIMEOUT	50
#घोषणा GSC_BUF_STOP	1
#घोषणा GSC_BUF_START	2
#घोषणा GSC_REG_SZ		16
#घोषणा GSC_WIDTH_ITU_709	1280
#घोषणा GSC_SC_UP_MAX_RATIO		65536
#घोषणा GSC_SC_DOWN_RATIO_7_8		74898
#घोषणा GSC_SC_DOWN_RATIO_6_8		87381
#घोषणा GSC_SC_DOWN_RATIO_5_8		104857
#घोषणा GSC_SC_DOWN_RATIO_4_8		131072
#घोषणा GSC_SC_DOWN_RATIO_3_8		174762
#घोषणा GSC_SC_DOWN_RATIO_2_8		262144
#घोषणा GSC_CROP_MAX	8192
#घोषणा GSC_CROP_MIN	32
#घोषणा GSC_SCALE_MAX	4224
#घोषणा GSC_SCALE_MIN	32
#घोषणा GSC_COEF_RATIO	7
#घोषणा GSC_COEF_PHASE	9
#घोषणा GSC_COEF_ATTR	16
#घोषणा GSC_COEF_H_8T	8
#घोषणा GSC_COEF_V_4T	4
#घोषणा GSC_COEF_DEPTH	3
#घोषणा GSC_AUTOSUSPEND_DELAY		2000

#घोषणा get_gsc_context(dev)	dev_get_drvdata(dev)
#घोषणा gsc_पढ़ो(offset)		पढ़ोl(ctx->regs + (offset))
#घोषणा gsc_ग_लिखो(cfg, offset)	ग_लिखोl(cfg, ctx->regs + (offset))

/*
 * A काष्ठाure of scaler.
 *
 * @range: narrow, wide.
 * @pre_shfactor: pre sclaer shअगरt factor.
 * @pre_hratio: horizontal ratio of the prescaler.
 * @pre_vratio: vertical ratio of the prescaler.
 * @मुख्य_hratio: the मुख्य scaler's horizontal ratio.
 * @मुख्य_vratio: the मुख्य scaler's vertical ratio.
 */
काष्ठा gsc_scaler अणु
	bool	range;
	u32	pre_shfactor;
	u32	pre_hratio;
	u32	pre_vratio;
	अचिन्हित दीर्घ मुख्य_hratio;
	अचिन्हित दीर्घ मुख्य_vratio;
पूर्ण;

/*
 * A काष्ठाure of gsc context.
 *
 * @regs_res: रेजिस्टर resources.
 * @regs: memory mapped io रेजिस्टरs.
 * @gsc_clk: gsc gate घड़ी.
 * @sc: scaler infomations.
 * @id: gsc id.
 * @irq: irq number.
 * @rotation: supports rotation of src.
 */
काष्ठा gsc_context अणु
	काष्ठा exynos_drm_ipp ipp;
	काष्ठा drm_device *drm_dev;
	व्योम		*dma_priv;
	काष्ठा device	*dev;
	काष्ठा exynos_drm_ipp_task	*task;
	काष्ठा exynos_drm_ipp_क्रमmats	*क्रमmats;
	अचिन्हित पूर्णांक			num_क्रमmats;

	काष्ठा resource	*regs_res;
	व्योम __iomem	*regs;
	स्थिर अक्षर	**clk_names;
	काष्ठा clk	*घड़ीs[GSC_MAX_CLOCKS];
	पूर्णांक		num_घड़ीs;
	काष्ठा gsc_scaler	sc;
	पूर्णांक	id;
	पूर्णांक	irq;
	bool	rotation;
पूर्ण;

/**
 * काष्ठा gsc_driverdata - per device type driver data क्रम init समय.
 *
 * @limits: picture size limits array
 * @num_limits: number of items in the aक्रमementioned array
 * @clk_names: names of घड़ीs needed by this variant
 * @num_घड़ीs: the number of घड़ीs needed by this variant
 */
काष्ठा gsc_driverdata अणु
	स्थिर काष्ठा drm_exynos_ipp_limit *limits;
	पूर्णांक		num_limits;
	स्थिर अक्षर	*clk_names[GSC_MAX_CLOCKS];
	पूर्णांक		num_घड़ीs;
पूर्ण;

/* 8-tap Filter Coefficient */
अटल स्थिर पूर्णांक h_coef_8t[GSC_COEF_RATIO][GSC_COEF_ATTR][GSC_COEF_H_8T] = अणु
	अणु	/* Ratio <= 65536 (~8:8) */
		अणु  0,  0,   0, 128,   0,   0,  0,  0 पूर्ण,
		अणु -1,  2,  -6, 127,   7,  -2,  1,  0 पूर्ण,
		अणु -1,  4, -12, 125,  16,  -5,  1,  0 पूर्ण,
		अणु -1,  5, -15, 120,  25,  -8,  2,  0 पूर्ण,
		अणु -1,  6, -18, 114,  35, -10,  3, -1 पूर्ण,
		अणु -1,  6, -20, 107,  46, -13,  4, -1 पूर्ण,
		अणु -2,  7, -21,  99,  57, -16,  5, -1 पूर्ण,
		अणु -1,  6, -20,  89,  68, -18,  5, -1 पूर्ण,
		अणु -1,  6, -20,  79,  79, -20,  6, -1 पूर्ण,
		अणु -1,  5, -18,  68,  89, -20,  6, -1 पूर्ण,
		अणु -1,  5, -16,  57,  99, -21,  7, -2 पूर्ण,
		अणु -1,  4, -13,  46, 107, -20,  6, -1 पूर्ण,
		अणु -1,  3, -10,  35, 114, -18,  6, -1 पूर्ण,
		अणु  0,  2,  -8,  25, 120, -15,  5, -1 पूर्ण,
		अणु  0,  1,  -5,  16, 125, -12,  4, -1 पूर्ण,
		अणु  0,  1,  -2,   7, 127,  -6,  2, -1 पूर्ण
	पूर्ण, अणु	/* 65536 < Ratio <= 74898 (~8:7) */
		अणु  3, -8,  14, 111,  13,  -8,  3,  0 पूर्ण,
		अणु  2, -6,   7, 112,  21, -10,  3, -1 पूर्ण,
		अणु  2, -4,   1, 110,  28, -12,  4, -1 पूर्ण,
		अणु  1, -2,  -3, 106,  36, -13,  4, -1 पूर्ण,
		अणु  1, -1,  -7, 103,  44, -15,  4, -1 पूर्ण,
		अणु  1,  1, -11,  97,  53, -16,  4, -1 पूर्ण,
		अणु  0,  2, -13,  91,  61, -16,  4, -1 पूर्ण,
		अणु  0,  3, -15,  85,  69, -17,  4, -1 पूर्ण,
		अणु  0,  3, -16,  77,  77, -16,  3,  0 पूर्ण,
		अणु -1,  4, -17,  69,  85, -15,  3,  0 पूर्ण,
		अणु -1,  4, -16,  61,  91, -13,  2,  0 पूर्ण,
		अणु -1,  4, -16,  53,  97, -11,  1,  1 पूर्ण,
		अणु -1,  4, -15,  44, 103,  -7, -1,  1 पूर्ण,
		अणु -1,  4, -13,  36, 106,  -3, -2,  1 पूर्ण,
		अणु -1,  4, -12,  28, 110,   1, -4,  2 पूर्ण,
		अणु -1,  3, -10,  21, 112,   7, -6,  2 पूर्ण
	पूर्ण, अणु	/* 74898 < Ratio <= 87381 (~8:6) */
		अणु 2, -11,  25,  96, 25, -11,   2,  0 पूर्ण,
		अणु 2, -10,  19,  96, 31, -12,   2,  0 पूर्ण,
		अणु 2,  -9,  14,  94, 37, -12,   2,  0 पूर्ण,
		अणु 2,  -8,  10,  92, 43, -12,   1,  0 पूर्ण,
		अणु 2,  -7,   5,  90, 49, -12,   1,  0 पूर्ण,
		अणु 2,  -5,   1,  86, 55, -12,   0,  1 पूर्ण,
		अणु 2,  -4,  -2,  82, 61, -11,  -1,  1 पूर्ण,
		अणु 1,  -3,  -5,  77, 67,  -9,  -1,  1 पूर्ण,
		अणु 1,  -2,  -7,  72, 72,  -7,  -2,  1 पूर्ण,
		अणु 1,  -1,  -9,  67, 77,  -5,  -3,  1 पूर्ण,
		अणु 1,  -1, -11,  61, 82,  -2,  -4,  2 पूर्ण,
		अणु 1,   0, -12,  55, 86,   1,  -5,  2 पूर्ण,
		अणु 0,   1, -12,  49, 90,   5,  -7,  2 पूर्ण,
		अणु 0,   1, -12,  43, 92,  10,  -8,  2 पूर्ण,
		अणु 0,   2, -12,  37, 94,  14,  -9,  2 पूर्ण,
		अणु 0,   2, -12,  31, 96,  19, -10,  2 पूर्ण
	पूर्ण, अणु	/* 87381 < Ratio <= 104857 (~8:5) */
		अणु -1,  -8, 33,  80, 33,  -8,  -1,  0 पूर्ण,
		अणु -1,  -8, 28,  80, 37,  -7,  -2,  1 पूर्ण,
		अणु  0,  -8, 24,  79, 41,  -7,  -2,  1 पूर्ण,
		अणु  0,  -8, 20,  78, 46,  -6,  -3,  1 पूर्ण,
		अणु  0,  -8, 16,  76, 50,  -4,  -3,  1 पूर्ण,
		अणु  0,  -7, 13,  74, 54,  -3,  -4,  1 पूर्ण,
		अणु  1,  -7, 10,  71, 58,  -1,  -5,  1 पूर्ण,
		अणु  1,  -6,  6,  68, 62,   1,  -5,  1 पूर्ण,
		अणु  1,  -6,  4,  65, 65,   4,  -6,  1 पूर्ण,
		अणु  1,  -5,  1,  62, 68,   6,  -6,  1 पूर्ण,
		अणु  1,  -5, -1,  58, 71,  10,  -7,  1 पूर्ण,
		अणु  1,  -4, -3,  54, 74,  13,  -7,  0 पूर्ण,
		अणु  1,  -3, -4,  50, 76,  16,  -8,  0 पूर्ण,
		अणु  1,  -3, -6,  46, 78,  20,  -8,  0 पूर्ण,
		अणु  1,  -2, -7,  41, 79,  24,  -8,  0 पूर्ण,
		अणु  1,  -2, -7,  37, 80,  28,  -8, -1 पूर्ण
	पूर्ण, अणु	/* 104857 < Ratio <= 131072 (~8:4) */
		अणु -3,   0, 35,  64, 35,   0,  -3,  0 पूर्ण,
		अणु -3,  -1, 32,  64, 38,   1,  -3,  0 पूर्ण,
		अणु -2,  -2, 29,  63, 41,   2,  -3,  0 पूर्ण,
		अणु -2,  -3, 27,  63, 43,   4,  -4,  0 पूर्ण,
		अणु -2,  -3, 24,  61, 46,   6,  -4,  0 पूर्ण,
		अणु -2,  -3, 21,  60, 49,   7,  -4,  0 पूर्ण,
		अणु -1,  -4, 19,  59, 51,   9,  -4, -1 पूर्ण,
		अणु -1,  -4, 16,  57, 53,  12,  -4, -1 पूर्ण,
		अणु -1,  -4, 14,  55, 55,  14,  -4, -1 पूर्ण,
		अणु -1,  -4, 12,  53, 57,  16,  -4, -1 पूर्ण,
		अणु -1,  -4,  9,  51, 59,  19,  -4, -1 पूर्ण,
		अणु  0,  -4,  7,  49, 60,  21,  -3, -2 पूर्ण,
		अणु  0,  -4,  6,  46, 61,  24,  -3, -2 पूर्ण,
		अणु  0,  -4,  4,  43, 63,  27,  -3, -2 पूर्ण,
		अणु  0,  -3,  2,  41, 63,  29,  -2, -2 पूर्ण,
		अणु  0,  -3,  1,  38, 64,  32,  -1, -3 पूर्ण
	पूर्ण, अणु	/* 131072 < Ratio <= 174762 (~8:3) */
		अणु -1,   8, 33,  48, 33,   8,  -1,  0 पूर्ण,
		अणु -1,   7, 31,  49, 35,   9,  -1, -1 पूर्ण,
		अणु -1,   6, 30,  49, 36,  10,  -1, -1 पूर्ण,
		अणु -1,   5, 28,  48, 38,  12,  -1, -1 पूर्ण,
		अणु -1,   4, 26,  48, 39,  13,   0, -1 पूर्ण,
		अणु -1,   3, 24,  47, 41,  15,   0, -1 पूर्ण,
		अणु -1,   2, 23,  47, 42,  16,   0, -1 पूर्ण,
		अणु -1,   2, 21,  45, 43,  18,   1, -1 पूर्ण,
		अणु -1,   1, 19,  45, 45,  19,   1, -1 पूर्ण,
		अणु -1,   1, 18,  43, 45,  21,   2, -1 पूर्ण,
		अणु -1,   0, 16,  42, 47,  23,   2, -1 पूर्ण,
		अणु -1,   0, 15,  41, 47,  24,   3, -1 पूर्ण,
		अणु -1,   0, 13,  39, 48,  26,   4, -1 पूर्ण,
		अणु -1,  -1, 12,  38, 48,  28,   5, -1 पूर्ण,
		अणु -1,  -1, 10,  36, 49,  30,   6, -1 पूर्ण,
		अणु -1,  -1,  9,  35, 49,  31,   7, -1 पूर्ण
	पूर्ण, अणु	/* 174762 < Ratio <= 262144 (~8:2) */
		अणु  2,  13, 30,  38, 30,  13,   2,  0 पूर्ण,
		अणु  2,  12, 29,  38, 30,  14,   3,  0 पूर्ण,
		अणु  2,  11, 28,  38, 31,  15,   3,  0 पूर्ण,
		अणु  2,  10, 26,  38, 32,  16,   4,  0 पूर्ण,
		अणु  1,  10, 26,  37, 33,  17,   4,  0 पूर्ण,
		अणु  1,   9, 24,  37, 34,  18,   5,  0 पूर्ण,
		अणु  1,   8, 24,  37, 34,  19,   5,  0 पूर्ण,
		अणु  1,   7, 22,  36, 35,  20,   6,  1 पूर्ण,
		अणु  1,   6, 21,  36, 36,  21,   6,  1 पूर्ण,
		अणु  1,   6, 20,  35, 36,  22,   7,  1 पूर्ण,
		अणु  0,   5, 19,  34, 37,  24,   8,  1 पूर्ण,
		अणु  0,   5, 18,  34, 37,  24,   9,  1 पूर्ण,
		अणु  0,   4, 17,  33, 37,  26,  10,  1 पूर्ण,
		अणु  0,   4, 16,  32, 38,  26,  10,  2 पूर्ण,
		अणु  0,   3, 15,  31, 38,  28,  11,  2 पूर्ण,
		अणु  0,   3, 14,  30, 38,  29,  12,  2 पूर्ण
	पूर्ण
पूर्ण;

/* 4-tap Filter Coefficient */
अटल स्थिर पूर्णांक v_coef_4t[GSC_COEF_RATIO][GSC_COEF_ATTR][GSC_COEF_V_4T] = अणु
	अणु	/* Ratio <= 65536 (~8:8) */
		अणु  0, 128,   0,  0 पूर्ण,
		अणु -4, 127,   5,  0 पूर्ण,
		अणु -6, 124,  11, -1 पूर्ण,
		अणु -8, 118,  19, -1 पूर्ण,
		अणु -8, 111,  27, -2 पूर्ण,
		अणु -8, 102,  37, -3 पूर्ण,
		अणु -8,  92,  48, -4 पूर्ण,
		अणु -7,  81,  59, -5 पूर्ण,
		अणु -6,  70,  70, -6 पूर्ण,
		अणु -5,  59,  81, -7 पूर्ण,
		अणु -4,  48,  92, -8 पूर्ण,
		अणु -3,  37, 102, -8 पूर्ण,
		अणु -2,  27, 111, -8 पूर्ण,
		अणु -1,  19, 118, -8 पूर्ण,
		अणु -1,  11, 124, -6 पूर्ण,
		अणु  0,   5, 127, -4 पूर्ण
	पूर्ण, अणु	/* 65536 < Ratio <= 74898 (~8:7) */
		अणु  8, 112,   8,  0 पूर्ण,
		अणु  4, 111,  14, -1 पूर्ण,
		अणु  1, 109,  20, -2 पूर्ण,
		अणु -2, 105,  27, -2 पूर्ण,
		अणु -3, 100,  34, -3 पूर्ण,
		अणु -5,  93,  43, -3 पूर्ण,
		अणु -5,  86,  51, -4 पूर्ण,
		अणु -5,  77,  60, -4 पूर्ण,
		अणु -5,  69,  69, -5 पूर्ण,
		अणु -4,  60,  77, -5 पूर्ण,
		अणु -4,  51,  86, -5 पूर्ण,
		अणु -3,  43,  93, -5 पूर्ण,
		अणु -3,  34, 100, -3 पूर्ण,
		अणु -2,  27, 105, -2 पूर्ण,
		अणु -2,  20, 109,  1 पूर्ण,
		अणु -1,  14, 111,  4 पूर्ण
	पूर्ण, अणु	/* 74898 < Ratio <= 87381 (~8:6) */
		अणु 16,  96,  16,  0 पूर्ण,
		अणु 12,  97,  21, -2 पूर्ण,
		अणु  8,  96,  26, -2 पूर्ण,
		अणु  5,  93,  32, -2 पूर्ण,
		अणु  2,  89,  39, -2 पूर्ण,
		अणु  0,  84,  46, -2 पूर्ण,
		अणु -1,  79,  53, -3 पूर्ण,
		अणु -2,  73,  59, -2 पूर्ण,
		अणु -2,  66,  66, -2 पूर्ण,
		अणु -2,  59,  73, -2 पूर्ण,
		अणु -3,  53,  79, -1 पूर्ण,
		अणु -2,  46,  84,  0 पूर्ण,
		अणु -2,  39,  89,  2 पूर्ण,
		अणु -2,  32,  93,  5 पूर्ण,
		अणु -2,  26,  96,  8 पूर्ण,
		अणु -2,  21,  97, 12 पूर्ण
	पूर्ण, अणु	/* 87381 < Ratio <= 104857 (~8:5) */
		अणु 22,  84,  22,  0 पूर्ण,
		अणु 18,  85,  26, -1 पूर्ण,
		अणु 14,  84,  31, -1 पूर्ण,
		अणु 11,  82,  36, -1 पूर्ण,
		अणु  8,  79,  42, -1 पूर्ण,
		अणु  6,  76,  47, -1 पूर्ण,
		अणु  4,  72,  52,  0 पूर्ण,
		अणु  2,  68,  58,  0 पूर्ण,
		अणु  1,  63,  63,  1 पूर्ण,
		अणु  0,  58,  68,  2 पूर्ण,
		अणु  0,  52,  72,  4 पूर्ण,
		अणु -1,  47,  76,  6 पूर्ण,
		अणु -1,  42,  79,  8 पूर्ण,
		अणु -1,  36,  82, 11 पूर्ण,
		अणु -1,  31,  84, 14 पूर्ण,
		अणु -1,  26,  85, 18 पूर्ण
	पूर्ण, अणु	/* 104857 < Ratio <= 131072 (~8:4) */
		अणु 26,  76,  26,  0 पूर्ण,
		अणु 22,  76,  30,  0 पूर्ण,
		अणु 19,  75,  34,  0 पूर्ण,
		अणु 16,  73,  38,  1 पूर्ण,
		अणु 13,  71,  43,  1 पूर्ण,
		अणु 10,  69,  47,  2 पूर्ण,
		अणु  8,  66,  51,  3 पूर्ण,
		अणु  6,  63,  55,  4 पूर्ण,
		अणु  5,  59,  59,  5 पूर्ण,
		अणु  4,  55,  63,  6 पूर्ण,
		अणु  3,  51,  66,  8 पूर्ण,
		अणु  2,  47,  69, 10 पूर्ण,
		अणु  1,  43,  71, 13 पूर्ण,
		अणु  1,  38,  73, 16 पूर्ण,
		अणु  0,  34,  75, 19 पूर्ण,
		अणु  0,  30,  76, 22 पूर्ण
	पूर्ण, अणु	/* 131072 < Ratio <= 174762 (~8:3) */
		अणु 29,  70,  29,  0 पूर्ण,
		अणु 26,  68,  32,  2 पूर्ण,
		अणु 23,  67,  36,  2 पूर्ण,
		अणु 20,  66,  39,  3 पूर्ण,
		अणु 17,  65,  43,  3 पूर्ण,
		अणु 15,  63,  46,  4 पूर्ण,
		अणु 12,  61,  50,  5 पूर्ण,
		अणु 10,  58,  53,  7 पूर्ण,
		अणु  8,  56,  56,  8 पूर्ण,
		अणु  7,  53,  58, 10 पूर्ण,
		अणु  5,  50,  61, 12 पूर्ण,
		अणु  4,  46,  63, 15 पूर्ण,
		अणु  3,  43,  65, 17 पूर्ण,
		अणु  3,  39,  66, 20 पूर्ण,
		अणु  2,  36,  67, 23 पूर्ण,
		अणु  2,  32,  68, 26 पूर्ण
	पूर्ण, अणु	/* 174762 < Ratio <= 262144 (~8:2) */
		अणु 32,  64,  32,  0 पूर्ण,
		अणु 28,  63,  34,  3 पूर्ण,
		अणु 25,  62,  37,  4 पूर्ण,
		अणु 22,  62,  40,  4 पूर्ण,
		अणु 19,  61,  43,  5 पूर्ण,
		अणु 17,  59,  46,  6 पूर्ण,
		अणु 15,  58,  48,  7 पूर्ण,
		अणु 13,  55,  51,  9 पूर्ण,
		अणु 11,  53,  53, 11 पूर्ण,
		अणु  9,  51,  55, 13 पूर्ण,
		अणु  7,  48,  58, 15 पूर्ण,
		अणु  6,  46,  59, 17 पूर्ण,
		अणु  5,  43,  61, 19 पूर्ण,
		अणु  4,  40,  62, 22 पूर्ण,
		अणु  4,  37,  62, 25 पूर्ण,
		अणु  3,  34,  63, 28 पूर्ण
	पूर्ण
पूर्ण;

अटल पूर्णांक gsc_sw_reset(काष्ठा gsc_context *ctx)
अणु
	u32 cfg;
	पूर्णांक count = GSC_RESET_TIMEOUT;

	/* s/w reset */
	cfg = (GSC_SW_RESET_SRESET);
	gsc_ग_लिखो(cfg, GSC_SW_RESET);

	/* रुको s/w reset complete */
	जबतक (count--) अणु
		cfg = gsc_पढ़ो(GSC_SW_RESET);
		अगर (!cfg)
			अवरोध;
		usleep_range(1000, 2000);
	पूर्ण

	अगर (cfg) अणु
		DRM_DEV_ERROR(ctx->dev, "failed to reset gsc h/w.\n");
		वापस -EBUSY;
	पूर्ण

	/* reset sequence */
	cfg = gsc_पढ़ो(GSC_IN_BASE_ADDR_Y_MASK);
	cfg |= (GSC_IN_BASE_ADDR_MASK |
		GSC_IN_BASE_ADDR_PINGPONG(0));
	gsc_ग_लिखो(cfg, GSC_IN_BASE_ADDR_Y_MASK);
	gsc_ग_लिखो(cfg, GSC_IN_BASE_ADDR_CB_MASK);
	gsc_ग_लिखो(cfg, GSC_IN_BASE_ADDR_CR_MASK);

	cfg = gsc_पढ़ो(GSC_OUT_BASE_ADDR_Y_MASK);
	cfg |= (GSC_OUT_BASE_ADDR_MASK |
		GSC_OUT_BASE_ADDR_PINGPONG(0));
	gsc_ग_लिखो(cfg, GSC_OUT_BASE_ADDR_Y_MASK);
	gsc_ग_लिखो(cfg, GSC_OUT_BASE_ADDR_CB_MASK);
	gsc_ग_लिखो(cfg, GSC_OUT_BASE_ADDR_CR_MASK);

	वापस 0;
पूर्ण

अटल व्योम gsc_handle_irq(काष्ठा gsc_context *ctx, bool enable,
		bool overflow, bool करोne)
अणु
	u32 cfg;

	DRM_DEV_DEBUG_KMS(ctx->dev, "enable[%d]overflow[%d]level[%d]\n",
			  enable, overflow, करोne);

	cfg = gsc_पढ़ो(GSC_IRQ);
	cfg |= (GSC_IRQ_OR_MASK | GSC_IRQ_FRMDONE_MASK);

	अगर (enable)
		cfg |= GSC_IRQ_ENABLE;
	अन्यथा
		cfg &= ~GSC_IRQ_ENABLE;

	अगर (overflow)
		cfg &= ~GSC_IRQ_OR_MASK;
	अन्यथा
		cfg |= GSC_IRQ_OR_MASK;

	अगर (करोne)
		cfg &= ~GSC_IRQ_FRMDONE_MASK;
	अन्यथा
		cfg |= GSC_IRQ_FRMDONE_MASK;

	gsc_ग_लिखो(cfg, GSC_IRQ);
पूर्ण


अटल व्योम gsc_src_set_fmt(काष्ठा gsc_context *ctx, u32 fmt, bool tiled)
अणु
	u32 cfg;

	DRM_DEV_DEBUG_KMS(ctx->dev, "fmt[0x%x]\n", fmt);

	cfg = gsc_पढ़ो(GSC_IN_CON);
	cfg &= ~(GSC_IN_RGB_TYPE_MASK | GSC_IN_YUV422_1P_ORDER_MASK |
		 GSC_IN_CHROMA_ORDER_MASK | GSC_IN_FORMAT_MASK |
		 GSC_IN_TILE_TYPE_MASK | GSC_IN_TILE_MODE |
		 GSC_IN_CHROM_STRIDE_SEL_MASK | GSC_IN_RB_SWAP_MASK);

	चयन (fmt) अणु
	हाल DRM_FORMAT_RGB565:
		cfg |= GSC_IN_RGB565;
		अवरोध;
	हाल DRM_FORMAT_XRGB8888:
	हाल DRM_FORMAT_ARGB8888:
		cfg |= GSC_IN_XRGB8888;
		अवरोध;
	हाल DRM_FORMAT_BGRX8888:
		cfg |= (GSC_IN_XRGB8888 | GSC_IN_RB_SWAP);
		अवरोध;
	हाल DRM_FORMAT_YUYV:
		cfg |= (GSC_IN_YUV422_1P |
			GSC_IN_YUV422_1P_ORDER_LSB_Y |
			GSC_IN_CHROMA_ORDER_CBCR);
		अवरोध;
	हाल DRM_FORMAT_YVYU:
		cfg |= (GSC_IN_YUV422_1P |
			GSC_IN_YUV422_1P_ORDER_LSB_Y |
			GSC_IN_CHROMA_ORDER_CRCB);
		अवरोध;
	हाल DRM_FORMAT_UYVY:
		cfg |= (GSC_IN_YUV422_1P |
			GSC_IN_YUV422_1P_OEDER_LSB_C |
			GSC_IN_CHROMA_ORDER_CBCR);
		अवरोध;
	हाल DRM_FORMAT_VYUY:
		cfg |= (GSC_IN_YUV422_1P |
			GSC_IN_YUV422_1P_OEDER_LSB_C |
			GSC_IN_CHROMA_ORDER_CRCB);
		अवरोध;
	हाल DRM_FORMAT_NV21:
		cfg |= (GSC_IN_CHROMA_ORDER_CRCB | GSC_IN_YUV420_2P);
		अवरोध;
	हाल DRM_FORMAT_NV61:
		cfg |= (GSC_IN_CHROMA_ORDER_CRCB | GSC_IN_YUV422_2P);
		अवरोध;
	हाल DRM_FORMAT_YUV422:
		cfg |= GSC_IN_YUV422_3P;
		अवरोध;
	हाल DRM_FORMAT_YUV420:
		cfg |= (GSC_IN_CHROMA_ORDER_CBCR | GSC_IN_YUV420_3P);
		अवरोध;
	हाल DRM_FORMAT_YVU420:
		cfg |= (GSC_IN_CHROMA_ORDER_CRCB | GSC_IN_YUV420_3P);
		अवरोध;
	हाल DRM_FORMAT_NV12:
		cfg |= (GSC_IN_CHROMA_ORDER_CBCR | GSC_IN_YUV420_2P);
		अवरोध;
	हाल DRM_FORMAT_NV16:
		cfg |= (GSC_IN_CHROMA_ORDER_CBCR | GSC_IN_YUV422_2P);
		अवरोध;
	पूर्ण

	अगर (tiled)
		cfg |= (GSC_IN_TILE_C_16x8 | GSC_IN_TILE_MODE);

	gsc_ग_लिखो(cfg, GSC_IN_CON);
पूर्ण

अटल व्योम gsc_src_set_transf(काष्ठा gsc_context *ctx, अचिन्हित पूर्णांक rotation)
अणु
	अचिन्हित पूर्णांक degree = rotation & DRM_MODE_ROTATE_MASK;
	u32 cfg;

	cfg = gsc_पढ़ो(GSC_IN_CON);
	cfg &= ~GSC_IN_ROT_MASK;

	चयन (degree) अणु
	हाल DRM_MODE_ROTATE_0:
		अगर (rotation & DRM_MODE_REFLECT_X)
			cfg |= GSC_IN_ROT_XFLIP;
		अगर (rotation & DRM_MODE_REFLECT_Y)
			cfg |= GSC_IN_ROT_YFLIP;
		अवरोध;
	हाल DRM_MODE_ROTATE_90:
		cfg |= GSC_IN_ROT_90;
		अगर (rotation & DRM_MODE_REFLECT_X)
			cfg |= GSC_IN_ROT_XFLIP;
		अगर (rotation & DRM_MODE_REFLECT_Y)
			cfg |= GSC_IN_ROT_YFLIP;
		अवरोध;
	हाल DRM_MODE_ROTATE_180:
		cfg |= GSC_IN_ROT_180;
		अगर (rotation & DRM_MODE_REFLECT_X)
			cfg &= ~GSC_IN_ROT_XFLIP;
		अगर (rotation & DRM_MODE_REFLECT_Y)
			cfg &= ~GSC_IN_ROT_YFLIP;
		अवरोध;
	हाल DRM_MODE_ROTATE_270:
		cfg |= GSC_IN_ROT_270;
		अगर (rotation & DRM_MODE_REFLECT_X)
			cfg &= ~GSC_IN_ROT_XFLIP;
		अगर (rotation & DRM_MODE_REFLECT_Y)
			cfg &= ~GSC_IN_ROT_YFLIP;
		अवरोध;
	पूर्ण

	gsc_ग_लिखो(cfg, GSC_IN_CON);

	ctx->rotation = (cfg & GSC_IN_ROT_90) ? 1 : 0;
पूर्ण

अटल व्योम gsc_src_set_size(काष्ठा gsc_context *ctx,
			     काष्ठा exynos_drm_ipp_buffer *buf)
अणु
	काष्ठा gsc_scaler *sc = &ctx->sc;
	u32 cfg;

	/* pixel offset */
	cfg = (GSC_SRCIMG_OFFSET_X(buf->rect.x) |
		GSC_SRCIMG_OFFSET_Y(buf->rect.y));
	gsc_ग_लिखो(cfg, GSC_SRCIMG_OFFSET);

	/* cropped size */
	cfg = (GSC_CROPPED_WIDTH(buf->rect.w) |
		GSC_CROPPED_HEIGHT(buf->rect.h));
	gsc_ग_लिखो(cfg, GSC_CROPPED_SIZE);

	/* original size */
	cfg = gsc_पढ़ो(GSC_SRCIMG_SIZE);
	cfg &= ~(GSC_SRCIMG_HEIGHT_MASK |
		GSC_SRCIMG_WIDTH_MASK);

	cfg |= (GSC_SRCIMG_WIDTH(buf->buf.pitch[0] / buf->क्रमmat->cpp[0]) |
		GSC_SRCIMG_HEIGHT(buf->buf.height));

	gsc_ग_लिखो(cfg, GSC_SRCIMG_SIZE);

	cfg = gsc_पढ़ो(GSC_IN_CON);
	cfg &= ~GSC_IN_RGB_TYPE_MASK;

	अगर (buf->rect.w >= GSC_WIDTH_ITU_709)
		अगर (sc->range)
			cfg |= GSC_IN_RGB_HD_WIDE;
		अन्यथा
			cfg |= GSC_IN_RGB_HD_NARROW;
	अन्यथा
		अगर (sc->range)
			cfg |= GSC_IN_RGB_SD_WIDE;
		अन्यथा
			cfg |= GSC_IN_RGB_SD_NARROW;

	gsc_ग_लिखो(cfg, GSC_IN_CON);
पूर्ण

अटल व्योम gsc_src_set_buf_seq(काष्ठा gsc_context *ctx, u32 buf_id,
			       bool enqueue)
अणु
	bool masked = !enqueue;
	u32 cfg;
	u32 mask = 0x00000001 << buf_id;

	/* mask रेजिस्टर set */
	cfg = gsc_पढ़ो(GSC_IN_BASE_ADDR_Y_MASK);

	/* sequence id */
	cfg &= ~mask;
	cfg |= masked << buf_id;
	gsc_ग_लिखो(cfg, GSC_IN_BASE_ADDR_Y_MASK);
	gsc_ग_लिखो(cfg, GSC_IN_BASE_ADDR_CB_MASK);
	gsc_ग_लिखो(cfg, GSC_IN_BASE_ADDR_CR_MASK);
पूर्ण

अटल व्योम gsc_src_set_addr(काष्ठा gsc_context *ctx, u32 buf_id,
			    काष्ठा exynos_drm_ipp_buffer *buf)
अणु
	/* address रेजिस्टर set */
	gsc_ग_लिखो(buf->dma_addr[0], GSC_IN_BASE_ADDR_Y(buf_id));
	gsc_ग_लिखो(buf->dma_addr[1], GSC_IN_BASE_ADDR_CB(buf_id));
	gsc_ग_लिखो(buf->dma_addr[2], GSC_IN_BASE_ADDR_CR(buf_id));

	gsc_src_set_buf_seq(ctx, buf_id, true);
पूर्ण

अटल व्योम gsc_dst_set_fmt(काष्ठा gsc_context *ctx, u32 fmt, bool tiled)
अणु
	u32 cfg;

	DRM_DEV_DEBUG_KMS(ctx->dev, "fmt[0x%x]\n", fmt);

	cfg = gsc_पढ़ो(GSC_OUT_CON);
	cfg &= ~(GSC_OUT_RGB_TYPE_MASK | GSC_OUT_YUV422_1P_ORDER_MASK |
		 GSC_OUT_CHROMA_ORDER_MASK | GSC_OUT_FORMAT_MASK |
		 GSC_OUT_CHROM_STRIDE_SEL_MASK | GSC_OUT_RB_SWAP_MASK |
		 GSC_OUT_GLOBAL_ALPHA_MASK);

	चयन (fmt) अणु
	हाल DRM_FORMAT_RGB565:
		cfg |= GSC_OUT_RGB565;
		अवरोध;
	हाल DRM_FORMAT_ARGB8888:
	हाल DRM_FORMAT_XRGB8888:
		cfg |= (GSC_OUT_XRGB8888 | GSC_OUT_GLOBAL_ALPHA(0xff));
		अवरोध;
	हाल DRM_FORMAT_BGRX8888:
		cfg |= (GSC_OUT_XRGB8888 | GSC_OUT_RB_SWAP);
		अवरोध;
	हाल DRM_FORMAT_YUYV:
		cfg |= (GSC_OUT_YUV422_1P |
			GSC_OUT_YUV422_1P_ORDER_LSB_Y |
			GSC_OUT_CHROMA_ORDER_CBCR);
		अवरोध;
	हाल DRM_FORMAT_YVYU:
		cfg |= (GSC_OUT_YUV422_1P |
			GSC_OUT_YUV422_1P_ORDER_LSB_Y |
			GSC_OUT_CHROMA_ORDER_CRCB);
		अवरोध;
	हाल DRM_FORMAT_UYVY:
		cfg |= (GSC_OUT_YUV422_1P |
			GSC_OUT_YUV422_1P_OEDER_LSB_C |
			GSC_OUT_CHROMA_ORDER_CBCR);
		अवरोध;
	हाल DRM_FORMAT_VYUY:
		cfg |= (GSC_OUT_YUV422_1P |
			GSC_OUT_YUV422_1P_OEDER_LSB_C |
			GSC_OUT_CHROMA_ORDER_CRCB);
		अवरोध;
	हाल DRM_FORMAT_NV21:
		cfg |= (GSC_OUT_CHROMA_ORDER_CRCB | GSC_OUT_YUV420_2P);
		अवरोध;
	हाल DRM_FORMAT_NV61:
		cfg |= (GSC_OUT_CHROMA_ORDER_CRCB | GSC_OUT_YUV422_2P);
		अवरोध;
	हाल DRM_FORMAT_YUV422:
		cfg |= GSC_OUT_YUV422_3P;
		अवरोध;
	हाल DRM_FORMAT_YUV420:
		cfg |= (GSC_OUT_CHROMA_ORDER_CBCR | GSC_OUT_YUV420_3P);
		अवरोध;
	हाल DRM_FORMAT_YVU420:
		cfg |= (GSC_OUT_CHROMA_ORDER_CRCB | GSC_OUT_YUV420_3P);
		अवरोध;
	हाल DRM_FORMAT_NV12:
		cfg |= (GSC_OUT_CHROMA_ORDER_CBCR | GSC_OUT_YUV420_2P);
		अवरोध;
	हाल DRM_FORMAT_NV16:
		cfg |= (GSC_OUT_CHROMA_ORDER_CBCR | GSC_OUT_YUV422_2P);
		अवरोध;
	पूर्ण

	अगर (tiled)
		cfg |= (GSC_IN_TILE_C_16x8 | GSC_OUT_TILE_MODE);

	gsc_ग_लिखो(cfg, GSC_OUT_CON);
पूर्ण

अटल पूर्णांक gsc_get_ratio_shअगरt(काष्ठा gsc_context *ctx, u32 src, u32 dst,
			       u32 *ratio)
अणु
	DRM_DEV_DEBUG_KMS(ctx->dev, "src[%d]dst[%d]\n", src, dst);

	अगर (src >= dst * 8) अणु
		DRM_DEV_ERROR(ctx->dev, "failed to make ratio and shift.\n");
		वापस -EINVAL;
	पूर्ण अन्यथा अगर (src >= dst * 4)
		*ratio = 4;
	अन्यथा अगर (src >= dst * 2)
		*ratio = 2;
	अन्यथा
		*ratio = 1;

	वापस 0;
पूर्ण

अटल व्योम gsc_get_prescaler_shfactor(u32 hratio, u32 vratio, u32 *shfactor)
अणु
	अगर (hratio == 4 && vratio == 4)
		*shfactor = 4;
	अन्यथा अगर ((hratio == 4 && vratio == 2) ||
		 (hratio == 2 && vratio == 4))
		*shfactor = 3;
	अन्यथा अगर ((hratio == 4 && vratio == 1) ||
		 (hratio == 1 && vratio == 4) ||
		 (hratio == 2 && vratio == 2))
		*shfactor = 2;
	अन्यथा अगर (hratio == 1 && vratio == 1)
		*shfactor = 0;
	अन्यथा
		*shfactor = 1;
पूर्ण

अटल पूर्णांक gsc_set_prescaler(काष्ठा gsc_context *ctx, काष्ठा gsc_scaler *sc,
			     काष्ठा drm_exynos_ipp_task_rect *src,
			     काष्ठा drm_exynos_ipp_task_rect *dst)
अणु
	u32 cfg;
	u32 src_w, src_h, dst_w, dst_h;
	पूर्णांक ret = 0;

	src_w = src->w;
	src_h = src->h;

	अगर (ctx->rotation) अणु
		dst_w = dst->h;
		dst_h = dst->w;
	पूर्ण अन्यथा अणु
		dst_w = dst->w;
		dst_h = dst->h;
	पूर्ण

	ret = gsc_get_ratio_shअगरt(ctx, src_w, dst_w, &sc->pre_hratio);
	अगर (ret) अणु
		DRM_DEV_ERROR(ctx->dev, "failed to get ratio horizontal.\n");
		वापस ret;
	पूर्ण

	ret = gsc_get_ratio_shअगरt(ctx, src_h, dst_h, &sc->pre_vratio);
	अगर (ret) अणु
		DRM_DEV_ERROR(ctx->dev, "failed to get ratio vertical.\n");
		वापस ret;
	पूर्ण

	DRM_DEV_DEBUG_KMS(ctx->dev, "pre_hratio[%d]pre_vratio[%d]\n",
			  sc->pre_hratio, sc->pre_vratio);

	sc->मुख्य_hratio = (src_w << 16) / dst_w;
	sc->मुख्य_vratio = (src_h << 16) / dst_h;

	DRM_DEV_DEBUG_KMS(ctx->dev, "main_hratio[%ld]main_vratio[%ld]\n",
			  sc->मुख्य_hratio, sc->मुख्य_vratio);

	gsc_get_prescaler_shfactor(sc->pre_hratio, sc->pre_vratio,
		&sc->pre_shfactor);

	DRM_DEV_DEBUG_KMS(ctx->dev, "pre_shfactor[%d]\n", sc->pre_shfactor);

	cfg = (GSC_PRESC_SHFACTOR(sc->pre_shfactor) |
		GSC_PRESC_H_RATIO(sc->pre_hratio) |
		GSC_PRESC_V_RATIO(sc->pre_vratio));
	gsc_ग_लिखो(cfg, GSC_PRE_SCALE_RATIO);

	वापस ret;
पूर्ण

अटल व्योम gsc_set_h_coef(काष्ठा gsc_context *ctx, अचिन्हित दीर्घ मुख्य_hratio)
अणु
	पूर्णांक i, j, k, sc_ratio;

	अगर (मुख्य_hratio <= GSC_SC_UP_MAX_RATIO)
		sc_ratio = 0;
	अन्यथा अगर (मुख्य_hratio <= GSC_SC_DOWN_RATIO_7_8)
		sc_ratio = 1;
	अन्यथा अगर (मुख्य_hratio <= GSC_SC_DOWN_RATIO_6_8)
		sc_ratio = 2;
	अन्यथा अगर (मुख्य_hratio <= GSC_SC_DOWN_RATIO_5_8)
		sc_ratio = 3;
	अन्यथा अगर (मुख्य_hratio <= GSC_SC_DOWN_RATIO_4_8)
		sc_ratio = 4;
	अन्यथा अगर (मुख्य_hratio <= GSC_SC_DOWN_RATIO_3_8)
		sc_ratio = 5;
	अन्यथा
		sc_ratio = 6;

	क्रम (i = 0; i < GSC_COEF_PHASE; i++)
		क्रम (j = 0; j < GSC_COEF_H_8T; j++)
			क्रम (k = 0; k < GSC_COEF_DEPTH; k++)
				gsc_ग_लिखो(h_coef_8t[sc_ratio][i][j],
					GSC_HCOEF(i, j, k));
पूर्ण

अटल व्योम gsc_set_v_coef(काष्ठा gsc_context *ctx, अचिन्हित दीर्घ मुख्य_vratio)
अणु
	पूर्णांक i, j, k, sc_ratio;

	अगर (मुख्य_vratio <= GSC_SC_UP_MAX_RATIO)
		sc_ratio = 0;
	अन्यथा अगर (मुख्य_vratio <= GSC_SC_DOWN_RATIO_7_8)
		sc_ratio = 1;
	अन्यथा अगर (मुख्य_vratio <= GSC_SC_DOWN_RATIO_6_8)
		sc_ratio = 2;
	अन्यथा अगर (मुख्य_vratio <= GSC_SC_DOWN_RATIO_5_8)
		sc_ratio = 3;
	अन्यथा अगर (मुख्य_vratio <= GSC_SC_DOWN_RATIO_4_8)
		sc_ratio = 4;
	अन्यथा अगर (मुख्य_vratio <= GSC_SC_DOWN_RATIO_3_8)
		sc_ratio = 5;
	अन्यथा
		sc_ratio = 6;

	क्रम (i = 0; i < GSC_COEF_PHASE; i++)
		क्रम (j = 0; j < GSC_COEF_V_4T; j++)
			क्रम (k = 0; k < GSC_COEF_DEPTH; k++)
				gsc_ग_लिखो(v_coef_4t[sc_ratio][i][j],
					GSC_VCOEF(i, j, k));
पूर्ण

अटल व्योम gsc_set_scaler(काष्ठा gsc_context *ctx, काष्ठा gsc_scaler *sc)
अणु
	u32 cfg;

	DRM_DEV_DEBUG_KMS(ctx->dev, "main_hratio[%ld]main_vratio[%ld]\n",
			  sc->मुख्य_hratio, sc->मुख्य_vratio);

	gsc_set_h_coef(ctx, sc->मुख्य_hratio);
	cfg = GSC_MAIN_H_RATIO_VALUE(sc->मुख्य_hratio);
	gsc_ग_लिखो(cfg, GSC_MAIN_H_RATIO);

	gsc_set_v_coef(ctx, sc->मुख्य_vratio);
	cfg = GSC_MAIN_V_RATIO_VALUE(sc->मुख्य_vratio);
	gsc_ग_लिखो(cfg, GSC_MAIN_V_RATIO);
पूर्ण

अटल व्योम gsc_dst_set_size(काष्ठा gsc_context *ctx,
			     काष्ठा exynos_drm_ipp_buffer *buf)
अणु
	काष्ठा gsc_scaler *sc = &ctx->sc;
	u32 cfg;

	/* pixel offset */
	cfg = (GSC_DSTIMG_OFFSET_X(buf->rect.x) |
		GSC_DSTIMG_OFFSET_Y(buf->rect.y));
	gsc_ग_लिखो(cfg, GSC_DSTIMG_OFFSET);

	/* scaled size */
	अगर (ctx->rotation)
		cfg = (GSC_SCALED_WIDTH(buf->rect.h) |
		       GSC_SCALED_HEIGHT(buf->rect.w));
	अन्यथा
		cfg = (GSC_SCALED_WIDTH(buf->rect.w) |
		       GSC_SCALED_HEIGHT(buf->rect.h));
	gsc_ग_लिखो(cfg, GSC_SCALED_SIZE);

	/* original size */
	cfg = gsc_पढ़ो(GSC_DSTIMG_SIZE);
	cfg &= ~(GSC_DSTIMG_HEIGHT_MASK | GSC_DSTIMG_WIDTH_MASK);
	cfg |= GSC_DSTIMG_WIDTH(buf->buf.pitch[0] / buf->क्रमmat->cpp[0]) |
	       GSC_DSTIMG_HEIGHT(buf->buf.height);
	gsc_ग_लिखो(cfg, GSC_DSTIMG_SIZE);

	cfg = gsc_पढ़ो(GSC_OUT_CON);
	cfg &= ~GSC_OUT_RGB_TYPE_MASK;

	अगर (buf->rect.w >= GSC_WIDTH_ITU_709)
		अगर (sc->range)
			cfg |= GSC_OUT_RGB_HD_WIDE;
		अन्यथा
			cfg |= GSC_OUT_RGB_HD_NARROW;
	अन्यथा
		अगर (sc->range)
			cfg |= GSC_OUT_RGB_SD_WIDE;
		अन्यथा
			cfg |= GSC_OUT_RGB_SD_NARROW;

	gsc_ग_लिखो(cfg, GSC_OUT_CON);
पूर्ण

अटल पूर्णांक gsc_dst_get_buf_seq(काष्ठा gsc_context *ctx)
अणु
	u32 cfg, i, buf_num = GSC_REG_SZ;
	u32 mask = 0x00000001;

	cfg = gsc_पढ़ो(GSC_OUT_BASE_ADDR_Y_MASK);

	क्रम (i = 0; i < GSC_REG_SZ; i++)
		अगर (cfg & (mask << i))
			buf_num--;

	DRM_DEV_DEBUG_KMS(ctx->dev, "buf_num[%d]\n", buf_num);

	वापस buf_num;
पूर्ण

अटल व्योम gsc_dst_set_buf_seq(काष्ठा gsc_context *ctx, u32 buf_id,
				bool enqueue)
अणु
	bool masked = !enqueue;
	u32 cfg;
	u32 mask = 0x00000001 << buf_id;

	/* mask रेजिस्टर set */
	cfg = gsc_पढ़ो(GSC_OUT_BASE_ADDR_Y_MASK);

	/* sequence id */
	cfg &= ~mask;
	cfg |= masked << buf_id;
	gsc_ग_लिखो(cfg, GSC_OUT_BASE_ADDR_Y_MASK);
	gsc_ग_लिखो(cfg, GSC_OUT_BASE_ADDR_CB_MASK);
	gsc_ग_लिखो(cfg, GSC_OUT_BASE_ADDR_CR_MASK);

	/* पूर्णांकerrupt enable */
	अगर (enqueue && gsc_dst_get_buf_seq(ctx) >= GSC_BUF_START)
		gsc_handle_irq(ctx, true, false, true);

	/* पूर्णांकerrupt disable */
	अगर (!enqueue && gsc_dst_get_buf_seq(ctx) <= GSC_BUF_STOP)
		gsc_handle_irq(ctx, false, false, true);
पूर्ण

अटल व्योम gsc_dst_set_addr(काष्ठा gsc_context *ctx,
			     u32 buf_id, काष्ठा exynos_drm_ipp_buffer *buf)
अणु
	/* address रेजिस्टर set */
	gsc_ग_लिखो(buf->dma_addr[0], GSC_OUT_BASE_ADDR_Y(buf_id));
	gsc_ग_लिखो(buf->dma_addr[1], GSC_OUT_BASE_ADDR_CB(buf_id));
	gsc_ग_लिखो(buf->dma_addr[2], GSC_OUT_BASE_ADDR_CR(buf_id));

	gsc_dst_set_buf_seq(ctx, buf_id, true);
पूर्ण

अटल पूर्णांक gsc_get_src_buf_index(काष्ठा gsc_context *ctx)
अणु
	u32 cfg, curr_index, i;
	u32 buf_id = GSC_MAX_SRC;

	DRM_DEV_DEBUG_KMS(ctx->dev, "gsc id[%d]\n", ctx->id);

	cfg = gsc_पढ़ो(GSC_IN_BASE_ADDR_Y_MASK);
	curr_index = GSC_IN_CURR_GET_INDEX(cfg);

	क्रम (i = curr_index; i < GSC_MAX_SRC; i++) अणु
		अगर (!((cfg >> i) & 0x1)) अणु
			buf_id = i;
			अवरोध;
		पूर्ण
	पूर्ण

	DRM_DEV_DEBUG_KMS(ctx->dev, "cfg[0x%x]curr_index[%d]buf_id[%d]\n", cfg,
			  curr_index, buf_id);

	अगर (buf_id == GSC_MAX_SRC) अणु
		DRM_DEV_ERROR(ctx->dev, "failed to get in buffer index.\n");
		वापस -EINVAL;
	पूर्ण

	gsc_src_set_buf_seq(ctx, buf_id, false);

	वापस buf_id;
पूर्ण

अटल पूर्णांक gsc_get_dst_buf_index(काष्ठा gsc_context *ctx)
अणु
	u32 cfg, curr_index, i;
	u32 buf_id = GSC_MAX_DST;

	DRM_DEV_DEBUG_KMS(ctx->dev, "gsc id[%d]\n", ctx->id);

	cfg = gsc_पढ़ो(GSC_OUT_BASE_ADDR_Y_MASK);
	curr_index = GSC_OUT_CURR_GET_INDEX(cfg);

	क्रम (i = curr_index; i < GSC_MAX_DST; i++) अणु
		अगर (!((cfg >> i) & 0x1)) अणु
			buf_id = i;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (buf_id == GSC_MAX_DST) अणु
		DRM_DEV_ERROR(ctx->dev, "failed to get out buffer index.\n");
		वापस -EINVAL;
	पूर्ण

	gsc_dst_set_buf_seq(ctx, buf_id, false);

	DRM_DEV_DEBUG_KMS(ctx->dev, "cfg[0x%x]curr_index[%d]buf_id[%d]\n", cfg,
			  curr_index, buf_id);

	वापस buf_id;
पूर्ण

अटल irqवापस_t gsc_irq_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा gsc_context *ctx = dev_id;
	u32 status;
	पूर्णांक err = 0;

	DRM_DEV_DEBUG_KMS(ctx->dev, "gsc id[%d]\n", ctx->id);

	status = gsc_पढ़ो(GSC_IRQ);
	अगर (status & GSC_IRQ_STATUS_OR_IRQ) अणु
		dev_err(ctx->dev, "occurred overflow at %d, status 0x%x.\n",
			ctx->id, status);
		err = -EINVAL;
	पूर्ण

	अगर (status & GSC_IRQ_STATUS_OR_FRM_DONE) अणु
		पूर्णांक src_buf_id, dst_buf_id;

		dev_dbg(ctx->dev, "occurred frame done at %d, status 0x%x.\n",
			ctx->id, status);

		src_buf_id = gsc_get_src_buf_index(ctx);
		dst_buf_id = gsc_get_dst_buf_index(ctx);

		DRM_DEV_DEBUG_KMS(ctx->dev, "buf_id_src[%d]buf_id_dst[%d]\n",
				  src_buf_id, dst_buf_id);

		अगर (src_buf_id < 0 || dst_buf_id < 0)
			err = -EINVAL;
	पूर्ण

	अगर (ctx->task) अणु
		काष्ठा exynos_drm_ipp_task *task = ctx->task;

		ctx->task = शून्य;
		pm_runसमय_mark_last_busy(ctx->dev);
		pm_runसमय_put_स्वतःsuspend(ctx->dev);
		exynos_drm_ipp_task_करोne(task, err);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक gsc_reset(काष्ठा gsc_context *ctx)
अणु
	काष्ठा gsc_scaler *sc = &ctx->sc;
	पूर्णांक ret;

	/* reset h/w block */
	ret = gsc_sw_reset(ctx);
	अगर (ret < 0) अणु
		dev_err(ctx->dev, "failed to reset hardware.\n");
		वापस ret;
	पूर्ण

	/* scaler setting */
	स_रखो(&ctx->sc, 0x0, माप(ctx->sc));
	sc->range = true;

	वापस 0;
पूर्ण

अटल व्योम gsc_start(काष्ठा gsc_context *ctx)
अणु
	u32 cfg;

	gsc_handle_irq(ctx, true, false, true);

	/* enable one shot */
	cfg = gsc_पढ़ो(GSC_ENABLE);
	cfg &= ~(GSC_ENABLE_ON_CLEAR_MASK |
		GSC_ENABLE_CLK_GATE_MODE_MASK);
	cfg |= GSC_ENABLE_ON_CLEAR_ONESHOT;
	gsc_ग_लिखो(cfg, GSC_ENABLE);

	/* src dma memory */
	cfg = gsc_पढ़ो(GSC_IN_CON);
	cfg &= ~(GSC_IN_PATH_MASK | GSC_IN_LOCAL_SEL_MASK);
	cfg |= GSC_IN_PATH_MEMORY;
	gsc_ग_लिखो(cfg, GSC_IN_CON);

	/* dst dma memory */
	cfg = gsc_पढ़ो(GSC_OUT_CON);
	cfg |= GSC_OUT_PATH_MEMORY;
	gsc_ग_लिखो(cfg, GSC_OUT_CON);

	gsc_set_scaler(ctx, &ctx->sc);

	cfg = gsc_पढ़ो(GSC_ENABLE);
	cfg |= GSC_ENABLE_ON;
	gsc_ग_लिखो(cfg, GSC_ENABLE);
पूर्ण

अटल पूर्णांक gsc_commit(काष्ठा exynos_drm_ipp *ipp,
			  काष्ठा exynos_drm_ipp_task *task)
अणु
	काष्ठा gsc_context *ctx = container_of(ipp, काष्ठा gsc_context, ipp);
	पूर्णांक ret;

	pm_runसमय_get_sync(ctx->dev);
	ctx->task = task;

	ret = gsc_reset(ctx);
	अगर (ret) अणु
		pm_runसमय_put_स्वतःsuspend(ctx->dev);
		ctx->task = शून्य;
		वापस ret;
	पूर्ण

	gsc_src_set_fmt(ctx, task->src.buf.fourcc, task->src.buf.modअगरier);
	gsc_src_set_transf(ctx, task->transक्रमm.rotation);
	gsc_src_set_size(ctx, &task->src);
	gsc_src_set_addr(ctx, 0, &task->src);
	gsc_dst_set_fmt(ctx, task->dst.buf.fourcc, task->dst.buf.modअगरier);
	gsc_dst_set_size(ctx, &task->dst);
	gsc_dst_set_addr(ctx, 0, &task->dst);
	gsc_set_prescaler(ctx, &ctx->sc, &task->src.rect, &task->dst.rect);
	gsc_start(ctx);

	वापस 0;
पूर्ण

अटल व्योम gsc_पात(काष्ठा exynos_drm_ipp *ipp,
			  काष्ठा exynos_drm_ipp_task *task)
अणु
	काष्ठा gsc_context *ctx =
			container_of(ipp, काष्ठा gsc_context, ipp);

	gsc_reset(ctx);
	अगर (ctx->task) अणु
		काष्ठा exynos_drm_ipp_task *task = ctx->task;

		ctx->task = शून्य;
		pm_runसमय_mark_last_busy(ctx->dev);
		pm_runसमय_put_स्वतःsuspend(ctx->dev);
		exynos_drm_ipp_task_करोne(task, -EIO);
	पूर्ण
पूर्ण

अटल काष्ठा exynos_drm_ipp_funcs ipp_funcs = अणु
	.commit = gsc_commit,
	.पात = gsc_पात,
पूर्ण;

अटल पूर्णांक gsc_bind(काष्ठा device *dev, काष्ठा device *master, व्योम *data)
अणु
	काष्ठा gsc_context *ctx = dev_get_drvdata(dev);
	काष्ठा drm_device *drm_dev = data;
	काष्ठा exynos_drm_ipp *ipp = &ctx->ipp;

	ctx->drm_dev = drm_dev;
	ctx->drm_dev = drm_dev;
	exynos_drm_रेजिस्टर_dma(drm_dev, dev, &ctx->dma_priv);

	exynos_drm_ipp_रेजिस्टर(dev, ipp, &ipp_funcs,
			DRM_EXYNOS_IPP_CAP_CROP | DRM_EXYNOS_IPP_CAP_ROTATE |
			DRM_EXYNOS_IPP_CAP_SCALE | DRM_EXYNOS_IPP_CAP_CONVERT,
			ctx->क्रमmats, ctx->num_क्रमmats, "gsc");

	dev_info(dev, "The exynos gscaler has been probed successfully\n");

	वापस 0;
पूर्ण

अटल व्योम gsc_unbind(काष्ठा device *dev, काष्ठा device *master,
			व्योम *data)
अणु
	काष्ठा gsc_context *ctx = dev_get_drvdata(dev);
	काष्ठा drm_device *drm_dev = data;
	काष्ठा exynos_drm_ipp *ipp = &ctx->ipp;

	exynos_drm_ipp_unरेजिस्टर(dev, ipp);
	exynos_drm_unरेजिस्टर_dma(drm_dev, dev, &ctx->dma_priv);
पूर्ण

अटल स्थिर काष्ठा component_ops gsc_component_ops = अणु
	.bind	= gsc_bind,
	.unbind = gsc_unbind,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक gsc_क्रमmats[] = अणु
	DRM_FORMAT_ARGB8888,
	DRM_FORMAT_XRGB8888, DRM_FORMAT_RGB565, DRM_FORMAT_BGRX8888,
	DRM_FORMAT_NV12, DRM_FORMAT_NV16, DRM_FORMAT_NV21, DRM_FORMAT_NV61,
	DRM_FORMAT_UYVY, DRM_FORMAT_VYUY, DRM_FORMAT_YUYV, DRM_FORMAT_YVYU,
	DRM_FORMAT_YUV420, DRM_FORMAT_YVU420, DRM_FORMAT_YUV422,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक gsc_tiled_क्रमmats[] = अणु
	DRM_FORMAT_NV12, DRM_FORMAT_NV21,
पूर्ण;

अटल पूर्णांक gsc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा gsc_driverdata *driver_data;
	काष्ठा exynos_drm_ipp_क्रमmats *क्रमmats;
	काष्ठा gsc_context *ctx;
	काष्ठा resource *res;
	पूर्णांक num_क्रमmats, ret, i, j;

	ctx = devm_kzalloc(dev, माप(*ctx), GFP_KERNEL);
	अगर (!ctx)
		वापस -ENOMEM;

	driver_data = (काष्ठा gsc_driverdata *)of_device_get_match_data(dev);
	ctx->dev = dev;
	ctx->num_घड़ीs = driver_data->num_घड़ीs;
	ctx->clk_names = driver_data->clk_names;

	/* स्थिरruct क्रमmats/limits array */
	num_क्रमmats = ARRAY_SIZE(gsc_क्रमmats) + ARRAY_SIZE(gsc_tiled_क्रमmats);
	क्रमmats = devm_kसुस्मृति(dev, num_क्रमmats, माप(*क्रमmats), GFP_KERNEL);
	अगर (!क्रमmats)
		वापस -ENOMEM;

	/* linear क्रमmats */
	क्रम (i = 0; i < ARRAY_SIZE(gsc_क्रमmats); i++) अणु
		क्रमmats[i].fourcc = gsc_क्रमmats[i];
		क्रमmats[i].type = DRM_EXYNOS_IPP_FORMAT_SOURCE |
				  DRM_EXYNOS_IPP_FORMAT_DESTINATION;
		क्रमmats[i].limits = driver_data->limits;
		क्रमmats[i].num_limits = driver_data->num_limits;
	पूर्ण

	/* tiled क्रमmats */
	क्रम (j = i, i = 0; i < ARRAY_SIZE(gsc_tiled_क्रमmats); j++, i++) अणु
		क्रमmats[j].fourcc = gsc_tiled_क्रमmats[i];
		क्रमmats[j].modअगरier = DRM_FORMAT_MOD_SAMSUNG_16_16_TILE;
		क्रमmats[j].type = DRM_EXYNOS_IPP_FORMAT_SOURCE |
				  DRM_EXYNOS_IPP_FORMAT_DESTINATION;
		क्रमmats[j].limits = driver_data->limits;
		क्रमmats[j].num_limits = driver_data->num_limits;
	पूर्ण

	ctx->क्रमmats = क्रमmats;
	ctx->num_क्रमmats = num_क्रमmats;

	/* घड़ी control */
	क्रम (i = 0; i < ctx->num_घड़ीs; i++) अणु
		ctx->घड़ीs[i] = devm_clk_get(dev, ctx->clk_names[i]);
		अगर (IS_ERR(ctx->घड़ीs[i])) अणु
			dev_err(dev, "failed to get clock: %s\n",
				ctx->clk_names[i]);
			वापस PTR_ERR(ctx->घड़ीs[i]);
		पूर्ण
	पूर्ण

	/* resource memory */
	ctx->regs_res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	ctx->regs = devm_ioremap_resource(dev, ctx->regs_res);
	अगर (IS_ERR(ctx->regs))
		वापस PTR_ERR(ctx->regs);

	/* resource irq */
	res = platक्रमm_get_resource(pdev, IORESOURCE_IRQ, 0);
	अगर (!res) अणु
		dev_err(dev, "failed to request irq resource.\n");
		वापस -ENOENT;
	पूर्ण

	ctx->irq = res->start;
	ret = devm_request_irq(dev, ctx->irq, gsc_irq_handler, 0,
			       dev_name(dev), ctx);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to request irq.\n");
		वापस ret;
	पूर्ण

	/* context initailization */
	ctx->id = pdev->id;

	platक्रमm_set_drvdata(pdev, ctx);

	pm_runसमय_use_स्वतःsuspend(dev);
	pm_runसमय_set_स्वतःsuspend_delay(dev, GSC_AUTOSUSPEND_DELAY);
	pm_runसमय_enable(dev);

	ret = component_add(dev, &gsc_component_ops);
	अगर (ret)
		जाओ err_pm_dis;

	dev_info(dev, "drm gsc registered successfully.\n");

	वापस 0;

err_pm_dis:
	pm_runसमय_करोnt_use_स्वतःsuspend(dev);
	pm_runसमय_disable(dev);
	वापस ret;
पूर्ण

अटल पूर्णांक gsc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;

	component_del(dev, &gsc_component_ops);
	pm_runसमय_करोnt_use_स्वतःsuspend(dev);
	pm_runसमय_disable(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused gsc_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा gsc_context *ctx = get_gsc_context(dev);
	पूर्णांक i;

	DRM_DEV_DEBUG_KMS(dev, "id[%d]\n", ctx->id);

	क्रम (i = ctx->num_घड़ीs - 1; i >= 0; i--)
		clk_disable_unprepare(ctx->घड़ीs[i]);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused gsc_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा gsc_context *ctx = get_gsc_context(dev);
	पूर्णांक i, ret;

	DRM_DEV_DEBUG_KMS(dev, "id[%d]\n", ctx->id);

	क्रम (i = 0; i < ctx->num_घड़ीs; i++) अणु
		ret = clk_prepare_enable(ctx->घड़ीs[i]);
		अगर (ret) अणु
			जबतक (--i > 0)
				clk_disable_unprepare(ctx->घड़ीs[i]);
			वापस ret;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops gsc_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(pm_runसमय_क्रमce_suspend,
				pm_runसमय_क्रमce_resume)
	SET_RUNTIME_PM_OPS(gsc_runसमय_suspend, gsc_runसमय_resume, शून्य)
पूर्ण;

अटल स्थिर काष्ठा drm_exynos_ipp_limit gsc_5250_limits[] = अणु
	अणु IPP_SIZE_LIMIT(BUFFER, .h = अणु 32, 4800, 8 पूर्ण, .v = अणु 16, 3344, 8 पूर्ण) पूर्ण,
	अणु IPP_SIZE_LIMIT(AREA, .h = अणु 16, 4800, 2 पूर्ण, .v = अणु 8, 3344, 2 पूर्ण) पूर्ण,
	अणु IPP_SIZE_LIMIT(ROTATED, .h = अणु 32, 2048 पूर्ण, .v = अणु 16, 2048 पूर्ण) पूर्ण,
	अणु IPP_SCALE_LIMIT(.h = अणु (1 << 16) / 16, (1 << 16) * 8 पूर्ण,
			  .v = अणु (1 << 16) / 16, (1 << 16) * 8 पूर्ण) पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा drm_exynos_ipp_limit gsc_5420_limits[] = अणु
	अणु IPP_SIZE_LIMIT(BUFFER, .h = अणु 32, 4800, 8 पूर्ण, .v = अणु 16, 3344, 8 पूर्ण) पूर्ण,
	अणु IPP_SIZE_LIMIT(AREA, .h = अणु 16, 4800, 2 पूर्ण, .v = अणु 8, 3344, 2 पूर्ण) पूर्ण,
	अणु IPP_SIZE_LIMIT(ROTATED, .h = अणु 16, 2016 पूर्ण, .v = अणु 8, 2016 पूर्ण) पूर्ण,
	अणु IPP_SCALE_LIMIT(.h = अणु (1 << 16) / 16, (1 << 16) * 8 पूर्ण,
			  .v = अणु (1 << 16) / 16, (1 << 16) * 8 पूर्ण) पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा drm_exynos_ipp_limit gsc_5433_limits[] = अणु
	अणु IPP_SIZE_LIMIT(BUFFER, .h = अणु 32, 8191, 16 पूर्ण, .v = अणु 16, 8191, 2 पूर्ण) पूर्ण,
	अणु IPP_SIZE_LIMIT(AREA, .h = अणु 16, 4800, 1 पूर्ण, .v = अणु 8, 3344, 1 पूर्ण) पूर्ण,
	अणु IPP_SIZE_LIMIT(ROTATED, .h = अणु 32, 2047 पूर्ण, .v = अणु 8, 8191 पूर्ण) पूर्ण,
	अणु IPP_SCALE_LIMIT(.h = अणु (1 << 16) / 16, (1 << 16) * 8 पूर्ण,
			  .v = अणु (1 << 16) / 16, (1 << 16) * 8 पूर्ण) पूर्ण,
पूर्ण;

अटल काष्ठा gsc_driverdata gsc_exynos5250_drvdata = अणु
	.clk_names = अणु"gscl"पूर्ण,
	.num_घड़ीs = 1,
	.limits = gsc_5250_limits,
	.num_limits = ARRAY_SIZE(gsc_5250_limits),
पूर्ण;

अटल काष्ठा gsc_driverdata gsc_exynos5420_drvdata = अणु
	.clk_names = अणु"gscl"पूर्ण,
	.num_घड़ीs = 1,
	.limits = gsc_5420_limits,
	.num_limits = ARRAY_SIZE(gsc_5420_limits),
पूर्ण;

अटल काष्ठा gsc_driverdata gsc_exynos5433_drvdata = अणु
	.clk_names = अणु"pclk", "aclk", "aclk_xiu", "aclk_gsclbend"पूर्ण,
	.num_घड़ीs = 4,
	.limits = gsc_5433_limits,
	.num_limits = ARRAY_SIZE(gsc_5433_limits),
पूर्ण;

अटल स्थिर काष्ठा of_device_id exynos_drm_gsc_of_match[] = अणु
	अणु
		.compatible = "samsung,exynos5-gsc",
		.data = &gsc_exynos5250_drvdata,
	पूर्ण, अणु
		.compatible = "samsung,exynos5250-gsc",
		.data = &gsc_exynos5250_drvdata,
	पूर्ण, अणु
		.compatible = "samsung,exynos5420-gsc",
		.data = &gsc_exynos5420_drvdata,
	पूर्ण, अणु
		.compatible = "samsung,exynos5433-gsc",
		.data = &gsc_exynos5433_drvdata,
	पूर्ण, अणु
	पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, exynos_drm_gsc_of_match);

काष्ठा platक्रमm_driver gsc_driver = अणु
	.probe		= gsc_probe,
	.हटाओ		= gsc_हटाओ,
	.driver		= अणु
		.name	= "exynos-drm-gsc",
		.owner	= THIS_MODULE,
		.pm	= &gsc_pm_ops,
		.of_match_table = of_match_ptr(exynos_drm_gsc_of_match),
	पूर्ण,
पूर्ण;
