<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVKM_BUS_HWSQ_H__
#घोषणा __NVKM_BUS_HWSQ_H__
#समावेश <subdev/bus.h>

काष्ठा hwsq अणु
	काष्ठा nvkm_subdev *subdev;
	काष्ठा nvkm_hwsq *hwsq;
	पूर्णांक sequence;
पूर्ण;

काष्ठा hwsq_reg अणु
	पूर्णांक sequence;
	bool क्रमce;
	u32 addr;
	u32 stride; /* in bytes */
	u32 mask;
	u32 data;
पूर्ण;

अटल अंतरभूत काष्ठा hwsq_reg
hwsq_stride(u32 addr, u32 stride, u32 mask)
अणु
	वापस (काष्ठा hwsq_reg) अणु
		.sequence = 0,
		.क्रमce = 0,
		.addr = addr,
		.stride = stride,
		.mask = mask,
		.data = 0xdeadbeef,
	पूर्ण;
पूर्ण

अटल अंतरभूत काष्ठा hwsq_reg
hwsq_reg2(u32 addr1, u32 addr2)
अणु
	वापस (काष्ठा hwsq_reg) अणु
		.sequence = 0,
		.क्रमce = 0,
		.addr = addr1,
		.stride = addr2 - addr1,
		.mask = 0x3,
		.data = 0xdeadbeef,
	पूर्ण;
पूर्ण

अटल अंतरभूत काष्ठा hwsq_reg
hwsq_reg(u32 addr)
अणु
	वापस (काष्ठा hwsq_reg) अणु
		.sequence = 0,
		.क्रमce = 0,
		.addr = addr,
		.stride = 0,
		.mask = 0x1,
		.data = 0xdeadbeef,
	पूर्ण;
पूर्ण

अटल अंतरभूत पूर्णांक
hwsq_init(काष्ठा hwsq *ram, काष्ठा nvkm_subdev *subdev)
अणु
	पूर्णांक ret;

	ret = nvkm_hwsq_init(subdev, &ram->hwsq);
	अगर (ret)
		वापस ret;

	ram->sequence++;
	ram->subdev = subdev;
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक
hwsq_exec(काष्ठा hwsq *ram, bool exec)
अणु
	पूर्णांक ret = 0;
	अगर (ram->subdev) अणु
		ret = nvkm_hwsq_fini(&ram->hwsq, exec);
		ram->subdev = शून्य;
	पूर्ण
	वापस ret;
पूर्ण

अटल अंतरभूत u32
hwsq_rd32(काष्ठा hwsq *ram, काष्ठा hwsq_reg *reg)
अणु
	काष्ठा nvkm_device *device = ram->subdev->device;
	अगर (reg->sequence != ram->sequence)
		reg->data = nvkm_rd32(device, reg->addr);
	वापस reg->data;
पूर्ण

अटल अंतरभूत व्योम
hwsq_wr32(काष्ठा hwsq *ram, काष्ठा hwsq_reg *reg, u32 data)
अणु
	u32 mask, off = 0;

	reg->sequence = ram->sequence;
	reg->data = data;

	क्रम (mask = reg->mask; mask > 0; mask = (mask & ~1) >> 1) अणु
		अगर (mask & 1)
			nvkm_hwsq_wr32(ram->hwsq, reg->addr+off, reg->data);

		off += reg->stride;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम
hwsq_nuke(काष्ठा hwsq *ram, काष्ठा hwsq_reg *reg)
अणु
	reg->क्रमce = true;
पूर्ण

अटल अंतरभूत u32
hwsq_mask(काष्ठा hwsq *ram, काष्ठा hwsq_reg *reg, u32 mask, u32 data)
अणु
	u32 temp = hwsq_rd32(ram, reg);
	अगर (temp != ((temp & ~mask) | data) || reg->क्रमce)
		hwsq_wr32(ram, reg, (temp & ~mask) | data);
	वापस temp;
पूर्ण

अटल अंतरभूत व्योम
hwsq_setf(काष्ठा hwsq *ram, u8 flag, पूर्णांक data)
अणु
	nvkm_hwsq_setf(ram->hwsq, flag, data);
पूर्ण

अटल अंतरभूत व्योम
hwsq_रुको(काष्ठा hwsq *ram, u8 flag, u8 data)
अणु
	nvkm_hwsq_रुको(ram->hwsq, flag, data);
पूर्ण

अटल अंतरभूत व्योम
hwsq_रुको_vblank(काष्ठा hwsq *ram)
अणु
	nvkm_hwsq_रुको_vblank(ram->hwsq);
पूर्ण

अटल अंतरभूत व्योम
hwsq_nsec(काष्ठा hwsq *ram, u32 nsec)
अणु
	nvkm_hwsq_nsec(ram->hwsq, nsec);
पूर्ण
#पूर्ण_अगर
