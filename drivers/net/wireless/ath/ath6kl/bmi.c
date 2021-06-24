<शैली गुरु>
/*
 * Copyright (c) 2004-2011 Atheros Communications Inc.
 * Copyright (c) 2011-2012 Qualcomm Atheros, Inc.
 *
 * Permission to use, copy, modअगरy, and/or distribute this software क्रम any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, सूचीECT, INसूचीECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#समावेश "core.h"
#समावेश "hif-ops.h"
#समावेश "target.h"
#समावेश "debug.h"

पूर्णांक ath6kl_bmi_करोne(काष्ठा ath6kl *ar)
अणु
	पूर्णांक ret;
	u32 cid = BMI_DONE;

	अगर (ar->bmi.करोne_sent) अणु
		ath6kl_dbg(ATH6KL_DBG_BMI, "bmi done skipped\n");
		वापस 0;
	पूर्ण

	ar->bmi.करोne_sent = true;

	ret = ath6kl_hअगर_bmi_ग_लिखो(ar, (u8 *)&cid, माप(cid));
	अगर (ret) अणु
		ath6kl_err("Unable to send bmi done: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक ath6kl_bmi_get_target_info(काष्ठा ath6kl *ar,
			       काष्ठा ath6kl_bmi_target_info *targ_info)
अणु
	पूर्णांक ret;
	u32 cid = BMI_GET_TARGET_INFO;

	अगर (ar->bmi.करोne_sent) अणु
		ath6kl_err("bmi done sent already, cmd %d disallowed\n", cid);
		वापस -EACCES;
	पूर्ण

	ret = ath6kl_hअगर_bmi_ग_लिखो(ar, (u8 *)&cid, माप(cid));
	अगर (ret) अणु
		ath6kl_err("Unable to send get target info: %d\n", ret);
		वापस ret;
	पूर्ण

	अगर (ar->hअगर_type == ATH6KL_HIF_TYPE_USB) अणु
		ret = ath6kl_hअगर_bmi_पढ़ो(ar, (u8 *)targ_info,
					  माप(*targ_info));
	पूर्ण अन्यथा अणु
		ret = ath6kl_hअगर_bmi_पढ़ो(ar, (u8 *)&targ_info->version,
				माप(targ_info->version));
	पूर्ण

	अगर (ret) अणु
		ath6kl_err("Unable to recv target info: %d\n", ret);
		वापस ret;
	पूर्ण

	अगर (le32_to_cpu(targ_info->version) == TARGET_VERSION_SENTINAL) अणु
		/* Determine how many bytes are in the Target's targ_info */
		ret = ath6kl_hअगर_bmi_पढ़ो(ar,
				   (u8 *)&targ_info->byte_count,
				   माप(targ_info->byte_count));
		अगर (ret) अणु
			ath6kl_err("unable to read target info byte count: %d\n",
				   ret);
			वापस ret;
		पूर्ण

		/*
		 * The target's targ_info doesn't match the host's targ_info.
		 * We need to करो some backwards compatibility to make this work.
		 */
		अगर (le32_to_cpu(targ_info->byte_count) != माप(*targ_info)) अणु
			WARN_ON(1);
			वापस -EINVAL;
		पूर्ण

		/* Read the reमुख्यder of the targ_info */
		ret = ath6kl_hअगर_bmi_पढ़ो(ar,
				   ((u8 *)targ_info) +
				   माप(targ_info->byte_count),
				   माप(*targ_info) -
				   माप(targ_info->byte_count));

		अगर (ret) अणु
			ath6kl_err("Unable to read target info (%d bytes): %d\n",
				   targ_info->byte_count, ret);
			वापस ret;
		पूर्ण
	पूर्ण

	ath6kl_dbg(ATH6KL_DBG_BMI, "target info (ver: 0x%x type: 0x%x)\n",
		   targ_info->version, targ_info->type);

	वापस 0;
पूर्ण

पूर्णांक ath6kl_bmi_पढ़ो(काष्ठा ath6kl *ar, u32 addr, u8 *buf, u32 len)
अणु
	u32 cid = BMI_READ_MEMORY;
	पूर्णांक ret;
	u32 offset;
	u32 len_reमुख्य, rx_len;
	u16 size;

	अगर (ar->bmi.करोne_sent) अणु
		ath6kl_err("bmi done sent already, cmd %d disallowed\n", cid);
		वापस -EACCES;
	पूर्ण

	size = ar->bmi.max_data_size + माप(cid) + माप(addr) + माप(len);
	अगर (size > ar->bmi.max_cmd_size) अणु
		WARN_ON(1);
		वापस -EINVAL;
	पूर्ण
	स_रखो(ar->bmi.cmd_buf, 0, size);

	ath6kl_dbg(ATH6KL_DBG_BMI,
		   "bmi read memory: device: addr: 0x%x, len: %d\n",
		   addr, len);

	len_reमुख्य = len;

	जबतक (len_reमुख्य) अणु
		rx_len = (len_reमुख्य < ar->bmi.max_data_size) ?
					len_reमुख्य : ar->bmi.max_data_size;
		offset = 0;
		स_नकल(&(ar->bmi.cmd_buf[offset]), &cid, माप(cid));
		offset += माप(cid);
		स_नकल(&(ar->bmi.cmd_buf[offset]), &addr, माप(addr));
		offset += माप(addr);
		स_नकल(&(ar->bmi.cmd_buf[offset]), &rx_len, माप(rx_len));
		offset += माप(len);

		ret = ath6kl_hअगर_bmi_ग_लिखो(ar, ar->bmi.cmd_buf, offset);
		अगर (ret) अणु
			ath6kl_err("Unable to write to the device: %d\n",
				   ret);
			वापस ret;
		पूर्ण
		ret = ath6kl_hअगर_bmi_पढ़ो(ar, ar->bmi.cmd_buf, rx_len);
		अगर (ret) अणु
			ath6kl_err("Unable to read from the device: %d\n",
				   ret);
			वापस ret;
		पूर्ण
		स_नकल(&buf[len - len_reमुख्य], ar->bmi.cmd_buf, rx_len);
		len_reमुख्य -= rx_len; addr += rx_len;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक ath6kl_bmi_ग_लिखो(काष्ठा ath6kl *ar, u32 addr, u8 *buf, u32 len)
अणु
	u32 cid = BMI_WRITE_MEMORY;
	पूर्णांक ret;
	u32 offset;
	u32 len_reमुख्य, tx_len;
	स्थिर u32 header = माप(cid) + माप(addr) + माप(len);
	u8 aligned_buf[400];
	u8 *src;

	अगर (ar->bmi.करोne_sent) अणु
		ath6kl_err("bmi done sent already, cmd %d disallowed\n", cid);
		वापस -EACCES;
	पूर्ण

	अगर ((ar->bmi.max_data_size + header) > ar->bmi.max_cmd_size) अणु
		WARN_ON(1);
		वापस -EINVAL;
	पूर्ण

	अगर (WARN_ON(ar->bmi.max_data_size > माप(aligned_buf)))
		वापस -E2BIG;

	स_रखो(ar->bmi.cmd_buf, 0, ar->bmi.max_data_size + header);

	ath6kl_dbg(ATH6KL_DBG_BMI,
		   "bmi write memory: addr: 0x%x, len: %d\n", addr, len);

	len_reमुख्य = len;
	जबतक (len_reमुख्य) अणु
		src = &buf[len - len_reमुख्य];

		अगर (len_reमुख्य < (ar->bmi.max_data_size - header)) अणु
			अगर (len_reमुख्य & 3) अणु
				/* align it with 4 bytes */
				len_reमुख्य = len_reमुख्य +
					     (4 - (len_reमुख्य & 3));
				स_नकल(aligned_buf, src, len_reमुख्य);
				src = aligned_buf;
			पूर्ण
			tx_len = len_reमुख्य;
		पूर्ण अन्यथा अणु
			tx_len = (ar->bmi.max_data_size - header);
		पूर्ण

		offset = 0;
		स_नकल(&(ar->bmi.cmd_buf[offset]), &cid, माप(cid));
		offset += माप(cid);
		स_नकल(&(ar->bmi.cmd_buf[offset]), &addr, माप(addr));
		offset += माप(addr);
		स_नकल(&(ar->bmi.cmd_buf[offset]), &tx_len, माप(tx_len));
		offset += माप(tx_len);
		स_नकल(&(ar->bmi.cmd_buf[offset]), src, tx_len);
		offset += tx_len;

		ret = ath6kl_hअगर_bmi_ग_लिखो(ar, ar->bmi.cmd_buf, offset);
		अगर (ret) अणु
			ath6kl_err("Unable to write to the device: %d\n",
				   ret);
			वापस ret;
		पूर्ण
		len_reमुख्य -= tx_len; addr += tx_len;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक ath6kl_bmi_execute(काष्ठा ath6kl *ar, u32 addr, u32 *param)
अणु
	u32 cid = BMI_EXECUTE;
	पूर्णांक ret;
	u32 offset;
	u16 size;

	अगर (ar->bmi.करोne_sent) अणु
		ath6kl_err("bmi done sent already, cmd %d disallowed\n", cid);
		वापस -EACCES;
	पूर्ण

	size = माप(cid) + माप(addr) + माप(param);
	अगर (size > ar->bmi.max_cmd_size) अणु
		WARN_ON(1);
		वापस -EINVAL;
	पूर्ण
	स_रखो(ar->bmi.cmd_buf, 0, size);

	ath6kl_dbg(ATH6KL_DBG_BMI, "bmi execute: addr: 0x%x, param: %d)\n",
		   addr, *param);

	offset = 0;
	स_नकल(&(ar->bmi.cmd_buf[offset]), &cid, माप(cid));
	offset += माप(cid);
	स_नकल(&(ar->bmi.cmd_buf[offset]), &addr, माप(addr));
	offset += माप(addr);
	स_नकल(&(ar->bmi.cmd_buf[offset]), param, माप(*param));
	offset += माप(*param);

	ret = ath6kl_hअगर_bmi_ग_लिखो(ar, ar->bmi.cmd_buf, offset);
	अगर (ret) अणु
		ath6kl_err("Unable to write to the device: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = ath6kl_hअगर_bmi_पढ़ो(ar, ar->bmi.cmd_buf, माप(*param));
	अगर (ret) अणु
		ath6kl_err("Unable to read from the device: %d\n", ret);
		वापस ret;
	पूर्ण

	स_नकल(param, ar->bmi.cmd_buf, माप(*param));

	वापस 0;
पूर्ण

पूर्णांक ath6kl_bmi_set_app_start(काष्ठा ath6kl *ar, u32 addr)
अणु
	u32 cid = BMI_SET_APP_START;
	पूर्णांक ret;
	u32 offset;
	u16 size;

	अगर (ar->bmi.करोne_sent) अणु
		ath6kl_err("bmi done sent already, cmd %d disallowed\n", cid);
		वापस -EACCES;
	पूर्ण

	size = माप(cid) + माप(addr);
	अगर (size > ar->bmi.max_cmd_size) अणु
		WARN_ON(1);
		वापस -EINVAL;
	पूर्ण
	स_रखो(ar->bmi.cmd_buf, 0, size);

	ath6kl_dbg(ATH6KL_DBG_BMI, "bmi set app start: addr: 0x%x\n", addr);

	offset = 0;
	स_नकल(&(ar->bmi.cmd_buf[offset]), &cid, माप(cid));
	offset += माप(cid);
	स_नकल(&(ar->bmi.cmd_buf[offset]), &addr, माप(addr));
	offset += माप(addr);

	ret = ath6kl_hअगर_bmi_ग_लिखो(ar, ar->bmi.cmd_buf, offset);
	अगर (ret) अणु
		ath6kl_err("Unable to write to the device: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक ath6kl_bmi_reg_पढ़ो(काष्ठा ath6kl *ar, u32 addr, u32 *param)
अणु
	u32 cid = BMI_READ_SOC_REGISTER;
	पूर्णांक ret;
	u32 offset;
	u16 size;

	अगर (ar->bmi.करोne_sent) अणु
		ath6kl_err("bmi done sent already, cmd %d disallowed\n", cid);
		वापस -EACCES;
	पूर्ण

	size = माप(cid) + माप(addr);
	अगर (size > ar->bmi.max_cmd_size) अणु
		WARN_ON(1);
		वापस -EINVAL;
	पूर्ण
	स_रखो(ar->bmi.cmd_buf, 0, size);

	ath6kl_dbg(ATH6KL_DBG_BMI, "bmi read SOC reg: addr: 0x%x\n", addr);

	offset = 0;
	स_नकल(&(ar->bmi.cmd_buf[offset]), &cid, माप(cid));
	offset += माप(cid);
	स_नकल(&(ar->bmi.cmd_buf[offset]), &addr, माप(addr));
	offset += माप(addr);

	ret = ath6kl_hअगर_bmi_ग_लिखो(ar, ar->bmi.cmd_buf, offset);
	अगर (ret) अणु
		ath6kl_err("Unable to write to the device: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = ath6kl_hअगर_bmi_पढ़ो(ar, ar->bmi.cmd_buf, माप(*param));
	अगर (ret) अणु
		ath6kl_err("Unable to read from the device: %d\n", ret);
		वापस ret;
	पूर्ण
	स_नकल(param, ar->bmi.cmd_buf, माप(*param));

	वापस 0;
पूर्ण

पूर्णांक ath6kl_bmi_reg_ग_लिखो(काष्ठा ath6kl *ar, u32 addr, u32 param)
अणु
	u32 cid = BMI_WRITE_SOC_REGISTER;
	पूर्णांक ret;
	u32 offset;
	u16 size;

	अगर (ar->bmi.करोne_sent) अणु
		ath6kl_err("bmi done sent already, cmd %d disallowed\n", cid);
		वापस -EACCES;
	पूर्ण

	size = माप(cid) + माप(addr) + माप(param);
	अगर (size > ar->bmi.max_cmd_size) अणु
		WARN_ON(1);
		वापस -EINVAL;
	पूर्ण
	स_रखो(ar->bmi.cmd_buf, 0, size);

	ath6kl_dbg(ATH6KL_DBG_BMI,
		   "bmi write SOC reg: addr: 0x%x, param: %d\n",
		    addr, param);

	offset = 0;
	स_नकल(&(ar->bmi.cmd_buf[offset]), &cid, माप(cid));
	offset += माप(cid);
	स_नकल(&(ar->bmi.cmd_buf[offset]), &addr, माप(addr));
	offset += माप(addr);
	स_नकल(&(ar->bmi.cmd_buf[offset]), &param, माप(param));
	offset += माप(param);

	ret = ath6kl_hअगर_bmi_ग_लिखो(ar, ar->bmi.cmd_buf, offset);
	अगर (ret) अणु
		ath6kl_err("Unable to write to the device: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक ath6kl_bmi_lz_data(काष्ठा ath6kl *ar, u8 *buf, u32 len)
अणु
	u32 cid = BMI_LZ_DATA;
	पूर्णांक ret;
	u32 offset;
	u32 len_reमुख्य, tx_len;
	स्थिर u32 header = माप(cid) + माप(len);
	u16 size;

	अगर (ar->bmi.करोne_sent) अणु
		ath6kl_err("bmi done sent already, cmd %d disallowed\n", cid);
		वापस -EACCES;
	पूर्ण

	size = ar->bmi.max_data_size + header;
	अगर (size > ar->bmi.max_cmd_size) अणु
		WARN_ON(1);
		वापस -EINVAL;
	पूर्ण
	स_रखो(ar->bmi.cmd_buf, 0, size);

	ath6kl_dbg(ATH6KL_DBG_BMI, "bmi send LZ data: len: %d)\n",
		   len);

	len_reमुख्य = len;
	जबतक (len_reमुख्य) अणु
		tx_len = (len_reमुख्य < (ar->bmi.max_data_size - header)) ?
			  len_reमुख्य : (ar->bmi.max_data_size - header);

		offset = 0;
		स_नकल(&(ar->bmi.cmd_buf[offset]), &cid, माप(cid));
		offset += माप(cid);
		स_नकल(&(ar->bmi.cmd_buf[offset]), &tx_len, माप(tx_len));
		offset += माप(tx_len);
		स_नकल(&(ar->bmi.cmd_buf[offset]), &buf[len - len_reमुख्य],
		       tx_len);
		offset += tx_len;

		ret = ath6kl_hअगर_bmi_ग_लिखो(ar, ar->bmi.cmd_buf, offset);
		अगर (ret) अणु
			ath6kl_err("Unable to write to the device: %d\n",
				   ret);
			वापस ret;
		पूर्ण

		len_reमुख्य -= tx_len;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक ath6kl_bmi_lz_stream_start(काष्ठा ath6kl *ar, u32 addr)
अणु
	u32 cid = BMI_LZ_STREAM_START;
	पूर्णांक ret;
	u32 offset;
	u16 size;

	अगर (ar->bmi.करोne_sent) अणु
		ath6kl_err("bmi done sent already, cmd %d disallowed\n", cid);
		वापस -EACCES;
	पूर्ण

	size = माप(cid) + माप(addr);
	अगर (size > ar->bmi.max_cmd_size) अणु
		WARN_ON(1);
		वापस -EINVAL;
	पूर्ण
	स_रखो(ar->bmi.cmd_buf, 0, size);

	ath6kl_dbg(ATH6KL_DBG_BMI,
		   "bmi LZ stream start: addr: 0x%x)\n",
		    addr);

	offset = 0;
	स_नकल(&(ar->bmi.cmd_buf[offset]), &cid, माप(cid));
	offset += माप(cid);
	स_नकल(&(ar->bmi.cmd_buf[offset]), &addr, माप(addr));
	offset += माप(addr);

	ret = ath6kl_hअगर_bmi_ग_लिखो(ar, ar->bmi.cmd_buf, offset);
	अगर (ret) अणु
		ath6kl_err("Unable to start LZ stream to the device: %d\n",
			   ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक ath6kl_bmi_fast_करोwnload(काष्ठा ath6kl *ar, u32 addr, u8 *buf, u32 len)
अणु
	पूर्णांक ret;
	u32 last_word = 0;
	u32 last_word_offset = len & ~0x3;
	u32 unaligned_bytes = len & 0x3;

	ret = ath6kl_bmi_lz_stream_start(ar, addr);
	अगर (ret)
		वापस ret;

	अगर (unaligned_bytes) अणु
		/* copy the last word पूर्णांकo a zero padded buffer */
		स_नकल(&last_word, &buf[last_word_offset], unaligned_bytes);
	पूर्ण

	ret = ath6kl_bmi_lz_data(ar, buf, last_word_offset);
	अगर (ret)
		वापस ret;

	अगर (unaligned_bytes)
		ret = ath6kl_bmi_lz_data(ar, (u8 *)&last_word, 4);

	अगर (!ret) अणु
		/* Close compressed stream and खोलो a new (fake) one.
		 * This serves मुख्यly to flush Target caches. */
		ret = ath6kl_bmi_lz_stream_start(ar, 0x00);
	पूर्ण
	वापस ret;
पूर्ण

व्योम ath6kl_bmi_reset(काष्ठा ath6kl *ar)
अणु
	ar->bmi.करोne_sent = false;
पूर्ण

पूर्णांक ath6kl_bmi_init(काष्ठा ath6kl *ar)
अणु
	अगर (WARN_ON(ar->bmi.max_data_size == 0))
		वापस -EINVAL;

	/* cmd + addr + len + data_size */
	ar->bmi.max_cmd_size = ar->bmi.max_data_size + (माप(u32) * 3);

	ar->bmi.cmd_buf = kzalloc(ar->bmi.max_cmd_size, GFP_KERNEL);
	अगर (!ar->bmi.cmd_buf)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

व्योम ath6kl_bmi_cleanup(काष्ठा ath6kl *ar)
अणु
	kमुक्त(ar->bmi.cmd_buf);
	ar->bmi.cmd_buf = शून्य;
पूर्ण
