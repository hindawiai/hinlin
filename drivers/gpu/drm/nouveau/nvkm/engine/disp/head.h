<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVKM_DISP_HEAD_H__
#घोषणा __NVKM_DISP_HEAD_H__
#समावेश "priv.h"

काष्ठा nvkm_head अणु
	स्थिर काष्ठा nvkm_head_func *func;
	काष्ठा nvkm_disp *disp;
	पूर्णांक id;

	काष्ठा list_head head;

	काष्ठा nvkm_head_state अणु
		u16 htotal;
		u16 hsynce;
		u16 hblanke;
		u16 hblanks;
		u16 vtotal;
		u16 vsynce;
		u16 vblanke;
		u16 vblanks;
		u32 hz;

		/* Prior to GF119, these are set by the OR. */
		काष्ठा अणु
			u8 depth;
		पूर्ण or;
	पूर्ण arm, asy;
पूर्ण;

पूर्णांक nvkm_head_new_(स्थिर काष्ठा nvkm_head_func *, काष्ठा nvkm_disp *, पूर्णांक id);
व्योम nvkm_head_del(काष्ठा nvkm_head **);
पूर्णांक nvkm_head_mthd_scanoutpos(काष्ठा nvkm_object *,
			      काष्ठा nvkm_head *, व्योम *, u32);
काष्ठा nvkm_head *nvkm_head_find(काष्ठा nvkm_disp *, पूर्णांक id);

काष्ठा nvkm_head_func अणु
	व्योम (*state)(काष्ठा nvkm_head *, काष्ठा nvkm_head_state *);
	व्योम (*rgpos)(काष्ठा nvkm_head *, u16 *hline, u16 *vline);
	व्योम (*rgclk)(काष्ठा nvkm_head *, पूर्णांक भाग);
	व्योम (*vblank_get)(काष्ठा nvkm_head *);
	व्योम (*vblank_put)(काष्ठा nvkm_head *);
पूर्ण;

व्योम nv50_head_rgpos(काष्ठा nvkm_head *, u16 *, u16 *);

#घोषणा HEAD_MSG(h,l,f,a...) करो अणु                                              \
	काष्ठा nvkm_head *_h = (h);                                            \
	nvkm_##l(&_h->disp->engine.subdev, "head-%d: "f"\n", _h->id, ##a);     \
पूर्ण जबतक(0)
#घोषणा HEAD_WARN(h,f,a...) HEAD_MSG((h), warn, f, ##a)
#घोषणा HEAD_DBG(h,f,a...) HEAD_MSG((h), debug, f, ##a)

पूर्णांक nv04_head_new(काष्ठा nvkm_disp *, पूर्णांक id);

पूर्णांक nv50_head_cnt(काष्ठा nvkm_disp *, अचिन्हित दीर्घ *);
पूर्णांक nv50_head_new(काष्ठा nvkm_disp *, पूर्णांक id);

पूर्णांक gf119_head_cnt(काष्ठा nvkm_disp *, अचिन्हित दीर्घ *);
पूर्णांक gf119_head_new(काष्ठा nvkm_disp *, पूर्णांक id);
व्योम gf119_head_rgclk(काष्ठा nvkm_head *, पूर्णांक);

पूर्णांक gv100_head_cnt(काष्ठा nvkm_disp *, अचिन्हित दीर्घ *);
पूर्णांक gv100_head_new(काष्ठा nvkm_disp *, पूर्णांक id);
#पूर्ण_अगर
