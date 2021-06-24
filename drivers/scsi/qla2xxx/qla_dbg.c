<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * QLogic Fibre Channel HBA Driver
 * Copyright (c)  2003-2014 QLogic Corporation
 */

/*
 * Table क्रम showing the current message id in use क्रम particular level
 * Change this table क्रम addition of log/debug messages.
 * ----------------------------------------------------------------------
 * |             Level            |   Last Value Used  |     Holes	|
 * ----------------------------------------------------------------------
 * | Module Init and Probe        |       0x0199       |                |
 * | Mailbox commands             |       0x1206       | 0x11a5-0x11ff	|
 * | Device Discovery             |       0x2134       | 0x210e-0x2116  |
 * |				  | 		       | 0x211a         |
 * |                              |                    | 0x211c-0x2128  |
 * |                              |                    | 0x212c-0x2134  |
 * | Queue Command and IO tracing |       0x3074       | 0x300b         |
 * |                              |                    | 0x3027-0x3028  |
 * |                              |                    | 0x303d-0x3041  |
 * |                              |                    | 0x302d,0x3033  |
 * |                              |                    | 0x3036,0x3038  |
 * |                              |                    | 0x303a		|
 * | DPC Thपढ़ो                   |       0x4023       | 0x4002,0x4013  |
 * | Async Events                 |       0x509c       |                |
 * | Timer Routines               |       0x6012       |                |
 * | User Space Interactions      |       0x70e3       | 0x7018,0x702e  |
 * |				  |		       | 0x7020,0x7024  |
 * |                              |                    | 0x7039,0x7045  |
 * |                              |                    | 0x7073-0x7075  |
 * |                              |                    | 0x70a5-0x70a6  |
 * |                              |                    | 0x70a8,0x70ab  |
 * |                              |                    | 0x70ad-0x70ae  |
 * |                              |                    | 0x70d0-0x70d6	|
 * |                              |                    | 0x70d7-0x70db  |
 * | Task Management              |       0x8042       | 0x8000         |
 * |                              |                    | 0x8019         |
 * |                              |                    | 0x8025,0x8026  |
 * |                              |                    | 0x8031,0x8032  |
 * |                              |                    | 0x8039,0x803c  |
 * | AER/EEH                      |       0x9011       |		|
 * | Virtual Port                 |       0xa007       |		|
 * | ISP82XX Specअगरic             |       0xb157       | 0xb002,0xb024  |
 * |                              |                    | 0xb09e,0xb0ae  |
 * |				  |		       | 0xb0c3,0xb0c6  |
 * |                              |                    | 0xb0e0-0xb0ef  |
 * |                              |                    | 0xb085,0xb0dc  |
 * |                              |                    | 0xb107,0xb108  |
 * |                              |                    | 0xb111,0xb11e  |
 * |                              |                    | 0xb12c,0xb12d  |
 * |                              |                    | 0xb13a,0xb142  |
 * |                              |                    | 0xb13c-0xb140  |
 * |                              |                    | 0xb149		|
 * | MultiQ                       |       0xc010       |		|
 * | Misc                         |       0xd303       | 0xd031-0xd0ff	|
 * |                              |                    | 0xd101-0xd1fe	|
 * |                              |                    | 0xd214-0xd2fe	|
 * | Target Mode		  |	  0xe081       |		|
 * | Target Mode Management	  |	  0xf09b       | 0xf002		|
 * |                              |                    | 0xf046-0xf049  |
 * | Target Mode Task Management  |	  0x1000d      |		|
 * ----------------------------------------------------------------------
 */

#समावेश "qla_def.h"

#समावेश <linux/delay.h>
#घोषणा CREATE_TRACE_POINTS
#समावेश <trace/events/qla.h>

अटल uपूर्णांक32_t ql_dbg_offset = 0x800;

अटल अंतरभूत व्योम
qla2xxx_prep_dump(काष्ठा qla_hw_data *ha, काष्ठा qla2xxx_fw_dump *fw_dump)
अणु
	fw_dump->fw_major_version = htonl(ha->fw_major_version);
	fw_dump->fw_minor_version = htonl(ha->fw_minor_version);
	fw_dump->fw_subminor_version = htonl(ha->fw_subminor_version);
	fw_dump->fw_attributes = htonl(ha->fw_attributes);

	fw_dump->venकरोr = htonl(ha->pdev->venकरोr);
	fw_dump->device = htonl(ha->pdev->device);
	fw_dump->subप्रणाली_venकरोr = htonl(ha->pdev->subप्रणाली_venकरोr);
	fw_dump->subप्रणाली_device = htonl(ha->pdev->subप्रणाली_device);
पूर्ण

अटल अंतरभूत व्योम *
qla2xxx_copy_queues(काष्ठा qla_hw_data *ha, व्योम *ptr)
अणु
	काष्ठा req_que *req = ha->req_q_map[0];
	काष्ठा rsp_que *rsp = ha->rsp_q_map[0];
	/* Request queue. */
	स_नकल(ptr, req->ring, req->length *
	    माप(request_t));

	/* Response queue. */
	ptr += req->length * माप(request_t);
	स_नकल(ptr, rsp->ring, rsp->length  *
	    माप(response_t));

	वापस ptr + (rsp->length * माप(response_t));
पूर्ण

पूर्णांक
qla27xx_dump_mpi_ram(काष्ठा qla_hw_data *ha, uपूर्णांक32_t addr, uपूर्णांक32_t *ram,
	uपूर्णांक32_t ram_dwords, व्योम **nxt)
अणु
	काष्ठा device_reg_24xx __iomem *reg = &ha->iobase->isp24;
	dma_addr_t dump_dma = ha->gid_list_dma;
	uपूर्णांक32_t *chunk = (uपूर्णांक32_t *)ha->gid_list;
	uपूर्णांक32_t dwords = qla2x00_gid_list_size(ha) / 4;
	uपूर्णांक32_t stat;
	uदीर्घ i, j, समयr = 6000000;
	पूर्णांक rval = QLA_FUNCTION_FAILED;
	scsi_qla_host_t *vha = pci_get_drvdata(ha->pdev);

	clear_bit(MBX_INTERRUPT, &ha->mbx_cmd_flags);

	अगर (qla_pci_disconnected(vha, reg))
		वापस rval;

	क्रम (i = 0; i < ram_dwords; i += dwords, addr += dwords) अणु
		अगर (i + dwords > ram_dwords)
			dwords = ram_dwords - i;

		wrt_reg_word(&reg->mailbox0, MBC_LOAD_DUMP_MPI_RAM);
		wrt_reg_word(&reg->mailbox1, LSW(addr));
		wrt_reg_word(&reg->mailbox8, MSW(addr));

		wrt_reg_word(&reg->mailbox2, MSW(LSD(dump_dma)));
		wrt_reg_word(&reg->mailbox3, LSW(LSD(dump_dma)));
		wrt_reg_word(&reg->mailbox6, MSW(MSD(dump_dma)));
		wrt_reg_word(&reg->mailbox7, LSW(MSD(dump_dma)));

		wrt_reg_word(&reg->mailbox4, MSW(dwords));
		wrt_reg_word(&reg->mailbox5, LSW(dwords));

		wrt_reg_word(&reg->mailbox9, 0);
		wrt_reg_dword(&reg->hccr, HCCRX_SET_HOST_INT);

		ha->flags.mbox_पूर्णांक = 0;
		जबतक (समयr--) अणु
			udelay(5);

			अगर (qla_pci_disconnected(vha, reg))
				वापस rval;

			stat = rd_reg_dword(&reg->host_status);
			/* Check क्रम pending पूर्णांकerrupts. */
			अगर (!(stat & HSRX_RISC_INT))
				जारी;

			stat &= 0xff;
			अगर (stat != 0x1 && stat != 0x2 &&
			    stat != 0x10 && stat != 0x11) अणु

				/* Clear this पूर्णांकr; it wasn't a mailbox पूर्णांकr */
				wrt_reg_dword(&reg->hccr, HCCRX_CLR_RISC_INT);
				rd_reg_dword(&reg->hccr);
				जारी;
			पूर्ण

			set_bit(MBX_INTERRUPT, &ha->mbx_cmd_flags);
			rval = rd_reg_word(&reg->mailbox0) & MBS_MASK;
			wrt_reg_dword(&reg->hccr, HCCRX_CLR_RISC_INT);
			rd_reg_dword(&reg->hccr);
			अवरोध;
		पूर्ण
		ha->flags.mbox_पूर्णांक = 1;
		*nxt = ram + i;

		अगर (!test_and_clear_bit(MBX_INTERRUPT, &ha->mbx_cmd_flags)) अणु
			/* no पूर्णांकerrupt, समयd out*/
			वापस rval;
		पूर्ण
		अगर (rval) अणु
			/* error completion status */
			वापस rval;
		पूर्ण
		क्रम (j = 0; j < dwords; j++) अणु
			ram[i + j] =
			    (IS_QLA27XX(ha) || IS_QLA28XX(ha)) ?
			    chunk[j] : swab32(chunk[j]);
		पूर्ण
	पूर्ण

	*nxt = ram + i;
	वापस QLA_SUCCESS;
पूर्ण

पूर्णांक
qla24xx_dump_ram(काष्ठा qla_hw_data *ha, uपूर्णांक32_t addr, __be32 *ram,
		 uपूर्णांक32_t ram_dwords, व्योम **nxt)
अणु
	पूर्णांक rval = QLA_FUNCTION_FAILED;
	काष्ठा device_reg_24xx __iomem *reg = &ha->iobase->isp24;
	dma_addr_t dump_dma = ha->gid_list_dma;
	uपूर्णांक32_t *chunk = (uपूर्णांक32_t *)ha->gid_list;
	uपूर्णांक32_t dwords = qla2x00_gid_list_size(ha) / 4;
	uपूर्णांक32_t stat;
	uदीर्घ i, j, समयr = 6000000;
	scsi_qla_host_t *vha = pci_get_drvdata(ha->pdev);

	clear_bit(MBX_INTERRUPT, &ha->mbx_cmd_flags);

	अगर (qla_pci_disconnected(vha, reg))
		वापस rval;

	क्रम (i = 0; i < ram_dwords; i += dwords, addr += dwords) अणु
		अगर (i + dwords > ram_dwords)
			dwords = ram_dwords - i;

		wrt_reg_word(&reg->mailbox0, MBC_DUMP_RISC_RAM_EXTENDED);
		wrt_reg_word(&reg->mailbox1, LSW(addr));
		wrt_reg_word(&reg->mailbox8, MSW(addr));
		wrt_reg_word(&reg->mailbox10, 0);

		wrt_reg_word(&reg->mailbox2, MSW(LSD(dump_dma)));
		wrt_reg_word(&reg->mailbox3, LSW(LSD(dump_dma)));
		wrt_reg_word(&reg->mailbox6, MSW(MSD(dump_dma)));
		wrt_reg_word(&reg->mailbox7, LSW(MSD(dump_dma)));

		wrt_reg_word(&reg->mailbox4, MSW(dwords));
		wrt_reg_word(&reg->mailbox5, LSW(dwords));
		wrt_reg_dword(&reg->hccr, HCCRX_SET_HOST_INT);

		ha->flags.mbox_पूर्णांक = 0;
		जबतक (समयr--) अणु
			udelay(5);
			अगर (qla_pci_disconnected(vha, reg))
				वापस rval;

			stat = rd_reg_dword(&reg->host_status);
			/* Check क्रम pending पूर्णांकerrupts. */
			अगर (!(stat & HSRX_RISC_INT))
				जारी;

			stat &= 0xff;
			अगर (stat != 0x1 && stat != 0x2 &&
			    stat != 0x10 && stat != 0x11) अणु
				wrt_reg_dword(&reg->hccr, HCCRX_CLR_RISC_INT);
				rd_reg_dword(&reg->hccr);
				जारी;
			पूर्ण

			set_bit(MBX_INTERRUPT, &ha->mbx_cmd_flags);
			rval = rd_reg_word(&reg->mailbox0) & MBS_MASK;
			wrt_reg_dword(&reg->hccr, HCCRX_CLR_RISC_INT);
			rd_reg_dword(&reg->hccr);
			अवरोध;
		पूर्ण
		ha->flags.mbox_पूर्णांक = 1;
		*nxt = ram + i;

		अगर (!test_and_clear_bit(MBX_INTERRUPT, &ha->mbx_cmd_flags)) अणु
			/* no पूर्णांकerrupt, समयd out*/
			वापस rval;
		पूर्ण
		अगर (rval) अणु
			/* error completion status */
			वापस rval;
		पूर्ण
		क्रम (j = 0; j < dwords; j++) अणु
			ram[i + j] = (__क्रमce __be32)
				((IS_QLA27XX(ha) || IS_QLA28XX(ha)) ?
				 chunk[j] : swab32(chunk[j]));
		पूर्ण
	पूर्ण

	*nxt = ram + i;
	वापस QLA_SUCCESS;
पूर्ण

अटल पूर्णांक
qla24xx_dump_memory(काष्ठा qla_hw_data *ha, __be32 *code_ram,
		    uपूर्णांक32_t cram_size, व्योम **nxt)
अणु
	पूर्णांक rval;

	/* Code RAM. */
	rval = qla24xx_dump_ram(ha, 0x20000, code_ram, cram_size / 4, nxt);
	अगर (rval != QLA_SUCCESS)
		वापस rval;

	set_bit(RISC_SRAM_DUMP_CMPL, &ha->fw_dump_cap_flags);

	/* External Memory. */
	rval = qla24xx_dump_ram(ha, 0x100000, *nxt,
	    ha->fw_memory_size - 0x100000 + 1, nxt);
	अगर (rval == QLA_SUCCESS)
		set_bit(RISC_EXT_MEM_DUMP_CMPL, &ha->fw_dump_cap_flags);

	वापस rval;
पूर्ण

अटल __be32 *
qla24xx_पढ़ो_winकरोw(काष्ठा device_reg_24xx __iomem *reg, uपूर्णांक32_t iobase,
		    uपूर्णांक32_t count, __be32 *buf)
अणु
	__le32 __iomem *dmp_reg;

	wrt_reg_dword(&reg->iobase_addr, iobase);
	dmp_reg = &reg->iobase_winकरोw;
	क्रम ( ; count--; dmp_reg++)
		*buf++ = htonl(rd_reg_dword(dmp_reg));

	वापस buf;
पूर्ण

व्योम
qla24xx_छोड़ो_risc(काष्ठा device_reg_24xx __iomem *reg, काष्ठा qla_hw_data *ha)
अणु
	wrt_reg_dword(&reg->hccr, HCCRX_SET_RISC_PAUSE);

	/* 100 usec delay is sufficient enough क्रम hardware to छोड़ो RISC */
	udelay(100);
	अगर (rd_reg_dword(&reg->host_status) & HSRX_RISC_PAUSED)
		set_bit(RISC_PAUSE_CMPL, &ha->fw_dump_cap_flags);
पूर्ण

पूर्णांक
qla24xx_soft_reset(काष्ठा qla_hw_data *ha)
अणु
	पूर्णांक rval = QLA_SUCCESS;
	uपूर्णांक32_t cnt;
	uपूर्णांक16_t wd;
	काष्ठा device_reg_24xx __iomem *reg = &ha->iobase->isp24;

	/*
	 * Reset RISC. The delay is dependent on प्रणाली architecture.
	 * Driver can proceed with the reset sequence after रुकोing
	 * क्रम a समयout period.
	 */
	wrt_reg_dword(&reg->ctrl_status, CSRX_DMA_SHUTDOWN|MWB_4096_BYTES);
	क्रम (cnt = 0; cnt < 30000; cnt++) अणु
		अगर ((rd_reg_dword(&reg->ctrl_status) & CSRX_DMA_ACTIVE) == 0)
			अवरोध;

		udelay(10);
	पूर्ण
	अगर (!(rd_reg_dword(&reg->ctrl_status) & CSRX_DMA_ACTIVE))
		set_bit(DMA_SHUTDOWN_CMPL, &ha->fw_dump_cap_flags);

	wrt_reg_dword(&reg->ctrl_status,
	    CSRX_ISP_SOFT_RESET|CSRX_DMA_SHUTDOWN|MWB_4096_BYTES);
	pci_पढ़ो_config_word(ha->pdev, PCI_COMMAND, &wd);

	udelay(100);

	/* Wait क्रम soft-reset to complete. */
	क्रम (cnt = 0; cnt < 30000; cnt++) अणु
		अगर ((rd_reg_dword(&reg->ctrl_status) &
		    CSRX_ISP_SOFT_RESET) == 0)
			अवरोध;

		udelay(10);
	पूर्ण
	अगर (!(rd_reg_dword(&reg->ctrl_status) & CSRX_ISP_SOFT_RESET))
		set_bit(ISP_RESET_CMPL, &ha->fw_dump_cap_flags);

	wrt_reg_dword(&reg->hccr, HCCRX_CLR_RISC_RESET);
	rd_reg_dword(&reg->hccr);             /* PCI Posting. */

	क्रम (cnt = 10000; rd_reg_word(&reg->mailbox0) != 0 &&
	    rval == QLA_SUCCESS; cnt--) अणु
		अगर (cnt)
			udelay(10);
		अन्यथा
			rval = QLA_FUNCTION_TIMEOUT;
	पूर्ण
	अगर (rval == QLA_SUCCESS)
		set_bit(RISC_RDY_AFT_RESET, &ha->fw_dump_cap_flags);

	वापस rval;
पूर्ण

अटल पूर्णांक
qla2xxx_dump_ram(काष्ठा qla_hw_data *ha, uपूर्णांक32_t addr, __be16 *ram,
    uपूर्णांक32_t ram_words, व्योम **nxt)
अणु
	पूर्णांक rval;
	uपूर्णांक32_t cnt, stat, समयr, words, idx;
	uपूर्णांक16_t mb0;
	काष्ठा device_reg_2xxx __iomem *reg = &ha->iobase->isp;
	dma_addr_t dump_dma = ha->gid_list_dma;
	__le16 *dump = (__क्रमce __le16 *)ha->gid_list;

	rval = QLA_SUCCESS;
	mb0 = 0;

	WRT_MAILBOX_REG(ha, reg, 0, MBC_DUMP_RISC_RAM_EXTENDED);
	clear_bit(MBX_INTERRUPT, &ha->mbx_cmd_flags);

	words = qla2x00_gid_list_size(ha) / 2;
	क्रम (cnt = 0; cnt < ram_words && rval == QLA_SUCCESS;
	    cnt += words, addr += words) अणु
		अगर (cnt + words > ram_words)
			words = ram_words - cnt;

		WRT_MAILBOX_REG(ha, reg, 1, LSW(addr));
		WRT_MAILBOX_REG(ha, reg, 8, MSW(addr));

		WRT_MAILBOX_REG(ha, reg, 2, MSW(dump_dma));
		WRT_MAILBOX_REG(ha, reg, 3, LSW(dump_dma));
		WRT_MAILBOX_REG(ha, reg, 6, MSW(MSD(dump_dma)));
		WRT_MAILBOX_REG(ha, reg, 7, LSW(MSD(dump_dma)));

		WRT_MAILBOX_REG(ha, reg, 4, words);
		wrt_reg_word(&reg->hccr, HCCR_SET_HOST_INT);

		क्रम (समयr = 6000000; समयr; समयr--) अणु
			/* Check क्रम pending पूर्णांकerrupts. */
			stat = rd_reg_dword(&reg->u.isp2300.host_status);
			अगर (stat & HSR_RISC_INT) अणु
				stat &= 0xff;

				अगर (stat == 0x1 || stat == 0x2) अणु
					set_bit(MBX_INTERRUPT,
					    &ha->mbx_cmd_flags);

					mb0 = RD_MAILBOX_REG(ha, reg, 0);

					/* Release mailbox रेजिस्टरs. */
					wrt_reg_word(&reg->semaphore, 0);
					wrt_reg_word(&reg->hccr,
					    HCCR_CLR_RISC_INT);
					rd_reg_word(&reg->hccr);
					अवरोध;
				पूर्ण अन्यथा अगर (stat == 0x10 || stat == 0x11) अणु
					set_bit(MBX_INTERRUPT,
					    &ha->mbx_cmd_flags);

					mb0 = RD_MAILBOX_REG(ha, reg, 0);

					wrt_reg_word(&reg->hccr,
					    HCCR_CLR_RISC_INT);
					rd_reg_word(&reg->hccr);
					अवरोध;
				पूर्ण

				/* clear this पूर्णांकr; it wasn't a mailbox पूर्णांकr */
				wrt_reg_word(&reg->hccr, HCCR_CLR_RISC_INT);
				rd_reg_word(&reg->hccr);
			पूर्ण
			udelay(5);
		पूर्ण

		अगर (test_and_clear_bit(MBX_INTERRUPT, &ha->mbx_cmd_flags)) अणु
			rval = mb0 & MBS_MASK;
			क्रम (idx = 0; idx < words; idx++)
				ram[cnt + idx] =
					cpu_to_be16(le16_to_cpu(dump[idx]));
		पूर्ण अन्यथा अणु
			rval = QLA_FUNCTION_FAILED;
		पूर्ण
	पूर्ण

	*nxt = rval == QLA_SUCCESS ? &ram[cnt] : शून्य;
	वापस rval;
पूर्ण

अटल अंतरभूत व्योम
qla2xxx_पढ़ो_winकरोw(काष्ठा device_reg_2xxx __iomem *reg, uपूर्णांक32_t count,
		    __be16 *buf)
अणु
	__le16 __iomem *dmp_reg = &reg->u.isp2300.fb_cmd;

	क्रम ( ; count--; dmp_reg++)
		*buf++ = htons(rd_reg_word(dmp_reg));
पूर्ण

अटल अंतरभूत व्योम *
qla24xx_copy_eft(काष्ठा qla_hw_data *ha, व्योम *ptr)
अणु
	अगर (!ha->eft)
		वापस ptr;

	स_नकल(ptr, ha->eft, ntohl(ha->fw_dump->eft_size));
	वापस ptr + ntohl(ha->fw_dump->eft_size);
पूर्ण

अटल अंतरभूत व्योम *
qla25xx_copy_fce(काष्ठा qla_hw_data *ha, व्योम *ptr, __be32 **last_chain)
अणु
	uपूर्णांक32_t cnt;
	__be32 *iter_reg;
	काष्ठा qla2xxx_fce_chain *fcec = ptr;

	अगर (!ha->fce)
		वापस ptr;

	*last_chain = &fcec->type;
	fcec->type = htonl(DUMP_CHAIN_FCE);
	fcec->chain_size = htonl(माप(काष्ठा qla2xxx_fce_chain) +
	    fce_calc_size(ha->fce_bufs));
	fcec->size = htonl(fce_calc_size(ha->fce_bufs));
	fcec->addr_l = htonl(LSD(ha->fce_dma));
	fcec->addr_h = htonl(MSD(ha->fce_dma));

	iter_reg = fcec->eregs;
	क्रम (cnt = 0; cnt < 8; cnt++)
		*iter_reg++ = htonl(ha->fce_mb[cnt]);

	स_नकल(iter_reg, ha->fce, ntohl(fcec->size));

	वापस (अक्षर *)iter_reg + ntohl(fcec->size);
पूर्ण

अटल अंतरभूत व्योम *
qla25xx_copy_exlogin(काष्ठा qla_hw_data *ha, व्योम *ptr, __be32 **last_chain)
अणु
	काष्ठा qla2xxx_offld_chain *c = ptr;

	अगर (!ha->exlogin_buf)
		वापस ptr;

	*last_chain = &c->type;

	c->type = cpu_to_be32(DUMP_CHAIN_EXLOGIN);
	c->chain_size = cpu_to_be32(माप(काष्ठा qla2xxx_offld_chain) +
	    ha->exlogin_size);
	c->size = cpu_to_be32(ha->exlogin_size);
	c->addr = cpu_to_be64(ha->exlogin_buf_dma);

	ptr += माप(काष्ठा qla2xxx_offld_chain);
	स_नकल(ptr, ha->exlogin_buf, ha->exlogin_size);

	वापस (अक्षर *)ptr + be32_to_cpu(c->size);
पूर्ण

अटल अंतरभूत व्योम *
qla81xx_copy_exchoffld(काष्ठा qla_hw_data *ha, व्योम *ptr, __be32 **last_chain)
अणु
	काष्ठा qla2xxx_offld_chain *c = ptr;

	अगर (!ha->exchoffld_buf)
		वापस ptr;

	*last_chain = &c->type;

	c->type = cpu_to_be32(DUMP_CHAIN_EXCHG);
	c->chain_size = cpu_to_be32(माप(काष्ठा qla2xxx_offld_chain) +
	    ha->exchoffld_size);
	c->size = cpu_to_be32(ha->exchoffld_size);
	c->addr = cpu_to_be64(ha->exchoffld_buf_dma);

	ptr += माप(काष्ठा qla2xxx_offld_chain);
	स_नकल(ptr, ha->exchoffld_buf, ha->exchoffld_size);

	वापस (अक्षर *)ptr + be32_to_cpu(c->size);
पूर्ण

अटल अंतरभूत व्योम *
qla2xxx_copy_atioqueues(काष्ठा qla_hw_data *ha, व्योम *ptr,
			__be32 **last_chain)
अणु
	काष्ठा qla2xxx_mqueue_chain *q;
	काष्ठा qla2xxx_mqueue_header *qh;
	uपूर्णांक32_t num_queues;
	पूर्णांक que;
	काष्ठा अणु
		पूर्णांक length;
		व्योम *ring;
	पूर्ण aq, *aqp;

	अगर (!ha->tgt.atio_ring)
		वापस ptr;

	num_queues = 1;
	aqp = &aq;
	aqp->length = ha->tgt.atio_q_length;
	aqp->ring = ha->tgt.atio_ring;

	क्रम (que = 0; que < num_queues; que++) अणु
		/* aqp = ha->atio_q_map[que]; */
		q = ptr;
		*last_chain = &q->type;
		q->type = htonl(DUMP_CHAIN_QUEUE);
		q->chain_size = htonl(
		    माप(काष्ठा qla2xxx_mqueue_chain) +
		    माप(काष्ठा qla2xxx_mqueue_header) +
		    (aqp->length * माप(request_t)));
		ptr += माप(काष्ठा qla2xxx_mqueue_chain);

		/* Add header. */
		qh = ptr;
		qh->queue = htonl(TYPE_ATIO_QUEUE);
		qh->number = htonl(que);
		qh->size = htonl(aqp->length * माप(request_t));
		ptr += माप(काष्ठा qla2xxx_mqueue_header);

		/* Add data. */
		स_नकल(ptr, aqp->ring, aqp->length * माप(request_t));

		ptr += aqp->length * माप(request_t);
	पूर्ण

	वापस ptr;
पूर्ण

अटल अंतरभूत व्योम *
qla25xx_copy_mqueues(काष्ठा qla_hw_data *ha, व्योम *ptr, __be32 **last_chain)
अणु
	काष्ठा qla2xxx_mqueue_chain *q;
	काष्ठा qla2xxx_mqueue_header *qh;
	काष्ठा req_que *req;
	काष्ठा rsp_que *rsp;
	पूर्णांक que;

	अगर (!ha->mqenable)
		वापस ptr;

	/* Request queues */
	क्रम (que = 1; que < ha->max_req_queues; que++) अणु
		req = ha->req_q_map[que];
		अगर (!req)
			अवरोध;

		/* Add chain. */
		q = ptr;
		*last_chain = &q->type;
		q->type = htonl(DUMP_CHAIN_QUEUE);
		q->chain_size = htonl(
		    माप(काष्ठा qla2xxx_mqueue_chain) +
		    माप(काष्ठा qla2xxx_mqueue_header) +
		    (req->length * माप(request_t)));
		ptr += माप(काष्ठा qla2xxx_mqueue_chain);

		/* Add header. */
		qh = ptr;
		qh->queue = htonl(TYPE_REQUEST_QUEUE);
		qh->number = htonl(que);
		qh->size = htonl(req->length * माप(request_t));
		ptr += माप(काष्ठा qla2xxx_mqueue_header);

		/* Add data. */
		स_नकल(ptr, req->ring, req->length * माप(request_t));
		ptr += req->length * माप(request_t);
	पूर्ण

	/* Response queues */
	क्रम (que = 1; que < ha->max_rsp_queues; que++) अणु
		rsp = ha->rsp_q_map[que];
		अगर (!rsp)
			अवरोध;

		/* Add chain. */
		q = ptr;
		*last_chain = &q->type;
		q->type = htonl(DUMP_CHAIN_QUEUE);
		q->chain_size = htonl(
		    माप(काष्ठा qla2xxx_mqueue_chain) +
		    माप(काष्ठा qla2xxx_mqueue_header) +
		    (rsp->length * माप(response_t)));
		ptr += माप(काष्ठा qla2xxx_mqueue_chain);

		/* Add header. */
		qh = ptr;
		qh->queue = htonl(TYPE_RESPONSE_QUEUE);
		qh->number = htonl(que);
		qh->size = htonl(rsp->length * माप(response_t));
		ptr += माप(काष्ठा qla2xxx_mqueue_header);

		/* Add data. */
		स_नकल(ptr, rsp->ring, rsp->length * माप(response_t));
		ptr += rsp->length * माप(response_t);
	पूर्ण

	वापस ptr;
पूर्ण

अटल अंतरभूत व्योम *
qla25xx_copy_mq(काष्ठा qla_hw_data *ha, व्योम *ptr, __be32 **last_chain)
अणु
	uपूर्णांक32_t cnt, que_idx;
	uपूर्णांक8_t que_cnt;
	काष्ठा qla2xxx_mq_chain *mq = ptr;
	device_reg_t *reg;

	अगर (!ha->mqenable || IS_QLA83XX(ha) || IS_QLA27XX(ha) ||
	    IS_QLA28XX(ha))
		वापस ptr;

	mq = ptr;
	*last_chain = &mq->type;
	mq->type = htonl(DUMP_CHAIN_MQ);
	mq->chain_size = htonl(माप(काष्ठा qla2xxx_mq_chain));

	que_cnt = ha->max_req_queues > ha->max_rsp_queues ?
		ha->max_req_queues : ha->max_rsp_queues;
	mq->count = htonl(que_cnt);
	क्रम (cnt = 0; cnt < que_cnt; cnt++) अणु
		reg = ISP_QUE_REG(ha, cnt);
		que_idx = cnt * 4;
		mq->qregs[que_idx] =
		    htonl(rd_reg_dword(&reg->isp25mq.req_q_in));
		mq->qregs[que_idx+1] =
		    htonl(rd_reg_dword(&reg->isp25mq.req_q_out));
		mq->qregs[que_idx+2] =
		    htonl(rd_reg_dword(&reg->isp25mq.rsp_q_in));
		mq->qregs[que_idx+3] =
		    htonl(rd_reg_dword(&reg->isp25mq.rsp_q_out));
	पूर्ण

	वापस ptr + माप(काष्ठा qla2xxx_mq_chain);
पूर्ण

व्योम
qla2xxx_dump_post_process(scsi_qla_host_t *vha, पूर्णांक rval)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;

	अगर (rval != QLA_SUCCESS) अणु
		ql_log(ql_log_warn, vha, 0xd000,
		    "Failed to dump firmware (%x), dump status flags (0x%lx).\n",
		    rval, ha->fw_dump_cap_flags);
		ha->fw_dumped = false;
	पूर्ण अन्यथा अणु
		ql_log(ql_log_info, vha, 0xd001,
		    "Firmware dump saved to temp buffer (%ld/%p), dump status flags (0x%lx).\n",
		    vha->host_no, ha->fw_dump, ha->fw_dump_cap_flags);
		ha->fw_dumped = true;
		qla2x00_post_uevent_work(vha, QLA_UEVENT_CODE_FW_DUMP);
	पूर्ण
पूर्ण

व्योम qla2xxx_dump_fw(scsi_qla_host_t *vha)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&vha->hw->hardware_lock, flags);
	vha->hw->isp_ops->fw_dump(vha);
	spin_unlock_irqrestore(&vha->hw->hardware_lock, flags);
पूर्ण

/**
 * qla2300_fw_dump() - Dumps binary data from the 2300 firmware.
 * @vha: HA context
 */
व्योम
qla2300_fw_dump(scsi_qla_host_t *vha)
अणु
	पूर्णांक		rval;
	uपूर्णांक32_t	cnt;
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा device_reg_2xxx __iomem *reg = &ha->iobase->isp;
	__le16 __iomem *dmp_reg;
	काष्ठा qla2300_fw_dump	*fw;
	व्योम		*nxt;
	काष्ठा scsi_qla_host *base_vha = pci_get_drvdata(ha->pdev);

	lockdep_निश्चित_held(&ha->hardware_lock);

	अगर (!ha->fw_dump) अणु
		ql_log(ql_log_warn, vha, 0xd002,
		    "No buffer available for dump.\n");
		वापस;
	पूर्ण

	अगर (ha->fw_dumped) अणु
		ql_log(ql_log_warn, vha, 0xd003,
		    "Firmware has been previously dumped (%p) "
		    "-- ignoring request.\n",
		    ha->fw_dump);
		वापस;
	पूर्ण
	fw = &ha->fw_dump->isp.isp23;
	qla2xxx_prep_dump(ha, ha->fw_dump);

	rval = QLA_SUCCESS;
	fw->hccr = htons(rd_reg_word(&reg->hccr));

	/* Pause RISC. */
	wrt_reg_word(&reg->hccr, HCCR_PAUSE_RISC);
	अगर (IS_QLA2300(ha)) अणु
		क्रम (cnt = 30000;
		    (rd_reg_word(&reg->hccr) & HCCR_RISC_PAUSE) == 0 &&
			rval == QLA_SUCCESS; cnt--) अणु
			अगर (cnt)
				udelay(100);
			अन्यथा
				rval = QLA_FUNCTION_TIMEOUT;
		पूर्ण
	पूर्ण अन्यथा अणु
		rd_reg_word(&reg->hccr);		/* PCI Posting. */
		udelay(10);
	पूर्ण

	अगर (rval == QLA_SUCCESS) अणु
		dmp_reg = &reg->flash_address;
		क्रम (cnt = 0; cnt < ARRAY_SIZE(fw->pbiu_reg); cnt++, dmp_reg++)
			fw->pbiu_reg[cnt] = htons(rd_reg_word(dmp_reg));

		dmp_reg = &reg->u.isp2300.req_q_in;
		क्रम (cnt = 0; cnt < ARRAY_SIZE(fw->risc_host_reg);
		    cnt++, dmp_reg++)
			fw->risc_host_reg[cnt] = htons(rd_reg_word(dmp_reg));

		dmp_reg = &reg->u.isp2300.mailbox0;
		क्रम (cnt = 0; cnt < ARRAY_SIZE(fw->mailbox_reg);
		    cnt++, dmp_reg++)
			fw->mailbox_reg[cnt] = htons(rd_reg_word(dmp_reg));

		wrt_reg_word(&reg->ctrl_status, 0x40);
		qla2xxx_पढ़ो_winकरोw(reg, 32, fw->resp_dma_reg);

		wrt_reg_word(&reg->ctrl_status, 0x50);
		qla2xxx_पढ़ो_winकरोw(reg, 48, fw->dma_reg);

		wrt_reg_word(&reg->ctrl_status, 0x00);
		dmp_reg = &reg->risc_hw;
		क्रम (cnt = 0; cnt < ARRAY_SIZE(fw->risc_hdw_reg);
		    cnt++, dmp_reg++)
			fw->risc_hdw_reg[cnt] = htons(rd_reg_word(dmp_reg));

		wrt_reg_word(&reg->pcr, 0x2000);
		qla2xxx_पढ़ो_winकरोw(reg, 16, fw->risc_gp0_reg);

		wrt_reg_word(&reg->pcr, 0x2200);
		qla2xxx_पढ़ो_winकरोw(reg, 16, fw->risc_gp1_reg);

		wrt_reg_word(&reg->pcr, 0x2400);
		qla2xxx_पढ़ो_winकरोw(reg, 16, fw->risc_gp2_reg);

		wrt_reg_word(&reg->pcr, 0x2600);
		qla2xxx_पढ़ो_winकरोw(reg, 16, fw->risc_gp3_reg);

		wrt_reg_word(&reg->pcr, 0x2800);
		qla2xxx_पढ़ो_winकरोw(reg, 16, fw->risc_gp4_reg);

		wrt_reg_word(&reg->pcr, 0x2A00);
		qla2xxx_पढ़ो_winकरोw(reg, 16, fw->risc_gp5_reg);

		wrt_reg_word(&reg->pcr, 0x2C00);
		qla2xxx_पढ़ो_winकरोw(reg, 16, fw->risc_gp6_reg);

		wrt_reg_word(&reg->pcr, 0x2E00);
		qla2xxx_पढ़ो_winकरोw(reg, 16, fw->risc_gp7_reg);

		wrt_reg_word(&reg->ctrl_status, 0x10);
		qla2xxx_पढ़ो_winकरोw(reg, 64, fw->frame_buf_hdw_reg);

		wrt_reg_word(&reg->ctrl_status, 0x20);
		qla2xxx_पढ़ो_winकरोw(reg, 64, fw->fpm_b0_reg);

		wrt_reg_word(&reg->ctrl_status, 0x30);
		qla2xxx_पढ़ो_winकरोw(reg, 64, fw->fpm_b1_reg);

		/* Reset RISC. */
		wrt_reg_word(&reg->ctrl_status, CSR_ISP_SOFT_RESET);
		क्रम (cnt = 0; cnt < 30000; cnt++) अणु
			अगर ((rd_reg_word(&reg->ctrl_status) &
			    CSR_ISP_SOFT_RESET) == 0)
				अवरोध;

			udelay(10);
		पूर्ण
	पूर्ण

	अगर (!IS_QLA2300(ha)) अणु
		क्रम (cnt = 30000; RD_MAILBOX_REG(ha, reg, 0) != 0 &&
		    rval == QLA_SUCCESS; cnt--) अणु
			अगर (cnt)
				udelay(100);
			अन्यथा
				rval = QLA_FUNCTION_TIMEOUT;
		पूर्ण
	पूर्ण

	/* Get RISC SRAM. */
	अगर (rval == QLA_SUCCESS)
		rval = qla2xxx_dump_ram(ha, 0x800, fw->risc_ram,
					ARRAY_SIZE(fw->risc_ram), &nxt);

	/* Get stack SRAM. */
	अगर (rval == QLA_SUCCESS)
		rval = qla2xxx_dump_ram(ha, 0x10000, fw->stack_ram,
					ARRAY_SIZE(fw->stack_ram), &nxt);

	/* Get data SRAM. */
	अगर (rval == QLA_SUCCESS)
		rval = qla2xxx_dump_ram(ha, 0x11000, fw->data_ram,
		    ha->fw_memory_size - 0x11000 + 1, &nxt);

	अगर (rval == QLA_SUCCESS)
		qla2xxx_copy_queues(ha, nxt);

	qla2xxx_dump_post_process(base_vha, rval);
पूर्ण

/**
 * qla2100_fw_dump() - Dumps binary data from the 2100/2200 firmware.
 * @vha: HA context
 */
व्योम
qla2100_fw_dump(scsi_qla_host_t *vha)
अणु
	पूर्णांक		rval;
	uपूर्णांक32_t	cnt, समयr;
	uपूर्णांक16_t	risc_address = 0;
	uपूर्णांक16_t	mb0 = 0, mb2 = 0;
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा device_reg_2xxx __iomem *reg = &ha->iobase->isp;
	__le16 __iomem *dmp_reg;
	काष्ठा qla2100_fw_dump	*fw;
	काष्ठा scsi_qla_host *base_vha = pci_get_drvdata(ha->pdev);

	lockdep_निश्चित_held(&ha->hardware_lock);

	अगर (!ha->fw_dump) अणु
		ql_log(ql_log_warn, vha, 0xd004,
		    "No buffer available for dump.\n");
		वापस;
	पूर्ण

	अगर (ha->fw_dumped) अणु
		ql_log(ql_log_warn, vha, 0xd005,
		    "Firmware has been previously dumped (%p) "
		    "-- ignoring request.\n",
		    ha->fw_dump);
		वापस;
	पूर्ण
	fw = &ha->fw_dump->isp.isp21;
	qla2xxx_prep_dump(ha, ha->fw_dump);

	rval = QLA_SUCCESS;
	fw->hccr = htons(rd_reg_word(&reg->hccr));

	/* Pause RISC. */
	wrt_reg_word(&reg->hccr, HCCR_PAUSE_RISC);
	क्रम (cnt = 30000; (rd_reg_word(&reg->hccr) & HCCR_RISC_PAUSE) == 0 &&
	    rval == QLA_SUCCESS; cnt--) अणु
		अगर (cnt)
			udelay(100);
		अन्यथा
			rval = QLA_FUNCTION_TIMEOUT;
	पूर्ण
	अगर (rval == QLA_SUCCESS) अणु
		dmp_reg = &reg->flash_address;
		क्रम (cnt = 0; cnt < ARRAY_SIZE(fw->pbiu_reg); cnt++, dmp_reg++)
			fw->pbiu_reg[cnt] = htons(rd_reg_word(dmp_reg));

		dmp_reg = &reg->u.isp2100.mailbox0;
		क्रम (cnt = 0; cnt < ha->mbx_count; cnt++, dmp_reg++) अणु
			अगर (cnt == 8)
				dmp_reg = &reg->u_end.isp2200.mailbox8;

			fw->mailbox_reg[cnt] = htons(rd_reg_word(dmp_reg));
		पूर्ण

		dmp_reg = &reg->u.isp2100.unused_2[0];
		क्रम (cnt = 0; cnt < ARRAY_SIZE(fw->dma_reg); cnt++, dmp_reg++)
			fw->dma_reg[cnt] = htons(rd_reg_word(dmp_reg));

		wrt_reg_word(&reg->ctrl_status, 0x00);
		dmp_reg = &reg->risc_hw;
		क्रम (cnt = 0; cnt < ARRAY_SIZE(fw->risc_hdw_reg); cnt++, dmp_reg++)
			fw->risc_hdw_reg[cnt] = htons(rd_reg_word(dmp_reg));

		wrt_reg_word(&reg->pcr, 0x2000);
		qla2xxx_पढ़ो_winकरोw(reg, 16, fw->risc_gp0_reg);

		wrt_reg_word(&reg->pcr, 0x2100);
		qla2xxx_पढ़ो_winकरोw(reg, 16, fw->risc_gp1_reg);

		wrt_reg_word(&reg->pcr, 0x2200);
		qla2xxx_पढ़ो_winकरोw(reg, 16, fw->risc_gp2_reg);

		wrt_reg_word(&reg->pcr, 0x2300);
		qla2xxx_पढ़ो_winकरोw(reg, 16, fw->risc_gp3_reg);

		wrt_reg_word(&reg->pcr, 0x2400);
		qla2xxx_पढ़ो_winकरोw(reg, 16, fw->risc_gp4_reg);

		wrt_reg_word(&reg->pcr, 0x2500);
		qla2xxx_पढ़ो_winकरोw(reg, 16, fw->risc_gp5_reg);

		wrt_reg_word(&reg->pcr, 0x2600);
		qla2xxx_पढ़ो_winकरोw(reg, 16, fw->risc_gp6_reg);

		wrt_reg_word(&reg->pcr, 0x2700);
		qla2xxx_पढ़ो_winकरोw(reg, 16, fw->risc_gp7_reg);

		wrt_reg_word(&reg->ctrl_status, 0x10);
		qla2xxx_पढ़ो_winकरोw(reg, 16, fw->frame_buf_hdw_reg);

		wrt_reg_word(&reg->ctrl_status, 0x20);
		qla2xxx_पढ़ो_winकरोw(reg, 64, fw->fpm_b0_reg);

		wrt_reg_word(&reg->ctrl_status, 0x30);
		qla2xxx_पढ़ो_winकरोw(reg, 64, fw->fpm_b1_reg);

		/* Reset the ISP. */
		wrt_reg_word(&reg->ctrl_status, CSR_ISP_SOFT_RESET);
	पूर्ण

	क्रम (cnt = 30000; RD_MAILBOX_REG(ha, reg, 0) != 0 &&
	    rval == QLA_SUCCESS; cnt--) अणु
		अगर (cnt)
			udelay(100);
		अन्यथा
			rval = QLA_FUNCTION_TIMEOUT;
	पूर्ण

	/* Pause RISC. */
	अगर (rval == QLA_SUCCESS && (IS_QLA2200(ha) || (IS_QLA2100(ha) &&
	    (rd_reg_word(&reg->mctr) & (BIT_1 | BIT_0)) != 0))) अणु

		wrt_reg_word(&reg->hccr, HCCR_PAUSE_RISC);
		क्रम (cnt = 30000;
		    (rd_reg_word(&reg->hccr) & HCCR_RISC_PAUSE) == 0 &&
		    rval == QLA_SUCCESS; cnt--) अणु
			अगर (cnt)
				udelay(100);
			अन्यथा
				rval = QLA_FUNCTION_TIMEOUT;
		पूर्ण
		अगर (rval == QLA_SUCCESS) अणु
			/* Set memory configuration and timing. */
			अगर (IS_QLA2100(ha))
				wrt_reg_word(&reg->mctr, 0xf1);
			अन्यथा
				wrt_reg_word(&reg->mctr, 0xf2);
			rd_reg_word(&reg->mctr);	/* PCI Posting. */

			/* Release RISC. */
			wrt_reg_word(&reg->hccr, HCCR_RELEASE_RISC);
		पूर्ण
	पूर्ण

	अगर (rval == QLA_SUCCESS) अणु
		/* Get RISC SRAM. */
		risc_address = 0x1000;
 		WRT_MAILBOX_REG(ha, reg, 0, MBC_READ_RAM_WORD);
		clear_bit(MBX_INTERRUPT, &ha->mbx_cmd_flags);
	पूर्ण
	क्रम (cnt = 0; cnt < ARRAY_SIZE(fw->risc_ram) && rval == QLA_SUCCESS;
	    cnt++, risc_address++) अणु
 		WRT_MAILBOX_REG(ha, reg, 1, risc_address);
		wrt_reg_word(&reg->hccr, HCCR_SET_HOST_INT);

		क्रम (समयr = 6000000; समयr != 0; समयr--) अणु
			/* Check क्रम pending पूर्णांकerrupts. */
			अगर (rd_reg_word(&reg->istatus) & ISR_RISC_INT) अणु
				अगर (rd_reg_word(&reg->semaphore) & BIT_0) अणु
					set_bit(MBX_INTERRUPT,
					    &ha->mbx_cmd_flags);

					mb0 = RD_MAILBOX_REG(ha, reg, 0);
					mb2 = RD_MAILBOX_REG(ha, reg, 2);

					wrt_reg_word(&reg->semaphore, 0);
					wrt_reg_word(&reg->hccr,
					    HCCR_CLR_RISC_INT);
					rd_reg_word(&reg->hccr);
					अवरोध;
				पूर्ण
				wrt_reg_word(&reg->hccr, HCCR_CLR_RISC_INT);
				rd_reg_word(&reg->hccr);
			पूर्ण
			udelay(5);
		पूर्ण

		अगर (test_and_clear_bit(MBX_INTERRUPT, &ha->mbx_cmd_flags)) अणु
			rval = mb0 & MBS_MASK;
			fw->risc_ram[cnt] = htons(mb2);
		पूर्ण अन्यथा अणु
			rval = QLA_FUNCTION_FAILED;
		पूर्ण
	पूर्ण

	अगर (rval == QLA_SUCCESS)
		qla2xxx_copy_queues(ha, &fw->queue_dump[0]);

	qla2xxx_dump_post_process(base_vha, rval);
पूर्ण

व्योम
qla24xx_fw_dump(scsi_qla_host_t *vha)
अणु
	पूर्णांक		rval;
	uपूर्णांक32_t	cnt;
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा device_reg_24xx __iomem *reg = &ha->iobase->isp24;
	__le32 __iomem *dmp_reg;
	__be32		*iter_reg;
	__le16 __iomem *mbx_reg;
	काष्ठा qla24xx_fw_dump *fw;
	व्योम		*nxt;
	व्योम		*nxt_chain;
	__be32		*last_chain = शून्य;
	काष्ठा scsi_qla_host *base_vha = pci_get_drvdata(ha->pdev);

	lockdep_निश्चित_held(&ha->hardware_lock);

	अगर (IS_P3P_TYPE(ha))
		वापस;

	ha->fw_dump_cap_flags = 0;

	अगर (!ha->fw_dump) अणु
		ql_log(ql_log_warn, vha, 0xd006,
		    "No buffer available for dump.\n");
		वापस;
	पूर्ण

	अगर (ha->fw_dumped) अणु
		ql_log(ql_log_warn, vha, 0xd007,
		    "Firmware has been previously dumped (%p) "
		    "-- ignoring request.\n",
		    ha->fw_dump);
		वापस;
	पूर्ण
	QLA_FW_STOPPED(ha);
	fw = &ha->fw_dump->isp.isp24;
	qla2xxx_prep_dump(ha, ha->fw_dump);

	fw->host_status = htonl(rd_reg_dword(&reg->host_status));

	/*
	 * Pause RISC. No need to track समयout, as resetting the chip
	 * is the right approach inहाल of छोड़ो समयout
	 */
	qla24xx_छोड़ो_risc(reg, ha);

	/* Host पूर्णांकerface रेजिस्टरs. */
	dmp_reg = &reg->flash_addr;
	क्रम (cnt = 0; cnt < ARRAY_SIZE(fw->host_reg); cnt++, dmp_reg++)
		fw->host_reg[cnt] = htonl(rd_reg_dword(dmp_reg));

	/* Disable पूर्णांकerrupts. */
	wrt_reg_dword(&reg->ictrl, 0);
	rd_reg_dword(&reg->ictrl);

	/* Shaकरोw रेजिस्टरs. */
	wrt_reg_dword(&reg->iobase_addr, 0x0F70);
	rd_reg_dword(&reg->iobase_addr);
	wrt_reg_dword(&reg->iobase_select, 0xB0000000);
	fw->shaकरोw_reg[0] = htonl(rd_reg_dword(&reg->iobase_sdata));

	wrt_reg_dword(&reg->iobase_select, 0xB0100000);
	fw->shaकरोw_reg[1] = htonl(rd_reg_dword(&reg->iobase_sdata));

	wrt_reg_dword(&reg->iobase_select, 0xB0200000);
	fw->shaकरोw_reg[2] = htonl(rd_reg_dword(&reg->iobase_sdata));

	wrt_reg_dword(&reg->iobase_select, 0xB0300000);
	fw->shaकरोw_reg[3] = htonl(rd_reg_dword(&reg->iobase_sdata));

	wrt_reg_dword(&reg->iobase_select, 0xB0400000);
	fw->shaकरोw_reg[4] = htonl(rd_reg_dword(&reg->iobase_sdata));

	wrt_reg_dword(&reg->iobase_select, 0xB0500000);
	fw->shaकरोw_reg[5] = htonl(rd_reg_dword(&reg->iobase_sdata));

	wrt_reg_dword(&reg->iobase_select, 0xB0600000);
	fw->shaकरोw_reg[6] = htonl(rd_reg_dword(&reg->iobase_sdata));

	/* Mailbox रेजिस्टरs. */
	mbx_reg = &reg->mailbox0;
	क्रम (cnt = 0; cnt < ARRAY_SIZE(fw->mailbox_reg); cnt++, mbx_reg++)
		fw->mailbox_reg[cnt] = htons(rd_reg_word(mbx_reg));

	/* Transfer sequence रेजिस्टरs. */
	iter_reg = fw->xseq_gp_reg;
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0xBF00, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0xBF10, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0xBF20, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0xBF30, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0xBF40, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0xBF50, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0xBF60, 16, iter_reg);
	qla24xx_पढ़ो_winकरोw(reg, 0xBF70, 16, iter_reg);

	qla24xx_पढ़ो_winकरोw(reg, 0xBFE0, 16, fw->xseq_0_reg);
	qla24xx_पढ़ो_winकरोw(reg, 0xBFF0, 16, fw->xseq_1_reg);

	/* Receive sequence रेजिस्टरs. */
	iter_reg = fw->rseq_gp_reg;
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0xFF00, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0xFF10, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0xFF20, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0xFF30, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0xFF40, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0xFF50, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0xFF60, 16, iter_reg);
	qla24xx_पढ़ो_winकरोw(reg, 0xFF70, 16, iter_reg);

	qla24xx_पढ़ो_winकरोw(reg, 0xFFD0, 16, fw->rseq_0_reg);
	qla24xx_पढ़ो_winकरोw(reg, 0xFFE0, 16, fw->rseq_1_reg);
	qla24xx_पढ़ो_winकरोw(reg, 0xFFF0, 16, fw->rseq_2_reg);

	/* Command DMA रेजिस्टरs. */
	qla24xx_पढ़ो_winकरोw(reg, 0x7100, 16, fw->cmd_dma_reg);

	/* Queues. */
	iter_reg = fw->req0_dma_reg;
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x7200, 8, iter_reg);
	dmp_reg = &reg->iobase_q;
	क्रम (cnt = 0; cnt < 7; cnt++, dmp_reg++)
		*iter_reg++ = htonl(rd_reg_dword(dmp_reg));

	iter_reg = fw->resp0_dma_reg;
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x7300, 8, iter_reg);
	dmp_reg = &reg->iobase_q;
	क्रम (cnt = 0; cnt < 7; cnt++, dmp_reg++)
		*iter_reg++ = htonl(rd_reg_dword(dmp_reg));

	iter_reg = fw->req1_dma_reg;
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x7400, 8, iter_reg);
	dmp_reg = &reg->iobase_q;
	क्रम (cnt = 0; cnt < 7; cnt++, dmp_reg++)
		*iter_reg++ = htonl(rd_reg_dword(dmp_reg));

	/* Transmit DMA रेजिस्टरs. */
	iter_reg = fw->xmt0_dma_reg;
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x7600, 16, iter_reg);
	qla24xx_पढ़ो_winकरोw(reg, 0x7610, 16, iter_reg);

	iter_reg = fw->xmt1_dma_reg;
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x7620, 16, iter_reg);
	qla24xx_पढ़ो_winकरोw(reg, 0x7630, 16, iter_reg);

	iter_reg = fw->xmt2_dma_reg;
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x7640, 16, iter_reg);
	qla24xx_पढ़ो_winकरोw(reg, 0x7650, 16, iter_reg);

	iter_reg = fw->xmt3_dma_reg;
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x7660, 16, iter_reg);
	qla24xx_पढ़ो_winकरोw(reg, 0x7670, 16, iter_reg);

	iter_reg = fw->xmt4_dma_reg;
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x7680, 16, iter_reg);
	qla24xx_पढ़ो_winकरोw(reg, 0x7690, 16, iter_reg);

	qla24xx_पढ़ो_winकरोw(reg, 0x76A0, 16, fw->xmt_data_dma_reg);

	/* Receive DMA रेजिस्टरs. */
	iter_reg = fw->rcvt0_data_dma_reg;
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x7700, 16, iter_reg);
	qla24xx_पढ़ो_winकरोw(reg, 0x7710, 16, iter_reg);

	iter_reg = fw->rcvt1_data_dma_reg;
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x7720, 16, iter_reg);
	qla24xx_पढ़ो_winकरोw(reg, 0x7730, 16, iter_reg);

	/* RISC रेजिस्टरs. */
	iter_reg = fw->risc_gp_reg;
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x0F00, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x0F10, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x0F20, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x0F30, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x0F40, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x0F50, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x0F60, 16, iter_reg);
	qla24xx_पढ़ो_winकरोw(reg, 0x0F70, 16, iter_reg);

	/* Local memory controller रेजिस्टरs. */
	iter_reg = fw->lmc_reg;
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x3000, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x3010, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x3020, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x3030, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x3040, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x3050, 16, iter_reg);
	qla24xx_पढ़ो_winकरोw(reg, 0x3060, 16, iter_reg);

	/* Fibre Protocol Module रेजिस्टरs. */
	iter_reg = fw->fpm_hdw_reg;
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x4000, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x4010, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x4020, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x4030, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x4040, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x4050, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x4060, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x4070, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x4080, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x4090, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x40A0, 16, iter_reg);
	qla24xx_पढ़ो_winकरोw(reg, 0x40B0, 16, iter_reg);

	/* Frame Buffer रेजिस्टरs. */
	iter_reg = fw->fb_hdw_reg;
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x6000, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x6010, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x6020, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x6030, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x6040, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x6100, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x6130, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x6150, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x6170, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x6190, 16, iter_reg);
	qla24xx_पढ़ो_winकरोw(reg, 0x61B0, 16, iter_reg);

	rval = qla24xx_soft_reset(ha);
	अगर (rval != QLA_SUCCESS)
		जाओ qla24xx_fw_dump_failed_0;

	rval = qla24xx_dump_memory(ha, fw->code_ram, माप(fw->code_ram),
	    &nxt);
	अगर (rval != QLA_SUCCESS)
		जाओ qla24xx_fw_dump_failed_0;

	nxt = qla2xxx_copy_queues(ha, nxt);

	qla24xx_copy_eft(ha, nxt);

	nxt_chain = (व्योम *)ha->fw_dump + ha->chain_offset;
	nxt_chain = qla2xxx_copy_atioqueues(ha, nxt_chain, &last_chain);
	अगर (last_chain) अणु
		ha->fw_dump->version |= htonl(DUMP_CHAIN_VARIANT);
		*last_chain |= htonl(DUMP_CHAIN_LAST);
	पूर्ण

	/* Adjust valid length. */
	ha->fw_dump_len = (nxt_chain - (व्योम *)ha->fw_dump);

qla24xx_fw_dump_failed_0:
	qla2xxx_dump_post_process(base_vha, rval);
पूर्ण

व्योम
qla25xx_fw_dump(scsi_qla_host_t *vha)
अणु
	पूर्णांक		rval;
	uपूर्णांक32_t	cnt;
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा device_reg_24xx __iomem *reg = &ha->iobase->isp24;
	__le32 __iomem *dmp_reg;
	__be32		*iter_reg;
	__le16 __iomem *mbx_reg;
	काष्ठा qla25xx_fw_dump *fw;
	व्योम		*nxt, *nxt_chain;
	__be32		*last_chain = शून्य;
	काष्ठा scsi_qla_host *base_vha = pci_get_drvdata(ha->pdev);

	lockdep_निश्चित_held(&ha->hardware_lock);

	ha->fw_dump_cap_flags = 0;

	अगर (!ha->fw_dump) अणु
		ql_log(ql_log_warn, vha, 0xd008,
		    "No buffer available for dump.\n");
		वापस;
	पूर्ण

	अगर (ha->fw_dumped) अणु
		ql_log(ql_log_warn, vha, 0xd009,
		    "Firmware has been previously dumped (%p) "
		    "-- ignoring request.\n",
		    ha->fw_dump);
		वापस;
	पूर्ण
	QLA_FW_STOPPED(ha);
	fw = &ha->fw_dump->isp.isp25;
	qla2xxx_prep_dump(ha, ha->fw_dump);
	ha->fw_dump->version = htonl(2);

	fw->host_status = htonl(rd_reg_dword(&reg->host_status));

	/*
	 * Pause RISC. No need to track समयout, as resetting the chip
	 * is the right approach inहाल of छोड़ो समयout
	 */
	qla24xx_छोड़ो_risc(reg, ha);

	/* Host/Risc रेजिस्टरs. */
	iter_reg = fw->host_risc_reg;
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x7000, 16, iter_reg);
	qla24xx_पढ़ो_winकरोw(reg, 0x7010, 16, iter_reg);

	/* PCIe रेजिस्टरs. */
	wrt_reg_dword(&reg->iobase_addr, 0x7C00);
	rd_reg_dword(&reg->iobase_addr);
	wrt_reg_dword(&reg->iobase_winकरोw, 0x01);
	dmp_reg = &reg->iobase_c4;
	fw->pcie_regs[0] = htonl(rd_reg_dword(dmp_reg));
	dmp_reg++;
	fw->pcie_regs[1] = htonl(rd_reg_dword(dmp_reg));
	dmp_reg++;
	fw->pcie_regs[2] = htonl(rd_reg_dword(dmp_reg));
	fw->pcie_regs[3] = htonl(rd_reg_dword(&reg->iobase_winकरोw));

	wrt_reg_dword(&reg->iobase_winकरोw, 0x00);
	rd_reg_dword(&reg->iobase_winकरोw);

	/* Host पूर्णांकerface रेजिस्टरs. */
	dmp_reg = &reg->flash_addr;
	क्रम (cnt = 0; cnt < ARRAY_SIZE(fw->host_reg); cnt++, dmp_reg++)
		fw->host_reg[cnt] = htonl(rd_reg_dword(dmp_reg));

	/* Disable पूर्णांकerrupts. */
	wrt_reg_dword(&reg->ictrl, 0);
	rd_reg_dword(&reg->ictrl);

	/* Shaकरोw रेजिस्टरs. */
	wrt_reg_dword(&reg->iobase_addr, 0x0F70);
	rd_reg_dword(&reg->iobase_addr);
	wrt_reg_dword(&reg->iobase_select, 0xB0000000);
	fw->shaकरोw_reg[0] = htonl(rd_reg_dword(&reg->iobase_sdata));

	wrt_reg_dword(&reg->iobase_select, 0xB0100000);
	fw->shaकरोw_reg[1] = htonl(rd_reg_dword(&reg->iobase_sdata));

	wrt_reg_dword(&reg->iobase_select, 0xB0200000);
	fw->shaकरोw_reg[2] = htonl(rd_reg_dword(&reg->iobase_sdata));

	wrt_reg_dword(&reg->iobase_select, 0xB0300000);
	fw->shaकरोw_reg[3] = htonl(rd_reg_dword(&reg->iobase_sdata));

	wrt_reg_dword(&reg->iobase_select, 0xB0400000);
	fw->shaकरोw_reg[4] = htonl(rd_reg_dword(&reg->iobase_sdata));

	wrt_reg_dword(&reg->iobase_select, 0xB0500000);
	fw->shaकरोw_reg[5] = htonl(rd_reg_dword(&reg->iobase_sdata));

	wrt_reg_dword(&reg->iobase_select, 0xB0600000);
	fw->shaकरोw_reg[6] = htonl(rd_reg_dword(&reg->iobase_sdata));

	wrt_reg_dword(&reg->iobase_select, 0xB0700000);
	fw->shaकरोw_reg[7] = htonl(rd_reg_dword(&reg->iobase_sdata));

	wrt_reg_dword(&reg->iobase_select, 0xB0800000);
	fw->shaकरोw_reg[8] = htonl(rd_reg_dword(&reg->iobase_sdata));

	wrt_reg_dword(&reg->iobase_select, 0xB0900000);
	fw->shaकरोw_reg[9] = htonl(rd_reg_dword(&reg->iobase_sdata));

	wrt_reg_dword(&reg->iobase_select, 0xB0A00000);
	fw->shaकरोw_reg[10] = htonl(rd_reg_dword(&reg->iobase_sdata));

	/* RISC I/O रेजिस्टर. */
	wrt_reg_dword(&reg->iobase_addr, 0x0010);
	fw->risc_io_reg = htonl(rd_reg_dword(&reg->iobase_winकरोw));

	/* Mailbox रेजिस्टरs. */
	mbx_reg = &reg->mailbox0;
	क्रम (cnt = 0; cnt < ARRAY_SIZE(fw->mailbox_reg); cnt++, mbx_reg++)
		fw->mailbox_reg[cnt] = htons(rd_reg_word(mbx_reg));

	/* Transfer sequence रेजिस्टरs. */
	iter_reg = fw->xseq_gp_reg;
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0xBF00, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0xBF10, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0xBF20, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0xBF30, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0xBF40, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0xBF50, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0xBF60, 16, iter_reg);
	qla24xx_पढ़ो_winकरोw(reg, 0xBF70, 16, iter_reg);

	iter_reg = fw->xseq_0_reg;
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0xBFC0, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0xBFD0, 16, iter_reg);
	qla24xx_पढ़ो_winकरोw(reg, 0xBFE0, 16, iter_reg);

	qla24xx_पढ़ो_winकरोw(reg, 0xBFF0, 16, fw->xseq_1_reg);

	/* Receive sequence रेजिस्टरs. */
	iter_reg = fw->rseq_gp_reg;
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0xFF00, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0xFF10, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0xFF20, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0xFF30, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0xFF40, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0xFF50, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0xFF60, 16, iter_reg);
	qla24xx_पढ़ो_winकरोw(reg, 0xFF70, 16, iter_reg);

	iter_reg = fw->rseq_0_reg;
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0xFFC0, 16, iter_reg);
	qla24xx_पढ़ो_winकरोw(reg, 0xFFD0, 16, iter_reg);

	qla24xx_पढ़ो_winकरोw(reg, 0xFFE0, 16, fw->rseq_1_reg);
	qla24xx_पढ़ो_winकरोw(reg, 0xFFF0, 16, fw->rseq_2_reg);

	/* Auxiliary sequence रेजिस्टरs. */
	iter_reg = fw->aseq_gp_reg;
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0xB000, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0xB010, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0xB020, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0xB030, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0xB040, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0xB050, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0xB060, 16, iter_reg);
	qla24xx_पढ़ो_winकरोw(reg, 0xB070, 16, iter_reg);

	iter_reg = fw->aseq_0_reg;
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0xB0C0, 16, iter_reg);
	qla24xx_पढ़ो_winकरोw(reg, 0xB0D0, 16, iter_reg);

	qla24xx_पढ़ो_winकरोw(reg, 0xB0E0, 16, fw->aseq_1_reg);
	qla24xx_पढ़ो_winकरोw(reg, 0xB0F0, 16, fw->aseq_2_reg);

	/* Command DMA रेजिस्टरs. */
	qla24xx_पढ़ो_winकरोw(reg, 0x7100, 16, fw->cmd_dma_reg);

	/* Queues. */
	iter_reg = fw->req0_dma_reg;
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x7200, 8, iter_reg);
	dmp_reg = &reg->iobase_q;
	क्रम (cnt = 0; cnt < 7; cnt++, dmp_reg++)
		*iter_reg++ = htonl(rd_reg_dword(dmp_reg));

	iter_reg = fw->resp0_dma_reg;
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x7300, 8, iter_reg);
	dmp_reg = &reg->iobase_q;
	क्रम (cnt = 0; cnt < 7; cnt++, dmp_reg++)
		*iter_reg++ = htonl(rd_reg_dword(dmp_reg));

	iter_reg = fw->req1_dma_reg;
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x7400, 8, iter_reg);
	dmp_reg = &reg->iobase_q;
	क्रम (cnt = 0; cnt < 7; cnt++, dmp_reg++)
		*iter_reg++ = htonl(rd_reg_dword(dmp_reg));

	/* Transmit DMA रेजिस्टरs. */
	iter_reg = fw->xmt0_dma_reg;
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x7600, 16, iter_reg);
	qla24xx_पढ़ो_winकरोw(reg, 0x7610, 16, iter_reg);

	iter_reg = fw->xmt1_dma_reg;
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x7620, 16, iter_reg);
	qla24xx_पढ़ो_winकरोw(reg, 0x7630, 16, iter_reg);

	iter_reg = fw->xmt2_dma_reg;
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x7640, 16, iter_reg);
	qla24xx_पढ़ो_winकरोw(reg, 0x7650, 16, iter_reg);

	iter_reg = fw->xmt3_dma_reg;
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x7660, 16, iter_reg);
	qla24xx_पढ़ो_winकरोw(reg, 0x7670, 16, iter_reg);

	iter_reg = fw->xmt4_dma_reg;
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x7680, 16, iter_reg);
	qla24xx_पढ़ो_winकरोw(reg, 0x7690, 16, iter_reg);

	qla24xx_पढ़ो_winकरोw(reg, 0x76A0, 16, fw->xmt_data_dma_reg);

	/* Receive DMA रेजिस्टरs. */
	iter_reg = fw->rcvt0_data_dma_reg;
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x7700, 16, iter_reg);
	qla24xx_पढ़ो_winकरोw(reg, 0x7710, 16, iter_reg);

	iter_reg = fw->rcvt1_data_dma_reg;
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x7720, 16, iter_reg);
	qla24xx_पढ़ो_winकरोw(reg, 0x7730, 16, iter_reg);

	/* RISC रेजिस्टरs. */
	iter_reg = fw->risc_gp_reg;
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x0F00, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x0F10, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x0F20, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x0F30, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x0F40, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x0F50, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x0F60, 16, iter_reg);
	qla24xx_पढ़ो_winकरोw(reg, 0x0F70, 16, iter_reg);

	/* Local memory controller रेजिस्टरs. */
	iter_reg = fw->lmc_reg;
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x3000, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x3010, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x3020, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x3030, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x3040, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x3050, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x3060, 16, iter_reg);
	qla24xx_पढ़ो_winकरोw(reg, 0x3070, 16, iter_reg);

	/* Fibre Protocol Module रेजिस्टरs. */
	iter_reg = fw->fpm_hdw_reg;
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x4000, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x4010, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x4020, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x4030, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x4040, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x4050, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x4060, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x4070, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x4080, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x4090, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x40A0, 16, iter_reg);
	qla24xx_पढ़ो_winकरोw(reg, 0x40B0, 16, iter_reg);

	/* Frame Buffer रेजिस्टरs. */
	iter_reg = fw->fb_hdw_reg;
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x6000, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x6010, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x6020, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x6030, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x6040, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x6100, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x6130, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x6150, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x6170, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x6190, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x61B0, 16, iter_reg);
	qla24xx_पढ़ो_winकरोw(reg, 0x6F00, 16, iter_reg);

	/* Multi queue रेजिस्टरs */
	nxt_chain = qla25xx_copy_mq(ha, (व्योम *)ha->fw_dump + ha->chain_offset,
	    &last_chain);

	rval = qla24xx_soft_reset(ha);
	अगर (rval != QLA_SUCCESS)
		जाओ qla25xx_fw_dump_failed_0;

	rval = qla24xx_dump_memory(ha, fw->code_ram, माप(fw->code_ram),
	    &nxt);
	अगर (rval != QLA_SUCCESS)
		जाओ qla25xx_fw_dump_failed_0;

	nxt = qla2xxx_copy_queues(ha, nxt);

	qla24xx_copy_eft(ha, nxt);

	/* Chain entries -- started with MQ. */
	nxt_chain = qla25xx_copy_fce(ha, nxt_chain, &last_chain);
	nxt_chain = qla25xx_copy_mqueues(ha, nxt_chain, &last_chain);
	nxt_chain = qla2xxx_copy_atioqueues(ha, nxt_chain, &last_chain);
	nxt_chain = qla25xx_copy_exlogin(ha, nxt_chain, &last_chain);
	अगर (last_chain) अणु
		ha->fw_dump->version |= htonl(DUMP_CHAIN_VARIANT);
		*last_chain |= htonl(DUMP_CHAIN_LAST);
	पूर्ण

	/* Adjust valid length. */
	ha->fw_dump_len = (nxt_chain - (व्योम *)ha->fw_dump);

qla25xx_fw_dump_failed_0:
	qla2xxx_dump_post_process(base_vha, rval);
पूर्ण

व्योम
qla81xx_fw_dump(scsi_qla_host_t *vha)
अणु
	पूर्णांक		rval;
	uपूर्णांक32_t	cnt;
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा device_reg_24xx __iomem *reg = &ha->iobase->isp24;
	__le32 __iomem *dmp_reg;
	__be32		*iter_reg;
	__le16 __iomem *mbx_reg;
	काष्ठा qla81xx_fw_dump *fw;
	व्योम		*nxt, *nxt_chain;
	__be32		*last_chain = शून्य;
	काष्ठा scsi_qla_host *base_vha = pci_get_drvdata(ha->pdev);

	lockdep_निश्चित_held(&ha->hardware_lock);

	ha->fw_dump_cap_flags = 0;

	अगर (!ha->fw_dump) अणु
		ql_log(ql_log_warn, vha, 0xd00a,
		    "No buffer available for dump.\n");
		वापस;
	पूर्ण

	अगर (ha->fw_dumped) अणु
		ql_log(ql_log_warn, vha, 0xd00b,
		    "Firmware has been previously dumped (%p) "
		    "-- ignoring request.\n",
		    ha->fw_dump);
		वापस;
	पूर्ण
	fw = &ha->fw_dump->isp.isp81;
	qla2xxx_prep_dump(ha, ha->fw_dump);

	fw->host_status = htonl(rd_reg_dword(&reg->host_status));

	/*
	 * Pause RISC. No need to track समयout, as resetting the chip
	 * is the right approach inहाल of छोड़ो समयout
	 */
	qla24xx_छोड़ो_risc(reg, ha);

	/* Host/Risc रेजिस्टरs. */
	iter_reg = fw->host_risc_reg;
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x7000, 16, iter_reg);
	qla24xx_पढ़ो_winकरोw(reg, 0x7010, 16, iter_reg);

	/* PCIe रेजिस्टरs. */
	wrt_reg_dword(&reg->iobase_addr, 0x7C00);
	rd_reg_dword(&reg->iobase_addr);
	wrt_reg_dword(&reg->iobase_winकरोw, 0x01);
	dmp_reg = &reg->iobase_c4;
	fw->pcie_regs[0] = htonl(rd_reg_dword(dmp_reg));
	dmp_reg++;
	fw->pcie_regs[1] = htonl(rd_reg_dword(dmp_reg));
	dmp_reg++;
	fw->pcie_regs[2] = htonl(rd_reg_dword(dmp_reg));
	fw->pcie_regs[3] = htonl(rd_reg_dword(&reg->iobase_winकरोw));

	wrt_reg_dword(&reg->iobase_winकरोw, 0x00);
	rd_reg_dword(&reg->iobase_winकरोw);

	/* Host पूर्णांकerface रेजिस्टरs. */
	dmp_reg = &reg->flash_addr;
	क्रम (cnt = 0; cnt < ARRAY_SIZE(fw->host_reg); cnt++, dmp_reg++)
		fw->host_reg[cnt] = htonl(rd_reg_dword(dmp_reg));

	/* Disable पूर्णांकerrupts. */
	wrt_reg_dword(&reg->ictrl, 0);
	rd_reg_dword(&reg->ictrl);

	/* Shaकरोw रेजिस्टरs. */
	wrt_reg_dword(&reg->iobase_addr, 0x0F70);
	rd_reg_dword(&reg->iobase_addr);
	wrt_reg_dword(&reg->iobase_select, 0xB0000000);
	fw->shaकरोw_reg[0] = htonl(rd_reg_dword(&reg->iobase_sdata));

	wrt_reg_dword(&reg->iobase_select, 0xB0100000);
	fw->shaकरोw_reg[1] = htonl(rd_reg_dword(&reg->iobase_sdata));

	wrt_reg_dword(&reg->iobase_select, 0xB0200000);
	fw->shaकरोw_reg[2] = htonl(rd_reg_dword(&reg->iobase_sdata));

	wrt_reg_dword(&reg->iobase_select, 0xB0300000);
	fw->shaकरोw_reg[3] = htonl(rd_reg_dword(&reg->iobase_sdata));

	wrt_reg_dword(&reg->iobase_select, 0xB0400000);
	fw->shaकरोw_reg[4] = htonl(rd_reg_dword(&reg->iobase_sdata));

	wrt_reg_dword(&reg->iobase_select, 0xB0500000);
	fw->shaकरोw_reg[5] = htonl(rd_reg_dword(&reg->iobase_sdata));

	wrt_reg_dword(&reg->iobase_select, 0xB0600000);
	fw->shaकरोw_reg[6] = htonl(rd_reg_dword(&reg->iobase_sdata));

	wrt_reg_dword(&reg->iobase_select, 0xB0700000);
	fw->shaकरोw_reg[7] = htonl(rd_reg_dword(&reg->iobase_sdata));

	wrt_reg_dword(&reg->iobase_select, 0xB0800000);
	fw->shaकरोw_reg[8] = htonl(rd_reg_dword(&reg->iobase_sdata));

	wrt_reg_dword(&reg->iobase_select, 0xB0900000);
	fw->shaकरोw_reg[9] = htonl(rd_reg_dword(&reg->iobase_sdata));

	wrt_reg_dword(&reg->iobase_select, 0xB0A00000);
	fw->shaकरोw_reg[10] = htonl(rd_reg_dword(&reg->iobase_sdata));

	/* RISC I/O रेजिस्टर. */
	wrt_reg_dword(&reg->iobase_addr, 0x0010);
	fw->risc_io_reg = htonl(rd_reg_dword(&reg->iobase_winकरोw));

	/* Mailbox रेजिस्टरs. */
	mbx_reg = &reg->mailbox0;
	क्रम (cnt = 0; cnt < ARRAY_SIZE(fw->mailbox_reg); cnt++, mbx_reg++)
		fw->mailbox_reg[cnt] = htons(rd_reg_word(mbx_reg));

	/* Transfer sequence रेजिस्टरs. */
	iter_reg = fw->xseq_gp_reg;
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0xBF00, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0xBF10, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0xBF20, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0xBF30, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0xBF40, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0xBF50, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0xBF60, 16, iter_reg);
	qla24xx_पढ़ो_winकरोw(reg, 0xBF70, 16, iter_reg);

	iter_reg = fw->xseq_0_reg;
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0xBFC0, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0xBFD0, 16, iter_reg);
	qla24xx_पढ़ो_winकरोw(reg, 0xBFE0, 16, iter_reg);

	qla24xx_पढ़ो_winकरोw(reg, 0xBFF0, 16, fw->xseq_1_reg);

	/* Receive sequence रेजिस्टरs. */
	iter_reg = fw->rseq_gp_reg;
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0xFF00, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0xFF10, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0xFF20, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0xFF30, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0xFF40, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0xFF50, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0xFF60, 16, iter_reg);
	qla24xx_पढ़ो_winकरोw(reg, 0xFF70, 16, iter_reg);

	iter_reg = fw->rseq_0_reg;
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0xFFC0, 16, iter_reg);
	qla24xx_पढ़ो_winकरोw(reg, 0xFFD0, 16, iter_reg);

	qla24xx_पढ़ो_winकरोw(reg, 0xFFE0, 16, fw->rseq_1_reg);
	qla24xx_पढ़ो_winकरोw(reg, 0xFFF0, 16, fw->rseq_2_reg);

	/* Auxiliary sequence रेजिस्टरs. */
	iter_reg = fw->aseq_gp_reg;
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0xB000, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0xB010, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0xB020, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0xB030, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0xB040, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0xB050, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0xB060, 16, iter_reg);
	qla24xx_पढ़ो_winकरोw(reg, 0xB070, 16, iter_reg);

	iter_reg = fw->aseq_0_reg;
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0xB0C0, 16, iter_reg);
	qla24xx_पढ़ो_winकरोw(reg, 0xB0D0, 16, iter_reg);

	qla24xx_पढ़ो_winकरोw(reg, 0xB0E0, 16, fw->aseq_1_reg);
	qla24xx_पढ़ो_winकरोw(reg, 0xB0F0, 16, fw->aseq_2_reg);

	/* Command DMA रेजिस्टरs. */
	qla24xx_पढ़ो_winकरोw(reg, 0x7100, 16, fw->cmd_dma_reg);

	/* Queues. */
	iter_reg = fw->req0_dma_reg;
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x7200, 8, iter_reg);
	dmp_reg = &reg->iobase_q;
	क्रम (cnt = 0; cnt < 7; cnt++, dmp_reg++)
		*iter_reg++ = htonl(rd_reg_dword(dmp_reg));

	iter_reg = fw->resp0_dma_reg;
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x7300, 8, iter_reg);
	dmp_reg = &reg->iobase_q;
	क्रम (cnt = 0; cnt < 7; cnt++, dmp_reg++)
		*iter_reg++ = htonl(rd_reg_dword(dmp_reg));

	iter_reg = fw->req1_dma_reg;
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x7400, 8, iter_reg);
	dmp_reg = &reg->iobase_q;
	क्रम (cnt = 0; cnt < 7; cnt++, dmp_reg++)
		*iter_reg++ = htonl(rd_reg_dword(dmp_reg));

	/* Transmit DMA रेजिस्टरs. */
	iter_reg = fw->xmt0_dma_reg;
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x7600, 16, iter_reg);
	qla24xx_पढ़ो_winकरोw(reg, 0x7610, 16, iter_reg);

	iter_reg = fw->xmt1_dma_reg;
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x7620, 16, iter_reg);
	qla24xx_पढ़ो_winकरोw(reg, 0x7630, 16, iter_reg);

	iter_reg = fw->xmt2_dma_reg;
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x7640, 16, iter_reg);
	qla24xx_पढ़ो_winकरोw(reg, 0x7650, 16, iter_reg);

	iter_reg = fw->xmt3_dma_reg;
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x7660, 16, iter_reg);
	qla24xx_पढ़ो_winकरोw(reg, 0x7670, 16, iter_reg);

	iter_reg = fw->xmt4_dma_reg;
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x7680, 16, iter_reg);
	qla24xx_पढ़ो_winकरोw(reg, 0x7690, 16, iter_reg);

	qla24xx_पढ़ो_winकरोw(reg, 0x76A0, 16, fw->xmt_data_dma_reg);

	/* Receive DMA रेजिस्टरs. */
	iter_reg = fw->rcvt0_data_dma_reg;
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x7700, 16, iter_reg);
	qla24xx_पढ़ो_winकरोw(reg, 0x7710, 16, iter_reg);

	iter_reg = fw->rcvt1_data_dma_reg;
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x7720, 16, iter_reg);
	qla24xx_पढ़ो_winकरोw(reg, 0x7730, 16, iter_reg);

	/* RISC रेजिस्टरs. */
	iter_reg = fw->risc_gp_reg;
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x0F00, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x0F10, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x0F20, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x0F30, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x0F40, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x0F50, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x0F60, 16, iter_reg);
	qla24xx_पढ़ो_winकरोw(reg, 0x0F70, 16, iter_reg);

	/* Local memory controller रेजिस्टरs. */
	iter_reg = fw->lmc_reg;
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x3000, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x3010, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x3020, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x3030, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x3040, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x3050, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x3060, 16, iter_reg);
	qla24xx_पढ़ो_winकरोw(reg, 0x3070, 16, iter_reg);

	/* Fibre Protocol Module रेजिस्टरs. */
	iter_reg = fw->fpm_hdw_reg;
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x4000, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x4010, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x4020, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x4030, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x4040, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x4050, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x4060, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x4070, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x4080, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x4090, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x40A0, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x40B0, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x40C0, 16, iter_reg);
	qla24xx_पढ़ो_winकरोw(reg, 0x40D0, 16, iter_reg);

	/* Frame Buffer रेजिस्टरs. */
	iter_reg = fw->fb_hdw_reg;
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x6000, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x6010, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x6020, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x6030, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x6040, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x6100, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x6130, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x6150, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x6170, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x6190, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x61B0, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x61C0, 16, iter_reg);
	qla24xx_पढ़ो_winकरोw(reg, 0x6F00, 16, iter_reg);

	/* Multi queue रेजिस्टरs */
	nxt_chain = qla25xx_copy_mq(ha, (व्योम *)ha->fw_dump + ha->chain_offset,
	    &last_chain);

	rval = qla24xx_soft_reset(ha);
	अगर (rval != QLA_SUCCESS)
		जाओ qla81xx_fw_dump_failed_0;

	rval = qla24xx_dump_memory(ha, fw->code_ram, माप(fw->code_ram),
	    &nxt);
	अगर (rval != QLA_SUCCESS)
		जाओ qla81xx_fw_dump_failed_0;

	nxt = qla2xxx_copy_queues(ha, nxt);

	qla24xx_copy_eft(ha, nxt);

	/* Chain entries -- started with MQ. */
	nxt_chain = qla25xx_copy_fce(ha, nxt_chain, &last_chain);
	nxt_chain = qla25xx_copy_mqueues(ha, nxt_chain, &last_chain);
	nxt_chain = qla2xxx_copy_atioqueues(ha, nxt_chain, &last_chain);
	nxt_chain = qla25xx_copy_exlogin(ha, nxt_chain, &last_chain);
	nxt_chain = qla81xx_copy_exchoffld(ha, nxt_chain, &last_chain);
	अगर (last_chain) अणु
		ha->fw_dump->version |= htonl(DUMP_CHAIN_VARIANT);
		*last_chain |= htonl(DUMP_CHAIN_LAST);
	पूर्ण

	/* Adjust valid length. */
	ha->fw_dump_len = (nxt_chain - (व्योम *)ha->fw_dump);

qla81xx_fw_dump_failed_0:
	qla2xxx_dump_post_process(base_vha, rval);
पूर्ण

व्योम
qla83xx_fw_dump(scsi_qla_host_t *vha)
अणु
	पूर्णांक		rval;
	uपूर्णांक32_t	cnt;
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा device_reg_24xx __iomem *reg = &ha->iobase->isp24;
	__le32 __iomem *dmp_reg;
	__be32		*iter_reg;
	__le16 __iomem *mbx_reg;
	काष्ठा qla83xx_fw_dump *fw;
	व्योम		*nxt, *nxt_chain;
	__be32		*last_chain = शून्य;
	काष्ठा scsi_qla_host *base_vha = pci_get_drvdata(ha->pdev);

	lockdep_निश्चित_held(&ha->hardware_lock);

	ha->fw_dump_cap_flags = 0;

	अगर (!ha->fw_dump) अणु
		ql_log(ql_log_warn, vha, 0xd00c,
		    "No buffer available for dump!!!\n");
		वापस;
	पूर्ण

	अगर (ha->fw_dumped) अणु
		ql_log(ql_log_warn, vha, 0xd00d,
		    "Firmware has been previously dumped (%p) -- ignoring "
		    "request...\n", ha->fw_dump);
		वापस;
	पूर्ण
	QLA_FW_STOPPED(ha);
	fw = &ha->fw_dump->isp.isp83;
	qla2xxx_prep_dump(ha, ha->fw_dump);

	fw->host_status = htonl(rd_reg_dword(&reg->host_status));

	/*
	 * Pause RISC. No need to track समयout, as resetting the chip
	 * is the right approach inहाल of छोड़ो समयout
	 */
	qla24xx_छोड़ो_risc(reg, ha);

	wrt_reg_dword(&reg->iobase_addr, 0x6000);
	dmp_reg = &reg->iobase_winकरोw;
	rd_reg_dword(dmp_reg);
	wrt_reg_dword(dmp_reg, 0);

	dmp_reg = &reg->unused_4_1[0];
	rd_reg_dword(dmp_reg);
	wrt_reg_dword(dmp_reg, 0);

	wrt_reg_dword(&reg->iobase_addr, 0x6010);
	dmp_reg = &reg->unused_4_1[2];
	rd_reg_dword(dmp_reg);
	wrt_reg_dword(dmp_reg, 0);

	/* select PCR and disable ecc checking and correction */
	wrt_reg_dword(&reg->iobase_addr, 0x0F70);
	rd_reg_dword(&reg->iobase_addr);
	wrt_reg_dword(&reg->iobase_select, 0x60000000);	/* ग_लिखो to F0h = PCR */

	/* Host/Risc रेजिस्टरs. */
	iter_reg = fw->host_risc_reg;
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x7000, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x7010, 16, iter_reg);
	qla24xx_पढ़ो_winकरोw(reg, 0x7040, 16, iter_reg);

	/* PCIe रेजिस्टरs. */
	wrt_reg_dword(&reg->iobase_addr, 0x7C00);
	rd_reg_dword(&reg->iobase_addr);
	wrt_reg_dword(&reg->iobase_winकरोw, 0x01);
	dmp_reg = &reg->iobase_c4;
	fw->pcie_regs[0] = htonl(rd_reg_dword(dmp_reg));
	dmp_reg++;
	fw->pcie_regs[1] = htonl(rd_reg_dword(dmp_reg));
	dmp_reg++;
	fw->pcie_regs[2] = htonl(rd_reg_dword(dmp_reg));
	fw->pcie_regs[3] = htonl(rd_reg_dword(&reg->iobase_winकरोw));

	wrt_reg_dword(&reg->iobase_winकरोw, 0x00);
	rd_reg_dword(&reg->iobase_winकरोw);

	/* Host पूर्णांकerface रेजिस्टरs. */
	dmp_reg = &reg->flash_addr;
	क्रम (cnt = 0; cnt < ARRAY_SIZE(fw->host_reg); cnt++, dmp_reg++)
		fw->host_reg[cnt] = htonl(rd_reg_dword(dmp_reg));

	/* Disable पूर्णांकerrupts. */
	wrt_reg_dword(&reg->ictrl, 0);
	rd_reg_dword(&reg->ictrl);

	/* Shaकरोw रेजिस्टरs. */
	wrt_reg_dword(&reg->iobase_addr, 0x0F70);
	rd_reg_dword(&reg->iobase_addr);
	wrt_reg_dword(&reg->iobase_select, 0xB0000000);
	fw->shaकरोw_reg[0] = htonl(rd_reg_dword(&reg->iobase_sdata));

	wrt_reg_dword(&reg->iobase_select, 0xB0100000);
	fw->shaकरोw_reg[1] = htonl(rd_reg_dword(&reg->iobase_sdata));

	wrt_reg_dword(&reg->iobase_select, 0xB0200000);
	fw->shaकरोw_reg[2] = htonl(rd_reg_dword(&reg->iobase_sdata));

	wrt_reg_dword(&reg->iobase_select, 0xB0300000);
	fw->shaकरोw_reg[3] = htonl(rd_reg_dword(&reg->iobase_sdata));

	wrt_reg_dword(&reg->iobase_select, 0xB0400000);
	fw->shaकरोw_reg[4] = htonl(rd_reg_dword(&reg->iobase_sdata));

	wrt_reg_dword(&reg->iobase_select, 0xB0500000);
	fw->shaकरोw_reg[5] = htonl(rd_reg_dword(&reg->iobase_sdata));

	wrt_reg_dword(&reg->iobase_select, 0xB0600000);
	fw->shaकरोw_reg[6] = htonl(rd_reg_dword(&reg->iobase_sdata));

	wrt_reg_dword(&reg->iobase_select, 0xB0700000);
	fw->shaकरोw_reg[7] = htonl(rd_reg_dword(&reg->iobase_sdata));

	wrt_reg_dword(&reg->iobase_select, 0xB0800000);
	fw->shaकरोw_reg[8] = htonl(rd_reg_dword(&reg->iobase_sdata));

	wrt_reg_dword(&reg->iobase_select, 0xB0900000);
	fw->shaकरोw_reg[9] = htonl(rd_reg_dword(&reg->iobase_sdata));

	wrt_reg_dword(&reg->iobase_select, 0xB0A00000);
	fw->shaकरोw_reg[10] = htonl(rd_reg_dword(&reg->iobase_sdata));

	/* RISC I/O रेजिस्टर. */
	wrt_reg_dword(&reg->iobase_addr, 0x0010);
	fw->risc_io_reg = htonl(rd_reg_dword(&reg->iobase_winकरोw));

	/* Mailbox रेजिस्टरs. */
	mbx_reg = &reg->mailbox0;
	क्रम (cnt = 0; cnt < ARRAY_SIZE(fw->mailbox_reg); cnt++, mbx_reg++)
		fw->mailbox_reg[cnt] = htons(rd_reg_word(mbx_reg));

	/* Transfer sequence रेजिस्टरs. */
	iter_reg = fw->xseq_gp_reg;
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0xBE00, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0xBE10, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0xBE20, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0xBE30, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0xBE40, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0xBE50, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0xBE60, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0xBE70, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0xBF00, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0xBF10, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0xBF20, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0xBF30, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0xBF40, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0xBF50, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0xBF60, 16, iter_reg);
	qla24xx_पढ़ो_winकरोw(reg, 0xBF70, 16, iter_reg);

	iter_reg = fw->xseq_0_reg;
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0xBFC0, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0xBFD0, 16, iter_reg);
	qla24xx_पढ़ो_winकरोw(reg, 0xBFE0, 16, iter_reg);

	qla24xx_पढ़ो_winकरोw(reg, 0xBFF0, 16, fw->xseq_1_reg);

	qla24xx_पढ़ो_winकरोw(reg, 0xBEF0, 16, fw->xseq_2_reg);

	/* Receive sequence रेजिस्टरs. */
	iter_reg = fw->rseq_gp_reg;
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0xFE00, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0xFE10, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0xFE20, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0xFE30, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0xFE40, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0xFE50, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0xFE60, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0xFE70, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0xFF00, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0xFF10, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0xFF20, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0xFF30, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0xFF40, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0xFF50, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0xFF60, 16, iter_reg);
	qla24xx_पढ़ो_winकरोw(reg, 0xFF70, 16, iter_reg);

	iter_reg = fw->rseq_0_reg;
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0xFFC0, 16, iter_reg);
	qla24xx_पढ़ो_winकरोw(reg, 0xFFD0, 16, iter_reg);

	qla24xx_पढ़ो_winकरोw(reg, 0xFFE0, 16, fw->rseq_1_reg);
	qla24xx_पढ़ो_winकरोw(reg, 0xFFF0, 16, fw->rseq_2_reg);
	qla24xx_पढ़ो_winकरोw(reg, 0xFEF0, 16, fw->rseq_3_reg);

	/* Auxiliary sequence रेजिस्टरs. */
	iter_reg = fw->aseq_gp_reg;
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0xB000, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0xB010, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0xB020, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0xB030, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0xB040, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0xB050, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0xB060, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0xB070, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0xB100, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0xB110, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0xB120, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0xB130, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0xB140, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0xB150, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0xB160, 16, iter_reg);
	qla24xx_पढ़ो_winकरोw(reg, 0xB170, 16, iter_reg);

	iter_reg = fw->aseq_0_reg;
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0xB0C0, 16, iter_reg);
	qla24xx_पढ़ो_winकरोw(reg, 0xB0D0, 16, iter_reg);

	qla24xx_पढ़ो_winकरोw(reg, 0xB0E0, 16, fw->aseq_1_reg);
	qla24xx_पढ़ो_winकरोw(reg, 0xB0F0, 16, fw->aseq_2_reg);
	qla24xx_पढ़ो_winकरोw(reg, 0xB1F0, 16, fw->aseq_3_reg);

	/* Command DMA रेजिस्टरs. */
	iter_reg = fw->cmd_dma_reg;
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x7100, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x7120, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x7130, 16, iter_reg);
	qla24xx_पढ़ो_winकरोw(reg, 0x71F0, 16, iter_reg);

	/* Queues. */
	iter_reg = fw->req0_dma_reg;
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x7200, 8, iter_reg);
	dmp_reg = &reg->iobase_q;
	क्रम (cnt = 0; cnt < 7; cnt++, dmp_reg++)
		*iter_reg++ = htonl(rd_reg_dword(dmp_reg));

	iter_reg = fw->resp0_dma_reg;
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x7300, 8, iter_reg);
	dmp_reg = &reg->iobase_q;
	क्रम (cnt = 0; cnt < 7; cnt++, dmp_reg++)
		*iter_reg++ = htonl(rd_reg_dword(dmp_reg));

	iter_reg = fw->req1_dma_reg;
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x7400, 8, iter_reg);
	dmp_reg = &reg->iobase_q;
	क्रम (cnt = 0; cnt < 7; cnt++, dmp_reg++)
		*iter_reg++ = htonl(rd_reg_dword(dmp_reg));

	/* Transmit DMA रेजिस्टरs. */
	iter_reg = fw->xmt0_dma_reg;
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x7600, 16, iter_reg);
	qla24xx_पढ़ो_winकरोw(reg, 0x7610, 16, iter_reg);

	iter_reg = fw->xmt1_dma_reg;
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x7620, 16, iter_reg);
	qla24xx_पढ़ो_winकरोw(reg, 0x7630, 16, iter_reg);

	iter_reg = fw->xmt2_dma_reg;
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x7640, 16, iter_reg);
	qla24xx_पढ़ो_winकरोw(reg, 0x7650, 16, iter_reg);

	iter_reg = fw->xmt3_dma_reg;
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x7660, 16, iter_reg);
	qla24xx_पढ़ो_winकरोw(reg, 0x7670, 16, iter_reg);

	iter_reg = fw->xmt4_dma_reg;
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x7680, 16, iter_reg);
	qla24xx_पढ़ो_winकरोw(reg, 0x7690, 16, iter_reg);

	qla24xx_पढ़ो_winकरोw(reg, 0x76A0, 16, fw->xmt_data_dma_reg);

	/* Receive DMA रेजिस्टरs. */
	iter_reg = fw->rcvt0_data_dma_reg;
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x7700, 16, iter_reg);
	qla24xx_पढ़ो_winकरोw(reg, 0x7710, 16, iter_reg);

	iter_reg = fw->rcvt1_data_dma_reg;
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x7720, 16, iter_reg);
	qla24xx_पढ़ो_winकरोw(reg, 0x7730, 16, iter_reg);

	/* RISC रेजिस्टरs. */
	iter_reg = fw->risc_gp_reg;
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x0F00, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x0F10, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x0F20, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x0F30, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x0F40, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x0F50, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x0F60, 16, iter_reg);
	qla24xx_पढ़ो_winकरोw(reg, 0x0F70, 16, iter_reg);

	/* Local memory controller रेजिस्टरs. */
	iter_reg = fw->lmc_reg;
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x3000, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x3010, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x3020, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x3030, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x3040, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x3050, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x3060, 16, iter_reg);
	qla24xx_पढ़ो_winकरोw(reg, 0x3070, 16, iter_reg);

	/* Fibre Protocol Module रेजिस्टरs. */
	iter_reg = fw->fpm_hdw_reg;
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x4000, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x4010, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x4020, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x4030, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x4040, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x4050, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x4060, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x4070, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x4080, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x4090, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x40A0, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x40B0, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x40C0, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x40D0, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x40E0, 16, iter_reg);
	qla24xx_पढ़ो_winकरोw(reg, 0x40F0, 16, iter_reg);

	/* RQ0 Array रेजिस्टरs. */
	iter_reg = fw->rq0_array_reg;
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x5C00, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x5C10, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x5C20, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x5C30, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x5C40, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x5C50, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x5C60, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x5C70, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x5C80, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x5C90, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x5CA0, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x5CB0, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x5CC0, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x5CD0, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x5CE0, 16, iter_reg);
	qla24xx_पढ़ो_winकरोw(reg, 0x5CF0, 16, iter_reg);

	/* RQ1 Array रेजिस्टरs. */
	iter_reg = fw->rq1_array_reg;
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x5D00, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x5D10, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x5D20, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x5D30, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x5D40, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x5D50, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x5D60, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x5D70, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x5D80, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x5D90, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x5DA0, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x5DB0, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x5DC0, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x5DD0, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x5DE0, 16, iter_reg);
	qla24xx_पढ़ो_winकरोw(reg, 0x5DF0, 16, iter_reg);

	/* RP0 Array रेजिस्टरs. */
	iter_reg = fw->rp0_array_reg;
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x5E00, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x5E10, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x5E20, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x5E30, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x5E40, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x5E50, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x5E60, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x5E70, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x5E80, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x5E90, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x5EA0, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x5EB0, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x5EC0, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x5ED0, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x5EE0, 16, iter_reg);
	qla24xx_पढ़ो_winकरोw(reg, 0x5EF0, 16, iter_reg);

	/* RP1 Array रेजिस्टरs. */
	iter_reg = fw->rp1_array_reg;
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x5F00, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x5F10, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x5F20, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x5F30, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x5F40, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x5F50, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x5F60, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x5F70, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x5F80, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x5F90, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x5FA0, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x5FB0, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x5FC0, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x5FD0, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x5FE0, 16, iter_reg);
	qla24xx_पढ़ो_winकरोw(reg, 0x5FF0, 16, iter_reg);

	iter_reg = fw->at0_array_reg;
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x7080, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x7090, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x70A0, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x70B0, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x70C0, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x70D0, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x70E0, 16, iter_reg);
	qla24xx_पढ़ो_winकरोw(reg, 0x70F0, 16, iter_reg);

	/* I/O Queue Control रेजिस्टरs. */
	qla24xx_पढ़ो_winकरोw(reg, 0x7800, 16, fw->queue_control_reg);

	/* Frame Buffer रेजिस्टरs. */
	iter_reg = fw->fb_hdw_reg;
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x6000, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x6010, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x6020, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x6030, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x6040, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x6060, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x6070, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x6100, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x6130, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x6150, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x6170, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x6190, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x61B0, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x61C0, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x6530, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x6540, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x6550, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x6560, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x6570, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x6580, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x6590, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x65A0, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x65B0, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x65C0, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x65D0, 16, iter_reg);
	iter_reg = qla24xx_पढ़ो_winकरोw(reg, 0x65E0, 16, iter_reg);
	qla24xx_पढ़ो_winकरोw(reg, 0x6F00, 16, iter_reg);

	/* Multi queue रेजिस्टरs */
	nxt_chain = qla25xx_copy_mq(ha, (व्योम *)ha->fw_dump + ha->chain_offset,
	    &last_chain);

	rval = qla24xx_soft_reset(ha);
	अगर (rval != QLA_SUCCESS) अणु
		ql_log(ql_log_warn, vha, 0xd00e,
		    "SOFT RESET FAILED, forcing continuation of dump!!!\n");
		rval = QLA_SUCCESS;

		ql_log(ql_log_warn, vha, 0xd00f, "try a bigger hammer!!!\n");

		wrt_reg_dword(&reg->hccr, HCCRX_SET_RISC_RESET);
		rd_reg_dword(&reg->hccr);

		wrt_reg_dword(&reg->hccr, HCCRX_REL_RISC_PAUSE);
		rd_reg_dword(&reg->hccr);

		wrt_reg_dword(&reg->hccr, HCCRX_CLR_RISC_RESET);
		rd_reg_dword(&reg->hccr);

		क्रम (cnt = 30000; cnt && (rd_reg_word(&reg->mailbox0)); cnt--)
			udelay(5);

		अगर (!cnt) अणु
			nxt = fw->code_ram;
			nxt += माप(fw->code_ram);
			nxt += (ha->fw_memory_size - 0x100000 + 1);
			जाओ copy_queue;
		पूर्ण अन्यथा अणु
			set_bit(RISC_RDY_AFT_RESET, &ha->fw_dump_cap_flags);
			ql_log(ql_log_warn, vha, 0xd010,
			    "bigger hammer success?\n");
		पूर्ण
	पूर्ण

	rval = qla24xx_dump_memory(ha, fw->code_ram, माप(fw->code_ram),
	    &nxt);
	अगर (rval != QLA_SUCCESS)
		जाओ qla83xx_fw_dump_failed_0;

copy_queue:
	nxt = qla2xxx_copy_queues(ha, nxt);

	qla24xx_copy_eft(ha, nxt);

	/* Chain entries -- started with MQ. */
	nxt_chain = qla25xx_copy_fce(ha, nxt_chain, &last_chain);
	nxt_chain = qla25xx_copy_mqueues(ha, nxt_chain, &last_chain);
	nxt_chain = qla2xxx_copy_atioqueues(ha, nxt_chain, &last_chain);
	nxt_chain = qla25xx_copy_exlogin(ha, nxt_chain, &last_chain);
	nxt_chain = qla81xx_copy_exchoffld(ha, nxt_chain, &last_chain);
	अगर (last_chain) अणु
		ha->fw_dump->version |= htonl(DUMP_CHAIN_VARIANT);
		*last_chain |= htonl(DUMP_CHAIN_LAST);
	पूर्ण

	/* Adjust valid length. */
	ha->fw_dump_len = (nxt_chain - (व्योम *)ha->fw_dump);

qla83xx_fw_dump_failed_0:
	qla2xxx_dump_post_process(base_vha, rval);
पूर्ण

/****************************************************************************/
/*                         Driver Debug Functions.                          */
/****************************************************************************/

/* Write the debug message prefix पूर्णांकo @pbuf. */
अटल व्योम ql_dbg_prefix(अक्षर *pbuf, पूर्णांक pbuf_size,
			  स्थिर scsi_qla_host_t *vha, uपूर्णांक msg_id)
अणु
	अगर (vha) अणु
		स्थिर काष्ठा pci_dev *pdev = vha->hw->pdev;

		/* <module-name> [<dev-name>]-<msg-id>:<host>: */
		snम_लिखो(pbuf, pbuf_size, "%s [%s]-%04x:%lu: ", QL_MSGHDR,
			 dev_name(&(pdev->dev)), msg_id, vha->host_no);
	पूर्ण अन्यथा अणु
		/* <module-name> [<dev-name>]-<msg-id>: : */
		snम_लिखो(pbuf, pbuf_size, "%s [%s]-%04x: : ", QL_MSGHDR,
			 "0000:00:00.0", msg_id);
	पूर्ण
पूर्ण

/*
 * This function is क्रम क्रमmatting and logging debug inक्रमmation.
 * It is to be used when vha is available. It क्रमmats the message
 * and logs it to the messages file.
 * parameters:
 * level: The level of the debug messages to be prपूर्णांकed.
 *        If ql2xextended_error_logging value is correctly set,
 *        this message will appear in the messages file.
 * vha:   Poपूर्णांकer to the scsi_qla_host_t.
 * id:    This is a unique identअगरier क्रम the level. It identअगरies the
 *        part of the code from where the message originated.
 * msg:   The message to be displayed.
 */
व्योम
ql_dbg(uपूर्णांक level, scsi_qla_host_t *vha, uपूर्णांक id, स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची va;
	काष्ठा va_क्रमmat vaf;
	अक्षर pbuf[64];

	बहु_शुरू(va, fmt);

	vaf.fmt = fmt;
	vaf.va = &va;

	ql_dbg_prefix(pbuf, ARRAY_SIZE(pbuf), vha, id);

	अगर (!ql_mask_match(level))
		trace_ql_dbg_log(pbuf, &vaf);
	अन्यथा
		pr_warn("%s%pV", pbuf, &vaf);

	बहु_पूर्ण(va);

पूर्ण

/*
 * This function is क्रम क्रमmatting and logging debug inक्रमmation.
 * It is to be used when vha is not available and pci is available,
 * i.e., beक्रमe host allocation. It क्रमmats the message and logs it
 * to the messages file.
 * parameters:
 * level: The level of the debug messages to be prपूर्णांकed.
 *        If ql2xextended_error_logging value is correctly set,
 *        this message will appear in the messages file.
 * pdev:  Poपूर्णांकer to the काष्ठा pci_dev.
 * id:    This is a unique id क्रम the level. It identअगरies the part
 *        of the code from where the message originated.
 * msg:   The message to be displayed.
 */
व्योम
ql_dbg_pci(uपूर्णांक level, काष्ठा pci_dev *pdev, uपूर्णांक id, स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची va;
	काष्ठा va_क्रमmat vaf;
	अक्षर pbuf[128];

	अगर (pdev == शून्य)
		वापस;
	अगर (!ql_mask_match(level))
		वापस;

	बहु_शुरू(va, fmt);

	vaf.fmt = fmt;
	vaf.va = &va;

	ql_dbg_prefix(pbuf, ARRAY_SIZE(pbuf), शून्य, id + ql_dbg_offset);
	pr_warn("%s%pV", pbuf, &vaf);

	बहु_पूर्ण(va);
पूर्ण

/*
 * This function is क्रम क्रमmatting and logging log messages.
 * It is to be used when vha is available. It क्रमmats the message
 * and logs it to the messages file. All the messages will be logged
 * irrespective of value of ql2xextended_error_logging.
 * parameters:
 * level: The level of the log messages to be prपूर्णांकed in the
 *        messages file.
 * vha:   Poपूर्णांकer to the scsi_qla_host_t
 * id:    This is a unique id क्रम the level. It identअगरies the
 *        part of the code from where the message originated.
 * msg:   The message to be displayed.
 */
व्योम
ql_log(uपूर्णांक level, scsi_qla_host_t *vha, uपूर्णांक id, स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची va;
	काष्ठा va_क्रमmat vaf;
	अक्षर pbuf[128];

	अगर (level > ql_errlev)
		वापस;

	ql_dbg_prefix(pbuf, ARRAY_SIZE(pbuf), vha, id);

	बहु_शुरू(va, fmt);

	vaf.fmt = fmt;
	vaf.va = &va;

	चयन (level) अणु
	हाल ql_log_fatal: /* FATAL LOG */
		pr_crit("%s%pV", pbuf, &vaf);
		अवरोध;
	हाल ql_log_warn:
		pr_err("%s%pV", pbuf, &vaf);
		अवरोध;
	हाल ql_log_info:
		pr_warn("%s%pV", pbuf, &vaf);
		अवरोध;
	शेष:
		pr_info("%s%pV", pbuf, &vaf);
		अवरोध;
	पूर्ण

	बहु_पूर्ण(va);
पूर्ण

/*
 * This function is क्रम क्रमmatting and logging log messages.
 * It is to be used when vha is not available and pci is available,
 * i.e., beक्रमe host allocation. It क्रमmats the message and logs
 * it to the messages file. All the messages are logged irrespective
 * of the value of ql2xextended_error_logging.
 * parameters:
 * level: The level of the log messages to be prपूर्णांकed in the
 *        messages file.
 * pdev:  Poपूर्णांकer to the काष्ठा pci_dev.
 * id:    This is a unique id क्रम the level. It identअगरies the
 *        part of the code from where the message originated.
 * msg:   The message to be displayed.
 */
व्योम
ql_log_pci(uपूर्णांक level, काष्ठा pci_dev *pdev, uपूर्णांक id, स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची va;
	काष्ठा va_क्रमmat vaf;
	अक्षर pbuf[128];

	अगर (pdev == शून्य)
		वापस;
	अगर (level > ql_errlev)
		वापस;

	ql_dbg_prefix(pbuf, ARRAY_SIZE(pbuf), शून्य, id);

	बहु_शुरू(va, fmt);

	vaf.fmt = fmt;
	vaf.va = &va;

	चयन (level) अणु
	हाल ql_log_fatal: /* FATAL LOG */
		pr_crit("%s%pV", pbuf, &vaf);
		अवरोध;
	हाल ql_log_warn:
		pr_err("%s%pV", pbuf, &vaf);
		अवरोध;
	हाल ql_log_info:
		pr_warn("%s%pV", pbuf, &vaf);
		अवरोध;
	शेष:
		pr_info("%s%pV", pbuf, &vaf);
		अवरोध;
	पूर्ण

	बहु_पूर्ण(va);
पूर्ण

व्योम
ql_dump_regs(uपूर्णांक level, scsi_qla_host_t *vha, uपूर्णांक id)
अणु
	पूर्णांक i;
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा device_reg_2xxx __iomem *reg = &ha->iobase->isp;
	काष्ठा device_reg_24xx __iomem *reg24 = &ha->iobase->isp24;
	काष्ठा device_reg_82xx __iomem *reg82 = &ha->iobase->isp82;
	__le16 __iomem *mbx_reg;

	अगर (!ql_mask_match(level))
		वापस;

	अगर (IS_P3P_TYPE(ha))
		mbx_reg = &reg82->mailbox_in[0];
	अन्यथा अगर (IS_FWI2_CAPABLE(ha))
		mbx_reg = &reg24->mailbox0;
	अन्यथा
		mbx_reg = MAILBOX_REG(ha, reg, 0);

	ql_dbg(level, vha, id, "Mailbox registers:\n");
	क्रम (i = 0; i < 6; i++, mbx_reg++)
		ql_dbg(level, vha, id,
		    "mbox[%d] %#04x\n", i, rd_reg_word(mbx_reg));
पूर्ण

व्योम
ql_dump_buffer(uपूर्णांक level, scsi_qla_host_t *vha, uपूर्णांक id, स्थिर व्योम *buf,
	       uपूर्णांक size)
अणु
	uपूर्णांक cnt;

	अगर (!ql_mask_match(level))
		वापस;

	ql_dbg(level, vha, id,
	    "%-+5d  0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F\n", size);
	ql_dbg(level, vha, id,
	    "----- -----------------------------------------------\n");
	क्रम (cnt = 0; cnt < size; cnt += 16) अणु
		ql_dbg(level, vha, id, "%04x: ", cnt);
		prपूर्णांक_hex_dump(KERN_CONT, "", DUMP_PREFIX_NONE, 16, 1,
			       buf + cnt, min(16U, size - cnt), false);
	पूर्ण
पूर्ण

/*
 * This function is क्रम क्रमmatting and logging log messages.
 * It is to be used when vha is available. It क्रमmats the message
 * and logs it to the messages file. All the messages will be logged
 * irrespective of value of ql2xextended_error_logging.
 * parameters:
 * level: The level of the log messages to be prपूर्णांकed in the
 *        messages file.
 * vha:   Poपूर्णांकer to the scsi_qla_host_t
 * id:    This is a unique id क्रम the level. It identअगरies the
 *        part of the code from where the message originated.
 * msg:   The message to be displayed.
 */
व्योम
ql_log_qp(uपूर्णांक32_t level, काष्ठा qla_qpair *qpair, पूर्णांक32_t id,
    स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची va;
	काष्ठा va_क्रमmat vaf;
	अक्षर pbuf[128];

	अगर (level > ql_errlev)
		वापस;

	ql_dbg_prefix(pbuf, ARRAY_SIZE(pbuf), qpair ? qpair->vha : शून्य, id);

	बहु_शुरू(va, fmt);

	vaf.fmt = fmt;
	vaf.va = &va;

	चयन (level) अणु
	हाल ql_log_fatal: /* FATAL LOG */
		pr_crit("%s%pV", pbuf, &vaf);
		अवरोध;
	हाल ql_log_warn:
		pr_err("%s%pV", pbuf, &vaf);
		अवरोध;
	हाल ql_log_info:
		pr_warn("%s%pV", pbuf, &vaf);
		अवरोध;
	शेष:
		pr_info("%s%pV", pbuf, &vaf);
		अवरोध;
	पूर्ण

	बहु_पूर्ण(va);
पूर्ण

/*
 * This function is क्रम क्रमmatting and logging debug inक्रमmation.
 * It is to be used when vha is available. It क्रमmats the message
 * and logs it to the messages file.
 * parameters:
 * level: The level of the debug messages to be prपूर्णांकed.
 *        If ql2xextended_error_logging value is correctly set,
 *        this message will appear in the messages file.
 * vha:   Poपूर्णांकer to the scsi_qla_host_t.
 * id:    This is a unique identअगरier क्रम the level. It identअगरies the
 *        part of the code from where the message originated.
 * msg:   The message to be displayed.
 */
व्योम
ql_dbg_qp(uपूर्णांक32_t level, काष्ठा qla_qpair *qpair, पूर्णांक32_t id,
    स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची va;
	काष्ठा va_क्रमmat vaf;
	अक्षर pbuf[128];

	अगर (!ql_mask_match(level))
		वापस;

	बहु_शुरू(va, fmt);

	vaf.fmt = fmt;
	vaf.va = &va;

	ql_dbg_prefix(pbuf, ARRAY_SIZE(pbuf), qpair ? qpair->vha : शून्य,
		      id + ql_dbg_offset);
	pr_warn("%s%pV", pbuf, &vaf);

	बहु_पूर्ण(va);

पूर्ण
