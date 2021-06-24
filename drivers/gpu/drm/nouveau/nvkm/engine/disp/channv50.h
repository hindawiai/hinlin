<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NV50_DISP_CHAN_H__
#घोषणा __NV50_DISP_CHAN_H__
#घोषणा nv50_disp_chan(p) container_of((p), काष्ठा nv50_disp_chan, object)
#समावेश <core/object.h>
#समावेश "nv50.h"
काष्ठा nv50_disp_root;

काष्ठा nv50_disp_chan अणु
	स्थिर काष्ठा nv50_disp_chan_func *func;
	स्थिर काष्ठा nv50_disp_chan_mthd *mthd;
	काष्ठा nv50_disp *disp;

	काष्ठा अणु
		पूर्णांक ctrl;
		पूर्णांक user;
	पूर्ण chid;
	पूर्णांक head;

	काष्ठा nvkm_object object;

	काष्ठा nvkm_memory *memory;
	u64 push;

	u32 suspend_put;
पूर्ण;

काष्ठा nv50_disp_chan_func अणु
	पूर्णांक (*init)(काष्ठा nv50_disp_chan *);
	व्योम (*fini)(काष्ठा nv50_disp_chan *);
	व्योम (*पूर्णांकr)(काष्ठा nv50_disp_chan *, bool en);
	u64 (*user)(काष्ठा nv50_disp_chan *, u64 *size);
	पूर्णांक (*bind)(काष्ठा nv50_disp_chan *, काष्ठा nvkm_object *, u32 handle);
पूर्ण;

पूर्णांक nv50_disp_chan_new_(स्थिर काष्ठा nv50_disp_chan_func *,
			स्थिर काष्ठा nv50_disp_chan_mthd *,
			काष्ठा nv50_disp *, पूर्णांक ctrl, पूर्णांक user, पूर्णांक head,
			स्थिर काष्ठा nvkm_oclass *, काष्ठा nvkm_object **);
पूर्णांक nv50_disp_dmac_new_(स्थिर काष्ठा nv50_disp_chan_func *,
			स्थिर काष्ठा nv50_disp_chan_mthd *,
			काष्ठा nv50_disp *, पूर्णांक chid, पूर्णांक head, u64 push,
			स्थिर काष्ठा nvkm_oclass *, काष्ठा nvkm_object **);

व्योम nv50_disp_chan_पूर्णांकr(काष्ठा nv50_disp_chan *, bool);
u64 nv50_disp_chan_user(काष्ठा nv50_disp_chan *, u64 *);
बाह्य स्थिर काष्ठा nv50_disp_chan_func nv50_disp_pioc_func;
बाह्य स्थिर काष्ठा nv50_disp_chan_func nv50_disp_dmac_func;
पूर्णांक nv50_disp_dmac_bind(काष्ठा nv50_disp_chan *, काष्ठा nvkm_object *, u32);
बाह्य स्थिर काष्ठा nv50_disp_chan_func nv50_disp_core_func;

व्योम gf119_disp_chan_पूर्णांकr(काष्ठा nv50_disp_chan *, bool);
बाह्य स्थिर काष्ठा nv50_disp_chan_func gf119_disp_pioc_func;
बाह्य स्थिर काष्ठा nv50_disp_chan_func gf119_disp_dmac_func;
व्योम gf119_disp_dmac_fini(काष्ठा nv50_disp_chan *);
पूर्णांक gf119_disp_dmac_bind(काष्ठा nv50_disp_chan *, काष्ठा nvkm_object *, u32);
बाह्य स्थिर काष्ठा nv50_disp_chan_func gf119_disp_core_func;
व्योम gf119_disp_core_fini(काष्ठा nv50_disp_chan *);

बाह्य स्थिर काष्ठा nv50_disp_chan_func gp102_disp_dmac_func;

u64 gv100_disp_chan_user(काष्ठा nv50_disp_chan *, u64 *);
पूर्णांक gv100_disp_dmac_init(काष्ठा nv50_disp_chan *);
व्योम gv100_disp_dmac_fini(काष्ठा nv50_disp_chan *);
पूर्णांक gv100_disp_dmac_bind(काष्ठा nv50_disp_chan *, काष्ठा nvkm_object *, u32);

पूर्णांक nv50_disp_curs_new_(स्थिर काष्ठा nv50_disp_chan_func *,
			काष्ठा nv50_disp *, पूर्णांक ctrl, पूर्णांक user,
			स्थिर काष्ठा nvkm_oclass *, व्योम *argv, u32 argc,
			काष्ठा nvkm_object **);
पूर्णांक nv50_disp_oimm_new_(स्थिर काष्ठा nv50_disp_chan_func *,
			काष्ठा nv50_disp *, पूर्णांक ctrl, पूर्णांक user,
			स्थिर काष्ठा nvkm_oclass *, व्योम *argv, u32 argc,
			काष्ठा nvkm_object **);
पूर्णांक nv50_disp_base_new_(स्थिर काष्ठा nv50_disp_chan_func *,
			स्थिर काष्ठा nv50_disp_chan_mthd *,
			काष्ठा nv50_disp *, पूर्णांक chid,
			स्थिर काष्ठा nvkm_oclass *, व्योम *argv, u32 argc,
			काष्ठा nvkm_object **);
पूर्णांक nv50_disp_core_new_(स्थिर काष्ठा nv50_disp_chan_func *,
			स्थिर काष्ठा nv50_disp_chan_mthd *,
			काष्ठा nv50_disp *, पूर्णांक chid,
			स्थिर काष्ठा nvkm_oclass *oclass, व्योम *argv, u32 argc,
			काष्ठा nvkm_object **);
पूर्णांक nv50_disp_ovly_new_(स्थिर काष्ठा nv50_disp_chan_func *,
			स्थिर काष्ठा nv50_disp_chan_mthd *,
			काष्ठा nv50_disp *, पूर्णांक chid,
			स्थिर काष्ठा nvkm_oclass *, व्योम *argv, u32 argc,
			काष्ठा nvkm_object **);

पूर्णांक nv50_disp_curs_new(स्थिर काष्ठा nvkm_oclass *, व्योम *, u32,
		       काष्ठा nv50_disp *, काष्ठा nvkm_object **);
पूर्णांक nv50_disp_oimm_new(स्थिर काष्ठा nvkm_oclass *, व्योम *, u32,
		       काष्ठा nv50_disp *, काष्ठा nvkm_object **);
पूर्णांक nv50_disp_base_new(स्थिर काष्ठा nvkm_oclass *, व्योम *, u32,
		       काष्ठा nv50_disp *, काष्ठा nvkm_object **);
पूर्णांक nv50_disp_core_new(स्थिर काष्ठा nvkm_oclass *, व्योम *, u32,
		       काष्ठा nv50_disp *, काष्ठा nvkm_object **);
पूर्णांक nv50_disp_ovly_new(स्थिर काष्ठा nvkm_oclass *, व्योम *, u32,
		       काष्ठा nv50_disp *, काष्ठा nvkm_object **);

पूर्णांक g84_disp_base_new(स्थिर काष्ठा nvkm_oclass *, व्योम *, u32,
		      काष्ठा nv50_disp *, काष्ठा nvkm_object **);
पूर्णांक g84_disp_core_new(स्थिर काष्ठा nvkm_oclass *, व्योम *, u32,
		      काष्ठा nv50_disp *, काष्ठा nvkm_object **);
पूर्णांक g84_disp_ovly_new(स्थिर काष्ठा nvkm_oclass *, व्योम *, u32,
		      काष्ठा nv50_disp *, काष्ठा nvkm_object **);

पूर्णांक g94_disp_core_new(स्थिर काष्ठा nvkm_oclass *, व्योम *, u32,
		      काष्ठा nv50_disp *, काष्ठा nvkm_object **);

पूर्णांक gt200_disp_ovly_new(स्थिर काष्ठा nvkm_oclass *, व्योम *, u32,
			काष्ठा nv50_disp *, काष्ठा nvkm_object **);

पूर्णांक gf119_disp_curs_new(स्थिर काष्ठा nvkm_oclass *, व्योम *, u32,
			काष्ठा nv50_disp *, काष्ठा nvkm_object **);
पूर्णांक gf119_disp_oimm_new(स्थिर काष्ठा nvkm_oclass *, व्योम *, u32,
			काष्ठा nv50_disp *, काष्ठा nvkm_object **);
पूर्णांक gf119_disp_base_new(स्थिर काष्ठा nvkm_oclass *, व्योम *, u32,
			काष्ठा nv50_disp *, काष्ठा nvkm_object **);
पूर्णांक gf119_disp_core_new(स्थिर काष्ठा nvkm_oclass *, व्योम *, u32,
			काष्ठा nv50_disp *, काष्ठा nvkm_object **);
पूर्णांक gf119_disp_ovly_new(स्थिर काष्ठा nvkm_oclass *, व्योम *, u32,
			काष्ठा nv50_disp *, काष्ठा nvkm_object **);

पूर्णांक gk104_disp_core_new(स्थिर काष्ठा nvkm_oclass *, व्योम *, u32,
			काष्ठा nv50_disp *, काष्ठा nvkm_object **);
पूर्णांक gk104_disp_ovly_new(स्थिर काष्ठा nvkm_oclass *, व्योम *, u32,
			काष्ठा nv50_disp *, काष्ठा nvkm_object **);

पूर्णांक gp102_disp_curs_new(स्थिर काष्ठा nvkm_oclass *, व्योम *, u32,
			काष्ठा nv50_disp *, काष्ठा nvkm_object **);
पूर्णांक gp102_disp_oimm_new(स्थिर काष्ठा nvkm_oclass *, व्योम *, u32,
			काष्ठा nv50_disp *, काष्ठा nvkm_object **);
पूर्णांक gp102_disp_base_new(स्थिर काष्ठा nvkm_oclass *, व्योम *, u32,
			काष्ठा nv50_disp *, काष्ठा nvkm_object **);
पूर्णांक gp102_disp_core_new(स्थिर काष्ठा nvkm_oclass *, व्योम *, u32,
			काष्ठा nv50_disp *, काष्ठा nvkm_object **);
पूर्णांक gp102_disp_ovly_new(स्थिर काष्ठा nvkm_oclass *, व्योम *, u32,
			काष्ठा nv50_disp *, काष्ठा nvkm_object **);

पूर्णांक gv100_disp_curs_new(स्थिर काष्ठा nvkm_oclass *, व्योम *, u32,
			काष्ठा nv50_disp *, काष्ठा nvkm_object **);
पूर्णांक gv100_disp_wimm_new(स्थिर काष्ठा nvkm_oclass *, व्योम *, u32,
			काष्ठा nv50_disp *, काष्ठा nvkm_object **);
पूर्णांक gv100_disp_core_new(स्थिर काष्ठा nvkm_oclass *, व्योम *, u32,
			काष्ठा nv50_disp *, काष्ठा nvkm_object **);
पूर्णांक gv100_disp_wndw_new(स्थिर काष्ठा nvkm_oclass *, व्योम *, u32,
			काष्ठा nv50_disp *, काष्ठा nvkm_object **);

काष्ठा nv50_disp_mthd_list अणु
	u32 mthd;
	u32 addr;
	काष्ठा अणु
		u32 mthd;
		u32 addr;
		स्थिर अक्षर *name;
	पूर्ण data[];
पूर्ण;

काष्ठा nv50_disp_chan_mthd अणु
	स्थिर अक्षर *name;
	u32 addr;
	s32 prev;
	काष्ठा अणु
		स्थिर अक्षर *name;
		पूर्णांक nr;
		स्थिर काष्ठा nv50_disp_mthd_list *mthd;
	पूर्ण data[];
पूर्ण;

व्योम nv50_disp_chan_mthd(काष्ठा nv50_disp_chan *, पूर्णांक debug);

बाह्य स्थिर काष्ठा nv50_disp_mthd_list nv50_disp_core_mthd_base;
बाह्य स्थिर काष्ठा nv50_disp_mthd_list nv50_disp_core_mthd_sor;
बाह्य स्थिर काष्ठा nv50_disp_mthd_list nv50_disp_core_mthd_pior;
बाह्य स्थिर काष्ठा nv50_disp_mthd_list nv50_disp_base_mthd_image;

बाह्य स्थिर काष्ठा nv50_disp_chan_mthd g84_disp_core_mthd;
बाह्य स्थिर काष्ठा nv50_disp_mthd_list g84_disp_core_mthd_dac;
बाह्य स्थिर काष्ठा nv50_disp_mthd_list g84_disp_core_mthd_head;

बाह्य स्थिर काष्ठा nv50_disp_chan_mthd g94_disp_core_mthd;

बाह्य स्थिर काष्ठा nv50_disp_mthd_list gf119_disp_core_mthd_base;
बाह्य स्थिर काष्ठा nv50_disp_mthd_list gf119_disp_core_mthd_dac;
बाह्य स्थिर काष्ठा nv50_disp_mthd_list gf119_disp_core_mthd_sor;
बाह्य स्थिर काष्ठा nv50_disp_mthd_list gf119_disp_core_mthd_pior;
बाह्य स्थिर काष्ठा nv50_disp_chan_mthd gf119_disp_base_mthd;

बाह्य स्थिर काष्ठा nv50_disp_chan_mthd gk104_disp_core_mthd;
बाह्य स्थिर काष्ठा nv50_disp_chan_mthd gk104_disp_ovly_mthd;
#पूर्ण_अगर
