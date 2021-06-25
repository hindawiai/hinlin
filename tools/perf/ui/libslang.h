<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _PERF_UI_SLANG_H_
#घोषणा _PERF_UI_SLANG_H_ 1
/*
 * slang versions <= 2.0.6 have a "#if HAVE_LONG_LONG" that अवरोधs
 * the build अगर it isn't defined. Use the equivalent one that glibc
 * has on features.h.
 */
#समावेश <features.h>
#अगर_अघोषित HAVE_LONG_LONG
#घोषणा HAVE_LONG_LONG __GLIBC_HAVE_LONG_LONG
#पूर्ण_अगर

#अगर_घोषित HAVE_SLANG_INCLUDE_SUBसूची
#समावेश <slang/slang.h>
#अन्यथा
#समावेश <slang.h>
#पूर्ण_अगर

#अगर SLANG_VERSION < 20104
#घोषणा slsmg_म_लिखो(msg, args...) \
	SLsmg_म_लिखो((अक्षर *)(msg), ##args)
#घोषणा slsmg_भ_लिखो(msg, vargs) \
	SLsmg_भ_लिखो((अक्षर *)(msg), vargs)
#घोषणा slsmg_ग_लिखो_nstring(msg, len) \
	SLsmg_ग_लिखो_nstring((अक्षर *)(msg), len)
#घोषणा sltt_set_color(obj, name, fg, bg) \
	SLtt_set_color(obj,(अक्षर *)(name), (अक्षर *)(fg), (अक्षर *)(bg))
#अन्यथा
#घोषणा slsmg_म_लिखो SLsmg_म_लिखो
#घोषणा slsmg_भ_लिखो SLsmg_भ_लिखो
#घोषणा slsmg_ग_लिखो_nstring SLsmg_ग_लिखो_nstring
#घोषणा sltt_set_color SLtt_set_color
#पूर्ण_अगर

#घोषणा SL_KEY_UNTAB 0x1000

#पूर्ण_अगर /* _PERF_UI_SLANG_H_ */
