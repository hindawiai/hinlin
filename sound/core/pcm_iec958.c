<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  PCM DRM helpers
 */
#समावेश <linux/export.h>
#समावेश <linux/types.h>
#समावेश <sound/asoundef.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/pcm_iec958.h>

अटल पूर्णांक create_iec958_consumer(uपूर्णांक rate, uपूर्णांक sample_width,
				  u8 *cs, माप_प्रकार len)
अणु
	अचिन्हित पूर्णांक fs, ws;

	अगर (len < 4)
		वापस -EINVAL;

	चयन (rate) अणु
	हाल 32000:
		fs = IEC958_AES3_CON_FS_32000;
		अवरोध;
	हाल 44100:
		fs = IEC958_AES3_CON_FS_44100;
		अवरोध;
	हाल 48000:
		fs = IEC958_AES3_CON_FS_48000;
		अवरोध;
	हाल 88200:
		fs = IEC958_AES3_CON_FS_88200;
		अवरोध;
	हाल 96000:
		fs = IEC958_AES3_CON_FS_96000;
		अवरोध;
	हाल 176400:
		fs = IEC958_AES3_CON_FS_176400;
		अवरोध;
	हाल 192000:
		fs = IEC958_AES3_CON_FS_192000;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (len > 4) अणु
		चयन (sample_width) अणु
		हाल 16:
			ws = IEC958_AES4_CON_WORDLEN_20_16;
			अवरोध;
		हाल 18:
			ws = IEC958_AES4_CON_WORDLEN_22_18;
			अवरोध;
		हाल 20:
			ws = IEC958_AES4_CON_WORDLEN_20_16 |
			     IEC958_AES4_CON_MAX_WORDLEN_24;
			अवरोध;
		हाल 24:
		हाल 32: /* Assume 24-bit width क्रम 32-bit samples. */
			ws = IEC958_AES4_CON_WORDLEN_24_20 |
			     IEC958_AES4_CON_MAX_WORDLEN_24;
			अवरोध;

		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	स_रखो(cs, 0, len);

	cs[0] = IEC958_AES0_CON_NOT_COPYRIGHT | IEC958_AES0_CON_EMPHASIS_NONE;
	cs[1] = IEC958_AES1_CON_GENERAL;
	cs[2] = IEC958_AES2_CON_SOURCE_UNSPEC | IEC958_AES2_CON_CHANNEL_UNSPEC;
	cs[3] = IEC958_AES3_CON_CLOCK_1000PPM | fs;

	अगर (len > 4)
		cs[4] = ws;

	वापस len;
पूर्ण

/**
 * snd_pcm_create_iec958_consumer - create consumer क्रमmat IEC958 channel status
 * @runसमय: pcm runसमय काष्ठाure with ->rate filled in
 * @cs: channel status buffer, at least four bytes
 * @len: length of channel status buffer
 *
 * Create the consumer क्रमmat channel status data in @cs of maximum size
 * @len corresponding to the parameters of the PCM runसमय @runसमय.
 *
 * Drivers may wish to tweak the contents of the buffer after creation.
 *
 * Returns: length of buffer, or negative error code अगर something failed.
 */
पूर्णांक snd_pcm_create_iec958_consumer(काष्ठा snd_pcm_runसमय *runसमय, u8 *cs,
	माप_प्रकार len)
अणु
	वापस create_iec958_consumer(runसमय->rate,
				      snd_pcm_क्रमmat_width(runसमय->क्रमmat),
				      cs, len);
पूर्ण
EXPORT_SYMBOL(snd_pcm_create_iec958_consumer);

/**
 * snd_pcm_create_iec958_consumer_hw_params - create IEC958 channel status
 * @params: the hw_params instance क्रम extracting rate and sample क्रमmat
 * @cs: channel status buffer, at least four bytes
 * @len: length of channel status buffer
 *
 * Create the consumer क्रमmat channel status data in @cs of maximum size
 * @len corresponding to the parameters of the PCM runसमय @runसमय.
 *
 * Drivers may wish to tweak the contents of the buffer after creation.
 *
 * Returns: length of buffer, or negative error code अगर something failed.
 */
पूर्णांक snd_pcm_create_iec958_consumer_hw_params(काष्ठा snd_pcm_hw_params *params,
					     u8 *cs, माप_प्रकार len)
अणु
	वापस create_iec958_consumer(params_rate(params), params_width(params),
				      cs, len);
पूर्ण
EXPORT_SYMBOL(snd_pcm_create_iec958_consumer_hw_params);
