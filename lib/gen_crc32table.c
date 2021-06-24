<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <मानकपन.स>
#समावेश "../include/linux/crc32poly.h"
#समावेश "../include/generated/autoconf.h"
#समावेश "crc32defs.h"
#समावेश <पूर्णांकtypes.h>

#घोषणा ENTRIES_PER_LINE 4

#अगर CRC_LE_BITS > 8
# define LE_TABLE_ROWS (CRC_LE_BITS/8)
# define LE_TABLE_SIZE 256
#अन्यथा
# define LE_TABLE_ROWS 1
# define LE_TABLE_SIZE (1 << CRC_LE_BITS)
#पूर्ण_अगर

#अगर CRC_BE_BITS > 8
# define BE_TABLE_ROWS (CRC_BE_BITS/8)
# define BE_TABLE_SIZE 256
#अन्यथा
# define BE_TABLE_ROWS 1
# define BE_TABLE_SIZE (1 << CRC_BE_BITS)
#पूर्ण_अगर

अटल uपूर्णांक32_t crc32table_le[LE_TABLE_ROWS][256];
अटल uपूर्णांक32_t crc32table_be[BE_TABLE_ROWS][256];
अटल uपूर्णांक32_t crc32ctable_le[LE_TABLE_ROWS][256];

/**
 * crc32init_le() - allocate and initialize LE table data
 *
 * crc is the crc of the byte i; other entries are filled in based on the
 * fact that crctable[i^j] = crctable[i] ^ crctable[j].
 *
 */
अटल व्योम crc32init_le_generic(स्थिर uपूर्णांक32_t polynomial,
				 uपूर्णांक32_t (*tab)[256])
अणु
	अचिन्हित i, j;
	uपूर्णांक32_t crc = 1;

	tab[0][0] = 0;

	क्रम (i = LE_TABLE_SIZE >> 1; i; i >>= 1) अणु
		crc = (crc >> 1) ^ ((crc & 1) ? polynomial : 0);
		क्रम (j = 0; j < LE_TABLE_SIZE; j += 2 * i)
			tab[0][i + j] = crc ^ tab[0][j];
	पूर्ण
	क्रम (i = 0; i < LE_TABLE_SIZE; i++) अणु
		crc = tab[0][i];
		क्रम (j = 1; j < LE_TABLE_ROWS; j++) अणु
			crc = tab[0][crc & 0xff] ^ (crc >> 8);
			tab[j][i] = crc;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम crc32init_le(व्योम)
अणु
	crc32init_le_generic(CRC32_POLY_LE, crc32table_le);
पूर्ण

अटल व्योम crc32cinit_le(व्योम)
अणु
	crc32init_le_generic(CRC32C_POLY_LE, crc32ctable_le);
पूर्ण

/**
 * crc32init_be() - allocate and initialize BE table data
 */
अटल व्योम crc32init_be(व्योम)
अणु
	अचिन्हित i, j;
	uपूर्णांक32_t crc = 0x80000000;

	crc32table_be[0][0] = 0;

	क्रम (i = 1; i < BE_TABLE_SIZE; i <<= 1) अणु
		crc = (crc << 1) ^ ((crc & 0x80000000) ? CRC32_POLY_BE : 0);
		क्रम (j = 0; j < i; j++)
			crc32table_be[0][i + j] = crc ^ crc32table_be[0][j];
	पूर्ण
	क्रम (i = 0; i < BE_TABLE_SIZE; i++) अणु
		crc = crc32table_be[0][i];
		क्रम (j = 1; j < BE_TABLE_ROWS; j++) अणु
			crc = crc32table_be[0][(crc >> 24) & 0xff] ^ (crc << 8);
			crc32table_be[j][i] = crc;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम output_table(uपूर्णांक32_t (*table)[256], पूर्णांक rows, पूर्णांक len, अक्षर *trans)
अणु
	पूर्णांक i, j;

	क्रम (j = 0 ; j < rows; j++) अणु
		म_लिखो("{");
		क्रम (i = 0; i < len - 1; i++) अणु
			अगर (i % ENTRIES_PER_LINE == 0)
				म_लिखो("\n");
			म_लिखो("%s(0x%8.8xL), ", trans, table[j][i]);
		पूर्ण
		म_लिखो("%s(0x%8.8xL)},\n", trans, table[j][len - 1]);
	पूर्ण
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर** argv)
अणु
	म_लिखो("/* this file is generated - do not edit */\n\n");

	अगर (CRC_LE_BITS > 1) अणु
		crc32init_le();
		म_लिखो("static const u32 ____cacheline_aligned "
		       "crc32table_le[%d][%d] = {",
		       LE_TABLE_ROWS, LE_TABLE_SIZE);
		output_table(crc32table_le, LE_TABLE_ROWS,
			     LE_TABLE_SIZE, "tole");
		म_लिखो("};\n");
	पूर्ण

	अगर (CRC_BE_BITS > 1) अणु
		crc32init_be();
		म_लिखो("static const u32 ____cacheline_aligned "
		       "crc32table_be[%d][%d] = {",
		       BE_TABLE_ROWS, BE_TABLE_SIZE);
		output_table(crc32table_be, LE_TABLE_ROWS,
			     BE_TABLE_SIZE, "tobe");
		म_लिखो("};\n");
	पूर्ण
	अगर (CRC_LE_BITS > 1) अणु
		crc32cinit_le();
		म_लिखो("static const u32 ____cacheline_aligned "
		       "crc32ctable_le[%d][%d] = {",
		       LE_TABLE_ROWS, LE_TABLE_SIZE);
		output_table(crc32ctable_le, LE_TABLE_ROWS,
			     LE_TABLE_SIZE, "tole");
		म_लिखो("};\n");
	पूर्ण

	वापस 0;
पूर्ण
