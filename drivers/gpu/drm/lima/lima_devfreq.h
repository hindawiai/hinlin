<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright 2020 Martin Blumenstingl <martin.blumenstingl@googlemail.com> */

#अगर_अघोषित __LIMA_DEVFREQ_H__
#घोषणा __LIMA_DEVFREQ_H__

#समावेश <linux/devfreq.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/kसमय.स>

काष्ठा devfreq;
काष्ठा thermal_cooling_device;

काष्ठा lima_device;

काष्ठा lima_devfreq अणु
	काष्ठा devfreq *devfreq;
	काष्ठा thermal_cooling_device *cooling;
	काष्ठा devfreq_simple_ondemand_data gov_data;

	kसमय_प्रकार busy_समय;
	kसमय_प्रकार idle_समय;
	kसमय_प्रकार समय_last_update;
	पूर्णांक busy_count;
	/*
	 * Protect busy_समय, idle_समय, समय_last_update and busy_count
	 * because these can be updated concurrently, क्रम example by the GP
	 * and PP पूर्णांकerrupts.
	 */
	spinlock_t lock;
पूर्ण;

पूर्णांक lima_devfreq_init(काष्ठा lima_device *ldev);
व्योम lima_devfreq_fini(काष्ठा lima_device *ldev);

व्योम lima_devfreq_record_busy(काष्ठा lima_devfreq *devfreq);
व्योम lima_devfreq_record_idle(काष्ठा lima_devfreq *devfreq);

पूर्णांक lima_devfreq_resume(काष्ठा lima_devfreq *devfreq);
पूर्णांक lima_devfreq_suspend(काष्ठा lima_devfreq *devfreq);

#पूर्ण_अगर
