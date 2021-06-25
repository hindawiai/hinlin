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
#समावेश <subdev/bios/bit.h>
#समावेश <subdev/bios/mxm.h>

u16
mxm_table(काष्ठा nvkm_bios *bios, u8 *ver, u8 *hdr)
अणु
	काष्ठा nvkm_subdev *subdev = &bios->subdev;
	काष्ठा bit_entry x;

	अगर (bit_entry(bios, 'x', &x)) अणु
		nvkm_debug(subdev, "BIT 'x' table not present\n");
		वापस 0x0000;
	पूर्ण

	*ver = x.version;
	*hdr = x.length;
	अगर (*ver != 1 || *hdr < 3) अणु
		nvkm_warn(subdev, "BIT 'x' table %d/%d unknown\n", *ver, *hdr);
		वापस 0x0000;
	पूर्ण

	वापस x.offset;
पूर्ण

/* These map MXM v2.x digital connection values to the appropriate SOR/link,
 * hopefully they're correct क्रम all boards within the same chipset...
 *
 * MXM v3.x VBIOS are nicer and provide poपूर्णांकers to these tables.
 */
अटल u8 g84_sor_map[16] = अणु
	0x00, 0x12, 0x22, 0x11, 0x32, 0x31, 0x11, 0x31,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
पूर्ण;

अटल u8 g92_sor_map[16] = अणु
	0x00, 0x12, 0x22, 0x11, 0x32, 0x31, 0x11, 0x31,
	0x11, 0x31, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
पूर्ण;

अटल u8 g94_sor_map[16] = अणु
	0x00, 0x14, 0x24, 0x11, 0x34, 0x31, 0x11, 0x31,
	0x11, 0x31, 0x12, 0x00, 0x00, 0x00, 0x00, 0x00
पूर्ण;

अटल u8 g98_sor_map[16] = अणु
	0x00, 0x14, 0x12, 0x11, 0x00, 0x31, 0x11, 0x31,
	0x11, 0x31, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
पूर्ण;

u8
mxm_sor_map(काष्ठा nvkm_bios *bios, u8 conn)
अणु
	काष्ठा nvkm_subdev *subdev = &bios->subdev;
	u8  ver, hdr;
	u16 mxm = mxm_table(bios, &ver, &hdr);
	अगर (mxm && hdr >= 6) अणु
		u16 map = nvbios_rd16(bios, mxm + 4);
		अगर (map) अणु
			ver = nvbios_rd08(bios, map);
			अगर (ver == 0x10 || ver == 0x11) अणु
				अगर (conn < nvbios_rd08(bios, map + 3)) अणु
					map += nvbios_rd08(bios, map + 1);
					map += conn;
					वापस nvbios_rd08(bios, map);
				पूर्ण

				वापस 0x00;
			पूर्ण

			nvkm_warn(subdev, "unknown sor map v%02x\n", ver);
		पूर्ण
	पूर्ण

	अगर (bios->version.chip == 0x84 || bios->version.chip == 0x86)
		वापस g84_sor_map[conn];
	अगर (bios->version.chip == 0x92)
		वापस g92_sor_map[conn];
	अगर (bios->version.chip == 0x94 || bios->version.chip == 0x96)
		वापस g94_sor_map[conn];
	अगर (bios->version.chip == 0x98)
		वापस g98_sor_map[conn];

	nvkm_warn(subdev, "missing sor map\n");
	वापस 0x00;
पूर्ण

u8
mxm_ddc_map(काष्ठा nvkm_bios *bios, u8 port)
अणु
	काष्ठा nvkm_subdev *subdev = &bios->subdev;
	u8  ver, hdr;
	u16 mxm = mxm_table(bios, &ver, &hdr);
	अगर (mxm && hdr >= 8) अणु
		u16 map = nvbios_rd16(bios, mxm + 6);
		अगर (map) अणु
			ver = nvbios_rd08(bios, map);
			अगर (ver == 0x10) अणु
				अगर (port < nvbios_rd08(bios, map + 3)) अणु
					map += nvbios_rd08(bios, map + 1);
					map += port;
					वापस nvbios_rd08(bios, map);
				पूर्ण

				वापस 0x00;
			पूर्ण

			nvkm_warn(subdev, "unknown ddc map v%02x\n", ver);
		पूर्ण
	पूर्ण

	/* v2.x: directly ग_लिखो port as dcb i2cidx */
	वापस (port << 4) | port;
पूर्ण
