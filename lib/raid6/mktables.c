<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* -*- linux-c -*- ------------------------------------------------------- *
 *
 *   Copyright 2002-2007 H. Peter Anvin - All Rights Reserved
 *
 * ----------------------------------------------------------------------- */

/*
 * mktables.c
 *
 * Make RAID-6 tables.  This is a host user space program to be run at
 * compile समय.
 */

#समावेश <मानकपन.स>
#समावेश <माला.स>
#समावेश <पूर्णांकtypes.h>
#समावेश <मानककोष.स>
#समावेश <समय.स>

अटल uपूर्णांक8_t gfmul(uपूर्णांक8_t a, uपूर्णांक8_t b)
अणु
	uपूर्णांक8_t v = 0;

	जबतक (b) अणु
		अगर (b & 1)
			v ^= a;
		a = (a << 1) ^ (a & 0x80 ? 0x1d : 0);
		b >>= 1;
	पूर्ण

	वापस v;
पूर्ण

अटल uपूर्णांक8_t gfघात(uपूर्णांक8_t a, पूर्णांक b)
अणु
	uपूर्णांक8_t v = 1;

	b %= 255;
	अगर (b < 0)
		b += 255;

	जबतक (b) अणु
		अगर (b & 1)
			v = gfmul(v, a);
		a = gfmul(a, a);
		b >>= 1;
	पूर्ण

	वापस v;
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	पूर्णांक i, j, k;
	uपूर्णांक8_t v;
	uपूर्णांक8_t exptbl[256], invtbl[256];

	म_लिखो("#include <linux/export.h>\n");
	म_लिखो("#include <linux/raid/pq.h>\n");

	/* Compute multiplication table */
	म_लिखो("\nconst u8  __attribute__((aligned(256)))\n"
		"raid6_gfmul[256][256] =\n"
		"{\n");
	क्रम (i = 0; i < 256; i++) अणु
		म_लिखो("\t{\n");
		क्रम (j = 0; j < 256; j += 8) अणु
			म_लिखो("\t\t");
			क्रम (k = 0; k < 8; k++)
				म_लिखो("0x%02x,%c", gfmul(i, j + k),
				       (k == 7) ? '\n' : ' ');
		पूर्ण
		म_लिखो("\t},\n");
	पूर्ण
	म_लिखो("};\n");
	म_लिखो("#ifdef __KERNEL__\n");
	म_लिखो("EXPORT_SYMBOL(raid6_gfmul);\n");
	म_लिखो("#endif\n");

	/* Compute vector multiplication table */
	म_लिखो("\nconst u8  __attribute__((aligned(256)))\n"
		"raid6_vgfmul[256][32] =\n"
		"{\n");
	क्रम (i = 0; i < 256; i++) अणु
		म_लिखो("\t{\n");
		क्रम (j = 0; j < 16; j += 8) अणु
			म_लिखो("\t\t");
			क्रम (k = 0; k < 8; k++)
				म_लिखो("0x%02x,%c", gfmul(i, j + k),
				       (k == 7) ? '\n' : ' ');
		पूर्ण
		क्रम (j = 0; j < 16; j += 8) अणु
			म_लिखो("\t\t");
			क्रम (k = 0; k < 8; k++)
				म_लिखो("0x%02x,%c", gfmul(i, (j + k) << 4),
				       (k == 7) ? '\n' : ' ');
		पूर्ण
		म_लिखो("\t},\n");
	पूर्ण
	म_लिखो("};\n");
	म_लिखो("#ifdef __KERNEL__\n");
	म_लिखो("EXPORT_SYMBOL(raid6_vgfmul);\n");
	म_लिखो("#endif\n");

	/* Compute घातer-of-2 table (exponent) */
	v = 1;
	म_लिखो("\nconst u8 __attribute__((aligned(256)))\n"
	       "raid6_gfexp[256] =\n" "{\n");
	क्रम (i = 0; i < 256; i += 8) अणु
		म_लिखो("\t");
		क्रम (j = 0; j < 8; j++) अणु
			exptbl[i + j] = v;
			म_लिखो("0x%02x,%c", v, (j == 7) ? '\n' : ' ');
			v = gfmul(v, 2);
			अगर (v == 1)
				v = 0;	/* For entry 255, not a real entry */
		पूर्ण
	पूर्ण
	म_लिखो("};\n");
	म_लिखो("#ifdef __KERNEL__\n");
	म_लिखो("EXPORT_SYMBOL(raid6_gfexp);\n");
	म_लिखो("#endif\n");

	/* Compute log-of-2 table */
	म_लिखो("\nconst u8 __attribute__((aligned(256)))\n"
	       "raid6_gflog[256] =\n" "{\n");
	क्रम (i = 0; i < 256; i += 8) अणु
		म_लिखो("\t");
		क्रम (j = 0; j < 8; j++) अणु
			v = 255;
			क्रम (k = 0; k < 256; k++)
				अगर (exptbl[k] == (i + j)) अणु
					v = k;
					अवरोध;
				पूर्ण
			म_लिखो("0x%02x,%c", v, (j == 7) ? '\n' : ' ');
		पूर्ण
	पूर्ण
	म_लिखो("};\n");
	म_लिखो("#ifdef __KERNEL__\n");
	म_लिखो("EXPORT_SYMBOL(raid6_gflog);\n");
	म_लिखो("#endif\n");

	/* Compute inverse table x^-1 == x^254 */
	म_लिखो("\nconst u8 __attribute__((aligned(256)))\n"
	       "raid6_gfinv[256] =\n" "{\n");
	क्रम (i = 0; i < 256; i += 8) अणु
		म_लिखो("\t");
		क्रम (j = 0; j < 8; j++) अणु
			invtbl[i + j] = v = gfघात(i + j, 254);
			म_लिखो("0x%02x,%c", v, (j == 7) ? '\n' : ' ');
		पूर्ण
	पूर्ण
	म_लिखो("};\n");
	म_लिखो("#ifdef __KERNEL__\n");
	म_लिखो("EXPORT_SYMBOL(raid6_gfinv);\n");
	म_लिखो("#endif\n");

	/* Compute inv(2^x + 1) (exponent-xor-inverse) table */
	म_लिखो("\nconst u8 __attribute__((aligned(256)))\n"
	       "raid6_gfexi[256] =\n" "{\n");
	क्रम (i = 0; i < 256; i += 8) अणु
		म_लिखो("\t");
		क्रम (j = 0; j < 8; j++)
			म_लिखो("0x%02x,%c", invtbl[exptbl[i + j] ^ 1],
			       (j == 7) ? '\n' : ' ');
	पूर्ण
	म_लिखो("};\n");
	म_लिखो("#ifdef __KERNEL__\n");
	म_लिखो("EXPORT_SYMBOL(raid6_gfexi);\n");
	म_लिखो("#endif\n");

	वापस 0;
पूर्ण
