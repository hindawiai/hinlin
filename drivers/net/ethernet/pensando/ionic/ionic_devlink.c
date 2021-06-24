<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2017 - 2019 Pensanकरो Systems, Inc */

#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>

#समावेश "ionic.h"
#समावेश "ionic_bus.h"
#समावेश "ionic_lif.h"
#समावेश "ionic_devlink.h"

अटल पूर्णांक ionic_dl_flash_update(काष्ठा devlink *dl,
				 काष्ठा devlink_flash_update_params *params,
				 काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा ionic *ionic = devlink_priv(dl);

	वापस ionic_firmware_update(ionic->lअगर, params->fw, extack);
पूर्ण

अटल पूर्णांक ionic_dl_info_get(काष्ठा devlink *dl, काष्ठा devlink_info_req *req,
			     काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा ionic *ionic = devlink_priv(dl);
	काष्ठा ionic_dev *idev = &ionic->idev;
	अक्षर buf[16];
	पूर्णांक err = 0;

	err = devlink_info_driver_name_put(req, IONIC_DRV_NAME);
	अगर (err)
		वापस err;

	err = devlink_info_version_running_put(req,
					       DEVLINK_INFO_VERSION_GENERIC_FW,
					       idev->dev_info.fw_version);
	अगर (err)
		वापस err;

	snम_लिखो(buf, माप(buf), "0x%x", idev->dev_info.asic_type);
	err = devlink_info_version_fixed_put(req,
					     DEVLINK_INFO_VERSION_GENERIC_ASIC_ID,
					     buf);
	अगर (err)
		वापस err;

	snम_लिखो(buf, माप(buf), "0x%x", idev->dev_info.asic_rev);
	err = devlink_info_version_fixed_put(req,
					     DEVLINK_INFO_VERSION_GENERIC_ASIC_REV,
					     buf);
	अगर (err)
		वापस err;

	err = devlink_info_serial_number_put(req, idev->dev_info.serial_num);

	वापस err;
पूर्ण

अटल स्थिर काष्ठा devlink_ops ionic_dl_ops = अणु
	.info_get	= ionic_dl_info_get,
	.flash_update	= ionic_dl_flash_update,
पूर्ण;

काष्ठा ionic *ionic_devlink_alloc(काष्ठा device *dev)
अणु
	काष्ठा devlink *dl;

	dl = devlink_alloc(&ionic_dl_ops, माप(काष्ठा ionic));

	वापस devlink_priv(dl);
पूर्ण

व्योम ionic_devlink_मुक्त(काष्ठा ionic *ionic)
अणु
	काष्ठा devlink *dl = priv_to_devlink(ionic);

	devlink_मुक्त(dl);
पूर्ण

पूर्णांक ionic_devlink_रेजिस्टर(काष्ठा ionic *ionic)
अणु
	काष्ठा devlink *dl = priv_to_devlink(ionic);
	काष्ठा devlink_port_attrs attrs = अणुपूर्ण;
	पूर्णांक err;

	err = devlink_रेजिस्टर(dl, ionic->dev);
	अगर (err) अणु
		dev_warn(ionic->dev, "devlink_register failed: %d\n", err);
		वापस err;
	पूर्ण

	attrs.flavour = DEVLINK_PORT_FLAVOUR_PHYSICAL;
	devlink_port_attrs_set(&ionic->dl_port, &attrs);
	err = devlink_port_रेजिस्टर(dl, &ionic->dl_port, 0);
	अगर (err)
		dev_err(ionic->dev, "devlink_port_register failed: %d\n", err);
	अन्यथा
		devlink_port_type_eth_set(&ionic->dl_port,
					  ionic->lअगर->netdev);

	वापस err;
पूर्ण

व्योम ionic_devlink_unरेजिस्टर(काष्ठा ionic *ionic)
अणु
	काष्ठा devlink *dl = priv_to_devlink(ionic);

	अगर (ionic->dl_port.रेजिस्टरed)
		devlink_port_unरेजिस्टर(&ionic->dl_port);
	devlink_unरेजिस्टर(dl);
पूर्ण
