<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* ZD1211 USB-WLAN driver क्रम Linux
 *
 * Copyright (C) 2005-2007 Ulrich Kunitz <kune@deine-taler.de>
 * Copyright (C) 2006-2007 Daniel Drake <dsd@gentoo.org>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>

#समावेश "zd_rf.h"
#समावेश "zd_usb.h"
#समावेश "zd_chip.h"

/* This RF programming code is based upon the code found in v2.16.0.0 of the
 * ZyDAS venकरोr driver. Unlike other RF's, Ubec publish full technical specs
 * क्रम this RF on their website, so we're able to understand more than
 * usual as to what is going on. Thumbs up क्रम Ubec क्रम करोing that. */

/* The 3-wire serial पूर्णांकerface provides access to 8 ग_लिखो-only रेजिस्टरs.
 * The data क्रमmat is a 4 bit रेजिस्टर address followed by a 20 bit value. */
#घोषणा UW2453_REGWRITE(reg, val) ((((reg) & 0xf) << 20) | ((val) & 0xfffff))

/* For channel tuning, we have to configure रेजिस्टरs 1 (synthesizer), 2 (synth
 * fractional भागide ratio) and 3 (VCO config).
 *
 * We configure the RF to produce an पूर्णांकerrupt when the PLL is locked onto
 * the configured frequency. During initialization, we run through a variety
 * of dअगरferent VCO configurations on channel 1 until we detect a PLL lock.
 * When this happens, we remember which VCO configuration produced the lock
 * and use it later. Actually, we use the configuration *after* the one that
 * produced the lock, which seems odd, but it works.
 *
 * If we करो not see a PLL lock on any standard VCO config, we fall back on an
 * स्वतःcal configuration, which has a fixed (as opposed to per-channel) VCO
 * config and dअगरferent synth values from the standard set (भागide ratio
 * is still shared with the standard set). */

/* The per-channel synth values क्रम all standard VCO configurations. These get
 * written to रेजिस्टर 1. */
अटल स्थिर u8 uw2453_std_synth[] = अणु
	RF_CHANNEL( 1) = 0x47,
	RF_CHANNEL( 2) = 0x47,
	RF_CHANNEL( 3) = 0x67,
	RF_CHANNEL( 4) = 0x67,
	RF_CHANNEL( 5) = 0x67,
	RF_CHANNEL( 6) = 0x67,
	RF_CHANNEL( 7) = 0x57,
	RF_CHANNEL( 8) = 0x57,
	RF_CHANNEL( 9) = 0x57,
	RF_CHANNEL(10) = 0x57,
	RF_CHANNEL(11) = 0x77,
	RF_CHANNEL(12) = 0x77,
	RF_CHANNEL(13) = 0x77,
	RF_CHANNEL(14) = 0x4f,
पूर्ण;

/* This table stores the synthesizer fractional भागide ratio क्रम *all* VCO
 * configurations (both standard and स्वतःcal). These get written to रेजिस्टर 2.
 */
अटल स्थिर u16 uw2453_synth_भागide[] = अणु
	RF_CHANNEL( 1) = 0x999,
	RF_CHANNEL( 2) = 0x99b,
	RF_CHANNEL( 3) = 0x998,
	RF_CHANNEL( 4) = 0x99a,
	RF_CHANNEL( 5) = 0x999,
	RF_CHANNEL( 6) = 0x99b,
	RF_CHANNEL( 7) = 0x998,
	RF_CHANNEL( 8) = 0x99a,
	RF_CHANNEL( 9) = 0x999,
	RF_CHANNEL(10) = 0x99b,
	RF_CHANNEL(11) = 0x998,
	RF_CHANNEL(12) = 0x99a,
	RF_CHANNEL(13) = 0x999,
	RF_CHANNEL(14) = 0xccc,
पूर्ण;

/* Here is the data क्रम all the standard VCO configurations. We shrink our
 * table a little by observing that both channels in a consecutive pair share
 * the same value. We also observe that the high 4 bits ([0:3] in the specs)
 * are all 'Reserved' and are always set to 0x4 - we chop them off in the data
 * below. */
#घोषणा CHAN_TO_PAIRIDX(a) ((a - 1) / 2)
#घोषणा RF_CHANPAIR(a,b) [CHAN_TO_PAIRIDX(a)]
अटल स्थिर u16 uw2453_std_vco_cfg[][7] = अणु
	अणु /* table 1 */
		RF_CHANPAIR( 1,  2) = 0x664d,
		RF_CHANPAIR( 3,  4) = 0x604d,
		RF_CHANPAIR( 5,  6) = 0x6675,
		RF_CHANPAIR( 7,  8) = 0x6475,
		RF_CHANPAIR( 9, 10) = 0x6655,
		RF_CHANPAIR(11, 12) = 0x6455,
		RF_CHANPAIR(13, 14) = 0x6665,
	पूर्ण,
	अणु /* table 2 */
		RF_CHANPAIR( 1,  2) = 0x666d,
		RF_CHANPAIR( 3,  4) = 0x606d,
		RF_CHANPAIR( 5,  6) = 0x664d,
		RF_CHANPAIR( 7,  8) = 0x644d,
		RF_CHANPAIR( 9, 10) = 0x6675,
		RF_CHANPAIR(11, 12) = 0x6475,
		RF_CHANPAIR(13, 14) = 0x6655,
	पूर्ण,
	अणु /* table 3 */
		RF_CHANPAIR( 1,  2) = 0x665d,
		RF_CHANPAIR( 3,  4) = 0x605d,
		RF_CHANPAIR( 5,  6) = 0x666d,
		RF_CHANPAIR( 7,  8) = 0x646d,
		RF_CHANPAIR( 9, 10) = 0x664d,
		RF_CHANPAIR(11, 12) = 0x644d,
		RF_CHANPAIR(13, 14) = 0x6675,
	पूर्ण,
	अणु /* table 4 */
		RF_CHANPAIR( 1,  2) = 0x667d,
		RF_CHANPAIR( 3,  4) = 0x607d,
		RF_CHANPAIR( 5,  6) = 0x665d,
		RF_CHANPAIR( 7,  8) = 0x645d,
		RF_CHANPAIR( 9, 10) = 0x666d,
		RF_CHANPAIR(11, 12) = 0x646d,
		RF_CHANPAIR(13, 14) = 0x664d,
	पूर्ण,
	अणु /* table 5 */
		RF_CHANPAIR( 1,  2) = 0x6643,
		RF_CHANPAIR( 3,  4) = 0x6043,
		RF_CHANPAIR( 5,  6) = 0x667d,
		RF_CHANPAIR( 7,  8) = 0x647d,
		RF_CHANPAIR( 9, 10) = 0x665d,
		RF_CHANPAIR(11, 12) = 0x645d,
		RF_CHANPAIR(13, 14) = 0x666d,
	पूर्ण,
	अणु /* table 6 */
		RF_CHANPAIR( 1,  2) = 0x6663,
		RF_CHANPAIR( 3,  4) = 0x6063,
		RF_CHANPAIR( 5,  6) = 0x6643,
		RF_CHANPAIR( 7,  8) = 0x6443,
		RF_CHANPAIR( 9, 10) = 0x667d,
		RF_CHANPAIR(11, 12) = 0x647d,
		RF_CHANPAIR(13, 14) = 0x665d,
	पूर्ण,
	अणु /* table 7 */
		RF_CHANPAIR( 1,  2) = 0x6653,
		RF_CHANPAIR( 3,  4) = 0x6053,
		RF_CHANPAIR( 5,  6) = 0x6663,
		RF_CHANPAIR( 7,  8) = 0x6463,
		RF_CHANPAIR( 9, 10) = 0x6643,
		RF_CHANPAIR(11, 12) = 0x6443,
		RF_CHANPAIR(13, 14) = 0x667d,
	पूर्ण,
	अणु /* table 8 */
		RF_CHANPAIR( 1,  2) = 0x6673,
		RF_CHANPAIR( 3,  4) = 0x6073,
		RF_CHANPAIR( 5,  6) = 0x6653,
		RF_CHANPAIR( 7,  8) = 0x6453,
		RF_CHANPAIR( 9, 10) = 0x6663,
		RF_CHANPAIR(11, 12) = 0x6463,
		RF_CHANPAIR(13, 14) = 0x6643,
	पूर्ण,
	अणु /* table 9 */
		RF_CHANPAIR( 1,  2) = 0x664b,
		RF_CHANPAIR( 3,  4) = 0x604b,
		RF_CHANPAIR( 5,  6) = 0x6673,
		RF_CHANPAIR( 7,  8) = 0x6473,
		RF_CHANPAIR( 9, 10) = 0x6653,
		RF_CHANPAIR(11, 12) = 0x6453,
		RF_CHANPAIR(13, 14) = 0x6663,
	पूर्ण,
	अणु /* table 10 */
		RF_CHANPAIR( 1,  2) = 0x666b,
		RF_CHANPAIR( 3,  4) = 0x606b,
		RF_CHANPAIR( 5,  6) = 0x664b,
		RF_CHANPAIR( 7,  8) = 0x644b,
		RF_CHANPAIR( 9, 10) = 0x6673,
		RF_CHANPAIR(11, 12) = 0x6473,
		RF_CHANPAIR(13, 14) = 0x6653,
	पूर्ण,
	अणु /* table 11 */
		RF_CHANPAIR( 1,  2) = 0x665b,
		RF_CHANPAIR( 3,  4) = 0x605b,
		RF_CHANPAIR( 5,  6) = 0x666b,
		RF_CHANPAIR( 7,  8) = 0x646b,
		RF_CHANPAIR( 9, 10) = 0x664b,
		RF_CHANPAIR(11, 12) = 0x644b,
		RF_CHANPAIR(13, 14) = 0x6673,
	पूर्ण,

पूर्ण;

/* The per-channel synth values क्रम स्वतःcal. These get written to रेजिस्टर 1. */
अटल स्थिर u16 uw2453_स्वतःcal_synth[] = अणु
	RF_CHANNEL( 1) = 0x6847,
	RF_CHANNEL( 2) = 0x6847,
	RF_CHANNEL( 3) = 0x6867,
	RF_CHANNEL( 4) = 0x6867,
	RF_CHANNEL( 5) = 0x6867,
	RF_CHANNEL( 6) = 0x6867,
	RF_CHANNEL( 7) = 0x6857,
	RF_CHANNEL( 8) = 0x6857,
	RF_CHANNEL( 9) = 0x6857,
	RF_CHANNEL(10) = 0x6857,
	RF_CHANNEL(11) = 0x6877,
	RF_CHANNEL(12) = 0x6877,
	RF_CHANNEL(13) = 0x6877,
	RF_CHANNEL(14) = 0x684f,
पूर्ण;

/* The VCO configuration क्रम स्वतःcal (all channels) */
अटल स्थिर u16 UW2453_AUTOCAL_VCO_CFG = 0x6662;

/* TX gain settings. The array index corresponds to the TX घातer पूर्णांकegration
 * values found in the EEPROM. The values get written to रेजिस्टर 7. */
अटल u32 uw2453_txgain[] = अणु
	[0x00] = 0x0e313,
	[0x01] = 0x0fb13,
	[0x02] = 0x0e093,
	[0x03] = 0x0f893,
	[0x04] = 0x0ea93,
	[0x05] = 0x1f093,
	[0x06] = 0x1f493,
	[0x07] = 0x1f693,
	[0x08] = 0x1f393,
	[0x09] = 0x1f35b,
	[0x0a] = 0x1e6db,
	[0x0b] = 0x1ff3f,
	[0x0c] = 0x1ffff,
	[0x0d] = 0x361d7,
	[0x0e] = 0x37fbf,
	[0x0f] = 0x3ff8b,
	[0x10] = 0x3ff33,
	[0x11] = 0x3fb3f,
	[0x12] = 0x3ffff,
पूर्ण;

/* RF-specअगरic काष्ठाure */
काष्ठा uw2453_priv अणु
	/* index पूर्णांकo synth/VCO config tables where PLL lock was found
	 * -1 means स्वतःcal */
	पूर्णांक config;
पूर्ण;

#घोषणा UW2453_PRIV(rf) ((काष्ठा uw2453_priv *) (rf)->priv)

अटल पूर्णांक uw2453_synth_set_channel(काष्ठा zd_chip *chip, पूर्णांक channel,
	bool स्वतःcal)
अणु
	पूर्णांक r;
	पूर्णांक idx = channel - 1;
	u32 val;

	अगर (स्वतःcal)
		val = UW2453_REGWRITE(1, uw2453_स्वतःcal_synth[idx]);
	अन्यथा
		val = UW2453_REGWRITE(1, uw2453_std_synth[idx]);

	r = zd_rख_डालो_locked(chip, val, RF_RV_BITS);
	अगर (r)
		वापस r;

	वापस zd_rख_डालो_locked(chip,
		UW2453_REGWRITE(2, uw2453_synth_भागide[idx]), RF_RV_BITS);
पूर्ण

अटल पूर्णांक uw2453_ग_लिखो_vco_cfg(काष्ठा zd_chip *chip, u16 value)
अणु
	/* venकरोr driver always sets these upper bits even though the specs say
	 * they are reserved */
	u32 val = 0x40000 | value;
	वापस zd_rख_डालो_locked(chip, UW2453_REGWRITE(3, val), RF_RV_BITS);
पूर्ण

अटल पूर्णांक uw2453_init_mode(काष्ठा zd_chip *chip)
अणु
	अटल स्थिर u32 rv[] = अणु
		UW2453_REGWRITE(0, 0x25f98), /* enter IDLE mode */
		UW2453_REGWRITE(0, 0x25f9a), /* enter CAL_VCO mode */
		UW2453_REGWRITE(0, 0x25f94), /* enter RX/TX mode */
		UW2453_REGWRITE(0, 0x27fd4), /* घातer करोwn RSSI circuit */
	पूर्ण;

	वापस zd_rख_डालोv_locked(chip, rv, ARRAY_SIZE(rv), RF_RV_BITS);
पूर्ण

अटल पूर्णांक uw2453_set_tx_gain_level(काष्ठा zd_chip *chip, पूर्णांक channel)
अणु
	u8 पूर्णांक_value = chip->pwr_पूर्णांक_values[channel - 1];

	अगर (पूर्णांक_value >= ARRAY_SIZE(uw2453_txgain)) अणु
		dev_dbg_f(zd_chip_dev(chip), "can't configure TX gain for "
			  "int value %x on channel %d\n", पूर्णांक_value, channel);
		वापस 0;
	पूर्ण

	वापस zd_rख_डालो_locked(chip,
		UW2453_REGWRITE(7, uw2453_txgain[पूर्णांक_value]), RF_RV_BITS);
पूर्ण

अटल पूर्णांक uw2453_init_hw(काष्ठा zd_rf *rf)
अणु
	पूर्णांक i, r;
	पूर्णांक found_config = -1;
	u16 पूर्णांकr_status;
	काष्ठा zd_chip *chip = zd_rf_to_chip(rf);

	अटल स्थिर काष्ठा zd_ioreq16 ioreqs[] = अणु
		अणु ZD_CR10,  0x89 पूर्ण, अणु ZD_CR15,  0x20 पूर्ण,
		अणु ZD_CR17,  0x28 पूर्ण, /* 6112 no change */
		अणु ZD_CR23,  0x38 पूर्ण, अणु ZD_CR24,  0x20 पूर्ण, अणु ZD_CR26,  0x93 पूर्ण,
		अणु ZD_CR27,  0x15 पूर्ण, अणु ZD_CR28,  0x3e पूर्ण, अणु ZD_CR29,  0x00 पूर्ण,
		अणु ZD_CR33,  0x28 पूर्ण, अणु ZD_CR34,  0x30 पूर्ण,
		अणु ZD_CR35,  0x43 पूर्ण, /* 6112 3e->43 */
		अणु ZD_CR41,  0x24 पूर्ण, अणु ZD_CR44,  0x32 पूर्ण,
		अणु ZD_CR46,  0x92 पूर्ण, /* 6112 96->92 */
		अणु ZD_CR47,  0x1e पूर्ण,
		अणु ZD_CR48,  0x04 पूर्ण, /* 5602 Roger */
		अणु ZD_CR49,  0xfa पूर्ण, अणु ZD_CR79,  0x58 पूर्ण, अणु ZD_CR80,  0x30 पूर्ण,
		अणु ZD_CR81,  0x30 पूर्ण, अणु ZD_CR87,  0x0a पूर्ण, अणु ZD_CR89,  0x04 पूर्ण,
		अणु ZD_CR91,  0x00 पूर्ण, अणु ZD_CR92,  0x0a पूर्ण, अणु ZD_CR98,  0x8d पूर्ण,
		अणु ZD_CR99,  0x28 पूर्ण, अणु ZD_CR100, 0x02 पूर्ण,
		अणु ZD_CR101, 0x09 पूर्ण, /* 6112 13->1f 6220 1f->13 6407 13->9 */
		अणु ZD_CR102, 0x27 पूर्ण,
		अणु ZD_CR106, 0x1c पूर्ण, /* 5d07 5112 1f->1c 6220 1c->1f
				     * 6221 1f->1c
				     */
		अणु ZD_CR107, 0x1c पूर्ण, /* 6220 1c->1a 5221 1a->1c */
		अणु ZD_CR109, 0x13 पूर्ण,
		अणु ZD_CR110, 0x1f पूर्ण, /* 6112 13->1f 6221 1f->13 6407 13->0x09 */
		अणु ZD_CR111, 0x13 पूर्ण, अणु ZD_CR112, 0x1f पूर्ण, अणु ZD_CR113, 0x27 पूर्ण,
		अणु ZD_CR114, 0x23 पूर्ण, /* 6221 27->23 */
		अणु ZD_CR115, 0x24 पूर्ण, /* 6112 24->1c 6220 1c->24 */
		अणु ZD_CR116, 0x24 पूर्ण, /* 6220 1c->24 */
		अणु ZD_CR117, 0xfa पूर्ण, /* 6112 fa->f8 6220 f8->f4 6220 f4->fa */
		अणु ZD_CR118, 0xf0 पूर्ण, /* 5d07 6112 f0->f2 6220 f2->f0 */
		अणु ZD_CR119, 0x1a पूर्ण, /* 6112 1a->10 6220 10->14 6220 14->1a */
		अणु ZD_CR120, 0x4f पूर्ण,
		अणु ZD_CR121, 0x1f पूर्ण, /* 6220 4f->1f */
		अणु ZD_CR122, 0xf0 पूर्ण, अणु ZD_CR123, 0x57 पूर्ण, अणु ZD_CR125, 0xad पूर्ण,
		अणु ZD_CR126, 0x6c पूर्ण, अणु ZD_CR127, 0x03 पूर्ण,
		अणु ZD_CR128, 0x14 पूर्ण, /* 6302 12->11 */
		अणु ZD_CR129, 0x12 पूर्ण, /* 6301 10->0f */
		अणु ZD_CR130, 0x10 पूर्ण, अणु ZD_CR137, 0x50 पूर्ण, अणु ZD_CR138, 0xa8 पूर्ण,
		अणु ZD_CR144, 0xac पूर्ण, अणु ZD_CR146, 0x20 पूर्ण, अणु ZD_CR252, 0xff पूर्ण,
		अणु ZD_CR253, 0xff पूर्ण,
	पूर्ण;

	अटल स्थिर u32 rv[] = अणु
		UW2453_REGWRITE(4, 0x2b),    /* configure receiver gain */
		UW2453_REGWRITE(5, 0x19e4f), /* configure transmitter gain */
		UW2453_REGWRITE(6, 0xf81ad), /* enable RX/TX filter tuning */
		UW2453_REGWRITE(7, 0x3fffe), /* disable TX gain in test mode */

		/* enter CAL_FIL mode, TX gain set by रेजिस्टरs, RX gain set by pins,
		 * RSSI circuit घातered करोwn, reduced RSSI range */
		UW2453_REGWRITE(0, 0x25f9c), /* 5d01 cal_fil */

		/* synthesizer configuration क्रम channel 1 */
		UW2453_REGWRITE(1, 0x47),
		UW2453_REGWRITE(2, 0x999),

		/* disable manual VCO band selection */
		UW2453_REGWRITE(3, 0x7602),

		/* enable manual VCO band selection, configure current level */
		UW2453_REGWRITE(3, 0x46063),
	पूर्ण;

	r = zd_ioग_लिखो16a_locked(chip, ioreqs, ARRAY_SIZE(ioreqs));
	अगर (r)
		वापस r;

	r = zd_rख_डालोv_locked(chip, rv, ARRAY_SIZE(rv), RF_RV_BITS);
	अगर (r)
		वापस r;

	r = uw2453_init_mode(chip);
	अगर (r)
		वापस r;

	/* Try all standard VCO configuration settings on channel 1 */
	क्रम (i = 0; i < ARRAY_SIZE(uw2453_std_vco_cfg) - 1; i++) अणु
		/* Configure synthesizer क्रम channel 1 */
		r = uw2453_synth_set_channel(chip, 1, false);
		अगर (r)
			वापस r;

		/* Write VCO config */
		r = uw2453_ग_लिखो_vco_cfg(chip, uw2453_std_vco_cfg[i][0]);
		अगर (r)
			वापस r;

		/* ack पूर्णांकerrupt event */
		r = zd_ioग_लिखो16_locked(chip, 0x0f, UW2453_INTR_REG);
		अगर (r)
			वापस r;

		/* check पूर्णांकerrupt status */
		r = zd_ioपढ़ो16_locked(chip, &पूर्णांकr_status, UW2453_INTR_REG);
		अगर (r)
			वापस r;

		अगर (!(पूर्णांकr_status & 0xf)) अणु
			dev_dbg_f(zd_chip_dev(chip),
				"PLL locked on configuration %d\n", i);
			found_config = i;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (found_config == -1) अणु
		/* स्वतःcal */
		dev_dbg_f(zd_chip_dev(chip),
			"PLL did not lock, using autocal\n");

		r = uw2453_synth_set_channel(chip, 1, true);
		अगर (r)
			वापस r;

		r = uw2453_ग_लिखो_vco_cfg(chip, UW2453_AUTOCAL_VCO_CFG);
		अगर (r)
			वापस r;
	पूर्ण

	/* To match the venकरोr driver behaviour, we use the configuration after
	 * the one that produced a lock. */
	UW2453_PRIV(rf)->config = found_config + 1;

	वापस zd_ioग_लिखो16_locked(chip, 0x06, ZD_CR203);
पूर्ण

अटल पूर्णांक uw2453_set_channel(काष्ठा zd_rf *rf, u8 channel)
अणु
	पूर्णांक r;
	u16 vco_cfg;
	पूर्णांक config = UW2453_PRIV(rf)->config;
	bool स्वतःcal = (config == -1);
	काष्ठा zd_chip *chip = zd_rf_to_chip(rf);

	अटल स्थिर काष्ठा zd_ioreq16 ioreqs[] = अणु
		अणु ZD_CR80,  0x30 पूर्ण, अणु ZD_CR81,  0x30 पूर्ण, अणु ZD_CR79,  0x58 पूर्ण,
		अणु ZD_CR12,  0xf0 पूर्ण, अणु ZD_CR77,  0x1b पूर्ण, अणु ZD_CR78,  0x58 पूर्ण,
	पूर्ण;

	r = uw2453_synth_set_channel(chip, channel, स्वतःcal);
	अगर (r)
		वापस r;

	अगर (स्वतःcal)
		vco_cfg = UW2453_AUTOCAL_VCO_CFG;
	अन्यथा
		vco_cfg = uw2453_std_vco_cfg[config][CHAN_TO_PAIRIDX(channel)];

	r = uw2453_ग_लिखो_vco_cfg(chip, vco_cfg);
	अगर (r)
		वापस r;

	r = uw2453_init_mode(chip);
	अगर (r)
		वापस r;

	r = zd_ioग_लिखो16a_locked(chip, ioreqs, ARRAY_SIZE(ioreqs));
	अगर (r)
		वापस r;

	r = uw2453_set_tx_gain_level(chip, channel);
	अगर (r)
		वापस r;

	वापस zd_ioग_लिखो16_locked(chip, 0x06, ZD_CR203);
पूर्ण

अटल पूर्णांक uw2453_चयन_radio_on(काष्ठा zd_rf *rf)
अणु
	पूर्णांक r;
	काष्ठा zd_chip *chip = zd_rf_to_chip(rf);
	काष्ठा zd_ioreq16 ioreqs[] = अणु
		अणु ZD_CR11,  0x00 पूर्ण, अणु ZD_CR251, 0x3f पूर्ण,
	पूर्ण;

	/* enter RXTX mode */
	r = zd_rख_डालो_locked(chip, UW2453_REGWRITE(0, 0x25f94), RF_RV_BITS);
	अगर (r)
		वापस r;

	अगर (zd_chip_is_zd1211b(chip))
		ioreqs[1].value = 0x7f;

	वापस zd_ioग_लिखो16a_locked(chip, ioreqs, ARRAY_SIZE(ioreqs));
पूर्ण

अटल पूर्णांक uw2453_चयन_radio_off(काष्ठा zd_rf *rf)
अणु
	पूर्णांक r;
	काष्ठा zd_chip *chip = zd_rf_to_chip(rf);
	अटल स्थिर काष्ठा zd_ioreq16 ioreqs[] = अणु
		अणु ZD_CR11,  0x04 पूर्ण, अणु ZD_CR251, 0x2f पूर्ण,
	पूर्ण;

	/* enter IDLE mode */
	/* FIXME: shouldn't we go to SLEEP? sent email to zydas */
	r = zd_rख_डालो_locked(chip, UW2453_REGWRITE(0, 0x25f90), RF_RV_BITS);
	अगर (r)
		वापस r;

	वापस zd_ioग_लिखो16a_locked(chip, ioreqs, ARRAY_SIZE(ioreqs));
पूर्ण

अटल व्योम uw2453_clear(काष्ठा zd_rf *rf)
अणु
	kमुक्त(rf->priv);
पूर्ण

पूर्णांक zd_rf_init_uw2453(काष्ठा zd_rf *rf)
अणु
	rf->init_hw = uw2453_init_hw;
	rf->set_channel = uw2453_set_channel;
	rf->चयन_radio_on = uw2453_चयन_radio_on;
	rf->चयन_radio_off = uw2453_चयन_radio_off;
	rf->patch_6m_band_edge = zd_rf_generic_patch_6m;
	rf->clear = uw2453_clear;
	/* we have our own TX पूर्णांकegration code */
	rf->update_channel_पूर्णांक = 0;

	rf->priv = kदो_स्मृति(माप(काष्ठा uw2453_priv), GFP_KERNEL);
	अगर (rf->priv == शून्य)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

