<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
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

#अगर_अघोषित _IA_CSS_ACC_TYPES_H
#घोषणा _IA_CSS_ACC_TYPES_H

/* @file
 * This file contains types used क्रम acceleration
 */

#समावेश <प्रणाली_local.h>	/* HAS_IRQ_MAP_VERSION_# */
#समावेश <type_support.h>
#समावेश <platक्रमm_support.h>
#समावेश <debug_global.h>

#समावेश "ia_css_types.h"
#समावेश "ia_css_frame_format.h"

/* Should be included without the path.
   However, that requires adding the path to numerous makefiles
   that have nothing to करो with isp parameters.
 */
#समावेश "runtime/isp_param/interface/ia_css_isp_param_types.h"

/* Types क्रम the acceleration API.
 * These should be moved to sh_css_पूर्णांकernal.h once the old acceleration
 * argument handling has been completed.
 * After that, पूर्णांकerpretation of these काष्ठाures is no दीर्घer needed
 * in the kernel and HAL.
*/

/* Type of acceleration.
 */
क्रमागत ia_css_acc_type अणु
	IA_CSS_ACC_NONE,	/** Normal binary */
	IA_CSS_ACC_OUTPUT,	/** Accelerator stage on output frame */
	IA_CSS_ACC_VIEWFINDER,	/** Accelerator stage on viewfinder frame */
	IA_CSS_ACC_STANDALONE,	/** Stand-alone acceleration */
पूर्ण;

/* Cells types
 */
क्रमागत ia_css_cell_type अणु
	IA_CSS_SP0 = 0,
	IA_CSS_SP1,
	IA_CSS_ISP,
	MAX_NUM_OF_CELLS
पूर्ण;

/* Firmware types.
 */
क्रमागत ia_css_fw_type अणु
	ia_css_sp_firmware,		/** Firmware क्रम the SP */
	ia_css_isp_firmware,		/** Firmware क्रम the ISP */
	ia_css_bootloader_firmware,	/** Firmware क्रम the BootLoader */
	ia_css_acc_firmware		/** Firmware क्रम accelrations */
पूर्ण;

काष्ठा ia_css_blob_descr;

/* Blob descriptor.
 * This काष्ठाure describes an SP or ISP blob.
 * It describes the test, data and bss sections as well as position in a
 * firmware file.
 * For convenience, it contains dynamic data after loading.
 */
काष्ठा ia_css_blob_info अणु
	/** Static blob data */
	u32 offset;		/** Blob offset in fw file */
	काष्ठा ia_css_isp_param_memory_offsets
		memory_offsets;  /** offset wrt hdr in bytes */
	u32 prog_name_offset;  /** offset wrt hdr in bytes */
	u32 size;			/** Size of blob */
	u32 padding_size;	/** total cummulative of bytes added due to section alignment */
	u32 icache_source;	/** Position of icache in blob */
	u32 icache_size;	/** Size of icache section */
	u32 icache_padding;/** bytes added due to icache section alignment */
	u32 text_source;	/** Position of text in blob */
	u32 text_size;		/** Size of text section */
	u32 text_padding;	/** bytes added due to text section alignment */
	u32 data_source;	/** Position of data in blob */
	u32 data_target;	/** Start of data in SP dmem */
	u32 data_size;		/** Size of text section */
	u32 data_padding;	/** bytes added due to data section alignment */
	u32 bss_target;	/** Start position of bss in SP dmem */
	u32 bss_size;		/** Size of bss section */
	/** Dynamic data filled by loader */
	CSS_ALIGN(स्थिर व्योम  *code,
		  8);		/** Code section असलolute poपूर्णांकer within fw, code = icache + text */
	CSS_ALIGN(स्थिर व्योम  *data,
		  8);		/** Data section असलolute poपूर्णांकer within fw, data = data + bss */
पूर्ण;

काष्ठा ia_css_binary_input_info अणु
	u32		min_width;
	u32		min_height;
	u32		max_width;
	u32		max_height;
	u32		source; /* memory, sensor, variable */
पूर्ण;

काष्ठा ia_css_binary_output_info अणु
	u32		min_width;
	u32		min_height;
	u32		max_width;
	u32		max_height;
	u32		num_chunks;
	u32		variable_क्रमmat;
पूर्ण;

काष्ठा ia_css_binary_पूर्णांकernal_info अणु
	u32		max_width;
	u32		max_height;
पूर्ण;

काष्ठा ia_css_binary_bds_info अणु
	u32		supported_bds_factors;
पूर्ण;

काष्ठा ia_css_binary_dvs_info अणु
	u32		max_envelope_width;
	u32		max_envelope_height;
पूर्ण;

काष्ठा ia_css_binary_vf_dec_info अणु
	u32		is_variable;
	u32		max_log_करोwnscale;
पूर्ण;

काष्ठा ia_css_binary_s3a_info अणु
	u32		s3atbl_use_dmem;
	u32		fixed_s3a_deci_log;
पूर्ण;

/* DPC related binary info */
काष्ठा ia_css_binary_dpc_info अणु
	u32		bnr_lite; /** bnr lite enable flag */
पूर्ण;

काष्ठा ia_css_binary_iterator_info अणु
	u32		num_stripes;
	u32		row_stripes_height;
	u32		row_stripes_overlap_lines;
पूर्ण;

काष्ठा ia_css_binary_address_info अणु
	u32		isp_addresses;	/* Address in ISP dmem */
	u32		मुख्य_entry;	/* Address of entry fct */
	u32		in_frame;	/* Address in ISP dmem */
	u32		out_frame;	/* Address in ISP dmem */
	u32		in_data;	/* Address in ISP dmem */
	u32		out_data;	/* Address in ISP dmem */
	u32		sh_dma_cmd_ptr;     /* In ISP dmem */
पूर्ण;

काष्ठा ia_css_binary_uds_info अणु
	u16	bpp;
	u16	use_bci;
	u16	use_str;
	u16	woix;
	u16	woiy;
	u16	extra_out_vecs;
	u16	vectors_per_line_in;
	u16	vectors_per_line_out;
	u16	vectors_c_per_line_in;
	u16	vectors_c_per_line_out;
	u16	vmem_gdc_in_block_height_y;
	u16	vmem_gdc_in_block_height_c;
	/* uपूर्णांक16_t padding; */
पूर्ण;

काष्ठा ia_css_binary_pipeline_info अणु
	u32	mode;
	u32	isp_pipe_version;
	u32	pipelining;
	u32	c_subsampling;
	u32	top_cropping;
	u32	left_cropping;
	u32	variable_resolution;
पूर्ण;

काष्ठा ia_css_binary_block_info अणु
	u32	block_width;
	u32	block_height;
	u32	output_block_height;
पूर्ण;

/* Structure describing an ISP binary.
 * It describes the capabilities of a binary, like the maximum resolution,
 * support features, dma channels, uds features, etc.
 * This part is to be used by the SP.
 * Future refactoring should move binary properties to ia_css_binary_xinfo,
 * thereby making the SP code more binary independent.
 */
काष्ठा ia_css_binary_info अणु
	CSS_ALIGN(u32			id, 8); /* IA_CSS_BINARY_ID_* */
	काष्ठा ia_css_binary_pipeline_info	pipeline;
	काष्ठा ia_css_binary_input_info		input;
	काष्ठा ia_css_binary_output_info	output;
	काष्ठा ia_css_binary_पूर्णांकernal_info	पूर्णांकernal;
	काष्ठा ia_css_binary_bds_info		bds;
	काष्ठा ia_css_binary_dvs_info		dvs;
	काष्ठा ia_css_binary_vf_dec_info	vf_dec;
	काष्ठा ia_css_binary_s3a_info		s3a;
	काष्ठा ia_css_binary_dpc_info		dpc_bnr; /** DPC related binary info */
	काष्ठा ia_css_binary_iterator_info	iterator;
	काष्ठा ia_css_binary_address_info	addresses;
	काष्ठा ia_css_binary_uds_info		uds;
	काष्ठा ia_css_binary_block_info		block;
	काष्ठा ia_css_isp_param_isp_segments	mem_initializers;
	/* MW: Packing (related) bools in an पूर्णांकeger ?? */
	काष्ठा अणु
		/* ISP2401 */
		u8	luma_only;
		u8	input_yuv;
		u8	input_raw;

		u8	reduced_pipe;
		u8	vf_veceven;
		u8	dis;
		u8	dvs_envelope;
		u8	uds;
		u8	dvs_6axis;
		u8	block_output;
		u8	streaming_dma;
		u8	ds;
		u8	bayer_fir_6db;
		u8	raw_binning;
		u8	continuous;
		u8	s3a;
		u8	fpnr;
		u8	sc;
		u8	macc;
		u8	output;
		u8	ref_frame;
		u8	tnr;
		u8	xnr;
		u8	params;
		u8	ca_gdc;
		u8	isp_addresses;
		u8	in_frame;
		u8	out_frame;
		u8	high_speed;
		u8	dpc;
		u8 padding[2];
	पूर्ण enable;
	काष्ठा अणु
		/* DMA channel ID: [0,...,HIVE_ISP_NUM_DMA_CHANNELS> */
		u8	ref_y_channel;
		u8	ref_c_channel;
		u8	tnr_channel;
		u8	tnr_out_channel;
		u8	dvs_coords_channel;
		u8	output_channel;
		u8	c_channel;
		u8	vfout_channel;
		u8	vfout_c_channel;
		u8	vfdec_bits_per_pixel;
		u8	claimed_by_isp;
		u8 padding[2];
	पूर्ण dma;
पूर्ण;

/* Structure describing an ISP binary.
 * It describes the capabilities of a binary, like the maximum resolution,
 * support features, dma channels, uds features, etc.
 */
काष्ठा ia_css_binary_xinfo अणु
	/* Part that is of पूर्णांकerest to the SP. */
	काष्ठा ia_css_binary_info    sp;

	/* Rest of the binary info, only पूर्णांकeresting to the host. */
	क्रमागत ia_css_acc_type	     type;

	CSS_ALIGN(s32	     num_output_क्रमmats, 8);
	क्रमागत ia_css_frame_क्रमmat     output_क्रमmats[IA_CSS_FRAME_FORMAT_NUM];

	CSS_ALIGN(s32	     num_vf_क्रमmats, 8); /** number of supported vf क्रमmats */
	क्रमागत ia_css_frame_क्रमmat
	vf_क्रमmats[IA_CSS_FRAME_FORMAT_NUM]; /** types of supported vf क्रमmats */
	u8			     num_output_pins;
	ia_css_ptr		     xmem_addr;

	CSS_ALIGN(स्थिर काष्ठा ia_css_blob_descr *blob, 8);
	CSS_ALIGN(u32 blob_index, 8);
	CSS_ALIGN(जोड़ ia_css_all_memory_offsets mem_offsets, 8);
	CSS_ALIGN(काष्ठा ia_css_binary_xinfo *next, 8);
पूर्ण;

/* Structure describing the Bootloader (an ISP binary).
 * It contains several address, either in ddr, isp_dmem or
 * the entry function in icache.
 */
काष्ठा ia_css_bl_info अणु
	u32 num_dma_cmds;	/** Number of cmds sent by CSS */
	u32 dma_cmd_list;	/** Dma command list sent by CSS */
	u32 sw_state;	/** Polled from css */
	/* Entry functions */
	u32 bl_entry;	/** The SP entry function */
पूर्ण;

/* Structure describing the SP binary.
 * It contains several address, either in ddr, sp_dmem or
 * the entry function in pmem.
 */
काष्ठा ia_css_sp_info अणु
	u32 init_dmem_data; /** data sect config, stored to dmem */
	u32 per_frame_data; /** Per frame data, stored to dmem */
	u32 group;		/** Per pipeline data, loaded by dma */
	u32 output;		/** SP output data, loaded by dmem */
	u32 host_sp_queue;	/** Host <-> SP queues */
	u32 host_sp_com;/** Host <-> SP commands */
	u32 isp_started;	/** Polled from sensor thपढ़ो, csim only */
	u32 sw_state;	/** Polled from css */
	u32 host_sp_queues_initialized; /** Polled from the SP */
	u32 sleep_mode;  /** dअगरferent mode to halt SP */
	u32 invalidate_tlb;		/** inक्रमm SP to invalidate mmu TLB */

	/* ISP2400 */
	u32 stop_copy_preview;       /** suspend copy and preview pipe when capture */

	u32 debug_buffer_ddr_address;	/** inक्रमm SP the address
	of DDR debug queue */
	u32 perf_counter_input_प्रणाली_error; /** input प्रणाली perf
	counter array */
#अगर_घोषित HAS_WATCHDOG_SP_THREAD_DEBUG
	u32 debug_रुको; /** thपढ़ो/pipe post mortem debug */
	u32 debug_stage; /** thपढ़ो/pipe post mortem debug */
	u32 debug_stripe; /** thपढ़ो/pipe post mortem debug */
#पूर्ण_अगर
	u32 thपढ़ोs_stack; /** sp thपढ़ो's stack poपूर्णांकers */
	u32 thपढ़ोs_stack_size; /** sp thपढ़ो's stack sizes */
	u32 curr_binary_id;        /** current binary id */
	u32 raw_copy_line_count;   /** raw copy line counter */
	u32 ddr_parameter_address; /** acc param ddrptr, sp dmem */
	u32 ddr_parameter_size;    /** acc param size, sp dmem */
	/* Entry functions */
	u32 sp_entry;	/** The SP entry function */
	u32 tagger_frames_addr;   /** Base address of tagger state */
पूर्ण;

/* The following #अगर is there because this header file is also included
   by SP and ISP code but they करो not need this data and HIVECC has alignment
   issue with the firmware काष्ठा/जोड़'s.
   More permanent solution will be to refactor this include.
*/

/* Accelerator firmware inक्रमmation.
 */
काष्ठा ia_css_acc_info अणु
	u32 per_frame_data; /** Dummy क्रम now */
पूर्ण;

/* Firmware inक्रमmation.
 */
जोड़ ia_css_fw_जोड़ अणु
	काष्ठा ia_css_binary_xinfo	isp; /** ISP info */
	काष्ठा ia_css_sp_info		sp;  /** SP info */
	काष्ठा ia_css_bl_info           bl;  /** Bootloader info */
	काष्ठा ia_css_acc_info		acc; /** Accelerator info */
पूर्ण;

/* Firmware inक्रमmation.
 */
काष्ठा ia_css_fw_info अणु
	माप_प्रकार			 header_size; /** size of fw header */

	CSS_ALIGN(u32 type, 8);
	जोड़ ia_css_fw_जोड़	 info; /** Binary info */
	काष्ठा ia_css_blob_info  blob; /** Blob info */
	/* Dynamic part */
	काष्ठा ia_css_fw_info   *next;

	CSS_ALIGN(u32       loaded, 8);	/** Firmware has been loaded */
	CSS_ALIGN(स्थिर u8 *isp_code, 8);  /** ISP poपूर्णांकer to code */
	/** Firmware handle between user space and kernel */
	CSS_ALIGN(u32	handle, 8);
	/** Sections to copy from/to ISP */
	काष्ठा ia_css_isp_param_css_segments mem_initializers;
	/** Initializer क्रम local ISP memories */
पूर्ण;

काष्ठा ia_css_blob_descr अणु
	स्थिर अचिन्हित अक्षर  *blob;
	काष्ठा ia_css_fw_info header;
	स्थिर अक्षर	     *name;
	जोड़ ia_css_all_memory_offsets mem_offsets;
पूर्ण;

काष्ठा ia_css_acc_fw;

/* Structure describing the SP binary of a stand-alone accelerator.
 */
काष्ठा ia_css_acc_sp अणु
	व्योम (*init)(काष्ठा ia_css_acc_fw *);	/** init क्रम crun */
	u32 sp_prog_name_offset;		/** program name offset wrt hdr in bytes */
	u32 sp_blob_offset;		/** blob offset wrt hdr in bytes */
	व्योम	 *entry;			/** Address of sp entry poपूर्णांक */
	u32 *css_पात;			/** SP dmem पात flag */
	व्योम	 *isp_code;			/** SP dmem address holding xmem
						     address of isp code */
	काष्ठा ia_css_fw_info fw;		/** SP fw descriptor */
	स्थिर u8 *code;			/** ISP poपूर्णांकer of allocated SP code */
पूर्ण;

/* Acceleration firmware descriptor.
  * This descriptor descibes either SP code (stand-alone), or
  * ISP code (a separate pipeline stage).
  */
काष्ठा ia_css_acc_fw_hdr अणु
	क्रमागत ia_css_acc_type type;	/** Type of accelerator */
	u32	isp_prog_name_offset; /** program name offset wrt
						   header in bytes */
	u32	isp_blob_offset;      /** blob offset wrt header
						   in bytes */
	u32	isp_size;	      /** Size of isp blob */
	स्थिर u8  *isp_code;	      /** ISP poपूर्णांकer to code */
	काष्ठा ia_css_acc_sp  sp;  /** Standalone sp code */
	/** Firmware handle between user space and kernel */
	u32	handle;
	काष्ठा ia_css_data parameters; /** Current SP parameters */
पूर्ण;

/* Firmware काष्ठाure.
  * This contains the header and actual blobs.
  * For standalone, it contains SP and ISP blob.
  * For a pipeline stage accelerator, it contains ISP code only.
  * Since its members are variable size, their offsets are described in the
  * header and computed using the access macros below.
  */
काष्ठा ia_css_acc_fw अणु
	काष्ठा ia_css_acc_fw_hdr header; /** firmware header */
	/*
	पूर्णांक8_t   isp_progname[];	  **< ISP program name
	पूर्णांक8_t   sp_progname[];	  **< SP program name, stand-alone only
	uपूर्णांक8_t sp_code[];  **< SP blob, stand-alone only
	uपूर्णांक8_t isp_code[]; **< ISP blob
	*/
पूर्ण;

/* Access macros क्रम firmware */
#घोषणा IA_CSS_ACC_OFFSET(t, f, n) ((t)((uपूर्णांक8_t *)(f) + (f->header.n)))
#घोषणा IA_CSS_ACC_SP_PROG_NAME(f) IA_CSS_ACC_OFFSET(स्थिर अक्षर *, f, \
						 sp.sp_prog_name_offset)
#घोषणा IA_CSS_ACC_ISP_PROG_NAME(f) IA_CSS_ACC_OFFSET(स्थिर अक्षर *, f, \
						 isp_prog_name_offset)
#घोषणा IA_CSS_ACC_SP_CODE(f)      IA_CSS_ACC_OFFSET(uपूर्णांक8_t *, f, \
						 sp.sp_blob_offset)
#घोषणा IA_CSS_ACC_SP_DATA(f)      (IA_CSS_ACC_SP_CODE(f) + \
					(f)->header.sp.fw.blob.data_source)
#घोषणा IA_CSS_ACC_ISP_CODE(f)     IA_CSS_ACC_OFFSET(uपूर्णांक8_t*, f,\
						 isp_blob_offset)
#घोषणा IA_CSS_ACC_ISP_SIZE(f)     ((f)->header.isp_size)

/* Binary name follows header immediately */
#घोषणा IA_CSS_EXT_ISP_PROG_NAME(f)   ((स्थिर अक्षर *)(f) + (f)->blob.prog_name_offset)
#घोषणा IA_CSS_EXT_ISP_MEM_OFFSETS(f) \
	((स्थिर काष्ठा ia_css_memory_offsets *)((स्थिर अक्षर *)(f) + (f)->blob.mem_offsets))

क्रमागत ia_css_sp_sleep_mode अणु
	SP_DISABLE_SLEEP_MODE = 0,
	SP_SLEEP_AFTER_FRAME = 1 << 0,
	SP_SLEEP_AFTER_IRQ = 1 << 1
पूर्ण;
#पूर्ण_अगर /* _IA_CSS_ACC_TYPES_H */
