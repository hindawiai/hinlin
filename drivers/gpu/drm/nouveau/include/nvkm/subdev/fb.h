<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVKM_FB_H__
#घोषणा __NVKM_FB_H__
#समावेश <core/subdev.h>
#समावेश <core/mm.h>

/* memory type/access flags, करो not match hardware values */
#घोषणा NV_MEM_ACCESS_RO  1
#घोषणा NV_MEM_ACCESS_WO  2
#घोषणा NV_MEM_ACCESS_RW (NV_MEM_ACCESS_RO | NV_MEM_ACCESS_WO)
#घोषणा NV_MEM_ACCESS_SYS 4
#घोषणा NV_MEM_ACCESS_VM  8
#घोषणा NV_MEM_ACCESS_NOSNOOP 16

#घोषणा NV_MEM_TARGET_VRAM        0
#घोषणा NV_MEM_TARGET_PCI         1
#घोषणा NV_MEM_TARGET_PCI_NOSNOOP 2
#घोषणा NV_MEM_TARGET_VM          3
#घोषणा NV_MEM_TARGET_GART        4

#घोषणा NVKM_RAM_TYPE_VM 0x7f
#घोषणा NV_MEM_COMP_VM 0x03

काष्ठा nvkm_fb_tile अणु
	काष्ठा nvkm_mm_node *tag;
	u32 addr;
	u32 limit;
	u32 pitch;
	u32 zcomp;
पूर्ण;

काष्ठा nvkm_fb अणु
	स्थिर काष्ठा nvkm_fb_func *func;
	काष्ठा nvkm_subdev subdev;

	काष्ठा nvkm_blob vpr_scrubber;

	काष्ठा nvkm_ram *ram;

	काष्ठा अणु
		काष्ठा mutex mutex; /* protects mm and nvkm_memory::tags */
		काष्ठा nvkm_mm mm;
	पूर्ण tags;

	काष्ठा अणु
		काष्ठा nvkm_fb_tile region[16];
		पूर्णांक regions;
	पूर्ण tile;

	u8 page;

	काष्ठा nvkm_memory *mmu_rd;
	काष्ठा nvkm_memory *mmu_wr;
पूर्ण;

व्योम nvkm_fb_tile_init(काष्ठा nvkm_fb *, पूर्णांक region, u32 addr, u32 size,
		       u32 pitch, u32 flags, काष्ठा nvkm_fb_tile *);
व्योम nvkm_fb_tile_fini(काष्ठा nvkm_fb *, पूर्णांक region, काष्ठा nvkm_fb_tile *);
व्योम nvkm_fb_tile_prog(काष्ठा nvkm_fb *, पूर्णांक region, काष्ठा nvkm_fb_tile *);

पूर्णांक nv04_fb_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_fb **);
पूर्णांक nv10_fb_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_fb **);
पूर्णांक nv1a_fb_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_fb **);
पूर्णांक nv20_fb_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_fb **);
पूर्णांक nv25_fb_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_fb **);
पूर्णांक nv30_fb_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_fb **);
पूर्णांक nv35_fb_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_fb **);
पूर्णांक nv36_fb_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_fb **);
पूर्णांक nv40_fb_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_fb **);
पूर्णांक nv41_fb_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_fb **);
पूर्णांक nv44_fb_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_fb **);
पूर्णांक nv46_fb_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_fb **);
पूर्णांक nv47_fb_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_fb **);
पूर्णांक nv49_fb_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_fb **);
पूर्णांक nv4e_fb_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_fb **);
पूर्णांक nv50_fb_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_fb **);
पूर्णांक g84_fb_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_fb **);
पूर्णांक gt215_fb_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_fb **);
पूर्णांक mcp77_fb_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_fb **);
पूर्णांक mcp89_fb_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_fb **);
पूर्णांक gf100_fb_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_fb **);
पूर्णांक gf108_fb_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_fb **);
पूर्णांक gk104_fb_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_fb **);
पूर्णांक gk110_fb_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_fb **);
पूर्णांक gk20a_fb_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_fb **);
पूर्णांक gm107_fb_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_fb **);
पूर्णांक gm200_fb_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_fb **);
पूर्णांक gm20b_fb_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_fb **);
पूर्णांक gp100_fb_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_fb **);
पूर्णांक gp102_fb_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_fb **);
पूर्णांक gp10b_fb_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_fb **);
पूर्णांक gv100_fb_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_fb **);
पूर्णांक ga100_fb_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_fb **);
पूर्णांक ga102_fb_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_fb **);

#समावेश <subdev/मूलप्रण.स>
#समावेश <subdev/bios/ramcfg.h>

काष्ठा nvkm_ram_data अणु
	काष्ठा list_head head;
	काष्ठा nvbios_ramcfg bios;
	u32 freq;
पूर्ण;

क्रमागत nvkm_ram_type अणु
	NVKM_RAM_TYPE_UNKNOWN = 0,
	NVKM_RAM_TYPE_STOLEN,
	NVKM_RAM_TYPE_SGRAM,
	NVKM_RAM_TYPE_SDRAM,
	NVKM_RAM_TYPE_DDR1,
	NVKM_RAM_TYPE_DDR2,
	NVKM_RAM_TYPE_DDR3,
	NVKM_RAM_TYPE_GDDR2,
	NVKM_RAM_TYPE_GDDR3,
	NVKM_RAM_TYPE_GDDR4,
	NVKM_RAM_TYPE_GDDR5,
	NVKM_RAM_TYPE_GDDR5X,
	NVKM_RAM_TYPE_GDDR6,
	NVKM_RAM_TYPE_HBM2,
पूर्ण;

काष्ठा nvkm_ram अणु
	स्थिर काष्ठा nvkm_ram_func *func;
	काष्ठा nvkm_fb *fb;
	क्रमागत nvkm_ram_type type;
	u64 size;

#घोषणा NVKM_RAM_MM_SHIFT 12
#घोषणा NVKM_RAM_MM_ANY    (NVKM_MM_HEAP_ANY + 0)
#घोषणा NVKM_RAM_MM_NORMAL (NVKM_MM_HEAP_ANY + 1)
#घोषणा NVKM_RAM_MM_NOMAP  (NVKM_MM_HEAP_ANY + 2)
#घोषणा NVKM_RAM_MM_MIXED  (NVKM_MM_HEAP_ANY + 3)
	काष्ठा nvkm_mm vram;
	u64 stolen;
	काष्ठा mutex mutex;

	पूर्णांक ranks;
	पूर्णांक parts;
	पूर्णांक part_mask;

	u32 freq;
	u32 mr[16];
	u32 mr1_nuts;

	काष्ठा nvkm_ram_data *next;
	काष्ठा nvkm_ram_data क्रमmer;
	काष्ठा nvkm_ram_data xition;
	काष्ठा nvkm_ram_data target;
पूर्ण;

पूर्णांक
nvkm_ram_get(काष्ठा nvkm_device *, u8 heap, u8 type, u8 page, u64 size,
	     bool contig, bool back, काष्ठा nvkm_memory **);

काष्ठा nvkm_ram_func अणु
	u64 upper;
	u32 (*probe_fbp)(स्थिर काष्ठा nvkm_ram_func *, काष्ठा nvkm_device *,
			 पूर्णांक fbp, पूर्णांक *pltcs);
	u32 (*probe_fbp_amount)(स्थिर काष्ठा nvkm_ram_func *, u32 fbpao,
				काष्ठा nvkm_device *, पूर्णांक fbp, पूर्णांक *pltcs);
	u32 (*probe_fbpa_amount)(काष्ठा nvkm_device *, पूर्णांक fbpa);
	व्योम *(*dtor)(काष्ठा nvkm_ram *);
	पूर्णांक (*init)(काष्ठा nvkm_ram *);

	पूर्णांक (*calc)(काष्ठा nvkm_ram *, u32 freq);
	पूर्णांक (*prog)(काष्ठा nvkm_ram *);
	व्योम (*tidy)(काष्ठा nvkm_ram *);
पूर्ण;
#पूर्ण_अगर
