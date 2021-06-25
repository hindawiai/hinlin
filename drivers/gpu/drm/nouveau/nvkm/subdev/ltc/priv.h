<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVKM_LTC_PRIV_H__
#घोषणा __NVKM_LTC_PRIV_H__
#घोषणा nvkm_ltc(p) container_of((p), काष्ठा nvkm_ltc, subdev)
#समावेश <subdev/ltc.h>
#समावेश <core/क्रमागत.h>

पूर्णांक nvkm_ltc_new_(स्थिर काष्ठा nvkm_ltc_func *, काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक,
		  काष्ठा nvkm_ltc **);

काष्ठा nvkm_ltc_func अणु
	पूर्णांक  (*oneinit)(काष्ठा nvkm_ltc *);
	व्योम (*init)(काष्ठा nvkm_ltc *);
	व्योम (*पूर्णांकr)(काष्ठा nvkm_ltc *);

	व्योम (*cbc_clear)(काष्ठा nvkm_ltc *, u32 start, u32 limit);
	व्योम (*cbc_रुको)(काष्ठा nvkm_ltc *);

	पूर्णांक zbc;
	व्योम (*zbc_clear_color)(काष्ठा nvkm_ltc *, पूर्णांक, स्थिर u32[4]);
	व्योम (*zbc_clear_depth)(काष्ठा nvkm_ltc *, पूर्णांक, स्थिर u32);
	व्योम (*zbc_clear_stencil)(काष्ठा nvkm_ltc *, पूर्णांक, स्थिर u32);

	व्योम (*invalidate)(काष्ठा nvkm_ltc *);
	व्योम (*flush)(काष्ठा nvkm_ltc *);
पूर्ण;

पूर्णांक gf100_ltc_oneinit(काष्ठा nvkm_ltc *);
पूर्णांक gf100_ltc_oneinit_tag_ram(काष्ठा nvkm_ltc *);
व्योम gf100_ltc_पूर्णांकr(काष्ठा nvkm_ltc *);
व्योम gf100_ltc_cbc_clear(काष्ठा nvkm_ltc *, u32, u32);
व्योम gf100_ltc_cbc_रुको(काष्ठा nvkm_ltc *);
व्योम gf100_ltc_zbc_clear_color(काष्ठा nvkm_ltc *, पूर्णांक, स्थिर u32[4]);
व्योम gf100_ltc_zbc_clear_depth(काष्ठा nvkm_ltc *, पूर्णांक, स्थिर u32);
व्योम gf100_ltc_invalidate(काष्ठा nvkm_ltc *);
व्योम gf100_ltc_flush(काष्ठा nvkm_ltc *);
बाह्य स्थिर काष्ठा nvkm_bitfield gf100_ltc_lts_पूर्णांकr_name[];

व्योम gm107_ltc_पूर्णांकr(काष्ठा nvkm_ltc *);
व्योम gm107_ltc_पूर्णांकr_lts(काष्ठा nvkm_ltc *, पूर्णांक ltc, पूर्णांक lts);
व्योम gm107_ltc_cbc_clear(काष्ठा nvkm_ltc *, u32, u32);
व्योम gm107_ltc_cbc_रुको(काष्ठा nvkm_ltc *);
व्योम gm107_ltc_zbc_clear_color(काष्ठा nvkm_ltc *, पूर्णांक, स्थिर u32[4]);
व्योम gm107_ltc_zbc_clear_depth(काष्ठा nvkm_ltc *, पूर्णांक, स्थिर u32);

पूर्णांक gp100_ltc_oneinit(काष्ठा nvkm_ltc *);
व्योम gp100_ltc_init(काष्ठा nvkm_ltc *);
व्योम gp100_ltc_पूर्णांकr(काष्ठा nvkm_ltc *);

व्योम gp102_ltc_zbc_clear_stencil(काष्ठा nvkm_ltc *, पूर्णांक, स्थिर u32);
#पूर्ण_अगर
