<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * PCM समयr handling on ctxfi
 */

#समावेश <linux/slab.h>
#समावेश <linux/math64.h>
#समावेश <linux/moduleparam.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश "ctatc.h"
#समावेश "cthardware.h"
#समावेश "cttimer.h"

अटल bool use_प्रणाली_समयr;
MODULE_PARM_DESC(use_प्रणाली_समयr, "Force to use system-timer");
module_param(use_प्रणाली_समयr, bool, 0444);

काष्ठा ct_समयr_ops अणु
	व्योम (*init)(काष्ठा ct_समयr_instance *);
	व्योम (*prepare)(काष्ठा ct_समयr_instance *);
	व्योम (*start)(काष्ठा ct_समयr_instance *);
	व्योम (*stop)(काष्ठा ct_समयr_instance *);
	व्योम (*मुक्त_instance)(काष्ठा ct_समयr_instance *);
	व्योम (*पूर्णांकerrupt)(काष्ठा ct_समयr *);
	व्योम (*मुक्त_global)(काष्ठा ct_समयr *);
पूर्ण;

/* समयr instance -- asचिन्हित to each PCM stream */
काष्ठा ct_समयr_instance अणु
	spinlock_t lock;
	काष्ठा ct_समयr *समयr_base;
	काष्ठा ct_atc_pcm *apcm;
	काष्ठा snd_pcm_substream *substream;
	काष्ठा समयr_list समयr;
	काष्ठा list_head instance_list;
	काष्ठा list_head running_list;
	अचिन्हित पूर्णांक position;
	अचिन्हित पूर्णांक frag_count;
	अचिन्हित पूर्णांक running:1;
	अचिन्हित पूर्णांक need_update:1;
पूर्ण;

/* समयr instance manager */
काष्ठा ct_समयr अणु
	spinlock_t lock;		/* global समयr lock (क्रम xfiसमयr) */
	spinlock_t list_lock;		/* lock क्रम instance list */
	काष्ठा ct_atc *atc;
	स्थिर काष्ठा ct_समयr_ops *ops;
	काष्ठा list_head instance_head;
	काष्ठा list_head running_head;
	अचिन्हित पूर्णांक wc;		/* current wallघड़ी */
	अचिन्हित पूर्णांक irq_handling:1;	/* in IRQ handling */
	अचिन्हित पूर्णांक reprogram:1;	/* need to reprogram the पूर्णांकernval */
	अचिन्हित पूर्णांक running:1;		/* global समयr running */
पूर्ण;


/*
 * प्रणाली-समयr-based updates
 */

अटल व्योम ct_sysसमयr_callback(काष्ठा समयr_list *t)
अणु
	काष्ठा ct_समयr_instance *ti = from_समयr(ti, t, समयr);
	काष्ठा snd_pcm_substream *substream = ti->substream;
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा ct_atc_pcm *apcm = ti->apcm;
	अचिन्हित पूर्णांक period_size = runसमय->period_size;
	अचिन्हित पूर्णांक buffer_size = runसमय->buffer_size;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक position, dist, पूर्णांकerval;

	position = substream->ops->poपूर्णांकer(substream);
	dist = (position + buffer_size - ti->position) % buffer_size;
	अगर (dist >= period_size ||
	    position / period_size != ti->position / period_size) अणु
		apcm->पूर्णांकerrupt(apcm);
		ti->position = position;
	पूर्ण
	/* Add extra HZ*5/1000 to aव्योम overrun issue when recording
	 * at 8kHz in 8-bit क्रमmat or at 88kHz in 24-bit क्रमmat. */
	पूर्णांकerval = ((period_size - (position % period_size))
		   * HZ + (runसमय->rate - 1)) / runसमय->rate + HZ * 5 / 1000;
	spin_lock_irqsave(&ti->lock, flags);
	अगर (ti->running)
		mod_समयr(&ti->समयr, jअगरfies + पूर्णांकerval);
	spin_unlock_irqrestore(&ti->lock, flags);
पूर्ण

अटल व्योम ct_sysसमयr_init(काष्ठा ct_समयr_instance *ti)
अणु
	समयr_setup(&ti->समयr, ct_sysसमयr_callback, 0);
पूर्ण

अटल व्योम ct_sysसमयr_start(काष्ठा ct_समयr_instance *ti)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = ti->substream->runसमय;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ti->lock, flags);
	ti->running = 1;
	mod_समयr(&ti->समयr,
		  jअगरfies + (runसमय->period_size * HZ +
			     (runसमय->rate - 1)) / runसमय->rate);
	spin_unlock_irqrestore(&ti->lock, flags);
पूर्ण

अटल व्योम ct_sysसमयr_stop(काष्ठा ct_समयr_instance *ti)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ti->lock, flags);
	ti->running = 0;
	del_समयr(&ti->समयr);
	spin_unlock_irqrestore(&ti->lock, flags);
पूर्ण

अटल व्योम ct_sysसमयr_prepare(काष्ठा ct_समयr_instance *ti)
अणु
	ct_sysसमयr_stop(ti);
	try_to_del_समयr_sync(&ti->समयr);
पूर्ण

#घोषणा ct_sysसमयr_मुक्त	ct_sysसमयr_prepare

अटल स्थिर काष्ठा ct_समयr_ops ct_sysसमयr_ops = अणु
	.init = ct_sysसमयr_init,
	.मुक्त_instance = ct_sysसमयr_मुक्त,
	.prepare = ct_sysसमयr_prepare,
	.start = ct_sysसमयr_start,
	.stop = ct_sysसमयr_stop,
पूर्ण;


/*
 * Handling multiple streams using a global emu20k1 समयr irq
 */

#घोषणा CT_TIMER_FREQ	48000
#घोषणा MIN_TICKS	1
#घोषणा MAX_TICKS	((1 << 13) - 1)

अटल व्योम ct_xfiसमयr_irq_rearm(काष्ठा ct_समयr *aसमयr, पूर्णांक ticks)
अणु
	काष्ठा hw *hw = aसमयr->atc->hw;
	अगर (ticks > MAX_TICKS)
		ticks = MAX_TICKS;
	hw->set_समयr_tick(hw, ticks);
	अगर (!aसमयr->running)
		hw->set_समयr_irq(hw, 1);
	aसमयr->running = 1;
पूर्ण

अटल व्योम ct_xfiसमयr_irq_stop(काष्ठा ct_समयr *aसमयr)
अणु
	अगर (aसमयr->running) अणु
		काष्ठा hw *hw = aसमयr->atc->hw;
		hw->set_समयr_irq(hw, 0);
		hw->set_समयr_tick(hw, 0);
		aसमयr->running = 0;
	पूर्ण
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक ct_xfiसमयr_get_wc(काष्ठा ct_समयr *aसमयr)
अणु
	काष्ठा hw *hw = aसमयr->atc->hw;
	वापस hw->get_wc(hw);
पूर्ण

/*
 * reprogram the समयr पूर्णांकerval;
 * checks the running instance list and determines the next समयr पूर्णांकerval.
 * also updates the each stream position, वापसs the number of streams
 * to call snd_pcm_period_elapsed() appropriately
 *
 * call this inside the lock and irq disabled
 */
अटल पूर्णांक ct_xfiसमयr_reprogram(काष्ठा ct_समयr *aसमयr, पूर्णांक can_update)
अणु
	काष्ठा ct_समयr_instance *ti;
	अचिन्हित पूर्णांक min_पूर्णांकr = (अचिन्हित पूर्णांक)-1;
	पूर्णांक updates = 0;
	अचिन्हित पूर्णांक wc, dअगरf;

	अगर (list_empty(&aसमयr->running_head)) अणु
		ct_xfiसमयr_irq_stop(aसमयr);
		aसमयr->reprogram = 0; /* clear flag */
		वापस 0;
	पूर्ण

	wc = ct_xfiसमयr_get_wc(aसमयr);
	dअगरf = wc - aसमयr->wc;
	aसमयr->wc = wc;
	list_क्रम_each_entry(ti, &aसमयr->running_head, running_list) अणु
		अगर (ti->frag_count > dअगरf)
			ti->frag_count -= dअगरf;
		अन्यथा अणु
			अचिन्हित पूर्णांक pos;
			अचिन्हित पूर्णांक period_size, rate;

			period_size = ti->substream->runसमय->period_size;
			rate = ti->substream->runसमय->rate;
			pos = ti->substream->ops->poपूर्णांकer(ti->substream);
			अगर (pos / period_size != ti->position / period_size) अणु
				ti->need_update = 1;
				ti->position = pos;
				updates++;
			पूर्ण
			pos %= period_size;
			pos = period_size - pos;
			ti->frag_count = भाग_u64((u64)pos * CT_TIMER_FREQ +
						 rate - 1, rate);
		पूर्ण
		अगर (ti->need_update && !can_update)
			min_पूर्णांकr = 0; /* pending to the next irq */
		अगर (ti->frag_count < min_पूर्णांकr)
			min_पूर्णांकr = ti->frag_count;
	पूर्ण

	अगर (min_पूर्णांकr < MIN_TICKS)
		min_पूर्णांकr = MIN_TICKS;
	ct_xfiसमयr_irq_rearm(aसमयr, min_पूर्णांकr);
	aसमयr->reprogram = 0; /* clear flag */
	वापस updates;
पूर्ण

/* look through the instance list and call period_elapsed अगर needed */
अटल व्योम ct_xfiसमयr_check_period(काष्ठा ct_समयr *aसमयr)
अणु
	काष्ठा ct_समयr_instance *ti;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&aसमयr->list_lock, flags);
	list_क्रम_each_entry(ti, &aसमयr->instance_head, instance_list) अणु
		अगर (ti->running && ti->need_update) अणु
			ti->need_update = 0;
			ti->apcm->पूर्णांकerrupt(ti->apcm);
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&aसमयr->list_lock, flags);
पूर्ण

/* Handle समयr-पूर्णांकerrupt */
अटल व्योम ct_xfiसमयr_callback(काष्ठा ct_समयr *aसमयr)
अणु
	पूर्णांक update;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&aसमयr->lock, flags);
	aसमयr->irq_handling = 1;
	करो अणु
		update = ct_xfiसमयr_reprogram(aसमयr, 1);
		spin_unlock(&aसमयr->lock);
		अगर (update)
			ct_xfiसमयr_check_period(aसमयr);
		spin_lock(&aसमयr->lock);
	पूर्ण जबतक (aसमयr->reprogram);
	aसमयr->irq_handling = 0;
	spin_unlock_irqrestore(&aसमयr->lock, flags);
पूर्ण

अटल व्योम ct_xfiसमयr_prepare(काष्ठा ct_समयr_instance *ti)
अणु
	ti->frag_count = ti->substream->runसमय->period_size;
	ti->running = 0;
	ti->need_update = 0;
पूर्ण


/* start/stop the समयr */
अटल व्योम ct_xfiसमयr_update(काष्ठा ct_समयr *aसमयr)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&aसमयr->lock, flags);
	अगर (aसमयr->irq_handling) अणु
		/* reached from IRQ handler; let it handle later */
		aसमयr->reprogram = 1;
		spin_unlock_irqrestore(&aसमयr->lock, flags);
		वापस;
	पूर्ण

	ct_xfiसमयr_irq_stop(aसमयr);
	ct_xfiसमयr_reprogram(aसमयr, 0);
	spin_unlock_irqrestore(&aसमयr->lock, flags);
पूर्ण

अटल व्योम ct_xfiसमयr_start(काष्ठा ct_समयr_instance *ti)
अणु
	काष्ठा ct_समयr *aसमयr = ti->समयr_base;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&aसमयr->lock, flags);
	अगर (list_empty(&ti->running_list))
		aसमयr->wc = ct_xfiसमयr_get_wc(aसमयr);
	ti->running = 1;
	ti->need_update = 0;
	list_add(&ti->running_list, &aसमयr->running_head);
	spin_unlock_irqrestore(&aसमयr->lock, flags);
	ct_xfiसमयr_update(aसमयr);
पूर्ण

अटल व्योम ct_xfiसमयr_stop(काष्ठा ct_समयr_instance *ti)
अणु
	काष्ठा ct_समयr *aसमयr = ti->समयr_base;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&aसमयr->lock, flags);
	list_del_init(&ti->running_list);
	ti->running = 0;
	spin_unlock_irqrestore(&aसमयr->lock, flags);
	ct_xfiसमयr_update(aसमयr);
पूर्ण

अटल व्योम ct_xfiसमयr_मुक्त_global(काष्ठा ct_समयr *aसमयr)
अणु
	ct_xfiसमयr_irq_stop(aसमयr);
पूर्ण

अटल स्थिर काष्ठा ct_समयr_ops ct_xfiसमयr_ops = अणु
	.prepare = ct_xfiसमयr_prepare,
	.start = ct_xfiसमयr_start,
	.stop = ct_xfiसमयr_stop,
	.पूर्णांकerrupt = ct_xfiसमयr_callback,
	.मुक्त_global = ct_xfiसमयr_मुक्त_global,
पूर्ण;

/*
 * समयr instance
 */

काष्ठा ct_समयr_instance *
ct_समयr_instance_new(काष्ठा ct_समयr *aसमयr, काष्ठा ct_atc_pcm *apcm)
अणु
	काष्ठा ct_समयr_instance *ti;

	ti = kzalloc(माप(*ti), GFP_KERNEL);
	अगर (!ti)
		वापस शून्य;
	spin_lock_init(&ti->lock);
	INIT_LIST_HEAD(&ti->instance_list);
	INIT_LIST_HEAD(&ti->running_list);
	ti->समयr_base = aसमयr;
	ti->apcm = apcm;
	ti->substream = apcm->substream;
	अगर (aसमयr->ops->init)
		aसमयr->ops->init(ti);

	spin_lock_irq(&aसमयr->list_lock);
	list_add(&ti->instance_list, &aसमयr->instance_head);
	spin_unlock_irq(&aसमयr->list_lock);

	वापस ti;
पूर्ण

व्योम ct_समयr_prepare(काष्ठा ct_समयr_instance *ti)
अणु
	अगर (ti->समयr_base->ops->prepare)
		ti->समयr_base->ops->prepare(ti);
	ti->position = 0;
	ti->running = 0;
पूर्ण

व्योम ct_समयr_start(काष्ठा ct_समयr_instance *ti)
अणु
	काष्ठा ct_समयr *aसमयr = ti->समयr_base;
	aसमयr->ops->start(ti);
पूर्ण

व्योम ct_समयr_stop(काष्ठा ct_समयr_instance *ti)
अणु
	काष्ठा ct_समयr *aसमयr = ti->समयr_base;
	aसमयr->ops->stop(ti);
पूर्ण

व्योम ct_समयr_instance_मुक्त(काष्ठा ct_समयr_instance *ti)
अणु
	काष्ठा ct_समयr *aसमयr = ti->समयr_base;

	aसमयr->ops->stop(ti); /* to be sure */
	अगर (aसमयr->ops->मुक्त_instance)
		aसमयr->ops->मुक्त_instance(ti);

	spin_lock_irq(&aसमयr->list_lock);
	list_del(&ti->instance_list);
	spin_unlock_irq(&aसमयr->list_lock);

	kमुक्त(ti);
पूर्ण

/*
 * समयr manager
 */

अटल व्योम ct_समयr_पूर्णांकerrupt(व्योम *data, अचिन्हित पूर्णांक status)
अणु
	काष्ठा ct_समयr *समयr = data;

	/* Interval समयr पूर्णांकerrupt */
	अगर ((status & IT_INT) && समयr->ops->पूर्णांकerrupt)
		समयr->ops->पूर्णांकerrupt(समयr);
पूर्ण

काष्ठा ct_समयr *ct_समयr_new(काष्ठा ct_atc *atc)
अणु
	काष्ठा ct_समयr *aसमयr;
	काष्ठा hw *hw;

	aसमयr = kzalloc(माप(*aसमयr), GFP_KERNEL);
	अगर (!aसमयr)
		वापस शून्य;
	spin_lock_init(&aसमयr->lock);
	spin_lock_init(&aसमयr->list_lock);
	INIT_LIST_HEAD(&aसमयr->instance_head);
	INIT_LIST_HEAD(&aसमयr->running_head);
	aसमयr->atc = atc;
	hw = atc->hw;
	अगर (!use_प्रणाली_समयr && hw->set_समयr_irq) अणु
		dev_info(atc->card->dev, "Use xfi-native timer\n");
		aसमयr->ops = &ct_xfiसमयr_ops;
		hw->irq_callback_data = aसमयr;
		hw->irq_callback = ct_समयr_पूर्णांकerrupt;
	पूर्ण अन्यथा अणु
		dev_info(atc->card->dev, "Use system timer\n");
		aसमयr->ops = &ct_sysसमयr_ops;
	पूर्ण
	वापस aसमयr;
पूर्ण

व्योम ct_समयr_मुक्त(काष्ठा ct_समयr *aसमयr)
अणु
	काष्ठा hw *hw = aसमयr->atc->hw;
	hw->irq_callback = शून्य;
	अगर (aसमयr->ops->मुक्त_global)
		aसमयr->ops->मुक्त_global(aसमयr);
	kमुक्त(aसमयr);
पूर्ण

