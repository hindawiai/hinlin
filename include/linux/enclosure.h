<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Enclosure Services
 *
 * Copyright (C) 2008 James Bottomley <James.Bottomley@HansenPartnership.com>
 *
**-----------------------------------------------------------------------------
**
**
**-----------------------------------------------------------------------------
*/
#अगर_अघोषित _LINUX_ENCLOSURE_H_
#घोषणा _LINUX_ENCLOSURE_H_

#समावेश <linux/device.h>
#समावेश <linux/list.h>

/* A few generic types ... taken from ses-2 */
क्रमागत enclosure_component_type अणु
	ENCLOSURE_COMPONENT_DEVICE = 0x01,
	ENCLOSURE_COMPONENT_CONTROLLER_ELECTRONICS = 0x07,
	ENCLOSURE_COMPONENT_SCSI_TARGET_PORT = 0x14,
	ENCLOSURE_COMPONENT_SCSI_INITIATOR_PORT = 0x15,
	ENCLOSURE_COMPONENT_ARRAY_DEVICE = 0x17,
	ENCLOSURE_COMPONENT_SAS_EXPANDER = 0x18,
पूर्ण;

/* ses-2 common element status */
क्रमागत enclosure_status अणु
	ENCLOSURE_STATUS_UNSUPPORTED = 0,
	ENCLOSURE_STATUS_OK,
	ENCLOSURE_STATUS_CRITICAL,
	ENCLOSURE_STATUS_NON_CRITICAL,
	ENCLOSURE_STATUS_UNRECOVERABLE,
	ENCLOSURE_STATUS_NOT_INSTALLED,
	ENCLOSURE_STATUS_UNKNOWN,
	ENCLOSURE_STATUS_UNAVAILABLE,
	/* last element क्रम counting purposes */
	ENCLOSURE_STATUS_MAX
पूर्ण;

/* SFF-8485 activity light settings */
क्रमागत enclosure_component_setting अणु
	ENCLOSURE_SETTING_DISABLED = 0,
	ENCLOSURE_SETTING_ENABLED = 1,
	ENCLOSURE_SETTING_BLINK_A_ON_OFF = 2,
	ENCLOSURE_SETTING_BLINK_A_OFF_ON = 3,
	ENCLOSURE_SETTING_BLINK_B_ON_OFF = 6,
	ENCLOSURE_SETTING_BLINK_B_OFF_ON = 7,
पूर्ण;

काष्ठा enclosure_device;
काष्ठा enclosure_component;
काष्ठा enclosure_component_callbacks अणु
	व्योम (*get_status)(काष्ठा enclosure_device *,
			     काष्ठा enclosure_component *);
	पूर्णांक (*set_status)(काष्ठा enclosure_device *,
			  काष्ठा enclosure_component *,
			  क्रमागत enclosure_status);
	व्योम (*get_fault)(काष्ठा enclosure_device *,
			  काष्ठा enclosure_component *);
	पूर्णांक (*set_fault)(काष्ठा enclosure_device *,
			 काष्ठा enclosure_component *,
			 क्रमागत enclosure_component_setting);
	व्योम (*get_active)(काष्ठा enclosure_device *,
			   काष्ठा enclosure_component *);
	पूर्णांक (*set_active)(काष्ठा enclosure_device *,
			  काष्ठा enclosure_component *,
			  क्रमागत enclosure_component_setting);
	व्योम (*get_locate)(काष्ठा enclosure_device *,
			   काष्ठा enclosure_component *);
	पूर्णांक (*set_locate)(काष्ठा enclosure_device *,
			  काष्ठा enclosure_component *,
			  क्रमागत enclosure_component_setting);
	व्योम (*get_घातer_status)(काष्ठा enclosure_device *,
				 काष्ठा enclosure_component *);
	पूर्णांक (*set_घातer_status)(काष्ठा enclosure_device *,
				काष्ठा enclosure_component *,
				पूर्णांक);
	पूर्णांक (*show_id)(काष्ठा enclosure_device *, अक्षर *buf);
पूर्ण;


काष्ठा enclosure_component अणु
	व्योम *scratch;
	काष्ठा device cdev;
	काष्ठा device *dev;
	क्रमागत enclosure_component_type type;
	पूर्णांक number;
	पूर्णांक fault;
	पूर्णांक active;
	पूर्णांक locate;
	पूर्णांक slot;
	क्रमागत enclosure_status status;
	पूर्णांक घातer_status;
पूर्ण;

काष्ठा enclosure_device अणु
	व्योम *scratch;
	काष्ठा list_head node;
	काष्ठा device edev;
	काष्ठा enclosure_component_callbacks *cb;
	पूर्णांक components;
	काष्ठा enclosure_component component[];
पूर्ण;

अटल अंतरभूत काष्ठा enclosure_device *
to_enclosure_device(काष्ठा device *dev)
अणु
	वापस container_of(dev, काष्ठा enclosure_device, edev);
पूर्ण

अटल अंतरभूत काष्ठा enclosure_component *
to_enclosure_component(काष्ठा device *dev)
अणु
	वापस container_of(dev, काष्ठा enclosure_component, cdev);
पूर्ण

काष्ठा enclosure_device *
enclosure_रेजिस्टर(काष्ठा device *, स्थिर अक्षर *, पूर्णांक,
		   काष्ठा enclosure_component_callbacks *);
व्योम enclosure_unरेजिस्टर(काष्ठा enclosure_device *);
काष्ठा enclosure_component *
enclosure_component_alloc(काष्ठा enclosure_device *, अचिन्हित पूर्णांक,
			  क्रमागत enclosure_component_type, स्थिर अक्षर *);
पूर्णांक enclosure_component_रेजिस्टर(काष्ठा enclosure_component *);
पूर्णांक enclosure_add_device(काष्ठा enclosure_device *enclosure, पूर्णांक component,
			 काष्ठा device *dev);
पूर्णांक enclosure_हटाओ_device(काष्ठा enclosure_device *, काष्ठा device *);
काष्ठा enclosure_device *enclosure_find(काष्ठा device *dev,
					काष्ठा enclosure_device *start);
पूर्णांक enclosure_क्रम_each_device(पूर्णांक (*fn)(काष्ठा enclosure_device *, व्योम *),
			      व्योम *data);

#पूर्ण_अगर /* _LINUX_ENCLOSURE_H_ */
