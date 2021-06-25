<शैली गुरु>
#अगर_अघोषित __NV50_KMS_HEAD_H__
#घोषणा __NV50_KMS_HEAD_H__
#घोषणा nv50_head(c) container_of((c), काष्ठा nv50_head, base.base)
#समावेश <linux/workqueue.h>

#समावेश "disp.h"
#समावेश "atom.h"
#समावेश "crc.h"
#समावेश "lut.h"

#समावेश "nouveau_crtc.h"
#समावेश "nouveau_encoder.h"

काष्ठा nv50_head अणु
	स्थिर काष्ठा nv50_head_func *func;
	काष्ठा nouveau_crtc base;
	काष्ठा nv50_crc crc;
	काष्ठा nv50_lut olut;
	काष्ठा nv50_msto *msto;
पूर्ण;

काष्ठा nv50_head *nv50_head_create(काष्ठा drm_device *, पूर्णांक index);
व्योम nv50_head_flush_set(काष्ठा nv50_head *head, काष्ठा nv50_head_atom *asyh);
व्योम nv50_head_flush_clr(काष्ठा nv50_head *head,
			 काष्ठा nv50_head_atom *asyh, bool flush);

काष्ठा nv50_head_func अणु
	पूर्णांक (*view)(काष्ठा nv50_head *, काष्ठा nv50_head_atom *);
	पूर्णांक (*mode)(काष्ठा nv50_head *, काष्ठा nv50_head_atom *);
	bool (*olut)(काष्ठा nv50_head *, काष्ठा nv50_head_atom *, पूर्णांक);
	bool olut_identity;
	पूर्णांक  olut_size;
	पूर्णांक (*olut_set)(काष्ठा nv50_head *, काष्ठा nv50_head_atom *);
	पूर्णांक (*olut_clr)(काष्ठा nv50_head *);
	व्योम (*core_calc)(काष्ठा nv50_head *, काष्ठा nv50_head_atom *);
	पूर्णांक (*core_set)(काष्ठा nv50_head *, काष्ठा nv50_head_atom *);
	पूर्णांक (*core_clr)(काष्ठा nv50_head *);
	पूर्णांक (*curs_layout)(काष्ठा nv50_head *, काष्ठा nv50_wndw_atom *,
			   काष्ठा nv50_head_atom *);
	पूर्णांक (*curs_क्रमmat)(काष्ठा nv50_head *, काष्ठा nv50_wndw_atom *,
			   काष्ठा nv50_head_atom *);
	पूर्णांक (*curs_set)(काष्ठा nv50_head *, काष्ठा nv50_head_atom *);
	पूर्णांक (*curs_clr)(काष्ठा nv50_head *);
	पूर्णांक (*base)(काष्ठा nv50_head *, काष्ठा nv50_head_atom *);
	पूर्णांक (*ovly)(काष्ठा nv50_head *, काष्ठा nv50_head_atom *);
	पूर्णांक (*dither)(काष्ठा nv50_head *, काष्ठा nv50_head_atom *);
	पूर्णांक (*procamp)(काष्ठा nv50_head *, काष्ठा nv50_head_atom *);
	पूर्णांक (*or)(काष्ठा nv50_head *, काष्ठा nv50_head_atom *);
	व्योम (*अटल_wndw_map)(काष्ठा nv50_head *, काष्ठा nv50_head_atom *);
पूर्ण;

बाह्य स्थिर काष्ठा nv50_head_func head507d;
पूर्णांक head507d_view(काष्ठा nv50_head *, काष्ठा nv50_head_atom *);
पूर्णांक head507d_mode(काष्ठा nv50_head *, काष्ठा nv50_head_atom *);
bool head507d_olut(काष्ठा nv50_head *, काष्ठा nv50_head_atom *, पूर्णांक);
व्योम head507d_core_calc(काष्ठा nv50_head *, काष्ठा nv50_head_atom *);
पूर्णांक head507d_core_clr(काष्ठा nv50_head *);
पूर्णांक head507d_curs_layout(काष्ठा nv50_head *, काष्ठा nv50_wndw_atom *,
			 काष्ठा nv50_head_atom *);
पूर्णांक head507d_curs_क्रमmat(काष्ठा nv50_head *, काष्ठा nv50_wndw_atom *,
			 काष्ठा nv50_head_atom *);
पूर्णांक head507d_base(काष्ठा nv50_head *, काष्ठा nv50_head_atom *);
पूर्णांक head507d_ovly(काष्ठा nv50_head *, काष्ठा nv50_head_atom *);
पूर्णांक head507d_dither(काष्ठा nv50_head *, काष्ठा nv50_head_atom *);
पूर्णांक head507d_procamp(काष्ठा nv50_head *, काष्ठा nv50_head_atom *);

बाह्य स्थिर काष्ठा nv50_head_func head827d;

बाह्य स्थिर काष्ठा nv50_head_func head907d;
पूर्णांक head907d_view(काष्ठा nv50_head *, काष्ठा nv50_head_atom *);
पूर्णांक head907d_mode(काष्ठा nv50_head *, काष्ठा nv50_head_atom *);
bool head907d_olut(काष्ठा nv50_head *, काष्ठा nv50_head_atom *, पूर्णांक);
पूर्णांक head907d_olut_set(काष्ठा nv50_head *, काष्ठा nv50_head_atom *);
पूर्णांक head907d_olut_clr(काष्ठा nv50_head *);
पूर्णांक head907d_core_set(काष्ठा nv50_head *, काष्ठा nv50_head_atom *);
पूर्णांक head907d_core_clr(काष्ठा nv50_head *);
पूर्णांक head907d_curs_set(काष्ठा nv50_head *, काष्ठा nv50_head_atom *);
पूर्णांक head907d_curs_clr(काष्ठा nv50_head *);
पूर्णांक head907d_ovly(काष्ठा nv50_head *, काष्ठा nv50_head_atom *);
पूर्णांक head907d_procamp(काष्ठा nv50_head *, काष्ठा nv50_head_atom *);
पूर्णांक head907d_or(काष्ठा nv50_head *, काष्ठा nv50_head_atom *);

बाह्य स्थिर काष्ठा nv50_head_func head917d;
पूर्णांक head917d_curs_layout(काष्ठा nv50_head *, काष्ठा nv50_wndw_atom *,
			 काष्ठा nv50_head_atom *);

बाह्य स्थिर काष्ठा nv50_head_func headc37d;
पूर्णांक headc37d_view(काष्ठा nv50_head *, काष्ठा nv50_head_atom *);
पूर्णांक headc37d_curs_क्रमmat(काष्ठा nv50_head *, काष्ठा nv50_wndw_atom *,
			 काष्ठा nv50_head_atom *);
पूर्णांक headc37d_curs_set(काष्ठा nv50_head *, काष्ठा nv50_head_atom *);
पूर्णांक headc37d_curs_clr(काष्ठा nv50_head *);
पूर्णांक headc37d_dither(काष्ठा nv50_head *, काष्ठा nv50_head_atom *);
व्योम headc37d_अटल_wndw_map(काष्ठा nv50_head *, काष्ठा nv50_head_atom *);

बाह्य स्थिर काष्ठा nv50_head_func headc57d;
#पूर्ण_अगर
