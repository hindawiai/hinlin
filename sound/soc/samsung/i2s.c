<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// ALSA SoC Audio Layer - Samsung I2S Controller driver
//
// Copyright (c) 2010 Samsung Electronics Co. Ltd.
//	Jaswinder Singh <jassisinghbrar@gmail.com>

#समावेश <dt-bindings/sound/samsung-i2s.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/pm_runसमय.स>

#समावेश <sound/soc.h>
#समावेश <sound/pcm_params.h>

#समावेश <linux/platक्रमm_data/asoc-s3c.h>

#समावेश "dma.h"
#समावेश "idma.h"
#समावेश "i2s.h"
#समावेश "i2s-regs.h"

#घोषणा msecs_to_loops(t) (loops_per_jअगरfy / 1000 * HZ * t)

#घोषणा SAMSUNG_I2S_ID_PRIMARY		1
#घोषणा SAMSUNG_I2S_ID_SECONDARY	2

काष्ठा samsung_i2s_variant_regs अणु
	अचिन्हित पूर्णांक	bfs_off;
	अचिन्हित पूर्णांक	rfs_off;
	अचिन्हित पूर्णांक	sdf_off;
	अचिन्हित पूर्णांक	txr_off;
	अचिन्हित पूर्णांक	rclksrc_off;
	अचिन्हित पूर्णांक	mss_off;
	अचिन्हित पूर्णांक	cdclkcon_off;
	अचिन्हित पूर्णांक	lrp_off;
	अचिन्हित पूर्णांक	bfs_mask;
	अचिन्हित पूर्णांक	rfs_mask;
	अचिन्हित पूर्णांक	ftx0cnt_off;
पूर्ण;

काष्ठा samsung_i2s_dai_data अणु
	u32 quirks;
	अचिन्हित पूर्णांक pcm_rates;
	स्थिर काष्ठा samsung_i2s_variant_regs *i2s_variant_regs;
पूर्ण;

काष्ठा i2s_dai अणु
	/* Platक्रमm device क्रम this DAI */
	काष्ठा platक्रमm_device *pdev;

	/* Frame घड़ी */
	अचिन्हित frmclk;
	/*
	 * Specअगरically requested RCLK, BCLK by machine driver.
	 * 0 indicates CPU driver is मुक्त to choose any value.
	 */
	अचिन्हित rfs, bfs;
	/* Poपूर्णांकer to the Primary_Fअगरo अगर this is Sec_Fअगरo, शून्य otherwise */
	काष्ठा i2s_dai *pri_dai;
	/* Poपूर्णांकer to the Secondary_Fअगरo अगर it has one, शून्य otherwise */
	काष्ठा i2s_dai *sec_dai;

#घोषणा DAI_OPENED	(1 << 0) /* DAI is खोलोed */
#घोषणा DAI_MANAGER	(1 << 1) /* DAI is the manager */
	अचिन्हित mode;

	/* Driver क्रम this DAI */
	काष्ठा snd_soc_dai_driver *drv;

	/* DMA parameters */
	काष्ठा snd_dmaengine_dai_dma_data dma_playback;
	काष्ठा snd_dmaengine_dai_dma_data dma_capture;
	काष्ठा snd_dmaengine_dai_dma_data idma_playback;
	dma_filter_fn filter;

	काष्ठा samsung_i2s_priv *priv;
पूर्ण;

काष्ठा samsung_i2s_priv अणु
	काष्ठा platक्रमm_device *pdev;
	काष्ठा platक्रमm_device *pdev_sec;

	/* Lock क्रम cross पूर्णांकerface checks */
	spinlock_t pcm_lock;

	/* CPU DAIs and their corresponding drivers */
	काष्ठा i2s_dai *dai;
	काष्ठा snd_soc_dai_driver *dai_drv;
	पूर्णांक num_dais;

	/* The I2S controller's core घड़ी */
	काष्ठा clk *clk;

	/* Clock क्रम generating I2S संकेतs */
	काष्ठा clk *op_clk;

	/* Rate of RCLK source घड़ी */
	अचिन्हित दीर्घ rclk_srcrate;

	/* Cache of selected I2S रेजिस्टरs क्रम प्रणाली suspend */
	u32 suspend_i2smod;
	u32 suspend_i2scon;
	u32 suspend_i2spsr;

	स्थिर काष्ठा samsung_i2s_variant_regs *variant_regs;
	u32 quirks;

	/* The घड़ी provider's data */
	काष्ठा clk *clk_table[3];
	काष्ठा clk_onecell_data clk_data;

	/* Spinlock protecting member fields below */
	spinlock_t lock;

	/* Memory mapped SFR region */
	व्योम __iomem *addr;

	/* A flag indicating the I2S slave mode operation */
	bool slave_mode;
पूर्ण;

/* Returns true अगर this is the 'overlay' stereo DAI */
अटल अंतरभूत bool is_secondary(काष्ठा i2s_dai *i2s)
अणु
	वापस i2s->drv->id == SAMSUNG_I2S_ID_SECONDARY;
पूर्ण

/* If this पूर्णांकerface of the controller is transmitting data */
अटल अंतरभूत bool tx_active(काष्ठा i2s_dai *i2s)
अणु
	u32 active;

	अगर (!i2s)
		वापस false;

	active = पढ़ोl(i2s->priv->addr + I2SCON);

	अगर (is_secondary(i2s))
		active &= CON_TXSDMA_ACTIVE;
	अन्यथा
		active &= CON_TXDMA_ACTIVE;

	वापस active ? true : false;
पूर्ण

/* Return poपूर्णांकer to the other DAI */
अटल अंतरभूत काष्ठा i2s_dai *get_other_dai(काष्ठा i2s_dai *i2s)
अणु
	वापस i2s->pri_dai ? : i2s->sec_dai;
पूर्ण

/* If the other पूर्णांकerface of the controller is transmitting data */
अटल अंतरभूत bool other_tx_active(काष्ठा i2s_dai *i2s)
अणु
	काष्ठा i2s_dai *other = get_other_dai(i2s);

	वापस tx_active(other);
पूर्ण

/* If any पूर्णांकerface of the controller is transmitting data */
अटल अंतरभूत bool any_tx_active(काष्ठा i2s_dai *i2s)
अणु
	वापस tx_active(i2s) || other_tx_active(i2s);
पूर्ण

/* If this पूर्णांकerface of the controller is receiving data */
अटल अंतरभूत bool rx_active(काष्ठा i2s_dai *i2s)
अणु
	u32 active;

	अगर (!i2s)
		वापस false;

	active = पढ़ोl(i2s->priv->addr + I2SCON) & CON_RXDMA_ACTIVE;

	वापस active ? true : false;
पूर्ण

/* If the other पूर्णांकerface of the controller is receiving data */
अटल अंतरभूत bool other_rx_active(काष्ठा i2s_dai *i2s)
अणु
	काष्ठा i2s_dai *other = get_other_dai(i2s);

	वापस rx_active(other);
पूर्ण

/* If any पूर्णांकerface of the controller is receiving data */
अटल अंतरभूत bool any_rx_active(काष्ठा i2s_dai *i2s)
अणु
	वापस rx_active(i2s) || other_rx_active(i2s);
पूर्ण

/* If the other DAI is transmitting or receiving data */
अटल अंतरभूत bool other_active(काष्ठा i2s_dai *i2s)
अणु
	वापस other_rx_active(i2s) || other_tx_active(i2s);
पूर्ण

/* If this DAI is transmitting or receiving data */
अटल अंतरभूत bool this_active(काष्ठा i2s_dai *i2s)
अणु
	वापस tx_active(i2s) || rx_active(i2s);
पूर्ण

/* If the controller is active anyway */
अटल अंतरभूत bool any_active(काष्ठा i2s_dai *i2s)
अणु
	वापस this_active(i2s) || other_active(i2s);
पूर्ण

अटल अंतरभूत काष्ठा i2s_dai *to_info(काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा samsung_i2s_priv *priv = snd_soc_dai_get_drvdata(dai);

	वापस &priv->dai[dai->id - 1];
पूर्ण

अटल अंतरभूत bool is_खोलोed(काष्ठा i2s_dai *i2s)
अणु
	अगर (i2s && (i2s->mode & DAI_OPENED))
		वापस true;
	अन्यथा
		वापस false;
पूर्ण

अटल अंतरभूत bool is_manager(काष्ठा i2s_dai *i2s)
अणु
	अगर (is_खोलोed(i2s) && (i2s->mode & DAI_MANAGER))
		वापस true;
	अन्यथा
		वापस false;
पूर्ण

/* Read RCLK of I2S (in multiples of LRCLK) */
अटल अंतरभूत अचिन्हित get_rfs(काष्ठा i2s_dai *i2s)
अणु
	काष्ठा samsung_i2s_priv *priv = i2s->priv;
	u32 rfs;

	rfs = पढ़ोl(priv->addr + I2SMOD) >> priv->variant_regs->rfs_off;
	rfs &= priv->variant_regs->rfs_mask;

	चयन (rfs) अणु
	हाल 7: वापस 192;
	हाल 6: वापस 96;
	हाल 5: वापस 128;
	हाल 4: वापस 64;
	हाल 3:	वापस 768;
	हाल 2: वापस 384;
	हाल 1:	वापस 512;
	शेष: वापस 256;
	पूर्ण
पूर्ण

/* Write RCLK of I2S (in multiples of LRCLK) */
अटल अंतरभूत व्योम set_rfs(काष्ठा i2s_dai *i2s, अचिन्हित rfs)
अणु
	काष्ठा samsung_i2s_priv *priv = i2s->priv;
	u32 mod = पढ़ोl(priv->addr + I2SMOD);
	पूर्णांक rfs_shअगरt = priv->variant_regs->rfs_off;

	mod &= ~(priv->variant_regs->rfs_mask << rfs_shअगरt);

	चयन (rfs) अणु
	हाल 192:
		mod |= (EXYNOS7_MOD_RCLK_192FS << rfs_shअगरt);
		अवरोध;
	हाल 96:
		mod |= (EXYNOS7_MOD_RCLK_96FS << rfs_shअगरt);
		अवरोध;
	हाल 128:
		mod |= (EXYNOS7_MOD_RCLK_128FS << rfs_shअगरt);
		अवरोध;
	हाल 64:
		mod |= (EXYNOS7_MOD_RCLK_64FS << rfs_shअगरt);
		अवरोध;
	हाल 768:
		mod |= (MOD_RCLK_768FS << rfs_shअगरt);
		अवरोध;
	हाल 512:
		mod |= (MOD_RCLK_512FS << rfs_shअगरt);
		अवरोध;
	हाल 384:
		mod |= (MOD_RCLK_384FS << rfs_shअगरt);
		अवरोध;
	शेष:
		mod |= (MOD_RCLK_256FS << rfs_shअगरt);
		अवरोध;
	पूर्ण

	ग_लिखोl(mod, priv->addr + I2SMOD);
पूर्ण

/* Read bit-घड़ी of I2S (in multiples of LRCLK) */
अटल अंतरभूत अचिन्हित get_bfs(काष्ठा i2s_dai *i2s)
अणु
	काष्ठा samsung_i2s_priv *priv = i2s->priv;
	u32 bfs;

	bfs = पढ़ोl(priv->addr + I2SMOD) >> priv->variant_regs->bfs_off;
	bfs &= priv->variant_regs->bfs_mask;

	चयन (bfs) अणु
	हाल 8: वापस 256;
	हाल 7: वापस 192;
	हाल 6: वापस 128;
	हाल 5: वापस 96;
	हाल 4: वापस 64;
	हाल 3: वापस 24;
	हाल 2: वापस 16;
	हाल 1:	वापस 48;
	शेष: वापस 32;
	पूर्ण
पूर्ण

/* Write bit-घड़ी of I2S (in multiples of LRCLK) */
अटल अंतरभूत व्योम set_bfs(काष्ठा i2s_dai *i2s, अचिन्हित bfs)
अणु
	काष्ठा samsung_i2s_priv *priv = i2s->priv;
	u32 mod = पढ़ोl(priv->addr + I2SMOD);
	पूर्णांक tdm = priv->quirks & QUIRK_SUPPORTS_TDM;
	पूर्णांक bfs_shअगरt = priv->variant_regs->bfs_off;

	/* Non-TDM I2S controllers करो not support BCLK > 48 * FS */
	अगर (!tdm && bfs > 48) अणु
		dev_err(&i2s->pdev->dev, "Unsupported BCLK divider\n");
		वापस;
	पूर्ण

	mod &= ~(priv->variant_regs->bfs_mask << bfs_shअगरt);

	चयन (bfs) अणु
	हाल 48:
		mod |= (MOD_BCLK_48FS << bfs_shअगरt);
		अवरोध;
	हाल 32:
		mod |= (MOD_BCLK_32FS << bfs_shअगरt);
		अवरोध;
	हाल 24:
		mod |= (MOD_BCLK_24FS << bfs_shअगरt);
		अवरोध;
	हाल 16:
		mod |= (MOD_BCLK_16FS << bfs_shअगरt);
		अवरोध;
	हाल 64:
		mod |= (EXYNOS5420_MOD_BCLK_64FS << bfs_shअगरt);
		अवरोध;
	हाल 96:
		mod |= (EXYNOS5420_MOD_BCLK_96FS << bfs_shअगरt);
		अवरोध;
	हाल 128:
		mod |= (EXYNOS5420_MOD_BCLK_128FS << bfs_shअगरt);
		अवरोध;
	हाल 192:
		mod |= (EXYNOS5420_MOD_BCLK_192FS << bfs_shअगरt);
		अवरोध;
	हाल 256:
		mod |= (EXYNOS5420_MOD_BCLK_256FS << bfs_shअगरt);
		अवरोध;
	शेष:
		dev_err(&i2s->pdev->dev, "Wrong BCLK Divider!\n");
		वापस;
	पूर्ण

	ग_लिखोl(mod, priv->addr + I2SMOD);
पूर्ण

/* Sample size */
अटल अंतरभूत पूर्णांक get_blc(काष्ठा i2s_dai *i2s)
अणु
	पूर्णांक blc = पढ़ोl(i2s->priv->addr + I2SMOD);

	blc = (blc >> 13) & 0x3;

	चयन (blc) अणु
	हाल 2: वापस 24;
	हाल 1:	वापस 8;
	शेष: वापस 16;
	पूर्ण
पूर्ण

/* TX channel control */
अटल व्योम i2s_txctrl(काष्ठा i2s_dai *i2s, पूर्णांक on)
अणु
	काष्ठा samsung_i2s_priv *priv = i2s->priv;
	व्योम __iomem *addr = priv->addr;
	पूर्णांक txr_off = priv->variant_regs->txr_off;
	u32 con = पढ़ोl(addr + I2SCON);
	u32 mod = पढ़ोl(addr + I2SMOD) & ~(3 << txr_off);

	अगर (on) अणु
		con |= CON_ACTIVE;
		con &= ~CON_TXCH_PAUSE;

		अगर (is_secondary(i2s)) अणु
			con |= CON_TXSDMA_ACTIVE;
			con &= ~CON_TXSDMA_PAUSE;
		पूर्ण अन्यथा अणु
			con |= CON_TXDMA_ACTIVE;
			con &= ~CON_TXDMA_PAUSE;
		पूर्ण

		अगर (any_rx_active(i2s))
			mod |= 2 << txr_off;
		अन्यथा
			mod |= 0 << txr_off;
	पूर्ण अन्यथा अणु
		अगर (is_secondary(i2s)) अणु
			con |=  CON_TXSDMA_PAUSE;
			con &= ~CON_TXSDMA_ACTIVE;
		पूर्ण अन्यथा अणु
			con |=  CON_TXDMA_PAUSE;
			con &= ~CON_TXDMA_ACTIVE;
		पूर्ण

		अगर (other_tx_active(i2s)) अणु
			ग_लिखोl(con, addr + I2SCON);
			वापस;
		पूर्ण

		con |=  CON_TXCH_PAUSE;

		अगर (any_rx_active(i2s))
			mod |= 1 << txr_off;
		अन्यथा
			con &= ~CON_ACTIVE;
	पूर्ण

	ग_लिखोl(mod, addr + I2SMOD);
	ग_लिखोl(con, addr + I2SCON);
पूर्ण

/* RX Channel Control */
अटल व्योम i2s_rxctrl(काष्ठा i2s_dai *i2s, पूर्णांक on)
अणु
	काष्ठा samsung_i2s_priv *priv = i2s->priv;
	व्योम __iomem *addr = priv->addr;
	पूर्णांक txr_off = priv->variant_regs->txr_off;
	u32 con = पढ़ोl(addr + I2SCON);
	u32 mod = पढ़ोl(addr + I2SMOD) & ~(3 << txr_off);

	अगर (on) अणु
		con |= CON_RXDMA_ACTIVE | CON_ACTIVE;
		con &= ~(CON_RXDMA_PAUSE | CON_RXCH_PAUSE);

		अगर (any_tx_active(i2s))
			mod |= 2 << txr_off;
		अन्यथा
			mod |= 1 << txr_off;
	पूर्ण अन्यथा अणु
		con |=  CON_RXDMA_PAUSE | CON_RXCH_PAUSE;
		con &= ~CON_RXDMA_ACTIVE;

		अगर (any_tx_active(i2s))
			mod |= 0 << txr_off;
		अन्यथा
			con &= ~CON_ACTIVE;
	पूर्ण

	ग_लिखोl(mod, addr + I2SMOD);
	ग_लिखोl(con, addr + I2SCON);
पूर्ण

/* Flush FIFO of an पूर्णांकerface */
अटल अंतरभूत व्योम i2s_fअगरo(काष्ठा i2s_dai *i2s, u32 flush)
अणु
	व्योम __iomem *fic;
	u32 val;

	अगर (!i2s)
		वापस;

	अगर (is_secondary(i2s))
		fic = i2s->priv->addr + I2SFICS;
	अन्यथा
		fic = i2s->priv->addr + I2SFIC;

	/* Flush the FIFO */
	ग_लिखोl(पढ़ोl(fic) | flush, fic);

	/* Be patient */
	val = msecs_to_loops(1) / 1000; /* 1 usec */
	जबतक (--val)
		cpu_relax();

	ग_लिखोl(पढ़ोl(fic) & ~flush, fic);
पूर्ण

अटल पूर्णांक i2s_set_sysclk(काष्ठा snd_soc_dai *dai, पूर्णांक clk_id, अचिन्हित पूर्णांक rfs,
			  पूर्णांक dir)
अणु
	काष्ठा samsung_i2s_priv *priv = snd_soc_dai_get_drvdata(dai);
	काष्ठा i2s_dai *i2s = to_info(dai);
	काष्ठा i2s_dai *other = get_other_dai(i2s);
	स्थिर काष्ठा samsung_i2s_variant_regs *i2s_regs = priv->variant_regs;
	अचिन्हित पूर्णांक cdcon_mask = 1 << i2s_regs->cdclkcon_off;
	अचिन्हित पूर्णांक rsrc_mask = 1 << i2s_regs->rclksrc_off;
	u32 mod, mask, val = 0;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	pm_runसमय_get_sync(dai->dev);

	spin_lock_irqsave(&priv->lock, flags);
	mod = पढ़ोl(priv->addr + I2SMOD);
	spin_unlock_irqrestore(&priv->lock, flags);

	चयन (clk_id) अणु
	हाल SAMSUNG_I2S_OPCLK:
		mask = MOD_OPCLK_MASK;
		val = (dir << MOD_OPCLK_SHIFT) & MOD_OPCLK_MASK;
		अवरोध;
	हाल SAMSUNG_I2S_CDCLK:
		mask = 1 << i2s_regs->cdclkcon_off;
		/* Shouldn't matter in GATING(CLOCK_IN) mode */
		अगर (dir == SND_SOC_CLOCK_IN)
			rfs = 0;

		अगर ((rfs && other && other->rfs && (other->rfs != rfs)) ||
				(any_active(i2s) &&
				(((dir == SND_SOC_CLOCK_IN)
					&& !(mod & cdcon_mask)) ||
				((dir == SND_SOC_CLOCK_OUT)
					&& (mod & cdcon_mask))))) अणु
			dev_err(&i2s->pdev->dev,
				"%s:%d Other DAI busy\n", __func__, __LINE__);
			ret = -EAGAIN;
			जाओ err;
		पूर्ण

		अगर (dir == SND_SOC_CLOCK_IN)
			val = 1 << i2s_regs->cdclkcon_off;

		i2s->rfs = rfs;
		अवरोध;

	हाल SAMSUNG_I2S_RCLKSRC_0: /* घड़ी corrsponding to IISMOD[10] := 0 */
	हाल SAMSUNG_I2S_RCLKSRC_1: /* घड़ी corrsponding to IISMOD[10] := 1 */
		mask = 1 << i2s_regs->rclksrc_off;

		अगर ((priv->quirks & QUIRK_NO_MUXPSR)
				|| (clk_id == SAMSUNG_I2S_RCLKSRC_0))
			clk_id = 0;
		अन्यथा
			clk_id = 1;

		अगर (!any_active(i2s)) अणु
			अगर (priv->op_clk && !IS_ERR(priv->op_clk)) अणु
				अगर ((clk_id && !(mod & rsrc_mask)) ||
					(!clk_id && (mod & rsrc_mask))) अणु
					clk_disable_unprepare(priv->op_clk);
					clk_put(priv->op_clk);
				पूर्ण अन्यथा अणु
					priv->rclk_srcrate =
						clk_get_rate(priv->op_clk);
					जाओ करोne;
				पूर्ण
			पूर्ण

			अगर (clk_id)
				priv->op_clk = clk_get(&i2s->pdev->dev,
						"i2s_opclk1");
			अन्यथा
				priv->op_clk = clk_get(&i2s->pdev->dev,
						"i2s_opclk0");

			अगर (WARN_ON(IS_ERR(priv->op_clk))) अणु
				ret = PTR_ERR(priv->op_clk);
				priv->op_clk = शून्य;
				जाओ err;
			पूर्ण

			ret = clk_prepare_enable(priv->op_clk);
			अगर (ret) अणु
				clk_put(priv->op_clk);
				priv->op_clk = शून्य;
				जाओ err;
			पूर्ण
			priv->rclk_srcrate = clk_get_rate(priv->op_clk);

		पूर्ण अन्यथा अगर ((!clk_id && (mod & rsrc_mask))
				|| (clk_id && !(mod & rsrc_mask))) अणु
			dev_err(&i2s->pdev->dev,
				"%s:%d Other DAI busy\n", __func__, __LINE__);
			ret = -EAGAIN;
			जाओ err;
		पूर्ण अन्यथा अणु
			/* Call can't be on the active DAI */
			जाओ करोne;
		पूर्ण

		अगर (clk_id == 1)
			val = 1 << i2s_regs->rclksrc_off;
		अवरोध;
	शेष:
		dev_err(&i2s->pdev->dev, "We don't serve that!\n");
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	spin_lock_irqsave(&priv->lock, flags);
	mod = पढ़ोl(priv->addr + I2SMOD);
	mod = (mod & ~mask) | val;
	ग_लिखोl(mod, priv->addr + I2SMOD);
	spin_unlock_irqrestore(&priv->lock, flags);
करोne:
	pm_runसमय_put(dai->dev);

	वापस 0;
err:
	pm_runसमय_put(dai->dev);
	वापस ret;
पूर्ण

अटल पूर्णांक i2s_set_fmt(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा samsung_i2s_priv *priv = snd_soc_dai_get_drvdata(dai);
	काष्ठा i2s_dai *i2s = to_info(dai);
	पूर्णांक lrp_shअगरt, sdf_shअगरt, sdf_mask, lrp_rlow, mod_slave;
	u32 mod, पंचांगp = 0;
	अचिन्हित दीर्घ flags;

	lrp_shअगरt = priv->variant_regs->lrp_off;
	sdf_shअगरt = priv->variant_regs->sdf_off;
	mod_slave = 1 << priv->variant_regs->mss_off;

	sdf_mask = MOD_SDF_MASK << sdf_shअगरt;
	lrp_rlow = MOD_LR_RLOW << lrp_shअगरt;

	/* Format is priority */
	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_RIGHT_J:
		पंचांगp |= lrp_rlow;
		पंचांगp |= (MOD_SDF_MSB << sdf_shअगरt);
		अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:
		पंचांगp |= lrp_rlow;
		पंचांगp |= (MOD_SDF_LSB << sdf_shअगरt);
		अवरोध;
	हाल SND_SOC_DAIFMT_I2S:
		पंचांगp |= (MOD_SDF_IIS << sdf_shअगरt);
		अवरोध;
	शेष:
		dev_err(&i2s->pdev->dev, "Format not supported\n");
		वापस -EINVAL;
	पूर्ण

	/*
	 * INV flag is relative to the FORMAT flag - अगर set it simply
	 * flips the polarity specअगरied by the Standard
	 */
	चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
	हाल SND_SOC_DAIFMT_NB_NF:
		अवरोध;
	हाल SND_SOC_DAIFMT_NB_IF:
		अगर (पंचांगp & lrp_rlow)
			पंचांगp &= ~lrp_rlow;
		अन्यथा
			पंचांगp |= lrp_rlow;
		अवरोध;
	शेष:
		dev_err(&i2s->pdev->dev, "Polarity not supported\n");
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBM_CFM:
		पंचांगp |= mod_slave;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBS_CFS:
		/*
		 * Set शेष source घड़ी in Master mode, only when the
		 * CLK_I2S_RCLK_SRC घड़ी is not exposed so we ensure any
		 * घड़ी configuration asचिन्हित in DT is not overwritten.
		 */
		अगर (priv->rclk_srcrate == 0 && priv->clk_data.clks == शून्य)
			i2s_set_sysclk(dai, SAMSUNG_I2S_RCLKSRC_0,
							0, SND_SOC_CLOCK_IN);
		अवरोध;
	शेष:
		dev_err(&i2s->pdev->dev, "master/slave format not supported\n");
		वापस -EINVAL;
	पूर्ण

	pm_runसमय_get_sync(dai->dev);
	spin_lock_irqsave(&priv->lock, flags);
	mod = पढ़ोl(priv->addr + I2SMOD);
	/*
	 * Don't change the I2S mode अगर any controller is active on this
	 * channel.
	 */
	अगर (any_active(i2s) &&
		((mod & (sdf_mask | lrp_rlow | mod_slave)) != पंचांगp)) अणु
		spin_unlock_irqrestore(&priv->lock, flags);
		pm_runसमय_put(dai->dev);
		dev_err(&i2s->pdev->dev,
				"%s:%d Other DAI busy\n", __func__, __LINE__);
		वापस -EAGAIN;
	पूर्ण

	mod &= ~(sdf_mask | lrp_rlow | mod_slave);
	mod |= पंचांगp;
	ग_लिखोl(mod, priv->addr + I2SMOD);
	priv->slave_mode = (mod & mod_slave);
	spin_unlock_irqrestore(&priv->lock, flags);
	pm_runसमय_put(dai->dev);

	वापस 0;
पूर्ण

अटल पूर्णांक i2s_hw_params(काष्ठा snd_pcm_substream *substream,
	काष्ठा snd_pcm_hw_params *params, काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा samsung_i2s_priv *priv = snd_soc_dai_get_drvdata(dai);
	काष्ठा i2s_dai *i2s = to_info(dai);
	u32 mod, mask = 0, val = 0;
	काष्ठा clk *rclksrc;
	अचिन्हित दीर्घ flags;

	WARN_ON(!pm_runसमय_active(dai->dev));

	अगर (!is_secondary(i2s))
		mask |= (MOD_DC2_EN | MOD_DC1_EN);

	चयन (params_channels(params)) अणु
	हाल 6:
		val |= MOD_DC2_EN;
		fallthrough;
	हाल 4:
		val |= MOD_DC1_EN;
		अवरोध;
	हाल 2:
		अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
			i2s->dma_playback.addr_width = 4;
		अन्यथा
			i2s->dma_capture.addr_width = 4;
		अवरोध;
	हाल 1:
		अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
			i2s->dma_playback.addr_width = 2;
		अन्यथा
			i2s->dma_capture.addr_width = 2;

		अवरोध;
	शेष:
		dev_err(&i2s->pdev->dev, "%d channels not supported\n",
				params_channels(params));
		वापस -EINVAL;
	पूर्ण

	अगर (is_secondary(i2s))
		mask |= MOD_BLCS_MASK;
	अन्यथा
		mask |= MOD_BLCP_MASK;

	अगर (is_manager(i2s))
		mask |= MOD_BLC_MASK;

	चयन (params_width(params)) अणु
	हाल 8:
		अगर (is_secondary(i2s))
			val |= MOD_BLCS_8BIT;
		अन्यथा
			val |= MOD_BLCP_8BIT;
		अगर (is_manager(i2s))
			val |= MOD_BLC_8BIT;
		अवरोध;
	हाल 16:
		अगर (is_secondary(i2s))
			val |= MOD_BLCS_16BIT;
		अन्यथा
			val |= MOD_BLCP_16BIT;
		अगर (is_manager(i2s))
			val |= MOD_BLC_16BIT;
		अवरोध;
	हाल 24:
		अगर (is_secondary(i2s))
			val |= MOD_BLCS_24BIT;
		अन्यथा
			val |= MOD_BLCP_24BIT;
		अगर (is_manager(i2s))
			val |= MOD_BLC_24BIT;
		अवरोध;
	शेष:
		dev_err(&i2s->pdev->dev, "Format(%d) not supported\n",
				params_क्रमmat(params));
		वापस -EINVAL;
	पूर्ण

	spin_lock_irqsave(&priv->lock, flags);
	mod = पढ़ोl(priv->addr + I2SMOD);
	mod = (mod & ~mask) | val;
	ग_लिखोl(mod, priv->addr + I2SMOD);
	spin_unlock_irqrestore(&priv->lock, flags);

	snd_soc_dai_init_dma_data(dai, &i2s->dma_playback, &i2s->dma_capture);

	i2s->frmclk = params_rate(params);

	rclksrc = priv->clk_table[CLK_I2S_RCLK_SRC];
	अगर (rclksrc && !IS_ERR(rclksrc))
		priv->rclk_srcrate = clk_get_rate(rclksrc);

	वापस 0;
पूर्ण

/* We set स्थिरraपूर्णांकs on the substream according to the version of I2S */
अटल पूर्णांक i2s_startup(काष्ठा snd_pcm_substream *substream,
	  काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा samsung_i2s_priv *priv = snd_soc_dai_get_drvdata(dai);
	काष्ठा i2s_dai *i2s = to_info(dai);
	काष्ठा i2s_dai *other = get_other_dai(i2s);
	अचिन्हित दीर्घ flags;

	pm_runसमय_get_sync(dai->dev);

	spin_lock_irqsave(&priv->pcm_lock, flags);

	i2s->mode |= DAI_OPENED;

	अगर (is_manager(other))
		i2s->mode &= ~DAI_MANAGER;
	अन्यथा
		i2s->mode |= DAI_MANAGER;

	अगर (!any_active(i2s) && (priv->quirks & QUIRK_NEED_RSTCLR))
		ग_लिखोl(CON_RSTCLR, i2s->priv->addr + I2SCON);

	spin_unlock_irqrestore(&priv->pcm_lock, flags);

	वापस 0;
पूर्ण

अटल व्योम i2s_shutकरोwn(काष्ठा snd_pcm_substream *substream,
	काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा samsung_i2s_priv *priv = snd_soc_dai_get_drvdata(dai);
	काष्ठा i2s_dai *i2s = to_info(dai);
	काष्ठा i2s_dai *other = get_other_dai(i2s);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&priv->pcm_lock, flags);

	i2s->mode &= ~DAI_OPENED;
	i2s->mode &= ~DAI_MANAGER;

	अगर (is_खोलोed(other))
		other->mode |= DAI_MANAGER;

	/* Reset any स्थिरraपूर्णांक on RFS and BFS */
	i2s->rfs = 0;
	i2s->bfs = 0;

	spin_unlock_irqrestore(&priv->pcm_lock, flags);

	pm_runसमय_put(dai->dev);
पूर्ण

अटल पूर्णांक config_setup(काष्ठा i2s_dai *i2s)
अणु
	काष्ठा samsung_i2s_priv *priv = i2s->priv;
	काष्ठा i2s_dai *other = get_other_dai(i2s);
	अचिन्हित rfs, bfs, blc;
	u32 psr;

	blc = get_blc(i2s);

	bfs = i2s->bfs;

	अगर (!bfs && other)
		bfs = other->bfs;

	/* Select least possible multiple(2) अगर no स्थिरraपूर्णांक set */
	अगर (!bfs)
		bfs = blc * 2;

	rfs = i2s->rfs;

	अगर (!rfs && other)
		rfs = other->rfs;

	अगर ((rfs == 256 || rfs == 512) && (blc == 24)) अणु
		dev_err(&i2s->pdev->dev,
			"%d-RFS not supported for 24-blc\n", rfs);
		वापस -EINVAL;
	पूर्ण

	अगर (!rfs) अणु
		अगर (bfs == 16 || bfs == 32)
			rfs = 256;
		अन्यथा
			rfs = 384;
	पूर्ण

	/* If alपढ़ोy setup and running */
	अगर (any_active(i2s) && (get_rfs(i2s) != rfs || get_bfs(i2s) != bfs)) अणु
		dev_err(&i2s->pdev->dev,
				"%s:%d Other DAI busy\n", __func__, __LINE__);
		वापस -EAGAIN;
	पूर्ण

	set_bfs(i2s, bfs);
	set_rfs(i2s, rfs);

	/* Don't bother with PSR in Slave mode */
	अगर (priv->slave_mode)
		वापस 0;

	अगर (!(priv->quirks & QUIRK_NO_MUXPSR)) अणु
		psr = priv->rclk_srcrate / i2s->frmclk / rfs;
		ग_लिखोl(((psr - 1) << 8) | PSR_PSREN, priv->addr + I2SPSR);
		dev_dbg(&i2s->pdev->dev,
			"RCLK_SRC=%luHz PSR=%u, RCLK=%dfs, BCLK=%dfs\n",
				priv->rclk_srcrate, psr, rfs, bfs);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक i2s_trigger(काष्ठा snd_pcm_substream *substream,
	पूर्णांक cmd, काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा samsung_i2s_priv *priv = snd_soc_dai_get_drvdata(dai);
	पूर्णांक capture = (substream->stream == SNDRV_PCM_STREAM_CAPTURE);
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा i2s_dai *i2s = to_info(asoc_rtd_to_cpu(rtd, 0));
	अचिन्हित दीर्घ flags;

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_RESUME:
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		pm_runसमय_get_sync(dai->dev);
		spin_lock_irqsave(&priv->lock, flags);

		अगर (config_setup(i2s)) अणु
			spin_unlock_irqrestore(&priv->lock, flags);
			वापस -EINVAL;
		पूर्ण

		अगर (capture)
			i2s_rxctrl(i2s, 1);
		अन्यथा
			i2s_txctrl(i2s, 1);

		spin_unlock_irqrestore(&priv->lock, flags);
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		spin_lock_irqsave(&priv->lock, flags);

		अगर (capture) अणु
			i2s_rxctrl(i2s, 0);
			i2s_fअगरo(i2s, FIC_RXFLUSH);
		पूर्ण अन्यथा अणु
			i2s_txctrl(i2s, 0);
			i2s_fअगरo(i2s, FIC_TXFLUSH);
		पूर्ण

		spin_unlock_irqrestore(&priv->lock, flags);
		pm_runसमय_put(dai->dev);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक i2s_set_clkभाग(काष्ठा snd_soc_dai *dai,
	पूर्णांक भाग_id, पूर्णांक भाग)
अणु
	काष्ठा i2s_dai *i2s = to_info(dai);
	काष्ठा i2s_dai *other = get_other_dai(i2s);

	चयन (भाग_id) अणु
	हाल SAMSUNG_I2S_DIV_BCLK:
		pm_runसमय_get_sync(dai->dev);
		अगर ((any_active(i2s) && भाग && (get_bfs(i2s) != भाग))
			|| (other && other->bfs && (other->bfs != भाग))) अणु
			pm_runसमय_put(dai->dev);
			dev_err(&i2s->pdev->dev,
				"%s:%d Other DAI busy\n", __func__, __LINE__);
			वापस -EAGAIN;
		पूर्ण
		i2s->bfs = भाग;
		pm_runसमय_put(dai->dev);
		अवरोध;
	शेष:
		dev_err(&i2s->pdev->dev,
			"Invalid clock divider(%d)\n", भाग_id);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल snd_pcm_sframes_t
i2s_delay(काष्ठा snd_pcm_substream *substream, काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा samsung_i2s_priv *priv = snd_soc_dai_get_drvdata(dai);
	काष्ठा i2s_dai *i2s = to_info(dai);
	u32 reg = पढ़ोl(priv->addr + I2SFIC);
	snd_pcm_sframes_t delay;

	WARN_ON(!pm_runसमय_active(dai->dev));

	अगर (substream->stream == SNDRV_PCM_STREAM_CAPTURE)
		delay = FIC_RXCOUNT(reg);
	अन्यथा अगर (is_secondary(i2s))
		delay = FICS_TXCOUNT(पढ़ोl(priv->addr + I2SFICS));
	अन्यथा
		delay = (reg >> priv->variant_regs->ftx0cnt_off) & 0x7f;

	वापस delay;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक i2s_suspend(काष्ठा snd_soc_component *component)
अणु
	वापस pm_runसमय_क्रमce_suspend(component->dev);
पूर्ण

अटल पूर्णांक i2s_resume(काष्ठा snd_soc_component *component)
अणु
	वापस pm_runसमय_क्रमce_resume(component->dev);
पूर्ण
#अन्यथा
#घोषणा i2s_suspend शून्य
#घोषणा i2s_resume  शून्य
#पूर्ण_अगर

अटल पूर्णांक samsung_i2s_dai_probe(काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा samsung_i2s_priv *priv = snd_soc_dai_get_drvdata(dai);
	काष्ठा i2s_dai *i2s = to_info(dai);
	काष्ठा i2s_dai *other = get_other_dai(i2s);
	अचिन्हित दीर्घ flags;

	pm_runसमय_get_sync(dai->dev);

	अगर (is_secondary(i2s)) अणु
		/* If this is probe on the secondary DAI */
		snd_soc_dai_init_dma_data(dai, &i2s->dma_playback, शून्य);
	पूर्ण अन्यथा अणु
		snd_soc_dai_init_dma_data(dai, &i2s->dma_playback,
					  &i2s->dma_capture);

		अगर (priv->quirks & QUIRK_NEED_RSTCLR)
			ग_लिखोl(CON_RSTCLR, priv->addr + I2SCON);

		अगर (priv->quirks & QUIRK_SUPPORTS_IDMA)
			idma_reg_addr_init(priv->addr,
					   other->idma_playback.addr);
	पूर्ण

	/* Reset any स्थिरraपूर्णांक on RFS and BFS */
	i2s->rfs = 0;
	i2s->bfs = 0;

	spin_lock_irqsave(&priv->lock, flags);
	i2s_txctrl(i2s, 0);
	i2s_rxctrl(i2s, 0);
	i2s_fअगरo(i2s, FIC_TXFLUSH);
	i2s_fअगरo(other, FIC_TXFLUSH);
	i2s_fअगरo(i2s, FIC_RXFLUSH);
	spin_unlock_irqrestore(&priv->lock, flags);

	/* Gate CDCLK by शेष */
	अगर (!is_खोलोed(other))
		i2s_set_sysclk(dai, SAMSUNG_I2S_CDCLK,
				0, SND_SOC_CLOCK_IN);
	pm_runसमय_put(dai->dev);

	वापस 0;
पूर्ण

अटल पूर्णांक samsung_i2s_dai_हटाओ(काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा samsung_i2s_priv *priv = snd_soc_dai_get_drvdata(dai);
	काष्ठा i2s_dai *i2s = to_info(dai);
	अचिन्हित दीर्घ flags;

	pm_runसमय_get_sync(dai->dev);

	अगर (!is_secondary(i2s)) अणु
		अगर (priv->quirks & QUIRK_NEED_RSTCLR) अणु
			spin_lock_irqsave(&priv->lock, flags);
			ग_लिखोl(0, priv->addr + I2SCON);
			spin_unlock_irqrestore(&priv->lock, flags);
		पूर्ण
	पूर्ण

	pm_runसमय_put(dai->dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops samsung_i2s_dai_ops = अणु
	.trigger = i2s_trigger,
	.hw_params = i2s_hw_params,
	.set_fmt = i2s_set_fmt,
	.set_clkभाग = i2s_set_clkभाग,
	.set_sysclk = i2s_set_sysclk,
	.startup = i2s_startup,
	.shutकरोwn = i2s_shutकरोwn,
	.delay = i2s_delay,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget samsung_i2s_widमाला_लो[] = अणु
	/* Backend DAI  */
	SND_SOC_DAPM_AIF_OUT("Mixer DAI TX", शून्य, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("Mixer DAI RX", शून्य, 0, SND_SOC_NOPM, 0, 0),

	/* Playback Mixer */
	SND_SOC_DAPM_MIXER("Playback Mixer", SND_SOC_NOPM, 0, 0, शून्य, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route samsung_i2s_dapm_routes[] = अणु
	अणु "Playback Mixer", शून्य, "Primary Playback" पूर्ण,
	अणु "Playback Mixer", शून्य, "Secondary Playback" पूर्ण,

	अणु "Mixer DAI TX", शून्य, "Playback Mixer" पूर्ण,
	अणु "Primary Capture", शून्य, "Mixer DAI RX" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver samsung_i2s_component = अणु
	.name = "samsung-i2s",

	.dapm_widमाला_लो = samsung_i2s_widमाला_लो,
	.num_dapm_widमाला_लो = ARRAY_SIZE(samsung_i2s_widमाला_लो),

	.dapm_routes = samsung_i2s_dapm_routes,
	.num_dapm_routes = ARRAY_SIZE(samsung_i2s_dapm_routes),

	.suspend = i2s_suspend,
	.resume = i2s_resume,
पूर्ण;

#घोषणा SAMSUNG_I2S_FMTS (SNDRV_PCM_FMTBIT_S8 | SNDRV_PCM_FMTBIT_S16_LE | \
			  SNDRV_PCM_FMTBIT_S24_LE)

अटल पूर्णांक i2s_alloc_dais(काष्ठा samsung_i2s_priv *priv,
			  स्थिर काष्ठा samsung_i2s_dai_data *i2s_dai_data,
			  पूर्णांक num_dais)
अणु
	अटल स्थिर अक्षर *dai_names[] = अणु "samsung-i2s", "samsung-i2s-sec" पूर्ण;
	अटल स्थिर अक्षर *stream_names[] = अणु "Primary Playback",
					      "Secondary Playback" पूर्ण;
	काष्ठा snd_soc_dai_driver *dai_drv;
	पूर्णांक i;

	priv->dai = devm_kसुस्मृति(&priv->pdev->dev, num_dais,
				     माप(काष्ठा i2s_dai), GFP_KERNEL);
	अगर (!priv->dai)
		वापस -ENOMEM;

	priv->dai_drv = devm_kसुस्मृति(&priv->pdev->dev, num_dais,
				     माप(*dai_drv), GFP_KERNEL);
	अगर (!priv->dai_drv)
		वापस -ENOMEM;

	क्रम (i = 0; i < num_dais; i++) अणु
		dai_drv = &priv->dai_drv[i];

		dai_drv->probe = samsung_i2s_dai_probe;
		dai_drv->हटाओ = samsung_i2s_dai_हटाओ;

		dai_drv->symmetric_rate = 1;
		dai_drv->ops = &samsung_i2s_dai_ops;

		dai_drv->playback.channels_min = 1;
		dai_drv->playback.channels_max = 2;
		dai_drv->playback.rates = i2s_dai_data->pcm_rates;
		dai_drv->playback.क्रमmats = SAMSUNG_I2S_FMTS;
		dai_drv->playback.stream_name = stream_names[i];

		dai_drv->id = i + 1;
		dai_drv->name = dai_names[i];

		priv->dai[i].drv = &priv->dai_drv[i];
		priv->dai[i].pdev = priv->pdev;
	पूर्ण

	/* Initialize capture only क्रम the primary DAI */
	dai_drv = &priv->dai_drv[SAMSUNG_I2S_ID_PRIMARY - 1];

	dai_drv->capture.channels_min = 1;
	dai_drv->capture.channels_max = 2;
	dai_drv->capture.rates = i2s_dai_data->pcm_rates;
	dai_drv->capture.क्रमmats = SAMSUNG_I2S_FMTS;
	dai_drv->capture.stream_name = "Primary Capture";

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक i2s_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा samsung_i2s_priv *priv = dev_get_drvdata(dev);

	priv->suspend_i2smod = पढ़ोl(priv->addr + I2SMOD);
	priv->suspend_i2scon = पढ़ोl(priv->addr + I2SCON);
	priv->suspend_i2spsr = पढ़ोl(priv->addr + I2SPSR);

	clk_disable_unprepare(priv->op_clk);
	clk_disable_unprepare(priv->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक i2s_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा samsung_i2s_priv *priv = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = clk_prepare_enable(priv->clk);
	अगर (ret)
		वापस ret;

	अगर (priv->op_clk) अणु
		ret = clk_prepare_enable(priv->op_clk);
		अगर (ret) अणु
			clk_disable_unprepare(priv->clk);
			वापस ret;
		पूर्ण
	पूर्ण

	ग_लिखोl(priv->suspend_i2scon, priv->addr + I2SCON);
	ग_लिखोl(priv->suspend_i2smod, priv->addr + I2SMOD);
	ग_लिखोl(priv->suspend_i2spsr, priv->addr + I2SPSR);

	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_PM */

अटल व्योम i2s_unरेजिस्टर_घड़ीs(काष्ठा samsung_i2s_priv *priv)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < priv->clk_data.clk_num; i++) अणु
		अगर (!IS_ERR(priv->clk_table[i]))
			clk_unरेजिस्टर(priv->clk_table[i]);
	पूर्ण
पूर्ण

अटल व्योम i2s_unरेजिस्टर_घड़ी_provider(काष्ठा samsung_i2s_priv *priv)
अणु
	of_clk_del_provider(priv->pdev->dev.of_node);
	i2s_unरेजिस्टर_घड़ीs(priv);
पूर्ण


अटल पूर्णांक i2s_रेजिस्टर_घड़ी_provider(काष्ठा samsung_i2s_priv *priv)
अणु

	स्थिर अक्षर * स्थिर i2s_clk_desc[] = अणु "cdclk", "rclk_src", "prescaler" पूर्ण;
	स्थिर अक्षर *clk_name[2] = अणु "i2s_opclk0", "i2s_opclk1" पूर्ण;
	स्थिर अक्षर *p_names[2] = अणु शून्य पूर्ण;
	काष्ठा device *dev = &priv->pdev->dev;
	स्थिर काष्ठा samsung_i2s_variant_regs *reg_info = priv->variant_regs;
	स्थिर अक्षर *i2s_clk_name[ARRAY_SIZE(i2s_clk_desc)];
	काष्ठा clk *rclksrc;
	पूर्णांक ret, i;

	/* Register the घड़ी provider only अगर it's expected in the DTB */
	अगर (!of_find_property(dev->of_node, "#clock-cells", शून्य))
		वापस 0;

	/* Get the RCLKSRC mux घड़ी parent घड़ी names */
	क्रम (i = 0; i < ARRAY_SIZE(p_names); i++) अणु
		rclksrc = clk_get(dev, clk_name[i]);
		अगर (IS_ERR(rclksrc))
			जारी;
		p_names[i] = __clk_get_name(rclksrc);
		clk_put(rclksrc);
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(i2s_clk_desc); i++) अणु
		i2s_clk_name[i] = devm_kaप्र_लिखो(dev, GFP_KERNEL, "%s_%s",
						dev_name(dev), i2s_clk_desc[i]);
		अगर (!i2s_clk_name[i])
			वापस -ENOMEM;
	पूर्ण

	अगर (!(priv->quirks & QUIRK_NO_MUXPSR)) अणु
		/* Activate the prescaler */
		u32 val = पढ़ोl(priv->addr + I2SPSR);
		ग_लिखोl(val | PSR_PSREN, priv->addr + I2SPSR);

		priv->clk_table[CLK_I2S_RCLK_SRC] = clk_रेजिस्टर_mux(dev,
				i2s_clk_name[CLK_I2S_RCLK_SRC], p_names,
				ARRAY_SIZE(p_names),
				CLK_SET_RATE_NO_REPARENT | CLK_SET_RATE_PARENT,
				priv->addr + I2SMOD, reg_info->rclksrc_off,
				1, 0, &priv->lock);

		priv->clk_table[CLK_I2S_RCLK_PSR] = clk_रेजिस्टर_भागider(dev,
				i2s_clk_name[CLK_I2S_RCLK_PSR],
				i2s_clk_name[CLK_I2S_RCLK_SRC],
				CLK_SET_RATE_PARENT,
				priv->addr + I2SPSR, 8, 6, 0, &priv->lock);

		p_names[0] = i2s_clk_name[CLK_I2S_RCLK_PSR];
		priv->clk_data.clk_num = 2;
	पूर्ण

	priv->clk_table[CLK_I2S_CDCLK] = clk_रेजिस्टर_gate(dev,
				i2s_clk_name[CLK_I2S_CDCLK], p_names[0],
				CLK_SET_RATE_PARENT,
				priv->addr + I2SMOD, reg_info->cdclkcon_off,
				CLK_GATE_SET_TO_DISABLE, &priv->lock);

	priv->clk_data.clk_num += 1;
	priv->clk_data.clks = priv->clk_table;

	ret = of_clk_add_provider(dev->of_node, of_clk_src_onecell_get,
				  &priv->clk_data);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to add clock provider: %d\n", ret);
		i2s_unरेजिस्टर_घड़ीs(priv);
	पूर्ण

	वापस ret;
पूर्ण

/* Create platक्रमm device क्रम the secondary PCM */
अटल पूर्णांक i2s_create_secondary_device(काष्ठा samsung_i2s_priv *priv)
अणु
	काष्ठा platक्रमm_device *pdev_sec;
	स्थिर अक्षर *devname;
	पूर्णांक ret;

	devname = devm_kaप्र_लिखो(&priv->pdev->dev, GFP_KERNEL, "%s-sec",
				 dev_name(&priv->pdev->dev));
	अगर (!devname)
		वापस -ENOMEM;

	pdev_sec = platक्रमm_device_alloc(devname, -1);
	अगर (!pdev_sec)
		वापस -ENOMEM;

	pdev_sec->driver_override = kstrdup("samsung-i2s", GFP_KERNEL);

	ret = platक्रमm_device_add(pdev_sec);
	अगर (ret < 0) अणु
		platक्रमm_device_put(pdev_sec);
		वापस ret;
	पूर्ण

	ret = device_attach(&pdev_sec->dev);
	अगर (ret <= 0) अणु
		platक्रमm_device_unरेजिस्टर(priv->pdev_sec);
		dev_info(&pdev_sec->dev, "device_attach() failed\n");
		वापस ret;
	पूर्ण

	priv->pdev_sec = pdev_sec;

	वापस 0;
पूर्ण

अटल व्योम i2s_delete_secondary_device(काष्ठा samsung_i2s_priv *priv)
अणु
	platक्रमm_device_unरेजिस्टर(priv->pdev_sec);
	priv->pdev_sec = शून्य;
पूर्ण

अटल पूर्णांक samsung_i2s_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा i2s_dai *pri_dai, *sec_dai = शून्य;
	काष्ठा s3c_audio_pdata *i2s_pdata = pdev->dev.platक्रमm_data;
	u32 regs_base, idma_addr = 0;
	काष्ठा device_node *np = pdev->dev.of_node;
	स्थिर काष्ठा samsung_i2s_dai_data *i2s_dai_data;
	स्थिर काष्ठा platक्रमm_device_id *id;
	काष्ठा samsung_i2s_priv *priv;
	काष्ठा resource *res;
	पूर्णांक num_dais, ret;

	अगर (IS_ENABLED(CONFIG_OF) && pdev->dev.of_node) अणु
		i2s_dai_data = of_device_get_match_data(&pdev->dev);
	पूर्ण अन्यथा अणु
		id = platक्रमm_get_device_id(pdev);

		/* Nothing to करो अगर it is the secondary device probe */
		अगर (!id)
			वापस 0;

		i2s_dai_data = (काष्ठा samsung_i2s_dai_data *)id->driver_data;
	पूर्ण

	priv = devm_kzalloc(&pdev->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	अगर (np) अणु
		priv->quirks = i2s_dai_data->quirks;
	पूर्ण अन्यथा अणु
		अगर (!i2s_pdata) अणु
			dev_err(&pdev->dev, "Missing platform data\n");
			वापस -EINVAL;
		पूर्ण
		priv->quirks = i2s_pdata->type.quirks;
	पूर्ण

	num_dais = (priv->quirks & QUIRK_SEC_DAI) ? 2 : 1;
	priv->pdev = pdev;
	priv->variant_regs = i2s_dai_data->i2s_variant_regs;

	ret = i2s_alloc_dais(priv, i2s_dai_data, num_dais);
	अगर (ret < 0)
		वापस ret;

	pri_dai = &priv->dai[SAMSUNG_I2S_ID_PRIMARY - 1];

	spin_lock_init(&priv->lock);
	spin_lock_init(&priv->pcm_lock);

	अगर (!np) अणु
		pri_dai->dma_playback.filter_data = i2s_pdata->dma_playback;
		pri_dai->dma_capture.filter_data = i2s_pdata->dma_capture;
		pri_dai->filter = i2s_pdata->dma_filter;

		idma_addr = i2s_pdata->type.idma_addr;
	पूर्ण अन्यथा अणु
		अगर (of_property_पढ़ो_u32(np, "samsung,idma-addr",
					 &idma_addr)) अणु
			अगर (priv->quirks & QUIRK_SUPPORTS_IDMA) अणु
				dev_info(&pdev->dev, "idma address is not"\
						"specified");
			पूर्ण
		पूर्ण
	पूर्ण

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	priv->addr = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(priv->addr))
		वापस PTR_ERR(priv->addr);

	regs_base = res->start;

	priv->clk = devm_clk_get(&pdev->dev, "iis");
	अगर (IS_ERR(priv->clk)) अणु
		dev_err(&pdev->dev, "Failed to get iis clock\n");
		वापस PTR_ERR(priv->clk);
	पूर्ण

	ret = clk_prepare_enable(priv->clk);
	अगर (ret != 0) अणु
		dev_err(&pdev->dev, "failed to enable clock: %d\n", ret);
		वापस ret;
	पूर्ण
	pri_dai->dma_playback.addr = regs_base + I2STXD;
	pri_dai->dma_capture.addr = regs_base + I2SRXD;
	pri_dai->dma_playback.chan_name = "tx";
	pri_dai->dma_capture.chan_name = "rx";
	pri_dai->dma_playback.addr_width = 4;
	pri_dai->dma_capture.addr_width = 4;
	pri_dai->priv = priv;

	अगर (priv->quirks & QUIRK_PRI_6CHAN)
		pri_dai->drv->playback.channels_max = 6;

	ret = samsung_asoc_dma_platक्रमm_रेजिस्टर(&pdev->dev, pri_dai->filter,
						 "tx", "rx", शून्य);
	अगर (ret < 0)
		जाओ err_disable_clk;

	अगर (priv->quirks & QUIRK_SEC_DAI) अणु
		sec_dai = &priv->dai[SAMSUNG_I2S_ID_SECONDARY - 1];

		sec_dai->dma_playback.addr = regs_base + I2STXDS;
		sec_dai->dma_playback.chan_name = "tx-sec";

		अगर (!np) अणु
			sec_dai->dma_playback.filter_data = i2s_pdata->dma_play_sec;
			sec_dai->filter = i2s_pdata->dma_filter;
		पूर्ण

		sec_dai->dma_playback.addr_width = 4;
		sec_dai->idma_playback.addr = idma_addr;
		sec_dai->pri_dai = pri_dai;
		sec_dai->priv = priv;
		pri_dai->sec_dai = sec_dai;

		ret = i2s_create_secondary_device(priv);
		अगर (ret < 0)
			जाओ err_disable_clk;

		ret = samsung_asoc_dma_platक्रमm_रेजिस्टर(&priv->pdev_sec->dev,
						sec_dai->filter, "tx-sec", शून्य,
						&pdev->dev);
		अगर (ret < 0)
			जाओ err_del_sec;

	पूर्ण

	अगर (i2s_pdata && i2s_pdata->cfg_gpio && i2s_pdata->cfg_gpio(pdev)) अणु
		dev_err(&pdev->dev, "Unable to configure gpio\n");
		ret = -EINVAL;
		जाओ err_del_sec;
	पूर्ण

	dev_set_drvdata(&pdev->dev, priv);

	ret = devm_snd_soc_रेजिस्टर_component(&pdev->dev,
					&samsung_i2s_component,
					priv->dai_drv, num_dais);
	अगर (ret < 0)
		जाओ err_del_sec;

	pm_runसमय_set_active(&pdev->dev);
	pm_runसमय_enable(&pdev->dev);

	ret = i2s_रेजिस्टर_घड़ी_provider(priv);
	अगर (ret < 0)
		जाओ err_disable_pm;

	priv->op_clk = clk_get_parent(priv->clk_table[CLK_I2S_RCLK_SRC]);

	वापस 0;

err_disable_pm:
	pm_runसमय_disable(&pdev->dev);
err_del_sec:
	i2s_delete_secondary_device(priv);
err_disable_clk:
	clk_disable_unprepare(priv->clk);
	वापस ret;
पूर्ण

अटल पूर्णांक samsung_i2s_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा samsung_i2s_priv *priv = dev_get_drvdata(&pdev->dev);

	/* The secondary device has no driver data asचिन्हित */
	अगर (!priv)
		वापस 0;

	pm_runसमय_get_sync(&pdev->dev);
	pm_runसमय_disable(&pdev->dev);

	i2s_unरेजिस्टर_घड़ी_provider(priv);
	i2s_delete_secondary_device(priv);
	clk_disable_unprepare(priv->clk);

	pm_runसमय_put_noidle(&pdev->dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा samsung_i2s_variant_regs i2sv3_regs = अणु
	.bfs_off = 1,
	.rfs_off = 3,
	.sdf_off = 5,
	.txr_off = 8,
	.rclksrc_off = 10,
	.mss_off = 11,
	.cdclkcon_off = 12,
	.lrp_off = 7,
	.bfs_mask = 0x3,
	.rfs_mask = 0x3,
	.ftx0cnt_off = 8,
पूर्ण;

अटल स्थिर काष्ठा samsung_i2s_variant_regs i2sv6_regs = अणु
	.bfs_off = 0,
	.rfs_off = 4,
	.sdf_off = 6,
	.txr_off = 8,
	.rclksrc_off = 10,
	.mss_off = 11,
	.cdclkcon_off = 12,
	.lrp_off = 15,
	.bfs_mask = 0xf,
	.rfs_mask = 0x3,
	.ftx0cnt_off = 8,
पूर्ण;

अटल स्थिर काष्ठा samsung_i2s_variant_regs i2sv7_regs = अणु
	.bfs_off = 0,
	.rfs_off = 4,
	.sdf_off = 7,
	.txr_off = 9,
	.rclksrc_off = 11,
	.mss_off = 12,
	.cdclkcon_off = 22,
	.lrp_off = 15,
	.bfs_mask = 0xf,
	.rfs_mask = 0x7,
	.ftx0cnt_off = 0,
पूर्ण;

अटल स्थिर काष्ठा samsung_i2s_variant_regs i2sv5_i2s1_regs = अणु
	.bfs_off = 0,
	.rfs_off = 3,
	.sdf_off = 6,
	.txr_off = 8,
	.rclksrc_off = 10,
	.mss_off = 11,
	.cdclkcon_off = 12,
	.lrp_off = 15,
	.bfs_mask = 0x7,
	.rfs_mask = 0x7,
	.ftx0cnt_off = 8,
पूर्ण;

अटल स्थिर काष्ठा samsung_i2s_dai_data i2sv3_dai_type = अणु
	.quirks = QUIRK_NO_MUXPSR,
	.pcm_rates = SNDRV_PCM_RATE_8000_96000,
	.i2s_variant_regs = &i2sv3_regs,
पूर्ण;

अटल स्थिर काष्ठा samsung_i2s_dai_data i2sv5_dai_type __maybe_unused = अणु
	.quirks = QUIRK_PRI_6CHAN | QUIRK_SEC_DAI | QUIRK_NEED_RSTCLR |
			QUIRK_SUPPORTS_IDMA,
	.pcm_rates = SNDRV_PCM_RATE_8000_96000,
	.i2s_variant_regs = &i2sv3_regs,
पूर्ण;

अटल स्थिर काष्ठा samsung_i2s_dai_data i2sv6_dai_type __maybe_unused = अणु
	.quirks = QUIRK_PRI_6CHAN | QUIRK_SEC_DAI | QUIRK_NEED_RSTCLR |
			QUIRK_SUPPORTS_TDM | QUIRK_SUPPORTS_IDMA,
	.pcm_rates = SNDRV_PCM_RATE_8000_96000,
	.i2s_variant_regs = &i2sv6_regs,
पूर्ण;

अटल स्थिर काष्ठा samsung_i2s_dai_data i2sv7_dai_type __maybe_unused = अणु
	.quirks = QUIRK_PRI_6CHAN | QUIRK_SEC_DAI | QUIRK_NEED_RSTCLR |
			QUIRK_SUPPORTS_TDM,
	.pcm_rates = SNDRV_PCM_RATE_8000_192000,
	.i2s_variant_regs = &i2sv7_regs,
पूर्ण;

अटल स्थिर काष्ठा samsung_i2s_dai_data i2sv5_dai_type_i2s1 __maybe_unused = अणु
	.quirks = QUIRK_PRI_6CHAN | QUIRK_NEED_RSTCLR,
	.pcm_rates = SNDRV_PCM_RATE_8000_96000,
	.i2s_variant_regs = &i2sv5_i2s1_regs,
पूर्ण;

अटल स्थिर काष्ठा platक्रमm_device_id samsung_i2s_driver_ids[] = अणु
	अणु
		.name           = "samsung-i2s",
		.driver_data	= (kernel_uदीर्घ_t)&i2sv3_dai_type,
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, samsung_i2s_driver_ids);

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id exynos_i2s_match[] = अणु
	अणु
		.compatible = "samsung,s3c6410-i2s",
		.data = &i2sv3_dai_type,
	पूर्ण, अणु
		.compatible = "samsung,s5pv210-i2s",
		.data = &i2sv5_dai_type,
	पूर्ण, अणु
		.compatible = "samsung,exynos5420-i2s",
		.data = &i2sv6_dai_type,
	पूर्ण, अणु
		.compatible = "samsung,exynos7-i2s",
		.data = &i2sv7_dai_type,
	पूर्ण, अणु
		.compatible = "samsung,exynos7-i2s1",
		.data = &i2sv5_dai_type_i2s1,
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, exynos_i2s_match);
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops samsung_i2s_pm = अणु
	SET_RUNTIME_PM_OPS(i2s_runसमय_suspend,
				i2s_runसमय_resume, शून्य)
	SET_SYSTEM_SLEEP_PM_OPS(pm_runसमय_क्रमce_suspend,
				     pm_runसमय_क्रमce_resume)
पूर्ण;

अटल काष्ठा platक्रमm_driver samsung_i2s_driver = अणु
	.probe  = samsung_i2s_probe,
	.हटाओ = samsung_i2s_हटाओ,
	.id_table = samsung_i2s_driver_ids,
	.driver = अणु
		.name = "samsung-i2s",
		.of_match_table = of_match_ptr(exynos_i2s_match),
		.pm = &samsung_i2s_pm,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(samsung_i2s_driver);

/* Module inक्रमmation */
MODULE_AUTHOR("Jaswinder Singh, <jassisinghbrar@gmail.com>");
MODULE_DESCRIPTION("Samsung I2S Interface");
MODULE_ALIAS("platform:samsung-i2s");
MODULE_LICENSE("GPL");
