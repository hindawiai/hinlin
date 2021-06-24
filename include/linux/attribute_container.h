<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * attribute_container.h - a generic container क्रम all classes
 *
 * Copyright (c) 2005 - James Bottomley <James.Bottomley@steeleye.com>
 */

#अगर_अघोषित _ATTRIBUTE_CONTAINER_H_
#घोषणा _ATTRIBUTE_CONTAINER_H_

#समावेश <linux/list.h>
#समावेश <linux/klist.h>

काष्ठा device;

काष्ठा attribute_container अणु
	काष्ठा list_head	node;
	काष्ठा klist		containers;
	काष्ठा class		*class;
	स्थिर काष्ठा attribute_group *grp;
	काष्ठा device_attribute **attrs;
	पूर्णांक (*match)(काष्ठा attribute_container *, काष्ठा device *);
#घोषणा	ATTRIBUTE_CONTAINER_NO_CLASSDEVS	0x01
	अचिन्हित दीर्घ		flags;
पूर्ण;

अटल अंतरभूत पूर्णांक
attribute_container_no_classdevs(काष्ठा attribute_container *atc)
अणु
	वापस atc->flags & ATTRIBUTE_CONTAINER_NO_CLASSDEVS;
पूर्ण

अटल अंतरभूत व्योम
attribute_container_set_no_classdevs(काष्ठा attribute_container *atc)
अणु
	atc->flags |= ATTRIBUTE_CONTAINER_NO_CLASSDEVS;
पूर्ण

पूर्णांक attribute_container_रेजिस्टर(काष्ठा attribute_container *cont);
पूर्णांक __must_check attribute_container_unरेजिस्टर(काष्ठा attribute_container *cont);
व्योम attribute_container_create_device(काष्ठा device *dev,
				       पूर्णांक (*fn)(काष्ठा attribute_container *,
						 काष्ठा device *,
						 काष्ठा device *));
व्योम attribute_container_add_device(काष्ठा device *dev,
				    पूर्णांक (*fn)(काष्ठा attribute_container *,
					      काष्ठा device *,
					      काष्ठा device *));
व्योम attribute_container_हटाओ_device(काष्ठा device *dev,
				       व्योम (*fn)(काष्ठा attribute_container *,
						  काष्ठा device *,
						  काष्ठा device *));
व्योम attribute_container_device_trigger(काष्ठा device *dev, 
					पूर्णांक (*fn)(काष्ठा attribute_container *,
						  काष्ठा device *,
						  काष्ठा device *));
पूर्णांक attribute_container_device_trigger_safe(काष्ठा device *dev,
					    पूर्णांक (*fn)(काष्ठा attribute_container *,
						      काष्ठा device *,
						      काष्ठा device *),
					    पूर्णांक (*unकरो)(काष्ठा attribute_container *,
							काष्ठा device *,
							काष्ठा device *));
व्योम attribute_container_trigger(काष्ठा device *dev, 
				 पूर्णांक (*fn)(काष्ठा attribute_container *,
					   काष्ठा device *));
पूर्णांक attribute_container_add_attrs(काष्ठा device *classdev);
पूर्णांक attribute_container_add_class_device(काष्ठा device *classdev);
पूर्णांक attribute_container_add_class_device_adapter(काष्ठा attribute_container *cont,
						 काष्ठा device *dev,
						 काष्ठा device *classdev);
व्योम attribute_container_हटाओ_attrs(काष्ठा device *classdev);
व्योम attribute_container_class_device_del(काष्ठा device *classdev);
काष्ठा attribute_container *attribute_container_classdev_to_container(काष्ठा device *);
काष्ठा device *attribute_container_find_class_device(काष्ठा attribute_container *, काष्ठा device *);
काष्ठा device_attribute **attribute_container_classdev_to_attrs(स्थिर काष्ठा device *classdev);

#पूर्ण_अगर
