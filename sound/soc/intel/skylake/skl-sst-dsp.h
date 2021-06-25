<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Skylake SST DSP Support
 *
 * Copyright (C) 2014-15, Intel Corporation.
 */

#अगर_अघोषित __SKL_SST_DSP_H__
#घोषणा __SKL_SST_DSP_H__

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/uuid.h>
#समावेश <linux/firmware.h>
#समावेश <sound/meदो_स्मृति.h>
#समावेश "skl-sst-cldma.h"

काष्ठा sst_dsp;
काष्ठा sst_dsp_device;
काष्ठा skl_lib_info;
काष्ठा skl_dev;

/* Intel HD Audio General DSP Registers */
#घोषणा SKL_ADSP_GEN_BASE		0x0
#घोषणा SKL_ADSP_REG_ADSPCS		(SKL_ADSP_GEN_BASE + 0x04)
#घोषणा SKL_ADSP_REG_ADSPIC		(SKL_ADSP_GEN_BASE + 0x08)
#घोषणा SKL_ADSP_REG_ADSPIS		(SKL_ADSP_GEN_BASE + 0x0C)
#घोषणा SKL_ADSP_REG_ADSPIC2		(SKL_ADSP_GEN_BASE + 0x10)
#घोषणा SKL_ADSP_REG_ADSPIS2		(SKL_ADSP_GEN_BASE + 0x14)

/* Intel HD Audio Inter-Processor Communication Registers */
#घोषणा SKL_ADSP_IPC_BASE		0x40
#घोषणा SKL_ADSP_REG_HIPCT		(SKL_ADSP_IPC_BASE + 0x00)
#घोषणा SKL_ADSP_REG_HIPCTE		(SKL_ADSP_IPC_BASE + 0x04)
#घोषणा SKL_ADSP_REG_HIPCI		(SKL_ADSP_IPC_BASE + 0x08)
#घोषणा SKL_ADSP_REG_HIPCIE		(SKL_ADSP_IPC_BASE + 0x0C)
#घोषणा SKL_ADSP_REG_HIPCCTL		(SKL_ADSP_IPC_BASE + 0x10)

/*  HIPCI */
#घोषणा SKL_ADSP_REG_HIPCI_BUSY		BIT(31)

/* HIPCIE */
#घोषणा SKL_ADSP_REG_HIPCIE_DONE	BIT(30)

/* HIPCCTL */
#घोषणा SKL_ADSP_REG_HIPCCTL_DONE	BIT(1)
#घोषणा SKL_ADSP_REG_HIPCCTL_BUSY	BIT(0)

/* HIPCT */
#घोषणा SKL_ADSP_REG_HIPCT_BUSY		BIT(31)

/* FW base IDs */
#घोषणा SKL_INSTANCE_ID			0
#घोषणा SKL_BASE_FW_MODULE_ID		0

/* Intel HD Audio SRAM Winकरोw 1 */
#घोषणा SKL_ADSP_SRAM1_BASE		0xA000

#घोषणा SKL_ADSP_MMIO_LEN		0x10000

#घोषणा SKL_ADSP_W0_STAT_SZ		0x1000

#घोषणा SKL_ADSP_W0_UP_SZ		0x1000

#घोषणा SKL_ADSP_W1_SZ			0x1000

#घोषणा SKL_FW_STS_MASK			0xf

#घोषणा SKL_FW_INIT			0x1
#घोषणा SKL_FW_RFW_START		0xf
#घोषणा BXT_FW_ROM_INIT_RETRY		3
#घोषणा BXT_INIT_TIMEOUT		300

#घोषणा SKL_ADSPIC_IPC			1
#घोषणा SKL_ADSPIS_IPC			1

/* Core ID of core0 */
#घोषणा SKL_DSP_CORE0_ID		0

/* Mask क्रम a given core index, c = 0.. number of supported cores - 1 */
#घोषणा SKL_DSP_CORE_MASK(c)		BIT(c)

/*
 * Core 0 mask = SKL_DSP_CORE_MASK(0); Defined separately
 * since Core0 is primary core and it is used often
 */
#घोषणा SKL_DSP_CORE0_MASK		BIT(0)

/*
 * Mask क्रम a given number of cores
 * nc = number of supported cores
 */
#घोषणा SKL_DSP_CORES_MASK(nc)	GENMASK((nc - 1), 0)

/* ADSPCS - Audio DSP Control & Status */

/*
 * Core Reset - निश्चितed high
 * CRST Mask क्रम a given core mask pattern, cm
 */
#घोषणा SKL_ADSPCS_CRST_SHIFT		0
#घोषणा SKL_ADSPCS_CRST_MASK(cm)	((cm) << SKL_ADSPCS_CRST_SHIFT)

/*
 * Core run/stall - when set to '1' core is stalled
 * CSTALL Mask क्रम a given core mask pattern, cm
 */
#घोषणा SKL_ADSPCS_CSTALL_SHIFT		8
#घोषणा SKL_ADSPCS_CSTALL_MASK(cm)	((cm) << SKL_ADSPCS_CSTALL_SHIFT)

/*
 * Set Power Active - when set to '1' turn cores on
 * SPA Mask क्रम a given core mask pattern, cm
 */
#घोषणा SKL_ADSPCS_SPA_SHIFT		16
#घोषणा SKL_ADSPCS_SPA_MASK(cm)		((cm) << SKL_ADSPCS_SPA_SHIFT)

/*
 * Current Power Active - घातer status of cores, set by hardware
 * CPA Mask क्रम a given core mask pattern, cm
 */
#घोषणा SKL_ADSPCS_CPA_SHIFT		24
#घोषणा SKL_ADSPCS_CPA_MASK(cm)		((cm) << SKL_ADSPCS_CPA_SHIFT)

/* DSP Core state */
क्रमागत skl_dsp_states अणु
	SKL_DSP_RUNNING = 1,
	/* Running in D0i3 state; can be in streaming or non-streaming D0i3 */
	SKL_DSP_RUNNING_D0I3, /* Running in D0i3 state*/
	SKL_DSP_RESET,
पूर्ण;

/* D0i3 substates */
क्रमागत skl_dsp_d0i3_states अणु
	SKL_DSP_D0I3_NONE = -1, /* No D0i3 */
	SKL_DSP_D0I3_NON_STREAMING = 0,
	SKL_DSP_D0I3_STREAMING = 1,
पूर्ण;

काष्ठा skl_dsp_fw_ops अणु
	पूर्णांक (*load_fw)(काष्ठा sst_dsp  *ctx);
	/* FW module parser/loader */
	पूर्णांक (*load_library)(काष्ठा sst_dsp *ctx,
		काष्ठा skl_lib_info *linfo, पूर्णांक lib_count);
	पूर्णांक (*parse_fw)(काष्ठा sst_dsp *ctx);
	पूर्णांक (*set_state_D0)(काष्ठा sst_dsp *ctx, अचिन्हित पूर्णांक core_id);
	पूर्णांक (*set_state_D3)(काष्ठा sst_dsp *ctx, अचिन्हित पूर्णांक core_id);
	पूर्णांक (*set_state_D0i3)(काष्ठा sst_dsp *ctx);
	पूर्णांक (*set_state_D0i0)(काष्ठा sst_dsp *ctx);
	अचिन्हित पूर्णांक (*get_fw_errcode)(काष्ठा sst_dsp *ctx);
	पूर्णांक (*load_mod)(काष्ठा sst_dsp *ctx, u16 mod_id, u8 *mod_name);
	पूर्णांक (*unload_mod)(काष्ठा sst_dsp *ctx, u16 mod_id);

पूर्ण;

काष्ठा skl_dsp_loader_ops अणु
	पूर्णांक stream_tag;

	पूर्णांक (*alloc_dma_buf)(काष्ठा device *dev,
		काष्ठा snd_dma_buffer *dmab, माप_प्रकार size);
	पूर्णांक (*मुक्त_dma_buf)(काष्ठा device *dev,
		काष्ठा snd_dma_buffer *dmab);
	पूर्णांक (*prepare)(काष्ठा device *dev, अचिन्हित पूर्णांक क्रमmat,
				अचिन्हित पूर्णांक byte_size,
				काष्ठा snd_dma_buffer *bufp);
	पूर्णांक (*trigger)(काष्ठा device *dev, bool start, पूर्णांक stream_tag);

	पूर्णांक (*cleanup)(काष्ठा device *dev, काष्ठा snd_dma_buffer *dmab,
				 पूर्णांक stream_tag);
पूर्ण;

#घोषणा MAX_INSTANCE_BUFF 2

काष्ठा uuid_module अणु
	guid_t uuid;
	पूर्णांक id;
	पूर्णांक is_loadable;
	पूर्णांक max_instance;
	u64 pvt_id[MAX_INSTANCE_BUFF];
	पूर्णांक *instance_id;

	काष्ठा list_head list;
पूर्ण;

काष्ठा skl_load_module_info अणु
	u16 mod_id;
	स्थिर काष्ठा firmware *fw;
पूर्ण;

काष्ठा skl_module_table अणु
	काष्ठा skl_load_module_info *mod_info;
	अचिन्हित पूर्णांक usage_cnt;
	काष्ठा list_head list;
पूर्ण;

व्योम skl_cldma_process_पूर्णांकr(काष्ठा sst_dsp *ctx);
व्योम skl_cldma_पूर्णांक_disable(काष्ठा sst_dsp *ctx);
पूर्णांक skl_cldma_prepare(काष्ठा sst_dsp *ctx);
पूर्णांक skl_cldma_रुको_पूर्णांकerruptible(काष्ठा sst_dsp *ctx);

व्योम skl_dsp_set_state_locked(काष्ठा sst_dsp *ctx, पूर्णांक state);
काष्ठा sst_dsp *skl_dsp_ctx_init(काष्ठा device *dev,
		काष्ठा sst_dsp_device *sst_dev, पूर्णांक irq);
पूर्णांक skl_dsp_acquire_irq(काष्ठा sst_dsp *sst);
bool is_skl_dsp_running(काष्ठा sst_dsp *ctx);

अचिन्हित पूर्णांक skl_dsp_get_enabled_cores(काष्ठा sst_dsp *ctx);
व्योम skl_dsp_init_core_state(काष्ठा sst_dsp *ctx);
पूर्णांक skl_dsp_enable_core(काष्ठा sst_dsp *ctx, अचिन्हित पूर्णांक core_mask);
पूर्णांक skl_dsp_disable_core(काष्ठा sst_dsp *ctx, अचिन्हित पूर्णांक core_mask);
पूर्णांक skl_dsp_core_घातer_up(काष्ठा sst_dsp *ctx, अचिन्हित पूर्णांक core_mask);
पूर्णांक skl_dsp_core_घातer_करोwn(काष्ठा sst_dsp *ctx, अचिन्हित पूर्णांक core_mask);
पूर्णांक skl_dsp_core_unset_reset_state(काष्ठा sst_dsp *ctx,
					अचिन्हित पूर्णांक core_mask);
पूर्णांक skl_dsp_start_core(काष्ठा sst_dsp *ctx, अचिन्हित पूर्णांक core_mask);

irqवापस_t skl_dsp_sst_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id);
पूर्णांक skl_dsp_wake(काष्ठा sst_dsp *ctx);
पूर्णांक skl_dsp_sleep(काष्ठा sst_dsp *ctx);
व्योम skl_dsp_मुक्त(काष्ठा sst_dsp *dsp);

पूर्णांक skl_dsp_get_core(काष्ठा sst_dsp *ctx, अचिन्हित पूर्णांक core_id);
पूर्णांक skl_dsp_put_core(काष्ठा sst_dsp *ctx, अचिन्हित पूर्णांक core_id);

पूर्णांक skl_dsp_boot(काष्ठा sst_dsp *ctx);
पूर्णांक skl_sst_dsp_init(काष्ठा device *dev, व्योम __iomem *mmio_base, पूर्णांक irq,
		स्थिर अक्षर *fw_name, काष्ठा skl_dsp_loader_ops dsp_ops,
		काष्ठा skl_dev **dsp);
पूर्णांक bxt_sst_dsp_init(काष्ठा device *dev, व्योम __iomem *mmio_base, पूर्णांक irq,
		स्थिर अक्षर *fw_name, काष्ठा skl_dsp_loader_ops dsp_ops,
		काष्ठा skl_dev **dsp);
पूर्णांक skl_sst_init_fw(काष्ठा device *dev, काष्ठा skl_dev *skl);
पूर्णांक bxt_sst_init_fw(काष्ठा device *dev, काष्ठा skl_dev *skl);
व्योम skl_sst_dsp_cleanup(काष्ठा device *dev, काष्ठा skl_dev *skl);
व्योम bxt_sst_dsp_cleanup(काष्ठा device *dev, काष्ठा skl_dev *skl);

पूर्णांक snd_skl_parse_uuids(काष्ठा sst_dsp *ctx, स्थिर काष्ठा firmware *fw,
				अचिन्हित पूर्णांक offset, पूर्णांक index);
पूर्णांक skl_get_pvt_id(काष्ठा skl_dev *skl, guid_t *uuid_mod, पूर्णांक instance_id);
पूर्णांक skl_put_pvt_id(काष्ठा skl_dev *skl, guid_t *uuid_mod, पूर्णांक *pvt_id);
पूर्णांक skl_get_pvt_instance_id_map(काष्ठा skl_dev *skl,
				पूर्णांक module_id, पूर्णांक instance_id);
व्योम skl_मुक्तup_uuid_list(काष्ठा skl_dev *skl);

पूर्णांक skl_dsp_strip_extended_manअगरest(काष्ठा firmware *fw);

व्योम skl_dsp_set_astate_cfg(काष्ठा skl_dev *skl, u32 cnt, व्योम *data);

पूर्णांक skl_sst_ctx_init(काष्ठा device *dev, पूर्णांक irq, स्थिर अक्षर *fw_name,
		काष्ठा skl_dsp_loader_ops dsp_ops, काष्ठा skl_dev **dsp,
		काष्ठा sst_dsp_device *skl_dev);
पूर्णांक skl_prepare_lib_load(काष्ठा skl_dev *skl, काष्ठा skl_lib_info *linfo,
			काष्ठा firmware *stripped_fw,
			अचिन्हित पूर्णांक hdr_offset, पूर्णांक index);
व्योम skl_release_library(काष्ठा skl_lib_info *linfo, पूर्णांक lib_count);

#पूर्ण_अगर /*__SKL_SST_DSP_H__*/
