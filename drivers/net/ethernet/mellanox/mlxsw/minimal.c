<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/* Copyright (c) 2016-2019 Mellanox Technologies. All rights reserved */

#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/i2c.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/types.h>

#समावेश "core.h"
#समावेश "core_env.h"
#समावेश "i2c.h"

अटल स्थिर अक्षर mlxsw_m_driver_name[] = "mlxsw_minimal";

#घोषणा MLXSW_M_FWREV_MINOR	2000
#घोषणा MLXSW_M_FWREV_SUBMINOR	1886

अटल स्थिर काष्ठा mlxsw_fw_rev mlxsw_m_fw_rev = अणु
	.minor = MLXSW_M_FWREV_MINOR,
	.subminor = MLXSW_M_FWREV_SUBMINOR,
पूर्ण;

काष्ठा mlxsw_m_port;

काष्ठा mlxsw_m अणु
	काष्ठा mlxsw_m_port **ports;
	पूर्णांक *module_to_port;
	काष्ठा mlxsw_core *core;
	स्थिर काष्ठा mlxsw_bus_info *bus_info;
	u8 base_mac[ETH_ALEN];
	u8 max_ports;
पूर्ण;

काष्ठा mlxsw_m_port अणु
	काष्ठा net_device *dev;
	काष्ठा mlxsw_m *mlxsw_m;
	u8 local_port;
	u8 module;
पूर्ण;

अटल पूर्णांक mlxsw_m_base_mac_get(काष्ठा mlxsw_m *mlxsw_m)
अणु
	अक्षर spad_pl[MLXSW_REG_SPAD_LEN] = अणु0पूर्ण;
	पूर्णांक err;

	err = mlxsw_reg_query(mlxsw_m->core, MLXSW_REG(spad), spad_pl);
	अगर (err)
		वापस err;
	mlxsw_reg_spad_base_mac_स_नकल_from(spad_pl, mlxsw_m->base_mac);
	वापस 0;
पूर्ण

अटल पूर्णांक mlxsw_m_port_dummy_खोलो_stop(काष्ठा net_device *dev)
अणु
	वापस 0;
पूर्ण

अटल काष्ठा devlink_port *
mlxsw_m_port_get_devlink_port(काष्ठा net_device *dev)
अणु
	काष्ठा mlxsw_m_port *mlxsw_m_port = netdev_priv(dev);
	काष्ठा mlxsw_m *mlxsw_m = mlxsw_m_port->mlxsw_m;

	वापस mlxsw_core_port_devlink_port_get(mlxsw_m->core,
						mlxsw_m_port->local_port);
पूर्ण

अटल स्थिर काष्ठा net_device_ops mlxsw_m_port_netdev_ops = अणु
	.nकरो_खोलो		= mlxsw_m_port_dummy_खोलो_stop,
	.nकरो_stop		= mlxsw_m_port_dummy_खोलो_stop,
	.nकरो_get_devlink_port	= mlxsw_m_port_get_devlink_port,
पूर्ण;

अटल व्योम mlxsw_m_module_get_drvinfo(काष्ठा net_device *dev,
				       काष्ठा ethtool_drvinfo *drvinfo)
अणु
	काष्ठा mlxsw_m_port *mlxsw_m_port = netdev_priv(dev);
	काष्ठा mlxsw_m *mlxsw_m = mlxsw_m_port->mlxsw_m;

	strlcpy(drvinfo->driver, mlxsw_m->bus_info->device_kind,
		माप(drvinfo->driver));
	snम_लिखो(drvinfo->fw_version, माप(drvinfo->fw_version),
		 "%d.%d.%d",
		 mlxsw_m->bus_info->fw_rev.major,
		 mlxsw_m->bus_info->fw_rev.minor,
		 mlxsw_m->bus_info->fw_rev.subminor);
	strlcpy(drvinfo->bus_info, mlxsw_m->bus_info->device_name,
		माप(drvinfo->bus_info));
पूर्ण

अटल पूर्णांक mlxsw_m_get_module_info(काष्ठा net_device *netdev,
				   काष्ठा ethtool_modinfo *modinfo)
अणु
	काष्ठा mlxsw_m_port *mlxsw_m_port = netdev_priv(netdev);
	काष्ठा mlxsw_core *core = mlxsw_m_port->mlxsw_m->core;

	वापस mlxsw_env_get_module_info(core, mlxsw_m_port->module, modinfo);
पूर्ण

अटल पूर्णांक
mlxsw_m_get_module_eeprom(काष्ठा net_device *netdev, काष्ठा ethtool_eeprom *ee,
			  u8 *data)
अणु
	काष्ठा mlxsw_m_port *mlxsw_m_port = netdev_priv(netdev);
	काष्ठा mlxsw_core *core = mlxsw_m_port->mlxsw_m->core;

	वापस mlxsw_env_get_module_eeprom(netdev, core, mlxsw_m_port->module,
					   ee, data);
पूर्ण

अटल स्थिर काष्ठा ethtool_ops mlxsw_m_port_ethtool_ops = अणु
	.get_drvinfo		= mlxsw_m_module_get_drvinfo,
	.get_module_info	= mlxsw_m_get_module_info,
	.get_module_eeprom	= mlxsw_m_get_module_eeprom,
पूर्ण;

अटल पूर्णांक
mlxsw_m_port_module_info_get(काष्ठा mlxsw_m *mlxsw_m, u8 local_port,
			     u8 *p_module, u8 *p_width)
अणु
	अक्षर pmlp_pl[MLXSW_REG_PMLP_LEN];
	पूर्णांक err;

	mlxsw_reg_pmlp_pack(pmlp_pl, local_port);
	err = mlxsw_reg_query(mlxsw_m->core, MLXSW_REG(pmlp), pmlp_pl);
	अगर (err)
		वापस err;
	*p_module = mlxsw_reg_pmlp_module_get(pmlp_pl, 0);
	*p_width = mlxsw_reg_pmlp_width_get(pmlp_pl);

	वापस 0;
पूर्ण

अटल पूर्णांक
mlxsw_m_port_dev_addr_get(काष्ठा mlxsw_m_port *mlxsw_m_port)
अणु
	काष्ठा mlxsw_m *mlxsw_m = mlxsw_m_port->mlxsw_m;
	काष्ठा net_device *dev = mlxsw_m_port->dev;
	अक्षर ppad_pl[MLXSW_REG_PPAD_LEN];
	पूर्णांक err;

	mlxsw_reg_ppad_pack(ppad_pl, false, 0);
	err = mlxsw_reg_query(mlxsw_m->core, MLXSW_REG(ppad), ppad_pl);
	अगर (err)
		वापस err;
	mlxsw_reg_ppad_mac_स_नकल_from(ppad_pl, dev->dev_addr);
	/* The last byte value in base mac address is guaranteed
	 * to be such it करोes not overflow when adding local_port
	 * value.
	 */
	dev->dev_addr[ETH_ALEN - 1] += mlxsw_m_port->module + 1;
	वापस 0;
पूर्ण

अटल पूर्णांक
mlxsw_m_port_create(काष्ठा mlxsw_m *mlxsw_m, u8 local_port, u8 module)
अणु
	काष्ठा mlxsw_m_port *mlxsw_m_port;
	काष्ठा net_device *dev;
	पूर्णांक err;

	err = mlxsw_core_port_init(mlxsw_m->core, local_port,
				   module + 1, false, 0, false,
				   0, mlxsw_m->base_mac,
				   माप(mlxsw_m->base_mac));
	अगर (err) अणु
		dev_err(mlxsw_m->bus_info->dev, "Port %d: Failed to init core port\n",
			local_port);
		वापस err;
	पूर्ण

	dev = alloc_etherdev(माप(काष्ठा mlxsw_m_port));
	अगर (!dev) अणु
		err = -ENOMEM;
		जाओ err_alloc_etherdev;
	पूर्ण

	SET_NETDEV_DEV(dev, mlxsw_m->bus_info->dev);
	dev_net_set(dev, mlxsw_core_net(mlxsw_m->core));
	mlxsw_m_port = netdev_priv(dev);
	mlxsw_m_port->dev = dev;
	mlxsw_m_port->mlxsw_m = mlxsw_m;
	mlxsw_m_port->local_port = local_port;
	mlxsw_m_port->module = module;

	dev->netdev_ops = &mlxsw_m_port_netdev_ops;
	dev->ethtool_ops = &mlxsw_m_port_ethtool_ops;

	err = mlxsw_m_port_dev_addr_get(mlxsw_m_port);
	अगर (err) अणु
		dev_err(mlxsw_m->bus_info->dev, "Port %d: Unable to get port mac address\n",
			mlxsw_m_port->local_port);
		जाओ err_dev_addr_get;
	पूर्ण

	netअगर_carrier_off(dev);
	mlxsw_m->ports[local_port] = mlxsw_m_port;
	err = रेजिस्टर_netdev(dev);
	अगर (err) अणु
		dev_err(mlxsw_m->bus_info->dev, "Port %d: Failed to register netdev\n",
			mlxsw_m_port->local_port);
		जाओ err_रेजिस्टर_netdev;
	पूर्ण

	mlxsw_core_port_eth_set(mlxsw_m->core, mlxsw_m_port->local_port,
				mlxsw_m_port, dev);

	वापस 0;

err_रेजिस्टर_netdev:
	mlxsw_m->ports[local_port] = शून्य;
err_dev_addr_get:
	मुक्त_netdev(dev);
err_alloc_etherdev:
	mlxsw_core_port_fini(mlxsw_m->core, local_port);
	वापस err;
पूर्ण

अटल व्योम mlxsw_m_port_हटाओ(काष्ठा mlxsw_m *mlxsw_m, u8 local_port)
अणु
	काष्ठा mlxsw_m_port *mlxsw_m_port = mlxsw_m->ports[local_port];

	mlxsw_core_port_clear(mlxsw_m->core, local_port, mlxsw_m);
	unरेजिस्टर_netdev(mlxsw_m_port->dev); /* This calls nकरो_stop */
	mlxsw_m->ports[local_port] = शून्य;
	मुक्त_netdev(mlxsw_m_port->dev);
	mlxsw_core_port_fini(mlxsw_m->core, local_port);
पूर्ण

अटल पूर्णांक mlxsw_m_port_module_map(काष्ठा mlxsw_m *mlxsw_m, u8 local_port,
				   u8 *last_module)
अणु
	u8 module, width;
	पूर्णांक err;

	/* Fill out to local port mapping array */
	err = mlxsw_m_port_module_info_get(mlxsw_m, local_port, &module,
					   &width);
	अगर (err)
		वापस err;

	अगर (!width)
		वापस 0;
	/* Skip, अगर port beदीर्घs to the cluster */
	अगर (module == *last_module)
		वापस 0;
	*last_module = module;
	mlxsw_m->module_to_port[module] = ++mlxsw_m->max_ports;

	वापस 0;
पूर्ण

अटल व्योम mlxsw_m_port_module_unmap(काष्ठा mlxsw_m *mlxsw_m, u8 module)
अणु
	mlxsw_m->module_to_port[module] = -1;
पूर्ण

अटल पूर्णांक mlxsw_m_ports_create(काष्ठा mlxsw_m *mlxsw_m)
अणु
	अचिन्हित पूर्णांक max_ports = mlxsw_core_max_ports(mlxsw_m->core);
	u8 last_module = max_ports;
	पूर्णांक i;
	पूर्णांक err;

	mlxsw_m->ports = kसुस्मृति(max_ports, माप(*mlxsw_m->ports),
				 GFP_KERNEL);
	अगर (!mlxsw_m->ports)
		वापस -ENOMEM;

	mlxsw_m->module_to_port = kदो_स्मृति_array(max_ports, माप(पूर्णांक),
						GFP_KERNEL);
	अगर (!mlxsw_m->module_to_port) अणु
		err = -ENOMEM;
		जाओ err_module_to_port_alloc;
	पूर्ण

	/* Invalidate the entries of module to local port mapping array */
	क्रम (i = 0; i < max_ports; i++)
		mlxsw_m->module_to_port[i] = -1;

	/* Fill out module to local port mapping array */
	क्रम (i = 1; i < max_ports; i++) अणु
		err = mlxsw_m_port_module_map(mlxsw_m, i, &last_module);
		अगर (err)
			जाओ err_module_to_port_map;
	पूर्ण

	/* Create port objects क्रम each valid entry */
	क्रम (i = 0; i < mlxsw_m->max_ports; i++) अणु
		अगर (mlxsw_m->module_to_port[i] > 0 &&
		    !mlxsw_core_port_is_xm(mlxsw_m->core, i)) अणु
			err = mlxsw_m_port_create(mlxsw_m,
						  mlxsw_m->module_to_port[i],
						  i);
			अगर (err)
				जाओ err_module_to_port_create;
		पूर्ण
	पूर्ण

	वापस 0;

err_module_to_port_create:
	क्रम (i--; i >= 0; i--) अणु
		अगर (mlxsw_m->module_to_port[i] > 0)
			mlxsw_m_port_हटाओ(mlxsw_m,
					    mlxsw_m->module_to_port[i]);
	पूर्ण
	i = max_ports;
err_module_to_port_map:
	क्रम (i--; i > 0; i--)
		mlxsw_m_port_module_unmap(mlxsw_m, i);
	kमुक्त(mlxsw_m->module_to_port);
err_module_to_port_alloc:
	kमुक्त(mlxsw_m->ports);
	वापस err;
पूर्ण

अटल व्योम mlxsw_m_ports_हटाओ(काष्ठा mlxsw_m *mlxsw_m)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < mlxsw_m->max_ports; i++) अणु
		अगर (mlxsw_m->module_to_port[i] > 0) अणु
			mlxsw_m_port_हटाओ(mlxsw_m,
					    mlxsw_m->module_to_port[i]);
			mlxsw_m_port_module_unmap(mlxsw_m, i);
		पूर्ण
	पूर्ण

	kमुक्त(mlxsw_m->module_to_port);
	kमुक्त(mlxsw_m->ports);
पूर्ण

अटल पूर्णांक mlxsw_m_fw_rev_validate(काष्ठा mlxsw_m *mlxsw_m)
अणु
	स्थिर काष्ठा mlxsw_fw_rev *rev = &mlxsw_m->bus_info->fw_rev;

	/* Validate driver and FW are compatible.
	 * Do not check major version, since it defines chip type, जबतक
	 * driver is supposed to support any type.
	 */
	अगर (mlxsw_core_fw_rev_minor_subminor_validate(rev, &mlxsw_m_fw_rev))
		वापस 0;

	dev_err(mlxsw_m->bus_info->dev, "The firmware version %d.%d.%d is incompatible with the driver (required >= %d.%d.%d)\n",
		rev->major, rev->minor, rev->subminor, rev->major,
		mlxsw_m_fw_rev.minor, mlxsw_m_fw_rev.subminor);

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक mlxsw_m_init(काष्ठा mlxsw_core *mlxsw_core,
			स्थिर काष्ठा mlxsw_bus_info *mlxsw_bus_info,
			काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mlxsw_m *mlxsw_m = mlxsw_core_driver_priv(mlxsw_core);
	पूर्णांक err;

	mlxsw_m->core = mlxsw_core;
	mlxsw_m->bus_info = mlxsw_bus_info;

	err = mlxsw_m_fw_rev_validate(mlxsw_m);
	अगर (err)
		वापस err;

	err = mlxsw_m_base_mac_get(mlxsw_m);
	अगर (err) अणु
		dev_err(mlxsw_m->bus_info->dev, "Failed to get base mac\n");
		वापस err;
	पूर्ण

	err = mlxsw_m_ports_create(mlxsw_m);
	अगर (err) अणु
		dev_err(mlxsw_m->bus_info->dev, "Failed to create ports\n");
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम mlxsw_m_fini(काष्ठा mlxsw_core *mlxsw_core)
अणु
	काष्ठा mlxsw_m *mlxsw_m = mlxsw_core_driver_priv(mlxsw_core);

	mlxsw_m_ports_हटाओ(mlxsw_m);
पूर्ण

अटल स्थिर काष्ठा mlxsw_config_profile mlxsw_m_config_profile;

अटल काष्ठा mlxsw_driver mlxsw_m_driver = अणु
	.kind			= mlxsw_m_driver_name,
	.priv_size		= माप(काष्ठा mlxsw_m),
	.init			= mlxsw_m_init,
	.fini			= mlxsw_m_fini,
	.profile		= &mlxsw_m_config_profile,
	.res_query_enabled	= true,
पूर्ण;

अटल स्थिर काष्ठा i2c_device_id mlxsw_m_i2c_id[] = अणु
	अणु "mlxsw_minimal", 0पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा i2c_driver mlxsw_m_i2c_driver = अणु
	.driver.name = "mlxsw_minimal",
	.class = I2C_CLASS_HWMON,
	.id_table = mlxsw_m_i2c_id,
पूर्ण;

अटल पूर्णांक __init mlxsw_m_module_init(व्योम)
अणु
	पूर्णांक err;

	err = mlxsw_core_driver_रेजिस्टर(&mlxsw_m_driver);
	अगर (err)
		वापस err;

	err = mlxsw_i2c_driver_रेजिस्टर(&mlxsw_m_i2c_driver);
	अगर (err)
		जाओ err_i2c_driver_रेजिस्टर;

	वापस 0;

err_i2c_driver_रेजिस्टर:
	mlxsw_core_driver_unरेजिस्टर(&mlxsw_m_driver);

	वापस err;
पूर्ण

अटल व्योम __निकास mlxsw_m_module_निकास(व्योम)
अणु
	mlxsw_i2c_driver_unरेजिस्टर(&mlxsw_m_i2c_driver);
	mlxsw_core_driver_unरेजिस्टर(&mlxsw_m_driver);
पूर्ण

module_init(mlxsw_m_module_init);
module_निकास(mlxsw_m_module_निकास);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("Vadim Pasternak <vadimp@mellanox.com>");
MODULE_DESCRIPTION("Mellanox minimal driver");
MODULE_DEVICE_TABLE(i2c, mlxsw_m_i2c_id);
