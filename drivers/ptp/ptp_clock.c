<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * PTP 1588 घड़ी support
 *
 * Copyright (C) 2010 OMICRON electronics GmbH
 */
#समावेश <linux/idr.h>
#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/posix-घड़ी.h>
#समावेश <linux/pps_kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/uaccess.h>
#समावेश <uapi/linux/sched/types.h>

#समावेश "ptp_private.h"

#घोषणा PTP_MAX_ALARMS 4
#घोषणा PTP_PPS_DEFAULTS (PPS_CAPTUREASSERT | PPS_OFFSETASSERT)
#घोषणा PTP_PPS_EVENT PPS_CAPTUREASSERT
#घोषणा PTP_PPS_MODE (PTP_PPS_DEFAULTS | PPS_CANWAIT | PPS_TSFMT_TSPEC)

/* निजी globals */

अटल dev_t ptp_devt;
अटल काष्ठा class *ptp_class;

अटल DEFINE_IDA(ptp_घड़ीs_map);

/* समय stamp event queue operations */

अटल अंतरभूत पूर्णांक queue_मुक्त(काष्ठा बारtamp_event_queue *q)
अणु
	वापस PTP_MAX_TIMESTAMPS - queue_cnt(q) - 1;
पूर्ण

अटल व्योम enqueue_बाह्यal_बारtamp(काष्ठा बारtamp_event_queue *queue,
				       काष्ठा ptp_घड़ी_event *src)
अणु
	काष्ठा ptp_extts_event *dst;
	अचिन्हित दीर्घ flags;
	s64 seconds;
	u32 reमुख्यder;

	seconds = भाग_u64_rem(src->बारtamp, 1000000000, &reमुख्यder);

	spin_lock_irqsave(&queue->lock, flags);

	dst = &queue->buf[queue->tail];
	dst->index = src->index;
	dst->t.sec = seconds;
	dst->t.nsec = reमुख्यder;

	अगर (!queue_मुक्त(queue))
		queue->head = (queue->head + 1) % PTP_MAX_TIMESTAMPS;

	queue->tail = (queue->tail + 1) % PTP_MAX_TIMESTAMPS;

	spin_unlock_irqrestore(&queue->lock, flags);
पूर्ण

दीर्घ scaled_ppm_to_ppb(दीर्घ ppm)
अणु
	/*
	 * The 'freq' field in the 'struct timex' is in parts per
	 * million, but with a 16 bit binary fractional field.
	 *
	 * We want to calculate
	 *
	 *    ppb = scaled_ppm * 1000 / 2^16
	 *
	 * which simplअगरies to
	 *
	 *    ppb = scaled_ppm * 125 / 2^13
	 */
	s64 ppb = 1 + ppm;
	ppb *= 125;
	ppb >>= 13;
	वापस (दीर्घ) ppb;
पूर्ण
EXPORT_SYMBOL(scaled_ppm_to_ppb);

/* posix घड़ी implementation */

अटल पूर्णांक ptp_घड़ी_getres(काष्ठा posix_घड़ी *pc, काष्ठा बारpec64 *tp)
अणु
	tp->tv_sec = 0;
	tp->tv_nsec = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक ptp_घड़ी_समय_रखो(काष्ठा posix_घड़ी *pc, स्थिर काष्ठा बारpec64 *tp)
अणु
	काष्ठा ptp_घड़ी *ptp = container_of(pc, काष्ठा ptp_घड़ी, घड़ी);

	वापस  ptp->info->समय_रखो64(ptp->info, tp);
पूर्ण

अटल पूर्णांक ptp_घड़ी_समय_लो(काष्ठा posix_घड़ी *pc, काष्ठा बारpec64 *tp)
अणु
	काष्ठा ptp_घड़ी *ptp = container_of(pc, काष्ठा ptp_घड़ी, घड़ी);
	पूर्णांक err;

	अगर (ptp->info->समय_लोx64)
		err = ptp->info->समय_लोx64(ptp->info, tp, शून्य);
	अन्यथा
		err = ptp->info->समय_लो64(ptp->info, tp);
	वापस err;
पूर्ण

अटल पूर्णांक ptp_घड़ी_adjसमय(काष्ठा posix_घड़ी *pc, काष्ठा __kernel_समयx *tx)
अणु
	काष्ठा ptp_घड़ी *ptp = container_of(pc, काष्ठा ptp_घड़ी, घड़ी);
	काष्ठा ptp_घड़ी_info *ops;
	पूर्णांक err = -EOPNOTSUPP;

	ops = ptp->info;

	अगर (tx->modes & ADJ_SETOFFSET) अणु
		काष्ठा बारpec64 ts;
		kसमय_प्रकार kt;
		s64 delta;

		ts.tv_sec  = tx->समय.tv_sec;
		ts.tv_nsec = tx->समय.tv_usec;

		अगर (!(tx->modes & ADJ_न_अंकO))
			ts.tv_nsec *= 1000;

		अगर ((अचिन्हित दीर्घ) ts.tv_nsec >= NSEC_PER_SEC)
			वापस -EINVAL;

		kt = बारpec64_to_kसमय(ts);
		delta = kसमय_प्रकारo_ns(kt);
		err = ops->adjसमय(ops, delta);
	पूर्ण अन्यथा अगर (tx->modes & ADJ_FREQUENCY) अणु
		दीर्घ ppb = scaled_ppm_to_ppb(tx->freq);
		अगर (ppb > ops->max_adj || ppb < -ops->max_adj)
			वापस -दुस्फल;
		अगर (ops->adjfine)
			err = ops->adjfine(ops, tx->freq);
		अन्यथा
			err = ops->adjfreq(ops, ppb);
		ptp->dialed_frequency = tx->freq;
	पूर्ण अन्यथा अगर (tx->modes & ADJ_OFFSET) अणु
		अगर (ops->adjphase) अणु
			s32 offset = tx->offset;

			अगर (!(tx->modes & ADJ_न_अंकO))
				offset *= NSEC_PER_USEC;

			err = ops->adjphase(ops, offset);
		पूर्ण
	पूर्ण अन्यथा अगर (tx->modes == 0) अणु
		tx->freq = ptp->dialed_frequency;
		err = 0;
	पूर्ण

	वापस err;
पूर्ण

अटल काष्ठा posix_घड़ी_operations ptp_घड़ी_ops = अणु
	.owner		= THIS_MODULE,
	.घड़ी_adjसमय	= ptp_घड़ी_adjसमय,
	.घड़ी_समय_लो	= ptp_घड़ी_समय_लो,
	.घड़ी_getres	= ptp_घड़ी_getres,
	.घड़ी_समय_रखो	= ptp_घड़ी_समय_रखो,
	.ioctl		= ptp_ioctl,
	.खोलो		= ptp_खोलो,
	.poll		= ptp_poll,
	.पढ़ो		= ptp_पढ़ो,
पूर्ण;

अटल व्योम ptp_घड़ी_release(काष्ठा device *dev)
अणु
	काष्ठा ptp_घड़ी *ptp = container_of(dev, काष्ठा ptp_घड़ी, dev);

	ptp_cleanup_pin_groups(ptp);
	mutex_destroy(&ptp->tsevq_mux);
	mutex_destroy(&ptp->pincfg_mux);
	ida_simple_हटाओ(&ptp_घड़ीs_map, ptp->index);
	kमुक्त(ptp);
पूर्ण

अटल व्योम ptp_aux_kworker(काष्ठा kthपढ़ो_work *work)
अणु
	काष्ठा ptp_घड़ी *ptp = container_of(work, काष्ठा ptp_घड़ी,
					     aux_work.work);
	काष्ठा ptp_घड़ी_info *info = ptp->info;
	दीर्घ delay;

	delay = info->करो_aux_work(info);

	अगर (delay >= 0)
		kthपढ़ो_queue_delayed_work(ptp->kworker, &ptp->aux_work, delay);
पूर्ण

/* खुला पूर्णांकerface */

काष्ठा ptp_घड़ी *ptp_घड़ी_रेजिस्टर(काष्ठा ptp_घड़ी_info *info,
				     काष्ठा device *parent)
अणु
	काष्ठा ptp_घड़ी *ptp;
	पूर्णांक err = 0, index, major = MAJOR(ptp_devt);

	अगर (info->n_alarm > PTP_MAX_ALARMS)
		वापस ERR_PTR(-EINVAL);

	/* Initialize a घड़ी काष्ठाure. */
	err = -ENOMEM;
	ptp = kzalloc(माप(काष्ठा ptp_घड़ी), GFP_KERNEL);
	अगर (ptp == शून्य)
		जाओ no_memory;

	index = ida_simple_get(&ptp_घड़ीs_map, 0, MINORMASK + 1, GFP_KERNEL);
	अगर (index < 0) अणु
		err = index;
		जाओ no_slot;
	पूर्ण

	ptp->घड़ी.ops = ptp_घड़ी_ops;
	ptp->info = info;
	ptp->devid = MKDEV(major, index);
	ptp->index = index;
	spin_lock_init(&ptp->tsevq.lock);
	mutex_init(&ptp->tsevq_mux);
	mutex_init(&ptp->pincfg_mux);
	init_रुकोqueue_head(&ptp->tsev_wq);

	अगर (ptp->info->करो_aux_work) अणु
		kthपढ़ो_init_delayed_work(&ptp->aux_work, ptp_aux_kworker);
		ptp->kworker = kthपढ़ो_create_worker(0, "ptp%d", ptp->index);
		अगर (IS_ERR(ptp->kworker)) अणु
			err = PTR_ERR(ptp->kworker);
			pr_err("failed to create ptp aux_worker %d\n", err);
			जाओ kworker_err;
		पूर्ण
	पूर्ण

	err = ptp_populate_pin_groups(ptp);
	अगर (err)
		जाओ no_pin_groups;

	/* Register a new PPS source. */
	अगर (info->pps) अणु
		काष्ठा pps_source_info pps;
		स_रखो(&pps, 0, माप(pps));
		snम_लिखो(pps.name, PPS_MAX_NAME_LEN, "ptp%d", index);
		pps.mode = PTP_PPS_MODE;
		pps.owner = info->owner;
		ptp->pps_source = pps_रेजिस्टर_source(&pps, PTP_PPS_DEFAULTS);
		अगर (IS_ERR(ptp->pps_source)) अणु
			err = PTR_ERR(ptp->pps_source);
			pr_err("failed to register pps source\n");
			जाओ no_pps;
		पूर्ण
	पूर्ण

	/* Initialize a new device of our class in our घड़ी काष्ठाure. */
	device_initialize(&ptp->dev);
	ptp->dev.devt = ptp->devid;
	ptp->dev.class = ptp_class;
	ptp->dev.parent = parent;
	ptp->dev.groups = ptp->pin_attr_groups;
	ptp->dev.release = ptp_घड़ी_release;
	dev_set_drvdata(&ptp->dev, ptp);
	dev_set_name(&ptp->dev, "ptp%d", ptp->index);

	/* Create a posix घड़ी and link it to the device. */
	err = posix_घड़ी_रेजिस्टर(&ptp->घड़ी, &ptp->dev);
	अगर (err) अणु
		pr_err("failed to create posix clock\n");
		जाओ no_घड़ी;
	पूर्ण

	वापस ptp;

no_घड़ी:
	अगर (ptp->pps_source)
		pps_unरेजिस्टर_source(ptp->pps_source);
no_pps:
	ptp_cleanup_pin_groups(ptp);
no_pin_groups:
	अगर (ptp->kworker)
		kthपढ़ो_destroy_worker(ptp->kworker);
kworker_err:
	mutex_destroy(&ptp->tsevq_mux);
	mutex_destroy(&ptp->pincfg_mux);
	ida_simple_हटाओ(&ptp_घड़ीs_map, index);
no_slot:
	kमुक्त(ptp);
no_memory:
	वापस ERR_PTR(err);
पूर्ण
EXPORT_SYMBOL(ptp_घड़ी_रेजिस्टर);

पूर्णांक ptp_घड़ी_unरेजिस्टर(काष्ठा ptp_घड़ी *ptp)
अणु
	ptp->defunct = 1;
	wake_up_पूर्णांकerruptible(&ptp->tsev_wq);

	अगर (ptp->kworker) अणु
		kthपढ़ो_cancel_delayed_work_sync(&ptp->aux_work);
		kthपढ़ो_destroy_worker(ptp->kworker);
	पूर्ण

	/* Release the घड़ी's resources. */
	अगर (ptp->pps_source)
		pps_unरेजिस्टर_source(ptp->pps_source);

	posix_घड़ी_unरेजिस्टर(&ptp->घड़ी);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(ptp_घड़ी_unरेजिस्टर);

व्योम ptp_घड़ी_event(काष्ठा ptp_घड़ी *ptp, काष्ठा ptp_घड़ी_event *event)
अणु
	काष्ठा pps_event_समय evt;

	चयन (event->type) अणु

	हाल PTP_CLOCK_ALARM:
		अवरोध;

	हाल PTP_CLOCK_EXTTS:
		enqueue_बाह्यal_बारtamp(&ptp->tsevq, event);
		wake_up_पूर्णांकerruptible(&ptp->tsev_wq);
		अवरोध;

	हाल PTP_CLOCK_PPS:
		pps_get_ts(&evt);
		pps_event(ptp->pps_source, &evt, PTP_PPS_EVENT, शून्य);
		अवरोध;

	हाल PTP_CLOCK_PPSUSR:
		pps_event(ptp->pps_source, &event->pps_बार,
			  PTP_PPS_EVENT, शून्य);
		अवरोध;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(ptp_घड़ी_event);

पूर्णांक ptp_घड़ी_index(काष्ठा ptp_घड़ी *ptp)
अणु
	वापस ptp->index;
पूर्ण
EXPORT_SYMBOL(ptp_घड़ी_index);

पूर्णांक ptp_find_pin(काष्ठा ptp_घड़ी *ptp,
		 क्रमागत ptp_pin_function func, अचिन्हित पूर्णांक chan)
अणु
	काष्ठा ptp_pin_desc *pin = शून्य;
	पूर्णांक i;

	क्रम (i = 0; i < ptp->info->n_pins; i++) अणु
		अगर (ptp->info->pin_config[i].func == func &&
		    ptp->info->pin_config[i].chan == chan) अणु
			pin = &ptp->info->pin_config[i];
			अवरोध;
		पूर्ण
	पूर्ण

	वापस pin ? i : -1;
पूर्ण
EXPORT_SYMBOL(ptp_find_pin);

पूर्णांक ptp_find_pin_unlocked(काष्ठा ptp_घड़ी *ptp,
			  क्रमागत ptp_pin_function func, अचिन्हित पूर्णांक chan)
अणु
	पूर्णांक result;

	mutex_lock(&ptp->pincfg_mux);

	result = ptp_find_pin(ptp, func, chan);

	mutex_unlock(&ptp->pincfg_mux);

	वापस result;
पूर्ण
EXPORT_SYMBOL(ptp_find_pin_unlocked);

पूर्णांक ptp_schedule_worker(काष्ठा ptp_घड़ी *ptp, अचिन्हित दीर्घ delay)
अणु
	वापस kthपढ़ो_mod_delayed_work(ptp->kworker, &ptp->aux_work, delay);
पूर्ण
EXPORT_SYMBOL(ptp_schedule_worker);

व्योम ptp_cancel_worker_sync(काष्ठा ptp_घड़ी *ptp)
अणु
	kthपढ़ो_cancel_delayed_work_sync(&ptp->aux_work);
पूर्ण
EXPORT_SYMBOL(ptp_cancel_worker_sync);

/* module operations */

अटल व्योम __निकास ptp_निकास(व्योम)
अणु
	class_destroy(ptp_class);
	unरेजिस्टर_chrdev_region(ptp_devt, MINORMASK + 1);
	ida_destroy(&ptp_घड़ीs_map);
पूर्ण

अटल पूर्णांक __init ptp_init(व्योम)
अणु
	पूर्णांक err;

	ptp_class = class_create(THIS_MODULE, "ptp");
	अगर (IS_ERR(ptp_class)) अणु
		pr_err("ptp: failed to allocate class\n");
		वापस PTR_ERR(ptp_class);
	पूर्ण

	err = alloc_chrdev_region(&ptp_devt, 0, MINORMASK + 1, "ptp");
	अगर (err < 0) अणु
		pr_err("ptp: failed to allocate device region\n");
		जाओ no_region;
	पूर्ण

	ptp_class->dev_groups = ptp_groups;
	pr_info("PTP clock support registered\n");
	वापस 0;

no_region:
	class_destroy(ptp_class);
	वापस err;
पूर्ण

subsys_initcall(ptp_init);
module_निकास(ptp_निकास);

MODULE_AUTHOR("Richard Cochran <richardcochran@gmail.com>");
MODULE_DESCRIPTION("PTP clocks support");
MODULE_LICENSE("GPL");
