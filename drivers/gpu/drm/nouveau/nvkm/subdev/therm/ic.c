<शैली गुरु>
/*
 * Copyright 2012 Nouveau community
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

#समावेश <subdev/bios/extdev.h>
#समावेश <subdev/i2c.h>

अटल bool
probe_monitoring_device(काष्ठा nvkm_i2c_bus *bus,
			काष्ठा i2c_board_info *info, व्योम *data)
अणु
	काष्ठा nvkm_therm *therm = data;
	काष्ठा nvbios_therm_sensor *sensor = &therm->bios_sensor;
	काष्ठा i2c_client *client;

	request_module("%s%s", I2C_MODULE_PREFIX, info->type);

	client = i2c_new_client_device(&bus->i2c, info);
	अगर (IS_ERR(client))
		वापस false;

	अगर (!client->dev.driver ||
	    to_i2c_driver(client->dev.driver)->detect(client, info)) अणु
		i2c_unरेजिस्टर_device(client);
		वापस false;
	पूर्ण

	nvkm_debug(&therm->subdev,
		   "Found an %s at address 0x%x (controlled by lm_sensors, "
		   "temp offset %+i C)\n",
		   info->type, info->addr, sensor->offset_स्थिरant);
	therm->ic = client;
	वापस true;
पूर्ण

अटल काष्ठा nvkm_i2c_bus_probe
nv_board_infos[] = अणु
	अणु अणु I2C_BOARD_INFO("w83l785ts", 0x2d) पूर्ण, 0 पूर्ण,
	अणु अणु I2C_BOARD_INFO("w83781d", 0x2d) पूर्ण, 0  पूर्ण,
	अणु अणु I2C_BOARD_INFO("adt7473", 0x2e) पूर्ण, 40  पूर्ण,
	अणु अणु I2C_BOARD_INFO("adt7473", 0x2d) पूर्ण, 40  पूर्ण,
	अणु अणु I2C_BOARD_INFO("adt7473", 0x2c) पूर्ण, 40  पूर्ण,
	अणु अणु I2C_BOARD_INFO("f75375", 0x2e) पूर्ण, 0  पूर्ण,
	अणु अणु I2C_BOARD_INFO("lm99", 0x4c) पूर्ण, 0  पूर्ण,
	अणु अणु I2C_BOARD_INFO("lm90", 0x4c) पूर्ण, 0  पूर्ण,
	अणु अणु I2C_BOARD_INFO("lm90", 0x4d) पूर्ण, 0  पूर्ण,
	अणु अणु I2C_BOARD_INFO("adm1021", 0x18) पूर्ण, 0  पूर्ण,
	अणु अणु I2C_BOARD_INFO("adm1021", 0x19) पूर्ण, 0  पूर्ण,
	अणु अणु I2C_BOARD_INFO("adm1021", 0x1a) पूर्ण, 0  पूर्ण,
	अणु अणु I2C_BOARD_INFO("adm1021", 0x29) पूर्ण, 0  पूर्ण,
	अणु अणु I2C_BOARD_INFO("adm1021", 0x2a) पूर्ण, 0  पूर्ण,
	अणु अणु I2C_BOARD_INFO("adm1021", 0x2b) पूर्ण, 0  पूर्ण,
	अणु अणु I2C_BOARD_INFO("adm1021", 0x4c) पूर्ण, 0  पूर्ण,
	अणु अणु I2C_BOARD_INFO("adm1021", 0x4d) पूर्ण, 0  पूर्ण,
	अणु अणु I2C_BOARD_INFO("adm1021", 0x4e) पूर्ण, 0  पूर्ण,
	अणु अणु I2C_BOARD_INFO("lm63", 0x18) पूर्ण, 0  पूर्ण,
	अणु अणु I2C_BOARD_INFO("lm63", 0x4e) पूर्ण, 0  पूर्ण,
	अणु पूर्ण
पूर्ण;

व्योम
nvkm_therm_ic_ctor(काष्ठा nvkm_therm *therm)
अणु
	काष्ठा nvkm_device *device = therm->subdev.device;
	काष्ठा nvkm_bios *bios = device->bios;
	काष्ठा nvkm_i2c *i2c = device->i2c;
	काष्ठा nvkm_i2c_bus *bus;
	काष्ठा nvbios_extdev_func extdev_entry;

	bus = nvkm_i2c_bus_find(i2c, NVKM_I2C_BUS_PRI);
	अगर (!bus)
		वापस;

	अगर (!nvbios_extdev_find(bios, NVBIOS_EXTDEV_LM89, &extdev_entry)) अणु
		काष्ठा nvkm_i2c_bus_probe board[] = अणु
		  अणु अणु I2C_BOARD_INFO("lm90", extdev_entry.addr >> 1) पूर्ण, 0पूर्ण,
		  अणु पूर्ण
		पूर्ण;

		nvkm_i2c_bus_probe(bus, "monitoring device", board,
				   probe_monitoring_device, therm);
		अगर (therm->ic)
			वापस;
	पूर्ण

	अगर (!nvbios_extdev_find(bios, NVBIOS_EXTDEV_ADT7473, &extdev_entry)) अणु
		काष्ठा nvkm_i2c_bus_probe board[] = अणु
		  अणु अणु I2C_BOARD_INFO("adt7473", extdev_entry.addr >> 1) पूर्ण, 20 पूर्ण,
		  अणु पूर्ण
		पूर्ण;

		nvkm_i2c_bus_probe(bus, "monitoring device", board,
				   probe_monitoring_device, therm);
		अगर (therm->ic)
			वापस;
	पूर्ण

	अगर (nvbios_extdev_skip_probe(bios))
		वापस;

	/* The vbios करोesn't provide the address of an exisiting monitoring
	   device. Let's try our अटल list.
	 */
	nvkm_i2c_bus_probe(bus, "monitoring device", nv_board_infos,
			   probe_monitoring_device, therm);
पूर्ण
