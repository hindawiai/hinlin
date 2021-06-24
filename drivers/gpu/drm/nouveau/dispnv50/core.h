<शैली गुरु>
#अगर_अघोषित __NV50_KMS_CORE_H__
#घोषणा __NV50_KMS_CORE_H__
#समावेश "disp.h"
#समावेश "atom.h"
#समावेश "crc.h"
#समावेश <nouveau_encoder.h>

काष्ठा nv50_core अणु
	स्थिर काष्ठा nv50_core_func *func;
	काष्ठा nv50_dmac chan;
	bool assign_winकरोws;
पूर्ण;

पूर्णांक nv50_core_new(काष्ठा nouveau_drm *, काष्ठा nv50_core **);
व्योम nv50_core_del(काष्ठा nv50_core **);

काष्ठा nv50_core_func अणु
	पूर्णांक (*init)(काष्ठा nv50_core *);
	व्योम (*ntfy_init)(काष्ठा nouveau_bo *, u32 offset);
	पूर्णांक (*caps_init)(काष्ठा nouveau_drm *, काष्ठा nv50_disp *);
	पूर्णांक (*ntfy_रुको_करोne)(काष्ठा nouveau_bo *, u32 offset,
			      काष्ठा nvअगर_device *);
	पूर्णांक (*update)(काष्ठा nv50_core *, u32 *पूर्णांकerlock, bool ntfy);

	काष्ठा अणु
		पूर्णांक (*owner)(काष्ठा nv50_core *);
	पूर्ण wndw;

	स्थिर काष्ठा nv50_head_func *head;
#अगर IS_ENABLED(CONFIG_DEBUG_FS)
	स्थिर काष्ठा nv50_crc_func *crc;
#पूर्ण_अगर
	स्थिर काष्ठा nv50_outp_func अणु
		पूर्णांक (*ctrl)(काष्ठा nv50_core *, पूर्णांक or, u32 ctrl,
			     काष्ठा nv50_head_atom *);
		/* XXX: Only used by SORs and PIORs क्रम now */
		व्योम (*get_caps)(काष्ठा nv50_disp *,
				 काष्ठा nouveau_encoder *, पूर्णांक or);
	पूर्ण *dac, *pior, *sor;
पूर्ण;

पूर्णांक core507d_new(काष्ठा nouveau_drm *, s32, काष्ठा nv50_core **);
पूर्णांक core507d_new_(स्थिर काष्ठा nv50_core_func *, काष्ठा nouveau_drm *, s32,
		  काष्ठा nv50_core **);
पूर्णांक core507d_init(काष्ठा nv50_core *);
व्योम core507d_ntfy_init(काष्ठा nouveau_bo *, u32);
पूर्णांक core507d_पढ़ो_caps(काष्ठा nv50_disp *disp);
पूर्णांक core507d_caps_init(काष्ठा nouveau_drm *, काष्ठा nv50_disp *);
पूर्णांक core507d_ntfy_रुको_करोne(काष्ठा nouveau_bo *, u32, काष्ठा nvअगर_device *);
पूर्णांक core507d_update(काष्ठा nv50_core *, u32 *, bool);

बाह्य स्थिर काष्ठा nv50_outp_func dac507d;
बाह्य स्थिर काष्ठा nv50_outp_func sor507d;
बाह्य स्थिर काष्ठा nv50_outp_func pior507d;

पूर्णांक core827d_new(काष्ठा nouveau_drm *, s32, काष्ठा nv50_core **);

पूर्णांक core907d_new(काष्ठा nouveau_drm *, s32, काष्ठा nv50_core **);
पूर्णांक core907d_caps_init(काष्ठा nouveau_drm *drm, काष्ठा nv50_disp *disp);
बाह्य स्थिर काष्ठा nv50_outp_func dac907d;
बाह्य स्थिर काष्ठा nv50_outp_func sor907d;

पूर्णांक core917d_new(काष्ठा nouveau_drm *, s32, काष्ठा nv50_core **);

पूर्णांक corec37d_new(काष्ठा nouveau_drm *, s32, काष्ठा nv50_core **);
पूर्णांक corec37d_caps_init(काष्ठा nouveau_drm *, काष्ठा nv50_disp *);
पूर्णांक corec37d_ntfy_रुको_करोne(काष्ठा nouveau_bo *, u32, काष्ठा nvअगर_device *);
पूर्णांक corec37d_update(काष्ठा nv50_core *, u32 *, bool);
पूर्णांक corec37d_wndw_owner(काष्ठा nv50_core *);
बाह्य स्थिर काष्ठा nv50_outp_func sorc37d;

पूर्णांक corec57d_new(काष्ठा nouveau_drm *, s32, काष्ठा nv50_core **);
#पूर्ण_अगर
