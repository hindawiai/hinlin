<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * McBSP Sidetone support
 *
 * Copyright (C) 2004 Nokia Corporation
 * Author: Samuel Ortiz <samuel.ortiz@nokia.com>
 *
 * Contact: Jarkko Nikula <jarkko.nikula@biपंचांगer.com>
 *          Peter Ujfalusi <peter.ujfalusi@ti.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/err.h>
#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/slab.h>
#समावेश <linux/pm_runसमय.स>

#समावेश "omap-mcbsp.h"
#समावेश "omap-mcbsp-priv.h"

/* OMAP3 sidetone control रेजिस्टरs */
#घोषणा OMAP_ST_REG_REV		0x00
#घोषणा OMAP_ST_REG_SYSCONFIG	0x10
#घोषणा OMAP_ST_REG_IRQSTATUS	0x18
#घोषणा OMAP_ST_REG_IRQENABLE	0x1C
#घोषणा OMAP_ST_REG_SGAINCR	0x24
#घोषणा OMAP_ST_REG_SFIRCR	0x28
#घोषणा OMAP_ST_REG_SSELCR	0x2C

/********************** McBSP SSELCR bit definitions ***********************/
#घोषणा SIDETONEEN		BIT(10)

/********************** McBSP Sidetone SYSCONFIG bit definitions ***********/
#घोषणा ST_AUTOIDLE		BIT(0)

/********************** McBSP Sidetone SGAINCR bit definitions *************/
#घोषणा ST_CH0GAIN(value)	((value) & 0xffff)	/* Bits 0:15 */
#घोषणा ST_CH1GAIN(value)	(((value) & 0xffff) << 16) /* Bits 16:31 */

/********************** McBSP Sidetone SFIRCR bit definitions **************/
#घोषणा ST_FIRCOEFF(value)	((value) & 0xffff)	/* Bits 0:15 */

/********************** McBSP Sidetone SSELCR bit definitions **************/
#घोषणा ST_SIDETONEEN		BIT(0)
#घोषणा ST_COEFFWREN		BIT(1)
#घोषणा ST_COEFFWRDONE		BIT(2)

काष्ठा omap_mcbsp_st_data अणु
	व्योम __iomem *io_base_st;
	काष्ठा clk *mcbsp_iclk;
	bool running;
	bool enabled;
	s16 taps[128];	/* Sidetone filter coefficients */
	पूर्णांक nr_taps;	/* Number of filter coefficients in use */
	s16 ch0gain;
	s16 ch1gain;
पूर्ण;

अटल व्योम omap_mcbsp_st_ग_लिखो(काष्ठा omap_mcbsp *mcbsp, u16 reg, u32 val)
अणु
	ग_लिखोl_relaxed(val, mcbsp->st_data->io_base_st + reg);
पूर्ण

अटल पूर्णांक omap_mcbsp_st_पढ़ो(काष्ठा omap_mcbsp *mcbsp, u16 reg)
अणु
	वापस पढ़ोl_relaxed(mcbsp->st_data->io_base_st + reg);
पूर्ण

#घोषणा MCBSP_ST_READ(mcbsp, reg) omap_mcbsp_st_पढ़ो(mcbsp, OMAP_ST_REG_##reg)
#घोषणा MCBSP_ST_WRITE(mcbsp, reg, val) \
			omap_mcbsp_st_ग_लिखो(mcbsp, OMAP_ST_REG_##reg, val)

अटल व्योम omap_mcbsp_st_on(काष्ठा omap_mcbsp *mcbsp)
अणु
	अचिन्हित पूर्णांक w;

	अगर (mcbsp->pdata->क्रमce_ick_on)
		mcbsp->pdata->क्रमce_ick_on(mcbsp->st_data->mcbsp_iclk, true);

	/* Disable Sidetone घड़ी स्वतः-gating क्रम normal operation */
	w = MCBSP_ST_READ(mcbsp, SYSCONFIG);
	MCBSP_ST_WRITE(mcbsp, SYSCONFIG, w & ~(ST_AUTOIDLE));

	/* Enable McBSP Sidetone */
	w = MCBSP_READ(mcbsp, SSELCR);
	MCBSP_WRITE(mcbsp, SSELCR, w | SIDETONEEN);

	/* Enable Sidetone from Sidetone Core */
	w = MCBSP_ST_READ(mcbsp, SSELCR);
	MCBSP_ST_WRITE(mcbsp, SSELCR, w | ST_SIDETONEEN);
पूर्ण

अटल व्योम omap_mcbsp_st_off(काष्ठा omap_mcbsp *mcbsp)
अणु
	अचिन्हित पूर्णांक w;

	w = MCBSP_ST_READ(mcbsp, SSELCR);
	MCBSP_ST_WRITE(mcbsp, SSELCR, w & ~(ST_SIDETONEEN));

	w = MCBSP_READ(mcbsp, SSELCR);
	MCBSP_WRITE(mcbsp, SSELCR, w & ~(SIDETONEEN));

	/* Enable Sidetone घड़ी स्वतः-gating to reduce घातer consumption */
	w = MCBSP_ST_READ(mcbsp, SYSCONFIG);
	MCBSP_ST_WRITE(mcbsp, SYSCONFIG, w | ST_AUTOIDLE);

	अगर (mcbsp->pdata->क्रमce_ick_on)
		mcbsp->pdata->क्रमce_ick_on(mcbsp->st_data->mcbsp_iclk, false);
पूर्ण

अटल व्योम omap_mcbsp_st_fir_ग_लिखो(काष्ठा omap_mcbsp *mcbsp, s16 *fir)
अणु
	u16 val, i;

	val = MCBSP_ST_READ(mcbsp, SSELCR);

	अगर (val & ST_COEFFWREN)
		MCBSP_ST_WRITE(mcbsp, SSELCR, val & ~(ST_COEFFWREN));

	MCBSP_ST_WRITE(mcbsp, SSELCR, val | ST_COEFFWREN);

	क्रम (i = 0; i < 128; i++)
		MCBSP_ST_WRITE(mcbsp, SFIRCR, fir[i]);

	i = 0;

	val = MCBSP_ST_READ(mcbsp, SSELCR);
	जबतक (!(val & ST_COEFFWRDONE) && (++i < 1000))
		val = MCBSP_ST_READ(mcbsp, SSELCR);

	MCBSP_ST_WRITE(mcbsp, SSELCR, val & ~(ST_COEFFWREN));

	अगर (i == 1000)
		dev_err(mcbsp->dev, "McBSP FIR load error!\n");
पूर्ण

अटल व्योम omap_mcbsp_st_chgain(काष्ठा omap_mcbsp *mcbsp)
अणु
	काष्ठा omap_mcbsp_st_data *st_data = mcbsp->st_data;

	MCBSP_ST_WRITE(mcbsp, SGAINCR, ST_CH0GAIN(st_data->ch0gain) |
		       ST_CH1GAIN(st_data->ch1gain));
पूर्ण

अटल पूर्णांक omap_mcbsp_st_set_chgain(काष्ठा omap_mcbsp *mcbsp, पूर्णांक channel,
				    s16 chgain)
अणु
	काष्ठा omap_mcbsp_st_data *st_data = mcbsp->st_data;
	पूर्णांक ret = 0;

	अगर (!st_data)
		वापस -ENOENT;

	spin_lock_irq(&mcbsp->lock);
	अगर (channel == 0)
		st_data->ch0gain = chgain;
	अन्यथा अगर (channel == 1)
		st_data->ch1gain = chgain;
	अन्यथा
		ret = -EINVAL;

	अगर (st_data->enabled)
		omap_mcbsp_st_chgain(mcbsp);
	spin_unlock_irq(&mcbsp->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक omap_mcbsp_st_get_chgain(काष्ठा omap_mcbsp *mcbsp, पूर्णांक channel,
				    s16 *chgain)
अणु
	काष्ठा omap_mcbsp_st_data *st_data = mcbsp->st_data;
	पूर्णांक ret = 0;

	अगर (!st_data)
		वापस -ENOENT;

	spin_lock_irq(&mcbsp->lock);
	अगर (channel == 0)
		*chgain = st_data->ch0gain;
	अन्यथा अगर (channel == 1)
		*chgain = st_data->ch1gain;
	अन्यथा
		ret = -EINVAL;
	spin_unlock_irq(&mcbsp->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक omap_mcbsp_st_enable(काष्ठा omap_mcbsp *mcbsp)
अणु
	काष्ठा omap_mcbsp_st_data *st_data = mcbsp->st_data;

	अगर (!st_data)
		वापस -ENODEV;

	spin_lock_irq(&mcbsp->lock);
	st_data->enabled = 1;
	omap_mcbsp_st_start(mcbsp);
	spin_unlock_irq(&mcbsp->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक omap_mcbsp_st_disable(काष्ठा omap_mcbsp *mcbsp)
अणु
	काष्ठा omap_mcbsp_st_data *st_data = mcbsp->st_data;
	पूर्णांक ret = 0;

	अगर (!st_data)
		वापस -ENODEV;

	spin_lock_irq(&mcbsp->lock);
	omap_mcbsp_st_stop(mcbsp);
	st_data->enabled = 0;
	spin_unlock_irq(&mcbsp->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक omap_mcbsp_st_is_enabled(काष्ठा omap_mcbsp *mcbsp)
अणु
	काष्ठा omap_mcbsp_st_data *st_data = mcbsp->st_data;

	अगर (!st_data)
		वापस -ENODEV;

	वापस st_data->enabled;
पूर्ण

अटल sमाप_प्रकार st_taps_show(काष्ठा device *dev,
			    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा omap_mcbsp *mcbsp = dev_get_drvdata(dev);
	काष्ठा omap_mcbsp_st_data *st_data = mcbsp->st_data;
	sमाप_प्रकार status = 0;
	पूर्णांक i;

	spin_lock_irq(&mcbsp->lock);
	क्रम (i = 0; i < st_data->nr_taps; i++)
		status += प्र_लिखो(&buf[status], (i ? ", %d" : "%d"),
				  st_data->taps[i]);
	अगर (i)
		status += प्र_लिखो(&buf[status], "\n");
	spin_unlock_irq(&mcbsp->lock);

	वापस status;
पूर्ण

अटल sमाप_प्रकार st_taps_store(काष्ठा device *dev,
			     काष्ठा device_attribute *attr,
			     स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	काष्ठा omap_mcbsp *mcbsp = dev_get_drvdata(dev);
	काष्ठा omap_mcbsp_st_data *st_data = mcbsp->st_data;
	पूर्णांक val, पंचांगp, status, i = 0;

	spin_lock_irq(&mcbsp->lock);
	स_रखो(st_data->taps, 0, माप(st_data->taps));
	st_data->nr_taps = 0;

	करो अणु
		status = माला_पूछो(buf, "%d%n", &val, &पंचांगp);
		अगर (status < 0 || status == 0) अणु
			size = -EINVAL;
			जाओ out;
		पूर्ण
		अगर (val < -32768 || val > 32767) अणु
			size = -EINVAL;
			जाओ out;
		पूर्ण
		st_data->taps[i++] = val;
		buf += पंचांगp;
		अगर (*buf != ',')
			अवरोध;
		buf++;
	पूर्ण जबतक (1);

	st_data->nr_taps = i;

out:
	spin_unlock_irq(&mcbsp->lock);

	वापस size;
पूर्ण

अटल DEVICE_ATTR_RW(st_taps);

अटल स्थिर काष्ठा attribute *sidetone_attrs[] = अणु
	&dev_attr_st_taps.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group sidetone_attr_group = अणु
	.attrs = (काष्ठा attribute **)sidetone_attrs,
पूर्ण;

पूर्णांक omap_mcbsp_st_start(काष्ठा omap_mcbsp *mcbsp)
अणु
	काष्ठा omap_mcbsp_st_data *st_data = mcbsp->st_data;

	अगर (st_data->enabled && !st_data->running) अणु
		omap_mcbsp_st_fir_ग_लिखो(mcbsp, st_data->taps);
		omap_mcbsp_st_chgain(mcbsp);

		अगर (!mcbsp->मुक्त) अणु
			omap_mcbsp_st_on(mcbsp);
			st_data->running = 1;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक omap_mcbsp_st_stop(काष्ठा omap_mcbsp *mcbsp)
अणु
	काष्ठा omap_mcbsp_st_data *st_data = mcbsp->st_data;

	अगर (st_data->running) अणु
		अगर (!mcbsp->मुक्त) अणु
			omap_mcbsp_st_off(mcbsp);
			st_data->running = 0;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक omap_mcbsp_st_init(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा omap_mcbsp *mcbsp = platक्रमm_get_drvdata(pdev);
	काष्ठा omap_mcbsp_st_data *st_data;
	काष्ठा resource *res;
	पूर्णांक ret;

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "sidetone");
	अगर (!res)
		वापस 0;

	st_data = devm_kzalloc(mcbsp->dev, माप(*mcbsp->st_data), GFP_KERNEL);
	अगर (!st_data)
		वापस -ENOMEM;

	st_data->mcbsp_iclk = clk_get(mcbsp->dev, "ick");
	अगर (IS_ERR(st_data->mcbsp_iclk)) अणु
		dev_warn(mcbsp->dev,
			 "Failed to get ick, sidetone might be broken\n");
		st_data->mcbsp_iclk = शून्य;
	पूर्ण

	st_data->io_base_st = devm_ioremap(mcbsp->dev, res->start,
					   resource_size(res));
	अगर (!st_data->io_base_st)
		वापस -ENOMEM;

	ret = sysfs_create_group(&mcbsp->dev->kobj, &sidetone_attr_group);
	अगर (ret)
		वापस ret;

	mcbsp->st_data = st_data;

	वापस 0;
पूर्ण

व्योम omap_mcbsp_st_cleanup(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा omap_mcbsp *mcbsp = platक्रमm_get_drvdata(pdev);

	अगर (mcbsp->st_data) अणु
		sysfs_हटाओ_group(&mcbsp->dev->kobj, &sidetone_attr_group);
		clk_put(mcbsp->st_data->mcbsp_iclk);
	पूर्ण
पूर्ण

अटल पूर्णांक omap_mcbsp_st_info_volsw(काष्ठा snd_kcontrol *kcontrol,
				    काष्ठा snd_ctl_elem_info *uinfo)
अणु
	काष्ठा soc_mixer_control *mc =
		(काष्ठा soc_mixer_control *)kcontrol->निजी_value;
	पूर्णांक max = mc->max;
	पूर्णांक min = mc->min;

	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 1;
	uinfo->value.पूर्णांकeger.min = min;
	uinfo->value.पूर्णांकeger.max = max;
	वापस 0;
पूर्ण

#घोषणा OMAP_MCBSP_ST_CHANNEL_VOLUME(channel)				\
अटल पूर्णांक								\
omap_mcbsp_set_st_ch##channel##_volume(काष्ठा snd_kcontrol *kc,		\
				       काष्ठा snd_ctl_elem_value *uc)	\
अणु									\
	काष्ठा snd_soc_dai *cpu_dai = snd_kcontrol_chip(kc);		\
	काष्ठा omap_mcbsp *mcbsp = snd_soc_dai_get_drvdata(cpu_dai);	\
	काष्ठा soc_mixer_control *mc =					\
		(काष्ठा soc_mixer_control *)kc->निजी_value;		\
	पूर्णांक max = mc->max;						\
	पूर्णांक min = mc->min;						\
	पूर्णांक val = uc->value.पूर्णांकeger.value[0];				\
									\
	अगर (val < min || val > max)					\
		वापस -EINVAL;						\
									\
	/* OMAP McBSP implementation uses index values 0..4 */		\
	वापस omap_mcbsp_st_set_chgain(mcbsp, channel, val);		\
पूर्ण									\
									\
अटल पूर्णांक								\
omap_mcbsp_get_st_ch##channel##_volume(काष्ठा snd_kcontrol *kc,		\
				       काष्ठा snd_ctl_elem_value *uc)	\
अणु									\
	काष्ठा snd_soc_dai *cpu_dai = snd_kcontrol_chip(kc);		\
	काष्ठा omap_mcbsp *mcbsp = snd_soc_dai_get_drvdata(cpu_dai);	\
	s16 chgain;							\
									\
	अगर (omap_mcbsp_st_get_chgain(mcbsp, channel, &chgain))		\
		वापस -EAGAIN;						\
									\
	uc->value.पूर्णांकeger.value[0] = chgain;				\
	वापस 0;							\
पूर्ण

OMAP_MCBSP_ST_CHANNEL_VOLUME(0)
OMAP_MCBSP_ST_CHANNEL_VOLUME(1)

अटल पूर्णांक omap_mcbsp_st_put_mode(काष्ठा snd_kcontrol *kcontrol,
				  काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_dai *cpu_dai = snd_kcontrol_chip(kcontrol);
	काष्ठा omap_mcbsp *mcbsp = snd_soc_dai_get_drvdata(cpu_dai);
	u8 value = ucontrol->value.पूर्णांकeger.value[0];

	अगर (value == omap_mcbsp_st_is_enabled(mcbsp))
		वापस 0;

	अगर (value)
		omap_mcbsp_st_enable(mcbsp);
	अन्यथा
		omap_mcbsp_st_disable(mcbsp);

	वापस 1;
पूर्ण

अटल पूर्णांक omap_mcbsp_st_get_mode(काष्ठा snd_kcontrol *kcontrol,
				  काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_dai *cpu_dai = snd_kcontrol_chip(kcontrol);
	काष्ठा omap_mcbsp *mcbsp = snd_soc_dai_get_drvdata(cpu_dai);

	ucontrol->value.पूर्णांकeger.value[0] = omap_mcbsp_st_is_enabled(mcbsp);
	वापस 0;
पूर्ण

#घोषणा OMAP_MCBSP_SOC_SINGLE_S16_EXT(xname, xmin, xmax,		\
				      xhandler_get, xhandler_put)	\
अणु	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname,		\
	.info = omap_mcbsp_st_info_volsw,				\
	.get = xhandler_get, .put = xhandler_put,			\
	.निजी_value = (अचिन्हित दीर्घ)&(काष्ठा soc_mixer_control)	\
	अणु.min = xmin, .max = xmaxपूर्ण पूर्ण

#घोषणा OMAP_MCBSP_ST_CONTROLS(port)					  \
अटल स्थिर काष्ठा snd_kcontrol_new omap_mcbsp##port##_st_controls[] = अणु \
SOC_SINGLE_EXT("McBSP" #port " Sidetone Switch", 1, 0, 1, 0,		  \
	       omap_mcbsp_st_get_mode, omap_mcbsp_st_put_mode),		  \
OMAP_MCBSP_SOC_SINGLE_S16_EXT("McBSP" #port " Sidetone Channel 0 Volume", \
			      -32768, 32767,				  \
			      omap_mcbsp_get_st_ch0_volume,		  \
			      omap_mcbsp_set_st_ch0_volume),		  \
OMAP_MCBSP_SOC_SINGLE_S16_EXT("McBSP" #port " Sidetone Channel 1 Volume", \
			      -32768, 32767,				  \
			      omap_mcbsp_get_st_ch1_volume,		  \
			      omap_mcbsp_set_st_ch1_volume),		  \
पूर्ण

OMAP_MCBSP_ST_CONTROLS(2);
OMAP_MCBSP_ST_CONTROLS(3);

पूर्णांक omap_mcbsp_st_add_controls(काष्ठा snd_soc_pcm_runसमय *rtd, पूर्णांक port_id)
अणु
	काष्ठा snd_soc_dai *cpu_dai = asoc_rtd_to_cpu(rtd, 0);
	काष्ठा omap_mcbsp *mcbsp = snd_soc_dai_get_drvdata(cpu_dai);

	अगर (!mcbsp->st_data) अणु
		dev_warn(mcbsp->dev, "No sidetone data for port\n");
		वापस 0;
	पूर्ण

	चयन (port_id) अणु
	हाल 2: /* McBSP 2 */
		वापस snd_soc_add_dai_controls(cpu_dai,
					omap_mcbsp2_st_controls,
					ARRAY_SIZE(omap_mcbsp2_st_controls));
	हाल 3: /* McBSP 3 */
		वापस snd_soc_add_dai_controls(cpu_dai,
					omap_mcbsp3_st_controls,
					ARRAY_SIZE(omap_mcbsp3_st_controls));
	शेष:
		dev_err(mcbsp->dev, "Port %d not supported\n", port_id);
		अवरोध;
	पूर्ण

	वापस -EINVAL;
पूर्ण
EXPORT_SYMBOL_GPL(omap_mcbsp_st_add_controls);
