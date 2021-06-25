<शैली गुरु>
/*
 * ARAnyM hardware support via Native Features (natfeats)
 *
 * Copyright (c) 2005 Petr Stehlik of ARAnyM dev team
 *
 * This software may be used and distributed according to the terms of
 * the GNU General Public License (GPL), incorporated herein by reference.
 */
#समावेश <linux/compiler.h>

#अगर_अघोषित _NATFEAT_H
#घोषणा _NATFEAT_H

दीर्घ nf_get_id(स्थिर अक्षर *feature_name);
दीर्घ nf_call(दीर्घ id, ...);

व्योम nf_init(व्योम);
व्योम nf_shutकरोwn(व्योम);

व्योम nfprपूर्णांक(स्थिर अक्षर *fmt, ...)
	__म_लिखो(1, 2);

# endअगर /* _NATFEAT_H */
