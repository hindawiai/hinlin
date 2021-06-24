<शैली गुरु>
/*
 * This file is provided under a dual BSD/GPLv2 license.  When using or
 *   redistributing this file, you may करो so under either license.
 *
 *   GPL LICENSE SUMMARY
 *
 *   Copyright (C) 2015 EMC Corporation. All Rights Reserved.
 *   Copyright (C) 2016 T-Platक्रमms. All Rights Reserved.
 *
 *   This program is मुक्त software; you can redistribute it and/or modअगरy
 *   it under the terms of version 2 of the GNU General Public License as
 *   published by the Free Software Foundation.
 *
 *   This program is distributed in the hope that it will be useful, but
 *   WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *   General Public License क्रम more details.
 *
 *   BSD LICENSE
 *
 *   Copyright (C) 2015 EMC Corporation. All Rights Reserved.
 *   Copyright (C) 2016 T-Platक्रमms. All Rights Reserved.
 *
 *   Redistribution and use in source and binary क्रमms, with or without
 *   modअगरication, are permitted provided that the following conditions
 *   are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary क्रमm must reproduce the above copy
 *       notice, this list of conditions and the following disclaimer in
 *       the करोcumentation and/or other materials provided with the
 *       distribution.
 *     * Neither the name of Intel Corporation nor the names of its
 *       contributors may be used to enकरोrse or promote products derived
 *       from this software without specअगरic prior written permission.
 *
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *   A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *   OWNER OR CONTRIBUTORS BE LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL,
 *   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *   LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *   DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *   THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *   OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * PCIe NTB Linux driver
 *
 * Contact Inक्रमmation:
 * Allen Hubbe <Allen.Hubbe@emc.com>
 */

#समावेश <linux/device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>

#समावेश <linux/ntb.h>
#समावेश <linux/pci.h>

#घोषणा DRIVER_NAME			"ntb"
#घोषणा DRIVER_DESCRIPTION		"PCIe NTB Driver Framework"

#घोषणा DRIVER_VERSION			"1.0"
#घोषणा DRIVER_RELDATE			"24 March 2015"
#घोषणा DRIVER_AUTHOR			"Allen Hubbe <Allen.Hubbe@emc.com>"

MODULE_LICENSE("Dual BSD/GPL");
MODULE_VERSION(DRIVER_VERSION);
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESCRIPTION);

अटल काष्ठा bus_type ntb_bus;
अटल व्योम ntb_dev_release(काष्ठा device *dev);

पूर्णांक __ntb_रेजिस्टर_client(काष्ठा ntb_client *client, काष्ठा module *mod,
			  स्थिर अक्षर *mod_name)
अणु
	अगर (!client)
		वापस -EINVAL;
	अगर (!ntb_client_ops_is_valid(&client->ops))
		वापस -EINVAL;

	स_रखो(&client->drv, 0, माप(client->drv));
	client->drv.bus = &ntb_bus;
	client->drv.name = mod_name;
	client->drv.owner = mod;

	वापस driver_रेजिस्टर(&client->drv);
पूर्ण
EXPORT_SYMBOL(__ntb_रेजिस्टर_client);

व्योम ntb_unरेजिस्टर_client(काष्ठा ntb_client *client)
अणु
	driver_unरेजिस्टर(&client->drv);
पूर्ण
EXPORT_SYMBOL(ntb_unरेजिस्टर_client);

पूर्णांक ntb_रेजिस्टर_device(काष्ठा ntb_dev *ntb)
अणु
	अगर (!ntb)
		वापस -EINVAL;
	अगर (!ntb->pdev)
		वापस -EINVAL;
	अगर (!ntb->ops)
		वापस -EINVAL;
	अगर (!ntb_dev_ops_is_valid(ntb->ops))
		वापस -EINVAL;

	init_completion(&ntb->released);

	ntb->dev.bus = &ntb_bus;
	ntb->dev.parent = &ntb->pdev->dev;
	ntb->dev.release = ntb_dev_release;
	dev_set_name(&ntb->dev, "%s", pci_name(ntb->pdev));

	ntb->ctx = शून्य;
	ntb->ctx_ops = शून्य;
	spin_lock_init(&ntb->ctx_lock);

	वापस device_रेजिस्टर(&ntb->dev);
पूर्ण
EXPORT_SYMBOL(ntb_रेजिस्टर_device);

व्योम ntb_unरेजिस्टर_device(काष्ठा ntb_dev *ntb)
अणु
	device_unरेजिस्टर(&ntb->dev);
	रुको_क्रम_completion(&ntb->released);
पूर्ण
EXPORT_SYMBOL(ntb_unरेजिस्टर_device);

पूर्णांक ntb_set_ctx(काष्ठा ntb_dev *ntb, व्योम *ctx,
		स्थिर काष्ठा ntb_ctx_ops *ctx_ops)
अणु
	अचिन्हित दीर्घ irqflags;

	अगर (!ntb_ctx_ops_is_valid(ctx_ops))
		वापस -EINVAL;
	अगर (ntb->ctx_ops)
		वापस -EINVAL;

	spin_lock_irqsave(&ntb->ctx_lock, irqflags);
	अणु
		ntb->ctx = ctx;
		ntb->ctx_ops = ctx_ops;
	पूर्ण
	spin_unlock_irqrestore(&ntb->ctx_lock, irqflags);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(ntb_set_ctx);

व्योम ntb_clear_ctx(काष्ठा ntb_dev *ntb)
अणु
	अचिन्हित दीर्घ irqflags;

	spin_lock_irqsave(&ntb->ctx_lock, irqflags);
	अणु
		ntb->ctx_ops = शून्य;
		ntb->ctx = शून्य;
	पूर्ण
	spin_unlock_irqrestore(&ntb->ctx_lock, irqflags);
पूर्ण
EXPORT_SYMBOL(ntb_clear_ctx);

व्योम ntb_link_event(काष्ठा ntb_dev *ntb)
अणु
	अचिन्हित दीर्घ irqflags;

	spin_lock_irqsave(&ntb->ctx_lock, irqflags);
	अणु
		अगर (ntb->ctx_ops && ntb->ctx_ops->link_event)
			ntb->ctx_ops->link_event(ntb->ctx);
	पूर्ण
	spin_unlock_irqrestore(&ntb->ctx_lock, irqflags);
पूर्ण
EXPORT_SYMBOL(ntb_link_event);

व्योम ntb_db_event(काष्ठा ntb_dev *ntb, पूर्णांक vector)
अणु
	अचिन्हित दीर्घ irqflags;

	spin_lock_irqsave(&ntb->ctx_lock, irqflags);
	अणु
		अगर (ntb->ctx_ops && ntb->ctx_ops->db_event)
			ntb->ctx_ops->db_event(ntb->ctx, vector);
	पूर्ण
	spin_unlock_irqrestore(&ntb->ctx_lock, irqflags);
पूर्ण
EXPORT_SYMBOL(ntb_db_event);

व्योम ntb_msg_event(काष्ठा ntb_dev *ntb)
अणु
	अचिन्हित दीर्घ irqflags;

	spin_lock_irqsave(&ntb->ctx_lock, irqflags);
	अणु
		अगर (ntb->ctx_ops && ntb->ctx_ops->msg_event)
			ntb->ctx_ops->msg_event(ntb->ctx);
	पूर्ण
	spin_unlock_irqrestore(&ntb->ctx_lock, irqflags);
पूर्ण
EXPORT_SYMBOL(ntb_msg_event);

पूर्णांक ntb_शेष_port_number(काष्ठा ntb_dev *ntb)
अणु
	चयन (ntb->topo) अणु
	हाल NTB_TOPO_PRI:
	हाल NTB_TOPO_B2B_USD:
		वापस NTB_PORT_PRI_USD;
	हाल NTB_TOPO_SEC:
	हाल NTB_TOPO_B2B_DSD:
		वापस NTB_PORT_SEC_DSD;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(ntb_शेष_port_number);

पूर्णांक ntb_शेष_peer_port_count(काष्ठा ntb_dev *ntb)
अणु
	वापस NTB_DEF_PEER_CNT;
पूर्ण
EXPORT_SYMBOL(ntb_शेष_peer_port_count);

पूर्णांक ntb_शेष_peer_port_number(काष्ठा ntb_dev *ntb, पूर्णांक pidx)
अणु
	अगर (pidx != NTB_DEF_PEER_IDX)
		वापस -EINVAL;

	चयन (ntb->topo) अणु
	हाल NTB_TOPO_PRI:
	हाल NTB_TOPO_B2B_USD:
		वापस NTB_PORT_SEC_DSD;
	हाल NTB_TOPO_SEC:
	हाल NTB_TOPO_B2B_DSD:
		वापस NTB_PORT_PRI_USD;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(ntb_शेष_peer_port_number);

पूर्णांक ntb_शेष_peer_port_idx(काष्ठा ntb_dev *ntb, पूर्णांक port)
अणु
	पूर्णांक peer_port = ntb_शेष_peer_port_number(ntb, NTB_DEF_PEER_IDX);

	अगर (peer_port == -EINVAL || port != peer_port)
		वापस -EINVAL;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(ntb_शेष_peer_port_idx);

अटल पूर्णांक ntb_probe(काष्ठा device *dev)
अणु
	काष्ठा ntb_dev *ntb;
	काष्ठा ntb_client *client;
	पूर्णांक rc;

	get_device(dev);
	ntb = dev_ntb(dev);
	client = drv_ntb_client(dev->driver);

	rc = client->ops.probe(client, ntb);
	अगर (rc)
		put_device(dev);

	वापस rc;
पूर्ण

अटल पूर्णांक ntb_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा ntb_dev *ntb;
	काष्ठा ntb_client *client;

	अगर (dev->driver) अणु
		ntb = dev_ntb(dev);
		client = drv_ntb_client(dev->driver);

		client->ops.हटाओ(client, ntb);
		put_device(dev);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ntb_dev_release(काष्ठा device *dev)
अणु
	काष्ठा ntb_dev *ntb = dev_ntb(dev);

	complete(&ntb->released);
पूर्ण

अटल काष्ठा bus_type ntb_bus = अणु
	.name = "ntb",
	.probe = ntb_probe,
	.हटाओ = ntb_हटाओ,
पूर्ण;

अटल पूर्णांक __init ntb_driver_init(व्योम)
अणु
	वापस bus_रेजिस्टर(&ntb_bus);
पूर्ण
module_init(ntb_driver_init);

अटल व्योम __निकास ntb_driver_निकास(व्योम)
अणु
	bus_unरेजिस्टर(&ntb_bus);
पूर्ण
module_निकास(ntb_driver_निकास);
