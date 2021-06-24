<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * ITE IT913X silicon tuner driver
 *
 *  Copyright (C) 2011 Malcolm Priestley (tvboxspy@gmail.com)
 *  IT9137 Copyright (C) ITE Tech Inc.
 */

#समावेश "it913x.h"
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>

काष्ठा it913x_dev अणु
	काष्ठा platक्रमm_device *pdev;
	काष्ठा regmap *regmap;
	काष्ठा dvb_frontend *fe;
	u8 chip_ver:2;
	u8 role:2;
	u16 xtal;
	u8 fभाग;
	u8 clk_mode;
	u32 fn_min;
	bool active;
पूर्ण;

अटल पूर्णांक it913x_init(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा it913x_dev *dev = fe->tuner_priv;
	काष्ठा platक्रमm_device *pdev = dev->pdev;
	पूर्णांक ret;
	अचिन्हित पूर्णांक uपंचांगp;
	u8 iqik_m_cal, nv_val, buf[2];
	अटल स्थिर u8 nv[] = अणु48, 32, 24, 16, 12, 8, 6, 4, 2पूर्ण;
	अचिन्हित दीर्घ समयout;

	dev_dbg(&pdev->dev, "role %u\n", dev->role);

	ret = regmap_ग_लिखो(dev->regmap, 0x80ec4c, 0x68);
	अगर (ret)
		जाओ err;

	usleep_range(10000, 100000);

	ret = regmap_पढ़ो(dev->regmap, 0x80ec86, &uपंचांगp);
	अगर (ret)
		जाओ err;

	चयन (uपंचांगp) अणु
	हाल 0:
		/* 12.000 MHz */
		dev->clk_mode = uपंचांगp;
		dev->xtal = 2000;
		dev->fभाग = 3;
		iqik_m_cal = 16;
		अवरोध;
	हाल 1:
		/* 20.480 MHz */
		dev->clk_mode = uपंचांगp;
		dev->xtal = 640;
		dev->fभाग = 1;
		iqik_m_cal = 6;
		अवरोध;
	शेष:
		dev_err(&pdev->dev, "unknown clock identifier %d\n", uपंचांगp);
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	ret = regmap_पढ़ो(dev->regmap, 0x80ed03,  &uपंचांगp);
	अगर (ret)
		जाओ err;

	अन्यथा अगर (uपंचांगp < ARRAY_SIZE(nv))
		nv_val = nv[uपंचांगp];
	अन्यथा
		nv_val = 2;

	#घोषणा TIMEOUT 50
	समयout = jअगरfies + msecs_to_jअगरfies(TIMEOUT);
	जबतक (!समय_after(jअगरfies, समयout)) अणु
		ret = regmap_bulk_पढ़ो(dev->regmap, 0x80ed23, buf, 2);
		अगर (ret)
			जाओ err;

		uपंचांगp = (buf[1] << 8) | (buf[0] << 0);
		अगर (uपंचांगp)
			अवरोध;
	पूर्ण

	dev_dbg(&pdev->dev, "r_fbc_m_bdry took %u ms, val %u\n",
			jअगरfies_to_msecs(jअगरfies) -
			(jअगरfies_to_msecs(समयout) - TIMEOUT), uपंचांगp);

	dev->fn_min = dev->xtal * uपंचांगp;
	dev->fn_min /= (dev->fभाग * nv_val);
	dev->fn_min *= 1000;
	dev_dbg(&pdev->dev, "fn_min %u\n", dev->fn_min);

	/*
	 * Chip version BX never sets that flag so we just रुको 50ms in that
	 * हाल. It is possible poll BX similarly than AX and then समयout in
	 * order to get 50ms delay, but that causes about 120 extra I2C
	 * messages. As क्रम now, we just रुको and reduce IO.
	 */
	अगर (dev->chip_ver == 1) अणु
		#घोषणा TIMEOUT 50
		समयout = jअगरfies + msecs_to_jअगरfies(TIMEOUT);
		जबतक (!समय_after(jअगरfies, समयout)) अणु
			ret = regmap_पढ़ो(dev->regmap, 0x80ec82, &uपंचांगp);
			अगर (ret)
				जाओ err;

			अगर (uपंचांगp)
				अवरोध;
		पूर्ण

		dev_dbg(&pdev->dev, "p_tsm_init_mode took %u ms, val %u\n",
				jअगरfies_to_msecs(jअगरfies) -
				(jअगरfies_to_msecs(समयout) - TIMEOUT), uपंचांगp);
	पूर्ण अन्यथा अणु
		msleep(50);
	पूर्ण

	ret = regmap_ग_लिखो(dev->regmap, 0x80ed81, iqik_m_cal);
	अगर (ret)
		जाओ err;

	ret = regmap_ग_लिखो(dev->regmap, 0x80ec57, 0x00);
	अगर (ret)
		जाओ err;

	ret = regmap_ग_लिखो(dev->regmap, 0x80ec58, 0x00);
	अगर (ret)
		जाओ err;

	ret = regmap_ग_लिखो(dev->regmap, 0x80ec40, 0x01);
	अगर (ret)
		जाओ err;

	dev->active = true;

	वापस 0;
err:
	dev_dbg(&pdev->dev, "failed %d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक it913x_sleep(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा it913x_dev *dev = fe->tuner_priv;
	काष्ठा platक्रमm_device *pdev = dev->pdev;
	पूर्णांक ret, len;

	dev_dbg(&pdev->dev, "role %u\n", dev->role);

	dev->active = false;

	ret  = regmap_bulk_ग_लिखो(dev->regmap, 0x80ec40, "\x00", 1);
	अगर (ret)
		जाओ err;

	/*
	 * Writing '0x00' to master tuner register '0x80ec08' causes slave tuner
	 * communication lost. Due to that, we cannot put master full sleep.
	 */
	अगर (dev->role == IT913X_ROLE_DUAL_MASTER)
		len = 4;
	अन्यथा
		len = 15;

	dev_dbg(&pdev->dev, "role %u, len %d\n", dev->role, len);

	ret = regmap_bulk_ग_लिखो(dev->regmap, 0x80ec02,
			"\x3f\x1f\x3f\x3e\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00",
			len);
	अगर (ret)
		जाओ err;

	ret = regmap_bulk_ग_लिखो(dev->regmap, 0x80ec12, "\x00\x00\x00\x00", 4);
	अगर (ret)
		जाओ err;

	ret = regmap_bulk_ग_लिखो(dev->regmap, 0x80ec17,
			"\x00\x00\x00\x00\x00\x00\x00\x00\x00", 9);
	अगर (ret)
		जाओ err;

	ret = regmap_bulk_ग_लिखो(dev->regmap, 0x80ec22,
			"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00", 10);
	अगर (ret)
		जाओ err;

	ret = regmap_bulk_ग_लिखो(dev->regmap, 0x80ec20, "\x00", 1);
	अगर (ret)
		जाओ err;

	ret = regmap_bulk_ग_लिखो(dev->regmap, 0x80ec3f, "\x01", 1);
	अगर (ret)
		जाओ err;

	वापस 0;
err:
	dev_dbg(&pdev->dev, "failed %d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक it913x_set_params(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा it913x_dev *dev = fe->tuner_priv;
	काष्ठा platक्रमm_device *pdev = dev->pdev;
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	पूर्णांक ret;
	अचिन्हित पूर्णांक uपंचांगp;
	u32 pre_lo_freq, t_cal_freq;
	u16 iqik_m_cal, n_भाग;
	u8 u8पंचांगp, n, l_band, lna_band;

	dev_dbg(&pdev->dev, "role=%u, frequency %u, bandwidth_hz %u\n",
			dev->role, c->frequency, c->bandwidth_hz);

	अगर (!dev->active) अणु
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	अगर (c->frequency <=         74000000) अणु
		n_भाग = 48;
		n = 0;
	पूर्ण अन्यथा अगर (c->frequency <= 111000000) अणु
		n_भाग = 32;
		n = 1;
	पूर्ण अन्यथा अगर (c->frequency <= 148000000) अणु
		n_भाग = 24;
		n = 2;
	पूर्ण अन्यथा अगर (c->frequency <= 222000000) अणु
		n_भाग = 16;
		n = 3;
	पूर्ण अन्यथा अगर (c->frequency <= 296000000) अणु
		n_भाग = 12;
		n = 4;
	पूर्ण अन्यथा अगर (c->frequency <= 445000000) अणु
		n_भाग = 8;
		n = 5;
	पूर्ण अन्यथा अगर (c->frequency <= dev->fn_min) अणु
		n_भाग = 6;
		n = 6;
	पूर्ण अन्यथा अगर (c->frequency <= 950000000) अणु
		n_भाग = 4;
		n = 7;
	पूर्ण अन्यथा अणु
		n_भाग = 2;
		n = 0;
	पूर्ण

	ret = regmap_पढ़ो(dev->regmap, 0x80ed81, &uपंचांगp);
	अगर (ret)
		जाओ err;

	iqik_m_cal = uपंचांगp * n_भाग;

	अगर (uपंचांगp < 0x20) अणु
		अगर (dev->clk_mode == 0)
			iqik_m_cal = (iqik_m_cal * 9) >> 5;
		अन्यथा
			iqik_m_cal >>= 1;
	पूर्ण अन्यथा अणु
		iqik_m_cal = 0x40 - iqik_m_cal;
		अगर (dev->clk_mode == 0)
			iqik_m_cal = ~((iqik_m_cal * 9) >> 5);
		अन्यथा
			iqik_m_cal = ~(iqik_m_cal >> 1);
	पूर्ण

	t_cal_freq = (c->frequency / 1000) * n_भाग * dev->fभाग;
	pre_lo_freq = t_cal_freq / dev->xtal;
	uपंचांगp = pre_lo_freq * dev->xtal;

	अगर ((t_cal_freq - uपंचांगp) >= (dev->xtal >> 1))
		pre_lo_freq++;

	pre_lo_freq += (u32) n << 13;
	/* Frequency OMEGA_IQIK_M_CAL_MID*/
	t_cal_freq = pre_lo_freq + (u32)iqik_m_cal;
	dev_dbg(&pdev->dev, "t_cal_freq %u, pre_lo_freq %u\n",
			t_cal_freq, pre_lo_freq);

	अगर (c->frequency <=         440000000) अणु
		l_band = 0;
		lna_band = 0;
	पूर्ण अन्यथा अगर (c->frequency <=  484000000) अणु
		l_band = 1;
		lna_band = 1;
	पूर्ण अन्यथा अगर (c->frequency <=  533000000) अणु
		l_band = 1;
		lna_band = 2;
	पूर्ण अन्यथा अगर (c->frequency <=  587000000) अणु
		l_band = 1;
		lna_band = 3;
	पूर्ण अन्यथा अगर (c->frequency <=  645000000) अणु
		l_band = 1;
		lna_band = 4;
	पूर्ण अन्यथा अगर (c->frequency <=  710000000) अणु
		l_band = 1;
		lna_band = 5;
	पूर्ण अन्यथा अगर (c->frequency <=  782000000) अणु
		l_band = 1;
		lna_band = 6;
	पूर्ण अन्यथा अगर (c->frequency <=  860000000) अणु
		l_band = 1;
		lna_band = 7;
	पूर्ण अन्यथा अगर (c->frequency <= 1492000000) अणु
		l_band = 1;
		lna_band = 0;
	पूर्ण अन्यथा अगर (c->frequency <= 1685000000) अणु
		l_band = 1;
		lna_band = 1;
	पूर्ण अन्यथा अणु
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	/* XXX: latest winकरोws driver करोes not set that at all */
	ret = regmap_ग_लिखो(dev->regmap, 0x80ee06, lna_band);
	अगर (ret)
		जाओ err;

	अगर (c->bandwidth_hz <=      5000000)
		u8पंचांगp = 0;
	अन्यथा अगर (c->bandwidth_hz <= 6000000)
		u8पंचांगp = 2;
	अन्यथा अगर (c->bandwidth_hz <= 7000000)
		u8पंचांगp = 4;
	अन्यथा
		u8पंचांगp = 6;       /* 8000000 */

	ret = regmap_ग_लिखो(dev->regmap, 0x80ec56, u8पंचांगp);
	अगर (ret)
		जाओ err;

	/* XXX: latest winकरोws driver sets dअगरferent value (a8 != 68) */
	ret = regmap_ग_लिखो(dev->regmap, 0x80ec4c, 0xa0 | (l_band << 3));
	अगर (ret)
		जाओ err;

	ret = regmap_ग_लिखो(dev->regmap, 0x80ec4d, (t_cal_freq >> 0) & 0xff);
	अगर (ret)
		जाओ err;

	ret = regmap_ग_लिखो(dev->regmap, 0x80ec4e, (t_cal_freq >> 8) & 0xff);
	अगर (ret)
		जाओ err;

	ret = regmap_ग_लिखो(dev->regmap, 0x80011e, (pre_lo_freq >> 0) & 0xff);
	अगर (ret)
		जाओ err;

	ret = regmap_ग_लिखो(dev->regmap, 0x80011f, (pre_lo_freq >> 8) & 0xff);
	अगर (ret)
		जाओ err;

	वापस 0;
err:
	dev_dbg(&pdev->dev, "failed %d\n", ret);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा dvb_tuner_ops it913x_tuner_ops = अणु
	.info = अणु
		.name             = "ITE IT913X",
		.frequency_min_hz = 174 * MHz,
		.frequency_max_hz = 862 * MHz,
	पूर्ण,

	.init = it913x_init,
	.sleep = it913x_sleep,
	.set_params = it913x_set_params,
पूर्ण;

अटल पूर्णांक it913x_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा it913x_platक्रमm_data *pdata = pdev->dev.platक्रमm_data;
	काष्ठा dvb_frontend *fe = pdata->fe;
	काष्ठा it913x_dev *dev;
	स्थिर काष्ठा platक्रमm_device_id *id = platक्रमm_get_device_id(pdev);
	पूर्णांक ret;
	अक्षर *chip_ver_str;

	dev = kzalloc(माप(काष्ठा it913x_dev), GFP_KERNEL);
	अगर (dev == शून्य) अणु
		ret = -ENOMEM;
		dev_err(&pdev->dev, "kzalloc() failed\n");
		जाओ err;
	पूर्ण

	dev->pdev = pdev;
	dev->regmap = pdata->regmap;
	dev->fe = pdata->fe;
	dev->chip_ver = id->driver_data;
	dev->role = pdata->role;

	fe->tuner_priv = dev;
	स_नकल(&fe->ops.tuner_ops, &it913x_tuner_ops,
			माप(काष्ठा dvb_tuner_ops));
	platक्रमm_set_drvdata(pdev, dev);

	अगर (dev->chip_ver == 1)
		chip_ver_str = "AX";
	अन्यथा अगर (dev->chip_ver == 2)
		chip_ver_str = "BX";
	अन्यथा
		chip_ver_str = "??";

	dev_info(&pdev->dev, "ITE IT913X %s successfully attached\n",
		 chip_ver_str);
	dev_dbg(&pdev->dev, "chip_ver %u, role %u\n", dev->chip_ver, dev->role);
	वापस 0;
err:
	dev_dbg(&pdev->dev, "failed %d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक it913x_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा it913x_dev *dev = platक्रमm_get_drvdata(pdev);
	काष्ठा dvb_frontend *fe = dev->fe;

	dev_dbg(&pdev->dev, "\n");

	स_रखो(&fe->ops.tuner_ops, 0, माप(काष्ठा dvb_tuner_ops));
	fe->tuner_priv = शून्य;
	kमुक्त(dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_id it913x_id_table[] = अणु
	अणु"it9133ax-tuner", 1पूर्ण,
	अणु"it9133bx-tuner", 2पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, it913x_id_table);

अटल काष्ठा platक्रमm_driver it913x_driver = अणु
	.driver = अणु
		.name	= "it913x",
		.suppress_bind_attrs	= true,
	पूर्ण,
	.probe		= it913x_probe,
	.हटाओ		= it913x_हटाओ,
	.id_table	= it913x_id_table,
पूर्ण;

module_platक्रमm_driver(it913x_driver);

MODULE_DESCRIPTION("ITE IT913X silicon tuner driver");
MODULE_AUTHOR("Antti Palosaari <crope@iki.fi>");
MODULE_LICENSE("GPL");
