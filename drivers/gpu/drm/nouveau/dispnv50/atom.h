<शैली गुरु>
#अगर_अघोषित __NV50_KMS_ATOM_H__
#घोषणा __NV50_KMS_ATOM_H__
#घोषणा nv50_atom(p) container_of((p), काष्ठा nv50_atom, state)
#समावेश <drm/drm_atomic.h>
#समावेश "crc.h"

काष्ठा nouveau_encoder;

काष्ठा nv50_atom अणु
	काष्ठा drm_atomic_state state;

	काष्ठा list_head outp;
	bool lock_core;
	bool flush_disable;
पूर्ण;

#घोषणा nv50_head_atom(p) container_of((p), काष्ठा nv50_head_atom, state)

काष्ठा nv50_head_atom अणु
	काष्ठा drm_crtc_state state;

	काष्ठा अणु
		u32 mask;
		u32 owned;
		u32 olut;
	पूर्ण wndw;

	काष्ठा अणु
		u16 iW;
		u16 iH;
		u16 oW;
		u16 oH;
	पूर्ण view;

	काष्ठा nv50_head_mode अणु
		bool पूर्णांकerlace;
		u32 घड़ी;
		काष्ठा अणु
			u16 active;
			u16 synce;
			u16 blanke;
			u16 blanks;
		पूर्ण h;
		काष्ठा अणु
			u32 active;
			u16 synce;
			u16 blanke;
			u16 blanks;
			u16 blank2s;
			u16 blank2e;
			u16 blankus;
		पूर्ण v;
	पूर्ण mode;

	काष्ठा अणु
		bool visible;
		u32 handle;
		u64 offset:40;
		u8 buffer:1;
		u8 mode:4;
		u16 size:11;
		u8 range:2;
		u8 output_mode:2;
		व्योम (*load)(काष्ठा drm_color_lut *, पूर्णांक size, व्योम __iomem *);
	पूर्ण olut;

	काष्ठा अणु
		bool visible;
		u32 handle;
		u64 offset:40;
		u8  क्रमmat;
		u8  kind:7;
		u8  layout:1;
		u8  blockh:4;
		u16 blocks:12;
		u32 pitch:20;
		u16 x;
		u16 y;
		u16 w;
		u16 h;
	पूर्ण core;

	काष्ठा अणु
		bool visible;
		u32 handle;
		u64 offset:40;
		u8  layout:2;
		u8  क्रमmat:8;
	पूर्ण curs;

	काष्ठा अणु
		u8  depth;
		u8  cpp;
		u16 x;
		u16 y;
		u16 w;
		u16 h;
	पूर्ण base;

	काष्ठा अणु
		u8 cpp;
	पूर्ण ovly;

	काष्ठा अणु
		bool enable:1;
		u8 bits:2;
		u8 mode:4;
	पूर्ण dither;

	काष्ठा अणु
		काष्ठा अणु
			u16 cos:12;
			u16 sin:12;
		पूर्ण sat;
	पूर्ण procamp;

	काष्ठा अणु
		u8 nhsync:1;
		u8 nvsync:1;
		u8 depth:4;
		u8 crc_raster:2;
		u8 bpc;
	पूर्ण or;

	काष्ठा nv50_crc_atom crc;

	/* Currently only used क्रम MST */
	काष्ठा अणु
		पूर्णांक pbn;
		u8 tu:6;
	पूर्ण dp;

	जोड़ nv50_head_atom_mask अणु
		काष्ठा अणु
			bool olut:1;
			bool core:1;
			bool curs:1;
			bool view:1;
			bool mode:1;
			bool base:1;
			bool ovly:1;
			bool dither:1;
			bool procamp:1;
			bool crc:1;
			bool or:1;
		पूर्ण;
		u16 mask;
	पूर्ण set, clr;
पूर्ण;

अटल अंतरभूत काष्ठा nv50_head_atom *
nv50_head_atom_get(काष्ठा drm_atomic_state *state, काष्ठा drm_crtc *crtc)
अणु
	काष्ठा drm_crtc_state *statec = drm_atomic_get_crtc_state(state, crtc);
	अगर (IS_ERR(statec))
		वापस (व्योम *)statec;
	वापस nv50_head_atom(statec);
पूर्ण

अटल अंतरभूत काष्ठा drm_encoder *
nv50_head_atom_get_encoder(काष्ठा nv50_head_atom *atom)
अणु
	काष्ठा drm_encoder *encoder = शून्य;

	/* We only ever have a single encoder */
	drm_क्रम_each_encoder_mask(encoder, atom->state.crtc->dev,
				  atom->state.encoder_mask)
		अवरोध;

	वापस encoder;
पूर्ण

#घोषणा nv50_wndw_atom(p) container_of((p), काष्ठा nv50_wndw_atom, state)

काष्ठा nv50_wndw_atom अणु
	काष्ठा drm_plane_state state;

	काष्ठा drm_property_blob *ilut;
	bool visible;

	काष्ठा अणु
		u32  handle;
		u16  offset:12;
		bool awaken:1;
	पूर्ण ntfy;

	काष्ठा अणु
		u32 handle;
		u16 offset:12;
		u32 acquire;
		u32 release;
	पूर्ण sema;

	काष्ठा अणु
		u32 handle;
		काष्ठा अणु
			u64 offset:40;
			u8  buffer:1;
			u8  enable:2;
			u8  mode:4;
			u16 size:11;
			u8  range:2;
			u8  output_mode:2;
			व्योम (*load)(काष्ठा drm_color_lut *, पूर्णांक size,
				     व्योम __iomem *);
		पूर्ण i;
	पूर्ण xlut;

	काष्ठा अणु
		u32 matrix[12];
		bool valid;
	पूर्ण csc;

	काष्ठा अणु
		u8  mode:2;
		u8  पूर्णांकerval:4;

		u8  colorspace:2;
		u8  क्रमmat;
		u8  kind:7;
		u8  layout:1;
		u8  blockh:4;
		u16 blocks[3];
		u32 pitch[3];
		u16 w;
		u16 h;

		u32 handle[6];
		u64 offset[6];
	पूर्ण image;

	काष्ठा अणु
		u16 sx;
		u16 sy;
		u16 sw;
		u16 sh;
		u16 dw;
		u16 dh;
	पूर्ण scale;

	काष्ठा अणु
		u16 x;
		u16 y;
	पूर्ण poपूर्णांक;

	काष्ठा अणु
		u8 depth;
		u8 k1;
		u8 src_color:4;
		u8 dst_color:4;
	पूर्ण blend;

	जोड़ nv50_wndw_atom_mask अणु
		काष्ठा अणु
			bool ntfy:1;
			bool sema:1;
			bool xlut:1;
			bool csc:1;
			bool image:1;
			bool scale:1;
			bool poपूर्णांक:1;
			bool blend:1;
		पूर्ण;
		u8 mask;
	पूर्ण set, clr;
पूर्ण;
#पूर्ण_अगर
