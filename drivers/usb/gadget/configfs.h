<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित USB__GADGET__CONFIGFS__H
#घोषणा USB__GADGET__CONFIGFS__H

#समावेश <linux/configfs.h>

व्योम unरेजिस्टर_gadget_item(काष्ठा config_item *item);

काष्ठा config_group *usb_os_desc_prepare_पूर्णांकerf_dir(
		काष्ठा config_group *parent,
		पूर्णांक n_पूर्णांकerf,
		काष्ठा usb_os_desc **desc,
		अक्षर **names,
		काष्ठा module *owner);

अटल अंतरभूत काष्ठा usb_os_desc *to_usb_os_desc(काष्ठा config_item *item)
अणु
	वापस container_of(to_config_group(item), काष्ठा usb_os_desc, group);
पूर्ण

#पूर्ण_अगर /*  USB__GADGET__CONFIGFS__H */
