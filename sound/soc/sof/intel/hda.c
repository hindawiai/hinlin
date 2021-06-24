<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-3-Clause)
//
// This file is provided under a dual BSD/GPLv2 license.  When using or
// redistributing this file, you may करो so under either license.
//
// Copyright(c) 2018 Intel Corporation. All rights reserved.
//
// Authors: Liam Girdwood <liam.r.girdwood@linux.पूर्णांकel.com>
//	    Ranjani Sridharan <ranjani.sridharan@linux.पूर्णांकel.com>
//	    Rander Wang <अक्रमer.wang@पूर्णांकel.com>
//          Keyon Jie <yang.jie@linux.पूर्णांकel.com>
//

/*
 * Hardware पूर्णांकerface क्रम generic Intel audio DSP HDA IP
 */

#समावेश <sound/hdaudio_ext.h>
#समावेश <sound/hda_रेजिस्टर.h>

#समावेश <linux/acpi.h>
#समावेश <linux/module.h>
#समावेश <linux/soundwire/sdw.h>
#समावेश <linux/soundwire/sdw_पूर्णांकel.h>
#समावेश <sound/पूर्णांकel-dsp-config.h>
#समावेश <sound/पूर्णांकel-nhlt.h>
#समावेश <sound/sof.h>
#समावेश <sound/sof/xtensa.h>
#समावेश "../sof-audio.h"
#समावेश "../sof-pci-dev.h"
#समावेश "../ops.h"
#समावेश "hda.h"

#अगर IS_ENABLED(CONFIG_SND_SOC_SOF_HDA)
#समावेश <sound/soc-acpi-पूर्णांकel-match.h>
#पूर्ण_अगर

/* platक्रमm specअगरic devices */
#समावेश "shim.h"

#घोषणा EXCEPT_MAX_HDR_SIZE	0x400
#घोषणा HDA_EXT_ROM_STATUS_SIZE 8

#अगर IS_ENABLED(CONFIG_SND_SOC_SOF_INTEL_SOUNDWIRE)

/*
 * The शेष क्रम SoundWire घड़ी stop quirks is to घातer gate the IP
 * and करो a Bus Reset, this will need to be modअगरied when the DSP
 * needs to reमुख्य in D0i3 so that the Master करोes not lose context
 * and क्रमागतeration is not required on घड़ी restart
 */
अटल पूर्णांक sdw_घड़ी_stop_quirks = SDW_INTEL_CLK_STOP_BUS_RESET;
module_param(sdw_घड़ी_stop_quirks, पूर्णांक, 0444);
MODULE_PARM_DESC(sdw_घड़ी_stop_quirks, "SOF SoundWire clock stop quirks");

अटल पूर्णांक sdw_params_stream(काष्ठा device *dev,
			     काष्ठा sdw_पूर्णांकel_stream_params_data *params_data)
अणु
	काष्ठा snd_sof_dev *sdev = dev_get_drvdata(dev);
	काष्ठा snd_soc_dai *d = params_data->dai;
	काष्ठा sof_ipc_dai_config config;
	काष्ठा sof_ipc_reply reply;
	पूर्णांक link_id = params_data->link_id;
	पूर्णांक alh_stream_id = params_data->alh_stream_id;
	पूर्णांक ret;
	u32 size = माप(config);

	स_रखो(&config, 0, size);
	config.hdr.size = size;
	config.hdr.cmd = SOF_IPC_GLB_DAI_MSG | SOF_IPC_DAI_CONFIG;
	config.type = SOF_DAI_INTEL_ALH;
	config.dai_index = (link_id << 8) | (d->id);
	config.alh.stream_id = alh_stream_id;

	/* send message to DSP */
	ret = sof_ipc_tx_message(sdev->ipc,
				 config.hdr.cmd, &config, size, &reply,
				 माप(reply));
	अगर (ret < 0) अणु
		dev_err(sdev->dev,
			"error: failed to set DAI hw_params for link %d dai->id %d ALH %d\n",
			link_id, d->id, alh_stream_id);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक sdw_मुक्त_stream(काष्ठा device *dev,
			   काष्ठा sdw_पूर्णांकel_stream_मुक्त_data *मुक्त_data)
अणु
	काष्ठा snd_sof_dev *sdev = dev_get_drvdata(dev);
	काष्ठा snd_soc_dai *d = मुक्त_data->dai;
	काष्ठा sof_ipc_dai_config config;
	काष्ठा sof_ipc_reply reply;
	पूर्णांक link_id = मुक्त_data->link_id;
	पूर्णांक ret;
	u32 size = माप(config);

	स_रखो(&config, 0, size);
	config.hdr.size = size;
	config.hdr.cmd = SOF_IPC_GLB_DAI_MSG | SOF_IPC_DAI_CONFIG;
	config.type = SOF_DAI_INTEL_ALH;
	config.dai_index = (link_id << 8) | d->id;
	config.alh.stream_id = 0xFFFF; /* invalid value on purpose */

	/* send message to DSP */
	ret = sof_ipc_tx_message(sdev->ipc,
				 config.hdr.cmd, &config, size, &reply,
				 माप(reply));
	अगर (ret < 0) अणु
		dev_err(sdev->dev,
			"error: failed to free stream for link %d dai->id %d\n",
			link_id, d->id);
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा sdw_पूर्णांकel_ops sdw_callback = अणु
	.params_stream = sdw_params_stream,
	.मुक्त_stream = sdw_मुक्त_stream,
पूर्ण;

व्योम hda_sdw_पूर्णांक_enable(काष्ठा snd_sof_dev *sdev, bool enable)
अणु
	sdw_पूर्णांकel_enable_irq(sdev->bar[HDA_DSP_BAR], enable);
पूर्ण

अटल पूर्णांक hda_sdw_acpi_scan(काष्ठा snd_sof_dev *sdev)
अणु
	काष्ठा sof_पूर्णांकel_hda_dev *hdev;
	acpi_handle handle;
	पूर्णांक ret;

	handle = ACPI_HANDLE(sdev->dev);

	/* save ACPI info क्रम the probe step */
	hdev = sdev->pdata->hw_pdata;

	ret = sdw_पूर्णांकel_acpi_scan(handle, &hdev->info);
	अगर (ret < 0)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक hda_sdw_probe(काष्ठा snd_sof_dev *sdev)
अणु
	काष्ठा sof_पूर्णांकel_hda_dev *hdev;
	काष्ठा sdw_पूर्णांकel_res res;
	व्योम *sdw;

	hdev = sdev->pdata->hw_pdata;

	स_रखो(&res, 0, माप(res));

	res.mmio_base = sdev->bar[HDA_DSP_BAR];
	res.irq = sdev->ipc_irq;
	res.handle = hdev->info.handle;
	res.parent = sdev->dev;
	res.ops = &sdw_callback;
	res.dev = sdev->dev;
	res.घड़ी_stop_quirks = sdw_घड़ी_stop_quirks;

	/*
	 * ops and arg fields are not populated क्रम now,
	 * they will be needed when the DAI callbacks are
	 * provided
	 */

	/* we could filter links here अगर needed, e.g क्रम quirks */
	res.count = hdev->info.count;
	res.link_mask = hdev->info.link_mask;

	sdw = sdw_पूर्णांकel_probe(&res);
	अगर (!sdw) अणु
		dev_err(sdev->dev, "error: SoundWire probe failed\n");
		वापस -EINVAL;
	पूर्ण

	/* save context */
	hdev->sdw = sdw;

	वापस 0;
पूर्ण

पूर्णांक hda_sdw_startup(काष्ठा snd_sof_dev *sdev)
अणु
	काष्ठा sof_पूर्णांकel_hda_dev *hdev;

	hdev = sdev->pdata->hw_pdata;

	अगर (!hdev->sdw)
		वापस 0;

	वापस sdw_पूर्णांकel_startup(hdev->sdw);
पूर्ण

अटल पूर्णांक hda_sdw_निकास(काष्ठा snd_sof_dev *sdev)
अणु
	काष्ठा sof_पूर्णांकel_hda_dev *hdev;

	hdev = sdev->pdata->hw_pdata;

	hda_sdw_पूर्णांक_enable(sdev, false);

	अगर (hdev->sdw)
		sdw_पूर्णांकel_निकास(hdev->sdw);
	hdev->sdw = शून्य;

	वापस 0;
पूर्ण

अटल bool hda_dsp_check_sdw_irq(काष्ठा snd_sof_dev *sdev)
अणु
	काष्ठा sof_पूर्णांकel_hda_dev *hdev;
	bool ret = false;
	u32 irq_status;

	hdev = sdev->pdata->hw_pdata;

	अगर (!hdev->sdw)
		वापस ret;

	/* store status */
	irq_status = snd_sof_dsp_पढ़ो(sdev, HDA_DSP_BAR, HDA_DSP_REG_ADSPIS2);

	/* invalid message ? */
	अगर (irq_status == 0xffffffff)
		जाओ out;

	/* SDW message ? */
	अगर (irq_status & HDA_DSP_REG_ADSPIS2_SNDW)
		ret = true;

out:
	वापस ret;
पूर्ण

अटल irqवापस_t hda_dsp_sdw_thपढ़ो(पूर्णांक irq, व्योम *context)
अणु
	वापस sdw_पूर्णांकel_thपढ़ो(irq, context);
पूर्ण

अटल bool hda_sdw_check_wakeen_irq(काष्ठा snd_sof_dev *sdev)
अणु
	काष्ठा sof_पूर्णांकel_hda_dev *hdev;

	hdev = sdev->pdata->hw_pdata;
	अगर (hdev->sdw &&
	    snd_sof_dsp_पढ़ो(sdev, HDA_DSP_BAR,
			     HDA_DSP_REG_SNDW_WAKE_STS))
		वापस true;

	वापस false;
पूर्ण

व्योम hda_sdw_process_wakeen(काष्ठा snd_sof_dev *sdev)
अणु
	काष्ठा sof_पूर्णांकel_hda_dev *hdev;

	hdev = sdev->pdata->hw_pdata;
	अगर (!hdev->sdw)
		वापस;

	sdw_पूर्णांकel_process_wakeen_event(hdev->sdw);
पूर्ण

#पूर्ण_अगर

/*
 * Debug
 */

काष्ठा hda_dsp_msg_code अणु
	u32 code;
	स्थिर अक्षर *msg;
पूर्ण;

अटल bool hda_use_msi = IS_ENABLED(CONFIG_PCI);
#अगर IS_ENABLED(CONFIG_SND_SOC_SOF_DEBUG)
module_param_named(use_msi, hda_use_msi, bool, 0444);
MODULE_PARM_DESC(use_msi, "SOF HDA use PCI MSI mode");
#पूर्ण_अगर

अटल अक्षर *hda_model;
module_param(hda_model, अक्षरp, 0444);
MODULE_PARM_DESC(hda_model, "Use the given HDA board model.");

#अगर IS_ENABLED(CONFIG_SND_SOC_SOF_HDA) || IS_ENABLED(CONFIG_SND_SOC_SOF_INTEL_SOUNDWIRE)
अटल पूर्णांक hda_dmic_num = -1;
module_param_named(dmic_num, hda_dmic_num, पूर्णांक, 0444);
MODULE_PARM_DESC(dmic_num, "SOF HDA DMIC number");
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_SND_SOC_SOF_HDA)
अटल bool hda_codec_use_common_hdmi = IS_ENABLED(CONFIG_SND_HDA_CODEC_HDMI);
module_param_named(use_common_hdmi, hda_codec_use_common_hdmi, bool, 0444);
MODULE_PARM_DESC(use_common_hdmi, "SOF HDA use common HDMI codec driver");
#पूर्ण_अगर

अटल स्थिर काष्ठा hda_dsp_msg_code hda_dsp_rom_msg[] = अणु
	अणुHDA_DSP_ROM_FW_MANIFEST_LOADED, "status: manifest loaded"पूर्ण,
	अणुHDA_DSP_ROM_FW_FW_LOADED, "status: fw loaded"पूर्ण,
	अणुHDA_DSP_ROM_FW_ENTERED, "status: fw entered"पूर्ण,
	अणुHDA_DSP_ROM_CSE_ERROR, "error: cse error"पूर्ण,
	अणुHDA_DSP_ROM_CSE_WRONG_RESPONSE, "error: cse wrong response"पूर्ण,
	अणुHDA_DSP_ROM_IMR_TO_SMALL, "error: IMR too small"पूर्ण,
	अणुHDA_DSP_ROM_BASE_FW_NOT_FOUND, "error: base fw not found"पूर्ण,
	अणुHDA_DSP_ROM_CSE_VALIDATION_FAILED, "error: signature verification failed"पूर्ण,
	अणुHDA_DSP_ROM_IPC_FATAL_ERROR, "error: ipc fatal error"पूर्ण,
	अणुHDA_DSP_ROM_L2_CACHE_ERROR, "error: L2 cache error"पूर्ण,
	अणुHDA_DSP_ROM_LOAD_OFFSET_TO_SMALL, "error: load offset too small"पूर्ण,
	अणुHDA_DSP_ROM_API_PTR_INVALID, "error: API ptr invalid"पूर्ण,
	अणुHDA_DSP_ROM_BASEFW_INCOMPAT, "error: base fw incompatible"पूर्ण,
	अणुHDA_DSP_ROM_UNHANDLED_INTERRUPT, "error: unhandled interrupt"पूर्ण,
	अणुHDA_DSP_ROM_MEMORY_HOLE_ECC, "error: ECC memory hole"पूर्ण,
	अणुHDA_DSP_ROM_KERNEL_EXCEPTION, "error: kernel exception"पूर्ण,
	अणुHDA_DSP_ROM_USER_EXCEPTION, "error: user exception"पूर्ण,
	अणुHDA_DSP_ROM_UNEXPECTED_RESET, "error: unexpected reset"पूर्ण,
	अणुHDA_DSP_ROM_शून्य_FW_ENTRY,	"error: null FW entry point"पूर्ण,
पूर्ण;

अटल व्योम hda_dsp_get_status(काष्ठा snd_sof_dev *sdev)
अणु
	u32 status;
	पूर्णांक i;

	status = snd_sof_dsp_पढ़ो(sdev, HDA_DSP_BAR,
				  HDA_DSP_SRAM_REG_ROM_STATUS);

	क्रम (i = 0; i < ARRAY_SIZE(hda_dsp_rom_msg); i++) अणु
		अगर (status == hda_dsp_rom_msg[i].code) अणु
			dev_err(sdev->dev, "%s - code %8.8x\n",
				hda_dsp_rom_msg[i].msg, status);
			वापस;
		पूर्ण
	पूर्ण

	/* not क्रम us, must be generic sof message */
	dev_dbg(sdev->dev, "unknown ROM status value %8.8x\n", status);
पूर्ण

अटल व्योम hda_dsp_get_रेजिस्टरs(काष्ठा snd_sof_dev *sdev,
				  काष्ठा sof_ipc_dsp_oops_xtensa *xoops,
				  काष्ठा sof_ipc_panic_info *panic_info,
				  u32 *stack, माप_प्रकार stack_words)
अणु
	u32 offset = sdev->dsp_oops_offset;

	/* first पढ़ो रेजिस्टरs */
	sof_mailbox_पढ़ो(sdev, offset, xoops, माप(*xoops));

	/* note: variable AR रेजिस्टर array is not पढ़ो */

	/* then get panic info */
	अगर (xoops->arch_hdr.totalsize > EXCEPT_MAX_HDR_SIZE) अणु
		dev_err(sdev->dev, "invalid header size 0x%x. FW oops is bogus\n",
			xoops->arch_hdr.totalsize);
		वापस;
	पूर्ण
	offset += xoops->arch_hdr.totalsize;
	sof_block_पढ़ो(sdev, sdev->mmio_bar, offset,
		       panic_info, माप(*panic_info));

	/* then get the stack */
	offset += माप(*panic_info);
	sof_block_पढ़ो(sdev, sdev->mmio_bar, offset, stack,
		       stack_words * माप(u32));
पूर्ण

/* dump the first 8 dwords representing the extended ROM status */
अटल व्योम hda_dsp_dump_ext_rom_status(काष्ठा snd_sof_dev *sdev, u32 flags)
अणु
	अक्षर msg[128];
	पूर्णांक len = 0;
	u32 value;
	पूर्णांक i;

	क्रम (i = 0; i < HDA_EXT_ROM_STATUS_SIZE; i++) अणु
		value = snd_sof_dsp_पढ़ो(sdev, HDA_DSP_BAR, HDA_DSP_SRAM_REG_ROM_STATUS + i * 0x4);
		len += snम_लिखो(msg + len, माप(msg) - len, " 0x%x", value);
	पूर्ण

	sof_dev_dbg_or_err(sdev->dev, flags & SOF_DBG_DUMP_FORCE_ERR_LEVEL,
			   "extended rom status: %s", msg);

पूर्ण

व्योम hda_dsp_dump(काष्ठा snd_sof_dev *sdev, u32 flags)
अणु
	काष्ठा sof_ipc_dsp_oops_xtensa xoops;
	काष्ठा sof_ipc_panic_info panic_info;
	u32 stack[HDA_DSP_STACK_DUMP_SIZE];
	u32 status, panic;

	/* try APL specअगरic status message types first */
	hda_dsp_get_status(sdev);

	/* now try generic SOF status messages */
	status = snd_sof_dsp_पढ़ो(sdev, HDA_DSP_BAR,
				  HDA_DSP_SRAM_REG_FW_STATUS);
	panic = snd_sof_dsp_पढ़ो(sdev, HDA_DSP_BAR, HDA_DSP_SRAM_REG_FW_TRACEP);

	अगर (sdev->fw_state == SOF_FW_BOOT_COMPLETE) अणु
		hda_dsp_get_रेजिस्टरs(sdev, &xoops, &panic_info, stack,
				      HDA_DSP_STACK_DUMP_SIZE);
		snd_sof_get_status(sdev, status, panic, &xoops, &panic_info,
				   stack, HDA_DSP_STACK_DUMP_SIZE);
	पूर्ण अन्यथा अणु
		sof_dev_dbg_or_err(sdev->dev, flags & SOF_DBG_DUMP_FORCE_ERR_LEVEL,
				   "status = 0x%8.8x panic = 0x%8.8x\n",
				   status, panic);

		hda_dsp_dump_ext_rom_status(sdev, flags);
		hda_dsp_get_status(sdev);
	पूर्ण
पूर्ण

व्योम hda_ipc_irq_dump(काष्ठा snd_sof_dev *sdev)
अणु
	काष्ठा hdac_bus *bus = sof_to_bus(sdev);
	u32 adspis;
	u32 पूर्णांकsts;
	u32 पूर्णांकctl;
	u32 ppsts;
	u8 rirbsts;

	/* पढ़ो key IRQ stats and config रेजिस्टरs */
	adspis = snd_sof_dsp_पढ़ो(sdev, HDA_DSP_BAR, HDA_DSP_REG_ADSPIS);
	पूर्णांकsts = snd_sof_dsp_पढ़ो(sdev, HDA_DSP_HDA_BAR, SOF_HDA_INTSTS);
	पूर्णांकctl = snd_sof_dsp_पढ़ो(sdev, HDA_DSP_HDA_BAR, SOF_HDA_INTCTL);
	ppsts = snd_sof_dsp_पढ़ो(sdev, HDA_DSP_PP_BAR, SOF_HDA_REG_PP_PPSTS);
	rirbsts = snd_hdac_chip_पढ़ोb(bus, RIRBSTS);

	dev_err(sdev->dev,
		"error: hda irq intsts 0x%8.8x intlctl 0x%8.8x rirb %2.2x\n",
		पूर्णांकsts, पूर्णांकctl, rirbsts);
	dev_err(sdev->dev,
		"error: dsp irq ppsts 0x%8.8x adspis 0x%8.8x\n",
		ppsts, adspis);
पूर्ण

व्योम hda_ipc_dump(काष्ठा snd_sof_dev *sdev)
अणु
	u32 hipcie;
	u32 hipct;
	u32 hipcctl;

	hda_ipc_irq_dump(sdev);

	/* पढ़ो IPC status */
	hipcie = snd_sof_dsp_पढ़ो(sdev, HDA_DSP_BAR, HDA_DSP_REG_HIPCIE);
	hipct = snd_sof_dsp_पढ़ो(sdev, HDA_DSP_BAR, HDA_DSP_REG_HIPCT);
	hipcctl = snd_sof_dsp_पढ़ो(sdev, HDA_DSP_BAR, HDA_DSP_REG_HIPCCTL);

	/* dump the IPC regs */
	/* TODO: parse the raw msg */
	dev_err(sdev->dev,
		"error: host status 0x%8.8x dsp status 0x%8.8x mask 0x%8.8x\n",
		hipcie, hipct, hipcctl);
पूर्ण

अटल पूर्णांक hda_init(काष्ठा snd_sof_dev *sdev)
अणु
	काष्ठा hda_bus *hbus;
	काष्ठा hdac_bus *bus;
	काष्ठा pci_dev *pci = to_pci_dev(sdev->dev);
	पूर्णांक ret;

	hbus = sof_to_hbus(sdev);
	bus = sof_to_bus(sdev);

	/* HDA bus init */
	sof_hda_bus_init(bus, &pci->dev);

	bus->use_posbuf = 1;
	bus->bdl_pos_adj = 0;
	bus->sync_ग_लिखो = 1;

	mutex_init(&hbus->prepare_mutex);
	hbus->pci = pci;
	hbus->mixer_asचिन्हित = -1;
	hbus->modelname = hda_model;

	/* initialise hdac bus */
	bus->addr = pci_resource_start(pci, 0);
#अगर IS_ENABLED(CONFIG_PCI)
	bus->remap_addr = pci_ioremap_bar(pci, 0);
#पूर्ण_अगर
	अगर (!bus->remap_addr) अणु
		dev_err(bus->dev, "error: ioremap error\n");
		वापस -ENXIO;
	पूर्ण

	/* HDA base */
	sdev->bar[HDA_DSP_HDA_BAR] = bus->remap_addr;

	/* init i915 and HDMI codecs */
	ret = hda_codec_i915_init(sdev);
	अगर (ret < 0)
		dev_warn(sdev->dev, "init of i915 and HDMI codec failed\n");

	/* get controller capabilities */
	ret = hda_dsp_ctrl_get_caps(sdev);
	अगर (ret < 0)
		dev_err(sdev->dev, "error: get caps error\n");

	वापस ret;
पूर्ण

#अगर IS_ENABLED(CONFIG_SND_SOC_SOF_HDA) || IS_ENABLED(CONFIG_SND_SOC_SOF_INTEL_SOUNDWIRE)

अटल पूर्णांक check_nhlt_dmic(काष्ठा snd_sof_dev *sdev)
अणु
	काष्ठा nhlt_acpi_table *nhlt;
	पूर्णांक dmic_num;

	nhlt = पूर्णांकel_nhlt_init(sdev->dev);
	अगर (nhlt) अणु
		dmic_num = पूर्णांकel_nhlt_get_dmic_geo(sdev->dev, nhlt);
		पूर्णांकel_nhlt_मुक्त(nhlt);
		अगर (dmic_num >= 1 && dmic_num <= 4)
			वापस dmic_num;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर अक्षर *fixup_tplg_name(काष्ठा snd_sof_dev *sdev,
				   स्थिर अक्षर *sof_tplg_filename,
				   स्थिर अक्षर *idisp_str,
				   स्थिर अक्षर *dmic_str)
अणु
	स्थिर अक्षर *tplg_filename = शून्य;
	अक्षर *filename, *पंचांगp;
	स्थिर अक्षर *split_ext;

	filename = kstrdup(sof_tplg_filename, GFP_KERNEL);
	अगर (!filename)
		वापस शून्य;

	/* this assumes a .tplg extension */
	पंचांगp = filename;
	split_ext = strsep(&पंचांगp, ".");
	अगर (split_ext)
		tplg_filename = devm_kaप्र_लिखो(sdev->dev, GFP_KERNEL,
					       "%s%s%s.tplg",
					       split_ext, idisp_str, dmic_str);
	kमुक्त(filename);

	वापस tplg_filename;
पूर्ण

अटल पूर्णांक dmic_topology_fixup(काष्ठा snd_sof_dev *sdev,
			       स्थिर अक्षर **tplg_filename,
			       स्थिर अक्षर *idisp_str,
			       पूर्णांक *dmic_found)
अणु
	स्थिर अक्षर *शेष_tplg_filename = *tplg_filename;
	स्थिर अक्षर *fixed_tplg_filename;
	स्थिर अक्षर *dmic_str;
	पूर्णांक dmic_num;

	/* first check NHLT क्रम DMICs */
	dmic_num = check_nhlt_dmic(sdev);

	/* allow क्रम module parameter override */
	अगर (hda_dmic_num != -1) अणु
		dev_dbg(sdev->dev,
			"overriding DMICs detected in NHLT tables %d by kernel param %d\n",
			dmic_num, hda_dmic_num);
		dmic_num = hda_dmic_num;
	पूर्ण

	चयन (dmic_num) अणु
	हाल 1:
		dmic_str = "-1ch";
		अवरोध;
	हाल 2:
		dmic_str = "-2ch";
		अवरोध;
	हाल 3:
		dmic_str = "-3ch";
		अवरोध;
	हाल 4:
		dmic_str = "-4ch";
		अवरोध;
	शेष:
		dmic_num = 0;
		dmic_str = "";
		अवरोध;
	पूर्ण

	fixed_tplg_filename = fixup_tplg_name(sdev, शेष_tplg_filename,
					      idisp_str, dmic_str);
	अगर (!fixed_tplg_filename)
		वापस -ENOMEM;

	dev_info(sdev->dev, "DMICs detected in NHLT tables: %d\n", dmic_num);
	*dmic_found = dmic_num;
	*tplg_filename = fixed_tplg_filename;

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक hda_init_caps(काष्ठा snd_sof_dev *sdev)
अणु
	काष्ठा hdac_bus *bus = sof_to_bus(sdev);
	काष्ठा snd_sof_pdata *pdata = sdev->pdata;
#अगर IS_ENABLED(CONFIG_SND_SOC_SOF_HDA)
	काष्ठा hdac_ext_link *hlink;
#पूर्ण_अगर
	काष्ठा sof_पूर्णांकel_hda_dev *hdev = pdata->hw_pdata;
	u32 link_mask;
	पूर्णांक ret = 0;

	/* check अगर dsp is there */
	अगर (bus->ppcap)
		dev_dbg(sdev->dev, "PP capability, will probe DSP later.\n");

	/* Init HDA controller after i915 init */
	ret = hda_dsp_ctrl_init_chip(sdev, true);
	अगर (ret < 0) अणु
		dev_err(bus->dev, "error: init chip failed with ret: %d\n",
			ret);
		वापस ret;
	पूर्ण

	/* scan SoundWire capabilities exposed by DSDT */
	ret = hda_sdw_acpi_scan(sdev);
	अगर (ret < 0) अणु
		dev_dbg(sdev->dev, "skipping SoundWire, not detected with ACPI scan\n");
		जाओ skip_soundwire;
	पूर्ण

	link_mask = hdev->info.link_mask;
	अगर (!link_mask) अणु
		dev_dbg(sdev->dev, "skipping SoundWire, no links enabled\n");
		जाओ skip_soundwire;
	पूर्ण

	/*
	 * probe/allocate SoundWire resources.
	 * The hardware configuration takes place in hda_sdw_startup
	 * after घातer rails are enabled.
	 * It's entirely possible to have a mix of I2S/DMIC/SoundWire
	 * devices, so we allocate the resources in all हालs.
	 */
	ret = hda_sdw_probe(sdev);
	अगर (ret < 0) अणु
		dev_err(sdev->dev, "error: SoundWire probe error\n");
		वापस ret;
	पूर्ण

skip_soundwire:

#अगर IS_ENABLED(CONFIG_SND_SOC_SOF_HDA)
	अगर (bus->mlcap)
		snd_hdac_ext_bus_get_ml_capabilities(bus);

	/* create codec instances */
	hda_codec_probe_bus(sdev, hda_codec_use_common_hdmi);

	अगर (!HDA_IDISP_CODEC(bus->codec_mask))
		hda_codec_i915_display_घातer(sdev, false);

	/*
	 * we are करोne probing so decrement link counts
	 */
	list_क्रम_each_entry(hlink, &bus->hlink_list, list)
		snd_hdac_ext_bus_link_put(bus, hlink);
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा sof_पूर्णांकel_dsp_desc
	*get_chip_info(काष्ठा snd_sof_pdata *pdata)
अणु
	स्थिर काष्ठा sof_dev_desc *desc = pdata->desc;
	स्थिर काष्ठा sof_पूर्णांकel_dsp_desc *chip_info;

	chip_info = desc->chip_info;

	वापस chip_info;
पूर्ण

अटल irqवापस_t hda_dsp_पूर्णांकerrupt_handler(पूर्णांक irq, व्योम *context)
अणु
	काष्ठा snd_sof_dev *sdev = context;

	/*
	 * Get global पूर्णांकerrupt status. It includes all hardware पूर्णांकerrupt
	 * sources in the Intel HD Audio controller.
	 */
	अगर (snd_sof_dsp_पढ़ो(sdev, HDA_DSP_HDA_BAR, SOF_HDA_INTSTS) &
	    SOF_HDA_INTSTS_GIS) अणु

		/* disable GIE पूर्णांकerrupt */
		snd_sof_dsp_update_bits(sdev, HDA_DSP_HDA_BAR,
					SOF_HDA_INTCTL,
					SOF_HDA_INT_GLOBAL_EN,
					0);

		वापस IRQ_WAKE_THREAD;
	पूर्ण

	वापस IRQ_NONE;
पूर्ण

अटल irqवापस_t hda_dsp_पूर्णांकerrupt_thपढ़ो(पूर्णांक irq, व्योम *context)
अणु
	काष्ठा snd_sof_dev *sdev = context;
	काष्ठा sof_पूर्णांकel_hda_dev *hdev = sdev->pdata->hw_pdata;

	/* deal with streams and controller first */
	अगर (hda_dsp_check_stream_irq(sdev))
		hda_dsp_stream_thपढ़ोed_handler(irq, sdev);

	अगर (hda_dsp_check_ipc_irq(sdev))
		sof_ops(sdev)->irq_thपढ़ो(irq, sdev);

	अगर (hda_dsp_check_sdw_irq(sdev))
		hda_dsp_sdw_thपढ़ो(irq, hdev->sdw);

	अगर (hda_sdw_check_wakeen_irq(sdev))
		hda_sdw_process_wakeen(sdev);

	/* enable GIE पूर्णांकerrupt */
	snd_sof_dsp_update_bits(sdev, HDA_DSP_HDA_BAR,
				SOF_HDA_INTCTL,
				SOF_HDA_INT_GLOBAL_EN,
				SOF_HDA_INT_GLOBAL_EN);

	वापस IRQ_HANDLED;
पूर्ण

पूर्णांक hda_dsp_probe(काष्ठा snd_sof_dev *sdev)
अणु
	काष्ठा pci_dev *pci = to_pci_dev(sdev->dev);
	काष्ठा sof_पूर्णांकel_hda_dev *hdev;
	काष्ठा hdac_bus *bus;
	स्थिर काष्ठा sof_पूर्णांकel_dsp_desc *chip;
	पूर्णांक ret = 0;

	/*
	 * detect DSP by checking class/subclass/prog-id inक्रमmation
	 * class=04 subclass 03 prog-अगर 00: no DSP, legacy driver is required
	 * class=04 subclass 01 prog-अगर 00: DSP is present
	 *   (and may be required e.g. क्रम DMIC or SSP support)
	 * class=04 subclass 03 prog-अगर 80: either of DSP or legacy mode works
	 */
	अगर (pci->class == 0x040300) अणु
		dev_err(sdev->dev, "error: the DSP is not enabled on this platform, aborting probe\n");
		वापस -ENODEV;
	पूर्ण अन्यथा अगर (pci->class != 0x040100 && pci->class != 0x040380) अणु
		dev_err(sdev->dev, "error: unknown PCI class/subclass/prog-if 0x%06x found, aborting probe\n", pci->class);
		वापस -ENODEV;
	पूर्ण
	dev_info(sdev->dev, "DSP detected with PCI class/subclass/prog-if 0x%06x\n", pci->class);

	chip = get_chip_info(sdev->pdata);
	अगर (!chip) अणु
		dev_err(sdev->dev, "error: no such device supported, chip id:%x\n",
			pci->device);
		ret = -EIO;
		जाओ err;
	पूर्ण

	hdev = devm_kzalloc(sdev->dev, माप(*hdev), GFP_KERNEL);
	अगर (!hdev)
		वापस -ENOMEM;
	sdev->pdata->hw_pdata = hdev;
	hdev->desc = chip;

	hdev->dmic_dev = platक्रमm_device_रेजिस्टर_data(sdev->dev, "dmic-codec",
						       PLATFORM_DEVID_NONE,
						       शून्य, 0);
	अगर (IS_ERR(hdev->dmic_dev)) अणु
		dev_err(sdev->dev, "error: failed to create DMIC device\n");
		वापस PTR_ERR(hdev->dmic_dev);
	पूर्ण

	/*
	 * use position update IPC अगर either it is क्रमced
	 * or we करोn't have other choice
	 */
#अगर IS_ENABLED(CONFIG_SND_SOC_SOF_DEBUG_FORCE_IPC_POSITION)
	hdev->no_ipc_position = 0;
#अन्यथा
	hdev->no_ipc_position = sof_ops(sdev)->pcm_poपूर्णांकer ? 1 : 0;
#पूर्ण_अगर

	/* set up HDA base */
	bus = sof_to_bus(sdev);
	ret = hda_init(sdev);
	अगर (ret < 0)
		जाओ hdac_bus_unmap;

	/* DSP base */
#अगर IS_ENABLED(CONFIG_PCI)
	sdev->bar[HDA_DSP_BAR] = pci_ioremap_bar(pci, HDA_DSP_BAR);
#पूर्ण_अगर
	अगर (!sdev->bar[HDA_DSP_BAR]) अणु
		dev_err(sdev->dev, "error: ioremap error\n");
		ret = -ENXIO;
		जाओ hdac_bus_unmap;
	पूर्ण

	sdev->mmio_bar = HDA_DSP_BAR;
	sdev->mailbox_bar = HDA_DSP_BAR;

	/* allow 64bit DMA address अगर supported by H/W */
	अगर (dma_set_mask_and_coherent(&pci->dev, DMA_BIT_MASK(64))) अणु
		dev_dbg(sdev->dev, "DMA mask is 32 bit\n");
		dma_set_mask_and_coherent(&pci->dev, DMA_BIT_MASK(32));
	पूर्ण

	/* init streams */
	ret = hda_dsp_stream_init(sdev);
	अगर (ret < 0) अणु
		dev_err(sdev->dev, "error: failed to init streams\n");
		/*
		 * not all errors are due to memory issues, but trying
		 * to मुक्त everything करोes not harm
		 */
		जाओ मुक्त_streams;
	पूर्ण

	/*
	 * रेजिस्टर our IRQ
	 * let's try to enable msi firstly
	 * अगर it fails, use legacy पूर्णांकerrupt mode
	 * TODO: support msi multiple vectors
	 */
	अगर (hda_use_msi && pci_alloc_irq_vectors(pci, 1, 1, PCI_IRQ_MSI) > 0) अणु
		dev_info(sdev->dev, "use msi interrupt mode\n");
		sdev->ipc_irq = pci_irq_vector(pci, 0);
		/* initialised to "false" by kzalloc() */
		sdev->msi_enabled = true;
	पूर्ण

	अगर (!sdev->msi_enabled) अणु
		dev_info(sdev->dev, "use legacy interrupt mode\n");
		/*
		 * in IO-APIC mode, hda->irq and ipc_irq are using the same
		 * irq number of pci->irq
		 */
		sdev->ipc_irq = pci->irq;
	पूर्ण

	dev_dbg(sdev->dev, "using IPC IRQ %d\n", sdev->ipc_irq);
	ret = request_thपढ़ोed_irq(sdev->ipc_irq, hda_dsp_पूर्णांकerrupt_handler,
				   hda_dsp_पूर्णांकerrupt_thपढ़ो,
				   IRQF_SHARED, "AudioDSP", sdev);
	अगर (ret < 0) अणु
		dev_err(sdev->dev, "error: failed to register IPC IRQ %d\n",
			sdev->ipc_irq);
		जाओ मुक्त_irq_vector;
	पूर्ण

	pci_set_master(pci);
	synchronize_irq(pci->irq);

	/*
	 * clear TCSEL to clear playback on some HD Audio
	 * codecs. PCI TCSEL is defined in the Intel manuals.
	 */
	snd_sof_pci_update_bits(sdev, PCI_TCSEL, 0x07, 0);

	/* init HDA capabilities */
	ret = hda_init_caps(sdev);
	अगर (ret < 0)
		जाओ मुक्त_ipc_irq;

	/* enable ppcap पूर्णांकerrupt */
	hda_dsp_ctrl_ppcap_enable(sdev, true);
	hda_dsp_ctrl_ppcap_पूर्णांक_enable(sdev, true);

	/* set शेष mailbox offset क्रम FW पढ़ोy message */
	sdev->dsp_box.offset = HDA_DSP_MBOX_UPLINK_OFFSET;

	INIT_DELAYED_WORK(&hdev->d0i3_work, hda_dsp_d0i3_work);

	वापस 0;

मुक्त_ipc_irq:
	मुक्त_irq(sdev->ipc_irq, sdev);
मुक्त_irq_vector:
	अगर (sdev->msi_enabled)
		pci_मुक्त_irq_vectors(pci);
मुक्त_streams:
	hda_dsp_stream_मुक्त(sdev);
/* dsp_unmap: not currently used */
	iounmap(sdev->bar[HDA_DSP_BAR]);
hdac_bus_unmap:
	platक्रमm_device_unरेजिस्टर(hdev->dmic_dev);
	iounmap(bus->remap_addr);
	hda_codec_i915_निकास(sdev);
err:
	वापस ret;
पूर्ण

पूर्णांक hda_dsp_हटाओ(काष्ठा snd_sof_dev *sdev)
अणु
	काष्ठा sof_पूर्णांकel_hda_dev *hda = sdev->pdata->hw_pdata;
	काष्ठा hdac_bus *bus = sof_to_bus(sdev);
	काष्ठा pci_dev *pci = to_pci_dev(sdev->dev);
	स्थिर काष्ठा sof_पूर्णांकel_dsp_desc *chip = hda->desc;

	/* cancel any attempt क्रम DSP D0I3 */
	cancel_delayed_work_sync(&hda->d0i3_work);

#अगर IS_ENABLED(CONFIG_SND_SOC_SOF_HDA)
	/* codec removal, invoke bus_device_हटाओ */
	snd_hdac_ext_bus_device_हटाओ(bus);
#पूर्ण_अगर

	hda_sdw_निकास(sdev);

	अगर (!IS_ERR_OR_शून्य(hda->dmic_dev))
		platक्रमm_device_unरेजिस्टर(hda->dmic_dev);

	/* disable DSP IRQ */
	snd_sof_dsp_update_bits(sdev, HDA_DSP_PP_BAR, SOF_HDA_REG_PP_PPCTL,
				SOF_HDA_PPCTL_PIE, 0);

	/* disable CIE and GIE पूर्णांकerrupts */
	snd_sof_dsp_update_bits(sdev, HDA_DSP_HDA_BAR, SOF_HDA_INTCTL,
				SOF_HDA_INT_CTRL_EN | SOF_HDA_INT_GLOBAL_EN, 0);

	/* disable cores */
	अगर (chip)
		snd_sof_dsp_core_घातer_करोwn(sdev, chip->host_managed_cores_mask);

	/* disable DSP */
	snd_sof_dsp_update_bits(sdev, HDA_DSP_PP_BAR, SOF_HDA_REG_PP_PPCTL,
				SOF_HDA_PPCTL_GPROCEN, 0);

	मुक्त_irq(sdev->ipc_irq, sdev);
	अगर (sdev->msi_enabled)
		pci_मुक्त_irq_vectors(pci);

	hda_dsp_stream_मुक्त(sdev);
#अगर IS_ENABLED(CONFIG_SND_SOC_SOF_HDA)
	snd_hdac_link_मुक्त_all(bus);
#पूर्ण_अगर

	iounmap(sdev->bar[HDA_DSP_BAR]);
	iounmap(bus->remap_addr);

#अगर IS_ENABLED(CONFIG_SND_SOC_SOF_HDA)
	snd_hdac_ext_bus_निकास(bus);
#पूर्ण_अगर
	hda_codec_i915_निकास(sdev);

	वापस 0;
पूर्ण

#अगर IS_ENABLED(CONFIG_SND_SOC_SOF_HDA)
अटल पूर्णांक hda_generic_machine_select(काष्ठा snd_sof_dev *sdev)
अणु
	काष्ठा hdac_bus *bus = sof_to_bus(sdev);
	काष्ठा snd_soc_acpi_mach_params *mach_params;
	काष्ठा snd_soc_acpi_mach *hda_mach;
	काष्ठा snd_sof_pdata *pdata = sdev->pdata;
	स्थिर अक्षर *tplg_filename;
	स्थिर अक्षर *idisp_str;
	पूर्णांक dmic_num = 0;
	पूर्णांक codec_num = 0;
	पूर्णांक ret;
	पूर्णांक i;

	/* codec detection */
	अगर (!bus->codec_mask) अणु
		dev_info(bus->dev, "no hda codecs found!\n");
	पूर्ण अन्यथा अणु
		dev_info(bus->dev, "hda codecs found, mask %lx\n",
			 bus->codec_mask);

		क्रम (i = 0; i < HDA_MAX_CODECS; i++) अणु
			अगर (bus->codec_mask & (1 << i))
				codec_num++;
		पूर्ण

		/*
		 * If no machine driver is found, then:
		 *
		 * generic hda machine driver can handle:
		 *  - one HDMI codec, and/or
		 *  - one बाह्यal HDAudio codec
		 */
		अगर (!pdata->machine && codec_num <= 2) अणु
			hda_mach = snd_soc_acpi_पूर्णांकel_hda_machines;

			dev_info(bus->dev, "using HDA machine driver %s now\n",
				 hda_mach->drv_name);

			अगर (codec_num == 1 && HDA_IDISP_CODEC(bus->codec_mask))
				idisp_str = "-idisp";
			अन्यथा
				idisp_str = "";

			/* topology: use the info from hda_machines */
			tplg_filename = hda_mach->sof_tplg_filename;
			ret = dmic_topology_fixup(sdev, &tplg_filename, idisp_str, &dmic_num);
			अगर (ret < 0)
				वापस ret;

			hda_mach->mach_params.dmic_num = dmic_num;
			pdata->machine = hda_mach;
			pdata->tplg_filename = tplg_filename;
		पूर्ण
	पूर्ण

	/* used by hda machine driver to create dai links */
	अगर (pdata->machine) अणु
		mach_params = (काष्ठा snd_soc_acpi_mach_params *)
			&pdata->machine->mach_params;
		mach_params->codec_mask = bus->codec_mask;
		mach_params->common_hdmi_codec_drv = hda_codec_use_common_hdmi;
	पूर्ण

	वापस 0;
पूर्ण
#अन्यथा
अटल पूर्णांक hda_generic_machine_select(काष्ठा snd_sof_dev *sdev)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_SND_SOC_SOF_INTEL_SOUNDWIRE)
/* Check अगर all Slaves defined on the link can be found */
अटल bool link_slaves_found(काष्ठा snd_sof_dev *sdev,
			      स्थिर काष्ठा snd_soc_acpi_link_adr *link,
			      काष्ठा sdw_पूर्णांकel_ctx *sdw)
अणु
	काष्ठा hdac_bus *bus = sof_to_bus(sdev);
	काष्ठा sdw_पूर्णांकel_slave_id *ids = sdw->ids;
	पूर्णांक num_slaves = sdw->num_slaves;
	अचिन्हित पूर्णांक part_id, link_id, unique_id, mfg_id;
	पूर्णांक i, j, k;

	क्रम (i = 0; i < link->num_adr; i++) अणु
		u64 adr = link->adr_d[i].adr;
		पूर्णांक reported_part_count = 0;

		mfg_id = SDW_MFG_ID(adr);
		part_id = SDW_PART_ID(adr);
		link_id = SDW_DISCO_LINK_ID(adr);

		क्रम (j = 0; j < num_slaves; j++) अणु
			/* find out how many identical parts were reported on that link */
			अगर (ids[j].link_id == link_id &&
			    ids[j].id.part_id == part_id &&
			    ids[j].id.mfg_id == mfg_id)
				reported_part_count++;
		पूर्ण

		क्रम (j = 0; j < num_slaves; j++) अणु
			पूर्णांक expected_part_count = 0;

			अगर (ids[j].link_id != link_id ||
			    ids[j].id.part_id != part_id ||
			    ids[j].id.mfg_id != mfg_id)
				जारी;

			/* find out how many identical parts are expected */
			क्रम (k = 0; k < link->num_adr; k++) अणु
				u64 adr2 = link->adr_d[i].adr;
				अचिन्हित पूर्णांक part_id2, link_id2, mfg_id2;

				mfg_id2 = SDW_MFG_ID(adr2);
				part_id2 = SDW_PART_ID(adr2);
				link_id2 = SDW_DISCO_LINK_ID(adr2);

				अगर (link_id2 == link_id &&
				    part_id2 == part_id &&
				    mfg_id2 == mfg_id)
					expected_part_count++;
			पूर्ण

			अगर (reported_part_count == expected_part_count) अणु
				/*
				 * we have to check unique id
				 * अगर there is more than one
				 * Slave on the link
				 */
				unique_id = SDW_UNIQUE_ID(adr);
				अगर (reported_part_count == 1 ||
				    ids[j].id.unique_id == unique_id) अणु
					dev_dbg(bus->dev, "found %x at link %d\n",
						part_id, link_id);
					अवरोध;
				पूर्ण
			पूर्ण अन्यथा अणु
				dev_dbg(bus->dev, "part %x reported %d expected %d on link %d, skipping\n",
					part_id, reported_part_count, expected_part_count, link_id);
			पूर्ण
		पूर्ण
		अगर (j == num_slaves) अणु
			dev_dbg(bus->dev,
				"Slave %x not found\n",
				part_id);
			वापस false;
		पूर्ण
	पूर्ण
	वापस true;
पूर्ण

अटल पूर्णांक hda_sdw_machine_select(काष्ठा snd_sof_dev *sdev)
अणु
	काष्ठा snd_sof_pdata *pdata = sdev->pdata;
	स्थिर काष्ठा snd_soc_acpi_link_adr *link;
	काष्ठा snd_soc_acpi_mach *mach;
	काष्ठा sof_पूर्णांकel_hda_dev *hdev;
	u32 link_mask;
	पूर्णांक i;

	hdev = pdata->hw_pdata;
	link_mask = hdev->info.link_mask;

	/*
	 * Select SoundWire machine driver अगर needed using the
	 * alternate tables. This हाल deals with SoundWire-only
	 * machines, क्रम mixed हालs with I2C/I2S the detection relies
	 * on the HID list.
	 */
	अगर (link_mask && !pdata->machine) अणु
		क्रम (mach = pdata->desc->alt_machines;
		     mach && mach->link_mask; mach++) अणु
			/*
			 * On some platक्रमms such as Up Extreme all links
			 * are enabled but only one link can be used by
			 * बाह्यal codec. Instead of exact match of two masks,
			 * first check whether link_mask of mach is subset of
			 * link_mask supported by hw and then go on searching
			 * link_adr
			 */
			अगर (~link_mask & mach->link_mask)
				जारी;

			/* No need to match adr अगर there is no links defined */
			अगर (!mach->links)
				अवरोध;

			link = mach->links;
			क्रम (i = 0; i < hdev->info.count && link->num_adr;
			     i++, link++) अणु
				/*
				 * Try next machine अगर any expected Slaves
				 * are not found on this link.
				 */
				अगर (!link_slaves_found(sdev, link, hdev->sdw))
					अवरोध;
			पूर्ण
			/* Found अगर all Slaves are checked */
			अगर (i == hdev->info.count || !link->num_adr)
				अवरोध;
		पूर्ण
		अगर (mach && mach->link_mask) अणु
			पूर्णांक dmic_num = 0;

			pdata->machine = mach;
			mach->mach_params.links = mach->links;
			mach->mach_params.link_mask = mach->link_mask;
			mach->mach_params.platक्रमm = dev_name(sdev->dev);
			अगर (mach->sof_fw_filename)
				pdata->fw_filename = mach->sof_fw_filename;
			अन्यथा
				pdata->fw_filename = pdata->desc->शेष_fw_filename;
			pdata->tplg_filename = mach->sof_tplg_filename;

			/*
			 * DMICs use up to 4 pins and are typically pin-muxed with SoundWire
			 * link 2 and 3, thus we only try to enable dmics अगर all conditions
			 * are true:
			 * a) link 2 and 3 are not used by SoundWire
			 * b) the NHLT table reports the presence of microphones
			 */
			अगर (!(mach->link_mask & GENMASK(3, 2))) अणु
				स्थिर अक्षर *tplg_filename = mach->sof_tplg_filename;
				पूर्णांक ret;

				ret = dmic_topology_fixup(sdev, &tplg_filename, "", &dmic_num);

				अगर (ret < 0)
					वापस ret;

				pdata->tplg_filename = tplg_filename;
			पूर्ण
			mach->mach_params.dmic_num = dmic_num;

			dev_dbg(sdev->dev,
				"SoundWire machine driver %s topology %s\n",
				mach->drv_name,
				pdata->tplg_filename);
		पूर्ण अन्यथा अणु
			dev_info(sdev->dev,
				 "No SoundWire machine driver found\n");
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
#अन्यथा
अटल पूर्णांक hda_sdw_machine_select(काष्ठा snd_sof_dev *sdev)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

व्योम hda_set_mach_params(स्थिर काष्ठा snd_soc_acpi_mach *mach,
			 काष्ठा snd_sof_dev *sdev)
अणु
	काष्ठा snd_sof_pdata *pdata = sdev->pdata;
	स्थिर काष्ठा sof_dev_desc *desc = pdata->desc;
	काष्ठा snd_soc_acpi_mach_params *mach_params;

	mach_params = (काष्ठा snd_soc_acpi_mach_params *)&mach->mach_params;
	mach_params->platक्रमm = dev_name(sdev->dev);
	mach_params->num_dai_drivers = desc->ops->num_drv;
	mach_params->dai_drivers = desc->ops->drv;
पूर्ण

व्योम hda_machine_select(काष्ठा snd_sof_dev *sdev)
अणु
	काष्ठा snd_sof_pdata *sof_pdata = sdev->pdata;
	स्थिर काष्ठा sof_dev_desc *desc = sof_pdata->desc;
	काष्ठा snd_soc_acpi_mach *mach;

	mach = snd_soc_acpi_find_machine(desc->machines);
	अगर (mach) अणु
		/*
		 * If tplg file name is overridden, use it instead of
		 * the one set in mach table
		 */
		अगर (!sof_pdata->tplg_filename)
			sof_pdata->tplg_filename = mach->sof_tplg_filename;

		sof_pdata->machine = mach;

		अगर (mach->link_mask) अणु
			mach->mach_params.links = mach->links;
			mach->mach_params.link_mask = mach->link_mask;
		पूर्ण
	पूर्ण

	/*
	 * If I2S fails, try SoundWire
	 */
	hda_sdw_machine_select(sdev);

	/*
	 * Choose HDA generic machine driver अगर mach is शून्य.
	 * Otherwise, set certain mach params.
	 */
	hda_generic_machine_select(sdev);

	अगर (!sof_pdata->machine)
		dev_warn(sdev->dev, "warning: No matching ASoC machine driver found\n");
पूर्ण

पूर्णांक hda_pci_पूर्णांकel_probe(काष्ठा pci_dev *pci, स्थिर काष्ठा pci_device_id *pci_id)
अणु
	पूर्णांक ret;

	ret = snd_पूर्णांकel_dsp_driver_probe(pci);
	अगर (ret != SND_INTEL_DSP_DRIVER_ANY && ret != SND_INTEL_DSP_DRIVER_SOF) अणु
		dev_dbg(&pci->dev, "SOF PCI driver not selected, aborting probe\n");
		वापस -ENODEV;
	पूर्ण

	वापस sof_pci_probe(pci, pci_id);
पूर्ण
EXPORT_SYMBOL_NS(hda_pci_पूर्णांकel_probe, SND_SOC_SOF_INTEL_HDA_COMMON);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_IMPORT_NS(SND_SOC_SOF_PCI_DEV);
MODULE_IMPORT_NS(SND_SOC_SOF_HDA_AUDIO_CODEC);
MODULE_IMPORT_NS(SND_SOC_SOF_HDA_AUDIO_CODEC_I915);
MODULE_IMPORT_NS(SND_SOC_SOF_XTENSA);
MODULE_IMPORT_NS(SND_INTEL_SOUNDWIRE_ACPI);
MODULE_IMPORT_NS(SOUNDWIRE_INTEL_INIT);
