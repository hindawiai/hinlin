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
 * Hardware पूर्णांकerface क्रम HDA DSP code loader
 */

#समावेश <linux/firmware.h>
#समावेश <sound/hdaudio_ext.h>
#समावेश <sound/hda_रेजिस्टर.h>
#समावेश <sound/sof.h>
#समावेश "ext_manifest.h"
#समावेश "../ops.h"
#समावेश "hda.h"

#घोषणा HDA_FW_BOOT_ATTEMPTS	3
#घोषणा HDA_CL_STREAM_FORMAT 0x40

अटल काष्ठा hdac_ext_stream *cl_stream_prepare(काष्ठा snd_sof_dev *sdev, अचिन्हित पूर्णांक क्रमmat,
						 अचिन्हित पूर्णांक size, काष्ठा snd_dma_buffer *dmab,
						 पूर्णांक direction)
अणु
	काष्ठा hdac_ext_stream *dsp_stream;
	काष्ठा hdac_stream *hstream;
	काष्ठा pci_dev *pci = to_pci_dev(sdev->dev);
	पूर्णांक ret;

	dsp_stream = hda_dsp_stream_get(sdev, direction, 0);

	अगर (!dsp_stream) अणु
		dev_err(sdev->dev, "error: no stream available\n");
		वापस ERR_PTR(-ENODEV);
	पूर्ण
	hstream = &dsp_stream->hstream;
	hstream->substream = शून्य;

	/* allocate DMA buffer */
	ret = snd_dma_alloc_pages(SNDRV_DMA_TYPE_DEV_SG, &pci->dev, size, dmab);
	अगर (ret < 0) अणु
		dev_err(sdev->dev, "error: memory alloc failed: %d\n", ret);
		जाओ error;
	पूर्ण

	hstream->period_bytes = 0;/* initialize period_bytes */
	hstream->क्रमmat_val = क्रमmat;
	hstream->bufsize = size;

	अगर (direction == SNDRV_PCM_STREAM_CAPTURE) अणु
		ret = hda_dsp_iccmax_stream_hw_params(sdev, dsp_stream, dmab, शून्य);
		अगर (ret < 0) अणु
			dev_err(sdev->dev, "error: iccmax stream prepare failed: %d\n", ret);
			जाओ error;
		पूर्ण
	पूर्ण अन्यथा अणु
		ret = hda_dsp_stream_hw_params(sdev, dsp_stream, dmab, शून्य);
		अगर (ret < 0) अणु
			dev_err(sdev->dev, "error: hdac prepare failed: %d\n", ret);
			जाओ error;
		पूर्ण
		hda_dsp_stream_spib_config(sdev, dsp_stream, HDA_DSP_SPIB_ENABLE, size);
	पूर्ण

	वापस dsp_stream;

error:
	hda_dsp_stream_put(sdev, direction, hstream->stream_tag);
	snd_dma_मुक्त_pages(dmab);
	वापस ERR_PTR(ret);
पूर्ण

/*
 * first boot sequence has some extra steps. core 0 रुकोs क्रम घातer
 * status on core 1, so घातer up core 1 also momentarily, keep it in
 * reset/stall and then turn it off
 */
अटल पूर्णांक cl_dsp_init(काष्ठा snd_sof_dev *sdev, पूर्णांक stream_tag)
अणु
	काष्ठा sof_पूर्णांकel_hda_dev *hda = sdev->pdata->hw_pdata;
	स्थिर काष्ठा sof_पूर्णांकel_dsp_desc *chip = hda->desc;
	अचिन्हित पूर्णांक status;
	u32 flags;
	पूर्णांक ret;
	पूर्णांक i;

	/* step 1: घातer up corex */
	ret = snd_sof_dsp_core_घातer_up(sdev, chip->host_managed_cores_mask);
	अगर (ret < 0) अणु
		अगर (hda->boot_iteration == HDA_FW_BOOT_ATTEMPTS)
			dev_err(sdev->dev, "error: dsp core 0/1 power up failed\n");
		जाओ err;
	पूर्ण

	/* DSP is घातered up, set all SSPs to slave mode */
	क्रम (i = 0; i < chip->ssp_count; i++) अणु
		snd_sof_dsp_update_bits_unlocked(sdev, HDA_DSP_BAR,
						 chip->ssp_base_offset
						 + i * SSP_DEV_MEM_SIZE
						 + SSP_SSC1_OFFSET,
						 SSP_SET_SLAVE,
						 SSP_SET_SLAVE);
	पूर्ण

	/* step 2: purge FW request */
	snd_sof_dsp_ग_लिखो(sdev, HDA_DSP_BAR, chip->ipc_req,
			  chip->ipc_req_mask | (HDA_DSP_IPC_PURGE_FW |
			  ((stream_tag - 1) << 9)));

	/* step 3: unset core 0 reset state & unstall/run core 0 */
	ret = hda_dsp_core_run(sdev, BIT(0));
	अगर (ret < 0) अणु
		अगर (hda->boot_iteration == HDA_FW_BOOT_ATTEMPTS)
			dev_err(sdev->dev,
				"error: dsp core start failed %d\n", ret);
		ret = -EIO;
		जाओ err;
	पूर्ण

	/* step 4: रुको क्रम IPC DONE bit from ROM */
	ret = snd_sof_dsp_पढ़ो_poll_समयout(sdev, HDA_DSP_BAR,
					    chip->ipc_ack, status,
					    ((status & chip->ipc_ack_mask)
						    == chip->ipc_ack_mask),
					    HDA_DSP_REG_POLL_INTERVAL_US,
					    HDA_DSP_INIT_TIMEOUT_US);

	अगर (ret < 0) अणु
		अगर (hda->boot_iteration == HDA_FW_BOOT_ATTEMPTS)
			dev_err(sdev->dev,
				"error: %s: timeout for HIPCIE done\n",
				__func__);
		जाओ err;
	पूर्ण

	/* set DONE bit to clear the reply IPC message */
	snd_sof_dsp_update_bits_क्रमced(sdev, HDA_DSP_BAR,
				       chip->ipc_ack,
				       chip->ipc_ack_mask,
				       chip->ipc_ack_mask);

	/* step 5: घातer करोwn cores that are no दीर्घer needed */
	ret = snd_sof_dsp_core_घातer_करोwn(sdev, chip->host_managed_cores_mask &
					  ~(chip->init_core_mask));
	अगर (ret < 0) अणु
		अगर (hda->boot_iteration == HDA_FW_BOOT_ATTEMPTS)
			dev_err(sdev->dev,
				"error: dsp core x power down failed\n");
		जाओ err;
	पूर्ण

	/* step 6: enable IPC पूर्णांकerrupts */
	hda_dsp_ipc_पूर्णांक_enable(sdev);

	/* step 7: रुको क्रम ROM init */
	ret = snd_sof_dsp_पढ़ो_poll_समयout(sdev, HDA_DSP_BAR,
					HDA_DSP_SRAM_REG_ROM_STATUS, status,
					((status & HDA_DSP_ROM_STS_MASK)
						== HDA_DSP_ROM_INIT),
					HDA_DSP_REG_POLL_INTERVAL_US,
					chip->rom_init_समयout *
					USEC_PER_MSEC);
	अगर (!ret)
		वापस 0;

	अगर (hda->boot_iteration == HDA_FW_BOOT_ATTEMPTS)
		dev_err(sdev->dev,
			"error: %s: timeout HDA_DSP_SRAM_REG_ROM_STATUS read\n",
			__func__);

err:
	flags = SOF_DBG_DUMP_REGS | SOF_DBG_DUMP_PCI | SOF_DBG_DUMP_MBOX;

	/* क्रमce error log level after max boot attempts */
	अगर (hda->boot_iteration == HDA_FW_BOOT_ATTEMPTS)
		flags |= SOF_DBG_DUMP_FORCE_ERR_LEVEL;

	hda_dsp_dump(sdev, flags);
	snd_sof_dsp_core_घातer_करोwn(sdev, chip->host_managed_cores_mask);

	वापस ret;
पूर्ण

अटल पूर्णांक cl_trigger(काष्ठा snd_sof_dev *sdev,
		      काष्ठा hdac_ext_stream *stream, पूर्णांक cmd)
अणु
	काष्ठा hdac_stream *hstream = &stream->hstream;
	पूर्णांक sd_offset = SOF_STREAM_SD_OFFSET(hstream);

	/* code loader is special हाल that reuses stream ops */
	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
		snd_sof_dsp_update_bits(sdev, HDA_DSP_HDA_BAR, SOF_HDA_INTCTL,
					1 << hstream->index,
					1 << hstream->index);

		snd_sof_dsp_update_bits(sdev, HDA_DSP_HDA_BAR,
					sd_offset,
					SOF_HDA_SD_CTL_DMA_START |
					SOF_HDA_CL_DMA_SD_INT_MASK,
					SOF_HDA_SD_CTL_DMA_START |
					SOF_HDA_CL_DMA_SD_INT_MASK);

		hstream->running = true;
		वापस 0;
	शेष:
		वापस hda_dsp_stream_trigger(sdev, stream, cmd);
	पूर्ण
पूर्ण

अटल पूर्णांक cl_cleanup(काष्ठा snd_sof_dev *sdev, काष्ठा snd_dma_buffer *dmab,
		      काष्ठा hdac_ext_stream *stream)
अणु
	काष्ठा hdac_stream *hstream = &stream->hstream;
	पूर्णांक sd_offset = SOF_STREAM_SD_OFFSET(hstream);
	पूर्णांक ret = 0;

	अगर (hstream->direction == SNDRV_PCM_STREAM_PLAYBACK)
		ret = hda_dsp_stream_spib_config(sdev, stream, HDA_DSP_SPIB_DISABLE, 0);
	अन्यथा
		snd_sof_dsp_update_bits(sdev, HDA_DSP_HDA_BAR, sd_offset,
					SOF_HDA_SD_CTL_DMA_START, 0);

	hda_dsp_stream_put(sdev, hstream->direction, hstream->stream_tag);
	hstream->running = 0;
	hstream->substream = शून्य;

	/* reset BDL address */
	snd_sof_dsp_ग_लिखो(sdev, HDA_DSP_HDA_BAR,
			  sd_offset + SOF_HDA_ADSP_REG_CL_SD_BDLPL, 0);
	snd_sof_dsp_ग_लिखो(sdev, HDA_DSP_HDA_BAR,
			  sd_offset + SOF_HDA_ADSP_REG_CL_SD_BDLPU, 0);

	snd_sof_dsp_ग_लिखो(sdev, HDA_DSP_HDA_BAR, sd_offset, 0);
	snd_dma_मुक्त_pages(dmab);
	dmab->area = शून्य;
	hstream->bufsize = 0;
	hstream->क्रमmat_val = 0;

	वापस ret;
पूर्ण

अटल पूर्णांक cl_copy_fw(काष्ठा snd_sof_dev *sdev, काष्ठा hdac_ext_stream *stream)
अणु
	अचिन्हित पूर्णांक reg;
	पूर्णांक ret, status;

	ret = cl_trigger(sdev, stream, SNDRV_PCM_TRIGGER_START);
	अगर (ret < 0) अणु
		dev_err(sdev->dev, "error: DMA trigger start failed\n");
		वापस ret;
	पूर्ण

	status = snd_sof_dsp_पढ़ो_poll_समयout(sdev, HDA_DSP_BAR,
					HDA_DSP_SRAM_REG_ROM_STATUS, reg,
					((reg & HDA_DSP_ROM_STS_MASK)
						== HDA_DSP_ROM_FW_ENTERED),
					HDA_DSP_REG_POLL_INTERVAL_US,
					HDA_DSP_BASEFW_TIMEOUT_US);

	/*
	 * even in हाल of errors we still need to stop the DMAs,
	 * but we वापस the initial error should the DMA stop also fail
	 */

	अगर (status < 0) अणु
		dev_err(sdev->dev,
			"error: %s: timeout HDA_DSP_SRAM_REG_ROM_STATUS read\n",
			__func__);
	पूर्ण

	ret = cl_trigger(sdev, stream, SNDRV_PCM_TRIGGER_STOP);
	अगर (ret < 0) अणु
		dev_err(sdev->dev, "error: DMA trigger stop failed\n");
		अगर (!status)
			status = ret;
	पूर्ण

	वापस status;
पूर्ण

पूर्णांक hda_dsp_cl_boot_firmware_iccmax(काष्ठा snd_sof_dev *sdev)
अणु
	काष्ठा snd_sof_pdata *plat_data = sdev->pdata;
	काष्ठा hdac_ext_stream *iccmax_stream;
	काष्ठा hdac_bus *bus = sof_to_bus(sdev);
	काष्ठा firmware stripped_firmware;
	पूर्णांक ret, ret1;
	u8 original_gb;

	/* save the original LTRP guardband value */
	original_gb = snd_hdac_chip_पढ़ोb(bus, VS_LTRP) & HDA_VS_INTEL_LTRP_GB_MASK;

	अगर (plat_data->fw->size <= plat_data->fw_offset) अणु
		dev_err(sdev->dev, "error: firmware size must be greater than firmware offset\n");
		वापस -EINVAL;
	पूर्ण

	stripped_firmware.size = plat_data->fw->size - plat_data->fw_offset;

	/* prepare capture stream क्रम ICCMAX */
	iccmax_stream = cl_stream_prepare(sdev, HDA_CL_STREAM_FORMAT, stripped_firmware.size,
					  &sdev->dmab_bdl, SNDRV_PCM_STREAM_CAPTURE);
	अगर (IS_ERR(iccmax_stream)) अणु
		dev_err(sdev->dev, "error: dma prepare for ICCMAX stream failed\n");
		वापस PTR_ERR(iccmax_stream);
	पूर्ण

	ret = hda_dsp_cl_boot_firmware(sdev);

	/*
	 * Perक्रमm iccmax stream cleanup. This should be करोne even अगर firmware loading fails.
	 * If the cleanup also fails, we वापस the initial error
	 */
	ret1 = cl_cleanup(sdev, &sdev->dmab_bdl, iccmax_stream);
	अगर (ret1 < 0) अणु
		dev_err(sdev->dev, "error: ICCMAX stream cleanup failed\n");

		/* set वापस value to indicate cleanup failure */
		अगर (!ret)
			ret = ret1;
	पूर्ण

	/* restore the original guardband value after FW boot */
	snd_hdac_chip_updateb(bus, VS_LTRP, HDA_VS_INTEL_LTRP_GB_MASK, original_gb);

	वापस ret;
पूर्ण

पूर्णांक hda_dsp_cl_boot_firmware(काष्ठा snd_sof_dev *sdev)
अणु
	काष्ठा sof_पूर्णांकel_hda_dev *hda = sdev->pdata->hw_pdata;
	काष्ठा snd_sof_pdata *plat_data = sdev->pdata;
	स्थिर काष्ठा sof_dev_desc *desc = plat_data->desc;
	स्थिर काष्ठा sof_पूर्णांकel_dsp_desc *chip_info;
	काष्ठा hdac_ext_stream *stream;
	काष्ठा firmware stripped_firmware;
	पूर्णांक ret, ret1, i;

	chip_info = desc->chip_info;

	अगर (plat_data->fw->size <= plat_data->fw_offset) अणु
		dev_err(sdev->dev, "error: firmware size must be greater than firmware offset\n");
		वापस -EINVAL;
	पूर्ण

	stripped_firmware.data = plat_data->fw->data + plat_data->fw_offset;
	stripped_firmware.size = plat_data->fw->size - plat_data->fw_offset;

	/* init क्रम booting रुको */
	init_रुकोqueue_head(&sdev->boot_रुको);

	/* prepare DMA क्रम code loader stream */
	stream = cl_stream_prepare(sdev, HDA_CL_STREAM_FORMAT, stripped_firmware.size,
				   &sdev->dmab, SNDRV_PCM_STREAM_PLAYBACK);
	अगर (IS_ERR(stream)) अणु
		dev_err(sdev->dev, "error: dma prepare for fw loading failed\n");
		वापस PTR_ERR(stream);
	पूर्ण

	स_नकल(sdev->dmab.area, stripped_firmware.data,
	       stripped_firmware.size);

	/* try ROM init a few बार beक्रमe giving up */
	क्रम (i = 0; i < HDA_FW_BOOT_ATTEMPTS; i++) अणु
		dev_dbg(sdev->dev,
			"Attempting iteration %d of Core En/ROM load...\n", i);

		hda->boot_iteration = i + 1;
		ret = cl_dsp_init(sdev, stream->hstream.stream_tag);

		/* करोn't retry anymore अगर successful */
		अगर (!ret)
			अवरोध;
	पूर्ण

	अगर (i == HDA_FW_BOOT_ATTEMPTS) अणु
		dev_err(sdev->dev, "error: dsp init failed after %d attempts with err: %d\n",
			i, ret);
		dev_err(sdev->dev, "ROM error=0x%x: FW status=0x%x\n",
			snd_sof_dsp_पढ़ो(sdev, HDA_DSP_BAR,
					 HDA_DSP_SRAM_REG_ROM_ERROR),
			snd_sof_dsp_पढ़ो(sdev, HDA_DSP_BAR,
					 HDA_DSP_SRAM_REG_ROM_STATUS));
		जाओ cleanup;
	पूर्ण

	/*
	 * When a SoundWire link is in घड़ी stop state, a Slave
	 * device may trigger in-band wakes क्रम events such as jack
	 * insertion or acoustic event detection. This event will lead
	 * to a WAKEEN पूर्णांकerrupt, handled by the PCI device and routed
	 * to PME अगर the PCI device is in D3. The resume function in
	 * audio PCI driver will be invoked by ACPI क्रम PME event and
	 * initialize the device and process WAKEEN पूर्णांकerrupt.
	 *
	 * The WAKEEN पूर्णांकerrupt should be processed ASAP to prevent an
	 * पूर्णांकerrupt flood, otherwise other पूर्णांकerrupts, such IPC,
	 * cannot work normally.  The WAKEEN is handled after the ROM
	 * is initialized successfully, which ensures घातer rails are
	 * enabled beक्रमe accessing the SoundWire SHIM रेजिस्टरs
	 */
	अगर (!sdev->first_boot)
		hda_sdw_process_wakeen(sdev);

	/*
	 * at this poपूर्णांक DSP ROM has been initialized and
	 * should be पढ़ोy क्रम code loading and firmware boot
	 */
	ret = cl_copy_fw(sdev, stream);
	अगर (!ret) अणु
		dev_dbg(sdev->dev, "Firmware download successful, booting...\n");
	पूर्ण अन्यथा अणु
		hda_dsp_dump(sdev, SOF_DBG_DUMP_REGS | SOF_DBG_DUMP_PCI | SOF_DBG_DUMP_MBOX |
			     SOF_DBG_DUMP_FORCE_ERR_LEVEL);
		dev_err(sdev->dev, "error: load fw failed ret: %d\n", ret);
	पूर्ण

cleanup:
	/*
	 * Perक्रमm codeloader stream cleanup.
	 * This should be करोne even अगर firmware loading fails.
	 * If the cleanup also fails, we वापस the initial error
	 */
	ret1 = cl_cleanup(sdev, &sdev->dmab, stream);
	अगर (ret1 < 0) अणु
		dev_err(sdev->dev, "error: Code loader DSP cleanup failed\n");

		/* set वापस value to indicate cleanup failure */
		अगर (!ret)
			ret = ret1;
	पूर्ण

	/*
	 * वापस primary core id अगर both fw copy
	 * and stream clean up are successful
	 */
	अगर (!ret)
		वापस chip_info->init_core_mask;

	/* disable DSP */
	snd_sof_dsp_update_bits(sdev, HDA_DSP_PP_BAR,
				SOF_HDA_REG_PP_PPCTL,
				SOF_HDA_PPCTL_GPROCEN, 0);
	वापस ret;
पूर्ण

/* pre fw run operations */
पूर्णांक hda_dsp_pre_fw_run(काष्ठा snd_sof_dev *sdev)
अणु
	/* disable घड़ी gating and घातer gating */
	वापस hda_dsp_ctrl_घड़ी_घातer_gating(sdev, false);
पूर्ण

/* post fw run operations */
पूर्णांक hda_dsp_post_fw_run(काष्ठा snd_sof_dev *sdev)
अणु
	पूर्णांक ret;

	अगर (sdev->first_boot) अणु
		ret = hda_sdw_startup(sdev);
		अगर (ret < 0) अणु
			dev_err(sdev->dev,
				"error: could not startup SoundWire links\n");
			वापस ret;
		पूर्ण
	पूर्ण

	hda_sdw_पूर्णांक_enable(sdev, true);

	/* re-enable घड़ी gating and घातer gating */
	वापस hda_dsp_ctrl_घड़ी_घातer_gating(sdev, true);
पूर्ण

/*
 * post fw run operations क्रम ICL,
 * Core 3 will be घातered up and in stall when HPRO is enabled
 */
पूर्णांक hda_dsp_post_fw_run_icl(काष्ठा snd_sof_dev *sdev)
अणु
	काष्ठा sof_पूर्णांकel_hda_dev *hda = sdev->pdata->hw_pdata;
	पूर्णांक ret;

	अगर (sdev->first_boot) अणु
		ret = hda_sdw_startup(sdev);
		अगर (ret < 0) अणु
			dev_err(sdev->dev,
				"error: could not startup SoundWire links\n");
			वापस ret;
		पूर्ण
	पूर्ण

	hda_sdw_पूर्णांक_enable(sdev, true);

	/*
	 * The recommended HW programming sequence क्रम ICL is to
	 * घातer up core 3 and keep it in stall अगर HPRO is enabled.
	 * Major dअगरference between ICL and TGL, on ICL core 3 is managed by
	 * the host whereas on TGL it is handled by the firmware.
	 */
	अगर (!hda->clk_config_lpro) अणु
		ret = snd_sof_dsp_core_घातer_up(sdev, BIT(3));
		अगर (ret < 0) अणु
			dev_err(sdev->dev, "error: dsp core power up failed on core 3\n");
			वापस ret;
		पूर्ण

		snd_sof_dsp_stall(sdev, BIT(3));
	पूर्ण

	/* re-enable घड़ी gating and घातer gating */
	वापस hda_dsp_ctrl_घड़ी_घातer_gating(sdev, true);
पूर्ण

पूर्णांक hda_dsp_ext_man_get_cavs_config_data(काष्ठा snd_sof_dev *sdev,
					 स्थिर काष्ठा sof_ext_man_elem_header *hdr)
अणु
	स्थिर काष्ठा sof_ext_man_cavs_config_data *config_data =
		container_of(hdr, काष्ठा sof_ext_man_cavs_config_data, hdr);
	काष्ठा sof_पूर्णांकel_hda_dev *hda = sdev->pdata->hw_pdata;
	पूर्णांक i, elem_num;

	/* calculate total number of config data elements */
	elem_num = (hdr->size - माप(काष्ठा sof_ext_man_elem_header))
		   / माप(काष्ठा sof_config_elem);
	अगर (elem_num <= 0) अणु
		dev_err(sdev->dev, "cavs config data is inconsistent: %d\n", elem_num);
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < elem_num; i++)
		चयन (config_data->elems[i].token) अणु
		हाल SOF_EXT_MAN_CAVS_CONFIG_EMPTY:
			/* skip empty token */
			अवरोध;
		हाल SOF_EXT_MAN_CAVS_CONFIG_CAVS_LPRO:
			hda->clk_config_lpro = config_data->elems[i].value;
			dev_dbg(sdev->dev, "FW clock config: %s\n",
				hda->clk_config_lpro ? "LPRO" : "HPRO");
			अवरोध;
		हाल SOF_EXT_MAN_CAVS_CONFIG_OUTBOX_SIZE:
		हाल SOF_EXT_MAN_CAVS_CONFIG_INBOX_SIZE:
			/* These elements are defined but not being used yet. No warn is required */
			अवरोध;
		शेष:
			dev_info(sdev->dev, "unsupported token type: %d\n",
				 config_data->elems[i].token);
		पूर्ण

	वापस 0;
पूर्ण

पूर्णांक hda_dsp_core_stall_icl(काष्ठा snd_sof_dev *sdev, अचिन्हित पूर्णांक core_mask)
अणु
	काष्ठा sof_पूर्णांकel_hda_dev *hda = sdev->pdata->hw_pdata;
	स्थिर काष्ठा sof_पूर्णांकel_dsp_desc *chip = hda->desc;

	/* make sure core_mask in host managed cores */
	core_mask &= chip->host_managed_cores_mask;
	अगर (!core_mask) अणु
		dev_err(sdev->dev, "error: core_mask is not in host managed cores\n");
		वापस -EINVAL;
	पूर्ण

	/* stall core */
	snd_sof_dsp_update_bits_unlocked(sdev, HDA_DSP_BAR,
					 HDA_DSP_REG_ADSPCS,
					 HDA_DSP_ADSPCS_CSTALL_MASK(core_mask),
					 HDA_DSP_ADSPCS_CSTALL_MASK(core_mask));

	वापस 0;
पूर्ण
