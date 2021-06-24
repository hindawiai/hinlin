<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Low-level API क्रम mac80211 ST-Ericsson CW1200 drivers
 *
 * Copyright (c) 2010, ST-Ericsson
 * Author: Dmitry Tarnyagin <dmitry.tarnyagin@lockless.no>
 *
 * Based on:
 * ST-Ericsson UMAC CW1200 driver which is
 * Copyright (c) 2010, ST-Ericsson
 * Author: Ajitpal Singh <ajitpal.singh@stericsson.com>
 */

#अगर_अघोषित CW1200_HWIO_H_INCLUDED
#घोषणा CW1200_HWIO_H_INCLUDED

/* बाह्य */ काष्ठा cw1200_common;

#घोषणा CW1200_CUT_11_ID_STR		(0x302E3830)
#घोषणा CW1200_CUT_22_ID_STR1		(0x302e3132)
#घोषणा CW1200_CUT_22_ID_STR2		(0x32302e30)
#घोषणा CW1200_CUT_22_ID_STR3		(0x3335)
#घोषणा CW1200_CUT_ID_ADDR		(0xFFF17F90)
#घोषणा CW1200_CUT2_ID_ADDR		(0xFFF1FF90)

/* Download control area */
/* boot loader start address in SRAM */
#घोषणा DOWNLOAD_BOOT_LOADER_OFFSET	(0x00000000)
/* 32K, 0x4000 to 0xDFFF */
#घोषणा DOWNLOAD_FIFO_OFFSET		(0x00004000)
/* 32K */
#घोषणा DOWNLOAD_FIFO_SIZE		(0x00008000)
/* 128 bytes, 0xFF80 to 0xFFFF */
#घोषणा DOWNLOAD_CTRL_OFFSET		(0x0000FF80)
#घोषणा DOWNLOAD_CTRL_DATA_DWORDS	(32-6)

काष्ठा करोwnload_cntl_t अणु
	/* size of whole firmware file (including Cheksum), host init */
	u32 image_size;
	/* करोwnloading flags */
	u32 flags;
	/* No. of bytes put पूर्णांकo the करोwnload, init & updated by host */
	u32 put;
	/* last traced program counter, last ARM reg_pc */
	u32 trace_pc;
	/* No. of bytes पढ़ो from the करोwnload, host init, device updates */
	u32 get;
	/* r0, boot losader status, host init to pending, device updates */
	u32 status;
	/* Extra debug info, r1 to r14 अगर status=r0=DOWNLOAD_EXCEPTION */
	u32 debug_data[DOWNLOAD_CTRL_DATA_DWORDS];
पूर्ण;

#घोषणा	DOWNLOAD_IMAGE_SIZE_REG		\
	(DOWNLOAD_CTRL_OFFSET + दुरत्व(काष्ठा करोwnload_cntl_t, image_size))
#घोषणा	DOWNLOAD_FLAGS_REG		\
	(DOWNLOAD_CTRL_OFFSET + दुरत्व(काष्ठा करोwnload_cntl_t, flags))
#घोषणा DOWNLOAD_PUT_REG		\
	(DOWNLOAD_CTRL_OFFSET + दुरत्व(काष्ठा करोwnload_cntl_t, put))
#घोषणा DOWNLOAD_TRACE_PC_REG		\
	(DOWNLOAD_CTRL_OFFSET + दुरत्व(काष्ठा करोwnload_cntl_t, trace_pc))
#घोषणा	DOWNLOAD_GET_REG		\
	(DOWNLOAD_CTRL_OFFSET + दुरत्व(काष्ठा करोwnload_cntl_t, get))
#घोषणा	DOWNLOAD_STATUS_REG		\
	(DOWNLOAD_CTRL_OFFSET + दुरत्व(काष्ठा करोwnload_cntl_t, status))
#घोषणा DOWNLOAD_DEBUG_DATA_REG		\
	(DOWNLOAD_CTRL_OFFSET + दुरत्व(काष्ठा करोwnload_cntl_t, debug_data))
#घोषणा DOWNLOAD_DEBUG_DATA_LEN		(108)

#घोषणा DOWNLOAD_BLOCK_SIZE		(1024)

/* For boot loader detection */
#घोषणा DOWNLOAD_ARE_YOU_HERE		(0x87654321)
#घोषणा DOWNLOAD_I_AM_HERE		(0x12345678)

/* Download error code */
#घोषणा DOWNLOAD_PENDING		(0xFFFFFFFF)
#घोषणा DOWNLOAD_SUCCESS		(0)
#घोषणा DOWNLOAD_EXCEPTION		(1)
#घोषणा DOWNLOAD_ERR_MEM_1		(2)
#घोषणा DOWNLOAD_ERR_MEM_2		(3)
#घोषणा DOWNLOAD_ERR_SOFTWARE		(4)
#घोषणा DOWNLOAD_ERR_खाता_SIZE		(5)
#घोषणा DOWNLOAD_ERR_CHECKSUM		(6)
#घोषणा DOWNLOAD_ERR_OVERFLOW		(7)
#घोषणा DOWNLOAD_ERR_IMAGE		(8)
#घोषणा DOWNLOAD_ERR_HOST		(9)
#घोषणा DOWNLOAD_ERR_ABORT		(10)


#घोषणा SYS_BASE_ADDR_SILICON		(0)
#घोषणा PAC_BASE_ADDRESS_SILICON	(SYS_BASE_ADDR_SILICON + 0x09000000)
#घोषणा PAC_SHARED_MEMORY_SILICON	(PAC_BASE_ADDRESS_SILICON)

#घोषणा CW1200_APB(addr)		(PAC_SHARED_MEMORY_SILICON + (addr))

/* Device रेजिस्टर definitions */

/* WBF - SPI Register Addresses */
#घोषणा ST90TDS_ADDR_ID_BASE		(0x0000)
/* 16/32 bits */
#घोषणा ST90TDS_CONFIG_REG_ID		(0x0000)
/* 16/32 bits */
#घोषणा ST90TDS_CONTROL_REG_ID		(0x0001)
/* 16 bits, Q mode W/R */
#घोषणा ST90TDS_IN_OUT_QUEUE_REG_ID	(0x0002)
/* 32 bits, AHB bus R/W */
#घोषणा ST90TDS_AHB_DPORT_REG_ID	(0x0003)
/* 16/32 bits */
#घोषणा ST90TDS_SRAM_BASE_ADDR_REG_ID   (0x0004)
/* 32 bits, APB bus R/W */
#घोषणा ST90TDS_SRAM_DPORT_REG_ID	(0x0005)
/* 32 bits, t_settle/general */
#घोषणा ST90TDS_TSET_GEN_R_W_REG_ID	(0x0006)
/* 16 bits, Q mode पढ़ो, no length */
#घोषणा ST90TDS_FRAME_OUT_REG_ID	(0x0007)
#घोषणा ST90TDS_ADDR_ID_MAX		(ST90TDS_FRAME_OUT_REG_ID)

/* WBF - Control रेजिस्टर bit set */
/* next o/p length, bit 11 to 0 */
#घोषणा ST90TDS_CONT_NEXT_LEN_MASK	(0x0FFF)
#घोषणा ST90TDS_CONT_WUP_BIT		(BIT(12))
#घोषणा ST90TDS_CONT_RDY_BIT		(BIT(13))
#घोषणा ST90TDS_CONT_IRQ_ENABLE		(BIT(14))
#घोषणा ST90TDS_CONT_RDY_ENABLE		(BIT(15))
#घोषणा ST90TDS_CONT_IRQ_RDY_ENABLE	(BIT(14)|BIT(15))

/* SPI Config रेजिस्टर bit set */
#घोषणा ST90TDS_CONFIG_FRAME_BIT	(BIT(2))
#घोषणा ST90TDS_CONFIG_WORD_MODE_BITS	(BIT(3)|BIT(4))
#घोषणा ST90TDS_CONFIG_WORD_MODE_1	(BIT(3))
#घोषणा ST90TDS_CONFIG_WORD_MODE_2	(BIT(4))
#घोषणा ST90TDS_CONFIG_ERROR_0_BIT	(BIT(5))
#घोषणा ST90TDS_CONFIG_ERROR_1_BIT	(BIT(6))
#घोषणा ST90TDS_CONFIG_ERROR_2_BIT	(BIT(7))
/* TBD: Sure??? */
#घोषणा ST90TDS_CONFIG_CSN_FRAME_BIT	(BIT(7))
#घोषणा ST90TDS_CONFIG_ERROR_3_BIT	(BIT(8))
#घोषणा ST90TDS_CONFIG_ERROR_4_BIT	(BIT(9))
/* QueueM */
#घोषणा ST90TDS_CONFIG_ACCESS_MODE_BIT	(BIT(10))
/* AHB bus */
#घोषणा ST90TDS_CONFIG_AHB_PRFETCH_BIT	(BIT(11))
#घोषणा ST90TDS_CONFIG_CPU_CLK_DIS_BIT	(BIT(12))
/* APB bus */
#घोषणा ST90TDS_CONFIG_PRFETCH_BIT	(BIT(13))
/* cpu reset */
#घोषणा ST90TDS_CONFIG_CPU_RESET_BIT	(BIT(14))
#घोषणा ST90TDS_CONFIG_CLEAR_INT_BIT	(BIT(15))

/* For CW1200 the IRQ Enable and Ready Bits are in CONFIG रेजिस्टर */
#घोषणा ST90TDS_CONF_IRQ_ENABLE		(BIT(16))
#घोषणा ST90TDS_CONF_RDY_ENABLE		(BIT(17))
#घोषणा ST90TDS_CONF_IRQ_RDY_ENABLE	(BIT(16)|BIT(17))

पूर्णांक cw1200_data_पढ़ो(काष्ठा cw1200_common *priv,
		     व्योम *buf, माप_प्रकार buf_len);
पूर्णांक cw1200_data_ग_लिखो(काष्ठा cw1200_common *priv,
		      स्थिर व्योम *buf, माप_प्रकार buf_len);

पूर्णांक cw1200_reg_पढ़ो(काष्ठा cw1200_common *priv, u16 addr,
		    व्योम *buf, माप_प्रकार buf_len);
पूर्णांक cw1200_reg_ग_लिखो(काष्ठा cw1200_common *priv, u16 addr,
		     स्थिर व्योम *buf, माप_प्रकार buf_len);

अटल अंतरभूत पूर्णांक cw1200_reg_पढ़ो_16(काष्ठा cw1200_common *priv,
				     u16 addr, u16 *val)
अणु
	__le32 पंचांगp;
	पूर्णांक i;
	i = cw1200_reg_पढ़ो(priv, addr, &पंचांगp, माप(पंचांगp));
	*val = le32_to_cpu(पंचांगp) & 0xfffff;
	वापस i;
पूर्ण

अटल अंतरभूत पूर्णांक cw1200_reg_ग_लिखो_16(काष्ठा cw1200_common *priv,
				      u16 addr, u16 val)
अणु
	__le32 पंचांगp = cpu_to_le32((u32)val);
	वापस cw1200_reg_ग_लिखो(priv, addr, &पंचांगp, माप(पंचांगp));
पूर्ण

अटल अंतरभूत पूर्णांक cw1200_reg_पढ़ो_32(काष्ठा cw1200_common *priv,
				     u16 addr, u32 *val)
अणु
	__le32 पंचांगp;
	पूर्णांक i = cw1200_reg_पढ़ो(priv, addr, &पंचांगp, माप(पंचांगp));
	*val = le32_to_cpu(पंचांगp);
	वापस i;
पूर्ण

अटल अंतरभूत पूर्णांक cw1200_reg_ग_लिखो_32(काष्ठा cw1200_common *priv,
				      u16 addr, u32 val)
अणु
	__le32 पंचांगp = cpu_to_le32(val);
	वापस cw1200_reg_ग_लिखो(priv, addr, &पंचांगp, माप(val));
पूर्ण

पूर्णांक cw1200_indirect_पढ़ो(काष्ठा cw1200_common *priv, u32 addr, व्योम *buf,
			 माप_प्रकार buf_len, u32 prefetch, u16 port_addr);
पूर्णांक cw1200_apb_ग_लिखो(काष्ठा cw1200_common *priv, u32 addr, स्थिर व्योम *buf,
		     माप_प्रकार buf_len);

अटल अंतरभूत पूर्णांक cw1200_apb_पढ़ो(काष्ठा cw1200_common *priv, u32 addr,
				  व्योम *buf, माप_प्रकार buf_len)
अणु
	वापस cw1200_indirect_पढ़ो(priv, addr, buf, buf_len,
				    ST90TDS_CONFIG_PRFETCH_BIT,
				    ST90TDS_SRAM_DPORT_REG_ID);
पूर्ण

अटल अंतरभूत पूर्णांक cw1200_ahb_पढ़ो(काष्ठा cw1200_common *priv, u32 addr,
				  व्योम *buf, माप_प्रकार buf_len)
अणु
	वापस cw1200_indirect_पढ़ो(priv, addr, buf, buf_len,
				    ST90TDS_CONFIG_AHB_PRFETCH_BIT,
				    ST90TDS_AHB_DPORT_REG_ID);
पूर्ण

अटल अंतरभूत पूर्णांक cw1200_apb_पढ़ो_32(काष्ठा cw1200_common *priv,
				     u32 addr, u32 *val)
अणु
	__le32 पंचांगp;
	पूर्णांक i = cw1200_apb_पढ़ो(priv, addr, &पंचांगp, माप(पंचांगp));
	*val = le32_to_cpu(पंचांगp);
	वापस i;
पूर्ण

अटल अंतरभूत पूर्णांक cw1200_apb_ग_लिखो_32(काष्ठा cw1200_common *priv,
				      u32 addr, u32 val)
अणु
	__le32 पंचांगp = cpu_to_le32(val);
	वापस cw1200_apb_ग_लिखो(priv, addr, &पंचांगp, माप(val));
पूर्ण
अटल अंतरभूत पूर्णांक cw1200_ahb_पढ़ो_32(काष्ठा cw1200_common *priv,
				     u32 addr, u32 *val)
अणु
	__le32 पंचांगp;
	पूर्णांक i = cw1200_ahb_पढ़ो(priv, addr, &पंचांगp, माप(पंचांगp));
	*val = le32_to_cpu(पंचांगp);
	वापस i;
पूर्ण

#पूर्ण_अगर /* CW1200_HWIO_H_INCLUDED */
