<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVKM_PM_PRIV_H__
#घोषणा __NVKM_PM_PRIV_H__
#घोषणा nvkm_pm(p) container_of((p), काष्ठा nvkm_pm, engine)
#समावेश <engine/pm.h>

पूर्णांक nvkm_pm_ctor(स्थिर काष्ठा nvkm_pm_func *, काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक,
		 काष्ठा nvkm_pm *);

काष्ठा nvkm_pm_func अणु
	व्योम (*fini)(काष्ठा nvkm_pm *);
पूर्ण;

काष्ठा nvkm_perfctr अणु
	काष्ठा list_head head;
	u8 करोमुख्य;
	u8  संकेत[4];
	u64 source[4][8];
	पूर्णांक slot;
	u32 logic_op;
	u32 ctr;
पूर्ण;

काष्ठा nvkm_specmux अणु
	u32 mask;
	u8 shअगरt;
	स्थिर अक्षर *name;
	bool enable;
पूर्ण;

काष्ठा nvkm_specsrc अणु
	u32 addr;
	स्थिर काष्ठा nvkm_specmux *mux;
	स्थिर अक्षर *name;
पूर्ण;

काष्ठा nvkm_perfsrc अणु
	काष्ठा list_head head;
	अक्षर *name;
	u32 addr;
	u32 mask;
	u8 shअगरt;
	bool enable;
पूर्ण;

बाह्य स्थिर काष्ठा nvkm_specsrc nv50_zcull_sources[];
बाह्य स्थिर काष्ठा nvkm_specsrc nv50_zrop_sources[];
बाह्य स्थिर काष्ठा nvkm_specsrc g84_vfetch_sources[];
बाह्य स्थिर काष्ठा nvkm_specsrc gt200_crop_sources[];
बाह्य स्थिर काष्ठा nvkm_specsrc gt200_prop_sources[];
बाह्य स्थिर काष्ठा nvkm_specsrc gt200_tex_sources[];

काष्ठा nvkm_specsig अणु
	u8 संकेत;
	स्थिर अक्षर *name;
	स्थिर काष्ठा nvkm_specsrc *source;
पूर्ण;

काष्ठा nvkm_perfsig अणु
	स्थिर अक्षर *name;
	u8 source[8];
पूर्ण;

काष्ठा nvkm_specकरोm अणु
	u16 संकेत_nr;
	स्थिर काष्ठा nvkm_specsig *संकेत;
	स्थिर काष्ठा nvkm_funcकरोm *func;
पूर्ण;

#घोषणा nvkm_perfकरोm(p) container_of((p), काष्ठा nvkm_perfकरोm, object)
#समावेश <core/object.h>

काष्ठा nvkm_perfकरोm अणु
	काष्ठा nvkm_object object;
	काष्ठा nvkm_perfmon *perfmon;
	काष्ठा list_head head;
	काष्ठा list_head list;
	स्थिर काष्ठा nvkm_funcकरोm *func;
	काष्ठा nvkm_perfctr *ctr[4];
	अक्षर name[32];
	u32 addr;
	u8  mode;
	u32 clk;
	u16 संकेत_nr;
	काष्ठा nvkm_perfsig संकेत[];
पूर्ण;

काष्ठा nvkm_funcकरोm अणु
	व्योम (*init)(काष्ठा nvkm_pm *, काष्ठा nvkm_perfकरोm *,
		     काष्ठा nvkm_perfctr *);
	व्योम (*पढ़ो)(काष्ठा nvkm_pm *, काष्ठा nvkm_perfकरोm *,
		     काष्ठा nvkm_perfctr *);
	व्योम (*next)(काष्ठा nvkm_pm *, काष्ठा nvkm_perfकरोm *);
पूर्ण;

पूर्णांक nvkm_perfकरोm_new(काष्ठा nvkm_pm *, स्थिर अक्षर *, u32, u32, u32, u32,
		     स्थिर काष्ठा nvkm_specकरोm *);

#घोषणा nvkm_perfmon(p) container_of((p), काष्ठा nvkm_perfmon, object)

काष्ठा nvkm_perfmon अणु
	काष्ठा nvkm_object object;
	काष्ठा nvkm_pm *pm;
पूर्ण;
#पूर्ण_अगर
