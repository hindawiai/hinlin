<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause
/*
 * Copyright(c) 2020-2021 Intel Corporation
 */

#समावेश "iwl-drv.h"
#समावेश "pnvm.h"
#समावेश "iwl-prph.h"
#समावेश "iwl-io.h"
#समावेश "fw/api/commands.h"
#समावेश "fw/api/nvm-reg.h"
#समावेश "fw/api/alive.h"
#समावेश <linux/efi.h>

काष्ठा iwl_pnvm_section अणु
	__le32 offset;
	स्थिर u8 data[];
पूर्ण __packed;

अटल bool iwl_pnvm_complete_fn(काष्ठा iwl_notअगर_रुको_data *notअगर_रुको,
				 काष्ठा iwl_rx_packet *pkt, व्योम *data)
अणु
	काष्ठा iwl_trans *trans = (काष्ठा iwl_trans *)data;
	काष्ठा iwl_pnvm_init_complete_ntfy *pnvm_ntf = (व्योम *)pkt->data;

	IWL_DEBUG_FW(trans,
		     "PNVM complete notification received with status %d\n",
		     le32_to_cpu(pnvm_ntf->status));

	वापस true;
पूर्ण

अटल पूर्णांक iwl_pnvm_handle_section(काष्ठा iwl_trans *trans, स्थिर u8 *data,
				   माप_प्रकार len)
अणु
	काष्ठा iwl_ucode_tlv *tlv;
	u32 sha1 = 0;
	u16 mac_type = 0, rf_id = 0;
	u8 *pnvm_data = शून्य, *पंचांगp;
	u32 size = 0;
	पूर्णांक ret;

	IWL_DEBUG_FW(trans, "Handling PNVM section\n");

	जबतक (len >= माप(*tlv)) अणु
		u32 tlv_len, tlv_type;

		len -= माप(*tlv);
		tlv = (व्योम *)data;

		tlv_len = le32_to_cpu(tlv->length);
		tlv_type = le32_to_cpu(tlv->type);

		अगर (len < tlv_len) अणु
			IWL_ERR(trans, "invalid TLV len: %zd/%u\n",
				len, tlv_len);
			ret = -EINVAL;
			जाओ out;
		पूर्ण

		data += माप(*tlv);

		चयन (tlv_type) अणु
		हाल IWL_UCODE_TLV_PNVM_VERSION:
			अगर (tlv_len < माप(__le32)) अणु
				IWL_DEBUG_FW(trans,
					     "Invalid size for IWL_UCODE_TLV_PNVM_VERSION (expected %zd, got %d)\n",
					     माप(__le32), tlv_len);
				अवरोध;
			पूर्ण

			sha1 = le32_to_cpup((__le32 *)data);

			IWL_DEBUG_FW(trans,
				     "Got IWL_UCODE_TLV_PNVM_VERSION %0x\n",
				     sha1);
			अवरोध;
		हाल IWL_UCODE_TLV_HW_TYPE:
			अगर (tlv_len < 2 * माप(__le16)) अणु
				IWL_DEBUG_FW(trans,
					     "Invalid size for IWL_UCODE_TLV_HW_TYPE (expected %zd, got %d)\n",
					     2 * माप(__le16), tlv_len);
				अवरोध;
			पूर्ण

			mac_type = le16_to_cpup((__le16 *)data);
			rf_id = le16_to_cpup((__le16 *)(data + माप(__le16)));

			IWL_DEBUG_FW(trans,
				     "Got IWL_UCODE_TLV_HW_TYPE mac_type 0x%0x rf_id 0x%0x\n",
				     mac_type, rf_id);

			अगर (mac_type != CSR_HW_REV_TYPE(trans->hw_rev) ||
			    rf_id != CSR_HW_RFID_TYPE(trans->hw_rf_id)) अणु
				IWL_DEBUG_FW(trans,
					     "HW mismatch, skipping PNVM section, mac_type 0x%0x, rf_id 0x%0x.\n",
					     CSR_HW_REV_TYPE(trans->hw_rev), trans->hw_rf_id);
				ret = -ENOENT;
				जाओ out;
			पूर्ण

			अवरोध;
		हाल IWL_UCODE_TLV_SEC_RT: अणु
			काष्ठा iwl_pnvm_section *section = (व्योम *)data;
			u32 data_len = tlv_len - माप(*section);

			IWL_DEBUG_FW(trans,
				     "Got IWL_UCODE_TLV_SEC_RT len %d\n",
				     tlv_len);

			/* TODO: हटाओ, this is a deprecated separator */
			अगर (le32_to_cpup((__le32 *)data) == 0xddddeeee) अणु
				IWL_DEBUG_FW(trans, "Ignoring separator.\n");
				अवरोध;
			पूर्ण

			IWL_DEBUG_FW(trans, "Adding data (size %d)\n",
				     data_len);

			पंचांगp = kपुनः_स्मृति(pnvm_data, size + data_len, GFP_KERNEL);
			अगर (!पंचांगp) अणु
				IWL_DEBUG_FW(trans,
					     "Couldn't allocate (more) pnvm_data\n");

				ret = -ENOMEM;
				जाओ out;
			पूर्ण

			pnvm_data = पंचांगp;

			स_नकल(pnvm_data + size, section->data, data_len);

			size += data_len;

			अवरोध;
		पूर्ण
		हाल IWL_UCODE_TLV_PNVM_SKU:
			IWL_DEBUG_FW(trans,
				     "New PNVM section started, stop parsing.\n");
			जाओ करोne;
		शेष:
			IWL_DEBUG_FW(trans, "Found TLV 0x%0x, len %d\n",
				     tlv_type, tlv_len);
			अवरोध;
		पूर्ण

		len -= ALIGN(tlv_len, 4);
		data += ALIGN(tlv_len, 4);
	पूर्ण

करोne:
	अगर (!size) अणु
		IWL_DEBUG_FW(trans, "Empty PNVM, skipping.\n");
		ret = -ENOENT;
		जाओ out;
	पूर्ण

	IWL_INFO(trans, "loaded PNVM version 0x%0x\n", sha1);

	ret = iwl_trans_set_pnvm(trans, pnvm_data, size);
out:
	kमुक्त(pnvm_data);
	वापस ret;
पूर्ण

अटल पूर्णांक iwl_pnvm_parse(काष्ठा iwl_trans *trans, स्थिर u8 *data,
			  माप_प्रकार len)
अणु
	काष्ठा iwl_ucode_tlv *tlv;

	IWL_DEBUG_FW(trans, "Parsing PNVM file\n");

	जबतक (len >= माप(*tlv)) अणु
		u32 tlv_len, tlv_type;

		len -= माप(*tlv);
		tlv = (व्योम *)data;

		tlv_len = le32_to_cpu(tlv->length);
		tlv_type = le32_to_cpu(tlv->type);

		अगर (len < tlv_len) अणु
			IWL_ERR(trans, "invalid TLV len: %zd/%u\n",
				len, tlv_len);
			वापस -EINVAL;
		पूर्ण

		अगर (tlv_type == IWL_UCODE_TLV_PNVM_SKU) अणु
			काष्ठा iwl_sku_id *sku_id =
				(व्योम *)(data + माप(*tlv));

			IWL_DEBUG_FW(trans,
				     "Got IWL_UCODE_TLV_PNVM_SKU len %d\n",
				     tlv_len);
			IWL_DEBUG_FW(trans, "sku_id 0x%0x 0x%0x 0x%0x\n",
				     le32_to_cpu(sku_id->data[0]),
				     le32_to_cpu(sku_id->data[1]),
				     le32_to_cpu(sku_id->data[2]));

			data += माप(*tlv) + ALIGN(tlv_len, 4);
			len -= ALIGN(tlv_len, 4);

			अगर (trans->sku_id[0] == le32_to_cpu(sku_id->data[0]) &&
			    trans->sku_id[1] == le32_to_cpu(sku_id->data[1]) &&
			    trans->sku_id[2] == le32_to_cpu(sku_id->data[2])) अणु
				पूर्णांक ret;

				ret = iwl_pnvm_handle_section(trans, data, len);
				अगर (!ret)
					वापस 0;
			पूर्ण अन्यथा अणु
				IWL_DEBUG_FW(trans, "SKU ID didn't match!\n");
			पूर्ण
		पूर्ण अन्यथा अणु
			data += माप(*tlv) + ALIGN(tlv_len, 4);
			len -= ALIGN(tlv_len, 4);
		पूर्ण
	पूर्ण

	वापस -ENOENT;
पूर्ण

#अगर defined(CONFIG_EFI)

#घोषणा IWL_EFI_VAR_GUID EFI_GUID(0x92daaf2f, 0xc02b, 0x455b,	\
				  0xb2, 0xec, 0xf5, 0xa3,	\
				  0x59, 0x4f, 0x4a, 0xea)

#घोषणा IWL_UEFI_OEM_PNVM_NAME	L"UefiCnvWlanOemSignedPnvm"

#घोषणा IWL_HARDCODED_PNVM_SIZE 4096

काष्ठा pnvm_sku_package अणु
	u8 rev;
	u8 reserved1[3];
	u32 total_size;
	u8 n_skus;
	u8 reserved2[11];
	u8 data[];
पूर्ण;

अटल पूर्णांक iwl_pnvm_get_from_efi(काष्ठा iwl_trans *trans,
				 u8 **data, माप_प्रकार *len)
अणु
	काष्ठा efivar_entry *pnvm_efivar;
	काष्ठा pnvm_sku_package *package;
	अचिन्हित दीर्घ package_size;
	पूर्णांक err;

	pnvm_efivar = kzalloc(माप(*pnvm_efivar), GFP_KERNEL);
	अगर (!pnvm_efivar)
		वापस -ENOMEM;

	स_नकल(&pnvm_efivar->var.VariableName, IWL_UEFI_OEM_PNVM_NAME,
	       माप(IWL_UEFI_OEM_PNVM_NAME));
	pnvm_efivar->var.VenकरोrGuid = IWL_EFI_VAR_GUID;

	/*
	 * TODO: we hardcode a maximum length here, because पढ़ोing
	 * from the UEFI is not working.  To implement this properly,
	 * we have to call efivar_entry_size().
	 */
	package_size = IWL_HARDCODED_PNVM_SIZE;

	package = kदो_स्मृति(package_size, GFP_KERNEL);
	अगर (!package) अणु
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	err = efivar_entry_get(pnvm_efivar, शून्य, &package_size, package);
	अगर (err) अणु
		IWL_DEBUG_FW(trans,
			     "PNVM UEFI variable not found %d (len %lu)\n",
			     err, package_size);
		जाओ out;
	पूर्ण

	IWL_DEBUG_FW(trans, "Read PNVM fro UEFI with size %lu\n", package_size);

	*data = kmemdup(package->data, *len, GFP_KERNEL);
	अगर (!*data)
		err = -ENOMEM;
	*len = package_size - माप(*package);

out:
	kमुक्त(package);
	kमुक्त(pnvm_efivar);

	वापस err;
पूर्ण
#अन्यथा /* CONFIG_EFI */
अटल अंतरभूत पूर्णांक iwl_pnvm_get_from_efi(काष्ठा iwl_trans *trans,
					u8 **data, माप_प्रकार *len)
अणु
	वापस -EOPNOTSUPP;
पूर्ण
#पूर्ण_अगर /* CONFIG_EFI */

अटल पूर्णांक iwl_pnvm_get_from_fs(काष्ठा iwl_trans *trans, u8 **data, माप_प्रकार *len)
अणु
	स्थिर काष्ठा firmware *pnvm;
	अक्षर pnvm_name[64];
	पूर्णांक ret;

	/*
	 * The prefix unक्रमtunately includes a hyphen at the end, so
	 * करोn't add the करोt here...
	 */
	snम_लिखो(pnvm_name, माप(pnvm_name), "%spnvm",
		 trans->cfg->fw_name_pre);

	/* ...but replace the hyphen with the करोt here. */
	अगर (म_माप(trans->cfg->fw_name_pre) < माप(pnvm_name))
		pnvm_name[म_माप(trans->cfg->fw_name_pre) - 1] = '.';

	ret = firmware_request_nowarn(&pnvm, pnvm_name, trans->dev);
	अगर (ret) अणु
		IWL_DEBUG_FW(trans, "PNVM file %s not found %d\n",
			     pnvm_name, ret);
		वापस ret;
	पूर्ण

	*data = kmemdup(pnvm->data, pnvm->size, GFP_KERNEL);
	अगर (!*data)
		वापस -ENOMEM;

	*len = pnvm->size;

	वापस 0;
पूर्ण

पूर्णांक iwl_pnvm_load(काष्ठा iwl_trans *trans,
		  काष्ठा iwl_notअगर_रुको_data *notअगर_रुको)
अणु
	u8 *data;
	माप_प्रकार len;
	काष्ठा iwl_notअगरication_रुको pnvm_रुको;
	अटल स्थिर u16 ntf_cmds[] = अणु WIDE_ID(REGULATORY_AND_NVM_GROUP,
						PNVM_INIT_COMPLETE_NTFY) पूर्ण;
	पूर्णांक ret;

	/* अगर the SKU_ID is empty, there's nothing to करो */
	अगर (!trans->sku_id[0] && !trans->sku_id[1] && !trans->sku_id[2])
		वापस 0;

	/*
	 * If we alपढ़ोy loaded (or tried to load) it beक्रमe, we just
	 * need to set it again.
	 */
	अगर (trans->pnvm_loaded) अणु
		ret = iwl_trans_set_pnvm(trans, शून्य, 0);
		अगर (ret)
			वापस ret;
		जाओ skip_parse;
	पूर्ण

	/* First attempt to get the PNVM from BIOS */
	ret = iwl_pnvm_get_from_efi(trans, &data, &len);
	अगर (!ret)
		जाओ parse;

	/* If it's not available, try from the fileप्रणाली */
	ret = iwl_pnvm_get_from_fs(trans, &data, &len);
	अगर (ret) अणु
		/*
		 * Pretend we've loaded it - at least we've tried and
		 * couldn't load it at all, so there's no poपूर्णांक in
		 * trying again over and over.
		 */
		trans->pnvm_loaded = true;

		जाओ skip_parse;
	पूर्ण

parse:
	iwl_pnvm_parse(trans, data, len);

	kमुक्त(data);

skip_parse:
	iwl_init_notअगरication_रुको(notअगर_रुको, &pnvm_रुको,
				   ntf_cmds, ARRAY_SIZE(ntf_cmds),
				   iwl_pnvm_complete_fn, trans);

	/* kick the करोorbell */
	iwl_ग_लिखो_umac_prph(trans, UREG_DOORBELL_TO_ISR6,
			    UREG_DOORBELL_TO_ISR6_PNVM);

	वापस iwl_रुको_notअगरication(notअगर_रुको, &pnvm_रुको,
				     MVM_UCODE_PNVM_TIMEOUT);
पूर्ण
IWL_EXPORT_SYMBOL(iwl_pnvm_load);
