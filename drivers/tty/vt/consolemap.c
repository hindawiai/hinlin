<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * consolemap.c
 *
 * Mapping from पूर्णांकernal code (such as Latin-1 or Unicode or IBM PC code)
 * to font positions.
 *
 * aeb, 950210
 *
 * Support क्रम multiple unimaps by Jakub Jelinek <jj@ultra.linux.cz>, July 1998
 *
 * Fix bug in inverse translation. Stanislav Voronyi <stas@cnti.uanet.kharkov.ua>, Dec 1998
 *
 * In order to prevent the following circular lock dependency:
 *   &mm->mmap_lock --> cpu_hotplug.lock --> console_lock --> &mm->mmap_lock
 *
 * We cannot allow page fault to happen जबतक holding the console_lock.
 * Thereक्रमe, all the userspace copy operations have to be करोne outside
 * the console_lock critical sections.
 *
 * As all the affected functions are all called directly from vt_ioctl(), we
 * can allocate some small buffers directly on stack without worrying about
 * stack overflow.
 */

#समावेश <linux/module.h>
#समावेश <linux/kd.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/mm.h>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/tty.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/console.h>
#समावेश <linux/consolemap.h>
#समावेश <linux/vt_kern.h>
#समावेश <linux/माला.स>

अटल अचिन्हित लघु translations[][256] = अणु
  /* 8-bit Latin-1 mapped to Unicode -- trivial mapping */
  अणु
    0x0000, 0x0001, 0x0002, 0x0003, 0x0004, 0x0005, 0x0006, 0x0007,
    0x0008, 0x0009, 0x000a, 0x000b, 0x000c, 0x000d, 0x000e, 0x000f,
    0x0010, 0x0011, 0x0012, 0x0013, 0x0014, 0x0015, 0x0016, 0x0017,
    0x0018, 0x0019, 0x001a, 0x001b, 0x001c, 0x001d, 0x001e, 0x001f,
    0x0020, 0x0021, 0x0022, 0x0023, 0x0024, 0x0025, 0x0026, 0x0027,
    0x0028, 0x0029, 0x002a, 0x002b, 0x002c, 0x002d, 0x002e, 0x002f,
    0x0030, 0x0031, 0x0032, 0x0033, 0x0034, 0x0035, 0x0036, 0x0037,
    0x0038, 0x0039, 0x003a, 0x003b, 0x003c, 0x003d, 0x003e, 0x003f,
    0x0040, 0x0041, 0x0042, 0x0043, 0x0044, 0x0045, 0x0046, 0x0047,
    0x0048, 0x0049, 0x004a, 0x004b, 0x004c, 0x004d, 0x004e, 0x004f,
    0x0050, 0x0051, 0x0052, 0x0053, 0x0054, 0x0055, 0x0056, 0x0057,
    0x0058, 0x0059, 0x005a, 0x005b, 0x005c, 0x005d, 0x005e, 0x005f,
    0x0060, 0x0061, 0x0062, 0x0063, 0x0064, 0x0065, 0x0066, 0x0067,
    0x0068, 0x0069, 0x006a, 0x006b, 0x006c, 0x006d, 0x006e, 0x006f,
    0x0070, 0x0071, 0x0072, 0x0073, 0x0074, 0x0075, 0x0076, 0x0077,
    0x0078, 0x0079, 0x007a, 0x007b, 0x007c, 0x007d, 0x007e, 0x007f,
    0x0080, 0x0081, 0x0082, 0x0083, 0x0084, 0x0085, 0x0086, 0x0087,
    0x0088, 0x0089, 0x008a, 0x008b, 0x008c, 0x008d, 0x008e, 0x008f,
    0x0090, 0x0091, 0x0092, 0x0093, 0x0094, 0x0095, 0x0096, 0x0097,
    0x0098, 0x0099, 0x009a, 0x009b, 0x009c, 0x009d, 0x009e, 0x009f,
    0x00a0, 0x00a1, 0x00a2, 0x00a3, 0x00a4, 0x00a5, 0x00a6, 0x00a7,
    0x00a8, 0x00a9, 0x00aa, 0x00ab, 0x00ac, 0x00ad, 0x00ae, 0x00af,
    0x00b0, 0x00b1, 0x00b2, 0x00b3, 0x00b4, 0x00b5, 0x00b6, 0x00b7,
    0x00b8, 0x00b9, 0x00ba, 0x00bb, 0x00bc, 0x00bd, 0x00be, 0x00bf,
    0x00c0, 0x00c1, 0x00c2, 0x00c3, 0x00c4, 0x00c5, 0x00c6, 0x00c7,
    0x00c8, 0x00c9, 0x00ca, 0x00cb, 0x00cc, 0x00cd, 0x00ce, 0x00cf,
    0x00d0, 0x00d1, 0x00d2, 0x00d3, 0x00d4, 0x00d5, 0x00d6, 0x00d7,
    0x00d8, 0x00d9, 0x00da, 0x00db, 0x00dc, 0x00dd, 0x00de, 0x00df,
    0x00e0, 0x00e1, 0x00e2, 0x00e3, 0x00e4, 0x00e5, 0x00e6, 0x00e7,
    0x00e8, 0x00e9, 0x00ea, 0x00eb, 0x00ec, 0x00ed, 0x00ee, 0x00ef,
    0x00f0, 0x00f1, 0x00f2, 0x00f3, 0x00f4, 0x00f5, 0x00f6, 0x00f7,
    0x00f8, 0x00f9, 0x00fa, 0x00fb, 0x00fc, 0x00fd, 0x00fe, 0x00ff
  पूर्ण, 
  /* VT100 graphics mapped to Unicode */
  अणु
    0x0000, 0x0001, 0x0002, 0x0003, 0x0004, 0x0005, 0x0006, 0x0007,
    0x0008, 0x0009, 0x000a, 0x000b, 0x000c, 0x000d, 0x000e, 0x000f,
    0x0010, 0x0011, 0x0012, 0x0013, 0x0014, 0x0015, 0x0016, 0x0017,
    0x0018, 0x0019, 0x001a, 0x001b, 0x001c, 0x001d, 0x001e, 0x001f,
    0x0020, 0x0021, 0x0022, 0x0023, 0x0024, 0x0025, 0x0026, 0x0027,
    0x0028, 0x0029, 0x002a, 0x2192, 0x2190, 0x2191, 0x2193, 0x002f,
    0x2588, 0x0031, 0x0032, 0x0033, 0x0034, 0x0035, 0x0036, 0x0037,
    0x0038, 0x0039, 0x003a, 0x003b, 0x003c, 0x003d, 0x003e, 0x003f,
    0x0040, 0x0041, 0x0042, 0x0043, 0x0044, 0x0045, 0x0046, 0x0047,
    0x0048, 0x0049, 0x004a, 0x004b, 0x004c, 0x004d, 0x004e, 0x004f,
    0x0050, 0x0051, 0x0052, 0x0053, 0x0054, 0x0055, 0x0056, 0x0057,
    0x0058, 0x0059, 0x005a, 0x005b, 0x005c, 0x005d, 0x005e, 0x00a0,
    0x25c6, 0x2592, 0x2409, 0x240c, 0x240d, 0x240a, 0x00b0, 0x00b1,
    0x2591, 0x240b, 0x2518, 0x2510, 0x250c, 0x2514, 0x253c, 0x23ba,
    0x23bb, 0x2500, 0x23bc, 0x23bd, 0x251c, 0x2524, 0x2534, 0x252c,
    0x2502, 0x2264, 0x2265, 0x03c0, 0x2260, 0x00a3, 0x00b7, 0x007f,
    0x0080, 0x0081, 0x0082, 0x0083, 0x0084, 0x0085, 0x0086, 0x0087,
    0x0088, 0x0089, 0x008a, 0x008b, 0x008c, 0x008d, 0x008e, 0x008f,
    0x0090, 0x0091, 0x0092, 0x0093, 0x0094, 0x0095, 0x0096, 0x0097,
    0x0098, 0x0099, 0x009a, 0x009b, 0x009c, 0x009d, 0x009e, 0x009f,
    0x00a0, 0x00a1, 0x00a2, 0x00a3, 0x00a4, 0x00a5, 0x00a6, 0x00a7,
    0x00a8, 0x00a9, 0x00aa, 0x00ab, 0x00ac, 0x00ad, 0x00ae, 0x00af,
    0x00b0, 0x00b1, 0x00b2, 0x00b3, 0x00b4, 0x00b5, 0x00b6, 0x00b7,
    0x00b8, 0x00b9, 0x00ba, 0x00bb, 0x00bc, 0x00bd, 0x00be, 0x00bf,
    0x00c0, 0x00c1, 0x00c2, 0x00c3, 0x00c4, 0x00c5, 0x00c6, 0x00c7,
    0x00c8, 0x00c9, 0x00ca, 0x00cb, 0x00cc, 0x00cd, 0x00ce, 0x00cf,
    0x00d0, 0x00d1, 0x00d2, 0x00d3, 0x00d4, 0x00d5, 0x00d6, 0x00d7,
    0x00d8, 0x00d9, 0x00da, 0x00db, 0x00dc, 0x00dd, 0x00de, 0x00df,
    0x00e0, 0x00e1, 0x00e2, 0x00e3, 0x00e4, 0x00e5, 0x00e6, 0x00e7,
    0x00e8, 0x00e9, 0x00ea, 0x00eb, 0x00ec, 0x00ed, 0x00ee, 0x00ef,
    0x00f0, 0x00f1, 0x00f2, 0x00f3, 0x00f4, 0x00f5, 0x00f6, 0x00f7,
    0x00f8, 0x00f9, 0x00fa, 0x00fb, 0x00fc, 0x00fd, 0x00fe, 0x00ff
  पूर्ण,
  /* IBM Codepage 437 mapped to Unicode */
  अणु
    0x0000, 0x263a, 0x263b, 0x2665, 0x2666, 0x2663, 0x2660, 0x2022, 
    0x25d8, 0x25cb, 0x25d9, 0x2642, 0x2640, 0x266a, 0x266b, 0x263c,
    0x25b6, 0x25c0, 0x2195, 0x203c, 0x00b6, 0x00a7, 0x25ac, 0x21a8,
    0x2191, 0x2193, 0x2192, 0x2190, 0x221f, 0x2194, 0x25b2, 0x25bc,
    0x0020, 0x0021, 0x0022, 0x0023, 0x0024, 0x0025, 0x0026, 0x0027,
    0x0028, 0x0029, 0x002a, 0x002b, 0x002c, 0x002d, 0x002e, 0x002f,
    0x0030, 0x0031, 0x0032, 0x0033, 0x0034, 0x0035, 0x0036, 0x0037,
    0x0038, 0x0039, 0x003a, 0x003b, 0x003c, 0x003d, 0x003e, 0x003f,
    0x0040, 0x0041, 0x0042, 0x0043, 0x0044, 0x0045, 0x0046, 0x0047,
    0x0048, 0x0049, 0x004a, 0x004b, 0x004c, 0x004d, 0x004e, 0x004f,
    0x0050, 0x0051, 0x0052, 0x0053, 0x0054, 0x0055, 0x0056, 0x0057,
    0x0058, 0x0059, 0x005a, 0x005b, 0x005c, 0x005d, 0x005e, 0x005f,
    0x0060, 0x0061, 0x0062, 0x0063, 0x0064, 0x0065, 0x0066, 0x0067,
    0x0068, 0x0069, 0x006a, 0x006b, 0x006c, 0x006d, 0x006e, 0x006f,
    0x0070, 0x0071, 0x0072, 0x0073, 0x0074, 0x0075, 0x0076, 0x0077,
    0x0078, 0x0079, 0x007a, 0x007b, 0x007c, 0x007d, 0x007e, 0x2302,
    0x00c7, 0x00fc, 0x00e9, 0x00e2, 0x00e4, 0x00e0, 0x00e5, 0x00e7,
    0x00ea, 0x00eb, 0x00e8, 0x00ef, 0x00ee, 0x00ec, 0x00c4, 0x00c5,
    0x00c9, 0x00e6, 0x00c6, 0x00f4, 0x00f6, 0x00f2, 0x00fb, 0x00f9,
    0x00ff, 0x00d6, 0x00dc, 0x00a2, 0x00a3, 0x00a5, 0x20a7, 0x0192,
    0x00e1, 0x00ed, 0x00f3, 0x00fa, 0x00f1, 0x00d1, 0x00aa, 0x00ba,
    0x00bf, 0x2310, 0x00ac, 0x00bd, 0x00bc, 0x00a1, 0x00ab, 0x00bb,
    0x2591, 0x2592, 0x2593, 0x2502, 0x2524, 0x2561, 0x2562, 0x2556,
    0x2555, 0x2563, 0x2551, 0x2557, 0x255d, 0x255c, 0x255b, 0x2510,
    0x2514, 0x2534, 0x252c, 0x251c, 0x2500, 0x253c, 0x255e, 0x255f,
    0x255a, 0x2554, 0x2569, 0x2566, 0x2560, 0x2550, 0x256c, 0x2567,
    0x2568, 0x2564, 0x2565, 0x2559, 0x2558, 0x2552, 0x2553, 0x256b,
    0x256a, 0x2518, 0x250c, 0x2588, 0x2584, 0x258c, 0x2590, 0x2580,
    0x03b1, 0x00df, 0x0393, 0x03c0, 0x03a3, 0x03c3, 0x00b5, 0x03c4,
    0x03a6, 0x0398, 0x03a9, 0x03b4, 0x221e, 0x03c6, 0x03b5, 0x2229,
    0x2261, 0x00b1, 0x2265, 0x2264, 0x2320, 0x2321, 0x00f7, 0x2248,
    0x00b0, 0x2219, 0x00b7, 0x221a, 0x207f, 0x00b2, 0x25a0, 0x00a0
  पूर्ण, 
  /* User mapping -- शेष to codes क्रम direct font mapping */
  अणु
    0xf000, 0xf001, 0xf002, 0xf003, 0xf004, 0xf005, 0xf006, 0xf007,
    0xf008, 0xf009, 0xf00a, 0xf00b, 0xf00c, 0xf00d, 0xf00e, 0xf00f,
    0xf010, 0xf011, 0xf012, 0xf013, 0xf014, 0xf015, 0xf016, 0xf017,
    0xf018, 0xf019, 0xf01a, 0xf01b, 0xf01c, 0xf01d, 0xf01e, 0xf01f,
    0xf020, 0xf021, 0xf022, 0xf023, 0xf024, 0xf025, 0xf026, 0xf027,
    0xf028, 0xf029, 0xf02a, 0xf02b, 0xf02c, 0xf02d, 0xf02e, 0xf02f,
    0xf030, 0xf031, 0xf032, 0xf033, 0xf034, 0xf035, 0xf036, 0xf037,
    0xf038, 0xf039, 0xf03a, 0xf03b, 0xf03c, 0xf03d, 0xf03e, 0xf03f,
    0xf040, 0xf041, 0xf042, 0xf043, 0xf044, 0xf045, 0xf046, 0xf047,
    0xf048, 0xf049, 0xf04a, 0xf04b, 0xf04c, 0xf04d, 0xf04e, 0xf04f,
    0xf050, 0xf051, 0xf052, 0xf053, 0xf054, 0xf055, 0xf056, 0xf057,
    0xf058, 0xf059, 0xf05a, 0xf05b, 0xf05c, 0xf05d, 0xf05e, 0xf05f,
    0xf060, 0xf061, 0xf062, 0xf063, 0xf064, 0xf065, 0xf066, 0xf067,
    0xf068, 0xf069, 0xf06a, 0xf06b, 0xf06c, 0xf06d, 0xf06e, 0xf06f,
    0xf070, 0xf071, 0xf072, 0xf073, 0xf074, 0xf075, 0xf076, 0xf077,
    0xf078, 0xf079, 0xf07a, 0xf07b, 0xf07c, 0xf07d, 0xf07e, 0xf07f,
    0xf080, 0xf081, 0xf082, 0xf083, 0xf084, 0xf085, 0xf086, 0xf087,
    0xf088, 0xf089, 0xf08a, 0xf08b, 0xf08c, 0xf08d, 0xf08e, 0xf08f,
    0xf090, 0xf091, 0xf092, 0xf093, 0xf094, 0xf095, 0xf096, 0xf097,
    0xf098, 0xf099, 0xf09a, 0xf09b, 0xf09c, 0xf09d, 0xf09e, 0xf09f,
    0xf0a0, 0xf0a1, 0xf0a2, 0xf0a3, 0xf0a4, 0xf0a5, 0xf0a6, 0xf0a7,
    0xf0a8, 0xf0a9, 0xf0aa, 0xf0ab, 0xf0ac, 0xf0ad, 0xf0ae, 0xf0af,
    0xf0b0, 0xf0b1, 0xf0b2, 0xf0b3, 0xf0b4, 0xf0b5, 0xf0b6, 0xf0b7,
    0xf0b8, 0xf0b9, 0xf0ba, 0xf0bb, 0xf0bc, 0xf0bd, 0xf0be, 0xf0bf,
    0xf0c0, 0xf0c1, 0xf0c2, 0xf0c3, 0xf0c4, 0xf0c5, 0xf0c6, 0xf0c7,
    0xf0c8, 0xf0c9, 0xf0ca, 0xf0cb, 0xf0cc, 0xf0cd, 0xf0ce, 0xf0cf,
    0xf0d0, 0xf0d1, 0xf0d2, 0xf0d3, 0xf0d4, 0xf0d5, 0xf0d6, 0xf0d7,
    0xf0d8, 0xf0d9, 0xf0da, 0xf0db, 0xf0dc, 0xf0dd, 0xf0de, 0xf0df,
    0xf0e0, 0xf0e1, 0xf0e2, 0xf0e3, 0xf0e4, 0xf0e5, 0xf0e6, 0xf0e7,
    0xf0e8, 0xf0e9, 0xf0ea, 0xf0eb, 0xf0ec, 0xf0ed, 0xf0ee, 0xf0ef,
    0xf0f0, 0xf0f1, 0xf0f2, 0xf0f3, 0xf0f4, 0xf0f5, 0xf0f6, 0xf0f7,
    0xf0f8, 0xf0f9, 0xf0fa, 0xf0fb, 0xf0fc, 0xf0fd, 0xf0fe, 0xf0ff
  पूर्ण
पूर्ण;

/* The standard kernel अक्षरacter-to-font mappings are not invertible
   -- this is just a best efक्रमt. */

#घोषणा MAX_GLYPH 512		/* Max possible glyph value */

अटल पूर्णांक inv_translate[MAX_NR_CONSOLES];

काष्ठा uni_pagedir अणु
	u16 		**uni_pgdir[32];
	अचिन्हित दीर्घ	refcount;
	अचिन्हित दीर्घ	sum;
	अचिन्हित अक्षर	*inverse_translations[4];
	u16		*inverse_trans_unicode;
पूर्ण;

अटल काष्ठा uni_pagedir *dflt;

अटल व्योम set_inverse_transl(काष्ठा vc_data *conp, काष्ठा uni_pagedir *p, पूर्णांक i)
अणु
	पूर्णांक j, glyph;
	अचिन्हित लघु *t = translations[i];
	अचिन्हित अक्षर *q;
	
	अगर (!p) वापस;
	q = p->inverse_translations[i];

	अगर (!q) अणु
		q = p->inverse_translations[i] = kदो_स्मृति(MAX_GLYPH, GFP_KERNEL);
		अगर (!q) वापस;
	पूर्ण
	स_रखो(q, 0, MAX_GLYPH);

	क्रम (j = 0; j < E_TABSZ; j++) अणु
		glyph = conv_uni_to_pc(conp, t[j]);
		अगर (glyph >= 0 && glyph < MAX_GLYPH && q[glyph] < 32) अणु
			/* prefer '-' above SHY etc. */
		  	q[glyph] = j;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम set_inverse_trans_unicode(काष्ठा vc_data *conp,
				      काष्ठा uni_pagedir *p)
अणु
	पूर्णांक i, j, k, glyph;
	u16 **p1, *p2;
	u16 *q;

	अगर (!p) वापस;
	q = p->inverse_trans_unicode;
	अगर (!q) अणु
		q = p->inverse_trans_unicode =
			kदो_स्मृति_array(MAX_GLYPH, माप(u16), GFP_KERNEL);
		अगर (!q)
			वापस;
	पूर्ण
	स_रखो(q, 0, MAX_GLYPH * माप(u16));

	क्रम (i = 0; i < 32; i++) अणु
		p1 = p->uni_pgdir[i];
		अगर (!p1)
			जारी;
		क्रम (j = 0; j < 32; j++) अणु
			p2 = p1[j];
			अगर (!p2)
				जारी;
			क्रम (k = 0; k < 64; k++) अणु
				glyph = p2[k];
				अगर (glyph >= 0 && glyph < MAX_GLYPH
					       && q[glyph] < 32)
		  			q[glyph] = (i << 11) + (j << 6) + k;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अचिन्हित लघु *set_translate(पूर्णांक m, काष्ठा vc_data *vc)
अणु
	inv_translate[vc->vc_num] = m;
	वापस translations[m];
पूर्ण

/*
 * Inverse translation is impossible क्रम several reasons:
 * 1. The font<->अक्षरacter maps are not 1-1.
 * 2. The text may have been written जबतक a dअगरferent translation map
 *    was active.
 * Still, it is now possible to a certain extent to cut and paste non-ASCII.
 */
u16 inverse_translate(स्थिर काष्ठा vc_data *conp, पूर्णांक glyph, पूर्णांक use_unicode)
अणु
	काष्ठा uni_pagedir *p;
	पूर्णांक m;
	अगर (glyph < 0 || glyph >= MAX_GLYPH)
		वापस 0;
	अन्यथा अणु
		p = *conp->vc_uni_pagedir_loc;
		अगर (!p)
			वापस glyph;
		अन्यथा अगर (use_unicode) अणु
			अगर (!p->inverse_trans_unicode)
				वापस glyph;
			अन्यथा
				वापस p->inverse_trans_unicode[glyph];
			पूर्ण अन्यथा अणु
			m = inv_translate[conp->vc_num];
			अगर (!p->inverse_translations[m])
				वापस glyph;
			अन्यथा
				वापस p->inverse_translations[m][glyph];
			पूर्ण
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(inverse_translate);

अटल व्योम update_user_maps(व्योम)
अणु
	पूर्णांक i;
	काष्ठा uni_pagedir *p, *q = शून्य;
	
	क्रम (i = 0; i < MAX_NR_CONSOLES; i++) अणु
		अगर (!vc_cons_allocated(i))
			जारी;
		p = *vc_cons[i].d->vc_uni_pagedir_loc;
		अगर (p && p != q) अणु
			set_inverse_transl(vc_cons[i].d, p, USER_MAP);
			set_inverse_trans_unicode(vc_cons[i].d, p);
			q = p;
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Load customizable translation table
 * arg poपूर्णांकs to a 256 byte translation table.
 *
 * The "old" variants are क्रम translation directly to font (using the
 * 0xf000-0xf0ff "transparent" Unicodes) whereas the "new" variants set
 * Unicodes explicitly.
 */
पूर्णांक con_set_trans_old(अचिन्हित अक्षर __user * arg)
अणु
	पूर्णांक i;
	अचिन्हित लघु inbuf[E_TABSZ];
	अचिन्हित अक्षर ubuf[E_TABSZ];

	अगर (copy_from_user(ubuf, arg, E_TABSZ))
		वापस -EFAULT;

	क्रम (i = 0; i < E_TABSZ ; i++)
		inbuf[i] = UNI_सूचीECT_BASE | ubuf[i];

	console_lock();
	स_नकल(translations[USER_MAP], inbuf, माप(inbuf));
	update_user_maps();
	console_unlock();
	वापस 0;
पूर्ण

पूर्णांक con_get_trans_old(अचिन्हित अक्षर __user * arg)
अणु
	पूर्णांक i, ch;
	अचिन्हित लघु *p = translations[USER_MAP];
	अचिन्हित अक्षर outbuf[E_TABSZ];

	console_lock();
	क्रम (i = 0; i < E_TABSZ ; i++)
	अणु
		ch = conv_uni_to_pc(vc_cons[fg_console].d, p[i]);
		outbuf[i] = (ch & ~0xff) ? 0 : ch;
	पूर्ण
	console_unlock();

	वापस copy_to_user(arg, outbuf, माप(outbuf)) ? -EFAULT : 0;
पूर्ण

पूर्णांक con_set_trans_new(uलघु __user * arg)
अणु
	अचिन्हित लघु inbuf[E_TABSZ];

	अगर (copy_from_user(inbuf, arg, माप(inbuf)))
		वापस -EFAULT;

	console_lock();
	स_नकल(translations[USER_MAP], inbuf, माप(inbuf));
	update_user_maps();
	console_unlock();
	वापस 0;
पूर्ण

पूर्णांक con_get_trans_new(uलघु __user * arg)
अणु
	अचिन्हित लघु outbuf[E_TABSZ];

	console_lock();
	स_नकल(outbuf, translations[USER_MAP], माप(outbuf));
	console_unlock();

	वापस copy_to_user(arg, outbuf, माप(outbuf)) ? -EFAULT : 0;
पूर्ण

/*
 * Unicode -> current font conversion 
 *
 * A font has at most 512 अक्षरs, usually 256.
 * But one font position may represent several Unicode अक्षरs.
 * A hashtable is somewhat of a pain to deal with, so use a
 * "paged table" instead.  Simulation has shown the memory cost of
 * this 3-level paged table scheme to be comparable to a hash table.
 */

बाह्य u8 dfont_unicount[];	/* Defined in console_defmap.c */
बाह्य u16 dfont_unitable[];

अटल व्योम con_release_unimap(काष्ठा uni_pagedir *p)
अणु
	u16 **p1;
	पूर्णांक i, j;

	अगर (p == dflt) dflt = शून्य;  
	क्रम (i = 0; i < 32; i++) अणु
		p1 = p->uni_pgdir[i];
		अगर (p1 != शून्य) अणु
			क्रम (j = 0; j < 32; j++)
				kमुक्त(p1[j]);
			kमुक्त(p1);
		पूर्ण
		p->uni_pgdir[i] = शून्य;
	पूर्ण
	क्रम (i = 0; i < 4; i++) अणु
		kमुक्त(p->inverse_translations[i]);
		p->inverse_translations[i] = शून्य;
	पूर्ण
	kमुक्त(p->inverse_trans_unicode);
	p->inverse_trans_unicode = शून्य;
पूर्ण

/* Caller must hold the console lock */
व्योम con_मुक्त_unimap(काष्ठा vc_data *vc)
अणु
	काष्ठा uni_pagedir *p;

	p = *vc->vc_uni_pagedir_loc;
	अगर (!p)
		वापस;
	*vc->vc_uni_pagedir_loc = शून्य;
	अगर (--p->refcount)
		वापस;
	con_release_unimap(p);
	kमुक्त(p);
पूर्ण
  
अटल पूर्णांक con_unअगरy_unimap(काष्ठा vc_data *conp, काष्ठा uni_pagedir *p)
अणु
	पूर्णांक i, j, k;
	काष्ठा uni_pagedir *q;
	
	क्रम (i = 0; i < MAX_NR_CONSOLES; i++) अणु
		अगर (!vc_cons_allocated(i))
			जारी;
		q = *vc_cons[i].d->vc_uni_pagedir_loc;
		अगर (!q || q == p || q->sum != p->sum)
			जारी;
		क्रम (j = 0; j < 32; j++) अणु
			u16 **p1, **q1;
			p1 = p->uni_pgdir[j]; q1 = q->uni_pgdir[j];
			अगर (!p1 && !q1)
				जारी;
			अगर (!p1 || !q1)
				अवरोध;
			क्रम (k = 0; k < 32; k++) अणु
				अगर (!p1[k] && !q1[k])
					जारी;
				अगर (!p1[k] || !q1[k])
					अवरोध;
				अगर (स_भेद(p1[k], q1[k], 64*माप(u16)))
					अवरोध;
			पूर्ण
			अगर (k < 32)
				अवरोध;
		पूर्ण
		अगर (j == 32) अणु
			q->refcount++;
			*conp->vc_uni_pagedir_loc = q;
			con_release_unimap(p);
			kमुक्त(p);
			वापस 1;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक
con_insert_unipair(काष्ठा uni_pagedir *p, u_लघु unicode, u_लघु fontpos)
अणु
	पूर्णांक i, n;
	u16 **p1, *p2;

	p1 = p->uni_pgdir[n = unicode >> 11];
	अगर (!p1) अणु
		p1 = p->uni_pgdir[n] = kदो_स्मृति_array(32, माप(u16 *),
						     GFP_KERNEL);
		अगर (!p1) वापस -ENOMEM;
		क्रम (i = 0; i < 32; i++)
			p1[i] = शून्य;
	पूर्ण

	p2 = p1[n = (unicode >> 6) & 0x1f];
	अगर (!p2) अणु
		p2 = p1[n] = kदो_स्मृति_array(64, माप(u16), GFP_KERNEL);
		अगर (!p2) वापस -ENOMEM;
		स_रखो(p2, 0xff, 64*माप(u16)); /* No glyphs क्रम the अक्षरacters (yet) */
	पूर्ण

	p2[unicode & 0x3f] = fontpos;
	
	p->sum += (fontpos << 20U) + unicode;

	वापस 0;
पूर्ण

/* Caller must hold the lock */
अटल पूर्णांक con_करो_clear_unimap(काष्ठा vc_data *vc)
अणु
	काष्ठा uni_pagedir *p, *q;

	p = *vc->vc_uni_pagedir_loc;
	अगर (!p || --p->refcount) अणु
		q = kzalloc(माप(*p), GFP_KERNEL);
		अगर (!q) अणु
			अगर (p)
				p->refcount++;
			वापस -ENOMEM;
		पूर्ण
		q->refcount=1;
		*vc->vc_uni_pagedir_loc = q;
	पूर्ण अन्यथा अणु
		अगर (p == dflt) dflt = शून्य;
		p->refcount++;
		p->sum = 0;
		con_release_unimap(p);
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक con_clear_unimap(काष्ठा vc_data *vc)
अणु
	पूर्णांक ret;
	console_lock();
	ret = con_करो_clear_unimap(vc);
	console_unlock();
	वापस ret;
पूर्ण
	
पूर्णांक con_set_unimap(काष्ठा vc_data *vc, uलघु ct, काष्ठा unipair __user *list)
अणु
	पूर्णांक err = 0, err1, i;
	काष्ठा uni_pagedir *p, *q;
	काष्ठा unipair *unilist, *plist;

	अगर (!ct)
		वापस 0;

	unilist = vmemdup_user(list, array_size(माप(काष्ठा unipair), ct));
	अगर (IS_ERR(unilist))
		वापस PTR_ERR(unilist);

	console_lock();

	/* Save original vc_unipagdir_loc in हाल we allocate a new one */
	p = *vc->vc_uni_pagedir_loc;

	अगर (!p) अणु
		err = -EINVAL;

		जाओ out_unlock;
	पूर्ण
	
	अगर (p->refcount > 1) अणु
		पूर्णांक j, k;
		u16 **p1, *p2, l;
		
		err1 = con_करो_clear_unimap(vc);
		अगर (err1) अणु
			err = err1;
			जाओ out_unlock;
		पूर्ण
		
		/*
		 * Since refcount was > 1, con_clear_unimap() allocated a
		 * a new uni_pagedir क्रम this vc.  Re: p != q
		 */
		q = *vc->vc_uni_pagedir_loc;

		/*
		 * uni_pgdir is a 32*32*64 table with rows allocated
		 * when its first entry is added.  The unicode value must
		 * still be incremented क्रम empty rows.  We are copying
		 * entries from "p" (old) to "q" (new).
		 */
		l = 0;		/* unicode value */
		क्रम (i = 0; i < 32; i++) अणु
		p1 = p->uni_pgdir[i];
		अगर (p1)
			क्रम (j = 0; j < 32; j++) अणु
			p2 = p1[j];
			अगर (p2) अणु
				क्रम (k = 0; k < 64; k++, l++)
				अगर (p2[k] != 0xffff) अणु
					/*
					 * Found one, copy entry क्रम unicode
					 * l with fontpos value p2[k].
					 */
					err1 = con_insert_unipair(q, l, p2[k]);
					अगर (err1) अणु
						p->refcount++;
						*vc->vc_uni_pagedir_loc = p;
						con_release_unimap(q);
						kमुक्त(q);
						err = err1;
						जाओ out_unlock;
					पूर्ण
				पूर्ण
			पूर्ण अन्यथा अणु
				/* Account क्रम row of 64 empty entries */
				l += 64;
			पूर्ण
		पूर्ण
		अन्यथा
			/* Account क्रम empty table */
			l += 32 * 64;
		पूर्ण

		/*
		 * Finished copying font table, set vc_uni_pagedir to new table
		 */
		p = q;
	पूर्ण अन्यथा अगर (p == dflt) अणु
		dflt = शून्य;
	पूर्ण

	/*
	 * Insert user specअगरied unicode pairs पूर्णांकo new table.
	 */
	क्रम (plist = unilist; ct; ct--, plist++) अणु
		err1 = con_insert_unipair(p, plist->unicode, plist->fontpos);
		अगर (err1)
			err = err1;
	पूर्ण
	
	/*
	 * Merge with fonपंचांगaps of any other भव consoles.
	 */
	अगर (con_unअगरy_unimap(vc, p))
		जाओ out_unlock;

	क्रम (i = 0; i <= 3; i++)
		set_inverse_transl(vc, p, i); /* Update inverse translations */
	set_inverse_trans_unicode(vc, p);

out_unlock:
	console_unlock();
	kvमुक्त(unilist);
	वापस err;
पूर्ण

/**
 *	con_set_शेष_unimap	-	set शेष unicode map
 *	@vc: the console we are updating
 *
 *	Loads the unimap क्रम the hardware font, as defined in uni_hash.tbl.
 *	The representation used was the most compact I could come up
 *	with.  This routine is executed at video setup, and when the
 *	PIO_FONTRESET ioctl is called. 
 *
 *	The caller must hold the console lock
 */
पूर्णांक con_set_शेष_unimap(काष्ठा vc_data *vc)
अणु
	पूर्णांक i, j, err = 0, err1;
	u16 *q;
	काष्ठा uni_pagedir *p;

	अगर (dflt) अणु
		p = *vc->vc_uni_pagedir_loc;
		अगर (p == dflt)
			वापस 0;

		dflt->refcount++;
		*vc->vc_uni_pagedir_loc = dflt;
		अगर (p && !--p->refcount) अणु
			con_release_unimap(p);
			kमुक्त(p);
		पूर्ण
		वापस 0;
	पूर्ण
	
	/* The शेष font is always 256 अक्षरacters */

	err = con_करो_clear_unimap(vc);
	अगर (err)
		वापस err;
    
	p = *vc->vc_uni_pagedir_loc;
	q = dfont_unitable;
	
	क्रम (i = 0; i < 256; i++)
		क्रम (j = dfont_unicount[i]; j; j--) अणु
			err1 = con_insert_unipair(p, *(q++), i);
			अगर (err1)
				err = err1;
		पूर्ण
			
	अगर (con_unअगरy_unimap(vc, p)) अणु
		dflt = *vc->vc_uni_pagedir_loc;
		वापस err;
	पूर्ण

	क्रम (i = 0; i <= 3; i++)
		set_inverse_transl(vc, p, i);	/* Update all inverse translations */
	set_inverse_trans_unicode(vc, p);
	dflt = p;
	वापस err;
पूर्ण
EXPORT_SYMBOL(con_set_शेष_unimap);

/**
 *	con_copy_unimap		-	copy unimap between two vts
 *	@dst_vc: target
 *	@src_vc: source
 *
 *	The caller must hold the console lock when invoking this method
 */
पूर्णांक con_copy_unimap(काष्ठा vc_data *dst_vc, काष्ठा vc_data *src_vc)
अणु
	काष्ठा uni_pagedir *q;

	अगर (!*src_vc->vc_uni_pagedir_loc)
		वापस -EINVAL;
	अगर (*dst_vc->vc_uni_pagedir_loc == *src_vc->vc_uni_pagedir_loc)
		वापस 0;
	con_मुक्त_unimap(dst_vc);
	q = *src_vc->vc_uni_pagedir_loc;
	q->refcount++;
	*dst_vc->vc_uni_pagedir_loc = q;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(con_copy_unimap);

/*
 *	con_get_unimap		-	get the unicode map
 *
 *	Read the console unicode data क्रम this console. Called from the ioctl
 *	handlers.
 */
पूर्णांक con_get_unimap(काष्ठा vc_data *vc, uलघु ct, uलघु __user *uct, काष्ठा unipair __user *list)
अणु
	पूर्णांक i, j, k, ret = 0;
	uलघु ect;
	u16 **p1, *p2;
	काष्ठा uni_pagedir *p;
	काष्ठा unipair *unilist;

	unilist = kvदो_स्मृति_array(ct, माप(काष्ठा unipair), GFP_KERNEL);
	अगर (!unilist)
		वापस -ENOMEM;

	console_lock();

	ect = 0;
	अगर (*vc->vc_uni_pagedir_loc) अणु
		p = *vc->vc_uni_pagedir_loc;
		क्रम (i = 0; i < 32; i++) अणु
		p1 = p->uni_pgdir[i];
		अगर (p1)
			क्रम (j = 0; j < 32; j++) अणु
			p2 = *(p1++);
			अगर (p2)
				क्रम (k = 0; k < 64; k++, p2++) अणु
					अगर (*p2 >= MAX_GLYPH)
						जारी;
					अगर (ect < ct) अणु
						unilist[ect].unicode =
							(i<<11)+(j<<6)+k;
						unilist[ect].fontpos = *p2;
					पूर्ण
					ect++;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
	console_unlock();
	अगर (copy_to_user(list, unilist, min(ect, ct) * माप(काष्ठा unipair)))
		ret = -EFAULT;
	put_user(ect, uct);
	kvमुक्त(unilist);
	वापस ret ? ret : (ect <= ct) ? 0 : -ENOMEM;
पूर्ण

/*
 * Always use USER_MAP. These functions are used by the keyboard,
 * which shouldn't be affected by G0/G1 चयनing, etc.
 * If the user map still contains शेष values, i.e. the
 * direct-to-font mapping, then assume user is using Latin1.
 *
 * FIXME: at some poपूर्णांक we need to decide अगर we want to lock the table
 * update element itself via the keyboard_event_lock क्रम consistency with the
 * keyboard driver as well as the consoles
 */
/* may be called during an पूर्णांकerrupt */
u32 conv_8bit_to_uni(अचिन्हित अक्षर c)
अणु
	अचिन्हित लघु uni = translations[USER_MAP][c];
	वापस uni == (0xf000 | c) ? c : uni;
पूर्ण

पूर्णांक conv_uni_to_8bit(u32 uni)
अणु
	पूर्णांक c;
	क्रम (c = 0; c < 0x100; c++)
		अगर (translations[USER_MAP][c] == uni ||
		   (translations[USER_MAP][c] == (c | 0xf000) && uni == c))
			वापस c;
	वापस -1;
पूर्ण

पूर्णांक
conv_uni_to_pc(काष्ठा vc_data *conp, दीर्घ ucs) 
अणु
	पूर्णांक h;
	u16 **p1, *p2;
	काष्ठा uni_pagedir *p;
  
	/* Only 16-bit codes supported at this समय */
	अगर (ucs > 0xffff)
		वापस -4;		/* Not found */
	अन्यथा अगर (ucs < 0x20)
		वापस -1;		/* Not a prपूर्णांकable अक्षरacter */
	अन्यथा अगर (ucs == 0xfeff || (ucs >= 0x200b && ucs <= 0x200f))
		वापस -2;			/* Zero-width space */
	/*
	 * UNI_सूचीECT_BASE indicates the start of the region in the User Zone
	 * which always has a 1:1 mapping to the currently loaded font.  The
	 * UNI_सूचीECT_MASK indicates the bit span of the region.
	 */
	अन्यथा अगर ((ucs & ~UNI_सूचीECT_MASK) == UNI_सूचीECT_BASE)
		वापस ucs & UNI_सूचीECT_MASK;
  
	अगर (!*conp->vc_uni_pagedir_loc)
		वापस -3;

	p = *conp->vc_uni_pagedir_loc;
	अगर ((p1 = p->uni_pgdir[ucs >> 11]) &&
	    (p2 = p1[(ucs >> 6) & 0x1f]) &&
	    (h = p2[ucs & 0x3f]) < MAX_GLYPH)
		वापस h;

	वापस -4;		/* not found */
पूर्ण

/*
 * This is called at sys_setup समय, after memory and the console are
 * initialized.  It must be possible to call kदो_स्मृति(..., GFP_KERNEL)
 * from this function, hence the call from sys_setup.
 */
व्योम __init 
console_map_init(व्योम)
अणु
	पूर्णांक i;
	
	क्रम (i = 0; i < MAX_NR_CONSOLES; i++)
		अगर (vc_cons_allocated(i) && !*vc_cons[i].d->vc_uni_pagedir_loc)
			con_set_शेष_unimap(vc_cons[i].d);
पूर्ण

