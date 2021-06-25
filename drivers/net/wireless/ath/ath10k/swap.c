<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (c) 2015-2016 Qualcomm Atheros, Inc.
 */

/* This file has implementation क्रम code swap logic. With code swap feature,
 * target can run the fw binary with even smaller IRAM size by using host
 * memory to store some of the code segments.
 */

#समावेश "core.h"
#समावेश "bmi.h"
#समावेश "debug.h"

अटल पूर्णांक ath10k_swap_code_seg_fill(काष्ठा ath10k *ar,
				     काष्ठा ath10k_swap_code_seg_info *seg_info,
				     स्थिर व्योम *data, माप_प्रकार data_len)
अणु
	u8 *virt_addr = seg_info->virt_address[0];
	u8 swap_magic[ATH10K_SWAP_CODE_SEG_MAGIC_BYTES_SZ] = अणुपूर्ण;
	स्थिर u8 *fw_data = data;
	जोड़ ath10k_swap_code_seg_item *swap_item;
	u32 length = 0;
	u32 payload_len;
	u32 total_payload_len = 0;
	u32 size_left = data_len;

	/* Parse swap bin and copy the content to host allocated memory.
	 * The क्रमmat is Address, length and value. The last 4-bytes is
	 * target ग_लिखो address. Currently address field is not used.
	 */
	seg_info->target_addr = -1;
	जबतक (size_left >= माप(*swap_item)) अणु
		swap_item = (जोड़ ath10k_swap_code_seg_item *)fw_data;
		payload_len = __le32_to_cpu(swap_item->tlv.length);
		अगर ((payload_len > size_left) ||
		    (payload_len == 0 &&
		     size_left != माप(काष्ठा ath10k_swap_code_seg_tail))) अणु
			ath10k_err(ar, "refusing to parse invalid tlv length %d\n",
				   payload_len);
			वापस -EINVAL;
		पूर्ण

		अगर (payload_len == 0) अणु
			अगर (स_भेद(swap_item->tail.magic_signature, swap_magic,
				   ATH10K_SWAP_CODE_SEG_MAGIC_BYTES_SZ)) अणु
				ath10k_err(ar, "refusing an invalid swap file\n");
				वापस -EINVAL;
			पूर्ण
			seg_info->target_addr =
				__le32_to_cpu(swap_item->tail.bmi_ग_लिखो_addr);
			अवरोध;
		पूर्ण

		स_नकल(virt_addr, swap_item->tlv.data, payload_len);
		virt_addr += payload_len;
		length = payload_len +  माप(काष्ठा ath10k_swap_code_seg_tlv);
		size_left -= length;
		fw_data += length;
		total_payload_len += payload_len;
	पूर्ण

	अगर (seg_info->target_addr == -1) अणु
		ath10k_err(ar, "failed to parse invalid swap file\n");
		वापस -EINVAL;
	पूर्ण
	seg_info->seg_hw_info.swap_size = __cpu_to_le32(total_payload_len);

	वापस 0;
पूर्ण

अटल व्योम
ath10k_swap_code_seg_मुक्त(काष्ठा ath10k *ar,
			  काष्ठा ath10k_swap_code_seg_info *seg_info)
अणु
	u32 seg_size;

	अगर (!seg_info)
		वापस;

	अगर (!seg_info->virt_address[0])
		वापस;

	seg_size = __le32_to_cpu(seg_info->seg_hw_info.size);
	dma_मुक्त_coherent(ar->dev, seg_size, seg_info->virt_address[0],
			  seg_info->paddr[0]);
पूर्ण

अटल काष्ठा ath10k_swap_code_seg_info *
ath10k_swap_code_seg_alloc(काष्ठा ath10k *ar, माप_प्रकार swap_bin_len)
अणु
	काष्ठा ath10k_swap_code_seg_info *seg_info;
	व्योम *virt_addr;
	dma_addr_t paddr;

	swap_bin_len = roundup(swap_bin_len, 2);
	अगर (swap_bin_len > ATH10K_SWAP_CODE_SEG_BIN_LEN_MAX) अणु
		ath10k_err(ar, "refusing code swap bin because it is too big %zu > %d\n",
			   swap_bin_len, ATH10K_SWAP_CODE_SEG_BIN_LEN_MAX);
		वापस शून्य;
	पूर्ण

	seg_info = devm_kzalloc(ar->dev, माप(*seg_info), GFP_KERNEL);
	अगर (!seg_info)
		वापस शून्य;

	virt_addr = dma_alloc_coherent(ar->dev, swap_bin_len, &paddr,
				       GFP_KERNEL);
	अगर (!virt_addr)
		वापस शून्य;

	seg_info->seg_hw_info.bus_addr[0] = __cpu_to_le32(paddr);
	seg_info->seg_hw_info.size = __cpu_to_le32(swap_bin_len);
	seg_info->seg_hw_info.swap_size = __cpu_to_le32(swap_bin_len);
	seg_info->seg_hw_info.num_segs =
			__cpu_to_le32(ATH10K_SWAP_CODE_SEG_NUM_SUPPORTED);
	seg_info->seg_hw_info.size_log2 = __cpu_to_le32(ilog2(swap_bin_len));
	seg_info->virt_address[0] = virt_addr;
	seg_info->paddr[0] = paddr;

	वापस seg_info;
पूर्ण

पूर्णांक ath10k_swap_code_seg_configure(काष्ठा ath10k *ar,
				   स्थिर काष्ठा ath10k_fw_file *fw_file)
अणु
	पूर्णांक ret;
	काष्ठा ath10k_swap_code_seg_info *seg_info = शून्य;

	अगर (!fw_file->firmware_swap_code_seg_info)
		वापस 0;

	ath10k_dbg(ar, ATH10K_DBG_BOOT, "boot found firmware code swap binary\n");

	seg_info = fw_file->firmware_swap_code_seg_info;

	ret = ath10k_bmi_ग_लिखो_memory(ar, seg_info->target_addr,
				      &seg_info->seg_hw_info,
				      माप(seg_info->seg_hw_info));
	अगर (ret) अणु
		ath10k_err(ar, "failed to write Code swap segment information (%d)\n",
			   ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

व्योम ath10k_swap_code_seg_release(काष्ठा ath10k *ar,
				  काष्ठा ath10k_fw_file *fw_file)
अणु
	ath10k_swap_code_seg_मुक्त(ar, fw_file->firmware_swap_code_seg_info);

	/* FIXME: these two assignments look to bein wrong place! Shouldn't
	 * they be in ath10k_core_मुक्त_firmware_files() like the rest?
	 */
	fw_file->codeswap_data = शून्य;
	fw_file->codeswap_len = 0;

	fw_file->firmware_swap_code_seg_info = शून्य;
पूर्ण

पूर्णांक ath10k_swap_code_seg_init(काष्ठा ath10k *ar, काष्ठा ath10k_fw_file *fw_file)
अणु
	पूर्णांक ret;
	काष्ठा ath10k_swap_code_seg_info *seg_info;
	स्थिर व्योम *codeswap_data;
	माप_प्रकार codeswap_len;

	codeswap_data = fw_file->codeswap_data;
	codeswap_len = fw_file->codeswap_len;

	अगर (!codeswap_len || !codeswap_data)
		वापस 0;

	seg_info = ath10k_swap_code_seg_alloc(ar, codeswap_len);
	अगर (!seg_info) अणु
		ath10k_err(ar, "failed to allocate fw code swap segment\n");
		वापस -ENOMEM;
	पूर्ण

	ret = ath10k_swap_code_seg_fill(ar, seg_info,
					codeswap_data, codeswap_len);

	अगर (ret) अणु
		ath10k_warn(ar, "failed to initialize fw code swap segment: %d\n",
			    ret);
		ath10k_swap_code_seg_मुक्त(ar, seg_info);
		वापस ret;
	पूर्ण

	fw_file->firmware_swap_code_seg_info = seg_info;

	वापस 0;
पूर्ण
