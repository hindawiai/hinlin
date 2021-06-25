<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  पूर्णांकel-dsp-config.h - Intel DSP config
 *
 *  Copyright (c) 2019 Jaroslav Kysela <perex@perex.cz>
 */

#अगर_अघोषित __INTEL_DSP_CONFIG_H__
#घोषणा __INTEL_DSP_CONFIG_H__

काष्ठा pci_dev;

क्रमागत अणु
	SND_INTEL_DSP_DRIVER_ANY = 0,
	SND_INTEL_DSP_DRIVER_LEGACY,
	SND_INTEL_DSP_DRIVER_SST,
	SND_INTEL_DSP_DRIVER_SOF,
	SND_INTEL_DSP_DRIVER_LAST = SND_INTEL_DSP_DRIVER_SOF
पूर्ण;

#अगर IS_ENABLED(CONFIG_SND_INTEL_DSP_CONFIG)

पूर्णांक snd_पूर्णांकel_dsp_driver_probe(काष्ठा pci_dev *pci);
पूर्णांक snd_पूर्णांकel_acpi_dsp_driver_probe(काष्ठा device *dev, स्थिर u8 acpi_hid[ACPI_ID_LEN]);

#अन्यथा

अटल अंतरभूत पूर्णांक snd_पूर्णांकel_dsp_driver_probe(काष्ठा pci_dev *pci)
अणु
	वापस SND_INTEL_DSP_DRIVER_ANY;
पूर्ण

अटल अंतरभूत
पूर्णांक snd_पूर्णांकel_acpi_dsp_driver_probe(काष्ठा device *dev, स्थिर u8 acpi_hid[ACPI_ID_LEN])
अणु
	वापस SND_INTEL_DSP_DRIVER_ANY;
पूर्ण

#पूर्ण_अगर

#पूर्ण_अगर
