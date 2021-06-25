<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (C) 2018 Intel Corporation */

#अगर_अघोषित __IPU3_CSS_FW_H
#घोषणा __IPU3_CSS_FW_H

/******************* Firmware file definitions *******************/

#घोषणा IMGU_FW_NAME			"intel/ipu3-fw.bin"

प्रकार u32 imgu_fw_ptr;

क्रमागत imgu_fw_type अणु
	IMGU_FW_SP_FIRMWARE,	/* Firmware क्रम the SP */
	IMGU_FW_SP1_FIRMWARE,	/* Firmware क्रम the SP1 */
	IMGU_FW_ISP_FIRMWARE,	/* Firmware क्रम the ISP */
	IMGU_FW_BOOTLOADER_FIRMWARE,	/* Firmware क्रम the BootLoader */
	IMGU_FW_ACC_FIRMWARE	/* Firmware क्रम accelerations */
पूर्ण;

क्रमागत imgu_fw_acc_type अणु
	IMGU_FW_ACC_NONE,	/* Normal binary */
	IMGU_FW_ACC_OUTPUT,	/* Accelerator stage on output frame */
	IMGU_FW_ACC_VIEWFINDER,	/* Accelerator stage on viewfinder frame */
	IMGU_FW_ACC_STANDALONE,	/* Stand-alone acceleration */
पूर्ण;

काष्ठा imgu_fw_isp_parameter अणु
	u32 offset;		/* Offset in isp_<mem> config, params, etc. */
	u32 size;		/* Disabled अगर 0 */
पूर्ण;

काष्ठा imgu_fw_param_memory_offsets अणु
	काष्ठा अणु
		काष्ठा imgu_fw_isp_parameter lin;	/* lin_vmem_params */
		काष्ठा imgu_fw_isp_parameter tnr3;	/* tnr3_vmem_params */
		काष्ठा imgu_fw_isp_parameter xnr3;	/* xnr3_vmem_params */
	पूर्ण vmem;
	काष्ठा अणु
		काष्ठा imgu_fw_isp_parameter tnr;
		काष्ठा imgu_fw_isp_parameter tnr3;	/* tnr3_params */
		काष्ठा imgu_fw_isp_parameter xnr3;	/* xnr3_params */
		काष्ठा imgu_fw_isp_parameter plane_io_config;	/* 192 bytes */
		काष्ठा imgu_fw_isp_parameter rgbir;	/* rgbir_params */
	पूर्ण dmem;
पूर्ण;

काष्ठा imgu_fw_config_memory_offsets अणु
	काष्ठा अणु
		काष्ठा imgu_fw_isp_parameter iterator;
		काष्ठा imgu_fw_isp_parameter dvs;
		काष्ठा imgu_fw_isp_parameter output;
		काष्ठा imgu_fw_isp_parameter raw;
		काष्ठा imgu_fw_isp_parameter input_yuv;
		काष्ठा imgu_fw_isp_parameter tnr;
		काष्ठा imgu_fw_isp_parameter tnr3;
		काष्ठा imgu_fw_isp_parameter ref;
	पूर्ण dmem;
पूर्ण;

काष्ठा imgu_fw_state_memory_offsets अणु
	काष्ठा अणु
		काष्ठा imgu_fw_isp_parameter tnr;
		काष्ठा imgu_fw_isp_parameter tnr3;
		काष्ठा imgu_fw_isp_parameter ref;
	पूर्ण dmem;
पूर्ण;

जोड़ imgu_fw_all_memory_offsets अणु
	काष्ठा अणु
		u64 imgu_fw_mem_offsets[3]; /* params, config, state */
	पूर्ण offsets;
	काष्ठा अणु
		u64 ptr;
	पूर्ण array[IMGU_ABI_PARAM_CLASS_NUM];
पूर्ण;

काष्ठा imgu_fw_binary_xinfo अणु
	/* Part that is of पूर्णांकerest to the SP. */
	काष्ठा imgu_abi_binary_info sp;

	/* Rest of the binary info, only पूर्णांकeresting to the host. */
	u32 type;	/* क्रमागत imgu_fw_acc_type */

	u32 num_output_क्रमmats __aligned(8);
	u32 output_क्रमmats[IMGU_ABI_FRAME_FORMAT_NUM];	/* क्रमागत frame_क्रमmat */

	/* number of supported vf क्रमmats */
	u32 num_vf_क्रमmats __aligned(8);
	/* types of supported vf क्रमmats */
	u32 vf_क्रमmats[IMGU_ABI_FRAME_FORMAT_NUM];	/* क्रमागत frame_क्रमmat */
	u8 num_output_pins;
	imgu_fw_ptr xmem_addr;

	u64 imgu_fw_blob_descr_ptr __aligned(8);
	u32 blob_index __aligned(8);
	जोड़ imgu_fw_all_memory_offsets mem_offsets __aligned(8);
	काष्ठा imgu_fw_binary_xinfo *next __aligned(8);
पूर्ण;

काष्ठा imgu_fw_sp_info अणु
	u32 init_dmem_data;	/* data sect config, stored to dmem */
	u32 per_frame_data;	/* Per frame data, stored to dmem */
	u32 group;		/* Per pipeline data, loaded by dma */
	u32 output;		/* SP output data, loaded by dmem */
	u32 host_sp_queue;	/* Host <-> SP queues */
	u32 host_sp_com;	/* Host <-> SP commands */
	u32 isp_started;	/* P'ed from sensor thपढ़ो, csim only */
	u32 sw_state;		/* Polled from css, क्रमागत imgu_abi_sp_swstate */
	u32 host_sp_queues_initialized;	/* Polled from the SP */
	u32 sleep_mode;		/* dअगरferent mode to halt SP */
	u32 invalidate_tlb;	/* inक्रमm SP to invalidate mmu TLB */
	u32 debug_buffer_ddr_address;	/* the addr of DDR debug queue */

	/* input प्रणाली perf count array */
	u32 perf_counter_input_प्रणाली_error;
	u32 thपढ़ोs_stack;	/* sp thपढ़ो's stack poपूर्णांकers */
	u32 thपढ़ोs_stack_size;	/* sp thपढ़ो's stack sizes */
	u32 curr_binary_id;	/* current binary id */
	u32 raw_copy_line_count;	/* raw copy line counter */
	u32 ddr_parameter_address;	/* acc param ddrptr, sp dmem */
	u32 ddr_parameter_size;	/* acc param size, sp dmem */
	/* Entry functions */
	u32 sp_entry;		/* The SP entry function */
	u32 tagger_frames_addr;	/* Base address of tagger state */
पूर्ण;

काष्ठा imgu_fw_bl_info अणु
	u32 num_dma_cmds;	/* Number of cmds sent by CSS */
	u32 dma_cmd_list;	/* Dma command list sent by CSS */
	u32 sw_state;		/* Polled from css, क्रमागत imgu_abi_bl_swstate */
	/* Entry functions */
	u32 bl_entry;		/* The SP entry function */
पूर्ण;

काष्ठा imgu_fw_acc_info अणु
	u32 per_frame_data;	/* Dummy क्रम now */
पूर्ण;

जोड़ imgu_fw_जोड़ अणु
	काष्ठा imgu_fw_binary_xinfo isp;	/* ISP info */
	काष्ठा imgu_fw_sp_info sp;	/* SP info */
	काष्ठा imgu_fw_sp_info sp1;	/* SP1 info */
	काष्ठा imgu_fw_bl_info bl;	/* Bootloader info */
	काष्ठा imgu_fw_acc_info acc;	/* Accelerator info */
पूर्ण;

काष्ठा imgu_fw_info अणु
	माप_प्रकार header_size;	/* size of fw header */
	u32 type __aligned(8);	/* क्रमागत imgu_fw_type */

	जोड़ imgu_fw_जोड़ info;	/* Binary info */
	काष्ठा imgu_abi_blob_info blob;	/* Blob info */
	/* Dynamic part */
	u64 next;

	u32 loaded __aligned(8);	/* Firmware has been loaded */
	स्थिर u64 isp_code __aligned(8);	/* ISP poपूर्णांकer to code */
	/* Firmware handle between user space and kernel */
	u32 handle __aligned(8);
	/* Sections to copy from/to ISP */
	काष्ठा imgu_abi_isp_param_segments mem_initializers;
	/* Initializer क्रम local ISP memories */
पूर्ण;

काष्ठा imgu_fw_bi_file_h अणु
	अक्षर version[64];	/* branch tag + week day + समय */
	पूर्णांक binary_nr;		/* Number of binaries */
	अचिन्हित पूर्णांक h_size;	/* माप(काष्ठा imgu_fw_bi_file_h) */
पूर्ण;

काष्ठा imgu_fw_header अणु
	काष्ठा imgu_fw_bi_file_h file_header;
	काष्ठा imgu_fw_info binary_header[1];	/* binary_nr items */
पूर्ण;

/******************* Firmware functions *******************/

पूर्णांक imgu_css_fw_init(काष्ठा imgu_css *css);
व्योम imgu_css_fw_cleanup(काष्ठा imgu_css *css);

अचिन्हित पूर्णांक imgu_css_fw_obgrid_size(स्थिर काष्ठा imgu_fw_info *bi);
व्योम *imgu_css_fw_pipeline_params(काष्ठा imgu_css *css, अचिन्हित पूर्णांक pipe,
				  क्रमागत imgu_abi_param_class cls,
				  क्रमागत imgu_abi_memories mem,
				  काष्ठा imgu_fw_isp_parameter *par,
				  माप_प्रकार par_size, व्योम *binary_params);

#पूर्ण_अगर
