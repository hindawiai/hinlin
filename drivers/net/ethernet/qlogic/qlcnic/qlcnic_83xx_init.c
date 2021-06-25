<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * QLogic qlcnic NIC Driver
 * Copyright (c) 2009-2013 QLogic Corporation
 */

#समावेश "qlcnic_sriov.h"
#समावेश "qlcnic.h"
#समावेश "qlcnic_hw.h"

/* Reset ढाँचा definitions */
#घोषणा QLC_83XX_RESTART_TEMPLATE_SIZE		0x2000
#घोषणा QLC_83XX_RESET_TEMPLATE_ADDR		0x4F0000
#घोषणा QLC_83XX_RESET_SEQ_VERSION		0x0101

#घोषणा QLC_83XX_OPCODE_NOP			0x0000
#घोषणा QLC_83XX_OPCODE_WRITE_LIST		0x0001
#घोषणा QLC_83XX_OPCODE_READ_WRITE_LIST		0x0002
#घोषणा QLC_83XX_OPCODE_POLL_LIST		0x0004
#घोषणा QLC_83XX_OPCODE_POLL_WRITE_LIST		0x0008
#घोषणा QLC_83XX_OPCODE_READ_MODIFY_WRITE	0x0010
#घोषणा QLC_83XX_OPCODE_SEQ_PAUSE		0x0020
#घोषणा QLC_83XX_OPCODE_SEQ_END			0x0040
#घोषणा QLC_83XX_OPCODE_TMPL_END		0x0080
#घोषणा QLC_83XX_OPCODE_POLL_READ_LIST		0x0100

/* EPORT control रेजिस्टरs */
#घोषणा QLC_83XX_RESET_CONTROL			0x28084E50
#घोषणा QLC_83XX_RESET_REG			0x28084E60
#घोषणा QLC_83XX_RESET_PORT0			0x28084E70
#घोषणा QLC_83XX_RESET_PORT1			0x28084E80
#घोषणा QLC_83XX_RESET_PORT2			0x28084E90
#घोषणा QLC_83XX_RESET_PORT3			0x28084EA0
#घोषणा QLC_83XX_RESET_SRESHIM			0x28084EB0
#घोषणा QLC_83XX_RESET_EPGSHIM			0x28084EC0
#घोषणा QLC_83XX_RESET_ETHERPCS			0x28084ED0

अटल पूर्णांक qlcnic_83xx_init_शेष_driver(काष्ठा qlcnic_adapter *adapter);
अटल पूर्णांक qlcnic_83xx_check_heartbeat(काष्ठा qlcnic_adapter *p_dev);
अटल पूर्णांक qlcnic_83xx_restart_hw(काष्ठा qlcnic_adapter *adapter);
अटल पूर्णांक qlcnic_83xx_check_hw_status(काष्ठा qlcnic_adapter *p_dev);
अटल पूर्णांक qlcnic_83xx_get_reset_inकाष्ठाion_ढाँचा(काष्ठा qlcnic_adapter *);
अटल व्योम qlcnic_83xx_stop_hw(काष्ठा qlcnic_adapter *);

/* Template header */
काष्ठा qlc_83xx_reset_hdr अणु
#अगर defined(__LITTLE_ENDIAN)
	u16	version;
	u16	signature;
	u16	size;
	u16	entries;
	u16	hdr_size;
	u16	checksum;
	u16	init_offset;
	u16	start_offset;
#या_अगर defined(__BIG_ENDIAN)
	u16	signature;
	u16	version;
	u16	entries;
	u16	size;
	u16	checksum;
	u16	hdr_size;
	u16	start_offset;
	u16	init_offset;
#पूर्ण_अगर
पूर्ण __packed;

/* Command entry header. */
काष्ठा qlc_83xx_entry_hdr अणु
#अगर defined(__LITTLE_ENDIAN)
	u16	cmd;
	u16	size;
	u16	count;
	u16	delay;
#या_अगर defined(__BIG_ENDIAN)
	u16	size;
	u16	cmd;
	u16	delay;
	u16	count;
#पूर्ण_अगर
पूर्ण __packed;

/* Generic poll command */
काष्ठा qlc_83xx_poll अणु
	u32	mask;
	u32	status;
पूर्ण __packed;

/* Read modअगरy ग_लिखो command */
काष्ठा qlc_83xx_rmw अणु
	u32	mask;
	u32	xor_value;
	u32	or_value;
#अगर defined(__LITTLE_ENDIAN)
	u8	shl;
	u8	shr;
	u8	index_a;
	u8	rsvd;
#या_अगर defined(__BIG_ENDIAN)
	u8	rsvd;
	u8	index_a;
	u8	shr;
	u8	shl;
#पूर्ण_अगर
पूर्ण __packed;

/* Generic command with 2 DWORD */
काष्ठा qlc_83xx_entry अणु
	u32 arg1;
	u32 arg2;
पूर्ण __packed;

/* Generic command with 4 DWORD */
काष्ठा qlc_83xx_quad_entry अणु
	u32 dr_addr;
	u32 dr_value;
	u32 ar_addr;
	u32 ar_value;
पूर्ण __packed;
अटल स्थिर अक्षर *स्थिर qlc_83xx_idc_states[] = अणु
	"Unknown",
	"Cold",
	"Init",
	"Ready",
	"Need Reset",
	"Need Quiesce",
	"Failed",
	"Quiesce"
पूर्ण;

अटल पूर्णांक
qlcnic_83xx_idc_check_driver_presence_reg(काष्ठा qlcnic_adapter *adapter)
अणु
	u32 val;

	val = QLCRDX(adapter->ahw, QLC_83XX_IDC_DRV_PRESENCE);
	अगर ((val & 0xFFFF))
		वापस 1;
	अन्यथा
		वापस 0;
पूर्ण

अटल व्योम qlcnic_83xx_idc_log_state_history(काष्ठा qlcnic_adapter *adapter)
अणु
	u32 cur, prev;
	cur = adapter->ahw->idc.curr_state;
	prev = adapter->ahw->idc.prev_state;

	dev_info(&adapter->pdev->dev,
		 "current state  = %s,  prev state = %s\n",
		 adapter->ahw->idc.name[cur],
		 adapter->ahw->idc.name[prev]);
पूर्ण

अटल पूर्णांक qlcnic_83xx_idc_update_audit_reg(काष्ठा qlcnic_adapter *adapter,
					    u8 mode, पूर्णांक lock)
अणु
	u32 val;
	पूर्णांक seconds;

	अगर (lock) अणु
		अगर (qlcnic_83xx_lock_driver(adapter))
			वापस -EBUSY;
	पूर्ण

	val = QLCRDX(adapter->ahw, QLC_83XX_IDC_DRV_AUDIT);
	val |= (adapter->portnum & 0xf);
	val |= mode << 7;
	अगर (mode)
		seconds = jअगरfies / HZ - adapter->ahw->idc.sec_counter;
	अन्यथा
		seconds = jअगरfies / HZ;

	val |= seconds << 8;
	QLCWRX(adapter->ahw, QLC_83XX_IDC_DRV_AUDIT, val);
	adapter->ahw->idc.sec_counter = jअगरfies / HZ;

	अगर (lock)
		qlcnic_83xx_unlock_driver(adapter);

	वापस 0;
पूर्ण

अटल व्योम qlcnic_83xx_idc_update_minor_version(काष्ठा qlcnic_adapter *adapter)
अणु
	u32 val;

	val = QLCRDX(adapter->ahw, QLC_83XX_IDC_MIN_VERSION);
	val = val & ~(0x3 << (adapter->portnum * 2));
	val = val | (QLC_83XX_IDC_MINOR_VERSION << (adapter->portnum * 2));
	QLCWRX(adapter->ahw, QLC_83XX_IDC_MIN_VERSION, val);
पूर्ण

अटल पूर्णांक qlcnic_83xx_idc_update_major_version(काष्ठा qlcnic_adapter *adapter,
						पूर्णांक lock)
अणु
	u32 val;

	अगर (lock) अणु
		अगर (qlcnic_83xx_lock_driver(adapter))
			वापस -EBUSY;
	पूर्ण

	val = QLCRDX(adapter->ahw, QLC_83XX_IDC_MAJ_VERSION);
	val = val & ~0xFF;
	val = val | QLC_83XX_IDC_MAJOR_VERSION;
	QLCWRX(adapter->ahw, QLC_83XX_IDC_MAJ_VERSION, val);

	अगर (lock)
		qlcnic_83xx_unlock_driver(adapter);

	वापस 0;
पूर्ण

अटल पूर्णांक
qlcnic_83xx_idc_update_drv_presence_reg(काष्ठा qlcnic_adapter *adapter,
					पूर्णांक status, पूर्णांक lock)
अणु
	u32 val;

	अगर (lock) अणु
		अगर (qlcnic_83xx_lock_driver(adapter))
			वापस -EBUSY;
	पूर्ण

	val = QLCRDX(adapter->ahw, QLC_83XX_IDC_DRV_PRESENCE);

	अगर (status)
		val = val | (1 << adapter->portnum);
	अन्यथा
		val = val & ~(1 << adapter->portnum);

	QLCWRX(adapter->ahw, QLC_83XX_IDC_DRV_PRESENCE, val);
	qlcnic_83xx_idc_update_minor_version(adapter);

	अगर (lock)
		qlcnic_83xx_unlock_driver(adapter);

	वापस 0;
पूर्ण

अटल पूर्णांक qlcnic_83xx_idc_check_major_version(काष्ठा qlcnic_adapter *adapter)
अणु
	u32 val;
	u8 version;

	val = QLCRDX(adapter->ahw, QLC_83XX_IDC_MAJ_VERSION);
	version = val & 0xFF;

	अगर (version != QLC_83XX_IDC_MAJOR_VERSION) अणु
		dev_info(&adapter->pdev->dev,
			 "%s:mismatch. version 0x%x, expected version 0x%x\n",
			 __func__, version, QLC_83XX_IDC_MAJOR_VERSION);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक qlcnic_83xx_idc_clear_रेजिस्टरs(काष्ठा qlcnic_adapter *adapter,
					   पूर्णांक lock)
अणु
	u32 val;

	अगर (lock) अणु
		अगर (qlcnic_83xx_lock_driver(adapter))
			वापस -EBUSY;
	पूर्ण

	QLCWRX(adapter->ahw, QLC_83XX_IDC_DRV_ACK, 0);
	/* Clear graceful reset bit */
	val = QLCRDX(adapter->ahw, QLC_83XX_IDC_CTRL);
	val &= ~QLC_83XX_IDC_GRACEFULL_RESET;
	QLCWRX(adapter->ahw, QLC_83XX_IDC_CTRL, val);

	अगर (lock)
		qlcnic_83xx_unlock_driver(adapter);

	वापस 0;
पूर्ण

अटल पूर्णांक qlcnic_83xx_idc_update_drv_ack_reg(काष्ठा qlcnic_adapter *adapter,
					      पूर्णांक flag, पूर्णांक lock)
अणु
	u32 val;

	अगर (lock) अणु
		अगर (qlcnic_83xx_lock_driver(adapter))
			वापस -EBUSY;
	पूर्ण

	val = QLCRDX(adapter->ahw, QLC_83XX_IDC_DRV_ACK);
	अगर (flag)
		val = val | (1 << adapter->portnum);
	अन्यथा
		val = val & ~(1 << adapter->portnum);
	QLCWRX(adapter->ahw, QLC_83XX_IDC_DRV_ACK, val);

	अगर (lock)
		qlcnic_83xx_unlock_driver(adapter);

	वापस 0;
पूर्ण

अटल पूर्णांक qlcnic_83xx_idc_check_समयout(काष्ठा qlcnic_adapter *adapter,
					 पूर्णांक समय_limit)
अणु
	u64 seconds;

	seconds = jअगरfies / HZ - adapter->ahw->idc.sec_counter;
	अगर (seconds <= समय_limit)
		वापस 0;
	अन्यथा
		वापस -EBUSY;
पूर्ण

/**
 * qlcnic_83xx_idc_check_reset_ack_reg
 *
 * @adapter: adapter काष्ठाure
 *
 * Check ACK रुको limit and clear the functions which failed to ACK
 *
 * Return 0 अगर all functions have acknowledged the reset request.
 **/
अटल पूर्णांक qlcnic_83xx_idc_check_reset_ack_reg(काष्ठा qlcnic_adapter *adapter)
अणु
	पूर्णांक समयout;
	u32 ack, presence, val;

	समयout = QLC_83XX_IDC_RESET_TIMEOUT_SECS;
	ack = QLCRDX(adapter->ahw, QLC_83XX_IDC_DRV_ACK);
	presence = QLCRDX(adapter->ahw, QLC_83XX_IDC_DRV_PRESENCE);
	dev_info(&adapter->pdev->dev,
		 "%s: ack = 0x%x, presence = 0x%x\n", __func__, ack, presence);
	अगर (!((ack & presence) == presence)) अणु
		अगर (qlcnic_83xx_idc_check_समयout(adapter, समयout)) अणु
			/* Clear functions which failed to ACK */
			dev_info(&adapter->pdev->dev,
				 "%s: ACK wait exceeds time limit\n", __func__);
			val = QLCRDX(adapter->ahw, QLC_83XX_IDC_DRV_PRESENCE);
			val = val & ~(ack ^ presence);
			अगर (qlcnic_83xx_lock_driver(adapter))
				वापस -EBUSY;
			QLCWRX(adapter->ahw, QLC_83XX_IDC_DRV_PRESENCE, val);
			dev_info(&adapter->pdev->dev,
				 "%s: updated drv presence reg = 0x%x\n",
				 __func__, val);
			qlcnic_83xx_unlock_driver(adapter);
			वापस 0;

		पूर्ण अन्यथा अणु
			वापस 1;
		पूर्ण
	पूर्ण अन्यथा अणु
		dev_info(&adapter->pdev->dev,
			 "%s: Reset ACK received from all functions\n",
			 __func__);
		वापस 0;
	पूर्ण
पूर्ण

/**
 * qlcnic_83xx_idc_tx_soft_reset
 *
 * @adapter: adapter काष्ठाure
 *
 * Handle context deletion and recreation request from transmit routine
 *
 * Returns -EBUSY  or Success (0)
 *
 **/
अटल पूर्णांक qlcnic_83xx_idc_tx_soft_reset(काष्ठा qlcnic_adapter *adapter)
अणु
	काष्ठा net_device *netdev = adapter->netdev;

	अगर (test_and_set_bit(__QLCNIC_RESETTING, &adapter->state))
		वापस -EBUSY;

	netअगर_device_detach(netdev);
	qlcnic_करोwn(adapter, netdev);
	qlcnic_up(adapter, netdev);
	netअगर_device_attach(netdev);
	clear_bit(__QLCNIC_RESETTING, &adapter->state);
	netdev_info(adapter->netdev, "%s: soft reset complete.\n", __func__);

	वापस 0;
पूर्ण

/**
 * qlcnic_83xx_idc_detach_driver
 *
 * @adapter: adapter काष्ठाure
 * Detach net पूर्णांकerface, stop TX and cleanup resources beक्रमe the HW reset.
 * Returns: None
 *
 **/
अटल व्योम qlcnic_83xx_idc_detach_driver(काष्ठा qlcnic_adapter *adapter)
अणु
	पूर्णांक i;
	काष्ठा net_device *netdev = adapter->netdev;

	netअगर_device_detach(netdev);
	qlcnic_83xx_detach_mailbox_work(adapter);

	/* Disable mailbox पूर्णांकerrupt */
	qlcnic_83xx_disable_mbx_पूर्णांकr(adapter);
	qlcnic_करोwn(adapter, netdev);
	क्रम (i = 0; i < adapter->ahw->num_msix; i++) अणु
		adapter->ahw->पूर्णांकr_tbl[i].id = i;
		adapter->ahw->पूर्णांकr_tbl[i].enabled = 0;
		adapter->ahw->पूर्णांकr_tbl[i].src = 0;
	पूर्ण

	अगर (qlcnic_sriov_pf_check(adapter))
		qlcnic_sriov_pf_reset(adapter);
पूर्ण

/**
 * qlcnic_83xx_idc_attach_driver
 *
 * @adapter: adapter काष्ठाure
 *
 * Re-attach and re-enable net पूर्णांकerface
 * Returns: None
 *
 **/
अटल व्योम qlcnic_83xx_idc_attach_driver(काष्ठा qlcnic_adapter *adapter)
अणु
	काष्ठा net_device *netdev = adapter->netdev;

	अगर (netअगर_running(netdev)) अणु
		अगर (qlcnic_up(adapter, netdev))
			जाओ करोne;
		qlcnic_restore_indev_addr(netdev, NETDEV_UP);
	पूर्ण
करोne:
	netअगर_device_attach(netdev);
पूर्ण

अटल पूर्णांक qlcnic_83xx_idc_enter_failed_state(काष्ठा qlcnic_adapter *adapter,
					      पूर्णांक lock)
अणु
	अगर (lock) अणु
		अगर (qlcnic_83xx_lock_driver(adapter))
			वापस -EBUSY;
	पूर्ण

	qlcnic_83xx_idc_clear_रेजिस्टरs(adapter, 0);
	QLCWRX(adapter->ahw, QLC_83XX_IDC_DEV_STATE, QLC_83XX_IDC_DEV_FAILED);
	अगर (lock)
		qlcnic_83xx_unlock_driver(adapter);

	qlcnic_83xx_idc_log_state_history(adapter);
	dev_info(&adapter->pdev->dev, "Device will enter failed state\n");

	वापस 0;
पूर्ण

अटल पूर्णांक qlcnic_83xx_idc_enter_init_state(काष्ठा qlcnic_adapter *adapter,
					    पूर्णांक lock)
अणु
	अगर (lock) अणु
		अगर (qlcnic_83xx_lock_driver(adapter))
			वापस -EBUSY;
	पूर्ण

	QLCWRX(adapter->ahw, QLC_83XX_IDC_DEV_STATE, QLC_83XX_IDC_DEV_INIT);

	अगर (lock)
		qlcnic_83xx_unlock_driver(adapter);

	वापस 0;
पूर्ण

अटल पूर्णांक qlcnic_83xx_idc_enter_need_quiesce(काष्ठा qlcnic_adapter *adapter,
					      पूर्णांक lock)
अणु
	अगर (lock) अणु
		अगर (qlcnic_83xx_lock_driver(adapter))
			वापस -EBUSY;
	पूर्ण

	QLCWRX(adapter->ahw, QLC_83XX_IDC_DEV_STATE,
	       QLC_83XX_IDC_DEV_NEED_QUISCENT);

	अगर (lock)
		qlcnic_83xx_unlock_driver(adapter);

	वापस 0;
पूर्ण

अटल पूर्णांक
qlcnic_83xx_idc_enter_need_reset_state(काष्ठा qlcnic_adapter *adapter, पूर्णांक lock)
अणु
	अगर (lock) अणु
		अगर (qlcnic_83xx_lock_driver(adapter))
			वापस -EBUSY;
	पूर्ण

	QLCWRX(adapter->ahw, QLC_83XX_IDC_DEV_STATE,
	       QLC_83XX_IDC_DEV_NEED_RESET);

	अगर (lock)
		qlcnic_83xx_unlock_driver(adapter);

	वापस 0;
पूर्ण

अटल पूर्णांक qlcnic_83xx_idc_enter_पढ़ोy_state(काष्ठा qlcnic_adapter *adapter,
					     पूर्णांक lock)
अणु
	अगर (lock) अणु
		अगर (qlcnic_83xx_lock_driver(adapter))
			वापस -EBUSY;
	पूर्ण

	QLCWRX(adapter->ahw, QLC_83XX_IDC_DEV_STATE, QLC_83XX_IDC_DEV_READY);
	अगर (lock)
		qlcnic_83xx_unlock_driver(adapter);

	वापस 0;
पूर्ण

/**
 * qlcnic_83xx_idc_find_reset_owner_id
 *
 * @adapter: adapter काष्ठाure
 *
 * NIC माला_लो precedence over ISCSI and ISCSI has precedence over FCOE.
 * Within the same class, function with lowest PCI ID assumes ownership
 *
 * Returns: reset owner id or failure indication (-EIO)
 *
 **/
अटल पूर्णांक qlcnic_83xx_idc_find_reset_owner_id(काष्ठा qlcnic_adapter *adapter)
अणु
	u32 reg, reg1, reg2, i, j, owner, class;

	reg1 = QLCRDX(adapter->ahw, QLC_83XX_IDC_DEV_PARTITION_INFO_1);
	reg2 = QLCRDX(adapter->ahw, QLC_83XX_IDC_DEV_PARTITION_INFO_2);
	owner = QLCNIC_TYPE_NIC;
	i = 0;
	j = 0;
	reg = reg1;

	करो अणु
		class = (((reg & (0xF << j * 4)) >> j * 4) & 0x3);
		अगर (class == owner)
			अवरोध;
		अगर (i == (QLC_83XX_IDC_MAX_FUNC_PER_PARTITION_INFO - 1)) अणु
			reg = reg2;
			j = 0;
		पूर्ण अन्यथा अणु
			j++;
		पूर्ण

		अगर (i == (QLC_83XX_IDC_MAX_CNA_FUNCTIONS - 1)) अणु
			अगर (owner == QLCNIC_TYPE_NIC)
				owner = QLCNIC_TYPE_ISCSI;
			अन्यथा अगर (owner == QLCNIC_TYPE_ISCSI)
				owner = QLCNIC_TYPE_FCOE;
			अन्यथा अगर (owner == QLCNIC_TYPE_FCOE)
				वापस -EIO;
			reg = reg1;
			j = 0;
			i = 0;
		पूर्ण
	पूर्ण जबतक (i++ < QLC_83XX_IDC_MAX_CNA_FUNCTIONS);

	वापस i;
पूर्ण

अटल पूर्णांक qlcnic_83xx_idc_restart_hw(काष्ठा qlcnic_adapter *adapter, पूर्णांक lock)
अणु
	पूर्णांक ret = 0;

	ret = qlcnic_83xx_restart_hw(adapter);

	अगर (ret) अणु
		qlcnic_83xx_idc_enter_failed_state(adapter, lock);
	पूर्ण अन्यथा अणु
		qlcnic_83xx_idc_clear_रेजिस्टरs(adapter, lock);
		ret = qlcnic_83xx_idc_enter_पढ़ोy_state(adapter, lock);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक qlcnic_83xx_idc_check_fan_failure(काष्ठा qlcnic_adapter *adapter)
अणु
	u32 status;

	status = QLC_SHARED_REG_RD32(adapter, QLCNIC_PEG_HALT_STATUS1);

	अगर (status & QLCNIC_RCODE_FATAL_ERROR) अणु
		dev_err(&adapter->pdev->dev,
			"peg halt status1=0x%x\n", status);
		अगर (QLCNIC_FWERROR_CODE(status) == QLCNIC_FWERROR_FAN_FAILURE) अणु
			dev_err(&adapter->pdev->dev,
				"On board active cooling fan failed. "
				"Device has been halted.\n");
			dev_err(&adapter->pdev->dev,
				"Replace the adapter.\n");
			वापस -EIO;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक qlcnic_83xx_idc_reattach_driver(काष्ठा qlcnic_adapter *adapter)
अणु
	पूर्णांक err;

	qlcnic_83xx_reinit_mbx_work(adapter->ahw->mailbox);
	qlcnic_83xx_enable_mbx_पूर्णांकerrupt(adapter);

	qlcnic_83xx_initialize_nic(adapter, 1);

	err = qlcnic_sriov_pf_reinit(adapter);
	अगर (err)
		वापस err;

	qlcnic_83xx_enable_mbx_पूर्णांकerrupt(adapter);

	अगर (qlcnic_83xx_configure_opmode(adapter)) अणु
		qlcnic_83xx_idc_enter_failed_state(adapter, 1);
		वापस -EIO;
	पूर्ण

	अगर (adapter->nic_ops->init_driver(adapter)) अणु
		qlcnic_83xx_idc_enter_failed_state(adapter, 1);
		वापस -EIO;
	पूर्ण

	अगर (adapter->portnum == 0)
		qlcnic_set_drv_version(adapter);

	qlcnic_dcb_get_info(adapter->dcb);
	qlcnic_83xx_idc_attach_driver(adapter);

	वापस 0;
पूर्ण

अटल व्योम qlcnic_83xx_idc_update_idc_params(काष्ठा qlcnic_adapter *adapter)
अणु
	काष्ठा qlcnic_hardware_context *ahw = adapter->ahw;

	qlcnic_83xx_idc_update_drv_presence_reg(adapter, 1, 1);
	qlcnic_83xx_idc_update_audit_reg(adapter, 0, 1);
	set_bit(QLC_83XX_MODULE_LOADED, &adapter->ahw->idc.status);

	ahw->idc.quiesce_req = 0;
	ahw->idc.delay = QLC_83XX_IDC_FW_POLL_DELAY;
	ahw->idc.err_code = 0;
	ahw->idc.collect_dump = 0;
	ahw->reset_context = 0;
	adapter->tx_समयo_cnt = 0;
	ahw->idc.delay_reset = 0;

	clear_bit(__QLCNIC_RESETTING, &adapter->state);
पूर्ण

/**
 * qlcnic_83xx_idc_पढ़ोy_state_entry
 *
 * @adapter: adapter काष्ठाure
 *
 * Perक्रमm पढ़ोy state initialization, this routine will get invoked only
 * once from READY state.
 *
 * Returns: Error code or Success(0)
 *
 **/
पूर्णांक qlcnic_83xx_idc_पढ़ोy_state_entry(काष्ठा qlcnic_adapter *adapter)
अणु
	काष्ठा qlcnic_hardware_context *ahw = adapter->ahw;

	अगर (ahw->idc.prev_state != QLC_83XX_IDC_DEV_READY) अणु
		qlcnic_83xx_idc_update_idc_params(adapter);
		/* Re-attach the device अगर required */
		अगर ((ahw->idc.prev_state == QLC_83XX_IDC_DEV_NEED_RESET) ||
		    (ahw->idc.prev_state == QLC_83XX_IDC_DEV_INIT)) अणु
			अगर (qlcnic_83xx_idc_reattach_driver(adapter))
				वापस -EIO;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/**
 * qlcnic_83xx_idc_vnic_pf_entry
 *
 * @adapter: adapter काष्ठाure
 *
 * Ensure vNIC mode privileged function starts only after vNIC mode is
 * enabled by management function.
 * If vNIC mode is पढ़ोy, start initialization.
 *
 * Returns: -EIO or 0
 *
 **/
पूर्णांक qlcnic_83xx_idc_vnic_pf_entry(काष्ठा qlcnic_adapter *adapter)
अणु
	u32 state;
	काष्ठा qlcnic_hardware_context *ahw = adapter->ahw;

	/* Privileged function रुकोs till mgmt function enables VNIC mode */
	state = QLCRDX(adapter->ahw, QLC_83XX_VNIC_STATE);
	अगर (state != QLCNIC_DEV_NPAR_OPER) अणु
		अगर (!ahw->idc.vnic_रुको_limit--) अणु
			qlcnic_83xx_idc_enter_failed_state(adapter, 1);
			वापस -EIO;
		पूर्ण
		dev_info(&adapter->pdev->dev, "vNIC mode disabled\n");
		वापस -EIO;

	पूर्ण अन्यथा अणु
		/* Perक्रमm one समय initialization from पढ़ोy state */
		अगर (ahw->idc.vnic_state != QLCNIC_DEV_NPAR_OPER) अणु
			qlcnic_83xx_idc_update_idc_params(adapter);

			/* If the previous state is UNKNOWN, device will be
			   alपढ़ोy attached properly by Init routine*/
			अगर (ahw->idc.prev_state != QLC_83XX_IDC_DEV_UNKNOWN) अणु
				अगर (qlcnic_83xx_idc_reattach_driver(adapter))
					वापस -EIO;
			पूर्ण
			adapter->ahw->idc.vnic_state =  QLCNIC_DEV_NPAR_OPER;
			dev_info(&adapter->pdev->dev, "vNIC mode enabled\n");
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक qlcnic_83xx_idc_unknown_state(काष्ठा qlcnic_adapter *adapter)
अणु
	adapter->ahw->idc.err_code = -EIO;
	dev_err(&adapter->pdev->dev,
		"%s: Device in unknown state\n", __func__);
	clear_bit(__QLCNIC_RESETTING, &adapter->state);
	वापस 0;
पूर्ण

/**
 * qlcnic_83xx_idc_cold_state
 *
 * @adapter: adapter काष्ठाure
 *
 * If HW is up and running device will enter READY state.
 * If firmware image from host needs to be loaded, device is
 * क्रमced to start with the file firmware image.
 *
 * Returns: Error code or Success(0)
 *
 **/
अटल पूर्णांक qlcnic_83xx_idc_cold_state_handler(काष्ठा qlcnic_adapter *adapter)
अणु
	qlcnic_83xx_idc_update_drv_presence_reg(adapter, 1, 0);
	qlcnic_83xx_idc_update_audit_reg(adapter, 1, 0);

	अगर (qlcnic_load_fw_file) अणु
		qlcnic_83xx_idc_restart_hw(adapter, 0);
	पूर्ण अन्यथा अणु
		अगर (qlcnic_83xx_check_hw_status(adapter)) अणु
			qlcnic_83xx_idc_enter_failed_state(adapter, 0);
			वापस -EIO;
		पूर्ण अन्यथा अणु
			qlcnic_83xx_idc_enter_पढ़ोy_state(adapter, 0);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/**
 * qlcnic_83xx_idc_init_state
 *
 * @adapter: adapter काष्ठाure
 *
 * Reset owner will restart the device from this state.
 * Device will enter failed state अगर it reमुख्यs
 * in this state क्रम more than DEV_INIT समय limit.
 *
 * Returns: Error code or Success(0)
 *
 **/
अटल पूर्णांक qlcnic_83xx_idc_init_state(काष्ठा qlcnic_adapter *adapter)
अणु
	पूर्णांक समयout, ret = 0;
	u32 owner;

	समयout = QLC_83XX_IDC_INIT_TIMEOUT_SECS;
	अगर (adapter->ahw->idc.prev_state == QLC_83XX_IDC_DEV_NEED_RESET) अणु
		owner = qlcnic_83xx_idc_find_reset_owner_id(adapter);
		अगर (adapter->ahw->pci_func == owner)
			ret = qlcnic_83xx_idc_restart_hw(adapter, 1);
	पूर्ण अन्यथा अणु
		ret = qlcnic_83xx_idc_check_समयout(adapter, समयout);
	पूर्ण

	वापस ret;
पूर्ण

/**
 * qlcnic_83xx_idc_पढ़ोy_state
 *
 * @adapter: adapter काष्ठाure
 *
 * Perक्रमm IDC protocol specicअगरed actions after monitoring device state and
 * events.
 *
 * Returns: Error code or Success(0)
 *
 **/
अटल पूर्णांक qlcnic_83xx_idc_पढ़ोy_state(काष्ठा qlcnic_adapter *adapter)
अणु
	काष्ठा qlcnic_hardware_context *ahw = adapter->ahw;
	काष्ठा qlcnic_mailbox *mbx = ahw->mailbox;
	पूर्णांक ret = 0;
	u32 val;

	/* Perक्रमm NIC configuration based पढ़ोy state entry actions */
	अगर (ahw->idc.state_entry(adapter))
		वापस -EIO;

	अगर (qlcnic_check_temp(adapter)) अणु
		अगर (ahw->temp == QLCNIC_TEMP_PANIC) अणु
			qlcnic_83xx_idc_check_fan_failure(adapter);
			dev_err(&adapter->pdev->dev,
				"Error: device temperature %d above limits\n",
				adapter->ahw->temp);
			clear_bit(QLC_83XX_MBX_READY, &mbx->status);
			set_bit(__QLCNIC_RESETTING, &adapter->state);
			qlcnic_83xx_idc_detach_driver(adapter);
			qlcnic_83xx_idc_enter_failed_state(adapter, 1);
			वापस -EIO;
		पूर्ण
	पूर्ण

	val = QLCRDX(adapter->ahw, QLC_83XX_IDC_CTRL);
	ret = qlcnic_83xx_check_heartbeat(adapter);
	अगर (ret) अणु
		adapter->flags |= QLCNIC_FW_HANG;
		अगर (!(val & QLC_83XX_IDC_DISABLE_FW_RESET_RECOVERY)) अणु
			clear_bit(QLC_83XX_MBX_READY, &mbx->status);
			set_bit(__QLCNIC_RESETTING, &adapter->state);
			qlcnic_83xx_idc_enter_need_reset_state(adapter, 1);
		पूर्ण  अन्यथा अणु
			netdev_info(adapter->netdev, "%s: Auto firmware recovery is disabled\n",
				    __func__);
			qlcnic_83xx_idc_enter_failed_state(adapter, 1);
		पूर्ण
		वापस -EIO;
	पूर्ण

	अगर ((val & QLC_83XX_IDC_GRACEFULL_RESET) || ahw->idc.collect_dump) अणु
		clear_bit(QLC_83XX_MBX_READY, &mbx->status);

		/* Move to need reset state and prepare क्रम reset */
		qlcnic_83xx_idc_enter_need_reset_state(adapter, 1);
		वापस ret;
	पूर्ण

	/* Check क्रम soft reset request */
	अगर (ahw->reset_context &&
	    !(val & QLC_83XX_IDC_DISABLE_FW_RESET_RECOVERY)) अणु
		adapter->ahw->reset_context = 0;
		qlcnic_83xx_idc_tx_soft_reset(adapter);
		वापस ret;
	पूर्ण

	/* Move to need quiesce state अगर requested */
	अगर (adapter->ahw->idc.quiesce_req) अणु
		qlcnic_83xx_idc_enter_need_quiesce(adapter, 1);
		qlcnic_83xx_idc_update_audit_reg(adapter, 0, 1);
		वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

/**
 * qlcnic_83xx_idc_need_reset_state
 *
 * @adapter: adapter काष्ठाure
 *
 * Device will reमुख्य in this state until:
 *	Reset request ACK's are received from all the functions
 *	Wait समय exceeds max समय limit
 *
 * Returns: Error code or Success(0)
 *
 **/
अटल पूर्णांक qlcnic_83xx_idc_need_reset_state(काष्ठा qlcnic_adapter *adapter)
अणु
	काष्ठा qlcnic_mailbox *mbx = adapter->ahw->mailbox;
	पूर्णांक ret = 0;

	अगर (adapter->ahw->idc.prev_state != QLC_83XX_IDC_DEV_NEED_RESET) अणु
		qlcnic_83xx_idc_update_audit_reg(adapter, 0, 1);
		set_bit(__QLCNIC_RESETTING, &adapter->state);
		clear_bit(QLC_83XX_MBX_READY, &mbx->status);
		अगर (adapter->ahw->nic_mode == QLCNIC_VNIC_MODE)
			qlcnic_83xx_disable_vnic_mode(adapter, 1);

		अगर (qlcnic_check_diag_status(adapter)) अणु
			dev_info(&adapter->pdev->dev,
				 "%s: Wait for diag completion\n", __func__);
			adapter->ahw->idc.delay_reset = 1;
			वापस 0;
		पूर्ण अन्यथा अणु
			qlcnic_83xx_idc_update_drv_ack_reg(adapter, 1, 1);
			qlcnic_83xx_idc_detach_driver(adapter);
		पूर्ण
	पूर्ण

	अगर (qlcnic_check_diag_status(adapter)) अणु
		dev_info(&adapter->pdev->dev,
			 "%s: Wait for diag completion\n", __func__);
		वापस  -1;
	पूर्ण अन्यथा अणु
		अगर (adapter->ahw->idc.delay_reset) अणु
			qlcnic_83xx_idc_update_drv_ack_reg(adapter, 1, 1);
			qlcnic_83xx_idc_detach_driver(adapter);
			adapter->ahw->idc.delay_reset = 0;
		पूर्ण

		/* Check क्रम ACK from other functions */
		ret = qlcnic_83xx_idc_check_reset_ack_reg(adapter);
		अगर (ret) अणु
			dev_info(&adapter->pdev->dev,
				 "%s: Waiting for reset ACK\n", __func__);
			वापस -1;
		पूर्ण
	पूर्ण

	/* Transit to INIT state and restart the HW */
	qlcnic_83xx_idc_enter_init_state(adapter, 1);

	वापस ret;
पूर्ण

अटल पूर्णांक qlcnic_83xx_idc_need_quiesce_state(काष्ठा qlcnic_adapter *adapter)
अणु
	dev_err(&adapter->pdev->dev, "%s: TBD\n", __func__);
	वापस 0;
पूर्ण

अटल व्योम qlcnic_83xx_idc_failed_state(काष्ठा qlcnic_adapter *adapter)
अणु
	काष्ठा qlcnic_hardware_context *ahw = adapter->ahw;
	u32 val, owner;

	val = QLCRDX(adapter->ahw, QLC_83XX_IDC_CTRL);
	अगर (val & QLC_83XX_IDC_DISABLE_FW_RESET_RECOVERY) अणु
		owner = qlcnic_83xx_idc_find_reset_owner_id(adapter);
		अगर (ahw->pci_func == owner) अणु
			qlcnic_83xx_stop_hw(adapter);
			qlcnic_dump_fw(adapter);
		पूर्ण
	पूर्ण

	netdev_warn(adapter->netdev, "%s: Reboot will be required to recover the adapter!!\n",
		    __func__);
	clear_bit(__QLCNIC_RESETTING, &adapter->state);
	ahw->idc.err_code = -EIO;

	वापस;
पूर्ण

अटल पूर्णांक qlcnic_83xx_idc_quiesce_state(काष्ठा qlcnic_adapter *adapter)
अणु
	dev_info(&adapter->pdev->dev, "%s: TBD\n", __func__);
	वापस 0;
पूर्ण

अटल पूर्णांक qlcnic_83xx_idc_check_state_validity(काष्ठा qlcnic_adapter *adapter,
						u32 state)
अणु
	u32 cur, prev, next;

	cur = adapter->ahw->idc.curr_state;
	prev = adapter->ahw->idc.prev_state;
	next = state;

	अगर ((next < QLC_83XX_IDC_DEV_COLD) ||
	    (next > QLC_83XX_IDC_DEV_QUISCENT)) अणु
		dev_err(&adapter->pdev->dev,
			"%s: curr %d, prev %d, next state %d is  invalid\n",
			__func__, cur, prev, state);
		वापस 1;
	पूर्ण

	अगर ((cur == QLC_83XX_IDC_DEV_UNKNOWN) &&
	    (prev == QLC_83XX_IDC_DEV_UNKNOWN)) अणु
		अगर ((next != QLC_83XX_IDC_DEV_COLD) &&
		    (next != QLC_83XX_IDC_DEV_READY)) अणु
			dev_err(&adapter->pdev->dev,
				"%s: failed, cur %d prev %d next %d\n",
				__func__, cur, prev, next);
			वापस 1;
		पूर्ण
	पूर्ण

	अगर (next == QLC_83XX_IDC_DEV_INIT) अणु
		अगर ((prev != QLC_83XX_IDC_DEV_INIT) &&
		    (prev != QLC_83XX_IDC_DEV_COLD) &&
		    (prev != QLC_83XX_IDC_DEV_NEED_RESET)) अणु
			dev_err(&adapter->pdev->dev,
				"%s: failed, cur %d prev %d next %d\n",
				__func__, cur, prev, next);
			वापस 1;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

#घोषणा QLC_83XX_ENCAP_TYPE_VXLAN	BIT_1
#घोषणा QLC_83XX_MATCH_ENCAP_ID		BIT_2
#घोषणा QLC_83XX_SET_VXLAN_UDP_DPORT	BIT_3
#घोषणा QLC_83XX_VXLAN_UDP_DPORT(PORT)	((PORT & 0xffff) << 16)

#घोषणा QLCNIC_ENABLE_INGRESS_ENCAP_PARSING 1
#घोषणा QLCNIC_DISABLE_INGRESS_ENCAP_PARSING 0

पूर्णांक qlcnic_set_vxlan_port(काष्ठा qlcnic_adapter *adapter, u16 port)
अणु
	काष्ठा qlcnic_cmd_args cmd;
	पूर्णांक ret = 0;

	स_रखो(&cmd, 0, माप(cmd));

	ret = qlcnic_alloc_mbx_args(&cmd, adapter,
				    QLCNIC_CMD_INIT_NIC_FUNC);
	अगर (ret)
		वापस ret;

	cmd.req.arg[1] = QLC_83XX_MULTI_TEन_अंकCY_INFO;
	cmd.req.arg[2] = QLC_83XX_ENCAP_TYPE_VXLAN |
			 QLC_83XX_SET_VXLAN_UDP_DPORT |
			 QLC_83XX_VXLAN_UDP_DPORT(port);

	ret = qlcnic_issue_cmd(adapter, &cmd);
	अगर (ret)
		netdev_err(adapter->netdev,
			   "Failed to set VXLAN port %d in adapter\n",
			   port);

	qlcnic_मुक्त_mbx_args(&cmd);

	वापस ret;
पूर्ण

पूर्णांक qlcnic_set_vxlan_parsing(काष्ठा qlcnic_adapter *adapter, u16 port)
अणु
	काष्ठा qlcnic_cmd_args cmd;
	पूर्णांक ret = 0;

	स_रखो(&cmd, 0, माप(cmd));

	ret = qlcnic_alloc_mbx_args(&cmd, adapter,
				    QLCNIC_CMD_SET_INGRESS_ENCAP);
	अगर (ret)
		वापस ret;

	cmd.req.arg[1] = port ? QLCNIC_ENABLE_INGRESS_ENCAP_PARSING :
				QLCNIC_DISABLE_INGRESS_ENCAP_PARSING;

	ret = qlcnic_issue_cmd(adapter, &cmd);
	अगर (ret)
		netdev_err(adapter->netdev,
			   "Failed to %s VXLAN parsing for port %d\n",
			   port ? "enable" : "disable", port);
	अन्यथा
		netdev_info(adapter->netdev,
			    "%s VXLAN parsing for port %d\n",
			    port ? "Enabled" : "Disabled", port);

	qlcnic_मुक्त_mbx_args(&cmd);

	वापस ret;
पूर्ण

अटल व्योम qlcnic_83xx_periodic_tasks(काष्ठा qlcnic_adapter *adapter)
अणु
	अगर (adapter->fhash.fnum)
		qlcnic_prune_lb_filters(adapter);
पूर्ण

/**
 * qlcnic_83xx_idc_poll_dev_state
 *
 * @work: kernel work queue काष्ठाure used to schedule the function
 *
 * Poll device state periodically and perक्रमm state specअगरic
 * actions defined by Inter Driver Communication (IDC) protocol.
 *
 * Returns: None
 *
 **/
व्योम qlcnic_83xx_idc_poll_dev_state(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा qlcnic_adapter *adapter;
	u32 state;

	adapter = container_of(work, काष्ठा qlcnic_adapter, fw_work.work);
	state =	QLCRDX(adapter->ahw, QLC_83XX_IDC_DEV_STATE);

	अगर (qlcnic_83xx_idc_check_state_validity(adapter, state)) अणु
		qlcnic_83xx_idc_log_state_history(adapter);
		adapter->ahw->idc.curr_state = QLC_83XX_IDC_DEV_UNKNOWN;
	पूर्ण अन्यथा अणु
		adapter->ahw->idc.curr_state = state;
	पूर्ण

	चयन (adapter->ahw->idc.curr_state) अणु
	हाल QLC_83XX_IDC_DEV_READY:
		qlcnic_83xx_idc_पढ़ोy_state(adapter);
		अवरोध;
	हाल QLC_83XX_IDC_DEV_NEED_RESET:
		qlcnic_83xx_idc_need_reset_state(adapter);
		अवरोध;
	हाल QLC_83XX_IDC_DEV_NEED_QUISCENT:
		qlcnic_83xx_idc_need_quiesce_state(adapter);
		अवरोध;
	हाल QLC_83XX_IDC_DEV_FAILED:
		qlcnic_83xx_idc_failed_state(adapter);
		वापस;
	हाल QLC_83XX_IDC_DEV_INIT:
		qlcnic_83xx_idc_init_state(adapter);
		अवरोध;
	हाल QLC_83XX_IDC_DEV_QUISCENT:
		qlcnic_83xx_idc_quiesce_state(adapter);
		अवरोध;
	शेष:
		qlcnic_83xx_idc_unknown_state(adapter);
		वापस;
	पूर्ण
	adapter->ahw->idc.prev_state = adapter->ahw->idc.curr_state;
	qlcnic_83xx_periodic_tasks(adapter);

	/* Re-schedule the function */
	अगर (test_bit(QLC_83XX_MODULE_LOADED, &adapter->ahw->idc.status))
		qlcnic_schedule_work(adapter, qlcnic_83xx_idc_poll_dev_state,
				     adapter->ahw->idc.delay);
पूर्ण

अटल व्योम qlcnic_83xx_setup_idc_parameters(काष्ठा qlcnic_adapter *adapter)
अणु
	u32 idc_params, val;

	अगर (qlcnic_83xx_flash_पढ़ो32(adapter, QLC_83XX_IDC_FLASH_PARAM_ADDR,
				     (u8 *)&idc_params, 1)) अणु
		dev_info(&adapter->pdev->dev,
			 "%s:failed to get IDC params from flash\n", __func__);
		adapter->dev_init_समयo = QLC_83XX_IDC_INIT_TIMEOUT_SECS;
		adapter->reset_ack_समयo = QLC_83XX_IDC_RESET_TIMEOUT_SECS;
	पूर्ण अन्यथा अणु
		adapter->dev_init_समयo = idc_params & 0xFFFF;
		adapter->reset_ack_समयo = ((idc_params >> 16) & 0xFFFF);
	पूर्ण

	adapter->ahw->idc.curr_state = QLC_83XX_IDC_DEV_UNKNOWN;
	adapter->ahw->idc.prev_state = QLC_83XX_IDC_DEV_UNKNOWN;
	adapter->ahw->idc.delay = QLC_83XX_IDC_FW_POLL_DELAY;
	adapter->ahw->idc.err_code = 0;
	adapter->ahw->idc.collect_dump = 0;
	adapter->ahw->idc.name = (अक्षर **)qlc_83xx_idc_states;

	clear_bit(__QLCNIC_RESETTING, &adapter->state);
	set_bit(QLC_83XX_MODULE_LOADED, &adapter->ahw->idc.status);

	/* Check अगर reset recovery is disabled */
	अगर (!qlcnic_स्वतः_fw_reset) अणु
		/* Propagate करो not reset request to other functions */
		val = QLCRDX(adapter->ahw, QLC_83XX_IDC_CTRL);
		val = val | QLC_83XX_IDC_DISABLE_FW_RESET_RECOVERY;
		QLCWRX(adapter->ahw, QLC_83XX_IDC_CTRL, val);
	पूर्ण
पूर्ण

अटल पूर्णांक
qlcnic_83xx_idc_first_to_load_function_handler(काष्ठा qlcnic_adapter *adapter)
अणु
	u32 state, val;

	अगर (qlcnic_83xx_lock_driver(adapter))
		वापस -EIO;

	/* Clear driver lock रेजिस्टर */
	QLCWRX(adapter->ahw, QLC_83XX_RECOVER_DRV_LOCK, 0);
	अगर (qlcnic_83xx_idc_update_major_version(adapter, 0)) अणु
		qlcnic_83xx_unlock_driver(adapter);
		वापस -EIO;
	पूर्ण

	state =	QLCRDX(adapter->ahw, QLC_83XX_IDC_DEV_STATE);
	अगर (qlcnic_83xx_idc_check_state_validity(adapter, state)) अणु
		qlcnic_83xx_unlock_driver(adapter);
		वापस -EIO;
	पूर्ण

	अगर (state != QLC_83XX_IDC_DEV_COLD && qlcnic_load_fw_file) अणु
		QLCWRX(adapter->ahw, QLC_83XX_IDC_DEV_STATE,
		       QLC_83XX_IDC_DEV_COLD);
		state = QLC_83XX_IDC_DEV_COLD;
	पूर्ण

	adapter->ahw->idc.curr_state = state;
	/* First to load function should cold boot the device */
	अगर (state == QLC_83XX_IDC_DEV_COLD)
		qlcnic_83xx_idc_cold_state_handler(adapter);

	/* Check अगर reset recovery is enabled */
	अगर (qlcnic_स्वतः_fw_reset) अणु
		val = QLCRDX(adapter->ahw, QLC_83XX_IDC_CTRL);
		val = val & ~QLC_83XX_IDC_DISABLE_FW_RESET_RECOVERY;
		QLCWRX(adapter->ahw, QLC_83XX_IDC_CTRL, val);
	पूर्ण

	qlcnic_83xx_unlock_driver(adapter);

	वापस 0;
पूर्ण

पूर्णांक qlcnic_83xx_idc_init(काष्ठा qlcnic_adapter *adapter)
अणु
	पूर्णांक ret = -EIO;

	qlcnic_83xx_setup_idc_parameters(adapter);

	अगर (qlcnic_83xx_get_reset_inकाष्ठाion_ढाँचा(adapter))
		वापस ret;

	अगर (!qlcnic_83xx_idc_check_driver_presence_reg(adapter)) अणु
		अगर (qlcnic_83xx_idc_first_to_load_function_handler(adapter))
			वापस -EIO;
	पूर्ण अन्यथा अणु
		अगर (qlcnic_83xx_idc_check_major_version(adapter))
			वापस -EIO;
	पूर्ण

	qlcnic_83xx_idc_update_audit_reg(adapter, 0, 1);

	वापस 0;
पूर्ण

व्योम qlcnic_83xx_idc_निकास(काष्ठा qlcnic_adapter *adapter)
अणु
	पूर्णांक id;
	u32 val;

	जबतक (test_and_set_bit(__QLCNIC_RESETTING, &adapter->state))
		usleep_range(10000, 11000);

	id = QLCRDX(adapter->ahw, QLC_83XX_DRV_LOCK_ID);
	id = id & 0xFF;

	अगर (id == adapter->portnum) अणु
		dev_err(&adapter->pdev->dev,
			"%s: wait for lock recovery.. %d\n", __func__, id);
		msleep(20);
		id = QLCRDX(adapter->ahw, QLC_83XX_DRV_LOCK_ID);
		id = id & 0xFF;
	पूर्ण

	/* Clear driver presence bit */
	val = QLCRDX(adapter->ahw, QLC_83XX_IDC_DRV_PRESENCE);
	val = val & ~(1 << adapter->portnum);
	QLCWRX(adapter->ahw, QLC_83XX_IDC_DRV_PRESENCE, val);
	clear_bit(QLC_83XX_MODULE_LOADED, &adapter->ahw->idc.status);
	clear_bit(__QLCNIC_RESETTING, &adapter->state);

	cancel_delayed_work_sync(&adapter->fw_work);
पूर्ण

व्योम qlcnic_83xx_idc_request_reset(काष्ठा qlcnic_adapter *adapter, u32 key)
अणु
	u32 val;

	अगर (qlcnic_sriov_vf_check(adapter))
		वापस;

	अगर (qlcnic_83xx_lock_driver(adapter)) अणु
		dev_err(&adapter->pdev->dev,
			"%s:failed, please retry\n", __func__);
		वापस;
	पूर्ण

	val = QLCRDX(adapter->ahw, QLC_83XX_IDC_CTRL);
	अगर (val & QLC_83XX_IDC_DISABLE_FW_RESET_RECOVERY) अणु
		netdev_info(adapter->netdev, "%s: Auto firmware recovery is disabled\n",
			    __func__);
		qlcnic_83xx_idc_enter_failed_state(adapter, 0);
		qlcnic_83xx_unlock_driver(adapter);
		वापस;
	पूर्ण

	अगर (key == QLCNIC_FORCE_FW_RESET) अणु
		val = QLCRDX(adapter->ahw, QLC_83XX_IDC_CTRL);
		val = val | QLC_83XX_IDC_GRACEFULL_RESET;
		QLCWRX(adapter->ahw, QLC_83XX_IDC_CTRL, val);
	पूर्ण अन्यथा अगर (key == QLCNIC_FORCE_FW_DUMP_KEY) अणु
		adapter->ahw->idc.collect_dump = 1;
	पूर्ण

	qlcnic_83xx_unlock_driver(adapter);
	वापस;
पूर्ण

अटल पूर्णांक qlcnic_83xx_copy_bootloader(काष्ठा qlcnic_adapter *adapter)
अणु
	u8 *p_cache;
	u32 src, size;
	u64 dest;
	पूर्णांक ret = -EIO;

	src = QLC_83XX_BOOTLOADER_FLASH_ADDR;
	dest = QLCRDX(adapter->ahw, QLCNIC_BOOTLOADER_ADDR);
	size = QLCRDX(adapter->ahw, QLCNIC_BOOTLOADER_SIZE);

	/* alignment check */
	अगर (size & 0xF)
		size = (size + 16) & ~0xF;

	p_cache = vzalloc(size);
	अगर (p_cache == शून्य)
		वापस -ENOMEM;

	ret = qlcnic_83xx_lockless_flash_पढ़ो32(adapter, src, p_cache,
						size / माप(u32));
	अगर (ret) अणु
		vमुक्त(p_cache);
		वापस ret;
	पूर्ण
	/* 16 byte ग_लिखो to MS memory */
	ret = qlcnic_ms_mem_ग_लिखो128(adapter, dest, (u32 *)p_cache,
				     size / 16);
	अगर (ret) अणु
		vमुक्त(p_cache);
		वापस ret;
	पूर्ण
	vमुक्त(p_cache);

	वापस ret;
पूर्ण

अटल पूर्णांक qlcnic_83xx_copy_fw_file(काष्ठा qlcnic_adapter *adapter)
अणु
	काष्ठा qlc_83xx_fw_info *fw_info = adapter->ahw->fw_info;
	स्थिर काष्ठा firmware *fw = fw_info->fw;
	u32 dest, *p_cache, *temp;
	पूर्णांक i, ret = -EIO;
	__le32 *temp_le;
	u8 data[16];
	माप_प्रकार size;
	u64 addr;

	temp = vzalloc(fw->size);
	अगर (!temp) अणु
		release_firmware(fw);
		fw_info->fw = शून्य;
		वापस -ENOMEM;
	पूर्ण

	temp_le = (__le32 *)fw->data;

	/* FW image in file is in little endian, swap the data to nullअगरy
	 * the effect of ग_लिखोl() operation on big endian platक्रमm.
	 */
	क्रम (i = 0; i < fw->size / माप(u32); i++)
		temp[i] = __le32_to_cpu(temp_le[i]);

	dest = QLCRDX(adapter->ahw, QLCNIC_FW_IMAGE_ADDR);
	size = (fw->size & ~0xF);
	p_cache = temp;
	addr = (u64)dest;

	ret = qlcnic_ms_mem_ग_लिखो128(adapter, addr,
				     p_cache, size / 16);
	अगर (ret) अणु
		dev_err(&adapter->pdev->dev, "MS memory write failed\n");
		जाओ निकास;
	पूर्ण

	/* alignment check */
	अगर (fw->size & 0xF) अणु
		addr = dest + size;
		क्रम (i = 0; i < (fw->size & 0xF); i++)
			data[i] = ((u8 *)temp)[size + i];
		क्रम (; i < 16; i++)
			data[i] = 0;
		ret = qlcnic_ms_mem_ग_लिखो128(adapter, addr,
					     (u32 *)data, 1);
		अगर (ret) अणु
			dev_err(&adapter->pdev->dev,
				"MS memory write failed\n");
			जाओ निकास;
		पूर्ण
	पूर्ण

निकास:
	release_firmware(fw);
	fw_info->fw = शून्य;
	vमुक्त(temp);

	वापस ret;
पूर्ण

अटल व्योम qlcnic_83xx_dump_छोड़ो_control_regs(काष्ठा qlcnic_adapter *adapter)
अणु
	पूर्णांक i, j;
	u32 val = 0, val1 = 0, reg = 0;
	पूर्णांक err = 0;

	val = QLCRD32(adapter, QLC_83XX_SRE_SHIM_REG, &err);
	अगर (err == -EIO)
		वापस;
	dev_info(&adapter->pdev->dev, "SRE-Shim Ctrl:0x%x\n", val);

	क्रम (j = 0; j < 2; j++) अणु
		अगर (j == 0) अणु
			dev_info(&adapter->pdev->dev,
				 "Port 0 RxB Pause Threshold Regs[TC7..TC0]:");
			reg = QLC_83XX_PORT0_THRESHOLD;
		पूर्ण अन्यथा अगर (j == 1) अणु
			dev_info(&adapter->pdev->dev,
				 "Port 1 RxB Pause Threshold Regs[TC7..TC0]:");
			reg = QLC_83XX_PORT1_THRESHOLD;
		पूर्ण
		क्रम (i = 0; i < 8; i++) अणु
			val = QLCRD32(adapter, reg + (i * 0x4), &err);
			अगर (err == -EIO)
				वापस;
			dev_info(&adapter->pdev->dev, "0x%x  ", val);
		पूर्ण
		dev_info(&adapter->pdev->dev, "\n");
	पूर्ण

	क्रम (j = 0; j < 2; j++) अणु
		अगर (j == 0) अणु
			dev_info(&adapter->pdev->dev,
				 "Port 0 RxB TC Max Cell Registers[4..1]:");
			reg = QLC_83XX_PORT0_TC_MC_REG;
		पूर्ण अन्यथा अगर (j == 1) अणु
			dev_info(&adapter->pdev->dev,
				 "Port 1 RxB TC Max Cell Registers[4..1]:");
			reg = QLC_83XX_PORT1_TC_MC_REG;
		पूर्ण
		क्रम (i = 0; i < 4; i++) अणु
			val = QLCRD32(adapter, reg + (i * 0x4), &err);
			अगर (err == -EIO)
				वापस;
			dev_info(&adapter->pdev->dev, "0x%x  ", val);
		पूर्ण
		dev_info(&adapter->pdev->dev, "\n");
	पूर्ण

	क्रम (j = 0; j < 2; j++) अणु
		अगर (j == 0) अणु
			dev_info(&adapter->pdev->dev,
				 "Port 0 RxB Rx TC Stats[TC7..TC0]:");
			reg = QLC_83XX_PORT0_TC_STATS;
		पूर्ण अन्यथा अगर (j == 1) अणु
			dev_info(&adapter->pdev->dev,
				 "Port 1 RxB Rx TC Stats[TC7..TC0]:");
			reg = QLC_83XX_PORT1_TC_STATS;
		पूर्ण
		क्रम (i = 7; i >= 0; i--) अणु
			val = QLCRD32(adapter, reg, &err);
			अगर (err == -EIO)
				वापस;
			val &= ~(0x7 << 29);    /* Reset bits 29 to 31 */
			QLCWR32(adapter, reg, (val | (i << 29)));
			val = QLCRD32(adapter, reg, &err);
			अगर (err == -EIO)
				वापस;
			dev_info(&adapter->pdev->dev, "0x%x  ", val);
		पूर्ण
		dev_info(&adapter->pdev->dev, "\n");
	पूर्ण

	val = QLCRD32(adapter, QLC_83XX_PORT2_IFB_THRESHOLD, &err);
	अगर (err == -EIO)
		वापस;
	val1 = QLCRD32(adapter, QLC_83XX_PORT3_IFB_THRESHOLD, &err);
	अगर (err == -EIO)
		वापस;
	dev_info(&adapter->pdev->dev,
		 "IFB-Pause Thresholds: Port 2:0x%x, Port 3:0x%x\n",
		 val, val1);
पूर्ण


अटल व्योम qlcnic_83xx_disable_छोड़ो_frames(काष्ठा qlcnic_adapter *adapter)
अणु
	u32 reg = 0, i, j;

	अगर (qlcnic_83xx_lock_driver(adapter)) अणु
		dev_err(&adapter->pdev->dev,
			"%s:failed to acquire driver lock\n", __func__);
		वापस;
	पूर्ण

	qlcnic_83xx_dump_छोड़ो_control_regs(adapter);
	QLCWR32(adapter, QLC_83XX_SRE_SHIM_REG, 0x0);

	क्रम (j = 0; j < 2; j++) अणु
		अगर (j == 0)
			reg = QLC_83XX_PORT0_THRESHOLD;
		अन्यथा अगर (j == 1)
			reg = QLC_83XX_PORT1_THRESHOLD;

		क्रम (i = 0; i < 8; i++)
			QLCWR32(adapter, reg + (i * 0x4), 0x0);
	पूर्ण

	क्रम (j = 0; j < 2; j++) अणु
		अगर (j == 0)
			reg = QLC_83XX_PORT0_TC_MC_REG;
		अन्यथा अगर (j == 1)
			reg = QLC_83XX_PORT1_TC_MC_REG;

		क्रम (i = 0; i < 4; i++)
			QLCWR32(adapter, reg + (i * 0x4), 0x03FF03FF);
	पूर्ण

	QLCWR32(adapter, QLC_83XX_PORT2_IFB_THRESHOLD, 0);
	QLCWR32(adapter, QLC_83XX_PORT3_IFB_THRESHOLD, 0);
	dev_info(&adapter->pdev->dev,
		 "Disabled pause frames successfully on all ports\n");
	qlcnic_83xx_unlock_driver(adapter);
पूर्ण

अटल व्योम qlcnic_83xx_take_eport_out_of_reset(काष्ठा qlcnic_adapter *adapter)
अणु
	QLCWR32(adapter, QLC_83XX_RESET_REG, 0);
	QLCWR32(adapter, QLC_83XX_RESET_PORT0, 0);
	QLCWR32(adapter, QLC_83XX_RESET_PORT1, 0);
	QLCWR32(adapter, QLC_83XX_RESET_PORT2, 0);
	QLCWR32(adapter, QLC_83XX_RESET_PORT3, 0);
	QLCWR32(adapter, QLC_83XX_RESET_SRESHIM, 0);
	QLCWR32(adapter, QLC_83XX_RESET_EPGSHIM, 0);
	QLCWR32(adapter, QLC_83XX_RESET_ETHERPCS, 0);
	QLCWR32(adapter, QLC_83XX_RESET_CONTROL, 1);
पूर्ण

अटल पूर्णांक qlcnic_83xx_check_heartbeat(काष्ठा qlcnic_adapter *p_dev)
अणु
	u32 heartbeat, peg_status;
	पूर्णांक retries, ret = -EIO, err = 0;

	retries = QLCNIC_HEARTBEAT_CHECK_RETRY_COUNT;
	p_dev->heartbeat = QLC_SHARED_REG_RD32(p_dev,
					       QLCNIC_PEG_ALIVE_COUNTER);

	करो अणु
		msleep(QLCNIC_HEARTBEAT_PERIOD_MSECS);
		heartbeat = QLC_SHARED_REG_RD32(p_dev,
						QLCNIC_PEG_ALIVE_COUNTER);
		अगर (heartbeat != p_dev->heartbeat) अणु
			ret = QLCNIC_RCODE_SUCCESS;
			अवरोध;
		पूर्ण
	पूर्ण जबतक (--retries);

	अगर (ret) अणु
		dev_err(&p_dev->pdev->dev, "firmware hang detected\n");
		qlcnic_83xx_take_eport_out_of_reset(p_dev);
		qlcnic_83xx_disable_छोड़ो_frames(p_dev);
		peg_status = QLC_SHARED_REG_RD32(p_dev,
						 QLCNIC_PEG_HALT_STATUS1);
		dev_info(&p_dev->pdev->dev, "Dumping HW/FW registers\n"
			 "PEG_HALT_STATUS1: 0x%x, PEG_HALT_STATUS2: 0x%x,\n"
			 "PEG_NET_0_PC: 0x%x, PEG_NET_1_PC: 0x%x,\n"
			 "PEG_NET_2_PC: 0x%x, PEG_NET_3_PC: 0x%x,\n"
			 "PEG_NET_4_PC: 0x%x\n", peg_status,
			 QLC_SHARED_REG_RD32(p_dev, QLCNIC_PEG_HALT_STATUS2),
			 QLCRD32(p_dev, QLC_83XX_CRB_PEG_NET_0, &err),
			 QLCRD32(p_dev, QLC_83XX_CRB_PEG_NET_1, &err),
			 QLCRD32(p_dev, QLC_83XX_CRB_PEG_NET_2, &err),
			 QLCRD32(p_dev, QLC_83XX_CRB_PEG_NET_3, &err),
			 QLCRD32(p_dev, QLC_83XX_CRB_PEG_NET_4, &err));

		अगर (QLCNIC_FWERROR_CODE(peg_status) == 0x67)
			dev_err(&p_dev->pdev->dev,
				"Device is being reset err code 0x00006700.\n");
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक qlcnic_83xx_check_cmd_peg_status(काष्ठा qlcnic_adapter *p_dev)
अणु
	पूर्णांक retries = QLCNIC_CMDPEG_CHECK_RETRY_COUNT;
	u32 val;

	करो अणु
		val = QLC_SHARED_REG_RD32(p_dev, QLCNIC_CMDPEG_STATE);
		अगर (val == QLC_83XX_CMDPEG_COMPLETE)
			वापस 0;
		msleep(QLCNIC_CMDPEG_CHECK_DELAY);
	पूर्ण जबतक (--retries);

	dev_err(&p_dev->pdev->dev, "%s: failed, state = 0x%x\n", __func__, val);
	वापस -EIO;
पूर्ण

अटल पूर्णांक qlcnic_83xx_check_hw_status(काष्ठा qlcnic_adapter *p_dev)
अणु
	पूर्णांक err;

	err = qlcnic_83xx_check_cmd_peg_status(p_dev);
	अगर (err)
		वापस err;

	err = qlcnic_83xx_check_heartbeat(p_dev);
	अगर (err)
		वापस err;

	वापस err;
पूर्ण

अटल पूर्णांक qlcnic_83xx_poll_reg(काष्ठा qlcnic_adapter *p_dev, u32 addr,
				पूर्णांक duration, u32 mask, u32 status)
अणु
	पूर्णांक समयout_error, err = 0;
	u32 value;
	u8 retries;

	value = QLCRD32(p_dev, addr, &err);
	अगर (err == -EIO)
		वापस err;
	retries = duration / 10;

	करो अणु
		अगर ((value & mask) != status) अणु
			समयout_error = 1;
			msleep(duration / 10);
			value = QLCRD32(p_dev, addr, &err);
			अगर (err == -EIO)
				वापस err;
		पूर्ण अन्यथा अणु
			समयout_error = 0;
			अवरोध;
		पूर्ण
	पूर्ण जबतक (retries--);

	अगर (समयout_error) अणु
		p_dev->ahw->reset.seq_error++;
		dev_err(&p_dev->pdev->dev,
			"%s: Timeout Err, entry_num = %d\n",
			__func__, p_dev->ahw->reset.seq_index);
		dev_err(&p_dev->pdev->dev,
			"0x%08x 0x%08x 0x%08x\n",
			value, mask, status);
	पूर्ण

	वापस समयout_error;
पूर्ण

अटल पूर्णांक qlcnic_83xx_reset_ढाँचा_checksum(काष्ठा qlcnic_adapter *p_dev)
अणु
	u32 sum = 0;
	u16 *buff = (u16 *)p_dev->ahw->reset.buff;
	पूर्णांक count = p_dev->ahw->reset.hdr->size / माप(u16);

	जबतक (count-- > 0)
		sum += *buff++;

	जबतक (sum >> 16)
		sum = (sum & 0xFFFF) + (sum >> 16);

	अगर (~sum) अणु
		वापस 0;
	पूर्ण अन्यथा अणु
		dev_err(&p_dev->pdev->dev, "%s: failed\n", __func__);
		वापस -1;
	पूर्ण
पूर्ण

अटल पूर्णांक qlcnic_83xx_get_reset_inकाष्ठाion_ढाँचा(काष्ठा qlcnic_adapter *p_dev)
अणु
	काष्ठा qlcnic_hardware_context *ahw = p_dev->ahw;
	u32 addr, count, prev_ver, curr_ver;
	u8 *p_buff;

	अगर (ahw->reset.buff != शून्य) अणु
		prev_ver = p_dev->fw_version;
		curr_ver = qlcnic_83xx_get_fw_version(p_dev);
		अगर (curr_ver > prev_ver)
			kमुक्त(ahw->reset.buff);
		अन्यथा
			वापस 0;
	पूर्ण

	ahw->reset.seq_error = 0;
	ahw->reset.buff = kzalloc(QLC_83XX_RESTART_TEMPLATE_SIZE, GFP_KERNEL);
	अगर (ahw->reset.buff == शून्य)
		वापस -ENOMEM;

	p_buff = p_dev->ahw->reset.buff;
	addr = QLC_83XX_RESET_TEMPLATE_ADDR;
	count = माप(काष्ठा qlc_83xx_reset_hdr) / माप(u32);

	/* Copy ढाँचा header from flash */
	अगर (qlcnic_83xx_flash_पढ़ो32(p_dev, addr, p_buff, count)) अणु
		dev_err(&p_dev->pdev->dev, "%s: flash read failed\n", __func__);
		वापस -EIO;
	पूर्ण
	ahw->reset.hdr = (काष्ठा qlc_83xx_reset_hdr *)ahw->reset.buff;
	addr = QLC_83XX_RESET_TEMPLATE_ADDR + ahw->reset.hdr->hdr_size;
	p_buff = ahw->reset.buff + ahw->reset.hdr->hdr_size;
	count = (ahw->reset.hdr->size - ahw->reset.hdr->hdr_size) / माप(u32);

	/* Copy rest of the ढाँचा */
	अगर (qlcnic_83xx_flash_पढ़ो32(p_dev, addr, p_buff, count)) अणु
		dev_err(&p_dev->pdev->dev, "%s: flash read failed\n", __func__);
		वापस -EIO;
	पूर्ण

	अगर (qlcnic_83xx_reset_ढाँचा_checksum(p_dev))
		वापस -EIO;
	/* Get Stop, Start and Init command offsets */
	ahw->reset.init_offset = ahw->reset.buff + ahw->reset.hdr->init_offset;
	ahw->reset.start_offset = ahw->reset.buff +
				  ahw->reset.hdr->start_offset;
	ahw->reset.stop_offset = ahw->reset.buff + ahw->reset.hdr->hdr_size;
	वापस 0;
पूर्ण

/* Read Write HW रेजिस्टर command */
अटल व्योम qlcnic_83xx_पढ़ो_ग_लिखो_crb_reg(काष्ठा qlcnic_adapter *p_dev,
					   u32 raddr, u32 waddr)
अणु
	पूर्णांक err = 0;
	u32 value;

	value = QLCRD32(p_dev, raddr, &err);
	अगर (err == -EIO)
		वापस;
	qlcnic_83xx_wrt_reg_indirect(p_dev, waddr, value);
पूर्ण

/* Read Modअगरy Write HW रेजिस्टर command */
अटल व्योम qlcnic_83xx_rmw_crb_reg(काष्ठा qlcnic_adapter *p_dev,
				    u32 raddr, u32 waddr,
				    काष्ठा qlc_83xx_rmw *p_rmw_hdr)
अणु
	पूर्णांक err = 0;
	u32 value;

	अगर (p_rmw_hdr->index_a) अणु
		value = p_dev->ahw->reset.array[p_rmw_hdr->index_a];
	पूर्ण अन्यथा अणु
		value = QLCRD32(p_dev, raddr, &err);
		अगर (err == -EIO)
			वापस;
	पूर्ण

	value &= p_rmw_hdr->mask;
	value <<= p_rmw_hdr->shl;
	value >>= p_rmw_hdr->shr;
	value |= p_rmw_hdr->or_value;
	value ^= p_rmw_hdr->xor_value;
	qlcnic_83xx_wrt_reg_indirect(p_dev, waddr, value);
पूर्ण

/* Write HW रेजिस्टर command */
अटल व्योम qlcnic_83xx_ग_लिखो_list(काष्ठा qlcnic_adapter *p_dev,
				   काष्ठा qlc_83xx_entry_hdr *p_hdr)
अणु
	पूर्णांक i;
	काष्ठा qlc_83xx_entry *entry;

	entry = (काष्ठा qlc_83xx_entry *)((अक्षर *)p_hdr +
					  माप(काष्ठा qlc_83xx_entry_hdr));

	क्रम (i = 0; i < p_hdr->count; i++, entry++) अणु
		qlcnic_83xx_wrt_reg_indirect(p_dev, entry->arg1,
					     entry->arg2);
		अगर (p_hdr->delay)
			udelay((u32)(p_hdr->delay));
	पूर्ण
पूर्ण

/* Read and Write inकाष्ठाion */
अटल व्योम qlcnic_83xx_पढ़ो_ग_लिखो_list(काष्ठा qlcnic_adapter *p_dev,
					काष्ठा qlc_83xx_entry_hdr *p_hdr)
अणु
	पूर्णांक i;
	काष्ठा qlc_83xx_entry *entry;

	entry = (काष्ठा qlc_83xx_entry *)((अक्षर *)p_hdr +
					  माप(काष्ठा qlc_83xx_entry_hdr));

	क्रम (i = 0; i < p_hdr->count; i++, entry++) अणु
		qlcnic_83xx_पढ़ो_ग_लिखो_crb_reg(p_dev, entry->arg1,
					       entry->arg2);
		अगर (p_hdr->delay)
			udelay((u32)(p_hdr->delay));
	पूर्ण
पूर्ण

/* Poll HW रेजिस्टर command */
अटल व्योम qlcnic_83xx_poll_list(काष्ठा qlcnic_adapter *p_dev,
				  काष्ठा qlc_83xx_entry_hdr *p_hdr)
अणु
	दीर्घ delay;
	काष्ठा qlc_83xx_entry *entry;
	काष्ठा qlc_83xx_poll *poll;
	पूर्णांक i, err = 0;
	अचिन्हित दीर्घ arg1, arg2;

	poll = (काष्ठा qlc_83xx_poll *)((अक्षर *)p_hdr +
					माप(काष्ठा qlc_83xx_entry_hdr));

	entry = (काष्ठा qlc_83xx_entry *)((अक्षर *)poll +
					  माप(काष्ठा qlc_83xx_poll));
	delay = (दीर्घ)p_hdr->delay;

	अगर (!delay) अणु
		क्रम (i = 0; i < p_hdr->count; i++, entry++)
			qlcnic_83xx_poll_reg(p_dev, entry->arg1,
					     delay, poll->mask,
					     poll->status);
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < p_hdr->count; i++, entry++) अणु
			arg1 = entry->arg1;
			arg2 = entry->arg2;
			अगर (delay) अणु
				अगर (qlcnic_83xx_poll_reg(p_dev,
							 arg1, delay,
							 poll->mask,
							 poll->status))अणु
					QLCRD32(p_dev, arg1, &err);
					अगर (err == -EIO)
						वापस;
					QLCRD32(p_dev, arg2, &err);
					अगर (err == -EIO)
						वापस;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

/* Poll and ग_लिखो HW रेजिस्टर command */
अटल व्योम qlcnic_83xx_poll_ग_लिखो_list(काष्ठा qlcnic_adapter *p_dev,
					काष्ठा qlc_83xx_entry_hdr *p_hdr)
अणु
	पूर्णांक i;
	दीर्घ delay;
	काष्ठा qlc_83xx_quad_entry *entry;
	काष्ठा qlc_83xx_poll *poll;

	poll = (काष्ठा qlc_83xx_poll *)((अक्षर *)p_hdr +
					माप(काष्ठा qlc_83xx_entry_hdr));
	entry = (काष्ठा qlc_83xx_quad_entry *)((अक्षर *)poll +
					       माप(काष्ठा qlc_83xx_poll));
	delay = (दीर्घ)p_hdr->delay;

	क्रम (i = 0; i < p_hdr->count; i++, entry++) अणु
		qlcnic_83xx_wrt_reg_indirect(p_dev, entry->dr_addr,
					     entry->dr_value);
		qlcnic_83xx_wrt_reg_indirect(p_dev, entry->ar_addr,
					     entry->ar_value);
		अगर (delay)
			qlcnic_83xx_poll_reg(p_dev, entry->ar_addr, delay,
					     poll->mask, poll->status);
	पूर्ण
पूर्ण

/* Read Modअगरy Write रेजिस्टर command */
अटल व्योम qlcnic_83xx_पढ़ो_modअगरy_ग_लिखो(काष्ठा qlcnic_adapter *p_dev,
					  काष्ठा qlc_83xx_entry_hdr *p_hdr)
अणु
	पूर्णांक i;
	काष्ठा qlc_83xx_entry *entry;
	काष्ठा qlc_83xx_rmw *rmw_hdr;

	rmw_hdr = (काष्ठा qlc_83xx_rmw *)((अक्षर *)p_hdr +
					  माप(काष्ठा qlc_83xx_entry_hdr));

	entry = (काष्ठा qlc_83xx_entry *)((अक्षर *)rmw_hdr +
					  माप(काष्ठा qlc_83xx_rmw));

	क्रम (i = 0; i < p_hdr->count; i++, entry++) अणु
		qlcnic_83xx_rmw_crb_reg(p_dev, entry->arg1,
					entry->arg2, rmw_hdr);
		अगर (p_hdr->delay)
			udelay((u32)(p_hdr->delay));
	पूर्ण
पूर्ण

अटल व्योम qlcnic_83xx_छोड़ो(काष्ठा qlc_83xx_entry_hdr *p_hdr)
अणु
	अगर (p_hdr->delay)
		mdelay((u32)((दीर्घ)p_hdr->delay));
पूर्ण

/* Read and poll रेजिस्टर command */
अटल व्योम qlcnic_83xx_poll_पढ़ो_list(काष्ठा qlcnic_adapter *p_dev,
				       काष्ठा qlc_83xx_entry_hdr *p_hdr)
अणु
	दीर्घ delay;
	पूर्णांक index, i, j, err;
	काष्ठा qlc_83xx_quad_entry *entry;
	काष्ठा qlc_83xx_poll *poll;
	अचिन्हित दीर्घ addr;

	poll = (काष्ठा qlc_83xx_poll *)((अक्षर *)p_hdr +
					माप(काष्ठा qlc_83xx_entry_hdr));

	entry = (काष्ठा qlc_83xx_quad_entry *)((अक्षर *)poll +
					       माप(काष्ठा qlc_83xx_poll));
	delay = (दीर्घ)p_hdr->delay;

	क्रम (i = 0; i < p_hdr->count; i++, entry++) अणु
		qlcnic_83xx_wrt_reg_indirect(p_dev, entry->ar_addr,
					     entry->ar_value);
		अगर (delay) अणु
			अगर (!qlcnic_83xx_poll_reg(p_dev, entry->ar_addr, delay,
						  poll->mask, poll->status))अणु
				index = p_dev->ahw->reset.array_index;
				addr = entry->dr_addr;
				j = QLCRD32(p_dev, addr, &err);
				अगर (err == -EIO)
					वापस;

				p_dev->ahw->reset.array[index++] = j;

				अगर (index == QLC_83XX_MAX_RESET_SEQ_ENTRIES)
					p_dev->ahw->reset.array_index = 1;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम qlcnic_83xx_seq_end(काष्ठा qlcnic_adapter *p_dev)
अणु
	p_dev->ahw->reset.seq_end = 1;
पूर्ण

अटल व्योम qlcnic_83xx_ढाँचा_end(काष्ठा qlcnic_adapter *p_dev)
अणु
	p_dev->ahw->reset.ढाँचा_end = 1;
	अगर (p_dev->ahw->reset.seq_error == 0)
		dev_err(&p_dev->pdev->dev,
			"HW restart process completed successfully.\n");
	अन्यथा
		dev_err(&p_dev->pdev->dev,
			"HW restart completed with timeout errors.\n");
पूर्ण

/**
* qlcnic_83xx_exec_ढाँचा_cmd
*
* @p_dev: adapter काष्ठाure
* @p_buff: Poiter to inकाष्ठाion ढाँचा
*
* Template provides inकाष्ठाions to stop, restart and initalize firmware.
* These inकाष्ठाions are असलtracted as a series of पढ़ो, ग_लिखो and
* poll operations on hardware रेजिस्टरs. Register inक्रमmation and operation
* specअगरics are not exposed to the driver. Driver पढ़ोs the ढाँचा from
* flash and executes the inकाष्ठाions located at pre-defined offsets.
*
* Returns: None
* */
अटल व्योम qlcnic_83xx_exec_ढाँचा_cmd(काष्ठा qlcnic_adapter *p_dev,
					  अक्षर *p_buff)
अणु
	पूर्णांक index, entries;
	काष्ठा qlc_83xx_entry_hdr *p_hdr;
	अक्षर *entry = p_buff;

	p_dev->ahw->reset.seq_end = 0;
	p_dev->ahw->reset.ढाँचा_end = 0;
	entries = p_dev->ahw->reset.hdr->entries;
	index = p_dev->ahw->reset.seq_index;

	क्रम (; (!p_dev->ahw->reset.seq_end) && (index < entries); index++) अणु
		p_hdr = (काष्ठा qlc_83xx_entry_hdr *)entry;

		चयन (p_hdr->cmd) अणु
		हाल QLC_83XX_OPCODE_NOP:
			अवरोध;
		हाल QLC_83XX_OPCODE_WRITE_LIST:
			qlcnic_83xx_ग_लिखो_list(p_dev, p_hdr);
			अवरोध;
		हाल QLC_83XX_OPCODE_READ_WRITE_LIST:
			qlcnic_83xx_पढ़ो_ग_लिखो_list(p_dev, p_hdr);
			अवरोध;
		हाल QLC_83XX_OPCODE_POLL_LIST:
			qlcnic_83xx_poll_list(p_dev, p_hdr);
			अवरोध;
		हाल QLC_83XX_OPCODE_POLL_WRITE_LIST:
			qlcnic_83xx_poll_ग_लिखो_list(p_dev, p_hdr);
			अवरोध;
		हाल QLC_83XX_OPCODE_READ_MODIFY_WRITE:
			qlcnic_83xx_पढ़ो_modअगरy_ग_लिखो(p_dev, p_hdr);
			अवरोध;
		हाल QLC_83XX_OPCODE_SEQ_PAUSE:
			qlcnic_83xx_छोड़ो(p_hdr);
			अवरोध;
		हाल QLC_83XX_OPCODE_SEQ_END:
			qlcnic_83xx_seq_end(p_dev);
			अवरोध;
		हाल QLC_83XX_OPCODE_TMPL_END:
			qlcnic_83xx_ढाँचा_end(p_dev);
			अवरोध;
		हाल QLC_83XX_OPCODE_POLL_READ_LIST:
			qlcnic_83xx_poll_पढ़ो_list(p_dev, p_hdr);
			अवरोध;
		शेष:
			dev_err(&p_dev->pdev->dev,
				"%s: Unknown opcode 0x%04x in template %d\n",
				__func__, p_hdr->cmd, index);
			अवरोध;
		पूर्ण
		entry += p_hdr->size;
		cond_resched();
	पूर्ण
	p_dev->ahw->reset.seq_index = index;
पूर्ण

अटल व्योम qlcnic_83xx_stop_hw(काष्ठा qlcnic_adapter *p_dev)
अणु
	p_dev->ahw->reset.seq_index = 0;

	qlcnic_83xx_exec_ढाँचा_cmd(p_dev, p_dev->ahw->reset.stop_offset);
	अगर (p_dev->ahw->reset.seq_end != 1)
		dev_err(&p_dev->pdev->dev, "%s: failed\n", __func__);
पूर्ण

अटल व्योम qlcnic_83xx_start_hw(काष्ठा qlcnic_adapter *p_dev)
अणु
	qlcnic_83xx_exec_ढाँचा_cmd(p_dev, p_dev->ahw->reset.start_offset);
	अगर (p_dev->ahw->reset.ढाँचा_end != 1)
		dev_err(&p_dev->pdev->dev, "%s: failed\n", __func__);
पूर्ण

अटल व्योम qlcnic_83xx_init_hw(काष्ठा qlcnic_adapter *p_dev)
अणु
	qlcnic_83xx_exec_ढाँचा_cmd(p_dev, p_dev->ahw->reset.init_offset);
	अगर (p_dev->ahw->reset.seq_end != 1)
		dev_err(&p_dev->pdev->dev, "%s: failed\n", __func__);
पूर्ण

/* POST FW related definations*/
#घोषणा QLC_83XX_POST_SIGNATURE_REG	0x41602014
#घोषणा QLC_83XX_POST_MODE_REG		0x41602018
#घोषणा QLC_83XX_POST_FAST_MODE		0
#घोषणा QLC_83XX_POST_MEDIUM_MODE	1
#घोषणा QLC_83XX_POST_SLOW_MODE		2

/* POST Timeout values in milliseconds */
#घोषणा QLC_83XX_POST_FAST_MODE_TIMEOUT	690
#घोषणा QLC_83XX_POST_MED_MODE_TIMEOUT	2930
#घोषणा QLC_83XX_POST_SLOW_MODE_TIMEOUT	7500

/* POST result values */
#घोषणा QLC_83XX_POST_PASS			0xfffffff0
#घोषणा QLC_83XX_POST_ASIC_STRESS_TEST_FAIL	0xffffffff
#घोषणा QLC_83XX_POST_DDR_TEST_FAIL		0xfffffffe
#घोषणा QLC_83XX_POST_ASIC_MEMORY_TEST_FAIL	0xfffffffc
#घोषणा QLC_83XX_POST_FLASH_TEST_FAIL		0xfffffff8

अटल पूर्णांक qlcnic_83xx_run_post(काष्ठा qlcnic_adapter *adapter)
अणु
	काष्ठा qlc_83xx_fw_info *fw_info = adapter->ahw->fw_info;
	काष्ठा device *dev = &adapter->pdev->dev;
	पूर्णांक समयout, count, ret = 0;
	u32 signature;

	/* Set समयout values with extra 2 seconds of buffer */
	चयन (adapter->ahw->post_mode) अणु
	हाल QLC_83XX_POST_FAST_MODE:
		समयout = QLC_83XX_POST_FAST_MODE_TIMEOUT + 2000;
		अवरोध;
	हाल QLC_83XX_POST_MEDIUM_MODE:
		समयout = QLC_83XX_POST_MED_MODE_TIMEOUT + 2000;
		अवरोध;
	हाल QLC_83XX_POST_SLOW_MODE:
		समयout = QLC_83XX_POST_SLOW_MODE_TIMEOUT + 2000;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	म_नकलन(fw_info->fw_file_name, QLC_83XX_POST_FW_खाता_NAME,
		QLC_FW_खाता_NAME_LEN);

	ret = request_firmware(&fw_info->fw, fw_info->fw_file_name, dev);
	अगर (ret) अणु
		dev_err(dev, "POST firmware can not be loaded, skipping POST\n");
		वापस 0;
	पूर्ण

	ret = qlcnic_83xx_copy_fw_file(adapter);
	अगर (ret)
		वापस ret;

	/* clear QLC_83XX_POST_SIGNATURE_REG रेजिस्टर */
	qlcnic_ind_wr(adapter, QLC_83XX_POST_SIGNATURE_REG, 0);

	/* Set POST mode */
	qlcnic_ind_wr(adapter, QLC_83XX_POST_MODE_REG,
		      adapter->ahw->post_mode);

	QLC_SHARED_REG_WR32(adapter, QLCNIC_FW_IMG_VALID,
			    QLC_83XX_BOOT_FROM_खाता);

	qlcnic_83xx_start_hw(adapter);

	count = 0;
	करो अणु
		msleep(100);
		count += 100;

		signature = qlcnic_ind_rd(adapter, QLC_83XX_POST_SIGNATURE_REG);
		अगर (signature == QLC_83XX_POST_PASS)
			अवरोध;
	पूर्ण जबतक (समयout > count);

	अगर (समयout <= count) अणु
		dev_err(dev, "POST timed out, signature = 0x%08x\n", signature);
		वापस -EIO;
	पूर्ण

	चयन (signature) अणु
	हाल QLC_83XX_POST_PASS:
		dev_info(dev, "POST passed, Signature = 0x%08x\n", signature);
		अवरोध;
	हाल QLC_83XX_POST_ASIC_STRESS_TEST_FAIL:
		dev_err(dev, "POST failed, Test case : ASIC STRESS TEST, Signature = 0x%08x\n",
			signature);
		ret = -EIO;
		अवरोध;
	हाल QLC_83XX_POST_DDR_TEST_FAIL:
		dev_err(dev, "POST failed, Test case : DDT TEST, Signature = 0x%08x\n",
			signature);
		ret = -EIO;
		अवरोध;
	हाल QLC_83XX_POST_ASIC_MEMORY_TEST_FAIL:
		dev_err(dev, "POST failed, Test case : ASIC MEMORY TEST, Signature = 0x%08x\n",
			signature);
		ret = -EIO;
		अवरोध;
	हाल QLC_83XX_POST_FLASH_TEST_FAIL:
		dev_err(dev, "POST failed, Test case : FLASH TEST, Signature = 0x%08x\n",
			signature);
		ret = -EIO;
		अवरोध;
	शेष:
		dev_err(dev, "POST failed, Test case : INVALID, Signature = 0x%08x\n",
			signature);
		ret = -EIO;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक qlcnic_83xx_load_fw_image_from_host(काष्ठा qlcnic_adapter *adapter)
अणु
	काष्ठा qlc_83xx_fw_info *fw_info = adapter->ahw->fw_info;
	पूर्णांक err = -EIO;

	अगर (request_firmware(&fw_info->fw, fw_info->fw_file_name,
			     &(adapter->pdev->dev))) अणु
		dev_err(&adapter->pdev->dev,
			"No file FW image, loading flash FW image.\n");
		QLC_SHARED_REG_WR32(adapter, QLCNIC_FW_IMG_VALID,
				    QLC_83XX_BOOT_FROM_FLASH);
	पूर्ण अन्यथा अणु
		अगर (qlcnic_83xx_copy_fw_file(adapter))
			वापस err;
		QLC_SHARED_REG_WR32(adapter, QLCNIC_FW_IMG_VALID,
				    QLC_83XX_BOOT_FROM_खाता);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक qlcnic_83xx_restart_hw(काष्ठा qlcnic_adapter *adapter)
अणु
	u32 val;
	पूर्णांक err = -EIO;

	qlcnic_83xx_stop_hw(adapter);

	/* Collect FW रेजिस्टर dump अगर required */
	val = QLCRDX(adapter->ahw, QLC_83XX_IDC_CTRL);
	अगर (!(val & QLC_83XX_IDC_GRACEFULL_RESET))
		qlcnic_dump_fw(adapter);

	अगर (val & QLC_83XX_IDC_DISABLE_FW_RESET_RECOVERY) अणु
		netdev_info(adapter->netdev, "%s: Auto firmware recovery is disabled\n",
			    __func__);
		qlcnic_83xx_idc_enter_failed_state(adapter, 1);
		वापस err;
	पूर्ण

	qlcnic_83xx_init_hw(adapter);

	अगर (qlcnic_83xx_copy_bootloader(adapter))
		वापस err;

	/* Check अगर POST needs to be run */
	अगर (adapter->ahw->run_post) अणु
		err = qlcnic_83xx_run_post(adapter);
		अगर (err)
			वापस err;

		/* No need to run POST in next reset sequence */
		adapter->ahw->run_post = false;

		/* Again reset the adapter to load regular firmware  */
		qlcnic_83xx_stop_hw(adapter);
		qlcnic_83xx_init_hw(adapter);

		err = qlcnic_83xx_copy_bootloader(adapter);
		अगर (err)
			वापस err;
	पूर्ण

	/* Boot either flash image or firmware image from host file प्रणाली */
	अगर (qlcnic_load_fw_file == 1) अणु
		err = qlcnic_83xx_load_fw_image_from_host(adapter);
		अगर (err)
			वापस err;
	पूर्ण अन्यथा अणु
		QLC_SHARED_REG_WR32(adapter, QLCNIC_FW_IMG_VALID,
				    QLC_83XX_BOOT_FROM_FLASH);
	पूर्ण

	qlcnic_83xx_start_hw(adapter);
	अगर (qlcnic_83xx_check_hw_status(adapter))
		वापस -EIO;

	वापस 0;
पूर्ण

अटल पूर्णांक qlcnic_83xx_get_nic_configuration(काष्ठा qlcnic_adapter *adapter)
अणु
	पूर्णांक err;
	काष्ठा qlcnic_info nic_info;
	काष्ठा qlcnic_hardware_context *ahw = adapter->ahw;

	स_रखो(&nic_info, 0, माप(काष्ठा qlcnic_info));
	err = qlcnic_get_nic_info(adapter, &nic_info, ahw->pci_func);
	अगर (err)
		वापस -EIO;

	ahw->physical_port = (u8) nic_info.phys_port;
	ahw->चयन_mode = nic_info.चयन_mode;
	ahw->max_tx_ques = nic_info.max_tx_ques;
	ahw->max_rx_ques = nic_info.max_rx_ques;
	ahw->capabilities = nic_info.capabilities;
	ahw->max_mac_filters = nic_info.max_mac_filters;
	ahw->max_mtu = nic_info.max_mtu;

	/* eSwitch capability indicates vNIC mode.
	 * vNIC and SRIOV are mutually exclusive operational modes.
	 * If SR-IOV capability is detected, SR-IOV physical function
	 * will get initialized in शेष mode.
	 * SR-IOV भव function initialization follows a
	 * dअगरferent code path and opmode.
	 * SRIOV mode has precedence over vNIC mode.
	 */
	अगर (test_bit(__QLCNIC_SRIOV_CAPABLE, &adapter->state))
		वापस QLC_83XX_DEFAULT_OPMODE;

	अगर (ahw->capabilities & QLC_83XX_ESWITCH_CAPABILITY)
		वापस QLCNIC_VNIC_MODE;

	वापस QLC_83XX_DEFAULT_OPMODE;
पूर्ण

पूर्णांक qlcnic_83xx_configure_opmode(काष्ठा qlcnic_adapter *adapter)
अणु
	काष्ठा qlcnic_hardware_context *ahw = adapter->ahw;
	u16 max_sds_rings, max_tx_rings;
	पूर्णांक ret;

	ret = qlcnic_83xx_get_nic_configuration(adapter);
	अगर (ret == -EIO)
		वापस -EIO;

	अगर (ret == QLCNIC_VNIC_MODE) अणु
		ahw->nic_mode = QLCNIC_VNIC_MODE;

		अगर (qlcnic_83xx_config_vnic_opmode(adapter))
			वापस -EIO;

		max_sds_rings = QLCNIC_MAX_VNIC_SDS_RINGS;
		max_tx_rings = QLCNIC_MAX_VNIC_TX_RINGS;
	पूर्ण अन्यथा अगर (ret == QLC_83XX_DEFAULT_OPMODE) अणु
		ahw->nic_mode = QLCNIC_DEFAULT_MODE;
		adapter->nic_ops->init_driver = qlcnic_83xx_init_शेष_driver;
		ahw->idc.state_entry = qlcnic_83xx_idc_पढ़ोy_state_entry;
		max_sds_rings = QLCNIC_MAX_SDS_RINGS;
		max_tx_rings = QLCNIC_MAX_TX_RINGS;
	पूर्ण अन्यथा अणु
		dev_err(&adapter->pdev->dev, "%s: Invalid opmode %d\n",
			__func__, ret);
		वापस -EIO;
	पूर्ण

	adapter->max_sds_rings = min(ahw->max_rx_ques, max_sds_rings);
	adapter->max_tx_rings = min(ahw->max_tx_ques, max_tx_rings);

	वापस 0;
पूर्ण

अटल व्योम qlcnic_83xx_config_buff_descriptors(काष्ठा qlcnic_adapter *adapter)
अणु
	काष्ठा qlcnic_hardware_context *ahw = adapter->ahw;

	अगर (ahw->port_type == QLCNIC_XGBE) अणु
		adapter->num_rxd = DEFAULT_RCV_DESCRIPTORS_10G;
		adapter->max_rxd = MAX_RCV_DESCRIPTORS_10G;
		adapter->num_jumbo_rxd = MAX_JUMBO_RCV_DESCRIPTORS_10G;
		adapter->max_jumbo_rxd = MAX_JUMBO_RCV_DESCRIPTORS_10G;

	पूर्ण अन्यथा अगर (ahw->port_type == QLCNIC_GBE) अणु
		adapter->num_rxd = DEFAULT_RCV_DESCRIPTORS_1G;
		adapter->num_jumbo_rxd = MAX_JUMBO_RCV_DESCRIPTORS_1G;
		adapter->max_jumbo_rxd = MAX_JUMBO_RCV_DESCRIPTORS_1G;
		adapter->max_rxd = MAX_RCV_DESCRIPTORS_1G;
	पूर्ण
	adapter->num_txd = MAX_CMD_DESCRIPTORS;
	adapter->max_rds_rings = MAX_RDS_RINGS;
पूर्ण

अटल पूर्णांक qlcnic_83xx_init_शेष_driver(काष्ठा qlcnic_adapter *adapter)
अणु
	पूर्णांक err = -EIO;

	qlcnic_83xx_get_minidump_ढाँचा(adapter);
	अगर (qlcnic_83xx_get_port_info(adapter))
		वापस err;

	qlcnic_83xx_config_buff_descriptors(adapter);
	adapter->ahw->msix_supported = !!qlcnic_use_msi_x;
	adapter->flags |= QLCNIC_ADAPTER_INITIALIZED;

	dev_info(&adapter->pdev->dev, "HAL Version: %d\n",
		 adapter->ahw->fw_hal_version);

	वापस 0;
पूर्ण

#घोषणा IS_QLC_83XX_USED(a, b, c) (((1 << a->portnum) & b) || ((c >> 6) & 0x1))
अटल व्योम qlcnic_83xx_clear_function_resources(काष्ठा qlcnic_adapter *adapter)
अणु
	काष्ठा qlcnic_cmd_args cmd;
	u32 presence_mask, audit_mask;
	पूर्णांक status;

	presence_mask = QLCRDX(adapter->ahw, QLC_83XX_IDC_DRV_PRESENCE);
	audit_mask = QLCRDX(adapter->ahw, QLC_83XX_IDC_DRV_AUDIT);

	अगर (IS_QLC_83XX_USED(adapter, presence_mask, audit_mask)) अणु
		status = qlcnic_alloc_mbx_args(&cmd, adapter,
					       QLCNIC_CMD_STOP_NIC_FUNC);
		अगर (status)
			वापस;

		cmd.req.arg[1] = BIT_31;
		status = qlcnic_issue_cmd(adapter, &cmd);
		अगर (status)
			dev_err(&adapter->pdev->dev,
				"Failed to clean up the function resources\n");
		qlcnic_मुक्त_mbx_args(&cmd);
	पूर्ण
पूर्ण

अटल पूर्णांक qlcnic_83xx_get_fw_info(काष्ठा qlcnic_adapter *adapter)
अणु
	काष्ठा qlcnic_hardware_context *ahw = adapter->ahw;
	काष्ठा pci_dev *pdev = adapter->pdev;
	काष्ठा qlc_83xx_fw_info *fw_info;
	पूर्णांक err = 0;

	ahw->fw_info = kzalloc(माप(*fw_info), GFP_KERNEL);
	अगर (!ahw->fw_info) अणु
		err = -ENOMEM;
	पूर्ण अन्यथा अणु
		fw_info = ahw->fw_info;
		चयन (pdev->device) अणु
		हाल PCI_DEVICE_ID_QLOGIC_QLE834X:
		हाल PCI_DEVICE_ID_QLOGIC_QLE8830:
			म_नकलन(fw_info->fw_file_name, QLC_83XX_FW_खाता_NAME,
				QLC_FW_खाता_NAME_LEN);
			अवरोध;
		हाल PCI_DEVICE_ID_QLOGIC_QLE844X:
			म_नकलन(fw_info->fw_file_name, QLC_84XX_FW_खाता_NAME,
				QLC_FW_खाता_NAME_LEN);
			अवरोध;
		शेष:
			dev_err(&pdev->dev, "%s: Invalid device id\n",
				__func__);
			err = -EINVAL;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम qlcnic_83xx_init_rings(काष्ठा qlcnic_adapter *adapter)
अणु
	u8 rx_cnt = QLCNIC_DEF_SDS_RINGS;
	u8 tx_cnt = QLCNIC_DEF_TX_RINGS;

	adapter->max_tx_rings = QLCNIC_MAX_TX_RINGS;
	adapter->max_sds_rings = QLCNIC_MAX_SDS_RINGS;

	अगर (!adapter->ahw->msix_supported) अणु
		rx_cnt = QLCNIC_SINGLE_RING;
		tx_cnt = QLCNIC_SINGLE_RING;
	पूर्ण

	/* compute and set drv sds rings */
	qlcnic_set_tx_ring_count(adapter, tx_cnt);
	qlcnic_set_sds_ring_count(adapter, rx_cnt);
पूर्ण

पूर्णांक qlcnic_83xx_init(काष्ठा qlcnic_adapter *adapter, पूर्णांक pci_using_dac)
अणु
	काष्ठा qlcnic_hardware_context *ahw = adapter->ahw;
	पूर्णांक err = 0;

	adapter->rx_mac_learn = false;
	ahw->msix_supported = !!qlcnic_use_msi_x;

	/* Check अगर POST needs to be run */
	चयन (qlcnic_load_fw_file) अणु
	हाल 2:
		ahw->post_mode = QLC_83XX_POST_FAST_MODE;
		ahw->run_post = true;
		अवरोध;
	हाल 3:
		ahw->post_mode = QLC_83XX_POST_MEDIUM_MODE;
		ahw->run_post = true;
		अवरोध;
	हाल 4:
		ahw->post_mode = QLC_83XX_POST_SLOW_MODE;
		ahw->run_post = true;
		अवरोध;
	शेष:
		ahw->run_post = false;
		अवरोध;
	पूर्ण

	qlcnic_83xx_init_rings(adapter);

	err = qlcnic_83xx_init_mailbox_work(adapter);
	अगर (err)
		जाओ निकास;

	अगर (qlcnic_sriov_vf_check(adapter)) अणु
		err = qlcnic_sriov_vf_init(adapter, pci_using_dac);
		अगर (err)
			जाओ detach_mbx;
		अन्यथा
			वापस err;
	पूर्ण

	अगर (qlcnic_83xx_पढ़ो_flash_descriptor_table(adapter) ||
	    qlcnic_83xx_पढ़ो_flash_mfg_id(adapter)) अणु
		dev_err(&adapter->pdev->dev, "Failed reading flash mfg id\n");
		err = -ENOTRECOVERABLE;
		जाओ detach_mbx;
	पूर्ण

	err = qlcnic_83xx_check_hw_status(adapter);
	अगर (err)
		जाओ detach_mbx;

	err = qlcnic_83xx_get_fw_info(adapter);
	अगर (err)
		जाओ detach_mbx;

	err = qlcnic_83xx_idc_init(adapter);
	अगर (err)
		जाओ detach_mbx;

	err = qlcnic_setup_पूर्णांकr(adapter);
	अगर (err) अणु
		dev_err(&adapter->pdev->dev, "Failed to setup interrupt\n");
		जाओ disable_पूर्णांकr;
	पूर्ण

	INIT_DELAYED_WORK(&adapter->idc_aen_work, qlcnic_83xx_idc_aen_work);

	err = qlcnic_83xx_setup_mbx_पूर्णांकr(adapter);
	अगर (err)
		जाओ disable_mbx_पूर्णांकr;

	qlcnic_83xx_clear_function_resources(adapter);
	qlcnic_dcb_enable(adapter->dcb);
	qlcnic_83xx_initialize_nic(adapter, 1);
	qlcnic_dcb_get_info(adapter->dcb);

	/* Configure शेष, SR-IOV or Virtual NIC mode of operation */
	err = qlcnic_83xx_configure_opmode(adapter);
	अगर (err)
		जाओ disable_mbx_पूर्णांकr;


	/* Perक्रमm operating mode specअगरic initialization */
	err = adapter->nic_ops->init_driver(adapter);
	अगर (err)
		जाओ disable_mbx_पूर्णांकr;

	/* Periodically monitor device status */
	qlcnic_83xx_idc_poll_dev_state(&adapter->fw_work.work);
	वापस 0;

disable_mbx_पूर्णांकr:
	qlcnic_83xx_मुक्त_mbx_पूर्णांकr(adapter);

disable_पूर्णांकr:
	qlcnic_tearकरोwn_पूर्णांकr(adapter);

detach_mbx:
	qlcnic_83xx_detach_mailbox_work(adapter);
	qlcnic_83xx_मुक्त_mailbox(ahw->mailbox);
	ahw->mailbox = शून्य;
निकास:
	वापस err;
पूर्ण

व्योम qlcnic_83xx_aer_stop_poll_work(काष्ठा qlcnic_adapter *adapter)
अणु
	काष्ठा qlcnic_hardware_context *ahw = adapter->ahw;
	काष्ठा qlc_83xx_idc *idc = &ahw->idc;

	clear_bit(QLC_83XX_MBX_READY, &idc->status);
	cancel_delayed_work_sync(&adapter->fw_work);

	अगर (ahw->nic_mode == QLCNIC_VNIC_MODE)
		qlcnic_83xx_disable_vnic_mode(adapter, 1);

	qlcnic_83xx_idc_detach_driver(adapter);
	qlcnic_83xx_initialize_nic(adapter, 0);

	cancel_delayed_work_sync(&adapter->idc_aen_work);
पूर्ण

पूर्णांक qlcnic_83xx_aer_reset(काष्ठा qlcnic_adapter *adapter)
अणु
	काष्ठा qlcnic_hardware_context *ahw = adapter->ahw;
	काष्ठा qlc_83xx_idc *idc = &ahw->idc;
	पूर्णांक ret = 0;
	u32 owner;

	/* Mark the previous IDC state as NEED_RESET so
	 * that state_entry() will perक्रमm the reattachment
	 * and bringup the device
	 */
	idc->prev_state = QLC_83XX_IDC_DEV_NEED_RESET;
	owner = qlcnic_83xx_idc_find_reset_owner_id(adapter);
	अगर (ahw->pci_func == owner) अणु
		ret = qlcnic_83xx_restart_hw(adapter);
		अगर (ret < 0)
			वापस ret;
		qlcnic_83xx_idc_clear_रेजिस्टरs(adapter, 0);
	पूर्ण

	ret = idc->state_entry(adapter);
	वापस ret;
पूर्ण

व्योम qlcnic_83xx_aer_start_poll_work(काष्ठा qlcnic_adapter *adapter)
अणु
	काष्ठा qlcnic_hardware_context *ahw = adapter->ahw;
	काष्ठा qlc_83xx_idc *idc = &ahw->idc;
	u32 owner;

	idc->prev_state = QLC_83XX_IDC_DEV_READY;
	owner = qlcnic_83xx_idc_find_reset_owner_id(adapter);
	अगर (ahw->pci_func == owner)
		qlcnic_83xx_idc_enter_पढ़ोy_state(adapter, 0);

	qlcnic_schedule_work(adapter, qlcnic_83xx_idc_poll_dev_state, 0);
पूर्ण
