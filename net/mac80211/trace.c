<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* bug in tracepoपूर्णांक.h, it should include this */
#समावेश <linux/module.h>

/* sparse isn't too happy with all macros... */
#अगर_अघोषित __CHECKER__
#समावेश <net/cfg80211.h>
#समावेश "driver-ops.h"
#समावेश "debug.h"
#घोषणा CREATE_TRACE_POINTS
#समावेश "trace.h"
#समावेश "trace_msg.h"

#अगर_घोषित CONFIG_MAC80211_MESSAGE_TRACING
व्योम __sdata_info(स्थिर अक्षर *fmt, ...)
अणु
	काष्ठा va_क्रमmat vaf = अणु
		.fmt = fmt,
	पूर्ण;
	बहु_सूची args;

	बहु_शुरू(args, fmt);
	vaf.va = &args;

	pr_info("%pV", &vaf);
	trace_mac80211_info(&vaf);
	बहु_पूर्ण(args);
पूर्ण

व्योम __sdata_dbg(bool prपूर्णांक, स्थिर अक्षर *fmt, ...)
अणु
	काष्ठा va_क्रमmat vaf = अणु
		.fmt = fmt,
	पूर्ण;
	बहु_सूची args;

	बहु_शुरू(args, fmt);
	vaf.va = &args;

	अगर (prपूर्णांक)
		pr_debug("%pV", &vaf);
	trace_mac80211_dbg(&vaf);
	बहु_पूर्ण(args);
पूर्ण

व्योम __sdata_err(स्थिर अक्षर *fmt, ...)
अणु
	काष्ठा va_क्रमmat vaf = अणु
		.fmt = fmt,
	पूर्ण;
	बहु_सूची args;

	बहु_शुरू(args, fmt);
	vaf.va = &args;

	pr_err("%pV", &vaf);
	trace_mac80211_err(&vaf);
	बहु_पूर्ण(args);
पूर्ण

व्योम __wiphy_dbg(काष्ठा wiphy *wiphy, bool prपूर्णांक, स्थिर अक्षर *fmt, ...)
अणु
	काष्ठा va_क्रमmat vaf = अणु
		.fmt = fmt,
	पूर्ण;
	बहु_सूची args;

	बहु_शुरू(args, fmt);
	vaf.va = &args;

	अगर (prपूर्णांक)
		wiphy_dbg(wiphy, "%pV", &vaf);
	trace_mac80211_dbg(&vaf);
	बहु_पूर्ण(args);
पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर
