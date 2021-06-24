<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * u_phonet.h - पूर्णांकerface to Phonet
 *
 * Copyright (C) 2007-2008 by Nokia Corporation
 */

#अगर_अघोषित __U_PHONET_H
#घोषणा __U_PHONET_H

#समावेश <linux/usb/composite.h>
#समावेश <linux/usb/cdc.h>

काष्ठा f_phonet_opts अणु
	काष्ठा usb_function_instance func_inst;
	bool bound;
	काष्ठा net_device *net;
पूर्ण;

काष्ठा net_device *gphonet_setup_शेष(व्योम);
व्योम gphonet_set_gadget(काष्ठा net_device *net, काष्ठा usb_gadget *g);
पूर्णांक gphonet_रेजिस्टर_netdev(काष्ठा net_device *net);
पूर्णांक phonet_bind_config(काष्ठा usb_configuration *c, काष्ठा net_device *dev);
व्योम gphonet_cleanup(काष्ठा net_device *dev);

#पूर्ण_अगर /* __U_PHONET_H */
