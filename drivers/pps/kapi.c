<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * kernel API
 *
 * Copyright (C) 2005-2009   Roकरोlfo Giometti <giometti@linux.it>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/sched.h>
#समावेश <linux/समय.स>
#समावेश <linux/समयx.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/fs.h>
#समावेश <linux/pps_kernel.h>
#समावेश <linux/slab.h>

#समावेश "kc.h"

/*
 * Local functions
 */

अटल व्योम pps_add_offset(काष्ठा pps_kसमय *ts, काष्ठा pps_kसमय *offset)
अणु
	ts->nsec += offset->nsec;
	जबतक (ts->nsec >= NSEC_PER_SEC) अणु
		ts->nsec -= NSEC_PER_SEC;
		ts->sec++;
	पूर्ण
	जबतक (ts->nsec < 0) अणु
		ts->nsec += NSEC_PER_SEC;
		ts->sec--;
	पूर्ण
	ts->sec += offset->sec;
पूर्ण

अटल व्योम pps_echo_client_शेष(काष्ठा pps_device *pps, पूर्णांक event,
		व्योम *data)
अणु
	dev_info(pps->dev, "echo %s %s\n",
		event & PPS_CAPTUREASSERT ? "assert" : "",
		event & PPS_CAPTURECLEAR ? "clear" : "");
पूर्ण

/*
 * Exported functions
 */

/* pps_रेजिस्टर_source - add a PPS source in the प्रणाली
 * @info: the PPS info काष्ठा
 * @शेष_params: the शेष PPS parameters of the new source
 *
 * This function is used to add a new PPS source in the प्रणाली. The new
 * source is described by info's fields and it will have, as शेष PPS
 * parameters, the ones specअगरied पूर्णांकo शेष_params.
 *
 * The function वापसs, in हाल of success, the PPS device. Otherwise
 * ERR_PTR(त्रुटि_सं).
 */

काष्ठा pps_device *pps_रेजिस्टर_source(काष्ठा pps_source_info *info,
		पूर्णांक शेष_params)
अणु
	काष्ठा pps_device *pps;
	पूर्णांक err;

	/* Sanity checks */
	अगर ((info->mode & शेष_params) != शेष_params) अणु
		pr_err("%s: unsupported default parameters\n",
					info->name);
		err = -EINVAL;
		जाओ pps_रेजिस्टर_source_निकास;
	पूर्ण
	अगर ((info->mode & (PPS_TSFMT_TSPEC | PPS_TSFMT_NTPFP)) == 0) अणु
		pr_err("%s: unspecified time format\n",
					info->name);
		err = -EINVAL;
		जाओ pps_रेजिस्टर_source_निकास;
	पूर्ण

	/* Allocate memory क्रम the new PPS source काष्ठा */
	pps = kzalloc(माप(काष्ठा pps_device), GFP_KERNEL);
	अगर (pps == शून्य) अणु
		err = -ENOMEM;
		जाओ pps_रेजिस्टर_source_निकास;
	पूर्ण

	/* These initializations must be करोne beक्रमe calling idr_alloc()
	 * in order to aव्योम reces पूर्णांकo pps_event().
	 */
	pps->params.api_version = PPS_API_VERS;
	pps->params.mode = शेष_params;
	pps->info = *info;

	/* check क्रम शेष echo function */
	अगर ((pps->info.mode & (PPS_ECHOASSERT | PPS_ECHOCLEAR)) &&
			pps->info.echo == शून्य)
		pps->info.echo = pps_echo_client_शेष;

	init_रुकोqueue_head(&pps->queue);
	spin_lock_init(&pps->lock);

	/* Create the अक्षर device */
	err = pps_रेजिस्टर_cdev(pps);
	अगर (err < 0) अणु
		pr_err("%s: unable to create char device\n",
					info->name);
		जाओ kमुक्त_pps;
	पूर्ण

	dev_info(pps->dev, "new PPS source %s\n", info->name);

	वापस pps;

kमुक्त_pps:
	kमुक्त(pps);

pps_रेजिस्टर_source_निकास:
	pr_err("%s: unable to register source\n", info->name);

	वापस ERR_PTR(err);
पूर्ण
EXPORT_SYMBOL(pps_रेजिस्टर_source);

/* pps_unरेजिस्टर_source - हटाओ a PPS source from the प्रणाली
 * @pps: the PPS source
 *
 * This function is used to हटाओ a previously रेजिस्टरed PPS source from
 * the प्रणाली.
 */

व्योम pps_unरेजिस्टर_source(काष्ठा pps_device *pps)
अणु
	pps_kc_हटाओ(pps);
	pps_unरेजिस्टर_cdev(pps);

	/* करोn't have to kमुक्त(pps) here because it will be करोne on
	 * device deकाष्ठाion */
पूर्ण
EXPORT_SYMBOL(pps_unरेजिस्टर_source);

/* pps_event - रेजिस्टर a PPS event पूर्णांकo the प्रणाली
 * @pps: the PPS device
 * @ts: the event बारtamp
 * @event: the event type
 * @data: userdef poपूर्णांकer
 *
 * This function is used by each PPS client in order to रेजिस्टर a new
 * PPS event पूर्णांकo the प्रणाली (it's usually called inside an IRQ handler).
 *
 * If an echo function is associated with the PPS device it will be called
 * as:
 *	pps->info.echo(pps, event, data);
 */
व्योम pps_event(काष्ठा pps_device *pps, काष्ठा pps_event_समय *ts, पूर्णांक event,
		व्योम *data)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक captured = 0;
	काष्ठा pps_kसमय ts_real = अणु .sec = 0, .nsec = 0, .flags = 0 पूर्ण;

	/* check event type */
	BUG_ON((event & (PPS_CAPTUREASSERT | PPS_CAPTURECLEAR)) == 0);

	dev_dbg(pps->dev, "PPS event at %lld.%09ld\n",
			(s64)ts->ts_real.tv_sec, ts->ts_real.tv_nsec);

	बारpec_to_pps_kसमय(&ts_real, ts->ts_real);

	spin_lock_irqsave(&pps->lock, flags);

	/* Must call the echo function? */
	अगर ((pps->params.mode & (PPS_ECHOASSERT | PPS_ECHOCLEAR)))
		pps->info.echo(pps, event, data);

	/* Check the event */
	pps->current_mode = pps->params.mode;
	अगर (event & pps->params.mode & PPS_CAPTUREASSERT) अणु
		/* We have to add an offset? */
		अगर (pps->params.mode & PPS_OFFSETASSERT)
			pps_add_offset(&ts_real,
					&pps->params.निश्चित_off_tu);

		/* Save the समय stamp */
		pps->निश्चित_tu = ts_real;
		pps->निश्चित_sequence++;
		dev_dbg(pps->dev, "capture assert seq #%u\n",
			pps->निश्चित_sequence);

		captured = ~0;
	पूर्ण
	अगर (event & pps->params.mode & PPS_CAPTURECLEAR) अणु
		/* We have to add an offset? */
		अगर (pps->params.mode & PPS_OFFSETCLEAR)
			pps_add_offset(&ts_real,
					&pps->params.clear_off_tu);

		/* Save the समय stamp */
		pps->clear_tu = ts_real;
		pps->clear_sequence++;
		dev_dbg(pps->dev, "capture clear seq #%u\n",
			pps->clear_sequence);

		captured = ~0;
	पूर्ण

	pps_kc_event(pps, ts, event);

	/* Wake up अगर captured something */
	अगर (captured) अणु
		pps->last_ev++;
		wake_up_पूर्णांकerruptible_all(&pps->queue);

		समाप्त_fasync(&pps->async_queue, SIGIO, POLL_IN);
	पूर्ण

	spin_unlock_irqrestore(&pps->lock, flags);
पूर्ण
EXPORT_SYMBOL(pps_event);
