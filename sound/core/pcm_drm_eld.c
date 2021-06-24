<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  PCM DRM helpers
 */
#समावेश <linux/export.h>
#समावेश <drm/drm_edid.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_drm_eld.h>

अटल स्थिर अचिन्हित पूर्णांक eld_rates[] = अणु
	32000,
	44100,
	48000,
	88200,
	96000,
	176400,
	192000,
पूर्ण;

अटल अचिन्हित पूर्णांक sad_max_channels(स्थिर u8 *sad)
अणु
	वापस 1 + (sad[0] & 7);
पूर्ण

अटल पूर्णांक eld_limit_rates(काष्ठा snd_pcm_hw_params *params,
			   काष्ठा snd_pcm_hw_rule *rule)
अणु
	काष्ठा snd_पूर्णांकerval *r = hw_param_पूर्णांकerval(params, rule->var);
	स्थिर काष्ठा snd_पूर्णांकerval *c;
	अचिन्हित पूर्णांक rate_mask = 7, i;
	स्थिर u8 *sad, *eld = rule->निजी;

	sad = drm_eld_sad(eld);
	अगर (sad) अणु
		c = hw_param_पूर्णांकerval_c(params, SNDRV_PCM_HW_PARAM_CHANNELS);

		क्रम (i = drm_eld_sad_count(eld); i > 0; i--, sad += 3) अणु
			अचिन्हित max_channels = sad_max_channels(sad);

			/*
			 * Exclude SADs which करो not include the
			 * requested number of channels.
			 */
			अगर (c->min <= max_channels)
				rate_mask |= sad[1];
		पूर्ण
	पूर्ण

	वापस snd_पूर्णांकerval_list(r, ARRAY_SIZE(eld_rates), eld_rates,
				 rate_mask);
पूर्ण

अटल पूर्णांक eld_limit_channels(काष्ठा snd_pcm_hw_params *params,
			      काष्ठा snd_pcm_hw_rule *rule)
अणु
	काष्ठा snd_पूर्णांकerval *c = hw_param_पूर्णांकerval(params, rule->var);
	स्थिर काष्ठा snd_पूर्णांकerval *r;
	काष्ठा snd_पूर्णांकerval t = अणु .min = 1, .max = 2, .पूर्णांकeger = 1, पूर्ण;
	अचिन्हित पूर्णांक i;
	स्थिर u8 *sad, *eld = rule->निजी;

	sad = drm_eld_sad(eld);
	अगर (sad) अणु
		अचिन्हित पूर्णांक rate_mask = 0;

		/* Convert the rate पूर्णांकerval to a mask */
		r = hw_param_पूर्णांकerval_c(params, SNDRV_PCM_HW_PARAM_RATE);
		क्रम (i = 0; i < ARRAY_SIZE(eld_rates); i++)
			अगर (r->min <= eld_rates[i] && r->max >= eld_rates[i])
				rate_mask |= BIT(i);

		क्रम (i = drm_eld_sad_count(eld); i > 0; i--, sad += 3)
			अगर (rate_mask & sad[1])
				t.max = max(t.max, sad_max_channels(sad));
	पूर्ण

	वापस snd_पूर्णांकerval_refine(c, &t);
पूर्ण

पूर्णांक snd_pcm_hw_स्थिरraपूर्णांक_eld(काष्ठा snd_pcm_runसमय *runसमय, व्योम *eld)
अणु
	पूर्णांक ret;

	ret = snd_pcm_hw_rule_add(runसमय, 0, SNDRV_PCM_HW_PARAM_RATE,
				  eld_limit_rates, eld,
				  SNDRV_PCM_HW_PARAM_CHANNELS, -1);
	अगर (ret < 0)
		वापस ret;

	ret = snd_pcm_hw_rule_add(runसमय, 0, SNDRV_PCM_HW_PARAM_CHANNELS,
				  eld_limit_channels, eld,
				  SNDRV_PCM_HW_PARAM_RATE, -1);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(snd_pcm_hw_स्थिरraपूर्णांक_eld);
