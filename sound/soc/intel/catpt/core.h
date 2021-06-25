<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright(c) 2020 Intel Corporation. All rights reserved.
 *
 * Author: Cezary Rojewski <cezary.rojewski@पूर्णांकel.com>
 */

#अगर_अघोषित __SND_SOC_INTEL_CATPT_CORE_H
#घोषणा __SND_SOC_INTEL_CATPT_CORE_H

#समावेश <linux/dma/dw.h>
#समावेश <linux/irqवापस.h>
#समावेश "messages.h"
#समावेश "registers.h"

काष्ठा catpt_dev;

बाह्य स्थिर काष्ठा attribute_group *catpt_attr_groups[];

व्योम catpt_sram_init(काष्ठा resource *sram, u32 start, u32 size);
व्योम catpt_sram_मुक्त(काष्ठा resource *sram);
काष्ठा resource *
catpt_request_region(काष्ठा resource *root, resource_माप_प्रकार size);

काष्ठा catpt_ipc_msg अणु
	जोड़ अणु
		u32 header;
		जोड़ catpt_global_msg rsp;
	पूर्ण;
	व्योम *data;
	माप_प्रकार size;
पूर्ण;

काष्ठा catpt_ipc अणु
	काष्ठा device *dev;

	काष्ठा catpt_ipc_msg rx;
	काष्ठा catpt_fw_पढ़ोy config;
	u32 शेष_समयout;
	bool पढ़ोy;

	spinlock_t lock;
	काष्ठा mutex mutex;
	काष्ठा completion करोne_completion;
	काष्ठा completion busy_completion;
पूर्ण;

व्योम catpt_ipc_init(काष्ठा catpt_ipc *ipc, काष्ठा device *dev);

काष्ठा catpt_module_type अणु
	bool loaded;
	u32 entry_poपूर्णांक;
	u32 persistent_size;
	u32 scratch_size;
	/* DRAM, initial module state */
	u32 state_offset;
	u32 state_size;

	काष्ठा list_head node;
पूर्ण;

काष्ठा catpt_spec अणु
	काष्ठा snd_soc_acpi_mach *machines;
	u8 core_id;
	u32 host_dram_offset;
	u32 host_iram_offset;
	u32 host_shim_offset;
	u32 host_dma_offset[CATPT_DMA_COUNT];
	u32 host_ssp_offset[CATPT_SSP_COUNT];
	u32 dram_mask;
	u32 iram_mask;
	u32 d3srampgd_bit;
	u32 d3pgd_bit;
	व्योम (*pll_shutकरोwn)(काष्ठा catpt_dev *cdev, bool enable);
पूर्ण;

काष्ठा catpt_dev अणु
	काष्ठा device *dev;
	काष्ठा dw_dma_chip *dmac;
	काष्ठा catpt_ipc ipc;

	व्योम __iomem *pci_ba;
	व्योम __iomem *lpe_ba;
	u32 lpe_base;
	पूर्णांक irq;

	स्थिर काष्ठा catpt_spec *spec;
	काष्ठा completion fw_पढ़ोy;

	काष्ठा resource dram;
	काष्ठा resource iram;
	काष्ठा resource *scratch;

	काष्ठा catpt_mixer_stream_info mixer;
	काष्ठा catpt_module_type modules[CATPT_MODULE_COUNT];
	काष्ठा catpt_ssp_device_क्रमmat devfmt[CATPT_SSP_COUNT];
	काष्ठा list_head stream_list;
	spinlock_t list_lock;
	काष्ठा mutex clk_mutex;

	काष्ठा catpt_dx_context dx_ctx;
	व्योम *dxbuf_vaddr;
	dma_addr_t dxbuf_paddr;
पूर्ण;

पूर्णांक catpt_dmac_probe(काष्ठा catpt_dev *cdev);
व्योम catpt_dmac_हटाओ(काष्ठा catpt_dev *cdev);
काष्ठा dma_chan *catpt_dma_request_config_chan(काष्ठा catpt_dev *cdev);
पूर्णांक catpt_dma_स_नकल_todsp(काष्ठा catpt_dev *cdev, काष्ठा dma_chan *chan,
			   dma_addr_t dst_addr, dma_addr_t src_addr,
			   माप_प्रकार size);
पूर्णांक catpt_dma_स_नकल_fromdsp(काष्ठा catpt_dev *cdev, काष्ठा dma_chan *chan,
			     dma_addr_t dst_addr, dma_addr_t src_addr,
			     माप_प्रकार size);

व्योम lpt_dsp_pll_shutकरोwn(काष्ठा catpt_dev *cdev, bool enable);
व्योम wpt_dsp_pll_shutकरोwn(काष्ठा catpt_dev *cdev, bool enable);
पूर्णांक catpt_dsp_घातer_up(काष्ठा catpt_dev *cdev);
पूर्णांक catpt_dsp_घातer_करोwn(काष्ठा catpt_dev *cdev);
पूर्णांक catpt_dsp_stall(काष्ठा catpt_dev *cdev, bool stall);
व्योम catpt_dsp_update_srampge(काष्ठा catpt_dev *cdev, काष्ठा resource *sram,
			      अचिन्हित दीर्घ mask);
पूर्णांक catpt_dsp_update_lpघड़ी(काष्ठा catpt_dev *cdev);
irqवापस_t catpt_dsp_irq_handler(पूर्णांक irq, व्योम *dev_id);
irqवापस_t catpt_dsp_irq_thपढ़ो(पूर्णांक irq, व्योम *dev_id);

/*
 * IPC handlers may वापस positive values which denote successful
 * HOST <-> DSP communication yet failure to process specअगरic request.
 * Use below macro to convert वापसed non-zero values appropriately
 */
#घोषणा CATPT_IPC_ERROR(err) (((err) < 0) ? (err) : -EREMOTEIO)

पूर्णांक catpt_dsp_send_msg_समयout(काष्ठा catpt_dev *cdev,
			       काष्ठा catpt_ipc_msg request,
			       काष्ठा catpt_ipc_msg *reply, पूर्णांक समयout);
पूर्णांक catpt_dsp_send_msg(काष्ठा catpt_dev *cdev, काष्ठा catpt_ipc_msg request,
		       काष्ठा catpt_ipc_msg *reply);

पूर्णांक catpt_first_boot_firmware(काष्ठा catpt_dev *cdev);
पूर्णांक catpt_boot_firmware(काष्ठा catpt_dev *cdev, bool restore);
पूर्णांक catpt_store_streams_context(काष्ठा catpt_dev *cdev, काष्ठा dma_chan *chan);
पूर्णांक catpt_store_module_states(काष्ठा catpt_dev *cdev, काष्ठा dma_chan *chan);
पूर्णांक catpt_store_memdumps(काष्ठा catpt_dev *cdev, काष्ठा dma_chan *chan);
पूर्णांक catpt_coredump(काष्ठा catpt_dev *cdev);

#समावेश <sound/meदो_स्मृति.h>
#समावेश <uapi/sound/asound.h>

काष्ठा snd_pcm_substream;
काष्ठा catpt_stream_ढाँचा;

काष्ठा catpt_stream_runसमय अणु
	काष्ठा snd_pcm_substream *substream;

	काष्ठा catpt_stream_ढाँचा *ढाँचा;
	काष्ठा catpt_stream_info info;
	काष्ठा resource *persistent;
	काष्ठा snd_dma_buffer pgtbl;

	bool allocated;
	bool prepared;

	काष्ठा list_head node;
पूर्ण;

पूर्णांक catpt_रेजिस्टर_plat_component(काष्ठा catpt_dev *cdev);
व्योम catpt_stream_update_position(काष्ठा catpt_dev *cdev,
				  काष्ठा catpt_stream_runसमय *stream,
				  काष्ठा catpt_notअगरy_position *pos);
काष्ठा catpt_stream_runसमय *
catpt_stream_find(काष्ठा catpt_dev *cdev, u8 stream_hw_id);
पूर्णांक catpt_arm_stream_ढाँचाs(काष्ठा catpt_dev *cdev);

#पूर्ण_अगर
