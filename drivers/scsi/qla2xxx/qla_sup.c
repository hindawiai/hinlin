<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * QLogic Fibre Channel HBA Driver
 * Copyright (c)  2003-2014 QLogic Corporation
 */
#समावेश "qla_def.h"

#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/uaccess.h>

/*
 * NVRAM support routines
 */

/**
 * qla2x00_lock_nvram_access() -
 * @ha: HA context
 */
अटल व्योम
qla2x00_lock_nvram_access(काष्ठा qla_hw_data *ha)
अणु
	uपूर्णांक16_t data;
	काष्ठा device_reg_2xxx __iomem *reg = &ha->iobase->isp;

	अगर (!IS_QLA2100(ha) && !IS_QLA2200(ha) && !IS_QLA2300(ha)) अणु
		data = rd_reg_word(&reg->nvram);
		जबतक (data & NVR_BUSY) अणु
			udelay(100);
			data = rd_reg_word(&reg->nvram);
		पूर्ण

		/* Lock resource */
		wrt_reg_word(&reg->u.isp2300.host_semaphore, 0x1);
		rd_reg_word(&reg->u.isp2300.host_semaphore);
		udelay(5);
		data = rd_reg_word(&reg->u.isp2300.host_semaphore);
		जबतक ((data & BIT_0) == 0) अणु
			/* Lock failed */
			udelay(100);
			wrt_reg_word(&reg->u.isp2300.host_semaphore, 0x1);
			rd_reg_word(&reg->u.isp2300.host_semaphore);
			udelay(5);
			data = rd_reg_word(&reg->u.isp2300.host_semaphore);
		पूर्ण
	पूर्ण
पूर्ण

/**
 * qla2x00_unlock_nvram_access() -
 * @ha: HA context
 */
अटल व्योम
qla2x00_unlock_nvram_access(काष्ठा qla_hw_data *ha)
अणु
	काष्ठा device_reg_2xxx __iomem *reg = &ha->iobase->isp;

	अगर (!IS_QLA2100(ha) && !IS_QLA2200(ha) && !IS_QLA2300(ha)) अणु
		wrt_reg_word(&reg->u.isp2300.host_semaphore, 0);
		rd_reg_word(&reg->u.isp2300.host_semaphore);
	पूर्ण
पूर्ण

/**
 * qla2x00_nv_ग_लिखो() - Prepare क्रम NVRAM पढ़ो/ग_लिखो operation.
 * @ha: HA context
 * @data: Serial पूर्णांकerface selector
 */
अटल व्योम
qla2x00_nv_ग_लिखो(काष्ठा qla_hw_data *ha, uपूर्णांक16_t data)
अणु
	काष्ठा device_reg_2xxx __iomem *reg = &ha->iobase->isp;

	wrt_reg_word(&reg->nvram, data | NVR_SELECT | NVR_WRT_ENABLE);
	rd_reg_word(&reg->nvram);		/* PCI Posting. */
	NVRAM_DELAY();
	wrt_reg_word(&reg->nvram, data | NVR_SELECT | NVR_CLOCK |
	    NVR_WRT_ENABLE);
	rd_reg_word(&reg->nvram);		/* PCI Posting. */
	NVRAM_DELAY();
	wrt_reg_word(&reg->nvram, data | NVR_SELECT | NVR_WRT_ENABLE);
	rd_reg_word(&reg->nvram);		/* PCI Posting. */
	NVRAM_DELAY();
पूर्ण

/**
 * qla2x00_nvram_request() - Sends पढ़ो command to NVRAM and माला_लो data from
 *	NVRAM.
 * @ha: HA context
 * @nv_cmd: NVRAM command
 *
 * Bit definitions क्रम NVRAM command:
 *
 *	Bit 26     = start bit
 *	Bit 25, 24 = opcode
 *	Bit 23-16  = address
 *	Bit 15-0   = ग_लिखो data
 *
 * Returns the word पढ़ो from nvram @addr.
 */
अटल uपूर्णांक16_t
qla2x00_nvram_request(काष्ठा qla_hw_data *ha, uपूर्णांक32_t nv_cmd)
अणु
	uपूर्णांक8_t		cnt;
	काष्ठा device_reg_2xxx __iomem *reg = &ha->iobase->isp;
	uपूर्णांक16_t	data = 0;
	uपूर्णांक16_t	reg_data;

	/* Send command to NVRAM. */
	nv_cmd <<= 5;
	क्रम (cnt = 0; cnt < 11; cnt++) अणु
		अगर (nv_cmd & BIT_31)
			qla2x00_nv_ग_लिखो(ha, NVR_DATA_OUT);
		अन्यथा
			qla2x00_nv_ग_लिखो(ha, 0);
		nv_cmd <<= 1;
	पूर्ण

	/* Read data from NVRAM. */
	क्रम (cnt = 0; cnt < 16; cnt++) अणु
		wrt_reg_word(&reg->nvram, NVR_SELECT | NVR_CLOCK);
		rd_reg_word(&reg->nvram);	/* PCI Posting. */
		NVRAM_DELAY();
		data <<= 1;
		reg_data = rd_reg_word(&reg->nvram);
		अगर (reg_data & NVR_DATA_IN)
			data |= BIT_0;
		wrt_reg_word(&reg->nvram, NVR_SELECT);
		rd_reg_word(&reg->nvram);	/* PCI Posting. */
		NVRAM_DELAY();
	पूर्ण

	/* Deselect chip. */
	wrt_reg_word(&reg->nvram, NVR_DESELECT);
	rd_reg_word(&reg->nvram);		/* PCI Posting. */
	NVRAM_DELAY();

	वापस data;
पूर्ण


/**
 * qla2x00_get_nvram_word() - Calculates word position in NVRAM and calls the
 *	request routine to get the word from NVRAM.
 * @ha: HA context
 * @addr: Address in NVRAM to पढ़ो
 *
 * Returns the word पढ़ो from nvram @addr.
 */
अटल uपूर्णांक16_t
qla2x00_get_nvram_word(काष्ठा qla_hw_data *ha, uपूर्णांक32_t addr)
अणु
	uपूर्णांक16_t	data;
	uपूर्णांक32_t	nv_cmd;

	nv_cmd = addr << 16;
	nv_cmd |= NV_READ_OP;
	data = qla2x00_nvram_request(ha, nv_cmd);

	वापस (data);
पूर्ण

/**
 * qla2x00_nv_deselect() - Deselect NVRAM operations.
 * @ha: HA context
 */
अटल व्योम
qla2x00_nv_deselect(काष्ठा qla_hw_data *ha)
अणु
	काष्ठा device_reg_2xxx __iomem *reg = &ha->iobase->isp;

	wrt_reg_word(&reg->nvram, NVR_DESELECT);
	rd_reg_word(&reg->nvram);		/* PCI Posting. */
	NVRAM_DELAY();
पूर्ण

/**
 * qla2x00_ग_लिखो_nvram_word() - Write NVRAM data.
 * @ha: HA context
 * @addr: Address in NVRAM to ग_लिखो
 * @data: word to program
 */
अटल व्योम
qla2x00_ग_लिखो_nvram_word(काष्ठा qla_hw_data *ha, uपूर्णांक32_t addr, __le16 data)
अणु
	पूर्णांक count;
	uपूर्णांक16_t word;
	uपूर्णांक32_t nv_cmd, रुको_cnt;
	काष्ठा device_reg_2xxx __iomem *reg = &ha->iobase->isp;
	scsi_qla_host_t *vha = pci_get_drvdata(ha->pdev);

	qla2x00_nv_ग_लिखो(ha, NVR_DATA_OUT);
	qla2x00_nv_ग_लिखो(ha, 0);
	qla2x00_nv_ग_लिखो(ha, 0);

	क्रम (word = 0; word < 8; word++)
		qla2x00_nv_ग_लिखो(ha, NVR_DATA_OUT);

	qla2x00_nv_deselect(ha);

	/* Write data */
	nv_cmd = (addr << 16) | NV_WRITE_OP;
	nv_cmd |= (__क्रमce u16)data;
	nv_cmd <<= 5;
	क्रम (count = 0; count < 27; count++) अणु
		अगर (nv_cmd & BIT_31)
			qla2x00_nv_ग_लिखो(ha, NVR_DATA_OUT);
		अन्यथा
			qla2x00_nv_ग_लिखो(ha, 0);

		nv_cmd <<= 1;
	पूर्ण

	qla2x00_nv_deselect(ha);

	/* Wait क्रम NVRAM to become पढ़ोy */
	wrt_reg_word(&reg->nvram, NVR_SELECT);
	rd_reg_word(&reg->nvram);		/* PCI Posting. */
	रुको_cnt = NVR_WAIT_CNT;
	करो अणु
		अगर (!--रुको_cnt) अणु
			ql_dbg(ql_dbg_user, vha, 0x708d,
			    "NVRAM didn't go ready...\n");
			अवरोध;
		पूर्ण
		NVRAM_DELAY();
		word = rd_reg_word(&reg->nvram);
	पूर्ण जबतक ((word & NVR_DATA_IN) == 0);

	qla2x00_nv_deselect(ha);

	/* Disable ग_लिखोs */
	qla2x00_nv_ग_लिखो(ha, NVR_DATA_OUT);
	क्रम (count = 0; count < 10; count++)
		qla2x00_nv_ग_लिखो(ha, 0);

	qla2x00_nv_deselect(ha);
पूर्ण

अटल पूर्णांक
qla2x00_ग_लिखो_nvram_word_पंचांगo(काष्ठा qla_hw_data *ha, uपूर्णांक32_t addr,
			     __le16 data, uपूर्णांक32_t पंचांगo)
अणु
	पूर्णांक ret, count;
	uपूर्णांक16_t word;
	uपूर्णांक32_t nv_cmd;
	काष्ठा device_reg_2xxx __iomem *reg = &ha->iobase->isp;

	ret = QLA_SUCCESS;

	qla2x00_nv_ग_लिखो(ha, NVR_DATA_OUT);
	qla2x00_nv_ग_लिखो(ha, 0);
	qla2x00_nv_ग_लिखो(ha, 0);

	क्रम (word = 0; word < 8; word++)
		qla2x00_nv_ग_लिखो(ha, NVR_DATA_OUT);

	qla2x00_nv_deselect(ha);

	/* Write data */
	nv_cmd = (addr << 16) | NV_WRITE_OP;
	nv_cmd |= (__क्रमce u16)data;
	nv_cmd <<= 5;
	क्रम (count = 0; count < 27; count++) अणु
		अगर (nv_cmd & BIT_31)
			qla2x00_nv_ग_लिखो(ha, NVR_DATA_OUT);
		अन्यथा
			qla2x00_nv_ग_लिखो(ha, 0);

		nv_cmd <<= 1;
	पूर्ण

	qla2x00_nv_deselect(ha);

	/* Wait क्रम NVRAM to become पढ़ोy */
	wrt_reg_word(&reg->nvram, NVR_SELECT);
	rd_reg_word(&reg->nvram);		/* PCI Posting. */
	करो अणु
		NVRAM_DELAY();
		word = rd_reg_word(&reg->nvram);
		अगर (!--पंचांगo) अणु
			ret = QLA_FUNCTION_FAILED;
			अवरोध;
		पूर्ण
	पूर्ण जबतक ((word & NVR_DATA_IN) == 0);

	qla2x00_nv_deselect(ha);

	/* Disable ग_लिखोs */
	qla2x00_nv_ग_लिखो(ha, NVR_DATA_OUT);
	क्रम (count = 0; count < 10; count++)
		qla2x00_nv_ग_लिखो(ha, 0);

	qla2x00_nv_deselect(ha);

	वापस ret;
पूर्ण

/**
 * qla2x00_clear_nvram_protection() -
 * @ha: HA context
 */
अटल पूर्णांक
qla2x00_clear_nvram_protection(काष्ठा qla_hw_data *ha)
अणु
	पूर्णांक ret, stat;
	काष्ठा device_reg_2xxx __iomem *reg = &ha->iobase->isp;
	uपूर्णांक32_t word, रुको_cnt;
	__le16 wprot, wprot_old;
	scsi_qla_host_t *vha = pci_get_drvdata(ha->pdev);

	/* Clear NVRAM ग_लिखो protection. */
	ret = QLA_FUNCTION_FAILED;

	wprot_old = cpu_to_le16(qla2x00_get_nvram_word(ha, ha->nvram_base));
	stat = qla2x00_ग_लिखो_nvram_word_पंचांगo(ha, ha->nvram_base,
					    cpu_to_le16(0x1234), 100000);
	wprot = cpu_to_le16(qla2x00_get_nvram_word(ha, ha->nvram_base));
	अगर (stat != QLA_SUCCESS || wprot != cpu_to_le16(0x1234)) अणु
		/* Write enable. */
		qla2x00_nv_ग_लिखो(ha, NVR_DATA_OUT);
		qla2x00_nv_ग_लिखो(ha, 0);
		qla2x00_nv_ग_लिखो(ha, 0);
		क्रम (word = 0; word < 8; word++)
			qla2x00_nv_ग_लिखो(ha, NVR_DATA_OUT);

		qla2x00_nv_deselect(ha);

		/* Enable protection रेजिस्टर. */
		qla2x00_nv_ग_लिखो(ha, NVR_PR_ENABLE | NVR_DATA_OUT);
		qla2x00_nv_ग_लिखो(ha, NVR_PR_ENABLE);
		qla2x00_nv_ग_लिखो(ha, NVR_PR_ENABLE);
		क्रम (word = 0; word < 8; word++)
			qla2x00_nv_ग_लिखो(ha, NVR_DATA_OUT | NVR_PR_ENABLE);

		qla2x00_nv_deselect(ha);

		/* Clear protection रेजिस्टर (ffff is cleared). */
		qla2x00_nv_ग_लिखो(ha, NVR_PR_ENABLE | NVR_DATA_OUT);
		qla2x00_nv_ग_लिखो(ha, NVR_PR_ENABLE | NVR_DATA_OUT);
		qla2x00_nv_ग_लिखो(ha, NVR_PR_ENABLE | NVR_DATA_OUT);
		क्रम (word = 0; word < 8; word++)
			qla2x00_nv_ग_लिखो(ha, NVR_DATA_OUT | NVR_PR_ENABLE);

		qla2x00_nv_deselect(ha);

		/* Wait क्रम NVRAM to become पढ़ोy. */
		wrt_reg_word(&reg->nvram, NVR_SELECT);
		rd_reg_word(&reg->nvram);	/* PCI Posting. */
		रुको_cnt = NVR_WAIT_CNT;
		करो अणु
			अगर (!--रुको_cnt) अणु
				ql_dbg(ql_dbg_user, vha, 0x708e,
				    "NVRAM didn't go ready...\n");
				अवरोध;
			पूर्ण
			NVRAM_DELAY();
			word = rd_reg_word(&reg->nvram);
		पूर्ण जबतक ((word & NVR_DATA_IN) == 0);

		अगर (रुको_cnt)
			ret = QLA_SUCCESS;
	पूर्ण अन्यथा
		qla2x00_ग_लिखो_nvram_word(ha, ha->nvram_base, wprot_old);

	वापस ret;
पूर्ण

अटल व्योम
qla2x00_set_nvram_protection(काष्ठा qla_hw_data *ha, पूर्णांक stat)
अणु
	काष्ठा device_reg_2xxx __iomem *reg = &ha->iobase->isp;
	uपूर्णांक32_t word, रुको_cnt;
	scsi_qla_host_t *vha = pci_get_drvdata(ha->pdev);

	अगर (stat != QLA_SUCCESS)
		वापस;

	/* Set NVRAM ग_लिखो protection. */
	/* Write enable. */
	qla2x00_nv_ग_लिखो(ha, NVR_DATA_OUT);
	qla2x00_nv_ग_लिखो(ha, 0);
	qla2x00_nv_ग_लिखो(ha, 0);
	क्रम (word = 0; word < 8; word++)
		qla2x00_nv_ग_लिखो(ha, NVR_DATA_OUT);

	qla2x00_nv_deselect(ha);

	/* Enable protection रेजिस्टर. */
	qla2x00_nv_ग_लिखो(ha, NVR_PR_ENABLE | NVR_DATA_OUT);
	qla2x00_nv_ग_लिखो(ha, NVR_PR_ENABLE);
	qla2x00_nv_ग_लिखो(ha, NVR_PR_ENABLE);
	क्रम (word = 0; word < 8; word++)
		qla2x00_nv_ग_लिखो(ha, NVR_DATA_OUT | NVR_PR_ENABLE);

	qla2x00_nv_deselect(ha);

	/* Enable protection रेजिस्टर. */
	qla2x00_nv_ग_लिखो(ha, NVR_PR_ENABLE | NVR_DATA_OUT);
	qla2x00_nv_ग_लिखो(ha, NVR_PR_ENABLE);
	qla2x00_nv_ग_लिखो(ha, NVR_PR_ENABLE | NVR_DATA_OUT);
	क्रम (word = 0; word < 8; word++)
		qla2x00_nv_ग_लिखो(ha, NVR_PR_ENABLE);

	qla2x00_nv_deselect(ha);

	/* Wait क्रम NVRAM to become पढ़ोy. */
	wrt_reg_word(&reg->nvram, NVR_SELECT);
	rd_reg_word(&reg->nvram);		/* PCI Posting. */
	रुको_cnt = NVR_WAIT_CNT;
	करो अणु
		अगर (!--रुको_cnt) अणु
			ql_dbg(ql_dbg_user, vha, 0x708f,
			    "NVRAM didn't go ready...\n");
			अवरोध;
		पूर्ण
		NVRAM_DELAY();
		word = rd_reg_word(&reg->nvram);
	पूर्ण जबतक ((word & NVR_DATA_IN) == 0);
पूर्ण


/*****************************************************************************/
/* Flash Manipulation Routines                                               */
/*****************************************************************************/

अटल अंतरभूत uपूर्णांक32_t
flash_conf_addr(काष्ठा qla_hw_data *ha, uपूर्णांक32_t faddr)
अणु
	वापस ha->flash_conf_off + faddr;
पूर्ण

अटल अंतरभूत uपूर्णांक32_t
flash_data_addr(काष्ठा qla_hw_data *ha, uपूर्णांक32_t faddr)
अणु
	वापस ha->flash_data_off + faddr;
पूर्ण

अटल अंतरभूत uपूर्णांक32_t
nvram_conf_addr(काष्ठा qla_hw_data *ha, uपूर्णांक32_t naddr)
अणु
	वापस ha->nvram_conf_off + naddr;
पूर्ण

अटल अंतरभूत uपूर्णांक32_t
nvram_data_addr(काष्ठा qla_hw_data *ha, uपूर्णांक32_t naddr)
अणु
	वापस ha->nvram_data_off + naddr;
पूर्ण

अटल पूर्णांक
qla24xx_पढ़ो_flash_dword(काष्ठा qla_hw_data *ha, uपूर्णांक32_t addr, uपूर्णांक32_t *data)
अणु
	काष्ठा device_reg_24xx __iomem *reg = &ha->iobase->isp24;
	uदीर्घ cnt = 30000;

	wrt_reg_dword(&reg->flash_addr, addr & ~FARX_DATA_FLAG);

	जबतक (cnt--) अणु
		अगर (rd_reg_dword(&reg->flash_addr) & FARX_DATA_FLAG) अणु
			*data = rd_reg_dword(&reg->flash_data);
			वापस QLA_SUCCESS;
		पूर्ण
		udelay(10);
		cond_resched();
	पूर्ण

	ql_log(ql_log_warn, pci_get_drvdata(ha->pdev), 0x7090,
	    "Flash read dword at %x timeout.\n", addr);
	*data = 0xDEADDEAD;
	वापस QLA_FUNCTION_TIMEOUT;
पूर्ण

पूर्णांक
qla24xx_पढ़ो_flash_data(scsi_qla_host_t *vha, uपूर्णांक32_t *dwptr, uपूर्णांक32_t faddr,
    uपूर्णांक32_t dwords)
अणु
	uदीर्घ i;
	पूर्णांक ret = QLA_SUCCESS;
	काष्ठा qla_hw_data *ha = vha->hw;

	/* Dword पढ़ोs to flash. */
	faddr =  flash_data_addr(ha, faddr);
	क्रम (i = 0; i < dwords; i++, faddr++, dwptr++) अणु
		ret = qla24xx_पढ़ो_flash_dword(ha, faddr, dwptr);
		अगर (ret != QLA_SUCCESS)
			अवरोध;
		cpu_to_le32s(dwptr);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक
qla24xx_ग_लिखो_flash_dword(काष्ठा qla_hw_data *ha, uपूर्णांक32_t addr, uपूर्णांक32_t data)
अणु
	काष्ठा device_reg_24xx __iomem *reg = &ha->iobase->isp24;
	uदीर्घ cnt = 500000;

	wrt_reg_dword(&reg->flash_data, data);
	wrt_reg_dword(&reg->flash_addr, addr | FARX_DATA_FLAG);

	जबतक (cnt--) अणु
		अगर (!(rd_reg_dword(&reg->flash_addr) & FARX_DATA_FLAG))
			वापस QLA_SUCCESS;
		udelay(10);
		cond_resched();
	पूर्ण

	ql_log(ql_log_warn, pci_get_drvdata(ha->pdev), 0x7090,
	    "Flash write dword at %x timeout.\n", addr);
	वापस QLA_FUNCTION_TIMEOUT;
पूर्ण

अटल व्योम
qla24xx_get_flash_manufacturer(काष्ठा qla_hw_data *ha, uपूर्णांक8_t *man_id,
    uपूर्णांक8_t *flash_id)
अणु
	uपूर्णांक32_t faddr, ids = 0;

	*man_id = *flash_id = 0;

	faddr = flash_conf_addr(ha, 0x03ab);
	अगर (!qla24xx_पढ़ो_flash_dword(ha, faddr, &ids)) अणु
		*man_id = LSB(ids);
		*flash_id = MSB(ids);
	पूर्ण

	/* Check अगर man_id and flash_id are valid. */
	अगर (ids != 0xDEADDEAD && (*man_id == 0 || *flash_id == 0)) अणु
		/* Read inक्रमmation using 0x9f opcode
		 * Device ID, Mfg ID would be पढ़ो in the क्रमmat:
		 *   <Ext Dev Info><Device ID Part2><Device ID Part 1><Mfg ID>
		 * Example: ATMEL 0x00 01 45 1F
		 * Extract MFG and Dev ID from last two bytes.
		 */
		faddr = flash_conf_addr(ha, 0x009f);
		अगर (!qla24xx_पढ़ो_flash_dword(ha, faddr, &ids)) अणु
			*man_id = LSB(ids);
			*flash_id = MSB(ids);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक
qla2xxx_find_flt_start(scsi_qla_host_t *vha, uपूर्णांक32_t *start)
अणु
	स्थिर अक्षर *loc, *locations[] = अणु "DEF", "PCI" पूर्ण;
	uपूर्णांक32_t pcihdr, pcids;
	uपूर्णांक16_t cnt, chksum;
	__le16 *wptr;
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा req_que *req = ha->req_q_map[0];
	काष्ठा qla_flt_location *fltl = (व्योम *)req->ring;
	uपूर्णांक32_t *dcode = (uपूर्णांक32_t *)req->ring;
	uपूर्णांक8_t *buf = (व्योम *)req->ring, *bcode,  last_image;

	/*
	 * FLT-location काष्ठाure resides after the last PCI region.
	 */

	/* Begin with sane शेषs. */
	loc = locations[0];
	*start = 0;
	अगर (IS_QLA24XX_TYPE(ha))
		*start = FA_FLASH_LAYOUT_ADDR_24;
	अन्यथा अगर (IS_QLA25XX(ha))
		*start = FA_FLASH_LAYOUT_ADDR;
	अन्यथा अगर (IS_QLA81XX(ha))
		*start = FA_FLASH_LAYOUT_ADDR_81;
	अन्यथा अगर (IS_P3P_TYPE(ha)) अणु
		*start = FA_FLASH_LAYOUT_ADDR_82;
		जाओ end;
	पूर्ण अन्यथा अगर (IS_QLA83XX(ha) || IS_QLA27XX(ha)) अणु
		*start = FA_FLASH_LAYOUT_ADDR_83;
		जाओ end;
	पूर्ण अन्यथा अगर (IS_QLA28XX(ha)) अणु
		*start = FA_FLASH_LAYOUT_ADDR_28;
		जाओ end;
	पूर्ण

	/* Begin with first PCI expansion ROM header. */
	pcihdr = 0;
	करो अणु
		/* Verअगरy PCI expansion ROM header. */
		qla24xx_पढ़ो_flash_data(vha, dcode, pcihdr >> 2, 0x20);
		bcode = buf + (pcihdr % 4);
		अगर (bcode[0x0] != 0x55 || bcode[0x1] != 0xaa)
			जाओ end;

		/* Locate PCI data काष्ठाure. */
		pcids = pcihdr + ((bcode[0x19] << 8) | bcode[0x18]);
		qla24xx_पढ़ो_flash_data(vha, dcode, pcids >> 2, 0x20);
		bcode = buf + (pcihdr % 4);

		/* Validate signature of PCI data काष्ठाure. */
		अगर (bcode[0x0] != 'P' || bcode[0x1] != 'C' ||
		    bcode[0x2] != 'I' || bcode[0x3] != 'R')
			जाओ end;

		last_image = bcode[0x15] & BIT_7;

		/* Locate next PCI expansion ROM. */
		pcihdr += ((bcode[0x11] << 8) | bcode[0x10]) * 512;
	पूर्ण जबतक (!last_image);

	/* Now verअगरy FLT-location काष्ठाure. */
	qla24xx_पढ़ो_flash_data(vha, dcode, pcihdr >> 2, माप(*fltl) >> 2);
	अगर (स_भेद(fltl->sig, "QFLT", 4))
		जाओ end;

	wptr = (__क्रमce __le16 *)req->ring;
	cnt = माप(*fltl) / माप(*wptr);
	क्रम (chksum = 0; cnt--; wptr++)
		chksum += le16_to_cpu(*wptr);
	अगर (chksum) अणु
		ql_log(ql_log_fatal, vha, 0x0045,
		    "Inconsistent FLTL detected: checksum=0x%x.\n", chksum);
		ql_dump_buffer(ql_dbg_init + ql_dbg_buffer, vha, 0x010e,
		    fltl, माप(*fltl));
		वापस QLA_FUNCTION_FAILED;
	पूर्ण

	/* Good data.  Use specअगरied location. */
	loc = locations[1];
	*start = (le16_to_cpu(fltl->start_hi) << 16 |
	    le16_to_cpu(fltl->start_lo)) >> 2;
end:
	ql_dbg(ql_dbg_init, vha, 0x0046,
	    "FLTL[%s] = 0x%x.\n",
	    loc, *start);
	वापस QLA_SUCCESS;
पूर्ण

अटल व्योम
qla2xxx_get_flt_info(scsi_qla_host_t *vha, uपूर्णांक32_t flt_addr)
अणु
	स्थिर अक्षर *locations[] = अणु "DEF", "FLT" पूर्ण, *loc = locations[1];
	स्थिर uपूर्णांक32_t def_fw[] =
		अणु FA_RISC_CODE_ADDR, FA_RISC_CODE_ADDR, FA_RISC_CODE_ADDR_81 पूर्ण;
	स्थिर uपूर्णांक32_t def_boot[] =
		अणु FA_BOOT_CODE_ADDR, FA_BOOT_CODE_ADDR, FA_BOOT_CODE_ADDR_81 पूर्ण;
	स्थिर uपूर्णांक32_t def_vpd_nvram[] =
		अणु FA_VPD_NVRAM_ADDR, FA_VPD_NVRAM_ADDR, FA_VPD_NVRAM_ADDR_81 पूर्ण;
	स्थिर uपूर्णांक32_t def_vpd0[] =
		अणु 0, 0, FA_VPD0_ADDR_81 पूर्ण;
	स्थिर uपूर्णांक32_t def_vpd1[] =
		अणु 0, 0, FA_VPD1_ADDR_81 पूर्ण;
	स्थिर uपूर्णांक32_t def_nvram0[] =
		अणु 0, 0, FA_NVRAM0_ADDR_81 पूर्ण;
	स्थिर uपूर्णांक32_t def_nvram1[] =
		अणु 0, 0, FA_NVRAM1_ADDR_81 पूर्ण;
	स्थिर uपूर्णांक32_t def_fdt[] =
		अणु FA_FLASH_DESCR_ADDR_24, FA_FLASH_DESCR_ADDR,
			FA_FLASH_DESCR_ADDR_81 पूर्ण;
	स्थिर uपूर्णांक32_t def_npiv_conf0[] =
		अणु FA_NPIV_CONF0_ADDR_24, FA_NPIV_CONF0_ADDR,
			FA_NPIV_CONF0_ADDR_81 पूर्ण;
	स्थिर uपूर्णांक32_t def_npiv_conf1[] =
		अणु FA_NPIV_CONF1_ADDR_24, FA_NPIV_CONF1_ADDR,
			FA_NPIV_CONF1_ADDR_81 पूर्ण;
	स्थिर uपूर्णांक32_t fcp_prio_cfg0[] =
		अणु FA_FCP_PRIO0_ADDR, FA_FCP_PRIO0_ADDR_25,
			0 पूर्ण;
	स्थिर uपूर्णांक32_t fcp_prio_cfg1[] =
		अणु FA_FCP_PRIO1_ADDR, FA_FCP_PRIO1_ADDR_25,
			0 पूर्ण;

	काष्ठा qla_hw_data *ha = vha->hw;
	uपूर्णांक32_t def = IS_QLA81XX(ha) ? 2 : IS_QLA25XX(ha) ? 1 : 0;
	काष्ठा qla_flt_header *flt = ha->flt;
	काष्ठा qla_flt_region *region = &flt->region[0];
	__le16 *wptr;
	uपूर्णांक16_t cnt, chksum;
	uपूर्णांक32_t start;

	/* Assign FCP prio region since older adapters may not have FLT, or
	   FCP prio region in it's FLT.
	 */
	ha->flt_region_fcp_prio = (ha->port_no == 0) ?
	    fcp_prio_cfg0[def] : fcp_prio_cfg1[def];

	ha->flt_region_flt = flt_addr;
	wptr = (__क्रमce __le16 *)ha->flt;
	ha->isp_ops->पढ़ो_optrom(vha, flt, flt_addr << 2,
	    (माप(काष्ठा qla_flt_header) + FLT_REGIONS_SIZE));

	अगर (le16_to_cpu(*wptr) == 0xffff)
		जाओ no_flash_data;
	अगर (flt->version != cpu_to_le16(1)) अणु
		ql_log(ql_log_warn, vha, 0x0047,
		    "Unsupported FLT detected: version=0x%x length=0x%x checksum=0x%x.\n",
		    le16_to_cpu(flt->version), le16_to_cpu(flt->length),
		    le16_to_cpu(flt->checksum));
		जाओ no_flash_data;
	पूर्ण

	cnt = (माप(*flt) + le16_to_cpu(flt->length)) / माप(*wptr);
	क्रम (chksum = 0; cnt--; wptr++)
		chksum += le16_to_cpu(*wptr);
	अगर (chksum) अणु
		ql_log(ql_log_fatal, vha, 0x0048,
		    "Inconsistent FLT detected: version=0x%x length=0x%x checksum=0x%x.\n",
		    le16_to_cpu(flt->version), le16_to_cpu(flt->length),
		    le16_to_cpu(flt->checksum));
		जाओ no_flash_data;
	पूर्ण

	cnt = le16_to_cpu(flt->length) / माप(*region);
	क्रम ( ; cnt; cnt--, region++) अणु
		/* Store addresses as DWORD offsets. */
		start = le32_to_cpu(region->start) >> 2;
		ql_dbg(ql_dbg_init, vha, 0x0049,
		    "FLT[%#x]: start=%#x end=%#x size=%#x.\n",
		    le16_to_cpu(region->code), start,
		    le32_to_cpu(region->end) >> 2,
		    le32_to_cpu(region->size) >> 2);
		अगर (region->attribute)
			ql_log(ql_dbg_init, vha, 0xffff,
			    "Region %x is secure\n", region->code);

		चयन (le16_to_cpu(region->code)) अणु
		हाल FLT_REG_FCOE_FW:
			अगर (!IS_QLA8031(ha))
				अवरोध;
			ha->flt_region_fw = start;
			अवरोध;
		हाल FLT_REG_FW:
			अगर (IS_QLA8031(ha))
				अवरोध;
			ha->flt_region_fw = start;
			अवरोध;
		हाल FLT_REG_BOOT_CODE:
			ha->flt_region_boot = start;
			अवरोध;
		हाल FLT_REG_VPD_0:
			अगर (IS_QLA8031(ha))
				अवरोध;
			ha->flt_region_vpd_nvram = start;
			अगर (IS_P3P_TYPE(ha))
				अवरोध;
			अगर (ha->port_no == 0)
				ha->flt_region_vpd = start;
			अवरोध;
		हाल FLT_REG_VPD_1:
			अगर (IS_P3P_TYPE(ha) || IS_QLA8031(ha))
				अवरोध;
			अगर (ha->port_no == 1)
				ha->flt_region_vpd = start;
			अवरोध;
		हाल FLT_REG_VPD_2:
			अगर (!IS_QLA27XX(ha) && !IS_QLA28XX(ha))
				अवरोध;
			अगर (ha->port_no == 2)
				ha->flt_region_vpd = start;
			अवरोध;
		हाल FLT_REG_VPD_3:
			अगर (!IS_QLA27XX(ha) && !IS_QLA28XX(ha))
				अवरोध;
			अगर (ha->port_no == 3)
				ha->flt_region_vpd = start;
			अवरोध;
		हाल FLT_REG_NVRAM_0:
			अगर (IS_QLA8031(ha))
				अवरोध;
			अगर (ha->port_no == 0)
				ha->flt_region_nvram = start;
			अवरोध;
		हाल FLT_REG_NVRAM_1:
			अगर (IS_QLA8031(ha))
				अवरोध;
			अगर (ha->port_no == 1)
				ha->flt_region_nvram = start;
			अवरोध;
		हाल FLT_REG_NVRAM_2:
			अगर (!IS_QLA27XX(ha) && !IS_QLA28XX(ha))
				अवरोध;
			अगर (ha->port_no == 2)
				ha->flt_region_nvram = start;
			अवरोध;
		हाल FLT_REG_NVRAM_3:
			अगर (!IS_QLA27XX(ha) && !IS_QLA28XX(ha))
				अवरोध;
			अगर (ha->port_no == 3)
				ha->flt_region_nvram = start;
			अवरोध;
		हाल FLT_REG_FDT:
			ha->flt_region_fdt = start;
			अवरोध;
		हाल FLT_REG_NPIV_CONF_0:
			अगर (ha->port_no == 0)
				ha->flt_region_npiv_conf = start;
			अवरोध;
		हाल FLT_REG_NPIV_CONF_1:
			अगर (ha->port_no == 1)
				ha->flt_region_npiv_conf = start;
			अवरोध;
		हाल FLT_REG_GOLD_FW:
			ha->flt_region_gold_fw = start;
			अवरोध;
		हाल FLT_REG_FCP_PRIO_0:
			अगर (ha->port_no == 0)
				ha->flt_region_fcp_prio = start;
			अवरोध;
		हाल FLT_REG_FCP_PRIO_1:
			अगर (ha->port_no == 1)
				ha->flt_region_fcp_prio = start;
			अवरोध;
		हाल FLT_REG_BOOT_CODE_82XX:
			ha->flt_region_boot = start;
			अवरोध;
		हाल FLT_REG_BOOT_CODE_8044:
			अगर (IS_QLA8044(ha))
				ha->flt_region_boot = start;
			अवरोध;
		हाल FLT_REG_FW_82XX:
			ha->flt_region_fw = start;
			अवरोध;
		हाल FLT_REG_CNA_FW:
			अगर (IS_CNA_CAPABLE(ha))
				ha->flt_region_fw = start;
			अवरोध;
		हाल FLT_REG_GOLD_FW_82XX:
			ha->flt_region_gold_fw = start;
			अवरोध;
		हाल FLT_REG_BOOTLOAD_82XX:
			ha->flt_region_bootload = start;
			अवरोध;
		हाल FLT_REG_VPD_8XXX:
			अगर (IS_CNA_CAPABLE(ha))
				ha->flt_region_vpd = start;
			अवरोध;
		हाल FLT_REG_FCOE_NVRAM_0:
			अगर (!(IS_QLA8031(ha) || IS_QLA8044(ha)))
				अवरोध;
			अगर (ha->port_no == 0)
				ha->flt_region_nvram = start;
			अवरोध;
		हाल FLT_REG_FCOE_NVRAM_1:
			अगर (!(IS_QLA8031(ha) || IS_QLA8044(ha)))
				अवरोध;
			अगर (ha->port_no == 1)
				ha->flt_region_nvram = start;
			अवरोध;
		हाल FLT_REG_IMG_PRI_27XX:
			अगर (IS_QLA27XX(ha) && !IS_QLA28XX(ha))
				ha->flt_region_img_status_pri = start;
			अवरोध;
		हाल FLT_REG_IMG_SEC_27XX:
			अगर (IS_QLA27XX(ha) || IS_QLA28XX(ha))
				ha->flt_region_img_status_sec = start;
			अवरोध;
		हाल FLT_REG_FW_SEC_27XX:
			अगर (IS_QLA27XX(ha) || IS_QLA28XX(ha))
				ha->flt_region_fw_sec = start;
			अवरोध;
		हाल FLT_REG_BOOTLOAD_SEC_27XX:
			अगर (IS_QLA27XX(ha) || IS_QLA28XX(ha))
				ha->flt_region_boot_sec = start;
			अवरोध;
		हाल FLT_REG_AUX_IMG_PRI_28XX:
			अगर (IS_QLA27XX(ha) || IS_QLA28XX(ha))
				ha->flt_region_aux_img_status_pri = start;
			अवरोध;
		हाल FLT_REG_AUX_IMG_SEC_28XX:
			अगर (IS_QLA27XX(ha) || IS_QLA28XX(ha))
				ha->flt_region_aux_img_status_sec = start;
			अवरोध;
		हाल FLT_REG_NVRAM_SEC_28XX_0:
			अगर (IS_QLA27XX(ha) || IS_QLA28XX(ha))
				अगर (ha->port_no == 0)
					ha->flt_region_nvram_sec = start;
			अवरोध;
		हाल FLT_REG_NVRAM_SEC_28XX_1:
			अगर (IS_QLA27XX(ha) || IS_QLA28XX(ha))
				अगर (ha->port_no == 1)
					ha->flt_region_nvram_sec = start;
			अवरोध;
		हाल FLT_REG_NVRAM_SEC_28XX_2:
			अगर (IS_QLA27XX(ha) || IS_QLA28XX(ha))
				अगर (ha->port_no == 2)
					ha->flt_region_nvram_sec = start;
			अवरोध;
		हाल FLT_REG_NVRAM_SEC_28XX_3:
			अगर (IS_QLA27XX(ha) || IS_QLA28XX(ha))
				अगर (ha->port_no == 3)
					ha->flt_region_nvram_sec = start;
			अवरोध;
		हाल FLT_REG_VPD_SEC_27XX_0:
		हाल FLT_REG_VPD_SEC_28XX_0:
			अगर (IS_QLA27XX(ha) || IS_QLA28XX(ha)) अणु
				ha->flt_region_vpd_nvram_sec = start;
				अगर (ha->port_no == 0)
					ha->flt_region_vpd_sec = start;
			पूर्ण
			अवरोध;
		हाल FLT_REG_VPD_SEC_27XX_1:
		हाल FLT_REG_VPD_SEC_28XX_1:
			अगर (IS_QLA27XX(ha) || IS_QLA28XX(ha))
				अगर (ha->port_no == 1)
					ha->flt_region_vpd_sec = start;
			अवरोध;
		हाल FLT_REG_VPD_SEC_27XX_2:
		हाल FLT_REG_VPD_SEC_28XX_2:
			अगर (IS_QLA27XX(ha) || IS_QLA28XX(ha))
				अगर (ha->port_no == 2)
					ha->flt_region_vpd_sec = start;
			अवरोध;
		हाल FLT_REG_VPD_SEC_27XX_3:
		हाल FLT_REG_VPD_SEC_28XX_3:
			अगर (IS_QLA27XX(ha) || IS_QLA28XX(ha))
				अगर (ha->port_no == 3)
					ha->flt_region_vpd_sec = start;
			अवरोध;
		पूर्ण
	पूर्ण
	जाओ करोne;

no_flash_data:
	/* Use hardcoded शेषs. */
	loc = locations[0];
	ha->flt_region_fw = def_fw[def];
	ha->flt_region_boot = def_boot[def];
	ha->flt_region_vpd_nvram = def_vpd_nvram[def];
	ha->flt_region_vpd = (ha->port_no == 0) ?
	    def_vpd0[def] : def_vpd1[def];
	ha->flt_region_nvram = (ha->port_no == 0) ?
	    def_nvram0[def] : def_nvram1[def];
	ha->flt_region_fdt = def_fdt[def];
	ha->flt_region_npiv_conf = (ha->port_no == 0) ?
	    def_npiv_conf0[def] : def_npiv_conf1[def];
करोne:
	ql_dbg(ql_dbg_init, vha, 0x004a,
	    "FLT[%s]: boot=0x%x fw=0x%x vpd_nvram=0x%x vpd=0x%x nvram=0x%x "
	    "fdt=0x%x flt=0x%x npiv=0x%x fcp_prif_cfg=0x%x.\n",
	    loc, ha->flt_region_boot, ha->flt_region_fw,
	    ha->flt_region_vpd_nvram, ha->flt_region_vpd, ha->flt_region_nvram,
	    ha->flt_region_fdt, ha->flt_region_flt, ha->flt_region_npiv_conf,
	    ha->flt_region_fcp_prio);
पूर्ण

अटल व्योम
qla2xxx_get_fdt_info(scsi_qla_host_t *vha)
अणु
#घोषणा FLASH_BLK_SIZE_4K	0x1000
#घोषणा FLASH_BLK_SIZE_32K	0x8000
#घोषणा FLASH_BLK_SIZE_64K	0x10000
	स्थिर अक्षर *loc, *locations[] = अणु "MID", "FDT" पूर्ण;
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा req_que *req = ha->req_q_map[0];
	uपूर्णांक16_t cnt, chksum;
	__le16 *wptr = (__क्रमce __le16 *)req->ring;
	काष्ठा qla_fdt_layout *fdt = (काष्ठा qla_fdt_layout *)req->ring;
	uपूर्णांक8_t	man_id, flash_id;
	uपूर्णांक16_t mid = 0, fid = 0;

	ha->isp_ops->पढ़ो_optrom(vha, fdt, ha->flt_region_fdt << 2,
	    OPTROM_BURST_DWORDS);
	अगर (le16_to_cpu(*wptr) == 0xffff)
		जाओ no_flash_data;
	अगर (स_भेद(fdt->sig, "QLID", 4))
		जाओ no_flash_data;

	क्रम (cnt = 0, chksum = 0; cnt < माप(*fdt) >> 1; cnt++, wptr++)
		chksum += le16_to_cpu(*wptr);
	अगर (chksum) अणु
		ql_dbg(ql_dbg_init, vha, 0x004c,
		    "Inconsistent FDT detected:"
		    " checksum=0x%x id=%c version0x%x.\n", chksum,
		    fdt->sig[0], le16_to_cpu(fdt->version));
		ql_dump_buffer(ql_dbg_init + ql_dbg_buffer, vha, 0x0113,
		    fdt, माप(*fdt));
		जाओ no_flash_data;
	पूर्ण

	loc = locations[1];
	mid = le16_to_cpu(fdt->man_id);
	fid = le16_to_cpu(fdt->id);
	ha->fdt_wrt_disable = fdt->wrt_disable_bits;
	ha->fdt_wrt_enable = fdt->wrt_enable_bits;
	ha->fdt_wrt_sts_reg_cmd = fdt->wrt_sts_reg_cmd;
	अगर (IS_QLA8044(ha))
		ha->fdt_erase_cmd = fdt->erase_cmd;
	अन्यथा
		ha->fdt_erase_cmd =
		    flash_conf_addr(ha, 0x0300 | fdt->erase_cmd);
	ha->fdt_block_size = le32_to_cpu(fdt->block_size);
	अगर (fdt->unprotect_sec_cmd) अणु
		ha->fdt_unprotect_sec_cmd = flash_conf_addr(ha, 0x0300 |
		    fdt->unprotect_sec_cmd);
		ha->fdt_protect_sec_cmd = fdt->protect_sec_cmd ?
		    flash_conf_addr(ha, 0x0300 | fdt->protect_sec_cmd) :
		    flash_conf_addr(ha, 0x0336);
	पूर्ण
	जाओ करोne;
no_flash_data:
	loc = locations[0];
	अगर (IS_P3P_TYPE(ha)) अणु
		ha->fdt_block_size = FLASH_BLK_SIZE_64K;
		जाओ करोne;
	पूर्ण
	qla24xx_get_flash_manufacturer(ha, &man_id, &flash_id);
	mid = man_id;
	fid = flash_id;
	ha->fdt_wrt_disable = 0x9c;
	ha->fdt_erase_cmd = flash_conf_addr(ha, 0x03d8);
	चयन (man_id) अणु
	हाल 0xbf: /* STT flash. */
		अगर (flash_id == 0x8e)
			ha->fdt_block_size = FLASH_BLK_SIZE_64K;
		अन्यथा
			ha->fdt_block_size = FLASH_BLK_SIZE_32K;

		अगर (flash_id == 0x80)
			ha->fdt_erase_cmd = flash_conf_addr(ha, 0x0352);
		अवरोध;
	हाल 0x13: /* ST M25P80. */
		ha->fdt_block_size = FLASH_BLK_SIZE_64K;
		अवरोध;
	हाल 0x1f: /* Aपंचांगel 26DF081A. */
		ha->fdt_block_size = FLASH_BLK_SIZE_4K;
		ha->fdt_erase_cmd = flash_conf_addr(ha, 0x0320);
		ha->fdt_unprotect_sec_cmd = flash_conf_addr(ha, 0x0339);
		ha->fdt_protect_sec_cmd = flash_conf_addr(ha, 0x0336);
		अवरोध;
	शेष:
		/* Default to 64 kb sector size. */
		ha->fdt_block_size = FLASH_BLK_SIZE_64K;
		अवरोध;
	पूर्ण
करोne:
	ql_dbg(ql_dbg_init, vha, 0x004d,
	    "FDT[%s]: (0x%x/0x%x) erase=0x%x "
	    "pr=%x wrtd=0x%x blk=0x%x.\n",
	    loc, mid, fid,
	    ha->fdt_erase_cmd, ha->fdt_protect_sec_cmd,
	    ha->fdt_wrt_disable, ha->fdt_block_size);

पूर्ण

अटल व्योम
qla2xxx_get_idc_param(scsi_qla_host_t *vha)
अणु
#घोषणा QLA82XX_IDC_PARAM_ADDR       0x003e885c
	__le32 *wptr;
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा req_que *req = ha->req_q_map[0];

	अगर (!(IS_P3P_TYPE(ha)))
		वापस;

	wptr = (__क्रमce __le32 *)req->ring;
	ha->isp_ops->पढ़ो_optrom(vha, req->ring, QLA82XX_IDC_PARAM_ADDR, 8);

	अगर (*wptr == cpu_to_le32(0xffffffff)) अणु
		ha->fcoe_dev_init_समयout = QLA82XX_ROM_DEV_INIT_TIMEOUT;
		ha->fcoe_reset_समयout = QLA82XX_ROM_DRV_RESET_ACK_TIMEOUT;
	पूर्ण अन्यथा अणु
		ha->fcoe_dev_init_समयout = le32_to_cpu(*wptr);
		wptr++;
		ha->fcoe_reset_समयout = le32_to_cpu(*wptr);
	पूर्ण
	ql_dbg(ql_dbg_init, vha, 0x004e,
	    "fcoe_dev_init_timeout=%d "
	    "fcoe_reset_timeout=%d.\n", ha->fcoe_dev_init_समयout,
	    ha->fcoe_reset_समयout);
	वापस;
पूर्ण

पूर्णांक
qla2xxx_get_flash_info(scsi_qla_host_t *vha)
अणु
	पूर्णांक ret;
	uपूर्णांक32_t flt_addr;
	काष्ठा qla_hw_data *ha = vha->hw;

	अगर (!IS_QLA24XX_TYPE(ha) && !IS_QLA25XX(ha) &&
	    !IS_CNA_CAPABLE(ha) && !IS_QLA2031(ha) &&
	    !IS_QLA27XX(ha) && !IS_QLA28XX(ha))
		वापस QLA_SUCCESS;

	ret = qla2xxx_find_flt_start(vha, &flt_addr);
	अगर (ret != QLA_SUCCESS)
		वापस ret;

	qla2xxx_get_flt_info(vha, flt_addr);
	qla2xxx_get_fdt_info(vha);
	qla2xxx_get_idc_param(vha);

	वापस QLA_SUCCESS;
पूर्ण

व्योम
qla2xxx_flash_npiv_conf(scsi_qla_host_t *vha)
अणु
#घोषणा NPIV_CONFIG_SIZE	(16*1024)
	व्योम *data;
	__le16 *wptr;
	uपूर्णांक16_t cnt, chksum;
	पूर्णांक i;
	काष्ठा qla_npiv_header hdr;
	काष्ठा qla_npiv_entry *entry;
	काष्ठा qla_hw_data *ha = vha->hw;

	अगर (!IS_QLA24XX_TYPE(ha) && !IS_QLA25XX(ha) &&
	    !IS_CNA_CAPABLE(ha) && !IS_QLA2031(ha))
		वापस;

	अगर (ha->flags.nic_core_reset_hdlr_active)
		वापस;

	अगर (IS_QLA8044(ha))
		वापस;

	ha->isp_ops->पढ़ो_optrom(vha, &hdr, ha->flt_region_npiv_conf << 2,
	    माप(काष्ठा qla_npiv_header));
	अगर (hdr.version == cpu_to_le16(0xffff))
		वापस;
	अगर (hdr.version != cpu_to_le16(1)) अणु
		ql_dbg(ql_dbg_user, vha, 0x7090,
		    "Unsupported NPIV-Config "
		    "detected: version=0x%x entries=0x%x checksum=0x%x.\n",
		    le16_to_cpu(hdr.version), le16_to_cpu(hdr.entries),
		    le16_to_cpu(hdr.checksum));
		वापस;
	पूर्ण

	data = kदो_स्मृति(NPIV_CONFIG_SIZE, GFP_KERNEL);
	अगर (!data) अणु
		ql_log(ql_log_warn, vha, 0x7091,
		    "Unable to allocate memory for data.\n");
		वापस;
	पूर्ण

	ha->isp_ops->पढ़ो_optrom(vha, data, ha->flt_region_npiv_conf << 2,
	    NPIV_CONFIG_SIZE);

	cnt = (माप(hdr) + le16_to_cpu(hdr.entries) * माप(*entry)) >> 1;
	क्रम (wptr = data, chksum = 0; cnt--; wptr++)
		chksum += le16_to_cpu(*wptr);
	अगर (chksum) अणु
		ql_dbg(ql_dbg_user, vha, 0x7092,
		    "Inconsistent NPIV-Config "
		    "detected: version=0x%x entries=0x%x checksum=0x%x.\n",
		    le16_to_cpu(hdr.version), le16_to_cpu(hdr.entries),
		    le16_to_cpu(hdr.checksum));
		जाओ करोne;
	पूर्ण

	entry = data + माप(काष्ठा qla_npiv_header);
	cnt = le16_to_cpu(hdr.entries);
	क्रम (i = 0; cnt; cnt--, entry++, i++) अणु
		uपूर्णांक16_t flags;
		काष्ठा fc_vport_identअगरiers vid;
		काष्ठा fc_vport *vport;

		स_नकल(&ha->npiv_info[i], entry, माप(काष्ठा qla_npiv_entry));

		flags = le16_to_cpu(entry->flags);
		अगर (flags == 0xffff)
			जारी;
		अगर ((flags & BIT_0) == 0)
			जारी;

		स_रखो(&vid, 0, माप(vid));
		vid.roles = FC_PORT_ROLE_FCP_INITIATOR;
		vid.vport_type = FC_PORTTYPE_NPIV;
		vid.disable = false;
		vid.port_name = wwn_to_u64(entry->port_name);
		vid.node_name = wwn_to_u64(entry->node_name);

		ql_dbg(ql_dbg_user, vha, 0x7093,
		    "NPIV[%02x]: wwpn=%llx wwnn=%llx vf_id=%#x Q_qos=%#x F_qos=%#x.\n",
		    cnt, vid.port_name, vid.node_name,
		    le16_to_cpu(entry->vf_id),
		    entry->q_qos, entry->f_qos);

		अगर (i < QLA_PRECONFIG_VPORTS) अणु
			vport = fc_vport_create(vha->host, 0, &vid);
			अगर (!vport)
				ql_log(ql_log_warn, vha, 0x7094,
				    "NPIV-Config Failed to create vport [%02x]: wwpn=%llx wwnn=%llx.\n",
				    cnt, vid.port_name, vid.node_name);
		पूर्ण
	पूर्ण
करोne:
	kमुक्त(data);
पूर्ण

अटल पूर्णांक
qla24xx_unprotect_flash(scsi_qla_host_t *vha)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा device_reg_24xx __iomem *reg = &ha->iobase->isp24;

	अगर (ha->flags.fac_supported)
		वापस qla81xx_fac_करो_ग_लिखो_enable(vha, 1);

	/* Enable flash ग_लिखो. */
	wrt_reg_dword(&reg->ctrl_status,
	    rd_reg_dword(&reg->ctrl_status) | CSRX_FLASH_ENABLE);
	rd_reg_dword(&reg->ctrl_status);	/* PCI Posting. */

	अगर (!ha->fdt_wrt_disable)
		जाओ करोne;

	/* Disable flash ग_लिखो-protection, first clear SR protection bit */
	qla24xx_ग_लिखो_flash_dword(ha, flash_conf_addr(ha, 0x101), 0);
	/* Then ग_लिखो zero again to clear reमुख्यing SR bits.*/
	qla24xx_ग_लिखो_flash_dword(ha, flash_conf_addr(ha, 0x101), 0);
करोne:
	वापस QLA_SUCCESS;
पूर्ण

अटल पूर्णांक
qla24xx_protect_flash(scsi_qla_host_t *vha)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा device_reg_24xx __iomem *reg = &ha->iobase->isp24;
	uदीर्घ cnt = 300;
	uपूर्णांक32_t faddr, dword;

	अगर (ha->flags.fac_supported)
		वापस qla81xx_fac_करो_ग_लिखो_enable(vha, 0);

	अगर (!ha->fdt_wrt_disable)
		जाओ skip_wrt_protect;

	/* Enable flash ग_लिखो-protection and रुको क्रम completion. */
	faddr = flash_conf_addr(ha, 0x101);
	qla24xx_ग_लिखो_flash_dword(ha, faddr, ha->fdt_wrt_disable);
	faddr = flash_conf_addr(ha, 0x5);
	जबतक (cnt--) अणु
		अगर (!qla24xx_पढ़ो_flash_dword(ha, faddr, &dword)) अणु
			अगर (!(dword & BIT_0))
				अवरोध;
		पूर्ण
		udelay(10);
	पूर्ण

skip_wrt_protect:
	/* Disable flash ग_लिखो. */
	wrt_reg_dword(&reg->ctrl_status,
	    rd_reg_dword(&reg->ctrl_status) & ~CSRX_FLASH_ENABLE);

	वापस QLA_SUCCESS;
पूर्ण

अटल पूर्णांक
qla24xx_erase_sector(scsi_qla_host_t *vha, uपूर्णांक32_t fdata)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;
	uपूर्णांक32_t start, finish;

	अगर (ha->flags.fac_supported) अणु
		start = fdata >> 2;
		finish = start + (ha->fdt_block_size >> 2) - 1;
		वापस qla81xx_fac_erase_sector(vha, flash_data_addr(ha,
		    start), flash_data_addr(ha, finish));
	पूर्ण

	वापस qla24xx_ग_लिखो_flash_dword(ha, ha->fdt_erase_cmd,
	    (fdata & 0xff00) | ((fdata << 16) & 0xff0000) |
	    ((fdata >> 16) & 0xff));
पूर्ण

अटल पूर्णांक
qla24xx_ग_लिखो_flash_data(scsi_qla_host_t *vha, __le32 *dwptr, uपूर्णांक32_t faddr,
    uपूर्णांक32_t dwords)
अणु
	पूर्णांक ret;
	uदीर्घ liter;
	uदीर्घ dburst = OPTROM_BURST_DWORDS; /* burst size in dwords */
	uपूर्णांक32_t sec_mask, rest_addr, fdata;
	dma_addr_t optrom_dma;
	व्योम *optrom = शून्य;
	काष्ठा qla_hw_data *ha = vha->hw;

	अगर (!IS_QLA25XX(ha) && !IS_QLA81XX(ha) && !IS_QLA83XX(ha) &&
	    !IS_QLA27XX(ha) && !IS_QLA28XX(ha))
		जाओ next;

	/* Allocate dma buffer क्रम burst ग_लिखो */
	optrom = dma_alloc_coherent(&ha->pdev->dev, OPTROM_BURST_SIZE,
	    &optrom_dma, GFP_KERNEL);
	अगर (!optrom) अणु
		ql_log(ql_log_warn, vha, 0x7095,
		    "Failed allocate burst (%x bytes)\n", OPTROM_BURST_SIZE);
	पूर्ण

next:
	ql_log(ql_log_warn + ql_dbg_verbose, vha, 0x7095,
	    "Unprotect flash...\n");
	ret = qla24xx_unprotect_flash(vha);
	अगर (ret) अणु
		ql_log(ql_log_warn, vha, 0x7096,
		    "Failed to unprotect flash.\n");
		जाओ करोne;
	पूर्ण

	rest_addr = (ha->fdt_block_size >> 2) - 1;
	sec_mask = ~rest_addr;
	क्रम (liter = 0; liter < dwords; liter++, faddr++, dwptr++) अणु
		fdata = (faddr & sec_mask) << 2;

		/* Are we at the beginning of a sector? */
		अगर (!(faddr & rest_addr)) अणु
			ql_log(ql_log_warn + ql_dbg_verbose, vha, 0x7095,
			    "Erase sector %#x...\n", faddr);

			ret = qla24xx_erase_sector(vha, fdata);
			अगर (ret) अणु
				ql_dbg(ql_dbg_user, vha, 0x7007,
				    "Failed to erase sector %x.\n", faddr);
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (optrom) अणु
			/* If smaller than a burst reमुख्यing */
			अगर (dwords - liter < dburst)
				dburst = dwords - liter;

			/* Copy to dma buffer */
			स_नकल(optrom, dwptr, dburst << 2);

			/* Burst ग_लिखो */
			ql_log(ql_log_warn + ql_dbg_verbose, vha, 0x7095,
			    "Write burst (%#lx dwords)...\n", dburst);
			ret = qla2x00_load_ram(vha, optrom_dma,
			    flash_data_addr(ha, faddr), dburst);
			अगर (!ret) अणु
				liter += dburst - 1;
				faddr += dburst - 1;
				dwptr += dburst - 1;
				जारी;
			पूर्ण

			ql_log(ql_log_warn, vha, 0x7097,
			    "Failed burst-write at %x (%p/%#llx)....\n",
			    flash_data_addr(ha, faddr), optrom,
			    (u64)optrom_dma);

			dma_मुक्त_coherent(&ha->pdev->dev,
			    OPTROM_BURST_SIZE, optrom, optrom_dma);
			optrom = शून्य;
			अगर (IS_QLA27XX(ha) || IS_QLA28XX(ha))
				अवरोध;
			ql_log(ql_log_warn, vha, 0x7098,
			    "Reverting to slow write...\n");
		पूर्ण

		/* Slow ग_लिखो */
		ret = qla24xx_ग_लिखो_flash_dword(ha,
		    flash_data_addr(ha, faddr), le32_to_cpu(*dwptr));
		अगर (ret) अणु
			ql_dbg(ql_dbg_user, vha, 0x7006,
			    "Failed slopw write %x (%x)\n", faddr, *dwptr);
			अवरोध;
		पूर्ण
	पूर्ण

	ql_log(ql_log_warn + ql_dbg_verbose, vha, 0x7095,
	    "Protect flash...\n");
	ret = qla24xx_protect_flash(vha);
	अगर (ret)
		ql_log(ql_log_warn, vha, 0x7099,
		    "Failed to protect flash\n");
करोne:
	अगर (optrom)
		dma_मुक्त_coherent(&ha->pdev->dev,
		    OPTROM_BURST_SIZE, optrom, optrom_dma);

	वापस ret;
पूर्ण

uपूर्णांक8_t *
qla2x00_पढ़ो_nvram_data(scsi_qla_host_t *vha, व्योम *buf, uपूर्णांक32_t naddr,
    uपूर्णांक32_t bytes)
अणु
	uपूर्णांक32_t i;
	__le16 *wptr;
	काष्ठा qla_hw_data *ha = vha->hw;

	/* Word पढ़ोs to NVRAM via रेजिस्टरs. */
	wptr = buf;
	qla2x00_lock_nvram_access(ha);
	क्रम (i = 0; i < bytes >> 1; i++, naddr++)
		wptr[i] = cpu_to_le16(qla2x00_get_nvram_word(ha,
		    naddr));
	qla2x00_unlock_nvram_access(ha);

	वापस buf;
पूर्ण

uपूर्णांक8_t *
qla24xx_पढ़ो_nvram_data(scsi_qla_host_t *vha, व्योम *buf, uपूर्णांक32_t naddr,
    uपूर्णांक32_t bytes)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;
	uपूर्णांक32_t *dwptr = buf;
	uपूर्णांक32_t i;

	अगर (IS_P3P_TYPE(ha))
		वापस  buf;

	/* Dword पढ़ोs to flash. */
	naddr = nvram_data_addr(ha, naddr);
	bytes >>= 2;
	क्रम (i = 0; i < bytes; i++, naddr++, dwptr++) अणु
		अगर (qla24xx_पढ़ो_flash_dword(ha, naddr, dwptr))
			अवरोध;
		cpu_to_le32s(dwptr);
	पूर्ण

	वापस buf;
पूर्ण

पूर्णांक
qla2x00_ग_लिखो_nvram_data(scsi_qla_host_t *vha, व्योम *buf, uपूर्णांक32_t naddr,
    uपूर्णांक32_t bytes)
अणु
	पूर्णांक ret, stat;
	uपूर्णांक32_t i;
	uपूर्णांक16_t *wptr;
	अचिन्हित दीर्घ flags;
	काष्ठा qla_hw_data *ha = vha->hw;

	ret = QLA_SUCCESS;

	spin_lock_irqsave(&ha->hardware_lock, flags);
	qla2x00_lock_nvram_access(ha);

	/* Disable NVRAM ग_लिखो-protection. */
	stat = qla2x00_clear_nvram_protection(ha);

	wptr = (uपूर्णांक16_t *)buf;
	क्रम (i = 0; i < bytes >> 1; i++, naddr++) अणु
		qla2x00_ग_लिखो_nvram_word(ha, naddr,
		    cpu_to_le16(*wptr));
		wptr++;
	पूर्ण

	/* Enable NVRAM ग_लिखो-protection. */
	qla2x00_set_nvram_protection(ha, stat);

	qla2x00_unlock_nvram_access(ha);
	spin_unlock_irqrestore(&ha->hardware_lock, flags);

	वापस ret;
पूर्ण

पूर्णांक
qla24xx_ग_लिखो_nvram_data(scsi_qla_host_t *vha, व्योम *buf, uपूर्णांक32_t naddr,
    uपूर्णांक32_t bytes)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा device_reg_24xx __iomem *reg = &ha->iobase->isp24;
	__le32 *dwptr = buf;
	uपूर्णांक32_t i;
	पूर्णांक ret;

	ret = QLA_SUCCESS;

	अगर (IS_P3P_TYPE(ha))
		वापस ret;

	/* Enable flash ग_लिखो. */
	wrt_reg_dword(&reg->ctrl_status,
	    rd_reg_dword(&reg->ctrl_status) | CSRX_FLASH_ENABLE);
	rd_reg_dword(&reg->ctrl_status);	/* PCI Posting. */

	/* Disable NVRAM ग_लिखो-protection. */
	qla24xx_ग_लिखो_flash_dword(ha, nvram_conf_addr(ha, 0x101), 0);
	qla24xx_ग_लिखो_flash_dword(ha, nvram_conf_addr(ha, 0x101), 0);

	/* Dword ग_लिखोs to flash. */
	naddr = nvram_data_addr(ha, naddr);
	bytes >>= 2;
	क्रम (i = 0; i < bytes; i++, naddr++, dwptr++) अणु
		अगर (qla24xx_ग_लिखो_flash_dword(ha, naddr, le32_to_cpu(*dwptr))) अणु
			ql_dbg(ql_dbg_user, vha, 0x709a,
			    "Unable to program nvram address=%x data=%x.\n",
			    naddr, *dwptr);
			अवरोध;
		पूर्ण
	पूर्ण

	/* Enable NVRAM ग_लिखो-protection. */
	qla24xx_ग_लिखो_flash_dword(ha, nvram_conf_addr(ha, 0x101), 0x8c);

	/* Disable flash ग_लिखो. */
	wrt_reg_dword(&reg->ctrl_status,
	    rd_reg_dword(&reg->ctrl_status) & ~CSRX_FLASH_ENABLE);
	rd_reg_dword(&reg->ctrl_status);	/* PCI Posting. */

	वापस ret;
पूर्ण

uपूर्णांक8_t *
qla25xx_पढ़ो_nvram_data(scsi_qla_host_t *vha, व्योम *buf, uपूर्णांक32_t naddr,
    uपूर्णांक32_t bytes)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;
	uपूर्णांक32_t *dwptr = buf;
	uपूर्णांक32_t i;

	/* Dword पढ़ोs to flash. */
	naddr = flash_data_addr(ha, ha->flt_region_vpd_nvram | naddr);
	bytes >>= 2;
	क्रम (i = 0; i < bytes; i++, naddr++, dwptr++) अणु
		अगर (qla24xx_पढ़ो_flash_dword(ha, naddr, dwptr))
			अवरोध;

		cpu_to_le32s(dwptr);
	पूर्ण

	वापस buf;
पूर्ण

#घोषणा RMW_BUFFER_SIZE	(64 * 1024)
पूर्णांक
qla25xx_ग_लिखो_nvram_data(scsi_qla_host_t *vha, व्योम *buf, uपूर्णांक32_t naddr,
    uपूर्णांक32_t bytes)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;
	uपूर्णांक8_t *dbuf = vदो_स्मृति(RMW_BUFFER_SIZE);

	अगर (!dbuf)
		वापस QLA_MEMORY_ALLOC_FAILED;
	ha->isp_ops->पढ़ो_optrom(vha, dbuf, ha->flt_region_vpd_nvram << 2,
	    RMW_BUFFER_SIZE);
	स_नकल(dbuf + (naddr << 2), buf, bytes);
	ha->isp_ops->ग_लिखो_optrom(vha, dbuf, ha->flt_region_vpd_nvram << 2,
	    RMW_BUFFER_SIZE);
	vमुक्त(dbuf);

	वापस QLA_SUCCESS;
पूर्ण

अटल अंतरभूत व्योम
qla2x00_flip_colors(काष्ठा qla_hw_data *ha, uपूर्णांक16_t *pflags)
अणु
	अगर (IS_QLA2322(ha)) अणु
		/* Flip all colors. */
		अगर (ha->beacon_color_state == QLA_LED_ALL_ON) अणु
			/* Turn off. */
			ha->beacon_color_state = 0;
			*pflags = GPIO_LED_ALL_OFF;
		पूर्ण अन्यथा अणु
			/* Turn on. */
			ha->beacon_color_state = QLA_LED_ALL_ON;
			*pflags = GPIO_LED_RGA_ON;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Flip green led only. */
		अगर (ha->beacon_color_state == QLA_LED_GRN_ON) अणु
			/* Turn off. */
			ha->beacon_color_state = 0;
			*pflags = GPIO_LED_GREEN_OFF_AMBER_OFF;
		पूर्ण अन्यथा अणु
			/* Turn on. */
			ha->beacon_color_state = QLA_LED_GRN_ON;
			*pflags = GPIO_LED_GREEN_ON_AMBER_OFF;
		पूर्ण
	पूर्ण
पूर्ण

#घोषणा PIO_REG(h, r) ((h)->pio_address + दुरत्व(काष्ठा device_reg_2xxx, r))

व्योम
qla2x00_beacon_blink(काष्ठा scsi_qla_host *vha)
अणु
	uपूर्णांक16_t gpio_enable;
	uपूर्णांक16_t gpio_data;
	uपूर्णांक16_t led_color = 0;
	अचिन्हित दीर्घ flags;
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा device_reg_2xxx __iomem *reg = &ha->iobase->isp;

	अगर (IS_P3P_TYPE(ha))
		वापस;

	spin_lock_irqsave(&ha->hardware_lock, flags);

	/* Save the Original GPIOE. */
	अगर (ha->pio_address) अणु
		gpio_enable = RD_REG_WORD_PIO(PIO_REG(ha, gpioe));
		gpio_data = RD_REG_WORD_PIO(PIO_REG(ha, gpiod));
	पूर्ण अन्यथा अणु
		gpio_enable = rd_reg_word(&reg->gpioe);
		gpio_data = rd_reg_word(&reg->gpiod);
	पूर्ण

	/* Set the modअगरied gpio_enable values */
	gpio_enable |= GPIO_LED_MASK;

	अगर (ha->pio_address) अणु
		WRT_REG_WORD_PIO(PIO_REG(ha, gpioe), gpio_enable);
	पूर्ण अन्यथा अणु
		wrt_reg_word(&reg->gpioe, gpio_enable);
		rd_reg_word(&reg->gpioe);
	पूर्ण

	qla2x00_flip_colors(ha, &led_color);

	/* Clear out any previously set LED color. */
	gpio_data &= ~GPIO_LED_MASK;

	/* Set the new input LED color to GPIOD. */
	gpio_data |= led_color;

	/* Set the modअगरied gpio_data values */
	अगर (ha->pio_address) अणु
		WRT_REG_WORD_PIO(PIO_REG(ha, gpiod), gpio_data);
	पूर्ण अन्यथा अणु
		wrt_reg_word(&reg->gpiod, gpio_data);
		rd_reg_word(&reg->gpiod);
	पूर्ण

	spin_unlock_irqrestore(&ha->hardware_lock, flags);
पूर्ण

पूर्णांक
qla2x00_beacon_on(काष्ठा scsi_qla_host *vha)
अणु
	uपूर्णांक16_t gpio_enable;
	uपूर्णांक16_t gpio_data;
	अचिन्हित दीर्घ flags;
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा device_reg_2xxx __iomem *reg = &ha->iobase->isp;

	ha->fw_options[1] &= ~FO1_SET_EMPHASIS_SWING;
	ha->fw_options[1] |= FO1_DISABLE_GPIO6_7;

	अगर (qla2x00_set_fw_options(vha, ha->fw_options) != QLA_SUCCESS) अणु
		ql_log(ql_log_warn, vha, 0x709b,
		    "Unable to update fw options (beacon on).\n");
		वापस QLA_FUNCTION_FAILED;
	पूर्ण

	/* Turn off LEDs. */
	spin_lock_irqsave(&ha->hardware_lock, flags);
	अगर (ha->pio_address) अणु
		gpio_enable = RD_REG_WORD_PIO(PIO_REG(ha, gpioe));
		gpio_data = RD_REG_WORD_PIO(PIO_REG(ha, gpiod));
	पूर्ण अन्यथा अणु
		gpio_enable = rd_reg_word(&reg->gpioe);
		gpio_data = rd_reg_word(&reg->gpiod);
	पूर्ण
	gpio_enable |= GPIO_LED_MASK;

	/* Set the modअगरied gpio_enable values. */
	अगर (ha->pio_address) अणु
		WRT_REG_WORD_PIO(PIO_REG(ha, gpioe), gpio_enable);
	पूर्ण अन्यथा अणु
		wrt_reg_word(&reg->gpioe, gpio_enable);
		rd_reg_word(&reg->gpioe);
	पूर्ण

	/* Clear out previously set LED colour. */
	gpio_data &= ~GPIO_LED_MASK;
	अगर (ha->pio_address) अणु
		WRT_REG_WORD_PIO(PIO_REG(ha, gpiod), gpio_data);
	पूर्ण अन्यथा अणु
		wrt_reg_word(&reg->gpiod, gpio_data);
		rd_reg_word(&reg->gpiod);
	पूर्ण
	spin_unlock_irqrestore(&ha->hardware_lock, flags);

	/*
	 * Let the per HBA समयr kick off the blinking process based on
	 * the following flags. No need to करो anything अन्यथा now.
	 */
	ha->beacon_blink_led = 1;
	ha->beacon_color_state = 0;

	वापस QLA_SUCCESS;
पूर्ण

पूर्णांक
qla2x00_beacon_off(काष्ठा scsi_qla_host *vha)
अणु
	पूर्णांक rval = QLA_SUCCESS;
	काष्ठा qla_hw_data *ha = vha->hw;

	ha->beacon_blink_led = 0;

	/* Set the on flag so when it माला_लो flipped it will be off. */
	अगर (IS_QLA2322(ha))
		ha->beacon_color_state = QLA_LED_ALL_ON;
	अन्यथा
		ha->beacon_color_state = QLA_LED_GRN_ON;

	ha->isp_ops->beacon_blink(vha);	/* This turns green LED off */

	ha->fw_options[1] &= ~FO1_SET_EMPHASIS_SWING;
	ha->fw_options[1] &= ~FO1_DISABLE_GPIO6_7;

	rval = qla2x00_set_fw_options(vha, ha->fw_options);
	अगर (rval != QLA_SUCCESS)
		ql_log(ql_log_warn, vha, 0x709c,
		    "Unable to update fw options (beacon off).\n");
	वापस rval;
पूर्ण


अटल अंतरभूत व्योम
qla24xx_flip_colors(काष्ठा qla_hw_data *ha, uपूर्णांक16_t *pflags)
अणु
	/* Flip all colors. */
	अगर (ha->beacon_color_state == QLA_LED_ALL_ON) अणु
		/* Turn off. */
		ha->beacon_color_state = 0;
		*pflags = 0;
	पूर्ण अन्यथा अणु
		/* Turn on. */
		ha->beacon_color_state = QLA_LED_ALL_ON;
		*pflags = GPDX_LED_YELLOW_ON | GPDX_LED_AMBER_ON;
	पूर्ण
पूर्ण

व्योम
qla24xx_beacon_blink(काष्ठा scsi_qla_host *vha)
अणु
	uपूर्णांक16_t led_color = 0;
	uपूर्णांक32_t gpio_data;
	अचिन्हित दीर्घ flags;
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा device_reg_24xx __iomem *reg = &ha->iobase->isp24;

	/* Save the Original GPIOD. */
	spin_lock_irqsave(&ha->hardware_lock, flags);
	gpio_data = rd_reg_dword(&reg->gpiod);

	/* Enable the gpio_data reg क्रम update. */
	gpio_data |= GPDX_LED_UPDATE_MASK;

	wrt_reg_dword(&reg->gpiod, gpio_data);
	gpio_data = rd_reg_dword(&reg->gpiod);

	/* Set the color bits. */
	qla24xx_flip_colors(ha, &led_color);

	/* Clear out any previously set LED color. */
	gpio_data &= ~GPDX_LED_COLOR_MASK;

	/* Set the new input LED color to GPIOD. */
	gpio_data |= led_color;

	/* Set the modअगरied gpio_data values. */
	wrt_reg_dword(&reg->gpiod, gpio_data);
	gpio_data = rd_reg_dword(&reg->gpiod);
	spin_unlock_irqrestore(&ha->hardware_lock, flags);
पूर्ण

अटल uपूर्णांक32_t
qla83xx_select_led_port(काष्ठा qla_hw_data *ha)
अणु
	uपूर्णांक32_t led_select_value = 0;

	अगर (!IS_QLA83XX(ha) && !IS_QLA27XX(ha) && !IS_QLA28XX(ha))
		जाओ out;

	अगर (ha->port_no == 0)
		led_select_value = QLA83XX_LED_PORT0;
	अन्यथा
		led_select_value = QLA83XX_LED_PORT1;

out:
	वापस led_select_value;
पूर्ण

व्योम
qla83xx_beacon_blink(काष्ठा scsi_qla_host *vha)
अणु
	uपूर्णांक32_t led_select_value;
	काष्ठा qla_hw_data *ha = vha->hw;
	uपूर्णांक16_t led_cfg[6];
	uपूर्णांक16_t orig_led_cfg[6];
	uपूर्णांक32_t led_10_value, led_43_value;

	अगर (!IS_QLA83XX(ha) && !IS_QLA81XX(ha) && !IS_QLA27XX(ha) &&
	    !IS_QLA28XX(ha))
		वापस;

	अगर (!ha->beacon_blink_led)
		वापस;

	अगर (IS_QLA27XX(ha) || IS_QLA28XX(ha)) अणु
		qla2x00_ग_लिखो_ram_word(vha, 0x1003, 0x40000230);
		qla2x00_ग_लिखो_ram_word(vha, 0x1004, 0x40000230);
	पूर्ण अन्यथा अगर (IS_QLA2031(ha)) अणु
		led_select_value = qla83xx_select_led_port(ha);

		qla83xx_wr_reg(vha, led_select_value, 0x40000230);
		qla83xx_wr_reg(vha, led_select_value + 4, 0x40000230);
	पूर्ण अन्यथा अगर (IS_QLA8031(ha)) अणु
		led_select_value = qla83xx_select_led_port(ha);

		qla83xx_rd_reg(vha, led_select_value, &led_10_value);
		qla83xx_rd_reg(vha, led_select_value + 0x10, &led_43_value);
		qla83xx_wr_reg(vha, led_select_value, 0x01f44000);
		msleep(500);
		qla83xx_wr_reg(vha, led_select_value, 0x400001f4);
		msleep(1000);
		qla83xx_wr_reg(vha, led_select_value, led_10_value);
		qla83xx_wr_reg(vha, led_select_value + 0x10, led_43_value);
	पूर्ण अन्यथा अगर (IS_QLA81XX(ha)) अणु
		पूर्णांक rval;

		/* Save Current */
		rval = qla81xx_get_led_config(vha, orig_led_cfg);
		/* Do the blink */
		अगर (rval == QLA_SUCCESS) अणु
			अगर (IS_QLA81XX(ha)) अणु
				led_cfg[0] = 0x4000;
				led_cfg[1] = 0x2000;
				led_cfg[2] = 0;
				led_cfg[3] = 0;
				led_cfg[4] = 0;
				led_cfg[5] = 0;
			पूर्ण अन्यथा अणु
				led_cfg[0] = 0x4000;
				led_cfg[1] = 0x4000;
				led_cfg[2] = 0x4000;
				led_cfg[3] = 0x2000;
				led_cfg[4] = 0;
				led_cfg[5] = 0x2000;
			पूर्ण
			rval = qla81xx_set_led_config(vha, led_cfg);
			msleep(1000);
			अगर (IS_QLA81XX(ha)) अणु
				led_cfg[0] = 0x4000;
				led_cfg[1] = 0x2000;
				led_cfg[2] = 0;
			पूर्ण अन्यथा अणु
				led_cfg[0] = 0x4000;
				led_cfg[1] = 0x2000;
				led_cfg[2] = 0x4000;
				led_cfg[3] = 0x4000;
				led_cfg[4] = 0;
				led_cfg[5] = 0x2000;
			पूर्ण
			rval = qla81xx_set_led_config(vha, led_cfg);
		पूर्ण
		/* On निकास, restore original (presumes no status change) */
		qla81xx_set_led_config(vha, orig_led_cfg);
	पूर्ण
पूर्ण

पूर्णांक
qla24xx_beacon_on(काष्ठा scsi_qla_host *vha)
अणु
	uपूर्णांक32_t gpio_data;
	अचिन्हित दीर्घ flags;
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा device_reg_24xx __iomem *reg = &ha->iobase->isp24;

	अगर (IS_P3P_TYPE(ha))
		वापस QLA_SUCCESS;

	अगर (IS_QLA8031(ha) || IS_QLA81XX(ha))
		जाओ skip_gpio; /* let blink handle it */

	अगर (ha->beacon_blink_led == 0) अणु
		/* Enable firmware क्रम update */
		ha->fw_options[1] |= ADD_FO1_DISABLE_GPIO_LED_CTRL;

		अगर (qla2x00_set_fw_options(vha, ha->fw_options) != QLA_SUCCESS)
			वापस QLA_FUNCTION_FAILED;

		अगर (qla2x00_get_fw_options(vha, ha->fw_options) !=
		    QLA_SUCCESS) अणु
			ql_log(ql_log_warn, vha, 0x7009,
			    "Unable to update fw options (beacon on).\n");
			वापस QLA_FUNCTION_FAILED;
		पूर्ण

		अगर (IS_QLA2031(ha) || IS_QLA27XX(ha) || IS_QLA28XX(ha))
			जाओ skip_gpio;

		spin_lock_irqsave(&ha->hardware_lock, flags);
		gpio_data = rd_reg_dword(&reg->gpiod);

		/* Enable the gpio_data reg क्रम update. */
		gpio_data |= GPDX_LED_UPDATE_MASK;
		wrt_reg_dword(&reg->gpiod, gpio_data);
		rd_reg_dword(&reg->gpiod);

		spin_unlock_irqrestore(&ha->hardware_lock, flags);
	पूर्ण

	/* So all colors blink together. */
	ha->beacon_color_state = 0;

skip_gpio:
	/* Let the per HBA समयr kick off the blinking process. */
	ha->beacon_blink_led = 1;

	वापस QLA_SUCCESS;
पूर्ण

पूर्णांक
qla24xx_beacon_off(काष्ठा scsi_qla_host *vha)
अणु
	uपूर्णांक32_t gpio_data;
	अचिन्हित दीर्घ flags;
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा device_reg_24xx __iomem *reg = &ha->iobase->isp24;

	अगर (IS_P3P_TYPE(ha))
		वापस QLA_SUCCESS;

	अगर (!ha->flags.fw_started)
		वापस QLA_SUCCESS;

	ha->beacon_blink_led = 0;

	अगर (IS_QLA2031(ha) || IS_QLA27XX(ha) || IS_QLA28XX(ha))
		जाओ set_fw_options;

	अगर (IS_QLA8031(ha) || IS_QLA81XX(ha))
		वापस QLA_SUCCESS;

	ha->beacon_color_state = QLA_LED_ALL_ON;

	ha->isp_ops->beacon_blink(vha);	/* Will flip to all off. */

	/* Give control back to firmware. */
	spin_lock_irqsave(&ha->hardware_lock, flags);
	gpio_data = rd_reg_dword(&reg->gpiod);

	/* Disable the gpio_data reg क्रम update. */
	gpio_data &= ~GPDX_LED_UPDATE_MASK;
	wrt_reg_dword(&reg->gpiod, gpio_data);
	rd_reg_dword(&reg->gpiod);
	spin_unlock_irqrestore(&ha->hardware_lock, flags);

set_fw_options:
	ha->fw_options[1] &= ~ADD_FO1_DISABLE_GPIO_LED_CTRL;

	अगर (qla2x00_set_fw_options(vha, ha->fw_options) != QLA_SUCCESS) अणु
		ql_log(ql_log_warn, vha, 0x704d,
		    "Unable to update fw options (beacon on).\n");
		वापस QLA_FUNCTION_FAILED;
	पूर्ण

	अगर (qla2x00_get_fw_options(vha, ha->fw_options) != QLA_SUCCESS) अणु
		ql_log(ql_log_warn, vha, 0x704e,
		    "Unable to update fw options (beacon on).\n");
		वापस QLA_FUNCTION_FAILED;
	पूर्ण

	वापस QLA_SUCCESS;
पूर्ण


/*
 * Flash support routines
 */

/**
 * qla2x00_flash_enable() - Setup flash क्रम पढ़ोing and writing.
 * @ha: HA context
 */
अटल व्योम
qla2x00_flash_enable(काष्ठा qla_hw_data *ha)
अणु
	uपूर्णांक16_t data;
	काष्ठा device_reg_2xxx __iomem *reg = &ha->iobase->isp;

	data = rd_reg_word(&reg->ctrl_status);
	data |= CSR_FLASH_ENABLE;
	wrt_reg_word(&reg->ctrl_status, data);
	rd_reg_word(&reg->ctrl_status);		/* PCI Posting. */
पूर्ण

/**
 * qla2x00_flash_disable() - Disable flash and allow RISC to run.
 * @ha: HA context
 */
अटल व्योम
qla2x00_flash_disable(काष्ठा qla_hw_data *ha)
अणु
	uपूर्णांक16_t data;
	काष्ठा device_reg_2xxx __iomem *reg = &ha->iobase->isp;

	data = rd_reg_word(&reg->ctrl_status);
	data &= ~(CSR_FLASH_ENABLE);
	wrt_reg_word(&reg->ctrl_status, data);
	rd_reg_word(&reg->ctrl_status);		/* PCI Posting. */
पूर्ण

/**
 * qla2x00_पढ़ो_flash_byte() - Reads a byte from flash
 * @ha: HA context
 * @addr: Address in flash to पढ़ो
 *
 * A word is पढ़ो from the chip, but, only the lower byte is valid.
 *
 * Returns the byte पढ़ो from flash @addr.
 */
अटल uपूर्णांक8_t
qla2x00_पढ़ो_flash_byte(काष्ठा qla_hw_data *ha, uपूर्णांक32_t addr)
अणु
	uपूर्णांक16_t data;
	uपूर्णांक16_t bank_select;
	काष्ठा device_reg_2xxx __iomem *reg = &ha->iobase->isp;

	bank_select = rd_reg_word(&reg->ctrl_status);

	अगर (IS_QLA2322(ha) || IS_QLA6322(ha)) अणु
		/* Specअगरy 64K address range: */
		/*  clear out Module Select and Flash Address bits [19:16]. */
		bank_select &= ~0xf8;
		bank_select |= addr >> 12 & 0xf0;
		bank_select |= CSR_FLASH_64K_BANK;
		wrt_reg_word(&reg->ctrl_status, bank_select);
		rd_reg_word(&reg->ctrl_status);	/* PCI Posting. */

		wrt_reg_word(&reg->flash_address, (uपूर्णांक16_t)addr);
		data = rd_reg_word(&reg->flash_data);

		वापस (uपूर्णांक8_t)data;
	पूर्ण

	/* Setup bit 16 of flash address. */
	अगर ((addr & BIT_16) && ((bank_select & CSR_FLASH_64K_BANK) == 0)) अणु
		bank_select |= CSR_FLASH_64K_BANK;
		wrt_reg_word(&reg->ctrl_status, bank_select);
		rd_reg_word(&reg->ctrl_status);	/* PCI Posting. */
	पूर्ण अन्यथा अगर (((addr & BIT_16) == 0) &&
	    (bank_select & CSR_FLASH_64K_BANK)) अणु
		bank_select &= ~(CSR_FLASH_64K_BANK);
		wrt_reg_word(&reg->ctrl_status, bank_select);
		rd_reg_word(&reg->ctrl_status);	/* PCI Posting. */
	पूर्ण

	/* Always perक्रमm IO mapped accesses to the FLASH रेजिस्टरs. */
	अगर (ha->pio_address) अणु
		uपूर्णांक16_t data2;

		WRT_REG_WORD_PIO(PIO_REG(ha, flash_address), (uपूर्णांक16_t)addr);
		करो अणु
			data = RD_REG_WORD_PIO(PIO_REG(ha, flash_data));
			barrier();
			cpu_relax();
			data2 = RD_REG_WORD_PIO(PIO_REG(ha, flash_data));
		पूर्ण जबतक (data != data2);
	पूर्ण अन्यथा अणु
		wrt_reg_word(&reg->flash_address, (uपूर्णांक16_t)addr);
		data = qla2x00_debounce_रेजिस्टर(&reg->flash_data);
	पूर्ण

	वापस (uपूर्णांक8_t)data;
पूर्ण

/**
 * qla2x00_ग_लिखो_flash_byte() - Write a byte to flash
 * @ha: HA context
 * @addr: Address in flash to ग_लिखो
 * @data: Data to ग_लिखो
 */
अटल व्योम
qla2x00_ग_लिखो_flash_byte(काष्ठा qla_hw_data *ha, uपूर्णांक32_t addr, uपूर्णांक8_t data)
अणु
	uपूर्णांक16_t bank_select;
	काष्ठा device_reg_2xxx __iomem *reg = &ha->iobase->isp;

	bank_select = rd_reg_word(&reg->ctrl_status);
	अगर (IS_QLA2322(ha) || IS_QLA6322(ha)) अणु
		/* Specअगरy 64K address range: */
		/*  clear out Module Select and Flash Address bits [19:16]. */
		bank_select &= ~0xf8;
		bank_select |= addr >> 12 & 0xf0;
		bank_select |= CSR_FLASH_64K_BANK;
		wrt_reg_word(&reg->ctrl_status, bank_select);
		rd_reg_word(&reg->ctrl_status);	/* PCI Posting. */

		wrt_reg_word(&reg->flash_address, (uपूर्णांक16_t)addr);
		rd_reg_word(&reg->ctrl_status);		/* PCI Posting. */
		wrt_reg_word(&reg->flash_data, (uपूर्णांक16_t)data);
		rd_reg_word(&reg->ctrl_status);		/* PCI Posting. */

		वापस;
	पूर्ण

	/* Setup bit 16 of flash address. */
	अगर ((addr & BIT_16) && ((bank_select & CSR_FLASH_64K_BANK) == 0)) अणु
		bank_select |= CSR_FLASH_64K_BANK;
		wrt_reg_word(&reg->ctrl_status, bank_select);
		rd_reg_word(&reg->ctrl_status);	/* PCI Posting. */
	पूर्ण अन्यथा अगर (((addr & BIT_16) == 0) &&
	    (bank_select & CSR_FLASH_64K_BANK)) अणु
		bank_select &= ~(CSR_FLASH_64K_BANK);
		wrt_reg_word(&reg->ctrl_status, bank_select);
		rd_reg_word(&reg->ctrl_status);	/* PCI Posting. */
	पूर्ण

	/* Always perक्रमm IO mapped accesses to the FLASH रेजिस्टरs. */
	अगर (ha->pio_address) अणु
		WRT_REG_WORD_PIO(PIO_REG(ha, flash_address), (uपूर्णांक16_t)addr);
		WRT_REG_WORD_PIO(PIO_REG(ha, flash_data), (uपूर्णांक16_t)data);
	पूर्ण अन्यथा अणु
		wrt_reg_word(&reg->flash_address, (uपूर्णांक16_t)addr);
		rd_reg_word(&reg->ctrl_status);		/* PCI Posting. */
		wrt_reg_word(&reg->flash_data, (uपूर्णांक16_t)data);
		rd_reg_word(&reg->ctrl_status);		/* PCI Posting. */
	पूर्ण
पूर्ण

/**
 * qla2x00_poll_flash() - Polls flash क्रम completion.
 * @ha: HA context
 * @addr: Address in flash to poll
 * @poll_data: Data to be polled
 * @man_id: Flash manufacturer ID
 * @flash_id: Flash ID
 *
 * This function polls the device until bit 7 of what is पढ़ो matches data
 * bit 7 or until data bit 5 becomes a 1.  If that hapens, the flash ROM समयd
 * out (a fatal error).  The flash book recommeds पढ़ोing bit 7 again after
 * पढ़ोing bit 5 as a 1.
 *
 * Returns 0 on success, अन्यथा non-zero.
 */
अटल पूर्णांक
qla2x00_poll_flash(काष्ठा qla_hw_data *ha, uपूर्णांक32_t addr, uपूर्णांक8_t poll_data,
    uपूर्णांक8_t man_id, uपूर्णांक8_t flash_id)
अणु
	पूर्णांक status;
	uपूर्णांक8_t flash_data;
	uपूर्णांक32_t cnt;

	status = 1;

	/* Wait क्रम 30 seconds क्रम command to finish. */
	poll_data &= BIT_7;
	क्रम (cnt = 3000000; cnt; cnt--) अणु
		flash_data = qla2x00_पढ़ो_flash_byte(ha, addr);
		अगर ((flash_data & BIT_7) == poll_data) अणु
			status = 0;
			अवरोध;
		पूर्ण

		अगर (man_id != 0x40 && man_id != 0xda) अणु
			अगर ((flash_data & BIT_5) && cnt > 2)
				cnt = 2;
		पूर्ण
		udelay(10);
		barrier();
		cond_resched();
	पूर्ण
	वापस status;
पूर्ण

/**
 * qla2x00_program_flash_address() - Programs a flash address
 * @ha: HA context
 * @addr: Address in flash to program
 * @data: Data to be written in flash
 * @man_id: Flash manufacturer ID
 * @flash_id: Flash ID
 *
 * Returns 0 on success, अन्यथा non-zero.
 */
अटल पूर्णांक
qla2x00_program_flash_address(काष्ठा qla_hw_data *ha, uपूर्णांक32_t addr,
    uपूर्णांक8_t data, uपूर्णांक8_t man_id, uपूर्णांक8_t flash_id)
अणु
	/* Write Program Command Sequence. */
	अगर (IS_OEM_001(ha)) अणु
		qla2x00_ग_लिखो_flash_byte(ha, 0xaaa, 0xaa);
		qla2x00_ग_लिखो_flash_byte(ha, 0x555, 0x55);
		qla2x00_ग_लिखो_flash_byte(ha, 0xaaa, 0xa0);
		qla2x00_ग_लिखो_flash_byte(ha, addr, data);
	पूर्ण अन्यथा अणु
		अगर (man_id == 0xda && flash_id == 0xc1) अणु
			qla2x00_ग_लिखो_flash_byte(ha, addr, data);
			अगर (addr & 0x7e)
				वापस 0;
		पूर्ण अन्यथा अणु
			qla2x00_ग_लिखो_flash_byte(ha, 0x5555, 0xaa);
			qla2x00_ग_लिखो_flash_byte(ha, 0x2aaa, 0x55);
			qla2x00_ग_लिखो_flash_byte(ha, 0x5555, 0xa0);
			qla2x00_ग_लिखो_flash_byte(ha, addr, data);
		पूर्ण
	पूर्ण

	udelay(150);

	/* Wait क्रम ग_लिखो to complete. */
	वापस qla2x00_poll_flash(ha, addr, data, man_id, flash_id);
पूर्ण

/**
 * qla2x00_erase_flash() - Erase the flash.
 * @ha: HA context
 * @man_id: Flash manufacturer ID
 * @flash_id: Flash ID
 *
 * Returns 0 on success, अन्यथा non-zero.
 */
अटल पूर्णांक
qla2x00_erase_flash(काष्ठा qla_hw_data *ha, uपूर्णांक8_t man_id, uपूर्णांक8_t flash_id)
अणु
	/* Inभागidual Sector Erase Command Sequence */
	अगर (IS_OEM_001(ha)) अणु
		qla2x00_ग_लिखो_flash_byte(ha, 0xaaa, 0xaa);
		qla2x00_ग_लिखो_flash_byte(ha, 0x555, 0x55);
		qla2x00_ग_लिखो_flash_byte(ha, 0xaaa, 0x80);
		qla2x00_ग_लिखो_flash_byte(ha, 0xaaa, 0xaa);
		qla2x00_ग_लिखो_flash_byte(ha, 0x555, 0x55);
		qla2x00_ग_लिखो_flash_byte(ha, 0xaaa, 0x10);
	पूर्ण अन्यथा अणु
		qla2x00_ग_लिखो_flash_byte(ha, 0x5555, 0xaa);
		qla2x00_ग_लिखो_flash_byte(ha, 0x2aaa, 0x55);
		qla2x00_ग_लिखो_flash_byte(ha, 0x5555, 0x80);
		qla2x00_ग_लिखो_flash_byte(ha, 0x5555, 0xaa);
		qla2x00_ग_लिखो_flash_byte(ha, 0x2aaa, 0x55);
		qla2x00_ग_लिखो_flash_byte(ha, 0x5555, 0x10);
	पूर्ण

	udelay(150);

	/* Wait क्रम erase to complete. */
	वापस qla2x00_poll_flash(ha, 0x00, 0x80, man_id, flash_id);
पूर्ण

/**
 * qla2x00_erase_flash_sector() - Erase a flash sector.
 * @ha: HA context
 * @addr: Flash sector to erase
 * @sec_mask: Sector address mask
 * @man_id: Flash manufacturer ID
 * @flash_id: Flash ID
 *
 * Returns 0 on success, अन्यथा non-zero.
 */
अटल पूर्णांक
qla2x00_erase_flash_sector(काष्ठा qla_hw_data *ha, uपूर्णांक32_t addr,
    uपूर्णांक32_t sec_mask, uपूर्णांक8_t man_id, uपूर्णांक8_t flash_id)
अणु
	/* Inभागidual Sector Erase Command Sequence */
	qla2x00_ग_लिखो_flash_byte(ha, 0x5555, 0xaa);
	qla2x00_ग_लिखो_flash_byte(ha, 0x2aaa, 0x55);
	qla2x00_ग_लिखो_flash_byte(ha, 0x5555, 0x80);
	qla2x00_ग_लिखो_flash_byte(ha, 0x5555, 0xaa);
	qla2x00_ग_लिखो_flash_byte(ha, 0x2aaa, 0x55);
	अगर (man_id == 0x1f && flash_id == 0x13)
		qla2x00_ग_लिखो_flash_byte(ha, addr & sec_mask, 0x10);
	अन्यथा
		qla2x00_ग_लिखो_flash_byte(ha, addr & sec_mask, 0x30);

	udelay(150);

	/* Wait क्रम erase to complete. */
	वापस qla2x00_poll_flash(ha, addr, 0x80, man_id, flash_id);
पूर्ण

/**
 * qla2x00_get_flash_manufacturer() - Read manufacturer ID from flash chip.
 * @ha: host adapter
 * @man_id: Flash manufacturer ID
 * @flash_id: Flash ID
 */
अटल व्योम
qla2x00_get_flash_manufacturer(काष्ठा qla_hw_data *ha, uपूर्णांक8_t *man_id,
    uपूर्णांक8_t *flash_id)
अणु
	qla2x00_ग_लिखो_flash_byte(ha, 0x5555, 0xaa);
	qla2x00_ग_लिखो_flash_byte(ha, 0x2aaa, 0x55);
	qla2x00_ग_लिखो_flash_byte(ha, 0x5555, 0x90);
	*man_id = qla2x00_पढ़ो_flash_byte(ha, 0x0000);
	*flash_id = qla2x00_पढ़ो_flash_byte(ha, 0x0001);
	qla2x00_ग_लिखो_flash_byte(ha, 0x5555, 0xaa);
	qla2x00_ग_लिखो_flash_byte(ha, 0x2aaa, 0x55);
	qla2x00_ग_लिखो_flash_byte(ha, 0x5555, 0xf0);
पूर्ण

अटल व्योम
qla2x00_पढ़ो_flash_data(काष्ठा qla_hw_data *ha, uपूर्णांक8_t *पंचांगp_buf,
	uपूर्णांक32_t saddr, uपूर्णांक32_t length)
अणु
	काष्ठा device_reg_2xxx __iomem *reg = &ha->iobase->isp;
	uपूर्णांक32_t midpoपूर्णांक, ilength;
	uपूर्णांक8_t data;

	midpoपूर्णांक = length / 2;

	wrt_reg_word(&reg->nvram, 0);
	rd_reg_word(&reg->nvram);
	क्रम (ilength = 0; ilength < length; saddr++, ilength++, पंचांगp_buf++) अणु
		अगर (ilength == midpoपूर्णांक) अणु
			wrt_reg_word(&reg->nvram, NVR_SELECT);
			rd_reg_word(&reg->nvram);
		पूर्ण
		data = qla2x00_पढ़ो_flash_byte(ha, saddr);
		अगर (saddr % 100)
			udelay(10);
		*पंचांगp_buf = data;
		cond_resched();
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम
qla2x00_suspend_hba(काष्ठा scsi_qla_host *vha)
अणु
	पूर्णांक cnt;
	अचिन्हित दीर्घ flags;
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा device_reg_2xxx __iomem *reg = &ha->iobase->isp;

	/* Suspend HBA. */
	scsi_block_requests(vha->host);
	ha->isp_ops->disable_पूर्णांकrs(ha);
	set_bit(MBX_UPDATE_FLASH_ACTIVE, &ha->mbx_cmd_flags);

	/* Pause RISC. */
	spin_lock_irqsave(&ha->hardware_lock, flags);
	wrt_reg_word(&reg->hccr, HCCR_PAUSE_RISC);
	rd_reg_word(&reg->hccr);
	अगर (IS_QLA2100(ha) || IS_QLA2200(ha) || IS_QLA2300(ha)) अणु
		क्रम (cnt = 0; cnt < 30000; cnt++) अणु
			अगर ((rd_reg_word(&reg->hccr) & HCCR_RISC_PAUSE) != 0)
				अवरोध;
			udelay(100);
		पूर्ण
	पूर्ण अन्यथा अणु
		udelay(10);
	पूर्ण
	spin_unlock_irqrestore(&ha->hardware_lock, flags);
पूर्ण

अटल अंतरभूत व्योम
qla2x00_resume_hba(काष्ठा scsi_qla_host *vha)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;

	/* Resume HBA. */
	clear_bit(MBX_UPDATE_FLASH_ACTIVE, &ha->mbx_cmd_flags);
	set_bit(ISP_ABORT_NEEDED, &vha->dpc_flags);
	qla2xxx_wake_dpc(vha);
	qla2x00_रुको_क्रम_chip_reset(vha);
	scsi_unblock_requests(vha->host);
पूर्ण

व्योम *
qla2x00_पढ़ो_optrom_data(काष्ठा scsi_qla_host *vha, व्योम *buf,
    uपूर्णांक32_t offset, uपूर्णांक32_t length)
अणु
	uपूर्णांक32_t addr, midpoपूर्णांक;
	uपूर्णांक8_t *data;
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा device_reg_2xxx __iomem *reg = &ha->iobase->isp;

	/* Suspend HBA. */
	qla2x00_suspend_hba(vha);

	/* Go with पढ़ो. */
	midpoपूर्णांक = ha->optrom_size / 2;

	qla2x00_flash_enable(ha);
	wrt_reg_word(&reg->nvram, 0);
	rd_reg_word(&reg->nvram);		/* PCI Posting. */
	क्रम (addr = offset, data = buf; addr < length; addr++, data++) अणु
		अगर (addr == midpoपूर्णांक) अणु
			wrt_reg_word(&reg->nvram, NVR_SELECT);
			rd_reg_word(&reg->nvram);	/* PCI Posting. */
		पूर्ण

		*data = qla2x00_पढ़ो_flash_byte(ha, addr);
	पूर्ण
	qla2x00_flash_disable(ha);

	/* Resume HBA. */
	qla2x00_resume_hba(vha);

	वापस buf;
पूर्ण

पूर्णांक
qla2x00_ग_लिखो_optrom_data(काष्ठा scsi_qla_host *vha, व्योम *buf,
    uपूर्णांक32_t offset, uपूर्णांक32_t length)
अणु

	पूर्णांक rval;
	uपूर्णांक8_t man_id, flash_id, sec_number, *data;
	uपूर्णांक16_t wd;
	uपूर्णांक32_t addr, liter, sec_mask, rest_addr;
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा device_reg_2xxx __iomem *reg = &ha->iobase->isp;

	/* Suspend HBA. */
	qla2x00_suspend_hba(vha);

	rval = QLA_SUCCESS;
	sec_number = 0;

	/* Reset ISP chip. */
	wrt_reg_word(&reg->ctrl_status, CSR_ISP_SOFT_RESET);
	pci_पढ़ो_config_word(ha->pdev, PCI_COMMAND, &wd);

	/* Go with ग_लिखो. */
	qla2x00_flash_enable(ha);
	करो अणु	/* Loop once to provide quick error निकास */
		/* Structure of flash memory based on manufacturer */
		अगर (IS_OEM_001(ha)) अणु
			/* OEM variant with special flash part. */
			man_id = flash_id = 0;
			rest_addr = 0xffff;
			sec_mask   = 0x10000;
			जाओ update_flash;
		पूर्ण
		qla2x00_get_flash_manufacturer(ha, &man_id, &flash_id);
		चयन (man_id) अणु
		हाल 0x20: /* ST flash. */
			अगर (flash_id == 0xd2 || flash_id == 0xe3) अणु
				/*
				 * ST m29w008at part - 64kb sector size with
				 * 32kb,8kb,8kb,16kb sectors at memory address
				 * 0xf0000.
				 */
				rest_addr = 0xffff;
				sec_mask = 0x10000;
				अवरोध;
			पूर्ण
			/*
			 * ST m29w010b part - 16kb sector size
			 * Default to 16kb sectors
			 */
			rest_addr = 0x3fff;
			sec_mask = 0x1c000;
			अवरोध;
		हाल 0x40: /* Mostel flash. */
			/* Mostel v29c51001 part - 512 byte sector size. */
			rest_addr = 0x1ff;
			sec_mask = 0x1fe00;
			अवरोध;
		हाल 0xbf: /* SST flash. */
			/* SST39sf10 part - 4kb sector size. */
			rest_addr = 0xfff;
			sec_mask = 0x1f000;
			अवरोध;
		हाल 0xda: /* Winbond flash. */
			/* Winbond W29EE011 part - 256 byte sector size. */
			rest_addr = 0x7f;
			sec_mask = 0x1ff80;
			अवरोध;
		हाल 0xc2: /* Macronix flash. */
			/* 64k sector size. */
			अगर (flash_id == 0x38 || flash_id == 0x4f) अणु
				rest_addr = 0xffff;
				sec_mask = 0x10000;
				अवरोध;
			पूर्ण
			fallthrough;

		हाल 0x1f: /* Aपंचांगel flash. */
			/* 512k sector size. */
			अगर (flash_id == 0x13) अणु
				rest_addr = 0x7fffffff;
				sec_mask =   0x80000000;
				अवरोध;
			पूर्ण
			fallthrough;

		हाल 0x01: /* AMD flash. */
			अगर (flash_id == 0x38 || flash_id == 0x40 ||
			    flash_id == 0x4f) अणु
				/* Am29LV081 part - 64kb sector size. */
				/* Am29LV002BT part - 64kb sector size. */
				rest_addr = 0xffff;
				sec_mask = 0x10000;
				अवरोध;
			पूर्ण अन्यथा अगर (flash_id == 0x3e) अणु
				/*
				 * Am29LV008b part - 64kb sector size with
				 * 32kb,8kb,8kb,16kb sector at memory address
				 * h0xf0000.
				 */
				rest_addr = 0xffff;
				sec_mask = 0x10000;
				अवरोध;
			पूर्ण अन्यथा अगर (flash_id == 0x20 || flash_id == 0x6e) अणु
				/*
				 * Am29LV010 part or AM29f010 - 16kb sector
				 * size.
				 */
				rest_addr = 0x3fff;
				sec_mask = 0x1c000;
				अवरोध;
			पूर्ण अन्यथा अगर (flash_id == 0x6d) अणु
				/* Am29LV001 part - 8kb sector size. */
				rest_addr = 0x1fff;
				sec_mask = 0x1e000;
				अवरोध;
			पूर्ण
			fallthrough;
		शेष:
			/* Default to 16 kb sector size. */
			rest_addr = 0x3fff;
			sec_mask = 0x1c000;
			अवरोध;
		पूर्ण

update_flash:
		अगर (IS_QLA2322(ha) || IS_QLA6322(ha)) अणु
			अगर (qla2x00_erase_flash(ha, man_id, flash_id)) अणु
				rval = QLA_FUNCTION_FAILED;
				अवरोध;
			पूर्ण
		पूर्ण

		क्रम (addr = offset, liter = 0; liter < length; liter++,
		    addr++) अणु
			data = buf + liter;
			/* Are we at the beginning of a sector? */
			अगर ((addr & rest_addr) == 0) अणु
				अगर (IS_QLA2322(ha) || IS_QLA6322(ha)) अणु
					अगर (addr >= 0x10000UL) अणु
						अगर (((addr >> 12) & 0xf0) &&
						    ((man_id == 0x01 &&
							flash_id == 0x3e) ||
						     (man_id == 0x20 &&
							 flash_id == 0xd2))) अणु
							sec_number++;
							अगर (sec_number == 1) अणु
								rest_addr =
								    0x7fff;
								sec_mask =
								    0x18000;
							पूर्ण अन्यथा अगर (
							    sec_number == 2 ||
							    sec_number == 3) अणु
								rest_addr =
								    0x1fff;
								sec_mask =
								    0x1e000;
							पूर्ण अन्यथा अगर (
							    sec_number == 4) अणु
								rest_addr =
								    0x3fff;
								sec_mask =
								    0x1c000;
							पूर्ण
						पूर्ण
					पूर्ण
				पूर्ण अन्यथा अगर (addr == ha->optrom_size / 2) अणु
					wrt_reg_word(&reg->nvram, NVR_SELECT);
					rd_reg_word(&reg->nvram);
				पूर्ण

				अगर (flash_id == 0xda && man_id == 0xc1) अणु
					qla2x00_ग_लिखो_flash_byte(ha, 0x5555,
					    0xaa);
					qla2x00_ग_लिखो_flash_byte(ha, 0x2aaa,
					    0x55);
					qla2x00_ग_लिखो_flash_byte(ha, 0x5555,
					    0xa0);
				पूर्ण अन्यथा अगर (!IS_QLA2322(ha) && !IS_QLA6322(ha)) अणु
					/* Then erase it */
					अगर (qla2x00_erase_flash_sector(ha,
					    addr, sec_mask, man_id,
					    flash_id)) अणु
						rval = QLA_FUNCTION_FAILED;
						अवरोध;
					पूर्ण
					अगर (man_id == 0x01 && flash_id == 0x6d)
						sec_number++;
				पूर्ण
			पूर्ण

			अगर (man_id == 0x01 && flash_id == 0x6d) अणु
				अगर (sec_number == 1 &&
				    addr == (rest_addr - 1)) अणु
					rest_addr = 0x0fff;
					sec_mask   = 0x1f000;
				पूर्ण अन्यथा अगर (sec_number == 3 && (addr & 0x7ffe)) अणु
					rest_addr = 0x3fff;
					sec_mask   = 0x1c000;
				पूर्ण
			पूर्ण

			अगर (qla2x00_program_flash_address(ha, addr, *data,
			    man_id, flash_id)) अणु
				rval = QLA_FUNCTION_FAILED;
				अवरोध;
			पूर्ण
			cond_resched();
		पूर्ण
	पूर्ण जबतक (0);
	qla2x00_flash_disable(ha);

	/* Resume HBA. */
	qla2x00_resume_hba(vha);

	वापस rval;
पूर्ण

व्योम *
qla24xx_पढ़ो_optrom_data(काष्ठा scsi_qla_host *vha, व्योम *buf,
    uपूर्णांक32_t offset, uपूर्णांक32_t length)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;

	/* Suspend HBA. */
	scsi_block_requests(vha->host);
	set_bit(MBX_UPDATE_FLASH_ACTIVE, &ha->mbx_cmd_flags);

	/* Go with पढ़ो. */
	qla24xx_पढ़ो_flash_data(vha, buf, offset >> 2, length >> 2);

	/* Resume HBA. */
	clear_bit(MBX_UPDATE_FLASH_ACTIVE, &ha->mbx_cmd_flags);
	scsi_unblock_requests(vha->host);

	वापस buf;
पूर्ण

अटल पूर्णांक
qla28xx_extract_sfub_and_verअगरy(काष्ठा scsi_qla_host *vha, __le32 *buf,
    uपूर्णांक32_t len, uपूर्णांक32_t buf_size_without_sfub, uपूर्णांक8_t *sfub_buf)
अणु
	uपूर्णांक32_t check_sum = 0;
	__le32 *p;
	पूर्णांक i;

	p = buf + buf_size_without_sfub;

	/* Extract SFUB from end of file */
	स_नकल(sfub_buf, (uपूर्णांक8_t *)p,
	    माप(काष्ठा secure_flash_update_block));

	क्रम (i = 0; i < (माप(काष्ठा secure_flash_update_block) >> 2); i++)
		check_sum += le32_to_cpu(p[i]);

	check_sum = (~check_sum) + 1;

	अगर (check_sum != le32_to_cpu(p[i])) अणु
		ql_log(ql_log_warn, vha, 0x7097,
		    "SFUB checksum failed, 0x%x, 0x%x\n",
		    check_sum, le32_to_cpu(p[i]));
		वापस QLA_COMMAND_ERROR;
	पूर्ण

	वापस QLA_SUCCESS;
पूर्ण

अटल पूर्णांक
qla28xx_get_flash_region(काष्ठा scsi_qla_host *vha, uपूर्णांक32_t start,
    काष्ठा qla_flt_region *region)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा qla_flt_header *flt = ha->flt;
	काष्ठा qla_flt_region *flt_reg = &flt->region[0];
	uपूर्णांक16_t cnt;
	पूर्णांक rval = QLA_FUNCTION_FAILED;

	अगर (!ha->flt)
		वापस QLA_FUNCTION_FAILED;

	cnt = le16_to_cpu(flt->length) / माप(काष्ठा qla_flt_region);
	क्रम (; cnt; cnt--, flt_reg++) अणु
		अगर (le32_to_cpu(flt_reg->start) == start) अणु
			स_नकल((uपूर्णांक8_t *)region, flt_reg,
			    माप(काष्ठा qla_flt_region));
			rval = QLA_SUCCESS;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस rval;
पूर्ण

अटल पूर्णांक
qla28xx_ग_लिखो_flash_data(scsi_qla_host_t *vha, uपूर्णांक32_t *dwptr, uपूर्णांक32_t faddr,
    uपूर्णांक32_t dwords)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;
	uदीर्घ liter;
	uदीर्घ dburst = OPTROM_BURST_DWORDS; /* burst size in dwords */
	uपूर्णांक32_t sec_mask, rest_addr, fdata;
	व्योम *optrom = शून्य;
	dma_addr_t optrom_dma;
	पूर्णांक rval, ret;
	काष्ठा secure_flash_update_block *sfub;
	dma_addr_t sfub_dma;
	uपूर्णांक32_t offset = faddr << 2;
	uपूर्णांक32_t buf_size_without_sfub = 0;
	काष्ठा qla_flt_region region;
	bool reset_to_rom = false;
	uपूर्णांक32_t risc_size, risc_attr = 0;
	__be32 *fw_array = शून्य;

	/* Retrieve region info - must be a start address passed in */
	rval = qla28xx_get_flash_region(vha, offset, &region);

	अगर (rval != QLA_SUCCESS) अणु
		ql_log(ql_log_warn, vha, 0xffff,
		    "Invalid address %x - not a region start address\n",
		    offset);
		जाओ करोne;
	पूर्ण

	/* Allocate dma buffer क्रम burst ग_लिखो */
	optrom = dma_alloc_coherent(&ha->pdev->dev, OPTROM_BURST_SIZE,
	    &optrom_dma, GFP_KERNEL);
	अगर (!optrom) अणु
		ql_log(ql_log_warn, vha, 0x7095,
		    "Failed allocate burst (%x bytes)\n", OPTROM_BURST_SIZE);
		rval = QLA_COMMAND_ERROR;
		जाओ करोne;
	पूर्ण

	/*
	 * If adapter supports secure flash and region is secure
	 * extract secure flash update block (SFUB) and verअगरy
	 */
	अगर (ha->flags.secure_adapter && region.attribute) अणु

		ql_log(ql_log_warn + ql_dbg_verbose, vha, 0xffff,
		    "Region %x is secure\n", le16_to_cpu(region.code));

		चयन (le16_to_cpu(region.code)) अणु
		हाल FLT_REG_FW:
		हाल FLT_REG_FW_SEC_27XX:
		हाल FLT_REG_MPI_PRI_28XX:
		हाल FLT_REG_MPI_SEC_28XX:
			fw_array = (__क्रमce __be32 *)dwptr;

			/* 1st fw array */
			risc_size = be32_to_cpu(fw_array[3]);
			risc_attr = be32_to_cpu(fw_array[9]);

			buf_size_without_sfub = risc_size;
			fw_array += risc_size;

			/* 2nd fw array */
			risc_size = be32_to_cpu(fw_array[3]);

			buf_size_without_sfub += risc_size;
			fw_array += risc_size;

			/* 1st dump ढाँचा */
			risc_size = be32_to_cpu(fw_array[2]);

			/* skip header and ignore checksum */
			buf_size_without_sfub += risc_size;
			fw_array += risc_size;

			अगर (risc_attr & BIT_9) अणु
				/* 2nd dump ढाँचा */
				risc_size = be32_to_cpu(fw_array[2]);

				/* skip header and ignore checksum */
				buf_size_without_sfub += risc_size;
				fw_array += risc_size;
			पूर्ण
			अवरोध;

		हाल FLT_REG_PEP_PRI_28XX:
		हाल FLT_REG_PEP_SEC_28XX:
			fw_array = (__क्रमce __be32 *)dwptr;

			/* 1st fw array */
			risc_size = be32_to_cpu(fw_array[3]);
			risc_attr = be32_to_cpu(fw_array[9]);

			buf_size_without_sfub = risc_size;
			fw_array += risc_size;
			अवरोध;

		शेष:
			ql_log(ql_log_warn + ql_dbg_verbose, vha,
			    0xffff, "Secure region %x not supported\n",
			    le16_to_cpu(region.code));
			rval = QLA_COMMAND_ERROR;
			जाओ करोne;
		पूर्ण

		sfub = dma_alloc_coherent(&ha->pdev->dev,
			माप(काष्ठा secure_flash_update_block), &sfub_dma,
			GFP_KERNEL);
		अगर (!sfub) अणु
			ql_log(ql_log_warn, vha, 0xffff,
			    "Unable to allocate memory for SFUB\n");
			rval = QLA_COMMAND_ERROR;
			जाओ करोne;
		पूर्ण

		rval = qla28xx_extract_sfub_and_verअगरy(vha, (__le32 *)dwptr,
			dwords, buf_size_without_sfub, (uपूर्णांक8_t *)sfub);

		अगर (rval != QLA_SUCCESS)
			जाओ करोne;

		ql_log(ql_log_warn + ql_dbg_verbose, vha, 0xffff,
		    "SFUB extract and verify successful\n");
	पूर्ण

	rest_addr = (ha->fdt_block_size >> 2) - 1;
	sec_mask = ~rest_addr;

	/* Lock semaphore */
	rval = qla81xx_fac_semaphore_access(vha, FAC_SEMAPHORE_LOCK);
	अगर (rval != QLA_SUCCESS) अणु
		ql_log(ql_log_warn, vha, 0xffff,
		    "Unable to lock flash semaphore.");
		जाओ करोne;
	पूर्ण

	ql_log(ql_log_warn + ql_dbg_verbose, vha, 0x7095,
	    "Unprotect flash...\n");
	rval = qla24xx_unprotect_flash(vha);
	अगर (rval) अणु
		qla81xx_fac_semaphore_access(vha, FAC_SEMAPHORE_UNLOCK);
		ql_log(ql_log_warn, vha, 0x7096, "Failed unprotect flash\n");
		जाओ करोne;
	पूर्ण

	क्रम (liter = 0; liter < dwords; liter++, faddr++) अणु
		fdata = (faddr & sec_mask) << 2;

		/* If start of sector */
		अगर (!(faddr & rest_addr)) अणु
			ql_log(ql_log_warn + ql_dbg_verbose, vha, 0x7095,
			    "Erase sector %#x...\n", faddr);
			rval = qla24xx_erase_sector(vha, fdata);
			अगर (rval) अणु
				ql_dbg(ql_dbg_user, vha, 0x7007,
				    "Failed erase sector %#x\n", faddr);
				जाओ ग_लिखो_protect;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (ha->flags.secure_adapter) अणु
		/*
		 * If adapter supports secure flash but FW करोesn't,
		 * disable ग_लिखो protect, release semaphore and reset
		 * chip to execute ROM code in order to update region securely
		 */
		अगर (!ha->flags.secure_fw) अणु
			ql_log(ql_log_warn + ql_dbg_verbose, vha, 0xffff,
			    "Disable Write and Release Semaphore.");
			rval = qla24xx_protect_flash(vha);
			अगर (rval != QLA_SUCCESS) अणु
				qla81xx_fac_semaphore_access(vha,
					FAC_SEMAPHORE_UNLOCK);
				ql_log(ql_log_warn, vha, 0xffff,
				    "Unable to protect flash.");
				जाओ करोne;
			पूर्ण

			ql_log(ql_log_warn + ql_dbg_verbose, vha, 0xffff,
			    "Reset chip to ROM.");
			set_bit(ISP_ABORT_NEEDED, &vha->dpc_flags);
			set_bit(ISP_ABORT_TO_ROM, &vha->dpc_flags);
			qla2xxx_wake_dpc(vha);
			rval = qla2x00_रुको_क्रम_chip_reset(vha);
			अगर (rval != QLA_SUCCESS) अणु
				ql_log(ql_log_warn, vha, 0xffff,
				    "Unable to reset to ROM code.");
				जाओ करोne;
			पूर्ण
			reset_to_rom = true;
			ha->flags.fac_supported = 0;

			ql_log(ql_log_warn + ql_dbg_verbose, vha, 0xffff,
			    "Lock Semaphore");
			rval = qla2xxx_ग_लिखो_remote_रेजिस्टर(vha,
			    FLASH_SEMAPHORE_REGISTER_ADDR, 0x00020002);
			अगर (rval != QLA_SUCCESS) अणु
				ql_log(ql_log_warn, vha, 0xffff,
				    "Unable to lock flash semaphore.");
				जाओ करोne;
			पूर्ण

			/* Unprotect flash */
			ql_log(ql_log_warn + ql_dbg_verbose, vha, 0xffff,
			    "Enable Write.");
			rval = qla2x00_ग_लिखो_ram_word(vha, 0x7ffd0101, 0);
			अगर (rval) अणु
				ql_log(ql_log_warn, vha, 0x7096,
				    "Failed unprotect flash\n");
				जाओ करोne;
			पूर्ण
		पूर्ण

		/* If region is secure, send Secure Flash MB Cmd */
		अगर (region.attribute && buf_size_without_sfub) अणु
			ql_log(ql_log_warn + ql_dbg_verbose, vha, 0xffff,
			    "Sending Secure Flash MB Cmd\n");
			rval = qla28xx_secure_flash_update(vha, 0,
				le16_to_cpu(region.code),
				buf_size_without_sfub, sfub_dma,
				माप(काष्ठा secure_flash_update_block) >> 2);
			अगर (rval != QLA_SUCCESS) अणु
				ql_log(ql_log_warn, vha, 0xffff,
				    "Secure Flash MB Cmd failed %x.", rval);
				जाओ ग_लिखो_protect;
			पूर्ण
		पूर्ण

	पूर्ण

	/* re-init flash offset */
	faddr = offset >> 2;

	क्रम (liter = 0; liter < dwords; liter++, faddr++, dwptr++) अणु
		fdata = (faddr & sec_mask) << 2;

		/* If smaller than a burst reमुख्यing */
		अगर (dwords - liter < dburst)
			dburst = dwords - liter;

		/* Copy to dma buffer */
		स_नकल(optrom, dwptr, dburst << 2);

		/* Burst ग_लिखो */
		ql_log(ql_log_warn + ql_dbg_verbose, vha, 0x7095,
		    "Write burst (%#lx dwords)...\n", dburst);
		rval = qla2x00_load_ram(vha, optrom_dma,
		    flash_data_addr(ha, faddr), dburst);
		अगर (rval != QLA_SUCCESS) अणु
			ql_log(ql_log_warn, vha, 0x7097,
			    "Failed burst write at %x (%p/%#llx)...\n",
			    flash_data_addr(ha, faddr), optrom,
			    (u64)optrom_dma);
			अवरोध;
		पूर्ण

		liter += dburst - 1;
		faddr += dburst - 1;
		dwptr += dburst - 1;
		जारी;
	पूर्ण

ग_लिखो_protect:
	ql_log(ql_log_warn + ql_dbg_verbose, vha, 0x7095,
	    "Protect flash...\n");
	ret = qla24xx_protect_flash(vha);
	अगर (ret) अणु
		qla81xx_fac_semaphore_access(vha, FAC_SEMAPHORE_UNLOCK);
		ql_log(ql_log_warn, vha, 0x7099,
		    "Failed protect flash\n");
		rval = QLA_COMMAND_ERROR;
	पूर्ण

	अगर (reset_to_rom == true) अणु
		/* Schedule DPC to restart the RISC */
		set_bit(ISP_ABORT_NEEDED, &vha->dpc_flags);
		qla2xxx_wake_dpc(vha);

		ret = qla2x00_रुको_क्रम_hba_online(vha);
		अगर (ret != QLA_SUCCESS) अणु
			ql_log(ql_log_warn, vha, 0xffff,
			    "Adapter did not come out of reset\n");
			rval = QLA_COMMAND_ERROR;
		पूर्ण
	पूर्ण

करोne:
	अगर (optrom)
		dma_मुक्त_coherent(&ha->pdev->dev,
		    OPTROM_BURST_SIZE, optrom, optrom_dma);

	वापस rval;
पूर्ण

पूर्णांक
qla24xx_ग_लिखो_optrom_data(काष्ठा scsi_qla_host *vha, व्योम *buf,
    uपूर्णांक32_t offset, uपूर्णांक32_t length)
अणु
	पूर्णांक rval;
	काष्ठा qla_hw_data *ha = vha->hw;

	/* Suspend HBA. */
	scsi_block_requests(vha->host);
	set_bit(MBX_UPDATE_FLASH_ACTIVE, &ha->mbx_cmd_flags);

	/* Go with ग_लिखो. */
	अगर (IS_QLA28XX(ha))
		rval = qla28xx_ग_लिखो_flash_data(vha, buf, offset >> 2,
						length >> 2);
	अन्यथा
		rval = qla24xx_ग_लिखो_flash_data(vha, buf, offset >> 2,
						length >> 2);

	clear_bit(MBX_UPDATE_FLASH_ACTIVE, &ha->mbx_cmd_flags);
	scsi_unblock_requests(vha->host);

	वापस rval;
पूर्ण

व्योम *
qla25xx_पढ़ो_optrom_data(काष्ठा scsi_qla_host *vha, व्योम *buf,
    uपूर्णांक32_t offset, uपूर्णांक32_t length)
अणु
	पूर्णांक rval;
	dma_addr_t optrom_dma;
	व्योम *optrom;
	uपूर्णांक8_t *pbuf;
	uपूर्णांक32_t faddr, left, burst;
	काष्ठा qla_hw_data *ha = vha->hw;

	अगर (IS_QLA25XX(ha) || IS_QLA81XX(ha) || IS_QLA83XX(ha) ||
	    IS_QLA27XX(ha) || IS_QLA28XX(ha))
		जाओ try_fast;
	अगर (offset & 0xfff)
		जाओ slow_पढ़ो;
	अगर (length < OPTROM_BURST_SIZE)
		जाओ slow_पढ़ो;

try_fast:
	अगर (offset & 0xff)
		जाओ slow_पढ़ो;
	optrom = dma_alloc_coherent(&ha->pdev->dev, OPTROM_BURST_SIZE,
	    &optrom_dma, GFP_KERNEL);
	अगर (!optrom) अणु
		ql_log(ql_log_warn, vha, 0x00cc,
		    "Unable to allocate memory for optrom burst read (%x KB).\n",
		    OPTROM_BURST_SIZE / 1024);
		जाओ slow_पढ़ो;
	पूर्ण

	pbuf = buf;
	faddr = offset >> 2;
	left = length >> 2;
	burst = OPTROM_BURST_DWORDS;
	जबतक (left != 0) अणु
		अगर (burst > left)
			burst = left;

		rval = qla2x00_dump_ram(vha, optrom_dma,
		    flash_data_addr(ha, faddr), burst);
		अगर (rval) अणु
			ql_log(ql_log_warn, vha, 0x00f5,
			    "Unable to burst-read optrom segment (%x/%x/%llx).\n",
			    rval, flash_data_addr(ha, faddr),
			    (अचिन्हित दीर्घ दीर्घ)optrom_dma);
			ql_log(ql_log_warn, vha, 0x00f6,
			    "Reverting to slow-read.\n");

			dma_मुक्त_coherent(&ha->pdev->dev, OPTROM_BURST_SIZE,
			    optrom, optrom_dma);
			जाओ slow_पढ़ो;
		पूर्ण

		स_नकल(pbuf, optrom, burst * 4);

		left -= burst;
		faddr += burst;
		pbuf += burst * 4;
	पूर्ण

	dma_मुक्त_coherent(&ha->pdev->dev, OPTROM_BURST_SIZE, optrom,
	    optrom_dma);

	वापस buf;

slow_पढ़ो:
    वापस qla24xx_पढ़ो_optrom_data(vha, buf, offset, length);
पूर्ण

/**
 * qla2x00_get_fcode_version() - Determine an FCODE image's version.
 * @ha: HA context
 * @pcids: Poपूर्णांकer to the FCODE PCI data काष्ठाure
 *
 * The process of retrieving the FCODE version inक्रमmation is at best
 * described as पूर्णांकeresting.
 *
 * Within the first 100h bytes of the image an ASCII string is present
 * which contains several pieces of inक्रमmation including the FCODE
 * version.  Unक्रमtunately it seems the only reliable way to retrieve
 * the version is by scanning क्रम another sentinel within the string,
 * the FCODE build date:
 *
 *	... 2.00.02 10/17/02 ...
 *
 * Returns QLA_SUCCESS on successful retrieval of version.
 */
अटल व्योम
qla2x00_get_fcode_version(काष्ठा qla_hw_data *ha, uपूर्णांक32_t pcids)
अणु
	पूर्णांक ret = QLA_FUNCTION_FAILED;
	uपूर्णांक32_t istart, iend, iter, vend;
	uपूर्णांक8_t करो_next, rbyte, *vbyte;

	स_रखो(ha->fcode_revision, 0, माप(ha->fcode_revision));

	/* Skip the PCI data काष्ठाure. */
	istart = pcids +
	    ((qla2x00_पढ़ो_flash_byte(ha, pcids + 0x0B) << 8) |
		qla2x00_पढ़ो_flash_byte(ha, pcids + 0x0A));
	iend = istart + 0x100;
	करो अणु
		/* Scan क्रम the sentinel date string...eeewww. */
		करो_next = 0;
		iter = istart;
		जबतक ((iter < iend) && !करो_next) अणु
			iter++;
			अगर (qla2x00_पढ़ो_flash_byte(ha, iter) == '/') अणु
				अगर (qla2x00_पढ़ो_flash_byte(ha, iter + 2) ==
				    '/')
					करो_next++;
				अन्यथा अगर (qla2x00_पढ़ो_flash_byte(ha,
				    iter + 3) == '/')
					करो_next++;
			पूर्ण
		पूर्ण
		अगर (!करो_next)
			अवरोध;

		/* Backtrack to previous ' ' (space). */
		करो_next = 0;
		जबतक ((iter > istart) && !करो_next) अणु
			iter--;
			अगर (qla2x00_पढ़ो_flash_byte(ha, iter) == ' ')
				करो_next++;
		पूर्ण
		अगर (!करो_next)
			अवरोध;

		/*
		 * Mark end of version tag, and find previous ' ' (space) or
		 * string length (recent FCODE images -- major hack ahead!!!).
		 */
		vend = iter - 1;
		करो_next = 0;
		जबतक ((iter > istart) && !करो_next) अणु
			iter--;
			rbyte = qla2x00_पढ़ो_flash_byte(ha, iter);
			अगर (rbyte == ' ' || rbyte == 0xd || rbyte == 0x10)
				करो_next++;
		पूर्ण
		अगर (!करो_next)
			अवरोध;

		/* Mark beginning of version tag, and copy data. */
		iter++;
		अगर ((vend - iter) &&
		    ((vend - iter) < माप(ha->fcode_revision))) अणु
			vbyte = ha->fcode_revision;
			जबतक (iter <= vend) अणु
				*vbyte++ = qla2x00_पढ़ो_flash_byte(ha, iter);
				iter++;
			पूर्ण
			ret = QLA_SUCCESS;
		पूर्ण
	पूर्ण जबतक (0);

	अगर (ret != QLA_SUCCESS)
		स_रखो(ha->fcode_revision, 0, माप(ha->fcode_revision));
पूर्ण

पूर्णांक
qla2x00_get_flash_version(scsi_qla_host_t *vha, व्योम *mbuf)
अणु
	पूर्णांक ret = QLA_SUCCESS;
	uपूर्णांक8_t code_type, last_image;
	uपूर्णांक32_t pcihdr, pcids;
	uपूर्णांक8_t *dbyte;
	uपूर्णांक16_t *dcode;
	काष्ठा qla_hw_data *ha = vha->hw;

	अगर (!ha->pio_address || !mbuf)
		वापस QLA_FUNCTION_FAILED;

	स_रखो(ha->bios_revision, 0, माप(ha->bios_revision));
	स_रखो(ha->efi_revision, 0, माप(ha->efi_revision));
	स_रखो(ha->fcode_revision, 0, माप(ha->fcode_revision));
	स_रखो(ha->fw_revision, 0, माप(ha->fw_revision));

	qla2x00_flash_enable(ha);

	/* Begin with first PCI expansion ROM header. */
	pcihdr = 0;
	last_image = 1;
	करो अणु
		/* Verअगरy PCI expansion ROM header. */
		अगर (qla2x00_पढ़ो_flash_byte(ha, pcihdr) != 0x55 ||
		    qla2x00_पढ़ो_flash_byte(ha, pcihdr + 0x01) != 0xaa) अणु
			/* No signature */
			ql_log(ql_log_fatal, vha, 0x0050,
			    "No matching ROM signature.\n");
			ret = QLA_FUNCTION_FAILED;
			अवरोध;
		पूर्ण

		/* Locate PCI data काष्ठाure. */
		pcids = pcihdr +
		    ((qla2x00_पढ़ो_flash_byte(ha, pcihdr + 0x19) << 8) |
			qla2x00_पढ़ो_flash_byte(ha, pcihdr + 0x18));

		/* Validate signature of PCI data काष्ठाure. */
		अगर (qla2x00_पढ़ो_flash_byte(ha, pcids) != 'P' ||
		    qla2x00_पढ़ो_flash_byte(ha, pcids + 0x1) != 'C' ||
		    qla2x00_पढ़ो_flash_byte(ha, pcids + 0x2) != 'I' ||
		    qla2x00_पढ़ो_flash_byte(ha, pcids + 0x3) != 'R') अणु
			/* Incorrect header. */
			ql_log(ql_log_fatal, vha, 0x0051,
			    "PCI data struct not found pcir_adr=%x.\n", pcids);
			ret = QLA_FUNCTION_FAILED;
			अवरोध;
		पूर्ण

		/* Read version */
		code_type = qla2x00_पढ़ो_flash_byte(ha, pcids + 0x14);
		चयन (code_type) अणु
		हाल ROM_CODE_TYPE_BIOS:
			/* Intel x86, PC-AT compatible. */
			ha->bios_revision[0] =
			    qla2x00_पढ़ो_flash_byte(ha, pcids + 0x12);
			ha->bios_revision[1] =
			    qla2x00_पढ़ो_flash_byte(ha, pcids + 0x13);
			ql_dbg(ql_dbg_init, vha, 0x0052,
			    "Read BIOS %d.%d.\n",
			    ha->bios_revision[1], ha->bios_revision[0]);
			अवरोध;
		हाल ROM_CODE_TYPE_FCODE:
			/* Open Firmware standard क्रम PCI (FCode). */
			/* Eeeewww... */
			qla2x00_get_fcode_version(ha, pcids);
			अवरोध;
		हाल ROM_CODE_TYPE_EFI:
			/* Extensible Firmware Interface (EFI). */
			ha->efi_revision[0] =
			    qla2x00_पढ़ो_flash_byte(ha, pcids + 0x12);
			ha->efi_revision[1] =
			    qla2x00_पढ़ो_flash_byte(ha, pcids + 0x13);
			ql_dbg(ql_dbg_init, vha, 0x0053,
			    "Read EFI %d.%d.\n",
			    ha->efi_revision[1], ha->efi_revision[0]);
			अवरोध;
		शेष:
			ql_log(ql_log_warn, vha, 0x0054,
			    "Unrecognized code type %x at pcids %x.\n",
			    code_type, pcids);
			अवरोध;
		पूर्ण

		last_image = qla2x00_पढ़ो_flash_byte(ha, pcids + 0x15) & BIT_7;

		/* Locate next PCI expansion ROM. */
		pcihdr += ((qla2x00_पढ़ो_flash_byte(ha, pcids + 0x11) << 8) |
		    qla2x00_पढ़ो_flash_byte(ha, pcids + 0x10)) * 512;
	पूर्ण जबतक (!last_image);

	अगर (IS_QLA2322(ha)) अणु
		/* Read firmware image inक्रमmation. */
		स_रखो(ha->fw_revision, 0, माप(ha->fw_revision));
		dbyte = mbuf;
		स_रखो(dbyte, 0, 8);
		dcode = (uपूर्णांक16_t *)dbyte;

		qla2x00_पढ़ो_flash_data(ha, dbyte, ha->flt_region_fw * 4 + 10,
		    8);
		ql_dbg(ql_dbg_init + ql_dbg_buffer, vha, 0x010a,
		    "Dumping fw "
		    "ver from flash:.\n");
		ql_dump_buffer(ql_dbg_init + ql_dbg_buffer, vha, 0x010b,
		    dbyte, 32);

		अगर ((dcode[0] == 0xffff && dcode[1] == 0xffff &&
		    dcode[2] == 0xffff && dcode[3] == 0xffff) ||
		    (dcode[0] == 0 && dcode[1] == 0 && dcode[2] == 0 &&
		    dcode[3] == 0)) अणु
			ql_log(ql_log_warn, vha, 0x0057,
			    "Unrecognized fw revision at %x.\n",
			    ha->flt_region_fw * 4);
		पूर्ण अन्यथा अणु
			/* values are in big endian */
			ha->fw_revision[0] = dbyte[0] << 16 | dbyte[1];
			ha->fw_revision[1] = dbyte[2] << 16 | dbyte[3];
			ha->fw_revision[2] = dbyte[4] << 16 | dbyte[5];
			ql_dbg(ql_dbg_init, vha, 0x0058,
			    "FW Version: "
			    "%d.%d.%d.\n", ha->fw_revision[0],
			    ha->fw_revision[1], ha->fw_revision[2]);
		पूर्ण
	पूर्ण

	qla2x00_flash_disable(ha);

	वापस ret;
पूर्ण

पूर्णांक
qla82xx_get_flash_version(scsi_qla_host_t *vha, व्योम *mbuf)
अणु
	पूर्णांक ret = QLA_SUCCESS;
	uपूर्णांक32_t pcihdr, pcids;
	uपूर्णांक32_t *dcode = mbuf;
	uपूर्णांक8_t *bcode = mbuf;
	uपूर्णांक8_t code_type, last_image;
	काष्ठा qla_hw_data *ha = vha->hw;

	अगर (!mbuf)
		वापस QLA_FUNCTION_FAILED;

	स_रखो(ha->bios_revision, 0, माप(ha->bios_revision));
	स_रखो(ha->efi_revision, 0, माप(ha->efi_revision));
	स_रखो(ha->fcode_revision, 0, माप(ha->fcode_revision));
	स_रखो(ha->fw_revision, 0, माप(ha->fw_revision));

	/* Begin with first PCI expansion ROM header. */
	pcihdr = ha->flt_region_boot << 2;
	last_image = 1;
	करो अणु
		/* Verअगरy PCI expansion ROM header. */
		ha->isp_ops->पढ़ो_optrom(vha, dcode, pcihdr, 0x20 * 4);
		bcode = mbuf + (pcihdr % 4);
		अगर (स_भेद(bcode, "\x55\xaa", 2)) अणु
			/* No signature */
			ql_log(ql_log_fatal, vha, 0x0154,
			    "No matching ROM signature.\n");
			ret = QLA_FUNCTION_FAILED;
			अवरोध;
		पूर्ण

		/* Locate PCI data काष्ठाure. */
		pcids = pcihdr + ((bcode[0x19] << 8) | bcode[0x18]);

		ha->isp_ops->पढ़ो_optrom(vha, dcode, pcids, 0x20 * 4);
		bcode = mbuf + (pcihdr % 4);

		/* Validate signature of PCI data काष्ठाure. */
		अगर (स_भेद(bcode, "PCIR", 4)) अणु
			/* Incorrect header. */
			ql_log(ql_log_fatal, vha, 0x0155,
			    "PCI data struct not found pcir_adr=%x.\n", pcids);
			ret = QLA_FUNCTION_FAILED;
			अवरोध;
		पूर्ण

		/* Read version */
		code_type = bcode[0x14];
		चयन (code_type) अणु
		हाल ROM_CODE_TYPE_BIOS:
			/* Intel x86, PC-AT compatible. */
			ha->bios_revision[0] = bcode[0x12];
			ha->bios_revision[1] = bcode[0x13];
			ql_dbg(ql_dbg_init, vha, 0x0156,
			    "Read BIOS %d.%d.\n",
			    ha->bios_revision[1], ha->bios_revision[0]);
			अवरोध;
		हाल ROM_CODE_TYPE_FCODE:
			/* Open Firmware standard क्रम PCI (FCode). */
			ha->fcode_revision[0] = bcode[0x12];
			ha->fcode_revision[1] = bcode[0x13];
			ql_dbg(ql_dbg_init, vha, 0x0157,
			    "Read FCODE %d.%d.\n",
			    ha->fcode_revision[1], ha->fcode_revision[0]);
			अवरोध;
		हाल ROM_CODE_TYPE_EFI:
			/* Extensible Firmware Interface (EFI). */
			ha->efi_revision[0] = bcode[0x12];
			ha->efi_revision[1] = bcode[0x13];
			ql_dbg(ql_dbg_init, vha, 0x0158,
			    "Read EFI %d.%d.\n",
			    ha->efi_revision[1], ha->efi_revision[0]);
			अवरोध;
		शेष:
			ql_log(ql_log_warn, vha, 0x0159,
			    "Unrecognized code type %x at pcids %x.\n",
			    code_type, pcids);
			अवरोध;
		पूर्ण

		last_image = bcode[0x15] & BIT_7;

		/* Locate next PCI expansion ROM. */
		pcihdr += ((bcode[0x11] << 8) | bcode[0x10]) * 512;
	पूर्ण जबतक (!last_image);

	/* Read firmware image inक्रमmation. */
	स_रखो(ha->fw_revision, 0, माप(ha->fw_revision));
	dcode = mbuf;
	ha->isp_ops->पढ़ो_optrom(vha, dcode, ha->flt_region_fw << 2, 0x20);
	bcode = mbuf + (pcihdr % 4);

	/* Validate signature of PCI data काष्ठाure. */
	अगर (bcode[0x0] == 0x3 && bcode[0x1] == 0x0 &&
	    bcode[0x2] == 0x40 && bcode[0x3] == 0x40) अणु
		ha->fw_revision[0] = bcode[0x4];
		ha->fw_revision[1] = bcode[0x5];
		ha->fw_revision[2] = bcode[0x6];
		ql_dbg(ql_dbg_init, vha, 0x0153,
		    "Firmware revision %d.%d.%d\n",
		    ha->fw_revision[0], ha->fw_revision[1],
		    ha->fw_revision[2]);
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक
qla24xx_get_flash_version(scsi_qla_host_t *vha, व्योम *mbuf)
अणु
	पूर्णांक ret = QLA_SUCCESS;
	uपूर्णांक32_t pcihdr = 0, pcids = 0;
	uपूर्णांक32_t *dcode = mbuf;
	uपूर्णांक8_t *bcode = mbuf;
	uपूर्णांक8_t code_type, last_image;
	पूर्णांक i;
	काष्ठा qla_hw_data *ha = vha->hw;
	uपूर्णांक32_t faddr = 0;
	काष्ठा active_regions active_regions = अणु पूर्ण;

	अगर (IS_P3P_TYPE(ha))
		वापस ret;

	अगर (!mbuf)
		वापस QLA_FUNCTION_FAILED;

	स_रखो(ha->bios_revision, 0, माप(ha->bios_revision));
	स_रखो(ha->efi_revision, 0, माप(ha->efi_revision));
	स_रखो(ha->fcode_revision, 0, माप(ha->fcode_revision));
	स_रखो(ha->fw_revision, 0, माप(ha->fw_revision));

	pcihdr = ha->flt_region_boot << 2;
	अगर (IS_QLA27XX(ha) || IS_QLA28XX(ha)) अणु
		qla27xx_get_active_image(vha, &active_regions);
		अगर (active_regions.global == QLA27XX_SECONDARY_IMAGE) अणु
			pcihdr = ha->flt_region_boot_sec << 2;
		पूर्ण
	पूर्ण

	करो अणु
		/* Verअगरy PCI expansion ROM header. */
		qla24xx_पढ़ो_flash_data(vha, dcode, pcihdr >> 2, 0x20);
		bcode = mbuf + (pcihdr % 4);
		अगर (स_भेद(bcode, "\x55\xaa", 2)) अणु
			/* No signature */
			ql_log(ql_log_fatal, vha, 0x0059,
			    "No matching ROM signature.\n");
			ret = QLA_FUNCTION_FAILED;
			अवरोध;
		पूर्ण

		/* Locate PCI data काष्ठाure. */
		pcids = pcihdr + ((bcode[0x19] << 8) | bcode[0x18]);

		qla24xx_पढ़ो_flash_data(vha, dcode, pcids >> 2, 0x20);
		bcode = mbuf + (pcihdr % 4);

		/* Validate signature of PCI data काष्ठाure. */
		अगर (स_भेद(bcode, "PCIR", 4)) अणु
			/* Incorrect header. */
			ql_log(ql_log_fatal, vha, 0x005a,
			    "PCI data struct not found pcir_adr=%x.\n", pcids);
			ql_dump_buffer(ql_dbg_init, vha, 0x0059, dcode, 32);
			ret = QLA_FUNCTION_FAILED;
			अवरोध;
		पूर्ण

		/* Read version */
		code_type = bcode[0x14];
		चयन (code_type) अणु
		हाल ROM_CODE_TYPE_BIOS:
			/* Intel x86, PC-AT compatible. */
			ha->bios_revision[0] = bcode[0x12];
			ha->bios_revision[1] = bcode[0x13];
			ql_dbg(ql_dbg_init, vha, 0x005b,
			    "Read BIOS %d.%d.\n",
			    ha->bios_revision[1], ha->bios_revision[0]);
			अवरोध;
		हाल ROM_CODE_TYPE_FCODE:
			/* Open Firmware standard क्रम PCI (FCode). */
			ha->fcode_revision[0] = bcode[0x12];
			ha->fcode_revision[1] = bcode[0x13];
			ql_dbg(ql_dbg_init, vha, 0x005c,
			    "Read FCODE %d.%d.\n",
			    ha->fcode_revision[1], ha->fcode_revision[0]);
			अवरोध;
		हाल ROM_CODE_TYPE_EFI:
			/* Extensible Firmware Interface (EFI). */
			ha->efi_revision[0] = bcode[0x12];
			ha->efi_revision[1] = bcode[0x13];
			ql_dbg(ql_dbg_init, vha, 0x005d,
			    "Read EFI %d.%d.\n",
			    ha->efi_revision[1], ha->efi_revision[0]);
			अवरोध;
		शेष:
			ql_log(ql_log_warn, vha, 0x005e,
			    "Unrecognized code type %x at pcids %x.\n",
			    code_type, pcids);
			अवरोध;
		पूर्ण

		last_image = bcode[0x15] & BIT_7;

		/* Locate next PCI expansion ROM. */
		pcihdr += ((bcode[0x11] << 8) | bcode[0x10]) * 512;
	पूर्ण जबतक (!last_image);

	/* Read firmware image inक्रमmation. */
	स_रखो(ha->fw_revision, 0, माप(ha->fw_revision));
	faddr = ha->flt_region_fw;
	अगर (IS_QLA27XX(ha) || IS_QLA28XX(ha)) अणु
		qla27xx_get_active_image(vha, &active_regions);
		अगर (active_regions.global == QLA27XX_SECONDARY_IMAGE)
			faddr = ha->flt_region_fw_sec;
	पूर्ण

	qla24xx_पढ़ो_flash_data(vha, dcode, faddr, 8);
	अगर (qla24xx_risc_firmware_invalid(dcode)) अणु
		ql_log(ql_log_warn, vha, 0x005f,
		    "Unrecognized fw revision at %x.\n",
		    ha->flt_region_fw * 4);
		ql_dump_buffer(ql_dbg_init, vha, 0x005f, dcode, 32);
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < 4; i++)
			ha->fw_revision[i] =
				be32_to_cpu((__क्रमce __be32)dcode[4+i]);
		ql_dbg(ql_dbg_init, vha, 0x0060,
		    "Firmware revision (flash) %u.%u.%u (%x).\n",
		    ha->fw_revision[0], ha->fw_revision[1],
		    ha->fw_revision[2], ha->fw_revision[3]);
	पूर्ण

	/* Check क्रम golden firmware and get version अगर available */
	अगर (!IS_QLA81XX(ha)) अणु
		/* Golden firmware is not present in non 81XX adapters */
		वापस ret;
	पूर्ण

	स_रखो(ha->gold_fw_version, 0, माप(ha->gold_fw_version));
	faddr = ha->flt_region_gold_fw;
	qla24xx_पढ़ो_flash_data(vha, dcode, ha->flt_region_gold_fw, 8);
	अगर (qla24xx_risc_firmware_invalid(dcode)) अणु
		ql_log(ql_log_warn, vha, 0x0056,
		    "Unrecognized golden fw at %#x.\n", faddr);
		ql_dump_buffer(ql_dbg_init, vha, 0x0056, dcode, 32);
		वापस ret;
	पूर्ण

	क्रम (i = 0; i < 4; i++)
		ha->gold_fw_version[i] =
			be32_to_cpu((__क्रमce __be32)dcode[4+i]);

	वापस ret;
पूर्ण

अटल पूर्णांक
qla2xxx_is_vpd_valid(uपूर्णांक8_t *pos, uपूर्णांक8_t *end)
अणु
	अगर (pos >= end || *pos != 0x82)
		वापस 0;

	pos += 3 + pos[1];
	अगर (pos >= end || *pos != 0x90)
		वापस 0;

	pos += 3 + pos[1];
	अगर (pos >= end || *pos != 0x78)
		वापस 0;

	वापस 1;
पूर्ण

पूर्णांक
qla2xxx_get_vpd_field(scsi_qla_host_t *vha, अक्षर *key, अक्षर *str, माप_प्रकार size)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;
	uपूर्णांक8_t *pos = ha->vpd;
	uपूर्णांक8_t *end = pos + ha->vpd_size;
	पूर्णांक len = 0;

	अगर (!IS_FWI2_CAPABLE(ha) || !qla2xxx_is_vpd_valid(pos, end))
		वापस 0;

	जबतक (pos < end && *pos != 0x78) अणु
		len = (*pos == 0x82) ? pos[1] : pos[2];

		अगर (!म_भेदन(pos, key, म_माप(key)))
			अवरोध;

		अगर (*pos != 0x90 && *pos != 0x91)
			pos += len;

		pos += 3;
	पूर्ण

	अगर (pos < end - len && *pos != 0x78)
		वापस scnम_लिखो(str, size, "%.*s", len, pos + 3);

	वापस 0;
पूर्ण

पूर्णांक
qla24xx_पढ़ो_fcp_prio_cfg(scsi_qla_host_t *vha)
अणु
	पूर्णांक len, max_len;
	uपूर्णांक32_t fcp_prio_addr;
	काष्ठा qla_hw_data *ha = vha->hw;

	अगर (!ha->fcp_prio_cfg) अणु
		ha->fcp_prio_cfg = vदो_स्मृति(FCP_PRIO_CFG_SIZE);
		अगर (!ha->fcp_prio_cfg) अणु
			ql_log(ql_log_warn, vha, 0x00d5,
			    "Unable to allocate memory for fcp priority data (%x).\n",
			    FCP_PRIO_CFG_SIZE);
			वापस QLA_FUNCTION_FAILED;
		पूर्ण
	पूर्ण
	स_रखो(ha->fcp_prio_cfg, 0, FCP_PRIO_CFG_SIZE);

	fcp_prio_addr = ha->flt_region_fcp_prio;

	/* first पढ़ो the fcp priority data header from flash */
	ha->isp_ops->पढ़ो_optrom(vha, ha->fcp_prio_cfg,
			fcp_prio_addr << 2, FCP_PRIO_CFG_HDR_SIZE);

	अगर (!qla24xx_fcp_prio_cfg_valid(vha, ha->fcp_prio_cfg, 0))
		जाओ fail;

	/* पढ़ो reमुख्यing FCP CMD config data from flash */
	fcp_prio_addr += (FCP_PRIO_CFG_HDR_SIZE >> 2);
	len = ha->fcp_prio_cfg->num_entries * माप(काष्ठा qla_fcp_prio_entry);
	max_len = FCP_PRIO_CFG_SIZE - FCP_PRIO_CFG_HDR_SIZE;

	ha->isp_ops->पढ़ो_optrom(vha, &ha->fcp_prio_cfg->entry[0],
			fcp_prio_addr << 2, (len < max_len ? len : max_len));

	/* revalidate the entire FCP priority config data, including entries */
	अगर (!qla24xx_fcp_prio_cfg_valid(vha, ha->fcp_prio_cfg, 1))
		जाओ fail;

	ha->flags.fcp_prio_enabled = 1;
	वापस QLA_SUCCESS;
fail:
	vमुक्त(ha->fcp_prio_cfg);
	ha->fcp_prio_cfg = शून्य;
	वापस QLA_FUNCTION_FAILED;
पूर्ण
