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
#समावेश <subdev/bios/i2c.h>

u16
dcb_i2c_table(काष्ठा nvkm_bios *bios, u8 *ver, u8 *hdr, u8 *cnt, u8 *len)
अणु
	u16 i2c = 0x0000;
	u16 dcb = dcb_table(bios, ver, hdr, cnt, len);
	अगर (dcb) अणु
		अगर (*ver >= 0x15)
			i2c = nvbios_rd16(bios, dcb + 2);
		अगर (*ver >= 0x30)
			i2c = nvbios_rd16(bios, dcb + 4);
	पूर्ण

	अगर (i2c && *ver >= 0x42) अणु
		nvkm_warn(&bios->subdev, "ccb %02x not supported\n", *ver);
		वापस 0x0000;
	पूर्ण

	अगर (i2c && *ver >= 0x30) अणु
		*ver = nvbios_rd08(bios, i2c + 0);
		*hdr = nvbios_rd08(bios, i2c + 1);
		*cnt = nvbios_rd08(bios, i2c + 2);
		*len = nvbios_rd08(bios, i2c + 3);
	पूर्ण अन्यथा अणु
		*ver = *ver; /* use DCB version */
		*hdr = 0;
		*cnt = 16;
		*len = 4;
	पूर्ण

	वापस i2c;
पूर्ण

u16
dcb_i2c_entry(काष्ठा nvkm_bios *bios, u8 idx, u8 *ver, u8 *len)
अणु
	u8  hdr, cnt;
	u16 i2c = dcb_i2c_table(bios, ver, &hdr, &cnt, len);
	अगर (i2c && idx < cnt)
		वापस i2c + hdr + (idx * *len);
	वापस 0x0000;
पूर्ण

पूर्णांक
dcb_i2c_parse(काष्ठा nvkm_bios *bios, u8 idx, काष्ठा dcb_i2c_entry *info)
अणु
	काष्ठा nvkm_subdev *subdev = &bios->subdev;
	u8  ver, len;
	u16 ent = dcb_i2c_entry(bios, idx, &ver, &len);
	अगर (ent) अणु
		अगर (ver >= 0x41) अणु
			u32 ent_value = nvbios_rd32(bios, ent);
			u8 i2c_port = (ent_value >> 0) & 0x1f;
			u8 dpaux_port = (ent_value >> 5) & 0x1f;
			/* value 0x1f means unused according to DCB 4.x spec */
			अगर (i2c_port == 0x1f && dpaux_port == 0x1f)
				info->type = DCB_I2C_UNUSED;
			अन्यथा
				info->type = DCB_I2C_PMGR;
		पूर्ण अन्यथा
		अगर (ver >= 0x30) अणु
			info->type = nvbios_rd08(bios, ent + 0x03);
		पूर्ण अन्यथा अणु
			info->type = nvbios_rd08(bios, ent + 0x03) & 0x07;
			अगर (info->type == 0x07)
				info->type = DCB_I2C_UNUSED;
		पूर्ण

		info->drive = DCB_I2C_UNUSED;
		info->sense = DCB_I2C_UNUSED;
		info->share = DCB_I2C_UNUSED;
		info->auxch = DCB_I2C_UNUSED;

		चयन (info->type) अणु
		हाल DCB_I2C_NV04_BIT:
			info->drive = nvbios_rd08(bios, ent + 0);
			info->sense = nvbios_rd08(bios, ent + 1);
			वापस 0;
		हाल DCB_I2C_NV4E_BIT:
			info->drive = nvbios_rd08(bios, ent + 1);
			वापस 0;
		हाल DCB_I2C_NVIO_BIT:
			info->drive = nvbios_rd08(bios, ent + 0) & 0x0f;
			अगर (nvbios_rd08(bios, ent + 1) & 0x01)
				info->share = nvbios_rd08(bios, ent + 1) >> 1;
			वापस 0;
		हाल DCB_I2C_NVIO_AUX:
			info->auxch = nvbios_rd08(bios, ent + 0) & 0x0f;
			अगर (nvbios_rd08(bios, ent + 1) & 0x01)
					info->share = info->auxch;
			वापस 0;
		हाल DCB_I2C_PMGR:
			info->drive = (nvbios_rd16(bios, ent + 0) & 0x01f) >> 0;
			अगर (info->drive == 0x1f)
				info->drive = DCB_I2C_UNUSED;
			info->auxch = (nvbios_rd16(bios, ent + 0) & 0x3e0) >> 5;
			अगर (info->auxch == 0x1f)
				info->auxch = DCB_I2C_UNUSED;
			info->share = info->auxch;
			वापस 0;
		हाल DCB_I2C_UNUSED:
			वापस 0;
		शेष:
			nvkm_warn(subdev, "unknown i2c type %d\n", info->type);
			info->type = DCB_I2C_UNUSED;
			वापस 0;
		पूर्ण
	पूर्ण

	अगर (bios->bmp_offset && idx < 2) अणु
		/* BMP (from v4.0 has i2c info in the काष्ठाure, it's in a
		 * fixed location on earlier VBIOS
		 */
		अगर (nvbios_rd08(bios, bios->bmp_offset + 5) < 4)
			ent = 0x0048;
		अन्यथा
			ent = 0x0036 + bios->bmp_offset;

		अगर (idx == 0) अणु
			info->drive = nvbios_rd08(bios, ent + 4);
			अगर (!info->drive) info->drive = 0x3f;
			info->sense = nvbios_rd08(bios, ent + 5);
			अगर (!info->sense) info->sense = 0x3e;
		पूर्ण अन्यथा
		अगर (idx == 1) अणु
			info->drive = nvbios_rd08(bios, ent + 6);
			अगर (!info->drive) info->drive = 0x37;
			info->sense = nvbios_rd08(bios, ent + 7);
			अगर (!info->sense) info->sense = 0x36;
		पूर्ण

		info->type  = DCB_I2C_NV04_BIT;
		info->share = DCB_I2C_UNUSED;
		वापस 0;
	पूर्ण

	वापस -ENOENT;
पूर्ण
