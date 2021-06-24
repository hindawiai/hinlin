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

#घोषणा IS_AL2230S(chip) ((chip)->al2230s_bit || (chip)->rf.type == AL2230S_RF)

अटल स्थिर u32 zd1211_al2230_table[][3] = अणु
	RF_CHANNEL( 1) = अणु 0x03f790, 0x033331, 0x00000d, पूर्ण,
	RF_CHANNEL( 2) = अणु 0x03f790, 0x0b3331, 0x00000d, पूर्ण,
	RF_CHANNEL( 3) = अणु 0x03e790, 0x033331, 0x00000d, पूर्ण,
	RF_CHANNEL( 4) = अणु 0x03e790, 0x0b3331, 0x00000d, पूर्ण,
	RF_CHANNEL( 5) = अणु 0x03f7a0, 0x033331, 0x00000d, पूर्ण,
	RF_CHANNEL( 6) = अणु 0x03f7a0, 0x0b3331, 0x00000d, पूर्ण,
	RF_CHANNEL( 7) = अणु 0x03e7a0, 0x033331, 0x00000d, पूर्ण,
	RF_CHANNEL( 8) = अणु 0x03e7a0, 0x0b3331, 0x00000d, पूर्ण,
	RF_CHANNEL( 9) = अणु 0x03f7b0, 0x033331, 0x00000d, पूर्ण,
	RF_CHANNEL(10) = अणु 0x03f7b0, 0x0b3331, 0x00000d, पूर्ण,
	RF_CHANNEL(11) = अणु 0x03e7b0, 0x033331, 0x00000d, पूर्ण,
	RF_CHANNEL(12) = अणु 0x03e7b0, 0x0b3331, 0x00000d, पूर्ण,
	RF_CHANNEL(13) = अणु 0x03f7c0, 0x033331, 0x00000d, पूर्ण,
	RF_CHANNEL(14) = अणु 0x03e7c0, 0x066661, 0x00000d, पूर्ण,
पूर्ण;

अटल स्थिर u32 zd1211b_al2230_table[][3] = अणु
	RF_CHANNEL( 1) = अणु 0x09efc0, 0x8cccc0, 0xb00000, पूर्ण,
	RF_CHANNEL( 2) = अणु 0x09efc0, 0x8cccd0, 0xb00000, पूर्ण,
	RF_CHANNEL( 3) = अणु 0x09e7c0, 0x8cccc0, 0xb00000, पूर्ण,
	RF_CHANNEL( 4) = अणु 0x09e7c0, 0x8cccd0, 0xb00000, पूर्ण,
	RF_CHANNEL( 5) = अणु 0x05efc0, 0x8cccc0, 0xb00000, पूर्ण,
	RF_CHANNEL( 6) = अणु 0x05efc0, 0x8cccd0, 0xb00000, पूर्ण,
	RF_CHANNEL( 7) = अणु 0x05e7c0, 0x8cccc0, 0xb00000, पूर्ण,
	RF_CHANNEL( 8) = अणु 0x05e7c0, 0x8cccd0, 0xb00000, पूर्ण,
	RF_CHANNEL( 9) = अणु 0x0defc0, 0x8cccc0, 0xb00000, पूर्ण,
	RF_CHANNEL(10) = अणु 0x0defc0, 0x8cccd0, 0xb00000, पूर्ण,
	RF_CHANNEL(11) = अणु 0x0de7c0, 0x8cccc0, 0xb00000, पूर्ण,
	RF_CHANNEL(12) = अणु 0x0de7c0, 0x8cccd0, 0xb00000, पूर्ण,
	RF_CHANNEL(13) = अणु 0x03efc0, 0x8cccc0, 0xb00000, पूर्ण,
	RF_CHANNEL(14) = अणु 0x03e7c0, 0x866660, 0xb00000, पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा zd_ioreq16 zd1211b_ioreqs_shared_1[] = अणु
	अणु ZD_CR240, 0x57 पूर्ण, अणु ZD_CR9,   0xe0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा zd_ioreq16 ioreqs_init_al2230s[] = अणु
	अणु ZD_CR47,   0x1e पूर्ण, /* MARK_002 */
	अणु ZD_CR106,  0x22 पूर्ण,
	अणु ZD_CR107,  0x2a पूर्ण, /* MARK_002 */
	अणु ZD_CR109,  0x13 पूर्ण, /* MARK_002 */
	अणु ZD_CR118,  0xf8 पूर्ण, /* MARK_002 */
	अणु ZD_CR119,  0x12 पूर्ण, अणु ZD_CR122,  0xe0 पूर्ण,
	अणु ZD_CR128,  0x10 पूर्ण, /* MARK_001 from 0xe->0x10 */
	अणु ZD_CR129,  0x0e पूर्ण, /* MARK_001 from 0xd->0x0e */
	अणु ZD_CR130,  0x10 पूर्ण, /* MARK_001 from 0xb->0x0d */
पूर्ण;

अटल पूर्णांक zd1211b_al2230_finalize_rf(काष्ठा zd_chip *chip)
अणु
	पूर्णांक r;
	अटल स्थिर काष्ठा zd_ioreq16 ioreqs[] = अणु
		अणु ZD_CR80,  0x30 पूर्ण, अणु ZD_CR81,  0x30 पूर्ण, अणु ZD_CR79,  0x58 पूर्ण,
		अणु ZD_CR12,  0xf0 पूर्ण, अणु ZD_CR77,  0x1b पूर्ण, अणु ZD_CR78,  0x58 पूर्ण,
		अणु ZD_CR203, 0x06 पूर्ण,
		अणु पूर्ण,

		अणु ZD_CR240, 0x80 पूर्ण,
	पूर्ण;

	r = zd_ioग_लिखो16a_locked(chip, ioreqs, ARRAY_SIZE(ioreqs));
	अगर (r)
		वापस r;

	/* related to antenna selection? */
	अगर (chip->new_phy_layout) अणु
		r = zd_ioग_लिखो16_locked(chip, 0xe1, ZD_CR9);
		अगर (r)
			वापस r;
	पूर्ण

	वापस zd_ioग_लिखो16_locked(chip, 0x06, ZD_CR203);
पूर्ण

अटल पूर्णांक zd1211_al2230_init_hw(काष्ठा zd_rf *rf)
अणु
	पूर्णांक r;
	काष्ठा zd_chip *chip = zd_rf_to_chip(rf);

	अटल स्थिर काष्ठा zd_ioreq16 ioreqs_init[] = अणु
		अणु ZD_CR15,   0x20 पूर्ण, अणु ZD_CR23,   0x40 पूर्ण, अणु ZD_CR24,  0x20 पूर्ण,
		अणु ZD_CR26,   0x11 पूर्ण, अणु ZD_CR28,   0x3e पूर्ण, अणु ZD_CR29,  0x00 पूर्ण,
		अणु ZD_CR44,   0x33 पूर्ण, अणु ZD_CR106,  0x2a पूर्ण, अणु ZD_CR107, 0x1a पूर्ण,
		अणु ZD_CR109,  0x09 पूर्ण, अणु ZD_CR110,  0x27 पूर्ण, अणु ZD_CR111, 0x2b पूर्ण,
		अणु ZD_CR112,  0x2b पूर्ण, अणु ZD_CR119,  0x0a पूर्ण, अणु ZD_CR10,  0x89 पूर्ण,
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
		अणु ZD_CR92,   0x0a पूर्ण, अणु ZD_CR99,   0x28 पूर्ण, अणु ZD_CR100, 0x00 पूर्ण,
		अणु ZD_CR101,  0x13 पूर्ण, अणु ZD_CR102,  0x27 पूर्ण, अणु ZD_CR106, 0x24 पूर्ण,
		अणु ZD_CR107,  0x2a पूर्ण, अणु ZD_CR109,  0x09 पूर्ण, अणु ZD_CR110, 0x13 पूर्ण,
		अणु ZD_CR111,  0x1f पूर्ण, अणु ZD_CR112,  0x1f पूर्ण, अणु ZD_CR113, 0x27 पूर्ण,
		अणु ZD_CR114,  0x27 पूर्ण,
		/* क्रम newest (3rd cut) AL2300 */
		अणु ZD_CR115,  0x24 पूर्ण,
		अणु ZD_CR116,  0x24 पूर्ण, अणु ZD_CR117,  0xf4 पूर्ण, अणु ZD_CR118, 0xfc पूर्ण,
		अणु ZD_CR119,  0x10 पूर्ण, अणु ZD_CR120,  0x4f पूर्ण, अणु ZD_CR121, 0x77 पूर्ण,
		अणु ZD_CR122,  0xe0 पूर्ण, अणु ZD_CR137,  0x88 पूर्ण, अणु ZD_CR252, 0xff पूर्ण,
		अणु ZD_CR253,  0xff पूर्ण,
	पूर्ण;

	अटल स्थिर काष्ठा zd_ioreq16 ioreqs_pll[] = अणु
		/* shdnb(PLL_ON)=0 */
		अणु ZD_CR251,  0x2f पूर्ण,
		/* shdnb(PLL_ON)=1 */
		अणु ZD_CR251,  0x3f पूर्ण,
		अणु ZD_CR138,  0x28 पूर्ण, अणु ZD_CR203,  0x06 पूर्ण,
	पूर्ण;

	अटल स्थिर u32 rv1[] = अणु
		/* Channel 1 */
		0x03f790,
		0x033331,
		0x00000d,

		0x0b3331,
		0x03b812,
		0x00fff3,
	पूर्ण;

	अटल स्थिर u32 rv2[] = अणु
		0x000da4,
		0x0f4dc5, /* fix freq shअगरt, 0x04edc5 */
		0x0805b6,
		0x011687,
		0x000688,
		0x0403b9, /* बाह्यal control TX घातer (ZD_CR31) */
		0x00dbba,
		0x00099b,
		0x0bdffc,
		0x00000d,
		0x00500f,
	पूर्ण;

	अटल स्थिर u32 rv3[] = अणु
		0x00d00f,
		0x004c0f,
		0x00540f,
		0x00700f,
		0x00500f,
	पूर्ण;

	r = zd_ioग_लिखो16a_locked(chip, ioreqs_init, ARRAY_SIZE(ioreqs_init));
	अगर (r)
		वापस r;

	अगर (IS_AL2230S(chip)) अणु
		r = zd_ioग_लिखो16a_locked(chip, ioreqs_init_al2230s,
			ARRAY_SIZE(ioreqs_init_al2230s));
		अगर (r)
			वापस r;
	पूर्ण

	r = zd_rख_डालोv_locked(chip, rv1, ARRAY_SIZE(rv1), RF_RV_BITS);
	अगर (r)
		वापस r;

	/* improve band edge क्रम AL2230S */
	अगर (IS_AL2230S(chip))
		r = zd_rख_डालो_locked(chip, 0x000824, RF_RV_BITS);
	अन्यथा
		r = zd_rख_डालो_locked(chip, 0x0005a4, RF_RV_BITS);
	अगर (r)
		वापस r;

	r = zd_rख_डालोv_locked(chip, rv2, ARRAY_SIZE(rv2), RF_RV_BITS);
	अगर (r)
		वापस r;

	r = zd_ioग_लिखो16a_locked(chip, ioreqs_pll, ARRAY_SIZE(ioreqs_pll));
	अगर (r)
		वापस r;

	r = zd_rख_डालोv_locked(chip, rv3, ARRAY_SIZE(rv3), RF_RV_BITS);
	अगर (r)
		वापस r;

	वापस 0;
पूर्ण

अटल पूर्णांक zd1211b_al2230_init_hw(काष्ठा zd_rf *rf)
अणु
	पूर्णांक r;
	काष्ठा zd_chip *chip = zd_rf_to_chip(rf);

	अटल स्थिर काष्ठा zd_ioreq16 ioreqs1[] = अणु
		अणु ZD_CR10,  0x89 पूर्ण, अणु ZD_CR15,  0x20 पूर्ण,
		अणु ZD_CR17,  0x2B पूर्ण, /* क्रम newest(3rd cut) AL2230 */
		अणु ZD_CR23,  0x40 पूर्ण, अणु ZD_CR24,  0x20 पूर्ण, अणु ZD_CR26,  0x93 पूर्ण,
		अणु ZD_CR28,  0x3e पूर्ण, अणु ZD_CR29,  0x00 पूर्ण,
		अणु ZD_CR33,  0x28 पूर्ण, /* 5621 */
		अणु ZD_CR34,  0x30 पूर्ण,
		अणु ZD_CR35,  0x3e पूर्ण, /* क्रम newest(3rd cut) AL2230 */
		अणु ZD_CR41,  0x24 पूर्ण, अणु ZD_CR44,  0x32 पूर्ण,
		अणु ZD_CR46,  0x99 पूर्ण, /* क्रम newest(3rd cut) AL2230 */
		अणु ZD_CR47,  0x1e पूर्ण,

		/* ZD1211B 05.06.10 */
		अणु ZD_CR48,  0x06 पूर्ण, अणु ZD_CR49,  0xf9 पूर्ण, अणु ZD_CR51,  0x01 पूर्ण,
		अणु ZD_CR52,  0x80 पूर्ण, अणु ZD_CR53,  0x7e पूर्ण, अणु ZD_CR65,  0x00 पूर्ण,
		अणु ZD_CR66,  0x00 पूर्ण, अणु ZD_CR67,  0x00 पूर्ण, अणु ZD_CR68,  0x00 पूर्ण,
		अणु ZD_CR69,  0x28 पूर्ण,

		अणु ZD_CR79,  0x58 पूर्ण, अणु ZD_CR80,  0x30 पूर्ण, अणु ZD_CR81,  0x30 पूर्ण,
		अणु ZD_CR87,  0x0a पूर्ण, अणु ZD_CR89,  0x04 पूर्ण,
		अणु ZD_CR91,  0x00 पूर्ण, /* 5621 */
		अणु ZD_CR92,  0x0a पूर्ण,
		अणु ZD_CR98,  0x8d पूर्ण, /* 4804,  क्रम 1212 new algorithm */
		अणु ZD_CR99,  0x00 पूर्ण, /* 5621 */
		अणु ZD_CR101, 0x13 पूर्ण, अणु ZD_CR102, 0x27 पूर्ण,
		अणु ZD_CR106, 0x24 पूर्ण, /* क्रम newest(3rd cut) AL2230 */
		अणु ZD_CR107, 0x2a पूर्ण,
		अणु ZD_CR109, 0x13 पूर्ण, /* 4804, क्रम 1212 new algorithm */
		अणु ZD_CR110, 0x1f पूर्ण, /* 4804, क्रम 1212 new algorithm */
		अणु ZD_CR111, 0x1f पूर्ण, अणु ZD_CR112, 0x1f पूर्ण, अणु ZD_CR113, 0x27 पूर्ण,
		अणु ZD_CR114, 0x27 पूर्ण,
		अणु ZD_CR115, 0x26 पूर्ण, /* 24->26 at 4902 क्रम newest(3rd cut)
				     * AL2230
				     */
		अणु ZD_CR116, 0x24 पूर्ण,
		अणु ZD_CR117, 0xfa पूर्ण, /* क्रम 1211b */
		अणु ZD_CR118, 0xfa पूर्ण, /* क्रम 1211b */
		अणु ZD_CR119, 0x10 पूर्ण,
		अणु ZD_CR120, 0x4f पूर्ण,
		अणु ZD_CR121, 0x6c पूर्ण, /* क्रम 1211b */
		अणु ZD_CR122, 0xfc पूर्ण, /* E0->FC at 4902 */
		अणु ZD_CR123, 0x57 पूर्ण, /* 5623 */
		अणु ZD_CR125, 0xad पूर्ण, /* 4804, क्रम 1212 new algorithm */
		अणु ZD_CR126, 0x6c पूर्ण, /* 5614 */
		अणु ZD_CR127, 0x03 पूर्ण, /* 4804, क्रम 1212 new algorithm */
		अणु ZD_CR137, 0x50 पूर्ण, /* 5614 */
		अणु ZD_CR138, 0xa8 पूर्ण,
		अणु ZD_CR144, 0xac पूर्ण, /* 5621 */
		अणु ZD_CR150, 0x0d पूर्ण, अणु ZD_CR252, 0x34 पूर्ण, अणु ZD_CR253, 0x34 पूर्ण,
	पूर्ण;

	अटल स्थिर u32 rv1[] = अणु
		0x8cccd0,
		0x481dc0,
		0xcfff00,
		0x25a000,
	पूर्ण;

	अटल स्थिर u32 rv2[] = अणु
		/* To improve AL2230 yield, improve phase noise, 4713 */
		0x25a000,
		0xa3b2f0,

		0x6da010, /* Reg6 update क्रम MP versio */
		0xe36280, /* Modअगरied by jxiao क्रम Bor-Chin on 2004/08/02 */
		0x116000,
		0x9dc020, /* External control TX घातer (ZD_CR31) */
		0x5ddb00, /* RegA update क्रम MP version */
		0xd99000, /* RegB update क्रम MP version */
		0x3ffbd0, /* RegC update क्रम MP version */
		0xb00000, /* RegD update क्रम MP version */

		/* improve phase noise and हटाओ phase calibration,4713 */
		0xf01a00,
	पूर्ण;

	अटल स्थिर काष्ठा zd_ioreq16 ioreqs2[] = अणु
		अणु ZD_CR251, 0x2f पूर्ण, /* shdnb(PLL_ON)=0 */
		अणु ZD_CR251, 0x7f पूर्ण, /* shdnb(PLL_ON)=1 */
	पूर्ण;

	अटल स्थिर u32 rv3[] = अणु
		/* To improve AL2230 yield, 4713 */
		0xf01b00,
		0xf01e00,
		0xf01a00,
	पूर्ण;

	अटल स्थिर काष्ठा zd_ioreq16 ioreqs3[] = अणु
		/* related to 6M band edge patching, happens unconditionally */
		अणु ZD_CR128, 0x14 पूर्ण, अणु ZD_CR129, 0x12 पूर्ण, अणु ZD_CR130, 0x10 पूर्ण,
	पूर्ण;

	r = zd_ioग_लिखो16a_locked(chip, zd1211b_ioreqs_shared_1,
		ARRAY_SIZE(zd1211b_ioreqs_shared_1));
	अगर (r)
		वापस r;
	r = zd_ioग_लिखो16a_locked(chip, ioreqs1, ARRAY_SIZE(ioreqs1));
	अगर (r)
		वापस r;

	अगर (IS_AL2230S(chip)) अणु
		r = zd_ioग_लिखो16a_locked(chip, ioreqs_init_al2230s,
			ARRAY_SIZE(ioreqs_init_al2230s));
		अगर (r)
			वापस r;
	पूर्ण

	r = zd_rख_डालोv_cr_locked(chip, zd1211b_al2230_table[0], 3);
	अगर (r)
		वापस r;
	r = zd_rख_डालोv_cr_locked(chip, rv1, ARRAY_SIZE(rv1));
	अगर (r)
		वापस r;

	अगर (IS_AL2230S(chip))
		r = zd_rख_डालो_locked(chip, 0x241000, RF_RV_BITS);
	अन्यथा
		r = zd_rख_डालो_locked(chip, 0x25a000, RF_RV_BITS);
	अगर (r)
		वापस r;

	r = zd_rख_डालोv_cr_locked(chip, rv2, ARRAY_SIZE(rv2));
	अगर (r)
		वापस r;
	r = zd_ioग_लिखो16a_locked(chip, ioreqs2, ARRAY_SIZE(ioreqs2));
	अगर (r)
		वापस r;
	r = zd_rख_डालोv_cr_locked(chip, rv3, ARRAY_SIZE(rv3));
	अगर (r)
		वापस r;
	r = zd_ioग_लिखो16a_locked(chip, ioreqs3, ARRAY_SIZE(ioreqs3));
	अगर (r)
		वापस r;
	वापस zd1211b_al2230_finalize_rf(chip);
पूर्ण

अटल पूर्णांक zd1211_al2230_set_channel(काष्ठा zd_rf *rf, u8 channel)
अणु
	पूर्णांक r;
	स्थिर u32 *rv = zd1211_al2230_table[channel-1];
	काष्ठा zd_chip *chip = zd_rf_to_chip(rf);
	अटल स्थिर काष्ठा zd_ioreq16 ioreqs[] = अणु
		अणु ZD_CR138, 0x28 पूर्ण,
		अणु ZD_CR203, 0x06 पूर्ण,
	पूर्ण;

	r = zd_rख_डालोv_locked(chip, rv, 3, RF_RV_BITS);
	अगर (r)
		वापस r;
	वापस zd_ioग_लिखो16a_locked(chip, ioreqs, ARRAY_SIZE(ioreqs));
पूर्ण

अटल पूर्णांक zd1211b_al2230_set_channel(काष्ठा zd_rf *rf, u8 channel)
अणु
	पूर्णांक r;
	स्थिर u32 *rv = zd1211b_al2230_table[channel-1];
	काष्ठा zd_chip *chip = zd_rf_to_chip(rf);

	r = zd_ioग_लिखो16a_locked(chip, zd1211b_ioreqs_shared_1,
		ARRAY_SIZE(zd1211b_ioreqs_shared_1));
	अगर (r)
		वापस r;

	r = zd_rख_डालोv_cr_locked(chip, rv, 3);
	अगर (r)
		वापस r;

	वापस zd1211b_al2230_finalize_rf(chip);
पूर्ण

अटल पूर्णांक zd1211_al2230_चयन_radio_on(काष्ठा zd_rf *rf)
अणु
	काष्ठा zd_chip *chip = zd_rf_to_chip(rf);
	अटल स्थिर काष्ठा zd_ioreq16 ioreqs[] = अणु
		अणु ZD_CR11,  0x00 पूर्ण,
		अणु ZD_CR251, 0x3f पूर्ण,
	पूर्ण;

	वापस zd_ioग_लिखो16a_locked(chip, ioreqs, ARRAY_SIZE(ioreqs));
पूर्ण

अटल पूर्णांक zd1211b_al2230_चयन_radio_on(काष्ठा zd_rf *rf)
अणु
	काष्ठा zd_chip *chip = zd_rf_to_chip(rf);
	अटल स्थिर काष्ठा zd_ioreq16 ioreqs[] = अणु
		अणु ZD_CR11,  0x00 पूर्ण,
		अणु ZD_CR251, 0x7f पूर्ण,
	पूर्ण;

	वापस zd_ioग_लिखो16a_locked(chip, ioreqs, ARRAY_SIZE(ioreqs));
पूर्ण

अटल पूर्णांक al2230_चयन_radio_off(काष्ठा zd_rf *rf)
अणु
	काष्ठा zd_chip *chip = zd_rf_to_chip(rf);
	अटल स्थिर काष्ठा zd_ioreq16 ioreqs[] = अणु
		अणु ZD_CR11,  0x04 पूर्ण,
		अणु ZD_CR251, 0x2f पूर्ण,
	पूर्ण;

	वापस zd_ioग_लिखो16a_locked(chip, ioreqs, ARRAY_SIZE(ioreqs));
पूर्ण

पूर्णांक zd_rf_init_al2230(काष्ठा zd_rf *rf)
अणु
	काष्ठा zd_chip *chip = zd_rf_to_chip(rf);

	rf->चयन_radio_off = al2230_चयन_radio_off;
	अगर (zd_chip_is_zd1211b(chip)) अणु
		rf->init_hw = zd1211b_al2230_init_hw;
		rf->set_channel = zd1211b_al2230_set_channel;
		rf->चयन_radio_on = zd1211b_al2230_चयन_radio_on;
	पूर्ण अन्यथा अणु
		rf->init_hw = zd1211_al2230_init_hw;
		rf->set_channel = zd1211_al2230_set_channel;
		rf->चयन_radio_on = zd1211_al2230_चयन_radio_on;
	पूर्ण
	rf->patch_6m_band_edge = zd_rf_generic_patch_6m;
	rf->patch_cck_gain = 1;
	वापस 0;
पूर्ण
