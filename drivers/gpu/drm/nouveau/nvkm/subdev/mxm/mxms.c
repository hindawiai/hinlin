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
#समावेश "mxms.h"

#घोषणा ROM16(x) get_unaligned_le16(&(x))
#घोषणा ROM32(x) get_unaligned_le32(&(x))

अटल u8 *
mxms_data(काष्ठा nvkm_mxm *mxm)
अणु
	वापस mxm->mxms;

पूर्ण

u16
mxms_version(काष्ठा nvkm_mxm *mxm)
अणु
	u8 *mxms = mxms_data(mxm);
	u16 version = (mxms[4] << 8) | mxms[5];
	चयन (version ) अणु
	हाल 0x0200:
	हाल 0x0201:
	हाल 0x0300:
		वापस version;
	शेष:
		अवरोध;
	पूर्ण

	nvkm_debug(&mxm->subdev, "unknown version %d.%d\n", mxms[4], mxms[5]);
	वापस 0x0000;
पूर्ण

u16
mxms_headerlen(काष्ठा nvkm_mxm *mxm)
अणु
	वापस 8;
पूर्ण

u16
mxms_काष्ठाlen(काष्ठा nvkm_mxm *mxm)
अणु
	वापस *(u16 *)&mxms_data(mxm)[6];
पूर्ण

bool
mxms_checksum(काष्ठा nvkm_mxm *mxm)
अणु
	u16 size = mxms_headerlen(mxm) + mxms_काष्ठाlen(mxm);
	u8 *mxms = mxms_data(mxm), sum = 0;
	जबतक (size--)
		sum += *mxms++;
	अगर (sum) अणु
		nvkm_debug(&mxm->subdev, "checksum invalid\n");
		वापस false;
	पूर्ण
	वापस true;
पूर्ण

bool
mxms_valid(काष्ठा nvkm_mxm *mxm)
अणु
	u8 *mxms = mxms_data(mxm);
	अगर (*(u32 *)mxms != 0x5f4d584d) अणु
		nvkm_debug(&mxm->subdev, "signature invalid\n");
		वापस false;
	पूर्ण

	अगर (!mxms_version(mxm) || !mxms_checksum(mxm))
		वापस false;

	वापस true;
पूर्ण

bool
mxms_क्रमeach(काष्ठा nvkm_mxm *mxm, u8 types,
	     bool (*exec)(काष्ठा nvkm_mxm *, u8 *, व्योम *), व्योम *info)
अणु
	काष्ठा nvkm_subdev *subdev = &mxm->subdev;
	u8 *mxms = mxms_data(mxm);
	u8 *desc = mxms + mxms_headerlen(mxm);
	u8 *fini = desc + mxms_काष्ठाlen(mxm) - 1;
	जबतक (desc < fini) अणु
		u8 type = desc[0] & 0x0f;
		u8 headerlen = 0;
		u8 recordlen = 0;
		u8 entries = 0;

		चयन (type) अणु
		हाल 0: /* Output Device Structure */
			अगर (mxms_version(mxm) >= 0x0300)
				headerlen = 8;
			अन्यथा
				headerlen = 6;
			अवरोध;
		हाल 1: /* System Cooling Capability Structure */
		हाल 2: /* Thermal Structure */
		हाल 3: /* Input Power Structure */
			headerlen = 4;
			अवरोध;
		हाल 4: /* GPIO Device Structure */
			headerlen = 4;
			recordlen = 2;
			entries   = (ROM32(desc[0]) & 0x01f00000) >> 20;
			अवरोध;
		हाल 5: /* Venकरोr Specअगरic Structure */
			headerlen = 8;
			अवरोध;
		हाल 6: /* Backlight Control Structure */
			अगर (mxms_version(mxm) >= 0x0300) अणु
				headerlen = 4;
				recordlen = 8;
				entries   = (desc[1] & 0xf0) >> 4;
			पूर्ण अन्यथा अणु
				headerlen = 8;
			पूर्ण
			अवरोध;
		हाल 7: /* Fan Control Structure */
			headerlen = 8;
			recordlen = 4;
			entries   = desc[1] & 0x07;
			अवरोध;
		शेष:
			nvkm_debug(subdev, "unknown descriptor type %d\n", type);
			वापस false;
		पूर्ण

		अगर (mxm->subdev.debug >= NV_DBG_DEBUG && (exec == शून्य)) अणु
			अटल स्थिर अक्षर * mxms_desc[] = अणु
				"ODS", "SCCS", "TS", "IPS",
				"GSD", "VSS", "BCS", "FCS",
			पूर्ण;
			u8 *dump = desc;
			अक्षर data[32], *ptr;
			पूर्णांक i, j;

			क्रम (j = headerlen - 1, ptr = data; j >= 0; j--)
				ptr += प्र_लिखो(ptr, "%02x", dump[j]);
			dump += headerlen;

			nvkm_debug(subdev, "%4s: %s\n", mxms_desc[type], data);
			क्रम (i = 0; i < entries; i++, dump += recordlen) अणु
				क्रम (j = recordlen - 1, ptr = data; j >= 0; j--)
					ptr += प्र_लिखो(ptr, "%02x", dump[j]);
				nvkm_debug(subdev, "      %s\n", data);
			पूर्ण
		पूर्ण

		अगर (types & (1 << type)) अणु
			अगर (!exec(mxm, desc, info))
				वापस false;
		पूर्ण

		desc += headerlen + (entries * recordlen);
	पूर्ण

	वापस true;
पूर्ण

व्योम
mxms_output_device(काष्ठा nvkm_mxm *mxm, u8 *pdata, काष्ठा mxms_odev *desc)
अणु
	u64 data = ROM32(pdata[0]);
	अगर (mxms_version(mxm) >= 0x0300)
		data |= (u64)ROM16(pdata[4]) << 32;

	desc->outp_type = (data & 0x00000000000000f0ULL) >> 4;
	desc->ddc_port  = (data & 0x0000000000000f00ULL) >> 8;
	desc->conn_type = (data & 0x000000000001f000ULL) >> 12;
	desc->dig_conn  = (data & 0x0000000000780000ULL) >> 19;
पूर्ण
