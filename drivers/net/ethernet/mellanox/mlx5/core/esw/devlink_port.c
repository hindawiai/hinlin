<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB
/* Copyright (c) 2020 Mellanox Technologies Ltd. */

#समावेश <linux/mlx5/driver.h>
#समावेश "eswitch.h"

अटल व्योम
mlx5_esw_get_port_parent_id(काष्ठा mlx5_core_dev *dev, काष्ठा netdev_phys_item_id *ppid)
अणु
	u64 parent_id;

	parent_id = mlx5_query_nic_प्रणाली_image_guid(dev);
	ppid->id_len = माप(parent_id);
	स_नकल(ppid->id, &parent_id, माप(parent_id));
पूर्ण

अटल bool mlx5_esw_devlink_port_supported(काष्ठा mlx5_eचयन *esw, u16 vport_num)
अणु
	वापस vport_num == MLX5_VPORT_UPLINK ||
	       (mlx5_core_is_ecpf(esw->dev) && vport_num == MLX5_VPORT_PF) ||
	       mlx5_eचयन_is_vf_vport(esw, vport_num);
पूर्ण

अटल काष्ठा devlink_port *mlx5_esw_dl_port_alloc(काष्ठा mlx5_eचयन *esw, u16 vport_num)
अणु
	काष्ठा mlx5_core_dev *dev = esw->dev;
	काष्ठा devlink_port_attrs attrs = अणुपूर्ण;
	काष्ठा netdev_phys_item_id ppid = अणुपूर्ण;
	काष्ठा devlink_port *dl_port;
	u32 controller_num = 0;
	bool बाह्यal;
	u16 pfnum;

	dl_port = kzalloc(माप(*dl_port), GFP_KERNEL);
	अगर (!dl_port)
		वापस शून्य;

	mlx5_esw_get_port_parent_id(dev, &ppid);
	pfnum = PCI_FUNC(dev->pdev->devfn);
	बाह्यal = mlx5_core_is_ecpf_esw_manager(dev);
	अगर (बाह्यal)
		controller_num = dev->priv.eचयन->offloads.host_number + 1;

	अगर (vport_num == MLX5_VPORT_UPLINK) अणु
		attrs.flavour = DEVLINK_PORT_FLAVOUR_PHYSICAL;
		attrs.phys.port_number = pfnum;
		स_नकल(attrs.चयन_id.id, ppid.id, ppid.id_len);
		attrs.चयन_id.id_len = ppid.id_len;
		devlink_port_attrs_set(dl_port, &attrs);
	पूर्ण अन्यथा अगर (vport_num == MLX5_VPORT_PF) अणु
		स_नकल(dl_port->attrs.चयन_id.id, ppid.id, ppid.id_len);
		dl_port->attrs.चयन_id.id_len = ppid.id_len;
		devlink_port_attrs_pci_pf_set(dl_port, controller_num, pfnum, बाह्यal);
	पूर्ण अन्यथा अगर (mlx5_eचयन_is_vf_vport(esw, vport_num)) अणु
		स_नकल(dl_port->attrs.चयन_id.id, ppid.id, ppid.id_len);
		dl_port->attrs.चयन_id.id_len = ppid.id_len;
		devlink_port_attrs_pci_vf_set(dl_port, controller_num, pfnum,
					      vport_num - 1, बाह्यal);
	पूर्ण
	वापस dl_port;
पूर्ण

अटल व्योम mlx5_esw_dl_port_मुक्त(काष्ठा devlink_port *dl_port)
अणु
	kमुक्त(dl_port);
पूर्ण

पूर्णांक mlx5_esw_offloads_devlink_port_रेजिस्टर(काष्ठा mlx5_eचयन *esw, u16 vport_num)
अणु
	काष्ठा mlx5_core_dev *dev = esw->dev;
	काष्ठा devlink_port *dl_port;
	अचिन्हित पूर्णांक dl_port_index;
	काष्ठा mlx5_vport *vport;
	काष्ठा devlink *devlink;
	पूर्णांक err;

	अगर (!mlx5_esw_devlink_port_supported(esw, vport_num))
		वापस 0;

	vport = mlx5_eचयन_get_vport(esw, vport_num);
	अगर (IS_ERR(vport))
		वापस PTR_ERR(vport);

	dl_port = mlx5_esw_dl_port_alloc(esw, vport_num);
	अगर (!dl_port)
		वापस -ENOMEM;

	devlink = priv_to_devlink(dev);
	dl_port_index = mlx5_esw_vport_to_devlink_port_index(dev, vport_num);
	err = devlink_port_रेजिस्टर(devlink, dl_port, dl_port_index);
	अगर (err)
		जाओ reg_err;

	vport->dl_port = dl_port;
	वापस 0;

reg_err:
	mlx5_esw_dl_port_मुक्त(dl_port);
	वापस err;
पूर्ण

व्योम mlx5_esw_offloads_devlink_port_unरेजिस्टर(काष्ठा mlx5_eचयन *esw, u16 vport_num)
अणु
	काष्ठा mlx5_vport *vport;

	अगर (!mlx5_esw_devlink_port_supported(esw, vport_num))
		वापस;

	vport = mlx5_eचयन_get_vport(esw, vport_num);
	अगर (IS_ERR(vport))
		वापस;
	devlink_port_unरेजिस्टर(vport->dl_port);
	mlx5_esw_dl_port_मुक्त(vport->dl_port);
	vport->dl_port = शून्य;
पूर्ण

काष्ठा devlink_port *mlx5_esw_offloads_devlink_port(काष्ठा mlx5_eचयन *esw, u16 vport_num)
अणु
	काष्ठा mlx5_vport *vport;

	vport = mlx5_eचयन_get_vport(esw, vport_num);
	वापस IS_ERR(vport) ? ERR_CAST(vport) : vport->dl_port;
पूर्ण

पूर्णांक mlx5_esw_devlink_sf_port_रेजिस्टर(काष्ठा mlx5_eचयन *esw, काष्ठा devlink_port *dl_port,
				      u16 vport_num, u32 controller, u32 sfnum)
अणु
	काष्ठा mlx5_core_dev *dev = esw->dev;
	काष्ठा netdev_phys_item_id ppid = अणुपूर्ण;
	अचिन्हित पूर्णांक dl_port_index;
	काष्ठा mlx5_vport *vport;
	काष्ठा devlink *devlink;
	u16 pfnum;
	पूर्णांक err;

	vport = mlx5_eचयन_get_vport(esw, vport_num);
	अगर (IS_ERR(vport))
		वापस PTR_ERR(vport);

	pfnum = PCI_FUNC(dev->pdev->devfn);
	mlx5_esw_get_port_parent_id(dev, &ppid);
	स_नकल(dl_port->attrs.चयन_id.id, &ppid.id[0], ppid.id_len);
	dl_port->attrs.चयन_id.id_len = ppid.id_len;
	devlink_port_attrs_pci_sf_set(dl_port, controller, pfnum, sfnum, !!controller);
	devlink = priv_to_devlink(dev);
	dl_port_index = mlx5_esw_vport_to_devlink_port_index(dev, vport_num);
	err = devlink_port_रेजिस्टर(devlink, dl_port, dl_port_index);
	अगर (err)
		वापस err;

	vport->dl_port = dl_port;
	वापस 0;
पूर्ण

व्योम mlx5_esw_devlink_sf_port_unरेजिस्टर(काष्ठा mlx5_eचयन *esw, u16 vport_num)
अणु
	काष्ठा mlx5_vport *vport;

	vport = mlx5_eचयन_get_vport(esw, vport_num);
	अगर (IS_ERR(vport))
		वापस;
	devlink_port_unरेजिस्टर(vport->dl_port);
	vport->dl_port = शून्य;
पूर्ण
