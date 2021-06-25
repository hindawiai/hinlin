<शैली गुरु>
/* SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0 */
/* Copyright (c) 2017-2019 Mellanox Technologies. All rights reserved */

#अगर_अघोषित _MLXFW_H
#घोषणा _MLXFW_H

#समावेश <linux/firmware.h>
#समावेश <linux/netlink.h>
#समावेश <linux/device.h>
#समावेश <net/devlink.h>

काष्ठा mlxfw_dev अणु
	स्थिर काष्ठा mlxfw_dev_ops *ops;
	स्थिर अक्षर *psid;
	u16 psid_size;
	काष्ठा devlink *devlink;
पूर्ण;

अटल अंतरभूत
काष्ठा device *mlxfw_dev_dev(काष्ठा mlxfw_dev *mlxfw_dev)
अणु
	वापस mlxfw_dev->devlink->dev;
पूर्ण

#घोषणा MLXFW_PRFX "mlxfw: "

#घोषणा mlxfw_info(mlxfw_dev, fmt, ...) \
	dev_info(mlxfw_dev_dev(mlxfw_dev), MLXFW_PRFX fmt, ## __VA_ARGS__)
#घोषणा mlxfw_err(mlxfw_dev, fmt, ...) \
	dev_err(mlxfw_dev_dev(mlxfw_dev), MLXFW_PRFX fmt, ## __VA_ARGS__)
#घोषणा mlxfw_dbg(mlxfw_dev, fmt, ...) \
	dev_dbg(mlxfw_dev_dev(mlxfw_dev), MLXFW_PRFX fmt, ## __VA_ARGS__)

क्रमागत mlxfw_fsm_state अणु
	MLXFW_FSM_STATE_IDLE,
	MLXFW_FSM_STATE_LOCKED,
	MLXFW_FSM_STATE_INITIALIZE,
	MLXFW_FSM_STATE_DOWNLOAD,
	MLXFW_FSM_STATE_VERIFY,
	MLXFW_FSM_STATE_APPLY,
	MLXFW_FSM_STATE_ACTIVATE,
पूर्ण;

क्रमागत mlxfw_fsm_state_err अणु
	MLXFW_FSM_STATE_ERR_OK,
	MLXFW_FSM_STATE_ERR_ERROR,
	MLXFW_FSM_STATE_ERR_REJECTED_DIGEST_ERR,
	MLXFW_FSM_STATE_ERR_REJECTED_NOT_APPLICABLE,
	MLXFW_FSM_STATE_ERR_REJECTED_UNKNOWN_KEY,
	MLXFW_FSM_STATE_ERR_REJECTED_AUTH_FAILED,
	MLXFW_FSM_STATE_ERR_REJECTED_UNSIGNED,
	MLXFW_FSM_STATE_ERR_REJECTED_KEY_NOT_APPLICABLE,
	MLXFW_FSM_STATE_ERR_REJECTED_BAD_FORMAT,
	MLXFW_FSM_STATE_ERR_BLOCKED_PENDING_RESET,
	MLXFW_FSM_STATE_ERR_MAX,
पूर्ण;

क्रमागत mlxfw_fsm_reactivate_status अणु
	MLXFW_FSM_REACTIVATE_STATUS_OK,
	MLXFW_FSM_REACTIVATE_STATUS_BUSY,
	MLXFW_FSM_REACTIVATE_STATUS_PROHIBITED_FW_VER_ERR,
	MLXFW_FSM_REACTIVATE_STATUS_FIRST_PAGE_COPY_FAILED,
	MLXFW_FSM_REACTIVATE_STATUS_FIRST_PAGE_ERASE_FAILED,
	MLXFW_FSM_REACTIVATE_STATUS_FIRST_PAGE_RESTORE_FAILED,
	MLXFW_FSM_REACTIVATE_STATUS_CANDIDATE_FW_DEACTIVATION_FAILED,
	MLXFW_FSM_REACTIVATE_STATUS_FW_ALREADY_ACTIVATED,
	MLXFW_FSM_REACTIVATE_STATUS_ERR_DEVICE_RESET_REQUIRED,
	MLXFW_FSM_REACTIVATE_STATUS_ERR_FW_PROGRAMMING_NEEDED,
	MLXFW_FSM_REACTIVATE_STATUS_MAX,
पूर्ण;

काष्ठा mlxfw_dev_ops अणु
	पूर्णांक (*component_query)(काष्ठा mlxfw_dev *mlxfw_dev, u16 component_index,
			       u32 *p_max_size, u8 *p_align_bits,
			       u16 *p_max_ग_लिखो_size);

	पूर्णांक (*fsm_lock)(काष्ठा mlxfw_dev *mlxfw_dev, u32 *fwhandle);

	पूर्णांक (*fsm_component_update)(काष्ठा mlxfw_dev *mlxfw_dev, u32 fwhandle,
				    u16 component_index, u32 component_size);

	पूर्णांक (*fsm_block_करोwnload)(काष्ठा mlxfw_dev *mlxfw_dev, u32 fwhandle,
				  u8 *data, u16 size, u32 offset);

	पूर्णांक (*fsm_component_verअगरy)(काष्ठा mlxfw_dev *mlxfw_dev, u32 fwhandle,
				    u16 component_index);

	पूर्णांक (*fsm_activate)(काष्ठा mlxfw_dev *mlxfw_dev, u32 fwhandle);

	पूर्णांक (*fsm_reactivate)(काष्ठा mlxfw_dev *mlxfw_dev, u8 *status);

	पूर्णांक (*fsm_query_state)(काष्ठा mlxfw_dev *mlxfw_dev, u32 fwhandle,
			       क्रमागत mlxfw_fsm_state *fsm_state,
			       क्रमागत mlxfw_fsm_state_err *fsm_state_err);

	व्योम (*fsm_cancel)(काष्ठा mlxfw_dev *mlxfw_dev, u32 fwhandle);

	व्योम (*fsm_release)(काष्ठा mlxfw_dev *mlxfw_dev, u32 fwhandle);
पूर्ण;

#अगर IS_REACHABLE(CONFIG_MLXFW)
पूर्णांक mlxfw_firmware_flash(काष्ठा mlxfw_dev *mlxfw_dev,
			 स्थिर काष्ठा firmware *firmware,
			 काष्ठा netlink_ext_ack *extack);
#अन्यथा
अटल अंतरभूत
पूर्णांक mlxfw_firmware_flash(काष्ठा mlxfw_dev *mlxfw_dev,
			 स्थिर काष्ठा firmware *firmware,
			 काष्ठा netlink_ext_ack *extack)
अणु
	वापस -EOPNOTSUPP;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
