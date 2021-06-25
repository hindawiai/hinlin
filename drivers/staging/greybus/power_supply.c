<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Power Supply driver क्रम a Greybus module.
 *
 * Copyright 2014-2015 Google Inc.
 * Copyright 2014-2015 Linaro Ltd.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/घातer_supply.h>
#समावेश <linux/slab.h>
#समावेश <linux/greybus.h>

#घोषणा PROP_MAX 32

काष्ठा gb_घातer_supply_prop अणु
	क्रमागत घातer_supply_property	prop;
	u8				gb_prop;
	पूर्णांक				val;
	पूर्णांक				previous_val;
	bool				is_ग_लिखोable;
पूर्ण;

काष्ठा gb_घातer_supply अणु
	u8				id;
	bool				रेजिस्टरed;
	काष्ठा घातer_supply		*psy;
	काष्ठा घातer_supply_desc	desc;
	अक्षर				name[64];
	काष्ठा gb_घातer_supplies	*supplies;
	काष्ठा delayed_work		work;
	अक्षर				*manufacturer;
	अक्षर				*model_name;
	अक्षर				*serial_number;
	u8				type;
	u8				properties_count;
	u8				properties_count_str;
	अचिन्हित दीर्घ			last_update;
	u8				cache_invalid;
	अचिन्हित पूर्णांक			update_पूर्णांकerval;
	bool				changed;
	काष्ठा gb_घातer_supply_prop	*props;
	क्रमागत घातer_supply_property	*props_raw;
	bool				pm_acquired;
	काष्ठा mutex			supply_lock;
पूर्ण;

काष्ठा gb_घातer_supplies अणु
	काष्ठा gb_connection	*connection;
	u8			supplies_count;
	काष्ठा gb_घातer_supply	*supply;
	काष्ठा mutex		supplies_lock;
पूर्ण;

#घोषणा to_gb_घातer_supply(x) घातer_supply_get_drvdata(x)

/*
 * General घातer supply properties that could be असलent from various reasons,
 * like kernel versions or venकरोr specअगरic versions
 */
#अगर_अघोषित POWER_SUPPLY_PROP_VOLTAGE_BOOT
	#घोषणा POWER_SUPPLY_PROP_VOLTAGE_BOOT	-1
#पूर्ण_अगर
#अगर_अघोषित POWER_SUPPLY_PROP_CURRENT_BOOT
	#घोषणा POWER_SUPPLY_PROP_CURRENT_BOOT	-1
#पूर्ण_अगर
#अगर_अघोषित POWER_SUPPLY_PROP_CALIBRATE
	#घोषणा POWER_SUPPLY_PROP_CALIBRATE	-1
#पूर्ण_अगर

/* cache समय in milliseconds, अगर cache_समय is set to 0 cache is disable */
अटल अचिन्हित पूर्णांक cache_समय = 1000;
/*
 * update पूर्णांकerval initial and maximum value, between the two will
 * back-off exponential
 */
अटल अचिन्हित पूर्णांक update_पूर्णांकerval_init = 1 * HZ;
अटल अचिन्हित पूर्णांक update_पूर्णांकerval_max = 30 * HZ;

काष्ठा gb_घातer_supply_changes अणु
	क्रमागत घातer_supply_property	prop;
	u32				tolerance_change;
	व्योम (*prop_changed)(काष्ठा gb_घातer_supply *gbpsy,
			     काष्ठा gb_घातer_supply_prop *prop);
पूर्ण;

अटल व्योम gb_घातer_supply_state_change(काष्ठा gb_घातer_supply *gbpsy,
					 काष्ठा gb_घातer_supply_prop *prop);

अटल स्थिर काष्ठा gb_घातer_supply_changes psy_props_changes[] = अणु
	अणु	.prop			= GB_POWER_SUPPLY_PROP_STATUS,
		.tolerance_change	= 0,
		.prop_changed		= gb_घातer_supply_state_change,
	पूर्ण,
	अणु	.prop			= GB_POWER_SUPPLY_PROP_TEMP,
		.tolerance_change	= 500,
		.prop_changed		= शून्य,
	पूर्ण,
	अणु	.prop			= GB_POWER_SUPPLY_PROP_ONLINE,
		.tolerance_change	= 0,
		.prop_changed		= शून्य,
	पूर्ण,
पूर्ण;

अटल पूर्णांक get_psp_from_gb_prop(पूर्णांक gb_prop, क्रमागत घातer_supply_property *psp)
अणु
	पूर्णांक prop;

	चयन (gb_prop) अणु
	हाल GB_POWER_SUPPLY_PROP_STATUS:
		prop = POWER_SUPPLY_PROP_STATUS;
		अवरोध;
	हाल GB_POWER_SUPPLY_PROP_CHARGE_TYPE:
		prop = POWER_SUPPLY_PROP_CHARGE_TYPE;
		अवरोध;
	हाल GB_POWER_SUPPLY_PROP_HEALTH:
		prop = POWER_SUPPLY_PROP_HEALTH;
		अवरोध;
	हाल GB_POWER_SUPPLY_PROP_PRESENT:
		prop = POWER_SUPPLY_PROP_PRESENT;
		अवरोध;
	हाल GB_POWER_SUPPLY_PROP_ONLINE:
		prop = POWER_SUPPLY_PROP_ONLINE;
		अवरोध;
	हाल GB_POWER_SUPPLY_PROP_AUTHENTIC:
		prop = POWER_SUPPLY_PROP_AUTHENTIC;
		अवरोध;
	हाल GB_POWER_SUPPLY_PROP_TECHNOLOGY:
		prop = POWER_SUPPLY_PROP_TECHNOLOGY;
		अवरोध;
	हाल GB_POWER_SUPPLY_PROP_CYCLE_COUNT:
		prop = POWER_SUPPLY_PROP_CYCLE_COUNT;
		अवरोध;
	हाल GB_POWER_SUPPLY_PROP_VOLTAGE_MAX:
		prop = POWER_SUPPLY_PROP_VOLTAGE_MAX;
		अवरोध;
	हाल GB_POWER_SUPPLY_PROP_VOLTAGE_MIN:
		prop = POWER_SUPPLY_PROP_VOLTAGE_MIN;
		अवरोध;
	हाल GB_POWER_SUPPLY_PROP_VOLTAGE_MAX_DESIGN:
		prop = POWER_SUPPLY_PROP_VOLTAGE_MAX_DESIGN;
		अवरोध;
	हाल GB_POWER_SUPPLY_PROP_VOLTAGE_MIN_DESIGN:
		prop = POWER_SUPPLY_PROP_VOLTAGE_MIN_DESIGN;
		अवरोध;
	हाल GB_POWER_SUPPLY_PROP_VOLTAGE_NOW:
		prop = POWER_SUPPLY_PROP_VOLTAGE_NOW;
		अवरोध;
	हाल GB_POWER_SUPPLY_PROP_VOLTAGE_AVG:
		prop = POWER_SUPPLY_PROP_VOLTAGE_AVG;
		अवरोध;
	हाल GB_POWER_SUPPLY_PROP_VOLTAGE_OCV:
		prop = POWER_SUPPLY_PROP_VOLTAGE_OCV;
		अवरोध;
	हाल GB_POWER_SUPPLY_PROP_VOLTAGE_BOOT:
		prop = POWER_SUPPLY_PROP_VOLTAGE_BOOT;
		अवरोध;
	हाल GB_POWER_SUPPLY_PROP_CURRENT_MAX:
		prop = POWER_SUPPLY_PROP_CURRENT_MAX;
		अवरोध;
	हाल GB_POWER_SUPPLY_PROP_CURRENT_NOW:
		prop = POWER_SUPPLY_PROP_CURRENT_NOW;
		अवरोध;
	हाल GB_POWER_SUPPLY_PROP_CURRENT_AVG:
		prop = POWER_SUPPLY_PROP_CURRENT_AVG;
		अवरोध;
	हाल GB_POWER_SUPPLY_PROP_CURRENT_BOOT:
		prop = POWER_SUPPLY_PROP_CURRENT_BOOT;
		अवरोध;
	हाल GB_POWER_SUPPLY_PROP_POWER_NOW:
		prop = POWER_SUPPLY_PROP_POWER_NOW;
		अवरोध;
	हाल GB_POWER_SUPPLY_PROP_POWER_AVG:
		prop = POWER_SUPPLY_PROP_POWER_AVG;
		अवरोध;
	हाल GB_POWER_SUPPLY_PROP_CHARGE_FULL_DESIGN:
		prop = POWER_SUPPLY_PROP_CHARGE_FULL_DESIGN;
		अवरोध;
	हाल GB_POWER_SUPPLY_PROP_CHARGE_EMPTY_DESIGN:
		prop = POWER_SUPPLY_PROP_CHARGE_EMPTY_DESIGN;
		अवरोध;
	हाल GB_POWER_SUPPLY_PROP_CHARGE_FULL:
		prop = POWER_SUPPLY_PROP_CHARGE_FULL;
		अवरोध;
	हाल GB_POWER_SUPPLY_PROP_CHARGE_EMPTY:
		prop = POWER_SUPPLY_PROP_CHARGE_EMPTY;
		अवरोध;
	हाल GB_POWER_SUPPLY_PROP_CHARGE_NOW:
		prop = POWER_SUPPLY_PROP_CHARGE_NOW;
		अवरोध;
	हाल GB_POWER_SUPPLY_PROP_CHARGE_AVG:
		prop = POWER_SUPPLY_PROP_CHARGE_AVG;
		अवरोध;
	हाल GB_POWER_SUPPLY_PROP_CHARGE_COUNTER:
		prop = POWER_SUPPLY_PROP_CHARGE_COUNTER;
		अवरोध;
	हाल GB_POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT:
		prop = POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT;
		अवरोध;
	हाल GB_POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT_MAX:
		prop = POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT_MAX;
		अवरोध;
	हाल GB_POWER_SUPPLY_PROP_CONSTANT_CHARGE_VOLTAGE:
		prop = POWER_SUPPLY_PROP_CONSTANT_CHARGE_VOLTAGE;
		अवरोध;
	हाल GB_POWER_SUPPLY_PROP_CONSTANT_CHARGE_VOLTAGE_MAX:
		prop = POWER_SUPPLY_PROP_CONSTANT_CHARGE_VOLTAGE_MAX;
		अवरोध;
	हाल GB_POWER_SUPPLY_PROP_CHARGE_CONTROL_LIMIT:
		prop = POWER_SUPPLY_PROP_CHARGE_CONTROL_LIMIT;
		अवरोध;
	हाल GB_POWER_SUPPLY_PROP_CHARGE_CONTROL_LIMIT_MAX:
		prop = POWER_SUPPLY_PROP_CHARGE_CONTROL_LIMIT_MAX;
		अवरोध;
	हाल GB_POWER_SUPPLY_PROP_INPUT_CURRENT_LIMIT:
		prop = POWER_SUPPLY_PROP_INPUT_CURRENT_LIMIT;
		अवरोध;
	हाल GB_POWER_SUPPLY_PROP_ENERGY_FULL_DESIGN:
		prop = POWER_SUPPLY_PROP_ENERGY_FULL_DESIGN;
		अवरोध;
	हाल GB_POWER_SUPPLY_PROP_ENERGY_EMPTY_DESIGN:
		prop = POWER_SUPPLY_PROP_ENERGY_EMPTY_DESIGN;
		अवरोध;
	हाल GB_POWER_SUPPLY_PROP_ENERGY_FULL:
		prop = POWER_SUPPLY_PROP_ENERGY_FULL;
		अवरोध;
	हाल GB_POWER_SUPPLY_PROP_ENERGY_EMPTY:
		prop = POWER_SUPPLY_PROP_ENERGY_EMPTY;
		अवरोध;
	हाल GB_POWER_SUPPLY_PROP_ENERGY_NOW:
		prop = POWER_SUPPLY_PROP_ENERGY_NOW;
		अवरोध;
	हाल GB_POWER_SUPPLY_PROP_ENERGY_AVG:
		prop = POWER_SUPPLY_PROP_ENERGY_AVG;
		अवरोध;
	हाल GB_POWER_SUPPLY_PROP_CAPACITY:
		prop = POWER_SUPPLY_PROP_CAPACITY;
		अवरोध;
	हाल GB_POWER_SUPPLY_PROP_CAPACITY_ALERT_MIN:
		prop = POWER_SUPPLY_PROP_CAPACITY_ALERT_MIN;
		अवरोध;
	हाल GB_POWER_SUPPLY_PROP_CAPACITY_ALERT_MAX:
		prop = POWER_SUPPLY_PROP_CAPACITY_ALERT_MAX;
		अवरोध;
	हाल GB_POWER_SUPPLY_PROP_CAPACITY_LEVEL:
		prop = POWER_SUPPLY_PROP_CAPACITY_LEVEL;
		अवरोध;
	हाल GB_POWER_SUPPLY_PROP_TEMP:
		prop = POWER_SUPPLY_PROP_TEMP;
		अवरोध;
	हाल GB_POWER_SUPPLY_PROP_TEMP_MAX:
		prop = POWER_SUPPLY_PROP_TEMP_MAX;
		अवरोध;
	हाल GB_POWER_SUPPLY_PROP_TEMP_MIN:
		prop = POWER_SUPPLY_PROP_TEMP_MIN;
		अवरोध;
	हाल GB_POWER_SUPPLY_PROP_TEMP_ALERT_MIN:
		prop = POWER_SUPPLY_PROP_TEMP_ALERT_MIN;
		अवरोध;
	हाल GB_POWER_SUPPLY_PROP_TEMP_ALERT_MAX:
		prop = POWER_SUPPLY_PROP_TEMP_ALERT_MAX;
		अवरोध;
	हाल GB_POWER_SUPPLY_PROP_TEMP_AMBIENT:
		prop = POWER_SUPPLY_PROP_TEMP_AMBIENT;
		अवरोध;
	हाल GB_POWER_SUPPLY_PROP_TEMP_AMBIENT_ALERT_MIN:
		prop = POWER_SUPPLY_PROP_TEMP_AMBIENT_ALERT_MIN;
		अवरोध;
	हाल GB_POWER_SUPPLY_PROP_TEMP_AMBIENT_ALERT_MAX:
		prop = POWER_SUPPLY_PROP_TEMP_AMBIENT_ALERT_MAX;
		अवरोध;
	हाल GB_POWER_SUPPLY_PROP_TIME_TO_EMPTY_NOW:
		prop = POWER_SUPPLY_PROP_TIME_TO_EMPTY_NOW;
		अवरोध;
	हाल GB_POWER_SUPPLY_PROP_TIME_TO_EMPTY_AVG:
		prop = POWER_SUPPLY_PROP_TIME_TO_EMPTY_AVG;
		अवरोध;
	हाल GB_POWER_SUPPLY_PROP_TIME_TO_FULL_NOW:
		prop = POWER_SUPPLY_PROP_TIME_TO_FULL_NOW;
		अवरोध;
	हाल GB_POWER_SUPPLY_PROP_TIME_TO_FULL_AVG:
		prop = POWER_SUPPLY_PROP_TIME_TO_FULL_AVG;
		अवरोध;
	हाल GB_POWER_SUPPLY_PROP_TYPE:
		prop = POWER_SUPPLY_PROP_TYPE;
		अवरोध;
	हाल GB_POWER_SUPPLY_PROP_SCOPE:
		prop = POWER_SUPPLY_PROP_SCOPE;
		अवरोध;
	हाल GB_POWER_SUPPLY_PROP_CHARGE_TERM_CURRENT:
		prop = POWER_SUPPLY_PROP_CHARGE_TERM_CURRENT;
		अवरोध;
	हाल GB_POWER_SUPPLY_PROP_CALIBRATE:
		prop = POWER_SUPPLY_PROP_CALIBRATE;
		अवरोध;
	शेष:
		prop = -1;
		अवरोध;
	पूर्ण

	अगर (prop < 0)
		वापस prop;

	*psp = (क्रमागत घातer_supply_property)prop;

	वापस 0;
पूर्ण

अटल काष्ठा gb_connection *get_conn_from_psy(काष्ठा gb_घातer_supply *gbpsy)
अणु
	वापस gbpsy->supplies->connection;
पूर्ण

अटल काष्ठा gb_घातer_supply_prop *get_psy_prop(काष्ठा gb_घातer_supply *gbpsy,
						 क्रमागत घातer_supply_property psp)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < gbpsy->properties_count; i++)
		अगर (gbpsy->props[i].prop == psp)
			वापस &gbpsy->props[i];
	वापस शून्य;
पूर्ण

अटल पूर्णांक is_psy_prop_ग_लिखोable(काष्ठा gb_घातer_supply *gbpsy,
				     क्रमागत घातer_supply_property psp)
अणु
	काष्ठा gb_घातer_supply_prop *prop;

	prop = get_psy_prop(gbpsy, psp);
	अगर (!prop)
		वापस -ENOENT;
	वापस prop->is_ग_लिखोable ? 1 : 0;
पूर्ण

अटल पूर्णांक is_prop_valपूर्णांक(क्रमागत घातer_supply_property psp)
अणु
	वापस ((psp < POWER_SUPPLY_PROP_MODEL_NAME) ? 1 : 0);
पूर्ण

अटल व्योम next_पूर्णांकerval(काष्ठा gb_घातer_supply *gbpsy)
अणु
	अगर (gbpsy->update_पूर्णांकerval == update_पूर्णांकerval_max)
		वापस;

	/* करो some exponential back-off in the update पूर्णांकerval */
	gbpsy->update_पूर्णांकerval *= 2;
	अगर (gbpsy->update_पूर्णांकerval > update_पूर्णांकerval_max)
		gbpsy->update_पूर्णांकerval = update_पूर्णांकerval_max;
पूर्ण

अटल व्योम __gb_घातer_supply_changed(काष्ठा gb_घातer_supply *gbpsy)
अणु
	घातer_supply_changed(gbpsy->psy);
पूर्ण

अटल व्योम gb_घातer_supply_state_change(काष्ठा gb_घातer_supply *gbpsy,
					 काष्ठा gb_घातer_supply_prop *prop)
अणु
	काष्ठा gb_connection *connection = get_conn_from_psy(gbpsy);
	पूर्णांक ret;

	/*
	 * Check gbpsy->pm_acquired to make sure only one pair of 'get_sync'
	 * and 'put_autosuspend' runसमय pm call क्रम state property change.
	 */
	mutex_lock(&gbpsy->supply_lock);

	अगर ((prop->val == GB_POWER_SUPPLY_STATUS_CHARGING) &&
	    !gbpsy->pm_acquired) अणु
		ret = gb_pm_runसमय_get_sync(connection->bundle);
		अगर (ret)
			dev_err(&connection->bundle->dev,
				"Fail to set wake lock for charging state\n");
		अन्यथा
			gbpsy->pm_acquired = true;
	पूर्ण अन्यथा अणु
		अगर (gbpsy->pm_acquired) अणु
			ret = gb_pm_runसमय_put_स्वतःsuspend(connection->bundle);
			अगर (ret)
				dev_err(&connection->bundle->dev,
					"Fail to set wake unlock for none charging\n");
			अन्यथा
				gbpsy->pm_acquired = false;
		पूर्ण
	पूर्ण

	mutex_unlock(&gbpsy->supply_lock);
पूर्ण

अटल व्योम check_changed(काष्ठा gb_घातer_supply *gbpsy,
			  काष्ठा gb_घातer_supply_prop *prop)
अणु
	स्थिर काष्ठा gb_घातer_supply_changes *psyc;
	पूर्णांक val = prop->val;
	पूर्णांक prev_val = prop->previous_val;
	bool changed = false;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(psy_props_changes); i++) अणु
		psyc = &psy_props_changes[i];
		अगर (prop->prop == psyc->prop) अणु
			अगर (!psyc->tolerance_change)
				changed = true;
			अन्यथा अगर (val < prev_val &&
				 prev_val - val > psyc->tolerance_change)
				changed = true;
			अन्यथा अगर (val > prev_val &&
				 val - prev_val > psyc->tolerance_change)
				changed = true;

			अगर (changed && psyc->prop_changed)
				psyc->prop_changed(gbpsy, prop);

			अगर (changed)
				gbpsy->changed = true;
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक total_props(काष्ठा gb_घातer_supply *gbpsy)
अणु
	/* this वापस the पूर्णांकval plus the strval properties */
	वापस (gbpsy->properties_count + gbpsy->properties_count_str);
पूर्ण

अटल व्योम prop_append(काष्ठा gb_घातer_supply *gbpsy,
			क्रमागत घातer_supply_property prop)
अणु
	क्रमागत घातer_supply_property *new_props_raw;

	gbpsy->properties_count_str++;
	new_props_raw = kपुनः_स्मृति(gbpsy->props_raw, total_props(gbpsy) *
				 माप(क्रमागत घातer_supply_property),
				 GFP_KERNEL);
	अगर (!new_props_raw)
		वापस;
	gbpsy->props_raw = new_props_raw;
	gbpsy->props_raw[total_props(gbpsy) - 1] = prop;
पूर्ण

अटल पूर्णांक __gb_घातer_supply_set_name(अक्षर *init_name, अक्षर *name, माप_प्रकार len)
अणु
	अचिन्हित पूर्णांक i = 0;
	पूर्णांक ret = 0;
	काष्ठा घातer_supply *psy;

	अगर (!म_माप(init_name))
		init_name = "gb_power_supply";
	strscpy(name, init_name, len);

	जबतक ((ret < len) && (psy = घातer_supply_get_by_name(name))) अणु
		घातer_supply_put(psy);

		ret = snम_लिखो(name, len, "%s_%u", init_name, ++i);
	पूर्ण
	अगर (ret >= len)
		वापस -ENOMEM;
	वापस i;
पूर्ण

अटल व्योम _gb_घातer_supply_append_props(काष्ठा gb_घातer_supply *gbpsy)
अणु
	अगर (म_माप(gbpsy->manufacturer))
		prop_append(gbpsy, POWER_SUPPLY_PROP_MANUFACTURER);
	अगर (म_माप(gbpsy->model_name))
		prop_append(gbpsy, POWER_SUPPLY_PROP_MODEL_NAME);
	अगर (म_माप(gbpsy->serial_number))
		prop_append(gbpsy, POWER_SUPPLY_PROP_SERIAL_NUMBER);
पूर्ण

अटल पूर्णांक gb_घातer_supply_description_get(काष्ठा gb_घातer_supply *gbpsy)
अणु
	काष्ठा gb_connection *connection = get_conn_from_psy(gbpsy);
	काष्ठा gb_घातer_supply_get_description_request req;
	काष्ठा gb_घातer_supply_get_description_response resp;
	पूर्णांक ret;

	req.psy_id = gbpsy->id;

	ret = gb_operation_sync(connection,
				GB_POWER_SUPPLY_TYPE_GET_DESCRIPTION,
				&req, माप(req), &resp, माप(resp));
	अगर (ret < 0)
		वापस ret;

	gbpsy->manufacturer = kstrndup(resp.manufacturer, PROP_MAX, GFP_KERNEL);
	अगर (!gbpsy->manufacturer)
		वापस -ENOMEM;
	gbpsy->model_name = kstrndup(resp.model, PROP_MAX, GFP_KERNEL);
	अगर (!gbpsy->model_name)
		वापस -ENOMEM;
	gbpsy->serial_number = kstrndup(resp.serial_number, PROP_MAX,
				       GFP_KERNEL);
	अगर (!gbpsy->serial_number)
		वापस -ENOMEM;

	gbpsy->type = le16_to_cpu(resp.type);
	gbpsy->properties_count = resp.properties_count;

	वापस 0;
पूर्ण

अटल पूर्णांक gb_घातer_supply_prop_descriptors_get(काष्ठा gb_घातer_supply *gbpsy)
अणु
	काष्ठा gb_connection *connection = get_conn_from_psy(gbpsy);
	काष्ठा gb_घातer_supply_get_property_descriptors_request *req;
	काष्ठा gb_घातer_supply_get_property_descriptors_response *resp;
	काष्ठा gb_operation *op;
	u8 props_count = gbpsy->properties_count;
	क्रमागत घातer_supply_property psp;
	पूर्णांक ret;
	पूर्णांक i, r = 0;

	अगर (props_count == 0)
		वापस 0;

	op = gb_operation_create(connection,
				 GB_POWER_SUPPLY_TYPE_GET_PROP_DESCRIPTORS,
				 माप(*req),
				 काष्ठा_size(resp, props, props_count),
				 GFP_KERNEL);
	अगर (!op)
		वापस -ENOMEM;

	req = op->request->payload;
	req->psy_id = gbpsy->id;

	ret = gb_operation_request_send_sync(op);
	अगर (ret < 0)
		जाओ out_put_operation;

	resp = op->response->payload;

	/* validate received properties */
	क्रम (i = 0; i < props_count; i++) अणु
		ret = get_psp_from_gb_prop(resp->props[i].property, &psp);
		अगर (ret < 0) अणु
			dev_warn(&connection->bundle->dev,
				 "greybus property %u it is not supported by this kernel, dropped\n",
				 resp->props[i].property);
			gbpsy->properties_count--;
		पूर्ण
	पूर्ण

	gbpsy->props = kसुस्मृति(gbpsy->properties_count, माप(*gbpsy->props),
			      GFP_KERNEL);
	अगर (!gbpsy->props) अणु
		ret = -ENOMEM;
		जाओ out_put_operation;
	पूर्ण

	gbpsy->props_raw = kसुस्मृति(gbpsy->properties_count,
				   माप(*gbpsy->props_raw), GFP_KERNEL);
	अगर (!gbpsy->props_raw) अणु
		ret = -ENOMEM;
		जाओ out_put_operation;
	पूर्ण

	/* Store available properties, skip the ones we करो not support */
	क्रम (i = 0; i < props_count; i++) अणु
		ret = get_psp_from_gb_prop(resp->props[i].property, &psp);
		अगर (ret < 0) अणु
			r++;
			जारी;
		पूर्ण
		gbpsy->props[i - r].prop = psp;
		gbpsy->props[i - r].gb_prop = resp->props[i].property;
		gbpsy->props_raw[i - r] = psp;
		अगर (resp->props[i].is_ग_लिखोable)
			gbpsy->props[i - r].is_ग_लिखोable = true;
	पूर्ण

	/*
	 * now append the properties that we alपढ़ोy got inक्रमmation in the
	 * get_description operation. (अक्षर * ones)
	 */
	_gb_घातer_supply_append_props(gbpsy);

	ret = 0;
out_put_operation:
	gb_operation_put(op);

	वापस ret;
पूर्ण

अटल पूर्णांक __gb_घातer_supply_property_update(काष्ठा gb_घातer_supply *gbpsy,
					     क्रमागत घातer_supply_property psp)
अणु
	काष्ठा gb_connection *connection = get_conn_from_psy(gbpsy);
	काष्ठा gb_घातer_supply_prop *prop;
	काष्ठा gb_घातer_supply_get_property_request req;
	काष्ठा gb_घातer_supply_get_property_response resp;
	पूर्णांक val;
	पूर्णांक ret;

	prop = get_psy_prop(gbpsy, psp);
	अगर (!prop)
		वापस -EINVAL;
	req.psy_id = gbpsy->id;
	req.property = prop->gb_prop;

	ret = gb_operation_sync(connection, GB_POWER_SUPPLY_TYPE_GET_PROPERTY,
				&req, माप(req), &resp, माप(resp));
	अगर (ret < 0)
		वापस ret;

	val = le32_to_cpu(resp.prop_val);
	अगर (val == prop->val)
		वापस 0;

	prop->previous_val = prop->val;
	prop->val = val;

	check_changed(gbpsy, prop);

	वापस 0;
पूर्ण

अटल पूर्णांक __gb_घातer_supply_property_get(काष्ठा gb_घातer_supply *gbpsy,
					  क्रमागत घातer_supply_property psp,
					  जोड़ घातer_supply_propval *val)
अणु
	काष्ठा gb_घातer_supply_prop *prop;

	prop = get_psy_prop(gbpsy, psp);
	अगर (!prop)
		वापस -EINVAL;

	val->पूर्णांकval = prop->val;
	वापस 0;
पूर्ण

अटल पूर्णांक __gb_घातer_supply_property_strval_get(काष्ठा gb_घातer_supply *gbpsy,
						क्रमागत घातer_supply_property psp,
						जोड़ घातer_supply_propval *val)
अणु
	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_MODEL_NAME:
		val->strval = gbpsy->model_name;
		अवरोध;
	हाल POWER_SUPPLY_PROP_MANUFACTURER:
		val->strval = gbpsy->manufacturer;
		अवरोध;
	हाल POWER_SUPPLY_PROP_SERIAL_NUMBER:
		val->strval = gbpsy->serial_number;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक _gb_घातer_supply_property_get(काष्ठा gb_घातer_supply *gbpsy,
					 क्रमागत घातer_supply_property psp,
					 जोड़ घातer_supply_propval *val)
अणु
	काष्ठा gb_connection *connection = get_conn_from_psy(gbpsy);
	पूर्णांक ret;

	/*
	 * Properties of type स्थिर अक्षर *, were alपढ़ोy fetched on
	 * get_description operation and should be cached in gb
	 */
	अगर (is_prop_valपूर्णांक(psp))
		ret = __gb_घातer_supply_property_get(gbpsy, psp, val);
	अन्यथा
		ret = __gb_घातer_supply_property_strval_get(gbpsy, psp, val);

	अगर (ret < 0)
		dev_err(&connection->bundle->dev, "get property %u\n", psp);

	वापस 0;
पूर्ण

अटल पूर्णांक is_cache_valid(काष्ठा gb_घातer_supply *gbpsy)
अणु
	/* check अगर cache is good enough or it has expired */
	अगर (gbpsy->cache_invalid) अणु
		gbpsy->cache_invalid = 0;
		वापस 0;
	पूर्ण

	अगर (gbpsy->last_update &&
	    समय_is_after_jअगरfies(gbpsy->last_update +
				  msecs_to_jअगरfies(cache_समय)))
		वापस 1;

	वापस 0;
पूर्ण

अटल पूर्णांक gb_घातer_supply_status_get(काष्ठा gb_घातer_supply *gbpsy)
अणु
	काष्ठा gb_connection *connection = get_conn_from_psy(gbpsy);
	पूर्णांक ret = 0;
	पूर्णांक i;

	अगर (is_cache_valid(gbpsy))
		वापस 0;

	ret = gb_pm_runसमय_get_sync(connection->bundle);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < gbpsy->properties_count; i++) अणु
		ret = __gb_घातer_supply_property_update(gbpsy,
							gbpsy->props[i].prop);
		अगर (ret < 0)
			अवरोध;
	पूर्ण

	अगर (ret == 0)
		gbpsy->last_update = jअगरfies;

	gb_pm_runसमय_put_स्वतःsuspend(connection->bundle);
	वापस ret;
पूर्ण

अटल व्योम gb_घातer_supply_status_update(काष्ठा gb_घातer_supply *gbpsy)
अणु
	/* check अगर there a change that need to be reported */
	gb_घातer_supply_status_get(gbpsy);

	अगर (!gbpsy->changed)
		वापस;

	gbpsy->update_पूर्णांकerval = update_पूर्णांकerval_init;
	__gb_घातer_supply_changed(gbpsy);
	gbpsy->changed = false;
पूर्ण

अटल व्योम gb_घातer_supply_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा gb_घातer_supply *gbpsy = container_of(work,
						     काष्ठा gb_घातer_supply,
						     work.work);

	/*
	 * अगर the poll पूर्णांकerval is not set, disable polling, this is helpful
	 * specially at unरेजिस्टर समय.
	 */
	अगर (!gbpsy->update_पूर्णांकerval)
		वापस;

	gb_घातer_supply_status_update(gbpsy);
	next_पूर्णांकerval(gbpsy);
	schedule_delayed_work(&gbpsy->work, gbpsy->update_पूर्णांकerval);
पूर्ण

अटल पूर्णांक get_property(काष्ठा घातer_supply *b,
			क्रमागत घातer_supply_property psp,
			जोड़ घातer_supply_propval *val)
अणु
	काष्ठा gb_घातer_supply *gbpsy = to_gb_घातer_supply(b);

	gb_घातer_supply_status_get(gbpsy);

	वापस _gb_घातer_supply_property_get(gbpsy, psp, val);
पूर्ण

अटल पूर्णांक gb_घातer_supply_property_set(काष्ठा gb_घातer_supply *gbpsy,
					क्रमागत घातer_supply_property psp,
					पूर्णांक val)
अणु
	काष्ठा gb_connection *connection = get_conn_from_psy(gbpsy);
	काष्ठा gb_घातer_supply_prop *prop;
	काष्ठा gb_घातer_supply_set_property_request req;
	पूर्णांक ret;

	ret = gb_pm_runसमय_get_sync(connection->bundle);
	अगर (ret)
		वापस ret;

	prop = get_psy_prop(gbpsy, psp);
	अगर (!prop) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	req.psy_id = gbpsy->id;
	req.property = prop->gb_prop;
	req.prop_val = cpu_to_le32((s32)val);

	ret = gb_operation_sync(connection, GB_POWER_SUPPLY_TYPE_SET_PROPERTY,
				&req, माप(req), शून्य, 0);
	अगर (ret < 0)
		जाओ out;

	/* cache immediately the new value */
	prop->val = val;

out:
	gb_pm_runसमय_put_स्वतःsuspend(connection->bundle);
	वापस ret;
पूर्ण

अटल पूर्णांक set_property(काष्ठा घातer_supply *b,
			क्रमागत घातer_supply_property psp,
			स्थिर जोड़ घातer_supply_propval *val)
अणु
	काष्ठा gb_घातer_supply *gbpsy = to_gb_घातer_supply(b);

	वापस gb_घातer_supply_property_set(gbpsy, psp, val->पूर्णांकval);
पूर्ण

अटल पूर्णांक property_is_ग_लिखोable(काष्ठा घातer_supply *b,
				 क्रमागत घातer_supply_property psp)
अणु
	काष्ठा gb_घातer_supply *gbpsy = to_gb_घातer_supply(b);

	वापस is_psy_prop_ग_लिखोable(gbpsy, psp);
पूर्ण

अटल पूर्णांक gb_घातer_supply_रेजिस्टर(काष्ठा gb_घातer_supply *gbpsy)
अणु
	काष्ठा gb_connection *connection = get_conn_from_psy(gbpsy);
	काष्ठा घातer_supply_config cfg = अणुपूर्ण;

	cfg.drv_data = gbpsy;

	gbpsy->desc.name		= gbpsy->name;
	gbpsy->desc.type		= gbpsy->type;
	gbpsy->desc.properties		= gbpsy->props_raw;
	gbpsy->desc.num_properties	= total_props(gbpsy);
	gbpsy->desc.get_property	= get_property;
	gbpsy->desc.set_property	= set_property;
	gbpsy->desc.property_is_ग_लिखोable = property_is_ग_लिखोable;

	gbpsy->psy = घातer_supply_रेजिस्टर(&connection->bundle->dev,
					   &gbpsy->desc, &cfg);
	वापस PTR_ERR_OR_ZERO(gbpsy->psy);
पूर्ण

अटल व्योम _gb_घातer_supply_मुक्त(काष्ठा gb_घातer_supply *gbpsy)
अणु
	kमुक्त(gbpsy->serial_number);
	kमुक्त(gbpsy->model_name);
	kमुक्त(gbpsy->manufacturer);
	kमुक्त(gbpsy->props_raw);
	kमुक्त(gbpsy->props);
पूर्ण

अटल व्योम _gb_घातer_supply_release(काष्ठा gb_घातer_supply *gbpsy)
अणु
	gbpsy->update_पूर्णांकerval = 0;

	cancel_delayed_work_sync(&gbpsy->work);

	अगर (gbpsy->रेजिस्टरed)
		घातer_supply_unरेजिस्टर(gbpsy->psy);

	_gb_घातer_supply_मुक्त(gbpsy);
पूर्ण

अटल व्योम _gb_घातer_supplies_release(काष्ठा gb_घातer_supplies *supplies)
अणु
	पूर्णांक i;

	अगर (!supplies->supply)
		वापस;

	mutex_lock(&supplies->supplies_lock);
	क्रम (i = 0; i < supplies->supplies_count; i++)
		_gb_घातer_supply_release(&supplies->supply[i]);
	kमुक्त(supplies->supply);
	mutex_unlock(&supplies->supplies_lock);
	kमुक्त(supplies);
पूर्ण

अटल पूर्णांक gb_घातer_supplies_get_count(काष्ठा gb_घातer_supplies *supplies)
अणु
	काष्ठा gb_घातer_supply_get_supplies_response resp;
	पूर्णांक ret;

	ret = gb_operation_sync(supplies->connection,
				GB_POWER_SUPPLY_TYPE_GET_SUPPLIES,
				शून्य, 0, &resp, माप(resp));
	अगर (ret < 0)
		वापस ret;

	अगर  (!resp.supplies_count)
		वापस -EINVAL;

	supplies->supplies_count = resp.supplies_count;

	वापस ret;
पूर्ण

अटल पूर्णांक gb_घातer_supply_config(काष्ठा gb_घातer_supplies *supplies, पूर्णांक id)
अणु
	काष्ठा gb_घातer_supply *gbpsy = &supplies->supply[id];
	पूर्णांक ret;

	gbpsy->supplies = supplies;
	gbpsy->id = id;

	ret = gb_घातer_supply_description_get(gbpsy);
	अगर (ret < 0)
		वापस ret;

	वापस gb_घातer_supply_prop_descriptors_get(gbpsy);
पूर्ण

अटल पूर्णांक gb_घातer_supply_enable(काष्ठा gb_घातer_supply *gbpsy)
अणु
	पूर्णांक ret;

	/* guarantee that we have an unique name, beक्रमe रेजिस्टर */
	ret =  __gb_घातer_supply_set_name(gbpsy->model_name, gbpsy->name,
					  माप(gbpsy->name));
	अगर (ret < 0)
		वापस ret;

	mutex_init(&gbpsy->supply_lock);

	ret = gb_घातer_supply_रेजिस्टर(gbpsy);
	अगर (ret < 0)
		वापस ret;

	gbpsy->update_पूर्णांकerval = update_पूर्णांकerval_init;
	INIT_DELAYED_WORK(&gbpsy->work, gb_घातer_supply_work);
	schedule_delayed_work(&gbpsy->work, 0);

	/* everything went fine, mark it क्रम release code to know */
	gbpsy->रेजिस्टरed = true;

	वापस 0;
पूर्ण

अटल पूर्णांक gb_घातer_supplies_setup(काष्ठा gb_घातer_supplies *supplies)
अणु
	काष्ठा gb_connection *connection = supplies->connection;
	पूर्णांक ret;
	पूर्णांक i;

	mutex_lock(&supplies->supplies_lock);

	ret = gb_घातer_supplies_get_count(supplies);
	अगर (ret < 0)
		जाओ out;

	supplies->supply = kसुस्मृति(supplies->supplies_count,
				     माप(काष्ठा gb_घातer_supply),
				     GFP_KERNEL);

	अगर (!supplies->supply) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	क्रम (i = 0; i < supplies->supplies_count; i++) अणु
		ret = gb_घातer_supply_config(supplies, i);
		अगर (ret < 0) अणु
			dev_err(&connection->bundle->dev,
				"Fail to configure supplies devices\n");
			जाओ out;
		पूर्ण
	पूर्ण
out:
	mutex_unlock(&supplies->supplies_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक gb_घातer_supplies_रेजिस्टर(काष्ठा gb_घातer_supplies *supplies)
अणु
	काष्ठा gb_connection *connection = supplies->connection;
	पूर्णांक ret = 0;
	पूर्णांक i;

	mutex_lock(&supplies->supplies_lock);

	क्रम (i = 0; i < supplies->supplies_count; i++) अणु
		ret = gb_घातer_supply_enable(&supplies->supply[i]);
		अगर (ret < 0) अणु
			dev_err(&connection->bundle->dev,
				"Fail to enable supplies devices\n");
			अवरोध;
		पूर्ण
	पूर्ण

	mutex_unlock(&supplies->supplies_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक gb_supplies_request_handler(काष्ठा gb_operation *op)
अणु
	काष्ठा gb_connection *connection = op->connection;
	काष्ठा gb_घातer_supplies *supplies = gb_connection_get_data(connection);
	काष्ठा gb_घातer_supply *gbpsy;
	काष्ठा gb_message *request;
	काष्ठा gb_घातer_supply_event_request *payload;
	u8 psy_id;
	u8 event;
	पूर्णांक ret = 0;

	अगर (op->type != GB_POWER_SUPPLY_TYPE_EVENT) अणु
		dev_err(&connection->bundle->dev,
			"Unsupported unsolicited event: %u\n", op->type);
		वापस -EINVAL;
	पूर्ण

	request = op->request;

	अगर (request->payload_size < माप(*payload)) अणु
		dev_err(&connection->bundle->dev,
			"Wrong event size received (%zu < %zu)\n",
			request->payload_size, माप(*payload));
		वापस -EINVAL;
	पूर्ण

	payload = request->payload;
	psy_id = payload->psy_id;
	mutex_lock(&supplies->supplies_lock);
	अगर (psy_id >= supplies->supplies_count ||
	    !supplies->supply[psy_id].रेजिस्टरed) अणु
		dev_err(&connection->bundle->dev,
			"Event received for unconfigured power_supply id: %d\n",
			psy_id);
		ret = -EINVAL;
		जाओ out_unlock;
	पूर्ण

	event = payload->event;
	/*
	 * we will only handle events after setup is करोne and beक्रमe release is
	 * running. For that just check update_पूर्णांकerval.
	 */
	gbpsy = &supplies->supply[psy_id];
	अगर (!gbpsy->update_पूर्णांकerval) अणु
		ret = -ESHUTDOWN;
		जाओ out_unlock;
	पूर्ण

	अगर (event & GB_POWER_SUPPLY_UPDATE) अणु
		/*
		 * we need to make sure we invalidate cache, अगर not no new
		 * values क्रम the properties will be fetch and the all propose
		 * of this event is missed
		 */
		gbpsy->cache_invalid = 1;
		gb_घातer_supply_status_update(gbpsy);
	पूर्ण

out_unlock:
	mutex_unlock(&supplies->supplies_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक gb_घातer_supply_probe(काष्ठा gb_bundle *bundle,
				 स्थिर काष्ठा greybus_bundle_id *id)
अणु
	काष्ठा greybus_descriptor_cport *cport_desc;
	काष्ठा gb_connection *connection;
	काष्ठा gb_घातer_supplies *supplies;
	पूर्णांक ret;

	अगर (bundle->num_cports != 1)
		वापस -ENODEV;

	cport_desc = &bundle->cport_desc[0];
	अगर (cport_desc->protocol_id != GREYBUS_PROTOCOL_POWER_SUPPLY)
		वापस -ENODEV;

	supplies = kzalloc(माप(*supplies), GFP_KERNEL);
	अगर (!supplies)
		वापस -ENOMEM;

	connection = gb_connection_create(bundle, le16_to_cpu(cport_desc->id),
					  gb_supplies_request_handler);
	अगर (IS_ERR(connection)) अणु
		ret = PTR_ERR(connection);
		जाओ out;
	पूर्ण

	supplies->connection = connection;
	gb_connection_set_data(connection, supplies);

	mutex_init(&supplies->supplies_lock);

	greybus_set_drvdata(bundle, supplies);

	/* We aren't पढ़ोy to receive an incoming request yet */
	ret = gb_connection_enable_tx(connection);
	अगर (ret)
		जाओ error_connection_destroy;

	ret = gb_घातer_supplies_setup(supplies);
	अगर (ret < 0)
		जाओ error_connection_disable;

	/* We are पढ़ोy to receive an incoming request now, enable RX as well */
	ret = gb_connection_enable(connection);
	अगर (ret)
		जाओ error_connection_disable;

	ret = gb_घातer_supplies_रेजिस्टर(supplies);
	अगर (ret < 0)
		जाओ error_connection_disable;

	gb_pm_runसमय_put_स्वतःsuspend(bundle);
	वापस 0;

error_connection_disable:
	gb_connection_disable(connection);
error_connection_destroy:
	gb_connection_destroy(connection);
out:
	_gb_घातer_supplies_release(supplies);
	वापस ret;
पूर्ण

अटल व्योम gb_घातer_supply_disconnect(काष्ठा gb_bundle *bundle)
अणु
	काष्ठा gb_घातer_supplies *supplies = greybus_get_drvdata(bundle);

	gb_connection_disable(supplies->connection);
	gb_connection_destroy(supplies->connection);

	_gb_घातer_supplies_release(supplies);
पूर्ण

अटल स्थिर काष्ठा greybus_bundle_id gb_घातer_supply_id_table[] = अणु
	अणु GREYBUS_DEVICE_CLASS(GREYBUS_CLASS_POWER_SUPPLY) पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(greybus, gb_घातer_supply_id_table);

अटल काष्ठा greybus_driver gb_घातer_supply_driver = अणु
	.name		= "power_supply",
	.probe		= gb_घातer_supply_probe,
	.disconnect	= gb_घातer_supply_disconnect,
	.id_table	= gb_घातer_supply_id_table,
पूर्ण;
module_greybus_driver(gb_घातer_supply_driver);

MODULE_LICENSE("GPL v2");
