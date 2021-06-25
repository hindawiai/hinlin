<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVKM_PMU_H__
#घोषणा __NVKM_PMU_H__
#समावेश <core/subdev.h>
#समावेश <core/falcon.h>

काष्ठा nvkm_pmu अणु
	स्थिर काष्ठा nvkm_pmu_func *func;
	काष्ठा nvkm_subdev subdev;
	काष्ठा nvkm_falcon falcon;

	काष्ठा nvkm_falcon_qmgr *qmgr;
	काष्ठा nvkm_falcon_cmdq *hpq;
	काष्ठा nvkm_falcon_cmdq *lpq;
	काष्ठा nvkm_falcon_msgq *msgq;
	bool iniपंचांगsg_received;

	काष्ठा completion wpr_पढ़ोy;

	काष्ठा अणु
		काष्ठा mutex mutex;
		u32 base;
		u32 size;
	पूर्ण send;

	काष्ठा अणु
		u32 base;
		u32 size;

		काष्ठा work_काष्ठा work;
		रुको_queue_head_t रुको;
		u32 process;
		u32 message;
		u32 data[2];
	पूर्ण recv;
पूर्ण;

पूर्णांक nvkm_pmu_send(काष्ठा nvkm_pmu *, u32 reply[2], u32 process,
		  u32 message, u32 data0, u32 data1);
व्योम nvkm_pmu_pgob(काष्ठा nvkm_pmu *, bool enable);
bool nvkm_pmu_fan_controlled(काष्ठा nvkm_device *);

पूर्णांक gt215_pmu_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_pmu **);
पूर्णांक gf100_pmu_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_pmu **);
पूर्णांक gf119_pmu_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_pmu **);
पूर्णांक gk104_pmu_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_pmu **);
पूर्णांक gk110_pmu_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_pmu **);
पूर्णांक gk208_pmu_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_pmu **);
पूर्णांक gk20a_pmu_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_pmu **);
पूर्णांक gm107_pmu_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_pmu **);
पूर्णांक gm200_pmu_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_pmu **);
पूर्णांक gm20b_pmu_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_pmu **);
पूर्णांक gp102_pmu_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_pmu **);
पूर्णांक gp10b_pmu_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_pmu **);

/* पूर्णांकerface to MEMX process running on PMU */
काष्ठा nvkm_memx;
पूर्णांक  nvkm_memx_init(काष्ठा nvkm_pmu *, काष्ठा nvkm_memx **);
पूर्णांक  nvkm_memx_fini(काष्ठा nvkm_memx **, bool exec);
व्योम nvkm_memx_wr32(काष्ठा nvkm_memx *, u32 addr, u32 data);
व्योम nvkm_memx_रुको(काष्ठा nvkm_memx *, u32 addr, u32 mask, u32 data, u32 nsec);
व्योम nvkm_memx_nsec(काष्ठा nvkm_memx *, u32 nsec);
व्योम nvkm_memx_रुको_vblank(काष्ठा nvkm_memx *);
व्योम nvkm_memx_train(काष्ठा nvkm_memx *);
पूर्णांक  nvkm_memx_train_result(काष्ठा nvkm_pmu *, u32 *, पूर्णांक);
व्योम nvkm_memx_block(काष्ठा nvkm_memx *);
व्योम nvkm_memx_unblock(काष्ठा nvkm_memx *);
#पूर्ण_अगर
