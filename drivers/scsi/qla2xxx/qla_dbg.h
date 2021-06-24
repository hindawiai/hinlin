<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * QLogic Fibre Channel HBA Driver
 * Copyright (c)  2003-2014 QLogic Corporation
 */

#समावेश "qla_def.h"

/*
 * Firmware Dump काष्ठाure definition
 */

काष्ठा qla2300_fw_dump अणु
	__be16 hccr;
	__be16 pbiu_reg[8];
	__be16 risc_host_reg[8];
	__be16 mailbox_reg[32];
	__be16 resp_dma_reg[32];
	__be16 dma_reg[48];
	__be16 risc_hdw_reg[16];
	__be16 risc_gp0_reg[16];
	__be16 risc_gp1_reg[16];
	__be16 risc_gp2_reg[16];
	__be16 risc_gp3_reg[16];
	__be16 risc_gp4_reg[16];
	__be16 risc_gp5_reg[16];
	__be16 risc_gp6_reg[16];
	__be16 risc_gp7_reg[16];
	__be16 frame_buf_hdw_reg[64];
	__be16 fpm_b0_reg[64];
	__be16 fpm_b1_reg[64];
	__be16 risc_ram[0xf800];
	__be16 stack_ram[0x1000];
	__be16 data_ram[1];
पूर्ण;

काष्ठा qla2100_fw_dump अणु
	__be16 hccr;
	__be16 pbiu_reg[8];
	__be16 mailbox_reg[32];
	__be16 dma_reg[48];
	__be16 risc_hdw_reg[16];
	__be16 risc_gp0_reg[16];
	__be16 risc_gp1_reg[16];
	__be16 risc_gp2_reg[16];
	__be16 risc_gp3_reg[16];
	__be16 risc_gp4_reg[16];
	__be16 risc_gp5_reg[16];
	__be16 risc_gp6_reg[16];
	__be16 risc_gp7_reg[16];
	__be16 frame_buf_hdw_reg[16];
	__be16 fpm_b0_reg[64];
	__be16 fpm_b1_reg[64];
	__be16 risc_ram[0xf000];
	u8	queue_dump[];
पूर्ण;

काष्ठा qla24xx_fw_dump अणु
	__be32	host_status;
	__be32	host_reg[32];
	__be32	shaकरोw_reg[7];
	__be16	mailbox_reg[32];
	__be32	xseq_gp_reg[128];
	__be32	xseq_0_reg[16];
	__be32	xseq_1_reg[16];
	__be32	rseq_gp_reg[128];
	__be32	rseq_0_reg[16];
	__be32	rseq_1_reg[16];
	__be32	rseq_2_reg[16];
	__be32	cmd_dma_reg[16];
	__be32	req0_dma_reg[15];
	__be32	resp0_dma_reg[15];
	__be32	req1_dma_reg[15];
	__be32	xmt0_dma_reg[32];
	__be32	xmt1_dma_reg[32];
	__be32	xmt2_dma_reg[32];
	__be32	xmt3_dma_reg[32];
	__be32	xmt4_dma_reg[32];
	__be32	xmt_data_dma_reg[16];
	__be32	rcvt0_data_dma_reg[32];
	__be32	rcvt1_data_dma_reg[32];
	__be32	risc_gp_reg[128];
	__be32	lmc_reg[112];
	__be32	fpm_hdw_reg[192];
	__be32	fb_hdw_reg[176];
	__be32	code_ram[0x2000];
	__be32	ext_mem[1];
पूर्ण;

काष्ठा qla25xx_fw_dump अणु
	__be32	host_status;
	__be32	host_risc_reg[32];
	__be32	pcie_regs[4];
	__be32	host_reg[32];
	__be32	shaकरोw_reg[11];
	__be32	risc_io_reg;
	__be16	mailbox_reg[32];
	__be32	xseq_gp_reg[128];
	__be32	xseq_0_reg[48];
	__be32	xseq_1_reg[16];
	__be32	rseq_gp_reg[128];
	__be32	rseq_0_reg[32];
	__be32	rseq_1_reg[16];
	__be32	rseq_2_reg[16];
	__be32	aseq_gp_reg[128];
	__be32	aseq_0_reg[32];
	__be32	aseq_1_reg[16];
	__be32	aseq_2_reg[16];
	__be32	cmd_dma_reg[16];
	__be32	req0_dma_reg[15];
	__be32	resp0_dma_reg[15];
	__be32	req1_dma_reg[15];
	__be32	xmt0_dma_reg[32];
	__be32	xmt1_dma_reg[32];
	__be32	xmt2_dma_reg[32];
	__be32	xmt3_dma_reg[32];
	__be32	xmt4_dma_reg[32];
	__be32	xmt_data_dma_reg[16];
	__be32	rcvt0_data_dma_reg[32];
	__be32	rcvt1_data_dma_reg[32];
	__be32	risc_gp_reg[128];
	__be32	lmc_reg[128];
	__be32	fpm_hdw_reg[192];
	__be32	fb_hdw_reg[192];
	__be32	code_ram[0x2000];
	__be32	ext_mem[1];
पूर्ण;

काष्ठा qla81xx_fw_dump अणु
	__be32	host_status;
	__be32	host_risc_reg[32];
	__be32	pcie_regs[4];
	__be32	host_reg[32];
	__be32	shaकरोw_reg[11];
	__be32	risc_io_reg;
	__be16	mailbox_reg[32];
	__be32	xseq_gp_reg[128];
	__be32	xseq_0_reg[48];
	__be32	xseq_1_reg[16];
	__be32	rseq_gp_reg[128];
	__be32	rseq_0_reg[32];
	__be32	rseq_1_reg[16];
	__be32	rseq_2_reg[16];
	__be32	aseq_gp_reg[128];
	__be32	aseq_0_reg[32];
	__be32	aseq_1_reg[16];
	__be32	aseq_2_reg[16];
	__be32	cmd_dma_reg[16];
	__be32	req0_dma_reg[15];
	__be32	resp0_dma_reg[15];
	__be32	req1_dma_reg[15];
	__be32	xmt0_dma_reg[32];
	__be32	xmt1_dma_reg[32];
	__be32	xmt2_dma_reg[32];
	__be32	xmt3_dma_reg[32];
	__be32	xmt4_dma_reg[32];
	__be32	xmt_data_dma_reg[16];
	__be32	rcvt0_data_dma_reg[32];
	__be32	rcvt1_data_dma_reg[32];
	__be32	risc_gp_reg[128];
	__be32	lmc_reg[128];
	__be32	fpm_hdw_reg[224];
	__be32	fb_hdw_reg[208];
	__be32	code_ram[0x2000];
	__be32	ext_mem[1];
पूर्ण;

काष्ठा qla83xx_fw_dump अणु
	__be32	host_status;
	__be32	host_risc_reg[48];
	__be32	pcie_regs[4];
	__be32	host_reg[32];
	__be32	shaकरोw_reg[11];
	__be32	risc_io_reg;
	__be16	mailbox_reg[32];
	__be32	xseq_gp_reg[256];
	__be32	xseq_0_reg[48];
	__be32	xseq_1_reg[16];
	__be32	xseq_2_reg[16];
	__be32	rseq_gp_reg[256];
	__be32	rseq_0_reg[32];
	__be32	rseq_1_reg[16];
	__be32	rseq_2_reg[16];
	__be32	rseq_3_reg[16];
	__be32	aseq_gp_reg[256];
	__be32	aseq_0_reg[32];
	__be32	aseq_1_reg[16];
	__be32	aseq_2_reg[16];
	__be32	aseq_3_reg[16];
	__be32	cmd_dma_reg[64];
	__be32	req0_dma_reg[15];
	__be32	resp0_dma_reg[15];
	__be32	req1_dma_reg[15];
	__be32	xmt0_dma_reg[32];
	__be32	xmt1_dma_reg[32];
	__be32	xmt2_dma_reg[32];
	__be32	xmt3_dma_reg[32];
	__be32	xmt4_dma_reg[32];
	__be32	xmt_data_dma_reg[16];
	__be32	rcvt0_data_dma_reg[32];
	__be32	rcvt1_data_dma_reg[32];
	__be32	risc_gp_reg[128];
	__be32	lmc_reg[128];
	__be32	fpm_hdw_reg[256];
	__be32	rq0_array_reg[256];
	__be32	rq1_array_reg[256];
	__be32	rp0_array_reg[256];
	__be32	rp1_array_reg[256];
	__be32	queue_control_reg[16];
	__be32	fb_hdw_reg[432];
	__be32	at0_array_reg[128];
	__be32	code_ram[0x2400];
	__be32	ext_mem[1];
पूर्ण;

#घोषणा EFT_NUM_BUFFERS		4
#घोषणा EFT_BYTES_PER_BUFFER	0x4000
#घोषणा EFT_SIZE		((EFT_BYTES_PER_BUFFER) * (EFT_NUM_BUFFERS))

#घोषणा FCE_NUM_BUFFERS		64
#घोषणा FCE_BYTES_PER_BUFFER	0x400
#घोषणा FCE_SIZE		((FCE_BYTES_PER_BUFFER) * (FCE_NUM_BUFFERS))
#घोषणा fce_calc_size(b)	((FCE_BYTES_PER_BUFFER) * (b))

काष्ठा qla2xxx_fce_chain अणु
	__be32	type;
	__be32	chain_size;

	__be32	size;
	__be32	addr_l;
	__be32	addr_h;
	__be32	eregs[8];
पूर्ण;

/* used by exchange off load and extended login offload */
काष्ठा qla2xxx_offld_chain अणु
	__be32	type;
	__be32	chain_size;

	__be32	size;
	__be32	reserved;
	__be64	addr;
पूर्ण;

काष्ठा qla2xxx_mq_chain अणु
	__be32	type;
	__be32	chain_size;

	__be32	count;
	__be32	qregs[4 * QLA_MQ_SIZE];
पूर्ण;

काष्ठा qla2xxx_mqueue_header अणु
	__be32	queue;
#घोषणा TYPE_REQUEST_QUEUE	0x1
#घोषणा TYPE_RESPONSE_QUEUE	0x2
#घोषणा TYPE_ATIO_QUEUE		0x3
	__be32	number;
	__be32	size;
पूर्ण;

काष्ठा qla2xxx_mqueue_chain अणु
	__be32	type;
	__be32	chain_size;
पूर्ण;

#घोषणा DUMP_CHAIN_VARIANT	0x80000000
#घोषणा DUMP_CHAIN_FCE		0x7FFFFAF0
#घोषणा DUMP_CHAIN_MQ		0x7FFFFAF1
#घोषणा DUMP_CHAIN_QUEUE	0x7FFFFAF2
#घोषणा DUMP_CHAIN_EXLOGIN	0x7FFFFAF3
#घोषणा DUMP_CHAIN_EXCHG	0x7FFFFAF4
#घोषणा DUMP_CHAIN_LAST		0x80000000

काष्ठा qla2xxx_fw_dump अणु
	uपूर्णांक8_t signature[4];
	__be32	version;

	__be32 fw_major_version;
	__be32 fw_minor_version;
	__be32 fw_subminor_version;
	__be32 fw_attributes;

	__be32 venकरोr;
	__be32 device;
	__be32 subप्रणाली_venकरोr;
	__be32 subप्रणाली_device;

	__be32	fixed_size;
	__be32	mem_size;
	__be32	req_q_size;
	__be32	rsp_q_size;

	__be32	eft_size;
	__be32	eft_addr_l;
	__be32	eft_addr_h;

	__be32	header_size;

	जोड़ अणु
		काष्ठा qla2100_fw_dump isp21;
		काष्ठा qla2300_fw_dump isp23;
		काष्ठा qla24xx_fw_dump isp24;
		काष्ठा qla25xx_fw_dump isp25;
		काष्ठा qla81xx_fw_dump isp81;
		काष्ठा qla83xx_fw_dump isp83;
	पूर्ण isp;
पूर्ण;

#घोषणा QL_MSGHDR "qla2xxx"
#घोषणा QL_DBG_DEFAULT1_MASK    0x1e600000

#घोषणा ql_log_fatal		0 /* display fatal errors */
#घोषणा ql_log_warn		1 /* display critical errors */
#घोषणा ql_log_info		2 /* display all recovered errors */
#घोषणा ql_log_all		3 /* This value is only used by ql_errlev.
				   * No messages will use this value.
				   * This should be always highest value
				   * as compared to other log levels.
				   */

बाह्य uपूर्णांक ql_errlev;

व्योम __attribute__((क्रमmat (म_लिखो, 4, 5)))
ql_dbg(uपूर्णांक, scsi_qla_host_t *vha, uपूर्णांक, स्थिर अक्षर *fmt, ...);
व्योम __attribute__((क्रमmat (म_लिखो, 4, 5)))
ql_dbg_pci(uपूर्णांक, काष्ठा pci_dev *pdev, uपूर्णांक, स्थिर अक्षर *fmt, ...);
व्योम __attribute__((क्रमmat (म_लिखो, 4, 5)))
ql_dbg_qp(uपूर्णांक32_t, काष्ठा qla_qpair *, पूर्णांक32_t, स्थिर अक्षर *fmt, ...);


व्योम __attribute__((क्रमmat (म_लिखो, 4, 5)))
ql_log(uपूर्णांक, scsi_qla_host_t *vha, uपूर्णांक, स्थिर अक्षर *fmt, ...);
व्योम __attribute__((क्रमmat (म_लिखो, 4, 5)))
ql_log_pci(uपूर्णांक, काष्ठा pci_dev *pdev, uपूर्णांक, स्थिर अक्षर *fmt, ...);

व्योम __attribute__((क्रमmat (म_लिखो, 4, 5)))
ql_log_qp(uपूर्णांक32_t, काष्ठा qla_qpair *, पूर्णांक32_t, स्थिर अक्षर *fmt, ...);

/* Debug Levels */
/* The 0x40000000 is the max value any debug level can have
 * as ql2xextended_error_logging is of type चिन्हित पूर्णांक
 */
#घोषणा ql_dbg_init	0x40000000 /* Init Debug */
#घोषणा ql_dbg_mbx	0x20000000 /* MBX Debug */
#घोषणा ql_dbg_disc	0x10000000 /* Device Discovery Debug */
#घोषणा ql_dbg_io	0x08000000 /* IO Tracing Debug */
#घोषणा ql_dbg_dpc	0x04000000 /* DPC Thead Debug */
#घोषणा ql_dbg_async	0x02000000 /* Async events Debug */
#घोषणा ql_dbg_समयr	0x01000000 /* Timer Debug */
#घोषणा ql_dbg_user	0x00800000 /* User Space Interations Debug */
#घोषणा ql_dbg_taskm	0x00400000 /* Task Management Debug */
#घोषणा ql_dbg_aer	0x00200000 /* AER/EEH Debug */
#घोषणा ql_dbg_multiq	0x00100000 /* MultiQ Debug */
#घोषणा ql_dbg_p3p	0x00080000 /* P3P specअगरic Debug */
#घोषणा ql_dbg_vport	0x00040000 /* Virtual Port Debug */
#घोषणा ql_dbg_buffer	0x00020000 /* For dumping the buffer/regs */
#घोषणा ql_dbg_misc	0x00010000 /* For dumping everything that is not
				    * not covered by upper categories
				    */
#घोषणा ql_dbg_verbose	0x00008000 /* More verbosity क्रम each level
				    * This is to be used with other levels where
				    * more verbosity is required. It might not
				    * be applicable to all the levels.
				    */
#घोषणा ql_dbg_tgt	0x00004000 /* Target mode */
#घोषणा ql_dbg_tgt_mgt	0x00002000 /* Target mode management */
#घोषणा ql_dbg_tgt_पंचांगr	0x00001000 /* Target mode task management */
#घोषणा ql_dbg_tgt_dअगर  0x00000800 /* Target mode dअगर */

बाह्य पूर्णांक qla27xx_dump_mpi_ram(काष्ठा qla_hw_data *, uपूर्णांक32_t, uपूर्णांक32_t *,
	uपूर्णांक32_t, व्योम **);
बाह्य पूर्णांक qla24xx_dump_ram(काष्ठा qla_hw_data *, uपूर्णांक32_t, __be32 *,
	uपूर्णांक32_t, व्योम **);
बाह्य व्योम qla24xx_छोड़ो_risc(काष्ठा device_reg_24xx __iomem *,
	काष्ठा qla_hw_data *);
बाह्य पूर्णांक qla24xx_soft_reset(काष्ठा qla_hw_data *);

अटल अंतरभूत पूर्णांक
ql_mask_match(uपूर्णांक level)
अणु
	अगर (ql2xextended_error_logging == 1)
		ql2xextended_error_logging = QL_DBG_DEFAULT1_MASK;

	वापस (level & ql2xextended_error_logging) == level;
पूर्ण
