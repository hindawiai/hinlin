<शैली गुरु>
/*
 * Copyright 2015 Martin Peres
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Authors: Martin Peres
 */
#समावेश "priv.h"

#समावेश <subdev/मूलप्रण.स>
#समावेश <subdev/bios/extdev.h>
#समावेश <subdev/bios/iccsense.h>
#समावेश <subdev/bios/घातer_budget.h>
#समावेश <subdev/i2c.h>

अटल bool
nvkm_iccsense_validate_device(काष्ठा i2c_adapter *i2c, u8 addr,
			      क्रमागत nvbios_extdev_type type)
अणु
	चयन (type) अणु
	हाल NVBIOS_EXTDEV_INA209:
	हाल NVBIOS_EXTDEV_INA219:
		वापस nv_rd16i2cr(i2c, addr, 0x0) >= 0;
	हाल NVBIOS_EXTDEV_INA3221:
		वापस nv_rd16i2cr(i2c, addr, 0xff) == 0x3220 &&
		       nv_rd16i2cr(i2c, addr, 0xfe) == 0x5449;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल पूर्णांक
nvkm_iccsense_poll_lane(काष्ठा i2c_adapter *i2c, u8 addr, u8 shunt_reg,
			u8 shunt_shअगरt, u8 bus_reg, u8 bus_shअगरt, u8 shunt,
			u16 lsb)
अणु
	पूर्णांक vshunt = nv_rd16i2cr(i2c, addr, shunt_reg);
	पूर्णांक vbus = nv_rd16i2cr(i2c, addr, bus_reg);

	अगर (vshunt < 0 || vbus < 0)
		वापस -EINVAL;

	vshunt >>= shunt_shअगरt;
	vbus >>= bus_shअगरt;

	वापस vbus * vshunt * lsb / shunt;
पूर्ण

अटल पूर्णांक
nvkm_iccsense_ina2x9_पढ़ो(काष्ठा nvkm_iccsense *iccsense,
                          काष्ठा nvkm_iccsense_rail *rail,
			  u8 shunt_reg, u8 bus_reg)
अणु
	वापस nvkm_iccsense_poll_lane(rail->sensor->i2c, rail->sensor->addr,
				       shunt_reg, 0, bus_reg, 3, rail->mohm,
				       10 * 4);
पूर्ण

अटल पूर्णांक
nvkm_iccsense_ina209_पढ़ो(काष्ठा nvkm_iccsense *iccsense,
			  काष्ठा nvkm_iccsense_rail *rail)
अणु
	वापस nvkm_iccsense_ina2x9_पढ़ो(iccsense, rail, 3, 4);
पूर्ण

अटल पूर्णांक
nvkm_iccsense_ina219_पढ़ो(काष्ठा nvkm_iccsense *iccsense,
			  काष्ठा nvkm_iccsense_rail *rail)
अणु
	वापस nvkm_iccsense_ina2x9_पढ़ो(iccsense, rail, 1, 2);
पूर्ण

अटल पूर्णांक
nvkm_iccsense_ina3221_पढ़ो(काष्ठा nvkm_iccsense *iccsense,
			   काष्ठा nvkm_iccsense_rail *rail)
अणु
	वापस nvkm_iccsense_poll_lane(rail->sensor->i2c, rail->sensor->addr,
				       1 + (rail->idx * 2), 3,
				       2 + (rail->idx * 2), 3, rail->mohm,
				       40 * 8);
पूर्ण

अटल व्योम
nvkm_iccsense_sensor_config(काष्ठा nvkm_iccsense *iccsense,
		            काष्ठा nvkm_iccsense_sensor *sensor)
अणु
	काष्ठा nvkm_subdev *subdev = &iccsense->subdev;
	nvkm_trace(subdev, "write config of extdev %i: 0x%04x\n", sensor->id, sensor->config);
	nv_wr16i2cr(sensor->i2c, sensor->addr, 0x00, sensor->config);
पूर्ण

पूर्णांक
nvkm_iccsense_पढ़ो_all(काष्ठा nvkm_iccsense *iccsense)
अणु
	पूर्णांक result = 0;
	काष्ठा nvkm_iccsense_rail *rail;

	अगर (!iccsense)
		वापस -EINVAL;

	list_क्रम_each_entry(rail, &iccsense->rails, head) अणु
		पूर्णांक res;
		अगर (!rail->पढ़ो)
			वापस -ENODEV;

		res = rail->पढ़ो(iccsense, rail);
		अगर (res < 0)
			वापस res;
		result += res;
	पूर्ण
	वापस result;
पूर्ण

अटल व्योम *
nvkm_iccsense_dtor(काष्ठा nvkm_subdev *subdev)
अणु
	काष्ठा nvkm_iccsense *iccsense = nvkm_iccsense(subdev);
	काष्ठा nvkm_iccsense_sensor *sensor, *पंचांगps;
	काष्ठा nvkm_iccsense_rail *rail, *पंचांगpr;

	list_क्रम_each_entry_safe(sensor, पंचांगps, &iccsense->sensors, head) अणु
		list_del(&sensor->head);
		kमुक्त(sensor);
	पूर्ण
	list_क्रम_each_entry_safe(rail, पंचांगpr, &iccsense->rails, head) अणु
		list_del(&rail->head);
		kमुक्त(rail);
	पूर्ण

	वापस iccsense;
पूर्ण

अटल काष्ठा nvkm_iccsense_sensor*
nvkm_iccsense_create_sensor(काष्ठा nvkm_iccsense *iccsense, u8 id)
अणु
	काष्ठा nvkm_subdev *subdev = &iccsense->subdev;
	काष्ठा nvkm_bios *bios = subdev->device->bios;
	काष्ठा nvkm_i2c *i2c = subdev->device->i2c;
	काष्ठा nvbios_extdev_func extdev;
	काष्ठा nvkm_i2c_bus *i2c_bus;
	काष्ठा nvkm_iccsense_sensor *sensor;
	u8 addr;

	अगर (!i2c || !bios || nvbios_extdev_parse(bios, id, &extdev))
		वापस शून्य;

	अगर (extdev.type == 0xff)
		वापस शून्य;

	अगर (extdev.type != NVBIOS_EXTDEV_INA209 &&
	    extdev.type != NVBIOS_EXTDEV_INA219 &&
	    extdev.type != NVBIOS_EXTDEV_INA3221) अणु
		iccsense->data_valid = false;
		nvkm_error(subdev, "Unknown sensor type %x, power reading "
			   "disabled\n", extdev.type);
		वापस शून्य;
	पूर्ण

	अगर (extdev.bus)
		i2c_bus = nvkm_i2c_bus_find(i2c, NVKM_I2C_BUS_SEC);
	अन्यथा
		i2c_bus = nvkm_i2c_bus_find(i2c, NVKM_I2C_BUS_PRI);
	अगर (!i2c_bus)
		वापस शून्य;

	addr = extdev.addr >> 1;
	अगर (!nvkm_iccsense_validate_device(&i2c_bus->i2c, addr,
					   extdev.type)) अणु
		iccsense->data_valid = false;
		nvkm_warn(subdev, "found invalid sensor id: %i, power reading"
			  "might be invalid\n", id);
		वापस शून्य;
	पूर्ण

	sensor = kदो_स्मृति(माप(*sensor), GFP_KERNEL);
	अगर (!sensor)
		वापस शून्य;

	list_add_tail(&sensor->head, &iccsense->sensors);
	sensor->id = id;
	sensor->type = extdev.type;
	sensor->i2c = &i2c_bus->i2c;
	sensor->addr = addr;
	sensor->config = 0x0;
	वापस sensor;
पूर्ण

अटल काष्ठा nvkm_iccsense_sensor*
nvkm_iccsense_get_sensor(काष्ठा nvkm_iccsense *iccsense, u8 id)
अणु
	काष्ठा nvkm_iccsense_sensor *sensor;
	list_क्रम_each_entry(sensor, &iccsense->sensors, head) अणु
		अगर (sensor->id == id)
			वापस sensor;
	पूर्ण
	वापस nvkm_iccsense_create_sensor(iccsense, id);
पूर्ण

अटल पूर्णांक
nvkm_iccsense_oneinit(काष्ठा nvkm_subdev *subdev)
अणु
	काष्ठा nvkm_iccsense *iccsense = nvkm_iccsense(subdev);
	काष्ठा nvkm_bios *bios = subdev->device->bios;
	काष्ठा nvbios_घातer_budget budget;
	काष्ठा nvbios_iccsense stbl;
	पूर्णांक i, ret;

	अगर (!bios)
		वापस 0;

	ret = nvbios_घातer_budget_header(bios, &budget);
	अगर (!ret && budget.cap_entry != 0xff) अणु
		काष्ठा nvbios_घातer_budget_entry entry;
		ret = nvbios_घातer_budget_entry(bios, &budget,
		                                budget.cap_entry, &entry);
		अगर (!ret) अणु
			iccsense->घातer_w_max  = entry.avg_w;
			iccsense->घातer_w_crit = entry.max_w;
		पूर्ण
	पूर्ण

	अगर (nvbios_iccsense_parse(bios, &stbl) || !stbl.nr_entry)
		वापस 0;

	iccsense->data_valid = true;
	क्रम (i = 0; i < stbl.nr_entry; ++i) अणु
		काष्ठा pwr_rail_t *pwr_rail = &stbl.rail[i];
		काष्ठा nvkm_iccsense_sensor *sensor;
		पूर्णांक r;

		अगर (pwr_rail->mode != 1 || !pwr_rail->resistor_count)
			जारी;

		sensor = nvkm_iccsense_get_sensor(iccsense, pwr_rail->extdev_id);
		अगर (!sensor)
			जारी;

		अगर (!sensor->config)
			sensor->config = pwr_rail->config;
		अन्यथा अगर (sensor->config != pwr_rail->config)
			nvkm_error(subdev, "config mismatch found for extdev %i\n", pwr_rail->extdev_id);

		क्रम (r = 0; r < pwr_rail->resistor_count; ++r) अणु
			काष्ठा nvkm_iccsense_rail *rail;
			काष्ठा pwr_rail_resistor_t *res = &pwr_rail->resistors[r];
			पूर्णांक (*पढ़ो)(काष्ठा nvkm_iccsense *,
				    काष्ठा nvkm_iccsense_rail *);

			अगर (!res->mohm || !res->enabled)
				जारी;

			चयन (sensor->type) अणु
			हाल NVBIOS_EXTDEV_INA209:
				पढ़ो = nvkm_iccsense_ina209_पढ़ो;
				अवरोध;
			हाल NVBIOS_EXTDEV_INA219:
				पढ़ो = nvkm_iccsense_ina219_पढ़ो;
				अवरोध;
			हाल NVBIOS_EXTDEV_INA3221:
				पढ़ो = nvkm_iccsense_ina3221_पढ़ो;
				अवरोध;
			शेष:
				जारी;
			पूर्ण

			rail = kदो_स्मृति(माप(*rail), GFP_KERNEL);
			अगर (!rail)
				वापस -ENOMEM;

			rail->पढ़ो = पढ़ो;
			rail->sensor = sensor;
			rail->idx = r;
			rail->mohm = res->mohm;
			nvkm_debug(subdev, "create rail for extdev %i: { idx: %i, mohm: %i }\n", pwr_rail->extdev_id, r, rail->mohm);
			list_add_tail(&rail->head, &iccsense->rails);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक
nvkm_iccsense_init(काष्ठा nvkm_subdev *subdev)
अणु
	काष्ठा nvkm_iccsense *iccsense = nvkm_iccsense(subdev);
	काष्ठा nvkm_iccsense_sensor *sensor;
	list_क्रम_each_entry(sensor, &iccsense->sensors, head)
		nvkm_iccsense_sensor_config(iccsense, sensor);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा nvkm_subdev_func
iccsense_func = अणु
	.oneinit = nvkm_iccsense_oneinit,
	.init = nvkm_iccsense_init,
	.dtor = nvkm_iccsense_dtor,
पूर्ण;

व्योम
nvkm_iccsense_ctor(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst,
		   काष्ठा nvkm_iccsense *iccsense)
अणु
	nvkm_subdev_ctor(&iccsense_func, device, type, inst, &iccsense->subdev);
पूर्ण

पूर्णांक
nvkm_iccsense_new_(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst,
		   काष्ठा nvkm_iccsense **iccsense)
अणु
	अगर (!(*iccsense = kzalloc(माप(**iccsense), GFP_KERNEL)))
		वापस -ENOMEM;
	INIT_LIST_HEAD(&(*iccsense)->sensors);
	INIT_LIST_HEAD(&(*iccsense)->rails);
	nvkm_iccsense_ctor(device, type, inst, *iccsense);
	वापस 0;
पूर्ण
