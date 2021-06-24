<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * governor.h - पूर्णांकernal header क्रम devfreq governors.
 *
 * Copyright (C) 2011 Samsung Electronics
 *	MyungJoo Ham <myungjoo.ham@samsung.com>
 *
 * This header is क्रम devfreq governors in drivers/devfreq/
 */

#अगर_अघोषित _GOVERNOR_H
#घोषणा _GOVERNOR_H

#समावेश <linux/devfreq.h>

#घोषणा DEVFREQ_NAME_LEN			16

#घोषणा to_devfreq(DEV)	container_of((DEV), काष्ठा devfreq, dev)

/* Devfreq events */
#घोषणा DEVFREQ_GOV_START			0x1
#घोषणा DEVFREQ_GOV_STOP			0x2
#घोषणा DEVFREQ_GOV_UPDATE_INTERVAL		0x3
#घोषणा DEVFREQ_GOV_SUSPEND			0x4
#घोषणा DEVFREQ_GOV_RESUME			0x5

#घोषणा DEVFREQ_MIN_FREQ			0
#घोषणा DEVFREQ_MAX_FREQ			अच_दीर्घ_उच्च

/*
 * Definition of the governor feature flags
 * - DEVFREQ_GOV_FLAG_IMMUTABLE
 *   : This governor is never changeable to other governors.
 * - DEVFREQ_GOV_FLAG_IRQ_DRIVEN
 *   : The devfreq won't schedule the work क्रम this governor.
 */
#घोषणा DEVFREQ_GOV_FLAG_IMMUTABLE			BIT(0)
#घोषणा DEVFREQ_GOV_FLAG_IRQ_DRIVEN			BIT(1)

/*
 * Definition of governor attribute flags except क्रम common sysfs attributes
 * - DEVFREQ_GOV_ATTR_POLLING_INTERVAL
 *   : Indicate polling_पूर्णांकerval sysfs attribute
 * - DEVFREQ_GOV_ATTR_TIMER
 *   : Indicate समयr sysfs attribute
 */
#घोषणा DEVFREQ_GOV_ATTR_POLLING_INTERVAL		BIT(0)
#घोषणा DEVFREQ_GOV_ATTR_TIMER				BIT(1)

/**
 * काष्ठा devfreq_governor - Devfreq policy governor
 * @node:		list node - contains रेजिस्टरed devfreq governors
 * @name:		Governor's name
 * @attrs:		Governor's sysfs attribute flags
 * @flags:		Governor's feature flags
 * @get_target_freq:	Returns desired operating frequency क्रम the device.
 *			Basically, get_target_freq will run
 *			devfreq_dev_profile.get_dev_status() to get the
 *			status of the device (load = busy_समय / total_समय).
 * @event_handler:      Callback क्रम devfreq core framework to notअगरy events
 *                      to governors. Events include per device governor
 *                      init and निकास, opp changes out of devfreq, suspend
 *                      and resume of per device devfreq during device idle.
 *
 * Note that the callbacks are called with devfreq->lock locked by devfreq.
 */
काष्ठा devfreq_governor अणु
	काष्ठा list_head node;

	स्थिर अक्षर name[DEVFREQ_NAME_LEN];
	स्थिर u64 attrs;
	स्थिर u64 flags;
	पूर्णांक (*get_target_freq)(काष्ठा devfreq *this, अचिन्हित दीर्घ *freq);
	पूर्णांक (*event_handler)(काष्ठा devfreq *devfreq,
				अचिन्हित पूर्णांक event, व्योम *data);
पूर्ण;

व्योम devfreq_monitor_start(काष्ठा devfreq *devfreq);
व्योम devfreq_monitor_stop(काष्ठा devfreq *devfreq);
व्योम devfreq_monitor_suspend(काष्ठा devfreq *devfreq);
व्योम devfreq_monitor_resume(काष्ठा devfreq *devfreq);
व्योम devfreq_update_पूर्णांकerval(काष्ठा devfreq *devfreq, अचिन्हित पूर्णांक *delay);

पूर्णांक devfreq_add_governor(काष्ठा devfreq_governor *governor);
पूर्णांक devfreq_हटाओ_governor(काष्ठा devfreq_governor *governor);

पूर्णांक devfreq_update_status(काष्ठा devfreq *devfreq, अचिन्हित दीर्घ freq);
पूर्णांक devfreq_update_target(काष्ठा devfreq *devfreq, अचिन्हित दीर्घ freq);

अटल अंतरभूत पूर्णांक devfreq_update_stats(काष्ठा devfreq *df)
अणु
	अगर (!df->profile->get_dev_status)
		वापस -EINVAL;

	वापस df->profile->get_dev_status(df->dev.parent, &df->last_status);
पूर्ण
#पूर्ण_अगर /* _GOVERNOR_H */
