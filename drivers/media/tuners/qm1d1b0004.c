<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Sharp QM1D1B0004 satellite tuner
 *
 * Copyright (C) 2014 Akihiro Tsukada <tskd08@gmail.com>
 *
 * based on (क्रमmer) drivers/media/pci/pt1/va1j5jf8007s.c.
 */

/*
 * Note:
 * Since the data-sheet of this tuner chip is not available,
 * this driver lacks some tuner_ops and config options.
 * In addition, the implementation might be dependent on the specअगरic use
 * in the FE module: VA1J5JF8007S and/or in the product: Earthsoft PT1/PT2.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <media/dvb_frontend.h>
#समावेश "qm1d1b0004.h"

/*
 * Tuner I/F (copied from the क्रमmer va1j5jf8007s.c)
 * b[0] I2C addr
 * b[1] "0":1, BG:2, भागider_quotient[7:3]:5
 * b[2] भागider_quotient[2:0]:3, भागider_reमुख्यder:5
 * b[3] "111":3, LPF[3:2]:2, TM:1, "0":1, REF:1
 * b[4] BANDX, PSC:1, LPF[1:0]:2, DIV:1, "0":1
 *
 * PLL frequency step :=
 *    REF == 0 -> PLL XTL frequency(4MHz) / 8
 *    REF == 1 -> PLL XTL frequency(4MHz) / 4
 *
 * PreScaler :=
 *    PSC == 0 -> x32
 *    PSC == 1 -> x16
 *
 * भागider_quotient := (frequency / PLL frequency step) / PreScaler
 * भागider_reमुख्यder := (frequency / PLL frequency step) % PreScaler
 *
 * LPF := LPF Frequency / 1000 / 2 - 2
 * LPF Frequency @ baudrate=28.86Mbps = 30000
 *
 * band (1..9)
 *   band 1 (freq <  986000) -> DIV:1, BANDX:5, PSC:1
 *   band 2 (freq < 1072000) -> DIV:1, BANDX:6, PSC:1
 *   band 3 (freq < 1154000) -> DIV:1, BANDX:7, PSC:0
 *   band 4 (freq < 1291000) -> DIV:0, BANDX:1, PSC:0
 *   band 5 (freq < 1447000) -> DIV:0, BANDX:2, PSC:0
 *   band 6 (freq < 1615000) -> DIV:0, BANDX:3, PSC:0
 *   band 7 (freq < 1791000) -> DIV:0, BANDX:4, PSC:0
 *   band 8 (freq < 1972000) -> DIV:0, BANDX:5, PSC:0
 *   band 9 (freq < 2150000) -> DIV:0, BANDX:6, PSC:0
 */

#घोषणा QM1D1B0004_PSC_MASK (1 << 4)

#घोषणा QM1D1B0004_XTL_FREQ 4000
#घोषणा QM1D1B0004_LPF_FALLBACK 30000

#अगर 0 /* Currently unused */
अटल स्थिर काष्ठा qm1d1b0004_config शेष_cfg = अणु
	.lpf_freq = QM1D1B0004_CFG_LPF_DFLT,
	.half_step = false,
पूर्ण;
#पूर्ण_अगर

काष्ठा qm1d1b0004_state अणु
	काष्ठा qm1d1b0004_config cfg;
	काष्ठा i2c_client *i2c;
पूर्ण;


काष्ठा qm1d1b0004_cb_map अणु
	u32 frequency;
	u8 cb;
पूर्ण;

अटल स्थिर काष्ठा qm1d1b0004_cb_map cb_maps[] = अणु
	अणु  986000, 0xb2 पूर्ण,
	अणु 1072000, 0xd2 पूर्ण,
	अणु 1154000, 0xe2 पूर्ण,
	अणु 1291000, 0x20 पूर्ण,
	अणु 1447000, 0x40 पूर्ण,
	अणु 1615000, 0x60 पूर्ण,
	अणु 1791000, 0x80 पूर्ण,
	अणु 1972000, 0xa0 पूर्ण,
पूर्ण;

अटल u8 lookup_cb(u32 frequency)
अणु
	पूर्णांक i;
	स्थिर काष्ठा qm1d1b0004_cb_map *map;

	क्रम (i = 0; i < ARRAY_SIZE(cb_maps); i++) अणु
		map = &cb_maps[i];
		अगर (frequency < map->frequency)
			वापस map->cb;
	पूर्ण
	वापस 0xc0;
पूर्ण

अटल पूर्णांक qm1d1b0004_set_params(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा qm1d1b0004_state *state;
	u32 frequency, pll, lpf_freq;
	u16 word;
	u8 buf[4], cb, lpf;
	पूर्णांक ret;

	state = fe->tuner_priv;
	frequency = fe->dtv_property_cache.frequency;

	pll = QM1D1B0004_XTL_FREQ / 4;
	अगर (state->cfg.half_step)
		pll /= 2;
	word = DIV_ROUND_CLOSEST(frequency, pll);
	cb = lookup_cb(frequency);
	अगर (cb & QM1D1B0004_PSC_MASK)
		word = (word << 1 & ~0x1f) | (word & 0x0f);

	/* step.1: set frequency with BG:2, TM:0(4MHZ), LPF:4MHz */
	buf[0] = 0x40 | word >> 8;
	buf[1] = word;
	/* inconsisnten with the above I/F करोc. maybe the करोc is wrong */
	buf[2] = 0xe0 | state->cfg.half_step;
	buf[3] = cb;
	ret = i2c_master_send(state->i2c, buf, 4);
	अगर (ret < 0)
		वापस ret;

	/* step.2: set TM:1 */
	buf[0] = 0xe4 | state->cfg.half_step;
	ret = i2c_master_send(state->i2c, buf, 1);
	अगर (ret < 0)
		वापस ret;
	msleep(20);

	/* step.3: set LPF */
	lpf_freq = state->cfg.lpf_freq;
	अगर (lpf_freq == QM1D1B0004_CFG_LPF_DFLT)
		lpf_freq = fe->dtv_property_cache.symbol_rate / 1000;
	अगर (lpf_freq == 0)
		lpf_freq = QM1D1B0004_LPF_FALLBACK;
	lpf = DIV_ROUND_UP(lpf_freq, 2000) - 2;
	buf[0] = 0xe4 | ((lpf & 0x0c) << 1) | state->cfg.half_step;
	buf[1] = cb | ((lpf & 0x03) << 2);
	ret = i2c_master_send(state->i2c, buf, 2);
	अगर (ret < 0)
		वापस ret;

	/* step.4: पढ़ो PLL lock? */
	buf[0] = 0;
	ret = i2c_master_recv(state->i2c, buf, 1);
	अगर (ret < 0)
		वापस ret;
	वापस 0;
पूर्ण


अटल पूर्णांक qm1d1b0004_set_config(काष्ठा dvb_frontend *fe, व्योम *priv_cfg)
अणु
	काष्ठा qm1d1b0004_state *state;

	state = fe->tuner_priv;
	स_नकल(&state->cfg, priv_cfg, माप(state->cfg));
	वापस 0;
पूर्ण


अटल पूर्णांक qm1d1b0004_init(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा qm1d1b0004_state *state;
	u8 buf[2] = अणु0xf8, 0x04पूर्ण;

	state = fe->tuner_priv;
	अगर (state->cfg.half_step)
		buf[0] |= 0x01;

	वापस i2c_master_send(state->i2c, buf, 2);
पूर्ण


अटल स्थिर काष्ठा dvb_tuner_ops qm1d1b0004_ops = अणु
	.info = अणु
		.name = "Sharp qm1d1b0004",

		.frequency_min_hz =  950 * MHz,
		.frequency_max_hz = 2150 * MHz,
	पूर्ण,

	.init = qm1d1b0004_init,

	.set_params = qm1d1b0004_set_params,
	.set_config = qm1d1b0004_set_config,
पूर्ण;

अटल पूर्णांक
qm1d1b0004_probe(काष्ठा i2c_client *client, स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा dvb_frontend *fe;
	काष्ठा qm1d1b0004_config *cfg;
	काष्ठा qm1d1b0004_state *state;
	पूर्णांक ret;

	cfg = client->dev.platक्रमm_data;
	fe = cfg->fe;
	i2c_set_clientdata(client, fe);

	fe->tuner_priv = kzalloc(माप(काष्ठा qm1d1b0004_state), GFP_KERNEL);
	अगर (!fe->tuner_priv) अणु
		ret = -ENOMEM;
		जाओ err_mem;
	पूर्ण

	स_नकल(&fe->ops.tuner_ops, &qm1d1b0004_ops, माप(fe->ops.tuner_ops));

	state = fe->tuner_priv;
	state->i2c = client;
	ret = qm1d1b0004_set_config(fe, cfg);
	अगर (ret != 0)
		जाओ err_priv;

	dev_info(&client->dev, "Sharp QM1D1B0004 attached.\n");
	वापस 0;

err_priv:
	kमुक्त(fe->tuner_priv);
err_mem:
	fe->tuner_priv = शून्य;
	वापस ret;
पूर्ण

अटल पूर्णांक qm1d1b0004_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा dvb_frontend *fe;

	fe = i2c_get_clientdata(client);
	kमुक्त(fe->tuner_priv);
	fe->tuner_priv = शून्य;
	वापस 0;
पूर्ण


अटल स्थिर काष्ठा i2c_device_id qm1d1b0004_id[] = अणु
	अणु"qm1d1b0004", 0पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(i2c, qm1d1b0004_id);

अटल काष्ठा i2c_driver qm1d1b0004_driver = अणु
	.driver = अणु
		.name = "qm1d1b0004",
	पूर्ण,
	.probe    = qm1d1b0004_probe,
	.हटाओ   = qm1d1b0004_हटाओ,
	.id_table = qm1d1b0004_id,
पूर्ण;

module_i2c_driver(qm1d1b0004_driver);

MODULE_DESCRIPTION("Sharp QM1D1B0004");
MODULE_AUTHOR("Akihiro Tsukada");
MODULE_LICENSE("GPL");
