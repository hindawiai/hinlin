<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause
/*
 * Copyright (C) 2005-2014, 2018-2021 Intel Corporation
 * Copyright (C) 2013-2015 Intel Mobile Communications GmbH
 * Copyright (C) 2016-2017 Intel Deutschland GmbH
 */
#समावेश <linux/completion.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/firmware.h>
#समावेश <linux/module.h>
#समावेश <linux/vदो_स्मृति.h>

#समावेश "iwl-drv.h"
#समावेश "iwl-csr.h"
#समावेश "iwl-debug.h"
#समावेश "iwl-trans.h"
#समावेश "iwl-op-mode.h"
#समावेश "iwl-agn-hw.h"
#समावेश "fw/img.h"
#समावेश "iwl-dbg-tlv.h"
#समावेश "iwl-config.h"
#समावेश "iwl-modparams.h"
#समावेश "fw/api/alive.h"
#समावेश "fw/api/mac.h"

/******************************************************************************
 *
 * module boiler plate
 *
 ******************************************************************************/

#घोषणा DRV_DESCRIPTION	"Intel(R) Wireless WiFi driver for Linux"
MODULE_DESCRIPTION(DRV_DESCRIPTION);
MODULE_AUTHOR(DRV_AUTHOR);
MODULE_LICENSE("GPL");

#अगर_घोषित CONFIG_IWLWIFI_DEBUGFS
अटल काष्ठा dentry *iwl_dbgfs_root;
#पूर्ण_अगर

/**
 * काष्ठा iwl_drv - drv common data
 * @list: list of drv काष्ठाures using this opmode
 * @fw: the iwl_fw काष्ठाure
 * @op_mode: the running op_mode
 * @trans: transport layer
 * @dev: क्रम debug prपूर्णांकs only
 * @fw_index: firmware revision to try loading
 * @firmware_name: composite filename of ucode file to load
 * @request_firmware_complete: the firmware has been obtained from user space
 * @dbgfs_drv: debugfs root directory entry
 * @dbgfs_trans: debugfs transport directory entry
 * @dbgfs_op_mode: debugfs op_mode directory entry
 */
काष्ठा iwl_drv अणु
	काष्ठा list_head list;
	काष्ठा iwl_fw fw;

	काष्ठा iwl_op_mode *op_mode;
	काष्ठा iwl_trans *trans;
	काष्ठा device *dev;

	पूर्णांक fw_index;                   /* firmware we're trying to load */
	अक्षर firmware_name[64];         /* name of firmware file to load */

	काष्ठा completion request_firmware_complete;

#अगर_घोषित CONFIG_IWLWIFI_DEBUGFS
	काष्ठा dentry *dbgfs_drv;
	काष्ठा dentry *dbgfs_trans;
	काष्ठा dentry *dbgfs_op_mode;
#पूर्ण_अगर
पूर्ण;

क्रमागत अणु
	DVM_OP_MODE,
	MVM_OP_MODE,
पूर्ण;

/* Protects the table contents, i.e. the ops poपूर्णांकer & drv list */
अटल काष्ठा mutex iwlwअगरi_opmode_table_mtx;
अटल काष्ठा iwlwअगरi_opmode_table अणु
	स्थिर अक्षर *name;			/* name: iwldvm, iwlmvm, etc */
	स्थिर काष्ठा iwl_op_mode_ops *ops;	/* poपूर्णांकer to op_mode ops */
	काष्ठा list_head drv;		/* list of devices using this op_mode */
पूर्ण iwlwअगरi_opmode_table[] = अणु		/* ops set when driver is initialized */
	[DVM_OP_MODE] = अणु .name = "iwldvm", .ops = शून्य पूर्ण,
	[MVM_OP_MODE] = अणु .name = "iwlmvm", .ops = शून्य पूर्ण,
पूर्ण;

#घोषणा IWL_DEFAULT_SCAN_CHANNELS 40

/*
 * काष्ठा fw_sec: Just क्रम the image parsing process.
 * For the fw storage we are using काष्ठा fw_desc.
 */
काष्ठा fw_sec अणु
	स्थिर व्योम *data;		/* the sec data */
	माप_प्रकार size;			/* section size */
	u32 offset;			/* offset of writing in the device */
पूर्ण;

अटल व्योम iwl_मुक्त_fw_desc(काष्ठा iwl_drv *drv, काष्ठा fw_desc *desc)
अणु
	vमुक्त(desc->data);
	desc->data = शून्य;
	desc->len = 0;
पूर्ण

अटल व्योम iwl_मुक्त_fw_img(काष्ठा iwl_drv *drv, काष्ठा fw_img *img)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < img->num_sec; i++)
		iwl_मुक्त_fw_desc(drv, &img->sec[i]);
	kमुक्त(img->sec);
पूर्ण

अटल व्योम iwl_dealloc_ucode(काष्ठा iwl_drv *drv)
अणु
	पूर्णांक i;

	kमुक्त(drv->fw.dbg.dest_tlv);
	क्रम (i = 0; i < ARRAY_SIZE(drv->fw.dbg.conf_tlv); i++)
		kमुक्त(drv->fw.dbg.conf_tlv[i]);
	क्रम (i = 0; i < ARRAY_SIZE(drv->fw.dbg.trigger_tlv); i++)
		kमुक्त(drv->fw.dbg.trigger_tlv[i]);
	kमुक्त(drv->fw.dbg.mem_tlv);
	kमुक्त(drv->fw.iml);
	kमुक्त(drv->fw.ucode_capa.cmd_versions);
	kमुक्त(drv->fw.phy_पूर्णांकegration_ver);

	क्रम (i = 0; i < IWL_UCODE_TYPE_MAX; i++)
		iwl_मुक्त_fw_img(drv, drv->fw.img + i);
पूर्ण

अटल पूर्णांक iwl_alloc_fw_desc(काष्ठा iwl_drv *drv, काष्ठा fw_desc *desc,
			     काष्ठा fw_sec *sec)
अणु
	व्योम *data;

	desc->data = शून्य;

	अगर (!sec || !sec->size)
		वापस -EINVAL;

	data = vदो_स्मृति(sec->size);
	अगर (!data)
		वापस -ENOMEM;

	desc->len = sec->size;
	desc->offset = sec->offset;
	स_नकल(data, sec->data, desc->len);
	desc->data = data;

	वापस 0;
पूर्ण

अटल व्योम iwl_req_fw_callback(स्थिर काष्ठा firmware *ucode_raw,
				व्योम *context);

अटल पूर्णांक iwl_request_firmware(काष्ठा iwl_drv *drv, bool first)
अणु
	स्थिर काष्ठा iwl_cfg *cfg = drv->trans->cfg;
	अक्षर tag[8];

	अगर (drv->trans->trans_cfg->device_family == IWL_DEVICE_FAMILY_9000 &&
	    (CSR_HW_REV_STEP(drv->trans->hw_rev) != SILICON_B_STEP &&
	     CSR_HW_REV_STEP(drv->trans->hw_rev) != SILICON_C_STEP)) अणु
		IWL_ERR(drv,
			"Only HW steps B and C are currently supported (0x%0x)\n",
			drv->trans->hw_rev);
		वापस -EINVAL;
	पूर्ण

	अगर (first) अणु
		drv->fw_index = cfg->ucode_api_max;
		प्र_लिखो(tag, "%d", drv->fw_index);
	पूर्ण अन्यथा अणु
		drv->fw_index--;
		प्र_लिखो(tag, "%d", drv->fw_index);
	पूर्ण

	अगर (drv->fw_index < cfg->ucode_api_min) अणु
		IWL_ERR(drv, "no suitable firmware found!\n");

		अगर (cfg->ucode_api_min == cfg->ucode_api_max) अणु
			IWL_ERR(drv, "%s%d is required\n", cfg->fw_name_pre,
				cfg->ucode_api_max);
		पूर्ण अन्यथा अणु
			IWL_ERR(drv, "minimum version required: %s%d\n",
				cfg->fw_name_pre, cfg->ucode_api_min);
			IWL_ERR(drv, "maximum version supported: %s%d\n",
				cfg->fw_name_pre, cfg->ucode_api_max);
		पूर्ण

		IWL_ERR(drv,
			"check git://git.kernel.org/pub/scm/linux/kernel/git/firmware/linux-firmware.git\n");
		वापस -ENOENT;
	पूर्ण

	snम_लिखो(drv->firmware_name, माप(drv->firmware_name), "%s%s.ucode",
		 cfg->fw_name_pre, tag);

	IWL_DEBUG_FW_INFO(drv, "attempting to load firmware '%s'\n",
			  drv->firmware_name);

	वापस request_firmware_noरुको(THIS_MODULE, 1, drv->firmware_name,
				       drv->trans->dev,
				       GFP_KERNEL, drv, iwl_req_fw_callback);
पूर्ण

काष्ठा fw_img_parsing अणु
	काष्ठा fw_sec *sec;
	पूर्णांक sec_counter;
पूर्ण;

/*
 * काष्ठा fw_sec_parsing: to extract fw section and it's offset from tlv
 */
काष्ठा fw_sec_parsing अणु
	__le32 offset;
	स्थिर u8 data[];
पूर्ण __packed;

/**
 * काष्ठा iwl_tlv_calib_data - parse the शेष calib data from TLV
 *
 * @ucode_type: the uCode to which the following शेष calib relates.
 * @calib: शेष calibrations.
 */
काष्ठा iwl_tlv_calib_data अणु
	__le32 ucode_type;
	काष्ठा iwl_tlv_calib_ctrl calib;
पूर्ण __packed;

काष्ठा iwl_firmware_pieces अणु
	काष्ठा fw_img_parsing img[IWL_UCODE_TYPE_MAX];

	u32 init_evtlog_ptr, init_evtlog_size, init_errlog_ptr;
	u32 inst_evtlog_ptr, inst_evtlog_size, inst_errlog_ptr;

	/* FW debug data parsed क्रम driver usage */
	bool dbg_dest_tlv_init;
	u8 *dbg_dest_ver;
	जोड़ अणु
		काष्ठा iwl_fw_dbg_dest_tlv *dbg_dest_tlv;
		काष्ठा iwl_fw_dbg_dest_tlv_v1 *dbg_dest_tlv_v1;
	पूर्ण;
	काष्ठा iwl_fw_dbg_conf_tlv *dbg_conf_tlv[FW_DBG_CONF_MAX];
	माप_प्रकार dbg_conf_tlv_len[FW_DBG_CONF_MAX];
	काष्ठा iwl_fw_dbg_trigger_tlv *dbg_trigger_tlv[FW_DBG_TRIGGER_MAX];
	माप_प्रकार dbg_trigger_tlv_len[FW_DBG_TRIGGER_MAX];
	काष्ठा iwl_fw_dbg_mem_seg_tlv *dbg_mem_tlv;
	माप_प्रकार n_mem_tlv;
पूर्ण;

/*
 * These functions are just to extract uCode section data from the pieces
 * काष्ठाure.
 */
अटल काष्ठा fw_sec *get_sec(काष्ठा iwl_firmware_pieces *pieces,
			      क्रमागत iwl_ucode_type type,
			      पूर्णांक  sec)
अणु
	वापस &pieces->img[type].sec[sec];
पूर्ण

अटल व्योम alloc_sec_data(काष्ठा iwl_firmware_pieces *pieces,
			   क्रमागत iwl_ucode_type type,
			   पूर्णांक sec)
अणु
	काष्ठा fw_img_parsing *img = &pieces->img[type];
	काष्ठा fw_sec *sec_memory;
	पूर्णांक size = sec + 1;
	माप_प्रकार alloc_size = माप(*img->sec) * size;

	अगर (img->sec && img->sec_counter >= size)
		वापस;

	sec_memory = kपुनः_स्मृति(img->sec, alloc_size, GFP_KERNEL);
	अगर (!sec_memory)
		वापस;

	img->sec = sec_memory;
	img->sec_counter = size;
पूर्ण

अटल व्योम set_sec_data(काष्ठा iwl_firmware_pieces *pieces,
			 क्रमागत iwl_ucode_type type,
			 पूर्णांक sec,
			 स्थिर व्योम *data)
अणु
	alloc_sec_data(pieces, type, sec);

	pieces->img[type].sec[sec].data = data;
पूर्ण

अटल व्योम set_sec_size(काष्ठा iwl_firmware_pieces *pieces,
			 क्रमागत iwl_ucode_type type,
			 पूर्णांक sec,
			 माप_प्रकार size)
अणु
	alloc_sec_data(pieces, type, sec);

	pieces->img[type].sec[sec].size = size;
पूर्ण

अटल माप_प्रकार get_sec_size(काष्ठा iwl_firmware_pieces *pieces,
			   क्रमागत iwl_ucode_type type,
			   पूर्णांक sec)
अणु
	वापस pieces->img[type].sec[sec].size;
पूर्ण

अटल व्योम set_sec_offset(काष्ठा iwl_firmware_pieces *pieces,
			   क्रमागत iwl_ucode_type type,
			   पूर्णांक sec,
			   u32 offset)
अणु
	alloc_sec_data(pieces, type, sec);

	pieces->img[type].sec[sec].offset = offset;
पूर्ण

अटल पूर्णांक iwl_store_cscheme(काष्ठा iwl_fw *fw, स्थिर u8 *data, स्थिर u32 len)
अणु
	पूर्णांक i, j;
	काष्ठा iwl_fw_cscheme_list *l = (काष्ठा iwl_fw_cscheme_list *)data;
	काष्ठा iwl_fw_cipher_scheme *fwcs;

	अगर (len < माप(*l) ||
	    len < माप(l->size) + l->size * माप(l->cs[0]))
		वापस -EINVAL;

	क्रम (i = 0, j = 0; i < IWL_UCODE_MAX_CS && i < l->size; i++) अणु
		fwcs = &l->cs[j];

		/* we skip schemes with zero cipher suite selector */
		अगर (!fwcs->cipher)
			जारी;

		fw->cs[j++] = *fwcs;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Gets uCode section from tlv.
 */
अटल पूर्णांक iwl_store_ucode_sec(काष्ठा iwl_firmware_pieces *pieces,
			       स्थिर व्योम *data, क्रमागत iwl_ucode_type type,
			       पूर्णांक size)
अणु
	काष्ठा fw_img_parsing *img;
	काष्ठा fw_sec *sec;
	काष्ठा fw_sec_parsing *sec_parse;
	माप_प्रकार alloc_size;

	अगर (WARN_ON(!pieces || !data || type >= IWL_UCODE_TYPE_MAX))
		वापस -1;

	sec_parse = (काष्ठा fw_sec_parsing *)data;

	img = &pieces->img[type];

	alloc_size = माप(*img->sec) * (img->sec_counter + 1);
	sec = kपुनः_स्मृति(img->sec, alloc_size, GFP_KERNEL);
	अगर (!sec)
		वापस -ENOMEM;
	img->sec = sec;

	sec = &img->sec[img->sec_counter];

	sec->offset = le32_to_cpu(sec_parse->offset);
	sec->data = sec_parse->data;
	sec->size = size - माप(sec_parse->offset);

	++img->sec_counter;

	वापस 0;
पूर्ण

अटल पूर्णांक iwl_set_शेष_calib(काष्ठा iwl_drv *drv, स्थिर u8 *data)
अणु
	काष्ठा iwl_tlv_calib_data *def_calib =
					(काष्ठा iwl_tlv_calib_data *)data;
	u32 ucode_type = le32_to_cpu(def_calib->ucode_type);
	अगर (ucode_type >= IWL_UCODE_TYPE_MAX) अणु
		IWL_ERR(drv, "Wrong ucode_type %u for default calibration.\n",
			ucode_type);
		वापस -EINVAL;
	पूर्ण
	drv->fw.शेष_calib[ucode_type].flow_trigger =
		def_calib->calib.flow_trigger;
	drv->fw.शेष_calib[ucode_type].event_trigger =
		def_calib->calib.event_trigger;

	वापस 0;
पूर्ण

अटल व्योम iwl_set_ucode_api_flags(काष्ठा iwl_drv *drv, स्थिर u8 *data,
				    काष्ठा iwl_ucode_capabilities *capa)
अणु
	स्थिर काष्ठा iwl_ucode_api *ucode_api = (व्योम *)data;
	u32 api_index = le32_to_cpu(ucode_api->api_index);
	u32 api_flags = le32_to_cpu(ucode_api->api_flags);
	पूर्णांक i;

	अगर (api_index >= DIV_ROUND_UP(NUM_IWL_UCODE_TLV_API, 32)) अणु
		IWL_WARN(drv,
			 "api flags index %d larger than supported by driver\n",
			 api_index);
		वापस;
	पूर्ण

	क्रम (i = 0; i < 32; i++) अणु
		अगर (api_flags & BIT(i))
			__set_bit(i + 32 * api_index, capa->_api);
	पूर्ण
पूर्ण

अटल व्योम iwl_set_ucode_capabilities(काष्ठा iwl_drv *drv, स्थिर u8 *data,
				       काष्ठा iwl_ucode_capabilities *capa)
अणु
	स्थिर काष्ठा iwl_ucode_capa *ucode_capa = (व्योम *)data;
	u32 api_index = le32_to_cpu(ucode_capa->api_index);
	u32 api_flags = le32_to_cpu(ucode_capa->api_capa);
	पूर्णांक i;

	अगर (api_index >= DIV_ROUND_UP(NUM_IWL_UCODE_TLV_CAPA, 32)) अणु
		IWL_WARN(drv,
			 "capa flags index %d larger than supported by driver\n",
			 api_index);
		वापस;
	पूर्ण

	क्रम (i = 0; i < 32; i++) अणु
		अगर (api_flags & BIT(i))
			__set_bit(i + 32 * api_index, capa->_capa);
	पूर्ण
पूर्ण

अटल स्थिर अक्षर *iwl_reduced_fw_name(काष्ठा iwl_drv *drv)
अणु
	स्थिर अक्षर *name = drv->firmware_name;

	अगर (म_भेदन(name, "iwlwifi-", 8) == 0)
		name += 8;

	वापस name;
पूर्ण

अटल पूर्णांक iwl_parse_v1_v2_firmware(काष्ठा iwl_drv *drv,
				    स्थिर काष्ठा firmware *ucode_raw,
				    काष्ठा iwl_firmware_pieces *pieces)
अणु
	काष्ठा iwl_ucode_header *ucode = (व्योम *)ucode_raw->data;
	u32 api_ver, hdr_size, build;
	अक्षर buildstr[25];
	स्थिर u8 *src;

	drv->fw.ucode_ver = le32_to_cpu(ucode->ver);
	api_ver = IWL_UCODE_API(drv->fw.ucode_ver);

	चयन (api_ver) अणु
	शेष:
		hdr_size = 28;
		अगर (ucode_raw->size < hdr_size) अणु
			IWL_ERR(drv, "File size too small!\n");
			वापस -EINVAL;
		पूर्ण
		build = le32_to_cpu(ucode->u.v2.build);
		set_sec_size(pieces, IWL_UCODE_REGULAR, IWL_UCODE_SECTION_INST,
			     le32_to_cpu(ucode->u.v2.inst_size));
		set_sec_size(pieces, IWL_UCODE_REGULAR, IWL_UCODE_SECTION_DATA,
			     le32_to_cpu(ucode->u.v2.data_size));
		set_sec_size(pieces, IWL_UCODE_INIT, IWL_UCODE_SECTION_INST,
			     le32_to_cpu(ucode->u.v2.init_size));
		set_sec_size(pieces, IWL_UCODE_INIT, IWL_UCODE_SECTION_DATA,
			     le32_to_cpu(ucode->u.v2.init_data_size));
		src = ucode->u.v2.data;
		अवरोध;
	हाल 0:
	हाल 1:
	हाल 2:
		hdr_size = 24;
		अगर (ucode_raw->size < hdr_size) अणु
			IWL_ERR(drv, "File size too small!\n");
			वापस -EINVAL;
		पूर्ण
		build = 0;
		set_sec_size(pieces, IWL_UCODE_REGULAR, IWL_UCODE_SECTION_INST,
			     le32_to_cpu(ucode->u.v1.inst_size));
		set_sec_size(pieces, IWL_UCODE_REGULAR, IWL_UCODE_SECTION_DATA,
			     le32_to_cpu(ucode->u.v1.data_size));
		set_sec_size(pieces, IWL_UCODE_INIT, IWL_UCODE_SECTION_INST,
			     le32_to_cpu(ucode->u.v1.init_size));
		set_sec_size(pieces, IWL_UCODE_INIT, IWL_UCODE_SECTION_DATA,
			     le32_to_cpu(ucode->u.v1.init_data_size));
		src = ucode->u.v1.data;
		अवरोध;
	पूर्ण

	अगर (build)
		प्र_लिखो(buildstr, " build %u", build);
	अन्यथा
		buildstr[0] = '\0';

	snम_लिखो(drv->fw.fw_version,
		 माप(drv->fw.fw_version),
		 "%u.%u.%u.%u%s %s",
		 IWL_UCODE_MAJOR(drv->fw.ucode_ver),
		 IWL_UCODE_MINOR(drv->fw.ucode_ver),
		 IWL_UCODE_API(drv->fw.ucode_ver),
		 IWL_UCODE_SERIAL(drv->fw.ucode_ver),
		 buildstr, iwl_reduced_fw_name(drv));

	/* Verअगरy size of file vs. image size info in file's header */

	अगर (ucode_raw->size != hdr_size +
	    get_sec_size(pieces, IWL_UCODE_REGULAR, IWL_UCODE_SECTION_INST) +
	    get_sec_size(pieces, IWL_UCODE_REGULAR, IWL_UCODE_SECTION_DATA) +
	    get_sec_size(pieces, IWL_UCODE_INIT, IWL_UCODE_SECTION_INST) +
	    get_sec_size(pieces, IWL_UCODE_INIT, IWL_UCODE_SECTION_DATA)) अणु

		IWL_ERR(drv,
			"uCode file size %d does not match expected size\n",
			(पूर्णांक)ucode_raw->size);
		वापस -EINVAL;
	पूर्ण


	set_sec_data(pieces, IWL_UCODE_REGULAR, IWL_UCODE_SECTION_INST, src);
	src += get_sec_size(pieces, IWL_UCODE_REGULAR, IWL_UCODE_SECTION_INST);
	set_sec_offset(pieces, IWL_UCODE_REGULAR, IWL_UCODE_SECTION_INST,
		       IWLAGN_RTC_INST_LOWER_BOUND);
	set_sec_data(pieces, IWL_UCODE_REGULAR, IWL_UCODE_SECTION_DATA, src);
	src += get_sec_size(pieces, IWL_UCODE_REGULAR, IWL_UCODE_SECTION_DATA);
	set_sec_offset(pieces, IWL_UCODE_REGULAR, IWL_UCODE_SECTION_DATA,
		       IWLAGN_RTC_DATA_LOWER_BOUND);
	set_sec_data(pieces, IWL_UCODE_INIT, IWL_UCODE_SECTION_INST, src);
	src += get_sec_size(pieces, IWL_UCODE_INIT, IWL_UCODE_SECTION_INST);
	set_sec_offset(pieces, IWL_UCODE_INIT, IWL_UCODE_SECTION_INST,
		       IWLAGN_RTC_INST_LOWER_BOUND);
	set_sec_data(pieces, IWL_UCODE_INIT, IWL_UCODE_SECTION_DATA, src);
	src += get_sec_size(pieces, IWL_UCODE_INIT, IWL_UCODE_SECTION_DATA);
	set_sec_offset(pieces, IWL_UCODE_INIT, IWL_UCODE_SECTION_DATA,
		       IWLAGN_RTC_DATA_LOWER_BOUND);
	वापस 0;
पूर्ण

अटल पूर्णांक iwl_parse_tlv_firmware(काष्ठा iwl_drv *drv,
				स्थिर काष्ठा firmware *ucode_raw,
				काष्ठा iwl_firmware_pieces *pieces,
				काष्ठा iwl_ucode_capabilities *capa,
				bool *usnअगरfer_images)
अणु
	काष्ठा iwl_tlv_ucode_header *ucode = (व्योम *)ucode_raw->data;
	स्थिर काष्ठा iwl_ucode_tlv *tlv;
	माप_प्रकार len = ucode_raw->size;
	स्थिर u8 *data;
	u32 tlv_len;
	u32 usnअगरfer_img;
	क्रमागत iwl_ucode_tlv_type tlv_type;
	स्थिर u8 *tlv_data;
	अक्षर buildstr[25];
	u32 build, paging_mem_size;
	पूर्णांक num_of_cpus;
	bool usnअगरfer_req = false;

	अगर (len < माप(*ucode)) अणु
		IWL_ERR(drv, "uCode has invalid length: %zd\n", len);
		वापस -EINVAL;
	पूर्ण

	अगर (ucode->magic != cpu_to_le32(IWL_TLV_UCODE_MAGIC)) अणु
		IWL_ERR(drv, "invalid uCode magic: 0X%x\n",
			le32_to_cpu(ucode->magic));
		वापस -EINVAL;
	पूर्ण

	drv->fw.ucode_ver = le32_to_cpu(ucode->ver);
	स_नकल(drv->fw.human_पढ़ोable, ucode->human_पढ़ोable,
	       माप(drv->fw.human_पढ़ोable));
	build = le32_to_cpu(ucode->build);

	अगर (build)
		प्र_लिखो(buildstr, " build %u", build);
	अन्यथा
		buildstr[0] = '\0';

	snम_लिखो(drv->fw.fw_version,
		 माप(drv->fw.fw_version),
		 "%u.%u.%u.%u%s %s",
		 IWL_UCODE_MAJOR(drv->fw.ucode_ver),
		 IWL_UCODE_MINOR(drv->fw.ucode_ver),
		 IWL_UCODE_API(drv->fw.ucode_ver),
		 IWL_UCODE_SERIAL(drv->fw.ucode_ver),
		 buildstr, iwl_reduced_fw_name(drv));

	data = ucode->data;

	len -= माप(*ucode);

	जबतक (len >= माप(*tlv)) अणु
		len -= माप(*tlv);
		tlv = (व्योम *)data;

		tlv_len = le32_to_cpu(tlv->length);
		tlv_type = le32_to_cpu(tlv->type);
		tlv_data = tlv->data;

		अगर (len < tlv_len) अणु
			IWL_ERR(drv, "invalid TLV len: %zd/%u\n",
				len, tlv_len);
			वापस -EINVAL;
		पूर्ण
		len -= ALIGN(tlv_len, 4);
		data += माप(*tlv) + ALIGN(tlv_len, 4);

		चयन (tlv_type) अणु
		हाल IWL_UCODE_TLV_INST:
			set_sec_data(pieces, IWL_UCODE_REGULAR,
				     IWL_UCODE_SECTION_INST, tlv_data);
			set_sec_size(pieces, IWL_UCODE_REGULAR,
				     IWL_UCODE_SECTION_INST, tlv_len);
			set_sec_offset(pieces, IWL_UCODE_REGULAR,
				       IWL_UCODE_SECTION_INST,
				       IWLAGN_RTC_INST_LOWER_BOUND);
			अवरोध;
		हाल IWL_UCODE_TLV_DATA:
			set_sec_data(pieces, IWL_UCODE_REGULAR,
				     IWL_UCODE_SECTION_DATA, tlv_data);
			set_sec_size(pieces, IWL_UCODE_REGULAR,
				     IWL_UCODE_SECTION_DATA, tlv_len);
			set_sec_offset(pieces, IWL_UCODE_REGULAR,
				       IWL_UCODE_SECTION_DATA,
				       IWLAGN_RTC_DATA_LOWER_BOUND);
			अवरोध;
		हाल IWL_UCODE_TLV_INIT:
			set_sec_data(pieces, IWL_UCODE_INIT,
				     IWL_UCODE_SECTION_INST, tlv_data);
			set_sec_size(pieces, IWL_UCODE_INIT,
				     IWL_UCODE_SECTION_INST, tlv_len);
			set_sec_offset(pieces, IWL_UCODE_INIT,
				       IWL_UCODE_SECTION_INST,
				       IWLAGN_RTC_INST_LOWER_BOUND);
			अवरोध;
		हाल IWL_UCODE_TLV_INIT_DATA:
			set_sec_data(pieces, IWL_UCODE_INIT,
				     IWL_UCODE_SECTION_DATA, tlv_data);
			set_sec_size(pieces, IWL_UCODE_INIT,
				     IWL_UCODE_SECTION_DATA, tlv_len);
			set_sec_offset(pieces, IWL_UCODE_INIT,
				       IWL_UCODE_SECTION_DATA,
				       IWLAGN_RTC_DATA_LOWER_BOUND);
			अवरोध;
		हाल IWL_UCODE_TLV_BOOT:
			IWL_ERR(drv, "Found unexpected BOOT ucode\n");
			अवरोध;
		हाल IWL_UCODE_TLV_PROBE_MAX_LEN:
			अगर (tlv_len != माप(u32))
				जाओ invalid_tlv_len;
			capa->max_probe_length =
					le32_to_cpup((__le32 *)tlv_data);
			अवरोध;
		हाल IWL_UCODE_TLV_PAN:
			अगर (tlv_len)
				जाओ invalid_tlv_len;
			capa->flags |= IWL_UCODE_TLV_FLAGS_PAN;
			अवरोध;
		हाल IWL_UCODE_TLV_FLAGS:
			/* must be at least one u32 */
			अगर (tlv_len < माप(u32))
				जाओ invalid_tlv_len;
			/* and a proper number of u32s */
			अगर (tlv_len % माप(u32))
				जाओ invalid_tlv_len;
			/*
			 * This driver only पढ़ोs the first u32 as
			 * right now no more features are defined,
			 * अगर that changes then either the driver
			 * will not work with the new firmware, or
			 * it'll not take advantage of new features.
			 */
			capa->flags = le32_to_cpup((__le32 *)tlv_data);
			अवरोध;
		हाल IWL_UCODE_TLV_API_CHANGES_SET:
			अगर (tlv_len != माप(काष्ठा iwl_ucode_api))
				जाओ invalid_tlv_len;
			iwl_set_ucode_api_flags(drv, tlv_data, capa);
			अवरोध;
		हाल IWL_UCODE_TLV_ENABLED_CAPABILITIES:
			अगर (tlv_len != माप(काष्ठा iwl_ucode_capa))
				जाओ invalid_tlv_len;
			iwl_set_ucode_capabilities(drv, tlv_data, capa);
			अवरोध;
		हाल IWL_UCODE_TLV_INIT_EVTLOG_PTR:
			अगर (tlv_len != माप(u32))
				जाओ invalid_tlv_len;
			pieces->init_evtlog_ptr =
					le32_to_cpup((__le32 *)tlv_data);
			अवरोध;
		हाल IWL_UCODE_TLV_INIT_EVTLOG_SIZE:
			अगर (tlv_len != माप(u32))
				जाओ invalid_tlv_len;
			pieces->init_evtlog_size =
					le32_to_cpup((__le32 *)tlv_data);
			अवरोध;
		हाल IWL_UCODE_TLV_INIT_ERRLOG_PTR:
			अगर (tlv_len != माप(u32))
				जाओ invalid_tlv_len;
			pieces->init_errlog_ptr =
					le32_to_cpup((__le32 *)tlv_data);
			अवरोध;
		हाल IWL_UCODE_TLV_RUNT_EVTLOG_PTR:
			अगर (tlv_len != माप(u32))
				जाओ invalid_tlv_len;
			pieces->inst_evtlog_ptr =
					le32_to_cpup((__le32 *)tlv_data);
			अवरोध;
		हाल IWL_UCODE_TLV_RUNT_EVTLOG_SIZE:
			अगर (tlv_len != माप(u32))
				जाओ invalid_tlv_len;
			pieces->inst_evtlog_size =
					le32_to_cpup((__le32 *)tlv_data);
			अवरोध;
		हाल IWL_UCODE_TLV_RUNT_ERRLOG_PTR:
			अगर (tlv_len != माप(u32))
				जाओ invalid_tlv_len;
			pieces->inst_errlog_ptr =
					le32_to_cpup((__le32 *)tlv_data);
			अवरोध;
		हाल IWL_UCODE_TLV_ENHANCE_SENS_TBL:
			अगर (tlv_len)
				जाओ invalid_tlv_len;
			drv->fw.enhance_sensitivity_table = true;
			अवरोध;
		हाल IWL_UCODE_TLV_WOWLAN_INST:
			set_sec_data(pieces, IWL_UCODE_WOWLAN,
				     IWL_UCODE_SECTION_INST, tlv_data);
			set_sec_size(pieces, IWL_UCODE_WOWLAN,
				     IWL_UCODE_SECTION_INST, tlv_len);
			set_sec_offset(pieces, IWL_UCODE_WOWLAN,
				       IWL_UCODE_SECTION_INST,
				       IWLAGN_RTC_INST_LOWER_BOUND);
			अवरोध;
		हाल IWL_UCODE_TLV_WOWLAN_DATA:
			set_sec_data(pieces, IWL_UCODE_WOWLAN,
				     IWL_UCODE_SECTION_DATA, tlv_data);
			set_sec_size(pieces, IWL_UCODE_WOWLAN,
				     IWL_UCODE_SECTION_DATA, tlv_len);
			set_sec_offset(pieces, IWL_UCODE_WOWLAN,
				       IWL_UCODE_SECTION_DATA,
				       IWLAGN_RTC_DATA_LOWER_BOUND);
			अवरोध;
		हाल IWL_UCODE_TLV_PHY_CALIBRATION_SIZE:
			अगर (tlv_len != माप(u32))
				जाओ invalid_tlv_len;
			capa->standard_phy_calibration_size =
					le32_to_cpup((__le32 *)tlv_data);
			अवरोध;
		हाल IWL_UCODE_TLV_SEC_RT:
			iwl_store_ucode_sec(pieces, tlv_data, IWL_UCODE_REGULAR,
					    tlv_len);
			drv->fw.type = IWL_FW_MVM;
			अवरोध;
		हाल IWL_UCODE_TLV_SEC_INIT:
			iwl_store_ucode_sec(pieces, tlv_data, IWL_UCODE_INIT,
					    tlv_len);
			drv->fw.type = IWL_FW_MVM;
			अवरोध;
		हाल IWL_UCODE_TLV_SEC_WOWLAN:
			iwl_store_ucode_sec(pieces, tlv_data, IWL_UCODE_WOWLAN,
					    tlv_len);
			drv->fw.type = IWL_FW_MVM;
			अवरोध;
		हाल IWL_UCODE_TLV_DEF_CALIB:
			अगर (tlv_len != माप(काष्ठा iwl_tlv_calib_data))
				जाओ invalid_tlv_len;
			अगर (iwl_set_शेष_calib(drv, tlv_data))
				जाओ tlv_error;
			अवरोध;
		हाल IWL_UCODE_TLV_PHY_SKU:
			अगर (tlv_len != माप(u32))
				जाओ invalid_tlv_len;
			drv->fw.phy_config = le32_to_cpup((__le32 *)tlv_data);
			drv->fw.valid_tx_ant = (drv->fw.phy_config &
						FW_PHY_CFG_TX_CHAIN) >>
						FW_PHY_CFG_TX_CHAIN_POS;
			drv->fw.valid_rx_ant = (drv->fw.phy_config &
						FW_PHY_CFG_RX_CHAIN) >>
						FW_PHY_CFG_RX_CHAIN_POS;
			अवरोध;
		हाल IWL_UCODE_TLV_SECURE_SEC_RT:
			iwl_store_ucode_sec(pieces, tlv_data, IWL_UCODE_REGULAR,
					    tlv_len);
			drv->fw.type = IWL_FW_MVM;
			अवरोध;
		हाल IWL_UCODE_TLV_SECURE_SEC_INIT:
			iwl_store_ucode_sec(pieces, tlv_data, IWL_UCODE_INIT,
					    tlv_len);
			drv->fw.type = IWL_FW_MVM;
			अवरोध;
		हाल IWL_UCODE_TLV_SECURE_SEC_WOWLAN:
			iwl_store_ucode_sec(pieces, tlv_data, IWL_UCODE_WOWLAN,
					    tlv_len);
			drv->fw.type = IWL_FW_MVM;
			अवरोध;
		हाल IWL_UCODE_TLV_NUM_OF_CPU:
			अगर (tlv_len != माप(u32))
				जाओ invalid_tlv_len;
			num_of_cpus =
				le32_to_cpup((__le32 *)tlv_data);

			अगर (num_of_cpus == 2) अणु
				drv->fw.img[IWL_UCODE_REGULAR].is_dual_cpus =
					true;
				drv->fw.img[IWL_UCODE_INIT].is_dual_cpus =
					true;
				drv->fw.img[IWL_UCODE_WOWLAN].is_dual_cpus =
					true;
			पूर्ण अन्यथा अगर ((num_of_cpus > 2) || (num_of_cpus < 1)) अणु
				IWL_ERR(drv, "Driver support upto 2 CPUs\n");
				वापस -EINVAL;
			पूर्ण
			अवरोध;
		हाल IWL_UCODE_TLV_CSCHEME:
			अगर (iwl_store_cscheme(&drv->fw, tlv_data, tlv_len))
				जाओ invalid_tlv_len;
			अवरोध;
		हाल IWL_UCODE_TLV_N_SCAN_CHANNELS:
			अगर (tlv_len != माप(u32))
				जाओ invalid_tlv_len;
			capa->n_scan_channels =
				le32_to_cpup((__le32 *)tlv_data);
			अवरोध;
		हाल IWL_UCODE_TLV_FW_VERSION: अणु
			__le32 *ptr = (व्योम *)tlv_data;
			u32 major, minor;
			u8 local_comp;

			अगर (tlv_len != माप(u32) * 3)
				जाओ invalid_tlv_len;

			major = le32_to_cpup(ptr++);
			minor = le32_to_cpup(ptr++);
			local_comp = le32_to_cpup(ptr);

			अगर (major >= 35)
				snम_लिखो(drv->fw.fw_version,
					 माप(drv->fw.fw_version),
					"%u.%08x.%u %s", major, minor,
					local_comp, iwl_reduced_fw_name(drv));
			अन्यथा
				snम_लिखो(drv->fw.fw_version,
					 माप(drv->fw.fw_version),
					"%u.%u.%u %s", major, minor,
					local_comp, iwl_reduced_fw_name(drv));
			अवरोध;
			पूर्ण
		हाल IWL_UCODE_TLV_FW_DBG_DEST: अणु
			काष्ठा iwl_fw_dbg_dest_tlv *dest = शून्य;
			काष्ठा iwl_fw_dbg_dest_tlv_v1 *dest_v1 = शून्य;
			u8 mon_mode;

			pieces->dbg_dest_ver = (u8 *)tlv_data;
			अगर (*pieces->dbg_dest_ver == 1) अणु
				dest = (व्योम *)tlv_data;
			पूर्ण अन्यथा अगर (*pieces->dbg_dest_ver == 0) अणु
				dest_v1 = (व्योम *)tlv_data;
			पूर्ण अन्यथा अणु
				IWL_ERR(drv,
					"The version is %d, and it is invalid\n",
					*pieces->dbg_dest_ver);
				अवरोध;
			पूर्ण

			अगर (pieces->dbg_dest_tlv_init) अणु
				IWL_ERR(drv,
					"dbg destination ignored, already exists\n");
				अवरोध;
			पूर्ण

			pieces->dbg_dest_tlv_init = true;

			अगर (dest_v1) अणु
				pieces->dbg_dest_tlv_v1 = dest_v1;
				mon_mode = dest_v1->monitor_mode;
			पूर्ण अन्यथा अणु
				pieces->dbg_dest_tlv = dest;
				mon_mode = dest->monitor_mode;
			पूर्ण

			IWL_INFO(drv, "Found debug destination: %s\n",
				 get_fw_dbg_mode_string(mon_mode));

			drv->fw.dbg.n_dest_reg = (dest_v1) ?
				tlv_len -
				दुरत्व(काष्ठा iwl_fw_dbg_dest_tlv_v1,
					 reg_ops) :
				tlv_len -
				दुरत्व(काष्ठा iwl_fw_dbg_dest_tlv,
					 reg_ops);

			drv->fw.dbg.n_dest_reg /=
				माप(drv->fw.dbg.dest_tlv->reg_ops[0]);

			अवरोध;
			पूर्ण
		हाल IWL_UCODE_TLV_FW_DBG_CONF: अणु
			काष्ठा iwl_fw_dbg_conf_tlv *conf = (व्योम *)tlv_data;

			अगर (!pieces->dbg_dest_tlv_init) अणु
				IWL_ERR(drv,
					"Ignore dbg config %d - no destination configured\n",
					conf->id);
				अवरोध;
			पूर्ण

			अगर (conf->id >= ARRAY_SIZE(drv->fw.dbg.conf_tlv)) अणु
				IWL_ERR(drv,
					"Skip unknown configuration: %d\n",
					conf->id);
				अवरोध;
			पूर्ण

			अगर (pieces->dbg_conf_tlv[conf->id]) अणु
				IWL_ERR(drv,
					"Ignore duplicate dbg config %d\n",
					conf->id);
				अवरोध;
			पूर्ण

			अगर (conf->usnअगरfer)
				usnअगरfer_req = true;

			IWL_INFO(drv, "Found debug configuration: %d\n",
				 conf->id);

			pieces->dbg_conf_tlv[conf->id] = conf;
			pieces->dbg_conf_tlv_len[conf->id] = tlv_len;
			अवरोध;
			पूर्ण
		हाल IWL_UCODE_TLV_FW_DBG_TRIGGER: अणु
			काष्ठा iwl_fw_dbg_trigger_tlv *trigger =
				(व्योम *)tlv_data;
			u32 trigger_id = le32_to_cpu(trigger->id);

			अगर (trigger_id >= ARRAY_SIZE(drv->fw.dbg.trigger_tlv)) अणु
				IWL_ERR(drv,
					"Skip unknown trigger: %u\n",
					trigger->id);
				अवरोध;
			पूर्ण

			अगर (pieces->dbg_trigger_tlv[trigger_id]) अणु
				IWL_ERR(drv,
					"Ignore duplicate dbg trigger %u\n",
					trigger->id);
				अवरोध;
			पूर्ण

			IWL_INFO(drv, "Found debug trigger: %u\n", trigger->id);

			pieces->dbg_trigger_tlv[trigger_id] = trigger;
			pieces->dbg_trigger_tlv_len[trigger_id] = tlv_len;
			अवरोध;
			पूर्ण
		हाल IWL_UCODE_TLV_FW_DBG_DUMP_LST: अणु
			अगर (tlv_len != माप(u32)) अणु
				IWL_ERR(drv,
					"dbg lst mask size incorrect, skip\n");
				अवरोध;
			पूर्ण

			drv->fw.dbg.dump_mask =
				le32_to_cpup((__le32 *)tlv_data);
			अवरोध;
			पूर्ण
		हाल IWL_UCODE_TLV_SEC_RT_USNIFFER:
			*usnअगरfer_images = true;
			iwl_store_ucode_sec(pieces, tlv_data,
					    IWL_UCODE_REGULAR_USNIFFER,
					    tlv_len);
			अवरोध;
		हाल IWL_UCODE_TLV_PAGING:
			अगर (tlv_len != माप(u32))
				जाओ invalid_tlv_len;
			paging_mem_size = le32_to_cpup((__le32 *)tlv_data);

			IWL_DEBUG_FW(drv,
				     "Paging: paging enabled (size = %u bytes)\n",
				     paging_mem_size);

			अगर (paging_mem_size > MAX_PAGING_IMAGE_SIZE) अणु
				IWL_ERR(drv,
					"Paging: driver supports up to %lu bytes for paging image\n",
					MAX_PAGING_IMAGE_SIZE);
				वापस -EINVAL;
			पूर्ण

			अगर (paging_mem_size & (FW_PAGING_SIZE - 1)) अणु
				IWL_ERR(drv,
					"Paging: image isn't multiple %lu\n",
					FW_PAGING_SIZE);
				वापस -EINVAL;
			पूर्ण

			drv->fw.img[IWL_UCODE_REGULAR].paging_mem_size =
				paging_mem_size;
			usnअगरfer_img = IWL_UCODE_REGULAR_USNIFFER;
			drv->fw.img[usnअगरfer_img].paging_mem_size =
				paging_mem_size;
			अवरोध;
		हाल IWL_UCODE_TLV_FW_GSCAN_CAPA:
			/* ignored */
			अवरोध;
		हाल IWL_UCODE_TLV_FW_MEM_SEG: अणु
			काष्ठा iwl_fw_dbg_mem_seg_tlv *dbg_mem =
				(व्योम *)tlv_data;
			माप_प्रकार size;
			काष्ठा iwl_fw_dbg_mem_seg_tlv *n;

			अगर (tlv_len != (माप(*dbg_mem)))
				जाओ invalid_tlv_len;

			IWL_DEBUG_INFO(drv, "Found debug memory segment: %u\n",
				       dbg_mem->data_type);

			size = माप(*pieces->dbg_mem_tlv) *
			       (pieces->n_mem_tlv + 1);
			n = kपुनः_स्मृति(pieces->dbg_mem_tlv, size, GFP_KERNEL);
			अगर (!n)
				वापस -ENOMEM;
			pieces->dbg_mem_tlv = n;
			pieces->dbg_mem_tlv[pieces->n_mem_tlv] = *dbg_mem;
			pieces->n_mem_tlv++;
			अवरोध;
			पूर्ण
		हाल IWL_UCODE_TLV_IML: अणु
			drv->fw.iml_len = tlv_len;
			drv->fw.iml = kmemdup(tlv_data, tlv_len, GFP_KERNEL);
			अगर (!drv->fw.iml)
				वापस -ENOMEM;
			अवरोध;
			पूर्ण
		हाल IWL_UCODE_TLV_FW_RECOVERY_INFO: अणु
			काष्ठा अणु
				__le32 buf_addr;
				__le32 buf_size;
			पूर्ण *recov_info = (व्योम *)tlv_data;

			अगर (tlv_len != माप(*recov_info))
				जाओ invalid_tlv_len;
			capa->error_log_addr =
				le32_to_cpu(recov_info->buf_addr);
			capa->error_log_size =
				le32_to_cpu(recov_info->buf_size);
			पूर्ण
			अवरोध;
		हाल IWL_UCODE_TLV_FW_FSEQ_VERSION: अणु
			काष्ठा अणु
				u8 version[32];
				u8 sha1[20];
			पूर्ण *fseq_ver = (व्योम *)tlv_data;

			अगर (tlv_len != माप(*fseq_ver))
				जाओ invalid_tlv_len;
			IWL_INFO(drv, "TLV_FW_FSEQ_VERSION: %s\n",
				 fseq_ver->version);
			पूर्ण
			अवरोध;
		हाल IWL_UCODE_TLV_FW_NUM_STATIONS:
			अगर (tlv_len != माप(u32))
				जाओ invalid_tlv_len;
			अगर (le32_to_cpup((__le32 *)tlv_data) >
			    IWL_MVM_STATION_COUNT_MAX) अणु
				IWL_ERR(drv,
					"%d is an invalid number of station\n",
					le32_to_cpup((__le32 *)tlv_data));
				जाओ tlv_error;
			पूर्ण
			capa->num_stations =
				le32_to_cpup((__le32 *)tlv_data);
			अवरोध;
		हाल IWL_UCODE_TLV_UMAC_DEBUG_ADDRS: अणु
			काष्ठा iwl_umac_debug_addrs *dbg_ptrs =
				(व्योम *)tlv_data;

			अगर (tlv_len != माप(*dbg_ptrs))
				जाओ invalid_tlv_len;
			अगर (drv->trans->trans_cfg->device_family <
			    IWL_DEVICE_FAMILY_22000)
				अवरोध;
			drv->trans->dbg.umac_error_event_table =
				le32_to_cpu(dbg_ptrs->error_info_addr) &
				~FW_ADDR_CACHE_CONTROL;
			drv->trans->dbg.error_event_table_tlv_status |=
				IWL_ERROR_EVENT_TABLE_UMAC;
			अवरोध;
			पूर्ण
		हाल IWL_UCODE_TLV_LMAC_DEBUG_ADDRS: अणु
			काष्ठा iwl_lmac_debug_addrs *dbg_ptrs =
				(व्योम *)tlv_data;

			अगर (tlv_len != माप(*dbg_ptrs))
				जाओ invalid_tlv_len;
			अगर (drv->trans->trans_cfg->device_family <
			    IWL_DEVICE_FAMILY_22000)
				अवरोध;
			drv->trans->dbg.lmac_error_event_table[0] =
				le32_to_cpu(dbg_ptrs->error_event_table_ptr) &
				~FW_ADDR_CACHE_CONTROL;
			drv->trans->dbg.error_event_table_tlv_status |=
				IWL_ERROR_EVENT_TABLE_LMAC1;
			अवरोध;
			पूर्ण
		हाल IWL_UCODE_TLV_TYPE_DEBUG_INFO:
		हाल IWL_UCODE_TLV_TYPE_BUFFER_ALLOCATION:
		हाल IWL_UCODE_TLV_TYPE_HCMD:
		हाल IWL_UCODE_TLV_TYPE_REGIONS:
		हाल IWL_UCODE_TLV_TYPE_TRIGGERS:
			अगर (iwlwअगरi_mod_params.enable_ini)
				iwl_dbg_tlv_alloc(drv->trans, tlv, false);
			अवरोध;
		हाल IWL_UCODE_TLV_CMD_VERSIONS:
			अगर (tlv_len % माप(काष्ठा iwl_fw_cmd_version)) अणु
				IWL_ERR(drv,
					"Invalid length for command versions: %u\n",
					tlv_len);
				tlv_len /= माप(काष्ठा iwl_fw_cmd_version);
				tlv_len *= माप(काष्ठा iwl_fw_cmd_version);
			पूर्ण
			अगर (WARN_ON(capa->cmd_versions))
				वापस -EINVAL;
			capa->cmd_versions = kmemdup(tlv_data, tlv_len,
						     GFP_KERNEL);
			अगर (!capa->cmd_versions)
				वापस -ENOMEM;
			capa->n_cmd_versions =
				tlv_len / माप(काष्ठा iwl_fw_cmd_version);
			अवरोध;
		हाल IWL_UCODE_TLV_PHY_INTEGRATION_VERSION:
			अगर (drv->fw.phy_पूर्णांकegration_ver) अणु
				IWL_ERR(drv,
					"phy integration str ignored, already exists\n");
				अवरोध;
			पूर्ण

			drv->fw.phy_पूर्णांकegration_ver =
				kmemdup(tlv_data, tlv_len, GFP_KERNEL);
			अगर (!drv->fw.phy_पूर्णांकegration_ver)
				वापस -ENOMEM;
			drv->fw.phy_पूर्णांकegration_ver_len = tlv_len;
			अवरोध;
		शेष:
			IWL_DEBUG_INFO(drv, "unknown TLV: %d\n", tlv_type);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!fw_has_capa(capa, IWL_UCODE_TLV_CAPA_USNIFFER_UNIFIED) &&
	    usnअगरfer_req && !*usnअगरfer_images) अणु
		IWL_ERR(drv,
			"user selected to work with usniffer but usniffer image isn't available in ucode package\n");
		वापस -EINVAL;
	पूर्ण

	अगर (len) अणु
		IWL_ERR(drv, "invalid TLV after parsing: %zd\n", len);
		iwl_prपूर्णांक_hex_dump(drv, IWL_DL_FW, (u8 *)data, len);
		वापस -EINVAL;
	पूर्ण

	वापस 0;

 invalid_tlv_len:
	IWL_ERR(drv, "TLV %d has invalid size: %u\n", tlv_type, tlv_len);
 tlv_error:
	iwl_prपूर्णांक_hex_dump(drv, IWL_DL_FW, tlv_data, tlv_len);

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक iwl_alloc_ucode(काष्ठा iwl_drv *drv,
			   काष्ठा iwl_firmware_pieces *pieces,
			   क्रमागत iwl_ucode_type type)
अणु
	पूर्णांक i;
	काष्ठा fw_desc *sec;

	sec = kसुस्मृति(pieces->img[type].sec_counter, माप(*sec), GFP_KERNEL);
	अगर (!sec)
		वापस -ENOMEM;
	drv->fw.img[type].sec = sec;
	drv->fw.img[type].num_sec = pieces->img[type].sec_counter;

	क्रम (i = 0; i < pieces->img[type].sec_counter; i++)
		अगर (iwl_alloc_fw_desc(drv, &sec[i], get_sec(pieces, type, i)))
			वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल पूर्णांक validate_sec_sizes(काष्ठा iwl_drv *drv,
			      काष्ठा iwl_firmware_pieces *pieces,
			      स्थिर काष्ठा iwl_cfg *cfg)
अणु
	IWL_DEBUG_INFO(drv, "f/w package hdr runtime inst size = %zd\n",
		get_sec_size(pieces, IWL_UCODE_REGULAR,
			     IWL_UCODE_SECTION_INST));
	IWL_DEBUG_INFO(drv, "f/w package hdr runtime data size = %zd\n",
		get_sec_size(pieces, IWL_UCODE_REGULAR,
			     IWL_UCODE_SECTION_DATA));
	IWL_DEBUG_INFO(drv, "f/w package hdr init inst size = %zd\n",
		get_sec_size(pieces, IWL_UCODE_INIT, IWL_UCODE_SECTION_INST));
	IWL_DEBUG_INFO(drv, "f/w package hdr init data size = %zd\n",
		get_sec_size(pieces, IWL_UCODE_INIT, IWL_UCODE_SECTION_DATA));

	/* Verअगरy that uCode images will fit in card's SRAM. */
	अगर (get_sec_size(pieces, IWL_UCODE_REGULAR, IWL_UCODE_SECTION_INST) >
	    cfg->max_inst_size) अणु
		IWL_ERR(drv, "uCode instr len %zd too large to fit in\n",
			get_sec_size(pieces, IWL_UCODE_REGULAR,
				     IWL_UCODE_SECTION_INST));
		वापस -1;
	पूर्ण

	अगर (get_sec_size(pieces, IWL_UCODE_REGULAR, IWL_UCODE_SECTION_DATA) >
	    cfg->max_data_size) अणु
		IWL_ERR(drv, "uCode data len %zd too large to fit in\n",
			get_sec_size(pieces, IWL_UCODE_REGULAR,
				     IWL_UCODE_SECTION_DATA));
		वापस -1;
	पूर्ण

	अगर (get_sec_size(pieces, IWL_UCODE_INIT, IWL_UCODE_SECTION_INST) >
	     cfg->max_inst_size) अणु
		IWL_ERR(drv, "uCode init instr len %zd too large to fit in\n",
			get_sec_size(pieces, IWL_UCODE_INIT,
				     IWL_UCODE_SECTION_INST));
		वापस -1;
	पूर्ण

	अगर (get_sec_size(pieces, IWL_UCODE_INIT, IWL_UCODE_SECTION_DATA) >
	    cfg->max_data_size) अणु
		IWL_ERR(drv, "uCode init data len %zd too large to fit in\n",
			get_sec_size(pieces, IWL_UCODE_REGULAR,
				     IWL_UCODE_SECTION_DATA));
		वापस -1;
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा iwl_op_mode *
_iwl_op_mode_start(काष्ठा iwl_drv *drv, काष्ठा iwlwअगरi_opmode_table *op)
अणु
	स्थिर काष्ठा iwl_op_mode_ops *ops = op->ops;
	काष्ठा dentry *dbgfs_dir = शून्य;
	काष्ठा iwl_op_mode *op_mode = शून्य;

#अगर_घोषित CONFIG_IWLWIFI_DEBUGFS
	drv->dbgfs_op_mode = debugfs_create_dir(op->name,
						drv->dbgfs_drv);
	dbgfs_dir = drv->dbgfs_op_mode;
#पूर्ण_अगर

	op_mode = ops->start(drv->trans, drv->trans->cfg, &drv->fw, dbgfs_dir);

#अगर_घोषित CONFIG_IWLWIFI_DEBUGFS
	अगर (!op_mode) अणु
		debugfs_हटाओ_recursive(drv->dbgfs_op_mode);
		drv->dbgfs_op_mode = शून्य;
	पूर्ण
#पूर्ण_अगर

	वापस op_mode;
पूर्ण

अटल व्योम _iwl_op_mode_stop(काष्ठा iwl_drv *drv)
अणु
	/* op_mode can be शून्य अगर its start failed */
	अगर (drv->op_mode) अणु
		iwl_op_mode_stop(drv->op_mode);
		drv->op_mode = शून्य;

#अगर_घोषित CONFIG_IWLWIFI_DEBUGFS
		debugfs_हटाओ_recursive(drv->dbgfs_op_mode);
		drv->dbgfs_op_mode = शून्य;
#पूर्ण_अगर
	पूर्ण
पूर्ण

/*
 * iwl_req_fw_callback - callback when firmware was loaded
 *
 * If loaded successfully, copies the firmware पूर्णांकo buffers
 * क्रम the card to fetch (via DMA).
 */
अटल व्योम iwl_req_fw_callback(स्थिर काष्ठा firmware *ucode_raw, व्योम *context)
अणु
	काष्ठा iwl_drv *drv = context;
	काष्ठा iwl_fw *fw = &drv->fw;
	काष्ठा iwl_ucode_header *ucode;
	काष्ठा iwlwअगरi_opmode_table *op;
	पूर्णांक err;
	काष्ठा iwl_firmware_pieces *pieces;
	स्थिर अचिन्हित पूर्णांक api_max = drv->trans->cfg->ucode_api_max;
	स्थिर अचिन्हित पूर्णांक api_min = drv->trans->cfg->ucode_api_min;
	माप_प्रकार trigger_tlv_sz[FW_DBG_TRIGGER_MAX];
	u32 api_ver;
	पूर्णांक i;
	bool load_module = false;
	bool usnअगरfer_images = false;

	fw->ucode_capa.max_probe_length = IWL_DEFAULT_MAX_PROBE_LENGTH;
	fw->ucode_capa.standard_phy_calibration_size =
			IWL_DEFAULT_STANDARD_PHY_CALIBRATE_TBL_SIZE;
	fw->ucode_capa.n_scan_channels = IWL_DEFAULT_SCAN_CHANNELS;
	fw->ucode_capa.num_stations = IWL_MVM_STATION_COUNT_MAX;
	/* dump all fw memory areas by शेष */
	fw->dbg.dump_mask = 0xffffffff;

	pieces = kzalloc(माप(*pieces), GFP_KERNEL);
	अगर (!pieces)
		जाओ out_मुक्त_fw;

	अगर (!ucode_raw)
		जाओ try_again;

	IWL_DEBUG_FW_INFO(drv, "Loaded firmware file '%s' (%zd bytes).\n",
			  drv->firmware_name, ucode_raw->size);

	/* Make sure that we got at least the API version number */
	अगर (ucode_raw->size < 4) अणु
		IWL_ERR(drv, "File size way too small!\n");
		जाओ try_again;
	पूर्ण

	/* Data from ucode file:  header followed by uCode images */
	ucode = (काष्ठा iwl_ucode_header *)ucode_raw->data;

	अगर (ucode->ver)
		err = iwl_parse_v1_v2_firmware(drv, ucode_raw, pieces);
	अन्यथा
		err = iwl_parse_tlv_firmware(drv, ucode_raw, pieces,
					     &fw->ucode_capa, &usnअगरfer_images);

	अगर (err)
		जाओ try_again;

	अगर (fw_has_api(&drv->fw.ucode_capa, IWL_UCODE_TLV_API_NEW_VERSION))
		api_ver = drv->fw.ucode_ver;
	अन्यथा
		api_ver = IWL_UCODE_API(drv->fw.ucode_ver);

	/*
	 * api_ver should match the api version क्रमming part of the
	 * firmware filename ... but we करोn't check क्रम that and only rely
	 * on the API version पढ़ो from firmware header from here on क्रमward
	 */
	अगर (api_ver < api_min || api_ver > api_max) अणु
		IWL_ERR(drv,
			"Driver unable to support your firmware API. "
			"Driver supports v%u, firmware is v%u.\n",
			api_max, api_ver);
		जाओ try_again;
	पूर्ण

	/*
	 * In mvm uCode there is no dअगरference between data and inकाष्ठाions
	 * sections.
	 */
	अगर (fw->type == IWL_FW_DVM && validate_sec_sizes(drv, pieces,
							 drv->trans->cfg))
		जाओ try_again;

	/* Allocate ucode buffers क्रम card's bus-master loading ... */

	/* Runसमय inकाष्ठाions and 2 copies of data:
	 * 1) unmodअगरied from disk
	 * 2) backup cache क्रम save/restore during घातer-करोwns
	 */
	क्रम (i = 0; i < IWL_UCODE_TYPE_MAX; i++)
		अगर (iwl_alloc_ucode(drv, pieces, i))
			जाओ out_मुक्त_fw;

	अगर (pieces->dbg_dest_tlv_init) अणु
		माप_प्रकार dbg_dest_size = माप(*drv->fw.dbg.dest_tlv) +
			माप(drv->fw.dbg.dest_tlv->reg_ops[0]) *
			drv->fw.dbg.n_dest_reg;

		drv->fw.dbg.dest_tlv = kदो_स्मृति(dbg_dest_size, GFP_KERNEL);

		अगर (!drv->fw.dbg.dest_tlv)
			जाओ out_मुक्त_fw;

		अगर (*pieces->dbg_dest_ver == 0) अणु
			स_नकल(drv->fw.dbg.dest_tlv, pieces->dbg_dest_tlv_v1,
			       dbg_dest_size);
		पूर्ण अन्यथा अणु
			काष्ठा iwl_fw_dbg_dest_tlv_v1 *dest_tlv =
				drv->fw.dbg.dest_tlv;

			dest_tlv->version = pieces->dbg_dest_tlv->version;
			dest_tlv->monitor_mode =
				pieces->dbg_dest_tlv->monitor_mode;
			dest_tlv->size_घातer =
				pieces->dbg_dest_tlv->size_घातer;
			dest_tlv->wrap_count =
				pieces->dbg_dest_tlv->wrap_count;
			dest_tlv->ग_लिखो_ptr_reg =
				pieces->dbg_dest_tlv->ग_लिखो_ptr_reg;
			dest_tlv->base_shअगरt =
				pieces->dbg_dest_tlv->base_shअगरt;
			स_नकल(dest_tlv->reg_ops,
			       pieces->dbg_dest_tlv->reg_ops,
			       माप(drv->fw.dbg.dest_tlv->reg_ops[0]) *
			       drv->fw.dbg.n_dest_reg);

			/* In version 1 of the destination tlv, which is
			 * relevant क्रम पूर्णांकernal buffer exclusively,
			 * the base address is part of given with the length
			 * of the buffer, and the size shअगरt is give instead of
			 * end shअगरt. We now store these values in base_reg,
			 * and end shअगरt, and when dumping the data we'll
			 * manipulate it क्रम extracting both the length and
			 * base address */
			dest_tlv->base_reg = pieces->dbg_dest_tlv->cfg_reg;
			dest_tlv->end_shअगरt =
				pieces->dbg_dest_tlv->size_shअगरt;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(drv->fw.dbg.conf_tlv); i++) अणु
		अगर (pieces->dbg_conf_tlv[i]) अणु
			drv->fw.dbg.conf_tlv[i] =
				kmemdup(pieces->dbg_conf_tlv[i],
					pieces->dbg_conf_tlv_len[i],
					GFP_KERNEL);
			अगर (!drv->fw.dbg.conf_tlv[i])
				जाओ out_मुक्त_fw;
		पूर्ण
	पूर्ण

	स_रखो(&trigger_tlv_sz, 0xff, माप(trigger_tlv_sz));

	trigger_tlv_sz[FW_DBG_TRIGGER_MISSED_BEACONS] =
		माप(काष्ठा iwl_fw_dbg_trigger_missed_bcon);
	trigger_tlv_sz[FW_DBG_TRIGGER_CHANNEL_SWITCH] = 0;
	trigger_tlv_sz[FW_DBG_TRIGGER_FW_NOTIF] =
		माप(काष्ठा iwl_fw_dbg_trigger_cmd);
	trigger_tlv_sz[FW_DBG_TRIGGER_MLME] =
		माप(काष्ठा iwl_fw_dbg_trigger_mlme);
	trigger_tlv_sz[FW_DBG_TRIGGER_STATS] =
		माप(काष्ठा iwl_fw_dbg_trigger_stats);
	trigger_tlv_sz[FW_DBG_TRIGGER_RSSI] =
		माप(काष्ठा iwl_fw_dbg_trigger_low_rssi);
	trigger_tlv_sz[FW_DBG_TRIGGER_TXQ_TIMERS] =
		माप(काष्ठा iwl_fw_dbg_trigger_txq_समयr);
	trigger_tlv_sz[FW_DBG_TRIGGER_TIME_EVENT] =
		माप(काष्ठा iwl_fw_dbg_trigger_समय_event);
	trigger_tlv_sz[FW_DBG_TRIGGER_BA] =
		माप(काष्ठा iwl_fw_dbg_trigger_ba);
	trigger_tlv_sz[FW_DBG_TRIGGER_TDLS] =
		माप(काष्ठा iwl_fw_dbg_trigger_tdls);

	क्रम (i = 0; i < ARRAY_SIZE(drv->fw.dbg.trigger_tlv); i++) अणु
		अगर (pieces->dbg_trigger_tlv[i]) अणु
			/*
			 * If the trigger isn't दीर्घ enough, WARN and निकास.
			 * Someone is trying to debug something and he won't
			 * be able to catch the bug he is trying to chase.
			 * We'd better be noisy to be sure he knows what's
			 * going on.
			 */
			अगर (WARN_ON(pieces->dbg_trigger_tlv_len[i] <
				    (trigger_tlv_sz[i] +
				     माप(काष्ठा iwl_fw_dbg_trigger_tlv))))
				जाओ out_मुक्त_fw;
			drv->fw.dbg.trigger_tlv_len[i] =
				pieces->dbg_trigger_tlv_len[i];
			drv->fw.dbg.trigger_tlv[i] =
				kmemdup(pieces->dbg_trigger_tlv[i],
					drv->fw.dbg.trigger_tlv_len[i],
					GFP_KERNEL);
			अगर (!drv->fw.dbg.trigger_tlv[i])
				जाओ out_मुक्त_fw;
		पूर्ण
	पूर्ण

	/* Now that we can no दीर्घer fail, copy inक्रमmation */

	drv->fw.dbg.mem_tlv = pieces->dbg_mem_tlv;
	pieces->dbg_mem_tlv = शून्य;
	drv->fw.dbg.n_mem_tlv = pieces->n_mem_tlv;

	/*
	 * The (size - 16) / 12 क्रमmula is based on the inक्रमmation recorded
	 * क्रम each event, which is of mode 1 (including बारtamp) क्रम all
	 * new microcodes that include this inक्रमmation.
	 */
	fw->init_evtlog_ptr = pieces->init_evtlog_ptr;
	अगर (pieces->init_evtlog_size)
		fw->init_evtlog_size = (pieces->init_evtlog_size - 16)/12;
	अन्यथा
		fw->init_evtlog_size =
			drv->trans->trans_cfg->base_params->max_event_log_size;
	fw->init_errlog_ptr = pieces->init_errlog_ptr;
	fw->inst_evtlog_ptr = pieces->inst_evtlog_ptr;
	अगर (pieces->inst_evtlog_size)
		fw->inst_evtlog_size = (pieces->inst_evtlog_size - 16)/12;
	अन्यथा
		fw->inst_evtlog_size =
			drv->trans->trans_cfg->base_params->max_event_log_size;
	fw->inst_errlog_ptr = pieces->inst_errlog_ptr;

	/*
	 * figure out the offset of chain noise reset and gain commands
	 * base on the size of standard phy calibration commands table size
	 */
	अगर (fw->ucode_capa.standard_phy_calibration_size >
	    IWL_MAX_PHY_CALIBRATE_TBL_SIZE)
		fw->ucode_capa.standard_phy_calibration_size =
			IWL_MAX_STANDARD_PHY_CALIBRATE_TBL_SIZE;

	/* We have our copies now, allow OS release its copies */
	release_firmware(ucode_raw);

	mutex_lock(&iwlwअगरi_opmode_table_mtx);
	चयन (fw->type) अणु
	हाल IWL_FW_DVM:
		op = &iwlwअगरi_opmode_table[DVM_OP_MODE];
		अवरोध;
	शेष:
		WARN(1, "Invalid fw type %d\n", fw->type);
		fallthrough;
	हाल IWL_FW_MVM:
		op = &iwlwअगरi_opmode_table[MVM_OP_MODE];
		अवरोध;
	पूर्ण

	IWL_INFO(drv, "loaded firmware version %s op_mode %s\n",
		 drv->fw.fw_version, op->name);

	iwl_dbg_tlv_load_bin(drv->trans->dev, drv->trans);

	/* add this device to the list of devices using this op_mode */
	list_add_tail(&drv->list, &op->drv);

	अगर (op->ops) अणु
		drv->op_mode = _iwl_op_mode_start(drv, op);

		अगर (!drv->op_mode) अणु
			mutex_unlock(&iwlwअगरi_opmode_table_mtx);
			जाओ out_unbind;
		पूर्ण
	पूर्ण अन्यथा अणु
		load_module = true;
	पूर्ण
	mutex_unlock(&iwlwअगरi_opmode_table_mtx);

	/*
	 * Complete the firmware request last so that
	 * a driver unbind (stop) करोesn't run जबतक we
	 * are करोing the start() above.
	 */
	complete(&drv->request_firmware_complete);

	/*
	 * Load the module last so we करोn't block anything
	 * अन्यथा from proceeding अगर the module fails to load
	 * or hangs loading.
	 */
	अगर (load_module) अणु
		request_module("%s", op->name);
#अगर_घोषित CONFIG_IWLWIFI_OPMODE_MODULAR
		अगर (err)
			IWL_ERR(drv,
				"failed to load module %s (error %d), is dynamic loading enabled?\n",
				op->name, err);
#पूर्ण_अगर
	पूर्ण
	जाओ मुक्त;

 try_again:
	/* try next, अगर any */
	release_firmware(ucode_raw);
	अगर (iwl_request_firmware(drv, false))
		जाओ out_unbind;
	जाओ मुक्त;

 out_मुक्त_fw:
	release_firmware(ucode_raw);
 out_unbind:
	complete(&drv->request_firmware_complete);
	device_release_driver(drv->trans->dev);
 मुक्त:
	अगर (pieces) अणु
		क्रम (i = 0; i < ARRAY_SIZE(pieces->img); i++)
			kमुक्त(pieces->img[i].sec);
		kमुक्त(pieces->dbg_mem_tlv);
		kमुक्त(pieces);
	पूर्ण
पूर्ण

काष्ठा iwl_drv *iwl_drv_start(काष्ठा iwl_trans *trans)
अणु
	काष्ठा iwl_drv *drv;
	पूर्णांक ret;

	drv = kzalloc(माप(*drv), GFP_KERNEL);
	अगर (!drv) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	drv->trans = trans;
	drv->dev = trans->dev;

	init_completion(&drv->request_firmware_complete);
	INIT_LIST_HEAD(&drv->list);

#अगर_घोषित CONFIG_IWLWIFI_DEBUGFS
	/* Create the device debugfs entries. */
	drv->dbgfs_drv = debugfs_create_dir(dev_name(trans->dev),
					    iwl_dbgfs_root);

	/* Create transport layer debugfs dir */
	drv->trans->dbgfs_dir = debugfs_create_dir("trans", drv->dbgfs_drv);
#पूर्ण_अगर

	drv->trans->dbg.करोमुख्यs_biपंचांगap = IWL_TRANS_FW_DBG_DOMAIN(drv->trans);

	ret = iwl_request_firmware(drv, true);
	अगर (ret) अणु
		IWL_ERR(trans, "Couldn't request the fw\n");
		जाओ err_fw;
	पूर्ण

	वापस drv;

err_fw:
#अगर_घोषित CONFIG_IWLWIFI_DEBUGFS
	debugfs_हटाओ_recursive(drv->dbgfs_drv);
	iwl_dbg_tlv_मुक्त(drv->trans);
#पूर्ण_अगर
	kमुक्त(drv);
err:
	वापस ERR_PTR(ret);
पूर्ण

व्योम iwl_drv_stop(काष्ठा iwl_drv *drv)
अणु
	रुको_क्रम_completion(&drv->request_firmware_complete);

	_iwl_op_mode_stop(drv);

	iwl_dealloc_ucode(drv);

	mutex_lock(&iwlwअगरi_opmode_table_mtx);
	/*
	 * List is empty (this item wasn't added)
	 * when firmware loading failed -- in that
	 * हाल we can't हटाओ it from any list.
	 */
	अगर (!list_empty(&drv->list))
		list_del(&drv->list);
	mutex_unlock(&iwlwअगरi_opmode_table_mtx);

#अगर_घोषित CONFIG_IWLWIFI_DEBUGFS
	drv->trans->ops->debugfs_cleanup(drv->trans);

	debugfs_हटाओ_recursive(drv->dbgfs_drv);
#पूर्ण_अगर

	iwl_dbg_tlv_मुक्त(drv->trans);

	kमुक्त(drv);
पूर्ण


/* shared module parameters */
काष्ठा iwl_mod_params iwlwअगरi_mod_params = अणु
	.fw_restart = true,
	.bt_coex_active = true,
	.घातer_level = IWL_POWER_INDEX_1,
	.uapsd_disable = IWL_DISABLE_UAPSD_BSS | IWL_DISABLE_UAPSD_P2P_CLIENT,
	.enable_ini = true,
	/* the rest are 0 by शेष */
पूर्ण;
IWL_EXPORT_SYMBOL(iwlwअगरi_mod_params);

पूर्णांक iwl_opmode_रेजिस्टर(स्थिर अक्षर *name, स्थिर काष्ठा iwl_op_mode_ops *ops)
अणु
	पूर्णांक i;
	काष्ठा iwl_drv *drv;
	काष्ठा iwlwअगरi_opmode_table *op;

	mutex_lock(&iwlwअगरi_opmode_table_mtx);
	क्रम (i = 0; i < ARRAY_SIZE(iwlwअगरi_opmode_table); i++) अणु
		op = &iwlwअगरi_opmode_table[i];
		अगर (म_भेद(op->name, name))
			जारी;
		op->ops = ops;
		/* TODO: need to handle exceptional हाल */
		list_क्रम_each_entry(drv, &op->drv, list)
			drv->op_mode = _iwl_op_mode_start(drv, op);

		mutex_unlock(&iwlwअगरi_opmode_table_mtx);
		वापस 0;
	पूर्ण
	mutex_unlock(&iwlwअगरi_opmode_table_mtx);
	वापस -EIO;
पूर्ण
IWL_EXPORT_SYMBOL(iwl_opmode_रेजिस्टर);

व्योम iwl_opmode_deरेजिस्टर(स्थिर अक्षर *name)
अणु
	पूर्णांक i;
	काष्ठा iwl_drv *drv;

	mutex_lock(&iwlwअगरi_opmode_table_mtx);
	क्रम (i = 0; i < ARRAY_SIZE(iwlwअगरi_opmode_table); i++) अणु
		अगर (म_भेद(iwlwअगरi_opmode_table[i].name, name))
			जारी;
		iwlwअगरi_opmode_table[i].ops = शून्य;

		/* call the stop routine क्रम all devices */
		list_क्रम_each_entry(drv, &iwlwअगरi_opmode_table[i].drv, list)
			_iwl_op_mode_stop(drv);

		mutex_unlock(&iwlwअगरi_opmode_table_mtx);
		वापस;
	पूर्ण
	mutex_unlock(&iwlwअगरi_opmode_table_mtx);
पूर्ण
IWL_EXPORT_SYMBOL(iwl_opmode_deरेजिस्टर);

अटल पूर्णांक __init iwl_drv_init(व्योम)
अणु
	पूर्णांक i, err;

	mutex_init(&iwlwअगरi_opmode_table_mtx);

	क्रम (i = 0; i < ARRAY_SIZE(iwlwअगरi_opmode_table); i++)
		INIT_LIST_HEAD(&iwlwअगरi_opmode_table[i].drv);

	pr_info(DRV_DESCRIPTION "\n");

#अगर_घोषित CONFIG_IWLWIFI_DEBUGFS
	/* Create the root of iwlwअगरi debugfs subप्रणाली. */
	iwl_dbgfs_root = debugfs_create_dir(DRV_NAME, शून्य);
#पूर्ण_अगर

	err = iwl_pci_रेजिस्टर_driver();
	अगर (err)
		जाओ cleanup_debugfs;

	वापस 0;

cleanup_debugfs:
#अगर_घोषित CONFIG_IWLWIFI_DEBUGFS
	debugfs_हटाओ_recursive(iwl_dbgfs_root);
#पूर्ण_अगर
	वापस err;
पूर्ण
module_init(iwl_drv_init);

अटल व्योम __निकास iwl_drv_निकास(व्योम)
अणु
	iwl_pci_unरेजिस्टर_driver();

#अगर_घोषित CONFIG_IWLWIFI_DEBUGFS
	debugfs_हटाओ_recursive(iwl_dbgfs_root);
#पूर्ण_अगर
पूर्ण
module_निकास(iwl_drv_निकास);

#अगर_घोषित CONFIG_IWLWIFI_DEBUG
module_param_named(debug, iwlwअगरi_mod_params.debug_level, uपूर्णांक, 0644);
MODULE_PARM_DESC(debug, "debug output mask");
#पूर्ण_अगर

module_param_named(swcrypto, iwlwअगरi_mod_params.swcrypto, पूर्णांक, 0444);
MODULE_PARM_DESC(swcrypto, "using crypto in software (default 0 [hardware])");
module_param_named(11n_disable, iwlwअगरi_mod_params.disable_11n, uपूर्णांक, 0444);
MODULE_PARM_DESC(11n_disable,
	"disable 11n functionality, bitmap: 1: full, 2: disable agg TX, 4: disable agg RX, 8 enable agg TX");
module_param_named(amsdu_size, iwlwअगरi_mod_params.amsdu_size, पूर्णांक, 0444);
MODULE_PARM_DESC(amsdu_size,
		 "amsdu size 0: 12K for multi Rx queue devices, 2K for AX210 devices, "
		 "4K for other devices 1:4K 2:8K 3:12K (16K buffers) 4: 2K (default 0)");
module_param_named(fw_restart, iwlwअगरi_mod_params.fw_restart, bool, 0444);
MODULE_PARM_DESC(fw_restart, "restart firmware in case of error (default true)");

module_param_named(nvm_file, iwlwअगरi_mod_params.nvm_file, अक्षरp, 0444);
MODULE_PARM_DESC(nvm_file, "NVM file name");

module_param_named(uapsd_disable, iwlwअगरi_mod_params.uapsd_disable, uपूर्णांक, 0644);
MODULE_PARM_DESC(uapsd_disable,
		 "disable U-APSD functionality bitmap 1: BSS 2: P2P Client (default: 3)");
module_param_named(enable_ini, iwlwअगरi_mod_params.enable_ini,
		   bool, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(enable_ini,
		 "Enable debug INI TLV FW debug infrastructure (default: true");

/*
 * set bt_coex_active to true, uCode will करो समाप्त/defer
 * every समय the priority line is निश्चितed (BT is sending संकेतs on the
 * priority line in the PCIx).
 * set bt_coex_active to false, uCode will ignore the BT activity and
 * perक्रमm the normal operation
 *
 * User might experience transmit issue on some platक्रमm due to WiFi/BT
 * co-exist problem. The possible behaviors are:
 *   Able to scan and finding all the available AP
 *   Not able to associate with any AP
 * On those platक्रमms, WiFi communication can be restored by set
 * "bt_coex_active" module parameter to "false"
 *
 * शेष: bt_coex_active = true (BT_COEX_ENABLE)
 */
module_param_named(bt_coex_active, iwlwअगरi_mod_params.bt_coex_active,
		   bool, 0444);
MODULE_PARM_DESC(bt_coex_active, "enable wifi/bt co-exist (default: enable)");

module_param_named(led_mode, iwlwअगरi_mod_params.led_mode, पूर्णांक, 0444);
MODULE_PARM_DESC(led_mode, "0=system default, "
		"1=On(RF On)/Off(RF Off), 2=blinking, 3=Off (default: 0)");

module_param_named(घातer_save, iwlwअगरi_mod_params.घातer_save, bool, 0444);
MODULE_PARM_DESC(घातer_save,
		 "enable WiFi power management (default: disable)");

module_param_named(घातer_level, iwlwअगरi_mod_params.घातer_level, पूर्णांक, 0444);
MODULE_PARM_DESC(घातer_level,
		 "default power save level (range from 1 - 5, default: 1)");

module_param_named(disable_11ac, iwlwअगरi_mod_params.disable_11ac, bool, 0444);
MODULE_PARM_DESC(disable_11ac, "Disable VHT capabilities (default: false)");

module_param_named(हटाओ_when_gone,
		   iwlwअगरi_mod_params.हटाओ_when_gone, bool,
		   0444);
MODULE_PARM_DESC(हटाओ_when_gone,
		 "Remove dev from PCIe bus if it is deemed inaccessible (default: false)");

module_param_named(disable_11ax, iwlwअगरi_mod_params.disable_11ax, bool,
		   S_IRUGO);
MODULE_PARM_DESC(disable_11ax, "Disable HE capabilities (default: false)");
