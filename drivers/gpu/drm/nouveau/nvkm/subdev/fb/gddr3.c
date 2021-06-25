<शैली गुरु>
/*
 * Copyright 2013 Red Hat Inc.
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
 * Authors: Ben Skeggs <bskeggs@redhat.com>
 * 	    Roy Spliet <rspliet@eclipso.eu>
 */
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
ramgddr3_cl_lo[] = अणु
	अणु 5, 5 पूर्ण, अणु 7, 7 पूर्ण, अणु 8, 0 पूर्ण, अणु 9, 1 पूर्ण, अणु 10, 2 पूर्ण, अणु 11, 3 पूर्ण, अणु 12, 8 पूर्ण,
	/* the below are mentioned in some, but not all, gddr3 करोcs */
	अणु 13, 9 पूर्ण, अणु 14, 6 पूर्ण,
	/* XXX: Per Samsung करोcs, are these used? They overlap with Qimonda */
	/* अणु 4, 4 पूर्ण, अणु 5, 5 पूर्ण, अणु 6, 6 पूर्ण, अणु 12, 8 पूर्ण, अणु 13, 9 पूर्ण, अणु 14, 10 पूर्ण,
	 * अणु 15, 11 पूर्ण, */
	अणु -1 पूर्ण
पूर्ण;

अटल स्थिर काष्ठा ramxlat
ramgddr3_cl_hi[] = अणु
	अणु 10, 2 पूर्ण, अणु 11, 3 पूर्ण, अणु 12, 4 पूर्ण, अणु 13, 5 पूर्ण, अणु 14, 6 पूर्ण, अणु 15, 7 पूर्ण,
	अणु 16, 0 पूर्ण, अणु 17, 1 पूर्ण,
	अणु -1 पूर्ण
पूर्ण;

अटल स्थिर काष्ठा ramxlat
ramgddr3_wr_lo[] = अणु
	अणु 5, 2 पूर्ण, अणु 7, 4 पूर्ण, अणु 8, 5 पूर्ण, अणु 9, 6 पूर्ण, अणु 10, 7 पूर्ण,
	अणु 11, 0 पूर्ण, अणु 13 , 1 पूर्ण,
	/* the below are mentioned in some, but not all, gddr3 करोcs */
	अणु 4, 0 पूर्ण, अणु 6, 3 पूर्ण, अणु 12, 1 पूर्ण,
	अणु -1 पूर्ण
पूर्ण;

पूर्णांक
nvkm_gddr3_calc(काष्ठा nvkm_ram *ram)
अणु
	पूर्णांक CL, WR, CWL, DLL = 0, ODT = 0, RON, hi;

	चयन (ram->next->bios.timing_ver) अणु
	हाल 0x10:
		CWL = ram->next->bios.timing_10_CWL;
		CL  = ram->next->bios.timing_10_CL;
		WR  = ram->next->bios.timing_10_WR;
		DLL = !ram->next->bios.ramcfg_DLLoff;
		ODT = ram->next->bios.timing_10_ODT;
		RON = ram->next->bios.ramcfg_RON;
		अवरोध;
	हाल 0x20:
		CWL = (ram->next->bios.timing[1] & 0x00000f80) >> 7;
		CL  = (ram->next->bios.timing[1] & 0x0000001f) >> 0;
		WR  = (ram->next->bios.timing[2] & 0x007f0000) >> 16;
		/* XXX: Get these values from the VBIOS instead */
		DLL = !(ram->mr[1] & 0x1);
		RON = !((ram->mr[1] & 0x300) >> 8);
		अवरोध;
	शेष:
		वापस -ENOSYS;
	पूर्ण

	अगर (ram->next->bios.timing_ver == 0x20 ||
	    ram->next->bios.ramcfg_timing == 0xff) अणु
		ODT =  (ram->mr[1] & 0xc) >> 2;
	पूर्ण

	hi = ram->mr[2] & 0x1;
	CL  = ramxlat(hi ? ramgddr3_cl_hi : ramgddr3_cl_lo, CL);
	WR  = ramxlat(ramgddr3_wr_lo, WR);
	अगर (CL < 0 || CWL < 1 || CWL > 7 || WR < 0)
		वापस -EINVAL;

	ram->mr[0] &= ~0xf74;
	ram->mr[0] |= (CWL & 0x07) << 9;
	ram->mr[0] |= (CL & 0x07) << 4;
	ram->mr[0] |= (CL & 0x08) >> 1;

	ram->mr[1] &= ~0x3fc;
	ram->mr[1] |= (ODT & 0x03) << 2;
	ram->mr[1] |= (RON & 0x03) << 8;
	ram->mr[1] |= (WR  & 0x03) << 4;
	ram->mr[1] |= (WR  & 0x04) << 5;
	ram->mr[1] |= !DLL << 6;
	वापस 0;
पूर्ण
