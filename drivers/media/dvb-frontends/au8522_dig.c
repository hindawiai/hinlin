<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
    Auvitek AU8522 QAM/8VSB demodulator driver

    Copyright (C) 2008 Steven Toth <stoth@linuxtv.org>


*/

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/माला.स>
#समावेश <linux/delay.h>
#समावेश <media/dvb_frontend.h>
#समावेश "au8522.h"
#समावेश "au8522_priv.h"

अटल पूर्णांक debug;
अटल पूर्णांक zv_mode = 1; /* शेष to on */

#घोषणा dprपूर्णांकk(arg...)\
	करो अणु अगर (debug)\
		prपूर्णांकk(arg);\
	पूर्ण जबतक (0)

काष्ठा mse2snr_tab अणु
	u16 val;
	u16 data;
पूर्ण;

/* VSB SNR lookup table */
अटल काष्ठा mse2snr_tab vsb_mse2snr_tab[] = अणु
	अणु   0, 270 पूर्ण,
	अणु   2, 250 पूर्ण,
	अणु   3, 240 पूर्ण,
	अणु   5, 230 पूर्ण,
	अणु   7, 220 पूर्ण,
	अणु   9, 210 पूर्ण,
	अणु  12, 200 पूर्ण,
	अणु  13, 195 पूर्ण,
	अणु  15, 190 पूर्ण,
	अणु  17, 185 पूर्ण,
	अणु  19, 180 पूर्ण,
	अणु  21, 175 पूर्ण,
	अणु  24, 170 पूर्ण,
	अणु  27, 165 पूर्ण,
	अणु  31, 160 पूर्ण,
	अणु  32, 158 पूर्ण,
	अणु  33, 156 पूर्ण,
	अणु  36, 152 पूर्ण,
	अणु  37, 150 पूर्ण,
	अणु  39, 148 पूर्ण,
	अणु  40, 146 पूर्ण,
	अणु  41, 144 पूर्ण,
	अणु  43, 142 पूर्ण,
	अणु  44, 140 पूर्ण,
	अणु  48, 135 पूर्ण,
	अणु  50, 130 पूर्ण,
	अणु  43, 142 पूर्ण,
	अणु  53, 125 पूर्ण,
	अणु  56, 120 पूर्ण,
	अणु 256, 115 पूर्ण,
पूर्ण;

/* QAM64 SNR lookup table */
अटल काष्ठा mse2snr_tab qam64_mse2snr_tab[] = अणु
	अणु  15,   0 पूर्ण,
	अणु  16, 290 पूर्ण,
	अणु  17, 288 पूर्ण,
	अणु  18, 286 पूर्ण,
	अणु  19, 284 पूर्ण,
	अणु  20, 282 पूर्ण,
	अणु  21, 281 पूर्ण,
	अणु  22, 279 पूर्ण,
	अणु  23, 277 पूर्ण,
	अणु  24, 275 पूर्ण,
	अणु  25, 273 पूर्ण,
	अणु  26, 271 पूर्ण,
	अणु  27, 269 पूर्ण,
	अणु  28, 268 पूर्ण,
	अणु  29, 266 पूर्ण,
	अणु  30, 264 पूर्ण,
	अणु  31, 262 पूर्ण,
	अणु  32, 260 पूर्ण,
	अणु  33, 259 पूर्ण,
	अणु  34, 258 पूर्ण,
	अणु  35, 256 पूर्ण,
	अणु  36, 255 पूर्ण,
	अणु  37, 254 पूर्ण,
	अणु  38, 252 पूर्ण,
	अणु  39, 251 पूर्ण,
	अणु  40, 250 पूर्ण,
	अणु  41, 249 पूर्ण,
	अणु  42, 248 पूर्ण,
	अणु  43, 246 पूर्ण,
	अणु  44, 245 पूर्ण,
	अणु  45, 244 पूर्ण,
	अणु  46, 242 पूर्ण,
	अणु  47, 241 पूर्ण,
	अणु  48, 240 पूर्ण,
	अणु  50, 239 पूर्ण,
	अणु  51, 238 पूर्ण,
	अणु  53, 237 पूर्ण,
	अणु  54, 236 पूर्ण,
	अणु  56, 235 पूर्ण,
	अणु  57, 234 पूर्ण,
	अणु  59, 233 पूर्ण,
	अणु  60, 232 पूर्ण,
	अणु  62, 231 पूर्ण,
	अणु  63, 230 पूर्ण,
	अणु  65, 229 पूर्ण,
	अणु  67, 228 पूर्ण,
	अणु  68, 227 पूर्ण,
	अणु  70, 226 पूर्ण,
	अणु  71, 225 पूर्ण,
	अणु  73, 224 पूर्ण,
	अणु  74, 223 पूर्ण,
	अणु  76, 222 पूर्ण,
	अणु  78, 221 पूर्ण,
	अणु  80, 220 पूर्ण,
	अणु  82, 219 पूर्ण,
	अणु  85, 218 पूर्ण,
	अणु  88, 217 पूर्ण,
	अणु  90, 216 पूर्ण,
	अणु  92, 215 पूर्ण,
	अणु  93, 214 पूर्ण,
	अणु  94, 212 पूर्ण,
	अणु  95, 211 पूर्ण,
	अणु  97, 210 पूर्ण,
	अणु  99, 209 पूर्ण,
	अणु 101, 208 पूर्ण,
	अणु 102, 207 पूर्ण,
	अणु 104, 206 पूर्ण,
	अणु 107, 205 पूर्ण,
	अणु 111, 204 पूर्ण,
	अणु 114, 203 पूर्ण,
	अणु 118, 202 पूर्ण,
	अणु 122, 201 पूर्ण,
	अणु 125, 200 पूर्ण,
	अणु 128, 199 पूर्ण,
	अणु 130, 198 पूर्ण,
	अणु 132, 197 पूर्ण,
	अणु 256, 190 पूर्ण,
पूर्ण;

/* QAM256 SNR lookup table */
अटल काष्ठा mse2snr_tab qam256_mse2snr_tab[] = अणु
	अणु  15,   0 पूर्ण,
	अणु  16, 400 पूर्ण,
	अणु  17, 398 पूर्ण,
	अणु  18, 396 पूर्ण,
	अणु  19, 394 पूर्ण,
	अणु  20, 392 पूर्ण,
	अणु  21, 390 पूर्ण,
	अणु  22, 388 पूर्ण,
	अणु  23, 386 पूर्ण,
	अणु  24, 384 पूर्ण,
	अणु  25, 382 पूर्ण,
	अणु  26, 380 पूर्ण,
	अणु  27, 379 पूर्ण,
	अणु  28, 378 पूर्ण,
	अणु  29, 377 पूर्ण,
	अणु  30, 376 पूर्ण,
	अणु  31, 375 पूर्ण,
	अणु  32, 374 पूर्ण,
	अणु  33, 373 पूर्ण,
	अणु  34, 372 पूर्ण,
	अणु  35, 371 पूर्ण,
	अणु  36, 370 पूर्ण,
	अणु  37, 362 पूर्ण,
	अणु  38, 354 पूर्ण,
	अणु  39, 346 पूर्ण,
	अणु  40, 338 पूर्ण,
	अणु  41, 330 पूर्ण,
	अणु  42, 328 पूर्ण,
	अणु  43, 326 पूर्ण,
	अणु  44, 324 पूर्ण,
	अणु  45, 322 पूर्ण,
	अणु  46, 320 पूर्ण,
	अणु  47, 319 पूर्ण,
	अणु  48, 318 पूर्ण,
	अणु  49, 317 पूर्ण,
	अणु  50, 316 पूर्ण,
	अणु  51, 315 पूर्ण,
	अणु  52, 314 पूर्ण,
	अणु  53, 313 पूर्ण,
	अणु  54, 312 पूर्ण,
	अणु  55, 311 पूर्ण,
	अणु  56, 310 पूर्ण,
	अणु  57, 308 पूर्ण,
	अणु  58, 306 पूर्ण,
	अणु  59, 304 पूर्ण,
	अणु  60, 302 पूर्ण,
	अणु  61, 300 पूर्ण,
	अणु  62, 298 पूर्ण,
	अणु  65, 295 पूर्ण,
	अणु  68, 294 पूर्ण,
	अणु  70, 293 पूर्ण,
	अणु  73, 292 पूर्ण,
	अणु  76, 291 पूर्ण,
	अणु  78, 290 पूर्ण,
	अणु  79, 289 पूर्ण,
	अणु  81, 288 पूर्ण,
	अणु  82, 287 पूर्ण,
	अणु  83, 286 पूर्ण,
	अणु  84, 285 पूर्ण,
	अणु  85, 284 पूर्ण,
	अणु  86, 283 पूर्ण,
	अणु  88, 282 पूर्ण,
	अणु  89, 281 पूर्ण,
	अणु 256, 280 पूर्ण,
पूर्ण;

अटल पूर्णांक au8522_mse2snr_lookup(काष्ठा mse2snr_tab *tab, पूर्णांक sz, पूर्णांक mse,
				 u16 *snr)
अणु
	पूर्णांक i, ret = -EINVAL;
	dprपूर्णांकk("%s()\n", __func__);

	क्रम (i = 0; i < sz; i++) अणु
		अगर (mse < tab[i].val) अणु
			*snr = tab[i].data;
			ret = 0;
			अवरोध;
		पूर्ण
	पूर्ण
	dprपूर्णांकk("%s() snr=%d\n", __func__, *snr);
	वापस ret;
पूर्ण

अटल पूर्णांक au8522_set_अगर(काष्ठा dvb_frontend *fe, क्रमागत au8522_अगर_freq अगर_freq)
अणु
	काष्ठा au8522_state *state = fe->demodulator_priv;
	u8 r0b5, r0b6, r0b7;
	अक्षर *अगरmhz;

	चयन (अगर_freq) अणु
	हाल AU8522_IF_3_25MHZ:
		अगरmhz = "3.25";
		r0b5 = 0x00;
		r0b6 = 0x3d;
		r0b7 = 0xa0;
		अवरोध;
	हाल AU8522_IF_4MHZ:
		अगरmhz = "4.00";
		r0b5 = 0x00;
		r0b6 = 0x4b;
		r0b7 = 0xd9;
		अवरोध;
	हाल AU8522_IF_6MHZ:
		अगरmhz = "6.00";
		r0b5 = 0xfb;
		r0b6 = 0x8e;
		r0b7 = 0x39;
		अवरोध;
	शेष:
		dprपूर्णांकk("%s() IF Frequency not supported\n", __func__);
		वापस -EINVAL;
	पूर्ण
	dprपूर्णांकk("%s() %s MHz\n", __func__, अगरmhz);
	au8522_ग_लिखोreg(state, 0x00b5, r0b5);
	au8522_ग_लिखोreg(state, 0x00b6, r0b6);
	au8522_ग_लिखोreg(state, 0x00b7, r0b7);

	वापस 0;
पूर्ण

/* VSB Modulation table */
अटल काष्ठा अणु
	u16 reg;
	u16 data;
पूर्ण VSB_mod_tab[] = अणु
	अणु 0x0090, 0x84 पूर्ण,
	अणु 0x2005, 0x00 पूर्ण,
	अणु 0x0091, 0x80 पूर्ण,
	अणु 0x00a3, 0x0c पूर्ण,
	अणु 0x00a4, 0xe8 पूर्ण,
	अणु 0x0081, 0xc4 पूर्ण,
	अणु 0x00a5, 0x40 पूर्ण,
	अणु 0x00a7, 0x40 पूर्ण,
	अणु 0x00a6, 0x67 पूर्ण,
	अणु 0x0262, 0x20 पूर्ण,
	अणु 0x021c, 0x30 पूर्ण,
	अणु 0x00d8, 0x1a पूर्ण,
	अणु 0x0227, 0xa0 पूर्ण,
	अणु 0x0121, 0xff पूर्ण,
	अणु 0x00a8, 0xf0 पूर्ण,
	अणु 0x00a9, 0x05 पूर्ण,
	अणु 0x00aa, 0x77 पूर्ण,
	अणु 0x00ab, 0xf0 पूर्ण,
	अणु 0x00ac, 0x05 पूर्ण,
	अणु 0x00ad, 0x77 पूर्ण,
	अणु 0x00ae, 0x41 पूर्ण,
	अणु 0x00af, 0x66 पूर्ण,
	अणु 0x021b, 0xcc पूर्ण,
	अणु 0x021d, 0x80 पूर्ण,
	अणु 0x00a4, 0xe8 पूर्ण,
	अणु 0x0231, 0x13 पूर्ण,
पूर्ण;

/* QAM64 Modulation table */
अटल काष्ठा अणु
	u16 reg;
	u16 data;
पूर्ण QAM64_mod_tab[] = अणु
	अणु 0x00a3, 0x09 पूर्ण,
	अणु 0x00a4, 0x00 पूर्ण,
	अणु 0x0081, 0xc4 पूर्ण,
	अणु 0x00a5, 0x40 पूर्ण,
	अणु 0x00aa, 0x77 पूर्ण,
	अणु 0x00ad, 0x77 पूर्ण,
	अणु 0x00a6, 0x67 पूर्ण,
	अणु 0x0262, 0x20 पूर्ण,
	अणु 0x021c, 0x30 पूर्ण,
	अणु 0x00b8, 0x3e पूर्ण,
	अणु 0x00b9, 0xf0 पूर्ण,
	अणु 0x00ba, 0x01 पूर्ण,
	अणु 0x00bb, 0x18 पूर्ण,
	अणु 0x00bc, 0x50 पूर्ण,
	अणु 0x00bd, 0x00 पूर्ण,
	अणु 0x00be, 0xea पूर्ण,
	अणु 0x00bf, 0xef पूर्ण,
	अणु 0x00c0, 0xfc पूर्ण,
	अणु 0x00c1, 0xbd पूर्ण,
	अणु 0x00c2, 0x1f पूर्ण,
	अणु 0x00c3, 0xfc पूर्ण,
	अणु 0x00c4, 0xdd पूर्ण,
	अणु 0x00c5, 0xaf पूर्ण,
	अणु 0x00c6, 0x00 पूर्ण,
	अणु 0x00c7, 0x38 पूर्ण,
	अणु 0x00c8, 0x30 पूर्ण,
	अणु 0x00c9, 0x05 पूर्ण,
	अणु 0x00ca, 0x4a पूर्ण,
	अणु 0x00cb, 0xd0 पूर्ण,
	अणु 0x00cc, 0x01 पूर्ण,
	अणु 0x00cd, 0xd9 पूर्ण,
	अणु 0x00ce, 0x6f पूर्ण,
	अणु 0x00cf, 0xf9 पूर्ण,
	अणु 0x00d0, 0x70 पूर्ण,
	अणु 0x00d1, 0xdf पूर्ण,
	अणु 0x00d2, 0xf7 पूर्ण,
	अणु 0x00d3, 0xc2 पूर्ण,
	अणु 0x00d4, 0xdf पूर्ण,
	अणु 0x00d5, 0x02 पूर्ण,
	अणु 0x00d6, 0x9a पूर्ण,
	अणु 0x00d7, 0xd0 पूर्ण,
	अणु 0x0250, 0x0d पूर्ण,
	अणु 0x0251, 0xcd पूर्ण,
	अणु 0x0252, 0xe0 पूर्ण,
	अणु 0x0253, 0x05 पूर्ण,
	अणु 0x0254, 0xa7 पूर्ण,
	अणु 0x0255, 0xff पूर्ण,
	अणु 0x0256, 0xed पूर्ण,
	अणु 0x0257, 0x5b पूर्ण,
	अणु 0x0258, 0xae पूर्ण,
	अणु 0x0259, 0xe6 पूर्ण,
	अणु 0x025a, 0x3d पूर्ण,
	अणु 0x025b, 0x0f पूर्ण,
	अणु 0x025c, 0x0d पूर्ण,
	अणु 0x025d, 0xea पूर्ण,
	अणु 0x025e, 0xf2 पूर्ण,
	अणु 0x025f, 0x51 पूर्ण,
	अणु 0x0260, 0xf5 पूर्ण,
	अणु 0x0261, 0x06 पूर्ण,
	अणु 0x021a, 0x00 पूर्ण,
	अणु 0x0546, 0x40 पूर्ण,
	अणु 0x0210, 0xc7 पूर्ण,
	अणु 0x0211, 0xaa पूर्ण,
	अणु 0x0212, 0xab पूर्ण,
	अणु 0x0213, 0x02 पूर्ण,
	अणु 0x0502, 0x00 पूर्ण,
	अणु 0x0121, 0x04 पूर्ण,
	अणु 0x0122, 0x04 पूर्ण,
	अणु 0x052e, 0x10 पूर्ण,
	अणु 0x00a4, 0xca पूर्ण,
	अणु 0x00a7, 0x40 पूर्ण,
	अणु 0x0526, 0x01 पूर्ण,
पूर्ण;

/* QAM256 Modulation table */
अटल काष्ठा अणु
	u16 reg;
	u16 data;
पूर्ण QAM256_mod_tab[] = अणु
	अणु 0x00a3, 0x09 पूर्ण,
	अणु 0x00a4, 0x00 पूर्ण,
	अणु 0x0081, 0xc4 पूर्ण,
	अणु 0x00a5, 0x40 पूर्ण,
	अणु 0x00aa, 0x77 पूर्ण,
	अणु 0x00ad, 0x77 पूर्ण,
	अणु 0x00a6, 0x67 पूर्ण,
	अणु 0x0262, 0x20 पूर्ण,
	अणु 0x021c, 0x30 पूर्ण,
	अणु 0x00b8, 0x3e पूर्ण,
	अणु 0x00b9, 0xf0 पूर्ण,
	अणु 0x00ba, 0x01 पूर्ण,
	अणु 0x00bb, 0x18 पूर्ण,
	अणु 0x00bc, 0x50 पूर्ण,
	अणु 0x00bd, 0x00 पूर्ण,
	अणु 0x00be, 0xea पूर्ण,
	अणु 0x00bf, 0xef पूर्ण,
	अणु 0x00c0, 0xfc पूर्ण,
	अणु 0x00c1, 0xbd पूर्ण,
	अणु 0x00c2, 0x1f पूर्ण,
	अणु 0x00c3, 0xfc पूर्ण,
	अणु 0x00c4, 0xdd पूर्ण,
	अणु 0x00c5, 0xaf पूर्ण,
	अणु 0x00c6, 0x00 पूर्ण,
	अणु 0x00c7, 0x38 पूर्ण,
	अणु 0x00c8, 0x30 पूर्ण,
	अणु 0x00c9, 0x05 पूर्ण,
	अणु 0x00ca, 0x4a पूर्ण,
	अणु 0x00cb, 0xd0 पूर्ण,
	अणु 0x00cc, 0x01 पूर्ण,
	अणु 0x00cd, 0xd9 पूर्ण,
	अणु 0x00ce, 0x6f पूर्ण,
	अणु 0x00cf, 0xf9 पूर्ण,
	अणु 0x00d0, 0x70 पूर्ण,
	अणु 0x00d1, 0xdf पूर्ण,
	अणु 0x00d2, 0xf7 पूर्ण,
	अणु 0x00d3, 0xc2 पूर्ण,
	अणु 0x00d4, 0xdf पूर्ण,
	अणु 0x00d5, 0x02 पूर्ण,
	अणु 0x00d6, 0x9a पूर्ण,
	अणु 0x00d7, 0xd0 पूर्ण,
	अणु 0x0250, 0x0d पूर्ण,
	अणु 0x0251, 0xcd पूर्ण,
	अणु 0x0252, 0xe0 पूर्ण,
	अणु 0x0253, 0x05 पूर्ण,
	अणु 0x0254, 0xa7 पूर्ण,
	अणु 0x0255, 0xff पूर्ण,
	अणु 0x0256, 0xed पूर्ण,
	अणु 0x0257, 0x5b पूर्ण,
	अणु 0x0258, 0xae पूर्ण,
	अणु 0x0259, 0xe6 पूर्ण,
	अणु 0x025a, 0x3d पूर्ण,
	अणु 0x025b, 0x0f पूर्ण,
	अणु 0x025c, 0x0d पूर्ण,
	अणु 0x025d, 0xea पूर्ण,
	अणु 0x025e, 0xf2 पूर्ण,
	अणु 0x025f, 0x51 पूर्ण,
	अणु 0x0260, 0xf5 पूर्ण,
	अणु 0x0261, 0x06 पूर्ण,
	अणु 0x021a, 0x00 पूर्ण,
	अणु 0x0546, 0x40 पूर्ण,
	अणु 0x0210, 0x26 पूर्ण,
	अणु 0x0211, 0xf6 पूर्ण,
	अणु 0x0212, 0x84 पूर्ण,
	अणु 0x0213, 0x02 पूर्ण,
	अणु 0x0502, 0x01 पूर्ण,
	अणु 0x0121, 0x04 पूर्ण,
	अणु 0x0122, 0x04 पूर्ण,
	अणु 0x052e, 0x10 पूर्ण,
	अणु 0x00a4, 0xca पूर्ण,
	अणु 0x00a7, 0x40 पूर्ण,
	अणु 0x0526, 0x01 पूर्ण,
पूर्ण;

अटल काष्ठा अणु
	u16 reg;
	u16 data;
पूर्ण QAM256_mod_tab_zv_mode[] = अणु
	अणु 0x80a3, 0x09 पूर्ण,
	अणु 0x80a4, 0x00 पूर्ण,
	अणु 0x8081, 0xc4 पूर्ण,
	अणु 0x80a5, 0x40 पूर्ण,
	अणु 0x80b5, 0xfb पूर्ण,
	अणु 0x80b6, 0x8e पूर्ण,
	अणु 0x80b7, 0x39 पूर्ण,
	अणु 0x80aa, 0x77 पूर्ण,
	अणु 0x80ad, 0x77 पूर्ण,
	अणु 0x80a6, 0x67 पूर्ण,
	अणु 0x8262, 0x20 पूर्ण,
	अणु 0x821c, 0x30 पूर्ण,
	अणु 0x80b8, 0x3e पूर्ण,
	अणु 0x80b9, 0xf0 पूर्ण,
	अणु 0x80ba, 0x01 पूर्ण,
	अणु 0x80bb, 0x18 पूर्ण,
	अणु 0x80bc, 0x50 पूर्ण,
	अणु 0x80bd, 0x00 पूर्ण,
	अणु 0x80be, 0xea पूर्ण,
	अणु 0x80bf, 0xef पूर्ण,
	अणु 0x80c0, 0xfc पूर्ण,
	अणु 0x80c1, 0xbd पूर्ण,
	अणु 0x80c2, 0x1f पूर्ण,
	अणु 0x80c3, 0xfc पूर्ण,
	अणु 0x80c4, 0xdd पूर्ण,
	अणु 0x80c5, 0xaf पूर्ण,
	अणु 0x80c6, 0x00 पूर्ण,
	अणु 0x80c7, 0x38 पूर्ण,
	अणु 0x80c8, 0x30 पूर्ण,
	अणु 0x80c9, 0x05 पूर्ण,
	अणु 0x80ca, 0x4a पूर्ण,
	अणु 0x80cb, 0xd0 पूर्ण,
	अणु 0x80cc, 0x01 पूर्ण,
	अणु 0x80cd, 0xd9 पूर्ण,
	अणु 0x80ce, 0x6f पूर्ण,
	अणु 0x80cf, 0xf9 पूर्ण,
	अणु 0x80d0, 0x70 पूर्ण,
	अणु 0x80d1, 0xdf पूर्ण,
	अणु 0x80d2, 0xf7 पूर्ण,
	अणु 0x80d3, 0xc2 पूर्ण,
	अणु 0x80d4, 0xdf पूर्ण,
	अणु 0x80d5, 0x02 पूर्ण,
	अणु 0x80d6, 0x9a पूर्ण,
	अणु 0x80d7, 0xd0 पूर्ण,
	अणु 0x8250, 0x0d पूर्ण,
	अणु 0x8251, 0xcd पूर्ण,
	अणु 0x8252, 0xe0 पूर्ण,
	अणु 0x8253, 0x05 पूर्ण,
	अणु 0x8254, 0xa7 पूर्ण,
	अणु 0x8255, 0xff पूर्ण,
	अणु 0x8256, 0xed पूर्ण,
	अणु 0x8257, 0x5b पूर्ण,
	अणु 0x8258, 0xae पूर्ण,
	अणु 0x8259, 0xe6 पूर्ण,
	अणु 0x825a, 0x3d पूर्ण,
	अणु 0x825b, 0x0f पूर्ण,
	अणु 0x825c, 0x0d पूर्ण,
	अणु 0x825d, 0xea पूर्ण,
	अणु 0x825e, 0xf2 पूर्ण,
	अणु 0x825f, 0x51 पूर्ण,
	अणु 0x8260, 0xf5 पूर्ण,
	अणु 0x8261, 0x06 पूर्ण,
	अणु 0x821a, 0x01 पूर्ण,
	अणु 0x8546, 0x40 पूर्ण,
	अणु 0x8210, 0x26 पूर्ण,
	अणु 0x8211, 0xf6 पूर्ण,
	अणु 0x8212, 0x84 पूर्ण,
	अणु 0x8213, 0x02 पूर्ण,
	अणु 0x8502, 0x01 पूर्ण,
	अणु 0x8121, 0x04 पूर्ण,
	अणु 0x8122, 0x04 पूर्ण,
	अणु 0x852e, 0x10 पूर्ण,
	अणु 0x80a4, 0xca पूर्ण,
	अणु 0x80a7, 0x40 पूर्ण,
	अणु 0x8526, 0x01 पूर्ण,
पूर्ण;

अटल पूर्णांक au8522_enable_modulation(काष्ठा dvb_frontend *fe,
				    क्रमागत fe_modulation m)
अणु
	काष्ठा au8522_state *state = fe->demodulator_priv;
	पूर्णांक i;

	dprपूर्णांकk("%s(0x%08x)\n", __func__, m);

	चयन (m) अणु
	हाल VSB_8:
		dprपूर्णांकk("%s() VSB_8\n", __func__);
		क्रम (i = 0; i < ARRAY_SIZE(VSB_mod_tab); i++)
			au8522_ग_लिखोreg(state,
				VSB_mod_tab[i].reg,
				VSB_mod_tab[i].data);
		au8522_set_अगर(fe, state->config.vsb_अगर);
		अवरोध;
	हाल QAM_64:
		dprपूर्णांकk("%s() QAM 64\n", __func__);
		क्रम (i = 0; i < ARRAY_SIZE(QAM64_mod_tab); i++)
			au8522_ग_लिखोreg(state,
				QAM64_mod_tab[i].reg,
				QAM64_mod_tab[i].data);
		au8522_set_अगर(fe, state->config.qam_अगर);
		अवरोध;
	हाल QAM_256:
		अगर (zv_mode) अणु
			dprपूर्णांकk("%s() QAM 256 (zv_mode)\n", __func__);
			क्रम (i = 0; i < ARRAY_SIZE(QAM256_mod_tab_zv_mode); i++)
				au8522_ग_लिखोreg(state,
					QAM256_mod_tab_zv_mode[i].reg,
					QAM256_mod_tab_zv_mode[i].data);
			au8522_set_अगर(fe, state->config.qam_अगर);
			msleep(100);
			au8522_ग_लिखोreg(state, 0x821a, 0x00);
		पूर्ण अन्यथा अणु
			dprपूर्णांकk("%s() QAM 256\n", __func__);
			क्रम (i = 0; i < ARRAY_SIZE(QAM256_mod_tab); i++)
				au8522_ग_लिखोreg(state,
					QAM256_mod_tab[i].reg,
					QAM256_mod_tab[i].data);
			au8522_set_अगर(fe, state->config.qam_अगर);
		पूर्ण
		अवरोध;
	शेष:
		dprपूर्णांकk("%s() Invalid modulation\n", __func__);
		वापस -EINVAL;
	पूर्ण

	state->current_modulation = m;

	वापस 0;
पूर्ण

/* Talk to the demod, set the FEC, GUARD, QAM settings etc */
अटल पूर्णांक au8522_set_frontend(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	काष्ठा au8522_state *state = fe->demodulator_priv;
	पूर्णांक ret = -EINVAL;

	dprपूर्णांकk("%s(frequency=%d)\n", __func__, c->frequency);

	अगर ((state->current_frequency == c->frequency) &&
	    (state->current_modulation == c->modulation))
		वापस 0;

	अगर (fe->ops.tuner_ops.set_params) अणु
		अगर (fe->ops.i2c_gate_ctrl)
			fe->ops.i2c_gate_ctrl(fe, 1);
		ret = fe->ops.tuner_ops.set_params(fe);
		अगर (fe->ops.i2c_gate_ctrl)
			fe->ops.i2c_gate_ctrl(fe, 0);
	पूर्ण

	अगर (ret < 0)
		वापस ret;

	/* Allow the tuner to settle */
	अगर (zv_mode) अणु
		dprपूर्णांकk("%s() increase tuner settling time for zv_mode\n",
			__func__);
		msleep(250);
	पूर्ण अन्यथा
		msleep(100);

	au8522_enable_modulation(fe, c->modulation);

	state->current_frequency = c->frequency;

	वापस 0;
पूर्ण

अटल पूर्णांक au8522_पढ़ो_status(काष्ठा dvb_frontend *fe, क्रमागत fe_status *status)
अणु
	काष्ठा au8522_state *state = fe->demodulator_priv;
	u8 reg;
	u32 tuner_status = 0;

	*status = 0;

	अगर (state->current_modulation == VSB_8) अणु
		dprपूर्णांकk("%s() Checking VSB_8\n", __func__);
		reg = au8522_पढ़ोreg(state, 0x0088);
		अगर ((reg & 0x03) == 0x03)
			*status |= FE_HAS_LOCK | FE_HAS_SYNC | FE_HAS_VITERBI;
	पूर्ण अन्यथा अणु
		dprपूर्णांकk("%s() Checking QAM\n", __func__);
		reg = au8522_पढ़ोreg(state, 0x0541);
		अगर (reg & 0x80)
			*status |= FE_HAS_VITERBI;
		अगर (reg & 0x20)
			*status |= FE_HAS_LOCK | FE_HAS_SYNC;
	पूर्ण

	चयन (state->config.status_mode) अणु
	हाल AU8522_DEMODLOCKING:
		dprपूर्णांकk("%s() DEMODLOCKING\n", __func__);
		अगर (*status & FE_HAS_VITERBI)
			*status |= FE_HAS_CARRIER | FE_HAS_SIGNAL;
		अवरोध;
	हाल AU8522_TUNERLOCKING:
		/* Get the tuner status */
		dprपूर्णांकk("%s() TUNERLOCKING\n", __func__);
		अगर (fe->ops.tuner_ops.get_status) अणु
			अगर (fe->ops.i2c_gate_ctrl)
				fe->ops.i2c_gate_ctrl(fe, 1);

			fe->ops.tuner_ops.get_status(fe, &tuner_status);

			अगर (fe->ops.i2c_gate_ctrl)
				fe->ops.i2c_gate_ctrl(fe, 0);
		पूर्ण
		अगर (tuner_status)
			*status |= FE_HAS_CARRIER | FE_HAS_SIGNAL;
		अवरोध;
	पूर्ण
	state->fe_status = *status;

	अगर (*status & FE_HAS_LOCK)
		/* turn on LED, अगर it isn't on alपढ़ोy */
		au8522_led_ctrl(state, -1);
	अन्यथा
		/* turn off LED */
		au8522_led_ctrl(state, 0);

	dprपूर्णांकk("%s() status 0x%08x\n", __func__, *status);

	वापस 0;
पूर्ण

अटल पूर्णांक au8522_led_status(काष्ठा au8522_state *state, स्थिर u16 *snr)
अणु
	काष्ठा au8522_led_config *led_config = state->config.led_cfg;
	पूर्णांक led;
	u16 strong;

	/* bail out अगर we can't control an LED */
	अगर (!led_config)
		वापस 0;

	अगर (0 == (state->fe_status & FE_HAS_LOCK))
		वापस au8522_led_ctrl(state, 0);
	अन्यथा अगर (state->current_modulation == QAM_256)
		strong = led_config->qam256_strong;
	अन्यथा अगर (state->current_modulation == QAM_64)
		strong = led_config->qam64_strong;
	अन्यथा /* (state->current_modulation == VSB_8) */
		strong = led_config->vsb8_strong;

	अगर (*snr >= strong)
		led = 2;
	अन्यथा
		led = 1;

	अगर ((state->led_state) &&
	    (((strong < *snr) ? (*snr - strong) : (strong - *snr)) <= 10))
		/* snr didn't change enough to bother
		 * changing the color of the led */
		वापस 0;

	वापस au8522_led_ctrl(state, led);
पूर्ण

अटल पूर्णांक au8522_पढ़ो_snr(काष्ठा dvb_frontend *fe, u16 *snr)
अणु
	काष्ठा au8522_state *state = fe->demodulator_priv;
	पूर्णांक ret = -EINVAL;

	dprपूर्णांकk("%s()\n", __func__);

	अगर (state->current_modulation == QAM_256)
		ret = au8522_mse2snr_lookup(qam256_mse2snr_tab,
					    ARRAY_SIZE(qam256_mse2snr_tab),
					    au8522_पढ़ोreg(state, 0x0522),
					    snr);
	अन्यथा अगर (state->current_modulation == QAM_64)
		ret = au8522_mse2snr_lookup(qam64_mse2snr_tab,
					    ARRAY_SIZE(qam64_mse2snr_tab),
					    au8522_पढ़ोreg(state, 0x0522),
					    snr);
	अन्यथा /* VSB_8 */
		ret = au8522_mse2snr_lookup(vsb_mse2snr_tab,
					    ARRAY_SIZE(vsb_mse2snr_tab),
					    au8522_पढ़ोreg(state, 0x0311),
					    snr);

	अगर (state->config.led_cfg)
		au8522_led_status(state, snr);

	वापस ret;
पूर्ण

अटल पूर्णांक au8522_पढ़ो_संकेत_strength(काष्ठा dvb_frontend *fe,
				       u16 *संकेत_strength)
अणु
	/* borrowed from lgdt330x.c
	 *
	 * Calculate strength from SNR up to 35dB
	 * Even though the SNR can go higher than 35dB,
	 * there is some comक्रमt factor in having a range of
	 * strong संकेतs that can show at 100%
	 */
	u16 snr;
	u32 पंचांगp;
	पूर्णांक ret = au8522_पढ़ो_snr(fe, &snr);

	*संकेत_strength = 0;

	अगर (0 == ret) अणु
		/* The following calculation method was chosen
		 * purely क्रम the sake of code re-use from the
		 * other demod drivers that use this method */

		/* Convert from SNR in dB * 10 to 8.24 fixed-poपूर्णांक */
		पंचांगp = (snr * ((1 << 24) / 10));

		/* Convert from 8.24 fixed-poपूर्णांक to
		 * scale the range 0 - 35*2^24 पूर्णांकo 0 - 65535*/
		अगर (पंचांगp >= 8960 * 0x10000)
			*संकेत_strength = 0xffff;
		अन्यथा
			*संकेत_strength = पंचांगp / 8960;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक au8522_पढ़ो_ucblocks(काष्ठा dvb_frontend *fe, u32 *ucblocks)
अणु
	काष्ठा au8522_state *state = fe->demodulator_priv;

	अगर (state->current_modulation == VSB_8)
		*ucblocks = au8522_पढ़ोreg(state, 0x0087);
	अन्यथा
		*ucblocks = au8522_पढ़ोreg(state, 0x0543);

	वापस 0;
पूर्ण

अटल पूर्णांक au8522_पढ़ो_ber(काष्ठा dvb_frontend *fe, u32 *ber)
अणु
	वापस au8522_पढ़ो_ucblocks(fe, ber);
पूर्ण

अटल पूर्णांक au8522_get_frontend(काष्ठा dvb_frontend *fe,
			       काष्ठा dtv_frontend_properties *c)
अणु
	काष्ठा au8522_state *state = fe->demodulator_priv;

	c->frequency = state->current_frequency;
	c->modulation = state->current_modulation;

	वापस 0;
पूर्ण

अटल पूर्णांक au8522_get_tune_settings(काष्ठा dvb_frontend *fe,
				    काष्ठा dvb_frontend_tune_settings *tune)
अणु
	tune->min_delay_ms = 1000;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dvb_frontend_ops au8522_ops;


अटल व्योम au8522_release(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा au8522_state *state = fe->demodulator_priv;
	au8522_release_state(state);
पूर्ण

काष्ठा dvb_frontend *au8522_attach(स्थिर काष्ठा au8522_config *config,
				   काष्ठा i2c_adapter *i2c)
अणु
	काष्ठा au8522_state *state = शून्य;
	पूर्णांक instance;

	/* allocate memory क्रम the पूर्णांकernal state */
	instance = au8522_get_state(&state, i2c, config->demod_address);
	चयन (instance) अणु
	हाल 0:
		dprपूर्णांकk("%s state allocation failed\n", __func__);
		अवरोध;
	हाल 1:
		/* new demod instance */
		dprपूर्णांकk("%s using new instance\n", __func__);
		अवरोध;
	शेष:
		/* existing demod instance */
		dprपूर्णांकk("%s using existing instance\n", __func__);
		अवरोध;
	पूर्ण

	/* setup the state */
	state->config = *config;
	state->i2c = i2c;
	state->operational_mode = AU8522_DIGITAL_MODE;

	/* create dvb_frontend */
	स_नकल(&state->frontend.ops, &au8522_ops,
	       माप(काष्ठा dvb_frontend_ops));
	state->frontend.demodulator_priv = state;

	state->frontend.ops.analog_ops.i2c_gate_ctrl = au8522_analog_i2c_gate_ctrl;

	अगर (au8522_init(&state->frontend) != 0) अणु
		prपूर्णांकk(KERN_ERR "%s: Failed to initialize correctly\n",
			__func__);
		जाओ error;
	पूर्ण

	/* Note: Leaving the I2C gate खोलो here. */
	au8522_i2c_gate_ctrl(&state->frontend, 1);

	वापस &state->frontend;

error:
	au8522_release_state(state);
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(au8522_attach);

अटल स्थिर काष्ठा dvb_frontend_ops au8522_ops = अणु
	.delsys = अणु SYS_ATSC, SYS_DVBC_ANNEX_B पूर्ण,
	.info = अणु
		.name			= "Auvitek AU8522 QAM/8VSB Frontend",
		.frequency_min_hz	=  54 * MHz,
		.frequency_max_hz	= 858 * MHz,
		.frequency_stepsize_hz	= 62500,
		.caps = FE_CAN_QAM_64 | FE_CAN_QAM_256 | FE_CAN_8VSB
	पूर्ण,

	.init                 = au8522_init,
	.sleep                = au8522_sleep,
	.i2c_gate_ctrl        = au8522_i2c_gate_ctrl,
	.set_frontend         = au8522_set_frontend,
	.get_frontend         = au8522_get_frontend,
	.get_tune_settings    = au8522_get_tune_settings,
	.पढ़ो_status          = au8522_पढ़ो_status,
	.पढ़ो_ber             = au8522_पढ़ो_ber,
	.पढ़ो_संकेत_strength = au8522_पढ़ो_संकेत_strength,
	.पढ़ो_snr             = au8522_पढ़ो_snr,
	.पढ़ो_ucblocks        = au8522_पढ़ो_ucblocks,
	.release              = au8522_release,
पूर्ण;

module_param(debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "Enable verbose debug messages");

module_param(zv_mode, पूर्णांक, 0644);
MODULE_PARM_DESC(zv_mode, "Turn on/off ZeeVee modulator compatibility mode (default:on).\n"
	"\t\ton - modified AU8522 QAM256 initialization.\n"
	"\t\tProvides faster lock when using ZeeVee modulator based sources");

MODULE_DESCRIPTION("Auvitek AU8522 QAM-B/ATSC Demodulator driver");
MODULE_AUTHOR("Steven Toth");
MODULE_LICENSE("GPL");
