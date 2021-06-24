<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/* Copyright (c) 2017-2019 Mellanox Technologies. All rights reserved */

#घोषणा pr_fmt(fmt) "mlxfw: " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/delay.h>

#समावेश "mlxfw.h"
#समावेश "mlxfw_mfa2.h"

#घोषणा MLXFW_FSM_STATE_WAIT_CYCLE_MS 200
#घोषणा MLXFW_FSM_STATE_WAIT_TIMEOUT_MS 30000
#घोषणा MLXFW_FSM_STATE_WAIT_ROUNDS \
	(MLXFW_FSM_STATE_WAIT_TIMEOUT_MS / MLXFW_FSM_STATE_WAIT_CYCLE_MS)
#घोषणा MLXFW_FSM_MAX_COMPONENT_SIZE (10 * (1 << 20))

अटल स्थिर पूर्णांक mlxfw_fsm_state_त्रुटि_सं[] = अणु
	[MLXFW_FSM_STATE_ERR_ERROR] = -EIO,
	[MLXFW_FSM_STATE_ERR_REJECTED_DIGEST_ERR] = -EBADMSG,
	[MLXFW_FSM_STATE_ERR_REJECTED_NOT_APPLICABLE] = -ENOENT,
	[MLXFW_FSM_STATE_ERR_REJECTED_UNKNOWN_KEY] = -ENOKEY,
	[MLXFW_FSM_STATE_ERR_REJECTED_AUTH_FAILED] = -EACCES,
	[MLXFW_FSM_STATE_ERR_REJECTED_UNSIGNED] = -EKEYREVOKED,
	[MLXFW_FSM_STATE_ERR_REJECTED_KEY_NOT_APPLICABLE] = -EKEYREJECTED,
	[MLXFW_FSM_STATE_ERR_REJECTED_BAD_FORMAT] = -ENOEXEC,
	[MLXFW_FSM_STATE_ERR_BLOCKED_PENDING_RESET] = -EBUSY,
	[MLXFW_FSM_STATE_ERR_MAX] = -EINVAL
पूर्ण;

#घोषणा MLXFW_ERR_PRFX "Firmware flash failed: "
#घोषणा MLXFW_ERR_MSG(fwdev, extack, msg, err) करो अणु \
	mlxfw_err(fwdev, "%s, err (%d)\n", MLXFW_ERR_PRFX msg, err); \
	NL_SET_ERR_MSG_MOD(extack, MLXFW_ERR_PRFX msg); \
पूर्ण जबतक (0)

अटल पूर्णांक mlxfw_fsm_state_err(काष्ठा mlxfw_dev *mlxfw_dev,
			       काष्ठा netlink_ext_ack *extack,
			       क्रमागत mlxfw_fsm_state_err err)
अणु
	क्रमागत mlxfw_fsm_state_err fsm_state_err;

	fsm_state_err = min_t(क्रमागत mlxfw_fsm_state_err, err,
			      MLXFW_FSM_STATE_ERR_MAX);

	चयन (fsm_state_err) अणु
	हाल MLXFW_FSM_STATE_ERR_ERROR:
		MLXFW_ERR_MSG(mlxfw_dev, extack, "general error", err);
		अवरोध;
	हाल MLXFW_FSM_STATE_ERR_REJECTED_DIGEST_ERR:
		MLXFW_ERR_MSG(mlxfw_dev, extack, "component hash mismatch", err);
		अवरोध;
	हाल MLXFW_FSM_STATE_ERR_REJECTED_NOT_APPLICABLE:
		MLXFW_ERR_MSG(mlxfw_dev, extack, "component not applicable", err);
		अवरोध;
	हाल MLXFW_FSM_STATE_ERR_REJECTED_UNKNOWN_KEY:
		MLXFW_ERR_MSG(mlxfw_dev, extack, "unknown key", err);
		अवरोध;
	हाल MLXFW_FSM_STATE_ERR_REJECTED_AUTH_FAILED:
		MLXFW_ERR_MSG(mlxfw_dev, extack, "authentication failed", err);
		अवरोध;
	हाल MLXFW_FSM_STATE_ERR_REJECTED_UNSIGNED:
		MLXFW_ERR_MSG(mlxfw_dev, extack, "component was not signed", err);
		अवरोध;
	हाल MLXFW_FSM_STATE_ERR_REJECTED_KEY_NOT_APPLICABLE:
		MLXFW_ERR_MSG(mlxfw_dev, extack, "key not applicable", err);
		अवरोध;
	हाल MLXFW_FSM_STATE_ERR_REJECTED_BAD_FORMAT:
		MLXFW_ERR_MSG(mlxfw_dev, extack, "bad format", err);
		अवरोध;
	हाल MLXFW_FSM_STATE_ERR_BLOCKED_PENDING_RESET:
		MLXFW_ERR_MSG(mlxfw_dev, extack, "pending reset", err);
		अवरोध;
	हाल MLXFW_FSM_STATE_ERR_OK:
	हाल MLXFW_FSM_STATE_ERR_MAX:
		MLXFW_ERR_MSG(mlxfw_dev, extack, "unknown error", err);
		अवरोध;
	पूर्ण

	वापस mlxfw_fsm_state_त्रुटि_सं[fsm_state_err];
पूर्ण;

अटल पूर्णांक mlxfw_fsm_state_रुको(काष्ठा mlxfw_dev *mlxfw_dev, u32 fwhandle,
				क्रमागत mlxfw_fsm_state fsm_state,
				काष्ठा netlink_ext_ack *extack)
अणु
	क्रमागत mlxfw_fsm_state_err fsm_state_err;
	क्रमागत mlxfw_fsm_state curr_fsm_state;
	पूर्णांक बार;
	पूर्णांक err;

	बार = MLXFW_FSM_STATE_WAIT_ROUNDS;
retry:
	err = mlxfw_dev->ops->fsm_query_state(mlxfw_dev, fwhandle,
					      &curr_fsm_state, &fsm_state_err);
	अगर (err) अणु
		MLXFW_ERR_MSG(mlxfw_dev, extack, "FSM state query failed", err);
		वापस err;
	पूर्ण

	अगर (fsm_state_err != MLXFW_FSM_STATE_ERR_OK)
		वापस mlxfw_fsm_state_err(mlxfw_dev, extack, fsm_state_err);

	अगर (curr_fsm_state != fsm_state) अणु
		अगर (--बार == 0) अणु
			MLXFW_ERR_MSG(mlxfw_dev, extack,
				      "Timeout reached on FSM state change", -ETIMEDOUT);
			वापस -ETIMEDOUT;
		पूर्ण
		msleep(MLXFW_FSM_STATE_WAIT_CYCLE_MS);
		जाओ retry;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक
mlxfw_fsm_reactivate_err(काष्ठा mlxfw_dev *mlxfw_dev,
			 काष्ठा netlink_ext_ack *extack, u8 err)
अणु
	क्रमागत mlxfw_fsm_reactivate_status status;

#घोषणा MXFW_REACT_PRFX "Reactivate FSM: "
#घोषणा MLXFW_REACT_ERR(msg, err) \
	MLXFW_ERR_MSG(mlxfw_dev, extack, MXFW_REACT_PRFX msg, err)

	status = min_t(क्रमागत mlxfw_fsm_reactivate_status, err,
		       MLXFW_FSM_REACTIVATE_STATUS_MAX);

	चयन (status) अणु
	हाल MLXFW_FSM_REACTIVATE_STATUS_BUSY:
		MLXFW_REACT_ERR("busy", err);
		अवरोध;
	हाल MLXFW_FSM_REACTIVATE_STATUS_PROHIBITED_FW_VER_ERR:
		MLXFW_REACT_ERR("prohibited fw ver", err);
		अवरोध;
	हाल MLXFW_FSM_REACTIVATE_STATUS_FIRST_PAGE_COPY_FAILED:
		MLXFW_REACT_ERR("first page copy failed", err);
		अवरोध;
	हाल MLXFW_FSM_REACTIVATE_STATUS_FIRST_PAGE_ERASE_FAILED:
		MLXFW_REACT_ERR("first page erase failed", err);
		अवरोध;
	हाल MLXFW_FSM_REACTIVATE_STATUS_FIRST_PAGE_RESTORE_FAILED:
		MLXFW_REACT_ERR("first page restore failed", err);
		अवरोध;
	हाल MLXFW_FSM_REACTIVATE_STATUS_CANDIDATE_FW_DEACTIVATION_FAILED:
		MLXFW_REACT_ERR("candidate fw deactivation failed", err);
		अवरोध;
	हाल MLXFW_FSM_REACTIVATE_STATUS_ERR_DEVICE_RESET_REQUIRED:
		MLXFW_REACT_ERR("device reset required", err);
		अवरोध;
	हाल MLXFW_FSM_REACTIVATE_STATUS_ERR_FW_PROGRAMMING_NEEDED:
		MLXFW_REACT_ERR("fw programming needed", err);
		अवरोध;
	हाल MLXFW_FSM_REACTIVATE_STATUS_FW_ALREADY_ACTIVATED:
		MLXFW_REACT_ERR("fw already activated", err);
		अवरोध;
	हाल MLXFW_FSM_REACTIVATE_STATUS_OK:
	हाल MLXFW_FSM_REACTIVATE_STATUS_MAX:
		MLXFW_REACT_ERR("unexpected error", err);
		अवरोध;
	पूर्ण
	वापस -EREMOTEIO;
पूर्ण;

अटल पूर्णांक mlxfw_fsm_reactivate(काष्ठा mlxfw_dev *mlxfw_dev,
				काष्ठा netlink_ext_ack *extack,
				bool *supported)
अणु
	u8 status;
	पूर्णांक err;

	अगर (!mlxfw_dev->ops->fsm_reactivate)
		वापस 0;

	err = mlxfw_dev->ops->fsm_reactivate(mlxfw_dev, &status);
	अगर (err == -EOPNOTSUPP) अणु
		*supported = false;
		वापस 0;
	पूर्ण

	अगर (err) अणु
		MLXFW_ERR_MSG(mlxfw_dev, extack,
			      "Could not reactivate firmware flash", err);
		वापस err;
	पूर्ण

	अगर (status == MLXFW_FSM_REACTIVATE_STATUS_OK ||
	    status == MLXFW_FSM_REACTIVATE_STATUS_FW_ALREADY_ACTIVATED)
		वापस 0;

	वापस mlxfw_fsm_reactivate_err(mlxfw_dev, extack, status);
पूर्ण

अटल व्योम mlxfw_status_notअगरy(काष्ठा mlxfw_dev *mlxfw_dev,
				स्थिर अक्षर *msg, स्थिर अक्षर *comp_name,
				u32 करोne_bytes, u32 total_bytes)
अणु
	devlink_flash_update_status_notअगरy(mlxfw_dev->devlink, msg, comp_name,
					   करोne_bytes, total_bytes);
पूर्ण

#घोषणा MLXFW_ALIGN_DOWN(x, align_bits) ((x) & ~((1 << (align_bits)) - 1))
#घोषणा MLXFW_ALIGN_UP(x, align_bits) \
		MLXFW_ALIGN_DOWN((x) + ((1 << (align_bits)) - 1), (align_bits))

अटल पूर्णांक mlxfw_flash_component(काष्ठा mlxfw_dev *mlxfw_dev,
				 u32 fwhandle,
				 काष्ठा mlxfw_mfa2_component *comp,
				 bool reactivate_supp,
				 काष्ठा netlink_ext_ack *extack)
अणु
	u16 comp_max_ग_लिखो_size;
	u8 comp_align_bits;
	u32 comp_max_size;
	अक्षर comp_name[8];
	u16 block_size;
	u8 *block_ptr;
	u32 offset;
	पूर्णांक err;

	प्र_लिखो(comp_name, "%u", comp->index);

	err = mlxfw_dev->ops->component_query(mlxfw_dev, comp->index,
					      &comp_max_size, &comp_align_bits,
					      &comp_max_ग_लिखो_size);
	अगर (err) अणु
		MLXFW_ERR_MSG(mlxfw_dev, extack, "FSM component query failed", err);
		वापस err;
	पूर्ण

	comp_max_size = min_t(u32, comp_max_size, MLXFW_FSM_MAX_COMPONENT_SIZE);
	अगर (comp->data_size > comp_max_size) अणु
		MLXFW_ERR_MSG(mlxfw_dev, extack,
			      "Component size is bigger than limit", -EINVAL);
		वापस -EINVAL;
	पूर्ण

	comp_max_ग_लिखो_size = MLXFW_ALIGN_DOWN(comp_max_ग_लिखो_size,
					       comp_align_bits);

	mlxfw_dbg(mlxfw_dev, "Component update\n");
	mlxfw_status_notअगरy(mlxfw_dev, "Updating component", comp_name, 0, 0);
	err = mlxfw_dev->ops->fsm_component_update(mlxfw_dev, fwhandle,
						   comp->index,
						   comp->data_size);
	अगर (err) अणु
		अगर (!reactivate_supp)
			MLXFW_ERR_MSG(mlxfw_dev, extack,
				      "FSM component update failed, FW reactivate is not supported",
				      err);
		अन्यथा
			MLXFW_ERR_MSG(mlxfw_dev, extack,
				      "FSM component update failed", err);
		वापस err;
	पूर्ण

	err = mlxfw_fsm_state_रुको(mlxfw_dev, fwhandle,
				   MLXFW_FSM_STATE_DOWNLOAD, extack);
	अगर (err)
		जाओ err_out;

	mlxfw_dbg(mlxfw_dev, "Component download\n");
	mlxfw_status_notअगरy(mlxfw_dev, "Downloading component",
			    comp_name, 0, comp->data_size);
	क्रम (offset = 0;
	     offset < MLXFW_ALIGN_UP(comp->data_size, comp_align_bits);
	     offset += comp_max_ग_लिखो_size) अणु
		block_ptr = comp->data + offset;
		block_size = (u16) min_t(u32, comp->data_size - offset,
					 comp_max_ग_लिखो_size);
		err = mlxfw_dev->ops->fsm_block_करोwnload(mlxfw_dev, fwhandle,
							 block_ptr, block_size,
							 offset);
		अगर (err) अणु
			MLXFW_ERR_MSG(mlxfw_dev, extack,
				      "Component download failed", err);
			जाओ err_out;
		पूर्ण
		mlxfw_status_notअगरy(mlxfw_dev, "Downloading component",
				    comp_name, offset + block_size,
				    comp->data_size);
	पूर्ण

	mlxfw_dbg(mlxfw_dev, "Component verify\n");
	mlxfw_status_notअगरy(mlxfw_dev, "Verifying component", comp_name, 0, 0);
	err = mlxfw_dev->ops->fsm_component_verअगरy(mlxfw_dev, fwhandle,
						   comp->index);
	अगर (err) अणु
		MLXFW_ERR_MSG(mlxfw_dev, extack,
			      "FSM component verify failed", err);
		जाओ err_out;
	पूर्ण

	err = mlxfw_fsm_state_रुको(mlxfw_dev, fwhandle,
				   MLXFW_FSM_STATE_LOCKED, extack);
	अगर (err)
		जाओ err_out;
	वापस 0;

err_out:
	mlxfw_dev->ops->fsm_cancel(mlxfw_dev, fwhandle);
	वापस err;
पूर्ण

अटल पूर्णांक mlxfw_flash_components(काष्ठा mlxfw_dev *mlxfw_dev, u32 fwhandle,
				  काष्ठा mlxfw_mfa2_file *mfa2_file,
				  bool reactivate_supp,
				  काष्ठा netlink_ext_ack *extack)
अणु
	u32 component_count;
	पूर्णांक err;
	पूर्णांक i;

	err = mlxfw_mfa2_file_component_count(mfa2_file, mlxfw_dev->psid,
					      mlxfw_dev->psid_size,
					      &component_count);
	अगर (err) अणु
		MLXFW_ERR_MSG(mlxfw_dev, extack,
			      "Could not find device PSID in MFA2 file", err);
		वापस err;
	पूर्ण

	क्रम (i = 0; i < component_count; i++) अणु
		काष्ठा mlxfw_mfa2_component *comp;

		comp = mlxfw_mfa2_file_component_get(mfa2_file, mlxfw_dev->psid,
						     mlxfw_dev->psid_size, i);
		अगर (IS_ERR(comp)) अणु
			err = PTR_ERR(comp);
			MLXFW_ERR_MSG(mlxfw_dev, extack,
				      "Failed to get MFA2 component", err);
			वापस err;
		पूर्ण

		mlxfw_info(mlxfw_dev, "Flashing component type %d\n",
			   comp->index);
		err = mlxfw_flash_component(mlxfw_dev, fwhandle, comp,
					    reactivate_supp, extack);
		mlxfw_mfa2_file_component_put(comp);
		अगर (err)
			वापस err;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक mlxfw_firmware_flash(काष्ठा mlxfw_dev *mlxfw_dev,
			 स्थिर काष्ठा firmware *firmware,
			 काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mlxfw_mfa2_file *mfa2_file;
	bool reactivate_supp = true;
	u32 fwhandle;
	पूर्णांक err;

	अगर (!mlxfw_mfa2_check(firmware)) अणु
		MLXFW_ERR_MSG(mlxfw_dev, extack,
			      "Firmware file is not MFA2", -EINVAL);
		वापस -EINVAL;
	पूर्ण

	mfa2_file = mlxfw_mfa2_file_init(firmware);
	अगर (IS_ERR(mfa2_file)) अणु
		err = PTR_ERR(mfa2_file);
		MLXFW_ERR_MSG(mlxfw_dev, extack,
			      "Failed to initialize MFA2 firmware file", err);
		वापस err;
	पूर्ण

	mlxfw_info(mlxfw_dev, "Initialize firmware flash process\n");
	mlxfw_status_notअगरy(mlxfw_dev, "Initializing firmware flash process",
			    शून्य, 0, 0);
	err = mlxfw_dev->ops->fsm_lock(mlxfw_dev, &fwhandle);
	अगर (err) अणु
		MLXFW_ERR_MSG(mlxfw_dev, extack,
			      "Could not lock the firmware FSM", err);
		जाओ err_fsm_lock;
	पूर्ण

	err = mlxfw_fsm_state_रुको(mlxfw_dev, fwhandle,
				   MLXFW_FSM_STATE_LOCKED, extack);
	अगर (err)
		जाओ err_state_रुको_idle_to_locked;

	err = mlxfw_fsm_reactivate(mlxfw_dev, extack, &reactivate_supp);
	अगर (err)
		जाओ err_fsm_reactivate;

	err = mlxfw_fsm_state_रुको(mlxfw_dev, fwhandle,
				   MLXFW_FSM_STATE_LOCKED, extack);
	अगर (err)
		जाओ err_state_रुको_reactivate_to_locked;

	err = mlxfw_flash_components(mlxfw_dev, fwhandle, mfa2_file,
				     reactivate_supp, extack);
	अगर (err)
		जाओ err_flash_components;

	mlxfw_dbg(mlxfw_dev, "Activate image\n");
	mlxfw_status_notअगरy(mlxfw_dev, "Activating image", शून्य, 0, 0);
	err = mlxfw_dev->ops->fsm_activate(mlxfw_dev, fwhandle);
	अगर (err) अणु
		MLXFW_ERR_MSG(mlxfw_dev, extack,
			      "Could not activate the downloaded image", err);
		जाओ err_fsm_activate;
	पूर्ण

	err = mlxfw_fsm_state_रुको(mlxfw_dev, fwhandle,
				   MLXFW_FSM_STATE_LOCKED, extack);
	अगर (err)
		जाओ err_state_रुको_activate_to_locked;

	mlxfw_dbg(mlxfw_dev, "Handle release\n");
	mlxfw_dev->ops->fsm_release(mlxfw_dev, fwhandle);

	mlxfw_info(mlxfw_dev, "Firmware flash done\n");
	mlxfw_status_notअगरy(mlxfw_dev, "Firmware flash done", शून्य, 0, 0);
	mlxfw_mfa2_file_fini(mfa2_file);
	वापस 0;

err_state_रुको_activate_to_locked:
err_fsm_activate:
err_flash_components:
err_state_रुको_reactivate_to_locked:
err_fsm_reactivate:
err_state_रुको_idle_to_locked:
	mlxfw_dev->ops->fsm_release(mlxfw_dev, fwhandle);
err_fsm_lock:
	mlxfw_mfa2_file_fini(mfa2_file);
	वापस err;
पूर्ण
EXPORT_SYMBOL(mlxfw_firmware_flash);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("Yotam Gigi <yotamg@mellanox.com>");
MODULE_DESCRIPTION("Mellanox firmware flash lib");
