<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Digital Audio (PCM) असलtract layer / OSS compatible
 *  Copyright (c) by Jaroslav Kysela <perex@perex.cz>
 */

#अगर 0
#घोषणा PLUGIN_DEBUG
#पूर्ण_अगर
#अगर 0
#घोषणा OSS_DEBUG
#पूर्ण_अगर

#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/समय.स>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/module.h>
#समावेश <linux/math64.h>
#समावेश <linux/माला.स>
#समावेश <linux/compat.h>
#समावेश <sound/core.h>
#समावेश <sound/minors.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश "pcm_plugin.h"
#समावेश <sound/info.h>
#समावेश <linux/soundcard.h>
#समावेश <sound/initval.h>
#समावेश <sound/mixer_oss.h>

#घोषणा OSS_ALSAEMULVER		_SIOR ('M', 249, पूर्णांक)

अटल पूर्णांक dsp_map[SNDRV_CARDS];
अटल पूर्णांक adsp_map[SNDRV_CARDS] = अणु[0 ... (SNDRV_CARDS-1)] = 1पूर्ण;
अटल bool nonblock_खोलो = 1;

MODULE_AUTHOR("Jaroslav Kysela <perex@perex.cz>, Abramo Bagnara <abramo@alsa-project.org>");
MODULE_DESCRIPTION("PCM OSS emulation for ALSA.");
MODULE_LICENSE("GPL");
module_param_array(dsp_map, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(dsp_map, "PCM device number assigned to 1st OSS device.");
module_param_array(adsp_map, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(adsp_map, "PCM device number assigned to 2nd OSS device.");
module_param(nonblock_खोलो, bool, 0644);
MODULE_PARM_DESC(nonblock_खोलो, "Don't block opening busy PCM devices.");
MODULE_ALIAS_SNDRV_MINOR(SNDRV_MINOR_OSS_PCM);
MODULE_ALIAS_SNDRV_MINOR(SNDRV_MINOR_OSS_PCM1);

अटल पूर्णांक snd_pcm_oss_get_rate(काष्ठा snd_pcm_oss_file *pcm_oss_file);
अटल पूर्णांक snd_pcm_oss_get_channels(काष्ठा snd_pcm_oss_file *pcm_oss_file);
अटल पूर्णांक snd_pcm_oss_get_क्रमmat(काष्ठा snd_pcm_oss_file *pcm_oss_file);

/*
 * helper functions to process hw_params
 */
अटल पूर्णांक snd_पूर्णांकerval_refine_min(काष्ठा snd_पूर्णांकerval *i, अचिन्हित पूर्णांक min, पूर्णांक खोलोmin)
अणु
	पूर्णांक changed = 0;
	अगर (i->min < min) अणु
		i->min = min;
		i->खोलोmin = खोलोmin;
		changed = 1;
	पूर्ण अन्यथा अगर (i->min == min && !i->खोलोmin && खोलोmin) अणु
		i->खोलोmin = 1;
		changed = 1;
	पूर्ण
	अगर (i->पूर्णांकeger) अणु
		अगर (i->खोलोmin) अणु
			i->min++;
			i->खोलोmin = 0;
		पूर्ण
	पूर्ण
	अगर (snd_पूर्णांकerval_checkempty(i)) अणु
		snd_पूर्णांकerval_none(i);
		वापस -EINVAL;
	पूर्ण
	वापस changed;
पूर्ण

अटल पूर्णांक snd_पूर्णांकerval_refine_max(काष्ठा snd_पूर्णांकerval *i, अचिन्हित पूर्णांक max, पूर्णांक खोलोmax)
अणु
	पूर्णांक changed = 0;
	अगर (i->max > max) अणु
		i->max = max;
		i->खोलोmax = खोलोmax;
		changed = 1;
	पूर्ण अन्यथा अगर (i->max == max && !i->खोलोmax && खोलोmax) अणु
		i->खोलोmax = 1;
		changed = 1;
	पूर्ण
	अगर (i->पूर्णांकeger) अणु
		अगर (i->खोलोmax) अणु
			i->max--;
			i->खोलोmax = 0;
		पूर्ण
	पूर्ण
	अगर (snd_पूर्णांकerval_checkempty(i)) अणु
		snd_पूर्णांकerval_none(i);
		वापस -EINVAL;
	पूर्ण
	वापस changed;
पूर्ण

अटल पूर्णांक snd_पूर्णांकerval_refine_set(काष्ठा snd_पूर्णांकerval *i, अचिन्हित पूर्णांक val)
अणु
	काष्ठा snd_पूर्णांकerval t;
	t.empty = 0;
	t.min = t.max = val;
	t.खोलोmin = t.खोलोmax = 0;
	t.पूर्णांकeger = 1;
	वापस snd_पूर्णांकerval_refine(i, &t);
पूर्ण

/**
 * snd_pcm_hw_param_value_min
 * @params: the hw_params instance
 * @var: parameter to retrieve
 * @dir: poपूर्णांकer to the direction (-1,0,1) or शून्य
 *
 * Return the minimum value क्रम field PAR.
 */
अटल अचिन्हित पूर्णांक
snd_pcm_hw_param_value_min(स्थिर काष्ठा snd_pcm_hw_params *params,
			   snd_pcm_hw_param_t var, पूर्णांक *dir)
अणु
	अगर (hw_is_mask(var)) अणु
		अगर (dir)
			*dir = 0;
		वापस snd_mask_min(hw_param_mask_c(params, var));
	पूर्ण
	अगर (hw_is_पूर्णांकerval(var)) अणु
		स्थिर काष्ठा snd_पूर्णांकerval *i = hw_param_पूर्णांकerval_c(params, var);
		अगर (dir)
			*dir = i->खोलोmin;
		वापस snd_पूर्णांकerval_min(i);
	पूर्ण
	वापस -EINVAL;
पूर्ण

/**
 * snd_pcm_hw_param_value_max
 * @params: the hw_params instance
 * @var: parameter to retrieve
 * @dir: poपूर्णांकer to the direction (-1,0,1) or शून्य
 *
 * Return the maximum value क्रम field PAR.
 */
अटल अचिन्हित पूर्णांक
snd_pcm_hw_param_value_max(स्थिर काष्ठा snd_pcm_hw_params *params,
			   snd_pcm_hw_param_t var, पूर्णांक *dir)
अणु
	अगर (hw_is_mask(var)) अणु
		अगर (dir)
			*dir = 0;
		वापस snd_mask_max(hw_param_mask_c(params, var));
	पूर्ण
	अगर (hw_is_पूर्णांकerval(var)) अणु
		स्थिर काष्ठा snd_पूर्णांकerval *i = hw_param_पूर्णांकerval_c(params, var);
		अगर (dir)
			*dir = - (पूर्णांक) i->खोलोmax;
		वापस snd_पूर्णांकerval_max(i);
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक _snd_pcm_hw_param_mask(काष्ठा snd_pcm_hw_params *params,
				  snd_pcm_hw_param_t var,
				  स्थिर काष्ठा snd_mask *val)
अणु
	पूर्णांक changed;
	changed = snd_mask_refine(hw_param_mask(params, var), val);
	अगर (changed > 0) अणु
		params->cmask |= 1 << var;
		params->rmask |= 1 << var;
	पूर्ण
	वापस changed;
पूर्ण

अटल पूर्णांक snd_pcm_hw_param_mask(काष्ठा snd_pcm_substream *pcm,
				 काष्ठा snd_pcm_hw_params *params,
				 snd_pcm_hw_param_t var,
				 स्थिर काष्ठा snd_mask *val)
अणु
	पूर्णांक changed = _snd_pcm_hw_param_mask(params, var, val);
	अगर (changed < 0)
		वापस changed;
	अगर (params->rmask) अणु
		पूर्णांक err = snd_pcm_hw_refine(pcm, params);
		अगर (err < 0)
			वापस err;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक _snd_pcm_hw_param_min(काष्ठा snd_pcm_hw_params *params,
				 snd_pcm_hw_param_t var, अचिन्हित पूर्णांक val,
				 पूर्णांक dir)
अणु
	पूर्णांक changed;
	पूर्णांक खोलो = 0;
	अगर (dir) अणु
		अगर (dir > 0) अणु
			खोलो = 1;
		पूर्ण अन्यथा अगर (dir < 0) अणु
			अगर (val > 0) अणु
				खोलो = 1;
				val--;
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (hw_is_mask(var))
		changed = snd_mask_refine_min(hw_param_mask(params, var),
					      val + !!खोलो);
	अन्यथा अगर (hw_is_पूर्णांकerval(var))
		changed = snd_पूर्णांकerval_refine_min(hw_param_पूर्णांकerval(params, var),
						  val, खोलो);
	अन्यथा
		वापस -EINVAL;
	अगर (changed > 0) अणु
		params->cmask |= 1 << var;
		params->rmask |= 1 << var;
	पूर्ण
	वापस changed;
पूर्ण

/**
 * snd_pcm_hw_param_min
 * @pcm: PCM instance
 * @params: the hw_params instance
 * @var: parameter to retrieve
 * @val: minimal value
 * @dir: poपूर्णांकer to the direction (-1,0,1) or शून्य
 *
 * Inside configuration space defined by PARAMS हटाओ from PAR all 
 * values < VAL. Reduce configuration space accordingly.
 * Return new minimum or -EINVAL अगर the configuration space is empty
 */
अटल पूर्णांक snd_pcm_hw_param_min(काष्ठा snd_pcm_substream *pcm,
				काष्ठा snd_pcm_hw_params *params,
				snd_pcm_hw_param_t var, अचिन्हित पूर्णांक val,
				पूर्णांक *dir)
अणु
	पूर्णांक changed = _snd_pcm_hw_param_min(params, var, val, dir ? *dir : 0);
	अगर (changed < 0)
		वापस changed;
	अगर (params->rmask) अणु
		पूर्णांक err = snd_pcm_hw_refine(pcm, params);
		अगर (err < 0)
			वापस err;
	पूर्ण
	वापस snd_pcm_hw_param_value_min(params, var, dir);
पूर्ण

अटल पूर्णांक _snd_pcm_hw_param_max(काष्ठा snd_pcm_hw_params *params,
				 snd_pcm_hw_param_t var, अचिन्हित पूर्णांक val,
				 पूर्णांक dir)
अणु
	पूर्णांक changed;
	पूर्णांक खोलो = 0;
	अगर (dir) अणु
		अगर (dir < 0) अणु
			खोलो = 1;
		पूर्ण अन्यथा अगर (dir > 0) अणु
			खोलो = 1;
			val++;
		पूर्ण
	पूर्ण
	अगर (hw_is_mask(var)) अणु
		अगर (val == 0 && खोलो) अणु
			snd_mask_none(hw_param_mask(params, var));
			changed = -EINVAL;
		पूर्ण अन्यथा
			changed = snd_mask_refine_max(hw_param_mask(params, var),
						      val - !!खोलो);
	पूर्ण अन्यथा अगर (hw_is_पूर्णांकerval(var))
		changed = snd_पूर्णांकerval_refine_max(hw_param_पूर्णांकerval(params, var),
						  val, खोलो);
	अन्यथा
		वापस -EINVAL;
	अगर (changed > 0) अणु
		params->cmask |= 1 << var;
		params->rmask |= 1 << var;
	पूर्ण
	वापस changed;
पूर्ण

/**
 * snd_pcm_hw_param_max
 * @pcm: PCM instance
 * @params: the hw_params instance
 * @var: parameter to retrieve
 * @val: maximal value
 * @dir: poपूर्णांकer to the direction (-1,0,1) or शून्य
 *
 * Inside configuration space defined by PARAMS हटाओ from PAR all 
 *  values >= VAL + 1. Reduce configuration space accordingly.
 *  Return new maximum or -EINVAL अगर the configuration space is empty
 */
अटल पूर्णांक snd_pcm_hw_param_max(काष्ठा snd_pcm_substream *pcm,
				काष्ठा snd_pcm_hw_params *params,
				snd_pcm_hw_param_t var, अचिन्हित पूर्णांक val,
				पूर्णांक *dir)
अणु
	पूर्णांक changed = _snd_pcm_hw_param_max(params, var, val, dir ? *dir : 0);
	अगर (changed < 0)
		वापस changed;
	अगर (params->rmask) अणु
		पूर्णांक err = snd_pcm_hw_refine(pcm, params);
		अगर (err < 0)
			वापस err;
	पूर्ण
	वापस snd_pcm_hw_param_value_max(params, var, dir);
पूर्ण

अटल पूर्णांक boundary_sub(पूर्णांक a, पूर्णांक adir,
			पूर्णांक b, पूर्णांक bdir,
			पूर्णांक *c, पूर्णांक *cdir)
अणु
	adir = adir < 0 ? -1 : (adir > 0 ? 1 : 0);
	bdir = bdir < 0 ? -1 : (bdir > 0 ? 1 : 0);
	*c = a - b;
	*cdir = adir - bdir;
	अगर (*cdir == -2) अणु
		(*c)--;
	पूर्ण अन्यथा अगर (*cdir == 2) अणु
		(*c)++;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक boundary_lt(अचिन्हित पूर्णांक a, पूर्णांक adir,
		       अचिन्हित पूर्णांक b, पूर्णांक bdir)
अणु
	अगर (adir < 0) अणु
		a--;
		adir = 1;
	पूर्ण अन्यथा अगर (adir > 0)
		adir = 1;
	अगर (bdir < 0) अणु
		b--;
		bdir = 1;
	पूर्ण अन्यथा अगर (bdir > 0)
		bdir = 1;
	वापस a < b || (a == b && adir < bdir);
पूर्ण

/* Return 1 अगर min is nearer to best than max */
अटल पूर्णांक boundary_nearer(पूर्णांक min, पूर्णांक mindir,
			   पूर्णांक best, पूर्णांक bestdir,
			   पूर्णांक max, पूर्णांक maxdir)
अणु
	पूर्णांक dmin, dmindir;
	पूर्णांक dmax, dmaxdir;
	boundary_sub(best, bestdir, min, mindir, &dmin, &dmindir);
	boundary_sub(max, maxdir, best, bestdir, &dmax, &dmaxdir);
	वापस boundary_lt(dmin, dmindir, dmax, dmaxdir);
पूर्ण

/**
 * snd_pcm_hw_param_near
 * @pcm: PCM instance
 * @params: the hw_params instance
 * @var: parameter to retrieve
 * @best: value to set
 * @dir: poपूर्णांकer to the direction (-1,0,1) or शून्य
 *
 * Inside configuration space defined by PARAMS set PAR to the available value
 * nearest to VAL. Reduce configuration space accordingly.
 * This function cannot be called क्रम SNDRV_PCM_HW_PARAM_ACCESS,
 * SNDRV_PCM_HW_PARAM_FORMAT, SNDRV_PCM_HW_PARAM_SUBFORMAT.
 * Return the value found.
  */
अटल पूर्णांक snd_pcm_hw_param_near(काष्ठा snd_pcm_substream *pcm,
				 काष्ठा snd_pcm_hw_params *params,
				 snd_pcm_hw_param_t var, अचिन्हित पूर्णांक best,
				 पूर्णांक *dir)
अणु
	काष्ठा snd_pcm_hw_params *save = शून्य;
	पूर्णांक v;
	अचिन्हित पूर्णांक saved_min;
	पूर्णांक last = 0;
	पूर्णांक min, max;
	पूर्णांक mindir, maxdir;
	पूर्णांक valdir = dir ? *dir : 0;
	/* FIXME */
	अगर (best > पूर्णांक_उच्च)
		best = पूर्णांक_उच्च;
	min = max = best;
	mindir = maxdir = valdir;
	अगर (maxdir > 0)
		maxdir = 0;
	अन्यथा अगर (maxdir == 0)
		maxdir = -1;
	अन्यथा अणु
		maxdir = 1;
		max--;
	पूर्ण
	save = kदो_स्मृति(माप(*save), GFP_KERNEL);
	अगर (save == शून्य)
		वापस -ENOMEM;
	*save = *params;
	saved_min = min;
	min = snd_pcm_hw_param_min(pcm, params, var, min, &mindir);
	अगर (min >= 0) अणु
		काष्ठा snd_pcm_hw_params *params1;
		अगर (max < 0)
			जाओ _end;
		अगर ((अचिन्हित पूर्णांक)min == saved_min && mindir == valdir)
			जाओ _end;
		params1 = kदो_स्मृति(माप(*params1), GFP_KERNEL);
		अगर (params1 == शून्य) अणु
			kमुक्त(save);
			वापस -ENOMEM;
		पूर्ण
		*params1 = *save;
		max = snd_pcm_hw_param_max(pcm, params1, var, max, &maxdir);
		अगर (max < 0) अणु
			kमुक्त(params1);
			जाओ _end;
		पूर्ण
		अगर (boundary_nearer(max, maxdir, best, valdir, min, mindir)) अणु
			*params = *params1;
			last = 1;
		पूर्ण
		kमुक्त(params1);
	पूर्ण अन्यथा अणु
		*params = *save;
		max = snd_pcm_hw_param_max(pcm, params, var, max, &maxdir);
		अगर (max < 0) अणु
			kमुक्त(save);
			वापस max;
		पूर्ण
		last = 1;
	पूर्ण
 _end:
 	kमुक्त(save);
	अगर (last)
		v = snd_pcm_hw_param_last(pcm, params, var, dir);
	अन्यथा
		v = snd_pcm_hw_param_first(pcm, params, var, dir);
	वापस v;
पूर्ण

अटल पूर्णांक _snd_pcm_hw_param_set(काष्ठा snd_pcm_hw_params *params,
				 snd_pcm_hw_param_t var, अचिन्हित पूर्णांक val,
				 पूर्णांक dir)
अणु
	पूर्णांक changed;
	अगर (hw_is_mask(var)) अणु
		काष्ठा snd_mask *m = hw_param_mask(params, var);
		अगर (val == 0 && dir < 0) अणु
			changed = -EINVAL;
			snd_mask_none(m);
		पूर्ण अन्यथा अणु
			अगर (dir > 0)
				val++;
			अन्यथा अगर (dir < 0)
				val--;
			changed = snd_mask_refine_set(hw_param_mask(params, var), val);
		पूर्ण
	पूर्ण अन्यथा अगर (hw_is_पूर्णांकerval(var)) अणु
		काष्ठा snd_पूर्णांकerval *i = hw_param_पूर्णांकerval(params, var);
		अगर (val == 0 && dir < 0) अणु
			changed = -EINVAL;
			snd_पूर्णांकerval_none(i);
		पूर्ण अन्यथा अगर (dir == 0)
			changed = snd_पूर्णांकerval_refine_set(i, val);
		अन्यथा अणु
			काष्ठा snd_पूर्णांकerval t;
			t.खोलोmin = 1;
			t.खोलोmax = 1;
			t.empty = 0;
			t.पूर्णांकeger = 0;
			अगर (dir < 0) अणु
				t.min = val - 1;
				t.max = val;
			पूर्ण अन्यथा अणु
				t.min = val;
				t.max = val+1;
			पूर्ण
			changed = snd_पूर्णांकerval_refine(i, &t);
		पूर्ण
	पूर्ण अन्यथा
		वापस -EINVAL;
	अगर (changed > 0) अणु
		params->cmask |= 1 << var;
		params->rmask |= 1 << var;
	पूर्ण
	वापस changed;
पूर्ण

/**
 * snd_pcm_hw_param_set
 * @pcm: PCM instance
 * @params: the hw_params instance
 * @var: parameter to retrieve
 * @val: value to set
 * @dir: poपूर्णांकer to the direction (-1,0,1) or शून्य
 *
 * Inside configuration space defined by PARAMS हटाओ from PAR all 
 * values != VAL. Reduce configuration space accordingly.
 *  Return VAL or -EINVAL अगर the configuration space is empty
 */
अटल पूर्णांक snd_pcm_hw_param_set(काष्ठा snd_pcm_substream *pcm,
				काष्ठा snd_pcm_hw_params *params,
				snd_pcm_hw_param_t var, अचिन्हित पूर्णांक val,
				पूर्णांक dir)
अणु
	पूर्णांक changed = _snd_pcm_hw_param_set(params, var, val, dir);
	अगर (changed < 0)
		वापस changed;
	अगर (params->rmask) अणु
		पूर्णांक err = snd_pcm_hw_refine(pcm, params);
		अगर (err < 0)
			वापस err;
	पूर्ण
	वापस snd_pcm_hw_param_value(params, var, शून्य);
पूर्ण

अटल पूर्णांक _snd_pcm_hw_param_setपूर्णांकeger(काष्ठा snd_pcm_hw_params *params,
					snd_pcm_hw_param_t var)
अणु
	पूर्णांक changed;
	changed = snd_पूर्णांकerval_setपूर्णांकeger(hw_param_पूर्णांकerval(params, var));
	अगर (changed > 0) अणु
		params->cmask |= 1 << var;
		params->rmask |= 1 << var;
	पूर्ण
	वापस changed;
पूर्ण
	
/*
 * plugin
 */

#अगर_घोषित CONFIG_SND_PCM_OSS_PLUGINS
अटल पूर्णांक snd_pcm_oss_plugin_clear(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_pcm_plugin *plugin, *next;
	
	plugin = runसमय->oss.plugin_first;
	जबतक (plugin) अणु
		next = plugin->next;
		snd_pcm_plugin_मुक्त(plugin);
		plugin = next;
	पूर्ण
	runसमय->oss.plugin_first = runसमय->oss.plugin_last = शून्य;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_pcm_plugin_insert(काष्ठा snd_pcm_plugin *plugin)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = plugin->plug->runसमय;
	plugin->next = runसमय->oss.plugin_first;
	plugin->prev = शून्य;
	अगर (runसमय->oss.plugin_first) अणु
		runसमय->oss.plugin_first->prev = plugin;
		runसमय->oss.plugin_first = plugin;
	पूर्ण अन्यथा अणु
		runसमय->oss.plugin_last =
		runसमय->oss.plugin_first = plugin;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक snd_pcm_plugin_append(काष्ठा snd_pcm_plugin *plugin)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = plugin->plug->runसमय;
	plugin->next = शून्य;
	plugin->prev = runसमय->oss.plugin_last;
	अगर (runसमय->oss.plugin_last) अणु
		runसमय->oss.plugin_last->next = plugin;
		runसमय->oss.plugin_last = plugin;
	पूर्ण अन्यथा अणु
		runसमय->oss.plugin_last =
		runसमय->oss.plugin_first = plugin;
	पूर्ण
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_SND_PCM_OSS_PLUGINS */

अटल दीर्घ snd_pcm_oss_bytes(काष्ठा snd_pcm_substream *substream, दीर्घ frames)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	दीर्घ buffer_size = snd_pcm_lib_buffer_bytes(substream);
	दीर्घ bytes = frames_to_bytes(runसमय, frames);
	अगर (buffer_size == runसमय->oss.buffer_bytes)
		वापस bytes;
#अगर BITS_PER_LONG >= 64
	वापस runसमय->oss.buffer_bytes * bytes / buffer_size;
#अन्यथा
	अणु
		u64 bsize = (u64)runसमय->oss.buffer_bytes * (u64)bytes;
		वापस भाग_u64(bsize, buffer_size);
	पूर्ण
#पूर्ण_अगर
पूर्ण

अटल दीर्घ snd_pcm_alsa_frames(काष्ठा snd_pcm_substream *substream, दीर्घ bytes)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	दीर्घ buffer_size = snd_pcm_lib_buffer_bytes(substream);
	अगर (buffer_size == runसमय->oss.buffer_bytes)
		वापस bytes_to_frames(runसमय, bytes);
	वापस bytes_to_frames(runसमय, (buffer_size * bytes) / runसमय->oss.buffer_bytes);
पूर्ण

अटल अंतरभूत
snd_pcm_uframes_t get_hw_ptr_period(काष्ठा snd_pcm_runसमय *runसमय)
अणु
	वापस runसमय->hw_ptr_पूर्णांकerrupt;
पूर्ण

/* define extended क्रमmats in the recent OSS versions (अगर any) */
/* linear क्रमmats */
#घोषणा AFMT_S32_LE      0x00001000
#घोषणा AFMT_S32_BE      0x00002000
#घोषणा AFMT_S24_LE      0x00008000
#घोषणा AFMT_S24_BE      0x00010000
#घोषणा AFMT_S24_PACKED  0x00040000

/* other supported क्रमmats */
#घोषणा AFMT_FLOAT       0x00004000
#घोषणा AFMT_SPDIF_RAW   0x00020000

/* unsupported क्रमmats */
#घोषणा AFMT_AC3         0x00000400
#घोषणा AFMT_VORBIS      0x00000800

अटल snd_pcm_क्रमmat_t snd_pcm_oss_क्रमmat_from(पूर्णांक क्रमmat)
अणु
	चयन (क्रमmat) अणु
	हाल AFMT_MU_LAW:	वापस SNDRV_PCM_FORMAT_MU_LAW;
	हाल AFMT_A_LAW:	वापस SNDRV_PCM_FORMAT_A_LAW;
	हाल AFMT_IMA_ADPCM:	वापस SNDRV_PCM_FORMAT_IMA_ADPCM;
	हाल AFMT_U8:		वापस SNDRV_PCM_FORMAT_U8;
	हाल AFMT_S16_LE:	वापस SNDRV_PCM_FORMAT_S16_LE;
	हाल AFMT_S16_BE:	वापस SNDRV_PCM_FORMAT_S16_BE;
	हाल AFMT_S8:		वापस SNDRV_PCM_FORMAT_S8;
	हाल AFMT_U16_LE:	वापस SNDRV_PCM_FORMAT_U16_LE;
	हाल AFMT_U16_BE:	वापस SNDRV_PCM_FORMAT_U16_BE;
	हाल AFMT_MPEG:		वापस SNDRV_PCM_FORMAT_MPEG;
	हाल AFMT_S32_LE:	वापस SNDRV_PCM_FORMAT_S32_LE;
	हाल AFMT_S32_BE:	वापस SNDRV_PCM_FORMAT_S32_BE;
	हाल AFMT_S24_LE:	वापस SNDRV_PCM_FORMAT_S24_LE;
	हाल AFMT_S24_BE:	वापस SNDRV_PCM_FORMAT_S24_BE;
	हाल AFMT_S24_PACKED:	वापस SNDRV_PCM_FORMAT_S24_3LE;
	हाल AFMT_FLOAT:	वापस SNDRV_PCM_FORMAT_FLOAT;
	हाल AFMT_SPDIF_RAW:	वापस SNDRV_PCM_FORMAT_IEC958_SUBFRAME;
	शेष:		वापस SNDRV_PCM_FORMAT_U8;
	पूर्ण
पूर्ण

अटल पूर्णांक snd_pcm_oss_क्रमmat_to(snd_pcm_क्रमmat_t क्रमmat)
अणु
	चयन (क्रमmat) अणु
	हाल SNDRV_PCM_FORMAT_MU_LAW:	वापस AFMT_MU_LAW;
	हाल SNDRV_PCM_FORMAT_A_LAW:	वापस AFMT_A_LAW;
	हाल SNDRV_PCM_FORMAT_IMA_ADPCM:	वापस AFMT_IMA_ADPCM;
	हाल SNDRV_PCM_FORMAT_U8:		वापस AFMT_U8;
	हाल SNDRV_PCM_FORMAT_S16_LE:	वापस AFMT_S16_LE;
	हाल SNDRV_PCM_FORMAT_S16_BE:	वापस AFMT_S16_BE;
	हाल SNDRV_PCM_FORMAT_S8:		वापस AFMT_S8;
	हाल SNDRV_PCM_FORMAT_U16_LE:	वापस AFMT_U16_LE;
	हाल SNDRV_PCM_FORMAT_U16_BE:	वापस AFMT_U16_BE;
	हाल SNDRV_PCM_FORMAT_MPEG:		वापस AFMT_MPEG;
	हाल SNDRV_PCM_FORMAT_S32_LE:	वापस AFMT_S32_LE;
	हाल SNDRV_PCM_FORMAT_S32_BE:	वापस AFMT_S32_BE;
	हाल SNDRV_PCM_FORMAT_S24_LE:	वापस AFMT_S24_LE;
	हाल SNDRV_PCM_FORMAT_S24_BE:	वापस AFMT_S24_BE;
	हाल SNDRV_PCM_FORMAT_S24_3LE:	वापस AFMT_S24_PACKED;
	हाल SNDRV_PCM_FORMAT_FLOAT:	वापस AFMT_FLOAT;
	हाल SNDRV_PCM_FORMAT_IEC958_SUBFRAME: वापस AFMT_SPDIF_RAW;
	शेष:			वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक snd_pcm_oss_period_size(काष्ठा snd_pcm_substream *substream, 
				   काष्ठा snd_pcm_hw_params *oss_params,
				   काष्ठा snd_pcm_hw_params *slave_params)
अणु
	माप_प्रकार s;
	माप_प्रकार oss_buffer_size, oss_period_size, oss_periods;
	माप_प्रकार min_period_size, max_period_size;
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	माप_प्रकार oss_frame_size;

	oss_frame_size = snd_pcm_क्रमmat_physical_width(params_क्रमmat(oss_params)) *
			 params_channels(oss_params) / 8;

	oss_buffer_size = snd_pcm_plug_client_size(substream,
						   snd_pcm_hw_param_value_max(slave_params, SNDRV_PCM_HW_PARAM_BUFFER_SIZE, शून्य)) * oss_frame_size;
	अगर (!oss_buffer_size)
		वापस -EINVAL;
	oss_buffer_size = roundकरोwn_घात_of_two(oss_buffer_size);
	अगर (atomic_पढ़ो(&substream->mmap_count)) अणु
		अगर (oss_buffer_size > runसमय->oss.mmap_bytes)
			oss_buffer_size = runसमय->oss.mmap_bytes;
	पूर्ण

	अगर (substream->oss.setup.period_size > 16)
		oss_period_size = substream->oss.setup.period_size;
	अन्यथा अगर (runसमय->oss.fragshअगरt) अणु
		oss_period_size = 1 << runसमय->oss.fragshअगरt;
		अगर (oss_period_size > oss_buffer_size / 2)
			oss_period_size = oss_buffer_size / 2;
	पूर्ण अन्यथा अणु
		पूर्णांक sd;
		माप_प्रकार bytes_per_sec = params_rate(oss_params) * snd_pcm_क्रमmat_physical_width(params_क्रमmat(oss_params)) * params_channels(oss_params) / 8;

		oss_period_size = oss_buffer_size;
		करो अणु
			oss_period_size /= 2;
		पूर्ण जबतक (oss_period_size > bytes_per_sec);
		अगर (runसमय->oss.subभागision == 0) अणु
			sd = 4;
			अगर (oss_period_size / sd > 4096)
				sd *= 2;
			अगर (oss_period_size / sd < 4096)
				sd = 1;
		पूर्ण अन्यथा
			sd = runसमय->oss.subभागision;
		oss_period_size /= sd;
		अगर (oss_period_size < 16)
			oss_period_size = 16;
	पूर्ण

	min_period_size = snd_pcm_plug_client_size(substream,
						   snd_pcm_hw_param_value_min(slave_params, SNDRV_PCM_HW_PARAM_PERIOD_SIZE, शून्य));
	अगर (min_period_size) अणु
		min_period_size *= oss_frame_size;
		min_period_size = roundup_घात_of_two(min_period_size);
		अगर (oss_period_size < min_period_size)
			oss_period_size = min_period_size;
	पूर्ण

	max_period_size = snd_pcm_plug_client_size(substream,
						   snd_pcm_hw_param_value_max(slave_params, SNDRV_PCM_HW_PARAM_PERIOD_SIZE, शून्य));
	अगर (max_period_size) अणु
		max_period_size *= oss_frame_size;
		max_period_size = roundकरोwn_घात_of_two(max_period_size);
		अगर (oss_period_size > max_period_size)
			oss_period_size = max_period_size;
	पूर्ण

	oss_periods = oss_buffer_size / oss_period_size;

	अगर (substream->oss.setup.periods > 1)
		oss_periods = substream->oss.setup.periods;

	s = snd_pcm_hw_param_value_max(slave_params, SNDRV_PCM_HW_PARAM_PERIODS, शून्य);
	अगर (runसमय->oss.maxfrags && s > runसमय->oss.maxfrags)
		s = runसमय->oss.maxfrags;
	अगर (oss_periods > s)
		oss_periods = s;

	s = snd_pcm_hw_param_value_min(slave_params, SNDRV_PCM_HW_PARAM_PERIODS, शून्य);
	अगर (s < 2)
		s = 2;
	अगर (oss_periods < s)
		oss_periods = s;

	जबतक (oss_period_size * oss_periods > oss_buffer_size)
		oss_period_size /= 2;

	अगर (oss_period_size < 16)
		वापस -EINVAL;
	runसमय->oss.period_bytes = oss_period_size;
	runसमय->oss.period_frames = 1;
	runसमय->oss.periods = oss_periods;
	वापस 0;
पूर्ण

अटल पूर्णांक choose_rate(काष्ठा snd_pcm_substream *substream,
		       काष्ठा snd_pcm_hw_params *params, अचिन्हित पूर्णांक best_rate)
अणु
	स्थिर काष्ठा snd_पूर्णांकerval *it;
	काष्ठा snd_pcm_hw_params *save;
	अचिन्हित पूर्णांक rate, prev;

	save = kदो_स्मृति(माप(*save), GFP_KERNEL);
	अगर (save == शून्य)
		वापस -ENOMEM;
	*save = *params;
	it = hw_param_पूर्णांकerval_c(save, SNDRV_PCM_HW_PARAM_RATE);

	/* try multiples of the best rate */
	rate = best_rate;
	क्रम (;;) अणु
		अगर (it->max < rate || (it->max == rate && it->खोलोmax))
			अवरोध;
		अगर (it->min < rate || (it->min == rate && !it->खोलोmin)) अणु
			पूर्णांक ret;
			ret = snd_pcm_hw_param_set(substream, params,
						   SNDRV_PCM_HW_PARAM_RATE,
						   rate, 0);
			अगर (ret == (पूर्णांक)rate) अणु
				kमुक्त(save);
				वापस rate;
			पूर्ण
			*params = *save;
		पूर्ण
		prev = rate;
		rate += best_rate;
		अगर (rate <= prev)
			अवरोध;
	पूर्ण

	/* not found, use the nearest rate */
	kमुक्त(save);
	वापस snd_pcm_hw_param_near(substream, params, SNDRV_PCM_HW_PARAM_RATE, best_rate, शून्य);
पूर्ण

/* parameter locking: वापसs immediately अगर tried during streaming */
अटल पूर्णांक lock_params(काष्ठा snd_pcm_runसमय *runसमय)
अणु
	अगर (mutex_lock_पूर्णांकerruptible(&runसमय->oss.params_lock))
		वापस -ERESTARTSYS;
	अगर (atomic_पढ़ो(&runसमय->oss.rw_ref)) अणु
		mutex_unlock(&runसमय->oss.params_lock);
		वापस -EBUSY;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम unlock_params(काष्ठा snd_pcm_runसमय *runसमय)
अणु
	mutex_unlock(&runसमय->oss.params_lock);
पूर्ण

/* call with params_lock held */
अटल पूर्णांक snd_pcm_oss_change_params_locked(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_pcm_hw_params *params, *sparams;
	काष्ठा snd_pcm_sw_params *sw_params;
	sमाप_प्रकार oss_buffer_size, oss_period_size;
	माप_प्रकार oss_frame_size;
	पूर्णांक err;
	पूर्णांक direct;
	snd_pcm_क्रमmat_t क्रमmat, sक्रमmat;
	पूर्णांक n;
	स्थिर काष्ठा snd_mask *sक्रमmat_mask;
	काष्ठा snd_mask mask;

	अगर (!runसमय->oss.params)
		वापस 0;
	sw_params = kzalloc(माप(*sw_params), GFP_KERNEL);
	params = kदो_स्मृति(माप(*params), GFP_KERNEL);
	sparams = kदो_स्मृति(माप(*sparams), GFP_KERNEL);
	अगर (!sw_params || !params || !sparams) अणु
		err = -ENOMEM;
		जाओ failure;
	पूर्ण

	अगर (atomic_पढ़ो(&substream->mmap_count))
		direct = 1;
	अन्यथा
		direct = substream->oss.setup.direct;

	_snd_pcm_hw_params_any(sparams);
	_snd_pcm_hw_param_setपूर्णांकeger(sparams, SNDRV_PCM_HW_PARAM_PERIODS);
	_snd_pcm_hw_param_min(sparams, SNDRV_PCM_HW_PARAM_PERIODS, 2, 0);
	snd_mask_none(&mask);
	अगर (atomic_पढ़ो(&substream->mmap_count))
		snd_mask_set(&mask, (__क्रमce पूर्णांक)SNDRV_PCM_ACCESS_MMAP_INTERLEAVED);
	अन्यथा अणु
		snd_mask_set(&mask, (__क्रमce पूर्णांक)SNDRV_PCM_ACCESS_RW_INTERLEAVED);
		अगर (!direct)
			snd_mask_set(&mask, (__क्रमce पूर्णांक)SNDRV_PCM_ACCESS_RW_NONINTERLEAVED);
	पूर्ण
	err = snd_pcm_hw_param_mask(substream, sparams, SNDRV_PCM_HW_PARAM_ACCESS, &mask);
	अगर (err < 0) अणु
		pcm_dbg(substream->pcm, "No usable accesses\n");
		err = -EINVAL;
		जाओ failure;
	पूर्ण
	choose_rate(substream, sparams, runसमय->oss.rate);
	snd_pcm_hw_param_near(substream, sparams, SNDRV_PCM_HW_PARAM_CHANNELS, runसमय->oss.channels, शून्य);

	क्रमmat = snd_pcm_oss_क्रमmat_from(runसमय->oss.क्रमmat);

	sक्रमmat_mask = hw_param_mask_c(sparams, SNDRV_PCM_HW_PARAM_FORMAT);
	अगर (direct)
		sक्रमmat = क्रमmat;
	अन्यथा
		sक्रमmat = snd_pcm_plug_slave_क्रमmat(क्रमmat, sक्रमmat_mask);

	अगर ((__क्रमce पूर्णांक)sक्रमmat < 0 ||
	    !snd_mask_test_क्रमmat(sक्रमmat_mask, sक्रमmat)) अणु
		pcm_क्रम_each_क्रमmat(sक्रमmat) अणु
			अगर (snd_mask_test_क्रमmat(sक्रमmat_mask, sक्रमmat) &&
			    snd_pcm_oss_क्रमmat_to(sक्रमmat) >= 0)
				जाओ क्रमmat_found;
		पूर्ण
		pcm_dbg(substream->pcm, "Cannot find a format!!!\n");
		err = -EINVAL;
		जाओ failure;
	पूर्ण
 क्रमmat_found:
	err = _snd_pcm_hw_param_set(sparams, SNDRV_PCM_HW_PARAM_FORMAT, (__क्रमce पूर्णांक)sक्रमmat, 0);
	अगर (err < 0)
		जाओ failure;

	अगर (direct) अणु
		स_नकल(params, sparams, माप(*params));
	पूर्ण अन्यथा अणु
		_snd_pcm_hw_params_any(params);
		_snd_pcm_hw_param_set(params, SNDRV_PCM_HW_PARAM_ACCESS,
				      (__क्रमce पूर्णांक)SNDRV_PCM_ACCESS_RW_INTERLEAVED, 0);
		_snd_pcm_hw_param_set(params, SNDRV_PCM_HW_PARAM_FORMAT,
				      (__क्रमce पूर्णांक)snd_pcm_oss_क्रमmat_from(runसमय->oss.क्रमmat), 0);
		_snd_pcm_hw_param_set(params, SNDRV_PCM_HW_PARAM_CHANNELS,
				      runसमय->oss.channels, 0);
		_snd_pcm_hw_param_set(params, SNDRV_PCM_HW_PARAM_RATE,
				      runसमय->oss.rate, 0);
		pdम_लिखो("client: access = %i, format = %i, channels = %i, rate = %i\n",
			 params_access(params), params_क्रमmat(params),
			 params_channels(params), params_rate(params));
	पूर्ण
	pdम_लिखो("slave: access = %i, format = %i, channels = %i, rate = %i\n",
		 params_access(sparams), params_क्रमmat(sparams),
		 params_channels(sparams), params_rate(sparams));

	oss_frame_size = snd_pcm_क्रमmat_physical_width(params_क्रमmat(params)) *
			 params_channels(params) / 8;

	err = snd_pcm_oss_period_size(substream, params, sparams);
	अगर (err < 0)
		जाओ failure;

	n = snd_pcm_plug_slave_size(substream, runसमय->oss.period_bytes / oss_frame_size);
	err = snd_pcm_hw_param_near(substream, sparams, SNDRV_PCM_HW_PARAM_PERIOD_SIZE, n, शून्य);
	अगर (err < 0)
		जाओ failure;

	err = snd_pcm_hw_param_near(substream, sparams, SNDRV_PCM_HW_PARAM_PERIODS,
				     runसमय->oss.periods, शून्य);
	अगर (err < 0)
		जाओ failure;

	snd_pcm_kernel_ioctl(substream, SNDRV_PCM_IOCTL_DROP, शून्य);

	err = snd_pcm_kernel_ioctl(substream, SNDRV_PCM_IOCTL_HW_PARAMS, sparams);
	अगर (err < 0) अणु
		pcm_dbg(substream->pcm, "HW_PARAMS failed: %i\n", err);
		जाओ failure;
	पूर्ण

#अगर_घोषित CONFIG_SND_PCM_OSS_PLUGINS
	snd_pcm_oss_plugin_clear(substream);
	अगर (!direct) अणु
		/* add necessary plugins */
		snd_pcm_oss_plugin_clear(substream);
		अगर ((err = snd_pcm_plug_क्रमmat_plugins(substream,
						       params, 
						       sparams)) < 0) अणु
			pcm_dbg(substream->pcm,
				"snd_pcm_plug_format_plugins failed: %i\n", err);
			snd_pcm_oss_plugin_clear(substream);
			जाओ failure;
		पूर्ण
		अगर (runसमय->oss.plugin_first) अणु
			काष्ठा snd_pcm_plugin *plugin;
			अगर ((err = snd_pcm_plugin_build_io(substream, sparams, &plugin)) < 0) अणु
				pcm_dbg(substream->pcm,
					"snd_pcm_plugin_build_io failed: %i\n", err);
				snd_pcm_oss_plugin_clear(substream);
				जाओ failure;
			पूर्ण
			अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
				err = snd_pcm_plugin_append(plugin);
			पूर्ण अन्यथा अणु
				err = snd_pcm_plugin_insert(plugin);
			पूर्ण
			अगर (err < 0) अणु
				snd_pcm_oss_plugin_clear(substream);
				जाओ failure;
			पूर्ण
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	अगर (runसमय->oss.trigger) अणु
		sw_params->start_threshold = 1;
	पूर्ण अन्यथा अणु
		sw_params->start_threshold = runसमय->boundary;
	पूर्ण
	अगर (atomic_पढ़ो(&substream->mmap_count) ||
	    substream->stream == SNDRV_PCM_STREAM_CAPTURE)
		sw_params->stop_threshold = runसमय->boundary;
	अन्यथा
		sw_params->stop_threshold = runसमय->buffer_size;
	sw_params->tstamp_mode = SNDRV_PCM_TSTAMP_NONE;
	sw_params->period_step = 1;
	sw_params->avail_min = substream->stream == SNDRV_PCM_STREAM_PLAYBACK ?
		1 : runसमय->period_size;
	अगर (atomic_पढ़ो(&substream->mmap_count) ||
	    substream->oss.setup.nosilence) अणु
		sw_params->silence_threshold = 0;
		sw_params->silence_size = 0;
	पूर्ण अन्यथा अणु
		snd_pcm_uframes_t frames;
		frames = runसमय->period_size + 16;
		अगर (frames > runसमय->buffer_size)
			frames = runसमय->buffer_size;
		sw_params->silence_threshold = frames;
		sw_params->silence_size = frames;
	पूर्ण

	अगर ((err = snd_pcm_kernel_ioctl(substream, SNDRV_PCM_IOCTL_SW_PARAMS, sw_params)) < 0) अणु
		pcm_dbg(substream->pcm, "SW_PARAMS failed: %i\n", err);
		जाओ failure;
	पूर्ण

	runसमय->oss.periods = params_periods(sparams);
	oss_period_size = snd_pcm_plug_client_size(substream, params_period_size(sparams));
	अगर (oss_period_size < 0) अणु
		err = -EINVAL;
		जाओ failure;
	पूर्ण
#अगर_घोषित CONFIG_SND_PCM_OSS_PLUGINS
	अगर (runसमय->oss.plugin_first) अणु
		err = snd_pcm_plug_alloc(substream, oss_period_size);
		अगर (err < 0)
			जाओ failure;
	पूर्ण
#पूर्ण_अगर
	oss_period_size *= oss_frame_size;

	oss_buffer_size = oss_period_size * runसमय->oss.periods;
	अगर (oss_buffer_size < 0) अणु
		err = -EINVAL;
		जाओ failure;
	पूर्ण

	runसमय->oss.period_bytes = oss_period_size;
	runसमय->oss.buffer_bytes = oss_buffer_size;

	pdम_लिखो("oss: period bytes = %i, buffer bytes = %i\n",
		 runसमय->oss.period_bytes,
		 runसमय->oss.buffer_bytes);
	pdम_लिखो("slave: period_size = %i, buffer_size = %i\n",
		 params_period_size(sparams),
		 params_buffer_size(sparams));

	runसमय->oss.क्रमmat = snd_pcm_oss_क्रमmat_to(params_क्रमmat(params));
	runसमय->oss.channels = params_channels(params);
	runसमय->oss.rate = params_rate(params);

	kvमुक्त(runसमय->oss.buffer);
	runसमय->oss.buffer = kvzalloc(runसमय->oss.period_bytes, GFP_KERNEL);
	अगर (!runसमय->oss.buffer) अणु
		err = -ENOMEM;
		जाओ failure;
	पूर्ण

	runसमय->oss.params = 0;
	runसमय->oss.prepare = 1;
	runसमय->oss.buffer_used = 0;
	अगर (runसमय->dma_area)
		snd_pcm_क्रमmat_set_silence(runसमय->क्रमmat, runसमय->dma_area, bytes_to_samples(runसमय, runसमय->dma_bytes));

	runसमय->oss.period_frames = snd_pcm_alsa_frames(substream, oss_period_size);

	err = 0;
failure:
	kमुक्त(sw_params);
	kमुक्त(params);
	kमुक्त(sparams);
	वापस err;
पूर्ण

/* this one takes the lock by itself */
अटल पूर्णांक snd_pcm_oss_change_params(काष्ठा snd_pcm_substream *substream,
				     bool trylock)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	पूर्णांक err;

	अगर (trylock) अणु
		अगर (!(mutex_trylock(&runसमय->oss.params_lock)))
			वापस -EAGAIN;
	पूर्ण अन्यथा अगर (mutex_lock_पूर्णांकerruptible(&runसमय->oss.params_lock))
		वापस -ERESTARTSYS;

	err = snd_pcm_oss_change_params_locked(substream);
	mutex_unlock(&runसमय->oss.params_lock);
	वापस err;
पूर्ण

अटल पूर्णांक snd_pcm_oss_get_active_substream(काष्ठा snd_pcm_oss_file *pcm_oss_file, काष्ठा snd_pcm_substream **r_substream)
अणु
	पूर्णांक idx, err;
	काष्ठा snd_pcm_substream *asubstream = शून्य, *substream;

	क्रम (idx = 0; idx < 2; idx++) अणु
		substream = pcm_oss_file->streams[idx];
		अगर (substream == शून्य)
			जारी;
		अगर (asubstream == शून्य)
			asubstream = substream;
		अगर (substream->runसमय->oss.params) अणु
			err = snd_pcm_oss_change_params(substream, false);
			अगर (err < 0)
				वापस err;
		पूर्ण
	पूर्ण
	अगर (!asubstream)
		वापस -EIO;
	अगर (r_substream)
		*r_substream = asubstream;
	वापस 0;
पूर्ण

/* call with params_lock held */
/* NOTE: this always call PREPARE unconditionally no matter whether
 * runसमय->oss.prepare is set or not
 */
अटल पूर्णांक snd_pcm_oss_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	पूर्णांक err;
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;

	err = snd_pcm_kernel_ioctl(substream, SNDRV_PCM_IOCTL_PREPARE, शून्य);
	अगर (err < 0) अणु
		pcm_dbg(substream->pcm,
			"snd_pcm_oss_prepare: SNDRV_PCM_IOCTL_PREPARE failed\n");
		वापस err;
	पूर्ण
	runसमय->oss.prepare = 0;
	runसमय->oss.prev_hw_ptr_period = 0;
	runसमय->oss.period_ptr = 0;
	runसमय->oss.buffer_used = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक snd_pcm_oss_make_पढ़ोy(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय;
	पूर्णांक err;

	runसमय = substream->runसमय;
	अगर (runसमय->oss.params) अणु
		err = snd_pcm_oss_change_params(substream, false);
		अगर (err < 0)
			वापस err;
	पूर्ण
	अगर (runसमय->oss.prepare) अणु
		अगर (mutex_lock_पूर्णांकerruptible(&runसमय->oss.params_lock))
			वापस -ERESTARTSYS;
		err = snd_pcm_oss_prepare(substream);
		mutex_unlock(&runसमय->oss.params_lock);
		अगर (err < 0)
			वापस err;
	पूर्ण
	वापस 0;
पूर्ण

/* call with params_lock held */
अटल पूर्णांक snd_pcm_oss_make_पढ़ोy_locked(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय;
	पूर्णांक err;

	runसमय = substream->runसमय;
	अगर (runसमय->oss.params) अणु
		err = snd_pcm_oss_change_params_locked(substream);
		अगर (err < 0)
			वापस err;
	पूर्ण
	अगर (runसमय->oss.prepare) अणु
		err = snd_pcm_oss_prepare(substream);
		अगर (err < 0)
			वापस err;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक snd_pcm_oss_capture_position_fixup(काष्ठा snd_pcm_substream *substream, snd_pcm_sframes_t *delay)
अणु
	काष्ठा snd_pcm_runसमय *runसमय;
	snd_pcm_uframes_t frames;
	पूर्णांक err = 0;

	जबतक (1) अणु
		err = snd_pcm_kernel_ioctl(substream, SNDRV_PCM_IOCTL_DELAY, delay);
		अगर (err < 0)
			अवरोध;
		runसमय = substream->runसमय;
		अगर (*delay <= (snd_pcm_sframes_t)runसमय->buffer_size)
			अवरोध;
		/* in हाल of overrun, skip whole periods like OSS/Linux driver करोes */
		/* until avail(delay) <= buffer_size */
		frames = (*delay - runसमय->buffer_size) + runसमय->period_size - 1;
		frames /= runसमय->period_size;
		frames *= runसमय->period_size;
		err = snd_pcm_kernel_ioctl(substream, SNDRV_PCM_IOCTL_FORWARD, &frames);
		अगर (err < 0)
			अवरोध;
	पूर्ण
	वापस err;
पूर्ण

snd_pcm_sframes_t snd_pcm_oss_ग_लिखो3(काष्ठा snd_pcm_substream *substream, स्थिर अक्षर *ptr, snd_pcm_uframes_t frames, पूर्णांक in_kernel)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	पूर्णांक ret;
	जबतक (1) अणु
		अगर (runसमय->status->state == SNDRV_PCM_STATE_XRUN ||
		    runसमय->status->state == SNDRV_PCM_STATE_SUSPENDED) अणु
#अगर_घोषित OSS_DEBUG
			pcm_dbg(substream->pcm,
				"pcm_oss: write: recovering from %s\n",
				runसमय->status->state == SNDRV_PCM_STATE_XRUN ?
				"XRUN" : "SUSPEND");
#पूर्ण_अगर
			ret = snd_pcm_oss_prepare(substream);
			अगर (ret < 0)
				अवरोध;
		पूर्ण
		mutex_unlock(&runसमय->oss.params_lock);
		ret = __snd_pcm_lib_xfer(substream, (व्योम *)ptr, true,
					 frames, in_kernel);
		mutex_lock(&runसमय->oss.params_lock);
		अगर (ret != -EPIPE && ret != -ESTRPIPE)
			अवरोध;
		/* test, अगर we can't store new data, because the stream */
		/* has not been started */
		अगर (runसमय->status->state == SNDRV_PCM_STATE_PREPARED)
			वापस -EAGAIN;
	पूर्ण
	वापस ret;
पूर्ण

snd_pcm_sframes_t snd_pcm_oss_पढ़ो3(काष्ठा snd_pcm_substream *substream, अक्षर *ptr, snd_pcm_uframes_t frames, पूर्णांक in_kernel)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	snd_pcm_sframes_t delay;
	पूर्णांक ret;
	जबतक (1) अणु
		अगर (runसमय->status->state == SNDRV_PCM_STATE_XRUN ||
		    runसमय->status->state == SNDRV_PCM_STATE_SUSPENDED) अणु
#अगर_घोषित OSS_DEBUG
			pcm_dbg(substream->pcm,
				"pcm_oss: read: recovering from %s\n",
				runसमय->status->state == SNDRV_PCM_STATE_XRUN ?
				"XRUN" : "SUSPEND");
#पूर्ण_अगर
			ret = snd_pcm_kernel_ioctl(substream, SNDRV_PCM_IOCTL_DRAIN, शून्य);
			अगर (ret < 0)
				अवरोध;
		पूर्ण अन्यथा अगर (runसमय->status->state == SNDRV_PCM_STATE_SETUP) अणु
			ret = snd_pcm_oss_prepare(substream);
			अगर (ret < 0)
				अवरोध;
		पूर्ण
		ret = snd_pcm_oss_capture_position_fixup(substream, &delay);
		अगर (ret < 0)
			अवरोध;
		mutex_unlock(&runसमय->oss.params_lock);
		ret = __snd_pcm_lib_xfer(substream, (व्योम *)ptr, true,
					 frames, in_kernel);
		mutex_lock(&runसमय->oss.params_lock);
		अगर (ret == -EPIPE) अणु
			अगर (runसमय->status->state == SNDRV_PCM_STATE_DRAINING) अणु
				ret = snd_pcm_kernel_ioctl(substream, SNDRV_PCM_IOCTL_DROP, शून्य);
				अगर (ret < 0)
					अवरोध;
			पूर्ण
			जारी;
		पूर्ण
		अगर (ret != -ESTRPIPE)
			अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_SND_PCM_OSS_PLUGINS
snd_pcm_sframes_t snd_pcm_oss_ग_लिखोv3(काष्ठा snd_pcm_substream *substream, व्योम **bufs, snd_pcm_uframes_t frames)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	पूर्णांक ret;
	जबतक (1) अणु
		अगर (runसमय->status->state == SNDRV_PCM_STATE_XRUN ||
		    runसमय->status->state == SNDRV_PCM_STATE_SUSPENDED) अणु
#अगर_घोषित OSS_DEBUG
			pcm_dbg(substream->pcm,
				"pcm_oss: writev: recovering from %s\n",
				runसमय->status->state == SNDRV_PCM_STATE_XRUN ?
				"XRUN" : "SUSPEND");
#पूर्ण_अगर
			ret = snd_pcm_oss_prepare(substream);
			अगर (ret < 0)
				अवरोध;
		पूर्ण
		ret = snd_pcm_kernel_ग_लिखोv(substream, bufs, frames);
		अगर (ret != -EPIPE && ret != -ESTRPIPE)
			अवरोध;

		/* test, अगर we can't store new data, because the stream */
		/* has not been started */
		अगर (runसमय->status->state == SNDRV_PCM_STATE_PREPARED)
			वापस -EAGAIN;
	पूर्ण
	वापस ret;
पूर्ण
	
snd_pcm_sframes_t snd_pcm_oss_पढ़ोv3(काष्ठा snd_pcm_substream *substream, व्योम **bufs, snd_pcm_uframes_t frames)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	पूर्णांक ret;
	जबतक (1) अणु
		अगर (runसमय->status->state == SNDRV_PCM_STATE_XRUN ||
		    runसमय->status->state == SNDRV_PCM_STATE_SUSPENDED) अणु
#अगर_घोषित OSS_DEBUG
			pcm_dbg(substream->pcm,
				"pcm_oss: readv: recovering from %s\n",
				runसमय->status->state == SNDRV_PCM_STATE_XRUN ?
				"XRUN" : "SUSPEND");
#पूर्ण_अगर
			ret = snd_pcm_kernel_ioctl(substream, SNDRV_PCM_IOCTL_DRAIN, शून्य);
			अगर (ret < 0)
				अवरोध;
		पूर्ण अन्यथा अगर (runसमय->status->state == SNDRV_PCM_STATE_SETUP) अणु
			ret = snd_pcm_oss_prepare(substream);
			अगर (ret < 0)
				अवरोध;
		पूर्ण
		ret = snd_pcm_kernel_पढ़ोv(substream, bufs, frames);
		अगर (ret != -EPIPE && ret != -ESTRPIPE)
			अवरोध;
	पूर्ण
	वापस ret;
पूर्ण
#पूर्ण_अगर /* CONFIG_SND_PCM_OSS_PLUGINS */

अटल sमाप_प्रकार snd_pcm_oss_ग_लिखो2(काष्ठा snd_pcm_substream *substream, स्थिर अक्षर *buf, माप_प्रकार bytes, पूर्णांक in_kernel)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	snd_pcm_sframes_t frames, frames1;
#अगर_घोषित CONFIG_SND_PCM_OSS_PLUGINS
	अगर (runसमय->oss.plugin_first) अणु
		काष्ठा snd_pcm_plugin_channel *channels;
		माप_प्रकार oss_frame_bytes = (runसमय->oss.plugin_first->src_width * runसमय->oss.plugin_first->src_क्रमmat.channels) / 8;
		अगर (!in_kernel) अणु
			अगर (copy_from_user(runसमय->oss.buffer, (स्थिर अक्षर __क्रमce __user *)buf, bytes))
				वापस -EFAULT;
			buf = runसमय->oss.buffer;
		पूर्ण
		frames = bytes / oss_frame_bytes;
		frames1 = snd_pcm_plug_client_channels_buf(substream, (अक्षर *)buf, frames, &channels);
		अगर (frames1 < 0)
			वापस frames1;
		frames1 = snd_pcm_plug_ग_लिखो_transfer(substream, channels, frames1);
		अगर (frames1 <= 0)
			वापस frames1;
		bytes = frames1 * oss_frame_bytes;
	पूर्ण अन्यथा
#पूर्ण_अगर
	अणु
		frames = bytes_to_frames(runसमय, bytes);
		frames1 = snd_pcm_oss_ग_लिखो3(substream, buf, frames, in_kernel);
		अगर (frames1 <= 0)
			वापस frames1;
		bytes = frames_to_bytes(runसमय, frames1);
	पूर्ण
	वापस bytes;
पूर्ण

अटल sमाप_प्रकार snd_pcm_oss_ग_लिखो1(काष्ठा snd_pcm_substream *substream, स्थिर अक्षर __user *buf, माप_प्रकार bytes)
अणु
	माप_प्रकार xfer = 0;
	sमाप_प्रकार पंचांगp = 0;
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;

	अगर (atomic_पढ़ो(&substream->mmap_count))
		वापस -ENXIO;

	atomic_inc(&runसमय->oss.rw_ref);
	जबतक (bytes > 0) अणु
		अगर (mutex_lock_पूर्णांकerruptible(&runसमय->oss.params_lock)) अणु
			पंचांगp = -ERESTARTSYS;
			अवरोध;
		पूर्ण
		पंचांगp = snd_pcm_oss_make_पढ़ोy_locked(substream);
		अगर (पंचांगp < 0)
			जाओ err;
		अगर (bytes < runसमय->oss.period_bytes || runसमय->oss.buffer_used > 0) अणु
			पंचांगp = bytes;
			अगर (पंचांगp + runसमय->oss.buffer_used > runसमय->oss.period_bytes)
				पंचांगp = runसमय->oss.period_bytes - runसमय->oss.buffer_used;
			अगर (पंचांगp > 0) अणु
				अगर (copy_from_user(runसमय->oss.buffer + runसमय->oss.buffer_used, buf, पंचांगp)) अणु
					पंचांगp = -EFAULT;
					जाओ err;
				पूर्ण
			पूर्ण
			runसमय->oss.buffer_used += पंचांगp;
			buf += पंचांगp;
			bytes -= पंचांगp;
			xfer += पंचांगp;
			अगर (substream->oss.setup.partialfrag ||
			    runसमय->oss.buffer_used == runसमय->oss.period_bytes) अणु
				पंचांगp = snd_pcm_oss_ग_लिखो2(substream, runसमय->oss.buffer + runसमय->oss.period_ptr, 
							 runसमय->oss.buffer_used - runसमय->oss.period_ptr, 1);
				अगर (पंचांगp <= 0)
					जाओ err;
				runसमय->oss.bytes += पंचांगp;
				runसमय->oss.period_ptr += पंचांगp;
				runसमय->oss.period_ptr %= runसमय->oss.period_bytes;
				अगर (runसमय->oss.period_ptr == 0 ||
				    runसमय->oss.period_ptr == runसमय->oss.buffer_used)
					runसमय->oss.buffer_used = 0;
				अन्यथा अगर ((substream->f_flags & O_NONBLOCK) != 0) अणु
					पंचांगp = -EAGAIN;
					जाओ err;
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अणु
			पंचांगp = snd_pcm_oss_ग_लिखो2(substream,
						 (स्थिर अक्षर __क्रमce *)buf,
						 runसमय->oss.period_bytes, 0);
			अगर (पंचांगp <= 0)
				जाओ err;
			runसमय->oss.bytes += पंचांगp;
			buf += पंचांगp;
			bytes -= पंचांगp;
			xfer += पंचांगp;
			अगर ((substream->f_flags & O_NONBLOCK) != 0 &&
			    पंचांगp != runसमय->oss.period_bytes)
				पंचांगp = -EAGAIN;
		पूर्ण
 err:
		mutex_unlock(&runसमय->oss.params_lock);
		अगर (पंचांगp < 0)
			अवरोध;
		अगर (संकेत_pending(current)) अणु
			पंचांगp = -ERESTARTSYS;
			अवरोध;
		पूर्ण
		पंचांगp = 0;
	पूर्ण
	atomic_dec(&runसमय->oss.rw_ref);
	वापस xfer > 0 ? (snd_pcm_sframes_t)xfer : पंचांगp;
पूर्ण

अटल sमाप_प्रकार snd_pcm_oss_पढ़ो2(काष्ठा snd_pcm_substream *substream, अक्षर *buf, माप_प्रकार bytes, पूर्णांक in_kernel)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	snd_pcm_sframes_t frames, frames1;
#अगर_घोषित CONFIG_SND_PCM_OSS_PLUGINS
	अक्षर __user *final_dst = (अक्षर __क्रमce __user *)buf;
	अगर (runसमय->oss.plugin_first) अणु
		काष्ठा snd_pcm_plugin_channel *channels;
		माप_प्रकार oss_frame_bytes = (runसमय->oss.plugin_last->dst_width * runसमय->oss.plugin_last->dst_क्रमmat.channels) / 8;
		अगर (!in_kernel)
			buf = runसमय->oss.buffer;
		frames = bytes / oss_frame_bytes;
		frames1 = snd_pcm_plug_client_channels_buf(substream, buf, frames, &channels);
		अगर (frames1 < 0)
			वापस frames1;
		frames1 = snd_pcm_plug_पढ़ो_transfer(substream, channels, frames1);
		अगर (frames1 <= 0)
			वापस frames1;
		bytes = frames1 * oss_frame_bytes;
		अगर (!in_kernel && copy_to_user(final_dst, buf, bytes))
			वापस -EFAULT;
	पूर्ण अन्यथा
#पूर्ण_अगर
	अणु
		frames = bytes_to_frames(runसमय, bytes);
		frames1 = snd_pcm_oss_पढ़ो3(substream, buf, frames, in_kernel);
		अगर (frames1 <= 0)
			वापस frames1;
		bytes = frames_to_bytes(runसमय, frames1);
	पूर्ण
	वापस bytes;
पूर्ण

अटल sमाप_प्रकार snd_pcm_oss_पढ़ो1(काष्ठा snd_pcm_substream *substream, अक्षर __user *buf, माप_प्रकार bytes)
अणु
	माप_प्रकार xfer = 0;
	sमाप_प्रकार पंचांगp = 0;
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;

	अगर (atomic_पढ़ो(&substream->mmap_count))
		वापस -ENXIO;

	atomic_inc(&runसमय->oss.rw_ref);
	जबतक (bytes > 0) अणु
		अगर (mutex_lock_पूर्णांकerruptible(&runसमय->oss.params_lock)) अणु
			पंचांगp = -ERESTARTSYS;
			अवरोध;
		पूर्ण
		पंचांगp = snd_pcm_oss_make_पढ़ोy_locked(substream);
		अगर (पंचांगp < 0)
			जाओ err;
		अगर (bytes < runसमय->oss.period_bytes || runसमय->oss.buffer_used > 0) अणु
			अगर (runसमय->oss.buffer_used == 0) अणु
				पंचांगp = snd_pcm_oss_पढ़ो2(substream, runसमय->oss.buffer, runसमय->oss.period_bytes, 1);
				अगर (पंचांगp <= 0)
					जाओ err;
				runसमय->oss.bytes += पंचांगp;
				runसमय->oss.period_ptr = पंचांगp;
				runसमय->oss.buffer_used = पंचांगp;
			पूर्ण
			पंचांगp = bytes;
			अगर ((माप_प्रकार) पंचांगp > runसमय->oss.buffer_used)
				पंचांगp = runसमय->oss.buffer_used;
			अगर (copy_to_user(buf, runसमय->oss.buffer + (runसमय->oss.period_ptr - runसमय->oss.buffer_used), पंचांगp)) अणु
				पंचांगp = -EFAULT;
				जाओ err;
			पूर्ण
			buf += पंचांगp;
			bytes -= पंचांगp;
			xfer += पंचांगp;
			runसमय->oss.buffer_used -= पंचांगp;
		पूर्ण अन्यथा अणु
			पंचांगp = snd_pcm_oss_पढ़ो2(substream, (अक्षर __क्रमce *)buf,
						runसमय->oss.period_bytes, 0);
			अगर (पंचांगp <= 0)
				जाओ err;
			runसमय->oss.bytes += पंचांगp;
			buf += पंचांगp;
			bytes -= पंचांगp;
			xfer += पंचांगp;
		पूर्ण
 err:
		mutex_unlock(&runसमय->oss.params_lock);
		अगर (पंचांगp < 0)
			अवरोध;
		अगर (संकेत_pending(current)) अणु
			पंचांगp = -ERESTARTSYS;
			अवरोध;
		पूर्ण
		पंचांगp = 0;
	पूर्ण
	atomic_dec(&runसमय->oss.rw_ref);
	वापस xfer > 0 ? (snd_pcm_sframes_t)xfer : पंचांगp;
पूर्ण

अटल पूर्णांक snd_pcm_oss_reset(काष्ठा snd_pcm_oss_file *pcm_oss_file)
अणु
	काष्ठा snd_pcm_substream *substream;
	काष्ठा snd_pcm_runसमय *runसमय;
	पूर्णांक i;

	क्रम (i = 0; i < 2; i++) अणु 
		substream = pcm_oss_file->streams[i];
		अगर (!substream)
			जारी;
		runसमय = substream->runसमय;
		snd_pcm_kernel_ioctl(substream, SNDRV_PCM_IOCTL_DROP, शून्य);
		mutex_lock(&runसमय->oss.params_lock);
		runसमय->oss.prepare = 1;
		runसमय->oss.buffer_used = 0;
		runसमय->oss.prev_hw_ptr_period = 0;
		runसमय->oss.period_ptr = 0;
		mutex_unlock(&runसमय->oss.params_lock);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक snd_pcm_oss_post(काष्ठा snd_pcm_oss_file *pcm_oss_file)
अणु
	काष्ठा snd_pcm_substream *substream;
	पूर्णांक err;

	substream = pcm_oss_file->streams[SNDRV_PCM_STREAM_PLAYBACK];
	अगर (substream != शून्य) अणु
		अगर ((err = snd_pcm_oss_make_पढ़ोy(substream)) < 0)
			वापस err;
		snd_pcm_kernel_ioctl(substream, SNDRV_PCM_IOCTL_START, शून्य);
	पूर्ण
	/* note: all errors from the start action are ignored */
	/* OSS apps करो not know, how to handle them */
	वापस 0;
पूर्ण

अटल पूर्णांक snd_pcm_oss_sync1(काष्ठा snd_pcm_substream *substream, माप_प्रकार size)
अणु
	काष्ठा snd_pcm_runसमय *runसमय;
	sमाप_प्रकार result = 0;
	snd_pcm_state_t state;
	दीर्घ res;
	रुको_queue_entry_t रुको;

	runसमय = substream->runसमय;
	init_रुकोqueue_entry(&रुको, current);
	add_रुको_queue(&runसमय->sleep, &रुको);
#अगर_घोषित OSS_DEBUG
	pcm_dbg(substream->pcm, "sync1: size = %li\n", size);
#पूर्ण_अगर
	जबतक (1) अणु
		result = snd_pcm_oss_ग_लिखो2(substream, runसमय->oss.buffer, size, 1);
		अगर (result > 0) अणु
			runसमय->oss.buffer_used = 0;
			result = 0;
			अवरोध;
		पूर्ण
		अगर (result != 0 && result != -EAGAIN)
			अवरोध;
		result = 0;
		set_current_state(TASK_INTERRUPTIBLE);
		snd_pcm_stream_lock_irq(substream);
		state = runसमय->status->state;
		snd_pcm_stream_unlock_irq(substream);
		अगर (state != SNDRV_PCM_STATE_RUNNING) अणु
			set_current_state(TASK_RUNNING);
			अवरोध;
		पूर्ण
		res = schedule_समयout(10 * HZ);
		अगर (संकेत_pending(current)) अणु
			result = -ERESTARTSYS;
			अवरोध;
		पूर्ण
		अगर (res == 0) अणु
			pcm_err(substream->pcm,
				"OSS sync error - DMA timeout\n");
			result = -EIO;
			अवरोध;
		पूर्ण
	पूर्ण
	हटाओ_रुको_queue(&runसमय->sleep, &रुको);
	वापस result;
पूर्ण

अटल पूर्णांक snd_pcm_oss_sync(काष्ठा snd_pcm_oss_file *pcm_oss_file)
अणु
	पूर्णांक err = 0;
	अचिन्हित पूर्णांक saved_f_flags;
	काष्ठा snd_pcm_substream *substream;
	काष्ठा snd_pcm_runसमय *runसमय;
	snd_pcm_क्रमmat_t क्रमmat;
	अचिन्हित दीर्घ width;
	माप_प्रकार size;

	substream = pcm_oss_file->streams[SNDRV_PCM_STREAM_PLAYBACK];
	अगर (substream != शून्य) अणु
		runसमय = substream->runसमय;
		अगर (atomic_पढ़ो(&substream->mmap_count))
			जाओ __direct;
		अगर ((err = snd_pcm_oss_make_पढ़ोy(substream)) < 0)
			वापस err;
		atomic_inc(&runसमय->oss.rw_ref);
		अगर (mutex_lock_पूर्णांकerruptible(&runसमय->oss.params_lock)) अणु
			atomic_dec(&runसमय->oss.rw_ref);
			वापस -ERESTARTSYS;
		पूर्ण
		क्रमmat = snd_pcm_oss_क्रमmat_from(runसमय->oss.क्रमmat);
		width = snd_pcm_क्रमmat_physical_width(क्रमmat);
		अगर (runसमय->oss.buffer_used > 0) अणु
#अगर_घोषित OSS_DEBUG
			pcm_dbg(substream->pcm, "sync: buffer_used\n");
#पूर्ण_अगर
			size = (8 * (runसमय->oss.period_bytes - runसमय->oss.buffer_used) + 7) / width;
			snd_pcm_क्रमmat_set_silence(क्रमmat,
						   runसमय->oss.buffer + runसमय->oss.buffer_used,
						   size);
			err = snd_pcm_oss_sync1(substream, runसमय->oss.period_bytes);
			अगर (err < 0)
				जाओ unlock;
		पूर्ण अन्यथा अगर (runसमय->oss.period_ptr > 0) अणु
#अगर_घोषित OSS_DEBUG
			pcm_dbg(substream->pcm, "sync: period_ptr\n");
#पूर्ण_अगर
			size = runसमय->oss.period_bytes - runसमय->oss.period_ptr;
			snd_pcm_क्रमmat_set_silence(क्रमmat,
						   runसमय->oss.buffer,
						   size * 8 / width);
			err = snd_pcm_oss_sync1(substream, size);
			अगर (err < 0)
				जाओ unlock;
		पूर्ण
		/*
		 * The ALSA's period might be a bit large than OSS one.
		 * Fill the reमुख्य portion of ALSA period with zeros.
		 */
		size = runसमय->control->appl_ptr % runसमय->period_size;
		अगर (size > 0) अणु
			size = runसमय->period_size - size;
			अगर (runसमय->access == SNDRV_PCM_ACCESS_RW_INTERLEAVED)
				snd_pcm_lib_ग_लिखो(substream, शून्य, size);
			अन्यथा अगर (runसमय->access == SNDRV_PCM_ACCESS_RW_NONINTERLEAVED)
				snd_pcm_lib_ग_लिखोv(substream, शून्य, size);
		पूर्ण
unlock:
		mutex_unlock(&runसमय->oss.params_lock);
		atomic_dec(&runसमय->oss.rw_ref);
		अगर (err < 0)
			वापस err;
		/*
		 * finish sync: drain the buffer
		 */
	      __direct:
		saved_f_flags = substream->f_flags;
		substream->f_flags &= ~O_NONBLOCK;
		err = snd_pcm_kernel_ioctl(substream, SNDRV_PCM_IOCTL_DRAIN, शून्य);
		substream->f_flags = saved_f_flags;
		अगर (err < 0)
			वापस err;
		mutex_lock(&runसमय->oss.params_lock);
		runसमय->oss.prepare = 1;
		mutex_unlock(&runसमय->oss.params_lock);
	पूर्ण

	substream = pcm_oss_file->streams[SNDRV_PCM_STREAM_CAPTURE];
	अगर (substream != शून्य) अणु
		अगर ((err = snd_pcm_oss_make_पढ़ोy(substream)) < 0)
			वापस err;
		runसमय = substream->runसमय;
		err = snd_pcm_kernel_ioctl(substream, SNDRV_PCM_IOCTL_DROP, शून्य);
		अगर (err < 0)
			वापस err;
		mutex_lock(&runसमय->oss.params_lock);
		runसमय->oss.buffer_used = 0;
		runसमय->oss.prepare = 1;
		mutex_unlock(&runसमय->oss.params_lock);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक snd_pcm_oss_set_rate(काष्ठा snd_pcm_oss_file *pcm_oss_file, पूर्णांक rate)
अणु
	पूर्णांक idx;

	क्रम (idx = 1; idx >= 0; --idx) अणु
		काष्ठा snd_pcm_substream *substream = pcm_oss_file->streams[idx];
		काष्ठा snd_pcm_runसमय *runसमय;
		पूर्णांक err;

		अगर (substream == शून्य)
			जारी;
		runसमय = substream->runसमय;
		अगर (rate < 1000)
			rate = 1000;
		अन्यथा अगर (rate > 192000)
			rate = 192000;
		err = lock_params(runसमय);
		अगर (err < 0)
			वापस err;
		अगर (runसमय->oss.rate != rate) अणु
			runसमय->oss.params = 1;
			runसमय->oss.rate = rate;
		पूर्ण
		unlock_params(runसमय);
	पूर्ण
	वापस snd_pcm_oss_get_rate(pcm_oss_file);
पूर्ण

अटल पूर्णांक snd_pcm_oss_get_rate(काष्ठा snd_pcm_oss_file *pcm_oss_file)
अणु
	काष्ठा snd_pcm_substream *substream;
	पूर्णांक err;
	
	अगर ((err = snd_pcm_oss_get_active_substream(pcm_oss_file, &substream)) < 0)
		वापस err;
	वापस substream->runसमय->oss.rate;
पूर्ण

अटल पूर्णांक snd_pcm_oss_set_channels(काष्ठा snd_pcm_oss_file *pcm_oss_file, अचिन्हित पूर्णांक channels)
अणु
	पूर्णांक idx;
	अगर (channels < 1)
		channels = 1;
	अगर (channels > 128)
		वापस -EINVAL;
	क्रम (idx = 1; idx >= 0; --idx) अणु
		काष्ठा snd_pcm_substream *substream = pcm_oss_file->streams[idx];
		काष्ठा snd_pcm_runसमय *runसमय;
		पूर्णांक err;

		अगर (substream == शून्य)
			जारी;
		runसमय = substream->runसमय;
		err = lock_params(runसमय);
		अगर (err < 0)
			वापस err;
		अगर (runसमय->oss.channels != channels) अणु
			runसमय->oss.params = 1;
			runसमय->oss.channels = channels;
		पूर्ण
		unlock_params(runसमय);
	पूर्ण
	वापस snd_pcm_oss_get_channels(pcm_oss_file);
पूर्ण

अटल पूर्णांक snd_pcm_oss_get_channels(काष्ठा snd_pcm_oss_file *pcm_oss_file)
अणु
	काष्ठा snd_pcm_substream *substream;
	पूर्णांक err;
	
	अगर ((err = snd_pcm_oss_get_active_substream(pcm_oss_file, &substream)) < 0)
		वापस err;
	वापस substream->runसमय->oss.channels;
पूर्ण

अटल पूर्णांक snd_pcm_oss_get_block_size(काष्ठा snd_pcm_oss_file *pcm_oss_file)
अणु
	काष्ठा snd_pcm_substream *substream;
	पूर्णांक err;
	
	अगर ((err = snd_pcm_oss_get_active_substream(pcm_oss_file, &substream)) < 0)
		वापस err;
	वापस substream->runसमय->oss.period_bytes;
पूर्ण

अटल पूर्णांक snd_pcm_oss_get_क्रमmats(काष्ठा snd_pcm_oss_file *pcm_oss_file)
अणु
	काष्ठा snd_pcm_substream *substream;
	पूर्णांक err;
	पूर्णांक direct;
	काष्ठा snd_pcm_hw_params *params;
	अचिन्हित पूर्णांक क्रमmats = 0;
	स्थिर काष्ठा snd_mask *क्रमmat_mask;
	पूर्णांक fmt;

	अगर ((err = snd_pcm_oss_get_active_substream(pcm_oss_file, &substream)) < 0)
		वापस err;
	अगर (atomic_पढ़ो(&substream->mmap_count))
		direct = 1;
	अन्यथा
		direct = substream->oss.setup.direct;
	अगर (!direct)
		वापस AFMT_MU_LAW | AFMT_U8 |
		       AFMT_S16_LE | AFMT_S16_BE |
		       AFMT_S8 | AFMT_U16_LE |
		       AFMT_U16_BE |
			AFMT_S32_LE | AFMT_S32_BE |
			AFMT_S24_LE | AFMT_S24_BE |
			AFMT_S24_PACKED;
	params = kदो_स्मृति(माप(*params), GFP_KERNEL);
	अगर (!params)
		वापस -ENOMEM;
	_snd_pcm_hw_params_any(params);
	err = snd_pcm_hw_refine(substream, params);
	अगर (err < 0)
		जाओ error;
	क्रमmat_mask = hw_param_mask_c(params, SNDRV_PCM_HW_PARAM_FORMAT);
	क्रम (fmt = 0; fmt < 32; ++fmt) अणु
		अगर (snd_mask_test(क्रमmat_mask, fmt)) अणु
			पूर्णांक f = snd_pcm_oss_क्रमmat_to((__क्रमce snd_pcm_क्रमmat_t)fmt);
			अगर (f >= 0)
				क्रमmats |= f;
		पूर्ण
	पूर्ण

 error:
	kमुक्त(params);
	वापस err < 0 ? err : क्रमmats;
पूर्ण

अटल पूर्णांक snd_pcm_oss_set_क्रमmat(काष्ठा snd_pcm_oss_file *pcm_oss_file, पूर्णांक क्रमmat)
अणु
	पूर्णांक क्रमmats, idx;
	पूर्णांक err;
	
	अगर (क्रमmat != AFMT_QUERY) अणु
		क्रमmats = snd_pcm_oss_get_क्रमmats(pcm_oss_file);
		अगर (क्रमmats < 0)
			वापस क्रमmats;
		अगर (!(क्रमmats & क्रमmat))
			क्रमmat = AFMT_U8;
		क्रम (idx = 1; idx >= 0; --idx) अणु
			काष्ठा snd_pcm_substream *substream = pcm_oss_file->streams[idx];
			काष्ठा snd_pcm_runसमय *runसमय;
			अगर (substream == शून्य)
				जारी;
			runसमय = substream->runसमय;
			err = lock_params(runसमय);
			अगर (err < 0)
				वापस err;
			अगर (runसमय->oss.क्रमmat != क्रमmat) अणु
				runसमय->oss.params = 1;
				runसमय->oss.क्रमmat = क्रमmat;
			पूर्ण
			unlock_params(runसमय);
		पूर्ण
	पूर्ण
	वापस snd_pcm_oss_get_क्रमmat(pcm_oss_file);
पूर्ण

अटल पूर्णांक snd_pcm_oss_get_क्रमmat(काष्ठा snd_pcm_oss_file *pcm_oss_file)
अणु
	काष्ठा snd_pcm_substream *substream;
	पूर्णांक err;
	
	अगर ((err = snd_pcm_oss_get_active_substream(pcm_oss_file, &substream)) < 0)
		वापस err;
	वापस substream->runसमय->oss.क्रमmat;
पूर्ण

अटल पूर्णांक snd_pcm_oss_set_subभागide1(काष्ठा snd_pcm_substream *substream, पूर्णांक subभागide)
अणु
	काष्ठा snd_pcm_runसमय *runसमय;

	runसमय = substream->runसमय;
	अगर (subभागide == 0) अणु
		subभागide = runसमय->oss.subभागision;
		अगर (subभागide == 0)
			subभागide = 1;
		वापस subभागide;
	पूर्ण
	अगर (runसमय->oss.subभागision || runसमय->oss.fragshअगरt)
		वापस -EINVAL;
	अगर (subभागide != 1 && subभागide != 2 && subभागide != 4 &&
	    subभागide != 8 && subभागide != 16)
		वापस -EINVAL;
	runसमय->oss.subभागision = subभागide;
	runसमय->oss.params = 1;
	वापस subभागide;
पूर्ण

अटल पूर्णांक snd_pcm_oss_set_subभागide(काष्ठा snd_pcm_oss_file *pcm_oss_file, पूर्णांक subभागide)
अणु
	पूर्णांक err = -EINVAL, idx;

	क्रम (idx = 1; idx >= 0; --idx) अणु
		काष्ठा snd_pcm_substream *substream = pcm_oss_file->streams[idx];
		काष्ठा snd_pcm_runसमय *runसमय;

		अगर (substream == शून्य)
			जारी;
		runसमय = substream->runसमय;
		err = lock_params(runसमय);
		अगर (err < 0)
			वापस err;
		err = snd_pcm_oss_set_subभागide1(substream, subभागide);
		unlock_params(runसमय);
		अगर (err < 0)
			वापस err;
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक snd_pcm_oss_set_fragment1(काष्ठा snd_pcm_substream *substream, अचिन्हित पूर्णांक val)
अणु
	काष्ठा snd_pcm_runसमय *runसमय;
	पूर्णांक fragshअगरt;

	runसमय = substream->runसमय;
	अगर (runसमय->oss.subभागision || runसमय->oss.fragshअगरt)
		वापस -EINVAL;
	fragshअगरt = val & 0xffff;
	अगर (fragshअगरt >= 31)
		वापस -EINVAL;
	runसमय->oss.fragshअगरt = fragshअगरt;
	runसमय->oss.maxfrags = (val >> 16) & 0xffff;
	अगर (runसमय->oss.fragshअगरt < 4)		/* < 16 */
		runसमय->oss.fragshअगरt = 4;
	अगर (runसमय->oss.maxfrags < 2)
		runसमय->oss.maxfrags = 2;
	runसमय->oss.params = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_pcm_oss_set_fragment(काष्ठा snd_pcm_oss_file *pcm_oss_file, अचिन्हित पूर्णांक val)
अणु
	पूर्णांक err = -EINVAL, idx;

	क्रम (idx = 1; idx >= 0; --idx) अणु
		काष्ठा snd_pcm_substream *substream = pcm_oss_file->streams[idx];
		काष्ठा snd_pcm_runसमय *runसमय;

		अगर (substream == शून्य)
			जारी;
		runसमय = substream->runसमय;
		err = lock_params(runसमय);
		अगर (err < 0)
			वापस err;
		err = snd_pcm_oss_set_fragment1(substream, val);
		unlock_params(runसमय);
		अगर (err < 0)
			वापस err;
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक snd_pcm_oss_nonblock(काष्ठा file * file)
अणु
	spin_lock(&file->f_lock);
	file->f_flags |= O_NONBLOCK;
	spin_unlock(&file->f_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_pcm_oss_get_caps1(काष्ठा snd_pcm_substream *substream, पूर्णांक res)
अणु

	अगर (substream == शून्य) अणु
		res &= ~DSP_CAP_DUPLEX;
		वापस res;
	पूर्ण
#अगर_घोषित DSP_CAP_MULTI
	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		अगर (substream->pstr->substream_count > 1)
			res |= DSP_CAP_MULTI;
#पूर्ण_अगर
	/* DSP_CAP_REALTIME is set all बार: */
	/* all ALSA drivers can वापस actual poपूर्णांकer in ring buffer */
#अगर defined(DSP_CAP_REALTIME) && 0
	अणु
		काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
		अगर (runसमय->info & (SNDRV_PCM_INFO_BLOCK_TRANSFER|SNDRV_PCM_INFO_BATCH))
			res &= ~DSP_CAP_REALTIME;
	पूर्ण
#पूर्ण_अगर
	वापस res;
पूर्ण

अटल पूर्णांक snd_pcm_oss_get_caps(काष्ठा snd_pcm_oss_file *pcm_oss_file)
अणु
	पूर्णांक result, idx;
	
	result = DSP_CAP_TRIGGER | DSP_CAP_MMAP	| DSP_CAP_DUPLEX | DSP_CAP_REALTIME;
	क्रम (idx = 0; idx < 2; idx++) अणु
		काष्ठा snd_pcm_substream *substream = pcm_oss_file->streams[idx];
		result = snd_pcm_oss_get_caps1(substream, result);
	पूर्ण
	result |= 0x0001;	/* revision - same as SB AWE 64 */
	वापस result;
पूर्ण

अटल व्योम snd_pcm_oss_simulate_fill(काष्ठा snd_pcm_substream *substream,
				      snd_pcm_uframes_t hw_ptr)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	snd_pcm_uframes_t appl_ptr;
	appl_ptr = hw_ptr + runसमय->buffer_size;
	appl_ptr %= runसमय->boundary;
	runसमय->control->appl_ptr = appl_ptr;
पूर्ण

अटल पूर्णांक snd_pcm_oss_set_trigger(काष्ठा snd_pcm_oss_file *pcm_oss_file, पूर्णांक trigger)
अणु
	काष्ठा snd_pcm_runसमय *runसमय;
	काष्ठा snd_pcm_substream *psubstream = शून्य, *csubstream = शून्य;
	पूर्णांक err, cmd;

#अगर_घोषित OSS_DEBUG
	pcm_dbg(substream->pcm, "pcm_oss: trigger = 0x%x\n", trigger);
#पूर्ण_अगर
	
	psubstream = pcm_oss_file->streams[SNDRV_PCM_STREAM_PLAYBACK];
	csubstream = pcm_oss_file->streams[SNDRV_PCM_STREAM_CAPTURE];

	अगर (psubstream) अणु
		अगर ((err = snd_pcm_oss_make_पढ़ोy(psubstream)) < 0)
			वापस err;
	पूर्ण
	अगर (csubstream) अणु
		अगर ((err = snd_pcm_oss_make_पढ़ोy(csubstream)) < 0)
			वापस err;
	पूर्ण
      	अगर (psubstream) अणु
      		runसमय = psubstream->runसमय;
		cmd = 0;
		अगर (mutex_lock_पूर्णांकerruptible(&runसमय->oss.params_lock))
			वापस -ERESTARTSYS;
		अगर (trigger & PCM_ENABLE_OUTPUT) अणु
			अगर (runसमय->oss.trigger)
				जाओ _skip1;
			अगर (atomic_पढ़ो(&psubstream->mmap_count))
				snd_pcm_oss_simulate_fill(psubstream,
						get_hw_ptr_period(runसमय));
			runसमय->oss.trigger = 1;
			runसमय->start_threshold = 1;
			cmd = SNDRV_PCM_IOCTL_START;
		पूर्ण अन्यथा अणु
			अगर (!runसमय->oss.trigger)
				जाओ _skip1;
			runसमय->oss.trigger = 0;
			runसमय->start_threshold = runसमय->boundary;
			cmd = SNDRV_PCM_IOCTL_DROP;
			runसमय->oss.prepare = 1;
		पूर्ण
 _skip1:
		mutex_unlock(&runसमय->oss.params_lock);
		अगर (cmd) अणु
			err = snd_pcm_kernel_ioctl(psubstream, cmd, शून्य);
			अगर (err < 0)
				वापस err;
		पूर्ण
	पूर्ण
	अगर (csubstream) अणु
      		runसमय = csubstream->runसमय;
		cmd = 0;
		अगर (mutex_lock_पूर्णांकerruptible(&runसमय->oss.params_lock))
			वापस -ERESTARTSYS;
		अगर (trigger & PCM_ENABLE_INPUT) अणु
			अगर (runसमय->oss.trigger)
				जाओ _skip2;
			runसमय->oss.trigger = 1;
			runसमय->start_threshold = 1;
			cmd = SNDRV_PCM_IOCTL_START;
		पूर्ण अन्यथा अणु
			अगर (!runसमय->oss.trigger)
				जाओ _skip2;
			runसमय->oss.trigger = 0;
			runसमय->start_threshold = runसमय->boundary;
			cmd = SNDRV_PCM_IOCTL_DROP;
			runसमय->oss.prepare = 1;
		पूर्ण
 _skip2:
		mutex_unlock(&runसमय->oss.params_lock);
		अगर (cmd) अणु
			err = snd_pcm_kernel_ioctl(csubstream, cmd, शून्य);
			अगर (err < 0)
				वापस err;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक snd_pcm_oss_get_trigger(काष्ठा snd_pcm_oss_file *pcm_oss_file)
अणु
	काष्ठा snd_pcm_substream *psubstream = शून्य, *csubstream = शून्य;
	पूर्णांक result = 0;

	psubstream = pcm_oss_file->streams[SNDRV_PCM_STREAM_PLAYBACK];
	csubstream = pcm_oss_file->streams[SNDRV_PCM_STREAM_CAPTURE];
	अगर (psubstream && psubstream->runसमय && psubstream->runसमय->oss.trigger)
		result |= PCM_ENABLE_OUTPUT;
	अगर (csubstream && csubstream->runसमय && csubstream->runसमय->oss.trigger)
		result |= PCM_ENABLE_INPUT;
	वापस result;
पूर्ण

अटल पूर्णांक snd_pcm_oss_get_odelay(काष्ठा snd_pcm_oss_file *pcm_oss_file)
अणु
	काष्ठा snd_pcm_substream *substream;
	काष्ठा snd_pcm_runसमय *runसमय;
	snd_pcm_sframes_t delay;
	पूर्णांक err;

	substream = pcm_oss_file->streams[SNDRV_PCM_STREAM_PLAYBACK];
	अगर (substream == शून्य)
		वापस -EINVAL;
	अगर ((err = snd_pcm_oss_make_पढ़ोy(substream)) < 0)
		वापस err;
	runसमय = substream->runसमय;
	अगर (runसमय->oss.params || runसमय->oss.prepare)
		वापस 0;
	err = snd_pcm_kernel_ioctl(substream, SNDRV_PCM_IOCTL_DELAY, &delay);
	अगर (err == -EPIPE)
		delay = 0;	/* hack क्रम broken OSS applications */
	अन्यथा अगर (err < 0)
		वापस err;
	वापस snd_pcm_oss_bytes(substream, delay);
पूर्ण

अटल पूर्णांक snd_pcm_oss_get_ptr(काष्ठा snd_pcm_oss_file *pcm_oss_file, पूर्णांक stream, काष्ठा count_info __user * _info)
अणु	
	काष्ठा snd_pcm_substream *substream;
	काष्ठा snd_pcm_runसमय *runसमय;
	snd_pcm_sframes_t delay;
	पूर्णांक fixup;
	काष्ठा count_info info;
	पूर्णांक err;

	अगर (_info == शून्य)
		वापस -EFAULT;
	substream = pcm_oss_file->streams[stream];
	अगर (substream == शून्य)
		वापस -EINVAL;
	अगर ((err = snd_pcm_oss_make_पढ़ोy(substream)) < 0)
		वापस err;
	runसमय = substream->runसमय;
	अगर (runसमय->oss.params || runसमय->oss.prepare) अणु
		स_रखो(&info, 0, माप(info));
		अगर (copy_to_user(_info, &info, माप(info)))
			वापस -EFAULT;
		वापस 0;
	पूर्ण
	अगर (stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
		err = snd_pcm_kernel_ioctl(substream, SNDRV_PCM_IOCTL_DELAY, &delay);
		अगर (err == -EPIPE || err == -ESTRPIPE || (! err && delay < 0)) अणु
			err = 0;
			delay = 0;
			fixup = 0;
		पूर्ण अन्यथा अणु
			fixup = runसमय->oss.buffer_used;
		पूर्ण
	पूर्ण अन्यथा अणु
		err = snd_pcm_oss_capture_position_fixup(substream, &delay);
		fixup = -runसमय->oss.buffer_used;
	पूर्ण
	अगर (err < 0)
		वापस err;
	info.ptr = snd_pcm_oss_bytes(substream, runसमय->status->hw_ptr % runसमय->buffer_size);
	अगर (atomic_पढ़ो(&substream->mmap_count)) अणु
		snd_pcm_sframes_t n;
		delay = get_hw_ptr_period(runसमय);
		n = delay - runसमय->oss.prev_hw_ptr_period;
		अगर (n < 0)
			n += runसमय->boundary;
		info.blocks = n / runसमय->period_size;
		runसमय->oss.prev_hw_ptr_period = delay;
		अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
			snd_pcm_oss_simulate_fill(substream, delay);
		info.bytes = snd_pcm_oss_bytes(substream, runसमय->status->hw_ptr) & पूर्णांक_उच्च;
	पूर्ण अन्यथा अणु
		delay = snd_pcm_oss_bytes(substream, delay);
		अगर (stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
			अगर (substream->oss.setup.buggyptr)
				info.blocks = (runसमय->oss.buffer_bytes - delay - fixup) / runसमय->oss.period_bytes;
			अन्यथा
				info.blocks = (delay + fixup) / runसमय->oss.period_bytes;
			info.bytes = (runसमय->oss.bytes - delay) & पूर्णांक_उच्च;
		पूर्ण अन्यथा अणु
			delay += fixup;
			info.blocks = delay / runसमय->oss.period_bytes;
			info.bytes = (runसमय->oss.bytes + delay) & पूर्णांक_उच्च;
		पूर्ण
	पूर्ण
	अगर (copy_to_user(_info, &info, माप(info)))
		वापस -EFAULT;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_pcm_oss_get_space(काष्ठा snd_pcm_oss_file *pcm_oss_file, पूर्णांक stream, काष्ठा audio_buf_info __user *_info)
अणु
	काष्ठा snd_pcm_substream *substream;
	काष्ठा snd_pcm_runसमय *runसमय;
	snd_pcm_sframes_t avail;
	पूर्णांक fixup;
	काष्ठा audio_buf_info info;
	पूर्णांक err;

	अगर (_info == शून्य)
		वापस -EFAULT;
	substream = pcm_oss_file->streams[stream];
	अगर (substream == शून्य)
		वापस -EINVAL;
	runसमय = substream->runसमय;

	अगर (runसमय->oss.params &&
	    (err = snd_pcm_oss_change_params(substream, false)) < 0)
		वापस err;

	info.fragsize = runसमय->oss.period_bytes;
	info.fragstotal = runसमय->periods;
	अगर (runसमय->oss.prepare) अणु
		अगर (stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
			info.bytes = runसमय->oss.period_bytes * runसमय->oss.periods;
			info.fragments = runसमय->oss.periods;
		पूर्ण अन्यथा अणु
			info.bytes = 0;
			info.fragments = 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
			err = snd_pcm_kernel_ioctl(substream, SNDRV_PCM_IOCTL_DELAY, &avail);
			अगर (err == -EPIPE || err == -ESTRPIPE || (! err && avail < 0)) अणु
				avail = runसमय->buffer_size;
				err = 0;
				fixup = 0;
			पूर्ण अन्यथा अणु
				avail = runसमय->buffer_size - avail;
				fixup = -runसमय->oss.buffer_used;
			पूर्ण
		पूर्ण अन्यथा अणु
			err = snd_pcm_oss_capture_position_fixup(substream, &avail);
			fixup = runसमय->oss.buffer_used;
		पूर्ण
		अगर (err < 0)
			वापस err;
		info.bytes = snd_pcm_oss_bytes(substream, avail) + fixup;
		info.fragments = info.bytes / runसमय->oss.period_bytes;
	पूर्ण

#अगर_घोषित OSS_DEBUG
	pcm_dbg(substream->pcm,
		"pcm_oss: space: bytes = %i, fragments = %i, fragstotal = %i, fragsize = %i\n",
		info.bytes, info.fragments, info.fragstotal, info.fragsize);
#पूर्ण_अगर
	अगर (copy_to_user(_info, &info, माप(info)))
		वापस -EFAULT;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_pcm_oss_get_mapbuf(काष्ठा snd_pcm_oss_file *pcm_oss_file, पूर्णांक stream, काष्ठा buffmem_desc __user * _info)
अणु
	// it won't be probably implemented
	// pr_debug("TODO: snd_pcm_oss_get_mapbuf\n");
	वापस -EINVAL;
पूर्ण

अटल स्थिर अक्षर *strip_task_path(स्थिर अक्षर *path)
अणु
	स्थिर अक्षर *ptr, *ptrl = शून्य;
	क्रम (ptr = path; *ptr; ptr++) अणु
		अगर (*ptr == '/')
			ptrl = ptr + 1;
	पूर्ण
	वापस ptrl;
पूर्ण

अटल व्योम snd_pcm_oss_look_क्रम_setup(काष्ठा snd_pcm *pcm, पूर्णांक stream,
				      स्थिर अक्षर *task_name,
				      काष्ठा snd_pcm_oss_setup *rsetup)
अणु
	काष्ठा snd_pcm_oss_setup *setup;

	mutex_lock(&pcm->streams[stream].oss.setup_mutex);
	करो अणु
		क्रम (setup = pcm->streams[stream].oss.setup_list; setup;
		     setup = setup->next) अणु
			अगर (!म_भेद(setup->task_name, task_name))
				जाओ out;
		पूर्ण
	पूर्ण जबतक ((task_name = strip_task_path(task_name)) != शून्य);
 out:
	अगर (setup)
		*rsetup = *setup;
	mutex_unlock(&pcm->streams[stream].oss.setup_mutex);
पूर्ण

अटल व्योम snd_pcm_oss_release_substream(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय;
	runसमय = substream->runसमय;
	kvमुक्त(runसमय->oss.buffer);
	runसमय->oss.buffer = शून्य;
#अगर_घोषित CONFIG_SND_PCM_OSS_PLUGINS
	snd_pcm_oss_plugin_clear(substream);
#पूर्ण_अगर
	substream->oss.oss = 0;
पूर्ण

अटल व्योम snd_pcm_oss_init_substream(काष्ठा snd_pcm_substream *substream,
				       काष्ठा snd_pcm_oss_setup *setup,
				       पूर्णांक minor)
अणु
	काष्ठा snd_pcm_runसमय *runसमय;

	substream->oss.oss = 1;
	substream->oss.setup = *setup;
	अगर (setup->nonblock)
		substream->f_flags |= O_NONBLOCK;
	अन्यथा अगर (setup->block)
		substream->f_flags &= ~O_NONBLOCK;
	runसमय = substream->runसमय;
	runसमय->oss.params = 1;
	runसमय->oss.trigger = 1;
	runसमय->oss.rate = 8000;
	mutex_init(&runसमय->oss.params_lock);
	चयन (SNDRV_MINOR_OSS_DEVICE(minor)) अणु
	हाल SNDRV_MINOR_OSS_PCM_8:
		runसमय->oss.क्रमmat = AFMT_U8;
		अवरोध;
	हाल SNDRV_MINOR_OSS_PCM_16:
		runसमय->oss.क्रमmat = AFMT_S16_LE;
		अवरोध;
	शेष:
		runसमय->oss.क्रमmat = AFMT_MU_LAW;
	पूर्ण
	runसमय->oss.channels = 1;
	runसमय->oss.fragshअगरt = 0;
	runसमय->oss.maxfrags = 0;
	runसमय->oss.subभागision = 0;
	substream->pcm_release = snd_pcm_oss_release_substream;
	atomic_set(&runसमय->oss.rw_ref, 0);
पूर्ण

अटल पूर्णांक snd_pcm_oss_release_file(काष्ठा snd_pcm_oss_file *pcm_oss_file)
अणु
	पूर्णांक cidx;
	अगर (!pcm_oss_file)
		वापस 0;
	क्रम (cidx = 0; cidx < 2; ++cidx) अणु
		काष्ठा snd_pcm_substream *substream = pcm_oss_file->streams[cidx];
		अगर (substream)
			snd_pcm_release_substream(substream);
	पूर्ण
	kमुक्त(pcm_oss_file);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_pcm_oss_खोलो_file(काष्ठा file *file,
				 काष्ठा snd_pcm *pcm,
				 काष्ठा snd_pcm_oss_file **rpcm_oss_file,
				 पूर्णांक minor,
				 काष्ठा snd_pcm_oss_setup *setup)
अणु
	पूर्णांक idx, err;
	काष्ठा snd_pcm_oss_file *pcm_oss_file;
	काष्ठा snd_pcm_substream *substream;
	भ_शेषe_t f_mode = file->f_mode;

	अगर (rpcm_oss_file)
		*rpcm_oss_file = शून्य;

	pcm_oss_file = kzalloc(माप(*pcm_oss_file), GFP_KERNEL);
	अगर (pcm_oss_file == शून्य)
		वापस -ENOMEM;

	अगर ((f_mode & (FMODE_WRITE|FMODE_READ)) == (FMODE_WRITE|FMODE_READ) &&
	    (pcm->info_flags & SNDRV_PCM_INFO_HALF_DUPLEX))
		f_mode = FMODE_WRITE;

	file->f_flags &= ~O_APPEND;
	क्रम (idx = 0; idx < 2; idx++) अणु
		अगर (setup[idx].disable)
			जारी;
		अगर (! pcm->streams[idx].substream_count)
			जारी; /* no matching substream */
		अगर (idx == SNDRV_PCM_STREAM_PLAYBACK) अणु
			अगर (! (f_mode & FMODE_WRITE))
				जारी;
		पूर्ण अन्यथा अणु
			अगर (! (f_mode & FMODE_READ))
				जारी;
		पूर्ण
		err = snd_pcm_खोलो_substream(pcm, idx, file, &substream);
		अगर (err < 0) अणु
			snd_pcm_oss_release_file(pcm_oss_file);
			वापस err;
		पूर्ण

		pcm_oss_file->streams[idx] = substream;
		snd_pcm_oss_init_substream(substream, &setup[idx], minor);
	पूर्ण
	
	अगर (!pcm_oss_file->streams[0] && !pcm_oss_file->streams[1]) अणु
		snd_pcm_oss_release_file(pcm_oss_file);
		वापस -EINVAL;
	पूर्ण

	file->निजी_data = pcm_oss_file;
	अगर (rpcm_oss_file)
		*rpcm_oss_file = pcm_oss_file;
	वापस 0;
पूर्ण


अटल पूर्णांक snd_task_name(काष्ठा task_काष्ठा *task, अक्षर *name, माप_प्रकार size)
अणु
	अचिन्हित पूर्णांक idx;

	अगर (snd_BUG_ON(!task || !name || size < 2))
		वापस -EINVAL;
	क्रम (idx = 0; idx < माप(task->comm) && idx + 1 < size; idx++)
		name[idx] = task->comm[idx];
	name[idx] = '\0';
	वापस 0;
पूर्ण

अटल पूर्णांक snd_pcm_oss_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	पूर्णांक err;
	अक्षर task_name[32];
	काष्ठा snd_pcm *pcm;
	काष्ठा snd_pcm_oss_file *pcm_oss_file;
	काष्ठा snd_pcm_oss_setup setup[2];
	पूर्णांक nonblock;
	रुको_queue_entry_t रुको;

	err = nonseekable_खोलो(inode, file);
	अगर (err < 0)
		वापस err;

	pcm = snd_lookup_oss_minor_data(iminor(inode),
					SNDRV_OSS_DEVICE_TYPE_PCM);
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
	अगर (snd_task_name(current, task_name, माप(task_name)) < 0) अणु
		err = -EFAULT;
		जाओ __error;
	पूर्ण
	स_रखो(setup, 0, माप(setup));
	अगर (file->f_mode & FMODE_WRITE)
		snd_pcm_oss_look_क्रम_setup(pcm, SNDRV_PCM_STREAM_PLAYBACK,
					   task_name, &setup[0]);
	अगर (file->f_mode & FMODE_READ)
		snd_pcm_oss_look_क्रम_setup(pcm, SNDRV_PCM_STREAM_CAPTURE,
					   task_name, &setup[1]);

	nonblock = !!(file->f_flags & O_NONBLOCK);
	अगर (!nonblock)
		nonblock = nonblock_खोलो;

	init_रुकोqueue_entry(&रुको, current);
	add_रुको_queue(&pcm->खोलो_रुको, &रुको);
	mutex_lock(&pcm->खोलो_mutex);
	जबतक (1) अणु
		err = snd_pcm_oss_खोलो_file(file, pcm, &pcm_oss_file,
					    iminor(inode), setup);
		अगर (err >= 0)
			अवरोध;
		अगर (err == -EAGAIN) अणु
			अगर (nonblock) अणु
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
	snd_card_unref(pcm->card);
	वापस err;

      __error:
     	module_put(pcm->card->module);
      __error2:
      	snd_card_file_हटाओ(pcm->card, file);
      __error1:
	अगर (pcm)
		snd_card_unref(pcm->card);
	वापस err;
पूर्ण

अटल पूर्णांक snd_pcm_oss_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा snd_pcm *pcm;
	काष्ठा snd_pcm_substream *substream;
	काष्ठा snd_pcm_oss_file *pcm_oss_file;

	pcm_oss_file = file->निजी_data;
	substream = pcm_oss_file->streams[SNDRV_PCM_STREAM_PLAYBACK];
	अगर (substream == शून्य)
		substream = pcm_oss_file->streams[SNDRV_PCM_STREAM_CAPTURE];
	अगर (snd_BUG_ON(!substream))
		वापस -ENXIO;
	pcm = substream->pcm;
	अगर (!pcm->card->shutकरोwn)
		snd_pcm_oss_sync(pcm_oss_file);
	mutex_lock(&pcm->खोलो_mutex);
	snd_pcm_oss_release_file(pcm_oss_file);
	mutex_unlock(&pcm->खोलो_mutex);
	wake_up(&pcm->खोलो_रुको);
	module_put(pcm->card->module);
	snd_card_file_हटाओ(pcm->card, file);
	वापस 0;
पूर्ण

अटल दीर्घ snd_pcm_oss_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा snd_pcm_oss_file *pcm_oss_file;
	पूर्णांक __user *p = (पूर्णांक __user *)arg;
	पूर्णांक res;

	pcm_oss_file = file->निजी_data;
	अगर (cmd == OSS_GETVERSION)
		वापस put_user(SNDRV_OSS_VERSION, p);
	अगर (cmd == OSS_ALSAEMULVER)
		वापस put_user(1, p);
#अगर IS_REACHABLE(CONFIG_SND_MIXER_OSS)
	अगर (((cmd >> 8) & 0xff) == 'M')	अणु	/* mixer ioctl - क्रम OSS compatibility */
		काष्ठा snd_pcm_substream *substream;
		पूर्णांक idx;
		क्रम (idx = 0; idx < 2; ++idx) अणु
			substream = pcm_oss_file->streams[idx];
			अगर (substream != शून्य)
				अवरोध;
		पूर्ण
		अगर (snd_BUG_ON(idx >= 2))
			वापस -ENXIO;
		वापस snd_mixer_oss_ioctl_card(substream->pcm->card, cmd, arg);
	पूर्ण
#पूर्ण_अगर
	अगर (((cmd >> 8) & 0xff) != 'P')
		वापस -EINVAL;
#अगर_घोषित OSS_DEBUG
	pr_debug("pcm_oss: ioctl = 0x%x\n", cmd);
#पूर्ण_अगर
	चयन (cmd) अणु
	हाल SNDCTL_DSP_RESET:
		वापस snd_pcm_oss_reset(pcm_oss_file);
	हाल SNDCTL_DSP_SYNC:
		वापस snd_pcm_oss_sync(pcm_oss_file);
	हाल SNDCTL_DSP_SPEED:
		अगर (get_user(res, p))
			वापस -EFAULT;
		अगर ((res = snd_pcm_oss_set_rate(pcm_oss_file, res))<0)
			वापस res;
		वापस put_user(res, p);
	हाल SOUND_PCM_READ_RATE:
		res = snd_pcm_oss_get_rate(pcm_oss_file);
		अगर (res < 0)
			वापस res;
		वापस put_user(res, p);
	हाल SNDCTL_DSP_STEREO:
		अगर (get_user(res, p))
			वापस -EFAULT;
		res = res > 0 ? 2 : 1;
		अगर ((res = snd_pcm_oss_set_channels(pcm_oss_file, res)) < 0)
			वापस res;
		वापस put_user(--res, p);
	हाल SNDCTL_DSP_GETBLKSIZE:
		res = snd_pcm_oss_get_block_size(pcm_oss_file);
		अगर (res < 0)
			वापस res;
		वापस put_user(res, p);
	हाल SNDCTL_DSP_SETFMT:
		अगर (get_user(res, p))
			वापस -EFAULT;
		res = snd_pcm_oss_set_क्रमmat(pcm_oss_file, res);
		अगर (res < 0)
			वापस res;
		वापस put_user(res, p);
	हाल SOUND_PCM_READ_BITS:
		res = snd_pcm_oss_get_क्रमmat(pcm_oss_file);
		अगर (res < 0)
			वापस res;
		वापस put_user(res, p);
	हाल SNDCTL_DSP_CHANNELS:
		अगर (get_user(res, p))
			वापस -EFAULT;
		res = snd_pcm_oss_set_channels(pcm_oss_file, res);
		अगर (res < 0)
			वापस res;
		वापस put_user(res, p);
	हाल SOUND_PCM_READ_CHANNELS:
		res = snd_pcm_oss_get_channels(pcm_oss_file);
		अगर (res < 0)
			वापस res;
		वापस put_user(res, p);
	हाल SOUND_PCM_WRITE_FILTER:
	हाल SOUND_PCM_READ_FILTER:
		वापस -EIO;
	हाल SNDCTL_DSP_POST:
		वापस snd_pcm_oss_post(pcm_oss_file);
	हाल SNDCTL_DSP_SUBDIVIDE:
		अगर (get_user(res, p))
			वापस -EFAULT;
		res = snd_pcm_oss_set_subभागide(pcm_oss_file, res);
		अगर (res < 0)
			वापस res;
		वापस put_user(res, p);
	हाल SNDCTL_DSP_SETFRAGMENT:
		अगर (get_user(res, p))
			वापस -EFAULT;
		वापस snd_pcm_oss_set_fragment(pcm_oss_file, res);
	हाल SNDCTL_DSP_GETFMTS:
		res = snd_pcm_oss_get_क्रमmats(pcm_oss_file);
		अगर (res < 0)
			वापस res;
		वापस put_user(res, p);
	हाल SNDCTL_DSP_GETOSPACE:
	हाल SNDCTL_DSP_GETISPACE:
		वापस snd_pcm_oss_get_space(pcm_oss_file,
			cmd == SNDCTL_DSP_GETISPACE ?
				SNDRV_PCM_STREAM_CAPTURE : SNDRV_PCM_STREAM_PLAYBACK,
			(काष्ठा audio_buf_info __user *) arg);
	हाल SNDCTL_DSP_NONBLOCK:
		वापस snd_pcm_oss_nonblock(file);
	हाल SNDCTL_DSP_GETCAPS:
		res = snd_pcm_oss_get_caps(pcm_oss_file);
		अगर (res < 0)
			वापस res;
		वापस put_user(res, p);
	हाल SNDCTL_DSP_GETTRIGGER:
		res = snd_pcm_oss_get_trigger(pcm_oss_file);
		अगर (res < 0)
			वापस res;
		वापस put_user(res, p);
	हाल SNDCTL_DSP_SETTRIGGER:
		अगर (get_user(res, p))
			वापस -EFAULT;
		वापस snd_pcm_oss_set_trigger(pcm_oss_file, res);
	हाल SNDCTL_DSP_GETIPTR:
	हाल SNDCTL_DSP_GETOPTR:
		वापस snd_pcm_oss_get_ptr(pcm_oss_file,
			cmd == SNDCTL_DSP_GETIPTR ?
				SNDRV_PCM_STREAM_CAPTURE : SNDRV_PCM_STREAM_PLAYBACK,
			(काष्ठा count_info __user *) arg);
	हाल SNDCTL_DSP_MAPINBUF:
	हाल SNDCTL_DSP_MAPOUTBUF:
		वापस snd_pcm_oss_get_mapbuf(pcm_oss_file,
			cmd == SNDCTL_DSP_MAPINBUF ?
				SNDRV_PCM_STREAM_CAPTURE : SNDRV_PCM_STREAM_PLAYBACK,
			(काष्ठा buffmem_desc __user *) arg);
	हाल SNDCTL_DSP_SETSYNCRO:
		/* stop DMA now.. */
		वापस 0;
	हाल SNDCTL_DSP_SETDUPLEX:
		अगर (snd_pcm_oss_get_caps(pcm_oss_file) & DSP_CAP_DUPLEX)
			वापस 0;
		वापस -EIO;
	हाल SNDCTL_DSP_GETODELAY:
		res = snd_pcm_oss_get_odelay(pcm_oss_file);
		अगर (res < 0) अणु
			/* it's for sure, some broken apps don't check क्रम error codes */
			put_user(0, p);
			वापस res;
		पूर्ण
		वापस put_user(res, p);
	हाल SNDCTL_DSP_PROखाता:
		वापस 0;	/* silently ignore */
	शेष:
		pr_debug("pcm_oss: unknown command = 0x%x\n", cmd);
	पूर्ण
	वापस -EINVAL;
पूर्ण

#अगर_घोषित CONFIG_COMPAT
/* all compatible */
अटल दीर्घ snd_pcm_oss_ioctl_compat(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
				     अचिन्हित दीर्घ arg)
अणु
	/*
	 * Everything is compatbile except SNDCTL_DSP_MAPINBUF/SNDCTL_DSP_MAPOUTBUF,
	 * which are not implemented क्रम the native हाल either
	 */
	वापस snd_pcm_oss_ioctl(file, cmd, (अचिन्हित दीर्घ)compat_ptr(arg));
पूर्ण
#अन्यथा
#घोषणा snd_pcm_oss_ioctl_compat	शून्य
#पूर्ण_अगर

अटल sमाप_प्रकार snd_pcm_oss_पढ़ो(काष्ठा file *file, अक्षर __user *buf, माप_प्रकार count, loff_t *offset)
अणु
	काष्ठा snd_pcm_oss_file *pcm_oss_file;
	काष्ठा snd_pcm_substream *substream;

	pcm_oss_file = file->निजी_data;
	substream = pcm_oss_file->streams[SNDRV_PCM_STREAM_CAPTURE];
	अगर (substream == शून्य)
		वापस -ENXIO;
	substream->f_flags = file->f_flags & O_NONBLOCK;
#अगर_अघोषित OSS_DEBUG
	वापस snd_pcm_oss_पढ़ो1(substream, buf, count);
#अन्यथा
	अणु
		sमाप_प्रकार res = snd_pcm_oss_पढ़ो1(substream, buf, count);
		pcm_dbg(substream->pcm,
			"pcm_oss: read %li bytes (returned %li bytes)\n",
			(दीर्घ)count, (दीर्घ)res);
		वापस res;
	पूर्ण
#पूर्ण_अगर
पूर्ण

अटल sमाप_प्रकार snd_pcm_oss_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf, माप_प्रकार count, loff_t *offset)
अणु
	काष्ठा snd_pcm_oss_file *pcm_oss_file;
	काष्ठा snd_pcm_substream *substream;
	दीर्घ result;

	pcm_oss_file = file->निजी_data;
	substream = pcm_oss_file->streams[SNDRV_PCM_STREAM_PLAYBACK];
	अगर (substream == शून्य)
		वापस -ENXIO;
	substream->f_flags = file->f_flags & O_NONBLOCK;
	result = snd_pcm_oss_ग_लिखो1(substream, buf, count);
#अगर_घोषित OSS_DEBUG
	pcm_dbg(substream->pcm, "pcm_oss: write %li bytes (wrote %li bytes)\n",
	       (दीर्घ)count, (दीर्घ)result);
#पूर्ण_अगर
	वापस result;
पूर्ण

अटल पूर्णांक snd_pcm_oss_playback_पढ़ोy(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	अगर (atomic_पढ़ो(&substream->mmap_count))
		वापस runसमय->oss.prev_hw_ptr_period !=
						get_hw_ptr_period(runसमय);
	अन्यथा
		वापस snd_pcm_playback_avail(runसमय) >=
						runसमय->oss.period_frames;
पूर्ण

अटल पूर्णांक snd_pcm_oss_capture_पढ़ोy(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	अगर (atomic_पढ़ो(&substream->mmap_count))
		वापस runसमय->oss.prev_hw_ptr_period !=
						get_hw_ptr_period(runसमय);
	अन्यथा
		वापस snd_pcm_capture_avail(runसमय) >=
						runसमय->oss.period_frames;
पूर्ण

अटल __poll_t snd_pcm_oss_poll(काष्ठा file *file, poll_table * रुको)
अणु
	काष्ठा snd_pcm_oss_file *pcm_oss_file;
	__poll_t mask;
	काष्ठा snd_pcm_substream *psubstream = शून्य, *csubstream = शून्य;
	
	pcm_oss_file = file->निजी_data;

	psubstream = pcm_oss_file->streams[SNDRV_PCM_STREAM_PLAYBACK];
	csubstream = pcm_oss_file->streams[SNDRV_PCM_STREAM_CAPTURE];

	mask = 0;
	अगर (psubstream != शून्य) अणु
		काष्ठा snd_pcm_runसमय *runसमय = psubstream->runसमय;
		poll_रुको(file, &runसमय->sleep, रुको);
		snd_pcm_stream_lock_irq(psubstream);
		अगर (runसमय->status->state != SNDRV_PCM_STATE_DRAINING &&
		    (runसमय->status->state != SNDRV_PCM_STATE_RUNNING ||
		     snd_pcm_oss_playback_पढ़ोy(psubstream)))
			mask |= EPOLLOUT | EPOLLWRNORM;
		snd_pcm_stream_unlock_irq(psubstream);
	पूर्ण
	अगर (csubstream != शून्य) अणु
		काष्ठा snd_pcm_runसमय *runसमय = csubstream->runसमय;
		snd_pcm_state_t ostate;
		poll_रुको(file, &runसमय->sleep, रुको);
		snd_pcm_stream_lock_irq(csubstream);
		अगर ((ostate = runसमय->status->state) != SNDRV_PCM_STATE_RUNNING ||
		    snd_pcm_oss_capture_पढ़ोy(csubstream))
			mask |= EPOLLIN | EPOLLRDNORM;
		snd_pcm_stream_unlock_irq(csubstream);
		अगर (ostate != SNDRV_PCM_STATE_RUNNING && runसमय->oss.trigger) अणु
			काष्ठा snd_pcm_oss_file ofile;
			स_रखो(&ofile, 0, माप(ofile));
			ofile.streams[SNDRV_PCM_STREAM_CAPTURE] = pcm_oss_file->streams[SNDRV_PCM_STREAM_CAPTURE];
			runसमय->oss.trigger = 0;
			snd_pcm_oss_set_trigger(&ofile, PCM_ENABLE_INPUT);
		पूर्ण
	पूर्ण

	वापस mask;
पूर्ण

अटल पूर्णांक snd_pcm_oss_mmap(काष्ठा file *file, काष्ठा vm_area_काष्ठा *area)
अणु
	काष्ठा snd_pcm_oss_file *pcm_oss_file;
	काष्ठा snd_pcm_substream *substream = शून्य;
	काष्ठा snd_pcm_runसमय *runसमय;
	पूर्णांक err;

#अगर_घोषित OSS_DEBUG
	pr_debug("pcm_oss: mmap begin\n");
#पूर्ण_अगर
	pcm_oss_file = file->निजी_data;
	चयन ((area->vm_flags & (VM_READ | VM_WRITE))) अणु
	हाल VM_READ | VM_WRITE:
		substream = pcm_oss_file->streams[SNDRV_PCM_STREAM_PLAYBACK];
		अगर (substream)
			अवरोध;
		fallthrough;
	हाल VM_READ:
		substream = pcm_oss_file->streams[SNDRV_PCM_STREAM_CAPTURE];
		अवरोध;
	हाल VM_WRITE:
		substream = pcm_oss_file->streams[SNDRV_PCM_STREAM_PLAYBACK];
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	/* set VM_READ access as well to fix स_रखो() routines that करो
	   पढ़ोs beक्रमe ग_लिखोs (to improve perक्रमmance) */
	area->vm_flags |= VM_READ;
	अगर (substream == शून्य)
		वापस -ENXIO;
	runसमय = substream->runसमय;
	अगर (!(runसमय->info & SNDRV_PCM_INFO_MMAP_VALID))
		वापस -EIO;
	अगर (runसमय->info & SNDRV_PCM_INFO_INTERLEAVED)
		runसमय->access = SNDRV_PCM_ACCESS_MMAP_INTERLEAVED;
	अन्यथा
		वापस -EIO;
	
	अगर (runसमय->oss.params) अणु
		/* use mutex_trylock() क्रम params_lock क्रम aव्योमing a deadlock
		 * between mmap_lock and params_lock taken by
		 * copy_from/to_user() in snd_pcm_oss_ग_लिखो/पढ़ो()
		 */
		err = snd_pcm_oss_change_params(substream, true);
		अगर (err < 0)
			वापस err;
	पूर्ण
#अगर_घोषित CONFIG_SND_PCM_OSS_PLUGINS
	अगर (runसमय->oss.plugin_first != शून्य)
		वापस -EIO;
#पूर्ण_अगर

	अगर (area->vm_pgoff != 0)
		वापस -EINVAL;

	err = snd_pcm_mmap_data(substream, file, area);
	अगर (err < 0)
		वापस err;
	runसमय->oss.mmap_bytes = area->vm_end - area->vm_start;
	runसमय->silence_threshold = 0;
	runसमय->silence_size = 0;
#अगर_घोषित OSS_DEBUG
	pr_debug("pcm_oss: mmap ok, bytes = 0x%x\n",
	       runसमय->oss.mmap_bytes);
#पूर्ण_अगर
	/* In mmap mode we never stop */
	runसमय->stop_threshold = runसमय->boundary;

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_SND_VERBOSE_PROCFS
/*
 *  /proc पूर्णांकerface
 */

अटल व्योम snd_pcm_oss_proc_पढ़ो(काष्ठा snd_info_entry *entry,
				  काष्ठा snd_info_buffer *buffer)
अणु
	काष्ठा snd_pcm_str *pstr = entry->निजी_data;
	काष्ठा snd_pcm_oss_setup *setup = pstr->oss.setup_list;
	mutex_lock(&pstr->oss.setup_mutex);
	जबतक (setup) अणु
		snd_iम_लिखो(buffer, "%s %u %u%s%s%s%s%s%s\n",
			    setup->task_name,
			    setup->periods,
			    setup->period_size,
			    setup->disable ? " disable" : "",
			    setup->direct ? " direct" : "",
			    setup->block ? " block" : "",
			    setup->nonblock ? " non-block" : "",
			    setup->partialfrag ? " partial-frag" : "",
			    setup->nosilence ? " no-silence" : "");
		setup = setup->next;
	पूर्ण
	mutex_unlock(&pstr->oss.setup_mutex);
पूर्ण

अटल व्योम snd_pcm_oss_proc_मुक्त_setup_list(काष्ठा snd_pcm_str * pstr)
अणु
	काष्ठा snd_pcm_oss_setup *setup, *setupn;

	क्रम (setup = pstr->oss.setup_list, pstr->oss.setup_list = शून्य;
	     setup; setup = setupn) अणु
		setupn = setup->next;
		kमुक्त(setup->task_name);
		kमुक्त(setup);
	पूर्ण
	pstr->oss.setup_list = शून्य;
पूर्ण

अटल व्योम snd_pcm_oss_proc_ग_लिखो(काष्ठा snd_info_entry *entry,
				   काष्ठा snd_info_buffer *buffer)
अणु
	काष्ठा snd_pcm_str *pstr = entry->निजी_data;
	अक्षर line[128], str[32], task_name[32];
	स्थिर अक्षर *ptr;
	पूर्णांक idx1;
	काष्ठा snd_pcm_oss_setup *setup, *setup1, ढाँचा;

	जबतक (!snd_info_get_line(buffer, line, माप(line))) अणु
		mutex_lock(&pstr->oss.setup_mutex);
		स_रखो(&ढाँचा, 0, माप(ढाँचा));
		ptr = snd_info_get_str(task_name, line, माप(task_name));
		अगर (!म_भेद(task_name, "clear") || !म_भेद(task_name, "erase")) अणु
			snd_pcm_oss_proc_मुक्त_setup_list(pstr);
			mutex_unlock(&pstr->oss.setup_mutex);
			जारी;
		पूर्ण
		क्रम (setup = pstr->oss.setup_list; setup; setup = setup->next) अणु
			अगर (!म_भेद(setup->task_name, task_name)) अणु
				ढाँचा = *setup;
				अवरोध;
			पूर्ण
		पूर्ण
		ptr = snd_info_get_str(str, ptr, माप(str));
		ढाँचा.periods = simple_म_से_अदीर्घ(str, शून्य, 10);
		ptr = snd_info_get_str(str, ptr, माप(str));
		ढाँचा.period_size = simple_म_से_अदीर्घ(str, शून्य, 10);
		क्रम (idx1 = 31; idx1 >= 0; idx1--)
			अगर (ढाँचा.period_size & (1 << idx1))
				अवरोध;
		क्रम (idx1--; idx1 >= 0; idx1--)
			ढाँचा.period_size &= ~(1 << idx1);
		करो अणु
			ptr = snd_info_get_str(str, ptr, माप(str));
			अगर (!म_भेद(str, "disable")) अणु
				ढाँचा.disable = 1;
			पूर्ण अन्यथा अगर (!म_भेद(str, "direct")) अणु
				ढाँचा.direct = 1;
			पूर्ण अन्यथा अगर (!म_भेद(str, "block")) अणु
				ढाँचा.block = 1;
			पूर्ण अन्यथा अगर (!म_भेद(str, "non-block")) अणु
				ढाँचा.nonblock = 1;
			पूर्ण अन्यथा अगर (!म_भेद(str, "partial-frag")) अणु
				ढाँचा.partialfrag = 1;
			पूर्ण अन्यथा अगर (!म_भेद(str, "no-silence")) अणु
				ढाँचा.nosilence = 1;
			पूर्ण अन्यथा अगर (!म_भेद(str, "buggy-ptr")) अणु
				ढाँचा.buggyptr = 1;
			पूर्ण
		पूर्ण जबतक (*str);
		अगर (setup == शून्य) अणु
			setup = kदो_स्मृति(माप(*setup), GFP_KERNEL);
			अगर (! setup) अणु
				buffer->error = -ENOMEM;
				mutex_unlock(&pstr->oss.setup_mutex);
				वापस;
			पूर्ण
			अगर (pstr->oss.setup_list == शून्य)
				pstr->oss.setup_list = setup;
			अन्यथा अणु
				क्रम (setup1 = pstr->oss.setup_list;
				     setup1->next; setup1 = setup1->next);
				setup1->next = setup;
			पूर्ण
			ढाँचा.task_name = kstrdup(task_name, GFP_KERNEL);
			अगर (! ढाँचा.task_name) अणु
				kमुक्त(setup);
				buffer->error = -ENOMEM;
				mutex_unlock(&pstr->oss.setup_mutex);
				वापस;
			पूर्ण
		पूर्ण
		*setup = ढाँचा;
		mutex_unlock(&pstr->oss.setup_mutex);
	पूर्ण
पूर्ण

अटल व्योम snd_pcm_oss_proc_init(काष्ठा snd_pcm *pcm)
अणु
	पूर्णांक stream;
	क्रम (stream = 0; stream < 2; ++stream) अणु
		काष्ठा snd_info_entry *entry;
		काष्ठा snd_pcm_str *pstr = &pcm->streams[stream];
		अगर (pstr->substream_count == 0)
			जारी;
		अगर ((entry = snd_info_create_card_entry(pcm->card, "oss", pstr->proc_root)) != शून्य) अणु
			entry->content = SNDRV_INFO_CONTENT_TEXT;
			entry->mode = S_IFREG | 0644;
			entry->c.text.पढ़ो = snd_pcm_oss_proc_पढ़ो;
			entry->c.text.ग_लिखो = snd_pcm_oss_proc_ग_लिखो;
			entry->निजी_data = pstr;
			अगर (snd_info_रेजिस्टर(entry) < 0) अणु
				snd_info_मुक्त_entry(entry);
				entry = शून्य;
			पूर्ण
		पूर्ण
		pstr->oss.proc_entry = entry;
	पूर्ण
पूर्ण

अटल व्योम snd_pcm_oss_proc_करोne(काष्ठा snd_pcm *pcm)
अणु
	पूर्णांक stream;
	क्रम (stream = 0; stream < 2; ++stream) अणु
		काष्ठा snd_pcm_str *pstr = &pcm->streams[stream];
		snd_info_मुक्त_entry(pstr->oss.proc_entry);
		pstr->oss.proc_entry = शून्य;
		snd_pcm_oss_proc_मुक्त_setup_list(pstr);
	पूर्ण
पूर्ण
#अन्यथा /* !CONFIG_SND_VERBOSE_PROCFS */
अटल अंतरभूत व्योम snd_pcm_oss_proc_init(काष्ठा snd_pcm *pcm)
अणु
पूर्ण
अटल अंतरभूत व्योम snd_pcm_oss_proc_करोne(काष्ठा snd_pcm *pcm)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_SND_VERBOSE_PROCFS */

/*
 *  ENTRY functions
 */

अटल स्थिर काष्ठा file_operations snd_pcm_oss_f_reg =
अणु
	.owner =	THIS_MODULE,
	.पढ़ो =		snd_pcm_oss_पढ़ो,
	.ग_लिखो =	snd_pcm_oss_ग_लिखो,
	.खोलो =		snd_pcm_oss_खोलो,
	.release =	snd_pcm_oss_release,
	.llseek =	no_llseek,
	.poll =		snd_pcm_oss_poll,
	.unlocked_ioctl =	snd_pcm_oss_ioctl,
	.compat_ioctl =	snd_pcm_oss_ioctl_compat,
	.mmap =		snd_pcm_oss_mmap,
पूर्ण;

अटल व्योम रेजिस्टर_oss_dsp(काष्ठा snd_pcm *pcm, पूर्णांक index)
अणु
	अगर (snd_रेजिस्टर_oss_device(SNDRV_OSS_DEVICE_TYPE_PCM,
				    pcm->card, index, &snd_pcm_oss_f_reg,
				    pcm) < 0) अणु
		pcm_err(pcm, "unable to register OSS PCM device %i:%i\n",
			   pcm->card->number, pcm->device);
	पूर्ण
पूर्ण

अटल पूर्णांक snd_pcm_oss_रेजिस्टर_minor(काष्ठा snd_pcm *pcm)
अणु
	pcm->oss.reg = 0;
	अगर (dsp_map[pcm->card->number] == (पूर्णांक)pcm->device) अणु
		अक्षर name[128];
		पूर्णांक duplex;
		रेजिस्टर_oss_dsp(pcm, 0);
		duplex = (pcm->streams[SNDRV_PCM_STREAM_PLAYBACK].substream_count > 0 && 
			      pcm->streams[SNDRV_PCM_STREAM_CAPTURE].substream_count && 
			      !(pcm->info_flags & SNDRV_PCM_INFO_HALF_DUPLEX));
		प्र_लिखो(name, "%s%s", pcm->name, duplex ? " (DUPLEX)" : "");
#अगर_घोषित SNDRV_OSS_INFO_DEV_AUDIO
		snd_oss_info_रेजिस्टर(SNDRV_OSS_INFO_DEV_AUDIO,
				      pcm->card->number,
				      name);
#पूर्ण_अगर
		pcm->oss.reg++;
		pcm->oss.reg_mask |= 1;
	पूर्ण
	अगर (adsp_map[pcm->card->number] == (पूर्णांक)pcm->device) अणु
		रेजिस्टर_oss_dsp(pcm, 1);
		pcm->oss.reg++;
		pcm->oss.reg_mask |= 2;
	पूर्ण

	अगर (pcm->oss.reg)
		snd_pcm_oss_proc_init(pcm);

	वापस 0;
पूर्ण

अटल पूर्णांक snd_pcm_oss_disconnect_minor(काष्ठा snd_pcm *pcm)
अणु
	अगर (pcm->oss.reg) अणु
		अगर (pcm->oss.reg_mask & 1) अणु
			pcm->oss.reg_mask &= ~1;
			snd_unरेजिस्टर_oss_device(SNDRV_OSS_DEVICE_TYPE_PCM,
						  pcm->card, 0);
		पूर्ण
		अगर (pcm->oss.reg_mask & 2) अणु
			pcm->oss.reg_mask &= ~2;
			snd_unरेजिस्टर_oss_device(SNDRV_OSS_DEVICE_TYPE_PCM,
						  pcm->card, 1);
		पूर्ण
		अगर (dsp_map[pcm->card->number] == (पूर्णांक)pcm->device) अणु
#अगर_घोषित SNDRV_OSS_INFO_DEV_AUDIO
			snd_oss_info_unरेजिस्टर(SNDRV_OSS_INFO_DEV_AUDIO, pcm->card->number);
#पूर्ण_अगर
		पूर्ण
		pcm->oss.reg = 0;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक snd_pcm_oss_unरेजिस्टर_minor(काष्ठा snd_pcm *pcm)
अणु
	snd_pcm_oss_disconnect_minor(pcm);
	snd_pcm_oss_proc_करोne(pcm);
	वापस 0;
पूर्ण

अटल काष्ठा snd_pcm_notअगरy snd_pcm_oss_notअगरy =
अणु
	.n_रेजिस्टर =	snd_pcm_oss_रेजिस्टर_minor,
	.n_disconnect = snd_pcm_oss_disconnect_minor,
	.n_unरेजिस्टर =	snd_pcm_oss_unरेजिस्टर_minor,
पूर्ण;

अटल पूर्णांक __init alsa_pcm_oss_init(व्योम)
अणु
	पूर्णांक i;
	पूर्णांक err;

	/* check device map table */
	क्रम (i = 0; i < SNDRV_CARDS; i++) अणु
		अगर (dsp_map[i] < 0 || dsp_map[i] >= SNDRV_PCM_DEVICES) अणु
			pr_err("ALSA: pcm_oss: invalid dsp_map[%d] = %d\n",
				   i, dsp_map[i]);
			dsp_map[i] = 0;
		पूर्ण
		अगर (adsp_map[i] < 0 || adsp_map[i] >= SNDRV_PCM_DEVICES) अणु
			pr_err("ALSA: pcm_oss: invalid adsp_map[%d] = %d\n",
				   i, adsp_map[i]);
			adsp_map[i] = 1;
		पूर्ण
	पूर्ण
	अगर ((err = snd_pcm_notअगरy(&snd_pcm_oss_notअगरy, 0)) < 0)
		वापस err;
	वापस 0;
पूर्ण

अटल व्योम __निकास alsa_pcm_oss_निकास(व्योम)
अणु
	snd_pcm_notअगरy(&snd_pcm_oss_notअगरy, 1);
पूर्ण

module_init(alsa_pcm_oss_init)
module_निकास(alsa_pcm_oss_निकास)
