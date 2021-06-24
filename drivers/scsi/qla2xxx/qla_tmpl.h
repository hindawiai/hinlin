<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * QLogic Fibre Channel HBA Driver
 * Copyright (c)  2003-2014 QLogic Corporation
 */

#अगर_अघोषित __QLA_DMP27_H__
#घोषणा	__QLA_DMP27_H__

#घोषणा IOBASE_ADDR	दुरत्व(काष्ठा device_reg_24xx, iobase_addr)

काष्ठा __packed qla27xx_fwdt_ढाँचा अणु
	__le32 ढाँचा_type;
	__le32 entry_offset;
	__le32 ढाँचा_size;
	uपूर्णांक32_t count;		/* borrow field क्रम running/residual count */

	__le32 entry_count;
	uपूर्णांक32_t ढाँचा_version;
	__le32 capture_बारtamp;
	uपूर्णांक32_t ढाँचा_checksum;

	uपूर्णांक32_t reserved_2;
	__le32 driver_info[3];

	uपूर्णांक32_t saved_state[16];

	uपूर्णांक32_t reserved_3[8];
	__le32 firmware_version[5];
पूर्ण;

#घोषणा TEMPLATE_TYPE_FWDUMP		99

#घोषणा ENTRY_TYPE_NOP			0
#घोषणा ENTRY_TYPE_TMP_END		255
#घोषणा ENTRY_TYPE_RD_IOB_T1		256
#घोषणा ENTRY_TYPE_WR_IOB_T1		257
#घोषणा ENTRY_TYPE_RD_IOB_T2		258
#घोषणा ENTRY_TYPE_WR_IOB_T2		259
#घोषणा ENTRY_TYPE_RD_PCI		260
#घोषणा ENTRY_TYPE_WR_PCI		261
#घोषणा ENTRY_TYPE_RD_RAM		262
#घोषणा ENTRY_TYPE_GET_QUEUE		263
#घोषणा ENTRY_TYPE_GET_FCE		264
#घोषणा ENTRY_TYPE_PSE_RISC		265
#घोषणा ENTRY_TYPE_RST_RISC		266
#घोषणा ENTRY_TYPE_DIS_INTR		267
#घोषणा ENTRY_TYPE_GET_HBUF		268
#घोषणा ENTRY_TYPE_SCRATCH		269
#घोषणा ENTRY_TYPE_RDREMREG		270
#घोषणा ENTRY_TYPE_WRREMREG		271
#घोषणा ENTRY_TYPE_RDREMRAM		272
#घोषणा ENTRY_TYPE_PCICFG		273
#घोषणा ENTRY_TYPE_GET_SHADOW		274
#घोषणा ENTRY_TYPE_WRITE_BUF		275
#घोषणा ENTRY_TYPE_CONDITIONAL		276
#घोषणा ENTRY_TYPE_RDPEPREG		277
#घोषणा ENTRY_TYPE_WRPEPREG		278

#घोषणा CAPTURE_FLAG_PHYS_ONLY		BIT_0
#घोषणा CAPTURE_FLAG_PHYS_VIRT		BIT_1

#घोषणा DRIVER_FLAG_SKIP_ENTRY		BIT_7

काष्ठा __packed qla27xx_fwdt_entry अणु
	काष्ठा __packed अणु
		__le32 type;
		__le32 size;
		uपूर्णांक32_t reserved_1;

		uपूर्णांक8_t  capture_flags;
		uपूर्णांक8_t  reserved_2[2];
		uपूर्णांक8_t  driver_flags;
	पूर्ण hdr;
	जोड़ __packed अणु
		काष्ठा __packed अणु
		पूर्ण t0;

		काष्ठा __packed अणु
		पूर्ण t255;

		काष्ठा __packed अणु
			__le32 base_addr;
			uपूर्णांक8_t  reg_width;
			__le16 reg_count;
			uपूर्णांक8_t  pci_offset;
		पूर्ण t256;

		काष्ठा __packed अणु
			__le32 base_addr;
			__le32 ग_लिखो_data;
			uपूर्णांक8_t  pci_offset;
			uपूर्णांक8_t  reserved[3];
		पूर्ण t257;

		काष्ठा __packed अणु
			__le32 base_addr;
			uपूर्णांक8_t  reg_width;
			__le16 reg_count;
			uपूर्णांक8_t  pci_offset;
			uपूर्णांक8_t  banksel_offset;
			uपूर्णांक8_t  reserved[3];
			__le32 bank;
		पूर्ण t258;

		काष्ठा __packed अणु
			__le32 base_addr;
			__le32 ग_लिखो_data;
			uपूर्णांक8_t  reserved[2];
			uपूर्णांक8_t  pci_offset;
			uपूर्णांक8_t  banksel_offset;
			__le32 bank;
		पूर्ण t259;

		काष्ठा __packed अणु
			uपूर्णांक8_t pci_offset;
			uपूर्णांक8_t reserved[3];
		पूर्ण t260;

		काष्ठा __packed अणु
			uपूर्णांक8_t pci_offset;
			uपूर्णांक8_t reserved[3];
			__le32 ग_लिखो_data;
		पूर्ण t261;

		काष्ठा __packed अणु
			uपूर्णांक8_t  ram_area;
			uपूर्णांक8_t  reserved[3];
			__le32 start_addr;
			__le32 end_addr;
		पूर्ण t262;

		काष्ठा __packed अणु
			uपूर्णांक32_t num_queues;
			uपूर्णांक8_t  queue_type;
			uपूर्णांक8_t  reserved[3];
		पूर्ण t263;

		काष्ठा __packed अणु
			uपूर्णांक32_t fce_trace_size;
			uपूर्णांक64_t ग_लिखो_poपूर्णांकer;
			uपूर्णांक64_t base_poपूर्णांकer;
			uपूर्णांक32_t fce_enable_mb0;
			uपूर्णांक32_t fce_enable_mb2;
			uपूर्णांक32_t fce_enable_mb3;
			uपूर्णांक32_t fce_enable_mb4;
			uपूर्णांक32_t fce_enable_mb5;
			uपूर्णांक32_t fce_enable_mb6;
		पूर्ण t264;

		काष्ठा __packed अणु
		पूर्ण t265;

		काष्ठा __packed अणु
		पूर्ण t266;

		काष्ठा __packed अणु
			uपूर्णांक8_t  pci_offset;
			uपूर्णांक8_t  reserved[3];
			__le32 data;
		पूर्ण t267;

		काष्ठा __packed अणु
			uपूर्णांक8_t  buf_type;
			uपूर्णांक8_t  reserved[3];
			uपूर्णांक32_t buf_size;
			uपूर्णांक64_t start_addr;
		पूर्ण t268;

		काष्ठा __packed अणु
			uपूर्णांक32_t scratch_size;
		पूर्ण t269;

		काष्ठा __packed अणु
			__le32 addr;
			__le32 count;
		पूर्ण t270;

		काष्ठा __packed अणु
			__le32 addr;
			__le32 data;
		पूर्ण t271;

		काष्ठा __packed अणु
			__le32 addr;
			__le32 count;
		पूर्ण t272;

		काष्ठा __packed अणु
			__le32 addr;
			__le32 count;
		पूर्ण t273;

		काष्ठा __packed अणु
			uपूर्णांक32_t num_queues;
			uपूर्णांक8_t  queue_type;
			uपूर्णांक8_t  reserved[3];
		पूर्ण t274;

		काष्ठा __packed अणु
			__le32 length;
			uपूर्णांक8_t  buffer[];
		पूर्ण t275;

		काष्ठा __packed अणु
			__le32 cond1;
			__le32 cond2;
		पूर्ण t276;

		काष्ठा __packed अणु
			__le32 cmd_addr;
			__le32 wr_cmd_data;
			__le32 data_addr;
		पूर्ण t277;

		काष्ठा __packed अणु
			__le32 cmd_addr;
			__le32 wr_cmd_data;
			__le32 data_addr;
			__le32 wr_data;
		पूर्ण t278;
	पूर्ण;
पूर्ण;

#घोषणा T262_RAM_AREA_CRITICAL_RAM	1
#घोषणा T262_RAM_AREA_EXTERNAL_RAM	2
#घोषणा T262_RAM_AREA_SHARED_RAM	3
#घोषणा T262_RAM_AREA_DDR_RAM		4
#घोषणा T262_RAM_AREA_MISC		5

#घोषणा T263_QUEUE_TYPE_REQ		1
#घोषणा T263_QUEUE_TYPE_RSP		2
#घोषणा T263_QUEUE_TYPE_ATIO		3

#घोषणा T268_BUF_TYPE_EXTD_TRACE	1
#घोषणा T268_BUF_TYPE_EXCH_BUFOFF	2
#घोषणा T268_BUF_TYPE_EXTD_LOGIN	3
#घोषणा T268_BUF_TYPE_REQ_MIRROR	4
#घोषणा T268_BUF_TYPE_RSP_MIRROR	5

#घोषणा T274_QUEUE_TYPE_REQ_SHAD	1
#घोषणा T274_QUEUE_TYPE_RSP_SHAD	2
#घोषणा T274_QUEUE_TYPE_ATIO_SHAD	3

#पूर्ण_अगर
