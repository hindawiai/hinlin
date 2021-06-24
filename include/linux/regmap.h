<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
#अगर_अघोषित __LINUX_REGMAP_H
#घोषणा __LINUX_REGMAP_H

/*
 * Register map access API
 *
 * Copyright 2011 Wolfson Microelectronics plc
 *
 * Author: Mark Brown <broonie@खोलोsource.wolfsonmicro.com>
 */

#समावेश <linux/list.h>
#समावेश <linux/rbtree.h>
#समावेश <linux/kसमय.स>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/bug.h>
#समावेश <linux/lockdep.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/fwnode.h>

काष्ठा module;
काष्ठा clk;
काष्ठा device;
काष्ठा device_node;
काष्ठा i2c_client;
काष्ठा i3c_device;
काष्ठा irq_करोमुख्य;
काष्ठा slim_device;
काष्ठा spi_device;
काष्ठा spmi_device;
काष्ठा regmap;
काष्ठा regmap_range_cfg;
काष्ठा regmap_field;
काष्ठा snd_ac97;
काष्ठा sdw_slave;

/* An क्रमागत of all the supported cache types */
क्रमागत regcache_type अणु
	REGCACHE_NONE,
	REGCACHE_RBTREE,
	REGCACHE_COMPRESSED,
	REGCACHE_FLAT,
पूर्ण;

/**
 * काष्ठा reg_शेष - Default value क्रम a रेजिस्टर.
 *
 * @reg: Register address.
 * @def: Register शेष value.
 *
 * We use an array of काष्ठाs rather than a simple array as many modern devices
 * have very sparse रेजिस्टर maps.
 */
काष्ठा reg_शेष अणु
	अचिन्हित पूर्णांक reg;
	अचिन्हित पूर्णांक def;
पूर्ण;

/**
 * काष्ठा reg_sequence - An inभागidual ग_लिखो from a sequence of ग_लिखोs.
 *
 * @reg: Register address.
 * @def: Register value.
 * @delay_us: Delay to be applied after the रेजिस्टर ग_लिखो in microseconds
 *
 * Register/value pairs क्रम sequences of ग_लिखोs with an optional delay in
 * microseconds to be applied after each ग_लिखो.
 */
काष्ठा reg_sequence अणु
	अचिन्हित पूर्णांक reg;
	अचिन्हित पूर्णांक def;
	अचिन्हित पूर्णांक delay_us;
पूर्ण;

#घोषणा REG_SEQ(_reg, _def, _delay_us) अणु		\
				.reg = _reg,		\
				.def = _def,		\
				.delay_us = _delay_us,	\
				पूर्ण
#घोषणा REG_SEQ0(_reg, _def)	REG_SEQ(_reg, _def, 0)

/**
 * regmap_पढ़ो_poll_समयout - Poll until a condition is met or a समयout occurs
 *
 * @map: Regmap to पढ़ो from
 * @addr: Address to poll
 * @val: Unचिन्हित पूर्णांकeger variable to पढ़ो the value पूर्णांकo
 * @cond: Break condition (usually involving @val)
 * @sleep_us: Maximum समय to sleep between पढ़ोs in us (0
 *            tight-loops).  Should be less than ~20ms since usleep_range
 *            is used (see Documentation/समयrs/समयrs-howto.rst).
 * @समयout_us: Timeout in us, 0 means never समयout
 *
 * Returns 0 on success and -ETIMEDOUT upon a समयout or the regmap_पढ़ो
 * error वापस value in हाल of a error पढ़ो. In the two क्रमmer हालs,
 * the last पढ़ो value at @addr is stored in @val. Must not be called
 * from atomic context अगर sleep_us or समयout_us are used.
 *
 * This is modelled after the पढ़ोx_poll_समयout macros in linux/iopoll.h.
 */
#घोषणा regmap_पढ़ो_poll_समयout(map, addr, val, cond, sleep_us, समयout_us) \
(अणु \
	पूर्णांक __ret, __पंचांगp; \
	__पंचांगp = पढ़ो_poll_समयout(regmap_पढ़ो, __ret, __ret || (cond), \
			sleep_us, समयout_us, false, (map), (addr), &(val)); \
	__ret ?: __पंचांगp; \
पूर्ण)

/**
 * regmap_पढ़ो_poll_समयout_atomic - Poll until a condition is met or a समयout occurs
 *
 * @map: Regmap to पढ़ो from
 * @addr: Address to poll
 * @val: Unचिन्हित पूर्णांकeger variable to पढ़ो the value पूर्णांकo
 * @cond: Break condition (usually involving @val)
 * @delay_us: Time to udelay between पढ़ोs in us (0 tight-loops).
 *            Should be less than ~10us since udelay is used
 *            (see Documentation/समयrs/समयrs-howto.rst).
 * @समयout_us: Timeout in us, 0 means never समयout
 *
 * Returns 0 on success and -ETIMEDOUT upon a समयout or the regmap_पढ़ो
 * error वापस value in हाल of a error पढ़ो. In the two क्रमmer हालs,
 * the last पढ़ो value at @addr is stored in @val.
 *
 * This is modelled after the पढ़ोx_poll_समयout_atomic macros in linux/iopoll.h.
 *
 * Note: In general regmap cannot be used in atomic context. If you want to use
 * this macro then first setup your regmap क्रम atomic use (flat or no cache
 * and MMIO regmap).
 */
#घोषणा regmap_पढ़ो_poll_समयout_atomic(map, addr, val, cond, delay_us, समयout_us) \
(अणु \
	u64 __समयout_us = (समयout_us); \
	अचिन्हित दीर्घ __delay_us = (delay_us); \
	kसमय_प्रकार __समयout = kसमय_add_us(kसमय_get(), __समयout_us); \
	पूर्णांक __ret; \
	क्रम (;;) अणु \
		__ret = regmap_पढ़ो((map), (addr), &(val)); \
		अगर (__ret) \
			अवरोध; \
		अगर (cond) \
			अवरोध; \
		अगर ((__समयout_us) && \
		    kसमय_compare(kसमय_get(), __समयout) > 0) अणु \
			__ret = regmap_पढ़ो((map), (addr), &(val)); \
			अवरोध; \
		पूर्ण \
		अगर (__delay_us) \
			udelay(__delay_us); \
	पूर्ण \
	__ret ?: ((cond) ? 0 : -ETIMEDOUT); \
पूर्ण)

/**
 * regmap_field_पढ़ो_poll_समयout - Poll until a condition is met or समयout
 *
 * @field: Regmap field to पढ़ो from
 * @val: Unचिन्हित पूर्णांकeger variable to पढ़ो the value पूर्णांकo
 * @cond: Break condition (usually involving @val)
 * @sleep_us: Maximum समय to sleep between पढ़ोs in us (0
 *            tight-loops).  Should be less than ~20ms since usleep_range
 *            is used (see Documentation/समयrs/समयrs-howto.rst).
 * @समयout_us: Timeout in us, 0 means never समयout
 *
 * Returns 0 on success and -ETIMEDOUT upon a समयout or the regmap_field_पढ़ो
 * error वापस value in हाल of a error पढ़ो. In the two क्रमmer हालs,
 * the last पढ़ो value at @addr is stored in @val. Must not be called
 * from atomic context अगर sleep_us or समयout_us are used.
 *
 * This is modelled after the पढ़ोx_poll_समयout macros in linux/iopoll.h.
 */
#घोषणा regmap_field_पढ़ो_poll_समयout(field, val, cond, sleep_us, समयout_us) \
(अणु \
	पूर्णांक __ret, __पंचांगp; \
	__पंचांगp = पढ़ो_poll_समयout(regmap_field_पढ़ो, __ret, __ret || (cond), \
			sleep_us, समयout_us, false, (field), &(val)); \
	__ret ?: __पंचांगp; \
पूर्ण)

#अगर_घोषित CONFIG_REGMAP

क्रमागत regmap_endian अणु
	/* Unspecअगरied -> 0 -> Backwards compatible शेष */
	REGMAP_ENDIAN_DEFAULT = 0,
	REGMAP_ENDIAN_BIG,
	REGMAP_ENDIAN_LITTLE,
	REGMAP_ENDIAN_NATIVE,
पूर्ण;

/**
 * काष्ठा regmap_range - A रेजिस्टर range, used क्रम access related checks
 *                       (पढ़ोable/ग_लिखोable/अस्थिर/precious checks)
 *
 * @range_min: address of first रेजिस्टर
 * @range_max: address of last रेजिस्टर
 */
काष्ठा regmap_range अणु
	अचिन्हित पूर्णांक range_min;
	अचिन्हित पूर्णांक range_max;
पूर्ण;

#घोषणा regmap_reg_range(low, high) अणु .range_min = low, .range_max = high, पूर्ण

/**
 * काष्ठा regmap_access_table - A table of रेजिस्टर ranges क्रम access checks
 *
 * @yes_ranges : poपूर्णांकer to an array of regmap ranges used as "yes ranges"
 * @n_yes_ranges: size of the above array
 * @no_ranges: poपूर्णांकer to an array of regmap ranges used as "no ranges"
 * @n_no_ranges: size of the above array
 *
 * A table of ranges including some yes ranges and some no ranges.
 * If a रेजिस्टर beदीर्घs to a no_range, the corresponding check function
 * will वापस false. If a रेजिस्टर beदीर्घs to a yes range, the corresponding
 * check function will वापस true. "no_ranges" are searched first.
 */
काष्ठा regmap_access_table अणु
	स्थिर काष्ठा regmap_range *yes_ranges;
	अचिन्हित पूर्णांक n_yes_ranges;
	स्थिर काष्ठा regmap_range *no_ranges;
	अचिन्हित पूर्णांक n_no_ranges;
पूर्ण;

प्रकार व्योम (*regmap_lock)(व्योम *);
प्रकार व्योम (*regmap_unlock)(व्योम *);

/**
 * काष्ठा regmap_config - Configuration क्रम the रेजिस्टर map of a device.
 *
 * @name: Optional name of the regmap. Useful when a device has multiple
 *        रेजिस्टर regions.
 *
 * @reg_bits: Number of bits in a रेजिस्टर address, mandatory.
 * @reg_stride: The रेजिस्टर address stride. Valid रेजिस्टर addresses are a
 *              multiple of this value. If set to 0, a value of 1 will be
 *              used.
 * @pad_bits: Number of bits of padding between रेजिस्टर and value.
 * @val_bits: Number of bits in a रेजिस्टर value, mandatory.
 *
 * @ग_लिखोable_reg: Optional callback वापसing true अगर the रेजिस्टर
 *		   can be written to. If this field is शून्य but wr_table
 *		   (see below) is not, the check is perक्रमmed on such table
 *                 (a रेजिस्टर is ग_लिखोable अगर it beदीर्घs to one of the ranges
 *                  specअगरied by wr_table).
 * @पढ़ोable_reg: Optional callback वापसing true अगर the रेजिस्टर
 *		  can be पढ़ो from. If this field is शून्य but rd_table
 *		   (see below) is not, the check is perक्रमmed on such table
 *                 (a रेजिस्टर is पढ़ोable अगर it beदीर्घs to one of the ranges
 *                  specअगरied by rd_table).
 * @अस्थिर_reg: Optional callback वापसing true अगर the रेजिस्टर
 *		  value can't be cached. If this field is शून्य but
 *		  अस्थिर_table (see below) is not, the check is perक्रमmed on
 *                such table (a रेजिस्टर is अस्थिर अगर it beदीर्घs to one of
 *                the ranges specअगरied by अस्थिर_table).
 * @precious_reg: Optional callback वापसing true अगर the रेजिस्टर
 *		  should not be पढ़ो outside of a call from the driver
 *		  (e.g., a clear on पढ़ो पूर्णांकerrupt status रेजिस्टर). If this
 *                field is शून्य but precious_table (see below) is not, the
 *                check is perक्रमmed on such table (a रेजिस्टर is precious अगर
 *                it beदीर्घs to one of the ranges specअगरied by precious_table).
 * @ग_लिखोable_noinc_reg: Optional callback वापसing true अगर the रेजिस्टर
 *			supports multiple ग_लिखो operations without incrementing
 *			the रेजिस्टर number. If this field is शून्य but
 *			wr_noinc_table (see below) is not, the check is
 *			perक्रमmed on such table (a रेजिस्टर is no increment
 *			ग_लिखोable अगर it beदीर्घs to one of the ranges specअगरied
 *			by wr_noinc_table).
 * @पढ़ोable_noinc_reg: Optional callback वापसing true अगर the रेजिस्टर
 *			supports multiple पढ़ो operations without incrementing
 *			the रेजिस्टर number. If this field is शून्य but
 *			rd_noinc_table (see below) is not, the check is
 *			perक्रमmed on such table (a रेजिस्टर is no increment
 *			पढ़ोable अगर it beदीर्घs to one of the ranges specअगरied
 *			by rd_noinc_table).
 * @disable_locking: This regmap is either रक्षित by बाह्यal means or
 *                   is guaranteed not to be accessed from multiple thपढ़ोs.
 *                   Don't use any locking mechanisms.
 * @lock:	  Optional lock callback (overrides regmap's शेष lock
 *		  function, based on spinlock or mutex).
 * @unlock:	  As above क्रम unlocking.
 * @lock_arg:	  this field is passed as the only argument of lock/unlock
 *		  functions (ignored in हाल regular lock/unlock functions
 *		  are not overridden).
 * @reg_पढ़ो:	  Optional callback that अगर filled will be used to perक्रमm
 *           	  all the पढ़ोs from the रेजिस्टरs. Should only be provided क्रम
 *		  devices whose पढ़ो operation cannot be represented as a simple
 *		  पढ़ो operation on a bus such as SPI, I2C, etc. Most of the
 *		  devices करो not need this.
 * @reg_ग_लिखो:	  Same as above क्रम writing.
 * @fast_io:	  Register IO is fast. Use a spinlock instead of a mutex
 *	     	  to perक्रमm locking. This field is ignored अगर custom lock/unlock
 *	     	  functions are used (see fields lock/unlock of काष्ठा regmap_config).
 *		  This field is a duplicate of a similar file in
 *		  'struct regmap_bus' and serves exact same purpose.
 *		   Use it only क्रम "no-bus" हालs.
 * @max_रेजिस्टर: Optional, specअगरies the maximum valid रेजिस्टर address.
 * @wr_table:     Optional, poपूर्णांकs to a काष्ठा regmap_access_table specअगरying
 *                valid ranges क्रम ग_लिखो access.
 * @rd_table:     As above, क्रम पढ़ो access.
 * @अस्थिर_table: As above, क्रम अस्थिर रेजिस्टरs.
 * @precious_table: As above, क्रम precious रेजिस्टरs.
 * @wr_noinc_table: As above, क्रम no increment ग_लिखोable रेजिस्टरs.
 * @rd_noinc_table: As above, क्रम no increment पढ़ोable रेजिस्टरs.
 * @reg_शेषs: Power on reset values क्रम रेजिस्टरs (क्रम use with
 *                रेजिस्टर cache support).
 * @num_reg_शेषs: Number of elements in reg_शेषs.
 *
 * @पढ़ो_flag_mask: Mask to be set in the top bytes of the रेजिस्टर when करोing
 *                  a पढ़ो.
 * @ग_लिखो_flag_mask: Mask to be set in the top bytes of the रेजिस्टर when करोing
 *                   a ग_लिखो. If both पढ़ो_flag_mask and ग_लिखो_flag_mask are
 *                   empty and zero_flag_mask is not set the regmap_bus शेष
 *                   masks are used.
 * @zero_flag_mask: If set, पढ़ो_flag_mask and ग_लिखो_flag_mask are used even
 *                   अगर they are both empty.
 * @use_relaxed_mmio: If set, MMIO R/W operations will not use memory barriers.
 *                    This can aव्योम load on devices which करोn't require strict
 *                    orderings, but drivers should carefully add any explicit
 *                    memory barriers when they may require them.
 * @use_single_पढ़ो: If set, converts the bulk पढ़ो operation पूर्णांकo a series of
 *                   single पढ़ो operations. This is useful क्रम a device that
 *                   करोes not support  bulk पढ़ो.
 * @use_single_ग_लिखो: If set, converts the bulk ग_लिखो operation पूर्णांकo a series of
 *                    single ग_लिखो operations. This is useful क्रम a device that
 *                    करोes not support bulk ग_लिखो.
 * @can_multi_ग_लिखो: If set, the device supports the multi ग_लिखो mode of bulk
 *                   ग_लिखो operations, अगर clear multi ग_लिखो requests will be
 *                   split पूर्णांकo inभागidual ग_लिखो operations
 *
 * @cache_type: The actual cache type.
 * @reg_शेषs_raw: Power on reset values क्रम रेजिस्टरs (क्रम use with
 *                    रेजिस्टर cache support).
 * @num_reg_शेषs_raw: Number of elements in reg_शेषs_raw.
 * @reg_क्रमmat_endian: Endianness क्रम क्रमmatted रेजिस्टर addresses. If this is
 *                     DEFAULT, the @reg_क्रमmat_endian_शेष value from the
 *                     regmap bus is used.
 * @val_क्रमmat_endian: Endianness क्रम क्रमmatted रेजिस्टर values. If this is
 *                     DEFAULT, the @reg_क्रमmat_endian_शेष value from the
 *                     regmap bus is used.
 *
 * @ranges: Array of configuration entries क्रम भव address ranges.
 * @num_ranges: Number of range configuration entries.
 * @use_hwlock: Indicate अगर a hardware spinlock should be used.
 * @hwlock_id: Specअगरy the hardware spinlock id.
 * @hwlock_mode: The hardware spinlock mode, should be HWLOCK_IRQSTATE,
 *		 HWLOCK_IRQ or 0.
 * @can_sleep: Optional, specअगरies whether regmap operations can sleep.
 */
काष्ठा regmap_config अणु
	स्थिर अक्षर *name;

	पूर्णांक reg_bits;
	पूर्णांक reg_stride;
	पूर्णांक pad_bits;
	पूर्णांक val_bits;

	bool (*ग_लिखोable_reg)(काष्ठा device *dev, अचिन्हित पूर्णांक reg);
	bool (*पढ़ोable_reg)(काष्ठा device *dev, अचिन्हित पूर्णांक reg);
	bool (*अस्थिर_reg)(काष्ठा device *dev, अचिन्हित पूर्णांक reg);
	bool (*precious_reg)(काष्ठा device *dev, अचिन्हित पूर्णांक reg);
	bool (*ग_लिखोable_noinc_reg)(काष्ठा device *dev, अचिन्हित पूर्णांक reg);
	bool (*पढ़ोable_noinc_reg)(काष्ठा device *dev, अचिन्हित पूर्णांक reg);

	bool disable_locking;
	regmap_lock lock;
	regmap_unlock unlock;
	व्योम *lock_arg;

	पूर्णांक (*reg_पढ़ो)(व्योम *context, अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक *val);
	पूर्णांक (*reg_ग_लिखो)(व्योम *context, अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक val);

	bool fast_io;

	अचिन्हित पूर्णांक max_रेजिस्टर;
	स्थिर काष्ठा regmap_access_table *wr_table;
	स्थिर काष्ठा regmap_access_table *rd_table;
	स्थिर काष्ठा regmap_access_table *अस्थिर_table;
	स्थिर काष्ठा regmap_access_table *precious_table;
	स्थिर काष्ठा regmap_access_table *wr_noinc_table;
	स्थिर काष्ठा regmap_access_table *rd_noinc_table;
	स्थिर काष्ठा reg_शेष *reg_शेषs;
	अचिन्हित पूर्णांक num_reg_शेषs;
	क्रमागत regcache_type cache_type;
	स्थिर व्योम *reg_शेषs_raw;
	अचिन्हित पूर्णांक num_reg_शेषs_raw;

	अचिन्हित दीर्घ पढ़ो_flag_mask;
	अचिन्हित दीर्घ ग_लिखो_flag_mask;
	bool zero_flag_mask;

	bool use_single_पढ़ो;
	bool use_single_ग_लिखो;
	bool use_relaxed_mmio;
	bool can_multi_ग_लिखो;

	क्रमागत regmap_endian reg_क्रमmat_endian;
	क्रमागत regmap_endian val_क्रमmat_endian;

	स्थिर काष्ठा regmap_range_cfg *ranges;
	अचिन्हित पूर्णांक num_ranges;

	bool use_hwlock;
	अचिन्हित पूर्णांक hwlock_id;
	अचिन्हित पूर्णांक hwlock_mode;

	bool can_sleep;
पूर्ण;

/**
 * काष्ठा regmap_range_cfg - Configuration क्रम indirectly accessed or paged
 *                           रेजिस्टरs.
 *
 * @name: Descriptive name क्रम diagnostics
 *
 * @range_min: Address of the lowest रेजिस्टर address in भव range.
 * @range_max: Address of the highest रेजिस्टर in भव range.
 *
 * @selector_reg: Register with selector field.
 * @selector_mask: Bit mask क्रम selector value.
 * @selector_shअगरt: Bit shअगरt क्रम selector value.
 *
 * @winकरोw_start: Address of first (lowest) रेजिस्टर in data winकरोw.
 * @winकरोw_len: Number of रेजिस्टरs in data winकरोw.
 *
 * Registers, mapped to this भव range, are accessed in two steps:
 *     1. page selector रेजिस्टर update;
 *     2. access through data winकरोw रेजिस्टरs.
 */
काष्ठा regmap_range_cfg अणु
	स्थिर अक्षर *name;

	/* Registers of भव address range */
	अचिन्हित पूर्णांक range_min;
	अचिन्हित पूर्णांक range_max;

	/* Page selector क्रम indirect addressing */
	अचिन्हित पूर्णांक selector_reg;
	अचिन्हित पूर्णांक selector_mask;
	पूर्णांक selector_shअगरt;

	/* Data winकरोw (per each page) */
	अचिन्हित पूर्णांक winकरोw_start;
	अचिन्हित पूर्णांक winकरोw_len;
पूर्ण;

काष्ठा regmap_async;

प्रकार पूर्णांक (*regmap_hw_ग_लिखो)(व्योम *context, स्थिर व्योम *data,
			       माप_प्रकार count);
प्रकार पूर्णांक (*regmap_hw_gather_ग_लिखो)(व्योम *context,
				      स्थिर व्योम *reg, माप_प्रकार reg_len,
				      स्थिर व्योम *val, माप_प्रकार val_len);
प्रकार पूर्णांक (*regmap_hw_async_ग_लिखो)(व्योम *context,
				     स्थिर व्योम *reg, माप_प्रकार reg_len,
				     स्थिर व्योम *val, माप_प्रकार val_len,
				     काष्ठा regmap_async *async);
प्रकार पूर्णांक (*regmap_hw_पढ़ो)(व्योम *context,
			      स्थिर व्योम *reg_buf, माप_प्रकार reg_size,
			      व्योम *val_buf, माप_प्रकार val_size);
प्रकार पूर्णांक (*regmap_hw_reg_पढ़ो)(व्योम *context, अचिन्हित पूर्णांक reg,
				  अचिन्हित पूर्णांक *val);
प्रकार पूर्णांक (*regmap_hw_reg_ग_लिखो)(व्योम *context, अचिन्हित पूर्णांक reg,
				   अचिन्हित पूर्णांक val);
प्रकार पूर्णांक (*regmap_hw_reg_update_bits)(व्योम *context, अचिन्हित पूर्णांक reg,
					 अचिन्हित पूर्णांक mask, अचिन्हित पूर्णांक val);
प्रकार काष्ठा regmap_async *(*regmap_hw_async_alloc)(व्योम);
प्रकार व्योम (*regmap_hw_मुक्त_context)(व्योम *context);

/**
 * काष्ठा regmap_bus - Description of a hardware bus क्रम the रेजिस्टर map
 *                     infraकाष्ठाure.
 *
 * @fast_io: Register IO is fast. Use a spinlock instead of a mutex
 *	     to perक्रमm locking. This field is ignored अगर custom lock/unlock
 *	     functions are used (see fields lock/unlock of
 *	     काष्ठा regmap_config).
 * @ग_लिखो: Write operation.
 * @gather_ग_लिखो: Write operation with split रेजिस्टर/value, वापस -ENOTSUPP
 *                अगर not implemented  on a given device.
 * @async_ग_लिखो: Write operation which completes asynchronously, optional and
 *               must serialise with respect to non-async I/O.
 * @reg_ग_लिखो: Write a single रेजिस्टर value to the given रेजिस्टर address. This
 *             ग_लिखो operation has to complete when वापसing from the function.
 * @reg_update_bits: Update bits operation to be used against अस्थिर
 *                   रेजिस्टरs, पूर्णांकended क्रम devices supporting some mechanism
 *                   क्रम setting clearing bits without having to
 *                   पढ़ो/modअगरy/ग_लिखो.
 * @पढ़ो: Read operation.  Data is वापसed in the buffer used to transmit
 *         data.
 * @reg_पढ़ो: Read a single रेजिस्टर value from a given रेजिस्टर address.
 * @मुक्त_context: Free context.
 * @async_alloc: Allocate a regmap_async() काष्ठाure.
 * @पढ़ो_flag_mask: Mask to be set in the top byte of the रेजिस्टर when करोing
 *                  a पढ़ो.
 * @reg_क्रमmat_endian_शेष: Default endianness क्रम क्रमmatted रेजिस्टर
 *     addresses. Used when the regmap_config specअगरies DEFAULT. If this is
 *     DEFAULT, BIG is assumed.
 * @val_क्रमmat_endian_शेष: Default endianness क्रम क्रमmatted रेजिस्टर
 *     values. Used when the regmap_config specअगरies DEFAULT. If this is
 *     DEFAULT, BIG is assumed.
 * @max_raw_पढ़ो: Max raw पढ़ो size that can be used on the bus.
 * @max_raw_ग_लिखो: Max raw ग_लिखो size that can be used on the bus.
 */
काष्ठा regmap_bus अणु
	bool fast_io;
	regmap_hw_ग_लिखो ग_लिखो;
	regmap_hw_gather_ग_लिखो gather_ग_लिखो;
	regmap_hw_async_ग_लिखो async_ग_लिखो;
	regmap_hw_reg_ग_लिखो reg_ग_लिखो;
	regmap_hw_reg_update_bits reg_update_bits;
	regmap_hw_पढ़ो पढ़ो;
	regmap_hw_reg_पढ़ो reg_पढ़ो;
	regmap_hw_मुक्त_context मुक्त_context;
	regmap_hw_async_alloc async_alloc;
	u8 पढ़ो_flag_mask;
	क्रमागत regmap_endian reg_क्रमmat_endian_शेष;
	क्रमागत regmap_endian val_क्रमmat_endian_शेष;
	माप_प्रकार max_raw_पढ़ो;
	माप_प्रकार max_raw_ग_लिखो;
पूर्ण;

/*
 * __regmap_init functions.
 *
 * These functions take a lock key and name parameter, and should not be called
 * directly. Instead, use the regmap_init macros that generate a key and name
 * क्रम each call.
 */
काष्ठा regmap *__regmap_init(काष्ठा device *dev,
			     स्थिर काष्ठा regmap_bus *bus,
			     व्योम *bus_context,
			     स्थिर काष्ठा regmap_config *config,
			     काष्ठा lock_class_key *lock_key,
			     स्थिर अक्षर *lock_name);
काष्ठा regmap *__regmap_init_i2c(काष्ठा i2c_client *i2c,
				 स्थिर काष्ठा regmap_config *config,
				 काष्ठा lock_class_key *lock_key,
				 स्थिर अक्षर *lock_name);
काष्ठा regmap *__regmap_init_sccb(काष्ठा i2c_client *i2c,
				  स्थिर काष्ठा regmap_config *config,
				  काष्ठा lock_class_key *lock_key,
				  स्थिर अक्षर *lock_name);
काष्ठा regmap *__regmap_init_slimbus(काष्ठा slim_device *slimbus,
				 स्थिर काष्ठा regmap_config *config,
				 काष्ठा lock_class_key *lock_key,
				 स्थिर अक्षर *lock_name);
काष्ठा regmap *__regmap_init_spi(काष्ठा spi_device *dev,
				 स्थिर काष्ठा regmap_config *config,
				 काष्ठा lock_class_key *lock_key,
				 स्थिर अक्षर *lock_name);
काष्ठा regmap *__regmap_init_spmi_base(काष्ठा spmi_device *dev,
				       स्थिर काष्ठा regmap_config *config,
				       काष्ठा lock_class_key *lock_key,
				       स्थिर अक्षर *lock_name);
काष्ठा regmap *__regmap_init_spmi_ext(काष्ठा spmi_device *dev,
				      स्थिर काष्ठा regmap_config *config,
				      काष्ठा lock_class_key *lock_key,
				      स्थिर अक्षर *lock_name);
काष्ठा regmap *__regmap_init_w1(काष्ठा device *w1_dev,
				 स्थिर काष्ठा regmap_config *config,
				 काष्ठा lock_class_key *lock_key,
				 स्थिर अक्षर *lock_name);
काष्ठा regmap *__regmap_init_mmio_clk(काष्ठा device *dev, स्थिर अक्षर *clk_id,
				      व्योम __iomem *regs,
				      स्थिर काष्ठा regmap_config *config,
				      काष्ठा lock_class_key *lock_key,
				      स्थिर अक्षर *lock_name);
काष्ठा regmap *__regmap_init_ac97(काष्ठा snd_ac97 *ac97,
				  स्थिर काष्ठा regmap_config *config,
				  काष्ठा lock_class_key *lock_key,
				  स्थिर अक्षर *lock_name);
काष्ठा regmap *__regmap_init_sdw(काष्ठा sdw_slave *sdw,
				 स्थिर काष्ठा regmap_config *config,
				 काष्ठा lock_class_key *lock_key,
				 स्थिर अक्षर *lock_name);
काष्ठा regmap *__regmap_init_sdw_mbq(काष्ठा sdw_slave *sdw,
				     स्थिर काष्ठा regmap_config *config,
				     काष्ठा lock_class_key *lock_key,
				     स्थिर अक्षर *lock_name);
काष्ठा regmap *__regmap_init_spi_avmm(काष्ठा spi_device *spi,
				      स्थिर काष्ठा regmap_config *config,
				      काष्ठा lock_class_key *lock_key,
				      स्थिर अक्षर *lock_name);

काष्ठा regmap *__devm_regmap_init(काष्ठा device *dev,
				  स्थिर काष्ठा regmap_bus *bus,
				  व्योम *bus_context,
				  स्थिर काष्ठा regmap_config *config,
				  काष्ठा lock_class_key *lock_key,
				  स्थिर अक्षर *lock_name);
काष्ठा regmap *__devm_regmap_init_i2c(काष्ठा i2c_client *i2c,
				      स्थिर काष्ठा regmap_config *config,
				      काष्ठा lock_class_key *lock_key,
				      स्थिर अक्षर *lock_name);
काष्ठा regmap *__devm_regmap_init_sccb(काष्ठा i2c_client *i2c,
				       स्थिर काष्ठा regmap_config *config,
				       काष्ठा lock_class_key *lock_key,
				       स्थिर अक्षर *lock_name);
काष्ठा regmap *__devm_regmap_init_spi(काष्ठा spi_device *dev,
				      स्थिर काष्ठा regmap_config *config,
				      काष्ठा lock_class_key *lock_key,
				      स्थिर अक्षर *lock_name);
काष्ठा regmap *__devm_regmap_init_spmi_base(काष्ठा spmi_device *dev,
					    स्थिर काष्ठा regmap_config *config,
					    काष्ठा lock_class_key *lock_key,
					    स्थिर अक्षर *lock_name);
काष्ठा regmap *__devm_regmap_init_spmi_ext(काष्ठा spmi_device *dev,
					   स्थिर काष्ठा regmap_config *config,
					   काष्ठा lock_class_key *lock_key,
					   स्थिर अक्षर *lock_name);
काष्ठा regmap *__devm_regmap_init_w1(काष्ठा device *w1_dev,
				      स्थिर काष्ठा regmap_config *config,
				      काष्ठा lock_class_key *lock_key,
				      स्थिर अक्षर *lock_name);
काष्ठा regmap *__devm_regmap_init_mmio_clk(काष्ठा device *dev,
					   स्थिर अक्षर *clk_id,
					   व्योम __iomem *regs,
					   स्थिर काष्ठा regmap_config *config,
					   काष्ठा lock_class_key *lock_key,
					   स्थिर अक्षर *lock_name);
काष्ठा regmap *__devm_regmap_init_ac97(काष्ठा snd_ac97 *ac97,
				       स्थिर काष्ठा regmap_config *config,
				       काष्ठा lock_class_key *lock_key,
				       स्थिर अक्षर *lock_name);
काष्ठा regmap *__devm_regmap_init_sdw(काष्ठा sdw_slave *sdw,
				 स्थिर काष्ठा regmap_config *config,
				 काष्ठा lock_class_key *lock_key,
				 स्थिर अक्षर *lock_name);
काष्ठा regmap *__devm_regmap_init_sdw_mbq(काष्ठा sdw_slave *sdw,
					  स्थिर काष्ठा regmap_config *config,
					  काष्ठा lock_class_key *lock_key,
					  स्थिर अक्षर *lock_name);
काष्ठा regmap *__devm_regmap_init_slimbus(काष्ठा slim_device *slimbus,
				 स्थिर काष्ठा regmap_config *config,
				 काष्ठा lock_class_key *lock_key,
				 स्थिर अक्षर *lock_name);
काष्ठा regmap *__devm_regmap_init_i3c(काष्ठा i3c_device *i3c,
				 स्थिर काष्ठा regmap_config *config,
				 काष्ठा lock_class_key *lock_key,
				 स्थिर अक्षर *lock_name);
काष्ठा regmap *__devm_regmap_init_spi_avmm(काष्ठा spi_device *spi,
					   स्थिर काष्ठा regmap_config *config,
					   काष्ठा lock_class_key *lock_key,
					   स्थिर अक्षर *lock_name);
/*
 * Wrapper क्रम regmap_init macros to include a unique lockdep key and name
 * क्रम each call. No-op अगर CONFIG_LOCKDEP is not set.
 *
 * @fn: Real function to call (in the क्रमm __[*_]regmap_init[_*])
 * @name: Config variable name (#config in the calling macro)
 **/
#अगर_घोषित CONFIG_LOCKDEP
#घोषणा __regmap_lockdep_wrapper(fn, name, ...)				\
(									\
	(अणु								\
		अटल काष्ठा lock_class_key _key;			\
		fn(__VA_ARGS__, &_key,					\
			KBUILD_BASENAME ":"				\
			__stringअगरy(__LINE__) ":"			\
			"(" name ")->lock");				\
	पूर्ण)								\
)
#अन्यथा
#घोषणा __regmap_lockdep_wrapper(fn, name, ...) fn(__VA_ARGS__, शून्य, शून्य)
#पूर्ण_अगर

/**
 * regmap_init() - Initialise रेजिस्टर map
 *
 * @dev: Device that will be पूर्णांकeracted with
 * @bus: Bus-specअगरic callbacks to use with device
 * @bus_context: Data passed to bus-specअगरic callbacks
 * @config: Configuration क्रम रेजिस्टर map
 *
 * The वापस value will be an ERR_PTR() on error or a valid poपूर्णांकer to
 * a काष्ठा regmap.  This function should generally not be called
 * directly, it should be called by bus-specअगरic init functions.
 */
#घोषणा regmap_init(dev, bus, bus_context, config)			\
	__regmap_lockdep_wrapper(__regmap_init, #config,		\
				dev, bus, bus_context, config)
पूर्णांक regmap_attach_dev(काष्ठा device *dev, काष्ठा regmap *map,
		      स्थिर काष्ठा regmap_config *config);

/**
 * regmap_init_i2c() - Initialise रेजिस्टर map
 *
 * @i2c: Device that will be पूर्णांकeracted with
 * @config: Configuration क्रम रेजिस्टर map
 *
 * The वापस value will be an ERR_PTR() on error or a valid poपूर्णांकer to
 * a काष्ठा regmap.
 */
#घोषणा regmap_init_i2c(i2c, config)					\
	__regmap_lockdep_wrapper(__regmap_init_i2c, #config,		\
				i2c, config)

/**
 * regmap_init_sccb() - Initialise रेजिस्टर map
 *
 * @i2c: Device that will be पूर्णांकeracted with
 * @config: Configuration क्रम रेजिस्टर map
 *
 * The वापस value will be an ERR_PTR() on error or a valid poपूर्णांकer to
 * a काष्ठा regmap.
 */
#घोषणा regmap_init_sccb(i2c, config)					\
	__regmap_lockdep_wrapper(__regmap_init_sccb, #config,		\
				i2c, config)

/**
 * regmap_init_slimbus() - Initialise रेजिस्टर map
 *
 * @slimbus: Device that will be पूर्णांकeracted with
 * @config: Configuration क्रम रेजिस्टर map
 *
 * The वापस value will be an ERR_PTR() on error or a valid poपूर्णांकer to
 * a काष्ठा regmap.
 */
#घोषणा regmap_init_slimbus(slimbus, config)				\
	__regmap_lockdep_wrapper(__regmap_init_slimbus, #config,	\
				slimbus, config)

/**
 * regmap_init_spi() - Initialise रेजिस्टर map
 *
 * @dev: Device that will be पूर्णांकeracted with
 * @config: Configuration क्रम रेजिस्टर map
 *
 * The वापस value will be an ERR_PTR() on error or a valid poपूर्णांकer to
 * a काष्ठा regmap.
 */
#घोषणा regmap_init_spi(dev, config)					\
	__regmap_lockdep_wrapper(__regmap_init_spi, #config,		\
				dev, config)

/**
 * regmap_init_spmi_base() - Create regmap क्रम the Base रेजिस्टर space
 *
 * @dev:	SPMI device that will be पूर्णांकeracted with
 * @config:	Configuration क्रम रेजिस्टर map
 *
 * The वापस value will be an ERR_PTR() on error or a valid poपूर्णांकer to
 * a काष्ठा regmap.
 */
#घोषणा regmap_init_spmi_base(dev, config)				\
	__regmap_lockdep_wrapper(__regmap_init_spmi_base, #config,	\
				dev, config)

/**
 * regmap_init_spmi_ext() - Create regmap क्रम Ext रेजिस्टर space
 *
 * @dev:	Device that will be पूर्णांकeracted with
 * @config:	Configuration क्रम रेजिस्टर map
 *
 * The वापस value will be an ERR_PTR() on error or a valid poपूर्णांकer to
 * a काष्ठा regmap.
 */
#घोषणा regmap_init_spmi_ext(dev, config)				\
	__regmap_lockdep_wrapper(__regmap_init_spmi_ext, #config,	\
				dev, config)

/**
 * regmap_init_w1() - Initialise रेजिस्टर map
 *
 * @w1_dev: Device that will be पूर्णांकeracted with
 * @config: Configuration क्रम रेजिस्टर map
 *
 * The वापस value will be an ERR_PTR() on error or a valid poपूर्णांकer to
 * a काष्ठा regmap.
 */
#घोषणा regmap_init_w1(w1_dev, config)					\
	__regmap_lockdep_wrapper(__regmap_init_w1, #config,		\
				w1_dev, config)

/**
 * regmap_init_mmio_clk() - Initialise रेजिस्टर map with रेजिस्टर घड़ी
 *
 * @dev: Device that will be पूर्णांकeracted with
 * @clk_id: रेजिस्टर घड़ी consumer ID
 * @regs: Poपूर्णांकer to memory-mapped IO region
 * @config: Configuration क्रम रेजिस्टर map
 *
 * The वापस value will be an ERR_PTR() on error or a valid poपूर्णांकer to
 * a काष्ठा regmap.
 */
#घोषणा regmap_init_mmio_clk(dev, clk_id, regs, config)			\
	__regmap_lockdep_wrapper(__regmap_init_mmio_clk, #config,	\
				dev, clk_id, regs, config)

/**
 * regmap_init_mmio() - Initialise रेजिस्टर map
 *
 * @dev: Device that will be पूर्णांकeracted with
 * @regs: Poपूर्णांकer to memory-mapped IO region
 * @config: Configuration क्रम रेजिस्टर map
 *
 * The वापस value will be an ERR_PTR() on error or a valid poपूर्णांकer to
 * a काष्ठा regmap.
 */
#घोषणा regmap_init_mmio(dev, regs, config)		\
	regmap_init_mmio_clk(dev, शून्य, regs, config)

/**
 * regmap_init_ac97() - Initialise AC'97 रेजिस्टर map
 *
 * @ac97: Device that will be पूर्णांकeracted with
 * @config: Configuration क्रम रेजिस्टर map
 *
 * The वापस value will be an ERR_PTR() on error or a valid poपूर्णांकer to
 * a काष्ठा regmap.
 */
#घोषणा regmap_init_ac97(ac97, config)					\
	__regmap_lockdep_wrapper(__regmap_init_ac97, #config,		\
				ac97, config)
bool regmap_ac97_शेष_अस्थिर(काष्ठा device *dev, अचिन्हित पूर्णांक reg);

/**
 * regmap_init_sdw() - Initialise रेजिस्टर map
 *
 * @sdw: Device that will be पूर्णांकeracted with
 * @config: Configuration क्रम रेजिस्टर map
 *
 * The वापस value will be an ERR_PTR() on error or a valid poपूर्णांकer to
 * a काष्ठा regmap.
 */
#घोषणा regmap_init_sdw(sdw, config)					\
	__regmap_lockdep_wrapper(__regmap_init_sdw, #config,		\
				sdw, config)

/**
 * regmap_init_sdw_mbq() - Initialise रेजिस्टर map
 *
 * @sdw: Device that will be पूर्णांकeracted with
 * @config: Configuration क्रम रेजिस्टर map
 *
 * The वापस value will be an ERR_PTR() on error or a valid poपूर्णांकer to
 * a काष्ठा regmap.
 */
#घोषणा regmap_init_sdw_mbq(sdw, config)					\
	__regmap_lockdep_wrapper(__regmap_init_sdw_mbq, #config,		\
				sdw, config)

/**
 * regmap_init_spi_avmm() - Initialize रेजिस्टर map क्रम Intel SPI Slave
 * to AVMM Bus Bridge
 *
 * @spi: Device that will be पूर्णांकeracted with
 * @config: Configuration क्रम रेजिस्टर map
 *
 * The वापस value will be an ERR_PTR() on error or a valid poपूर्णांकer
 * to a काष्ठा regmap.
 */
#घोषणा regmap_init_spi_avmm(spi, config)					\
	__regmap_lockdep_wrapper(__regmap_init_spi_avmm, #config,		\
				 spi, config)

/**
 * devm_regmap_init() - Initialise managed रेजिस्टर map
 *
 * @dev: Device that will be पूर्णांकeracted with
 * @bus: Bus-specअगरic callbacks to use with device
 * @bus_context: Data passed to bus-specअगरic callbacks
 * @config: Configuration क्रम रेजिस्टर map
 *
 * The वापस value will be an ERR_PTR() on error or a valid poपूर्णांकer
 * to a काष्ठा regmap.  This function should generally not be called
 * directly, it should be called by bus-specअगरic init functions.  The
 * map will be स्वतःmatically मुक्तd by the device management code.
 */
#घोषणा devm_regmap_init(dev, bus, bus_context, config)			\
	__regmap_lockdep_wrapper(__devm_regmap_init, #config,		\
				dev, bus, bus_context, config)

/**
 * devm_regmap_init_i2c() - Initialise managed रेजिस्टर map
 *
 * @i2c: Device that will be पूर्णांकeracted with
 * @config: Configuration क्रम रेजिस्टर map
 *
 * The वापस value will be an ERR_PTR() on error or a valid poपूर्णांकer
 * to a काष्ठा regmap.  The regmap will be स्वतःmatically मुक्तd by the
 * device management code.
 */
#घोषणा devm_regmap_init_i2c(i2c, config)				\
	__regmap_lockdep_wrapper(__devm_regmap_init_i2c, #config,	\
				i2c, config)

/**
 * devm_regmap_init_sccb() - Initialise managed रेजिस्टर map
 *
 * @i2c: Device that will be पूर्णांकeracted with
 * @config: Configuration क्रम रेजिस्टर map
 *
 * The वापस value will be an ERR_PTR() on error or a valid poपूर्णांकer
 * to a काष्ठा regmap.  The regmap will be स्वतःmatically मुक्तd by the
 * device management code.
 */
#घोषणा devm_regmap_init_sccb(i2c, config)				\
	__regmap_lockdep_wrapper(__devm_regmap_init_sccb, #config,	\
				i2c, config)

/**
 * devm_regmap_init_spi() - Initialise रेजिस्टर map
 *
 * @dev: Device that will be पूर्णांकeracted with
 * @config: Configuration क्रम रेजिस्टर map
 *
 * The वापस value will be an ERR_PTR() on error or a valid poपूर्णांकer
 * to a काष्ठा regmap.  The map will be स्वतःmatically मुक्तd by the
 * device management code.
 */
#घोषणा devm_regmap_init_spi(dev, config)				\
	__regmap_lockdep_wrapper(__devm_regmap_init_spi, #config,	\
				dev, config)

/**
 * devm_regmap_init_spmi_base() - Create managed regmap क्रम Base रेजिस्टर space
 *
 * @dev:	SPMI device that will be पूर्णांकeracted with
 * @config:	Configuration क्रम रेजिस्टर map
 *
 * The वापस value will be an ERR_PTR() on error or a valid poपूर्णांकer
 * to a काष्ठा regmap.  The regmap will be स्वतःmatically मुक्तd by the
 * device management code.
 */
#घोषणा devm_regmap_init_spmi_base(dev, config)				\
	__regmap_lockdep_wrapper(__devm_regmap_init_spmi_base, #config,	\
				dev, config)

/**
 * devm_regmap_init_spmi_ext() - Create managed regmap क्रम Ext रेजिस्टर space
 *
 * @dev:	SPMI device that will be पूर्णांकeracted with
 * @config:	Configuration क्रम रेजिस्टर map
 *
 * The वापस value will be an ERR_PTR() on error or a valid poपूर्णांकer
 * to a काष्ठा regmap.  The regmap will be स्वतःmatically मुक्तd by the
 * device management code.
 */
#घोषणा devm_regmap_init_spmi_ext(dev, config)				\
	__regmap_lockdep_wrapper(__devm_regmap_init_spmi_ext, #config,	\
				dev, config)

/**
 * devm_regmap_init_w1() - Initialise managed रेजिस्टर map
 *
 * @w1_dev: Device that will be पूर्णांकeracted with
 * @config: Configuration क्रम रेजिस्टर map
 *
 * The वापस value will be an ERR_PTR() on error or a valid poपूर्णांकer
 * to a काष्ठा regmap.  The regmap will be स्वतःmatically मुक्तd by the
 * device management code.
 */
#घोषणा devm_regmap_init_w1(w1_dev, config)				\
	__regmap_lockdep_wrapper(__devm_regmap_init_w1, #config,	\
				w1_dev, config)
/**
 * devm_regmap_init_mmio_clk() - Initialise managed रेजिस्टर map with घड़ी
 *
 * @dev: Device that will be पूर्णांकeracted with
 * @clk_id: रेजिस्टर घड़ी consumer ID
 * @regs: Poपूर्णांकer to memory-mapped IO region
 * @config: Configuration क्रम रेजिस्टर map
 *
 * The वापस value will be an ERR_PTR() on error or a valid poपूर्णांकer
 * to a काष्ठा regmap.  The regmap will be स्वतःmatically मुक्तd by the
 * device management code.
 */
#घोषणा devm_regmap_init_mmio_clk(dev, clk_id, regs, config)		\
	__regmap_lockdep_wrapper(__devm_regmap_init_mmio_clk, #config,	\
				dev, clk_id, regs, config)

/**
 * devm_regmap_init_mmio() - Initialise managed रेजिस्टर map
 *
 * @dev: Device that will be पूर्णांकeracted with
 * @regs: Poपूर्णांकer to memory-mapped IO region
 * @config: Configuration क्रम रेजिस्टर map
 *
 * The वापस value will be an ERR_PTR() on error or a valid poपूर्णांकer
 * to a काष्ठा regmap.  The regmap will be स्वतःmatically मुक्तd by the
 * device management code.
 */
#घोषणा devm_regmap_init_mmio(dev, regs, config)		\
	devm_regmap_init_mmio_clk(dev, शून्य, regs, config)

/**
 * devm_regmap_init_ac97() - Initialise AC'97 रेजिस्टर map
 *
 * @ac97: Device that will be पूर्णांकeracted with
 * @config: Configuration क्रम रेजिस्टर map
 *
 * The वापस value will be an ERR_PTR() on error or a valid poपूर्णांकer
 * to a काष्ठा regmap.  The regmap will be स्वतःmatically मुक्तd by the
 * device management code.
 */
#घोषणा devm_regmap_init_ac97(ac97, config)				\
	__regmap_lockdep_wrapper(__devm_regmap_init_ac97, #config,	\
				ac97, config)

/**
 * devm_regmap_init_sdw() - Initialise managed रेजिस्टर map
 *
 * @sdw: Device that will be पूर्णांकeracted with
 * @config: Configuration क्रम रेजिस्टर map
 *
 * The वापस value will be an ERR_PTR() on error or a valid poपूर्णांकer
 * to a काष्ठा regmap. The regmap will be स्वतःmatically मुक्तd by the
 * device management code.
 */
#घोषणा devm_regmap_init_sdw(sdw, config)				\
	__regmap_lockdep_wrapper(__devm_regmap_init_sdw, #config,	\
				sdw, config)

/**
 * devm_regmap_init_sdw_mbq() - Initialise managed रेजिस्टर map
 *
 * @sdw: Device that will be पूर्णांकeracted with
 * @config: Configuration क्रम रेजिस्टर map
 *
 * The वापस value will be an ERR_PTR() on error or a valid poपूर्णांकer
 * to a काष्ठा regmap. The regmap will be स्वतःmatically मुक्तd by the
 * device management code.
 */
#घोषणा devm_regmap_init_sdw_mbq(sdw, config)			\
	__regmap_lockdep_wrapper(__devm_regmap_init_sdw_mbq, #config,   \
				sdw, config)

/**
 * devm_regmap_init_slimbus() - Initialise managed रेजिस्टर map
 *
 * @slimbus: Device that will be पूर्णांकeracted with
 * @config: Configuration क्रम रेजिस्टर map
 *
 * The वापस value will be an ERR_PTR() on error or a valid poपूर्णांकer
 * to a काष्ठा regmap. The regmap will be स्वतःmatically मुक्तd by the
 * device management code.
 */
#घोषणा devm_regmap_init_slimbus(slimbus, config)			\
	__regmap_lockdep_wrapper(__devm_regmap_init_slimbus, #config,	\
				slimbus, config)

/**
 * devm_regmap_init_i3c() - Initialise managed रेजिस्टर map
 *
 * @i3c: Device that will be पूर्णांकeracted with
 * @config: Configuration क्रम रेजिस्टर map
 *
 * The वापस value will be an ERR_PTR() on error or a valid poपूर्णांकer
 * to a काष्ठा regmap.  The regmap will be स्वतःmatically मुक्तd by the
 * device management code.
 */
#घोषणा devm_regmap_init_i3c(i3c, config)				\
	__regmap_lockdep_wrapper(__devm_regmap_init_i3c, #config,	\
				i3c, config)

/**
 * devm_regmap_init_spi_avmm() - Initialize रेजिस्टर map क्रम Intel SPI Slave
 * to AVMM Bus Bridge
 *
 * @spi: Device that will be पूर्णांकeracted with
 * @config: Configuration क्रम रेजिस्टर map
 *
 * The वापस value will be an ERR_PTR() on error or a valid poपूर्णांकer
 * to a काष्ठा regmap.  The map will be स्वतःmatically मुक्तd by the
 * device management code.
 */
#घोषणा devm_regmap_init_spi_avmm(spi, config)				\
	__regmap_lockdep_wrapper(__devm_regmap_init_spi_avmm, #config,	\
				 spi, config)

पूर्णांक regmap_mmio_attach_clk(काष्ठा regmap *map, काष्ठा clk *clk);
व्योम regmap_mmio_detach_clk(काष्ठा regmap *map);
व्योम regmap_निकास(काष्ठा regmap *map);
पूर्णांक regmap_reinit_cache(काष्ठा regmap *map,
			स्थिर काष्ठा regmap_config *config);
काष्ठा regmap *dev_get_regmap(काष्ठा device *dev, स्थिर अक्षर *name);
काष्ठा device *regmap_get_device(काष्ठा regmap *map);
पूर्णांक regmap_ग_लिखो(काष्ठा regmap *map, अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक val);
पूर्णांक regmap_ग_लिखो_async(काष्ठा regmap *map, अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक val);
पूर्णांक regmap_raw_ग_लिखो(काष्ठा regmap *map, अचिन्हित पूर्णांक reg,
		     स्थिर व्योम *val, माप_प्रकार val_len);
पूर्णांक regmap_noinc_ग_लिखो(काष्ठा regmap *map, अचिन्हित पूर्णांक reg,
		     स्थिर व्योम *val, माप_प्रकार val_len);
पूर्णांक regmap_bulk_ग_लिखो(काष्ठा regmap *map, अचिन्हित पूर्णांक reg, स्थिर व्योम *val,
			माप_प्रकार val_count);
पूर्णांक regmap_multi_reg_ग_लिखो(काष्ठा regmap *map, स्थिर काष्ठा reg_sequence *regs,
			पूर्णांक num_regs);
पूर्णांक regmap_multi_reg_ग_लिखो_bypassed(काष्ठा regmap *map,
				    स्थिर काष्ठा reg_sequence *regs,
				    पूर्णांक num_regs);
पूर्णांक regmap_raw_ग_लिखो_async(काष्ठा regmap *map, अचिन्हित पूर्णांक reg,
			   स्थिर व्योम *val, माप_प्रकार val_len);
पूर्णांक regmap_पढ़ो(काष्ठा regmap *map, अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक *val);
पूर्णांक regmap_raw_पढ़ो(काष्ठा regmap *map, अचिन्हित पूर्णांक reg,
		    व्योम *val, माप_प्रकार val_len);
पूर्णांक regmap_noinc_पढ़ो(काष्ठा regmap *map, अचिन्हित पूर्णांक reg,
		      व्योम *val, माप_प्रकार val_len);
पूर्णांक regmap_bulk_पढ़ो(काष्ठा regmap *map, अचिन्हित पूर्णांक reg, व्योम *val,
		     माप_प्रकार val_count);
पूर्णांक regmap_update_bits_base(काष्ठा regmap *map, अचिन्हित पूर्णांक reg,
			    अचिन्हित पूर्णांक mask, अचिन्हित पूर्णांक val,
			    bool *change, bool async, bool क्रमce);

अटल अंतरभूत पूर्णांक regmap_update_bits(काष्ठा regmap *map, अचिन्हित पूर्णांक reg,
				     अचिन्हित पूर्णांक mask, अचिन्हित पूर्णांक val)
अणु
	वापस regmap_update_bits_base(map, reg, mask, val, शून्य, false, false);
पूर्ण

अटल अंतरभूत पूर्णांक regmap_update_bits_async(काष्ठा regmap *map, अचिन्हित पूर्णांक reg,
					   अचिन्हित पूर्णांक mask, अचिन्हित पूर्णांक val)
अणु
	वापस regmap_update_bits_base(map, reg, mask, val, शून्य, true, false);
पूर्ण

अटल अंतरभूत पूर्णांक regmap_update_bits_check(काष्ठा regmap *map, अचिन्हित पूर्णांक reg,
					   अचिन्हित पूर्णांक mask, अचिन्हित पूर्णांक val,
					   bool *change)
अणु
	वापस regmap_update_bits_base(map, reg, mask, val,
				       change, false, false);
पूर्ण

अटल अंतरभूत पूर्णांक
regmap_update_bits_check_async(काष्ठा regmap *map, अचिन्हित पूर्णांक reg,
			       अचिन्हित पूर्णांक mask, अचिन्हित पूर्णांक val,
			       bool *change)
अणु
	वापस regmap_update_bits_base(map, reg, mask, val,
				       change, true, false);
पूर्ण

अटल अंतरभूत पूर्णांक regmap_ग_लिखो_bits(काष्ठा regmap *map, अचिन्हित पूर्णांक reg,
				    अचिन्हित पूर्णांक mask, अचिन्हित पूर्णांक val)
अणु
	वापस regmap_update_bits_base(map, reg, mask, val, शून्य, false, true);
पूर्ण

पूर्णांक regmap_get_val_bytes(काष्ठा regmap *map);
पूर्णांक regmap_get_max_रेजिस्टर(काष्ठा regmap *map);
पूर्णांक regmap_get_reg_stride(काष्ठा regmap *map);
पूर्णांक regmap_async_complete(काष्ठा regmap *map);
bool regmap_can_raw_ग_लिखो(काष्ठा regmap *map);
माप_प्रकार regmap_get_raw_पढ़ो_max(काष्ठा regmap *map);
माप_प्रकार regmap_get_raw_ग_लिखो_max(काष्ठा regmap *map);

पूर्णांक regcache_sync(काष्ठा regmap *map);
पूर्णांक regcache_sync_region(काष्ठा regmap *map, अचिन्हित पूर्णांक min,
			 अचिन्हित पूर्णांक max);
पूर्णांक regcache_drop_region(काष्ठा regmap *map, अचिन्हित पूर्णांक min,
			 अचिन्हित पूर्णांक max);
व्योम regcache_cache_only(काष्ठा regmap *map, bool enable);
व्योम regcache_cache_bypass(काष्ठा regmap *map, bool enable);
व्योम regcache_mark_dirty(काष्ठा regmap *map);

bool regmap_check_range_table(काष्ठा regmap *map, अचिन्हित पूर्णांक reg,
			      स्थिर काष्ठा regmap_access_table *table);

पूर्णांक regmap_रेजिस्टर_patch(काष्ठा regmap *map, स्थिर काष्ठा reg_sequence *regs,
			  पूर्णांक num_regs);
पूर्णांक regmap_parse_val(काष्ठा regmap *map, स्थिर व्योम *buf,
				अचिन्हित पूर्णांक *val);

अटल अंतरभूत bool regmap_reg_in_range(अचिन्हित पूर्णांक reg,
				       स्थिर काष्ठा regmap_range *range)
अणु
	वापस reg >= range->range_min && reg <= range->range_max;
पूर्ण

bool regmap_reg_in_ranges(अचिन्हित पूर्णांक reg,
			  स्थिर काष्ठा regmap_range *ranges,
			  अचिन्हित पूर्णांक nranges);

अटल अंतरभूत पूर्णांक regmap_set_bits(काष्ठा regmap *map,
				  अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक bits)
अणु
	वापस regmap_update_bits_base(map, reg, bits, bits,
				       शून्य, false, false);
पूर्ण

अटल अंतरभूत पूर्णांक regmap_clear_bits(काष्ठा regmap *map,
				    अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक bits)
अणु
	वापस regmap_update_bits_base(map, reg, bits, 0, शून्य, false, false);
पूर्ण

पूर्णांक regmap_test_bits(काष्ठा regmap *map, अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक bits);

/**
 * काष्ठा reg_field - Description of an रेजिस्टर field
 *
 * @reg: Offset of the रेजिस्टर within the regmap bank
 * @lsb: lsb of the रेजिस्टर field.
 * @msb: msb of the रेजिस्टर field.
 * @id_size: port size अगर it has some ports
 * @id_offset: address offset क्रम each ports
 */
काष्ठा reg_field अणु
	अचिन्हित पूर्णांक reg;
	अचिन्हित पूर्णांक lsb;
	अचिन्हित पूर्णांक msb;
	अचिन्हित पूर्णांक id_size;
	अचिन्हित पूर्णांक id_offset;
पूर्ण;

#घोषणा REG_FIELD(_reg, _lsb, _msb) अणु		\
				.reg = _reg,	\
				.lsb = _lsb,	\
				.msb = _msb,	\
				पूर्ण

#घोषणा REG_FIELD_ID(_reg, _lsb, _msb, _size, _offset) अणु	\
				.reg = _reg,			\
				.lsb = _lsb,			\
				.msb = _msb,			\
				.id_size = _size,		\
				.id_offset = _offset,		\
				पूर्ण

काष्ठा regmap_field *regmap_field_alloc(काष्ठा regmap *regmap,
		काष्ठा reg_field reg_field);
व्योम regmap_field_मुक्त(काष्ठा regmap_field *field);

काष्ठा regmap_field *devm_regmap_field_alloc(काष्ठा device *dev,
		काष्ठा regmap *regmap, काष्ठा reg_field reg_field);
व्योम devm_regmap_field_मुक्त(काष्ठा device *dev,	काष्ठा regmap_field *field);

पूर्णांक regmap_field_bulk_alloc(काष्ठा regmap *regmap,
			     काष्ठा regmap_field **rm_field,
			     काष्ठा reg_field *reg_field,
			     पूर्णांक num_fields);
व्योम regmap_field_bulk_मुक्त(काष्ठा regmap_field *field);
पूर्णांक devm_regmap_field_bulk_alloc(काष्ठा device *dev, काष्ठा regmap *regmap,
				 काष्ठा regmap_field **field,
				 काष्ठा reg_field *reg_field, पूर्णांक num_fields);
व्योम devm_regmap_field_bulk_मुक्त(काष्ठा device *dev,
				 काष्ठा regmap_field *field);

पूर्णांक regmap_field_पढ़ो(काष्ठा regmap_field *field, अचिन्हित पूर्णांक *val);
पूर्णांक regmap_field_update_bits_base(काष्ठा regmap_field *field,
				  अचिन्हित पूर्णांक mask, अचिन्हित पूर्णांक val,
				  bool *change, bool async, bool क्रमce);
पूर्णांक regmap_fields_पढ़ो(काष्ठा regmap_field *field, अचिन्हित पूर्णांक id,
		       अचिन्हित पूर्णांक *val);
पूर्णांक regmap_fields_update_bits_base(काष्ठा regmap_field *field,  अचिन्हित पूर्णांक id,
				   अचिन्हित पूर्णांक mask, अचिन्हित पूर्णांक val,
				   bool *change, bool async, bool क्रमce);

अटल अंतरभूत पूर्णांक regmap_field_ग_लिखो(काष्ठा regmap_field *field,
				     अचिन्हित पूर्णांक val)
अणु
	वापस regmap_field_update_bits_base(field, ~0, val,
					     शून्य, false, false);
पूर्ण

अटल अंतरभूत पूर्णांक regmap_field_क्रमce_ग_लिखो(काष्ठा regmap_field *field,
					   अचिन्हित पूर्णांक val)
अणु
	वापस regmap_field_update_bits_base(field, ~0, val, शून्य, false, true);
पूर्ण

अटल अंतरभूत पूर्णांक regmap_field_update_bits(काष्ठा regmap_field *field,
					   अचिन्हित पूर्णांक mask, अचिन्हित पूर्णांक val)
अणु
	वापस regmap_field_update_bits_base(field, mask, val,
					     शून्य, false, false);
पूर्ण

अटल अंतरभूत पूर्णांक
regmap_field_क्रमce_update_bits(काष्ठा regmap_field *field,
			       अचिन्हित पूर्णांक mask, अचिन्हित पूर्णांक val)
अणु
	वापस regmap_field_update_bits_base(field, mask, val,
					     शून्य, false, true);
पूर्ण

अटल अंतरभूत पूर्णांक regmap_fields_ग_लिखो(काष्ठा regmap_field *field,
				      अचिन्हित पूर्णांक id, अचिन्हित पूर्णांक val)
अणु
	वापस regmap_fields_update_bits_base(field, id, ~0, val,
					      शून्य, false, false);
पूर्ण

अटल अंतरभूत पूर्णांक regmap_fields_क्रमce_ग_लिखो(काष्ठा regmap_field *field,
					    अचिन्हित पूर्णांक id, अचिन्हित पूर्णांक val)
अणु
	वापस regmap_fields_update_bits_base(field, id, ~0, val,
					      शून्य, false, true);
पूर्ण

अटल अंतरभूत पूर्णांक
regmap_fields_update_bits(काष्ठा regmap_field *field, अचिन्हित पूर्णांक id,
			  अचिन्हित पूर्णांक mask, अचिन्हित पूर्णांक val)
अणु
	वापस regmap_fields_update_bits_base(field, id, mask, val,
					      शून्य, false, false);
पूर्ण

अटल अंतरभूत पूर्णांक
regmap_fields_क्रमce_update_bits(काष्ठा regmap_field *field, अचिन्हित पूर्णांक id,
				अचिन्हित पूर्णांक mask, अचिन्हित पूर्णांक val)
अणु
	वापस regmap_fields_update_bits_base(field, id, mask, val,
					      शून्य, false, true);
पूर्ण

/**
 * काष्ठा regmap_irq_type - IRQ type definitions.
 *
 * @type_reg_offset: Offset रेजिस्टर क्रम the irq type setting.
 * @type_rising_val: Register value to configure RISING type irq.
 * @type_falling_val: Register value to configure FALLING type irq.
 * @type_level_low_val: Register value to configure LEVEL_LOW type irq.
 * @type_level_high_val: Register value to configure LEVEL_HIGH type irq.
 * @types_supported: logical OR of IRQ_TYPE_* flags indicating supported types.
 */
काष्ठा regmap_irq_type अणु
	अचिन्हित पूर्णांक type_reg_offset;
	अचिन्हित पूर्णांक type_reg_mask;
	अचिन्हित पूर्णांक type_rising_val;
	अचिन्हित पूर्णांक type_falling_val;
	अचिन्हित पूर्णांक type_level_low_val;
	अचिन्हित पूर्णांक type_level_high_val;
	अचिन्हित पूर्णांक types_supported;
पूर्ण;

/**
 * काष्ठा regmap_irq - Description of an IRQ क्रम the generic regmap irq_chip.
 *
 * @reg_offset: Offset of the status/mask रेजिस्टर within the bank
 * @mask:       Mask used to flag/control the रेजिस्टर.
 * @type:	IRQ trigger type setting details अगर supported.
 */
काष्ठा regmap_irq अणु
	अचिन्हित पूर्णांक reg_offset;
	अचिन्हित पूर्णांक mask;
	काष्ठा regmap_irq_type type;
पूर्ण;

#घोषणा REGMAP_IRQ_REG(_irq, _off, _mask)		\
	[_irq] = अणु .reg_offset = (_off), .mask = (_mask) पूर्ण

#घोषणा REGMAP_IRQ_REG_LINE(_id, _reg_bits) \
	[_id] = अणु				\
		.mask = BIT((_id) % (_reg_bits)),	\
		.reg_offset = (_id) / (_reg_bits),	\
	पूर्ण

#घोषणा REGMAP_IRQ_MAIN_REG_OFFSET(arr)				\
	अणु .num_regs = ARRAY_SIZE((arr)), .offset = &(arr)[0] पूर्ण

काष्ठा regmap_irq_sub_irq_map अणु
	अचिन्हित पूर्णांक num_regs;
	अचिन्हित पूर्णांक *offset;
पूर्ण;

/**
 * काष्ठा regmap_irq_chip - Description of a generic regmap irq_chip.
 *
 * @name:        Descriptive name क्रम IRQ controller.
 *
 * @मुख्य_status: Base मुख्य status रेजिस्टर address. For chips which have
 *		 पूर्णांकerrupts arranged in separate sub-irq blocks with own IRQ
 *		 रेजिस्टरs and which have a मुख्य IRQ रेजिस्टरs indicating
 *		 sub-irq blocks with unhandled पूर्णांकerrupts. For such chips fill
 *		 sub-irq रेजिस्टर inक्रमmation in status_base, mask_base and
 *		 ack_base.
 * @num_मुख्य_status_bits: Should be given to chips where number of meaningfull
 *			  मुख्य status bits dअगरfers from num_regs.
 * @sub_reg_offsets: arrays of mappings from मुख्य रेजिस्टर bits to sub irq
 *		     रेजिस्टरs. First item in array describes the रेजिस्टरs
 *		     क्रम first मुख्य status bit. Second array क्रम second bit etc.
 *		     Offset is given as sub रेजिस्टर status offset to
 *		     status_base. Should contain num_regs arrays.
 *		     Can be provided क्रम chips with more complex mapping than
 *		     1.st bit to 1.st sub-reg, 2.nd bit to 2.nd sub-reg, ...
 *		     When used with not_fixed_stride, each one-element array
 *		     member contains offset calculated as address from each
 *		     peripheral to first peripheral.
 * @num_मुख्य_regs: Number of 'main status' irq रेजिस्टरs क्रम chips which have
 *		   मुख्य_status set.
 *
 * @status_base: Base status रेजिस्टर address.
 * @mask_base:   Base mask रेजिस्टर address.
 * @mask_ग_लिखोonly: Base mask रेजिस्टर is ग_लिखो only.
 * @unmask_base:  Base unmask रेजिस्टर address. क्रम chips who have
 *                separate mask and unmask रेजिस्टरs
 * @ack_base:    Base ack address. If zero then the chip is clear on पढ़ो.
 *               Using zero value is possible with @use_ack bit.
 * @wake_base:   Base address क्रम wake enables.  If zero unsupported.
 * @type_base:   Base address क्रम irq type.  If zero unsupported.
 * @virt_reg_base:   Base addresses क्रम extra config regs.
 * @irq_reg_stride:  Stride to use क्रम chips where रेजिस्टरs are not contiguous.
 * @init_ack_masked: Ack all masked पूर्णांकerrupts once during initalization.
 * @mask_invert: Inverted mask रेजिस्टर: cleared bits are masked out.
 * @use_ack:     Use @ack रेजिस्टर even अगर it is zero.
 * @ack_invert:  Inverted ack रेजिस्टर: cleared bits क्रम ack.
 * @clear_ack:  Use this to set 1 and 0 or vice-versa to clear पूर्णांकerrupts.
 * @wake_invert: Inverted wake रेजिस्टर: cleared bits are wake enabled.
 * @type_invert: Invert the type flags.
 * @type_in_mask: Use the mask रेजिस्टरs क्रम controlling irq type. For
 *                पूर्णांकerrupts defining type_rising/falling_mask use mask_base
 *                क्रम edge configuration and never update bits in type_base.
 * @clear_on_unmask: For chips with पूर्णांकerrupts cleared on पढ़ो: पढ़ो the status
 *                   रेजिस्टरs beक्रमe unmasking पूर्णांकerrupts to clear any bits
 *                   set when they were masked.
 * @not_fixed_stride: Used when chip peripherals are not laid out with fixed
 * 		      stride. Must be used with sub_reg_offsets containing the
 * 		      offsets to each peripheral.
 * @runसमय_pm:  Hold a runसमय PM lock on the device when accessing it.
 *
 * @num_regs:    Number of रेजिस्टरs in each control bank.
 * @irqs:        Descriptors क्रम inभागidual IRQs.  Interrupt numbers are
 *               asचिन्हित based on the index in the array of the पूर्णांकerrupt.
 * @num_irqs:    Number of descriptors.
 * @num_type_reg:    Number of type रेजिस्टरs.
 * @num_virt_regs:   Number of non-standard irq configuration रेजिस्टरs.
 *		     If zero unsupported.
 * @type_reg_stride: Stride to use क्रम chips where type रेजिस्टरs are not
 *			contiguous.
 * @handle_pre_irq:  Driver specअगरic callback to handle पूर्णांकerrupt from device
 *		     beक्रमe regmap_irq_handler process the पूर्णांकerrupts.
 * @handle_post_irq: Driver specअगरic callback to handle पूर्णांकerrupt from device
 *		     after handling the पूर्णांकerrupts in regmap_irq_handler().
 * @set_type_virt:   Driver specअगरic callback to extend regmap_irq_set_type()
 *		     and configure virt regs.
 * @irq_drv_data:    Driver specअगरic IRQ data which is passed as parameter when
 *		     driver specअगरic pre/post पूर्णांकerrupt handler is called.
 *
 * This is not पूर्णांकended to handle every possible पूर्णांकerrupt controller, but
 * it should handle a substantial proportion of those that are found in the
 * wild.
 */
काष्ठा regmap_irq_chip अणु
	स्थिर अक्षर *name;

	अचिन्हित पूर्णांक मुख्य_status;
	अचिन्हित पूर्णांक num_मुख्य_status_bits;
	काष्ठा regmap_irq_sub_irq_map *sub_reg_offsets;
	पूर्णांक num_मुख्य_regs;

	अचिन्हित पूर्णांक status_base;
	अचिन्हित पूर्णांक mask_base;
	अचिन्हित पूर्णांक unmask_base;
	अचिन्हित पूर्णांक ack_base;
	अचिन्हित पूर्णांक wake_base;
	अचिन्हित पूर्णांक type_base;
	अचिन्हित पूर्णांक *virt_reg_base;
	अचिन्हित पूर्णांक irq_reg_stride;
	bool mask_ग_लिखोonly:1;
	bool init_ack_masked:1;
	bool mask_invert:1;
	bool use_ack:1;
	bool ack_invert:1;
	bool clear_ack:1;
	bool wake_invert:1;
	bool runसमय_pm:1;
	bool type_invert:1;
	bool type_in_mask:1;
	bool clear_on_unmask:1;
	bool not_fixed_stride:1;

	पूर्णांक num_regs;

	स्थिर काष्ठा regmap_irq *irqs;
	पूर्णांक num_irqs;

	पूर्णांक num_type_reg;
	पूर्णांक num_virt_regs;
	अचिन्हित पूर्णांक type_reg_stride;

	पूर्णांक (*handle_pre_irq)(व्योम *irq_drv_data);
	पूर्णांक (*handle_post_irq)(व्योम *irq_drv_data);
	पूर्णांक (*set_type_virt)(अचिन्हित पूर्णांक **buf, अचिन्हित पूर्णांक type,
			     अचिन्हित दीर्घ hwirq, पूर्णांक reg);
	व्योम *irq_drv_data;
पूर्ण;

काष्ठा regmap_irq_chip_data;

पूर्णांक regmap_add_irq_chip(काष्ठा regmap *map, पूर्णांक irq, पूर्णांक irq_flags,
			पूर्णांक irq_base, स्थिर काष्ठा regmap_irq_chip *chip,
			काष्ठा regmap_irq_chip_data **data);
पूर्णांक regmap_add_irq_chip_fwnode(काष्ठा fwnode_handle *fwnode,
			       काष्ठा regmap *map, पूर्णांक irq,
			       पूर्णांक irq_flags, पूर्णांक irq_base,
			       स्थिर काष्ठा regmap_irq_chip *chip,
			       काष्ठा regmap_irq_chip_data **data);
व्योम regmap_del_irq_chip(पूर्णांक irq, काष्ठा regmap_irq_chip_data *data);

पूर्णांक devm_regmap_add_irq_chip(काष्ठा device *dev, काष्ठा regmap *map, पूर्णांक irq,
			     पूर्णांक irq_flags, पूर्णांक irq_base,
			     स्थिर काष्ठा regmap_irq_chip *chip,
			     काष्ठा regmap_irq_chip_data **data);
पूर्णांक devm_regmap_add_irq_chip_fwnode(काष्ठा device *dev,
				    काष्ठा fwnode_handle *fwnode,
				    काष्ठा regmap *map, पूर्णांक irq,
				    पूर्णांक irq_flags, पूर्णांक irq_base,
				    स्थिर काष्ठा regmap_irq_chip *chip,
				    काष्ठा regmap_irq_chip_data **data);
व्योम devm_regmap_del_irq_chip(काष्ठा device *dev, पूर्णांक irq,
			      काष्ठा regmap_irq_chip_data *data);

पूर्णांक regmap_irq_chip_get_base(काष्ठा regmap_irq_chip_data *data);
पूर्णांक regmap_irq_get_virq(काष्ठा regmap_irq_chip_data *data, पूर्णांक irq);
काष्ठा irq_करोमुख्य *regmap_irq_get_करोमुख्य(काष्ठा regmap_irq_chip_data *data);

#अन्यथा

/*
 * These stubs should only ever be called by generic code which has
 * regmap based facilities, अगर they ever get called at runसमय
 * something is going wrong and something probably needs to select
 * REGMAP.
 */

अटल अंतरभूत पूर्णांक regmap_ग_लिखो(काष्ठा regmap *map, अचिन्हित पूर्णांक reg,
			       अचिन्हित पूर्णांक val)
अणु
	WARN_ONCE(1, "regmap API is disabled");
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत पूर्णांक regmap_ग_लिखो_async(काष्ठा regmap *map, अचिन्हित पूर्णांक reg,
				     अचिन्हित पूर्णांक val)
अणु
	WARN_ONCE(1, "regmap API is disabled");
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत पूर्णांक regmap_raw_ग_लिखो(काष्ठा regmap *map, अचिन्हित पूर्णांक reg,
				   स्थिर व्योम *val, माप_प्रकार val_len)
अणु
	WARN_ONCE(1, "regmap API is disabled");
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत पूर्णांक regmap_raw_ग_लिखो_async(काष्ठा regmap *map, अचिन्हित पूर्णांक reg,
					 स्थिर व्योम *val, माप_प्रकार val_len)
अणु
	WARN_ONCE(1, "regmap API is disabled");
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत पूर्णांक regmap_noinc_ग_लिखो(काष्ठा regmap *map, अचिन्हित पूर्णांक reg,
				    स्थिर व्योम *val, माप_प्रकार val_len)
अणु
	WARN_ONCE(1, "regmap API is disabled");
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत पूर्णांक regmap_bulk_ग_लिखो(काष्ठा regmap *map, अचिन्हित पूर्णांक reg,
				    स्थिर व्योम *val, माप_प्रकार val_count)
अणु
	WARN_ONCE(1, "regmap API is disabled");
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत पूर्णांक regmap_पढ़ो(काष्ठा regmap *map, अचिन्हित पूर्णांक reg,
			      अचिन्हित पूर्णांक *val)
अणु
	WARN_ONCE(1, "regmap API is disabled");
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत पूर्णांक regmap_raw_पढ़ो(काष्ठा regmap *map, अचिन्हित पूर्णांक reg,
				  व्योम *val, माप_प्रकार val_len)
अणु
	WARN_ONCE(1, "regmap API is disabled");
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत पूर्णांक regmap_noinc_पढ़ो(काष्ठा regmap *map, अचिन्हित पूर्णांक reg,
				    व्योम *val, माप_प्रकार val_len)
अणु
	WARN_ONCE(1, "regmap API is disabled");
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत पूर्णांक regmap_bulk_पढ़ो(काष्ठा regmap *map, अचिन्हित पूर्णांक reg,
				   व्योम *val, माप_प्रकार val_count)
अणु
	WARN_ONCE(1, "regmap API is disabled");
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत पूर्णांक regmap_update_bits_base(काष्ठा regmap *map, अचिन्हित पूर्णांक reg,
					  अचिन्हित पूर्णांक mask, अचिन्हित पूर्णांक val,
					  bool *change, bool async, bool क्रमce)
अणु
	WARN_ONCE(1, "regmap API is disabled");
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत पूर्णांक regmap_set_bits(काष्ठा regmap *map,
				  अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक bits)
अणु
	WARN_ONCE(1, "regmap API is disabled");
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत पूर्णांक regmap_clear_bits(काष्ठा regmap *map,
				    अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक bits)
अणु
	WARN_ONCE(1, "regmap API is disabled");
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत पूर्णांक regmap_test_bits(काष्ठा regmap *map,
				   अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक bits)
अणु
	WARN_ONCE(1, "regmap API is disabled");
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत पूर्णांक regmap_field_update_bits_base(काष्ठा regmap_field *field,
					अचिन्हित पूर्णांक mask, अचिन्हित पूर्णांक val,
					bool *change, bool async, bool क्रमce)
अणु
	WARN_ONCE(1, "regmap API is disabled");
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत पूर्णांक regmap_fields_update_bits_base(काष्ठा regmap_field *field,
				   अचिन्हित पूर्णांक id,
				   अचिन्हित पूर्णांक mask, अचिन्हित पूर्णांक val,
				   bool *change, bool async, bool क्रमce)
अणु
	WARN_ONCE(1, "regmap API is disabled");
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत पूर्णांक regmap_update_bits(काष्ठा regmap *map, अचिन्हित पूर्णांक reg,
				     अचिन्हित पूर्णांक mask, अचिन्हित पूर्णांक val)
अणु
	WARN_ONCE(1, "regmap API is disabled");
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत पूर्णांक regmap_update_bits_async(काष्ठा regmap *map, अचिन्हित पूर्णांक reg,
					   अचिन्हित पूर्णांक mask, अचिन्हित पूर्णांक val)
अणु
	WARN_ONCE(1, "regmap API is disabled");
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत पूर्णांक regmap_update_bits_check(काष्ठा regmap *map, अचिन्हित पूर्णांक reg,
					   अचिन्हित पूर्णांक mask, अचिन्हित पूर्णांक val,
					   bool *change)
अणु
	WARN_ONCE(1, "regmap API is disabled");
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत पूर्णांक
regmap_update_bits_check_async(काष्ठा regmap *map, अचिन्हित पूर्णांक reg,
			       अचिन्हित पूर्णांक mask, अचिन्हित पूर्णांक val,
			       bool *change)
अणु
	WARN_ONCE(1, "regmap API is disabled");
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत पूर्णांक regmap_ग_लिखो_bits(काष्ठा regmap *map, अचिन्हित पूर्णांक reg,
				    अचिन्हित पूर्णांक mask, अचिन्हित पूर्णांक val)
अणु
	WARN_ONCE(1, "regmap API is disabled");
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत पूर्णांक regmap_field_ग_लिखो(काष्ठा regmap_field *field,
				     अचिन्हित पूर्णांक val)
अणु
	WARN_ONCE(1, "regmap API is disabled");
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत पूर्णांक regmap_field_क्रमce_ग_लिखो(काष्ठा regmap_field *field,
					   अचिन्हित पूर्णांक val)
अणु
	WARN_ONCE(1, "regmap API is disabled");
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत पूर्णांक regmap_field_update_bits(काष्ठा regmap_field *field,
					   अचिन्हित पूर्णांक mask, अचिन्हित पूर्णांक val)
अणु
	WARN_ONCE(1, "regmap API is disabled");
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत पूर्णांक
regmap_field_क्रमce_update_bits(काष्ठा regmap_field *field,
			       अचिन्हित पूर्णांक mask, अचिन्हित पूर्णांक val)
अणु
	WARN_ONCE(1, "regmap API is disabled");
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत पूर्णांक regmap_fields_ग_लिखो(काष्ठा regmap_field *field,
				      अचिन्हित पूर्णांक id, अचिन्हित पूर्णांक val)
अणु
	WARN_ONCE(1, "regmap API is disabled");
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत पूर्णांक regmap_fields_क्रमce_ग_लिखो(काष्ठा regmap_field *field,
					    अचिन्हित पूर्णांक id, अचिन्हित पूर्णांक val)
अणु
	WARN_ONCE(1, "regmap API is disabled");
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत पूर्णांक
regmap_fields_update_bits(काष्ठा regmap_field *field, अचिन्हित पूर्णांक id,
			  अचिन्हित पूर्णांक mask, अचिन्हित पूर्णांक val)
अणु
	WARN_ONCE(1, "regmap API is disabled");
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत पूर्णांक
regmap_fields_क्रमce_update_bits(काष्ठा regmap_field *field, अचिन्हित पूर्णांक id,
				अचिन्हित पूर्णांक mask, अचिन्हित पूर्णांक val)
अणु
	WARN_ONCE(1, "regmap API is disabled");
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत पूर्णांक regmap_get_val_bytes(काष्ठा regmap *map)
अणु
	WARN_ONCE(1, "regmap API is disabled");
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत पूर्णांक regmap_get_max_रेजिस्टर(काष्ठा regmap *map)
अणु
	WARN_ONCE(1, "regmap API is disabled");
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत पूर्णांक regmap_get_reg_stride(काष्ठा regmap *map)
अणु
	WARN_ONCE(1, "regmap API is disabled");
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत पूर्णांक regcache_sync(काष्ठा regmap *map)
अणु
	WARN_ONCE(1, "regmap API is disabled");
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत पूर्णांक regcache_sync_region(काष्ठा regmap *map, अचिन्हित पूर्णांक min,
				       अचिन्हित पूर्णांक max)
अणु
	WARN_ONCE(1, "regmap API is disabled");
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत पूर्णांक regcache_drop_region(काष्ठा regmap *map, अचिन्हित पूर्णांक min,
				       अचिन्हित पूर्णांक max)
अणु
	WARN_ONCE(1, "regmap API is disabled");
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत व्योम regcache_cache_only(काष्ठा regmap *map, bool enable)
अणु
	WARN_ONCE(1, "regmap API is disabled");
पूर्ण

अटल अंतरभूत व्योम regcache_cache_bypass(काष्ठा regmap *map, bool enable)
अणु
	WARN_ONCE(1, "regmap API is disabled");
पूर्ण

अटल अंतरभूत व्योम regcache_mark_dirty(काष्ठा regmap *map)
अणु
	WARN_ONCE(1, "regmap API is disabled");
पूर्ण

अटल अंतरभूत व्योम regmap_async_complete(काष्ठा regmap *map)
अणु
	WARN_ONCE(1, "regmap API is disabled");
पूर्ण

अटल अंतरभूत पूर्णांक regmap_रेजिस्टर_patch(काष्ठा regmap *map,
					स्थिर काष्ठा reg_sequence *regs,
					पूर्णांक num_regs)
अणु
	WARN_ONCE(1, "regmap API is disabled");
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत पूर्णांक regmap_parse_val(काष्ठा regmap *map, स्थिर व्योम *buf,
				अचिन्हित पूर्णांक *val)
अणु
	WARN_ONCE(1, "regmap API is disabled");
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत काष्ठा regmap *dev_get_regmap(काष्ठा device *dev,
					    स्थिर अक्षर *name)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत काष्ठा device *regmap_get_device(काष्ठा regmap *map)
अणु
	WARN_ONCE(1, "regmap API is disabled");
	वापस शून्य;
पूर्ण

#पूर्ण_अगर

#पूर्ण_अगर
