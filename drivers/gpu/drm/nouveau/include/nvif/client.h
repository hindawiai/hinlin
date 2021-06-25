<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVIF_CLIENT_H__
#घोषणा __NVIF_CLIENT_H__

#समावेश <nvअगर/object.h>

काष्ठा nvअगर_client अणु
	काष्ठा nvअगर_object object;
	स्थिर काष्ठा nvअगर_driver *driver;
	u64 version;
	u8 route;
	bool super;
पूर्ण;

पूर्णांक  nvअगर_client_ctor(काष्ठा nvअगर_client *parent, स्थिर अक्षर *name, u64 device,
		      काष्ठा nvअगर_client *);
व्योम nvअगर_client_dtor(काष्ठा nvअगर_client *);
पूर्णांक  nvअगर_client_ioctl(काष्ठा nvअगर_client *, व्योम *, u32);
पूर्णांक  nvअगर_client_suspend(काष्ठा nvअगर_client *);
पूर्णांक  nvअगर_client_resume(काष्ठा nvअगर_client *);

/*XXX*/
#समावेश <core/client.h>
#घोषणा nvxx_client(a) (अणु                                                      \
	काष्ठा nvअगर_client *_client = (a);                                     \
	(काष्ठा nvkm_client *)_client->object.priv;                            \
पूर्ण)
#पूर्ण_अगर
