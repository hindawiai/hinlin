<शैली गुरु>
/* SPDX-License-Identअगरier: ISC */
/*
 * Copyright (c) 2015-2016 Qualcomm Atheros, Inc.
 */

#अगर_अघोषित _SWAP_H_
#घोषणा _SWAP_H_

#घोषणा ATH10K_SWAP_CODE_SEG_BIN_LEN_MAX	(512 * 1024)
#घोषणा ATH10K_SWAP_CODE_SEG_MAGIC_BYTES_SZ	12
#घोषणा ATH10K_SWAP_CODE_SEG_NUM_MAX		16
/* Currently only one swap segment is supported */
#घोषणा ATH10K_SWAP_CODE_SEG_NUM_SUPPORTED	1

काष्ठा ath10k_fw_file;

काष्ठा ath10k_swap_code_seg_tlv अणु
	__le32 address;
	__le32 length;
	u8 data[0];
पूर्ण __packed;

काष्ठा ath10k_swap_code_seg_tail अणु
	u8 magic_signature[ATH10K_SWAP_CODE_SEG_MAGIC_BYTES_SZ];
	__le32 bmi_ग_लिखो_addr;
पूर्ण __packed;

जोड़ ath10k_swap_code_seg_item अणु
	काष्ठा ath10k_swap_code_seg_tlv tlv;
	काष्ठा ath10k_swap_code_seg_tail tail;
पूर्ण __packed;

काष्ठा ath10k_swap_code_seg_hw_info अणु
	/* Swap binary image size */
	__le32 swap_size;
	__le32 num_segs;

	/* Swap data size */
	__le32 size;
	__le32 size_log2;
	__le32 bus_addr[ATH10K_SWAP_CODE_SEG_NUM_MAX];
	__le64 reserved[ATH10K_SWAP_CODE_SEG_NUM_MAX];
पूर्ण __packed;

काष्ठा ath10k_swap_code_seg_info अणु
	काष्ठा ath10k_swap_code_seg_hw_info seg_hw_info;
	व्योम *virt_address[ATH10K_SWAP_CODE_SEG_NUM_SUPPORTED];
	u32 target_addr;
	dma_addr_t paddr[ATH10K_SWAP_CODE_SEG_NUM_SUPPORTED];
पूर्ण;

पूर्णांक ath10k_swap_code_seg_configure(काष्ठा ath10k *ar,
				   स्थिर काष्ठा ath10k_fw_file *fw_file);
व्योम ath10k_swap_code_seg_release(काष्ठा ath10k *ar,
				  काष्ठा ath10k_fw_file *fw_file);
पूर्णांक ath10k_swap_code_seg_init(काष्ठा ath10k *ar,
			      काष्ठा ath10k_fw_file *fw_file);

#पूर्ण_अगर
