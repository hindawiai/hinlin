<शैली गुरु>
/*
 * Copyright 2012 Red Hat Inc.
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
 * Authors: Ben Skeggs
 */
#समावेश <subdev/मूलप्रण.स>
#समावेश <subdev/bios/dcb.h>

u16
dcb_table(काष्ठा nvkm_bios *bios, u8 *ver, u8 *hdr, u8 *cnt, u8 *len)
अणु
	काष्ठा nvkm_subdev *subdev = &bios->subdev;
	काष्ठा nvkm_device *device = subdev->device;
	u16 dcb = 0x0000;

	अगर (device->card_type > NV_04)
		dcb = nvbios_rd16(bios, 0x36);
	अगर (!dcb) अणु
		nvkm_warn(subdev, "DCB table not found\n");
		वापस dcb;
	पूर्ण

	*ver = nvbios_rd08(bios, dcb);

	अगर (*ver >= 0x42) अणु
		nvkm_warn(subdev, "DCB version 0x%02x unknown\n", *ver);
		वापस 0x0000;
	पूर्ण अन्यथा
	अगर (*ver >= 0x30) अणु
		अगर (nvbios_rd32(bios, dcb + 6) == 0x4edcbdcb) अणु
			*hdr = nvbios_rd08(bios, dcb + 1);
			*cnt = nvbios_rd08(bios, dcb + 2);
			*len = nvbios_rd08(bios, dcb + 3);
			वापस dcb;
		पूर्ण
	पूर्ण अन्यथा
	अगर (*ver >= 0x20) अणु
		अगर (nvbios_rd32(bios, dcb + 4) == 0x4edcbdcb) अणु
			u16 i2c = nvbios_rd16(bios, dcb + 2);
			*hdr = 8;
			*cnt = (i2c - dcb) / 8;
			*len = 8;
			वापस dcb;
		पूर्ण
	पूर्ण अन्यथा
	अगर (*ver >= 0x15) अणु
		अगर (!nvbios_स_भेद(bios, dcb - 7, "DEV_REC", 7)) अणु
			u16 i2c = nvbios_rd16(bios, dcb + 2);
			*hdr = 4;
			*cnt = (i2c - dcb) / 10;
			*len = 10;
			वापस dcb;
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * v1.4 (some NV15/16, NV11+) seems the same as v1.5, but
		 * always has the same single (crt) entry, even when tv-out
		 * present, so the conclusion is this version cannot really
		 * be used.
		 *
		 * v1.2 tables (some NV6/10, and NV15+) normally have the
		 * same 5 entries, which are not specअगरic to the card and so
		 * no use.
		 *
		 * v1.2 करोes have an I2C table that पढ़ो_dcb_i2c_table can
		 * handle, but cards exist (nv11 in #14821) with a bad i2c
		 * table poपूर्णांकer, so use the indices parsed in
		 * parse_bmp_काष्ठाure.
		 *
		 * v1.1 (NV5+, maybe some NV4) is entirely unhelpful
		 */
		nvkm_debug(subdev, "DCB contains no useful data\n");
		वापस 0x0000;
	पूर्ण

	nvkm_warn(subdev, "DCB header validation failed\n");
	वापस 0x0000;
पूर्ण

u16
dcb_outp(काष्ठा nvkm_bios *bios, u8 idx, u8 *ver, u8 *len)
अणु
	u8  hdr, cnt;
	u16 dcb = dcb_table(bios, ver, &hdr, &cnt, len);
	अगर (dcb && idx < cnt)
		वापस dcb + hdr + (idx * *len);
	वापस 0x0000;
पूर्ण

अटल अंतरभूत u16
dcb_outp_hasht(काष्ठा dcb_output *outp)
अणु
	वापस (outp->extdev << 8) | (outp->location << 4) | outp->type;
पूर्ण

अटल अंतरभूत u16
dcb_outp_hashm(काष्ठा dcb_output *outp)
अणु
	वापस (outp->heads << 8) | (outp->link << 6) | outp->or;
पूर्ण

u16
dcb_outp_parse(काष्ठा nvkm_bios *bios, u8 idx, u8 *ver, u8 *len,
	       काष्ठा dcb_output *outp)
अणु
	u16 dcb = dcb_outp(bios, idx, ver, len);
	स_रखो(outp, 0x00, माप(*outp));
	अगर (dcb) अणु
		अगर (*ver >= 0x20) अणु
			u32 conn = nvbios_rd32(bios, dcb + 0x00);
			outp->or        = (conn & 0x0f000000) >> 24;
			outp->location  = (conn & 0x00300000) >> 20;
			outp->bus       = (conn & 0x000f0000) >> 16;
			outp->connector = (conn & 0x0000f000) >> 12;
			outp->heads     = (conn & 0x00000f00) >> 8;
			outp->i2c_index = (conn & 0x000000f0) >> 4;
			outp->type      = (conn & 0x0000000f);
			outp->link      = 0;
		पूर्ण अन्यथा अणु
			dcb = 0x0000;
		पूर्ण

		अगर (*ver >= 0x40) अणु
			u32 conf = nvbios_rd32(bios, dcb + 0x04);
			चयन (outp->type) अणु
			हाल DCB_OUTPUT_DP:
				चयन (conf & 0x00e00000) अणु
				हाल 0x00000000: /* 1.62 */
					outp->dpconf.link_bw = 0x06;
					अवरोध;
				हाल 0x00200000: /* 2.7 */
					outp->dpconf.link_bw = 0x0a;
					अवरोध;
				हाल 0x00400000: /* 5.4 */
					outp->dpconf.link_bw = 0x14;
					अवरोध;
				हाल 0x00600000: /* 8.1 */
				शेष:
					outp->dpconf.link_bw = 0x1e;
					अवरोध;
				पूर्ण

				चयन ((conf & 0x0f000000) >> 24) अणु
				हाल 0xf:
				हाल 0x4:
					outp->dpconf.link_nr = 4;
					अवरोध;
				हाल 0x3:
				हाल 0x2:
					outp->dpconf.link_nr = 2;
					अवरोध;
				हाल 0x1:
				शेष:
					outp->dpconf.link_nr = 1;
					अवरोध;
				पूर्ण
				fallthrough;

			हाल DCB_OUTPUT_TMDS:
			हाल DCB_OUTPUT_LVDS:
				outp->link = (conf & 0x00000030) >> 4;
				outp->sorconf.link = outp->link; /*XXX*/
				outp->extdev = 0x00;
				अगर (outp->location != 0)
					outp->extdev = (conf & 0x0000ff00) >> 8;
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण
		पूर्ण

		outp->hasht = dcb_outp_hasht(outp);
		outp->hashm = dcb_outp_hashm(outp);
	पूर्ण
	वापस dcb;
पूर्ण

u16
dcb_outp_match(काष्ठा nvkm_bios *bios, u16 type, u16 mask,
	       u8 *ver, u8 *len, काष्ठा dcb_output *outp)
अणु
	u16 dcb, idx = 0;
	जबतक ((dcb = dcb_outp_parse(bios, idx++, ver, len, outp))) अणु
		अगर ((dcb_outp_hasht(outp) & 0x00ff) == (type & 0x00ff)) अणु
			अगर ((dcb_outp_hashm(outp) & mask) == mask)
				अवरोध;
		पूर्ण
	पूर्ण
	वापस dcb;
पूर्ण

पूर्णांक
dcb_outp_क्रमeach(काष्ठा nvkm_bios *bios, व्योम *data,
		 पूर्णांक (*exec)(काष्ठा nvkm_bios *, व्योम *, पूर्णांक, u16))
अणु
	पूर्णांक ret, idx = -1;
	u8  ver, len;
	u16 outp;

	जबतक ((outp = dcb_outp(bios, ++idx, &ver, &len))) अणु
		अगर (nvbios_rd32(bios, outp) == 0x00000000)
			अवरोध; /* seen on an NV11 with DCB v1.5 */
		अगर (nvbios_rd32(bios, outp) == 0xffffffff)
			अवरोध; /* seen on an NV17 with DCB v2.0 */

		अगर (nvbios_rd08(bios, outp) == DCB_OUTPUT_UNUSED)
			जारी;
		अगर (nvbios_rd08(bios, outp) == DCB_OUTPUT_EOL)
			अवरोध;

		ret = exec(bios, data, idx, outp);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
