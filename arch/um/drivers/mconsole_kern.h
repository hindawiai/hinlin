<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2001, 2002 Jeff Dike (jdike@karaya.com)
 */

#अगर_अघोषित __MCONSOLE_KERN_H__
#घोषणा __MCONSOLE_KERN_H__

#समावेश <linux/list.h>
#समावेश "mconsole.h"

काष्ठा mconsole_entry अणु
	काष्ठा list_head list;
	काष्ठा mc_request request;
पूर्ण;

/* All these methods are called in process context. */
काष्ठा mc_device अणु
	काष्ठा list_head list;
	अक्षर *name;
	पूर्णांक (*config)(अक्षर *, अक्षर **);
	पूर्णांक (*get_config)(अक्षर *, अक्षर *, पूर्णांक, अक्षर **);
	पूर्णांक (*id)(अक्षर **, पूर्णांक *, पूर्णांक *);
	पूर्णांक (*हटाओ)(पूर्णांक, अक्षर **);
पूर्ण;

#घोषणा CONFIG_CHUNK(str, size, current, chunk, end) \
करो अणु \
	current += म_माप(chunk); \
	अगर(current >= size) \
		str = शून्य; \
	अगर(str != शून्य)अणु \
		म_नकल(str, chunk); \
		str += म_माप(chunk); \
	पूर्ण \
	अगर(end) \
		current++; \
पूर्ण जबतक(0)

#अगर_घोषित CONFIG_MCONSOLE

बाह्य व्योम mconsole_रेजिस्टर_dev(काष्ठा mc_device *new);

#अन्यथा

अटल अंतरभूत व्योम mconsole_रेजिस्टर_dev(काष्ठा mc_device *new)
अणु
पूर्ण

#पूर्ण_अगर

#पूर्ण_अगर
