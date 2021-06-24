<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * soc-पूर्णांकel-quirks.h - prototypes क्रम quirk स्वतःdetection
 *
 * Copyright (c) 2019, Intel Corporation.
 *
 */

#अगर_अघोषित _SND_SOC_INTEL_QUIRKS_H
#घोषणा _SND_SOC_INTEL_QUIRKS_H

#अगर IS_ENABLED(CONFIG_X86)

#समावेश <linux/dmi.h>
#समावेश <यंत्र/cpu_device_id.h>
#समावेश <यंत्र/पूर्णांकel-family.h>
#समावेश <यंत्र/iosf_mbi.h>

#घोषणा SOC_INTEL_IS_CPU(soc, type)				\
अटल अंतरभूत bool soc_पूर्णांकel_is_##soc(व्योम)			\
अणु								\
	अटल स्थिर काष्ठा x86_cpu_id soc##_cpu_ids[] = अणु	\
		X86_MATCH_INTEL_FAM6_MODEL(type, शून्य),		\
		अणुपूर्ण						\
	पूर्ण;							\
	स्थिर काष्ठा x86_cpu_id *id;				\
								\
	id = x86_match_cpu(soc##_cpu_ids);			\
	अगर (id)							\
		वापस true;					\
	वापस false;						\
पूर्ण

SOC_INTEL_IS_CPU(byt, ATOM_SILVERMONT);
SOC_INTEL_IS_CPU(cht, ATOM_AIRMONT);
SOC_INTEL_IS_CPU(apl, ATOM_GOLDMONT);
SOC_INTEL_IS_CPU(glk, ATOM_GOLDMONT_PLUS);
SOC_INTEL_IS_CPU(cml, KABYLAKE_L);

अटल अंतरभूत bool soc_पूर्णांकel_is_byt_cr(काष्ठा platक्रमm_device *pdev)
अणु
	/*
	 * List of प्रणालीs which:
	 * 1. Use a non CR version of the Bay Trail SoC
	 * 2. Contain at least 6 पूर्णांकerrupt resources so that the
	 *    platक्रमm_get_resource(pdev, IORESOURCE_IRQ, 5) check below
	 *    succeeds
	 * 3. Despite 1. and 2. still have their IPC IRQ at index 0 rather then 5
	 *
	 * This needs to be here so that it can be shared between the SST and
	 * SOF drivers. We rely on the compiler to optimize this out in files
	 * where soc_पूर्णांकel_is_byt_cr is not used.
	 */
	अटल स्थिर काष्ठा dmi_प्रणाली_id क्रमce_bytcr_table[] = अणु
		अणु	/* Lenovo Yoga Tablet 2 series */
			.matches = अणु
				DMI_MATCH(DMI_SYS_VENDOR, "LENOVO"),
				DMI_MATCH(DMI_PRODUCT_FAMILY, "YOGATablet2"),
			पूर्ण,
		पूर्ण,
		अणुपूर्ण
	पूर्ण;
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक status = 0;

	अगर (!soc_पूर्णांकel_is_byt())
		वापस false;

	अगर (dmi_check_प्रणाली(क्रमce_bytcr_table))
		वापस true;

	अगर (iosf_mbi_available()) अणु
		u32 bios_status;

		status = iosf_mbi_पढ़ो(BT_MBI_UNIT_PMC, /* 0x04 PUNIT */
				       MBI_REG_READ, /* 0x10 */
				       0x006, /* BIOS_CONFIG */
				       &bios_status);

		अगर (status) अणु
			dev_err(dev, "could not read PUNIT BIOS_CONFIG\n");
		पूर्ण अन्यथा अणु
			/* bits 26:27 mirror PMIC options */
			bios_status = (bios_status >> 26) & 3;

			अगर (bios_status == 1 || bios_status == 3) अणु
				dev_info(dev, "Detected Baytrail-CR platform\n");
				वापस true;
			पूर्ण

			dev_info(dev, "BYT-CR not detected\n");
		पूर्ण
	पूर्ण अन्यथा अणु
		dev_info(dev, "IOSF_MBI not available, no BYT-CR detection\n");
	पूर्ण

	अगर (!platक्रमm_get_resource(pdev, IORESOURCE_IRQ, 5)) अणु
		/*
		 * Some devices detected as BYT-T have only a single IRQ listed,
		 * causing platक्रमm_get_irq with index 5 to वापस -ENXIO.
		 * The correct IRQ in this हाल is at index 0, as on BYT-CR.
		 */
		dev_info(dev, "Falling back to Baytrail-CR platform\n");
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

#अन्यथा

अटल अंतरभूत bool soc_पूर्णांकel_is_byt_cr(काष्ठा platक्रमm_device *pdev)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत bool soc_पूर्णांकel_is_byt(व्योम)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत bool soc_पूर्णांकel_is_cht(व्योम)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत bool soc_पूर्णांकel_is_apl(व्योम)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत bool soc_पूर्णांकel_is_glk(व्योम)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत bool soc_पूर्णांकel_is_cml(व्योम)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर

 #पूर्ण_अगर /* _SND_SOC_INTEL_QUIRKS_H */
