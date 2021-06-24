<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2005, Intec Automation Inc.
 * Copyright (C) 2014, Freescale Semiconductor, Inc.
 */

#समावेश <linux/mtd/spi-nor.h>

#समावेश "core.h"

#घोषणा SST26VF_CR_BPNV		BIT(3)

अटल पूर्णांक sst26vf_lock(काष्ठा spi_nor *nor, loff_t ofs, uपूर्णांक64_t len)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक sst26vf_unlock(काष्ठा spi_nor *nor, loff_t ofs, uपूर्णांक64_t len)
अणु
	पूर्णांक ret;

	/* We only support unlocking the entire flash array. */
	अगर (ofs != 0 || len != nor->params->size)
		वापस -EINVAL;

	ret = spi_nor_पढ़ो_cr(nor, nor->bouncebuf);
	अगर (ret)
		वापस ret;

	अगर (!(nor->bouncebuf[0] & SST26VF_CR_BPNV)) अणु
		dev_dbg(nor->dev, "Any block has been permanently locked\n");
		वापस -EINVAL;
	पूर्ण

	वापस spi_nor_global_block_unlock(nor);
पूर्ण

अटल पूर्णांक sst26vf_is_locked(काष्ठा spi_nor *nor, loff_t ofs, uपूर्णांक64_t len)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल स्थिर काष्ठा spi_nor_locking_ops sst26vf_locking_ops = अणु
	.lock = sst26vf_lock,
	.unlock = sst26vf_unlock,
	.is_locked = sst26vf_is_locked,
पूर्ण;

अटल व्योम sst26vf_शेष_init(काष्ठा spi_nor *nor)
अणु
	nor->params->locking_ops = &sst26vf_locking_ops;
पूर्ण

अटल स्थिर काष्ठा spi_nor_fixups sst26vf_fixups = अणु
	.शेष_init = sst26vf_शेष_init,
पूर्ण;

अटल स्थिर काष्ठा flash_info sst_parts[] = अणु
	/* SST -- large erase sizes are "overlays", "sectors" are 4K */
	अणु "sst25vf040b", INFO(0xbf258d, 0, 64 * 1024,  8,
			      SECT_4K | SST_WRITE | SPI_NOR_HAS_LOCK | SPI_NOR_SWP_IS_VOLATILE) पूर्ण,
	अणु "sst25vf080b", INFO(0xbf258e, 0, 64 * 1024, 16,
			      SECT_4K | SST_WRITE | SPI_NOR_HAS_LOCK | SPI_NOR_SWP_IS_VOLATILE) पूर्ण,
	अणु "sst25vf016b", INFO(0xbf2541, 0, 64 * 1024, 32,
			      SECT_4K | SST_WRITE | SPI_NOR_HAS_LOCK | SPI_NOR_SWP_IS_VOLATILE) पूर्ण,
	अणु "sst25vf032b", INFO(0xbf254a, 0, 64 * 1024, 64,
			      SECT_4K | SST_WRITE | SPI_NOR_HAS_LOCK | SPI_NOR_SWP_IS_VOLATILE) पूर्ण,
	अणु "sst25vf064c", INFO(0xbf254b, 0, 64 * 1024, 128,
			      SECT_4K | SPI_NOR_4BIT_BP | SPI_NOR_HAS_LOCK |
			      SPI_NOR_SWP_IS_VOLATILE) पूर्ण,
	अणु "sst25wf512",  INFO(0xbf2501, 0, 64 * 1024,  1,
			      SECT_4K | SST_WRITE | SPI_NOR_HAS_LOCK | SPI_NOR_SWP_IS_VOLATILE) पूर्ण,
	अणु "sst25wf010",  INFO(0xbf2502, 0, 64 * 1024,  2,
			      SECT_4K | SST_WRITE | SPI_NOR_HAS_LOCK | SPI_NOR_SWP_IS_VOLATILE) पूर्ण,
	अणु "sst25wf020",  INFO(0xbf2503, 0, 64 * 1024,  4,
			      SECT_4K | SST_WRITE | SPI_NOR_HAS_LOCK | SPI_NOR_SWP_IS_VOLATILE) पूर्ण,
	अणु "sst25wf020a", INFO(0x621612, 0, 64 * 1024,  4, SECT_4K | SPI_NOR_HAS_LOCK) पूर्ण,
	अणु "sst25wf040b", INFO(0x621613, 0, 64 * 1024,  8, SECT_4K | SPI_NOR_HAS_LOCK) पूर्ण,
	अणु "sst25wf040",  INFO(0xbf2504, 0, 64 * 1024,  8,
			      SECT_4K | SST_WRITE | SPI_NOR_HAS_LOCK | SPI_NOR_SWP_IS_VOLATILE) पूर्ण,
	अणु "sst25wf080",  INFO(0xbf2505, 0, 64 * 1024, 16,
			      SECT_4K | SST_WRITE | SPI_NOR_HAS_LOCK | SPI_NOR_SWP_IS_VOLATILE) पूर्ण,
	अणु "sst26wf016b", INFO(0xbf2651, 0, 64 * 1024, 32,
			      SECT_4K | SPI_NOR_DUAL_READ |
			      SPI_NOR_QUAD_READ) पूर्ण,
	अणु "sst26vf016b", INFO(0xbf2641, 0, 64 * 1024, 32,
			      SECT_4K | SPI_NOR_DUAL_READ) पूर्ण,
	अणु "sst26vf064b", INFO(0xbf2643, 0, 64 * 1024, 128,
			      SECT_4K | SPI_NOR_DUAL_READ | SPI_NOR_QUAD_READ |
			      SPI_NOR_HAS_LOCK | SPI_NOR_SWP_IS_VOLATILE)
		.fixups = &sst26vf_fixups पूर्ण,
पूर्ण;

अटल पूर्णांक sst_ग_लिखो(काष्ठा mtd_info *mtd, loff_t to, माप_प्रकार len,
		     माप_प्रकार *retlen, स्थिर u_अक्षर *buf)
अणु
	काष्ठा spi_nor *nor = mtd_to_spi_nor(mtd);
	माप_प्रकार actual = 0;
	पूर्णांक ret;

	dev_dbg(nor->dev, "to 0x%08x, len %zd\n", (u32)to, len);

	ret = spi_nor_lock_and_prep(nor);
	अगर (ret)
		वापस ret;

	ret = spi_nor_ग_लिखो_enable(nor);
	अगर (ret)
		जाओ out;

	nor->sst_ग_लिखो_second = false;

	/* Start ग_लिखो from odd address. */
	अगर (to % 2) अणु
		nor->program_opcode = SPINOR_OP_BP;

		/* ग_लिखो one byte. */
		ret = spi_nor_ग_लिखो_data(nor, to, 1, buf);
		अगर (ret < 0)
			जाओ out;
		WARN(ret != 1, "While writing 1 byte written %i bytes\n", ret);
		ret = spi_nor_रुको_till_पढ़ोy(nor);
		अगर (ret)
			जाओ out;

		to++;
		actual++;
	पूर्ण

	/* Write out most of the data here. */
	क्रम (; actual < len - 1; actual += 2) अणु
		nor->program_opcode = SPINOR_OP_AAI_WP;

		/* ग_लिखो two bytes. */
		ret = spi_nor_ग_लिखो_data(nor, to, 2, buf + actual);
		अगर (ret < 0)
			जाओ out;
		WARN(ret != 2, "While writing 2 bytes written %i bytes\n", ret);
		ret = spi_nor_रुको_till_पढ़ोy(nor);
		अगर (ret)
			जाओ out;
		to += 2;
		nor->sst_ग_लिखो_second = true;
	पूर्ण
	nor->sst_ग_लिखो_second = false;

	ret = spi_nor_ग_लिखो_disable(nor);
	अगर (ret)
		जाओ out;

	ret = spi_nor_रुको_till_पढ़ोy(nor);
	अगर (ret)
		जाओ out;

	/* Write out trailing byte अगर it exists. */
	अगर (actual != len) अणु
		ret = spi_nor_ग_लिखो_enable(nor);
		अगर (ret)
			जाओ out;

		nor->program_opcode = SPINOR_OP_BP;
		ret = spi_nor_ग_लिखो_data(nor, to, 1, buf + actual);
		अगर (ret < 0)
			जाओ out;
		WARN(ret != 1, "While writing 1 byte written %i bytes\n", ret);
		ret = spi_nor_रुको_till_पढ़ोy(nor);
		अगर (ret)
			जाओ out;

		actual += 1;

		ret = spi_nor_ग_लिखो_disable(nor);
	पूर्ण
out:
	*retlen += actual;
	spi_nor_unlock_and_unprep(nor);
	वापस ret;
पूर्ण

अटल व्योम sst_post_sfdp_fixups(काष्ठा spi_nor *nor)
अणु
	अगर (nor->info->flags & SST_WRITE)
		nor->mtd._ग_लिखो = sst_ग_लिखो;
पूर्ण

अटल स्थिर काष्ठा spi_nor_fixups sst_fixups = अणु
	.post_sfdp = sst_post_sfdp_fixups,
पूर्ण;

स्थिर काष्ठा spi_nor_manufacturer spi_nor_sst = अणु
	.name = "sst",
	.parts = sst_parts,
	.nparts = ARRAY_SIZE(sst_parts),
	.fixups = &sst_fixups,
पूर्ण;
