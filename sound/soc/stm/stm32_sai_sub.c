<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * STM32 ALSA SoC Digital Audio Interface (SAI) driver.
 *
 * Copyright (C) 2016, STMicroelectronics - All Rights Reserved
 * Author(s): Olivier Moysan <olivier.moysan@st.com> क्रम STMicroelectronics.
 */

#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regmap.h>

#समावेश <sound/asoundef.h>
#समावेश <sound/core.h>
#समावेश <sound/dmaengine_pcm.h>
#समावेश <sound/pcm_params.h>

#समावेश "stm32_sai.h"

#घोषणा SAI_FREE_PROTOCOL	0x0
#घोषणा SAI_SPDIF_PROTOCOL	0x1

#घोषणा SAI_SLOT_SIZE_AUTO	0x0
#घोषणा SAI_SLOT_SIZE_16	0x1
#घोषणा SAI_SLOT_SIZE_32	0x2

#घोषणा SAI_DATASIZE_8		0x2
#घोषणा SAI_DATASIZE_10		0x3
#घोषणा SAI_DATASIZE_16		0x4
#घोषणा SAI_DATASIZE_20		0x5
#घोषणा SAI_DATASIZE_24		0x6
#घोषणा SAI_DATASIZE_32		0x7

#घोषणा STM_SAI_DAI_NAME_SIZE	15

#घोषणा STM_SAI_IS_PLAYBACK(ip)	((ip)->dir == SNDRV_PCM_STREAM_PLAYBACK)
#घोषणा STM_SAI_IS_CAPTURE(ip)	((ip)->dir == SNDRV_PCM_STREAM_CAPTURE)

#घोषणा STM_SAI_A_ID		0x0
#घोषणा STM_SAI_B_ID		0x1

#घोषणा STM_SAI_IS_SUB_A(x)	((x)->id == STM_SAI_A_ID)
#घोषणा STM_SAI_IS_SUB_B(x)	((x)->id == STM_SAI_B_ID)
#घोषणा STM_SAI_BLOCK_NAME(x)	(((x)->id == STM_SAI_A_ID) ? "A" : "B")

#घोषणा SAI_SYNC_NONE		0x0
#घोषणा SAI_SYNC_INTERNAL	0x1
#घोषणा SAI_SYNC_EXTERNAL	0x2

#घोषणा STM_SAI_PROTOCOL_IS_SPDIF(ip)	((ip)->spdअगर)
#घोषणा STM_SAI_HAS_SPDIF(x)	((x)->pdata->conf.has_spdअगर_pdm)
#घोषणा STM_SAI_HAS_PDM(x)	((x)->pdata->conf.has_spdअगर_pdm)
#घोषणा STM_SAI_HAS_EXT_SYNC(x) (!STM_SAI_IS_F4(sai->pdata))

#घोषणा SAI_IEC60958_BLOCK_FRAMES	192
#घोषणा SAI_IEC60958_STATUS_BYTES	24

#घोषणा SAI_MCLK_NAME_LEN		32
#घोषणा SAI_RATE_11K			11025

/**
 * काष्ठा sपंचांग32_sai_sub_data - निजी data of SAI sub block (block A or B)
 * @pdev: device data poपूर्णांकer
 * @regmap: SAI रेजिस्टर map poपूर्णांकer
 * @regmap_config: SAI sub block रेजिस्टर map configuration poपूर्णांकer
 * @dma_params: dma configuration data क्रम rx or tx channel
 * @cpu_dai_drv: DAI driver data poपूर्णांकer
 * @cpu_dai: DAI runसमय data poपूर्णांकer
 * @substream: PCM substream data poपूर्णांकer
 * @pdata: SAI block parent data poपूर्णांकer
 * @np_sync_provider: synchronization provider node
 * @sai_ck: kernel घड़ी feeding the SAI घड़ी generator
 * @sai_mclk: master घड़ी from SAI mclk provider
 * @phys_addr: SAI रेजिस्टरs physical base address
 * @mclk_rate: SAI block master घड़ी frequency (Hz). set at init
 * @id: SAI sub block id corresponding to sub-block A or B
 * @dir: SAI block direction (playback or capture). set at init
 * @master: SAI block mode flag. (true=master, false=slave) set at init
 * @spdअगर: SAI S/PDIF iec60958 mode flag. set at init
 * @fmt: SAI block क्रमmat. relevant only क्रम custom protocols. set at init
 * @sync: SAI block synchronization mode. (none, पूर्णांकernal or बाह्यal)
 * @synco: SAI block ext sync source (provider setting). (none, sub-block A/B)
 * @synci: SAI block ext sync source (client setting). (SAI sync provider index)
 * @fs_length: frame synchronization length. depends on protocol settings
 * @slots: rx or tx slot number
 * @slot_width: rx or tx slot width in bits
 * @slot_mask: rx or tx active slots mask. set at init or at runसमय
 * @data_size: PCM data width. corresponds to PCM substream width.
 * @spdअगर_frm_cnt: S/PDIF playback frame counter
 * @iec958: iec958 data
 * @ctrl_lock: control lock
 * @irq_lock: prevent race condition with IRQ
 */
काष्ठा sपंचांग32_sai_sub_data अणु
	काष्ठा platक्रमm_device *pdev;
	काष्ठा regmap *regmap;
	स्थिर काष्ठा regmap_config *regmap_config;
	काष्ठा snd_dmaengine_dai_dma_data dma_params;
	काष्ठा snd_soc_dai_driver cpu_dai_drv;
	काष्ठा snd_soc_dai *cpu_dai;
	काष्ठा snd_pcm_substream *substream;
	काष्ठा sपंचांग32_sai_data *pdata;
	काष्ठा device_node *np_sync_provider;
	काष्ठा clk *sai_ck;
	काष्ठा clk *sai_mclk;
	dma_addr_t phys_addr;
	अचिन्हित पूर्णांक mclk_rate;
	अचिन्हित पूर्णांक id;
	पूर्णांक dir;
	bool master;
	bool spdअगर;
	पूर्णांक fmt;
	पूर्णांक sync;
	पूर्णांक synco;
	पूर्णांक synci;
	पूर्णांक fs_length;
	पूर्णांक slots;
	पूर्णांक slot_width;
	पूर्णांक slot_mask;
	पूर्णांक data_size;
	अचिन्हित पूर्णांक spdअगर_frm_cnt;
	काष्ठा snd_aes_iec958 iec958;
	काष्ठा mutex ctrl_lock; /* protect resources accessed by controls */
	spinlock_t irq_lock; /* used to prevent race condition with IRQ */
पूर्ण;

क्रमागत sपंचांग32_sai_fअगरo_th अणु
	STM_SAI_FIFO_TH_EMPTY,
	STM_SAI_FIFO_TH_QUARTER,
	STM_SAI_FIFO_TH_HALF,
	STM_SAI_FIFO_TH_3_QUARTER,
	STM_SAI_FIFO_TH_FULL,
पूर्ण;

अटल bool sपंचांग32_sai_sub_पढ़ोable_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल STM_SAI_CR1_REGX:
	हाल STM_SAI_CR2_REGX:
	हाल STM_SAI_FRCR_REGX:
	हाल STM_SAI_SLOTR_REGX:
	हाल STM_SAI_IMR_REGX:
	हाल STM_SAI_SR_REGX:
	हाल STM_SAI_CLRFR_REGX:
	हाल STM_SAI_DR_REGX:
	हाल STM_SAI_PDMCR_REGX:
	हाल STM_SAI_PDMLY_REGX:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool sपंचांग32_sai_sub_अस्थिर_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल STM_SAI_DR_REGX:
	हाल STM_SAI_SR_REGX:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool sपंचांग32_sai_sub_ग_लिखोable_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल STM_SAI_CR1_REGX:
	हाल STM_SAI_CR2_REGX:
	हाल STM_SAI_FRCR_REGX:
	हाल STM_SAI_SLOTR_REGX:
	हाल STM_SAI_IMR_REGX:
	हाल STM_SAI_CLRFR_REGX:
	हाल STM_SAI_DR_REGX:
	हाल STM_SAI_PDMCR_REGX:
	हाल STM_SAI_PDMLY_REGX:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल पूर्णांक sपंचांग32_sai_sub_reg_up(काष्ठा sपंचांग32_sai_sub_data *sai,
				अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक mask,
				अचिन्हित पूर्णांक val)
अणु
	पूर्णांक ret;

	ret = clk_enable(sai->pdata->pclk);
	अगर (ret < 0)
		वापस ret;

	ret = regmap_update_bits(sai->regmap, reg, mask, val);

	clk_disable(sai->pdata->pclk);

	वापस ret;
पूर्ण

अटल पूर्णांक sपंचांग32_sai_sub_reg_wr(काष्ठा sपंचांग32_sai_sub_data *sai,
				अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक mask,
				अचिन्हित पूर्णांक val)
अणु
	पूर्णांक ret;

	ret = clk_enable(sai->pdata->pclk);
	अगर (ret < 0)
		वापस ret;

	ret = regmap_ग_लिखो_bits(sai->regmap, reg, mask, val);

	clk_disable(sai->pdata->pclk);

	वापस ret;
पूर्ण

अटल पूर्णांक sपंचांग32_sai_sub_reg_rd(काष्ठा sपंचांग32_sai_sub_data *sai,
				अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक *val)
अणु
	पूर्णांक ret;

	ret = clk_enable(sai->pdata->pclk);
	अगर (ret < 0)
		वापस ret;

	ret = regmap_पढ़ो(sai->regmap, reg, val);

	clk_disable(sai->pdata->pclk);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा regmap_config sपंचांग32_sai_sub_regmap_config_f4 = अणु
	.reg_bits = 32,
	.reg_stride = 4,
	.val_bits = 32,
	.max_रेजिस्टर = STM_SAI_DR_REGX,
	.पढ़ोable_reg = sपंचांग32_sai_sub_पढ़ोable_reg,
	.अस्थिर_reg = sपंचांग32_sai_sub_अस्थिर_reg,
	.ग_लिखोable_reg = sपंचांग32_sai_sub_ग_लिखोable_reg,
	.fast_io = true,
	.cache_type = REGCACHE_FLAT,
पूर्ण;

अटल स्थिर काष्ठा regmap_config sपंचांग32_sai_sub_regmap_config_h7 = अणु
	.reg_bits = 32,
	.reg_stride = 4,
	.val_bits = 32,
	.max_रेजिस्टर = STM_SAI_PDMLY_REGX,
	.पढ़ोable_reg = sपंचांग32_sai_sub_पढ़ोable_reg,
	.अस्थिर_reg = sपंचांग32_sai_sub_अस्थिर_reg,
	.ग_लिखोable_reg = sपंचांग32_sai_sub_ग_लिखोable_reg,
	.fast_io = true,
	.cache_type = REGCACHE_FLAT,
पूर्ण;

अटल पूर्णांक snd_pcm_iec958_info(काष्ठा snd_kcontrol *kcontrol,
			       काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_IEC958;
	uinfo->count = 1;

	वापस 0;
पूर्ण

अटल पूर्णांक snd_pcm_iec958_get(काष्ठा snd_kcontrol *kcontrol,
			      काष्ठा snd_ctl_elem_value *uctl)
अणु
	काष्ठा sपंचांग32_sai_sub_data *sai = snd_kcontrol_chip(kcontrol);

	mutex_lock(&sai->ctrl_lock);
	स_नकल(uctl->value.iec958.status, sai->iec958.status, 4);
	mutex_unlock(&sai->ctrl_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक snd_pcm_iec958_put(काष्ठा snd_kcontrol *kcontrol,
			      काष्ठा snd_ctl_elem_value *uctl)
अणु
	काष्ठा sपंचांग32_sai_sub_data *sai = snd_kcontrol_chip(kcontrol);

	mutex_lock(&sai->ctrl_lock);
	स_नकल(sai->iec958.status, uctl->value.iec958.status, 4);
	mutex_unlock(&sai->ctrl_lock);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new iec958_ctls = अणु
	.access = (SNDRV_CTL_ELEM_ACCESS_READWRITE |
			SNDRV_CTL_ELEM_ACCESS_VOLATILE),
	.अगरace = SNDRV_CTL_ELEM_IFACE_PCM,
	.name = SNDRV_CTL_NAME_IEC958("", PLAYBACK, DEFAULT),
	.info = snd_pcm_iec958_info,
	.get = snd_pcm_iec958_get,
	.put = snd_pcm_iec958_put,
पूर्ण;

काष्ठा sपंचांग32_sai_mclk_data अणु
	काष्ठा clk_hw hw;
	अचिन्हित दीर्घ freq;
	काष्ठा sपंचांग32_sai_sub_data *sai_data;
पूर्ण;

#घोषणा to_mclk_data(_hw) container_of(_hw, काष्ठा sपंचांग32_sai_mclk_data, hw)
#घोषणा STM32_SAI_MAX_CLKS 1

अटल पूर्णांक sपंचांग32_sai_get_clk_भाग(काष्ठा sपंचांग32_sai_sub_data *sai,
				 अचिन्हित दीर्घ input_rate,
				 अचिन्हित दीर्घ output_rate)
अणु
	पूर्णांक version = sai->pdata->conf.version;
	पूर्णांक भाग;

	भाग = DIV_ROUND_CLOSEST(input_rate, output_rate);
	अगर (भाग > SAI_XCR1_MCKDIV_MAX(version)) अणु
		dev_err(&sai->pdev->dev, "Divider %d out of range\n", भाग);
		वापस -EINVAL;
	पूर्ण
	dev_dbg(&sai->pdev->dev, "SAI divider %d\n", भाग);

	अगर (input_rate % भाग)
		dev_dbg(&sai->pdev->dev,
			"Rate not accurate. requested (%ld), actual (%ld)\n",
			output_rate, input_rate / भाग);

	वापस भाग;
पूर्ण

अटल पूर्णांक sपंचांग32_sai_set_clk_भाग(काष्ठा sपंचांग32_sai_sub_data *sai,
				 अचिन्हित पूर्णांक भाग)
अणु
	पूर्णांक version = sai->pdata->conf.version;
	पूर्णांक ret, cr1, mask;

	अगर (भाग > SAI_XCR1_MCKDIV_MAX(version)) अणु
		dev_err(&sai->pdev->dev, "Divider %d out of range\n", भाग);
		वापस -EINVAL;
	पूर्ण

	mask = SAI_XCR1_MCKDIV_MASK(SAI_XCR1_MCKDIV_WIDTH(version));
	cr1 = SAI_XCR1_MCKDIV_SET(भाग);
	ret = sपंचांग32_sai_sub_reg_up(sai, STM_SAI_CR1_REGX, mask, cr1);
	अगर (ret < 0)
		dev_err(&sai->pdev->dev, "Failed to update CR1 register\n");

	वापस ret;
पूर्ण

अटल पूर्णांक sपंचांग32_sai_set_parent_घड़ी(काष्ठा sपंचांग32_sai_sub_data *sai,
				      अचिन्हित पूर्णांक rate)
अणु
	काष्ठा platक्रमm_device *pdev = sai->pdev;
	काष्ठा clk *parent_clk = sai->pdata->clk_x8k;
	पूर्णांक ret;

	अगर (!(rate % SAI_RATE_11K))
		parent_clk = sai->pdata->clk_x11k;

	ret = clk_set_parent(sai->sai_ck, parent_clk);
	अगर (ret)
		dev_err(&pdev->dev, " Error %d setting sai_ck parent clock. %s",
			ret, ret == -EBUSY ?
			"Active stream rates conflict\n" : "\n");

	वापस ret;
पूर्ण

अटल दीर्घ sपंचांग32_sai_mclk_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				      अचिन्हित दीर्घ *prate)
अणु
	काष्ठा sपंचांग32_sai_mclk_data *mclk = to_mclk_data(hw);
	काष्ठा sपंचांग32_sai_sub_data *sai = mclk->sai_data;
	पूर्णांक भाग;

	भाग = sपंचांग32_sai_get_clk_भाग(sai, *prate, rate);
	अगर (भाग < 0)
		वापस भाग;

	mclk->freq = *prate / भाग;

	वापस mclk->freq;
पूर्ण

अटल अचिन्हित दीर्घ sपंचांग32_sai_mclk_recalc_rate(काष्ठा clk_hw *hw,
						अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा sपंचांग32_sai_mclk_data *mclk = to_mclk_data(hw);

	वापस mclk->freq;
पूर्ण

अटल पूर्णांक sपंचांग32_sai_mclk_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				   अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा sपंचांग32_sai_mclk_data *mclk = to_mclk_data(hw);
	काष्ठा sपंचांग32_sai_sub_data *sai = mclk->sai_data;
	पूर्णांक भाग, ret;

	भाग = sपंचांग32_sai_get_clk_भाग(sai, parent_rate, rate);
	अगर (भाग < 0)
		वापस भाग;

	ret = sपंचांग32_sai_set_clk_भाग(sai, भाग);
	अगर (ret)
		वापस ret;

	mclk->freq = rate;

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_sai_mclk_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा sपंचांग32_sai_mclk_data *mclk = to_mclk_data(hw);
	काष्ठा sपंचांग32_sai_sub_data *sai = mclk->sai_data;

	dev_dbg(&sai->pdev->dev, "Enable master clock\n");

	वापस sपंचांग32_sai_sub_reg_up(sai, STM_SAI_CR1_REGX,
				    SAI_XCR1_MCKEN, SAI_XCR1_MCKEN);
पूर्ण

अटल व्योम sपंचांग32_sai_mclk_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा sपंचांग32_sai_mclk_data *mclk = to_mclk_data(hw);
	काष्ठा sपंचांग32_sai_sub_data *sai = mclk->sai_data;

	dev_dbg(&sai->pdev->dev, "Disable master clock\n");

	sपंचांग32_sai_sub_reg_up(sai, STM_SAI_CR1_REGX, SAI_XCR1_MCKEN, 0);
पूर्ण

अटल स्थिर काष्ठा clk_ops mclk_ops = अणु
	.enable = sपंचांग32_sai_mclk_enable,
	.disable = sपंचांग32_sai_mclk_disable,
	.recalc_rate = sपंचांग32_sai_mclk_recalc_rate,
	.round_rate = sपंचांग32_sai_mclk_round_rate,
	.set_rate = sपंचांग32_sai_mclk_set_rate,
पूर्ण;

अटल पूर्णांक sपंचांग32_sai_add_mclk_provider(काष्ठा sपंचांग32_sai_sub_data *sai)
अणु
	काष्ठा clk_hw *hw;
	काष्ठा sपंचांग32_sai_mclk_data *mclk;
	काष्ठा device *dev = &sai->pdev->dev;
	स्थिर अक्षर *pname = __clk_get_name(sai->sai_ck);
	अक्षर *mclk_name, *p, *s = (अक्षर *)pname;
	पूर्णांक ret, i = 0;

	mclk = devm_kzalloc(dev, माप(*mclk), GFP_KERNEL);
	अगर (!mclk)
		वापस -ENOMEM;

	mclk_name = devm_kसुस्मृति(dev, माप(अक्षर),
				 SAI_MCLK_NAME_LEN, GFP_KERNEL);
	अगर (!mclk_name)
		वापस -ENOMEM;

	/*
	 * Forge mclk घड़ी name from parent घड़ी name and suffix.
	 * String after "_" अक्षर is stripped in parent name.
	 */
	p = mclk_name;
	जबतक (*s && *s != '_' && (i < (SAI_MCLK_NAME_LEN - 7))) अणु
		*p++ = *s++;
		i++;
	पूर्ण
	STM_SAI_IS_SUB_A(sai) ? म_जोड़ो(p, "a_mclk") : म_जोड़ो(p, "b_mclk");

	mclk->hw.init = CLK_HW_INIT(mclk_name, pname, &mclk_ops, 0);
	mclk->sai_data = sai;
	hw = &mclk->hw;

	dev_dbg(dev, "Register master clock %s\n", mclk_name);
	ret = devm_clk_hw_रेजिस्टर(&sai->pdev->dev, hw);
	अगर (ret) अणु
		dev_err(dev, "mclk register returned %d\n", ret);
		वापस ret;
	पूर्ण
	sai->sai_mclk = hw->clk;

	/* रेजिस्टर mclk provider */
	वापस devm_of_clk_add_hw_provider(dev, of_clk_hw_simple_get, hw);
पूर्ण

अटल irqवापस_t sपंचांग32_sai_isr(पूर्णांक irq, व्योम *devid)
अणु
	काष्ठा sपंचांग32_sai_sub_data *sai = (काष्ठा sपंचांग32_sai_sub_data *)devid;
	काष्ठा platक्रमm_device *pdev = sai->pdev;
	अचिन्हित पूर्णांक sr, imr, flags;
	snd_pcm_state_t status = SNDRV_PCM_STATE_RUNNING;

	sपंचांग32_sai_sub_reg_rd(sai, STM_SAI_IMR_REGX, &imr);
	sपंचांग32_sai_sub_reg_rd(sai, STM_SAI_SR_REGX, &sr);

	flags = sr & imr;
	अगर (!flags)
		वापस IRQ_NONE;

	sपंचांग32_sai_sub_reg_wr(sai, STM_SAI_CLRFR_REGX, SAI_XCLRFR_MASK,
			     SAI_XCLRFR_MASK);

	अगर (!sai->substream) अणु
		dev_err(&pdev->dev, "Device stopped. Spurious IRQ 0x%x\n", sr);
		वापस IRQ_NONE;
	पूर्ण

	अगर (flags & SAI_XIMR_OVRUDRIE) अणु
		dev_err(&pdev->dev, "IRQ %s\n",
			STM_SAI_IS_PLAYBACK(sai) ? "underrun" : "overrun");
		status = SNDRV_PCM_STATE_XRUN;
	पूर्ण

	अगर (flags & SAI_XIMR_MUTEDETIE)
		dev_dbg(&pdev->dev, "IRQ mute detected\n");

	अगर (flags & SAI_XIMR_WCKCFGIE) अणु
		dev_err(&pdev->dev, "IRQ wrong clock configuration\n");
		status = SNDRV_PCM_STATE_DISCONNECTED;
	पूर्ण

	अगर (flags & SAI_XIMR_CNRDYIE)
		dev_err(&pdev->dev, "IRQ Codec not ready\n");

	अगर (flags & SAI_XIMR_AFSDETIE) अणु
		dev_err(&pdev->dev, "IRQ Anticipated frame synchro\n");
		status = SNDRV_PCM_STATE_XRUN;
	पूर्ण

	अगर (flags & SAI_XIMR_LFSDETIE) अणु
		dev_err(&pdev->dev, "IRQ Late frame synchro\n");
		status = SNDRV_PCM_STATE_XRUN;
	पूर्ण

	spin_lock(&sai->irq_lock);
	अगर (status != SNDRV_PCM_STATE_RUNNING && sai->substream)
		snd_pcm_stop_xrun(sai->substream);
	spin_unlock(&sai->irq_lock);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक sपंचांग32_sai_set_sysclk(काष्ठा snd_soc_dai *cpu_dai,
				पूर्णांक clk_id, अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा sपंचांग32_sai_sub_data *sai = snd_soc_dai_get_drvdata(cpu_dai);
	पूर्णांक ret;

	अगर (dir == SND_SOC_CLOCK_OUT && sai->sai_mclk) अणु
		ret = sपंचांग32_sai_sub_reg_up(sai, STM_SAI_CR1_REGX,
					   SAI_XCR1_NODIV,
					 freq ? 0 : SAI_XCR1_NODIV);
		अगर (ret < 0)
			वापस ret;

		/* Assume shutकरोwn अगर requested frequency is 0Hz */
		अगर (!freq) अणु
			/* Release mclk rate only अगर rate was actually set */
			अगर (sai->mclk_rate) अणु
				clk_rate_exclusive_put(sai->sai_mclk);
				sai->mclk_rate = 0;
			पूर्ण
			वापस 0;
		पूर्ण

		/* If master घड़ी is used, set parent घड़ी now */
		ret = sपंचांग32_sai_set_parent_घड़ी(sai, freq);
		अगर (ret)
			वापस ret;

		ret = clk_set_rate_exclusive(sai->sai_mclk, freq);
		अगर (ret) अणु
			dev_err(cpu_dai->dev,
				ret == -EBUSY ?
				"Active streams have incompatible rates" :
				"Could not set mclk rate\n");
			वापस ret;
		पूर्ण

		dev_dbg(cpu_dai->dev, "SAI MCLK frequency is %uHz\n", freq);
		sai->mclk_rate = freq;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_sai_set_dai_tdm_slot(काष्ठा snd_soc_dai *cpu_dai, u32 tx_mask,
				      u32 rx_mask, पूर्णांक slots, पूर्णांक slot_width)
अणु
	काष्ठा sपंचांग32_sai_sub_data *sai = snd_soc_dai_get_drvdata(cpu_dai);
	पूर्णांक slotr, slotr_mask, slot_size;

	अगर (STM_SAI_PROTOCOL_IS_SPDIF(sai)) अणु
		dev_warn(cpu_dai->dev, "Slot setting relevant only for TDM\n");
		वापस 0;
	पूर्ण

	dev_dbg(cpu_dai->dev, "Masks tx/rx:%#x/%#x, slots:%d, width:%d\n",
		tx_mask, rx_mask, slots, slot_width);

	चयन (slot_width) अणु
	हाल 16:
		slot_size = SAI_SLOT_SIZE_16;
		अवरोध;
	हाल 32:
		slot_size = SAI_SLOT_SIZE_32;
		अवरोध;
	शेष:
		slot_size = SAI_SLOT_SIZE_AUTO;
		अवरोध;
	पूर्ण

	slotr = SAI_XSLOTR_SLOTSZ_SET(slot_size) |
		SAI_XSLOTR_NBSLOT_SET(slots - 1);
	slotr_mask = SAI_XSLOTR_SLOTSZ_MASK | SAI_XSLOTR_NBSLOT_MASK;

	/* tx/rx mask set in machine init, अगर slot number defined in DT */
	अगर (STM_SAI_IS_PLAYBACK(sai)) अणु
		sai->slot_mask = tx_mask;
		slotr |= SAI_XSLOTR_SLOTEN_SET(tx_mask);
	पूर्ण

	अगर (STM_SAI_IS_CAPTURE(sai)) अणु
		sai->slot_mask = rx_mask;
		slotr |= SAI_XSLOTR_SLOTEN_SET(rx_mask);
	पूर्ण

	slotr_mask |= SAI_XSLOTR_SLOTEN_MASK;

	sपंचांग32_sai_sub_reg_up(sai, STM_SAI_SLOTR_REGX, slotr_mask, slotr);

	sai->slot_width = slot_width;
	sai->slots = slots;

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_sai_set_dai_fmt(काष्ठा snd_soc_dai *cpu_dai, अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा sपंचांग32_sai_sub_data *sai = snd_soc_dai_get_drvdata(cpu_dai);
	पूर्णांक cr1, frcr = 0;
	पूर्णांक cr1_mask, frcr_mask = 0;
	पूर्णांक ret;

	dev_dbg(cpu_dai->dev, "fmt %x\n", fmt);

	/* Do not generate master by शेष */
	cr1 = SAI_XCR1_NODIV;
	cr1_mask = SAI_XCR1_NODIV;

	cr1_mask |= SAI_XCR1_PRTCFG_MASK;
	अगर (STM_SAI_PROTOCOL_IS_SPDIF(sai)) अणु
		cr1 |= SAI_XCR1_PRTCFG_SET(SAI_SPDIF_PROTOCOL);
		जाओ conf_update;
	पूर्ण

	cr1 |= SAI_XCR1_PRTCFG_SET(SAI_FREE_PROTOCOL);

	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	/* SCK active high क्रम all protocols */
	हाल SND_SOC_DAIFMT_I2S:
		cr1 |= SAI_XCR1_CKSTR;
		frcr |= SAI_XFRCR_FSOFF | SAI_XFRCR_FSDEF;
		अवरोध;
	/* Left justअगरied */
	हाल SND_SOC_DAIFMT_MSB:
		frcr |= SAI_XFRCR_FSPOL | SAI_XFRCR_FSDEF;
		अवरोध;
	/* Right justअगरied */
	हाल SND_SOC_DAIFMT_LSB:
		frcr |= SAI_XFRCR_FSPOL | SAI_XFRCR_FSDEF;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_A:
		frcr |= SAI_XFRCR_FSPOL | SAI_XFRCR_FSOFF;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_B:
		frcr |= SAI_XFRCR_FSPOL;
		अवरोध;
	शेष:
		dev_err(cpu_dai->dev, "Unsupported protocol %#x\n",
			fmt & SND_SOC_DAIFMT_FORMAT_MASK);
		वापस -EINVAL;
	पूर्ण

	cr1_mask |= SAI_XCR1_CKSTR;
	frcr_mask |= SAI_XFRCR_FSPOL | SAI_XFRCR_FSOFF |
		     SAI_XFRCR_FSDEF;

	/* DAI घड़ी strobing. Invert setting previously set */
	चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
	हाल SND_SOC_DAIFMT_NB_NF:
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_NF:
		cr1 ^= SAI_XCR1_CKSTR;
		अवरोध;
	हाल SND_SOC_DAIFMT_NB_IF:
		frcr ^= SAI_XFRCR_FSPOL;
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_IF:
		/* Invert fs & sck */
		cr1 ^= SAI_XCR1_CKSTR;
		frcr ^= SAI_XFRCR_FSPOL;
		अवरोध;
	शेष:
		dev_err(cpu_dai->dev, "Unsupported strobing %#x\n",
			fmt & SND_SOC_DAIFMT_INV_MASK);
		वापस -EINVAL;
	पूर्ण
	cr1_mask |= SAI_XCR1_CKSTR;
	frcr_mask |= SAI_XFRCR_FSPOL;

	sपंचांग32_sai_sub_reg_up(sai, STM_SAI_FRCR_REGX, frcr_mask, frcr);

	/* DAI घड़ी master masks */
	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBM_CFM:
		/* codec is master */
		cr1 |= SAI_XCR1_SLAVE;
		sai->master = false;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBS_CFS:
		sai->master = true;
		अवरोध;
	शेष:
		dev_err(cpu_dai->dev, "Unsupported mode %#x\n",
			fmt & SND_SOC_DAIFMT_MASTER_MASK);
		वापस -EINVAL;
	पूर्ण

	/* Set slave mode अगर sub-block is synchronized with another SAI */
	अगर (sai->sync) अणु
		dev_dbg(cpu_dai->dev, "Synchronized SAI configured as slave\n");
		cr1 |= SAI_XCR1_SLAVE;
		sai->master = false;
	पूर्ण

	cr1_mask |= SAI_XCR1_SLAVE;

conf_update:
	ret = sपंचांग32_sai_sub_reg_up(sai, STM_SAI_CR1_REGX, cr1_mask, cr1);
	अगर (ret < 0) अणु
		dev_err(cpu_dai->dev, "Failed to update CR1 register\n");
		वापस ret;
	पूर्ण

	sai->fmt = fmt;

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_sai_startup(काष्ठा snd_pcm_substream *substream,
			     काष्ठा snd_soc_dai *cpu_dai)
अणु
	काष्ठा sपंचांग32_sai_sub_data *sai = snd_soc_dai_get_drvdata(cpu_dai);
	पूर्णांक imr, cr2, ret;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&sai->irq_lock, flags);
	sai->substream = substream;
	spin_unlock_irqrestore(&sai->irq_lock, flags);

	अगर (STM_SAI_PROTOCOL_IS_SPDIF(sai)) अणु
		snd_pcm_hw_स्थिरraपूर्णांक_mask64(substream->runसमय,
					     SNDRV_PCM_HW_PARAM_FORMAT,
					     SNDRV_PCM_FMTBIT_S32_LE);
		snd_pcm_hw_स्थिरraपूर्णांक_single(substream->runसमय,
					     SNDRV_PCM_HW_PARAM_CHANNELS, 2);
	पूर्ण

	ret = clk_prepare_enable(sai->sai_ck);
	अगर (ret < 0) अणु
		dev_err(cpu_dai->dev, "Failed to enable clock: %d\n", ret);
		वापस ret;
	पूर्ण

	/* Enable ITs */
	sपंचांग32_sai_sub_reg_wr(sai, STM_SAI_CLRFR_REGX,
			     SAI_XCLRFR_MASK, SAI_XCLRFR_MASK);

	imr = SAI_XIMR_OVRUDRIE;
	अगर (STM_SAI_IS_CAPTURE(sai)) अणु
		sपंचांग32_sai_sub_reg_rd(sai, STM_SAI_CR2_REGX, &cr2);
		अगर (cr2 & SAI_XCR2_MUTECNT_MASK)
			imr |= SAI_XIMR_MUTEDETIE;
	पूर्ण

	अगर (sai->master)
		imr |= SAI_XIMR_WCKCFGIE;
	अन्यथा
		imr |= SAI_XIMR_AFSDETIE | SAI_XIMR_LFSDETIE;

	sपंचांग32_sai_sub_reg_up(sai, STM_SAI_IMR_REGX,
			     SAI_XIMR_MASK, imr);

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_sai_set_config(काष्ठा snd_soc_dai *cpu_dai,
				काष्ठा snd_pcm_substream *substream,
				काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा sपंचांग32_sai_sub_data *sai = snd_soc_dai_get_drvdata(cpu_dai);
	पूर्णांक cr1, cr1_mask, ret;

	/*
	 * DMA bursts increment is set to 4 words.
	 * SAI fअगरo threshold is set to half fअगरo, to keep enough space
	 * क्रम DMA incoming bursts.
	 */
	sपंचांग32_sai_sub_reg_wr(sai, STM_SAI_CR2_REGX,
			     SAI_XCR2_FFLUSH | SAI_XCR2_FTH_MASK,
			     SAI_XCR2_FFLUSH |
			     SAI_XCR2_FTH_SET(STM_SAI_FIFO_TH_HALF));

	/* DS bits in CR1 not set क्रम SPDIF (size क्रमced to 24 bits).*/
	अगर (STM_SAI_PROTOCOL_IS_SPDIF(sai)) अणु
		sai->spdअगर_frm_cnt = 0;
		वापस 0;
	पूर्ण

	/* Mode, data क्रमmat and channel config */
	cr1_mask = SAI_XCR1_DS_MASK;
	चयन (params_क्रमmat(params)) अणु
	हाल SNDRV_PCM_FORMAT_S8:
		cr1 = SAI_XCR1_DS_SET(SAI_DATASIZE_8);
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S16_LE:
		cr1 = SAI_XCR1_DS_SET(SAI_DATASIZE_16);
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S32_LE:
		cr1 = SAI_XCR1_DS_SET(SAI_DATASIZE_32);
		अवरोध;
	शेष:
		dev_err(cpu_dai->dev, "Data format not supported\n");
		वापस -EINVAL;
	पूर्ण

	cr1_mask |= SAI_XCR1_MONO;
	अगर ((sai->slots == 2) && (params_channels(params) == 1))
		cr1 |= SAI_XCR1_MONO;

	ret = sपंचांग32_sai_sub_reg_up(sai, STM_SAI_CR1_REGX, cr1_mask, cr1);
	अगर (ret < 0) अणु
		dev_err(cpu_dai->dev, "Failed to update CR1 register\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_sai_set_slots(काष्ठा snd_soc_dai *cpu_dai)
अणु
	काष्ठा sपंचांग32_sai_sub_data *sai = snd_soc_dai_get_drvdata(cpu_dai);
	पूर्णांक slotr, slot_sz;

	sपंचांग32_sai_sub_reg_rd(sai, STM_SAI_SLOTR_REGX, &slotr);

	/*
	 * If SLOTSZ is set to स्वतः in SLOTR, align slot width on data size
	 * By शेष slot width = data size, अगर not क्रमced from DT
	 */
	slot_sz = slotr & SAI_XSLOTR_SLOTSZ_MASK;
	अगर (slot_sz == SAI_XSLOTR_SLOTSZ_SET(SAI_SLOT_SIZE_AUTO))
		sai->slot_width = sai->data_size;

	अगर (sai->slot_width < sai->data_size) अणु
		dev_err(cpu_dai->dev,
			"Data size %d larger than slot width\n",
			sai->data_size);
		वापस -EINVAL;
	पूर्ण

	/* Slot number is set to 2, अगर not specअगरied in DT */
	अगर (!sai->slots)
		sai->slots = 2;

	/* The number of slots in the audio frame is equal to NBSLOT[3:0] + 1*/
	sपंचांग32_sai_sub_reg_up(sai, STM_SAI_SLOTR_REGX,
			     SAI_XSLOTR_NBSLOT_MASK,
			     SAI_XSLOTR_NBSLOT_SET((sai->slots - 1)));

	/* Set शेष slots mask अगर not alपढ़ोy set from DT */
	अगर (!(slotr & SAI_XSLOTR_SLOTEN_MASK)) अणु
		sai->slot_mask = (1 << sai->slots) - 1;
		sपंचांग32_sai_sub_reg_up(sai,
				     STM_SAI_SLOTR_REGX, SAI_XSLOTR_SLOTEN_MASK,
				     SAI_XSLOTR_SLOTEN_SET(sai->slot_mask));
	पूर्ण

	dev_dbg(cpu_dai->dev, "Slots %d, slot width %d\n",
		sai->slots, sai->slot_width);

	वापस 0;
पूर्ण

अटल व्योम sपंचांग32_sai_set_frame(काष्ठा snd_soc_dai *cpu_dai)
अणु
	काष्ठा sपंचांग32_sai_sub_data *sai = snd_soc_dai_get_drvdata(cpu_dai);
	पूर्णांक fs_active, offset, क्रमmat;
	पूर्णांक frcr, frcr_mask;

	क्रमmat = sai->fmt & SND_SOC_DAIFMT_FORMAT_MASK;
	sai->fs_length = sai->slot_width * sai->slots;

	fs_active = sai->fs_length / 2;
	अगर ((क्रमmat == SND_SOC_DAIFMT_DSP_A) ||
	    (क्रमmat == SND_SOC_DAIFMT_DSP_B))
		fs_active = 1;

	frcr = SAI_XFRCR_FRL_SET((sai->fs_length - 1));
	frcr |= SAI_XFRCR_FSALL_SET((fs_active - 1));
	frcr_mask = SAI_XFRCR_FRL_MASK | SAI_XFRCR_FSALL_MASK;

	dev_dbg(cpu_dai->dev, "Frame length %d, frame active %d\n",
		sai->fs_length, fs_active);

	sपंचांग32_sai_sub_reg_up(sai, STM_SAI_FRCR_REGX, frcr_mask, frcr);

	अगर ((sai->fmt & SND_SOC_DAIFMT_FORMAT_MASK) == SND_SOC_DAIFMT_LSB) अणु
		offset = sai->slot_width - sai->data_size;

		sपंचांग32_sai_sub_reg_up(sai, STM_SAI_SLOTR_REGX,
				     SAI_XSLOTR_FBOFF_MASK,
				     SAI_XSLOTR_FBOFF_SET(offset));
	पूर्ण
पूर्ण

अटल व्योम sपंचांग32_sai_init_iec958_status(काष्ठा sपंचांग32_sai_sub_data *sai)
अणु
	अचिन्हित अक्षर *cs = sai->iec958.status;

	cs[0] = IEC958_AES0_CON_NOT_COPYRIGHT | IEC958_AES0_CON_EMPHASIS_NONE;
	cs[1] = IEC958_AES1_CON_GENERAL;
	cs[2] = IEC958_AES2_CON_SOURCE_UNSPEC | IEC958_AES2_CON_CHANNEL_UNSPEC;
	cs[3] = IEC958_AES3_CON_CLOCK_1000PPM | IEC958_AES3_CON_FS_NOTID;
पूर्ण

अटल व्योम sपंचांग32_sai_set_iec958_status(काष्ठा sपंचांग32_sai_sub_data *sai,
					काष्ठा snd_pcm_runसमय *runसमय)
अणु
	अगर (!runसमय)
		वापस;

	/* Force the sample rate according to runसमय rate */
	mutex_lock(&sai->ctrl_lock);
	चयन (runसमय->rate) अणु
	हाल 22050:
		sai->iec958.status[3] = IEC958_AES3_CON_FS_22050;
		अवरोध;
	हाल 44100:
		sai->iec958.status[3] = IEC958_AES3_CON_FS_44100;
		अवरोध;
	हाल 88200:
		sai->iec958.status[3] = IEC958_AES3_CON_FS_88200;
		अवरोध;
	हाल 176400:
		sai->iec958.status[3] = IEC958_AES3_CON_FS_176400;
		अवरोध;
	हाल 24000:
		sai->iec958.status[3] = IEC958_AES3_CON_FS_24000;
		अवरोध;
	हाल 48000:
		sai->iec958.status[3] = IEC958_AES3_CON_FS_48000;
		अवरोध;
	हाल 96000:
		sai->iec958.status[3] = IEC958_AES3_CON_FS_96000;
		अवरोध;
	हाल 192000:
		sai->iec958.status[3] = IEC958_AES3_CON_FS_192000;
		अवरोध;
	हाल 32000:
		sai->iec958.status[3] = IEC958_AES3_CON_FS_32000;
		अवरोध;
	शेष:
		sai->iec958.status[3] = IEC958_AES3_CON_FS_NOTID;
		अवरोध;
	पूर्ण
	mutex_unlock(&sai->ctrl_lock);
पूर्ण

अटल पूर्णांक sपंचांग32_sai_configure_घड़ी(काष्ठा snd_soc_dai *cpu_dai,
				     काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा sपंचांग32_sai_sub_data *sai = snd_soc_dai_get_drvdata(cpu_dai);
	पूर्णांक भाग = 0, cr1 = 0;
	पूर्णांक sai_clk_rate, mclk_ratio, den;
	अचिन्हित पूर्णांक rate = params_rate(params);
	पूर्णांक ret;

	अगर (!sai->sai_mclk) अणु
		ret = sपंचांग32_sai_set_parent_घड़ी(sai, rate);
		अगर (ret)
			वापस ret;
	पूर्ण
	sai_clk_rate = clk_get_rate(sai->sai_ck);

	अगर (STM_SAI_IS_F4(sai->pdata)) अणु
		/* mclk on (NODIV=0)
		 *   mclk_rate = 256 * fs
		 *   MCKDIV = 0 अगर sai_ck < 3/2 * mclk_rate
		 *   MCKDIV = sai_ck / (2 * mclk_rate) otherwise
		 * mclk off (NODIV=1)
		 *   MCKDIV ignored. sck = sai_ck
		 */
		अगर (!sai->mclk_rate)
			वापस 0;

		अगर (2 * sai_clk_rate >= 3 * sai->mclk_rate) अणु
			भाग = sपंचांग32_sai_get_clk_भाग(sai, sai_clk_rate,
						    2 * sai->mclk_rate);
			अगर (भाग < 0)
				वापस भाग;
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * TDM mode :
		 *   mclk on
		 *      MCKDIV = sai_ck / (ws x 256)	(NOMCK=0. OSR=0)
		 *      MCKDIV = sai_ck / (ws x 512)	(NOMCK=0. OSR=1)
		 *   mclk off
		 *      MCKDIV = sai_ck / (frl x ws)	(NOMCK=1)
		 * Note: NOMCK/NODIV correspond to same bit.
		 */
		अगर (STM_SAI_PROTOCOL_IS_SPDIF(sai)) अणु
			भाग = sपंचांग32_sai_get_clk_भाग(sai, sai_clk_rate,
						    rate * 128);
			अगर (भाग < 0)
				वापस भाग;
		पूर्ण अन्यथा अणु
			अगर (sai->mclk_rate) अणु
				mclk_ratio = sai->mclk_rate / rate;
				अगर (mclk_ratio == 512) अणु
					cr1 = SAI_XCR1_OSR;
				पूर्ण अन्यथा अगर (mclk_ratio != 256) अणु
					dev_err(cpu_dai->dev,
						"Wrong mclk ratio %d\n",
						mclk_ratio);
					वापस -EINVAL;
				पूर्ण

				sपंचांग32_sai_sub_reg_up(sai,
						     STM_SAI_CR1_REGX,
						     SAI_XCR1_OSR, cr1);

				भाग = sपंचांग32_sai_get_clk_भाग(sai, sai_clk_rate,
							    sai->mclk_rate);
				अगर (भाग < 0)
					वापस भाग;
			पूर्ण अन्यथा अणु
				/* mclk-fs not set, master घड़ी not active */
				den = sai->fs_length * params_rate(params);
				भाग = sपंचांग32_sai_get_clk_भाग(sai, sai_clk_rate,
							    den);
				अगर (भाग < 0)
					वापस भाग;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस sपंचांग32_sai_set_clk_भाग(sai, भाग);
पूर्ण

अटल पूर्णांक sपंचांग32_sai_hw_params(काष्ठा snd_pcm_substream *substream,
			       काष्ठा snd_pcm_hw_params *params,
			       काष्ठा snd_soc_dai *cpu_dai)
अणु
	काष्ठा sपंचांग32_sai_sub_data *sai = snd_soc_dai_get_drvdata(cpu_dai);
	पूर्णांक ret;

	sai->data_size = params_width(params);

	अगर (STM_SAI_PROTOCOL_IS_SPDIF(sai)) अणु
		/* Rate not alपढ़ोy set in runसमय काष्ठाure */
		substream->runसमय->rate = params_rate(params);
		sपंचांग32_sai_set_iec958_status(sai, substream->runसमय);
	पूर्ण अन्यथा अणु
		ret = sपंचांग32_sai_set_slots(cpu_dai);
		अगर (ret < 0)
			वापस ret;
		sपंचांग32_sai_set_frame(cpu_dai);
	पूर्ण

	ret = sपंचांग32_sai_set_config(cpu_dai, substream, params);
	अगर (ret)
		वापस ret;

	अगर (sai->master)
		ret = sपंचांग32_sai_configure_घड़ी(cpu_dai, params);

	वापस ret;
पूर्ण

अटल पूर्णांक sपंचांग32_sai_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd,
			     काष्ठा snd_soc_dai *cpu_dai)
अणु
	काष्ठा sपंचांग32_sai_sub_data *sai = snd_soc_dai_get_drvdata(cpu_dai);
	पूर्णांक ret;

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_RESUME:
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		dev_dbg(cpu_dai->dev, "Enable DMA and SAI\n");

		sपंचांग32_sai_sub_reg_up(sai, STM_SAI_CR1_REGX,
				     SAI_XCR1_DMAEN, SAI_XCR1_DMAEN);

		/* Enable SAI */
		ret = sपंचांग32_sai_sub_reg_up(sai, STM_SAI_CR1_REGX,
					   SAI_XCR1_SAIEN, SAI_XCR1_SAIEN);
		अगर (ret < 0)
			dev_err(cpu_dai->dev, "Failed to update CR1 register\n");
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
	हाल SNDRV_PCM_TRIGGER_STOP:
		dev_dbg(cpu_dai->dev, "Disable DMA and SAI\n");

		sपंचांग32_sai_sub_reg_up(sai, STM_SAI_IMR_REGX,
				     SAI_XIMR_MASK, 0);

		sपंचांग32_sai_sub_reg_up(sai, STM_SAI_CR1_REGX,
				     SAI_XCR1_SAIEN,
				     (अचिन्हित पूर्णांक)~SAI_XCR1_SAIEN);

		ret = sपंचांग32_sai_sub_reg_up(sai, STM_SAI_CR1_REGX,
					   SAI_XCR1_DMAEN,
					   (अचिन्हित पूर्णांक)~SAI_XCR1_DMAEN);
		अगर (ret < 0)
			dev_err(cpu_dai->dev, "Failed to update CR1 register\n");

		अगर (STM_SAI_PROTOCOL_IS_SPDIF(sai))
			sai->spdअगर_frm_cnt = 0;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम sपंचांग32_sai_shutकरोwn(काष्ठा snd_pcm_substream *substream,
			       काष्ठा snd_soc_dai *cpu_dai)
अणु
	काष्ठा sपंचांग32_sai_sub_data *sai = snd_soc_dai_get_drvdata(cpu_dai);
	अचिन्हित दीर्घ flags;

	sपंचांग32_sai_sub_reg_up(sai, STM_SAI_IMR_REGX, SAI_XIMR_MASK, 0);

	clk_disable_unprepare(sai->sai_ck);

	spin_lock_irqsave(&sai->irq_lock, flags);
	sai->substream = शून्य;
	spin_unlock_irqrestore(&sai->irq_lock, flags);
पूर्ण

अटल पूर्णांक sपंचांग32_sai_pcm_new(काष्ठा snd_soc_pcm_runसमय *rtd,
			     काष्ठा snd_soc_dai *cpu_dai)
अणु
	काष्ठा sपंचांग32_sai_sub_data *sai = dev_get_drvdata(cpu_dai->dev);
	काष्ठा snd_kcontrol_new knew = iec958_ctls;

	अगर (STM_SAI_PROTOCOL_IS_SPDIF(sai)) अणु
		dev_dbg(&sai->pdev->dev, "%s: register iec controls", __func__);
		knew.device = rtd->pcm->device;
		वापस snd_ctl_add(rtd->pcm->card, snd_ctl_new1(&knew, sai));
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_sai_dai_probe(काष्ठा snd_soc_dai *cpu_dai)
अणु
	काष्ठा sपंचांग32_sai_sub_data *sai = dev_get_drvdata(cpu_dai->dev);
	पूर्णांक cr1 = 0, cr1_mask, ret;

	sai->cpu_dai = cpu_dai;

	sai->dma_params.addr = (dma_addr_t)(sai->phys_addr + STM_SAI_DR_REGX);
	/*
	 * DMA supports 4, 8 or 16 burst sizes. Burst size 4 is the best choice,
	 * as it allows bytes, half-word and words transfers. (See DMA fअगरos
	 * स्थिरraपूर्णांकs).
	 */
	sai->dma_params.maxburst = 4;
	अगर (sai->pdata->conf.fअगरo_size < 8)
		sai->dma_params.maxburst = 1;
	/* Buswidth will be set by framework at runसमय */
	sai->dma_params.addr_width = DMA_SLAVE_BUSWIDTH_UNDEFINED;

	अगर (STM_SAI_IS_PLAYBACK(sai))
		snd_soc_dai_init_dma_data(cpu_dai, &sai->dma_params, शून्य);
	अन्यथा
		snd_soc_dai_init_dma_data(cpu_dai, शून्य, &sai->dma_params);

	/* Next settings are not relevant क्रम spdअगर mode */
	अगर (STM_SAI_PROTOCOL_IS_SPDIF(sai))
		वापस 0;

	cr1_mask = SAI_XCR1_RX_TX;
	अगर (STM_SAI_IS_CAPTURE(sai))
		cr1 |= SAI_XCR1_RX_TX;

	/* Configure synchronization */
	अगर (sai->sync == SAI_SYNC_EXTERNAL) अणु
		/* Configure synchro client and provider */
		ret = sai->pdata->set_sync(sai->pdata, sai->np_sync_provider,
					   sai->synco, sai->synci);
		अगर (ret)
			वापस ret;
	पूर्ण

	cr1_mask |= SAI_XCR1_SYNCEN_MASK;
	cr1 |= SAI_XCR1_SYNCEN_SET(sai->sync);

	वापस sपंचांग32_sai_sub_reg_up(sai, STM_SAI_CR1_REGX, cr1_mask, cr1);
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops sपंचांग32_sai_pcm_dai_ops = अणु
	.set_sysclk	= sपंचांग32_sai_set_sysclk,
	.set_fmt	= sपंचांग32_sai_set_dai_fmt,
	.set_tdm_slot	= sपंचांग32_sai_set_dai_tdm_slot,
	.startup	= sपंचांग32_sai_startup,
	.hw_params	= sपंचांग32_sai_hw_params,
	.trigger	= sपंचांग32_sai_trigger,
	.shutकरोwn	= sपंचांग32_sai_shutकरोwn,
पूर्ण;

अटल पूर्णांक sपंचांग32_sai_pcm_process_spdअगर(काष्ठा snd_pcm_substream *substream,
				       पूर्णांक channel, अचिन्हित दीर्घ hwoff,
				       व्योम *buf, अचिन्हित दीर्घ bytes)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_dai *cpu_dai = asoc_rtd_to_cpu(rtd, 0);
	काष्ठा sपंचांग32_sai_sub_data *sai = dev_get_drvdata(cpu_dai->dev);
	पूर्णांक *ptr = (पूर्णांक *)(runसमय->dma_area + hwoff +
			   channel * (runसमय->dma_bytes / runसमय->channels));
	sमाप_प्रकार cnt = bytes_to_samples(runसमय, bytes);
	अचिन्हित पूर्णांक frm_cnt = sai->spdअगर_frm_cnt;
	अचिन्हित पूर्णांक byte;
	अचिन्हित पूर्णांक mask;

	करो अणु
		*ptr = ((*ptr >> 8) & 0x00ffffff);

		/* Set channel status bit */
		byte = frm_cnt >> 3;
		mask = 1 << (frm_cnt - (byte << 3));
		अगर (sai->iec958.status[byte] & mask)
			*ptr |= 0x04000000;
		ptr++;

		अगर (!(cnt % 2))
			frm_cnt++;

		अगर (frm_cnt == SAI_IEC60958_BLOCK_FRAMES)
			frm_cnt = 0;
	पूर्ण जबतक (--cnt);
	sai->spdअगर_frm_cnt = frm_cnt;

	वापस 0;
पूर्ण

/* No support of mmap in S/PDIF mode */
अटल स्थिर काष्ठा snd_pcm_hardware sपंचांग32_sai_pcm_hw_spdअगर = अणु
	.info = SNDRV_PCM_INFO_INTERLEAVED,
	.buffer_bytes_max = 8 * PAGE_SIZE,
	.period_bytes_min = 1024,
	.period_bytes_max = PAGE_SIZE,
	.periods_min = 2,
	.periods_max = 8,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hardware sपंचांग32_sai_pcm_hw = अणु
	.info = SNDRV_PCM_INFO_INTERLEAVED | SNDRV_PCM_INFO_MMAP,
	.buffer_bytes_max = 8 * PAGE_SIZE,
	.period_bytes_min = 1024, /* 5ms at 48kHz */
	.period_bytes_max = PAGE_SIZE,
	.periods_min = 2,
	.periods_max = 8,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver sपंचांग32_sai_playback_dai = अणु
		.probe = sपंचांग32_sai_dai_probe,
		.pcm_new = sपंचांग32_sai_pcm_new,
		.id = 1, /* aव्योम call to fmt_single_name() */
		.playback = अणु
			.channels_min = 1,
			.channels_max = 2,
			.rate_min = 8000,
			.rate_max = 192000,
			.rates = SNDRV_PCM_RATE_CONTINUOUS,
			/* DMA करोes not support 24 bits transfers */
			.क्रमmats =
				SNDRV_PCM_FMTBIT_S8 |
				SNDRV_PCM_FMTBIT_S16_LE |
				SNDRV_PCM_FMTBIT_S32_LE,
		पूर्ण,
		.ops = &sपंचांग32_sai_pcm_dai_ops,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver sपंचांग32_sai_capture_dai = अणु
		.probe = sपंचांग32_sai_dai_probe,
		.id = 1, /* aव्योम call to fmt_single_name() */
		.capture = अणु
			.channels_min = 1,
			.channels_max = 2,
			.rate_min = 8000,
			.rate_max = 192000,
			.rates = SNDRV_PCM_RATE_CONTINUOUS,
			/* DMA करोes not support 24 bits transfers */
			.क्रमmats =
				SNDRV_PCM_FMTBIT_S8 |
				SNDRV_PCM_FMTBIT_S16_LE |
				SNDRV_PCM_FMTBIT_S32_LE,
		पूर्ण,
		.ops = &sपंचांग32_sai_pcm_dai_ops,
पूर्ण;

अटल स्थिर काष्ठा snd_dmaengine_pcm_config sपंचांग32_sai_pcm_config = अणु
	.pcm_hardware = &sपंचांग32_sai_pcm_hw,
	.prepare_slave_config = snd_dmaengine_pcm_prepare_slave_config,
पूर्ण;

अटल स्थिर काष्ठा snd_dmaengine_pcm_config sपंचांग32_sai_pcm_config_spdअगर = अणु
	.pcm_hardware = &sपंचांग32_sai_pcm_hw_spdअगर,
	.prepare_slave_config = snd_dmaengine_pcm_prepare_slave_config,
	.process = sपंचांग32_sai_pcm_process_spdअगर,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver sपंचांग32_component = अणु
	.name = "stm32-sai",
पूर्ण;

अटल स्थिर काष्ठा of_device_id sपंचांग32_sai_sub_ids[] = अणु
	अणु .compatible = "st,stm32-sai-sub-a",
	  .data = (व्योम *)STM_SAI_A_IDपूर्ण,
	अणु .compatible = "st,stm32-sai-sub-b",
	  .data = (व्योम *)STM_SAI_B_IDपूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, sपंचांग32_sai_sub_ids);

अटल पूर्णांक sपंचांग32_sai_sub_parse_of(काष्ठा platक्रमm_device *pdev,
				  काष्ठा sपंचांग32_sai_sub_data *sai)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा resource *res;
	व्योम __iomem *base;
	काष्ठा of_phandle_args args;
	पूर्णांक ret;

	अगर (!np)
		वापस -ENODEV;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	sai->phys_addr = res->start;

	sai->regmap_config = &sपंचांग32_sai_sub_regmap_config_f4;
	/* Note: PDM रेजिस्टरs not available क्रम sub-block B */
	अगर (STM_SAI_HAS_PDM(sai) && STM_SAI_IS_SUB_A(sai))
		sai->regmap_config = &sपंचांग32_sai_sub_regmap_config_h7;

	/*
	 * Do not manage peripheral घड़ी through regmap framework as this
	 * can lead to circular locking issue with sai master घड़ी provider.
	 * Manage peripheral घड़ी directly in driver instead.
	 */
	sai->regmap = devm_regmap_init_mmio(&pdev->dev, base,
					    sai->regmap_config);
	अगर (IS_ERR(sai->regmap)) अणु
		अगर (PTR_ERR(sai->regmap) != -EPROBE_DEFER)
			dev_err(&pdev->dev, "Regmap init error %ld\n",
				PTR_ERR(sai->regmap));
		वापस PTR_ERR(sai->regmap);
	पूर्ण

	/* Get direction property */
	अगर (of_property_match_string(np, "dma-names", "tx") >= 0) अणु
		sai->dir = SNDRV_PCM_STREAM_PLAYBACK;
	पूर्ण अन्यथा अगर (of_property_match_string(np, "dma-names", "rx") >= 0) अणु
		sai->dir = SNDRV_PCM_STREAM_CAPTURE;
	पूर्ण अन्यथा अणु
		dev_err(&pdev->dev, "Unsupported direction\n");
		वापस -EINVAL;
	पूर्ण

	/* Get spdअगर iec60958 property */
	sai->spdअगर = false;
	अगर (of_get_property(np, "st,iec60958", शून्य)) अणु
		अगर (!STM_SAI_HAS_SPDIF(sai) ||
		    sai->dir == SNDRV_PCM_STREAM_CAPTURE) अणु
			dev_err(&pdev->dev, "S/PDIF IEC60958 not supported\n");
			वापस -EINVAL;
		पूर्ण
		sपंचांग32_sai_init_iec958_status(sai);
		sai->spdअगर = true;
		sai->master = true;
	पूर्ण

	/* Get synchronization property */
	args.np = शून्य;
	ret = of_parse_phandle_with_fixed_args(np, "st,sync", 1, 0, &args);
	अगर (ret < 0  && ret != -ENOENT) अणु
		dev_err(&pdev->dev, "Failed to get st,sync property\n");
		वापस ret;
	पूर्ण

	sai->sync = SAI_SYNC_NONE;
	अगर (args.np) अणु
		अगर (args.np == np) अणु
			dev_err(&pdev->dev, "%pOFn sync own reference\n", np);
			of_node_put(args.np);
			वापस -EINVAL;
		पूर्ण

		sai->np_sync_provider  = of_get_parent(args.np);
		अगर (!sai->np_sync_provider) अणु
			dev_err(&pdev->dev, "%pOFn parent node not found\n",
				np);
			of_node_put(args.np);
			वापस -ENODEV;
		पूर्ण

		sai->sync = SAI_SYNC_INTERNAL;
		अगर (sai->np_sync_provider != sai->pdata->pdev->dev.of_node) अणु
			अगर (!STM_SAI_HAS_EXT_SYNC(sai)) अणु
				dev_err(&pdev->dev,
					"External synchro not supported\n");
				of_node_put(args.np);
				वापस -EINVAL;
			पूर्ण
			sai->sync = SAI_SYNC_EXTERNAL;

			sai->synci = args.args[0];
			अगर (sai->synci < 1 ||
			    (sai->synci > (SAI_GCR_SYNCIN_MAX + 1))) अणु
				dev_err(&pdev->dev, "Wrong SAI index\n");
				of_node_put(args.np);
				वापस -EINVAL;
			पूर्ण

			अगर (of_property_match_string(args.np, "compatible",
						     "st,stm32-sai-sub-a") >= 0)
				sai->synco = STM_SAI_SYNC_OUT_A;

			अगर (of_property_match_string(args.np, "compatible",
						     "st,stm32-sai-sub-b") >= 0)
				sai->synco = STM_SAI_SYNC_OUT_B;

			अगर (!sai->synco) अणु
				dev_err(&pdev->dev, "Unknown SAI sub-block\n");
				of_node_put(args.np);
				वापस -EINVAL;
			पूर्ण
		पूर्ण

		dev_dbg(&pdev->dev, "%s synchronized with %s\n",
			pdev->name, args.np->full_name);
	पूर्ण

	of_node_put(args.np);
	sai->sai_ck = devm_clk_get(&pdev->dev, "sai_ck");
	अगर (IS_ERR(sai->sai_ck)) अणु
		अगर (PTR_ERR(sai->sai_ck) != -EPROBE_DEFER)
			dev_err(&pdev->dev, "Missing kernel clock sai_ck: %ld\n",
				PTR_ERR(sai->sai_ck));
		वापस PTR_ERR(sai->sai_ck);
	पूर्ण

	ret = clk_prepare(sai->pdata->pclk);
	अगर (ret < 0)
		वापस ret;

	अगर (STM_SAI_IS_F4(sai->pdata))
		वापस 0;

	/* Register mclk provider अगर requested */
	अगर (of_find_property(np, "#clock-cells", शून्य)) अणु
		ret = sपंचांग32_sai_add_mclk_provider(sai);
		अगर (ret < 0)
			वापस ret;
	पूर्ण अन्यथा अणु
		sai->sai_mclk = devm_clk_get(&pdev->dev, "MCLK");
		अगर (IS_ERR(sai->sai_mclk)) अणु
			अगर (PTR_ERR(sai->sai_mclk) != -ENOENT)
				वापस PTR_ERR(sai->sai_mclk);
			sai->sai_mclk = शून्य;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_sai_sub_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sपंचांग32_sai_sub_data *sai;
	स्थिर काष्ठा of_device_id *of_id;
	स्थिर काष्ठा snd_dmaengine_pcm_config *conf = &sपंचांग32_sai_pcm_config;
	पूर्णांक ret;

	sai = devm_kzalloc(&pdev->dev, माप(*sai), GFP_KERNEL);
	अगर (!sai)
		वापस -ENOMEM;

	of_id = of_match_device(sपंचांग32_sai_sub_ids, &pdev->dev);
	अगर (!of_id)
		वापस -EINVAL;
	sai->id = (uपूर्णांकptr_t)of_id->data;

	sai->pdev = pdev;
	mutex_init(&sai->ctrl_lock);
	spin_lock_init(&sai->irq_lock);
	platक्रमm_set_drvdata(pdev, sai);

	sai->pdata = dev_get_drvdata(pdev->dev.parent);
	अगर (!sai->pdata) अणु
		dev_err(&pdev->dev, "Parent device data not available\n");
		वापस -EINVAL;
	पूर्ण

	ret = sपंचांग32_sai_sub_parse_of(pdev, sai);
	अगर (ret)
		वापस ret;

	अगर (STM_SAI_IS_PLAYBACK(sai))
		sai->cpu_dai_drv = sपंचांग32_sai_playback_dai;
	अन्यथा
		sai->cpu_dai_drv = sपंचांग32_sai_capture_dai;
	sai->cpu_dai_drv.name = dev_name(&pdev->dev);

	ret = devm_request_irq(&pdev->dev, sai->pdata->irq, sपंचांग32_sai_isr,
			       IRQF_SHARED, dev_name(&pdev->dev), sai);
	अगर (ret) अणु
		dev_err(&pdev->dev, "IRQ request returned %d\n", ret);
		वापस ret;
	पूर्ण

	अगर (STM_SAI_PROTOCOL_IS_SPDIF(sai))
		conf = &sपंचांग32_sai_pcm_config_spdअगर;

	ret = snd_dmaengine_pcm_रेजिस्टर(&pdev->dev, conf, 0);
	अगर (ret) अणु
		अगर (ret != -EPROBE_DEFER)
			dev_err(&pdev->dev, "Could not register pcm dma\n");
		वापस ret;
	पूर्ण

	ret = snd_soc_रेजिस्टर_component(&pdev->dev, &sपंचांग32_component,
					 &sai->cpu_dai_drv, 1);
	अगर (ret) अणु
		snd_dmaengine_pcm_unरेजिस्टर(&pdev->dev);
		वापस ret;
	पूर्ण

	pm_runसमय_enable(&pdev->dev);

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_sai_sub_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sपंचांग32_sai_sub_data *sai = dev_get_drvdata(&pdev->dev);

	clk_unprepare(sai->pdata->pclk);
	snd_dmaengine_pcm_unरेजिस्टर(&pdev->dev);
	snd_soc_unरेजिस्टर_component(&pdev->dev);
	pm_runसमय_disable(&pdev->dev);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक sपंचांग32_sai_sub_suspend(काष्ठा device *dev)
अणु
	काष्ठा sपंचांग32_sai_sub_data *sai = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = clk_enable(sai->pdata->pclk);
	अगर (ret < 0)
		वापस ret;

	regcache_cache_only(sai->regmap, true);
	regcache_mark_dirty(sai->regmap);

	clk_disable(sai->pdata->pclk);

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_sai_sub_resume(काष्ठा device *dev)
अणु
	काष्ठा sपंचांग32_sai_sub_data *sai = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = clk_enable(sai->pdata->pclk);
	अगर (ret < 0)
		वापस ret;

	regcache_cache_only(sai->regmap, false);
	ret = regcache_sync(sai->regmap);

	clk_disable(sai->pdata->pclk);

	वापस ret;
पूर्ण
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

अटल स्थिर काष्ठा dev_pm_ops sपंचांग32_sai_sub_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(sपंचांग32_sai_sub_suspend, sपंचांग32_sai_sub_resume)
पूर्ण;

अटल काष्ठा platक्रमm_driver sपंचांग32_sai_sub_driver = अणु
	.driver = अणु
		.name = "st,stm32-sai-sub",
		.of_match_table = sपंचांग32_sai_sub_ids,
		.pm = &sपंचांग32_sai_sub_pm_ops,
	पूर्ण,
	.probe = sपंचांग32_sai_sub_probe,
	.हटाओ = sपंचांग32_sai_sub_हटाओ,
पूर्ण;

module_platक्रमm_driver(sपंचांग32_sai_sub_driver);

MODULE_DESCRIPTION("STM32 Soc SAI sub-block Interface");
MODULE_AUTHOR("Olivier Moysan <olivier.moysan@st.com>");
MODULE_ALIAS("platform:st,stm32-sai-sub");
MODULE_LICENSE("GPL v2");
