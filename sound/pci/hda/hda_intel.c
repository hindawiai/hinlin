<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *
 *  hda_पूर्णांकel.c - Implementation of primary alsa driver code base
 *                क्रम Intel HD Audio.
 *
 *  Copyright(c) 2004 Intel Corporation. All rights reserved.
 *
 *  Copyright (c) 2004 Takashi Iwai <tiwai@suse.de>
 *                     PeiSen Hou <pshou@realtek.com.tw>
 *
 *  CONTACTS:
 *
 *  Matt Jared		matt.jared@पूर्णांकel.com
 *  Andy Kopp		andy.kopp@पूर्णांकel.com
 *  Dan Kogan		dan.d.kogan@पूर्णांकel.com
 *
 *  CHANGES:
 *
 *  2004.12.01	Major reग_लिखो by tiwai, merged the work of pshou
 */

#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/pci.h>
#समावेश <linux/mutex.h>
#समावेश <linux/पन.स>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/घड़ीsource.h>
#समावेश <linux/समय.स>
#समावेश <linux/completion.h>
#समावेश <linux/acpi.h>
#समावेश <linux/pgtable.h>

#अगर_घोषित CONFIG_X86
/* क्रम snoop control */
#समावेश <यंत्र/set_memory.h>
#समावेश <यंत्र/cpufeature.h>
#पूर्ण_अगर
#समावेश <sound/core.h>
#समावेश <sound/initval.h>
#समावेश <sound/hdaudपन.स>
#समावेश <sound/hda_i915.h>
#समावेश <sound/पूर्णांकel-dsp-config.h>
#समावेश <linux/vgaarb.h>
#समावेश <linux/vga_चयनeroo.h>
#समावेश <linux/firmware.h>
#समावेश <sound/hda_codec.h>
#समावेश "hda_controller.h"
#समावेश "hda_intel.h"

#घोषणा CREATE_TRACE_POINTS
#समावेश "hda_intel_trace.h"

/* position fix mode */
क्रमागत अणु
	POS_FIX_AUTO,
	POS_FIX_LPIB,
	POS_FIX_POSBUF,
	POS_FIX_VIACOMBO,
	POS_FIX_COMBO,
	POS_FIX_SKL,
	POS_FIX_FIFO,
पूर्ण;

/* Defines क्रम ATI HD Audio support in SB450 south bridge */
#घोषणा ATI_SB450_HDAUDIO_MISC_CNTR2_ADDR   0x42
#घोषणा ATI_SB450_HDAUDIO_ENABLE_SNOOP      0x02

/* Defines क्रम Nvidia HDA support */
#घोषणा NVIDIA_HDA_TRANSREG_ADDR      0x4e
#घोषणा NVIDIA_HDA_ENABLE_COHBITS     0x0f
#घोषणा NVIDIA_HDA_ISTRM_COH          0x4d
#घोषणा NVIDIA_HDA_OSTRM_COH          0x4c
#घोषणा NVIDIA_HDA_ENABLE_COHBIT      0x01

/* Defines क्रम Intel SCH HDA snoop control */
#घोषणा INTEL_HDA_CGCTL	 0x48
#घोषणा INTEL_HDA_CGCTL_MISCBDCGE        (0x1 << 6)
#घोषणा INTEL_SCH_HDA_DEVC      0x78
#घोषणा INTEL_SCH_HDA_DEVC_NOSNOOP       (0x1<<11)

/* Define VIA HD Audio Device ID*/
#घोषणा VIA_HDAC_DEVICE_ID		0x3288

/* max number of SDs */
/* ICH, ATI and VIA have 4 playback and 4 capture */
#घोषणा ICH6_NUM_CAPTURE	4
#घोषणा ICH6_NUM_PLAYBACK	4

/* ULI has 6 playback and 5 capture */
#घोषणा ULI_NUM_CAPTURE		5
#घोषणा ULI_NUM_PLAYBACK	6

/* ATI HDMI may have up to 8 playbacks and 0 capture */
#घोषणा ATIHDMI_NUM_CAPTURE	0
#घोषणा ATIHDMI_NUM_PLAYBACK	8

/* TERA has 4 playback and 3 capture */
#घोषणा TERA_NUM_CAPTURE	3
#घोषणा TERA_NUM_PLAYBACK	4


अटल पूर्णांक index[SNDRV_CARDS] = SNDRV_DEFAULT_IDX;
अटल अक्षर *id[SNDRV_CARDS] = SNDRV_DEFAULT_STR;
अटल bool enable[SNDRV_CARDS] = SNDRV_DEFAULT_ENABLE_PNP;
अटल अक्षर *model[SNDRV_CARDS];
अटल पूर्णांक position_fix[SNDRV_CARDS] = अणु[0 ... (SNDRV_CARDS-1)] = -1पूर्ण;
अटल पूर्णांक bdl_pos_adj[SNDRV_CARDS] = अणु[0 ... (SNDRV_CARDS-1)] = -1पूर्ण;
अटल पूर्णांक probe_mask[SNDRV_CARDS] = अणु[0 ... (SNDRV_CARDS-1)] = -1पूर्ण;
अटल पूर्णांक probe_only[SNDRV_CARDS];
अटल पूर्णांक jackpoll_ms[SNDRV_CARDS];
अटल पूर्णांक single_cmd = -1;
अटल पूर्णांक enable_msi = -1;
#अगर_घोषित CONFIG_SND_HDA_PATCH_LOADER
अटल अक्षर *patch[SNDRV_CARDS];
#पूर्ण_अगर
#अगर_घोषित CONFIG_SND_HDA_INPUT_BEEP
अटल bool beep_mode[SNDRV_CARDS] = अणु[0 ... (SNDRV_CARDS-1)] =
					CONFIG_SND_HDA_INPUT_BEEP_MODEपूर्ण;
#पूर्ण_अगर
अटल bool dmic_detect = 1;

module_param_array(index, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(index, "Index value for Intel HD audio interface.");
module_param_array(id, अक्षरp, शून्य, 0444);
MODULE_PARM_DESC(id, "ID string for Intel HD audio interface.");
module_param_array(enable, bool, शून्य, 0444);
MODULE_PARM_DESC(enable, "Enable Intel HD audio interface.");
module_param_array(model, अक्षरp, शून्य, 0444);
MODULE_PARM_DESC(model, "Use the given board model.");
module_param_array(position_fix, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(position_fix, "DMA pointer read method."
		 "(-1 = system default, 0 = auto, 1 = LPIB, 2 = POSBUF, 3 = VIACOMBO, 4 = COMBO, 5 = SKL+, 6 = FIFO).");
module_param_array(bdl_pos_adj, पूर्णांक, शून्य, 0644);
MODULE_PARM_DESC(bdl_pos_adj, "BDL position adjustment offset.");
module_param_array(probe_mask, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(probe_mask, "Bitmask to probe codecs (default = -1).");
module_param_array(probe_only, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(probe_only, "Only probing and no codec initialization.");
module_param_array(jackpoll_ms, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(jackpoll_ms, "Ms between polling for jack events (default = 0, using unsol events only)");
module_param(single_cmd, bपूर्णांक, 0444);
MODULE_PARM_DESC(single_cmd, "Use single command to communicate with codecs "
		 "(for debugging only).");
module_param(enable_msi, bपूर्णांक, 0444);
MODULE_PARM_DESC(enable_msi, "Enable Message Signaled Interrupt (MSI)");
#अगर_घोषित CONFIG_SND_HDA_PATCH_LOADER
module_param_array(patch, अक्षरp, शून्य, 0444);
MODULE_PARM_DESC(patch, "Patch file for Intel HD audio interface.");
#पूर्ण_अगर
#अगर_घोषित CONFIG_SND_HDA_INPUT_BEEP
module_param_array(beep_mode, bool, शून्य, 0444);
MODULE_PARM_DESC(beep_mode, "Select HDA Beep registration mode "
			    "(0=off, 1=on) (default=1).");
#पूर्ण_अगर
module_param(dmic_detect, bool, 0444);
MODULE_PARM_DESC(dmic_detect, "Allow DSP driver selection (bypass this driver) "
			     "(0=off, 1=on) (default=1); "
		 "deprecated, use snd-intel-dspcfg.dsp_driver option instead");

#अगर_घोषित CONFIG_PM
अटल पूर्णांक param_set_xपूर्णांक(स्थिर अक्षर *val, स्थिर काष्ठा kernel_param *kp);
अटल स्थिर काष्ठा kernel_param_ops param_ops_xपूर्णांक = अणु
	.set = param_set_xपूर्णांक,
	.get = param_get_पूर्णांक,
पूर्ण;
#घोषणा param_check_xपूर्णांक param_check_पूर्णांक

अटल पूर्णांक घातer_save = CONFIG_SND_HDA_POWER_SAVE_DEFAULT;
module_param(घातer_save, xपूर्णांक, 0644);
MODULE_PARM_DESC(घातer_save, "Automatic power-saving timeout "
		 "(in second, 0 = disable).");

अटल bool pm_blacklist = true;
module_param(pm_blacklist, bool, 0644);
MODULE_PARM_DESC(pm_blacklist, "Enable power-management denylist");

/* reset the HD-audio controller in घातer save mode.
 * this may give more घातer-saving, but will take दीर्घer समय to
 * wake up.
 */
अटल bool घातer_save_controller = 1;
module_param(घातer_save_controller, bool, 0644);
MODULE_PARM_DESC(घातer_save_controller, "Reset controller in power save mode.");
#अन्यथा
#घोषणा घातer_save	0
#पूर्ण_अगर /* CONFIG_PM */

अटल पूर्णांक align_buffer_size = -1;
module_param(align_buffer_size, bपूर्णांक, 0644);
MODULE_PARM_DESC(align_buffer_size,
		"Force buffer and period sizes to be multiple of 128 bytes.");

#अगर_घोषित CONFIG_X86
अटल पूर्णांक hda_snoop = -1;
module_param_named(snoop, hda_snoop, bपूर्णांक, 0444);
MODULE_PARM_DESC(snoop, "Enable/disable snooping");
#अन्यथा
#घोषणा hda_snoop		true
#पूर्ण_अगर


MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Intel HDA driver");

#अगर defined(CONFIG_PM) && defined(CONFIG_VGA_SWITCHEROO)
#अगर IS_ENABLED(CONFIG_SND_HDA_CODEC_HDMI)
#घोषणा SUPPORT_VGA_SWITCHEROO
#पूर्ण_अगर
#पूर्ण_अगर


/*
 */

/* driver types */
क्रमागत अणु
	AZX_DRIVER_ICH,
	AZX_DRIVER_PCH,
	AZX_DRIVER_SCH,
	AZX_DRIVER_SKL,
	AZX_DRIVER_HDMI,
	AZX_DRIVER_ATI,
	AZX_DRIVER_ATIHDMI,
	AZX_DRIVER_ATIHDMI_NS,
	AZX_DRIVER_VIA,
	AZX_DRIVER_SIS,
	AZX_DRIVER_ULI,
	AZX_DRIVER_NVIDIA,
	AZX_DRIVER_TERA,
	AZX_DRIVER_CTX,
	AZX_DRIVER_CTHDA,
	AZX_DRIVER_CMEDIA,
	AZX_DRIVER_ZHAOXIN,
	AZX_DRIVER_GENERIC,
	AZX_NUM_DRIVERS, /* keep this as last entry */
पूर्ण;

#घोषणा azx_get_snoop_type(chip) \
	(((chip)->driver_caps & AZX_DCAPS_SNOOP_MASK) >> 10)
#घोषणा AZX_DCAPS_SNOOP_TYPE(type) ((AZX_SNOOP_TYPE_ ## type) << 10)

/* quirks क्रम old Intel chipsets */
#घोषणा AZX_DCAPS_INTEL_ICH \
	(AZX_DCAPS_OLD_SSYNC | AZX_DCAPS_NO_ALIGN_बफ_मानE)

/* quirks क्रम Intel PCH */
#घोषणा AZX_DCAPS_INTEL_PCH_BASE \
	(AZX_DCAPS_NO_ALIGN_बफ_मानE | AZX_DCAPS_COUNT_LPIB_DELAY |\
	 AZX_DCAPS_SNOOP_TYPE(SCH))

/* PCH up to IVB; no runसमय PM; bind with i915 gfx */
#घोषणा AZX_DCAPS_INTEL_PCH_NOPM \
	(AZX_DCAPS_INTEL_PCH_BASE | AZX_DCAPS_I915_COMPONENT)

/* PCH क्रम HSW/BDW; with runसमय PM */
/* no i915 binding क्रम this as HSW/BDW has another controller क्रम HDMI */
#घोषणा AZX_DCAPS_INTEL_PCH \
	(AZX_DCAPS_INTEL_PCH_BASE | AZX_DCAPS_PM_RUNTIME)

/* HSW HDMI */
#घोषणा AZX_DCAPS_INTEL_HASWELL \
	(/*AZX_DCAPS_ALIGN_बफ_मानE |*/ AZX_DCAPS_COUNT_LPIB_DELAY |\
	 AZX_DCAPS_PM_RUNTIME | AZX_DCAPS_I915_COMPONENT |\
	 AZX_DCAPS_SNOOP_TYPE(SCH))

/* Broadwell HDMI can't use position buffer reliably, क्रमce to use LPIB */
#घोषणा AZX_DCAPS_INTEL_BROADWELL \
	(/*AZX_DCAPS_ALIGN_बफ_मानE |*/ AZX_DCAPS_POSFIX_LPIB |\
	 AZX_DCAPS_PM_RUNTIME | AZX_DCAPS_I915_COMPONENT |\
	 AZX_DCAPS_SNOOP_TYPE(SCH))

#घोषणा AZX_DCAPS_INTEL_BAYTRAIL \
	(AZX_DCAPS_INTEL_PCH_BASE | AZX_DCAPS_I915_COMPONENT)

#घोषणा AZX_DCAPS_INTEL_BRASWELL \
	(AZX_DCAPS_INTEL_PCH_BASE | AZX_DCAPS_PM_RUNTIME |\
	 AZX_DCAPS_I915_COMPONENT)

#घोषणा AZX_DCAPS_INTEL_SKYLAKE \
	(AZX_DCAPS_INTEL_PCH_BASE | AZX_DCAPS_PM_RUNTIME |\
	 AZX_DCAPS_SEPARATE_STREAM_TAG | AZX_DCAPS_I915_COMPONENT)

#घोषणा AZX_DCAPS_INTEL_BROXTON		AZX_DCAPS_INTEL_SKYLAKE

/* quirks क्रम ATI SB / AMD Hudson */
#घोषणा AZX_DCAPS_PRESET_ATI_SB \
	(AZX_DCAPS_NO_TCSEL | AZX_DCAPS_POSFIX_LPIB |\
	 AZX_DCAPS_SNOOP_TYPE(ATI))

/* quirks क्रम ATI/AMD HDMI */
#घोषणा AZX_DCAPS_PRESET_ATI_HDMI \
	(AZX_DCAPS_NO_TCSEL | AZX_DCAPS_POSFIX_LPIB|\
	 AZX_DCAPS_NO_MSI64)

/* quirks क्रम ATI HDMI with snoop off */
#घोषणा AZX_DCAPS_PRESET_ATI_HDMI_NS \
	(AZX_DCAPS_PRESET_ATI_HDMI | AZX_DCAPS_SNOOP_OFF)

/* quirks क्रम AMD SB */
#घोषणा AZX_DCAPS_PRESET_AMD_SB \
	(AZX_DCAPS_NO_TCSEL | AZX_DCAPS_AMD_WORKAROUND |\
	 AZX_DCAPS_SNOOP_TYPE(ATI) | AZX_DCAPS_PM_RUNTIME)

/* quirks क्रम Nvidia */
#घोषणा AZX_DCAPS_PRESET_NVIDIA \
	(AZX_DCAPS_NO_MSI | AZX_DCAPS_CORBRP_SELF_CLEAR |\
	 AZX_DCAPS_SNOOP_TYPE(NVIDIA))

#घोषणा AZX_DCAPS_PRESET_CTHDA \
	(AZX_DCAPS_NO_MSI | AZX_DCAPS_POSFIX_LPIB |\
	 AZX_DCAPS_NO_64BIT |\
	 AZX_DCAPS_4K_BDLE_BOUNDARY | AZX_DCAPS_SNOOP_OFF)

/*
 * vga_चयनeroo support
 */
#अगर_घोषित SUPPORT_VGA_SWITCHEROO
#घोषणा use_vga_चयनeroo(chip)	((chip)->use_vga_चयनeroo)
#घोषणा needs_eld_notअगरy_link(chip)	((chip)->bus.keep_घातer)
#अन्यथा
#घोषणा use_vga_चयनeroo(chip)	0
#घोषणा needs_eld_notअगरy_link(chip)	false
#पूर्ण_अगर

#घोषणा CONTROLLER_IN_GPU(pci) (((pci)->device == 0x0a0c) || \
					((pci)->device == 0x0c0c) || \
					((pci)->device == 0x0d0c) || \
					((pci)->device == 0x160c) || \
					((pci)->device == 0x490d))

#घोषणा IS_BXT(pci) ((pci)->venकरोr == 0x8086 && (pci)->device == 0x5a98)

अटल स्थिर अक्षर * स्थिर driver_लघु_names[] = अणु
	[AZX_DRIVER_ICH] = "HDA Intel",
	[AZX_DRIVER_PCH] = "HDA Intel PCH",
	[AZX_DRIVER_SCH] = "HDA Intel MID",
	[AZX_DRIVER_SKL] = "HDA Intel PCH", /* kept old name क्रम compatibility */
	[AZX_DRIVER_HDMI] = "HDA Intel HDMI",
	[AZX_DRIVER_ATI] = "HDA ATI SB",
	[AZX_DRIVER_ATIHDMI] = "HDA ATI HDMI",
	[AZX_DRIVER_ATIHDMI_NS] = "HDA ATI HDMI",
	[AZX_DRIVER_VIA] = "HDA VIA VT82xx",
	[AZX_DRIVER_SIS] = "HDA SIS966",
	[AZX_DRIVER_ULI] = "HDA ULI M5461",
	[AZX_DRIVER_NVIDIA] = "HDA NVidia",
	[AZX_DRIVER_TERA] = "HDA Teradici", 
	[AZX_DRIVER_CTX] = "HDA Creative", 
	[AZX_DRIVER_CTHDA] = "HDA Creative",
	[AZX_DRIVER_CMEDIA] = "HDA C-Media",
	[AZX_DRIVER_ZHAOXIN] = "HDA Zhaoxin",
	[AZX_DRIVER_GENERIC] = "HD-Audio Generic",
पूर्ण;

अटल पूर्णांक azx_acquire_irq(काष्ठा azx *chip, पूर्णांक करो_disconnect);
अटल व्योम set_शेष_घातer_save(काष्ठा azx *chip);

/*
 * initialize the PCI रेजिस्टरs
 */
/* update bits in a PCI रेजिस्टर byte */
अटल व्योम update_pci_byte(काष्ठा pci_dev *pci, अचिन्हित पूर्णांक reg,
			    अचिन्हित अक्षर mask, अचिन्हित अक्षर val)
अणु
	अचिन्हित अक्षर data;

	pci_पढ़ो_config_byte(pci, reg, &data);
	data &= ~mask;
	data |= (val & mask);
	pci_ग_लिखो_config_byte(pci, reg, data);
पूर्ण

अटल व्योम azx_init_pci(काष्ठा azx *chip)
अणु
	पूर्णांक snoop_type = azx_get_snoop_type(chip);

	/* Clear bits 0-2 of PCI रेजिस्टर TCSEL (at offset 0x44)
	 * TCSEL == Traffic Class Select Register, which sets PCI express QOS
	 * Ensuring these bits are 0 clears playback अटल on some HD Audio
	 * codecs.
	 * The PCI रेजिस्टर TCSEL is defined in the Intel manuals.
	 */
	अगर (!(chip->driver_caps & AZX_DCAPS_NO_TCSEL)) अणु
		dev_dbg(chip->card->dev, "Clearing TCSEL\n");
		update_pci_byte(chip->pci, AZX_PCIREG_TCSEL, 0x07, 0);
	पूर्ण

	/* For ATI SB450/600/700/800/900 and AMD Hudson azalia HD audio,
	 * we need to enable snoop.
	 */
	अगर (snoop_type == AZX_SNOOP_TYPE_ATI) अणु
		dev_dbg(chip->card->dev, "Setting ATI snoop: %d\n",
			azx_snoop(chip));
		update_pci_byte(chip->pci,
				ATI_SB450_HDAUDIO_MISC_CNTR2_ADDR, 0x07,
				azx_snoop(chip) ? ATI_SB450_HDAUDIO_ENABLE_SNOOP : 0);
	पूर्ण

	/* For NVIDIA HDA, enable snoop */
	अगर (snoop_type == AZX_SNOOP_TYPE_NVIDIA) अणु
		dev_dbg(chip->card->dev, "Setting Nvidia snoop: %d\n",
			azx_snoop(chip));
		update_pci_byte(chip->pci,
				NVIDIA_HDA_TRANSREG_ADDR,
				0x0f, NVIDIA_HDA_ENABLE_COHBITS);
		update_pci_byte(chip->pci,
				NVIDIA_HDA_ISTRM_COH,
				0x01, NVIDIA_HDA_ENABLE_COHBIT);
		update_pci_byte(chip->pci,
				NVIDIA_HDA_OSTRM_COH,
				0x01, NVIDIA_HDA_ENABLE_COHBIT);
	पूर्ण

	/* Enable SCH/PCH snoop अगर needed */
	अगर (snoop_type == AZX_SNOOP_TYPE_SCH) अणु
		अचिन्हित लघु snoop;
		pci_पढ़ो_config_word(chip->pci, INTEL_SCH_HDA_DEVC, &snoop);
		अगर ((!azx_snoop(chip) && !(snoop & INTEL_SCH_HDA_DEVC_NOSNOOP)) ||
		    (azx_snoop(chip) && (snoop & INTEL_SCH_HDA_DEVC_NOSNOOP))) अणु
			snoop &= ~INTEL_SCH_HDA_DEVC_NOSNOOP;
			अगर (!azx_snoop(chip))
				snoop |= INTEL_SCH_HDA_DEVC_NOSNOOP;
			pci_ग_लिखो_config_word(chip->pci, INTEL_SCH_HDA_DEVC, snoop);
			pci_पढ़ो_config_word(chip->pci,
				INTEL_SCH_HDA_DEVC, &snoop);
		पूर्ण
		dev_dbg(chip->card->dev, "SCH snoop: %s\n",
			(snoop & INTEL_SCH_HDA_DEVC_NOSNOOP) ?
			"Disabled" : "Enabled");
        पूर्ण
पूर्ण

/*
 * In BXT-P A0, HD-Audio DMA requests is later than expected,
 * and makes an audio stream sensitive to प्रणाली latencies when
 * 24/32 bits are playing.
 * Adjusting threshold of DMA fअगरo to क्रमce the DMA request
 * sooner to improve latency tolerance at the expense of घातer.
 */
अटल व्योम bxt_reduce_dma_latency(काष्ठा azx *chip)
अणु
	u32 val;

	val = azx_पढ़ोl(chip, VS_EM4L);
	val &= (0x3 << 20);
	azx_ग_लिखोl(chip, VS_EM4L, val);
पूर्ण

/*
 * ML_LCAP bits:
 *  bit 0: 6 MHz Supported
 *  bit 1: 12 MHz Supported
 *  bit 2: 24 MHz Supported
 *  bit 3: 48 MHz Supported
 *  bit 4: 96 MHz Supported
 *  bit 5: 192 MHz Supported
 */
अटल पूर्णांक पूर्णांकel_get_lctl_scf(काष्ठा azx *chip)
अणु
	काष्ठा hdac_bus *bus = azx_bus(chip);
	अटल स्थिर पूर्णांक preferred_bits[] = अणु 2, 3, 1, 4, 5 पूर्ण;
	u32 val, t;
	पूर्णांक i;

	val = पढ़ोl(bus->mlcap + AZX_ML_BASE + AZX_REG_ML_LCAP);

	क्रम (i = 0; i < ARRAY_SIZE(preferred_bits); i++) अणु
		t = preferred_bits[i];
		अगर (val & (1 << t))
			वापस t;
	पूर्ण

	dev_warn(chip->card->dev, "set audio clock frequency to 6MHz");
	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_ml_lctl_set_घातer(काष्ठा azx *chip, पूर्णांक state)
अणु
	काष्ठा hdac_bus *bus = azx_bus(chip);
	u32 val;
	पूर्णांक समयout;

	/*
	 * the codecs are sharing the first link setting by शेष
	 * If other links are enabled क्रम stream, they need similar fix
	 */
	val = पढ़ोl(bus->mlcap + AZX_ML_BASE + AZX_REG_ML_LCTL);
	val &= ~AZX_MLCTL_SPA;
	val |= state << AZX_MLCTL_SPA_SHIFT;
	ग_लिखोl(val, bus->mlcap + AZX_ML_BASE + AZX_REG_ML_LCTL);
	/* रुको क्रम CPA */
	समयout = 50;
	जबतक (समयout) अणु
		अगर (((पढ़ोl(bus->mlcap + AZX_ML_BASE + AZX_REG_ML_LCTL)) &
		    AZX_MLCTL_CPA) == (state << AZX_MLCTL_CPA_SHIFT))
			वापस 0;
		समयout--;
		udelay(10);
	पूर्ण

	वापस -1;
पूर्ण

अटल व्योम पूर्णांकel_init_lctl(काष्ठा azx *chip)
अणु
	काष्ठा hdac_bus *bus = azx_bus(chip);
	u32 val;
	पूर्णांक ret;

	/* 0. check lctl रेजिस्टर value is correct or not */
	val = पढ़ोl(bus->mlcap + AZX_ML_BASE + AZX_REG_ML_LCTL);
	/* अगर SCF is alपढ़ोy set, let's use it */
	अगर ((val & ML_LCTL_SCF_MASK) != 0)
		वापस;

	/*
	 * Beक्रमe operating on SPA, CPA must match SPA.
	 * Any deviation may result in undefined behavior.
	 */
	अगर (((val & AZX_MLCTL_SPA) >> AZX_MLCTL_SPA_SHIFT) !=
		((val & AZX_MLCTL_CPA) >> AZX_MLCTL_CPA_SHIFT))
		वापस;

	/* 1. turn link करोwn: set SPA to 0 and रुको CPA to 0 */
	ret = पूर्णांकel_ml_lctl_set_घातer(chip, 0);
	udelay(100);
	अगर (ret)
		जाओ set_spa;

	/* 2. update SCF to select a properly audio घड़ी*/
	val &= ~ML_LCTL_SCF_MASK;
	val |= पूर्णांकel_get_lctl_scf(chip);
	ग_लिखोl(val, bus->mlcap + AZX_ML_BASE + AZX_REG_ML_LCTL);

set_spa:
	/* 4. turn link up: set SPA to 1 and रुको CPA to 1 */
	पूर्णांकel_ml_lctl_set_घातer(chip, 1);
	udelay(100);
पूर्ण

अटल व्योम hda_पूर्णांकel_init_chip(काष्ठा azx *chip, bool full_reset)
अणु
	काष्ठा hdac_bus *bus = azx_bus(chip);
	काष्ठा pci_dev *pci = chip->pci;
	u32 val;

	snd_hdac_set_codec_wakeup(bus, true);
	अगर (chip->driver_type == AZX_DRIVER_SKL) अणु
		pci_पढ़ो_config_dword(pci, INTEL_HDA_CGCTL, &val);
		val = val & ~INTEL_HDA_CGCTL_MISCBDCGE;
		pci_ग_लिखो_config_dword(pci, INTEL_HDA_CGCTL, val);
	पूर्ण
	azx_init_chip(chip, full_reset);
	अगर (chip->driver_type == AZX_DRIVER_SKL) अणु
		pci_पढ़ो_config_dword(pci, INTEL_HDA_CGCTL, &val);
		val = val | INTEL_HDA_CGCTL_MISCBDCGE;
		pci_ग_लिखो_config_dword(pci, INTEL_HDA_CGCTL, val);
	पूर्ण

	snd_hdac_set_codec_wakeup(bus, false);

	/* reduce dma latency to aव्योम noise */
	अगर (IS_BXT(pci))
		bxt_reduce_dma_latency(chip);

	अगर (bus->mlcap != शून्य)
		पूर्णांकel_init_lctl(chip);
पूर्ण

/* calculate runसमय delay from LPIB */
अटल पूर्णांक azx_get_delay_from_lpib(काष्ठा azx *chip, काष्ठा azx_dev *azx_dev,
				   अचिन्हित पूर्णांक pos)
अणु
	काष्ठा snd_pcm_substream *substream = azx_dev->core.substream;
	पूर्णांक stream = substream->stream;
	अचिन्हित पूर्णांक lpib_pos = azx_get_pos_lpib(chip, azx_dev);
	पूर्णांक delay;

	अगर (stream == SNDRV_PCM_STREAM_PLAYBACK)
		delay = pos - lpib_pos;
	अन्यथा
		delay = lpib_pos - pos;
	अगर (delay < 0) अणु
		अगर (delay >= azx_dev->core.delay_negative_threshold)
			delay = 0;
		अन्यथा
			delay += azx_dev->core.bufsize;
	पूर्ण

	अगर (delay >= azx_dev->core.period_bytes) अणु
		dev_info(chip->card->dev,
			 "Unstable LPIB (%d >= %d); disabling LPIB delay counting\n",
			 delay, azx_dev->core.period_bytes);
		delay = 0;
		chip->driver_caps &= ~AZX_DCAPS_COUNT_LPIB_DELAY;
		chip->get_delay[stream] = शून्य;
	पूर्ण

	वापस bytes_to_frames(substream->runसमय, delay);
पूर्ण

अटल पूर्णांक azx_position_ok(काष्ठा azx *chip, काष्ठा azx_dev *azx_dev);

/* called from IRQ */
अटल पूर्णांक azx_position_check(काष्ठा azx *chip, काष्ठा azx_dev *azx_dev)
अणु
	काष्ठा hda_पूर्णांकel *hda = container_of(chip, काष्ठा hda_पूर्णांकel, chip);
	पूर्णांक ok;

	ok = azx_position_ok(chip, azx_dev);
	अगर (ok == 1) अणु
		azx_dev->irq_pending = 0;
		वापस ok;
	पूर्ण अन्यथा अगर (ok == 0) अणु
		/* bogus IRQ, process it later */
		azx_dev->irq_pending = 1;
		schedule_work(&hda->irq_pending_work);
	पूर्ण
	वापस 0;
पूर्ण

#घोषणा display_घातer(chip, enable) \
	snd_hdac_display_घातer(azx_bus(chip), HDA_CODEC_IDX_CONTROLLER, enable)

/*
 * Check whether the current DMA position is acceptable क्रम updating
 * periods.  Returns non-zero अगर it's OK.
 *
 * Many HD-audio controllers appear pretty inaccurate about
 * the update-IRQ timing.  The IRQ is issued beक्रमe actually the
 * data is processed.  So, we need to process it afterwords in a
 * workqueue.
 */
अटल पूर्णांक azx_position_ok(काष्ठा azx *chip, काष्ठा azx_dev *azx_dev)
अणु
	काष्ठा snd_pcm_substream *substream = azx_dev->core.substream;
	पूर्णांक stream = substream->stream;
	u32 wallclk;
	अचिन्हित पूर्णांक pos;

	wallclk = azx_पढ़ोl(chip, WALLCLK) - azx_dev->core.start_wallclk;
	अगर (wallclk < (azx_dev->core.period_wallclk * 2) / 3)
		वापस -1;	/* bogus (too early) पूर्णांकerrupt */

	अगर (chip->get_position[stream])
		pos = chip->get_position[stream](chip, azx_dev);
	अन्यथा अणु /* use the position buffer as शेष */
		pos = azx_get_pos_posbuf(chip, azx_dev);
		अगर (!pos || pos == (u32)-1) अणु
			dev_info(chip->card->dev,
				 "Invalid position buffer, using LPIB read method instead.\n");
			chip->get_position[stream] = azx_get_pos_lpib;
			अगर (chip->get_position[0] == azx_get_pos_lpib &&
			    chip->get_position[1] == azx_get_pos_lpib)
				azx_bus(chip)->use_posbuf = false;
			pos = azx_get_pos_lpib(chip, azx_dev);
			chip->get_delay[stream] = शून्य;
		पूर्ण अन्यथा अणु
			chip->get_position[stream] = azx_get_pos_posbuf;
			अगर (chip->driver_caps & AZX_DCAPS_COUNT_LPIB_DELAY)
				chip->get_delay[stream] = azx_get_delay_from_lpib;
		पूर्ण
	पूर्ण

	अगर (pos >= azx_dev->core.bufsize)
		pos = 0;

	अगर (WARN_ONCE(!azx_dev->core.period_bytes,
		      "hda-intel: zero azx_dev->period_bytes"))
		वापस -1; /* this shouldn't happen! */
	अगर (wallclk < (azx_dev->core.period_wallclk * 5) / 4 &&
	    pos % azx_dev->core.period_bytes > azx_dev->core.period_bytes / 2)
		/* NG - it's below the first next period boundary */
		वापस chip->bdl_pos_adj ? 0 : -1;
	azx_dev->core.start_wallclk += wallclk;
	वापस 1; /* OK, it's fine */
पूर्ण

/*
 * The work क्रम pending PCM period updates.
 */
अटल व्योम azx_irq_pending_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा hda_पूर्णांकel *hda = container_of(work, काष्ठा hda_पूर्णांकel, irq_pending_work);
	काष्ठा azx *chip = &hda->chip;
	काष्ठा hdac_bus *bus = azx_bus(chip);
	काष्ठा hdac_stream *s;
	पूर्णांक pending, ok;

	अगर (!hda->irq_pending_warned) अणु
		dev_info(chip->card->dev,
			 "IRQ timing workaround is activated for card #%d. Suggest a bigger bdl_pos_adj.\n",
			 chip->card->number);
		hda->irq_pending_warned = 1;
	पूर्ण

	क्रम (;;) अणु
		pending = 0;
		spin_lock_irq(&bus->reg_lock);
		list_क्रम_each_entry(s, &bus->stream_list, list) अणु
			काष्ठा azx_dev *azx_dev = stream_to_azx_dev(s);
			अगर (!azx_dev->irq_pending ||
			    !s->substream ||
			    !s->running)
				जारी;
			ok = azx_position_ok(chip, azx_dev);
			अगर (ok > 0) अणु
				azx_dev->irq_pending = 0;
				spin_unlock(&bus->reg_lock);
				snd_pcm_period_elapsed(s->substream);
				spin_lock(&bus->reg_lock);
			पूर्ण अन्यथा अगर (ok < 0) अणु
				pending = 0;	/* too early */
			पूर्ण अन्यथा
				pending++;
		पूर्ण
		spin_unlock_irq(&bus->reg_lock);
		अगर (!pending)
			वापस;
		msleep(1);
	पूर्ण
पूर्ण

/* clear irq_pending flags and assure no on-going workq */
अटल व्योम azx_clear_irq_pending(काष्ठा azx *chip)
अणु
	काष्ठा hdac_bus *bus = azx_bus(chip);
	काष्ठा hdac_stream *s;

	spin_lock_irq(&bus->reg_lock);
	list_क्रम_each_entry(s, &bus->stream_list, list) अणु
		काष्ठा azx_dev *azx_dev = stream_to_azx_dev(s);
		azx_dev->irq_pending = 0;
	पूर्ण
	spin_unlock_irq(&bus->reg_lock);
पूर्ण

अटल पूर्णांक azx_acquire_irq(काष्ठा azx *chip, पूर्णांक करो_disconnect)
अणु
	काष्ठा hdac_bus *bus = azx_bus(chip);

	अगर (request_irq(chip->pci->irq, azx_पूर्णांकerrupt,
			chip->msi ? 0 : IRQF_SHARED,
			chip->card->irq_descr, chip)) अणु
		dev_err(chip->card->dev,
			"unable to grab IRQ %d, disabling device\n",
			chip->pci->irq);
		अगर (करो_disconnect)
			snd_card_disconnect(chip->card);
		वापस -1;
	पूर्ण
	bus->irq = chip->pci->irq;
	chip->card->sync_irq = bus->irq;
	pci_पूर्णांकx(chip->pci, !chip->msi);
	वापस 0;
पूर्ण

/* get the current DMA position with correction on VIA chips */
अटल अचिन्हित पूर्णांक azx_via_get_position(काष्ठा azx *chip,
					 काष्ठा azx_dev *azx_dev)
अणु
	अचिन्हित पूर्णांक link_pos, mini_pos, bound_pos;
	अचिन्हित पूर्णांक mod_link_pos, mod_dma_pos, mod_mini_pos;
	अचिन्हित पूर्णांक fअगरo_size;

	link_pos = snd_hdac_stream_get_pos_lpib(azx_stream(azx_dev));
	अगर (azx_dev->core.substream->stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
		/* Playback, no problem using link position */
		वापस link_pos;
	पूर्ण

	/* Capture */
	/* For new chipset,
	 * use mod to get the DMA position just like old chipset
	 */
	mod_dma_pos = le32_to_cpu(*azx_dev->core.posbuf);
	mod_dma_pos %= azx_dev->core.period_bytes;

	fअगरo_size = azx_stream(azx_dev)->fअगरo_size - 1;

	अगर (azx_dev->insufficient) अणु
		/* Link position never gather than FIFO size */
		अगर (link_pos <= fअगरo_size)
			वापस 0;

		azx_dev->insufficient = 0;
	पूर्ण

	अगर (link_pos <= fअगरo_size)
		mini_pos = azx_dev->core.bufsize + link_pos - fअगरo_size;
	अन्यथा
		mini_pos = link_pos - fअगरo_size;

	/* Find nearest previous boudary */
	mod_mini_pos = mini_pos % azx_dev->core.period_bytes;
	mod_link_pos = link_pos % azx_dev->core.period_bytes;
	अगर (mod_link_pos >= fअगरo_size)
		bound_pos = link_pos - mod_link_pos;
	अन्यथा अगर (mod_dma_pos >= mod_mini_pos)
		bound_pos = mini_pos - mod_mini_pos;
	अन्यथा अणु
		bound_pos = mini_pos - mod_mini_pos + azx_dev->core.period_bytes;
		अगर (bound_pos >= azx_dev->core.bufsize)
			bound_pos = 0;
	पूर्ण

	/* Calculate real DMA position we want */
	वापस bound_pos + mod_dma_pos;
पूर्ण

#घोषणा AMD_FIFO_SIZE	32

/* get the current DMA position with FIFO size correction */
अटल अचिन्हित पूर्णांक azx_get_pos_fअगरo(काष्ठा azx *chip, काष्ठा azx_dev *azx_dev)
अणु
	काष्ठा snd_pcm_substream *substream = azx_dev->core.substream;
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	अचिन्हित पूर्णांक pos, delay;

	pos = snd_hdac_stream_get_pos_lpib(azx_stream(azx_dev));
	अगर (!runसमय)
		वापस pos;

	runसमय->delay = AMD_FIFO_SIZE;
	delay = frames_to_bytes(runसमय, AMD_FIFO_SIZE);
	अगर (azx_dev->insufficient) अणु
		अगर (pos < delay) अणु
			delay = pos;
			runसमय->delay = bytes_to_frames(runसमय, pos);
		पूर्ण अन्यथा अणु
			azx_dev->insufficient = 0;
		पूर्ण
	पूर्ण

	/* correct the DMA position क्रम capture stream */
	अगर (substream->stream == SNDRV_PCM_STREAM_CAPTURE) अणु
		अगर (pos < delay)
			pos += azx_dev->core.bufsize;
		pos -= delay;
	पूर्ण

	वापस pos;
पूर्ण

अटल पूर्णांक azx_get_delay_from_fअगरo(काष्ठा azx *chip, काष्ठा azx_dev *azx_dev,
				   अचिन्हित पूर्णांक pos)
अणु
	काष्ठा snd_pcm_substream *substream = azx_dev->core.substream;

	/* just पढ़ो back the calculated value in the above */
	वापस substream->runसमय->delay;
पूर्ण

अटल अचिन्हित पूर्णांक azx_skl_get_dpib_pos(काष्ठा azx *chip,
					 काष्ठा azx_dev *azx_dev)
अणु
	वापस _snd_hdac_chip_पढ़ोl(azx_bus(chip),
				    AZX_REG_VS_SDXDPIB_XBASE +
				    (AZX_REG_VS_SDXDPIB_XINTERVAL *
				     azx_dev->core.index));
पूर्ण

/* get the current DMA position with correction on SKL+ chips */
अटल अचिन्हित पूर्णांक azx_get_pos_skl(काष्ठा azx *chip, काष्ठा azx_dev *azx_dev)
अणु
	/* DPIB रेजिस्टर gives a more accurate position क्रम playback */
	अगर (azx_dev->core.substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		वापस azx_skl_get_dpib_pos(chip, azx_dev);

	/* For capture, we need to पढ़ो posbuf, but it requires a delay
	 * क्रम the possible boundary overlap; the पढ़ो of DPIB fetches the
	 * actual posbuf
	 */
	udelay(20);
	azx_skl_get_dpib_pos(chip, azx_dev);
	वापस azx_get_pos_posbuf(chip, azx_dev);
पूर्ण

#अगर_घोषित CONFIG_PM
अटल DEFINE_MUTEX(card_list_lock);
अटल LIST_HEAD(card_list);

अटल व्योम azx_add_card_list(काष्ठा azx *chip)
अणु
	काष्ठा hda_पूर्णांकel *hda = container_of(chip, काष्ठा hda_पूर्णांकel, chip);
	mutex_lock(&card_list_lock);
	list_add(&hda->list, &card_list);
	mutex_unlock(&card_list_lock);
पूर्ण

अटल व्योम azx_del_card_list(काष्ठा azx *chip)
अणु
	काष्ठा hda_पूर्णांकel *hda = container_of(chip, काष्ठा hda_पूर्णांकel, chip);
	mutex_lock(&card_list_lock);
	list_del_init(&hda->list);
	mutex_unlock(&card_list_lock);
पूर्ण

/* trigger घातer-save check at writing parameter */
अटल पूर्णांक param_set_xपूर्णांक(स्थिर अक्षर *val, स्थिर काष्ठा kernel_param *kp)
अणु
	काष्ठा hda_पूर्णांकel *hda;
	काष्ठा azx *chip;
	पूर्णांक prev = घातer_save;
	पूर्णांक ret = param_set_पूर्णांक(val, kp);

	अगर (ret || prev == घातer_save)
		वापस ret;

	mutex_lock(&card_list_lock);
	list_क्रम_each_entry(hda, &card_list, list) अणु
		chip = &hda->chip;
		अगर (!hda->probe_जारीd || chip->disabled)
			जारी;
		snd_hda_set_घातer_save(&chip->bus, घातer_save * 1000);
	पूर्ण
	mutex_unlock(&card_list_lock);
	वापस 0;
पूर्ण

/*
 * घातer management
 */
अटल bool azx_is_pm_पढ़ोy(काष्ठा snd_card *card)
अणु
	काष्ठा azx *chip;
	काष्ठा hda_पूर्णांकel *hda;

	अगर (!card)
		वापस false;
	chip = card->निजी_data;
	hda = container_of(chip, काष्ठा hda_पूर्णांकel, chip);
	अगर (chip->disabled || hda->init_failed || !chip->running)
		वापस false;
	वापस true;
पूर्ण

अटल व्योम __azx_runसमय_suspend(काष्ठा azx *chip)
अणु
	azx_stop_chip(chip);
	azx_enter_link_reset(chip);
	azx_clear_irq_pending(chip);
	display_घातer(chip, false);
पूर्ण

अटल व्योम __azx_runसमय_resume(काष्ठा azx *chip)
अणु
	काष्ठा hda_पूर्णांकel *hda = container_of(chip, काष्ठा hda_पूर्णांकel, chip);
	काष्ठा hdac_bus *bus = azx_bus(chip);
	काष्ठा hda_codec *codec;
	पूर्णांक status;

	display_घातer(chip, true);
	अगर (hda->need_i915_घातer)
		snd_hdac_i915_set_bclk(bus);

	/* Read STATESTS beक्रमe controller reset */
	status = azx_पढ़ोw(chip, STATESTS);

	azx_init_pci(chip);
	hda_पूर्णांकel_init_chip(chip, true);

	/* Aव्योम codec resume अगर runसमय resume is क्रम प्रणाली suspend */
	अगर (!chip->pm_prepared) अणु
		list_क्रम_each_codec(codec, &chip->bus) अणु
			अगर (codec->relaxed_resume)
				जारी;

			अगर (codec->क्रमced_resume || (status & (1 << codec->addr)))
				pm_request_resume(hda_codec_dev(codec));
		पूर्ण
	पूर्ण

	/* घातer करोwn again क्रम link-controlled chips */
	अगर (!hda->need_i915_घातer)
		display_घातer(chip, false);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक azx_prepare(काष्ठा device *dev)
अणु
	काष्ठा snd_card *card = dev_get_drvdata(dev);
	काष्ठा azx *chip;

	अगर (!azx_is_pm_पढ़ोy(card))
		वापस 0;

	chip = card->निजी_data;
	chip->pm_prepared = 1;
	snd_घातer_change_state(card, SNDRV_CTL_POWER_D3hot);

	flush_work(&azx_bus(chip)->unsol_work);

	/* HDA controller always requires dअगरferent WAKEEN क्रम runसमय suspend
	 * and प्रणाली suspend, so करोn't use direct-complete here.
	 */
	वापस 0;
पूर्ण

अटल व्योम azx_complete(काष्ठा device *dev)
अणु
	काष्ठा snd_card *card = dev_get_drvdata(dev);
	काष्ठा azx *chip;

	अगर (!azx_is_pm_पढ़ोy(card))
		वापस;

	chip = card->निजी_data;
	snd_घातer_change_state(card, SNDRV_CTL_POWER_D0);
	chip->pm_prepared = 0;
पूर्ण

अटल पूर्णांक azx_suspend(काष्ठा device *dev)
अणु
	काष्ठा snd_card *card = dev_get_drvdata(dev);
	काष्ठा azx *chip;
	काष्ठा hdac_bus *bus;

	अगर (!azx_is_pm_पढ़ोy(card))
		वापस 0;

	chip = card->निजी_data;
	bus = azx_bus(chip);
	__azx_runसमय_suspend(chip);
	अगर (bus->irq >= 0) अणु
		मुक्त_irq(bus->irq, chip);
		bus->irq = -1;
		chip->card->sync_irq = -1;
	पूर्ण

	अगर (chip->msi)
		pci_disable_msi(chip->pci);

	trace_azx_suspend(chip);
	वापस 0;
पूर्ण

अटल पूर्णांक azx_resume(काष्ठा device *dev)
अणु
	काष्ठा snd_card *card = dev_get_drvdata(dev);
	काष्ठा azx *chip;

	अगर (!azx_is_pm_पढ़ोy(card))
		वापस 0;

	chip = card->निजी_data;
	अगर (chip->msi)
		अगर (pci_enable_msi(chip->pci) < 0)
			chip->msi = 0;
	अगर (azx_acquire_irq(chip, 1) < 0)
		वापस -EIO;

	__azx_runसमय_resume(chip);

	trace_azx_resume(chip);
	वापस 0;
पूर्ण

/* put codec करोwn to D3 at hibernation क्रम Intel SKL+;
 * otherwise BIOS may still access the codec and screw up the driver
 */
अटल पूर्णांक azx_मुक्तze_noirq(काष्ठा device *dev)
अणु
	काष्ठा snd_card *card = dev_get_drvdata(dev);
	काष्ठा azx *chip = card->निजी_data;
	काष्ठा pci_dev *pci = to_pci_dev(dev);

	अगर (!azx_is_pm_पढ़ोy(card))
		वापस 0;
	अगर (chip->driver_type == AZX_DRIVER_SKL)
		pci_set_घातer_state(pci, PCI_D3hot);

	वापस 0;
पूर्ण

अटल पूर्णांक azx_thaw_noirq(काष्ठा device *dev)
अणु
	काष्ठा snd_card *card = dev_get_drvdata(dev);
	काष्ठा azx *chip = card->निजी_data;
	काष्ठा pci_dev *pci = to_pci_dev(dev);

	अगर (!azx_is_pm_पढ़ोy(card))
		वापस 0;
	अगर (chip->driver_type == AZX_DRIVER_SKL)
		pci_set_घातer_state(pci, PCI_D0);

	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

अटल पूर्णांक azx_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा snd_card *card = dev_get_drvdata(dev);
	काष्ठा azx *chip;

	अगर (!azx_is_pm_पढ़ोy(card))
		वापस 0;
	chip = card->निजी_data;

	/* enable controller wake up event */
	azx_ग_लिखोw(chip, WAKEEN, azx_पढ़ोw(chip, WAKEEN) | STATESTS_INT_MASK);

	__azx_runसमय_suspend(chip);
	trace_azx_runसमय_suspend(chip);
	वापस 0;
पूर्ण

अटल पूर्णांक azx_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा snd_card *card = dev_get_drvdata(dev);
	काष्ठा azx *chip;

	अगर (!azx_is_pm_पढ़ोy(card))
		वापस 0;
	chip = card->निजी_data;
	__azx_runसमय_resume(chip);

	/* disable controller Wake Up event*/
	azx_ग_लिखोw(chip, WAKEEN, azx_पढ़ोw(chip, WAKEEN) & ~STATESTS_INT_MASK);

	trace_azx_runसमय_resume(chip);
	वापस 0;
पूर्ण

अटल पूर्णांक azx_runसमय_idle(काष्ठा device *dev)
अणु
	काष्ठा snd_card *card = dev_get_drvdata(dev);
	काष्ठा azx *chip;
	काष्ठा hda_पूर्णांकel *hda;

	अगर (!card)
		वापस 0;

	chip = card->निजी_data;
	hda = container_of(chip, काष्ठा hda_पूर्णांकel, chip);
	अगर (chip->disabled || hda->init_failed)
		वापस 0;

	अगर (!घातer_save_controller || !azx_has_pm_runसमय(chip) ||
	    azx_bus(chip)->codec_घातered || !chip->running)
		वापस -EBUSY;

	/* ELD notअगरication माला_लो broken when HD-audio bus is off */
	अगर (needs_eld_notअगरy_link(chip))
		वापस -EBUSY;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops azx_pm = अणु
	SET_SYSTEM_SLEEP_PM_OPS(azx_suspend, azx_resume)
#अगर_घोषित CONFIG_PM_SLEEP
	.prepare = azx_prepare,
	.complete = azx_complete,
	.मुक्तze_noirq = azx_मुक्तze_noirq,
	.thaw_noirq = azx_thaw_noirq,
#पूर्ण_अगर
	SET_RUNTIME_PM_OPS(azx_runसमय_suspend, azx_runसमय_resume, azx_runसमय_idle)
पूर्ण;

#घोषणा AZX_PM_OPS	&azx_pm
#अन्यथा
#घोषणा azx_add_card_list(chip) /* NOP */
#घोषणा azx_del_card_list(chip) /* NOP */
#घोषणा AZX_PM_OPS	शून्य
#पूर्ण_अगर /* CONFIG_PM */


अटल पूर्णांक azx_probe_जारी(काष्ठा azx *chip);

#अगर_घोषित SUPPORT_VGA_SWITCHEROO
अटल काष्ठा pci_dev *get_bound_vga(काष्ठा pci_dev *pci);

अटल व्योम azx_vs_set_state(काष्ठा pci_dev *pci,
			     क्रमागत vga_चयनeroo_state state)
अणु
	काष्ठा snd_card *card = pci_get_drvdata(pci);
	काष्ठा azx *chip = card->निजी_data;
	काष्ठा hda_पूर्णांकel *hda = container_of(chip, काष्ठा hda_पूर्णांकel, chip);
	काष्ठा hda_codec *codec;
	bool disabled;

	रुको_क्रम_completion(&hda->probe_रुको);
	अगर (hda->init_failed)
		वापस;

	disabled = (state == VGA_SWITCHEROO_OFF);
	अगर (chip->disabled == disabled)
		वापस;

	अगर (!hda->probe_जारीd) अणु
		chip->disabled = disabled;
		अगर (!disabled) अणु
			dev_info(chip->card->dev,
				 "Start delayed initialization\n");
			अगर (azx_probe_जारी(chip) < 0)
				dev_err(chip->card->dev, "initialization error\n");
		पूर्ण
	पूर्ण अन्यथा अणु
		dev_info(chip->card->dev, "%s via vga_switcheroo\n",
			 disabled ? "Disabling" : "Enabling");
		अगर (disabled) अणु
			list_क्रम_each_codec(codec, &chip->bus) अणु
				pm_runसमय_suspend(hda_codec_dev(codec));
				pm_runसमय_disable(hda_codec_dev(codec));
			पूर्ण
			pm_runसमय_suspend(card->dev);
			pm_runसमय_disable(card->dev);
			/* when we get suspended by vga_चयनeroo we end up in D3cold,
			 * however we have no ACPI handle, so pci/acpi can't put us there,
			 * put ourselves there */
			pci->current_state = PCI_D3cold;
			chip->disabled = true;
			अगर (snd_hda_lock_devices(&chip->bus))
				dev_warn(chip->card->dev,
					 "Cannot lock devices!\n");
		पूर्ण अन्यथा अणु
			snd_hda_unlock_devices(&chip->bus);
			chip->disabled = false;
			pm_runसमय_enable(card->dev);
			list_क्रम_each_codec(codec, &chip->bus) अणु
				pm_runसमय_enable(hda_codec_dev(codec));
				pm_runसमय_resume(hda_codec_dev(codec));
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल bool azx_vs_can_चयन(काष्ठा pci_dev *pci)
अणु
	काष्ठा snd_card *card = pci_get_drvdata(pci);
	काष्ठा azx *chip = card->निजी_data;
	काष्ठा hda_पूर्णांकel *hda = container_of(chip, काष्ठा hda_पूर्णांकel, chip);

	रुको_क्रम_completion(&hda->probe_रुको);
	अगर (hda->init_failed)
		वापस false;
	अगर (chip->disabled || !hda->probe_जारीd)
		वापस true;
	अगर (snd_hda_lock_devices(&chip->bus))
		वापस false;
	snd_hda_unlock_devices(&chip->bus);
	वापस true;
पूर्ण

/*
 * The discrete GPU cannot घातer करोwn unless the HDA controller runसमय
 * suspends, so activate runसमय PM on codecs even अगर घातer_save == 0.
 */
अटल व्योम setup_vga_चयनeroo_runसमय_pm(काष्ठा azx *chip)
अणु
	काष्ठा hda_पूर्णांकel *hda = container_of(chip, काष्ठा hda_पूर्णांकel, chip);
	काष्ठा hda_codec *codec;

	अगर (hda->use_vga_चयनeroo && !needs_eld_notअगरy_link(chip)) अणु
		list_क्रम_each_codec(codec, &chip->bus)
			codec->स्वतः_runसमय_pm = 1;
		/* reset the घातer save setup */
		अगर (chip->running)
			set_शेष_घातer_save(chip);
	पूर्ण
पूर्ण

अटल व्योम azx_vs_gpu_bound(काष्ठा pci_dev *pci,
			     क्रमागत vga_चयनeroo_client_id client_id)
अणु
	काष्ठा snd_card *card = pci_get_drvdata(pci);
	काष्ठा azx *chip = card->निजी_data;

	अगर (client_id == VGA_SWITCHEROO_DIS)
		chip->bus.keep_घातer = 0;
	setup_vga_चयनeroo_runसमय_pm(chip);
पूर्ण

अटल व्योम init_vga_चयनeroo(काष्ठा azx *chip)
अणु
	काष्ठा hda_पूर्णांकel *hda = container_of(chip, काष्ठा hda_पूर्णांकel, chip);
	काष्ठा pci_dev *p = get_bound_vga(chip->pci);
	काष्ठा pci_dev *parent;
	अगर (p) अणु
		dev_info(chip->card->dev,
			 "Handle vga_switcheroo audio client\n");
		hda->use_vga_चयनeroo = 1;

		/* cleared in either gpu_bound op or codec probe, or when its
		 * upstream port has _PR3 (i.e. dGPU).
		 */
		parent = pci_upstream_bridge(p);
		chip->bus.keep_घातer = parent ? !pci_pr3_present(parent) : 1;
		chip->driver_caps |= AZX_DCAPS_PM_RUNTIME;
		pci_dev_put(p);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा vga_चयनeroo_client_ops azx_vs_ops = अणु
	.set_gpu_state = azx_vs_set_state,
	.can_चयन = azx_vs_can_चयन,
	.gpu_bound = azx_vs_gpu_bound,
पूर्ण;

अटल पूर्णांक रेजिस्टर_vga_चयनeroo(काष्ठा azx *chip)
अणु
	काष्ठा hda_पूर्णांकel *hda = container_of(chip, काष्ठा hda_पूर्णांकel, chip);
	काष्ठा pci_dev *p;
	पूर्णांक err;

	अगर (!hda->use_vga_चयनeroo)
		वापस 0;

	p = get_bound_vga(chip->pci);
	err = vga_चयनeroo_रेजिस्टर_audio_client(chip->pci, &azx_vs_ops, p);
	pci_dev_put(p);

	अगर (err < 0)
		वापस err;
	hda->vga_चयनeroo_रेजिस्टरed = 1;

	वापस 0;
पूर्ण
#अन्यथा
#घोषणा init_vga_चयनeroo(chip)		/* NOP */
#घोषणा रेजिस्टर_vga_चयनeroo(chip)		0
#घोषणा check_hdmi_disabled(pci)	false
#घोषणा setup_vga_चयनeroo_runसमय_pm(chip)	/* NOP */
#पूर्ण_अगर /* SUPPORT_VGA_SWITCHER */

/*
 * deकाष्ठाor
 */
अटल व्योम azx_मुक्त(काष्ठा azx *chip)
अणु
	काष्ठा pci_dev *pci = chip->pci;
	काष्ठा hda_पूर्णांकel *hda = container_of(chip, काष्ठा hda_पूर्णांकel, chip);
	काष्ठा hdac_bus *bus = azx_bus(chip);

	अगर (hda->मुक्तd)
		वापस;

	अगर (azx_has_pm_runसमय(chip) && chip->running)
		pm_runसमय_get_noresume(&pci->dev);
	chip->running = 0;

	azx_del_card_list(chip);

	hda->init_failed = 1; /* to be sure */
	complete_all(&hda->probe_रुको);

	अगर (use_vga_चयनeroo(hda)) अणु
		अगर (chip->disabled && hda->probe_जारीd)
			snd_hda_unlock_devices(&chip->bus);
		अगर (hda->vga_चयनeroo_रेजिस्टरed)
			vga_चयनeroo_unरेजिस्टर_client(chip->pci);
	पूर्ण

	अगर (bus->chip_init) अणु
		azx_clear_irq_pending(chip);
		azx_stop_all_streams(chip);
		azx_stop_chip(chip);
	पूर्ण

	अगर (bus->irq >= 0)
		मुक्त_irq(bus->irq, (व्योम*)chip);
	अगर (chip->msi)
		pci_disable_msi(chip->pci);
	iounmap(bus->remap_addr);

	azx_मुक्त_stream_pages(chip);
	azx_मुक्त_streams(chip);
	snd_hdac_bus_निकास(bus);

	अगर (chip->region_requested)
		pci_release_regions(chip->pci);

	pci_disable_device(chip->pci);
#अगर_घोषित CONFIG_SND_HDA_PATCH_LOADER
	release_firmware(chip->fw);
#पूर्ण_अगर
	display_घातer(chip, false);

	अगर (chip->driver_caps & AZX_DCAPS_I915_COMPONENT)
		snd_hdac_i915_निकास(bus);

	hda->मुक्तd = 1;
पूर्ण

अटल पूर्णांक azx_dev_disconnect(काष्ठा snd_device *device)
अणु
	काष्ठा azx *chip = device->device_data;
	काष्ठा hdac_bus *bus = azx_bus(chip);

	chip->bus.shutकरोwn = 1;
	cancel_work_sync(&bus->unsol_work);

	वापस 0;
पूर्ण

अटल पूर्णांक azx_dev_मुक्त(काष्ठा snd_device *device)
अणु
	azx_मुक्त(device->device_data);
	वापस 0;
पूर्ण

#अगर_घोषित SUPPORT_VGA_SWITCHEROO
#अगर_घोषित CONFIG_ACPI
/* ATPX is in the पूर्णांकegrated GPU's namespace */
अटल bool atpx_present(व्योम)
अणु
	काष्ठा pci_dev *pdev = शून्य;
	acpi_handle dhandle, atpx_handle;
	acpi_status status;

	जबतक ((pdev = pci_get_class(PCI_CLASS_DISPLAY_VGA << 8, pdev)) != शून्य) अणु
		dhandle = ACPI_HANDLE(&pdev->dev);
		अगर (dhandle) अणु
			status = acpi_get_handle(dhandle, "ATPX", &atpx_handle);
			अगर (ACPI_SUCCESS(status)) अणु
				pci_dev_put(pdev);
				वापस true;
			पूर्ण
		पूर्ण
	पूर्ण
	जबतक ((pdev = pci_get_class(PCI_CLASS_DISPLAY_OTHER << 8, pdev)) != शून्य) अणु
		dhandle = ACPI_HANDLE(&pdev->dev);
		अगर (dhandle) अणु
			status = acpi_get_handle(dhandle, "ATPX", &atpx_handle);
			अगर (ACPI_SUCCESS(status)) अणु
				pci_dev_put(pdev);
				वापस true;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस false;
पूर्ण
#अन्यथा
अटल bool atpx_present(व्योम)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर

/*
 * Check of disabled HDMI controller by vga_चयनeroo
 */
अटल काष्ठा pci_dev *get_bound_vga(काष्ठा pci_dev *pci)
अणु
	काष्ठा pci_dev *p;

	/* check only discrete GPU */
	चयन (pci->venकरोr) अणु
	हाल PCI_VENDOR_ID_ATI:
	हाल PCI_VENDOR_ID_AMD:
		अगर (pci->devfn == 1) अणु
			p = pci_get_करोमुख्य_bus_and_slot(pci_करोमुख्य_nr(pci->bus),
							pci->bus->number, 0);
			अगर (p) अणु
				/* ATPX is in the पूर्णांकegrated GPU's ACPI namespace
				 * rather than the dGPU's namespace. However,
				 * the dGPU is the one who is involved in
				 * vgaचयनeroo.
				 */
				अगर (((p->class >> 16) == PCI_BASE_CLASS_DISPLAY) &&
				    atpx_present())
					वापस p;
				pci_dev_put(p);
			पूर्ण
		पूर्ण
		अवरोध;
	हाल PCI_VENDOR_ID_NVIDIA:
		अगर (pci->devfn == 1) अणु
			p = pci_get_करोमुख्य_bus_and_slot(pci_करोमुख्य_nr(pci->bus),
							pci->bus->number, 0);
			अगर (p) अणु
				अगर ((p->class >> 16) == PCI_BASE_CLASS_DISPLAY)
					वापस p;
				pci_dev_put(p);
			पूर्ण
		पूर्ण
		अवरोध;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल bool check_hdmi_disabled(काष्ठा pci_dev *pci)
अणु
	bool vga_inactive = false;
	काष्ठा pci_dev *p = get_bound_vga(pci);

	अगर (p) अणु
		अगर (vga_चयनeroo_get_client_state(p) == VGA_SWITCHEROO_OFF)
			vga_inactive = true;
		pci_dev_put(p);
	पूर्ण
	वापस vga_inactive;
पूर्ण
#पूर्ण_अगर /* SUPPORT_VGA_SWITCHEROO */

/*
 * allow/deny-listing क्रम position_fix
 */
अटल स्थिर काष्ठा snd_pci_quirk position_fix_list[] = अणु
	SND_PCI_QUIRK(0x1028, 0x01cc, "Dell D820", POS_FIX_LPIB),
	SND_PCI_QUIRK(0x1028, 0x01de, "Dell Precision 390", POS_FIX_LPIB),
	SND_PCI_QUIRK(0x103c, 0x306d, "HP dv3", POS_FIX_LPIB),
	SND_PCI_QUIRK(0x1043, 0x813d, "ASUS P5AD2", POS_FIX_LPIB),
	SND_PCI_QUIRK(0x1043, 0x81b3, "ASUS", POS_FIX_LPIB),
	SND_PCI_QUIRK(0x1043, 0x81e7, "ASUS M2V", POS_FIX_LPIB),
	SND_PCI_QUIRK(0x104d, 0x9069, "Sony VPCS11V9E", POS_FIX_LPIB),
	SND_PCI_QUIRK(0x10de, 0xcb89, "Macbook Pro 7,1", POS_FIX_LPIB),
	SND_PCI_QUIRK(0x1297, 0x3166, "Shuttle", POS_FIX_LPIB),
	SND_PCI_QUIRK(0x1458, 0xa022, "ga-ma770-ud3", POS_FIX_LPIB),
	SND_PCI_QUIRK(0x1462, 0x1002, "MSI Wind U115", POS_FIX_LPIB),
	SND_PCI_QUIRK(0x1565, 0x8218, "Biostar Microtech", POS_FIX_LPIB),
	SND_PCI_QUIRK(0x1849, 0x0888, "775Dual-VSTA", POS_FIX_LPIB),
	SND_PCI_QUIRK(0x8086, 0x2503, "DG965OT AAD63733-203", POS_FIX_LPIB),
	अणुपूर्ण
पूर्ण;

अटल पूर्णांक check_position_fix(काष्ठा azx *chip, पूर्णांक fix)
अणु
	स्थिर काष्ठा snd_pci_quirk *q;

	चयन (fix) अणु
	हाल POS_FIX_AUTO:
	हाल POS_FIX_LPIB:
	हाल POS_FIX_POSBUF:
	हाल POS_FIX_VIACOMBO:
	हाल POS_FIX_COMBO:
	हाल POS_FIX_SKL:
	हाल POS_FIX_FIFO:
		वापस fix;
	पूर्ण

	q = snd_pci_quirk_lookup(chip->pci, position_fix_list);
	अगर (q) अणु
		dev_info(chip->card->dev,
			 "position_fix set to %d for device %04x:%04x\n",
			 q->value, q->subvenकरोr, q->subdevice);
		वापस q->value;
	पूर्ण

	/* Check VIA/ATI HD Audio Controller exist */
	अगर (chip->driver_type == AZX_DRIVER_VIA) अणु
		dev_dbg(chip->card->dev, "Using VIACOMBO position fix\n");
		वापस POS_FIX_VIACOMBO;
	पूर्ण
	अगर (chip->driver_caps & AZX_DCAPS_AMD_WORKAROUND) अणु
		dev_dbg(chip->card->dev, "Using FIFO position fix\n");
		वापस POS_FIX_FIFO;
	पूर्ण
	अगर (chip->driver_caps & AZX_DCAPS_POSFIX_LPIB) अणु
		dev_dbg(chip->card->dev, "Using LPIB position fix\n");
		वापस POS_FIX_LPIB;
	पूर्ण
	अगर (chip->driver_type == AZX_DRIVER_SKL) अणु
		dev_dbg(chip->card->dev, "Using SKL position fix\n");
		वापस POS_FIX_SKL;
	पूर्ण
	वापस POS_FIX_AUTO;
पूर्ण

अटल व्योम assign_position_fix(काष्ठा azx *chip, पूर्णांक fix)
अणु
	अटल स्थिर azx_get_pos_callback_t callbacks[] = अणु
		[POS_FIX_AUTO] = शून्य,
		[POS_FIX_LPIB] = azx_get_pos_lpib,
		[POS_FIX_POSBUF] = azx_get_pos_posbuf,
		[POS_FIX_VIACOMBO] = azx_via_get_position,
		[POS_FIX_COMBO] = azx_get_pos_lpib,
		[POS_FIX_SKL] = azx_get_pos_skl,
		[POS_FIX_FIFO] = azx_get_pos_fअगरo,
	पूर्ण;

	chip->get_position[0] = chip->get_position[1] = callbacks[fix];

	/* combo mode uses LPIB only क्रम playback */
	अगर (fix == POS_FIX_COMBO)
		chip->get_position[1] = शून्य;

	अगर ((fix == POS_FIX_POSBUF || fix == POS_FIX_SKL) &&
	    (chip->driver_caps & AZX_DCAPS_COUNT_LPIB_DELAY)) अणु
		chip->get_delay[0] = chip->get_delay[1] =
			azx_get_delay_from_lpib;
	पूर्ण

	अगर (fix == POS_FIX_FIFO)
		chip->get_delay[0] = chip->get_delay[1] =
			azx_get_delay_from_fअगरo;
पूर्ण

/*
 * deny-lists क्रम probe_mask
 */
अटल स्थिर काष्ठा snd_pci_quirk probe_mask_list[] = अणु
	/* Thinkpad often अवरोधs the controller communication when accessing
	 * to the non-working (or non-existing) modem codec slot.
	 */
	SND_PCI_QUIRK(0x1014, 0x05b7, "Thinkpad Z60", 0x01),
	SND_PCI_QUIRK(0x17aa, 0x2010, "Thinkpad X/T/R60", 0x01),
	SND_PCI_QUIRK(0x17aa, 0x20ac, "Thinkpad X/T/R61", 0x01),
	/* broken BIOS */
	SND_PCI_QUIRK(0x1028, 0x20ac, "Dell Studio Desktop", 0x01),
	/* including bogus ALC268 in slot#2 that conflicts with ALC888 */
	SND_PCI_QUIRK(0x17c0, 0x4085, "Medion MD96630", 0x01),
	/* क्रमced codec slots */
	SND_PCI_QUIRK(0x1043, 0x1262, "ASUS W5Fm", 0x103),
	SND_PCI_QUIRK(0x1046, 0x1262, "ASUS W5F", 0x103),
	/* WinFast VP200 H (Teradici) user reported broken communication */
	SND_PCI_QUIRK(0x3a21, 0x040d, "WinFast VP200 H", 0x101),
	अणुपूर्ण
पूर्ण;

#घोषणा AZX_FORCE_CODEC_MASK	0x100

अटल व्योम check_probe_mask(काष्ठा azx *chip, पूर्णांक dev)
अणु
	स्थिर काष्ठा snd_pci_quirk *q;

	chip->codec_probe_mask = probe_mask[dev];
	अगर (chip->codec_probe_mask == -1) अणु
		q = snd_pci_quirk_lookup(chip->pci, probe_mask_list);
		अगर (q) अणु
			dev_info(chip->card->dev,
				 "probe_mask set to 0x%x for device %04x:%04x\n",
				 q->value, q->subvenकरोr, q->subdevice);
			chip->codec_probe_mask = q->value;
		पूर्ण
	पूर्ण

	/* check क्रमced option */
	अगर (chip->codec_probe_mask != -1 &&
	    (chip->codec_probe_mask & AZX_FORCE_CODEC_MASK)) अणु
		azx_bus(chip)->codec_mask = chip->codec_probe_mask & 0xff;
		dev_info(chip->card->dev, "codec_mask forced to 0x%x\n",
			 (पूर्णांक)azx_bus(chip)->codec_mask);
	पूर्ण
पूर्ण

/*
 * allow/deny-list क्रम enable_msi
 */
अटल स्थिर काष्ठा snd_pci_quirk msi_deny_list[] = अणु
	SND_PCI_QUIRK(0x103c, 0x2191, "HP", 0), /* AMD Hudson */
	SND_PCI_QUIRK(0x103c, 0x2192, "HP", 0), /* AMD Hudson */
	SND_PCI_QUIRK(0x103c, 0x21f7, "HP", 0), /* AMD Hudson */
	SND_PCI_QUIRK(0x103c, 0x21fa, "HP", 0), /* AMD Hudson */
	SND_PCI_QUIRK(0x1043, 0x81f2, "ASUS", 0), /* Athlon64 X2 + nvidia */
	SND_PCI_QUIRK(0x1043, 0x81f6, "ASUS", 0), /* nvidia */
	SND_PCI_QUIRK(0x1043, 0x822d, "ASUS", 0), /* Athlon64 X2 + nvidia MCP55 */
	SND_PCI_QUIRK(0x1179, 0xfb44, "Toshiba Satellite C870", 0), /* AMD Hudson */
	SND_PCI_QUIRK(0x1849, 0x0888, "ASRock", 0), /* Athlon64 X2 + nvidia */
	SND_PCI_QUIRK(0xa0a0, 0x0575, "Aopen MZ915-M", 0), /* ICH6 */
	अणुपूर्ण
पूर्ण;

अटल व्योम check_msi(काष्ठा azx *chip)
अणु
	स्थिर काष्ठा snd_pci_quirk *q;

	अगर (enable_msi >= 0) अणु
		chip->msi = !!enable_msi;
		वापस;
	पूर्ण
	chip->msi = 1;	/* enable MSI as शेष */
	q = snd_pci_quirk_lookup(chip->pci, msi_deny_list);
	अगर (q) अणु
		dev_info(chip->card->dev,
			 "msi for device %04x:%04x set to %d\n",
			 q->subvenकरोr, q->subdevice, q->value);
		chip->msi = q->value;
		वापस;
	पूर्ण

	/* NVidia chipsets seem to cause troubles with MSI */
	अगर (chip->driver_caps & AZX_DCAPS_NO_MSI) अणु
		dev_info(chip->card->dev, "Disabling MSI\n");
		chip->msi = 0;
	पूर्ण
पूर्ण

/* check the snoop mode availability */
अटल व्योम azx_check_snoop_available(काष्ठा azx *chip)
अणु
	पूर्णांक snoop = hda_snoop;

	अगर (snoop >= 0) अणु
		dev_info(chip->card->dev, "Force to %s mode by module option\n",
			 snoop ? "snoop" : "non-snoop");
		chip->snoop = snoop;
		chip->uc_buffer = !snoop;
		वापस;
	पूर्ण

	snoop = true;
	अगर (azx_get_snoop_type(chip) == AZX_SNOOP_TYPE_NONE &&
	    chip->driver_type == AZX_DRIVER_VIA) अणु
		/* क्रमce to non-snoop mode क्रम a new VIA controller
		 * when BIOS is set
		 */
		u8 val;
		pci_पढ़ो_config_byte(chip->pci, 0x42, &val);
		अगर (!(val & 0x80) && (chip->pci->revision == 0x30 ||
				      chip->pci->revision == 0x20))
			snoop = false;
	पूर्ण

	अगर (chip->driver_caps & AZX_DCAPS_SNOOP_OFF)
		snoop = false;

	chip->snoop = snoop;
	अगर (!snoop) अणु
		dev_info(chip->card->dev, "Force to non-snoop mode\n");
		/* C-Media requires non-cached pages only क्रम CORB/RIRB */
		अगर (chip->driver_type != AZX_DRIVER_CMEDIA)
			chip->uc_buffer = true;
	पूर्ण
पूर्ण

अटल व्योम azx_probe_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा hda_पूर्णांकel *hda = container_of(work, काष्ठा hda_पूर्णांकel, probe_work);
	azx_probe_जारी(&hda->chip);
पूर्ण

अटल पूर्णांक शेष_bdl_pos_adj(काष्ठा azx *chip)
अणु
	/* some exceptions: Atoms seem problematic with value 1 */
	अगर (chip->pci->venकरोr == PCI_VENDOR_ID_INTEL) अणु
		चयन (chip->pci->device) अणु
		हाल 0x0f04: /* Baytrail */
		हाल 0x2284: /* Braswell */
			वापस 32;
		पूर्ण
	पूर्ण

	चयन (chip->driver_type) अणु
	हाल AZX_DRIVER_ICH:
	हाल AZX_DRIVER_PCH:
		वापस 1;
	शेष:
		वापस 32;
	पूर्ण
पूर्ण

/*
 * स्थिरructor
 */
अटल स्थिर काष्ठा hda_controller_ops pci_hda_ops;

अटल पूर्णांक azx_create(काष्ठा snd_card *card, काष्ठा pci_dev *pci,
		      पूर्णांक dev, अचिन्हित पूर्णांक driver_caps,
		      काष्ठा azx **rchip)
अणु
	अटल स्थिर काष्ठा snd_device_ops ops = अणु
		.dev_disconnect = azx_dev_disconnect,
		.dev_मुक्त = azx_dev_मुक्त,
	पूर्ण;
	काष्ठा hda_पूर्णांकel *hda;
	काष्ठा azx *chip;
	पूर्णांक err;

	*rchip = शून्य;

	err = pci_enable_device(pci);
	अगर (err < 0)
		वापस err;

	hda = devm_kzalloc(&pci->dev, माप(*hda), GFP_KERNEL);
	अगर (!hda) अणु
		pci_disable_device(pci);
		वापस -ENOMEM;
	पूर्ण

	chip = &hda->chip;
	mutex_init(&chip->खोलो_mutex);
	chip->card = card;
	chip->pci = pci;
	chip->ops = &pci_hda_ops;
	chip->driver_caps = driver_caps;
	chip->driver_type = driver_caps & 0xff;
	check_msi(chip);
	chip->dev_index = dev;
	अगर (jackpoll_ms[dev] >= 50 && jackpoll_ms[dev] <= 60000)
		chip->jackpoll_पूर्णांकerval = msecs_to_jअगरfies(jackpoll_ms[dev]);
	INIT_LIST_HEAD(&chip->pcm_list);
	INIT_WORK(&hda->irq_pending_work, azx_irq_pending_work);
	INIT_LIST_HEAD(&hda->list);
	init_vga_चयनeroo(chip);
	init_completion(&hda->probe_रुको);

	assign_position_fix(chip, check_position_fix(chip, position_fix[dev]));

	check_probe_mask(chip, dev);

	अगर (single_cmd < 0) /* allow fallback to single_cmd at errors */
		chip->fallback_to_single_cmd = 1;
	अन्यथा /* explicitly set to single_cmd or not */
		chip->single_cmd = single_cmd;

	azx_check_snoop_available(chip);

	अगर (bdl_pos_adj[dev] < 0)
		chip->bdl_pos_adj = शेष_bdl_pos_adj(chip);
	अन्यथा
		chip->bdl_pos_adj = bdl_pos_adj[dev];

	err = azx_bus_init(chip, model[dev]);
	अगर (err < 0) अणु
		pci_disable_device(pci);
		वापस err;
	पूर्ण

	/* use the non-cached pages in non-snoop mode */
	अगर (!azx_snoop(chip))
		azx_bus(chip)->dma_type = SNDRV_DMA_TYPE_DEV_UC;

	अगर (chip->driver_type == AZX_DRIVER_NVIDIA) अणु
		dev_dbg(chip->card->dev, "Enable delay in RIRB handling\n");
		chip->bus.core.needs_damn_दीर्घ_delay = 1;
	पूर्ण

	err = snd_device_new(card, SNDRV_DEV_LOWLEVEL, chip, &ops);
	अगर (err < 0) अणु
		dev_err(card->dev, "Error creating device [card]!\n");
		azx_मुक्त(chip);
		वापस err;
	पूर्ण

	/* जारी probing in work context as may trigger request module */
	INIT_WORK(&hda->probe_work, azx_probe_work);

	*rchip = chip;

	वापस 0;
पूर्ण

अटल पूर्णांक azx_first_init(काष्ठा azx *chip)
अणु
	पूर्णांक dev = chip->dev_index;
	काष्ठा pci_dev *pci = chip->pci;
	काष्ठा snd_card *card = chip->card;
	काष्ठा hdac_bus *bus = azx_bus(chip);
	पूर्णांक err;
	अचिन्हित लघु gcap;
	अचिन्हित पूर्णांक dma_bits = 64;

#अगर BITS_PER_LONG != 64
	/* Fix up base address on ULI M5461 */
	अगर (chip->driver_type == AZX_DRIVER_ULI) अणु
		u16 पंचांगp3;
		pci_पढ़ो_config_word(pci, 0x40, &पंचांगp3);
		pci_ग_लिखो_config_word(pci, 0x40, पंचांगp3 | 0x10);
		pci_ग_लिखो_config_dword(pci, PCI_BASE_ADDRESS_1, 0);
	पूर्ण
#पूर्ण_अगर

	err = pci_request_regions(pci, "ICH HD audio");
	अगर (err < 0)
		वापस err;
	chip->region_requested = 1;

	bus->addr = pci_resource_start(pci, 0);
	bus->remap_addr = pci_ioremap_bar(pci, 0);
	अगर (bus->remap_addr == शून्य) अणु
		dev_err(card->dev, "ioremap error\n");
		वापस -ENXIO;
	पूर्ण

	अगर (chip->driver_type == AZX_DRIVER_SKL)
		snd_hdac_bus_parse_capabilities(bus);

	/*
	 * Some Intel CPUs has always running समयr (ART) feature and
	 * controller may have Global समय sync reporting capability, so
	 * check both of these beक्रमe declaring synchronized समय reporting
	 * capability SNDRV_PCM_INFO_HAS_LINK_SYNCHRONIZED_ATIME
	 */
	chip->gts_present = false;

#अगर_घोषित CONFIG_X86
	अगर (bus->ppcap && boot_cpu_has(X86_FEATURE_ART))
		chip->gts_present = true;
#पूर्ण_अगर

	अगर (chip->msi) अणु
		अगर (chip->driver_caps & AZX_DCAPS_NO_MSI64) अणु
			dev_dbg(card->dev, "Disabling 64bit MSI\n");
			pci->no_64bit_msi = true;
		पूर्ण
		अगर (pci_enable_msi(pci) < 0)
			chip->msi = 0;
	पूर्ण

	pci_set_master(pci);

	gcap = azx_पढ़ोw(chip, GCAP);
	dev_dbg(card->dev, "chipset global capabilities = 0x%x\n", gcap);

	/* AMD devices support 40 or 48bit DMA, take the safe one */
	अगर (chip->pci->venकरोr == PCI_VENDOR_ID_AMD)
		dma_bits = 40;

	/* disable SB600 64bit support क्रम safety */
	अगर (chip->pci->venकरोr == PCI_VENDOR_ID_ATI) अणु
		काष्ठा pci_dev *p_smbus;
		dma_bits = 40;
		p_smbus = pci_get_device(PCI_VENDOR_ID_ATI,
					 PCI_DEVICE_ID_ATI_SBX00_SMBUS,
					 शून्य);
		अगर (p_smbus) अणु
			अगर (p_smbus->revision < 0x30)
				gcap &= ~AZX_GCAP_64OK;
			pci_dev_put(p_smbus);
		पूर्ण
	पूर्ण

	/* NVidia hardware normally only supports up to 40 bits of DMA */
	अगर (chip->pci->venकरोr == PCI_VENDOR_ID_NVIDIA)
		dma_bits = 40;

	/* disable 64bit DMA address on some devices */
	अगर (chip->driver_caps & AZX_DCAPS_NO_64BIT) अणु
		dev_dbg(card->dev, "Disabling 64bit DMA\n");
		gcap &= ~AZX_GCAP_64OK;
	पूर्ण

	/* disable buffer size rounding to 128-byte multiples अगर supported */
	अगर (align_buffer_size >= 0)
		chip->align_buffer_size = !!align_buffer_size;
	अन्यथा अणु
		अगर (chip->driver_caps & AZX_DCAPS_NO_ALIGN_बफ_मानE)
			chip->align_buffer_size = 0;
		अन्यथा
			chip->align_buffer_size = 1;
	पूर्ण

	/* allow 64bit DMA address अगर supported by H/W */
	अगर (!(gcap & AZX_GCAP_64OK))
		dma_bits = 32;
	अगर (dma_set_mask_and_coherent(&pci->dev, DMA_BIT_MASK(dma_bits)))
		dma_set_mask_and_coherent(&pci->dev, DMA_BIT_MASK(32));

	/* पढ़ो number of streams from GCAP रेजिस्टर instead of using
	 * hardcoded value
	 */
	chip->capture_streams = (gcap >> 8) & 0x0f;
	chip->playback_streams = (gcap >> 12) & 0x0f;
	अगर (!chip->playback_streams && !chip->capture_streams) अणु
		/* gcap didn't give any info, चयनing to old method */

		चयन (chip->driver_type) अणु
		हाल AZX_DRIVER_ULI:
			chip->playback_streams = ULI_NUM_PLAYBACK;
			chip->capture_streams = ULI_NUM_CAPTURE;
			अवरोध;
		हाल AZX_DRIVER_ATIHDMI:
		हाल AZX_DRIVER_ATIHDMI_NS:
			chip->playback_streams = ATIHDMI_NUM_PLAYBACK;
			chip->capture_streams = ATIHDMI_NUM_CAPTURE;
			अवरोध;
		हाल AZX_DRIVER_GENERIC:
		शेष:
			chip->playback_streams = ICH6_NUM_PLAYBACK;
			chip->capture_streams = ICH6_NUM_CAPTURE;
			अवरोध;
		पूर्ण
	पूर्ण
	chip->capture_index_offset = 0;
	chip->playback_index_offset = chip->capture_streams;
	chip->num_streams = chip->playback_streams + chip->capture_streams;

	/* sanity check क्रम the SDxCTL.STRM field overflow */
	अगर (chip->num_streams > 15 &&
	    (chip->driver_caps & AZX_DCAPS_SEPARATE_STREAM_TAG) == 0) अणु
		dev_warn(chip->card->dev, "number of I/O streams is %d, "
			 "forcing separate stream tags", chip->num_streams);
		chip->driver_caps |= AZX_DCAPS_SEPARATE_STREAM_TAG;
	पूर्ण

	/* initialize streams */
	err = azx_init_streams(chip);
	अगर (err < 0)
		वापस err;

	err = azx_alloc_stream_pages(chip);
	अगर (err < 0)
		वापस err;

	/* initialize chip */
	azx_init_pci(chip);

	snd_hdac_i915_set_bclk(bus);

	hda_पूर्णांकel_init_chip(chip, (probe_only[dev] & 2) == 0);

	/* codec detection */
	अगर (!azx_bus(chip)->codec_mask) अणु
		dev_err(card->dev, "no codecs found!\n");
		/* keep running the rest क्रम the runसमय PM */
	पूर्ण

	अगर (azx_acquire_irq(chip, 0) < 0)
		वापस -EBUSY;

	म_नकल(card->driver, "HDA-Intel");
	strscpy(card->लघुname, driver_लघु_names[chip->driver_type],
		माप(card->लघुname));
	snम_लिखो(card->दीर्घname, माप(card->दीर्घname),
		 "%s at 0x%lx irq %i",
		 card->लघुname, bus->addr, bus->irq);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_SND_HDA_PATCH_LOADER
/* callback from request_firmware_noरुको() */
अटल व्योम azx_firmware_cb(स्थिर काष्ठा firmware *fw, व्योम *context)
अणु
	काष्ठा snd_card *card = context;
	काष्ठा azx *chip = card->निजी_data;

	अगर (fw)
		chip->fw = fw;
	अन्यथा
		dev_err(card->dev, "Cannot load firmware, continue without patching\n");
	अगर (!chip->disabled) अणु
		/* जारी probing */
		azx_probe_जारी(chip);
	पूर्ण
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक disable_msi_reset_irq(काष्ठा azx *chip)
अणु
	काष्ठा hdac_bus *bus = azx_bus(chip);
	पूर्णांक err;

	मुक्त_irq(bus->irq, chip);
	bus->irq = -1;
	chip->card->sync_irq = -1;
	pci_disable_msi(chip->pci);
	chip->msi = 0;
	err = azx_acquire_irq(chip, 1);
	अगर (err < 0)
		वापस err;

	वापस 0;
पूर्ण

अटल व्योम pcm_mmap_prepare(काष्ठा snd_pcm_substream *substream,
			     काष्ठा vm_area_काष्ठा *area)
अणु
#अगर_घोषित CONFIG_X86
	काष्ठा azx_pcm *apcm = snd_pcm_substream_chip(substream);
	काष्ठा azx *chip = apcm->chip;
	अगर (chip->uc_buffer)
		area->vm_page_prot = pgprot_ग_लिखोcombine(area->vm_page_prot);
#पूर्ण_अगर
पूर्ण

/* Denylist क्रम skipping the whole probe:
 * some HD-audio PCI entries are exposed without any codecs, and such devices
 * should be ignored from the beginning.
 */
अटल स्थिर काष्ठा pci_device_id driver_denylist[] = अणु
	अणु PCI_DEVICE_SUB(0x1022, 0x1487, 0x1043, 0x874f) पूर्ण, /* ASUS ROG Zenith II / Strix */
	अणु PCI_DEVICE_SUB(0x1022, 0x1487, 0x1462, 0xcb59) पूर्ण, /* MSI TRX40 Creator */
	अणु PCI_DEVICE_SUB(0x1022, 0x1487, 0x1462, 0xcb60) पूर्ण, /* MSI TRX40 */
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा hda_controller_ops pci_hda_ops = अणु
	.disable_msi_reset_irq = disable_msi_reset_irq,
	.pcm_mmap_prepare = pcm_mmap_prepare,
	.position_check = azx_position_check,
पूर्ण;

अटल पूर्णांक azx_probe(काष्ठा pci_dev *pci,
		     स्थिर काष्ठा pci_device_id *pci_id)
अणु
	अटल पूर्णांक dev;
	काष्ठा snd_card *card;
	काष्ठा hda_पूर्णांकel *hda;
	काष्ठा azx *chip;
	bool schedule_probe;
	पूर्णांक err;

	अगर (pci_match_id(driver_denylist, pci)) अणु
		dev_info(&pci->dev, "Skipping the device on the denylist\n");
		वापस -ENODEV;
	पूर्ण

	अगर (dev >= SNDRV_CARDS)
		वापस -ENODEV;
	अगर (!enable[dev]) अणु
		dev++;
		वापस -ENOENT;
	पूर्ण

	/*
	 * stop probe अगर another Intel's DSP driver should be activated
	 */
	अगर (dmic_detect) अणु
		err = snd_पूर्णांकel_dsp_driver_probe(pci);
		अगर (err != SND_INTEL_DSP_DRIVER_ANY && err != SND_INTEL_DSP_DRIVER_LEGACY) अणु
			dev_dbg(&pci->dev, "HDAudio driver not selected, aborting probe\n");
			वापस -ENODEV;
		पूर्ण
	पूर्ण अन्यथा अणु
		dev_warn(&pci->dev, "dmic_detect option is deprecated, pass snd-intel-dspcfg.dsp_driver=1 option instead\n");
	पूर्ण

	err = snd_card_new(&pci->dev, index[dev], id[dev], THIS_MODULE,
			   0, &card);
	अगर (err < 0) अणु
		dev_err(&pci->dev, "Error creating card!\n");
		वापस err;
	पूर्ण

	err = azx_create(card, pci, dev, pci_id->driver_data, &chip);
	अगर (err < 0)
		जाओ out_मुक्त;
	card->निजी_data = chip;
	hda = container_of(chip, काष्ठा hda_पूर्णांकel, chip);

	pci_set_drvdata(pci, card);

	err = रेजिस्टर_vga_चयनeroo(chip);
	अगर (err < 0) अणु
		dev_err(card->dev, "Error registering vga_switcheroo client\n");
		जाओ out_मुक्त;
	पूर्ण

	अगर (check_hdmi_disabled(pci)) अणु
		dev_info(card->dev, "VGA controller is disabled\n");
		dev_info(card->dev, "Delaying initialization\n");
		chip->disabled = true;
	पूर्ण

	schedule_probe = !chip->disabled;

#अगर_घोषित CONFIG_SND_HDA_PATCH_LOADER
	अगर (patch[dev] && *patch[dev]) अणु
		dev_info(card->dev, "Applying patch firmware '%s'\n",
			 patch[dev]);
		err = request_firmware_noरुको(THIS_MODULE, true, patch[dev],
					      &pci->dev, GFP_KERNEL, card,
					      azx_firmware_cb);
		अगर (err < 0)
			जाओ out_मुक्त;
		schedule_probe = false; /* जारीd in azx_firmware_cb() */
	पूर्ण
#पूर्ण_अगर /* CONFIG_SND_HDA_PATCH_LOADER */

#अगर_अघोषित CONFIG_SND_HDA_I915
	अगर (CONTROLLER_IN_GPU(pci))
		dev_err(card->dev, "Haswell/Broadwell HDMI/DP must build in CONFIG_SND_HDA_I915\n");
#पूर्ण_अगर

	अगर (schedule_probe)
		schedule_work(&hda->probe_work);

	dev++;
	अगर (chip->disabled)
		complete_all(&hda->probe_रुको);
	वापस 0;

out_मुक्त:
	snd_card_मुक्त(card);
	वापस err;
पूर्ण

#अगर_घोषित CONFIG_PM
/* On some boards setting घातer_save to a non 0 value leads to clicking /
 * popping sounds when ever we enter/leave घातersaving mode. Ideally we would
 * figure out how to aव्योम these sounds, but that is not always feasible.
 * So we keep a list of devices where we disable घातersaving as its known
 * to causes problems on these devices.
 */
अटल स्थिर काष्ठा snd_pci_quirk घातer_save_denylist[] = अणु
	/* https://bugzilla.redhat.com/show_bug.cgi?id=1525104 */
	SND_PCI_QUIRK(0x1849, 0xc892, "Asrock B85M-ITX", 0),
	/* https://bugzilla.redhat.com/show_bug.cgi?id=1525104 */
	SND_PCI_QUIRK(0x1849, 0x0397, "Asrock N68C-S UCC", 0),
	/* https://bugzilla.redhat.com/show_bug.cgi?id=1525104 */
	SND_PCI_QUIRK(0x1849, 0x7662, "Asrock H81M-HDS", 0),
	/* https://bugzilla.redhat.com/show_bug.cgi?id=1525104 */
	SND_PCI_QUIRK(0x1043, 0x8733, "Asus Prime X370-Pro", 0),
	/* https://bugzilla.redhat.com/show_bug.cgi?id=1525104 */
	SND_PCI_QUIRK(0x1028, 0x0497, "Dell Precision T3600", 0),
	/* https://bugzilla.redhat.com/show_bug.cgi?id=1525104 */
	/* Note the P55A-UD3 and Z87-D3HP share the subsys id क्रम the HDA dev */
	SND_PCI_QUIRK(0x1458, 0xa002, "Gigabyte P55A-UD3 / Z87-D3HP", 0),
	/* https://bugzilla.redhat.com/show_bug.cgi?id=1525104 */
	SND_PCI_QUIRK(0x8086, 0x2040, "Intel DZ77BH-55K", 0),
	/* https://bugzilla.kernel.org/show_bug.cgi?id=199607 */
	SND_PCI_QUIRK(0x8086, 0x2057, "Intel NUC5i7RYB", 0),
	/* https://bugs.launchpad.net/bugs/1821663 */
	SND_PCI_QUIRK(0x8086, 0x2064, "Intel SDP 8086:2064", 0),
	/* https://bugzilla.redhat.com/show_bug.cgi?id=1520902 */
	SND_PCI_QUIRK(0x8086, 0x2068, "Intel NUC7i3BNB", 0),
	/* https://bugzilla.kernel.org/show_bug.cgi?id=198611 */
	SND_PCI_QUIRK(0x17aa, 0x2227, "Lenovo X1 Carbon 3rd Gen", 0),
	/* https://bugzilla.redhat.com/show_bug.cgi?id=1689623 */
	SND_PCI_QUIRK(0x17aa, 0x367b, "Lenovo IdeaCentre B550", 0),
	/* https://bugzilla.redhat.com/show_bug.cgi?id=1572975 */
	SND_PCI_QUIRK(0x17aa, 0x36a7, "Lenovo C50 All in one", 0),
	/* https://bugs.launchpad.net/bugs/1821663 */
	SND_PCI_QUIRK(0x1631, 0xe017, "Packard Bell NEC IMEDIA 5204", 0),
	अणुपूर्ण
पूर्ण;
#पूर्ण_अगर /* CONFIG_PM */

अटल व्योम set_शेष_घातer_save(काष्ठा azx *chip)
अणु
	पूर्णांक val = घातer_save;

#अगर_घोषित CONFIG_PM
	अगर (pm_blacklist) अणु
		स्थिर काष्ठा snd_pci_quirk *q;

		q = snd_pci_quirk_lookup(chip->pci, घातer_save_denylist);
		अगर (q && val) अणु
			dev_info(chip->card->dev, "device %04x:%04x is on the power_save denylist, forcing power_save to 0\n",
				 q->subvenकरोr, q->subdevice);
			val = 0;
		पूर्ण
	पूर्ण
#पूर्ण_अगर /* CONFIG_PM */
	snd_hda_set_घातer_save(&chip->bus, val * 1000);
पूर्ण

/* number of codec slots क्रम each chipset: 0 = शेष slots (i.e. 4) */
अटल स्थिर अचिन्हित पूर्णांक azx_max_codecs[AZX_NUM_DRIVERS] = अणु
	[AZX_DRIVER_NVIDIA] = 8,
	[AZX_DRIVER_TERA] = 1,
पूर्ण;

अटल पूर्णांक azx_probe_जारी(काष्ठा azx *chip)
अणु
	काष्ठा hda_पूर्णांकel *hda = container_of(chip, काष्ठा hda_पूर्णांकel, chip);
	काष्ठा hdac_bus *bus = azx_bus(chip);
	काष्ठा pci_dev *pci = chip->pci;
	पूर्णांक dev = chip->dev_index;
	पूर्णांक err;

	to_hda_bus(bus)->bus_probing = 1;
	hda->probe_जारीd = 1;

	/* bind with i915 अगर needed */
	अगर (chip->driver_caps & AZX_DCAPS_I915_COMPONENT) अणु
		err = snd_hdac_i915_init(bus);
		अगर (err < 0) अणु
			/* अगर the controller is bound only with HDMI/DP
			 * (क्रम HSW and BDW), we need to पात the probe;
			 * क्रम other chips, still जारी probing as other
			 * codecs can be on the same link.
			 */
			अगर (CONTROLLER_IN_GPU(pci)) अणु
				dev_err(chip->card->dev,
					"HSW/BDW HD-audio HDMI/DP requires binding with gfx driver\n");
				जाओ out_मुक्त;
			पूर्ण अन्यथा अणु
				/* करोn't bother any दीर्घer */
				chip->driver_caps &= ~AZX_DCAPS_I915_COMPONENT;
			पूर्ण
		पूर्ण

		/* HSW/BDW controllers need this घातer */
		अगर (CONTROLLER_IN_GPU(pci))
			hda->need_i915_घातer = true;
	पूर्ण

	/* Request display घातer well क्रम the HDA controller or codec. For
	 * Haswell/Broadwell, both the display HDA controller and codec need
	 * this घातer. For other platक्रमms, like Baytrail/Braswell, only the
	 * display codec needs the घातer and it can be released after probe.
	 */
	display_घातer(chip, true);

	err = azx_first_init(chip);
	अगर (err < 0)
		जाओ out_मुक्त;

#अगर_घोषित CONFIG_SND_HDA_INPUT_BEEP
	chip->beep_mode = beep_mode[dev];
#पूर्ण_अगर

	/* create codec instances */
	अगर (bus->codec_mask) अणु
		err = azx_probe_codecs(chip, azx_max_codecs[chip->driver_type]);
		अगर (err < 0)
			जाओ out_मुक्त;
	पूर्ण

#अगर_घोषित CONFIG_SND_HDA_PATCH_LOADER
	अगर (chip->fw) अणु
		err = snd_hda_load_patch(&chip->bus, chip->fw->size,
					 chip->fw->data);
		अगर (err < 0)
			जाओ out_मुक्त;
#अगर_अघोषित CONFIG_PM
		release_firmware(chip->fw); /* no दीर्घer needed */
		chip->fw = शून्य;
#पूर्ण_अगर
	पूर्ण
#पूर्ण_अगर
	अगर (bus->codec_mask && !(probe_only[dev] & 1)) अणु
		err = azx_codec_configure(chip);
		अगर (err < 0)
			जाओ out_मुक्त;
	पूर्ण

	err = snd_card_रेजिस्टर(chip->card);
	अगर (err < 0)
		जाओ out_मुक्त;

	setup_vga_चयनeroo_runसमय_pm(chip);

	chip->running = 1;
	azx_add_card_list(chip);

	set_शेष_घातer_save(chip);

	अगर (azx_has_pm_runसमय(chip)) अणु
		pm_runसमय_use_स्वतःsuspend(&pci->dev);
		pm_runसमय_allow(&pci->dev);
		pm_runसमय_put_स्वतःsuspend(&pci->dev);
	पूर्ण

out_मुक्त:
	अगर (err < 0) अणु
		azx_मुक्त(chip);
		वापस err;
	पूर्ण

	अगर (!hda->need_i915_घातer)
		display_घातer(chip, false);
	complete_all(&hda->probe_रुको);
	to_hda_bus(bus)->bus_probing = 0;
	वापस 0;
पूर्ण

अटल व्योम azx_हटाओ(काष्ठा pci_dev *pci)
अणु
	काष्ठा snd_card *card = pci_get_drvdata(pci);
	काष्ठा azx *chip;
	काष्ठा hda_पूर्णांकel *hda;

	अगर (card) अणु
		/* cancel the pending probing work */
		chip = card->निजी_data;
		hda = container_of(chip, काष्ठा hda_पूर्णांकel, chip);
		/* FIXME: below is an ugly workaround.
		 * Both device_release_driver() and driver_probe_device()
		 * take *both* the device's and its parent's lock beक्रमe
		 * calling the हटाओ() and probe() callbacks.  The codec
		 * probe takes the locks of both the codec itself and its
		 * parent, i.e. the PCI controller dev.  Meanजबतक, when
		 * the PCI controller is unbound, it takes its lock, too
		 * ==> ouch, a deadlock!
		 * As a workaround, we unlock temporarily here the controller
		 * device during cancel_work_sync() call.
		 */
		device_unlock(&pci->dev);
		cancel_work_sync(&hda->probe_work);
		device_lock(&pci->dev);

		snd_card_मुक्त(card);
	पूर्ण
पूर्ण

अटल व्योम azx_shutकरोwn(काष्ठा pci_dev *pci)
अणु
	काष्ठा snd_card *card = pci_get_drvdata(pci);
	काष्ठा azx *chip;

	अगर (!card)
		वापस;
	chip = card->निजी_data;
	अगर (chip && chip->running)
		azx_stop_chip(chip);
पूर्ण

/* PCI IDs */
अटल स्थिर काष्ठा pci_device_id azx_ids[] = अणु
	/* CPT */
	अणु PCI_DEVICE(0x8086, 0x1c20),
	  .driver_data = AZX_DRIVER_PCH | AZX_DCAPS_INTEL_PCH_NOPM पूर्ण,
	/* PBG */
	अणु PCI_DEVICE(0x8086, 0x1d20),
	  .driver_data = AZX_DRIVER_PCH | AZX_DCAPS_INTEL_PCH_NOPM पूर्ण,
	/* Panther Poपूर्णांक */
	अणु PCI_DEVICE(0x8086, 0x1e20),
	  .driver_data = AZX_DRIVER_PCH | AZX_DCAPS_INTEL_PCH_NOPM पूर्ण,
	/* Lynx Poपूर्णांक */
	अणु PCI_DEVICE(0x8086, 0x8c20),
	  .driver_data = AZX_DRIVER_PCH | AZX_DCAPS_INTEL_PCH पूर्ण,
	/* 9 Series */
	अणु PCI_DEVICE(0x8086, 0x8ca0),
	  .driver_data = AZX_DRIVER_PCH | AZX_DCAPS_INTEL_PCH पूर्ण,
	/* Wellsburg */
	अणु PCI_DEVICE(0x8086, 0x8d20),
	  .driver_data = AZX_DRIVER_PCH | AZX_DCAPS_INTEL_PCH पूर्ण,
	अणु PCI_DEVICE(0x8086, 0x8d21),
	  .driver_data = AZX_DRIVER_PCH | AZX_DCAPS_INTEL_PCH पूर्ण,
	/* Lewisburg */
	अणु PCI_DEVICE(0x8086, 0xa1f0),
	  .driver_data = AZX_DRIVER_PCH | AZX_DCAPS_INTEL_SKYLAKE पूर्ण,
	अणु PCI_DEVICE(0x8086, 0xa270),
	  .driver_data = AZX_DRIVER_PCH | AZX_DCAPS_INTEL_SKYLAKE पूर्ण,
	/* Lynx Poपूर्णांक-LP */
	अणु PCI_DEVICE(0x8086, 0x9c20),
	  .driver_data = AZX_DRIVER_PCH | AZX_DCAPS_INTEL_PCH पूर्ण,
	/* Lynx Poपूर्णांक-LP */
	अणु PCI_DEVICE(0x8086, 0x9c21),
	  .driver_data = AZX_DRIVER_PCH | AZX_DCAPS_INTEL_PCH पूर्ण,
	/* Wildcat Poपूर्णांक-LP */
	अणु PCI_DEVICE(0x8086, 0x9ca0),
	  .driver_data = AZX_DRIVER_PCH | AZX_DCAPS_INTEL_PCH पूर्ण,
	/* Sunrise Poपूर्णांक */
	अणु PCI_DEVICE(0x8086, 0xa170),
	  .driver_data = AZX_DRIVER_SKL | AZX_DCAPS_INTEL_SKYLAKE पूर्ण,
	/* Sunrise Poपूर्णांक-LP */
	अणु PCI_DEVICE(0x8086, 0x9d70),
	  .driver_data = AZX_DRIVER_SKL | AZX_DCAPS_INTEL_SKYLAKE पूर्ण,
	/* Kabylake */
	अणु PCI_DEVICE(0x8086, 0xa171),
	  .driver_data = AZX_DRIVER_SKL | AZX_DCAPS_INTEL_SKYLAKE पूर्ण,
	/* Kabylake-LP */
	अणु PCI_DEVICE(0x8086, 0x9d71),
	  .driver_data = AZX_DRIVER_SKL | AZX_DCAPS_INTEL_SKYLAKE पूर्ण,
	/* Kabylake-H */
	अणु PCI_DEVICE(0x8086, 0xa2f0),
	  .driver_data = AZX_DRIVER_SKL | AZX_DCAPS_INTEL_SKYLAKE पूर्ण,
	/* Coffelake */
	अणु PCI_DEVICE(0x8086, 0xa348),
	  .driver_data = AZX_DRIVER_SKL | AZX_DCAPS_INTEL_SKYLAKEपूर्ण,
	/* Cannonlake */
	अणु PCI_DEVICE(0x8086, 0x9dc8),
	  .driver_data = AZX_DRIVER_SKL | AZX_DCAPS_INTEL_SKYLAKEपूर्ण,
	/* CometLake-LP */
	अणु PCI_DEVICE(0x8086, 0x02C8),
	  .driver_data = AZX_DRIVER_SKL | AZX_DCAPS_INTEL_SKYLAKEपूर्ण,
	/* CometLake-H */
	अणु PCI_DEVICE(0x8086, 0x06C8),
	  .driver_data = AZX_DRIVER_SKL | AZX_DCAPS_INTEL_SKYLAKEपूर्ण,
	अणु PCI_DEVICE(0x8086, 0xf1c8),
	  .driver_data = AZX_DRIVER_SKL | AZX_DCAPS_INTEL_SKYLAKEपूर्ण,
	/* CometLake-S */
	अणु PCI_DEVICE(0x8086, 0xa3f0),
	  .driver_data = AZX_DRIVER_SKL | AZX_DCAPS_INTEL_SKYLAKEपूर्ण,
	/* CometLake-R */
	अणु PCI_DEVICE(0x8086, 0xf0c8),
	  .driver_data = AZX_DRIVER_SKL | AZX_DCAPS_INTEL_SKYLAKEपूर्ण,
	/* Icelake */
	अणु PCI_DEVICE(0x8086, 0x34c8),
	  .driver_data = AZX_DRIVER_SKL | AZX_DCAPS_INTEL_SKYLAKEपूर्ण,
	/* Icelake-H */
	अणु PCI_DEVICE(0x8086, 0x3dc8),
	  .driver_data = AZX_DRIVER_SKL | AZX_DCAPS_INTEL_SKYLAKEपूर्ण,
	/* Jasperlake */
	अणु PCI_DEVICE(0x8086, 0x38c8),
	  .driver_data = AZX_DRIVER_SKL | AZX_DCAPS_INTEL_SKYLAKEपूर्ण,
	अणु PCI_DEVICE(0x8086, 0x4dc8),
	  .driver_data = AZX_DRIVER_SKL | AZX_DCAPS_INTEL_SKYLAKEपूर्ण,
	/* Tigerlake */
	अणु PCI_DEVICE(0x8086, 0xa0c8),
	  .driver_data = AZX_DRIVER_SKL | AZX_DCAPS_INTEL_SKYLAKEपूर्ण,
	/* Tigerlake-H */
	अणु PCI_DEVICE(0x8086, 0x43c8),
	  .driver_data = AZX_DRIVER_SKL | AZX_DCAPS_INTEL_SKYLAKEपूर्ण,
	/* DG1 */
	अणु PCI_DEVICE(0x8086, 0x490d),
	  .driver_data = AZX_DRIVER_SKL | AZX_DCAPS_INTEL_SKYLAKEपूर्ण,
	/* Alderlake-S */
	अणु PCI_DEVICE(0x8086, 0x7ad0),
	  .driver_data = AZX_DRIVER_SKL | AZX_DCAPS_INTEL_SKYLAKEपूर्ण,
	/* Alderlake-P */
	अणु PCI_DEVICE(0x8086, 0x51c8),
	  .driver_data = AZX_DRIVER_SKL | AZX_DCAPS_INTEL_SKYLAKEपूर्ण,
	/* Alderlake-M */
	अणु PCI_DEVICE(0x8086, 0x51cc),
	  .driver_data = AZX_DRIVER_SKL | AZX_DCAPS_INTEL_SKYLAKEपूर्ण,
	/* Elkhart Lake */
	अणु PCI_DEVICE(0x8086, 0x4b55),
	  .driver_data = AZX_DRIVER_SKL | AZX_DCAPS_INTEL_SKYLAKEपूर्ण,
	अणु PCI_DEVICE(0x8086, 0x4b58),
	  .driver_data = AZX_DRIVER_SKL | AZX_DCAPS_INTEL_SKYLAKEपूर्ण,
	/* Broxton-P(Apollolake) */
	अणु PCI_DEVICE(0x8086, 0x5a98),
	  .driver_data = AZX_DRIVER_SKL | AZX_DCAPS_INTEL_BROXTON पूर्ण,
	/* Broxton-T */
	अणु PCI_DEVICE(0x8086, 0x1a98),
	  .driver_data = AZX_DRIVER_SKL | AZX_DCAPS_INTEL_BROXTON पूर्ण,
	/* Gemini-Lake */
	अणु PCI_DEVICE(0x8086, 0x3198),
	  .driver_data = AZX_DRIVER_SKL | AZX_DCAPS_INTEL_BROXTON पूर्ण,
	/* Haswell */
	अणु PCI_DEVICE(0x8086, 0x0a0c),
	  .driver_data = AZX_DRIVER_HDMI | AZX_DCAPS_INTEL_HASWELL पूर्ण,
	अणु PCI_DEVICE(0x8086, 0x0c0c),
	  .driver_data = AZX_DRIVER_HDMI | AZX_DCAPS_INTEL_HASWELL पूर्ण,
	अणु PCI_DEVICE(0x8086, 0x0d0c),
	  .driver_data = AZX_DRIVER_HDMI | AZX_DCAPS_INTEL_HASWELL पूर्ण,
	/* Broadwell */
	अणु PCI_DEVICE(0x8086, 0x160c),
	  .driver_data = AZX_DRIVER_HDMI | AZX_DCAPS_INTEL_BROADWELL पूर्ण,
	/* 5 Series/3400 */
	अणु PCI_DEVICE(0x8086, 0x3b56),
	  .driver_data = AZX_DRIVER_SCH | AZX_DCAPS_INTEL_PCH_NOPM पूर्ण,
	/* Poulsbo */
	अणु PCI_DEVICE(0x8086, 0x811b),
	  .driver_data = AZX_DRIVER_SCH | AZX_DCAPS_INTEL_PCH_BASE पूर्ण,
	/* Oaktrail */
	अणु PCI_DEVICE(0x8086, 0x080a),
	  .driver_data = AZX_DRIVER_SCH | AZX_DCAPS_INTEL_PCH_BASE पूर्ण,
	/* BayTrail */
	अणु PCI_DEVICE(0x8086, 0x0f04),
	  .driver_data = AZX_DRIVER_PCH | AZX_DCAPS_INTEL_BAYTRAIL पूर्ण,
	/* Braswell */
	अणु PCI_DEVICE(0x8086, 0x2284),
	  .driver_data = AZX_DRIVER_PCH | AZX_DCAPS_INTEL_BRASWELL पूर्ण,
	/* ICH6 */
	अणु PCI_DEVICE(0x8086, 0x2668),
	  .driver_data = AZX_DRIVER_ICH | AZX_DCAPS_INTEL_ICH पूर्ण,
	/* ICH7 */
	अणु PCI_DEVICE(0x8086, 0x27d8),
	  .driver_data = AZX_DRIVER_ICH | AZX_DCAPS_INTEL_ICH पूर्ण,
	/* ESB2 */
	अणु PCI_DEVICE(0x8086, 0x269a),
	  .driver_data = AZX_DRIVER_ICH | AZX_DCAPS_INTEL_ICH पूर्ण,
	/* ICH8 */
	अणु PCI_DEVICE(0x8086, 0x284b),
	  .driver_data = AZX_DRIVER_ICH | AZX_DCAPS_INTEL_ICH पूर्ण,
	/* ICH9 */
	अणु PCI_DEVICE(0x8086, 0x293e),
	  .driver_data = AZX_DRIVER_ICH | AZX_DCAPS_INTEL_ICH पूर्ण,
	/* ICH9 */
	अणु PCI_DEVICE(0x8086, 0x293f),
	  .driver_data = AZX_DRIVER_ICH | AZX_DCAPS_INTEL_ICH पूर्ण,
	/* ICH10 */
	अणु PCI_DEVICE(0x8086, 0x3a3e),
	  .driver_data = AZX_DRIVER_ICH | AZX_DCAPS_INTEL_ICH पूर्ण,
	/* ICH10 */
	अणु PCI_DEVICE(0x8086, 0x3a6e),
	  .driver_data = AZX_DRIVER_ICH | AZX_DCAPS_INTEL_ICH पूर्ण,
	/* Generic Intel */
	अणु PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_ANY_ID),
	  .class = PCI_CLASS_MULTIMEDIA_HD_AUDIO << 8,
	  .class_mask = 0xffffff,
	  .driver_data = AZX_DRIVER_ICH | AZX_DCAPS_NO_ALIGN_बफ_मानE पूर्ण,
	/* ATI SB 450/600/700/800/900 */
	अणु PCI_DEVICE(0x1002, 0x437b),
	  .driver_data = AZX_DRIVER_ATI | AZX_DCAPS_PRESET_ATI_SB पूर्ण,
	अणु PCI_DEVICE(0x1002, 0x4383),
	  .driver_data = AZX_DRIVER_ATI | AZX_DCAPS_PRESET_ATI_SB पूर्ण,
	/* AMD Hudson */
	अणु PCI_DEVICE(0x1022, 0x780d),
	  .driver_data = AZX_DRIVER_GENERIC | AZX_DCAPS_PRESET_ATI_SB पूर्ण,
	/* AMD, X370 & co */
	अणु PCI_DEVICE(0x1022, 0x1457),
	  .driver_data = AZX_DRIVER_GENERIC | AZX_DCAPS_PRESET_AMD_SB पूर्ण,
	/* AMD, X570 & co */
	अणु PCI_DEVICE(0x1022, 0x1487),
	  .driver_data = AZX_DRIVER_GENERIC | AZX_DCAPS_PRESET_AMD_SB पूर्ण,
	/* AMD Stoney */
	अणु PCI_DEVICE(0x1022, 0x157a),
	  .driver_data = AZX_DRIVER_GENERIC | AZX_DCAPS_PRESET_ATI_SB |
			 AZX_DCAPS_PM_RUNTIME पूर्ण,
	/* AMD Raven */
	अणु PCI_DEVICE(0x1022, 0x15e3),
	  .driver_data = AZX_DRIVER_GENERIC | AZX_DCAPS_PRESET_AMD_SB पूर्ण,
	/* ATI HDMI */
	अणु PCI_DEVICE(0x1002, 0x0002),
	  .driver_data = AZX_DRIVER_ATIHDMI_NS | AZX_DCAPS_PRESET_ATI_HDMI_NS |
	  AZX_DCAPS_PM_RUNTIME पूर्ण,
	अणु PCI_DEVICE(0x1002, 0x1308),
	  .driver_data = AZX_DRIVER_ATIHDMI_NS | AZX_DCAPS_PRESET_ATI_HDMI_NS पूर्ण,
	अणु PCI_DEVICE(0x1002, 0x157a),
	  .driver_data = AZX_DRIVER_ATIHDMI_NS | AZX_DCAPS_PRESET_ATI_HDMI_NS पूर्ण,
	अणु PCI_DEVICE(0x1002, 0x15b3),
	  .driver_data = AZX_DRIVER_ATIHDMI_NS | AZX_DCAPS_PRESET_ATI_HDMI_NS पूर्ण,
	अणु PCI_DEVICE(0x1002, 0x793b),
	  .driver_data = AZX_DRIVER_ATIHDMI | AZX_DCAPS_PRESET_ATI_HDMI पूर्ण,
	अणु PCI_DEVICE(0x1002, 0x7919),
	  .driver_data = AZX_DRIVER_ATIHDMI | AZX_DCAPS_PRESET_ATI_HDMI पूर्ण,
	अणु PCI_DEVICE(0x1002, 0x960f),
	  .driver_data = AZX_DRIVER_ATIHDMI | AZX_DCAPS_PRESET_ATI_HDMI पूर्ण,
	अणु PCI_DEVICE(0x1002, 0x970f),
	  .driver_data = AZX_DRIVER_ATIHDMI | AZX_DCAPS_PRESET_ATI_HDMI पूर्ण,
	अणु PCI_DEVICE(0x1002, 0x9840),
	  .driver_data = AZX_DRIVER_ATIHDMI_NS | AZX_DCAPS_PRESET_ATI_HDMI_NS पूर्ण,
	अणु PCI_DEVICE(0x1002, 0xaa00),
	  .driver_data = AZX_DRIVER_ATIHDMI | AZX_DCAPS_PRESET_ATI_HDMI पूर्ण,
	अणु PCI_DEVICE(0x1002, 0xaa08),
	  .driver_data = AZX_DRIVER_ATIHDMI | AZX_DCAPS_PRESET_ATI_HDMI पूर्ण,
	अणु PCI_DEVICE(0x1002, 0xaa10),
	  .driver_data = AZX_DRIVER_ATIHDMI | AZX_DCAPS_PRESET_ATI_HDMI पूर्ण,
	अणु PCI_DEVICE(0x1002, 0xaa18),
	  .driver_data = AZX_DRIVER_ATIHDMI | AZX_DCAPS_PRESET_ATI_HDMI पूर्ण,
	अणु PCI_DEVICE(0x1002, 0xaa20),
	  .driver_data = AZX_DRIVER_ATIHDMI | AZX_DCAPS_PRESET_ATI_HDMI पूर्ण,
	अणु PCI_DEVICE(0x1002, 0xaa28),
	  .driver_data = AZX_DRIVER_ATIHDMI | AZX_DCAPS_PRESET_ATI_HDMI पूर्ण,
	अणु PCI_DEVICE(0x1002, 0xaa30),
	  .driver_data = AZX_DRIVER_ATIHDMI | AZX_DCAPS_PRESET_ATI_HDMI पूर्ण,
	अणु PCI_DEVICE(0x1002, 0xaa38),
	  .driver_data = AZX_DRIVER_ATIHDMI | AZX_DCAPS_PRESET_ATI_HDMI पूर्ण,
	अणु PCI_DEVICE(0x1002, 0xaa40),
	  .driver_data = AZX_DRIVER_ATIHDMI | AZX_DCAPS_PRESET_ATI_HDMI पूर्ण,
	अणु PCI_DEVICE(0x1002, 0xaa48),
	  .driver_data = AZX_DRIVER_ATIHDMI | AZX_DCAPS_PRESET_ATI_HDMI पूर्ण,
	अणु PCI_DEVICE(0x1002, 0xaa50),
	  .driver_data = AZX_DRIVER_ATIHDMI | AZX_DCAPS_PRESET_ATI_HDMI पूर्ण,
	अणु PCI_DEVICE(0x1002, 0xaa58),
	  .driver_data = AZX_DRIVER_ATIHDMI | AZX_DCAPS_PRESET_ATI_HDMI पूर्ण,
	अणु PCI_DEVICE(0x1002, 0xaa60),
	  .driver_data = AZX_DRIVER_ATIHDMI | AZX_DCAPS_PRESET_ATI_HDMI पूर्ण,
	अणु PCI_DEVICE(0x1002, 0xaa68),
	  .driver_data = AZX_DRIVER_ATIHDMI | AZX_DCAPS_PRESET_ATI_HDMI पूर्ण,
	अणु PCI_DEVICE(0x1002, 0xaa80),
	  .driver_data = AZX_DRIVER_ATIHDMI | AZX_DCAPS_PRESET_ATI_HDMI पूर्ण,
	अणु PCI_DEVICE(0x1002, 0xaa88),
	  .driver_data = AZX_DRIVER_ATIHDMI | AZX_DCAPS_PRESET_ATI_HDMI पूर्ण,
	अणु PCI_DEVICE(0x1002, 0xaa90),
	  .driver_data = AZX_DRIVER_ATIHDMI | AZX_DCAPS_PRESET_ATI_HDMI पूर्ण,
	अणु PCI_DEVICE(0x1002, 0xaa98),
	  .driver_data = AZX_DRIVER_ATIHDMI | AZX_DCAPS_PRESET_ATI_HDMI पूर्ण,
	अणु PCI_DEVICE(0x1002, 0x9902),
	  .driver_data = AZX_DRIVER_ATIHDMI_NS | AZX_DCAPS_PRESET_ATI_HDMI_NS पूर्ण,
	अणु PCI_DEVICE(0x1002, 0xaaa0),
	  .driver_data = AZX_DRIVER_ATIHDMI_NS | AZX_DCAPS_PRESET_ATI_HDMI_NS पूर्ण,
	अणु PCI_DEVICE(0x1002, 0xaaa8),
	  .driver_data = AZX_DRIVER_ATIHDMI_NS | AZX_DCAPS_PRESET_ATI_HDMI_NS पूर्ण,
	अणु PCI_DEVICE(0x1002, 0xaab0),
	  .driver_data = AZX_DRIVER_ATIHDMI_NS | AZX_DCAPS_PRESET_ATI_HDMI_NS पूर्ण,
	अणु PCI_DEVICE(0x1002, 0xaac0),
	  .driver_data = AZX_DRIVER_ATIHDMI_NS | AZX_DCAPS_PRESET_ATI_HDMI_NS |
	  AZX_DCAPS_PM_RUNTIME पूर्ण,
	अणु PCI_DEVICE(0x1002, 0xaac8),
	  .driver_data = AZX_DRIVER_ATIHDMI_NS | AZX_DCAPS_PRESET_ATI_HDMI_NS |
	  AZX_DCAPS_PM_RUNTIME पूर्ण,
	अणु PCI_DEVICE(0x1002, 0xaad8),
	  .driver_data = AZX_DRIVER_ATIHDMI_NS | AZX_DCAPS_PRESET_ATI_HDMI_NS |
	  AZX_DCAPS_PM_RUNTIME पूर्ण,
	अणु PCI_DEVICE(0x1002, 0xaae0),
	  .driver_data = AZX_DRIVER_ATIHDMI_NS | AZX_DCAPS_PRESET_ATI_HDMI_NS |
	  AZX_DCAPS_PM_RUNTIME पूर्ण,
	अणु PCI_DEVICE(0x1002, 0xaae8),
	  .driver_data = AZX_DRIVER_ATIHDMI_NS | AZX_DCAPS_PRESET_ATI_HDMI_NS |
	  AZX_DCAPS_PM_RUNTIME पूर्ण,
	अणु PCI_DEVICE(0x1002, 0xaaf0),
	  .driver_data = AZX_DRIVER_ATIHDMI_NS | AZX_DCAPS_PRESET_ATI_HDMI_NS |
	  AZX_DCAPS_PM_RUNTIME पूर्ण,
	अणु PCI_DEVICE(0x1002, 0xaaf8),
	  .driver_data = AZX_DRIVER_ATIHDMI_NS | AZX_DCAPS_PRESET_ATI_HDMI_NS |
	  AZX_DCAPS_PM_RUNTIME पूर्ण,
	अणु PCI_DEVICE(0x1002, 0xab00),
	  .driver_data = AZX_DRIVER_ATIHDMI_NS | AZX_DCAPS_PRESET_ATI_HDMI_NS |
	  AZX_DCAPS_PM_RUNTIME पूर्ण,
	अणु PCI_DEVICE(0x1002, 0xab08),
	  .driver_data = AZX_DRIVER_ATIHDMI_NS | AZX_DCAPS_PRESET_ATI_HDMI_NS |
	  AZX_DCAPS_PM_RUNTIME पूर्ण,
	अणु PCI_DEVICE(0x1002, 0xab10),
	  .driver_data = AZX_DRIVER_ATIHDMI_NS | AZX_DCAPS_PRESET_ATI_HDMI_NS |
	  AZX_DCAPS_PM_RUNTIME पूर्ण,
	अणु PCI_DEVICE(0x1002, 0xab18),
	  .driver_data = AZX_DRIVER_ATIHDMI_NS | AZX_DCAPS_PRESET_ATI_HDMI_NS |
	  AZX_DCAPS_PM_RUNTIME पूर्ण,
	अणु PCI_DEVICE(0x1002, 0xab20),
	  .driver_data = AZX_DRIVER_ATIHDMI_NS | AZX_DCAPS_PRESET_ATI_HDMI_NS |
	  AZX_DCAPS_PM_RUNTIME पूर्ण,
	अणु PCI_DEVICE(0x1002, 0xab28),
	  .driver_data = AZX_DRIVER_ATIHDMI_NS | AZX_DCAPS_PRESET_ATI_HDMI_NS |
	  AZX_DCAPS_PM_RUNTIME पूर्ण,
	अणु PCI_DEVICE(0x1002, 0xab38),
	  .driver_data = AZX_DRIVER_ATIHDMI_NS | AZX_DCAPS_PRESET_ATI_HDMI_NS |
	  AZX_DCAPS_PM_RUNTIME पूर्ण,
	/* VIA VT8251/VT8237A */
	अणु PCI_DEVICE(0x1106, 0x3288), .driver_data = AZX_DRIVER_VIA पूर्ण,
	/* VIA GFX VT7122/VX900 */
	अणु PCI_DEVICE(0x1106, 0x9170), .driver_data = AZX_DRIVER_GENERIC पूर्ण,
	/* VIA GFX VT6122/VX11 */
	अणु PCI_DEVICE(0x1106, 0x9140), .driver_data = AZX_DRIVER_GENERIC पूर्ण,
	/* SIS966 */
	अणु PCI_DEVICE(0x1039, 0x7502), .driver_data = AZX_DRIVER_SIS पूर्ण,
	/* ULI M5461 */
	अणु PCI_DEVICE(0x10b9, 0x5461), .driver_data = AZX_DRIVER_ULI पूर्ण,
	/* NVIDIA MCP */
	अणु PCI_DEVICE(PCI_VENDOR_ID_NVIDIA, PCI_ANY_ID),
	  .class = PCI_CLASS_MULTIMEDIA_HD_AUDIO << 8,
	  .class_mask = 0xffffff,
	  .driver_data = AZX_DRIVER_NVIDIA | AZX_DCAPS_PRESET_NVIDIA पूर्ण,
	/* Teradici */
	अणु PCI_DEVICE(0x6549, 0x1200),
	  .driver_data = AZX_DRIVER_TERA | AZX_DCAPS_NO_64BIT पूर्ण,
	अणु PCI_DEVICE(0x6549, 0x2200),
	  .driver_data = AZX_DRIVER_TERA | AZX_DCAPS_NO_64BIT पूर्ण,
	/* Creative X-Fi (CA0110-IBG) */
	/* CTHDA chips */
	अणु PCI_DEVICE(0x1102, 0x0010),
	  .driver_data = AZX_DRIVER_CTHDA | AZX_DCAPS_PRESET_CTHDA पूर्ण,
	अणु PCI_DEVICE(0x1102, 0x0012),
	  .driver_data = AZX_DRIVER_CTHDA | AZX_DCAPS_PRESET_CTHDA पूर्ण,
#अगर !IS_ENABLED(CONFIG_SND_CTXFI)
	/* the following entry conflicts with snd-ctxfi driver,
	 * as ctxfi driver mutates from HD-audio to native mode with
	 * a special command sequence.
	 */
	अणु PCI_DEVICE(PCI_VENDOR_ID_CREATIVE, PCI_ANY_ID),
	  .class = PCI_CLASS_MULTIMEDIA_HD_AUDIO << 8,
	  .class_mask = 0xffffff,
	  .driver_data = AZX_DRIVER_CTX | AZX_DCAPS_CTX_WORKAROUND |
	  AZX_DCAPS_NO_64BIT | AZX_DCAPS_POSFIX_LPIB पूर्ण,
#अन्यथा
	/* this entry seems still valid -- i.e. without emu20kx chip */
	अणु PCI_DEVICE(0x1102, 0x0009),
	  .driver_data = AZX_DRIVER_CTX | AZX_DCAPS_CTX_WORKAROUND |
	  AZX_DCAPS_NO_64BIT | AZX_DCAPS_POSFIX_LPIB पूर्ण,
#पूर्ण_अगर
	/* CM8888 */
	अणु PCI_DEVICE(0x13f6, 0x5011),
	  .driver_data = AZX_DRIVER_CMEDIA |
	  AZX_DCAPS_NO_MSI | AZX_DCAPS_POSFIX_LPIB | AZX_DCAPS_SNOOP_OFF पूर्ण,
	/* Vortex86MX */
	अणु PCI_DEVICE(0x17f3, 0x3010), .driver_data = AZX_DRIVER_GENERIC पूर्ण,
	/* VMware HDAudio */
	अणु PCI_DEVICE(0x15ad, 0x1977), .driver_data = AZX_DRIVER_GENERIC पूर्ण,
	/* AMD/ATI Generic, PCI class code and Venकरोr ID क्रम HD Audio */
	अणु PCI_DEVICE(PCI_VENDOR_ID_ATI, PCI_ANY_ID),
	  .class = PCI_CLASS_MULTIMEDIA_HD_AUDIO << 8,
	  .class_mask = 0xffffff,
	  .driver_data = AZX_DRIVER_GENERIC | AZX_DCAPS_PRESET_ATI_HDMI पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_AMD, PCI_ANY_ID),
	  .class = PCI_CLASS_MULTIMEDIA_HD_AUDIO << 8,
	  .class_mask = 0xffffff,
	  .driver_data = AZX_DRIVER_GENERIC | AZX_DCAPS_PRESET_ATI_HDMI पूर्ण,
	/* Zhaoxin */
	अणु PCI_DEVICE(0x1d17, 0x3288), .driver_data = AZX_DRIVER_ZHAOXIN पूर्ण,
	अणु 0, पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, azx_ids);

/* pci_driver definition */
अटल काष्ठा pci_driver azx_driver = अणु
	.name = KBUILD_MODNAME,
	.id_table = azx_ids,
	.probe = azx_probe,
	.हटाओ = azx_हटाओ,
	.shutकरोwn = azx_shutकरोwn,
	.driver = अणु
		.pm = AZX_PM_OPS,
	पूर्ण,
पूर्ण;

module_pci_driver(azx_driver);
