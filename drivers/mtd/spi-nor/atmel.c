<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2005, Intec Automation Inc.
 * Copyright (C) 2014, Freescale Semiconductor, Inc.
 */

#समावेश <linux/mtd/spi-nor.h>

#समावेश "core.h"

#घोषणा ATMEL_SR_GLOBAL_PROTECT_MASK GENMASK(5, 2)

/*
 * The Aपंचांगel AT25FS010/AT25FS040 parts have some weird configuration क्रम the
 * block protection bits. We करोn't support them. But legacy behavior in linux
 * is to unlock the whole flash array on startup. Thereक्रमe, we have to support
 * exactly this operation.
 */
अटल पूर्णांक aपंचांगel_at25fs_lock(काष्ठा spi_nor *nor, loff_t ofs, uपूर्णांक64_t len)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक aपंचांगel_at25fs_unlock(काष्ठा spi_nor *nor, loff_t ofs, uपूर्णांक64_t len)
अणु
	पूर्णांक ret;

	/* We only support unlocking the whole flash array */
	अगर (ofs || len != nor->params->size)
		वापस -EINVAL;

	/* Write 0x00 to the status रेजिस्टर to disable ग_लिखो protection */
	ret = spi_nor_ग_लिखो_sr_and_check(nor, 0);
	अगर (ret)
		dev_dbg(nor->dev, "unable to clear BP bits, WP# asserted?\n");

	वापस ret;
पूर्ण

अटल पूर्णांक aपंचांगel_at25fs_is_locked(काष्ठा spi_nor *nor, loff_t ofs, uपूर्णांक64_t len)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल स्थिर काष्ठा spi_nor_locking_ops aपंचांगel_at25fs_locking_ops = अणु
	.lock = aपंचांगel_at25fs_lock,
	.unlock = aपंचांगel_at25fs_unlock,
	.is_locked = aपंचांगel_at25fs_is_locked,
पूर्ण;

अटल व्योम aपंचांगel_at25fs_शेष_init(काष्ठा spi_nor *nor)
अणु
	nor->params->locking_ops = &aपंचांगel_at25fs_locking_ops;
पूर्ण

अटल स्थिर काष्ठा spi_nor_fixups aपंचांगel_at25fs_fixups = अणु
	.शेष_init = aपंचांगel_at25fs_शेष_init,
पूर्ण;

/**
 * aपंचांगel_set_global_protection - Do a Global Protect or Unprotect command
 * @nor:	poपूर्णांकer to 'struct spi_nor'
 * @ofs:	offset in bytes
 * @len:	len in bytes
 * @is_protect:	अगर true करो a Global Protect otherwise it is a Global Unprotect
 *
 * Return: 0 on success, -error otherwise.
 */
अटल पूर्णांक aपंचांगel_set_global_protection(काष्ठा spi_nor *nor, loff_t ofs,
				       uपूर्णांक64_t len, bool is_protect)
अणु
	पूर्णांक ret;
	u8 sr;

	/* We only support locking the whole flash array */
	अगर (ofs || len != nor->params->size)
		वापस -EINVAL;

	ret = spi_nor_पढ़ो_sr(nor, nor->bouncebuf);
	अगर (ret)
		वापस ret;

	sr = nor->bouncebuf[0];

	/* SRWD bit needs to be cleared, otherwise the protection करोesn't change */
	अगर (sr & SR_SRWD) अणु
		sr &= ~SR_SRWD;
		ret = spi_nor_ग_लिखो_sr_and_check(nor, sr);
		अगर (ret) अणु
			dev_dbg(nor->dev, "unable to clear SRWD bit, WP# asserted?\n");
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (is_protect) अणु
		sr |= ATMEL_SR_GLOBAL_PROTECT_MASK;
		/*
		 * Set the SRWD bit again as soon as we are protecting
		 * anything. This will ensure that the WP# pin is working
		 * correctly. By करोing this we also behave the same as
		 * spi_nor_sr_lock(), which sets SRWD अगर any block protection
		 * is active.
		 */
		sr |= SR_SRWD;
	पूर्ण अन्यथा अणु
		sr &= ~ATMEL_SR_GLOBAL_PROTECT_MASK;
	पूर्ण

	nor->bouncebuf[0] = sr;

	/*
	 * We cannot use the spi_nor_ग_लिखो_sr_and_check() because this command
	 * isn't really setting any bits, instead it is an pseuकरो command क्रम
	 * "Global Unprotect" or "Global Protect"
	 */
	वापस spi_nor_ग_लिखो_sr(nor, nor->bouncebuf, 1);
पूर्ण

अटल पूर्णांक aपंचांगel_global_protect(काष्ठा spi_nor *nor, loff_t ofs, uपूर्णांक64_t len)
अणु
	वापस aपंचांगel_set_global_protection(nor, ofs, len, true);
पूर्ण

अटल पूर्णांक aपंचांगel_global_unprotect(काष्ठा spi_nor *nor, loff_t ofs, uपूर्णांक64_t len)
अणु
	वापस aपंचांगel_set_global_protection(nor, ofs, len, false);
पूर्ण

अटल पूर्णांक aपंचांगel_is_global_रक्षित(काष्ठा spi_nor *nor, loff_t ofs, uपूर्णांक64_t len)
अणु
	पूर्णांक ret;

	अगर (ofs >= nor->params->size || (ofs + len) > nor->params->size)
		वापस -EINVAL;

	ret = spi_nor_पढ़ो_sr(nor, nor->bouncebuf);
	अगर (ret)
		वापस ret;

	वापस ((nor->bouncebuf[0] & ATMEL_SR_GLOBAL_PROTECT_MASK) == ATMEL_SR_GLOBAL_PROTECT_MASK);
पूर्ण

अटल स्थिर काष्ठा spi_nor_locking_ops aपंचांगel_global_protection_ops = अणु
	.lock = aपंचांगel_global_protect,
	.unlock = aपंचांगel_global_unprotect,
	.is_locked = aपंचांगel_is_global_रक्षित,
पूर्ण;

अटल व्योम aपंचांगel_global_protection_शेष_init(काष्ठा spi_nor *nor)
अणु
	nor->params->locking_ops = &aपंचांगel_global_protection_ops;
पूर्ण

अटल स्थिर काष्ठा spi_nor_fixups aपंचांगel_global_protection_fixups = अणु
	.शेष_init = aपंचांगel_global_protection_शेष_init,
पूर्ण;

अटल स्थिर काष्ठा flash_info aपंचांगel_parts[] = अणु
	/* Aपंचांगel -- some are (confusingly) marketed as "DataFlash" */
	अणु "at25fs010",  INFO(0x1f6601, 0, 32 * 1024,   4, SECT_4K | SPI_NOR_HAS_LOCK)
		.fixups = &aपंचांगel_at25fs_fixups पूर्ण,
	अणु "at25fs040",  INFO(0x1f6604, 0, 64 * 1024,   8, SECT_4K | SPI_NOR_HAS_LOCK)
		.fixups = &aपंचांगel_at25fs_fixups पूर्ण,

	अणु "at25df041a", INFO(0x1f4401, 0, 64 * 1024,   8,
			     SECT_4K | SPI_NOR_HAS_LOCK | SPI_NOR_SWP_IS_VOLATILE)
			.fixups = &aपंचांगel_global_protection_fixups पूर्ण,
	अणु "at25df321",  INFO(0x1f4700, 0, 64 * 1024,  64,
			     SECT_4K | SPI_NOR_HAS_LOCK | SPI_NOR_SWP_IS_VOLATILE)
			.fixups = &aपंचांगel_global_protection_fixups पूर्ण,
	अणु "at25df321a", INFO(0x1f4701, 0, 64 * 1024,  64,
			     SECT_4K | SPI_NOR_HAS_LOCK | SPI_NOR_SWP_IS_VOLATILE)
			.fixups = &aपंचांगel_global_protection_fixups पूर्ण,
	अणु "at25df641",  INFO(0x1f4800, 0, 64 * 1024, 128,
			     SECT_4K | SPI_NOR_HAS_LOCK | SPI_NOR_SWP_IS_VOLATILE)
			.fixups = &aपंचांगel_global_protection_fixups पूर्ण,

	अणु "at25sl321",	INFO(0x1f4216, 0, 64 * 1024, 64,
			     SECT_4K | SPI_NOR_DUAL_READ | SPI_NOR_QUAD_READ) पूर्ण,

	अणु "at26f004",   INFO(0x1f0400, 0, 64 * 1024,  8, SECT_4K) पूर्ण,
	अणु "at26df081a", INFO(0x1f4501, 0, 64 * 1024, 16,
			     SECT_4K | SPI_NOR_HAS_LOCK | SPI_NOR_SWP_IS_VOLATILE)
			.fixups = &aपंचांगel_global_protection_fixups पूर्ण,
	अणु "at26df161a", INFO(0x1f4601, 0, 64 * 1024, 32,
			     SECT_4K | SPI_NOR_HAS_LOCK | SPI_NOR_SWP_IS_VOLATILE)
			.fixups = &aपंचांगel_global_protection_fixups पूर्ण,
	अणु "at26df321",  INFO(0x1f4700, 0, 64 * 1024, 64,
			     SECT_4K | SPI_NOR_HAS_LOCK | SPI_NOR_SWP_IS_VOLATILE)
			.fixups = &aपंचांगel_global_protection_fixups पूर्ण,

	अणु "at45db081d", INFO(0x1f2500, 0, 64 * 1024, 16, SECT_4K) पूर्ण,
पूर्ण;

स्थिर काष्ठा spi_nor_manufacturer spi_nor_aपंचांगel = अणु
	.name = "atmel",
	.parts = aपंचांगel_parts,
	.nparts = ARRAY_SIZE(aपंचांगel_parts),
पूर्ण;
