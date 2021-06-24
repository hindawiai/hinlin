<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  linux/drivers/mmc/sdio_ops.c
 *
 *  Copyright 2006-2007 Pierre Ossman
 */

#समावेश <linux/scatterlist.h>

#समावेश <linux/mmc/host.h>
#समावेश <linux/mmc/card.h>
#समावेश <linux/mmc/mmc.h>
#समावेश <linux/mmc/sdपन.स>

#समावेश "core.h"
#समावेश "sdio_ops.h"

पूर्णांक mmc_send_io_op_cond(काष्ठा mmc_host *host, u32 ocr, u32 *rocr)
अणु
	काष्ठा mmc_command cmd = अणुपूर्ण;
	पूर्णांक i, err = 0;

	cmd.opcode = SD_IO_SEND_OP_COND;
	cmd.arg = ocr;
	cmd.flags = MMC_RSP_SPI_R4 | MMC_RSP_R4 | MMC_CMD_BCR;

	क्रम (i = 100; i; i--) अणु
		err = mmc_रुको_क्रम_cmd(host, &cmd, MMC_CMD_RETRIES);
		अगर (err)
			अवरोध;

		/* अगर we're just probing, करो a single pass */
		अगर (ocr == 0)
			अवरोध;

		/* otherwise रुको until reset completes */
		अगर (mmc_host_is_spi(host)) अणु
			/*
			 * Both R1_SPI_IDLE and MMC_CARD_BUSY indicate
			 * an initialized card under SPI, but some cards
			 * (Marvell's) only behave when looking at this
			 * one.
			 */
			अगर (cmd.resp[1] & MMC_CARD_BUSY)
				अवरोध;
		पूर्ण अन्यथा अणु
			अगर (cmd.resp[0] & MMC_CARD_BUSY)
				अवरोध;
		पूर्ण

		err = -ETIMEDOUT;

		mmc_delay(10);
	पूर्ण

	अगर (rocr)
		*rocr = cmd.resp[mmc_host_is_spi(host) ? 1 : 0];

	वापस err;
पूर्ण

अटल पूर्णांक mmc_io_rw_direct_host(काष्ठा mmc_host *host, पूर्णांक ग_लिखो, अचिन्हित fn,
	अचिन्हित addr, u8 in, u8 *out)
अणु
	काष्ठा mmc_command cmd = अणुपूर्ण;
	पूर्णांक err;

	अगर (fn > 7)
		वापस -EINVAL;

	/* sanity check */
	अगर (addr & ~0x1FFFF)
		वापस -EINVAL;

	cmd.opcode = SD_IO_RW_सूचीECT;
	cmd.arg = ग_लिखो ? 0x80000000 : 0x00000000;
	cmd.arg |= fn << 28;
	cmd.arg |= (ग_लिखो && out) ? 0x08000000 : 0x00000000;
	cmd.arg |= addr << 9;
	cmd.arg |= in;
	cmd.flags = MMC_RSP_SPI_R5 | MMC_RSP_R5 | MMC_CMD_AC;

	err = mmc_रुको_क्रम_cmd(host, &cmd, 0);
	अगर (err)
		वापस err;

	अगर (mmc_host_is_spi(host)) अणु
		/* host driver alपढ़ोy reported errors */
	पूर्ण अन्यथा अणु
		अगर (cmd.resp[0] & R5_ERROR)
			वापस -EIO;
		अगर (cmd.resp[0] & R5_FUNCTION_NUMBER)
			वापस -EINVAL;
		अगर (cmd.resp[0] & R5_OUT_OF_RANGE)
			वापस -दुस्फल;
	पूर्ण

	अगर (out) अणु
		अगर (mmc_host_is_spi(host))
			*out = (cmd.resp[0] >> 8) & 0xFF;
		अन्यथा
			*out = cmd.resp[0] & 0xFF;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक mmc_io_rw_direct(काष्ठा mmc_card *card, पूर्णांक ग_लिखो, अचिन्हित fn,
	अचिन्हित addr, u8 in, u8 *out)
अणु
	वापस mmc_io_rw_direct_host(card->host, ग_लिखो, fn, addr, in, out);
पूर्ण

पूर्णांक mmc_io_rw_extended(काष्ठा mmc_card *card, पूर्णांक ग_लिखो, अचिन्हित fn,
	अचिन्हित addr, पूर्णांक incr_addr, u8 *buf, अचिन्हित blocks, अचिन्हित blksz)
अणु
	काष्ठा mmc_request mrq = अणुपूर्ण;
	काष्ठा mmc_command cmd = अणुपूर्ण;
	काष्ठा mmc_data data = अणुपूर्ण;
	काष्ठा scatterlist sg, *sg_ptr;
	काष्ठा sg_table sgtable;
	अचिन्हित पूर्णांक nents, left_size, i;
	अचिन्हित पूर्णांक seg_size = card->host->max_seg_size;
	पूर्णांक err;

	WARN_ON(blksz == 0);

	/* sanity check */
	अगर (addr & ~0x1FFFF)
		वापस -EINVAL;

	mrq.cmd = &cmd;
	mrq.data = &data;

	cmd.opcode = SD_IO_RW_EXTENDED;
	cmd.arg = ग_लिखो ? 0x80000000 : 0x00000000;
	cmd.arg |= fn << 28;
	cmd.arg |= incr_addr ? 0x04000000 : 0x00000000;
	cmd.arg |= addr << 9;
	अगर (blocks == 0)
		cmd.arg |= (blksz == 512) ? 0 : blksz;	/* byte mode */
	अन्यथा
		cmd.arg |= 0x08000000 | blocks;		/* block mode */
	cmd.flags = MMC_RSP_SPI_R5 | MMC_RSP_R5 | MMC_CMD_ADTC;

	data.blksz = blksz;
	/* Code in host drivers/fwk assumes that "blocks" always is >=1 */
	data.blocks = blocks ? blocks : 1;
	data.flags = ग_लिखो ? MMC_DATA_WRITE : MMC_DATA_READ;

	left_size = data.blksz * data.blocks;
	nents = DIV_ROUND_UP(left_size, seg_size);
	अगर (nents > 1) अणु
		अगर (sg_alloc_table(&sgtable, nents, GFP_KERNEL))
			वापस -ENOMEM;

		data.sg = sgtable.sgl;
		data.sg_len = nents;

		क्रम_each_sg(data.sg, sg_ptr, data.sg_len, i) अणु
			sg_set_buf(sg_ptr, buf + i * seg_size,
				   min(seg_size, left_size));
			left_size -= seg_size;
		पूर्ण
	पूर्ण अन्यथा अणु
		data.sg = &sg;
		data.sg_len = 1;

		sg_init_one(&sg, buf, left_size);
	पूर्ण

	mmc_set_data_समयout(&data, card);

	mmc_pre_req(card->host, &mrq);

	mmc_रुको_क्रम_req(card->host, &mrq);

	अगर (cmd.error)
		err = cmd.error;
	अन्यथा अगर (data.error)
		err = data.error;
	अन्यथा अगर (mmc_host_is_spi(card->host))
		/* host driver alपढ़ोy reported errors */
		err = 0;
	अन्यथा अगर (cmd.resp[0] & R5_ERROR)
		err = -EIO;
	अन्यथा अगर (cmd.resp[0] & R5_FUNCTION_NUMBER)
		err = -EINVAL;
	अन्यथा अगर (cmd.resp[0] & R5_OUT_OF_RANGE)
		err = -दुस्फल;
	अन्यथा
		err = 0;

	mmc_post_req(card->host, &mrq, err);

	अगर (nents > 1)
		sg_मुक्त_table(&sgtable);

	वापस err;
पूर्ण

पूर्णांक sdio_reset(काष्ठा mmc_host *host)
अणु
	पूर्णांक ret;
	u8 पात;

	/* SDIO Simplअगरied Specअगरication V2.0, 4.4 Reset क्रम SDIO */

	ret = mmc_io_rw_direct_host(host, 0, 0, SDIO_CCCR_ABORT, 0, &पात);
	अगर (ret)
		पात = 0x08;
	अन्यथा
		पात |= 0x08;

	वापस mmc_io_rw_direct_host(host, 1, 0, SDIO_CCCR_ABORT, पात, शून्य);
पूर्ण

