<शैली गुरु>
/* SPDX-License-Identअगरier: ISC */
/*
 * Copyright (c) 2005-2011 Atheros Communications Inc.
 * Copyright (c) 2011-2015,2017 Qualcomm Atheros, Inc.
 */

#अगर_अघोषित _BMI_H_
#घोषणा _BMI_H_

#समावेश "core.h"

/*
 * Bootloader Messaging Interface (BMI)
 *
 * BMI is a very simple messaging पूर्णांकerface used during initialization
 * to पढ़ो memory, ग_लिखो memory, execute code, and to define an
 * application entry PC.
 *
 * It is used to करोwnload an application to QCA988x, to provide
 * patches to code that is alपढ़ोy resident on QCA988x, and generally
 * to examine and modअगरy state.  The Host has an opportunity to use
 * BMI only once during bootup.  Once the Host issues a BMI_DONE
 * command, this opportunity ends.
 *
 * The Host ग_लिखोs BMI requests to mailbox0, and पढ़ोs BMI responses
 * from mailbox0.   BMI requests all begin with a command
 * (see below क्रम specअगरic commands), and are followed by
 * command-specअगरic data.
 *
 * Flow control:
 * The Host can only issue a command once the Target gives it a
 * "BMI Command Credit", using AR8K Counter #4.  As soon as the
 * Target has completed a command, it issues another BMI Command
 * Credit (so the Host can issue the next command).
 *
 * BMI handles all required Target-side cache flushing.
 */

/* Maximum data size used क्रम BMI transfers */
#घोषणा BMI_MAX_DATA_SIZE	256

/* len = cmd + addr + length */
#घोषणा BMI_MAX_CMDBUF_SIZE (BMI_MAX_DATA_SIZE + \
			माप(u32) + \
			माप(u32) + \
			माप(u32))

/* Maximum data size used क्रम large BMI transfers */
#घोषणा BMI_MAX_LARGE_DATA_SIZE	2048

/* len = cmd + addr + length */
#घोषणा BMI_MAX_LARGE_CMDBUF_SIZE (BMI_MAX_LARGE_DATA_SIZE + \
			माप(u32) + \
			माप(u32) + \
			माप(u32))

/* BMI Commands */

क्रमागत bmi_cmd_id अणु
	BMI_NO_COMMAND          = 0,
	BMI_DONE                = 1,
	BMI_READ_MEMORY         = 2,
	BMI_WRITE_MEMORY        = 3,
	BMI_EXECUTE             = 4,
	BMI_SET_APP_START       = 5,
	BMI_READ_SOC_REGISTER   = 6,
	BMI_READ_SOC_WORD       = 6,
	BMI_WRITE_SOC_REGISTER  = 7,
	BMI_WRITE_SOC_WORD      = 7,
	BMI_GET_TARGET_ID       = 8,
	BMI_GET_TARGET_INFO     = 8,
	BMI_ROMPATCH_INSTALL    = 9,
	BMI_ROMPATCH_UNINSTALL  = 10,
	BMI_ROMPATCH_ACTIVATE   = 11,
	BMI_ROMPATCH_DEACTIVATE = 12,
	BMI_LZ_STREAM_START     = 13, /* should be followed by LZ_DATA */
	BMI_LZ_DATA             = 14,
	BMI_NVRAM_PROCESS       = 15,
पूर्ण;

#घोषणा BMI_NVRAM_SEG_NAME_SZ 16

#घोषणा BMI_PARAM_GET_EEPROM_BOARD_ID 0x10
#घोषणा BMI_PARAM_GET_FLASH_BOARD_ID 0x8000
#घोषणा BMI_PARAM_FLASH_SECTION_ALL 0x10000

/* Dual-band Extended Board ID */
#घोषणा BMI_PARAM_GET_EXT_BOARD_ID 0x40000
#घोषणा ATH10K_BMI_EXT_BOARD_ID_SUPPORT 0x40000

#घोषणा ATH10K_BMI_BOARD_ID_FROM_OTP_MASK   0x7c00
#घोषणा ATH10K_BMI_BOARD_ID_FROM_OTP_LSB    10

#घोषणा ATH10K_BMI_CHIP_ID_FROM_OTP_MASK    0x18000
#घोषणा ATH10K_BMI_CHIP_ID_FROM_OTP_LSB     15

#घोषणा ATH10K_BMI_BOARD_ID_STATUS_MASK 0xff
#घोषणा ATH10K_BMI_EBOARD_ID_STATUS_MASK 0xff

काष्ठा bmi_cmd अणु
	__le32 id; /* क्रमागत bmi_cmd_id */
	जोड़ अणु
		काष्ठा अणु
		पूर्ण करोne;
		काष्ठा अणु
			__le32 addr;
			__le32 len;
		पूर्ण पढ़ो_mem;
		काष्ठा अणु
			__le32 addr;
			__le32 len;
			u8 payload[0];
		पूर्ण ग_लिखो_mem;
		काष्ठा अणु
			__le32 addr;
			__le32 param;
		पूर्ण execute;
		काष्ठा अणु
			__le32 addr;
		पूर्ण set_app_start;
		काष्ठा अणु
			__le32 addr;
		पूर्ण पढ़ो_soc_reg;
		काष्ठा अणु
			__le32 addr;
			__le32 value;
		पूर्ण ग_लिखो_soc_reg;
		काष्ठा अणु
		पूर्ण get_target_info;
		काष्ठा अणु
			__le32 rom_addr;
			__le32 ram_addr; /* or value */
			__le32 size;
			__le32 activate; /* 0=install, but करोnt activate */
		पूर्ण rompatch_install;
		काष्ठा अणु
			__le32 patch_id;
		पूर्ण rompatch_uninstall;
		काष्ठा अणु
			__le32 count;
			__le32 patch_ids[0]; /* length of @count */
		पूर्ण rompatch_activate;
		काष्ठा अणु
			__le32 count;
			__le32 patch_ids[0]; /* length of @count */
		पूर्ण rompatch_deactivate;
		काष्ठा अणु
			__le32 addr;
		पूर्ण lz_start;
		काष्ठा अणु
			__le32 len; /* max BMI_MAX_DATA_SIZE */
			u8 payload[0]; /* length of @len */
		पूर्ण lz_data;
		काष्ठा अणु
			u8 name[BMI_NVRAM_SEG_NAME_SZ];
		पूर्ण nvram_process;
		u8 payload[BMI_MAX_CMDBUF_SIZE];
	पूर्ण;
पूर्ण __packed;

जोड़ bmi_resp अणु
	काष्ठा अणु
		u8 payload[0];
	पूर्ण पढ़ो_mem;
	काष्ठा अणु
		__le32 result;
	पूर्ण execute;
	काष्ठा अणु
		__le32 value;
	पूर्ण पढ़ो_soc_reg;
	काष्ठा अणु
		__le32 len;
		__le32 version;
		__le32 type;
	पूर्ण get_target_info;
	काष्ठा अणु
		__le32 patch_id;
	पूर्ण rompatch_install;
	काष्ठा अणु
		__le32 patch_id;
	पूर्ण rompatch_uninstall;
	काष्ठा अणु
		/* 0 = nothing executed
		 * otherwise = NVRAM segment वापस value
		 */
		__le32 result;
	पूर्ण nvram_process;
	u8 payload[BMI_MAX_CMDBUF_SIZE];
पूर्ण __packed;

काष्ठा bmi_target_info अणु
	u32 version;
	u32 type;
पूर्ण;

काष्ठा bmi_segmented_file_header अणु
	__le32 magic_num;
	__le32 file_flags;
	u8 data[];
पूर्ण;

काष्ठा bmi_segmented_metadata अणु
	__le32 addr;
	__le32 length;
	u8 data[];
पूर्ण;

#घोषणा BMI_SGMTखाता_MAGIC_NUM          0x544d4753 /* "SGMT" */
#घोषणा BMI_SGMTखाता_FLAG_COMPRESS      1

/* Special values क्रम bmi_segmented_metadata.length (all have high bit set) */

/* end of segmented data */
#घोषणा BMI_SGMTखाता_DONE               0xffffffff

/* Board Data segment */
#घोषणा BMI_SGMTखाता_BDDATA             0xfffffffe

/* set beginning address */
#घोषणा BMI_SGMTखाता_BEGINADDR          0xfffffffd

/* immediate function execution */
#घोषणा BMI_SGMTखाता_EXEC               0xfffffffc

/* in jअगरfies */
#घोषणा BMI_COMMUNICATION_TIMEOUT_HZ (3 * HZ)

#घोषणा BMI_CE_NUM_TO_TARG 0
#घोषणा BMI_CE_NUM_TO_HOST 1

व्योम ath10k_bmi_start(काष्ठा ath10k *ar);
पूर्णांक ath10k_bmi_करोne(काष्ठा ath10k *ar);
पूर्णांक ath10k_bmi_get_target_info(काष्ठा ath10k *ar,
			       काष्ठा bmi_target_info *target_info);
पूर्णांक ath10k_bmi_get_target_info_sdio(काष्ठा ath10k *ar,
				    काष्ठा bmi_target_info *target_info);
पूर्णांक ath10k_bmi_पढ़ो_memory(काष्ठा ath10k *ar, u32 address,
			   व्योम *buffer, u32 length);
पूर्णांक ath10k_bmi_ग_लिखो_memory(काष्ठा ath10k *ar, u32 address,
			    स्थिर व्योम *buffer, u32 length);

#घोषणा ath10k_bmi_पढ़ो32(ar, item, val)				\
	(अणु								\
		पूर्णांक ret;						\
		u32 addr;						\
		__le32 पंचांगp;						\
									\
		addr = host_पूर्णांकerest_item_address(HI_ITEM(item));	\
		ret = ath10k_bmi_पढ़ो_memory(ar, addr, (u8 *)&पंचांगp, 4); \
		अगर (!ret)						\
			*val = __le32_to_cpu(पंचांगp);			\
		ret;							\
	 पूर्ण)

#घोषणा ath10k_bmi_ग_लिखो32(ar, item, val)				\
	(अणु								\
		पूर्णांक ret;						\
		u32 address;						\
		__le32 v = __cpu_to_le32(val);				\
									\
		address = host_पूर्णांकerest_item_address(HI_ITEM(item));	\
		ret = ath10k_bmi_ग_लिखो_memory(ar, address,		\
					      (u8 *)&v, माप(v));	\
		ret;							\
	पूर्ण)

पूर्णांक ath10k_bmi_execute(काष्ठा ath10k *ar, u32 address, u32 param, u32 *result);
पूर्णांक ath10k_bmi_lz_stream_start(काष्ठा ath10k *ar, u32 address);
पूर्णांक ath10k_bmi_lz_data(काष्ठा ath10k *ar, स्थिर व्योम *buffer, u32 length);

पूर्णांक ath10k_bmi_fast_करोwnload(काष्ठा ath10k *ar, u32 address,
			     स्थिर व्योम *buffer, u32 length);
पूर्णांक ath10k_bmi_पढ़ो_soc_reg(काष्ठा ath10k *ar, u32 address, u32 *reg_val);
पूर्णांक ath10k_bmi_ग_लिखो_soc_reg(काष्ठा ath10k *ar, u32 address, u32 reg_val);
पूर्णांक ath10k_bmi_set_start(काष्ठा ath10k *ar, u32 address);

#पूर्ण_अगर /* _BMI_H_ */
