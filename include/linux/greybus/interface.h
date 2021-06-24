<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Greybus Interface Block code
 *
 * Copyright 2014 Google Inc.
 * Copyright 2014 Linaro Ltd.
 */

#अगर_अघोषित __INTERFACE_H
#घोषणा __INTERFACE_H

#समावेश <linux/types.h>
#समावेश <linux/device.h>

क्रमागत gb_पूर्णांकerface_type अणु
	GB_INTERFACE_TYPE_INVALID = 0,
	GB_INTERFACE_TYPE_UNKNOWN,
	GB_INTERFACE_TYPE_DUMMY,
	GB_INTERFACE_TYPE_UNIPRO,
	GB_INTERFACE_TYPE_GREYBUS,
पूर्ण;

#घोषणा GB_INTERFACE_QUIRK_NO_CPORT_FEATURES		BIT(0)
#घोषणा GB_INTERFACE_QUIRK_NO_INIT_STATUS		BIT(1)
#घोषणा GB_INTERFACE_QUIRK_NO_GMP_IDS			BIT(2)
#घोषणा GB_INTERFACE_QUIRK_FORCED_DISABLE		BIT(3)
#घोषणा GB_INTERFACE_QUIRK_LEGACY_MODE_SWITCH		BIT(4)
#घोषणा GB_INTERFACE_QUIRK_NO_BUNDLE_ACTIVATE		BIT(5)
#घोषणा GB_INTERFACE_QUIRK_NO_PM			BIT(6)

काष्ठा gb_पूर्णांकerface अणु
	काष्ठा device dev;
	काष्ठा gb_control *control;

	काष्ठा list_head bundles;
	काष्ठा list_head module_node;
	काष्ठा list_head manअगरest_descs;
	u8 पूर्णांकerface_id;	/* Physical location within the Enकरो */
	u8 device_id;
	u8 features;		/* Feature flags set in the manअगरest */

	क्रमागत gb_पूर्णांकerface_type type;

	u32 ddbl1_manufacturer_id;
	u32 ddbl1_product_id;
	u32 venकरोr_id;
	u32 product_id;
	u64 serial_number;

	काष्ठा gb_host_device *hd;
	काष्ठा gb_module *module;

	अचिन्हित दीर्घ quirks;

	काष्ठा mutex mutex;

	bool disconnected;

	bool ejected;
	bool हटाओd;
	bool active;
	bool enabled;
	bool mode_चयन;
	bool dme_पढ़ो;

	काष्ठा work_काष्ठा mode_चयन_work;
	काष्ठा completion mode_चयन_completion;
पूर्ण;
#घोषणा to_gb_पूर्णांकerface(d) container_of(d, काष्ठा gb_पूर्णांकerface, dev)

काष्ठा gb_पूर्णांकerface *gb_पूर्णांकerface_create(काष्ठा gb_module *module,
					 u8 पूर्णांकerface_id);
पूर्णांक gb_पूर्णांकerface_activate(काष्ठा gb_पूर्णांकerface *पूर्णांकf);
व्योम gb_पूर्णांकerface_deactivate(काष्ठा gb_पूर्णांकerface *पूर्णांकf);
पूर्णांक gb_पूर्णांकerface_enable(काष्ठा gb_पूर्णांकerface *पूर्णांकf);
व्योम gb_पूर्णांकerface_disable(काष्ठा gb_पूर्णांकerface *पूर्णांकf);
पूर्णांक gb_पूर्णांकerface_add(काष्ठा gb_पूर्णांकerface *पूर्णांकf);
व्योम gb_पूर्णांकerface_del(काष्ठा gb_पूर्णांकerface *पूर्णांकf);
व्योम gb_पूर्णांकerface_put(काष्ठा gb_पूर्णांकerface *पूर्णांकf);
व्योम gb_पूर्णांकerface_mailbox_event(काष्ठा gb_पूर्णांकerface *पूर्णांकf, u16 result,
								u32 mailbox);

पूर्णांक gb_पूर्णांकerface_request_mode_चयन(काष्ठा gb_पूर्णांकerface *पूर्णांकf);

#पूर्ण_अगर /* __INTERFACE_H */
