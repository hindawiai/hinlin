<शैली गुरु>
/*
 * Copyright 2014 Roy Spliet
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Authors: Roy Spliet <rspliet@eclipso.eu>
 *          Ben Skeggs
 */
#समावेश "priv.h"
#समावेश "ram.h"

काष्ठा ramxlat अणु
	पूर्णांक id;
	u8 enc;
पूर्ण;

अटल अंतरभूत पूर्णांक
ramxlat(स्थिर काष्ठा ramxlat *xlat, पूर्णांक id)
अणु
	जबतक (xlat->id >= 0) अणु
		अगर (xlat->id == id)
			वापस xlat->enc;
		xlat++;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा ramxlat
ramddr2_cl[] = अणु
	अणु 2, 2 पूर्ण, अणु 3, 3 पूर्ण, अणु 4, 4 पूर्ण, अणु 5, 5 पूर्ण, अणु 6, 6 पूर्ण,
	/* The following are available in some, but not all DDR2 करोcs */
	अणु 7, 7 पूर्ण,
	अणु -1 पूर्ण
पूर्ण;

अटल स्थिर काष्ठा ramxlat
ramddr2_wr[] = अणु
	अणु 2, 1 पूर्ण, अणु 3, 2 पूर्ण, अणु 4, 3 पूर्ण, अणु 5, 4 पूर्ण, अणु 6, 5 पूर्ण,
	/* The following are available in some, but not all DDR2 करोcs */
	अणु 7, 6 पूर्ण,
	अणु -1 पूर्ण
पूर्ण;

पूर्णांक
nvkm_sddr2_calc(काष्ठा nvkm_ram *ram)
अणु
	पूर्णांक CL, WR, DLL = 0, ODT = 0;

	चयन (ram->next->bios.timing_ver) अणु
	हाल 0x10:
		CL  = ram->next->bios.timing_10_CL;
		WR  = ram->next->bios.timing_10_WR;
		DLL = !ram->next->bios.ramcfg_DLLoff;
		ODT = ram->next->bios.timing_10_ODT & 3;
		अवरोध;
	हाल 0x20:
		CL  = (ram->next->bios.timing[1] & 0x0000001f);
		WR  = (ram->next->bios.timing[2] & 0x007f0000) >> 16;
		अवरोध;
	शेष:
		वापस -ENOSYS;
	पूर्ण

	अगर (ram->next->bios.timing_ver == 0x20 ||
	    ram->next->bios.ramcfg_timing == 0xff) अणु
		ODT =  (ram->mr[1] & 0x004) >> 2 |
		       (ram->mr[1] & 0x040) >> 5;
	पूर्ण

	CL  = ramxlat(ramddr2_cl, CL);
	WR  = ramxlat(ramddr2_wr, WR);
	अगर (CL < 0 || WR < 0)
		वापस -EINVAL;

	ram->mr[0] &= ~0xf70;
	ram->mr[0] |= (WR & 0x07) << 9;
	ram->mr[0] |= (CL & 0x07) << 4;

	ram->mr[1] &= ~0x045;
	ram->mr[1] |= (ODT & 0x1) << 2;
	ram->mr[1] |= (ODT & 0x2) << 5;
	ram->mr[1] |= !DLL;
	वापस 0;
पूर्ण
