<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Copyright (C) 2019 NVIDIA Corporation
 */

#समावेश <linux/bug.h>

#समावेश <sound/hda_verbs.h>

#समावेश "hda.h"

व्योम tegra_hda_parse_क्रमmat(अचिन्हित पूर्णांक क्रमmat, काष्ठा tegra_hda_क्रमmat *fmt)
अणु
	अचिन्हित पूर्णांक mul, भाग, bits, channels;

	अगर (क्रमmat & AC_FMT_TYPE_NON_PCM)
		fmt->pcm = false;
	अन्यथा
		fmt->pcm = true;

	अगर (क्रमmat & AC_FMT_BASE_44K)
		fmt->sample_rate = 44100;
	अन्यथा
		fmt->sample_rate = 48000;

	mul = (क्रमmat & AC_FMT_MULT_MASK) >> AC_FMT_MULT_SHIFT;
	भाग = (क्रमmat & AC_FMT_DIV_MASK) >> AC_FMT_DIV_SHIFT;

	fmt->sample_rate *= (mul + 1) / (भाग + 1);

	चयन (क्रमmat & AC_FMT_BITS_MASK) अणु
	हाल AC_FMT_BITS_8:
		fmt->bits = 8;
		अवरोध;

	हाल AC_FMT_BITS_16:
		fmt->bits = 16;
		अवरोध;

	हाल AC_FMT_BITS_20:
		fmt->bits = 20;
		अवरोध;

	हाल AC_FMT_BITS_24:
		fmt->bits = 24;
		अवरोध;

	हाल AC_FMT_BITS_32:
		fmt->bits = 32;
		अवरोध;

	शेष:
		bits = (क्रमmat & AC_FMT_BITS_MASK) >> AC_FMT_BITS_SHIFT;
		WARN(1, "invalid number of bits: %#x\n", bits);
		fmt->bits = 8;
		अवरोध;
	पूर्ण

	channels = (क्रमmat & AC_FMT_CHAN_MASK) >> AC_FMT_CHAN_SHIFT;

	/* channels are encoded as n - 1 */
	fmt->channels = channels + 1;
पूर्ण
