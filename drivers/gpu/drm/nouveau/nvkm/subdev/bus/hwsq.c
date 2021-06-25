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
 */
#समावेश "priv.h"

काष्ठा nvkm_hwsq अणु
	काष्ठा nvkm_subdev *subdev;
	u32 addr;
	u32 data;
	काष्ठा अणु
		u8 data[512];
		u16 size;
	पूर्ण c;
पूर्ण;

अटल व्योम
hwsq_cmd(काष्ठा nvkm_hwsq *hwsq, पूर्णांक size, u8 data[])
अणु
	स_नकल(&hwsq->c.data[hwsq->c.size], data, size * माप(data[0]));
	hwsq->c.size += size;
पूर्ण

पूर्णांक
nvkm_hwsq_init(काष्ठा nvkm_subdev *subdev, काष्ठा nvkm_hwsq **phwsq)
अणु
	काष्ठा nvkm_hwsq *hwsq;

	hwsq = *phwsq = kदो_स्मृति(माप(*hwsq), GFP_KERNEL);
	अगर (hwsq) अणु
		hwsq->subdev = subdev;
		hwsq->addr = ~0;
		hwsq->data = ~0;
		स_रखो(hwsq->c.data, 0x7f, माप(hwsq->c.data));
		hwsq->c.size = 0;
	पूर्ण

	वापस hwsq ? 0 : -ENOMEM;
पूर्ण

पूर्णांक
nvkm_hwsq_fini(काष्ठा nvkm_hwsq **phwsq, bool exec)
अणु
	काष्ठा nvkm_hwsq *hwsq = *phwsq;
	पूर्णांक ret = 0, i;
	अगर (hwsq) अणु
		काष्ठा nvkm_subdev *subdev = hwsq->subdev;
		काष्ठा nvkm_bus *bus = subdev->device->bus;
		hwsq->c.size = (hwsq->c.size + 4) / 4;
		अगर (hwsq->c.size <= bus->func->hwsq_size) अणु
			अगर (exec)
				ret = bus->func->hwsq_exec(bus,
							   (u32 *)hwsq->c.data,
								  hwsq->c.size);
			अगर (ret)
				nvkm_error(subdev, "hwsq exec failed: %d\n", ret);
		पूर्ण अन्यथा अणु
			nvkm_error(subdev, "hwsq ucode too large\n");
			ret = -ENOSPC;
		पूर्ण

		क्रम (i = 0; ret && i < hwsq->c.size; i++)
			nvkm_error(subdev, "\t%08x\n", ((u32 *)hwsq->c.data)[i]);

		*phwsq = शून्य;
		kमुक्त(hwsq);
	पूर्ण
	वापस ret;
पूर्ण

व्योम
nvkm_hwsq_wr32(काष्ठा nvkm_hwsq *hwsq, u32 addr, u32 data)
अणु
	nvkm_debug(hwsq->subdev, "R[%06x] = %08x\n", addr, data);

	अगर (hwsq->data != data) अणु
		अगर ((data & 0xffff0000) != (hwsq->data & 0xffff0000)) अणु
			hwsq_cmd(hwsq, 5, (u8[])अणु 0xe2, data, data >> 8,
						  data >> 16, data >> 24 पूर्ण);
		पूर्ण अन्यथा अणु
			hwsq_cmd(hwsq, 3, (u8[])अणु 0x42, data, data >> 8 पूर्ण);
		पूर्ण
	पूर्ण

	अगर ((addr & 0xffff0000) != (hwsq->addr & 0xffff0000)) अणु
		hwsq_cmd(hwsq, 5, (u8[])अणु 0xe0, addr, addr >> 8,
					  addr >> 16, addr >> 24 पूर्ण);
	पूर्ण अन्यथा अणु
		hwsq_cmd(hwsq, 3, (u8[])अणु 0x40, addr, addr >> 8 पूर्ण);
	पूर्ण

	hwsq->addr = addr;
	hwsq->data = data;
पूर्ण

व्योम
nvkm_hwsq_setf(काष्ठा nvkm_hwsq *hwsq, u8 flag, पूर्णांक data)
अणु
	nvkm_debug(hwsq->subdev, " FLAG[%02x] = %d\n", flag, data);
	flag += 0x80;
	अगर (data >= 0)
		flag += 0x20;
	अगर (data >= 1)
		flag += 0x20;
	hwsq_cmd(hwsq, 1, (u8[])अणु flag पूर्ण);
पूर्ण

व्योम
nvkm_hwsq_रुको(काष्ठा nvkm_hwsq *hwsq, u8 flag, u8 data)
अणु
	nvkm_debug(hwsq->subdev, " WAIT[%02x] = %d\n", flag, data);
	hwsq_cmd(hwsq, 3, (u8[])अणु 0x5f, flag, data पूर्ण);
पूर्ण

व्योम
nvkm_hwsq_रुको_vblank(काष्ठा nvkm_hwsq *hwsq)
अणु
	काष्ठा nvkm_subdev *subdev = hwsq->subdev;
	काष्ठा nvkm_device *device = subdev->device;
	u32 heads, x, y, px = 0;
	पूर्णांक i, head_sync;

	heads = nvkm_rd32(device, 0x610050);
	क्रम (i = 0; i < 2; i++) अणु
		/* Heuristic: sync to head with biggest resolution */
		अगर (heads & (2 << (i << 3))) अणु
			x = nvkm_rd32(device, 0x610b40 + (0x540 * i));
			y = (x & 0xffff0000) >> 16;
			x &= 0x0000ffff;
			अगर ((x * y) > px) अणु
				px = (x * y);
				head_sync = i;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (px == 0) अणु
		nvkm_debug(subdev, "WAIT VBLANK !NO ACTIVE HEAD\n");
		वापस;
	पूर्ण

	nvkm_debug(subdev, "WAIT VBLANK HEAD%d\n", head_sync);
	nvkm_hwsq_रुको(hwsq, head_sync ? 0x3 : 0x1, 0x0);
	nvkm_hwsq_रुको(hwsq, head_sync ? 0x3 : 0x1, 0x1);
पूर्ण

व्योम
nvkm_hwsq_nsec(काष्ठा nvkm_hwsq *hwsq, u32 nsec)
अणु
	u8 shअगरt = 0, usec = nsec / 1000;
	जबतक (usec & ~3) अणु
		usec >>= 2;
		shअगरt++;
	पूर्ण

	nvkm_debug(hwsq->subdev, "    DELAY = %d ns\n", nsec);
	hwsq_cmd(hwsq, 1, (u8[])अणु 0x00 | (shअगरt << 2) | usec पूर्ण);
पूर्ण
