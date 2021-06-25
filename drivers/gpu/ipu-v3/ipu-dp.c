<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (c) 2010 Sascha Hauer <s.hauer@pengutronix.de>
 * Copyright (C) 2005-2009 Freescale Semiconductor, Inc.
 */
#समावेश <linux/export.h>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/पन.स>
#समावेश <linux/err.h>

#समावेश <video/imx-ipu-v3.h>
#समावेश "ipu-prv.h"

#घोषणा DP_SYNC 0
#घोषणा DP_ASYNC0 0x60
#घोषणा DP_ASYNC1 0xBC

#घोषणा DP_COM_CONF		0x0
#घोषणा DP_GRAPH_WIND_CTRL	0x0004
#घोषणा DP_FG_POS		0x0008
#घोषणा DP_CSC_A_0		0x0044
#घोषणा DP_CSC_A_1		0x0048
#घोषणा DP_CSC_A_2		0x004C
#घोषणा DP_CSC_A_3		0x0050
#घोषणा DP_CSC_0		0x0054
#घोषणा DP_CSC_1		0x0058

#घोषणा DP_COM_CONF_FG_EN		(1 << 0)
#घोषणा DP_COM_CONF_GWSEL		(1 << 1)
#घोषणा DP_COM_CONF_GWAM		(1 << 2)
#घोषणा DP_COM_CONF_GWCKE		(1 << 3)
#घोषणा DP_COM_CONF_CSC_DEF_MASK	(3 << 8)
#घोषणा DP_COM_CONF_CSC_DEF_OFFSET	8
#घोषणा DP_COM_CONF_CSC_DEF_FG		(3 << 8)
#घोषणा DP_COM_CONF_CSC_DEF_BG		(2 << 8)
#घोषणा DP_COM_CONF_CSC_DEF_BOTH	(1 << 8)

#घोषणा IPUV3_NUM_FLOWS		3

काष्ठा ipu_dp_priv;

काष्ठा ipu_dp अणु
	u32 flow;
	bool in_use;
	bool क्रमeground;
	क्रमागत ipu_color_space in_cs;
पूर्ण;

काष्ठा ipu_flow अणु
	काष्ठा ipu_dp क्रमeground;
	काष्ठा ipu_dp background;
	क्रमागत ipu_color_space out_cs;
	व्योम __iomem *base;
	काष्ठा ipu_dp_priv *priv;
पूर्ण;

काष्ठा ipu_dp_priv अणु
	काष्ठा ipu_soc *ipu;
	काष्ठा device *dev;
	व्योम __iomem *base;
	काष्ठा ipu_flow flow[IPUV3_NUM_FLOWS];
	काष्ठा mutex mutex;
	पूर्णांक use_count;
पूर्ण;

अटल u32 ipu_dp_flow_base[] = अणुDP_SYNC, DP_ASYNC0, DP_ASYNC1पूर्ण;

अटल अंतरभूत काष्ठा ipu_flow *to_flow(काष्ठा ipu_dp *dp)
अणु
	अगर (dp->क्रमeground)
		वापस container_of(dp, काष्ठा ipu_flow, क्रमeground);
	अन्यथा
		वापस container_of(dp, काष्ठा ipu_flow, background);
पूर्ण

पूर्णांक ipu_dp_set_global_alpha(काष्ठा ipu_dp *dp, bool enable,
		u8 alpha, bool bg_chan)
अणु
	काष्ठा ipu_flow *flow = to_flow(dp);
	काष्ठा ipu_dp_priv *priv = flow->priv;
	u32 reg;

	mutex_lock(&priv->mutex);

	reg = पढ़ोl(flow->base + DP_COM_CONF);
	अगर (bg_chan)
		reg &= ~DP_COM_CONF_GWSEL;
	अन्यथा
		reg |= DP_COM_CONF_GWSEL;
	ग_लिखोl(reg, flow->base + DP_COM_CONF);

	अगर (enable) अणु
		reg = पढ़ोl(flow->base + DP_GRAPH_WIND_CTRL) & 0x00FFFFFFL;
		ग_लिखोl(reg | ((u32) alpha << 24),
			     flow->base + DP_GRAPH_WIND_CTRL);

		reg = पढ़ोl(flow->base + DP_COM_CONF);
		ग_लिखोl(reg | DP_COM_CONF_GWAM, flow->base + DP_COM_CONF);
	पूर्ण अन्यथा अणु
		reg = पढ़ोl(flow->base + DP_COM_CONF);
		ग_लिखोl(reg & ~DP_COM_CONF_GWAM, flow->base + DP_COM_CONF);
	पूर्ण

	ipu_srm_dp_update(priv->ipu, true);

	mutex_unlock(&priv->mutex);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ipu_dp_set_global_alpha);

पूर्णांक ipu_dp_set_winकरोw_pos(काष्ठा ipu_dp *dp, u16 x_pos, u16 y_pos)
अणु
	काष्ठा ipu_flow *flow = to_flow(dp);
	काष्ठा ipu_dp_priv *priv = flow->priv;

	ग_लिखोl((x_pos << 16) | y_pos, flow->base + DP_FG_POS);

	ipu_srm_dp_update(priv->ipu, true);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ipu_dp_set_winकरोw_pos);

अटल व्योम ipu_dp_csc_init(काष्ठा ipu_flow *flow,
		क्रमागत ipu_color_space in,
		क्रमागत ipu_color_space out,
		u32 place)
अणु
	u32 reg;

	reg = पढ़ोl(flow->base + DP_COM_CONF);
	reg &= ~DP_COM_CONF_CSC_DEF_MASK;

	अगर (in == out) अणु
		ग_लिखोl(reg, flow->base + DP_COM_CONF);
		वापस;
	पूर्ण

	अगर (in == IPUV3_COLORSPACE_RGB && out == IPUV3_COLORSPACE_YUV) अणु
		ग_लिखोl(0x099 | (0x12d << 16), flow->base + DP_CSC_A_0);
		ग_लिखोl(0x03a | (0x3a9 << 16), flow->base + DP_CSC_A_1);
		ग_लिखोl(0x356 | (0x100 << 16), flow->base + DP_CSC_A_2);
		ग_लिखोl(0x100 | (0x329 << 16), flow->base + DP_CSC_A_3);
		ग_लिखोl(0x3d6 | (0x0000 << 16) | (2 << 30),
				flow->base + DP_CSC_0);
		ग_लिखोl(0x200 | (2 << 14) | (0x200 << 16) | (2 << 30),
				flow->base + DP_CSC_1);
	पूर्ण अन्यथा अणु
		ग_लिखोl(0x095 | (0x000 << 16), flow->base + DP_CSC_A_0);
		ग_लिखोl(0x0cc | (0x095 << 16), flow->base + DP_CSC_A_1);
		ग_लिखोl(0x3ce | (0x398 << 16), flow->base + DP_CSC_A_2);
		ग_लिखोl(0x095 | (0x0ff << 16), flow->base + DP_CSC_A_3);
		ग_लिखोl(0x000 | (0x3e42 << 16) | (1 << 30),
				flow->base + DP_CSC_0);
		ग_लिखोl(0x10a | (1 << 14) | (0x3dd6 << 16) | (1 << 30),
				flow->base + DP_CSC_1);
	पूर्ण

	reg |= place;

	ग_लिखोl(reg, flow->base + DP_COM_CONF);
पूर्ण

पूर्णांक ipu_dp_setup_channel(काष्ठा ipu_dp *dp,
		क्रमागत ipu_color_space in,
		क्रमागत ipu_color_space out)
अणु
	काष्ठा ipu_flow *flow = to_flow(dp);
	काष्ठा ipu_dp_priv *priv = flow->priv;

	mutex_lock(&priv->mutex);

	dp->in_cs = in;

	अगर (!dp->क्रमeground)
		flow->out_cs = out;

	अगर (flow->क्रमeground.in_cs == flow->background.in_cs) अणु
		/*
		 * क्रमeground and background are of same colorspace, put
		 * colorspace converter after combining unit.
		 */
		ipu_dp_csc_init(flow, flow->क्रमeground.in_cs, flow->out_cs,
				DP_COM_CONF_CSC_DEF_BOTH);
	पूर्ण अन्यथा अणु
		अगर (flow->क्रमeground.in_cs == IPUV3_COLORSPACE_UNKNOWN ||
		    flow->क्रमeground.in_cs == flow->out_cs)
			/*
			 * क्रमeground identical to output, apply color
			 * conversion on background
			 */
			ipu_dp_csc_init(flow, flow->background.in_cs,
					flow->out_cs, DP_COM_CONF_CSC_DEF_BG);
		अन्यथा
			ipu_dp_csc_init(flow, flow->क्रमeground.in_cs,
					flow->out_cs, DP_COM_CONF_CSC_DEF_FG);
	पूर्ण

	ipu_srm_dp_update(priv->ipu, true);

	mutex_unlock(&priv->mutex);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ipu_dp_setup_channel);

पूर्णांक ipu_dp_enable(काष्ठा ipu_soc *ipu)
अणु
	काष्ठा ipu_dp_priv *priv = ipu->dp_priv;

	mutex_lock(&priv->mutex);

	अगर (!priv->use_count)
		ipu_module_enable(priv->ipu, IPU_CONF_DP_EN);

	priv->use_count++;

	mutex_unlock(&priv->mutex);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ipu_dp_enable);

पूर्णांक ipu_dp_enable_channel(काष्ठा ipu_dp *dp)
अणु
	काष्ठा ipu_flow *flow = to_flow(dp);
	काष्ठा ipu_dp_priv *priv = flow->priv;
	u32 reg;

	अगर (!dp->क्रमeground)
		वापस 0;

	mutex_lock(&priv->mutex);

	reg = पढ़ोl(flow->base + DP_COM_CONF);
	reg |= DP_COM_CONF_FG_EN;
	ग_लिखोl(reg, flow->base + DP_COM_CONF);

	ipu_srm_dp_update(priv->ipu, true);

	mutex_unlock(&priv->mutex);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ipu_dp_enable_channel);

व्योम ipu_dp_disable_channel(काष्ठा ipu_dp *dp, bool sync)
अणु
	काष्ठा ipu_flow *flow = to_flow(dp);
	काष्ठा ipu_dp_priv *priv = flow->priv;
	u32 reg, csc;

	dp->in_cs = IPUV3_COLORSPACE_UNKNOWN;

	अगर (!dp->क्रमeground)
		वापस;

	mutex_lock(&priv->mutex);

	reg = पढ़ोl(flow->base + DP_COM_CONF);
	csc = reg & DP_COM_CONF_CSC_DEF_MASK;
	reg &= ~DP_COM_CONF_CSC_DEF_MASK;
	अगर (csc == DP_COM_CONF_CSC_DEF_BOTH || csc == DP_COM_CONF_CSC_DEF_BG)
		reg |= DP_COM_CONF_CSC_DEF_BG;

	reg &= ~DP_COM_CONF_FG_EN;
	ग_लिखोl(reg, flow->base + DP_COM_CONF);

	ग_लिखोl(0, flow->base + DP_FG_POS);
	ipu_srm_dp_update(priv->ipu, sync);

	mutex_unlock(&priv->mutex);
पूर्ण
EXPORT_SYMBOL_GPL(ipu_dp_disable_channel);

व्योम ipu_dp_disable(काष्ठा ipu_soc *ipu)
अणु
	काष्ठा ipu_dp_priv *priv = ipu->dp_priv;

	mutex_lock(&priv->mutex);

	priv->use_count--;

	अगर (!priv->use_count)
		ipu_module_disable(priv->ipu, IPU_CONF_DP_EN);

	अगर (priv->use_count < 0)
		priv->use_count = 0;

	mutex_unlock(&priv->mutex);
पूर्ण
EXPORT_SYMBOL_GPL(ipu_dp_disable);

काष्ठा ipu_dp *ipu_dp_get(काष्ठा ipu_soc *ipu, अचिन्हित पूर्णांक flow)
अणु
	काष्ठा ipu_dp_priv *priv = ipu->dp_priv;
	काष्ठा ipu_dp *dp;

	अगर ((flow >> 1) >= IPUV3_NUM_FLOWS)
		वापस ERR_PTR(-EINVAL);

	अगर (flow & 1)
		dp = &priv->flow[flow >> 1].क्रमeground;
	अन्यथा
		dp = &priv->flow[flow >> 1].background;

	अगर (dp->in_use)
		वापस ERR_PTR(-EBUSY);

	dp->in_use = true;

	वापस dp;
पूर्ण
EXPORT_SYMBOL_GPL(ipu_dp_get);

व्योम ipu_dp_put(काष्ठा ipu_dp *dp)
अणु
	dp->in_use = false;
पूर्ण
EXPORT_SYMBOL_GPL(ipu_dp_put);

पूर्णांक ipu_dp_init(काष्ठा ipu_soc *ipu, काष्ठा device *dev, अचिन्हित दीर्घ base)
अणु
	काष्ठा ipu_dp_priv *priv;
	पूर्णांक i;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;
	priv->dev = dev;
	priv->ipu = ipu;

	ipu->dp_priv = priv;

	priv->base = devm_ioremap(dev, base, PAGE_SIZE);
	अगर (!priv->base)
		वापस -ENOMEM;

	mutex_init(&priv->mutex);

	क्रम (i = 0; i < IPUV3_NUM_FLOWS; i++) अणु
		priv->flow[i].background.in_cs = IPUV3_COLORSPACE_UNKNOWN;
		priv->flow[i].क्रमeground.in_cs = IPUV3_COLORSPACE_UNKNOWN;
		priv->flow[i].क्रमeground.क्रमeground = true;
		priv->flow[i].base = priv->base + ipu_dp_flow_base[i];
		priv->flow[i].priv = priv;
	पूर्ण

	वापस 0;
पूर्ण

व्योम ipu_dp_निकास(काष्ठा ipu_soc *ipu)
अणु
पूर्ण
