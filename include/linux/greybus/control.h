<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Greybus CPort control protocol
 *
 * Copyright 2015 Google Inc.
 * Copyright 2015 Linaro Ltd.
 */

#अगर_अघोषित __CONTROL_H
#घोषणा __CONTROL_H

#समावेश <linux/types.h>
#समावेश <linux/device.h>

काष्ठा gb_control अणु
	काष्ठा device dev;
	काष्ठा gb_पूर्णांकerface *पूर्णांकf;

	काष्ठा gb_connection *connection;

	u8 protocol_major;
	u8 protocol_minor;

	bool has_bundle_activate;
	bool has_bundle_version;

	अक्षर *venकरोr_string;
	अक्षर *product_string;
पूर्ण;
#घोषणा to_gb_control(d) container_of(d, काष्ठा gb_control, dev)

काष्ठा gb_control *gb_control_create(काष्ठा gb_पूर्णांकerface *पूर्णांकf);
पूर्णांक gb_control_enable(काष्ठा gb_control *control);
व्योम gb_control_disable(काष्ठा gb_control *control);
पूर्णांक gb_control_suspend(काष्ठा gb_control *control);
पूर्णांक gb_control_resume(काष्ठा gb_control *control);
पूर्णांक gb_control_add(काष्ठा gb_control *control);
व्योम gb_control_del(काष्ठा gb_control *control);
काष्ठा gb_control *gb_control_get(काष्ठा gb_control *control);
व्योम gb_control_put(काष्ठा gb_control *control);

पूर्णांक gb_control_get_bundle_versions(काष्ठा gb_control *control);
पूर्णांक gb_control_connected_operation(काष्ठा gb_control *control, u16 cport_id);
पूर्णांक gb_control_disconnected_operation(काष्ठा gb_control *control, u16 cport_id);
पूर्णांक gb_control_disconnecting_operation(काष्ठा gb_control *control,
				       u16 cport_id);
पूर्णांक gb_control_mode_चयन_operation(काष्ठा gb_control *control);
व्योम gb_control_mode_चयन_prepare(काष्ठा gb_control *control);
व्योम gb_control_mode_चयन_complete(काष्ठा gb_control *control);
पूर्णांक gb_control_get_manअगरest_size_operation(काष्ठा gb_पूर्णांकerface *पूर्णांकf);
पूर्णांक gb_control_get_manअगरest_operation(काष्ठा gb_पूर्णांकerface *पूर्णांकf, व्योम *manअगरest,
				      माप_प्रकार size);
पूर्णांक gb_control_bundle_suspend(काष्ठा gb_control *control, u8 bundle_id);
पूर्णांक gb_control_bundle_resume(काष्ठा gb_control *control, u8 bundle_id);
पूर्णांक gb_control_bundle_deactivate(काष्ठा gb_control *control, u8 bundle_id);
पूर्णांक gb_control_bundle_activate(काष्ठा gb_control *control, u8 bundle_id);
पूर्णांक gb_control_पूर्णांकerface_suspend_prepare(काष्ठा gb_control *control);
पूर्णांक gb_control_पूर्णांकerface_deactivate_prepare(काष्ठा gb_control *control);
पूर्णांक gb_control_पूर्णांकerface_hibernate_पात(काष्ठा gb_control *control);
#पूर्ण_अगर /* __CONTROL_H */
