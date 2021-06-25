<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* ZD1211 USB-WLAN driver क्रम Linux
 *
 * Copyright (C) 2005-2007 Ulrich Kunitz <kune@deine-taler.de>
 * Copyright (C) 2006-2007 Daniel Drake <dsd@gentoo.org>
 */

#समावेश <linux/kernel.h>

#समावेश "zd_rf.h"
#समावेश "zd_usb.h"
#समावेश "zd_chip.h"

अटल स्थिर u32 chan_rv[][2] = अणु
	RF_CHANNEL( 1) = अणु 0x09ec00, 0x8cccc8 पूर्ण,
	RF_CHANNEL( 2) = अणु 0x09ec00, 0x8cccd8 पूर्ण,
	RF_CHANNEL( 3) = अणु 0x09ec00, 0x8cccc0 पूर्ण,
	RF_CHANNEL( 4) = अणु 0x09ec00, 0x8cccd0 पूर्ण,
	RF_CHANNEL( 5) = अणु 0x05ec00, 0x8cccc8 पूर्ण,
	RF_CHANNEL( 6) = अणु 0x05ec00, 0x8cccd8 पूर्ण,
	RF_CHANNEL( 7) = अणु 0x05ec00, 0x8cccc0 पूर्ण,
	RF_CHANNEL( 8) = अणु 0x05ec00, 0x8cccd0 पूर्ण,
	RF_CHANNEL( 9) = अणु 0x0dec00, 0x8cccc8 पूर्ण,
	RF_CHANNEL(10) = अणु 0x0dec00, 0x8cccd8 पूर्ण,
	RF_CHANNEL(11) = अणु 0x0dec00, 0x8cccc0 पूर्ण,
	RF_CHANNEL(12) = अणु 0x0dec00, 0x8cccd0 पूर्ण,
	RF_CHANNEL(13) = अणु 0x03ec00, 0x8cccc8 पूर्ण,
	RF_CHANNEL(14) = अणु 0x03ec00, 0x866660 पूर्ण,
पूर्ण;

अटल स्थिर u32 std_rv[] = अणु
	0x4ff821,
	0xc5fbfc,
	0x21ebfe,
	0xafd401, /* freq shअगरt 0xaad401 */
	0x6cf56a,
	0xe04073,
	0x193d76,
	0x9dd844,
	0x500007,
	0xd8c010,
पूर्ण;

अटल स्थिर u32 rv_init1[] = अणु
	0x3c9000,
	0xbfffff,
	0x700000,
	0xf15d58,
पूर्ण;

अटल स्थिर u32 rv_init2[] = अणु
	0xf15d59,
	0xf15d5c,
	0xf15d58,
पूर्ण;

अटल स्थिर काष्ठा zd_ioreq16 ioreqs_sw[] = अणु
	अणु ZD_CR128, 0x14 पूर्ण, अणु ZD_CR129, 0x12 पूर्ण, अणु ZD_CR130, 0x10 पूर्ण,
	अणु ZD_CR38,  0x38 पूर्ण, अणु ZD_CR136, 0xdf पूर्ण,
पूर्ण;

अटल पूर्णांक zd1211b_al7230b_finalize(काष्ठा zd_chip *chip)
अणु
	पूर्णांक r;
	अटल स्थिर काष्ठा zd_ioreq16 ioreqs[] = अणु
		अणु ZD_CR80,  0x30 पूर्ण, अणु ZD_CR81,  0x30 पूर्ण, अणु ZD_CR79,  0x58 पूर्ण,
		अणु ZD_CR12,  0xf0 पूर्ण, अणु ZD_CR77,  0x1b पूर्ण, अणु ZD_CR78,  0x58 पूर्ण,
		अणु ZD_CR203, 0x04 पूर्ण,
		अणु पूर्ण,
		अणु ZD_CR240, 0x80 पूर्ण,
	पूर्ण;

	r = zd_ioग_लिखो16a_locked(chip, ioreqs, ARRAY_SIZE(ioreqs));
	अगर (r)
		वापस r;

	अगर (chip->new_phy_layout) अणु
		/* antenna selection? */
		r = zd_ioग_लिखो16_locked(chip, 0xe5, ZD_CR9);
		अगर (r)
			वापस r;
	पूर्ण

	वापस zd_ioग_लिखो16_locked(chip, 0x04, ZD_CR203);
पूर्ण

अटल पूर्णांक zd1211_al7230b_init_hw(काष्ठा zd_rf *rf)
अणु
	पूर्णांक r;
	काष्ठा zd_chip *chip = zd_rf_to_chip(rf);

	/* All of these ग_लिखोs are identical to AL2230 unless otherwise
	 * specअगरied */
	अटल स्थिर काष्ठा zd_ioreq16 ioreqs_1[] = अणु
		/* This one is 7230-specअगरic, and happens beक्रमe the rest */
		अणु ZD_CR240,  0x57 पूर्ण,
		अणु पूर्ण,

		अणु ZD_CR15,   0x20 पूर्ण, अणु ZD_CR23,   0x40 पूर्ण, अणु ZD_CR24,  0x20 पूर्ण,
		अणु ZD_CR26,   0x11 पूर्ण, अणु ZD_CR28,   0x3e पूर्ण, अणु ZD_CR29,  0x00 पूर्ण,
		अणु ZD_CR44,   0x33 पूर्ण,
		/* This value is dअगरferent क्रम 7230 (was: 0x2a) */
		अणु ZD_CR106,  0x22 पूर्ण,
		अणु ZD_CR107,  0x1a पूर्ण, अणु ZD_CR109,  0x09 पूर्ण, अणु ZD_CR110,  0x27 पूर्ण,
		अणु ZD_CR111,  0x2b पूर्ण, अणु ZD_CR112,  0x2b पूर्ण, अणु ZD_CR119,  0x0a पूर्ण,
		/* This happened further करोwn in AL2230,
		 * and the value changed (was: 0xe0) */
		अणु ZD_CR122,  0xfc पूर्ण,
		अणु ZD_CR10,   0x89 पूर्ण,
		/* क्रम newest (3rd cut) AL2300 */
		अणु ZD_CR17,   0x28 पूर्ण,
		अणु ZD_CR26,   0x93 पूर्ण, अणु ZD_CR34,   0x30 पूर्ण,
		/* क्रम newest (3rd cut) AL2300 */
		अणु ZD_CR35,   0x3e पूर्ण,
		अणु ZD_CR41,   0x24 पूर्ण, अणु ZD_CR44,   0x32 पूर्ण,
		/* क्रम newest (3rd cut) AL2300 */
		अणु ZD_CR46,   0x96 पूर्ण,
		अणु ZD_CR47,   0x1e पूर्ण, अणु ZD_CR79,   0x58 पूर्ण, अणु ZD_CR80,  0x30 पूर्ण,
		अणु ZD_CR81,   0x30 पूर्ण, अणु ZD_CR87,   0x0a पूर्ण, अणु ZD_CR89,  0x04 पूर्ण,
		अणु ZD_CR92,   0x0a पूर्ण, अणु ZD_CR99,   0x28 पूर्ण,
		/* This value is dअगरferent क्रम 7230 (was: 0x00) */
		अणु ZD_CR100,  0x02 पूर्ण,
		अणु ZD_CR101,  0x13 पूर्ण, अणु ZD_CR102,  0x27 पूर्ण,
		/* This value is dअगरferent क्रम 7230 (was: 0x24) */
		अणु ZD_CR106,  0x22 पूर्ण,
		/* This value is dअगरferent क्रम 7230 (was: 0x2a) */
		अणु ZD_CR107,  0x3f पूर्ण,
		अणु ZD_CR109,  0x09 पूर्ण,
		/* This value is dअगरferent क्रम 7230 (was: 0x13) */
		अणु ZD_CR110,  0x1f पूर्ण,
		अणु ZD_CR111,  0x1f पूर्ण, अणु ZD_CR112,  0x1f पूर्ण, अणु ZD_CR113, 0x27 पूर्ण,
		अणु ZD_CR114,  0x27 पूर्ण,
		/* क्रम newest (3rd cut) AL2300 */
		अणु ZD_CR115,  0x24 पूर्ण,
		/* This value is dअगरferent क्रम 7230 (was: 0x24) */
		अणु ZD_CR116,  0x3f पूर्ण,
		/* This value is dअगरferent क्रम 7230 (was: 0xf4) */
		अणु ZD_CR117,  0xfa पूर्ण,
		अणु ZD_CR118,  0xfc पूर्ण, अणु ZD_CR119,  0x10 पूर्ण, अणु ZD_CR120, 0x4f पूर्ण,
		अणु ZD_CR121,  0x77 पूर्ण, अणु ZD_CR137,  0x88 पूर्ण,
		/* This one is 7230-specअगरic */
		अणु ZD_CR138,  0xa8 पूर्ण,
		/* This value is dअगरferent क्रम 7230 (was: 0xff) */
		अणु ZD_CR252,  0x34 पूर्ण,
		/* This value is dअगरferent क्रम 7230 (was: 0xff) */
		अणु ZD_CR253,  0x34 पूर्ण,

		/* PLL_OFF */
		अणु ZD_CR251, 0x2f पूर्ण,
	पूर्ण;

	अटल स्थिर काष्ठा zd_ioreq16 ioreqs_2[] = अणु
		अणु ZD_CR251, 0x3f पूर्ण, /* PLL_ON */
		अणु ZD_CR128, 0x14 पूर्ण, अणु ZD_CR129, 0x12 पूर्ण, अणु ZD_CR130, 0x10 पूर्ण,
		अणु ZD_CR38,  0x38 पूर्ण, अणु ZD_CR136, 0xdf पूर्ण,
	पूर्ण;

	r = zd_ioग_लिखो16a_locked(chip, ioreqs_1, ARRAY_SIZE(ioreqs_1));
	अगर (r)
		वापस r;

	r = zd_rख_डालोv_cr_locked(chip, chan_rv[0], ARRAY_SIZE(chan_rv[0]));
	अगर (r)
		वापस r;

	r = zd_rख_डालोv_cr_locked(chip, std_rv, ARRAY_SIZE(std_rv));
	अगर (r)
		वापस r;

	r = zd_rख_डालोv_cr_locked(chip, rv_init1, ARRAY_SIZE(rv_init1));
	अगर (r)
		वापस r;

	r = zd_ioग_लिखो16a_locked(chip, ioreqs_2, ARRAY_SIZE(ioreqs_2));
	अगर (r)
		वापस r;

	r = zd_rख_डालोv_cr_locked(chip, rv_init2, ARRAY_SIZE(rv_init2));
	अगर (r)
		वापस r;

	r = zd_ioग_लिखो16_locked(chip, 0x06, ZD_CR203);
	अगर (r)
		वापस r;
	r = zd_ioग_लिखो16_locked(chip, 0x80, ZD_CR240);
	अगर (r)
		वापस r;

	वापस 0;
पूर्ण

अटल पूर्णांक zd1211b_al7230b_init_hw(काष्ठा zd_rf *rf)
अणु
	पूर्णांक r;
	काष्ठा zd_chip *chip = zd_rf_to_chip(rf);

	अटल स्थिर काष्ठा zd_ioreq16 ioreqs_1[] = अणु
		अणु ZD_CR240, 0x57 पूर्ण, अणु ZD_CR9,   0x9 पूर्ण,
		अणु पूर्ण,
		अणु ZD_CR10,  0x8b पूर्ण, अणु ZD_CR15,  0x20 पूर्ण,
		अणु ZD_CR17,  0x2B पूर्ण, /* क्रम newest (3rd cut) AL2230 */
		अणु ZD_CR20,  0x10 पूर्ण, /* 4N25->Stone Request */
		अणु ZD_CR23,  0x40 पूर्ण, अणु ZD_CR24,  0x20 पूर्ण, अणु ZD_CR26,  0x93 पूर्ण,
		अणु ZD_CR28,  0x3e पूर्ण, अणु ZD_CR29,  0x00 पूर्ण,
		अणु ZD_CR33,  0x28 पूर्ण, /* 5613 */
		अणु ZD_CR34,  0x30 पूर्ण,
		अणु ZD_CR35,  0x3e पूर्ण, /* क्रम newest (3rd cut) AL2230 */
		अणु ZD_CR41,  0x24 पूर्ण, अणु ZD_CR44,  0x32 पूर्ण,
		अणु ZD_CR46,  0x99 पूर्ण, /* क्रम newest (3rd cut) AL2230 */
		अणु ZD_CR47,  0x1e पूर्ण,

		/* ZD1215 5610 */
		अणु ZD_CR48,  0x00 पूर्ण, अणु ZD_CR49,  0x00 पूर्ण, अणु ZD_CR51,  0x01 पूर्ण,
		अणु ZD_CR52,  0x80 पूर्ण, अणु ZD_CR53,  0x7e पूर्ण, अणु ZD_CR65,  0x00 पूर्ण,
		अणु ZD_CR66,  0x00 पूर्ण, अणु ZD_CR67,  0x00 पूर्ण, अणु ZD_CR68,  0x00 पूर्ण,
		अणु ZD_CR69,  0x28 पूर्ण,

		अणु ZD_CR79,  0x58 पूर्ण, अणु ZD_CR80,  0x30 पूर्ण, अणु ZD_CR81,  0x30 पूर्ण,
		अणु ZD_CR87,  0x0A पूर्ण, अणु ZD_CR89,  0x04 पूर्ण,
		अणु ZD_CR90,  0x58 पूर्ण, /* 5112 */
		अणु ZD_CR91,  0x00 पूर्ण, /* 5613 */
		अणु ZD_CR92,  0x0a पूर्ण,
		अणु ZD_CR98,  0x8d पूर्ण, /* 4804, क्रम 1212 new algorithm */
		अणु ZD_CR99,  0x00 पूर्ण, अणु ZD_CR100, 0x02 पूर्ण, अणु ZD_CR101, 0x13 पूर्ण,
		अणु ZD_CR102, 0x27 पूर्ण,
		अणु ZD_CR106, 0x20 पूर्ण, /* change to 0x24 क्रम AL7230B */
		अणु ZD_CR109, 0x13 पूर्ण, /* 4804, क्रम 1212 new algorithm */
		अणु ZD_CR112, 0x1f पूर्ण,
	पूर्ण;

	अटल स्थिर काष्ठा zd_ioreq16 ioreqs_new_phy[] = अणु
		अणु ZD_CR107, 0x28 पूर्ण,
		अणु ZD_CR110, 0x1f पूर्ण, /* 5127, 0x13->0x1f */
		अणु ZD_CR111, 0x1f पूर्ण, /* 0x13 to 0x1f क्रम AL7230B */
		अणु ZD_CR116, 0x2a पूर्ण, अणु ZD_CR118, 0xfa पूर्ण, अणु ZD_CR119, 0x12 पूर्ण,
		अणु ZD_CR121, 0x6c पूर्ण, /* 5613 */
	पूर्ण;

	अटल स्थिर काष्ठा zd_ioreq16 ioreqs_old_phy[] = अणु
		अणु ZD_CR107, 0x24 पूर्ण,
		अणु ZD_CR110, 0x13 पूर्ण, /* 5127, 0x13->0x1f */
		अणु ZD_CR111, 0x13 पूर्ण, /* 0x13 to 0x1f क्रम AL7230B */
		अणु ZD_CR116, 0x24 पूर्ण, अणु ZD_CR118, 0xfc पूर्ण, अणु ZD_CR119, 0x11 पूर्ण,
		अणु ZD_CR121, 0x6a पूर्ण, /* 5613 */
	पूर्ण;

	अटल स्थिर काष्ठा zd_ioreq16 ioreqs_2[] = अणु
		अणु ZD_CR113, 0x27 पूर्ण, अणु ZD_CR114, 0x27 पूर्ण, अणु ZD_CR115, 0x24 पूर्ण,
		अणु ZD_CR117, 0xfa पूर्ण, अणु ZD_CR120, 0x4f पूर्ण,
		अणु ZD_CR122, 0xfc पूर्ण, /* E0->FCh at 4901 */
		अणु ZD_CR123, 0x57 पूर्ण, /* 5613 */
		अणु ZD_CR125, 0xad पूर्ण, /* 4804, क्रम 1212 new algorithm */
		अणु ZD_CR126, 0x6c पूर्ण, /* 5613 */
		अणु ZD_CR127, 0x03 पूर्ण, /* 4804, क्रम 1212 new algorithm */
		अणु ZD_CR130, 0x10 पूर्ण,
		अणु ZD_CR131, 0x00 पूर्ण, /* 5112 */
		अणु ZD_CR137, 0x50 पूर्ण, /* 5613 */
		अणु ZD_CR138, 0xa8 पूर्ण, /* 5112 */
		अणु ZD_CR144, 0xac पूर्ण, /* 5613 */
		अणु ZD_CR148, 0x40 पूर्ण, /* 5112 */
		अणु ZD_CR149, 0x40 पूर्ण, /* 4O07, 50->40 */
		अणु ZD_CR150, 0x1a पूर्ण, /* 5112, 0C->1A */
		अणु ZD_CR252, 0x34 पूर्ण, अणु ZD_CR253, 0x34 पूर्ण,
		अणु ZD_CR251, 0x2f पूर्ण, /* PLL_OFF */
	पूर्ण;

	अटल स्थिर काष्ठा zd_ioreq16 ioreqs_3[] = अणु
		अणु ZD_CR251, 0x7f पूर्ण, /* PLL_ON */
		अणु ZD_CR128, 0x14 पूर्ण, अणु ZD_CR129, 0x12 पूर्ण, अणु ZD_CR130, 0x10 पूर्ण,
		अणु ZD_CR38,  0x38 पूर्ण, अणु ZD_CR136, 0xdf पूर्ण,
	पूर्ण;

	r = zd_ioग_लिखो16a_locked(chip, ioreqs_1, ARRAY_SIZE(ioreqs_1));
	अगर (r)
		वापस r;

	अगर (chip->new_phy_layout)
		r = zd_ioग_लिखो16a_locked(chip, ioreqs_new_phy,
			ARRAY_SIZE(ioreqs_new_phy));
	अन्यथा
		r = zd_ioग_लिखो16a_locked(chip, ioreqs_old_phy,
			ARRAY_SIZE(ioreqs_old_phy));
	अगर (r)
		वापस r;

	r = zd_ioग_लिखो16a_locked(chip, ioreqs_2, ARRAY_SIZE(ioreqs_2));
	अगर (r)
		वापस r;

	r = zd_rख_डालोv_cr_locked(chip, chan_rv[0], ARRAY_SIZE(chan_rv[0]));
	अगर (r)
		वापस r;

	r = zd_rख_डालोv_cr_locked(chip, std_rv, ARRAY_SIZE(std_rv));
	अगर (r)
		वापस r;

	r = zd_rख_डालोv_cr_locked(chip, rv_init1, ARRAY_SIZE(rv_init1));
	अगर (r)
		वापस r;

	r = zd_ioग_लिखो16a_locked(chip, ioreqs_3, ARRAY_SIZE(ioreqs_3));
	अगर (r)
		वापस r;

	r = zd_rख_डालोv_cr_locked(chip, rv_init2, ARRAY_SIZE(rv_init2));
	अगर (r)
		वापस r;

	वापस zd1211b_al7230b_finalize(chip);
पूर्ण

अटल पूर्णांक zd1211_al7230b_set_channel(काष्ठा zd_rf *rf, u8 channel)
अणु
	पूर्णांक r;
	स्थिर u32 *rv = chan_rv[channel-1];
	काष्ठा zd_chip *chip = zd_rf_to_chip(rf);

	अटल स्थिर काष्ठा zd_ioreq16 ioreqs[] = अणु
		/* PLL_ON */
		अणु ZD_CR251, 0x3f पूर्ण,
		अणु ZD_CR203, 0x06 पूर्ण, अणु ZD_CR240, 0x08 पूर्ण,
	पूर्ण;

	r = zd_ioग_लिखो16_locked(chip, 0x57, ZD_CR240);
	अगर (r)
		वापस r;

	/* PLL_OFF */
	r = zd_ioग_लिखो16_locked(chip, 0x2f, ZD_CR251);
	अगर (r)
		वापस r;

	r = zd_rख_डालोv_cr_locked(chip, std_rv, ARRAY_SIZE(std_rv));
	अगर (r)
		वापस r;

	r = zd_rख_डालो_cr_locked(chip, 0x3c9000);
	अगर (r)
		वापस r;
	r = zd_rख_डालो_cr_locked(chip, 0xf15d58);
	अगर (r)
		वापस r;

	r = zd_ioग_लिखो16a_locked(chip, ioreqs_sw, ARRAY_SIZE(ioreqs_sw));
	अगर (r)
		वापस r;

	r = zd_rख_डालोv_cr_locked(chip, rv, 2);
	अगर (r)
		वापस r;

	r = zd_rख_डालो_cr_locked(chip, 0x3c9000);
	अगर (r)
		वापस r;

	वापस zd_ioग_लिखो16a_locked(chip, ioreqs, ARRAY_SIZE(ioreqs));
पूर्ण

अटल पूर्णांक zd1211b_al7230b_set_channel(काष्ठा zd_rf *rf, u8 channel)
अणु
	पूर्णांक r;
	स्थिर u32 *rv = chan_rv[channel-1];
	काष्ठा zd_chip *chip = zd_rf_to_chip(rf);

	r = zd_ioग_लिखो16_locked(chip, 0x57, ZD_CR240);
	अगर (r)
		वापस r;
	r = zd_ioग_लिखो16_locked(chip, 0xe4, ZD_CR9);
	अगर (r)
		वापस r;

	/* PLL_OFF */
	r = zd_ioग_लिखो16_locked(chip, 0x2f, ZD_CR251);
	अगर (r)
		वापस r;
	r = zd_rख_डालोv_cr_locked(chip, std_rv, ARRAY_SIZE(std_rv));
	अगर (r)
		वापस r;

	r = zd_rख_डालो_cr_locked(chip, 0x3c9000);
	अगर (r)
		वापस r;
	r = zd_rख_डालो_cr_locked(chip, 0xf15d58);
	अगर (r)
		वापस r;

	r = zd_ioग_लिखो16a_locked(chip, ioreqs_sw, ARRAY_SIZE(ioreqs_sw));
	अगर (r)
		वापस r;

	r = zd_rख_डालोv_cr_locked(chip, rv, 2);
	अगर (r)
		वापस r;

	r = zd_rख_डालो_cr_locked(chip, 0x3c9000);
	अगर (r)
		वापस r;

	r = zd_ioग_लिखो16_locked(chip, 0x7f, ZD_CR251);
	अगर (r)
		वापस r;

	वापस zd1211b_al7230b_finalize(chip);
पूर्ण

अटल पूर्णांक zd1211_al7230b_चयन_radio_on(काष्ठा zd_rf *rf)
अणु
	काष्ठा zd_chip *chip = zd_rf_to_chip(rf);
	अटल स्थिर काष्ठा zd_ioreq16 ioreqs[] = अणु
		अणु ZD_CR11,  0x00 पूर्ण,
		अणु ZD_CR251, 0x3f पूर्ण,
	पूर्ण;

	वापस zd_ioग_लिखो16a_locked(chip, ioreqs, ARRAY_SIZE(ioreqs));
पूर्ण

अटल पूर्णांक zd1211b_al7230b_चयन_radio_on(काष्ठा zd_rf *rf)
अणु
	काष्ठा zd_chip *chip = zd_rf_to_chip(rf);
	अटल स्थिर काष्ठा zd_ioreq16 ioreqs[] = अणु
		अणु ZD_CR11,  0x00 पूर्ण,
		अणु ZD_CR251, 0x7f पूर्ण,
	पूर्ण;

	वापस zd_ioग_लिखो16a_locked(chip, ioreqs, ARRAY_SIZE(ioreqs));
पूर्ण

अटल पूर्णांक al7230b_चयन_radio_off(काष्ठा zd_rf *rf)
अणु
	काष्ठा zd_chip *chip = zd_rf_to_chip(rf);
	अटल स्थिर काष्ठा zd_ioreq16 ioreqs[] = अणु
		अणु ZD_CR11,  0x04 पूर्ण,
		अणु ZD_CR251, 0x2f पूर्ण,
	पूर्ण;

	वापस zd_ioग_लिखो16a_locked(chip, ioreqs, ARRAY_SIZE(ioreqs));
पूर्ण

/* ZD1211B+AL7230B 6m band edge patching dअगरfers slightly from other
 * configurations */
अटल पूर्णांक zd1211b_al7230b_patch_6m(काष्ठा zd_rf *rf, u8 channel)
अणु
	काष्ठा zd_chip *chip = zd_rf_to_chip(rf);
	काष्ठा zd_ioreq16 ioreqs[] = अणु
		अणु ZD_CR128, 0x14 पूर्ण, अणु ZD_CR129, 0x12 पूर्ण,
	पूर्ण;

	/* FIXME: Channel 11 is not the edge क्रम all regulatory करोमुख्यs. */
	अगर (channel == 1) अणु
		ioreqs[0].value = 0x0e;
		ioreqs[1].value = 0x10;
	पूर्ण अन्यथा अगर (channel == 11) अणु
		ioreqs[0].value = 0x10;
		ioreqs[1].value = 0x10;
	पूर्ण

	dev_dbg_f(zd_chip_dev(chip), "patching for channel %d\n", channel);
	वापस zd_ioग_लिखो16a_locked(chip, ioreqs, ARRAY_SIZE(ioreqs));
पूर्ण

पूर्णांक zd_rf_init_al7230b(काष्ठा zd_rf *rf)
अणु
	काष्ठा zd_chip *chip = zd_rf_to_chip(rf);

	अगर (zd_chip_is_zd1211b(chip)) अणु
		rf->init_hw = zd1211b_al7230b_init_hw;
		rf->चयन_radio_on = zd1211b_al7230b_चयन_radio_on;
		rf->set_channel = zd1211b_al7230b_set_channel;
		rf->patch_6m_band_edge = zd1211b_al7230b_patch_6m;
	पूर्ण अन्यथा अणु
		rf->init_hw = zd1211_al7230b_init_hw;
		rf->चयन_radio_on = zd1211_al7230b_चयन_radio_on;
		rf->set_channel = zd1211_al7230b_set_channel;
		rf->patch_6m_band_edge = zd_rf_generic_patch_6m;
		rf->patch_cck_gain = 1;
	पूर्ण

	rf->चयन_radio_off = al7230b_चयन_radio_off;

	वापस 0;
पूर्ण
