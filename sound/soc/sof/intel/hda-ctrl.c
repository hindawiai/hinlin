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

#समावेश <linux/module.h>
#समावेश <sound/hdaudio_ext.h>
#समावेश <sound/hda_रेजिस्टर.h>
#समावेश <sound/hda_component.h>
#समावेश "../ops.h"
#समावेश "hda.h"

#अगर IS_ENABLED(CONFIG_SND_SOC_SOF_HDA)
अटल पूर्णांक hda_codec_mask = -1;
module_param_named(codec_mask, hda_codec_mask, पूर्णांक, 0444);
MODULE_PARM_DESC(codec_mask, "SOF HDA codec mask for probing");
#पूर्ण_अगर

/*
 * HDA Operations.
 */

पूर्णांक hda_dsp_ctrl_link_reset(काष्ठा snd_sof_dev *sdev, bool reset)
अणु
	अचिन्हित दीर्घ समयout;
	u32 gctl = 0;
	u32 val;

	/* 0 to enter reset and 1 to निकास reset */
	val = reset ? 0 : SOF_HDA_GCTL_RESET;

	/* enter/निकास HDA controller reset */
	snd_sof_dsp_update_bits(sdev, HDA_DSP_HDA_BAR, SOF_HDA_GCTL,
				SOF_HDA_GCTL_RESET, val);

	/* रुको to enter/निकास reset */
	समयout = jअगरfies + msecs_to_jअगरfies(HDA_DSP_CTRL_RESET_TIMEOUT);
	जबतक (समय_beक्रमe(jअगरfies, समयout)) अणु
		gctl = snd_sof_dsp_पढ़ो(sdev, HDA_DSP_HDA_BAR, SOF_HDA_GCTL);
		अगर ((gctl & SOF_HDA_GCTL_RESET) == val)
			वापस 0;
		usleep_range(500, 1000);
	पूर्ण

	/* enter/निकास reset failed */
	dev_err(sdev->dev, "error: failed to %s HDA controller gctl 0x%x\n",
		reset ? "reset" : "ready", gctl);
	वापस -EIO;
पूर्ण

पूर्णांक hda_dsp_ctrl_get_caps(काष्ठा snd_sof_dev *sdev)
अणु
	काष्ठा hdac_bus *bus = sof_to_bus(sdev);
	u32 cap, offset, feature;
	पूर्णांक count = 0;
	पूर्णांक ret;

	/*
	 * On some devices, one reset cycle is necessary beक्रमe पढ़ोing
	 * capabilities
	 */
	ret = hda_dsp_ctrl_link_reset(sdev, true);
	अगर (ret < 0)
		वापस ret;
	ret = hda_dsp_ctrl_link_reset(sdev, false);
	अगर (ret < 0)
		वापस ret;

	offset = snd_sof_dsp_पढ़ो(sdev, HDA_DSP_HDA_BAR, SOF_HDA_LLCH);

	करो अणु
		dev_dbg(sdev->dev, "checking for capabilities at offset 0x%x\n",
			offset & SOF_HDA_CAP_NEXT_MASK);

		cap = snd_sof_dsp_पढ़ो(sdev, HDA_DSP_HDA_BAR, offset);

		अगर (cap == -1) अणु
			dev_dbg(bus->dev, "Invalid capability reg read\n");
			अवरोध;
		पूर्ण

		feature = (cap & SOF_HDA_CAP_ID_MASK) >> SOF_HDA_CAP_ID_OFF;

		चयन (feature) अणु
		हाल SOF_HDA_PP_CAP_ID:
			dev_dbg(sdev->dev, "found DSP capability at 0x%x\n",
				offset);
			bus->ppcap = bus->remap_addr + offset;
			sdev->bar[HDA_DSP_PP_BAR] = bus->ppcap;
			अवरोध;
		हाल SOF_HDA_SPIB_CAP_ID:
			dev_dbg(sdev->dev, "found SPIB capability at 0x%x\n",
				offset);
			bus->spbcap = bus->remap_addr + offset;
			sdev->bar[HDA_DSP_SPIB_BAR] = bus->spbcap;
			अवरोध;
		हाल SOF_HDA_DRSM_CAP_ID:
			dev_dbg(sdev->dev, "found DRSM capability at 0x%x\n",
				offset);
			bus->drsmcap = bus->remap_addr + offset;
			sdev->bar[HDA_DSP_DRSM_BAR] = bus->drsmcap;
			अवरोध;
		हाल SOF_HDA_GTS_CAP_ID:
			dev_dbg(sdev->dev, "found GTS capability at 0x%x\n",
				offset);
			bus->gtscap = bus->remap_addr + offset;
			अवरोध;
		हाल SOF_HDA_ML_CAP_ID:
			dev_dbg(sdev->dev, "found ML capability at 0x%x\n",
				offset);
			bus->mlcap = bus->remap_addr + offset;
			अवरोध;
		शेष:
			dev_dbg(sdev->dev, "found capability %d at 0x%x\n",
				feature, offset);
			अवरोध;
		पूर्ण

		offset = cap & SOF_HDA_CAP_NEXT_MASK;
	पूर्ण जबतक (count++ <= SOF_HDA_MAX_CAPS && offset);

	वापस 0;
पूर्ण

व्योम hda_dsp_ctrl_ppcap_enable(काष्ठा snd_sof_dev *sdev, bool enable)
अणु
	u32 val = enable ? SOF_HDA_PPCTL_GPROCEN : 0;

	snd_sof_dsp_update_bits(sdev, HDA_DSP_PP_BAR, SOF_HDA_REG_PP_PPCTL,
				SOF_HDA_PPCTL_GPROCEN, val);
पूर्ण

व्योम hda_dsp_ctrl_ppcap_पूर्णांक_enable(काष्ठा snd_sof_dev *sdev, bool enable)
अणु
	u32 val	= enable ? SOF_HDA_PPCTL_PIE : 0;

	snd_sof_dsp_update_bits(sdev, HDA_DSP_PP_BAR, SOF_HDA_REG_PP_PPCTL,
				SOF_HDA_PPCTL_PIE, val);
पूर्ण

व्योम hda_dsp_ctrl_misc_घड़ी_gating(काष्ठा snd_sof_dev *sdev, bool enable)
अणु
	u32 val = enable ? PCI_CGCTL_MISCBDCGE_MASK : 0;

	snd_sof_pci_update_bits(sdev, PCI_CGCTL, PCI_CGCTL_MISCBDCGE_MASK, val);
पूर्ण

/*
 * enable/disable audio dsp घड़ी gating and घातer gating bits.
 * This allows the HW to opportunistically घातer and घड़ी gate
 * the audio dsp when it is idle
 */
पूर्णांक hda_dsp_ctrl_घड़ी_घातer_gating(काष्ठा snd_sof_dev *sdev, bool enable)
अणु
	u32 val;

	/* enable/disable audio dsp घड़ी gating */
	val = enable ? PCI_CGCTL_ADSPDCGE : 0;
	snd_sof_pci_update_bits(sdev, PCI_CGCTL, PCI_CGCTL_ADSPDCGE, val);

	/* enable/disable DMI Link L1 support */
	val = enable ? HDA_VS_INTEL_EM2_L1SEN : 0;
	snd_sof_dsp_update_bits(sdev, HDA_DSP_HDA_BAR, HDA_VS_INTEL_EM2,
				HDA_VS_INTEL_EM2_L1SEN, val);

	/* enable/disable audio dsp घातer gating */
	val = enable ? 0 : PCI_PGCTL_ADSPPGD;
	snd_sof_pci_update_bits(sdev, PCI_PGCTL, PCI_PGCTL_ADSPPGD, val);

	वापस 0;
पूर्ण

पूर्णांक hda_dsp_ctrl_init_chip(काष्ठा snd_sof_dev *sdev, bool full_reset)
अणु
	काष्ठा hdac_bus *bus = sof_to_bus(sdev);
#अगर IS_ENABLED(CONFIG_SND_SOC_SOF_HDA)
	काष्ठा hdac_ext_link *hlink;
#पूर्ण_अगर
	काष्ठा hdac_stream *stream;
	पूर्णांक sd_offset, ret = 0;

	अगर (bus->chip_init)
		वापस 0;

#अगर IS_ENABLED(CONFIG_SND_SOC_SOF_HDA)
	snd_hdac_set_codec_wakeup(bus, true);
#पूर्ण_अगर
	hda_dsp_ctrl_misc_घड़ी_gating(sdev, false);

	अगर (full_reset) अणु
		/* reset HDA controller */
		ret = hda_dsp_ctrl_link_reset(sdev, true);
		अगर (ret < 0) अणु
			dev_err(sdev->dev, "error: failed to reset HDA controller\n");
			जाओ err;
		पूर्ण

		usleep_range(500, 1000);

		/* निकास HDA controller reset */
		ret = hda_dsp_ctrl_link_reset(sdev, false);
		अगर (ret < 0) अणु
			dev_err(sdev->dev, "error: failed to exit HDA controller reset\n");
			जाओ err;
		पूर्ण

		usleep_range(1000, 1200);
	पूर्ण

#अगर IS_ENABLED(CONFIG_SND_SOC_SOF_HDA)
	/* check to see अगर controller is पढ़ोy */
	अगर (!snd_hdac_chip_पढ़ोb(bus, GCTL)) अणु
		dev_dbg(bus->dev, "controller not ready!\n");
		ret = -EBUSY;
		जाओ err;
	पूर्ण

	/* Accept unsolicited responses */
	snd_hdac_chip_updatel(bus, GCTL, AZX_GCTL_UNSOL, AZX_GCTL_UNSOL);

	/* detect codecs */
	अगर (!bus->codec_mask) अणु
		bus->codec_mask = snd_hdac_chip_पढ़ोw(bus, STATESTS);
		dev_dbg(bus->dev, "codec_mask = 0x%lx\n", bus->codec_mask);
	पूर्ण

	अगर (hda_codec_mask != -1) अणु
		bus->codec_mask &= hda_codec_mask;
		dev_dbg(bus->dev, "filtered codec_mask = 0x%lx\n",
			bus->codec_mask);
	पूर्ण
#पूर्ण_अगर

	/* clear stream status */
	list_क्रम_each_entry(stream, &bus->stream_list, list) अणु
		sd_offset = SOF_STREAM_SD_OFFSET(stream);
		snd_sof_dsp_ग_लिखो(sdev, HDA_DSP_HDA_BAR,
				  sd_offset + SOF_HDA_ADSP_REG_CL_SD_STS,
				  SOF_HDA_CL_DMA_SD_INT_MASK);
	पूर्ण

	/* clear WAKESTS */
	snd_sof_dsp_ग_लिखो(sdev, HDA_DSP_HDA_BAR, SOF_HDA_WAKESTS,
			  SOF_HDA_WAKESTS_INT_MASK);

#अगर IS_ENABLED(CONFIG_SND_SOC_SOF_HDA)
	/* clear rirb status */
	snd_hdac_chip_ग_लिखोb(bus, RIRBSTS, RIRB_INT_MASK);
#पूर्ण_अगर

	/* clear पूर्णांकerrupt status रेजिस्टर */
	snd_sof_dsp_ग_लिखो(sdev, HDA_DSP_HDA_BAR, SOF_HDA_INTSTS,
			  SOF_HDA_INT_CTRL_EN | SOF_HDA_INT_ALL_STREAM);

#अगर IS_ENABLED(CONFIG_SND_SOC_SOF_HDA)
	/* initialize the codec command I/O */
	snd_hdac_bus_init_cmd_io(bus);
#पूर्ण_अगर

	/* enable CIE and GIE पूर्णांकerrupts */
	snd_sof_dsp_update_bits(sdev, HDA_DSP_HDA_BAR, SOF_HDA_INTCTL,
				SOF_HDA_INT_CTRL_EN | SOF_HDA_INT_GLOBAL_EN,
				SOF_HDA_INT_CTRL_EN | SOF_HDA_INT_GLOBAL_EN);

	/* program the position buffer */
	अगर (bus->use_posbuf && bus->posbuf.addr) अणु
		snd_sof_dsp_ग_लिखो(sdev, HDA_DSP_HDA_BAR, SOF_HDA_ADSP_DPLBASE,
				  (u32)bus->posbuf.addr);
		snd_sof_dsp_ग_लिखो(sdev, HDA_DSP_HDA_BAR, SOF_HDA_ADSP_DPUBASE,
				  upper_32_bits(bus->posbuf.addr));
	पूर्ण

#अगर IS_ENABLED(CONFIG_SND_SOC_SOF_HDA)
	/* Reset stream-to-link mapping */
	list_क्रम_each_entry(hlink, &bus->hlink_list, list)
		ग_लिखोl(0, hlink->ml_addr + AZX_REG_ML_LOSIDV);
#पूर्ण_अगर

	bus->chip_init = true;

err:
	hda_dsp_ctrl_misc_घड़ी_gating(sdev, true);
#अगर IS_ENABLED(CONFIG_SND_SOC_SOF_HDA)
	snd_hdac_set_codec_wakeup(bus, false);
#पूर्ण_अगर

	वापस ret;
पूर्ण

व्योम hda_dsp_ctrl_stop_chip(काष्ठा snd_sof_dev *sdev)
अणु
	काष्ठा hdac_bus *bus = sof_to_bus(sdev);
	काष्ठा hdac_stream *stream;
	पूर्णांक sd_offset;

	अगर (!bus->chip_init)
		वापस;

	/* disable पूर्णांकerrupts in stream descriptor */
	list_क्रम_each_entry(stream, &bus->stream_list, list) अणु
		sd_offset = SOF_STREAM_SD_OFFSET(stream);
		snd_sof_dsp_update_bits(sdev, HDA_DSP_HDA_BAR,
					sd_offset +
					SOF_HDA_ADSP_REG_CL_SD_CTL,
					SOF_HDA_CL_DMA_SD_INT_MASK,
					0);
	पूर्ण

	/* disable SIE क्रम all streams */
	snd_sof_dsp_update_bits(sdev, HDA_DSP_HDA_BAR, SOF_HDA_INTCTL,
				SOF_HDA_INT_ALL_STREAM,	0);

	/* disable controller CIE and GIE */
	snd_sof_dsp_update_bits(sdev, HDA_DSP_HDA_BAR, SOF_HDA_INTCTL,
				SOF_HDA_INT_CTRL_EN | SOF_HDA_INT_GLOBAL_EN,
				0);

	/* clear stream status */
	list_क्रम_each_entry(stream, &bus->stream_list, list) अणु
		sd_offset = SOF_STREAM_SD_OFFSET(stream);
		snd_sof_dsp_ग_लिखो(sdev, HDA_DSP_HDA_BAR,
				  sd_offset + SOF_HDA_ADSP_REG_CL_SD_STS,
				  SOF_HDA_CL_DMA_SD_INT_MASK);
	पूर्ण

	/* clear WAKESTS */
	snd_sof_dsp_ग_लिखो(sdev, HDA_DSP_HDA_BAR, SOF_HDA_WAKESTS,
			  SOF_HDA_WAKESTS_INT_MASK);

#अगर IS_ENABLED(CONFIG_SND_SOC_SOF_HDA)
	/* clear rirb status */
	snd_hdac_chip_ग_लिखोb(bus, RIRBSTS, RIRB_INT_MASK);
#पूर्ण_अगर

	/* clear पूर्णांकerrupt status रेजिस्टर */
	snd_sof_dsp_ग_लिखो(sdev, HDA_DSP_HDA_BAR, SOF_HDA_INTSTS,
			  SOF_HDA_INT_CTRL_EN | SOF_HDA_INT_ALL_STREAM);

#अगर IS_ENABLED(CONFIG_SND_SOC_SOF_HDA)
	/* disable CORB/RIRB */
	snd_hdac_bus_stop_cmd_io(bus);
#पूर्ण_अगर
	/* disable position buffer */
	अगर (bus->posbuf.addr) अणु
		snd_sof_dsp_ग_लिखो(sdev, HDA_DSP_HDA_BAR,
				  SOF_HDA_ADSP_DPLBASE, 0);
		snd_sof_dsp_ग_लिखो(sdev, HDA_DSP_HDA_BAR,
				  SOF_HDA_ADSP_DPUBASE, 0);
	पूर्ण

	bus->chip_init = false;
पूर्ण
