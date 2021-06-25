<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * QLogic iSCSI HBA Driver
 * Copyright (c)  2003-2013 QLogic Corporation
 */

#समावेश "ql4_def.h"
#समावेश "ql4_glbl.h"
#समावेश "ql4_dbg.h"
#समावेश "ql4_inline.h"

अटल अंतरभूत व्योम eeprom_cmd(uपूर्णांक32_t cmd, काष्ठा scsi_qla_host *ha)
अणु
	ग_लिखोl(cmd, isp_nvram(ha));
	पढ़ोl(isp_nvram(ha));
	udelay(1);
पूर्ण

अटल अंतरभूत पूर्णांक eeprom_size(काष्ठा scsi_qla_host *ha)
अणु
	वापस is_qla4010(ha) ? FM93C66A_SIZE_16 : FM93C86A_SIZE_16;
पूर्ण

अटल अंतरभूत पूर्णांक eeprom_no_addr_bits(काष्ठा scsi_qla_host *ha)
अणु
	वापस is_qla4010(ha) ? FM93C56A_NO_ADDR_BITS_16 :
		FM93C86A_NO_ADDR_BITS_16 ;
पूर्ण

अटल अंतरभूत पूर्णांक eeprom_no_data_bits(काष्ठा scsi_qla_host *ha)
अणु
	वापस FM93C56A_DATA_BITS_16;
पूर्ण

अटल पूर्णांक fm93c56a_select(काष्ठा scsi_qla_host * ha)
अणु
	DEBUG5(prपूर्णांकk(KERN_ERR "fm93c56a_select:\n"));

	ha->eeprom_cmd_data = AUBURN_EEPROM_CS_1 | 0x000f0000;
	eeprom_cmd(ha->eeprom_cmd_data, ha);
	वापस 1;
पूर्ण

अटल पूर्णांक fm93c56a_cmd(काष्ठा scsi_qla_host * ha, पूर्णांक cmd, पूर्णांक addr)
अणु
	पूर्णांक i;
	पूर्णांक mask;
	पूर्णांक dataBit;
	पूर्णांक previousBit;

	/* Clock in a zero, then करो the start bit. */
	eeprom_cmd(ha->eeprom_cmd_data | AUBURN_EEPROM_DO_1, ha);

	eeprom_cmd(ha->eeprom_cmd_data | AUBURN_EEPROM_DO_1 |
	       AUBURN_EEPROM_CLK_RISE, ha);
	eeprom_cmd(ha->eeprom_cmd_data | AUBURN_EEPROM_DO_1 |
	       AUBURN_EEPROM_CLK_FALL, ha);

	mask = 1 << (FM93C56A_CMD_BITS - 1);

	/* Force the previous data bit to be dअगरferent. */
	previousBit = 0xffff;
	क्रम (i = 0; i < FM93C56A_CMD_BITS; i++) अणु
		dataBit =
			(cmd & mask) ? AUBURN_EEPROM_DO_1 : AUBURN_EEPROM_DO_0;
		अगर (previousBit != dataBit) अणु

			/*
			 * If the bit changed, then change the DO state to
			 * match.
			 */
			eeprom_cmd(ha->eeprom_cmd_data | dataBit, ha);
			previousBit = dataBit;
		पूर्ण
		eeprom_cmd(ha->eeprom_cmd_data | dataBit |
		       AUBURN_EEPROM_CLK_RISE, ha);
		eeprom_cmd(ha->eeprom_cmd_data | dataBit |
		       AUBURN_EEPROM_CLK_FALL, ha);

		cmd = cmd << 1;
	पूर्ण
	mask = 1 << (eeprom_no_addr_bits(ha) - 1);

	/* Force the previous data bit to be dअगरferent. */
	previousBit = 0xffff;
	क्रम (i = 0; i < eeprom_no_addr_bits(ha); i++) अणु
		dataBit = addr & mask ? AUBURN_EEPROM_DO_1 :
			AUBURN_EEPROM_DO_0;
		अगर (previousBit != dataBit) अणु
			/*
			 * If the bit changed, then change the DO state to
			 * match.
			 */
			eeprom_cmd(ha->eeprom_cmd_data | dataBit, ha);

			previousBit = dataBit;
		पूर्ण
		eeprom_cmd(ha->eeprom_cmd_data | dataBit |
		       AUBURN_EEPROM_CLK_RISE, ha);
		eeprom_cmd(ha->eeprom_cmd_data | dataBit |
		       AUBURN_EEPROM_CLK_FALL, ha);

		addr = addr << 1;
	पूर्ण
	वापस 1;
पूर्ण

अटल पूर्णांक fm93c56a_deselect(काष्ठा scsi_qla_host * ha)
अणु
	ha->eeprom_cmd_data = AUBURN_EEPROM_CS_0 | 0x000f0000;
	eeprom_cmd(ha->eeprom_cmd_data, ha);
	वापस 1;
पूर्ण

अटल पूर्णांक fm93c56a_datain(काष्ठा scsi_qla_host * ha, अचिन्हित लघु *value)
अणु
	पूर्णांक i;
	पूर्णांक data = 0;
	पूर्णांक dataBit;

	/* Read the data bits
	 * The first bit is a dummy.  Clock right over it. */
	क्रम (i = 0; i < eeprom_no_data_bits(ha); i++) अणु
		eeprom_cmd(ha->eeprom_cmd_data |
		       AUBURN_EEPROM_CLK_RISE, ha);
		eeprom_cmd(ha->eeprom_cmd_data |
		       AUBURN_EEPROM_CLK_FALL, ha);

		dataBit = (पढ़ोw(isp_nvram(ha)) & AUBURN_EEPROM_DI_1) ? 1 : 0;

		data = (data << 1) | dataBit;
	पूर्ण

	*value = data;
	वापस 1;
पूर्ण

अटल पूर्णांक eeprom_पढ़ोword(पूर्णांक eepromAddr, u16 * value,
			   काष्ठा scsi_qla_host * ha)
अणु
	fm93c56a_select(ha);
	fm93c56a_cmd(ha, FM93C56A_READ, eepromAddr);
	fm93c56a_datain(ha, value);
	fm93c56a_deselect(ha);
	वापस 1;
पूर्ण

/* Hardware_lock must be set beक्रमe calling */
u16 rd_nvram_word(काष्ठा scsi_qla_host * ha, पूर्णांक offset)
अणु
	u16 val = 0;

	/* NOTE: NVRAM uses half-word addresses */
	eeprom_पढ़ोword(offset, &val, ha);
	वापस val;
पूर्ण

u8 rd_nvram_byte(काष्ठा scsi_qla_host *ha, पूर्णांक offset)
अणु
	u16 val = 0;
	u8 rval = 0;
	पूर्णांक index = 0;

	अगर (offset & 0x1)
		index = (offset - 1) / 2;
	अन्यथा
		index = offset / 2;

	val = le16_to_cpu(rd_nvram_word(ha, index));

	अगर (offset & 0x1)
		rval = (u8)((val & 0xff00) >> 8);
	अन्यथा
		rval = (u8)((val & 0x00ff));

	वापस rval;
पूर्ण

पूर्णांक qla4xxx_is_nvram_configuration_valid(काष्ठा scsi_qla_host * ha)
अणु
	पूर्णांक status = QLA_ERROR;
	uपूर्णांक16_t checksum = 0;
	uपूर्णांक32_t index;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ha->hardware_lock, flags);
	क्रम (index = 0; index < eeprom_size(ha); index++)
		checksum += rd_nvram_word(ha, index);
	spin_unlock_irqrestore(&ha->hardware_lock, flags);

	अगर (checksum == 0)
		status = QLA_SUCCESS;

	वापस status;
पूर्ण

/*************************************************************************
 *
 *			Hardware Semaphore routines
 *
 *************************************************************************/
पूर्णांक ql4xxx_sem_spinlock(काष्ठा scsi_qla_host * ha, u32 sem_mask, u32 sem_bits)
अणु
	uपूर्णांक32_t value;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक seconds = 30;

	DEBUG2(prपूर्णांकk("scsi%ld : Trying to get SEM lock - mask= 0x%x, code = "
		      "0x%x\n", ha->host_no, sem_mask, sem_bits));
	करो अणु
		spin_lock_irqsave(&ha->hardware_lock, flags);
		ग_लिखोl((sem_mask | sem_bits), isp_semaphore(ha));
		value = पढ़ोw(isp_semaphore(ha));
		spin_unlock_irqrestore(&ha->hardware_lock, flags);
		अगर ((value & (sem_mask >> 16)) == sem_bits) अणु
			DEBUG2(prपूर्णांकk("scsi%ld : Got SEM LOCK - mask= 0x%x, "
				      "code = 0x%x\n", ha->host_no,
				      sem_mask, sem_bits));
			वापस QLA_SUCCESS;
		पूर्ण
		ssleep(1);
	पूर्ण जबतक (--seconds);
	वापस QLA_ERROR;
पूर्ण

व्योम ql4xxx_sem_unlock(काष्ठा scsi_qla_host * ha, u32 sem_mask)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ha->hardware_lock, flags);
	ग_लिखोl(sem_mask, isp_semaphore(ha));
	पढ़ोl(isp_semaphore(ha));
	spin_unlock_irqrestore(&ha->hardware_lock, flags);

	DEBUG2(prपूर्णांकk("scsi%ld : UNLOCK SEM - mask= 0x%x\n", ha->host_no,
		      sem_mask));
पूर्ण

पूर्णांक ql4xxx_sem_lock(काष्ठा scsi_qla_host * ha, u32 sem_mask, u32 sem_bits)
अणु
	uपूर्णांक32_t value;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ha->hardware_lock, flags);
	ग_लिखोl((sem_mask | sem_bits), isp_semaphore(ha));
	value = पढ़ोw(isp_semaphore(ha));
	spin_unlock_irqrestore(&ha->hardware_lock, flags);
	अगर ((value & (sem_mask >> 16)) == sem_bits) अणु
		DEBUG2(prपूर्णांकk("scsi%ld : Got SEM LOCK - mask= 0x%x, code = "
			      "0x%x, sema code=0x%x\n", ha->host_no,
			      sem_mask, sem_bits, value));
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण
