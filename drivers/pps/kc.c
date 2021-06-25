<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * PPS kernel consumer API
 *
 * Copyright (C) 2009-2010   Alexander Gordeev <lasaine@lvk.cs.msu.su>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/init.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/pps_kernel.h>

#समावेश "kc.h"

/*
 * Global variables
 */

/* state variables to bind kernel consumer */
अटल DEFINE_SPINLOCK(pps_kc_hardpps_lock);
/* PPS API (RFC 2783): current source and mode क्रम kernel consumer */
अटल काष्ठा pps_device *pps_kc_hardpps_dev;	/* unique poपूर्णांकer to device */
अटल पूर्णांक pps_kc_hardpps_mode;		/* mode bits क्रम kernel consumer */

/* pps_kc_bind - control PPS kernel consumer binding
 * @pps: the PPS source
 * @bind_args: kernel consumer bind parameters
 *
 * This function is used to bind or unbind PPS kernel consumer according to
 * supplied parameters. Should not be called in पूर्णांकerrupt context.
 */
पूर्णांक pps_kc_bind(काष्ठा pps_device *pps, काष्ठा pps_bind_args *bind_args)
अणु
	/* Check अगर another consumer is alपढ़ोy bound */
	spin_lock_irq(&pps_kc_hardpps_lock);

	अगर (bind_args->edge == 0)
		अगर (pps_kc_hardpps_dev == pps) अणु
			pps_kc_hardpps_mode = 0;
			pps_kc_hardpps_dev = शून्य;
			spin_unlock_irq(&pps_kc_hardpps_lock);
			dev_info(pps->dev, "unbound kernel"
					" consumer\n");
		पूर्ण अन्यथा अणु
			spin_unlock_irq(&pps_kc_hardpps_lock);
			dev_err(pps->dev, "selected kernel consumer"
					" is not bound\n");
			वापस -EINVAL;
		पूर्ण
	अन्यथा
		अगर (pps_kc_hardpps_dev == शून्य ||
				pps_kc_hardpps_dev == pps) अणु
			pps_kc_hardpps_mode = bind_args->edge;
			pps_kc_hardpps_dev = pps;
			spin_unlock_irq(&pps_kc_hardpps_lock);
			dev_info(pps->dev, "bound kernel consumer: "
				"edge=0x%x\n", bind_args->edge);
		पूर्ण अन्यथा अणु
			spin_unlock_irq(&pps_kc_hardpps_lock);
			dev_err(pps->dev, "another kernel consumer"
					" is already bound\n");
			वापस -EINVAL;
		पूर्ण

	वापस 0;
पूर्ण

/* pps_kc_हटाओ - unbind kernel consumer on PPS source removal
 * @pps: the PPS source
 *
 * This function is used to disable kernel consumer on PPS source removal
 * अगर this source was bound to PPS kernel consumer. Can be called on any
 * source safely. Should not be called in पूर्णांकerrupt context.
 */
व्योम pps_kc_हटाओ(काष्ठा pps_device *pps)
अणु
	spin_lock_irq(&pps_kc_hardpps_lock);
	अगर (pps == pps_kc_hardpps_dev) अणु
		pps_kc_hardpps_mode = 0;
		pps_kc_hardpps_dev = शून्य;
		spin_unlock_irq(&pps_kc_hardpps_lock);
		dev_info(pps->dev, "unbound kernel consumer"
				" on device removal\n");
	पूर्ण अन्यथा
		spin_unlock_irq(&pps_kc_hardpps_lock);
पूर्ण

/* pps_kc_event - call hardpps() on PPS event
 * @pps: the PPS source
 * @ts: PPS event बारtamp
 * @event: PPS event edge
 *
 * This function calls hardpps() when an event from bound PPS source occurs.
 */
व्योम pps_kc_event(काष्ठा pps_device *pps, काष्ठा pps_event_समय *ts,
		पूर्णांक event)
अणु
	अचिन्हित दीर्घ flags;

	/* Pass some events to kernel consumer अगर activated */
	spin_lock_irqsave(&pps_kc_hardpps_lock, flags);
	अगर (pps == pps_kc_hardpps_dev && event & pps_kc_hardpps_mode)
		hardpps(&ts->ts_real, &ts->ts_raw);
	spin_unlock_irqrestore(&pps_kc_hardpps_lock, flags);
पूर्ण
