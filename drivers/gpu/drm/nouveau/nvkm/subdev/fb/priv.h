<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVKM_FB_PRIV_H__
#घोषणा __NVKM_FB_PRIV_H__
#घोषणा nvkm_fb(p) container_of((p), काष्ठा nvkm_fb, subdev)
#समावेश <subdev/fb.h>
#समावेश <subdev/therm.h>
काष्ठा nvkm_bios;

काष्ठा nvkm_fb_func अणु
	व्योम *(*dtor)(काष्ठा nvkm_fb *);
	u32 (*tags)(काष्ठा nvkm_fb *);
	पूर्णांक (*oneinit)(काष्ठा nvkm_fb *);
	व्योम (*init)(काष्ठा nvkm_fb *);
	व्योम (*init_remapper)(काष्ठा nvkm_fb *);
	पूर्णांक (*init_page)(काष्ठा nvkm_fb *);
	व्योम (*init_unkn)(काष्ठा nvkm_fb *);
	व्योम (*पूर्णांकr)(काष्ठा nvkm_fb *);

	काष्ठा अणु
		bool (*scrub_required)(काष्ठा nvkm_fb *);
		पूर्णांक (*scrub)(काष्ठा nvkm_fb *);
	पूर्ण vpr;

	काष्ठा अणु
		पूर्णांक regions;
		व्योम (*init)(काष्ठा nvkm_fb *, पूर्णांक i, u32 addr, u32 size,
			     u32 pitch, u32 flags, काष्ठा nvkm_fb_tile *);
		व्योम (*comp)(काष्ठा nvkm_fb *, पूर्णांक i, u32 size, u32 flags,
			     काष्ठा nvkm_fb_tile *);
		व्योम (*fini)(काष्ठा nvkm_fb *, पूर्णांक i, काष्ठा nvkm_fb_tile *);
		व्योम (*prog)(काष्ठा nvkm_fb *, पूर्णांक i, काष्ठा nvkm_fb_tile *);
	पूर्ण tile;

	पूर्णांक (*ram_new)(काष्ठा nvkm_fb *, काष्ठा nvkm_ram **);

	u8 शेष_bigpage;
	स्थिर काष्ठा nvkm_therm_clkgate_pack *clkgate_pack;
पूर्ण;

व्योम nvkm_fb_ctor(स्थिर काष्ठा nvkm_fb_func *, काष्ठा nvkm_device *device,
		  क्रमागत nvkm_subdev_type type, पूर्णांक inst, काष्ठा nvkm_fb *);
पूर्णांक nvkm_fb_new_(स्थिर काष्ठा nvkm_fb_func *, काष्ठा nvkm_device *device,
		 क्रमागत nvkm_subdev_type type, पूर्णांक inst, काष्ठा nvkm_fb **);
पूर्णांक nvkm_fb_bios_memtype(काष्ठा nvkm_bios *);

व्योम nv10_fb_tile_init(काष्ठा nvkm_fb *, पूर्णांक i, u32 addr, u32 size,
		       u32 pitch, u32 flags, काष्ठा nvkm_fb_tile *);
व्योम nv10_fb_tile_fini(काष्ठा nvkm_fb *, पूर्णांक i, काष्ठा nvkm_fb_tile *);
व्योम nv10_fb_tile_prog(काष्ठा nvkm_fb *, पूर्णांक, काष्ठा nvkm_fb_tile *);

u32 nv20_fb_tags(काष्ठा nvkm_fb *);
व्योम nv20_fb_tile_init(काष्ठा nvkm_fb *, पूर्णांक i, u32 addr, u32 size,
		       u32 pitch, u32 flags, काष्ठा nvkm_fb_tile *);
व्योम nv20_fb_tile_fini(काष्ठा nvkm_fb *, पूर्णांक i, काष्ठा nvkm_fb_tile *);
व्योम nv20_fb_tile_prog(काष्ठा nvkm_fb *, पूर्णांक, काष्ठा nvkm_fb_tile *);

व्योम nv30_fb_init(काष्ठा nvkm_fb *);
व्योम nv30_fb_tile_init(काष्ठा nvkm_fb *, पूर्णांक i, u32 addr, u32 size,
		       u32 pitch, u32 flags, काष्ठा nvkm_fb_tile *);

व्योम nv40_fb_tile_comp(काष्ठा nvkm_fb *, पूर्णांक i, u32 size, u32 flags,
		       काष्ठा nvkm_fb_tile *);

व्योम nv41_fb_init(काष्ठा nvkm_fb *);
व्योम nv41_fb_tile_prog(काष्ठा nvkm_fb *, पूर्णांक, काष्ठा nvkm_fb_tile *);

व्योम nv44_fb_init(काष्ठा nvkm_fb *);
व्योम nv44_fb_tile_prog(काष्ठा nvkm_fb *, पूर्णांक, काष्ठा nvkm_fb_tile *);

व्योम nv46_fb_tile_init(काष्ठा nvkm_fb *, पूर्णांक i, u32 addr, u32 size,
		       u32 pitch, u32 flags, काष्ठा nvkm_fb_tile *);

पूर्णांक gf100_fb_oneinit(काष्ठा nvkm_fb *);
पूर्णांक gf100_fb_init_page(काष्ठा nvkm_fb *);

पूर्णांक gm200_fb_init_page(काष्ठा nvkm_fb *);

व्योम gp100_fb_init_remapper(काष्ठा nvkm_fb *);
व्योम gp100_fb_init_unkn(काष्ठा nvkm_fb *);

पूर्णांक gp102_fb_new_(स्थिर काष्ठा nvkm_fb_func *, काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक,
		  काष्ठा nvkm_fb **);
bool gp102_fb_vpr_scrub_required(काष्ठा nvkm_fb *);
पूर्णांक gp102_fb_vpr_scrub(काष्ठा nvkm_fb *);

पूर्णांक gv100_fb_init_page(काष्ठा nvkm_fb *);
#पूर्ण_अगर
