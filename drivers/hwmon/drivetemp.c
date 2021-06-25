<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Hwmon client क्रम disk and solid state drives with temperature sensors
 * Copyright (C) 2019 Zodiac Inflight Innovations
 *
 * With input from:
 *    Hwmon client क्रम S.M.A.R.T. hard disk drives with temperature sensors.
 *    (C) 2018 Linus Walleij
 *
 *    hwmon: Driver क्रम SCSI/ATA temperature sensors
 *    by Constantin Baranov <स्थिर@mimas.ru>, submitted September 2009
 *
 * This drive supports reporting the temperature of SATA drives. It can be
 * easily extended to report the temperature of SCSI drives.
 *
 * The primary means to पढ़ो drive temperatures and temperature limits
 * क्रम ATA drives is the SCT Command Transport feature set as specअगरied in
 * ATA8-ACS.
 * It can be used to पढ़ो the current drive temperature, temperature limits,
 * and historic minimum and maximum temperatures. The SCT Command Transport
 * feature set is करोcumented in "AT Attachment 8 - ATA/ATAPI Command Set
 * (ATA8-ACS)".
 *
 * If the SCT Command Transport feature set is not available, drive temperatures
 * may be पढ़ोable through SMART attributes. Since SMART attributes are not well
 * defined, this method is only used as fallback mechanism.
 *
 * There are three SMART attributes which may report drive temperatures.
 * Those are defined as follows (from
 * http://www.cropel.com/library/smart-attribute-list.aspx).
 *
 * 190	Temperature	Temperature, monitored by a sensor somewhere inside
 *			the drive. Raw value typicaly holds the actual
 *			temperature (hexadecimal) in its righपंचांगost two digits.
 *
 * 194	Temperature	Temperature, monitored by a sensor somewhere inside
 *			the drive. Raw value typicaly holds the actual
 *			temperature (hexadecimal) in its righपंचांगost two digits.
 *
 * 231	Temperature	Temperature, monitored by a sensor somewhere inside
 *			the drive. Raw value typicaly holds the actual
 *			temperature (hexadecimal) in its righपंचांगost two digits.
 *
 * Wikipedia defines attributes a bit dअगरferently.
 *
 * 190	Temperature	Value is equal to (100-temp. तओC), allowing manufacturer
 *	Dअगरference or	to set a minimum threshold which corresponds to a
 *	Airflow		maximum temperature. This also follows the convention of
 *	Temperature	100 being a best-हाल value and lower values being
 *			undesirable. However, some older drives may instead
 *			report raw Temperature (identical to 0xC2) or
 *			Temperature minus 50 here.
 * 194	Temperature or	Indicates the device temperature, अगर the appropriate
 *	Temperature	sensor is fitted. Lowest byte of the raw value contains
 *	Celsius		the exact temperature value (Celsius degrees).
 * 231	Lअगरe Left	Indicates the approximate SSD lअगरe left, in terms of
 *	(SSDs) or	program/erase cycles or available reserved blocks.
 *	Temperature	A normalized value of 100 represents a new drive, with
 *			a threshold value at 10 indicating a need क्रम
 *			replacement. A value of 0 may mean that the drive is
 *			operating in पढ़ो-only mode to allow data recovery.
 *			Previously (pre-2010) occasionally used क्रम Drive
 *			Temperature (more typically reported at 0xC2).
 *
 * Common denominator is that the first raw byte reports the temperature
 * in degrees C on almost all drives. Some drives may report a fractional
 * temperature in the second raw byte.
 *
 * Known exceptions (from libatयंत्रart):
 * - SAMSUNG SV0412H and SAMSUNG SV1204H) report the temperature in 10th
 *   degrees C in the first two raw bytes.
 * - A few Maxtor drives report an unknown or bad value in attribute 194.
 * - Certain Apple SSD drives report an unknown value in attribute 190.
 *   Only certain firmware versions are affected.
 *
 * Those exceptions affect older ATA drives and are currently ignored.
 * Also, the second raw byte (possibly reporting the fractional temperature)
 * is currently ignored.
 *
 * Many drives also report temperature limits in additional SMART data raw
 * bytes. The क्रमmat of those is not well defined and varies widely.
 * The driver करोes not currently attempt to report those limits.
 *
 * According to data in smarपंचांगontools, attribute 231 is rarely used to report
 * drive temperatures. At the same समय, several drives report SSD lअगरe left
 * in attribute 231, but करो not support temperature sensors. For this reason,
 * attribute 231 is currently ignored.
 *
 * Following above definitions, temperatures are reported as follows.
 *   If SCT Command Transport is supported, it is used to पढ़ो the
 *   temperature and, अगर available, temperature limits.
 * - Otherwise, अगर SMART attribute 194 is supported, it is used to पढ़ो
 *   the temperature.
 * - Otherwise, अगर SMART attribute 190 is supported, it is used to पढ़ो
 *   the temperature.
 */

#समावेश <linux/ata.h>
#समावेश <linux/bits.h>
#समावेश <linux/device.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <scsi/scsi_cmnd.h>
#समावेश <scsi/scsi_device.h>
#समावेश <scsi/scsi_driver.h>
#समावेश <scsi/scsi_proto.h>

काष्ठा drivetemp_data अणु
	काष्ठा list_head list;		/* list of instantiated devices */
	काष्ठा mutex lock;		/* protect data buffer accesses */
	काष्ठा scsi_device *sdev;	/* SCSI device */
	काष्ठा device *dev;		/* instantiating device */
	काष्ठा device *hwdev;		/* hardware monitoring device */
	u8 smartdata[ATA_SECT_SIZE];	/* local buffer */
	पूर्णांक (*get_temp)(काष्ठा drivetemp_data *st, u32 attr, दीर्घ *val);
	bool have_temp_lowest;		/* lowest temp in SCT status */
	bool have_temp_highest;		/* highest temp in SCT status */
	bool have_temp_min;		/* have min temp */
	bool have_temp_max;		/* have max temp */
	bool have_temp_lcrit;		/* have lower critical limit */
	bool have_temp_crit;		/* have critical limit */
	पूर्णांक temp_min;			/* min temp */
	पूर्णांक temp_max;			/* max temp */
	पूर्णांक temp_lcrit;			/* lower critical limit */
	पूर्णांक temp_crit;			/* critical limit */
पूर्ण;

अटल LIST_HEAD(drivetemp_devlist);

#घोषणा ATA_MAX_SMART_ATTRS	30
#घोषणा SMART_TEMP_PROP_190	190
#घोषणा SMART_TEMP_PROP_194	194

#घोषणा SCT_STATUS_REQ_ADDR	0xe0
#घोषणा  SCT_STATUS_VERSION_LOW		0	/* log byte offsets */
#घोषणा  SCT_STATUS_VERSION_HIGH	1
#घोषणा  SCT_STATUS_TEMP		200
#घोषणा  SCT_STATUS_TEMP_LOWEST		201
#घोषणा  SCT_STATUS_TEMP_HIGHEST	202
#घोषणा SCT_READ_LOG_ADDR	0xe1
#घोषणा  SMART_READ_LOG			0xd5
#घोषणा  SMART_WRITE_LOG		0xd6

#घोषणा INVALID_TEMP		0x80

#घोषणा temp_is_valid(temp)	((temp) != INVALID_TEMP)
#घोषणा temp_from_sct(temp)	(((s8)(temp)) * 1000)

अटल अंतरभूत bool ata_id_smart_supported(u16 *id)
अणु
	वापस id[ATA_ID_COMMAND_SET_1] & BIT(0);
पूर्ण

अटल अंतरभूत bool ata_id_smart_enabled(u16 *id)
अणु
	वापस id[ATA_ID_CFS_ENABLE_1] & BIT(0);
पूर्ण

अटल पूर्णांक drivetemp_scsi_command(काष्ठा drivetemp_data *st,
				 u8 ata_command, u8 feature,
				 u8 lba_low, u8 lba_mid, u8 lba_high)
अणु
	u8 scsi_cmd[MAX_COMMAND_SIZE];
	पूर्णांक data_dir;

	स_रखो(scsi_cmd, 0, माप(scsi_cmd));
	scsi_cmd[0] = ATA_16;
	अगर (ata_command == ATA_CMD_SMART && feature == SMART_WRITE_LOG) अणु
		scsi_cmd[1] = (5 << 1);	/* PIO Data-out */
		/*
		 * No off.line or cc, ग_लिखो to dev, block count in sector count
		 * field.
		 */
		scsi_cmd[2] = 0x06;
		data_dir = DMA_TO_DEVICE;
	पूर्ण अन्यथा अणु
		scsi_cmd[1] = (4 << 1);	/* PIO Data-in */
		/*
		 * No off.line or cc, पढ़ो from dev, block count in sector count
		 * field.
		 */
		scsi_cmd[2] = 0x0e;
		data_dir = DMA_FROM_DEVICE;
	पूर्ण
	scsi_cmd[4] = feature;
	scsi_cmd[6] = 1;	/* 1 sector */
	scsi_cmd[8] = lba_low;
	scsi_cmd[10] = lba_mid;
	scsi_cmd[12] = lba_high;
	scsi_cmd[14] = ata_command;

	वापस scsi_execute_req(st->sdev, scsi_cmd, data_dir,
				st->smartdata, ATA_SECT_SIZE, शून्य, HZ, 5,
				शून्य);
पूर्ण

अटल पूर्णांक drivetemp_ata_command(काष्ठा drivetemp_data *st, u8 feature,
				 u8 select)
अणु
	वापस drivetemp_scsi_command(st, ATA_CMD_SMART, feature, select,
				     ATA_SMART_LBAM_PASS, ATA_SMART_LBAH_PASS);
पूर्ण

अटल पूर्णांक drivetemp_get_smarttemp(काष्ठा drivetemp_data *st, u32 attr,
				  दीर्घ *temp)
अणु
	u8 *buf = st->smartdata;
	bool have_temp = false;
	u8 temp_raw;
	u8 csum;
	पूर्णांक err;
	पूर्णांक i;

	err = drivetemp_ata_command(st, ATA_SMART_READ_VALUES, 0);
	अगर (err)
		वापस err;

	/* Checksum the पढ़ो value table */
	csum = 0;
	क्रम (i = 0; i < ATA_SECT_SIZE; i++)
		csum += buf[i];
	अगर (csum) अणु
		dev_dbg(&st->sdev->sdev_gendev,
			"checksum error reading SMART values\n");
		वापस -EIO;
	पूर्ण

	क्रम (i = 0; i < ATA_MAX_SMART_ATTRS; i++) अणु
		u8 *attr = buf + i * 12;
		पूर्णांक id = attr[2];

		अगर (!id)
			जारी;

		अगर (id == SMART_TEMP_PROP_190) अणु
			temp_raw = attr[7];
			have_temp = true;
		पूर्ण
		अगर (id == SMART_TEMP_PROP_194) अणु
			temp_raw = attr[7];
			have_temp = true;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (have_temp) अणु
		*temp = temp_raw * 1000;
		वापस 0;
	पूर्ण

	वापस -ENXIO;
पूर्ण

अटल पूर्णांक drivetemp_get_scttemp(काष्ठा drivetemp_data *st, u32 attr, दीर्घ *val)
अणु
	u8 *buf = st->smartdata;
	पूर्णांक err;

	err = drivetemp_ata_command(st, SMART_READ_LOG, SCT_STATUS_REQ_ADDR);
	अगर (err)
		वापस err;
	चयन (attr) अणु
	हाल hwmon_temp_input:
		अगर (!temp_is_valid(buf[SCT_STATUS_TEMP]))
			वापस -ENODATA;
		*val = temp_from_sct(buf[SCT_STATUS_TEMP]);
		अवरोध;
	हाल hwmon_temp_lowest:
		अगर (!temp_is_valid(buf[SCT_STATUS_TEMP_LOWEST]))
			वापस -ENODATA;
		*val = temp_from_sct(buf[SCT_STATUS_TEMP_LOWEST]);
		अवरोध;
	हाल hwmon_temp_highest:
		अगर (!temp_is_valid(buf[SCT_STATUS_TEMP_HIGHEST]))
			वापस -ENODATA;
		*val = temp_from_sct(buf[SCT_STATUS_TEMP_HIGHEST]);
		अवरोध;
	शेष:
		err = -EINVAL;
		अवरोध;
	पूर्ण
	वापस err;
पूर्ण

अटल स्थिर अक्षर * स्थिर sct_aव्योम_models[] = अणु
/*
 * These drives will have WRITE FPDMA QUEUED command समयouts and someबार just
 * मुक्तze until घातer-cycled under heavy ग_लिखो loads when their temperature is
 * getting polled in SCT mode. The SMART mode seems to be fine, though.
 *
 * While only the 3 TB model (DT01ACA3) was actually caught exhibiting the
 * problem let's play safe here to aव्योम data corruption and ban the whole
 * DT01ACAx family.

 * The models from this array are prefix-matched.
 */
	"TOSHIBA DT01ACA",
पूर्ण;

अटल bool drivetemp_sct_aव्योम(काष्ठा drivetemp_data *st)
अणु
	काष्ठा scsi_device *sdev = st->sdev;
	अचिन्हित पूर्णांक ctr;

	अगर (!sdev->model)
		वापस false;

	/*
	 * The "model" field contains just the raw SCSI INQUIRY response
	 * "product identification" field, which has a width of 16 bytes.
	 * This field is space-filled, but is NOT शून्य-terminated.
	 */
	क्रम (ctr = 0; ctr < ARRAY_SIZE(sct_aव्योम_models); ctr++)
		अगर (!म_भेदन(sdev->model, sct_aव्योम_models[ctr],
			     म_माप(sct_aव्योम_models[ctr])))
			वापस true;

	वापस false;
पूर्ण

अटल पूर्णांक drivetemp_identअगरy_sata(काष्ठा drivetemp_data *st)
अणु
	काष्ठा scsi_device *sdev = st->sdev;
	u8 *buf = st->smartdata;
	काष्ठा scsi_vpd *vpd;
	bool is_ata, is_sata;
	bool have_sct_data_table;
	bool have_sct_temp;
	bool have_smart;
	bool have_sct;
	u16 *ata_id;
	u16 version;
	दीर्घ temp;
	पूर्णांक err;

	/* SCSI-ATA Translation present? */
	rcu_पढ़ो_lock();
	vpd = rcu_dereference(sdev->vpd_pg89);

	/*
	 * Verअगरy that ATA IDENTIFY DEVICE data is included in ATA Inक्रमmation
	 * VPD and that the drive implements the SATA protocol.
	 */
	अगर (!vpd || vpd->len < 572 || vpd->data[56] != ATA_CMD_ID_ATA ||
	    vpd->data[36] != 0x34) अणु
		rcu_पढ़ो_unlock();
		वापस -ENODEV;
	पूर्ण
	ata_id = (u16 *)&vpd->data[60];
	is_ata = ata_id_is_ata(ata_id);
	is_sata = ata_id_is_sata(ata_id);
	have_sct = ata_id_sct_supported(ata_id);
	have_sct_data_table = ata_id_sct_data_tables(ata_id);
	have_smart = ata_id_smart_supported(ata_id) &&
				ata_id_smart_enabled(ata_id);

	rcu_पढ़ो_unlock();

	/* bail out अगर this is not a SATA device */
	अगर (!is_ata || !is_sata)
		वापस -ENODEV;

	अगर (have_sct && drivetemp_sct_aव्योम(st)) अणु
		dev_notice(&sdev->sdev_gendev,
			   "will avoid using SCT for temperature monitoring\n");
		have_sct = false;
	पूर्ण

	अगर (!have_sct)
		जाओ skip_sct;

	err = drivetemp_ata_command(st, SMART_READ_LOG, SCT_STATUS_REQ_ADDR);
	अगर (err)
		जाओ skip_sct;

	version = (buf[SCT_STATUS_VERSION_HIGH] << 8) |
		  buf[SCT_STATUS_VERSION_LOW];
	अगर (version != 2 && version != 3)
		जाओ skip_sct;

	have_sct_temp = temp_is_valid(buf[SCT_STATUS_TEMP]);
	अगर (!have_sct_temp)
		जाओ skip_sct;

	st->have_temp_lowest = temp_is_valid(buf[SCT_STATUS_TEMP_LOWEST]);
	st->have_temp_highest = temp_is_valid(buf[SCT_STATUS_TEMP_HIGHEST]);

	अगर (!have_sct_data_table)
		जाओ skip_sct_data;

	/* Request and पढ़ो temperature history table */
	स_रखो(buf, '\0', माप(st->smartdata));
	buf[0] = 5;	/* data table command */
	buf[2] = 1;	/* पढ़ो table */
	buf[4] = 2;	/* temperature history table */

	err = drivetemp_ata_command(st, SMART_WRITE_LOG, SCT_STATUS_REQ_ADDR);
	अगर (err)
		जाओ skip_sct_data;

	err = drivetemp_ata_command(st, SMART_READ_LOG, SCT_READ_LOG_ADDR);
	अगर (err)
		जाओ skip_sct_data;

	/*
	 * Temperature limits per AT Attachment 8 -
	 * ATA/ATAPI Command Set (ATA8-ACS)
	 */
	st->have_temp_max = temp_is_valid(buf[6]);
	st->have_temp_crit = temp_is_valid(buf[7]);
	st->have_temp_min = temp_is_valid(buf[8]);
	st->have_temp_lcrit = temp_is_valid(buf[9]);

	st->temp_max = temp_from_sct(buf[6]);
	st->temp_crit = temp_from_sct(buf[7]);
	st->temp_min = temp_from_sct(buf[8]);
	st->temp_lcrit = temp_from_sct(buf[9]);

skip_sct_data:
	अगर (have_sct_temp) अणु
		st->get_temp = drivetemp_get_scttemp;
		वापस 0;
	पूर्ण
skip_sct:
	अगर (!have_smart)
		वापस -ENODEV;
	st->get_temp = drivetemp_get_smarttemp;
	वापस drivetemp_get_smarttemp(st, hwmon_temp_input, &temp);
पूर्ण

अटल पूर्णांक drivetemp_identअगरy(काष्ठा drivetemp_data *st)
अणु
	काष्ठा scsi_device *sdev = st->sdev;

	/* Bail out immediately अगर there is no inquiry data */
	अगर (!sdev->inquiry || sdev->inquiry_len < 16)
		वापस -ENODEV;

	/* Disk device? */
	अगर (sdev->type != TYPE_DISK && sdev->type != TYPE_ZBC)
		वापस -ENODEV;

	वापस drivetemp_identअगरy_sata(st);
पूर्ण

अटल पूर्णांक drivetemp_पढ़ो(काष्ठा device *dev, क्रमागत hwmon_sensor_types type,
			 u32 attr, पूर्णांक channel, दीर्घ *val)
अणु
	काष्ठा drivetemp_data *st = dev_get_drvdata(dev);
	पूर्णांक err = 0;

	अगर (type != hwmon_temp)
		वापस -EINVAL;

	चयन (attr) अणु
	हाल hwmon_temp_input:
	हाल hwmon_temp_lowest:
	हाल hwmon_temp_highest:
		mutex_lock(&st->lock);
		err = st->get_temp(st, attr, val);
		mutex_unlock(&st->lock);
		अवरोध;
	हाल hwmon_temp_lcrit:
		*val = st->temp_lcrit;
		अवरोध;
	हाल hwmon_temp_min:
		*val = st->temp_min;
		अवरोध;
	हाल hwmon_temp_max:
		*val = st->temp_max;
		अवरोध;
	हाल hwmon_temp_crit:
		*val = st->temp_crit;
		अवरोध;
	शेष:
		err = -EINVAL;
		अवरोध;
	पूर्ण
	वापस err;
पूर्ण

अटल umode_t drivetemp_is_visible(स्थिर व्योम *data,
				   क्रमागत hwmon_sensor_types type,
				   u32 attr, पूर्णांक channel)
अणु
	स्थिर काष्ठा drivetemp_data *st = data;

	चयन (type) अणु
	हाल hwmon_temp:
		चयन (attr) अणु
		हाल hwmon_temp_input:
			वापस 0444;
		हाल hwmon_temp_lowest:
			अगर (st->have_temp_lowest)
				वापस 0444;
			अवरोध;
		हाल hwmon_temp_highest:
			अगर (st->have_temp_highest)
				वापस 0444;
			अवरोध;
		हाल hwmon_temp_min:
			अगर (st->have_temp_min)
				वापस 0444;
			अवरोध;
		हाल hwmon_temp_max:
			अगर (st->have_temp_max)
				वापस 0444;
			अवरोध;
		हाल hwmon_temp_lcrit:
			अगर (st->have_temp_lcrit)
				वापस 0444;
			अवरोध;
		हाल hwmon_temp_crit:
			अगर (st->have_temp_crit)
				वापस 0444;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा hwmon_channel_info *drivetemp_info[] = अणु
	HWMON_CHANNEL_INFO(chip,
			   HWMON_C_REGISTER_TZ),
	HWMON_CHANNEL_INFO(temp, HWMON_T_INPUT |
			   HWMON_T_LOWEST | HWMON_T_HIGHEST |
			   HWMON_T_MIN | HWMON_T_MAX |
			   HWMON_T_LCRIT | HWMON_T_CRIT),
	शून्य
पूर्ण;

अटल स्थिर काष्ठा hwmon_ops drivetemp_ops = अणु
	.is_visible = drivetemp_is_visible,
	.पढ़ो = drivetemp_पढ़ो,
पूर्ण;

अटल स्थिर काष्ठा hwmon_chip_info drivetemp_chip_info = अणु
	.ops = &drivetemp_ops,
	.info = drivetemp_info,
पूर्ण;

/*
 * The device argument poपूर्णांकs to sdev->sdev_dev. Its parent is
 * sdev->sdev_gendev, which we can use to get the scsi_device poपूर्णांकer.
 */
अटल पूर्णांक drivetemp_add(काष्ठा device *dev, काष्ठा class_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा scsi_device *sdev = to_scsi_device(dev->parent);
	काष्ठा drivetemp_data *st;
	पूर्णांक err;

	st = kzalloc(माप(*st), GFP_KERNEL);
	अगर (!st)
		वापस -ENOMEM;

	st->sdev = sdev;
	st->dev = dev;
	mutex_init(&st->lock);

	अगर (drivetemp_identअगरy(st)) अणु
		err = -ENODEV;
		जाओ पात;
	पूर्ण

	st->hwdev = hwmon_device_रेजिस्टर_with_info(dev->parent, "drivetemp",
						    st, &drivetemp_chip_info,
						    शून्य);
	अगर (IS_ERR(st->hwdev)) अणु
		err = PTR_ERR(st->hwdev);
		जाओ पात;
	पूर्ण

	list_add(&st->list, &drivetemp_devlist);
	वापस 0;

पात:
	kमुक्त(st);
	वापस err;
पूर्ण

अटल व्योम drivetemp_हटाओ(काष्ठा device *dev, काष्ठा class_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा drivetemp_data *st, *पंचांगp;

	list_क्रम_each_entry_safe(st, पंचांगp, &drivetemp_devlist, list) अणु
		अगर (st->dev == dev) अणु
			list_del(&st->list);
			hwmon_device_unरेजिस्टर(st->hwdev);
			kमुक्त(st);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल काष्ठा class_पूर्णांकerface drivetemp_पूर्णांकerface = अणु
	.add_dev = drivetemp_add,
	.हटाओ_dev = drivetemp_हटाओ,
पूर्ण;

अटल पूर्णांक __init drivetemp_init(व्योम)
अणु
	वापस scsi_रेजिस्टर_पूर्णांकerface(&drivetemp_पूर्णांकerface);
पूर्ण

अटल व्योम __निकास drivetemp_निकास(व्योम)
अणु
	scsi_unरेजिस्टर_पूर्णांकerface(&drivetemp_पूर्णांकerface);
पूर्ण

module_init(drivetemp_init);
module_निकास(drivetemp_निकास);

MODULE_AUTHOR("Guenter Roeck <linus@roeck-us.net>");
MODULE_DESCRIPTION("Hard drive temperature monitor");
MODULE_LICENSE("GPL");
