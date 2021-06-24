<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित __USB_TYPEC_ALTMODE_H__
#घोषणा __USB_TYPEC_ALTMODE_H__

#समावेश <linux/usb/typec_alपंचांगode.h>

काष्ठा bus_type;
काष्ठा typec_mux;

काष्ठा alपंचांगode अणु
	अचिन्हित पूर्णांक			id;
	काष्ठा typec_alपंचांगode		adev;
	काष्ठा typec_mux		*mux;

	क्रमागत typec_port_data		roles;

	काष्ठा attribute		*attrs[5];
	अक्षर				group_name[8];
	काष्ठा attribute_group		group;
	स्थिर काष्ठा attribute_group	*groups[2];

	काष्ठा alपंचांगode			*partner;
	काष्ठा alपंचांगode			*plug[2];
पूर्ण;

#घोषणा to_alपंचांगode(d) container_of(d, काष्ठा alपंचांगode, adev)

बाह्य काष्ठा bus_type typec_bus;
बाह्य स्थिर काष्ठा device_type typec_alपंचांगode_dev_type;

#घोषणा is_typec_alपंचांगode(_dev_) (_dev_->type == &typec_alपंचांगode_dev_type)

#पूर्ण_अगर /* __USB_TYPEC_ALTMODE_H__ */
