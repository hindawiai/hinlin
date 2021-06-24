<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * IMG SPDIF input controller driver
 *
 * Copyright (C) 2015 Imagination Technologies Ltd.
 *
 * Author: Damien Horsley <Damien.Horsley@imgtec.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/reset.h>

#समावेश <sound/core.h>
#समावेश <sound/dmaengine_pcm.h>
#समावेश <sound/initval.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>

#घोषणा IMG_SPDIF_IN_RX_FIFO_OFFSET		0

#घोषणा IMG_SPDIF_IN_CTL			0x4
#घोषणा IMG_SPDIF_IN_CTL_LOCKLO_MASK		0xff
#घोषणा IMG_SPDIF_IN_CTL_LOCKLO_SHIFT		0
#घोषणा IMG_SPDIF_IN_CTL_LOCKHI_MASK		0xff00
#घोषणा IMG_SPDIF_IN_CTL_LOCKHI_SHIFT		8
#घोषणा IMG_SPDIF_IN_CTL_TRK_MASK		0xff0000
#घोषणा IMG_SPDIF_IN_CTL_TRK_SHIFT		16
#घोषणा IMG_SPDIF_IN_CTL_SRD_MASK		0x70000000
#घोषणा IMG_SPDIF_IN_CTL_SRD_SHIFT		28
#घोषणा IMG_SPDIF_IN_CTL_SRT_MASK		BIT(31)

#घोषणा IMG_SPDIF_IN_STATUS			0x8
#घोषणा IMG_SPDIF_IN_STATUS_SAM_MASK		0x7000
#घोषणा IMG_SPDIF_IN_STATUS_SAM_SHIFT		12
#घोषणा IMG_SPDIF_IN_STATUS_LOCK_MASK		BIT(15)
#घोषणा IMG_SPDIF_IN_STATUS_LOCK_SHIFT		15

#घोषणा IMG_SPDIF_IN_CLKGEN			0x1c
#घोषणा IMG_SPDIF_IN_CLKGEN_NOM_MASK		0x3ff
#घोषणा IMG_SPDIF_IN_CLKGEN_NOM_SHIFT		0
#घोषणा IMG_SPDIF_IN_CLKGEN_HLD_MASK		0x3ff0000
#घोषणा IMG_SPDIF_IN_CLKGEN_HLD_SHIFT		16

#घोषणा IMG_SPDIF_IN_CSL			0x20

#घोषणा IMG_SPDIF_IN_CSH			0x24
#घोषणा IMG_SPDIF_IN_CSH_MASK			0xff
#घोषणा IMG_SPDIF_IN_CSH_SHIFT			0

#घोषणा IMG_SPDIF_IN_SOFT_RESET			0x28
#घोषणा IMG_SPDIF_IN_SOFT_RESET_MASK		BIT(0)

#घोषणा IMG_SPDIF_IN_ACLKGEN_START		0x2c
#घोषणा IMG_SPDIF_IN_ACLKGEN_NOM_MASK		0x3ff
#घोषणा IMG_SPDIF_IN_ACLKGEN_NOM_SHIFT		0
#घोषणा IMG_SPDIF_IN_ACLKGEN_HLD_MASK		0xffc00
#घोषणा IMG_SPDIF_IN_ACLKGEN_HLD_SHIFT		10
#घोषणा IMG_SPDIF_IN_ACLKGEN_TRK_MASK		0xff00000
#घोषणा IMG_SPDIF_IN_ACLKGEN_TRK_SHIFT		20

#घोषणा IMG_SPDIF_IN_NUM_ACLKGEN		4

काष्ठा img_spdअगर_in अणु
	spinlock_t lock;
	व्योम __iomem *base;
	काष्ठा clk *clk_sys;
	काष्ठा snd_dmaengine_dai_dma_data dma_data;
	काष्ठा device *dev;
	अचिन्हित पूर्णांक trk;
	bool multi_freq;
	पूर्णांक lock_acquire;
	पूर्णांक lock_release;
	अचिन्हित पूर्णांक single_freq;
	अचिन्हित पूर्णांक multi_freqs[IMG_SPDIF_IN_NUM_ACLKGEN];
	bool active;
	u32 suspend_clkgen;
	u32 suspend_ctl;

	/* Write-only रेजिस्टरs */
	अचिन्हित पूर्णांक aclkgen_regs[IMG_SPDIF_IN_NUM_ACLKGEN];
पूर्ण;

अटल पूर्णांक img_spdअगर_in_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा img_spdअगर_in *spdअगर = dev_get_drvdata(dev);

	clk_disable_unprepare(spdअगर->clk_sys);

	वापस 0;
पूर्ण

अटल पूर्णांक img_spdअगर_in_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा img_spdअगर_in *spdअगर = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = clk_prepare_enable(spdअगर->clk_sys);
	अगर (ret) अणु
		dev_err(dev, "Unable to enable sys clock\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम img_spdअगर_in_ग_लिखोl(काष्ठा img_spdअगर_in *spdअगर,
					u32 val, u32 reg)
अणु
	ग_लिखोl(val, spdअगर->base + reg);
पूर्ण

अटल अंतरभूत u32 img_spdअगर_in_पढ़ोl(काष्ठा img_spdअगर_in *spdअगर, u32 reg)
अणु
	वापस पढ़ोl(spdअगर->base + reg);
पूर्ण

अटल अंतरभूत व्योम img_spdअगर_in_aclkgen_ग_लिखोl(काष्ठा img_spdअगर_in *spdअगर,
						u32 index)
अणु
	img_spdअगर_in_ग_लिखोl(spdअगर, spdअगर->aclkgen_regs[index],
			IMG_SPDIF_IN_ACLKGEN_START + (index * 0x4));
पूर्ण

अटल पूर्णांक img_spdअगर_in_check_max_rate(काष्ठा img_spdअगर_in *spdअगर,
		अचिन्हित पूर्णांक sample_rate, अचिन्हित दीर्घ *actual_freq)
अणु
	अचिन्हित दीर्घ min_freq, freq_t;

	/* Clock rate must be at least 24x the bit rate */
	min_freq = sample_rate * 2 * 32 * 24;

	freq_t = clk_get_rate(spdअगर->clk_sys);

	अगर (freq_t < min_freq)
		वापस -EINVAL;

	*actual_freq = freq_t;

	वापस 0;
पूर्ण

अटल पूर्णांक img_spdअगर_in_करो_clkgen_calc(अचिन्हित पूर्णांक rate, अचिन्हित पूर्णांक *pnom,
		अचिन्हित पूर्णांक *phld, अचिन्हित दीर्घ clk_rate)
अणु
	अचिन्हित पूर्णांक ori, nom, hld;

	/*
	 * Calculate oversampling ratio, nominal phase increment and hold
	 * increment क्रम the given rate / frequency
	 */

	अगर (!rate)
		वापस -EINVAL;

	ori = clk_rate / (rate * 64);

	अगर (!ori)
		वापस -EINVAL;

	nom = (4096 / ori) + 1;
	करो
		hld = 4096 - (--nom * (ori - 1));
	जबतक (hld < 120);

	*pnom = nom;
	*phld = hld;

	वापस 0;
पूर्ण

अटल पूर्णांक img_spdअगर_in_करो_clkgen_single(काष्ठा img_spdअगर_in *spdअगर,
		अचिन्हित पूर्णांक rate)
अणु
	अचिन्हित पूर्णांक nom, hld;
	अचिन्हित दीर्घ flags, clk_rate;
	पूर्णांक ret = 0;
	u32 reg;

	ret = img_spdअगर_in_check_max_rate(spdअगर, rate, &clk_rate);
	अगर (ret)
		वापस ret;

	ret = img_spdअगर_in_करो_clkgen_calc(rate, &nom, &hld, clk_rate);
	अगर (ret)
		वापस ret;

	reg = (nom << IMG_SPDIF_IN_CLKGEN_NOM_SHIFT) &
		IMG_SPDIF_IN_CLKGEN_NOM_MASK;
	reg |= (hld << IMG_SPDIF_IN_CLKGEN_HLD_SHIFT) &
		IMG_SPDIF_IN_CLKGEN_HLD_MASK;

	spin_lock_irqsave(&spdअगर->lock, flags);

	अगर (spdअगर->active) अणु
		spin_unlock_irqrestore(&spdअगर->lock, flags);
		वापस -EBUSY;
	पूर्ण

	img_spdअगर_in_ग_लिखोl(spdअगर, reg, IMG_SPDIF_IN_CLKGEN);

	spdअगर->single_freq = rate;

	spin_unlock_irqrestore(&spdअगर->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक img_spdअगर_in_करो_clkgen_multi(काष्ठा img_spdअगर_in *spdअगर,
		अचिन्हित पूर्णांक multi_freqs[])
अणु
	अचिन्हित पूर्णांक nom, hld, rate, max_rate = 0;
	अचिन्हित दीर्घ flags, clk_rate;
	पूर्णांक i, ret = 0;
	u32 reg, trk_reg, temp_regs[IMG_SPDIF_IN_NUM_ACLKGEN];

	क्रम (i = 0; i < IMG_SPDIF_IN_NUM_ACLKGEN; i++)
		अगर (multi_freqs[i] > max_rate)
			max_rate = multi_freqs[i];

	ret = img_spdअगर_in_check_max_rate(spdअगर, max_rate, &clk_rate);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < IMG_SPDIF_IN_NUM_ACLKGEN; i++) अणु
		rate = multi_freqs[i];

		ret = img_spdअगर_in_करो_clkgen_calc(rate, &nom, &hld, clk_rate);
		अगर (ret)
			वापस ret;

		reg = (nom << IMG_SPDIF_IN_ACLKGEN_NOM_SHIFT) &
			IMG_SPDIF_IN_ACLKGEN_NOM_MASK;
		reg |= (hld << IMG_SPDIF_IN_ACLKGEN_HLD_SHIFT) &
			IMG_SPDIF_IN_ACLKGEN_HLD_MASK;
		temp_regs[i] = reg;
	पूर्ण

	spin_lock_irqsave(&spdअगर->lock, flags);

	अगर (spdअगर->active) अणु
		spin_unlock_irqrestore(&spdअगर->lock, flags);
		वापस -EBUSY;
	पूर्ण

	trk_reg = spdअगर->trk << IMG_SPDIF_IN_ACLKGEN_TRK_SHIFT;

	क्रम (i = 0; i < IMG_SPDIF_IN_NUM_ACLKGEN; i++) अणु
		spdअगर->aclkgen_regs[i] = temp_regs[i] | trk_reg;
		img_spdअगर_in_aclkgen_ग_लिखोl(spdअगर, i);
	पूर्ण

	spdअगर->multi_freq = true;
	spdअगर->multi_freqs[0] = multi_freqs[0];
	spdअगर->multi_freqs[1] = multi_freqs[1];
	spdअगर->multi_freqs[2] = multi_freqs[2];
	spdअगर->multi_freqs[3] = multi_freqs[3];

	spin_unlock_irqrestore(&spdअगर->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक img_spdअगर_in_iec958_info(काष्ठा snd_kcontrol *kcontrol,
		काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_IEC958;
	uinfo->count = 1;

	वापस 0;
पूर्ण

अटल पूर्णांक img_spdअगर_in_get_status_mask(काष्ठा snd_kcontrol *kcontrol,
				       काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	ucontrol->value.iec958.status[0] = 0xff;
	ucontrol->value.iec958.status[1] = 0xff;
	ucontrol->value.iec958.status[2] = 0xff;
	ucontrol->value.iec958.status[3] = 0xff;
	ucontrol->value.iec958.status[4] = 0xff;

	वापस 0;
पूर्ण

अटल पूर्णांक img_spdअगर_in_get_status(काष्ठा snd_kcontrol *kcontrol,
				  काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_dai *cpu_dai = snd_kcontrol_chip(kcontrol);
	काष्ठा img_spdअगर_in *spdअगर = snd_soc_dai_get_drvdata(cpu_dai);
	u32 reg;

	reg = img_spdअगर_in_पढ़ोl(spdअगर, IMG_SPDIF_IN_CSL);
	ucontrol->value.iec958.status[0] = reg & 0xff;
	ucontrol->value.iec958.status[1] = (reg >> 8) & 0xff;
	ucontrol->value.iec958.status[2] = (reg >> 16) & 0xff;
	ucontrol->value.iec958.status[3] = (reg >> 24) & 0xff;
	reg = img_spdअगर_in_पढ़ोl(spdअगर, IMG_SPDIF_IN_CSH);
	ucontrol->value.iec958.status[4] = (reg & IMG_SPDIF_IN_CSH_MASK)
		>> IMG_SPDIF_IN_CSH_SHIFT;

	वापस 0;
पूर्ण

अटल पूर्णांक img_spdअगर_in_info_multi_freq(काष्ठा snd_kcontrol *kcontrol,
		काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = IMG_SPDIF_IN_NUM_ACLKGEN;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = दीर्घ_उच्च;

	वापस 0;
पूर्ण

अटल पूर्णांक img_spdअगर_in_get_multi_freq(काष्ठा snd_kcontrol *kcontrol,
				  काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_dai *cpu_dai = snd_kcontrol_chip(kcontrol);
	काष्ठा img_spdअगर_in *spdअगर = snd_soc_dai_get_drvdata(cpu_dai);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&spdअगर->lock, flags);
	अगर (spdअगर->multi_freq) अणु
		ucontrol->value.पूर्णांकeger.value[0] = spdअगर->multi_freqs[0];
		ucontrol->value.पूर्णांकeger.value[1] = spdअगर->multi_freqs[1];
		ucontrol->value.पूर्णांकeger.value[2] = spdअगर->multi_freqs[2];
		ucontrol->value.पूर्णांकeger.value[3] = spdअगर->multi_freqs[3];
	पूर्ण अन्यथा अणु
		ucontrol->value.पूर्णांकeger.value[0] = 0;
		ucontrol->value.पूर्णांकeger.value[1] = 0;
		ucontrol->value.पूर्णांकeger.value[2] = 0;
		ucontrol->value.पूर्णांकeger.value[3] = 0;
	पूर्ण
	spin_unlock_irqrestore(&spdअगर->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक img_spdअगर_in_set_multi_freq(काष्ठा snd_kcontrol *kcontrol,
				  काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_dai *cpu_dai = snd_kcontrol_chip(kcontrol);
	काष्ठा img_spdअगर_in *spdअगर = snd_soc_dai_get_drvdata(cpu_dai);
	अचिन्हित पूर्णांक multi_freqs[IMG_SPDIF_IN_NUM_ACLKGEN];
	bool multi_freq;
	अचिन्हित दीर्घ flags;

	अगर ((ucontrol->value.पूर्णांकeger.value[0] == 0) &&
			(ucontrol->value.पूर्णांकeger.value[1] == 0) &&
			(ucontrol->value.पूर्णांकeger.value[2] == 0) &&
			(ucontrol->value.पूर्णांकeger.value[3] == 0)) अणु
		multi_freq = false;
	पूर्ण अन्यथा अणु
		multi_freqs[0] = ucontrol->value.पूर्णांकeger.value[0];
		multi_freqs[1] = ucontrol->value.पूर्णांकeger.value[1];
		multi_freqs[2] = ucontrol->value.पूर्णांकeger.value[2];
		multi_freqs[3] = ucontrol->value.पूर्णांकeger.value[3];
		multi_freq = true;
	पूर्ण

	अगर (multi_freq)
		वापस img_spdअगर_in_करो_clkgen_multi(spdअगर, multi_freqs);

	spin_lock_irqsave(&spdअगर->lock, flags);

	अगर (spdअगर->active) अणु
		spin_unlock_irqrestore(&spdअगर->lock, flags);
		वापस -EBUSY;
	पूर्ण

	spdअगर->multi_freq = false;

	spin_unlock_irqrestore(&spdअगर->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक img_spdअगर_in_info_lock_freq(काष्ठा snd_kcontrol *kcontrol,
		काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 1;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = दीर्घ_उच्च;

	वापस 0;
पूर्ण

अटल पूर्णांक img_spdअगर_in_get_lock_freq(काष्ठा snd_kcontrol *kcontrol,
				  काष्ठा snd_ctl_elem_value *uc)
अणु
	काष्ठा snd_soc_dai *cpu_dai = snd_kcontrol_chip(kcontrol);
	काष्ठा img_spdअगर_in *spdअगर = snd_soc_dai_get_drvdata(cpu_dai);
	u32 reg;
	पूर्णांक i;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&spdअगर->lock, flags);

	reg = img_spdअगर_in_पढ़ोl(spdअगर, IMG_SPDIF_IN_STATUS);
	अगर (reg & IMG_SPDIF_IN_STATUS_LOCK_MASK) अणु
		अगर (spdअगर->multi_freq) अणु
			i = ((reg & IMG_SPDIF_IN_STATUS_SAM_MASK) >>
					IMG_SPDIF_IN_STATUS_SAM_SHIFT) - 1;
			uc->value.पूर्णांकeger.value[0] = spdअगर->multi_freqs[i];
		पूर्ण अन्यथा अणु
			uc->value.पूर्णांकeger.value[0] = spdअगर->single_freq;
		पूर्ण
	पूर्ण अन्यथा अणु
		uc->value.पूर्णांकeger.value[0] = 0;
	पूर्ण

	spin_unlock_irqrestore(&spdअगर->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक img_spdअगर_in_info_trk(काष्ठा snd_kcontrol *kcontrol,
		काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 1;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = 255;

	वापस 0;
पूर्ण

अटल पूर्णांक img_spdअगर_in_get_trk(काष्ठा snd_kcontrol *kcontrol,
				  काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_dai *cpu_dai = snd_kcontrol_chip(kcontrol);
	काष्ठा img_spdअगर_in *spdअगर = snd_soc_dai_get_drvdata(cpu_dai);

	ucontrol->value.पूर्णांकeger.value[0] = spdअगर->trk;

	वापस 0;
पूर्ण

अटल पूर्णांक img_spdअगर_in_set_trk(काष्ठा snd_kcontrol *kcontrol,
				  काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_dai *cpu_dai = snd_kcontrol_chip(kcontrol);
	काष्ठा img_spdअगर_in *spdअगर = snd_soc_dai_get_drvdata(cpu_dai);
	अचिन्हित दीर्घ flags;
	पूर्णांक i;
	u32 reg;

	spin_lock_irqsave(&spdअगर->lock, flags);

	अगर (spdअगर->active) अणु
		spin_unlock_irqrestore(&spdअगर->lock, flags);
		वापस -EBUSY;
	पूर्ण

	spdअगर->trk = ucontrol->value.पूर्णांकeger.value[0];

	reg = img_spdअगर_in_पढ़ोl(spdअगर, IMG_SPDIF_IN_CTL);
	reg &= ~IMG_SPDIF_IN_CTL_TRK_MASK;
	reg |= spdअगर->trk << IMG_SPDIF_IN_CTL_TRK_SHIFT;
	img_spdअगर_in_ग_लिखोl(spdअगर, reg, IMG_SPDIF_IN_CTL);

	क्रम (i = 0; i < IMG_SPDIF_IN_NUM_ACLKGEN; i++) अणु
		spdअगर->aclkgen_regs[i] = (spdअगर->aclkgen_regs[i] &
			~IMG_SPDIF_IN_ACLKGEN_TRK_MASK) |
			(spdअगर->trk << IMG_SPDIF_IN_ACLKGEN_TRK_SHIFT);

		img_spdअगर_in_aclkgen_ग_लिखोl(spdअगर, i);
	पूर्ण

	spin_unlock_irqrestore(&spdअगर->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक img_spdअगर_in_info_lock(काष्ठा snd_kcontrol *kcontrol,
		काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 1;
	uinfo->value.पूर्णांकeger.min = -128;
	uinfo->value.पूर्णांकeger.max = 127;

	वापस 0;
पूर्ण

अटल पूर्णांक img_spdअगर_in_get_lock_acquire(काष्ठा snd_kcontrol *kcontrol,
				  काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_dai *cpu_dai = snd_kcontrol_chip(kcontrol);
	काष्ठा img_spdअगर_in *spdअगर = snd_soc_dai_get_drvdata(cpu_dai);

	ucontrol->value.पूर्णांकeger.value[0] = spdअगर->lock_acquire;

	वापस 0;
पूर्ण

अटल पूर्णांक img_spdअगर_in_set_lock_acquire(काष्ठा snd_kcontrol *kcontrol,
				  काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_dai *cpu_dai = snd_kcontrol_chip(kcontrol);
	काष्ठा img_spdअगर_in *spdअगर = snd_soc_dai_get_drvdata(cpu_dai);
	अचिन्हित दीर्घ flags;
	u32 reg;

	spin_lock_irqsave(&spdअगर->lock, flags);

	अगर (spdअगर->active) अणु
		spin_unlock_irqrestore(&spdअगर->lock, flags);
		वापस -EBUSY;
	पूर्ण

	spdअगर->lock_acquire = ucontrol->value.पूर्णांकeger.value[0];

	reg = img_spdअगर_in_पढ़ोl(spdअगर, IMG_SPDIF_IN_CTL);
	reg &= ~IMG_SPDIF_IN_CTL_LOCKHI_MASK;
	reg |= (spdअगर->lock_acquire << IMG_SPDIF_IN_CTL_LOCKHI_SHIFT) &
		IMG_SPDIF_IN_CTL_LOCKHI_MASK;
	img_spdअगर_in_ग_लिखोl(spdअगर, reg, IMG_SPDIF_IN_CTL);

	spin_unlock_irqrestore(&spdअगर->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक img_spdअगर_in_get_lock_release(काष्ठा snd_kcontrol *kcontrol,
				  काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_dai *cpu_dai = snd_kcontrol_chip(kcontrol);
	काष्ठा img_spdअगर_in *spdअगर = snd_soc_dai_get_drvdata(cpu_dai);

	ucontrol->value.पूर्णांकeger.value[0] = spdअगर->lock_release;

	वापस 0;
पूर्ण

अटल पूर्णांक img_spdअगर_in_set_lock_release(काष्ठा snd_kcontrol *kcontrol,
				  काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_dai *cpu_dai = snd_kcontrol_chip(kcontrol);
	काष्ठा img_spdअगर_in *spdअगर = snd_soc_dai_get_drvdata(cpu_dai);
	अचिन्हित दीर्घ flags;
	u32 reg;

	spin_lock_irqsave(&spdअगर->lock, flags);

	अगर (spdअगर->active) अणु
		spin_unlock_irqrestore(&spdअगर->lock, flags);
		वापस -EBUSY;
	पूर्ण

	spdअगर->lock_release = ucontrol->value.पूर्णांकeger.value[0];

	reg = img_spdअगर_in_पढ़ोl(spdअगर, IMG_SPDIF_IN_CTL);
	reg &= ~IMG_SPDIF_IN_CTL_LOCKLO_MASK;
	reg |= (spdअगर->lock_release << IMG_SPDIF_IN_CTL_LOCKLO_SHIFT) &
		IMG_SPDIF_IN_CTL_LOCKLO_MASK;
	img_spdअगर_in_ग_लिखोl(spdअगर, reg, IMG_SPDIF_IN_CTL);

	spin_unlock_irqrestore(&spdअगर->lock, flags);

	वापस 0;
पूर्ण

अटल काष्ठा snd_kcontrol_new img_spdअगर_in_controls[] = अणु
	अणु
		.access = SNDRV_CTL_ELEM_ACCESS_READ,
		.अगरace = SNDRV_CTL_ELEM_IFACE_PCM,
		.name = SNDRV_CTL_NAME_IEC958("", CAPTURE, MASK),
		.info = img_spdअगर_in_iec958_info,
		.get = img_spdअगर_in_get_status_mask
	पूर्ण,
	अणु
		.access = SNDRV_CTL_ELEM_ACCESS_READ |
			SNDRV_CTL_ELEM_ACCESS_VOLATILE,
		.अगरace = SNDRV_CTL_ELEM_IFACE_PCM,
		.name = SNDRV_CTL_NAME_IEC958("", CAPTURE, DEFAULT),
		.info = img_spdअगर_in_iec958_info,
		.get = img_spdअगर_in_get_status
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_PCM,
		.name = "SPDIF In Multi Frequency Acquire",
		.info = img_spdअगर_in_info_multi_freq,
		.get = img_spdअगर_in_get_multi_freq,
		.put = img_spdअगर_in_set_multi_freq
	पूर्ण,
	अणु
		.access = SNDRV_CTL_ELEM_ACCESS_READ |
			SNDRV_CTL_ELEM_ACCESS_VOLATILE,
		.अगरace = SNDRV_CTL_ELEM_IFACE_PCM,
		.name = "SPDIF In Lock Frequency",
		.info = img_spdअगर_in_info_lock_freq,
		.get = img_spdअगर_in_get_lock_freq
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_PCM,
		.name = "SPDIF In Lock TRK",
		.info = img_spdअगर_in_info_trk,
		.get = img_spdअगर_in_get_trk,
		.put = img_spdअगर_in_set_trk
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_PCM,
		.name = "SPDIF In Lock Acquire Threshold",
		.info = img_spdअगर_in_info_lock,
		.get = img_spdअगर_in_get_lock_acquire,
		.put = img_spdअगर_in_set_lock_acquire
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_PCM,
		.name = "SPDIF In Lock Release Threshold",
		.info = img_spdअगर_in_info_lock,
		.get = img_spdअगर_in_get_lock_release,
		.put = img_spdअगर_in_set_lock_release
	पूर्ण
पूर्ण;

अटल पूर्णांक img_spdअगर_in_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd,
	काष्ठा snd_soc_dai *dai)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा img_spdअगर_in *spdअगर = snd_soc_dai_get_drvdata(dai);
	पूर्णांक ret = 0;
	u32 reg;

	spin_lock_irqsave(&spdअगर->lock, flags);

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_RESUME:
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		reg = img_spdअगर_in_पढ़ोl(spdअगर, IMG_SPDIF_IN_CTL);
		अगर (spdअगर->multi_freq)
			reg &= ~IMG_SPDIF_IN_CTL_SRD_MASK;
		अन्यथा
			reg |= (1UL << IMG_SPDIF_IN_CTL_SRD_SHIFT);
		reg |= IMG_SPDIF_IN_CTL_SRT_MASK;
		img_spdअगर_in_ग_लिखोl(spdअगर, reg, IMG_SPDIF_IN_CTL);
		spdअगर->active = true;
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		reg = img_spdअगर_in_पढ़ोl(spdअगर, IMG_SPDIF_IN_CTL);
		reg &= ~IMG_SPDIF_IN_CTL_SRT_MASK;
		img_spdअगर_in_ग_लिखोl(spdअगर, reg, IMG_SPDIF_IN_CTL);
		spdअगर->active = false;
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण

	spin_unlock_irqrestore(&spdअगर->lock, flags);

	वापस ret;
पूर्ण

अटल पूर्णांक img_spdअगर_in_hw_params(काष्ठा snd_pcm_substream *substream,
	काष्ठा snd_pcm_hw_params *params, काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा img_spdअगर_in *spdअगर = snd_soc_dai_get_drvdata(dai);
	अचिन्हित पूर्णांक rate, channels;
	snd_pcm_क्रमmat_t क्रमmat;

	rate = params_rate(params);
	channels = params_channels(params);
	क्रमmat = params_क्रमmat(params);

	अगर (क्रमmat != SNDRV_PCM_FORMAT_S32_LE)
		वापस -EINVAL;

	अगर (channels != 2)
		वापस -EINVAL;

	वापस img_spdअगर_in_करो_clkgen_single(spdअगर, rate);
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops img_spdअगर_in_dai_ops = अणु
	.trigger = img_spdअगर_in_trigger,
	.hw_params = img_spdअगर_in_hw_params
पूर्ण;

अटल पूर्णांक img_spdअगर_in_dai_probe(काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा img_spdअगर_in *spdअगर = snd_soc_dai_get_drvdata(dai);

	snd_soc_dai_init_dma_data(dai, शून्य, &spdअगर->dma_data);

	snd_soc_add_dai_controls(dai, img_spdअगर_in_controls,
			ARRAY_SIZE(img_spdअगर_in_controls));

	वापस 0;
पूर्ण

अटल काष्ठा snd_soc_dai_driver img_spdअगर_in_dai = अणु
	.probe = img_spdअगर_in_dai_probe,
	.capture = अणु
		.channels_min = 2,
		.channels_max = 2,
		.rates = SNDRV_PCM_RATE_8000_192000,
		.क्रमmats = SNDRV_PCM_FMTBIT_S32_LE
	पूर्ण,
	.ops = &img_spdअगर_in_dai_ops
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver img_spdअगर_in_component = अणु
	.name = "img-spdif-in"
पूर्ण;

अटल पूर्णांक img_spdअगर_in_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा img_spdअगर_in *spdअगर;
	काष्ठा resource *res;
	व्योम __iomem *base;
	पूर्णांक ret;
	काष्ठा reset_control *rst;
	u32 reg;
	काष्ठा device *dev = &pdev->dev;

	spdअगर = devm_kzalloc(&pdev->dev, माप(*spdअगर), GFP_KERNEL);
	अगर (!spdअगर)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, spdअगर);

	spdअगर->dev = &pdev->dev;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	spdअगर->base = base;

	spdअगर->clk_sys = devm_clk_get(dev, "sys");
	अगर (IS_ERR(spdअगर->clk_sys)) अणु
		अगर (PTR_ERR(spdअगर->clk_sys) != -EPROBE_DEFER)
			dev_err(dev, "Failed to acquire clock 'sys'\n");
		वापस PTR_ERR(spdअगर->clk_sys);
	पूर्ण

	pm_runसमय_enable(&pdev->dev);
	अगर (!pm_runसमय_enabled(&pdev->dev)) अणु
		ret = img_spdअगर_in_runसमय_resume(&pdev->dev);
		अगर (ret)
			जाओ err_pm_disable;
	पूर्ण
	ret = pm_runसमय_get_sync(&pdev->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(&pdev->dev);
		जाओ err_suspend;
	पूर्ण

	rst = devm_reset_control_get_exclusive(&pdev->dev, "rst");
	अगर (IS_ERR(rst)) अणु
		अगर (PTR_ERR(rst) == -EPROBE_DEFER) अणु
			ret = -EPROBE_DEFER;
			जाओ err_pm_put;
		पूर्ण
		dev_dbg(dev, "No top level reset found\n");
		img_spdअगर_in_ग_लिखोl(spdअगर, IMG_SPDIF_IN_SOFT_RESET_MASK,
				IMG_SPDIF_IN_SOFT_RESET);
		img_spdअगर_in_ग_लिखोl(spdअगर, 0, IMG_SPDIF_IN_SOFT_RESET);
	पूर्ण अन्यथा अणु
		reset_control_निश्चित(rst);
		reset_control_deनिश्चित(rst);
	पूर्ण

	spin_lock_init(&spdअगर->lock);

	spdअगर->dma_data.addr = res->start + IMG_SPDIF_IN_RX_FIFO_OFFSET;
	spdअगर->dma_data.addr_width = 4;
	spdअगर->dma_data.maxburst = 4;
	spdअगर->trk = 0x80;
	spdअगर->lock_acquire = 4;
	spdअगर->lock_release = -128;

	reg = (spdअगर->lock_acquire << IMG_SPDIF_IN_CTL_LOCKHI_SHIFT) &
		IMG_SPDIF_IN_CTL_LOCKHI_MASK;
	reg |= (spdअगर->lock_release << IMG_SPDIF_IN_CTL_LOCKLO_SHIFT) &
		IMG_SPDIF_IN_CTL_LOCKLO_MASK;
	reg |= (spdअगर->trk << IMG_SPDIF_IN_CTL_TRK_SHIFT) &
		IMG_SPDIF_IN_CTL_TRK_MASK;
	img_spdअगर_in_ग_लिखोl(spdअगर, reg, IMG_SPDIF_IN_CTL);

	pm_runसमय_put(&pdev->dev);

	ret = devm_snd_soc_रेजिस्टर_component(&pdev->dev,
			&img_spdअगर_in_component, &img_spdअगर_in_dai, 1);
	अगर (ret)
		जाओ err_suspend;

	ret = devm_snd_dmaengine_pcm_रेजिस्टर(&pdev->dev, शून्य, 0);
	अगर (ret)
		जाओ err_suspend;

	वापस 0;

err_pm_put:
	pm_runसमय_put(&pdev->dev);
err_suspend:
	अगर (!pm_runसमय_enabled(&pdev->dev))
		img_spdअगर_in_runसमय_suspend(&pdev->dev);
err_pm_disable:
	pm_runसमय_disable(&pdev->dev);

	वापस ret;
पूर्ण

अटल पूर्णांक img_spdअगर_in_dev_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	pm_runसमय_disable(&pdev->dev);
	अगर (!pm_runसमय_status_suspended(&pdev->dev))
		img_spdअगर_in_runसमय_suspend(&pdev->dev);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक img_spdअगर_in_suspend(काष्ठा device *dev)
अणु
	काष्ठा img_spdअगर_in *spdअगर = dev_get_drvdata(dev);
	पूर्णांक ret;

	अगर (pm_runसमय_status_suspended(dev)) अणु
		ret = img_spdअगर_in_runसमय_resume(dev);
		अगर (ret)
			वापस ret;
	पूर्ण

	spdअगर->suspend_clkgen = img_spdअगर_in_पढ़ोl(spdअगर, IMG_SPDIF_IN_CLKGEN);
	spdअगर->suspend_ctl = img_spdअगर_in_पढ़ोl(spdअगर, IMG_SPDIF_IN_CTL);

	img_spdअगर_in_runसमय_suspend(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक img_spdअगर_in_resume(काष्ठा device *dev)
अणु
	काष्ठा img_spdअगर_in *spdअगर = dev_get_drvdata(dev);
	पूर्णांक i, ret;

	ret = img_spdअगर_in_runसमय_resume(dev);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < IMG_SPDIF_IN_NUM_ACLKGEN; i++)
		img_spdअगर_in_aclkgen_ग_लिखोl(spdअगर, i);

	img_spdअगर_in_ग_लिखोl(spdअगर, spdअगर->suspend_clkgen, IMG_SPDIF_IN_CLKGEN);
	img_spdअगर_in_ग_लिखोl(spdअगर, spdअगर->suspend_ctl, IMG_SPDIF_IN_CTL);

	अगर (pm_runसमय_status_suspended(dev))
		img_spdअगर_in_runसमय_suspend(dev);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा of_device_id img_spdअगर_in_of_match[] = अणु
	अणु .compatible = "img,spdif-in" पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, img_spdअगर_in_of_match);

अटल स्थिर काष्ठा dev_pm_ops img_spdअगर_in_pm_ops = अणु
	SET_RUNTIME_PM_OPS(img_spdअगर_in_runसमय_suspend,
			   img_spdअगर_in_runसमय_resume, शून्य)
	SET_SYSTEM_SLEEP_PM_OPS(img_spdअगर_in_suspend, img_spdअगर_in_resume)
पूर्ण;

अटल काष्ठा platक्रमm_driver img_spdअगर_in_driver = अणु
	.driver = अणु
		.name = "img-spdif-in",
		.of_match_table = img_spdअगर_in_of_match,
		.pm = &img_spdअगर_in_pm_ops
	पूर्ण,
	.probe = img_spdअगर_in_probe,
	.हटाओ = img_spdअगर_in_dev_हटाओ
पूर्ण;
module_platक्रमm_driver(img_spdअगर_in_driver);

MODULE_AUTHOR("Damien Horsley <Damien.Horsley@imgtec.com>");
MODULE_DESCRIPTION("IMG SPDIF Input driver");
MODULE_LICENSE("GPL v2");
