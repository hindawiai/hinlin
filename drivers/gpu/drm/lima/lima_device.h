<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR MIT */
/* Copyright 2018-2019 Qiang Yu <yuq825@gmail.com> */

#अगर_अघोषित __LIMA_DEVICE_H__
#घोषणा __LIMA_DEVICE_H__

#समावेश <drm/drm_device.h>
#समावेश <linux/delay.h>
#समावेश <linux/list.h>
#समावेश <linux/mutex.h>

#समावेश "lima_sched.h"
#समावेश "lima_dump.h"
#समावेश "lima_devfreq.h"

क्रमागत lima_gpu_id अणु
	lima_gpu_mali400 = 0,
	lima_gpu_mali450,
	lima_gpu_num,
पूर्ण;

क्रमागत lima_ip_id अणु
	lima_ip_pmu,
	lima_ip_gpmmu,
	lima_ip_ppmmu0,
	lima_ip_ppmmu1,
	lima_ip_ppmmu2,
	lima_ip_ppmmu3,
	lima_ip_ppmmu4,
	lima_ip_ppmmu5,
	lima_ip_ppmmu6,
	lima_ip_ppmmu7,
	lima_ip_gp,
	lima_ip_pp0,
	lima_ip_pp1,
	lima_ip_pp2,
	lima_ip_pp3,
	lima_ip_pp4,
	lima_ip_pp5,
	lima_ip_pp6,
	lima_ip_pp7,
	lima_ip_l2_cache0,
	lima_ip_l2_cache1,
	lima_ip_l2_cache2,
	lima_ip_dlbu,
	lima_ip_bcast,
	lima_ip_pp_bcast,
	lima_ip_ppmmu_bcast,
	lima_ip_num,
पूर्ण;

काष्ठा lima_device;

काष्ठा lima_ip अणु
	काष्ठा lima_device *dev;
	क्रमागत lima_ip_id id;
	bool present;

	व्योम __iomem *iomem;
	पूर्णांक irq;

	जोड़ अणु
		/* gp/pp */
		bool async_reset;
		/* l2 cache */
		spinlock_t lock;
		/* pmu/bcast */
		u32 mask;
	पूर्ण data;
पूर्ण;

क्रमागत lima_pipe_id अणु
	lima_pipe_gp,
	lima_pipe_pp,
	lima_pipe_num,
पूर्ण;

काष्ठा lima_device अणु
	काष्ठा device *dev;
	काष्ठा drm_device *ddev;

	क्रमागत lima_gpu_id id;
	u32 gp_version;
	u32 pp_version;
	पूर्णांक num_pp;

	व्योम __iomem *iomem;
	काष्ठा clk *clk_bus;
	काष्ठा clk *clk_gpu;
	काष्ठा reset_control *reset;
	काष्ठा regulator *regulator;

	काष्ठा lima_ip ip[lima_ip_num];
	काष्ठा lima_sched_pipe pipe[lima_pipe_num];

	काष्ठा lima_vm *empty_vm;
	uपूर्णांक64_t बहु_शुरू;
	uपूर्णांक64_t बहु_पूर्ण;

	u32 *dlbu_cpu;
	dma_addr_t dlbu_dma;

	काष्ठा lima_devfreq devfreq;

	/* debug info */
	काष्ठा lima_dump_head dump;
	काष्ठा list_head error_task_list;
	काष्ठा mutex error_task_list_lock;
पूर्ण;

अटल अंतरभूत काष्ठा lima_device *
to_lima_dev(काष्ठा drm_device *dev)
अणु
	वापस dev->dev_निजी;
पूर्ण

पूर्णांक lima_device_init(काष्ठा lima_device *ldev);
व्योम lima_device_fini(काष्ठा lima_device *ldev);

स्थिर अक्षर *lima_ip_name(काष्ठा lima_ip *ip);

प्रकार पूर्णांक (*lima_poll_func_t)(काष्ठा lima_ip *);

अटल अंतरभूत पूर्णांक lima_poll_समयout(काष्ठा lima_ip *ip, lima_poll_func_t func,
				    पूर्णांक sleep_us, पूर्णांक समयout_us)
अणु
	kसमय_प्रकार समयout = kसमय_add_us(kसमय_get(), समयout_us);

	might_sleep_अगर(sleep_us);
	जबतक (1) अणु
		अगर (func(ip))
			वापस 0;

		अगर (समयout_us && kसमय_compare(kसमय_get(), समयout) > 0)
			वापस -ETIMEDOUT;

		अगर (sleep_us)
			usleep_range((sleep_us >> 2) + 1, sleep_us);
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक lima_device_suspend(काष्ठा device *dev);
पूर्णांक lima_device_resume(काष्ठा device *dev);

#पूर्ण_अगर
