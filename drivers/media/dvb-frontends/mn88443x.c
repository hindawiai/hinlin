<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Socionext MN88443x series demodulator driver क्रम ISDB-S/ISDB-T.
//
// Copyright (c) 2018 Socionext Inc.

#समावेश <linux/bitfield.h>
#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/of_device.h>
#समावेश <linux/regmap.h>
#समावेश <media/dvb_गणित.स>

#समावेश "mn88443x.h"

/* ISDB-S रेजिस्टरs */
#घोषणा ATSIDU_S                                    0x2f
#घोषणा ATSIDL_S                                    0x30
#घोषणा TSSET_S                                     0x31
#घोषणा AGCREAD_S                                   0x5a
#घोषणा CPMON1_S                                    0x5e
#घोषणा   CPMON1_S_FSYNC                              BIT(5)
#घोषणा   CPMON1_S_ERRMON                             BIT(4)
#घोषणा   CPMON1_S_SIGOFF                             BIT(3)
#घोषणा   CPMON1_S_W2LOCK                             BIT(2)
#घोषणा   CPMON1_S_W1LOCK                             BIT(1)
#घोषणा   CPMON1_S_DW1LOCK                            BIT(0)
#घोषणा TRMON_S                                     0x60
#घोषणा BERCNFLG_S                                  0x68
#घोषणा   BERCNFLG_S_BERVRDY                          BIT(5)
#घोषणा   BERCNFLG_S_BERVCHK                          BIT(4)
#घोषणा   BERCNFLG_S_BERDRDY                          BIT(3)
#घोषणा   BERCNFLG_S_BERDCHK                          BIT(2)
#घोषणा CNRDXU_S                                    0x69
#घोषणा CNRDXL_S                                    0x6a
#घोषणा CNRDYU_S                                    0x6b
#घोषणा CNRDYL_S                                    0x6c
#घोषणा BERVRDU_S                                   0x71
#घोषणा BERVRDL_S                                   0x72
#घोषणा DOSET1_S                                    0x73

/* Primary ISDB-T */
#घोषणा PLLASET1                                    0x00
#घोषणा PLLASET2                                    0x01
#घोषणा PLLBSET1                                    0x02
#घोषणा PLLBSET2                                    0x03
#घोषणा PLLSET                                      0x04
#घोषणा OUTCSET                                     0x08
#घोषणा   OUTCSET_CHDRV_8MA                           0xff
#घोषणा   OUTCSET_CHDRV_4MA                           0x00
#घोषणा PLDWSET                                     0x09
#घोषणा   PLDWSET_NORMAL                             0x00
#घोषणा   PLDWSET_PULLDOWN                           0xff
#घोषणा HIZSET1                                     0x0a
#घोषणा HIZSET2                                     0x0b

/* Secondary ISDB-T (क्रम MN884434 only) */
#घोषणा RCVSET                                      0x00
#घोषणा TSSET1_M                                    0x01
#घोषणा TSSET2_M                                    0x02
#घोषणा TSSET3_M                                    0x03
#घोषणा INTACSET                                    0x08
#घोषणा HIZSET3                                     0x0b

/* ISDB-T रेजिस्टरs */
#घोषणा TSSET1                                      0x05
#घोषणा   TSSET1_TSASEL_MASK                          GENMASK(4, 3)
#घोषणा   TSSET1_TSASEL_ISDBT                         (0x0 << 3)
#घोषणा   TSSET1_TSASEL_ISDBS                         (0x1 << 3)
#घोषणा   TSSET1_TSASEL_NONE                          (0x2 << 3)
#घोषणा   TSSET1_TSBSEL_MASK                          GENMASK(2, 1)
#घोषणा   TSSET1_TSBSEL_ISDBS                         (0x0 << 1)
#घोषणा   TSSET1_TSBSEL_ISDBT                         (0x1 << 1)
#घोषणा   TSSET1_TSBSEL_NONE                          (0x2 << 1)
#घोषणा TSSET2                                      0x06
#घोषणा TSSET3                                      0x07
#घोषणा   TSSET3_INTASEL_MASK                         GENMASK(7, 6)
#घोषणा   TSSET3_INTASEL_T                            (0x0 << 6)
#घोषणा   TSSET3_INTASEL_S                            (0x1 << 6)
#घोषणा   TSSET3_INTASEL_NONE                         (0x2 << 6)
#घोषणा   TSSET3_INTBSEL_MASK                         GENMASK(5, 4)
#घोषणा   TSSET3_INTBSEL_S                            (0x0 << 4)
#घोषणा   TSSET3_INTBSEL_T                            (0x1 << 4)
#घोषणा   TSSET3_INTBSEL_NONE                         (0x2 << 4)
#घोषणा OUTSET2                                     0x0d
#घोषणा PWDSET                                      0x0f
#घोषणा   PWDSET_OFDMPD_MASK                          GENMASK(3, 2)
#घोषणा   PWDSET_OFDMPD_DOWN                          BIT(3)
#घोषणा   PWDSET_PSKPD_MASK                           GENMASK(1, 0)
#घोषणा   PWDSET_PSKPD_DOWN                           BIT(1)
#घोषणा CLKSET1_T                                   0x11
#घोषणा MDSET_T                                     0x13
#घोषणा   MDSET_T_MDAUTO_MASK                         GENMASK(7, 4)
#घोषणा   MDSET_T_MDAUTO_AUTO                         (0xf << 4)
#घोषणा   MDSET_T_MDAUTO_MANUAL                       (0x0 << 4)
#घोषणा   MDSET_T_FFTS_MASK                           GENMASK(3, 2)
#घोषणा   MDSET_T_FFTS_MODE1                          (0x0 << 2)
#घोषणा   MDSET_T_FFTS_MODE2                          (0x1 << 2)
#घोषणा   MDSET_T_FFTS_MODE3                          (0x2 << 2)
#घोषणा   MDSET_T_GI_MASK                             GENMASK(1, 0)
#घोषणा   MDSET_T_GI_1_32                             (0x0 << 0)
#घोषणा   MDSET_T_GI_1_16                             (0x1 << 0)
#घोषणा   MDSET_T_GI_1_8                              (0x2 << 0)
#घोषणा   MDSET_T_GI_1_4                              (0x3 << 0)
#घोषणा MDASET_T                                    0x14
#घोषणा ADCSET1_T                                   0x20
#घोषणा   ADCSET1_T_REFSEL_MASK                       GENMASK(1, 0)
#घोषणा   ADCSET1_T_REFSEL_2V                         (0x3 << 0)
#घोषणा   ADCSET1_T_REFSEL_1_5V                       (0x2 << 0)
#घोषणा   ADCSET1_T_REFSEL_1V                         (0x1 << 0)
#घोषणा NCOFREQU_T                                  0x24
#घोषणा NCOFREQM_T                                  0x25
#घोषणा NCOFREQL_T                                  0x26
#घोषणा FADU_T                                      0x27
#घोषणा FADM_T                                      0x28
#घोषणा FADL_T                                      0x29
#घोषणा AGCSET2_T                                   0x2c
#घोषणा   AGCSET2_T_IFPOLINV_INC                      BIT(0)
#घोषणा   AGCSET2_T_RFPOLINV_INC                      BIT(1)
#घोषणा AGCV3_T                                     0x3e
#घोषणा MDRD_T                                      0xa2
#घोषणा   MDRD_T_SEGID_MASK                           GENMASK(5, 4)
#घोषणा   MDRD_T_SEGID_13                             (0x0 << 4)
#घोषणा   MDRD_T_SEGID_1                              (0x1 << 4)
#घोषणा   MDRD_T_SEGID_3                              (0x2 << 4)
#घोषणा   MDRD_T_FFTS_MASK                            GENMASK(3, 2)
#घोषणा   MDRD_T_FFTS_MODE1                           (0x0 << 2)
#घोषणा   MDRD_T_FFTS_MODE2                           (0x1 << 2)
#घोषणा   MDRD_T_FFTS_MODE3                           (0x2 << 2)
#घोषणा   MDRD_T_GI_MASK                              GENMASK(1, 0)
#घोषणा   MDRD_T_GI_1_32                              (0x0 << 0)
#घोषणा   MDRD_T_GI_1_16                              (0x1 << 0)
#घोषणा   MDRD_T_GI_1_8                               (0x2 << 0)
#घोषणा   MDRD_T_GI_1_4                               (0x3 << 0)
#घोषणा SSEQRD_T                                    0xa3
#घोषणा   SSEQRD_T_SSEQSTRD_MASK                      GENMASK(3, 0)
#घोषणा   SSEQRD_T_SSEQSTRD_RESET                     (0x0 << 0)
#घोषणा   SSEQRD_T_SSEQSTRD_TUNING                    (0x1 << 0)
#घोषणा   SSEQRD_T_SSEQSTRD_AGC                       (0x2 << 0)
#घोषणा   SSEQRD_T_SSEQSTRD_SEARCH                    (0x3 << 0)
#घोषणा   SSEQRD_T_SSEQSTRD_CLOCK_SYNC                (0x4 << 0)
#घोषणा   SSEQRD_T_SSEQSTRD_FREQ_SYNC                 (0x8 << 0)
#घोषणा   SSEQRD_T_SSEQSTRD_FRAME_SYNC                (0x9 << 0)
#घोषणा   SSEQRD_T_SSEQSTRD_SYNC                      (0xa << 0)
#घोषणा   SSEQRD_T_SSEQSTRD_LOCK                      (0xb << 0)
#घोषणा AGCRDU_T                                    0xa8
#घोषणा AGCRDL_T                                    0xa9
#घोषणा CNRDU_T                                     0xbe
#घोषणा CNRDL_T                                     0xbf
#घोषणा BERFLG_T                                    0xc0
#घोषणा   BERFLG_T_BERDRDY                            BIT(7)
#घोषणा   BERFLG_T_BERDCHK                            BIT(6)
#घोषणा   BERFLG_T_BERVRDYA                           BIT(5)
#घोषणा   BERFLG_T_BERVCHKA                           BIT(4)
#घोषणा   BERFLG_T_BERVRDYB                           BIT(3)
#घोषणा   BERFLG_T_BERVCHKB                           BIT(2)
#घोषणा   BERFLG_T_BERVRDYC                           BIT(1)
#घोषणा   BERFLG_T_BERVCHKC                           BIT(0)
#घोषणा BERRDU_T                                    0xc1
#घोषणा BERRDM_T                                    0xc2
#घोषणा BERRDL_T                                    0xc3
#घोषणा BERLENRDU_T                                 0xc4
#घोषणा BERLENRDL_T                                 0xc5
#घोषणा ERRFLG_T                                    0xc6
#घोषणा   ERRFLG_T_BERDOVF                            BIT(7)
#घोषणा   ERRFLG_T_BERVOVFA                           BIT(6)
#घोषणा   ERRFLG_T_BERVOVFB                           BIT(5)
#घोषणा   ERRFLG_T_BERVOVFC                           BIT(4)
#घोषणा   ERRFLG_T_NERRFA                             BIT(3)
#घोषणा   ERRFLG_T_NERRFB                             BIT(2)
#घोषणा   ERRFLG_T_NERRFC                             BIT(1)
#घोषणा   ERRFLG_T_NERRF                              BIT(0)
#घोषणा DOSET1_T                                    0xcf

#घोषणा CLK_LOW            4000000
#घोषणा CLK_सूचीECT         20200000
#घोषणा CLK_MAX            25410000

#घोषणा S_T_FREQ           8126984 /* 512 / 63 MHz */

काष्ठा mn88443x_spec अणु
	bool primary;
पूर्ण;

काष्ठा mn88443x_priv अणु
	स्थिर काष्ठा mn88443x_spec *spec;

	काष्ठा dvb_frontend fe;
	काष्ठा clk *mclk;
	काष्ठा gpio_desc *reset_gpio;
	u32 clk_freq;
	u32 अगर_freq;

	/* Common */
	bool use_clkbuf;

	/* ISDB-S */
	काष्ठा i2c_client *client_s;
	काष्ठा regmap *regmap_s;

	/* ISDB-T */
	काष्ठा i2c_client *client_t;
	काष्ठा regmap *regmap_t;
पूर्ण;

अटल व्योम mn88443x_cmn_घातer_on(काष्ठा mn88443x_priv *chip)
अणु
	काष्ठा regmap *r_t = chip->regmap_t;

	clk_prepare_enable(chip->mclk);

	gpiod_set_value_cansleep(chip->reset_gpio, 1);
	usleep_range(100, 1000);
	gpiod_set_value_cansleep(chip->reset_gpio, 0);

	अगर (chip->spec->primary) अणु
		regmap_ग_लिखो(r_t, OUTCSET, OUTCSET_CHDRV_8MA);
		regmap_ग_लिखो(r_t, PLDWSET, PLDWSET_NORMAL);
		regmap_ग_लिखो(r_t, HIZSET1, 0x80);
		regmap_ग_लिखो(r_t, HIZSET2, 0xe0);
	पूर्ण अन्यथा अणु
		regmap_ग_लिखो(r_t, HIZSET3, 0x8f);
	पूर्ण
पूर्ण

अटल व्योम mn88443x_cmn_घातer_off(काष्ठा mn88443x_priv *chip)
अणु
	gpiod_set_value_cansleep(chip->reset_gpio, 1);

	clk_disable_unprepare(chip->mclk);
पूर्ण

अटल व्योम mn88443x_s_sleep(काष्ठा mn88443x_priv *chip)
अणु
	काष्ठा regmap *r_t = chip->regmap_t;

	regmap_update_bits(r_t, PWDSET, PWDSET_PSKPD_MASK,
			   PWDSET_PSKPD_DOWN);
पूर्ण

अटल व्योम mn88443x_s_wake(काष्ठा mn88443x_priv *chip)
अणु
	काष्ठा regmap *r_t = chip->regmap_t;

	regmap_update_bits(r_t, PWDSET, PWDSET_PSKPD_MASK, 0);
पूर्ण

अटल व्योम mn88443x_s_tune(काष्ठा mn88443x_priv *chip,
			    काष्ठा dtv_frontend_properties *c)
अणु
	काष्ठा regmap *r_s = chip->regmap_s;

	regmap_ग_लिखो(r_s, ATSIDU_S, c->stream_id >> 8);
	regmap_ग_लिखो(r_s, ATSIDL_S, c->stream_id);
	regmap_ग_लिखो(r_s, TSSET_S, 0);
पूर्ण

अटल पूर्णांक mn88443x_s_पढ़ो_status(काष्ठा mn88443x_priv *chip,
				  काष्ठा dtv_frontend_properties *c,
				  क्रमागत fe_status *status)
अणु
	काष्ठा regmap *r_s = chip->regmap_s;
	u32 cpmon, पंचांगpu, पंचांगpl, flg;
	u64 पंचांगp;

	/* Sync detection */
	regmap_पढ़ो(r_s, CPMON1_S, &cpmon);

	*status = 0;
	अगर (cpmon & CPMON1_S_FSYNC)
		*status |= FE_HAS_VITERBI | FE_HAS_SYNC | FE_HAS_LOCK;
	अगर (cpmon & CPMON1_S_W2LOCK)
		*status |= FE_HAS_SIGNAL | FE_HAS_CARRIER;

	/* Signal strength */
	c->strength.stat[0].scale = FE_SCALE_NOT_AVAILABLE;

	अगर (*status & FE_HAS_SIGNAL) अणु
		u32 agc;

		regmap_पढ़ो(r_s, AGCREAD_S, &पंचांगpu);
		agc = पंचांगpu << 8;

		c->strength.len = 1;
		c->strength.stat[0].scale = FE_SCALE_RELATIVE;
		c->strength.stat[0].uvalue = agc;
	पूर्ण

	/* C/N rate */
	c->cnr.stat[0].scale = FE_SCALE_NOT_AVAILABLE;

	अगर (*status & FE_HAS_VITERBI) अणु
		u32 cnr = 0, x, y, d;
		u64 d_3 = 0;

		regmap_पढ़ो(r_s, CNRDXU_S, &पंचांगpu);
		regmap_पढ़ो(r_s, CNRDXL_S, &पंचांगpl);
		x = (पंचांगpu << 8) | पंचांगpl;
		regmap_पढ़ो(r_s, CNRDYU_S, &पंचांगpu);
		regmap_पढ़ो(r_s, CNRDYL_S, &पंचांगpl);
		y = (पंचांगpu << 8) | पंचांगpl;

		/* CNR[dB]: 10 * log10(D) - 30.74 / D^3 - 3 */
		/*   D = x^2 / (2^15 * y - x^2) */
		d = (y << 15) - x * x;
		अगर (d > 0) अणु
			/* (2^4 * D)^3 = 2^12 * D^3 */
			/* 3.074 * 2^(12 + 24) = 211243671486 */
			d_3 = भाग_u64(16 * x * x, d);
			d_3 = d_3 * d_3 * d_3;
			अगर (d_3)
				d_3 = भाग_u64(211243671486ULL, d_3);
		पूर्ण

		अगर (d_3) अणु
			/* 0.3 * 2^24 = 5033164 */
			पंचांगp = (s64)2 * पूर्णांकlog10(x) - पूर्णांकlog10(असल(d)) - d_3
				- 5033164;
			cnr = भाग_u64(पंचांगp * 10000, 1 << 24);
		पूर्ण

		अगर (cnr) अणु
			c->cnr.len = 1;
			c->cnr.stat[0].scale = FE_SCALE_DECIBEL;
			c->cnr.stat[0].uvalue = cnr;
		पूर्ण
	पूर्ण

	/* BER */
	c->post_bit_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	c->post_bit_count.stat[0].scale = FE_SCALE_NOT_AVAILABLE;

	regmap_पढ़ो(r_s, BERCNFLG_S, &flg);

	अगर ((*status & FE_HAS_VITERBI) && (flg & BERCNFLG_S_BERVRDY)) अणु
		u32 bit_err, bit_cnt;

		regmap_पढ़ो(r_s, BERVRDU_S, &पंचांगpu);
		regmap_पढ़ो(r_s, BERVRDL_S, &पंचांगpl);
		bit_err = (पंचांगpu << 8) | पंचांगpl;
		bit_cnt = (1 << 13) * 204;

		अगर (bit_cnt) अणु
			c->post_bit_error.len = 1;
			c->post_bit_error.stat[0].scale = FE_SCALE_COUNTER;
			c->post_bit_error.stat[0].uvalue = bit_err;
			c->post_bit_count.len = 1;
			c->post_bit_count.stat[0].scale = FE_SCALE_COUNTER;
			c->post_bit_count.stat[0].uvalue = bit_cnt;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम mn88443x_t_sleep(काष्ठा mn88443x_priv *chip)
अणु
	काष्ठा regmap *r_t = chip->regmap_t;

	regmap_update_bits(r_t, PWDSET, PWDSET_OFDMPD_MASK,
			   PWDSET_OFDMPD_DOWN);
पूर्ण

अटल व्योम mn88443x_t_wake(काष्ठा mn88443x_priv *chip)
अणु
	काष्ठा regmap *r_t = chip->regmap_t;

	regmap_update_bits(r_t, PWDSET, PWDSET_OFDMPD_MASK, 0);
पूर्ण

अटल bool mn88443x_t_is_valid_clk(u32 adckt, u32 अगर_freq)
अणु
	अगर (अगर_freq == सूचीECT_IF_57MHZ) अणु
		अगर (adckt >= CLK_सूचीECT && adckt <= 21000000)
			वापस true;
		अगर (adckt >= 25300000 && adckt <= CLK_MAX)
			वापस true;
	पूर्ण अन्यथा अगर (अगर_freq == सूचीECT_IF_44MHZ) अणु
		अगर (adckt >= 25000000 && adckt <= CLK_MAX)
			वापस true;
	पूर्ण अन्यथा अगर (अगर_freq >= LOW_IF_4MHZ && अगर_freq < सूचीECT_IF_44MHZ) अणु
		अगर (adckt >= CLK_सूचीECT && adckt <= CLK_MAX)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक mn88443x_t_set_freq(काष्ठा mn88443x_priv *chip)
अणु
	काष्ठा device *dev = &chip->client_s->dev;
	काष्ठा regmap *r_t = chip->regmap_t;
	s64 adckt, nco, ad_t;
	u32 m, v;

	/* Clock buffer (but not supported) or XTAL */
	अगर (chip->clk_freq >= CLK_LOW && chip->clk_freq < CLK_सूचीECT) अणु
		chip->use_clkbuf = true;
		regmap_ग_लिखो(r_t, CLKSET1_T, 0x07);

		adckt = 0;
	पूर्ण अन्यथा अणु
		chip->use_clkbuf = false;
		regmap_ग_लिखो(r_t, CLKSET1_T, 0x00);

		adckt = chip->clk_freq;
	पूर्ण
	अगर (!mn88443x_t_is_valid_clk(adckt, chip->अगर_freq)) अणु
		dev_err(dev, "Invalid clock, CLK:%d, ADCKT:%lld, IF:%d\n",
			chip->clk_freq, adckt, chip->अगर_freq);
		वापस -EINVAL;
	पूर्ण

	/* Direct IF or Low IF */
	अगर (chip->अगर_freq == सूचीECT_IF_57MHZ ||
	    chip->अगर_freq == सूचीECT_IF_44MHZ)
		nco = adckt * 2 - chip->अगर_freq;
	अन्यथा
		nco = -((s64)chip->अगर_freq);
	nco = भाग_s64(nco << 24, adckt);
	ad_t = भाग_s64(adckt << 22, S_T_FREQ);

	regmap_ग_लिखो(r_t, NCOFREQU_T, nco >> 16);
	regmap_ग_लिखो(r_t, NCOFREQM_T, nco >> 8);
	regmap_ग_लिखो(r_t, NCOFREQL_T, nco);
	regmap_ग_लिखो(r_t, FADU_T, ad_t >> 16);
	regmap_ग_लिखो(r_t, FADM_T, ad_t >> 8);
	regmap_ग_लिखो(r_t, FADL_T, ad_t);

	/* Level of IF */
	m = ADCSET1_T_REFSEL_MASK;
	v = ADCSET1_T_REFSEL_1_5V;
	regmap_update_bits(r_t, ADCSET1_T, m, v);

	/* Polarity of AGC */
	v = AGCSET2_T_IFPOLINV_INC | AGCSET2_T_RFPOLINV_INC;
	regmap_update_bits(r_t, AGCSET2_T, v, v);

	/* Lower output level of AGC */
	regmap_ग_लिखो(r_t, AGCV3_T, 0x00);

	regmap_ग_लिखो(r_t, MDSET_T, 0xfa);

	वापस 0;
पूर्ण

अटल व्योम mn88443x_t_tune(काष्ठा mn88443x_priv *chip,
			    काष्ठा dtv_frontend_properties *c)
अणु
	काष्ठा regmap *r_t = chip->regmap_t;
	u32 m, v;

	m = MDSET_T_MDAUTO_MASK | MDSET_T_FFTS_MASK | MDSET_T_GI_MASK;
	v = MDSET_T_MDAUTO_AUTO | MDSET_T_FFTS_MODE3 | MDSET_T_GI_1_8;
	regmap_update_bits(r_t, MDSET_T, m, v);

	regmap_ग_लिखो(r_t, MDASET_T, 0);
पूर्ण

अटल पूर्णांक mn88443x_t_पढ़ो_status(काष्ठा mn88443x_priv *chip,
				  काष्ठा dtv_frontend_properties *c,
				  क्रमागत fe_status *status)
अणु
	काष्ठा regmap *r_t = chip->regmap_t;
	u32 seqrd, st, flg, पंचांगpu, पंचांगpm, पंचांगpl;
	u64 पंचांगp;

	/* Sync detection */
	regmap_पढ़ो(r_t, SSEQRD_T, &seqrd);
	st = seqrd & SSEQRD_T_SSEQSTRD_MASK;

	*status = 0;
	अगर (st >= SSEQRD_T_SSEQSTRD_SYNC)
		*status |= FE_HAS_VITERBI | FE_HAS_SYNC | FE_HAS_LOCK;
	अगर (st >= SSEQRD_T_SSEQSTRD_FRAME_SYNC)
		*status |= FE_HAS_SIGNAL | FE_HAS_CARRIER;

	/* Signal strength */
	c->strength.stat[0].scale = FE_SCALE_NOT_AVAILABLE;

	अगर (*status & FE_HAS_SIGNAL) अणु
		u32 agc;

		regmap_पढ़ो(r_t, AGCRDU_T, &पंचांगpu);
		regmap_पढ़ो(r_t, AGCRDL_T, &पंचांगpl);
		agc = (पंचांगpu << 8) | पंचांगpl;

		c->strength.len = 1;
		c->strength.stat[0].scale = FE_SCALE_RELATIVE;
		c->strength.stat[0].uvalue = agc;
	पूर्ण

	/* C/N rate */
	c->cnr.stat[0].scale = FE_SCALE_NOT_AVAILABLE;

	अगर (*status & FE_HAS_VITERBI) अणु
		u32 cnr;

		regmap_पढ़ो(r_t, CNRDU_T, &पंचांगpu);
		regmap_पढ़ो(r_t, CNRDL_T, &पंचांगpl);

		अगर (पंचांगpu || पंचांगpl) अणु
			/* CNR[dB]: 10 * (log10(65536 / value) + 0.2) */
			/* पूर्णांकlog10(65536) = 80807124, 0.2 * 2^24 = 3355443 */
			पंचांगp = (u64)80807124 - पूर्णांकlog10((पंचांगpu << 8) | पंचांगpl)
				+ 3355443;
			cnr = भाग_u64(पंचांगp * 10000, 1 << 24);
		पूर्ण अन्यथा अणु
			cnr = 0;
		पूर्ण

		c->cnr.len = 1;
		c->cnr.stat[0].scale = FE_SCALE_DECIBEL;
		c->cnr.stat[0].uvalue = cnr;
	पूर्ण

	/* BER */
	c->post_bit_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	c->post_bit_count.stat[0].scale = FE_SCALE_NOT_AVAILABLE;

	regmap_पढ़ो(r_t, BERFLG_T, &flg);

	अगर ((*status & FE_HAS_VITERBI) && (flg & BERFLG_T_BERVRDYA)) अणु
		u32 bit_err, bit_cnt;

		regmap_पढ़ो(r_t, BERRDU_T, &पंचांगpu);
		regmap_पढ़ो(r_t, BERRDM_T, &पंचांगpm);
		regmap_पढ़ो(r_t, BERRDL_T, &पंचांगpl);
		bit_err = (पंचांगpu << 16) | (पंचांगpm << 8) | पंचांगpl;

		regmap_पढ़ो(r_t, BERLENRDU_T, &पंचांगpu);
		regmap_पढ़ो(r_t, BERLENRDL_T, &पंचांगpl);
		bit_cnt = ((पंचांगpu << 8) | पंचांगpl) * 203 * 8;

		अगर (bit_cnt) अणु
			c->post_bit_error.len = 1;
			c->post_bit_error.stat[0].scale = FE_SCALE_COUNTER;
			c->post_bit_error.stat[0].uvalue = bit_err;
			c->post_bit_count.len = 1;
			c->post_bit_count.stat[0].scale = FE_SCALE_COUNTER;
			c->post_bit_count.stat[0].uvalue = bit_cnt;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mn88443x_sleep(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा mn88443x_priv *chip = fe->demodulator_priv;

	mn88443x_s_sleep(chip);
	mn88443x_t_sleep(chip);

	वापस 0;
पूर्ण

अटल पूर्णांक mn88443x_set_frontend(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा mn88443x_priv *chip = fe->demodulator_priv;
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	काष्ठा regmap *r_s = chip->regmap_s;
	काष्ठा regmap *r_t = chip->regmap_t;
	u8 tssel = 0, पूर्णांकsel = 0;

	अगर (c->delivery_प्रणाली == SYS_ISDBS) अणु
		mn88443x_s_wake(chip);
		mn88443x_t_sleep(chip);

		tssel = TSSET1_TSASEL_ISDBS;
		पूर्णांकsel = TSSET3_INTASEL_S;
	पूर्ण अन्यथा अगर (c->delivery_प्रणाली == SYS_ISDBT) अणु
		mn88443x_s_sleep(chip);
		mn88443x_t_wake(chip);

		mn88443x_t_set_freq(chip);

		tssel = TSSET1_TSASEL_ISDBT;
		पूर्णांकsel = TSSET3_INTASEL_T;
	पूर्ण

	regmap_update_bits(r_t, TSSET1,
			   TSSET1_TSASEL_MASK | TSSET1_TSBSEL_MASK,
			   tssel | TSSET1_TSBSEL_NONE);
	regmap_ग_लिखो(r_t, TSSET2, 0);
	regmap_update_bits(r_t, TSSET3,
			   TSSET3_INTASEL_MASK | TSSET3_INTBSEL_MASK,
			   पूर्णांकsel | TSSET3_INTBSEL_NONE);

	regmap_ग_लिखो(r_t, DOSET1_T, 0x95);
	regmap_ग_लिखो(r_s, DOSET1_S, 0x80);

	अगर (c->delivery_प्रणाली == SYS_ISDBS)
		mn88443x_s_tune(chip, c);
	अन्यथा अगर (c->delivery_प्रणाली == SYS_ISDBT)
		mn88443x_t_tune(chip, c);

	अगर (fe->ops.tuner_ops.set_params) अणु
		अगर (fe->ops.i2c_gate_ctrl)
			fe->ops.i2c_gate_ctrl(fe, 1);
		fe->ops.tuner_ops.set_params(fe);
		अगर (fe->ops.i2c_gate_ctrl)
			fe->ops.i2c_gate_ctrl(fe, 0);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mn88443x_get_tune_settings(काष्ठा dvb_frontend *fe,
				      काष्ठा dvb_frontend_tune_settings *s)
अणु
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;

	s->min_delay_ms = 850;

	अगर (c->delivery_प्रणाली == SYS_ISDBS) अणु
		s->max_drअगरt = 30000 * 2 + 1;
		s->step_size = 30000;
	पूर्ण अन्यथा अगर (c->delivery_प्रणाली == SYS_ISDBT) अणु
		s->max_drअगरt = 142857 * 2 + 1;
		s->step_size = 142857 * 2;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mn88443x_पढ़ो_status(काष्ठा dvb_frontend *fe, क्रमागत fe_status *status)
अणु
	काष्ठा mn88443x_priv *chip = fe->demodulator_priv;
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;

	अगर (c->delivery_प्रणाली == SYS_ISDBS)
		वापस mn88443x_s_पढ़ो_status(chip, c, status);

	अगर (c->delivery_प्रणाली == SYS_ISDBT)
		वापस mn88443x_t_पढ़ो_status(chip, c, status);

	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा dvb_frontend_ops mn88443x_ops = अणु
	.delsys = अणु SYS_ISDBS, SYS_ISDBT पूर्ण,
	.info = अणु
		.name = "Socionext MN88443x",
		.frequency_min_hz =  470 * MHz,
		.frequency_max_hz = 2071 * MHz,
		.symbol_rate_min  = 28860000,
		.symbol_rate_max  = 28860000,
		.caps = FE_CAN_INVERSION_AUTO | FE_CAN_FEC_AUTO |
			FE_CAN_QAM_AUTO | FE_CAN_TRANSMISSION_MODE_AUTO |
			FE_CAN_GUARD_INTERVAL_AUTO | FE_CAN_HIERARCHY_AUTO,
	पूर्ण,

	.sleep                   = mn88443x_sleep,
	.set_frontend            = mn88443x_set_frontend,
	.get_tune_settings       = mn88443x_get_tune_settings,
	.पढ़ो_status             = mn88443x_पढ़ो_status,
पूर्ण;

अटल स्थिर काष्ठा regmap_config regmap_config = अणु
	.reg_bits   = 8,
	.val_bits   = 8,
	.cache_type = REGCACHE_NONE,
पूर्ण;

अटल पूर्णांक mn88443x_probe(काष्ठा i2c_client *client,
			  स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा mn88443x_config *conf = client->dev.platक्रमm_data;
	काष्ठा mn88443x_priv *chip;
	काष्ठा device *dev = &client->dev;
	पूर्णांक ret;

	chip = devm_kzalloc(dev, माप(*chip), GFP_KERNEL);
	अगर (!chip)
		वापस -ENOMEM;

	अगर (dev->of_node)
		chip->spec = of_device_get_match_data(dev);
	अन्यथा
		chip->spec = (काष्ठा mn88443x_spec *)id->driver_data;
	अगर (!chip->spec)
		वापस -EINVAL;

	chip->mclk = devm_clk_get(dev, "mclk");
	अगर (IS_ERR(chip->mclk) && !conf) अणु
		dev_err(dev, "Failed to request mclk: %ld\n",
			PTR_ERR(chip->mclk));
		वापस PTR_ERR(chip->mclk);
	पूर्ण

	ret = of_property_पढ़ो_u32(dev->of_node, "if-frequency",
				   &chip->अगर_freq);
	अगर (ret && !conf) अणु
		dev_err(dev, "Failed to load IF frequency: %d.\n", ret);
		वापस ret;
	पूर्ण

	chip->reset_gpio = devm_gpiod_get_optional(dev, "reset",
						   GPIOD_OUT_HIGH);
	अगर (IS_ERR(chip->reset_gpio)) अणु
		dev_err(dev, "Failed to request reset_gpio: %ld\n",
			PTR_ERR(chip->reset_gpio));
		वापस PTR_ERR(chip->reset_gpio);
	पूर्ण

	अगर (conf) अणु
		chip->mclk = conf->mclk;
		chip->अगर_freq = conf->अगर_freq;
		chip->reset_gpio = conf->reset_gpio;

		*conf->fe = &chip->fe;
	पूर्ण

	chip->client_s = client;
	chip->regmap_s = devm_regmap_init_i2c(chip->client_s, &regmap_config);
	अगर (IS_ERR(chip->regmap_s))
		वापस PTR_ERR(chip->regmap_s);

	/*
	 * Chip has two I2C addresses क्रम each satellite/terrestrial प्रणाली.
	 * ISDB-T uses address ISDB-S + 4, so we रेजिस्टर a dummy client.
	 */
	chip->client_t = i2c_new_dummy_device(client->adapter, client->addr + 4);
	अगर (IS_ERR(chip->client_t))
		वापस PTR_ERR(chip->client_t);

	chip->regmap_t = devm_regmap_init_i2c(chip->client_t, &regmap_config);
	अगर (IS_ERR(chip->regmap_t)) अणु
		ret = PTR_ERR(chip->regmap_t);
		जाओ err_i2c_t;
	पूर्ण

	chip->clk_freq = clk_get_rate(chip->mclk);

	स_नकल(&chip->fe.ops, &mn88443x_ops, माप(mn88443x_ops));
	chip->fe.demodulator_priv = chip;
	i2c_set_clientdata(client, chip);

	mn88443x_cmn_घातer_on(chip);
	mn88443x_s_sleep(chip);
	mn88443x_t_sleep(chip);

	वापस 0;

err_i2c_t:
	i2c_unरेजिस्टर_device(chip->client_t);

	वापस ret;
पूर्ण

अटल पूर्णांक mn88443x_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा mn88443x_priv *chip = i2c_get_clientdata(client);

	mn88443x_cmn_घातer_off(chip);

	i2c_unरेजिस्टर_device(chip->client_t);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा mn88443x_spec mn88443x_spec_pri = अणु
	.primary = true,
पूर्ण;

अटल स्थिर काष्ठा mn88443x_spec mn88443x_spec_sec = अणु
	.primary = false,
पूर्ण;

अटल स्थिर काष्ठा of_device_id mn88443x_of_match[] = अणु
	अणु .compatible = "socionext,mn884433",   .data = &mn88443x_spec_pri, पूर्ण,
	अणु .compatible = "socionext,mn884434-0", .data = &mn88443x_spec_pri, पूर्ण,
	अणु .compatible = "socionext,mn884434-1", .data = &mn88443x_spec_sec, पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, mn88443x_of_match);

अटल स्थिर काष्ठा i2c_device_id mn88443x_i2c_id[] = अणु
	अणु "mn884433",   (kernel_uदीर्घ_t)&mn88443x_spec_pri पूर्ण,
	अणु "mn884434-0", (kernel_uदीर्घ_t)&mn88443x_spec_pri पूर्ण,
	अणु "mn884434-1", (kernel_uदीर्घ_t)&mn88443x_spec_sec पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, mn88443x_i2c_id);

अटल काष्ठा i2c_driver mn88443x_driver = अणु
	.driver = अणु
		.name = "mn88443x",
		.of_match_table = of_match_ptr(mn88443x_of_match),
	पूर्ण,
	.probe    = mn88443x_probe,
	.हटाओ   = mn88443x_हटाओ,
	.id_table = mn88443x_i2c_id,
पूर्ण;

module_i2c_driver(mn88443x_driver);

MODULE_AUTHOR("Katsuhiro Suzuki <suzuki.katsuhiro@socionext.com>");
MODULE_DESCRIPTION("Socionext MN88443x series demodulator driver.");
MODULE_LICENSE("GPL v2");
