<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * transport_class.h - a generic container क्रम all transport classes
 *
 * Copyright (c) 2005 - James Bottomley <James.Bottomley@steeleye.com>
 */

#अगर_अघोषित _TRANSPORT_CLASS_H_
#घोषणा _TRANSPORT_CLASS_H_

#समावेश <linux/device.h>
#समावेश <linux/bug.h>
#समावेश <linux/attribute_container.h>

काष्ठा transport_container;

काष्ठा transport_class अणु
	काष्ठा class class;
	पूर्णांक (*setup)(काष्ठा transport_container *, काष्ठा device *,
		     काष्ठा device *);
	पूर्णांक (*configure)(काष्ठा transport_container *, काष्ठा device *,
			 काष्ठा device *);
	पूर्णांक (*हटाओ)(काष्ठा transport_container *, काष्ठा device *,
		      काष्ठा device *);
पूर्ण;

#घोषणा DECLARE_TRANSPORT_CLASS(cls, nm, su, rm, cfg)			\
काष्ठा transport_class cls = अणु						\
	.class = अणु							\
		.name = nm,						\
	पूर्ण,								\
	.setup = su,							\
	.हटाओ = rm,							\
	.configure = cfg,						\
पूर्ण


काष्ठा anon_transport_class अणु
	काष्ठा transport_class tclass;
	काष्ठा attribute_container container;
पूर्ण;

#घोषणा DECLARE_ANON_TRANSPORT_CLASS(cls, mtch, cfg)		\
काष्ठा anon_transport_class cls = अणु				\
	.tclass = अणु						\
		.configure = cfg,				\
	पूर्ण,							\
	. container = अणु						\
		.match = mtch,					\
	पूर्ण,							\
पूर्ण

#घोषणा class_to_transport_class(x) \
	container_of(x, काष्ठा transport_class, class)

काष्ठा transport_container अणु
	काष्ठा attribute_container ac;
	स्थिर काष्ठा attribute_group *statistics;
पूर्ण;

#घोषणा attribute_container_to_transport_container(x) \
	container_of(x, काष्ठा transport_container, ac)

व्योम transport_हटाओ_device(काष्ठा device *);
पूर्णांक transport_add_device(काष्ठा device *);
व्योम transport_setup_device(काष्ठा device *);
व्योम transport_configure_device(काष्ठा device *);
व्योम transport_destroy_device(काष्ठा device *);

अटल अंतरभूत पूर्णांक
transport_रेजिस्टर_device(काष्ठा device *dev)
अणु
	transport_setup_device(dev);
	वापस transport_add_device(dev);
पूर्ण

अटल अंतरभूत व्योम
transport_unरेजिस्टर_device(काष्ठा device *dev)
अणु
	transport_हटाओ_device(dev);
	transport_destroy_device(dev);
पूर्ण

अटल अंतरभूत पूर्णांक transport_container_रेजिस्टर(काष्ठा transport_container *tc)
अणु
	वापस attribute_container_रेजिस्टर(&tc->ac);
पूर्ण

अटल अंतरभूत व्योम transport_container_unरेजिस्टर(काष्ठा transport_container *tc)
अणु
	अगर (unlikely(attribute_container_unरेजिस्टर(&tc->ac)))
		BUG();
पूर्ण

पूर्णांक transport_class_रेजिस्टर(काष्ठा transport_class *);
पूर्णांक anon_transport_class_रेजिस्टर(काष्ठा anon_transport_class *);
व्योम transport_class_unरेजिस्टर(काष्ठा transport_class *);
व्योम anon_transport_class_unरेजिस्टर(काष्ठा anon_transport_class *);


#पूर्ण_अगर
