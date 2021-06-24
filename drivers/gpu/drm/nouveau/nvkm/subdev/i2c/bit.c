<शैली गुरु>
/*
 * Copyright 2012 Red Hat Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial busions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Authors: Ben Skeggs
 */
#समावेश "bus.h"

#अगर_घोषित CONFIG_NOUVEAU_I2C_INTERNAL
#घोषणा T_TIMEOUT  2200000
#घोषणा T_RISEFALL 1000
#घोषणा T_HOLD     5000

अटल अंतरभूत व्योम
nvkm_i2c_drive_scl(काष्ठा nvkm_i2c_bus *bus, पूर्णांक state)
अणु
	bus->func->drive_scl(bus, state);
पूर्ण

अटल अंतरभूत व्योम
nvkm_i2c_drive_sda(काष्ठा nvkm_i2c_bus *bus, पूर्णांक state)
अणु
	bus->func->drive_sda(bus, state);
पूर्ण

अटल अंतरभूत पूर्णांक
nvkm_i2c_sense_scl(काष्ठा nvkm_i2c_bus *bus)
अणु
	वापस bus->func->sense_scl(bus);
पूर्ण

अटल अंतरभूत पूर्णांक
nvkm_i2c_sense_sda(काष्ठा nvkm_i2c_bus *bus)
अणु
	वापस bus->func->sense_sda(bus);
पूर्ण

अटल व्योम
nvkm_i2c_delay(काष्ठा nvkm_i2c_bus *bus, u32 nsec)
अणु
	udelay((nsec + 500) / 1000);
पूर्ण

अटल bool
nvkm_i2c_उठाओ_scl(काष्ठा nvkm_i2c_bus *bus)
अणु
	u32 समयout = T_TIMEOUT / T_RISEFALL;

	nvkm_i2c_drive_scl(bus, 1);
	करो अणु
		nvkm_i2c_delay(bus, T_RISEFALL);
	पूर्ण जबतक (!nvkm_i2c_sense_scl(bus) && --समयout);

	वापस समयout != 0;
पूर्ण

अटल पूर्णांक
i2c_start(काष्ठा nvkm_i2c_bus *bus)
अणु
	पूर्णांक ret = 0;

	अगर (!nvkm_i2c_sense_scl(bus) ||
	    !nvkm_i2c_sense_sda(bus)) अणु
		nvkm_i2c_drive_scl(bus, 0);
		nvkm_i2c_drive_sda(bus, 1);
		अगर (!nvkm_i2c_उठाओ_scl(bus))
			ret = -EBUSY;
	पूर्ण

	nvkm_i2c_drive_sda(bus, 0);
	nvkm_i2c_delay(bus, T_HOLD);
	nvkm_i2c_drive_scl(bus, 0);
	nvkm_i2c_delay(bus, T_HOLD);
	वापस ret;
पूर्ण

अटल व्योम
i2c_stop(काष्ठा nvkm_i2c_bus *bus)
अणु
	nvkm_i2c_drive_scl(bus, 0);
	nvkm_i2c_drive_sda(bus, 0);
	nvkm_i2c_delay(bus, T_RISEFALL);

	nvkm_i2c_drive_scl(bus, 1);
	nvkm_i2c_delay(bus, T_HOLD);
	nvkm_i2c_drive_sda(bus, 1);
	nvkm_i2c_delay(bus, T_HOLD);
पूर्ण

अटल पूर्णांक
i2c_bitw(काष्ठा nvkm_i2c_bus *bus, पूर्णांक sda)
अणु
	nvkm_i2c_drive_sda(bus, sda);
	nvkm_i2c_delay(bus, T_RISEFALL);

	अगर (!nvkm_i2c_उठाओ_scl(bus))
		वापस -ETIMEDOUT;
	nvkm_i2c_delay(bus, T_HOLD);

	nvkm_i2c_drive_scl(bus, 0);
	nvkm_i2c_delay(bus, T_HOLD);
	वापस 0;
पूर्ण

अटल पूर्णांक
i2c_bitr(काष्ठा nvkm_i2c_bus *bus)
अणु
	पूर्णांक sda;

	nvkm_i2c_drive_sda(bus, 1);
	nvkm_i2c_delay(bus, T_RISEFALL);

	अगर (!nvkm_i2c_उठाओ_scl(bus))
		वापस -ETIMEDOUT;
	nvkm_i2c_delay(bus, T_HOLD);

	sda = nvkm_i2c_sense_sda(bus);

	nvkm_i2c_drive_scl(bus, 0);
	nvkm_i2c_delay(bus, T_HOLD);
	वापस sda;
पूर्ण

अटल पूर्णांक
nvkm_i2c_get_byte(काष्ठा nvkm_i2c_bus *bus, u8 *byte, bool last)
अणु
	पूर्णांक i, bit;

	*byte = 0;
	क्रम (i = 7; i >= 0; i--) अणु
		bit = i2c_bitr(bus);
		अगर (bit < 0)
			वापस bit;
		*byte |= bit << i;
	पूर्ण

	वापस i2c_bitw(bus, last ? 1 : 0);
पूर्ण

अटल पूर्णांक
nvkm_i2c_put_byte(काष्ठा nvkm_i2c_bus *bus, u8 byte)
अणु
	पूर्णांक i, ret;
	क्रम (i = 7; i >= 0; i--) अणु
		ret = i2c_bitw(bus, !!(byte & (1 << i)));
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	ret = i2c_bitr(bus);
	अगर (ret == 1) /* nack */
		ret = -EIO;
	वापस ret;
पूर्ण

अटल पूर्णांक
i2c_addr(काष्ठा nvkm_i2c_bus *bus, काष्ठा i2c_msg *msg)
अणु
	u32 addr = msg->addr << 1;
	अगर (msg->flags & I2C_M_RD)
		addr |= 1;
	वापस nvkm_i2c_put_byte(bus, addr);
पूर्ण

पूर्णांक
nvkm_i2c_bit_xfer(काष्ठा nvkm_i2c_bus *bus, काष्ठा i2c_msg *msgs, पूर्णांक num)
अणु
	काष्ठा i2c_msg *msg = msgs;
	पूर्णांक ret = 0, mcnt = num;

	जबतक (!ret && mcnt--) अणु
		u8 reमुख्यing = msg->len;
		u8 *ptr = msg->buf;

		ret = i2c_start(bus);
		अगर (ret == 0)
			ret = i2c_addr(bus, msg);

		अगर (msg->flags & I2C_M_RD) अणु
			जबतक (!ret && reमुख्यing--)
				ret = nvkm_i2c_get_byte(bus, ptr++, !reमुख्यing);
		पूर्ण अन्यथा अणु
			जबतक (!ret && reमुख्यing--)
				ret = nvkm_i2c_put_byte(bus, *ptr++);
		पूर्ण

		msg++;
	पूर्ण

	i2c_stop(bus);
	वापस (ret < 0) ? ret : num;
पूर्ण
#अन्यथा
पूर्णांक
nvkm_i2c_bit_xfer(काष्ठा nvkm_i2c_bus *bus, काष्ठा i2c_msg *msgs, पूर्णांक num)
अणु
	वापस -ENODEV;
पूर्ण
#पूर्ण_अगर
