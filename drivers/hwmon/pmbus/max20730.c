<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Driver क्रम MAX20710, MAX20730, MAX20734, and MAX20743 Integrated,
 * Step-Down Switching Regulators
 *
 * Copyright 2019 Google LLC.
 * Copyright 2020 Maxim Integrated
 */

#समावेश <linux/bits.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/err.h>
#समावेश <linux/i2c.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/of_device.h>
#समावेश <linux/pmbus.h>
#समावेश <linux/util_macros.h>
#समावेश "pmbus.h"

क्रमागत chips अणु
	max20710,
	max20730,
	max20734,
	max20743
पूर्ण;

क्रमागत अणु
	MAX20730_DEBUGFS_VOUT_MIN = 0,
	MAX20730_DEBUGFS_FREQUENCY,
	MAX20730_DEBUGFS_PG_DELAY,
	MAX20730_DEBUGFS_INTERNAL_GAIN,
	MAX20730_DEBUGFS_BOOT_VOLTAGE,
	MAX20730_DEBUGFS_OUT_V_RAMP_RATE,
	MAX20730_DEBUGFS_OC_PROTECT_MODE,
	MAX20730_DEBUGFS_SS_TIMING,
	MAX20730_DEBUGFS_IMAX,
	MAX20730_DEBUGFS_OPERATION,
	MAX20730_DEBUGFS_ON_OFF_CONFIG,
	MAX20730_DEBUGFS_SMBALERT_MASK,
	MAX20730_DEBUGFS_VOUT_MODE,
	MAX20730_DEBUGFS_VOUT_COMMAND,
	MAX20730_DEBUGFS_VOUT_MAX,
	MAX20730_DEBUGFS_NUM_ENTRIES
पूर्ण;

काष्ठा max20730_data अणु
	क्रमागत chips id;
	काष्ठा pmbus_driver_info info;
	काष्ठा mutex lock;	/* Used to protect against parallel ग_लिखोs */
	u16 mfr_devset1;
	u16 mfr_devset2;
	u16 mfr_vouपंचांगin;
	u32 vout_voltage_भागider[2];
पूर्ण;

#घोषणा to_max20730_data(x)  container_of(x, काष्ठा max20730_data, info)

#घोषणा VOLT_FROM_REG(val)	DIV_ROUND_CLOSEST((val), 1 << 9)

#घोषणा PMBUS_SMB_ALERT_MASK	0x1B

#घोषणा MAX20730_MFR_VOUT_MIN	0xd1
#घोषणा MAX20730_MFR_DEVSET1	0xd2
#घोषणा MAX20730_MFR_DEVSET2	0xd3

#घोषणा MAX20730_MFR_VOUT_MIN_MASK		GENMASK(9, 0)
#घोषणा MAX20730_MFR_VOUT_MIN_BIT_POS		0

#घोषणा MAX20730_MFR_DEVSET1_RGAIN_MASK		(BIT(13) | BIT(14))
#घोषणा MAX20730_MFR_DEVSET1_OTP_MASK		(BIT(11) | BIT(12))
#घोषणा MAX20730_MFR_DEVSET1_VBOOT_MASK		(BIT(8) | BIT(9))
#घोषणा MAX20730_MFR_DEVSET1_OCP_MASK		(BIT(5) | BIT(6))
#घोषणा MAX20730_MFR_DEVSET1_FSW_MASK		GENMASK(4, 2)
#घोषणा MAX20730_MFR_DEVSET1_TSTAT_MASK		(BIT(0) | BIT(1))

#घोषणा MAX20730_MFR_DEVSET1_RGAIN_BIT_POS	13
#घोषणा MAX20730_MFR_DEVSET1_OTP_BIT_POS	11
#घोषणा MAX20730_MFR_DEVSET1_VBOOT_BIT_POS	8
#घोषणा MAX20730_MFR_DEVSET1_OCP_BIT_POS	5
#घोषणा MAX20730_MFR_DEVSET1_FSW_BIT_POS	2
#घोषणा MAX20730_MFR_DEVSET1_TSTAT_BIT_POS	0

#घोषणा MAX20730_MFR_DEVSET2_IMAX_MASK		GENMASK(10, 8)
#घोषणा MAX20730_MFR_DEVSET2_VRATE		(BIT(6) | BIT(7))
#घोषणा MAX20730_MFR_DEVSET2_OCPM_MASK		BIT(5)
#घोषणा MAX20730_MFR_DEVSET2_SS_MASK		(BIT(0) | BIT(1))

#घोषणा MAX20730_MFR_DEVSET2_IMAX_BIT_POS	8
#घोषणा MAX20730_MFR_DEVSET2_VRATE_BIT_POS	6
#घोषणा MAX20730_MFR_DEVSET2_OCPM_BIT_POS	5
#घोषणा MAX20730_MFR_DEVSET2_SS_BIT_POS		0

#घोषणा DEBUG_FS_DATA_MAX			16

काष्ठा max20730_debugfs_data अणु
	काष्ठा i2c_client *client;
	पूर्णांक debugfs_entries[MAX20730_DEBUGFS_NUM_ENTRIES];
पूर्ण;

#घोषणा to_psu(x, y) container_of((x), \
			काष्ठा max20730_debugfs_data, debugfs_entries[(y)])

#अगर_घोषित CONFIG_DEBUG_FS
अटल sमाप_प्रकार max20730_debugfs_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
				     माप_प्रकार count, loff_t *ppos)
अणु
	पूर्णांक ret, len;
	पूर्णांक *idxp = file->निजी_data;
	पूर्णांक idx = *idxp;
	काष्ठा max20730_debugfs_data *psu = to_psu(idxp, idx);
	स्थिर काष्ठा pmbus_driver_info *info;
	स्थिर काष्ठा max20730_data *data;
	अक्षर tbuf[DEBUG_FS_DATA_MAX] = अणु 0 पूर्ण;
	u16 val;

	info = pmbus_get_driver_info(psu->client);
	data = to_max20730_data(info);

	चयन (idx) अणु
	हाल MAX20730_DEBUGFS_VOUT_MIN:
		ret = VOLT_FROM_REG(data->mfr_vouपंचांगin * 10000);
		len = scnम_लिखो(tbuf, DEBUG_FS_DATA_MAX, "%d.%d\n",
				ret / 10000, ret % 10000);
		अवरोध;
	हाल MAX20730_DEBUGFS_FREQUENCY:
		val = (data->mfr_devset1 & MAX20730_MFR_DEVSET1_FSW_MASK)
			>> MAX20730_MFR_DEVSET1_FSW_BIT_POS;

		अगर (val == 0)
			ret = 400;
		अन्यथा अगर (val == 1)
			ret = 500;
		अन्यथा अगर (val == 2 || val == 3)
			ret = 600;
		अन्यथा अगर (val == 4)
			ret = 700;
		अन्यथा अगर (val == 5)
			ret = 800;
		अन्यथा
			ret = 900;
		len = scnम_लिखो(tbuf, DEBUG_FS_DATA_MAX, "%d\n", ret);
		अवरोध;
	हाल MAX20730_DEBUGFS_PG_DELAY:
		val = (data->mfr_devset1 & MAX20730_MFR_DEVSET1_TSTAT_MASK)
			>> MAX20730_MFR_DEVSET1_TSTAT_BIT_POS;

		अगर (val == 0)
			len = strlcpy(tbuf, "2000\n", DEBUG_FS_DATA_MAX);
		अन्यथा अगर (val == 1)
			len = strlcpy(tbuf, "125\n", DEBUG_FS_DATA_MAX);
		अन्यथा अगर (val == 2)
			len = strlcpy(tbuf, "62.5\n", DEBUG_FS_DATA_MAX);
		अन्यथा
			len = strlcpy(tbuf, "32\n", DEBUG_FS_DATA_MAX);
		अवरोध;
	हाल MAX20730_DEBUGFS_INTERNAL_GAIN:
		val = (data->mfr_devset1 & MAX20730_MFR_DEVSET1_RGAIN_MASK)
			>> MAX20730_MFR_DEVSET1_RGAIN_BIT_POS;

		अगर (data->id == max20734) अणु
			/* AN6209 */
			अगर (val == 0)
				len = strlcpy(tbuf, "0.8\n", DEBUG_FS_DATA_MAX);
			अन्यथा अगर (val == 1)
				len = strlcpy(tbuf, "3.2\n", DEBUG_FS_DATA_MAX);
			अन्यथा अगर (val == 2)
				len = strlcpy(tbuf, "1.6\n", DEBUG_FS_DATA_MAX);
			अन्यथा
				len = strlcpy(tbuf, "6.4\n", DEBUG_FS_DATA_MAX);
		पूर्ण अन्यथा अगर (data->id == max20730 || data->id == max20710) अणु
			/* AN6042 or AN6140 */
			अगर (val == 0)
				len = strlcpy(tbuf, "0.9\n", DEBUG_FS_DATA_MAX);
			अन्यथा अगर (val == 1)
				len = strlcpy(tbuf, "3.6\n", DEBUG_FS_DATA_MAX);
			अन्यथा अगर (val == 2)
				len = strlcpy(tbuf, "1.8\n", DEBUG_FS_DATA_MAX);
			अन्यथा
				len = strlcpy(tbuf, "7.2\n", DEBUG_FS_DATA_MAX);
		पूर्ण अन्यथा अगर (data->id == max20743) अणु
			/* AN6042 */
			अगर (val == 0)
				len = strlcpy(tbuf, "0.45\n", DEBUG_FS_DATA_MAX);
			अन्यथा अगर (val == 1)
				len = strlcpy(tbuf, "1.8\n", DEBUG_FS_DATA_MAX);
			अन्यथा अगर (val == 2)
				len = strlcpy(tbuf, "0.9\n", DEBUG_FS_DATA_MAX);
			अन्यथा
				len = strlcpy(tbuf, "3.6\n", DEBUG_FS_DATA_MAX);
		पूर्ण अन्यथा अणु
			len = strlcpy(tbuf, "Not supported\n", DEBUG_FS_DATA_MAX);
		पूर्ण
		अवरोध;
	हाल MAX20730_DEBUGFS_BOOT_VOLTAGE:
		val = (data->mfr_devset1 & MAX20730_MFR_DEVSET1_VBOOT_MASK)
			>> MAX20730_MFR_DEVSET1_VBOOT_BIT_POS;

		अगर (val == 0)
			len = strlcpy(tbuf, "0.6484\n", DEBUG_FS_DATA_MAX);
		अन्यथा अगर (val == 1)
			len = strlcpy(tbuf, "0.8984\n", DEBUG_FS_DATA_MAX);
		अन्यथा अगर (val == 2)
			len = strlcpy(tbuf, "1.0\n", DEBUG_FS_DATA_MAX);
		अन्यथा
			len = strlcpy(tbuf, "Invalid\n", DEBUG_FS_DATA_MAX);
		अवरोध;
	हाल MAX20730_DEBUGFS_OUT_V_RAMP_RATE:
		val = (data->mfr_devset2 & MAX20730_MFR_DEVSET2_VRATE)
			>> MAX20730_MFR_DEVSET2_VRATE_BIT_POS;

		अगर (val == 0)
			len = strlcpy(tbuf, "4\n", DEBUG_FS_DATA_MAX);
		अन्यथा अगर (val == 1)
			len = strlcpy(tbuf, "2\n", DEBUG_FS_DATA_MAX);
		अन्यथा अगर (val == 2)
			len = strlcpy(tbuf, "1\n", DEBUG_FS_DATA_MAX);
		अन्यथा
			len = strlcpy(tbuf, "Invalid\n", DEBUG_FS_DATA_MAX);
		अवरोध;
	हाल MAX20730_DEBUGFS_OC_PROTECT_MODE:
		ret = (data->mfr_devset2 & MAX20730_MFR_DEVSET2_OCPM_MASK)
			>> MAX20730_MFR_DEVSET2_OCPM_BIT_POS;
		len = scnम_लिखो(tbuf, DEBUG_FS_DATA_MAX, "%d\n", ret);
		अवरोध;
	हाल MAX20730_DEBUGFS_SS_TIMING:
		val = (data->mfr_devset2 & MAX20730_MFR_DEVSET2_SS_MASK)
			>> MAX20730_MFR_DEVSET2_SS_BIT_POS;

		अगर (val == 0)
			len = strlcpy(tbuf, "0.75\n", DEBUG_FS_DATA_MAX);
		अन्यथा अगर (val == 1)
			len = strlcpy(tbuf, "1.5\n", DEBUG_FS_DATA_MAX);
		अन्यथा अगर (val == 2)
			len = strlcpy(tbuf, "3\n", DEBUG_FS_DATA_MAX);
		अन्यथा
			len = strlcpy(tbuf, "6\n", DEBUG_FS_DATA_MAX);
		अवरोध;
	हाल MAX20730_DEBUGFS_IMAX:
		ret = (data->mfr_devset2 & MAX20730_MFR_DEVSET2_IMAX_MASK)
			>> MAX20730_MFR_DEVSET2_IMAX_BIT_POS;
		len = scnम_लिखो(tbuf, DEBUG_FS_DATA_MAX, "%d\n", ret);
		अवरोध;
	हाल MAX20730_DEBUGFS_OPERATION:
		ret = i2c_smbus_पढ़ो_byte_data(psu->client, PMBUS_OPERATION);
		अगर (ret < 0)
			वापस ret;
		len = scnम_लिखो(tbuf, DEBUG_FS_DATA_MAX, "%d\n", ret);
		अवरोध;
	हाल MAX20730_DEBUGFS_ON_OFF_CONFIG:
		ret = i2c_smbus_पढ़ो_byte_data(psu->client, PMBUS_ON_OFF_CONFIG);
		अगर (ret < 0)
			वापस ret;
		len = scnम_लिखो(tbuf, DEBUG_FS_DATA_MAX, "%d\n", ret);
		अवरोध;
	हाल MAX20730_DEBUGFS_SMBALERT_MASK:
		ret = i2c_smbus_पढ़ो_word_data(psu->client,
					       PMBUS_SMB_ALERT_MASK);
		अगर (ret < 0)
			वापस ret;
		len = scnम_लिखो(tbuf, DEBUG_FS_DATA_MAX, "%d\n", ret);
		अवरोध;
	हाल MAX20730_DEBUGFS_VOUT_MODE:
		ret = i2c_smbus_पढ़ो_byte_data(psu->client, PMBUS_VOUT_MODE);
		अगर (ret < 0)
			वापस ret;
		len = scnम_लिखो(tbuf, DEBUG_FS_DATA_MAX, "%d\n", ret);
		अवरोध;
	हाल MAX20730_DEBUGFS_VOUT_COMMAND:
		ret = i2c_smbus_पढ़ो_word_data(psu->client, PMBUS_VOUT_COMMAND);
		अगर (ret < 0)
			वापस ret;

		ret = VOLT_FROM_REG(ret * 10000);
		len = scnम_लिखो(tbuf, DEBUG_FS_DATA_MAX,
				"%d.%d\n", ret / 10000, ret % 10000);
		अवरोध;
	हाल MAX20730_DEBUGFS_VOUT_MAX:
		ret = i2c_smbus_पढ़ो_word_data(psu->client, PMBUS_VOUT_MAX);
		अगर (ret < 0)
			वापस ret;

		ret = VOLT_FROM_REG(ret * 10000);
		len = scnम_लिखो(tbuf, DEBUG_FS_DATA_MAX,
				"%d.%d\n", ret / 10000, ret % 10000);
		अवरोध;
	शेष:
		len = strlcpy(tbuf, "Invalid\n", DEBUG_FS_DATA_MAX);
	पूर्ण

	वापस simple_पढ़ो_from_buffer(buf, count, ppos, tbuf, len);
पूर्ण

अटल स्थिर काष्ठा file_operations max20730_fops = अणु
	.llseek = noop_llseek,
	.पढ़ो = max20730_debugfs_पढ़ो,
	.ग_लिखो = शून्य,
	.खोलो = simple_खोलो,
पूर्ण;

अटल पूर्णांक max20730_init_debugfs(काष्ठा i2c_client *client,
				 काष्ठा max20730_data *data)
अणु
	पूर्णांक ret, i;
	काष्ठा dentry *debugfs;
	काष्ठा dentry *max20730_dir;
	काष्ठा max20730_debugfs_data *psu;

	ret = i2c_smbus_पढ़ो_word_data(client, MAX20730_MFR_DEVSET2);
	अगर (ret < 0)
		वापस ret;
	data->mfr_devset2 = ret;

	ret = i2c_smbus_पढ़ो_word_data(client, MAX20730_MFR_VOUT_MIN);
	अगर (ret < 0)
		वापस ret;
	data->mfr_vouपंचांगin = ret;

	psu = devm_kzalloc(&client->dev, माप(*psu), GFP_KERNEL);
	अगर (!psu)
		वापस -ENOMEM;
	psu->client = client;

	debugfs = pmbus_get_debugfs_dir(client);
	अगर (!debugfs)
		वापस -ENOENT;

	max20730_dir = debugfs_create_dir(client->name, debugfs);

	क्रम (i = 0; i < MAX20730_DEBUGFS_NUM_ENTRIES; ++i)
		psu->debugfs_entries[i] = i;

	debugfs_create_file("vout_min", 0444, max20730_dir,
			    &psu->debugfs_entries[MAX20730_DEBUGFS_VOUT_MIN],
			    &max20730_fops);
	debugfs_create_file("frequency", 0444, max20730_dir,
			    &psu->debugfs_entries[MAX20730_DEBUGFS_FREQUENCY],
			    &max20730_fops);
	debugfs_create_file("power_good_delay", 0444, max20730_dir,
			    &psu->debugfs_entries[MAX20730_DEBUGFS_PG_DELAY],
			    &max20730_fops);
	debugfs_create_file("internal_gain", 0444, max20730_dir,
			    &psu->debugfs_entries[MAX20730_DEBUGFS_INTERNAL_GAIN],
			    &max20730_fops);
	debugfs_create_file("boot_voltage", 0444, max20730_dir,
			    &psu->debugfs_entries[MAX20730_DEBUGFS_BOOT_VOLTAGE],
			    &max20730_fops);
	debugfs_create_file("out_voltage_ramp_rate", 0444, max20730_dir,
			    &psu->debugfs_entries[MAX20730_DEBUGFS_OUT_V_RAMP_RATE],
			    &max20730_fops);
	debugfs_create_file("oc_protection_mode", 0444, max20730_dir,
			    &psu->debugfs_entries[MAX20730_DEBUGFS_OC_PROTECT_MODE],
			    &max20730_fops);
	debugfs_create_file("soft_start_timing", 0444, max20730_dir,
			    &psu->debugfs_entries[MAX20730_DEBUGFS_SS_TIMING],
			    &max20730_fops);
	debugfs_create_file("imax", 0444, max20730_dir,
			    &psu->debugfs_entries[MAX20730_DEBUGFS_IMAX],
			    &max20730_fops);
	debugfs_create_file("operation", 0444, max20730_dir,
			    &psu->debugfs_entries[MAX20730_DEBUGFS_OPERATION],
			    &max20730_fops);
	debugfs_create_file("on_off_config", 0444, max20730_dir,
			    &psu->debugfs_entries[MAX20730_DEBUGFS_ON_OFF_CONFIG],
			    &max20730_fops);
	debugfs_create_file("smbalert_mask", 0444, max20730_dir,
			    &psu->debugfs_entries[MAX20730_DEBUGFS_SMBALERT_MASK],
			    &max20730_fops);
	debugfs_create_file("vout_mode", 0444, max20730_dir,
			    &psu->debugfs_entries[MAX20730_DEBUGFS_VOUT_MODE],
			    &max20730_fops);
	debugfs_create_file("vout_command", 0444, max20730_dir,
			    &psu->debugfs_entries[MAX20730_DEBUGFS_VOUT_COMMAND],
			    &max20730_fops);
	debugfs_create_file("vout_max", 0444, max20730_dir,
			    &psu->debugfs_entries[MAX20730_DEBUGFS_VOUT_MAX],
			    &max20730_fops);

	वापस 0;
पूर्ण
#अन्यथा
अटल पूर्णांक max20730_init_debugfs(काष्ठा i2c_client *client,
				 काष्ठा max20730_data *data)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_DEBUG_FS */

अटल स्थिर काष्ठा i2c_device_id max20730_id[];

/*
 * Convert discreet value to direct data क्रमmat. Strictly speaking, all passed
 * values are स्थिरants, so we could करो that calculation manually. On the
 * करोwnside, that would make the driver more dअगरficult to मुख्यtain, so lets
 * use this approach.
 */
अटल u16 val_to_direct(पूर्णांक v, क्रमागत pmbus_sensor_classes class,
			 स्थिर काष्ठा pmbus_driver_info *info)
अणु
	पूर्णांक R = info->R[class] - 3;	/* take milli-units पूर्णांकo account */
	पूर्णांक b = info->b[class] * 1000;
	दीर्घ d;

	d = v * info->m[class] + b;
	/*
	 * R < 0 is true क्रम all callers, so we करोn't need to bother
	 * about the R > 0 हाल.
	 */
	जबतक (R < 0) अणु
		d = DIV_ROUND_CLOSEST(d, 10);
		R++;
	पूर्ण
	वापस (u16)d;
पूर्ण

अटल दीर्घ direct_to_val(u16 w, क्रमागत pmbus_sensor_classes class,
			  स्थिर काष्ठा pmbus_driver_info *info)
अणु
	पूर्णांक R = info->R[class] - 3;
	पूर्णांक b = info->b[class] * 1000;
	पूर्णांक m = info->m[class];
	दीर्घ d = (s16)w;

	अगर (m == 0)
		वापस 0;

	जबतक (R < 0) अणु
		d *= 10;
		R++;
	पूर्ण
	d = (d - b) / m;
	वापस d;
पूर्ण

अटल u32 max_current[][5] = अणु
	[max20710] = अणु 6200, 8000, 9700, 11600 पूर्ण,
	[max20730] = अणु 13000, 16600, 20100, 23600 पूर्ण,
	[max20734] = अणु 21000, 27000, 32000, 38000 पूर्ण,
	[max20743] = अणु 18900, 24100, 29200, 34100 पूर्ण,
पूर्ण;

अटल पूर्णांक max20730_पढ़ो_word_data(काष्ठा i2c_client *client, पूर्णांक page,
				   पूर्णांक phase, पूर्णांक reg)
अणु
	स्थिर काष्ठा pmbus_driver_info *info = pmbus_get_driver_info(client);
	स्थिर काष्ठा max20730_data *data = to_max20730_data(info);
	पूर्णांक ret = 0;
	u32 max_c;

	चयन (reg) अणु
	हाल PMBUS_OT_FAULT_LIMIT:
		चयन ((data->mfr_devset1 >> 11) & 0x3) अणु
		हाल 0x0:
			ret = val_to_direct(150000, PSC_TEMPERATURE, info);
			अवरोध;
		हाल 0x1:
			ret = val_to_direct(130000, PSC_TEMPERATURE, info);
			अवरोध;
		शेष:
			ret = -ENODATA;
			अवरोध;
		पूर्ण
		अवरोध;
	हाल PMBUS_IOUT_OC_FAULT_LIMIT:
		max_c = max_current[data->id][(data->mfr_devset1 >> 5) & 0x3];
		ret = val_to_direct(max_c, PSC_CURRENT_OUT, info);
		अवरोध;
	हाल PMBUS_READ_VOUT:
		ret = pmbus_पढ़ो_word_data(client, page, phase, reg);
		अगर (ret > 0 && data->vout_voltage_भागider[0] && data->vout_voltage_भागider[1]) अणु
			u64 temp = DIV_ROUND_CLOSEST_ULL((u64)ret * data->vout_voltage_भागider[1],
							 data->vout_voltage_भागider[0]);
			ret = clamp_val(temp, 0, 0xffff);
		पूर्ण
		अवरोध;
	शेष:
		ret = -ENODATA;
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक max20730_ग_लिखो_word_data(काष्ठा i2c_client *client, पूर्णांक page,
				    पूर्णांक reg, u16 word)
अणु
	काष्ठा pmbus_driver_info *info;
	काष्ठा max20730_data *data;
	u16 devset1;
	पूर्णांक ret = 0;
	पूर्णांक idx;

	info = (काष्ठा pmbus_driver_info *)pmbus_get_driver_info(client);
	data = to_max20730_data(info);

	mutex_lock(&data->lock);
	devset1 = data->mfr_devset1;

	चयन (reg) अणु
	हाल PMBUS_OT_FAULT_LIMIT:
		devset1 &= ~(BIT(11) | BIT(12));
		अगर (direct_to_val(word, PSC_TEMPERATURE, info) < 140000)
			devset1 |= BIT(11);
		अवरोध;
	हाल PMBUS_IOUT_OC_FAULT_LIMIT:
		devset1 &= ~(BIT(5) | BIT(6));

		idx = find_बंदst(direct_to_val(word, PSC_CURRENT_OUT, info),
				   max_current[data->id], 4);
		devset1 |= (idx << 5);
		अवरोध;
	शेष:
		ret = -ENODATA;
		अवरोध;
	पूर्ण

	अगर (!ret && devset1 != data->mfr_devset1) अणु
		ret = i2c_smbus_ग_लिखो_word_data(client, MAX20730_MFR_DEVSET1,
						devset1);
		अगर (!ret) अणु
			data->mfr_devset1 = devset1;
			pmbus_clear_cache(client);
		पूर्ण
	पूर्ण
	mutex_unlock(&data->lock);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा pmbus_driver_info max20730_info[] = अणु
	[max20710] = अणु
		.pages = 1,
		.पढ़ो_word_data = max20730_पढ़ो_word_data,
		.ग_लिखो_word_data = max20730_ग_लिखो_word_data,

		/* Source : Maxim AN6140 and AN6042 */
		.क्रमmat[PSC_TEMPERATURE] = direct,
		.m[PSC_TEMPERATURE] = 21,
		.b[PSC_TEMPERATURE] = 5887,
		.R[PSC_TEMPERATURE] = -1,

		.क्रमmat[PSC_VOLTAGE_IN] = direct,
		.m[PSC_VOLTAGE_IN] = 3609,
		.b[PSC_VOLTAGE_IN] = 0,
		.R[PSC_VOLTAGE_IN] = -2,

		.क्रमmat[PSC_CURRENT_OUT] = direct,
		.m[PSC_CURRENT_OUT] = 153,
		.b[PSC_CURRENT_OUT] = 4976,
		.R[PSC_CURRENT_OUT] = -1,

		.क्रमmat[PSC_VOLTAGE_OUT] = linear,

		.func[0] = PMBUS_HAVE_VIN |
			PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT |
			PMBUS_HAVE_IOUT | PMBUS_HAVE_STATUS_IOUT |
			PMBUS_HAVE_TEMP | PMBUS_HAVE_STATUS_TEMP |
			PMBUS_HAVE_STATUS_INPUT,
	पूर्ण,
	[max20730] = अणु
		.pages = 1,
		.पढ़ो_word_data = max20730_पढ़ो_word_data,
		.ग_लिखो_word_data = max20730_ग_लिखो_word_data,

		/* Source : Maxim AN6042 */
		.क्रमmat[PSC_TEMPERATURE] = direct,
		.m[PSC_TEMPERATURE] = 21,
		.b[PSC_TEMPERATURE] = 5887,
		.R[PSC_TEMPERATURE] = -1,

		.क्रमmat[PSC_VOLTAGE_IN] = direct,
		.m[PSC_VOLTAGE_IN] = 3609,
		.b[PSC_VOLTAGE_IN] = 0,
		.R[PSC_VOLTAGE_IN] = -2,

		/*
		 * Values in the datasheet are adjusted क्रम temperature and
		 * क्रम the relationship between Vin and Vout.
		 * Unक्रमtunately, the data sheet suggests that Vout measurement
		 * may be scaled with a resistor array. This is indeed the हाल
		 * at least on the evaulation boards. As a result, any in-driver
		 * adjusपंचांगents would either be wrong or require elaborate means
		 * to configure the scaling. Instead of करोing that, just report
		 * raw values and let userspace handle adjusपंचांगents.
		 */
		.क्रमmat[PSC_CURRENT_OUT] = direct,
		.m[PSC_CURRENT_OUT] = 153,
		.b[PSC_CURRENT_OUT] = 4976,
		.R[PSC_CURRENT_OUT] = -1,

		.क्रमmat[PSC_VOLTAGE_OUT] = linear,

		.func[0] = PMBUS_HAVE_VIN |
			PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT |
			PMBUS_HAVE_IOUT | PMBUS_HAVE_STATUS_IOUT |
			PMBUS_HAVE_TEMP | PMBUS_HAVE_STATUS_TEMP |
			PMBUS_HAVE_STATUS_INPUT,
	पूर्ण,
	[max20734] = अणु
		.pages = 1,
		.पढ़ो_word_data = max20730_पढ़ो_word_data,
		.ग_लिखो_word_data = max20730_ग_लिखो_word_data,

		/* Source : Maxim AN6209 */
		.क्रमmat[PSC_TEMPERATURE] = direct,
		.m[PSC_TEMPERATURE] = 21,
		.b[PSC_TEMPERATURE] = 5887,
		.R[PSC_TEMPERATURE] = -1,

		.क्रमmat[PSC_VOLTAGE_IN] = direct,
		.m[PSC_VOLTAGE_IN] = 3592,
		.b[PSC_VOLTAGE_IN] = 0,
		.R[PSC_VOLTAGE_IN] = -2,

		.क्रमmat[PSC_CURRENT_OUT] = direct,
		.m[PSC_CURRENT_OUT] = 111,
		.b[PSC_CURRENT_OUT] = 3461,
		.R[PSC_CURRENT_OUT] = -1,

		.क्रमmat[PSC_VOLTAGE_OUT] = linear,

		.func[0] = PMBUS_HAVE_VIN |
			PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT |
			PMBUS_HAVE_IOUT | PMBUS_HAVE_STATUS_IOUT |
			PMBUS_HAVE_TEMP | PMBUS_HAVE_STATUS_TEMP |
			PMBUS_HAVE_STATUS_INPUT,
	पूर्ण,
	[max20743] = अणु
		.pages = 1,
		.पढ़ो_word_data = max20730_पढ़ो_word_data,
		.ग_लिखो_word_data = max20730_ग_लिखो_word_data,

		/* Source : Maxim AN6042 */
		.क्रमmat[PSC_TEMPERATURE] = direct,
		.m[PSC_TEMPERATURE] = 21,
		.b[PSC_TEMPERATURE] = 5887,
		.R[PSC_TEMPERATURE] = -1,

		.क्रमmat[PSC_VOLTAGE_IN] = direct,
		.m[PSC_VOLTAGE_IN] = 3597,
		.b[PSC_VOLTAGE_IN] = 0,
		.R[PSC_VOLTAGE_IN] = -2,

		.क्रमmat[PSC_CURRENT_OUT] = direct,
		.m[PSC_CURRENT_OUT] = 95,
		.b[PSC_CURRENT_OUT] = 5014,
		.R[PSC_CURRENT_OUT] = -1,

		.क्रमmat[PSC_VOLTAGE_OUT] = linear,

		.func[0] = PMBUS_HAVE_VIN |
			PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT |
			PMBUS_HAVE_IOUT | PMBUS_HAVE_STATUS_IOUT |
			PMBUS_HAVE_TEMP | PMBUS_HAVE_STATUS_TEMP |
			PMBUS_HAVE_STATUS_INPUT,
	पूर्ण,
पूर्ण;

अटल पूर्णांक max20730_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा device *dev = &client->dev;
	u8 buf[I2C_SMBUS_BLOCK_MAX + 1];
	काष्ठा max20730_data *data;
	क्रमागत chips chip_id;
	पूर्णांक ret;

	अगर (!i2c_check_functionality(client->adapter,
				     I2C_FUNC_SMBUS_READ_BYTE_DATA |
				     I2C_FUNC_SMBUS_READ_WORD_DATA |
				     I2C_FUNC_SMBUS_BLOCK_DATA))
		वापस -ENODEV;

	ret = i2c_smbus_पढ़ो_block_data(client, PMBUS_MFR_ID, buf);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "Failed to read Manufacturer ID\n");
		वापस ret;
	पूर्ण
	अगर (ret != 5 || म_भेदन(buf, "MAXIM", 5)) अणु
		buf[ret] = '\0';
		dev_err(dev, "Unsupported Manufacturer ID '%s'\n", buf);
		वापस -ENODEV;
	पूर्ण

	/*
	 * The chips support पढ़ोing PMBUS_MFR_MODEL. On both MAX20730
	 * and MAX20734, पढ़ोing it वापसs M20743. Presumably that is
	 * the reason why the command is not करोcumented. Unक्रमtunately,
	 * that means that there is no reliable means to detect the chip.
	 * However, we can at least detect the chip series. Compare
	 * the वापसed value against 'M20743' and bail out अगर there is
	 * a mismatch. If that करोesn't work क्रम all chips, we may have
	 * to हटाओ this check.
	 */
	ret = i2c_smbus_पढ़ो_block_data(client, PMBUS_MFR_MODEL, buf);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to read Manufacturer Model\n");
		वापस ret;
	पूर्ण
	अगर (ret != 6 || म_भेदन(buf, "M20743", 6)) अणु
		buf[ret] = '\0';
		dev_err(dev, "Unsupported Manufacturer Model '%s'\n", buf);
		वापस -ENODEV;
	पूर्ण

	ret = i2c_smbus_पढ़ो_block_data(client, PMBUS_MFR_REVISION, buf);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to read Manufacturer Revision\n");
		वापस ret;
	पूर्ण
	अगर (ret != 1 || buf[0] != 'F') अणु
		buf[ret] = '\0';
		dev_err(dev, "Unsupported Manufacturer Revision '%s'\n", buf);
		वापस -ENODEV;
	पूर्ण

	अगर (client->dev.of_node)
		chip_id = (क्रमागत chips)of_device_get_match_data(dev);
	अन्यथा
		chip_id = i2c_match_id(max20730_id, client)->driver_data;

	data = devm_kzalloc(dev, माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;
	data->id = chip_id;
	mutex_init(&data->lock);
	स_नकल(&data->info, &max20730_info[chip_id], माप(data->info));
	अगर (of_property_पढ़ो_u32_array(client->dev.of_node, "vout-voltage-divider",
				       data->vout_voltage_भागider,
				       ARRAY_SIZE(data->vout_voltage_भागider)) != 0)
		स_रखो(data->vout_voltage_भागider, 0, माप(data->vout_voltage_भागider));
	अगर (data->vout_voltage_भागider[1] < data->vout_voltage_भागider[0]) अणु
		dev_err(dev,
			"The total resistance of voltage divider is less than output resistance\n");
		वापस -EINVAL;
	पूर्ण

	ret = i2c_smbus_पढ़ो_word_data(client, MAX20730_MFR_DEVSET1);
	अगर (ret < 0)
		वापस ret;
	data->mfr_devset1 = ret;

	ret = pmbus_करो_probe(client, &data->info);
	अगर (ret < 0)
		वापस ret;

	ret = max20730_init_debugfs(client, data);
	अगर (ret)
		dev_warn(dev, "Failed to register debugfs: %d\n",
			 ret);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id max20730_id[] = अणु
	अणु "max20710", max20710 पूर्ण,
	अणु "max20730", max20730 पूर्ण,
	अणु "max20734", max20734 पूर्ण,
	अणु "max20743", max20743 पूर्ण,
	अणु पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(i2c, max20730_id);

अटल स्थिर काष्ठा of_device_id max20730_of_match[] = अणु
	अणु .compatible = "maxim,max20710", .data = (व्योम *)max20710 पूर्ण,
	अणु .compatible = "maxim,max20730", .data = (व्योम *)max20730 पूर्ण,
	अणु .compatible = "maxim,max20734", .data = (व्योम *)max20734 पूर्ण,
	अणु .compatible = "maxim,max20743", .data = (व्योम *)max20743 पूर्ण,
	अणु पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, max20730_of_match);

अटल काष्ठा i2c_driver max20730_driver = अणु
	.driver = अणु
		.name = "max20730",
		.of_match_table = max20730_of_match,
	पूर्ण,
	.probe_new = max20730_probe,
	.id_table = max20730_id,
पूर्ण;

module_i2c_driver(max20730_driver);

MODULE_AUTHOR("Guenter Roeck <linux@roeck-us.net>");
MODULE_DESCRIPTION("PMBus driver for Maxim MAX20710 / MAX20730 / MAX20734 / MAX20743");
MODULE_LICENSE("GPL");
MODULE_IMPORT_NS(PMBUS);
