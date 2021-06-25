<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * hvconsole.h
 * Copyright (C) 2004 Ryan S Arnold, IBM Corporation
 *
 * LPAR console support.
 */

#अगर_अघोषित _PPC64_HVCONSOLE_H
#घोषणा _PPC64_HVCONSOLE_H
#अगर_घोषित __KERNEL__

/*
 * PSeries firmware will only send/recv up to 16 bytes of अक्षरacter data per
 * hcall.
 */
#घोषणा MAX_VIO_PUT_CHARS	16
#घोषणा SIZE_VIO_GET_CHARS	16

/*
 * Vio firmware always attempts to fetch MAX_VIO_GET_CHARS अक्षरs.  The 'count'
 * parm is included to conक्रमm to put_अक्षरs() function poपूर्णांकer ढाँचा
 */
बाह्य पूर्णांक hvc_get_अक्षरs(uपूर्णांक32_t vtermno, अक्षर *buf, पूर्णांक count);
बाह्य पूर्णांक hvc_put_अक्षरs(uपूर्णांक32_t vtermno, स्थिर अक्षर *buf, पूर्णांक count);

/* Provided by HVC VIO */
व्योम hvc_vio_init_early(व्योम);

#पूर्ण_अगर /* __KERNEL__ */
#पूर्ण_अगर /* _PPC64_HVCONSOLE_H */
