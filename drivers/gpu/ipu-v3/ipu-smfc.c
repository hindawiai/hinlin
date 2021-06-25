<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2008-2010 Freescale Semiconductor, Inc. All Rights Reserved.
 */
#समावेश <linux/export.h>
#समावेश <linux/types.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/spinlock.h>
#समावेश <linux/delay.h>
#समावेश <linux/clk.h>
#समावेश <video/imx-ipu-v3.h>

#समावेश "ipu-prv.h"

काष्ठा ipu_smfc अणु
	काष्ठा ipu_smfc_priv *priv;
	पूर्णांक chno;
	bool inuse;
पूर्ण;

काष्ठा ipu_smfc_priv अणु
	व्योम __iomem *base;
	spinlock_t lock;
	काष्ठा ipu_soc *ipu;
	काष्ठा ipu_smfc channel[4];
	पूर्णांक use_count;
पूर्ण;

/*SMFC Registers */
#घोषणा SMFC_MAP	0x0000
#घोषणा SMFC_WMC	0x0004
#घोषणा SMFC_BS		0x0008

पूर्णांक ipu_smfc_set_burstsize(काष्ठा ipu_smfc *smfc, पूर्णांक burstsize)
अणु
	काष्ठा ipu_smfc_priv *priv = smfc->priv;
	अचिन्हित दीर्घ flags;
	u32 val, shअगरt;

	spin_lock_irqsave(&priv->lock, flags);

	shअगरt = smfc->chno * 4;
	val = पढ़ोl(priv->base + SMFC_BS);
	val &= ~(0xf << shअगरt);
	val |= burstsize << shअगरt;
	ग_लिखोl(val, priv->base + SMFC_BS);

	spin_unlock_irqrestore(&priv->lock, flags);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ipu_smfc_set_burstsize);

पूर्णांक ipu_smfc_map_channel(काष्ठा ipu_smfc *smfc, पूर्णांक csi_id, पूर्णांक mipi_id)
अणु
	काष्ठा ipu_smfc_priv *priv = smfc->priv;
	अचिन्हित दीर्घ flags;
	u32 val, shअगरt;

	spin_lock_irqsave(&priv->lock, flags);

	shअगरt = smfc->chno * 3;
	val = पढ़ोl(priv->base + SMFC_MAP);
	val &= ~(0x7 << shअगरt);
	val |= ((csi_id << 2) | mipi_id) << shअगरt;
	ग_लिखोl(val, priv->base + SMFC_MAP);

	spin_unlock_irqrestore(&priv->lock, flags);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ipu_smfc_map_channel);

पूर्णांक ipu_smfc_set_watermark(काष्ठा ipu_smfc *smfc, u32 set_level, u32 clr_level)
अणु
	काष्ठा ipu_smfc_priv *priv = smfc->priv;
	अचिन्हित दीर्घ flags;
	u32 val, shअगरt;

	spin_lock_irqsave(&priv->lock, flags);

	shअगरt = smfc->chno * 6 + (smfc->chno > 1 ? 4 : 0);
	val = पढ़ोl(priv->base + SMFC_WMC);
	val &= ~(0x3f << shअगरt);
	val |= ((clr_level << 3) | set_level) << shअगरt;
	ग_लिखोl(val, priv->base + SMFC_WMC);

	spin_unlock_irqrestore(&priv->lock, flags);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ipu_smfc_set_watermark);

पूर्णांक ipu_smfc_enable(काष्ठा ipu_smfc *smfc)
अणु
	काष्ठा ipu_smfc_priv *priv = smfc->priv;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&priv->lock, flags);

	अगर (!priv->use_count)
		ipu_module_enable(priv->ipu, IPU_CONF_SMFC_EN);

	priv->use_count++;

	spin_unlock_irqrestore(&priv->lock, flags);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ipu_smfc_enable);

पूर्णांक ipu_smfc_disable(काष्ठा ipu_smfc *smfc)
अणु
	काष्ठा ipu_smfc_priv *priv = smfc->priv;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&priv->lock, flags);

	priv->use_count--;

	अगर (!priv->use_count)
		ipu_module_disable(priv->ipu, IPU_CONF_SMFC_EN);

	अगर (priv->use_count < 0)
		priv->use_count = 0;

	spin_unlock_irqrestore(&priv->lock, flags);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ipu_smfc_disable);

काष्ठा ipu_smfc *ipu_smfc_get(काष्ठा ipu_soc *ipu, अचिन्हित पूर्णांक chno)
अणु
	काष्ठा ipu_smfc_priv *priv = ipu->smfc_priv;
	काष्ठा ipu_smfc *smfc, *ret;
	अचिन्हित दीर्घ flags;

	अगर (chno >= 4)
		वापस ERR_PTR(-EINVAL);

	smfc = &priv->channel[chno];
	ret = smfc;

	spin_lock_irqsave(&priv->lock, flags);

	अगर (smfc->inuse) अणु
		ret = ERR_PTR(-EBUSY);
		जाओ unlock;
	पूर्ण

	smfc->inuse = true;
unlock:
	spin_unlock_irqrestore(&priv->lock, flags);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(ipu_smfc_get);

व्योम ipu_smfc_put(काष्ठा ipu_smfc *smfc)
अणु
	काष्ठा ipu_smfc_priv *priv = smfc->priv;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&priv->lock, flags);
	smfc->inuse = false;
	spin_unlock_irqrestore(&priv->lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(ipu_smfc_put);

पूर्णांक ipu_smfc_init(काष्ठा ipu_soc *ipu, काष्ठा device *dev,
		  अचिन्हित दीर्घ base)
अणु
	काष्ठा ipu_smfc_priv *priv;
	पूर्णांक i;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	ipu->smfc_priv = priv;
	spin_lock_init(&priv->lock);
	priv->ipu = ipu;

	priv->base = devm_ioremap(dev, base, PAGE_SIZE);
	अगर (!priv->base)
		वापस -ENOMEM;

	क्रम (i = 0; i < 4; i++) अणु
		priv->channel[i].priv = priv;
		priv->channel[i].chno = i;
	पूर्ण

	pr_debug("%s: ioremap 0x%08lx -> %p\n", __func__, base, priv->base);

	वापस 0;
पूर्ण

व्योम ipu_smfc_निकास(काष्ठा ipu_soc *ipu)
अणु
पूर्ण
