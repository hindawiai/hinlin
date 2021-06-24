<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2019 Jaroslav Kysela <perex@perex.cz>

#समावेश <linux/acpi.h>
#समावेश <linux/bits.h>
#समावेश <linux/dmi.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/soundwire/sdw.h>
#समावेश <linux/soundwire/sdw_पूर्णांकel.h>
#समावेश <sound/core.h>
#समावेश <sound/पूर्णांकel-dsp-config.h>
#समावेश <sound/पूर्णांकel-nhlt.h>

अटल पूर्णांक dsp_driver;

module_param(dsp_driver, पूर्णांक, 0444);
MODULE_PARM_DESC(dsp_driver, "Force the DSP driver for Intel DSP (0=auto, 1=legacy, 2=SST, 3=SOF)");

#घोषणा FLAG_SST			BIT(0)
#घोषणा FLAG_SOF			BIT(1)
#घोषणा FLAG_SST_ONLY_IF_DMIC		BIT(15)
#घोषणा FLAG_SOF_ONLY_IF_DMIC		BIT(16)
#घोषणा FLAG_SOF_ONLY_IF_SOUNDWIRE	BIT(17)

#घोषणा FLAG_SOF_ONLY_IF_DMIC_OR_SOUNDWIRE (FLAG_SOF_ONLY_IF_DMIC | \
					    FLAG_SOF_ONLY_IF_SOUNDWIRE)

काष्ठा config_entry अणु
	u32 flags;
	u16 device;
	u8 acpi_hid[ACPI_ID_LEN];
	स्थिर काष्ठा dmi_प्रणाली_id *dmi_table;
पूर्ण;

/*
 * configuration table
 * - the order of similar PCI ID entries is important!
 * - the first successful match will win
 */
अटल स्थिर काष्ठा config_entry config_table[] = अणु
/* Merrअगरield */
#अगर IS_ENABLED(CONFIG_SND_SOC_SOF_MERRIFIELD)
	अणु
		.flags = FLAG_SOF,
		.device = 0x119a,
	पूर्ण,
#पूर्ण_अगर
/* Broxton-T */
#अगर IS_ENABLED(CONFIG_SND_SOC_SOF_APOLLOLAKE)
	अणु
		.flags = FLAG_SOF,
		.device = 0x1a98,
	पूर्ण,
#पूर्ण_अगर
/*
 * Apollolake (Broxton-P)
 * the legacy HDAudio driver is used except on Up Squared (SOF) and
 * Chromebooks (SST)
 */
#अगर IS_ENABLED(CONFIG_SND_SOC_SOF_APOLLOLAKE)
	अणु
		.flags = FLAG_SOF,
		.device = 0x5a98,
		.dmi_table = (स्थिर काष्ठा dmi_प्रणाली_id []) अणु
			अणु
				.ident = "Up Squared",
				.matches = अणु
					DMI_MATCH(DMI_SYS_VENDOR, "AAEON"),
					DMI_MATCH(DMI_BOARD_NAME, "UP-APL01"),
				पूर्ण
			पूर्ण,
			अणुपूर्ण
		पूर्ण
	पूर्ण,
#पूर्ण_अगर
#अगर IS_ENABLED(CONFIG_SND_SOC_INTEL_APL)
	अणु
		.flags = FLAG_SST,
		.device = 0x5a98,
		.dmi_table = (स्थिर काष्ठा dmi_प्रणाली_id []) अणु
			अणु
				.ident = "Google Chromebooks",
				.matches = अणु
					DMI_MATCH(DMI_SYS_VENDOR, "Google"),
				पूर्ण
			पूर्ण,
			अणुपूर्ण
		पूर्ण
	पूर्ण,
#पूर्ण_अगर
/*
 * Skylake and Kabylake use legacy HDAudio driver except क्रम Google
 * Chromebooks (SST)
 */

/* Sunrise Poपूर्णांक-LP */
#अगर IS_ENABLED(CONFIG_SND_SOC_INTEL_SKL)
	अणु
		.flags = FLAG_SST,
		.device = 0x9d70,
		.dmi_table = (स्थिर काष्ठा dmi_प्रणाली_id []) अणु
			अणु
				.ident = "Google Chromebooks",
				.matches = अणु
					DMI_MATCH(DMI_SYS_VENDOR, "Google"),
				पूर्ण
			पूर्ण,
			अणुपूर्ण
		पूर्ण
	पूर्ण,
	अणु
		.flags = FLAG_SST | FLAG_SST_ONLY_IF_DMIC,
		.device = 0x9d70,
	पूर्ण,
#पूर्ण_अगर
/* Kabylake-LP */
#अगर IS_ENABLED(CONFIG_SND_SOC_INTEL_KBL)
	अणु
		.flags = FLAG_SST,
		.device = 0x9d71,
		.dmi_table = (स्थिर काष्ठा dmi_प्रणाली_id []) अणु
			अणु
				.ident = "Google Chromebooks",
				.matches = अणु
					DMI_MATCH(DMI_SYS_VENDOR, "Google"),
				पूर्ण
			पूर्ण,
			अणुपूर्ण
		पूर्ण
	पूर्ण,
	अणु
		.flags = FLAG_SST | FLAG_SST_ONLY_IF_DMIC,
		.device = 0x9d71,
	पूर्ण,
#पूर्ण_अगर

/*
 * Geminilake uses legacy HDAudio driver except क्रम Google
 * Chromebooks
 */
/* Geminilake */
#अगर IS_ENABLED(CONFIG_SND_SOC_SOF_GEMINILAKE)
	अणु
		.flags = FLAG_SOF,
		.device = 0x3198,
		.dmi_table = (स्थिर काष्ठा dmi_प्रणाली_id []) अणु
			अणु
				.ident = "Google Chromebooks",
				.matches = अणु
					DMI_MATCH(DMI_SYS_VENDOR, "Google"),
				पूर्ण
			पूर्ण,
			अणुपूर्ण
		पूर्ण
	पूर्ण,
#पूर्ण_अगर

/*
 * CoffeeLake, CannonLake, CometLake, IceLake, TigerLake use legacy
 * HDAudio driver except क्रम Google Chromebooks and when DMICs are
 * present. Two हालs are required since Coreboot करोes not expose NHLT
 * tables.
 *
 * When the Chromebook quirk is not present, it's based on inक्रमmation
 * that no such device exists. When the quirk is present, it could be
 * either based on product inक्रमmation or a placeholder.
 */

/* Cannonlake */
#अगर IS_ENABLED(CONFIG_SND_SOC_SOF_CANNONLAKE)
	अणु
		.flags = FLAG_SOF,
		.device = 0x9dc8,
		.dmi_table = (स्थिर काष्ठा dmi_प्रणाली_id []) अणु
			अणु
				.ident = "Google Chromebooks",
				.matches = अणु
					DMI_MATCH(DMI_SYS_VENDOR, "Google"),
				पूर्ण
			पूर्ण,
			अणुपूर्ण
		पूर्ण
	पूर्ण,
	अणु
		.flags = FLAG_SOF | FLAG_SOF_ONLY_IF_DMIC_OR_SOUNDWIRE,
		.device = 0x9dc8,
	पूर्ण,
#पूर्ण_अगर

/* Coffelake */
#अगर IS_ENABLED(CONFIG_SND_SOC_SOF_COFFEELAKE)
	अणु
		.flags = FLAG_SOF,
		.device = 0xa348,
		.dmi_table = (स्थिर काष्ठा dmi_प्रणाली_id []) अणु
			अणु
				.ident = "Google Chromebooks",
				.matches = अणु
					DMI_MATCH(DMI_SYS_VENDOR, "Google"),
				पूर्ण
			पूर्ण,
			अणुपूर्ण
		पूर्ण
	पूर्ण,
	अणु
		.flags = FLAG_SOF | FLAG_SOF_ONLY_IF_DMIC_OR_SOUNDWIRE,
		.device = 0xa348,
	पूर्ण,
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_SND_SOC_SOF_COMETLAKE)
/* Cometlake-LP */
	अणु
		.flags = FLAG_SOF,
		.device = 0x02c8,
		.dmi_table = (स्थिर काष्ठा dmi_प्रणाली_id []) अणु
			अणु
				.ident = "Google Chromebooks",
				.matches = अणु
					DMI_MATCH(DMI_SYS_VENDOR, "Google"),
				पूर्ण
			पूर्ण,
			अणु
				.matches = अणु
					DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc"),
					DMI_EXACT_MATCH(DMI_PRODUCT_SKU, "09C6")
				पूर्ण,
			पूर्ण,
			अणु
				/* early version of SKU 09C6 */
				.matches = अणु
					DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc"),
					DMI_EXACT_MATCH(DMI_PRODUCT_SKU, "0983")
				पूर्ण,
			पूर्ण,
			अणुपूर्ण
		पूर्ण
	पूर्ण,
	अणु
		.flags = FLAG_SOF | FLAG_SOF_ONLY_IF_DMIC_OR_SOUNDWIRE,
		.device = 0x02c8,
	पूर्ण,
/* Cometlake-H */
	अणु
		.flags = FLAG_SOF,
		.device = 0x06c8,
		.dmi_table = (स्थिर काष्ठा dmi_प्रणाली_id []) अणु
			अणु
				.matches = अणु
					DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc"),
					DMI_EXACT_MATCH(DMI_PRODUCT_SKU, "098F"),
				पूर्ण,
			पूर्ण,
			अणु
				.matches = अणु
					DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc"),
					DMI_EXACT_MATCH(DMI_PRODUCT_SKU, "0990"),
				पूर्ण,
			पूर्ण,
			अणुपूर्ण
		पूर्ण
	पूर्ण,
	अणु
		.flags = FLAG_SOF | FLAG_SOF_ONLY_IF_DMIC_OR_SOUNDWIRE,
		.device = 0x06c8,
	पूर्ण,
#पूर्ण_अगर

/* Icelake */
#अगर IS_ENABLED(CONFIG_SND_SOC_SOF_ICELAKE)
	अणु
		.flags = FLAG_SOF,
		.device = 0x34c8,
		.dmi_table = (स्थिर काष्ठा dmi_प्रणाली_id []) अणु
			अणु
				.ident = "Google Chromebooks",
				.matches = अणु
					DMI_MATCH(DMI_SYS_VENDOR, "Google"),
				पूर्ण
			पूर्ण,
			अणुपूर्ण
		पूर्ण
	पूर्ण,
	अणु
		.flags = FLAG_SOF | FLAG_SOF_ONLY_IF_DMIC_OR_SOUNDWIRE,
		.device = 0x34c8,
	पूर्ण,
#पूर्ण_अगर

/* Tigerlake */
#अगर IS_ENABLED(CONFIG_SND_SOC_SOF_TIGERLAKE)
	अणु
		.flags = FLAG_SOF,
		.device = 0xa0c8,
		.dmi_table = (स्थिर काष्ठा dmi_प्रणाली_id []) अणु
			अणु
				.ident = "Google Chromebooks",
				.matches = अणु
					DMI_MATCH(DMI_SYS_VENDOR, "Google"),
				पूर्ण
			पूर्ण,
			अणुपूर्ण
		पूर्ण
	पूर्ण,
	अणु
		.flags = FLAG_SOF | FLAG_SOF_ONLY_IF_DMIC_OR_SOUNDWIRE,
		.device = 0xa0c8,
	पूर्ण,
	अणु
		.flags = FLAG_SOF | FLAG_SOF_ONLY_IF_DMIC_OR_SOUNDWIRE,
		.device = 0x43c8,
	पूर्ण,
#पूर्ण_अगर

/* Elkhart Lake */
#अगर IS_ENABLED(CONFIG_SND_SOC_SOF_ELKHARTLAKE)
	अणु
		.flags = FLAG_SOF | FLAG_SOF_ONLY_IF_DMIC,
		.device = 0x4b55,
	पूर्ण,
#पूर्ण_अगर

/* Alder Lake */
#अगर IS_ENABLED(CONFIG_SND_SOC_SOF_ALDERLAKE)
	अणु
		.flags = FLAG_SOF | FLAG_SOF_ONLY_IF_DMIC_OR_SOUNDWIRE,
		.device = 0x7ad0,
	पूर्ण,
	अणु
		.flags = FLAG_SOF | FLAG_SOF_ONLY_IF_DMIC_OR_SOUNDWIRE,
		.device = 0x51c8,
	पूर्ण,
	अणु
		.flags = FLAG_SOF | FLAG_SOF_ONLY_IF_DMIC_OR_SOUNDWIRE,
		.device = 0x51cc,
	पूर्ण,
#पूर्ण_अगर

पूर्ण;

अटल स्थिर काष्ठा config_entry *snd_पूर्णांकel_dsp_find_config
		(काष्ठा pci_dev *pci, स्थिर काष्ठा config_entry *table, u32 len)
अणु
	u16 device;

	device = pci->device;
	क्रम (; len > 0; len--, table++) अणु
		अगर (table->device != device)
			जारी;
		अगर (table->dmi_table && !dmi_check_प्रणाली(table->dmi_table))
			जारी;
		वापस table;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल पूर्णांक snd_पूर्णांकel_dsp_check_dmic(काष्ठा pci_dev *pci)
अणु
	काष्ठा nhlt_acpi_table *nhlt;
	पूर्णांक ret = 0;

	nhlt = पूर्णांकel_nhlt_init(&pci->dev);
	अगर (nhlt) अणु
		अगर (पूर्णांकel_nhlt_get_dmic_geo(&pci->dev, nhlt))
			ret = 1;
		पूर्णांकel_nhlt_मुक्त(nhlt);
	पूर्ण
	वापस ret;
पूर्ण

#अगर IS_ENABLED(CONFIG_SND_SOC_SOF_INTEL_SOUNDWIRE)
अटल पूर्णांक snd_पूर्णांकel_dsp_check_soundwire(काष्ठा pci_dev *pci)
अणु
	काष्ठा sdw_पूर्णांकel_acpi_info info;
	acpi_handle handle;
	पूर्णांक ret;

	handle = ACPI_HANDLE(&pci->dev);

	ret = sdw_पूर्णांकel_acpi_scan(handle, &info);
	अगर (ret < 0)
		वापस ret;

	वापस info.link_mask;
पूर्ण
#अन्यथा
अटल पूर्णांक snd_पूर्णांकel_dsp_check_soundwire(काष्ठा pci_dev *pci)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

पूर्णांक snd_पूर्णांकel_dsp_driver_probe(काष्ठा pci_dev *pci)
अणु
	स्थिर काष्ठा config_entry *cfg;

	/* Intel venकरोr only */
	अगर (pci->venकरोr != 0x8086)
		वापस SND_INTEL_DSP_DRIVER_ANY;

	/*
	 * Legacy devices करोn't have a PCI-based DSP and use HDaudio
	 * क्रम HDMI/DP support, ignore kernel parameter
	 */
	चयन (pci->device) अणु
	हाल 0x160c: /* Broadwell */
	हाल 0x0a0c: /* Haswell */
	हाल 0x0c0c:
	हाल 0x0d0c:
	हाल 0x0f04: /* Baytrail */
	हाल 0x2284: /* Braswell */
		वापस SND_INTEL_DSP_DRIVER_ANY;
	पूर्ण

	अगर (dsp_driver > 0 && dsp_driver <= SND_INTEL_DSP_DRIVER_LAST)
		वापस dsp_driver;

	/*
	 * detect DSP by checking class/subclass/prog-id inक्रमmation
	 * class=04 subclass 03 prog-अगर 00: no DSP, use legacy driver
	 * class=04 subclass 01 prog-अगर 00: DSP is present
	 *  (and may be required e.g. क्रम DMIC or SSP support)
	 * class=04 subclass 03 prog-अगर 80: use DSP or legacy mode
	 */
	अगर (pci->class == 0x040300)
		वापस SND_INTEL_DSP_DRIVER_LEGACY;
	अगर (pci->class != 0x040100 && pci->class != 0x040380) अणु
		dev_err(&pci->dev, "Unknown PCI class/subclass/prog-if information (0x%06x) found, selecting HDAudio legacy driver\n", pci->class);
		वापस SND_INTEL_DSP_DRIVER_LEGACY;
	पूर्ण

	dev_info(&pci->dev, "DSP detected with PCI class/subclass/prog-if info 0x%06x\n", pci->class);

	/* find the configuration क्रम the specअगरic device */
	cfg = snd_पूर्णांकel_dsp_find_config(pci, config_table, ARRAY_SIZE(config_table));
	अगर (!cfg)
		वापस SND_INTEL_DSP_DRIVER_ANY;

	अगर (cfg->flags & FLAG_SOF) अणु
		अगर (cfg->flags & FLAG_SOF_ONLY_IF_SOUNDWIRE &&
		    snd_पूर्णांकel_dsp_check_soundwire(pci) > 0) अणु
			dev_info(&pci->dev, "SoundWire enabled on CannonLake+ platform, using SOF driver\n");
			वापस SND_INTEL_DSP_DRIVER_SOF;
		पूर्ण
		अगर (cfg->flags & FLAG_SOF_ONLY_IF_DMIC &&
		    snd_पूर्णांकel_dsp_check_dmic(pci)) अणु
			dev_info(&pci->dev, "Digital mics found on Skylake+ platform, using SOF driver\n");
			वापस SND_INTEL_DSP_DRIVER_SOF;
		पूर्ण
		अगर (!(cfg->flags & FLAG_SOF_ONLY_IF_DMIC_OR_SOUNDWIRE))
			वापस SND_INTEL_DSP_DRIVER_SOF;
	पूर्ण


	अगर (cfg->flags & FLAG_SST) अणु
		अगर (cfg->flags & FLAG_SST_ONLY_IF_DMIC) अणु
			अगर (snd_पूर्णांकel_dsp_check_dmic(pci)) अणु
				dev_info(&pci->dev, "Digital mics found on Skylake+ platform, using SST driver\n");
				वापस SND_INTEL_DSP_DRIVER_SST;
			पूर्ण
		पूर्ण अन्यथा अणु
			वापस SND_INTEL_DSP_DRIVER_SST;
		पूर्ण
	पूर्ण

	वापस SND_INTEL_DSP_DRIVER_LEGACY;
पूर्ण
EXPORT_SYMBOL_GPL(snd_पूर्णांकel_dsp_driver_probe);

/* Should we शेष to SOF or SST क्रम BYT/CHT ? */
#अगर IS_ENABLED(CONFIG_SND_INTEL_BYT_PREFER_SOF) || \
    !IS_ENABLED(CONFIG_SND_SST_ATOM_HIFI2_PLATFORM_ACPI)
#घोषणा FLAG_SST_OR_SOF_BYT	FLAG_SOF
#अन्यथा
#घोषणा FLAG_SST_OR_SOF_BYT	FLAG_SST
#पूर्ण_अगर

/*
 * configuration table
 * - the order of similar ACPI ID entries is important!
 * - the first successful match will win
 */
अटल स्थिर काष्ठा config_entry acpi_config_table[] = अणु
#अगर IS_ENABLED(CONFIG_SND_SST_ATOM_HIFI2_PLATFORM_ACPI) || \
    IS_ENABLED(CONFIG_SND_SOC_SOF_BAYTRAIL)
/* BayTrail */
	अणु
		.flags = FLAG_SST_OR_SOF_BYT,
		.acpi_hid = "80860F28",
	पूर्ण,
/* CherryTrail */
	अणु
		.flags = FLAG_SST_OR_SOF_BYT,
		.acpi_hid = "808622A8",
	पूर्ण,
#पूर्ण_अगर
/* Broadwell */
#अगर IS_ENABLED(CONFIG_SND_SOC_INTEL_CATPT)
	अणु
		.flags = FLAG_SST,
		.acpi_hid = "INT3438"
	पूर्ण,
#पूर्ण_अगर
#अगर IS_ENABLED(CONFIG_SND_SOC_SOF_BROADWELL)
	अणु
		.flags = FLAG_SOF,
		.acpi_hid = "INT3438"
	पूर्ण,
#पूर्ण_अगर
/* Haswell - not supported by SOF but added क्रम consistency */
#अगर IS_ENABLED(CONFIG_SND_SOC_INTEL_CATPT)
	अणु
		.flags = FLAG_SST,
		.acpi_hid = "INT33C8"
	पूर्ण,
#पूर्ण_अगर
पूर्ण;

अटल स्थिर काष्ठा config_entry *snd_पूर्णांकel_acpi_dsp_find_config(स्थिर u8 acpi_hid[ACPI_ID_LEN],
								 स्थिर काष्ठा config_entry *table,
								 u32 len)
अणु
	क्रम (; len > 0; len--, table++) अणु
		अगर (स_भेद(table->acpi_hid, acpi_hid, ACPI_ID_LEN))
			जारी;
		अगर (table->dmi_table && !dmi_check_प्रणाली(table->dmi_table))
			जारी;
		वापस table;
	पूर्ण
	वापस शून्य;
पूर्ण

पूर्णांक snd_पूर्णांकel_acpi_dsp_driver_probe(काष्ठा device *dev, स्थिर u8 acpi_hid[ACPI_ID_LEN])
अणु
	स्थिर काष्ठा config_entry *cfg;

	अगर (dsp_driver > SND_INTEL_DSP_DRIVER_LEGACY && dsp_driver <= SND_INTEL_DSP_DRIVER_LAST)
		वापस dsp_driver;

	अगर (dsp_driver == SND_INTEL_DSP_DRIVER_LEGACY) अणु
		dev_warn(dev, "dsp_driver parameter %d not supported, using automatic detection\n",
			 SND_INTEL_DSP_DRIVER_LEGACY);
	पूर्ण

	/* find the configuration क्रम the specअगरic device */
	cfg = snd_पूर्णांकel_acpi_dsp_find_config(acpi_hid,  acpi_config_table,
					     ARRAY_SIZE(acpi_config_table));
	अगर (!cfg)
		वापस SND_INTEL_DSP_DRIVER_ANY;

	अगर (cfg->flags & FLAG_SST)
		वापस SND_INTEL_DSP_DRIVER_SST;

	अगर (cfg->flags & FLAG_SOF)
		वापस SND_INTEL_DSP_DRIVER_SOF;

	वापस SND_INTEL_DSP_DRIVER_SST;
पूर्ण
EXPORT_SYMBOL_GPL(snd_पूर्णांकel_acpi_dsp_driver_probe);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("Intel DSP config driver");
MODULE_IMPORT_NS(SND_INTEL_SOUNDWIRE_ACPI);
