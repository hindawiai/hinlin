<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVIF_PARENT_H__
#घोषणा __NVIF_PARENT_H__
#समावेश <nvअगर/os.h>
काष्ठा nvअगर_object;

काष्ठा nvअगर_parent अणु
	स्थिर काष्ठा nvअगर_parent_func अणु
		व्योम (*debugf)(काष्ठा nvअगर_object *, स्थिर अक्षर *fmt, ...) __म_लिखो(2, 3);
		व्योम (*errorf)(काष्ठा nvअगर_object *, स्थिर अक्षर *fmt, ...) __म_लिखो(2, 3);
	पूर्ण *func;
पूर्ण;

अटल अंतरभूत व्योम
nvअगर_parent_dtor(काष्ठा nvअगर_parent *parent)
अणु
	parent->func = शून्य;
पूर्ण

अटल अंतरभूत व्योम
nvअगर_parent_ctor(स्थिर काष्ठा nvअगर_parent_func *func, काष्ठा nvअगर_parent *parent)
अणु
	parent->func = func;
पूर्ण
#पूर्ण_अगर
