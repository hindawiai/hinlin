<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  skl-sst-utils.c - SKL sst utils functions
 *
 *  Copyright (C) 2016 Intel Corp
 */

#समावेश <linux/device.h>
#समावेश <linux/slab.h>
#समावेश <linux/uuid.h>
#समावेश "../common/sst-dsp.h"
#समावेश "../common/sst-dsp-priv.h"
#समावेश "skl.h"

#घोषणा DEFAULT_HASH_SHA256_LEN 32

/* FW Extended Manअगरest Header id = $AE1 */
#घोषणा SKL_EXT_MANIFEST_HEADER_MAGIC   0x31454124

जोड़ seg_flags अणु
	u32 ul;
	काष्ठा अणु
		u32 contents : 1;
		u32 alloc    : 1;
		u32 load     : 1;
		u32 पढ़ो_only : 1;
		u32 code     : 1;
		u32 data     : 1;
		u32 _rsvd0   : 2;
		u32 type     : 4;
		u32 _rsvd1   : 4;
		u32 length   : 16;
	पूर्ण r;
पूर्ण __packed;

काष्ठा segment_desc अणु
	जोड़ seg_flags flags;
	u32 v_base_addr;
	u32 file_offset;
पूर्ण;

काष्ठा module_type अणु
	u32 load_type  : 4;
	u32 स्वतः_start : 1;
	u32 करोमुख्य_ll  : 1;
	u32 करोमुख्य_dp  : 1;
	u32 rsvd       : 25;
पूर्ण __packed;

काष्ठा adsp_module_entry अणु
	u32 काष्ठा_id;
	u8  name[8];
	u8  uuid[16];
	काष्ठा module_type type;
	u8  hash1[DEFAULT_HASH_SHA256_LEN];
	u32 entry_poपूर्णांक;
	u16 cfg_offset;
	u16 cfg_count;
	u32 affinity_mask;
	u16 instance_max_count;
	u16 instance_bss_size;
	काष्ठा segment_desc segments[3];
पूर्ण __packed;

काष्ठा adsp_fw_hdr अणु
	u32 id;
	u32 len;
	u8  name[8];
	u32 preload_page_count;
	u32 fw_image_flags;
	u32 feature_mask;
	u16 major;
	u16 minor;
	u16 hotfix;
	u16 build;
	u32 num_modules;
	u32 hw_buf_base;
	u32 hw_buf_length;
	u32 load_offset;
पूर्ण __packed;

काष्ठा skl_ext_manअगरest_hdr अणु
	u32 id;
	u32 len;
	u16 version_major;
	u16 version_minor;
	u32 entries;
पूर्ण;

अटल पूर्णांक skl_get_pvtid_map(काष्ठा uuid_module *module, पूर्णांक instance_id)
अणु
	पूर्णांक pvt_id;

	क्रम (pvt_id = 0; pvt_id < module->max_instance; pvt_id++) अणु
		अगर (module->instance_id[pvt_id] == instance_id)
			वापस pvt_id;
	पूर्ण
	वापस -EINVAL;
पूर्ण

पूर्णांक skl_get_pvt_instance_id_map(काष्ठा skl_dev *skl,
				पूर्णांक module_id, पूर्णांक instance_id)
अणु
	काष्ठा uuid_module *module;

	list_क्रम_each_entry(module, &skl->uuid_list, list) अणु
		अगर (module->id == module_id)
			वापस skl_get_pvtid_map(module, instance_id);
	पूर्ण

	वापस -EINVAL;
पूर्ण
EXPORT_SYMBOL_GPL(skl_get_pvt_instance_id_map);

अटल अंतरभूत पूर्णांक skl_getid_32(काष्ठा uuid_module *module, u64 *val,
				पूर्णांक word1_mask, पूर्णांक word2_mask)
अणु
	पूर्णांक index, max_inst, pvt_id;
	u32 mask_val;

	max_inst =  module->max_instance;
	mask_val = (u32)(*val >> word1_mask);

	अगर (mask_val != 0xffffffff) अणु
		index = ffz(mask_val);
		pvt_id = index + word1_mask + word2_mask;
		अगर (pvt_id <= (max_inst - 1)) अणु
			*val |= 1ULL << (index + word1_mask);
			वापस pvt_id;
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल अंतरभूत पूर्णांक skl_pvtid_128(काष्ठा uuid_module *module)
अणु
	पूर्णांक j, i, word1_mask, word2_mask = 0, pvt_id;

	क्रम (j = 0; j < MAX_INSTANCE_BUFF; j++) अणु
		word1_mask = 0;

		क्रम (i = 0; i < 2; i++) अणु
			pvt_id = skl_getid_32(module, &module->pvt_id[j],
						word1_mask, word2_mask);
			अगर (pvt_id >= 0)
				वापस pvt_id;

			word1_mask += 32;
			अगर ((word1_mask + word2_mask) >= module->max_instance)
				वापस -EINVAL;
		पूर्ण

		word2_mask += 64;
		अगर (word2_mask >= module->max_instance)
			वापस -EINVAL;
	पूर्ण

	वापस -EINVAL;
पूर्ण

/**
 * skl_get_pvt_id: generate a निजी id क्रम use as module id
 *
 * @skl: driver context
 * @uuid_mod: module's uuid
 * @instance_id: module's instance id
 *
 * This generates a 128 bit निजी unique id क्रम a module TYPE so that
 * module instance is unique
 */
पूर्णांक skl_get_pvt_id(काष्ठा skl_dev *skl, guid_t *uuid_mod, पूर्णांक instance_id)
अणु
	काष्ठा uuid_module *module;
	पूर्णांक pvt_id;

	list_क्रम_each_entry(module, &skl->uuid_list, list) अणु
		अगर (guid_equal(uuid_mod, &module->uuid)) अणु

			pvt_id = skl_pvtid_128(module);
			अगर (pvt_id >= 0) अणु
				module->instance_id[pvt_id] = instance_id;

				वापस pvt_id;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण
EXPORT_SYMBOL_GPL(skl_get_pvt_id);

/**
 * skl_put_pvt_id: मुक्त up the निजी id allocated
 *
 * @skl: driver context
 * @uuid_mod: module's uuid
 * @pvt_id: module pvt id
 *
 * This मुक्तs a 128 bit निजी unique id previously generated
 */
पूर्णांक skl_put_pvt_id(काष्ठा skl_dev *skl, guid_t *uuid_mod, पूर्णांक *pvt_id)
अणु
	पूर्णांक i;
	काष्ठा uuid_module *module;

	list_क्रम_each_entry(module, &skl->uuid_list, list) अणु
		अगर (guid_equal(uuid_mod, &module->uuid)) अणु

			अगर (*pvt_id != 0)
				i = (*pvt_id) / 64;
			अन्यथा
				i = 0;

			module->pvt_id[i] &= ~(1 << (*pvt_id));
			*pvt_id = -1;
			वापस 0;
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण
EXPORT_SYMBOL_GPL(skl_put_pvt_id);

/*
 * Parse the firmware binary to get the UUID, module id
 * and loadable flags
 */
पूर्णांक snd_skl_parse_uuids(काष्ठा sst_dsp *ctx, स्थिर काष्ठा firmware *fw,
			अचिन्हित पूर्णांक offset, पूर्णांक index)
अणु
	काष्ठा adsp_fw_hdr *adsp_hdr;
	काष्ठा adsp_module_entry *mod_entry;
	पूर्णांक i, num_entry, size;
	स्थिर अक्षर *buf;
	काष्ठा skl_dev *skl = ctx->thपढ़ो_context;
	काष्ठा uuid_module *module;
	काष्ठा firmware stripped_fw;
	अचिन्हित पूर्णांक safe_file;
	पूर्णांक ret;

	/* Get the FW poपूर्णांकer to derive ADSP header */
	stripped_fw.data = fw->data;
	stripped_fw.size = fw->size;

	skl_dsp_strip_extended_manअगरest(&stripped_fw);

	buf = stripped_fw.data;

	/* check अगर we have enough space in file to move to header */
	safe_file = माप(*adsp_hdr) + offset;
	अगर (stripped_fw.size <= safe_file) अणु
		dev_err(ctx->dev, "Small fw file size, No space for hdr\n");
		वापस -EINVAL;
	पूर्ण

	adsp_hdr = (काष्ठा adsp_fw_hdr *)(buf + offset);

	/* check 1st module entry is in file */
	safe_file += adsp_hdr->len + माप(*mod_entry);
	अगर (stripped_fw.size <= safe_file) अणु
		dev_err(ctx->dev, "Small fw file size, No module entry\n");
		वापस -EINVAL;
	पूर्ण

	mod_entry = (काष्ठा adsp_module_entry *)(buf + offset + adsp_hdr->len);

	num_entry = adsp_hdr->num_modules;

	/* check all entries are in file */
	safe_file += num_entry * माप(*mod_entry);
	अगर (stripped_fw.size <= safe_file) अणु
		dev_err(ctx->dev, "Small fw file size, No modules\n");
		वापस -EINVAL;
	पूर्ण


	/*
	 * Read the UUID(GUID) from FW Manअगरest.
	 *
	 * The 16 byte UUID क्रमmat is: XXXXXXXX-XXXX-XXXX-XXXX-XXXXXXXXXX
	 * Populate the UUID table to store module_id and loadable flags
	 * क्रम the module.
	 */

	क्रम (i = 0; i < num_entry; i++, mod_entry++) अणु
		module = kzalloc(माप(*module), GFP_KERNEL);
		अगर (!module) अणु
			ret = -ENOMEM;
			जाओ मुक्त_uuid_list;
		पूर्ण

		import_guid(&module->uuid, mod_entry->uuid);

		module->id = (i | (index << 12));
		module->is_loadable = mod_entry->type.load_type;
		module->max_instance = mod_entry->instance_max_count;
		size = माप(पूर्णांक) * mod_entry->instance_max_count;
		module->instance_id = devm_kzalloc(ctx->dev, size, GFP_KERNEL);
		अगर (!module->instance_id) अणु
			ret = -ENOMEM;
			जाओ मुक्त_uuid_list;
		पूर्ण

		list_add_tail(&module->list, &skl->uuid_list);

		dev_dbg(ctx->dev,
			"Adding uuid :%pUL   mod id: %d  Loadable: %d\n",
			&module->uuid, module->id, module->is_loadable);
	पूर्ण

	वापस 0;

मुक्त_uuid_list:
	skl_मुक्तup_uuid_list(skl);
	वापस ret;
पूर्ण

व्योम skl_मुक्तup_uuid_list(काष्ठा skl_dev *skl)
अणु
	काष्ठा uuid_module *uuid, *_uuid;

	list_क्रम_each_entry_safe(uuid, _uuid, &skl->uuid_list, list) अणु
		list_del(&uuid->list);
		kमुक्त(uuid);
	पूर्ण
पूर्ण

/*
 * some firmware binary contains some extended manअगरest. This needs
 * to be stripped in that हाल beक्रमe we load and use that image.
 *
 * Get the module id क्रम the module by checking
 * the table क्रम the UUID क्रम the module
 */
पूर्णांक skl_dsp_strip_extended_manअगरest(काष्ठा firmware *fw)
अणु
	काष्ठा skl_ext_manअगरest_hdr *hdr;

	/* check अगर fw file is greater than header we are looking */
	अगर (fw->size < माप(hdr)) अणु
		pr_err("%s: Firmware file small, no hdr\n", __func__);
		वापस -EINVAL;
	पूर्ण

	hdr = (काष्ठा skl_ext_manअगरest_hdr *)fw->data;

	अगर (hdr->id == SKL_EXT_MANIFEST_HEADER_MAGIC) अणु
		fw->size -= hdr->len;
		fw->data += hdr->len;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक skl_sst_ctx_init(काष्ठा device *dev, पूर्णांक irq, स्थिर अक्षर *fw_name,
	काष्ठा skl_dsp_loader_ops dsp_ops, काष्ठा skl_dev **dsp,
	काष्ठा sst_dsp_device *skl_dev)
अणु
	काष्ठा skl_dev *skl = *dsp;
	काष्ठा sst_dsp *sst;

	skl->dev = dev;
	skl_dev->thपढ़ो_context = skl;
	INIT_LIST_HEAD(&skl->uuid_list);
	skl->dsp = skl_dsp_ctx_init(dev, skl_dev, irq);
	अगर (!skl->dsp) अणु
		dev_err(skl->dev, "%s: no device\n", __func__);
		वापस -ENODEV;
	पूर्ण

	sst = skl->dsp;
	sst->fw_name = fw_name;
	sst->dsp_ops = dsp_ops;
	init_रुकोqueue_head(&skl->mod_load_रुको);
	INIT_LIST_HEAD(&sst->module_list);

	skl->is_first_boot = true;

	वापस 0;
पूर्ण

पूर्णांक skl_prepare_lib_load(काष्ठा skl_dev *skl, काष्ठा skl_lib_info *linfo,
		काष्ठा firmware *stripped_fw,
		अचिन्हित पूर्णांक hdr_offset, पूर्णांक index)
अणु
	पूर्णांक ret;
	काष्ठा sst_dsp *dsp = skl->dsp;

	अगर (linfo->fw == शून्य) अणु
		ret = request_firmware(&linfo->fw, linfo->name,
					skl->dev);
		अगर (ret < 0) अणु
			dev_err(skl->dev, "Request lib %s failed:%d\n",
				linfo->name, ret);
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (skl->is_first_boot) अणु
		ret = snd_skl_parse_uuids(dsp, linfo->fw, hdr_offset, index);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	stripped_fw->data = linfo->fw->data;
	stripped_fw->size = linfo->fw->size;
	skl_dsp_strip_extended_manअगरest(stripped_fw);

	वापस 0;
पूर्ण

व्योम skl_release_library(काष्ठा skl_lib_info *linfo, पूर्णांक lib_count)
अणु
	पूर्णांक i;

	/* library indices start from 1 to N. 0 represents base FW */
	क्रम (i = 1; i < lib_count; i++) अणु
		अगर (linfo[i].fw) अणु
			release_firmware(linfo[i].fw);
			linfo[i].fw = शून्य;
		पूर्ण
	पूर्ण
पूर्ण
