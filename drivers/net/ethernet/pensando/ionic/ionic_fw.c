<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2020 Pensanकरो Systems, Inc */

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/firmware.h>

#समावेश "ionic.h"
#समावेश "ionic_dev.h"
#समावेश "ionic_lif.h"
#समावेश "ionic_devlink.h"

/* The worst हाल रुको क्रम the install activity is about 25 minutes when
 * installing a new CPLD, which is very selकरोm.  Normal is about 30-35
 * seconds.  Since the driver can't tell अगर a CPLD update will happen we
 * set the समयout क्रम the ugly हाल.
 */
#घोषणा IONIC_FW_INSTALL_TIMEOUT	(25 * 60)
#घोषणा IONIC_FW_SELECT_TIMEOUT		30

/* Number of periodic log updates during fw file करोwnload */
#घोषणा IONIC_FW_INTERVAL_FRACTION	32

अटल व्योम ionic_dev_cmd_firmware_करोwnload(काष्ठा ionic_dev *idev, u64 addr,
					    u32 offset, u32 length)
अणु
	जोड़ ionic_dev_cmd cmd = अणु
		.fw_करोwnload.opcode = IONIC_CMD_FW_DOWNLOAD,
		.fw_करोwnload.offset = cpu_to_le32(offset),
		.fw_करोwnload.addr = cpu_to_le64(addr),
		.fw_करोwnload.length = cpu_to_le32(length),
	पूर्ण;

	ionic_dev_cmd_go(idev, &cmd);
पूर्ण

अटल व्योम ionic_dev_cmd_firmware_install(काष्ठा ionic_dev *idev)
अणु
	जोड़ ionic_dev_cmd cmd = अणु
		.fw_control.opcode = IONIC_CMD_FW_CONTROL,
		.fw_control.oper = IONIC_FW_INSTALL_ASYNC
	पूर्ण;

	ionic_dev_cmd_go(idev, &cmd);
पूर्ण

अटल व्योम ionic_dev_cmd_firmware_activate(काष्ठा ionic_dev *idev, u8 slot)
अणु
	जोड़ ionic_dev_cmd cmd = अणु
		.fw_control.opcode = IONIC_CMD_FW_CONTROL,
		.fw_control.oper = IONIC_FW_ACTIVATE_ASYNC,
		.fw_control.slot = slot
	पूर्ण;

	ionic_dev_cmd_go(idev, &cmd);
पूर्ण

अटल पूर्णांक ionic_fw_status_दीर्घ_रुको(काष्ठा ionic *ionic,
				     स्थिर अक्षर *label,
				     अचिन्हित दीर्घ समयout,
				     u8 fw_cmd,
				     काष्ठा netlink_ext_ack *extack)
अणु
	जोड़ ionic_dev_cmd cmd = अणु
		.fw_control.opcode = IONIC_CMD_FW_CONTROL,
		.fw_control.oper = fw_cmd,
	पूर्ण;
	अचिन्हित दीर्घ start_समय;
	अचिन्हित दीर्घ end_समय;
	पूर्णांक err;

	start_समय = jअगरfies;
	end_समय = start_समय + (समयout * HZ);
	करो अणु
		mutex_lock(&ionic->dev_cmd_lock);
		ionic_dev_cmd_go(&ionic->idev, &cmd);
		err = ionic_dev_cmd_रुको(ionic, DEVCMD_TIMEOUT);
		mutex_unlock(&ionic->dev_cmd_lock);

		msleep(20);
	पूर्ण जबतक (समय_beक्रमe(jअगरfies, end_समय) && (err == -EAGAIN || err == -ETIMEDOUT));

	अगर (err == -EAGAIN || err == -ETIMEDOUT) अणु
		NL_SET_ERR_MSG_MOD(extack, "Firmware wait timed out");
		dev_err(ionic->dev, "DEV_CMD firmware wait %s timed out\n", label);
	पूर्ण अन्यथा अगर (err) अणु
		NL_SET_ERR_MSG_MOD(extack, "Firmware wait failed");
	पूर्ण

	वापस err;
पूर्ण

पूर्णांक ionic_firmware_update(काष्ठा ionic_lअगर *lअगर, स्थिर काष्ठा firmware *fw,
			  काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा ionic_dev *idev = &lअगर->ionic->idev;
	काष्ठा net_device *netdev = lअगर->netdev;
	काष्ठा ionic *ionic = lअगर->ionic;
	जोड़ ionic_dev_cmd_comp comp;
	u32 buf_sz, copy_sz, offset;
	काष्ठा devlink *dl;
	पूर्णांक next_पूर्णांकerval;
	पूर्णांक err = 0;
	u8 fw_slot;

	netdev_info(netdev, "Installing firmware\n");

	dl = priv_to_devlink(ionic);
	devlink_flash_update_status_notअगरy(dl, "Preparing to flash", शून्य, 0, 0);

	buf_sz = माप(idev->dev_cmd_regs->data);

	netdev_dbg(netdev,
		   "downloading firmware - size %d part_sz %d nparts %lu\n",
		   (पूर्णांक)fw->size, buf_sz, DIV_ROUND_UP(fw->size, buf_sz));

	offset = 0;
	next_पूर्णांकerval = 0;
	जबतक (offset < fw->size) अणु
		अगर (offset >= next_पूर्णांकerval) अणु
			devlink_flash_update_status_notअगरy(dl, "Downloading", शून्य,
							   offset, fw->size);
			next_पूर्णांकerval = offset + (fw->size / IONIC_FW_INTERVAL_FRACTION);
		पूर्ण

		copy_sz = min_t(अचिन्हित पूर्णांक, buf_sz, fw->size - offset);
		mutex_lock(&ionic->dev_cmd_lock);
		स_नकल_toio(&idev->dev_cmd_regs->data, fw->data + offset, copy_sz);
		ionic_dev_cmd_firmware_करोwnload(idev,
						दुरत्व(जोड़ ionic_dev_cmd_regs, data),
						offset, copy_sz);
		err = ionic_dev_cmd_रुको(ionic, DEVCMD_TIMEOUT);
		mutex_unlock(&ionic->dev_cmd_lock);
		अगर (err) अणु
			netdev_err(netdev,
				   "download failed offset 0x%x addr 0x%lx len 0x%x\n",
				   offset, दुरत्व(जोड़ ionic_dev_cmd_regs, data),
				   copy_sz);
			NL_SET_ERR_MSG_MOD(extack, "Segment download failed");
			जाओ err_out;
		पूर्ण
		offset += copy_sz;
	पूर्ण
	devlink_flash_update_status_notअगरy(dl, "Downloading", शून्य,
					   fw->size, fw->size);

	devlink_flash_update_समयout_notअगरy(dl, "Installing", शून्य,
					    IONIC_FW_INSTALL_TIMEOUT);

	mutex_lock(&ionic->dev_cmd_lock);
	ionic_dev_cmd_firmware_install(idev);
	err = ionic_dev_cmd_रुको(ionic, DEVCMD_TIMEOUT);
	ionic_dev_cmd_comp(idev, (जोड़ ionic_dev_cmd_comp *)&comp);
	fw_slot = comp.fw_control.slot;
	mutex_unlock(&ionic->dev_cmd_lock);
	अगर (err) अणु
		NL_SET_ERR_MSG_MOD(extack, "Failed to start firmware install");
		जाओ err_out;
	पूर्ण

	err = ionic_fw_status_दीर्घ_रुको(ionic, "Installing",
					IONIC_FW_INSTALL_TIMEOUT,
					IONIC_FW_INSTALL_STATUS,
					extack);
	अगर (err)
		जाओ err_out;

	devlink_flash_update_समयout_notअगरy(dl, "Selecting", शून्य,
					    IONIC_FW_SELECT_TIMEOUT);

	mutex_lock(&ionic->dev_cmd_lock);
	ionic_dev_cmd_firmware_activate(idev, fw_slot);
	err = ionic_dev_cmd_रुको(ionic, DEVCMD_TIMEOUT);
	mutex_unlock(&ionic->dev_cmd_lock);
	अगर (err) अणु
		NL_SET_ERR_MSG_MOD(extack, "Failed to start firmware select");
		जाओ err_out;
	पूर्ण

	err = ionic_fw_status_दीर्घ_रुको(ionic, "Selecting",
					IONIC_FW_SELECT_TIMEOUT,
					IONIC_FW_ACTIVATE_STATUS,
					extack);
	अगर (err)
		जाओ err_out;

	netdev_info(netdev, "Firmware update completed\n");

err_out:
	अगर (err)
		devlink_flash_update_status_notअगरy(dl, "Flash failed", शून्य, 0, 0);
	अन्यथा
		devlink_flash_update_status_notअगरy(dl, "Flash done", शून्य, 0, 0);
	वापस err;
पूर्ण
