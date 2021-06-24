<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/****************************************************************************
 * Driver क्रम Solarflare network controllers and boards
 * Copyright 2011-2013 Solarflare Communications Inc.
 */

#समावेश <linux/bitops.h>
#समावेश <linux/slab.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/स्थिति.स>

#समावेश "net_driver.h"
#समावेश "mcdi.h"
#समावेश "mcdi_pcol.h"
#समावेश "nic.h"

क्रमागत efx_hwmon_type अणु
	EFX_HWMON_UNKNOWN,
	EFX_HWMON_TEMP,         /* temperature */
	EFX_HWMON_COOL,         /* cooling device, probably a heatsink */
	EFX_HWMON_IN,		/* voltage */
	EFX_HWMON_CURR,		/* current */
	EFX_HWMON_POWER,	/* घातer */
	EFX_HWMON_TYPES_COUNT
पूर्ण;

अटल स्थिर अक्षर *स्थिर efx_hwmon_unit[EFX_HWMON_TYPES_COUNT] = अणु
	[EFX_HWMON_TEMP]  = " degC",
	[EFX_HWMON_COOL]  = " rpm", /* though nonsense क्रम a heatsink */
	[EFX_HWMON_IN]    = " mV",
	[EFX_HWMON_CURR]  = " mA",
	[EFX_HWMON_POWER] = " W",
पूर्ण;

अटल स्थिर काष्ठा अणु
	स्थिर अक्षर *label;
	क्रमागत efx_hwmon_type hwmon_type;
	पूर्णांक port;
पूर्ण efx_mcdi_sensor_type[] = अणु
#घोषणा SENSOR(name, label, hwmon_type, port)				\
	[MC_CMD_SENSOR_##name] = अणु label, EFX_HWMON_ ## hwmon_type, port पूर्ण
	SENSOR(CONTROLLER_TEMP,		"Controller board temp.",   TEMP,  -1),
	SENSOR(PHY_COMMON_TEMP,		"PHY temp.",		    TEMP,  -1),
	SENSOR(CONTROLLER_COOLING,	"Controller heat sink",	    COOL,  -1),
	SENSOR(PHY0_TEMP,		"PHY temp.",		    TEMP,  0),
	SENSOR(PHY0_COOLING,		"PHY heat sink",	    COOL,  0),
	SENSOR(PHY1_TEMP,		"PHY temp.",		    TEMP,  1),
	SENSOR(PHY1_COOLING,		"PHY heat sink",	    COOL,  1),
	SENSOR(IN_1V0,			"1.0V supply",		    IN,    -1),
	SENSOR(IN_1V2,			"1.2V supply",		    IN,    -1),
	SENSOR(IN_1V8,			"1.8V supply",		    IN,    -1),
	SENSOR(IN_2V5,			"2.5V supply",		    IN,    -1),
	SENSOR(IN_3V3,			"3.3V supply",		    IN,    -1),
	SENSOR(IN_12V0,			"12.0V supply",		    IN,    -1),
	SENSOR(IN_1V2A,			"1.2V analogue supply",	    IN,    -1),
	SENSOR(IN_VREF,			"Ref. voltage",		    IN,    -1),
	SENSOR(OUT_VAOE,		"AOE FPGA supply",	    IN,    -1),
	SENSOR(AOE_TEMP,		"AOE FPGA temp.",	    TEMP,  -1),
	SENSOR(PSU_AOE_TEMP,		"AOE regulator temp.",	    TEMP,  -1),
	SENSOR(PSU_TEMP,		"Controller regulator temp.",
								    TEMP,  -1),
	SENSOR(FAN_0,			"Fan 0",		    COOL,  -1),
	SENSOR(FAN_1,			"Fan 1",		    COOL,  -1),
	SENSOR(FAN_2,			"Fan 2",		    COOL,  -1),
	SENSOR(FAN_3,			"Fan 3",		    COOL,  -1),
	SENSOR(FAN_4,			"Fan 4",		    COOL,  -1),
	SENSOR(IN_VAOE,			"AOE input supply",	    IN,    -1),
	SENSOR(OUT_IAOE,		"AOE output current",	    CURR,  -1),
	SENSOR(IN_IAOE,			"AOE input current",	    CURR,  -1),
	SENSOR(NIC_POWER,		"Board power use",	    POWER, -1),
	SENSOR(IN_0V9,			"0.9V supply",		    IN,    -1),
	SENSOR(IN_I0V9,			"0.9V supply current",	    CURR,  -1),
	SENSOR(IN_I1V2,			"1.2V supply current",	    CURR,  -1),
	SENSOR(IN_0V9_ADC,		"0.9V supply (ext. ADC)",   IN,    -1),
	SENSOR(CONTROLLER_2_TEMP,	"Controller board temp. 2", TEMP,  -1),
	SENSOR(VREG_INTERNAL_TEMP,	"Regulator die temp.",	    TEMP,  -1),
	SENSOR(VREG_0V9_TEMP,		"0.9V regulator temp.",     TEMP,  -1),
	SENSOR(VREG_1V2_TEMP,		"1.2V regulator temp.",     TEMP,  -1),
	SENSOR(CONTROLLER_VPTAT,
			      "Controller PTAT voltage (int. ADC)", IN,    -1),
	SENSOR(CONTROLLER_INTERNAL_TEMP,
				 "Controller die temp. (int. ADC)", TEMP,  -1),
	SENSOR(CONTROLLER_VPTAT_EXTADC,
			      "Controller PTAT voltage (ext. ADC)", IN,    -1),
	SENSOR(CONTROLLER_INTERNAL_TEMP_EXTADC,
				 "Controller die temp. (ext. ADC)", TEMP,  -1),
	SENSOR(AMBIENT_TEMP,		"Ambient temp.",	    TEMP,  -1),
	SENSOR(AIRFLOW,			"Air flow raw",		    IN,    -1),
	SENSOR(VDD08D_VSS08D_CSR,	"0.9V die (int. ADC)",	    IN,    -1),
	SENSOR(VDD08D_VSS08D_CSR_EXTADC, "0.9V die (ext. ADC)",	    IN,    -1),
	SENSOR(HOTPOINT_TEMP,  "Controller board temp. (hotpoint)", TEMP,  -1),
#अघोषित SENSOR
पूर्ण;

अटल स्थिर अक्षर *स्थिर sensor_status_names[] = अणु
	[MC_CMD_SENSOR_STATE_OK] = "OK",
	[MC_CMD_SENSOR_STATE_WARNING] = "Warning",
	[MC_CMD_SENSOR_STATE_FATAL] = "Fatal",
	[MC_CMD_SENSOR_STATE_BROKEN] = "Device failure",
	[MC_CMD_SENSOR_STATE_NO_READING] = "No reading",
पूर्ण;

व्योम efx_mcdi_sensor_event(काष्ठा efx_nic *efx, efx_qword_t *ev)
अणु
	अचिन्हित पूर्णांक type, state, value;
	क्रमागत efx_hwmon_type hwmon_type = EFX_HWMON_UNKNOWN;
	स्थिर अक्षर *name = शून्य, *state_txt, *unit;

	type = EFX_QWORD_FIELD(*ev, MCDI_EVENT_SENSOREVT_MONITOR);
	state = EFX_QWORD_FIELD(*ev, MCDI_EVENT_SENSOREVT_STATE);
	value = EFX_QWORD_FIELD(*ev, MCDI_EVENT_SENSOREVT_VALUE);

	/* Deal gracefully with the board having more drivers than we
	 * know about, but करो not expect new sensor states. */
	अगर (type < ARRAY_SIZE(efx_mcdi_sensor_type)) अणु
		name = efx_mcdi_sensor_type[type].label;
		hwmon_type = efx_mcdi_sensor_type[type].hwmon_type;
	पूर्ण
	अगर (!name)
		name = "No sensor name available";
	EFX_WARN_ON_PARANOID(state >= ARRAY_SIZE(sensor_status_names));
	state_txt = sensor_status_names[state];
	EFX_WARN_ON_PARANOID(hwmon_type >= EFX_HWMON_TYPES_COUNT);
	unit = efx_hwmon_unit[hwmon_type];
	अगर (!unit)
		unit = "";

	netअगर_err(efx, hw, efx->net_dev,
		  "Sensor %d (%s) reports condition '%s' for value %d%s\n",
		  type, name, state_txt, value, unit);
पूर्ण

#अगर_घोषित CONFIG_SFC_MCDI_MON

काष्ठा efx_mcdi_mon_attribute अणु
	काष्ठा device_attribute dev_attr;
	अचिन्हित पूर्णांक index;
	अचिन्हित पूर्णांक type;
	क्रमागत efx_hwmon_type hwmon_type;
	अचिन्हित पूर्णांक limit_value;
	अक्षर name[12];
पूर्ण;

अटल पूर्णांक efx_mcdi_mon_update(काष्ठा efx_nic *efx)
अणु
	काष्ठा efx_mcdi_mon *hwmon = efx_mcdi_mon(efx);
	MCDI_DECLARE_BUF(inbuf, MC_CMD_READ_SENSORS_EXT_IN_LEN);
	पूर्णांक rc;

	MCDI_SET_QWORD(inbuf, READ_SENSORS_EXT_IN_DMA_ADDR,
		       hwmon->dma_buf.dma_addr);
	MCDI_SET_DWORD(inbuf, READ_SENSORS_EXT_IN_LENGTH, hwmon->dma_buf.len);

	rc = efx_mcdi_rpc(efx, MC_CMD_READ_SENSORS,
			  inbuf, माप(inbuf), शून्य, 0, शून्य);
	अगर (rc == 0)
		hwmon->last_update = jअगरfies;
	वापस rc;
पूर्ण

अटल पूर्णांक efx_mcdi_mon_get_entry(काष्ठा device *dev, अचिन्हित पूर्णांक index,
				  efx_dword_t *entry)
अणु
	काष्ठा efx_nic *efx = dev_get_drvdata(dev->parent);
	काष्ठा efx_mcdi_mon *hwmon = efx_mcdi_mon(efx);
	पूर्णांक rc;

	BUILD_BUG_ON(MC_CMD_READ_SENSORS_OUT_LEN != 0);

	mutex_lock(&hwmon->update_lock);

	/* Use cached value अगर last update was < 1 s ago */
	अगर (समय_beक्रमe(jअगरfies, hwmon->last_update + HZ))
		rc = 0;
	अन्यथा
		rc = efx_mcdi_mon_update(efx);

	/* Copy out the requested entry */
	*entry = ((efx_dword_t *)hwmon->dma_buf.addr)[index];

	mutex_unlock(&hwmon->update_lock);

	वापस rc;
पूर्ण

अटल sमाप_प्रकार efx_mcdi_mon_show_value(काष्ठा device *dev,
				       काष्ठा device_attribute *attr,
				       अक्षर *buf)
अणु
	काष्ठा efx_mcdi_mon_attribute *mon_attr =
		container_of(attr, काष्ठा efx_mcdi_mon_attribute, dev_attr);
	efx_dword_t entry;
	अचिन्हित पूर्णांक value, state;
	पूर्णांक rc;

	rc = efx_mcdi_mon_get_entry(dev, mon_attr->index, &entry);
	अगर (rc)
		वापस rc;

	state = EFX_DWORD_FIELD(entry, MC_CMD_SENSOR_VALUE_ENTRY_TYPEDEF_STATE);
	अगर (state == MC_CMD_SENSOR_STATE_NO_READING)
		वापस -EBUSY;

	value = EFX_DWORD_FIELD(entry, MC_CMD_SENSOR_VALUE_ENTRY_TYPEDEF_VALUE);

	चयन (mon_attr->hwmon_type) अणु
	हाल EFX_HWMON_TEMP:
		/* Convert temperature from degrees to milli-degrees Celsius */
		value *= 1000;
		अवरोध;
	हाल EFX_HWMON_POWER:
		/* Convert घातer from watts to microwatts */
		value *= 1000000;
		अवरोध;
	शेष:
		/* No conversion needed */
		अवरोध;
	पूर्ण

	वापस प्र_लिखो(buf, "%u\n", value);
पूर्ण

अटल sमाप_प्रकार efx_mcdi_mon_show_limit(काष्ठा device *dev,
				       काष्ठा device_attribute *attr,
				       अक्षर *buf)
अणु
	काष्ठा efx_mcdi_mon_attribute *mon_attr =
		container_of(attr, काष्ठा efx_mcdi_mon_attribute, dev_attr);
	अचिन्हित पूर्णांक value;

	value = mon_attr->limit_value;

	चयन (mon_attr->hwmon_type) अणु
	हाल EFX_HWMON_TEMP:
		/* Convert temperature from degrees to milli-degrees Celsius */
		value *= 1000;
		अवरोध;
	हाल EFX_HWMON_POWER:
		/* Convert घातer from watts to microwatts */
		value *= 1000000;
		अवरोध;
	शेष:
		/* No conversion needed */
		अवरोध;
	पूर्ण

	वापस प्र_लिखो(buf, "%u\n", value);
पूर्ण

अटल sमाप_प्रकार efx_mcdi_mon_show_alarm(काष्ठा device *dev,
				       काष्ठा device_attribute *attr,
				       अक्षर *buf)
अणु
	काष्ठा efx_mcdi_mon_attribute *mon_attr =
		container_of(attr, काष्ठा efx_mcdi_mon_attribute, dev_attr);
	efx_dword_t entry;
	पूर्णांक state;
	पूर्णांक rc;

	rc = efx_mcdi_mon_get_entry(dev, mon_attr->index, &entry);
	अगर (rc)
		वापस rc;

	state = EFX_DWORD_FIELD(entry, MC_CMD_SENSOR_VALUE_ENTRY_TYPEDEF_STATE);
	वापस प्र_लिखो(buf, "%d\n", state != MC_CMD_SENSOR_STATE_OK);
पूर्ण

अटल sमाप_प्रकार efx_mcdi_mon_show_label(काष्ठा device *dev,
				       काष्ठा device_attribute *attr,
				       अक्षर *buf)
अणु
	काष्ठा efx_mcdi_mon_attribute *mon_attr =
		container_of(attr, काष्ठा efx_mcdi_mon_attribute, dev_attr);
	वापस प्र_लिखो(buf, "%s\n",
		       efx_mcdi_sensor_type[mon_attr->type].label);
पूर्ण

अटल व्योम
efx_mcdi_mon_add_attr(काष्ठा efx_nic *efx, स्थिर अक्षर *name,
		      sमाप_प्रकार (*पढ़ोer)(काष्ठा device *,
					काष्ठा device_attribute *, अक्षर *),
		      अचिन्हित पूर्णांक index, अचिन्हित पूर्णांक type,
		      अचिन्हित पूर्णांक limit_value)
अणु
	काष्ठा efx_mcdi_mon *hwmon = efx_mcdi_mon(efx);
	काष्ठा efx_mcdi_mon_attribute *attr = &hwmon->attrs[hwmon->n_attrs];

	strlcpy(attr->name, name, माप(attr->name));
	attr->index = index;
	attr->type = type;
	अगर (type < ARRAY_SIZE(efx_mcdi_sensor_type))
		attr->hwmon_type = efx_mcdi_sensor_type[type].hwmon_type;
	अन्यथा
		attr->hwmon_type = EFX_HWMON_UNKNOWN;
	attr->limit_value = limit_value;
	sysfs_attr_init(&attr->dev_attr.attr);
	attr->dev_attr.attr.name = attr->name;
	attr->dev_attr.attr.mode = 0444;
	attr->dev_attr.show = पढ़ोer;
	hwmon->group.attrs[hwmon->n_attrs++] = &attr->dev_attr.attr;
पूर्ण

पूर्णांक efx_mcdi_mon_probe(काष्ठा efx_nic *efx)
अणु
	अचिन्हित पूर्णांक n_temp = 0, n_cool = 0, n_in = 0, n_curr = 0, n_घातer = 0;
	काष्ठा efx_mcdi_mon *hwmon = efx_mcdi_mon(efx);
	MCDI_DECLARE_BUF(inbuf, MC_CMD_SENSOR_INFO_EXT_IN_LEN);
	MCDI_DECLARE_BUF(outbuf, MC_CMD_SENSOR_INFO_OUT_LENMAX);
	अचिन्हित पूर्णांक n_pages, n_sensors, n_attrs, page;
	माप_प्रकार outlen;
	अक्षर name[12];
	u32 mask;
	पूर्णांक rc, i, j, type;

	/* Find out how many sensors are present */
	n_sensors = 0;
	page = 0;
	करो अणु
		MCDI_SET_DWORD(inbuf, SENSOR_INFO_EXT_IN_PAGE, page);

		rc = efx_mcdi_rpc(efx, MC_CMD_SENSOR_INFO, inbuf, माप(inbuf),
				  outbuf, माप(outbuf), &outlen);
		अगर (rc)
			वापस rc;
		अगर (outlen < MC_CMD_SENSOR_INFO_OUT_LENMIN)
			वापस -EIO;

		mask = MCDI_DWORD(outbuf, SENSOR_INFO_OUT_MASK);
		n_sensors += hweight32(mask & ~(1 << MC_CMD_SENSOR_PAGE0_NEXT));
		++page;
	पूर्ण जबतक (mask & (1 << MC_CMD_SENSOR_PAGE0_NEXT));
	n_pages = page;

	/* Don't create a device अगर there are none */
	अगर (n_sensors == 0)
		वापस 0;

	rc = efx_nic_alloc_buffer(
		efx, &hwmon->dma_buf,
		n_sensors * MC_CMD_SENSOR_VALUE_ENTRY_TYPEDEF_LEN,
		GFP_KERNEL);
	अगर (rc)
		वापस rc;

	mutex_init(&hwmon->update_lock);
	efx_mcdi_mon_update(efx);

	/* Allocate space क्रम the maximum possible number of
	 * attributes क्रम this set of sensors:
	 * value, min, max, crit, alarm and label क्रम each sensor.
	 */
	n_attrs = 6 * n_sensors;
	hwmon->attrs = kसुस्मृति(n_attrs, माप(*hwmon->attrs), GFP_KERNEL);
	अगर (!hwmon->attrs) अणु
		rc = -ENOMEM;
		जाओ fail;
	पूर्ण
	hwmon->group.attrs = kसुस्मृति(n_attrs + 1, माप(काष्ठा attribute *),
				     GFP_KERNEL);
	अगर (!hwmon->group.attrs) अणु
		rc = -ENOMEM;
		जाओ fail;
	पूर्ण

	क्रम (i = 0, j = -1, type = -1; ; i++) अणु
		क्रमागत efx_hwmon_type hwmon_type;
		स्थिर अक्षर *hwmon_prefix;
		अचिन्हित hwmon_index;
		u16 min1, max1, min2, max2;

		/* Find next sensor type or निकास अगर there is none */
		करो अणु
			type++;

			अगर ((type % 32) == 0) अणु
				page = type / 32;
				j = -1;
				अगर (page == n_pages)
					जाओ hwmon_रेजिस्टर;

				MCDI_SET_DWORD(inbuf, SENSOR_INFO_EXT_IN_PAGE,
					       page);
				rc = efx_mcdi_rpc(efx, MC_CMD_SENSOR_INFO,
						  inbuf, माप(inbuf),
						  outbuf, माप(outbuf),
						  &outlen);
				अगर (rc)
					जाओ fail;
				अगर (outlen < MC_CMD_SENSOR_INFO_OUT_LENMIN) अणु
					rc = -EIO;
					जाओ fail;
				पूर्ण

				mask = (MCDI_DWORD(outbuf,
						   SENSOR_INFO_OUT_MASK) &
					~(1 << MC_CMD_SENSOR_PAGE0_NEXT));

				/* Check again क्रम लघु response */
				अगर (outlen <
				    MC_CMD_SENSOR_INFO_OUT_LEN(hweight32(mask))) अणु
					rc = -EIO;
					जाओ fail;
				पूर्ण
			पूर्ण
		पूर्ण जबतक (!(mask & (1 << type % 32)));
		j++;

		अगर (type < ARRAY_SIZE(efx_mcdi_sensor_type)) अणु
			hwmon_type = efx_mcdi_sensor_type[type].hwmon_type;

			/* Skip sensors specअगरic to a dअगरferent port */
			अगर (hwmon_type != EFX_HWMON_UNKNOWN &&
			    efx_mcdi_sensor_type[type].port >= 0 &&
			    efx_mcdi_sensor_type[type].port !=
			    efx_port_num(efx))
				जारी;
		पूर्ण अन्यथा अणु
			hwmon_type = EFX_HWMON_UNKNOWN;
		पूर्ण

		चयन (hwmon_type) अणु
		हाल EFX_HWMON_TEMP:
			hwmon_prefix = "temp";
			hwmon_index = ++n_temp; /* 1-based */
			अवरोध;
		हाल EFX_HWMON_COOL:
			/* This is likely to be a heatsink, but there
			 * is no convention क्रम representing cooling
			 * devices other than fans.
			 */
			hwmon_prefix = "fan";
			hwmon_index = ++n_cool; /* 1-based */
			अवरोध;
		शेष:
			hwmon_prefix = "in";
			hwmon_index = n_in++; /* 0-based */
			अवरोध;
		हाल EFX_HWMON_CURR:
			hwmon_prefix = "curr";
			hwmon_index = ++n_curr; /* 1-based */
			अवरोध;
		हाल EFX_HWMON_POWER:
			hwmon_prefix = "power";
			hwmon_index = ++n_घातer; /* 1-based */
			अवरोध;
		पूर्ण

		min1 = MCDI_ARRAY_FIELD(outbuf, SENSOR_ENTRY,
					SENSOR_INFO_ENTRY, j, MIN1);
		max1 = MCDI_ARRAY_FIELD(outbuf, SENSOR_ENTRY,
					SENSOR_INFO_ENTRY, j, MAX1);
		min2 = MCDI_ARRAY_FIELD(outbuf, SENSOR_ENTRY,
					SENSOR_INFO_ENTRY, j, MIN2);
		max2 = MCDI_ARRAY_FIELD(outbuf, SENSOR_ENTRY,
					SENSOR_INFO_ENTRY, j, MAX2);

		अगर (min1 != max1) अणु
			snम_लिखो(name, माप(name), "%s%u_input",
				 hwmon_prefix, hwmon_index);
			efx_mcdi_mon_add_attr(
				efx, name, efx_mcdi_mon_show_value, i, type, 0);

			अगर (hwmon_type != EFX_HWMON_POWER) अणु
				snम_लिखो(name, माप(name), "%s%u_min",
					 hwmon_prefix, hwmon_index);
				efx_mcdi_mon_add_attr(
					efx, name, efx_mcdi_mon_show_limit,
					i, type, min1);
			पूर्ण

			snम_लिखो(name, माप(name), "%s%u_max",
				 hwmon_prefix, hwmon_index);
			efx_mcdi_mon_add_attr(
				efx, name, efx_mcdi_mon_show_limit,
				i, type, max1);

			अगर (min2 != max2) अणु
				/* Assume max2 is critical value.
				 * But we have no good way to expose min2.
				 */
				snम_लिखो(name, माप(name), "%s%u_crit",
					 hwmon_prefix, hwmon_index);
				efx_mcdi_mon_add_attr(
					efx, name, efx_mcdi_mon_show_limit,
					i, type, max2);
			पूर्ण
		पूर्ण

		snम_लिखो(name, माप(name), "%s%u_alarm",
			 hwmon_prefix, hwmon_index);
		efx_mcdi_mon_add_attr(
			efx, name, efx_mcdi_mon_show_alarm, i, type, 0);

		अगर (type < ARRAY_SIZE(efx_mcdi_sensor_type) &&
		    efx_mcdi_sensor_type[type].label) अणु
			snम_लिखो(name, माप(name), "%s%u_label",
				 hwmon_prefix, hwmon_index);
			efx_mcdi_mon_add_attr(
				efx, name, efx_mcdi_mon_show_label, i, type, 0);
		पूर्ण
	पूर्ण

hwmon_रेजिस्टर:
	hwmon->groups[0] = &hwmon->group;
	hwmon->device = hwmon_device_रेजिस्टर_with_groups(&efx->pci_dev->dev,
							  KBUILD_MODNAME, शून्य,
							  hwmon->groups);
	अगर (IS_ERR(hwmon->device)) अणु
		rc = PTR_ERR(hwmon->device);
		जाओ fail;
	पूर्ण

	वापस 0;

fail:
	efx_mcdi_mon_हटाओ(efx);
	वापस rc;
पूर्ण

व्योम efx_mcdi_mon_हटाओ(काष्ठा efx_nic *efx)
अणु
	काष्ठा efx_mcdi_mon *hwmon = efx_mcdi_mon(efx);

	अगर (hwmon->device)
		hwmon_device_unरेजिस्टर(hwmon->device);
	kमुक्त(hwmon->attrs);
	kमुक्त(hwmon->group.attrs);
	efx_nic_मुक्त_buffer(efx, &hwmon->dma_buf);
पूर्ण

#पूर्ण_अगर /* CONFIG_SFC_MCDI_MON */
