<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Generate lookup table क्रम the table-driven CRC64 calculation.
 *
 * gen_crc64table is executed in kernel build समय and generates
 * lib/crc64table.h. This header is included by lib/crc64.c क्रम
 * the table-driven CRC64 calculation.
 *
 * See lib/crc64.c क्रम more inक्रमmation about which specअगरication
 * and polynomial arithmetic that gen_crc64table.c follows to
 * generate the lookup table.
 *
 * Copyright 2018 SUSE Linux.
 *   Author: Coly Li <colyli@suse.de>
 */
#समावेश <पूर्णांकtypes.h>
#समावेश <मानकपन.स>

#घोषणा CRC64_ECMA182_POLY 0x42F0E1EBA9EA3693ULL

अटल uपूर्णांक64_t crc64_table[256] = अणु0पूर्ण;

अटल व्योम generate_crc64_table(व्योम)
अणु
	uपूर्णांक64_t i, j, c, crc;

	क्रम (i = 0; i < 256; i++) अणु
		crc = 0;
		c = i << 56;

		क्रम (j = 0; j < 8; j++) अणु
			अगर ((crc ^ c) & 0x8000000000000000ULL)
				crc = (crc << 1) ^ CRC64_ECMA182_POLY;
			अन्यथा
				crc <<= 1;
			c <<= 1;
		पूर्ण

		crc64_table[i] = crc;
	पूर्ण
पूर्ण

अटल व्योम prपूर्णांक_crc64_table(व्योम)
अणु
	पूर्णांक i;

	म_लिखो("/* this file is generated - do not edit */\n\n");
	म_लिखो("#include <linux/types.h>\n");
	म_लिखो("#include <linux/cache.h>\n\n");
	म_लिखो("static const u64 ____cacheline_aligned crc64table[256] = {\n");
	क्रम (i = 0; i < 256; i++) अणु
		म_लिखो("\t0x%016" PRIx64 "ULL", crc64_table[i]);
		अगर (i & 0x1)
			म_लिखो(",\n");
		अन्यथा
			म_लिखो(", ");
	पूर्ण
	म_लिखो("};\n");
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	generate_crc64_table();
	prपूर्णांक_crc64_table();
	वापस 0;
पूर्ण
