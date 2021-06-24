<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * PTP 1588 घड़ी support - अक्षरacter device implementation.
 *
 * Copyright (C) 2010 OMICRON electronics GmbH
 */
#समावेश <linux/module.h>
#समावेश <linux/posix-घड़ी.h>
#समावेश <linux/poll.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/समयkeeping.h>

#समावेश <linux/nospec.h>

#समावेश "ptp_private.h"

अटल पूर्णांक ptp_disable_pinfunc(काष्ठा ptp_घड़ी_info *ops,
			       क्रमागत ptp_pin_function func, अचिन्हित पूर्णांक chan)
अणु
	काष्ठा ptp_घड़ी_request rq;
	पूर्णांक err = 0;

	स_रखो(&rq, 0, माप(rq));

	चयन (func) अणु
	हाल PTP_PF_NONE:
		अवरोध;
	हाल PTP_PF_EXTTS:
		rq.type = PTP_CLK_REQ_EXTTS;
		rq.extts.index = chan;
		err = ops->enable(ops, &rq, 0);
		अवरोध;
	हाल PTP_PF_PEROUT:
		rq.type = PTP_CLK_REQ_PEROUT;
		rq.perout.index = chan;
		err = ops->enable(ops, &rq, 0);
		अवरोध;
	हाल PTP_PF_PHYSYNC:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस err;
पूर्ण

पूर्णांक ptp_set_pinfunc(काष्ठा ptp_घड़ी *ptp, अचिन्हित पूर्णांक pin,
		    क्रमागत ptp_pin_function func, अचिन्हित पूर्णांक chan)
अणु
	काष्ठा ptp_घड़ी_info *info = ptp->info;
	काष्ठा ptp_pin_desc *pin1 = शून्य, *pin2 = &info->pin_config[pin];
	अचिन्हित पूर्णांक i;

	/* Check to see अगर any other pin previously had this function. */
	क्रम (i = 0; i < info->n_pins; i++) अणु
		अगर (info->pin_config[i].func == func &&
		    info->pin_config[i].chan == chan) अणु
			pin1 = &info->pin_config[i];
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (pin1 && i == pin)
		वापस 0;

	/* Check the desired function and channel. */
	चयन (func) अणु
	हाल PTP_PF_NONE:
		अवरोध;
	हाल PTP_PF_EXTTS:
		अगर (chan >= info->n_ext_ts)
			वापस -EINVAL;
		अवरोध;
	हाल PTP_PF_PEROUT:
		अगर (chan >= info->n_per_out)
			वापस -EINVAL;
		अवरोध;
	हाल PTP_PF_PHYSYNC:
		अगर (chan != 0)
			वापस -EINVAL;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (info->verअगरy(info, pin, func, chan)) अणु
		pr_err("driver cannot use function %u on pin %u\n", func, chan);
		वापस -EOPNOTSUPP;
	पूर्ण

	/* Disable whatever function was previously asचिन्हित. */
	अगर (pin1) अणु
		ptp_disable_pinfunc(info, func, chan);
		pin1->func = PTP_PF_NONE;
		pin1->chan = 0;
	पूर्ण
	ptp_disable_pinfunc(info, pin2->func, pin2->chan);
	pin2->func = func;
	pin2->chan = chan;

	वापस 0;
पूर्ण

पूर्णांक ptp_खोलो(काष्ठा posix_घड़ी *pc, भ_शेषe_t भ_शेषe)
अणु
	वापस 0;
पूर्ण

दीर्घ ptp_ioctl(काष्ठा posix_घड़ी *pc, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा ptp_घड़ी *ptp = container_of(pc, काष्ठा ptp_घड़ी, घड़ी);
	काष्ठा ptp_sys_offset_extended *extoff = शून्य;
	काष्ठा ptp_sys_offset_precise precise_offset;
	काष्ठा प्रणाली_device_crosststamp xtstamp;
	काष्ठा ptp_घड़ी_info *ops = ptp->info;
	काष्ठा ptp_sys_offset *sysoff = शून्य;
	काष्ठा ptp_प्रणाली_बारtamp sts;
	काष्ठा ptp_घड़ी_request req;
	काष्ठा ptp_घड़ी_caps caps;
	काष्ठा ptp_घड़ी_प्रकारime *pct;
	अचिन्हित पूर्णांक i, pin_index;
	काष्ठा ptp_pin_desc pd;
	काष्ठा बारpec64 ts;
	पूर्णांक enable, err = 0;

	चयन (cmd) अणु

	हाल PTP_CLOCK_GETCAPS:
	हाल PTP_CLOCK_GETCAPS2:
		स_रखो(&caps, 0, माप(caps));

		caps.max_adj = ptp->info->max_adj;
		caps.n_alarm = ptp->info->n_alarm;
		caps.n_ext_ts = ptp->info->n_ext_ts;
		caps.n_per_out = ptp->info->n_per_out;
		caps.pps = ptp->info->pps;
		caps.n_pins = ptp->info->n_pins;
		caps.cross_बारtamping = ptp->info->अ_लोrosststamp != शून्य;
		caps.adjust_phase = ptp->info->adjphase != शून्य;
		अगर (copy_to_user((व्योम __user *)arg, &caps, माप(caps)))
			err = -EFAULT;
		अवरोध;

	हाल PTP_EXTTS_REQUEST:
	हाल PTP_EXTTS_REQUEST2:
		स_रखो(&req, 0, माप(req));

		अगर (copy_from_user(&req.extts, (व्योम __user *)arg,
				   माप(req.extts))) अणु
			err = -EFAULT;
			अवरोध;
		पूर्ण
		अगर (cmd == PTP_EXTTS_REQUEST2) अणु
			/* Tell the drivers to check the flags carefully. */
			req.extts.flags |= PTP_STRICT_FLAGS;
			/* Make sure no reserved bit is set. */
			अगर ((req.extts.flags & ~PTP_EXTTS_VALID_FLAGS) ||
			    req.extts.rsv[0] || req.extts.rsv[1]) अणु
				err = -EINVAL;
				अवरोध;
			पूर्ण
			/* Ensure one of the rising/falling edge bits is set. */
			अगर ((req.extts.flags & PTP_ENABLE_FEATURE) &&
			    (req.extts.flags & PTP_EXTTS_EDGES) == 0) अणु
				err = -EINVAL;
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अगर (cmd == PTP_EXTTS_REQUEST) अणु
			req.extts.flags &= PTP_EXTTS_V1_VALID_FLAGS;
			req.extts.rsv[0] = 0;
			req.extts.rsv[1] = 0;
		पूर्ण
		अगर (req.extts.index >= ops->n_ext_ts) अणु
			err = -EINVAL;
			अवरोध;
		पूर्ण
		req.type = PTP_CLK_REQ_EXTTS;
		enable = req.extts.flags & PTP_ENABLE_FEATURE ? 1 : 0;
		अगर (mutex_lock_पूर्णांकerruptible(&ptp->pincfg_mux))
			वापस -ERESTARTSYS;
		err = ops->enable(ops, &req, enable);
		mutex_unlock(&ptp->pincfg_mux);
		अवरोध;

	हाल PTP_PEROUT_REQUEST:
	हाल PTP_PEROUT_REQUEST2:
		स_रखो(&req, 0, माप(req));

		अगर (copy_from_user(&req.perout, (व्योम __user *)arg,
				   माप(req.perout))) अणु
			err = -EFAULT;
			अवरोध;
		पूर्ण
		अगर (cmd == PTP_PEROUT_REQUEST2) अणु
			काष्ठा ptp_perout_request *perout = &req.perout;

			अगर (perout->flags & ~PTP_PEROUT_VALID_FLAGS) अणु
				err = -EINVAL;
				अवरोध;
			पूर्ण
			/*
			 * The "on" field has undefined meaning अगर
			 * PTP_PEROUT_DUTY_CYCLE isn't set, we must still treat
			 * it as reserved, which must be set to zero.
			 */
			अगर (!(perout->flags & PTP_PEROUT_DUTY_CYCLE) &&
			    (perout->rsv[0] || perout->rsv[1] ||
			     perout->rsv[2] || perout->rsv[3])) अणु
				err = -EINVAL;
				अवरोध;
			पूर्ण
			अगर (perout->flags & PTP_PEROUT_DUTY_CYCLE) अणु
				/* The duty cycle must be subunitary. */
				अगर (perout->on.sec > perout->period.sec ||
				    (perout->on.sec == perout->period.sec &&
				     perout->on.nsec > perout->period.nsec)) अणु
					err = -दुस्फल;
					अवरोध;
				पूर्ण
			पूर्ण
			अगर (perout->flags & PTP_PEROUT_PHASE) अणु
				/*
				 * The phase should be specअगरied modulo the
				 * period, thereक्रमe anything equal or larger
				 * than 1 period is invalid.
				 */
				अगर (perout->phase.sec > perout->period.sec ||
				    (perout->phase.sec == perout->period.sec &&
				     perout->phase.nsec >= perout->period.nsec)) अणु
					err = -दुस्फल;
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अगर (cmd == PTP_PEROUT_REQUEST) अणु
			req.perout.flags &= PTP_PEROUT_V1_VALID_FLAGS;
			req.perout.rsv[0] = 0;
			req.perout.rsv[1] = 0;
			req.perout.rsv[2] = 0;
			req.perout.rsv[3] = 0;
		पूर्ण
		अगर (req.perout.index >= ops->n_per_out) अणु
			err = -EINVAL;
			अवरोध;
		पूर्ण
		req.type = PTP_CLK_REQ_PEROUT;
		enable = req.perout.period.sec || req.perout.period.nsec;
		अगर (mutex_lock_पूर्णांकerruptible(&ptp->pincfg_mux))
			वापस -ERESTARTSYS;
		err = ops->enable(ops, &req, enable);
		mutex_unlock(&ptp->pincfg_mux);
		अवरोध;

	हाल PTP_ENABLE_PPS:
	हाल PTP_ENABLE_PPS2:
		स_रखो(&req, 0, माप(req));

		अगर (!capable(CAP_SYS_TIME))
			वापस -EPERM;
		req.type = PTP_CLK_REQ_PPS;
		enable = arg ? 1 : 0;
		अगर (mutex_lock_पूर्णांकerruptible(&ptp->pincfg_mux))
			वापस -ERESTARTSYS;
		err = ops->enable(ops, &req, enable);
		mutex_unlock(&ptp->pincfg_mux);
		अवरोध;

	हाल PTP_SYS_OFFSET_PRECISE:
	हाल PTP_SYS_OFFSET_PRECISE2:
		अगर (!ptp->info->अ_लोrosststamp) अणु
			err = -EOPNOTSUPP;
			अवरोध;
		पूर्ण
		err = ptp->info->अ_लोrosststamp(ptp->info, &xtstamp);
		अगर (err)
			अवरोध;

		स_रखो(&precise_offset, 0, माप(precise_offset));
		ts = kसमय_प्रकारo_बारpec64(xtstamp.device);
		precise_offset.device.sec = ts.tv_sec;
		precise_offset.device.nsec = ts.tv_nsec;
		ts = kसमय_प्रकारo_बारpec64(xtstamp.sys_realसमय);
		precise_offset.sys_realसमय.sec = ts.tv_sec;
		precise_offset.sys_realसमय.nsec = ts.tv_nsec;
		ts = kसमय_प्रकारo_बारpec64(xtstamp.sys_monoraw);
		precise_offset.sys_monoraw.sec = ts.tv_sec;
		precise_offset.sys_monoraw.nsec = ts.tv_nsec;
		अगर (copy_to_user((व्योम __user *)arg, &precise_offset,
				 माप(precise_offset)))
			err = -EFAULT;
		अवरोध;

	हाल PTP_SYS_OFFSET_EXTENDED:
	हाल PTP_SYS_OFFSET_EXTENDED2:
		अगर (!ptp->info->समय_लोx64) अणु
			err = -EOPNOTSUPP;
			अवरोध;
		पूर्ण
		extoff = memdup_user((व्योम __user *)arg, माप(*extoff));
		अगर (IS_ERR(extoff)) अणु
			err = PTR_ERR(extoff);
			extoff = शून्य;
			अवरोध;
		पूर्ण
		अगर (extoff->n_samples > PTP_MAX_SAMPLES
		    || extoff->rsv[0] || extoff->rsv[1] || extoff->rsv[2]) अणु
			err = -EINVAL;
			अवरोध;
		पूर्ण
		क्रम (i = 0; i < extoff->n_samples; i++) अणु
			err = ptp->info->समय_लोx64(ptp->info, &ts, &sts);
			अगर (err)
				जाओ out;
			extoff->ts[i][0].sec = sts.pre_ts.tv_sec;
			extoff->ts[i][0].nsec = sts.pre_ts.tv_nsec;
			extoff->ts[i][1].sec = ts.tv_sec;
			extoff->ts[i][1].nsec = ts.tv_nsec;
			extoff->ts[i][2].sec = sts.post_ts.tv_sec;
			extoff->ts[i][2].nsec = sts.post_ts.tv_nsec;
		पूर्ण
		अगर (copy_to_user((व्योम __user *)arg, extoff, माप(*extoff)))
			err = -EFAULT;
		अवरोध;

	हाल PTP_SYS_OFFSET:
	हाल PTP_SYS_OFFSET2:
		sysoff = memdup_user((व्योम __user *)arg, माप(*sysoff));
		अगर (IS_ERR(sysoff)) अणु
			err = PTR_ERR(sysoff);
			sysoff = शून्य;
			अवरोध;
		पूर्ण
		अगर (sysoff->n_samples > PTP_MAX_SAMPLES) अणु
			err = -EINVAL;
			अवरोध;
		पूर्ण
		pct = &sysoff->ts[0];
		क्रम (i = 0; i < sysoff->n_samples; i++) अणु
			kसमय_get_real_ts64(&ts);
			pct->sec = ts.tv_sec;
			pct->nsec = ts.tv_nsec;
			pct++;
			अगर (ops->समय_लोx64)
				err = ops->समय_लोx64(ops, &ts, शून्य);
			अन्यथा
				err = ops->समय_लो64(ops, &ts);
			अगर (err)
				जाओ out;
			pct->sec = ts.tv_sec;
			pct->nsec = ts.tv_nsec;
			pct++;
		पूर्ण
		kसमय_get_real_ts64(&ts);
		pct->sec = ts.tv_sec;
		pct->nsec = ts.tv_nsec;
		अगर (copy_to_user((व्योम __user *)arg, sysoff, माप(*sysoff)))
			err = -EFAULT;
		अवरोध;

	हाल PTP_PIN_GETFUNC:
	हाल PTP_PIN_GETFUNC2:
		अगर (copy_from_user(&pd, (व्योम __user *)arg, माप(pd))) अणु
			err = -EFAULT;
			अवरोध;
		पूर्ण
		अगर ((pd.rsv[0] || pd.rsv[1] || pd.rsv[2]
				|| pd.rsv[3] || pd.rsv[4])
			&& cmd == PTP_PIN_GETFUNC2) अणु
			err = -EINVAL;
			अवरोध;
		पूर्ण अन्यथा अगर (cmd == PTP_PIN_GETFUNC) अणु
			pd.rsv[0] = 0;
			pd.rsv[1] = 0;
			pd.rsv[2] = 0;
			pd.rsv[3] = 0;
			pd.rsv[4] = 0;
		पूर्ण
		pin_index = pd.index;
		अगर (pin_index >= ops->n_pins) अणु
			err = -EINVAL;
			अवरोध;
		पूर्ण
		pin_index = array_index_nospec(pin_index, ops->n_pins);
		अगर (mutex_lock_पूर्णांकerruptible(&ptp->pincfg_mux))
			वापस -ERESTARTSYS;
		pd = ops->pin_config[pin_index];
		mutex_unlock(&ptp->pincfg_mux);
		अगर (!err && copy_to_user((व्योम __user *)arg, &pd, माप(pd)))
			err = -EFAULT;
		अवरोध;

	हाल PTP_PIN_SETFUNC:
	हाल PTP_PIN_SETFUNC2:
		अगर (copy_from_user(&pd, (व्योम __user *)arg, माप(pd))) अणु
			err = -EFAULT;
			अवरोध;
		पूर्ण
		अगर ((pd.rsv[0] || pd.rsv[1] || pd.rsv[2]
				|| pd.rsv[3] || pd.rsv[4])
			&& cmd == PTP_PIN_SETFUNC2) अणु
			err = -EINVAL;
			अवरोध;
		पूर्ण अन्यथा अगर (cmd == PTP_PIN_SETFUNC) अणु
			pd.rsv[0] = 0;
			pd.rsv[1] = 0;
			pd.rsv[2] = 0;
			pd.rsv[3] = 0;
			pd.rsv[4] = 0;
		पूर्ण
		pin_index = pd.index;
		अगर (pin_index >= ops->n_pins) अणु
			err = -EINVAL;
			अवरोध;
		पूर्ण
		pin_index = array_index_nospec(pin_index, ops->n_pins);
		अगर (mutex_lock_पूर्णांकerruptible(&ptp->pincfg_mux))
			वापस -ERESTARTSYS;
		err = ptp_set_pinfunc(ptp, pin_index, pd.func, pd.chan);
		mutex_unlock(&ptp->pincfg_mux);
		अवरोध;

	शेष:
		err = -ENOTTY;
		अवरोध;
	पूर्ण

out:
	kमुक्त(extoff);
	kमुक्त(sysoff);
	वापस err;
पूर्ण

__poll_t ptp_poll(काष्ठा posix_घड़ी *pc, काष्ठा file *fp, poll_table *रुको)
अणु
	काष्ठा ptp_घड़ी *ptp = container_of(pc, काष्ठा ptp_घड़ी, घड़ी);

	poll_रुको(fp, &ptp->tsev_wq, रुको);

	वापस queue_cnt(&ptp->tsevq) ? EPOLLIN : 0;
पूर्ण

#घोषणा EXTTS_बफ_मानE (PTP_BUF_TIMESTAMPS * माप(काष्ठा ptp_extts_event))

sमाप_प्रकार ptp_पढ़ो(काष्ठा posix_घड़ी *pc,
		 uपूर्णांक rdflags, अक्षर __user *buf, माप_प्रकार cnt)
अणु
	काष्ठा ptp_घड़ी *ptp = container_of(pc, काष्ठा ptp_घड़ी, घड़ी);
	काष्ठा बारtamp_event_queue *queue = &ptp->tsevq;
	काष्ठा ptp_extts_event *event;
	अचिन्हित दीर्घ flags;
	माप_प्रकार qcnt, i;
	पूर्णांक result;

	अगर (cnt % माप(काष्ठा ptp_extts_event) != 0)
		वापस -EINVAL;

	अगर (cnt > EXTTS_बफ_मानE)
		cnt = EXTTS_बफ_मानE;

	cnt = cnt / माप(काष्ठा ptp_extts_event);

	अगर (mutex_lock_पूर्णांकerruptible(&ptp->tsevq_mux))
		वापस -ERESTARTSYS;

	अगर (रुको_event_पूर्णांकerruptible(ptp->tsev_wq,
				     ptp->defunct || queue_cnt(queue))) अणु
		mutex_unlock(&ptp->tsevq_mux);
		वापस -ERESTARTSYS;
	पूर्ण

	अगर (ptp->defunct) अणु
		mutex_unlock(&ptp->tsevq_mux);
		वापस -ENODEV;
	पूर्ण

	event = kदो_स्मृति(EXTTS_बफ_मानE, GFP_KERNEL);
	अगर (!event) अणु
		mutex_unlock(&ptp->tsevq_mux);
		वापस -ENOMEM;
	पूर्ण

	spin_lock_irqsave(&queue->lock, flags);

	qcnt = queue_cnt(queue);

	अगर (cnt > qcnt)
		cnt = qcnt;

	क्रम (i = 0; i < cnt; i++) अणु
		event[i] = queue->buf[queue->head];
		queue->head = (queue->head + 1) % PTP_MAX_TIMESTAMPS;
	पूर्ण

	spin_unlock_irqrestore(&queue->lock, flags);

	cnt = cnt * माप(काष्ठा ptp_extts_event);

	mutex_unlock(&ptp->tsevq_mux);

	result = cnt;
	अगर (copy_to_user(buf, event, cnt))
		result = -EFAULT;

	kमुक्त(event);
	वापस result;
पूर्ण
