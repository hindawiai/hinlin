<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * QLogic iSCSI HBA Driver
 * Copyright (c)   2003-2013 QLogic Corporation
 */

#समावेश <linux/ratelimit.h>

#समावेश "ql4_def.h"
#समावेश "ql4_version.h"
#समावेश "ql4_glbl.h"
#समावेश "ql4_dbg.h"
#समावेश "ql4_inline.h"

uपूर्णांक32_t qla4_83xx_rd_reg(काष्ठा scsi_qla_host *ha, uदीर्घ addr)
अणु
	वापस पढ़ोl((व्योम __iomem *)(ha->nx_pcibase + addr));
पूर्ण

व्योम qla4_83xx_wr_reg(काष्ठा scsi_qla_host *ha, uदीर्घ addr, uपूर्णांक32_t val)
अणु
	ग_लिखोl(val, (व्योम __iomem *)(ha->nx_pcibase + addr));
पूर्ण

अटल पूर्णांक qla4_83xx_set_win_base(काष्ठा scsi_qla_host *ha, uपूर्णांक32_t addr)
अणु
	uपूर्णांक32_t val;
	पूर्णांक ret_val = QLA_SUCCESS;

	qla4_83xx_wr_reg(ha, QLA83XX_CRB_WIN_FUNC(ha->func_num), addr);
	val = qla4_83xx_rd_reg(ha, QLA83XX_CRB_WIN_FUNC(ha->func_num));
	अगर (val != addr) अणु
		ql4_prपूर्णांकk(KERN_ERR, ha, "%s: Failed to set register window : addr written 0x%x, read 0x%x!\n",
			   __func__, addr, val);
		ret_val = QLA_ERROR;
	पूर्ण

	वापस ret_val;
पूर्ण

पूर्णांक qla4_83xx_rd_reg_indirect(काष्ठा scsi_qla_host *ha, uपूर्णांक32_t addr,
			      uपूर्णांक32_t *data)
अणु
	पूर्णांक ret_val;

	ret_val = qla4_83xx_set_win_base(ha, addr);

	अगर (ret_val == QLA_SUCCESS) अणु
		*data = qla4_83xx_rd_reg(ha, QLA83XX_WILDCARD);
	पूर्ण अन्यथा अणु
		*data = 0xffffffff;
		ql4_prपूर्णांकk(KERN_ERR, ha, "%s: failed read of addr 0x%x!\n",
			   __func__, addr);
	पूर्ण

	वापस ret_val;
पूर्ण

पूर्णांक qla4_83xx_wr_reg_indirect(काष्ठा scsi_qla_host *ha, uपूर्णांक32_t addr,
			      uपूर्णांक32_t data)
अणु
	पूर्णांक ret_val;

	ret_val = qla4_83xx_set_win_base(ha, addr);

	अगर (ret_val == QLA_SUCCESS)
		qla4_83xx_wr_reg(ha, QLA83XX_WILDCARD, data);
	अन्यथा
		ql4_prपूर्णांकk(KERN_ERR, ha, "%s: failed wrt to addr 0x%x, data 0x%x\n",
			   __func__, addr, data);

	वापस ret_val;
पूर्ण

अटल पूर्णांक qla4_83xx_flash_lock(काष्ठा scsi_qla_host *ha)
अणु
	पूर्णांक lock_owner;
	पूर्णांक समयout = 0;
	uपूर्णांक32_t lock_status = 0;
	पूर्णांक ret_val = QLA_SUCCESS;

	जबतक (lock_status == 0) अणु
		lock_status = qla4_83xx_rd_reg(ha, QLA83XX_FLASH_LOCK);
		अगर (lock_status)
			अवरोध;

		अगर (++समयout >= QLA83XX_FLASH_LOCK_TIMEOUT / 20) अणु
			lock_owner = qla4_83xx_rd_reg(ha,
						      QLA83XX_FLASH_LOCK_ID);
			ql4_prपूर्णांकk(KERN_ERR, ha, "%s: flash lock by func %d failed, held by func %d\n",
				   __func__, ha->func_num, lock_owner);
			ret_val = QLA_ERROR;
			अवरोध;
		पूर्ण
		msleep(20);
	पूर्ण

	qla4_83xx_wr_reg(ha, QLA83XX_FLASH_LOCK_ID, ha->func_num);
	वापस ret_val;
पूर्ण

अटल व्योम qla4_83xx_flash_unlock(काष्ठा scsi_qla_host *ha)
अणु
	/* Reading FLASH_UNLOCK रेजिस्टर unlocks the Flash */
	qla4_83xx_wr_reg(ha, QLA83XX_FLASH_LOCK_ID, 0xFF);
	qla4_83xx_rd_reg(ha, QLA83XX_FLASH_UNLOCK);
पूर्ण

पूर्णांक qla4_83xx_flash_पढ़ो_u32(काष्ठा scsi_qla_host *ha, uपूर्णांक32_t flash_addr,
			     uपूर्णांक8_t *p_data, पूर्णांक u32_word_count)
अणु
	पूर्णांक i;
	uपूर्णांक32_t u32_word;
	uपूर्णांक32_t addr = flash_addr;
	पूर्णांक ret_val = QLA_SUCCESS;

	ret_val = qla4_83xx_flash_lock(ha);
	अगर (ret_val == QLA_ERROR)
		जाओ निकास_lock_error;

	अगर (addr & 0x03) अणु
		ql4_prपूर्णांकk(KERN_ERR, ha, "%s: Illegal addr = 0x%x\n",
			   __func__, addr);
		ret_val = QLA_ERROR;
		जाओ निकास_flash_पढ़ो;
	पूर्ण

	क्रम (i = 0; i < u32_word_count; i++) अणु
		ret_val = qla4_83xx_wr_reg_indirect(ha,
						    QLA83XX_FLASH_सूचीECT_WINDOW,
						    (addr & 0xFFFF0000));
		अगर (ret_val == QLA_ERROR) अणु
			ql4_prपूर्णांकk(KERN_ERR, ha, "%s: failed to write addr 0x%x to FLASH_DIRECT_WINDOW\n!",
				   __func__, addr);
			जाओ निकास_flash_पढ़ो;
		पूर्ण

		ret_val = qla4_83xx_rd_reg_indirect(ha,
						QLA83XX_FLASH_सूचीECT_DATA(addr),
						&u32_word);
		अगर (ret_val == QLA_ERROR) अणु
			ql4_prपूर्णांकk(KERN_ERR, ha, "%s: failed to read addr 0x%x!\n",
				   __func__, addr);
			जाओ निकास_flash_पढ़ो;
		पूर्ण

		*(__le32 *)p_data = le32_to_cpu(u32_word);
		p_data = p_data + 4;
		addr = addr + 4;
	पूर्ण

निकास_flash_पढ़ो:
	qla4_83xx_flash_unlock(ha);

निकास_lock_error:
	वापस ret_val;
पूर्ण

पूर्णांक qla4_83xx_lockless_flash_पढ़ो_u32(काष्ठा scsi_qla_host *ha,
				      uपूर्णांक32_t flash_addr, uपूर्णांक8_t *p_data,
				      पूर्णांक u32_word_count)
अणु
	uपूर्णांक32_t i;
	uपूर्णांक32_t u32_word;
	uपूर्णांक32_t flash_offset;
	uपूर्णांक32_t addr = flash_addr;
	पूर्णांक ret_val = QLA_SUCCESS;

	flash_offset = addr & (QLA83XX_FLASH_SECTOR_SIZE - 1);

	अगर (addr & 0x3) अणु
		ql4_prपूर्णांकk(KERN_ERR, ha, "%s: Illegal addr = 0x%x\n",
			   __func__, addr);
		ret_val = QLA_ERROR;
		जाओ निकास_lockless_पढ़ो;
	पूर्ण

	ret_val = qla4_83xx_wr_reg_indirect(ha, QLA83XX_FLASH_सूचीECT_WINDOW,
					    addr);
	अगर (ret_val == QLA_ERROR) अणु
		ql4_prपूर्णांकk(KERN_ERR, ha, "%s: failed to write addr 0x%x to FLASH_DIRECT_WINDOW!\n",
			   __func__, addr);
		जाओ निकास_lockless_पढ़ो;
	पूर्ण

	/* Check अगर data is spपढ़ो across multiple sectors  */
	अगर ((flash_offset + (u32_word_count * माप(uपूर्णांक32_t))) >
	    (QLA83XX_FLASH_SECTOR_SIZE - 1)) अणु

		/* Multi sector पढ़ो */
		क्रम (i = 0; i < u32_word_count; i++) अणु
			ret_val = qla4_83xx_rd_reg_indirect(ha,
						QLA83XX_FLASH_सूचीECT_DATA(addr),
						&u32_word);
			अगर (ret_val == QLA_ERROR) अणु
				ql4_prपूर्णांकk(KERN_ERR, ha, "%s: failed to read addr 0x%x!\n",
					   __func__, addr);
				जाओ निकास_lockless_पढ़ो;
			पूर्ण

			*(__le32 *)p_data  = le32_to_cpu(u32_word);
			p_data = p_data + 4;
			addr = addr + 4;
			flash_offset = flash_offset + 4;

			अगर (flash_offset > (QLA83XX_FLASH_SECTOR_SIZE - 1)) अणु
				/* This ग_लिखो is needed once क्रम each sector */
				ret_val = qla4_83xx_wr_reg_indirect(ha,
						   QLA83XX_FLASH_सूचीECT_WINDOW,
						   addr);
				अगर (ret_val == QLA_ERROR) अणु
					ql4_prपूर्णांकk(KERN_ERR, ha, "%s: failed to write addr 0x%x to FLASH_DIRECT_WINDOW!\n",
						   __func__, addr);
					जाओ निकास_lockless_पढ़ो;
				पूर्ण
				flash_offset = 0;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Single sector पढ़ो */
		क्रम (i = 0; i < u32_word_count; i++) अणु
			ret_val = qla4_83xx_rd_reg_indirect(ha,
						QLA83XX_FLASH_सूचीECT_DATA(addr),
						&u32_word);
			अगर (ret_val == QLA_ERROR) अणु
				ql4_prपूर्णांकk(KERN_ERR, ha, "%s: failed to read addr 0x%x!\n",
					   __func__, addr);
				जाओ निकास_lockless_पढ़ो;
			पूर्ण

			*(__le32 *)p_data = le32_to_cpu(u32_word);
			p_data = p_data + 4;
			addr = addr + 4;
		पूर्ण
	पूर्ण

निकास_lockless_पढ़ो:
	वापस ret_val;
पूर्ण

व्योम qla4_83xx_rom_lock_recovery(काष्ठा scsi_qla_host *ha)
अणु
	अगर (qla4_83xx_flash_lock(ha))
		ql4_prपूर्णांकk(KERN_INFO, ha, "%s: Resetting rom lock\n", __func__);

	/*
	 * We got the lock, or someone अन्यथा is holding the lock
	 * since we are restting, क्रमcefully unlock
	 */
	qla4_83xx_flash_unlock(ha);
पूर्ण

#घोषणा INTENT_TO_RECOVER	0x01
#घोषणा PROCEED_TO_RECOVER	0x02

अटल पूर्णांक qla4_83xx_lock_recovery(काष्ठा scsi_qla_host *ha)
अणु

	uपूर्णांक32_t lock = 0, lockid;
	पूर्णांक ret_val = QLA_ERROR;

	lockid = ha->isp_ops->rd_reg_direct(ha, QLA83XX_DRV_LOCKRECOVERY);

	/* Check क्रम other Recovery in progress, go रुको */
	अगर ((lockid & 0x3) != 0)
		जाओ निकास_lock_recovery;

	/* Intent to Recover */
	ha->isp_ops->wr_reg_direct(ha, QLA83XX_DRV_LOCKRECOVERY,
				   (ha->func_num << 2) | INTENT_TO_RECOVER);

	msleep(200);

	/* Check Intent to Recover is advertised */
	lockid = ha->isp_ops->rd_reg_direct(ha, QLA83XX_DRV_LOCKRECOVERY);
	अगर ((lockid & 0x3C) != (ha->func_num << 2))
		जाओ निकास_lock_recovery;

	ql4_prपूर्णांकk(KERN_INFO, ha, "%s: IDC Lock recovery initiated for func %d\n",
		   __func__, ha->func_num);

	/* Proceed to Recover */
	ha->isp_ops->wr_reg_direct(ha, QLA83XX_DRV_LOCKRECOVERY,
				   (ha->func_num << 2) | PROCEED_TO_RECOVER);

	/* Force Unlock */
	ha->isp_ops->wr_reg_direct(ha, QLA83XX_DRV_LOCK_ID, 0xFF);
	ha->isp_ops->rd_reg_direct(ha, QLA83XX_DRV_UNLOCK);

	/* Clear bits 0-5 in IDC_RECOVERY रेजिस्टर*/
	ha->isp_ops->wr_reg_direct(ha, QLA83XX_DRV_LOCKRECOVERY, 0);

	/* Get lock */
	lock = ha->isp_ops->rd_reg_direct(ha, QLA83XX_DRV_LOCK);
	अगर (lock) अणु
		lockid = ha->isp_ops->rd_reg_direct(ha, QLA83XX_DRV_LOCK_ID);
		lockid = ((lockid + (1 << 8)) & ~0xFF) | ha->func_num;
		ha->isp_ops->wr_reg_direct(ha, QLA83XX_DRV_LOCK_ID, lockid);
		ret_val = QLA_SUCCESS;
	पूर्ण

निकास_lock_recovery:
	वापस ret_val;
पूर्ण

#घोषणा	QLA83XX_DRV_LOCK_MSLEEP		200

पूर्णांक qla4_83xx_drv_lock(काष्ठा scsi_qla_host *ha)
अणु
	पूर्णांक समयout = 0;
	uपूर्णांक32_t status = 0;
	पूर्णांक ret_val = QLA_SUCCESS;
	uपूर्णांक32_t first_owner = 0;
	uपूर्णांक32_t पंचांगo_owner = 0;
	uपूर्णांक32_t lock_id;
	uपूर्णांक32_t func_num;
	uपूर्णांक32_t lock_cnt;

	जबतक (status == 0) अणु
		status = qla4_83xx_rd_reg(ha, QLA83XX_DRV_LOCK);
		अगर (status) अणु
			/* Increment Counter (8-31) and update func_num (0-7) on
			 * getting a successful lock  */
			lock_id = qla4_83xx_rd_reg(ha, QLA83XX_DRV_LOCK_ID);
			lock_id = ((lock_id + (1 << 8)) & ~0xFF) | ha->func_num;
			qla4_83xx_wr_reg(ha, QLA83XX_DRV_LOCK_ID, lock_id);
			अवरोध;
		पूर्ण

		अगर (समयout == 0)
			/* Save counter + ID of function holding the lock क्रम
			 * first failure */
			first_owner = ha->isp_ops->rd_reg_direct(ha,
							  QLA83XX_DRV_LOCK_ID);

		अगर (++समयout >=
		    (QLA83XX_DRV_LOCK_TIMEOUT / QLA83XX_DRV_LOCK_MSLEEP)) अणु
			पंचांगo_owner = qla4_83xx_rd_reg(ha, QLA83XX_DRV_LOCK_ID);
			func_num = पंचांगo_owner & 0xFF;
			lock_cnt = पंचांगo_owner >> 8;
			ql4_prपूर्णांकk(KERN_INFO, ha, "%s: Lock by func %d failed after 2s, lock held by func %d, lock count %d, first_owner %d\n",
				   __func__, ha->func_num, func_num, lock_cnt,
				   (first_owner & 0xFF));

			अगर (first_owner != पंचांगo_owner) अणु
				/* Some other driver got lock, OR same driver
				 * got lock again (counter value changed), when
				 * we were रुकोing क्रम lock.
				 * Retry क्रम another 2 sec */
				ql4_prपूर्णांकk(KERN_INFO, ha, "%s: IDC lock failed for func %d\n",
					   __func__, ha->func_num);
				समयout = 0;
			पूर्ण अन्यथा अणु
				/* Same driver holding lock > 2sec.
				 * Force Recovery */
				ret_val = qla4_83xx_lock_recovery(ha);
				अगर (ret_val == QLA_SUCCESS) अणु
					/* Recovered and got lock */
					ql4_prपूर्णांकk(KERN_INFO, ha, "%s: IDC lock Recovery by %d successful\n",
						   __func__, ha->func_num);
					अवरोध;
				पूर्ण
				/* Recovery Failed, some other function
				 * has the lock, रुको क्रम 2secs and retry */
				ql4_prपूर्णांकk(KERN_INFO, ha, "%s: IDC lock Recovery by %d failed, Retrying timeout\n",
					   __func__, ha->func_num);
				समयout = 0;
			पूर्ण
		पूर्ण
		msleep(QLA83XX_DRV_LOCK_MSLEEP);
	पूर्ण

	वापस ret_val;
पूर्ण

व्योम qla4_83xx_drv_unlock(काष्ठा scsi_qla_host *ha)
अणु
	पूर्णांक id;

	id = qla4_83xx_rd_reg(ha, QLA83XX_DRV_LOCK_ID);

	अगर ((id & 0xFF) != ha->func_num) अणु
		ql4_prपूर्णांकk(KERN_ERR, ha, "%s: IDC Unlock by %d failed, lock owner is %d\n",
			   __func__, ha->func_num, (id & 0xFF));
		वापस;
	पूर्ण

	/* Keep lock counter value, update the ha->func_num to 0xFF */
	qla4_83xx_wr_reg(ha, QLA83XX_DRV_LOCK_ID, (id | 0xFF));
	qla4_83xx_rd_reg(ha, QLA83XX_DRV_UNLOCK);
पूर्ण

व्योम qla4_83xx_set_idc_करोntreset(काष्ठा scsi_qla_host *ha)
अणु
	uपूर्णांक32_t idc_ctrl;

	idc_ctrl = qla4_83xx_rd_reg(ha, QLA83XX_IDC_DRV_CTRL);
	idc_ctrl |= DONTRESET_BIT0;
	qla4_83xx_wr_reg(ha, QLA83XX_IDC_DRV_CTRL, idc_ctrl);
	DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha, "%s: idc_ctrl = %d\n", __func__,
			  idc_ctrl));
पूर्ण

व्योम qla4_83xx_clear_idc_करोntreset(काष्ठा scsi_qla_host *ha)
अणु
	uपूर्णांक32_t idc_ctrl;

	idc_ctrl = qla4_83xx_rd_reg(ha, QLA83XX_IDC_DRV_CTRL);
	idc_ctrl &= ~DONTRESET_BIT0;
	qla4_83xx_wr_reg(ha, QLA83XX_IDC_DRV_CTRL, idc_ctrl);
	DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha, "%s: idc_ctrl = %d\n", __func__,
			  idc_ctrl));
पूर्ण

पूर्णांक qla4_83xx_idc_करोntreset(काष्ठा scsi_qla_host *ha)
अणु
	uपूर्णांक32_t idc_ctrl;

	idc_ctrl = qla4_83xx_rd_reg(ha, QLA83XX_IDC_DRV_CTRL);
	वापस idc_ctrl & DONTRESET_BIT0;
पूर्ण

/*-------------------------IDC State Machine ---------------------*/

क्रमागत अणु
	UNKNOWN_CLASS = 0,
	NIC_CLASS,
	FCOE_CLASS,
	ISCSI_CLASS
पूर्ण;

काष्ठा device_info अणु
	पूर्णांक func_num;
	पूर्णांक device_type;
	पूर्णांक port_num;
पूर्ण;

पूर्णांक qla4_83xx_can_perक्रमm_reset(काष्ठा scsi_qla_host *ha)
अणु
	uपूर्णांक32_t drv_active;
	uपूर्णांक32_t dev_part, dev_part1, dev_part2;
	पूर्णांक i;
	काष्ठा device_info device_map[16];
	पूर्णांक func_nibble;
	पूर्णांक nibble;
	पूर्णांक nic_present = 0;
	पूर्णांक iscsi_present = 0;
	पूर्णांक iscsi_func_low = 0;

	/* Use the dev_partition रेजिस्टर to determine the PCI function number
	 * and then check drv_active रेजिस्टर to see which driver is loaded */
	dev_part1 = qla4_83xx_rd_reg(ha,
				     ha->reg_tbl[QLA8XXX_CRB_DEV_PART_INFO]);
	dev_part2 = qla4_83xx_rd_reg(ha, QLA83XX_CRB_DEV_PART_INFO2);
	drv_active = qla4_83xx_rd_reg(ha, ha->reg_tbl[QLA8XXX_CRB_DRV_ACTIVE]);

	/* Each function has 4 bits in dev_partition Info रेजिस्टर,
	 * Lower 2 bits - device type, Upper 2 bits - physical port number */
	dev_part = dev_part1;
	क्रम (i = nibble = 0; i <= 15; i++, nibble++) अणु
		func_nibble = dev_part & (0xF << (nibble * 4));
		func_nibble >>= (nibble * 4);
		device_map[i].func_num = i;
		device_map[i].device_type = func_nibble & 0x3;
		device_map[i].port_num = func_nibble & 0xC;

		अगर (device_map[i].device_type == NIC_CLASS) अणु
			अगर (drv_active & (1 << device_map[i].func_num)) अणु
				nic_present++;
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अगर (device_map[i].device_type == ISCSI_CLASS) अणु
			अगर (drv_active & (1 << device_map[i].func_num)) अणु
				अगर (!iscsi_present ||
				    (iscsi_present &&
				     (iscsi_func_low > device_map[i].func_num)))
					iscsi_func_low = device_map[i].func_num;

				iscsi_present++;
			पूर्ण
		पूर्ण

		/* For function_num[8..15] get info from dev_part2 रेजिस्टर */
		अगर (nibble == 7) अणु
			nibble = 0;
			dev_part = dev_part2;
		पूर्ण
	पूर्ण

	/* NIC, iSCSI and FCOE are the Reset owners based on order, NIC माला_लो
	 * precedence over iSCSI and FCOE and iSCSI over FCOE, based on drivers
	 * present. */
	अगर (!nic_present && (ha->func_num == iscsi_func_low)) अणु
		DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha,
				  "%s: can reset - NIC not present and lower iSCSI function is %d\n",
				  __func__, ha->func_num));
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * qla4_83xx_need_reset_handler - Code to start reset sequence
 * @ha: poपूर्णांकer to adapter काष्ठाure
 *
 * Note: IDC lock must be held upon entry
 **/
व्योम qla4_83xx_need_reset_handler(काष्ठा scsi_qla_host *ha)
अणु
	uपूर्णांक32_t dev_state, drv_state, drv_active;
	अचिन्हित दीर्घ reset_समयout, dev_init_समयout;

	ql4_prपूर्णांकk(KERN_INFO, ha, "%s: Performing ISP error recovery\n",
		   __func__);

	अगर (!test_bit(AF_8XXX_RST_OWNER, &ha->flags)) अणु
		DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha, "%s: reset acknowledged\n",
				  __func__));
		qla4_8xxx_set_rst_पढ़ोy(ha);

		/* Non-reset owners ACK Reset and रुको क्रम device INIT state
		 * as part of Reset Recovery by Reset Owner */
		dev_init_समयout = jअगरfies + (ha->nx_dev_init_समयout * HZ);

		करो अणु
			अगर (समय_after_eq(jअगरfies, dev_init_समयout)) अणु
				ql4_prपूर्णांकk(KERN_INFO, ha, "%s: Non Reset owner dev init timeout\n",
					   __func__);
				अवरोध;
			पूर्ण

			ha->isp_ops->idc_unlock(ha);
			msleep(1000);
			ha->isp_ops->idc_lock(ha);

			dev_state = qla4_8xxx_rd_direct(ha,
							QLA8XXX_CRB_DEV_STATE);
		पूर्ण जबतक (dev_state == QLA8XXX_DEV_NEED_RESET);
	पूर्ण अन्यथा अणु
		qla4_8xxx_set_rst_पढ़ोy(ha);
		reset_समयout = jअगरfies + (ha->nx_reset_समयout * HZ);
		drv_state = qla4_8xxx_rd_direct(ha, QLA8XXX_CRB_DRV_STATE);
		drv_active = qla4_8xxx_rd_direct(ha, QLA8XXX_CRB_DRV_ACTIVE);

		ql4_prपूर्णांकk(KERN_INFO, ha, "%s: drv_state = 0x%x, drv_active = 0x%x\n",
			   __func__, drv_state, drv_active);

		जबतक (drv_state != drv_active) अणु
			अगर (समय_after_eq(jअगरfies, reset_समयout)) अणु
				ql4_prपूर्णांकk(KERN_INFO, ha, "%s: %s: RESET TIMEOUT! drv_state: 0x%08x, drv_active: 0x%08x\n",
					   __func__, DRIVER_NAME, drv_state,
					   drv_active);
				अवरोध;
			पूर्ण

			ha->isp_ops->idc_unlock(ha);
			msleep(1000);
			ha->isp_ops->idc_lock(ha);

			drv_state = qla4_8xxx_rd_direct(ha,
							QLA8XXX_CRB_DRV_STATE);
			drv_active = qla4_8xxx_rd_direct(ha,
							QLA8XXX_CRB_DRV_ACTIVE);
		पूर्ण

		अगर (drv_state != drv_active) अणु
			ql4_prपूर्णांकk(KERN_INFO, ha, "%s: Reset_owner turning off drv_active of non-acking function 0x%x\n",
				   __func__, (drv_active ^ drv_state));
			drv_active = drv_active & drv_state;
			qla4_8xxx_wr_direct(ha, QLA8XXX_CRB_DRV_ACTIVE,
					    drv_active);
		पूर्ण

		clear_bit(AF_8XXX_RST_OWNER, &ha->flags);
		/* Start Reset Recovery */
		qla4_8xxx_device_bootstrap(ha);
	पूर्ण
पूर्ण

व्योम qla4_83xx_get_idc_param(काष्ठा scsi_qla_host *ha)
अणु
	uपूर्णांक32_t idc_params, ret_val;

	ret_val = qla4_83xx_flash_पढ़ो_u32(ha, QLA83XX_IDC_PARAM_ADDR,
					   (uपूर्णांक8_t *)&idc_params, 1);
	अगर (ret_val == QLA_SUCCESS) अणु
		ha->nx_dev_init_समयout = idc_params & 0xFFFF;
		ha->nx_reset_समयout = (idc_params >> 16) & 0xFFFF;
	पूर्ण अन्यथा अणु
		ha->nx_dev_init_समयout = ROM_DEV_INIT_TIMEOUT;
		ha->nx_reset_समयout = ROM_DRV_RESET_ACK_TIMEOUT;
	पूर्ण

	DEBUG2(ql4_prपूर्णांकk(KERN_DEBUG, ha,
			  "%s: ha->nx_dev_init_timeout = %d, ha->nx_reset_timeout = %d\n",
			  __func__, ha->nx_dev_init_समयout,
			  ha->nx_reset_समयout));
पूर्ण

/*-------------------------Reset Sequence Functions-----------------------*/

अटल व्योम qla4_83xx_dump_reset_seq_hdr(काष्ठा scsi_qla_host *ha)
अणु
	uपूर्णांक8_t *phdr;

	अगर (!ha->reset_पंचांगplt.buff) अणु
		ql4_prपूर्णांकk(KERN_ERR, ha, "%s: Error: Invalid reset_seq_template\n",
			   __func__);
		वापस;
	पूर्ण

	phdr = ha->reset_पंचांगplt.buff;

	DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha,
			  "Reset Template: 0x%X 0x%X 0x%X 0x%X 0x%X 0x%X 0x%X 0x%X 0x%X 0x%X 0x%X 0x%X 0x%X 0x%X 0x%X 0x%X\n",
			  *phdr, *(phdr+1), *(phdr+2), *(phdr+3), *(phdr+4),
			  *(phdr+5), *(phdr+6), *(phdr+7), *(phdr + 8),
			  *(phdr+9), *(phdr+10), *(phdr+11), *(phdr+12),
			  *(phdr+13), *(phdr+14), *(phdr+15)));
पूर्ण

अटल पूर्णांक qla4_83xx_copy_bootloader(काष्ठा scsi_qla_host *ha)
अणु
	uपूर्णांक8_t *p_cache;
	uपूर्णांक32_t src, count, size;
	uपूर्णांक64_t dest;
	पूर्णांक ret_val = QLA_SUCCESS;

	src = QLA83XX_BOOTLOADER_FLASH_ADDR;
	dest = qla4_83xx_rd_reg(ha, QLA83XX_BOOTLOADER_ADDR);
	size = qla4_83xx_rd_reg(ha, QLA83XX_BOOTLOADER_SIZE);

	/* 128 bit alignment check */
	अगर (size & 0xF)
		size = (size + 16) & ~0xF;

	/* 16 byte count */
	count = size/16;

	p_cache = vदो_स्मृति(size);
	अगर (p_cache == शून्य) अणु
		ql4_prपूर्णांकk(KERN_ERR, ha, "%s: Failed to allocate memory for boot loader cache\n",
			   __func__);
		ret_val = QLA_ERROR;
		जाओ निकास_copy_bootloader;
	पूर्ण

	ret_val = qla4_83xx_lockless_flash_पढ़ो_u32(ha, src, p_cache,
						    size / माप(uपूर्णांक32_t));
	अगर (ret_val == QLA_ERROR) अणु
		ql4_prपूर्णांकk(KERN_ERR, ha, "%s: Error reading firmware from flash\n",
			   __func__);
		जाओ निकास_copy_error;
	पूर्ण
	DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha, "%s: Read firmware from flash\n",
			  __func__));

	/* 128 bit/16 byte ग_लिखो to MS memory */
	ret_val = qla4_8xxx_ms_mem_ग_लिखो_128b(ha, dest, (uपूर्णांक32_t *)p_cache,
					      count);
	अगर (ret_val == QLA_ERROR) अणु
		ql4_prपूर्णांकk(KERN_ERR, ha, "%s: Error writing firmware to MS\n",
			   __func__);
		जाओ निकास_copy_error;
	पूर्ण

	DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha, "%s: Wrote firmware size %d to MS\n",
			  __func__, size));

निकास_copy_error:
	vमुक्त(p_cache);

निकास_copy_bootloader:
	वापस ret_val;
पूर्ण

अटल पूर्णांक qla4_83xx_check_cmd_peg_status(काष्ठा scsi_qla_host *ha)
अणु
	uपूर्णांक32_t val, ret_val = QLA_ERROR;
	पूर्णांक retries = CRB_CMDPEG_CHECK_RETRY_COUNT;

	करो अणु
		val = qla4_83xx_rd_reg(ha, QLA83XX_CMDPEG_STATE);
		अगर (val == PHAN_INITIALIZE_COMPLETE) अणु
			DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha,
					  "%s: Command Peg initialization complete. State=0x%x\n",
					  __func__, val));
			ret_val = QLA_SUCCESS;
			अवरोध;
		पूर्ण
		msleep(CRB_CMDPEG_CHECK_DELAY);
	पूर्ण जबतक (--retries);

	वापस ret_val;
पूर्ण

/**
 * qla4_83xx_poll_reg - Poll the given CRB addr क्रम duration msecs till
 * value पढ़ो ANDed with test_mask is equal to test_result.
 *
 * @ha : Poपूर्णांकer to adapter काष्ठाure
 * @addr : CRB रेजिस्टर address
 * @duration : Poll क्रम total of "duration" msecs
 * @test_mask : Mask value पढ़ो with "test_mask"
 * @test_result : Compare (value&test_mask) with test_result.
 **/
अटल पूर्णांक qla4_83xx_poll_reg(काष्ठा scsi_qla_host *ha, uपूर्णांक32_t addr,
			      पूर्णांक duration, uपूर्णांक32_t test_mask,
			      uपूर्णांक32_t test_result)
अणु
	uपूर्णांक32_t value;
	uपूर्णांक8_t retries;
	पूर्णांक ret_val = QLA_SUCCESS;

	ret_val = qla4_83xx_rd_reg_indirect(ha, addr, &value);
	अगर (ret_val == QLA_ERROR)
		जाओ निकास_poll_reg;

	retries = duration / 10;
	करो अणु
		अगर ((value & test_mask) != test_result) अणु
			msleep(duration / 10);
			ret_val = qla4_83xx_rd_reg_indirect(ha, addr, &value);
			अगर (ret_val == QLA_ERROR)
				जाओ निकास_poll_reg;

			ret_val = QLA_ERROR;
		पूर्ण अन्यथा अणु
			ret_val = QLA_SUCCESS;
			अवरोध;
		पूर्ण
	पूर्ण जबतक (retries--);

निकास_poll_reg:
	अगर (ret_val == QLA_ERROR) अणु
		ha->reset_पंचांगplt.seq_error++;
		ql4_prपूर्णांकk(KERN_ERR, ha, "%s: Poll Failed:  0x%08x 0x%08x 0x%08x\n",
			   __func__, value, test_mask, test_result);
	पूर्ण

	वापस ret_val;
पूर्ण

अटल पूर्णांक qla4_83xx_reset_seq_checksum_test(काष्ठा scsi_qla_host *ha)
अणु
	uपूर्णांक32_t sum =  0;
	uपूर्णांक16_t *buff = (uपूर्णांक16_t *)ha->reset_पंचांगplt.buff;
	पूर्णांक u16_count =  ha->reset_पंचांगplt.hdr->size / माप(uपूर्णांक16_t);
	पूर्णांक ret_val;

	जबतक (u16_count-- > 0)
		sum += *buff++;

	जबतक (sum >> 16)
		sum = (sum & 0xFFFF) +  (sum >> 16);

	/* checksum of 0 indicates a valid ढाँचा */
	अगर (~sum) अणु
		ret_val = QLA_SUCCESS;
	पूर्ण अन्यथा अणु
		ql4_prपूर्णांकk(KERN_ERR, ha, "%s: Reset seq checksum failed\n",
			   __func__);
		ret_val = QLA_ERROR;
	पूर्ण

	वापस ret_val;
पूर्ण

/**
 * qla4_83xx_पढ़ो_reset_ढाँचा - Read Reset Template from Flash
 * @ha: Poपूर्णांकer to adapter काष्ठाure
 **/
व्योम qla4_83xx_पढ़ो_reset_ढाँचा(काष्ठा scsi_qla_host *ha)
अणु
	uपूर्णांक8_t *p_buff;
	uपूर्णांक32_t addr, पंचांगplt_hdr_def_size, पंचांगplt_hdr_size;
	uपूर्णांक32_t ret_val;

	ha->reset_पंचांगplt.seq_error = 0;
	ha->reset_पंचांगplt.buff = vदो_स्मृति(QLA83XX_RESTART_TEMPLATE_SIZE);
	अगर (ha->reset_पंचांगplt.buff == शून्य) अणु
		ql4_prपूर्णांकk(KERN_ERR, ha, "%s: Failed to allocate reset template resources\n",
			   __func__);
		जाओ निकास_पढ़ो_reset_ढाँचा;
	पूर्ण

	p_buff = ha->reset_पंचांगplt.buff;
	addr = QLA83XX_RESET_TEMPLATE_ADDR;

	पंचांगplt_hdr_def_size = माप(काष्ठा qla4_83xx_reset_ढाँचा_hdr) /
				    माप(uपूर्णांक32_t);

	DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha,
			  "%s: Read template hdr size %d from Flash\n",
			  __func__, पंचांगplt_hdr_def_size));

	/* Copy ढाँचा header from flash */
	ret_val = qla4_83xx_flash_पढ़ो_u32(ha, addr, p_buff,
					   पंचांगplt_hdr_def_size);
	अगर (ret_val != QLA_SUCCESS) अणु
		ql4_prपूर्णांकk(KERN_ERR, ha, "%s: Failed to read reset template\n",
			   __func__);
		जाओ निकास_पढ़ो_ढाँचा_error;
	पूर्ण

	ha->reset_पंचांगplt.hdr =
		(काष्ठा qla4_83xx_reset_ढाँचा_hdr *)ha->reset_पंचांगplt.buff;

	/* Validate the ढाँचा header size and signature */
	पंचांगplt_hdr_size = ha->reset_पंचांगplt.hdr->hdr_size/माप(uपूर्णांक32_t);
	अगर ((पंचांगplt_hdr_size != पंचांगplt_hdr_def_size) ||
	    (ha->reset_पंचांगplt.hdr->signature != RESET_TMPLT_HDR_SIGNATURE)) अणु
		ql4_prपूर्णांकk(KERN_ERR, ha, "%s: Template Header size %d is invalid, tmplt_hdr_def_size %d\n",
			   __func__, पंचांगplt_hdr_size, पंचांगplt_hdr_def_size);
		जाओ निकास_पढ़ो_ढाँचा_error;
	पूर्ण

	addr = QLA83XX_RESET_TEMPLATE_ADDR + ha->reset_पंचांगplt.hdr->hdr_size;
	p_buff = ha->reset_पंचांगplt.buff + ha->reset_पंचांगplt.hdr->hdr_size;
	पंचांगplt_hdr_def_size = (ha->reset_पंचांगplt.hdr->size -
			      ha->reset_पंचांगplt.hdr->hdr_size) / माप(uपूर्णांक32_t);

	DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha,
			  "%s: Read rest of the template size %d\n",
			  __func__, ha->reset_पंचांगplt.hdr->size));

	/* Copy rest of the ढाँचा */
	ret_val = qla4_83xx_flash_पढ़ो_u32(ha, addr, p_buff,
					   पंचांगplt_hdr_def_size);
	अगर (ret_val != QLA_SUCCESS) अणु
		ql4_prपूर्णांकk(KERN_ERR, ha, "%s: Failed to read reset template\n",
			   __func__);
		जाओ निकास_पढ़ो_ढाँचा_error;
	पूर्ण

	/* Integrity check */
	अगर (qla4_83xx_reset_seq_checksum_test(ha)) अणु
		ql4_prपूर्णांकk(KERN_ERR, ha, "%s: Reset Seq checksum failed!\n",
			   __func__);
		जाओ निकास_पढ़ो_ढाँचा_error;
	पूर्ण
	DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha,
			  "%s: Reset Seq checksum passed, Get stop, start and init seq offsets\n",
			  __func__));

	/* Get STOP, START, INIT sequence offsets */
	ha->reset_पंचांगplt.init_offset = ha->reset_पंचांगplt.buff +
				      ha->reset_पंचांगplt.hdr->init_seq_offset;
	ha->reset_पंचांगplt.start_offset = ha->reset_पंचांगplt.buff +
				       ha->reset_पंचांगplt.hdr->start_seq_offset;
	ha->reset_पंचांगplt.stop_offset = ha->reset_पंचांगplt.buff +
				      ha->reset_पंचांगplt.hdr->hdr_size;
	qla4_83xx_dump_reset_seq_hdr(ha);

	जाओ निकास_पढ़ो_reset_ढाँचा;

निकास_पढ़ो_ढाँचा_error:
	vमुक्त(ha->reset_पंचांगplt.buff);

निकास_पढ़ो_reset_ढाँचा:
	वापस;
पूर्ण

/**
 * qla4_83xx_पढ़ो_ग_लिखो_crb_reg - Read from raddr and ग_लिखो value to waddr.
 *
 * @ha : Poपूर्णांकer to adapter काष्ठाure
 * @raddr : CRB address to पढ़ो from
 * @waddr : CRB address to ग_लिखो to
 **/
अटल व्योम qla4_83xx_पढ़ो_ग_लिखो_crb_reg(काष्ठा scsi_qla_host *ha,
					 uपूर्णांक32_t raddr, uपूर्णांक32_t waddr)
अणु
	uपूर्णांक32_t value;

	qla4_83xx_rd_reg_indirect(ha, raddr, &value);
	qla4_83xx_wr_reg_indirect(ha, waddr, value);
पूर्ण

/**
 * qla4_83xx_rmw_crb_reg - Read Modअगरy Write crb रेजिस्टर
 *
 * This function पढ़ो value from raddr, AND with test_mask,
 * Shअगरt Left,Right/OR/XOR with values RMW header and ग_लिखो value to waddr.
 *
 * @ha : Poपूर्णांकer to adapter काष्ठाure
 * @raddr : CRB address to पढ़ो from
 * @waddr : CRB address to ग_लिखो to
 * @p_rmw_hdr : header with shअगरt/or/xor values.
 **/
अटल व्योम qla4_83xx_rmw_crb_reg(काष्ठा scsi_qla_host *ha, uपूर्णांक32_t raddr,
				  uपूर्णांक32_t waddr,
				  काष्ठा qla4_83xx_rmw *p_rmw_hdr)
अणु
	uपूर्णांक32_t value;

	अगर (p_rmw_hdr->index_a)
		value = ha->reset_पंचांगplt.array[p_rmw_hdr->index_a];
	अन्यथा
		qla4_83xx_rd_reg_indirect(ha, raddr, &value);

	value &= p_rmw_hdr->test_mask;
	value <<= p_rmw_hdr->shl;
	value >>= p_rmw_hdr->shr;
	value |= p_rmw_hdr->or_value;
	value ^= p_rmw_hdr->xor_value;

	qla4_83xx_wr_reg_indirect(ha, waddr, value);

	वापस;
पूर्ण

अटल व्योम qla4_83xx_ग_लिखो_list(काष्ठा scsi_qla_host *ha,
				 काष्ठा qla4_83xx_reset_entry_hdr *p_hdr)
अणु
	काष्ठा qla4_83xx_entry *p_entry;
	uपूर्णांक32_t i;

	p_entry = (काष्ठा qla4_83xx_entry *)
		  ((अक्षर *)p_hdr + माप(काष्ठा qla4_83xx_reset_entry_hdr));

	क्रम (i = 0; i < p_hdr->count; i++, p_entry++) अणु
		qla4_83xx_wr_reg_indirect(ha, p_entry->arg1, p_entry->arg2);
		अगर (p_hdr->delay)
			udelay((uपूर्णांक32_t)(p_hdr->delay));
	पूर्ण
पूर्ण

अटल व्योम qla4_83xx_पढ़ो_ग_लिखो_list(काष्ठा scsi_qla_host *ha,
				      काष्ठा qla4_83xx_reset_entry_hdr *p_hdr)
अणु
	काष्ठा qla4_83xx_entry *p_entry;
	uपूर्णांक32_t i;

	p_entry = (काष्ठा qla4_83xx_entry *)
		  ((अक्षर *)p_hdr + माप(काष्ठा qla4_83xx_reset_entry_hdr));

	क्रम (i = 0; i < p_hdr->count; i++, p_entry++) अणु
		qla4_83xx_पढ़ो_ग_लिखो_crb_reg(ha, p_entry->arg1, p_entry->arg2);
		अगर (p_hdr->delay)
			udelay((uपूर्णांक32_t)(p_hdr->delay));
	पूर्ण
पूर्ण

अटल व्योम qla4_83xx_poll_list(काष्ठा scsi_qla_host *ha,
				काष्ठा qla4_83xx_reset_entry_hdr *p_hdr)
अणु
	दीर्घ delay;
	काष्ठा qla4_83xx_entry *p_entry;
	काष्ठा qla4_83xx_poll *p_poll;
	uपूर्णांक32_t i;
	uपूर्णांक32_t value;

	p_poll = (काष्ठा qla4_83xx_poll *)
		 ((अक्षर *)p_hdr + माप(काष्ठा qla4_83xx_reset_entry_hdr));

	/* Entries start after 8 byte qla4_83xx_poll, poll header contains
	 * the test_mask, test_value. */
	p_entry = (काष्ठा qla4_83xx_entry *)((अक्षर *)p_poll +
					     माप(काष्ठा qla4_83xx_poll));

	delay = (दीर्घ)p_hdr->delay;
	अगर (!delay) अणु
		क्रम (i = 0; i < p_hdr->count; i++, p_entry++) अणु
			qla4_83xx_poll_reg(ha, p_entry->arg1, delay,
					   p_poll->test_mask,
					   p_poll->test_value);
		पूर्ण
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < p_hdr->count; i++, p_entry++) अणु
			अगर (qla4_83xx_poll_reg(ha, p_entry->arg1, delay,
					       p_poll->test_mask,
					       p_poll->test_value)) अणु
				qla4_83xx_rd_reg_indirect(ha, p_entry->arg1,
							  &value);
				qla4_83xx_rd_reg_indirect(ha, p_entry->arg2,
							  &value);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम qla4_83xx_poll_ग_लिखो_list(काष्ठा scsi_qla_host *ha,
				      काष्ठा qla4_83xx_reset_entry_hdr *p_hdr)
अणु
	दीर्घ delay;
	काष्ठा qla4_83xx_quad_entry *p_entry;
	काष्ठा qla4_83xx_poll *p_poll;
	uपूर्णांक32_t i;

	p_poll = (काष्ठा qla4_83xx_poll *)
		 ((अक्षर *)p_hdr + माप(काष्ठा qla4_83xx_reset_entry_hdr));
	p_entry = (काष्ठा qla4_83xx_quad_entry *)
		  ((अक्षर *)p_poll + माप(काष्ठा qla4_83xx_poll));
	delay = (दीर्घ)p_hdr->delay;

	क्रम (i = 0; i < p_hdr->count; i++, p_entry++) अणु
		qla4_83xx_wr_reg_indirect(ha, p_entry->dr_addr,
					  p_entry->dr_value);
		qla4_83xx_wr_reg_indirect(ha, p_entry->ar_addr,
					  p_entry->ar_value);
		अगर (delay) अणु
			अगर (qla4_83xx_poll_reg(ha, p_entry->ar_addr, delay,
					       p_poll->test_mask,
					       p_poll->test_value)) अणु
				DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha,
						  "%s: Timeout Error: poll list, item_num %d, entry_num %d\n",
						  __func__, i,
						  ha->reset_पंचांगplt.seq_index));
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम qla4_83xx_पढ़ो_modअगरy_ग_लिखो(काष्ठा scsi_qla_host *ha,
					काष्ठा qla4_83xx_reset_entry_hdr *p_hdr)
अणु
	काष्ठा qla4_83xx_entry *p_entry;
	काष्ठा qla4_83xx_rmw *p_rmw_hdr;
	uपूर्णांक32_t i;

	p_rmw_hdr = (काष्ठा qla4_83xx_rmw *)
		    ((अक्षर *)p_hdr + माप(काष्ठा qla4_83xx_reset_entry_hdr));
	p_entry = (काष्ठा qla4_83xx_entry *)
		  ((अक्षर *)p_rmw_hdr + माप(काष्ठा qla4_83xx_rmw));

	क्रम (i = 0; i < p_hdr->count; i++, p_entry++) अणु
		qla4_83xx_rmw_crb_reg(ha, p_entry->arg1, p_entry->arg2,
				      p_rmw_hdr);
		अगर (p_hdr->delay)
			udelay((uपूर्णांक32_t)(p_hdr->delay));
	पूर्ण
पूर्ण

अटल व्योम qla4_83xx_छोड़ो(काष्ठा scsi_qla_host *ha,
			    काष्ठा qla4_83xx_reset_entry_hdr *p_hdr)
अणु
	अगर (p_hdr->delay)
		mdelay((uपूर्णांक32_t)((दीर्घ)p_hdr->delay));
पूर्ण

अटल व्योम qla4_83xx_poll_पढ़ो_list(काष्ठा scsi_qla_host *ha,
				     काष्ठा qla4_83xx_reset_entry_hdr *p_hdr)
अणु
	दीर्घ delay;
	पूर्णांक index;
	काष्ठा qla4_83xx_quad_entry *p_entry;
	काष्ठा qla4_83xx_poll *p_poll;
	uपूर्णांक32_t i;
	uपूर्णांक32_t value;

	p_poll = (काष्ठा qla4_83xx_poll *)
		 ((अक्षर *)p_hdr + माप(काष्ठा qla4_83xx_reset_entry_hdr));
	p_entry = (काष्ठा qla4_83xx_quad_entry *)
		  ((अक्षर *)p_poll + माप(काष्ठा qla4_83xx_poll));
	delay = (दीर्घ)p_hdr->delay;

	क्रम (i = 0; i < p_hdr->count; i++, p_entry++) अणु
		qla4_83xx_wr_reg_indirect(ha, p_entry->ar_addr,
					  p_entry->ar_value);
		अगर (delay) अणु
			अगर (qla4_83xx_poll_reg(ha, p_entry->ar_addr, delay,
					       p_poll->test_mask,
					       p_poll->test_value)) अणु
				DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha,
						  "%s: Timeout Error: poll list, Item_num %d, entry_num %d\n",
						  __func__, i,
						  ha->reset_पंचांगplt.seq_index));
			पूर्ण अन्यथा अणु
				index = ha->reset_पंचांगplt.array_index;
				qla4_83xx_rd_reg_indirect(ha, p_entry->dr_addr,
							  &value);
				ha->reset_पंचांगplt.array[index++] = value;

				अगर (index == QLA83XX_MAX_RESET_SEQ_ENTRIES)
					ha->reset_पंचांगplt.array_index = 1;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम qla4_83xx_seq_end(काष्ठा scsi_qla_host *ha,
			      काष्ठा qla4_83xx_reset_entry_hdr *p_hdr)
अणु
	ha->reset_पंचांगplt.seq_end = 1;
पूर्ण

अटल व्योम qla4_83xx_ढाँचा_end(काष्ठा scsi_qla_host *ha,
				   काष्ठा qla4_83xx_reset_entry_hdr *p_hdr)
अणु
	ha->reset_पंचांगplt.ढाँचा_end = 1;

	अगर (ha->reset_पंचांगplt.seq_error == 0) अणु
		DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha,
				  "%s: Reset sequence completed SUCCESSFULLY.\n",
				  __func__));
	पूर्ण अन्यथा अणु
		ql4_prपूर्णांकk(KERN_ERR, ha, "%s: Reset sequence completed with some timeout errors.\n",
			   __func__);
	पूर्ण
पूर्ण

/**
 * qla4_83xx_process_reset_ढाँचा - Process reset ढाँचा.
 *
 * Process all entries in reset ढाँचा till entry with SEQ_END opcode,
 * which indicates end of the reset ढाँचा processing. Each entry has a
 * Reset Entry header, entry opcode/command, with size of the entry, number
 * of entries in sub-sequence and delay in microsecs or समयout in millisecs.
 *
 * @ha : Poपूर्णांकer to adapter काष्ठाure
 * @p_buff : Common reset entry header.
 **/
अटल व्योम qla4_83xx_process_reset_ढाँचा(काष्ठा scsi_qla_host *ha,
					     अक्षर *p_buff)
अणु
	पूर्णांक index, entries;
	काष्ठा qla4_83xx_reset_entry_hdr *p_hdr;
	अक्षर *p_entry = p_buff;

	ha->reset_पंचांगplt.seq_end = 0;
	ha->reset_पंचांगplt.ढाँचा_end = 0;
	entries = ha->reset_पंचांगplt.hdr->entries;
	index = ha->reset_पंचांगplt.seq_index;

	क्रम (; (!ha->reset_पंचांगplt.seq_end) && (index  < entries); index++) अणु

		p_hdr = (काष्ठा qla4_83xx_reset_entry_hdr *)p_entry;
		चयन (p_hdr->cmd) अणु
		हाल OPCODE_NOP:
			अवरोध;
		हाल OPCODE_WRITE_LIST:
			qla4_83xx_ग_लिखो_list(ha, p_hdr);
			अवरोध;
		हाल OPCODE_READ_WRITE_LIST:
			qla4_83xx_पढ़ो_ग_लिखो_list(ha, p_hdr);
			अवरोध;
		हाल OPCODE_POLL_LIST:
			qla4_83xx_poll_list(ha, p_hdr);
			अवरोध;
		हाल OPCODE_POLL_WRITE_LIST:
			qla4_83xx_poll_ग_लिखो_list(ha, p_hdr);
			अवरोध;
		हाल OPCODE_READ_MODIFY_WRITE:
			qla4_83xx_पढ़ो_modअगरy_ग_लिखो(ha, p_hdr);
			अवरोध;
		हाल OPCODE_SEQ_PAUSE:
			qla4_83xx_छोड़ो(ha, p_hdr);
			अवरोध;
		हाल OPCODE_SEQ_END:
			qla4_83xx_seq_end(ha, p_hdr);
			अवरोध;
		हाल OPCODE_TMPL_END:
			qla4_83xx_ढाँचा_end(ha, p_hdr);
			अवरोध;
		हाल OPCODE_POLL_READ_LIST:
			qla4_83xx_poll_पढ़ो_list(ha, p_hdr);
			अवरोध;
		शेष:
			ql4_prपूर्णांकk(KERN_ERR, ha, "%s: Unknown command ==> 0x%04x on entry = %d\n",
				   __func__, p_hdr->cmd, index);
			अवरोध;
		पूर्ण

		/* Set poपूर्णांकer to next entry in the sequence. */
		p_entry += p_hdr->size;
	पूर्ण

	ha->reset_पंचांगplt.seq_index = index;
पूर्ण

अटल व्योम qla4_83xx_process_stop_seq(काष्ठा scsi_qla_host *ha)
अणु
	ha->reset_पंचांगplt.seq_index = 0;
	qla4_83xx_process_reset_ढाँचा(ha, ha->reset_पंचांगplt.stop_offset);

	अगर (ha->reset_पंचांगplt.seq_end != 1)
		ql4_prपूर्णांकk(KERN_ERR, ha, "%s: Abrupt STOP Sub-Sequence end.\n",
			   __func__);
पूर्ण

अटल व्योम qla4_83xx_process_start_seq(काष्ठा scsi_qla_host *ha)
अणु
	qla4_83xx_process_reset_ढाँचा(ha, ha->reset_पंचांगplt.start_offset);

	अगर (ha->reset_पंचांगplt.ढाँचा_end != 1)
		ql4_prपूर्णांकk(KERN_ERR, ha, "%s: Abrupt START Sub-Sequence end.\n",
			   __func__);
पूर्ण

अटल व्योम qla4_83xx_process_init_seq(काष्ठा scsi_qla_host *ha)
अणु
	qla4_83xx_process_reset_ढाँचा(ha, ha->reset_पंचांगplt.init_offset);

	अगर (ha->reset_पंचांगplt.seq_end != 1)
		ql4_prपूर्णांकk(KERN_ERR, ha, "%s: Abrupt INIT Sub-Sequence end.\n",
			   __func__);
पूर्ण

अटल पूर्णांक qla4_83xx_restart(काष्ठा scsi_qla_host *ha)
अणु
	पूर्णांक ret_val = QLA_SUCCESS;
	uपूर्णांक32_t idc_ctrl;

	qla4_83xx_process_stop_seq(ha);

	/*
	 * Collect minidump.
	 * If IDC_CTRL BIT1 is set, clear it on going to INIT state and
	 * करोn't collect minidump
	 */
	idc_ctrl = qla4_83xx_rd_reg(ha, QLA83XX_IDC_DRV_CTRL);
	अगर (idc_ctrl & GRACEFUL_RESET_BIT1) अणु
		qla4_83xx_wr_reg(ha, QLA83XX_IDC_DRV_CTRL,
				 (idc_ctrl & ~GRACEFUL_RESET_BIT1));
		ql4_prपूर्णांकk(KERN_INFO, ha, "%s: Graceful RESET: Not collecting minidump\n",
			   __func__);
	पूर्ण अन्यथा अणु
		qla4_8xxx_get_minidump(ha);
	पूर्ण

	qla4_83xx_process_init_seq(ha);

	अगर (qla4_83xx_copy_bootloader(ha)) अणु
		ql4_prपूर्णांकk(KERN_ERR, ha, "%s: Copy bootloader, firmware restart failed!\n",
			   __func__);
		ret_val = QLA_ERROR;
		जाओ निकास_restart;
	पूर्ण

	qla4_83xx_wr_reg(ha, QLA83XX_FW_IMAGE_VALID, QLA83XX_BOOT_FROM_FLASH);
	qla4_83xx_process_start_seq(ha);

निकास_restart:
	वापस ret_val;
पूर्ण

पूर्णांक qla4_83xx_start_firmware(काष्ठा scsi_qla_host *ha)
अणु
	पूर्णांक ret_val = QLA_SUCCESS;

	ret_val = qla4_83xx_restart(ha);
	अगर (ret_val == QLA_ERROR) अणु
		ql4_prपूर्णांकk(KERN_ERR, ha, "%s: Restart error\n", __func__);
		जाओ निकास_start_fw;
	पूर्ण अन्यथा अणु
		DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha, "%s: Restart done\n",
				  __func__));
	पूर्ण

	ret_val = qla4_83xx_check_cmd_peg_status(ha);
	अगर (ret_val == QLA_ERROR)
		ql4_prपूर्णांकk(KERN_ERR, ha, "%s: Peg not initialized\n",
			   __func__);

निकास_start_fw:
	वापस ret_val;
पूर्ण

/*----------------------Interrupt Related functions ---------------------*/

अटल व्योम qla4_83xx_disable_iocb_पूर्णांकrs(काष्ठा scsi_qla_host *ha)
अणु
	अगर (test_and_clear_bit(AF_83XX_IOCB_INTR_ON, &ha->flags))
		qla4_8xxx_पूर्णांकr_disable(ha);
पूर्ण

अटल व्योम qla4_83xx_disable_mbox_पूर्णांकrs(काष्ठा scsi_qla_host *ha)
अणु
	uपूर्णांक32_t mb_पूर्णांक, ret;

	अगर (test_and_clear_bit(AF_83XX_MBOX_INTR_ON, &ha->flags)) अणु
		ret = पढ़ोl(&ha->qla4_83xx_reg->mbox_पूर्णांक);
		mb_पूर्णांक = ret & ~INT_ENABLE_FW_MB;
		ग_लिखोl(mb_पूर्णांक, &ha->qla4_83xx_reg->mbox_पूर्णांक);
		ग_लिखोl(1, &ha->qla4_83xx_reg->leg_पूर्णांक_mask);
	पूर्ण
पूर्ण

व्योम qla4_83xx_disable_पूर्णांकrs(काष्ठा scsi_qla_host *ha)
अणु
	qla4_83xx_disable_mbox_पूर्णांकrs(ha);
	qla4_83xx_disable_iocb_पूर्णांकrs(ha);
पूर्ण

अटल व्योम qla4_83xx_enable_iocb_पूर्णांकrs(काष्ठा scsi_qla_host *ha)
अणु
	अगर (!test_bit(AF_83XX_IOCB_INTR_ON, &ha->flags)) अणु
		qla4_8xxx_पूर्णांकr_enable(ha);
		set_bit(AF_83XX_IOCB_INTR_ON, &ha->flags);
	पूर्ण
पूर्ण

व्योम qla4_83xx_enable_mbox_पूर्णांकrs(काष्ठा scsi_qla_host *ha)
अणु
	uपूर्णांक32_t mb_पूर्णांक;

	अगर (!test_bit(AF_83XX_MBOX_INTR_ON, &ha->flags)) अणु
		mb_पूर्णांक = INT_ENABLE_FW_MB;
		ग_लिखोl(mb_पूर्णांक, &ha->qla4_83xx_reg->mbox_पूर्णांक);
		ग_लिखोl(0, &ha->qla4_83xx_reg->leg_पूर्णांक_mask);
		set_bit(AF_83XX_MBOX_INTR_ON, &ha->flags);
	पूर्ण
पूर्ण


व्योम qla4_83xx_enable_पूर्णांकrs(काष्ठा scsi_qla_host *ha)
अणु
	qla4_83xx_enable_mbox_पूर्णांकrs(ha);
	qla4_83xx_enable_iocb_पूर्णांकrs(ha);
पूर्ण


व्योम qla4_83xx_queue_mbox_cmd(काष्ठा scsi_qla_host *ha, uपूर्णांक32_t *mbx_cmd,
			      पूर्णांक incount)
अणु
	पूर्णांक i;

	/* Load all mailbox रेजिस्टरs, except mailbox 0. */
	क्रम (i = 1; i < incount; i++)
		ग_लिखोl(mbx_cmd[i], &ha->qla4_83xx_reg->mailbox_in[i]);

	ग_लिखोl(mbx_cmd[0], &ha->qla4_83xx_reg->mailbox_in[0]);

	/* Set Host Interrupt रेजिस्टर to 1, to tell the firmware that
	 * a mailbox command is pending. Firmware after पढ़ोing the
	 * mailbox command, clears the host पूर्णांकerrupt रेजिस्टर */
	ग_लिखोl(HINT_MBX_INT_PENDING, &ha->qla4_83xx_reg->host_पूर्णांकr);
पूर्ण

व्योम qla4_83xx_process_mbox_पूर्णांकr(काष्ठा scsi_qla_host *ha, पूर्णांक outcount)
अणु
	पूर्णांक पूर्णांकr_status;

	पूर्णांकr_status = पढ़ोl(&ha->qla4_83xx_reg->risc_पूर्णांकr);
	अगर (पूर्णांकr_status) अणु
		ha->mbox_status_count = outcount;
		ha->isp_ops->पूर्णांकerrupt_service_routine(ha, पूर्णांकr_status);
	पूर्ण
पूर्ण

/**
 * qla4_83xx_isp_reset - Resets ISP and पातs all outstanding commands.
 * @ha: poपूर्णांकer to host adapter काष्ठाure.
 **/
पूर्णांक qla4_83xx_isp_reset(काष्ठा scsi_qla_host *ha)
अणु
	पूर्णांक rval;
	uपूर्णांक32_t dev_state;

	ha->isp_ops->idc_lock(ha);
	dev_state = qla4_8xxx_rd_direct(ha, QLA8XXX_CRB_DEV_STATE);

	अगर (ql4xकरोntresethba)
		qla4_83xx_set_idc_करोntreset(ha);

	अगर (dev_state == QLA8XXX_DEV_READY) अणु
		/* If IDC_CTRL DONTRESETHBA_BIT0 is set करोnt करो reset
		 * recovery */
		अगर (qla4_83xx_idc_करोntreset(ha) == DONTRESET_BIT0) अणु
			ql4_prपूर्णांकk(KERN_ERR, ha, "%s: Reset recovery disabled\n",
				   __func__);
			rval = QLA_ERROR;
			जाओ निकास_isp_reset;
		पूर्ण

		DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha, "%s: HW State: NEED RESET\n",
				  __func__));
		qla4_8xxx_wr_direct(ha, QLA8XXX_CRB_DEV_STATE,
				    QLA8XXX_DEV_NEED_RESET);

	पूर्ण अन्यथा अणु
		/* If device_state is NEED_RESET, go ahead with
		 * Reset,irrespective of ql4xकरोntresethba. This is to allow a
		 * non-reset-owner to क्रमce a reset. Non-reset-owner sets
		 * the IDC_CTRL BIT0 to prevent Reset-owner from करोing a Reset
		 * and then क्रमces a Reset by setting device_state to
		 * NEED_RESET. */
		DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha,
				  "%s: HW state already set to NEED_RESET\n",
				  __func__));
	पूर्ण

	/* For ISP8324 and ISP8042, Reset owner is NIC, iSCSI or FCOE based on
	 * priority and which drivers are present. Unlike ISP8022, the function
	 * setting NEED_RESET, may not be the Reset owner. */
	अगर (qla4_83xx_can_perक्रमm_reset(ha))
		set_bit(AF_8XXX_RST_OWNER, &ha->flags);

	ha->isp_ops->idc_unlock(ha);
	rval = qla4_8xxx_device_state_handler(ha);

	ha->isp_ops->idc_lock(ha);
	qla4_8xxx_clear_rst_पढ़ोy(ha);
निकास_isp_reset:
	ha->isp_ops->idc_unlock(ha);

	अगर (rval == QLA_SUCCESS)
		clear_bit(AF_FW_RECOVERY, &ha->flags);

	वापस rval;
पूर्ण

अटल व्योम qla4_83xx_dump_छोड़ो_control_regs(काष्ठा scsi_qla_host *ha)
अणु
	u32 val = 0, val1 = 0;
	पूर्णांक i;

	qla4_83xx_rd_reg_indirect(ha, QLA83XX_SRE_SHIM_CONTROL, &val);
	DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha, "SRE-Shim Ctrl:0x%x\n", val));

	/* Port 0 Rx Buffer Pause Threshold Registers. */
	DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha,
		"Port 0 Rx Buffer Pause Threshold Registers[TC7..TC0]:"));
	क्रम (i = 0; i < 8; i++) अणु
		qla4_83xx_rd_reg_indirect(ha,
				QLA83XX_PORT0_RXB_PAUSE_THRS + (i * 0x4), &val);
		DEBUG2(pr_info("0x%x ", val));
	पूर्ण

	DEBUG2(pr_info("\n"));

	/* Port 1 Rx Buffer Pause Threshold Registers. */
	DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha,
		"Port 1 Rx Buffer Pause Threshold Registers[TC7..TC0]:"));
	क्रम (i = 0; i < 8; i++) अणु
		qla4_83xx_rd_reg_indirect(ha,
				QLA83XX_PORT1_RXB_PAUSE_THRS + (i * 0x4), &val);
		DEBUG2(pr_info("0x%x  ", val));
	पूर्ण

	DEBUG2(pr_info("\n"));

	/* Port 0 RxB Traffic Class Max Cell Registers. */
	DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha,
		"Port 0 RxB Traffic Class Max Cell Registers[3..0]:"));
	क्रम (i = 0; i < 4; i++) अणु
		qla4_83xx_rd_reg_indirect(ha,
			       QLA83XX_PORT0_RXB_TC_MAX_CELL + (i * 0x4), &val);
		DEBUG2(pr_info("0x%x  ", val));
	पूर्ण

	DEBUG2(pr_info("\n"));

	/* Port 1 RxB Traffic Class Max Cell Registers. */
	DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha,
		"Port 1 RxB Traffic Class Max Cell Registers[3..0]:"));
	क्रम (i = 0; i < 4; i++) अणु
		qla4_83xx_rd_reg_indirect(ha,
			       QLA83XX_PORT1_RXB_TC_MAX_CELL + (i * 0x4), &val);
		DEBUG2(pr_info("0x%x  ", val));
	पूर्ण

	DEBUG2(pr_info("\n"));

	/* Port 0 RxB Rx Traffic Class Stats. */
	DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha,
			  "Port 0 RxB Rx Traffic Class Stats [TC7..TC0]"));
	क्रम (i = 7; i >= 0; i--) अणु
		qla4_83xx_rd_reg_indirect(ha, QLA83XX_PORT0_RXB_TC_STATS, &val);
		val &= ~(0x7 << 29);    /* Reset bits 29 to 31 */
		qla4_83xx_wr_reg_indirect(ha, QLA83XX_PORT0_RXB_TC_STATS,
					  (val | (i << 29)));
		qla4_83xx_rd_reg_indirect(ha, QLA83XX_PORT0_RXB_TC_STATS, &val);
		DEBUG2(pr_info("0x%x  ", val));
	पूर्ण

	DEBUG2(pr_info("\n"));

	/* Port 1 RxB Rx Traffic Class Stats. */
	DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha,
			  "Port 1 RxB Rx Traffic Class Stats [TC7..TC0]"));
	क्रम (i = 7; i >= 0; i--) अणु
		qla4_83xx_rd_reg_indirect(ha, QLA83XX_PORT1_RXB_TC_STATS, &val);
		val &= ~(0x7 << 29);    /* Reset bits 29 to 31 */
		qla4_83xx_wr_reg_indirect(ha, QLA83XX_PORT1_RXB_TC_STATS,
					  (val | (i << 29)));
		qla4_83xx_rd_reg_indirect(ha, QLA83XX_PORT1_RXB_TC_STATS, &val);
		DEBUG2(pr_info("0x%x  ", val));
	पूर्ण

	DEBUG2(pr_info("\n"));

	qla4_83xx_rd_reg_indirect(ha, QLA83XX_PORT2_IFB_PAUSE_THRS, &val);
	qla4_83xx_rd_reg_indirect(ha, QLA83XX_PORT3_IFB_PAUSE_THRS, &val1);

	DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha,
			  "IFB-Pause Thresholds: Port 2:0x%x, Port 3:0x%x\n",
			  val, val1));
पूर्ण

अटल व्योम __qla4_83xx_disable_छोड़ो(काष्ठा scsi_qla_host *ha)
अणु
	पूर्णांक i;

	/* set SRE-Shim Control Register */
	qla4_83xx_wr_reg_indirect(ha, QLA83XX_SRE_SHIM_CONTROL,
				  QLA83XX_SET_PAUSE_VAL);

	क्रम (i = 0; i < 8; i++) अणु
		/* Port 0 Rx Buffer Pause Threshold Registers. */
		qla4_83xx_wr_reg_indirect(ha,
				      QLA83XX_PORT0_RXB_PAUSE_THRS + (i * 0x4),
				      QLA83XX_SET_PAUSE_VAL);
		/* Port 1 Rx Buffer Pause Threshold Registers. */
		qla4_83xx_wr_reg_indirect(ha,
				      QLA83XX_PORT1_RXB_PAUSE_THRS + (i * 0x4),
				      QLA83XX_SET_PAUSE_VAL);
	पूर्ण

	क्रम (i = 0; i < 4; i++) अणु
		/* Port 0 RxB Traffic Class Max Cell Registers. */
		qla4_83xx_wr_reg_indirect(ha,
				     QLA83XX_PORT0_RXB_TC_MAX_CELL + (i * 0x4),
				     QLA83XX_SET_TC_MAX_CELL_VAL);
		/* Port 1 RxB Traffic Class Max Cell Registers. */
		qla4_83xx_wr_reg_indirect(ha,
				     QLA83XX_PORT1_RXB_TC_MAX_CELL + (i * 0x4),
				     QLA83XX_SET_TC_MAX_CELL_VAL);
	पूर्ण

	qla4_83xx_wr_reg_indirect(ha, QLA83XX_PORT2_IFB_PAUSE_THRS,
				  QLA83XX_SET_PAUSE_VAL);
	qla4_83xx_wr_reg_indirect(ha, QLA83XX_PORT3_IFB_PAUSE_THRS,
				  QLA83XX_SET_PAUSE_VAL);

	ql4_prपूर्णांकk(KERN_INFO, ha, "Disabled pause frames successfully.\n");
पूर्ण

/**
 * qla4_83xx_eport_init - Initialize EPort.
 * @ha: Poपूर्णांकer to host adapter काष्ठाure.
 *
 * If EPort hardware is in reset state beक्रमe disabling छोड़ो, there would be
 * serious hardware wedging issues. To prevent this perक्रमm eport init everyसमय
 * beक्रमe disabling छोड़ो frames.
 **/
अटल व्योम qla4_83xx_eport_init(काष्ठा scsi_qla_host *ha)
अणु
	/* Clear the 8 रेजिस्टरs */
	qla4_83xx_wr_reg_indirect(ha, QLA83XX_RESET_REG, 0x0);
	qla4_83xx_wr_reg_indirect(ha, QLA83XX_RESET_PORT0, 0x0);
	qla4_83xx_wr_reg_indirect(ha, QLA83XX_RESET_PORT1, 0x0);
	qla4_83xx_wr_reg_indirect(ha, QLA83XX_RESET_PORT2, 0x0);
	qla4_83xx_wr_reg_indirect(ha, QLA83XX_RESET_PORT3, 0x0);
	qla4_83xx_wr_reg_indirect(ha, QLA83XX_RESET_SRE_SHIM, 0x0);
	qla4_83xx_wr_reg_indirect(ha, QLA83XX_RESET_EPG_SHIM, 0x0);
	qla4_83xx_wr_reg_indirect(ha, QLA83XX_RESET_ETHER_PCS, 0x0);

	/* Write any value to Reset Control रेजिस्टर */
	qla4_83xx_wr_reg_indirect(ha, QLA83XX_RESET_CONTROL, 0xFF);

	ql4_prपूर्णांकk(KERN_INFO, ha, "EPORT is out of reset.\n");
पूर्ण

व्योम qla4_83xx_disable_छोड़ो(काष्ठा scsi_qla_host *ha)
अणु
	ha->isp_ops->idc_lock(ha);
	/* Beक्रमe disabling छोड़ो frames, ensure that eport is not in reset */
	qla4_83xx_eport_init(ha);
	qla4_83xx_dump_छोड़ो_control_regs(ha);
	__qla4_83xx_disable_छोड़ो(ha);
	ha->isp_ops->idc_unlock(ha);
पूर्ण

/**
 * qla4_83xx_is_detached - Check अगर we are marked invisible.
 * @ha: Poपूर्णांकer to host adapter काष्ठाure.
 **/
पूर्णांक qla4_83xx_is_detached(काष्ठा scsi_qla_host *ha)
अणु
	uपूर्णांक32_t drv_active;

	drv_active = qla4_8xxx_rd_direct(ha, QLA8XXX_CRB_DRV_ACTIVE);

	अगर (test_bit(AF_INIT_DONE, &ha->flags) &&
	    !(drv_active & (1 << ha->func_num))) अणु
		DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha, "%s: drv_active = 0x%X\n",
				  __func__, drv_active));
		वापस QLA_SUCCESS;
	पूर्ण

	वापस QLA_ERROR;
पूर्ण
