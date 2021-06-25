<शैली गुरु>
#अगर_अघोषित __NV50_KMS_WNDW_H__
#घोषणा __NV50_KMS_WNDW_H__
#घोषणा nv50_wndw(p) container_of((p), काष्ठा nv50_wndw, plane)
#समावेश "disp.h"
#समावेश "atom.h"
#समावेश "lut.h"

#समावेश <nvअगर/notअगरy.h>

काष्ठा nv50_wndw_ctxdma अणु
	काष्ठा list_head head;
	काष्ठा nvअगर_object object;
पूर्ण;

काष्ठा nv50_wndw अणु
	स्थिर काष्ठा nv50_wndw_func *func;
	स्थिर काष्ठा nv50_wimm_func *immd;
	पूर्णांक id;
	काष्ठा nv50_disp_पूर्णांकerlock पूर्णांकerlock;

	काष्ठा अणु
		काष्ठा nvअगर_object *parent;
		काष्ठा list_head list;
	पूर्ण ctxdma;

	काष्ठा drm_plane plane;

	काष्ठा nv50_lut ilut;

	काष्ठा nv50_dmac wndw;
	काष्ठा nv50_dmac wimm;

	काष्ठा nvअगर_notअगरy notअगरy;
	u16 ntfy;
	u16 sema;
	u32 data;
पूर्ण;

पूर्णांक nv50_wndw_new_(स्थिर काष्ठा nv50_wndw_func *, काष्ठा drm_device *,
		   क्रमागत drm_plane_type, स्थिर अक्षर *name, पूर्णांक index,
		   स्थिर u32 *क्रमmat, क्रमागत nv50_disp_पूर्णांकerlock_type,
		   u32 पूर्णांकerlock_data, u32 heads, काष्ठा nv50_wndw **);
व्योम nv50_wndw_init(काष्ठा nv50_wndw *);
व्योम nv50_wndw_fini(काष्ठा nv50_wndw *);
व्योम nv50_wndw_flush_set(काष्ठा nv50_wndw *, u32 *पूर्णांकerlock,
			 काष्ठा nv50_wndw_atom *);
व्योम nv50_wndw_flush_clr(काष्ठा nv50_wndw *, u32 *पूर्णांकerlock, bool flush,
			 काष्ठा nv50_wndw_atom *);
व्योम nv50_wndw_ntfy_enable(काष्ठा nv50_wndw *, काष्ठा nv50_wndw_atom *);
पूर्णांक nv50_wndw_रुको_armed(काष्ठा nv50_wndw *, काष्ठा nv50_wndw_atom *);

काष्ठा nv50_wndw_func अणु
	पूर्णांक (*acquire)(काष्ठा nv50_wndw *, काष्ठा nv50_wndw_atom *asyw,
		       काष्ठा nv50_head_atom *asyh);
	व्योम (*release)(काष्ठा nv50_wndw *, काष्ठा nv50_wndw_atom *asyw,
			काष्ठा nv50_head_atom *asyh);
	व्योम (*prepare)(काष्ठा nv50_wndw *, काष्ठा nv50_head_atom *asyh,
			काष्ठा nv50_wndw_atom *asyw);

	पूर्णांक (*sema_set)(काष्ठा nv50_wndw *, काष्ठा nv50_wndw_atom *);
	पूर्णांक (*sema_clr)(काष्ठा nv50_wndw *);
	व्योम (*ntfy_reset)(काष्ठा nouveau_bo *, u32 offset);
	पूर्णांक (*ntfy_set)(काष्ठा nv50_wndw *, काष्ठा nv50_wndw_atom *);
	पूर्णांक (*ntfy_clr)(काष्ठा nv50_wndw *);
	पूर्णांक (*ntfy_रुको_begun)(काष्ठा nouveau_bo *, u32 offset,
			       काष्ठा nvअगर_device *);
	bool (*ilut)(काष्ठा nv50_wndw *, काष्ठा nv50_wndw_atom *, पूर्णांक);
	व्योम (*csc)(काष्ठा nv50_wndw *, काष्ठा nv50_wndw_atom *,
		    स्थिर काष्ठा drm_color_cपंचांग *);
	पूर्णांक (*csc_set)(काष्ठा nv50_wndw *, काष्ठा nv50_wndw_atom *);
	पूर्णांक (*csc_clr)(काष्ठा nv50_wndw *);
	bool ilut_identity;
	पूर्णांक  ilut_size;
	bool olut_core;
	पूर्णांक (*xlut_set)(काष्ठा nv50_wndw *, काष्ठा nv50_wndw_atom *);
	पूर्णांक (*xlut_clr)(काष्ठा nv50_wndw *);
	पूर्णांक (*image_set)(काष्ठा nv50_wndw *, काष्ठा nv50_wndw_atom *);
	पूर्णांक (*image_clr)(काष्ठा nv50_wndw *);
	पूर्णांक (*scale_set)(काष्ठा nv50_wndw *, काष्ठा nv50_wndw_atom *);
	पूर्णांक (*blend_set)(काष्ठा nv50_wndw *, काष्ठा nv50_wndw_atom *);

	पूर्णांक (*update)(काष्ठा nv50_wndw *, u32 *पूर्णांकerlock);
पूर्ण;

बाह्य स्थिर काष्ठा drm_plane_funcs nv50_wndw;

व्योम base507c_ntfy_reset(काष्ठा nouveau_bo *, u32);
पूर्णांक base507c_ntfy_set(काष्ठा nv50_wndw *, काष्ठा nv50_wndw_atom *);
पूर्णांक base507c_ntfy_clr(काष्ठा nv50_wndw *);
पूर्णांक base507c_ntfy_रुको_begun(काष्ठा nouveau_bo *, u32, काष्ठा nvअगर_device *);
पूर्णांक base507c_image_clr(काष्ठा nv50_wndw *);
पूर्णांक base507c_update(काष्ठा nv50_wndw *, u32 *);

व्योम base907c_csc(काष्ठा nv50_wndw *, काष्ठा nv50_wndw_atom *,
		  स्थिर काष्ठा drm_color_cपंचांग *);

काष्ठा nv50_wimm_func अणु
	पूर्णांक (*poपूर्णांक)(काष्ठा nv50_wndw *, काष्ठा nv50_wndw_atom *);

	पूर्णांक (*update)(काष्ठा nv50_wndw *, u32 *पूर्णांकerlock);
पूर्ण;

बाह्य स्थिर काष्ठा nv50_wimm_func curs507a;
bool curs507a_space(काष्ठा nv50_wndw *);

अटल अंतरभूत __must_check पूर्णांक
nvअगर_chan_रुको(काष्ठा nv50_dmac *dmac, u32 size)
अणु
	काष्ठा nv50_wndw *wndw = container_of(dmac, typeof(*wndw), wimm);
	वापस curs507a_space(wndw) ? 0 : -ETIMEDOUT;
पूर्ण

पूर्णांक wndwc37e_new(काष्ठा nouveau_drm *, क्रमागत drm_plane_type, पूर्णांक, s32,
		 काष्ठा nv50_wndw **);
पूर्णांक wndwc37e_new_(स्थिर काष्ठा nv50_wndw_func *, काष्ठा nouveau_drm *,
		  क्रमागत drm_plane_type type, पूर्णांक index, s32 oclass, u32 heads,
		  काष्ठा nv50_wndw **);
पूर्णांक wndwc37e_acquire(काष्ठा nv50_wndw *, काष्ठा nv50_wndw_atom *,
		     काष्ठा nv50_head_atom *);
व्योम wndwc37e_release(काष्ठा nv50_wndw *, काष्ठा nv50_wndw_atom *,
		      काष्ठा nv50_head_atom *);
पूर्णांक wndwc37e_sema_set(काष्ठा nv50_wndw *, काष्ठा nv50_wndw_atom *);
पूर्णांक wndwc37e_sema_clr(काष्ठा nv50_wndw *);
पूर्णांक wndwc37e_ntfy_set(काष्ठा nv50_wndw *, काष्ठा nv50_wndw_atom *);
पूर्णांक wndwc37e_ntfy_clr(काष्ठा nv50_wndw *);
पूर्णांक wndwc37e_image_clr(काष्ठा nv50_wndw *);
पूर्णांक wndwc37e_blend_set(काष्ठा nv50_wndw *, काष्ठा nv50_wndw_atom *);
पूर्णांक wndwc37e_update(काष्ठा nv50_wndw *, u32 *);

पूर्णांक wndwc57e_new(काष्ठा nouveau_drm *, क्रमागत drm_plane_type, पूर्णांक, s32,
		 काष्ठा nv50_wndw **);
bool wndwc57e_ilut(काष्ठा nv50_wndw *, काष्ठा nv50_wndw_atom *, पूर्णांक);
पूर्णांक wndwc57e_ilut_set(काष्ठा nv50_wndw *, काष्ठा nv50_wndw_atom *);
पूर्णांक wndwc57e_ilut_clr(काष्ठा nv50_wndw *);
पूर्णांक wndwc57e_csc_set(काष्ठा nv50_wndw *, काष्ठा nv50_wndw_atom *);
पूर्णांक wndwc57e_csc_clr(काष्ठा nv50_wndw *);

पूर्णांक wndwc67e_new(काष्ठा nouveau_drm *, क्रमागत drm_plane_type, पूर्णांक, s32,
		 काष्ठा nv50_wndw **);

पूर्णांक nv50_wndw_new(काष्ठा nouveau_drm *, क्रमागत drm_plane_type, पूर्णांक index,
		  काष्ठा nv50_wndw **);
#पूर्ण_अगर
