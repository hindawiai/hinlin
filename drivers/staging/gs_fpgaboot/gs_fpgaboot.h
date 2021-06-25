<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */

#समावेश <linux/firmware.h>

#घोषणा	MAX_STR	256

क्रमागत fmt_image अणु
	f_bit,	/* only bitstream is supported */
	f_rbt,
	f_bin,
	f_mcs,
	f_hex,
पूर्ण;

क्रमागत mकरोwnload अणु
	m_प्रणालीmap,	/* only प्रणाली map is supported */
	m_serial,
	m_jtag,
पूर्ण;

/*
 * xilinx fpgaimage inक्रमmation
 * NOTE: use MAX_STR instead of dynamic alloc क्रम simplicity
 */
काष्ठा fpgaimage अणु
	क्रमागत fmt_image	fmt_img;
	क्रमागत mकरोwnload	dmethod;

	स्थिर काष्ठा	firmware	*fw_entry;

	/*
	 * the following can be पढ़ो from bitstream,
	 * but other image क्रमmat should have as well
	 */
	अक्षर	filename[MAX_STR];
	अक्षर	part[MAX_STR];
	अक्षर	date[MAX_STR];
	अक्षर	समय[MAX_STR];
	पूर्णांक	lendata;
	u8	*fpgadata;
पूर्ण;
