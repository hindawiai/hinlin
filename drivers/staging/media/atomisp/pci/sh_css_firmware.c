<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Support क्रम Intel Camera Imaging ISP subप्रणाली.
 * Copyright (c) 2015, Intel Corporation.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License क्रम
 * more details.
 */

#समावेश <linux/माला.स> /* क्रम स_नकल() */
#समावेश <linux/slab.h>
#समावेश <linux/vदो_स्मृति.h>

#समावेश "hmm.h"

#समावेश <math_support.h>
#समावेश "platform_support.h"
#समावेश "sh_css_firmware.h"

#समावेश "sh_css_defs.h"
#समावेश "ia_css_debug.h"
#समावेश "sh_css_internal.h"
#समावेश "ia_css_isp_param.h"

#समावेश "assert_support.h"

#समावेश "isp.h"				/* PMEM_WIDTH_LOG2 */

#समावेश "ia_css_isp_params.h"
#समावेश "ia_css_isp_configs.h"
#समावेश "ia_css_isp_states.h"

#घोषणा _STR(x) #x
#घोषणा STR(x) _STR(x)

काष्ठा firmware_header अणु
	काष्ठा sh_css_fw_bi_file_h file_header;
	काष्ठा ia_css_fw_info      binary_header;
पूर्ण;

काष्ठा fw_param अणु
	स्थिर अक्षर *name;
	स्थिर व्योम *buffer;
पूर्ण;

अटल काष्ठा firmware_header *firmware_header;

/*
 * The string STR is a place holder
 * which will be replaced with the actual RELEASE_VERSION
 * during package generation. Please करो not modअगरy
 */
अटल स्थिर अक्षर *isp2400_release_version = STR(irci_stable_candrpv_0415_20150521_0458);
अटल स्थिर अक्षर *isp2401_release_version = STR(irci_ecr - master_20150911_0724);

#घोषणा MAX_FW_REL_VER_NAME	300
अटल अक्षर FW_rel_ver_name[MAX_FW_REL_VER_NAME] = "---";

काष्ठा ia_css_fw_info	  sh_css_sp_fw;
काष्ठा ia_css_blob_descr *sh_css_blob_info; /* Only ISP blob info (no SP) */
अचिन्हित पूर्णांक sh_css_num_binaries; /* This includes 1 SP binary */

अटल काष्ठा fw_param *fw_minibuffer;

अक्षर *sh_css_get_fw_version(व्योम)
अणु
	वापस FW_rel_ver_name;
पूर्ण

/*
 * Split the loaded firmware पूर्णांकo blobs
 */

/* Setup sp/sp1 binary */
अटल पूर्णांक
setup_binary(काष्ठा ia_css_fw_info *fw, स्थिर अक्षर *fw_data,
	     काष्ठा ia_css_fw_info *sh_css_fw, अचिन्हित पूर्णांक binary_id)
अणु
	स्थिर अक्षर *blob_data;

	अगर ((!fw) || (!fw_data))
		वापस -EINVAL;

	blob_data = fw_data + fw->blob.offset;

	*sh_css_fw = *fw;

	sh_css_fw->blob.code = vदो_स्मृति(fw->blob.size);
	अगर (!sh_css_fw->blob.code)
		वापस -ENOMEM;

	स_नकल((व्योम *)sh_css_fw->blob.code, blob_data, fw->blob.size);
	sh_css_fw->blob.data = (अक्षर *)sh_css_fw->blob.code + fw->blob.data_source;
	fw_minibuffer[binary_id].buffer = sh_css_fw->blob.code;

	वापस 0;
पूर्ण

पूर्णांक
sh_css_load_blob_info(स्थिर अक्षर *fw, स्थिर काष्ठा ia_css_fw_info *bi,
		      काष्ठा ia_css_blob_descr *bd,
		      अचिन्हित पूर्णांक index)
अणु
	स्थिर अक्षर *name;
	स्थिर अचिन्हित अक्षर *blob;

	अगर ((!fw) || (!bd))
		वापस -EINVAL;

	/* Special हाल: only one binary in fw */
	अगर (!bi)
		bi = (स्थिर काष्ठा ia_css_fw_info *)fw;

	name = fw + bi->blob.prog_name_offset;
	blob = (स्थिर अचिन्हित अक्षर *)fw + bi->blob.offset;

	/* sanity check */
	अगर (bi->blob.size !=
		bi->blob.text_size + bi->blob.icache_size +
			bi->blob.data_size + bi->blob.padding_size) अणु
		/* sanity check, note the padding bytes added क्रम section to DDR alignment */
		वापस -EINVAL;
	पूर्ण

	अगर ((bi->blob.offset % (1UL << (ISP_PMEM_WIDTH_LOG2 - 3))) != 0)
		वापस -EINVAL;

	bd->blob = blob;
	bd->header = *bi;

	अगर (bi->type == ia_css_isp_firmware || bi->type == ia_css_sp_firmware) अणु
		अक्षर *namebuffer;

		namebuffer = kstrdup(name, GFP_KERNEL);
		अगर (!namebuffer)
			वापस -ENOMEM;
		bd->name = fw_minibuffer[index].name = namebuffer;
	पूर्ण अन्यथा अणु
		bd->name = name;
	पूर्ण

	अगर (bi->type == ia_css_isp_firmware) अणु
		माप_प्रकार paramकाष्ठा_size = माप(काष्ठा ia_css_memory_offsets);
		माप_प्रकार configकाष्ठा_size = माप(काष्ठा ia_css_config_memory_offsets);
		माप_प्रकार stateकाष्ठा_size = माप(काष्ठा ia_css_state_memory_offsets);

		अक्षर *parambuf = kदो_स्मृति(paramकाष्ठा_size + configकाष्ठा_size +
					 stateकाष्ठा_size,
					 GFP_KERNEL);
		अगर (!parambuf)
			वापस -ENOMEM;

		bd->mem_offsets.array[IA_CSS_PARAM_CLASS_PARAM].ptr = शून्य;
		bd->mem_offsets.array[IA_CSS_PARAM_CLASS_CONFIG].ptr = शून्य;
		bd->mem_offsets.array[IA_CSS_PARAM_CLASS_STATE].ptr = शून्य;

		fw_minibuffer[index].buffer = parambuf;

		/* copy ia_css_memory_offsets */
		स_नकल(parambuf, (व्योम *)(fw +
					  bi->blob.memory_offsets.offsets[IA_CSS_PARAM_CLASS_PARAM]),
		       paramकाष्ठा_size);
		bd->mem_offsets.array[IA_CSS_PARAM_CLASS_PARAM].ptr = parambuf;

		/* copy ia_css_config_memory_offsets */
		स_नकल(parambuf + paramकाष्ठा_size,
		       (व्योम *)(fw + bi->blob.memory_offsets.offsets[IA_CSS_PARAM_CLASS_CONFIG]),
		       configकाष्ठा_size);
		bd->mem_offsets.array[IA_CSS_PARAM_CLASS_CONFIG].ptr = parambuf +
		paramकाष्ठा_size;

		/* copy ia_css_state_memory_offsets */
		स_नकल(parambuf + paramकाष्ठा_size + configकाष्ठा_size,
		       (व्योम *)(fw + bi->blob.memory_offsets.offsets[IA_CSS_PARAM_CLASS_STATE]),
		       stateकाष्ठा_size);
		bd->mem_offsets.array[IA_CSS_PARAM_CLASS_STATE].ptr = parambuf +
		paramकाष्ठा_size + configकाष्ठा_size;
	पूर्ण
	वापस 0;
पूर्ण

bool
sh_css_check_firmware_version(काष्ठा device *dev, स्थिर अक्षर *fw_data)
अणु
	काष्ठा sh_css_fw_bi_file_h *file_header;

	स्थिर अक्षर *release_version;

	अगर (!IS_ISP2401)
		release_version = isp2400_release_version;
	अन्यथा
		release_version = isp2401_release_version;

	firmware_header = (काष्ठा firmware_header *)fw_data;
	file_header = &firmware_header->file_header;

	अगर (म_भेद(file_header->version, release_version) != 0) अणु
		dev_err(dev, "Firmware version may not be compatible with this driver\n");
		dev_err(dev, "Expecting version '%s', but firmware is '%s'.\n",
			release_version, file_header->version);
	पूर्ण

	/* For now, let's just accept a wrong version, even अगर wrong */
	वापस false;
पूर्ण

अटल स्थिर अक्षर * स्थिर fw_type_name[] = अणु
	[ia_css_sp_firmware]		= "SP",
	[ia_css_isp_firmware]		= "ISP",
	[ia_css_bootloader_firmware]	= "BootLoader",
	[ia_css_acc_firmware]		= "accel",
पूर्ण;

अटल स्थिर अक्षर * स्थिर fw_acc_type_name[] = अणु
	[IA_CSS_ACC_NONE] =		"Normal",
	[IA_CSS_ACC_OUTPUT] =		"Accel for output",
	[IA_CSS_ACC_VIEWFINDER] =	"Accel for viewfinder",
	[IA_CSS_ACC_STANDALONE] =	"Stand-alone accel",
पूर्ण;

पूर्णांक
sh_css_load_firmware(काष्ठा device *dev, स्थिर अक्षर *fw_data,
		     अचिन्हित पूर्णांक fw_size)
अणु
	अचिन्हित पूर्णांक i;
	काष्ठा ia_css_fw_info *binaries;
	काष्ठा sh_css_fw_bi_file_h *file_header;
	पूर्णांक ret;
	स्थिर अक्षर *release_version;

	अगर (!IS_ISP2401)
		release_version = isp2400_release_version;
	अन्यथा
		release_version = isp2401_release_version;

	firmware_header = (काष्ठा firmware_header *)fw_data;
	file_header = &firmware_header->file_header;
	binaries = &firmware_header->binary_header;
	strscpy(FW_rel_ver_name, file_header->version,
		min(माप(FW_rel_ver_name), माप(file_header->version)));
	ret = sh_css_check_firmware_version(dev, fw_data);
	अगर (ret) अणु
		IA_CSS_ERROR("CSS code version (%s) and firmware version (%s) mismatch!",
			     file_header->version, release_version);
		वापस -EINVAL;
	पूर्ण अन्यथा अणु
		IA_CSS_LOG("successfully load firmware version %s", release_version);
	पूर्ण

	/* some sanity checks */
	अगर (!fw_data || fw_size < माप(काष्ठा sh_css_fw_bi_file_h))
		वापस -EINVAL;

	अगर (file_header->h_size != माप(काष्ठा sh_css_fw_bi_file_h))
		वापस -EINVAL;

	sh_css_num_binaries = file_header->binary_nr;
	/* Only allocate memory क्रम ISP blob info */
	अगर (sh_css_num_binaries > NUM_OF_SPS) अणु
		sh_css_blob_info = kदो_स्मृति(
		    (sh_css_num_binaries - NUM_OF_SPS) *
		    माप(*sh_css_blob_info), GFP_KERNEL);
		अगर (!sh_css_blob_info)
			वापस -ENOMEM;
	पूर्ण अन्यथा अणु
		sh_css_blob_info = शून्य;
	पूर्ण

	fw_minibuffer = kसुस्मृति(sh_css_num_binaries, माप(काष्ठा fw_param),
				GFP_KERNEL);
	अगर (!fw_minibuffer)
		वापस -ENOMEM;

	क्रम (i = 0; i < sh_css_num_binaries; i++) अणु
		काष्ठा ia_css_fw_info *bi = &binaries[i];
		/*
		 * note: the var below is made अटल as it is quite large;
		 * अगर it is not अटल it ends up on the stack which could
		 * cause issues क्रम drivers
		 */
		अटल काष्ठा ia_css_blob_descr bd;
		पूर्णांक err;

		err = sh_css_load_blob_info(fw_data, bi, &bd, i);

		अगर (err)
			वापस -EINVAL;

		अगर (bi->blob.offset + bi->blob.size > fw_size)
			वापस -EINVAL;

		चयन (bd.header.type) अणु
		हाल ia_css_isp_firmware:
			अगर (bd.header.info.isp.type > IA_CSS_ACC_STANDALONE) अणु
				dev_err(dev, "binary #%2d: invalid SP type\n",
					i);
				वापस -EINVAL;
			पूर्ण

			dev_dbg(dev,
				"binary #%-2d type %s (%s), binary id is %2d: %s\n",
				i,
				fw_type_name[bd.header.type],
				fw_acc_type_name[bd.header.info.isp.type],
				bd.header.info.isp.sp.id,
				bd.name);
			अवरोध;
		हाल ia_css_sp_firmware:
		हाल ia_css_bootloader_firmware:
		हाल ia_css_acc_firmware:
			dev_dbg(dev,
				"binary #%-2d type %s: %s\n",
				i, fw_type_name[bd.header.type],
				bd.name);
			अवरोध;
		शेष:
			अगर (bd.header.info.isp.type > IA_CSS_ACC_STANDALONE) अणु
				dev_err(dev,
					"binary #%2d: invalid firmware type\n",
					i);
				वापस -EINVAL;
			पूर्ण
			अवरोध;
		पूर्ण

		अगर (bi->type == ia_css_sp_firmware) अणु
			अगर (i != SP_FIRMWARE)
				वापस -EINVAL;
			err = setup_binary(bi, fw_data, &sh_css_sp_fw, i);
			अगर (err)
				वापस err;

		पूर्ण अन्यथा अणु
			/*
			 * All subsequent binaries
			 * (including bootloaders) (i>NUM_OF_SPS)
			 * are ISP firmware
			 */
			अगर (i < NUM_OF_SPS)
				वापस -EINVAL;

			अगर (bi->type != ia_css_isp_firmware)
				वापस -EINVAL;
			अगर (!sh_css_blob_info) /* cannot happen but KW करोes not see this */
				वापस -EINVAL;
			sh_css_blob_info[i - NUM_OF_SPS] = bd;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

व्योम sh_css_unload_firmware(व्योम)
अणु
	/* release firmware minibuffer */
	अगर (fw_minibuffer) अणु
		अचिन्हित पूर्णांक i = 0;

		क्रम (i = 0; i < sh_css_num_binaries; i++) अणु
			अगर (fw_minibuffer[i].name)
				kमुक्त((व्योम *)fw_minibuffer[i].name);
			अगर (fw_minibuffer[i].buffer)
				kvमुक्त(fw_minibuffer[i].buffer);
		पूर्ण
		kमुक्त(fw_minibuffer);
		fw_minibuffer = शून्य;
	पूर्ण

	स_रखो(&sh_css_sp_fw, 0, माप(sh_css_sp_fw));
	kमुक्त(sh_css_blob_info);
	sh_css_blob_info = शून्य;
	sh_css_num_binaries = 0;
पूर्ण

ia_css_ptr
sh_css_load_blob(स्थिर अचिन्हित अक्षर *blob, अचिन्हित पूर्णांक size)
अणु
	ia_css_ptr target_addr = hmm_alloc(size, HMM_BO_PRIVATE, 0, शून्य, 0);
	/*
	 * this will allocate memory aligned to a DDR word boundary which
	 * is required क्रम the CSS DMA to पढ़ो the inकाष्ठाions.
	 */

	निश्चित(blob);
	अगर (target_addr)
		hmm_store(target_addr, blob, size);
	वापस target_addr;
पूर्ण
