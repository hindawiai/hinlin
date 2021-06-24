<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c)  2020 Intel Corporation */

#समावेश "igc.h"
#समावेश "igc_diag.h"

अटल काष्ठा igc_reg_test reg_test[] = अणु
	अणु IGC_FCAL,	1,	PATTERN_TEST,	0xFFFFFFFF,	0xFFFFFFFF पूर्ण,
	अणु IGC_FCAH,	1,	PATTERN_TEST,	0x0000FFFF,	0xFFFFFFFF पूर्ण,
	अणु IGC_FCT,	1,	PATTERN_TEST,	0x0000FFFF,	0xFFFFFFFF पूर्ण,
	अणु IGC_RDBAH(0), 4,	PATTERN_TEST,	0xFFFFFFFF,	0xFFFFFFFF पूर्ण,
	अणु IGC_RDBAL(0),	4,	PATTERN_TEST,	0xFFFFFF80,	0xFFFFFF80 पूर्ण,
	अणु IGC_RDLEN(0),	4,	PATTERN_TEST,	0x000FFF80,	0x000FFFFF पूर्ण,
	अणु IGC_RDT(0),	4,	PATTERN_TEST,	0x0000FFFF,	0x0000FFFF पूर्ण,
	अणु IGC_FCRTH,	1,	PATTERN_TEST,	0x0003FFF0,	0x0003FFF0 पूर्ण,
	अणु IGC_FCTTV,	1,	PATTERN_TEST,	0x0000FFFF,	0x0000FFFF पूर्ण,
	अणु IGC_TIPG,	1,	PATTERN_TEST,	0x3FFFFFFF,	0x3FFFFFFF पूर्ण,
	अणु IGC_TDBAH(0),	4,	PATTERN_TEST,	0xFFFFFFFF,	0xFFFFFFFF पूर्ण,
	अणु IGC_TDBAL(0),	4,	PATTERN_TEST,	0xFFFFFF80,	0xFFFFFF80 पूर्ण,
	अणु IGC_TDLEN(0),	4,	PATTERN_TEST,	0x000FFF80,	0x000FFFFF पूर्ण,
	अणु IGC_TDT(0),	4,	PATTERN_TEST,	0x0000FFFF,	0x0000FFFF पूर्ण,
	अणु IGC_RCTL,	1,	SET_READ_TEST,	0xFFFFFFFF,	0x00000000 पूर्ण,
	अणु IGC_RCTL,	1,	SET_READ_TEST,	0x04CFB2FE,	0x003FFFFB पूर्ण,
	अणु IGC_RCTL,	1,	SET_READ_TEST,	0x04CFB2FE,	0xFFFFFFFF पूर्ण,
	अणु IGC_TCTL,	1,	SET_READ_TEST,	0xFFFFFFFF,	0x00000000 पूर्ण,
	अणु IGC_RA,	16,	TABLE64_TEST_LO,
						0xFFFFFFFF,	0xFFFFFFFF पूर्ण,
	अणु IGC_RA,	16,	TABLE64_TEST_HI,
						0x900FFFFF,	0xFFFFFFFF पूर्ण,
	अणु IGC_MTA,	128,	TABLE32_TEST,
						0xFFFFFFFF,	0xFFFFFFFF पूर्ण,
	अणु 0, 0, 0, 0पूर्ण
पूर्ण;

अटल bool reg_pattern_test(काष्ठा igc_adapter *adapter, u64 *data, पूर्णांक reg,
			     u32 mask, u32 ग_लिखो)
अणु
	काष्ठा igc_hw *hw = &adapter->hw;
	u32 pat, val, beक्रमe;
	अटल स्थिर u32 test_pattern[] = अणु
		0x5A5A5A5A, 0xA5A5A5A5, 0x00000000, 0xFFFFFFFF
	पूर्ण;

	क्रम (pat = 0; pat < ARRAY_SIZE(test_pattern); pat++) अणु
		beक्रमe = rd32(reg);
		wr32(reg, test_pattern[pat] & ग_लिखो);
		val = rd32(reg);
		अगर (val != (test_pattern[pat] & ग_लिखो & mask)) अणु
			netdev_err(adapter->netdev,
				   "pattern test reg %04X failed: got 0x%08X expected 0x%08X",
				   reg, val, test_pattern[pat] & ग_लिखो & mask);
			*data = reg;
			wr32(reg, beक्रमe);
			वापस false;
		पूर्ण
		wr32(reg, beक्रमe);
	पूर्ण
	वापस true;
पूर्ण

अटल bool reg_set_and_check(काष्ठा igc_adapter *adapter, u64 *data, पूर्णांक reg,
			      u32 mask, u32 ग_लिखो)
अणु
	काष्ठा igc_hw *hw = &adapter->hw;
	u32 val, beक्रमe;

	beक्रमe = rd32(reg);
	wr32(reg, ग_लिखो & mask);
	val = rd32(reg);
	अगर ((ग_लिखो & mask) != (val & mask)) अणु
		netdev_err(adapter->netdev,
			   "set/check reg %04X test failed: got 0x%08X expected 0x%08X",
			   reg, (val & mask), (ग_लिखो & mask));
		*data = reg;
		wr32(reg, beक्रमe);
		वापस false;
	पूर्ण
	wr32(reg, beक्रमe);
	वापस true;
पूर्ण

bool igc_reg_test(काष्ठा igc_adapter *adapter, u64 *data)
अणु
	काष्ठा igc_reg_test *test = reg_test;
	काष्ठा igc_hw *hw = &adapter->hw;
	u32 value, beक्रमe, after;
	u32 i, toggle, b = false;

	/* Because the status रेजिस्टर is such a special हाल,
	 * we handle it separately from the rest of the रेजिस्टर
	 * tests.  Some bits are पढ़ो-only, some toggle, and some
	 * are ग_लिखोable.
	 */
	toggle = 0x6800D3;
	beक्रमe = rd32(IGC_STATUS);
	value = beक्रमe & toggle;
	wr32(IGC_STATUS, toggle);
	after = rd32(IGC_STATUS) & toggle;
	अगर (value != after) अणु
		netdev_err(adapter->netdev,
			   "failed STATUS register test got: 0x%08X expected: 0x%08X",
			   after, value);
		*data = 1;
		वापस false;
	पूर्ण
	/* restore previous status */
	wr32(IGC_STATUS, beक्रमe);

	/* Perक्रमm the reमुख्यder of the रेजिस्टर test, looping through
	 * the test table until we either fail or reach the null entry.
	 */
	जबतक (test->reg) अणु
		क्रम (i = 0; i < test->array_len; i++) अणु
			चयन (test->test_type) अणु
			हाल PATTERN_TEST:
				b = reg_pattern_test(adapter, data,
						     test->reg + (i * 0x40),
						     test->mask,
						     test->ग_लिखो);
				अवरोध;
			हाल SET_READ_TEST:
				b = reg_set_and_check(adapter, data,
						      test->reg + (i * 0x40),
						      test->mask,
						      test->ग_लिखो);
				अवरोध;
			हाल TABLE64_TEST_LO:
				b = reg_pattern_test(adapter, data,
						     test->reg + (i * 8),
						     test->mask,
						     test->ग_लिखो);
				अवरोध;
			हाल TABLE64_TEST_HI:
				b = reg_pattern_test(adapter, data,
						     test->reg + 4 + (i * 8),
						     test->mask,
						     test->ग_लिखो);
				अवरोध;
			हाल TABLE32_TEST:
				b = reg_pattern_test(adapter, data,
						     test->reg + (i * 4),
						     test->mask,
						     test->ग_लिखो);
				अवरोध;
			पूर्ण
			अगर (!b)
				वापस false;
		पूर्ण
		test++;
	पूर्ण
	*data = 0;
	वापस true;
पूर्ण

bool igc_eeprom_test(काष्ठा igc_adapter *adapter, u64 *data)
अणु
	काष्ठा igc_hw *hw = &adapter->hw;

	*data = 0;

	अगर (hw->nvm.ops.validate(hw) != IGC_SUCCESS) अणु
		*data = 1;
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

bool igc_link_test(काष्ठा igc_adapter *adapter, u64 *data)
अणु
	bool link_up;

	*data = 0;

	/* add delay to give enough समय क्रम स्वतःnegotioation to finish */
	अगर (adapter->hw.mac.स्वतःneg)
		ssleep(5);

	link_up = igc_has_link(adapter);
	अगर (!link_up) अणु
		*data = 1;
		वापस false;
	पूर्ण

	वापस true;
पूर्ण
