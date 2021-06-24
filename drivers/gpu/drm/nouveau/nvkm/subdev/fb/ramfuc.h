<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVKM_FBRAM_FUC_H__
#घोषणा __NVKM_FBRAM_FUC_H__
#समावेश <subdev/fb.h>
#समावेश <subdev/pmu.h>

काष्ठा ramfuc अणु
	काष्ठा nvkm_memx *memx;
	काष्ठा nvkm_fb *fb;
	पूर्णांक sequence;
पूर्ण;

काष्ठा ramfuc_reg अणु
	पूर्णांक sequence;
	bool क्रमce;
	u32 addr;
	u32 stride; /* in bytes */
	u32 mask;
	u32 data;
पूर्ण;

अटल अंतरभूत काष्ठा ramfuc_reg
ramfuc_stride(u32 addr, u32 stride, u32 mask)
अणु
	वापस (काष्ठा ramfuc_reg) अणु
		.sequence = 0,
		.addr = addr,
		.stride = stride,
		.mask = mask,
		.data = 0xdeadbeef,
	पूर्ण;
पूर्ण

अटल अंतरभूत काष्ठा ramfuc_reg
ramfuc_reg2(u32 addr1, u32 addr2)
अणु
	वापस (काष्ठा ramfuc_reg) अणु
		.sequence = 0,
		.addr = addr1,
		.stride = addr2 - addr1,
		.mask = 0x3,
		.data = 0xdeadbeef,
	पूर्ण;
पूर्ण

अटल noअंतरभूत काष्ठा ramfuc_reg
ramfuc_reg(u32 addr)
अणु
	वापस (काष्ठा ramfuc_reg) अणु
		.sequence = 0,
		.addr = addr,
		.stride = 0,
		.mask = 0x1,
		.data = 0xdeadbeef,
	पूर्ण;
पूर्ण

अटल अंतरभूत पूर्णांक
ramfuc_init(काष्ठा ramfuc *ram, काष्ठा nvkm_fb *fb)
अणु
	पूर्णांक ret = nvkm_memx_init(fb->subdev.device->pmu, &ram->memx);
	अगर (ret)
		वापस ret;

	ram->sequence++;
	ram->fb = fb;
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक
ramfuc_exec(काष्ठा ramfuc *ram, bool exec)
अणु
	पूर्णांक ret = 0;
	अगर (ram->fb) अणु
		ret = nvkm_memx_fini(&ram->memx, exec);
		ram->fb = शून्य;
	पूर्ण
	वापस ret;
पूर्ण

अटल अंतरभूत u32
ramfuc_rd32(काष्ठा ramfuc *ram, काष्ठा ramfuc_reg *reg)
अणु
	काष्ठा nvkm_device *device = ram->fb->subdev.device;
	अगर (reg->sequence != ram->sequence)
		reg->data = nvkm_rd32(device, reg->addr);
	वापस reg->data;
पूर्ण

अटल अंतरभूत व्योम
ramfuc_wr32(काष्ठा ramfuc *ram, काष्ठा ramfuc_reg *reg, u32 data)
अणु
	अचिन्हित पूर्णांक mask, off = 0;

	reg->sequence = ram->sequence;
	reg->data = data;

	क्रम (mask = reg->mask; mask > 0; mask = (mask & ~1) >> 1) अणु
		अगर (mask & 1)
			nvkm_memx_wr32(ram->memx, reg->addr+off, reg->data);
		off += reg->stride;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम
ramfuc_nuke(काष्ठा ramfuc *ram, काष्ठा ramfuc_reg *reg)
अणु
	reg->क्रमce = true;
पूर्ण

अटल अंतरभूत u32
ramfuc_mask(काष्ठा ramfuc *ram, काष्ठा ramfuc_reg *reg, u32 mask, u32 data)
अणु
	u32 temp = ramfuc_rd32(ram, reg);
	अगर (temp != ((temp & ~mask) | data) || reg->क्रमce) अणु
		ramfuc_wr32(ram, reg, (temp & ~mask) | data);
		reg->क्रमce = false;
	पूर्ण
	वापस temp;
पूर्ण

अटल अंतरभूत व्योम
ramfuc_रुको(काष्ठा ramfuc *ram, u32 addr, u32 mask, u32 data, u32 nsec)
अणु
	nvkm_memx_रुको(ram->memx, addr, mask, data, nsec);
पूर्ण

अटल अंतरभूत व्योम
ramfuc_nsec(काष्ठा ramfuc *ram, u32 nsec)
अणु
	nvkm_memx_nsec(ram->memx, nsec);
पूर्ण

अटल अंतरभूत व्योम
ramfuc_रुको_vblank(काष्ठा ramfuc *ram)
अणु
	nvkm_memx_रुको_vblank(ram->memx);
पूर्ण

अटल अंतरभूत व्योम
ramfuc_train(काष्ठा ramfuc *ram)
अणु
	nvkm_memx_train(ram->memx);
पूर्ण

अटल अंतरभूत पूर्णांक
ramfuc_train_result(काष्ठा nvkm_fb *fb, u32 *result, u32 rsize)
अणु
	वापस nvkm_memx_train_result(fb->subdev.device->pmu, result, rsize);
पूर्ण

अटल अंतरभूत व्योम
ramfuc_block(काष्ठा ramfuc *ram)
अणु
	nvkm_memx_block(ram->memx);
पूर्ण

अटल अंतरभूत व्योम
ramfuc_unblock(काष्ठा ramfuc *ram)
अणु
	nvkm_memx_unblock(ram->memx);
पूर्ण

#घोषणा ram_init(s,p)        ramfuc_init(&(s)->base, (p))
#घोषणा ram_exec(s,e)        ramfuc_exec(&(s)->base, (e))
#घोषणा ram_have(s,r)        ((s)->r_##r.addr != 0x000000)
#घोषणा ram_rd32(s,r)        ramfuc_rd32(&(s)->base, &(s)->r_##r)
#घोषणा ram_wr32(s,r,d)      ramfuc_wr32(&(s)->base, &(s)->r_##r, (d))
#घोषणा ram_nuke(s,r)        ramfuc_nuke(&(s)->base, &(s)->r_##r)
#घोषणा ram_mask(s,r,m,d)    ramfuc_mask(&(s)->base, &(s)->r_##r, (m), (d))
#घोषणा ram_रुको(s,r,m,d,n)  ramfuc_रुको(&(s)->base, (r), (m), (d), (n))
#घोषणा ram_nsec(s,n)        ramfuc_nsec(&(s)->base, (n))
#घोषणा ram_रुको_vblank(s)   ramfuc_रुको_vblank(&(s)->base)
#घोषणा ram_train(s)         ramfuc_train(&(s)->base)
#घोषणा ram_train_result(s,r,l) ramfuc_train_result((s), (r), (l))
#घोषणा ram_block(s)         ramfuc_block(&(s)->base)
#घोषणा ram_unblock(s)       ramfuc_unblock(&(s)->base)
#पूर्ण_अगर
