<शैली गुरु>
#अगर_अघोषित __NV50_KMS_H__
#घोषणा __NV50_KMS_H__
#समावेश <linux/workqueue.h>
#समावेश <nvअगर/स्मृति.स>
#समावेश <nvअगर/push.h>

#समावेश "nouveau_display.h"

काष्ठा nv50_msto;
काष्ठा nouveau_encoder;

काष्ठा nv50_disp अणु
	काष्ठा nvअगर_disp *disp;
	काष्ठा nv50_core *core;
	काष्ठा nvअगर_object caps;

#घोषणा NV50_DISP_SYNC(c, o)                                ((c) * 0x040 + (o))
#घोषणा NV50_DISP_CORE_NTFY                       NV50_DISP_SYNC(0      , 0x00)
#घोषणा NV50_DISP_WNDW_SEM0(c)                    NV50_DISP_SYNC(1 + (c), 0x00)
#घोषणा NV50_DISP_WNDW_SEM1(c)                    NV50_DISP_SYNC(1 + (c), 0x10)
#घोषणा NV50_DISP_WNDW_NTFY(c)                    NV50_DISP_SYNC(1 + (c), 0x20)
#घोषणा NV50_DISP_BASE_SEM0(c)                    NV50_DISP_WNDW_SEM0(0 + (c))
#घोषणा NV50_DISP_BASE_SEM1(c)                    NV50_DISP_WNDW_SEM1(0 + (c))
#घोषणा NV50_DISP_BASE_NTFY(c)                    NV50_DISP_WNDW_NTFY(0 + (c))
#घोषणा NV50_DISP_OVLY_SEM0(c)                    NV50_DISP_WNDW_SEM0(4 + (c))
#घोषणा NV50_DISP_OVLY_SEM1(c)                    NV50_DISP_WNDW_SEM1(4 + (c))
#घोषणा NV50_DISP_OVLY_NTFY(c)                    NV50_DISP_WNDW_NTFY(4 + (c))
	काष्ठा nouveau_bo *sync;

	काष्ठा mutex mutex;
पूर्ण;

अटल अंतरभूत काष्ठा nv50_disp *
nv50_disp(काष्ठा drm_device *dev)
अणु
	वापस nouveau_display(dev)->priv;
पूर्ण

काष्ठा nv50_disp_पूर्णांकerlock अणु
	क्रमागत nv50_disp_पूर्णांकerlock_type अणु
		NV50_DISP_INTERLOCK_CORE = 0,
		NV50_DISP_INTERLOCK_CURS,
		NV50_DISP_INTERLOCK_BASE,
		NV50_DISP_INTERLOCK_OVLY,
		NV50_DISP_INTERLOCK_WNDW,
		NV50_DISP_INTERLOCK_WIMM,
		NV50_DISP_INTERLOCK__SIZE
	पूर्ण type;
	u32 data;
	u32 wimm;
पूर्ण;

व्योम corec37d_ntfy_init(काष्ठा nouveau_bo *, u32);

व्योम head907d_olut_load(काष्ठा drm_color_lut *, पूर्णांक size, व्योम __iomem *);

काष्ठा nv50_chan अणु
	काष्ठा nvअगर_object user;
	काष्ठा nvअगर_device *device;
पूर्ण;

काष्ठा nv50_dmac अणु
	काष्ठा nv50_chan base;

	काष्ठा nvअगर_push _push;
	काष्ठा nvअगर_push *push;
	u32 *ptr;

	काष्ठा nvअगर_object sync;
	काष्ठा nvअगर_object vram;

	/* Protects against concurrent pushbuf access to this channel, lock is
	 * grabbed by evo_रुको (अगर the pushbuf reservation is successful) and
	 * dropped again by evo_kick. */
	काष्ठा mutex lock;

	u32 cur;
	u32 put;
	u32 max;
पूर्ण;

काष्ठा nv50_outp_atom अणु
	काष्ठा list_head head;

	काष्ठा drm_encoder *encoder;
	bool flush_disable;

	जोड़ nv50_outp_atom_mask अणु
		काष्ठा अणु
			bool ctrl:1;
		पूर्ण;
		u8 mask;
	पूर्ण set, clr;
पूर्ण;

पूर्णांक nv50_dmac_create(काष्ठा nvअगर_device *device, काष्ठा nvअगर_object *disp,
		     स्थिर s32 *oclass, u8 head, व्योम *data, u32 size,
		     s64 syncbuf, काष्ठा nv50_dmac *dmac);
व्योम nv50_dmac_destroy(काष्ठा nv50_dmac *);

/*
 * For normal encoders this just वापसs the encoder. For active MST encoders,
 * this वापसs the real outp that's driving displays on the topology.
 * Inactive MST encoders वापस शून्य, since they would have no real outp to
 * वापस anyway.
 */
काष्ठा nouveau_encoder *nv50_real_outp(काष्ठा drm_encoder *encoder);

u32 *evo_रुको(काष्ठा nv50_dmac *, पूर्णांक nr);
व्योम evo_kick(u32 *, काष्ठा nv50_dmac *);

बाह्य स्थिर u64 disp50xx_modअगरiers[];
बाह्य स्थिर u64 disp90xx_modअगरiers[];
बाह्य स्थिर u64 wndwc57e_modअगरiers[];
#पूर्ण_अगर
