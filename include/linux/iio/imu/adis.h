<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Common library क्रम ADIS16XXX devices
 *
 * Copyright 2012 Analog Devices Inc.
 *   Author: Lars-Peter Clausen <lars@metafoo.de>
 */

#अगर_अघोषित __IIO_ADIS_H__
#घोषणा __IIO_ADIS_H__

#समावेश <linux/spi/spi.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/iio/types.h>

#घोषणा ADIS_WRITE_REG(reg) ((0x80 | (reg)))
#घोषणा ADIS_READ_REG(reg) ((reg) & 0x7f)

#घोषणा ADIS_PAGE_SIZE 0x80
#घोषणा ADIS_REG_PAGE_ID 0x00

काष्ठा adis;

/**
 * काष्ठा adis_समयouts - ADIS chip variant समयouts
 * @reset_ms - Wait समय after rst pin goes inactive
 * @sw_reset_ms - Wait समय after sw reset command
 * @self_test_ms - Wait समय after self test command
 */
काष्ठा adis_समयout अणु
	u16 reset_ms;
	u16 sw_reset_ms;
	u16 self_test_ms;
पूर्ण;
/**
 * काष्ठा adis_data - ADIS chip variant specअगरic data
 * @पढ़ो_delay: SPI delay क्रम पढ़ो operations in us
 * @ग_लिखो_delay: SPI delay क्रम ग_लिखो operations in us
 * @cs_change_delay: SPI delay between CS changes in us
 * @glob_cmd_reg: Register address of the GLOB_CMD रेजिस्टर
 * @msc_ctrl_reg: Register address of the MSC_CTRL रेजिस्टर
 * @diag_stat_reg: Register address of the DIAG_STAT रेजिस्टर
 * @prod_id_reg: Register address of the PROD_ID रेजिस्टर
 * @prod_id: Product ID code that should be expected when पढ़ोing @prod_id_reg
 * @self_test_mask: Biपंचांगask of supported self-test operations
 * @self_test_reg: Register address to request self test command
 * @self_test_no_स्वतःclear: True अगर device's self-test needs clear of ctrl reg
 * @status_error_msgs: Array of error messgaes
 * @status_error_mask: Biपंचांगask of errors supported by the device
 * @समयouts: Chip specअगरic delays
 * @enable_irq: Hook क्रम ADIS devices that have a special IRQ enable/disable
 * @has_paging: True अगर ADIS device has paged रेजिस्टरs
 * @burst_reg_cmd:	Register command that triggers burst
 * @burst_len:		Burst size in the SPI RX buffer. If @burst_max_len is defined,
 *			this should be the minimum size supported by the device.
 * @burst_max_len:	Holds the maximum burst size when the device supports
 *			more than one burst mode with dअगरferent sizes
 */
काष्ठा adis_data अणु
	अचिन्हित पूर्णांक पढ़ो_delay;
	अचिन्हित पूर्णांक ग_लिखो_delay;
	अचिन्हित पूर्णांक cs_change_delay;

	अचिन्हित पूर्णांक glob_cmd_reg;
	अचिन्हित पूर्णांक msc_ctrl_reg;
	अचिन्हित पूर्णांक diag_stat_reg;
	अचिन्हित पूर्णांक prod_id_reg;

	अचिन्हित पूर्णांक prod_id;

	अचिन्हित पूर्णांक self_test_mask;
	अचिन्हित पूर्णांक self_test_reg;
	bool self_test_no_स्वतःclear;
	स्थिर काष्ठा adis_समयout *समयouts;

	स्थिर अक्षर * स्थिर *status_error_msgs;
	अचिन्हित पूर्णांक status_error_mask;

	पूर्णांक (*enable_irq)(काष्ठा adis *adis, bool enable);

	bool has_paging;

	अचिन्हित पूर्णांक burst_reg_cmd;
	अचिन्हित पूर्णांक burst_len;
	अचिन्हित पूर्णांक burst_max_len;
पूर्ण;

/**
 * काष्ठा adis - ADIS device instance data
 * @spi: Reference to SPI device which owns this ADIS IIO device
 * @trig: IIO trigger object data
 * @data: ADIS chip variant specअगरic data
 * @burst: ADIS burst transfer inक्रमmation
 * @burst_extra_len: Burst extra length. Should only be used by devices that can
 *		     dynamically change their burst mode length.
 * @state_lock: Lock used by the device to protect state
 * @msg: SPI message object
 * @xfer: SPI transfer objects to be used क्रम a @msg
 * @current_page: Some ADIS devices have रेजिस्टरs, this selects current page
 * @irq_flag: IRQ handling flags as passed to request_irq()
 * @buffer: Data buffer क्रम inक्रमmation पढ़ो from the device
 * @tx: DMA safe TX buffer क्रम SPI transfers
 * @rx: DMA safe RX buffer क्रम SPI transfers
 */
काष्ठा adis अणु
	काष्ठा spi_device	*spi;
	काष्ठा iio_trigger	*trig;

	स्थिर काष्ठा adis_data	*data;
	अचिन्हित पूर्णांक		burst_extra_len;
	/**
	 * The state_lock is meant to be used during operations that require
	 * a sequence of SPI R/W in order to protect the SPI transfer
	 * inक्रमmation (fields 'xfer', 'msg' & 'current_page') between
	 * potential concurrent accesses.
	 * This lock is used by all "adis_{functions}" that have to पढ़ो/ग_लिखो
	 * रेजिस्टरs. These functions also have unlocked variants
	 * (see "__adis_{functions}"), which करोn't hold this lock.
	 * This allows users of the ADIS library to group SPI R/W पूर्णांकo
	 * the drivers, but they also must manage this lock themselves.
	 */
	काष्ठा mutex		state_lock;
	काष्ठा spi_message	msg;
	काष्ठा spi_transfer	*xfer;
	अचिन्हित पूर्णांक		current_page;
	अचिन्हित दीर्घ		irq_flag;
	व्योम			*buffer;

	uपूर्णांक8_t			tx[10] ____cacheline_aligned;
	uपूर्णांक8_t			rx[4];
पूर्ण;

पूर्णांक adis_init(काष्ठा adis *adis, काष्ठा iio_dev *indio_dev,
	काष्ठा spi_device *spi, स्थिर काष्ठा adis_data *data);
पूर्णांक __adis_reset(काष्ठा adis *adis);

/**
 * adis_reset() - Reset the device
 * @adis: The adis device
 *
 * Returns 0 on success, a negative error code otherwise
 */
अटल अंतरभूत पूर्णांक adis_reset(काष्ठा adis *adis)
अणु
	पूर्णांक ret;

	mutex_lock(&adis->state_lock);
	ret = __adis_reset(adis);
	mutex_unlock(&adis->state_lock);

	वापस ret;
पूर्ण

पूर्णांक __adis_ग_लिखो_reg(काष्ठा adis *adis, अचिन्हित पूर्णांक reg,
	अचिन्हित पूर्णांक val, अचिन्हित पूर्णांक size);
पूर्णांक __adis_पढ़ो_reg(काष्ठा adis *adis, अचिन्हित पूर्णांक reg,
	अचिन्हित पूर्णांक *val, अचिन्हित पूर्णांक size);

/**
 * __adis_ग_लिखो_reg_8() - Write single byte to a रेजिस्टर (unlocked)
 * @adis: The adis device
 * @reg: The address of the रेजिस्टर to be written
 * @value: The value to ग_लिखो
 */
अटल अंतरभूत पूर्णांक __adis_ग_लिखो_reg_8(काष्ठा adis *adis, अचिन्हित पूर्णांक reg,
	uपूर्णांक8_t val)
अणु
	वापस __adis_ग_लिखो_reg(adis, reg, val, 1);
पूर्ण

/**
 * __adis_ग_लिखो_reg_16() - Write 2 bytes to a pair of रेजिस्टरs (unlocked)
 * @adis: The adis device
 * @reg: The address of the lower of the two रेजिस्टरs
 * @value: Value to be written
 */
अटल अंतरभूत पूर्णांक __adis_ग_लिखो_reg_16(काष्ठा adis *adis, अचिन्हित पूर्णांक reg,
	uपूर्णांक16_t val)
अणु
	वापस __adis_ग_लिखो_reg(adis, reg, val, 2);
पूर्ण

/**
 * __adis_ग_लिखो_reg_32() - ग_लिखो 4 bytes to four रेजिस्टरs (unlocked)
 * @adis: The adis device
 * @reg: The address of the lower of the four रेजिस्टर
 * @value: Value to be written
 */
अटल अंतरभूत पूर्णांक __adis_ग_लिखो_reg_32(काष्ठा adis *adis, अचिन्हित पूर्णांक reg,
	uपूर्णांक32_t val)
अणु
	वापस __adis_ग_लिखो_reg(adis, reg, val, 4);
पूर्ण

/**
 * __adis_पढ़ो_reg_16() - पढ़ो 2 bytes from a 16-bit रेजिस्टर (unlocked)
 * @adis: The adis device
 * @reg: The address of the lower of the two रेजिस्टरs
 * @val: The value पढ़ो back from the device
 */
अटल अंतरभूत पूर्णांक __adis_पढ़ो_reg_16(काष्ठा adis *adis, अचिन्हित पूर्णांक reg,
	uपूर्णांक16_t *val)
अणु
	अचिन्हित पूर्णांक पंचांगp;
	पूर्णांक ret;

	ret = __adis_पढ़ो_reg(adis, reg, &पंचांगp, 2);
	अगर (ret == 0)
		*val = पंचांगp;

	वापस ret;
पूर्ण

/**
 * __adis_पढ़ो_reg_32() - पढ़ो 4 bytes from a 32-bit रेजिस्टर (unlocked)
 * @adis: The adis device
 * @reg: The address of the lower of the two रेजिस्टरs
 * @val: The value पढ़ो back from the device
 */
अटल अंतरभूत पूर्णांक __adis_पढ़ो_reg_32(काष्ठा adis *adis, अचिन्हित पूर्णांक reg,
	uपूर्णांक32_t *val)
अणु
	अचिन्हित पूर्णांक पंचांगp;
	पूर्णांक ret;

	ret = __adis_पढ़ो_reg(adis, reg, &पंचांगp, 4);
	अगर (ret == 0)
		*val = पंचांगp;

	वापस ret;
पूर्ण

/**
 * adis_ग_लिखो_reg() - ग_लिखो N bytes to रेजिस्टर
 * @adis: The adis device
 * @reg: The address of the lower of the two रेजिस्टरs
 * @value: The value to ग_लिखो to device (up to 4 bytes)
 * @size: The size of the @value (in bytes)
 */
अटल अंतरभूत पूर्णांक adis_ग_लिखो_reg(काष्ठा adis *adis, अचिन्हित पूर्णांक reg,
	अचिन्हित पूर्णांक val, अचिन्हित पूर्णांक size)
अणु
	पूर्णांक ret;

	mutex_lock(&adis->state_lock);
	ret = __adis_ग_लिखो_reg(adis, reg, val, size);
	mutex_unlock(&adis->state_lock);

	वापस ret;
पूर्ण

/**
 * adis_पढ़ो_reg() - पढ़ो N bytes from रेजिस्टर
 * @adis: The adis device
 * @reg: The address of the lower of the two रेजिस्टरs
 * @val: The value पढ़ो back from the device
 * @size: The size of the @val buffer
 */
अटल पूर्णांक adis_पढ़ो_reg(काष्ठा adis *adis, अचिन्हित पूर्णांक reg,
	अचिन्हित पूर्णांक *val, अचिन्हित पूर्णांक size)
अणु
	पूर्णांक ret;

	mutex_lock(&adis->state_lock);
	ret = __adis_पढ़ो_reg(adis, reg, val, size);
	mutex_unlock(&adis->state_lock);

	वापस ret;
पूर्ण

/**
 * adis_ग_लिखो_reg_8() - Write single byte to a रेजिस्टर
 * @adis: The adis device
 * @reg: The address of the रेजिस्टर to be written
 * @value: The value to ग_लिखो
 */
अटल अंतरभूत पूर्णांक adis_ग_लिखो_reg_8(काष्ठा adis *adis, अचिन्हित पूर्णांक reg,
	uपूर्णांक8_t val)
अणु
	वापस adis_ग_लिखो_reg(adis, reg, val, 1);
पूर्ण

/**
 * adis_ग_लिखो_reg_16() - Write 2 bytes to a pair of रेजिस्टरs
 * @adis: The adis device
 * @reg: The address of the lower of the two रेजिस्टरs
 * @value: Value to be written
 */
अटल अंतरभूत पूर्णांक adis_ग_लिखो_reg_16(काष्ठा adis *adis, अचिन्हित पूर्णांक reg,
	uपूर्णांक16_t val)
अणु
	वापस adis_ग_लिखो_reg(adis, reg, val, 2);
पूर्ण

/**
 * adis_ग_लिखो_reg_32() - ग_लिखो 4 bytes to four रेजिस्टरs
 * @adis: The adis device
 * @reg: The address of the lower of the four रेजिस्टर
 * @value: Value to be written
 */
अटल अंतरभूत पूर्णांक adis_ग_लिखो_reg_32(काष्ठा adis *adis, अचिन्हित पूर्णांक reg,
	uपूर्णांक32_t val)
अणु
	वापस adis_ग_लिखो_reg(adis, reg, val, 4);
पूर्ण

/**
 * adis_पढ़ो_reg_16() - पढ़ो 2 bytes from a 16-bit रेजिस्टर
 * @adis: The adis device
 * @reg: The address of the lower of the two रेजिस्टरs
 * @val: The value पढ़ो back from the device
 */
अटल अंतरभूत पूर्णांक adis_पढ़ो_reg_16(काष्ठा adis *adis, अचिन्हित पूर्णांक reg,
	uपूर्णांक16_t *val)
अणु
	अचिन्हित पूर्णांक पंचांगp;
	पूर्णांक ret;

	ret = adis_पढ़ो_reg(adis, reg, &पंचांगp, 2);
	अगर (ret == 0)
		*val = पंचांगp;

	वापस ret;
पूर्ण

/**
 * adis_पढ़ो_reg_32() - पढ़ो 4 bytes from a 32-bit रेजिस्टर
 * @adis: The adis device
 * @reg: The address of the lower of the two रेजिस्टरs
 * @val: The value पढ़ो back from the device
 */
अटल अंतरभूत पूर्णांक adis_पढ़ो_reg_32(काष्ठा adis *adis, अचिन्हित पूर्णांक reg,
	uपूर्णांक32_t *val)
अणु
	अचिन्हित पूर्णांक पंचांगp;
	पूर्णांक ret;

	ret = adis_पढ़ो_reg(adis, reg, &पंचांगp, 4);
	अगर (ret == 0)
		*val = पंचांगp;

	वापस ret;
पूर्ण

पूर्णांक __adis_update_bits_base(काष्ठा adis *adis, अचिन्हित पूर्णांक reg, स्थिर u32 mask,
			    स्थिर u32 val, u8 size);
/**
 * adis_update_bits_base() - ADIS Update bits function - Locked version
 * @adis: The adis device
 * @reg: The address of the lower of the two रेजिस्टरs
 * @mask: Biपंचांगask to change
 * @val: Value to be written
 * @size: Size of the रेजिस्टर to update
 *
 * Updates the desired bits of @reg in accordance with @mask and @val.
 */
अटल अंतरभूत पूर्णांक adis_update_bits_base(काष्ठा adis *adis, अचिन्हित पूर्णांक reg,
					स्थिर u32 mask, स्थिर u32 val, u8 size)
अणु
	पूर्णांक ret;

	mutex_lock(&adis->state_lock);
	ret = __adis_update_bits_base(adis, reg, mask, val, size);
	mutex_unlock(&adis->state_lock);
	वापस ret;
पूर्ण

/**
 * adis_update_bits() - Wrapper macro क्रम adis_update_bits_base - Locked version
 * @adis: The adis device
 * @reg: The address of the lower of the two रेजिस्टरs
 * @mask: Biपंचांगask to change
 * @val: Value to be written
 *
 * This macro evaluates the माप of @val at compile समय and calls
 * adis_update_bits_base() accordingly. Be aware that using MACROS/DEFINES क्रम
 * @val can lead to undesired behavior अगर the रेजिस्टर to update is 16bit.
 */
#घोषणा adis_update_bits(adis, reg, mask, val) (अणु			\
	BUILD_BUG_ON(माप(val) == 1 || माप(val) == 8);		\
	__builtin_choose_expr(माप(val) == 4,				\
		adis_update_bits_base(adis, reg, mask, val, 4),         \
		adis_update_bits_base(adis, reg, mask, val, 2));	\
पूर्ण)

/**
 * adis_update_bits() - Wrapper macro क्रम adis_update_bits_base
 * @adis: The adis device
 * @reg: The address of the lower of the two रेजिस्टरs
 * @mask: Biपंचांगask to change
 * @val: Value to be written
 *
 * This macro evaluates the माप of @val at compile समय and calls
 * adis_update_bits_base() accordingly. Be aware that using MACROS/DEFINES क्रम
 * @val can lead to undesired behavior अगर the रेजिस्टर to update is 16bit.
 */
#घोषणा __adis_update_bits(adis, reg, mask, val) (अणु			\
	BUILD_BUG_ON(माप(val) == 1 || माप(val) == 8);		\
	__builtin_choose_expr(माप(val) == 4,				\
		__adis_update_bits_base(adis, reg, mask, val, 4),	\
		__adis_update_bits_base(adis, reg, mask, val, 2));	\
पूर्ण)

पूर्णांक adis_enable_irq(काष्ठा adis *adis, bool enable);
पूर्णांक __adis_check_status(काष्ठा adis *adis);
पूर्णांक __adis_initial_startup(काष्ठा adis *adis);

अटल अंतरभूत पूर्णांक adis_check_status(काष्ठा adis *adis)
अणु
	पूर्णांक ret;

	mutex_lock(&adis->state_lock);
	ret = __adis_check_status(adis);
	mutex_unlock(&adis->state_lock);

	वापस ret;
पूर्ण

/* locked version of __adis_initial_startup() */
अटल अंतरभूत पूर्णांक adis_initial_startup(काष्ठा adis *adis)
अणु
	पूर्णांक ret;

	mutex_lock(&adis->state_lock);
	ret = __adis_initial_startup(adis);
	mutex_unlock(&adis->state_lock);

	वापस ret;
पूर्ण

अटल अंतरभूत व्योम adis_dev_lock(काष्ठा adis *adis)
अणु
	mutex_lock(&adis->state_lock);
पूर्ण

अटल अंतरभूत व्योम adis_dev_unlock(काष्ठा adis *adis)
अणु
	mutex_unlock(&adis->state_lock);
पूर्ण

पूर्णांक adis_single_conversion(काष्ठा iio_dev *indio_dev,
	स्थिर काष्ठा iio_chan_spec *chan, अचिन्हित पूर्णांक error_mask,
	पूर्णांक *val);

#घोषणा ADIS_VOLTAGE_CHAN(addr, si, chan, name, info_all, bits) अणु \
	.type = IIO_VOLTAGE, \
	.indexed = 1, \
	.channel = (chan), \
	.extend_name = name, \
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) | \
		BIT(IIO_CHAN_INFO_SCALE), \
	.info_mask_shared_by_all = info_all, \
	.address = (addr), \
	.scan_index = (si), \
	.scan_type = अणु \
		.sign = 'u', \
		.realbits = (bits), \
		.storagebits = 16, \
		.endianness = IIO_BE, \
	पूर्ण, \
पूर्ण

#घोषणा ADIS_SUPPLY_CHAN(addr, si, info_all, bits) \
	ADIS_VOLTAGE_CHAN(addr, si, 0, "supply", info_all, bits)

#घोषणा ADIS_AUX_ADC_CHAN(addr, si, info_all, bits) \
	ADIS_VOLTAGE_CHAN(addr, si, 1, शून्य, info_all, bits)

#घोषणा ADIS_TEMP_CHAN(addr, si, info_all, bits) अणु \
	.type = IIO_TEMP, \
	.indexed = 1, \
	.channel = 0, \
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) | \
		BIT(IIO_CHAN_INFO_SCALE) | \
		BIT(IIO_CHAN_INFO_OFFSET), \
	.info_mask_shared_by_all = info_all, \
	.address = (addr), \
	.scan_index = (si), \
	.scan_type = अणु \
		.sign = 'u', \
		.realbits = (bits), \
		.storagebits = 16, \
		.endianness = IIO_BE, \
	पूर्ण, \
पूर्ण

#घोषणा ADIS_MOD_CHAN(_type, mod, addr, si, info_sep, info_all, bits) अणु \
	.type = (_type), \
	.modअगरied = 1, \
	.channel2 = IIO_MOD_ ## mod, \
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) | \
		 info_sep, \
	.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE), \
	.info_mask_shared_by_all = info_all, \
	.address = (addr), \
	.scan_index = (si), \
	.scan_type = अणु \
		.sign = 's', \
		.realbits = (bits), \
		.storagebits = 16, \
		.endianness = IIO_BE, \
	पूर्ण, \
पूर्ण

#घोषणा ADIS_ACCEL_CHAN(mod, addr, si, info_sep, info_all, bits) \
	ADIS_MOD_CHAN(IIO_ACCEL, mod, addr, si, info_sep, info_all, bits)

#घोषणा ADIS_GYRO_CHAN(mod, addr, si, info_sep, info_all, bits)		\
	ADIS_MOD_CHAN(IIO_ANGL_VEL, mod, addr, si, info_sep, info_all, bits)

#घोषणा ADIS_INCLI_CHAN(mod, addr, si, info_sep, info_all, bits) \
	ADIS_MOD_CHAN(IIO_INCLI, mod, addr, si, info_sep, info_all, bits)

#घोषणा ADIS_ROT_CHAN(mod, addr, si, info_sep, info_all, bits) \
	ADIS_MOD_CHAN(IIO_ROT, mod, addr, si, info_sep, info_all, bits)

#अगर_घोषित CONFIG_IIO_ADIS_LIB_BUFFER

पूर्णांक
devm_adis_setup_buffer_and_trigger(काष्ठा adis *adis, काष्ठा iio_dev *indio_dev,
				   irq_handler_t trigger_handler);

पूर्णांक devm_adis_probe_trigger(काष्ठा adis *adis, काष्ठा iio_dev *indio_dev);

पूर्णांक adis_update_scan_mode(काष्ठा iio_dev *indio_dev,
	स्थिर अचिन्हित दीर्घ *scan_mask);

#अन्यथा /* CONFIG_IIO_BUFFER */

अटल अंतरभूत पूर्णांक
devm_adis_setup_buffer_and_trigger(काष्ठा adis *adis, काष्ठा iio_dev *indio_dev,
				   irq_handler_t trigger_handler)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक devm_adis_probe_trigger(काष्ठा adis *adis,
					  काष्ठा iio_dev *indio_dev)
अणु
	वापस 0;
पूर्ण

#घोषणा adis_update_scan_mode शून्य

#पूर्ण_अगर /* CONFIG_IIO_BUFFER */

#अगर_घोषित CONFIG_DEBUG_FS

पूर्णांक adis_debugfs_reg_access(काष्ठा iio_dev *indio_dev,
	अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक ग_लिखोval, अचिन्हित पूर्णांक *पढ़ोval);

#अन्यथा

#घोषणा adis_debugfs_reg_access शून्य

#पूर्ण_अगर

#पूर्ण_अगर
