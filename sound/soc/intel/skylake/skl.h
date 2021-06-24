<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  skl.h - HD Audio skylake definitions.
 *
 *  Copyright (C) 2015 Intel Corp
 *  Author: Jeeja KP <jeeja.kp@पूर्णांकel.com>
 *  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

#अगर_अघोषित __SOUND_SOC_SKL_H
#घोषणा __SOUND_SOC_SKL_H

#समावेश <sound/hda_रेजिस्टर.h>
#समावेश <sound/hdaudio_ext.h>
#समावेश <sound/hda_codec.h>
#समावेश <sound/soc.h>
#समावेश "skl-ssp-clk.h"
#समावेश "skl-sst-ipc.h"

#घोषणा SKL_SUSPEND_DELAY 2000

#घोषणा SKL_MAX_ASTATE_CFG		3

#घोषणा AZX_PCIREG_PGCTL		0x44
#घोषणा AZX_PGCTL_LSRMD_MASK		(1 << 4)
#घोषणा AZX_PGCTL_ADSPPGD		BIT(2)
#घोषणा AZX_PCIREG_CGCTL		0x48
#घोषणा AZX_CGCTL_MISCBDCGE_MASK	(1 << 6)
#घोषणा AZX_CGCTL_ADSPDCGE		BIT(1)
/* D0I3C Register fields */
#घोषणा AZX_REG_VS_D0I3C_CIP      0x1 /* Command in progress */
#घोषणा AZX_REG_VS_D0I3C_I3       0x4 /* D0i3 enable */
#घोषणा SKL_MAX_DMACTRL_CFG	18
#घोषणा DMA_CLK_CONTROLS	1
#घोषणा DMA_TRANSMITION_START	2
#घोषणा DMA_TRANSMITION_STOP	3

#घोषणा AZX_VS_EM2_DUM			BIT(23)
#घोषणा AZX_REG_VS_EM2_L1SEN		BIT(13)

काष्ठा skl_debug;

काष्ठा skl_astate_param अणु
	u32 kcps;
	u32 clk_src;
पूर्ण;

काष्ठा skl_astate_config अणु
	u32 count;
	काष्ठा skl_astate_param astate_table[];
पूर्ण;

काष्ठा skl_fw_config अणु
	काष्ठा skl_astate_config *astate_cfg;
पूर्ण;

काष्ठा skl_dev अणु
	काष्ठा hda_bus hbus;
	काष्ठा pci_dev *pci;

	अचिन्हित पूर्णांक init_करोne:1; /* delayed init status */
	काष्ठा platक्रमm_device *dmic_dev;
	काष्ठा platक्रमm_device *i2s_dev;
	काष्ठा platक्रमm_device *clk_dev;
	काष्ठा snd_soc_component *component;
	काष्ठा snd_soc_dai_driver *dais;

	काष्ठा nhlt_acpi_table *nhlt; /* nhlt ptr */

	काष्ठा list_head ppl_list;
	काष्ठा list_head bind_list;

	स्थिर अक्षर *fw_name;
	अक्षर tplg_name[64];
	अचिन्हित लघु pci_id;

	पूर्णांक supend_active;

	काष्ठा work_काष्ठा probe_work;

	काष्ठा skl_debug *debugfs;
	u8 nr_modules;
	काष्ठा skl_module **modules;
	bool use_tplg_pcm;
	काष्ठा skl_fw_config cfg;
	काष्ठा snd_soc_acpi_mach *mach;

	काष्ठा device *dev;
	काष्ठा sst_dsp *dsp;

	/* boot */
	रुको_queue_head_t boot_रुको;
	bool boot_complete;

	/* module load */
	रुको_queue_head_t mod_load_रुको;
	bool mod_load_complete;
	bool mod_load_status;

	/* IPC messaging */
	काष्ठा sst_generic_ipc ipc;

	/* callback क्रम miscbdge */
	व्योम (*enable_miscbdcge)(काष्ठा device *dev, bool enable);
	/* Is CGCTL.MISCBDCGE disabled */
	bool miscbdcg_disabled;

	/* Populate module inक्रमmation */
	काष्ठा list_head uuid_list;

	/* Is firmware loaded */
	bool fw_loaded;

	/* first boot ? */
	bool is_first_boot;

	/* multi-core */
	काष्ठा skl_dsp_cores cores;

	/* library info */
	काष्ठा skl_lib_info  lib_info[SKL_MAX_LIB];
	पूर्णांक lib_count;

	/* Callback to update D0i3C रेजिस्टर */
	व्योम (*update_d0i3c)(काष्ठा device *dev, bool enable);

	काष्ठा skl_d0i3_data d0i3;

	स्थिर काष्ठा skl_dsp_ops *dsp_ops;

	/* Callback to update dynamic घड़ी and घातer gating रेजिस्टरs */
	व्योम (*घड़ी_घातer_gating)(काष्ठा device *dev, bool enable);
पूर्ण;

#घोषणा skl_to_bus(s)  (&(s)->hbus.core)
#घोषणा bus_to_skl(bus) container_of(bus, काष्ठा skl_dev, hbus.core)

#घोषणा skl_to_hbus(s) (&(s)->hbus)
#घोषणा hbus_to_skl(hbus) container_of((hbus), काष्ठा skl_dev, (hbus))

/* to pass dai dma data */
काष्ठा skl_dma_params अणु
	u32 क्रमmat;
	u8 stream_tag;
पूर्ण;

काष्ठा skl_machine_pdata अणु
	bool use_tplg_pcm; /* use dais and dai links from topology */
पूर्ण;

काष्ठा skl_dsp_ops अणु
	पूर्णांक id;
	अचिन्हित पूर्णांक num_cores;
	काष्ठा skl_dsp_loader_ops (*loader_ops)(व्योम);
	पूर्णांक (*init)(काष्ठा device *dev, व्योम __iomem *mmio_base,
			पूर्णांक irq, स्थिर अक्षर *fw_name,
			काष्ठा skl_dsp_loader_ops loader_ops,
			काष्ठा skl_dev **skl_sst);
	पूर्णांक (*init_fw)(काष्ठा device *dev, काष्ठा skl_dev *skl);
	व्योम (*cleanup)(काष्ठा device *dev, काष्ठा skl_dev *skl);
पूर्ण;

पूर्णांक skl_platक्रमm_unरेजिस्टर(काष्ठा device *dev);
पूर्णांक skl_platक्रमm_रेजिस्टर(काष्ठा device *dev);

काष्ठा nhlt_specअगरic_cfg *skl_get_ep_blob(काष्ठा skl_dev *skl, u32 instance,
					u8 link_type, u8 s_fmt, u8 num_ch,
					u32 s_rate, u8 dirn, u8 dev_type);

पूर्णांक skl_nhlt_update_topology_bin(काष्ठा skl_dev *skl);
पूर्णांक skl_init_dsp(काष्ठा skl_dev *skl);
पूर्णांक skl_मुक्त_dsp(काष्ठा skl_dev *skl);
पूर्णांक skl_suspend_late_dsp(काष्ठा skl_dev *skl);
पूर्णांक skl_suspend_dsp(काष्ठा skl_dev *skl);
पूर्णांक skl_resume_dsp(काष्ठा skl_dev *skl);
व्योम skl_cleanup_resources(काष्ठा skl_dev *skl);
स्थिर काष्ठा skl_dsp_ops *skl_get_dsp_ops(पूर्णांक pci_id);
व्योम skl_update_d0i3c(काष्ठा device *dev, bool enable);
पूर्णांक skl_nhlt_create_sysfs(काष्ठा skl_dev *skl);
व्योम skl_nhlt_हटाओ_sysfs(काष्ठा skl_dev *skl);
व्योम skl_get_clks(काष्ठा skl_dev *skl, काष्ठा skl_ssp_clk *ssp_clks);
काष्ठा skl_clk_parent_src *skl_get_parent_clk(u8 clk_id);
पूर्णांक skl_dsp_set_dma_control(काष्ठा skl_dev *skl, u32 *caps,
				u32 caps_size, u32 node_id);

काष्ठा skl_module_cfg;

#अगर_घोषित CONFIG_DEBUG_FS
काष्ठा skl_debug *skl_debugfs_init(काष्ठा skl_dev *skl);
व्योम skl_debugfs_निकास(काष्ठा skl_dev *skl);
व्योम skl_debug_init_module(काष्ठा skl_debug *d,
			काष्ठा snd_soc_dapm_widget *w,
			काष्ठा skl_module_cfg *mconfig);
#अन्यथा
अटल अंतरभूत काष्ठा skl_debug *skl_debugfs_init(काष्ठा skl_dev *skl)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम skl_debugfs_निकास(काष्ठा skl_dev *skl)
अणुपूर्ण

अटल अंतरभूत व्योम skl_debug_init_module(काष्ठा skl_debug *d,
					 काष्ठा snd_soc_dapm_widget *w,
					 काष्ठा skl_module_cfg *mconfig)
अणुपूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* __SOUND_SOC_SKL_H */
