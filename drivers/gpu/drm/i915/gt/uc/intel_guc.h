<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/*
 * Copyright तऊ 2014-2019 Intel Corporation
 */

#अगर_अघोषित _INTEL_GUC_H_
#घोषणा _INTEL_GUC_H_

#समावेश "intel_uncore.h"
#समावेश "intel_guc_fw.h"
#समावेश "intel_guc_fwif.h"
#समावेश "intel_guc_ct.h"
#समावेश "intel_guc_log.h"
#समावेश "intel_guc_reg.h"
#समावेश "intel_uc_fw.h"
#समावेश "i915_utils.h"
#समावेश "i915_vma.h"

काष्ठा __guc_ads_blob;

/*
 * Top level काष्ठाure of GuC. It handles firmware loading and manages client
 * pool. पूर्णांकel_guc owns a पूर्णांकel_guc_client to replace the legacy ExecList
 * submission.
 */
काष्ठा पूर्णांकel_guc अणु
	काष्ठा पूर्णांकel_uc_fw fw;
	काष्ठा पूर्णांकel_guc_log log;
	काष्ठा पूर्णांकel_guc_ct ct;

	/* पूर्णांकel_guc_recv पूर्णांकerrupt related state */
	spinlock_t irq_lock;
	अचिन्हित पूर्णांक msg_enabled_mask;

	काष्ठा अणु
		bool enabled;
		व्योम (*reset)(काष्ठा पूर्णांकel_guc *guc);
		व्योम (*enable)(काष्ठा पूर्णांकel_guc *guc);
		व्योम (*disable)(काष्ठा पूर्णांकel_guc *guc);
	पूर्ण पूर्णांकerrupts;

	bool submission_selected;

	काष्ठा i915_vma *ads_vma;
	काष्ठा __guc_ads_blob *ads_blob;

	काष्ठा i915_vma *stage_desc_pool;
	व्योम *stage_desc_pool_vaddr;

	/* Control params क्रम fw initialization */
	u32 params[GUC_CTL_MAX_DWORDS];

	/* GuC's FW specअगरic रेजिस्टरs used in MMIO send */
	काष्ठा अणु
		u32 base;
		अचिन्हित पूर्णांक count;
		क्रमागत क्रमcewake_करोमुख्यs fw_करोमुख्यs;
	पूर्ण send_regs;

	/* रेजिस्टर used to send पूर्णांकerrupts to the GuC FW */
	i915_reg_t notअगरy_reg;

	/* Store msg (e.g. log flush) that we see जबतक CTBs are disabled */
	u32 mmio_msg;

	/* To serialize the पूर्णांकel_guc_send actions */
	काष्ठा mutex send_mutex;
पूर्ण;

अटल अंतरभूत काष्ठा पूर्णांकel_guc *log_to_guc(काष्ठा पूर्णांकel_guc_log *log)
अणु
	वापस container_of(log, काष्ठा पूर्णांकel_guc, log);
पूर्ण

अटल
अंतरभूत पूर्णांक पूर्णांकel_guc_send(काष्ठा पूर्णांकel_guc *guc, स्थिर u32 *action, u32 len)
अणु
	वापस पूर्णांकel_guc_ct_send(&guc->ct, action, len, शून्य, 0);
पूर्ण

अटल अंतरभूत पूर्णांक
पूर्णांकel_guc_send_and_receive(काष्ठा पूर्णांकel_guc *guc, स्थिर u32 *action, u32 len,
			   u32 *response_buf, u32 response_buf_size)
अणु
	वापस पूर्णांकel_guc_ct_send(&guc->ct, action, len,
				 response_buf, response_buf_size);
पूर्ण

अटल अंतरभूत व्योम पूर्णांकel_guc_to_host_event_handler(काष्ठा पूर्णांकel_guc *guc)
अणु
	पूर्णांकel_guc_ct_event_handler(&guc->ct);
पूर्ण

/* GuC addresses above GUC_GGTT_TOP also करोn't map through the GTT */
#घोषणा GUC_GGTT_TOP	0xFEE00000

/**
 * पूर्णांकel_guc_ggtt_offset() - Get and validate the GGTT offset of @vma
 * @guc: पूर्णांकel_guc काष्ठाure.
 * @vma: i915 graphics भव memory area.
 *
 * GuC करोes not allow any gfx GGTT address that falls पूर्णांकo range
 * [0, ggtt.pin_bias), which is reserved क्रम Boot ROM, SRAM and WOPCM.
 * Currently, in order to exclude [0, ggtt.pin_bias) address space from
 * GGTT, all gfx objects used by GuC are allocated with पूर्णांकel_guc_allocate_vma()
 * and pinned with PIN_OFFSET_BIAS aदीर्घ with the value of ggtt.pin_bias.
 *
 * Return: GGTT offset of the @vma.
 */
अटल अंतरभूत u32 पूर्णांकel_guc_ggtt_offset(काष्ठा पूर्णांकel_guc *guc,
					काष्ठा i915_vma *vma)
अणु
	u32 offset = i915_ggtt_offset(vma);

	GEM_BUG_ON(offset < i915_ggtt_pin_bias(vma));
	GEM_BUG_ON(range_overflows_t(u64, offset, vma->size, GUC_GGTT_TOP));

	वापस offset;
पूर्ण

व्योम पूर्णांकel_guc_init_early(काष्ठा पूर्णांकel_guc *guc);
व्योम पूर्णांकel_guc_init_send_regs(काष्ठा पूर्णांकel_guc *guc);
व्योम पूर्णांकel_guc_ग_लिखो_params(काष्ठा पूर्णांकel_guc *guc);
पूर्णांक पूर्णांकel_guc_init(काष्ठा पूर्णांकel_guc *guc);
व्योम पूर्णांकel_guc_fini(काष्ठा पूर्णांकel_guc *guc);
व्योम पूर्णांकel_guc_notअगरy(काष्ठा पूर्णांकel_guc *guc);
पूर्णांक पूर्णांकel_guc_send_mmio(काष्ठा पूर्णांकel_guc *guc, स्थिर u32 *action, u32 len,
			u32 *response_buf, u32 response_buf_size);
पूर्णांक पूर्णांकel_guc_to_host_process_recv_msg(काष्ठा पूर्णांकel_guc *guc,
				       स्थिर u32 *payload, u32 len);
पूर्णांक पूर्णांकel_guc_sample_क्रमcewake(काष्ठा पूर्णांकel_guc *guc);
पूर्णांक पूर्णांकel_guc_auth_huc(काष्ठा पूर्णांकel_guc *guc, u32 rsa_offset);
पूर्णांक पूर्णांकel_guc_suspend(काष्ठा पूर्णांकel_guc *guc);
पूर्णांक पूर्णांकel_guc_resume(काष्ठा पूर्णांकel_guc *guc);
काष्ठा i915_vma *पूर्णांकel_guc_allocate_vma(काष्ठा पूर्णांकel_guc *guc, u32 size);
पूर्णांक पूर्णांकel_guc_allocate_and_map_vma(काष्ठा पूर्णांकel_guc *guc, u32 size,
				   काष्ठा i915_vma **out_vma, व्योम **out_vaddr);

अटल अंतरभूत bool पूर्णांकel_guc_is_supported(काष्ठा पूर्णांकel_guc *guc)
अणु
	वापस पूर्णांकel_uc_fw_is_supported(&guc->fw);
पूर्ण

अटल अंतरभूत bool पूर्णांकel_guc_is_wanted(काष्ठा पूर्णांकel_guc *guc)
अणु
	वापस पूर्णांकel_uc_fw_is_enabled(&guc->fw);
पूर्ण

अटल अंतरभूत bool पूर्णांकel_guc_is_used(काष्ठा पूर्णांकel_guc *guc)
अणु
	GEM_BUG_ON(__पूर्णांकel_uc_fw_status(&guc->fw) == INTEL_UC_FIRMWARE_SELECTED);
	वापस पूर्णांकel_uc_fw_is_available(&guc->fw);
पूर्ण

अटल अंतरभूत bool पूर्णांकel_guc_is_fw_running(काष्ठा पूर्णांकel_guc *guc)
अणु
	वापस पूर्णांकel_uc_fw_is_running(&guc->fw);
पूर्ण

अटल अंतरभूत bool पूर्णांकel_guc_is_पढ़ोy(काष्ठा पूर्णांकel_guc *guc)
अणु
	वापस पूर्णांकel_guc_is_fw_running(guc) && पूर्णांकel_guc_ct_enabled(&guc->ct);
पूर्ण

अटल अंतरभूत पूर्णांक पूर्णांकel_guc_sanitize(काष्ठा पूर्णांकel_guc *guc)
अणु
	पूर्णांकel_uc_fw_sanitize(&guc->fw);
	पूर्णांकel_guc_ct_sanitize(&guc->ct);
	guc->mmio_msg = 0;

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम पूर्णांकel_guc_enable_msg(काष्ठा पूर्णांकel_guc *guc, u32 mask)
अणु
	spin_lock_irq(&guc->irq_lock);
	guc->msg_enabled_mask |= mask;
	spin_unlock_irq(&guc->irq_lock);
पूर्ण

अटल अंतरभूत व्योम पूर्णांकel_guc_disable_msg(काष्ठा पूर्णांकel_guc *guc, u32 mask)
अणु
	spin_lock_irq(&guc->irq_lock);
	guc->msg_enabled_mask &= ~mask;
	spin_unlock_irq(&guc->irq_lock);
पूर्ण

पूर्णांक पूर्णांकel_guc_reset_engine(काष्ठा पूर्णांकel_guc *guc,
			   काष्ठा पूर्णांकel_engine_cs *engine);

व्योम पूर्णांकel_guc_load_status(काष्ठा पूर्णांकel_guc *guc, काष्ठा drm_prपूर्णांकer *p);

#पूर्ण_अगर
