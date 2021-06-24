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

अटल स्थिर u32 rf2959_table[][2] = अणु
	RF_CHANNEL( 1) = अणु 0x181979, 0x1e6666 पूर्ण,
	RF_CHANNEL( 2) = अणु 0x181989, 0x1e6666 पूर्ण,
	RF_CHANNEL( 3) = अणु 0x181999, 0x1e6666 पूर्ण,
	RF_CHANNEL( 4) = अणु 0x1819a9, 0x1e6666 पूर्ण,
	RF_CHANNEL( 5) = अणु 0x1819b9, 0x1e6666 पूर्ण,
	RF_CHANNEL( 6) = अणु 0x1819c9, 0x1e6666 पूर्ण,
	RF_CHANNEL( 7) = अणु 0x1819d9, 0x1e6666 पूर्ण,
	RF_CHANNEL( 8) = अणु 0x1819e9, 0x1e6666 पूर्ण,
	RF_CHANNEL( 9) = अणु 0x1819f9, 0x1e6666 पूर्ण,
	RF_CHANNEL(10) = अणु 0x181a09, 0x1e6666 पूर्ण,
	RF_CHANNEL(11) = अणु 0x181a19, 0x1e6666 पूर्ण,
	RF_CHANNEL(12) = अणु 0x181a29, 0x1e6666 पूर्ण,
	RF_CHANNEL(13) = अणु 0x181a39, 0x1e6666 पूर्ण,
	RF_CHANNEL(14) = अणु 0x181a60, 0x1c0000 पूर्ण,
पूर्ण;

#अगर 0
अटल पूर्णांक bits(u32 rw, पूर्णांक from, पूर्णांक to)
अणु
	rw &= ~(0xffffffffU << (to+1));
	rw >>= from;
	वापस rw;
पूर्ण

अटल पूर्णांक bit(u32 rw, पूर्णांक bit)
अणु
	वापस bits(rw, bit, bit);
पूर्ण

अटल व्योम dump_regग_लिखो(u32 rw)
अणु
	पूर्णांक reg = bits(rw, 18, 22);
	पूर्णांक rw_flag = bits(rw, 23, 23);
	PDEBUG("rf2959 %#010x reg %d rw %d", rw, reg, rw_flag);

	चयन (reg) अणु
	हाल 0:
		PDEBUG("reg0 CFG1 ref_sel %d hibernate %d rf_vco_reg_en %d"
		       " if_vco_reg_en %d if_vga_en %d",
		       bits(rw, 14, 15), bit(rw, 3), bit(rw, 2), bit(rw, 1),
		       bit(rw, 0));
		अवरोध;
	हाल 1:
		PDEBUG("reg1 IFPLL1 pll_en1 %d kv_en1 %d vtc_en1 %d lpf1 %d"
		       " cpl1 %d pdp1 %d autocal_en1 %d ld_en1 %d ifloopr %d"
		       " ifloopc %d dac1 %d",
		       bit(rw, 17), bit(rw, 16), bit(rw, 15), bit(rw, 14),
		       bit(rw, 13), bit(rw, 12), bit(rw, 11), bit(rw, 10),
		       bits(rw, 7, 9), bits(rw, 4, 6), bits(rw, 0, 3));
		अवरोध;
	हाल 2:
		PDEBUG("reg2 IFPLL2 n1 %d num1 %d",
		       bits(rw, 6, 17), bits(rw, 0, 5));
		अवरोध;
	हाल 3:
		PDEBUG("reg3 IFPLL3 num %d", bits(rw, 0, 17));
		अवरोध;
	हाल 4:
		PDEBUG("reg4 IFPLL4 dn1 %#04x ct_def1 %d kv_def1 %d",
		       bits(rw, 8, 16), bits(rw, 4, 7), bits(rw, 0, 3));
		अवरोध;
	हाल 5:
		PDEBUG("reg5 RFPLL1 pll_en %d kv_en %d vtc_en %d lpf %d cpl %d"
		       " pdp %d autocal_en %d ld_en %d rfloopr %d rfloopc %d"
		       " dac %d",
		       bit(rw, 17), bit(rw, 16), bit(rw, 15), bit(rw, 14),
		       bit(rw, 13), bit(rw, 12), bit(rw, 11), bit(rw, 10),
		       bits(rw, 7, 9), bits(rw, 4, 6), bits(rw, 0,3));
		अवरोध;
	हाल 6:
		PDEBUG("reg6 RFPLL2 n %d num %d",
		       bits(rw, 6, 17), bits(rw, 0, 5));
		अवरोध;
	हाल 7:
		PDEBUG("reg7 RFPLL3 num2 %d", bits(rw, 0, 17));
		अवरोध;
	हाल 8:
		PDEBUG("reg8 RFPLL4 dn %#06x ct_def %d kv_def %d",
		       bits(rw, 8, 16), bits(rw, 4, 7), bits(rw, 0, 3));
		अवरोध;
	हाल 9:
		PDEBUG("reg9 CAL1 tvco %d tlock %d m_ct_value %d ld_window %d",
		       bits(rw, 13, 17), bits(rw, 8, 12), bits(rw, 3, 7),
		       bits(rw, 0, 2));
		अवरोध;
	हाल 10:
		PDEBUG("reg10 TXRX1 rxdcfbbyps %d pcontrol %d txvgc %d"
		       " rxlpfbw %d txlpfbw %d txdiffmode %d txenmode %d"
		       " intbiasen %d tybypass %d",
		       bit(rw, 17), bits(rw, 15, 16), bits(rw, 10, 14),
		       bits(rw, 7, 9), bits(rw, 4, 6), bit(rw, 3), bit(rw, 2),
		       bit(rw, 1), bit(rw, 0));
		अवरोध;
	हाल 11:
		PDEBUG("reg11 PCNT1 mid_bias %d p_desired %d pc_offset %d"
			" tx_delay %d",
			bits(rw, 15, 17), bits(rw, 9, 14), bits(rw, 3, 8),
			bits(rw, 0, 2));
		अवरोध;
	हाल 12:
		PDEBUG("reg12 PCNT2 max_power %d mid_power %d min_power %d",
		       bits(rw, 12, 17), bits(rw, 6, 11), bits(rw, 0, 5));
		अवरोध;
	हाल 13:
		PDEBUG("reg13 VCOT1 rfpll vco comp %d ifpll vco comp %d"
		       " lobias %d if_biasbuf %d if_biasvco %d rf_biasbuf %d"
		       " rf_biasvco %d",
		       bit(rw, 17), bit(rw, 16), bit(rw, 15),
		       bits(rw, 8, 9), bits(rw, 5, 7), bits(rw, 3, 4),
		       bits(rw, 0, 2));
		अवरोध;
	हाल 14:
		PDEBUG("reg14 IQCAL rx_acal %d rx_pcal %d"
		       " tx_acal %d tx_pcal %d",
		       bits(rw, 13, 17), bits(rw, 9, 12), bits(rw, 4, 8),
		       bits(rw, 0, 3));
		अवरोध;
	पूर्ण
पूर्ण
#पूर्ण_अगर /* 0 */

अटल पूर्णांक rf2959_init_hw(काष्ठा zd_rf *rf)
अणु
	पूर्णांक r;
	काष्ठा zd_chip *chip = zd_rf_to_chip(rf);

	अटल स्थिर काष्ठा zd_ioreq16 ioreqs[] = अणु
		अणु ZD_CR2,   0x1E पूर्ण, अणु ZD_CR9,   0x20 पूर्ण, अणु ZD_CR10,  0x89 पूर्ण,
		अणु ZD_CR11,  0x00 पूर्ण, अणु ZD_CR15,  0xD0 पूर्ण, अणु ZD_CR17,  0x68 पूर्ण,
		अणु ZD_CR19,  0x4a पूर्ण, अणु ZD_CR20,  0x0c पूर्ण, अणु ZD_CR21,  0x0E पूर्ण,
		अणु ZD_CR23,  0x48 पूर्ण,
		/* normal size क्रम cca threshold */
		अणु ZD_CR24,  0x14 पूर्ण,
		/* अणु ZD_CR24,  0x20 पूर्ण, */
		अणु ZD_CR26,  0x90 पूर्ण, अणु ZD_CR27,  0x30 पूर्ण, अणु ZD_CR29,  0x20 पूर्ण,
		अणु ZD_CR31,  0xb2 पूर्ण, अणु ZD_CR32,  0x43 पूर्ण, अणु ZD_CR33,  0x28 पूर्ण,
		अणु ZD_CR38,  0x30 पूर्ण, अणु ZD_CR34,  0x0f पूर्ण, अणु ZD_CR35,  0xF0 पूर्ण,
		अणु ZD_CR41,  0x2a पूर्ण, अणु ZD_CR46,  0x7F पूर्ण, अणु ZD_CR47,  0x1E पूर्ण,
		अणु ZD_CR51,  0xc5 पूर्ण, अणु ZD_CR52,  0xc5 पूर्ण, अणु ZD_CR53,  0xc5 पूर्ण,
		अणु ZD_CR79,  0x58 पूर्ण, अणु ZD_CR80,  0x30 पूर्ण, अणु ZD_CR81,  0x30 पूर्ण,
		अणु ZD_CR82,  0x00 पूर्ण, अणु ZD_CR83,  0x24 पूर्ण, अणु ZD_CR84,  0x04 पूर्ण,
		अणु ZD_CR85,  0x00 पूर्ण, अणु ZD_CR86,  0x10 पूर्ण, अणु ZD_CR87,  0x2A पूर्ण,
		अणु ZD_CR88,  0x10 पूर्ण, अणु ZD_CR89,  0x24 पूर्ण, अणु ZD_CR90,  0x18 पूर्ण,
		/* अणु ZD_CR91,  0x18 पूर्ण, */
		/* should solve continuous CTS frame problems */
		अणु ZD_CR91,  0x00 पूर्ण,
		अणु ZD_CR92,  0x0a पूर्ण, अणु ZD_CR93,  0x00 पूर्ण, अणु ZD_CR94,  0x01 पूर्ण,
		अणु ZD_CR95,  0x00 पूर्ण, अणु ZD_CR96,  0x40 पूर्ण, अणु ZD_CR97,  0x37 पूर्ण,
		अणु ZD_CR98,  0x05 पूर्ण, अणु ZD_CR99,  0x28 पूर्ण, अणु ZD_CR100, 0x00 पूर्ण,
		अणु ZD_CR101, 0x13 पूर्ण, अणु ZD_CR102, 0x27 पूर्ण, अणु ZD_CR103, 0x27 पूर्ण,
		अणु ZD_CR104, 0x18 पूर्ण, अणु ZD_CR105, 0x12 पूर्ण,
		/* normal size */
		अणु ZD_CR106, 0x1a पूर्ण,
		/* अणु ZD_CR106, 0x22 पूर्ण, */
		अणु ZD_CR107, 0x24 पूर्ण, अणु ZD_CR108, 0x0a पूर्ण, अणु ZD_CR109, 0x13 पूर्ण,
		अणु ZD_CR110, 0x2F पूर्ण, अणु ZD_CR111, 0x27 पूर्ण, अणु ZD_CR112, 0x27 पूर्ण,
		अणु ZD_CR113, 0x27 पूर्ण, अणु ZD_CR114, 0x27 पूर्ण, अणु ZD_CR115, 0x40 पूर्ण,
		अणु ZD_CR116, 0x40 पूर्ण, अणु ZD_CR117, 0xF0 पूर्ण, अणु ZD_CR118, 0xF0 पूर्ण,
		अणु ZD_CR119, 0x16 पूर्ण,
		/* no TX continuation */
		अणु ZD_CR122, 0x00 पूर्ण,
		/* अणु ZD_CR122, 0xff पूर्ण, */
		अणु ZD_CR127, 0x03 पूर्ण, अणु ZD_CR131, 0x08 पूर्ण, अणु ZD_CR138, 0x28 पूर्ण,
		अणु ZD_CR148, 0x44 पूर्ण, अणु ZD_CR150, 0x10 पूर्ण, अणु ZD_CR169, 0xBB पूर्ण,
		अणु ZD_CR170, 0xBB पूर्ण,
	पूर्ण;

	अटल स्थिर u32 rv[] = अणु
		0x000007,  /* REG0(CFG1) */
		0x07dd43,  /* REG1(IFPLL1) */
		0x080959,  /* REG2(IFPLL2) */
		0x0e6666,
		0x116a57,  /* REG4 */
		0x17dd43,  /* REG5 */
		0x1819f9,  /* REG6 */
		0x1e6666,
		0x214554,
		0x25e7fa,
		0x27fffa,
		/* The Zydas driver somehow क्रममाला_लो to set this value. It's
		 * only set क्रम Japan. We are using पूर्णांकernal घातer control
		 * क्रम now.
		 */
		0x294128, /* पूर्णांकernal घातer */
		/* 0x28252c, */ /* External control TX घातer */
		/* ZD_CR31_CCK, ZD_CR51_6-36M, ZD_CR52_48M, ZD_CR53_54M */
		0x2c0000,
		0x300000,
		0x340000,  /* REG13(0xD) */
		0x381e0f,  /* REG14(0xE) */
		/* Bogus, RF2959's data sheet doesn't know रेजिस्टर 27, which is
		 * actually referenced here. The commented 0x11 is 17.
		 */
		0x6c180f,  /* REG27(0x11) */
	पूर्ण;

	r = zd_ioग_लिखो16a_locked(chip, ioreqs, ARRAY_SIZE(ioreqs));
	अगर (r)
		वापस r;

	वापस zd_rख_डालोv_locked(chip, rv, ARRAY_SIZE(rv), RF_RV_BITS);
पूर्ण

अटल पूर्णांक rf2959_set_channel(काष्ठा zd_rf *rf, u8 channel)
अणु
	पूर्णांक i, r;
	स्थिर u32 *rv = rf2959_table[channel-1];
	काष्ठा zd_chip *chip = zd_rf_to_chip(rf);

	क्रम (i = 0; i < 2; i++) अणु
		r = zd_rख_डालो_locked(chip, rv[i], RF_RV_BITS);
		अगर (r)
			वापस r;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक rf2959_चयन_radio_on(काष्ठा zd_rf *rf)
अणु
	अटल स्थिर काष्ठा zd_ioreq16 ioreqs[] = अणु
		अणु ZD_CR10, 0x89 पूर्ण,
		अणु ZD_CR11, 0x00 पूर्ण,
	पूर्ण;
	काष्ठा zd_chip *chip = zd_rf_to_chip(rf);

	वापस zd_ioग_लिखो16a_locked(chip, ioreqs, ARRAY_SIZE(ioreqs));
पूर्ण

अटल पूर्णांक rf2959_चयन_radio_off(काष्ठा zd_rf *rf)
अणु
	अटल स्थिर काष्ठा zd_ioreq16 ioreqs[] = अणु
		अणु ZD_CR10, 0x15 पूर्ण,
		अणु ZD_CR11, 0x81 पूर्ण,
	पूर्ण;
	काष्ठा zd_chip *chip = zd_rf_to_chip(rf);

	वापस zd_ioग_लिखो16a_locked(chip, ioreqs, ARRAY_SIZE(ioreqs));
पूर्ण

पूर्णांक zd_rf_init_rf2959(काष्ठा zd_rf *rf)
अणु
	काष्ठा zd_chip *chip = zd_rf_to_chip(rf);

	अगर (zd_chip_is_zd1211b(chip)) अणु
		dev_err(zd_chip_dev(chip),
		       "RF2959 is currently not supported for ZD1211B"
		       " devices\n");
		वापस -ENODEV;
	पूर्ण
	rf->init_hw = rf2959_init_hw;
	rf->set_channel = rf2959_set_channel;
	rf->चयन_radio_on = rf2959_चयन_radio_on;
	rf->चयन_radio_off = rf2959_चयन_radio_off;
	वापस 0;
पूर्ण
