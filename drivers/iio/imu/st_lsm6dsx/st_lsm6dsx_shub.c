<शैली गुरु>
/*
 * STMicroelectronics st_lsm6dsx i2c controller driver
 *
 * i2c controller embedded in lsm6dx series can connect up to four
 * slave devices using accelerometer sensor as trigger क्रम i2c
 * पढ़ो/ग_लिखो operations. Current implementation relies on SLV0 channel
 * क्रम slave configuration and SLVअणु1,2,3पूर्ण to पढ़ो data and push them पूर्णांकo
 * the hw FIFO
 *
 * Copyright (C) 2018 Lorenzo Bianconi <lorenzo.bianconi83@gmail.com>
 *
 * Permission to use, copy, modअगरy, and/or distribute this software क्रम any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, सूचीECT, INसूचीECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 */
#समावेश <linux/module.h>
#समावेश <linux/regmap.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/bitfield.h>

#समावेश "st_lsm6dsx.h"

#घोषणा ST_LSM6DSX_SLV_ADDR(n, base)		((base) + (n) * 3)
#घोषणा ST_LSM6DSX_SLV_SUB_ADDR(n, base)	((base) + 1 + (n) * 3)
#घोषणा ST_LSM6DSX_SLV_CONFIG(n, base)		((base) + 2 + (n) * 3)

#घोषणा ST_LS6DSX_READ_OP_MASK			GENMASK(2, 0)

अटल स्थिर काष्ठा st_lsm6dsx_ext_dev_settings st_lsm6dsx_ext_dev_table[] = अणु
	/* LIS2MDL */
	अणु
		.i2c_addr = अणु 0x1e पूर्ण,
		.wai = अणु
			.addr = 0x4f,
			.val = 0x40,
		पूर्ण,
		.id = ST_LSM6DSX_ID_MAGN,
		.odr_table = अणु
			.reg = अणु
				.addr = 0x60,
				.mask = GENMASK(3, 2),
			पूर्ण,
			.odr_avl[0] = अणु  10000, 0x0 पूर्ण,
			.odr_avl[1] = अणु  20000, 0x1 पूर्ण,
			.odr_avl[2] = अणु  50000, 0x2 पूर्ण,
			.odr_avl[3] = अणु 100000, 0x3 पूर्ण,
			.odr_len = 4,
		पूर्ण,
		.fs_table = अणु
			.fs_avl[0] = अणु
				.gain = 1500,
				.val = 0x0,
			पूर्ण, /* 1500 uG/LSB */
			.fs_len = 1,
		पूर्ण,
		.temp_comp = अणु
			.addr = 0x60,
			.mask = BIT(7),
		पूर्ण,
		.pwr_table = अणु
			.reg = अणु
				.addr = 0x60,
				.mask = GENMASK(1, 0),
			पूर्ण,
			.off_val = 0x2,
			.on_val = 0x0,
		पूर्ण,
		.off_canc = अणु
			.addr = 0x61,
			.mask = BIT(1),
		पूर्ण,
		.bdu = अणु
			.addr = 0x62,
			.mask = BIT(4),
		पूर्ण,
		.out = अणु
			.addr = 0x68,
			.len = 6,
		पूर्ण,
	पूर्ण,
	/* LIS3MDL */
	अणु
		.i2c_addr = अणु 0x1e पूर्ण,
		.wai = अणु
			.addr = 0x0f,
			.val = 0x3d,
		पूर्ण,
		.id = ST_LSM6DSX_ID_MAGN,
		.odr_table = अणु
			.reg = अणु
				.addr = 0x20,
				.mask = GENMASK(4, 2),
			पूर्ण,
			.odr_avl[0] = अणु  1000, 0x0 पूर्ण,
			.odr_avl[1] = अणु  2000, 0x1 पूर्ण,
			.odr_avl[2] = अणु  3000, 0x2 पूर्ण,
			.odr_avl[3] = अणु  5000, 0x3 पूर्ण,
			.odr_avl[4] = अणु 10000, 0x4 पूर्ण,
			.odr_avl[5] = अणु 20000, 0x5 पूर्ण,
			.odr_avl[6] = अणु 40000, 0x6 पूर्ण,
			.odr_avl[7] = अणु 80000, 0x7 पूर्ण,
			.odr_len = 8,
		पूर्ण,
		.fs_table = अणु
			.reg = अणु
				.addr = 0x21,
				.mask = GENMASK(6, 5),
			पूर्ण,
			.fs_avl[0] = अणु
				.gain = 146,
				.val = 0x00,
			पूर्ण, /* 4000 uG/LSB */
			.fs_avl[1] = अणु
				.gain = 292,
				.val = 0x01,
			पूर्ण, /* 8000 uG/LSB */
			.fs_avl[2] = अणु
				.gain = 438,
				.val = 0x02,
			पूर्ण, /* 12000 uG/LSB */
			.fs_avl[3] = अणु
				.gain = 584,
				.val = 0x03,
			पूर्ण, /* 16000 uG/LSB */
			.fs_len = 4,
		पूर्ण,
		.pwr_table = अणु
			.reg = अणु
				.addr = 0x22,
				.mask = GENMASK(1, 0),
			पूर्ण,
			.off_val = 0x2,
			.on_val = 0x0,
		पूर्ण,
		.bdu = अणु
			.addr = 0x24,
			.mask = BIT(6),
		पूर्ण,
		.out = अणु
			.addr = 0x28,
			.len = 6,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल व्योम st_lsm6dsx_shub_रुको_complete(काष्ठा st_lsm6dsx_hw *hw)
अणु
	काष्ठा st_lsm6dsx_sensor *sensor;
	u32 odr, समयout;

	sensor = iio_priv(hw->iio_devs[ST_LSM6DSX_ID_ACC]);
	odr = (hw->enable_mask & BIT(ST_LSM6DSX_ID_ACC)) ? sensor->odr : 12500;
	/* set 10ms as minimum समयout क्रम i2c slave configuration */
	समयout = max_t(u32, 2000000U / odr + 1, 10);
	msleep(समयout);
पूर्ण

/*
 * st_lsm6dsx_shub_पढ़ो_output - पढ़ो i2c controller रेजिस्टर
 *
 * Read st_lsm6dsx i2c controller रेजिस्टर
 */
अटल पूर्णांक
st_lsm6dsx_shub_पढ़ो_output(काष्ठा st_lsm6dsx_hw *hw, u8 *data,
			    पूर्णांक len)
अणु
	स्थिर काष्ठा st_lsm6dsx_shub_settings *hub_settings;
	पूर्णांक err;

	mutex_lock(&hw->page_lock);

	hub_settings = &hw->settings->shub_settings;
	अगर (hub_settings->shub_out.sec_page) अणु
		err = st_lsm6dsx_set_page(hw, true);
		अगर (err < 0)
			जाओ out;
	पूर्ण

	err = regmap_bulk_पढ़ो(hw->regmap, hub_settings->shub_out.addr,
			       data, len);

	अगर (hub_settings->shub_out.sec_page)
		st_lsm6dsx_set_page(hw, false);
out:
	mutex_unlock(&hw->page_lock);

	वापस err;
पूर्ण

/*
 * st_lsm6dsx_shub_ग_लिखो_reg - ग_लिखो i2c controller रेजिस्टर
 *
 * Write st_lsm6dsx i2c controller रेजिस्टर
 */
अटल पूर्णांक st_lsm6dsx_shub_ग_लिखो_reg(काष्ठा st_lsm6dsx_hw *hw, u8 addr,
				     u8 *data, पूर्णांक len)
अणु
	पूर्णांक err;

	mutex_lock(&hw->page_lock);
	err = st_lsm6dsx_set_page(hw, true);
	अगर (err < 0)
		जाओ out;

	err = regmap_bulk_ग_लिखो(hw->regmap, addr, data, len);

	st_lsm6dsx_set_page(hw, false);
out:
	mutex_unlock(&hw->page_lock);

	वापस err;
पूर्ण

अटल पूर्णांक
st_lsm6dsx_shub_ग_लिखो_reg_with_mask(काष्ठा st_lsm6dsx_hw *hw, u8 addr,
				    u8 mask, u8 val)
अणु
	पूर्णांक err;

	mutex_lock(&hw->page_lock);
	err = st_lsm6dsx_set_page(hw, true);
	अगर (err < 0)
		जाओ out;

	err = regmap_update_bits(hw->regmap, addr, mask, val);

	st_lsm6dsx_set_page(hw, false);
out:
	mutex_unlock(&hw->page_lock);

	वापस err;
पूर्ण

अटल पूर्णांक st_lsm6dsx_shub_master_enable(काष्ठा st_lsm6dsx_sensor *sensor,
					 bool enable)
अणु
	स्थिर काष्ठा st_lsm6dsx_shub_settings *hub_settings;
	काष्ठा st_lsm6dsx_hw *hw = sensor->hw;
	अचिन्हित पूर्णांक data;
	पूर्णांक err;

	/* enable acc sensor as trigger */
	err = st_lsm6dsx_sensor_set_enable(sensor, enable);
	अगर (err < 0)
		वापस err;

	mutex_lock(&hw->page_lock);

	hub_settings = &hw->settings->shub_settings;
	अगर (hub_settings->master_en.sec_page) अणु
		err = st_lsm6dsx_set_page(hw, true);
		अगर (err < 0)
			जाओ out;
	पूर्ण

	data = ST_LSM6DSX_SHIFT_VAL(enable, hub_settings->master_en.mask);
	err = regmap_update_bits(hw->regmap, hub_settings->master_en.addr,
				 hub_settings->master_en.mask, data);

	अगर (hub_settings->master_en.sec_page)
		st_lsm6dsx_set_page(hw, false);
out:
	mutex_unlock(&hw->page_lock);

	वापस err;
पूर्ण

/*
 * st_lsm6dsx_shub_पढ़ो - पढ़ो data from slave device रेजिस्टर
 *
 * Read data from slave device रेजिस्टर. SLV0 is used क्रम
 * one-shot पढ़ो operation
 */
अटल पूर्णांक
st_lsm6dsx_shub_पढ़ो(काष्ठा st_lsm6dsx_sensor *sensor, u8 addr,
		     u8 *data, पूर्णांक len)
अणु
	स्थिर काष्ठा st_lsm6dsx_shub_settings *hub_settings;
	u8 config[3], slv_addr, slv_config = 0;
	काष्ठा st_lsm6dsx_hw *hw = sensor->hw;
	स्थिर काष्ठा st_lsm6dsx_reg *aux_sens;
	पूर्णांक err;

	hub_settings = &hw->settings->shub_settings;
	slv_addr = ST_LSM6DSX_SLV_ADDR(0, hub_settings->slv0_addr);
	aux_sens = &hw->settings->shub_settings.aux_sens;
	/* करो not overग_लिखो aux_sens */
	अगर (slv_addr + 2 == aux_sens->addr)
		slv_config = ST_LSM6DSX_SHIFT_VAL(3, aux_sens->mask);

	config[0] = (sensor->ext_info.addr << 1) | 1;
	config[1] = addr;
	config[2] = (len & ST_LS6DSX_READ_OP_MASK) | slv_config;

	err = st_lsm6dsx_shub_ग_लिखो_reg(hw, slv_addr, config,
					माप(config));
	अगर (err < 0)
		वापस err;

	err = st_lsm6dsx_shub_master_enable(sensor, true);
	अगर (err < 0)
		वापस err;

	st_lsm6dsx_shub_रुको_complete(hw);

	err = st_lsm6dsx_shub_पढ़ो_output(hw, data,
					  len & ST_LS6DSX_READ_OP_MASK);
	अगर (err < 0)
		वापस err;

	st_lsm6dsx_shub_master_enable(sensor, false);

	config[0] = hub_settings->छोड़ो;
	config[1] = 0;
	config[2] = slv_config;
	वापस st_lsm6dsx_shub_ग_लिखो_reg(hw, slv_addr, config,
					 माप(config));
पूर्ण

/*
 * st_lsm6dsx_shub_ग_लिखो - ग_लिखो data to slave device रेजिस्टर
 *
 * Write data from slave device रेजिस्टर. SLV0 is used क्रम
 * one-shot ग_लिखो operation
 */
अटल पूर्णांक
st_lsm6dsx_shub_ग_लिखो(काष्ठा st_lsm6dsx_sensor *sensor, u8 addr,
		      u8 *data, पूर्णांक len)
अणु
	स्थिर काष्ठा st_lsm6dsx_shub_settings *hub_settings;
	काष्ठा st_lsm6dsx_hw *hw = sensor->hw;
	u8 config[2], slv_addr;
	पूर्णांक err, i;

	hub_settings = &hw->settings->shub_settings;
	अगर (hub_settings->wr_once.addr) अणु
		अचिन्हित पूर्णांक data;

		data = ST_LSM6DSX_SHIFT_VAL(1, hub_settings->wr_once.mask);
		err = st_lsm6dsx_shub_ग_लिखो_reg_with_mask(hw,
			hub_settings->wr_once.addr,
			hub_settings->wr_once.mask,
			data);
		अगर (err < 0)
			वापस err;
	पूर्ण

	slv_addr = ST_LSM6DSX_SLV_ADDR(0, hub_settings->slv0_addr);
	config[0] = sensor->ext_info.addr << 1;
	क्रम (i = 0 ; i < len; i++) अणु
		config[1] = addr + i;

		err = st_lsm6dsx_shub_ग_लिखो_reg(hw, slv_addr, config,
						माप(config));
		अगर (err < 0)
			वापस err;

		err = st_lsm6dsx_shub_ग_लिखो_reg(hw, hub_settings->dw_slv0_addr,
						&data[i], 1);
		अगर (err < 0)
			वापस err;

		err = st_lsm6dsx_shub_master_enable(sensor, true);
		अगर (err < 0)
			वापस err;

		st_lsm6dsx_shub_रुको_complete(hw);

		st_lsm6dsx_shub_master_enable(sensor, false);
	पूर्ण

	config[0] = hub_settings->छोड़ो;
	config[1] = 0;
	वापस st_lsm6dsx_shub_ग_लिखो_reg(hw, slv_addr, config, माप(config));
पूर्ण

अटल पूर्णांक
st_lsm6dsx_shub_ग_लिखो_with_mask(काष्ठा st_lsm6dsx_sensor *sensor,
				u8 addr, u8 mask, u8 val)
अणु
	पूर्णांक err;
	u8 data;

	err = st_lsm6dsx_shub_पढ़ो(sensor, addr, &data, माप(data));
	अगर (err < 0)
		वापस err;

	data = ((data & ~mask) | (val << __ffs(mask) & mask));

	वापस st_lsm6dsx_shub_ग_लिखो(sensor, addr, &data, माप(data));
पूर्ण

अटल पूर्णांक
st_lsm6dsx_shub_get_odr_val(काष्ठा st_lsm6dsx_sensor *sensor,
			    u32 odr, u16 *val)
अणु
	स्थिर काष्ठा st_lsm6dsx_ext_dev_settings *settings;
	पूर्णांक i;

	settings = sensor->ext_info.settings;
	क्रम (i = 0; i < settings->odr_table.odr_len; i++) अणु
		अगर (settings->odr_table.odr_avl[i].milli_hz == odr)
			अवरोध;
	पूर्ण

	अगर (i == settings->odr_table.odr_len)
		वापस -EINVAL;

	*val = settings->odr_table.odr_avl[i].val;
	वापस 0;
पूर्ण

अटल पूर्णांक
st_lsm6dsx_shub_set_odr(काष्ठा st_lsm6dsx_sensor *sensor, u32 odr)
अणु
	स्थिर काष्ठा st_lsm6dsx_ext_dev_settings *settings;
	u16 val;
	पूर्णांक err;

	err = st_lsm6dsx_shub_get_odr_val(sensor, odr, &val);
	अगर (err < 0)
		वापस err;

	settings = sensor->ext_info.settings;
	वापस st_lsm6dsx_shub_ग_लिखो_with_mask(sensor,
					       settings->odr_table.reg.addr,
					       settings->odr_table.reg.mask,
					       val);
पूर्ण

/* use SLVअणु1,2,3पूर्ण क्रम FIFO पढ़ो operations */
अटल पूर्णांक
st_lsm6dsx_shub_config_channels(काष्ठा st_lsm6dsx_sensor *sensor,
				bool enable)
अणु
	स्थिर काष्ठा st_lsm6dsx_shub_settings *hub_settings;
	स्थिर काष्ठा st_lsm6dsx_ext_dev_settings *settings;
	u8 config[9] = अणुपूर्ण, enable_mask, slv_addr;
	काष्ठा st_lsm6dsx_hw *hw = sensor->hw;
	काष्ठा st_lsm6dsx_sensor *cur_sensor;
	पूर्णांक i, j = 0;

	hub_settings = &hw->settings->shub_settings;
	अगर (enable)
		enable_mask = hw->enable_mask | BIT(sensor->id);
	अन्यथा
		enable_mask = hw->enable_mask & ~BIT(sensor->id);

	क्रम (i = ST_LSM6DSX_ID_EXT0; i <= ST_LSM6DSX_ID_EXT2; i++) अणु
		अगर (!hw->iio_devs[i])
			जारी;

		cur_sensor = iio_priv(hw->iio_devs[i]);
		अगर (!(enable_mask & BIT(cur_sensor->id)))
			जारी;

		settings = cur_sensor->ext_info.settings;
		config[j] = (sensor->ext_info.addr << 1) | 1;
		config[j + 1] = settings->out.addr;
		config[j + 2] = (settings->out.len & ST_LS6DSX_READ_OP_MASK) |
				hub_settings->batch_en;
		j += 3;
	पूर्ण

	slv_addr = ST_LSM6DSX_SLV_ADDR(1, hub_settings->slv0_addr);
	वापस st_lsm6dsx_shub_ग_लिखो_reg(hw, slv_addr, config,
					 माप(config));
पूर्ण

पूर्णांक st_lsm6dsx_shub_set_enable(काष्ठा st_lsm6dsx_sensor *sensor, bool enable)
अणु
	स्थिर काष्ठा st_lsm6dsx_ext_dev_settings *settings;
	पूर्णांक err;

	err = st_lsm6dsx_shub_config_channels(sensor, enable);
	अगर (err < 0)
		वापस err;

	settings = sensor->ext_info.settings;
	अगर (enable) अणु
		err = st_lsm6dsx_shub_set_odr(sensor,
					      sensor->ext_info.slv_odr);
		अगर (err < 0)
			वापस err;
	पूर्ण अन्यथा अणु
		err = st_lsm6dsx_shub_ग_लिखो_with_mask(sensor,
					settings->odr_table.reg.addr,
					settings->odr_table.reg.mask, 0);
		अगर (err < 0)
			वापस err;
	पूर्ण

	अगर (settings->pwr_table.reg.addr) अणु
		u8 val;

		val = enable ? settings->pwr_table.on_val
			     : settings->pwr_table.off_val;
		err = st_lsm6dsx_shub_ग_लिखो_with_mask(sensor,
					settings->pwr_table.reg.addr,
					settings->pwr_table.reg.mask, val);
		अगर (err < 0)
			वापस err;
	पूर्ण

	वापस st_lsm6dsx_shub_master_enable(sensor, enable);
पूर्ण

अटल पूर्णांक
st_lsm6dsx_shub_पढ़ो_oneshot(काष्ठा st_lsm6dsx_sensor *sensor,
			     काष्ठा iio_chan_spec स्थिर *ch,
			     पूर्णांक *val)
अणु
	पूर्णांक err, delay, len;
	u8 data[4];

	err = st_lsm6dsx_shub_set_enable(sensor, true);
	अगर (err < 0)
		वापस err;

	delay = 1000000000 / sensor->ext_info.slv_odr;
	usleep_range(delay, 2 * delay);

	len = min_t(पूर्णांक, माप(data), ch->scan_type.realbits >> 3);
	err = st_lsm6dsx_shub_पढ़ो(sensor, ch->address, data, len);
	अगर (err < 0)
		वापस err;

	err = st_lsm6dsx_shub_set_enable(sensor, false);
	अगर (err < 0)
		वापस err;

	चयन (len) अणु
	हाल 2:
		*val = (s16)le16_to_cpu(*((__le16 *)data));
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस IIO_VAL_INT;
पूर्ण

अटल पूर्णांक
st_lsm6dsx_shub_पढ़ो_raw(काष्ठा iio_dev *iio_dev,
			 काष्ठा iio_chan_spec स्थिर *ch,
			 पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा st_lsm6dsx_sensor *sensor = iio_priv(iio_dev);
	पूर्णांक ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		ret = iio_device_claim_direct_mode(iio_dev);
		अगर (ret)
			अवरोध;

		ret = st_lsm6dsx_shub_पढ़ो_oneshot(sensor, ch, val);
		iio_device_release_direct_mode(iio_dev);
		अवरोध;
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		*val = sensor->ext_info.slv_odr / 1000;
		*val2 = (sensor->ext_info.slv_odr % 1000) * 1000;
		ret = IIO_VAL_INT_PLUS_MICRO;
		अवरोध;
	हाल IIO_CHAN_INFO_SCALE:
		*val = 0;
		*val2 = sensor->gain;
		ret = IIO_VAL_INT_PLUS_MICRO;
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक
st_lsm6dsx_shub_set_full_scale(काष्ठा st_lsm6dsx_sensor *sensor,
			       u32 gain)
अणु
	स्थिर काष्ठा st_lsm6dsx_fs_table_entry *fs_table;
	पूर्णांक i, err;

	fs_table = &sensor->ext_info.settings->fs_table;
	अगर (!fs_table->reg.addr)
		वापस -ENOTSUPP;

	क्रम (i = 0; i < fs_table->fs_len; i++) अणु
		अगर (fs_table->fs_avl[i].gain == gain)
			अवरोध;
	पूर्ण

	अगर (i == fs_table->fs_len)
		वापस -EINVAL;

	err = st_lsm6dsx_shub_ग_लिखो_with_mask(sensor, fs_table->reg.addr,
					      fs_table->reg.mask,
					      fs_table->fs_avl[i].val);
	अगर (err < 0)
		वापस err;

	sensor->gain = gain;

	वापस 0;
पूर्ण

अटल पूर्णांक
st_lsm6dsx_shub_ग_लिखो_raw(काष्ठा iio_dev *iio_dev,
			  काष्ठा iio_chan_spec स्थिर *chan,
			  पूर्णांक val, पूर्णांक val2, दीर्घ mask)
अणु
	काष्ठा st_lsm6dsx_sensor *sensor = iio_priv(iio_dev);
	पूर्णांक err;

	err = iio_device_claim_direct_mode(iio_dev);
	अगर (err)
		वापस err;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_SAMP_FREQ: अणु
		u16 data;

		val = val * 1000 + val2 / 1000;
		err = st_lsm6dsx_shub_get_odr_val(sensor, val, &data);
		अगर (!err) अणु
			काष्ठा st_lsm6dsx_hw *hw = sensor->hw;
			काष्ठा st_lsm6dsx_sensor *ref_sensor;
			u8 odr_val;
			पूर्णांक odr;

			ref_sensor = iio_priv(hw->iio_devs[ST_LSM6DSX_ID_ACC]);
			odr = st_lsm6dsx_check_odr(ref_sensor, val, &odr_val);
			अगर (odr < 0) अणु
				err = odr;
				जाओ release;
			पूर्ण

			sensor->ext_info.slv_odr = val;
			sensor->odr = odr;
		पूर्ण
		अवरोध;
	पूर्ण
	हाल IIO_CHAN_INFO_SCALE:
		err = st_lsm6dsx_shub_set_full_scale(sensor, val2);
		अवरोध;
	शेष:
		err = -EINVAL;
		अवरोध;
	पूर्ण

release:
	iio_device_release_direct_mode(iio_dev);

	वापस err;
पूर्ण

अटल sमाप_प्रकार
st_lsm6dsx_shub_sampling_freq_avail(काष्ठा device *dev,
				    काष्ठा device_attribute *attr,
				    अक्षर *buf)
अणु
	काष्ठा st_lsm6dsx_sensor *sensor = iio_priv(dev_get_drvdata(dev));
	स्थिर काष्ठा st_lsm6dsx_ext_dev_settings *settings;
	पूर्णांक i, len = 0;

	settings = sensor->ext_info.settings;
	क्रम (i = 0; i < settings->odr_table.odr_len; i++) अणु
		u32 val = settings->odr_table.odr_avl[i].milli_hz;

		len += scnम_लिखो(buf + len, PAGE_SIZE - len, "%d.%03d ",
				 val / 1000, val % 1000);
	पूर्ण
	buf[len - 1] = '\n';

	वापस len;
पूर्ण

अटल sमाप_प्रकार st_lsm6dsx_shub_scale_avail(काष्ठा device *dev,
					   काष्ठा device_attribute *attr,
					   अक्षर *buf)
अणु
	काष्ठा st_lsm6dsx_sensor *sensor = iio_priv(dev_get_drvdata(dev));
	स्थिर काष्ठा st_lsm6dsx_ext_dev_settings *settings;
	पूर्णांक i, len = 0;

	settings = sensor->ext_info.settings;
	क्रम (i = 0; i < settings->fs_table.fs_len; i++)
		len += scnम_लिखो(buf + len, PAGE_SIZE - len, "0.%06u ",
				 settings->fs_table.fs_avl[i].gain);
	buf[len - 1] = '\n';

	वापस len;
पूर्ण

अटल IIO_DEV_ATTR_SAMP_FREQ_AVAIL(st_lsm6dsx_shub_sampling_freq_avail);
अटल IIO_DEVICE_ATTR(in_scale_available, 0444,
		       st_lsm6dsx_shub_scale_avail, शून्य, 0);
अटल काष्ठा attribute *st_lsm6dsx_ext_attributes[] = अणु
	&iio_dev_attr_sampling_frequency_available.dev_attr.attr,
	&iio_dev_attr_in_scale_available.dev_attr.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group st_lsm6dsx_ext_attribute_group = अणु
	.attrs = st_lsm6dsx_ext_attributes,
पूर्ण;

अटल स्थिर काष्ठा iio_info st_lsm6dsx_ext_info = अणु
	.attrs = &st_lsm6dsx_ext_attribute_group,
	.पढ़ो_raw = st_lsm6dsx_shub_पढ़ो_raw,
	.ग_लिखो_raw = st_lsm6dsx_shub_ग_लिखो_raw,
	.hwfअगरo_set_watermark = st_lsm6dsx_set_watermark,
पूर्ण;

अटल काष्ठा iio_dev *
st_lsm6dsx_shub_alloc_iiodev(काष्ठा st_lsm6dsx_hw *hw,
			     क्रमागत st_lsm6dsx_sensor_id id,
			     स्थिर काष्ठा st_lsm6dsx_ext_dev_settings *info,
			     u8 i2c_addr, स्थिर अक्षर *name)
अणु
	क्रमागत st_lsm6dsx_sensor_id ref_id = ST_LSM6DSX_ID_ACC;
	काष्ठा iio_chan_spec *ext_channels;
	काष्ठा st_lsm6dsx_sensor *sensor;
	काष्ठा iio_dev *iio_dev;

	iio_dev = devm_iio_device_alloc(hw->dev, माप(*sensor));
	अगर (!iio_dev)
		वापस शून्य;

	iio_dev->modes = INDIO_सूचीECT_MODE;
	iio_dev->info = &st_lsm6dsx_ext_info;

	sensor = iio_priv(iio_dev);
	sensor->id = id;
	sensor->hw = hw;
	sensor->odr = hw->settings->odr_table[ref_id].odr_avl[0].milli_hz;
	sensor->ext_info.slv_odr = info->odr_table.odr_avl[0].milli_hz;
	sensor->gain = info->fs_table.fs_avl[0].gain;
	sensor->ext_info.settings = info;
	sensor->ext_info.addr = i2c_addr;
	sensor->watermark = 1;

	चयन (info->id) अणु
	हाल ST_LSM6DSX_ID_MAGN: अणु
		स्थिर काष्ठा iio_chan_spec magn_channels[] = अणु
			ST_LSM6DSX_CHANNEL(IIO_MAGN, info->out.addr,
					   IIO_MOD_X, 0),
			ST_LSM6DSX_CHANNEL(IIO_MAGN, info->out.addr + 2,
					   IIO_MOD_Y, 1),
			ST_LSM6DSX_CHANNEL(IIO_MAGN, info->out.addr + 4,
					   IIO_MOD_Z, 2),
			IIO_CHAN_SOFT_TIMESTAMP(3),
		पूर्ण;

		ext_channels = devm_kzalloc(hw->dev, माप(magn_channels),
					    GFP_KERNEL);
		अगर (!ext_channels)
			वापस शून्य;

		स_नकल(ext_channels, magn_channels, माप(magn_channels));
		iio_dev->available_scan_masks = st_lsm6dsx_available_scan_masks;
		iio_dev->channels = ext_channels;
		iio_dev->num_channels = ARRAY_SIZE(magn_channels);

		scnम_लिखो(sensor->name, माप(sensor->name), "%s_magn",
			  name);
		अवरोध;
	पूर्ण
	शेष:
		वापस शून्य;
	पूर्ण
	iio_dev->name = sensor->name;

	वापस iio_dev;
पूर्ण

अटल पूर्णांक st_lsm6dsx_shub_init_device(काष्ठा st_lsm6dsx_sensor *sensor)
अणु
	स्थिर काष्ठा st_lsm6dsx_ext_dev_settings *settings;
	पूर्णांक err;

	settings = sensor->ext_info.settings;
	अगर (settings->bdu.addr) अणु
		err = st_lsm6dsx_shub_ग_लिखो_with_mask(sensor,
						      settings->bdu.addr,
						      settings->bdu.mask, 1);
		अगर (err < 0)
			वापस err;
	पूर्ण

	अगर (settings->temp_comp.addr) अणु
		err = st_lsm6dsx_shub_ग_लिखो_with_mask(sensor,
					settings->temp_comp.addr,
					settings->temp_comp.mask, 1);
		अगर (err < 0)
			वापस err;
	पूर्ण

	अगर (settings->off_canc.addr) अणु
		err = st_lsm6dsx_shub_ग_लिखो_with_mask(sensor,
					settings->off_canc.addr,
					settings->off_canc.mask, 1);
		अगर (err < 0)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
st_lsm6dsx_shub_check_wai(काष्ठा st_lsm6dsx_hw *hw, u8 *i2c_addr,
			  स्थिर काष्ठा st_lsm6dsx_ext_dev_settings *settings)
अणु
	स्थिर काष्ठा st_lsm6dsx_shub_settings *hub_settings;
	u8 config[3], data, slv_addr, slv_config = 0;
	स्थिर काष्ठा st_lsm6dsx_reg *aux_sens;
	काष्ठा st_lsm6dsx_sensor *sensor;
	bool found = false;
	पूर्णांक i, err;

	sensor = iio_priv(hw->iio_devs[ST_LSM6DSX_ID_ACC]);
	hub_settings = &hw->settings->shub_settings;
	aux_sens = &hw->settings->shub_settings.aux_sens;
	slv_addr = ST_LSM6DSX_SLV_ADDR(0, hub_settings->slv0_addr);
	/* करो not overग_लिखो aux_sens */
	अगर (slv_addr + 2 == aux_sens->addr)
		slv_config = ST_LSM6DSX_SHIFT_VAL(3, aux_sens->mask);

	क्रम (i = 0; i < ARRAY_SIZE(settings->i2c_addr); i++) अणु
		अगर (!settings->i2c_addr[i])
			जारी;

		/* पढ़ो wai slave रेजिस्टर */
		config[0] = (settings->i2c_addr[i] << 1) | 0x1;
		config[1] = settings->wai.addr;
		config[2] = 0x1 | slv_config;

		err = st_lsm6dsx_shub_ग_लिखो_reg(hw, slv_addr, config,
						माप(config));
		अगर (err < 0)
			वापस err;

		err = st_lsm6dsx_shub_master_enable(sensor, true);
		अगर (err < 0)
			वापस err;

		st_lsm6dsx_shub_रुको_complete(hw);

		err = st_lsm6dsx_shub_पढ़ो_output(hw, &data, माप(data));

		st_lsm6dsx_shub_master_enable(sensor, false);

		अगर (err < 0)
			वापस err;

		अगर (data != settings->wai.val)
			जारी;

		*i2c_addr = settings->i2c_addr[i];
		found = true;
		अवरोध;
	पूर्ण

	/* reset SLV0 channel */
	config[0] = hub_settings->छोड़ो;
	config[1] = 0;
	config[2] = slv_config;
	err = st_lsm6dsx_shub_ग_लिखो_reg(hw, slv_addr, config,
					माप(config));
	अगर (err < 0)
		वापस err;

	वापस found ? 0 : -ENODEV;
पूर्ण

पूर्णांक st_lsm6dsx_shub_probe(काष्ठा st_lsm6dsx_hw *hw, स्थिर अक्षर *name)
अणु
	क्रमागत st_lsm6dsx_sensor_id id = ST_LSM6DSX_ID_EXT0;
	काष्ठा st_lsm6dsx_sensor *sensor;
	पूर्णांक err, i, num_ext_dev = 0;
	u8 i2c_addr = 0;

	क्रम (i = 0; i < ARRAY_SIZE(st_lsm6dsx_ext_dev_table); i++) अणु
		err = st_lsm6dsx_shub_check_wai(hw, &i2c_addr,
					&st_lsm6dsx_ext_dev_table[i]);
		अगर (err == -ENODEV)
			जारी;
		अन्यथा अगर (err < 0)
			वापस err;

		hw->iio_devs[id] = st_lsm6dsx_shub_alloc_iiodev(hw, id,
						&st_lsm6dsx_ext_dev_table[i],
						i2c_addr, name);
		अगर (!hw->iio_devs[id])
			वापस -ENOMEM;

		sensor = iio_priv(hw->iio_devs[id]);
		err = st_lsm6dsx_shub_init_device(sensor);
		अगर (err < 0)
			वापस err;

		अगर (++num_ext_dev >= hw->settings->shub_settings.num_ext_dev)
			अवरोध;
		id++;
	पूर्ण

	वापस 0;
पूर्ण
