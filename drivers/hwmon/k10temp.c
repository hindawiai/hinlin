<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * k10temp.c - AMD Family 10h/11h/12h/14h/15h/16h/17h
 *		processor hardware monitoring
 *
 * Copyright (c) 2009 Clemens Ladisch <clemens@ladisch.de>
 * Copyright (c) 2020 Guenter Roeck <linux@roeck-us.net>
 *
 * Implementation notes:
 * - CCD रेजिस्टर address inक्रमmation as well as the calculation to
 *   convert raw रेजिस्टर values is from https://github.com/ocerman/zenघातer.
 *   The inक्रमmation is not confirmed from chip datasheets, but experiments
 *   suggest that it provides reasonable temperature values.
 */

#समावेश <linux/bitops.h>
#समावेश <linux/err.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/pci_ids.h>
#समावेश <यंत्र/amd_nb.h>
#समावेश <यंत्र/processor.h>

MODULE_DESCRIPTION("AMD Family 10h+ CPU core temperature monitor");
MODULE_AUTHOR("Clemens Ladisch <clemens@ladisch.de>");
MODULE_LICENSE("GPL");

अटल bool क्रमce;
module_param(क्रमce, bool, 0444);
MODULE_PARM_DESC(क्रमce, "force loading on processors with erratum 319");

/* Provide lock क्रम writing to NB_SMU_IND_ADDR */
अटल DEFINE_MUTEX(nb_smu_ind_mutex);

#अगर_अघोषित PCI_DEVICE_ID_AMD_15H_M70H_NB_F3
#घोषणा PCI_DEVICE_ID_AMD_15H_M70H_NB_F3	0x15b3
#पूर्ण_अगर

/* CPUID function 0x80000001, ebx */
#घोषणा CPUID_PKGTYPE_MASK	GENMASK(31, 28)
#घोषणा CPUID_PKGTYPE_F		0x00000000
#घोषणा CPUID_PKGTYPE_AM2R2_AM3	0x10000000

/* DRAM controller (PCI function 2) */
#घोषणा REG_DCT0_CONFIG_HIGH		0x094
#घोषणा  DDR3_MODE			BIT(8)

/* miscellaneous (PCI function 3) */
#घोषणा REG_HARDWARE_THERMAL_CONTROL	0x64
#घोषणा  HTC_ENABLE			BIT(0)

#घोषणा REG_REPORTED_TEMPERATURE	0xa4

#घोषणा REG_NORTHBRIDGE_CAPABILITIES	0xe8
#घोषणा  NB_CAP_HTC			BIT(10)

/*
 * For F15h M60h and M70h, REG_HARDWARE_THERMAL_CONTROL
 * and REG_REPORTED_TEMPERATURE have been moved to
 * D0F0xBC_xD820_0C64 [Hardware Temperature Control]
 * D0F0xBC_xD820_0CA4 [Reported Temperature Control]
 */
#घोषणा F15H_M60H_HARDWARE_TEMP_CTRL_OFFSET	0xd8200c64
#घोषणा F15H_M60H_REPORTED_TEMP_CTRL_OFFSET	0xd8200ca4

/* Common क्रम Zen CPU families (Family 17h and 18h) */
#घोषणा ZEN_REPORTED_TEMP_CTRL_OFFSET		0x00059800

#घोषणा ZEN_CCD_TEMP(x)				(0x00059954 + ((x) * 4))
#घोषणा ZEN_CCD_TEMP_VALID			BIT(11)
#घोषणा ZEN_CCD_TEMP_MASK			GENMASK(10, 0)

#घोषणा ZEN_CUR_TEMP_SHIFT			21
#घोषणा ZEN_CUR_TEMP_RANGE_SEL_MASK		BIT(19)

#घोषणा ZEN_SVI_BASE				0x0005A000

/* F17h thermal रेजिस्टरs through SMN */
#घोषणा F17H_M01H_SVI_TEL_PLANE0		(ZEN_SVI_BASE + 0xc)
#घोषणा F17H_M01H_SVI_TEL_PLANE1		(ZEN_SVI_BASE + 0x10)
#घोषणा F17H_M31H_SVI_TEL_PLANE0		(ZEN_SVI_BASE + 0x14)
#घोषणा F17H_M31H_SVI_TEL_PLANE1		(ZEN_SVI_BASE + 0x10)

#घोषणा F17H_M01H_CFACTOR_ICORE			1000000	/* 1A / LSB	*/
#घोषणा F17H_M01H_CFACTOR_ISOC			250000	/* 0.25A / LSB	*/
#घोषणा F17H_M31H_CFACTOR_ICORE			1000000	/* 1A / LSB	*/
#घोषणा F17H_M31H_CFACTOR_ISOC			310000	/* 0.31A / LSB	*/

/* F19h thermal रेजिस्टरs through SMN */
#घोषणा F19H_M01_SVI_TEL_PLANE0			(ZEN_SVI_BASE + 0x14)
#घोषणा F19H_M01_SVI_TEL_PLANE1			(ZEN_SVI_BASE + 0x10)

#घोषणा F19H_M01H_CFACTOR_ICORE			1000000	/* 1A / LSB	*/
#घोषणा F19H_M01H_CFACTOR_ISOC			310000	/* 0.31A / LSB	*/

काष्ठा k10temp_data अणु
	काष्ठा pci_dev *pdev;
	व्योम (*पढ़ो_htcreg)(काष्ठा pci_dev *pdev, u32 *regval);
	व्योम (*पढ़ो_tempreg)(काष्ठा pci_dev *pdev, u32 *regval);
	पूर्णांक temp_offset;
	u32 temp_adjust_mask;
	u32 show_temp;
	bool is_zen;
पूर्ण;

#घोषणा TCTL_BIT	0
#घोषणा TDIE_BIT	1
#घोषणा TCCD_BIT(x)	((x) + 2)

#घोषणा HAVE_TEMP(d, channel)	((d)->show_temp & BIT(channel))
#घोषणा HAVE_TDIE(d)		HAVE_TEMP(d, TDIE_BIT)

काष्ठा tctl_offset अणु
	u8 model;
	अक्षर स्थिर *id;
	पूर्णांक offset;
पूर्ण;

अटल स्थिर काष्ठा tctl_offset tctl_offset_table[] = अणु
	अणु 0x17, "AMD Ryzen 5 1600X", 20000 पूर्ण,
	अणु 0x17, "AMD Ryzen 7 1700X", 20000 पूर्ण,
	अणु 0x17, "AMD Ryzen 7 1800X", 20000 पूर्ण,
	अणु 0x17, "AMD Ryzen 7 2700X", 10000 पूर्ण,
	अणु 0x17, "AMD Ryzen Threadripper 19", 27000 पूर्ण, /* 19अणु00,20,50पूर्णX */
	अणु 0x17, "AMD Ryzen Threadripper 29", 27000 पूर्ण, /* 29अणु20,50,70,90पूर्ण[W]X */
पूर्ण;

अटल व्योम पढ़ो_htcreg_pci(काष्ठा pci_dev *pdev, u32 *regval)
अणु
	pci_पढ़ो_config_dword(pdev, REG_HARDWARE_THERMAL_CONTROL, regval);
पूर्ण

अटल व्योम पढ़ो_tempreg_pci(काष्ठा pci_dev *pdev, u32 *regval)
अणु
	pci_पढ़ो_config_dword(pdev, REG_REPORTED_TEMPERATURE, regval);
पूर्ण

अटल व्योम amd_nb_index_पढ़ो(काष्ठा pci_dev *pdev, अचिन्हित पूर्णांक devfn,
			      अचिन्हित पूर्णांक base, पूर्णांक offset, u32 *val)
अणु
	mutex_lock(&nb_smu_ind_mutex);
	pci_bus_ग_लिखो_config_dword(pdev->bus, devfn,
				   base, offset);
	pci_bus_पढ़ो_config_dword(pdev->bus, devfn,
				  base + 4, val);
	mutex_unlock(&nb_smu_ind_mutex);
पूर्ण

अटल व्योम पढ़ो_htcreg_nb_f15(काष्ठा pci_dev *pdev, u32 *regval)
अणु
	amd_nb_index_पढ़ो(pdev, PCI_DEVFN(0, 0), 0xb8,
			  F15H_M60H_HARDWARE_TEMP_CTRL_OFFSET, regval);
पूर्ण

अटल व्योम पढ़ो_tempreg_nb_f15(काष्ठा pci_dev *pdev, u32 *regval)
अणु
	amd_nb_index_पढ़ो(pdev, PCI_DEVFN(0, 0), 0xb8,
			  F15H_M60H_REPORTED_TEMP_CTRL_OFFSET, regval);
पूर्ण

अटल व्योम पढ़ो_tempreg_nb_zen(काष्ठा pci_dev *pdev, u32 *regval)
अणु
	amd_smn_पढ़ो(amd_pci_dev_to_node_id(pdev),
		     ZEN_REPORTED_TEMP_CTRL_OFFSET, regval);
पूर्ण

अटल दीर्घ get_raw_temp(काष्ठा k10temp_data *data)
अणु
	u32 regval;
	दीर्घ temp;

	data->पढ़ो_tempreg(data->pdev, &regval);
	temp = (regval >> ZEN_CUR_TEMP_SHIFT) * 125;
	अगर (regval & data->temp_adjust_mask)
		temp -= 49000;
	वापस temp;
पूर्ण

अटल स्थिर अक्षर *k10temp_temp_label[] = अणु
	"Tctl",
	"Tdie",
	"Tccd1",
	"Tccd2",
	"Tccd3",
	"Tccd4",
	"Tccd5",
	"Tccd6",
	"Tccd7",
	"Tccd8",
पूर्ण;

अटल पूर्णांक k10temp_पढ़ो_labels(काष्ठा device *dev,
			       क्रमागत hwmon_sensor_types type,
			       u32 attr, पूर्णांक channel, स्थिर अक्षर **str)
अणु
	चयन (type) अणु
	हाल hwmon_temp:
		*str = k10temp_temp_label[channel];
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक k10temp_पढ़ो_temp(काष्ठा device *dev, u32 attr, पूर्णांक channel,
			     दीर्घ *val)
अणु
	काष्ठा k10temp_data *data = dev_get_drvdata(dev);
	u32 regval;

	चयन (attr) अणु
	हाल hwmon_temp_input:
		चयन (channel) अणु
		हाल 0:		/* Tctl */
			*val = get_raw_temp(data);
			अगर (*val < 0)
				*val = 0;
			अवरोध;
		हाल 1:		/* Tdie */
			*val = get_raw_temp(data) - data->temp_offset;
			अगर (*val < 0)
				*val = 0;
			अवरोध;
		हाल 2 ... 9:		/* Tccdअणु1-8पूर्ण */
			amd_smn_पढ़ो(amd_pci_dev_to_node_id(data->pdev),
				     ZEN_CCD_TEMP(channel - 2), &regval);
			*val = (regval & ZEN_CCD_TEMP_MASK) * 125 - 49000;
			अवरोध;
		शेष:
			वापस -EOPNOTSUPP;
		पूर्ण
		अवरोध;
	हाल hwmon_temp_max:
		*val = 70 * 1000;
		अवरोध;
	हाल hwmon_temp_crit:
		data->पढ़ो_htcreg(data->pdev, &regval);
		*val = ((regval >> 16) & 0x7f) * 500 + 52000;
		अवरोध;
	हाल hwmon_temp_crit_hyst:
		data->पढ़ो_htcreg(data->pdev, &regval);
		*val = (((regval >> 16) & 0x7f)
			- ((regval >> 24) & 0xf)) * 500 + 52000;
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक k10temp_पढ़ो(काष्ठा device *dev, क्रमागत hwmon_sensor_types type,
			u32 attr, पूर्णांक channel, दीर्घ *val)
अणु
	चयन (type) अणु
	हाल hwmon_temp:
		वापस k10temp_पढ़ो_temp(dev, attr, channel, val);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल umode_t k10temp_is_visible(स्थिर व्योम *_data,
				  क्रमागत hwmon_sensor_types type,
				  u32 attr, पूर्णांक channel)
अणु
	स्थिर काष्ठा k10temp_data *data = _data;
	काष्ठा pci_dev *pdev = data->pdev;
	u32 reg;

	चयन (type) अणु
	हाल hwmon_temp:
		चयन (attr) अणु
		हाल hwmon_temp_input:
			अगर (!HAVE_TEMP(data, channel))
				वापस 0;
			अवरोध;
		हाल hwmon_temp_max:
			अगर (channel || data->is_zen)
				वापस 0;
			अवरोध;
		हाल hwmon_temp_crit:
		हाल hwmon_temp_crit_hyst:
			अगर (channel || !data->पढ़ो_htcreg)
				वापस 0;

			pci_पढ़ो_config_dword(pdev,
					      REG_NORTHBRIDGE_CAPABILITIES,
					      &reg);
			अगर (!(reg & NB_CAP_HTC))
				वापस 0;

			data->पढ़ो_htcreg(data->pdev, &reg);
			अगर (!(reg & HTC_ENABLE))
				वापस 0;
			अवरोध;
		हाल hwmon_temp_label:
			/* Show temperature labels only on Zen CPUs */
			अगर (!data->is_zen || !HAVE_TEMP(data, channel))
				वापस 0;
			अवरोध;
		शेष:
			वापस 0;
		पूर्ण
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण
	वापस 0444;
पूर्ण

अटल bool has_erratum_319(काष्ठा pci_dev *pdev)
अणु
	u32 pkg_type, reg_dram_cfg;

	अगर (boot_cpu_data.x86 != 0x10)
		वापस false;

	/*
	 * Erratum 319: The thermal sensor of Socket F/AM2+ processors
	 *              may be unreliable.
	 */
	pkg_type = cpuid_ebx(0x80000001) & CPUID_PKGTYPE_MASK;
	अगर (pkg_type == CPUID_PKGTYPE_F)
		वापस true;
	अगर (pkg_type != CPUID_PKGTYPE_AM2R2_AM3)
		वापस false;

	/* DDR3 memory implies socket AM3, which is good */
	pci_bus_पढ़ो_config_dword(pdev->bus,
				  PCI_DEVFN(PCI_SLOT(pdev->devfn), 2),
				  REG_DCT0_CONFIG_HIGH, &reg_dram_cfg);
	अगर (reg_dram_cfg & DDR3_MODE)
		वापस false;

	/*
	 * Unक्रमtunately it is possible to run a socket AM3 CPU with DDR2
	 * memory. We blacklist all the cores which करो exist in socket AM2+
	 * क्रमmat. It still isn't perfect, as RB-C2 cores exist in both AM2+
	 * and AM3 क्रमmats, but that's the best we can करो.
	 */
	वापस boot_cpu_data.x86_model < 4 ||
	       (boot_cpu_data.x86_model == 4 && boot_cpu_data.x86_stepping <= 2);
पूर्ण

अटल स्थिर काष्ठा hwmon_channel_info *k10temp_info[] = अणु
	HWMON_CHANNEL_INFO(temp,
			   HWMON_T_INPUT | HWMON_T_MAX |
			   HWMON_T_CRIT | HWMON_T_CRIT_HYST |
			   HWMON_T_LABEL,
			   HWMON_T_INPUT | HWMON_T_LABEL,
			   HWMON_T_INPUT | HWMON_T_LABEL,
			   HWMON_T_INPUT | HWMON_T_LABEL,
			   HWMON_T_INPUT | HWMON_T_LABEL,
			   HWMON_T_INPUT | HWMON_T_LABEL,
			   HWMON_T_INPUT | HWMON_T_LABEL,
			   HWMON_T_INPUT | HWMON_T_LABEL,
			   HWMON_T_INPUT | HWMON_T_LABEL,
			   HWMON_T_INPUT | HWMON_T_LABEL),
	HWMON_CHANNEL_INFO(in,
			   HWMON_I_INPUT | HWMON_I_LABEL,
			   HWMON_I_INPUT | HWMON_I_LABEL),
	HWMON_CHANNEL_INFO(curr,
			   HWMON_C_INPUT | HWMON_C_LABEL,
			   HWMON_C_INPUT | HWMON_C_LABEL),
	शून्य
पूर्ण;

अटल स्थिर काष्ठा hwmon_ops k10temp_hwmon_ops = अणु
	.is_visible = k10temp_is_visible,
	.पढ़ो = k10temp_पढ़ो,
	.पढ़ो_string = k10temp_पढ़ो_labels,
पूर्ण;

अटल स्थिर काष्ठा hwmon_chip_info k10temp_chip_info = अणु
	.ops = &k10temp_hwmon_ops,
	.info = k10temp_info,
पूर्ण;

अटल व्योम k10temp_get_ccd_support(काष्ठा pci_dev *pdev,
				    काष्ठा k10temp_data *data, पूर्णांक limit)
अणु
	u32 regval;
	पूर्णांक i;

	क्रम (i = 0; i < limit; i++) अणु
		amd_smn_पढ़ो(amd_pci_dev_to_node_id(pdev),
			     ZEN_CCD_TEMP(i), &regval);
		अगर (regval & ZEN_CCD_TEMP_VALID)
			data->show_temp |= BIT(TCCD_BIT(i));
	पूर्ण
पूर्ण

अटल पूर्णांक k10temp_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *id)
अणु
	पूर्णांक unreliable = has_erratum_319(pdev);
	काष्ठा device *dev = &pdev->dev;
	काष्ठा k10temp_data *data;
	काष्ठा device *hwmon_dev;
	पूर्णांक i;

	अगर (unreliable) अणु
		अगर (!क्रमce) अणु
			dev_err(dev,
				"unreliable CPU thermal sensor; monitoring disabled\n");
			वापस -ENODEV;
		पूर्ण
		dev_warn(dev,
			 "unreliable CPU thermal sensor; check erratum 319\n");
	पूर्ण

	data = devm_kzalloc(dev, माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->pdev = pdev;
	data->show_temp |= BIT(TCTL_BIT);	/* Always show Tctl */

	अगर (boot_cpu_data.x86 == 0x15 &&
	    ((boot_cpu_data.x86_model & 0xf0) == 0x60 ||
	     (boot_cpu_data.x86_model & 0xf0) == 0x70)) अणु
		data->पढ़ो_htcreg = पढ़ो_htcreg_nb_f15;
		data->पढ़ो_tempreg = पढ़ो_tempreg_nb_f15;
	पूर्ण अन्यथा अगर (boot_cpu_data.x86 == 0x17 || boot_cpu_data.x86 == 0x18) अणु
		data->temp_adjust_mask = ZEN_CUR_TEMP_RANGE_SEL_MASK;
		data->पढ़ो_tempreg = पढ़ो_tempreg_nb_zen;
		data->show_temp |= BIT(TDIE_BIT);	/* show Tdie */
		data->is_zen = true;

		चयन (boot_cpu_data.x86_model) अणु
		हाल 0x1:	/* Zen */
		हाल 0x8:	/* Zen+ */
		हाल 0x11:	/* Zen APU */
		हाल 0x18:	/* Zen+ APU */
			k10temp_get_ccd_support(pdev, data, 4);
			अवरोध;
		हाल 0x31:	/* Zen2 Thपढ़ोripper */
		हाल 0x71:	/* Zen2 */
			k10temp_get_ccd_support(pdev, data, 8);
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अगर (boot_cpu_data.x86 == 0x19) अणु
		data->temp_adjust_mask = ZEN_CUR_TEMP_RANGE_SEL_MASK;
		data->पढ़ो_tempreg = पढ़ो_tempreg_nb_zen;
		data->show_temp |= BIT(TDIE_BIT);
		data->is_zen = true;

		चयन (boot_cpu_data.x86_model) अणु
		हाल 0x0 ... 0x1:	/* Zen3 SP3/TR */
		हाल 0x21:		/* Zen3 Ryzen Desktop */
			k10temp_get_ccd_support(pdev, data, 8);
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		data->पढ़ो_htcreg = पढ़ो_htcreg_pci;
		data->पढ़ो_tempreg = पढ़ो_tempreg_pci;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(tctl_offset_table); i++) अणु
		स्थिर काष्ठा tctl_offset *entry = &tctl_offset_table[i];

		अगर (boot_cpu_data.x86 == entry->model &&
		    म_माला(boot_cpu_data.x86_model_id, entry->id)) अणु
			data->temp_offset = entry->offset;
			अवरोध;
		पूर्ण
	पूर्ण

	hwmon_dev = devm_hwmon_device_रेजिस्टर_with_info(dev, "k10temp", data,
							 &k10temp_chip_info,
							 शून्य);
	वापस PTR_ERR_OR_ZERO(hwmon_dev);
पूर्ण

अटल स्थिर काष्ठा pci_device_id k10temp_id_table[] = अणु
	अणु PCI_VDEVICE(AMD, PCI_DEVICE_ID_AMD_10H_NB_MISC) पूर्ण,
	अणु PCI_VDEVICE(AMD, PCI_DEVICE_ID_AMD_11H_NB_MISC) पूर्ण,
	अणु PCI_VDEVICE(AMD, PCI_DEVICE_ID_AMD_CNB17H_F3) पूर्ण,
	अणु PCI_VDEVICE(AMD, PCI_DEVICE_ID_AMD_15H_NB_F3) पूर्ण,
	अणु PCI_VDEVICE(AMD, PCI_DEVICE_ID_AMD_15H_M10H_F3) पूर्ण,
	अणु PCI_VDEVICE(AMD, PCI_DEVICE_ID_AMD_15H_M30H_NB_F3) पूर्ण,
	अणु PCI_VDEVICE(AMD, PCI_DEVICE_ID_AMD_15H_M60H_NB_F3) पूर्ण,
	अणु PCI_VDEVICE(AMD, PCI_DEVICE_ID_AMD_15H_M70H_NB_F3) पूर्ण,
	अणु PCI_VDEVICE(AMD, PCI_DEVICE_ID_AMD_16H_NB_F3) पूर्ण,
	अणु PCI_VDEVICE(AMD, PCI_DEVICE_ID_AMD_16H_M30H_NB_F3) पूर्ण,
	अणु PCI_VDEVICE(AMD, PCI_DEVICE_ID_AMD_17H_DF_F3) पूर्ण,
	अणु PCI_VDEVICE(AMD, PCI_DEVICE_ID_AMD_17H_M10H_DF_F3) पूर्ण,
	अणु PCI_VDEVICE(AMD, PCI_DEVICE_ID_AMD_17H_M30H_DF_F3) पूर्ण,
	अणु PCI_VDEVICE(AMD, PCI_DEVICE_ID_AMD_17H_M60H_DF_F3) पूर्ण,
	अणु PCI_VDEVICE(AMD, PCI_DEVICE_ID_AMD_17H_M70H_DF_F3) पूर्ण,
	अणु PCI_VDEVICE(AMD, PCI_DEVICE_ID_AMD_19H_DF_F3) पूर्ण,
	अणु PCI_VDEVICE(HYGON, PCI_DEVICE_ID_AMD_17H_DF_F3) पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, k10temp_id_table);

अटल काष्ठा pci_driver k10temp_driver = अणु
	.name = "k10temp",
	.id_table = k10temp_id_table,
	.probe = k10temp_probe,
पूर्ण;

module_pci_driver(k10temp_driver);
