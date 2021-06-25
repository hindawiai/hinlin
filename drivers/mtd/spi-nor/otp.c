<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * OTP support क्रम SPI NOR flashes
 *
 * Copyright (C) 2021 Michael Walle <michael@walle.cc>
 */

#समावेश <linux/log2.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/spi-nor.h>

#समावेश "core.h"

#घोषणा spi_nor_otp_region_len(nor) ((nor)->params->otp.org->len)
#घोषणा spi_nor_otp_n_regions(nor) ((nor)->params->otp.org->n_regions)

/**
 * spi_nor_otp_पढ़ो_secr() - पढ़ो OTP data
 * @nor:	poपूर्णांकer to 'struct spi_nor'
 * @from:       offset to पढ़ो from
 * @len:        number of bytes to पढ़ो
 * @buf:        poपूर्णांकer to dst buffer
 *
 * Read OTP data from one region by using the SPINOR_OP_RSECR commands. This
 * method is used on GigaDevice and Winbond flashes.
 *
 * Return: number of bytes पढ़ो successfully, -त्रुटि_सं otherwise
 */
पूर्णांक spi_nor_otp_पढ़ो_secr(काष्ठा spi_nor *nor, loff_t addr, माप_प्रकार len, u8 *buf)
अणु
	u8 addr_width, पढ़ो_opcode, पढ़ो_dummy;
	काष्ठा spi_mem_dirmap_desc *rdesc;
	क्रमागत spi_nor_protocol पढ़ो_proto;
	पूर्णांक ret;

	पढ़ो_opcode = nor->पढ़ो_opcode;
	addr_width = nor->addr_width;
	पढ़ो_dummy = nor->पढ़ो_dummy;
	पढ़ो_proto = nor->पढ़ो_proto;
	rdesc = nor->dirmap.rdesc;

	nor->पढ़ो_opcode = SPINOR_OP_RSECR;
	nor->addr_width = 3;
	nor->पढ़ो_dummy = 8;
	nor->पढ़ो_proto = SNOR_PROTO_1_1_1;
	nor->dirmap.rdesc = शून्य;

	ret = spi_nor_पढ़ो_data(nor, addr, len, buf);

	nor->पढ़ो_opcode = पढ़ो_opcode;
	nor->addr_width = addr_width;
	nor->पढ़ो_dummy = पढ़ो_dummy;
	nor->पढ़ो_proto = पढ़ो_proto;
	nor->dirmap.rdesc = rdesc;

	वापस ret;
पूर्ण

/**
 * spi_nor_otp_ग_लिखो_secr() - ग_लिखो OTP data
 * @nor:        poपूर्णांकer to 'struct spi_nor'
 * @to:         offset to ग_लिखो to
 * @len:        number of bytes to ग_लिखो
 * @buf:        poपूर्णांकer to src buffer
 *
 * Write OTP data to one region by using the SPINOR_OP_PSECR commands. This
 * method is used on GigaDevice and Winbond flashes.
 *
 * Please note, the ग_लिखो must not span multiple OTP regions.
 *
 * Return: number of bytes written successfully, -त्रुटि_सं otherwise
 */
पूर्णांक spi_nor_otp_ग_लिखो_secr(काष्ठा spi_nor *nor, loff_t addr, माप_प्रकार len,
			   स्थिर u8 *buf)
अणु
	क्रमागत spi_nor_protocol ग_लिखो_proto;
	काष्ठा spi_mem_dirmap_desc *wdesc;
	u8 addr_width, program_opcode;
	पूर्णांक ret, written;

	program_opcode = nor->program_opcode;
	addr_width = nor->addr_width;
	ग_लिखो_proto = nor->ग_लिखो_proto;
	wdesc = nor->dirmap.wdesc;

	nor->program_opcode = SPINOR_OP_PSECR;
	nor->addr_width = 3;
	nor->ग_लिखो_proto = SNOR_PROTO_1_1_1;
	nor->dirmap.wdesc = शून्य;

	/*
	 * We only support a ग_लिखो to one single page. For now all winbond
	 * flashes only have one page per OTP region.
	 */
	ret = spi_nor_ग_लिखो_enable(nor);
	अगर (ret)
		जाओ out;

	written = spi_nor_ग_लिखो_data(nor, addr, len, buf);
	अगर (written < 0)
		जाओ out;

	ret = spi_nor_रुको_till_पढ़ोy(nor);

out:
	nor->program_opcode = program_opcode;
	nor->addr_width = addr_width;
	nor->ग_लिखो_proto = ग_लिखो_proto;
	nor->dirmap.wdesc = wdesc;

	वापस ret ?: written;
पूर्ण

अटल पूर्णांक spi_nor_otp_lock_bit_cr(अचिन्हित पूर्णांक region)
अणु
	अटल स्थिर पूर्णांक lock_bits[] = अणु SR2_LB1, SR2_LB2, SR2_LB3 पूर्ण;

	अगर (region >= ARRAY_SIZE(lock_bits))
		वापस -EINVAL;

	वापस lock_bits[region];
पूर्ण

/**
 * spi_nor_otp_lock_sr2() - lock the OTP region
 * @nor:        poपूर्णांकer to 'struct spi_nor'
 * @region:     OTP region
 *
 * Lock the OTP region by writing the status रेजिस्टर-2. This method is used on
 * GigaDevice and Winbond flashes.
 *
 * Return: 0 on success, -त्रुटि_सं otherwise.
 */
पूर्णांक spi_nor_otp_lock_sr2(काष्ठा spi_nor *nor, अचिन्हित पूर्णांक region)
अणु
	u8 *cr = nor->bouncebuf;
	पूर्णांक ret, lock_bit;

	lock_bit = spi_nor_otp_lock_bit_cr(region);
	अगर (lock_bit < 0)
		वापस lock_bit;

	ret = spi_nor_पढ़ो_cr(nor, cr);
	अगर (ret)
		वापस ret;

	/* no need to ग_लिखो the रेजिस्टर अगर region is alपढ़ोy locked */
	अगर (cr[0] & lock_bit)
		वापस 0;

	cr[0] |= lock_bit;

	वापस spi_nor_ग_लिखो_16bit_cr_and_check(nor, cr[0]);
पूर्ण

/**
 * spi_nor_otp_is_locked_sr2() - get the OTP region lock status
 * @nor:        poपूर्णांकer to 'struct spi_nor'
 * @region:     OTP region
 *
 * Retrieve the OTP region lock bit by पढ़ोing the status रेजिस्टर-2. This
 * method is used on GigaDevice and Winbond flashes.
 *
 * Return: 0 on success, -त्रुटि_सं otherwise.
 */
पूर्णांक spi_nor_otp_is_locked_sr2(काष्ठा spi_nor *nor, अचिन्हित पूर्णांक region)
अणु
	u8 *cr = nor->bouncebuf;
	पूर्णांक ret, lock_bit;

	lock_bit = spi_nor_otp_lock_bit_cr(region);
	अगर (lock_bit < 0)
		वापस lock_bit;

	ret = spi_nor_पढ़ो_cr(nor, cr);
	अगर (ret)
		वापस ret;

	वापस cr[0] & lock_bit;
पूर्ण

अटल loff_t spi_nor_otp_region_start(स्थिर काष्ठा spi_nor *nor, अचिन्हित पूर्णांक region)
अणु
	स्थिर काष्ठा spi_nor_otp_organization *org = nor->params->otp.org;

	वापस org->base + region * org->offset;
पूर्ण

अटल माप_प्रकार spi_nor_otp_size(काष्ठा spi_nor *nor)
अणु
	वापस spi_nor_otp_n_regions(nor) * spi_nor_otp_region_len(nor);
पूर्ण

/* Translate the file offsets from and to OTP regions. */
अटल loff_t spi_nor_otp_region_to_offset(काष्ठा spi_nor *nor, अचिन्हित पूर्णांक region)
अणु
	वापस region * spi_nor_otp_region_len(nor);
पूर्ण

अटल अचिन्हित पूर्णांक spi_nor_otp_offset_to_region(काष्ठा spi_nor *nor, loff_t ofs)
अणु
	वापस भाग64_u64(ofs, spi_nor_otp_region_len(nor));
पूर्ण

अटल पूर्णांक spi_nor_mtd_otp_info(काष्ठा mtd_info *mtd, माप_प्रकार len,
				माप_प्रकार *retlen, काष्ठा otp_info *buf)
अणु
	काष्ठा spi_nor *nor = mtd_to_spi_nor(mtd);
	स्थिर काष्ठा spi_nor_otp_ops *ops = nor->params->otp.ops;
	अचिन्हित पूर्णांक n_regions = spi_nor_otp_n_regions(nor);
	अचिन्हित पूर्णांक i;
	पूर्णांक ret, locked;

	अगर (len < n_regions * माप(*buf))
		वापस -ENOSPC;

	ret = spi_nor_lock_and_prep(nor);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < n_regions; i++) अणु
		buf->start = spi_nor_otp_region_to_offset(nor, i);
		buf->length = spi_nor_otp_region_len(nor);

		locked = ops->is_locked(nor, i);
		अगर (locked < 0) अणु
			ret = locked;
			जाओ out;
		पूर्ण

		buf->locked = !!locked;
		buf++;
	पूर्ण

	*retlen = n_regions * माप(*buf);

out:
	spi_nor_unlock_and_unprep(nor);

	वापस ret;
पूर्ण

अटल पूर्णांक spi_nor_mtd_otp_पढ़ो_ग_लिखो(काष्ठा mtd_info *mtd, loff_t ofs,
				      माप_प्रकार total_len, माप_प्रकार *retlen,
				      स्थिर u8 *buf, bool is_ग_लिखो)
अणु
	काष्ठा spi_nor *nor = mtd_to_spi_nor(mtd);
	स्थिर काष्ठा spi_nor_otp_ops *ops = nor->params->otp.ops;
	स्थिर माप_प्रकार rlen = spi_nor_otp_region_len(nor);
	loff_t rstart, rofs;
	अचिन्हित पूर्णांक region;
	माप_प्रकार len;
	पूर्णांक ret;

	अगर (ofs < 0 || ofs >= spi_nor_otp_size(nor))
		वापस 0;

	ret = spi_nor_lock_and_prep(nor);
	अगर (ret)
		वापस ret;

	/* करोn't access beyond the end */
	total_len = min_t(माप_प्रकार, total_len, spi_nor_otp_size(nor) - ofs);

	*retlen = 0;
	जबतक (total_len) अणु
		/*
		 * The OTP regions are mapped पूर्णांकo a contiguous area starting
		 * at 0 as expected by the MTD layer. This will map the MTD
		 * file offsets to the address of an OTP region as used in the
		 * actual SPI commands.
		 */
		region = spi_nor_otp_offset_to_region(nor, ofs);
		rstart = spi_nor_otp_region_start(nor, region);

		/*
		 * The size of a OTP region is expected to be a घातer of two,
		 * thus we can just mask the lower bits and get the offset पूर्णांकo
		 * a region.
		 */
		rofs = ofs & (rlen - 1);

		/* करोn't access beyond one OTP region */
		len = min_t(माप_प्रकार, total_len, rlen - rofs);

		अगर (is_ग_लिखो)
			ret = ops->ग_लिखो(nor, rstart + rofs, len, buf);
		अन्यथा
			ret = ops->पढ़ो(nor, rstart + rofs, len, (u8 *)buf);
		अगर (ret == 0)
			ret = -EIO;
		अगर (ret < 0)
			जाओ out;

		*retlen += ret;
		ofs += ret;
		buf += ret;
		total_len -= ret;
	पूर्ण
	ret = 0;

out:
	spi_nor_unlock_and_unprep(nor);
	वापस ret;
पूर्ण

अटल पूर्णांक spi_nor_mtd_otp_पढ़ो(काष्ठा mtd_info *mtd, loff_t from, माप_प्रकार len,
				माप_प्रकार *retlen, u8 *buf)
अणु
	वापस spi_nor_mtd_otp_पढ़ो_ग_लिखो(mtd, from, len, retlen, buf, false);
पूर्ण

अटल पूर्णांक spi_nor_mtd_otp_ग_लिखो(काष्ठा mtd_info *mtd, loff_t to, माप_प्रकार len,
				 माप_प्रकार *retlen, स्थिर u8 *buf)
अणु
	वापस spi_nor_mtd_otp_पढ़ो_ग_लिखो(mtd, to, len, retlen, buf, true);
पूर्ण

अटल पूर्णांक spi_nor_mtd_otp_lock(काष्ठा mtd_info *mtd, loff_t from, माप_प्रकार len)
अणु
	काष्ठा spi_nor *nor = mtd_to_spi_nor(mtd);
	स्थिर काष्ठा spi_nor_otp_ops *ops = nor->params->otp.ops;
	स्थिर माप_प्रकार rlen = spi_nor_otp_region_len(nor);
	अचिन्हित पूर्णांक region;
	पूर्णांक ret;

	अगर (from < 0 || (from + len) > spi_nor_otp_size(nor))
		वापस -EINVAL;

	/* the user has to explicitly ask क्रम whole regions */
	अगर (!IS_ALIGNED(len, rlen) || !IS_ALIGNED(from, rlen))
		वापस -EINVAL;

	ret = spi_nor_lock_and_prep(nor);
	अगर (ret)
		वापस ret;

	जबतक (len) अणु
		region = spi_nor_otp_offset_to_region(nor, from);
		ret = ops->lock(nor, region);
		अगर (ret)
			जाओ out;

		len -= rlen;
		from += rlen;
	पूर्ण

out:
	spi_nor_unlock_and_unprep(nor);

	वापस ret;
पूर्ण

व्योम spi_nor_otp_init(काष्ठा spi_nor *nor)
अणु
	काष्ठा mtd_info *mtd = &nor->mtd;

	अगर (!nor->params->otp.ops)
		वापस;

	अगर (WARN_ON(!is_घातer_of_2(spi_nor_otp_region_len(nor))))
		वापस;

	/*
	 * We only support user_prot callbacks (yet).
	 *
	 * Some SPI NOR flashes like Macronix ones can be ordered in two
	 * dअगरferent variants. One with a factory locked OTP area and one where
	 * it is left to the user to ग_लिखो to it. The factory locked OTP is
	 * usually preprogrammed with an "electrical serial number". We करोn't
	 * support these क्रम now.
	 */
	mtd->_get_user_prot_info = spi_nor_mtd_otp_info;
	mtd->_पढ़ो_user_prot_reg = spi_nor_mtd_otp_पढ़ो;
	mtd->_ग_लिखो_user_prot_reg = spi_nor_mtd_otp_ग_लिखो;
	mtd->_lock_user_prot_reg = spi_nor_mtd_otp_lock;
पूर्ण
