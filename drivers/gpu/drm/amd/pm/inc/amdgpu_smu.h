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
 */
#अगर_अघोषित __AMDGPU_SMU_H__
#घोषणा __AMDGPU_SMU_H__

#समावेश "amdgpu.h"
#समावेश "kgd_pp_interface.h"
#समावेश "dm_pp_interface.h"
#समावेश "dm_pp_smu.h"
#समावेश "smu_types.h"

#घोषणा SMU_THERMAL_MINIMUM_ALERT_TEMP		0
#घोषणा SMU_THERMAL_MAXIMUM_ALERT_TEMP		255
#घोषणा SMU_TEMPERATURE_UNITS_PER_CENTIGRADES	1000
#घोषणा SMU_FW_NAME_LEN			0x24

#घोषणा SMU_DPM_USER_PROखाता_RESTORE (1 << 0)

काष्ठा smu_hw_घातer_state अणु
	अचिन्हित पूर्णांक magic;
पूर्ण;

काष्ठा smu_घातer_state;

क्रमागत smu_state_ui_label अणु
	SMU_STATE_UI_LABEL_NONE,
	SMU_STATE_UI_LABEL_BATTERY,
	SMU_STATE_UI_TABEL_MIDDLE_LOW,
	SMU_STATE_UI_LABEL_BALLANCED,
	SMU_STATE_UI_LABEL_MIDDLE_HIGHT,
	SMU_STATE_UI_LABEL_PERFORMANCE,
	SMU_STATE_UI_LABEL_BACO,
पूर्ण;

क्रमागत smu_state_classअगरication_flag अणु
	SMU_STATE_CLASSIFICATION_FLAG_BOOT                     = 0x0001,
	SMU_STATE_CLASSIFICATION_FLAG_THERMAL                  = 0x0002,
	SMU_STATE_CLASSIFICATIN_FLAG_LIMITED_POWER_SOURCE      = 0x0004,
	SMU_STATE_CLASSIFICATION_FLAG_RESET                    = 0x0008,
	SMU_STATE_CLASSIFICATION_FLAG_FORCED                   = 0x0010,
	SMU_STATE_CLASSIFICATION_FLAG_USER_3D_PERFORMANCE      = 0x0020,
	SMU_STATE_CLASSIFICATION_FLAG_USER_2D_PERFORMANCE      = 0x0040,
	SMU_STATE_CLASSIFICATION_FLAG_3D_PERFORMANCE           = 0x0080,
	SMU_STATE_CLASSIFICATION_FLAG_AC_OVERसूचीVER_TEMPLATE   = 0x0100,
	SMU_STATE_CLASSIFICATION_FLAG_UVD                      = 0x0200,
	SMU_STATE_CLASSIFICATION_FLAG_3D_PERFORMANCE_LOW       = 0x0400,
	SMU_STATE_CLASSIFICATION_FLAG_ACPI                     = 0x0800,
	SMU_STATE_CLASSIFICATION_FLAG_HD2                      = 0x1000,
	SMU_STATE_CLASSIFICATION_FLAG_UVD_HD                   = 0x2000,
	SMU_STATE_CLASSIFICATION_FLAG_UVD_SD                   = 0x4000,
	SMU_STATE_CLASSIFICATION_FLAG_USER_DC_PERFORMANCE      = 0x8000,
	SMU_STATE_CLASSIFICATION_FLAG_DC_OVERसूचीVER_TEMPLATE   = 0x10000,
	SMU_STATE_CLASSIFICATION_FLAG_BACO                     = 0x20000,
	SMU_STATE_CLASSIFICATIN_FLAG_LIMITED_POWER_SOURCE2      = 0x40000,
	SMU_STATE_CLASSIFICATION_FLAG_ULV                      = 0x80000,
	SMU_STATE_CLASSIFICATION_FLAG_UVD_MVC                  = 0x100000,
पूर्ण;

काष्ठा smu_state_classअगरication_block अणु
	क्रमागत smu_state_ui_label         ui_label;
	क्रमागत smu_state_classअगरication_flag  flags;
	पूर्णांक                          bios_index;
	bool                      temporary_state;
	bool                      to_be_deleted;
पूर्ण;

काष्ठा smu_state_pcie_block अणु
	अचिन्हित पूर्णांक lanes;
पूर्ण;

क्रमागत smu_refreshrate_source अणु
	SMU_REFRESHRATE_SOURCE_EDID,
	SMU_REFRESHRATE_SOURCE_EXPLICIT
पूर्ण;

काष्ठा smu_state_display_block अणु
	bool              disable_frame_modulation;
	bool              limit_refreshrate;
	क्रमागत smu_refreshrate_source refreshrate_source;
	पूर्णांक                  explicit_refreshrate;
	पूर्णांक                  edid_refreshrate_index;
	bool              enable_vari_bright;
पूर्ण;

काष्ठा smu_state_memory_block अणु
	bool              dll_off;
	uपूर्णांक8_t                 m3arb;
	uपूर्णांक8_t                 unused[3];
पूर्ण;

काष्ठा smu_state_software_algorithm_block अणु
	bool disable_load_balancing;
	bool enable_sleep_क्रम_बारtamps;
पूर्ण;

काष्ठा smu_temperature_range अणु
	पूर्णांक min;
	पूर्णांक max;
	पूर्णांक edge_emergency_max;
	पूर्णांक hotspot_min;
	पूर्णांक hotspot_crit_max;
	पूर्णांक hotspot_emergency_max;
	पूर्णांक mem_min;
	पूर्णांक mem_crit_max;
	पूर्णांक mem_emergency_max;
	पूर्णांक software_shutकरोwn_temp;
पूर्ण;

काष्ठा smu_state_validation_block अणु
	bool single_display_only;
	bool disallow_on_dc;
	uपूर्णांक8_t supported_घातer_levels;
पूर्ण;

काष्ठा smu_uvd_घड़ीs अणु
	uपूर्णांक32_t vclk;
	uपूर्णांक32_t dclk;
पूर्ण;

/**
* Structure to hold a SMU Power State.
*/
काष्ठा smu_घातer_state अणु
	uपूर्णांक32_t                                      id;
	काष्ठा list_head                              ordered_list;
	काष्ठा list_head                              all_states_list;

	काष्ठा smu_state_classअगरication_block         classअगरication;
	काष्ठा smu_state_validation_block             validation;
	काष्ठा smu_state_pcie_block                   pcie;
	काष्ठा smu_state_display_block                display;
	काष्ठा smu_state_memory_block                 memory;
	काष्ठा smu_state_software_algorithm_block     software;
	काष्ठा smu_uvd_घड़ीs                         uvd_घड़ीs;
	काष्ठा smu_hw_घातer_state                     hardware;
पूर्ण;

क्रमागत smu_घातer_src_type
अणु
	SMU_POWER_SOURCE_AC,
	SMU_POWER_SOURCE_DC,
	SMU_POWER_SOURCE_COUNT,
पूर्ण;

क्रमागत smu_ppt_limit_type
अणु
	SMU_DEFAULT_PPT_LIMIT = 0,
	SMU_FAST_PPT_LIMIT,
पूर्ण;

क्रमागत smu_ppt_limit_level
अणु
	SMU_PPT_LIMIT_MIN = -1,
	SMU_PPT_LIMIT_CURRENT,
	SMU_PPT_LIMIT_DEFAULT,
	SMU_PPT_LIMIT_MAX,
पूर्ण;

क्रमागत smu_memory_pool_size
अणु
    SMU_MEMORY_POOL_SIZE_ZERO   = 0,
    SMU_MEMORY_POOL_SIZE_256_MB = 0x10000000,
    SMU_MEMORY_POOL_SIZE_512_MB = 0x20000000,
    SMU_MEMORY_POOL_SIZE_1_GB   = 0x40000000,
    SMU_MEMORY_POOL_SIZE_2_GB   = 0x80000000,
पूर्ण;

काष्ठा smu_user_dpm_profile अणु
	uपूर्णांक32_t fan_mode;
	uपूर्णांक32_t घातer_limit;
	uपूर्णांक32_t fan_speed_percent;
	uपूर्णांक32_t flags;

	/* user घड़ी state inक्रमmation */
	uपूर्णांक32_t clk_mask[SMU_CLK_COUNT];
	uपूर्णांक32_t clk_dependency;
पूर्ण;

क्रमागत smu_event_type अणु

	SMU_EVENT_RESET_COMPLETE = 0,
पूर्ण;

#घोषणा SMU_TABLE_INIT(tables, table_id, s, a, d)	\
	करो अणु						\
		tables[table_id].size = s;		\
		tables[table_id].align = a;		\
		tables[table_id].करोमुख्य = d;		\
	पूर्ण जबतक (0)

काष्ठा smu_table अणु
	uपूर्णांक64_t size;
	uपूर्णांक32_t align;
	uपूर्णांक8_t करोमुख्य;
	uपूर्णांक64_t mc_address;
	व्योम *cpu_addr;
	काष्ठा amdgpu_bo *bo;
पूर्ण;

क्रमागत smu_perf_level_designation अणु
	PERF_LEVEL_ACTIVITY,
	PERF_LEVEL_POWER_CONTAINMENT,
पूर्ण;

काष्ठा smu_perक्रमmance_level अणु
	uपूर्णांक32_t core_घड़ी;
	uपूर्णांक32_t memory_घड़ी;
	uपूर्णांक32_t vddc;
	uपूर्णांक32_t vddci;
	uपूर्णांक32_t non_local_mem_freq;
	uपूर्णांक32_t non_local_mem_width;
पूर्ण;

काष्ठा smu_घड़ी_info अणु
	uपूर्णांक32_t min_mem_clk;
	uपूर्णांक32_t max_mem_clk;
	uपूर्णांक32_t min_eng_clk;
	uपूर्णांक32_t max_eng_clk;
	uपूर्णांक32_t min_bus_bandwidth;
	uपूर्णांक32_t max_bus_bandwidth;
पूर्ण;

काष्ठा smu_bios_boot_up_values
अणु
	uपूर्णांक32_t			revision;
	uपूर्णांक32_t			gfxclk;
	uपूर्णांक32_t			uclk;
	uपूर्णांक32_t			socclk;
	uपूर्णांक32_t			dcefclk;
	uपूर्णांक32_t			eclk;
	uपूर्णांक32_t			vclk;
	uपूर्णांक32_t			dclk;
	uपूर्णांक16_t			vddc;
	uपूर्णांक16_t			vddci;
	uपूर्णांक16_t			mvddc;
	uपूर्णांक16_t			vdd_gfx;
	uपूर्णांक8_t				cooling_id;
	uपूर्णांक32_t			pp_table_id;
	uपूर्णांक32_t			क्रमmat_revision;
	uपूर्णांक32_t			content_revision;
	uपूर्णांक32_t			fclk;
	uपूर्णांक32_t			lclk;
	uपूर्णांक32_t			firmware_caps;
पूर्ण;

क्रमागत smu_table_id
अणु
	SMU_TABLE_PPTABLE = 0,
	SMU_TABLE_WATERMARKS,
	SMU_TABLE_CUSTOM_DPM,
	SMU_TABLE_DPMCLOCKS,
	SMU_TABLE_AVFS,
	SMU_TABLE_AVFS_PSM_DEBUG,
	SMU_TABLE_AVFS_FUSE_OVERRIDE,
	SMU_TABLE_PMSTATUSLOG,
	SMU_TABLE_SMU_METRICS,
	SMU_TABLE_DRIVER_SMU_CONFIG,
	SMU_TABLE_ACTIVITY_MONITOR_COEFF,
	SMU_TABLE_OVERDRIVE,
	SMU_TABLE_I2C_COMMANDS,
	SMU_TABLE_PACE,
	SMU_TABLE_COUNT,
पूर्ण;

काष्ठा smu_table_context
अणु
	व्योम				*घातer_play_table;
	uपूर्णांक32_t			घातer_play_table_size;
	व्योम				*hardcode_pptable;
	अचिन्हित दीर्घ			metrics_समय;
	व्योम				*metrics_table;
	व्योम				*घड़ीs_table;
	व्योम				*watermarks_table;

	व्योम				*max_sustainable_घड़ीs;
	काष्ठा smu_bios_boot_up_values	boot_values;
	व्योम                            *driver_pptable;
	काष्ठा smu_table		tables[SMU_TABLE_COUNT];
	/*
	 * The driver table is just a staging buffer क्रम
	 * uploading/करोwnloading content from the SMU.
	 *
	 * And the table_id क्रम SMU_MSG_TransferTableSmu2Dram/
	 * SMU_MSG_TransferTableDram2Smu inकाष्ठाs SMU
	 * which content driver is पूर्णांकerested.
	 */
	काष्ठा smu_table		driver_table;
	काष्ठा smu_table		memory_pool;
	काष्ठा smu_table		dummy_पढ़ो_1_table;
	uपूर्णांक8_t                         thermal_controller_type;

	व्योम				*overdrive_table;
	व्योम                            *boot_overdrive_table;

	uपूर्णांक32_t			gpu_metrics_table_size;
	व्योम				*gpu_metrics_table;
पूर्ण;

काष्ठा smu_dpm_context अणु
	uपूर्णांक32_t dpm_context_size;
	व्योम *dpm_context;
	व्योम *golden_dpm_context;
	bool enable_umd_pstate;
	क्रमागत amd_dpm_क्रमced_level dpm_level;
	क्रमागत amd_dpm_क्रमced_level saved_dpm_level;
	क्रमागत amd_dpm_क्रमced_level requested_dpm_level;
	काष्ठा smu_घातer_state *dpm_request_घातer_state;
	काष्ठा smu_घातer_state *dpm_current_घातer_state;
	काष्ठा mघड़ी_latency_table *mclk_latency_table;
पूर्ण;

काष्ठा smu_घातer_gate अणु
	bool uvd_gated;
	bool vce_gated;
	atomic_t vcn_gated;
	atomic_t jpeg_gated;
	काष्ठा mutex vcn_gate_lock;
	काष्ठा mutex jpeg_gate_lock;
पूर्ण;

काष्ठा smu_घातer_context अणु
	व्योम *घातer_context;
	uपूर्णांक32_t घातer_context_size;
	काष्ठा smu_घातer_gate घातer_gate;
पूर्ण;

#घोषणा SMU_FEATURE_MAX	(64)
काष्ठा smu_feature
अणु
	uपूर्णांक32_t feature_num;
	DECLARE_BITMAP(supported, SMU_FEATURE_MAX);
	DECLARE_BITMAP(allowed, SMU_FEATURE_MAX);
	DECLARE_BITMAP(enabled, SMU_FEATURE_MAX);
	काष्ठा mutex mutex;
पूर्ण;

काष्ठा smu_घड़ीs अणु
	uपूर्णांक32_t engine_घड़ी;
	uपूर्णांक32_t memory_घड़ी;
	uपूर्णांक32_t bus_bandwidth;
	uपूर्णांक32_t engine_घड़ी_in_sr;
	uपूर्णांक32_t dcef_घड़ी;
	uपूर्णांक32_t dcef_घड़ी_in_sr;
पूर्ण;

#घोषणा MAX_REGULAR_DPM_NUM 16
काष्ठा mclk_latency_entries अणु
	uपूर्णांक32_t  frequency;
	uपूर्णांक32_t  latency;
पूर्ण;
काष्ठा mघड़ी_latency_table अणु
	uपूर्णांक32_t  count;
	काष्ठा mclk_latency_entries  entries[MAX_REGULAR_DPM_NUM];
पूर्ण;

क्रमागत smu_reset_mode
अणु
    SMU_RESET_MODE_0,
    SMU_RESET_MODE_1,
    SMU_RESET_MODE_2,
पूर्ण;

क्रमागत smu_baco_state
अणु
	SMU_BACO_STATE_ENTER = 0,
	SMU_BACO_STATE_EXIT,
पूर्ण;

काष्ठा smu_baco_context
अणु
	काष्ठा mutex mutex;
	uपूर्णांक32_t state;
	bool platक्रमm_support;
पूर्ण;

काष्ठा pstates_clk_freq अणु
	uपूर्णांक32_t			min;
	uपूर्णांक32_t			standard;
	uपूर्णांक32_t			peak;
पूर्ण;

काष्ठा smu_umd_pstate_table अणु
	काष्ठा pstates_clk_freq		gfxclk_pstate;
	काष्ठा pstates_clk_freq		socclk_pstate;
	काष्ठा pstates_clk_freq		uclk_pstate;
	काष्ठा pstates_clk_freq		vclk_pstate;
	काष्ठा pstates_clk_freq		dclk_pstate;
पूर्ण;

काष्ठा cmn2asic_msg_mapping अणु
	पूर्णांक	valid_mapping;
	पूर्णांक	map_to;
	पूर्णांक	valid_in_vf;
पूर्ण;

काष्ठा cmn2asic_mapping अणु
	पूर्णांक	valid_mapping;
	पूर्णांक	map_to;
पूर्ण;

#घोषणा WORKLOAD_POLICY_MAX 7
काष्ठा smu_context
अणु
	काष्ठा amdgpu_device            *adev;
	काष्ठा amdgpu_irq_src		irq_source;

	स्थिर काष्ठा pptable_funcs	*ppt_funcs;
	स्थिर काष्ठा cmn2asic_msg_mapping	*message_map;
	स्थिर काष्ठा cmn2asic_mapping	*घड़ी_map;
	स्थिर काष्ठा cmn2asic_mapping	*feature_map;
	स्थिर काष्ठा cmn2asic_mapping	*table_map;
	स्थिर काष्ठा cmn2asic_mapping	*pwr_src_map;
	स्थिर काष्ठा cmn2asic_mapping	*workload_map;
	काष्ठा mutex			mutex;
	काष्ठा mutex			sensor_lock;
	काष्ठा mutex			metrics_lock;
	काष्ठा mutex			message_lock;
	uपूर्णांक64_t pool_size;

	काष्ठा smu_table_context	smu_table;
	काष्ठा smu_dpm_context		smu_dpm;
	काष्ठा smu_घातer_context	smu_घातer;
	काष्ठा smu_feature		smu_feature;
	काष्ठा amd_pp_display_configuration  *display_config;
	काष्ठा smu_baco_context		smu_baco;
	काष्ठा smu_temperature_range	thermal_range;
	व्योम *od_settings;

	काष्ठा smu_umd_pstate_table	pstate_table;
	uपूर्णांक32_t pstate_sclk;
	uपूर्णांक32_t pstate_mclk;

	bool od_enabled;
	uपूर्णांक32_t current_घातer_limit;
	uपूर्णांक32_t शेष_घातer_limit;
	uपूर्णांक32_t max_घातer_limit;

	/* soft pptable */
	uपूर्णांक32_t ppt_offset_bytes;
	uपूर्णांक32_t ppt_size_bytes;
	uपूर्णांक8_t  *ppt_start_addr;

	bool support_घातer_containment;
	bool disable_watermark;

#घोषणा WATERMARKS_EXIST	(1 << 0)
#घोषणा WATERMARKS_LOADED	(1 << 1)
	uपूर्णांक32_t watermarks_biपंचांगap;
	uपूर्णांक32_t hard_min_uclk_req_from_dal;
	bool disable_uclk_चयन;

	uपूर्णांक32_t workload_mask;
	uपूर्णांक32_t workload_prority[WORKLOAD_POLICY_MAX];
	uपूर्णांक32_t workload_setting[WORKLOAD_POLICY_MAX];
	uपूर्णांक32_t घातer_profile_mode;
	uपूर्णांक32_t शेष_घातer_profile_mode;
	bool pm_enabled;
	bool is_apu;

	uपूर्णांक32_t smc_driver_अगर_version;
	uपूर्णांक32_t smc_fw_अगर_version;
	uपूर्णांक32_t smc_fw_version;

	bool uploading_custom_pp_table;
	bool dc_controlled_by_gpio;

	काष्ठा work_काष्ठा throttling_logging_work;
	atomic64_t throttle_पूर्णांक_counter;
	काष्ठा work_काष्ठा पूर्णांकerrupt_work;

	अचिन्हित fan_max_rpm;
	अचिन्हित manual_fan_speed_percent;

	uपूर्णांक32_t gfx_शेष_hard_min_freq;
	uपूर्णांक32_t gfx_शेष_soft_max_freq;
	uपूर्णांक32_t gfx_actual_hard_min_freq;
	uपूर्णांक32_t gfx_actual_soft_max_freq;

	/* APU only */
	uपूर्णांक32_t cpu_शेष_soft_min_freq;
	uपूर्णांक32_t cpu_शेष_soft_max_freq;
	uपूर्णांक32_t cpu_actual_soft_min_freq;
	uपूर्णांक32_t cpu_actual_soft_max_freq;
	uपूर्णांक32_t cpu_core_id_select;
	uपूर्णांक16_t cpu_core_num;

	काष्ठा smu_user_dpm_profile user_dpm_profile;
पूर्ण;

काष्ठा i2c_adapter;

/**
 * काष्ठा pptable_funcs - Callbacks used to पूर्णांकeract with the SMU.
 */
काष्ठा pptable_funcs अणु
	/**
	 * @run_btc: Calibrate voltage/frequency curve to fit the प्रणाली's
	 *           घातer delivery and voltage margins. Required क्रम adaptive
	 *           voltage frequency scaling (AVFS).
	 */
	पूर्णांक (*run_btc)(काष्ठा smu_context *smu);

	/**
	 * @get_allowed_feature_mask: Get allowed feature mask.
	 * &feature_mask: Array to store feature mask.
	 * &num: Elements in &feature_mask.
	 */
	पूर्णांक (*get_allowed_feature_mask)(काष्ठा smu_context *smu, uपूर्णांक32_t *feature_mask, uपूर्णांक32_t num);

	/**
	 * @get_current_घातer_state: Get the current घातer state.
	 *
	 * Return: Current घातer state on success, negative त्रुटि_सं on failure.
	 */
	क्रमागत amd_pm_state_type (*get_current_घातer_state)(काष्ठा smu_context *smu);

	/**
	 * @set_शेष_dpm_table: Retrieve the शेष overdrive settings from
	 *                         the SMU.
	 */
	पूर्णांक (*set_शेष_dpm_table)(काष्ठा smu_context *smu);

	पूर्णांक (*set_घातer_state)(काष्ठा smu_context *smu);

	/**
	 * @populate_umd_state_clk: Populate the UMD घातer state table with
	 *                          शेषs.
	 */
	पूर्णांक (*populate_umd_state_clk)(काष्ठा smu_context *smu);

	/**
	 * @prपूर्णांक_clk_levels: Prपूर्णांक DPM घड़ी levels क्रम a घड़ी करोमुख्य
	 *                    to buffer. Star current level.
	 *
	 * Used क्रम sysfs पूर्णांकerfaces.
	 */
	पूर्णांक (*prपूर्णांक_clk_levels)(काष्ठा smu_context *smu, क्रमागत smu_clk_type clk_type, अक्षर *buf);

	/**
	 * @क्रमce_clk_levels: Set a range of allowed DPM levels क्रम a घड़ी
	 *                    करोमुख्य.
	 * &clk_type: Clock करोमुख्य.
	 * &mask: Range of allowed DPM levels.
	 */
	पूर्णांक (*क्रमce_clk_levels)(काष्ठा smu_context *smu, क्रमागत smu_clk_type clk_type, uपूर्णांक32_t mask);

	/**
	 * @od_edit_dpm_table: Edit the custom overdrive DPM table.
	 * &type: Type of edit.
	 * &input: Edit parameters.
	 * &size: Size of &input.
	 */
	पूर्णांक (*od_edit_dpm_table)(काष्ठा smu_context *smu,
				 क्रमागत PP_OD_DPM_TABLE_COMMAND type,
				 दीर्घ *input, uपूर्णांक32_t size);

	/**
	 * @get_घड़ी_by_type_with_latency: Get the speed and latency of a घड़ी
	 *                                  करोमुख्य.
	 */
	पूर्णांक (*get_घड़ी_by_type_with_latency)(काष्ठा smu_context *smu,
					      क्रमागत smu_clk_type clk_type,
					      काष्ठा
					      pp_घड़ी_levels_with_latency
					      *घड़ीs);
	/**
	 * @get_घड़ी_by_type_with_voltage: Get the speed and voltage of a घड़ी
	 *                                  करोमुख्य.
	 */
	पूर्णांक (*get_घड़ी_by_type_with_voltage)(काष्ठा smu_context *smu,
					      क्रमागत amd_pp_घड़ी_प्रकारype type,
					      काष्ठा
					      pp_घड़ी_levels_with_voltage
					      *घड़ीs);

	/**
	 * @get_घातer_profile_mode: Prपूर्णांक all घातer profile modes to
	 *                          buffer. Star current mode.
	 */
	पूर्णांक (*get_घातer_profile_mode)(काष्ठा smu_context *smu, अक्षर *buf);

	/**
	 * @set_घातer_profile_mode: Set a घातer profile mode. Also used to
	 *                          create/set custom घातer profile modes.
	 * &input: Power profile mode parameters.
	 * &size: Size of &input.
	 */
	पूर्णांक (*set_घातer_profile_mode)(काष्ठा smu_context *smu, दीर्घ *input, uपूर्णांक32_t size);

	/**
	 * @dpm_set_vcn_enable: Enable/disable VCN engine dynamic घातer
	 *                      management.
	 */
	पूर्णांक (*dpm_set_vcn_enable)(काष्ठा smu_context *smu, bool enable);

	/**
	 * @dpm_set_jpeg_enable: Enable/disable JPEG engine dynamic घातer
	 *                       management.
	 */
	पूर्णांक (*dpm_set_jpeg_enable)(काष्ठा smu_context *smu, bool enable);

	/**
	 * @पढ़ो_sensor: Read data from a sensor.
	 * &sensor: Sensor to पढ़ो data from.
	 * &data: Sensor पढ़ोing.
	 * &size: Size of &data.
	 */
	पूर्णांक (*पढ़ो_sensor)(काष्ठा smu_context *smu, क्रमागत amd_pp_sensors sensor,
			   व्योम *data, uपूर्णांक32_t *size);

	/**
	 * @pre_display_config_changed: Prepare GPU क्रम a display configuration
	 *                              change.
	 *
	 * Disable display tracking and pin memory घड़ी speed to maximum. Used
	 * in display component synchronization.
	 */
	पूर्णांक (*pre_display_config_changed)(काष्ठा smu_context *smu);

	/**
	 * @display_config_changed: Notअगरy the SMU of the current display
	 *                          configuration.
	 *
	 * Allows SMU to properly track blanking periods क्रम memory घड़ी
	 * adjusपंचांगent. Used in display component synchronization.
	 */
	पूर्णांक (*display_config_changed)(काष्ठा smu_context *smu);

	पूर्णांक (*apply_घड़ीs_adjust_rules)(काष्ठा smu_context *smu);

	/**
	 * @notअगरy_smc_display_config: Applies display requirements to the
	 *                             current घातer state.
	 *
	 * Optimize deep sleep DCEFclk and mclk क्रम the current display
	 * configuration. Used in display component synchronization.
	 */
	पूर्णांक (*notअगरy_smc_display_config)(काष्ठा smu_context *smu);

	/**
	 * @is_dpm_running: Check अगर DPM is running.
	 *
	 * Return: True अगर DPM is running, false otherwise.
	 */
	bool (*is_dpm_running)(काष्ठा smu_context *smu);

	/**
	 * @get_fan_speed_percent: Get the current fan speed in percent.
	 */
	पूर्णांक (*get_fan_speed_percent)(काष्ठा smu_context *smu, uपूर्णांक32_t *speed);

	/**
	 * @set_watermarks_table: Configure and upload the watermarks tables to
	 *                        the SMU.
	 */
	पूर्णांक (*set_watermarks_table)(काष्ठा smu_context *smu,
				    काष्ठा pp_smu_wm_range_sets *घड़ी_ranges);

	/**
	 * @get_thermal_temperature_range: Get safe thermal limits in Celcius.
	 */
	पूर्णांक (*get_thermal_temperature_range)(काष्ठा smu_context *smu, काष्ठा smu_temperature_range *range);

	/**
	 * @get_uclk_dpm_states: Get memory घड़ी DPM levels in kHz.
	 * &घड़ीs_in_khz: Array of DPM levels.
	 * &num_states: Elements in &घड़ीs_in_khz.
	 */
	पूर्णांक (*get_uclk_dpm_states)(काष्ठा smu_context *smu, uपूर्णांक32_t *घड़ीs_in_khz, uपूर्णांक32_t *num_states);

	/**
	 * @set_शेष_od_settings: Set the overdrive tables to शेषs.
	 */
	पूर्णांक (*set_शेष_od_settings)(काष्ठा smu_context *smu);

	/**
	 * @set_perक्रमmance_level: Set a perक्रमmance level.
	 */
	पूर्णांक (*set_perक्रमmance_level)(काष्ठा smu_context *smu, क्रमागत amd_dpm_क्रमced_level level);

	/**
	 * @display_disable_memory_घड़ी_चयन: Enable/disable dynamic memory
	 *                                       घड़ी चयनing.
	 *
	 * Disabling this feature क्रमces memory घड़ी speed to maximum.
	 * Enabling sets the minimum memory घड़ी capable of driving the
	 * current display configuration.
	 */
	पूर्णांक (*display_disable_memory_घड़ी_चयन)(काष्ठा smu_context *smu, bool disable_memory_घड़ी_चयन);

	/**
	 * @dump_pptable: Prपूर्णांक the घातer play table to the प्रणाली log.
	 */
	व्योम (*dump_pptable)(काष्ठा smu_context *smu);

	/**
	 * @get_घातer_limit: Get the device's घातer limits.
	 */
	पूर्णांक (*get_घातer_limit)(काष्ठा smu_context *smu);

	/**
	 * @get_ppt_limit: Get the device's ppt limits.
	 */
	पूर्णांक (*get_ppt_limit)(काष्ठा smu_context *smu, uपूर्णांक32_t *ppt_limit,
			क्रमागत smu_ppt_limit_type limit_type, क्रमागत smu_ppt_limit_level limit_level);

	/**
	 * @set_df_cstate: Set data fabric cstate.
	 */
	पूर्णांक (*set_df_cstate)(काष्ठा smu_context *smu, क्रमागत pp_df_cstate state);

	/**
	 * @allow_xgmi_घातer_करोwn: Enable/disable बाह्यal global memory
	 *                         पूर्णांकerconnect घातer करोwn.
	 */
	पूर्णांक (*allow_xgmi_घातer_करोwn)(काष्ठा smu_context *smu, bool en);

	/**
	 * @update_pcie_parameters: Update and upload the प्रणाली's PCIe
	 *                          capabilites to the SMU.
	 * &pcie_gen_cap: Maximum allowed PCIe generation.
	 * &pcie_width_cap: Maximum allowed PCIe width.
	 */
	पूर्णांक (*update_pcie_parameters)(काष्ठा smu_context *smu, uपूर्णांक32_t pcie_gen_cap, uपूर्णांक32_t pcie_width_cap);

	/**
	 * @i2c_init: Initialize i2c.
	 *
	 * The i2c bus is used पूर्णांकernally by the SMU voltage regulators and
	 * other devices. The i2c's EEPROM also stores bad page tables on boards
	 * with ECC.
	 */
	पूर्णांक (*i2c_init)(काष्ठा smu_context *smu, काष्ठा i2c_adapter *control);

	/**
	 * @i2c_fini: Tear करोwn i2c.
	 */
	व्योम (*i2c_fini)(काष्ठा smu_context *smu, काष्ठा i2c_adapter *control);

	/**
	 * @get_unique_id: Get the GPU's unique id. Used क्रम asset tracking.
	 */
	व्योम (*get_unique_id)(काष्ठा smu_context *smu);

	/**
	 * @get_dpm_घड़ी_प्रकारable: Get a copy of the DPM घड़ी table.
	 *
	 * Used by display component in bandwidth and watermark calculations.
	 */
	पूर्णांक (*get_dpm_घड़ी_प्रकारable)(काष्ठा smu_context *smu, काष्ठा dpm_घड़ीs *घड़ी_प्रकारable);

	/**
	 * @init_microcode: Request the SMU's firmware from the kernel.
	 */
	पूर्णांक (*init_microcode)(काष्ठा smu_context *smu);

	/**
	 * @load_microcode: Load firmware onto the SMU.
	 */
	पूर्णांक (*load_microcode)(काष्ठा smu_context *smu);

	/**
	 * @fini_microcode: Release the SMU's firmware.
	 */
	व्योम (*fini_microcode)(काष्ठा smu_context *smu);

	/**
	 * @init_smc_tables: Initialize the SMU tables.
	 */
	पूर्णांक (*init_smc_tables)(काष्ठा smu_context *smu);

	/**
	 * @fini_smc_tables: Release the SMU tables.
	 */
	पूर्णांक (*fini_smc_tables)(काष्ठा smu_context *smu);

	/**
	 * @init_घातer: Initialize the घातer gate table context.
	 */
	पूर्णांक (*init_घातer)(काष्ठा smu_context *smu);

	/**
	 * @fini_घातer: Release the घातer gate table context.
	 */
	पूर्णांक (*fini_घातer)(काष्ठा smu_context *smu);

	/**
	 * @check_fw_status: Check the SMU's firmware status.
	 *
	 * Return: Zero अगर check passes, negative त्रुटि_सं on failure.
	 */
	पूर्णांक (*check_fw_status)(काष्ठा smu_context *smu);

	/**
	 * @set_mp1_state: put SMU पूर्णांकo a correct state क्रम comming
	 *                 resume from runpm or gpu reset.
	 */
	पूर्णांक (*set_mp1_state)(काष्ठा smu_context *smu,
			     क्रमागत pp_mp1_state mp1_state);

	/**
	 * @setup_pptable: Initialize the घातer play table and populate it with
	 *                 शेष values.
	 */
	पूर्णांक (*setup_pptable)(काष्ठा smu_context *smu);

	/**
	 * @get_vbios_bootup_values: Get शेष boot values from the VBIOS.
	 */
	पूर्णांक (*get_vbios_bootup_values)(काष्ठा smu_context *smu);

	/**
	 * @check_fw_version: Prपूर्णांक driver and SMU पूर्णांकerface versions to the
	 *                    प्रणाली log.
	 *
	 * Interface mismatch is not a critical failure.
	 */
	पूर्णांक (*check_fw_version)(काष्ठा smu_context *smu);

	/**
	 * @घातergate_sdma: Power up/करोwn प्रणाली direct memory access.
	 */
	पूर्णांक (*घातergate_sdma)(काष्ठा smu_context *smu, bool gate);

	/**
	 * @set_gfx_cgpg: Enable/disable graphics engine course grain घातer
	 *                gating.
	 */
	पूर्णांक (*set_gfx_cgpg)(काष्ठा smu_context *smu, bool enable);

	/**
	 * @ग_लिखो_pptable: Write the घातer play table to the SMU.
	 */
	पूर्णांक (*ग_लिखो_pptable)(काष्ठा smu_context *smu);

	/**
	 * @set_driver_table_location: Send the location of the driver table to
	 *                             the SMU.
	 */
	पूर्णांक (*set_driver_table_location)(काष्ठा smu_context *smu);

	/**
	 * @set_tool_table_location: Send the location of the tool table to the
	 *                           SMU.
	 */
	पूर्णांक (*set_tool_table_location)(काष्ठा smu_context *smu);

	/**
	 * @notअगरy_memory_pool_location: Send the location of the memory pool to
	 *                               the SMU.
	 */
	पूर्णांक (*notअगरy_memory_pool_location)(काष्ठा smu_context *smu);

	/**
	 * @प्रणाली_features_control: Enable/disable all SMU features.
	 */
	पूर्णांक (*प्रणाली_features_control)(काष्ठा smu_context *smu, bool en);

	/**
	 * @send_smc_msg_with_param: Send a message with a parameter to the SMU.
	 * &msg: Type of message.
	 * &param: Message parameter.
	 * &पढ़ो_arg: SMU response (optional).
	 */
	पूर्णांक (*send_smc_msg_with_param)(काष्ठा smu_context *smu,
				       क्रमागत smu_message_type msg, uपूर्णांक32_t param, uपूर्णांक32_t *पढ़ो_arg);

	/**
	 * @send_smc_msg: Send a message to the SMU.
	 * &msg: Type of message.
	 * &पढ़ो_arg: SMU response (optional).
	 */
	पूर्णांक (*send_smc_msg)(काष्ठा smu_context *smu,
			    क्रमागत smu_message_type msg,
			    uपूर्णांक32_t *पढ़ो_arg);

	/**
	 * @init_display_count: Notअगरy the SMU of the number of display
	 *                      components in current display configuration.
	 */
	पूर्णांक (*init_display_count)(काष्ठा smu_context *smu, uपूर्णांक32_t count);

	/**
	 * @set_allowed_mask: Notअगरy the SMU of the features currently allowed
	 *                    by the driver.
	 */
	पूर्णांक (*set_allowed_mask)(काष्ठा smu_context *smu);

	/**
	 * @get_enabled_mask: Get a mask of features that are currently enabled
	 *                    on the SMU.
	 * &feature_mask: Array representing enabled feature mask.
	 * &num: Elements in &feature_mask.
	 */
	पूर्णांक (*get_enabled_mask)(काष्ठा smu_context *smu, uपूर्णांक32_t *feature_mask, uपूर्णांक32_t num);

	/**
	 * @feature_is_enabled: Test अगर a feature is enabled.
	 *
	 * Return: One अगर enabled, zero अगर disabled.
	 */
	पूर्णांक (*feature_is_enabled)(काष्ठा smu_context *smu, क्रमागत smu_feature_mask mask);

	/**
	 * @disable_all_features_with_exception: Disable all features with
	 *                                       exception to those in &mask.
	 */
	पूर्णांक (*disable_all_features_with_exception)(काष्ठा smu_context *smu, क्रमागत smu_feature_mask mask);

	/**
	 * @notअगरy_display_change: Enable fast memory घड़ी चयनing.
	 *
	 * Allows क्रम fine grained memory घड़ी चयनing but has more stringent
	 * timing requirements.
	 */
	पूर्णांक (*notअगरy_display_change)(काष्ठा smu_context *smu);

	/**
	 * @set_घातer_limit: Set घातer limit in watts.
	 */
	पूर्णांक (*set_घातer_limit)(काष्ठा smu_context *smu, uपूर्णांक32_t n);

	/**
	 * @init_max_sustainable_घड़ीs: Populate max sustainable घड़ी speed
	 *                               table with values from the SMU.
	 */
	पूर्णांक (*init_max_sustainable_घड़ीs)(काष्ठा smu_context *smu);

	/**
	 * @enable_thermal_alert: Enable thermal alert पूर्णांकerrupts.
	 */
	पूर्णांक (*enable_thermal_alert)(काष्ठा smu_context *smu);

	/**
	 * @disable_thermal_alert: Disable thermal alert पूर्णांकerrupts.
	 */
	पूर्णांक (*disable_thermal_alert)(काष्ठा smu_context *smu);

	/**
	 * @set_min_dcef_deep_sleep: Set a minimum display fabric deep sleep
	 *                           घड़ी speed in MHz.
	 */
	पूर्णांक (*set_min_dcef_deep_sleep)(काष्ठा smu_context *smu, uपूर्णांक32_t clk);

	/**
	 * @display_घड़ी_voltage_request: Set a hard minimum frequency
	 * क्रम a घड़ी करोमुख्य.
	 */
	पूर्णांक (*display_घड़ी_voltage_request)(काष्ठा smu_context *smu, काष्ठा
					     pp_display_घड़ी_request
					     *घड़ी_req);

	/**
	 * @get_fan_control_mode: Get the current fan control mode.
	 */
	uपूर्णांक32_t (*get_fan_control_mode)(काष्ठा smu_context *smu);

	/**
	 * @set_fan_control_mode: Set the fan control mode.
	 */
	पूर्णांक (*set_fan_control_mode)(काष्ठा smu_context *smu, uपूर्णांक32_t mode);

	/**
	 * @set_fan_speed_percent: Set a अटल fan speed in percent.
	 */
	पूर्णांक (*set_fan_speed_percent)(काष्ठा smu_context *smu, uपूर्णांक32_t speed);

	/**
	 * @set_xgmi_pstate: Set पूर्णांकer-chip global memory पूर्णांकerconnect pstate.
	 * &pstate: Pstate to set. D0 अगर Nonzero, D3 otherwise.
	 */
	पूर्णांक (*set_xgmi_pstate)(काष्ठा smu_context *smu, uपूर्णांक32_t pstate);

	/**
	 * @gfx_off_control: Enable/disable graphics engine घातeroff.
	 */
	पूर्णांक (*gfx_off_control)(काष्ठा smu_context *smu, bool enable);


	/**
	 * @get_gfx_off_status: Get graphics engine घातeroff status.
	 *
	 * Return:
	 * 0 - GFXOFF(शेष).
	 * 1 - Transition out of GFX State.
	 * 2 - Not in GFXOFF.
	 * 3 - Transition पूर्णांकo GFXOFF.
	 */
	uपूर्णांक32_t (*get_gfx_off_status)(काष्ठा smu_context *smu);

	/**
	 * @रेजिस्टर_irq_handler: Register पूर्णांकerupt request handlers.
	 */
	पूर्णांक (*रेजिस्टर_irq_handler)(काष्ठा smu_context *smu);

	/**
	 * @set_azalia_d3_pme: Wake the audio decode engine from d3 sleep.
	 */
	पूर्णांक (*set_azalia_d3_pme)(काष्ठा smu_context *smu);

	/**
	 * @get_max_sustainable_घड़ीs_by_dc: Get a copy of the max sustainable
	 *                                    घड़ी speeds table.
	 *
	 * Provides a way क्रम the display component (DC) to get the max
	 * sustainable घड़ीs from the SMU.
	 */
	पूर्णांक (*get_max_sustainable_घड़ीs_by_dc)(काष्ठा smu_context *smu, काष्ठा pp_smu_nv_घड़ी_प्रकारable *max_घड़ीs);

	/**
	 * @baco_is_support: Check अगर GPU supports BACO (Bus Active, Chip Off).
	 */
	bool (*baco_is_support)(काष्ठा smu_context *smu);

	/**
	 * @baco_get_state: Get the current BACO state.
	 *
	 * Return: Current BACO state.
	 */
	क्रमागत smu_baco_state (*baco_get_state)(काष्ठा smu_context *smu);

	/**
	 * @baco_set_state: Enter/निकास BACO.
	 */
	पूर्णांक (*baco_set_state)(काष्ठा smu_context *smu, क्रमागत smu_baco_state state);

	/**
	 * @baco_enter: Enter BACO.
	 */
	पूर्णांक (*baco_enter)(काष्ठा smu_context *smu);

	/**
	 * @baco_निकास: Exit Baco.
	 */
	पूर्णांक (*baco_निकास)(काष्ठा smu_context *smu);

	/**
	 * @mode1_reset_is_support: Check अगर GPU supports mode1 reset.
	 */
	bool (*mode1_reset_is_support)(काष्ठा smu_context *smu);
	/**
	 * @mode2_reset_is_support: Check अगर GPU supports mode2 reset.
	 */
	bool (*mode2_reset_is_support)(काष्ठा smu_context *smu);

	/**
	 * @mode1_reset: Perक्रमm mode1 reset.
	 *
	 * Complete GPU reset.
	 */
	पूर्णांक (*mode1_reset)(काष्ठा smu_context *smu);

	/**
	 * @mode2_reset: Perक्रमm mode2 reset.
	 *
	 * Mode2 reset generally करोes not reset as many IPs as mode1 reset. The
	 * IPs reset varies by asic.
	 */
	पूर्णांक (*mode2_reset)(काष्ठा smu_context *smu);

	/**
	 * @get_dpm_ultimate_freq: Get the hard frequency range of a घड़ी
	 *                         करोमुख्य in MHz.
	 */
	पूर्णांक (*get_dpm_ultimate_freq)(काष्ठा smu_context *smu, क्रमागत smu_clk_type clk_type, uपूर्णांक32_t *min, uपूर्णांक32_t *max);

	/**
	 * @set_soft_freq_limited_range: Set the soft frequency range of a घड़ी
	 *                               करोमुख्य in MHz.
	 */
	पूर्णांक (*set_soft_freq_limited_range)(काष्ठा smu_context *smu, क्रमागत smu_clk_type clk_type, uपूर्णांक32_t min, uपूर्णांक32_t max);

	/**
	 * @set_घातer_source: Notअगरy the SMU of the current घातer source.
	 */
	पूर्णांक (*set_घातer_source)(काष्ठा smu_context *smu, क्रमागत smu_घातer_src_type घातer_src);

	/**
	 * @log_thermal_throttling_event: Prपूर्णांक a thermal throttling warning to
	 *                                the प्रणाली's log.
	 */
	व्योम (*log_thermal_throttling_event)(काष्ठा smu_context *smu);

	/**
	 * @get_pp_feature_mask: Prपूर्णांक a human पढ़ोable table of enabled
	 *                       features to buffer.
	 */
	माप_प्रकार (*get_pp_feature_mask)(काष्ठा smu_context *smu, अक्षर *buf);

	/**
	 * @set_pp_feature_mask: Request the SMU enable/disable features to
	 *                       match those enabled in &new_mask.
	 */
	पूर्णांक (*set_pp_feature_mask)(काष्ठा smu_context *smu, uपूर्णांक64_t new_mask);

	/**
	 * @get_gpu_metrics: Get a copy of the GPU metrics table from the SMU.
	 *
	 * Return: Size of &table
	 */
	sमाप_प्रकार (*get_gpu_metrics)(काष्ठा smu_context *smu, व्योम **table);

	/**
	 * @enable_mgpu_fan_boost: Enable multi-GPU fan boost.
	 */
	पूर्णांक (*enable_mgpu_fan_boost)(काष्ठा smu_context *smu);

	/**
	 * @gfx_ulv_control: Enable/disable ultra low voltage.
	 */
	पूर्णांक (*gfx_ulv_control)(काष्ठा smu_context *smu, bool enablement);

	/**
	 * @deep_sleep_control: Enable/disable deep sleep.
	 */
	पूर्णांक (*deep_sleep_control)(काष्ठा smu_context *smu, bool enablement);

	/**
	 * @get_fan_parameters: Get fan parameters.
	 *
	 * Get maximum fan speed from the घातer play table.
	 */
	पूर्णांक (*get_fan_parameters)(काष्ठा smu_context *smu);

	/**
	 * @post_init: Helper function क्रम asic specअगरic workarounds.
	 */
	पूर्णांक (*post_init)(काष्ठा smu_context *smu);

	/**
	 * @पूर्णांकerrupt_work: Work task scheduled from SMU पूर्णांकerrupt handler.
	 */
	व्योम (*पूर्णांकerrupt_work)(काष्ठा smu_context *smu);

	/**
	 * @gpo_control: Enable/disable graphics घातer optimization अगर supported.
	 */
	पूर्णांक (*gpo_control)(काष्ठा smu_context *smu, bool enablement);

	/**
	 * @gfx_state_change_set: Send the current graphics state to the SMU.
	 */
	पूर्णांक (*gfx_state_change_set)(काष्ठा smu_context *smu, uपूर्णांक32_t state);

	/**
	 * @set_fine_grain_gfx_freq_parameters: Set fine grain graphics घड़ी
	 *                                      parameters to शेषs.
	 */
	पूर्णांक (*set_fine_grain_gfx_freq_parameters)(काष्ठा smu_context *smu);

	/**
	 * @set_light_sbr:  Set light sbr mode क्रम the SMU.
	 */
	पूर्णांक (*set_light_sbr)(काष्ठा smu_context *smu, bool enable);

	/**
	 * @रुको_क्रम_event:  Wait क्रम events from SMU.
	 */
	पूर्णांक (*रुको_क्रम_event)(काष्ठा smu_context *smu,
			      क्रमागत smu_event_type event, uपूर्णांक64_t event_arg);
पूर्ण;

प्रकार क्रमागत अणु
	METRICS_CURR_GFXCLK,
	METRICS_CURR_SOCCLK,
	METRICS_CURR_UCLK,
	METRICS_CURR_VCLK,
	METRICS_CURR_VCLK1,
	METRICS_CURR_DCLK,
	METRICS_CURR_DCLK1,
	METRICS_CURR_FCLK,
	METRICS_CURR_DCEFCLK,
	METRICS_AVERAGE_CPUCLK,
	METRICS_AVERAGE_GFXCLK,
	METRICS_AVERAGE_SOCCLK,
	METRICS_AVERAGE_FCLK,
	METRICS_AVERAGE_UCLK,
	METRICS_AVERAGE_VCLK,
	METRICS_AVERAGE_DCLK,
	METRICS_AVERAGE_GFXACTIVITY,
	METRICS_AVERAGE_MEMACTIVITY,
	METRICS_AVERAGE_VCNACTIVITY,
	METRICS_AVERAGE_SOCKETPOWER,
	METRICS_TEMPERATURE_EDGE,
	METRICS_TEMPERATURE_HOTSPOT,
	METRICS_TEMPERATURE_MEM,
	METRICS_TEMPERATURE_VRGFX,
	METRICS_TEMPERATURE_VRSOC,
	METRICS_TEMPERATURE_VRMEM,
	METRICS_THROTTLER_STATUS,
	METRICS_CURR_FANSPEED,
	METRICS_VOLTAGE_VDDSOC,
	METRICS_VOLTAGE_VDDGFX,
पूर्ण MetricsMember_t;

क्रमागत smu_cmn2asic_mapping_type अणु
	CMN2ASIC_MAPPING_MSG,
	CMN2ASIC_MAPPING_CLK,
	CMN2ASIC_MAPPING_FEATURE,
	CMN2ASIC_MAPPING_TABLE,
	CMN2ASIC_MAPPING_PWR,
	CMN2ASIC_MAPPING_WORKLOAD,
पूर्ण;

#घोषणा MSG_MAP(msg, index, valid_in_vf) \
	[SMU_MSG_##msg] = अणु1, (index), (valid_in_vf)पूर्ण

#घोषणा CLK_MAP(clk, index) \
	[SMU_##clk] = अणु1, (index)पूर्ण

#घोषणा FEA_MAP(fea) \
	[SMU_FEATURE_##fea##_BIT] = अणु1, FEATURE_##fea##_BITपूर्ण

#घोषणा FEA_MAP_REVERSE(fea) \
	[SMU_FEATURE_DPM_##fea##_BIT] = अणु1, FEATURE_##fea##_DPM_BITपूर्ण

#घोषणा FEA_MAP_HALF_REVERSE(fea) \
	[SMU_FEATURE_DPM_##fea##CLK_BIT] = अणु1, FEATURE_##fea##_DPM_BITपूर्ण

#घोषणा TAB_MAP(tab) \
	[SMU_TABLE_##tab] = अणु1, TABLE_##tabपूर्ण

#घोषणा TAB_MAP_VALID(tab) \
	[SMU_TABLE_##tab] = अणु1, TABLE_##tabपूर्ण

#घोषणा TAB_MAP_INVALID(tab) \
	[SMU_TABLE_##tab] = अणु0, TABLE_##tabपूर्ण

#घोषणा PWR_MAP(tab) \
	[SMU_POWER_SOURCE_##tab] = अणु1, POWER_SOURCE_##tabपूर्ण

#घोषणा WORKLOAD_MAP(profile, workload) \
	[profile] = अणु1, (workload)पूर्ण

#अगर !defined(SWSMU_CODE_LAYER_L2) && !defined(SWSMU_CODE_LAYER_L3) && !defined(SWSMU_CODE_LAYER_L4)
पूर्णांक smu_get_घातer_limit(काष्ठा smu_context *smu,
			uपूर्णांक32_t *limit,
			क्रमागत smu_ppt_limit_level limit_level);

bool smu_mode1_reset_is_support(काष्ठा smu_context *smu);
bool smu_mode2_reset_is_support(काष्ठा smu_context *smu);
पूर्णांक smu_mode1_reset(काष्ठा smu_context *smu);

बाह्य स्थिर काष्ठा amd_ip_funcs smu_ip_funcs;

बाह्य स्थिर काष्ठा amdgpu_ip_block_version smu_v11_0_ip_block;
बाह्य स्थिर काष्ठा amdgpu_ip_block_version smu_v12_0_ip_block;
बाह्य स्थिर काष्ठा amdgpu_ip_block_version smu_v13_0_ip_block;

bool is_support_sw_smu(काष्ठा amdgpu_device *adev);
bool is_support_cclk_dpm(काष्ठा amdgpu_device *adev);
पूर्णांक smu_ग_लिखो_watermarks_table(काष्ठा smu_context *smu);

पूर्णांक smu_get_dpm_freq_range(काष्ठा smu_context *smu, क्रमागत smu_clk_type clk_type,
			   uपूर्णांक32_t *min, uपूर्णांक32_t *max);

पूर्णांक smu_set_soft_freq_range(काष्ठा smu_context *smu, क्रमागत smu_clk_type clk_type,
			    uपूर्णांक32_t min, uपूर्णांक32_t max);

पूर्णांक smu_set_ac_dc(काष्ठा smu_context *smu);

पूर्णांक smu_allow_xgmi_घातer_करोwn(काष्ठा smu_context *smu, bool en);

पूर्णांक smu_get_status_gfxoff(काष्ठा amdgpu_device *adev, uपूर्णांक32_t *value);

पूर्णांक smu_set_light_sbr(काष्ठा smu_context *smu, bool enable);

पूर्णांक smu_रुको_क्रम_event(काष्ठा amdgpu_device *adev, क्रमागत smu_event_type event,
		       uपूर्णांक64_t event_arg);

#पूर्ण_अगर
#पूर्ण_अगर
