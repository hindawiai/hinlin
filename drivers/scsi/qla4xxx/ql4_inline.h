<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * QLogic iSCSI HBA Driver
 * Copyright (c)  2003-2013 QLogic Corporation
 */

/*
 *
 * qla4xxx_lookup_ddb_by_fw_index
 *	This routine locates a device handle given the firmware device
 *	database index.	 If device करोesn't exist, वापसs शून्य.
 *
 * Input:
 *	ha - Poपूर्णांकer to host adapter काष्ठाure.
 *	fw_ddb_index - Firmware's device database index
 *
 * Returns:
 *	Poपूर्णांकer to the corresponding पूर्णांकernal device database काष्ठाure
 */
अटल अंतरभूत काष्ठा ddb_entry *
qla4xxx_lookup_ddb_by_fw_index(काष्ठा scsi_qla_host *ha, uपूर्णांक32_t fw_ddb_index)
अणु
	काष्ठा ddb_entry *ddb_entry = शून्य;

	अगर ((fw_ddb_index < MAX_DDB_ENTRIES) &&
	    (ha->fw_ddb_index_map[fw_ddb_index] !=
		(काष्ठा ddb_entry *) INVALID_ENTRY)) अणु
		ddb_entry = ha->fw_ddb_index_map[fw_ddb_index];
	पूर्ण

	DEBUG3(prपूर्णांकk("scsi%d: %s: ddb [%d], ddb_entry = %p\n",
	    ha->host_no, __func__, fw_ddb_index, ddb_entry));

	वापस ddb_entry;
पूर्ण

अटल अंतरभूत व्योम
__qla4xxx_enable_पूर्णांकrs(काष्ठा scsi_qla_host *ha)
अणु
	अगर (is_qla4022(ha) | is_qla4032(ha)) अणु
		ग_लिखोl(set_rmask(IMR_SCSI_INTR_ENABLE),
		       &ha->reg->u1.isp4022.पूर्णांकr_mask);
		पढ़ोl(&ha->reg->u1.isp4022.पूर्णांकr_mask);
	पूर्ण अन्यथा अणु
		ग_लिखोl(set_rmask(CSR_SCSI_INTR_ENABLE), &ha->reg->ctrl_status);
		पढ़ोl(&ha->reg->ctrl_status);
	पूर्ण
	set_bit(AF_INTERRUPTS_ON, &ha->flags);
पूर्ण

अटल अंतरभूत व्योम
__qla4xxx_disable_पूर्णांकrs(काष्ठा scsi_qla_host *ha)
अणु
	अगर (is_qla4022(ha) | is_qla4032(ha)) अणु
		ग_लिखोl(clr_rmask(IMR_SCSI_INTR_ENABLE),
		       &ha->reg->u1.isp4022.पूर्णांकr_mask);
		पढ़ोl(&ha->reg->u1.isp4022.पूर्णांकr_mask);
	पूर्ण अन्यथा अणु
		ग_लिखोl(clr_rmask(CSR_SCSI_INTR_ENABLE), &ha->reg->ctrl_status);
		पढ़ोl(&ha->reg->ctrl_status);
	पूर्ण
	clear_bit(AF_INTERRUPTS_ON, &ha->flags);
पूर्ण

अटल अंतरभूत व्योम
qla4xxx_enable_पूर्णांकrs(काष्ठा scsi_qla_host *ha)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ha->hardware_lock, flags);
	__qla4xxx_enable_पूर्णांकrs(ha);
	spin_unlock_irqrestore(&ha->hardware_lock, flags);
पूर्ण

अटल अंतरभूत व्योम
qla4xxx_disable_पूर्णांकrs(काष्ठा scsi_qla_host *ha)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ha->hardware_lock, flags);
	__qla4xxx_disable_पूर्णांकrs(ha);
	spin_unlock_irqrestore(&ha->hardware_lock, flags);
पूर्ण

अटल अंतरभूत पूर्णांक qla4xxx_get_chap_type(काष्ठा ql4_chap_table *chap_entry)
अणु
	पूर्णांक type;

	अगर (chap_entry->flags & BIT_7)
		type = LOCAL_CHAP;
	अन्यथा
		type = BIDI_CHAP;

	वापस type;
पूर्ण
