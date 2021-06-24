<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  sst.h - Intel SST Driver क्रम audio engine
 *
 *  Copyright (C) 2008-14 Intel Corporation
 *  Authors:	Vinod Koul <vinod.koul@पूर्णांकel.com>
 *		Harsha Priya <priya.harsha@पूर्णांकel.com>
 *		Dharageswari R <dharageswari.r@पूर्णांकel.com>
 *		KP Jeeja <jeeja.kp@पूर्णांकel.com>
 *  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 *  Common निजी declarations क्रम SST
 */
#अगर_अघोषित __SST_H__
#घोषणा __SST_H__

#समावेश <linux/firmware.h>

/* driver names */
#घोषणा SST_DRV_NAME "intel_sst_driver"
#घोषणा SST_MRFLD_PCI_ID 0x119A
#घोषणा SST_BYT_ACPI_ID	0x80860F28
#घोषणा SST_CHV_ACPI_ID	0x808622A8

#घोषणा SST_SUSPEND_DELAY 2000
#घोषणा FW_CONTEXT_MEM (64*1024)
#घोषणा SST_ICCM_BOUNDARY 4
#घोषणा SST_CONFIG_SSP_SIGN 0x7ffe8001

#घोषणा MRFLD_FW_VIRTUAL_BASE 0xC0000000
#घोषणा MRFLD_FW_DDR_BASE_OFFSET 0x0
#घोषणा MRFLD_FW_FEATURE_BASE_OFFSET 0x4
#घोषणा MRFLD_FW_BSS_RESET_BIT 0

/* SST Shim रेजिस्टर map */
#घोषणा SST_CSR			0x00
#घोषणा SST_ISRX		0x18
#घोषणा SST_IMRX		0x28
#घोषणा SST_IPCX		0x38 /* IPC IA -> SST */
#घोषणा SST_IPCD		0x40 /* IPC SST -> IA */

बाह्य स्थिर काष्ठा dev_pm_ops पूर्णांकel_sst_pm;
क्रमागत sst_states अणु
	SST_FW_LOADING = 1,
	SST_FW_RUNNING,
	SST_RESET,
	SST_SHUTDOWN,
पूर्ण;

क्रमागत sst_algo_ops अणु
	SST_SET_ALGO = 0,
	SST_GET_ALGO = 1,
पूर्ण;

#घोषणा SST_BLOCK_TIMEOUT	1000

#घोषणा FW_SIGNATURE_SIZE	4
#घोषणा FW_NAME_SIZE		32

/* stream states */
क्रमागत sst_stream_states अणु
	STREAM_UN_INIT	= 0,	/* Freed/Not used stream */
	STREAM_RUNNING	= 1,	/* Running */
	STREAM_PAUSED	= 2,	/* Paused stream */
	STREAM_INIT	= 3,	/* stream init, रुकोing क्रम data */
पूर्ण;

क्रमागत sst_ram_type अणु
	SST_IRAM	= 1,
	SST_DRAM	= 2,
	SST_DDR	= 5,
	SST_CUSTOM_INFO	= 7,	/* consists of FW binary inक्रमmation */
पूर्ण;

/* SST shim रेजिस्टरs to काष्ठाure mapping */
जोड़ पूर्णांकerrupt_reg अणु
	काष्ठा अणु
		u64 करोne_पूर्णांकerrupt:1;
		u64 busy_पूर्णांकerrupt:1;
		u64 rsvd:62;
	पूर्ण part;
	u64 full;
पूर्ण;

जोड़ sst_pisr_reg अणु
	काष्ठा अणु
		u32 pssp0:1;
		u32 pssp1:1;
		u32 rsvd0:3;
		u32 dmac:1;
		u32 rsvd1:26;
	पूर्ण part;
	u32 full;
पूर्ण;

जोड़ sst_pimr_reg अणु
	काष्ठा अणु
		u32 ssp0:1;
		u32 ssp1:1;
		u32 rsvd0:3;
		u32 dmac:1;
		u32 rsvd1:10;
		u32 ssp0_sc:1;
		u32 ssp1_sc:1;
		u32 rsvd2:3;
		u32 dmac_sc:1;
		u32 rsvd3:10;
	पूर्ण part;
	u32 full;
पूर्ण;

जोड़ config_status_reg_mrfld अणु
	काष्ठा अणु
		u64 lpe_reset:1;
		u64 lpe_reset_vector:1;
		u64 runstall:1;
		u64 pरुकोmode:1;
		u64 clk_sel:3;
		u64 rsvd2:1;
		u64 sst_clk:3;
		u64 xt_snoop:1;
		u64 rsvd3:4;
		u64 clk_sel1:6;
		u64 clk_enable:3;
		u64 rsvd4:6;
		u64 slim0baseclk:1;
		u64 rsvd:32;
	पूर्ण part;
	u64 full;
पूर्ण;

जोड़ पूर्णांकerrupt_reg_mrfld अणु
	काष्ठा अणु
		u64 करोne_पूर्णांकerrupt:1;
		u64 busy_पूर्णांकerrupt:1;
		u64 rsvd:62;
	पूर्ण part;
	u64 full;
पूर्ण;

जोड़ sst_imr_reg_mrfld अणु
	काष्ठा अणु
		u64 करोne_पूर्णांकerrupt:1;
		u64 busy_पूर्णांकerrupt:1;
		u64 rsvd:62;
	पूर्ण part;
	u64 full;
पूर्ण;

/**
 * काष्ठा sst_block - This काष्ठाure is used to block a user/fw data call to another
 * fw/user call
 *
 * @condition: condition क्रम blocking check
 * @ret_code: ret code when block is released
 * @data: data ptr
 * @size: size of data
 * @on: block condition
 * @msg_id: msg_id = msgid in mfld/ctp, mrfld = शून्य
 * @drv_id: str_id in mfld/ctp, = drv_id in mrfld
 * @node: list head node
 */
काष्ठा sst_block अणु
	bool	condition;
	पूर्णांक	ret_code;
	व्योम	*data;
	u32     size;
	bool	on;
	u32     msg_id;
	u32     drv_id;
	काष्ठा list_head node;
पूर्ण;

/**
 * काष्ठा stream_info - काष्ठाure that holds the stream inक्रमmation
 *
 * @status : stream current state
 * @prev : stream prev state
 * @resume_status : stream current state to restore on resume
 * @resume_prev : stream prev state to restore on resume
 * @lock : stream mutex क्रम protecting state
 * @alloc_param : parameters used क्रम stream (re-)allocation
 * @pcm_substream : PCM substream
 * @period_elapsed : PCM period elapsed callback
 * @sfreq : stream sampling freq
 * @cumm_bytes : cummulative bytes decoded
 */
काष्ठा stream_info अणु
	अचिन्हित पूर्णांक		status;
	अचिन्हित पूर्णांक		prev;
	अचिन्हित पूर्णांक		resume_status;
	अचिन्हित पूर्णांक		resume_prev;
	काष्ठा mutex		lock;
	काष्ठा snd_sst_alloc_mrfld alloc_param;

	व्योम			*pcm_substream;
	व्योम (*period_elapsed)(व्योम *pcm_substream);

	अचिन्हित पूर्णांक		sfreq;
	u32			cumm_bytes;

	व्योम			*compr_cb_param;
	व्योम (*compr_cb)(व्योम *compr_cb_param);

	व्योम			*drain_cb_param;
	व्योम (*drain_notअगरy)(व्योम *drain_cb_param);

	अचिन्हित पूर्णांक		num_ch;
	अचिन्हित पूर्णांक		pipe_id;
	अचिन्हित पूर्णांक		task_id;
पूर्ण;

#घोषणा SST_FW_SIGN "$SST"
#घोषणा SST_FW_LIB_SIGN "$LIB"

/**
 * काष्ठा sst_fw_header - FW file headers
 *
 * @signature : FW signature
 * @file_size: size of fw image
 * @modules : # of modules
 * @file_क्रमmat : version of header क्रमmat
 * @reserved : reserved fields
 */
काष्ठा sst_fw_header अणु
	अचिन्हित अक्षर signature[FW_SIGNATURE_SIZE];
	u32 file_size;
	u32 modules;
	u32 file_क्रमmat;
	u32 reserved[4];
पूर्ण;

/**
 * काष्ठा fw_module_header - module header in FW
 *
 * @signature: module signature
 * @mod_size: size of module
 * @blocks: block count
 * @type: block type
 * @entry_poपूर्णांक: module netry poपूर्णांक
 */
काष्ठा fw_module_header अणु
	अचिन्हित अक्षर signature[FW_SIGNATURE_SIZE];
	u32 mod_size;
	u32 blocks;
	u32 type;
	u32 entry_poपूर्णांक;
पूर्ण;

/**
 * काष्ठा fw_block_info - block header क्रम FW
 *
 * @type: block ram type I/D
 * @size: size of block
 * @ram_offset: offset in ram
 */
काष्ठा fw_block_info अणु
	क्रमागत sst_ram_type	type;
	u32			size;
	u32			ram_offset;
	u32			rsvd;
पूर्ण;

काष्ठा sst_runसमय_param अणु
	काष्ठा snd_sst_runसमय_params param;
पूर्ण;

काष्ठा sst_sg_list अणु
	काष्ठा scatterlist *src;
	काष्ठा scatterlist *dst;
	पूर्णांक list_len;
	अचिन्हित पूर्णांक sg_idx;
पूर्ण;

काष्ठा sst_स_नकल_list अणु
	काष्ठा list_head स_नकलlist;
	व्योम *dstn;
	स्थिर व्योम *src;
	u32 size;
	bool is_io;
पूर्ण;

/*Firmware Module Inक्रमmation*/
क्रमागत sst_lib_dwnld_status अणु
	SST_LIB_NOT_FOUND = 0,
	SST_LIB_FOUND,
	SST_LIB_DOWNLOADED,
पूर्ण;

काष्ठा sst_module_info अणु
	स्थिर अक्षर *name; /*Library name*/
	u32	id; /*Module ID*/
	u32	entry_pt; /*Module entry poपूर्णांक*/
	u8	status; /*module status*/
	u8	rsvd1;
	u16	rsvd2;
पूर्ण;

/*
 * Structure क्रम managing the Library Region(1.5MB)
 * in DDR in Merrअगरield
 */
काष्ठा sst_mem_mgr अणु
	phys_addr_t current_base;
	पूर्णांक avail;
	अचिन्हित पूर्णांक count;
पूर्ण;

काष्ठा sst_ipc_reg अणु
	पूर्णांक ipcx;
	पूर्णांक ipcd;
पूर्ण;

काष्ठा sst_fw_save अणु
	व्योम *iram;	/* allocated via kvदो_स्मृति() */
	व्योम *dram;	/* allocated via kvदो_स्मृति() */
	व्योम *sram;	/* allocated via kvदो_स्मृति() */
	व्योम *ddr;	/* allocated via kvदो_स्मृति() */
पूर्ण;

/**
 * काष्ठा पूर्णांकel_sst_drv - driver ops
 *
 * @sst_state : current sst device state
 * @dev_id : device identअगरier, pci_id क्रम pci devices and acpi_id क्रम acpi
 * 	     devices
 * @shim : SST shim poपूर्णांकer
 * @mailbox : SST mailbox poपूर्णांकer
 * @iram : SST IRAM poपूर्णांकer
 * @dram : SST DRAM poपूर्णांकer
 * @pdata : SST info passed as a part of pci platक्रमm data
 * @shim_phy_add : SST shim phy addr
 * @ipc_dispatch_list : ipc messages dispatched
 * @rx_list : to copy the process_reply/process_msg from DSP
 * @ipc_post_msg_wq : wq to post IPC messages context
 * @mad_ops : MAD driver operations रेजिस्टरed
 * @mad_wq : MAD driver wq
 * @post_msg_wq : wq to post IPC messages
 * @streams : sst stream contexts
 * @list_lock : sst driver list lock (deprecated)
 * @ipc_spin_lock : spin lock to handle audio shim access and ipc queue
 * @block_lock : spin lock to add block to block_list and assign pvt_id
 * @rx_msg_lock : spin lock to handle the rx messages from the DSP
 * @scard_ops : sst card ops
 * @pci : sst pci device struture
 * @dev : poपूर्णांकer to current device काष्ठा
 * @sst_lock : sst device lock
 * @pvt_id : sst निजी id
 * @stream_cnt : total sst active stream count
 * @pb_streams : total active pb streams
 * @cp_streams : total active cp streams
 * @audio_start : audio status
 * @qos		: PM Qos काष्ठा
 * firmware_name : Firmware / Library name
 */
काष्ठा पूर्णांकel_sst_drv अणु
	पूर्णांक			sst_state;
	पूर्णांक			irq_num;
	अचिन्हित पूर्णांक		dev_id;
	व्योम __iomem		*ddr;
	व्योम __iomem		*shim;
	व्योम __iomem		*mailbox;
	व्योम __iomem		*iram;
	व्योम __iomem		*dram;
	अचिन्हित पूर्णांक		mailbox_add;
	अचिन्हित पूर्णांक		iram_base;
	अचिन्हित पूर्णांक		dram_base;
	अचिन्हित पूर्णांक		shim_phy_add;
	अचिन्हित पूर्णांक		iram_end;
	अचिन्हित पूर्णांक		dram_end;
	अचिन्हित पूर्णांक		ddr_end;
	अचिन्हित पूर्णांक		ddr_base;
	अचिन्हित पूर्णांक		mailbox_recv_offset;
	काष्ठा list_head        block_list;
	काष्ठा list_head	ipc_dispatch_list;
	काष्ठा sst_platक्रमm_info *pdata;
	काष्ठा list_head	rx_list;
	काष्ठा work_काष्ठा      ipc_post_msg_wq;
	रुको_queue_head_t	रुको_queue;
	काष्ठा workqueue_काष्ठा *post_msg_wq;
	अचिन्हित पूर्णांक		tstamp;
	/* str_id 0 is not used */
	काष्ठा stream_info	streams[MAX_NUM_STREAMS+1];
	spinlock_t		ipc_spin_lock;
	spinlock_t              block_lock;
	spinlock_t		rx_msg_lock;
	काष्ठा pci_dev		*pci;
	काष्ठा device		*dev;
	अस्थिर दीर्घ अचिन्हित 		pvt_id;
	काष्ठा mutex            sst_lock;
	अचिन्हित पूर्णांक		stream_cnt;
	अचिन्हित पूर्णांक		csr_value;
	व्योम			*fw_in_mem;
	काष्ठा sst_sg_list	fw_sg_list, library_list;
	काष्ठा पूर्णांकel_sst_ops	*ops;
	काष्ठा sst_info		info;
	काष्ठा pm_qos_request	*qos;
	अचिन्हित पूर्णांक		use_dma;
	अचिन्हित पूर्णांक		use_lli;
	atomic_t		fw_clear_context;
	bool			lib_dwnld_reqd;
	काष्ठा list_head	स_नकल_list;
	काष्ठा sst_ipc_reg	ipc_reg;
	काष्ठा sst_mem_mgr      lib_mem_mgr;
	/*
	 * Holder क्रम firmware name. Due to async call it needs to be
	 * persistent till worker thपढ़ो माला_लो called
	 */
	अक्षर firmware_name[FW_NAME_SIZE];

	काष्ठा snd_sst_fw_version fw_version;
	काष्ठा sst_fw_save	*fw_save;
पूर्ण;

/* misc definitions */
#घोषणा FW_DWNL_ID 0x01

काष्ठा पूर्णांकel_sst_ops अणु
	irqवापस_t (*पूर्णांकerrupt)(पूर्णांक, व्योम *);
	irqवापस_t (*irq_thपढ़ो)(पूर्णांक, व्योम *);
	व्योम (*clear_पूर्णांकerrupt)(काष्ठा पूर्णांकel_sst_drv *ctx);
	पूर्णांक (*start)(काष्ठा पूर्णांकel_sst_drv *ctx);
	पूर्णांक (*reset)(काष्ठा पूर्णांकel_sst_drv *ctx);
	व्योम (*process_reply)(काष्ठा पूर्णांकel_sst_drv *ctx, काष्ठा ipc_post *msg);
	पूर्णांक (*post_message)(काष्ठा पूर्णांकel_sst_drv *ctx,
			काष्ठा ipc_post *msg, bool sync);
	व्योम (*process_message)(काष्ठा ipc_post *msg);
	व्योम (*set_bypass)(bool set);
	पूर्णांक (*save_dsp_context)(काष्ठा पूर्णांकel_sst_drv *sst);
	व्योम (*restore_dsp_context)(व्योम);
	पूर्णांक (*alloc_stream)(काष्ठा पूर्णांकel_sst_drv *ctx, व्योम *params);
	व्योम (*post_करोwnload)(काष्ठा पूर्णांकel_sst_drv *sst);
पूर्ण;

पूर्णांक sst_पुनः_स्मृति_stream(काष्ठा पूर्णांकel_sst_drv *sst_drv_ctx, पूर्णांक str_id);
पूर्णांक sst_छोड़ो_stream(काष्ठा पूर्णांकel_sst_drv *sst_drv_ctx, पूर्णांक str_id);
पूर्णांक sst_resume_stream(काष्ठा पूर्णांकel_sst_drv *sst_drv_ctx, पूर्णांक str_id);
पूर्णांक sst_drop_stream(काष्ठा पूर्णांकel_sst_drv *sst_drv_ctx, पूर्णांक str_id);
पूर्णांक sst_मुक्त_stream(काष्ठा पूर्णांकel_sst_drv *sst_drv_ctx, पूर्णांक str_id);
पूर्णांक sst_start_stream(काष्ठा पूर्णांकel_sst_drv *sst_drv_ctx, पूर्णांक str_id);
पूर्णांक sst_send_byte_stream_mrfld(काष्ठा पूर्णांकel_sst_drv *sst_drv_ctx,
			काष्ठा snd_sst_bytes_v2 *bytes);
पूर्णांक sst_set_stream_param(पूर्णांक str_id, काष्ठा snd_sst_params *str_param);
पूर्णांक sst_set_metadata(पूर्णांक str_id, अक्षर *params);
पूर्णांक sst_get_stream(काष्ठा पूर्णांकel_sst_drv *ctx,
		काष्ठा snd_sst_params *str_param);
पूर्णांक sst_get_stream_allocated(काष्ठा पूर्णांकel_sst_drv *ctx,
		काष्ठा snd_sst_params *str_param,
		काष्ठा snd_sst_lib_करोwnload **lib_dnld);
पूर्णांक sst_drain_stream(काष्ठा पूर्णांकel_sst_drv *sst_drv_ctx,
		पूर्णांक str_id, bool partial_drain);
पूर्णांक sst_post_message_mrfld(काष्ठा पूर्णांकel_sst_drv *sst_drv_ctx,
		काष्ठा ipc_post *ipc_msg, bool sync);
व्योम sst_process_reply_mrfld(काष्ठा पूर्णांकel_sst_drv *sst_drv_ctx, काष्ठा ipc_post *msg);
पूर्णांक sst_start_mrfld(काष्ठा पूर्णांकel_sst_drv *sst_drv_ctx);
पूर्णांक पूर्णांकel_sst_reset_dsp_mrfld(काष्ठा पूर्णांकel_sst_drv *sst_drv_ctx);
व्योम पूर्णांकel_sst_clear_पूर्णांकr_mrfld(काष्ठा पूर्णांकel_sst_drv *sst_drv_ctx);

पूर्णांक sst_load_fw(काष्ठा पूर्णांकel_sst_drv *sst_drv_ctx);
पूर्णांक sst_load_library(काष्ठा snd_sst_lib_करोwnload *lib, u8 ops);
व्योम sst_post_करोwnload_mrfld(काष्ठा पूर्णांकel_sst_drv *ctx);
पूर्णांक sst_get_block_stream(काष्ठा पूर्णांकel_sst_drv *sst_drv_ctx);
व्योम sst_स_नकल_मुक्त_resources(काष्ठा पूर्णांकel_sst_drv *sst_drv_ctx);

पूर्णांक sst_रुको_पूर्णांकerruptible(काष्ठा पूर्णांकel_sst_drv *sst_drv_ctx,
				काष्ठा sst_block *block);
पूर्णांक sst_रुको_समयout(काष्ठा पूर्णांकel_sst_drv *sst_drv_ctx,
			काष्ठा sst_block *block);
पूर्णांक sst_create_ipc_msg(काष्ठा ipc_post **arg, bool large);
पूर्णांक मुक्त_stream_context(काष्ठा पूर्णांकel_sst_drv *ctx, अचिन्हित पूर्णांक str_id);
व्योम sst_clean_stream(काष्ठा stream_info *stream);
पूर्णांक पूर्णांकel_sst_रेजिस्टर_compress(काष्ठा पूर्णांकel_sst_drv *sst);
पूर्णांक पूर्णांकel_sst_हटाओ_compress(काष्ठा पूर्णांकel_sst_drv *sst);
व्योम sst_cdev_fragment_elapsed(काष्ठा पूर्णांकel_sst_drv *ctx, पूर्णांक str_id);
पूर्णांक sst_send_sync_msg(पूर्णांक ipc, पूर्णांक str_id);
पूर्णांक sst_get_num_channel(काष्ठा snd_sst_params *str_param);
पूर्णांक sst_get_sfreq(काष्ठा snd_sst_params *str_param);
पूर्णांक sst_alloc_stream_mrfld(काष्ठा पूर्णांकel_sst_drv *sst_drv_ctx, व्योम *params);
व्योम sst_restore_fw_context(व्योम);
काष्ठा sst_block *sst_create_block(काष्ठा पूर्णांकel_sst_drv *ctx,
				u32 msg_id, u32 drv_id);
पूर्णांक sst_create_block_and_ipc_msg(काष्ठा ipc_post **arg, bool large,
		काष्ठा पूर्णांकel_sst_drv *sst_drv_ctx, काष्ठा sst_block **block,
		u32 msg_id, u32 drv_id);
पूर्णांक sst_मुक्त_block(काष्ठा पूर्णांकel_sst_drv *ctx, काष्ठा sst_block *मुक्तd);
पूर्णांक sst_wake_up_block(काष्ठा पूर्णांकel_sst_drv *ctx, पूर्णांक result,
		u32 drv_id, u32 ipc, व्योम *data, u32 size);
पूर्णांक sst_request_firmware_async(काष्ठा पूर्णांकel_sst_drv *ctx);
पूर्णांक sst_driver_ops(काष्ठा पूर्णांकel_sst_drv *sst);
काष्ठा sst_platक्रमm_info *sst_get_acpi_driver_data(स्थिर अक्षर *hid);
व्योम sst_firmware_load_cb(स्थिर काष्ठा firmware *fw, व्योम *context);
पूर्णांक sst_prepare_and_post_msg(काष्ठा पूर्णांकel_sst_drv *sst,
		पूर्णांक task_id, पूर्णांक ipc_msg, पूर्णांक cmd_id, पूर्णांक pipe_id,
		माप_प्रकार mbox_data_len, स्थिर व्योम *mbox_data, व्योम **data,
		bool large, bool fill_dsp, bool sync, bool response);

व्योम sst_process_pending_msg(काष्ठा work_काष्ठा *work);
पूर्णांक sst_assign_pvt_id(काष्ठा पूर्णांकel_sst_drv *drv);
पूर्णांक sst_validate_strid(काष्ठा पूर्णांकel_sst_drv *sst_drv_ctx, पूर्णांक str_id);
काष्ठा stream_info *get_stream_info(काष्ठा पूर्णांकel_sst_drv *sst_drv_ctx,
		पूर्णांक str_id);
पूर्णांक get_stream_id_mrfld(काष्ठा पूर्णांकel_sst_drv *sst_drv_ctx,
		u32 pipe_id);
u32 relocate_imr_addr_mrfld(u32 base_addr);
व्योम sst_add_to_dispatch_list_and_post(काष्ठा पूर्णांकel_sst_drv *sst,
					काष्ठा ipc_post *msg);
पूर्णांक sst_pm_runसमय_put(काष्ठा पूर्णांकel_sst_drv *sst_drv);
पूर्णांक sst_shim_ग_लिखो(व्योम __iomem *addr, पूर्णांक offset, पूर्णांक value);
u32 sst_shim_पढ़ो(व्योम __iomem *addr, पूर्णांक offset);
u64 sst_reg_पढ़ो64(व्योम __iomem *addr, पूर्णांक offset);
पूर्णांक sst_shim_ग_लिखो64(व्योम __iomem *addr, पूर्णांक offset, u64 value);
u64 sst_shim_पढ़ो64(व्योम __iomem *addr, पूर्णांक offset);
व्योम sst_set_fw_state_locked(
		काष्ठा पूर्णांकel_sst_drv *sst_drv_ctx, पूर्णांक sst_state);
व्योम sst_fill_header_mrfld(जोड़ ipc_header_mrfld *header,
				पूर्णांक msg, पूर्णांक task_id, पूर्णांक large, पूर्णांक drv_id);
व्योम sst_fill_header_dsp(काष्ठा ipc_dsp_hdr *dsp, पूर्णांक msg,
					पूर्णांक pipe_id, पूर्णांक len);

पूर्णांक sst_रेजिस्टर(काष्ठा device *);
पूर्णांक sst_unरेजिस्टर(काष्ठा device *);

पूर्णांक sst_alloc_drv_context(काष्ठा पूर्णांकel_sst_drv **ctx,
		काष्ठा device *dev, अचिन्हित पूर्णांक dev_id);
पूर्णांक sst_context_init(काष्ठा पूर्णांकel_sst_drv *ctx);
व्योम sst_context_cleanup(काष्ठा पूर्णांकel_sst_drv *ctx);
व्योम sst_configure_runसमय_pm(काष्ठा पूर्णांकel_sst_drv *ctx);
व्योम स_नकल32_toio(व्योम __iomem *dst, स्थिर व्योम *src, पूर्णांक count);
व्योम स_नकल32_fromio(व्योम *dst, स्थिर व्योम __iomem *src, पूर्णांक count);

#पूर्ण_अगर
