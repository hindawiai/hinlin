<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *	linux/arch/alpha/kernel/err_impl.h
 *
 *	Copyright (C) 2000 Jeff Wiedemeier (Compaq Computer Corporation)
 *
 *	Contains declarations and macros to support Alpha error handling
 * 	implementations.
 */

#समावेश <यंत्र/mce.h>

जोड़ el_बारtamp;
काष्ठा el_subpacket;
काष्ठा ev7_lf_subpackets;

काष्ठा el_subpacket_annotation अणु
	काष्ठा el_subpacket_annotation *next;
	u16 class;
	u16 type;
	u16 revision;
	अक्षर *description;
	अक्षर **annotation;
पूर्ण;
#घोषणा SUBPACKET_ANNOTATION(c, t, r, d, a) अणुशून्य, (c), (t), (r), (d), (a)पूर्ण

काष्ठा el_subpacket_handler अणु
	काष्ठा el_subpacket_handler *next;
	u16 class;
	काष्ठा el_subpacket *(*handler)(काष्ठा el_subpacket *);
पूर्ण;
#घोषणा SUBPACKET_HANDLER_INIT(c, h) अणुशून्य, (c), (h)पूर्ण

/*
 * Manipulate a field from a रेजिस्टर given it's name. defines
 * क्रम the LSB (__S - shअगरt count) and biपंचांगask (__M) are required
 *
 * EXTRACT(u, f) - extracts the field and places it at bit position 0
 * GEN_MASK(f) - creates an in-position mask क्रम the field
 */
#घोषणा EXTRACT(u, f) (((u) >> f##__S) & f##__M)
#घोषणा GEN_MASK(f) ((u64)f##__M << f##__S)

/*
 * err_common.c
 */
बाह्य अक्षर *err_prपूर्णांक_prefix;

बाह्य व्योम mchk_dump_mem(व्योम *, माप_प्रकार, अक्षर **);
बाह्य व्योम mchk_dump_logout_frame(काष्ठा el_common *);
बाह्य व्योम el_prपूर्णांक_बारtamp(जोड़ el_बारtamp *);
बाह्य व्योम el_process_subpackets(काष्ठा el_subpacket *, पूर्णांक);
बाह्य काष्ठा el_subpacket *el_process_subpacket(काष्ठा el_subpacket *);
बाह्य व्योम el_annotate_subpacket(काष्ठा el_subpacket *);
बाह्य व्योम cdl_check_console_data_log(व्योम);
बाह्य पूर्णांक cdl_रेजिस्टर_subpacket_annotation(काष्ठा el_subpacket_annotation *);
बाह्य पूर्णांक cdl_रेजिस्टर_subpacket_handler(काष्ठा el_subpacket_handler *);

/*
 * err_ev7.c
 */
बाह्य काष्ठा ev7_lf_subpackets *
ev7_collect_logout_frame_subpackets(काष्ठा el_subpacket *,
				    काष्ठा ev7_lf_subpackets *);
बाह्य व्योम ev7_रेजिस्टर_error_handlers(व्योम);
बाह्य व्योम ev7_machine_check(अचिन्हित दीर्घ, अचिन्हित दीर्घ);

/*
 * err_ev6.c
 */
बाह्य व्योम ev6_रेजिस्टर_error_handlers(व्योम);
बाह्य पूर्णांक ev6_process_logout_frame(काष्ठा el_common *, पूर्णांक);
बाह्य व्योम ev6_machine_check(अचिन्हित दीर्घ, अचिन्हित दीर्घ);

/*
 * err_marvel.c
 */
बाह्य व्योम marvel_machine_check(अचिन्हित दीर्घ, अचिन्हित दीर्घ);
बाह्य व्योम marvel_रेजिस्टर_error_handlers(व्योम);

/*
 * err_titan.c
 */
बाह्य पूर्णांक titan_process_logout_frame(काष्ठा el_common *, पूर्णांक);
बाह्य व्योम titan_machine_check(अचिन्हित दीर्घ, अचिन्हित दीर्घ);
बाह्य व्योम titan_रेजिस्टर_error_handlers(व्योम);
बाह्य पूर्णांक निजीer_process_logout_frame(काष्ठा el_common *, पूर्णांक);
बाह्य व्योम निजीer_machine_check(अचिन्हित दीर्घ, अचिन्हित दीर्घ);
