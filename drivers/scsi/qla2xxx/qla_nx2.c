<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * QLogic Fibre Channel HBA Driver
 * Copyright (c)  2003-2014 QLogic Corporation
 */

#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/delay.h>

#समावेश "qla_def.h"
#समावेश "qla_gbl.h"

#घोषणा TIMEOUT_100_MS 100

अटल स्थिर uपूर्णांक32_t qla8044_reg_tbl[] = अणु
	QLA8044_PEG_HALT_STATUS1,
	QLA8044_PEG_HALT_STATUS2,
	QLA8044_PEG_ALIVE_COUNTER,
	QLA8044_CRB_DRV_ACTIVE,
	QLA8044_CRB_DEV_STATE,
	QLA8044_CRB_DRV_STATE,
	QLA8044_CRB_DRV_SCRATCH,
	QLA8044_CRB_DEV_PART_INFO1,
	QLA8044_CRB_IDC_VER_MAJOR,
	QLA8044_FW_VER_MAJOR,
	QLA8044_FW_VER_MINOR,
	QLA8044_FW_VER_SUB,
	QLA8044_CMDPEG_STATE,
	QLA8044_ASIC_TEMP,
पूर्ण;

/* 8044 Flash Read/Write functions */
uपूर्णांक32_t
qla8044_rd_reg(काष्ठा qla_hw_data *ha, uदीर्घ addr)
अणु
	वापस पढ़ोl((व्योम __iomem *) (ha->nx_pcibase + addr));
पूर्ण

व्योम
qla8044_wr_reg(काष्ठा qla_hw_data *ha, uदीर्घ addr, uपूर्णांक32_t val)
अणु
	ग_लिखोl(val, (व्योम __iomem *)((ha)->nx_pcibase + addr));
पूर्ण

पूर्णांक
qla8044_rd_direct(काष्ठा scsi_qla_host *vha,
	स्थिर uपूर्णांक32_t crb_reg)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;

	अगर (crb_reg < CRB_REG_INDEX_MAX)
		वापस qla8044_rd_reg(ha, qla8044_reg_tbl[crb_reg]);
	अन्यथा
		वापस QLA_FUNCTION_FAILED;
पूर्ण

व्योम
qla8044_wr_direct(काष्ठा scsi_qla_host *vha,
	स्थिर uपूर्णांक32_t crb_reg,
	स्थिर uपूर्णांक32_t value)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;

	अगर (crb_reg < CRB_REG_INDEX_MAX)
		qla8044_wr_reg(ha, qla8044_reg_tbl[crb_reg], value);
पूर्ण

अटल पूर्णांक
qla8044_set_win_base(scsi_qla_host_t *vha, uपूर्णांक32_t addr)
अणु
	uपूर्णांक32_t val;
	पूर्णांक ret_val = QLA_SUCCESS;
	काष्ठा qla_hw_data *ha = vha->hw;

	qla8044_wr_reg(ha, QLA8044_CRB_WIN_FUNC(ha->portnum), addr);
	val = qla8044_rd_reg(ha, QLA8044_CRB_WIN_FUNC(ha->portnum));

	अगर (val != addr) अणु
		ql_log(ql_log_warn, vha, 0xb087,
		    "%s: Failed to set register window : "
		    "addr written 0x%x, read 0x%x!\n",
		    __func__, addr, val);
		ret_val = QLA_FUNCTION_FAILED;
	पूर्ण
	वापस ret_val;
पूर्ण

अटल पूर्णांक
qla8044_rd_reg_indirect(scsi_qla_host_t *vha, uपूर्णांक32_t addr, uपूर्णांक32_t *data)
अणु
	पूर्णांक ret_val = QLA_SUCCESS;
	काष्ठा qla_hw_data *ha = vha->hw;

	ret_val = qla8044_set_win_base(vha, addr);
	अगर (!ret_val)
		*data = qla8044_rd_reg(ha, QLA8044_WILDCARD);
	अन्यथा
		ql_log(ql_log_warn, vha, 0xb088,
		    "%s: failed read of addr 0x%x!\n", __func__, addr);
	वापस ret_val;
पूर्ण

अटल पूर्णांक
qla8044_wr_reg_indirect(scsi_qla_host_t *vha, uपूर्णांक32_t addr, uपूर्णांक32_t data)
अणु
	पूर्णांक ret_val = QLA_SUCCESS;
	काष्ठा qla_hw_data *ha = vha->hw;

	ret_val = qla8044_set_win_base(vha, addr);
	अगर (!ret_val)
		qla8044_wr_reg(ha, QLA8044_WILDCARD, data);
	अन्यथा
		ql_log(ql_log_warn, vha, 0xb089,
		    "%s: failed wrt to addr 0x%x, data 0x%x\n",
		    __func__, addr, data);
	वापस ret_val;
पूर्ण

/*
 * qla8044_पढ़ो_ग_लिखो_crb_reg - Read from raddr and ग_लिखो value to waddr.
 *
 * @ha : Poपूर्णांकer to adapter काष्ठाure
 * @raddr : CRB address to पढ़ो from
 * @waddr : CRB address to ग_लिखो to
 *
 */
अटल व्योम
qla8044_पढ़ो_ग_लिखो_crb_reg(काष्ठा scsi_qla_host *vha,
	uपूर्णांक32_t raddr, uपूर्णांक32_t waddr)
अणु
	uपूर्णांक32_t value;

	qla8044_rd_reg_indirect(vha, raddr, &value);
	qla8044_wr_reg_indirect(vha, waddr, value);
पूर्ण

अटल पूर्णांक
qla8044_poll_रुको_क्रम_पढ़ोy(काष्ठा scsi_qla_host *vha, uपूर्णांक32_t addr1,
	uपूर्णांक32_t mask)
अणु
	अचिन्हित दीर्घ समयout;
	uपूर्णांक32_t temp = 0;

	/* jअगरfies after 100ms */
	समयout = jअगरfies + msecs_to_jअगरfies(TIMEOUT_100_MS);
	करो अणु
		qla8044_rd_reg_indirect(vha, addr1, &temp);
		अगर ((temp & mask) != 0)
			अवरोध;
		अगर (समय_after_eq(jअगरfies, समयout)) अणु
			ql_log(ql_log_warn, vha, 0xb151,
				"Error in processing rdmdio entry\n");
			वापस -1;
		पूर्ण
	पूर्ण जबतक (1);

	वापस 0;
पूर्ण

अटल uपूर्णांक32_t
qla8044_ipmdio_rd_reg(काष्ठा scsi_qla_host *vha,
	uपूर्णांक32_t addr1, uपूर्णांक32_t addr3, uपूर्णांक32_t mask, uपूर्णांक32_t addr)
अणु
	uपूर्णांक32_t temp;
	पूर्णांक ret = 0;

	ret = qla8044_poll_रुको_क्रम_पढ़ोy(vha, addr1, mask);
	अगर (ret == -1)
		वापस -1;

	temp = (0x40000000 | addr);
	qla8044_wr_reg_indirect(vha, addr1, temp);

	ret = qla8044_poll_रुको_क्रम_पढ़ोy(vha, addr1, mask);
	अगर (ret == -1)
		वापस 0;

	qla8044_rd_reg_indirect(vha, addr3, &ret);

	वापस ret;
पूर्ण


अटल पूर्णांक
qla8044_poll_रुको_ipmdio_bus_idle(काष्ठा scsi_qla_host *vha,
	uपूर्णांक32_t addr1, uपूर्णांक32_t addr2, uपूर्णांक32_t addr3, uपूर्णांक32_t mask)
अणु
	अचिन्हित दीर्घ समयout;
	uपूर्णांक32_t temp;

	/* jअगरfies after 100 msecs */
	समयout = jअगरfies + msecs_to_jअगरfies(TIMEOUT_100_MS);
	करो अणु
		temp = qla8044_ipmdio_rd_reg(vha, addr1, addr3, mask, addr2);
		अगर ((temp & 0x1) != 1)
			अवरोध;
		अगर (समय_after_eq(jअगरfies, समयout)) अणु
			ql_log(ql_log_warn, vha, 0xb152,
			    "Error in processing mdiobus idle\n");
			वापस -1;
		पूर्ण
	पूर्ण जबतक (1);

	वापस 0;
पूर्ण

अटल पूर्णांक
qla8044_ipmdio_wr_reg(काष्ठा scsi_qla_host *vha, uपूर्णांक32_t addr1,
	uपूर्णांक32_t addr3, uपूर्णांक32_t mask, uपूर्णांक32_t addr, uपूर्णांक32_t value)
अणु
	पूर्णांक ret = 0;

	ret = qla8044_poll_रुको_क्रम_पढ़ोy(vha, addr1, mask);
	अगर (ret == -1)
		वापस -1;

	qla8044_wr_reg_indirect(vha, addr3, value);
	qla8044_wr_reg_indirect(vha, addr1, addr);

	ret = qla8044_poll_रुको_क्रम_पढ़ोy(vha, addr1, mask);
	अगर (ret == -1)
		वापस -1;

	वापस 0;
पूर्ण
/*
 * qla8044_rmw_crb_reg - Read value from raddr, AND with test_mask,
 * Shअगरt Left,Right/OR/XOR with values RMW header and ग_लिखो value to waddr.
 *
 * @vha : Poपूर्णांकer to adapter काष्ठाure
 * @raddr : CRB address to पढ़ो from
 * @waddr : CRB address to ग_लिखो to
 * @p_rmw_hdr : header with shअगरt/or/xor values.
 *
 */
अटल व्योम
qla8044_rmw_crb_reg(काष्ठा scsi_qla_host *vha,
	uपूर्णांक32_t raddr, uपूर्णांक32_t waddr,	काष्ठा qla8044_rmw *p_rmw_hdr)
अणु
	uपूर्णांक32_t value;

	अगर (p_rmw_hdr->index_a)
		value = vha->reset_पंचांगplt.array[p_rmw_hdr->index_a];
	अन्यथा
		qla8044_rd_reg_indirect(vha, raddr, &value);
	value &= p_rmw_hdr->test_mask;
	value <<= p_rmw_hdr->shl;
	value >>= p_rmw_hdr->shr;
	value |= p_rmw_hdr->or_value;
	value ^= p_rmw_hdr->xor_value;
	qla8044_wr_reg_indirect(vha, waddr, value);
	वापस;
पूर्ण

अटल अंतरभूत व्योम
qla8044_set_qsnt_पढ़ोy(काष्ठा scsi_qla_host *vha)
अणु
	uपूर्णांक32_t qsnt_state;
	काष्ठा qla_hw_data *ha = vha->hw;

	qsnt_state = qla8044_rd_direct(vha, QLA8044_CRB_DRV_STATE_INDEX);
	qsnt_state |= (1 << ha->portnum);
	qla8044_wr_direct(vha, QLA8044_CRB_DRV_STATE_INDEX, qsnt_state);
	ql_log(ql_log_info, vha, 0xb08e, "%s(%ld): qsnt_state: 0x%08x\n",
	     __func__, vha->host_no, qsnt_state);
पूर्ण

व्योम
qla8044_clear_qsnt_पढ़ोy(काष्ठा scsi_qla_host *vha)
अणु
	uपूर्णांक32_t qsnt_state;
	काष्ठा qla_hw_data *ha = vha->hw;

	qsnt_state = qla8044_rd_direct(vha, QLA8044_CRB_DRV_STATE_INDEX);
	qsnt_state &= ~(1 << ha->portnum);
	qla8044_wr_direct(vha, QLA8044_CRB_DRV_STATE_INDEX, qsnt_state);
	ql_log(ql_log_info, vha, 0xb08f, "%s(%ld): qsnt_state: 0x%08x\n",
	    __func__, vha->host_no, qsnt_state);
पूर्ण

/**
 * qla8044_lock_recovery - Recovers the idc_lock.
 * @vha : Poपूर्णांकer to adapter काष्ठाure
 *
 * Lock Recovery Register
 * 5-2	Lock recovery owner: Function ID of driver करोing lock recovery,
 *	valid अगर bits 1..0 are set by driver करोing lock recovery.
 * 1-0  1 - Driver पूर्णांकends to क्रमce unlock the IDC lock.
 *	2 - Driver is moving क्रमward to unlock the IDC lock. Driver clears
 *	    this field after क्रमce unlocking the IDC lock.
 *
 * Lock Recovery process
 * a. Read the IDC_LOCK_RECOVERY रेजिस्टर. If the value in bits 1..0 is
 *    greater than 0, then रुको क्रम the other driver to unlock otherwise
 *    move to the next step.
 * b. Indicate पूर्णांकent to क्रमce-unlock by writing 1h to the IDC_LOCK_RECOVERY
 *    रेजिस्टर bits 1..0 and also set the function# in bits 5..2.
 * c. Read the IDC_LOCK_RECOVERY रेजिस्टर again after a delay of 200ms.
 *    Wait क्रम the other driver to perक्रमm lock recovery अगर the function
 *    number in bits 5..2 has changed, otherwise move to the next step.
 * d. Write a value of 2h to the IDC_LOCK_RECOVERY रेजिस्टर bits 1..0
 *    leaving your function# in bits 5..2.
 * e. Force unlock using the DRIVER_UNLOCK रेजिस्टर and immediately clear
 *    the IDC_LOCK_RECOVERY bits 5..0 by writing 0.
 **/
अटल पूर्णांक
qla8044_lock_recovery(काष्ठा scsi_qla_host *vha)
अणु
	uपूर्णांक32_t lock = 0, lockid;
	काष्ठा qla_hw_data *ha = vha->hw;

	lockid = qla8044_rd_reg(ha, QLA8044_DRV_LOCKRECOVERY);

	/* Check क्रम other Recovery in progress, go रुको */
	अगर ((lockid & IDC_LOCK_RECOVERY_STATE_MASK) != 0)
		वापस QLA_FUNCTION_FAILED;

	/* Intent to Recover */
	qla8044_wr_reg(ha, QLA8044_DRV_LOCKRECOVERY,
	    (ha->portnum <<
	     IDC_LOCK_RECOVERY_STATE_SHIFT_BITS) | INTENT_TO_RECOVER);
	msleep(200);

	/* Check Intent to Recover is advertised */
	lockid = qla8044_rd_reg(ha, QLA8044_DRV_LOCKRECOVERY);
	अगर ((lockid & IDC_LOCK_RECOVERY_OWNER_MASK) != (ha->portnum <<
	    IDC_LOCK_RECOVERY_STATE_SHIFT_BITS))
		वापस QLA_FUNCTION_FAILED;

	ql_dbg(ql_dbg_p3p, vha, 0xb08B, "%s:%d: IDC Lock recovery initiated\n"
	    , __func__, ha->portnum);

	/* Proceed to Recover */
	qla8044_wr_reg(ha, QLA8044_DRV_LOCKRECOVERY,
	    (ha->portnum << IDC_LOCK_RECOVERY_STATE_SHIFT_BITS) |
	    PROCEED_TO_RECOVER);

	/* Force Unlock() */
	qla8044_wr_reg(ha, QLA8044_DRV_LOCK_ID, 0xFF);
	qla8044_rd_reg(ha, QLA8044_DRV_UNLOCK);

	/* Clear bits 0-5 in IDC_RECOVERY रेजिस्टर*/
	qla8044_wr_reg(ha, QLA8044_DRV_LOCKRECOVERY, 0);

	/* Get lock() */
	lock = qla8044_rd_reg(ha, QLA8044_DRV_LOCK);
	अगर (lock) अणु
		lockid = qla8044_rd_reg(ha, QLA8044_DRV_LOCK_ID);
		lockid = ((lockid + (1 << 8)) & ~0xFF) | ha->portnum;
		qla8044_wr_reg(ha, QLA8044_DRV_LOCK_ID, lockid);
		वापस QLA_SUCCESS;
	पूर्ण अन्यथा
		वापस QLA_FUNCTION_FAILED;
पूर्ण

पूर्णांक
qla8044_idc_lock(काष्ठा qla_hw_data *ha)
अणु
	uपूर्णांक32_t ret_val = QLA_SUCCESS, समयout = 0, status = 0;
	uपूर्णांक32_t lock_id, lock_cnt, func_num, पंचांगo_owner = 0, first_owner = 0;
	scsi_qla_host_t *vha = pci_get_drvdata(ha->pdev);

	जबतक (status == 0) अणु
		/* acquire semaphore5 from PCI HW block */
		status = qla8044_rd_reg(ha, QLA8044_DRV_LOCK);

		अगर (status) अणु
			/* Increment Counter (8-31) and update func_num (0-7) on
			 * getting a successful lock  */
			lock_id = qla8044_rd_reg(ha, QLA8044_DRV_LOCK_ID);
			lock_id = ((lock_id + (1 << 8)) & ~0xFF) | ha->portnum;
			qla8044_wr_reg(ha, QLA8044_DRV_LOCK_ID, lock_id);
			अवरोध;
		पूर्ण

		अगर (समयout == 0)
			first_owner = qla8044_rd_reg(ha, QLA8044_DRV_LOCK_ID);

		अगर (++समयout >=
		    (QLA8044_DRV_LOCK_TIMEOUT / QLA8044_DRV_LOCK_MSLEEP)) अणु
			पंचांगo_owner = qla8044_rd_reg(ha, QLA8044_DRV_LOCK_ID);
			func_num = पंचांगo_owner & 0xFF;
			lock_cnt = पंचांगo_owner >> 8;
			ql_log(ql_log_warn, vha, 0xb114,
			    "%s: Lock by func %d failed after 2s, lock held "
			    "by func %d, lock count %d, first_owner %d\n",
			    __func__, ha->portnum, func_num, lock_cnt,
			    (first_owner & 0xFF));
			अगर (first_owner != पंचांगo_owner) अणु
				/* Some other driver got lock,
				 * OR same driver got lock again (counter
				 * value changed), when we were रुकोing क्रम
				 * lock. Retry क्रम another 2 sec */
				ql_dbg(ql_dbg_p3p, vha, 0xb115,
				    "%s: %d: IDC lock failed\n",
				    __func__, ha->portnum);
				समयout = 0;
			पूर्ण अन्यथा अणु
				/* Same driver holding lock > 2sec.
				 * Force Recovery */
				अगर (qla8044_lock_recovery(vha) == QLA_SUCCESS) अणु
					/* Recovered and got lock */
					ret_val = QLA_SUCCESS;
					ql_dbg(ql_dbg_p3p, vha, 0xb116,
					    "%s:IDC lock Recovery by %d"
					    "successful...\n", __func__,
					     ha->portnum);
				पूर्ण
				/* Recovery Failed, some other function
				 * has the lock, रुको क्रम 2secs
				 * and retry
				 */
				ql_dbg(ql_dbg_p3p, vha, 0xb08a,
				       "%s: IDC lock Recovery by %d "
				       "failed, Retrying timeout\n", __func__,
				       ha->portnum);
				समयout = 0;
			पूर्ण
		पूर्ण
		msleep(QLA8044_DRV_LOCK_MSLEEP);
	पूर्ण
	वापस ret_val;
पूर्ण

व्योम
qla8044_idc_unlock(काष्ठा qla_hw_data *ha)
अणु
	पूर्णांक id;
	scsi_qla_host_t *vha = pci_get_drvdata(ha->pdev);

	id = qla8044_rd_reg(ha, QLA8044_DRV_LOCK_ID);

	अगर ((id & 0xFF) != ha->portnum) अणु
		ql_log(ql_log_warn, vha, 0xb118,
		    "%s: IDC Unlock by %d failed, lock owner is %d!\n",
		    __func__, ha->portnum, (id & 0xFF));
		वापस;
	पूर्ण

	/* Keep lock counter value, update the ha->func_num to 0xFF */
	qla8044_wr_reg(ha, QLA8044_DRV_LOCK_ID, (id | 0xFF));
	qla8044_rd_reg(ha, QLA8044_DRV_UNLOCK);
पूर्ण

/* 8044 Flash Lock/Unlock functions */
अटल पूर्णांक
qla8044_flash_lock(scsi_qla_host_t *vha)
अणु
	पूर्णांक lock_owner;
	पूर्णांक समयout = 0;
	uपूर्णांक32_t lock_status = 0;
	पूर्णांक ret_val = QLA_SUCCESS;
	काष्ठा qla_hw_data *ha = vha->hw;

	जबतक (lock_status == 0) अणु
		lock_status = qla8044_rd_reg(ha, QLA8044_FLASH_LOCK);
		अगर (lock_status)
			अवरोध;

		अगर (++समयout >= QLA8044_FLASH_LOCK_TIMEOUT / 20) अणु
			lock_owner = qla8044_rd_reg(ha,
			    QLA8044_FLASH_LOCK_ID);
			ql_log(ql_log_warn, vha, 0xb113,
			    "%s: Simultaneous flash access by following ports, active port = %d: accessing port = %d",
			    __func__, ha->portnum, lock_owner);
			ret_val = QLA_FUNCTION_FAILED;
			अवरोध;
		पूर्ण
		msleep(20);
	पूर्ण
	qla8044_wr_reg(ha, QLA8044_FLASH_LOCK_ID, ha->portnum);
	वापस ret_val;
पूर्ण

अटल व्योम
qla8044_flash_unlock(scsi_qla_host_t *vha)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;

	/* Reading FLASH_UNLOCK रेजिस्टर unlocks the Flash */
	qla8044_wr_reg(ha, QLA8044_FLASH_LOCK_ID, 0xFF);
	qla8044_rd_reg(ha, QLA8044_FLASH_UNLOCK);
पूर्ण


अटल
व्योम qla8044_flash_lock_recovery(काष्ठा scsi_qla_host *vha)
अणु

	अगर (qla8044_flash_lock(vha)) अणु
		/* Someone अन्यथा is holding the lock. */
		ql_log(ql_log_warn, vha, 0xb120, "Resetting flash_lock\n");
	पूर्ण

	/*
	 * Either we got the lock, or someone
	 * अन्यथा died जबतक holding it.
	 * In either हाल, unlock.
	 */
	qla8044_flash_unlock(vha);
पूर्ण

/*
 * Address and length are byte address
 */
अटल पूर्णांक
qla8044_पढ़ो_flash_data(scsi_qla_host_t *vha,  uपूर्णांक8_t *p_data,
	uपूर्णांक32_t flash_addr, पूर्णांक u32_word_count)
अणु
	पूर्णांक i, ret_val = QLA_SUCCESS;
	uपूर्णांक32_t u32_word;

	अगर (qla8044_flash_lock(vha) != QLA_SUCCESS) अणु
		ret_val = QLA_FUNCTION_FAILED;
		जाओ निकास_lock_error;
	पूर्ण

	अगर (flash_addr & 0x03) अणु
		ql_log(ql_log_warn, vha, 0xb117,
		    "%s: Illegal addr = 0x%x\n", __func__, flash_addr);
		ret_val = QLA_FUNCTION_FAILED;
		जाओ निकास_flash_पढ़ो;
	पूर्ण

	क्रम (i = 0; i < u32_word_count; i++) अणु
		अगर (qla8044_wr_reg_indirect(vha, QLA8044_FLASH_सूचीECT_WINDOW,
		    (flash_addr & 0xFFFF0000))) अणु
			ql_log(ql_log_warn, vha, 0xb119,
			    "%s: failed to write addr 0x%x to "
			    "FLASH_DIRECT_WINDOW\n! ",
			    __func__, flash_addr);
			ret_val = QLA_FUNCTION_FAILED;
			जाओ निकास_flash_पढ़ो;
		पूर्ण

		ret_val = qla8044_rd_reg_indirect(vha,
		    QLA8044_FLASH_सूचीECT_DATA(flash_addr),
		    &u32_word);
		अगर (ret_val != QLA_SUCCESS) अणु
			ql_log(ql_log_warn, vha, 0xb08c,
			    "%s: failed to read addr 0x%x!\n",
			    __func__, flash_addr);
			जाओ निकास_flash_पढ़ो;
		पूर्ण

		*(uपूर्णांक32_t *)p_data = u32_word;
		p_data = p_data + 4;
		flash_addr = flash_addr + 4;
	पूर्ण

निकास_flash_पढ़ो:
	qla8044_flash_unlock(vha);

निकास_lock_error:
	वापस ret_val;
पूर्ण

/*
 * Address and length are byte address
 */
व्योम *
qla8044_पढ़ो_optrom_data(काष्ठा scsi_qla_host *vha, व्योम *buf,
	uपूर्णांक32_t offset, uपूर्णांक32_t length)
अणु
	scsi_block_requests(vha->host);
	अगर (qla8044_पढ़ो_flash_data(vha, buf, offset, length / 4)
	    != QLA_SUCCESS) अणु
		ql_log(ql_log_warn, vha,  0xb08d,
		    "%s: Failed to read from flash\n",
		    __func__);
	पूर्ण
	scsi_unblock_requests(vha->host);
	वापस buf;
पूर्ण

अटल अंतरभूत पूर्णांक
qla8044_need_reset(काष्ठा scsi_qla_host *vha)
अणु
	uपूर्णांक32_t drv_state, drv_active;
	पूर्णांक rval;
	काष्ठा qla_hw_data *ha = vha->hw;

	drv_active = qla8044_rd_direct(vha, QLA8044_CRB_DRV_ACTIVE_INDEX);
	drv_state = qla8044_rd_direct(vha, QLA8044_CRB_DRV_STATE_INDEX);

	rval = drv_state & (1 << ha->portnum);

	अगर (ha->flags.eeh_busy && drv_active)
		rval = 1;
	वापस rval;
पूर्ण

/*
 * qla8044_ग_लिखो_list - Write the value (p_entry->arg2) to address specअगरied
 * by p_entry->arg1 क्रम all entries in header with delay of p_hdr->delay between
 * entries.
 *
 * @vha : Poपूर्णांकer to adapter काष्ठाure
 * @p_hdr : reset_entry header क्रम WRITE_LIST opcode.
 *
 */
अटल व्योम
qla8044_ग_लिखो_list(काष्ठा scsi_qla_host *vha,
	काष्ठा qla8044_reset_entry_hdr *p_hdr)
अणु
	काष्ठा qla8044_entry *p_entry;
	uपूर्णांक32_t i;

	p_entry = (काष्ठा qla8044_entry *)((अक्षर *)p_hdr +
	    माप(काष्ठा qla8044_reset_entry_hdr));

	क्रम (i = 0; i < p_hdr->count; i++, p_entry++) अणु
		qla8044_wr_reg_indirect(vha, p_entry->arg1, p_entry->arg2);
		अगर (p_hdr->delay)
			udelay((uपूर्णांक32_t)(p_hdr->delay));
	पूर्ण
पूर्ण

/*
 * qla8044_पढ़ो_ग_लिखो_list - Read from address specअगरied by p_entry->arg1,
 * ग_लिखो value पढ़ो to address specअगरied by p_entry->arg2, क्रम all entries in
 * header with delay of p_hdr->delay between entries.
 *
 * @vha : Poपूर्णांकer to adapter काष्ठाure
 * @p_hdr : reset_entry header क्रम READ_WRITE_LIST opcode.
 *
 */
अटल व्योम
qla8044_पढ़ो_ग_लिखो_list(काष्ठा scsi_qla_host *vha,
	काष्ठा qla8044_reset_entry_hdr *p_hdr)
अणु
	काष्ठा qla8044_entry *p_entry;
	uपूर्णांक32_t i;

	p_entry = (काष्ठा qla8044_entry *)((अक्षर *)p_hdr +
	    माप(काष्ठा qla8044_reset_entry_hdr));

	क्रम (i = 0; i < p_hdr->count; i++, p_entry++) अणु
		qla8044_पढ़ो_ग_लिखो_crb_reg(vha, p_entry->arg1,
		    p_entry->arg2);
		अगर (p_hdr->delay)
			udelay((uपूर्णांक32_t)(p_hdr->delay));
	पूर्ण
पूर्ण

/*
 * qla8044_poll_reg - Poll the given CRB addr क्रम duration msecs till
 * value पढ़ो ANDed with test_mask is equal to test_result.
 *
 * @ha : Poपूर्णांकer to adapter काष्ठाure
 * @addr : CRB रेजिस्टर address
 * @duration : Poll क्रम total of "duration" msecs
 * @test_mask : Mask value पढ़ो with "test_mask"
 * @test_result : Compare (value&test_mask) with test_result.
 *
 * Return Value - QLA_SUCCESS/QLA_FUNCTION_FAILED
 */
अटल पूर्णांक
qla8044_poll_reg(काष्ठा scsi_qla_host *vha, uपूर्णांक32_t addr,
	पूर्णांक duration, uपूर्णांक32_t test_mask, uपूर्णांक32_t test_result)
अणु
	uपूर्णांक32_t value = 0;
	पूर्णांक समयout_error;
	uपूर्णांक8_t retries;
	पूर्णांक ret_val = QLA_SUCCESS;

	ret_val = qla8044_rd_reg_indirect(vha, addr, &value);
	अगर (ret_val == QLA_FUNCTION_FAILED) अणु
		समयout_error = 1;
		जाओ निकास_poll_reg;
	पूर्ण

	/* poll every 1/10 of the total duration */
	retries = duration/10;

	करो अणु
		अगर ((value & test_mask) != test_result) अणु
			समयout_error = 1;
			msleep(duration/10);
			ret_val = qla8044_rd_reg_indirect(vha, addr, &value);
			अगर (ret_val == QLA_FUNCTION_FAILED) अणु
				समयout_error = 1;
				जाओ निकास_poll_reg;
			पूर्ण
		पूर्ण अन्यथा अणु
			समयout_error = 0;
			अवरोध;
		पूर्ण
	पूर्ण जबतक (retries--);

निकास_poll_reg:
	अगर (समयout_error) अणु
		vha->reset_पंचांगplt.seq_error++;
		ql_log(ql_log_fatal, vha, 0xb090,
		    "%s: Poll Failed: 0x%08x 0x%08x 0x%08x\n",
		    __func__, value, test_mask, test_result);
	पूर्ण

	वापस समयout_error;
पूर्ण

/*
 * qla8044_poll_list - For all entries in the POLL_LIST header, poll पढ़ो CRB
 * रेजिस्टर specअगरied by p_entry->arg1 and compare (value AND test_mask) with
 * test_result to validate it. Wait क्रम p_hdr->delay between processing entries.
 *
 * @ha : Poपूर्णांकer to adapter काष्ठाure
 * @p_hdr : reset_entry header क्रम POLL_LIST opcode.
 *
 */
अटल व्योम
qla8044_poll_list(काष्ठा scsi_qla_host *vha,
	काष्ठा qla8044_reset_entry_hdr *p_hdr)
अणु
	दीर्घ delay;
	काष्ठा qla8044_entry *p_entry;
	काष्ठा qla8044_poll *p_poll;
	uपूर्णांक32_t i;
	uपूर्णांक32_t value;

	p_poll = (काष्ठा qla8044_poll *)
		((अक्षर *)p_hdr + माप(काष्ठा qla8044_reset_entry_hdr));

	/* Entries start after 8 byte qla8044_poll, poll header contains
	 * the test_mask, test_value.
	 */
	p_entry = (काष्ठा qla8044_entry *)((अक्षर *)p_poll +
	    माप(काष्ठा qla8044_poll));

	delay = (दीर्घ)p_hdr->delay;

	अगर (!delay) अणु
		क्रम (i = 0; i < p_hdr->count; i++, p_entry++)
			qla8044_poll_reg(vha, p_entry->arg1,
			    delay, p_poll->test_mask, p_poll->test_value);
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < p_hdr->count; i++, p_entry++) अणु
			अगर (delay) अणु
				अगर (qla8044_poll_reg(vha,
				    p_entry->arg1, delay,
				    p_poll->test_mask,
				    p_poll->test_value)) अणु
					/*If
					* (data_पढ़ो&test_mask != test_value)
					* पढ़ो TIMEOUT_ADDR (arg1) and
					* ADDR (arg2) रेजिस्टरs
					*/
					qla8044_rd_reg_indirect(vha,
					    p_entry->arg1, &value);
					qla8044_rd_reg_indirect(vha,
					    p_entry->arg2, &value);
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

/*
 * qla8044_poll_ग_लिखो_list - Write dr_value, ar_value to dr_addr/ar_addr,
 * पढ़ो ar_addr, अगर (value& test_mask != test_mask) re-पढ़ो till समयout
 * expires.
 *
 * @vha : Poपूर्णांकer to adapter काष्ठाure
 * @p_hdr : reset entry header क्रम POLL_WRITE_LIST opcode.
 *
 */
अटल व्योम
qla8044_poll_ग_लिखो_list(काष्ठा scsi_qla_host *vha,
	काष्ठा qla8044_reset_entry_hdr *p_hdr)
अणु
	दीर्घ delay;
	काष्ठा qla8044_quad_entry *p_entry;
	काष्ठा qla8044_poll *p_poll;
	uपूर्णांक32_t i;

	p_poll = (काष्ठा qla8044_poll *)((अक्षर *)p_hdr +
	    माप(काष्ठा qla8044_reset_entry_hdr));

	p_entry = (काष्ठा qla8044_quad_entry *)((अक्षर *)p_poll +
	    माप(काष्ठा qla8044_poll));

	delay = (दीर्घ)p_hdr->delay;

	क्रम (i = 0; i < p_hdr->count; i++, p_entry++) अणु
		qla8044_wr_reg_indirect(vha,
		    p_entry->dr_addr, p_entry->dr_value);
		qla8044_wr_reg_indirect(vha,
		    p_entry->ar_addr, p_entry->ar_value);
		अगर (delay) अणु
			अगर (qla8044_poll_reg(vha,
			    p_entry->ar_addr, delay,
			    p_poll->test_mask,
			    p_poll->test_value)) अणु
				ql_dbg(ql_dbg_p3p, vha, 0xb091,
				    "%s: Timeout Error: poll list, ",
				    __func__);
				ql_dbg(ql_dbg_p3p, vha, 0xb092,
				    "item_num %d, entry_num %d\n", i,
				    vha->reset_पंचांगplt.seq_index);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

/*
 * qla8044_पढ़ो_modअगरy_ग_लिखो - Read value from p_entry->arg1, modअगरy the
 * value, ग_लिखो value to p_entry->arg2. Process entries with p_hdr->delay
 * between entries.
 *
 * @vha : Poपूर्णांकer to adapter काष्ठाure
 * @p_hdr : header with shअगरt/or/xor values.
 *
 */
अटल व्योम
qla8044_पढ़ो_modअगरy_ग_लिखो(काष्ठा scsi_qla_host *vha,
	काष्ठा qla8044_reset_entry_hdr *p_hdr)
अणु
	काष्ठा qla8044_entry *p_entry;
	काष्ठा qla8044_rmw *p_rmw_hdr;
	uपूर्णांक32_t i;

	p_rmw_hdr = (काष्ठा qla8044_rmw *)((अक्षर *)p_hdr +
	    माप(काष्ठा qla8044_reset_entry_hdr));

	p_entry = (काष्ठा qla8044_entry *)((अक्षर *)p_rmw_hdr +
	    माप(काष्ठा qla8044_rmw));

	क्रम (i = 0; i < p_hdr->count; i++, p_entry++) अणु
		qla8044_rmw_crb_reg(vha, p_entry->arg1,
		    p_entry->arg2, p_rmw_hdr);
		अगर (p_hdr->delay)
			udelay((uपूर्णांक32_t)(p_hdr->delay));
	पूर्ण
पूर्ण

/*
 * qla8044_छोड़ो - Wait क्रम p_hdr->delay msecs, called between processing
 * two entries of a sequence.
 *
 * @vha : Poपूर्णांकer to adapter काष्ठाure
 * @p_hdr : Common reset entry header.
 *
 */
अटल
व्योम qla8044_छोड़ो(काष्ठा scsi_qla_host *vha,
	काष्ठा qla8044_reset_entry_hdr *p_hdr)
अणु
	अगर (p_hdr->delay)
		mdelay((uपूर्णांक32_t)((दीर्घ)p_hdr->delay));
पूर्ण

/*
 * qla8044_ढाँचा_end - Indicates end of reset sequence processing.
 *
 * @vha : Poपूर्णांकer to adapter काष्ठाure
 * @p_hdr : Common reset entry header.
 *
 */
अटल व्योम
qla8044_ढाँचा_end(काष्ठा scsi_qla_host *vha,
	काष्ठा qla8044_reset_entry_hdr *p_hdr)
अणु
	vha->reset_पंचांगplt.ढाँचा_end = 1;

	अगर (vha->reset_पंचांगplt.seq_error == 0) अणु
		ql_dbg(ql_dbg_p3p, vha, 0xb093,
		    "%s: Reset sequence completed SUCCESSFULLY.\n", __func__);
	पूर्ण अन्यथा अणु
		ql_log(ql_log_fatal, vha, 0xb094,
		    "%s: Reset sequence completed with some timeout "
		    "errors.\n", __func__);
	पूर्ण
पूर्ण

/*
 * qla8044_poll_पढ़ो_list - Write ar_value to ar_addr रेजिस्टर, पढ़ो ar_addr,
 * अगर (value & test_mask != test_value) re-पढ़ो till समयout value expires,
 * पढ़ो dr_addr रेजिस्टर and assign to reset_पंचांगplt.array.
 *
 * @vha : Poपूर्णांकer to adapter काष्ठाure
 * @p_hdr : Common reset entry header.
 *
 */
अटल व्योम
qla8044_poll_पढ़ो_list(काष्ठा scsi_qla_host *vha,
	काष्ठा qla8044_reset_entry_hdr *p_hdr)
अणु
	दीर्घ delay;
	पूर्णांक index;
	काष्ठा qla8044_quad_entry *p_entry;
	काष्ठा qla8044_poll *p_poll;
	uपूर्णांक32_t i;
	uपूर्णांक32_t value;

	p_poll = (काष्ठा qla8044_poll *)
		((अक्षर *)p_hdr + माप(काष्ठा qla8044_reset_entry_hdr));

	p_entry = (काष्ठा qla8044_quad_entry *)
		((अक्षर *)p_poll + माप(काष्ठा qla8044_poll));

	delay = (दीर्घ)p_hdr->delay;

	क्रम (i = 0; i < p_hdr->count; i++, p_entry++) अणु
		qla8044_wr_reg_indirect(vha, p_entry->ar_addr,
		    p_entry->ar_value);
		अगर (delay) अणु
			अगर (qla8044_poll_reg(vha, p_entry->ar_addr, delay,
			    p_poll->test_mask, p_poll->test_value)) अणु
				ql_dbg(ql_dbg_p3p, vha, 0xb095,
				    "%s: Timeout Error: poll "
				    "list, ", __func__);
				ql_dbg(ql_dbg_p3p, vha, 0xb096,
				    "Item_num %d, "
				    "entry_num %d\n", i,
				    vha->reset_पंचांगplt.seq_index);
			पूर्ण अन्यथा अणु
				index = vha->reset_पंचांगplt.array_index;
				qla8044_rd_reg_indirect(vha,
				    p_entry->dr_addr, &value);
				vha->reset_पंचांगplt.array[index++] = value;
				अगर (index == QLA8044_MAX_RESET_SEQ_ENTRIES)
					vha->reset_पंचांगplt.array_index = 1;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

/*
 * qla8031_process_reset_ढाँचा - Process all entries in reset ढाँचा
 * till entry with SEQ_END opcode, which indicates end of the reset ढाँचा
 * processing. Each entry has a Reset Entry header, entry opcode/command, with
 * size of the entry, number of entries in sub-sequence and delay in microsecs
 * or समयout in millisecs.
 *
 * @ha : Poपूर्णांकer to adapter काष्ठाure
 * @p_buff : Common reset entry header.
 *
 */
अटल व्योम
qla8044_process_reset_ढाँचा(काष्ठा scsi_qla_host *vha,
	अक्षर *p_buff)
अणु
	पूर्णांक index, entries;
	काष्ठा qla8044_reset_entry_hdr *p_hdr;
	अक्षर *p_entry = p_buff;

	vha->reset_पंचांगplt.seq_end = 0;
	vha->reset_पंचांगplt.ढाँचा_end = 0;
	entries = vha->reset_पंचांगplt.hdr->entries;
	index = vha->reset_पंचांगplt.seq_index;

	क्रम (; (!vha->reset_पंचांगplt.seq_end) && (index  < entries); index++) अणु
		p_hdr = (काष्ठा qla8044_reset_entry_hdr *)p_entry;
		चयन (p_hdr->cmd) अणु
		हाल OPCODE_NOP:
			अवरोध;
		हाल OPCODE_WRITE_LIST:
			qla8044_ग_लिखो_list(vha, p_hdr);
			अवरोध;
		हाल OPCODE_READ_WRITE_LIST:
			qla8044_पढ़ो_ग_लिखो_list(vha, p_hdr);
			अवरोध;
		हाल OPCODE_POLL_LIST:
			qla8044_poll_list(vha, p_hdr);
			अवरोध;
		हाल OPCODE_POLL_WRITE_LIST:
			qla8044_poll_ग_लिखो_list(vha, p_hdr);
			अवरोध;
		हाल OPCODE_READ_MODIFY_WRITE:
			qla8044_पढ़ो_modअगरy_ग_लिखो(vha, p_hdr);
			अवरोध;
		हाल OPCODE_SEQ_PAUSE:
			qla8044_छोड़ो(vha, p_hdr);
			अवरोध;
		हाल OPCODE_SEQ_END:
			vha->reset_पंचांगplt.seq_end = 1;
			अवरोध;
		हाल OPCODE_TMPL_END:
			qla8044_ढाँचा_end(vha, p_hdr);
			अवरोध;
		हाल OPCODE_POLL_READ_LIST:
			qla8044_poll_पढ़ो_list(vha, p_hdr);
			अवरोध;
		शेष:
			ql_log(ql_log_fatal, vha, 0xb097,
			    "%s: Unknown command ==> 0x%04x on "
			    "entry = %d\n", __func__, p_hdr->cmd, index);
			अवरोध;
		पूर्ण
		/*
		 *Set poपूर्णांकer to next entry in the sequence.
		*/
		p_entry += p_hdr->size;
	पूर्ण
	vha->reset_पंचांगplt.seq_index = index;
पूर्ण

अटल व्योम
qla8044_process_init_seq(काष्ठा scsi_qla_host *vha)
अणु
	qla8044_process_reset_ढाँचा(vha,
	    vha->reset_पंचांगplt.init_offset);
	अगर (vha->reset_पंचांगplt.seq_end != 1)
		ql_log(ql_log_fatal, vha, 0xb098,
		    "%s: Abrupt INIT Sub-Sequence end.\n",
		    __func__);
पूर्ण

अटल व्योम
qla8044_process_stop_seq(काष्ठा scsi_qla_host *vha)
अणु
	vha->reset_पंचांगplt.seq_index = 0;
	qla8044_process_reset_ढाँचा(vha, vha->reset_पंचांगplt.stop_offset);
	अगर (vha->reset_पंचांगplt.seq_end != 1)
		ql_log(ql_log_fatal, vha, 0xb099,
		    "%s: Abrupt STOP Sub-Sequence end.\n", __func__);
पूर्ण

अटल व्योम
qla8044_process_start_seq(काष्ठा scsi_qla_host *vha)
अणु
	qla8044_process_reset_ढाँचा(vha, vha->reset_पंचांगplt.start_offset);
	अगर (vha->reset_पंचांगplt.ढाँचा_end != 1)
		ql_log(ql_log_fatal, vha, 0xb09a,
		    "%s: Abrupt START Sub-Sequence end.\n",
		    __func__);
पूर्ण

अटल पूर्णांक
qla8044_lockless_flash_पढ़ो_u32(काष्ठा scsi_qla_host *vha,
	uपूर्णांक32_t flash_addr, uपूर्णांक8_t *p_data, पूर्णांक u32_word_count)
अणु
	uपूर्णांक32_t i;
	uपूर्णांक32_t u32_word;
	uपूर्णांक32_t flash_offset;
	uपूर्णांक32_t addr = flash_addr;
	पूर्णांक ret_val = QLA_SUCCESS;

	flash_offset = addr & (QLA8044_FLASH_SECTOR_SIZE - 1);

	अगर (addr & 0x3) अणु
		ql_log(ql_log_fatal, vha, 0xb09b, "%s: Illegal addr = 0x%x\n",
		    __func__, addr);
		ret_val = QLA_FUNCTION_FAILED;
		जाओ निकास_lockless_पढ़ो;
	पूर्ण

	ret_val = qla8044_wr_reg_indirect(vha,
	    QLA8044_FLASH_सूचीECT_WINDOW, (addr));

	अगर (ret_val != QLA_SUCCESS) अणु
		ql_log(ql_log_fatal, vha, 0xb09c,
		    "%s: failed to write addr 0x%x to FLASH_DIRECT_WINDOW!\n",
		    __func__, addr);
		जाओ निकास_lockless_पढ़ो;
	पूर्ण

	/* Check अगर data is spपढ़ो across multiple sectors  */
	अगर ((flash_offset + (u32_word_count * माप(uपूर्णांक32_t))) >
	    (QLA8044_FLASH_SECTOR_SIZE - 1)) अणु
		/* Multi sector पढ़ो */
		क्रम (i = 0; i < u32_word_count; i++) अणु
			ret_val = qla8044_rd_reg_indirect(vha,
			    QLA8044_FLASH_सूचीECT_DATA(addr), &u32_word);
			अगर (ret_val != QLA_SUCCESS) अणु
				ql_log(ql_log_fatal, vha, 0xb09d,
				    "%s: failed to read addr 0x%x!\n",
				    __func__, addr);
				जाओ निकास_lockless_पढ़ो;
			पूर्ण
			*(uपूर्णांक32_t *)p_data  = u32_word;
			p_data = p_data + 4;
			addr = addr + 4;
			flash_offset = flash_offset + 4;
			अगर (flash_offset > (QLA8044_FLASH_SECTOR_SIZE - 1)) अणु
				/* This ग_लिखो is needed once क्रम each sector */
				ret_val = qla8044_wr_reg_indirect(vha,
				    QLA8044_FLASH_सूचीECT_WINDOW, (addr));
				अगर (ret_val != QLA_SUCCESS) अणु
					ql_log(ql_log_fatal, vha, 0xb09f,
					    "%s: failed to write addr "
					    "0x%x to FLASH_DIRECT_WINDOW!\n",
					    __func__, addr);
					जाओ निकास_lockless_पढ़ो;
				पूर्ण
				flash_offset = 0;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Single sector पढ़ो */
		क्रम (i = 0; i < u32_word_count; i++) अणु
			ret_val = qla8044_rd_reg_indirect(vha,
			    QLA8044_FLASH_सूचीECT_DATA(addr), &u32_word);
			अगर (ret_val != QLA_SUCCESS) अणु
				ql_log(ql_log_fatal, vha, 0xb0a0,
				    "%s: failed to read addr 0x%x!\n",
				    __func__, addr);
				जाओ निकास_lockless_पढ़ो;
			पूर्ण
			*(uपूर्णांक32_t *)p_data = u32_word;
			p_data = p_data + 4;
			addr = addr + 4;
		पूर्ण
	पूर्ण

निकास_lockless_पढ़ो:
	वापस ret_val;
पूर्ण

/*
 * qla8044_ms_mem_ग_लिखो_128b - Writes data to MS/off-chip memory
 *
 * @vha : Poपूर्णांकer to adapter काष्ठाure
 * addr : Flash address to ग_लिखो to
 * data : Data to be written
 * count : word_count to be written
 *
 * Return Value - QLA_SUCCESS/QLA_FUNCTION_FAILED
 */
अटल पूर्णांक
qla8044_ms_mem_ग_लिखो_128b(काष्ठा scsi_qla_host *vha,
	uपूर्णांक64_t addr, uपूर्णांक32_t *data, uपूर्णांक32_t count)
अणु
	पूर्णांक i, j, ret_val = QLA_SUCCESS;
	uपूर्णांक32_t agt_ctrl;
	अचिन्हित दीर्घ flags;
	काष्ठा qla_hw_data *ha = vha->hw;

	/* Only 128-bit aligned access */
	अगर (addr & 0xF) अणु
		ret_val = QLA_FUNCTION_FAILED;
		जाओ निकास_ms_mem_ग_लिखो;
	पूर्ण
	ग_लिखो_lock_irqsave(&ha->hw_lock, flags);

	/* Write address */
	ret_val = qla8044_wr_reg_indirect(vha, MD_MIU_TEST_AGT_ADDR_HI, 0);
	अगर (ret_val == QLA_FUNCTION_FAILED) अणु
		ql_log(ql_log_fatal, vha, 0xb0a1,
		    "%s: write to AGT_ADDR_HI failed!\n", __func__);
		जाओ निकास_ms_mem_ग_लिखो_unlock;
	पूर्ण

	क्रम (i = 0; i < count; i++, addr += 16) अणु
		अगर (!((addr_in_range(addr, QLA8044_ADDR_QDR_NET,
		    QLA8044_ADDR_QDR_NET_MAX)) ||
		    (addr_in_range(addr, QLA8044_ADDR_DDR_NET,
			QLA8044_ADDR_DDR_NET_MAX)))) अणु
			ret_val = QLA_FUNCTION_FAILED;
			जाओ निकास_ms_mem_ग_लिखो_unlock;
		पूर्ण

		ret_val = qla8044_wr_reg_indirect(vha,
		    MD_MIU_TEST_AGT_ADDR_LO, addr);

		/* Write data */
		ret_val += qla8044_wr_reg_indirect(vha,
		    MD_MIU_TEST_AGT_WRDATA_LO, *data++);
		ret_val += qla8044_wr_reg_indirect(vha,
		    MD_MIU_TEST_AGT_WRDATA_HI, *data++);
		ret_val += qla8044_wr_reg_indirect(vha,
		    MD_MIU_TEST_AGT_WRDATA_ULO, *data++);
		ret_val += qla8044_wr_reg_indirect(vha,
		    MD_MIU_TEST_AGT_WRDATA_UHI, *data++);
		अगर (ret_val == QLA_FUNCTION_FAILED) अणु
			ql_log(ql_log_fatal, vha, 0xb0a2,
			    "%s: write to AGT_WRDATA failed!\n",
			    __func__);
			जाओ निकास_ms_mem_ग_लिखो_unlock;
		पूर्ण

		/* Check ग_लिखो status */
		ret_val = qla8044_wr_reg_indirect(vha, MD_MIU_TEST_AGT_CTRL,
		    MIU_TA_CTL_WRITE_ENABLE);
		ret_val += qla8044_wr_reg_indirect(vha, MD_MIU_TEST_AGT_CTRL,
		    MIU_TA_CTL_WRITE_START);
		अगर (ret_val == QLA_FUNCTION_FAILED) अणु
			ql_log(ql_log_fatal, vha, 0xb0a3,
			    "%s: write to AGT_CTRL failed!\n", __func__);
			जाओ निकास_ms_mem_ग_लिखो_unlock;
		पूर्ण

		क्रम (j = 0; j < MAX_CTL_CHECK; j++) अणु
			ret_val = qla8044_rd_reg_indirect(vha,
			    MD_MIU_TEST_AGT_CTRL, &agt_ctrl);
			अगर (ret_val == QLA_FUNCTION_FAILED) अणु
				ql_log(ql_log_fatal, vha, 0xb0a4,
				    "%s: failed to read "
				    "MD_MIU_TEST_AGT_CTRL!\n", __func__);
				जाओ निकास_ms_mem_ग_लिखो_unlock;
			पूर्ण
			अगर ((agt_ctrl & MIU_TA_CTL_BUSY) == 0)
				अवरोध;
		पूर्ण

		/* Status check failed */
		अगर (j >= MAX_CTL_CHECK) अणु
			ql_log(ql_log_fatal, vha, 0xb0a5,
			    "%s: MS memory write failed!\n",
			   __func__);
			ret_val = QLA_FUNCTION_FAILED;
			जाओ निकास_ms_mem_ग_लिखो_unlock;
		पूर्ण
	पूर्ण

निकास_ms_mem_ग_लिखो_unlock:
	ग_लिखो_unlock_irqrestore(&ha->hw_lock, flags);

निकास_ms_mem_ग_लिखो:
	वापस ret_val;
पूर्ण

अटल पूर्णांक
qla8044_copy_bootloader(काष्ठा scsi_qla_host *vha)
अणु
	uपूर्णांक8_t *p_cache;
	uपूर्णांक32_t src, count, size;
	uपूर्णांक64_t dest;
	पूर्णांक ret_val = QLA_SUCCESS;
	काष्ठा qla_hw_data *ha = vha->hw;

	src = QLA8044_BOOTLOADER_FLASH_ADDR;
	dest = qla8044_rd_reg(ha, QLA8044_BOOTLOADER_ADDR);
	size = qla8044_rd_reg(ha, QLA8044_BOOTLOADER_SIZE);

	/* 128 bit alignment check */
	अगर (size & 0xF)
		size = (size + 16) & ~0xF;

	/* 16 byte count */
	count = size/16;

	p_cache = vदो_स्मृति(size);
	अगर (p_cache == शून्य) अणु
		ql_log(ql_log_fatal, vha, 0xb0a6,
		    "%s: Failed to allocate memory for "
		    "boot loader cache\n", __func__);
		ret_val = QLA_FUNCTION_FAILED;
		जाओ निकास_copy_bootloader;
	पूर्ण

	ret_val = qla8044_lockless_flash_पढ़ो_u32(vha, src,
	    p_cache, size/माप(uपूर्णांक32_t));
	अगर (ret_val == QLA_FUNCTION_FAILED) अणु
		ql_log(ql_log_fatal, vha, 0xb0a7,
		    "%s: Error reading F/W from flash!!!\n", __func__);
		जाओ निकास_copy_error;
	पूर्ण
	ql_dbg(ql_dbg_p3p, vha, 0xb0a8, "%s: Read F/W from flash!\n",
	    __func__);

	/* 128 bit/16 byte ग_लिखो to MS memory */
	ret_val = qla8044_ms_mem_ग_लिखो_128b(vha, dest,
	    (uपूर्णांक32_t *)p_cache, count);
	अगर (ret_val == QLA_FUNCTION_FAILED) अणु
		ql_log(ql_log_fatal, vha, 0xb0a9,
		    "%s: Error writing F/W to MS !!!\n", __func__);
		जाओ निकास_copy_error;
	पूर्ण
	ql_dbg(ql_dbg_p3p, vha, 0xb0aa,
	    "%s: Wrote F/W (size %d) to MS !!!\n",
	    __func__, size);

निकास_copy_error:
	vमुक्त(p_cache);

निकास_copy_bootloader:
	वापस ret_val;
पूर्ण

अटल पूर्णांक
qla8044_restart(काष्ठा scsi_qla_host *vha)
अणु
	पूर्णांक ret_val = QLA_SUCCESS;
	काष्ठा qla_hw_data *ha = vha->hw;

	qla8044_process_stop_seq(vha);

	/* Collect minidump */
	अगर (ql2xmdenable)
		qla8044_get_minidump(vha);
	अन्यथा
		ql_log(ql_log_fatal, vha, 0xb14c,
		    "Minidump disabled.\n");

	qla8044_process_init_seq(vha);

	अगर (qla8044_copy_bootloader(vha)) अणु
		ql_log(ql_log_fatal, vha, 0xb0ab,
		    "%s: Copy bootloader, firmware restart failed!\n",
		    __func__);
		ret_val = QLA_FUNCTION_FAILED;
		जाओ निकास_restart;
	पूर्ण

	/*
	 *  Loads F/W from flash
	 */
	qla8044_wr_reg(ha, QLA8044_FW_IMAGE_VALID, QLA8044_BOOT_FROM_FLASH);

	qla8044_process_start_seq(vha);

निकास_restart:
	वापस ret_val;
पूर्ण

/*
 * qla8044_check_cmd_peg_status - Check peg status to see अगर Peg is
 * initialized.
 *
 * @ha : Poपूर्णांकer to adapter काष्ठाure
 *
 * Return Value - QLA_SUCCESS/QLA_FUNCTION_FAILED
 */
अटल पूर्णांक
qla8044_check_cmd_peg_status(काष्ठा scsi_qla_host *vha)
अणु
	uपूर्णांक32_t val, ret_val = QLA_FUNCTION_FAILED;
	पूर्णांक retries = CRB_CMDPEG_CHECK_RETRY_COUNT;
	काष्ठा qla_hw_data *ha = vha->hw;

	करो अणु
		val = qla8044_rd_reg(ha, QLA8044_CMDPEG_STATE);
		अगर (val == PHAN_INITIALIZE_COMPLETE) अणु
			ql_dbg(ql_dbg_p3p, vha, 0xb0ac,
			    "%s: Command Peg initialization "
			    "complete! state=0x%x\n", __func__, val);
			ret_val = QLA_SUCCESS;
			अवरोध;
		पूर्ण
		msleep(CRB_CMDPEG_CHECK_DELAY);
	पूर्ण जबतक (--retries);

	वापस ret_val;
पूर्ण

अटल पूर्णांक
qla8044_start_firmware(काष्ठा scsi_qla_host *vha)
अणु
	पूर्णांक ret_val = QLA_SUCCESS;

	अगर (qla8044_restart(vha)) अणु
		ql_log(ql_log_fatal, vha, 0xb0ad,
		    "%s: Restart Error!!!, Need Reset!!!\n",
		    __func__);
		ret_val = QLA_FUNCTION_FAILED;
		जाओ निकास_start_fw;
	पूर्ण अन्यथा
		ql_dbg(ql_dbg_p3p, vha, 0xb0af,
		    "%s: Restart done!\n", __func__);

	ret_val = qla8044_check_cmd_peg_status(vha);
	अगर (ret_val) अणु
		ql_log(ql_log_fatal, vha, 0xb0b0,
		    "%s: Peg not initialized!\n", __func__);
		ret_val = QLA_FUNCTION_FAILED;
	पूर्ण

निकास_start_fw:
	वापस ret_val;
पूर्ण

व्योम
qla8044_clear_drv_active(काष्ठा qla_hw_data *ha)
अणु
	uपूर्णांक32_t drv_active;
	काष्ठा scsi_qla_host *vha = pci_get_drvdata(ha->pdev);

	drv_active = qla8044_rd_direct(vha, QLA8044_CRB_DRV_ACTIVE_INDEX);
	drv_active &= ~(1 << (ha->portnum));

	ql_log(ql_log_info, vha, 0xb0b1,
	    "%s(%ld): drv_active: 0x%08x\n",
	    __func__, vha->host_no, drv_active);

	qla8044_wr_direct(vha, QLA8044_CRB_DRV_ACTIVE_INDEX, drv_active);
पूर्ण

/*
 * qla8044_device_bootstrap - Initialize device, set DEV_READY, start fw
 * @ha: poपूर्णांकer to adapter काष्ठाure
 *
 * Note: IDC lock must be held upon entry
 **/
अटल पूर्णांक
qla8044_device_bootstrap(काष्ठा scsi_qla_host *vha)
अणु
	पूर्णांक rval = QLA_FUNCTION_FAILED;
	पूर्णांक i;
	uपूर्णांक32_t old_count = 0, count = 0;
	पूर्णांक need_reset = 0;
	uपूर्णांक32_t idc_ctrl;
	काष्ठा qla_hw_data *ha = vha->hw;

	need_reset = qla8044_need_reset(vha);

	अगर (!need_reset) अणु
		old_count = qla8044_rd_direct(vha,
		    QLA8044_PEG_ALIVE_COUNTER_INDEX);

		क्रम (i = 0; i < 10; i++) अणु
			msleep(200);

			count = qla8044_rd_direct(vha,
			    QLA8044_PEG_ALIVE_COUNTER_INDEX);
			अगर (count != old_count) अणु
				rval = QLA_SUCCESS;
				जाओ dev_पढ़ोy;
			पूर्ण
		पूर्ण
		qla8044_flash_lock_recovery(vha);
	पूर्ण अन्यथा अणु
		/* We are trying to perक्रमm a recovery here. */
		अगर (ha->flags.isp82xx_fw_hung)
			qla8044_flash_lock_recovery(vha);
	पूर्ण

	/* set to DEV_INITIALIZING */
	ql_log(ql_log_info, vha, 0xb0b2,
	    "%s: HW State: INITIALIZING\n", __func__);
	qla8044_wr_direct(vha, QLA8044_CRB_DEV_STATE_INDEX,
	    QLA8XXX_DEV_INITIALIZING);

	qla8044_idc_unlock(ha);
	rval = qla8044_start_firmware(vha);
	qla8044_idc_lock(ha);

	अगर (rval != QLA_SUCCESS) अणु
		ql_log(ql_log_info, vha, 0xb0b3,
		     "%s: HW State: FAILED\n", __func__);
		qla8044_clear_drv_active(ha);
		qla8044_wr_direct(vha, QLA8044_CRB_DEV_STATE_INDEX,
		    QLA8XXX_DEV_FAILED);
		वापस rval;
	पूर्ण

	/* For ISP8044, If IDC_CTRL GRACEFUL_RESET_BIT1 is set , reset it after
	 * device goes to INIT state. */
	idc_ctrl = qla8044_rd_reg(ha, QLA8044_IDC_DRV_CTRL);
	अगर (idc_ctrl & GRACEFUL_RESET_BIT1) अणु
		qla8044_wr_reg(ha, QLA8044_IDC_DRV_CTRL,
		    (idc_ctrl & ~GRACEFUL_RESET_BIT1));
		ha->fw_dumped = false;
	पूर्ण

dev_पढ़ोy:
	ql_log(ql_log_info, vha, 0xb0b4,
	    "%s: HW State: READY\n", __func__);
	qla8044_wr_direct(vha, QLA8044_CRB_DEV_STATE_INDEX, QLA8XXX_DEV_READY);

	वापस rval;
पूर्ण

/*-------------------------Reset Sequence Functions-----------------------*/
अटल व्योम
qla8044_dump_reset_seq_hdr(काष्ठा scsi_qla_host *vha)
अणु
	u8 *phdr;

	अगर (!vha->reset_पंचांगplt.buff) अणु
		ql_log(ql_log_fatal, vha, 0xb0b5,
		    "%s: Error Invalid reset_seq_template\n", __func__);
		वापस;
	पूर्ण

	phdr = vha->reset_पंचांगplt.buff;
	ql_dbg(ql_dbg_p3p, vha, 0xb0b6,
	    "Reset Template :\n\t0x%X 0x%X 0x%X 0x%X"
	    "0x%X 0x%X 0x%X 0x%X 0x%X 0x%X\n"
	    "\t0x%X 0x%X 0x%X 0x%X 0x%X 0x%X\n\n",
	    *phdr, *(phdr+1), *(phdr+2), *(phdr+3), *(phdr+4),
	    *(phdr+5), *(phdr+6), *(phdr+7), *(phdr + 8),
	    *(phdr+9), *(phdr+10), *(phdr+11), *(phdr+12),
	    *(phdr+13), *(phdr+14), *(phdr+15));
पूर्ण

/*
 * qla8044_reset_seq_checksum_test - Validate Reset Sequence ढाँचा.
 *
 * @ha : Poपूर्णांकer to adapter काष्ठाure
 *
 * Return Value - QLA_SUCCESS/QLA_FUNCTION_FAILED
 */
अटल पूर्णांक
qla8044_reset_seq_checksum_test(काष्ठा scsi_qla_host *vha)
अणु
	uपूर्णांक32_t sum =  0;
	uपूर्णांक16_t *buff = (uपूर्णांक16_t *)vha->reset_पंचांगplt.buff;
	पूर्णांक u16_count =  vha->reset_पंचांगplt.hdr->size / माप(uपूर्णांक16_t);

	जबतक (u16_count-- > 0)
		sum += *buff++;

	जबतक (sum >> 16)
		sum = (sum & 0xFFFF) +  (sum >> 16);

	/* checksum of 0 indicates a valid ढाँचा */
	अगर (~sum) अणु
		वापस QLA_SUCCESS;
	पूर्ण अन्यथा अणु
		ql_log(ql_log_fatal, vha, 0xb0b7,
		    "%s: Reset seq checksum failed\n", __func__);
		वापस QLA_FUNCTION_FAILED;
	पूर्ण
पूर्ण

/*
 * qla8044_पढ़ो_reset_ढाँचा - Read Reset Template from Flash, validate
 * the ढाँचा and store offsets of stop/start/init offsets in ha->reset_पंचांगplt.
 *
 * @ha : Poपूर्णांकer to adapter काष्ठाure
 */
व्योम
qla8044_पढ़ो_reset_ढाँचा(काष्ठा scsi_qla_host *vha)
अणु
	uपूर्णांक8_t *p_buff;
	uपूर्णांक32_t addr, पंचांगplt_hdr_def_size, पंचांगplt_hdr_size;

	vha->reset_पंचांगplt.seq_error = 0;
	vha->reset_पंचांगplt.buff = vदो_स्मृति(QLA8044_RESTART_TEMPLATE_SIZE);
	अगर (vha->reset_पंचांगplt.buff == शून्य) अणु
		ql_log(ql_log_fatal, vha, 0xb0b8,
		    "%s: Failed to allocate reset template resources\n",
		    __func__);
		जाओ निकास_पढ़ो_reset_ढाँचा;
	पूर्ण

	p_buff = vha->reset_पंचांगplt.buff;
	addr = QLA8044_RESET_TEMPLATE_ADDR;

	पंचांगplt_hdr_def_size =
	    माप(काष्ठा qla8044_reset_ढाँचा_hdr) / माप(uपूर्णांक32_t);

	ql_dbg(ql_dbg_p3p, vha, 0xb0b9,
	    "%s: Read template hdr size %d from Flash\n",
	    __func__, पंचांगplt_hdr_def_size);

	/* Copy ढाँचा header from flash */
	अगर (qla8044_पढ़ो_flash_data(vha, p_buff, addr, पंचांगplt_hdr_def_size)) अणु
		ql_log(ql_log_fatal, vha, 0xb0ba,
		    "%s: Failed to read reset template\n", __func__);
		जाओ निकास_पढ़ो_ढाँचा_error;
	पूर्ण

	vha->reset_पंचांगplt.hdr =
	 (काष्ठा qla8044_reset_ढाँचा_hdr *) vha->reset_पंचांगplt.buff;

	/* Validate the ढाँचा header size and signature */
	पंचांगplt_hdr_size = vha->reset_पंचांगplt.hdr->hdr_size/माप(uपूर्णांक32_t);
	अगर ((पंचांगplt_hdr_size != पंचांगplt_hdr_def_size) ||
	    (vha->reset_पंचांगplt.hdr->signature != RESET_TMPLT_HDR_SIGNATURE)) अणु
		ql_log(ql_log_fatal, vha, 0xb0bb,
		    "%s: Template Header size invalid %d "
		    "tmplt_hdr_def_size %d!!!\n", __func__,
		    पंचांगplt_hdr_size, पंचांगplt_hdr_def_size);
		जाओ निकास_पढ़ो_ढाँचा_error;
	पूर्ण

	addr = QLA8044_RESET_TEMPLATE_ADDR + vha->reset_पंचांगplt.hdr->hdr_size;
	p_buff = vha->reset_पंचांगplt.buff + vha->reset_पंचांगplt.hdr->hdr_size;
	पंचांगplt_hdr_def_size = (vha->reset_पंचांगplt.hdr->size -
	    vha->reset_पंचांगplt.hdr->hdr_size)/माप(uपूर्णांक32_t);

	ql_dbg(ql_dbg_p3p, vha, 0xb0bc,
	    "%s: Read rest of the template size %d\n",
	    __func__, vha->reset_पंचांगplt.hdr->size);

	/* Copy rest of the ढाँचा */
	अगर (qla8044_पढ़ो_flash_data(vha, p_buff, addr, पंचांगplt_hdr_def_size)) अणु
		ql_log(ql_log_fatal, vha, 0xb0bd,
		    "%s: Failed to read reset template\n", __func__);
		जाओ निकास_पढ़ो_ढाँचा_error;
	पूर्ण

	/* Integrity check */
	अगर (qla8044_reset_seq_checksum_test(vha)) अणु
		ql_log(ql_log_fatal, vha, 0xb0be,
		    "%s: Reset Seq checksum failed!\n", __func__);
		जाओ निकास_पढ़ो_ढाँचा_error;
	पूर्ण

	ql_dbg(ql_dbg_p3p, vha, 0xb0bf,
	    "%s: Reset Seq checksum passed! Get stop, "
	    "start and init seq offsets\n", __func__);

	/* Get STOP, START, INIT sequence offsets */
	vha->reset_पंचांगplt.init_offset = vha->reset_पंचांगplt.buff +
	    vha->reset_पंचांगplt.hdr->init_seq_offset;

	vha->reset_पंचांगplt.start_offset = vha->reset_पंचांगplt.buff +
	    vha->reset_पंचांगplt.hdr->start_seq_offset;

	vha->reset_पंचांगplt.stop_offset = vha->reset_पंचांगplt.buff +
	    vha->reset_पंचांगplt.hdr->hdr_size;

	qla8044_dump_reset_seq_hdr(vha);

	जाओ निकास_पढ़ो_reset_ढाँचा;

निकास_पढ़ो_ढाँचा_error:
	vमुक्त(vha->reset_पंचांगplt.buff);

निकास_पढ़ो_reset_ढाँचा:
	वापस;
पूर्ण

व्योम
qla8044_set_idc_करोntreset(काष्ठा scsi_qla_host *vha)
अणु
	uपूर्णांक32_t idc_ctrl;
	काष्ठा qla_hw_data *ha = vha->hw;

	idc_ctrl = qla8044_rd_reg(ha, QLA8044_IDC_DRV_CTRL);
	idc_ctrl |= DONTRESET_BIT0;
	ql_dbg(ql_dbg_p3p, vha, 0xb0c0,
	    "%s: idc_ctrl = %d\n", __func__, idc_ctrl);
	qla8044_wr_reg(ha, QLA8044_IDC_DRV_CTRL, idc_ctrl);
पूर्ण

अटल अंतरभूत व्योम
qla8044_set_rst_पढ़ोy(काष्ठा scsi_qla_host *vha)
अणु
	uपूर्णांक32_t drv_state;
	काष्ठा qla_hw_data *ha = vha->hw;

	drv_state = qla8044_rd_direct(vha, QLA8044_CRB_DRV_STATE_INDEX);

	/* For ISP8044, drv_active रेजिस्टर has 1 bit per function,
	 * shअगरt 1 by func_num to set a bit क्रम the function.*/
	drv_state |= (1 << ha->portnum);

	ql_log(ql_log_info, vha, 0xb0c1,
	    "%s(%ld): drv_state: 0x%08x\n",
	    __func__, vha->host_no, drv_state);
	qla8044_wr_direct(vha, QLA8044_CRB_DRV_STATE_INDEX, drv_state);
पूर्ण

/**
 * qla8044_need_reset_handler - Code to start reset sequence
 * @vha: poपूर्णांकer to adapter काष्ठाure
 *
 * Note: IDC lock must be held upon entry
 */
अटल व्योम
qla8044_need_reset_handler(काष्ठा scsi_qla_host *vha)
अणु
	uपूर्णांक32_t dev_state = 0, drv_state, drv_active;
	अचिन्हित दीर्घ reset_समयout;
	काष्ठा qla_hw_data *ha = vha->hw;

	ql_log(ql_log_fatal, vha, 0xb0c2,
	    "%s: Performing ISP error recovery\n", __func__);

	अगर (vha->flags.online) अणु
		qla8044_idc_unlock(ha);
		qla2x00_पात_isp_cleanup(vha);
		ha->isp_ops->get_flash_version(vha, vha->req->ring);
		ha->isp_ops->nvram_config(vha);
		qla8044_idc_lock(ha);
	पूर्ण

	dev_state = qla8044_rd_direct(vha,
	    QLA8044_CRB_DEV_STATE_INDEX);
	drv_state = qla8044_rd_direct(vha,
	    QLA8044_CRB_DRV_STATE_INDEX);
	drv_active = qla8044_rd_direct(vha,
	    QLA8044_CRB_DRV_ACTIVE_INDEX);

	ql_log(ql_log_info, vha, 0xb0c5,
	    "%s(%ld): drv_state = 0x%x, drv_active = 0x%x dev_state = 0x%x\n",
	    __func__, vha->host_no, drv_state, drv_active, dev_state);

	qla8044_set_rst_पढ़ोy(vha);

	/* रुको क्रम 10 seconds क्रम reset ack from all functions */
	reset_समयout = jअगरfies + (ha->fcoe_reset_समयout * HZ);

	करो अणु
		अगर (समय_after_eq(jअगरfies, reset_समयout)) अणु
			ql_log(ql_log_info, vha, 0xb0c4,
			    "%s: Function %d: Reset Ack Timeout!, drv_state: 0x%08x, drv_active: 0x%08x\n",
			    __func__, ha->portnum, drv_state, drv_active);
			अवरोध;
		पूर्ण

		qla8044_idc_unlock(ha);
		msleep(1000);
		qla8044_idc_lock(ha);

		dev_state = qla8044_rd_direct(vha,
		    QLA8044_CRB_DEV_STATE_INDEX);
		drv_state = qla8044_rd_direct(vha,
		    QLA8044_CRB_DRV_STATE_INDEX);
		drv_active = qla8044_rd_direct(vha,
		    QLA8044_CRB_DRV_ACTIVE_INDEX);
	पूर्ण जबतक (((drv_state & drv_active) != drv_active) &&
	    (dev_state == QLA8XXX_DEV_NEED_RESET));

	/* Remove IDC participation of functions not acknowledging */
	अगर (drv_state != drv_active) अणु
		ql_log(ql_log_info, vha, 0xb0c7,
		    "%s(%ld): Function %d turning off drv_active of non-acking function 0x%x\n",
		    __func__, vha->host_no, ha->portnum,
		    (drv_active ^ drv_state));
		drv_active = drv_active & drv_state;
		qla8044_wr_direct(vha, QLA8044_CRB_DRV_ACTIVE_INDEX,
		    drv_active);
	पूर्ण अन्यथा अणु
		/*
		 * Reset owner should execute reset recovery,
		 * अगर all functions acknowledged
		 */
		अगर ((ha->flags.nic_core_reset_owner) &&
		    (dev_state == QLA8XXX_DEV_NEED_RESET)) अणु
			ha->flags.nic_core_reset_owner = 0;
			qla8044_device_bootstrap(vha);
			वापस;
		पूर्ण
	पूर्ण

	/* Exit अगर non active function */
	अगर (!(drv_active & (1 << ha->portnum))) अणु
		ha->flags.nic_core_reset_owner = 0;
		वापस;
	पूर्ण

	/*
	 * Execute Reset Recovery अगर Reset Owner or Function 7
	 * is the only active function
	 */
	अगर (ha->flags.nic_core_reset_owner ||
	    ((drv_state & drv_active) == QLA8044_FUN7_ACTIVE_INDEX)) अणु
		ha->flags.nic_core_reset_owner = 0;
		qla8044_device_bootstrap(vha);
	पूर्ण
पूर्ण

अटल व्योम
qla8044_set_drv_active(काष्ठा scsi_qla_host *vha)
अणु
	uपूर्णांक32_t drv_active;
	काष्ठा qla_hw_data *ha = vha->hw;

	drv_active = qla8044_rd_direct(vha, QLA8044_CRB_DRV_ACTIVE_INDEX);

	/* For ISP8044, drv_active रेजिस्टर has 1 bit per function,
	 * shअगरt 1 by func_num to set a bit क्रम the function.*/
	drv_active |= (1 << ha->portnum);

	ql_log(ql_log_info, vha, 0xb0c8,
	    "%s(%ld): drv_active: 0x%08x\n",
	    __func__, vha->host_no, drv_active);
	qla8044_wr_direct(vha, QLA8044_CRB_DRV_ACTIVE_INDEX, drv_active);
पूर्ण

अटल पूर्णांक
qla8044_check_drv_active(काष्ठा scsi_qla_host *vha)
अणु
	uपूर्णांक32_t drv_active;
	काष्ठा qla_hw_data *ha = vha->hw;

	drv_active = qla8044_rd_direct(vha, QLA8044_CRB_DRV_ACTIVE_INDEX);
	अगर (drv_active & (1 << ha->portnum))
		वापस QLA_SUCCESS;
	अन्यथा
		वापस QLA_TEST_FAILED;
पूर्ण

अटल व्योम
qla8044_clear_idc_करोntreset(काष्ठा scsi_qla_host *vha)
अणु
	uपूर्णांक32_t idc_ctrl;
	काष्ठा qla_hw_data *ha = vha->hw;

	idc_ctrl = qla8044_rd_reg(ha, QLA8044_IDC_DRV_CTRL);
	idc_ctrl &= ~DONTRESET_BIT0;
	ql_log(ql_log_info, vha, 0xb0c9,
	    "%s: idc_ctrl = %d\n", __func__,
	    idc_ctrl);
	qla8044_wr_reg(ha, QLA8044_IDC_DRV_CTRL, idc_ctrl);
पूर्ण

अटल पूर्णांक
qla8044_set_idc_ver(काष्ठा scsi_qla_host *vha)
अणु
	पूर्णांक idc_ver;
	uपूर्णांक32_t drv_active;
	पूर्णांक rval = QLA_SUCCESS;
	काष्ठा qla_hw_data *ha = vha->hw;

	drv_active = qla8044_rd_direct(vha, QLA8044_CRB_DRV_ACTIVE_INDEX);
	अगर (drv_active == (1 << ha->portnum)) अणु
		idc_ver = qla8044_rd_direct(vha,
		    QLA8044_CRB_DRV_IDC_VERSION_INDEX);
		idc_ver &= (~0xFF);
		idc_ver |= QLA8044_IDC_VER_MAJ_VALUE;
		qla8044_wr_direct(vha, QLA8044_CRB_DRV_IDC_VERSION_INDEX,
		    idc_ver);
		ql_log(ql_log_info, vha, 0xb0ca,
		    "%s: IDC version updated to %d\n",
		    __func__, idc_ver);
	पूर्ण अन्यथा अणु
		idc_ver = qla8044_rd_direct(vha,
		    QLA8044_CRB_DRV_IDC_VERSION_INDEX);
		idc_ver &= 0xFF;
		अगर (QLA8044_IDC_VER_MAJ_VALUE != idc_ver) अणु
			ql_log(ql_log_info, vha, 0xb0cb,
			    "%s: qla4xxx driver IDC version %d "
			    "is not compatible with IDC version %d "
			    "of other drivers!\n",
			    __func__, QLA8044_IDC_VER_MAJ_VALUE,
			    idc_ver);
			rval = QLA_FUNCTION_FAILED;
			जाओ निकास_set_idc_ver;
		पूर्ण
	पूर्ण

	/* Update IDC_MINOR_VERSION */
	idc_ver = qla8044_rd_reg(ha, QLA8044_CRB_IDC_VER_MINOR);
	idc_ver &= ~(0x03 << (ha->portnum * 2));
	idc_ver |= (QLA8044_IDC_VER_MIN_VALUE << (ha->portnum * 2));
	qla8044_wr_reg(ha, QLA8044_CRB_IDC_VER_MINOR, idc_ver);

निकास_set_idc_ver:
	वापस rval;
पूर्ण

अटल पूर्णांक
qla8044_update_idc_reg(काष्ठा scsi_qla_host *vha)
अणु
	uपूर्णांक32_t drv_active;
	पूर्णांक rval = QLA_SUCCESS;
	काष्ठा qla_hw_data *ha = vha->hw;

	अगर (vha->flags.init_करोne)
		जाओ निकास_update_idc_reg;

	qla8044_idc_lock(ha);
	qla8044_set_drv_active(vha);

	drv_active = qla8044_rd_direct(vha,
	    QLA8044_CRB_DRV_ACTIVE_INDEX);

	/* If we are the first driver to load and
	 * ql2xकरोntresethba is not set, clear IDC_CTRL BIT0. */
	अगर ((drv_active == (1 << ha->portnum)) && !ql2xकरोntresethba)
		qla8044_clear_idc_करोntreset(vha);

	rval = qla8044_set_idc_ver(vha);
	अगर (rval == QLA_FUNCTION_FAILED)
		qla8044_clear_drv_active(ha);
	qla8044_idc_unlock(ha);

निकास_update_idc_reg:
	वापस rval;
पूर्ण

/**
 * qla8044_need_qsnt_handler - Code to start qsnt
 * @vha: poपूर्णांकer to adapter काष्ठाure
 */
अटल व्योम
qla8044_need_qsnt_handler(काष्ठा scsi_qla_host *vha)
अणु
	अचिन्हित दीर्घ qsnt_समयout;
	uपूर्णांक32_t drv_state, drv_active, dev_state;
	काष्ठा qla_hw_data *ha = vha->hw;

	अगर (vha->flags.online)
		qla2x00_quiesce_io(vha);
	अन्यथा
		वापस;

	qla8044_set_qsnt_पढ़ोy(vha);

	/* Wait क्रम 30 secs क्रम all functions to ack qsnt mode */
	qsnt_समयout = jअगरfies + (QSNT_ACK_TOV * HZ);
	drv_state = qla8044_rd_direct(vha, QLA8044_CRB_DRV_STATE_INDEX);
	drv_active = qla8044_rd_direct(vha, QLA8044_CRB_DRV_ACTIVE_INDEX);

	/* Shअगरt drv_active by 1 to match drv_state. As quiescent पढ़ोy bit
	   position is at bit 1 and drv active is at bit 0 */
	drv_active = drv_active << 1;

	जबतक (drv_state != drv_active) अणु
		अगर (समय_after_eq(jअगरfies, qsnt_समयout)) अणु
			/* Other functions did not ack, changing state to
			 * DEV_READY
			 */
			clear_bit(ISP_QUIESCE_NEEDED, &vha->dpc_flags);
			qla8044_wr_direct(vha, QLA8044_CRB_DEV_STATE_INDEX,
					    QLA8XXX_DEV_READY);
			qla8044_clear_qsnt_पढ़ोy(vha);
			ql_log(ql_log_info, vha, 0xb0cc,
			    "Timeout waiting for quiescent ack!!!\n");
			वापस;
		पूर्ण
		qla8044_idc_unlock(ha);
		msleep(1000);
		qla8044_idc_lock(ha);

		drv_state = qla8044_rd_direct(vha,
		    QLA8044_CRB_DRV_STATE_INDEX);
		drv_active = qla8044_rd_direct(vha,
		    QLA8044_CRB_DRV_ACTIVE_INDEX);
		drv_active = drv_active << 1;
	पूर्ण

	/* All functions have Acked. Set quiescent state */
	dev_state = qla8044_rd_direct(vha, QLA8044_CRB_DEV_STATE_INDEX);

	अगर (dev_state == QLA8XXX_DEV_NEED_QUIESCENT) अणु
		qla8044_wr_direct(vha, QLA8044_CRB_DEV_STATE_INDEX,
		    QLA8XXX_DEV_QUIESCENT);
		ql_log(ql_log_info, vha, 0xb0cd,
		    "%s: HW State: QUIESCENT\n", __func__);
	पूर्ण
पूर्ण

/*
 * qla8044_device_state_handler - Adapter state machine
 * @ha: poपूर्णांकer to host adapter काष्ठाure.
 *
 * Note: IDC lock must be UNLOCKED upon entry
 **/
पूर्णांक
qla8044_device_state_handler(काष्ठा scsi_qla_host *vha)
अणु
	uपूर्णांक32_t dev_state;
	पूर्णांक rval = QLA_SUCCESS;
	अचिन्हित दीर्घ dev_init_समयout;
	काष्ठा qla_hw_data *ha = vha->hw;

	rval = qla8044_update_idc_reg(vha);
	अगर (rval == QLA_FUNCTION_FAILED)
		जाओ निकास_error;

	dev_state = qla8044_rd_direct(vha, QLA8044_CRB_DEV_STATE_INDEX);
	ql_dbg(ql_dbg_p3p, vha, 0xb0ce,
	    "Device state is 0x%x = %s\n",
	    dev_state, dev_state < MAX_STATES ?
	    qdev_state(dev_state) : "Unknown");

	/* रुको क्रम 30 seconds क्रम device to go पढ़ोy */
	dev_init_समयout = jअगरfies + (ha->fcoe_dev_init_समयout * HZ);

	qla8044_idc_lock(ha);

	जबतक (1) अणु
		अगर (समय_after_eq(jअगरfies, dev_init_समयout)) अणु
			अगर (qla8044_check_drv_active(vha) == QLA_SUCCESS) अणु
				ql_log(ql_log_warn, vha, 0xb0cf,
				    "%s: Device Init Failed 0x%x = %s\n",
				    QLA2XXX_DRIVER_NAME, dev_state,
				    dev_state < MAX_STATES ?
				    qdev_state(dev_state) : "Unknown");
				qla8044_wr_direct(vha,
				    QLA8044_CRB_DEV_STATE_INDEX,
				    QLA8XXX_DEV_FAILED);
			पूर्ण
		पूर्ण

		dev_state = qla8044_rd_direct(vha, QLA8044_CRB_DEV_STATE_INDEX);
		ql_log(ql_log_info, vha, 0xb0d0,
		    "Device state is 0x%x = %s\n",
		    dev_state, dev_state < MAX_STATES ?
		    qdev_state(dev_state) : "Unknown");

		/* NOTE: Make sure idc unlocked upon निकास of चयन statement */
		चयन (dev_state) अणु
		हाल QLA8XXX_DEV_READY:
			ha->flags.nic_core_reset_owner = 0;
			जाओ निकास;
		हाल QLA8XXX_DEV_COLD:
			rval = qla8044_device_bootstrap(vha);
			अवरोध;
		हाल QLA8XXX_DEV_INITIALIZING:
			qla8044_idc_unlock(ha);
			msleep(1000);
			qla8044_idc_lock(ha);
			अवरोध;
		हाल QLA8XXX_DEV_NEED_RESET:
			/* For ISP8044, अगर NEED_RESET is set by any driver,
			 * it should be honored, irrespective of IDC_CTRL
			 * DONTRESET_BIT0 */
			qla8044_need_reset_handler(vha);
			अवरोध;
		हाल QLA8XXX_DEV_NEED_QUIESCENT:
			/* idc locked/unlocked in handler */
			qla8044_need_qsnt_handler(vha);

			/* Reset the init समयout after qsnt handler */
			dev_init_समयout = jअगरfies +
			    (ha->fcoe_reset_समयout * HZ);
			अवरोध;
		हाल QLA8XXX_DEV_QUIESCENT:
			ql_log(ql_log_info, vha, 0xb0d1,
			    "HW State: QUIESCENT\n");

			qla8044_idc_unlock(ha);
			msleep(1000);
			qla8044_idc_lock(ha);

			/* Reset the init समयout after qsnt handler */
			dev_init_समयout = jअगरfies +
			    (ha->fcoe_reset_समयout * HZ);
			अवरोध;
		हाल QLA8XXX_DEV_FAILED:
			ha->flags.nic_core_reset_owner = 0;
			qla8044_idc_unlock(ha);
			qla8xxx_dev_failed_handler(vha);
			rval = QLA_FUNCTION_FAILED;
			qla8044_idc_lock(ha);
			जाओ निकास;
		शेष:
			qla8044_idc_unlock(ha);
			qla8xxx_dev_failed_handler(vha);
			rval = QLA_FUNCTION_FAILED;
			qla8044_idc_lock(ha);
			जाओ निकास;
		पूर्ण
	पूर्ण
निकास:
	qla8044_idc_unlock(ha);

निकास_error:
	वापस rval;
पूर्ण

/**
 * qla8044_check_temp - Check the ISP82XX temperature.
 * @vha: adapter block poपूर्णांकer.
 *
 * Note: The caller should not hold the idc lock.
 */
अटल पूर्णांक
qla8044_check_temp(काष्ठा scsi_qla_host *vha)
अणु
	uपूर्णांक32_t temp, temp_state, temp_val;
	पूर्णांक status = QLA_SUCCESS;

	temp = qla8044_rd_direct(vha, QLA8044_CRB_TEMP_STATE_INDEX);
	temp_state = qla82xx_get_temp_state(temp);
	temp_val = qla82xx_get_temp_val(temp);

	अगर (temp_state == QLA82XX_TEMP_PANIC) अणु
		ql_log(ql_log_warn, vha, 0xb0d2,
		    "Device temperature %d degrees C"
		    " exceeds maximum allowed. Hardware has been shut"
		    " down\n", temp_val);
		status = QLA_FUNCTION_FAILED;
		वापस status;
	पूर्ण अन्यथा अगर (temp_state == QLA82XX_TEMP_WARN) अणु
		ql_log(ql_log_warn, vha, 0xb0d3,
		    "Device temperature %d"
		    " degrees C exceeds operating range."
		    " Immediate action needed.\n", temp_val);
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक qla8044_पढ़ो_temperature(scsi_qla_host_t *vha)
अणु
	uपूर्णांक32_t temp;

	temp = qla8044_rd_direct(vha, QLA8044_CRB_TEMP_STATE_INDEX);
	वापस qla82xx_get_temp_val(temp);
पूर्ण

/**
 * qla8044_check_fw_alive  - Check firmware health
 * @vha: Poपूर्णांकer to host adapter काष्ठाure.
 *
 * Context: Interrupt
 */
पूर्णांक
qla8044_check_fw_alive(काष्ठा scsi_qla_host *vha)
अणु
	uपूर्णांक32_t fw_heartbeat_counter;
	uपूर्णांक32_t halt_status1, halt_status2;
	पूर्णांक status = QLA_SUCCESS;

	fw_heartbeat_counter = qla8044_rd_direct(vha,
	    QLA8044_PEG_ALIVE_COUNTER_INDEX);

	/* If PEG_ALIVE_COUNTER is 0xffffffff, AER/EEH is in progress, ignore */
	अगर (fw_heartbeat_counter == 0xffffffff) अणु
		ql_dbg(ql_dbg_p3p, vha, 0xb0d4,
		    "scsi%ld: %s: Device in frozen "
		    "state, QLA82XX_PEG_ALIVE_COUNTER is 0xffffffff\n",
		    vha->host_no, __func__);
		वापस status;
	पूर्ण

	अगर (vha->fw_heartbeat_counter == fw_heartbeat_counter) अणु
		vha->seconds_since_last_heartbeat++;
		/* FW not alive after 2 seconds */
		अगर (vha->seconds_since_last_heartbeat == 2) अणु
			vha->seconds_since_last_heartbeat = 0;
			halt_status1 = qla8044_rd_direct(vha,
			    QLA8044_PEG_HALT_STATUS1_INDEX);
			halt_status2 = qla8044_rd_direct(vha,
			    QLA8044_PEG_HALT_STATUS2_INDEX);

			ql_log(ql_log_info, vha, 0xb0d5,
			    "scsi(%ld): %s, ISP8044 "
			    "Dumping hw/fw registers:\n"
			    " PEG_HALT_STATUS1: 0x%x, "
			    "PEG_HALT_STATUS2: 0x%x,\n",
			    vha->host_no, __func__, halt_status1,
			    halt_status2);
			status = QLA_FUNCTION_FAILED;
		पूर्ण
	पूर्ण अन्यथा
		vha->seconds_since_last_heartbeat = 0;

	vha->fw_heartbeat_counter = fw_heartbeat_counter;
	वापस status;
पूर्ण

व्योम
qla8044_watchकरोg(काष्ठा scsi_qla_host *vha)
अणु
	uपूर्णांक32_t dev_state, halt_status;
	पूर्णांक halt_status_unrecoverable = 0;
	काष्ठा qla_hw_data *ha = vha->hw;

	/* करोn't poll अगर reset is going on or FW hang in quiescent state */
	अगर (!(test_bit(ABORT_ISP_ACTIVE, &vha->dpc_flags) ||
	    test_bit(FCOE_CTX_RESET_NEEDED, &vha->dpc_flags))) अणु
		dev_state = qla8044_rd_direct(vha, QLA8044_CRB_DEV_STATE_INDEX);

		अगर (qla8044_check_fw_alive(vha)) अणु
			ha->flags.isp82xx_fw_hung = 1;
			ql_log(ql_log_warn, vha, 0xb10a,
			    "Firmware hung.\n");
			qla82xx_clear_pending_mbx(vha);
		पूर्ण

		अगर (qla8044_check_temp(vha)) अणु
			set_bit(ISP_UNRECOVERABLE, &vha->dpc_flags);
			ha->flags.isp82xx_fw_hung = 1;
			qla2xxx_wake_dpc(vha);
		पूर्ण अन्यथा अगर (dev_state == QLA8XXX_DEV_NEED_RESET &&
			   !test_bit(ISP_ABORT_NEEDED, &vha->dpc_flags)) अणु
			ql_log(ql_log_info, vha, 0xb0d6,
			    "%s: HW State: NEED RESET!\n",
			    __func__);
			set_bit(ISP_ABORT_NEEDED, &vha->dpc_flags);
			qla2xxx_wake_dpc(vha);
		पूर्ण अन्यथा अगर (dev_state == QLA8XXX_DEV_NEED_QUIESCENT &&
		    !test_bit(ISP_QUIESCE_NEEDED, &vha->dpc_flags)) अणु
			ql_log(ql_log_info, vha, 0xb0d7,
			    "%s: HW State: NEED QUIES detected!\n",
			    __func__);
			set_bit(ISP_QUIESCE_NEEDED, &vha->dpc_flags);
			qla2xxx_wake_dpc(vha);
		पूर्ण अन्यथा  अणु
			/* Check firmware health */
			अगर (ha->flags.isp82xx_fw_hung) अणु
				halt_status = qla8044_rd_direct(vha,
					QLA8044_PEG_HALT_STATUS1_INDEX);
				अगर (halt_status &
				    QLA8044_HALT_STATUS_FW_RESET) अणु
					ql_log(ql_log_fatal, vha,
					    0xb0d8, "%s: Firmware "
					    "error detected device "
					    "is being reset\n",
					    __func__);
				पूर्ण अन्यथा अगर (halt_status &
					    QLA8044_HALT_STATUS_UNRECOVERABLE) अणु
						halt_status_unrecoverable = 1;
				पूर्ण

				/* Since we cannot change dev_state in पूर्णांकerrupt
				 * context, set appropriate DPC flag then wakeup
				 *  DPC */
				अगर (halt_status_unrecoverable) अणु
					set_bit(ISP_UNRECOVERABLE,
					    &vha->dpc_flags);
				पूर्ण अन्यथा अणु
					अगर (dev_state ==
					    QLA8XXX_DEV_QUIESCENT) अणु
						set_bit(FCOE_CTX_RESET_NEEDED,
						    &vha->dpc_flags);
						ql_log(ql_log_info, vha, 0xb0d9,
						    "%s: FW CONTEXT Reset "
						    "needed!\n", __func__);
					पूर्ण अन्यथा अणु
						ql_log(ql_log_info, vha,
						    0xb0da, "%s: "
						    "detect abort needed\n",
						    __func__);
						set_bit(ISP_ABORT_NEEDED,
						    &vha->dpc_flags);
					पूर्ण
				पूर्ण
				qla2xxx_wake_dpc(vha);
			पूर्ण
		पूर्ण

	पूर्ण
पूर्ण

अटल पूर्णांक
qla8044_minidump_process_control(काष्ठा scsi_qla_host *vha,
				 काष्ठा qla8044_minidump_entry_hdr *entry_hdr)
अणु
	काष्ठा qla8044_minidump_entry_crb *crb_entry;
	uपूर्णांक32_t पढ़ो_value, opcode, poll_समय, addr, index;
	uपूर्णांक32_t crb_addr, rval = QLA_SUCCESS;
	अचिन्हित दीर्घ wसमय;
	काष्ठा qla8044_minidump_ढाँचा_hdr *पंचांगplt_hdr;
	पूर्णांक i;
	काष्ठा qla_hw_data *ha = vha->hw;

	ql_dbg(ql_dbg_p3p, vha, 0xb0dd, "Entering fn: %s\n", __func__);
	पंचांगplt_hdr = (काष्ठा qla8044_minidump_ढाँचा_hdr *)
		ha->md_पंचांगplt_hdr;
	crb_entry = (काष्ठा qla8044_minidump_entry_crb *)entry_hdr;

	crb_addr = crb_entry->addr;
	क्रम (i = 0; i < crb_entry->op_count; i++) अणु
		opcode = crb_entry->crb_ctrl.opcode;

		अगर (opcode & QLA82XX_DBG_OPCODE_WR) अणु
			qla8044_wr_reg_indirect(vha, crb_addr,
			    crb_entry->value_1);
		पूर्ण

		अगर (opcode & QLA82XX_DBG_OPCODE_RW) अणु
			qla8044_rd_reg_indirect(vha, crb_addr, &पढ़ो_value);
			qla8044_wr_reg_indirect(vha, crb_addr, पढ़ो_value);
		पूर्ण

		अगर (opcode & QLA82XX_DBG_OPCODE_AND) अणु
			qla8044_rd_reg_indirect(vha, crb_addr, &पढ़ो_value);
			पढ़ो_value &= crb_entry->value_2;
			अगर (opcode & QLA82XX_DBG_OPCODE_OR) अणु
				पढ़ो_value |= crb_entry->value_3;
				opcode &= ~QLA82XX_DBG_OPCODE_OR;
			पूर्ण
			qla8044_wr_reg_indirect(vha, crb_addr, पढ़ो_value);
		पूर्ण
		अगर (opcode & QLA82XX_DBG_OPCODE_OR) अणु
			qla8044_rd_reg_indirect(vha, crb_addr, &पढ़ो_value);
			पढ़ो_value |= crb_entry->value_3;
			qla8044_wr_reg_indirect(vha, crb_addr, पढ़ो_value);
		पूर्ण
		अगर (opcode & QLA82XX_DBG_OPCODE_POLL) अणु
			poll_समय = crb_entry->crb_strd.poll_समयout;
			wसमय = jअगरfies + poll_समय;
			qla8044_rd_reg_indirect(vha, crb_addr, &पढ़ो_value);

			करो अणु
				अगर ((पढ़ो_value & crb_entry->value_2) ==
				    crb_entry->value_1) अणु
					अवरोध;
				पूर्ण अन्यथा अगर (समय_after_eq(jअगरfies, wसमय)) अणु
					/* capturing dump failed */
					rval = QLA_FUNCTION_FAILED;
					अवरोध;
				पूर्ण अन्यथा अणु
					qla8044_rd_reg_indirect(vha,
					    crb_addr, &पढ़ो_value);
				पूर्ण
			पूर्ण जबतक (1);
		पूर्ण

		अगर (opcode & QLA82XX_DBG_OPCODE_RDSTATE) अणु
			अगर (crb_entry->crb_strd.state_index_a) अणु
				index = crb_entry->crb_strd.state_index_a;
				addr = पंचांगplt_hdr->saved_state_array[index];
			पूर्ण अन्यथा अणु
				addr = crb_addr;
			पूर्ण

			qla8044_rd_reg_indirect(vha, addr, &पढ़ो_value);
			index = crb_entry->crb_ctrl.state_index_v;
			पंचांगplt_hdr->saved_state_array[index] = पढ़ो_value;
		पूर्ण

		अगर (opcode & QLA82XX_DBG_OPCODE_WRSTATE) अणु
			अगर (crb_entry->crb_strd.state_index_a) अणु
				index = crb_entry->crb_strd.state_index_a;
				addr = पंचांगplt_hdr->saved_state_array[index];
			पूर्ण अन्यथा अणु
				addr = crb_addr;
			पूर्ण

			अगर (crb_entry->crb_ctrl.state_index_v) अणु
				index = crb_entry->crb_ctrl.state_index_v;
				पढ़ो_value =
				    पंचांगplt_hdr->saved_state_array[index];
			पूर्ण अन्यथा अणु
				पढ़ो_value = crb_entry->value_1;
			पूर्ण

			qla8044_wr_reg_indirect(vha, addr, पढ़ो_value);
		पूर्ण

		अगर (opcode & QLA82XX_DBG_OPCODE_MDSTATE) अणु
			index = crb_entry->crb_ctrl.state_index_v;
			पढ़ो_value = पंचांगplt_hdr->saved_state_array[index];
			पढ़ो_value <<= crb_entry->crb_ctrl.shl;
			पढ़ो_value >>= crb_entry->crb_ctrl.shr;
			अगर (crb_entry->value_2)
				पढ़ो_value &= crb_entry->value_2;
			पढ़ो_value |= crb_entry->value_3;
			पढ़ो_value += crb_entry->value_1;
			पंचांगplt_hdr->saved_state_array[index] = पढ़ो_value;
		पूर्ण
		crb_addr += crb_entry->crb_strd.addr_stride;
	पूर्ण
	वापस rval;
पूर्ण

अटल व्योम
qla8044_minidump_process_rdcrb(काष्ठा scsi_qla_host *vha,
	काष्ठा qla8044_minidump_entry_hdr *entry_hdr, uपूर्णांक32_t **d_ptr)
अणु
	uपूर्णांक32_t r_addr, r_stride, loop_cnt, i, r_value;
	काष्ठा qla8044_minidump_entry_crb *crb_hdr;
	uपूर्णांक32_t *data_ptr = *d_ptr;

	ql_dbg(ql_dbg_p3p, vha, 0xb0de, "Entering fn: %s\n", __func__);
	crb_hdr = (काष्ठा qla8044_minidump_entry_crb *)entry_hdr;
	r_addr = crb_hdr->addr;
	r_stride = crb_hdr->crb_strd.addr_stride;
	loop_cnt = crb_hdr->op_count;

	क्रम (i = 0; i < loop_cnt; i++) अणु
		qla8044_rd_reg_indirect(vha, r_addr, &r_value);
		*data_ptr++ = r_addr;
		*data_ptr++ = r_value;
		r_addr += r_stride;
	पूर्ण
	*d_ptr = data_ptr;
पूर्ण

अटल पूर्णांक
qla8044_minidump_process_rdmem(काष्ठा scsi_qla_host *vha,
	काष्ठा qla8044_minidump_entry_hdr *entry_hdr, uपूर्णांक32_t **d_ptr)
अणु
	uपूर्णांक32_t r_addr, r_value, r_data;
	uपूर्णांक32_t i, j, loop_cnt;
	काष्ठा qla8044_minidump_entry_rdmem *m_hdr;
	अचिन्हित दीर्घ flags;
	uपूर्णांक32_t *data_ptr = *d_ptr;
	काष्ठा qla_hw_data *ha = vha->hw;

	ql_dbg(ql_dbg_p3p, vha, 0xb0df, "Entering fn: %s\n", __func__);
	m_hdr = (काष्ठा qla8044_minidump_entry_rdmem *)entry_hdr;
	r_addr = m_hdr->पढ़ो_addr;
	loop_cnt = m_hdr->पढ़ो_data_size/16;

	ql_dbg(ql_dbg_p3p, vha, 0xb0f0,
	    "[%s]: Read addr: 0x%x, read_data_size: 0x%x\n",
	    __func__, r_addr, m_hdr->पढ़ो_data_size);

	अगर (r_addr & 0xf) अणु
		ql_dbg(ql_dbg_p3p, vha, 0xb0f1,
		    "[%s]: Read addr 0x%x not 16 bytes aligned\n",
		    __func__, r_addr);
		वापस QLA_FUNCTION_FAILED;
	पूर्ण

	अगर (m_hdr->पढ़ो_data_size % 16) अणु
		ql_dbg(ql_dbg_p3p, vha, 0xb0f2,
		    "[%s]: Read data[0x%x] not multiple of 16 bytes\n",
		    __func__, m_hdr->पढ़ो_data_size);
		वापस QLA_FUNCTION_FAILED;
	पूर्ण

	ql_dbg(ql_dbg_p3p, vha, 0xb0f3,
	    "[%s]: rdmem_addr: 0x%x, read_data_size: 0x%x, loop_cnt: 0x%x\n",
	    __func__, r_addr, m_hdr->पढ़ो_data_size, loop_cnt);

	ग_लिखो_lock_irqsave(&ha->hw_lock, flags);
	क्रम (i = 0; i < loop_cnt; i++) अणु
		qla8044_wr_reg_indirect(vha, MD_MIU_TEST_AGT_ADDR_LO, r_addr);
		r_value = 0;
		qla8044_wr_reg_indirect(vha, MD_MIU_TEST_AGT_ADDR_HI, r_value);
		r_value = MIU_TA_CTL_ENABLE;
		qla8044_wr_reg_indirect(vha, MD_MIU_TEST_AGT_CTRL, r_value);
		r_value = MIU_TA_CTL_START_ENABLE;
		qla8044_wr_reg_indirect(vha, MD_MIU_TEST_AGT_CTRL, r_value);

		क्रम (j = 0; j < MAX_CTL_CHECK; j++) अणु
			qla8044_rd_reg_indirect(vha, MD_MIU_TEST_AGT_CTRL,
			    &r_value);
			अगर ((r_value & MIU_TA_CTL_BUSY) == 0)
				अवरोध;
		पूर्ण

		अगर (j >= MAX_CTL_CHECK) अणु
			ग_लिखो_unlock_irqrestore(&ha->hw_lock, flags);
			वापस QLA_SUCCESS;
		पूर्ण

		क्रम (j = 0; j < 4; j++) अणु
			qla8044_rd_reg_indirect(vha, MD_MIU_TEST_AGT_RDDATA[j],
			    &r_data);
			*data_ptr++ = r_data;
		पूर्ण

		r_addr += 16;
	पूर्ण
	ग_लिखो_unlock_irqrestore(&ha->hw_lock, flags);

	ql_dbg(ql_dbg_p3p, vha, 0xb0f4,
	    "Leaving fn: %s datacount: 0x%x\n",
	     __func__, (loop_cnt * 16));

	*d_ptr = data_ptr;
	वापस QLA_SUCCESS;
पूर्ण

/* ISP83xx flash पढ़ो क्रम _RDROM _BOARD */
अटल uपूर्णांक32_t
qla8044_minidump_process_rdrom(काष्ठा scsi_qla_host *vha,
	काष्ठा qla8044_minidump_entry_hdr *entry_hdr, uपूर्णांक32_t **d_ptr)
अणु
	uपूर्णांक32_t fl_addr, u32_count, rval;
	काष्ठा qla8044_minidump_entry_rdrom *rom_hdr;
	uपूर्णांक32_t *data_ptr = *d_ptr;

	rom_hdr = (काष्ठा qla8044_minidump_entry_rdrom *)entry_hdr;
	fl_addr = rom_hdr->पढ़ो_addr;
	u32_count = (rom_hdr->पढ़ो_data_size)/माप(uपूर्णांक32_t);

	ql_dbg(ql_dbg_p3p, vha, 0xb0f5, "[%s]: fl_addr: 0x%x, count: 0x%x\n",
	    __func__, fl_addr, u32_count);

	rval = qla8044_lockless_flash_पढ़ो_u32(vha, fl_addr,
	    (u8 *)(data_ptr), u32_count);

	अगर (rval != QLA_SUCCESS) अणु
		ql_log(ql_log_fatal, vha, 0xb0f6,
		    "%s: Flash Read Error,Count=%d\n", __func__, u32_count);
		वापस QLA_FUNCTION_FAILED;
	पूर्ण अन्यथा अणु
		data_ptr += u32_count;
		*d_ptr = data_ptr;
		वापस QLA_SUCCESS;
	पूर्ण
पूर्ण

अटल व्योम
qla8044_mark_entry_skipped(काष्ठा scsi_qla_host *vha,
	काष्ठा qla8044_minidump_entry_hdr *entry_hdr, पूर्णांक index)
अणु
	entry_hdr->d_ctrl.driver_flags |= QLA82XX_DBG_SKIPPED_FLAG;

	ql_log(ql_log_info, vha, 0xb0f7,
	    "scsi(%ld): Skipping entry[%d]: ETYPE[0x%x]-ELEVEL[0x%x]\n",
	    vha->host_no, index, entry_hdr->entry_type,
	    entry_hdr->d_ctrl.entry_capture_mask);
पूर्ण

अटल पूर्णांक
qla8044_minidump_process_l2tag(काष्ठा scsi_qla_host *vha,
	काष्ठा qla8044_minidump_entry_hdr *entry_hdr,
				 uपूर्णांक32_t **d_ptr)
अणु
	uपूर्णांक32_t addr, r_addr, c_addr, t_r_addr;
	uपूर्णांक32_t i, k, loop_count, t_value, r_cnt, r_value;
	अचिन्हित दीर्घ p_रुको, w_समय, p_mask;
	uपूर्णांक32_t c_value_w, c_value_r;
	काष्ठा qla8044_minidump_entry_cache *cache_hdr;
	पूर्णांक rval = QLA_FUNCTION_FAILED;
	uपूर्णांक32_t *data_ptr = *d_ptr;

	ql_dbg(ql_dbg_p3p, vha, 0xb0f8, "Entering fn: %s\n", __func__);
	cache_hdr = (काष्ठा qla8044_minidump_entry_cache *)entry_hdr;

	loop_count = cache_hdr->op_count;
	r_addr = cache_hdr->पढ़ो_addr;
	c_addr = cache_hdr->control_addr;
	c_value_w = cache_hdr->cache_ctrl.ग_लिखो_value;

	t_r_addr = cache_hdr->tag_reg_addr;
	t_value = cache_hdr->addr_ctrl.init_tag_value;
	r_cnt = cache_hdr->पढ़ो_ctrl.पढ़ो_addr_cnt;
	p_रुको = cache_hdr->cache_ctrl.poll_रुको;
	p_mask = cache_hdr->cache_ctrl.poll_mask;

	क्रम (i = 0; i < loop_count; i++) अणु
		qla8044_wr_reg_indirect(vha, t_r_addr, t_value);
		अगर (c_value_w)
			qla8044_wr_reg_indirect(vha, c_addr, c_value_w);

		अगर (p_mask) अणु
			w_समय = jअगरfies + p_रुको;
			करो अणु
				qla8044_rd_reg_indirect(vha, c_addr,
				    &c_value_r);
				अगर ((c_value_r & p_mask) == 0) अणु
					अवरोध;
				पूर्ण अन्यथा अगर (समय_after_eq(jअगरfies, w_समय)) अणु
					/* capturing dump failed */
					वापस rval;
				पूर्ण
			पूर्ण जबतक (1);
		पूर्ण

		addr = r_addr;
		क्रम (k = 0; k < r_cnt; k++) अणु
			qla8044_rd_reg_indirect(vha, addr, &r_value);
			*data_ptr++ = r_value;
			addr += cache_hdr->पढ़ो_ctrl.पढ़ो_addr_stride;
		पूर्ण
		t_value += cache_hdr->addr_ctrl.tag_value_stride;
	पूर्ण
	*d_ptr = data_ptr;
	वापस QLA_SUCCESS;
पूर्ण

अटल व्योम
qla8044_minidump_process_l1cache(काष्ठा scsi_qla_host *vha,
	काष्ठा qla8044_minidump_entry_hdr *entry_hdr, uपूर्णांक32_t **d_ptr)
अणु
	uपूर्णांक32_t addr, r_addr, c_addr, t_r_addr;
	uपूर्णांक32_t i, k, loop_count, t_value, r_cnt, r_value;
	uपूर्णांक32_t c_value_w;
	काष्ठा qla8044_minidump_entry_cache *cache_hdr;
	uपूर्णांक32_t *data_ptr = *d_ptr;

	cache_hdr = (काष्ठा qla8044_minidump_entry_cache *)entry_hdr;
	loop_count = cache_hdr->op_count;
	r_addr = cache_hdr->पढ़ो_addr;
	c_addr = cache_hdr->control_addr;
	c_value_w = cache_hdr->cache_ctrl.ग_लिखो_value;

	t_r_addr = cache_hdr->tag_reg_addr;
	t_value = cache_hdr->addr_ctrl.init_tag_value;
	r_cnt = cache_hdr->पढ़ो_ctrl.पढ़ो_addr_cnt;

	क्रम (i = 0; i < loop_count; i++) अणु
		qla8044_wr_reg_indirect(vha, t_r_addr, t_value);
		qla8044_wr_reg_indirect(vha, c_addr, c_value_w);
		addr = r_addr;
		क्रम (k = 0; k < r_cnt; k++) अणु
			qla8044_rd_reg_indirect(vha, addr, &r_value);
			*data_ptr++ = r_value;
			addr += cache_hdr->पढ़ो_ctrl.पढ़ो_addr_stride;
		पूर्ण
		t_value += cache_hdr->addr_ctrl.tag_value_stride;
	पूर्ण
	*d_ptr = data_ptr;
पूर्ण

अटल व्योम
qla8044_minidump_process_rकरोcm(काष्ठा scsi_qla_host *vha,
	काष्ठा qla8044_minidump_entry_hdr *entry_hdr, uपूर्णांक32_t **d_ptr)
अणु
	uपूर्णांक32_t r_addr, r_stride, loop_cnt, i, r_value;
	काष्ठा qla8044_minidump_entry_rकरोcm *ocm_hdr;
	uपूर्णांक32_t *data_ptr = *d_ptr;
	काष्ठा qla_hw_data *ha = vha->hw;

	ql_dbg(ql_dbg_p3p, vha, 0xb0f9, "Entering fn: %s\n", __func__);

	ocm_hdr = (काष्ठा qla8044_minidump_entry_rकरोcm *)entry_hdr;
	r_addr = ocm_hdr->पढ़ो_addr;
	r_stride = ocm_hdr->पढ़ो_addr_stride;
	loop_cnt = ocm_hdr->op_count;

	ql_dbg(ql_dbg_p3p, vha, 0xb0fa,
	    "[%s]: r_addr: 0x%x, r_stride: 0x%x, loop_cnt: 0x%x\n",
	    __func__, r_addr, r_stride, loop_cnt);

	क्रम (i = 0; i < loop_cnt; i++) अणु
		r_value = पढ़ोl((व्योम __iomem *)(r_addr + ha->nx_pcibase));
		*data_ptr++ = r_value;
		r_addr += r_stride;
	पूर्ण
	ql_dbg(ql_dbg_p3p, vha, 0xb0fb, "Leaving fn: %s datacount: 0x%lx\n",
	    __func__, (दीर्घ अचिन्हित पूर्णांक) (loop_cnt * माप(uपूर्णांक32_t)));

	*d_ptr = data_ptr;
पूर्ण

अटल व्योम
qla8044_minidump_process_rdmux(काष्ठा scsi_qla_host *vha,
	काष्ठा qla8044_minidump_entry_hdr *entry_hdr,
	uपूर्णांक32_t **d_ptr)
अणु
	uपूर्णांक32_t r_addr, s_stride, s_addr, s_value, loop_cnt, i, r_value = 0;
	काष्ठा qla8044_minidump_entry_mux *mux_hdr;
	uपूर्णांक32_t *data_ptr = *d_ptr;

	ql_dbg(ql_dbg_p3p, vha, 0xb0fc, "Entering fn: %s\n", __func__);

	mux_hdr = (काष्ठा qla8044_minidump_entry_mux *)entry_hdr;
	r_addr = mux_hdr->पढ़ो_addr;
	s_addr = mux_hdr->select_addr;
	s_stride = mux_hdr->select_value_stride;
	s_value = mux_hdr->select_value;
	loop_cnt = mux_hdr->op_count;

	क्रम (i = 0; i < loop_cnt; i++) अणु
		qla8044_wr_reg_indirect(vha, s_addr, s_value);
		qla8044_rd_reg_indirect(vha, r_addr, &r_value);
		*data_ptr++ = s_value;
		*data_ptr++ = r_value;
		s_value += s_stride;
	पूर्ण
	*d_ptr = data_ptr;
पूर्ण

अटल व्योम
qla8044_minidump_process_queue(काष्ठा scsi_qla_host *vha,
	काष्ठा qla8044_minidump_entry_hdr *entry_hdr,
	uपूर्णांक32_t **d_ptr)
अणु
	uपूर्णांक32_t s_addr, r_addr;
	uपूर्णांक32_t r_stride, r_value, r_cnt, qid = 0;
	uपूर्णांक32_t i, k, loop_cnt;
	काष्ठा qla8044_minidump_entry_queue *q_hdr;
	uपूर्णांक32_t *data_ptr = *d_ptr;

	ql_dbg(ql_dbg_p3p, vha, 0xb0fd, "Entering fn: %s\n", __func__);
	q_hdr = (काष्ठा qla8044_minidump_entry_queue *)entry_hdr;
	s_addr = q_hdr->select_addr;
	r_cnt = q_hdr->rd_strd.पढ़ो_addr_cnt;
	r_stride = q_hdr->rd_strd.पढ़ो_addr_stride;
	loop_cnt = q_hdr->op_count;

	क्रम (i = 0; i < loop_cnt; i++) अणु
		qla8044_wr_reg_indirect(vha, s_addr, qid);
		r_addr = q_hdr->पढ़ो_addr;
		क्रम (k = 0; k < r_cnt; k++) अणु
			qla8044_rd_reg_indirect(vha, r_addr, &r_value);
			*data_ptr++ = r_value;
			r_addr += r_stride;
		पूर्ण
		qid += q_hdr->q_strd.queue_id_stride;
	पूर्ण
	*d_ptr = data_ptr;
पूर्ण

/* ISP83xx functions to process new minidump entries... */
अटल uपूर्णांक32_t
qla8044_minidump_process_pollrd(काष्ठा scsi_qla_host *vha,
	काष्ठा qla8044_minidump_entry_hdr *entry_hdr,
	uपूर्णांक32_t **d_ptr)
अणु
	uपूर्णांक32_t r_addr, s_addr, s_value, r_value, poll_रुको, poll_mask;
	uपूर्णांक16_t s_stride, i;
	काष्ठा qla8044_minidump_entry_pollrd *pollrd_hdr;
	uपूर्णांक32_t *data_ptr = *d_ptr;

	pollrd_hdr = (काष्ठा qla8044_minidump_entry_pollrd *) entry_hdr;
	s_addr = pollrd_hdr->select_addr;
	r_addr = pollrd_hdr->पढ़ो_addr;
	s_value = pollrd_hdr->select_value;
	s_stride = pollrd_hdr->select_value_stride;

	poll_रुको = pollrd_hdr->poll_रुको;
	poll_mask = pollrd_hdr->poll_mask;

	क्रम (i = 0; i < pollrd_hdr->op_count; i++) अणु
		qla8044_wr_reg_indirect(vha, s_addr, s_value);
		poll_रुको = pollrd_hdr->poll_रुको;
		जबतक (1) अणु
			qla8044_rd_reg_indirect(vha, s_addr, &r_value);
			अगर ((r_value & poll_mask) != 0) अणु
				अवरोध;
			पूर्ण अन्यथा अणु
				usleep_range(1000, 1100);
				अगर (--poll_रुको == 0) अणु
					ql_log(ql_log_fatal, vha, 0xb0fe,
					    "%s: TIMEOUT\n", __func__);
					जाओ error;
				पूर्ण
			पूर्ण
		पूर्ण
		qla8044_rd_reg_indirect(vha, r_addr, &r_value);
		*data_ptr++ = s_value;
		*data_ptr++ = r_value;

		s_value += s_stride;
	पूर्ण
	*d_ptr = data_ptr;
	वापस QLA_SUCCESS;

error:
	वापस QLA_FUNCTION_FAILED;
पूर्ण

अटल व्योम
qla8044_minidump_process_rdmux2(काष्ठा scsi_qla_host *vha,
	काष्ठा qla8044_minidump_entry_hdr *entry_hdr, uपूर्णांक32_t **d_ptr)
अणु
	uपूर्णांक32_t sel_val1, sel_val2, t_sel_val, data, i;
	uपूर्णांक32_t sel_addr1, sel_addr2, sel_val_mask, पढ़ो_addr;
	काष्ठा qla8044_minidump_entry_rdmux2 *rdmux2_hdr;
	uपूर्णांक32_t *data_ptr = *d_ptr;

	rdmux2_hdr = (काष्ठा qla8044_minidump_entry_rdmux2 *) entry_hdr;
	sel_val1 = rdmux2_hdr->select_value_1;
	sel_val2 = rdmux2_hdr->select_value_2;
	sel_addr1 = rdmux2_hdr->select_addr_1;
	sel_addr2 = rdmux2_hdr->select_addr_2;
	sel_val_mask = rdmux2_hdr->select_value_mask;
	पढ़ो_addr = rdmux2_hdr->पढ़ो_addr;

	क्रम (i = 0; i < rdmux2_hdr->op_count; i++) अणु
		qla8044_wr_reg_indirect(vha, sel_addr1, sel_val1);
		t_sel_val = sel_val1 & sel_val_mask;
		*data_ptr++ = t_sel_val;

		qla8044_wr_reg_indirect(vha, sel_addr2, t_sel_val);
		qla8044_rd_reg_indirect(vha, पढ़ो_addr, &data);

		*data_ptr++ = data;

		qla8044_wr_reg_indirect(vha, sel_addr1, sel_val2);
		t_sel_val = sel_val2 & sel_val_mask;
		*data_ptr++ = t_sel_val;

		qla8044_wr_reg_indirect(vha, sel_addr2, t_sel_val);
		qla8044_rd_reg_indirect(vha, पढ़ो_addr, &data);

		*data_ptr++ = data;

		sel_val1 += rdmux2_hdr->select_value_stride;
		sel_val2 += rdmux2_hdr->select_value_stride;
	पूर्ण

	*d_ptr = data_ptr;
पूर्ण

अटल uपूर्णांक32_t
qla8044_minidump_process_pollrdmwr(काष्ठा scsi_qla_host *vha,
	काष्ठा qla8044_minidump_entry_hdr *entry_hdr,
	uपूर्णांक32_t **d_ptr)
अणु
	uपूर्णांक32_t poll_रुको, poll_mask, r_value, data;
	uपूर्णांक32_t addr_1, addr_2, value_1, value_2;
	काष्ठा qla8044_minidump_entry_pollrdmwr *poll_hdr;
	uपूर्णांक32_t *data_ptr = *d_ptr;

	poll_hdr = (काष्ठा qla8044_minidump_entry_pollrdmwr *) entry_hdr;
	addr_1 = poll_hdr->addr_1;
	addr_2 = poll_hdr->addr_2;
	value_1 = poll_hdr->value_1;
	value_2 = poll_hdr->value_2;
	poll_mask = poll_hdr->poll_mask;

	qla8044_wr_reg_indirect(vha, addr_1, value_1);

	poll_रुको = poll_hdr->poll_रुको;
	जबतक (1) अणु
		qla8044_rd_reg_indirect(vha, addr_1, &r_value);

		अगर ((r_value & poll_mask) != 0) अणु
			अवरोध;
		पूर्ण अन्यथा अणु
			usleep_range(1000, 1100);
			अगर (--poll_रुको == 0) अणु
				ql_log(ql_log_fatal, vha, 0xb0ff,
				    "%s: TIMEOUT\n", __func__);
				जाओ error;
			पूर्ण
		पूर्ण
	पूर्ण

	qla8044_rd_reg_indirect(vha, addr_2, &data);
	data &= poll_hdr->modअगरy_mask;
	qla8044_wr_reg_indirect(vha, addr_2, data);
	qla8044_wr_reg_indirect(vha, addr_1, value_2);

	poll_रुको = poll_hdr->poll_रुको;
	जबतक (1) अणु
		qla8044_rd_reg_indirect(vha, addr_1, &r_value);

		अगर ((r_value & poll_mask) != 0) अणु
			अवरोध;
		पूर्ण अन्यथा अणु
			usleep_range(1000, 1100);
			अगर (--poll_रुको == 0) अणु
				ql_log(ql_log_fatal, vha, 0xb100,
				    "%s: TIMEOUT2\n", __func__);
				जाओ error;
			पूर्ण
		पूर्ण
	पूर्ण

	*data_ptr++ = addr_2;
	*data_ptr++ = data;

	*d_ptr = data_ptr;

	वापस QLA_SUCCESS;

error:
	वापस QLA_FUNCTION_FAILED;
पूर्ण

#घोषणा ISP8044_PEX_DMA_ENGINE_INDEX		8
#घोषणा ISP8044_PEX_DMA_BASE_ADDRESS		0x77320000
#घोषणा ISP8044_PEX_DMA_NUM_OFFSET		0x10000UL
#घोषणा ISP8044_PEX_DMA_CMD_ADDR_LOW		0x0
#घोषणा ISP8044_PEX_DMA_CMD_ADDR_HIGH		0x04
#घोषणा ISP8044_PEX_DMA_CMD_STS_AND_CNTRL	0x08

#घोषणा ISP8044_PEX_DMA_READ_SIZE	(16 * 1024)
#घोषणा ISP8044_PEX_DMA_MAX_WAIT	(100 * 100) /* Max रुको of 100 msecs */

अटल पूर्णांक
qla8044_check_dma_engine_state(काष्ठा scsi_qla_host *vha)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;
	पूर्णांक rval = QLA_SUCCESS;
	uपूर्णांक32_t dma_eng_num = 0, cmd_sts_and_cntrl = 0;
	uपूर्णांक64_t dma_base_addr = 0;
	काष्ठा qla8044_minidump_ढाँचा_hdr *पंचांगplt_hdr = शून्य;

	पंचांगplt_hdr = ha->md_पंचांगplt_hdr;
	dma_eng_num =
	    पंचांगplt_hdr->saved_state_array[ISP8044_PEX_DMA_ENGINE_INDEX];
	dma_base_addr = ISP8044_PEX_DMA_BASE_ADDRESS +
		(dma_eng_num * ISP8044_PEX_DMA_NUM_OFFSET);

	/* Read the pex-dma's command-status-and-control रेजिस्टर. */
	rval = qla8044_rd_reg_indirect(vha,
	    (dma_base_addr + ISP8044_PEX_DMA_CMD_STS_AND_CNTRL),
	    &cmd_sts_and_cntrl);
	अगर (rval)
		वापस QLA_FUNCTION_FAILED;

	/* Check अगर requested pex-dma engine is available. */
	अगर (cmd_sts_and_cntrl & BIT_31)
		वापस QLA_SUCCESS;

	वापस QLA_FUNCTION_FAILED;
पूर्ण

अटल पूर्णांक
qla8044_start_pex_dma(काष्ठा scsi_qla_host *vha,
	काष्ठा qla8044_minidump_entry_rdmem_pex_dma *m_hdr)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;
	पूर्णांक rval = QLA_SUCCESS, रुको = 0;
	uपूर्णांक32_t dma_eng_num = 0, cmd_sts_and_cntrl = 0;
	uपूर्णांक64_t dma_base_addr = 0;
	काष्ठा qla8044_minidump_ढाँचा_hdr *पंचांगplt_hdr = शून्य;

	पंचांगplt_hdr = ha->md_पंचांगplt_hdr;
	dma_eng_num =
	    पंचांगplt_hdr->saved_state_array[ISP8044_PEX_DMA_ENGINE_INDEX];
	dma_base_addr = ISP8044_PEX_DMA_BASE_ADDRESS +
		(dma_eng_num * ISP8044_PEX_DMA_NUM_OFFSET);

	rval = qla8044_wr_reg_indirect(vha,
	    dma_base_addr + ISP8044_PEX_DMA_CMD_ADDR_LOW,
	    m_hdr->desc_card_addr);
	अगर (rval)
		जाओ error_निकास;

	rval = qla8044_wr_reg_indirect(vha,
	    dma_base_addr + ISP8044_PEX_DMA_CMD_ADDR_HIGH, 0);
	अगर (rval)
		जाओ error_निकास;

	rval = qla8044_wr_reg_indirect(vha,
	    dma_base_addr + ISP8044_PEX_DMA_CMD_STS_AND_CNTRL,
	    m_hdr->start_dma_cmd);
	अगर (rval)
		जाओ error_निकास;

	/* Wait क्रम dma operation to complete. */
	क्रम (रुको = 0; रुको < ISP8044_PEX_DMA_MAX_WAIT; रुको++) अणु
		rval = qla8044_rd_reg_indirect(vha,
		    (dma_base_addr + ISP8044_PEX_DMA_CMD_STS_AND_CNTRL),
		    &cmd_sts_and_cntrl);
		अगर (rval)
			जाओ error_निकास;

		अगर ((cmd_sts_and_cntrl & BIT_1) == 0)
			अवरोध;

		udelay(10);
	पूर्ण

	/* Wait a max of 100 ms, otherwise fallback to rdmem entry पढ़ो */
	अगर (रुको >= ISP8044_PEX_DMA_MAX_WAIT) अणु
		rval = QLA_FUNCTION_FAILED;
		जाओ error_निकास;
	पूर्ण

error_निकास:
	वापस rval;
पूर्ण

अटल पूर्णांक
qla8044_minidump_pex_dma_पढ़ो(काष्ठा scsi_qla_host *vha,
	काष्ठा qla8044_minidump_entry_hdr *entry_hdr, uपूर्णांक32_t **d_ptr)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;
	पूर्णांक rval = QLA_SUCCESS;
	काष्ठा qla8044_minidump_entry_rdmem_pex_dma *m_hdr = शून्य;
	uपूर्णांक32_t chunk_size, पढ़ो_size;
	uपूर्णांक8_t *data_ptr = (uपूर्णांक8_t *)*d_ptr;
	व्योम *rdmem_buffer = शून्य;
	dma_addr_t rdmem_dma;
	काष्ठा qla8044_pex_dma_descriptor dma_desc;

	rval = qla8044_check_dma_engine_state(vha);
	अगर (rval != QLA_SUCCESS) अणु
		ql_dbg(ql_dbg_p3p, vha, 0xb147,
		    "DMA engine not available. Fallback to rdmem-read.\n");
		वापस QLA_FUNCTION_FAILED;
	पूर्ण

	m_hdr = (व्योम *)entry_hdr;

	rdmem_buffer = dma_alloc_coherent(&ha->pdev->dev,
	    ISP8044_PEX_DMA_READ_SIZE, &rdmem_dma, GFP_KERNEL);
	अगर (!rdmem_buffer) अणु
		ql_dbg(ql_dbg_p3p, vha, 0xb148,
		    "Unable to allocate rdmem dma buffer\n");
		वापस QLA_FUNCTION_FAILED;
	पूर्ण

	/* Prepare pex-dma descriptor to be written to MS memory. */
	/* dma-desc-cmd layout:
	 *		0-3: dma-desc-cmd 0-3
	 *		4-7: pcid function number
	 *		8-15: dma-desc-cmd 8-15
	 * dma_bus_addr: dma buffer address
	 * cmd.पढ़ो_data_size: amount of data-chunk to be पढ़ो.
	 */
	dma_desc.cmd.dma_desc_cmd = (m_hdr->dma_desc_cmd & 0xff0f);
	dma_desc.cmd.dma_desc_cmd |=
	    ((PCI_FUNC(ha->pdev->devfn) & 0xf) << 0x4);

	dma_desc.dma_bus_addr = rdmem_dma;
	dma_desc.cmd.पढ़ो_data_size = chunk_size = ISP8044_PEX_DMA_READ_SIZE;
	पढ़ो_size = 0;

	/*
	 * Perक्रमm rdmem operation using pex-dma.
	 * Prepare dma in chunks of ISP8044_PEX_DMA_READ_SIZE.
	 */
	जबतक (पढ़ो_size < m_hdr->पढ़ो_data_size) अणु
		अगर (m_hdr->पढ़ो_data_size - पढ़ो_size <
		    ISP8044_PEX_DMA_READ_SIZE) अणु
			chunk_size = (m_hdr->पढ़ो_data_size - पढ़ो_size);
			dma_desc.cmd.पढ़ो_data_size = chunk_size;
		पूर्ण

		dma_desc.src_addr = m_hdr->पढ़ो_addr + पढ़ो_size;

		/* Prepare: Write pex-dma descriptor to MS memory. */
		rval = qla8044_ms_mem_ग_लिखो_128b(vha,
		    m_hdr->desc_card_addr, (uपूर्णांक32_t *)&dma_desc,
		    (माप(काष्ठा qla8044_pex_dma_descriptor)/16));
		अगर (rval) अणु
			ql_log(ql_log_warn, vha, 0xb14a,
			    "%s: Error writing rdmem-dma-init to MS !!!\n",
			    __func__);
			जाओ error_निकास;
		पूर्ण
		ql_dbg(ql_dbg_p3p, vha, 0xb14b,
		    "%s: Dma-descriptor: Instruct for rdmem dma "
		    "(chunk_size 0x%x).\n", __func__, chunk_size);

		/* Execute: Start pex-dma operation. */
		rval = qla8044_start_pex_dma(vha, m_hdr);
		अगर (rval)
			जाओ error_निकास;

		स_नकल(data_ptr, rdmem_buffer, chunk_size);
		data_ptr += chunk_size;
		पढ़ो_size += chunk_size;
	पूर्ण

	*d_ptr = (uपूर्णांक32_t *)data_ptr;

error_निकास:
	अगर (rdmem_buffer)
		dma_मुक्त_coherent(&ha->pdev->dev, ISP8044_PEX_DMA_READ_SIZE,
		    rdmem_buffer, rdmem_dma);

	वापस rval;
पूर्ण

अटल uपूर्णांक32_t
qla8044_minidump_process_rddfe(काष्ठा scsi_qla_host *vha,
	काष्ठा qla8044_minidump_entry_hdr *entry_hdr, uपूर्णांक32_t **d_ptr)
अणु
	पूर्णांक loop_cnt;
	uपूर्णांक32_t addr1, addr2, value, data, temp, wrVal;
	uपूर्णांक8_t stride, stride2;
	uपूर्णांक16_t count;
	uपूर्णांक32_t poll, mask, modअगरy_mask;
	uपूर्णांक32_t रुको_count = 0;
	uपूर्णांक32_t *data_ptr = *d_ptr;
	काष्ठा qla8044_minidump_entry_rddfe *rddfe;

	rddfe = (काष्ठा qla8044_minidump_entry_rddfe *) entry_hdr;

	addr1 = rddfe->addr_1;
	value = rddfe->value;
	stride = rddfe->stride;
	stride2 = rddfe->stride2;
	count = rddfe->count;

	poll = rddfe->poll;
	mask = rddfe->mask;
	modअगरy_mask = rddfe->modअगरy_mask;

	addr2 = addr1 + stride;

	क्रम (loop_cnt = 0x0; loop_cnt < count; loop_cnt++) अणु
		qla8044_wr_reg_indirect(vha, addr1, (0x40000000 | value));

		रुको_count = 0;
		जबतक (रुको_count < poll) अणु
			qla8044_rd_reg_indirect(vha, addr1, &temp);
			अगर ((temp & mask) != 0)
				अवरोध;
			रुको_count++;
		पूर्ण

		अगर (रुको_count == poll) अणु
			ql_log(ql_log_warn, vha, 0xb153,
			    "%s: TIMEOUT\n", __func__);
			जाओ error;
		पूर्ण अन्यथा अणु
			qla8044_rd_reg_indirect(vha, addr2, &temp);
			temp = temp & modअगरy_mask;
			temp = (temp | ((loop_cnt << 16) | loop_cnt));
			wrVal = ((temp << 16) | temp);

			qla8044_wr_reg_indirect(vha, addr2, wrVal);
			qla8044_wr_reg_indirect(vha, addr1, value);

			रुको_count = 0;
			जबतक (रुको_count < poll) अणु
				qla8044_rd_reg_indirect(vha, addr1, &temp);
				अगर ((temp & mask) != 0)
					अवरोध;
				रुको_count++;
			पूर्ण
			अगर (रुको_count == poll) अणु
				ql_log(ql_log_warn, vha, 0xb154,
				    "%s: TIMEOUT\n", __func__);
				जाओ error;
			पूर्ण

			qla8044_wr_reg_indirect(vha, addr1,
			    ((0x40000000 | value) + stride2));
			रुको_count = 0;
			जबतक (रुको_count < poll) अणु
				qla8044_rd_reg_indirect(vha, addr1, &temp);
				अगर ((temp & mask) != 0)
					अवरोध;
				रुको_count++;
			पूर्ण

			अगर (रुको_count == poll) अणु
				ql_log(ql_log_warn, vha, 0xb155,
				    "%s: TIMEOUT\n", __func__);
				जाओ error;
			पूर्ण

			qla8044_rd_reg_indirect(vha, addr2, &data);

			*data_ptr++ = wrVal;
			*data_ptr++ = data;
		पूर्ण

	पूर्ण

	*d_ptr = data_ptr;
	वापस QLA_SUCCESS;

error:
	वापस -1;

पूर्ण

अटल uपूर्णांक32_t
qla8044_minidump_process_rdmdio(काष्ठा scsi_qla_host *vha,
	काष्ठा qla8044_minidump_entry_hdr *entry_hdr, uपूर्णांक32_t **d_ptr)
अणु
	पूर्णांक ret = 0;
	uपूर्णांक32_t addr1, addr2, value1, value2, data, selVal;
	uपूर्णांक8_t stride1, stride2;
	uपूर्णांक32_t addr3, addr4, addr5, addr6, addr7;
	uपूर्णांक16_t count, loop_cnt;
	uपूर्णांक32_t mask;
	uपूर्णांक32_t *data_ptr = *d_ptr;

	काष्ठा qla8044_minidump_entry_rdmdio *rdmdio;

	rdmdio = (काष्ठा qla8044_minidump_entry_rdmdio *) entry_hdr;

	addr1 = rdmdio->addr_1;
	addr2 = rdmdio->addr_2;
	value1 = rdmdio->value_1;
	stride1 = rdmdio->stride_1;
	stride2 = rdmdio->stride_2;
	count = rdmdio->count;

	mask = rdmdio->mask;
	value2 = rdmdio->value_2;

	addr3 = addr1 + stride1;

	क्रम (loop_cnt = 0; loop_cnt < count; loop_cnt++) अणु
		ret = qla8044_poll_रुको_ipmdio_bus_idle(vha, addr1, addr2,
		    addr3, mask);
		अगर (ret == -1)
			जाओ error;

		addr4 = addr2 - stride1;
		ret = qla8044_ipmdio_wr_reg(vha, addr1, addr3, mask, addr4,
		    value2);
		अगर (ret == -1)
			जाओ error;

		addr5 = addr2 - (2 * stride1);
		ret = qla8044_ipmdio_wr_reg(vha, addr1, addr3, mask, addr5,
		    value1);
		अगर (ret == -1)
			जाओ error;

		addr6 = addr2 - (3 * stride1);
		ret = qla8044_ipmdio_wr_reg(vha, addr1, addr3, mask,
		    addr6, 0x2);
		अगर (ret == -1)
			जाओ error;

		ret = qla8044_poll_रुको_ipmdio_bus_idle(vha, addr1, addr2,
		    addr3, mask);
		अगर (ret == -1)
			जाओ error;

		addr7 = addr2 - (4 * stride1);
		data = qla8044_ipmdio_rd_reg(vha, addr1, addr3, mask, addr7);
		अगर (data == -1)
			जाओ error;

		selVal = (value2 << 18) | (value1 << 2) | 2;

		stride2 = rdmdio->stride_2;
		*data_ptr++ = selVal;
		*data_ptr++ = data;

		value1 = value1 + stride2;
		*d_ptr = data_ptr;
	पूर्ण

	वापस 0;

error:
	वापस -1;
पूर्ण

अटल uपूर्णांक32_t qla8044_minidump_process_pollwr(काष्ठा scsi_qla_host *vha,
		काष्ठा qla8044_minidump_entry_hdr *entry_hdr, uपूर्णांक32_t **d_ptr)
अणु
	uपूर्णांक32_t addr1, addr2, value1, value2, poll, r_value;
	uपूर्णांक32_t रुको_count = 0;
	काष्ठा qla8044_minidump_entry_pollwr *pollwr_hdr;

	pollwr_hdr = (काष्ठा qla8044_minidump_entry_pollwr *)entry_hdr;
	addr1 = pollwr_hdr->addr_1;
	addr2 = pollwr_hdr->addr_2;
	value1 = pollwr_hdr->value_1;
	value2 = pollwr_hdr->value_2;

	poll = pollwr_hdr->poll;

	जबतक (रुको_count < poll) अणु
		qla8044_rd_reg_indirect(vha, addr1, &r_value);

		अगर ((r_value & poll) != 0)
			अवरोध;
		रुको_count++;
	पूर्ण

	अगर (रुको_count == poll) अणु
		ql_log(ql_log_warn, vha, 0xb156, "%s: TIMEOUT\n", __func__);
		जाओ error;
	पूर्ण

	qla8044_wr_reg_indirect(vha, addr2, value2);
	qla8044_wr_reg_indirect(vha, addr1, value1);

	रुको_count = 0;
	जबतक (रुको_count < poll) अणु
		qla8044_rd_reg_indirect(vha, addr1, &r_value);

		अगर ((r_value & poll) != 0)
			अवरोध;
		रुको_count++;
	पूर्ण

	वापस QLA_SUCCESS;

error:
	वापस -1;
पूर्ण

/*
 *
 * qla8044_collect_md_data - Retrieve firmware minidump data.
 * @ha: poपूर्णांकer to adapter काष्ठाure
 **/
पूर्णांक
qla8044_collect_md_data(काष्ठा scsi_qla_host *vha)
अणु
	पूर्णांक num_entry_hdr = 0;
	काष्ठा qla8044_minidump_entry_hdr *entry_hdr;
	काष्ठा qla8044_minidump_ढाँचा_hdr *पंचांगplt_hdr;
	uपूर्णांक32_t *data_ptr;
	uपूर्णांक32_t data_collected = 0, f_capture_mask;
	पूर्णांक i, rval = QLA_FUNCTION_FAILED;
	uपूर्णांक64_t now;
	uपूर्णांक32_t बारtamp, idc_control;
	काष्ठा qla_hw_data *ha = vha->hw;

	अगर (!ha->md_dump) अणु
		ql_log(ql_log_info, vha, 0xb101,
		    "%s(%ld) No buffer to dump\n",
		    __func__, vha->host_no);
		वापस rval;
	पूर्ण

	अगर (ha->fw_dumped) अणु
		ql_log(ql_log_warn, vha, 0xb10d,
		    "Firmware has been previously dumped (%p) "
		    "-- ignoring request.\n", ha->fw_dump);
		जाओ md_failed;
	पूर्ण

	ha->fw_dumped = false;

	अगर (!ha->md_पंचांगplt_hdr || !ha->md_dump) अणु
		ql_log(ql_log_warn, vha, 0xb10e,
		    "Memory not allocated for minidump capture\n");
		जाओ md_failed;
	पूर्ण

	qla8044_idc_lock(ha);
	idc_control = qla8044_rd_reg(ha, QLA8044_IDC_DRV_CTRL);
	अगर (idc_control & GRACEFUL_RESET_BIT1) अणु
		ql_log(ql_log_warn, vha, 0xb112,
		    "Forced reset from application, "
		    "ignore minidump capture\n");
		qla8044_wr_reg(ha, QLA8044_IDC_DRV_CTRL,
		    (idc_control & ~GRACEFUL_RESET_BIT1));
		qla8044_idc_unlock(ha);

		जाओ md_failed;
	पूर्ण
	qla8044_idc_unlock(ha);

	अगर (qla82xx_validate_ढाँचा_chksum(vha)) अणु
		ql_log(ql_log_info, vha, 0xb109,
		    "Template checksum validation error\n");
		जाओ md_failed;
	पूर्ण

	पंचांगplt_hdr = (काष्ठा qla8044_minidump_ढाँचा_hdr *)
		ha->md_पंचांगplt_hdr;
	data_ptr = (uपूर्णांक32_t *)((uपूर्णांक8_t *)ha->md_dump);
	num_entry_hdr = पंचांगplt_hdr->num_of_entries;

	ql_dbg(ql_dbg_p3p, vha, 0xb11a,
	    "Capture Mask obtained: 0x%x\n", पंचांगplt_hdr->capture_debug_level);

	f_capture_mask = पंचांगplt_hdr->capture_debug_level & 0xFF;

	/* Validate whether required debug level is set */
	अगर ((f_capture_mask & 0x3) != 0x3) अणु
		ql_log(ql_log_warn, vha, 0xb10f,
		    "Minimum required capture mask[0x%x] level not set\n",
		    f_capture_mask);

	पूर्ण
	पंचांगplt_hdr->driver_capture_mask = ql2xmdcapmask;
	ql_log(ql_log_info, vha, 0xb102,
	    "[%s]: starting data ptr: %p\n",
	   __func__, data_ptr);
	ql_log(ql_log_info, vha, 0xb10b,
	   "[%s]: no of entry headers in Template: 0x%x\n",
	   __func__, num_entry_hdr);
	ql_log(ql_log_info, vha, 0xb10c,
	    "[%s]: Total_data_size 0x%x, %d obtained\n",
	   __func__, ha->md_dump_size, ha->md_dump_size);

	/* Update current बारtamp beक्रमe taking dump */
	now = get_jअगरfies_64();
	बारtamp = (u32)(jअगरfies_to_msecs(now) / 1000);
	पंचांगplt_hdr->driver_बारtamp = बारtamp;

	entry_hdr = (काष्ठा qla8044_minidump_entry_hdr *)
		(((uपूर्णांक8_t *)ha->md_पंचांगplt_hdr) + पंचांगplt_hdr->first_entry_offset);
	पंचांगplt_hdr->saved_state_array[QLA8044_SS_OCM_WNDREG_INDEX] =
	    पंचांगplt_hdr->ocm_winकरोw_reg[ha->portnum];

	/* Walk through the entry headers - validate/perक्रमm required action */
	क्रम (i = 0; i < num_entry_hdr; i++) अणु
		अगर (data_collected > ha->md_dump_size) अणु
			ql_log(ql_log_info, vha, 0xb103,
			    "Data collected: [0x%x], "
			    "Total Dump size: [0x%x]\n",
			    data_collected, ha->md_dump_size);
			वापस rval;
		पूर्ण

		अगर (!(entry_hdr->d_ctrl.entry_capture_mask &
		      ql2xmdcapmask)) अणु
			entry_hdr->d_ctrl.driver_flags |=
			    QLA82XX_DBG_SKIPPED_FLAG;
			जाओ skip_nxt_entry;
		पूर्ण

		ql_dbg(ql_dbg_p3p, vha, 0xb104,
		    "Data collected: [0x%x], Dump size left:[0x%x]\n",
		    data_collected,
		    (ha->md_dump_size - data_collected));

		/* Decode the entry type and take required action to capture
		 * debug data
		 */
		चयन (entry_hdr->entry_type) अणु
		हाल QLA82XX_RDEND:
			qla8044_mark_entry_skipped(vha, entry_hdr, i);
			अवरोध;
		हाल QLA82XX_CNTRL:
			rval = qla8044_minidump_process_control(vha,
			    entry_hdr);
			अगर (rval != QLA_SUCCESS) अणु
				qla8044_mark_entry_skipped(vha, entry_hdr, i);
				जाओ md_failed;
			पूर्ण
			अवरोध;
		हाल QLA82XX_RDCRB:
			qla8044_minidump_process_rdcrb(vha,
			    entry_hdr, &data_ptr);
			अवरोध;
		हाल QLA82XX_RDMEM:
			rval = qla8044_minidump_pex_dma_पढ़ो(vha,
			    entry_hdr, &data_ptr);
			अगर (rval != QLA_SUCCESS) अणु
				rval = qla8044_minidump_process_rdmem(vha,
				    entry_hdr, &data_ptr);
				अगर (rval != QLA_SUCCESS) अणु
					qla8044_mark_entry_skipped(vha,
					    entry_hdr, i);
					जाओ md_failed;
				पूर्ण
			पूर्ण
			अवरोध;
		हाल QLA82XX_BOARD:
		हाल QLA82XX_RDROM:
			rval = qla8044_minidump_process_rdrom(vha,
			    entry_hdr, &data_ptr);
			अगर (rval != QLA_SUCCESS) अणु
				qla8044_mark_entry_skipped(vha,
				    entry_hdr, i);
			पूर्ण
			अवरोध;
		हाल QLA82XX_L2DTG:
		हाल QLA82XX_L2ITG:
		हाल QLA82XX_L2DAT:
		हाल QLA82XX_L2INS:
			rval = qla8044_minidump_process_l2tag(vha,
			    entry_hdr, &data_ptr);
			अगर (rval != QLA_SUCCESS) अणु
				qla8044_mark_entry_skipped(vha, entry_hdr, i);
				जाओ md_failed;
			पूर्ण
			अवरोध;
		हाल QLA8044_L1DTG:
		हाल QLA8044_L1ITG:
		हाल QLA82XX_L1DAT:
		हाल QLA82XX_L1INS:
			qla8044_minidump_process_l1cache(vha,
			    entry_hdr, &data_ptr);
			अवरोध;
		हाल QLA82XX_RDOCM:
			qla8044_minidump_process_rकरोcm(vha,
			    entry_hdr, &data_ptr);
			अवरोध;
		हाल QLA82XX_RDMUX:
			qla8044_minidump_process_rdmux(vha,
			    entry_hdr, &data_ptr);
			अवरोध;
		हाल QLA82XX_QUEUE:
			qla8044_minidump_process_queue(vha,
			    entry_hdr, &data_ptr);
			अवरोध;
		हाल QLA8044_POLLRD:
			rval = qla8044_minidump_process_pollrd(vha,
			    entry_hdr, &data_ptr);
			अगर (rval != QLA_SUCCESS)
				qla8044_mark_entry_skipped(vha, entry_hdr, i);
			अवरोध;
		हाल QLA8044_RDMUX2:
			qla8044_minidump_process_rdmux2(vha,
			    entry_hdr, &data_ptr);
			अवरोध;
		हाल QLA8044_POLLRDMWR:
			rval = qla8044_minidump_process_pollrdmwr(vha,
			    entry_hdr, &data_ptr);
			अगर (rval != QLA_SUCCESS)
				qla8044_mark_entry_skipped(vha, entry_hdr, i);
			अवरोध;
		हाल QLA8044_RDDFE:
			rval = qla8044_minidump_process_rddfe(vha, entry_hdr,
			    &data_ptr);
			अगर (rval != QLA_SUCCESS)
				qla8044_mark_entry_skipped(vha, entry_hdr, i);
			अवरोध;
		हाल QLA8044_RDMDIO:
			rval = qla8044_minidump_process_rdmdio(vha, entry_hdr,
			    &data_ptr);
			अगर (rval != QLA_SUCCESS)
				qla8044_mark_entry_skipped(vha, entry_hdr, i);
			अवरोध;
		हाल QLA8044_POLLWR:
			rval = qla8044_minidump_process_pollwr(vha, entry_hdr,
			    &data_ptr);
			अगर (rval != QLA_SUCCESS)
				qla8044_mark_entry_skipped(vha, entry_hdr, i);
			अवरोध;
		हाल QLA82XX_RDNOP:
		शेष:
			qla8044_mark_entry_skipped(vha, entry_hdr, i);
			अवरोध;
		पूर्ण

		data_collected = (uपूर्णांक8_t *)data_ptr -
		    (uपूर्णांक8_t *)((uपूर्णांक8_t *)ha->md_dump);
skip_nxt_entry:
		/*
		 * next entry in the ढाँचा
		 */
		entry_hdr = (काष्ठा qla8044_minidump_entry_hdr *)
		    (((uपूर्णांक8_t *)entry_hdr) + entry_hdr->entry_size);
	पूर्ण

	अगर (data_collected != ha->md_dump_size) अणु
		ql_log(ql_log_info, vha, 0xb105,
		    "Dump data mismatch: Data collected: "
		    "[0x%x], total_data_size:[0x%x]\n",
		    data_collected, ha->md_dump_size);
		rval = QLA_FUNCTION_FAILED;
		जाओ md_failed;
	पूर्ण

	ql_log(ql_log_info, vha, 0xb110,
	    "Firmware dump saved to temp buffer (%ld/%p %ld/%p).\n",
	    vha->host_no, ha->md_पंचांगplt_hdr, vha->host_no, ha->md_dump);
	ha->fw_dumped = true;
	qla2x00_post_uevent_work(vha, QLA_UEVENT_CODE_FW_DUMP);


	ql_log(ql_log_info, vha, 0xb106,
	    "Leaving fn: %s Last entry: 0x%x\n",
	    __func__, i);
md_failed:
	वापस rval;
पूर्ण

व्योम
qla8044_get_minidump(काष्ठा scsi_qla_host *vha)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;

	अगर (!qla8044_collect_md_data(vha)) अणु
		ha->fw_dumped = true;
		ha->prev_minidump_failed = 0;
	पूर्ण अन्यथा अणु
		ql_log(ql_log_fatal, vha, 0xb0db,
		    "%s: Unable to collect minidump\n",
		    __func__);
		ha->prev_minidump_failed = 1;
	पूर्ण
पूर्ण

अटल पूर्णांक
qla8044_poll_flash_status_reg(काष्ठा scsi_qla_host *vha)
अणु
	uपूर्णांक32_t flash_status;
	पूर्णांक retries = QLA8044_FLASH_READ_RETRY_COUNT;
	पूर्णांक ret_val = QLA_SUCCESS;

	जबतक (retries--) अणु
		ret_val = qla8044_rd_reg_indirect(vha, QLA8044_FLASH_STATUS,
		    &flash_status);
		अगर (ret_val) अणु
			ql_log(ql_log_warn, vha, 0xb13c,
			    "%s: Failed to read FLASH_STATUS reg.\n",
			    __func__);
			अवरोध;
		पूर्ण
		अगर ((flash_status & QLA8044_FLASH_STATUS_READY) ==
		    QLA8044_FLASH_STATUS_READY)
			अवरोध;
		msleep(QLA8044_FLASH_STATUS_REG_POLL_DELAY);
	पूर्ण

	अगर (!retries)
		ret_val = QLA_FUNCTION_FAILED;

	वापस ret_val;
पूर्ण

अटल पूर्णांक
qla8044_ग_लिखो_flash_status_reg(काष्ठा scsi_qla_host *vha,
			       uपूर्णांक32_t data)
अणु
	पूर्णांक ret_val = QLA_SUCCESS;
	uपूर्णांक32_t cmd;

	cmd = vha->hw->fdt_wrt_sts_reg_cmd;

	ret_val = qla8044_wr_reg_indirect(vha, QLA8044_FLASH_ADDR,
	    QLA8044_FLASH_STATUS_WRITE_DEF_SIG | cmd);
	अगर (ret_val) अणु
		ql_log(ql_log_warn, vha, 0xb125,
		    "%s: Failed to write to FLASH_ADDR.\n", __func__);
		जाओ निकास_func;
	पूर्ण

	ret_val = qla8044_wr_reg_indirect(vha, QLA8044_FLASH_WRDATA, data);
	अगर (ret_val) अणु
		ql_log(ql_log_warn, vha, 0xb126,
		    "%s: Failed to write to FLASH_WRDATA.\n", __func__);
		जाओ निकास_func;
	पूर्ण

	ret_val = qla8044_wr_reg_indirect(vha, QLA8044_FLASH_CONTROL,
	    QLA8044_FLASH_SECOND_ERASE_MS_VAL);
	अगर (ret_val) अणु
		ql_log(ql_log_warn, vha, 0xb127,
		    "%s: Failed to write to FLASH_CONTROL.\n", __func__);
		जाओ निकास_func;
	पूर्ण

	ret_val = qla8044_poll_flash_status_reg(vha);
	अगर (ret_val)
		ql_log(ql_log_warn, vha, 0xb128,
		    "%s: Error polling flash status reg.\n", __func__);

निकास_func:
	वापस ret_val;
पूर्ण

/*
 * This function assumes that the flash lock is held.
 */
अटल पूर्णांक
qla8044_unprotect_flash(scsi_qla_host_t *vha)
अणु
	पूर्णांक ret_val;
	काष्ठा qla_hw_data *ha = vha->hw;

	ret_val = qla8044_ग_लिखो_flash_status_reg(vha, ha->fdt_wrt_enable);
	अगर (ret_val)
		ql_log(ql_log_warn, vha, 0xb139,
		    "%s: Write flash status failed.\n", __func__);

	वापस ret_val;
पूर्ण

/*
 * This function assumes that the flash lock is held.
 */
अटल पूर्णांक
qla8044_protect_flash(scsi_qla_host_t *vha)
अणु
	पूर्णांक ret_val;
	काष्ठा qla_hw_data *ha = vha->hw;

	ret_val = qla8044_ग_लिखो_flash_status_reg(vha, ha->fdt_wrt_disable);
	अगर (ret_val)
		ql_log(ql_log_warn, vha, 0xb13b,
		    "%s: Write flash status failed.\n", __func__);

	वापस ret_val;
पूर्ण


अटल पूर्णांक
qla8044_erase_flash_sector(काष्ठा scsi_qla_host *vha,
			   uपूर्णांक32_t sector_start_addr)
अणु
	uपूर्णांक32_t reversed_addr;
	पूर्णांक ret_val = QLA_SUCCESS;

	ret_val = qla8044_poll_flash_status_reg(vha);
	अगर (ret_val) अणु
		ql_log(ql_log_warn, vha, 0xb12e,
		    "%s: Poll flash status after erase failed..\n", __func__);
	पूर्ण

	reversed_addr = (((sector_start_addr & 0xFF) << 16) |
	    (sector_start_addr & 0xFF00) |
	    ((sector_start_addr & 0xFF0000) >> 16));

	ret_val = qla8044_wr_reg_indirect(vha,
	    QLA8044_FLASH_WRDATA, reversed_addr);
	अगर (ret_val) अणु
		ql_log(ql_log_warn, vha, 0xb12f,
		    "%s: Failed to write to FLASH_WRDATA.\n", __func__);
	पूर्ण
	ret_val = qla8044_wr_reg_indirect(vha, QLA8044_FLASH_ADDR,
	   QLA8044_FLASH_ERASE_SIG | vha->hw->fdt_erase_cmd);
	अगर (ret_val) अणु
		ql_log(ql_log_warn, vha, 0xb130,
		    "%s: Failed to write to FLASH_ADDR.\n", __func__);
	पूर्ण
	ret_val = qla8044_wr_reg_indirect(vha, QLA8044_FLASH_CONTROL,
	    QLA8044_FLASH_LAST_ERASE_MS_VAL);
	अगर (ret_val) अणु
		ql_log(ql_log_warn, vha, 0xb131,
		    "%s: Failed write to FLASH_CONTROL.\n", __func__);
	पूर्ण
	ret_val = qla8044_poll_flash_status_reg(vha);
	अगर (ret_val) अणु
		ql_log(ql_log_warn, vha, 0xb132,
		    "%s: Poll flash status failed.\n", __func__);
	पूर्ण


	वापस ret_val;
पूर्ण

/*
 * qla8044_flash_ग_लिखो_u32 - Write data to flash
 *
 * @ha : Poपूर्णांकer to adapter काष्ठाure
 * addr : Flash address to ग_लिखो to
 * p_data : Data to be written
 *
 * Return Value - QLA_SUCCESS/QLA_FUNCTION_FAILED
 *
 * NOTE: Lock should be held on entry
 */
अटल पूर्णांक
qla8044_flash_ग_लिखो_u32(काष्ठा scsi_qla_host *vha, uपूर्णांक32_t addr,
			uपूर्णांक32_t *p_data)
अणु
	पूर्णांक ret_val = QLA_SUCCESS;

	ret_val = qla8044_wr_reg_indirect(vha, QLA8044_FLASH_ADDR,
	    0x00800000 | (addr >> 2));
	अगर (ret_val) अणु
		ql_log(ql_log_warn, vha, 0xb134,
		    "%s: Failed write to FLASH_ADDR.\n", __func__);
		जाओ निकास_func;
	पूर्ण
	ret_val = qla8044_wr_reg_indirect(vha, QLA8044_FLASH_WRDATA, *p_data);
	अगर (ret_val) अणु
		ql_log(ql_log_warn, vha, 0xb135,
		    "%s: Failed write to FLASH_WRDATA.\n", __func__);
		जाओ निकास_func;
	पूर्ण
	ret_val = qla8044_wr_reg_indirect(vha, QLA8044_FLASH_CONTROL, 0x3D);
	अगर (ret_val) अणु
		ql_log(ql_log_warn, vha, 0xb136,
		    "%s: Failed write to FLASH_CONTROL.\n", __func__);
		जाओ निकास_func;
	पूर्ण
	ret_val = qla8044_poll_flash_status_reg(vha);
	अगर (ret_val) अणु
		ql_log(ql_log_warn, vha, 0xb137,
		    "%s: Poll flash status failed.\n", __func__);
	पूर्ण

निकास_func:
	वापस ret_val;
पूर्ण

अटल पूर्णांक
qla8044_ग_लिखो_flash_buffer_mode(scsi_qla_host_t *vha, uपूर्णांक32_t *dwptr,
				uपूर्णांक32_t faddr, uपूर्णांक32_t dwords)
अणु
	पूर्णांक ret = QLA_FUNCTION_FAILED;
	uपूर्णांक32_t spi_val;

	अगर (dwords < QLA8044_MIN_OPTROM_BURST_DWORDS ||
	    dwords > QLA8044_MAX_OPTROM_BURST_DWORDS) अणु
		ql_dbg(ql_dbg_user, vha, 0xb123,
		    "Got unsupported dwords = 0x%x.\n",
		    dwords);
		वापस QLA_FUNCTION_FAILED;
	पूर्ण

	qla8044_rd_reg_indirect(vha, QLA8044_FLASH_SPI_CONTROL, &spi_val);
	qla8044_wr_reg_indirect(vha, QLA8044_FLASH_SPI_CONTROL,
	    spi_val | QLA8044_FLASH_SPI_CTL);
	qla8044_wr_reg_indirect(vha, QLA8044_FLASH_ADDR,
	    QLA8044_FLASH_FIRST_TEMP_VAL);

	/* First DWORD ग_लिखो to FLASH_WRDATA */
	ret = qla8044_wr_reg_indirect(vha, QLA8044_FLASH_WRDATA,
	    *dwptr++);
	qla8044_wr_reg_indirect(vha, QLA8044_FLASH_CONTROL,
	    QLA8044_FLASH_FIRST_MS_PATTERN);

	ret = qla8044_poll_flash_status_reg(vha);
	अगर (ret) अणु
		ql_log(ql_log_warn, vha, 0xb124,
		    "%s: Failed.\n", __func__);
		जाओ निकास_func;
	पूर्ण

	dwords--;

	qla8044_wr_reg_indirect(vha, QLA8044_FLASH_ADDR,
	    QLA8044_FLASH_SECOND_TEMP_VAL);


	/* Second to N-1 DWORDS ग_लिखोs */
	जबतक (dwords != 1) अणु
		qla8044_wr_reg_indirect(vha, QLA8044_FLASH_WRDATA, *dwptr++);
		qla8044_wr_reg_indirect(vha, QLA8044_FLASH_CONTROL,
		    QLA8044_FLASH_SECOND_MS_PATTERN);
		ret = qla8044_poll_flash_status_reg(vha);
		अगर (ret) अणु
			ql_log(ql_log_warn, vha, 0xb129,
			    "%s: Failed.\n", __func__);
			जाओ निकास_func;
		पूर्ण
		dwords--;
	पूर्ण

	qla8044_wr_reg_indirect(vha, QLA8044_FLASH_ADDR,
	    QLA8044_FLASH_FIRST_TEMP_VAL | (faddr >> 2));

	/* Last DWORD ग_लिखो */
	qla8044_wr_reg_indirect(vha, QLA8044_FLASH_WRDATA, *dwptr++);
	qla8044_wr_reg_indirect(vha, QLA8044_FLASH_CONTROL,
	    QLA8044_FLASH_LAST_MS_PATTERN);
	ret = qla8044_poll_flash_status_reg(vha);
	अगर (ret) अणु
		ql_log(ql_log_warn, vha, 0xb12a,
		    "%s: Failed.\n", __func__);
		जाओ निकास_func;
	पूर्ण
	qla8044_rd_reg_indirect(vha, QLA8044_FLASH_SPI_STATUS, &spi_val);

	अगर ((spi_val & QLA8044_FLASH_SPI_CTL) == QLA8044_FLASH_SPI_CTL) अणु
		ql_log(ql_log_warn, vha, 0xb12b,
		    "%s: Failed.\n", __func__);
		spi_val = 0;
		/* Operation failed, clear error bit. */
		qla8044_rd_reg_indirect(vha, QLA8044_FLASH_SPI_CONTROL,
		    &spi_val);
		qla8044_wr_reg_indirect(vha, QLA8044_FLASH_SPI_CONTROL,
		    spi_val | QLA8044_FLASH_SPI_CTL);
	पूर्ण
निकास_func:
	वापस ret;
पूर्ण

अटल पूर्णांक
qla8044_ग_लिखो_flash_dword_mode(scsi_qla_host_t *vha, uपूर्णांक32_t *dwptr,
			       uपूर्णांक32_t faddr, uपूर्णांक32_t dwords)
अणु
	पूर्णांक ret = QLA_FUNCTION_FAILED;
	uपूर्णांक32_t liter;

	क्रम (liter = 0; liter < dwords; liter++, faddr += 4, dwptr++) अणु
		ret = qla8044_flash_ग_लिखो_u32(vha, faddr, dwptr);
		अगर (ret) अणु
			ql_dbg(ql_dbg_p3p, vha, 0xb141,
			    "%s: flash address=%x data=%x.\n", __func__,
			     faddr, *dwptr);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक
qla8044_ग_लिखो_optrom_data(काष्ठा scsi_qla_host *vha, व्योम *buf,
			  uपूर्णांक32_t offset, uपूर्णांक32_t length)
अणु
	पूर्णांक rval = QLA_FUNCTION_FAILED, i, burst_iter_count;
	पूर्णांक dword_count, erase_sec_count;
	uपूर्णांक32_t erase_offset;
	uपूर्णांक8_t *p_cache, *p_src;

	erase_offset = offset;

	p_cache = kसुस्मृति(length, माप(uपूर्णांक8_t), GFP_KERNEL);
	अगर (!p_cache)
		वापस QLA_FUNCTION_FAILED;

	स_नकल(p_cache, buf, length);
	p_src = p_cache;
	dword_count = length / माप(uपूर्णांक32_t);
	/* Since the offset and legth are sector aligned, it will be always
	 * multiple of burst_iter_count (64)
	 */
	burst_iter_count = dword_count / QLA8044_MAX_OPTROM_BURST_DWORDS;
	erase_sec_count = length / QLA8044_SECTOR_SIZE;

	/* Suspend HBA. */
	scsi_block_requests(vha->host);
	/* Lock and enable ग_लिखो क्रम whole operation. */
	qla8044_flash_lock(vha);
	qla8044_unprotect_flash(vha);

	/* Erasing the sectors */
	क्रम (i = 0; i < erase_sec_count; i++) अणु
		rval = qla8044_erase_flash_sector(vha, erase_offset);
		ql_dbg(ql_dbg_user, vha, 0xb138,
		    "Done erase of sector=0x%x.\n",
		    erase_offset);
		अगर (rval) अणु
			ql_log(ql_log_warn, vha, 0xb121,
			    "Failed to erase the sector having address: "
			    "0x%x.\n", erase_offset);
			जाओ out;
		पूर्ण
		erase_offset += QLA8044_SECTOR_SIZE;
	पूर्ण
	ql_dbg(ql_dbg_user, vha, 0xb13f,
	    "Got write for addr = 0x%x length=0x%x.\n",
	    offset, length);

	क्रम (i = 0; i < burst_iter_count; i++) अणु

		/* Go with ग_लिखो. */
		rval = qla8044_ग_लिखो_flash_buffer_mode(vha, (uपूर्णांक32_t *)p_src,
		    offset, QLA8044_MAX_OPTROM_BURST_DWORDS);
		अगर (rval) अणु
			/* Buffer Mode failed skip to dword mode */
			ql_log(ql_log_warn, vha, 0xb122,
			    "Failed to write flash in buffer mode, "
			    "Reverting to slow-write.\n");
			rval = qla8044_ग_लिखो_flash_dword_mode(vha,
			    (uपूर्णांक32_t *)p_src, offset,
			    QLA8044_MAX_OPTROM_BURST_DWORDS);
		पूर्ण
		p_src +=  माप(uपूर्णांक32_t) * QLA8044_MAX_OPTROM_BURST_DWORDS;
		offset += माप(uपूर्णांक32_t) * QLA8044_MAX_OPTROM_BURST_DWORDS;
	पूर्ण
	ql_dbg(ql_dbg_user, vha, 0xb133,
	    "Done writing.\n");

out:
	qla8044_protect_flash(vha);
	qla8044_flash_unlock(vha);
	scsi_unblock_requests(vha->host);
	kमुक्त(p_cache);

	वापस rval;
पूर्ण

#घोषणा LEG_INT_PTR_B31		(1 << 31)
#घोषणा LEG_INT_PTR_B30		(1 << 30)
#घोषणा PF_BITS_MASK		(0xF << 16)
/**
 * qla8044_पूर्णांकr_handler() - Process पूर्णांकerrupts क्रम the ISP8044
 * @irq: पूर्णांकerrupt number
 * @dev_id: SCSI driver HA context
 *
 * Called by प्रणाली whenever the host adapter generates an पूर्णांकerrupt.
 *
 * Returns handled flag.
 */
irqवापस_t
qla8044_पूर्णांकr_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	scsi_qla_host_t	*vha;
	काष्ठा qla_hw_data *ha;
	काष्ठा rsp_que *rsp;
	काष्ठा device_reg_82xx __iomem *reg;
	पूर्णांक		status = 0;
	अचिन्हित दीर्घ	flags;
	अचिन्हित दीर्घ	iter;
	uपूर्णांक32_t	stat;
	uपूर्णांक16_t	mb[8];
	uपूर्णांक32_t leg_पूर्णांक_ptr = 0, pf_bit;

	rsp = (काष्ठा rsp_que *) dev_id;
	अगर (!rsp) अणु
		ql_log(ql_log_info, शून्य, 0xb143,
		    "%s(): NULL response queue pointer\n", __func__);
		वापस IRQ_NONE;
	पूर्ण
	ha = rsp->hw;
	vha = pci_get_drvdata(ha->pdev);

	अगर (unlikely(pci_channel_offline(ha->pdev)))
		वापस IRQ_HANDLED;

	leg_पूर्णांक_ptr = qla8044_rd_reg(ha, LEG_INTR_PTR_OFFSET);

	/* Legacy पूर्णांकerrupt is valid अगर bit31 of leg_पूर्णांक_ptr is set */
	अगर (!(leg_पूर्णांक_ptr & (LEG_INT_PTR_B31))) अणु
		ql_dbg(ql_dbg_p3p, vha, 0xb144,
		    "%s: Legacy Interrupt Bit 31 not set, "
		    "spurious interrupt!\n", __func__);
		वापस IRQ_NONE;
	पूर्ण

	pf_bit = ha->portnum << 16;
	/* Validate the PCIE function ID set in leg_पूर्णांक_ptr bits [19..16] */
	अगर ((leg_पूर्णांक_ptr & (PF_BITS_MASK)) != pf_bit) अणु
		ql_dbg(ql_dbg_p3p, vha, 0xb145,
		    "%s: Incorrect function ID 0x%x in "
		    "legacy interrupt register, "
		    "ha->pf_bit = 0x%x\n", __func__,
		    (leg_पूर्णांक_ptr & (PF_BITS_MASK)), pf_bit);
		वापस IRQ_NONE;
	पूर्ण

	/* To de-निश्चित legacy पूर्णांकerrupt, ग_लिखो 0 to Legacy Interrupt Trigger
	 * Control रेजिस्टर and poll till Legacy Interrupt Poपूर्णांकer रेजिस्टर
	 * bit32 is 0.
	 */
	qla8044_wr_reg(ha, LEG_INTR_TRIG_OFFSET, 0);
	करो अणु
		leg_पूर्णांक_ptr = qla8044_rd_reg(ha, LEG_INTR_PTR_OFFSET);
		अगर ((leg_पूर्णांक_ptr & (PF_BITS_MASK)) != pf_bit)
			अवरोध;
	पूर्ण जबतक (leg_पूर्णांक_ptr & (LEG_INT_PTR_B30));

	reg = &ha->iobase->isp82;
	spin_lock_irqsave(&ha->hardware_lock, flags);
	क्रम (iter = 1; iter--; ) अणु

		अगर (rd_reg_dword(&reg->host_पूर्णांक)) अणु
			stat = rd_reg_dword(&reg->host_status);
			अगर ((stat & HSRX_RISC_INT) == 0)
				अवरोध;

			चयन (stat & 0xff) अणु
			हाल 0x1:
			हाल 0x2:
			हाल 0x10:
			हाल 0x11:
				qla82xx_mbx_completion(vha, MSW(stat));
				status |= MBX_INTERRUPT;
				अवरोध;
			हाल 0x12:
				mb[0] = MSW(stat);
				mb[1] = rd_reg_word(&reg->mailbox_out[1]);
				mb[2] = rd_reg_word(&reg->mailbox_out[2]);
				mb[3] = rd_reg_word(&reg->mailbox_out[3]);
				qla2x00_async_event(vha, rsp, mb);
				अवरोध;
			हाल 0x13:
				qla24xx_process_response_queue(vha, rsp);
				अवरोध;
			शेष:
				ql_dbg(ql_dbg_p3p, vha, 0xb146,
				    "Unrecognized interrupt type "
				    "(%d).\n", stat & 0xff);
				अवरोध;
			पूर्ण
		पूर्ण
		wrt_reg_dword(&reg->host_पूर्णांक, 0);
	पूर्ण

	qla2x00_handle_mbx_completion(ha, status);
	spin_unlock_irqrestore(&ha->hardware_lock, flags);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक
qla8044_idc_करोntreset(काष्ठा qla_hw_data *ha)
अणु
	uपूर्णांक32_t idc_ctrl;

	idc_ctrl = qla8044_rd_reg(ha, QLA8044_IDC_DRV_CTRL);
	वापस idc_ctrl & DONTRESET_BIT0;
पूर्ण

अटल व्योम
qla8044_clear_rst_पढ़ोy(scsi_qla_host_t *vha)
अणु
	uपूर्णांक32_t drv_state;

	drv_state = qla8044_rd_direct(vha, QLA8044_CRB_DRV_STATE_INDEX);

	/*
	 * For ISP8044, drv_active रेजिस्टर has 1 bit per function,
	 * shअगरt 1 by func_num to set a bit क्रम the function.
	 * For ISP82xx, drv_active has 4 bits per function
	 */
	drv_state &= ~(1 << vha->hw->portnum);

	ql_dbg(ql_dbg_p3p, vha, 0xb13d,
	    "drv_state: 0x%08x\n", drv_state);
	qla8044_wr_direct(vha, QLA8044_CRB_DRV_STATE_INDEX, drv_state);
पूर्ण

पूर्णांक
qla8044_पात_isp(scsi_qla_host_t *vha)
अणु
	पूर्णांक rval;
	uपूर्णांक32_t dev_state;
	काष्ठा qla_hw_data *ha = vha->hw;

	qla8044_idc_lock(ha);
	dev_state = qla8044_rd_direct(vha, QLA8044_CRB_DEV_STATE_INDEX);

	अगर (ql2xकरोntresethba)
		qla8044_set_idc_करोntreset(vha);

	/* If device_state is NEED_RESET, go ahead with
	 * Reset,irrespective of ql2xकरोntresethba. This is to allow a
	 * non-reset-owner to क्रमce a reset. Non-reset-owner sets
	 * the IDC_CTRL BIT0 to prevent Reset-owner from करोing a Reset
	 * and then क्रमces a Reset by setting device_state to
	 * NEED_RESET. */
	अगर (dev_state == QLA8XXX_DEV_READY) अणु
		/* If IDC_CTRL DONTRESETHBA_BIT0 is set करोn't करो reset
		 * recovery */
		अगर (qla8044_idc_करोntreset(ha) == DONTRESET_BIT0) अणु
			ql_dbg(ql_dbg_p3p, vha, 0xb13e,
			    "Reset recovery disabled\n");
			rval = QLA_FUNCTION_FAILED;
			जाओ निकास_isp_reset;
		पूर्ण

		ql_dbg(ql_dbg_p3p, vha, 0xb140,
		    "HW State: NEED RESET\n");
		qla8044_wr_direct(vha, QLA8044_CRB_DEV_STATE_INDEX,
		    QLA8XXX_DEV_NEED_RESET);
	पूर्ण

	/* For ISP8044, Reset owner is NIC, iSCSI or FCOE based on priority
	 * and which drivers are present. Unlike ISP82XX, the function setting
	 * NEED_RESET, may not be the Reset owner. */
	qla83xx_reset_ownership(vha);

	qla8044_idc_unlock(ha);
	rval = qla8044_device_state_handler(vha);
	qla8044_idc_lock(ha);
	qla8044_clear_rst_पढ़ोy(vha);

निकास_isp_reset:
	qla8044_idc_unlock(ha);
	अगर (rval == QLA_SUCCESS) अणु
		ha->flags.isp82xx_fw_hung = 0;
		ha->flags.nic_core_reset_hdlr_active = 0;
		rval = qla82xx_restart_isp(vha);
	पूर्ण

	वापस rval;
पूर्ण

व्योम
qla8044_fw_dump(scsi_qla_host_t *vha)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;

	अगर (!ha->allow_cna_fw_dump)
		वापस;

	scsi_block_requests(vha->host);
	ha->flags.isp82xx_no_md_cap = 1;
	qla8044_idc_lock(ha);
	qla82xx_set_reset_owner(vha);
	qla8044_idc_unlock(ha);
	qla2x00_रुको_क्रम_chip_reset(vha);
	scsi_unblock_requests(vha->host);
पूर्ण
