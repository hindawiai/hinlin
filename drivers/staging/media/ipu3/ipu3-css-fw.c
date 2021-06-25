<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) 2018 Intel Corporation

#समावेश <linux/device.h>
#समावेश <linux/firmware.h>
#समावेश <linux/mm.h>
#समावेश <linux/slab.h>

#समावेश "ipu3-css.h"
#समावेश "ipu3-css-fw.h"
#समावेश "ipu3-dmamap.h"

अटल व्योम imgu_css_fw_show_binary(काष्ठा device *dev, काष्ठा imgu_fw_info *bi,
				    स्थिर अक्षर *name)
अणु
	अचिन्हित पूर्णांक i;

	dev_dbg(dev, "found firmware binary type %i size %i name %s\n",
		bi->type, bi->blob.size, name);
	अगर (bi->type != IMGU_FW_ISP_FIRMWARE)
		वापस;

	dev_dbg(dev, "    id %i mode %i bds 0x%x veceven %i/%i out_pins %i\n",
		bi->info.isp.sp.id, bi->info.isp.sp.pipeline.mode,
		bi->info.isp.sp.bds.supported_bds_factors,
		bi->info.isp.sp.enable.vf_veceven,
		bi->info.isp.sp.vf_dec.is_variable,
		bi->info.isp.num_output_pins);

	dev_dbg(dev, "    input (%i,%i)-(%i,%i) formats %s%s%s\n",
		bi->info.isp.sp.input.min_width,
		bi->info.isp.sp.input.min_height,
		bi->info.isp.sp.input.max_width,
		bi->info.isp.sp.input.max_height,
		bi->info.isp.sp.enable.input_yuv ? "yuv420 " : "",
		bi->info.isp.sp.enable.input_feeder ||
		bi->info.isp.sp.enable.input_raw ? "raw8 raw10 " : "",
		bi->info.isp.sp.enable.input_raw ? "raw12" : "");

	dev_dbg(dev, "    internal (%i,%i)\n",
		bi->info.isp.sp.पूर्णांकernal.max_width,
		bi->info.isp.sp.पूर्णांकernal.max_height);

	dev_dbg(dev, "    output (%i,%i)-(%i,%i) formats",
		bi->info.isp.sp.output.min_width,
		bi->info.isp.sp.output.min_height,
		bi->info.isp.sp.output.max_width,
		bi->info.isp.sp.output.max_height);
	क्रम (i = 0; i < bi->info.isp.num_output_क्रमmats; i++)
		dev_dbg(dev, " %i", bi->info.isp.output_क्रमmats[i]);
	dev_dbg(dev, " vf");
	क्रम (i = 0; i < bi->info.isp.num_vf_क्रमmats; i++)
		dev_dbg(dev, " %i", bi->info.isp.vf_क्रमmats[i]);
	dev_dbg(dev, "\n");
पूर्ण

अचिन्हित पूर्णांक imgu_css_fw_obgrid_size(स्थिर काष्ठा imgu_fw_info *bi)
अणु
	अचिन्हित पूर्णांक width = DIV_ROUND_UP(bi->info.isp.sp.पूर्णांकernal.max_width,
					  IMGU_OBGRID_TILE_SIZE * 2) + 1;
	अचिन्हित पूर्णांक height = DIV_ROUND_UP(bi->info.isp.sp.पूर्णांकernal.max_height,
					   IMGU_OBGRID_TILE_SIZE * 2) + 1;
	अचिन्हित पूर्णांक obgrid_size;

	width = ALIGN(width, IPU3_UAPI_ISP_VEC_ELEMS / 4);
	obgrid_size = PAGE_ALIGN(width * height *
				 माप(काष्ठा ipu3_uapi_obgrid_param)) *
				 bi->info.isp.sp.iterator.num_stripes;
	वापस obgrid_size;
पूर्ण

व्योम *imgu_css_fw_pipeline_params(काष्ठा imgu_css *css, अचिन्हित पूर्णांक pipe,
				  क्रमागत imgu_abi_param_class cls,
				  क्रमागत imgu_abi_memories mem,
				  काष्ठा imgu_fw_isp_parameter *par,
				  माप_प्रकार par_size, व्योम *binary_params)
अणु
	काष्ठा imgu_fw_info *bi =
		&css->fwp->binary_header[css->pipes[pipe].bindex];

	अगर (par->offset + par->size >
	    bi->info.isp.sp.mem_initializers.params[cls][mem].size)
		वापस शून्य;

	अगर (par->size != par_size)
		pr_warn("parameter size doesn't match defined size\n");

	अगर (par->size < par_size)
		वापस शून्य;

	वापस binary_params + par->offset;
पूर्ण

व्योम imgu_css_fw_cleanup(काष्ठा imgu_css *css)
अणु
	काष्ठा imgu_device *imgu = dev_get_drvdata(css->dev);

	अगर (css->binary) अणु
		अचिन्हित पूर्णांक i;

		क्रम (i = 0; i < css->fwp->file_header.binary_nr; i++)
			imgu_dmamap_मुक्त(imgu, &css->binary[i]);
		kमुक्त(css->binary);
	पूर्ण
	अगर (css->fw)
		release_firmware(css->fw);

	css->binary = शून्य;
	css->fw = शून्य;
पूर्ण

पूर्णांक imgu_css_fw_init(काष्ठा imgu_css *css)
अणु
	अटल स्थिर u32 BLOCK_MAX = 65536;
	काष्ठा imgu_device *imgu = dev_get_drvdata(css->dev);
	काष्ठा device *dev = css->dev;
	अचिन्हित पूर्णांक i, j, binary_nr;
	पूर्णांक r;

	r = request_firmware(&css->fw, IMGU_FW_NAME, css->dev);
	अगर (r)
		वापस r;

	/* Check and display fw header info */

	css->fwp = (काष्ठा imgu_fw_header *)css->fw->data;
	अगर (css->fw->size < माप(काष्ठा imgu_fw_header *) ||
	    css->fwp->file_header.h_size != माप(काष्ठा imgu_fw_bi_file_h))
		जाओ bad_fw;
	अगर (माप(काष्ठा imgu_fw_bi_file_h) +
	    css->fwp->file_header.binary_nr * माप(काष्ठा imgu_fw_info) >
	    css->fw->size)
		जाओ bad_fw;

	dev_info(dev, "loaded firmware version %.64s, %u binaries, %zu bytes\n",
		 css->fwp->file_header.version, css->fwp->file_header.binary_nr,
		 css->fw->size);

	/* Validate and display info on fw binaries */

	binary_nr = css->fwp->file_header.binary_nr;

	css->fw_bl = -1;
	css->fw_sp[0] = -1;
	css->fw_sp[1] = -1;

	क्रम (i = 0; i < binary_nr; i++) अणु
		काष्ठा imgu_fw_info *bi = &css->fwp->binary_header[i];
		स्थिर अक्षर *name = (व्योम *)css->fwp + bi->blob.prog_name_offset;
		माप_प्रकार len;

		अगर (bi->blob.prog_name_offset >= css->fw->size)
			जाओ bad_fw;
		len = strnlen(name, css->fw->size - bi->blob.prog_name_offset);
		अगर (len + 1 > css->fw->size - bi->blob.prog_name_offset ||
		    len + 1 >= IMGU_ABI_MAX_BINARY_NAME)
			जाओ bad_fw;

		अगर (bi->blob.size != bi->blob.text_size + bi->blob.icache_size
		    + bi->blob.data_size + bi->blob.padding_size)
			जाओ bad_fw;
		अगर (bi->blob.offset + bi->blob.size > css->fw->size)
			जाओ bad_fw;

		अगर (bi->type == IMGU_FW_BOOTLOADER_FIRMWARE) अणु
			css->fw_bl = i;
			अगर (bi->info.bl.sw_state >= css->iomem_length ||
			    bi->info.bl.num_dma_cmds >= css->iomem_length ||
			    bi->info.bl.dma_cmd_list >= css->iomem_length)
				जाओ bad_fw;
		पूर्ण
		अगर (bi->type == IMGU_FW_SP_FIRMWARE ||
		    bi->type == IMGU_FW_SP1_FIRMWARE) अणु
			css->fw_sp[bi->type == IMGU_FW_SP_FIRMWARE ? 0 : 1] = i;
			अगर (bi->info.sp.per_frame_data >= css->iomem_length ||
			    bi->info.sp.init_dmem_data >= css->iomem_length ||
			    bi->info.sp.host_sp_queue >= css->iomem_length ||
			    bi->info.sp.isp_started >= css->iomem_length ||
			    bi->info.sp.sw_state >= css->iomem_length ||
			    bi->info.sp.sleep_mode >= css->iomem_length ||
			    bi->info.sp.invalidate_tlb >= css->iomem_length ||
			    bi->info.sp.host_sp_com >= css->iomem_length ||
			    bi->info.sp.output + 12 >= css->iomem_length ||
			    bi->info.sp.host_sp_queues_initialized >=
			    css->iomem_length)
				जाओ bad_fw;
		पूर्ण
		अगर (bi->type != IMGU_FW_ISP_FIRMWARE)
			जारी;

		अगर (bi->info.isp.sp.pipeline.mode >= IPU3_CSS_PIPE_ID_NUM)
			जाओ bad_fw;

		अगर (bi->info.isp.sp.iterator.num_stripes >
		    IPU3_UAPI_MAX_STRIPES)
			जाओ bad_fw;

		अगर (bi->info.isp.num_vf_क्रमmats > IMGU_ABI_FRAME_FORMAT_NUM ||
		    bi->info.isp.num_output_क्रमmats > IMGU_ABI_FRAME_FORMAT_NUM)
			जाओ bad_fw;

		क्रम (j = 0; j < bi->info.isp.num_output_क्रमmats; j++)
			अगर (bi->info.isp.output_क्रमmats[j] >=
			    IMGU_ABI_FRAME_FORMAT_NUM)
				जाओ bad_fw;
		क्रम (j = 0; j < bi->info.isp.num_vf_क्रमmats; j++)
			अगर (bi->info.isp.vf_क्रमmats[j] >=
			    IMGU_ABI_FRAME_FORMAT_NUM)
				जाओ bad_fw;

		अगर (bi->info.isp.sp.block.block_width <= 0 ||
		    bi->info.isp.sp.block.block_width > BLOCK_MAX ||
		    bi->info.isp.sp.block.output_block_height <= 0 ||
		    bi->info.isp.sp.block.output_block_height > BLOCK_MAX)
			जाओ bad_fw;

		अगर (bi->blob.memory_offsets.offsets[IMGU_ABI_PARAM_CLASS_PARAM]
		    + माप(काष्ठा imgu_fw_param_memory_offsets) >
		    css->fw->size ||
		    bi->blob.memory_offsets.offsets[IMGU_ABI_PARAM_CLASS_CONFIG]
		    + माप(काष्ठा imgu_fw_config_memory_offsets) >
		    css->fw->size ||
		    bi->blob.memory_offsets.offsets[IMGU_ABI_PARAM_CLASS_STATE]
		    + माप(काष्ठा imgu_fw_state_memory_offsets) >
		    css->fw->size)
			जाओ bad_fw;

		imgu_css_fw_show_binary(dev, bi, name);
	पूर्ण

	अगर (css->fw_bl == -1 || css->fw_sp[0] == -1 || css->fw_sp[1] == -1)
		जाओ bad_fw;

	/* Allocate and map fw binaries पूर्णांकo IMGU */

	css->binary = kसुस्मृति(binary_nr, माप(*css->binary), GFP_KERNEL);
	अगर (!css->binary) अणु
		r = -ENOMEM;
		जाओ error_out;
	पूर्ण

	क्रम (i = 0; i < css->fwp->file_header.binary_nr; i++) अणु
		काष्ठा imgu_fw_info *bi = &css->fwp->binary_header[i];
		व्योम *blob = (व्योम *)css->fwp + bi->blob.offset;
		माप_प्रकार size = bi->blob.size;

		अगर (!imgu_dmamap_alloc(imgu, &css->binary[i], size)) अणु
			r = -ENOMEM;
			जाओ error_out;
		पूर्ण
		स_नकल(css->binary[i].vaddr, blob, size);
	पूर्ण

	वापस 0;

bad_fw:
	dev_err(dev, "invalid firmware binary, size %u\n", (पूर्णांक)css->fw->size);
	r = -ENODEV;

error_out:
	imgu_css_fw_cleanup(css);
	वापस r;
पूर्ण
