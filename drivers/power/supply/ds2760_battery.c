<शैली गुरु>
/*
 * Driver क्रम batteries with DS2760 chips inside.
 *
 * Copyright तऊ 2007 Anton Vorontsov
 *	       2004-2007 Matt Reimer
 *	       2004 Szabolcs Gyurko
 *
 * Use consistent with the GNU GPL is permitted,
 * provided that this copyright notice is
 * preserved in its entirety in all copies and derived works.
 *
 * Author:  Anton Vorontsov <cbou@mail.ru>
 *	    February 2007
 *
 *	    Matt Reimer <mreimer@vpop.net>
 *	    April 2004, 2005, 2007
 *
 *	    Szabolcs Gyurko <szabolcs.gyurko@tlt.hu>
 *	    September 2004
 */

#समावेश <linux/module.h>
#समावेश <linux/param.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/pm.h>
#समावेश <linux/slab.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/घातer_supply.h>
#समावेश <linux/suspend.h>
#समावेश <linux/w1.h>
#समावेश <linux/of.h>

अटल अचिन्हित पूर्णांक cache_समय = 1000;
module_param(cache_समय, uपूर्णांक, 0644);
MODULE_PARM_DESC(cache_समय, "cache time in milliseconds");

अटल bool pmod_enabled;
module_param(pmod_enabled, bool, 0644);
MODULE_PARM_DESC(pmod_enabled, "PMOD enable bit");

अटल अचिन्हित पूर्णांक rated_capacity;
module_param(rated_capacity, uपूर्णांक, 0644);
MODULE_PARM_DESC(rated_capacity, "rated battery capacity, 10*mAh or index");

अटल अचिन्हित पूर्णांक current_accum;
module_param(current_accum, uपूर्णांक, 0644);
MODULE_PARM_DESC(current_accum, "current accumulator value");

#घोषणा W1_FAMILY_DS2760		0x30

/* Known commands to the DS2760 chip */
#घोषणा W1_DS2760_SWAP			0xAA
#घोषणा W1_DS2760_READ_DATA		0x69
#घोषणा W1_DS2760_WRITE_DATA		0x6C
#घोषणा W1_DS2760_COPY_DATA		0x48
#घोषणा W1_DS2760_RECALL_DATA		0xB8
#घोषणा W1_DS2760_LOCK			0x6A

/* Number of valid रेजिस्टर addresses */
#घोषणा DS2760_DATA_SIZE		0x40

#घोषणा DS2760_PROTECTION_REG		0x00

#घोषणा DS2760_STATUS_REG		0x01
#घोषणा DS2760_STATUS_IE		(1 << 2)
#घोषणा DS2760_STATUS_SWEN		(1 << 3)
#घोषणा DS2760_STATUS_RNAOP		(1 << 4)
#घोषणा DS2760_STATUS_PMOD		(1 << 5)

#घोषणा DS2760_EEPROM_REG		0x07
#घोषणा DS2760_SPECIAL_FEATURE_REG	0x08
#घोषणा DS2760_VOLTAGE_MSB		0x0c
#घोषणा DS2760_VOLTAGE_LSB		0x0d
#घोषणा DS2760_CURRENT_MSB		0x0e
#घोषणा DS2760_CURRENT_LSB		0x0f
#घोषणा DS2760_CURRENT_ACCUM_MSB	0x10
#घोषणा DS2760_CURRENT_ACCUM_LSB	0x11
#घोषणा DS2760_TEMP_MSB			0x18
#घोषणा DS2760_TEMP_LSB			0x19
#घोषणा DS2760_EEPROM_BLOCK0		0x20
#घोषणा DS2760_ACTIVE_FULL		0x20
#घोषणा DS2760_EEPROM_BLOCK1		0x30
#घोषणा DS2760_STATUS_WRITE_REG		0x31
#घोषणा DS2760_RATED_CAPACITY		0x32
#घोषणा DS2760_CURRENT_OFFSET_BIAS	0x33
#घोषणा DS2760_ACTIVE_EMPTY		0x3b

काष्ठा ds2760_device_info अणु
	काष्ठा device *dev;

	/* DS2760 data, valid after calling ds2760_battery_पढ़ो_status() */
	अचिन्हित दीर्घ update_समय;	/* jअगरfies when data पढ़ो */
	अक्षर raw[DS2760_DATA_SIZE];	/* raw DS2760 data */
	पूर्णांक voltage_raw;		/* units of 4.88 mV */
	पूर्णांक voltage_uV;			/* units of तगV */
	पूर्णांक current_raw;		/* units of 0.625 mA */
	पूर्णांक current_uA;			/* units of तगA */
	पूर्णांक accum_current_raw;		/* units of 0.25 mAh */
	पूर्णांक accum_current_uAh;		/* units of तगAh */
	पूर्णांक temp_raw;			/* units of 0.125 तओC */
	पूर्णांक temp_C;			/* units of 0.1 तओC */
	पूर्णांक rated_capacity;		/* units of तगAh */
	पूर्णांक rem_capacity;		/* percentage */
	पूर्णांक full_active_uAh;		/* units of तगAh */
	पूर्णांक empty_uAh;			/* units of तगAh */
	पूर्णांक lअगरe_sec;			/* units of seconds */
	पूर्णांक अक्षरge_status;		/* POWER_SUPPLY_STATUS_* */

	पूर्णांक full_counter;
	काष्ठा घातer_supply *bat;
	काष्ठा घातer_supply_desc bat_desc;
	काष्ठा workqueue_काष्ठा *monitor_wqueue;
	काष्ठा delayed_work monitor_work;
	काष्ठा delayed_work set_अक्षरged_work;
	काष्ठा notअगरier_block pm_notअगरier;
पूर्ण;

अटल पूर्णांक w1_ds2760_io(काष्ठा device *dev, अक्षर *buf, पूर्णांक addr, माप_प्रकार count,
			पूर्णांक io)
अणु
	काष्ठा w1_slave *sl = container_of(dev, काष्ठा w1_slave, dev);

	अगर (!dev)
		वापस 0;

	mutex_lock(&sl->master->bus_mutex);

	अगर (addr > DS2760_DATA_SIZE || addr < 0) अणु
		count = 0;
		जाओ out;
	पूर्ण
	अगर (addr + count > DS2760_DATA_SIZE)
		count = DS2760_DATA_SIZE - addr;

	अगर (!w1_reset_select_slave(sl)) अणु
		अगर (!io) अणु
			w1_ग_लिखो_8(sl->master, W1_DS2760_READ_DATA);
			w1_ग_लिखो_8(sl->master, addr);
			count = w1_पढ़ो_block(sl->master, buf, count);
		पूर्ण अन्यथा अणु
			w1_ग_लिखो_8(sl->master, W1_DS2760_WRITE_DATA);
			w1_ग_लिखो_8(sl->master, addr);
			w1_ग_लिखो_block(sl->master, buf, count);
			/* XXX w1_ग_लिखो_block वापसs व्योम, not n_written */
		पूर्ण
	पूर्ण

out:
	mutex_unlock(&sl->master->bus_mutex);

	वापस count;
पूर्ण

अटल पूर्णांक w1_ds2760_पढ़ो(काष्ठा device *dev,
			  अक्षर *buf, पूर्णांक addr,
			  माप_प्रकार count)
अणु
	वापस w1_ds2760_io(dev, buf, addr, count, 0);
पूर्ण

अटल पूर्णांक w1_ds2760_ग_लिखो(काष्ठा device *dev,
			   अक्षर *buf,
			   पूर्णांक addr, माप_प्रकार count)
अणु
	वापस w1_ds2760_io(dev, buf, addr, count, 1);
पूर्ण

अटल पूर्णांक w1_ds2760_eeprom_cmd(काष्ठा device *dev, पूर्णांक addr, पूर्णांक cmd)
अणु
	काष्ठा w1_slave *sl = container_of(dev, काष्ठा w1_slave, dev);

	अगर (!dev)
		वापस -EINVAL;

	mutex_lock(&sl->master->bus_mutex);

	अगर (w1_reset_select_slave(sl) == 0) अणु
		w1_ग_लिखो_8(sl->master, cmd);
		w1_ग_लिखो_8(sl->master, addr);
	पूर्ण

	mutex_unlock(&sl->master->bus_mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक w1_ds2760_store_eeprom(काष्ठा device *dev, पूर्णांक addr)
अणु
	वापस w1_ds2760_eeprom_cmd(dev, addr, W1_DS2760_COPY_DATA);
पूर्ण

अटल पूर्णांक w1_ds2760_recall_eeprom(काष्ठा device *dev, पूर्णांक addr)
अणु
	वापस w1_ds2760_eeprom_cmd(dev, addr, W1_DS2760_RECALL_DATA);
पूर्ण

अटल sमाप_प्रकार w1_slave_पढ़ो(काष्ठा file *filp, काष्ठा kobject *kobj,
			     काष्ठा bin_attribute *bin_attr, अक्षर *buf,
			     loff_t off, माप_प्रकार count)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	वापस w1_ds2760_पढ़ो(dev, buf, off, count);
पूर्ण

अटल BIN_ATTR_RO(w1_slave, DS2760_DATA_SIZE);

अटल काष्ठा bin_attribute *w1_ds2760_bin_attrs[] = अणु
	&bin_attr_w1_slave,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group w1_ds2760_group = अणु
	.bin_attrs = w1_ds2760_bin_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *w1_ds2760_groups[] = अणु
	&w1_ds2760_group,
	शून्य,
पूर्ण;
/* Some batteries have their rated capacity stored a N * 10 mAh, जबतक
 * others use an index पूर्णांकo this table. */
अटल पूर्णांक rated_capacities[] = अणु
	0,
	920,	/* Samsung */
	920,	/* BYD */
	920,	/* Lishen */
	920,	/* NEC */
	1440,	/* Samsung */
	1440,	/* BYD */
#अगर_घोषित CONFIG_MACH_H4700
	1800,	/* HP iPAQ hx4700 3.7V 1800mAh (359113-001) */
#अन्यथा
	1440,	/* Lishen */
#पूर्ण_अगर
	1440,	/* NEC */
	2880,	/* Samsung */
	2880,	/* BYD */
	2880,	/* Lishen */
	2880,	/* NEC */
#अगर_घोषित CONFIG_MACH_H4700
	0,
	3600,	/* HP iPAQ hx4700 3.7V 3600mAh (359114-001) */
#पूर्ण_अगर
पूर्ण;

/* array is level at temps 0तओC, 10तओC, 20तओC, 30तओC, 40तओC
 * temp is in Celsius */
अटल पूर्णांक battery_पूर्णांकerpolate(पूर्णांक array[], पूर्णांक temp)
अणु
	पूर्णांक index, dt;

	अगर (temp <= 0)
		वापस array[0];
	अगर (temp >= 40)
		वापस array[4];

	index = temp / 10;
	dt    = temp % 10;

	वापस array[index] + (((array[index + 1] - array[index]) * dt) / 10);
पूर्ण

अटल पूर्णांक ds2760_battery_पढ़ो_status(काष्ठा ds2760_device_info *di)
अणु
	पूर्णांक ret, i, start, count, scale[5];

	अगर (di->update_समय && समय_beक्रमe(jअगरfies, di->update_समय +
					   msecs_to_jअगरfies(cache_समय)))
		वापस 0;

	/* The first समय we पढ़ो the entire contents of SRAM/EEPROM,
	 * but after that we just पढ़ो the पूर्णांकeresting bits that change. */
	अगर (di->update_समय == 0) अणु
		start = 0;
		count = DS2760_DATA_SIZE;
	पूर्ण अन्यथा अणु
		start = DS2760_VOLTAGE_MSB;
		count = DS2760_TEMP_LSB - start + 1;
	पूर्ण

	ret = w1_ds2760_पढ़ो(di->dev, di->raw + start, start, count);
	अगर (ret != count) अणु
		dev_warn(di->dev, "call to w1_ds2760_read failed (0x%p)\n",
			 di->dev);
		वापस 1;
	पूर्ण

	di->update_समय = jअगरfies;

	/* DS2760 reports voltage in units of 4.88mV, but the battery class
	 * reports in units of uV, so convert by multiplying by 4880. */
	di->voltage_raw = (di->raw[DS2760_VOLTAGE_MSB] << 3) |
			  (di->raw[DS2760_VOLTAGE_LSB] >> 5);
	di->voltage_uV = di->voltage_raw * 4880;

	/* DS2760 reports current in चिन्हित units of 0.625mA, but the battery
	 * class reports in units of तगA, so convert by multiplying by 625. */
	di->current_raw =
	    (((चिन्हित अक्षर)di->raw[DS2760_CURRENT_MSB]) << 5) |
			  (di->raw[DS2760_CURRENT_LSB] >> 3);
	di->current_uA = di->current_raw * 625;

	/* DS2760 reports accumulated current in चिन्हित units of 0.25mAh. */
	di->accum_current_raw =
	    (((चिन्हित अक्षर)di->raw[DS2760_CURRENT_ACCUM_MSB]) << 8) |
			   di->raw[DS2760_CURRENT_ACCUM_LSB];
	di->accum_current_uAh = di->accum_current_raw * 250;

	/* DS2760 reports temperature in चिन्हित units of 0.125तओC, but the
	 * battery class reports in units of 1/10 तओC, so we convert by
	 * multiplying by .125 * 10 = 1.25. */
	di->temp_raw = (((चिन्हित अक्षर)di->raw[DS2760_TEMP_MSB]) << 3) |
				     (di->raw[DS2760_TEMP_LSB] >> 5);
	di->temp_C = di->temp_raw + (di->temp_raw / 4);

	/* At least some battery monitors (e.g. HP iPAQ) store the battery's
	 * maximum rated capacity. */
	अगर (di->raw[DS2760_RATED_CAPACITY] < ARRAY_SIZE(rated_capacities))
		di->rated_capacity = rated_capacities[
			(अचिन्हित पूर्णांक)di->raw[DS2760_RATED_CAPACITY]];
	अन्यथा
		di->rated_capacity = di->raw[DS2760_RATED_CAPACITY] * 10;

	di->rated_capacity *= 1000; /* convert to तगAh */

	/* Calculate the full level at the present temperature. */
	di->full_active_uAh = di->raw[DS2760_ACTIVE_FULL] << 8 |
			      di->raw[DS2760_ACTIVE_FULL + 1];

	/* If the full_active_uAh value is not given, fall back to the rated
	 * capacity. This is likely to happen when chips are not part of the
	 * battery pack and is thereक्रमe not bootstrapped. */
	अगर (di->full_active_uAh == 0)
		di->full_active_uAh = di->rated_capacity / 1000L;

	scale[0] = di->full_active_uAh;
	क्रम (i = 1; i < 5; i++)
		scale[i] = scale[i - 1] + di->raw[DS2760_ACTIVE_FULL + 1 + i];

	di->full_active_uAh = battery_पूर्णांकerpolate(scale, di->temp_C / 10);
	di->full_active_uAh *= 1000; /* convert to तगAh */

	/* Calculate the empty level at the present temperature. */
	scale[4] = di->raw[DS2760_ACTIVE_EMPTY + 4];
	क्रम (i = 3; i >= 0; i--)
		scale[i] = scale[i + 1] + di->raw[DS2760_ACTIVE_EMPTY + i];

	di->empty_uAh = battery_पूर्णांकerpolate(scale, di->temp_C / 10);
	di->empty_uAh *= 1000; /* convert to तगAh */

	अगर (di->full_active_uAh == di->empty_uAh)
		di->rem_capacity = 0;
	अन्यथा
		/* From Maxim Application Note 131: reमुख्यing capacity =
		 * ((ICA - Empty Value) / (Full Value - Empty Value)) x 100% */
		di->rem_capacity = ((di->accum_current_uAh - di->empty_uAh) * 100L) /
				    (di->full_active_uAh - di->empty_uAh);

	अगर (di->rem_capacity < 0)
		di->rem_capacity = 0;
	अगर (di->rem_capacity > 100)
		di->rem_capacity = 100;

	अगर (di->current_uA < -100L)
		di->lअगरe_sec = -((di->accum_current_uAh - di->empty_uAh) * 36L)
					/ (di->current_uA / 100L);
	अन्यथा
		di->lअगरe_sec = 0;

	वापस 0;
पूर्ण

अटल व्योम ds2760_battery_set_current_accum(काष्ठा ds2760_device_info *di,
					     अचिन्हित पूर्णांक acr_val)
अणु
	अचिन्हित अक्षर acr[2];

	/* acr is in units of 0.25 mAh */
	acr_val *= 4L;
	acr_val /= 1000;

	acr[0] = acr_val >> 8;
	acr[1] = acr_val & 0xff;

	अगर (w1_ds2760_ग_लिखो(di->dev, acr, DS2760_CURRENT_ACCUM_MSB, 2) < 2)
		dev_warn(di->dev, "ACR write failed\n");
पूर्ण

अटल व्योम ds2760_battery_update_status(काष्ठा ds2760_device_info *di)
अणु
	पूर्णांक old_अक्षरge_status = di->अक्षरge_status;

	ds2760_battery_पढ़ो_status(di);

	अगर (di->अक्षरge_status == POWER_SUPPLY_STATUS_UNKNOWN)
		di->full_counter = 0;

	अगर (घातer_supply_am_i_supplied(di->bat)) अणु
		अगर (di->current_uA > 10000) अणु
			di->अक्षरge_status = POWER_SUPPLY_STATUS_CHARGING;
			di->full_counter = 0;
		पूर्ण अन्यथा अगर (di->current_uA < -5000) अणु
			अगर (di->अक्षरge_status != POWER_SUPPLY_STATUS_NOT_CHARGING)
				dev_notice(di->dev, "not enough power to "
					   "charge\n");
			di->अक्षरge_status = POWER_SUPPLY_STATUS_NOT_CHARGING;
			di->full_counter = 0;
		पूर्ण अन्यथा अगर (di->current_uA < 10000 &&
			    di->अक्षरge_status != POWER_SUPPLY_STATUS_FULL) अणु

			/* Don't consider the battery to be full unless
			 * we've seen the current < 10 mA at least two
			 * consecutive बार. */

			di->full_counter++;

			अगर (di->full_counter < 2) अणु
				di->अक्षरge_status = POWER_SUPPLY_STATUS_CHARGING;
			पूर्ण अन्यथा अणु
				di->अक्षरge_status = POWER_SUPPLY_STATUS_FULL;
				ds2760_battery_set_current_accum(di,
						di->full_active_uAh);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		di->अक्षरge_status = POWER_SUPPLY_STATUS_DISCHARGING;
		di->full_counter = 0;
	पूर्ण

	अगर (di->अक्षरge_status != old_अक्षरge_status)
		घातer_supply_changed(di->bat);
पूर्ण

अटल व्योम ds2760_battery_ग_लिखो_status(काष्ठा ds2760_device_info *di,
					अक्षर status)
अणु
	अगर (status == di->raw[DS2760_STATUS_REG])
		वापस;

	w1_ds2760_ग_लिखो(di->dev, &status, DS2760_STATUS_WRITE_REG, 1);
	w1_ds2760_store_eeprom(di->dev, DS2760_EEPROM_BLOCK1);
	w1_ds2760_recall_eeprom(di->dev, DS2760_EEPROM_BLOCK1);
पूर्ण

अटल व्योम ds2760_battery_ग_लिखो_rated_capacity(काष्ठा ds2760_device_info *di,
						अचिन्हित अक्षर rated_capacity)
अणु
	अगर (rated_capacity == di->raw[DS2760_RATED_CAPACITY])
		वापस;

	w1_ds2760_ग_लिखो(di->dev, &rated_capacity, DS2760_RATED_CAPACITY, 1);
	w1_ds2760_store_eeprom(di->dev, DS2760_EEPROM_BLOCK1);
	w1_ds2760_recall_eeprom(di->dev, DS2760_EEPROM_BLOCK1);
पूर्ण

अटल व्योम ds2760_battery_ग_लिखो_active_full(काष्ठा ds2760_device_info *di,
					     पूर्णांक active_full)
अणु
	अचिन्हित अक्षर पंचांगp[2] = अणु
		active_full >> 8,
		active_full & 0xff
	पूर्ण;

	अगर (पंचांगp[0] == di->raw[DS2760_ACTIVE_FULL] &&
	    पंचांगp[1] == di->raw[DS2760_ACTIVE_FULL + 1])
		वापस;

	w1_ds2760_ग_लिखो(di->dev, पंचांगp, DS2760_ACTIVE_FULL, माप(पंचांगp));
	w1_ds2760_store_eeprom(di->dev, DS2760_EEPROM_BLOCK0);
	w1_ds2760_recall_eeprom(di->dev, DS2760_EEPROM_BLOCK0);

	/* Write to the di->raw[] buffer directly - the DS2760_ACTIVE_FULL
	 * values won't be पढ़ो back by ds2760_battery_पढ़ो_status() */
	di->raw[DS2760_ACTIVE_FULL] = पंचांगp[0];
	di->raw[DS2760_ACTIVE_FULL + 1] = पंचांगp[1];
पूर्ण

अटल व्योम ds2760_battery_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ds2760_device_info *di = container_of(work,
		काष्ठा ds2760_device_info, monitor_work.work);
	स्थिर पूर्णांक पूर्णांकerval = HZ * 60;

	dev_dbg(di->dev, "%s\n", __func__);

	ds2760_battery_update_status(di);
	queue_delayed_work(di->monitor_wqueue, &di->monitor_work, पूर्णांकerval);
पूर्ण

अटल व्योम ds2760_battery_बाह्यal_घातer_changed(काष्ठा घातer_supply *psy)
अणु
	काष्ठा ds2760_device_info *di = घातer_supply_get_drvdata(psy);

	dev_dbg(di->dev, "%s\n", __func__);

	mod_delayed_work(di->monitor_wqueue, &di->monitor_work, HZ/10);
पूर्ण


अटल व्योम ds2760_battery_set_अक्षरged_work(काष्ठा work_काष्ठा *work)
अणु
	अक्षर bias;
	काष्ठा ds2760_device_info *di = container_of(work,
		काष्ठा ds2760_device_info, set_अक्षरged_work.work);

	dev_dbg(di->dev, "%s\n", __func__);

	ds2760_battery_पढ़ो_status(di);

	/* When we get notअगरied by बाह्यal circuitry that the battery is
	 * considered fully अक्षरged now, we know that there is no current
	 * flow any more. However, the ds2760's पूर्णांकernal current meter is
	 * too inaccurate to rely on - spec say something ~15% failure.
	 * Hence, we use the current offset bias रेजिस्टर to compensate
	 * that error.
	 */

	अगर (!घातer_supply_am_i_supplied(di->bat))
		वापस;

	bias = (चिन्हित अक्षर) di->current_raw +
		(चिन्हित अक्षर) di->raw[DS2760_CURRENT_OFFSET_BIAS];

	dev_dbg(di->dev, "%s: bias = %d\n", __func__, bias);

	w1_ds2760_ग_लिखो(di->dev, &bias, DS2760_CURRENT_OFFSET_BIAS, 1);
	w1_ds2760_store_eeprom(di->dev, DS2760_EEPROM_BLOCK1);
	w1_ds2760_recall_eeprom(di->dev, DS2760_EEPROM_BLOCK1);

	/* Write to the di->raw[] buffer directly - the CURRENT_OFFSET_BIAS
	 * value won't be पढ़ो back by ds2760_battery_पढ़ो_status() */
	di->raw[DS2760_CURRENT_OFFSET_BIAS] = bias;
पूर्ण

अटल व्योम ds2760_battery_set_अक्षरged(काष्ठा घातer_supply *psy)
अणु
	काष्ठा ds2760_device_info *di = घातer_supply_get_drvdata(psy);

	/* postpone the actual work by 20 secs. This is क्रम debouncing GPIO
	 * संकेतs and to let the current value settle. See AN4188. */
	mod_delayed_work(di->monitor_wqueue, &di->set_अक्षरged_work, HZ * 20);
पूर्ण

अटल पूर्णांक ds2760_battery_get_property(काष्ठा घातer_supply *psy,
				       क्रमागत घातer_supply_property psp,
				       जोड़ घातer_supply_propval *val)
अणु
	काष्ठा ds2760_device_info *di = घातer_supply_get_drvdata(psy);

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_STATUS:
		val->पूर्णांकval = di->अक्षरge_status;
		वापस 0;
	शेष:
		अवरोध;
	पूर्ण

	ds2760_battery_पढ़ो_status(di);

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_VOLTAGE_NOW:
		val->पूर्णांकval = di->voltage_uV;
		अवरोध;
	हाल POWER_SUPPLY_PROP_CURRENT_NOW:
		val->पूर्णांकval = di->current_uA;
		अवरोध;
	हाल POWER_SUPPLY_PROP_CHARGE_FULL_DESIGN:
		val->पूर्णांकval = di->rated_capacity;
		अवरोध;
	हाल POWER_SUPPLY_PROP_CHARGE_FULL:
		val->पूर्णांकval = di->full_active_uAh;
		अवरोध;
	हाल POWER_SUPPLY_PROP_CHARGE_EMPTY:
		val->पूर्णांकval = di->empty_uAh;
		अवरोध;
	हाल POWER_SUPPLY_PROP_CHARGE_NOW:
		val->पूर्णांकval = di->accum_current_uAh;
		अवरोध;
	हाल POWER_SUPPLY_PROP_TEMP:
		val->पूर्णांकval = di->temp_C;
		अवरोध;
	हाल POWER_SUPPLY_PROP_TIME_TO_EMPTY_NOW:
		val->पूर्णांकval = di->lअगरe_sec;
		अवरोध;
	हाल POWER_SUPPLY_PROP_CAPACITY:
		val->पूर्णांकval = di->rem_capacity;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ds2760_battery_set_property(काष्ठा घातer_supply *psy,
				       क्रमागत घातer_supply_property psp,
				       स्थिर जोड़ घातer_supply_propval *val)
अणु
	काष्ठा ds2760_device_info *di = घातer_supply_get_drvdata(psy);

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_CHARGE_FULL:
		/* the पूर्णांकerface counts in uAh, convert the value */
		ds2760_battery_ग_लिखो_active_full(di, val->पूर्णांकval / 1000L);
		अवरोध;

	हाल POWER_SUPPLY_PROP_CHARGE_NOW:
		/* ds2760_battery_set_current_accum() करोes the conversion */
		ds2760_battery_set_current_accum(di, val->पूर्णांकval);
		अवरोध;

	शेष:
		वापस -EPERM;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ds2760_battery_property_is_ग_लिखोable(काष्ठा घातer_supply *psy,
						क्रमागत घातer_supply_property psp)
अणु
	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_CHARGE_FULL:
	हाल POWER_SUPPLY_PROP_CHARGE_NOW:
		वापस 1;

	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल क्रमागत घातer_supply_property ds2760_battery_props[] = अणु
	POWER_SUPPLY_PROP_STATUS,
	POWER_SUPPLY_PROP_VOLTAGE_NOW,
	POWER_SUPPLY_PROP_CURRENT_NOW,
	POWER_SUPPLY_PROP_CHARGE_FULL_DESIGN,
	POWER_SUPPLY_PROP_CHARGE_FULL,
	POWER_SUPPLY_PROP_CHARGE_EMPTY,
	POWER_SUPPLY_PROP_CHARGE_NOW,
	POWER_SUPPLY_PROP_TEMP,
	POWER_SUPPLY_PROP_TIME_TO_EMPTY_NOW,
	POWER_SUPPLY_PROP_CAPACITY,
पूर्ण;

अटल पूर्णांक ds2760_pm_notअगरier(काष्ठा notअगरier_block *notअगरier,
			      अचिन्हित दीर्घ pm_event,
			      व्योम *unused)
अणु
	काष्ठा ds2760_device_info *di =
		container_of(notअगरier, काष्ठा ds2760_device_info, pm_notअगरier);

	चयन (pm_event) अणु
	हाल PM_HIBERNATION_PREPARE:
	हाल PM_SUSPEND_PREPARE:
		di->अक्षरge_status = POWER_SUPPLY_STATUS_UNKNOWN;
		अवरोध;

	हाल PM_POST_RESTORE:
	हाल PM_POST_HIBERNATION:
	हाल PM_POST_SUSPEND:
		di->अक्षरge_status = POWER_SUPPLY_STATUS_UNKNOWN;
		घातer_supply_changed(di->bat);
		mod_delayed_work(di->monitor_wqueue, &di->monitor_work, HZ);

		अवरोध;

	हाल PM_RESTORE_PREPARE:
	शेष:
		अवरोध;
	पूर्ण

	वापस NOTIFY_DONE;
पूर्ण

अटल पूर्णांक w1_ds2760_add_slave(काष्ठा w1_slave *sl)
अणु
	काष्ठा घातer_supply_config psy_cfg = अणुपूर्ण;
	काष्ठा ds2760_device_info *di;
	काष्ठा device *dev = &sl->dev;
	पूर्णांक retval = 0;
	अक्षर name[32];
	अक्षर status;

	di = devm_kzalloc(dev, माप(*di), GFP_KERNEL);
	अगर (!di) अणु
		retval = -ENOMEM;
		जाओ di_alloc_failed;
	पूर्ण

	snम_लिखो(name, माप(name), "ds2760-battery.%d", dev->id);

	di->dev				= dev;
	di->bat_desc.name		= name;
	di->bat_desc.type		= POWER_SUPPLY_TYPE_BATTERY;
	di->bat_desc.properties		= ds2760_battery_props;
	di->bat_desc.num_properties	= ARRAY_SIZE(ds2760_battery_props);
	di->bat_desc.get_property	= ds2760_battery_get_property;
	di->bat_desc.set_property	= ds2760_battery_set_property;
	di->bat_desc.property_is_ग_लिखोable =
				  ds2760_battery_property_is_ग_लिखोable;
	di->bat_desc.set_अक्षरged	= ds2760_battery_set_अक्षरged;
	di->bat_desc.बाह्यal_घातer_changed =
				  ds2760_battery_बाह्यal_घातer_changed;

	psy_cfg.drv_data = di;

	अगर (dev->of_node) अणु
		u32 पंचांगp;

		psy_cfg.of_node = dev->of_node;

		अगर (!of_property_पढ़ो_bool(dev->of_node, "maxim,pmod-enabled"))
			pmod_enabled = true;

		अगर (!of_property_पढ़ो_u32(dev->of_node,
					  "maxim,cache-time-ms", &पंचांगp))
			cache_समय = पंचांगp;

		अगर (!of_property_पढ़ो_u32(dev->of_node,
					  "rated-capacity-microamp-hours",
					  &पंचांगp))
			rated_capacity = पंचांगp / 10; /* property is in mAh */
	पूर्ण

	di->अक्षरge_status = POWER_SUPPLY_STATUS_UNKNOWN;

	sl->family_data = di;

	/* enable sleep mode feature */
	ds2760_battery_पढ़ो_status(di);
	status = di->raw[DS2760_STATUS_REG];
	अगर (pmod_enabled)
		status |= DS2760_STATUS_PMOD;
	अन्यथा
		status &= ~DS2760_STATUS_PMOD;

	ds2760_battery_ग_लिखो_status(di, status);

	/* set rated capacity from module param or device tree */
	अगर (rated_capacity)
		ds2760_battery_ग_लिखो_rated_capacity(di, rated_capacity);

	/* set current accumulator अगर given as parameter.
	 * this should only be करोne क्रम bootstrapping the value */
	अगर (current_accum)
		ds2760_battery_set_current_accum(di, current_accum);

	di->bat = घातer_supply_रेजिस्टर(dev, &di->bat_desc, &psy_cfg);
	अगर (IS_ERR(di->bat)) अणु
		dev_err(di->dev, "failed to register battery\n");
		retval = PTR_ERR(di->bat);
		जाओ batt_failed;
	पूर्ण

	INIT_DELAYED_WORK(&di->monitor_work, ds2760_battery_work);
	INIT_DELAYED_WORK(&di->set_अक्षरged_work,
			  ds2760_battery_set_अक्षरged_work);
	di->monitor_wqueue = alloc_ordered_workqueue(name, WQ_MEM_RECLAIM);
	अगर (!di->monitor_wqueue) अणु
		retval = -ESRCH;
		जाओ workqueue_failed;
	पूर्ण
	queue_delayed_work(di->monitor_wqueue, &di->monitor_work, HZ * 1);

	di->pm_notअगरier.notअगरier_call = ds2760_pm_notअगरier;
	रेजिस्टर_pm_notअगरier(&di->pm_notअगरier);

	जाओ success;

workqueue_failed:
	घातer_supply_unरेजिस्टर(di->bat);
batt_failed:
di_alloc_failed:
success:
	वापस retval;
पूर्ण

अटल व्योम w1_ds2760_हटाओ_slave(काष्ठा w1_slave *sl)
अणु
	काष्ठा ds2760_device_info *di = sl->family_data;

	unरेजिस्टर_pm_notअगरier(&di->pm_notअगरier);
	cancel_delayed_work_sync(&di->monitor_work);
	cancel_delayed_work_sync(&di->set_अक्षरged_work);
	destroy_workqueue(di->monitor_wqueue);
	घातer_supply_unरेजिस्टर(di->bat);
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id w1_ds2760_of_ids[] = अणु
	अणु .compatible = "maxim,ds2760" पूर्ण,
	अणुपूर्ण
पूर्ण;
#पूर्ण_अगर

अटल स्थिर काष्ठा w1_family_ops w1_ds2760_fops = अणु
	.add_slave	= w1_ds2760_add_slave,
	.हटाओ_slave	= w1_ds2760_हटाओ_slave,
	.groups		= w1_ds2760_groups,
पूर्ण;

अटल काष्ठा w1_family w1_ds2760_family = अणु
	.fid		= W1_FAMILY_DS2760,
	.fops		= &w1_ds2760_fops,
	.of_match_table	= of_match_ptr(w1_ds2760_of_ids),
पूर्ण;
module_w1_family(w1_ds2760_family);

MODULE_AUTHOR("Szabolcs Gyurko <szabolcs.gyurko@tlt.hu>, "
	      "Matt Reimer <mreimer@vpop.net>, "
	      "Anton Vorontsov <cbou@mail.ru>");
MODULE_DESCRIPTION("1-wire Driver Dallas 2760 battery monitor chip");
MODULE_LICENSE("GPL");
MODULE_ALIAS("w1-family-" __stringअगरy(W1_FAMILY_DS2760));
