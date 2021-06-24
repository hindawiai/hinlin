<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright 2019 Collabora ltd. */

#अगर_अघोषित __PANFROST_DEVFREQ_H__
#घोषणा __PANFROST_DEVFREQ_H__

#समावेश <linux/devfreq.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/kसमय.स>

काष्ठा devfreq;
काष्ठा thermal_cooling_device;

काष्ठा panfrost_device;

काष्ठा panfrost_devfreq अणु
	काष्ठा devfreq *devfreq;
	काष्ठा thermal_cooling_device *cooling;
	काष्ठा devfreq_simple_ondemand_data gov_data;
	bool opp_of_table_added;

	kसमय_प्रकार busy_समय;
	kसमय_प्रकार idle_समय;
	kसमय_प्रकार समय_last_update;
	पूर्णांक busy_count;
	/*
	 * Protect busy_समय, idle_समय, समय_last_update and busy_count
	 * because these can be updated concurrently between multiple jobs.
	 */
	spinlock_t lock;
पूर्ण;

पूर्णांक panfrost_devfreq_init(काष्ठा panfrost_device *pfdev);
व्योम panfrost_devfreq_fini(काष्ठा panfrost_device *pfdev);

व्योम panfrost_devfreq_resume(काष्ठा panfrost_device *pfdev);
व्योम panfrost_devfreq_suspend(काष्ठा panfrost_device *pfdev);

व्योम panfrost_devfreq_record_busy(काष्ठा panfrost_devfreq *devfreq);
व्योम panfrost_devfreq_record_idle(काष्ठा panfrost_devfreq *devfreq);

#पूर्ण_अगर /* __PANFROST_DEVFREQ_H__ */
