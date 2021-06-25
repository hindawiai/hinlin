<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Greybus Host Device
 *
 * Copyright 2014-2015 Google Inc.
 * Copyright 2014-2015 Linaro Ltd.
 */

#अगर_अघोषित __HD_H
#घोषणा __HD_H

#समावेश <linux/types.h>
#समावेश <linux/device.h>

काष्ठा gb_host_device;
काष्ठा gb_message;

काष्ठा gb_hd_driver अणु
	माप_प्रकार	hd_priv_size;

	पूर्णांक (*cport_allocate)(काष्ठा gb_host_device *hd, पूर्णांक cport_id,
				अचिन्हित दीर्घ flags);
	व्योम (*cport_release)(काष्ठा gb_host_device *hd, u16 cport_id);
	पूर्णांक (*cport_enable)(काष्ठा gb_host_device *hd, u16 cport_id,
				अचिन्हित दीर्घ flags);
	पूर्णांक (*cport_disable)(काष्ठा gb_host_device *hd, u16 cport_id);
	पूर्णांक (*cport_connected)(काष्ठा gb_host_device *hd, u16 cport_id);
	पूर्णांक (*cport_flush)(काष्ठा gb_host_device *hd, u16 cport_id);
	पूर्णांक (*cport_shutकरोwn)(काष्ठा gb_host_device *hd, u16 cport_id,
				u8 phase, अचिन्हित पूर्णांक समयout);
	पूर्णांक (*cport_quiesce)(काष्ठा gb_host_device *hd, u16 cport_id,
				माप_प्रकार peer_space, अचिन्हित पूर्णांक समयout);
	पूर्णांक (*cport_clear)(काष्ठा gb_host_device *hd, u16 cport_id);

	पूर्णांक (*message_send)(काष्ठा gb_host_device *hd, u16 dest_cport_id,
			काष्ठा gb_message *message, gfp_t gfp_mask);
	व्योम (*message_cancel)(काष्ठा gb_message *message);
	पूर्णांक (*latency_tag_enable)(काष्ठा gb_host_device *hd, u16 cport_id);
	पूर्णांक (*latency_tag_disable)(काष्ठा gb_host_device *hd, u16 cport_id);
	पूर्णांक (*output)(काष्ठा gb_host_device *hd, व्योम *req, u16 size, u8 cmd,
		      bool async);
पूर्ण;

काष्ठा gb_host_device अणु
	काष्ठा device dev;
	पूर्णांक bus_id;
	स्थिर काष्ठा gb_hd_driver *driver;

	काष्ठा list_head modules;
	काष्ठा list_head connections;
	काष्ठा ida cport_id_map;

	/* Number of CPorts supported by the UniPro IP */
	माप_प्रकार num_cports;

	/* Host device buffer स्थिरraपूर्णांकs */
	माप_प्रकार buffer_size_max;

	काष्ठा gb_svc *svc;
	/* Private data क्रम the host driver */
	अचिन्हित दीर्घ hd_priv[0] __aligned(माप(s64));
पूर्ण;
#घोषणा to_gb_host_device(d) container_of(d, काष्ठा gb_host_device, dev)

पूर्णांक gb_hd_cport_reserve(काष्ठा gb_host_device *hd, u16 cport_id);
व्योम gb_hd_cport_release_reserved(काष्ठा gb_host_device *hd, u16 cport_id);
पूर्णांक gb_hd_cport_allocate(काष्ठा gb_host_device *hd, पूर्णांक cport_id,
					अचिन्हित दीर्घ flags);
व्योम gb_hd_cport_release(काष्ठा gb_host_device *hd, u16 cport_id);

काष्ठा gb_host_device *gb_hd_create(काष्ठा gb_hd_driver *driver,
					काष्ठा device *parent,
					माप_प्रकार buffer_size_max,
					माप_प्रकार num_cports);
पूर्णांक gb_hd_add(काष्ठा gb_host_device *hd);
व्योम gb_hd_del(काष्ठा gb_host_device *hd);
व्योम gb_hd_shutकरोwn(काष्ठा gb_host_device *hd);
व्योम gb_hd_put(काष्ठा gb_host_device *hd);
पूर्णांक gb_hd_output(काष्ठा gb_host_device *hd, व्योम *req, u16 size, u8 cmd,
		 bool in_irq);

पूर्णांक gb_hd_init(व्योम);
व्योम gb_hd_निकास(व्योम);

#पूर्ण_अगर	/* __HD_H */
