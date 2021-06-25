<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVKM_GR_PRIV_H__
#घोषणा __NVKM_GR_PRIV_H__
#घोषणा nvkm_gr(p) container_of((p), काष्ठा nvkm_gr, engine)
#समावेश <engine/gr.h>
#समावेश <core/क्रमागत.h>
काष्ठा nvkm_fb_tile;
काष्ठा nvkm_fअगरo_chan;

पूर्णांक nvkm_gr_ctor(स्थिर काष्ठा nvkm_gr_func *, काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक,
		 bool enable, काष्ठा nvkm_gr *);

bool nv04_gr_idle(काष्ठा nvkm_gr *);

काष्ठा nvkm_gr_func अणु
	व्योम *(*dtor)(काष्ठा nvkm_gr *);
	पूर्णांक (*oneinit)(काष्ठा nvkm_gr *);
	पूर्णांक (*init)(काष्ठा nvkm_gr *);
	पूर्णांक (*fini)(काष्ठा nvkm_gr *, bool);
	व्योम (*पूर्णांकr)(काष्ठा nvkm_gr *);
	व्योम (*tile)(काष्ठा nvkm_gr *, पूर्णांक region, काष्ठा nvkm_fb_tile *);
	पूर्णांक (*tlb_flush)(काष्ठा nvkm_gr *);
	पूर्णांक (*chan_new)(काष्ठा nvkm_gr *, काष्ठा nvkm_fअगरo_chan *,
			स्थिर काष्ठा nvkm_oclass *, काष्ठा nvkm_object **);
	पूर्णांक (*object_get)(काष्ठा nvkm_gr *, पूर्णांक, काष्ठा nvkm_sclass *);
	/* Returns chipset-specअगरic counts of units packed पूर्णांकo an u64.
	 */
	u64 (*units)(काष्ठा nvkm_gr *);
	bool (*chsw_load)(काष्ठा nvkm_gr *);
	काष्ठा अणु
		पूर्णांक (*छोड़ो)(काष्ठा nvkm_gr *);
		पूर्णांक (*resume)(काष्ठा nvkm_gr *);
		u32 (*inst)(काष्ठा nvkm_gr *);
	पूर्ण ctxsw;
	काष्ठा nvkm_sclass sclass[];
पूर्ण;

बाह्य स्थिर काष्ठा nvkm_bitfield nv04_gr_nsource[];
बाह्य स्थिर काष्ठा nvkm_object_func nv04_gr_object;

बाह्य स्थिर काष्ठा nvkm_bitfield nv10_gr_पूर्णांकr_name[];
बाह्य स्थिर काष्ठा nvkm_bitfield nv10_gr_nstatus[];

बाह्य स्थिर काष्ठा nvkm_क्रमागत nv50_data_error_names[];
#पूर्ण_अगर
