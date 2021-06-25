<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (c) 2014-2017 Qualcomm Atheros, Inc.
 * Copyright (c) 2018-2019, The Linux Foundation. All rights reserved.
 */

/* Algorithmic part of the firmware करोwnload.
 * To be included in the container file providing framework
 */

#घोषणा wil_err_fw(wil, fmt, arg...) wil_err(wil, "ERR[ FW ]" fmt, ##arg)
#घोषणा wil_dbg_fw(wil, fmt, arg...) wil_dbg(wil, "DBG[ FW ]" fmt, ##arg)
#घोषणा wil_hex_dump_fw(prefix_str, prefix_type, rowsize,		\
			groupsize, buf, len, ascii)			\
			prपूर्णांक_hex_dump_debug("DBG[ FW ]" prefix_str,	\
					     prefix_type, rowsize,	\
					     groupsize, buf, len, ascii)

अटल bool wil_fw_addr_check(काष्ठा wil6210_priv *wil,
			      व्योम __iomem **ioaddr, __le32 val,
			      u32 size, स्थिर अक्षर *msg)
अणु
	*ioaddr = wmi_buffer_block(wil, val, size);
	अगर (!(*ioaddr)) अणु
		wil_err_fw(wil, "bad %s: 0x%08x\n", msg, le32_to_cpu(val));
		वापस false;
	पूर्ण
	वापस true;
पूर्ण

/**
 * wil_fw_verअगरy - verअगरy firmware file validity
 *
 * perक्रमm various checks क्रम the firmware file header.
 * records are not validated.
 *
 * Return file size or negative error
 */
अटल पूर्णांक wil_fw_verअगरy(काष्ठा wil6210_priv *wil, स्थिर u8 *data, माप_प्रकार size)
अणु
	स्थिर काष्ठा wil_fw_record_head *hdr = (स्थिर व्योम *)data;
	काष्ठा wil_fw_record_file_header fh;
	स्थिर काष्ठा wil_fw_record_file_header *fh_;
	u32 crc;
	u32 dlen;

	अगर (size % 4) अणु
		wil_err_fw(wil, "image size not aligned: %zu\n", size);
		वापस -EINVAL;
	पूर्ण
	/* have enough data क्रम the file header? */
	अगर (size < माप(*hdr) + माप(fh)) अणु
		wil_err_fw(wil, "file too short: %zu bytes\n", size);
		वापस -EINVAL;
	पूर्ण

	/* start with the file header? */
	अगर (le16_to_cpu(hdr->type) != wil_fw_type_file_header) अणु
		wil_err_fw(wil, "no file header\n");
		वापस -EINVAL;
	पूर्ण

	/* data_len */
	fh_ = (काष्ठा wil_fw_record_file_header *)&hdr[1];
	dlen = le32_to_cpu(fh_->data_len);
	अगर (dlen % 4) अणु
		wil_err_fw(wil, "data length not aligned: %lu\n", (uदीर्घ)dlen);
		वापस -EINVAL;
	पूर्ण
	अगर (size < dlen) अणु
		wil_err_fw(wil, "file truncated at %zu/%lu\n",
			   size, (uदीर्घ)dlen);
		वापस -EINVAL;
	पूर्ण
	अगर (dlen < माप(*hdr) + माप(fh)) अणु
		wil_err_fw(wil, "data length too short: %lu\n", (uदीर्घ)dlen);
		वापस -EINVAL;
	पूर्ण

	/* signature */
	अगर (le32_to_cpu(fh_->signature) != WIL_FW_SIGNATURE) अणु
		wil_err_fw(wil, "bad header signature: 0x%08x\n",
			   le32_to_cpu(fh_->signature));
		वापस -EINVAL;
	पूर्ण

	/* version */
	अगर (le32_to_cpu(fh_->version) > WIL_FW_FMT_VERSION) अणु
		wil_err_fw(wil, "unsupported header version: %d\n",
			   le32_to_cpu(fh_->version));
		वापस -EINVAL;
	पूर्ण

	/* checksum. ~crc32(~0, data, size) when fh.crc set to 0*/
	fh = *fh_;
	fh.crc = 0;

	crc = crc32_le(~0, (अचिन्हित अक्षर स्थिर *)hdr, माप(*hdr));
	crc = crc32_le(crc, (अचिन्हित अक्षर स्थिर *)&fh, माप(fh));
	crc = crc32_le(crc, (अचिन्हित अक्षर स्थिर *)&fh_[1],
		       dlen - माप(*hdr) - माप(fh));
	crc = ~crc;

	अगर (crc != le32_to_cpu(fh_->crc)) अणु
		wil_err_fw(wil, "checksum mismatch:"
			   " calculated for %lu bytes 0x%08x != 0x%08x\n",
			   (uदीर्घ)dlen, crc, le32_to_cpu(fh_->crc));
		वापस -EINVAL;
	पूर्ण

	वापस (पूर्णांक)dlen;
पूर्ण

अटल पूर्णांक fw_ignore_section(काष्ठा wil6210_priv *wil, स्थिर व्योम *data,
			     माप_प्रकार size)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक
fw_handle_capabilities(काष्ठा wil6210_priv *wil, स्थिर व्योम *data,
		       माप_प्रकार size)
अणु
	स्थिर काष्ठा wil_fw_record_capabilities *rec = data;
	माप_प्रकार capa_size;

	अगर (size < माप(*rec)) अणु
		wil_err_fw(wil, "capabilities record too short: %zu\n", size);
		/* let the FW load anyway */
		वापस 0;
	पूर्ण

	capa_size = size - दुरत्व(काष्ठा wil_fw_record_capabilities,
				    capabilities);
	biपंचांगap_zero(wil->fw_capabilities, WMI_FW_CAPABILITY_MAX);
	स_नकल(wil->fw_capabilities, rec->capabilities,
	       min_t(माप_प्रकार, माप(wil->fw_capabilities), capa_size));
	wil_hex_dump_fw("CAPA", DUMP_PREFIX_OFFSET, 16, 1,
			rec->capabilities, capa_size, false);
	वापस 0;
पूर्ण

अटल पूर्णांक
fw_handle_brd_file(काष्ठा wil6210_priv *wil, स्थिर व्योम *data,
		   माप_प्रकार size)
अणु
	स्थिर काष्ठा wil_fw_record_brd_file *rec = data;
	u32 max_num_ent, i, ent_size;

	अगर (size <= दुरत्व(काष्ठा wil_fw_record_brd_file, brd_info)) अणु
		wil_err(wil, "board record too short, size %zu\n", size);
		वापस -EINVAL;
	पूर्ण

	ent_size = size - दुरत्व(काष्ठा wil_fw_record_brd_file, brd_info);
	max_num_ent = ent_size / माप(काष्ठा brd_info);

	अगर (!max_num_ent) अणु
		wil_err(wil, "brd info entries are missing\n");
		वापस -EINVAL;
	पूर्ण

	wil->brd_info = kसुस्मृति(max_num_ent, माप(काष्ठा wil_brd_info),
				GFP_KERNEL);
	अगर (!wil->brd_info)
		वापस -ENOMEM;

	क्रम (i = 0; i < max_num_ent; i++) अणु
		wil->brd_info[i].file_addr =
			le32_to_cpu(rec->brd_info[i].base_addr);
		wil->brd_info[i].file_max_size =
			le32_to_cpu(rec->brd_info[i].max_size_bytes);

		अगर (!wil->brd_info[i].file_addr)
			अवरोध;

		wil_dbg_fw(wil,
			   "brd info %d: file_addr 0x%x, file_max_size %d\n",
			   i, wil->brd_info[i].file_addr,
			   wil->brd_info[i].file_max_size);
	पूर्ण

	wil->num_of_brd_entries = i;
	अगर (wil->num_of_brd_entries == 0) अणु
		kमुक्त(wil->brd_info);
		wil->brd_info = शून्य;
		wil_dbg_fw(wil,
			   "no valid brd info entries, using brd file addr\n");

	पूर्ण अन्यथा अणु
		wil_dbg_fw(wil, "num of brd info entries %d\n",
			   wil->num_of_brd_entries);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
fw_handle_concurrency(काष्ठा wil6210_priv *wil, स्थिर व्योम *data,
		      माप_प्रकार size)
अणु
	स्थिर काष्ठा wil_fw_record_concurrency *rec = data;
	स्थिर काष्ठा wil_fw_concurrency_combo *combo;
	स्थिर काष्ठा wil_fw_concurrency_limit *limit;
	माप_प्रकार reमुख्य, lsize;
	पूर्णांक i, n_combos;

	अगर (size < माप(*rec)) अणु
		wil_err_fw(wil, "concurrency record too short: %zu\n", size);
		/* जारी, let the FW load anyway */
		वापस 0;
	पूर्ण

	n_combos = le16_to_cpu(rec->n_combos);
	reमुख्य = size - दुरत्व(काष्ठा wil_fw_record_concurrency, combos);
	combo = rec->combos;
	क्रम (i = 0; i < n_combos; i++) अणु
		अगर (reमुख्य < माप(*combo))
			जाओ out_लघु;
		reमुख्य -= माप(*combo);
		limit = combo->limits;
		lsize = combo->n_limits * माप(*limit);
		अगर (reमुख्य < lsize)
			जाओ out_लघु;
		reमुख्य -= lsize;
		limit += combo->n_limits;
		combo = (काष्ठा wil_fw_concurrency_combo *)limit;
	पूर्ण

	वापस wil_cfg80211_अगरace_combinations_from_fw(wil, rec);
out_लघु:
	wil_err_fw(wil, "concurrency record truncated\n");
	वापस 0;
पूर्ण

अटल पूर्णांक
fw_handle_comment(काष्ठा wil6210_priv *wil, स्थिर व्योम *data,
		  माप_प्रकार size)
अणु
	स्थिर काष्ठा wil_fw_record_comment_hdr *hdr = data;
	u32 magic;
	पूर्णांक rc = 0;

	अगर (size < माप(*hdr))
		वापस 0;

	magic = le32_to_cpu(hdr->magic);

	चयन (magic) अणु
	हाल WIL_FW_CAPABILITIES_MAGIC:
		wil_dbg_fw(wil, "magic is WIL_FW_CAPABILITIES_MAGIC\n");
		rc = fw_handle_capabilities(wil, data, size);
		अवरोध;
	हाल WIL_BRD_खाता_MAGIC:
		wil_dbg_fw(wil, "magic is WIL_BRD_FILE_MAGIC\n");
		rc = fw_handle_brd_file(wil, data, size);
		अवरोध;
	हाल WIL_FW_CONCURRENCY_MAGIC:
		wil_dbg_fw(wil, "magic is WIL_FW_CONCURRENCY_MAGIC\n");
		rc = fw_handle_concurrency(wil, data, size);
		अवरोध;
	शेष:
		wil_hex_dump_fw("", DUMP_PREFIX_OFFSET, 16, 1,
				data, size, true);
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक __fw_handle_data(काष्ठा wil6210_priv *wil, स्थिर व्योम *data,
			    माप_प्रकार size, __le32 addr)
अणु
	स्थिर काष्ठा wil_fw_record_data *d = data;
	व्योम __iomem *dst;
	माप_प्रकार s = size - माप(*d);

	अगर (size < माप(*d) + माप(u32)) अणु
		wil_err_fw(wil, "data record too short: %zu\n", size);
		वापस -EINVAL;
	पूर्ण

	अगर (!wil_fw_addr_check(wil, &dst, addr, s, "address"))
		वापस -EINVAL;
	wil_dbg_fw(wil, "write [0x%08x] <== %zu bytes\n", le32_to_cpu(addr), s);
	wil_स_नकल_toio_32(dst, d->data, s);
	wmb(); /* finish beक्रमe processing next record */

	वापस 0;
पूर्ण

अटल पूर्णांक fw_handle_data(काष्ठा wil6210_priv *wil, स्थिर व्योम *data,
			  माप_प्रकार size)
अणु
	स्थिर काष्ठा wil_fw_record_data *d = data;

	वापस __fw_handle_data(wil, data, size, d->addr);
पूर्ण

अटल पूर्णांक fw_handle_fill(काष्ठा wil6210_priv *wil, स्थिर व्योम *data,
			  माप_प्रकार size)
अणु
	स्थिर काष्ठा wil_fw_record_fill *d = data;
	व्योम __iomem *dst;
	u32 v;
	माप_प्रकार s = (माप_प्रकार)le32_to_cpu(d->size);

	अगर (size != माप(*d)) अणु
		wil_err_fw(wil, "bad size for fill record: %zu\n", size);
		वापस -EINVAL;
	पूर्ण

	अगर (s < माप(u32)) अणु
		wil_err_fw(wil, "fill size too short: %zu\n", s);
		वापस -EINVAL;
	पूर्ण

	अगर (s % माप(u32)) अणु
		wil_err_fw(wil, "fill size not aligned: %zu\n", s);
		वापस -EINVAL;
	पूर्ण

	अगर (!wil_fw_addr_check(wil, &dst, d->addr, s, "address"))
		वापस -EINVAL;

	v = le32_to_cpu(d->value);
	wil_dbg_fw(wil, "fill [0x%08x] <== 0x%08x, %zu bytes\n",
		   le32_to_cpu(d->addr), v, s);
	wil_स_रखो_toio_32(dst, v, s);
	wmb(); /* finish beक्रमe processing next record */

	वापस 0;
पूर्ण

अटल पूर्णांक fw_handle_file_header(काष्ठा wil6210_priv *wil, स्थिर व्योम *data,
				 माप_प्रकार size)
अणु
	स्थिर काष्ठा wil_fw_record_file_header *d = data;

	अगर (size != माप(*d)) अणु
		wil_err_fw(wil, "file header length incorrect: %zu\n", size);
		वापस -EINVAL;
	पूर्ण

	wil_dbg_fw(wil, "new file, ver. %d, %i bytes\n",
		   d->version, d->data_len);
	wil_hex_dump_fw("", DUMP_PREFIX_OFFSET, 16, 1, d->comment,
			माप(d->comment), true);

	अगर (!स_भेद(d->comment, WIL_FW_VERSION_PREFIX,
		    WIL_FW_VERSION_PREFIX_LEN))
		स_नकल(wil->fw_version,
		       d->comment + WIL_FW_VERSION_PREFIX_LEN,
		       min(माप(d->comment) - WIL_FW_VERSION_PREFIX_LEN,
			   माप(wil->fw_version) - 1));

	वापस 0;
पूर्ण

अटल पूर्णांक fw_handle_direct_ग_लिखो(काष्ठा wil6210_priv *wil, स्थिर व्योम *data,
				  माप_प्रकार size)
अणु
	स्थिर काष्ठा wil_fw_record_direct_ग_लिखो *d = data;
	स्थिर काष्ठा wil_fw_data_dग_लिखो *block = d->data;
	पूर्णांक n, i;

	अगर (size % माप(*block)) अणु
		wil_err_fw(wil, "record size not aligned on %zu: %zu\n",
			   माप(*block), size);
		वापस -EINVAL;
	पूर्ण
	n = size / माप(*block);

	क्रम (i = 0; i < n; i++) अणु
		व्योम __iomem *dst;
		u32 m = le32_to_cpu(block[i].mask);
		u32 v = le32_to_cpu(block[i].value);
		u32 x, y;

		अगर (!wil_fw_addr_check(wil, &dst, block[i].addr, 0, "address"))
			वापस -EINVAL;

		x = पढ़ोl(dst);
		y = (x & m) | (v & ~m);
		wil_dbg_fw(wil, "write [0x%08x] <== 0x%08x "
			   "(old 0x%08x val 0x%08x mask 0x%08x)\n",
			   le32_to_cpu(block[i].addr), y, x, v, m);
		ग_लिखोl(y, dst);
		wmb(); /* finish beक्रमe processing next record */
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक gw_ग_लिखो(काष्ठा wil6210_priv *wil, व्योम __iomem *gwa_addr,
		    व्योम __iomem *gwa_cmd, व्योम __iomem *gwa_ctl, u32 gw_cmd,
		    u32 a)
अणु
	अचिन्हित delay = 0;

	ग_लिखोl(a, gwa_addr);
	ग_लिखोl(gw_cmd, gwa_cmd);
	wmb(); /* finish beक्रमe activate gw */

	ग_लिखोl(WIL_FW_GW_CTL_RUN, gwa_ctl); /* activate gw */
	करो अणु
		udelay(1); /* typical समय is few usec */
		अगर (delay++ > 100) अणु
			wil_err_fw(wil, "gw timeout\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण जबतक (पढ़ोl(gwa_ctl) & WIL_FW_GW_CTL_BUSY); /* gw करोne? */

	वापस 0;
पूर्ण

अटल पूर्णांक fw_handle_gateway_data(काष्ठा wil6210_priv *wil, स्थिर व्योम *data,
				  माप_प्रकार size)
अणु
	स्थिर काष्ठा wil_fw_record_gateway_data *d = data;
	स्थिर काष्ठा wil_fw_data_gw *block = d->data;
	व्योम __iomem *gwa_addr;
	व्योम __iomem *gwa_val;
	व्योम __iomem *gwa_cmd;
	व्योम __iomem *gwa_ctl;
	u32 gw_cmd;
	पूर्णांक n, i;

	अगर (size < माप(*d) + माप(*block)) अणु
		wil_err_fw(wil, "gateway record too short: %zu\n", size);
		वापस -EINVAL;
	पूर्ण

	अगर ((size - माप(*d)) % माप(*block)) अणु
		wil_err_fw(wil, "gateway record data size"
			   " not aligned on %zu: %zu\n",
			   माप(*block), size - माप(*d));
		वापस -EINVAL;
	पूर्ण
	n = (size - माप(*d)) / माप(*block);

	gw_cmd = le32_to_cpu(d->command);

	wil_dbg_fw(wil, "gw write record [%3d] blocks, cmd 0x%08x\n",
		   n, gw_cmd);

	अगर (!wil_fw_addr_check(wil, &gwa_addr, d->gateway_addr_addr, 0,
			       "gateway_addr_addr") ||
	    !wil_fw_addr_check(wil, &gwa_val, d->gateway_value_addr, 0,
			       "gateway_value_addr") ||
	    !wil_fw_addr_check(wil, &gwa_cmd, d->gateway_cmd_addr, 0,
			       "gateway_cmd_addr") ||
	    !wil_fw_addr_check(wil, &gwa_ctl, d->gateway_ctrl_address, 0,
			       "gateway_ctrl_address"))
		वापस -EINVAL;

	wil_dbg_fw(wil, "gw addresses: addr 0x%08x val 0x%08x"
		   " cmd 0x%08x ctl 0x%08x\n",
		   le32_to_cpu(d->gateway_addr_addr),
		   le32_to_cpu(d->gateway_value_addr),
		   le32_to_cpu(d->gateway_cmd_addr),
		   le32_to_cpu(d->gateway_ctrl_address));

	क्रम (i = 0; i < n; i++) अणु
		पूर्णांक rc;
		u32 a = le32_to_cpu(block[i].addr);
		u32 v = le32_to_cpu(block[i].value);

		wil_dbg_fw(wil, "  gw write[%3d] [0x%08x] <== 0x%08x\n",
			   i, a, v);

		ग_लिखोl(v, gwa_val);
		rc = gw_ग_लिखो(wil, gwa_addr, gwa_cmd, gwa_ctl, gw_cmd, a);
		अगर (rc)
			वापस rc;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक fw_handle_gateway_data4(काष्ठा wil6210_priv *wil, स्थिर व्योम *data,
				   माप_प्रकार size)
अणु
	स्थिर काष्ठा wil_fw_record_gateway_data4 *d = data;
	स्थिर काष्ठा wil_fw_data_gw4 *block = d->data;
	व्योम __iomem *gwa_addr;
	व्योम __iomem *gwa_val[ARRAY_SIZE(block->value)];
	व्योम __iomem *gwa_cmd;
	व्योम __iomem *gwa_ctl;
	u32 gw_cmd;
	पूर्णांक n, i, k;

	अगर (size < माप(*d) + माप(*block)) अणु
		wil_err_fw(wil, "gateway4 record too short: %zu\n", size);
		वापस -EINVAL;
	पूर्ण

	अगर ((size - माप(*d)) % माप(*block)) अणु
		wil_err_fw(wil, "gateway4 record data size"
			   " not aligned on %zu: %zu\n",
			   माप(*block), size - माप(*d));
		वापस -EINVAL;
	पूर्ण
	n = (size - माप(*d)) / माप(*block);

	gw_cmd = le32_to_cpu(d->command);

	wil_dbg_fw(wil, "gw4 write record [%3d] blocks, cmd 0x%08x\n",
		   n, gw_cmd);

	अगर (!wil_fw_addr_check(wil, &gwa_addr, d->gateway_addr_addr, 0,
			       "gateway_addr_addr"))
		वापस -EINVAL;
	क्रम (k = 0; k < ARRAY_SIZE(block->value); k++)
		अगर (!wil_fw_addr_check(wil, &gwa_val[k],
				       d->gateway_value_addr[k],
				       0, "gateway_value_addr"))
			वापस -EINVAL;
	अगर (!wil_fw_addr_check(wil, &gwa_cmd, d->gateway_cmd_addr, 0,
			       "gateway_cmd_addr") ||
	    !wil_fw_addr_check(wil, &gwa_ctl, d->gateway_ctrl_address, 0,
			       "gateway_ctrl_address"))
		वापस -EINVAL;

	wil_dbg_fw(wil, "gw4 addresses: addr 0x%08x cmd 0x%08x ctl 0x%08x\n",
		   le32_to_cpu(d->gateway_addr_addr),
		   le32_to_cpu(d->gateway_cmd_addr),
		   le32_to_cpu(d->gateway_ctrl_address));
	wil_hex_dump_fw("val addresses: ", DUMP_PREFIX_NONE, 16, 4,
			d->gateway_value_addr, माप(d->gateway_value_addr),
			false);

	क्रम (i = 0; i < n; i++) अणु
		पूर्णांक rc;
		u32 a = le32_to_cpu(block[i].addr);
		u32 v[ARRAY_SIZE(block->value)];

		क्रम (k = 0; k < ARRAY_SIZE(block->value); k++)
			v[k] = le32_to_cpu(block[i].value[k]);

		wil_dbg_fw(wil, "  gw4 write[%3d] [0x%08x] <==\n", i, a);
		wil_hex_dump_fw("    val ", DUMP_PREFIX_NONE, 16, 4, v,
				माप(v), false);

		क्रम (k = 0; k < ARRAY_SIZE(block->value); k++)
			ग_लिखोl(v[k], gwa_val[k]);
		rc = gw_ग_लिखो(wil, gwa_addr, gwa_cmd, gwa_ctl, gw_cmd, a);
		अगर (rc)
			वापस rc;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा अणु
	पूर्णांक type;
	पूर्णांक (*load_handler)(काष्ठा wil6210_priv *wil, स्थिर व्योम *data,
			    माप_प्रकार size);
	पूर्णांक (*parse_handler)(काष्ठा wil6210_priv *wil, स्थिर व्योम *data,
			     माप_प्रकार size);
पूर्ण wil_fw_handlers[] = अणु
	अणुwil_fw_type_comment, fw_handle_comment, fw_handle_commentपूर्ण,
	अणुwil_fw_type_data, fw_handle_data, fw_ignore_sectionपूर्ण,
	अणुwil_fw_type_fill, fw_handle_fill, fw_ignore_sectionपूर्ण,
	/* wil_fw_type_action */
	/* wil_fw_type_verअगरy */
	अणुwil_fw_type_file_header, fw_handle_file_header,
		fw_handle_file_headerपूर्ण,
	अणुwil_fw_type_direct_ग_लिखो, fw_handle_direct_ग_लिखो, fw_ignore_sectionपूर्ण,
	अणुwil_fw_type_gateway_data, fw_handle_gateway_data, fw_ignore_sectionपूर्ण,
	अणुwil_fw_type_gateway_data4, fw_handle_gateway_data4,
		fw_ignore_sectionपूर्ण,
पूर्ण;

अटल पूर्णांक wil_fw_handle_record(काष्ठा wil6210_priv *wil, पूर्णांक type,
				स्थिर व्योम *data, माप_प्रकार size, bool load)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(wil_fw_handlers); i++)
		अगर (wil_fw_handlers[i].type == type)
			वापस load ?
				wil_fw_handlers[i].load_handler(
					wil, data, size) :
				wil_fw_handlers[i].parse_handler(
					wil, data, size);

	wil_err_fw(wil, "unknown record type: %d\n", type);
	वापस -EINVAL;
पूर्ण

/**
 * wil_fw_process - process section from FW file
 * अगर load is true: Load the FW and uCode code and data to the
 * corresponding device memory regions,
 * otherwise only parse and look क्रम capabilities
 *
 * Return error code
 */
अटल पूर्णांक wil_fw_process(काष्ठा wil6210_priv *wil, स्थिर व्योम *data,
			  माप_प्रकार size, bool load)
अणु
	पूर्णांक rc = 0;
	स्थिर काष्ठा wil_fw_record_head *hdr;
	माप_प्रकार s, hdr_sz;

	क्रम (hdr = data;; hdr = (स्थिर व्योम *)hdr + s, size -= s) अणु
		अगर (size < माप(*hdr))
			अवरोध;
		hdr_sz = le32_to_cpu(hdr->size);
		s = माप(*hdr) + hdr_sz;
		अगर (s > size)
			अवरोध;
		अगर (hdr_sz % 4) अणु
			wil_err_fw(wil, "unaligned record size: %zu\n",
				   hdr_sz);
			वापस -EINVAL;
		पूर्ण
		rc = wil_fw_handle_record(wil, le16_to_cpu(hdr->type),
					  &hdr[1], hdr_sz, load);
		अगर (rc)
			वापस rc;
	पूर्ण
	अगर (size) अणु
		wil_err_fw(wil, "unprocessed bytes: %zu\n", size);
		अगर (size >= माप(*hdr)) अणु
			wil_err_fw(wil, "Stop at offset %ld"
				   " record type %d [%zd bytes]\n",
				   (दीर्घ)((स्थिर व्योम *)hdr - data),
				   le16_to_cpu(hdr->type), hdr_sz);
		पूर्ण
		वापस -EINVAL;
	पूर्ण

	वापस rc;
पूर्ण

/**
 * wil_request_firmware - Request firmware
 *
 * Request firmware image from the file
 * If load is true, load firmware to device, otherwise
 * only parse and extract capabilities
 *
 * Return error code
 */
पूर्णांक wil_request_firmware(काष्ठा wil6210_priv *wil, स्थिर अक्षर *name,
			 bool load)
अणु
	पूर्णांक rc, rc1;
	स्थिर काष्ठा firmware *fw;
	माप_प्रकार sz;
	स्थिर व्योम *d;

	rc = request_firmware(&fw, name, wil_to_dev(wil));
	अगर (rc) अणु
		wil_err_fw(wil, "Failed to load firmware %s rc %d\n", name, rc);
		वापस rc;
	पूर्ण
	wil_dbg_fw(wil, "Loading <%s>, %zu bytes\n", name, fw->size);

	/* re-initialize board info params */
	wil->num_of_brd_entries = 0;
	kमुक्त(wil->brd_info);
	wil->brd_info = शून्य;

	क्रम (sz = fw->size, d = fw->data; sz; sz -= rc1, d += rc1) अणु
		rc1 = wil_fw_verअगरy(wil, d, sz);
		अगर (rc1 < 0) अणु
			rc = rc1;
			जाओ out;
		पूर्ण
		rc = wil_fw_process(wil, d, rc1, load);
		अगर (rc < 0)
			जाओ out;
	पूर्ण

out:
	release_firmware(fw);
	अगर (rc)
		wil_err_fw(wil, "Loading <%s> failed, rc %d\n", name, rc);
	वापस rc;
पूर्ण

/**
 * wil_brd_process - process section from BRD file
 *
 * Return error code
 */
अटल पूर्णांक wil_brd_process(काष्ठा wil6210_priv *wil, स्थिर व्योम *data,
			   माप_प्रकार size)
अणु
	पूर्णांक rc = 0;
	स्थिर काष्ठा wil_fw_record_head *hdr = data;
	माप_प्रकार s, hdr_sz = 0;
	u16 type;
	पूर्णांक i = 0;

	/* Assuming the board file includes only one file header
	 * and one or several data records.
	 * Each record starts with wil_fw_record_head.
	 */
	अगर (size < माप(*hdr))
		वापस -EINVAL;
	s = माप(*hdr) + le32_to_cpu(hdr->size);
	अगर (s > size)
		वापस -EINVAL;

	/* Skip the header record and handle the data records */
	size -= s;

	क्रम (hdr = data + s;; hdr = (स्थिर व्योम *)hdr + s, size -= s, i++) अणु
		अगर (size < माप(*hdr))
			अवरोध;

		अगर (i >= wil->num_of_brd_entries) अणु
			wil_err_fw(wil,
				   "Too many brd records: %d, num of expected entries %d\n",
				   i, wil->num_of_brd_entries);
			अवरोध;
		पूर्ण

		hdr_sz = le32_to_cpu(hdr->size);
		s = माप(*hdr) + hdr_sz;
		अगर (wil->brd_info[i].file_max_size &&
		    hdr_sz > wil->brd_info[i].file_max_size)
			वापस -EINVAL;
		अगर (माप(*hdr) + hdr_sz > size)
			वापस -EINVAL;
		अगर (hdr_sz % 4) अणु
			wil_err_fw(wil, "unaligned record size: %zu\n",
				   hdr_sz);
			वापस -EINVAL;
		पूर्ण
		type = le16_to_cpu(hdr->type);
		अगर (type != wil_fw_type_data) अणु
			wil_err_fw(wil,
				   "invalid record type for board file: %d\n",
				   type);
			वापस -EINVAL;
		पूर्ण
		अगर (hdr_sz < माप(काष्ठा wil_fw_record_data)) अणु
			wil_err_fw(wil, "data record too short: %zu\n", hdr_sz);
			वापस -EINVAL;
		पूर्ण

		wil_dbg_fw(wil,
			   "using info from fw file for record %d: addr[0x%08x], max size %d\n",
			   i, wil->brd_info[i].file_addr,
			   wil->brd_info[i].file_max_size);

		rc = __fw_handle_data(wil, &hdr[1], hdr_sz,
				      cpu_to_le32(wil->brd_info[i].file_addr));
		अगर (rc)
			वापस rc;
	पूर्ण

	अगर (size) अणु
		wil_err_fw(wil, "unprocessed bytes: %zu\n", size);
		अगर (size >= माप(*hdr)) अणु
			wil_err_fw(wil,
				   "Stop at offset %ld record type %d [%zd bytes]\n",
				   (दीर्घ)((स्थिर व्योम *)hdr - data),
				   le16_to_cpu(hdr->type), hdr_sz);
		पूर्ण
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * wil_request_board - Request board file
 *
 * Request board image from the file
 * board file address and max size are पढ़ो from FW file
 * during initialization.
 * brd file shall include one header and one data section.
 *
 * Return error code
 */
पूर्णांक wil_request_board(काष्ठा wil6210_priv *wil, स्थिर अक्षर *name)
अणु
	पूर्णांक rc, dlen;
	स्थिर काष्ठा firmware *brd;

	rc = request_firmware(&brd, name, wil_to_dev(wil));
	अगर (rc) अणु
		wil_err_fw(wil, "Failed to load brd %s\n", name);
		वापस rc;
	पूर्ण
	wil_dbg_fw(wil, "Loading <%s>, %zu bytes\n", name, brd->size);

	/* Verअगरy the header */
	dlen = wil_fw_verअगरy(wil, brd->data, brd->size);
	अगर (dlen < 0) अणु
		rc = dlen;
		जाओ out;
	पूर्ण

	/* Process the data records */
	rc = wil_brd_process(wil, brd->data, dlen);

out:
	release_firmware(brd);
	अगर (rc)
		wil_err_fw(wil, "Loading <%s> failed, rc %d\n", name, rc);
	वापस rc;
पूर्ण

/**
 * wil_fw_verअगरy_file_exists - checks अगर firmware file exist
 *
 * @wil: driver context
 * @name: firmware file name
 *
 * वापस value - boolean, true क्रम success, false क्रम failure
 */
bool wil_fw_verअगरy_file_exists(काष्ठा wil6210_priv *wil, स्थिर अक्षर *name)
अणु
	स्थिर काष्ठा firmware *fw;
	पूर्णांक rc;

	rc = request_firmware(&fw, name, wil_to_dev(wil));
	अगर (!rc)
		release_firmware(fw);
	अन्यथा
		wil_dbg_fw(wil, "<%s> not available: %d\n", name, rc);
	वापस !rc;
पूर्ण
