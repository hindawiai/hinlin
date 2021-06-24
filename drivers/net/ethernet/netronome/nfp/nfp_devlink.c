<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-2-Clause)
/* Copyright (C) 2017-2018 Netronome Systems, Inc. */

#समावेश <linux/rtnetlink.h>
#समावेश <net/devlink.h>

#समावेश "nfpcore/nfp.h"
#समावेश "nfpcore/nfp_nsp.h"
#समावेश "nfp_app.h"
#समावेश "nfp_main.h"
#समावेश "nfp_port.h"

अटल पूर्णांक
nfp_devlink_fill_eth_port(काष्ठा nfp_port *port,
			  काष्ठा nfp_eth_table_port *copy)
अणु
	काष्ठा nfp_eth_table_port *eth_port;

	eth_port = __nfp_port_get_eth_port(port);
	अगर (!eth_port)
		वापस -EINVAL;

	स_नकल(copy, eth_port, माप(*eth_port));

	वापस 0;
पूर्ण

अटल पूर्णांक
nfp_devlink_fill_eth_port_from_id(काष्ठा nfp_pf *pf, अचिन्हित पूर्णांक port_index,
				  काष्ठा nfp_eth_table_port *copy)
अणु
	काष्ठा nfp_port *port;

	port = nfp_port_from_id(pf, NFP_PORT_PHYS_PORT, port_index);

	वापस nfp_devlink_fill_eth_port(port, copy);
पूर्ण

अटल पूर्णांक
nfp_devlink_set_lanes(काष्ठा nfp_pf *pf, अचिन्हित पूर्णांक idx, अचिन्हित पूर्णांक lanes)
अणु
	काष्ठा nfp_nsp *nsp;
	पूर्णांक ret;

	nsp = nfp_eth_config_start(pf->cpp, idx);
	अगर (IS_ERR(nsp))
		वापस PTR_ERR(nsp);

	ret = __nfp_eth_set_split(nsp, lanes);
	अगर (ret) अणु
		nfp_eth_config_cleanup_end(nsp);
		वापस ret;
	पूर्ण

	ret = nfp_eth_config_commit_end(nsp);
	अगर (ret < 0)
		वापस ret;
	अगर (ret) /* no change */
		वापस 0;

	वापस nfp_net_refresh_port_table_sync(pf);
पूर्ण

अटल पूर्णांक
nfp_devlink_port_split(काष्ठा devlink *devlink, अचिन्हित पूर्णांक port_index,
		       अचिन्हित पूर्णांक count, काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा nfp_pf *pf = devlink_priv(devlink);
	काष्ठा nfp_eth_table_port eth_port;
	अचिन्हित पूर्णांक lanes;
	पूर्णांक ret;

	mutex_lock(&pf->lock);

	rtnl_lock();
	ret = nfp_devlink_fill_eth_port_from_id(pf, port_index, &eth_port);
	rtnl_unlock();
	अगर (ret)
		जाओ out;

	अगर (eth_port.port_lanes % count) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	/* Special हाल the 100G CXP -> 2x40G split */
	lanes = eth_port.port_lanes / count;
	अगर (eth_port.lanes == 10 && count == 2)
		lanes = 8 / count;

	ret = nfp_devlink_set_lanes(pf, eth_port.index, lanes);
out:
	mutex_unlock(&pf->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक
nfp_devlink_port_unsplit(काष्ठा devlink *devlink, अचिन्हित पूर्णांक port_index,
			 काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा nfp_pf *pf = devlink_priv(devlink);
	काष्ठा nfp_eth_table_port eth_port;
	अचिन्हित पूर्णांक lanes;
	पूर्णांक ret;

	mutex_lock(&pf->lock);

	rtnl_lock();
	ret = nfp_devlink_fill_eth_port_from_id(pf, port_index, &eth_port);
	rtnl_unlock();
	अगर (ret)
		जाओ out;

	अगर (!eth_port.is_split) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	/* Special हाल the 100G CXP -> 2x40G unsplit */
	lanes = eth_port.port_lanes;
	अगर (eth_port.port_lanes == 8)
		lanes = 10;

	ret = nfp_devlink_set_lanes(pf, eth_port.index, lanes);
out:
	mutex_unlock(&pf->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक
nfp_devlink_sb_pool_get(काष्ठा devlink *devlink, अचिन्हित पूर्णांक sb_index,
			u16 pool_index, काष्ठा devlink_sb_pool_info *pool_info)
अणु
	काष्ठा nfp_pf *pf = devlink_priv(devlink);

	वापस nfp_shared_buf_pool_get(pf, sb_index, pool_index, pool_info);
पूर्ण

अटल पूर्णांक
nfp_devlink_sb_pool_set(काष्ठा devlink *devlink, अचिन्हित पूर्णांक sb_index,
			u16 pool_index,
			u32 size, क्रमागत devlink_sb_threshold_type threshold_type,
			काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा nfp_pf *pf = devlink_priv(devlink);

	वापस nfp_shared_buf_pool_set(pf, sb_index, pool_index,
				       size, threshold_type);
पूर्ण

अटल पूर्णांक nfp_devlink_eचयन_mode_get(काष्ठा devlink *devlink, u16 *mode)
अणु
	काष्ठा nfp_pf *pf = devlink_priv(devlink);

	वापस nfp_app_eचयन_mode_get(pf->app, mode);
पूर्ण

अटल पूर्णांक nfp_devlink_eचयन_mode_set(काष्ठा devlink *devlink, u16 mode,
					काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा nfp_pf *pf = devlink_priv(devlink);
	पूर्णांक ret;

	mutex_lock(&pf->lock);
	ret = nfp_app_eचयन_mode_set(pf->app, mode);
	mutex_unlock(&pf->lock);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा nfp_devlink_versions_simple अणु
	स्थिर अक्षर *key;
	स्थिर अक्षर *hwinfo;
पूर्ण nfp_devlink_versions_hwinfo[] = अणु
	अणु DEVLINK_INFO_VERSION_GENERIC_BOARD_ID,	"assembly.partno", पूर्ण,
	अणु DEVLINK_INFO_VERSION_GENERIC_BOARD_REV,	"assembly.revision", पूर्ण,
	अणु DEVLINK_INFO_VERSION_GENERIC_BOARD_MANUFACTURE, "assembly.vendor", पूर्ण,
	अणु "board.model", /* code name */		"assembly.model", पूर्ण,
पूर्ण;

अटल पूर्णांक
nfp_devlink_versions_get_hwinfo(काष्ठा nfp_pf *pf, काष्ठा devlink_info_req *req)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	क्रम (i = 0; i < ARRAY_SIZE(nfp_devlink_versions_hwinfo); i++) अणु
		स्थिर काष्ठा nfp_devlink_versions_simple *info;
		स्थिर अक्षर *val;

		info = &nfp_devlink_versions_hwinfo[i];

		val = nfp_hwinfo_lookup(pf->hwinfo, info->hwinfo);
		अगर (!val)
			जारी;

		err = devlink_info_version_fixed_put(req, info->key, val);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा nfp_devlink_versions अणु
	क्रमागत nfp_nsp_versions id;
	स्थिर अक्षर *key;
पूर्ण nfp_devlink_versions_nsp[] = अणु
	अणु NFP_VERSIONS_BUNDLE,	DEVLINK_INFO_VERSION_GENERIC_FW_BUNDLE_ID, पूर्ण,
	अणु NFP_VERSIONS_BSP,	DEVLINK_INFO_VERSION_GENERIC_FW_MGMT, पूर्ण,
	अणु NFP_VERSIONS_CPLD,	"fw.cpld", पूर्ण,
	अणु NFP_VERSIONS_APP,	DEVLINK_INFO_VERSION_GENERIC_FW_APP, पूर्ण,
	अणु NFP_VERSIONS_UNDI,	DEVLINK_INFO_VERSION_GENERIC_FW_UNDI, पूर्ण,
	अणु NFP_VERSIONS_NCSI,	DEVLINK_INFO_VERSION_GENERIC_FW_NCSI, पूर्ण,
	अणु NFP_VERSIONS_CFGR,	"chip.init", पूर्ण,
पूर्ण;

अटल पूर्णांक
nfp_devlink_versions_get_nsp(काष्ठा devlink_info_req *req, bool flash,
			     स्थिर u8 *buf, अचिन्हित पूर्णांक size)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	क्रम (i = 0; i < ARRAY_SIZE(nfp_devlink_versions_nsp); i++) अणु
		स्थिर काष्ठा nfp_devlink_versions *info;
		स्थिर अक्षर *version;

		info = &nfp_devlink_versions_nsp[i];

		version = nfp_nsp_versions_get(info->id, flash, buf, size);
		अगर (IS_ERR(version)) अणु
			अगर (PTR_ERR(version) == -ENOENT)
				जारी;
			अन्यथा
				वापस PTR_ERR(version);
		पूर्ण

		अगर (flash)
			err = devlink_info_version_stored_put(req, info->key,
							      version);
		अन्यथा
			err = devlink_info_version_running_put(req, info->key,
							       version);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
nfp_devlink_info_get(काष्ठा devlink *devlink, काष्ठा devlink_info_req *req,
		     काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा nfp_pf *pf = devlink_priv(devlink);
	स्थिर अक्षर *sn, *venकरोr, *part;
	काष्ठा nfp_nsp *nsp;
	अक्षर *buf = शून्य;
	पूर्णांक err;

	err = devlink_info_driver_name_put(req, "nfp");
	अगर (err)
		वापस err;

	venकरोr = nfp_hwinfo_lookup(pf->hwinfo, "assembly.vendor");
	part = nfp_hwinfo_lookup(pf->hwinfo, "assembly.partno");
	sn = nfp_hwinfo_lookup(pf->hwinfo, "assembly.serial");
	अगर (venकरोr && part && sn) अणु
		अक्षर *buf;

		buf = kदो_स्मृति(म_माप(venकरोr) + म_माप(part) + म_माप(sn) + 1,
			      GFP_KERNEL);
		अगर (!buf)
			वापस -ENOMEM;

		buf[0] = '\0';
		म_जोड़ो(buf, venकरोr);
		म_जोड़ो(buf, part);
		म_जोड़ो(buf, sn);

		err = devlink_info_serial_number_put(req, buf);
		kमुक्त(buf);
		अगर (err)
			वापस err;
	पूर्ण

	nsp = nfp_nsp_खोलो(pf->cpp);
	अगर (IS_ERR(nsp)) अणु
		NL_SET_ERR_MSG_MOD(extack, "can't access NSP");
		वापस PTR_ERR(nsp);
	पूर्ण

	अगर (nfp_nsp_has_versions(nsp)) अणु
		buf = kzalloc(NFP_NSP_VERSION_BUFSZ, GFP_KERNEL);
		अगर (!buf) अणु
			err = -ENOMEM;
			जाओ err_बंद_nsp;
		पूर्ण

		err = nfp_nsp_versions(nsp, buf, NFP_NSP_VERSION_BUFSZ);
		अगर (err)
			जाओ err_मुक्त_buf;

		err = nfp_devlink_versions_get_nsp(req, false,
						   buf, NFP_NSP_VERSION_BUFSZ);
		अगर (err)
			जाओ err_मुक्त_buf;

		err = nfp_devlink_versions_get_nsp(req, true,
						   buf, NFP_NSP_VERSION_BUFSZ);
		अगर (err)
			जाओ err_मुक्त_buf;

		kमुक्त(buf);
	पूर्ण

	nfp_nsp_बंद(nsp);

	वापस nfp_devlink_versions_get_hwinfo(pf, req);

err_मुक्त_buf:
	kमुक्त(buf);
err_बंद_nsp:
	nfp_nsp_बंद(nsp);
	वापस err;
पूर्ण

अटल पूर्णांक
nfp_devlink_flash_update(काष्ठा devlink *devlink,
			 काष्ठा devlink_flash_update_params *params,
			 काष्ठा netlink_ext_ack *extack)
अणु
	वापस nfp_flash_update_common(devlink_priv(devlink), params->fw, extack);
पूर्ण

स्थिर काष्ठा devlink_ops nfp_devlink_ops = अणु
	.port_split		= nfp_devlink_port_split,
	.port_unsplit		= nfp_devlink_port_unsplit,
	.sb_pool_get		= nfp_devlink_sb_pool_get,
	.sb_pool_set		= nfp_devlink_sb_pool_set,
	.eचयन_mode_get	= nfp_devlink_eचयन_mode_get,
	.eचयन_mode_set	= nfp_devlink_eचयन_mode_set,
	.info_get		= nfp_devlink_info_get,
	.flash_update		= nfp_devlink_flash_update,
पूर्ण;

पूर्णांक nfp_devlink_port_रेजिस्टर(काष्ठा nfp_app *app, काष्ठा nfp_port *port)
अणु
	काष्ठा devlink_port_attrs attrs = अणुपूर्ण;
	काष्ठा nfp_eth_table_port eth_port;
	काष्ठा devlink *devlink;
	स्थिर u8 *serial;
	पूर्णांक serial_len;
	पूर्णांक ret;

	rtnl_lock();
	ret = nfp_devlink_fill_eth_port(port, &eth_port);
	rtnl_unlock();
	अगर (ret)
		वापस ret;

	attrs.split = eth_port.is_split;
	attrs.splittable = !attrs.split;
	attrs.lanes = eth_port.port_lanes;
	attrs.flavour = DEVLINK_PORT_FLAVOUR_PHYSICAL;
	attrs.phys.port_number = eth_port.label_port;
	attrs.phys.split_subport_number = eth_port.label_subport;
	serial_len = nfp_cpp_serial(port->app->cpp, &serial);
	स_नकल(attrs.चयन_id.id, serial, serial_len);
	attrs.चयन_id.id_len = serial_len;
	devlink_port_attrs_set(&port->dl_port, &attrs);

	devlink = priv_to_devlink(app->pf);

	वापस devlink_port_रेजिस्टर(devlink, &port->dl_port, port->eth_id);
पूर्ण

व्योम nfp_devlink_port_unरेजिस्टर(काष्ठा nfp_port *port)
अणु
	devlink_port_unरेजिस्टर(&port->dl_port);
पूर्ण

व्योम nfp_devlink_port_type_eth_set(काष्ठा nfp_port *port)
अणु
	devlink_port_type_eth_set(&port->dl_port, port->netdev);
पूर्ण

व्योम nfp_devlink_port_type_clear(काष्ठा nfp_port *port)
अणु
	devlink_port_type_clear(&port->dl_port);
पूर्ण

काष्ठा devlink_port *nfp_devlink_get_devlink_port(काष्ठा net_device *netdev)
अणु
	काष्ठा nfp_port *port;

	port = nfp_port_from_netdev(netdev);
	अगर (!port)
		वापस शून्य;

	वापस &port->dl_port;
पूर्ण
