<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (c) 2010 Sascha Hauer <s.hauer@pengutronix.de>
 * Copyright (C) 2005-2009 Freescale Semiconductor, Inc.
 */
#समावेश <linux/export.h>
#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/पन.स>

#समावेश <video/imx-ipu-v3.h>
#समावेश "ipu-prv.h"

#घोषणा DMFC_RD_CHAN		0x0000
#घोषणा DMFC_WR_CHAN		0x0004
#घोषणा DMFC_WR_CHAN_DEF	0x0008
#घोषणा DMFC_DP_CHAN		0x000c
#घोषणा DMFC_DP_CHAN_DEF	0x0010
#घोषणा DMFC_GENERAL1		0x0014
#घोषणा DMFC_GENERAL2		0x0018
#घोषणा DMFC_IC_CTRL		0x001c
#घोषणा DMFC_WR_CHAN_ALT	0x0020
#घोषणा DMFC_WR_CHAN_DEF_ALT	0x0024
#घोषणा DMFC_DP_CHAN_ALT	0x0028
#घोषणा DMFC_DP_CHAN_DEF_ALT	0x002c
#घोषणा DMFC_GENERAL1_ALT	0x0030
#घोषणा DMFC_STAT		0x0034

#घोषणा DMFC_WR_CHAN_1_28		0
#घोषणा DMFC_WR_CHAN_2_41		8
#घोषणा DMFC_WR_CHAN_1C_42		16
#घोषणा DMFC_WR_CHAN_2C_43		24

#घोषणा DMFC_DP_CHAN_5B_23		0
#घोषणा DMFC_DP_CHAN_5F_27		8
#घोषणा DMFC_DP_CHAN_6B_24		16
#घोषणा DMFC_DP_CHAN_6F_29		24

काष्ठा dmfc_channel_data अणु
	पूर्णांक		ipu_channel;
	अचिन्हित दीर्घ	channel_reg;
	अचिन्हित दीर्घ	shअगरt;
	अचिन्हित	eot_shअगरt;
	अचिन्हित	max_fअगरo_lines;
पूर्ण;

अटल स्थिर काष्ठा dmfc_channel_data dmfcdata[] = अणु
	अणु
		.ipu_channel	= IPUV3_CHANNEL_MEM_BG_SYNC,
		.channel_reg	= DMFC_DP_CHAN,
		.shअगरt		= DMFC_DP_CHAN_5B_23,
		.eot_shअगरt	= 20,
		.max_fअगरo_lines	= 3,
	पूर्ण, अणु
		.ipu_channel	= 24,
		.channel_reg	= DMFC_DP_CHAN,
		.shअगरt		= DMFC_DP_CHAN_6B_24,
		.eot_shअगरt	= 22,
		.max_fअगरo_lines	= 1,
	पूर्ण, अणु
		.ipu_channel	= IPUV3_CHANNEL_MEM_FG_SYNC,
		.channel_reg	= DMFC_DP_CHAN,
		.shअगरt		= DMFC_DP_CHAN_5F_27,
		.eot_shअगरt	= 21,
		.max_fअगरo_lines	= 2,
	पूर्ण, अणु
		.ipu_channel	= IPUV3_CHANNEL_MEM_DC_SYNC,
		.channel_reg	= DMFC_WR_CHAN,
		.shअगरt		= DMFC_WR_CHAN_1_28,
		.eot_shअगरt	= 16,
		.max_fअगरo_lines	= 2,
	पूर्ण, अणु
		.ipu_channel	= 29,
		.channel_reg	= DMFC_DP_CHAN,
		.shअगरt		= DMFC_DP_CHAN_6F_29,
		.eot_shअगरt	= 23,
		.max_fअगरo_lines	= 1,
	पूर्ण,
पूर्ण;

#घोषणा DMFC_NUM_CHANNELS	ARRAY_SIZE(dmfcdata)

काष्ठा ipu_dmfc_priv;

काष्ठा dmfc_channel अणु
	अचिन्हित			slots;
	काष्ठा ipu_soc			*ipu;
	काष्ठा ipu_dmfc_priv		*priv;
	स्थिर काष्ठा dmfc_channel_data	*data;
पूर्ण;

काष्ठा ipu_dmfc_priv अणु
	काष्ठा ipu_soc *ipu;
	काष्ठा device *dev;
	काष्ठा dmfc_channel channels[DMFC_NUM_CHANNELS];
	काष्ठा mutex mutex;
	व्योम __iomem *base;
	पूर्णांक use_count;
पूर्ण;

पूर्णांक ipu_dmfc_enable_channel(काष्ठा dmfc_channel *dmfc)
अणु
	काष्ठा ipu_dmfc_priv *priv = dmfc->priv;
	mutex_lock(&priv->mutex);

	अगर (!priv->use_count)
		ipu_module_enable(priv->ipu, IPU_CONF_DMFC_EN);

	priv->use_count++;

	mutex_unlock(&priv->mutex);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ipu_dmfc_enable_channel);

व्योम ipu_dmfc_disable_channel(काष्ठा dmfc_channel *dmfc)
अणु
	काष्ठा ipu_dmfc_priv *priv = dmfc->priv;

	mutex_lock(&priv->mutex);

	priv->use_count--;

	अगर (!priv->use_count)
		ipu_module_disable(priv->ipu, IPU_CONF_DMFC_EN);

	अगर (priv->use_count < 0)
		priv->use_count = 0;

	mutex_unlock(&priv->mutex);
पूर्ण
EXPORT_SYMBOL_GPL(ipu_dmfc_disable_channel);

व्योम ipu_dmfc_config_रुको4eot(काष्ठा dmfc_channel *dmfc, पूर्णांक width)
अणु
	काष्ठा ipu_dmfc_priv *priv = dmfc->priv;
	u32 dmfc_gen1;

	mutex_lock(&priv->mutex);

	dmfc_gen1 = पढ़ोl(priv->base + DMFC_GENERAL1);

	अगर ((dmfc->slots * 64 * 4) / width > dmfc->data->max_fअगरo_lines)
		dmfc_gen1 |= 1 << dmfc->data->eot_shअगरt;
	अन्यथा
		dmfc_gen1 &= ~(1 << dmfc->data->eot_shअगरt);

	ग_लिखोl(dmfc_gen1, priv->base + DMFC_GENERAL1);

	mutex_unlock(&priv->mutex);
पूर्ण
EXPORT_SYMBOL_GPL(ipu_dmfc_config_रुको4eot);

काष्ठा dmfc_channel *ipu_dmfc_get(काष्ठा ipu_soc *ipu, पूर्णांक ipu_channel)
अणु
	काष्ठा ipu_dmfc_priv *priv = ipu->dmfc_priv;
	पूर्णांक i;

	क्रम (i = 0; i < DMFC_NUM_CHANNELS; i++)
		अगर (dmfcdata[i].ipu_channel == ipu_channel)
			वापस &priv->channels[i];
	वापस ERR_PTR(-ENODEV);
पूर्ण
EXPORT_SYMBOL_GPL(ipu_dmfc_get);

व्योम ipu_dmfc_put(काष्ठा dmfc_channel *dmfc)
अणु
पूर्ण
EXPORT_SYMBOL_GPL(ipu_dmfc_put);

पूर्णांक ipu_dmfc_init(काष्ठा ipu_soc *ipu, काष्ठा device *dev, अचिन्हित दीर्घ base,
		काष्ठा clk *ipu_clk)
अणु
	काष्ठा ipu_dmfc_priv *priv;
	पूर्णांक i;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->base = devm_ioremap(dev, base, PAGE_SIZE);
	अगर (!priv->base)
		वापस -ENOMEM;

	priv->dev = dev;
	priv->ipu = ipu;
	mutex_init(&priv->mutex);

	ipu->dmfc_priv = priv;

	क्रम (i = 0; i < DMFC_NUM_CHANNELS; i++) अणु
		priv->channels[i].priv = priv;
		priv->channels[i].ipu = ipu;
		priv->channels[i].data = &dmfcdata[i];

		अगर (dmfcdata[i].ipu_channel == IPUV3_CHANNEL_MEM_BG_SYNC ||
		    dmfcdata[i].ipu_channel == IPUV3_CHANNEL_MEM_FG_SYNC ||
		    dmfcdata[i].ipu_channel == IPUV3_CHANNEL_MEM_DC_SYNC)
			priv->channels[i].slots = 2;
	पूर्ण

	ग_लिखोl(0x00000050, priv->base + DMFC_WR_CHAN);
	ग_लिखोl(0x00005654, priv->base + DMFC_DP_CHAN);
	ग_लिखोl(0x202020f6, priv->base + DMFC_WR_CHAN_DEF);
	ग_लिखोl(0x2020f6f6, priv->base + DMFC_DP_CHAN_DEF);
	ग_लिखोl(0x00000003, priv->base + DMFC_GENERAL1);

	वापस 0;
पूर्ण

व्योम ipu_dmfc_निकास(काष्ठा ipu_soc *ipu)
अणु
पूर्ण
