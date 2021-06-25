<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB
/* Copyright (c) 2020, Mellanox Technologies inc.  All rights reserved. */

#समावेश "en/devlink.h"
#समावेश "eswitch.h"

अटल व्योम
mlx5e_devlink_get_port_parent_id(काष्ठा mlx5_core_dev *dev, काष्ठा netdev_phys_item_id *ppid)
अणु
	u64 parent_id;

	parent_id = mlx5_query_nic_प्रणाली_image_guid(dev);
	ppid->id_len = माप(parent_id);
	स_नकल(ppid->id, &parent_id, माप(parent_id));
पूर्ण

पूर्णांक mlx5e_devlink_port_रेजिस्टर(काष्ठा mlx5e_priv *priv)
अणु
	काष्ठा devlink *devlink = priv_to_devlink(priv->mdev);
	काष्ठा devlink_port_attrs attrs = अणुपूर्ण;
	काष्ठा netdev_phys_item_id ppid = अणुपूर्ण;
	काष्ठा devlink_port *dl_port;
	अचिन्हित पूर्णांक dl_port_index;

	अगर (mlx5_core_is_pf(priv->mdev)) अणु
		attrs.flavour = DEVLINK_PORT_FLAVOUR_PHYSICAL;
		attrs.phys.port_number = PCI_FUNC(priv->mdev->pdev->devfn);
		अगर (MLX5_ESWITCH_MANAGER(priv->mdev)) अणु
			mlx5e_devlink_get_port_parent_id(priv->mdev, &ppid);
			स_नकल(attrs.चयन_id.id, ppid.id, ppid.id_len);
			attrs.चयन_id.id_len = ppid.id_len;
		पूर्ण
		dl_port_index = mlx5_esw_vport_to_devlink_port_index(priv->mdev,
								     MLX5_VPORT_UPLINK);
	पूर्ण अन्यथा अणु
		attrs.flavour = DEVLINK_PORT_FLAVOUR_VIRTUAL;
		dl_port_index = mlx5_esw_vport_to_devlink_port_index(priv->mdev, 0);
	पूर्ण

	dl_port = mlx5e_devlink_get_dl_port(priv);
	स_रखो(dl_port, 0, माप(*dl_port));
	devlink_port_attrs_set(dl_port, &attrs);

	वापस devlink_port_रेजिस्टर(devlink, dl_port, dl_port_index);
पूर्ण

व्योम mlx5e_devlink_port_type_eth_set(काष्ठा mlx5e_priv *priv)
अणु
	काष्ठा devlink_port *dl_port = mlx5e_devlink_get_dl_port(priv);

	devlink_port_type_eth_set(dl_port, priv->netdev);
पूर्ण

व्योम mlx5e_devlink_port_unरेजिस्टर(काष्ठा mlx5e_priv *priv)
अणु
	काष्ठा devlink_port *dl_port = mlx5e_devlink_get_dl_port(priv);

	अगर (dl_port->रेजिस्टरed)
		devlink_port_unरेजिस्टर(dl_port);
पूर्ण

काष्ठा devlink_port *mlx5e_get_devlink_port(काष्ठा net_device *dev)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(dev);
	काष्ठा devlink_port *port;

	अगर (!netअगर_device_present(dev))
		वापस शून्य;
	port = mlx5e_devlink_get_dl_port(priv);
	अगर (port->रेजिस्टरed)
		वापस port;
	वापस शून्य;
पूर्ण
