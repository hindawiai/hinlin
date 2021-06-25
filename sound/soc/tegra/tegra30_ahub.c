<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * tegra30_ahub.c - Tegra30 AHUB driver
 *
 * Copyright (c) 2011,2012, NVIDIA CORPORATION.  All rights reserved.
 */

#समावेश <linux/clk.h>
#समावेश <linux/device.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regmap.h>
#समावेश <linux/reset.h>
#समावेश <linux/slab.h>
#समावेश <sound/soc.h>
#समावेश "tegra30_ahub.h"

#घोषणा DRV_NAME "tegra30-ahub"

अटल काष्ठा tegra30_ahub *ahub;

अटल अंतरभूत व्योम tegra30_apbअगर_ग_लिखो(u32 reg, u32 val)
अणु
	regmap_ग_लिखो(ahub->regmap_apbअगर, reg, val);
पूर्ण

अटल अंतरभूत u32 tegra30_apbअगर_पढ़ो(u32 reg)
अणु
	u32 val;

	regmap_पढ़ो(ahub->regmap_apbअगर, reg, &val);
	वापस val;
पूर्ण

अटल अंतरभूत व्योम tegra30_audio_ग_लिखो(u32 reg, u32 val)
अणु
	regmap_ग_लिखो(ahub->regmap_ahub, reg, val);
पूर्ण

अटल __maybe_unused पूर्णांक tegra30_ahub_runसमय_suspend(काष्ठा device *dev)
अणु
	regcache_cache_only(ahub->regmap_apbअगर, true);
	regcache_cache_only(ahub->regmap_ahub, true);

	clk_bulk_disable_unprepare(ahub->nघड़ीs, ahub->घड़ीs);

	वापस 0;
पूर्ण

/*
 * clk_apbअगर isn't required क्रम an I2S<->I2S configuration where no PCM data
 * is पढ़ो from or sent to memory. However, that's not something the rest of
 * the driver supports right now, so we'll just treat the two घड़ीs as one
 * क्रम now.
 *
 * These functions should not be a plain ref-count. Instead, each active stream
 * contributes some requirement to the minimum घड़ी rate, so starting or
 * stopping streams should dynamically adjust the घड़ी as required.  However,
 * this is not yet implemented.
 */
अटल __maybe_unused पूर्णांक tegra30_ahub_runसमय_resume(काष्ठा device *dev)
अणु
	पूर्णांक ret;

	ret = reset_control_bulk_निश्चित(ahub->nresets, ahub->resets);
	अगर (ret)
		वापस ret;

	ret = clk_bulk_prepare_enable(ahub->nघड़ीs, ahub->घड़ीs);
	अगर (ret)
		वापस ret;

	usleep_range(10, 100);

	ret = reset_control_bulk_deनिश्चित(ahub->nresets, ahub->resets);
	अगर (ret)
		जाओ disable_घड़ीs;

	regcache_cache_only(ahub->regmap_apbअगर, false);
	regcache_cache_only(ahub->regmap_ahub, false);
	regcache_mark_dirty(ahub->regmap_apbअगर);
	regcache_mark_dirty(ahub->regmap_ahub);

	ret = regcache_sync(ahub->regmap_apbअगर);
	अगर (ret)
		जाओ disable_घड़ीs;

	ret = regcache_sync(ahub->regmap_ahub);
	अगर (ret)
		जाओ disable_घड़ीs;

	वापस 0;

disable_घड़ीs:
	clk_bulk_disable_unprepare(ahub->nघड़ीs, ahub->घड़ीs);

	वापस ret;
पूर्ण

पूर्णांक tegra30_ahub_allocate_rx_fअगरo(क्रमागत tegra30_ahub_rxcअगर *rxcअगर,
				  अक्षर *dmachan, पूर्णांक dmachan_len,
				  dma_addr_t *fअगरoreg)
अणु
	पूर्णांक channel;
	u32 reg, val;
	काष्ठा tegra30_ahub_cअगर_conf cअगर_conf;

	channel = find_first_zero_bit(ahub->rx_usage,
				      TEGRA30_AHUB_CHANNEL_CTRL_COUNT);
	अगर (channel >= TEGRA30_AHUB_CHANNEL_CTRL_COUNT)
		वापस -EBUSY;

	__set_bit(channel, ahub->rx_usage);

	*rxcअगर = TEGRA30_AHUB_RXCIF_APBIF_RX0 + channel;
	snम_लिखो(dmachan, dmachan_len, "rx%d", channel);
	*fअगरoreg = ahub->apbअगर_addr + TEGRA30_AHUB_CHANNEL_RXFIFO +
		   (channel * TEGRA30_AHUB_CHANNEL_RXFIFO_STRIDE);

	pm_runसमय_get_sync(ahub->dev);

	reg = TEGRA30_AHUB_CHANNEL_CTRL +
	      (channel * TEGRA30_AHUB_CHANNEL_CTRL_STRIDE);
	val = tegra30_apbअगर_पढ़ो(reg);
	val &= ~(TEGRA30_AHUB_CHANNEL_CTRL_RX_THRESHOLD_MASK |
		 TEGRA30_AHUB_CHANNEL_CTRL_RX_PACK_MASK);
	val |= (7 << TEGRA30_AHUB_CHANNEL_CTRL_RX_THRESHOLD_SHIFT) |
	       TEGRA30_AHUB_CHANNEL_CTRL_RX_PACK_EN |
	       TEGRA30_AHUB_CHANNEL_CTRL_RX_PACK_16;
	tegra30_apbअगर_ग_लिखो(reg, val);

	cअगर_conf.threshold = 0;
	cअगर_conf.audio_channels = 2;
	cअगर_conf.client_channels = 2;
	cअगर_conf.audio_bits = TEGRA30_AUDIOCIF_BITS_16;
	cअगर_conf.client_bits = TEGRA30_AUDIOCIF_BITS_16;
	cअगर_conf.expand = 0;
	cअगर_conf.stereo_conv = 0;
	cअगर_conf.replicate = 0;
	cअगर_conf.direction = TEGRA30_AUDIOCIF_सूचीECTION_RX;
	cअगर_conf.truncate = 0;
	cअगर_conf.mono_conv = 0;

	reg = TEGRA30_AHUB_CIF_RX_CTRL +
	      (channel * TEGRA30_AHUB_CIF_RX_CTRL_STRIDE);
	ahub->soc_data->set_audio_cअगर(ahub->regmap_apbअगर, reg, &cअगर_conf);

	pm_runसमय_put(ahub->dev);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(tegra30_ahub_allocate_rx_fअगरo);

पूर्णांक tegra30_ahub_enable_rx_fअगरo(क्रमागत tegra30_ahub_rxcअगर rxcअगर)
अणु
	पूर्णांक channel = rxcअगर - TEGRA30_AHUB_RXCIF_APBIF_RX0;
	पूर्णांक reg, val;

	pm_runसमय_get_sync(ahub->dev);

	reg = TEGRA30_AHUB_CHANNEL_CTRL +
	      (channel * TEGRA30_AHUB_CHANNEL_CTRL_STRIDE);
	val = tegra30_apbअगर_पढ़ो(reg);
	val |= TEGRA30_AHUB_CHANNEL_CTRL_RX_EN;
	tegra30_apbअगर_ग_लिखो(reg, val);

	pm_runसमय_put(ahub->dev);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(tegra30_ahub_enable_rx_fअगरo);

पूर्णांक tegra30_ahub_disable_rx_fअगरo(क्रमागत tegra30_ahub_rxcअगर rxcअगर)
अणु
	पूर्णांक channel = rxcअगर - TEGRA30_AHUB_RXCIF_APBIF_RX0;
	पूर्णांक reg, val;

	pm_runसमय_get_sync(ahub->dev);

	reg = TEGRA30_AHUB_CHANNEL_CTRL +
	      (channel * TEGRA30_AHUB_CHANNEL_CTRL_STRIDE);
	val = tegra30_apbअगर_पढ़ो(reg);
	val &= ~TEGRA30_AHUB_CHANNEL_CTRL_RX_EN;
	tegra30_apbअगर_ग_लिखो(reg, val);

	pm_runसमय_put(ahub->dev);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(tegra30_ahub_disable_rx_fअगरo);

पूर्णांक tegra30_ahub_मुक्त_rx_fअगरo(क्रमागत tegra30_ahub_rxcअगर rxcअगर)
अणु
	पूर्णांक channel = rxcअगर - TEGRA30_AHUB_RXCIF_APBIF_RX0;

	__clear_bit(channel, ahub->rx_usage);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(tegra30_ahub_मुक्त_rx_fअगरo);

पूर्णांक tegra30_ahub_allocate_tx_fअगरo(क्रमागत tegra30_ahub_txcअगर *txcअगर,
				  अक्षर *dmachan, पूर्णांक dmachan_len,
				  dma_addr_t *fअगरoreg)
अणु
	पूर्णांक channel;
	u32 reg, val;
	काष्ठा tegra30_ahub_cअगर_conf cअगर_conf;

	channel = find_first_zero_bit(ahub->tx_usage,
				      TEGRA30_AHUB_CHANNEL_CTRL_COUNT);
	अगर (channel >= TEGRA30_AHUB_CHANNEL_CTRL_COUNT)
		वापस -EBUSY;

	__set_bit(channel, ahub->tx_usage);

	*txcअगर = TEGRA30_AHUB_TXCIF_APBIF_TX0 + channel;
	snम_लिखो(dmachan, dmachan_len, "tx%d", channel);
	*fअगरoreg = ahub->apbअगर_addr + TEGRA30_AHUB_CHANNEL_TXFIFO +
		   (channel * TEGRA30_AHUB_CHANNEL_TXFIFO_STRIDE);

	pm_runसमय_get_sync(ahub->dev);

	reg = TEGRA30_AHUB_CHANNEL_CTRL +
	      (channel * TEGRA30_AHUB_CHANNEL_CTRL_STRIDE);
	val = tegra30_apbअगर_पढ़ो(reg);
	val &= ~(TEGRA30_AHUB_CHANNEL_CTRL_TX_THRESHOLD_MASK |
		 TEGRA30_AHUB_CHANNEL_CTRL_TX_PACK_MASK);
	val |= (7 << TEGRA30_AHUB_CHANNEL_CTRL_TX_THRESHOLD_SHIFT) |
	       TEGRA30_AHUB_CHANNEL_CTRL_TX_PACK_EN |
	       TEGRA30_AHUB_CHANNEL_CTRL_TX_PACK_16;
	tegra30_apbअगर_ग_लिखो(reg, val);

	cअगर_conf.threshold = 0;
	cअगर_conf.audio_channels = 2;
	cअगर_conf.client_channels = 2;
	cअगर_conf.audio_bits = TEGRA30_AUDIOCIF_BITS_16;
	cअगर_conf.client_bits = TEGRA30_AUDIOCIF_BITS_16;
	cअगर_conf.expand = 0;
	cअगर_conf.stereo_conv = 0;
	cअगर_conf.replicate = 0;
	cअगर_conf.direction = TEGRA30_AUDIOCIF_सूचीECTION_TX;
	cअगर_conf.truncate = 0;
	cअगर_conf.mono_conv = 0;

	reg = TEGRA30_AHUB_CIF_TX_CTRL +
	      (channel * TEGRA30_AHUB_CIF_TX_CTRL_STRIDE);
	ahub->soc_data->set_audio_cअगर(ahub->regmap_apbअगर, reg, &cअगर_conf);

	pm_runसमय_put(ahub->dev);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(tegra30_ahub_allocate_tx_fअगरo);

पूर्णांक tegra30_ahub_enable_tx_fअगरo(क्रमागत tegra30_ahub_txcअगर txcअगर)
अणु
	पूर्णांक channel = txcअगर - TEGRA30_AHUB_TXCIF_APBIF_TX0;
	पूर्णांक reg, val;

	pm_runसमय_get_sync(ahub->dev);

	reg = TEGRA30_AHUB_CHANNEL_CTRL +
	      (channel * TEGRA30_AHUB_CHANNEL_CTRL_STRIDE);
	val = tegra30_apbअगर_पढ़ो(reg);
	val |= TEGRA30_AHUB_CHANNEL_CTRL_TX_EN;
	tegra30_apbअगर_ग_लिखो(reg, val);

	pm_runसमय_put(ahub->dev);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(tegra30_ahub_enable_tx_fअगरo);

पूर्णांक tegra30_ahub_disable_tx_fअगरo(क्रमागत tegra30_ahub_txcअगर txcअगर)
अणु
	पूर्णांक channel = txcअगर - TEGRA30_AHUB_TXCIF_APBIF_TX0;
	पूर्णांक reg, val;

	pm_runसमय_get_sync(ahub->dev);

	reg = TEGRA30_AHUB_CHANNEL_CTRL +
	      (channel * TEGRA30_AHUB_CHANNEL_CTRL_STRIDE);
	val = tegra30_apbअगर_पढ़ो(reg);
	val &= ~TEGRA30_AHUB_CHANNEL_CTRL_TX_EN;
	tegra30_apbअगर_ग_लिखो(reg, val);

	pm_runसमय_put(ahub->dev);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(tegra30_ahub_disable_tx_fअगरo);

पूर्णांक tegra30_ahub_मुक्त_tx_fअगरo(क्रमागत tegra30_ahub_txcअगर txcअगर)
अणु
	पूर्णांक channel = txcअगर - TEGRA30_AHUB_TXCIF_APBIF_TX0;

	__clear_bit(channel, ahub->tx_usage);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(tegra30_ahub_मुक्त_tx_fअगरo);

पूर्णांक tegra30_ahub_set_rx_cअगर_source(क्रमागत tegra30_ahub_rxcअगर rxcअगर,
				   क्रमागत tegra30_ahub_txcअगर txcअगर)
अणु
	पूर्णांक channel = rxcअगर - TEGRA30_AHUB_RXCIF_APBIF_RX0;
	पूर्णांक reg;

	pm_runसमय_get_sync(ahub->dev);

	reg = TEGRA30_AHUB_AUDIO_RX +
	      (channel * TEGRA30_AHUB_AUDIO_RX_STRIDE);
	tegra30_audio_ग_लिखो(reg, 1 << txcअगर);

	pm_runसमय_put(ahub->dev);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(tegra30_ahub_set_rx_cअगर_source);

पूर्णांक tegra30_ahub_unset_rx_cअगर_source(क्रमागत tegra30_ahub_rxcअगर rxcअगर)
अणु
	पूर्णांक channel = rxcअगर - TEGRA30_AHUB_RXCIF_APBIF_RX0;
	पूर्णांक reg;

	pm_runसमय_get_sync(ahub->dev);

	reg = TEGRA30_AHUB_AUDIO_RX +
	      (channel * TEGRA30_AHUB_AUDIO_RX_STRIDE);
	tegra30_audio_ग_लिखो(reg, 0);

	pm_runसमय_put(ahub->dev);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(tegra30_ahub_unset_rx_cअगर_source);

अटल स्थिर काष्ठा reset_control_bulk_data tegra30_ahub_resets_data[] = अणु
	अणु "d_audio" पूर्ण,
	अणु "apbif" पूर्ण,
	अणु "i2s0" पूर्ण,
	अणु "i2s1" पूर्ण,
	अणु "i2s2" पूर्ण,
	अणु "i2s3" पूर्ण,
	अणु "i2s4" पूर्ण,
	अणु "dam0" पूर्ण,
	अणु "dam1" पूर्ण,
	अणु "dam2" पूर्ण,
	अणु "spdif" पूर्ण,
	अणु "amx" पूर्ण, /* Tegra114+ */
	अणु "adx" पूर्ण, /* Tegra114+ */
	अणु "amx1" पूर्ण, /* Tegra124 */
	अणु "adx1" पूर्ण, /* Tegra124 */
	अणु "afc0" पूर्ण, /* Tegra124 */
	अणु "afc1" पूर्ण, /* Tegra124 */
	अणु "afc2" पूर्ण, /* Tegra124 */
	अणु "afc3" पूर्ण, /* Tegra124 */
	अणु "afc4" पूर्ण, /* Tegra124 */
	अणु "afc5" पूर्ण, /* Tegra124 */
पूर्ण;

#घोषणा LAST_REG(name) \
	(TEGRA30_AHUB_##name + \
	 (TEGRA30_AHUB_##name##_STRIDE * TEGRA30_AHUB_##name##_COUNT) - 4)

#घोषणा REG_IN_ARRAY(reg, name) \
	((reg >= TEGRA30_AHUB_##name) && \
	 (reg <= LAST_REG(name) && \
	 (!((reg - TEGRA30_AHUB_##name) % TEGRA30_AHUB_##name##_STRIDE))))

अटल bool tegra30_ahub_apbअगर_wr_rd_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल TEGRA30_AHUB_CONFIG_LINK_CTRL:
	हाल TEGRA30_AHUB_MISC_CTRL:
	हाल TEGRA30_AHUB_APBDMA_LIVE_STATUS:
	हाल TEGRA30_AHUB_I2S_LIVE_STATUS:
	हाल TEGRA30_AHUB_SPDIF_LIVE_STATUS:
	हाल TEGRA30_AHUB_I2S_INT_MASK:
	हाल TEGRA30_AHUB_DAM_INT_MASK:
	हाल TEGRA30_AHUB_SPDIF_INT_MASK:
	हाल TEGRA30_AHUB_APBIF_INT_MASK:
	हाल TEGRA30_AHUB_I2S_INT_STATUS:
	हाल TEGRA30_AHUB_DAM_INT_STATUS:
	हाल TEGRA30_AHUB_SPDIF_INT_STATUS:
	हाल TEGRA30_AHUB_APBIF_INT_STATUS:
	हाल TEGRA30_AHUB_I2S_INT_SOURCE:
	हाल TEGRA30_AHUB_DAM_INT_SOURCE:
	हाल TEGRA30_AHUB_SPDIF_INT_SOURCE:
	हाल TEGRA30_AHUB_APBIF_INT_SOURCE:
	हाल TEGRA30_AHUB_I2S_INT_SET:
	हाल TEGRA30_AHUB_DAM_INT_SET:
	हाल TEGRA30_AHUB_SPDIF_INT_SET:
	हाल TEGRA30_AHUB_APBIF_INT_SET:
		वापस true;
	शेष:
		अवरोध;
	पूर्ण

	अगर (REG_IN_ARRAY(reg, CHANNEL_CTRL) ||
	    REG_IN_ARRAY(reg, CHANNEL_CLEAR) ||
	    REG_IN_ARRAY(reg, CHANNEL_STATUS) ||
	    REG_IN_ARRAY(reg, CHANNEL_TXFIFO) ||
	    REG_IN_ARRAY(reg, CHANNEL_RXFIFO) ||
	    REG_IN_ARRAY(reg, CIF_TX_CTRL) ||
	    REG_IN_ARRAY(reg, CIF_RX_CTRL) ||
	    REG_IN_ARRAY(reg, DAM_LIVE_STATUS))
		वापस true;

	वापस false;
पूर्ण

अटल bool tegra30_ahub_apbअगर_अस्थिर_reg(काष्ठा device *dev,
					    अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल TEGRA30_AHUB_CONFIG_LINK_CTRL:
	हाल TEGRA30_AHUB_MISC_CTRL:
	हाल TEGRA30_AHUB_APBDMA_LIVE_STATUS:
	हाल TEGRA30_AHUB_I2S_LIVE_STATUS:
	हाल TEGRA30_AHUB_SPDIF_LIVE_STATUS:
	हाल TEGRA30_AHUB_I2S_INT_STATUS:
	हाल TEGRA30_AHUB_DAM_INT_STATUS:
	हाल TEGRA30_AHUB_SPDIF_INT_STATUS:
	हाल TEGRA30_AHUB_APBIF_INT_STATUS:
	हाल TEGRA30_AHUB_I2S_INT_SET:
	हाल TEGRA30_AHUB_DAM_INT_SET:
	हाल TEGRA30_AHUB_SPDIF_INT_SET:
	हाल TEGRA30_AHUB_APBIF_INT_SET:
		वापस true;
	शेष:
		अवरोध;
	पूर्ण

	अगर (REG_IN_ARRAY(reg, CHANNEL_CLEAR) ||
	    REG_IN_ARRAY(reg, CHANNEL_STATUS) ||
	    REG_IN_ARRAY(reg, CHANNEL_TXFIFO) ||
	    REG_IN_ARRAY(reg, CHANNEL_RXFIFO) ||
	    REG_IN_ARRAY(reg, DAM_LIVE_STATUS))
		वापस true;

	वापस false;
पूर्ण

अटल bool tegra30_ahub_apbअगर_precious_reg(काष्ठा device *dev,
					    अचिन्हित पूर्णांक reg)
अणु
	अगर (REG_IN_ARRAY(reg, CHANNEL_TXFIFO) ||
	    REG_IN_ARRAY(reg, CHANNEL_RXFIFO))
		वापस true;

	वापस false;
पूर्ण

अटल स्थिर काष्ठा regmap_config tegra30_ahub_apbअगर_regmap_config = अणु
	.name = "apbif",
	.reg_bits = 32,
	.val_bits = 32,
	.reg_stride = 4,
	.max_रेजिस्टर = TEGRA30_AHUB_APBIF_INT_SET,
	.ग_लिखोable_reg = tegra30_ahub_apbअगर_wr_rd_reg,
	.पढ़ोable_reg = tegra30_ahub_apbअगर_wr_rd_reg,
	.अस्थिर_reg = tegra30_ahub_apbअगर_अस्थिर_reg,
	.precious_reg = tegra30_ahub_apbअगर_precious_reg,
	.cache_type = REGCACHE_FLAT,
पूर्ण;

अटल bool tegra30_ahub_ahub_wr_rd_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	अगर (REG_IN_ARRAY(reg, AUDIO_RX))
		वापस true;

	वापस false;
पूर्ण

अटल स्थिर काष्ठा regmap_config tegra30_ahub_ahub_regmap_config = अणु
	.name = "ahub",
	.reg_bits = 32,
	.val_bits = 32,
	.reg_stride = 4,
	.max_रेजिस्टर = LAST_REG(AUDIO_RX),
	.ग_लिखोable_reg = tegra30_ahub_ahub_wr_rd_reg,
	.पढ़ोable_reg = tegra30_ahub_ahub_wr_rd_reg,
	.cache_type = REGCACHE_FLAT,
पूर्ण;

अटल काष्ठा tegra30_ahub_soc_data soc_data_tegra30 = अणु
	.num_resets = 11,
	.set_audio_cअगर = tegra30_ahub_set_cअगर,
पूर्ण;

अटल काष्ठा tegra30_ahub_soc_data soc_data_tegra114 = अणु
	.num_resets = 13,
	.set_audio_cअगर = tegra30_ahub_set_cअगर,
पूर्ण;

अटल काष्ठा tegra30_ahub_soc_data soc_data_tegra124 = अणु
	.num_resets = 21,
	.set_audio_cअगर = tegra124_ahub_set_cअगर,
पूर्ण;

अटल स्थिर काष्ठा of_device_id tegra30_ahub_of_match[] = अणु
	अणु .compatible = "nvidia,tegra124-ahub", .data = &soc_data_tegra124 पूर्ण,
	अणु .compatible = "nvidia,tegra114-ahub", .data = &soc_data_tegra114 पूर्ण,
	अणु .compatible = "nvidia,tegra30-ahub",  .data = &soc_data_tegra30 पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल पूर्णांक tegra30_ahub_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा of_device_id *match;
	स्थिर काष्ठा tegra30_ahub_soc_data *soc_data;
	काष्ठा resource *res0;
	व्योम __iomem *regs_apbअगर, *regs_ahub;
	पूर्णांक ret = 0;

	match = of_match_device(tegra30_ahub_of_match, &pdev->dev);
	अगर (!match)
		वापस -EINVAL;
	soc_data = match->data;

	ahub = devm_kzalloc(&pdev->dev, माप(काष्ठा tegra30_ahub),
			    GFP_KERNEL);
	अगर (!ahub)
		वापस -ENOMEM;
	dev_set_drvdata(&pdev->dev, ahub);

	BUILD_BUG_ON(माप(ahub->resets) != माप(tegra30_ahub_resets_data));
	स_नकल(ahub->resets, tegra30_ahub_resets_data, माप(ahub->resets));

	ahub->nresets = soc_data->num_resets;
	ahub->soc_data = soc_data;
	ahub->dev = &pdev->dev;

	ahub->घड़ीs[ahub->nघड़ीs++].id = "apbif";
	ahub->घड़ीs[ahub->nघड़ीs++].id = "d_audio";

	ret = devm_clk_bulk_get(&pdev->dev, ahub->nघड़ीs, ahub->घड़ीs);
	अगर (ret)
		जाओ err_unset_ahub;

	ret = devm_reset_control_bulk_get_exclusive(&pdev->dev, ahub->nresets,
						    ahub->resets);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Can't get resets: %d\n", ret);
		जाओ err_unset_ahub;
	पूर्ण

	res0 = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	regs_apbअगर = devm_ioremap_resource(&pdev->dev, res0);
	अगर (IS_ERR(regs_apbअगर)) अणु
		ret = PTR_ERR(regs_apbअगर);
		जाओ err_unset_ahub;
	पूर्ण

	ahub->apbअगर_addr = res0->start;

	ahub->regmap_apbअगर = devm_regmap_init_mmio(&pdev->dev, regs_apbअगर,
					&tegra30_ahub_apbअगर_regmap_config);
	अगर (IS_ERR(ahub->regmap_apbअगर)) अणु
		dev_err(&pdev->dev, "apbif regmap init failed\n");
		ret = PTR_ERR(ahub->regmap_apbअगर);
		जाओ err_unset_ahub;
	पूर्ण
	regcache_cache_only(ahub->regmap_apbअगर, true);

	regs_ahub = devm_platक्रमm_ioremap_resource(pdev, 1);
	अगर (IS_ERR(regs_ahub)) अणु
		ret = PTR_ERR(regs_ahub);
		जाओ err_unset_ahub;
	पूर्ण

	ahub->regmap_ahub = devm_regmap_init_mmio(&pdev->dev, regs_ahub,
					&tegra30_ahub_ahub_regmap_config);
	अगर (IS_ERR(ahub->regmap_ahub)) अणु
		dev_err(&pdev->dev, "ahub regmap init failed\n");
		ret = PTR_ERR(ahub->regmap_ahub);
		जाओ err_unset_ahub;
	पूर्ण
	regcache_cache_only(ahub->regmap_ahub, true);

	pm_runसमय_enable(&pdev->dev);

	of_platक्रमm_populate(pdev->dev.of_node, शून्य, शून्य, &pdev->dev);

	वापस 0;

err_unset_ahub:
	ahub = शून्य;

	वापस ret;
पूर्ण

अटल पूर्णांक tegra30_ahub_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	pm_runसमय_disable(&pdev->dev);

	ahub = शून्य;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops tegra30_ahub_pm_ops = अणु
	SET_RUNTIME_PM_OPS(tegra30_ahub_runसमय_suspend,
			   tegra30_ahub_runसमय_resume, शून्य)
	SET_SYSTEM_SLEEP_PM_OPS(pm_runसमय_क्रमce_suspend,
				pm_runसमय_क्रमce_resume)
पूर्ण;

अटल काष्ठा platक्रमm_driver tegra30_ahub_driver = अणु
	.probe = tegra30_ahub_probe,
	.हटाओ = tegra30_ahub_हटाओ,
	.driver = अणु
		.name = DRV_NAME,
		.of_match_table = tegra30_ahub_of_match,
		.pm = &tegra30_ahub_pm_ops,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(tegra30_ahub_driver);

व्योम tegra30_ahub_set_cअगर(काष्ठा regmap *regmap, अचिन्हित पूर्णांक reg,
			  काष्ठा tegra30_ahub_cअगर_conf *conf)
अणु
	अचिन्हित पूर्णांक value;

	value = (conf->threshold <<
			TEGRA30_AUDIOCIF_CTRL_FIFO_THRESHOLD_SHIFT) |
		((conf->audio_channels - 1) <<
			TEGRA30_AUDIOCIF_CTRL_AUDIO_CHANNELS_SHIFT) |
		((conf->client_channels - 1) <<
			TEGRA30_AUDIOCIF_CTRL_CLIENT_CHANNELS_SHIFT) |
		(conf->audio_bits <<
			TEGRA30_AUDIOCIF_CTRL_AUDIO_BITS_SHIFT) |
		(conf->client_bits <<
			TEGRA30_AUDIOCIF_CTRL_CLIENT_BITS_SHIFT) |
		(conf->expand <<
			TEGRA30_AUDIOCIF_CTRL_EXPAND_SHIFT) |
		(conf->stereo_conv <<
			TEGRA30_AUDIOCIF_CTRL_STEREO_CONV_SHIFT) |
		(conf->replicate <<
			TEGRA30_AUDIOCIF_CTRL_REPLICATE_SHIFT) |
		(conf->direction <<
			TEGRA30_AUDIOCIF_CTRL_सूचीECTION_SHIFT) |
		(conf->truncate <<
			TEGRA30_AUDIOCIF_CTRL_TRUNCATE_SHIFT) |
		(conf->mono_conv <<
			TEGRA30_AUDIOCIF_CTRL_MONO_CONV_SHIFT);

	regmap_ग_लिखो(regmap, reg, value);
पूर्ण
EXPORT_SYMBOL_GPL(tegra30_ahub_set_cअगर);

व्योम tegra124_ahub_set_cअगर(काष्ठा regmap *regmap, अचिन्हित पूर्णांक reg,
			   काष्ठा tegra30_ahub_cअगर_conf *conf)
अणु
	अचिन्हित पूर्णांक value;

	value = (conf->threshold <<
			TEGRA124_AUDIOCIF_CTRL_FIFO_THRESHOLD_SHIFT) |
		((conf->audio_channels - 1) <<
			TEGRA124_AUDIOCIF_CTRL_AUDIO_CHANNELS_SHIFT) |
		((conf->client_channels - 1) <<
			TEGRA124_AUDIOCIF_CTRL_CLIENT_CHANNELS_SHIFT) |
		(conf->audio_bits <<
			TEGRA30_AUDIOCIF_CTRL_AUDIO_BITS_SHIFT) |
		(conf->client_bits <<
			TEGRA30_AUDIOCIF_CTRL_CLIENT_BITS_SHIFT) |
		(conf->expand <<
			TEGRA30_AUDIOCIF_CTRL_EXPAND_SHIFT) |
		(conf->stereo_conv <<
			TEGRA30_AUDIOCIF_CTRL_STEREO_CONV_SHIFT) |
		(conf->replicate <<
			TEGRA30_AUDIOCIF_CTRL_REPLICATE_SHIFT) |
		(conf->direction <<
			TEGRA30_AUDIOCIF_CTRL_सूचीECTION_SHIFT) |
		(conf->truncate <<
			TEGRA30_AUDIOCIF_CTRL_TRUNCATE_SHIFT) |
		(conf->mono_conv <<
			TEGRA30_AUDIOCIF_CTRL_MONO_CONV_SHIFT);

	regmap_ग_लिखो(regmap, reg, value);
पूर्ण
EXPORT_SYMBOL_GPL(tegra124_ahub_set_cअगर);

MODULE_AUTHOR("Stephen Warren <swarren@nvidia.com>");
MODULE_DESCRIPTION("Tegra30 AHUB driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:" DRV_NAME);
MODULE_DEVICE_TABLE(of, tegra30_ahub_of_match);
