<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Digital Audio (PCM) असलtract layer
 *  Copyright (c) by Jaroslav Kysela <perex@perex.cz>
 */

#समावेश <linux/compat.h>
#समावेश <linux/mm.h>
#समावेश <linux/module.h>
#समावेश <linux/file.h>
#समावेश <linux/slab.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/समय.स>
#समावेश <linux/pm_qos.h>
#समावेश <linux/पन.स>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <sound/core.h>
#समावेश <sound/control.h>
#समावेश <sound/info.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/समयr.h>
#समावेश <sound/minors.h>
#समावेश <linux/uपन.स>
#समावेश <linux/delay.h>

#समावेश "pcm_local.h"

#अगर_घोषित CONFIG_SND_DEBUG
#घोषणा CREATE_TRACE_POINTS
#समावेश "pcm_param_trace.h"
#अन्यथा
#घोषणा trace_hw_mask_param_enabled()		0
#घोषणा trace_hw_पूर्णांकerval_param_enabled()	0
#घोषणा trace_hw_mask_param(substream, type, index, prev, curr)
#घोषणा trace_hw_पूर्णांकerval_param(substream, type, index, prev, curr)
#पूर्ण_अगर

/*
 *  Compatibility
 */

काष्ठा snd_pcm_hw_params_old अणु
	अचिन्हित पूर्णांक flags;
	अचिन्हित पूर्णांक masks[SNDRV_PCM_HW_PARAM_SUBFORMAT -
			   SNDRV_PCM_HW_PARAM_ACCESS + 1];
	काष्ठा snd_पूर्णांकerval पूर्णांकervals[SNDRV_PCM_HW_PARAM_TICK_TIME -
					SNDRV_PCM_HW_PARAM_SAMPLE_BITS + 1];
	अचिन्हित पूर्णांक rmask;
	अचिन्हित पूर्णांक cmask;
	अचिन्हित पूर्णांक info;
	अचिन्हित पूर्णांक msbits;
	अचिन्हित पूर्णांक rate_num;
	अचिन्हित पूर्णांक rate_den;
	snd_pcm_uframes_t fअगरo_size;
	अचिन्हित अक्षर reserved[64];
पूर्ण;

#अगर_घोषित CONFIG_SND_SUPPORT_OLD_API
#घोषणा SNDRV_PCM_IOCTL_HW_REFINE_OLD _IOWR('A', 0x10, काष्ठा snd_pcm_hw_params_old)
#घोषणा SNDRV_PCM_IOCTL_HW_PARAMS_OLD _IOWR('A', 0x11, काष्ठा snd_pcm_hw_params_old)

अटल पूर्णांक snd_pcm_hw_refine_old_user(काष्ठा snd_pcm_substream *substream,
				      काष्ठा snd_pcm_hw_params_old __user * _oparams);
अटल पूर्णांक snd_pcm_hw_params_old_user(काष्ठा snd_pcm_substream *substream,
				      काष्ठा snd_pcm_hw_params_old __user * _oparams);
#पूर्ण_अगर
अटल पूर्णांक snd_pcm_खोलो(काष्ठा file *file, काष्ठा snd_pcm *pcm, पूर्णांक stream);

/*
 *
 */

अटल DECLARE_RWSEM(snd_pcm_link_rwsem);

व्योम snd_pcm_group_init(काष्ठा snd_pcm_group *group)
अणु
	spin_lock_init(&group->lock);
	mutex_init(&group->mutex);
	INIT_LIST_HEAD(&group->substreams);
	refcount_set(&group->refs, 1);
पूर्ण

/* define group lock helpers */
#घोषणा DEFINE_PCM_GROUP_LOCK(action, mutex_action) \
अटल व्योम snd_pcm_group_ ## action(काष्ठा snd_pcm_group *group, bool nonatomic) \
अणु \
	अगर (nonatomic) \
		mutex_ ## mutex_action(&group->mutex); \
	अन्यथा \
		spin_ ## action(&group->lock); \
पूर्ण

DEFINE_PCM_GROUP_LOCK(lock, lock);
DEFINE_PCM_GROUP_LOCK(unlock, unlock);
DEFINE_PCM_GROUP_LOCK(lock_irq, lock);
DEFINE_PCM_GROUP_LOCK(unlock_irq, unlock);

/**
 * snd_pcm_stream_lock - Lock the PCM stream
 * @substream: PCM substream
 *
 * This locks the PCM stream's spinlock or mutex depending on the nonatomic
 * flag of the given substream.  This also takes the global link rw lock
 * (or rw sem), too, क्रम aव्योमing the race with linked streams.
 */
व्योम snd_pcm_stream_lock(काष्ठा snd_pcm_substream *substream)
अणु
	snd_pcm_group_lock(&substream->self_group, substream->pcm->nonatomic);
पूर्ण
EXPORT_SYMBOL_GPL(snd_pcm_stream_lock);

/**
 * snd_pcm_stream_unlock - Unlock the PCM stream
 * @substream: PCM substream
 *
 * This unlocks the PCM stream that has been locked via snd_pcm_stream_lock().
 */
व्योम snd_pcm_stream_unlock(काष्ठा snd_pcm_substream *substream)
अणु
	snd_pcm_group_unlock(&substream->self_group, substream->pcm->nonatomic);
पूर्ण
EXPORT_SYMBOL_GPL(snd_pcm_stream_unlock);

/**
 * snd_pcm_stream_lock_irq - Lock the PCM stream
 * @substream: PCM substream
 *
 * This locks the PCM stream like snd_pcm_stream_lock() and disables the local
 * IRQ (only when nonatomic is false).  In nonatomic हाल, this is identical
 * as snd_pcm_stream_lock().
 */
व्योम snd_pcm_stream_lock_irq(काष्ठा snd_pcm_substream *substream)
अणु
	snd_pcm_group_lock_irq(&substream->self_group,
			       substream->pcm->nonatomic);
पूर्ण
EXPORT_SYMBOL_GPL(snd_pcm_stream_lock_irq);

अटल व्योम snd_pcm_stream_lock_nested(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_group *group = &substream->self_group;

	अगर (substream->pcm->nonatomic)
		mutex_lock_nested(&group->mutex, SINGLE_DEPTH_NESTING);
	अन्यथा
		spin_lock_nested(&group->lock, SINGLE_DEPTH_NESTING);
पूर्ण

/**
 * snd_pcm_stream_unlock_irq - Unlock the PCM stream
 * @substream: PCM substream
 *
 * This is a counter-part of snd_pcm_stream_lock_irq().
 */
व्योम snd_pcm_stream_unlock_irq(काष्ठा snd_pcm_substream *substream)
अणु
	snd_pcm_group_unlock_irq(&substream->self_group,
				 substream->pcm->nonatomic);
पूर्ण
EXPORT_SYMBOL_GPL(snd_pcm_stream_unlock_irq);

अचिन्हित दीर्घ _snd_pcm_stream_lock_irqsave(काष्ठा snd_pcm_substream *substream)
अणु
	अचिन्हित दीर्घ flags = 0;
	अगर (substream->pcm->nonatomic)
		mutex_lock(&substream->self_group.mutex);
	अन्यथा
		spin_lock_irqsave(&substream->self_group.lock, flags);
	वापस flags;
पूर्ण
EXPORT_SYMBOL_GPL(_snd_pcm_stream_lock_irqsave);

/**
 * snd_pcm_stream_unlock_irqrestore - Unlock the PCM stream
 * @substream: PCM substream
 * @flags: irq flags
 *
 * This is a counter-part of snd_pcm_stream_lock_irqsave().
 */
व्योम snd_pcm_stream_unlock_irqrestore(काष्ठा snd_pcm_substream *substream,
				      अचिन्हित दीर्घ flags)
अणु
	अगर (substream->pcm->nonatomic)
		mutex_unlock(&substream->self_group.mutex);
	अन्यथा
		spin_unlock_irqrestore(&substream->self_group.lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(snd_pcm_stream_unlock_irqrestore);

/* Run PCM ioctl ops */
अटल पूर्णांक snd_pcm_ops_ioctl(काष्ठा snd_pcm_substream *substream,
			     अचिन्हित cmd, व्योम *arg)
अणु
	अगर (substream->ops->ioctl)
		वापस substream->ops->ioctl(substream, cmd, arg);
	अन्यथा
		वापस snd_pcm_lib_ioctl(substream, cmd, arg);
पूर्ण

पूर्णांक snd_pcm_info(काष्ठा snd_pcm_substream *substream, काष्ठा snd_pcm_info *info)
अणु
	काष्ठा snd_pcm *pcm = substream->pcm;
	काष्ठा snd_pcm_str *pstr = substream->pstr;

	स_रखो(info, 0, माप(*info));
	info->card = pcm->card->number;
	info->device = pcm->device;
	info->stream = substream->stream;
	info->subdevice = substream->number;
	strscpy(info->id, pcm->id, माप(info->id));
	strscpy(info->name, pcm->name, माप(info->name));
	info->dev_class = pcm->dev_class;
	info->dev_subclass = pcm->dev_subclass;
	info->subdevices_count = pstr->substream_count;
	info->subdevices_avail = pstr->substream_count - pstr->substream_खोलोed;
	strscpy(info->subname, substream->name, माप(info->subname));

	वापस 0;
पूर्ण

पूर्णांक snd_pcm_info_user(काष्ठा snd_pcm_substream *substream,
		      काष्ठा snd_pcm_info __user * _info)
अणु
	काष्ठा snd_pcm_info *info;
	पूर्णांक err;

	info = kदो_स्मृति(माप(*info), GFP_KERNEL);
	अगर (! info)
		वापस -ENOMEM;
	err = snd_pcm_info(substream, info);
	अगर (err >= 0) अणु
		अगर (copy_to_user(_info, info, माप(*info)))
			err = -EFAULT;
	पूर्ण
	kमुक्त(info);
	वापस err;
पूर्ण

/* macro क्रम simplअगरied cast */
#घोषणा PARAM_MASK_BIT(b)	(1U << (__क्रमce पूर्णांक)(b))

अटल bool hw_support_mmap(काष्ठा snd_pcm_substream *substream)
अणु
	अगर (!(substream->runसमय->hw.info & SNDRV_PCM_INFO_MMAP))
		वापस false;

	अगर (substream->ops->mmap ||
	    (substream->dma_buffer.dev.type != SNDRV_DMA_TYPE_DEV &&
	     substream->dma_buffer.dev.type != SNDRV_DMA_TYPE_DEV_UC))
		वापस true;

	वापस dma_can_mmap(substream->dma_buffer.dev.dev);
पूर्ण

अटल पूर्णांक स्थिरrain_mask_params(काष्ठा snd_pcm_substream *substream,
				 काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_pcm_hw_स्थिरraपूर्णांकs *स्थिरrs =
					&substream->runसमय->hw_स्थिरraपूर्णांकs;
	काष्ठा snd_mask *m;
	अचिन्हित पूर्णांक k;
	काष्ठा snd_mask old_mask;
	पूर्णांक changed;

	क्रम (k = SNDRV_PCM_HW_PARAM_FIRST_MASK; k <= SNDRV_PCM_HW_PARAM_LAST_MASK; k++) अणु
		m = hw_param_mask(params, k);
		अगर (snd_mask_empty(m))
			वापस -EINVAL;

		/* This parameter is not requested to change by a caller. */
		अगर (!(params->rmask & PARAM_MASK_BIT(k)))
			जारी;

		अगर (trace_hw_mask_param_enabled())
			old_mask = *m;

		changed = snd_mask_refine(m, स्थिरrs_mask(स्थिरrs, k));
		अगर (changed < 0)
			वापस changed;
		अगर (changed == 0)
			जारी;

		/* Set corresponding flag so that the caller माला_लो it. */
		trace_hw_mask_param(substream, k, 0, &old_mask, m);
		params->cmask |= PARAM_MASK_BIT(k);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक स्थिरrain_पूर्णांकerval_params(काष्ठा snd_pcm_substream *substream,
				     काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_pcm_hw_स्थिरraपूर्णांकs *स्थिरrs =
					&substream->runसमय->hw_स्थिरraपूर्णांकs;
	काष्ठा snd_पूर्णांकerval *i;
	अचिन्हित पूर्णांक k;
	काष्ठा snd_पूर्णांकerval old_पूर्णांकerval;
	पूर्णांक changed;

	क्रम (k = SNDRV_PCM_HW_PARAM_FIRST_INTERVAL; k <= SNDRV_PCM_HW_PARAM_LAST_INTERVAL; k++) अणु
		i = hw_param_पूर्णांकerval(params, k);
		अगर (snd_पूर्णांकerval_empty(i))
			वापस -EINVAL;

		/* This parameter is not requested to change by a caller. */
		अगर (!(params->rmask & PARAM_MASK_BIT(k)))
			जारी;

		अगर (trace_hw_पूर्णांकerval_param_enabled())
			old_पूर्णांकerval = *i;

		changed = snd_पूर्णांकerval_refine(i, स्थिरrs_पूर्णांकerval(स्थिरrs, k));
		अगर (changed < 0)
			वापस changed;
		अगर (changed == 0)
			जारी;

		/* Set corresponding flag so that the caller माला_लो it. */
		trace_hw_पूर्णांकerval_param(substream, k, 0, &old_पूर्णांकerval, i);
		params->cmask |= PARAM_MASK_BIT(k);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक स्थिरrain_params_by_rules(काष्ठा snd_pcm_substream *substream,
				     काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_pcm_hw_स्थिरraपूर्णांकs *स्थिरrs =
					&substream->runसमय->hw_स्थिरraपूर्णांकs;
	अचिन्हित पूर्णांक k;
	अचिन्हित पूर्णांक *rstamps;
	अचिन्हित पूर्णांक vstamps[SNDRV_PCM_HW_PARAM_LAST_INTERVAL + 1];
	अचिन्हित पूर्णांक stamp;
	काष्ठा snd_pcm_hw_rule *r;
	अचिन्हित पूर्णांक d;
	काष्ठा snd_mask old_mask;
	काष्ठा snd_पूर्णांकerval old_पूर्णांकerval;
	bool again;
	पूर्णांक changed, err = 0;

	/*
	 * Each application of rule has own sequence number.
	 *
	 * Each member of 'rstamps' array represents the sequence number of
	 * recent application of corresponding rule.
	 */
	rstamps = kसुस्मृति(स्थिरrs->rules_num, माप(अचिन्हित पूर्णांक), GFP_KERNEL);
	अगर (!rstamps)
		वापस -ENOMEM;

	/*
	 * Each member of 'vstamps' array represents the sequence number of
	 * recent application of rule in which corresponding parameters were
	 * changed.
	 *
	 * In initial state, elements corresponding to parameters requested by
	 * a caller is 1. For unrequested parameters, corresponding members
	 * have 0 so that the parameters are never changed anymore.
	 */
	क्रम (k = 0; k <= SNDRV_PCM_HW_PARAM_LAST_INTERVAL; k++)
		vstamps[k] = (params->rmask & PARAM_MASK_BIT(k)) ? 1 : 0;

	/* Due to the above design, actual sequence number starts at 2. */
	stamp = 2;
retry:
	/* Apply all rules in order. */
	again = false;
	क्रम (k = 0; k < स्थिरrs->rules_num; k++) अणु
		r = &स्थिरrs->rules[k];

		/*
		 * Check condition bits of this rule. When the rule has
		 * some condition bits, parameter without the bits is
		 * never processed. SNDRV_PCM_HW_PARAMS_NO_PERIOD_WAKEUP
		 * is an example of the condition bits.
		 */
		अगर (r->cond && !(r->cond & params->flags))
			जारी;

		/*
		 * The 'deps' array includes maximum four dependencies
		 * to SNDRV_PCM_HW_PARAM_XXXs क्रम this rule. The fअगरth
		 * member of this array is a sentinel and should be
		 * negative value.
		 *
		 * This rule should be processed in this समय when dependent
		 * parameters were changed at क्रमmer applications of the other
		 * rules.
		 */
		क्रम (d = 0; r->deps[d] >= 0; d++) अणु
			अगर (vstamps[r->deps[d]] > rstamps[k])
				अवरोध;
		पूर्ण
		अगर (r->deps[d] < 0)
			जारी;

		अगर (trace_hw_mask_param_enabled()) अणु
			अगर (hw_is_mask(r->var))
				old_mask = *hw_param_mask(params, r->var);
		पूर्ण
		अगर (trace_hw_पूर्णांकerval_param_enabled()) अणु
			अगर (hw_is_पूर्णांकerval(r->var))
				old_पूर्णांकerval = *hw_param_पूर्णांकerval(params, r->var);
		पूर्ण

		changed = r->func(params, r);
		अगर (changed < 0) अणु
			err = changed;
			जाओ out;
		पूर्ण

		/*
		 * When the parameter is changed, notअगरy it to the caller
		 * by corresponding वापसed bit, then preparing क्रम next
		 * iteration.
		 */
		अगर (changed && r->var >= 0) अणु
			अगर (hw_is_mask(r->var)) अणु
				trace_hw_mask_param(substream, r->var,
					k + 1, &old_mask,
					hw_param_mask(params, r->var));
			पूर्ण
			अगर (hw_is_पूर्णांकerval(r->var)) अणु
				trace_hw_पूर्णांकerval_param(substream, r->var,
					k + 1, &old_पूर्णांकerval,
					hw_param_पूर्णांकerval(params, r->var));
			पूर्ण

			params->cmask |= PARAM_MASK_BIT(r->var);
			vstamps[r->var] = stamp;
			again = true;
		पूर्ण

		rstamps[k] = stamp++;
	पूर्ण

	/* Iterate to evaluate all rules till no parameters are changed. */
	अगर (again)
		जाओ retry;

 out:
	kमुक्त(rstamps);
	वापस err;
पूर्ण

अटल पूर्णांक fixup_unreferenced_params(काष्ठा snd_pcm_substream *substream,
				     काष्ठा snd_pcm_hw_params *params)
अणु
	स्थिर काष्ठा snd_पूर्णांकerval *i;
	स्थिर काष्ठा snd_mask *m;
	पूर्णांक err;

	अगर (!params->msbits) अणु
		i = hw_param_पूर्णांकerval_c(params, SNDRV_PCM_HW_PARAM_SAMPLE_BITS);
		अगर (snd_पूर्णांकerval_single(i))
			params->msbits = snd_पूर्णांकerval_value(i);
	पूर्ण

	अगर (!params->rate_den) अणु
		i = hw_param_पूर्णांकerval_c(params, SNDRV_PCM_HW_PARAM_RATE);
		अगर (snd_पूर्णांकerval_single(i)) अणु
			params->rate_num = snd_पूर्णांकerval_value(i);
			params->rate_den = 1;
		पूर्ण
	पूर्ण

	अगर (!params->fअगरo_size) अणु
		m = hw_param_mask_c(params, SNDRV_PCM_HW_PARAM_FORMAT);
		i = hw_param_पूर्णांकerval_c(params, SNDRV_PCM_HW_PARAM_CHANNELS);
		अगर (snd_mask_single(m) && snd_पूर्णांकerval_single(i)) अणु
			err = snd_pcm_ops_ioctl(substream,
						SNDRV_PCM_IOCTL1_FIFO_SIZE,
						params);
			अगर (err < 0)
				वापस err;
		पूर्ण
	पूर्ण

	अगर (!params->info) अणु
		params->info = substream->runसमय->hw.info;
		params->info &= ~(SNDRV_PCM_INFO_FIFO_IN_FRAMES |
				  SNDRV_PCM_INFO_DRAIN_TRIGGER);
		अगर (!hw_support_mmap(substream))
			params->info &= ~(SNDRV_PCM_INFO_MMAP |
					  SNDRV_PCM_INFO_MMAP_VALID);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक snd_pcm_hw_refine(काष्ठा snd_pcm_substream *substream,
		      काष्ठा snd_pcm_hw_params *params)
अणु
	पूर्णांक err;

	params->info = 0;
	params->fअगरo_size = 0;
	अगर (params->rmask & PARAM_MASK_BIT(SNDRV_PCM_HW_PARAM_SAMPLE_BITS))
		params->msbits = 0;
	अगर (params->rmask & PARAM_MASK_BIT(SNDRV_PCM_HW_PARAM_RATE)) अणु
		params->rate_num = 0;
		params->rate_den = 0;
	पूर्ण

	err = स्थिरrain_mask_params(substream, params);
	अगर (err < 0)
		वापस err;

	err = स्थिरrain_पूर्णांकerval_params(substream, params);
	अगर (err < 0)
		वापस err;

	err = स्थिरrain_params_by_rules(substream, params);
	अगर (err < 0)
		वापस err;

	params->rmask = 0;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(snd_pcm_hw_refine);

अटल पूर्णांक snd_pcm_hw_refine_user(काष्ठा snd_pcm_substream *substream,
				  काष्ठा snd_pcm_hw_params __user * _params)
अणु
	काष्ठा snd_pcm_hw_params *params;
	पूर्णांक err;

	params = memdup_user(_params, माप(*params));
	अगर (IS_ERR(params))
		वापस PTR_ERR(params);

	err = snd_pcm_hw_refine(substream, params);
	अगर (err < 0)
		जाओ end;

	err = fixup_unreferenced_params(substream, params);
	अगर (err < 0)
		जाओ end;

	अगर (copy_to_user(_params, params, माप(*params)))
		err = -EFAULT;
end:
	kमुक्त(params);
	वापस err;
पूर्ण

अटल पूर्णांक period_to_usecs(काष्ठा snd_pcm_runसमय *runसमय)
अणु
	पूर्णांक usecs;

	अगर (! runसमय->rate)
		वापस -1; /* invalid */

	/* take 75% of period समय as the deadline */
	usecs = (750000 / runसमय->rate) * runसमय->period_size;
	usecs += ((750000 % runसमय->rate) * runसमय->period_size) /
		runसमय->rate;

	वापस usecs;
पूर्ण

अटल व्योम snd_pcm_set_state(काष्ठा snd_pcm_substream *substream,
			      snd_pcm_state_t state)
अणु
	snd_pcm_stream_lock_irq(substream);
	अगर (substream->runसमय->status->state != SNDRV_PCM_STATE_DISCONNECTED)
		substream->runसमय->status->state = state;
	snd_pcm_stream_unlock_irq(substream);
पूर्ण

अटल अंतरभूत व्योम snd_pcm_समयr_notअगरy(काष्ठा snd_pcm_substream *substream,
					पूर्णांक event)
अणु
#अगर_घोषित CONFIG_SND_PCM_TIMER
	अगर (substream->समयr)
		snd_समयr_notअगरy(substream->समयr, event,
					&substream->runसमय->trigger_tstamp);
#पूर्ण_अगर
पूर्ण

व्योम snd_pcm_sync_stop(काष्ठा snd_pcm_substream *substream, bool sync_irq)
अणु
	अगर (substream->runसमय && substream->runसमय->stop_operating) अणु
		substream->runसमय->stop_operating = false;
		अगर (substream->ops && substream->ops->sync_stop)
			substream->ops->sync_stop(substream);
		अन्यथा अगर (sync_irq && substream->pcm->card->sync_irq > 0)
			synchronize_irq(substream->pcm->card->sync_irq);
	पूर्ण
पूर्ण

/**
 * snd_pcm_hw_params_choose - choose a configuration defined by @params
 * @pcm: PCM instance
 * @params: the hw_params instance
 *
 * Choose one configuration from configuration space defined by @params.
 * The configuration chosen is that obtained fixing in this order:
 * first access, first क्रमmat, first subक्रमmat, min channels,
 * min rate, min period समय, max buffer size, min tick समय
 *
 * Return: Zero अगर successful, or a negative error code on failure.
 */
अटल पूर्णांक snd_pcm_hw_params_choose(काष्ठा snd_pcm_substream *pcm,
				    काष्ठा snd_pcm_hw_params *params)
अणु
	अटल स्थिर पूर्णांक vars[] = अणु
		SNDRV_PCM_HW_PARAM_ACCESS,
		SNDRV_PCM_HW_PARAM_FORMAT,
		SNDRV_PCM_HW_PARAM_SUBFORMAT,
		SNDRV_PCM_HW_PARAM_CHANNELS,
		SNDRV_PCM_HW_PARAM_RATE,
		SNDRV_PCM_HW_PARAM_PERIOD_TIME,
		SNDRV_PCM_HW_PARAM_BUFFER_SIZE,
		SNDRV_PCM_HW_PARAM_TICK_TIME,
		-1
	पूर्ण;
	स्थिर पूर्णांक *v;
	काष्ठा snd_mask old_mask;
	काष्ठा snd_पूर्णांकerval old_पूर्णांकerval;
	पूर्णांक changed;

	क्रम (v = vars; *v != -1; v++) अणु
		/* Keep old parameter to trace. */
		अगर (trace_hw_mask_param_enabled()) अणु
			अगर (hw_is_mask(*v))
				old_mask = *hw_param_mask(params, *v);
		पूर्ण
		अगर (trace_hw_पूर्णांकerval_param_enabled()) अणु
			अगर (hw_is_पूर्णांकerval(*v))
				old_पूर्णांकerval = *hw_param_पूर्णांकerval(params, *v);
		पूर्ण
		अगर (*v != SNDRV_PCM_HW_PARAM_BUFFER_SIZE)
			changed = snd_pcm_hw_param_first(pcm, params, *v, शून्य);
		अन्यथा
			changed = snd_pcm_hw_param_last(pcm, params, *v, शून्य);
		अगर (changed < 0)
			वापस changed;
		अगर (changed == 0)
			जारी;

		/* Trace the changed parameter. */
		अगर (hw_is_mask(*v)) अणु
			trace_hw_mask_param(pcm, *v, 0, &old_mask,
					    hw_param_mask(params, *v));
		पूर्ण
		अगर (hw_is_पूर्णांकerval(*v)) अणु
			trace_hw_पूर्णांकerval_param(pcm, *v, 0, &old_पूर्णांकerval,
						hw_param_पूर्णांकerval(params, *v));
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक snd_pcm_hw_params(काष्ठा snd_pcm_substream *substream,
			     काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_pcm_runसमय *runसमय;
	पूर्णांक err, usecs;
	अचिन्हित पूर्णांक bits;
	snd_pcm_uframes_t frames;

	अगर (PCM_RUNTIME_CHECK(substream))
		वापस -ENXIO;
	runसमय = substream->runसमय;
	snd_pcm_stream_lock_irq(substream);
	चयन (runसमय->status->state) अणु
	हाल SNDRV_PCM_STATE_OPEN:
	हाल SNDRV_PCM_STATE_SETUP:
	हाल SNDRV_PCM_STATE_PREPARED:
		अवरोध;
	शेष:
		snd_pcm_stream_unlock_irq(substream);
		वापस -EBADFD;
	पूर्ण
	snd_pcm_stream_unlock_irq(substream);
#अगर IS_ENABLED(CONFIG_SND_PCM_OSS)
	अगर (!substream->oss.oss)
#पूर्ण_अगर
		अगर (atomic_पढ़ो(&substream->mmap_count))
			वापस -EBADFD;

	snd_pcm_sync_stop(substream, true);

	params->rmask = ~0U;
	err = snd_pcm_hw_refine(substream, params);
	अगर (err < 0)
		जाओ _error;

	err = snd_pcm_hw_params_choose(substream, params);
	अगर (err < 0)
		जाओ _error;

	err = fixup_unreferenced_params(substream, params);
	अगर (err < 0)
		जाओ _error;

	अगर (substream->managed_buffer_alloc) अणु
		err = snd_pcm_lib_दो_स्मृति_pages(substream,
					       params_buffer_bytes(params));
		अगर (err < 0)
			जाओ _error;
		runसमय->buffer_changed = err > 0;
	पूर्ण

	अगर (substream->ops->hw_params != शून्य) अणु
		err = substream->ops->hw_params(substream, params);
		अगर (err < 0)
			जाओ _error;
	पूर्ण

	runसमय->access = params_access(params);
	runसमय->क्रमmat = params_क्रमmat(params);
	runसमय->subक्रमmat = params_subक्रमmat(params);
	runसमय->channels = params_channels(params);
	runसमय->rate = params_rate(params);
	runसमय->period_size = params_period_size(params);
	runसमय->periods = params_periods(params);
	runसमय->buffer_size = params_buffer_size(params);
	runसमय->info = params->info;
	runसमय->rate_num = params->rate_num;
	runसमय->rate_den = params->rate_den;
	runसमय->no_period_wakeup =
			(params->info & SNDRV_PCM_INFO_NO_PERIOD_WAKEUP) &&
			(params->flags & SNDRV_PCM_HW_PARAMS_NO_PERIOD_WAKEUP);

	bits = snd_pcm_क्रमmat_physical_width(runसमय->क्रमmat);
	runसमय->sample_bits = bits;
	bits *= runसमय->channels;
	runसमय->frame_bits = bits;
	frames = 1;
	जबतक (bits % 8 != 0) अणु
		bits *= 2;
		frames *= 2;
	पूर्ण
	runसमय->byte_align = bits / 8;
	runसमय->min_align = frames;

	/* Default sw params */
	runसमय->tstamp_mode = SNDRV_PCM_TSTAMP_NONE;
	runसमय->period_step = 1;
	runसमय->control->avail_min = runसमय->period_size;
	runसमय->start_threshold = 1;
	runसमय->stop_threshold = runसमय->buffer_size;
	runसमय->silence_threshold = 0;
	runसमय->silence_size = 0;
	runसमय->boundary = runसमय->buffer_size;
	जबतक (runसमय->boundary * 2 <= दीर्घ_उच्च - runसमय->buffer_size)
		runसमय->boundary *= 2;

	/* clear the buffer क्रम aव्योमing possible kernel info leaks */
	अगर (runसमय->dma_area && !substream->ops->copy_user) अणु
		माप_प्रकार size = runसमय->dma_bytes;

		अगर (runसमय->info & SNDRV_PCM_INFO_MMAP)
			size = PAGE_ALIGN(size);
		स_रखो(runसमय->dma_area, 0, size);
	पूर्ण

	snd_pcm_समयr_resolution_change(substream);
	snd_pcm_set_state(substream, SNDRV_PCM_STATE_SETUP);

	अगर (cpu_latency_qos_request_active(&substream->latency_pm_qos_req))
		cpu_latency_qos_हटाओ_request(&substream->latency_pm_qos_req);
	अगर ((usecs = period_to_usecs(runसमय)) >= 0)
		cpu_latency_qos_add_request(&substream->latency_pm_qos_req,
					    usecs);
	वापस 0;
 _error:
	/* hardware might be unusable from this समय,
	   so we क्रमce application to retry to set
	   the correct hardware parameter settings */
	snd_pcm_set_state(substream, SNDRV_PCM_STATE_OPEN);
	अगर (substream->ops->hw_मुक्त != शून्य)
		substream->ops->hw_मुक्त(substream);
	अगर (substream->managed_buffer_alloc)
		snd_pcm_lib_मुक्त_pages(substream);
	वापस err;
पूर्ण

अटल पूर्णांक snd_pcm_hw_params_user(काष्ठा snd_pcm_substream *substream,
				  काष्ठा snd_pcm_hw_params __user * _params)
अणु
	काष्ठा snd_pcm_hw_params *params;
	पूर्णांक err;

	params = memdup_user(_params, माप(*params));
	अगर (IS_ERR(params))
		वापस PTR_ERR(params);

	err = snd_pcm_hw_params(substream, params);
	अगर (err < 0)
		जाओ end;

	अगर (copy_to_user(_params, params, माप(*params)))
		err = -EFAULT;
end:
	kमुक्त(params);
	वापस err;
पूर्ण

अटल पूर्णांक करो_hw_मुक्त(काष्ठा snd_pcm_substream *substream)
अणु
	पूर्णांक result = 0;

	snd_pcm_sync_stop(substream, true);
	अगर (substream->ops->hw_मुक्त)
		result = substream->ops->hw_मुक्त(substream);
	अगर (substream->managed_buffer_alloc)
		snd_pcm_lib_मुक्त_pages(substream);
	वापस result;
पूर्ण

अटल पूर्णांक snd_pcm_hw_मुक्त(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय;
	पूर्णांक result;

	अगर (PCM_RUNTIME_CHECK(substream))
		वापस -ENXIO;
	runसमय = substream->runसमय;
	snd_pcm_stream_lock_irq(substream);
	चयन (runसमय->status->state) अणु
	हाल SNDRV_PCM_STATE_SETUP:
	हाल SNDRV_PCM_STATE_PREPARED:
		अवरोध;
	शेष:
		snd_pcm_stream_unlock_irq(substream);
		वापस -EBADFD;
	पूर्ण
	snd_pcm_stream_unlock_irq(substream);
	अगर (atomic_पढ़ो(&substream->mmap_count))
		वापस -EBADFD;
	result = करो_hw_मुक्त(substream);
	snd_pcm_set_state(substream, SNDRV_PCM_STATE_OPEN);
	cpu_latency_qos_हटाओ_request(&substream->latency_pm_qos_req);
	वापस result;
पूर्ण

अटल पूर्णांक snd_pcm_sw_params(काष्ठा snd_pcm_substream *substream,
			     काष्ठा snd_pcm_sw_params *params)
अणु
	काष्ठा snd_pcm_runसमय *runसमय;
	पूर्णांक err;

	अगर (PCM_RUNTIME_CHECK(substream))
		वापस -ENXIO;
	runसमय = substream->runसमय;
	snd_pcm_stream_lock_irq(substream);
	अगर (runसमय->status->state == SNDRV_PCM_STATE_OPEN) अणु
		snd_pcm_stream_unlock_irq(substream);
		वापस -EBADFD;
	पूर्ण
	snd_pcm_stream_unlock_irq(substream);

	अगर (params->tstamp_mode < 0 ||
	    params->tstamp_mode > SNDRV_PCM_TSTAMP_LAST)
		वापस -EINVAL;
	अगर (params->proto >= SNDRV_PROTOCOL_VERSION(2, 0, 12) &&
	    params->tstamp_type > SNDRV_PCM_TSTAMP_TYPE_LAST)
		वापस -EINVAL;
	अगर (params->avail_min == 0)
		वापस -EINVAL;
	अगर (params->silence_size >= runसमय->boundary) अणु
		अगर (params->silence_threshold != 0)
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		अगर (params->silence_size > params->silence_threshold)
			वापस -EINVAL;
		अगर (params->silence_threshold > runसमय->buffer_size)
			वापस -EINVAL;
	पूर्ण
	err = 0;
	snd_pcm_stream_lock_irq(substream);
	runसमय->tstamp_mode = params->tstamp_mode;
	अगर (params->proto >= SNDRV_PROTOCOL_VERSION(2, 0, 12))
		runसमय->tstamp_type = params->tstamp_type;
	runसमय->period_step = params->period_step;
	runसमय->control->avail_min = params->avail_min;
	runसमय->start_threshold = params->start_threshold;
	runसमय->stop_threshold = params->stop_threshold;
	runसमय->silence_threshold = params->silence_threshold;
	runसमय->silence_size = params->silence_size;
        params->boundary = runसमय->boundary;
	अगर (snd_pcm_running(substream)) अणु
		अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK &&
		    runसमय->silence_size > 0)
			snd_pcm_playback_silence(substream, अच_दीर्घ_उच्च);
		err = snd_pcm_update_state(substream, runसमय);
	पूर्ण
	snd_pcm_stream_unlock_irq(substream);
	वापस err;
पूर्ण

अटल पूर्णांक snd_pcm_sw_params_user(काष्ठा snd_pcm_substream *substream,
				  काष्ठा snd_pcm_sw_params __user * _params)
अणु
	काष्ठा snd_pcm_sw_params params;
	पूर्णांक err;
	अगर (copy_from_user(&params, _params, माप(params)))
		वापस -EFAULT;
	err = snd_pcm_sw_params(substream, &params);
	अगर (copy_to_user(_params, &params, माप(params)))
		वापस -EFAULT;
	वापस err;
पूर्ण

अटल अंतरभूत snd_pcm_uframes_t
snd_pcm_calc_delay(काष्ठा snd_pcm_substream *substream)
अणु
	snd_pcm_uframes_t delay;

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		delay = snd_pcm_playback_hw_avail(substream->runसमय);
	अन्यथा
		delay = snd_pcm_capture_avail(substream->runसमय);
	वापस delay + substream->runसमय->delay;
पूर्ण

पूर्णांक snd_pcm_status64(काष्ठा snd_pcm_substream *substream,
		     काष्ठा snd_pcm_status64 *status)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;

	snd_pcm_stream_lock_irq(substream);

	snd_pcm_unpack_audio_tstamp_config(status->audio_tstamp_data,
					&runसमय->audio_tstamp_config);

	/* backwards compatible behavior */
	अगर (runसमय->audio_tstamp_config.type_requested ==
		SNDRV_PCM_AUDIO_TSTAMP_TYPE_COMPAT) अणु
		अगर (runसमय->hw.info & SNDRV_PCM_INFO_HAS_WALL_CLOCK)
			runसमय->audio_tstamp_config.type_requested =
				SNDRV_PCM_AUDIO_TSTAMP_TYPE_LINK;
		अन्यथा
			runसमय->audio_tstamp_config.type_requested =
				SNDRV_PCM_AUDIO_TSTAMP_TYPE_DEFAULT;
		runसमय->audio_tstamp_report.valid = 0;
	पूर्ण अन्यथा
		runसमय->audio_tstamp_report.valid = 1;

	status->state = runसमय->status->state;
	status->suspended_state = runसमय->status->suspended_state;
	अगर (status->state == SNDRV_PCM_STATE_OPEN)
		जाओ _end;
	status->trigger_tstamp_sec = runसमय->trigger_tstamp.tv_sec;
	status->trigger_tstamp_nsec = runसमय->trigger_tstamp.tv_nsec;
	अगर (snd_pcm_running(substream)) अणु
		snd_pcm_update_hw_ptr(substream);
		अगर (runसमय->tstamp_mode == SNDRV_PCM_TSTAMP_ENABLE) अणु
			status->tstamp_sec = runसमय->status->tstamp.tv_sec;
			status->tstamp_nsec =
				runसमय->status->tstamp.tv_nsec;
			status->driver_tstamp_sec =
				runसमय->driver_tstamp.tv_sec;
			status->driver_tstamp_nsec =
				runसमय->driver_tstamp.tv_nsec;
			status->audio_tstamp_sec =
				runसमय->status->audio_tstamp.tv_sec;
			status->audio_tstamp_nsec =
				runसमय->status->audio_tstamp.tv_nsec;
			अगर (runसमय->audio_tstamp_report.valid == 1)
				/* backwards compatibility, no report provided in COMPAT mode */
				snd_pcm_pack_audio_tstamp_report(&status->audio_tstamp_data,
								&status->audio_tstamp_accuracy,
								&runसमय->audio_tstamp_report);

			जाओ _tstamp_end;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* get tstamp only in fallback mode and only अगर enabled */
		अगर (runसमय->tstamp_mode == SNDRV_PCM_TSTAMP_ENABLE) अणु
			काष्ठा बारpec64 tstamp;

			snd_pcm_समय_लो(runसमय, &tstamp);
			status->tstamp_sec = tstamp.tv_sec;
			status->tstamp_nsec = tstamp.tv_nsec;
		पूर्ण
	पूर्ण
 _tstamp_end:
	status->appl_ptr = runसमय->control->appl_ptr;
	status->hw_ptr = runसमय->status->hw_ptr;
	status->avail = snd_pcm_avail(substream);
	status->delay = snd_pcm_running(substream) ?
		snd_pcm_calc_delay(substream) : 0;
	status->avail_max = runसमय->avail_max;
	status->overrange = runसमय->overrange;
	runसमय->avail_max = 0;
	runसमय->overrange = 0;
 _end:
 	snd_pcm_stream_unlock_irq(substream);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_pcm_status_user64(काष्ठा snd_pcm_substream *substream,
				 काष्ठा snd_pcm_status64 __user * _status,
				 bool ext)
अणु
	काष्ठा snd_pcm_status64 status;
	पूर्णांक res;

	स_रखो(&status, 0, माप(status));
	/*
	 * with extension, parameters are पढ़ो/ग_लिखो,
	 * get audio_tstamp_data from user,
	 * ignore rest of status काष्ठाure
	 */
	अगर (ext && get_user(status.audio_tstamp_data,
				(u32 __user *)(&_status->audio_tstamp_data)))
		वापस -EFAULT;
	res = snd_pcm_status64(substream, &status);
	अगर (res < 0)
		वापस res;
	अगर (copy_to_user(_status, &status, माप(status)))
		वापस -EFAULT;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_pcm_status_user32(काष्ठा snd_pcm_substream *substream,
				 काष्ठा snd_pcm_status32 __user * _status,
				 bool ext)
अणु
	काष्ठा snd_pcm_status64 status64;
	काष्ठा snd_pcm_status32 status32;
	पूर्णांक res;

	स_रखो(&status64, 0, माप(status64));
	स_रखो(&status32, 0, माप(status32));
	/*
	 * with extension, parameters are पढ़ो/ग_लिखो,
	 * get audio_tstamp_data from user,
	 * ignore rest of status काष्ठाure
	 */
	अगर (ext && get_user(status64.audio_tstamp_data,
			    (u32 __user *)(&_status->audio_tstamp_data)))
		वापस -EFAULT;
	res = snd_pcm_status64(substream, &status64);
	अगर (res < 0)
		वापस res;

	status32 = (काष्ठा snd_pcm_status32) अणु
		.state = status64.state,
		.trigger_tstamp_sec = status64.trigger_tstamp_sec,
		.trigger_tstamp_nsec = status64.trigger_tstamp_nsec,
		.tstamp_sec = status64.tstamp_sec,
		.tstamp_nsec = status64.tstamp_nsec,
		.appl_ptr = status64.appl_ptr,
		.hw_ptr = status64.hw_ptr,
		.delay = status64.delay,
		.avail = status64.avail,
		.avail_max = status64.avail_max,
		.overrange = status64.overrange,
		.suspended_state = status64.suspended_state,
		.audio_tstamp_data = status64.audio_tstamp_data,
		.audio_tstamp_sec = status64.audio_tstamp_sec,
		.audio_tstamp_nsec = status64.audio_tstamp_nsec,
		.driver_tstamp_sec = status64.audio_tstamp_sec,
		.driver_tstamp_nsec = status64.audio_tstamp_nsec,
		.audio_tstamp_accuracy = status64.audio_tstamp_accuracy,
	पूर्ण;

	अगर (copy_to_user(_status, &status32, माप(status32)))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल पूर्णांक snd_pcm_channel_info(काष्ठा snd_pcm_substream *substream,
				काष्ठा snd_pcm_channel_info * info)
अणु
	काष्ठा snd_pcm_runसमय *runसमय;
	अचिन्हित पूर्णांक channel;
	
	channel = info->channel;
	runसमय = substream->runसमय;
	snd_pcm_stream_lock_irq(substream);
	अगर (runसमय->status->state == SNDRV_PCM_STATE_OPEN) अणु
		snd_pcm_stream_unlock_irq(substream);
		वापस -EBADFD;
	पूर्ण
	snd_pcm_stream_unlock_irq(substream);
	अगर (channel >= runसमय->channels)
		वापस -EINVAL;
	स_रखो(info, 0, माप(*info));
	info->channel = channel;
	वापस snd_pcm_ops_ioctl(substream, SNDRV_PCM_IOCTL1_CHANNEL_INFO, info);
पूर्ण

अटल पूर्णांक snd_pcm_channel_info_user(काष्ठा snd_pcm_substream *substream,
				     काष्ठा snd_pcm_channel_info __user * _info)
अणु
	काष्ठा snd_pcm_channel_info info;
	पूर्णांक res;
	
	अगर (copy_from_user(&info, _info, माप(info)))
		वापस -EFAULT;
	res = snd_pcm_channel_info(substream, &info);
	अगर (res < 0)
		वापस res;
	अगर (copy_to_user(_info, &info, माप(info)))
		वापस -EFAULT;
	वापस 0;
पूर्ण

अटल व्योम snd_pcm_trigger_tstamp(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	अगर (runसमय->trigger_master == शून्य)
		वापस;
	अगर (runसमय->trigger_master == substream) अणु
		अगर (!runसमय->trigger_tstamp_latched)
			snd_pcm_समय_लो(runसमय, &runसमय->trigger_tstamp);
	पूर्ण अन्यथा अणु
		snd_pcm_trigger_tstamp(runसमय->trigger_master);
		runसमय->trigger_tstamp = runसमय->trigger_master->runसमय->trigger_tstamp;
	पूर्ण
	runसमय->trigger_master = शून्य;
पूर्ण

#घोषणा ACTION_ARG_IGNORE	(__क्रमce snd_pcm_state_t)0

काष्ठा action_ops अणु
	पूर्णांक (*pre_action)(काष्ठा snd_pcm_substream *substream,
			  snd_pcm_state_t state);
	पूर्णांक (*करो_action)(काष्ठा snd_pcm_substream *substream,
			 snd_pcm_state_t state);
	व्योम (*unकरो_action)(काष्ठा snd_pcm_substream *substream,
			    snd_pcm_state_t state);
	व्योम (*post_action)(काष्ठा snd_pcm_substream *substream,
			    snd_pcm_state_t state);
पूर्ण;

/*
 *  this functions is core क्रम handling of linked stream
 *  Note: the stream state might be changed also on failure
 *  Note2: call with calling stream lock + link lock
 */
अटल पूर्णांक snd_pcm_action_group(स्थिर काष्ठा action_ops *ops,
				काष्ठा snd_pcm_substream *substream,
				snd_pcm_state_t state,
				bool करो_lock)
अणु
	काष्ठा snd_pcm_substream *s = शून्य;
	काष्ठा snd_pcm_substream *s1;
	पूर्णांक res = 0, depth = 1;

	snd_pcm_group_क्रम_each_entry(s, substream) अणु
		अगर (करो_lock && s != substream) अणु
			अगर (s->pcm->nonatomic)
				mutex_lock_nested(&s->self_group.mutex, depth);
			अन्यथा
				spin_lock_nested(&s->self_group.lock, depth);
			depth++;
		पूर्ण
		res = ops->pre_action(s, state);
		अगर (res < 0)
			जाओ _unlock;
	पूर्ण
	snd_pcm_group_क्रम_each_entry(s, substream) अणु
		res = ops->करो_action(s, state);
		अगर (res < 0) अणु
			अगर (ops->unकरो_action) अणु
				snd_pcm_group_क्रम_each_entry(s1, substream) अणु
					अगर (s1 == s) /* failed stream */
						अवरोध;
					ops->unकरो_action(s1, state);
				पूर्ण
			पूर्ण
			s = शून्य; /* unlock all */
			जाओ _unlock;
		पूर्ण
	पूर्ण
	snd_pcm_group_क्रम_each_entry(s, substream) अणु
		ops->post_action(s, state);
	पूर्ण
 _unlock:
	अगर (करो_lock) अणु
		/* unlock streams */
		snd_pcm_group_क्रम_each_entry(s1, substream) अणु
			अगर (s1 != substream) अणु
				अगर (s1->pcm->nonatomic)
					mutex_unlock(&s1->self_group.mutex);
				अन्यथा
					spin_unlock(&s1->self_group.lock);
			पूर्ण
			अगर (s1 == s)	/* end */
				अवरोध;
		पूर्ण
	पूर्ण
	वापस res;
पूर्ण

/*
 *  Note: call with stream lock
 */
अटल पूर्णांक snd_pcm_action_single(स्थिर काष्ठा action_ops *ops,
				 काष्ठा snd_pcm_substream *substream,
				 snd_pcm_state_t state)
अणु
	पूर्णांक res;
	
	res = ops->pre_action(substream, state);
	अगर (res < 0)
		वापस res;
	res = ops->करो_action(substream, state);
	अगर (res == 0)
		ops->post_action(substream, state);
	अन्यथा अगर (ops->unकरो_action)
		ops->unकरो_action(substream, state);
	वापस res;
पूर्ण

अटल व्योम snd_pcm_group_assign(काष्ठा snd_pcm_substream *substream,
				 काष्ठा snd_pcm_group *new_group)
अणु
	substream->group = new_group;
	list_move(&substream->link_list, &new_group->substreams);
पूर्ण

/*
 * Unref and unlock the group, but keep the stream lock;
 * when the group becomes empty and no दीर्घer referred, destroy itself
 */
अटल व्योम snd_pcm_group_unref(काष्ठा snd_pcm_group *group,
				काष्ठा snd_pcm_substream *substream)
अणु
	bool करो_मुक्त;

	अगर (!group)
		वापस;
	करो_मुक्त = refcount_dec_and_test(&group->refs);
	snd_pcm_group_unlock(group, substream->pcm->nonatomic);
	अगर (करो_मुक्त)
		kमुक्त(group);
पूर्ण

/*
 * Lock the group inside a stream lock and reference it;
 * वापस the locked group object, or शून्य अगर not linked
 */
अटल काष्ठा snd_pcm_group *
snd_pcm_stream_group_ref(काष्ठा snd_pcm_substream *substream)
अणु
	bool nonatomic = substream->pcm->nonatomic;
	काष्ठा snd_pcm_group *group;
	bool trylock;

	क्रम (;;) अणु
		अगर (!snd_pcm_stream_linked(substream))
			वापस शून्य;
		group = substream->group;
		/* block मुक्तing the group object */
		refcount_inc(&group->refs);

		trylock = nonatomic ? mutex_trylock(&group->mutex) :
			spin_trylock(&group->lock);
		अगर (trylock)
			अवरोध; /* OK */

		/* re-lock क्रम aव्योमing ABBA deadlock */
		snd_pcm_stream_unlock(substream);
		snd_pcm_group_lock(group, nonatomic);
		snd_pcm_stream_lock(substream);

		/* check the group again; the above खोलोs a small race winकरोw */
		अगर (substream->group == group)
			अवरोध; /* OK */
		/* group changed, try again */
		snd_pcm_group_unref(group, substream);
	पूर्ण
	वापस group;
पूर्ण

/*
 *  Note: call with stream lock
 */
अटल पूर्णांक snd_pcm_action(स्थिर काष्ठा action_ops *ops,
			  काष्ठा snd_pcm_substream *substream,
			  snd_pcm_state_t state)
अणु
	काष्ठा snd_pcm_group *group;
	पूर्णांक res;

	group = snd_pcm_stream_group_ref(substream);
	अगर (group)
		res = snd_pcm_action_group(ops, substream, state, true);
	अन्यथा
		res = snd_pcm_action_single(ops, substream, state);
	snd_pcm_group_unref(group, substream);
	वापस res;
पूर्ण

/*
 *  Note: करोn't use any locks beक्रमe
 */
अटल पूर्णांक snd_pcm_action_lock_irq(स्थिर काष्ठा action_ops *ops,
				   काष्ठा snd_pcm_substream *substream,
				   snd_pcm_state_t state)
अणु
	पूर्णांक res;

	snd_pcm_stream_lock_irq(substream);
	res = snd_pcm_action(ops, substream, state);
	snd_pcm_stream_unlock_irq(substream);
	वापस res;
पूर्ण

/*
 */
अटल पूर्णांक snd_pcm_action_nonatomic(स्थिर काष्ठा action_ops *ops,
				    काष्ठा snd_pcm_substream *substream,
				    snd_pcm_state_t state)
अणु
	पूर्णांक res;

	/* Guarantee the group members won't change during non-atomic action */
	करोwn_पढ़ो(&snd_pcm_link_rwsem);
	अगर (snd_pcm_stream_linked(substream))
		res = snd_pcm_action_group(ops, substream, state, false);
	अन्यथा
		res = snd_pcm_action_single(ops, substream, state);
	up_पढ़ो(&snd_pcm_link_rwsem);
	वापस res;
पूर्ण

/*
 * start callbacks
 */
अटल पूर्णांक snd_pcm_pre_start(काष्ठा snd_pcm_substream *substream,
			     snd_pcm_state_t state)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	अगर (runसमय->status->state != SNDRV_PCM_STATE_PREPARED)
		वापस -EBADFD;
	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK &&
	    !snd_pcm_playback_data(substream))
		वापस -EPIPE;
	runसमय->trigger_tstamp_latched = false;
	runसमय->trigger_master = substream;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_pcm_करो_start(काष्ठा snd_pcm_substream *substream,
			    snd_pcm_state_t state)
अणु
	अगर (substream->runसमय->trigger_master != substream)
		वापस 0;
	वापस substream->ops->trigger(substream, SNDRV_PCM_TRIGGER_START);
पूर्ण

अटल व्योम snd_pcm_unकरो_start(काष्ठा snd_pcm_substream *substream,
			       snd_pcm_state_t state)
अणु
	अगर (substream->runसमय->trigger_master == substream)
		substream->ops->trigger(substream, SNDRV_PCM_TRIGGER_STOP);
पूर्ण

अटल व्योम snd_pcm_post_start(काष्ठा snd_pcm_substream *substream,
			       snd_pcm_state_t state)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	snd_pcm_trigger_tstamp(substream);
	runसमय->hw_ptr_jअगरfies = jअगरfies;
	runसमय->hw_ptr_buffer_jअगरfies = (runसमय->buffer_size * HZ) / 
							    runसमय->rate;
	runसमय->status->state = state;
	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK &&
	    runसमय->silence_size > 0)
		snd_pcm_playback_silence(substream, अच_दीर्घ_उच्च);
	snd_pcm_समयr_notअगरy(substream, SNDRV_TIMER_EVENT_MSTART);
पूर्ण

अटल स्थिर काष्ठा action_ops snd_pcm_action_start = अणु
	.pre_action = snd_pcm_pre_start,
	.करो_action = snd_pcm_करो_start,
	.unकरो_action = snd_pcm_unकरो_start,
	.post_action = snd_pcm_post_start
पूर्ण;

/**
 * snd_pcm_start - start all linked streams
 * @substream: the PCM substream instance
 *
 * Return: Zero अगर successful, or a negative error code.
 * The stream lock must be acquired beक्रमe calling this function.
 */
पूर्णांक snd_pcm_start(काष्ठा snd_pcm_substream *substream)
अणु
	वापस snd_pcm_action(&snd_pcm_action_start, substream,
			      SNDRV_PCM_STATE_RUNNING);
पूर्ण

/* take the stream lock and start the streams */
अटल पूर्णांक snd_pcm_start_lock_irq(काष्ठा snd_pcm_substream *substream)
अणु
	वापस snd_pcm_action_lock_irq(&snd_pcm_action_start, substream,
				       SNDRV_PCM_STATE_RUNNING);
पूर्ण

/*
 * stop callbacks
 */
अटल पूर्णांक snd_pcm_pre_stop(काष्ठा snd_pcm_substream *substream,
			    snd_pcm_state_t state)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	अगर (runसमय->status->state == SNDRV_PCM_STATE_OPEN)
		वापस -EBADFD;
	runसमय->trigger_master = substream;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_pcm_करो_stop(काष्ठा snd_pcm_substream *substream,
			   snd_pcm_state_t state)
अणु
	अगर (substream->runसमय->trigger_master == substream &&
	    snd_pcm_running(substream)) अणु
		substream->ops->trigger(substream, SNDRV_PCM_TRIGGER_STOP);
		substream->runसमय->stop_operating = true;
	पूर्ण
	वापस 0; /* unconditionally stop all substreams */
पूर्ण

अटल व्योम snd_pcm_post_stop(काष्ठा snd_pcm_substream *substream,
			      snd_pcm_state_t state)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	अगर (runसमय->status->state != state) अणु
		snd_pcm_trigger_tstamp(substream);
		runसमय->status->state = state;
		snd_pcm_समयr_notअगरy(substream, SNDRV_TIMER_EVENT_MSTOP);
	पूर्ण
	wake_up(&runसमय->sleep);
	wake_up(&runसमय->tsleep);
पूर्ण

अटल स्थिर काष्ठा action_ops snd_pcm_action_stop = अणु
	.pre_action = snd_pcm_pre_stop,
	.करो_action = snd_pcm_करो_stop,
	.post_action = snd_pcm_post_stop
पूर्ण;

/**
 * snd_pcm_stop - try to stop all running streams in the substream group
 * @substream: the PCM substream instance
 * @state: PCM state after stopping the stream
 *
 * The state of each stream is then changed to the given state unconditionally.
 *
 * Return: Zero अगर successful, or a negative error code.
 */
पूर्णांक snd_pcm_stop(काष्ठा snd_pcm_substream *substream, snd_pcm_state_t state)
अणु
	वापस snd_pcm_action(&snd_pcm_action_stop, substream, state);
पूर्ण
EXPORT_SYMBOL(snd_pcm_stop);

/**
 * snd_pcm_drain_करोne - stop the DMA only when the given stream is playback
 * @substream: the PCM substream
 *
 * After stopping, the state is changed to SETUP.
 * Unlike snd_pcm_stop(), this affects only the given stream.
 *
 * Return: Zero अगर successful, or a negative error code.
 */
पूर्णांक snd_pcm_drain_करोne(काष्ठा snd_pcm_substream *substream)
अणु
	वापस snd_pcm_action_single(&snd_pcm_action_stop, substream,
				     SNDRV_PCM_STATE_SETUP);
पूर्ण

/**
 * snd_pcm_stop_xrun - stop the running streams as XRUN
 * @substream: the PCM substream instance
 *
 * This stops the given running substream (and all linked substreams) as XRUN.
 * Unlike snd_pcm_stop(), this function takes the substream lock by itself.
 *
 * Return: Zero अगर successful, or a negative error code.
 */
पूर्णांक snd_pcm_stop_xrun(काष्ठा snd_pcm_substream *substream)
अणु
	अचिन्हित दीर्घ flags;

	snd_pcm_stream_lock_irqsave(substream, flags);
	अगर (substream->runसमय && snd_pcm_running(substream))
		__snd_pcm_xrun(substream);
	snd_pcm_stream_unlock_irqrestore(substream, flags);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_pcm_stop_xrun);

/*
 * छोड़ो callbacks: pass boolean (to start छोड़ो or resume) as state argument
 */
#घोषणा छोड़ो_pushed(state)	(__क्रमce bool)(state)

अटल पूर्णांक snd_pcm_pre_छोड़ो(काष्ठा snd_pcm_substream *substream,
			     snd_pcm_state_t state)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	अगर (!(runसमय->info & SNDRV_PCM_INFO_PAUSE))
		वापस -ENOSYS;
	अगर (छोड़ो_pushed(state)) अणु
		अगर (runसमय->status->state != SNDRV_PCM_STATE_RUNNING)
			वापस -EBADFD;
	पूर्ण अन्यथा अगर (runसमय->status->state != SNDRV_PCM_STATE_PAUSED)
		वापस -EBADFD;
	runसमय->trigger_master = substream;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_pcm_करो_छोड़ो(काष्ठा snd_pcm_substream *substream,
			    snd_pcm_state_t state)
अणु
	अगर (substream->runसमय->trigger_master != substream)
		वापस 0;
	/* some drivers might use hw_ptr to recover from the छोड़ो -
	   update the hw_ptr now */
	अगर (छोड़ो_pushed(state))
		snd_pcm_update_hw_ptr(substream);
	/* The jअगरfies check in snd_pcm_update_hw_ptr*() is करोne by
	 * a delta between the current jअगरfies, this gives a large enough
	 * delta, effectively to skip the check once.
	 */
	substream->runसमय->hw_ptr_jअगरfies = jअगरfies - HZ * 1000;
	वापस substream->ops->trigger(substream,
				       छोड़ो_pushed(state) ?
				       SNDRV_PCM_TRIGGER_PAUSE_PUSH :
				       SNDRV_PCM_TRIGGER_PAUSE_RELEASE);
पूर्ण

अटल व्योम snd_pcm_unकरो_छोड़ो(काष्ठा snd_pcm_substream *substream,
			       snd_pcm_state_t state)
अणु
	अगर (substream->runसमय->trigger_master == substream)
		substream->ops->trigger(substream,
					छोड़ो_pushed(state) ?
					SNDRV_PCM_TRIGGER_PAUSE_RELEASE :
					SNDRV_PCM_TRIGGER_PAUSE_PUSH);
पूर्ण

अटल व्योम snd_pcm_post_छोड़ो(काष्ठा snd_pcm_substream *substream,
			       snd_pcm_state_t state)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	snd_pcm_trigger_tstamp(substream);
	अगर (छोड़ो_pushed(state)) अणु
		runसमय->status->state = SNDRV_PCM_STATE_PAUSED;
		snd_pcm_समयr_notअगरy(substream, SNDRV_TIMER_EVENT_MPAUSE);
		wake_up(&runसमय->sleep);
		wake_up(&runसमय->tsleep);
	पूर्ण अन्यथा अणु
		runसमय->status->state = SNDRV_PCM_STATE_RUNNING;
		snd_pcm_समयr_notअगरy(substream, SNDRV_TIMER_EVENT_MCONTINUE);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा action_ops snd_pcm_action_छोड़ो = अणु
	.pre_action = snd_pcm_pre_छोड़ो,
	.करो_action = snd_pcm_करो_छोड़ो,
	.unकरो_action = snd_pcm_unकरो_छोड़ो,
	.post_action = snd_pcm_post_छोड़ो
पूर्ण;

/*
 * Push/release the छोड़ो क्रम all linked streams.
 */
अटल पूर्णांक snd_pcm_छोड़ो(काष्ठा snd_pcm_substream *substream, bool push)
अणु
	वापस snd_pcm_action(&snd_pcm_action_छोड़ो, substream,
			      (__क्रमce snd_pcm_state_t)push);
पूर्ण

अटल पूर्णांक snd_pcm_छोड़ो_lock_irq(काष्ठा snd_pcm_substream *substream,
				  bool push)
अणु
	वापस snd_pcm_action_lock_irq(&snd_pcm_action_छोड़ो, substream,
				       (__क्रमce snd_pcm_state_t)push);
पूर्ण

#अगर_घोषित CONFIG_PM
/* suspend callback: state argument ignored */

अटल पूर्णांक snd_pcm_pre_suspend(काष्ठा snd_pcm_substream *substream,
			       snd_pcm_state_t state)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	चयन (runसमय->status->state) अणु
	हाल SNDRV_PCM_STATE_SUSPENDED:
		वापस -EBUSY;
	/* unresumable PCM state; वापस -EBUSY क्रम skipping suspend */
	हाल SNDRV_PCM_STATE_OPEN:
	हाल SNDRV_PCM_STATE_SETUP:
	हाल SNDRV_PCM_STATE_DISCONNECTED:
		वापस -EBUSY;
	पूर्ण
	runसमय->trigger_master = substream;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_pcm_करो_suspend(काष्ठा snd_pcm_substream *substream,
			      snd_pcm_state_t state)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	अगर (runसमय->trigger_master != substream)
		वापस 0;
	अगर (! snd_pcm_running(substream))
		वापस 0;
	substream->ops->trigger(substream, SNDRV_PCM_TRIGGER_SUSPEND);
	runसमय->stop_operating = true;
	वापस 0; /* suspend unconditionally */
पूर्ण

अटल व्योम snd_pcm_post_suspend(काष्ठा snd_pcm_substream *substream,
				 snd_pcm_state_t state)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	snd_pcm_trigger_tstamp(substream);
	runसमय->status->suspended_state = runसमय->status->state;
	runसमय->status->state = SNDRV_PCM_STATE_SUSPENDED;
	snd_pcm_समयr_notअगरy(substream, SNDRV_TIMER_EVENT_MSUSPEND);
	wake_up(&runसमय->sleep);
	wake_up(&runसमय->tsleep);
पूर्ण

अटल स्थिर काष्ठा action_ops snd_pcm_action_suspend = अणु
	.pre_action = snd_pcm_pre_suspend,
	.करो_action = snd_pcm_करो_suspend,
	.post_action = snd_pcm_post_suspend
पूर्ण;

/*
 * snd_pcm_suspend - trigger SUSPEND to all linked streams
 * @substream: the PCM substream
 *
 * After this call, all streams are changed to SUSPENDED state.
 *
 * Return: Zero अगर successful, or a negative error code.
 */
अटल पूर्णांक snd_pcm_suspend(काष्ठा snd_pcm_substream *substream)
अणु
	पूर्णांक err;
	अचिन्हित दीर्घ flags;

	snd_pcm_stream_lock_irqsave(substream, flags);
	err = snd_pcm_action(&snd_pcm_action_suspend, substream,
			     ACTION_ARG_IGNORE);
	snd_pcm_stream_unlock_irqrestore(substream, flags);
	वापस err;
पूर्ण

/**
 * snd_pcm_suspend_all - trigger SUSPEND to all substreams in the given pcm
 * @pcm: the PCM instance
 *
 * After this call, all streams are changed to SUSPENDED state.
 *
 * Return: Zero अगर successful (or @pcm is %शून्य), or a negative error code.
 */
पूर्णांक snd_pcm_suspend_all(काष्ठा snd_pcm *pcm)
अणु
	काष्ठा snd_pcm_substream *substream;
	पूर्णांक stream, err = 0;

	अगर (! pcm)
		वापस 0;

	क्रम_each_pcm_substream(pcm, stream, substream) अणु
		/* FIXME: the खोलो/बंद code should lock this as well */
		अगर (!substream->runसमय)
			जारी;

		/*
		 * Skip BE dai link PCM's that are पूर्णांकernal and may
		 * not have their substream ops set.
		 */
		अगर (!substream->ops)
			जारी;

		err = snd_pcm_suspend(substream);
		अगर (err < 0 && err != -EBUSY)
			वापस err;
	पूर्ण

	क्रम_each_pcm_substream(pcm, stream, substream)
		snd_pcm_sync_stop(substream, false);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(snd_pcm_suspend_all);

/* resume callbacks: state argument ignored */

अटल पूर्णांक snd_pcm_pre_resume(काष्ठा snd_pcm_substream *substream,
			      snd_pcm_state_t state)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	अगर (!(runसमय->info & SNDRV_PCM_INFO_RESUME))
		वापस -ENOSYS;
	runसमय->trigger_master = substream;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_pcm_करो_resume(काष्ठा snd_pcm_substream *substream,
			     snd_pcm_state_t state)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	अगर (runसमय->trigger_master != substream)
		वापस 0;
	/* DMA not running previously? */
	अगर (runसमय->status->suspended_state != SNDRV_PCM_STATE_RUNNING &&
	    (runसमय->status->suspended_state != SNDRV_PCM_STATE_DRAINING ||
	     substream->stream != SNDRV_PCM_STREAM_PLAYBACK))
		वापस 0;
	वापस substream->ops->trigger(substream, SNDRV_PCM_TRIGGER_RESUME);
पूर्ण

अटल व्योम snd_pcm_unकरो_resume(काष्ठा snd_pcm_substream *substream,
				snd_pcm_state_t state)
अणु
	अगर (substream->runसमय->trigger_master == substream &&
	    snd_pcm_running(substream))
		substream->ops->trigger(substream, SNDRV_PCM_TRIGGER_SUSPEND);
पूर्ण

अटल व्योम snd_pcm_post_resume(काष्ठा snd_pcm_substream *substream,
				snd_pcm_state_t state)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	snd_pcm_trigger_tstamp(substream);
	runसमय->status->state = runसमय->status->suspended_state;
	snd_pcm_समयr_notअगरy(substream, SNDRV_TIMER_EVENT_MRESUME);
पूर्ण

अटल स्थिर काष्ठा action_ops snd_pcm_action_resume = अणु
	.pre_action = snd_pcm_pre_resume,
	.करो_action = snd_pcm_करो_resume,
	.unकरो_action = snd_pcm_unकरो_resume,
	.post_action = snd_pcm_post_resume
पूर्ण;

अटल पूर्णांक snd_pcm_resume(काष्ठा snd_pcm_substream *substream)
अणु
	वापस snd_pcm_action_lock_irq(&snd_pcm_action_resume, substream,
				       ACTION_ARG_IGNORE);
पूर्ण

#अन्यथा

अटल पूर्णांक snd_pcm_resume(काष्ठा snd_pcm_substream *substream)
अणु
	वापस -ENOSYS;
पूर्ण

#पूर्ण_अगर /* CONFIG_PM */

/*
 * xrun ioctl
 *
 * Change the RUNNING stream(s) to XRUN state.
 */
अटल पूर्णांक snd_pcm_xrun(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	पूर्णांक result;

	snd_pcm_stream_lock_irq(substream);
	चयन (runसमय->status->state) अणु
	हाल SNDRV_PCM_STATE_XRUN:
		result = 0;	/* alपढ़ोy there */
		अवरोध;
	हाल SNDRV_PCM_STATE_RUNNING:
		__snd_pcm_xrun(substream);
		result = 0;
		अवरोध;
	शेष:
		result = -EBADFD;
	पूर्ण
	snd_pcm_stream_unlock_irq(substream);
	वापस result;
पूर्ण

/*
 * reset ioctl
 */
/* reset callbacks:  state argument ignored */
अटल पूर्णांक snd_pcm_pre_reset(काष्ठा snd_pcm_substream *substream,
			     snd_pcm_state_t state)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	चयन (runसमय->status->state) अणु
	हाल SNDRV_PCM_STATE_RUNNING:
	हाल SNDRV_PCM_STATE_PREPARED:
	हाल SNDRV_PCM_STATE_PAUSED:
	हाल SNDRV_PCM_STATE_SUSPENDED:
		वापस 0;
	शेष:
		वापस -EBADFD;
	पूर्ण
पूर्ण

अटल पूर्णांक snd_pcm_करो_reset(काष्ठा snd_pcm_substream *substream,
			    snd_pcm_state_t state)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	पूर्णांक err = snd_pcm_ops_ioctl(substream, SNDRV_PCM_IOCTL1_RESET, शून्य);
	अगर (err < 0)
		वापस err;
	runसमय->hw_ptr_base = 0;
	runसमय->hw_ptr_पूर्णांकerrupt = runसमय->status->hw_ptr -
		runसमय->status->hw_ptr % runसमय->period_size;
	runसमय->silence_start = runसमय->status->hw_ptr;
	runसमय->silence_filled = 0;
	वापस 0;
पूर्ण

अटल व्योम snd_pcm_post_reset(काष्ठा snd_pcm_substream *substream,
			       snd_pcm_state_t state)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	runसमय->control->appl_ptr = runसमय->status->hw_ptr;
	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK &&
	    runसमय->silence_size > 0)
		snd_pcm_playback_silence(substream, अच_दीर्घ_उच्च);
पूर्ण

अटल स्थिर काष्ठा action_ops snd_pcm_action_reset = अणु
	.pre_action = snd_pcm_pre_reset,
	.करो_action = snd_pcm_करो_reset,
	.post_action = snd_pcm_post_reset
पूर्ण;

अटल पूर्णांक snd_pcm_reset(काष्ठा snd_pcm_substream *substream)
अणु
	वापस snd_pcm_action_nonatomic(&snd_pcm_action_reset, substream,
					ACTION_ARG_IGNORE);
पूर्ण

/*
 * prepare ioctl
 */
/* pass f_flags as state argument */
अटल पूर्णांक snd_pcm_pre_prepare(काष्ठा snd_pcm_substream *substream,
			       snd_pcm_state_t state)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	पूर्णांक f_flags = (__क्रमce पूर्णांक)state;

	अगर (runसमय->status->state == SNDRV_PCM_STATE_OPEN ||
	    runसमय->status->state == SNDRV_PCM_STATE_DISCONNECTED)
		वापस -EBADFD;
	अगर (snd_pcm_running(substream))
		वापस -EBUSY;
	substream->f_flags = f_flags;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_pcm_करो_prepare(काष्ठा snd_pcm_substream *substream,
			      snd_pcm_state_t state)
अणु
	पूर्णांक err;
	snd_pcm_sync_stop(substream, true);
	err = substream->ops->prepare(substream);
	अगर (err < 0)
		वापस err;
	वापस snd_pcm_करो_reset(substream, state);
पूर्ण

अटल व्योम snd_pcm_post_prepare(काष्ठा snd_pcm_substream *substream,
				 snd_pcm_state_t state)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	runसमय->control->appl_ptr = runसमय->status->hw_ptr;
	snd_pcm_set_state(substream, SNDRV_PCM_STATE_PREPARED);
पूर्ण

अटल स्थिर काष्ठा action_ops snd_pcm_action_prepare = अणु
	.pre_action = snd_pcm_pre_prepare,
	.करो_action = snd_pcm_करो_prepare,
	.post_action = snd_pcm_post_prepare
पूर्ण;

/**
 * snd_pcm_prepare - prepare the PCM substream to be triggerable
 * @substream: the PCM substream instance
 * @file: file to refer f_flags
 *
 * Return: Zero अगर successful, or a negative error code.
 */
अटल पूर्णांक snd_pcm_prepare(काष्ठा snd_pcm_substream *substream,
			   काष्ठा file *file)
अणु
	पूर्णांक f_flags;

	अगर (file)
		f_flags = file->f_flags;
	अन्यथा
		f_flags = substream->f_flags;

	snd_pcm_stream_lock_irq(substream);
	चयन (substream->runसमय->status->state) अणु
	हाल SNDRV_PCM_STATE_PAUSED:
		snd_pcm_छोड़ो(substream, false);
		fallthrough;
	हाल SNDRV_PCM_STATE_SUSPENDED:
		snd_pcm_stop(substream, SNDRV_PCM_STATE_SETUP);
		अवरोध;
	पूर्ण
	snd_pcm_stream_unlock_irq(substream);

	वापस snd_pcm_action_nonatomic(&snd_pcm_action_prepare,
					substream,
					(__क्रमce snd_pcm_state_t)f_flags);
पूर्ण

/*
 * drain ioctl
 */

/* drain init callbacks: state argument ignored */
अटल पूर्णांक snd_pcm_pre_drain_init(काष्ठा snd_pcm_substream *substream,
				  snd_pcm_state_t state)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	चयन (runसमय->status->state) अणु
	हाल SNDRV_PCM_STATE_OPEN:
	हाल SNDRV_PCM_STATE_DISCONNECTED:
	हाल SNDRV_PCM_STATE_SUSPENDED:
		वापस -EBADFD;
	पूर्ण
	runसमय->trigger_master = substream;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_pcm_करो_drain_init(काष्ठा snd_pcm_substream *substream,
				 snd_pcm_state_t state)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
		चयन (runसमय->status->state) अणु
		हाल SNDRV_PCM_STATE_PREPARED:
			/* start playback stream अगर possible */
			अगर (! snd_pcm_playback_empty(substream)) अणु
				snd_pcm_करो_start(substream, SNDRV_PCM_STATE_DRAINING);
				snd_pcm_post_start(substream, SNDRV_PCM_STATE_DRAINING);
			पूर्ण अन्यथा अणु
				runसमय->status->state = SNDRV_PCM_STATE_SETUP;
			पूर्ण
			अवरोध;
		हाल SNDRV_PCM_STATE_RUNNING:
			runसमय->status->state = SNDRV_PCM_STATE_DRAINING;
			अवरोध;
		हाल SNDRV_PCM_STATE_XRUN:
			runसमय->status->state = SNDRV_PCM_STATE_SETUP;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* stop running stream */
		अगर (runसमय->status->state == SNDRV_PCM_STATE_RUNNING) अणु
			snd_pcm_state_t new_state;

			new_state = snd_pcm_capture_avail(runसमय) > 0 ?
				SNDRV_PCM_STATE_DRAINING : SNDRV_PCM_STATE_SETUP;
			snd_pcm_करो_stop(substream, new_state);
			snd_pcm_post_stop(substream, new_state);
		पूर्ण
	पूर्ण

	अगर (runसमय->status->state == SNDRV_PCM_STATE_DRAINING &&
	    runसमय->trigger_master == substream &&
	    (runसमय->hw.info & SNDRV_PCM_INFO_DRAIN_TRIGGER))
		वापस substream->ops->trigger(substream,
					       SNDRV_PCM_TRIGGER_DRAIN);

	वापस 0;
पूर्ण

अटल व्योम snd_pcm_post_drain_init(काष्ठा snd_pcm_substream *substream,
				    snd_pcm_state_t state)
अणु
पूर्ण

अटल स्थिर काष्ठा action_ops snd_pcm_action_drain_init = अणु
	.pre_action = snd_pcm_pre_drain_init,
	.करो_action = snd_pcm_करो_drain_init,
	.post_action = snd_pcm_post_drain_init
पूर्ण;

/*
 * Drain the stream(s).
 * When the substream is linked, sync until the draining of all playback streams
 * is finished.
 * After this call, all streams are supposed to be either SETUP or DRAINING
 * (capture only) state.
 */
अटल पूर्णांक snd_pcm_drain(काष्ठा snd_pcm_substream *substream,
			 काष्ठा file *file)
अणु
	काष्ठा snd_card *card;
	काष्ठा snd_pcm_runसमय *runसमय;
	काष्ठा snd_pcm_substream *s;
	काष्ठा snd_pcm_group *group;
	रुको_queue_entry_t रुको;
	पूर्णांक result = 0;
	पूर्णांक nonblock = 0;

	card = substream->pcm->card;
	runसमय = substream->runसमय;

	अगर (runसमय->status->state == SNDRV_PCM_STATE_OPEN)
		वापस -EBADFD;

	अगर (file) अणु
		अगर (file->f_flags & O_NONBLOCK)
			nonblock = 1;
	पूर्ण अन्यथा अगर (substream->f_flags & O_NONBLOCK)
		nonblock = 1;

	snd_pcm_stream_lock_irq(substream);
	/* resume छोड़ो */
	अगर (runसमय->status->state == SNDRV_PCM_STATE_PAUSED)
		snd_pcm_छोड़ो(substream, false);

	/* pre-start/stop - all running streams are changed to DRAINING state */
	result = snd_pcm_action(&snd_pcm_action_drain_init, substream,
				ACTION_ARG_IGNORE);
	अगर (result < 0)
		जाओ unlock;
	/* in non-blocking, we करोn't रुको in ioctl but let caller poll */
	अगर (nonblock) अणु
		result = -EAGAIN;
		जाओ unlock;
	पूर्ण

	क्रम (;;) अणु
		दीर्घ tout;
		काष्ठा snd_pcm_runसमय *to_check;
		अगर (संकेत_pending(current)) अणु
			result = -ERESTARTSYS;
			अवरोध;
		पूर्ण
		/* find a substream to drain */
		to_check = शून्य;
		group = snd_pcm_stream_group_ref(substream);
		snd_pcm_group_क्रम_each_entry(s, substream) अणु
			अगर (s->stream != SNDRV_PCM_STREAM_PLAYBACK)
				जारी;
			runसमय = s->runसमय;
			अगर (runसमय->status->state == SNDRV_PCM_STATE_DRAINING) अणु
				to_check = runसमय;
				अवरोध;
			पूर्ण
		पूर्ण
		snd_pcm_group_unref(group, substream);
		अगर (!to_check)
			अवरोध; /* all drained */
		init_रुकोqueue_entry(&रुको, current);
		set_current_state(TASK_INTERRUPTIBLE);
		add_रुको_queue(&to_check->sleep, &रुको);
		snd_pcm_stream_unlock_irq(substream);
		अगर (runसमय->no_period_wakeup)
			tout = MAX_SCHEDULE_TIMEOUT;
		अन्यथा अणु
			tout = 10;
			अगर (runसमय->rate) अणु
				दीर्घ t = runसमय->period_size * 2 / runसमय->rate;
				tout = max(t, tout);
			पूर्ण
			tout = msecs_to_jअगरfies(tout * 1000);
		पूर्ण
		tout = schedule_समयout(tout);

		snd_pcm_stream_lock_irq(substream);
		group = snd_pcm_stream_group_ref(substream);
		snd_pcm_group_क्रम_each_entry(s, substream) अणु
			अगर (s->runसमय == to_check) अणु
				हटाओ_रुको_queue(&to_check->sleep, &रुको);
				अवरोध;
			पूर्ण
		पूर्ण
		snd_pcm_group_unref(group, substream);

		अगर (card->shutकरोwn) अणु
			result = -ENODEV;
			अवरोध;
		पूर्ण
		अगर (tout == 0) अणु
			अगर (substream->runसमय->status->state == SNDRV_PCM_STATE_SUSPENDED)
				result = -ESTRPIPE;
			अन्यथा अणु
				dev_dbg(substream->pcm->card->dev,
					"playback drain error (DMA or IRQ trouble?)\n");
				snd_pcm_stop(substream, SNDRV_PCM_STATE_SETUP);
				result = -EIO;
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण

 unlock:
	snd_pcm_stream_unlock_irq(substream);

	वापस result;
पूर्ण

/*
 * drop ioctl
 *
 * Immediately put all linked substreams पूर्णांकo SETUP state.
 */
अटल पूर्णांक snd_pcm_drop(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय;
	पूर्णांक result = 0;
	
	अगर (PCM_RUNTIME_CHECK(substream))
		वापस -ENXIO;
	runसमय = substream->runसमय;

	अगर (runसमय->status->state == SNDRV_PCM_STATE_OPEN ||
	    runसमय->status->state == SNDRV_PCM_STATE_DISCONNECTED)
		वापस -EBADFD;

	snd_pcm_stream_lock_irq(substream);
	/* resume छोड़ो */
	अगर (runसमय->status->state == SNDRV_PCM_STATE_PAUSED)
		snd_pcm_छोड़ो(substream, false);

	snd_pcm_stop(substream, SNDRV_PCM_STATE_SETUP);
	/* runसमय->control->appl_ptr = runसमय->status->hw_ptr; */
	snd_pcm_stream_unlock_irq(substream);

	वापस result;
पूर्ण


अटल bool is_pcm_file(काष्ठा file *file)
अणु
	काष्ठा inode *inode = file_inode(file);
	काष्ठा snd_pcm *pcm;
	अचिन्हित पूर्णांक minor;

	अगर (!S_ISCHR(inode->i_mode) || imajor(inode) != snd_major)
		वापस false;
	minor = iminor(inode);
	pcm = snd_lookup_minor_data(minor, SNDRV_DEVICE_TYPE_PCM_PLAYBACK);
	अगर (!pcm)
		pcm = snd_lookup_minor_data(minor, SNDRV_DEVICE_TYPE_PCM_CAPTURE);
	अगर (!pcm)
		वापस false;
	snd_card_unref(pcm->card);
	वापस true;
पूर्ण

/*
 * PCM link handling
 */
अटल पूर्णांक snd_pcm_link(काष्ठा snd_pcm_substream *substream, पूर्णांक fd)
अणु
	पूर्णांक res = 0;
	काष्ठा snd_pcm_file *pcm_file;
	काष्ठा snd_pcm_substream *substream1;
	काष्ठा snd_pcm_group *group, *target_group;
	bool nonatomic = substream->pcm->nonatomic;
	काष्ठा fd f = fdget(fd);

	अगर (!f.file)
		वापस -EBADFD;
	अगर (!is_pcm_file(f.file)) अणु
		res = -EBADFD;
		जाओ _badf;
	पूर्ण
	pcm_file = f.file->निजी_data;
	substream1 = pcm_file->substream;

	अगर (substream == substream1) अणु
		res = -EINVAL;
		जाओ _badf;
	पूर्ण

	group = kzalloc(माप(*group), GFP_KERNEL);
	अगर (!group) अणु
		res = -ENOMEM;
		जाओ _nolock;
	पूर्ण
	snd_pcm_group_init(group);

	करोwn_ग_लिखो(&snd_pcm_link_rwsem);
	अगर (substream->runसमय->status->state == SNDRV_PCM_STATE_OPEN ||
	    substream->runसमय->status->state != substream1->runसमय->status->state ||
	    substream->pcm->nonatomic != substream1->pcm->nonatomic) अणु
		res = -EBADFD;
		जाओ _end;
	पूर्ण
	अगर (snd_pcm_stream_linked(substream1)) अणु
		res = -EALREADY;
		जाओ _end;
	पूर्ण

	snd_pcm_stream_lock_irq(substream);
	अगर (!snd_pcm_stream_linked(substream)) अणु
		snd_pcm_group_assign(substream, group);
		group = शून्य; /* asचिन्हित, करोn't मुक्त this one below */
	पूर्ण
	target_group = substream->group;
	snd_pcm_stream_unlock_irq(substream);

	snd_pcm_group_lock_irq(target_group, nonatomic);
	snd_pcm_stream_lock_nested(substream1);
	snd_pcm_group_assign(substream1, target_group);
	refcount_inc(&target_group->refs);
	snd_pcm_stream_unlock(substream1);
	snd_pcm_group_unlock_irq(target_group, nonatomic);
 _end:
	up_ग_लिखो(&snd_pcm_link_rwsem);
 _nolock:
	kमुक्त(group);
 _badf:
	fdput(f);
	वापस res;
पूर्ण

अटल व्योम relink_to_local(काष्ठा snd_pcm_substream *substream)
अणु
	snd_pcm_stream_lock_nested(substream);
	snd_pcm_group_assign(substream, &substream->self_group);
	snd_pcm_stream_unlock(substream);
पूर्ण

अटल पूर्णांक snd_pcm_unlink(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_group *group;
	bool nonatomic = substream->pcm->nonatomic;
	bool करो_मुक्त = false;
	पूर्णांक res = 0;

	करोwn_ग_लिखो(&snd_pcm_link_rwsem);

	अगर (!snd_pcm_stream_linked(substream)) अणु
		res = -EALREADY;
		जाओ _end;
	पूर्ण

	group = substream->group;
	snd_pcm_group_lock_irq(group, nonatomic);

	relink_to_local(substream);
	refcount_dec(&group->refs);

	/* detach the last stream, too */
	अगर (list_is_singular(&group->substreams)) अणु
		relink_to_local(list_first_entry(&group->substreams,
						 काष्ठा snd_pcm_substream,
						 link_list));
		करो_मुक्त = refcount_dec_and_test(&group->refs);
	पूर्ण

	snd_pcm_group_unlock_irq(group, nonatomic);
	अगर (करो_मुक्त)
		kमुक्त(group);

       _end:
	up_ग_लिखो(&snd_pcm_link_rwsem);
	वापस res;
पूर्ण

/*
 * hw configurator
 */
अटल पूर्णांक snd_pcm_hw_rule_mul(काष्ठा snd_pcm_hw_params *params,
			       काष्ठा snd_pcm_hw_rule *rule)
अणु
	काष्ठा snd_पूर्णांकerval t;
	snd_पूर्णांकerval_mul(hw_param_पूर्णांकerval_c(params, rule->deps[0]),
		     hw_param_पूर्णांकerval_c(params, rule->deps[1]), &t);
	वापस snd_पूर्णांकerval_refine(hw_param_पूर्णांकerval(params, rule->var), &t);
पूर्ण

अटल पूर्णांक snd_pcm_hw_rule_भाग(काष्ठा snd_pcm_hw_params *params,
			       काष्ठा snd_pcm_hw_rule *rule)
अणु
	काष्ठा snd_पूर्णांकerval t;
	snd_पूर्णांकerval_भाग(hw_param_पूर्णांकerval_c(params, rule->deps[0]),
		     hw_param_पूर्णांकerval_c(params, rule->deps[1]), &t);
	वापस snd_पूर्णांकerval_refine(hw_param_पूर्णांकerval(params, rule->var), &t);
पूर्ण

अटल पूर्णांक snd_pcm_hw_rule_muद_भागk(काष्ठा snd_pcm_hw_params *params,
				   काष्ठा snd_pcm_hw_rule *rule)
अणु
	काष्ठा snd_पूर्णांकerval t;
	snd_पूर्णांकerval_muद_भागk(hw_param_पूर्णांकerval_c(params, rule->deps[0]),
			 hw_param_पूर्णांकerval_c(params, rule->deps[1]),
			 (अचिन्हित दीर्घ) rule->निजी, &t);
	वापस snd_पूर्णांकerval_refine(hw_param_पूर्णांकerval(params, rule->var), &t);
पूर्ण

अटल पूर्णांक snd_pcm_hw_rule_mulkभाग(काष्ठा snd_pcm_hw_params *params,
				   काष्ठा snd_pcm_hw_rule *rule)
अणु
	काष्ठा snd_पूर्णांकerval t;
	snd_पूर्णांकerval_mulkभाग(hw_param_पूर्णांकerval_c(params, rule->deps[0]),
			 (अचिन्हित दीर्घ) rule->निजी,
			 hw_param_पूर्णांकerval_c(params, rule->deps[1]), &t);
	वापस snd_पूर्णांकerval_refine(hw_param_पूर्णांकerval(params, rule->var), &t);
पूर्ण

अटल पूर्णांक snd_pcm_hw_rule_क्रमmat(काष्ठा snd_pcm_hw_params *params,
				  काष्ठा snd_pcm_hw_rule *rule)
अणु
	snd_pcm_क्रमmat_t k;
	स्थिर काष्ठा snd_पूर्णांकerval *i =
				hw_param_पूर्णांकerval_c(params, rule->deps[0]);
	काष्ठा snd_mask m;
	काष्ठा snd_mask *mask = hw_param_mask(params, SNDRV_PCM_HW_PARAM_FORMAT);
	snd_mask_any(&m);
	pcm_क्रम_each_क्रमmat(k) अणु
		पूर्णांक bits;
		अगर (!snd_mask_test_क्रमmat(mask, k))
			जारी;
		bits = snd_pcm_क्रमmat_physical_width(k);
		अगर (bits <= 0)
			जारी; /* ignore invalid क्रमmats */
		अगर ((अचिन्हित)bits < i->min || (अचिन्हित)bits > i->max)
			snd_mask_reset(&m, (__क्रमce अचिन्हित)k);
	पूर्ण
	वापस snd_mask_refine(mask, &m);
पूर्ण

अटल पूर्णांक snd_pcm_hw_rule_sample_bits(काष्ठा snd_pcm_hw_params *params,
				       काष्ठा snd_pcm_hw_rule *rule)
अणु
	काष्ठा snd_पूर्णांकerval t;
	snd_pcm_क्रमmat_t k;

	t.min = अच_पूर्णांक_उच्च;
	t.max = 0;
	t.खोलोmin = 0;
	t.खोलोmax = 0;
	pcm_क्रम_each_क्रमmat(k) अणु
		पूर्णांक bits;
		अगर (!snd_mask_test_क्रमmat(hw_param_mask(params, SNDRV_PCM_HW_PARAM_FORMAT), k))
			जारी;
		bits = snd_pcm_क्रमmat_physical_width(k);
		अगर (bits <= 0)
			जारी; /* ignore invalid क्रमmats */
		अगर (t.min > (अचिन्हित)bits)
			t.min = bits;
		अगर (t.max < (अचिन्हित)bits)
			t.max = bits;
	पूर्ण
	t.पूर्णांकeger = 1;
	वापस snd_पूर्णांकerval_refine(hw_param_पूर्णांकerval(params, rule->var), &t);
पूर्ण

#अगर SNDRV_PCM_RATE_5512 != 1 << 0 || SNDRV_PCM_RATE_192000 != 1 << 12
#त्रुटि "Change this table"
#पूर्ण_अगर

अटल स्थिर अचिन्हित पूर्णांक rates[] = अणु
	5512, 8000, 11025, 16000, 22050, 32000, 44100,
	48000, 64000, 88200, 96000, 176400, 192000, 352800, 384000
पूर्ण;

स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list snd_pcm_known_rates = अणु
	.count = ARRAY_SIZE(rates),
	.list = rates,
पूर्ण;

अटल पूर्णांक snd_pcm_hw_rule_rate(काष्ठा snd_pcm_hw_params *params,
				काष्ठा snd_pcm_hw_rule *rule)
अणु
	काष्ठा snd_pcm_hardware *hw = rule->निजी;
	वापस snd_पूर्णांकerval_list(hw_param_पूर्णांकerval(params, rule->var),
				 snd_pcm_known_rates.count,
				 snd_pcm_known_rates.list, hw->rates);
पूर्ण		

अटल पूर्णांक snd_pcm_hw_rule_buffer_bytes_max(काष्ठा snd_pcm_hw_params *params,
					    काष्ठा snd_pcm_hw_rule *rule)
अणु
	काष्ठा snd_पूर्णांकerval t;
	काष्ठा snd_pcm_substream *substream = rule->निजी;
	t.min = 0;
	t.max = substream->buffer_bytes_max;
	t.खोलोmin = 0;
	t.खोलोmax = 0;
	t.पूर्णांकeger = 1;
	वापस snd_पूर्णांकerval_refine(hw_param_पूर्णांकerval(params, rule->var), &t);
पूर्ण		

अटल पूर्णांक snd_pcm_hw_स्थिरraपूर्णांकs_init(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_pcm_hw_स्थिरraपूर्णांकs *स्थिरrs = &runसमय->hw_स्थिरraपूर्णांकs;
	पूर्णांक k, err;

	क्रम (k = SNDRV_PCM_HW_PARAM_FIRST_MASK; k <= SNDRV_PCM_HW_PARAM_LAST_MASK; k++) अणु
		snd_mask_any(स्थिरrs_mask(स्थिरrs, k));
	पूर्ण

	क्रम (k = SNDRV_PCM_HW_PARAM_FIRST_INTERVAL; k <= SNDRV_PCM_HW_PARAM_LAST_INTERVAL; k++) अणु
		snd_पूर्णांकerval_any(स्थिरrs_पूर्णांकerval(स्थिरrs, k));
	पूर्ण

	snd_पूर्णांकerval_setपूर्णांकeger(स्थिरrs_पूर्णांकerval(स्थिरrs, SNDRV_PCM_HW_PARAM_CHANNELS));
	snd_पूर्णांकerval_setपूर्णांकeger(स्थिरrs_पूर्णांकerval(स्थिरrs, SNDRV_PCM_HW_PARAM_BUFFER_SIZE));
	snd_पूर्णांकerval_setपूर्णांकeger(स्थिरrs_पूर्णांकerval(स्थिरrs, SNDRV_PCM_HW_PARAM_BUFFER_BYTES));
	snd_पूर्णांकerval_setपूर्णांकeger(स्थिरrs_पूर्णांकerval(स्थिरrs, SNDRV_PCM_HW_PARAM_SAMPLE_BITS));
	snd_पूर्णांकerval_setपूर्णांकeger(स्थिरrs_पूर्णांकerval(स्थिरrs, SNDRV_PCM_HW_PARAM_FRAME_BITS));

	err = snd_pcm_hw_rule_add(runसमय, 0, SNDRV_PCM_HW_PARAM_FORMAT,
				   snd_pcm_hw_rule_क्रमmat, शून्य,
				   SNDRV_PCM_HW_PARAM_SAMPLE_BITS, -1);
	अगर (err < 0)
		वापस err;
	err = snd_pcm_hw_rule_add(runसमय, 0, SNDRV_PCM_HW_PARAM_SAMPLE_BITS, 
				  snd_pcm_hw_rule_sample_bits, शून्य,
				  SNDRV_PCM_HW_PARAM_FORMAT, 
				  SNDRV_PCM_HW_PARAM_SAMPLE_BITS, -1);
	अगर (err < 0)
		वापस err;
	err = snd_pcm_hw_rule_add(runसमय, 0, SNDRV_PCM_HW_PARAM_SAMPLE_BITS, 
				  snd_pcm_hw_rule_भाग, शून्य,
				  SNDRV_PCM_HW_PARAM_FRAME_BITS, SNDRV_PCM_HW_PARAM_CHANNELS, -1);
	अगर (err < 0)
		वापस err;
	err = snd_pcm_hw_rule_add(runसमय, 0, SNDRV_PCM_HW_PARAM_FRAME_BITS, 
				  snd_pcm_hw_rule_mul, शून्य,
				  SNDRV_PCM_HW_PARAM_SAMPLE_BITS, SNDRV_PCM_HW_PARAM_CHANNELS, -1);
	अगर (err < 0)
		वापस err;
	err = snd_pcm_hw_rule_add(runसमय, 0, SNDRV_PCM_HW_PARAM_FRAME_BITS, 
				  snd_pcm_hw_rule_mulkभाग, (व्योम*) 8,
				  SNDRV_PCM_HW_PARAM_PERIOD_BYTES, SNDRV_PCM_HW_PARAM_PERIOD_SIZE, -1);
	अगर (err < 0)
		वापस err;
	err = snd_pcm_hw_rule_add(runसमय, 0, SNDRV_PCM_HW_PARAM_FRAME_BITS, 
				  snd_pcm_hw_rule_mulkभाग, (व्योम*) 8,
				  SNDRV_PCM_HW_PARAM_BUFFER_BYTES, SNDRV_PCM_HW_PARAM_BUFFER_SIZE, -1);
	अगर (err < 0)
		वापस err;
	err = snd_pcm_hw_rule_add(runसमय, 0, SNDRV_PCM_HW_PARAM_CHANNELS, 
				  snd_pcm_hw_rule_भाग, शून्य,
				  SNDRV_PCM_HW_PARAM_FRAME_BITS, SNDRV_PCM_HW_PARAM_SAMPLE_BITS, -1);
	अगर (err < 0)
		वापस err;
	err = snd_pcm_hw_rule_add(runसमय, 0, SNDRV_PCM_HW_PARAM_RATE, 
				  snd_pcm_hw_rule_mulkभाग, (व्योम*) 1000000,
				  SNDRV_PCM_HW_PARAM_PERIOD_SIZE, SNDRV_PCM_HW_PARAM_PERIOD_TIME, -1);
	अगर (err < 0)
		वापस err;
	err = snd_pcm_hw_rule_add(runसमय, 0, SNDRV_PCM_HW_PARAM_RATE, 
				  snd_pcm_hw_rule_mulkभाग, (व्योम*) 1000000,
				  SNDRV_PCM_HW_PARAM_BUFFER_SIZE, SNDRV_PCM_HW_PARAM_BUFFER_TIME, -1);
	अगर (err < 0)
		वापस err;
	err = snd_pcm_hw_rule_add(runसमय, 0, SNDRV_PCM_HW_PARAM_PERIODS, 
				  snd_pcm_hw_rule_भाग, शून्य,
				  SNDRV_PCM_HW_PARAM_BUFFER_SIZE, SNDRV_PCM_HW_PARAM_PERIOD_SIZE, -1);
	अगर (err < 0)
		वापस err;
	err = snd_pcm_hw_rule_add(runसमय, 0, SNDRV_PCM_HW_PARAM_PERIOD_SIZE, 
				  snd_pcm_hw_rule_भाग, शून्य,
				  SNDRV_PCM_HW_PARAM_BUFFER_SIZE, SNDRV_PCM_HW_PARAM_PERIODS, -1);
	अगर (err < 0)
		वापस err;
	err = snd_pcm_hw_rule_add(runसमय, 0, SNDRV_PCM_HW_PARAM_PERIOD_SIZE, 
				  snd_pcm_hw_rule_mulkभाग, (व्योम*) 8,
				  SNDRV_PCM_HW_PARAM_PERIOD_BYTES, SNDRV_PCM_HW_PARAM_FRAME_BITS, -1);
	अगर (err < 0)
		वापस err;
	err = snd_pcm_hw_rule_add(runसमय, 0, SNDRV_PCM_HW_PARAM_PERIOD_SIZE, 
				  snd_pcm_hw_rule_muद_भागk, (व्योम*) 1000000,
				  SNDRV_PCM_HW_PARAM_PERIOD_TIME, SNDRV_PCM_HW_PARAM_RATE, -1);
	अगर (err < 0)
		वापस err;
	err = snd_pcm_hw_rule_add(runसमय, 0, SNDRV_PCM_HW_PARAM_BUFFER_SIZE, 
				  snd_pcm_hw_rule_mul, शून्य,
				  SNDRV_PCM_HW_PARAM_PERIOD_SIZE, SNDRV_PCM_HW_PARAM_PERIODS, -1);
	अगर (err < 0)
		वापस err;
	err = snd_pcm_hw_rule_add(runसमय, 0, SNDRV_PCM_HW_PARAM_BUFFER_SIZE, 
				  snd_pcm_hw_rule_mulkभाग, (व्योम*) 8,
				  SNDRV_PCM_HW_PARAM_BUFFER_BYTES, SNDRV_PCM_HW_PARAM_FRAME_BITS, -1);
	अगर (err < 0)
		वापस err;
	err = snd_pcm_hw_rule_add(runसमय, 0, SNDRV_PCM_HW_PARAM_BUFFER_SIZE, 
				  snd_pcm_hw_rule_muद_भागk, (व्योम*) 1000000,
				  SNDRV_PCM_HW_PARAM_BUFFER_TIME, SNDRV_PCM_HW_PARAM_RATE, -1);
	अगर (err < 0)
		वापस err;
	err = snd_pcm_hw_rule_add(runसमय, 0, SNDRV_PCM_HW_PARAM_PERIOD_BYTES, 
				  snd_pcm_hw_rule_muद_भागk, (व्योम*) 8,
				  SNDRV_PCM_HW_PARAM_PERIOD_SIZE, SNDRV_PCM_HW_PARAM_FRAME_BITS, -1);
	अगर (err < 0)
		वापस err;
	err = snd_pcm_hw_rule_add(runसमय, 0, SNDRV_PCM_HW_PARAM_BUFFER_BYTES, 
				  snd_pcm_hw_rule_muद_भागk, (व्योम*) 8,
				  SNDRV_PCM_HW_PARAM_BUFFER_SIZE, SNDRV_PCM_HW_PARAM_FRAME_BITS, -1);
	अगर (err < 0)
		वापस err;
	err = snd_pcm_hw_rule_add(runसमय, 0, SNDRV_PCM_HW_PARAM_PERIOD_TIME, 
				  snd_pcm_hw_rule_mulkभाग, (व्योम*) 1000000,
				  SNDRV_PCM_HW_PARAM_PERIOD_SIZE, SNDRV_PCM_HW_PARAM_RATE, -1);
	अगर (err < 0)
		वापस err;
	err = snd_pcm_hw_rule_add(runसमय, 0, SNDRV_PCM_HW_PARAM_BUFFER_TIME, 
				  snd_pcm_hw_rule_mulkभाग, (व्योम*) 1000000,
				  SNDRV_PCM_HW_PARAM_BUFFER_SIZE, SNDRV_PCM_HW_PARAM_RATE, -1);
	अगर (err < 0)
		वापस err;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_pcm_hw_स्थिरraपूर्णांकs_complete(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_pcm_hardware *hw = &runसमय->hw;
	पूर्णांक err;
	अचिन्हित पूर्णांक mask = 0;

        अगर (hw->info & SNDRV_PCM_INFO_INTERLEAVED)
		mask |= PARAM_MASK_BIT(SNDRV_PCM_ACCESS_RW_INTERLEAVED);
        अगर (hw->info & SNDRV_PCM_INFO_NONINTERLEAVED)
		mask |= PARAM_MASK_BIT(SNDRV_PCM_ACCESS_RW_NONINTERLEAVED);
	अगर (hw_support_mmap(substream)) अणु
		अगर (hw->info & SNDRV_PCM_INFO_INTERLEAVED)
			mask |= PARAM_MASK_BIT(SNDRV_PCM_ACCESS_MMAP_INTERLEAVED);
		अगर (hw->info & SNDRV_PCM_INFO_NONINTERLEAVED)
			mask |= PARAM_MASK_BIT(SNDRV_PCM_ACCESS_MMAP_NONINTERLEAVED);
		अगर (hw->info & SNDRV_PCM_INFO_COMPLEX)
			mask |= PARAM_MASK_BIT(SNDRV_PCM_ACCESS_MMAP_COMPLEX);
	पूर्ण
	err = snd_pcm_hw_स्थिरraपूर्णांक_mask(runसमय, SNDRV_PCM_HW_PARAM_ACCESS, mask);
	अगर (err < 0)
		वापस err;

	err = snd_pcm_hw_स्थिरraपूर्णांक_mask64(runसमय, SNDRV_PCM_HW_PARAM_FORMAT, hw->क्रमmats);
	अगर (err < 0)
		वापस err;

	err = snd_pcm_hw_स्थिरraपूर्णांक_mask(runसमय, SNDRV_PCM_HW_PARAM_SUBFORMAT,
					 PARAM_MASK_BIT(SNDRV_PCM_SUBFORMAT_STD));
	अगर (err < 0)
		वापस err;

	err = snd_pcm_hw_स्थिरraपूर्णांक_minmax(runसमय, SNDRV_PCM_HW_PARAM_CHANNELS,
					   hw->channels_min, hw->channels_max);
	अगर (err < 0)
		वापस err;

	err = snd_pcm_hw_स्थिरraपूर्णांक_minmax(runसमय, SNDRV_PCM_HW_PARAM_RATE,
					   hw->rate_min, hw->rate_max);
	अगर (err < 0)
		वापस err;

	err = snd_pcm_hw_स्थिरraपूर्णांक_minmax(runसमय, SNDRV_PCM_HW_PARAM_PERIOD_BYTES,
					   hw->period_bytes_min, hw->period_bytes_max);
	अगर (err < 0)
		वापस err;

	err = snd_pcm_hw_स्थिरraपूर्णांक_minmax(runसमय, SNDRV_PCM_HW_PARAM_PERIODS,
					   hw->periods_min, hw->periods_max);
	अगर (err < 0)
		वापस err;

	err = snd_pcm_hw_स्थिरraपूर्णांक_minmax(runसमय, SNDRV_PCM_HW_PARAM_BUFFER_BYTES,
					   hw->period_bytes_min, hw->buffer_bytes_max);
	अगर (err < 0)
		वापस err;

	err = snd_pcm_hw_rule_add(runसमय, 0, SNDRV_PCM_HW_PARAM_BUFFER_BYTES, 
				  snd_pcm_hw_rule_buffer_bytes_max, substream,
				  SNDRV_PCM_HW_PARAM_BUFFER_BYTES, -1);
	अगर (err < 0)
		वापस err;

	/* FIXME: हटाओ */
	अगर (runसमय->dma_bytes) अणु
		err = snd_pcm_hw_स्थिरraपूर्णांक_minmax(runसमय, SNDRV_PCM_HW_PARAM_BUFFER_BYTES, 0, runसमय->dma_bytes);
		अगर (err < 0)
			वापस err;
	पूर्ण

	अगर (!(hw->rates & (SNDRV_PCM_RATE_KNOT | SNDRV_PCM_RATE_CONTINUOUS))) अणु
		err = snd_pcm_hw_rule_add(runसमय, 0, SNDRV_PCM_HW_PARAM_RATE, 
					  snd_pcm_hw_rule_rate, hw,
					  SNDRV_PCM_HW_PARAM_RATE, -1);
		अगर (err < 0)
			वापस err;
	पूर्ण

	/* FIXME: this beदीर्घ to lowlevel */
	snd_pcm_hw_स्थिरraपूर्णांक_पूर्णांकeger(runसमय, SNDRV_PCM_HW_PARAM_PERIOD_SIZE);

	वापस 0;
पूर्ण

अटल व्योम pcm_release_निजी(काष्ठा snd_pcm_substream *substream)
अणु
	अगर (snd_pcm_stream_linked(substream))
		snd_pcm_unlink(substream);
पूर्ण

व्योम snd_pcm_release_substream(काष्ठा snd_pcm_substream *substream)
अणु
	substream->ref_count--;
	अगर (substream->ref_count > 0)
		वापस;

	snd_pcm_drop(substream);
	अगर (substream->hw_खोलोed) अणु
		अगर (substream->runसमय->status->state != SNDRV_PCM_STATE_OPEN)
			करो_hw_मुक्त(substream);
		substream->ops->बंद(substream);
		substream->hw_खोलोed = 0;
	पूर्ण
	अगर (cpu_latency_qos_request_active(&substream->latency_pm_qos_req))
		cpu_latency_qos_हटाओ_request(&substream->latency_pm_qos_req);
	अगर (substream->pcm_release) अणु
		substream->pcm_release(substream);
		substream->pcm_release = शून्य;
	पूर्ण
	snd_pcm_detach_substream(substream);
पूर्ण
EXPORT_SYMBOL(snd_pcm_release_substream);

पूर्णांक snd_pcm_खोलो_substream(काष्ठा snd_pcm *pcm, पूर्णांक stream,
			   काष्ठा file *file,
			   काष्ठा snd_pcm_substream **rsubstream)
अणु
	काष्ठा snd_pcm_substream *substream;
	पूर्णांक err;

	err = snd_pcm_attach_substream(pcm, stream, file, &substream);
	अगर (err < 0)
		वापस err;
	अगर (substream->ref_count > 1) अणु
		*rsubstream = substream;
		वापस 0;
	पूर्ण

	err = snd_pcm_hw_स्थिरraपूर्णांकs_init(substream);
	अगर (err < 0) अणु
		pcm_dbg(pcm, "snd_pcm_hw_constraints_init failed\n");
		जाओ error;
	पूर्ण

	अगर ((err = substream->ops->खोलो(substream)) < 0)
		जाओ error;

	substream->hw_खोलोed = 1;

	err = snd_pcm_hw_स्थिरraपूर्णांकs_complete(substream);
	अगर (err < 0) अणु
		pcm_dbg(pcm, "snd_pcm_hw_constraints_complete failed\n");
		जाओ error;
	पूर्ण

	*rsubstream = substream;
	वापस 0;

 error:
	snd_pcm_release_substream(substream);
	वापस err;
पूर्ण
EXPORT_SYMBOL(snd_pcm_खोलो_substream);

अटल पूर्णांक snd_pcm_खोलो_file(काष्ठा file *file,
			     काष्ठा snd_pcm *pcm,
			     पूर्णांक stream)
अणु
	काष्ठा snd_pcm_file *pcm_file;
	काष्ठा snd_pcm_substream *substream;
	पूर्णांक err;

	err = snd_pcm_खोलो_substream(pcm, stream, file, &substream);
	अगर (err < 0)
		वापस err;

	pcm_file = kzalloc(माप(*pcm_file), GFP_KERNEL);
	अगर (pcm_file == शून्य) अणु
		snd_pcm_release_substream(substream);
		वापस -ENOMEM;
	पूर्ण
	pcm_file->substream = substream;
	अगर (substream->ref_count == 1)
		substream->pcm_release = pcm_release_निजी;
	file->निजी_data = pcm_file;

	वापस 0;
पूर्ण

अटल पूर्णांक snd_pcm_playback_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा snd_pcm *pcm;
	पूर्णांक err = nonseekable_खोलो(inode, file);
	अगर (err < 0)
		वापस err;
	pcm = snd_lookup_minor_data(iminor(inode),
				    SNDRV_DEVICE_TYPE_PCM_PLAYBACK);
	err = snd_pcm_खोलो(file, pcm, SNDRV_PCM_STREAM_PLAYBACK);
	अगर (pcm)
		snd_card_unref(pcm->card);
	वापस err;
पूर्ण

अटल पूर्णांक snd_pcm_capture_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा snd_pcm *pcm;
	पूर्णांक err = nonseekable_खोलो(inode, file);
	अगर (err < 0)
		वापस err;
	pcm = snd_lookup_minor_data(iminor(inode),
				    SNDRV_DEVICE_TYPE_PCM_CAPTURE);
	err = snd_pcm_खोलो(file, pcm, SNDRV_PCM_STREAM_CAPTURE);
	अगर (pcm)
		snd_card_unref(pcm->card);
	वापस err;
पूर्ण

अटल पूर्णांक snd_pcm_खोलो(काष्ठा file *file, काष्ठा snd_pcm *pcm, पूर्णांक stream)
अणु
	पूर्णांक err;
	रुको_queue_entry_t रुको;

	अगर (pcm == शून्य) अणु
		err = -ENODEV;
		जाओ __error1;
	पूर्ण
	err = snd_card_file_add(pcm->card, file);
	अगर (err < 0)
		जाओ __error1;
	अगर (!try_module_get(pcm->card->module)) अणु
		err = -EFAULT;
		जाओ __error2;
	पूर्ण
	init_रुकोqueue_entry(&रुको, current);
	add_रुको_queue(&pcm->खोलो_रुको, &रुको);
	mutex_lock(&pcm->खोलो_mutex);
	जबतक (1) अणु
		err = snd_pcm_खोलो_file(file, pcm, stream);
		अगर (err >= 0)
			अवरोध;
		अगर (err == -EAGAIN) अणु
			अगर (file->f_flags & O_NONBLOCK) अणु
				err = -EBUSY;
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा
			अवरोध;
		set_current_state(TASK_INTERRUPTIBLE);
		mutex_unlock(&pcm->खोलो_mutex);
		schedule();
		mutex_lock(&pcm->खोलो_mutex);
		अगर (pcm->card->shutकरोwn) अणु
			err = -ENODEV;
			अवरोध;
		पूर्ण
		अगर (संकेत_pending(current)) अणु
			err = -ERESTARTSYS;
			अवरोध;
		पूर्ण
	पूर्ण
	हटाओ_रुको_queue(&pcm->खोलो_रुको, &रुको);
	mutex_unlock(&pcm->खोलो_mutex);
	अगर (err < 0)
		जाओ __error;
	वापस err;

      __error:
	module_put(pcm->card->module);
      __error2:
      	snd_card_file_हटाओ(pcm->card, file);
      __error1:
      	वापस err;
पूर्ण

अटल पूर्णांक snd_pcm_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा snd_pcm *pcm;
	काष्ठा snd_pcm_substream *substream;
	काष्ठा snd_pcm_file *pcm_file;

	pcm_file = file->निजी_data;
	substream = pcm_file->substream;
	अगर (snd_BUG_ON(!substream))
		वापस -ENXIO;
	pcm = substream->pcm;
	mutex_lock(&pcm->खोलो_mutex);
	snd_pcm_release_substream(substream);
	kमुक्त(pcm_file);
	mutex_unlock(&pcm->खोलो_mutex);
	wake_up(&pcm->खोलो_रुको);
	module_put(pcm->card->module);
	snd_card_file_हटाओ(pcm->card, file);
	वापस 0;
पूर्ण

/* check and update PCM state; वापस 0 or a negative error
 * call this inside PCM lock
 */
अटल पूर्णांक करो_pcm_hwsync(काष्ठा snd_pcm_substream *substream)
अणु
	चयन (substream->runसमय->status->state) अणु
	हाल SNDRV_PCM_STATE_DRAINING:
		अगर (substream->stream == SNDRV_PCM_STREAM_CAPTURE)
			वापस -EBADFD;
		fallthrough;
	हाल SNDRV_PCM_STATE_RUNNING:
		वापस snd_pcm_update_hw_ptr(substream);
	हाल SNDRV_PCM_STATE_PREPARED:
	हाल SNDRV_PCM_STATE_PAUSED:
		वापस 0;
	हाल SNDRV_PCM_STATE_SUSPENDED:
		वापस -ESTRPIPE;
	हाल SNDRV_PCM_STATE_XRUN:
		वापस -EPIPE;
	शेष:
		वापस -EBADFD;
	पूर्ण
पूर्ण

/* increase the appl_ptr; वापसs the processed frames or a negative error */
अटल snd_pcm_sframes_t क्रमward_appl_ptr(काष्ठा snd_pcm_substream *substream,
					  snd_pcm_uframes_t frames,
					   snd_pcm_sframes_t avail)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	snd_pcm_sframes_t appl_ptr;
	पूर्णांक ret;

	अगर (avail <= 0)
		वापस 0;
	अगर (frames > (snd_pcm_uframes_t)avail)
		frames = avail;
	appl_ptr = runसमय->control->appl_ptr + frames;
	अगर (appl_ptr >= (snd_pcm_sframes_t)runसमय->boundary)
		appl_ptr -= runसमय->boundary;
	ret = pcm_lib_apply_appl_ptr(substream, appl_ptr);
	वापस ret < 0 ? ret : frames;
पूर्ण

/* decrease the appl_ptr; वापसs the processed frames or zero क्रम error */
अटल snd_pcm_sframes_t शुरुआत_appl_ptr(काष्ठा snd_pcm_substream *substream,
					 snd_pcm_uframes_t frames,
					 snd_pcm_sframes_t avail)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	snd_pcm_sframes_t appl_ptr;
	पूर्णांक ret;

	अगर (avail <= 0)
		वापस 0;
	अगर (frames > (snd_pcm_uframes_t)avail)
		frames = avail;
	appl_ptr = runसमय->control->appl_ptr - frames;
	अगर (appl_ptr < 0)
		appl_ptr += runसमय->boundary;
	ret = pcm_lib_apply_appl_ptr(substream, appl_ptr);
	/* NOTE: we वापस zero क्रम errors because PulseAudio माला_लो depressed
	 * upon receiving an error from शुरुआत ioctl and stops processing
	 * any दीर्घer.  Returning zero means that no शुरुआत is करोne, so
	 * it's not असलolutely wrong to answer like that.
	 */
	वापस ret < 0 ? 0 : frames;
पूर्ण

अटल snd_pcm_sframes_t snd_pcm_शुरुआत(काष्ठा snd_pcm_substream *substream,
					snd_pcm_uframes_t frames)
अणु
	snd_pcm_sframes_t ret;

	अगर (frames == 0)
		वापस 0;

	snd_pcm_stream_lock_irq(substream);
	ret = करो_pcm_hwsync(substream);
	अगर (!ret)
		ret = शुरुआत_appl_ptr(substream, frames,
				      snd_pcm_hw_avail(substream));
	snd_pcm_stream_unlock_irq(substream);
	वापस ret;
पूर्ण

अटल snd_pcm_sframes_t snd_pcm_क्रमward(काष्ठा snd_pcm_substream *substream,
					 snd_pcm_uframes_t frames)
अणु
	snd_pcm_sframes_t ret;

	अगर (frames == 0)
		वापस 0;

	snd_pcm_stream_lock_irq(substream);
	ret = करो_pcm_hwsync(substream);
	अगर (!ret)
		ret = क्रमward_appl_ptr(substream, frames,
				       snd_pcm_avail(substream));
	snd_pcm_stream_unlock_irq(substream);
	वापस ret;
पूर्ण

अटल पूर्णांक snd_pcm_hwsync(काष्ठा snd_pcm_substream *substream)
अणु
	पूर्णांक err;

	snd_pcm_stream_lock_irq(substream);
	err = करो_pcm_hwsync(substream);
	snd_pcm_stream_unlock_irq(substream);
	वापस err;
पूर्ण
		
अटल पूर्णांक snd_pcm_delay(काष्ठा snd_pcm_substream *substream,
			 snd_pcm_sframes_t *delay)
अणु
	पूर्णांक err;
	snd_pcm_sframes_t n = 0;

	snd_pcm_stream_lock_irq(substream);
	err = करो_pcm_hwsync(substream);
	अगर (!err)
		n = snd_pcm_calc_delay(substream);
	snd_pcm_stream_unlock_irq(substream);
	अगर (!err)
		*delay = n;
	वापस err;
पूर्ण
		
अटल पूर्णांक snd_pcm_sync_ptr(काष्ठा snd_pcm_substream *substream,
			    काष्ठा snd_pcm_sync_ptr __user *_sync_ptr)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_pcm_sync_ptr sync_ptr;
	अस्थिर काष्ठा snd_pcm_mmap_status *status;
	अस्थिर काष्ठा snd_pcm_mmap_control *control;
	पूर्णांक err;

	स_रखो(&sync_ptr, 0, माप(sync_ptr));
	अगर (get_user(sync_ptr.flags, (अचिन्हित __user *)&(_sync_ptr->flags)))
		वापस -EFAULT;
	अगर (copy_from_user(&sync_ptr.c.control, &(_sync_ptr->c.control), माप(काष्ठा snd_pcm_mmap_control)))
		वापस -EFAULT;	
	status = runसमय->status;
	control = runसमय->control;
	अगर (sync_ptr.flags & SNDRV_PCM_SYNC_PTR_HWSYNC) अणु
		err = snd_pcm_hwsync(substream);
		अगर (err < 0)
			वापस err;
	पूर्ण
	snd_pcm_stream_lock_irq(substream);
	अगर (!(sync_ptr.flags & SNDRV_PCM_SYNC_PTR_APPL)) अणु
		err = pcm_lib_apply_appl_ptr(substream,
					     sync_ptr.c.control.appl_ptr);
		अगर (err < 0) अणु
			snd_pcm_stream_unlock_irq(substream);
			वापस err;
		पूर्ण
	पूर्ण अन्यथा अणु
		sync_ptr.c.control.appl_ptr = control->appl_ptr;
	पूर्ण
	अगर (!(sync_ptr.flags & SNDRV_PCM_SYNC_PTR_AVAIL_MIN))
		control->avail_min = sync_ptr.c.control.avail_min;
	अन्यथा
		sync_ptr.c.control.avail_min = control->avail_min;
	sync_ptr.s.status.state = status->state;
	sync_ptr.s.status.hw_ptr = status->hw_ptr;
	sync_ptr.s.status.tstamp = status->tstamp;
	sync_ptr.s.status.suspended_state = status->suspended_state;
	sync_ptr.s.status.audio_tstamp = status->audio_tstamp;
	snd_pcm_stream_unlock_irq(substream);
	अगर (copy_to_user(_sync_ptr, &sync_ptr, माप(sync_ptr)))
		वापस -EFAULT;
	वापस 0;
पूर्ण

काष्ठा snd_pcm_mmap_status32 अणु
	snd_pcm_state_t state;
	s32 pad1;
	u32 hw_ptr;
	s32 tstamp_sec;
	s32 tstamp_nsec;
	snd_pcm_state_t suspended_state;
	s32 audio_tstamp_sec;
	s32 audio_tstamp_nsec;
पूर्ण __attribute__((packed));

काष्ठा snd_pcm_mmap_control32 अणु
	u32 appl_ptr;
	u32 avail_min;
पूर्ण;

काष्ठा snd_pcm_sync_ptr32 अणु
	u32 flags;
	जोड़ अणु
		काष्ठा snd_pcm_mmap_status32 status;
		अचिन्हित अक्षर reserved[64];
	पूर्ण s;
	जोड़ अणु
		काष्ठा snd_pcm_mmap_control32 control;
		अचिन्हित अक्षर reserved[64];
	पूर्ण c;
पूर्ण __attribute__((packed));

/* recalcuate the boundary within 32bit */
अटल snd_pcm_uframes_t recalculate_boundary(काष्ठा snd_pcm_runसमय *runसमय)
अणु
	snd_pcm_uframes_t boundary;

	अगर (! runसमय->buffer_size)
		वापस 0;
	boundary = runसमय->buffer_size;
	जबतक (boundary * 2 <= 0x7fffffffUL - runसमय->buffer_size)
		boundary *= 2;
	वापस boundary;
पूर्ण

अटल पूर्णांक snd_pcm_ioctl_sync_ptr_compat(काष्ठा snd_pcm_substream *substream,
					 काष्ठा snd_pcm_sync_ptr32 __user *src)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	अस्थिर काष्ठा snd_pcm_mmap_status *status;
	अस्थिर काष्ठा snd_pcm_mmap_control *control;
	u32 sflags;
	काष्ठा snd_pcm_mmap_control scontrol;
	काष्ठा snd_pcm_mmap_status sstatus;
	snd_pcm_uframes_t boundary;
	पूर्णांक err;

	अगर (snd_BUG_ON(!runसमय))
		वापस -EINVAL;

	अगर (get_user(sflags, &src->flags) ||
	    get_user(scontrol.appl_ptr, &src->c.control.appl_ptr) ||
	    get_user(scontrol.avail_min, &src->c.control.avail_min))
		वापस -EFAULT;
	अगर (sflags & SNDRV_PCM_SYNC_PTR_HWSYNC) अणु
		err = snd_pcm_hwsync(substream);
		अगर (err < 0)
			वापस err;
	पूर्ण
	status = runसमय->status;
	control = runसमय->control;
	boundary = recalculate_boundary(runसमय);
	अगर (! boundary)
		boundary = 0x7fffffff;
	snd_pcm_stream_lock_irq(substream);
	/* FIXME: we should consider the boundary क्रम the sync from app */
	अगर (!(sflags & SNDRV_PCM_SYNC_PTR_APPL))
		control->appl_ptr = scontrol.appl_ptr;
	अन्यथा
		scontrol.appl_ptr = control->appl_ptr % boundary;
	अगर (!(sflags & SNDRV_PCM_SYNC_PTR_AVAIL_MIN))
		control->avail_min = scontrol.avail_min;
	अन्यथा
		scontrol.avail_min = control->avail_min;
	sstatus.state = status->state;
	sstatus.hw_ptr = status->hw_ptr % boundary;
	sstatus.tstamp = status->tstamp;
	sstatus.suspended_state = status->suspended_state;
	sstatus.audio_tstamp = status->audio_tstamp;
	snd_pcm_stream_unlock_irq(substream);
	अगर (put_user(sstatus.state, &src->s.status.state) ||
	    put_user(sstatus.hw_ptr, &src->s.status.hw_ptr) ||
	    put_user(sstatus.tstamp.tv_sec, &src->s.status.tstamp_sec) ||
	    put_user(sstatus.tstamp.tv_nsec, &src->s.status.tstamp_nsec) ||
	    put_user(sstatus.suspended_state, &src->s.status.suspended_state) ||
	    put_user(sstatus.audio_tstamp.tv_sec, &src->s.status.audio_tstamp_sec) ||
	    put_user(sstatus.audio_tstamp.tv_nsec, &src->s.status.audio_tstamp_nsec) ||
	    put_user(scontrol.appl_ptr, &src->c.control.appl_ptr) ||
	    put_user(scontrol.avail_min, &src->c.control.avail_min))
		वापस -EFAULT;

	वापस 0;
पूर्ण
#घोषणा __SNDRV_PCM_IOCTL_SYNC_PTR32 _IOWR('A', 0x23, काष्ठा snd_pcm_sync_ptr32)

अटल पूर्णांक snd_pcm_tstamp(काष्ठा snd_pcm_substream *substream, पूर्णांक __user *_arg)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	पूर्णांक arg;
	
	अगर (get_user(arg, _arg))
		वापस -EFAULT;
	अगर (arg < 0 || arg > SNDRV_PCM_TSTAMP_TYPE_LAST)
		वापस -EINVAL;
	runसमय->tstamp_type = arg;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_pcm_xferi_frames_ioctl(काष्ठा snd_pcm_substream *substream,
				      काष्ठा snd_xferi __user *_xferi)
अणु
	काष्ठा snd_xferi xferi;
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	snd_pcm_sframes_t result;

	अगर (runसमय->status->state == SNDRV_PCM_STATE_OPEN)
		वापस -EBADFD;
	अगर (put_user(0, &_xferi->result))
		वापस -EFAULT;
	अगर (copy_from_user(&xferi, _xferi, माप(xferi)))
		वापस -EFAULT;
	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		result = snd_pcm_lib_ग_लिखो(substream, xferi.buf, xferi.frames);
	अन्यथा
		result = snd_pcm_lib_पढ़ो(substream, xferi.buf, xferi.frames);
	अगर (put_user(result, &_xferi->result))
		वापस -EFAULT;
	वापस result < 0 ? result : 0;
पूर्ण

अटल पूर्णांक snd_pcm_xfern_frames_ioctl(काष्ठा snd_pcm_substream *substream,
				      काष्ठा snd_xfern __user *_xfern)
अणु
	काष्ठा snd_xfern xfern;
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	व्योम *bufs;
	snd_pcm_sframes_t result;

	अगर (runसमय->status->state == SNDRV_PCM_STATE_OPEN)
		वापस -EBADFD;
	अगर (runसमय->channels > 128)
		वापस -EINVAL;
	अगर (put_user(0, &_xfern->result))
		वापस -EFAULT;
	अगर (copy_from_user(&xfern, _xfern, माप(xfern)))
		वापस -EFAULT;

	bufs = memdup_user(xfern.bufs, माप(व्योम *) * runसमय->channels);
	अगर (IS_ERR(bufs))
		वापस PTR_ERR(bufs);
	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		result = snd_pcm_lib_ग_लिखोv(substream, bufs, xfern.frames);
	अन्यथा
		result = snd_pcm_lib_पढ़ोv(substream, bufs, xfern.frames);
	kमुक्त(bufs);
	अगर (put_user(result, &_xfern->result))
		वापस -EFAULT;
	वापस result < 0 ? result : 0;
पूर्ण

अटल पूर्णांक snd_pcm_शुरुआत_ioctl(काष्ठा snd_pcm_substream *substream,
				snd_pcm_uframes_t __user *_frames)
अणु
	snd_pcm_uframes_t frames;
	snd_pcm_sframes_t result;

	अगर (get_user(frames, _frames))
		वापस -EFAULT;
	अगर (put_user(0, _frames))
		वापस -EFAULT;
	result = snd_pcm_शुरुआत(substream, frames);
	अगर (put_user(result, _frames))
		वापस -EFAULT;
	वापस result < 0 ? result : 0;
पूर्ण

अटल पूर्णांक snd_pcm_क्रमward_ioctl(काष्ठा snd_pcm_substream *substream,
				 snd_pcm_uframes_t __user *_frames)
अणु
	snd_pcm_uframes_t frames;
	snd_pcm_sframes_t result;

	अगर (get_user(frames, _frames))
		वापस -EFAULT;
	अगर (put_user(0, _frames))
		वापस -EFAULT;
	result = snd_pcm_क्रमward(substream, frames);
	अगर (put_user(result, _frames))
		वापस -EFAULT;
	वापस result < 0 ? result : 0;
पूर्ण

अटल पूर्णांक snd_pcm_common_ioctl(काष्ठा file *file,
				 काष्ठा snd_pcm_substream *substream,
				 अचिन्हित पूर्णांक cmd, व्योम __user *arg)
अणु
	काष्ठा snd_pcm_file *pcm_file = file->निजी_data;
	पूर्णांक res;

	अगर (PCM_RUNTIME_CHECK(substream))
		वापस -ENXIO;

	res = snd_घातer_रुको(substream->pcm->card, SNDRV_CTL_POWER_D0);
	अगर (res < 0)
		वापस res;

	चयन (cmd) अणु
	हाल SNDRV_PCM_IOCTL_PVERSION:
		वापस put_user(SNDRV_PCM_VERSION, (पूर्णांक __user *)arg) ? -EFAULT : 0;
	हाल SNDRV_PCM_IOCTL_INFO:
		वापस snd_pcm_info_user(substream, arg);
	हाल SNDRV_PCM_IOCTL_TSTAMP:	/* just क्रम compatibility */
		वापस 0;
	हाल SNDRV_PCM_IOCTL_TTSTAMP:
		वापस snd_pcm_tstamp(substream, arg);
	हाल SNDRV_PCM_IOCTL_USER_PVERSION:
		अगर (get_user(pcm_file->user_pversion,
			     (अचिन्हित पूर्णांक __user *)arg))
			वापस -EFAULT;
		वापस 0;
	हाल SNDRV_PCM_IOCTL_HW_REFINE:
		वापस snd_pcm_hw_refine_user(substream, arg);
	हाल SNDRV_PCM_IOCTL_HW_PARAMS:
		वापस snd_pcm_hw_params_user(substream, arg);
	हाल SNDRV_PCM_IOCTL_HW_FREE:
		वापस snd_pcm_hw_मुक्त(substream);
	हाल SNDRV_PCM_IOCTL_SW_PARAMS:
		वापस snd_pcm_sw_params_user(substream, arg);
	हाल SNDRV_PCM_IOCTL_STATUS32:
		वापस snd_pcm_status_user32(substream, arg, false);
	हाल SNDRV_PCM_IOCTL_STATUS_EXT32:
		वापस snd_pcm_status_user32(substream, arg, true);
	हाल SNDRV_PCM_IOCTL_STATUS64:
		वापस snd_pcm_status_user64(substream, arg, false);
	हाल SNDRV_PCM_IOCTL_STATUS_EXT64:
		वापस snd_pcm_status_user64(substream, arg, true);
	हाल SNDRV_PCM_IOCTL_CHANNEL_INFO:
		वापस snd_pcm_channel_info_user(substream, arg);
	हाल SNDRV_PCM_IOCTL_PREPARE:
		वापस snd_pcm_prepare(substream, file);
	हाल SNDRV_PCM_IOCTL_RESET:
		वापस snd_pcm_reset(substream);
	हाल SNDRV_PCM_IOCTL_START:
		वापस snd_pcm_start_lock_irq(substream);
	हाल SNDRV_PCM_IOCTL_LINK:
		वापस snd_pcm_link(substream, (पूर्णांक)(अचिन्हित दीर्घ) arg);
	हाल SNDRV_PCM_IOCTL_UNLINK:
		वापस snd_pcm_unlink(substream);
	हाल SNDRV_PCM_IOCTL_RESUME:
		वापस snd_pcm_resume(substream);
	हाल SNDRV_PCM_IOCTL_XRUN:
		वापस snd_pcm_xrun(substream);
	हाल SNDRV_PCM_IOCTL_HWSYNC:
		वापस snd_pcm_hwsync(substream);
	हाल SNDRV_PCM_IOCTL_DELAY:
	अणु
		snd_pcm_sframes_t delay;
		snd_pcm_sframes_t __user *res = arg;
		पूर्णांक err;

		err = snd_pcm_delay(substream, &delay);
		अगर (err)
			वापस err;
		अगर (put_user(delay, res))
			वापस -EFAULT;
		वापस 0;
	पूर्ण
	हाल __SNDRV_PCM_IOCTL_SYNC_PTR32:
		वापस snd_pcm_ioctl_sync_ptr_compat(substream, arg);
	हाल __SNDRV_PCM_IOCTL_SYNC_PTR64:
		वापस snd_pcm_sync_ptr(substream, arg);
#अगर_घोषित CONFIG_SND_SUPPORT_OLD_API
	हाल SNDRV_PCM_IOCTL_HW_REFINE_OLD:
		वापस snd_pcm_hw_refine_old_user(substream, arg);
	हाल SNDRV_PCM_IOCTL_HW_PARAMS_OLD:
		वापस snd_pcm_hw_params_old_user(substream, arg);
#पूर्ण_अगर
	हाल SNDRV_PCM_IOCTL_DRAIN:
		वापस snd_pcm_drain(substream, file);
	हाल SNDRV_PCM_IOCTL_DROP:
		वापस snd_pcm_drop(substream);
	हाल SNDRV_PCM_IOCTL_PAUSE:
		वापस snd_pcm_छोड़ो_lock_irq(substream, (अचिन्हित दीर्घ)arg);
	हाल SNDRV_PCM_IOCTL_WRITEI_FRAMES:
	हाल SNDRV_PCM_IOCTL_READI_FRAMES:
		वापस snd_pcm_xferi_frames_ioctl(substream, arg);
	हाल SNDRV_PCM_IOCTL_WRITEN_FRAMES:
	हाल SNDRV_PCM_IOCTL_READN_FRAMES:
		वापस snd_pcm_xfern_frames_ioctl(substream, arg);
	हाल SNDRV_PCM_IOCTL_REWIND:
		वापस snd_pcm_शुरुआत_ioctl(substream, arg);
	हाल SNDRV_PCM_IOCTL_FORWARD:
		वापस snd_pcm_क्रमward_ioctl(substream, arg);
	पूर्ण
	pcm_dbg(substream->pcm, "unknown ioctl = 0x%x\n", cmd);
	वापस -ENOTTY;
पूर्ण

अटल दीर्घ snd_pcm_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
			  अचिन्हित दीर्घ arg)
अणु
	काष्ठा snd_pcm_file *pcm_file;

	pcm_file = file->निजी_data;

	अगर (((cmd >> 8) & 0xff) != 'A')
		वापस -ENOTTY;

	वापस snd_pcm_common_ioctl(file, pcm_file->substream, cmd,
				     (व्योम __user *)arg);
पूर्ण

/**
 * snd_pcm_kernel_ioctl - Execute PCM ioctl in the kernel-space
 * @substream: PCM substream
 * @cmd: IOCTL cmd
 * @arg: IOCTL argument
 *
 * The function is provided primarily क्रम OSS layer and USB gadget drivers,
 * and it allows only the limited set of ioctls (hw_params, sw_params,
 * prepare, start, drain, drop, क्रमward).
 */
पूर्णांक snd_pcm_kernel_ioctl(काष्ठा snd_pcm_substream *substream,
			 अचिन्हित पूर्णांक cmd, व्योम *arg)
अणु
	snd_pcm_uframes_t *frames = arg;
	snd_pcm_sframes_t result;
	
	चयन (cmd) अणु
	हाल SNDRV_PCM_IOCTL_FORWARD:
	अणु
		/* provided only क्रम OSS; capture-only and no value वापसed */
		अगर (substream->stream != SNDRV_PCM_STREAM_CAPTURE)
			वापस -EINVAL;
		result = snd_pcm_क्रमward(substream, *frames);
		वापस result < 0 ? result : 0;
	पूर्ण
	हाल SNDRV_PCM_IOCTL_HW_PARAMS:
		वापस snd_pcm_hw_params(substream, arg);
	हाल SNDRV_PCM_IOCTL_SW_PARAMS:
		वापस snd_pcm_sw_params(substream, arg);
	हाल SNDRV_PCM_IOCTL_PREPARE:
		वापस snd_pcm_prepare(substream, शून्य);
	हाल SNDRV_PCM_IOCTL_START:
		वापस snd_pcm_start_lock_irq(substream);
	हाल SNDRV_PCM_IOCTL_DRAIN:
		वापस snd_pcm_drain(substream, शून्य);
	हाल SNDRV_PCM_IOCTL_DROP:
		वापस snd_pcm_drop(substream);
	हाल SNDRV_PCM_IOCTL_DELAY:
		वापस snd_pcm_delay(substream, frames);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(snd_pcm_kernel_ioctl);

अटल sमाप_प्रकार snd_pcm_पढ़ो(काष्ठा file *file, अक्षर __user *buf, माप_प्रकार count,
			    loff_t * offset)
अणु
	काष्ठा snd_pcm_file *pcm_file;
	काष्ठा snd_pcm_substream *substream;
	काष्ठा snd_pcm_runसमय *runसमय;
	snd_pcm_sframes_t result;

	pcm_file = file->निजी_data;
	substream = pcm_file->substream;
	अगर (PCM_RUNTIME_CHECK(substream))
		वापस -ENXIO;
	runसमय = substream->runसमय;
	अगर (runसमय->status->state == SNDRV_PCM_STATE_OPEN)
		वापस -EBADFD;
	अगर (!frame_aligned(runसमय, count))
		वापस -EINVAL;
	count = bytes_to_frames(runसमय, count);
	result = snd_pcm_lib_पढ़ो(substream, buf, count);
	अगर (result > 0)
		result = frames_to_bytes(runसमय, result);
	वापस result;
पूर्ण

अटल sमाप_प्रकार snd_pcm_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
			     माप_प्रकार count, loff_t * offset)
अणु
	काष्ठा snd_pcm_file *pcm_file;
	काष्ठा snd_pcm_substream *substream;
	काष्ठा snd_pcm_runसमय *runसमय;
	snd_pcm_sframes_t result;

	pcm_file = file->निजी_data;
	substream = pcm_file->substream;
	अगर (PCM_RUNTIME_CHECK(substream))
		वापस -ENXIO;
	runसमय = substream->runसमय;
	अगर (runसमय->status->state == SNDRV_PCM_STATE_OPEN)
		वापस -EBADFD;
	अगर (!frame_aligned(runसमय, count))
		वापस -EINVAL;
	count = bytes_to_frames(runसमय, count);
	result = snd_pcm_lib_ग_लिखो(substream, buf, count);
	अगर (result > 0)
		result = frames_to_bytes(runसमय, result);
	वापस result;
पूर्ण

अटल sमाप_प्रकार snd_pcm_पढ़ोv(काष्ठा kiocb *iocb, काष्ठा iov_iter *to)
अणु
	काष्ठा snd_pcm_file *pcm_file;
	काष्ठा snd_pcm_substream *substream;
	काष्ठा snd_pcm_runसमय *runसमय;
	snd_pcm_sframes_t result;
	अचिन्हित दीर्घ i;
	व्योम __user **bufs;
	snd_pcm_uframes_t frames;

	pcm_file = iocb->ki_filp->निजी_data;
	substream = pcm_file->substream;
	अगर (PCM_RUNTIME_CHECK(substream))
		वापस -ENXIO;
	runसमय = substream->runसमय;
	अगर (runसमय->status->state == SNDRV_PCM_STATE_OPEN)
		वापस -EBADFD;
	अगर (!iter_is_iovec(to))
		वापस -EINVAL;
	अगर (to->nr_segs > 1024 || to->nr_segs != runसमय->channels)
		वापस -EINVAL;
	अगर (!frame_aligned(runसमय, to->iov->iov_len))
		वापस -EINVAL;
	frames = bytes_to_samples(runसमय, to->iov->iov_len);
	bufs = kदो_स्मृति_array(to->nr_segs, माप(व्योम *), GFP_KERNEL);
	अगर (bufs == शून्य)
		वापस -ENOMEM;
	क्रम (i = 0; i < to->nr_segs; ++i)
		bufs[i] = to->iov[i].iov_base;
	result = snd_pcm_lib_पढ़ोv(substream, bufs, frames);
	अगर (result > 0)
		result = frames_to_bytes(runसमय, result);
	kमुक्त(bufs);
	वापस result;
पूर्ण

अटल sमाप_प्रकार snd_pcm_ग_लिखोv(काष्ठा kiocb *iocb, काष्ठा iov_iter *from)
अणु
	काष्ठा snd_pcm_file *pcm_file;
	काष्ठा snd_pcm_substream *substream;
	काष्ठा snd_pcm_runसमय *runसमय;
	snd_pcm_sframes_t result;
	अचिन्हित दीर्घ i;
	व्योम __user **bufs;
	snd_pcm_uframes_t frames;

	pcm_file = iocb->ki_filp->निजी_data;
	substream = pcm_file->substream;
	अगर (PCM_RUNTIME_CHECK(substream))
		वापस -ENXIO;
	runसमय = substream->runसमय;
	अगर (runसमय->status->state == SNDRV_PCM_STATE_OPEN)
		वापस -EBADFD;
	अगर (!iter_is_iovec(from))
		वापस -EINVAL;
	अगर (from->nr_segs > 128 || from->nr_segs != runसमय->channels ||
	    !frame_aligned(runसमय, from->iov->iov_len))
		वापस -EINVAL;
	frames = bytes_to_samples(runसमय, from->iov->iov_len);
	bufs = kदो_स्मृति_array(from->nr_segs, माप(व्योम *), GFP_KERNEL);
	अगर (bufs == शून्य)
		वापस -ENOMEM;
	क्रम (i = 0; i < from->nr_segs; ++i)
		bufs[i] = from->iov[i].iov_base;
	result = snd_pcm_lib_ग_लिखोv(substream, bufs, frames);
	अगर (result > 0)
		result = frames_to_bytes(runसमय, result);
	kमुक्त(bufs);
	वापस result;
पूर्ण

अटल __poll_t snd_pcm_poll(काष्ठा file *file, poll_table *रुको)
अणु
	काष्ठा snd_pcm_file *pcm_file;
	काष्ठा snd_pcm_substream *substream;
	काष्ठा snd_pcm_runसमय *runसमय;
	__poll_t mask, ok;
	snd_pcm_uframes_t avail;

	pcm_file = file->निजी_data;

	substream = pcm_file->substream;
	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		ok = EPOLLOUT | EPOLLWRNORM;
	अन्यथा
		ok = EPOLLIN | EPOLLRDNORM;
	अगर (PCM_RUNTIME_CHECK(substream))
		वापस ok | EPOLLERR;

	runसमय = substream->runसमय;
	poll_रुको(file, &runसमय->sleep, रुको);

	mask = 0;
	snd_pcm_stream_lock_irq(substream);
	avail = snd_pcm_avail(substream);
	चयन (runसमय->status->state) अणु
	हाल SNDRV_PCM_STATE_RUNNING:
	हाल SNDRV_PCM_STATE_PREPARED:
	हाल SNDRV_PCM_STATE_PAUSED:
		अगर (avail >= runसमय->control->avail_min)
			mask = ok;
		अवरोध;
	हाल SNDRV_PCM_STATE_DRAINING:
		अगर (substream->stream == SNDRV_PCM_STREAM_CAPTURE) अणु
			mask = ok;
			अगर (!avail)
				mask |= EPOLLERR;
		पूर्ण
		अवरोध;
	शेष:
		mask = ok | EPOLLERR;
		अवरोध;
	पूर्ण
	snd_pcm_stream_unlock_irq(substream);
	वापस mask;
पूर्ण

/*
 * mmap support
 */

/*
 * Only on coherent architectures, we can mmap the status and the control records
 * क्रम effcient data transfer.  On others, we have to use HWSYNC ioctl...
 */
#अगर defined(CONFIG_X86) || defined(CONFIG_PPC) || defined(CONFIG_ALPHA)
/*
 * mmap status record
 */
अटल vm_fault_t snd_pcm_mmap_status_fault(काष्ठा vm_fault *vmf)
अणु
	काष्ठा snd_pcm_substream *substream = vmf->vma->vm_निजी_data;
	काष्ठा snd_pcm_runसमय *runसमय;
	
	अगर (substream == शून्य)
		वापस VM_FAULT_SIGBUS;
	runसमय = substream->runसमय;
	vmf->page = virt_to_page(runसमय->status);
	get_page(vmf->page);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा vm_operations_काष्ठा snd_pcm_vm_ops_status =
अणु
	.fault =	snd_pcm_mmap_status_fault,
पूर्ण;

अटल पूर्णांक snd_pcm_mmap_status(काष्ठा snd_pcm_substream *substream, काष्ठा file *file,
			       काष्ठा vm_area_काष्ठा *area)
अणु
	दीर्घ size;
	अगर (!(area->vm_flags & VM_READ))
		वापस -EINVAL;
	size = area->vm_end - area->vm_start;
	अगर (size != PAGE_ALIGN(माप(काष्ठा snd_pcm_mmap_status)))
		वापस -EINVAL;
	area->vm_ops = &snd_pcm_vm_ops_status;
	area->vm_निजी_data = substream;
	area->vm_flags |= VM_DONTEXPAND | VM_DONTDUMP;
	वापस 0;
पूर्ण

/*
 * mmap control record
 */
अटल vm_fault_t snd_pcm_mmap_control_fault(काष्ठा vm_fault *vmf)
अणु
	काष्ठा snd_pcm_substream *substream = vmf->vma->vm_निजी_data;
	काष्ठा snd_pcm_runसमय *runसमय;
	
	अगर (substream == शून्य)
		वापस VM_FAULT_SIGBUS;
	runसमय = substream->runसमय;
	vmf->page = virt_to_page(runसमय->control);
	get_page(vmf->page);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा vm_operations_काष्ठा snd_pcm_vm_ops_control =
अणु
	.fault =	snd_pcm_mmap_control_fault,
पूर्ण;

अटल पूर्णांक snd_pcm_mmap_control(काष्ठा snd_pcm_substream *substream, काष्ठा file *file,
				काष्ठा vm_area_काष्ठा *area)
अणु
	दीर्घ size;
	अगर (!(area->vm_flags & VM_READ))
		वापस -EINVAL;
	size = area->vm_end - area->vm_start;
	अगर (size != PAGE_ALIGN(माप(काष्ठा snd_pcm_mmap_control)))
		वापस -EINVAL;
	area->vm_ops = &snd_pcm_vm_ops_control;
	area->vm_निजी_data = substream;
	area->vm_flags |= VM_DONTEXPAND | VM_DONTDUMP;
	वापस 0;
पूर्ण

अटल bool pcm_status_mmap_allowed(काष्ठा snd_pcm_file *pcm_file)
अणु
	/* See pcm_control_mmap_allowed() below.
	 * Since older alsa-lib requires both status and control mmaps to be
	 * coupled, we have to disable the status mmap क्रम old alsa-lib, too.
	 */
	अगर (pcm_file->user_pversion < SNDRV_PROTOCOL_VERSION(2, 0, 14) &&
	    (pcm_file->substream->runसमय->hw.info & SNDRV_PCM_INFO_SYNC_APPLPTR))
		वापस false;
	वापस true;
पूर्ण

अटल bool pcm_control_mmap_allowed(काष्ठा snd_pcm_file *pcm_file)
अणु
	अगर (pcm_file->no_compat_mmap)
		वापस false;
	/* Disallow the control mmap when SYNC_APPLPTR flag is set;
	 * it enक्रमces the user-space to fall back to snd_pcm_sync_ptr(),
	 * thus it effectively assures the manual update of appl_ptr.
	 */
	अगर (pcm_file->substream->runसमय->hw.info & SNDRV_PCM_INFO_SYNC_APPLPTR)
		वापस false;
	वापस true;
पूर्ण

#अन्यथा /* ! coherent mmap */
/*
 * करोn't support mmap क्रम status and control records.
 */
#घोषणा pcm_status_mmap_allowed(pcm_file)	false
#घोषणा pcm_control_mmap_allowed(pcm_file)	false

अटल पूर्णांक snd_pcm_mmap_status(काष्ठा snd_pcm_substream *substream, काष्ठा file *file,
			       काष्ठा vm_area_काष्ठा *area)
अणु
	वापस -ENXIO;
पूर्ण
अटल पूर्णांक snd_pcm_mmap_control(काष्ठा snd_pcm_substream *substream, काष्ठा file *file,
				काष्ठा vm_area_काष्ठा *area)
अणु
	वापस -ENXIO;
पूर्ण
#पूर्ण_अगर /* coherent mmap */

अटल अंतरभूत काष्ठा page *
snd_pcm_शेष_page_ops(काष्ठा snd_pcm_substream *substream, अचिन्हित दीर्घ ofs)
अणु
	व्योम *vaddr = substream->runसमय->dma_area + ofs;

	चयन (substream->dma_buffer.dev.type) अणु
#अगर_घोषित CONFIG_SND_DMA_SGBUF
	हाल SNDRV_DMA_TYPE_DEV_SG:
	हाल SNDRV_DMA_TYPE_DEV_UC_SG:
		वापस snd_pcm_sgbuf_ops_page(substream, ofs);
#पूर्ण_अगर /* CONFIG_SND_DMA_SGBUF */
	हाल SNDRV_DMA_TYPE_VMALLOC:
		वापस vदो_स्मृति_to_page(vaddr);
	शेष:
		वापस virt_to_page(vaddr);
	पूर्ण
पूर्ण

/*
 * fault callback क्रम mmapping a RAM page
 */
अटल vm_fault_t snd_pcm_mmap_data_fault(काष्ठा vm_fault *vmf)
अणु
	काष्ठा snd_pcm_substream *substream = vmf->vma->vm_निजी_data;
	काष्ठा snd_pcm_runसमय *runसमय;
	अचिन्हित दीर्घ offset;
	काष्ठा page * page;
	माप_प्रकार dma_bytes;
	
	अगर (substream == शून्य)
		वापस VM_FAULT_SIGBUS;
	runसमय = substream->runसमय;
	offset = vmf->pgoff << PAGE_SHIFT;
	dma_bytes = PAGE_ALIGN(runसमय->dma_bytes);
	अगर (offset > dma_bytes - PAGE_SIZE)
		वापस VM_FAULT_SIGBUS;
	अगर (substream->ops->page)
		page = substream->ops->page(substream, offset);
	अन्यथा
		page = snd_pcm_शेष_page_ops(substream, offset);
	अगर (!page)
		वापस VM_FAULT_SIGBUS;
	get_page(page);
	vmf->page = page;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा vm_operations_काष्ठा snd_pcm_vm_ops_data = अणु
	.खोलो =		snd_pcm_mmap_data_खोलो,
	.बंद =	snd_pcm_mmap_data_बंद,
पूर्ण;

अटल स्थिर काष्ठा vm_operations_काष्ठा snd_pcm_vm_ops_data_fault = अणु
	.खोलो =		snd_pcm_mmap_data_खोलो,
	.बंद =	snd_pcm_mmap_data_बंद,
	.fault =	snd_pcm_mmap_data_fault,
पूर्ण;

/*
 * mmap the DMA buffer on RAM
 */

/**
 * snd_pcm_lib_शेष_mmap - Default PCM data mmap function
 * @substream: PCM substream
 * @area: VMA
 *
 * This is the शेष mmap handler क्रम PCM data.  When mmap pcm_ops is शून्य,
 * this function is invoked implicitly.
 */
पूर्णांक snd_pcm_lib_शेष_mmap(काष्ठा snd_pcm_substream *substream,
			     काष्ठा vm_area_काष्ठा *area)
अणु
	area->vm_flags |= VM_DONTEXPAND | VM_DONTDUMP;
#अगर_घोषित CONFIG_GENERIC_ALLOCATOR
	अगर (substream->dma_buffer.dev.type == SNDRV_DMA_TYPE_DEV_IRAM) अणु
		area->vm_page_prot = pgprot_ग_लिखोcombine(area->vm_page_prot);
		वापस remap_pfn_range(area, area->vm_start,
				substream->dma_buffer.addr >> PAGE_SHIFT,
				area->vm_end - area->vm_start, area->vm_page_prot);
	पूर्ण
#पूर्ण_अगर /* CONFIG_GENERIC_ALLOCATOR */
	अगर (IS_ENABLED(CONFIG_HAS_DMA) && !substream->ops->page &&
	    (substream->dma_buffer.dev.type == SNDRV_DMA_TYPE_DEV ||
	     substream->dma_buffer.dev.type == SNDRV_DMA_TYPE_DEV_UC))
		वापस dma_mmap_coherent(substream->dma_buffer.dev.dev,
					 area,
					 substream->runसमय->dma_area,
					 substream->runसमय->dma_addr,
					 substream->runसमय->dma_bytes);
	/* mmap with fault handler */
	area->vm_ops = &snd_pcm_vm_ops_data_fault;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_pcm_lib_शेष_mmap);

/*
 * mmap the DMA buffer on I/O memory area
 */
#अगर SNDRV_PCM_INFO_MMAP_IOMEM
/**
 * snd_pcm_lib_mmap_iomem - Default PCM data mmap function क्रम I/O mem
 * @substream: PCM substream
 * @area: VMA
 *
 * When your hardware uses the iomapped pages as the hardware buffer and
 * wants to mmap it, pass this function as mmap pcm_ops.  Note that this
 * is supposed to work only on limited architectures.
 */
पूर्णांक snd_pcm_lib_mmap_iomem(काष्ठा snd_pcm_substream *substream,
			   काष्ठा vm_area_काष्ठा *area)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;

	area->vm_page_prot = pgprot_noncached(area->vm_page_prot);
	वापस vm_iomap_memory(area, runसमय->dma_addr, runसमय->dma_bytes);
पूर्ण
EXPORT_SYMBOL(snd_pcm_lib_mmap_iomem);
#पूर्ण_अगर /* SNDRV_PCM_INFO_MMAP */

/*
 * mmap DMA buffer
 */
पूर्णांक snd_pcm_mmap_data(काष्ठा snd_pcm_substream *substream, काष्ठा file *file,
		      काष्ठा vm_area_काष्ठा *area)
अणु
	काष्ठा snd_pcm_runसमय *runसमय;
	दीर्घ size;
	अचिन्हित दीर्घ offset;
	माप_प्रकार dma_bytes;
	पूर्णांक err;

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
		अगर (!(area->vm_flags & (VM_WRITE|VM_READ)))
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		अगर (!(area->vm_flags & VM_READ))
			वापस -EINVAL;
	पूर्ण
	runसमय = substream->runसमय;
	अगर (runसमय->status->state == SNDRV_PCM_STATE_OPEN)
		वापस -EBADFD;
	अगर (!(runसमय->info & SNDRV_PCM_INFO_MMAP))
		वापस -ENXIO;
	अगर (runसमय->access == SNDRV_PCM_ACCESS_RW_INTERLEAVED ||
	    runसमय->access == SNDRV_PCM_ACCESS_RW_NONINTERLEAVED)
		वापस -EINVAL;
	size = area->vm_end - area->vm_start;
	offset = area->vm_pgoff << PAGE_SHIFT;
	dma_bytes = PAGE_ALIGN(runसमय->dma_bytes);
	अगर ((माप_प्रकार)size > dma_bytes)
		वापस -EINVAL;
	अगर (offset > dma_bytes - size)
		वापस -EINVAL;

	area->vm_ops = &snd_pcm_vm_ops_data;
	area->vm_निजी_data = substream;
	अगर (substream->ops->mmap)
		err = substream->ops->mmap(substream, area);
	अन्यथा
		err = snd_pcm_lib_शेष_mmap(substream, area);
	अगर (!err)
		atomic_inc(&substream->mmap_count);
	वापस err;
पूर्ण
EXPORT_SYMBOL(snd_pcm_mmap_data);

अटल पूर्णांक snd_pcm_mmap(काष्ठा file *file, काष्ठा vm_area_काष्ठा *area)
अणु
	काष्ठा snd_pcm_file * pcm_file;
	काष्ठा snd_pcm_substream *substream;	
	अचिन्हित दीर्घ offset;
	
	pcm_file = file->निजी_data;
	substream = pcm_file->substream;
	अगर (PCM_RUNTIME_CHECK(substream))
		वापस -ENXIO;

	offset = area->vm_pgoff << PAGE_SHIFT;
	चयन (offset) अणु
	हाल SNDRV_PCM_MMAP_OFFSET_STATUS_OLD:
		अगर (pcm_file->no_compat_mmap || !IS_ENABLED(CONFIG_64BIT))
			वापस -ENXIO;
		fallthrough;
	हाल SNDRV_PCM_MMAP_OFFSET_STATUS_NEW:
		अगर (!pcm_status_mmap_allowed(pcm_file))
			वापस -ENXIO;
		वापस snd_pcm_mmap_status(substream, file, area);
	हाल SNDRV_PCM_MMAP_OFFSET_CONTROL_OLD:
		अगर (pcm_file->no_compat_mmap || !IS_ENABLED(CONFIG_64BIT))
			वापस -ENXIO;
		fallthrough;
	हाल SNDRV_PCM_MMAP_OFFSET_CONTROL_NEW:
		अगर (!pcm_control_mmap_allowed(pcm_file))
			वापस -ENXIO;
		वापस snd_pcm_mmap_control(substream, file, area);
	शेष:
		वापस snd_pcm_mmap_data(substream, file, area);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक snd_pcm_fasync(पूर्णांक fd, काष्ठा file * file, पूर्णांक on)
अणु
	काष्ठा snd_pcm_file * pcm_file;
	काष्ठा snd_pcm_substream *substream;
	काष्ठा snd_pcm_runसमय *runसमय;

	pcm_file = file->निजी_data;
	substream = pcm_file->substream;
	अगर (PCM_RUNTIME_CHECK(substream))
		वापस -ENXIO;
	runसमय = substream->runसमय;
	वापस fasync_helper(fd, file, on, &runसमय->fasync);
पूर्ण

/*
 * ioctl32 compat
 */
#अगर_घोषित CONFIG_COMPAT
#समावेश "pcm_compat.c"
#अन्यथा
#घोषणा snd_pcm_ioctl_compat	शून्य
#पूर्ण_अगर

/*
 *  To be हटाओd helpers to keep binary compatibility
 */

#अगर_घोषित CONFIG_SND_SUPPORT_OLD_API
#घोषणा __OLD_TO_NEW_MASK(x) ((x&7)|((x&0x07fffff8)<<5))
#घोषणा __NEW_TO_OLD_MASK(x) ((x&7)|((x&0xffffff00)>>5))

अटल व्योम snd_pcm_hw_convert_from_old_params(काष्ठा snd_pcm_hw_params *params,
					       काष्ठा snd_pcm_hw_params_old *oparams)
अणु
	अचिन्हित पूर्णांक i;

	स_रखो(params, 0, माप(*params));
	params->flags = oparams->flags;
	क्रम (i = 0; i < ARRAY_SIZE(oparams->masks); i++)
		params->masks[i].bits[0] = oparams->masks[i];
	स_नकल(params->पूर्णांकervals, oparams->पूर्णांकervals, माप(oparams->पूर्णांकervals));
	params->rmask = __OLD_TO_NEW_MASK(oparams->rmask);
	params->cmask = __OLD_TO_NEW_MASK(oparams->cmask);
	params->info = oparams->info;
	params->msbits = oparams->msbits;
	params->rate_num = oparams->rate_num;
	params->rate_den = oparams->rate_den;
	params->fअगरo_size = oparams->fअगरo_size;
पूर्ण

अटल व्योम snd_pcm_hw_convert_to_old_params(काष्ठा snd_pcm_hw_params_old *oparams,
					     काष्ठा snd_pcm_hw_params *params)
अणु
	अचिन्हित पूर्णांक i;

	स_रखो(oparams, 0, माप(*oparams));
	oparams->flags = params->flags;
	क्रम (i = 0; i < ARRAY_SIZE(oparams->masks); i++)
		oparams->masks[i] = params->masks[i].bits[0];
	स_नकल(oparams->पूर्णांकervals, params->पूर्णांकervals, माप(oparams->पूर्णांकervals));
	oparams->rmask = __NEW_TO_OLD_MASK(params->rmask);
	oparams->cmask = __NEW_TO_OLD_MASK(params->cmask);
	oparams->info = params->info;
	oparams->msbits = params->msbits;
	oparams->rate_num = params->rate_num;
	oparams->rate_den = params->rate_den;
	oparams->fअगरo_size = params->fअगरo_size;
पूर्ण

अटल पूर्णांक snd_pcm_hw_refine_old_user(काष्ठा snd_pcm_substream *substream,
				      काष्ठा snd_pcm_hw_params_old __user * _oparams)
अणु
	काष्ठा snd_pcm_hw_params *params;
	काष्ठा snd_pcm_hw_params_old *oparams = शून्य;
	पूर्णांक err;

	params = kदो_स्मृति(माप(*params), GFP_KERNEL);
	अगर (!params)
		वापस -ENOMEM;

	oparams = memdup_user(_oparams, माप(*oparams));
	अगर (IS_ERR(oparams)) अणु
		err = PTR_ERR(oparams);
		जाओ out;
	पूर्ण
	snd_pcm_hw_convert_from_old_params(params, oparams);
	err = snd_pcm_hw_refine(substream, params);
	अगर (err < 0)
		जाओ out_old;

	err = fixup_unreferenced_params(substream, params);
	अगर (err < 0)
		जाओ out_old;

	snd_pcm_hw_convert_to_old_params(oparams, params);
	अगर (copy_to_user(_oparams, oparams, माप(*oparams)))
		err = -EFAULT;
out_old:
	kमुक्त(oparams);
out:
	kमुक्त(params);
	वापस err;
पूर्ण

अटल पूर्णांक snd_pcm_hw_params_old_user(काष्ठा snd_pcm_substream *substream,
				      काष्ठा snd_pcm_hw_params_old __user * _oparams)
अणु
	काष्ठा snd_pcm_hw_params *params;
	काष्ठा snd_pcm_hw_params_old *oparams = शून्य;
	पूर्णांक err;

	params = kदो_स्मृति(माप(*params), GFP_KERNEL);
	अगर (!params)
		वापस -ENOMEM;

	oparams = memdup_user(_oparams, माप(*oparams));
	अगर (IS_ERR(oparams)) अणु
		err = PTR_ERR(oparams);
		जाओ out;
	पूर्ण

	snd_pcm_hw_convert_from_old_params(params, oparams);
	err = snd_pcm_hw_params(substream, params);
	अगर (err < 0)
		जाओ out_old;

	snd_pcm_hw_convert_to_old_params(oparams, params);
	अगर (copy_to_user(_oparams, oparams, माप(*oparams)))
		err = -EFAULT;
out_old:
	kमुक्त(oparams);
out:
	kमुक्त(params);
	वापस err;
पूर्ण
#पूर्ण_अगर /* CONFIG_SND_SUPPORT_OLD_API */

#अगर_अघोषित CONFIG_MMU
अटल अचिन्हित दीर्घ snd_pcm_get_unmapped_area(काष्ठा file *file,
					       अचिन्हित दीर्घ addr,
					       अचिन्हित दीर्घ len,
					       अचिन्हित दीर्घ pgoff,
					       अचिन्हित दीर्घ flags)
अणु
	काष्ठा snd_pcm_file *pcm_file = file->निजी_data;
	काष्ठा snd_pcm_substream *substream = pcm_file->substream;
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	अचिन्हित दीर्घ offset = pgoff << PAGE_SHIFT;

	चयन (offset) अणु
	हाल SNDRV_PCM_MMAP_OFFSET_STATUS_NEW:
		वापस (अचिन्हित दीर्घ)runसमय->status;
	हाल SNDRV_PCM_MMAP_OFFSET_CONTROL_NEW:
		वापस (अचिन्हित दीर्घ)runसमय->control;
	शेष:
		वापस (अचिन्हित दीर्घ)runसमय->dma_area + offset;
	पूर्ण
पूर्ण
#अन्यथा
# define snd_pcm_get_unmapped_area शून्य
#पूर्ण_अगर

/*
 *  Register section
 */

स्थिर काष्ठा file_operations snd_pcm_f_ops[2] = अणु
	अणु
		.owner =		THIS_MODULE,
		.ग_लिखो =		snd_pcm_ग_लिखो,
		.ग_लिखो_iter =		snd_pcm_ग_लिखोv,
		.खोलो =			snd_pcm_playback_खोलो,
		.release =		snd_pcm_release,
		.llseek =		no_llseek,
		.poll =			snd_pcm_poll,
		.unlocked_ioctl =	snd_pcm_ioctl,
		.compat_ioctl = 	snd_pcm_ioctl_compat,
		.mmap =			snd_pcm_mmap,
		.fasync =		snd_pcm_fasync,
		.get_unmapped_area =	snd_pcm_get_unmapped_area,
	पूर्ण,
	अणु
		.owner =		THIS_MODULE,
		.पढ़ो =			snd_pcm_पढ़ो,
		.पढ़ो_iter =		snd_pcm_पढ़ोv,
		.खोलो =			snd_pcm_capture_खोलो,
		.release =		snd_pcm_release,
		.llseek =		no_llseek,
		.poll =			snd_pcm_poll,
		.unlocked_ioctl =	snd_pcm_ioctl,
		.compat_ioctl = 	snd_pcm_ioctl_compat,
		.mmap =			snd_pcm_mmap,
		.fasync =		snd_pcm_fasync,
		.get_unmapped_area =	snd_pcm_get_unmapped_area,
	पूर्ण
पूर्ण;
