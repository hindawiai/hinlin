<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/* Copyright (c) 2019-2020 Marvell International Ltd. All rights reserved */

#समावेश <net/devlink.h>

#समावेश "prestera_devlink.h"

अटल पूर्णांक prestera_dl_info_get(काष्ठा devlink *dl,
				काष्ठा devlink_info_req *req,
				काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा prestera_चयन *sw = devlink_priv(dl);
	अक्षर buf[16];
	पूर्णांक err;

	err = devlink_info_driver_name_put(req, PRESTERA_DRV_NAME);
	अगर (err)
		वापस err;

	snम_लिखो(buf, माप(buf), "%d.%d.%d",
		 sw->dev->fw_rev.maj,
		 sw->dev->fw_rev.min,
		 sw->dev->fw_rev.sub);

	वापस devlink_info_version_running_put(req,
					       DEVLINK_INFO_VERSION_GENERIC_FW,
					       buf);
पूर्ण

अटल स्थिर काष्ठा devlink_ops prestera_dl_ops = अणु
	.info_get = prestera_dl_info_get,
पूर्ण;

काष्ठा prestera_चयन *prestera_devlink_alloc(व्योम)
अणु
	काष्ठा devlink *dl;

	dl = devlink_alloc(&prestera_dl_ops, माप(काष्ठा prestera_चयन));

	वापस devlink_priv(dl);
पूर्ण

व्योम prestera_devlink_मुक्त(काष्ठा prestera_चयन *sw)
अणु
	काष्ठा devlink *dl = priv_to_devlink(sw);

	devlink_मुक्त(dl);
पूर्ण

पूर्णांक prestera_devlink_रेजिस्टर(काष्ठा prestera_चयन *sw)
अणु
	काष्ठा devlink *dl = priv_to_devlink(sw);
	पूर्णांक err;

	err = devlink_रेजिस्टर(dl, sw->dev->dev);
	अगर (err)
		dev_err(prestera_dev(sw), "devlink_register failed: %d\n", err);

	वापस err;
पूर्ण

व्योम prestera_devlink_unरेजिस्टर(काष्ठा prestera_चयन *sw)
अणु
	काष्ठा devlink *dl = priv_to_devlink(sw);

	devlink_unरेजिस्टर(dl);
पूर्ण

पूर्णांक prestera_devlink_port_रेजिस्टर(काष्ठा prestera_port *port)
अणु
	काष्ठा prestera_चयन *sw = port->sw;
	काष्ठा devlink *dl = priv_to_devlink(sw);
	काष्ठा devlink_port_attrs attrs = अणुपूर्ण;
	पूर्णांक err;

	attrs.flavour = DEVLINK_PORT_FLAVOUR_PHYSICAL;
	attrs.phys.port_number = port->fp_id;
	attrs.चयन_id.id_len = माप(sw->id);
	स_नकल(attrs.चयन_id.id, &sw->id, attrs.चयन_id.id_len);

	devlink_port_attrs_set(&port->dl_port, &attrs);

	err = devlink_port_रेजिस्टर(dl, &port->dl_port, port->fp_id);
	अगर (err) अणु
		dev_err(prestera_dev(sw), "devlink_port_register failed: %d\n", err);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

व्योम prestera_devlink_port_unरेजिस्टर(काष्ठा prestera_port *port)
अणु
	devlink_port_unरेजिस्टर(&port->dl_port);
पूर्ण

व्योम prestera_devlink_port_set(काष्ठा prestera_port *port)
अणु
	devlink_port_type_eth_set(&port->dl_port, port->dev);
पूर्ण

व्योम prestera_devlink_port_clear(काष्ठा prestera_port *port)
अणु
	devlink_port_type_clear(&port->dl_port);
पूर्ण

काष्ठा devlink_port *prestera_devlink_get_port(काष्ठा net_device *dev)
अणु
	काष्ठा prestera_port *port = netdev_priv(dev);

	वापस &port->dl_port;
पूर्ण
