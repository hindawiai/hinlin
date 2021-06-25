<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVKM_DISP_IOR_H__
#घोषणा __NVKM_DISP_IOR_H__
#समावेश "priv.h"
काष्ठा nvkm_i2c_aux;

काष्ठा nvkm_ior अणु
	स्थिर काष्ठा nvkm_ior_func *func;
	काष्ठा nvkm_disp *disp;
	क्रमागत nvkm_ior_type अणु
		DAC,
		SOR,
		PIOR,
	पूर्ण type;
	पूर्णांक id;
	अक्षर name[8];

	काष्ठा list_head head;
	bool identity;

	काष्ठा nvkm_ior_state अणु
		काष्ठा nvkm_outp *outp;
		अचिन्हित rgभाग;
		अचिन्हित proto_evo:4;
		क्रमागत nvkm_ior_proto अणु
			CRT,
			TV,
			TMDS,
			LVDS,
			DP,
			UNKNOWN
		पूर्ण proto:3;
		अचिन्हित link:2;
		अचिन्हित head:8;
	पूर्ण arm, asy;

	/* Armed DP state. */
	काष्ठा अणु
		bool mst;
		bool ef;
		u8 nr;
		u8 bw;
	पूर्ण dp;

	/* Armed TMDS state. */
	काष्ठा अणु
		bool high_speed;
	पूर्ण पंचांगds;
पूर्ण;

काष्ठा nvkm_ior_func अणु
	काष्ठा अणु
		पूर्णांक (*get)(काष्ठा nvkm_outp *, पूर्णांक *link);
		व्योम (*set)(काष्ठा nvkm_outp *, काष्ठा nvkm_ior *);
	पूर्ण route;

	व्योम (*state)(काष्ठा nvkm_ior *, काष्ठा nvkm_ior_state *);
	व्योम (*घातer)(काष्ठा nvkm_ior *, bool normal, bool pu,
		      bool data, bool vsync, bool hsync);
	पूर्णांक (*sense)(काष्ठा nvkm_ior *, u32 loadval);
	व्योम (*घड़ी)(काष्ठा nvkm_ior *);
	व्योम (*war_2)(काष्ठा nvkm_ior *);
	व्योम (*war_3)(काष्ठा nvkm_ior *);

	काष्ठा अणु
		व्योम (*ctrl)(काष्ठा nvkm_ior *, पूर्णांक head, bool enable,
			     u8 max_ac_packet, u8 rekey, u8 *avi, u8 avi_size,
			     u8 *venकरोr, u8 venकरोr_size);
		व्योम (*scdc)(काष्ठा nvkm_ior *, u8 scdc);
	पूर्ण hdmi;

	काष्ठा अणु
		u8 lanes[4];
		पूर्णांक (*links)(काष्ठा nvkm_ior *, काष्ठा nvkm_i2c_aux *);
		व्योम (*घातer)(काष्ठा nvkm_ior *, पूर्णांक nr);
		व्योम (*pattern)(काष्ठा nvkm_ior *, पूर्णांक pattern);
		व्योम (*drive)(काष्ठा nvkm_ior *, पूर्णांक ln, पूर्णांक pc,
			      पूर्णांक dc, पूर्णांक pe, पूर्णांक tx_pu);
		व्योम (*vcpi)(काष्ठा nvkm_ior *, पूर्णांक head, u8 slot,
			     u8 slot_nr, u16 pbn, u16 aligned);
		व्योम (*audio)(काष्ठा nvkm_ior *, पूर्णांक head, bool enable);
		व्योम (*audio_sym)(काष्ठा nvkm_ior *, पूर्णांक head, u16 h, u32 v);
		व्योम (*activesym)(काष्ठा nvkm_ior *, पूर्णांक head,
				  u8 TU, u8 VTUa, u8 VTUf, u8 VTUi);
		व्योम (*watermark)(काष्ठा nvkm_ior *, पूर्णांक head, u8 watermark);
	पूर्ण dp;

	काष्ठा अणु
		व्योम (*hpd)(काष्ठा nvkm_ior *, पूर्णांक head, bool present);
		व्योम (*eld)(काष्ठा nvkm_ior *, पूर्णांक head, u8 *data, u8 size);
		व्योम (*device_entry)(काष्ठा nvkm_ior *, पूर्णांक head);
	पूर्ण hda;
पूर्ण;

पूर्णांक nvkm_ior_new_(स्थिर काष्ठा nvkm_ior_func *func, काष्ठा nvkm_disp *,
		  क्रमागत nvkm_ior_type type, पूर्णांक id);
व्योम nvkm_ior_del(काष्ठा nvkm_ior **);
काष्ठा nvkm_ior *nvkm_ior_find(काष्ठा nvkm_disp *, क्रमागत nvkm_ior_type, पूर्णांक id);

अटल अंतरभूत u32
nv50_ior_base(काष्ठा nvkm_ior *ior)
अणु
	वापस ior->id * 0x800;
पूर्ण

व्योम nv50_dac_घातer(काष्ठा nvkm_ior *, bool, bool, bool, bool, bool);
पूर्णांक nv50_dac_sense(काष्ठा nvkm_ior *, u32);

व्योम nv50_pior_depth(काष्ठा nvkm_ior *, काष्ठा nvkm_ior_state *, u32 ctrl);

अटल अंतरभूत u32
nv50_sor_link(काष्ठा nvkm_ior *ior)
अणु
	वापस nv50_ior_base(ior) + ((ior->asy.link == 2) * 0x80);
पूर्ण

व्योम nv50_sor_state(काष्ठा nvkm_ior *, काष्ठा nvkm_ior_state *);
व्योम nv50_sor_घातer(काष्ठा nvkm_ior *, bool, bool, bool, bool, bool);
व्योम nv50_sor_घड़ी(काष्ठा nvkm_ior *);

व्योम g94_sor_state(काष्ठा nvkm_ior *, काष्ठा nvkm_ior_state *);
पूर्णांक g94_sor_dp_links(काष्ठा nvkm_ior *, काष्ठा nvkm_i2c_aux *);
व्योम g94_sor_dp_घातer(काष्ठा nvkm_ior *, पूर्णांक);
व्योम g94_sor_dp_pattern(काष्ठा nvkm_ior *, पूर्णांक);
व्योम g94_sor_dp_drive(काष्ठा nvkm_ior *, पूर्णांक, पूर्णांक, पूर्णांक, पूर्णांक, पूर्णांक);
व्योम g94_sor_dp_audio_sym(काष्ठा nvkm_ior *, पूर्णांक, u16, u32);
व्योम g94_sor_dp_activesym(काष्ठा nvkm_ior *, पूर्णांक, u8, u8, u8, u8);
व्योम g94_sor_dp_watermark(काष्ठा nvkm_ior *, पूर्णांक, u8);

व्योम gt215_sor_dp_audio(काष्ठा nvkm_ior *, पूर्णांक, bool);

व्योम gf119_sor_state(काष्ठा nvkm_ior *, काष्ठा nvkm_ior_state *);
व्योम gf119_sor_घड़ी(काष्ठा nvkm_ior *);
पूर्णांक gf119_sor_dp_links(काष्ठा nvkm_ior *, काष्ठा nvkm_i2c_aux *);
व्योम gf119_sor_dp_pattern(काष्ठा nvkm_ior *, पूर्णांक);
व्योम gf119_sor_dp_drive(काष्ठा nvkm_ior *, पूर्णांक, पूर्णांक, पूर्णांक, पूर्णांक, पूर्णांक);
व्योम gf119_sor_dp_vcpi(काष्ठा nvkm_ior *, पूर्णांक, u8, u8, u16, u16);
व्योम gf119_sor_dp_audio(काष्ठा nvkm_ior *, पूर्णांक, bool);
व्योम gf119_sor_dp_audio_sym(काष्ठा nvkm_ior *, पूर्णांक, u16, u32);
व्योम gf119_sor_dp_watermark(काष्ठा nvkm_ior *, पूर्णांक, u8);

व्योम gm107_sor_dp_pattern(काष्ठा nvkm_ior *, पूर्णांक);

व्योम gm200_sor_route_set(काष्ठा nvkm_outp *, काष्ठा nvkm_ior *);
पूर्णांक gm200_sor_route_get(काष्ठा nvkm_outp *, पूर्णांक *);
व्योम gm200_sor_dp_drive(काष्ठा nvkm_ior *, पूर्णांक, पूर्णांक, पूर्णांक, पूर्णांक, पूर्णांक);

व्योम gv100_sor_state(काष्ठा nvkm_ior *, काष्ठा nvkm_ior_state *);
व्योम gv100_sor_dp_audio(काष्ठा nvkm_ior *, पूर्णांक, bool);
व्योम gv100_sor_dp_audio_sym(काष्ठा nvkm_ior *, पूर्णांक, u16, u32);
व्योम gv100_sor_dp_watermark(काष्ठा nvkm_ior *, पूर्णांक, u8);

व्योम tu102_sor_dp_vcpi(काष्ठा nvkm_ior *, पूर्णांक, u8, u8, u16, u16);

व्योम g84_hdmi_ctrl(काष्ठा nvkm_ior *, पूर्णांक, bool, u8, u8, u8 *, u8 , u8 *, u8);
व्योम gt215_hdmi_ctrl(काष्ठा nvkm_ior *, पूर्णांक, bool, u8, u8, u8 *, u8 , u8 *, u8);
व्योम gf119_hdmi_ctrl(काष्ठा nvkm_ior *, पूर्णांक, bool, u8, u8, u8 *, u8 , u8 *, u8);
व्योम gk104_hdmi_ctrl(काष्ठा nvkm_ior *, पूर्णांक, bool, u8, u8, u8 *, u8 , u8 *, u8);
व्योम gv100_hdmi_ctrl(काष्ठा nvkm_ior *, पूर्णांक, bool, u8, u8, u8 *, u8 , u8 *, u8);

व्योम gm200_hdmi_scdc(काष्ठा nvkm_ior *, u8);

व्योम gt215_hda_hpd(काष्ठा nvkm_ior *, पूर्णांक, bool);
व्योम gt215_hda_eld(काष्ठा nvkm_ior *, पूर्णांक, u8 *, u8);

व्योम gf119_hda_hpd(काष्ठा nvkm_ior *, पूर्णांक, bool);
व्योम gf119_hda_eld(काष्ठा nvkm_ior *, पूर्णांक, u8 *, u8);
व्योम gf119_hda_device_entry(काष्ठा nvkm_ior *, पूर्णांक);

व्योम gv100_hda_device_entry(काष्ठा nvkm_ior *, पूर्णांक);

#घोषणा IOR_MSG(i,l,f,a...) करो अणु                                               \
	काष्ठा nvkm_ior *_ior = (i);                                           \
	nvkm_##l(&_ior->disp->engine.subdev, "%s: "f"\n", _ior->name, ##a);    \
पूर्ण जबतक(0)
#घोषणा IOR_WARN(i,f,a...) IOR_MSG((i), warn, f, ##a)
#घोषणा IOR_DBG(i,f,a...) IOR_MSG((i), debug, f, ##a)

पूर्णांक nv50_dac_cnt(काष्ठा nvkm_disp *, अचिन्हित दीर्घ *);
पूर्णांक nv50_dac_new(काष्ठा nvkm_disp *, पूर्णांक);

पूर्णांक gf119_dac_cnt(काष्ठा nvkm_disp *, अचिन्हित दीर्घ *);
पूर्णांक gf119_dac_new(काष्ठा nvkm_disp *, पूर्णांक);

पूर्णांक nv50_pior_cnt(काष्ठा nvkm_disp *, अचिन्हित दीर्घ *);
पूर्णांक nv50_pior_new(काष्ठा nvkm_disp *, पूर्णांक);

पूर्णांक nv50_sor_cnt(काष्ठा nvkm_disp *, अचिन्हित दीर्घ *);
पूर्णांक nv50_sor_new(काष्ठा nvkm_disp *, पूर्णांक);

पूर्णांक g84_sor_new(काष्ठा nvkm_disp *, पूर्णांक);

पूर्णांक g94_sor_cnt(काष्ठा nvkm_disp *, अचिन्हित दीर्घ *);
पूर्णांक g94_sor_new(काष्ठा nvkm_disp *, पूर्णांक);

पूर्णांक mcp77_sor_new(काष्ठा nvkm_disp *, पूर्णांक);
पूर्णांक gt215_sor_new(काष्ठा nvkm_disp *, पूर्णांक);
पूर्णांक mcp89_sor_new(काष्ठा nvkm_disp *, पूर्णांक);

पूर्णांक gf119_sor_cnt(काष्ठा nvkm_disp *, अचिन्हित दीर्घ *);
पूर्णांक gf119_sor_new(काष्ठा nvkm_disp *, पूर्णांक);

पूर्णांक gk104_sor_new(काष्ठा nvkm_disp *, पूर्णांक);
पूर्णांक gm107_sor_new(काष्ठा nvkm_disp *, पूर्णांक);
पूर्णांक gm200_sor_new(काष्ठा nvkm_disp *, पूर्णांक);
पूर्णांक gp100_sor_new(काष्ठा nvkm_disp *, पूर्णांक);

पूर्णांक gv100_sor_cnt(काष्ठा nvkm_disp *, अचिन्हित दीर्घ *);
पूर्णांक gv100_sor_new(काष्ठा nvkm_disp *, पूर्णांक);

पूर्णांक tu102_sor_new(काष्ठा nvkm_disp *, पूर्णांक);

पूर्णांक ga102_sor_new(काष्ठा nvkm_disp *, पूर्णांक);
#पूर्ण_अगर
