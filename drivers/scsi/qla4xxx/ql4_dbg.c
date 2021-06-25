<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * QLogic iSCSI HBA Driver
 * Copyright (c)  2003-2012 QLogic Corporation
 */

#समावेश "ql4_def.h"
#समावेश "ql4_glbl.h"
#समावेश "ql4_dbg.h"
#समावेश "ql4_inline.h"

व्योम qla4xxx_dump_buffer(व्योम *b, uपूर्णांक32_t size)
अणु
	uपूर्णांक32_t cnt;
	uपूर्णांक8_t *c = b;

	prपूर्णांकk(" 0   1   2   3   4   5   6   7   8   9  Ah  Bh  Ch  Dh  Eh  "
	       "Fh\n");
	prपूर्णांकk("------------------------------------------------------------"
	       "--\n");
	क्रम (cnt = 0; cnt < size; c++) अणु
		prपूर्णांकk("%02x", *c);
		अगर (!(++cnt % 16))
			prपूर्णांकk("\n");

		अन्यथा
			prपूर्णांकk("  ");
	पूर्ण
	prपूर्णांकk(KERN_INFO "\n");
पूर्ण

व्योम qla4xxx_dump_रेजिस्टरs(काष्ठा scsi_qla_host *ha)
अणु
	uपूर्णांक8_t i;

	अगर (is_qla8022(ha)) अणु
		क्रम (i = 1; i < MBOX_REG_COUNT; i++)
			prपूर्णांकk(KERN_INFO "mailbox[%d]     = 0x%08X\n",
			    i, पढ़ोl(&ha->qla4_82xx_reg->mailbox_in[i]));
		वापस;
	पूर्ण

	क्रम (i = 0; i < MBOX_REG_COUNT; i++) अणु
		prपूर्णांकk(KERN_INFO "0x%02X mailbox[%d]      = 0x%08X\n",
		    (uपूर्णांक8_t) दुरत्व(काष्ठा isp_reg, mailbox[i]), i,
		    पढ़ोw(&ha->reg->mailbox[i]));
	पूर्ण

	prपूर्णांकk(KERN_INFO "0x%02X flash_address            = 0x%08X\n",
	    (uपूर्णांक8_t) दुरत्व(काष्ठा isp_reg, flash_address),
	    पढ़ोw(&ha->reg->flash_address));
	prपूर्णांकk(KERN_INFO "0x%02X flash_data               = 0x%08X\n",
	    (uपूर्णांक8_t) दुरत्व(काष्ठा isp_reg, flash_data),
	    पढ़ोw(&ha->reg->flash_data));
	prपूर्णांकk(KERN_INFO "0x%02X ctrl_status              = 0x%08X\n",
	    (uपूर्णांक8_t) दुरत्व(काष्ठा isp_reg, ctrl_status),
	    पढ़ोw(&ha->reg->ctrl_status));

	अगर (is_qla4010(ha)) अणु
		prपूर्णांकk(KERN_INFO "0x%02X nvram            = 0x%08X\n",
		    (uपूर्णांक8_t) दुरत्व(काष्ठा isp_reg, u1.isp4010.nvram),
		    पढ़ोw(&ha->reg->u1.isp4010.nvram));
	पूर्ण अन्यथा अगर (is_qla4022(ha) | is_qla4032(ha)) अणु
		prपूर्णांकk(KERN_INFO "0x%02X intr_mask        = 0x%08X\n",
		    (uपूर्णांक8_t) दुरत्व(काष्ठा isp_reg, u1.isp4022.पूर्णांकr_mask),
		    पढ़ोw(&ha->reg->u1.isp4022.पूर्णांकr_mask));
		prपूर्णांकk(KERN_INFO "0x%02X nvram            = 0x%08X\n",
		    (uपूर्णांक8_t) दुरत्व(काष्ठा isp_reg, u1.isp4022.nvram),
		    पढ़ोw(&ha->reg->u1.isp4022.nvram));
		prपूर्णांकk(KERN_INFO "0x%02X semaphore	  = 0x%08X\n",
		    (uपूर्णांक8_t) दुरत्व(काष्ठा isp_reg, u1.isp4022.semaphore),
		    पढ़ोw(&ha->reg->u1.isp4022.semaphore));
	पूर्ण
	prपूर्णांकk(KERN_INFO "0x%02X req_q_in                 = 0x%08X\n",
	    (uपूर्णांक8_t) दुरत्व(काष्ठा isp_reg, req_q_in),
	    पढ़ोw(&ha->reg->req_q_in));
	prपूर्णांकk(KERN_INFO "0x%02X rsp_q_out                = 0x%08X\n",
	    (uपूर्णांक8_t) दुरत्व(काष्ठा isp_reg, rsp_q_out),
	    पढ़ोw(&ha->reg->rsp_q_out));

	अगर (is_qla4010(ha)) अणु
		prपूर्णांकk(KERN_INFO "0x%02X ext_hw_conf      = 0x%08X\n",
		    (uपूर्णांक8_t) दुरत्व(काष्ठा isp_reg, u2.isp4010.ext_hw_conf),
		    पढ़ोw(&ha->reg->u2.isp4010.ext_hw_conf));
		prपूर्णांकk(KERN_INFO "0x%02X port_ctrl        = 0x%08X\n",
		    (uपूर्णांक8_t) दुरत्व(काष्ठा isp_reg, u2.isp4010.port_ctrl),
		    पढ़ोw(&ha->reg->u2.isp4010.port_ctrl));
		prपूर्णांकk(KERN_INFO "0x%02X port_status      = 0x%08X\n",
		    (uपूर्णांक8_t) दुरत्व(काष्ठा isp_reg, u2.isp4010.port_status),
		    पढ़ोw(&ha->reg->u2.isp4010.port_status));
		prपूर्णांकk(KERN_INFO "0x%02X req_q_out        = 0x%08X\n",
		    (uपूर्णांक8_t) दुरत्व(काष्ठा isp_reg, u2.isp4010.req_q_out),
		    पढ़ोw(&ha->reg->u2.isp4010.req_q_out));
		prपूर्णांकk(KERN_INFO "0x%02X gp_out           = 0x%08X\n",
		    (uपूर्णांक8_t) दुरत्व(काष्ठा isp_reg, u2.isp4010.gp_out),
		    पढ़ोw(&ha->reg->u2.isp4010.gp_out));
		prपूर्णांकk(KERN_INFO "0x%02X gp_in	          = 0x%08X\n",
		    (uपूर्णांक8_t) दुरत्व(काष्ठा isp_reg, u2.isp4010.gp_in),
		    पढ़ोw(&ha->reg->u2.isp4010.gp_in));
		prपूर्णांकk(KERN_INFO "0x%02X port_err_status  = 0x%08X\n", (uपूर्णांक8_t)
		    दुरत्व(काष्ठा isp_reg, u2.isp4010.port_err_status),
		    पढ़ोw(&ha->reg->u2.isp4010.port_err_status));
	पूर्ण अन्यथा अगर (is_qla4022(ha) | is_qla4032(ha)) अणु
		prपूर्णांकk(KERN_INFO "Page 0 Registers:\n");
		prपूर्णांकk(KERN_INFO "0x%02X ext_hw_conf      = 0x%08X\n", (uपूर्णांक8_t)
		    दुरत्व(काष्ठा isp_reg, u2.isp4022.p0.ext_hw_conf),
		    पढ़ोw(&ha->reg->u2.isp4022.p0.ext_hw_conf));
		prपूर्णांकk(KERN_INFO "0x%02X port_ctrl        = 0x%08X\n", (uपूर्णांक8_t)
		    दुरत्व(काष्ठा isp_reg, u2.isp4022.p0.port_ctrl),
		    पढ़ोw(&ha->reg->u2.isp4022.p0.port_ctrl));
		prपूर्णांकk(KERN_INFO "0x%02X port_status      = 0x%08X\n", (uपूर्णांक8_t)
		    दुरत्व(काष्ठा isp_reg, u2.isp4022.p0.port_status),
		    पढ़ोw(&ha->reg->u2.isp4022.p0.port_status));
		prपूर्णांकk(KERN_INFO "0x%02X gp_out           = 0x%08X\n",
		    (uपूर्णांक8_t) दुरत्व(काष्ठा isp_reg, u2.isp4022.p0.gp_out),
		    पढ़ोw(&ha->reg->u2.isp4022.p0.gp_out));
		prपूर्णांकk(KERN_INFO "0x%02X gp_in            = 0x%08X\n",
		    (uपूर्णांक8_t) दुरत्व(काष्ठा isp_reg, u2.isp4022.p0.gp_in),
		    पढ़ोw(&ha->reg->u2.isp4022.p0.gp_in));
		prपूर्णांकk(KERN_INFO "0x%02X port_err_status  = 0x%08X\n", (uपूर्णांक8_t)
		    दुरत्व(काष्ठा isp_reg, u2.isp4022.p0.port_err_status),
		    पढ़ोw(&ha->reg->u2.isp4022.p0.port_err_status));
		prपूर्णांकk(KERN_INFO "Page 1 Registers:\n");
		ग_लिखोl(HOST_MEM_CFG_PAGE & set_rmask(CSR_SCSI_PAGE_SELECT),
		    &ha->reg->ctrl_status);
		prपूर्णांकk(KERN_INFO "0x%02X req_q_out        = 0x%08X\n",
		    (uपूर्णांक8_t) दुरत्व(काष्ठा isp_reg, u2.isp4022.p1.req_q_out),
		    पढ़ोw(&ha->reg->u2.isp4022.p1.req_q_out));
		ग_लिखोl(PORT_CTRL_STAT_PAGE & set_rmask(CSR_SCSI_PAGE_SELECT),
		    &ha->reg->ctrl_status);
	पूर्ण
पूर्ण

व्योम qla4_8xxx_dump_peg_reg(काष्ठा scsi_qla_host *ha)
अणु
	uपूर्णांक32_t halt_status1, halt_status2;

	halt_status1 = qla4_8xxx_rd_direct(ha, QLA8XXX_PEG_HALT_STATUS1);
	halt_status2 = qla4_8xxx_rd_direct(ha, QLA8XXX_PEG_HALT_STATUS2);

	अगर (is_qla8022(ha)) अणु
		ql4_prपूर्णांकk(KERN_INFO, ha,
			   "scsi(%ld): %s, ISP%04x Dumping hw/fw registers:\n"
			   " PEG_HALT_STATUS1: 0x%x, PEG_HALT_STATUS2: 0x%x,\n"
			   " PEG_NET_0_PC: 0x%x, PEG_NET_1_PC: 0x%x,\n"
			   " PEG_NET_2_PC: 0x%x, PEG_NET_3_PC: 0x%x,\n"
			   " PEG_NET_4_PC: 0x%x\n", ha->host_no, __func__,
			   ha->pdev->device, halt_status1, halt_status2,
			   qla4_82xx_rd_32(ha, QLA82XX_CRB_PEG_NET_0 + 0x3c),
			   qla4_82xx_rd_32(ha, QLA82XX_CRB_PEG_NET_1 + 0x3c),
			   qla4_82xx_rd_32(ha, QLA82XX_CRB_PEG_NET_2 + 0x3c),
			   qla4_82xx_rd_32(ha, QLA82XX_CRB_PEG_NET_3 + 0x3c),
			   qla4_82xx_rd_32(ha, QLA82XX_CRB_PEG_NET_4 + 0x3c));
	पूर्ण अन्यथा अगर (is_qla8032(ha) || is_qla8042(ha)) अणु
		ql4_prपूर्णांकk(KERN_INFO, ha,
			   "scsi(%ld): %s, ISP%04x Dumping hw/fw registers:\n"
			   " PEG_HALT_STATUS1: 0x%x, PEG_HALT_STATUS2: 0x%x,\n",
			   ha->host_no, __func__, ha->pdev->device,
			   halt_status1, halt_status2);
	पूर्ण
पूर्ण
