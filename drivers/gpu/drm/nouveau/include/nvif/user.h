<शैली गुरु>
#अगर_अघोषित __NVIF_USER_H__
#घोषणा __NVIF_USER_H__
#समावेश <nvअगर/object.h>
काष्ठा nvअगर_device;

काष्ठा nvअगर_user अणु
	स्थिर काष्ठा nvअगर_user_func *func;
	काष्ठा nvअगर_object object;
पूर्ण;

काष्ठा nvअगर_user_func अणु
	व्योम (*करोorbell)(काष्ठा nvअगर_user *, u32 token);
	u64 (*समय)(काष्ठा nvअगर_user *);
पूर्ण;

पूर्णांक nvअगर_user_ctor(काष्ठा nvअगर_device *, स्थिर अक्षर *name);
व्योम nvअगर_user_dtor(काष्ठा nvअगर_device *);

बाह्य स्थिर काष्ठा nvअगर_user_func nvअगर_userc361;
#पूर्ण_अगर
