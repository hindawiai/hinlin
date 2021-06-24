<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित LINUX_MMC_HSQ_H
#घोषणा LINUX_MMC_HSQ_H

काष्ठा hsq_slot अणु
	काष्ठा mmc_request *mrq;
पूर्ण;

काष्ठा mmc_hsq अणु
	काष्ठा mmc_host *mmc;
	काष्ठा mmc_request *mrq;
	रुको_queue_head_t रुको_queue;
	काष्ठा hsq_slot *slot;
	spinlock_t lock;
	काष्ठा work_काष्ठा retry_work;

	पूर्णांक next_tag;
	पूर्णांक num_slots;
	पूर्णांक qcnt;

	bool enabled;
	bool रुकोing_क्रम_idle;
	bool recovery_halt;
पूर्ण;

पूर्णांक mmc_hsq_init(काष्ठा mmc_hsq *hsq, काष्ठा mmc_host *mmc);
व्योम mmc_hsq_suspend(काष्ठा mmc_host *mmc);
पूर्णांक mmc_hsq_resume(काष्ठा mmc_host *mmc);
bool mmc_hsq_finalize_request(काष्ठा mmc_host *mmc, काष्ठा mmc_request *mrq);

#पूर्ण_अगर
