<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *      names.h  --  USB name database manipulation routines
 *
 *      Copyright (C) 1999, 2000  Thomas Sailer (sailer@अगरe.ee.ethz.ch)
 *
 *	Copyright (C) 2005 Takahiro Hirofuchi
 *	       - names_मुक्त() is added.
 */

#अगर_अघोषित _NAMES_H
#घोषणा _NAMES_H

#समावेश <sys/types.h>

/* used by usbip_common.c */
बाह्य स्थिर अक्षर *names_venकरोr(u_पूर्णांक16_t venकरोrid);
बाह्य स्थिर अक्षर *names_product(u_पूर्णांक16_t venकरोrid, u_पूर्णांक16_t productid);
बाह्य स्थिर अक्षर *names_class(u_पूर्णांक8_t classid);
बाह्य स्थिर अक्षर *names_subclass(u_पूर्णांक8_t classid, u_पूर्णांक8_t subclassid);
बाह्य स्थिर अक्षर *names_protocol(u_पूर्णांक8_t classid, u_पूर्णांक8_t subclassid,
				  u_पूर्णांक8_t protocolid);
बाह्य पूर्णांक  names_init(अक्षर *n);
बाह्य व्योम names_मुक्त(व्योम);

#पूर्ण_अगर /* _NAMES_H */
