<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित __SOUND_PCM_PARAMS_H
#घोषणा __SOUND_PCM_PARAMS_H

/*
 *  PCM params helpers
 *  Copyright (c) by Abramo Bagnara <abramo@alsa-project.org>
 */

#समावेश <sound/pcm.h>

पूर्णांक snd_pcm_hw_param_first(काष्ठा snd_pcm_substream *pcm, 
			   काष्ठा snd_pcm_hw_params *params,
			   snd_pcm_hw_param_t var, पूर्णांक *dir);
पूर्णांक snd_pcm_hw_param_last(काष्ठा snd_pcm_substream *pcm, 
			  काष्ठा snd_pcm_hw_params *params,
			  snd_pcm_hw_param_t var, पूर्णांक *dir);
पूर्णांक snd_pcm_hw_param_value(स्थिर काष्ठा snd_pcm_hw_params *params,
			   snd_pcm_hw_param_t var, पूर्णांक *dir);

#घोषणा SNDRV_MASK_BITS	64	/* we use so far 64bits only */
#घोषणा SNDRV_MASK_SIZE	(SNDRV_MASK_BITS / 32)
#घोषणा MASK_OFS(i)	((i) >> 5)
#घोषणा MASK_BIT(i)	(1U << ((i) & 31))

अटल अंतरभूत व्योम snd_mask_none(काष्ठा snd_mask *mask)
अणु
	स_रखो(mask, 0, माप(*mask));
पूर्ण

अटल अंतरभूत व्योम snd_mask_any(काष्ठा snd_mask *mask)
अणु
	स_रखो(mask, 0xff, SNDRV_MASK_SIZE * माप(u_पूर्णांक32_t));
पूर्ण

अटल अंतरभूत पूर्णांक snd_mask_empty(स्थिर काष्ठा snd_mask *mask)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < SNDRV_MASK_SIZE; i++)
		अगर (mask->bits[i])
			वापस 0;
	वापस 1;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक snd_mask_min(स्थिर काष्ठा snd_mask *mask)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < SNDRV_MASK_SIZE; i++) अणु
		अगर (mask->bits[i])
			वापस __ffs(mask->bits[i]) + (i << 5);
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक snd_mask_max(स्थिर काष्ठा snd_mask *mask)
अणु
	पूर्णांक i;
	क्रम (i = SNDRV_MASK_SIZE - 1; i >= 0; i--) अणु
		अगर (mask->bits[i])
			वापस __fls(mask->bits[i]) + (i << 5);
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम snd_mask_set(काष्ठा snd_mask *mask, अचिन्हित पूर्णांक val)
अणु
	mask->bits[MASK_OFS(val)] |= MASK_BIT(val);
पूर्ण

/* Most of drivers need only this one */
अटल अंतरभूत व्योम snd_mask_set_क्रमmat(काष्ठा snd_mask *mask,
				       snd_pcm_क्रमmat_t क्रमmat)
अणु
	snd_mask_set(mask, (__क्रमce अचिन्हित पूर्णांक)क्रमmat);
पूर्ण

अटल अंतरभूत व्योम snd_mask_reset(काष्ठा snd_mask *mask, अचिन्हित पूर्णांक val)
अणु
	mask->bits[MASK_OFS(val)] &= ~MASK_BIT(val);
पूर्ण

अटल अंतरभूत व्योम snd_mask_set_range(काष्ठा snd_mask *mask,
				      अचिन्हित पूर्णांक from, अचिन्हित पूर्णांक to)
अणु
	अचिन्हित पूर्णांक i;
	क्रम (i = from; i <= to; i++)
		mask->bits[MASK_OFS(i)] |= MASK_BIT(i);
पूर्ण

अटल अंतरभूत व्योम snd_mask_reset_range(काष्ठा snd_mask *mask,
					अचिन्हित पूर्णांक from, अचिन्हित पूर्णांक to)
अणु
	अचिन्हित पूर्णांक i;
	क्रम (i = from; i <= to; i++)
		mask->bits[MASK_OFS(i)] &= ~MASK_BIT(i);
पूर्ण

अटल अंतरभूत व्योम snd_mask_leave(काष्ठा snd_mask *mask, अचिन्हित पूर्णांक val)
अणु
	अचिन्हित पूर्णांक v;
	v = mask->bits[MASK_OFS(val)] & MASK_BIT(val);
	snd_mask_none(mask);
	mask->bits[MASK_OFS(val)] = v;
पूर्ण

अटल अंतरभूत व्योम snd_mask_पूर्णांकersect(काष्ठा snd_mask *mask,
				      स्थिर काष्ठा snd_mask *v)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < SNDRV_MASK_SIZE; i++)
		mask->bits[i] &= v->bits[i];
पूर्ण

अटल अंतरभूत पूर्णांक snd_mask_eq(स्थिर काष्ठा snd_mask *mask,
			      स्थिर काष्ठा snd_mask *v)
अणु
	वापस ! स_भेद(mask, v, SNDRV_MASK_SIZE * माप(u_पूर्णांक32_t));
पूर्ण

अटल अंतरभूत व्योम snd_mask_copy(काष्ठा snd_mask *mask,
				 स्थिर काष्ठा snd_mask *v)
अणु
	*mask = *v;
पूर्ण

अटल अंतरभूत पूर्णांक snd_mask_test(स्थिर काष्ठा snd_mask *mask, अचिन्हित पूर्णांक val)
अणु
	वापस mask->bits[MASK_OFS(val)] & MASK_BIT(val);
पूर्ण

/* Most of drivers need only this one */
अटल अंतरभूत पूर्णांक snd_mask_test_क्रमmat(स्थिर काष्ठा snd_mask *mask,
				       snd_pcm_क्रमmat_t क्रमmat)
अणु
	वापस snd_mask_test(mask, (__क्रमce अचिन्हित पूर्णांक)क्रमmat);
पूर्ण

अटल अंतरभूत पूर्णांक snd_mask_single(स्थिर काष्ठा snd_mask *mask)
अणु
	पूर्णांक i, c = 0;
	क्रम (i = 0; i < SNDRV_MASK_SIZE; i++) अणु
		अगर (! mask->bits[i])
			जारी;
		अगर (mask->bits[i] & (mask->bits[i] - 1))
			वापस 0;
		अगर (c)
			वापस 0;
		c++;
	पूर्ण
	वापस 1;
पूर्ण

अटल अंतरभूत पूर्णांक snd_mask_refine(काष्ठा snd_mask *mask,
				  स्थिर काष्ठा snd_mask *v)
अणु
	काष्ठा snd_mask old;
	snd_mask_copy(&old, mask);
	snd_mask_पूर्णांकersect(mask, v);
	अगर (snd_mask_empty(mask))
		वापस -EINVAL;
	वापस !snd_mask_eq(mask, &old);
पूर्ण

अटल अंतरभूत पूर्णांक snd_mask_refine_first(काष्ठा snd_mask *mask)
अणु
	अगर (snd_mask_single(mask))
		वापस 0;
	snd_mask_leave(mask, snd_mask_min(mask));
	वापस 1;
पूर्ण

अटल अंतरभूत पूर्णांक snd_mask_refine_last(काष्ठा snd_mask *mask)
अणु
	अगर (snd_mask_single(mask))
		वापस 0;
	snd_mask_leave(mask, snd_mask_max(mask));
	वापस 1;
पूर्ण

अटल अंतरभूत पूर्णांक snd_mask_refine_min(काष्ठा snd_mask *mask, अचिन्हित पूर्णांक val)
अणु
	अगर (snd_mask_min(mask) >= val)
		वापस 0;
	snd_mask_reset_range(mask, 0, val - 1);
	अगर (snd_mask_empty(mask))
		वापस -EINVAL;
	वापस 1;
पूर्ण

अटल अंतरभूत पूर्णांक snd_mask_refine_max(काष्ठा snd_mask *mask, अचिन्हित पूर्णांक val)
अणु
	अगर (snd_mask_max(mask) <= val)
		वापस 0;
	snd_mask_reset_range(mask, val + 1, SNDRV_MASK_BITS);
	अगर (snd_mask_empty(mask))
		वापस -EINVAL;
	वापस 1;
पूर्ण

अटल अंतरभूत पूर्णांक snd_mask_refine_set(काष्ठा snd_mask *mask, अचिन्हित पूर्णांक val)
अणु
	पूर्णांक changed;
	changed = !snd_mask_single(mask);
	snd_mask_leave(mask, val);
	अगर (snd_mask_empty(mask))
		वापस -EINVAL;
	वापस changed;
पूर्ण

अटल अंतरभूत पूर्णांक snd_mask_value(स्थिर काष्ठा snd_mask *mask)
अणु
	वापस snd_mask_min(mask);
पूर्ण

अटल अंतरभूत व्योम snd_पूर्णांकerval_any(काष्ठा snd_पूर्णांकerval *i)
अणु
	i->min = 0;
	i->खोलोmin = 0;
	i->max = अच_पूर्णांक_उच्च;
	i->खोलोmax = 0;
	i->पूर्णांकeger = 0;
	i->empty = 0;
पूर्ण

अटल अंतरभूत व्योम snd_पूर्णांकerval_none(काष्ठा snd_पूर्णांकerval *i)
अणु
	i->empty = 1;
पूर्ण

अटल अंतरभूत पूर्णांक snd_पूर्णांकerval_checkempty(स्थिर काष्ठा snd_पूर्णांकerval *i)
अणु
	वापस (i->min > i->max ||
		(i->min == i->max && (i->खोलोmin || i->खोलोmax)));
पूर्ण

अटल अंतरभूत पूर्णांक snd_पूर्णांकerval_empty(स्थिर काष्ठा snd_पूर्णांकerval *i)
अणु
	वापस i->empty;
पूर्ण

अटल अंतरभूत पूर्णांक snd_पूर्णांकerval_single(स्थिर काष्ठा snd_पूर्णांकerval *i)
अणु
	वापस (i->min == i->max || 
		(i->min + 1 == i->max && (i->खोलोmin || i->खोलोmax)));
पूर्ण

अटल अंतरभूत पूर्णांक snd_पूर्णांकerval_value(स्थिर काष्ठा snd_पूर्णांकerval *i)
अणु
	अगर (i->खोलोmin && !i->खोलोmax)
		वापस i->max;
	वापस i->min;
पूर्ण

अटल अंतरभूत पूर्णांक snd_पूर्णांकerval_min(स्थिर काष्ठा snd_पूर्णांकerval *i)
अणु
	वापस i->min;
पूर्ण

अटल अंतरभूत पूर्णांक snd_पूर्णांकerval_max(स्थिर काष्ठा snd_पूर्णांकerval *i)
अणु
	अचिन्हित पूर्णांक v;
	v = i->max;
	अगर (i->खोलोmax)
		v--;
	वापस v;
पूर्ण

अटल अंतरभूत पूर्णांक snd_पूर्णांकerval_test(स्थिर काष्ठा snd_पूर्णांकerval *i, अचिन्हित पूर्णांक val)
अणु
	वापस !((i->min > val || (i->min == val && i->खोलोmin) ||
		  i->max < val || (i->max == val && i->खोलोmax)));
पूर्ण

अटल अंतरभूत व्योम snd_पूर्णांकerval_copy(काष्ठा snd_पूर्णांकerval *d, स्थिर काष्ठा snd_पूर्णांकerval *s)
अणु
	*d = *s;
पूर्ण

अटल अंतरभूत पूर्णांक snd_पूर्णांकerval_setपूर्णांकeger(काष्ठा snd_पूर्णांकerval *i)
अणु
	अगर (i->पूर्णांकeger)
		वापस 0;
	अगर (i->खोलोmin && i->खोलोmax && i->min == i->max)
		वापस -EINVAL;
	i->पूर्णांकeger = 1;
	वापस 1;
पूर्ण

अटल अंतरभूत पूर्णांक snd_पूर्णांकerval_eq(स्थिर काष्ठा snd_पूर्णांकerval *i1, स्थिर काष्ठा snd_पूर्णांकerval *i2)
अणु
	अगर (i1->empty)
		वापस i2->empty;
	अगर (i2->empty)
		वापस i1->empty;
	वापस i1->min == i2->min && i1->खोलोmin == i2->खोलोmin &&
		i1->max == i2->max && i1->खोलोmax == i2->खोलोmax;
पूर्ण

/**
 * params_access - get the access type from the hw params
 * @p: hw params
 */
अटल अंतरभूत snd_pcm_access_t params_access(स्थिर काष्ठा snd_pcm_hw_params *p)
अणु
	वापस (__क्रमce snd_pcm_access_t)snd_mask_min(hw_param_mask_c(p,
		SNDRV_PCM_HW_PARAM_ACCESS));
पूर्ण

/**
 * params_क्रमmat - get the sample क्रमmat from the hw params
 * @p: hw params
 */
अटल अंतरभूत snd_pcm_क्रमmat_t params_क्रमmat(स्थिर काष्ठा snd_pcm_hw_params *p)
अणु
	वापस (__क्रमce snd_pcm_क्रमmat_t)snd_mask_min(hw_param_mask_c(p,
		SNDRV_PCM_HW_PARAM_FORMAT));
पूर्ण

/**
 * params_subक्रमmat - get the sample subक्रमmat from the hw params
 * @p: hw params
 */
अटल अंतरभूत snd_pcm_subक्रमmat_t
params_subक्रमmat(स्थिर काष्ठा snd_pcm_hw_params *p)
अणु
	वापस (__क्रमce snd_pcm_subक्रमmat_t)snd_mask_min(hw_param_mask_c(p,
		SNDRV_PCM_HW_PARAM_SUBFORMAT));
पूर्ण

/**
 * params_period_bytes - get the period size (in bytes) from the hw params
 * @p: hw params
 */
अटल अंतरभूत अचिन्हित पूर्णांक
params_period_bytes(स्थिर काष्ठा snd_pcm_hw_params *p)
अणु
	वापस hw_param_पूर्णांकerval_c(p, SNDRV_PCM_HW_PARAM_PERIOD_BYTES)->min;
पूर्ण

/**
 * params_width - get the number of bits of the sample क्रमmat from the hw params
 * @p: hw params
 *
 * This function वापसs the number of bits per sample that the selected sample
 * क्रमmat of the hw params has.
 */
अटल अंतरभूत पूर्णांक params_width(स्थिर काष्ठा snd_pcm_hw_params *p)
अणु
	वापस snd_pcm_क्रमmat_width(params_क्रमmat(p));
पूर्ण

/*
 * params_physical_width - get the storage size of the sample क्रमmat from the hw params
 * @p: hw params
 *
 * This functions वापसs the number of bits per sample that the selected sample
 * क्रमmat of the hw params takes up in memory. This will be equal or larger than
 * params_width().
 */
अटल अंतरभूत पूर्णांक params_physical_width(स्थिर काष्ठा snd_pcm_hw_params *p)
अणु
	वापस snd_pcm_क्रमmat_physical_width(params_क्रमmat(p));
पूर्ण

अटल अंतरभूत व्योम
params_set_क्रमmat(काष्ठा snd_pcm_hw_params *p, snd_pcm_क्रमmat_t fmt)
अणु
	snd_mask_set_क्रमmat(hw_param_mask(p, SNDRV_PCM_HW_PARAM_FORMAT), fmt);
पूर्ण

#पूर्ण_अगर /* __SOUND_PCM_PARAMS_H */
