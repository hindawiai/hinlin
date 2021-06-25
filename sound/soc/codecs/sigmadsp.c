<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Load Analog Devices SigmaStudio firmware files
 *
 * Copyright 2009-2014 Analog Devices Inc.
 */

#समावेश <linux/crc32.h>
#समावेश <linux/firmware.h>
#समावेश <linux/kernel.h>
#समावेश <linux/i2c.h>
#समावेश <linux/regmap.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>

#समावेश <sound/control.h>
#समावेश <sound/soc.h>

#समावेश "sigmadsp.h"

#घोषणा SIGMA_MAGIC "ADISIGM"

#घोषणा SIGMA_FW_CHUNK_TYPE_DATA 0
#घोषणा SIGMA_FW_CHUNK_TYPE_CONTROL 1
#घोषणा SIGMA_FW_CHUNK_TYPE_SAMPLERATES 2

#घोषणा READBACK_CTRL_NAME "ReadBack"

काष्ठा sigmadsp_control अणु
	काष्ठा list_head head;
	uपूर्णांक32_t samplerates;
	अचिन्हित पूर्णांक addr;
	अचिन्हित पूर्णांक num_bytes;
	स्थिर अक्षर *name;
	काष्ठा snd_kcontrol *kcontrol;
	bool is_पढ़ोback;
	bool cached;
	uपूर्णांक8_t cache[];
पूर्ण;

काष्ठा sigmadsp_data अणु
	काष्ठा list_head head;
	uपूर्णांक32_t samplerates;
	अचिन्हित पूर्णांक addr;
	अचिन्हित पूर्णांक length;
	uपूर्णांक8_t data[];
पूर्ण;

काष्ठा sigma_fw_chunk अणु
	__le32 length;
	__le32 tag;
	__le32 samplerates;
पूर्ण __packed;

काष्ठा sigma_fw_chunk_data अणु
	काष्ठा sigma_fw_chunk chunk;
	__le16 addr;
	uपूर्णांक8_t data[];
पूर्ण __packed;

काष्ठा sigma_fw_chunk_control अणु
	काष्ठा sigma_fw_chunk chunk;
	__le16 type;
	__le16 addr;
	__le16 num_bytes;
	स्थिर अक्षर name[];
पूर्ण __packed;

काष्ठा sigma_fw_chunk_samplerate अणु
	काष्ठा sigma_fw_chunk chunk;
	__le32 samplerates[];
पूर्ण __packed;

काष्ठा sigma_firmware_header अणु
	अचिन्हित अक्षर magic[7];
	u8 version;
	__le32 crc;
पूर्ण __packed;

क्रमागत अणु
	SIGMA_ACTION_WRITEXBYTES = 0,
	SIGMA_ACTION_WRITESINGLE,
	SIGMA_ACTION_WRITESAFELOAD,
	SIGMA_ACTION_END,
पूर्ण;

काष्ठा sigma_action अणु
	u8 instr;
	u8 len_hi;
	__le16 len;
	__be16 addr;
	अचिन्हित अक्षर payload[];
पूर्ण __packed;

अटल पूर्णांक sigmadsp_ग_लिखो(काष्ठा sigmadsp *sigmadsp, अचिन्हित पूर्णांक addr,
	स्थिर uपूर्णांक8_t data[], माप_प्रकार len)
अणु
	वापस sigmadsp->ग_लिखो(sigmadsp->control_data, addr, data, len);
पूर्ण

अटल पूर्णांक sigmadsp_पढ़ो(काष्ठा sigmadsp *sigmadsp, अचिन्हित पूर्णांक addr,
	uपूर्णांक8_t data[], माप_प्रकार len)
अणु
	वापस sigmadsp->पढ़ो(sigmadsp->control_data, addr, data, len);
पूर्ण

अटल पूर्णांक sigmadsp_ctrl_info(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_info *info)
अणु
	काष्ठा sigmadsp_control *ctrl = (व्योम *)kcontrol->निजी_value;

	info->type = SNDRV_CTL_ELEM_TYPE_BYTES;
	info->count = ctrl->num_bytes;

	वापस 0;
पूर्ण

अटल पूर्णांक sigmadsp_ctrl_ग_लिखो(काष्ठा sigmadsp *sigmadsp,
	काष्ठा sigmadsp_control *ctrl, व्योम *data)
अणु
	/* safeload loads up to 20 bytes in a atomic operation */
	अगर (ctrl->num_bytes <= 20 && sigmadsp->ops && sigmadsp->ops->safeload)
		वापस sigmadsp->ops->safeload(sigmadsp, ctrl->addr, data,
			ctrl->num_bytes);
	अन्यथा
		वापस sigmadsp_ग_लिखो(sigmadsp, ctrl->addr, data,
			ctrl->num_bytes);
पूर्ण

अटल पूर्णांक sigmadsp_ctrl_put(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा sigmadsp_control *ctrl = (व्योम *)kcontrol->निजी_value;
	काष्ठा sigmadsp *sigmadsp = snd_kcontrol_chip(kcontrol);
	uपूर्णांक8_t *data;
	पूर्णांक ret = 0;

	mutex_lock(&sigmadsp->lock);

	data = ucontrol->value.bytes.data;

	अगर (!(kcontrol->vd[0].access & SNDRV_CTL_ELEM_ACCESS_INACTIVE))
		ret = sigmadsp_ctrl_ग_लिखो(sigmadsp, ctrl, data);

	अगर (ret == 0) अणु
		स_नकल(ctrl->cache, data, ctrl->num_bytes);
		अगर (!ctrl->is_पढ़ोback)
			ctrl->cached = true;
	पूर्ण

	mutex_unlock(&sigmadsp->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक sigmadsp_ctrl_get(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा sigmadsp_control *ctrl = (व्योम *)kcontrol->निजी_value;
	काष्ठा sigmadsp *sigmadsp = snd_kcontrol_chip(kcontrol);
	पूर्णांक ret = 0;

	mutex_lock(&sigmadsp->lock);

	अगर (!ctrl->cached) अणु
		ret = sigmadsp_पढ़ो(sigmadsp, ctrl->addr, ctrl->cache,
			ctrl->num_bytes);
	पूर्ण

	अगर (ret == 0) अणु
		अगर (!ctrl->is_पढ़ोback)
			ctrl->cached = true;
		स_नकल(ucontrol->value.bytes.data, ctrl->cache,
			ctrl->num_bytes);
	पूर्ण

	mutex_unlock(&sigmadsp->lock);

	वापस ret;
पूर्ण

अटल व्योम sigmadsp_control_मुक्त(काष्ठा snd_kcontrol *kcontrol)
अणु
	काष्ठा sigmadsp_control *ctrl = (व्योम *)kcontrol->निजी_value;

	ctrl->kcontrol = शून्य;
पूर्ण

अटल bool sigma_fw_validate_control_name(स्थिर अक्षर *name, अचिन्हित पूर्णांक len)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < len; i++) अणु
		/* Normal ASCII अक्षरacters are valid */
		अगर (name[i] < ' ' || name[i] > '~')
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल पूर्णांक sigma_fw_load_control(काष्ठा sigmadsp *sigmadsp,
	स्थिर काष्ठा sigma_fw_chunk *chunk, अचिन्हित पूर्णांक length)
अणु
	स्थिर काष्ठा sigma_fw_chunk_control *ctrl_chunk;
	काष्ठा sigmadsp_control *ctrl;
	अचिन्हित पूर्णांक num_bytes;
	माप_प्रकार name_len;
	अक्षर *name;
	पूर्णांक ret;

	अगर (length <= माप(*ctrl_chunk))
		वापस -EINVAL;

	ctrl_chunk = (स्थिर काष्ठा sigma_fw_chunk_control *)chunk;

	name_len = length - माप(*ctrl_chunk);
	अगर (name_len >= SNDRV_CTL_ELEM_ID_NAME_MAXLEN)
		name_len = SNDRV_CTL_ELEM_ID_NAME_MAXLEN - 1;

	/* Make sure there are no non-displayable अक्षरacaters in the string */
	अगर (!sigma_fw_validate_control_name(ctrl_chunk->name, name_len))
		वापस -EINVAL;

	num_bytes = le16_to_cpu(ctrl_chunk->num_bytes);
	ctrl = kzalloc(माप(*ctrl) + num_bytes, GFP_KERNEL);
	अगर (!ctrl)
		वापस -ENOMEM;

	name = kzalloc(name_len + 1, GFP_KERNEL);
	अगर (!name) अणु
		ret = -ENOMEM;
		जाओ err_मुक्त_ctrl;
	पूर्ण
	स_नकल(name, ctrl_chunk->name, name_len);
	name[name_len] = '\0';
	ctrl->name = name;

	/*
	 * Readbacks करोesn't work with non-अस्थिर controls, since the
	 * firmware updates the control value without driver पूर्णांकeraction. Mark
	 * the पढ़ोbacks to ensure that the values are not cached.
	 */
	अगर (ctrl->name && म_भेदन(ctrl->name, READBACK_CTRL_NAME,
				  (माप(READBACK_CTRL_NAME) - 1)) == 0)
		ctrl->is_पढ़ोback = true;

	ctrl->addr = le16_to_cpu(ctrl_chunk->addr);
	ctrl->num_bytes = num_bytes;
	ctrl->samplerates = le32_to_cpu(chunk->samplerates);

	list_add_tail(&ctrl->head, &sigmadsp->ctrl_list);

	वापस 0;

err_मुक्त_ctrl:
	kमुक्त(ctrl);

	वापस ret;
पूर्ण

अटल पूर्णांक sigma_fw_load_data(काष्ठा sigmadsp *sigmadsp,
	स्थिर काष्ठा sigma_fw_chunk *chunk, अचिन्हित पूर्णांक length)
अणु
	स्थिर काष्ठा sigma_fw_chunk_data *data_chunk;
	काष्ठा sigmadsp_data *data;

	अगर (length <= माप(*data_chunk))
		वापस -EINVAL;

	data_chunk = (काष्ठा sigma_fw_chunk_data *)chunk;

	length -= माप(*data_chunk);

	data = kzalloc(माप(*data) + length, GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->addr = le16_to_cpu(data_chunk->addr);
	data->length = length;
	data->samplerates = le32_to_cpu(chunk->samplerates);
	स_नकल(data->data, data_chunk->data, length);
	list_add_tail(&data->head, &sigmadsp->data_list);

	वापस 0;
पूर्ण

अटल पूर्णांक sigma_fw_load_samplerates(काष्ठा sigmadsp *sigmadsp,
	स्थिर काष्ठा sigma_fw_chunk *chunk, अचिन्हित पूर्णांक length)
अणु
	स्थिर काष्ठा sigma_fw_chunk_samplerate *rate_chunk;
	अचिन्हित पूर्णांक num_rates;
	अचिन्हित पूर्णांक *rates;
	अचिन्हित पूर्णांक i;

	rate_chunk = (स्थिर काष्ठा sigma_fw_chunk_samplerate *)chunk;

	num_rates = (length - माप(*rate_chunk)) / माप(__le32);

	अगर (num_rates > 32 || num_rates == 0)
		वापस -EINVAL;

	/* We only allow one samplerates block per file */
	अगर (sigmadsp->rate_स्थिरraपूर्णांकs.count)
		वापस -EINVAL;

	rates = kसुस्मृति(num_rates, माप(*rates), GFP_KERNEL);
	अगर (!rates)
		वापस -ENOMEM;

	क्रम (i = 0; i < num_rates; i++)
		rates[i] = le32_to_cpu(rate_chunk->samplerates[i]);

	sigmadsp->rate_स्थिरraपूर्णांकs.count = num_rates;
	sigmadsp->rate_स्थिरraपूर्णांकs.list = rates;

	वापस 0;
पूर्ण

अटल पूर्णांक sigmadsp_fw_load_v2(काष्ठा sigmadsp *sigmadsp,
	स्थिर काष्ठा firmware *fw)
अणु
	काष्ठा sigma_fw_chunk *chunk;
	अचिन्हित पूर्णांक length, pos;
	पूर्णांक ret;

	/*
	 * Make sure that there is at least one chunk to aव्योम पूर्णांकeger
	 * underflows later on. Empty firmware is still valid though.
	 */
	अगर (fw->size < माप(*chunk) + माप(काष्ठा sigma_firmware_header))
		वापस 0;

	pos = माप(काष्ठा sigma_firmware_header);

	जबतक (pos < fw->size - माप(*chunk)) अणु
		chunk = (काष्ठा sigma_fw_chunk *)(fw->data + pos);

		length = le32_to_cpu(chunk->length);

		अगर (length > fw->size - pos || length < माप(*chunk))
			वापस -EINVAL;

		चयन (le32_to_cpu(chunk->tag)) अणु
		हाल SIGMA_FW_CHUNK_TYPE_DATA:
			ret = sigma_fw_load_data(sigmadsp, chunk, length);
			अवरोध;
		हाल SIGMA_FW_CHUNK_TYPE_CONTROL:
			ret = sigma_fw_load_control(sigmadsp, chunk, length);
			अवरोध;
		हाल SIGMA_FW_CHUNK_TYPE_SAMPLERATES:
			ret = sigma_fw_load_samplerates(sigmadsp, chunk, length);
			अवरोध;
		शेष:
			dev_warn(sigmadsp->dev, "Unknown chunk type: %d\n",
				chunk->tag);
			ret = 0;
			अवरोध;
		पूर्ण

		अगर (ret)
			वापस ret;

		/*
		 * This can not overflow since अगर length is larger than the
		 * maximum firmware size (0x4000000) we'll error out earilier.
		 */
		pos += ALIGN(length, माप(__le32));
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत u32 sigma_action_len(काष्ठा sigma_action *sa)
अणु
	वापस (sa->len_hi << 16) | le16_to_cpu(sa->len);
पूर्ण

अटल माप_प्रकार sigma_action_size(काष्ठा sigma_action *sa)
अणु
	माप_प्रकार payload = 0;

	चयन (sa->instr) अणु
	हाल SIGMA_ACTION_WRITEXBYTES:
	हाल SIGMA_ACTION_WRITESINGLE:
	हाल SIGMA_ACTION_WRITESAFELOAD:
		payload = sigma_action_len(sa);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	payload = ALIGN(payload, 2);

	वापस payload + माप(काष्ठा sigma_action);
पूर्ण

/*
 * Returns a negative error value in हाल of an error, 0 अगर processing of
 * the firmware should be stopped after this action, 1 otherwise.
 */
अटल पूर्णांक process_sigma_action(काष्ठा sigmadsp *sigmadsp,
	काष्ठा sigma_action *sa)
अणु
	माप_प्रकार len = sigma_action_len(sa);
	काष्ठा sigmadsp_data *data;

	pr_debug("%s: instr:%i addr:%#x len:%zu\n", __func__,
		sa->instr, sa->addr, len);

	चयन (sa->instr) अणु
	हाल SIGMA_ACTION_WRITEXBYTES:
	हाल SIGMA_ACTION_WRITESINGLE:
	हाल SIGMA_ACTION_WRITESAFELOAD:
		अगर (len < 3)
			वापस -EINVAL;

		data = kzalloc(माप(*data) + len - 2, GFP_KERNEL);
		अगर (!data)
			वापस -ENOMEM;

		data->addr = be16_to_cpu(sa->addr);
		data->length = len - 2;
		स_नकल(data->data, sa->payload, data->length);
		list_add_tail(&data->head, &sigmadsp->data_list);
		अवरोध;
	हाल SIGMA_ACTION_END:
		वापस 0;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 1;
पूर्ण

अटल पूर्णांक sigmadsp_fw_load_v1(काष्ठा sigmadsp *sigmadsp,
	स्थिर काष्ठा firmware *fw)
अणु
	काष्ठा sigma_action *sa;
	माप_प्रकार size, pos;
	पूर्णांक ret;

	pos = माप(काष्ठा sigma_firmware_header);

	जबतक (pos + माप(*sa) <= fw->size) अणु
		sa = (काष्ठा sigma_action *)(fw->data + pos);

		size = sigma_action_size(sa);
		pos += size;
		अगर (pos > fw->size || size == 0)
			अवरोध;

		ret = process_sigma_action(sigmadsp, sa);

		pr_debug("%s: action returned %i\n", __func__, ret);

		अगर (ret <= 0)
			वापस ret;
	पूर्ण

	अगर (pos != fw->size)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल व्योम sigmadsp_firmware_release(काष्ठा sigmadsp *sigmadsp)
अणु
	काष्ठा sigmadsp_control *ctrl, *_ctrl;
	काष्ठा sigmadsp_data *data, *_data;

	list_क्रम_each_entry_safe(ctrl, _ctrl, &sigmadsp->ctrl_list, head) अणु
		kमुक्त(ctrl->name);
		kमुक्त(ctrl);
	पूर्ण

	list_क्रम_each_entry_safe(data, _data, &sigmadsp->data_list, head)
		kमुक्त(data);

	INIT_LIST_HEAD(&sigmadsp->ctrl_list);
	INIT_LIST_HEAD(&sigmadsp->data_list);
पूर्ण

अटल व्योम devm_sigmadsp_release(काष्ठा device *dev, व्योम *res)
अणु
	sigmadsp_firmware_release((काष्ठा sigmadsp *)res);
पूर्ण

अटल पूर्णांक sigmadsp_firmware_load(काष्ठा sigmadsp *sigmadsp, स्थिर अक्षर *name)
अणु
	स्थिर काष्ठा sigma_firmware_header *ssfw_head;
	स्थिर काष्ठा firmware *fw;
	पूर्णांक ret;
	u32 crc;

	/* first load the blob */
	ret = request_firmware(&fw, name, sigmadsp->dev);
	अगर (ret) अणु
		pr_debug("%s: request_firmware() failed with %i\n", __func__, ret);
		जाओ करोne;
	पूर्ण

	/* then verअगरy the header */
	ret = -EINVAL;

	/*
	 * Reject too small or unreasonable large files. The upper limit has been
	 * chosen a bit arbitrarily, but it should be enough क्रम all practical
	 * purposes and having the limit makes it easier to aव्योम पूर्णांकeger
	 * overflows later in the loading process.
	 */
	अगर (fw->size < माप(*ssfw_head) || fw->size >= 0x4000000) अणु
		dev_err(sigmadsp->dev, "Failed to load firmware: Invalid size\n");
		जाओ करोne;
	पूर्ण

	ssfw_head = (व्योम *)fw->data;
	अगर (स_भेद(ssfw_head->magic, SIGMA_MAGIC, ARRAY_SIZE(ssfw_head->magic))) अणु
		dev_err(sigmadsp->dev, "Failed to load firmware: Invalid magic\n");
		जाओ करोne;
	पूर्ण

	crc = crc32(0, fw->data + माप(*ssfw_head),
			fw->size - माप(*ssfw_head));
	pr_debug("%s: crc=%x\n", __func__, crc);
	अगर (crc != le32_to_cpu(ssfw_head->crc)) अणु
		dev_err(sigmadsp->dev, "Failed to load firmware: Wrong crc checksum: expected %x got %x\n",
			le32_to_cpu(ssfw_head->crc), crc);
		जाओ करोne;
	पूर्ण

	चयन (ssfw_head->version) अणु
	हाल 1:
		ret = sigmadsp_fw_load_v1(sigmadsp, fw);
		अवरोध;
	हाल 2:
		ret = sigmadsp_fw_load_v2(sigmadsp, fw);
		अवरोध;
	शेष:
		dev_err(sigmadsp->dev,
			"Failed to load firmware: Invalid version %d. Supported firmware versions: 1, 2\n",
			ssfw_head->version);
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	अगर (ret)
		sigmadsp_firmware_release(sigmadsp);

करोne:
	release_firmware(fw);

	वापस ret;
पूर्ण

अटल पूर्णांक sigmadsp_init(काष्ठा sigmadsp *sigmadsp, काष्ठा device *dev,
	स्थिर काष्ठा sigmadsp_ops *ops, स्थिर अक्षर *firmware_name)
अणु
	sigmadsp->ops = ops;
	sigmadsp->dev = dev;

	INIT_LIST_HEAD(&sigmadsp->ctrl_list);
	INIT_LIST_HEAD(&sigmadsp->data_list);
	mutex_init(&sigmadsp->lock);

	वापस sigmadsp_firmware_load(sigmadsp, firmware_name);
पूर्ण

/**
 * devm_sigmadsp_init() - Initialize SigmaDSP instance
 * @dev: The parent device
 * @ops: The sigmadsp_ops to use क्रम this instance
 * @firmware_name: Name of the firmware file to load
 *
 * Allocates a SigmaDSP instance and loads the specअगरied firmware file.
 *
 * Returns a poपूर्णांकer to a काष्ठा sigmadsp on success, or a PTR_ERR() on error.
 */
काष्ठा sigmadsp *devm_sigmadsp_init(काष्ठा device *dev,
	स्थिर काष्ठा sigmadsp_ops *ops, स्थिर अक्षर *firmware_name)
अणु
	काष्ठा sigmadsp *sigmadsp;
	पूर्णांक ret;

	sigmadsp = devres_alloc(devm_sigmadsp_release, माप(*sigmadsp),
		GFP_KERNEL);
	अगर (!sigmadsp)
		वापस ERR_PTR(-ENOMEM);

	ret = sigmadsp_init(sigmadsp, dev, ops, firmware_name);
	अगर (ret) अणु
		devres_मुक्त(sigmadsp);
		वापस ERR_PTR(ret);
	पूर्ण

	devres_add(dev, sigmadsp);

	वापस sigmadsp;
पूर्ण
EXPORT_SYMBOL_GPL(devm_sigmadsp_init);

अटल पूर्णांक sigmadsp_rate_to_index(काष्ठा sigmadsp *sigmadsp, अचिन्हित पूर्णांक rate)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < sigmadsp->rate_स्थिरraपूर्णांकs.count; i++) अणु
		अगर (sigmadsp->rate_स्थिरraपूर्णांकs.list[i] == rate)
			वापस i;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल अचिन्हित पूर्णांक sigmadsp_get_samplerate_mask(काष्ठा sigmadsp *sigmadsp,
	अचिन्हित पूर्णांक samplerate)
अणु
	पूर्णांक samplerate_index;

	अगर (samplerate == 0)
		वापस 0;

	अगर (sigmadsp->rate_स्थिरraपूर्णांकs.count) अणु
		samplerate_index = sigmadsp_rate_to_index(sigmadsp, samplerate);
		अगर (samplerate_index < 0)
			वापस 0;

		वापस BIT(samplerate_index);
	पूर्ण अन्यथा अणु
		वापस ~0;
	पूर्ण
पूर्ण

अटल bool sigmadsp_samplerate_valid(अचिन्हित पूर्णांक supported,
	अचिन्हित पूर्णांक requested)
अणु
	/* All samplerates are supported */
	अगर (!supported)
		वापस true;

	वापस supported & requested;
पूर्ण

अटल पूर्णांक sigmadsp_alloc_control(काष्ठा sigmadsp *sigmadsp,
	काष्ठा sigmadsp_control *ctrl, अचिन्हित पूर्णांक samplerate_mask)
अणु
	काष्ठा snd_kcontrol_new ढाँचा;
	काष्ठा snd_kcontrol *kcontrol;

	स_रखो(&ढाँचा, 0, माप(ढाँचा));
	ढाँचा.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER;
	ढाँचा.name = ctrl->name;
	ढाँचा.info = sigmadsp_ctrl_info;
	ढाँचा.get = sigmadsp_ctrl_get;
	ढाँचा.put = sigmadsp_ctrl_put;
	ढाँचा.निजी_value = (अचिन्हित दीर्घ)ctrl;
	ढाँचा.access = SNDRV_CTL_ELEM_ACCESS_READWRITE;
	अगर (!sigmadsp_samplerate_valid(ctrl->samplerates, samplerate_mask))
		ढाँचा.access |= SNDRV_CTL_ELEM_ACCESS_INACTIVE;

	kcontrol = snd_ctl_new1(&ढाँचा, sigmadsp);
	अगर (!kcontrol)
		वापस -ENOMEM;

	kcontrol->निजी_मुक्त = sigmadsp_control_मुक्त;
	ctrl->kcontrol = kcontrol;

	वापस snd_ctl_add(sigmadsp->component->card->snd_card, kcontrol);
पूर्ण

अटल व्योम sigmadsp_activate_ctrl(काष्ठा sigmadsp *sigmadsp,
	काष्ठा sigmadsp_control *ctrl, अचिन्हित पूर्णांक samplerate_mask)
अणु
	काष्ठा snd_card *card = sigmadsp->component->card->snd_card;
	काष्ठा snd_kcontrol_अस्थिर *vd;
	काष्ठा snd_ctl_elem_id id;
	bool active;
	bool changed = false;

	active = sigmadsp_samplerate_valid(ctrl->samplerates, samplerate_mask);

	करोwn_ग_लिखो(&card->controls_rwsem);
	अगर (!ctrl->kcontrol) अणु
		up_ग_लिखो(&card->controls_rwsem);
		वापस;
	पूर्ण

	id = ctrl->kcontrol->id;
	vd = &ctrl->kcontrol->vd[0];
	अगर (active == (bool)(vd->access & SNDRV_CTL_ELEM_ACCESS_INACTIVE)) अणु
		vd->access ^= SNDRV_CTL_ELEM_ACCESS_INACTIVE;
		changed = true;
	पूर्ण
	up_ग_लिखो(&card->controls_rwsem);

	अगर (active && changed) अणु
		mutex_lock(&sigmadsp->lock);
		अगर (ctrl->cached)
			sigmadsp_ctrl_ग_लिखो(sigmadsp, ctrl, ctrl->cache);
		mutex_unlock(&sigmadsp->lock);
	पूर्ण

	अगर (changed)
		snd_ctl_notअगरy(card, SNDRV_CTL_EVENT_MASK_INFO, &id);
पूर्ण

/**
 * sigmadsp_attach() - Attach a sigmadsp instance to a ASoC component
 * @sigmadsp: The sigmadsp instance to attach
 * @component: The component to attach to
 *
 * Typically called in the components probe callback.
 *
 * Note, once this function has been called the firmware must not be released
 * until after the ALSA snd_card that the component beदीर्घs to has been
 * disconnected, even अगर sigmadsp_attach() वापसs an error.
 */
पूर्णांक sigmadsp_attach(काष्ठा sigmadsp *sigmadsp,
	काष्ठा snd_soc_component *component)
अणु
	काष्ठा sigmadsp_control *ctrl;
	अचिन्हित पूर्णांक samplerate_mask;
	पूर्णांक ret;

	sigmadsp->component = component;

	samplerate_mask = sigmadsp_get_samplerate_mask(sigmadsp,
		sigmadsp->current_samplerate);

	list_क्रम_each_entry(ctrl, &sigmadsp->ctrl_list, head) अणु
		ret = sigmadsp_alloc_control(sigmadsp, ctrl, samplerate_mask);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(sigmadsp_attach);

/**
 * sigmadsp_setup() - Setup the DSP क्रम the specअगरied samplerate
 * @sigmadsp: The sigmadsp instance to configure
 * @samplerate: The samplerate the DSP should be configured क्रम
 *
 * Loads the appropriate firmware program and parameter memory (अगर not alपढ़ोy
 * loaded) and enables the controls क्रम the specअगरied samplerate. Any control
 * parameter changes that have been made previously will be restored.
 *
 * Returns 0 on success, a negative error code otherwise.
 */
पूर्णांक sigmadsp_setup(काष्ठा sigmadsp *sigmadsp, अचिन्हित पूर्णांक samplerate)
अणु
	काष्ठा sigmadsp_control *ctrl;
	अचिन्हित पूर्णांक samplerate_mask;
	काष्ठा sigmadsp_data *data;
	पूर्णांक ret;

	अगर (sigmadsp->current_samplerate == samplerate)
		वापस 0;

	samplerate_mask = sigmadsp_get_samplerate_mask(sigmadsp, samplerate);
	अगर (samplerate_mask == 0)
		वापस -EINVAL;

	list_क्रम_each_entry(data, &sigmadsp->data_list, head) अणु
		अगर (!sigmadsp_samplerate_valid(data->samplerates,
		    samplerate_mask))
			जारी;
		ret = sigmadsp_ग_लिखो(sigmadsp, data->addr, data->data,
			data->length);
		अगर (ret)
			जाओ err;
	पूर्ण

	list_क्रम_each_entry(ctrl, &sigmadsp->ctrl_list, head)
		sigmadsp_activate_ctrl(sigmadsp, ctrl, samplerate_mask);

	sigmadsp->current_samplerate = samplerate;

	वापस 0;
err:
	sigmadsp_reset(sigmadsp);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(sigmadsp_setup);

/**
 * sigmadsp_reset() - Notअगरy the sigmadsp instance that the DSP has been reset
 * @sigmadsp: The sigmadsp instance to reset
 *
 * Should be called whenever the DSP has been reset and parameter and program
 * memory need to be re-loaded.
 */
व्योम sigmadsp_reset(काष्ठा sigmadsp *sigmadsp)
अणु
	काष्ठा sigmadsp_control *ctrl;

	list_क्रम_each_entry(ctrl, &sigmadsp->ctrl_list, head)
		sigmadsp_activate_ctrl(sigmadsp, ctrl, false);

	sigmadsp->current_samplerate = 0;
पूर्ण
EXPORT_SYMBOL_GPL(sigmadsp_reset);

/**
 * sigmadsp_restrict_params() - Applies DSP firmware specअगरic स्थिरraपूर्णांकs
 * @sigmadsp: The sigmadsp instance
 * @substream: The substream to restrict
 *
 * Applies samplerate स्थिरraपूर्णांकs that may be required by the firmware Should
 * typically be called from the CODEC/component drivers startup callback.
 *
 * Returns 0 on success, a negative error code otherwise.
 */
पूर्णांक sigmadsp_restrict_params(काष्ठा sigmadsp *sigmadsp,
	काष्ठा snd_pcm_substream *substream)
अणु
	अगर (sigmadsp->rate_स्थिरraपूर्णांकs.count == 0)
		वापस 0;

	वापस snd_pcm_hw_स्थिरraपूर्णांक_list(substream->runसमय, 0,
		SNDRV_PCM_HW_PARAM_RATE, &sigmadsp->rate_स्थिरraपूर्णांकs);
पूर्ण
EXPORT_SYMBOL_GPL(sigmadsp_restrict_params);

MODULE_LICENSE("GPL");
