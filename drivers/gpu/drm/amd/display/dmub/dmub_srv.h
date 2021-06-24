<शैली गुरु>
/*
 * Copyright 2019 Advanced Micro Devices, Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Authors: AMD
 *
 */

#अगर_अघोषित _DMUB_SRV_H_
#घोषणा _DMUB_SRV_H_

/**
 * DOC: DMUB पूर्णांकerface and operation
 *
 * DMUB is the पूर्णांकerface to the display DMCUB microcontroller on DCN hardware.
 * It delegates hardware initialization and command submission to the
 * microcontroller. DMUB is the लघुname क्रम DMCUB.
 *
 * This पूर्णांकerface is not thपढ़ो-safe. Ensure that all access to the पूर्णांकerface
 * is properly synchronized by the caller.
 *
 * Initialization and usage of the DMUB service should be करोne in the
 * steps given below:
 *
 * 1. dmub_srv_create()
 * 2. dmub_srv_has_hw_support()
 * 3. dmub_srv_calc_region_info()
 * 4. dmub_srv_hw_init()
 *
 * The call to dmub_srv_create() is required to use the server.
 *
 * The calls to dmub_srv_has_hw_support() and dmub_srv_calc_region_info()
 * are helpers to query cache winकरोw size and allocate framebuffer(s)
 * क्रम the cache winकरोws.
 *
 * The call to dmub_srv_hw_init() programs the DMCUB रेजिस्टरs to prepare
 * क्रम command submission. Commands can be queued via dmub_srv_cmd_queue()
 * and executed via dmub_srv_cmd_execute().
 *
 * If the queue is full the dmub_srv_रुको_क्रम_idle() call can be used to
 * रुको until the queue has been cleared.
 *
 * Destroying the DMUB service can be करोne by calling dmub_srv_destroy().
 * This करोes not clear DMUB hardware state, only software state.
 *
 * The पूर्णांकerface is पूर्णांकended to be standalone and should not depend on any
 * other component within DAL.
 */

#समावेश "inc/dmub_cmd.h"

#अगर defined(__cplusplus)
बाह्य "C" अणु
#पूर्ण_अगर

/* Forward declarations */
काष्ठा dmub_srv;
काष्ठा dmub_srv_common_regs;

काष्ठा dmcub_trace_buf_entry;

/* क्रमागत dmub_status - वापस code क्रम dmcub functions */
क्रमागत dmub_status अणु
	DMUB_STATUS_OK = 0,
	DMUB_STATUS_NO_CTX,
	DMUB_STATUS_QUEUE_FULL,
	DMUB_STATUS_TIMEOUT,
	DMUB_STATUS_INVALID,
पूर्ण;

/* क्रमागत dmub_asic - dmub asic identअगरier */
क्रमागत dmub_asic अणु
	DMUB_ASIC_NONE = 0,
	DMUB_ASIC_DCN20,
	DMUB_ASIC_DCN21,
	DMUB_ASIC_DCN30,
	DMUB_ASIC_DCN301,
	DMUB_ASIC_DCN302,
	DMUB_ASIC_MAX,
पूर्ण;

/* क्रमागत dmub_winकरोw_id - dmub winकरोw identअगरier */
क्रमागत dmub_winकरोw_id अणु
	DMUB_WINDOW_0_INST_CONST = 0,
	DMUB_WINDOW_1_STACK,
	DMUB_WINDOW_2_BSS_DATA,
	DMUB_WINDOW_3_VBIOS,
	DMUB_WINDOW_4_MAILBOX,
	DMUB_WINDOW_5_TRACEBUFF,
	DMUB_WINDOW_6_FW_STATE,
	DMUB_WINDOW_7_SCRATCH_MEM,
	DMUB_WINDOW_TOTAL,
पूर्ण;

/* क्रमागत dmub_notअगरication_type - dmub outbox notअगरication identअगरier */
क्रमागत dmub_notअगरication_type अणु
	DMUB_NOTIFICATION_NO_DATA = 0,
	DMUB_NOTIFICATION_AUX_REPLY,
	DMUB_NOTIFICATION_HPD,
	DMUB_NOTIFICATION_HPD_IRQ,
	DMUB_NOTIFICATION_MAX
पूर्ण;

/**
 * काष्ठा dmub_region - dmub hw memory region
 * @base: base address क्रम region, must be 256 byte aligned
 * @top: top address क्रम region
 */
काष्ठा dmub_region अणु
	uपूर्णांक32_t base;
	uपूर्णांक32_t top;
पूर्ण;

/**
 * काष्ठा dmub_winकरोw - dmub hw cache winकरोw
 * @off: offset to the fb memory in gpu address space
 * @r: region in uc address space क्रम cache winकरोw
 */
काष्ठा dmub_winकरोw अणु
	जोड़ dmub_addr offset;
	काष्ठा dmub_region region;
पूर्ण;

/**
 * काष्ठा dmub_fb - defines a dmub framebuffer memory region
 * @cpu_addr: cpu भव address क्रम the region, शून्य अगर invalid
 * @gpu_addr: gpu भव address क्रम the region, शून्य अगर invalid
 * @size: size of the region in bytes, zero अगर invalid
 */
काष्ठा dmub_fb अणु
	व्योम *cpu_addr;
	uपूर्णांक64_t gpu_addr;
	uपूर्णांक32_t size;
पूर्ण;

/**
 * काष्ठा dmub_srv_region_params - params used क्रम calculating dmub regions
 * @inst_स्थिर_size: size of the fw inst स्थिर section
 * @bss_data_size: size of the fw bss data section
 * @vbios_size: size of the vbios data
 * @fw_bss_data: raw firmware bss data section
 */
काष्ठा dmub_srv_region_params अणु
	uपूर्णांक32_t inst_स्थिर_size;
	uपूर्णांक32_t bss_data_size;
	uपूर्णांक32_t vbios_size;
	स्थिर uपूर्णांक8_t *fw_inst_स्थिर;
	स्थिर uपूर्णांक8_t *fw_bss_data;
पूर्ण;

/**
 * काष्ठा dmub_srv_region_info - output region info from the dmub service
 * @fb_size: required minimum fb size क्रम all regions, aligned to 4096 bytes
 * @num_regions: number of regions used by the dmub service
 * @regions: region info
 *
 * The regions are aligned such that they can be all placed within the
 * same framebuffer but they can also be placed पूर्णांकo dअगरferent framebuffers.
 *
 * The size of each region can be calculated by the caller:
 * size = reg.top - reg.base
 *
 * Care must be taken when perक्रमming custom allocations to ensure that each
 * region base address is 256 byte aligned.
 */
काष्ठा dmub_srv_region_info अणु
	uपूर्णांक32_t fb_size;
	uपूर्णांक8_t num_regions;
	काष्ठा dmub_region regions[DMUB_WINDOW_TOTAL];
पूर्ण;

/**
 * काष्ठा dmub_srv_fb_params - parameters used क्रम driver fb setup
 * @region_info: region info calculated by dmub service
 * @cpu_addr: base cpu address क्रम the framebuffer
 * @gpu_addr: base gpu भव address क्रम the framebuffer
 */
काष्ठा dmub_srv_fb_params अणु
	स्थिर काष्ठा dmub_srv_region_info *region_info;
	व्योम *cpu_addr;
	uपूर्णांक64_t gpu_addr;
पूर्ण;

/**
 * काष्ठा dmub_srv_fb_info - output fb info from the dmub service
 * @num_fbs: number of required dmub framebuffers
 * @fbs: fb data क्रम each region
 *
 * Output from the dmub service helper that can be used by the
 * driver to prepare dmub_fb that can be passed पूर्णांकo the dmub
 * hw init service.
 *
 * Assumes that all regions are within the same framebuffer
 * and have been setup according to the region_info generated
 * by the dmub service.
 */
काष्ठा dmub_srv_fb_info अणु
	uपूर्णांक8_t num_fb;
	काष्ठा dmub_fb fb[DMUB_WINDOW_TOTAL];
पूर्ण;

/**
 * काष्ठा dmub_srv_base_funcs - Driver specअगरic base callbacks
 */
काष्ठा dmub_srv_base_funcs अणु
	/**
	 * @reg_पढ़ो:
	 *
	 * Hook क्रम पढ़ोing a रेजिस्टर.
	 *
	 * Return: The 32-bit रेजिस्टर value from the given address.
	 */
	uपूर्णांक32_t (*reg_पढ़ो)(व्योम *ctx, uपूर्णांक32_t address);

	/**
	 * @reg_ग_लिखो:
	 *
	 * Hook क्रम writing a value to the रेजिस्टर specअगरied by address.
	 */
	व्योम (*reg_ग_लिखो)(व्योम *ctx, uपूर्णांक32_t address, uपूर्णांक32_t value);
पूर्ण;

/**
 * काष्ठा dmub_srv_hw_funcs - hardware sequencer funcs क्रम dmub
 */
काष्ठा dmub_srv_hw_funcs अणु
	/* निजी: पूर्णांकernal use only */

	व्योम (*init)(काष्ठा dmub_srv *dmub);

	व्योम (*reset)(काष्ठा dmub_srv *dmub);

	व्योम (*reset_release)(काष्ठा dmub_srv *dmub);

	व्योम (*backकरोor_load)(काष्ठा dmub_srv *dmub,
			      स्थिर काष्ठा dmub_winकरोw *cw0,
			      स्थिर काष्ठा dmub_winकरोw *cw1);

	व्योम (*setup_winकरोws)(काष्ठा dmub_srv *dmub,
			      स्थिर काष्ठा dmub_winकरोw *cw2,
			      स्थिर काष्ठा dmub_winकरोw *cw3,
			      स्थिर काष्ठा dmub_winकरोw *cw4,
			      स्थिर काष्ठा dmub_winकरोw *cw5,
			      स्थिर काष्ठा dmub_winकरोw *cw6);

	व्योम (*setup_mailbox)(काष्ठा dmub_srv *dmub,
			      स्थिर काष्ठा dmub_region *inbox1);

	uपूर्णांक32_t (*get_inbox1_rptr)(काष्ठा dmub_srv *dmub);

	व्योम (*set_inbox1_wptr)(काष्ठा dmub_srv *dmub, uपूर्णांक32_t wptr_offset);

	व्योम (*setup_out_mailbox)(काष्ठा dmub_srv *dmub,
			      स्थिर काष्ठा dmub_region *outbox1);

	uपूर्णांक32_t (*get_outbox1_wptr)(काष्ठा dmub_srv *dmub);

	व्योम (*set_outbox1_rptr)(काष्ठा dmub_srv *dmub, uपूर्णांक32_t rptr_offset);

	व्योम (*setup_outbox0)(काष्ठा dmub_srv *dmub,
			      स्थिर काष्ठा dmub_region *outbox0);

	uपूर्णांक32_t (*get_outbox0_wptr)(काष्ठा dmub_srv *dmub);

	व्योम (*set_outbox0_rptr)(काष्ठा dmub_srv *dmub, uपूर्णांक32_t rptr_offset);

	uपूर्णांक32_t (*emul_get_inbox1_rptr)(काष्ठा dmub_srv *dmub);

	व्योम (*emul_set_inbox1_wptr)(काष्ठा dmub_srv *dmub, uपूर्णांक32_t wptr_offset);

	bool (*is_supported)(काष्ठा dmub_srv *dmub);

	bool (*is_hw_init)(काष्ठा dmub_srv *dmub);

	bool (*is_phy_init)(काष्ठा dmub_srv *dmub);
	व्योम (*enable_dmub_boot_options)(काष्ठा dmub_srv *dmub);

	व्योम (*skip_dmub_panel_घातer_sequence)(काष्ठा dmub_srv *dmub, bool skip);

	जोड़ dmub_fw_boot_status (*get_fw_status)(काष्ठा dmub_srv *dmub);


	व्योम (*set_gpपूर्णांक)(काष्ठा dmub_srv *dmub,
			  जोड़ dmub_gpपूर्णांक_data_रेजिस्टर reg);

	bool (*is_gpपूर्णांक_acked)(काष्ठा dmub_srv *dmub,
			       जोड़ dmub_gpपूर्णांक_data_रेजिस्टर reg);

	uपूर्णांक32_t (*get_gpपूर्णांक_response)(काष्ठा dmub_srv *dmub);

पूर्ण;

/**
 * काष्ठा dmub_srv_create_params - params क्रम dmub service creation
 * @base_funcs: driver supplied base routines
 * @hw_funcs: optional overrides क्रम hw funcs
 * @user_ctx: context data क्रम callback funcs
 * @asic: driver supplied asic
 * @fw_version: the current firmware version, अगर any
 * @is_भव: false क्रम hw support only
 */
काष्ठा dmub_srv_create_params अणु
	काष्ठा dmub_srv_base_funcs funcs;
	काष्ठा dmub_srv_hw_funcs *hw_funcs;
	व्योम *user_ctx;
	क्रमागत dmub_asic asic;
	uपूर्णांक32_t fw_version;
	bool is_भव;
पूर्ण;

/*
 * काष्ठा dmub_srv_hw_params - params क्रम dmub hardware initialization
 * @fb: framebuffer info क्रम each region
 * @fb_base: base of the framebuffer aperture
 * @fb_offset: offset of the framebuffer aperture
 * @psp_version: psp version to pass क्रम DMCU init
 * @load_inst_स्थिर: true अगर DMUB should load inst स्थिर fw
 */
काष्ठा dmub_srv_hw_params अणु
	काष्ठा dmub_fb *fb[DMUB_WINDOW_TOTAL];
	uपूर्णांक64_t fb_base;
	uपूर्णांक64_t fb_offset;
	uपूर्णांक32_t psp_version;
	bool load_inst_स्थिर;
	bool skip_panel_घातer_sequence;
पूर्ण;

/**
 * काष्ठा dmub_srv - software state क्रम dmcub
 * @asic: dmub asic identअगरier
 * @user_ctx: user provided context क्रम the dmub_srv
 * @fw_version: the current firmware version, अगर any
 * @is_भव: false अगर hardware support only
 * @fw_state: dmub firmware state poपूर्णांकer
 */
काष्ठा dmub_srv अणु
	क्रमागत dmub_asic asic;
	व्योम *user_ctx;
	uपूर्णांक32_t fw_version;
	bool is_भव;
	काष्ठा dmub_fb scratch_mem_fb;
	अस्थिर स्थिर काष्ठा dmub_fw_state *fw_state;

	/* निजी: पूर्णांकernal use only */
	स्थिर काष्ठा dmub_srv_common_regs *regs;

	काष्ठा dmub_srv_base_funcs funcs;
	काष्ठा dmub_srv_hw_funcs hw_funcs;
	काष्ठा dmub_rb inbox1_rb;
	/**
	 * outbox1_rb is accessed without locks (dal & dc)
	 * and to be used only in dmub_srv_stat_get_notअगरication()
	 */
	काष्ठा dmub_rb outbox1_rb;

	काष्ठा dmub_rb outbox0_rb;

	bool sw_init;
	bool hw_init;

	uपूर्णांक64_t fb_base;
	uपूर्णांक64_t fb_offset;
	uपूर्णांक32_t psp_version;

	/* Feature capabilities reported by fw */
	काष्ठा dmub_feature_caps feature_caps;
पूर्ण;

/**
 * काष्ठा dmub_notअगरication - dmub notअगरication data
 * @type: dmub notअगरication type
 * @link_index: link index to identअगरy aux connection
 * @result: USB4 status वापसed from dmub
 * @pending_notअगरication: Indicates there are other pending notअगरications
 * @aux_reply: aux reply
 * @hpd_status: hpd status
 */
काष्ठा dmub_notअगरication अणु
	क्रमागत dmub_notअगरication_type type;
	uपूर्णांक8_t link_index;
	uपूर्णांक8_t result;
	bool pending_notअगरication;
	जोड़ अणु
		काष्ठा aux_reply_data aux_reply;
		क्रमागत dp_hpd_status hpd_status;
	पूर्ण;
पूर्ण;

/**
 * DMUB firmware version helper macro - useful क्रम checking अगर the version
 * of a firmware to know अगर feature or functionality is supported or present.
 */
#घोषणा DMUB_FW_VERSION(major, minor, revision) \
	((((major) & 0xFF) << 24) | (((minor) & 0xFF) << 16) | ((revision) & 0xFFFF))

/**
 * dmub_srv_create() - creates the DMUB service.
 * @dmub: the dmub service
 * @params: creation parameters क्रम the service
 *
 * Return:
 *   DMUB_STATUS_OK - success
 *   DMUB_STATUS_INVALID - unspecअगरied error
 */
क्रमागत dmub_status dmub_srv_create(काष्ठा dmub_srv *dmub,
				 स्थिर काष्ठा dmub_srv_create_params *params);

/**
 * dmub_srv_destroy() - destroys the DMUB service.
 * @dmub: the dmub service
 */
व्योम dmub_srv_destroy(काष्ठा dmub_srv *dmub);

/**
 * dmub_srv_calc_region_info() - retreives region info from the dmub service
 * @dmub: the dmub service
 * @params: parameters used to calculate region locations
 * @info_out: the output region info from dmub
 *
 * Calculates the base and top address क्रम all relevant dmub regions
 * using the parameters given (अगर any).
 *
 * Return:
 *   DMUB_STATUS_OK - success
 *   DMUB_STATUS_INVALID - unspecअगरied error
 */
क्रमागत dmub_status
dmub_srv_calc_region_info(काष्ठा dmub_srv *dmub,
			  स्थिर काष्ठा dmub_srv_region_params *params,
			  काष्ठा dmub_srv_region_info *out);

/**
 * dmub_srv_calc_region_info() - retreives fb info from the dmub service
 * @dmub: the dmub service
 * @params: parameters used to calculate fb locations
 * @info_out: the output fb info from dmub
 *
 * Calculates the base and top address क्रम all relevant dmub regions
 * using the parameters given (अगर any).
 *
 * Return:
 *   DMUB_STATUS_OK - success
 *   DMUB_STATUS_INVALID - unspecअगरied error
 */
क्रमागत dmub_status dmub_srv_calc_fb_info(काष्ठा dmub_srv *dmub,
				       स्थिर काष्ठा dmub_srv_fb_params *params,
				       काष्ठा dmub_srv_fb_info *out);

/**
 * dmub_srv_has_hw_support() - वापसs hw support state क्रम dmcub
 * @dmub: the dmub service
 * @is_supported: hw support state
 *
 * Queries the hardware क्रम DMCUB support and वापसs the result.
 *
 * Can be called beक्रमe dmub_srv_hw_init().
 *
 * Return:
 *   DMUB_STATUS_OK - success
 *   DMUB_STATUS_INVALID - unspecअगरied error
 */
क्रमागत dmub_status dmub_srv_has_hw_support(काष्ठा dmub_srv *dmub,
					 bool *is_supported);

/**
 * dmub_srv_is_hw_init() - वापसs hardware init state
 *
 * Return:
 *   DMUB_STATUS_OK - success
 *   DMUB_STATUS_INVALID - unspecअगरied error
 */
क्रमागत dmub_status dmub_srv_is_hw_init(काष्ठा dmub_srv *dmub, bool *is_hw_init);

/**
 * dmub_srv_hw_init() - initializes the underlying DMUB hardware
 * @dmub: the dmub service
 * @params: params क्रम hardware initialization
 *
 * Resets the DMUB hardware and perक्रमms backकरोor loading of the
 * required cache regions based on the input framebuffer regions.
 *
 * Return:
 *   DMUB_STATUS_OK - success
 *   DMUB_STATUS_NO_CTX - dmcub context not initialized
 *   DMUB_STATUS_INVALID - unspecअगरied error
 */
क्रमागत dmub_status dmub_srv_hw_init(काष्ठा dmub_srv *dmub,
				  स्थिर काष्ठा dmub_srv_hw_params *params);

/**
 * dmub_srv_hw_reset() - माला_दो the DMUB hardware in reset state अगर initialized
 * @dmub: the dmub service
 *
 * Beक्रमe destroying the DMUB service or releasing the backing framebuffer
 * memory we'll need to put the DMCUB पूर्णांकo reset first.
 *
 * A subsequent call to dmub_srv_hw_init() will re-enable the DMCUB.
 *
 * Return:
 *   DMUB_STATUS_OK - success
 *   DMUB_STATUS_INVALID - unspecअगरied error
 */
क्रमागत dmub_status dmub_srv_hw_reset(काष्ठा dmub_srv *dmub);

/**
 * dmub_srv_cmd_queue() - queues a command to the DMUB
 * @dmub: the dmub service
 * @cmd: the command to queue
 *
 * Queues a command to the DMUB service but करोes not begin execution
 * immediately.
 *
 * Return:
 *   DMUB_STATUS_OK - success
 *   DMUB_STATUS_QUEUE_FULL - no reमुख्यing room in queue
 *   DMUB_STATUS_INVALID - unspecअगरied error
 */
क्रमागत dmub_status dmub_srv_cmd_queue(काष्ठा dmub_srv *dmub,
				    स्थिर जोड़ dmub_rb_cmd *cmd);

/**
 * dmub_srv_cmd_execute() - Executes a queued sequence to the dmub
 * @dmub: the dmub service
 *
 * Begins execution of queued commands on the dmub.
 *
 * Return:
 *   DMUB_STATUS_OK - success
 *   DMUB_STATUS_INVALID - unspecअगरied error
 */
क्रमागत dmub_status dmub_srv_cmd_execute(काष्ठा dmub_srv *dmub);

/**
 * dmub_srv_रुको_क्रम_स्वतः_load() - Waits क्रम firmware स्वतः load to complete
 * @dmub: the dmub service
 * @समयout_us: the maximum number of microseconds to रुको
 *
 * Waits until firmware has been स्वतःloaded by the DMCUB. The maximum
 * रुको समय is given in microseconds to prevent spinning क्रमever.
 *
 * On ASICs without firmware स्वतःload support this function will वापस
 * immediately.
 *
 * Return:
 *   DMUB_STATUS_OK - success
 *   DMUB_STATUS_TIMEOUT - रुको क्रम phy init समयd out
 *   DMUB_STATUS_INVALID - unspecअगरied error
 */
क्रमागत dmub_status dmub_srv_रुको_क्रम_स्वतः_load(काष्ठा dmub_srv *dmub,
					     uपूर्णांक32_t समयout_us);

/**
 * dmub_srv_रुको_क्रम_phy_init() - Waits क्रम DMUB PHY init to complete
 * @dmub: the dmub service
 * @समयout_us: the maximum number of microseconds to रुको
 *
 * Waits until the PHY has been initialized by the DMUB. The maximum
 * रुको समय is given in microseconds to prevent spinning क्रमever.
 *
 * On ASICs without PHY init support this function will वापस
 * immediately.
 *
 * Return:
 *   DMUB_STATUS_OK - success
 *   DMUB_STATUS_TIMEOUT - रुको क्रम phy init समयd out
 *   DMUB_STATUS_INVALID - unspecअगरied error
 */
क्रमागत dmub_status dmub_srv_रुको_क्रम_phy_init(काष्ठा dmub_srv *dmub,
					    uपूर्णांक32_t समयout_us);

/**
 * dmub_srv_रुको_क्रम_idle() - Waits क्रम the DMUB to be idle
 * @dmub: the dmub service
 * @समयout_us: the maximum number of microseconds to रुको
 *
 * Waits until the DMUB buffer is empty and all commands have
 * finished processing. The maximum रुको समय is given in
 * microseconds to prevent spinning क्रमever.
 *
 * Return:
 *   DMUB_STATUS_OK - success
 *   DMUB_STATUS_TIMEOUT - रुको क्रम buffer to flush समयd out
 *   DMUB_STATUS_INVALID - unspecअगरied error
 */
क्रमागत dmub_status dmub_srv_रुको_क्रम_idle(काष्ठा dmub_srv *dmub,
					uपूर्णांक32_t समयout_us);

/**
 * dmub_srv_send_gpपूर्णांक_command() - Sends a GPINT based command.
 * @dmub: the dmub service
 * @command_code: the command code to send
 * @param: the command parameter to send
 * @समयout_us: the maximum number of microseconds to रुको
 *
 * Sends a command via the general purpose पूर्णांकerrupt (GPINT).
 * Waits क्रम the number of microseconds specअगरied by समयout_us
 * क्रम the command ACK beक्रमe वापसing.
 *
 * Can be called after software initialization.
 *
 * Return:
 *   DMUB_STATUS_OK - success
 *   DMUB_STATUS_TIMEOUT - रुको क्रम ACK समयd out
 *   DMUB_STATUS_INVALID - unspecअगरied error
 */
क्रमागत dmub_status
dmub_srv_send_gpपूर्णांक_command(काष्ठा dmub_srv *dmub,
			    क्रमागत dmub_gpपूर्णांक_command command_code,
			    uपूर्णांक16_t param, uपूर्णांक32_t समयout_us);

/**
 * dmub_srv_get_gpपूर्णांक_response() - Queries the GPINT response.
 * @dmub: the dmub service
 * @response: the response क्रम the last GPINT
 *
 * Returns the response code क्रम the last GPINT पूर्णांकerrupt.
 *
 * Can be called after software initialization.
 *
 * Return:
 *   DMUB_STATUS_OK - success
 *   DMUB_STATUS_INVALID - unspecअगरied error
 */
क्रमागत dmub_status dmub_srv_get_gpपूर्णांक_response(काष्ठा dmub_srv *dmub,
					     uपूर्णांक32_t *response);

/**
 * dmub_flush_buffer_mem() - Read back entire frame buffer region.
 * This ensures that the ग_लिखो from x86 has been flushed and will not
 * hang the DMCUB.
 * @fb: frame buffer to flush
 *
 * Can be called after software initialization.
 */
व्योम dmub_flush_buffer_mem(स्थिर काष्ठा dmub_fb *fb);

/**
 * dmub_srv_get_fw_boot_status() - Returns the DMUB boot status bits.
 *
 * @dmub: the dmub service
 * @status: out poपूर्णांकer क्रम firmware status
 *
 * Return:
 *   DMUB_STATUS_OK - success
 *   DMUB_STATUS_INVALID - unspecअगरied error, unsupported
 */
क्रमागत dmub_status dmub_srv_get_fw_boot_status(काष्ठा dmub_srv *dmub,
					     जोड़ dmub_fw_boot_status *status);

क्रमागत dmub_status dmub_srv_cmd_with_reply_data(काष्ठा dmub_srv *dmub,
					      जोड़ dmub_rb_cmd *cmd);

bool dmub_srv_get_outbox0_msg(काष्ठा dmub_srv *dmub, काष्ठा dmcub_trace_buf_entry *entry);

#अगर defined(__cplusplus)
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* _DMUB_SRV_H_ */
