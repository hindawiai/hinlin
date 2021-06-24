<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/mm_types.h>
#समावेश <linux/tracepoपूर्णांक.h>

#घोषणा CREATE_TRACE_POINTS
#समावेश <trace/events/page_ref.h>

व्योम __page_ref_set(काष्ठा page *page, पूर्णांक v)
अणु
	trace_page_ref_set(page, v);
पूर्ण
EXPORT_SYMBOL(__page_ref_set);
EXPORT_TRACEPOINT_SYMBOL(page_ref_set);

व्योम __page_ref_mod(काष्ठा page *page, पूर्णांक v)
अणु
	trace_page_ref_mod(page, v);
पूर्ण
EXPORT_SYMBOL(__page_ref_mod);
EXPORT_TRACEPOINT_SYMBOL(page_ref_mod);

व्योम __page_ref_mod_and_test(काष्ठा page *page, पूर्णांक v, पूर्णांक ret)
अणु
	trace_page_ref_mod_and_test(page, v, ret);
पूर्ण
EXPORT_SYMBOL(__page_ref_mod_and_test);
EXPORT_TRACEPOINT_SYMBOL(page_ref_mod_and_test);

व्योम __page_ref_mod_and_वापस(काष्ठा page *page, पूर्णांक v, पूर्णांक ret)
अणु
	trace_page_ref_mod_and_वापस(page, v, ret);
पूर्ण
EXPORT_SYMBOL(__page_ref_mod_and_वापस);
EXPORT_TRACEPOINT_SYMBOL(page_ref_mod_and_वापस);

व्योम __page_ref_mod_unless(काष्ठा page *page, पूर्णांक v, पूर्णांक u)
अणु
	trace_page_ref_mod_unless(page, v, u);
पूर्ण
EXPORT_SYMBOL(__page_ref_mod_unless);
EXPORT_TRACEPOINT_SYMBOL(page_ref_mod_unless);

व्योम __page_ref_मुक्तze(काष्ठा page *page, पूर्णांक v, पूर्णांक ret)
अणु
	trace_page_ref_मुक्तze(page, v, ret);
पूर्ण
EXPORT_SYMBOL(__page_ref_मुक्तze);
EXPORT_TRACEPOINT_SYMBOL(page_ref_मुक्तze);

व्योम __page_ref_unमुक्तze(काष्ठा page *page, पूर्णांक v)
अणु
	trace_page_ref_unमुक्तze(page, v);
पूर्ण
EXPORT_SYMBOL(__page_ref_unमुक्तze);
EXPORT_TRACEPOINT_SYMBOL(page_ref_unमुक्तze);
