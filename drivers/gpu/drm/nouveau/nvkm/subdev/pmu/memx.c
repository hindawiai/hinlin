<शैली गुरु>
// SPDX-License-Identअगरier: MIT
#अगर_अघोषित __NVKM_PMU_MEMX_H__
#घोषणा __NVKM_PMU_MEMX_H__
#समावेश "priv.h"

काष्ठा nvkm_memx अणु
	काष्ठा nvkm_pmu *pmu;
	u32 base;
	u32 size;
	काष्ठा अणु
		u32 mthd;
		u32 size;
		u32 data[64];
	पूर्ण c;
पूर्ण;

अटल व्योम
memx_out(काष्ठा nvkm_memx *memx)
अणु
	काष्ठा nvkm_device *device = memx->pmu->subdev.device;
	पूर्णांक i;

	अगर (memx->c.mthd) अणु
		nvkm_wr32(device, 0x10a1c4, (memx->c.size << 16) | memx->c.mthd);
		क्रम (i = 0; i < memx->c.size; i++)
			nvkm_wr32(device, 0x10a1c4, memx->c.data[i]);
		memx->c.mthd = 0;
		memx->c.size = 0;
	पूर्ण
पूर्ण

अटल व्योम
memx_cmd(काष्ठा nvkm_memx *memx, u32 mthd, u32 size, u32 data[])
अणु
	अगर ((memx->c.size + size >= ARRAY_SIZE(memx->c.data)) ||
	    (memx->c.mthd && memx->c.mthd != mthd))
		memx_out(memx);
	स_नकल(&memx->c.data[memx->c.size], data, size * माप(data[0]));
	memx->c.size += size;
	memx->c.mthd  = mthd;
पूर्ण

पूर्णांक
nvkm_memx_init(काष्ठा nvkm_pmu *pmu, काष्ठा nvkm_memx **pmemx)
अणु
	काष्ठा nvkm_device *device = pmu->subdev.device;
	काष्ठा nvkm_memx *memx;
	u32 reply[2];
	पूर्णांक ret;

	ret = nvkm_pmu_send(pmu, reply, PROC_MEMX, MEMX_MSG_INFO,
			    MEMX_INFO_DATA, 0);
	अगर (ret)
		वापस ret;

	memx = *pmemx = kzalloc(माप(*memx), GFP_KERNEL);
	अगर (!memx)
		वापस -ENOMEM;
	memx->pmu = pmu;
	memx->base = reply[0];
	memx->size = reply[1];

	/* acquire data segment access */
	करो अणु
		nvkm_wr32(device, 0x10a580, 0x00000003);
	पूर्ण जबतक (nvkm_rd32(device, 0x10a580) != 0x00000003);
	nvkm_wr32(device, 0x10a1c0, 0x01000000 | memx->base);
	वापस 0;
पूर्ण

पूर्णांक
nvkm_memx_fini(काष्ठा nvkm_memx **pmemx, bool exec)
अणु
	काष्ठा nvkm_memx *memx = *pmemx;
	काष्ठा nvkm_pmu *pmu = memx->pmu;
	काष्ठा nvkm_subdev *subdev = &pmu->subdev;
	काष्ठा nvkm_device *device = subdev->device;
	u32 finish, reply[2];

	/* flush the cache... */
	memx_out(memx);

	/* release data segment access */
	finish = nvkm_rd32(device, 0x10a1c0) & 0x00ffffff;
	nvkm_wr32(device, 0x10a580, 0x00000000);

	/* call MEMX process to execute the script, and रुको क्रम reply */
	अगर (exec) अणु
		nvkm_pmu_send(pmu, reply, PROC_MEMX, MEMX_MSG_EXEC,
			      memx->base, finish);
		nvkm_debug(subdev, "Exec took %uns, PMU_IN %08x\n",
			   reply[0], reply[1]);
	पूर्ण

	kमुक्त(memx);
	वापस 0;
पूर्ण

व्योम
nvkm_memx_wr32(काष्ठा nvkm_memx *memx, u32 addr, u32 data)
अणु
	nvkm_debug(&memx->pmu->subdev, "R[%06x] = %08x\n", addr, data);
	memx_cmd(memx, MEMX_WR32, 2, (u32[])अणु addr, data पूर्ण);
पूर्ण

व्योम
nvkm_memx_रुको(काष्ठा nvkm_memx *memx,
		  u32 addr, u32 mask, u32 data, u32 nsec)
अणु
	nvkm_debug(&memx->pmu->subdev, "R[%06x] & %08x == %08x, %d us\n",
		   addr, mask, data, nsec);
	memx_cmd(memx, MEMX_WAIT, 4, (u32[])अणु addr, mask, data, nsec पूर्ण);
	memx_out(memx); /* fuc can't handle multiple */
पूर्ण

व्योम
nvkm_memx_nsec(काष्ठा nvkm_memx *memx, u32 nsec)
अणु
	nvkm_debug(&memx->pmu->subdev, "    DELAY = %d ns\n", nsec);
	memx_cmd(memx, MEMX_DELAY, 1, (u32[])अणु nsec पूर्ण);
	memx_out(memx); /* fuc can't handle multiple */
पूर्ण

व्योम
nvkm_memx_रुको_vblank(काष्ठा nvkm_memx *memx)
अणु
	काष्ठा nvkm_subdev *subdev = &memx->pmu->subdev;
	काष्ठा nvkm_device *device = subdev->device;
	u32 heads, x, y, px = 0;
	पूर्णांक i, head_sync;

	अगर (device->chipset < 0xd0) अणु
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
	पूर्ण

	अगर (px == 0) अणु
		nvkm_debug(subdev, "WAIT VBLANK !NO ACTIVE HEAD\n");
		वापस;
	पूर्ण

	nvkm_debug(subdev, "WAIT VBLANK HEAD%d\n", head_sync);
	memx_cmd(memx, MEMX_VBLANK, 1, (u32[])अणु head_sync पूर्ण);
	memx_out(memx); /* fuc can't handle multiple */
पूर्ण

व्योम
nvkm_memx_train(काष्ठा nvkm_memx *memx)
अणु
	nvkm_debug(&memx->pmu->subdev, "   MEM TRAIN\n");
	memx_cmd(memx, MEMX_TRAIN, 0, शून्य);
पूर्ण

पूर्णांक
nvkm_memx_train_result(काष्ठा nvkm_pmu *pmu, u32 *res, पूर्णांक rsize)
अणु
	काष्ठा nvkm_device *device = pmu->subdev.device;
	u32 reply[2], base, size, i;
	पूर्णांक ret;

	ret = nvkm_pmu_send(pmu, reply, PROC_MEMX, MEMX_MSG_INFO,
			    MEMX_INFO_TRAIN, 0);
	अगर (ret)
		वापस ret;

	base = reply[0];
	size = reply[1] >> 2;
	अगर (size > rsize)
		वापस -ENOMEM;

	/* पढ़ो the packet */
	nvkm_wr32(device, 0x10a1c0, 0x02000000 | base);

	क्रम (i = 0; i < size; i++)
		res[i] = nvkm_rd32(device, 0x10a1c4);

	वापस 0;
पूर्ण

व्योम
nvkm_memx_block(काष्ठा nvkm_memx *memx)
अणु
	nvkm_debug(&memx->pmu->subdev, "   HOST BLOCKED\n");
	memx_cmd(memx, MEMX_ENTER, 0, शून्य);
पूर्ण

व्योम
nvkm_memx_unblock(काष्ठा nvkm_memx *memx)
अणु
	nvkm_debug(&memx->pmu->subdev, "   HOST UNBLOCKED\n");
	memx_cmd(memx, MEMX_LEAVE, 0, शून्य);
पूर्ण
#पूर्ण_अगर
