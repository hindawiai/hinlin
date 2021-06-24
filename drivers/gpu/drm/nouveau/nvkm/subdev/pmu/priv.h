<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVKM_PMU_PRIV_H__
#घोषणा __NVKM_PMU_PRIV_H__
#घोषणा nvkm_pmu(p) container_of((p), काष्ठा nvkm_pmu, subdev)
#समावेश <subdev/pmu.h>
#समावेश <subdev/pmu/fuc/os.h>
क्रमागत nvkm_acr_lsf_id;
काष्ठा nvkm_acr_lsfw;

काष्ठा nvkm_pmu_func अणु
	स्थिर काष्ठा nvkm_falcon_func *flcn;

	काष्ठा अणु
		u32 *data;
		u32  size;
	पूर्ण code;

	काष्ठा अणु
		u32 *data;
		u32  size;
	पूर्ण data;

	bool (*enabled)(काष्ठा nvkm_pmu *);
	व्योम (*reset)(काष्ठा nvkm_pmu *);
	पूर्णांक (*init)(काष्ठा nvkm_pmu *);
	व्योम (*fini)(काष्ठा nvkm_pmu *);
	व्योम (*पूर्णांकr)(काष्ठा nvkm_pmu *);
	पूर्णांक (*send)(काष्ठा nvkm_pmu *, u32 reply[2], u32 process,
		    u32 message, u32 data0, u32 data1);
	व्योम (*recv)(काष्ठा nvkm_pmu *);
	पूर्णांक (*iniपंचांगsg)(काष्ठा nvkm_pmu *);
	व्योम (*pgob)(काष्ठा nvkm_pmu *, bool);
पूर्ण;

बाह्य स्थिर काष्ठा nvkm_falcon_func gt215_pmu_flcn;
पूर्णांक gt215_pmu_init(काष्ठा nvkm_pmu *);
व्योम gt215_pmu_fini(काष्ठा nvkm_pmu *);
व्योम gt215_pmu_पूर्णांकr(काष्ठा nvkm_pmu *);
व्योम gt215_pmu_recv(काष्ठा nvkm_pmu *);
पूर्णांक gt215_pmu_send(काष्ठा nvkm_pmu *, u32[2], u32, u32, u32, u32);

bool gf100_pmu_enabled(काष्ठा nvkm_pmu *);
व्योम gf100_pmu_reset(काष्ठा nvkm_pmu *);

व्योम gk110_pmu_pgob(काष्ठा nvkm_pmu *, bool);

व्योम gm20b_pmu_acr_bld_patch(काष्ठा nvkm_acr *, u32, s64);
व्योम gm20b_pmu_acr_bld_ग_लिखो(काष्ठा nvkm_acr *, u32, काष्ठा nvkm_acr_lsfw *);
पूर्णांक gm20b_pmu_acr_boot(काष्ठा nvkm_falcon *);
पूर्णांक gm20b_pmu_acr_bootstrap_falcon(काष्ठा nvkm_falcon *, क्रमागत nvkm_acr_lsf_id);
व्योम gm20b_pmu_recv(काष्ठा nvkm_pmu *);
पूर्णांक gm20b_pmu_iniपंचांगsg(काष्ठा nvkm_pmu *);

काष्ठा nvkm_pmu_fwअगर अणु
	पूर्णांक version;
	पूर्णांक (*load)(काष्ठा nvkm_pmu *, पूर्णांक ver, स्थिर काष्ठा nvkm_pmu_fwअगर *);
	स्थिर काष्ठा nvkm_pmu_func *func;
	स्थिर काष्ठा nvkm_acr_lsf_func *acr;
पूर्ण;

पूर्णांक gf100_pmu_nofw(काष्ठा nvkm_pmu *, पूर्णांक, स्थिर काष्ठा nvkm_pmu_fwअगर *);
पूर्णांक gm200_pmu_nofw(काष्ठा nvkm_pmu *, पूर्णांक, स्थिर काष्ठा nvkm_pmu_fwअगर *);
पूर्णांक gm20b_pmu_load(काष्ठा nvkm_pmu *, पूर्णांक, स्थिर काष्ठा nvkm_pmu_fwअगर *);

पूर्णांक nvkm_pmu_ctor(स्थिर काष्ठा nvkm_pmu_fwअगर *, काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक,
		  काष्ठा nvkm_pmu *);
पूर्णांक nvkm_pmu_new_(स्थिर काष्ठा nvkm_pmu_fwअगर *, काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक,
		  काष्ठा nvkm_pmu **);
#पूर्ण_अगर
