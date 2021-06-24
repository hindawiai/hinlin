<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Mirics MSi001 silicon tuner driver
 *
 * Copyright (C) 2013 Antti Palosaari <crope@iki.fi>
 * Copyright (C) 2014 Antti Palosaari <crope@iki.fi>
 */

#समावेश <linux/module.h>
#समावेश <linux/gcd.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-ctrls.h>

अटल स्थिर काष्ठा v4l2_frequency_band bands[] = अणु
	अणु
		.type = V4L2_TUNER_RF,
		.index = 0,
		.capability = V4L2_TUNER_CAP_1HZ | V4L2_TUNER_CAP_FREQ_BANDS,
		.rangelow   =   49000000,
		.rangehigh  =  263000000,
	पूर्ण, अणु
		.type = V4L2_TUNER_RF,
		.index = 1,
		.capability = V4L2_TUNER_CAP_1HZ | V4L2_TUNER_CAP_FREQ_BANDS,
		.rangelow   =  390000000,
		.rangehigh  =  960000000,
	पूर्ण,
पूर्ण;

काष्ठा msi001_dev अणु
	काष्ठा spi_device *spi;
	काष्ठा v4l2_subdev sd;

	/* Controls */
	काष्ठा v4l2_ctrl_handler hdl;
	काष्ठा v4l2_ctrl *bandwidth_स्वतः;
	काष्ठा v4l2_ctrl *bandwidth;
	काष्ठा v4l2_ctrl *lna_gain;
	काष्ठा v4l2_ctrl *mixer_gain;
	काष्ठा v4l2_ctrl *अगर_gain;

	अचिन्हित पूर्णांक f_tuner;
पूर्ण;

अटल अंतरभूत काष्ठा msi001_dev *sd_to_msi001_dev(काष्ठा v4l2_subdev *sd)
अणु
	वापस container_of(sd, काष्ठा msi001_dev, sd);
पूर्ण

अटल पूर्णांक msi001_wreg(काष्ठा msi001_dev *dev, u32 data)
अणु
	/* Register क्रमmat: 4 bits addr + 20 bits value */
	वापस spi_ग_लिखो(dev->spi, &data, 3);
पूर्ण;

अटल पूर्णांक msi001_set_gain(काष्ठा msi001_dev *dev, पूर्णांक lna_gain, पूर्णांक mixer_gain,
			   पूर्णांक अगर_gain)
अणु
	काष्ठा spi_device *spi = dev->spi;
	पूर्णांक ret;
	u32 reg;

	dev_dbg(&spi->dev, "lna=%d mixer=%d if=%d\n",
		lna_gain, mixer_gain, अगर_gain);

	reg = 1 << 0;
	reg |= (59 - अगर_gain) << 4;
	reg |= 0 << 10;
	reg |= (1 - mixer_gain) << 12;
	reg |= (1 - lna_gain) << 13;
	reg |= 4 << 14;
	reg |= 0 << 17;
	ret = msi001_wreg(dev, reg);
	अगर (ret)
		जाओ err;

	वापस 0;
err:
	dev_dbg(&spi->dev, "failed %d\n", ret);
	वापस ret;
पूर्ण;

अटल पूर्णांक msi001_set_tuner(काष्ठा msi001_dev *dev)
अणु
	काष्ठा spi_device *spi = dev->spi;
	पूर्णांक ret, i;
	अचिन्हित पूर्णांक uiपंचांगp, भाग_n, k, k_thresh, k_frac, भाग_lo, f_अगर1;
	u32 reg;
	u64 f_vco;
	u8 mode, filter_mode;

	अटल स्थिर काष्ठा अणु
		u32 rf;
		u8 mode;
		u8 भाग_lo;
	पूर्ण band_lut[] = अणु
		अणु 50000000, 0xe1, 16पूर्ण, /* AM_MODE2, antenna 2 */
		अणु108000000, 0x42, 32पूर्ण, /* VHF_MODE */
		अणु330000000, 0x44, 16पूर्ण, /* B3_MODE */
		अणु960000000, 0x48,  4पूर्ण, /* B45_MODE */
		अणु      ~0U, 0x50,  2पूर्ण, /* BL_MODE */
	पूर्ण;
	अटल स्थिर काष्ठा अणु
		u32 freq;
		u8 filter_mode;
	पूर्ण अगर_freq_lut[] = अणु
		अणु      0, 0x03पूर्ण, /* Zero IF */
		अणु 450000, 0x02पूर्ण, /* 450 kHz IF */
		अणु1620000, 0x01पूर्ण, /* 1.62 MHz IF */
		अणु2048000, 0x00पूर्ण, /* 2.048 MHz IF */
	पूर्ण;
	अटल स्थिर काष्ठा अणु
		u32 freq;
		u8 val;
	पूर्ण bandwidth_lut[] = अणु
		अणु 200000, 0x00पूर्ण, /* 200 kHz */
		अणु 300000, 0x01पूर्ण, /* 300 kHz */
		अणु 600000, 0x02पूर्ण, /* 600 kHz */
		अणु1536000, 0x03पूर्ण, /* 1.536 MHz */
		अणु5000000, 0x04पूर्ण, /* 5 MHz */
		अणु6000000, 0x05पूर्ण, /* 6 MHz */
		अणु7000000, 0x06पूर्ण, /* 7 MHz */
		अणु8000000, 0x07पूर्ण, /* 8 MHz */
	पूर्ण;

	अचिन्हित पूर्णांक f_rf = dev->f_tuner;

	/*
	 * bandwidth (Hz)
	 * 200000, 300000, 600000, 1536000, 5000000, 6000000, 7000000, 8000000
	 */
	अचिन्हित पूर्णांक bandwidth;

	/*
	 * पूर्णांकermediate frequency (Hz)
	 * 0, 450000, 1620000, 2048000
	 */
	अचिन्हित पूर्णांक f_अगर = 0;
	#घोषणा F_REF 24000000
	#घोषणा DIV_PRE_N 4
	#घोषणा	F_VCO_STEP भाग_lo

	dev_dbg(&spi->dev, "f_rf=%d f_if=%d\n", f_rf, f_अगर);

	क्रम (i = 0; i < ARRAY_SIZE(band_lut); i++) अणु
		अगर (f_rf <= band_lut[i].rf) अणु
			mode = band_lut[i].mode;
			भाग_lo = band_lut[i].भाग_lo;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (i == ARRAY_SIZE(band_lut)) अणु
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	/* AM_MODE is upconverted */
	अगर ((mode >> 0) & 0x1)
		f_अगर1 =  5 * F_REF;
	अन्यथा
		f_अगर1 =  0;

	क्रम (i = 0; i < ARRAY_SIZE(अगर_freq_lut); i++) अणु
		अगर (f_अगर == अगर_freq_lut[i].freq) अणु
			filter_mode = अगर_freq_lut[i].filter_mode;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (i == ARRAY_SIZE(अगर_freq_lut)) अणु
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	/* filters */
	bandwidth = dev->bandwidth->val;
	bandwidth = clamp(bandwidth, 200000U, 8000000U);

	क्रम (i = 0; i < ARRAY_SIZE(bandwidth_lut); i++) अणु
		अगर (bandwidth <= bandwidth_lut[i].freq) अणु
			bandwidth = bandwidth_lut[i].val;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (i == ARRAY_SIZE(bandwidth_lut)) अणु
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	dev->bandwidth->val = bandwidth_lut[i].freq;

	dev_dbg(&spi->dev, "bandwidth selected=%d\n", bandwidth_lut[i].freq);

	/*
	 * Fractional-N synthesizer
	 *
	 *           +---------------------------------------+
	 *           v                                       |
	 *  Fref   +----+     +-------+         +----+     +------+     +---+
	 * ------> | PD | --> |  VCO  | ------> | /4 | --> | /N.F | <-- | K |
	 *         +----+     +-------+         +----+     +------+     +---+
	 *                      |
	 *                      |
	 *                      v
	 *                    +-------+  Fout
	 *                    | /Rout | ------>
	 *                    +-------+
	 */

	/* Calculate PLL पूर्णांकeger and fractional control word. */
	f_vco = (u64) (f_rf + f_अगर + f_अगर1) * भाग_lo;
	भाग_n = भाग_u64_rem(f_vco, DIV_PRE_N * F_REF, &k);
	k_thresh = (DIV_PRE_N * F_REF) / F_VCO_STEP;
	k_frac = भाग_u64((u64) k * k_thresh, (DIV_PRE_N * F_REF));

	/* Find out greatest common भागisor and भागide to smaller. */
	uiपंचांगp = gcd(k_thresh, k_frac);
	k_thresh /= uiपंचांगp;
	k_frac /= uiपंचांगp;

	/* Force भागide to reg max. Resolution will be reduced. */
	uiपंचांगp = DIV_ROUND_UP(k_thresh, 4095);
	k_thresh = DIV_ROUND_CLOSEST(k_thresh, uiपंचांगp);
	k_frac = DIV_ROUND_CLOSEST(k_frac, uiपंचांगp);

	/* Calculate real RF set. */
	uiपंचांगp = (अचिन्हित पूर्णांक) F_REF * DIV_PRE_N * भाग_n;
	uiपंचांगp += (अचिन्हित पूर्णांक) F_REF * DIV_PRE_N * k_frac / k_thresh;
	uiपंचांगp /= भाग_lo;

	dev_dbg(&spi->dev,
		"f_rf=%u:%u f_vco=%llu div_n=%u k_thresh=%u k_frac=%u div_lo=%u\n",
		f_rf, uiपंचांगp, f_vco, भाग_n, k_thresh, k_frac, भाग_lo);

	ret = msi001_wreg(dev, 0x00000e);
	अगर (ret)
		जाओ err;

	ret = msi001_wreg(dev, 0x000003);
	अगर (ret)
		जाओ err;

	reg = 0 << 0;
	reg |= mode << 4;
	reg |= filter_mode << 12;
	reg |= bandwidth << 14;
	reg |= 0x02 << 17;
	reg |= 0x00 << 20;
	ret = msi001_wreg(dev, reg);
	अगर (ret)
		जाओ err;

	reg = 5 << 0;
	reg |= k_thresh << 4;
	reg |= 1 << 19;
	reg |= 1 << 21;
	ret = msi001_wreg(dev, reg);
	अगर (ret)
		जाओ err;

	reg = 2 << 0;
	reg |= k_frac << 4;
	reg |= भाग_n << 16;
	ret = msi001_wreg(dev, reg);
	अगर (ret)
		जाओ err;

	ret = msi001_set_gain(dev, dev->lna_gain->cur.val,
			      dev->mixer_gain->cur.val, dev->अगर_gain->cur.val);
	अगर (ret)
		जाओ err;

	reg = 6 << 0;
	reg |= 63 << 4;
	reg |= 4095 << 10;
	ret = msi001_wreg(dev, reg);
	अगर (ret)
		जाओ err;

	वापस 0;
err:
	dev_dbg(&spi->dev, "failed %d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक msi001_standby(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा msi001_dev *dev = sd_to_msi001_dev(sd);

	वापस msi001_wreg(dev, 0x000000);
पूर्ण

अटल पूर्णांक msi001_g_tuner(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_tuner *v)
अणु
	काष्ठा msi001_dev *dev = sd_to_msi001_dev(sd);
	काष्ठा spi_device *spi = dev->spi;

	dev_dbg(&spi->dev, "index=%d\n", v->index);

	strscpy(v->name, "Mirics MSi001", माप(v->name));
	v->type = V4L2_TUNER_RF;
	v->capability = V4L2_TUNER_CAP_1HZ | V4L2_TUNER_CAP_FREQ_BANDS;
	v->rangelow =    49000000;
	v->rangehigh =  960000000;

	वापस 0;
पूर्ण

अटल पूर्णांक msi001_s_tuner(काष्ठा v4l2_subdev *sd, स्थिर काष्ठा v4l2_tuner *v)
अणु
	काष्ठा msi001_dev *dev = sd_to_msi001_dev(sd);
	काष्ठा spi_device *spi = dev->spi;

	dev_dbg(&spi->dev, "index=%d\n", v->index);
	वापस 0;
पूर्ण

अटल पूर्णांक msi001_g_frequency(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_frequency *f)
अणु
	काष्ठा msi001_dev *dev = sd_to_msi001_dev(sd);
	काष्ठा spi_device *spi = dev->spi;

	dev_dbg(&spi->dev, "tuner=%d\n", f->tuner);
	f->frequency = dev->f_tuner;
	वापस 0;
पूर्ण

अटल पूर्णांक msi001_s_frequency(काष्ठा v4l2_subdev *sd,
			      स्थिर काष्ठा v4l2_frequency *f)
अणु
	काष्ठा msi001_dev *dev = sd_to_msi001_dev(sd);
	काष्ठा spi_device *spi = dev->spi;
	अचिन्हित पूर्णांक band;

	dev_dbg(&spi->dev, "tuner=%d type=%d frequency=%u\n",
		f->tuner, f->type, f->frequency);

	अगर (f->frequency < ((bands[0].rangehigh + bands[1].rangelow) / 2))
		band = 0;
	अन्यथा
		band = 1;
	dev->f_tuner = clamp_t(अचिन्हित पूर्णांक, f->frequency,
			       bands[band].rangelow, bands[band].rangehigh);

	वापस msi001_set_tuner(dev);
पूर्ण

अटल पूर्णांक msi001_क्रमागत_freq_bands(काष्ठा v4l2_subdev *sd,
				  काष्ठा v4l2_frequency_band *band)
अणु
	काष्ठा msi001_dev *dev = sd_to_msi001_dev(sd);
	काष्ठा spi_device *spi = dev->spi;

	dev_dbg(&spi->dev, "tuner=%d type=%d index=%d\n",
		band->tuner, band->type, band->index);

	अगर (band->index >= ARRAY_SIZE(bands))
		वापस -EINVAL;

	band->capability = bands[band->index].capability;
	band->rangelow = bands[band->index].rangelow;
	band->rangehigh = bands[band->index].rangehigh;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_tuner_ops msi001_tuner_ops = अणु
	.standby                  = msi001_standby,
	.g_tuner                  = msi001_g_tuner,
	.s_tuner                  = msi001_s_tuner,
	.g_frequency              = msi001_g_frequency,
	.s_frequency              = msi001_s_frequency,
	.क्रमागत_freq_bands          = msi001_क्रमागत_freq_bands,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops msi001_ops = अणु
	.tuner                    = &msi001_tuner_ops,
पूर्ण;

अटल पूर्णांक msi001_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा msi001_dev *dev = container_of(ctrl->handler, काष्ठा msi001_dev, hdl);
	काष्ठा spi_device *spi = dev->spi;

	पूर्णांक ret;

	dev_dbg(&spi->dev, "id=%d name=%s val=%d min=%lld max=%lld step=%lld\n",
		ctrl->id, ctrl->name, ctrl->val, ctrl->minimum, ctrl->maximum,
		ctrl->step);

	चयन (ctrl->id) अणु
	हाल V4L2_CID_RF_TUNER_BANDWIDTH_AUTO:
	हाल V4L2_CID_RF_TUNER_BANDWIDTH:
		ret = msi001_set_tuner(dev);
		अवरोध;
	हाल  V4L2_CID_RF_TUNER_LNA_GAIN:
		ret = msi001_set_gain(dev, dev->lna_gain->val,
				      dev->mixer_gain->cur.val,
				      dev->अगर_gain->cur.val);
		अवरोध;
	हाल  V4L2_CID_RF_TUNER_MIXER_GAIN:
		ret = msi001_set_gain(dev, dev->lna_gain->cur.val,
				      dev->mixer_gain->val,
				      dev->अगर_gain->cur.val);
		अवरोध;
	हाल  V4L2_CID_RF_TUNER_IF_GAIN:
		ret = msi001_set_gain(dev, dev->lna_gain->cur.val,
				      dev->mixer_gain->cur.val,
				      dev->अगर_gain->val);
		अवरोध;
	शेष:
		dev_dbg(&spi->dev, "unknown control %d\n", ctrl->id);
		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops msi001_ctrl_ops = अणु
	.s_ctrl                   = msi001_s_ctrl,
पूर्ण;

अटल पूर्णांक msi001_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा msi001_dev *dev;
	पूर्णांक ret;

	dev_dbg(&spi->dev, "\n");

	dev = kzalloc(माप(*dev), GFP_KERNEL);
	अगर (!dev) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	dev->spi = spi;
	dev->f_tuner = bands[0].rangelow;
	v4l2_spi_subdev_init(&dev->sd, spi, &msi001_ops);

	/* Register controls */
	v4l2_ctrl_handler_init(&dev->hdl, 5);
	dev->bandwidth_स्वतः = v4l2_ctrl_new_std(&dev->hdl, &msi001_ctrl_ops,
			V4L2_CID_RF_TUNER_BANDWIDTH_AUTO, 0, 1, 1, 1);
	dev->bandwidth = v4l2_ctrl_new_std(&dev->hdl, &msi001_ctrl_ops,
			V4L2_CID_RF_TUNER_BANDWIDTH, 200000, 8000000, 1, 200000);
	v4l2_ctrl_स्वतः_cluster(2, &dev->bandwidth_स्वतः, 0, false);
	dev->lna_gain = v4l2_ctrl_new_std(&dev->hdl, &msi001_ctrl_ops,
			V4L2_CID_RF_TUNER_LNA_GAIN, 0, 1, 1, 1);
	dev->mixer_gain = v4l2_ctrl_new_std(&dev->hdl, &msi001_ctrl_ops,
			V4L2_CID_RF_TUNER_MIXER_GAIN, 0, 1, 1, 1);
	dev->अगर_gain = v4l2_ctrl_new_std(&dev->hdl, &msi001_ctrl_ops,
			V4L2_CID_RF_TUNER_IF_GAIN, 0, 59, 1, 0);
	अगर (dev->hdl.error) अणु
		ret = dev->hdl.error;
		dev_err(&spi->dev, "Could not initialize controls\n");
		/* control init failed, मुक्त handler */
		जाओ err_ctrl_handler_मुक्त;
	पूर्ण

	dev->sd.ctrl_handler = &dev->hdl;
	वापस 0;
err_ctrl_handler_मुक्त:
	v4l2_ctrl_handler_मुक्त(&dev->hdl);
	kमुक्त(dev);
err:
	वापस ret;
पूर्ण

अटल पूर्णांक msi001_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा v4l2_subdev *sd = spi_get_drvdata(spi);
	काष्ठा msi001_dev *dev = sd_to_msi001_dev(sd);

	dev_dbg(&spi->dev, "\n");

	/*
	 * Registered by v4l2_spi_new_subdev() from master driver, but we must
	 * unरेजिस्टर it from here. Weird.
	 */
	v4l2_device_unरेजिस्टर_subdev(&dev->sd);
	v4l2_ctrl_handler_मुक्त(&dev->hdl);
	kमुक्त(dev);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा spi_device_id msi001_id_table[] = अणु
	अणु"msi001", 0पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(spi, msi001_id_table);

अटल काष्ठा spi_driver msi001_driver = अणु
	.driver = अणु
		.name	= "msi001",
		.suppress_bind_attrs = true,
	पूर्ण,
	.probe		= msi001_probe,
	.हटाओ		= msi001_हटाओ,
	.id_table	= msi001_id_table,
पूर्ण;
module_spi_driver(msi001_driver);

MODULE_AUTHOR("Antti Palosaari <crope@iki.fi>");
MODULE_DESCRIPTION("Mirics MSi001");
MODULE_LICENSE("GPL");
