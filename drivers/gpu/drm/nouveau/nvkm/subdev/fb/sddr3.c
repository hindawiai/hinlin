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
ramddr3_cl[] = अणु
	अणु 5, 2 पूर्ण, अणु 6, 4 पूर्ण, अणु 7, 6 पूर्ण, अणु 8, 8 पूर्ण, अणु 9, 10 पूर्ण, अणु 10, 12 पूर्ण,
	अणु 11, 14 पूर्ण,
	/* the below are mentioned in some, but not all, ddr3 करोcs */
	अणु 12, 1 पूर्ण, अणु 13, 3 पूर्ण, अणु 14, 5 पूर्ण,
	अणु -1 पूर्ण
पूर्ण;

अटल स्थिर काष्ठा ramxlat
ramddr3_wr[] = अणु
	अणु 5, 1 पूर्ण, अणु 6, 2 पूर्ण, अणु 7, 3 पूर्ण, अणु 8, 4 पूर्ण, अणु 10, 5 पूर्ण, अणु 12, 6 पूर्ण,
	/* the below are mentioned in some, but not all, ddr3 करोcs */
	अणु 14, 7 पूर्ण, अणु 15, 7 पूर्ण, अणु 16, 0 पूर्ण,
	अणु -1 पूर्ण
पूर्ण;

अटल स्थिर काष्ठा ramxlat
ramddr3_cwl[] = अणु
	अणु 5, 0 पूर्ण, अणु 6, 1 पूर्ण, अणु 7, 2 पूर्ण, अणु 8, 3 पूर्ण,
	/* the below are mentioned in some, but not all, ddr3 करोcs */
	अणु 9, 4 पूर्ण, अणु 10, 5 पूर्ण,
	अणु -1 पूर्ण
पूर्ण;

पूर्णांक
nvkm_sddr3_calc(काष्ठा nvkm_ram *ram)
अणु
	पूर्णांक CWL, CL, WR, DLL = 0, ODT = 0;

	DLL = !ram->next->bios.ramcfg_DLLoff;

	चयन (ram->next->bios.timing_ver) अणु
	हाल 0x10:
		अगर (ram->next->bios.timing_hdr < 0x17) अणु
			/* XXX: NV50: Get CWL from the timing रेजिस्टर */
			वापस -ENOSYS;
		पूर्ण
		CWL = ram->next->bios.timing_10_CWL;
		CL  = ram->next->bios.timing_10_CL;
		WR  = ram->next->bios.timing_10_WR;
		ODT = ram->next->bios.timing_10_ODT;
		अवरोध;
	हाल 0x20:
		CWL = (ram->next->bios.timing[1] & 0x00000f80) >> 7;
		CL  = (ram->next->bios.timing[1] & 0x0000001f) >> 0;
		WR  = (ram->next->bios.timing[2] & 0x007f0000) >> 16;
		/* XXX: Get these values from the VBIOS instead */
		ODT =   (ram->mr[1] & 0x004) >> 2 |
			(ram->mr[1] & 0x040) >> 5 |
		        (ram->mr[1] & 0x200) >> 7;
		अवरोध;
	शेष:
		वापस -ENOSYS;
	पूर्ण

	CWL = ramxlat(ramddr3_cwl, CWL);
	CL  = ramxlat(ramddr3_cl, CL);
	WR  = ramxlat(ramddr3_wr, WR);
	अगर (CL < 0 || CWL < 0 || WR < 0)
		वापस -EINVAL;

	ram->mr[0] &= ~0xf74;
	ram->mr[0] |= (WR & 0x07) << 9;
	ram->mr[0] |= (CL & 0x0e) << 3;
	ram->mr[0] |= (CL & 0x01) << 2;

	ram->mr[1] &= ~0x245;
	ram->mr[1] |= (ODT & 0x1) << 2;
	ram->mr[1] |= (ODT & 0x2) << 5;
	ram->mr[1] |= (ODT & 0x4) << 7;
	ram->mr[1] |= !DLL;

	ram->mr[2] &= ~0x038;
	ram->mr[2] |= (CWL & 0x07) << 3;
	वापस 0;
पूर्ण
