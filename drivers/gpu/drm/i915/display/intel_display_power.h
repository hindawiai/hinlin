<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/*
 * Copyright तऊ 2019 Intel Corporation
 */

#अगर_अघोषित __INTEL_DISPLAY_POWER_H__
#घोषणा __INTEL_DISPLAY_POWER_H__

#समावेश "intel_display.h"
#समावेश "intel_runtime_pm.h"
#समावेश "i915_reg.h"

काष्ठा drm_i915_निजी;
काष्ठा पूर्णांकel_encoder;

क्रमागत पूर्णांकel_display_घातer_करोमुख्य अणु
	POWER_DOMAIN_DISPLAY_CORE,
	POWER_DOMAIN_PIPE_A,
	POWER_DOMAIN_PIPE_B,
	POWER_DOMAIN_PIPE_C,
	POWER_DOMAIN_PIPE_D,
	POWER_DOMAIN_PIPE_A_PANEL_FITTER,
	POWER_DOMAIN_PIPE_B_PANEL_FITTER,
	POWER_DOMAIN_PIPE_C_PANEL_FITTER,
	POWER_DOMAIN_PIPE_D_PANEL_FITTER,
	POWER_DOMAIN_TRANSCODER_A,
	POWER_DOMAIN_TRANSCODER_B,
	POWER_DOMAIN_TRANSCODER_C,
	POWER_DOMAIN_TRANSCODER_D,
	POWER_DOMAIN_TRANSCODER_EDP,
	/* VDSC/joining क्रम eDP/DSI transcoder (ICL) or pipe A (TGL) */
	POWER_DOMAIN_TRANSCODER_VDSC_PW2,
	POWER_DOMAIN_TRANSCODER_DSI_A,
	POWER_DOMAIN_TRANSCODER_DSI_C,
	POWER_DOMAIN_PORT_DDI_A_LANES,
	POWER_DOMAIN_PORT_DDI_B_LANES,
	POWER_DOMAIN_PORT_DDI_C_LANES,
	POWER_DOMAIN_PORT_DDI_D_LANES,
	POWER_DOMAIN_PORT_DDI_E_LANES,
	POWER_DOMAIN_PORT_DDI_F_LANES,
	POWER_DOMAIN_PORT_DDI_G_LANES,
	POWER_DOMAIN_PORT_DDI_H_LANES,
	POWER_DOMAIN_PORT_DDI_I_LANES,

	POWER_DOMAIN_PORT_DDI_LANES_TC1 = POWER_DOMAIN_PORT_DDI_D_LANES, /* tgl+ */
	POWER_DOMAIN_PORT_DDI_LANES_TC2,
	POWER_DOMAIN_PORT_DDI_LANES_TC3,
	POWER_DOMAIN_PORT_DDI_LANES_TC4,
	POWER_DOMAIN_PORT_DDI_LANES_TC5,
	POWER_DOMAIN_PORT_DDI_LANES_TC6,

	POWER_DOMAIN_PORT_DDI_A_IO,
	POWER_DOMAIN_PORT_DDI_B_IO,
	POWER_DOMAIN_PORT_DDI_C_IO,
	POWER_DOMAIN_PORT_DDI_D_IO,
	POWER_DOMAIN_PORT_DDI_E_IO,
	POWER_DOMAIN_PORT_DDI_F_IO,
	POWER_DOMAIN_PORT_DDI_G_IO,
	POWER_DOMAIN_PORT_DDI_H_IO,
	POWER_DOMAIN_PORT_DDI_I_IO,

	POWER_DOMAIN_PORT_DDI_IO_TC1 = POWER_DOMAIN_PORT_DDI_D_IO, /* tgl+ */
	POWER_DOMAIN_PORT_DDI_IO_TC2,
	POWER_DOMAIN_PORT_DDI_IO_TC3,
	POWER_DOMAIN_PORT_DDI_IO_TC4,
	POWER_DOMAIN_PORT_DDI_IO_TC5,
	POWER_DOMAIN_PORT_DDI_IO_TC6,

	POWER_DOMAIN_PORT_DSI,
	POWER_DOMAIN_PORT_CRT,
	POWER_DOMAIN_PORT_OTHER,
	POWER_DOMAIN_VGA,
	POWER_DOMAIN_AUDIO,
	POWER_DOMAIN_AUX_A,
	POWER_DOMAIN_AUX_B,
	POWER_DOMAIN_AUX_C,
	POWER_DOMAIN_AUX_D,
	POWER_DOMAIN_AUX_E,
	POWER_DOMAIN_AUX_F,
	POWER_DOMAIN_AUX_G,
	POWER_DOMAIN_AUX_H,
	POWER_DOMAIN_AUX_I,

	POWER_DOMAIN_AUX_USBC1 = POWER_DOMAIN_AUX_D, /* tgl+ */
	POWER_DOMAIN_AUX_USBC2,
	POWER_DOMAIN_AUX_USBC3,
	POWER_DOMAIN_AUX_USBC4,
	POWER_DOMAIN_AUX_USBC5,
	POWER_DOMAIN_AUX_USBC6,

	POWER_DOMAIN_AUX_IO_A,
	POWER_DOMAIN_AUX_C_TBT,
	POWER_DOMAIN_AUX_D_TBT,
	POWER_DOMAIN_AUX_E_TBT,
	POWER_DOMAIN_AUX_F_TBT,
	POWER_DOMAIN_AUX_G_TBT,
	POWER_DOMAIN_AUX_H_TBT,
	POWER_DOMAIN_AUX_I_TBT,

	POWER_DOMAIN_AUX_TBT1 = POWER_DOMAIN_AUX_D_TBT, /* tgl+ */
	POWER_DOMAIN_AUX_TBT2,
	POWER_DOMAIN_AUX_TBT3,
	POWER_DOMAIN_AUX_TBT4,
	POWER_DOMAIN_AUX_TBT5,
	POWER_DOMAIN_AUX_TBT6,

	POWER_DOMAIN_GMBUS,
	POWER_DOMAIN_MODESET,
	POWER_DOMAIN_GT_IRQ,
	POWER_DOMAIN_DPLL_DC_OFF,
	POWER_DOMAIN_TC_COLD_OFF,
	POWER_DOMAIN_INIT,

	POWER_DOMAIN_NUM,
पूर्ण;

/*
 * i915_घातer_well_id:
 *
 * IDs used to look up घातer wells. Power wells accessed directly bypassing
 * the घातer करोमुख्यs framework must be asचिन्हित a unique ID. The rest of घातer
 * wells must be asचिन्हित DISP_PW_ID_NONE.
 */
क्रमागत i915_घातer_well_id अणु
	DISP_PW_ID_NONE,

	VLV_DISP_PW_DISP2D,
	BXT_DISP_PW_DPIO_CMN_A,
	VLV_DISP_PW_DPIO_CMN_BC,
	GLK_DISP_PW_DPIO_CMN_C,
	CHV_DISP_PW_DPIO_CMN_D,
	HSW_DISP_PW_GLOBAL,
	SKL_DISP_PW_MISC_IO,
	SKL_DISP_PW_1,
	SKL_DISP_PW_2,
	CNL_DISP_PW_DDI_F_IO,
	CNL_DISP_PW_DDI_F_AUX,
	ICL_DISP_PW_3,
	SKL_DISP_DC_OFF,
	TGL_DISP_PW_TC_COLD_OFF,
पूर्ण;

#घोषणा POWER_DOMAIN_PIPE(pipe) ((pipe) + POWER_DOMAIN_PIPE_A)
#घोषणा POWER_DOMAIN_PIPE_PANEL_FITTER(pipe) \
		((pipe) + POWER_DOMAIN_PIPE_A_PANEL_FITTER)
#घोषणा POWER_DOMAIN_TRANSCODER(tran) \
	((tran) == TRANSCODER_EDP ? POWER_DOMAIN_TRANSCODER_EDP : \
	 (tran) + POWER_DOMAIN_TRANSCODER_A)

काष्ठा i915_घातer_well;

काष्ठा i915_घातer_well_ops अणु
	/*
	 * Synchronize the well's hw state to match the current sw state, क्रम
	 * example enable/disable it based on the current refcount. Called
	 * during driver init and resume समय, possibly after first calling
	 * the enable/disable handlers.
	 */
	व्योम (*sync_hw)(काष्ठा drm_i915_निजी *dev_priv,
			काष्ठा i915_घातer_well *घातer_well);
	/*
	 * Enable the well and resources that depend on it (क्रम example
	 * पूर्णांकerrupts located on the well). Called after the 0->1 refcount
	 * transition.
	 */
	व्योम (*enable)(काष्ठा drm_i915_निजी *dev_priv,
		       काष्ठा i915_घातer_well *घातer_well);
	/*
	 * Disable the well and resources that depend on it. Called after
	 * the 1->0 refcount transition.
	 */
	व्योम (*disable)(काष्ठा drm_i915_निजी *dev_priv,
			काष्ठा i915_घातer_well *घातer_well);
	/* Returns the hw enabled state. */
	bool (*is_enabled)(काष्ठा drm_i915_निजी *dev_priv,
			   काष्ठा i915_घातer_well *घातer_well);
पूर्ण;

काष्ठा i915_घातer_well_regs अणु
	i915_reg_t bios;
	i915_reg_t driver;
	i915_reg_t kvmr;
	i915_reg_t debug;
पूर्ण;

/* Power well काष्ठाure क्रम haswell */
काष्ठा i915_घातer_well_desc अणु
	स्थिर अक्षर *name;
	bool always_on;
	u64 करोमुख्यs;
	/* unique identअगरier क्रम this घातer well */
	क्रमागत i915_घातer_well_id id;
	/*
	 * Arbitraty data associated with this घातer well. Platक्रमm and घातer
	 * well specअगरic.
	 */
	जोड़ अणु
		काष्ठा अणु
			/*
			 * request/status flag index in the PUNIT घातer well
			 * control/status रेजिस्टरs.
			 */
			u8 idx;
		पूर्ण vlv;
		काष्ठा अणु
			क्रमागत dpio_phy phy;
		पूर्ण bxt;
		काष्ठा अणु
			स्थिर काष्ठा i915_घातer_well_regs *regs;
			/*
			 * request/status flag index in the घातer well
			 * स्थिरrol/status रेजिस्टरs.
			 */
			u8 idx;
			/* Mask of pipes whose IRQ logic is backed by the pw */
			u8 irq_pipe_mask;
			/* The pw is backing the VGA functionality */
			bool has_vga:1;
			bool has_fuses:1;
			/*
			 * The pw is क्रम an ICL+ TypeC PHY port in
			 * Thunderbolt mode.
			 */
			bool is_tc_tbt:1;
		पूर्ण hsw;
	पूर्ण;
	स्थिर काष्ठा i915_घातer_well_ops *ops;
पूर्ण;

काष्ठा i915_घातer_well अणु
	स्थिर काष्ठा i915_घातer_well_desc *desc;
	/* घातer well enable/disable usage count */
	पूर्णांक count;
	/* cached hw enabled state */
	bool hw_enabled;
पूर्ण;

काष्ठा i915_घातer_करोमुख्यs अणु
	/*
	 * Power wells needed क्रम initialization at driver init and suspend
	 * समय are on. They are kept on until after the first modeset.
	 */
	bool initializing;
	bool display_core_suspended;
	पूर्णांक घातer_well_count;

	पूर्णांकel_wakeref_t init_wakeref;
	पूर्णांकel_wakeref_t disable_wakeref;

	काष्ठा mutex lock;
	पूर्णांक करोमुख्य_use_count[POWER_DOMAIN_NUM];

	काष्ठा delayed_work async_put_work;
	पूर्णांकel_wakeref_t async_put_wakeref;
	u64 async_put_करोमुख्यs[2];

	काष्ठा i915_घातer_well *घातer_wells;
पूर्ण;

काष्ठा पूर्णांकel_display_घातer_करोमुख्य_set अणु
	u64 mask;
#अगर_घोषित CONFIG_DRM_I915_DEBUG_RUNTIME_PM
	पूर्णांकel_wakeref_t wakerefs[POWER_DOMAIN_NUM];
#पूर्ण_अगर
पूर्ण;

#घोषणा क्रम_each_घातer_करोमुख्य(करोमुख्य, mask)				\
	क्रम ((करोमुख्य) = 0; (करोमुख्य) < POWER_DOMAIN_NUM; (करोमुख्य)++)	\
		क्रम_each_अगर(BIT_ULL(करोमुख्य) & (mask))

#घोषणा क्रम_each_घातer_well(__dev_priv, __घातer_well)				\
	क्रम ((__घातer_well) = (__dev_priv)->घातer_करोमुख्यs.घातer_wells;	\
	     (__घातer_well) - (__dev_priv)->घातer_करोमुख्यs.घातer_wells <	\
		(__dev_priv)->घातer_करोमुख्यs.घातer_well_count;		\
	     (__घातer_well)++)

#घोषणा क्रम_each_घातer_well_reverse(__dev_priv, __घातer_well)			\
	क्रम ((__घातer_well) = (__dev_priv)->घातer_करोमुख्यs.घातer_wells +		\
			      (__dev_priv)->घातer_करोमुख्यs.घातer_well_count - 1;	\
	     (__घातer_well) - (__dev_priv)->घातer_करोमुख्यs.घातer_wells >= 0;	\
	     (__घातer_well)--)

#घोषणा क्रम_each_घातer_करोमुख्य_well(__dev_priv, __घातer_well, __करोमुख्य_mask)	\
	क्रम_each_घातer_well(__dev_priv, __घातer_well)				\
		क्रम_each_अगर((__घातer_well)->desc->करोमुख्यs & (__करोमुख्य_mask))

#घोषणा क्रम_each_घातer_करोमुख्य_well_reverse(__dev_priv, __घातer_well, __करोमुख्य_mask) \
	क्रम_each_घातer_well_reverse(__dev_priv, __घातer_well)		        \
		क्रम_each_अगर((__घातer_well)->desc->करोमुख्यs & (__करोमुख्य_mask))

पूर्णांक पूर्णांकel_घातer_करोमुख्यs_init(काष्ठा drm_i915_निजी *dev_priv);
व्योम पूर्णांकel_घातer_करोमुख्यs_cleanup(काष्ठा drm_i915_निजी *dev_priv);
व्योम पूर्णांकel_घातer_करोमुख्यs_init_hw(काष्ठा drm_i915_निजी *dev_priv, bool resume);
व्योम पूर्णांकel_घातer_करोमुख्यs_driver_हटाओ(काष्ठा drm_i915_निजी *dev_priv);
व्योम पूर्णांकel_घातer_करोमुख्यs_enable(काष्ठा drm_i915_निजी *dev_priv);
व्योम पूर्णांकel_घातer_करोमुख्यs_disable(काष्ठा drm_i915_निजी *dev_priv);
व्योम पूर्णांकel_घातer_करोमुख्यs_suspend(काष्ठा drm_i915_निजी *dev_priv,
				 क्रमागत i915_drm_suspend_mode);
व्योम पूर्णांकel_घातer_करोमुख्यs_resume(काष्ठा drm_i915_निजी *dev_priv);

व्योम पूर्णांकel_display_घातer_suspend_late(काष्ठा drm_i915_निजी *i915);
व्योम पूर्णांकel_display_घातer_resume_early(काष्ठा drm_i915_निजी *i915);
व्योम पूर्णांकel_display_घातer_suspend(काष्ठा drm_i915_निजी *i915);
व्योम पूर्णांकel_display_घातer_resume(काष्ठा drm_i915_निजी *i915);
व्योम पूर्णांकel_display_घातer_set_target_dc_state(काष्ठा drm_i915_निजी *dev_priv,
					     u32 state);

स्थिर अक्षर *
पूर्णांकel_display_घातer_करोमुख्य_str(क्रमागत पूर्णांकel_display_घातer_करोमुख्य करोमुख्य);

bool पूर्णांकel_display_घातer_is_enabled(काष्ठा drm_i915_निजी *dev_priv,
				    क्रमागत पूर्णांकel_display_घातer_करोमुख्य करोमुख्य);
bool पूर्णांकel_display_घातer_well_is_enabled(काष्ठा drm_i915_निजी *dev_priv,
					 क्रमागत i915_घातer_well_id घातer_well_id);
bool __पूर्णांकel_display_घातer_is_enabled(काष्ठा drm_i915_निजी *dev_priv,
				      क्रमागत पूर्णांकel_display_घातer_करोमुख्य करोमुख्य);
पूर्णांकel_wakeref_t पूर्णांकel_display_घातer_get(काष्ठा drm_i915_निजी *dev_priv,
					क्रमागत पूर्णांकel_display_घातer_करोमुख्य करोमुख्य);
पूर्णांकel_wakeref_t
पूर्णांकel_display_घातer_get_अगर_enabled(काष्ठा drm_i915_निजी *dev_priv,
				   क्रमागत पूर्णांकel_display_घातer_करोमुख्य करोमुख्य);
व्योम __पूर्णांकel_display_घातer_put_async(काष्ठा drm_i915_निजी *i915,
				     क्रमागत पूर्णांकel_display_घातer_करोमुख्य करोमुख्य,
				     पूर्णांकel_wakeref_t wakeref);
व्योम पूर्णांकel_display_घातer_flush_work(काष्ठा drm_i915_निजी *i915);
#अगर IS_ENABLED(CONFIG_DRM_I915_DEBUG_RUNTIME_PM)
व्योम पूर्णांकel_display_घातer_put(काष्ठा drm_i915_निजी *dev_priv,
			     क्रमागत पूर्णांकel_display_घातer_करोमुख्य करोमुख्य,
			     पूर्णांकel_wakeref_t wakeref);
अटल अंतरभूत व्योम
पूर्णांकel_display_घातer_put_async(काष्ठा drm_i915_निजी *i915,
			      क्रमागत पूर्णांकel_display_घातer_करोमुख्य करोमुख्य,
			      पूर्णांकel_wakeref_t wakeref)
अणु
	__पूर्णांकel_display_घातer_put_async(i915, करोमुख्य, wakeref);
पूर्ण
#अन्यथा
व्योम पूर्णांकel_display_घातer_put_unchecked(काष्ठा drm_i915_निजी *dev_priv,
				       क्रमागत पूर्णांकel_display_घातer_करोमुख्य करोमुख्य);

अटल अंतरभूत व्योम
पूर्णांकel_display_घातer_put(काष्ठा drm_i915_निजी *i915,
			क्रमागत पूर्णांकel_display_घातer_करोमुख्य करोमुख्य,
			पूर्णांकel_wakeref_t wakeref)
अणु
	पूर्णांकel_display_घातer_put_unchecked(i915, करोमुख्य);
पूर्ण

अटल अंतरभूत व्योम
पूर्णांकel_display_घातer_put_async(काष्ठा drm_i915_निजी *i915,
			      क्रमागत पूर्णांकel_display_घातer_करोमुख्य करोमुख्य,
			      पूर्णांकel_wakeref_t wakeref)
अणु
	__पूर्णांकel_display_घातer_put_async(i915, करोमुख्य, -1);
पूर्ण
#पूर्ण_अगर

व्योम
पूर्णांकel_display_घातer_get_in_set(काष्ठा drm_i915_निजी *i915,
			       काष्ठा पूर्णांकel_display_घातer_करोमुख्य_set *घातer_करोमुख्य_set,
			       क्रमागत पूर्णांकel_display_घातer_करोमुख्य करोमुख्य);

bool
पूर्णांकel_display_घातer_get_in_set_अगर_enabled(काष्ठा drm_i915_निजी *i915,
					  काष्ठा पूर्णांकel_display_घातer_करोमुख्य_set *घातer_करोमुख्य_set,
					  क्रमागत पूर्णांकel_display_घातer_करोमुख्य करोमुख्य);

व्योम
पूर्णांकel_display_घातer_put_mask_in_set(काष्ठा drm_i915_निजी *i915,
				    काष्ठा पूर्णांकel_display_घातer_करोमुख्य_set *घातer_करोमुख्य_set,
				    u64 mask);

अटल अंतरभूत व्योम
पूर्णांकel_display_घातer_put_all_in_set(काष्ठा drm_i915_निजी *i915,
				   काष्ठा पूर्णांकel_display_घातer_करोमुख्य_set *घातer_करोमुख्य_set)
अणु
	पूर्णांकel_display_घातer_put_mask_in_set(i915, घातer_करोमुख्य_set, घातer_करोमुख्य_set->mask);
पूर्ण

क्रमागत dbuf_slice अणु
	DBUF_S1,
	DBUF_S2,
	I915_MAX_DBUF_SLICES
पूर्ण;

व्योम gen9_dbuf_slices_update(काष्ठा drm_i915_निजी *dev_priv,
			     u8 req_slices);

#घोषणा with_पूर्णांकel_display_घातer(i915, करोमुख्य, wf) \
	क्रम ((wf) = पूर्णांकel_display_घातer_get((i915), (करोमुख्य)); (wf); \
	     पूर्णांकel_display_घातer_put_async((i915), (करोमुख्य), (wf)), (wf) = 0)

व्योम chv_phy_घातergate_lanes(काष्ठा पूर्णांकel_encoder *encoder,
			     bool override, अचिन्हित पूर्णांक mask);
bool chv_phy_घातergate_ch(काष्ठा drm_i915_निजी *dev_priv, क्रमागत dpio_phy phy,
			  क्रमागत dpio_channel ch, bool override);

#पूर्ण_अगर /* __INTEL_DISPLAY_POWER_H__ */
