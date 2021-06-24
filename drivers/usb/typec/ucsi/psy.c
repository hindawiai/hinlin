<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Power Supply क्रम UCSI
 *
 * Copyright (C) 2020, Intel Corporation
 * Author: K V, Abhilash <abhilash.k.v@पूर्णांकel.com>
 * Author: Heikki Krogerus <heikki.krogerus@linux.पूर्णांकel.com>
 */

#समावेश <linux/property.h>
#समावेश <linux/usb/pd.h>

#समावेश "ucsi.h"

/* Power Supply access to expose source घातer inक्रमmation */
क्रमागत ucsi_psy_online_states अणु
	UCSI_PSY_OFFLINE = 0,
	UCSI_PSY_FIXED_ONLINE,
	UCSI_PSY_PROG_ONLINE,
पूर्ण;

अटल क्रमागत घातer_supply_property ucsi_psy_props[] = अणु
	POWER_SUPPLY_PROP_USB_TYPE,
	POWER_SUPPLY_PROP_ONLINE,
	POWER_SUPPLY_PROP_VOLTAGE_MIN,
	POWER_SUPPLY_PROP_VOLTAGE_MAX,
	POWER_SUPPLY_PROP_VOLTAGE_NOW,
	POWER_SUPPLY_PROP_CURRENT_MAX,
	POWER_SUPPLY_PROP_CURRENT_NOW,
पूर्ण;

अटल पूर्णांक ucsi_psy_get_online(काष्ठा ucsi_connector *con,
			       जोड़ घातer_supply_propval *val)
अणु
	val->पूर्णांकval = UCSI_PSY_OFFLINE;
	अगर (con->status.flags & UCSI_CONSTAT_CONNECTED &&
	    (con->status.flags & UCSI_CONSTAT_PWR_सूची) == TYPEC_SINK)
		val->पूर्णांकval = UCSI_PSY_FIXED_ONLINE;
	वापस 0;
पूर्ण

अटल पूर्णांक ucsi_psy_get_voltage_min(काष्ठा ucsi_connector *con,
				    जोड़ घातer_supply_propval *val)
अणु
	u32 pकरो;

	चयन (UCSI_CONSTAT_PWR_OPMODE(con->status.flags)) अणु
	हाल UCSI_CONSTAT_PWR_OPMODE_PD:
		pकरो = con->src_pकरोs[0];
		val->पूर्णांकval = pकरो_fixed_voltage(pकरो) * 1000;
		अवरोध;
	हाल UCSI_CONSTAT_PWR_OPMODE_TYPEC3_0:
	हाल UCSI_CONSTAT_PWR_OPMODE_TYPEC1_5:
	हाल UCSI_CONSTAT_PWR_OPMODE_BC:
	हाल UCSI_CONSTAT_PWR_OPMODE_DEFAULT:
		val->पूर्णांकval = UCSI_TYPEC_VSAFE5V * 1000;
		अवरोध;
	शेष:
		val->पूर्णांकval = 0;
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक ucsi_psy_get_voltage_max(काष्ठा ucsi_connector *con,
				    जोड़ घातer_supply_propval *val)
अणु
	u32 pकरो;

	चयन (UCSI_CONSTAT_PWR_OPMODE(con->status.flags)) अणु
	हाल UCSI_CONSTAT_PWR_OPMODE_PD:
		अगर (con->num_pकरोs > 0) अणु
			pकरो = con->src_pकरोs[con->num_pकरोs - 1];
			val->पूर्णांकval = pकरो_fixed_voltage(pकरो) * 1000;
		पूर्ण अन्यथा अणु
			val->पूर्णांकval = 0;
		पूर्ण
		अवरोध;
	हाल UCSI_CONSTAT_PWR_OPMODE_TYPEC3_0:
	हाल UCSI_CONSTAT_PWR_OPMODE_TYPEC1_5:
	हाल UCSI_CONSTAT_PWR_OPMODE_BC:
	हाल UCSI_CONSTAT_PWR_OPMODE_DEFAULT:
		val->पूर्णांकval = UCSI_TYPEC_VSAFE5V * 1000;
		अवरोध;
	शेष:
		val->पूर्णांकval = 0;
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक ucsi_psy_get_voltage_now(काष्ठा ucsi_connector *con,
				    जोड़ घातer_supply_propval *val)
अणु
	पूर्णांक index;
	u32 pकरो;

	चयन (UCSI_CONSTAT_PWR_OPMODE(con->status.flags)) अणु
	हाल UCSI_CONSTAT_PWR_OPMODE_PD:
		index = rकरो_index(con->rकरो);
		अगर (index > 0) अणु
			pकरो = con->src_pकरोs[index - 1];
			val->पूर्णांकval = pकरो_fixed_voltage(pकरो) * 1000;
		पूर्ण अन्यथा अणु
			val->पूर्णांकval = 0;
		पूर्ण
		अवरोध;
	हाल UCSI_CONSTAT_PWR_OPMODE_TYPEC3_0:
	हाल UCSI_CONSTAT_PWR_OPMODE_TYPEC1_5:
	हाल UCSI_CONSTAT_PWR_OPMODE_BC:
	हाल UCSI_CONSTAT_PWR_OPMODE_DEFAULT:
		val->पूर्णांकval = UCSI_TYPEC_VSAFE5V * 1000;
		अवरोध;
	शेष:
		val->पूर्णांकval = 0;
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक ucsi_psy_get_current_max(काष्ठा ucsi_connector *con,
				    जोड़ घातer_supply_propval *val)
अणु
	u32 pकरो;

	चयन (UCSI_CONSTAT_PWR_OPMODE(con->status.flags)) अणु
	हाल UCSI_CONSTAT_PWR_OPMODE_PD:
		अगर (con->num_pकरोs > 0) अणु
			pकरो = con->src_pकरोs[con->num_pकरोs - 1];
			val->पूर्णांकval = pकरो_max_current(pकरो) * 1000;
		पूर्ण अन्यथा अणु
			val->पूर्णांकval = 0;
		पूर्ण
		अवरोध;
	हाल UCSI_CONSTAT_PWR_OPMODE_TYPEC1_5:
		val->पूर्णांकval = UCSI_TYPEC_1_5_CURRENT * 1000;
		अवरोध;
	हाल UCSI_CONSTAT_PWR_OPMODE_TYPEC3_0:
		val->पूर्णांकval = UCSI_TYPEC_3_0_CURRENT * 1000;
		अवरोध;
	हाल UCSI_CONSTAT_PWR_OPMODE_BC:
	हाल UCSI_CONSTAT_PWR_OPMODE_DEFAULT:
	/* UCSI can't tell b/w DCP/CDP or USB2/3x1/3x2 SDP अक्षरgers */
	शेष:
		val->पूर्णांकval = 0;
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक ucsi_psy_get_current_now(काष्ठा ucsi_connector *con,
				    जोड़ घातer_supply_propval *val)
अणु
	u16 flags = con->status.flags;

	अगर (UCSI_CONSTAT_PWR_OPMODE(flags) == UCSI_CONSTAT_PWR_OPMODE_PD)
		val->पूर्णांकval = rकरो_op_current(con->rकरो) * 1000;
	अन्यथा
		val->पूर्णांकval = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक ucsi_psy_get_usb_type(काष्ठा ucsi_connector *con,
				 जोड़ घातer_supply_propval *val)
अणु
	u16 flags = con->status.flags;

	val->पूर्णांकval = POWER_SUPPLY_USB_TYPE_C;
	अगर (flags & UCSI_CONSTAT_CONNECTED &&
	    UCSI_CONSTAT_PWR_OPMODE(flags) == UCSI_CONSTAT_PWR_OPMODE_PD)
		val->पूर्णांकval = POWER_SUPPLY_USB_TYPE_PD;

	वापस 0;
पूर्ण

अटल पूर्णांक ucsi_psy_get_prop(काष्ठा घातer_supply *psy,
			     क्रमागत घातer_supply_property psp,
			     जोड़ घातer_supply_propval *val)
अणु
	काष्ठा ucsi_connector *con = घातer_supply_get_drvdata(psy);

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_USB_TYPE:
		वापस ucsi_psy_get_usb_type(con, val);
	हाल POWER_SUPPLY_PROP_ONLINE:
		वापस ucsi_psy_get_online(con, val);
	हाल POWER_SUPPLY_PROP_VOLTAGE_MIN:
		वापस ucsi_psy_get_voltage_min(con, val);
	हाल POWER_SUPPLY_PROP_VOLTAGE_MAX:
		वापस ucsi_psy_get_voltage_max(con, val);
	हाल POWER_SUPPLY_PROP_VOLTAGE_NOW:
		वापस ucsi_psy_get_voltage_now(con, val);
	हाल POWER_SUPPLY_PROP_CURRENT_MAX:
		वापस ucsi_psy_get_current_max(con, val);
	हाल POWER_SUPPLY_PROP_CURRENT_NOW:
		वापस ucsi_psy_get_current_now(con, val);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल क्रमागत घातer_supply_usb_type ucsi_psy_usb_types[] = अणु
	POWER_SUPPLY_USB_TYPE_C,
	POWER_SUPPLY_USB_TYPE_PD,
	POWER_SUPPLY_USB_TYPE_PD_PPS,
पूर्ण;

पूर्णांक ucsi_रेजिस्टर_port_psy(काष्ठा ucsi_connector *con)
अणु
	काष्ठा घातer_supply_config psy_cfg = अणुपूर्ण;
	काष्ठा device *dev = con->ucsi->dev;
	अक्षर *psy_name;

	psy_cfg.drv_data = con;
	psy_cfg.fwnode = dev_fwnode(dev);

	psy_name = devm_kaप्र_लिखो(dev, GFP_KERNEL, "ucsi-source-psy-%s%d",
				  dev_name(dev), con->num);
	अगर (!psy_name)
		वापस -ENOMEM;

	con->psy_desc.name = psy_name;
	con->psy_desc.type = POWER_SUPPLY_TYPE_USB;
	con->psy_desc.usb_types = ucsi_psy_usb_types;
	con->psy_desc.num_usb_types = ARRAY_SIZE(ucsi_psy_usb_types);
	con->psy_desc.properties = ucsi_psy_props;
	con->psy_desc.num_properties = ARRAY_SIZE(ucsi_psy_props);
	con->psy_desc.get_property = ucsi_psy_get_prop;

	con->psy = घातer_supply_रेजिस्टर(dev, &con->psy_desc, &psy_cfg);

	वापस PTR_ERR_OR_ZERO(con->psy);
पूर्ण

व्योम ucsi_unरेजिस्टर_port_psy(काष्ठा ucsi_connector *con)
अणु
	अगर (IS_ERR_OR_शून्य(con->psy))
		वापस;

	घातer_supply_unरेजिस्टर(con->psy);
	con->psy = शून्य;
पूर्ण

व्योम ucsi_port_psy_changed(काष्ठा ucsi_connector *con)
अणु
	अगर (IS_ERR_OR_शून्य(con->psy))
		वापस;

	घातer_supply_changed(con->psy);
पूर्ण
