<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * STMicroelectronics st_lsm6dsx sensor driver
 *
 * Copyright 2016 STMicroelectronics Inc.
 *
 * Lorenzo Bianconi <lorenzo.bianconi@st.com>
 * Denis Ciocca <denis.ciocca@st.com>
 */

#अगर_अघोषित ST_LSM6DSX_H
#घोषणा ST_LSM6DSX_H

#समावेश <linux/device.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/regulator/consumer.h>

#घोषणा ST_LSM6DS3_DEV_NAME	"lsm6ds3"
#घोषणा ST_LSM6DS3H_DEV_NAME	"lsm6ds3h"
#घोषणा ST_LSM6DSL_DEV_NAME	"lsm6dsl"
#घोषणा ST_LSM6DSM_DEV_NAME	"lsm6dsm"
#घोषणा ST_ISM330DLC_DEV_NAME	"ism330dlc"
#घोषणा ST_LSM6DSO_DEV_NAME	"lsm6dso"
#घोषणा ST_ASM330LHH_DEV_NAME	"asm330lhh"
#घोषणा ST_LSM6DSOX_DEV_NAME	"lsm6dsox"
#घोषणा ST_LSM6DSR_DEV_NAME	"lsm6dsr"
#घोषणा ST_LSM6DS3TRC_DEV_NAME	"lsm6ds3tr-c"
#घोषणा ST_ISM330DHCX_DEV_NAME	"ism330dhcx"
#घोषणा ST_LSM9DS1_DEV_NAME	"lsm9ds1-imu"
#घोषणा ST_LSM6DS0_DEV_NAME	"lsm6ds0"
#घोषणा ST_LSM6DSRX_DEV_NAME	"lsm6dsrx"
#घोषणा ST_LSM6DST_DEV_NAME	"lsm6dst"
#घोषणा ST_LSM6DSOP_DEV_NAME	"lsm6dsop"

क्रमागत st_lsm6dsx_hw_id अणु
	ST_LSM6DS3_ID,
	ST_LSM6DS3H_ID,
	ST_LSM6DSL_ID,
	ST_LSM6DSM_ID,
	ST_ISM330DLC_ID,
	ST_LSM6DSO_ID,
	ST_ASM330LHH_ID,
	ST_LSM6DSOX_ID,
	ST_LSM6DSR_ID,
	ST_LSM6DS3TRC_ID,
	ST_ISM330DHCX_ID,
	ST_LSM9DS1_ID,
	ST_LSM6DS0_ID,
	ST_LSM6DSRX_ID,
	ST_LSM6DST_ID,
	ST_LSM6DSOP_ID,
	ST_LSM6DSX_MAX_ID,
पूर्ण;

#घोषणा ST_LSM6DSX_BUFF_SIZE		512
#घोषणा ST_LSM6DSX_CHAN_SIZE		2
#घोषणा ST_LSM6DSX_SAMPLE_SIZE		6
#घोषणा ST_LSM6DSX_TAG_SIZE		1
#घोषणा ST_LSM6DSX_TAGGED_SAMPLE_SIZE	(ST_LSM6DSX_SAMPLE_SIZE + \
					 ST_LSM6DSX_TAG_SIZE)
#घोषणा ST_LSM6DSX_MAX_WORD_LEN		((32 / ST_LSM6DSX_SAMPLE_SIZE) * \
					 ST_LSM6DSX_SAMPLE_SIZE)
#घोषणा ST_LSM6DSX_MAX_TAGGED_WORD_LEN	((32 / ST_LSM6DSX_TAGGED_SAMPLE_SIZE) \
					 * ST_LSM6DSX_TAGGED_SAMPLE_SIZE)
#घोषणा ST_LSM6DSX_SHIFT_VAL(val, mask)	(((val) << __ffs(mask)) & (mask))

#घोषणा ST_LSM6DSX_CHANNEL_ACC(chan_type, addr, mod, scan_idx)		\
अणु									\
	.type = chan_type,						\
	.address = addr,						\
	.modअगरied = 1,							\
	.channel2 = mod,						\
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),			\
	.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE),		\
	.info_mask_shared_by_all = BIT(IIO_CHAN_INFO_SAMP_FREQ),	\
	.scan_index = scan_idx,						\
	.scan_type = अणु							\
		.sign = 's',						\
		.realbits = 16,						\
		.storagebits = 16,					\
		.endianness = IIO_LE,					\
	पूर्ण,								\
	.event_spec = &st_lsm6dsx_event,				\
	.ext_info = st_lsm6dsx_accel_ext_info,				\
	.num_event_specs = 1,						\
पूर्ण

#घोषणा ST_LSM6DSX_CHANNEL(chan_type, addr, mod, scan_idx)		\
अणु									\
	.type = chan_type,						\
	.address = addr,						\
	.modअगरied = 1,							\
	.channel2 = mod,						\
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),			\
	.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE),		\
	.info_mask_shared_by_all = BIT(IIO_CHAN_INFO_SAMP_FREQ),	\
	.scan_index = scan_idx,						\
	.scan_type = अणु							\
		.sign = 's',						\
		.realbits = 16,						\
		.storagebits = 16,					\
		.endianness = IIO_LE,					\
	पूर्ण,								\
पूर्ण

काष्ठा st_lsm6dsx_reg अणु
	u8 addr;
	u8 mask;
पूर्ण;

काष्ठा st_lsm6dsx_sensor;
काष्ठा st_lsm6dsx_hw;

काष्ठा st_lsm6dsx_odr अणु
	u32 milli_hz;
	u8 val;
पूर्ण;

#घोषणा ST_LSM6DSX_ODR_LIST_SIZE	8
काष्ठा st_lsm6dsx_odr_table_entry अणु
	काष्ठा st_lsm6dsx_reg reg;

	काष्ठा st_lsm6dsx_odr odr_avl[ST_LSM6DSX_ODR_LIST_SIZE];
	पूर्णांक odr_len;
पूर्ण;

काष्ठा st_lsm6dsx_fs अणु
	u32 gain;
	u8 val;
पूर्ण;

#घोषणा ST_LSM6DSX_FS_LIST_SIZE		4
काष्ठा st_lsm6dsx_fs_table_entry अणु
	काष्ठा st_lsm6dsx_reg reg;

	काष्ठा st_lsm6dsx_fs fs_avl[ST_LSM6DSX_FS_LIST_SIZE];
	पूर्णांक fs_len;
पूर्ण;

/**
 * काष्ठा st_lsm6dsx_fअगरo_ops - ST IMU FIFO settings
 * @update_fअगरo: Update FIFO configuration callback.
 * @पढ़ो_fअगरo: Read FIFO callback.
 * @fअगरo_th: FIFO threshold रेजिस्टर info (addr + mask).
 * @fअगरo_dअगरf: FIFO dअगरf status रेजिस्टर info (addr + mask).
 * @th_wl: FIFO threshold word length.
 */
काष्ठा st_lsm6dsx_fअगरo_ops अणु
	पूर्णांक (*update_fअगरo)(काष्ठा st_lsm6dsx_sensor *sensor, bool enable);
	पूर्णांक (*पढ़ो_fअगरo)(काष्ठा st_lsm6dsx_hw *hw);
	काष्ठा अणु
		u8 addr;
		u16 mask;
	पूर्ण fअगरo_th;
	काष्ठा अणु
		u8 addr;
		u16 mask;
	पूर्ण fअगरo_dअगरf;
	u8 th_wl;
पूर्ण;

/**
 * काष्ठा st_lsm6dsx_hw_ts_settings - ST IMU hw समयr settings
 * @समयr_en: Hw समयr enable रेजिस्टर info (addr + mask).
 * @hr_समयr: Hw समयr resolution रेजिस्टर info (addr + mask).
 * @fअगरo_en: Hw समयr FIFO enable रेजिस्टर info (addr + mask).
 * @decimator: Hw समयr FIFO decimator रेजिस्टर info (addr + mask).
 * @freq_fine: Dअगरference in % of ODR with respect to the typical.
 */
काष्ठा st_lsm6dsx_hw_ts_settings अणु
	काष्ठा st_lsm6dsx_reg समयr_en;
	काष्ठा st_lsm6dsx_reg hr_समयr;
	काष्ठा st_lsm6dsx_reg fअगरo_en;
	काष्ठा st_lsm6dsx_reg decimator;
	u8 freq_fine;
पूर्ण;

/**
 * काष्ठा st_lsm6dsx_shub_settings - ST IMU hw i2c controller settings
 * @page_mux: रेजिस्टर page mux info (addr + mask).
 * @master_en: master config रेजिस्टर info (addr + mask).
 * @pullup_en: i2c controller pull-up रेजिस्टर info (addr + mask).
 * @aux_sens: aux sensor रेजिस्टर info (addr + mask).
 * @wr_once: ग_लिखो_once रेजिस्टर info (addr + mask).
 * @emb_func:  embedded function रेजिस्टर info (addr + mask).
 * @num_ext_dev: max number of slave devices.
 * @shub_out: sensor hub first output रेजिस्टर info.
 * @slv0_addr: slave0 address in secondary page.
 * @dw_slv0_addr: slave0 ग_लिखो रेजिस्टर address in secondary page.
 * @batch_en: Enable/disable FIFO batching.
 * @छोड़ो: controller छोड़ो value.
 */
काष्ठा st_lsm6dsx_shub_settings अणु
	काष्ठा st_lsm6dsx_reg page_mux;
	काष्ठा अणु
		bool sec_page;
		u8 addr;
		u8 mask;
	पूर्ण master_en;
	काष्ठा अणु
		bool sec_page;
		u8 addr;
		u8 mask;
	पूर्ण pullup_en;
	काष्ठा st_lsm6dsx_reg aux_sens;
	काष्ठा st_lsm6dsx_reg wr_once;
	काष्ठा st_lsm6dsx_reg emb_func;
	u8 num_ext_dev;
	काष्ठा अणु
		bool sec_page;
		u8 addr;
	पूर्ण shub_out;
	u8 slv0_addr;
	u8 dw_slv0_addr;
	u8 batch_en;
	u8 छोड़ो;
पूर्ण;

काष्ठा st_lsm6dsx_event_settings अणु
	काष्ठा st_lsm6dsx_reg enable_reg;
	काष्ठा st_lsm6dsx_reg wakeup_reg;
	u8 wakeup_src_reg;
	u8 wakeup_src_status_mask;
	u8 wakeup_src_z_mask;
	u8 wakeup_src_y_mask;
	u8 wakeup_src_x_mask;
पूर्ण;

क्रमागत st_lsm6dsx_ext_sensor_id अणु
	ST_LSM6DSX_ID_MAGN,
पूर्ण;

/**
 * काष्ठा st_lsm6dsx_ext_dev_settings - i2c controller slave settings
 * @i2c_addr: I2c slave address list.
 * @wai: Wai address info.
 * @id: बाह्यal sensor id.
 * @odr_table: Output data rate of the sensor [Hz].
 * @fs_table: Configured sensor sensitivity table depending on full scale.
 * @temp_comp: Temperature compensation रेजिस्टर info (addr + mask).
 * @pwr_table: Power on रेजिस्टर info (addr + mask).
 * @off_canc: Offset cancellation रेजिस्टर info (addr + mask).
 * @bdu: Block data update रेजिस्टर info (addr + mask).
 * @out: Output रेजिस्टर info.
 */
काष्ठा st_lsm6dsx_ext_dev_settings अणु
	u8 i2c_addr[2];
	काष्ठा अणु
		u8 addr;
		u8 val;
	पूर्ण wai;
	क्रमागत st_lsm6dsx_ext_sensor_id id;
	काष्ठा st_lsm6dsx_odr_table_entry odr_table;
	काष्ठा st_lsm6dsx_fs_table_entry fs_table;
	काष्ठा st_lsm6dsx_reg temp_comp;
	काष्ठा अणु
		काष्ठा st_lsm6dsx_reg reg;
		u8 off_val;
		u8 on_val;
	पूर्ण pwr_table;
	काष्ठा st_lsm6dsx_reg off_canc;
	काष्ठा st_lsm6dsx_reg bdu;
	काष्ठा अणु
		u8 addr;
		u8 len;
	पूर्ण out;
पूर्ण;

/**
 * काष्ठा st_lsm6dsx_settings - ST IMU sensor settings
 * @reset: रेजिस्टर address क्रम reset.
 * @boot: रेजिस्टर address क्रम boot.
 * @bdu: रेजिस्टर address क्रम Block Data Update.
 * @max_fअगरo_size: Sensor max fअगरo length in FIFO words.
 * @id: List of hw id/device name supported by the driver configuration.
 * @channels: IIO channels supported by the device.
 * @irq_config: पूर्णांकerrupts related रेजिस्टरs.
 * @drdy_mask: रेजिस्टर info क्रम data-पढ़ोy mask (addr + mask).
 * @odr_table: Hw sensors odr table (Hz + val).
 * @fs_table: Hw sensors gain table (gain + val).
 * @decimator: List of decimator रेजिस्टर info (addr + mask).
 * @batch: List of FIFO batching रेजिस्टर info (addr + mask).
 * @fअगरo_ops: Sensor hw FIFO parameters.
 * @ts_settings: Hw समयr related settings.
 * @shub_settings: i2c controller related settings.
 */
काष्ठा st_lsm6dsx_settings अणु
	काष्ठा st_lsm6dsx_reg reset;
	काष्ठा st_lsm6dsx_reg boot;
	काष्ठा st_lsm6dsx_reg bdu;
	u16 max_fअगरo_size;
	काष्ठा अणु
		क्रमागत st_lsm6dsx_hw_id hw_id;
		स्थिर अक्षर *name;
		u8 wai;
	पूर्ण id[ST_LSM6DSX_MAX_ID];
	काष्ठा अणु
		स्थिर काष्ठा iio_chan_spec *chan;
		पूर्णांक len;
	पूर्ण channels[2];
	काष्ठा अणु
		काष्ठा st_lsm6dsx_reg irq1;
		काष्ठा st_lsm6dsx_reg irq2;
		काष्ठा st_lsm6dsx_reg irq1_func;
		काष्ठा st_lsm6dsx_reg irq2_func;
		काष्ठा st_lsm6dsx_reg lir;
		काष्ठा st_lsm6dsx_reg clear_on_पढ़ो;
		काष्ठा st_lsm6dsx_reg hla;
		काष्ठा st_lsm6dsx_reg od;
	पूर्ण irq_config;
	काष्ठा st_lsm6dsx_reg drdy_mask;
	काष्ठा st_lsm6dsx_odr_table_entry odr_table[2];
	काष्ठा st_lsm6dsx_fs_table_entry fs_table[2];
	काष्ठा st_lsm6dsx_reg decimator[ST_LSM6DSX_MAX_ID];
	काष्ठा st_lsm6dsx_reg batch[ST_LSM6DSX_MAX_ID];
	काष्ठा st_lsm6dsx_fअगरo_ops fअगरo_ops;
	काष्ठा st_lsm6dsx_hw_ts_settings ts_settings;
	काष्ठा st_lsm6dsx_shub_settings shub_settings;
	काष्ठा st_lsm6dsx_event_settings event_settings;
पूर्ण;

क्रमागत st_lsm6dsx_sensor_id अणु
	ST_LSM6DSX_ID_GYRO,
	ST_LSM6DSX_ID_ACC,
	ST_LSM6DSX_ID_EXT0,
	ST_LSM6DSX_ID_EXT1,
	ST_LSM6DSX_ID_EXT2,
	ST_LSM6DSX_ID_MAX,
पूर्ण;

क्रमागत st_lsm6dsx_fअगरo_mode अणु
	ST_LSM6DSX_FIFO_BYPASS = 0x0,
	ST_LSM6DSX_FIFO_CONT = 0x6,
पूर्ण;

/**
 * काष्ठा st_lsm6dsx_sensor - ST IMU sensor instance
 * @name: Sensor name.
 * @id: Sensor identअगरier.
 * @hw: Poपूर्णांकer to instance of काष्ठा st_lsm6dsx_hw.
 * @gain: Configured sensor sensitivity.
 * @odr: Output data rate of the sensor [Hz].
 * @watermark: Sensor watermark level.
 * @decimator: Sensor decimation factor.
 * @sip: Number of samples in a given pattern.
 * @ts_ref: Sensor बारtamp reference क्रम hw one.
 * @ext_info: Sensor settings अगर it is connected to i2c controller
 */
काष्ठा st_lsm6dsx_sensor अणु
	अक्षर name[32];
	क्रमागत st_lsm6dsx_sensor_id id;
	काष्ठा st_lsm6dsx_hw *hw;

	u32 gain;
	u32 odr;

	u16 watermark;
	u8 decimator;
	u8 sip;
	s64 ts_ref;

	काष्ठा अणु
		स्थिर काष्ठा st_lsm6dsx_ext_dev_settings *settings;
		u32 slv_odr;
		u8 addr;
	पूर्ण ext_info;
पूर्ण;

/**
 * काष्ठा st_lsm6dsx_hw - ST IMU MEMS hw instance
 * @dev: Poपूर्णांकer to instance of काष्ठा device (I2C or SPI).
 * @regmap: Register map of the device.
 * @regulators: VDD/VDDIO voltage regulators.
 * @irq: Device पूर्णांकerrupt line (I2C or SPI).
 * @fअगरo_lock: Mutex to prevent concurrent access to the hw FIFO.
 * @conf_lock: Mutex to prevent concurrent FIFO configuration update.
 * @page_lock: Mutex to prevent concurrent memory page configuration.
 * @suspend_mask: Suspended sensor biपंचांगask.
 * @enable_mask: Enabled sensor biपंचांगask.
 * @fअगरo_mask: Enabled hw FIFO biपंचांगask.
 * @ts_gain: Hw बारtamp rate after पूर्णांकernal calibration.
 * @ts_sip: Total number of बारtamp samples in a given pattern.
 * @sip: Total number of samples (acc/gyro/ts) in a given pattern.
 * @buff: Device पढ़ो buffer.
 * @irq_routing: poपूर्णांकer to पूर्णांकerrupt routing configuration.
 * @event_threshold: wakeup event threshold.
 * @enable_event: enabled event biपंचांगask.
 * @iio_devs: Poपूर्णांकers to acc/gyro iio_dev instances.
 * @settings: Poपूर्णांकer to the specअगरic sensor settings in use.
 * @orientation: sensor chip orientation relative to मुख्य hardware.
 * @scan: Temporary buffers used to align data beक्रमe iio_push_to_buffers()
 */
काष्ठा st_lsm6dsx_hw अणु
	काष्ठा device *dev;
	काष्ठा regmap *regmap;
	काष्ठा regulator_bulk_data regulators[2];
	पूर्णांक irq;

	काष्ठा mutex fअगरo_lock;
	काष्ठा mutex conf_lock;
	काष्ठा mutex page_lock;

	u8 suspend_mask;
	u8 enable_mask;
	u8 fअगरo_mask;
	s64 ts_gain;
	u8 ts_sip;
	u8 sip;

	स्थिर काष्ठा st_lsm6dsx_reg *irq_routing;
	u8 event_threshold;
	u8 enable_event;

	u8 *buff;

	काष्ठा iio_dev *iio_devs[ST_LSM6DSX_ID_MAX];

	स्थिर काष्ठा st_lsm6dsx_settings *settings;

	काष्ठा iio_mount_matrix orientation;
	/* Ensure natural alignment of buffer elements */
	काष्ठा अणु
		__le16 channels[3];
		s64 ts __aligned(8);
	पूर्ण scan[3];
पूर्ण;

अटल __maybe_unused स्थिर काष्ठा iio_event_spec st_lsm6dsx_event = अणु
	.type = IIO_EV_TYPE_THRESH,
	.dir = IIO_EV_सूची_EITHER,
	.mask_separate = BIT(IIO_EV_INFO_VALUE) |
			 BIT(IIO_EV_INFO_ENABLE)
पूर्ण;

अटल __maybe_unused स्थिर अचिन्हित दीर्घ st_lsm6dsx_available_scan_masks[] = अणु
	0x7, 0x0,
पूर्ण;

बाह्य स्थिर काष्ठा dev_pm_ops st_lsm6dsx_pm_ops;

पूर्णांक st_lsm6dsx_probe(काष्ठा device *dev, पूर्णांक irq, पूर्णांक hw_id,
		     काष्ठा regmap *regmap);
पूर्णांक st_lsm6dsx_sensor_set_enable(काष्ठा st_lsm6dsx_sensor *sensor,
				 bool enable);
पूर्णांक st_lsm6dsx_fअगरo_setup(काष्ठा st_lsm6dsx_hw *hw);
पूर्णांक st_lsm6dsx_set_watermark(काष्ठा iio_dev *iio_dev, अचिन्हित पूर्णांक val);
पूर्णांक st_lsm6dsx_update_watermark(काष्ठा st_lsm6dsx_sensor *sensor,
				u16 watermark);
पूर्णांक st_lsm6dsx_update_fअगरo(काष्ठा st_lsm6dsx_sensor *sensor, bool enable);
पूर्णांक st_lsm6dsx_flush_fअगरo(काष्ठा st_lsm6dsx_hw *hw);
पूर्णांक st_lsm6dsx_resume_fअगरo(काष्ठा st_lsm6dsx_hw *hw);
पूर्णांक st_lsm6dsx_पढ़ो_fअगरo(काष्ठा st_lsm6dsx_hw *hw);
पूर्णांक st_lsm6dsx_पढ़ो_tagged_fअगरo(काष्ठा st_lsm6dsx_hw *hw);
पूर्णांक st_lsm6dsx_check_odr(काष्ठा st_lsm6dsx_sensor *sensor, u32 odr, u8 *val);
पूर्णांक st_lsm6dsx_shub_probe(काष्ठा st_lsm6dsx_hw *hw, स्थिर अक्षर *name);
पूर्णांक st_lsm6dsx_shub_set_enable(काष्ठा st_lsm6dsx_sensor *sensor, bool enable);
पूर्णांक st_lsm6dsx_set_page(काष्ठा st_lsm6dsx_hw *hw, bool enable);

अटल अंतरभूत पूर्णांक
st_lsm6dsx_update_bits_locked(काष्ठा st_lsm6dsx_hw *hw, अचिन्हित पूर्णांक addr,
			      अचिन्हित पूर्णांक mask, अचिन्हित पूर्णांक val)
अणु
	पूर्णांक err;

	mutex_lock(&hw->page_lock);
	err = regmap_update_bits(hw->regmap, addr, mask, val);
	mutex_unlock(&hw->page_lock);

	वापस err;
पूर्ण

अटल अंतरभूत पूर्णांक
st_lsm6dsx_पढ़ो_locked(काष्ठा st_lsm6dsx_hw *hw, अचिन्हित पूर्णांक addr,
		       व्योम *val, अचिन्हित पूर्णांक len)
अणु
	पूर्णांक err;

	mutex_lock(&hw->page_lock);
	err = regmap_bulk_पढ़ो(hw->regmap, addr, val, len);
	mutex_unlock(&hw->page_lock);

	वापस err;
पूर्ण

अटल अंतरभूत पूर्णांक
st_lsm6dsx_ग_लिखो_locked(काष्ठा st_lsm6dsx_hw *hw, अचिन्हित पूर्णांक addr,
			अचिन्हित पूर्णांक val)
अणु
	पूर्णांक err;

	mutex_lock(&hw->page_lock);
	err = regmap_ग_लिखो(hw->regmap, addr, val);
	mutex_unlock(&hw->page_lock);

	वापस err;
पूर्ण

अटल अंतरभूत स्थिर काष्ठा iio_mount_matrix *
st_lsm6dsx_get_mount_matrix(स्थिर काष्ठा iio_dev *iio_dev,
			    स्थिर काष्ठा iio_chan_spec *chan)
अणु
	काष्ठा st_lsm6dsx_sensor *sensor = iio_priv(iio_dev);
	काष्ठा st_lsm6dsx_hw *hw = sensor->hw;

	वापस &hw->orientation;
पूर्ण

अटल स्थिर
काष्ठा iio_chan_spec_ext_info __maybe_unused st_lsm6dsx_accel_ext_info[] = अणु
	IIO_MOUNT_MATRIX(IIO_SHARED_BY_ALL, st_lsm6dsx_get_mount_matrix),
	अणु पूर्ण
पूर्ण;

#पूर्ण_अगर /* ST_LSM6DSX_H */
