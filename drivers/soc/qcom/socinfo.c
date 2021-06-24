<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2009-2017, The Linux Foundation. All rights reserved.
 * Copyright (c) 2017-2019, Linaro Ltd.
 */

#समावेश <linux/debugfs.h>
#समावेश <linux/err.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/slab.h>
#समावेश <linux/soc/qcom/sस्मृति.स>
#समावेश <linux/माला.स>
#समावेश <linux/sys_soc.h>
#समावेश <linux/types.h>

#समावेश <यंत्र/unaligned.h>

/*
 * SoC version type with major number in the upper 16 bits and minor
 * number in the lower 16 bits.
 */
#घोषणा SOCINFO_MAJOR(ver) (((ver) >> 16) & 0xffff)
#घोषणा SOCINFO_MINOR(ver) ((ver) & 0xffff)
#घोषणा SOCINFO_VERSION(maj, min)  ((((maj) & 0xffff) << 16)|((min) & 0xffff))

#घोषणा SMEM_SOCINFO_BUILD_ID_LENGTH           32
#घोषणा SMEM_SOCINFO_CHIP_ID_LENGTH            32

/*
 * SMEM item id, used to acquire handles to respective
 * SMEM region.
 */
#घोषणा SMEM_HW_SW_BUILD_ID            137

#अगर_घोषित CONFIG_DEBUG_FS
#घोषणा SMEM_IMAGE_VERSION_BLOCKS_COUNT        32
#घोषणा SMEM_IMAGE_VERSION_SIZE                4096
#घोषणा SMEM_IMAGE_VERSION_NAME_SIZE           75
#घोषणा SMEM_IMAGE_VERSION_VARIANT_SIZE        20
#घोषणा SMEM_IMAGE_VERSION_OEM_SIZE            32

/*
 * SMEM Image table indices
 */
#घोषणा SMEM_IMAGE_TABLE_BOOT_INDEX     0
#घोषणा SMEM_IMAGE_TABLE_TZ_INDEX       1
#घोषणा SMEM_IMAGE_TABLE_RPM_INDEX      3
#घोषणा SMEM_IMAGE_TABLE_APPS_INDEX     10
#घोषणा SMEM_IMAGE_TABLE_MPSS_INDEX     11
#घोषणा SMEM_IMAGE_TABLE_ADSP_INDEX     12
#घोषणा SMEM_IMAGE_TABLE_CNSS_INDEX     13
#घोषणा SMEM_IMAGE_TABLE_VIDEO_INDEX    14
#घोषणा SMEM_IMAGE_VERSION_TABLE       469

/*
 * SMEM Image table names
 */
अटल स्थिर अक्षर *स्थिर socinfo_image_names[] = अणु
	[SMEM_IMAGE_TABLE_ADSP_INDEX] = "adsp",
	[SMEM_IMAGE_TABLE_APPS_INDEX] = "apps",
	[SMEM_IMAGE_TABLE_BOOT_INDEX] = "boot",
	[SMEM_IMAGE_TABLE_CNSS_INDEX] = "cnss",
	[SMEM_IMAGE_TABLE_MPSS_INDEX] = "mpss",
	[SMEM_IMAGE_TABLE_RPM_INDEX] = "rpm",
	[SMEM_IMAGE_TABLE_TZ_INDEX] = "tz",
	[SMEM_IMAGE_TABLE_VIDEO_INDEX] = "video",
पूर्ण;

अटल स्थिर अक्षर *स्थिर pmic_models[] = अणु
	[0]  = "Unknown PMIC model",
	[9]  = "PM8994",
	[11] = "PM8916",
	[13] = "PM8058",
	[14] = "PM8028",
	[15] = "PM8901",
	[16] = "PM8027",
	[17] = "ISL9519",
	[18] = "PM8921",
	[19] = "PM8018",
	[20] = "PM8015",
	[21] = "PM8014",
	[22] = "PM8821",
	[23] = "PM8038",
	[24] = "PM8922",
	[25] = "PM8917",
	[30] = "PM8150",
	[31] = "PM8150L",
	[32] = "PM8150B",
	[33] = "PMK8002",
	[36] = "PM8009",
पूर्ण;
#पूर्ण_अगर /* CONFIG_DEBUG_FS */

/* Socinfo SMEM item काष्ठाure */
काष्ठा socinfo अणु
	__le32 fmt;
	__le32 id;
	__le32 ver;
	अक्षर build_id[SMEM_SOCINFO_BUILD_ID_LENGTH];
	/* Version 2 */
	__le32 raw_id;
	__le32 raw_ver;
	/* Version 3 */
	__le32 hw_plat;
	/* Version 4 */
	__le32 plat_ver;
	/* Version 5 */
	__le32 accessory_chip;
	/* Version 6 */
	__le32 hw_plat_subtype;
	/* Version 7 */
	__le32 pmic_model;
	__le32 pmic_die_rev;
	/* Version 8 */
	__le32 pmic_model_1;
	__le32 pmic_die_rev_1;
	__le32 pmic_model_2;
	__le32 pmic_die_rev_2;
	/* Version 9 */
	__le32 foundry_id;
	/* Version 10 */
	__le32 serial_num;
	/* Version 11 */
	__le32 num_pmics;
	__le32 pmic_array_offset;
	/* Version 12 */
	__le32 chip_family;
	__le32 raw_device_family;
	__le32 raw_device_num;
	/* Version 13 */
	__le32 nproduct_id;
	अक्षर chip_id[SMEM_SOCINFO_CHIP_ID_LENGTH];
	/* Version 14 */
	__le32 num_clusters;
	__le32 ncluster_array_offset;
	__le32 num_defective_parts;
	__le32 ndefective_parts_array_offset;
	/* Version 15 */
	__le32 nmodem_supported;
पूर्ण;

#अगर_घोषित CONFIG_DEBUG_FS
काष्ठा socinfo_params अणु
	u32 raw_device_family;
	u32 hw_plat_subtype;
	u32 accessory_chip;
	u32 raw_device_num;
	u32 chip_family;
	u32 foundry_id;
	u32 plat_ver;
	u32 raw_ver;
	u32 hw_plat;
	u32 fmt;
	u32 nproduct_id;
	u32 num_clusters;
	u32 ncluster_array_offset;
	u32 num_defective_parts;
	u32 ndefective_parts_array_offset;
	u32 nmodem_supported;
पूर्ण;

काष्ठा smem_image_version अणु
	अक्षर name[SMEM_IMAGE_VERSION_NAME_SIZE];
	अक्षर variant[SMEM_IMAGE_VERSION_VARIANT_SIZE];
	अक्षर pad;
	अक्षर oem[SMEM_IMAGE_VERSION_OEM_SIZE];
पूर्ण;
#पूर्ण_अगर /* CONFIG_DEBUG_FS */

काष्ठा qcom_socinfo अणु
	काष्ठा soc_device *soc_dev;
	काष्ठा soc_device_attribute attr;
#अगर_घोषित CONFIG_DEBUG_FS
	काष्ठा dentry *dbg_root;
	काष्ठा socinfo_params info;
#पूर्ण_अगर /* CONFIG_DEBUG_FS */
पूर्ण;

काष्ठा soc_id अणु
	अचिन्हित पूर्णांक id;
	स्थिर अक्षर *name;
पूर्ण;

अटल स्थिर काष्ठा soc_id soc_id[] = अणु
	अणु 87, "MSM8960" पूर्ण,
	अणु 109, "APQ8064" पूर्ण,
	अणु 122, "MSM8660A" पूर्ण,
	अणु 123, "MSM8260A" पूर्ण,
	अणु 124, "APQ8060A" पूर्ण,
	अणु 126, "MSM8974" पूर्ण,
	अणु 130, "MPQ8064" पूर्ण,
	अणु 138, "MSM8960AB" पूर्ण,
	अणु 139, "APQ8060AB" पूर्ण,
	अणु 140, "MSM8260AB" पूर्ण,
	अणु 141, "MSM8660AB" पूर्ण,
	अणु 178, "APQ8084" पूर्ण,
	अणु 184, "APQ8074" पूर्ण,
	अणु 185, "MSM8274" पूर्ण,
	अणु 186, "MSM8674" पूर्ण,
	अणु 194, "MSM8974PRO" पूर्ण,
	अणु 206, "MSM8916" पूर्ण,
	अणु 207, "MSM8994" पूर्ण,
	अणु 208, "APQ8074-AA" पूर्ण,
	अणु 209, "APQ8074-AB" पूर्ण,
	अणु 210, "APQ8074PRO" पूर्ण,
	अणु 211, "MSM8274-AA" पूर्ण,
	अणु 212, "MSM8274-AB" पूर्ण,
	अणु 213, "MSM8274PRO" पूर्ण,
	अणु 214, "MSM8674-AA" पूर्ण,
	अणु 215, "MSM8674-AB" पूर्ण,
	अणु 216, "MSM8674PRO" पूर्ण,
	अणु 217, "MSM8974-AA" पूर्ण,
	अणु 218, "MSM8974-AB" पूर्ण,
	अणु 233, "MSM8936" पूर्ण,
	अणु 239, "MSM8939" पूर्ण,
	अणु 240, "APQ8036" पूर्ण,
	अणु 241, "APQ8039" पूर्ण,
	अणु 246, "MSM8996" पूर्ण,
	अणु 247, "APQ8016" पूर्ण,
	अणु 248, "MSM8216" पूर्ण,
	अणु 249, "MSM8116" पूर्ण,
	अणु 250, "MSM8616" पूर्ण,
	अणु 251, "MSM8992" पूर्ण,
	अणु 253, "APQ8094" पूर्ण,
	अणु 290, "MDM9607" पूर्ण,
	अणु 291, "APQ8096" पूर्ण,
	अणु 292, "MSM8998" पूर्ण,
	अणु 293, "MSM8953" पूर्ण,
	अणु 296, "MDM8207" पूर्ण,
	अणु 297, "MDM9207" पूर्ण,
	अणु 298, "MDM9307" पूर्ण,
	अणु 299, "MDM9628" पूर्ण,
	अणु 304, "APQ8053" पूर्ण,
	अणु 305, "MSM8996SG" पूर्ण,
	अणु 310, "MSM8996AU" पूर्ण,
	अणु 311, "APQ8096AU" पूर्ण,
	अणु 312, "APQ8096SG" पूर्ण,
	अणु 317, "SDM660" पूर्ण,
	अणु 318, "SDM630" पूर्ण,
	अणु 319, "APQ8098" पूर्ण,
	अणु 321, "SDM845" पूर्ण,
	अणु 322, "MDM9206" पूर्ण,
	अणु 324, "SDA660" पूर्ण,
	अणु 325, "SDM658" पूर्ण,
	अणु 326, "SDA658" पूर्ण,
	अणु 327, "SDA630" पूर्ण,
	अणु 338, "SDM450" पूर्ण,
	अणु 341, "SDA845" पूर्ण,
	अणु 345, "SDM636" पूर्ण,
	अणु 346, "SDA636" पूर्ण,
	अणु 349, "SDM632" पूर्ण,
	अणु 350, "SDA632" पूर्ण,
	अणु 351, "SDA450" पूर्ण,
	अणु 356, "SM8250" पूर्ण,
	अणु 402, "IPQ6018" पूर्ण,
	अणु 425, "SC7180" पूर्ण,
	अणु 455, "QRB5165" पूर्ण,
पूर्ण;

अटल स्थिर अक्षर *socinfo_machine(काष्ठा device *dev, अचिन्हित पूर्णांक id)
अणु
	पूर्णांक idx;

	क्रम (idx = 0; idx < ARRAY_SIZE(soc_id); idx++) अणु
		अगर (soc_id[idx].id == id)
			वापस soc_id[idx].name;
	पूर्ण

	वापस शून्य;
पूर्ण

#अगर_घोषित CONFIG_DEBUG_FS

#घोषणा QCOM_OPEN(name, _func)						\
अटल पूर्णांक qcom_खोलो_##name(काष्ठा inode *inode, काष्ठा file *file)	\
अणु									\
	वापस single_खोलो(file, _func, inode->i_निजी);		\
पूर्ण									\
									\
अटल स्थिर काष्ठा file_operations qcom_ ##name## _ops = अणु		\
	.खोलो = qcom_खोलो_##name,					\
	.पढ़ो = seq_पढ़ो,						\
	.llseek = seq_lseek,						\
	.release = single_release,					\
पूर्ण

#घोषणा DEBUGFS_ADD(info, name)						\
	debugfs_create_file(__stringअगरy(name), 0444,			\
			    qcom_socinfo->dbg_root,			\
			    info, &qcom_ ##name## _ops)


अटल पूर्णांक qcom_show_build_id(काष्ठा seq_file *seq, व्योम *p)
अणु
	काष्ठा socinfo *socinfo = seq->निजी;

	seq_म_लिखो(seq, "%s\n", socinfo->build_id);

	वापस 0;
पूर्ण

अटल पूर्णांक qcom_show_pmic_model(काष्ठा seq_file *seq, व्योम *p)
अणु
	काष्ठा socinfo *socinfo = seq->निजी;
	पूर्णांक model = SOCINFO_MINOR(le32_to_cpu(socinfo->pmic_model));

	अगर (model < 0)
		वापस -EINVAL;

	अगर (model < ARRAY_SIZE(pmic_models) && pmic_models[model])
		seq_म_लिखो(seq, "%s\n", pmic_models[model]);
	अन्यथा
		seq_म_लिखो(seq, "unknown (%d)\n", model);

	वापस 0;
पूर्ण

अटल पूर्णांक qcom_show_pmic_model_array(काष्ठा seq_file *seq, व्योम *p)
अणु
	काष्ठा socinfo *socinfo = seq->निजी;
	अचिन्हित पूर्णांक num_pmics = le32_to_cpu(socinfo->num_pmics);
	अचिन्हित पूर्णांक pmic_array_offset = le32_to_cpu(socinfo->pmic_array_offset);
	पूर्णांक i;
	व्योम *ptr = socinfo;

	ptr += pmic_array_offset;

	/* No need क्रम bounds checking, it happened at socinfo_debugfs_init */
	क्रम (i = 0; i < num_pmics; i++) अणु
		अचिन्हित पूर्णांक model = SOCINFO_MINOR(get_unaligned_le32(ptr + 2 * i * माप(u32)));
		अचिन्हित पूर्णांक die_rev = get_unaligned_le32(ptr + (2 * i + 1) * माप(u32));

		अगर (model < ARRAY_SIZE(pmic_models) && pmic_models[model])
			seq_म_लिखो(seq, "%s %u.%u\n", pmic_models[model],
				   SOCINFO_MAJOR(die_rev),
				   SOCINFO_MINOR(die_rev));
		अन्यथा
			seq_म_लिखो(seq, "unknown (%d)\n", model);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक qcom_show_pmic_die_revision(काष्ठा seq_file *seq, व्योम *p)
अणु
	काष्ठा socinfo *socinfo = seq->निजी;

	seq_म_लिखो(seq, "%u.%u\n",
		   SOCINFO_MAJOR(le32_to_cpu(socinfo->pmic_die_rev)),
		   SOCINFO_MINOR(le32_to_cpu(socinfo->pmic_die_rev)));

	वापस 0;
पूर्ण

अटल पूर्णांक qcom_show_chip_id(काष्ठा seq_file *seq, व्योम *p)
अणु
	काष्ठा socinfo *socinfo = seq->निजी;

	seq_म_लिखो(seq, "%s\n", socinfo->chip_id);

	वापस 0;
पूर्ण

QCOM_OPEN(build_id, qcom_show_build_id);
QCOM_OPEN(pmic_model, qcom_show_pmic_model);
QCOM_OPEN(pmic_model_array, qcom_show_pmic_model_array);
QCOM_OPEN(pmic_die_rev, qcom_show_pmic_die_revision);
QCOM_OPEN(chip_id, qcom_show_chip_id);

#घोषणा DEFINE_IMAGE_OPS(type)					\
अटल पूर्णांक show_image_##type(काष्ठा seq_file *seq, व्योम *p)		  \
अणु								  \
	काष्ठा smem_image_version *image_version = seq->निजी;  \
	seq_माला_दो(seq, image_version->type);			  \
	seq_अ_दो(seq, '\n');					  \
	वापस 0;						  \
पूर्ण								  \
अटल पूर्णांक खोलो_image_##type(काष्ठा inode *inode, काष्ठा file *file)	  \
अणु									  \
	वापस single_खोलो(file, show_image_##type, inode->i_निजी); \
पूर्ण									  \
									  \
अटल स्थिर काष्ठा file_operations qcom_image_##type##_ops = अणु	  \
	.खोलो = खोलो_image_##type,					  \
	.पढ़ो = seq_पढ़ो,						  \
	.llseek = seq_lseek,						  \
	.release = single_release,					  \
पूर्ण

DEFINE_IMAGE_OPS(name);
DEFINE_IMAGE_OPS(variant);
DEFINE_IMAGE_OPS(oem);

अटल व्योम socinfo_debugfs_init(काष्ठा qcom_socinfo *qcom_socinfo,
				 काष्ठा socinfo *info, माप_प्रकार info_size)
अणु
	काष्ठा smem_image_version *versions;
	काष्ठा dentry *dentry;
	माप_प्रकार size;
	पूर्णांक i;
	अचिन्हित पूर्णांक num_pmics;
	अचिन्हित पूर्णांक pmic_array_offset;

	qcom_socinfo->dbg_root = debugfs_create_dir("qcom_socinfo", शून्य);

	qcom_socinfo->info.fmt = __le32_to_cpu(info->fmt);

	debugfs_create_x32("info_fmt", 0444, qcom_socinfo->dbg_root,
			   &qcom_socinfo->info.fmt);

	चयन (qcom_socinfo->info.fmt) अणु
	हाल SOCINFO_VERSION(0, 15):
		qcom_socinfo->info.nmodem_supported = __le32_to_cpu(info->nmodem_supported);

		debugfs_create_u32("nmodem_supported", 0444, qcom_socinfo->dbg_root,
				   &qcom_socinfo->info.nmodem_supported);
		fallthrough;
	हाल SOCINFO_VERSION(0, 14):
		qcom_socinfo->info.num_clusters = __le32_to_cpu(info->num_clusters);
		qcom_socinfo->info.ncluster_array_offset = __le32_to_cpu(info->ncluster_array_offset);
		qcom_socinfo->info.num_defective_parts = __le32_to_cpu(info->num_defective_parts);
		qcom_socinfo->info.ndefective_parts_array_offset = __le32_to_cpu(info->ndefective_parts_array_offset);

		debugfs_create_u32("num_clusters", 0444, qcom_socinfo->dbg_root,
				   &qcom_socinfo->info.num_clusters);
		debugfs_create_u32("ncluster_array_offset", 0444, qcom_socinfo->dbg_root,
				   &qcom_socinfo->info.ncluster_array_offset);
		debugfs_create_u32("num_defective_parts", 0444, qcom_socinfo->dbg_root,
				   &qcom_socinfo->info.num_defective_parts);
		debugfs_create_u32("ndefective_parts_array_offset", 0444, qcom_socinfo->dbg_root,
				   &qcom_socinfo->info.ndefective_parts_array_offset);
		fallthrough;
	हाल SOCINFO_VERSION(0, 13):
		qcom_socinfo->info.nproduct_id = __le32_to_cpu(info->nproduct_id);

		debugfs_create_u32("nproduct_id", 0444, qcom_socinfo->dbg_root,
				   &qcom_socinfo->info.nproduct_id);
		DEBUGFS_ADD(info, chip_id);
		fallthrough;
	हाल SOCINFO_VERSION(0, 12):
		qcom_socinfo->info.chip_family =
			__le32_to_cpu(info->chip_family);
		qcom_socinfo->info.raw_device_family =
			__le32_to_cpu(info->raw_device_family);
		qcom_socinfo->info.raw_device_num =
			__le32_to_cpu(info->raw_device_num);

		debugfs_create_x32("chip_family", 0444, qcom_socinfo->dbg_root,
				   &qcom_socinfo->info.chip_family);
		debugfs_create_x32("raw_device_family", 0444,
				   qcom_socinfo->dbg_root,
				   &qcom_socinfo->info.raw_device_family);
		debugfs_create_x32("raw_device_number", 0444,
				   qcom_socinfo->dbg_root,
				   &qcom_socinfo->info.raw_device_num);
		fallthrough;
	हाल SOCINFO_VERSION(0, 11):
		num_pmics = le32_to_cpu(info->num_pmics);
		pmic_array_offset = le32_to_cpu(info->pmic_array_offset);
		अगर (pmic_array_offset + 2 * num_pmics * माप(u32) <= info_size)
			DEBUGFS_ADD(info, pmic_model_array);
		fallthrough;
	हाल SOCINFO_VERSION(0, 10):
	हाल SOCINFO_VERSION(0, 9):
		qcom_socinfo->info.foundry_id = __le32_to_cpu(info->foundry_id);

		debugfs_create_u32("foundry_id", 0444, qcom_socinfo->dbg_root,
				   &qcom_socinfo->info.foundry_id);
		fallthrough;
	हाल SOCINFO_VERSION(0, 8):
	हाल SOCINFO_VERSION(0, 7):
		DEBUGFS_ADD(info, pmic_model);
		DEBUGFS_ADD(info, pmic_die_rev);
		fallthrough;
	हाल SOCINFO_VERSION(0, 6):
		qcom_socinfo->info.hw_plat_subtype =
			__le32_to_cpu(info->hw_plat_subtype);

		debugfs_create_u32("hardware_platform_subtype", 0444,
				   qcom_socinfo->dbg_root,
				   &qcom_socinfo->info.hw_plat_subtype);
		fallthrough;
	हाल SOCINFO_VERSION(0, 5):
		qcom_socinfo->info.accessory_chip =
			__le32_to_cpu(info->accessory_chip);

		debugfs_create_u32("accessory_chip", 0444,
				   qcom_socinfo->dbg_root,
				   &qcom_socinfo->info.accessory_chip);
		fallthrough;
	हाल SOCINFO_VERSION(0, 4):
		qcom_socinfo->info.plat_ver = __le32_to_cpu(info->plat_ver);

		debugfs_create_u32("platform_version", 0444,
				   qcom_socinfo->dbg_root,
				   &qcom_socinfo->info.plat_ver);
		fallthrough;
	हाल SOCINFO_VERSION(0, 3):
		qcom_socinfo->info.hw_plat = __le32_to_cpu(info->hw_plat);

		debugfs_create_u32("hardware_platform", 0444,
				   qcom_socinfo->dbg_root,
				   &qcom_socinfo->info.hw_plat);
		fallthrough;
	हाल SOCINFO_VERSION(0, 2):
		qcom_socinfo->info.raw_ver  = __le32_to_cpu(info->raw_ver);

		debugfs_create_u32("raw_version", 0444, qcom_socinfo->dbg_root,
				   &qcom_socinfo->info.raw_ver);
		fallthrough;
	हाल SOCINFO_VERSION(0, 1):
		DEBUGFS_ADD(info, build_id);
		अवरोध;
	पूर्ण

	versions = qcom_smem_get(QCOM_SMEM_HOST_ANY, SMEM_IMAGE_VERSION_TABLE,
				 &size);

	क्रम (i = 0; i < ARRAY_SIZE(socinfo_image_names); i++) अणु
		अगर (!socinfo_image_names[i])
			जारी;

		dentry = debugfs_create_dir(socinfo_image_names[i],
					    qcom_socinfo->dbg_root);
		debugfs_create_file("name", 0444, dentry, &versions[i],
				    &qcom_image_name_ops);
		debugfs_create_file("variant", 0444, dentry, &versions[i],
				    &qcom_image_variant_ops);
		debugfs_create_file("oem", 0444, dentry, &versions[i],
				    &qcom_image_oem_ops);
	पूर्ण
पूर्ण

अटल व्योम socinfo_debugfs_निकास(काष्ठा qcom_socinfo *qcom_socinfo)
अणु
	debugfs_हटाओ_recursive(qcom_socinfo->dbg_root);
पूर्ण
#अन्यथा
अटल व्योम socinfo_debugfs_init(काष्ठा qcom_socinfo *qcom_socinfo,
				 काष्ठा socinfo *info, माप_प्रकार info_size)
अणु
पूर्ण
अटल व्योम socinfo_debugfs_निकास(काष्ठा qcom_socinfo *qcom_socinfo) अणु  पूर्ण
#पूर्ण_अगर /* CONFIG_DEBUG_FS */

अटल पूर्णांक qcom_socinfo_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा qcom_socinfo *qs;
	काष्ठा socinfo *info;
	माप_प्रकार item_size;

	info = qcom_smem_get(QCOM_SMEM_HOST_ANY, SMEM_HW_SW_BUILD_ID,
			      &item_size);
	अगर (IS_ERR(info)) अणु
		dev_err(&pdev->dev, "Couldn't find socinfo\n");
		वापस PTR_ERR(info);
	पूर्ण

	qs = devm_kzalloc(&pdev->dev, माप(*qs), GFP_KERNEL);
	अगर (!qs)
		वापस -ENOMEM;

	qs->attr.family = "Snapdragon";
	qs->attr.machine = socinfo_machine(&pdev->dev,
					   le32_to_cpu(info->id));
	qs->attr.soc_id = devm_kaप्र_लिखो(&pdev->dev, GFP_KERNEL, "%u",
					 le32_to_cpu(info->id));
	qs->attr.revision = devm_kaप्र_लिखो(&pdev->dev, GFP_KERNEL, "%u.%u",
					   SOCINFO_MAJOR(le32_to_cpu(info->ver)),
					   SOCINFO_MINOR(le32_to_cpu(info->ver)));
	अगर (दुरत्व(काष्ठा socinfo, serial_num) <= item_size)
		qs->attr.serial_number = devm_kaप्र_लिखो(&pdev->dev, GFP_KERNEL,
							"%u",
							le32_to_cpu(info->serial_num));

	qs->soc_dev = soc_device_रेजिस्टर(&qs->attr);
	अगर (IS_ERR(qs->soc_dev))
		वापस PTR_ERR(qs->soc_dev);

	socinfo_debugfs_init(qs, info, item_size);

	/* Feed the soc specअगरic unique data पूर्णांकo entropy pool */
	add_device_अक्रमomness(info, item_size);

	platक्रमm_set_drvdata(pdev, qs->soc_dev);

	वापस 0;
पूर्ण

अटल पूर्णांक qcom_socinfo_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा qcom_socinfo *qs = platक्रमm_get_drvdata(pdev);

	soc_device_unरेजिस्टर(qs->soc_dev);

	socinfo_debugfs_निकास(qs);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver qcom_socinfo_driver = अणु
	.probe = qcom_socinfo_probe,
	.हटाओ = qcom_socinfo_हटाओ,
	.driver  = अणु
		.name = "qcom-socinfo",
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(qcom_socinfo_driver);

MODULE_DESCRIPTION("Qualcomm SoCinfo driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:qcom-socinfo");
