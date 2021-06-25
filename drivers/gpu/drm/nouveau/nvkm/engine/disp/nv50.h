<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NV50_DISP_H__
#घोषणा __NV50_DISP_H__
#घोषणा nv50_disp(p) container_of((p), काष्ठा nv50_disp, base)
#समावेश "priv.h"
काष्ठा nvkm_head;

#समावेश <core/क्रमागत.h>

काष्ठा nv50_disp अणु
	स्थिर काष्ठा nv50_disp_func *func;
	काष्ठा nvkm_disp base;

	काष्ठा workqueue_काष्ठा *wq;
	काष्ठा work_काष्ठा supervisor;
	u32 super;

	काष्ठा nvkm_event uevent;

	काष्ठा अणु
		अचिन्हित दीर्घ mask;
		पूर्णांक nr;
	पूर्ण wndw, head, dac;

	काष्ठा अणु
		अचिन्हित दीर्घ mask;
		पूर्णांक nr;
		u32 lvdsconf;
	पूर्ण sor;

	काष्ठा अणु
		अचिन्हित दीर्घ mask;
		पूर्णांक nr;
		u8 type[3];
	पूर्ण pior;

	काष्ठा nvkm_gpuobj *inst;
	काष्ठा nvkm_ramht *ramht;

	काष्ठा nv50_disp_chan *chan[81];
पूर्ण;

व्योम nv50_disp_super_1(काष्ठा nv50_disp *);
व्योम nv50_disp_super_1_0(काष्ठा nv50_disp *, काष्ठा nvkm_head *);
व्योम nv50_disp_super_2_0(काष्ठा nv50_disp *, काष्ठा nvkm_head *);
व्योम nv50_disp_super_2_1(काष्ठा nv50_disp *, काष्ठा nvkm_head *);
व्योम nv50_disp_super_2_2(काष्ठा nv50_disp *, काष्ठा nvkm_head *);
व्योम nv50_disp_super_3_0(काष्ठा nv50_disp *, काष्ठा nvkm_head *);

पूर्णांक nv50_disp_new_(स्थिर काष्ठा nv50_disp_func *, काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक,
		   काष्ठा nvkm_disp **);

काष्ठा nv50_disp_func अणु
	पूर्णांक (*init)(काष्ठा nv50_disp *);
	व्योम (*fini)(काष्ठा nv50_disp *);
	व्योम (*पूर्णांकr)(काष्ठा nv50_disp *);
	व्योम (*पूर्णांकr_error)(काष्ठा nv50_disp *, पूर्णांक chid);

	स्थिर काष्ठा nvkm_event_func *uevent;
	व्योम (*super)(काष्ठा work_काष्ठा *);

	स्थिर काष्ठा nvkm_disp_oclass *root;

	काष्ठा अणु
		पूर्णांक (*cnt)(काष्ठा nvkm_disp *, अचिन्हित दीर्घ *mask);
		पूर्णांक (*new)(काष्ठा nvkm_disp *, पूर्णांक id);
	पूर्ण wndw, head, dac, sor, pior;

	u16 ramht_size;
पूर्ण;

पूर्णांक nv50_disp_init(काष्ठा nv50_disp *);
व्योम nv50_disp_fini(काष्ठा nv50_disp *);
व्योम nv50_disp_पूर्णांकr(काष्ठा nv50_disp *);
व्योम nv50_disp_super(काष्ठा work_काष्ठा *);
बाह्य स्थिर काष्ठा nvkm_क्रमागत nv50_disp_पूर्णांकr_error_type[];

पूर्णांक gf119_disp_init(काष्ठा nv50_disp *);
व्योम gf119_disp_fini(काष्ठा nv50_disp *);
व्योम gf119_disp_पूर्णांकr(काष्ठा nv50_disp *);
व्योम gf119_disp_super(काष्ठा work_काष्ठा *);
व्योम gf119_disp_पूर्णांकr_error(काष्ठा nv50_disp *, पूर्णांक);

व्योम gv100_disp_fini(काष्ठा nv50_disp *);
व्योम gv100_disp_पूर्णांकr(काष्ठा nv50_disp *);
व्योम gv100_disp_super(काष्ठा work_काष्ठा *);
पूर्णांक gv100_disp_wndw_cnt(काष्ठा nvkm_disp *, अचिन्हित दीर्घ *);

पूर्णांक tu102_disp_init(काष्ठा nv50_disp *);

व्योम nv50_disp_dpपंचांगds_war_2(काष्ठा nv50_disp *, काष्ठा dcb_output *);
व्योम nv50_disp_dpपंचांगds_war_3(काष्ठा nv50_disp *, काष्ठा dcb_output *);
व्योम nv50_disp_update_sppll1(काष्ठा nv50_disp *);

बाह्य स्थिर काष्ठा nvkm_event_func nv50_disp_chan_uevent;
पूर्णांक  nv50_disp_chan_uevent_ctor(काष्ठा nvkm_object *, व्योम *, u32,
				काष्ठा nvkm_notअगरy *);
व्योम nv50_disp_chan_uevent_send(काष्ठा nv50_disp *, पूर्णांक);

बाह्य स्थिर काष्ठा nvkm_event_func gf119_disp_chan_uevent;
बाह्य स्थिर काष्ठा nvkm_event_func gv100_disp_chan_uevent;
#पूर्ण_अगर
