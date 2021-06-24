<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (c)  2020 Intel Corporation */

bool igc_reg_test(काष्ठा igc_adapter *adapter, u64 *data);
bool igc_eeprom_test(काष्ठा igc_adapter *adapter, u64 *data);
bool igc_link_test(काष्ठा igc_adapter *adapter, u64 *data);

काष्ठा igc_reg_test अणु
	u16 reg;
	u8 array_len;
	u8 test_type;
	u32 mask;
	u32 ग_लिखो;
पूर्ण;

/* In the hardware, रेजिस्टरs are laid out either singly, in arrays
 * spaced 0x40 bytes apart, or in contiguous tables.  We assume
 * most tests take place on arrays or single रेजिस्टरs (handled
 * as a single-element array) and special-हाल the tables.
 * Table tests are always pattern tests.
 *
 * We also make provision क्रम some required setup steps by specअगरying
 * रेजिस्टरs to be written without any पढ़ो-back testing.
 */

#घोषणा PATTERN_TEST	1
#घोषणा SET_READ_TEST	2
#घोषणा TABLE32_TEST	3
#घोषणा TABLE64_TEST_LO	4
#घोषणा TABLE64_TEST_HI	5
