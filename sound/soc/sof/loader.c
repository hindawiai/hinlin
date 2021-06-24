<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-3-Clause)
//
// This file is provided under a dual BSD/GPLv2 license.  When using or
// redistributing this file, you may करो so under either license.
//
// Copyright(c) 2018 Intel Corporation. All rights reserved.
//
// Author: Liam Girdwood <liam.r.girdwood@linux.पूर्णांकel.com>
//
// Generic firmware loader.
//

#समावेश <linux/firmware.h>
#समावेश <sound/sof.h>
#समावेश <sound/sof/ext_manअगरest.h>
#समावेश "ops.h"

अटल पूर्णांक get_ext_winकरोws(काष्ठा snd_sof_dev *sdev,
			   स्थिर काष्ठा sof_ipc_ext_data_hdr *ext_hdr)
अणु
	स्थिर काष्ठा sof_ipc_winकरोw *w =
		container_of(ext_hdr, काष्ठा sof_ipc_winकरोw, ext_hdr);

	अगर (w->num_winकरोws == 0 || w->num_winकरोws > SOF_IPC_MAX_ELEMS)
		वापस -EINVAL;

	अगर (sdev->info_winकरोw) अणु
		अगर (स_भेद(sdev->info_winकरोw, w, ext_hdr->hdr.size)) अणु
			dev_err(sdev->dev, "error: mismatch between window descriptor from extended manifest and mailbox");
			वापस -EINVAL;
		पूर्ण
		वापस 0;
	पूर्ण

	/* keep a local copy of the data */
	sdev->info_winकरोw = devm_kmemdup(sdev->dev, w, ext_hdr->hdr.size,
					 GFP_KERNEL);
	अगर (!sdev->info_winकरोw)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल पूर्णांक get_cc_info(काष्ठा snd_sof_dev *sdev,
		       स्थिर काष्ठा sof_ipc_ext_data_hdr *ext_hdr)
अणु
	पूर्णांक ret;

	स्थिर काष्ठा sof_ipc_cc_version *cc =
		container_of(ext_hdr, काष्ठा sof_ipc_cc_version, ext_hdr);

	अगर (sdev->cc_version) अणु
		अगर (स_भेद(sdev->cc_version, cc, cc->ext_hdr.hdr.size)) अणु
			dev_err(sdev->dev, "error: receive diverged cc_version descriptions");
			वापस -EINVAL;
		पूर्ण
		वापस 0;
	पूर्ण

	dev_dbg(sdev->dev, "Firmware info: used compiler %s %d:%d:%d%s used optimization flags %s\n",
		cc->name, cc->major, cc->minor, cc->micro, cc->desc,
		cc->optim);

	/* create पढ़ो-only cc_version debugfs to store compiler version info */
	/* use local copy of the cc_version to prevent data corruption */
	अगर (sdev->first_boot) अणु
		sdev->cc_version = devm_kदो_स्मृति(sdev->dev, cc->ext_hdr.hdr.size,
						GFP_KERNEL);

		अगर (!sdev->cc_version)
			वापस -ENOMEM;

		स_नकल(sdev->cc_version, cc, cc->ext_hdr.hdr.size);
		ret = snd_sof_debugfs_buf_item(sdev, sdev->cc_version,
					       cc->ext_hdr.hdr.size,
					       "cc_version", 0444);

		/* errors are only due to memory allocation, not debugfs */
		अगर (ret < 0) अणु
			dev_err(sdev->dev, "error: snd_sof_debugfs_buf_item failed\n");
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/* parse the extended FW boot data काष्ठाures from FW boot message */
पूर्णांक snd_sof_fw_parse_ext_data(काष्ठा snd_sof_dev *sdev, u32 bar, u32 offset)
अणु
	काष्ठा sof_ipc_ext_data_hdr *ext_hdr;
	व्योम *ext_data;
	पूर्णांक ret = 0;

	ext_data = kzalloc(PAGE_SIZE, GFP_KERNEL);
	अगर (!ext_data)
		वापस -ENOMEM;

	/* get first header */
	snd_sof_dsp_block_पढ़ो(sdev, bar, offset, ext_data,
			       माप(*ext_hdr));
	ext_hdr = ext_data;

	जबतक (ext_hdr->hdr.cmd == SOF_IPC_FW_READY) अणु
		/* पढ़ो in ext काष्ठाure */
		snd_sof_dsp_block_पढ़ो(sdev, bar, offset + माप(*ext_hdr),
				   (व्योम *)((u8 *)ext_data + माप(*ext_hdr)),
				   ext_hdr->hdr.size - माप(*ext_hdr));

		dev_dbg(sdev->dev, "found ext header type %d size 0x%x\n",
			ext_hdr->type, ext_hdr->hdr.size);

		/* process काष्ठाure data */
		चयन (ext_hdr->type) अणु
		हाल SOF_IPC_EXT_WINDOW:
			ret = get_ext_winकरोws(sdev, ext_hdr);
			अवरोध;
		हाल SOF_IPC_EXT_CC_INFO:
			ret = get_cc_info(sdev, ext_hdr);
			अवरोध;
		हाल SOF_IPC_EXT_UNUSED:
		हाल SOF_IPC_EXT_PROBE_INFO:
		हाल SOF_IPC_EXT_USER_ABI_INFO:
			/* They are supported but we करोn't करो anything here */
			अवरोध;
		शेष:
			dev_info(sdev->dev, "unknown ext header type %d size 0x%x\n",
				 ext_hdr->type, ext_hdr->hdr.size);
			ret = 0;
			अवरोध;
		पूर्ण

		अगर (ret < 0) अणु
			dev_err(sdev->dev, "error: failed to parse ext data type %d\n",
				ext_hdr->type);
			अवरोध;
		पूर्ण

		/* move to next header */
		offset += ext_hdr->hdr.size;
		snd_sof_dsp_block_पढ़ो(sdev, bar, offset, ext_data,
				       माप(*ext_hdr));
		ext_hdr = ext_data;
	पूर्ण

	kमुक्त(ext_data);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(snd_sof_fw_parse_ext_data);

अटल पूर्णांक ext_man_get_fw_version(काष्ठा snd_sof_dev *sdev,
				  स्थिर काष्ठा sof_ext_man_elem_header *hdr)
अणु
	स्थिर काष्ठा sof_ext_man_fw_version *v =
		container_of(hdr, काष्ठा sof_ext_man_fw_version, hdr);

	स_नकल(&sdev->fw_पढ़ोy.version, &v->version, माप(v->version));
	sdev->fw_पढ़ोy.flags = v->flags;

	/* log ABI versions and check FW compatibility */
	वापस snd_sof_ipc_valid(sdev);
पूर्ण

अटल पूर्णांक ext_man_get_winकरोws(काष्ठा snd_sof_dev *sdev,
			       स्थिर काष्ठा sof_ext_man_elem_header *hdr)
अणु
	स्थिर काष्ठा sof_ext_man_winकरोw *w;

	w = container_of(hdr, काष्ठा sof_ext_man_winकरोw, hdr);

	वापस get_ext_winकरोws(sdev, &w->ipc_winकरोw.ext_hdr);
पूर्ण

अटल पूर्णांक ext_man_get_cc_info(काष्ठा snd_sof_dev *sdev,
			       स्थिर काष्ठा sof_ext_man_elem_header *hdr)
अणु
	स्थिर काष्ठा sof_ext_man_cc_version *cc;

	cc = container_of(hdr, काष्ठा sof_ext_man_cc_version, hdr);

	वापस get_cc_info(sdev, &cc->cc_version.ext_hdr);
पूर्ण

अटल पूर्णांक ext_man_get_dbg_abi_info(काष्ठा snd_sof_dev *sdev,
				    स्थिर काष्ठा sof_ext_man_elem_header *hdr)
अणु
	स्थिर काष्ठा ext_man_dbg_abi *dbg_abi =
		container_of(hdr, काष्ठा ext_man_dbg_abi, hdr);

	अगर (sdev->first_boot)
		dev_dbg(sdev->dev,
			"Firmware: DBG_ABI %d:%d:%d\n",
			SOF_ABI_VERSION_MAJOR(dbg_abi->dbg_abi.abi_dbg_version),
			SOF_ABI_VERSION_MINOR(dbg_abi->dbg_abi.abi_dbg_version),
			SOF_ABI_VERSION_PATCH(dbg_abi->dbg_abi.abi_dbg_version));

	वापस 0;
पूर्ण

अटल पूर्णांक ext_man_get_config_data(काष्ठा snd_sof_dev *sdev,
				   स्थिर काष्ठा sof_ext_man_elem_header *hdr)
अणु
	स्थिर काष्ठा sof_ext_man_config_data *config =
		container_of(hdr, काष्ठा sof_ext_man_config_data, hdr);
	स्थिर काष्ठा sof_config_elem *elem;
	पूर्णांक elems_counter;
	पूर्णांक elems_size;
	पूर्णांक ret = 0;
	पूर्णांक i;

	/* calculate elements counter */
	elems_size = config->hdr.size - माप(काष्ठा sof_ext_man_elem_header);
	elems_counter = elems_size / माप(काष्ठा sof_config_elem);

	dev_dbg(sdev->dev, "%s can hold up to %d config elements\n",
		__func__, elems_counter);

	क्रम (i = 0; i < elems_counter; ++i) अणु
		elem = &config->elems[i];
		dev_dbg(sdev->dev, "%s get index %d token %d val %d\n",
			__func__, i, elem->token, elem->value);
		चयन (elem->token) अणु
		हाल SOF_EXT_MAN_CONFIG_EMPTY:
			/* unused memory space is zero filled - mapped to EMPTY elements */
			अवरोध;
		हाल SOF_EXT_MAN_CONFIG_IPC_MSG_SIZE:
			/* TODO: use ipc msg size from config data */
			अवरोध;
		हाल SOF_EXT_MAN_CONFIG_MEMORY_USAGE_SCAN:
			अगर (sdev->first_boot && elem->value)
				ret = snd_sof_dbg_memory_info_init(sdev);
			अवरोध;
		शेष:
			dev_info(sdev->dev, "Unknown firmware configuration token %d value %d",
				 elem->token, elem->value);
			अवरोध;
		पूर्ण
		अगर (ret < 0) अणु
			dev_err(sdev->dev, "error: processing sof_ext_man_config_data failed for token %d value 0x%x, %d\n",
				elem->token, elem->value, ret);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल sमाप_प्रकार snd_sof_ext_man_size(स्थिर काष्ठा firmware *fw)
अणु
	स्थिर काष्ठा sof_ext_man_header *head;

	head = (काष्ठा sof_ext_man_header *)fw->data;

	/*
	 * निश्चित fw size is big enough to contain extended manअगरest header,
	 * it prevents from पढ़ोing unallocated memory from `head` in following
	 * step.
	 */
	अगर (fw->size < माप(*head))
		वापस -EINVAL;

	/*
	 * When fw poपूर्णांकs to extended manअगरest,
	 * then first u32 must be equal SOF_EXT_MAN_MAGIC_NUMBER.
	 */
	अगर (head->magic == SOF_EXT_MAN_MAGIC_NUMBER)
		वापस head->full_size;

	/* otherwise given fw करोn't have an extended manअगरest */
	वापस 0;
पूर्ण

/* parse extended FW manअगरest data काष्ठाures */
अटल पूर्णांक snd_sof_fw_ext_man_parse(काष्ठा snd_sof_dev *sdev,
				    स्थिर काष्ठा firmware *fw)
अणु
	स्थिर काष्ठा sof_ext_man_elem_header *elem_hdr;
	स्थिर काष्ठा sof_ext_man_header *head;
	sमाप_प्रकार ext_man_size;
	sमाप_प्रकार reमुख्यing;
	uपूर्णांकptr_t iptr;
	पूर्णांक ret = 0;

	head = (काष्ठा sof_ext_man_header *)fw->data;
	reमुख्यing = head->full_size - head->header_size;
	ext_man_size = snd_sof_ext_man_size(fw);

	/* Assert firmware starts with extended manअगरest */
	अगर (ext_man_size <= 0)
		वापस ext_man_size;

	/* incompatible version */
	अगर (SOF_EXT_MAN_VERSION_INCOMPATIBLE(SOF_EXT_MAN_VERSION,
					     head->header_version)) अणु
		dev_err(sdev->dev, "error: extended manifest version 0x%X differ from used 0x%X\n",
			head->header_version, SOF_EXT_MAN_VERSION);
		वापस -EINVAL;
	पूर्ण

	/* get first extended manअगरest element header */
	iptr = (uपूर्णांकptr_t)fw->data + head->header_size;

	जबतक (reमुख्यing > माप(*elem_hdr)) अणु
		elem_hdr = (काष्ठा sof_ext_man_elem_header *)iptr;

		dev_dbg(sdev->dev, "found sof_ext_man header type %d size 0x%X\n",
			elem_hdr->type, elem_hdr->size);

		अगर (elem_hdr->size < माप(*elem_hdr) ||
		    elem_hdr->size > reमुख्यing) अणु
			dev_err(sdev->dev, "error: invalid sof_ext_man header size, type %d size 0x%X\n",
				elem_hdr->type, elem_hdr->size);
			वापस -EINVAL;
		पूर्ण

		/* process काष्ठाure data */
		चयन (elem_hdr->type) अणु
		हाल SOF_EXT_MAN_ELEM_FW_VERSION:
			ret = ext_man_get_fw_version(sdev, elem_hdr);
			अवरोध;
		हाल SOF_EXT_MAN_ELEM_WINDOW:
			ret = ext_man_get_winकरोws(sdev, elem_hdr);
			अवरोध;
		हाल SOF_EXT_MAN_ELEM_CC_VERSION:
			ret = ext_man_get_cc_info(sdev, elem_hdr);
			अवरोध;
		हाल SOF_EXT_MAN_ELEM_DBG_ABI:
			ret = ext_man_get_dbg_abi_info(sdev, elem_hdr);
			अवरोध;
		हाल SOF_EXT_MAN_ELEM_CONFIG_DATA:
			ret = ext_man_get_config_data(sdev, elem_hdr);
			अवरोध;
		हाल SOF_EXT_MAN_ELEM_PLATFORM_CONFIG_DATA:
			ret = snd_sof_dsp_parse_platक्रमm_ext_manअगरest(sdev, elem_hdr);
			अवरोध;
		शेष:
			dev_info(sdev->dev, "unknown sof_ext_man header type %d size 0x%X\n",
				 elem_hdr->type, elem_hdr->size);
			अवरोध;
		पूर्ण

		अगर (ret < 0) अणु
			dev_err(sdev->dev, "error: failed to parse sof_ext_man header type %d size 0x%X\n",
				elem_hdr->type, elem_hdr->size);
			वापस ret;
		पूर्ण

		reमुख्यing -= elem_hdr->size;
		iptr += elem_hdr->size;
	पूर्ण

	अगर (reमुख्यing) अणु
		dev_err(sdev->dev, "error: sof_ext_man header is inconsistent\n");
		वापस -EINVAL;
	पूर्ण

	वापस ext_man_size;
पूर्ण

/*
 * IPC Firmware पढ़ोy.
 */
अटल व्योम sof_get_winकरोws(काष्ठा snd_sof_dev *sdev)
अणु
	काष्ठा sof_ipc_winकरोw_elem *elem;
	u32 outbox_offset = 0;
	u32 stream_offset = 0;
	u32 inbox_offset = 0;
	u32 outbox_size = 0;
	u32 stream_size = 0;
	u32 inbox_size = 0;
	u32 debug_size = 0;
	u32 debug_offset = 0;
	पूर्णांक winकरोw_offset;
	पूर्णांक bar;
	पूर्णांक i;

	अगर (!sdev->info_winकरोw) अणु
		dev_err(sdev->dev, "error: have no window info\n");
		वापस;
	पूर्ण

	bar = snd_sof_dsp_get_bar_index(sdev, SOF_FW_BLK_TYPE_SRAM);
	अगर (bar < 0) अणु
		dev_err(sdev->dev, "error: have no bar mapping\n");
		वापस;
	पूर्ण

	क्रम (i = 0; i < sdev->info_winकरोw->num_winकरोws; i++) अणु
		elem = &sdev->info_winकरोw->winकरोw[i];

		winकरोw_offset = snd_sof_dsp_get_winकरोw_offset(sdev, elem->id);
		अगर (winकरोw_offset < 0) अणु
			dev_warn(sdev->dev, "warn: no offset for window %d\n",
				 elem->id);
			जारी;
		पूर्ण

		चयन (elem->type) अणु
		हाल SOF_IPC_REGION_UPBOX:
			inbox_offset = winकरोw_offset + elem->offset;
			inbox_size = elem->size;
			snd_sof_debugfs_io_item(sdev,
						sdev->bar[bar] +
						inbox_offset,
						elem->size, "inbox",
						SOF_DEBUGFS_ACCESS_D0_ONLY);
			अवरोध;
		हाल SOF_IPC_REGION_DOWNBOX:
			outbox_offset = winकरोw_offset + elem->offset;
			outbox_size = elem->size;
			snd_sof_debugfs_io_item(sdev,
						sdev->bar[bar] +
						outbox_offset,
						elem->size, "outbox",
						SOF_DEBUGFS_ACCESS_D0_ONLY);
			अवरोध;
		हाल SOF_IPC_REGION_TRACE:
			snd_sof_debugfs_io_item(sdev,
						sdev->bar[bar] +
						winकरोw_offset +
						elem->offset,
						elem->size, "etrace",
						SOF_DEBUGFS_ACCESS_D0_ONLY);
			अवरोध;
		हाल SOF_IPC_REGION_DEBUG:
			debug_offset = winकरोw_offset + elem->offset;
			debug_size = elem->size;
			snd_sof_debugfs_io_item(sdev,
						sdev->bar[bar] +
						winकरोw_offset +
						elem->offset,
						elem->size, "debug",
						SOF_DEBUGFS_ACCESS_D0_ONLY);
			अवरोध;
		हाल SOF_IPC_REGION_STREAM:
			stream_offset = winकरोw_offset + elem->offset;
			stream_size = elem->size;
			snd_sof_debugfs_io_item(sdev,
						sdev->bar[bar] +
						stream_offset,
						elem->size, "stream",
						SOF_DEBUGFS_ACCESS_D0_ONLY);
			अवरोध;
		हाल SOF_IPC_REGION_REGS:
			snd_sof_debugfs_io_item(sdev,
						sdev->bar[bar] +
						winकरोw_offset +
						elem->offset,
						elem->size, "regs",
						SOF_DEBUGFS_ACCESS_D0_ONLY);
			अवरोध;
		हाल SOF_IPC_REGION_EXCEPTION:
			sdev->dsp_oops_offset = winकरोw_offset + elem->offset;
			snd_sof_debugfs_io_item(sdev,
						sdev->bar[bar] +
						winकरोw_offset +
						elem->offset,
						elem->size, "exception",
						SOF_DEBUGFS_ACCESS_D0_ONLY);
			अवरोध;
		शेष:
			dev_err(sdev->dev, "error: get illegal window info\n");
			वापस;
		पूर्ण
	पूर्ण

	अगर (outbox_size == 0 || inbox_size == 0) अणु
		dev_err(sdev->dev, "error: get illegal mailbox window\n");
		वापस;
	पूर्ण

	snd_sof_dsp_mailbox_init(sdev, inbox_offset, inbox_size,
				 outbox_offset, outbox_size);
	sdev->stream_box.offset = stream_offset;
	sdev->stream_box.size = stream_size;

	sdev->debug_box.offset = debug_offset;
	sdev->debug_box.size = debug_size;

	dev_dbg(sdev->dev, " mailbox upstream 0x%x - size 0x%x\n",
		inbox_offset, inbox_size);
	dev_dbg(sdev->dev, " mailbox downstream 0x%x - size 0x%x\n",
		outbox_offset, outbox_size);
	dev_dbg(sdev->dev, " stream region 0x%x - size 0x%x\n",
		stream_offset, stream_size);
	dev_dbg(sdev->dev, " debug region 0x%x - size 0x%x\n",
		debug_offset, debug_size);
पूर्ण

/* check क्रम ABI compatibility and create memory winकरोws on first boot */
पूर्णांक sof_fw_पढ़ोy(काष्ठा snd_sof_dev *sdev, u32 msg_id)
अणु
	काष्ठा sof_ipc_fw_पढ़ोy *fw_पढ़ोy = &sdev->fw_पढ़ोy;
	पूर्णांक offset;
	पूर्णांक bar;
	पूर्णांक ret;

	/* mailbox must be on 4k boundary */
	offset = snd_sof_dsp_get_mailbox_offset(sdev);
	अगर (offset < 0) अणु
		dev_err(sdev->dev, "error: have no mailbox offset\n");
		वापस offset;
	पूर्ण

	bar = snd_sof_dsp_get_bar_index(sdev, SOF_FW_BLK_TYPE_SRAM);
	अगर (bar < 0) अणु
		dev_err(sdev->dev, "error: have no bar mapping\n");
		वापस -EINVAL;
	पूर्ण

	dev_dbg(sdev->dev, "ipc: DSP is ready 0x%8.8x offset 0x%x\n",
		msg_id, offset);

	/* no need to re-check version/ABI क्रम subsequent boots */
	अगर (!sdev->first_boot)
		वापस 0;

	/* copy data from the DSP FW पढ़ोy offset */
	sof_block_पढ़ो(sdev, bar, offset, fw_पढ़ोy, माप(*fw_पढ़ोy));

	/* make sure ABI version is compatible */
	ret = snd_sof_ipc_valid(sdev);
	अगर (ret < 0)
		वापस ret;

	/* now check क्रम extended data */
	snd_sof_fw_parse_ext_data(sdev, bar, offset +
				  माप(काष्ठा sof_ipc_fw_पढ़ोy));

	sof_get_winकरोws(sdev);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(sof_fw_पढ़ोy);

/* generic module parser क्रम mmaped DSPs */
पूर्णांक snd_sof_parse_module_स_नकल(काष्ठा snd_sof_dev *sdev,
				काष्ठा snd_sof_mod_hdr *module)
अणु
	काष्ठा snd_sof_blk_hdr *block;
	पूर्णांक count, bar;
	u32 offset;
	माप_प्रकार reमुख्यing;

	dev_dbg(sdev->dev, "new module size 0x%x blocks 0x%x type 0x%x\n",
		module->size, module->num_blocks, module->type);

	block = (काष्ठा snd_sof_blk_hdr *)((u8 *)module + माप(*module));

	/* module->size करोesn't include header size */
	reमुख्यing = module->size;
	क्रम (count = 0; count < module->num_blocks; count++) अणु
		/* check क्रम wrap */
		अगर (reमुख्यing < माप(*block)) अणु
			dev_err(sdev->dev, "error: not enough data remaining\n");
			वापस -EINVAL;
		पूर्ण

		/* minus header size of block */
		reमुख्यing -= माप(*block);

		अगर (block->size == 0) अणु
			dev_warn(sdev->dev,
				 "warning: block %d size zero\n", count);
			dev_warn(sdev->dev, " type 0x%x offset 0x%x\n",
				 block->type, block->offset);
			जारी;
		पूर्ण

		चयन (block->type) अणु
		हाल SOF_FW_BLK_TYPE_RSRVD0:
		हाल SOF_FW_BLK_TYPE_ROM...SOF_FW_BLK_TYPE_RSRVD14:
			जारी;	/* not handled aपंचांग */
		हाल SOF_FW_BLK_TYPE_IRAM:
		हाल SOF_FW_BLK_TYPE_DRAM:
		हाल SOF_FW_BLK_TYPE_SRAM:
			offset = block->offset;
			bar = snd_sof_dsp_get_bar_index(sdev, block->type);
			अगर (bar < 0) अणु
				dev_err(sdev->dev,
					"error: no BAR mapping for block type 0x%x\n",
					block->type);
				वापस bar;
			पूर्ण
			अवरोध;
		शेष:
			dev_err(sdev->dev, "error: bad type 0x%x for block 0x%x\n",
				block->type, count);
			वापस -EINVAL;
		पूर्ण

		dev_dbg(sdev->dev,
			"block %d type 0x%x size 0x%x ==>  offset 0x%x\n",
			count, block->type, block->size, offset);

		/* checking block->size to aव्योम unaligned access */
		अगर (block->size % माप(u32)) अणु
			dev_err(sdev->dev, "error: invalid block size 0x%x\n",
				block->size);
			वापस -EINVAL;
		पूर्ण
		snd_sof_dsp_block_ग_लिखो(sdev, bar, offset,
					block + 1, block->size);

		अगर (reमुख्यing < block->size) अणु
			dev_err(sdev->dev, "error: not enough data remaining\n");
			वापस -EINVAL;
		पूर्ण

		/* minus body size of block */
		reमुख्यing -= block->size;
		/* next block */
		block = (काष्ठा snd_sof_blk_hdr *)((u8 *)block + माप(*block)
			+ block->size);
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(snd_sof_parse_module_स_नकल);

अटल पूर्णांक check_header(काष्ठा snd_sof_dev *sdev, स्थिर काष्ठा firmware *fw,
			माप_प्रकार fw_offset)
अणु
	काष्ठा snd_sof_fw_header *header;
	माप_प्रकार fw_size = fw->size - fw_offset;

	अगर (fw->size <= fw_offset) अणु
		dev_err(sdev->dev, "error: firmware size must be greater than firmware offset\n");
		वापस -EINVAL;
	पूर्ण

	/* Read the header inक्रमmation from the data poपूर्णांकer */
	header = (काष्ठा snd_sof_fw_header *)(fw->data + fw_offset);

	/* verअगरy FW sig */
	अगर (म_भेदन(header->sig, SND_SOF_FW_SIG, SND_SOF_FW_SIG_SIZE) != 0) अणु
		dev_err(sdev->dev, "error: invalid firmware signature\n");
		वापस -EINVAL;
	पूर्ण

	/* check size is valid */
	अगर (fw_size != header->file_size + माप(*header)) अणु
		dev_err(sdev->dev, "error: invalid filesize mismatch got 0x%zx expected 0x%zx\n",
			fw_size, header->file_size + माप(*header));
		वापस -EINVAL;
	पूर्ण

	dev_dbg(sdev->dev, "header size=0x%x modules=0x%x abi=0x%x size=%zu\n",
		header->file_size, header->num_modules,
		header->abi, माप(*header));

	वापस 0;
पूर्ण

अटल पूर्णांक load_modules(काष्ठा snd_sof_dev *sdev, स्थिर काष्ठा firmware *fw,
			माप_प्रकार fw_offset)
अणु
	काष्ठा snd_sof_fw_header *header;
	काष्ठा snd_sof_mod_hdr *module;
	पूर्णांक (*load_module)(काष्ठा snd_sof_dev *sof_dev,
			   काष्ठा snd_sof_mod_hdr *hdr);
	पूर्णांक ret, count;
	माप_प्रकार reमुख्यing;

	header = (काष्ठा snd_sof_fw_header *)(fw->data + fw_offset);
	load_module = sof_ops(sdev)->load_module;
	अगर (!load_module)
		वापस -EINVAL;

	/* parse each module */
	module = (काष्ठा snd_sof_mod_hdr *)(fw->data + fw_offset +
					    माप(*header));
	reमुख्यing = fw->size - माप(*header) - fw_offset;
	/* check क्रम wrap */
	अगर (reमुख्यing > fw->size) अणु
		dev_err(sdev->dev, "error: fw size smaller than header size\n");
		वापस -EINVAL;
	पूर्ण

	क्रम (count = 0; count < header->num_modules; count++) अणु
		/* check क्रम wrap */
		अगर (reमुख्यing < माप(*module)) अणु
			dev_err(sdev->dev, "error: not enough data remaining\n");
			वापस -EINVAL;
		पूर्ण

		/* minus header size of module */
		reमुख्यing -= माप(*module);

		/* module */
		ret = load_module(sdev, module);
		अगर (ret < 0) अणु
			dev_err(sdev->dev, "error: invalid module %d\n", count);
			वापस ret;
		पूर्ण

		अगर (reमुख्यing < module->size) अणु
			dev_err(sdev->dev, "error: not enough data remaining\n");
			वापस -EINVAL;
		पूर्ण

		/* minus body size of module */
		reमुख्यing -=  module->size;
		module = (काष्ठा snd_sof_mod_hdr *)((u8 *)module
			+ माप(*module) + module->size);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक snd_sof_load_firmware_raw(काष्ठा snd_sof_dev *sdev)
अणु
	काष्ठा snd_sof_pdata *plat_data = sdev->pdata;
	स्थिर अक्षर *fw_filename;
	sमाप_प्रकार ext_man_size;
	पूर्णांक ret;

	/* Don't request firmware again अगर firmware is alपढ़ोy requested */
	अगर (plat_data->fw)
		वापस 0;

	fw_filename = kaप्र_लिखो(GFP_KERNEL, "%s/%s",
				plat_data->fw_filename_prefix,
				plat_data->fw_filename);
	अगर (!fw_filename)
		वापस -ENOMEM;

	ret = request_firmware(&plat_data->fw, fw_filename, sdev->dev);

	अगर (ret < 0) अणु
		dev_err(sdev->dev, "error: request firmware %s failed err: %d\n",
			fw_filename, ret);
		dev_err(sdev->dev,
			"you may need to download the firmware from https://github.com/thesofproject/sof-bin/\n");
		जाओ err;
	पूर्ण अन्यथा अणु
		dev_dbg(sdev->dev, "request_firmware %s successful\n",
			fw_filename);
	पूर्ण

	/* check क्रम extended manअगरest */
	ext_man_size = snd_sof_fw_ext_man_parse(sdev, plat_data->fw);
	अगर (ext_man_size > 0) अणु
		/* when no error occurred, drop extended manअगरest */
		plat_data->fw_offset = ext_man_size;
	पूर्ण अन्यथा अगर (!ext_man_size) अणु
		/* No extended manअगरest, so nothing to skip during FW load */
		dev_dbg(sdev->dev, "firmware doesn't contain extended manifest\n");
	पूर्ण अन्यथा अणु
		ret = ext_man_size;
		dev_err(sdev->dev, "error: firmware %s contains unsupported or invalid extended manifest: %d\n",
			fw_filename, ret);
	पूर्ण

err:
	kमुक्त(fw_filename);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(snd_sof_load_firmware_raw);

पूर्णांक snd_sof_load_firmware_स_नकल(काष्ठा snd_sof_dev *sdev)
अणु
	काष्ठा snd_sof_pdata *plat_data = sdev->pdata;
	पूर्णांक ret;

	ret = snd_sof_load_firmware_raw(sdev);
	अगर (ret < 0)
		वापस ret;

	/* make sure the FW header and file is valid */
	ret = check_header(sdev, plat_data->fw, plat_data->fw_offset);
	अगर (ret < 0) अणु
		dev_err(sdev->dev, "error: invalid FW header\n");
		जाओ error;
	पूर्ण

	/* prepare the DSP क्रम FW loading */
	ret = snd_sof_dsp_reset(sdev);
	अगर (ret < 0) अणु
		dev_err(sdev->dev, "error: failed to reset DSP\n");
		जाओ error;
	पूर्ण

	/* parse and load firmware modules to DSP */
	ret = load_modules(sdev, plat_data->fw, plat_data->fw_offset);
	अगर (ret < 0) अणु
		dev_err(sdev->dev, "error: invalid FW modules\n");
		जाओ error;
	पूर्ण

	वापस 0;

error:
	release_firmware(plat_data->fw);
	plat_data->fw = शून्य;
	वापस ret;

पूर्ण
EXPORT_SYMBOL(snd_sof_load_firmware_स_नकल);

पूर्णांक snd_sof_load_firmware(काष्ठा snd_sof_dev *sdev)
अणु
	dev_dbg(sdev->dev, "loading firmware\n");

	अगर (sof_ops(sdev)->load_firmware)
		वापस sof_ops(sdev)->load_firmware(sdev);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(snd_sof_load_firmware);

पूर्णांक snd_sof_run_firmware(काष्ठा snd_sof_dev *sdev)
अणु
	पूर्णांक ret;

	init_रुकोqueue_head(&sdev->boot_रुको);

	/* create पढ़ो-only fw_version debugfs to store boot version info */
	अगर (sdev->first_boot) अणु
		ret = snd_sof_debugfs_buf_item(sdev, &sdev->fw_version,
					       माप(sdev->fw_version),
					       "fw_version", 0444);
		/* errors are only due to memory allocation, not debugfs */
		अगर (ret < 0) अणु
			dev_err(sdev->dev, "error: snd_sof_debugfs_buf_item failed\n");
			वापस ret;
		पूर्ण
	पूर्ण

	/* perक्रमm pre fw run operations */
	ret = snd_sof_dsp_pre_fw_run(sdev);
	अगर (ret < 0) अणु
		dev_err(sdev->dev, "error: failed pre fw run op\n");
		वापस ret;
	पूर्ण

	dev_dbg(sdev->dev, "booting DSP firmware\n");

	/* boot the firmware on the DSP */
	ret = snd_sof_dsp_run(sdev);
	अगर (ret < 0) अणु
		dev_err(sdev->dev, "error: failed to reset DSP\n");
		वापस ret;
	पूर्ण

	/*
	 * now रुको क्रम the DSP to boot. There are 3 possible outcomes:
	 * 1. Boot रुको बार out indicating FW boot failure.
	 * 2. FW boots successfully and fw_पढ़ोy op succeeds.
	 * 3. FW boots but fw_पढ़ोy op fails.
	 */
	ret = रुको_event_समयout(sdev->boot_रुको,
				 sdev->fw_state > SOF_FW_BOOT_IN_PROGRESS,
				 msecs_to_jअगरfies(sdev->boot_समयout));
	अगर (ret == 0) अणु
		dev_err(sdev->dev, "error: firmware boot failure\n");
		snd_sof_dsp_dbg_dump(sdev, SOF_DBG_DUMP_REGS | SOF_DBG_DUMP_MBOX |
			SOF_DBG_DUMP_TEXT | SOF_DBG_DUMP_PCI | SOF_DBG_DUMP_FORCE_ERR_LEVEL);
		sdev->fw_state = SOF_FW_BOOT_FAILED;
		वापस -EIO;
	पूर्ण

	अगर (sdev->fw_state == SOF_FW_BOOT_COMPLETE)
		dev_dbg(sdev->dev, "firmware boot complete\n");
	अन्यथा
		वापस -EIO; /* FW boots but fw_पढ़ोy op failed */

	/* perक्रमm post fw run operations */
	ret = snd_sof_dsp_post_fw_run(sdev);
	अगर (ret < 0) अणु
		dev_err(sdev->dev, "error: failed post fw run op\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(snd_sof_run_firmware);

व्योम snd_sof_fw_unload(काष्ठा snd_sof_dev *sdev)
अणु
	/* TODO: support module unloading at runसमय */
पूर्ण
EXPORT_SYMBOL(snd_sof_fw_unload);
