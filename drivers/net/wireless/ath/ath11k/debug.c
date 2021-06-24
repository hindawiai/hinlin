<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause-Clear
/*
 * Copyright (c) 2018-2019 The Linux Foundation. All rights reserved.
 */

#समावेश <linux/vदो_स्मृति.h>
#समावेश "core.h"
#समावेश "debug.h"

व्योम ath11k_info(काष्ठा ath11k_base *ab, स्थिर अक्षर *fmt, ...)
अणु
	काष्ठा va_क्रमmat vaf = अणु
		.fmt = fmt,
	पूर्ण;
	बहु_सूची args;

	बहु_शुरू(args, fmt);
	vaf.va = &args;
	dev_info(ab->dev, "%pV", &vaf);
	/* TODO: Trace the log */
	बहु_पूर्ण(args);
पूर्ण
EXPORT_SYMBOL(ath11k_info);

व्योम ath11k_err(काष्ठा ath11k_base *ab, स्थिर अक्षर *fmt, ...)
अणु
	काष्ठा va_क्रमmat vaf = अणु
		.fmt = fmt,
	पूर्ण;
	बहु_सूची args;

	बहु_शुरू(args, fmt);
	vaf.va = &args;
	dev_err(ab->dev, "%pV", &vaf);
	/* TODO: Trace the log */
	बहु_पूर्ण(args);
पूर्ण
EXPORT_SYMBOL(ath11k_err);

व्योम ath11k_warn(काष्ठा ath11k_base *ab, स्थिर अक्षर *fmt, ...)
अणु
	काष्ठा va_क्रमmat vaf = अणु
		.fmt = fmt,
	पूर्ण;
	बहु_सूची args;

	बहु_शुरू(args, fmt);
	vaf.va = &args;
	dev_warn_ratelimited(ab->dev, "%pV", &vaf);
	/* TODO: Trace the log */
	बहु_पूर्ण(args);
पूर्ण
EXPORT_SYMBOL(ath11k_warn);

#अगर_घोषित CONFIG_ATH11K_DEBUG

व्योम __ath11k_dbg(काष्ठा ath11k_base *ab, क्रमागत ath11k_debug_mask mask,
		  स्थिर अक्षर *fmt, ...)
अणु
	काष्ठा va_क्रमmat vaf;
	बहु_सूची args;

	बहु_शुरू(args, fmt);

	vaf.fmt = fmt;
	vaf.va = &args;

	अगर (ath11k_debug_mask & mask)
		dev_prपूर्णांकk(KERN_DEBUG, ab->dev, "%pV", &vaf);

	/* TODO: trace log */

	बहु_पूर्ण(args);
पूर्ण
EXPORT_SYMBOL(__ath11k_dbg);

व्योम ath11k_dbg_dump(काष्ठा ath11k_base *ab,
		     क्रमागत ath11k_debug_mask mask,
		     स्थिर अक्षर *msg, स्थिर अक्षर *prefix,
		     स्थिर व्योम *buf, माप_प्रकार len)
अणु
	अक्षर linebuf[256];
	माप_प्रकार linebuflen;
	स्थिर व्योम *ptr;

	अगर (ath11k_debug_mask & mask) अणु
		अगर (msg)
			__ath11k_dbg(ab, mask, "%s\n", msg);

		क्रम (ptr = buf; (ptr - buf) < len; ptr += 16) अणु
			linebuflen = 0;
			linebuflen += scnम_लिखो(linebuf + linebuflen,
						माप(linebuf) - linebuflen,
						"%s%08x: ",
						(prefix ? prefix : ""),
						(अचिन्हित पूर्णांक)(ptr - buf));
			hex_dump_to_buffer(ptr, len - (ptr - buf), 16, 1,
					   linebuf + linebuflen,
					   माप(linebuf) - linebuflen, true);
			dev_prपूर्णांकk(KERN_DEBUG, ab->dev, "%s\n", linebuf);
		पूर्ण
	पूर्ण
पूर्ण
EXPORT_SYMBOL(ath11k_dbg_dump);

#पूर्ण_अगर /* CONFIG_ATH11K_DEBUG */
