<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _SYSDEP_TLS_H
#घोषणा _SYSDEP_TLS_H

#अगर_घोषित __UM_HOST__

/* Change name to aव्योम conflicts with the original one from <यंत्र/ldt.h>, which
 * may be named user_desc (but in 2.4 and in header matching its API was named
 * modअगरy_ldt_ldt_s). */

प्रकार काष्ठा um_dup_user_desc अणु
	अचिन्हित पूर्णांक  entry_number;
	अचिन्हित पूर्णांक  base_addr;
	अचिन्हित पूर्णांक  limit;
	अचिन्हित पूर्णांक  seg_32bit:1;
	अचिन्हित पूर्णांक  contents:2;
	अचिन्हित पूर्णांक  पढ़ो_exec_only:1;
	अचिन्हित पूर्णांक  limit_in_pages:1;
	अचिन्हित पूर्णांक  seg_not_present:1;
	अचिन्हित पूर्णांक  useable:1;
#अगर_घोषित __x86_64__
	अचिन्हित पूर्णांक  lm:1;
#पूर्ण_अगर
पूर्ण user_desc_t;

#अन्यथा /* __UM_HOST__ */

प्रकार काष्ठा user_desc user_desc_t;

#पूर्ण_अगर /* __UM_HOST__ */

बाह्य पूर्णांक os_set_thपढ़ो_area(user_desc_t *info, पूर्णांक pid);
बाह्य पूर्णांक os_get_thपढ़ो_area(user_desc_t *info, पूर्णांक pid);

#अगर_घोषित __i386__
#घोषणा GDT_ENTRY_TLS_MIN_I386 6
#घोषणा GDT_ENTRY_TLS_MIN_X86_64 12
#पूर्ण_अगर

#पूर्ण_अगर /* _SYSDEP_TLS_H */
