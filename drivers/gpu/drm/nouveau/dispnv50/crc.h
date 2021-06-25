<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NV50_CRC_H__
#घोषणा __NV50_CRC_H__

#समावेश <linux/mutex.h>
#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_vblank_work.h>

#समावेश <nvअगर/स्मृति.स>
#समावेश <nvkm/subdev/मूलप्रण.स>
#समावेश "nouveau_encoder.h"

काष्ठा nv50_atom;
काष्ठा nv50_disp;
काष्ठा nv50_head;

#अगर IS_ENABLED(CONFIG_DEBUG_FS)
क्रमागत nv50_crc_source अणु
	NV50_CRC_SOURCE_NONE = 0,
	NV50_CRC_SOURCE_AUTO,
	NV50_CRC_SOURCE_RG,
	NV50_CRC_SOURCE_OUTP_ACTIVE,
	NV50_CRC_SOURCE_OUTP_COMPLETE,
	NV50_CRC_SOURCE_OUTP_INACTIVE,
पूर्ण;

/* RG -> SF (DP only)
 *    -> SOR
 *    -> PIOR
 *    -> DAC
 */
क्रमागत nv50_crc_source_type अणु
	NV50_CRC_SOURCE_TYPE_NONE = 0,
	NV50_CRC_SOURCE_TYPE_SOR,
	NV50_CRC_SOURCE_TYPE_PIOR,
	NV50_CRC_SOURCE_TYPE_DAC,
	NV50_CRC_SOURCE_TYPE_RG,
	NV50_CRC_SOURCE_TYPE_SF,
पूर्ण;

काष्ठा nv50_crc_notअगरier_ctx अणु
	काष्ठा nvअगर_mem mem;
	काष्ठा nvअगर_object ntfy;
पूर्ण;

काष्ठा nv50_crc_atom अणु
	क्रमागत nv50_crc_source src;
	/* Only used क्रम gv100+ */
	u8 wndw : 4;
पूर्ण;

काष्ठा nv50_crc_func अणु
	पूर्णांक (*set_src)(काष्ठा nv50_head *, पूर्णांक or, क्रमागत nv50_crc_source_type,
		       काष्ठा nv50_crc_notअगरier_ctx *, u32 wndw);
	पूर्णांक (*set_ctx)(काष्ठा nv50_head *, काष्ठा nv50_crc_notअगरier_ctx *);
	u32 (*get_entry)(काष्ठा nv50_head *, काष्ठा nv50_crc_notअगरier_ctx *,
			 क्रमागत nv50_crc_source, पूर्णांक idx);
	bool (*ctx_finished)(काष्ठा nv50_head *,
			     काष्ठा nv50_crc_notअगरier_ctx *);
	लघु flip_threshold;
	लघु num_entries;
	माप_प्रकार notअगरier_len;
पूर्ण;

काष्ठा nv50_crc अणु
	spinlock_t lock;
	काष्ठा nv50_crc_notअगरier_ctx ctx[2];
	काष्ठा drm_vblank_work flip_work;
	क्रमागत nv50_crc_source src;

	u64 frame;
	लघु entry_idx;
	लघु flip_threshold;
	u8 ctx_idx : 1;
	bool ctx_changed : 1;
पूर्ण;

व्योम nv50_crc_init(काष्ठा drm_device *dev);
पूर्णांक nv50_head_crc_late_रेजिस्टर(काष्ठा nv50_head *);
व्योम nv50_crc_handle_vblank(काष्ठा nv50_head *head);

पूर्णांक nv50_crc_verअगरy_source(काष्ठा drm_crtc *, स्थिर अक्षर *, माप_प्रकार *);
स्थिर अक्षर *स्थिर *nv50_crc_get_sources(काष्ठा drm_crtc *, माप_प्रकार *);
पूर्णांक nv50_crc_set_source(काष्ठा drm_crtc *, स्थिर अक्षर *);

पूर्णांक nv50_crc_atomic_check_head(काष्ठा nv50_head *, काष्ठा nv50_head_atom *,
			       काष्ठा nv50_head_atom *);
व्योम nv50_crc_atomic_check_outp(काष्ठा nv50_atom *atom);
व्योम nv50_crc_atomic_stop_reporting(काष्ठा drm_atomic_state *);
व्योम nv50_crc_atomic_init_notअगरier_contexts(काष्ठा drm_atomic_state *);
व्योम nv50_crc_atomic_release_notअगरier_contexts(काष्ठा drm_atomic_state *);
व्योम nv50_crc_atomic_start_reporting(काष्ठा drm_atomic_state *);
व्योम nv50_crc_atomic_set(काष्ठा nv50_head *, काष्ठा nv50_head_atom *);
व्योम nv50_crc_atomic_clr(काष्ठा nv50_head *);

बाह्य स्थिर काष्ठा nv50_crc_func crc907d;
बाह्य स्थिर काष्ठा nv50_crc_func crcc37d;

#अन्यथा /* IS_ENABLED(CONFIG_DEBUG_FS) */
काष्ठा nv50_crc अणुपूर्ण;
काष्ठा nv50_crc_func अणुपूर्ण;
काष्ठा nv50_crc_atom अणुपूर्ण;

#घोषणा nv50_crc_verअगरy_source शून्य
#घोषणा nv50_crc_get_sources शून्य
#घोषणा nv50_crc_set_source शून्य

अटल अंतरभूत व्योम nv50_crc_init(काष्ठा drm_device *dev) अणुपूर्ण
अटल अंतरभूत पूर्णांक
nv50_head_crc_late_रेजिस्टर(काष्ठा nv50_head *head) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम nv50_crc_handle_vblank(काष्ठा nv50_head *head) अणुपूर्ण

अटल अंतरभूत पूर्णांक
nv50_crc_atomic_check_head(काष्ठा nv50_head *head,
			   काष्ठा nv50_head_atom *asyh,
			   काष्ठा nv50_head_atom *armh) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम nv50_crc_atomic_check_outp(काष्ठा nv50_atom *atom) अणुपूर्ण
अटल अंतरभूत व्योम
nv50_crc_atomic_stop_reporting(काष्ठा drm_atomic_state *state) अणुपूर्ण
अटल अंतरभूत व्योम
nv50_crc_atomic_init_notअगरier_contexts(काष्ठा drm_atomic_state *state) अणुपूर्ण
अटल अंतरभूत व्योम
nv50_crc_atomic_release_notअगरier_contexts(काष्ठा drm_atomic_state *state) अणुपूर्ण
अटल अंतरभूत व्योम
nv50_crc_atomic_start_reporting(काष्ठा drm_atomic_state *state) अणुपूर्ण
अटल अंतरभूत व्योम
nv50_crc_atomic_set(काष्ठा nv50_head *head, काष्ठा nv50_head_atom *state) अणुपूर्ण
अटल अंतरभूत व्योम
nv50_crc_atomic_clr(काष्ठा nv50_head *head) अणुपूर्ण

#पूर्ण_अगर /* IS_ENABLED(CONFIG_DEBUG_FS) */
#पूर्ण_अगर /* !__NV50_CRC_H__ */
