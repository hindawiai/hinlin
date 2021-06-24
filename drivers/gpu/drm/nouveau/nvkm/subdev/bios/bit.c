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

पूर्णांक
bit_entry(काष्ठा nvkm_bios *bios, u8 id, काष्ठा bit_entry *bit)
अणु
	अगर (likely(bios->bit_offset)) अणु
		u8  entries = nvbios_rd08(bios, bios->bit_offset + 10);
		u32 entry   = bios->bit_offset + 12;
		जबतक (entries--) अणु
			अगर (nvbios_rd08(bios, entry + 0) == id) अणु
				bit->id      = nvbios_rd08(bios, entry + 0);
				bit->version = nvbios_rd08(bios, entry + 1);
				bit->length  = nvbios_rd16(bios, entry + 2);
				bit->offset  = nvbios_rd16(bios, entry + 4);
				वापस 0;
			पूर्ण

			entry += nvbios_rd08(bios, bios->bit_offset + 9);
		पूर्ण

		वापस -ENOENT;
	पूर्ण

	वापस -EINVAL;
पूर्ण
