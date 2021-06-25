<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/* Copyright (c) 2018 Mellanox Technologies. All rights reserved */

#समावेश <linux/kernel.h>
#समावेश <linux/err.h>
#समावेश <linux/sfp.h>

#समावेश "core.h"
#समावेश "core_env.h"
#समावेश "item.h"
#समावेश "reg.h"

काष्ठा mlxsw_env_module_info अणु
	u64 module_overheat_counter;
	bool is_overheat;
पूर्ण;

काष्ठा mlxsw_env अणु
	काष्ठा mlxsw_core *core;
	u8 module_count;
	spinlock_t module_info_lock; /* Protects 'module_info'. */
	काष्ठा mlxsw_env_module_info module_info[];
पूर्ण;

अटल पूर्णांक mlxsw_env_validate_cable_ident(काष्ठा mlxsw_core *core, पूर्णांक id,
					  bool *qsfp, bool *cmis)
अणु
	अक्षर eeprom_पंचांगp[MLXSW_REG_MCIA_EEPROM_SIZE];
	अक्षर mcia_pl[MLXSW_REG_MCIA_LEN];
	u8 ident;
	पूर्णांक err;

	mlxsw_reg_mcia_pack(mcia_pl, id, 0, MLXSW_REG_MCIA_PAGE0_LO_OFF, 0, 1,
			    MLXSW_REG_MCIA_I2C_ADDR_LOW);
	err = mlxsw_reg_query(core, MLXSW_REG(mcia), mcia_pl);
	अगर (err)
		वापस err;
	mlxsw_reg_mcia_eeprom_स_नकल_from(mcia_pl, eeprom_पंचांगp);
	ident = eeprom_पंचांगp[0];
	*cmis = false;
	चयन (ident) अणु
	हाल MLXSW_REG_MCIA_EEPROM_MODULE_INFO_ID_SFP:
		*qsfp = false;
		अवरोध;
	हाल MLXSW_REG_MCIA_EEPROM_MODULE_INFO_ID_QSFP:
	हाल MLXSW_REG_MCIA_EEPROM_MODULE_INFO_ID_QSFP_PLUS:
	हाल MLXSW_REG_MCIA_EEPROM_MODULE_INFO_ID_QSFP28:
		*qsfp = true;
		अवरोध;
	हाल MLXSW_REG_MCIA_EEPROM_MODULE_INFO_ID_QSFP_DD:
		*qsfp = true;
		*cmis = true;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
mlxsw_env_query_module_eeprom(काष्ठा mlxsw_core *mlxsw_core, पूर्णांक module,
			      u16 offset, u16 size, व्योम *data,
			      bool qsfp, अचिन्हित पूर्णांक *p_पढ़ो_size)
अणु
	अक्षर eeprom_पंचांगp[MLXSW_REG_MCIA_EEPROM_SIZE];
	अक्षर mcia_pl[MLXSW_REG_MCIA_LEN];
	u16 i2c_addr;
	u8 page = 0;
	पूर्णांक status;
	पूर्णांक err;

	/* MCIA रेजिस्टर accepts buffer size <= 48. Page of size 128 should be
	 * पढ़ो by chunks of size 48, 48, 32. Align the size of the last chunk
	 * to aव्योम पढ़ोing after the end of the page.
	 */
	size = min_t(u16, size, MLXSW_REG_MCIA_EEPROM_SIZE);

	अगर (offset < MLXSW_REG_MCIA_EEPROM_PAGE_LENGTH &&
	    offset + size > MLXSW_REG_MCIA_EEPROM_PAGE_LENGTH)
		/* Cross pages पढ़ो, पढ़ो until offset 256 in low page */
		size = MLXSW_REG_MCIA_EEPROM_PAGE_LENGTH - offset;

	i2c_addr = MLXSW_REG_MCIA_I2C_ADDR_LOW;
	अगर (offset >= MLXSW_REG_MCIA_EEPROM_PAGE_LENGTH) अणु
		अगर (qsfp) अणु
			/* When पढ़ोing upper pages 1, 2 and 3 the offset
			 * starts at 128. Please refer to "QSFP+ Memory Map"
			 * figure in SFF-8436 specअगरication and to "CMIS Module
			 * Memory Map" figure in CMIS specअगरication क्रम
			 * graphical depiction.
			 */
			page = MLXSW_REG_MCIA_PAGE_GET(offset);
			offset -= MLXSW_REG_MCIA_EEPROM_UP_PAGE_LENGTH * page;
			अगर (offset + size > MLXSW_REG_MCIA_EEPROM_PAGE_LENGTH)
				size = MLXSW_REG_MCIA_EEPROM_PAGE_LENGTH - offset;
		पूर्ण अन्यथा अणु
			/* When पढ़ोing upper pages 1, 2 and 3 the offset
			 * starts at 0 and I2C high address is used. Please refer
			 * refer to "Memory Organization" figure in SFF-8472
			 * specअगरication क्रम graphical depiction.
			 */
			i2c_addr = MLXSW_REG_MCIA_I2C_ADDR_HIGH;
			offset -= MLXSW_REG_MCIA_EEPROM_PAGE_LENGTH;
		पूर्ण
	पूर्ण

	mlxsw_reg_mcia_pack(mcia_pl, module, 0, page, offset, size, i2c_addr);

	err = mlxsw_reg_query(mlxsw_core, MLXSW_REG(mcia), mcia_pl);
	अगर (err)
		वापस err;

	status = mlxsw_reg_mcia_status_get(mcia_pl);
	अगर (status)
		वापस -EIO;

	mlxsw_reg_mcia_eeprom_स_नकल_from(mcia_pl, eeprom_पंचांगp);
	स_नकल(data, eeprom_पंचांगp, size);
	*p_पढ़ो_size = size;

	वापस 0;
पूर्ण

पूर्णांक mlxsw_env_module_temp_thresholds_get(काष्ठा mlxsw_core *core, पूर्णांक module,
					 पूर्णांक off, पूर्णांक *temp)
अणु
	अक्षर eeprom_पंचांगp[MLXSW_REG_MCIA_EEPROM_SIZE];
	जोड़ अणु
		u8 buf[MLXSW_REG_MCIA_TH_ITEM_SIZE];
		u16 temp;
	पूर्ण temp_thresh;
	अक्षर mcia_pl[MLXSW_REG_MCIA_LEN] = अणु0पूर्ण;
	अक्षर mपंचांगp_pl[MLXSW_REG_MTMP_LEN];
	अचिन्हित पूर्णांक module_temp;
	bool qsfp, cmis;
	पूर्णांक page;
	पूर्णांक err;

	mlxsw_reg_mपंचांगp_pack(mपंचांगp_pl, MLXSW_REG_MTMP_MODULE_INDEX_MIN + module,
			    false, false);
	err = mlxsw_reg_query(core, MLXSW_REG(mपंचांगp), mपंचांगp_pl);
	अगर (err)
		वापस err;
	mlxsw_reg_mपंचांगp_unpack(mपंचांगp_pl, &module_temp, शून्य, शून्य);
	अगर (!module_temp) अणु
		*temp = 0;
		वापस 0;
	पूर्ण

	/* Read Free Side Device Temperature Thresholds from page 03h
	 * (MSB at lower byte address).
	 * Bytes:
	 * 128-129 - Temp High Alarm (SFP_TEMP_HIGH_ALARM);
	 * 130-131 - Temp Low Alarm (SFP_TEMP_LOW_ALARM);
	 * 132-133 - Temp High Warning (SFP_TEMP_HIGH_WARN);
	 * 134-135 - Temp Low Warning (SFP_TEMP_LOW_WARN);
	 */

	/* Validate module identअगरier value. */
	err = mlxsw_env_validate_cable_ident(core, module, &qsfp, &cmis);
	अगर (err)
		वापस err;

	अगर (qsfp) अणु
		/* For QSFP/CMIS module-defined thresholds are located in page
		 * 02h, otherwise in page 03h.
		 */
		अगर (cmis)
			page = MLXSW_REG_MCIA_TH_PAGE_CMIS_NUM;
		अन्यथा
			page = MLXSW_REG_MCIA_TH_PAGE_NUM;
		mlxsw_reg_mcia_pack(mcia_pl, module, 0, page,
				    MLXSW_REG_MCIA_TH_PAGE_OFF + off,
				    MLXSW_REG_MCIA_TH_ITEM_SIZE,
				    MLXSW_REG_MCIA_I2C_ADDR_LOW);
	पूर्ण अन्यथा अणु
		mlxsw_reg_mcia_pack(mcia_pl, module, 0,
				    MLXSW_REG_MCIA_PAGE0_LO,
				    off, MLXSW_REG_MCIA_TH_ITEM_SIZE,
				    MLXSW_REG_MCIA_I2C_ADDR_HIGH);
	पूर्ण

	err = mlxsw_reg_query(core, MLXSW_REG(mcia), mcia_pl);
	अगर (err)
		वापस err;

	mlxsw_reg_mcia_eeprom_स_नकल_from(mcia_pl, eeprom_पंचांगp);
	स_नकल(temp_thresh.buf, eeprom_पंचांगp, MLXSW_REG_MCIA_TH_ITEM_SIZE);
	*temp = temp_thresh.temp * 1000;

	वापस 0;
पूर्ण

पूर्णांक mlxsw_env_get_module_info(काष्ठा mlxsw_core *mlxsw_core, पूर्णांक module,
			      काष्ठा ethtool_modinfo *modinfo)
अणु
	u8 module_info[MLXSW_REG_MCIA_EEPROM_MODULE_INFO_SIZE];
	u16 offset = MLXSW_REG_MCIA_EEPROM_MODULE_INFO_SIZE;
	u8 module_rev_id, module_id, diag_mon;
	अचिन्हित पूर्णांक पढ़ो_size;
	पूर्णांक err;

	err = mlxsw_env_query_module_eeprom(mlxsw_core, module, 0, offset,
					    module_info, false, &पढ़ो_size);
	अगर (err)
		वापस err;

	अगर (पढ़ो_size < offset)
		वापस -EIO;

	module_rev_id = module_info[MLXSW_REG_MCIA_EEPROM_MODULE_INFO_REV_ID];
	module_id = module_info[MLXSW_REG_MCIA_EEPROM_MODULE_INFO_ID];

	चयन (module_id) अणु
	हाल MLXSW_REG_MCIA_EEPROM_MODULE_INFO_ID_QSFP:
		modinfo->type       = ETH_MODULE_SFF_8436;
		modinfo->eeprom_len = ETH_MODULE_SFF_8436_MAX_LEN;
		अवरोध;
	हाल MLXSW_REG_MCIA_EEPROM_MODULE_INFO_ID_QSFP_PLUS:
	हाल MLXSW_REG_MCIA_EEPROM_MODULE_INFO_ID_QSFP28:
		अगर (module_id == MLXSW_REG_MCIA_EEPROM_MODULE_INFO_ID_QSFP28 ||
		    module_rev_id >=
		    MLXSW_REG_MCIA_EEPROM_MODULE_INFO_REV_ID_8636) अणु
			modinfo->type       = ETH_MODULE_SFF_8636;
			modinfo->eeprom_len = ETH_MODULE_SFF_8636_MAX_LEN;
		पूर्ण अन्यथा अणु
			modinfo->type       = ETH_MODULE_SFF_8436;
			modinfo->eeprom_len = ETH_MODULE_SFF_8436_MAX_LEN;
		पूर्ण
		अवरोध;
	हाल MLXSW_REG_MCIA_EEPROM_MODULE_INFO_ID_SFP:
		/* Verअगरy अगर transceiver provides diagnostic monitoring page */
		err = mlxsw_env_query_module_eeprom(mlxsw_core, module,
						    SFP_DIAGMON, 1, &diag_mon,
						    false, &पढ़ो_size);
		अगर (err)
			वापस err;

		अगर (पढ़ो_size < 1)
			वापस -EIO;

		modinfo->type       = ETH_MODULE_SFF_8472;
		अगर (diag_mon)
			modinfo->eeprom_len = ETH_MODULE_SFF_8472_LEN;
		अन्यथा
			modinfo->eeprom_len = ETH_MODULE_SFF_8472_LEN / 2;
		अवरोध;
	हाल MLXSW_REG_MCIA_EEPROM_MODULE_INFO_ID_QSFP_DD:
		/* Use SFF_8636 as base type. ethtool should recognize specअगरic
		 * type through the identअगरier value.
		 */
		modinfo->type       = ETH_MODULE_SFF_8636;
		/* Verअगरy अगर module EEPROM is a flat memory. In हाल of flat
		 * memory only page 00h (0-255 bytes) can be पढ़ो. Otherwise
		 * upper pages 01h and 02h can also be पढ़ो. Upper pages 10h
		 * and 11h are currently not supported by the driver.
		 */
		अगर (module_info[MLXSW_REG_MCIA_EEPROM_MODULE_INFO_TYPE_ID] &
		    MLXSW_REG_MCIA_EEPROM_CMIS_FLAT_MEMORY)
			modinfo->eeprom_len = ETH_MODULE_SFF_8636_LEN;
		अन्यथा
			modinfo->eeprom_len = ETH_MODULE_SFF_8472_LEN;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(mlxsw_env_get_module_info);

पूर्णांक mlxsw_env_get_module_eeprom(काष्ठा net_device *netdev,
				काष्ठा mlxsw_core *mlxsw_core, पूर्णांक module,
				काष्ठा ethtool_eeprom *ee, u8 *data)
अणु
	पूर्णांक offset = ee->offset;
	अचिन्हित पूर्णांक पढ़ो_size;
	bool qsfp, cmis;
	पूर्णांक i = 0;
	पूर्णांक err;

	अगर (!ee->len)
		वापस -EINVAL;

	स_रखो(data, 0, ee->len);
	/* Validate module identअगरier value. */
	err = mlxsw_env_validate_cable_ident(mlxsw_core, module, &qsfp, &cmis);
	अगर (err)
		वापस err;

	जबतक (i < ee->len) अणु
		err = mlxsw_env_query_module_eeprom(mlxsw_core, module, offset,
						    ee->len - i, data + i,
						    qsfp, &पढ़ो_size);
		अगर (err) अणु
			netdev_err(netdev, "Eeprom query failed\n");
			वापस err;
		पूर्ण

		i += पढ़ो_size;
		offset += पढ़ो_size;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(mlxsw_env_get_module_eeprom);

अटल पूर्णांक mlxsw_env_module_has_temp_sensor(काष्ठा mlxsw_core *mlxsw_core,
					    u8 module,
					    bool *p_has_temp_sensor)
अणु
	अक्षर mtbr_pl[MLXSW_REG_MTBR_LEN];
	u16 temp;
	पूर्णांक err;

	mlxsw_reg_mtbr_pack(mtbr_pl, MLXSW_REG_MTBR_BASE_MODULE_INDEX + module,
			    1);
	err = mlxsw_reg_query(mlxsw_core, MLXSW_REG(mtbr), mtbr_pl);
	अगर (err)
		वापस err;

	mlxsw_reg_mtbr_temp_unpack(mtbr_pl, 0, &temp, शून्य);

	चयन (temp) अणु
	हाल MLXSW_REG_MTBR_BAD_SENS_INFO:
	हाल MLXSW_REG_MTBR_NO_CONN:
	हाल MLXSW_REG_MTBR_NO_TEMP_SENS:
	हाल MLXSW_REG_MTBR_INDEX_NA:
		*p_has_temp_sensor = false;
		अवरोध;
	शेष:
		*p_has_temp_sensor = temp ? true : false;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक mlxsw_env_temp_event_set(काष्ठा mlxsw_core *mlxsw_core,
				    u16 sensor_index, bool enable)
अणु
	अक्षर mपंचांगp_pl[MLXSW_REG_MTMP_LEN] = अणु0पूर्ण;
	क्रमागत mlxsw_reg_mपंचांगp_tee tee;
	पूर्णांक err, threshold_hi;

	mlxsw_reg_mपंचांगp_sensor_index_set(mपंचांगp_pl, sensor_index);
	err = mlxsw_reg_query(mlxsw_core, MLXSW_REG(mपंचांगp), mपंचांगp_pl);
	अगर (err)
		वापस err;

	अगर (enable) अणु
		err = mlxsw_env_module_temp_thresholds_get(mlxsw_core,
							   sensor_index -
							   MLXSW_REG_MTMP_MODULE_INDEX_MIN,
							   SFP_TEMP_HIGH_WARN,
							   &threshold_hi);
		/* In हाल it is not possible to query the module's threshold,
		 * use the शेष value.
		 */
		अगर (err)
			threshold_hi = MLXSW_REG_MTMP_THRESH_HI;
		अन्यथा
			/* mlxsw_env_module_temp_thresholds_get() multiplies
			 * Celsius degrees by 1000 whereas MTMP expects
			 * temperature in 0.125 Celsius degrees units.
			 * Convert threshold_hi to correct units.
			 */
			threshold_hi = threshold_hi / 1000 * 8;

		mlxsw_reg_mपंचांगp_temperature_threshold_hi_set(mपंचांगp_pl, threshold_hi);
		mlxsw_reg_mपंचांगp_temperature_threshold_lo_set(mपंचांगp_pl, threshold_hi -
							    MLXSW_REG_MTMP_HYSTERESIS_TEMP);
	पूर्ण
	tee = enable ? MLXSW_REG_MTMP_TEE_GENERATE_EVENT : MLXSW_REG_MTMP_TEE_NO_EVENT;
	mlxsw_reg_mपंचांगp_tee_set(mपंचांगp_pl, tee);
	वापस mlxsw_reg_ग_लिखो(mlxsw_core, MLXSW_REG(mपंचांगp), mपंचांगp_pl);
पूर्ण

अटल पूर्णांक mlxsw_env_module_temp_event_enable(काष्ठा mlxsw_core *mlxsw_core,
					      u8 module_count)
अणु
	पूर्णांक i, err, sensor_index;
	bool has_temp_sensor;

	क्रम (i = 0; i < module_count; i++) अणु
		err = mlxsw_env_module_has_temp_sensor(mlxsw_core, i,
						       &has_temp_sensor);
		अगर (err)
			वापस err;

		अगर (!has_temp_sensor)
			जारी;

		sensor_index = i + MLXSW_REG_MTMP_MODULE_INDEX_MIN;
		err = mlxsw_env_temp_event_set(mlxsw_core, sensor_index, true);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम mlxsw_env_mtwe_event_func(स्थिर काष्ठा mlxsw_reg_info *reg,
				      अक्षर *mtwe_pl, व्योम *priv)
अणु
	काष्ठा mlxsw_env *mlxsw_env = priv;
	पूर्णांक i, sensor_warning;
	bool is_overheat;

	क्रम (i = 0; i < mlxsw_env->module_count; i++) अणु
		/* 64-127 of sensor_index are mapped to the port modules
		 * sequentially (module 0 is mapped to sensor_index 64,
		 * module 1 to sensor_index 65 and so on)
		 */
		sensor_warning =
			mlxsw_reg_mtwe_sensor_warning_get(mtwe_pl,
							  i + MLXSW_REG_MTMP_MODULE_INDEX_MIN);
		spin_lock(&mlxsw_env->module_info_lock);
		is_overheat =
			mlxsw_env->module_info[i].is_overheat;

		अगर ((is_overheat && sensor_warning) ||
		    (!is_overheat && !sensor_warning)) अणु
			/* Current state is "warning" and MTWE still reports
			 * warning OR current state in "no warning" and MTWE
			 * करोes not report warning.
			 */
			spin_unlock(&mlxsw_env->module_info_lock);
			जारी;
		पूर्ण अन्यथा अगर (is_overheat && !sensor_warning) अणु
			/* MTWE reports "no warning", turn is_overheat off.
			 */
			mlxsw_env->module_info[i].is_overheat = false;
			spin_unlock(&mlxsw_env->module_info_lock);
		पूर्ण अन्यथा अणु
			/* Current state is "no warning" and MTWE reports
			 * "warning", increase the counter and turn is_overheat
			 * on.
			 */
			mlxsw_env->module_info[i].is_overheat = true;
			mlxsw_env->module_info[i].module_overheat_counter++;
			spin_unlock(&mlxsw_env->module_info_lock);
		पूर्ण
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा mlxsw_listener mlxsw_env_temp_warn_listener =
	MLXSW_EVENTL(mlxsw_env_mtwe_event_func, MTWE, MTWE);

अटल पूर्णांक mlxsw_env_temp_warn_event_रेजिस्टर(काष्ठा mlxsw_core *mlxsw_core)
अणु
	काष्ठा mlxsw_env *mlxsw_env = mlxsw_core_env(mlxsw_core);

	अगर (!mlxsw_core_temp_warn_enabled(mlxsw_core))
		वापस 0;

	वापस mlxsw_core_trap_रेजिस्टर(mlxsw_core,
					&mlxsw_env_temp_warn_listener,
					mlxsw_env);
पूर्ण

अटल व्योम mlxsw_env_temp_warn_event_unरेजिस्टर(काष्ठा mlxsw_env *mlxsw_env)
अणु
	अगर (!mlxsw_core_temp_warn_enabled(mlxsw_env->core))
		वापस;

	mlxsw_core_trap_unरेजिस्टर(mlxsw_env->core,
				   &mlxsw_env_temp_warn_listener, mlxsw_env);
पूर्ण

काष्ठा mlxsw_env_module_plug_unplug_event अणु
	काष्ठा mlxsw_env *mlxsw_env;
	u8 module;
	काष्ठा work_काष्ठा work;
पूर्ण;

अटल व्योम mlxsw_env_pmpe_event_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mlxsw_env_module_plug_unplug_event *event;
	काष्ठा mlxsw_env *mlxsw_env;
	bool has_temp_sensor;
	u16 sensor_index;
	पूर्णांक err;

	event = container_of(work, काष्ठा mlxsw_env_module_plug_unplug_event,
			     work);
	mlxsw_env = event->mlxsw_env;

	spin_lock_bh(&mlxsw_env->module_info_lock);
	mlxsw_env->module_info[event->module].is_overheat = false;
	spin_unlock_bh(&mlxsw_env->module_info_lock);

	err = mlxsw_env_module_has_temp_sensor(mlxsw_env->core, event->module,
					       &has_temp_sensor);
	/* Do not disable events on modules without sensors or faulty sensors
	 * because FW वापसs errors.
	 */
	अगर (err)
		जाओ out;

	अगर (!has_temp_sensor)
		जाओ out;

	sensor_index = event->module + MLXSW_REG_MTMP_MODULE_INDEX_MIN;
	mlxsw_env_temp_event_set(mlxsw_env->core, sensor_index, true);

out:
	kमुक्त(event);
पूर्ण

अटल व्योम
mlxsw_env_pmpe_listener_func(स्थिर काष्ठा mlxsw_reg_info *reg, अक्षर *pmpe_pl,
			     व्योम *priv)
अणु
	काष्ठा mlxsw_env_module_plug_unplug_event *event;
	क्रमागत mlxsw_reg_pmpe_module_status module_status;
	u8 module = mlxsw_reg_pmpe_module_get(pmpe_pl);
	काष्ठा mlxsw_env *mlxsw_env = priv;

	अगर (WARN_ON_ONCE(module >= mlxsw_env->module_count))
		वापस;

	module_status = mlxsw_reg_pmpe_module_status_get(pmpe_pl);
	अगर (module_status != MLXSW_REG_PMPE_MODULE_STATUS_PLUGGED_ENABLED)
		वापस;

	event = kदो_स्मृति(माप(*event), GFP_ATOMIC);
	अगर (!event)
		वापस;

	event->mlxsw_env = mlxsw_env;
	event->module = module;
	INIT_WORK(&event->work, mlxsw_env_pmpe_event_work);
	mlxsw_core_schedule_work(&event->work);
पूर्ण

अटल स्थिर काष्ठा mlxsw_listener mlxsw_env_module_plug_listener =
	MLXSW_EVENTL(mlxsw_env_pmpe_listener_func, PMPE, PMPE);

अटल पूर्णांक
mlxsw_env_module_plug_event_रेजिस्टर(काष्ठा mlxsw_core *mlxsw_core)
अणु
	काष्ठा mlxsw_env *mlxsw_env = mlxsw_core_env(mlxsw_core);

	अगर (!mlxsw_core_temp_warn_enabled(mlxsw_core))
		वापस 0;

	वापस mlxsw_core_trap_रेजिस्टर(mlxsw_core,
					&mlxsw_env_module_plug_listener,
					mlxsw_env);
पूर्ण

अटल व्योम
mlxsw_env_module_plug_event_unरेजिस्टर(काष्ठा mlxsw_env *mlxsw_env)
अणु
	अगर (!mlxsw_core_temp_warn_enabled(mlxsw_env->core))
		वापस;

	mlxsw_core_trap_unरेजिस्टर(mlxsw_env->core,
				   &mlxsw_env_module_plug_listener,
				   mlxsw_env);
पूर्ण

अटल पूर्णांक
mlxsw_env_module_oper_state_event_enable(काष्ठा mlxsw_core *mlxsw_core,
					 u8 module_count)
अणु
	पूर्णांक i, err;

	क्रम (i = 0; i < module_count; i++) अणु
		अक्षर pmaos_pl[MLXSW_REG_PMAOS_LEN];

		mlxsw_reg_pmaos_pack(pmaos_pl, i,
				     MLXSW_REG_PMAOS_E_GENERATE_EVENT);
		err = mlxsw_reg_ग_लिखो(mlxsw_core, MLXSW_REG(pmaos), pmaos_pl);
		अगर (err)
			वापस err;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक
mlxsw_env_module_overheat_counter_get(काष्ठा mlxsw_core *mlxsw_core, u8 module,
				      u64 *p_counter)
अणु
	काष्ठा mlxsw_env *mlxsw_env = mlxsw_core_env(mlxsw_core);

	/* Prevent चयन driver from accessing uninitialized data. */
	अगर (!mlxsw_core_is_initialized(mlxsw_core)) अणु
		*p_counter = 0;
		वापस 0;
	पूर्ण

	अगर (WARN_ON_ONCE(module >= mlxsw_env->module_count))
		वापस -EINVAL;

	spin_lock_bh(&mlxsw_env->module_info_lock);
	*p_counter = mlxsw_env->module_info[module].module_overheat_counter;
	spin_unlock_bh(&mlxsw_env->module_info_lock);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(mlxsw_env_module_overheat_counter_get);

पूर्णांक mlxsw_env_init(काष्ठा mlxsw_core *mlxsw_core, काष्ठा mlxsw_env **p_env)
अणु
	अक्षर mgpir_pl[MLXSW_REG_MGPIR_LEN];
	काष्ठा mlxsw_env *env;
	u8 module_count;
	पूर्णांक err;

	mlxsw_reg_mgpir_pack(mgpir_pl);
	err = mlxsw_reg_query(mlxsw_core, MLXSW_REG(mgpir), mgpir_pl);
	अगर (err)
		वापस err;

	mlxsw_reg_mgpir_unpack(mgpir_pl, शून्य, शून्य, शून्य, &module_count);

	env = kzalloc(काष्ठा_size(env, module_info, module_count), GFP_KERNEL);
	अगर (!env)
		वापस -ENOMEM;

	spin_lock_init(&env->module_info_lock);
	env->core = mlxsw_core;
	env->module_count = module_count;
	*p_env = env;

	err = mlxsw_env_temp_warn_event_रेजिस्टर(mlxsw_core);
	अगर (err)
		जाओ err_temp_warn_event_रेजिस्टर;

	err = mlxsw_env_module_plug_event_रेजिस्टर(mlxsw_core);
	अगर (err)
		जाओ err_module_plug_event_रेजिस्टर;

	err = mlxsw_env_module_oper_state_event_enable(mlxsw_core,
						       env->module_count);
	अगर (err)
		जाओ err_oper_state_event_enable;

	err = mlxsw_env_module_temp_event_enable(mlxsw_core, env->module_count);
	अगर (err)
		जाओ err_temp_event_enable;

	वापस 0;

err_temp_event_enable:
err_oper_state_event_enable:
	mlxsw_env_module_plug_event_unरेजिस्टर(env);
err_module_plug_event_रेजिस्टर:
	mlxsw_env_temp_warn_event_unरेजिस्टर(env);
err_temp_warn_event_रेजिस्टर:
	kमुक्त(env);
	वापस err;
पूर्ण

व्योम mlxsw_env_fini(काष्ठा mlxsw_env *env)
अणु
	mlxsw_env_module_plug_event_unरेजिस्टर(env);
	/* Make sure there is no more event work scheduled. */
	mlxsw_core_flush_owq();
	mlxsw_env_temp_warn_event_unरेजिस्टर(env);
	kमुक्त(env);
पूर्ण
