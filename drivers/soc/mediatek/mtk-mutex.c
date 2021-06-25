<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2015 MediaTek Inc.
 */

#समावेश <linux/clk.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/soc/mediatek/mtk-mmsys.h>
#समावेश <linux/soc/mediatek/mtk-mutex.h>

#घोषणा MT2701_MUTEX0_MOD0			0x2c
#घोषणा MT2701_MUTEX0_SOF0			0x30
#घोषणा MT8183_MUTEX0_MOD0			0x30
#घोषणा MT8183_MUTEX0_SOF0			0x2c

#घोषणा DISP_REG_MUTEX_EN(n)			(0x20 + 0x20 * (n))
#घोषणा DISP_REG_MUTEX(n)			(0x24 + 0x20 * (n))
#घोषणा DISP_REG_MUTEX_RST(n)			(0x28 + 0x20 * (n))
#घोषणा DISP_REG_MUTEX_MOD(mutex_mod_reg, n)	(mutex_mod_reg + 0x20 * (n))
#घोषणा DISP_REG_MUTEX_SOF(mutex_sof_reg, n)	(mutex_sof_reg + 0x20 * (n))
#घोषणा DISP_REG_MUTEX_MOD2(n)			(0x34 + 0x20 * (n))

#घोषणा INT_MUTEX				BIT(1)

#घोषणा MT8167_MUTEX_MOD_DISP_PWM		1
#घोषणा MT8167_MUTEX_MOD_DISP_OVL0		6
#घोषणा MT8167_MUTEX_MOD_DISP_OVL1		7
#घोषणा MT8167_MUTEX_MOD_DISP_RDMA0		8
#घोषणा MT8167_MUTEX_MOD_DISP_RDMA1		9
#घोषणा MT8167_MUTEX_MOD_DISP_WDMA0		10
#घोषणा MT8167_MUTEX_MOD_DISP_CCORR		11
#घोषणा MT8167_MUTEX_MOD_DISP_COLOR		12
#घोषणा MT8167_MUTEX_MOD_DISP_AAL		13
#घोषणा MT8167_MUTEX_MOD_DISP_GAMMA		14
#घोषणा MT8167_MUTEX_MOD_DISP_DITHER		15
#घोषणा MT8167_MUTEX_MOD_DISP_UFOE		16

#घोषणा MT8183_MUTEX_MOD_DISP_RDMA0		0
#घोषणा MT8183_MUTEX_MOD_DISP_RDMA1		1
#घोषणा MT8183_MUTEX_MOD_DISP_OVL0		9
#घोषणा MT8183_MUTEX_MOD_DISP_OVL0_2L		10
#घोषणा MT8183_MUTEX_MOD_DISP_OVL1_2L		11
#घोषणा MT8183_MUTEX_MOD_DISP_WDMA0		12
#घोषणा MT8183_MUTEX_MOD_DISP_COLOR0		13
#घोषणा MT8183_MUTEX_MOD_DISP_CCORR0		14
#घोषणा MT8183_MUTEX_MOD_DISP_AAL0		15
#घोषणा MT8183_MUTEX_MOD_DISP_GAMMA0		16
#घोषणा MT8183_MUTEX_MOD_DISP_DITHER0		17

#घोषणा MT8173_MUTEX_MOD_DISP_OVL0		11
#घोषणा MT8173_MUTEX_MOD_DISP_OVL1		12
#घोषणा MT8173_MUTEX_MOD_DISP_RDMA0		13
#घोषणा MT8173_MUTEX_MOD_DISP_RDMA1		14
#घोषणा MT8173_MUTEX_MOD_DISP_RDMA2		15
#घोषणा MT8173_MUTEX_MOD_DISP_WDMA0		16
#घोषणा MT8173_MUTEX_MOD_DISP_WDMA1		17
#घोषणा MT8173_MUTEX_MOD_DISP_COLOR0		18
#घोषणा MT8173_MUTEX_MOD_DISP_COLOR1		19
#घोषणा MT8173_MUTEX_MOD_DISP_AAL		20
#घोषणा MT8173_MUTEX_MOD_DISP_GAMMA		21
#घोषणा MT8173_MUTEX_MOD_DISP_UFOE		22
#घोषणा MT8173_MUTEX_MOD_DISP_PWM0		23
#घोषणा MT8173_MUTEX_MOD_DISP_PWM1		24
#घोषणा MT8173_MUTEX_MOD_DISP_OD		25

#घोषणा MT2712_MUTEX_MOD_DISP_PWM2		10
#घोषणा MT2712_MUTEX_MOD_DISP_OVL0		11
#घोषणा MT2712_MUTEX_MOD_DISP_OVL1		12
#घोषणा MT2712_MUTEX_MOD_DISP_RDMA0		13
#घोषणा MT2712_MUTEX_MOD_DISP_RDMA1		14
#घोषणा MT2712_MUTEX_MOD_DISP_RDMA2		15
#घोषणा MT2712_MUTEX_MOD_DISP_WDMA0		16
#घोषणा MT2712_MUTEX_MOD_DISP_WDMA1		17
#घोषणा MT2712_MUTEX_MOD_DISP_COLOR0		18
#घोषणा MT2712_MUTEX_MOD_DISP_COLOR1		19
#घोषणा MT2712_MUTEX_MOD_DISP_AAL0		20
#घोषणा MT2712_MUTEX_MOD_DISP_UFOE		22
#घोषणा MT2712_MUTEX_MOD_DISP_PWM0		23
#घोषणा MT2712_MUTEX_MOD_DISP_PWM1		24
#घोषणा MT2712_MUTEX_MOD_DISP_OD0		25
#घोषणा MT2712_MUTEX_MOD2_DISP_AAL1		33
#घोषणा MT2712_MUTEX_MOD2_DISP_OD1		34

#घोषणा MT2701_MUTEX_MOD_DISP_OVL		3
#घोषणा MT2701_MUTEX_MOD_DISP_WDMA		6
#घोषणा MT2701_MUTEX_MOD_DISP_COLOR		7
#घोषणा MT2701_MUTEX_MOD_DISP_BLS		9
#घोषणा MT2701_MUTEX_MOD_DISP_RDMA0		10
#घोषणा MT2701_MUTEX_MOD_DISP_RDMA1		12

#घोषणा MT2712_MUTEX_SOF_SINGLE_MODE		0
#घोषणा MT2712_MUTEX_SOF_DSI0			1
#घोषणा MT2712_MUTEX_SOF_DSI1			2
#घोषणा MT2712_MUTEX_SOF_DPI0			3
#घोषणा MT2712_MUTEX_SOF_DPI1			4
#घोषणा MT2712_MUTEX_SOF_DSI2			5
#घोषणा MT2712_MUTEX_SOF_DSI3			6
#घोषणा MT8167_MUTEX_SOF_DPI0			2
#घोषणा MT8167_MUTEX_SOF_DPI1			3
#घोषणा MT8183_MUTEX_SOF_DSI0			1
#घोषणा MT8183_MUTEX_SOF_DPI0			2

#घोषणा MT8183_MUTEX_खातापूर्ण_DSI0			(MT8183_MUTEX_SOF_DSI0 << 6)
#घोषणा MT8183_MUTEX_खातापूर्ण_DPI0			(MT8183_MUTEX_SOF_DPI0 << 6)

काष्ठा mtk_mutex अणु
	पूर्णांक id;
	bool claimed;
पूर्ण;

क्रमागत mtk_mutex_sof_id अणु
	MUTEX_SOF_SINGLE_MODE,
	MUTEX_SOF_DSI0,
	MUTEX_SOF_DSI1,
	MUTEX_SOF_DPI0,
	MUTEX_SOF_DPI1,
	MUTEX_SOF_DSI2,
	MUTEX_SOF_DSI3,
पूर्ण;

काष्ठा mtk_mutex_data अणु
	स्थिर अचिन्हित पूर्णांक *mutex_mod;
	स्थिर अचिन्हित पूर्णांक *mutex_sof;
	स्थिर अचिन्हित पूर्णांक mutex_mod_reg;
	स्थिर अचिन्हित पूर्णांक mutex_sof_reg;
	स्थिर bool no_clk;
पूर्ण;

काष्ठा mtk_mutex_ctx अणु
	काष्ठा device			*dev;
	काष्ठा clk			*clk;
	व्योम __iomem			*regs;
	काष्ठा mtk_mutex		mutex[10];
	स्थिर काष्ठा mtk_mutex_data	*data;
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक mt2701_mutex_mod[DDP_COMPONENT_ID_MAX] = अणु
	[DDP_COMPONENT_BLS] = MT2701_MUTEX_MOD_DISP_BLS,
	[DDP_COMPONENT_COLOR0] = MT2701_MUTEX_MOD_DISP_COLOR,
	[DDP_COMPONENT_OVL0] = MT2701_MUTEX_MOD_DISP_OVL,
	[DDP_COMPONENT_RDMA0] = MT2701_MUTEX_MOD_DISP_RDMA0,
	[DDP_COMPONENT_RDMA1] = MT2701_MUTEX_MOD_DISP_RDMA1,
	[DDP_COMPONENT_WDMA0] = MT2701_MUTEX_MOD_DISP_WDMA,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक mt2712_mutex_mod[DDP_COMPONENT_ID_MAX] = अणु
	[DDP_COMPONENT_AAL0] = MT2712_MUTEX_MOD_DISP_AAL0,
	[DDP_COMPONENT_AAL1] = MT2712_MUTEX_MOD2_DISP_AAL1,
	[DDP_COMPONENT_COLOR0] = MT2712_MUTEX_MOD_DISP_COLOR0,
	[DDP_COMPONENT_COLOR1] = MT2712_MUTEX_MOD_DISP_COLOR1,
	[DDP_COMPONENT_OD0] = MT2712_MUTEX_MOD_DISP_OD0,
	[DDP_COMPONENT_OD1] = MT2712_MUTEX_MOD2_DISP_OD1,
	[DDP_COMPONENT_OVL0] = MT2712_MUTEX_MOD_DISP_OVL0,
	[DDP_COMPONENT_OVL1] = MT2712_MUTEX_MOD_DISP_OVL1,
	[DDP_COMPONENT_PWM0] = MT2712_MUTEX_MOD_DISP_PWM0,
	[DDP_COMPONENT_PWM1] = MT2712_MUTEX_MOD_DISP_PWM1,
	[DDP_COMPONENT_PWM2] = MT2712_MUTEX_MOD_DISP_PWM2,
	[DDP_COMPONENT_RDMA0] = MT2712_MUTEX_MOD_DISP_RDMA0,
	[DDP_COMPONENT_RDMA1] = MT2712_MUTEX_MOD_DISP_RDMA1,
	[DDP_COMPONENT_RDMA2] = MT2712_MUTEX_MOD_DISP_RDMA2,
	[DDP_COMPONENT_UFOE] = MT2712_MUTEX_MOD_DISP_UFOE,
	[DDP_COMPONENT_WDMA0] = MT2712_MUTEX_MOD_DISP_WDMA0,
	[DDP_COMPONENT_WDMA1] = MT2712_MUTEX_MOD_DISP_WDMA1,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक mt8167_mutex_mod[DDP_COMPONENT_ID_MAX] = अणु
	[DDP_COMPONENT_AAL0] = MT8167_MUTEX_MOD_DISP_AAL,
	[DDP_COMPONENT_CCORR] = MT8167_MUTEX_MOD_DISP_CCORR,
	[DDP_COMPONENT_COLOR0] = MT8167_MUTEX_MOD_DISP_COLOR,
	[DDP_COMPONENT_DITHER] = MT8167_MUTEX_MOD_DISP_DITHER,
	[DDP_COMPONENT_GAMMA] = MT8167_MUTEX_MOD_DISP_GAMMA,
	[DDP_COMPONENT_OVL0] = MT8167_MUTEX_MOD_DISP_OVL0,
	[DDP_COMPONENT_OVL1] = MT8167_MUTEX_MOD_DISP_OVL1,
	[DDP_COMPONENT_PWM0] = MT8167_MUTEX_MOD_DISP_PWM,
	[DDP_COMPONENT_RDMA0] = MT8167_MUTEX_MOD_DISP_RDMA0,
	[DDP_COMPONENT_RDMA1] = MT8167_MUTEX_MOD_DISP_RDMA1,
	[DDP_COMPONENT_UFOE] = MT8167_MUTEX_MOD_DISP_UFOE,
	[DDP_COMPONENT_WDMA0] = MT8167_MUTEX_MOD_DISP_WDMA0,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक mt8173_mutex_mod[DDP_COMPONENT_ID_MAX] = अणु
	[DDP_COMPONENT_AAL0] = MT8173_MUTEX_MOD_DISP_AAL,
	[DDP_COMPONENT_COLOR0] = MT8173_MUTEX_MOD_DISP_COLOR0,
	[DDP_COMPONENT_COLOR1] = MT8173_MUTEX_MOD_DISP_COLOR1,
	[DDP_COMPONENT_GAMMA] = MT8173_MUTEX_MOD_DISP_GAMMA,
	[DDP_COMPONENT_OD0] = MT8173_MUTEX_MOD_DISP_OD,
	[DDP_COMPONENT_OVL0] = MT8173_MUTEX_MOD_DISP_OVL0,
	[DDP_COMPONENT_OVL1] = MT8173_MUTEX_MOD_DISP_OVL1,
	[DDP_COMPONENT_PWM0] = MT8173_MUTEX_MOD_DISP_PWM0,
	[DDP_COMPONENT_PWM1] = MT8173_MUTEX_MOD_DISP_PWM1,
	[DDP_COMPONENT_RDMA0] = MT8173_MUTEX_MOD_DISP_RDMA0,
	[DDP_COMPONENT_RDMA1] = MT8173_MUTEX_MOD_DISP_RDMA1,
	[DDP_COMPONENT_RDMA2] = MT8173_MUTEX_MOD_DISP_RDMA2,
	[DDP_COMPONENT_UFOE] = MT8173_MUTEX_MOD_DISP_UFOE,
	[DDP_COMPONENT_WDMA0] = MT8173_MUTEX_MOD_DISP_WDMA0,
	[DDP_COMPONENT_WDMA1] = MT8173_MUTEX_MOD_DISP_WDMA1,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक mt8183_mutex_mod[DDP_COMPONENT_ID_MAX] = अणु
	[DDP_COMPONENT_AAL0] = MT8183_MUTEX_MOD_DISP_AAL0,
	[DDP_COMPONENT_CCORR] = MT8183_MUTEX_MOD_DISP_CCORR0,
	[DDP_COMPONENT_COLOR0] = MT8183_MUTEX_MOD_DISP_COLOR0,
	[DDP_COMPONENT_DITHER] = MT8183_MUTEX_MOD_DISP_DITHER0,
	[DDP_COMPONENT_GAMMA] = MT8183_MUTEX_MOD_DISP_GAMMA0,
	[DDP_COMPONENT_OVL0] = MT8183_MUTEX_MOD_DISP_OVL0,
	[DDP_COMPONENT_OVL_2L0] = MT8183_MUTEX_MOD_DISP_OVL0_2L,
	[DDP_COMPONENT_OVL_2L1] = MT8183_MUTEX_MOD_DISP_OVL1_2L,
	[DDP_COMPONENT_RDMA0] = MT8183_MUTEX_MOD_DISP_RDMA0,
	[DDP_COMPONENT_RDMA1] = MT8183_MUTEX_MOD_DISP_RDMA1,
	[DDP_COMPONENT_WDMA0] = MT8183_MUTEX_MOD_DISP_WDMA0,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक mt2712_mutex_sof[MUTEX_SOF_DSI3 + 1] = अणु
	[MUTEX_SOF_SINGLE_MODE] = MUTEX_SOF_SINGLE_MODE,
	[MUTEX_SOF_DSI0] = MUTEX_SOF_DSI0,
	[MUTEX_SOF_DSI1] = MUTEX_SOF_DSI1,
	[MUTEX_SOF_DPI0] = MUTEX_SOF_DPI0,
	[MUTEX_SOF_DPI1] = MUTEX_SOF_DPI1,
	[MUTEX_SOF_DSI2] = MUTEX_SOF_DSI2,
	[MUTEX_SOF_DSI3] = MUTEX_SOF_DSI3,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक mt8167_mutex_sof[MUTEX_SOF_DSI3 + 1] = अणु
	[MUTEX_SOF_SINGLE_MODE] = MUTEX_SOF_SINGLE_MODE,
	[MUTEX_SOF_DSI0] = MUTEX_SOF_DSI0,
	[MUTEX_SOF_DPI0] = MT8167_MUTEX_SOF_DPI0,
	[MUTEX_SOF_DPI1] = MT8167_MUTEX_SOF_DPI1,
पूर्ण;

/* Add खातापूर्ण setting so overlay hardware can receive frame करोne irq */
अटल स्थिर अचिन्हित पूर्णांक mt8183_mutex_sof[MUTEX_SOF_DSI3 + 1] = अणु
	[MUTEX_SOF_SINGLE_MODE] = MUTEX_SOF_SINGLE_MODE,
	[MUTEX_SOF_DSI0] = MUTEX_SOF_DSI0 | MT8183_MUTEX_खातापूर्ण_DSI0,
	[MUTEX_SOF_DPI0] = MT8183_MUTEX_SOF_DPI0 | MT8183_MUTEX_खातापूर्ण_DPI0,
पूर्ण;

अटल स्थिर काष्ठा mtk_mutex_data mt2701_mutex_driver_data = अणु
	.mutex_mod = mt2701_mutex_mod,
	.mutex_sof = mt2712_mutex_sof,
	.mutex_mod_reg = MT2701_MUTEX0_MOD0,
	.mutex_sof_reg = MT2701_MUTEX0_SOF0,
पूर्ण;

अटल स्थिर काष्ठा mtk_mutex_data mt2712_mutex_driver_data = अणु
	.mutex_mod = mt2712_mutex_mod,
	.mutex_sof = mt2712_mutex_sof,
	.mutex_mod_reg = MT2701_MUTEX0_MOD0,
	.mutex_sof_reg = MT2701_MUTEX0_SOF0,
पूर्ण;

अटल स्थिर काष्ठा mtk_mutex_data mt8167_mutex_driver_data = अणु
	.mutex_mod = mt8167_mutex_mod,
	.mutex_sof = mt8167_mutex_sof,
	.mutex_mod_reg = MT2701_MUTEX0_MOD0,
	.mutex_sof_reg = MT2701_MUTEX0_SOF0,
	.no_clk = true,
पूर्ण;

अटल स्थिर काष्ठा mtk_mutex_data mt8173_mutex_driver_data = अणु
	.mutex_mod = mt8173_mutex_mod,
	.mutex_sof = mt2712_mutex_sof,
	.mutex_mod_reg = MT2701_MUTEX0_MOD0,
	.mutex_sof_reg = MT2701_MUTEX0_SOF0,
पूर्ण;

अटल स्थिर काष्ठा mtk_mutex_data mt8183_mutex_driver_data = अणु
	.mutex_mod = mt8183_mutex_mod,
	.mutex_sof = mt8183_mutex_sof,
	.mutex_mod_reg = MT8183_MUTEX0_MOD0,
	.mutex_sof_reg = MT8183_MUTEX0_SOF0,
	.no_clk = true,
पूर्ण;

काष्ठा mtk_mutex *mtk_mutex_get(काष्ठा device *dev)
अणु
	काष्ठा mtk_mutex_ctx *mtx = dev_get_drvdata(dev);
	पूर्णांक i;

	क्रम (i = 0; i < 10; i++)
		अगर (!mtx->mutex[i].claimed) अणु
			mtx->mutex[i].claimed = true;
			वापस &mtx->mutex[i];
		पूर्ण

	वापस ERR_PTR(-EBUSY);
पूर्ण
EXPORT_SYMBOL_GPL(mtk_mutex_get);

व्योम mtk_mutex_put(काष्ठा mtk_mutex *mutex)
अणु
	काष्ठा mtk_mutex_ctx *mtx = container_of(mutex, काष्ठा mtk_mutex_ctx,
						 mutex[mutex->id]);

	WARN_ON(&mtx->mutex[mutex->id] != mutex);

	mutex->claimed = false;
पूर्ण
EXPORT_SYMBOL_GPL(mtk_mutex_put);

पूर्णांक mtk_mutex_prepare(काष्ठा mtk_mutex *mutex)
अणु
	काष्ठा mtk_mutex_ctx *mtx = container_of(mutex, काष्ठा mtk_mutex_ctx,
						 mutex[mutex->id]);
	वापस clk_prepare_enable(mtx->clk);
पूर्ण
EXPORT_SYMBOL_GPL(mtk_mutex_prepare);

व्योम mtk_mutex_unprepare(काष्ठा mtk_mutex *mutex)
अणु
	काष्ठा mtk_mutex_ctx *mtx = container_of(mutex, काष्ठा mtk_mutex_ctx,
						 mutex[mutex->id]);
	clk_disable_unprepare(mtx->clk);
पूर्ण
EXPORT_SYMBOL_GPL(mtk_mutex_unprepare);

व्योम mtk_mutex_add_comp(काष्ठा mtk_mutex *mutex,
			क्रमागत mtk_ddp_comp_id id)
अणु
	काष्ठा mtk_mutex_ctx *mtx = container_of(mutex, काष्ठा mtk_mutex_ctx,
						 mutex[mutex->id]);
	अचिन्हित पूर्णांक reg;
	अचिन्हित पूर्णांक sof_id;
	अचिन्हित पूर्णांक offset;

	WARN_ON(&mtx->mutex[mutex->id] != mutex);

	चयन (id) अणु
	हाल DDP_COMPONENT_DSI0:
		sof_id = MUTEX_SOF_DSI0;
		अवरोध;
	हाल DDP_COMPONENT_DSI1:
		sof_id = MUTEX_SOF_DSI0;
		अवरोध;
	हाल DDP_COMPONENT_DSI2:
		sof_id = MUTEX_SOF_DSI2;
		अवरोध;
	हाल DDP_COMPONENT_DSI3:
		sof_id = MUTEX_SOF_DSI3;
		अवरोध;
	हाल DDP_COMPONENT_DPI0:
		sof_id = MUTEX_SOF_DPI0;
		अवरोध;
	हाल DDP_COMPONENT_DPI1:
		sof_id = MUTEX_SOF_DPI1;
		अवरोध;
	शेष:
		अगर (mtx->data->mutex_mod[id] < 32) अणु
			offset = DISP_REG_MUTEX_MOD(mtx->data->mutex_mod_reg,
						    mutex->id);
			reg = पढ़ोl_relaxed(mtx->regs + offset);
			reg |= 1 << mtx->data->mutex_mod[id];
			ग_लिखोl_relaxed(reg, mtx->regs + offset);
		पूर्ण अन्यथा अणु
			offset = DISP_REG_MUTEX_MOD2(mutex->id);
			reg = पढ़ोl_relaxed(mtx->regs + offset);
			reg |= 1 << (mtx->data->mutex_mod[id] - 32);
			ग_लिखोl_relaxed(reg, mtx->regs + offset);
		पूर्ण
		वापस;
	पूर्ण

	ग_लिखोl_relaxed(mtx->data->mutex_sof[sof_id],
		       mtx->regs +
		       DISP_REG_MUTEX_SOF(mtx->data->mutex_sof_reg, mutex->id));
पूर्ण
EXPORT_SYMBOL_GPL(mtk_mutex_add_comp);

व्योम mtk_mutex_हटाओ_comp(काष्ठा mtk_mutex *mutex,
			   क्रमागत mtk_ddp_comp_id id)
अणु
	काष्ठा mtk_mutex_ctx *mtx = container_of(mutex, काष्ठा mtk_mutex_ctx,
						 mutex[mutex->id]);
	अचिन्हित पूर्णांक reg;
	अचिन्हित पूर्णांक offset;

	WARN_ON(&mtx->mutex[mutex->id] != mutex);

	चयन (id) अणु
	हाल DDP_COMPONENT_DSI0:
	हाल DDP_COMPONENT_DSI1:
	हाल DDP_COMPONENT_DSI2:
	हाल DDP_COMPONENT_DSI3:
	हाल DDP_COMPONENT_DPI0:
	हाल DDP_COMPONENT_DPI1:
		ग_लिखोl_relaxed(MUTEX_SOF_SINGLE_MODE,
			       mtx->regs +
			       DISP_REG_MUTEX_SOF(mtx->data->mutex_sof_reg,
						  mutex->id));
		अवरोध;
	शेष:
		अगर (mtx->data->mutex_mod[id] < 32) अणु
			offset = DISP_REG_MUTEX_MOD(mtx->data->mutex_mod_reg,
						    mutex->id);
			reg = पढ़ोl_relaxed(mtx->regs + offset);
			reg &= ~(1 << mtx->data->mutex_mod[id]);
			ग_लिखोl_relaxed(reg, mtx->regs + offset);
		पूर्ण अन्यथा अणु
			offset = DISP_REG_MUTEX_MOD2(mutex->id);
			reg = पढ़ोl_relaxed(mtx->regs + offset);
			reg &= ~(1 << (mtx->data->mutex_mod[id] - 32));
			ग_लिखोl_relaxed(reg, mtx->regs + offset);
		पूर्ण
		अवरोध;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(mtk_mutex_हटाओ_comp);

व्योम mtk_mutex_enable(काष्ठा mtk_mutex *mutex)
अणु
	काष्ठा mtk_mutex_ctx *mtx = container_of(mutex, काष्ठा mtk_mutex_ctx,
						 mutex[mutex->id]);

	WARN_ON(&mtx->mutex[mutex->id] != mutex);

	ग_लिखोl(1, mtx->regs + DISP_REG_MUTEX_EN(mutex->id));
पूर्ण
EXPORT_SYMBOL_GPL(mtk_mutex_enable);

व्योम mtk_mutex_disable(काष्ठा mtk_mutex *mutex)
अणु
	काष्ठा mtk_mutex_ctx *mtx = container_of(mutex, काष्ठा mtk_mutex_ctx,
						 mutex[mutex->id]);

	WARN_ON(&mtx->mutex[mutex->id] != mutex);

	ग_लिखोl(0, mtx->regs + DISP_REG_MUTEX_EN(mutex->id));
पूर्ण
EXPORT_SYMBOL_GPL(mtk_mutex_disable);

व्योम mtk_mutex_acquire(काष्ठा mtk_mutex *mutex)
अणु
	काष्ठा mtk_mutex_ctx *mtx = container_of(mutex, काष्ठा mtk_mutex_ctx,
						 mutex[mutex->id]);
	u32 पंचांगp;

	ग_लिखोl(1, mtx->regs + DISP_REG_MUTEX_EN(mutex->id));
	ग_लिखोl(1, mtx->regs + DISP_REG_MUTEX(mutex->id));
	अगर (पढ़ोl_poll_समयout_atomic(mtx->regs + DISP_REG_MUTEX(mutex->id),
				      पंचांगp, पंचांगp & INT_MUTEX, 1, 10000))
		pr_err("could not acquire mutex %d\n", mutex->id);
पूर्ण
EXPORT_SYMBOL_GPL(mtk_mutex_acquire);

व्योम mtk_mutex_release(काष्ठा mtk_mutex *mutex)
अणु
	काष्ठा mtk_mutex_ctx *mtx = container_of(mutex, काष्ठा mtk_mutex_ctx,
						 mutex[mutex->id]);

	ग_लिखोl(0, mtx->regs + DISP_REG_MUTEX(mutex->id));
पूर्ण
EXPORT_SYMBOL_GPL(mtk_mutex_release);

अटल पूर्णांक mtk_mutex_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा mtk_mutex_ctx *mtx;
	काष्ठा resource *regs;
	पूर्णांक i;

	mtx = devm_kzalloc(dev, माप(*mtx), GFP_KERNEL);
	अगर (!mtx)
		वापस -ENOMEM;

	क्रम (i = 0; i < 10; i++)
		mtx->mutex[i].id = i;

	mtx->data = of_device_get_match_data(dev);

	अगर (!mtx->data->no_clk) अणु
		mtx->clk = devm_clk_get(dev, शून्य);
		अगर (IS_ERR(mtx->clk)) अणु
			अगर (PTR_ERR(mtx->clk) != -EPROBE_DEFER)
				dev_err(dev, "Failed to get clock\n");
			वापस PTR_ERR(mtx->clk);
		पूर्ण
	पूर्ण

	regs = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	mtx->regs = devm_ioremap_resource(dev, regs);
	अगर (IS_ERR(mtx->regs)) अणु
		dev_err(dev, "Failed to map mutex registers\n");
		वापस PTR_ERR(mtx->regs);
	पूर्ण

	platक्रमm_set_drvdata(pdev, mtx);

	वापस 0;
पूर्ण

अटल पूर्णांक mtk_mutex_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id mutex_driver_dt_match[] = अणु
	अणु .compatible = "mediatek,mt2701-disp-mutex",
	  .data = &mt2701_mutex_driver_dataपूर्ण,
	अणु .compatible = "mediatek,mt2712-disp-mutex",
	  .data = &mt2712_mutex_driver_dataपूर्ण,
	अणु .compatible = "mediatek,mt8167-disp-mutex",
	  .data = &mt8167_mutex_driver_dataपूर्ण,
	अणु .compatible = "mediatek,mt8173-disp-mutex",
	  .data = &mt8173_mutex_driver_dataपूर्ण,
	अणु .compatible = "mediatek,mt8183-disp-mutex",
	  .data = &mt8183_mutex_driver_dataपूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, mutex_driver_dt_match);

अटल काष्ठा platक्रमm_driver mtk_mutex_driver = अणु
	.probe		= mtk_mutex_probe,
	.हटाओ		= mtk_mutex_हटाओ,
	.driver		= अणु
		.name	= "mediatek-mutex",
		.owner	= THIS_MODULE,
		.of_match_table = mutex_driver_dt_match,
	पूर्ण,
पूर्ण;

builtin_platक्रमm_driver(mtk_mutex_driver);
