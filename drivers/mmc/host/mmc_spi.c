<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Access SD/MMC cards through SPI master controllers
 *
 * (C) Copyright 2005, Intec Automation,
 *		Mike Lavender (mike@steroidmicros)
 * (C) Copyright 2006-2007, David Brownell
 * (C) Copyright 2007, Axis Communications,
 *		Hans-Peter Nilsson (hp@axis.com)
 * (C) Copyright 2007, ATRON electronic GmbH,
 *		Jan Nikitenko <jan.nikitenko@gmail.com>
 */
#समावेश <linux/sched.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/bपन.स>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/crc7.h>
#समावेश <linux/crc-itu-t.h>
#समावेश <linux/scatterlist.h>

#समावेश <linux/mmc/host.h>
#समावेश <linux/mmc/mmc.h>		/* क्रम R1_SPI_* bit values */
#समावेश <linux/mmc/slot-gpपन.स>

#समावेश <linux/spi/spi.h>
#समावेश <linux/spi/mmc_spi.h>

#समावेश <यंत्र/unaligned.h>


/* NOTES:
 *
 * - For now, we won't try to पूर्णांकeroperate with a real mmc/sd/sdio
 *   controller, although some of them करो have hardware support क्रम
 *   SPI protocol.  The मुख्य reason क्रम such configs would be mmc-ish
 *   cards like DataFlash, which करोn't support that "native" protocol.
 *
 *   We करोn't have a "DataFlash/MMC/SD/SDIO card slot" असलtraction to
 *   चयन between driver stacks, and in any हाल अगर "native" mode
 *   is available, it will be faster and hence preferable.
 *
 * - MMC depends on a dअगरferent chipselect management policy than the
 *   SPI पूर्णांकerface currently supports क्रम shared bus segments:  it needs
 *   to issue multiple spi_message requests with the chipselect active,
 *   using the results of one message to decide the next one to issue.
 *
 *   Pending updates to the programming पूर्णांकerface, this driver expects
 *   that it not share the bus with other drivers (precluding conflicts).
 *
 * - We tell the controller to keep the chipselect active from the
 *   beginning of an mmc_host_ops.request until the end.  So beware
 *   of SPI controller drivers that mis-handle the cs_change flag!
 *
 *   However, many cards seem OK with chipselect flapping up/करोwn
 *   during that समय ... at least on unshared bus segments.
 */


/*
 * Local protocol स्थिरants, पूर्णांकernal to data block protocols.
 */

/* Response tokens used to ack each block written: */
#घोषणा SPI_MMC_RESPONSE_CODE(x)	((x) & 0x1f)
#घोषणा SPI_RESPONSE_ACCEPTED		((2 << 1)|1)
#घोषणा SPI_RESPONSE_CRC_ERR		((5 << 1)|1)
#घोषणा SPI_RESPONSE_WRITE_ERR		((6 << 1)|1)

/* Read and ग_लिखो blocks start with these tokens and end with crc;
 * on error, पढ़ो tokens act like a subset of R2_SPI_* values.
 */
#घोषणा SPI_TOKEN_SINGLE	0xfe	/* single block r/w, multiblock पढ़ो */
#घोषणा SPI_TOKEN_MULTI_WRITE	0xfc	/* multiblock ग_लिखो */
#घोषणा SPI_TOKEN_STOP_TRAN	0xfd	/* terminate multiblock ग_लिखो */

#घोषणा MMC_SPI_BLOCKSIZE	512

#घोषणा MMC_SPI_R1B_TIMEOUT_MS	3000
#घोषणा MMC_SPI_INIT_TIMEOUT_MS	3000

/* One of the critical speed parameters is the amount of data which may
 * be transferred in one command. If this value is too low, the SD card
 * controller has to करो multiple partial block ग_लिखोs (argggh!). With
 * today (2008) SD cards there is little speed gain अगर we transfer more
 * than 64 KBytes at a समय. So use this value until there is any indication
 * that we should करो more here.
 */
#घोषणा MMC_SPI_BLOCKSATONCE	128

/****************************************************************************/

/*
 * Local Data Structures
 */

/* "scratch" is per-अणुcommand,blockपूर्ण data exchanged with the card */
काष्ठा scratch अणु
	u8			status[29];
	u8			data_token;
	__be16			crc_val;
पूर्ण;

काष्ठा mmc_spi_host अणु
	काष्ठा mmc_host		*mmc;
	काष्ठा spi_device	*spi;

	अचिन्हित अक्षर		घातer_mode;
	u16			घातerup_msecs;

	काष्ठा mmc_spi_platक्रमm_data	*pdata;

	/* क्रम bulk data transfers */
	काष्ठा spi_transfer	token, t, crc, early_status;
	काष्ठा spi_message	m;

	/* क्रम status पढ़ोback */
	काष्ठा spi_transfer	status;
	काष्ठा spi_message	पढ़ोback;

	/* underlying DMA-aware controller, or null */
	काष्ठा device		*dma_dev;

	/* buffer used क्रम commands and क्रम message "overhead" */
	काष्ठा scratch		*data;
	dma_addr_t		data_dma;

	/* Specs say to ग_लिखो ones most of the समय, even when the card
	 * has no need to पढ़ो its input data; and many cards won't care.
	 * This is our source of those ones.
	 */
	व्योम			*ones;
	dma_addr_t		ones_dma;
पूर्ण;


/****************************************************************************/

/*
 * MMC-over-SPI protocol glue, used by the MMC stack पूर्णांकerface
 */

अटल अंतरभूत पूर्णांक mmc_cs_off(काष्ठा mmc_spi_host *host)
अणु
	/* chipselect will always be inactive after setup() */
	वापस spi_setup(host->spi);
पूर्ण

अटल पूर्णांक
mmc_spi_पढ़ोbytes(काष्ठा mmc_spi_host *host, अचिन्हित len)
अणु
	पूर्णांक status;

	अगर (len > माप(*host->data)) अणु
		WARN_ON(1);
		वापस -EIO;
	पूर्ण

	host->status.len = len;

	अगर (host->dma_dev)
		dma_sync_single_क्रम_device(host->dma_dev,
				host->data_dma, माप(*host->data),
				DMA_FROM_DEVICE);

	status = spi_sync_locked(host->spi, &host->पढ़ोback);

	अगर (host->dma_dev)
		dma_sync_single_क्रम_cpu(host->dma_dev,
				host->data_dma, माप(*host->data),
				DMA_FROM_DEVICE);

	वापस status;
पूर्ण

अटल पूर्णांक mmc_spi_skip(काष्ठा mmc_spi_host *host, अचिन्हित दीर्घ समयout,
			अचिन्हित n, u8 byte)
अणु
	u8 *cp = host->data->status;
	अचिन्हित दीर्घ start = jअगरfies;

	जबतक (1) अणु
		पूर्णांक		status;
		अचिन्हित	i;

		status = mmc_spi_पढ़ोbytes(host, n);
		अगर (status < 0)
			वापस status;

		क्रम (i = 0; i < n; i++) अणु
			अगर (cp[i] != byte)
				वापस cp[i];
		पूर्ण

		अगर (समय_is_beक्रमe_jअगरfies(start + समयout))
			अवरोध;

		/* If we need दीर्घ समयouts, we may release the CPU.
		 * We use jअगरfies here because we want to have a relation
		 * between elapsed समय and the blocking of the scheduler.
		 */
		अगर (समय_is_beक्रमe_jअगरfies(start + 1))
			schedule();
	पूर्ण
	वापस -ETIMEDOUT;
पूर्ण

अटल अंतरभूत पूर्णांक
mmc_spi_रुको_unbusy(काष्ठा mmc_spi_host *host, अचिन्हित दीर्घ समयout)
अणु
	वापस mmc_spi_skip(host, समयout, माप(host->data->status), 0);
पूर्ण

अटल पूर्णांक mmc_spi_पढ़ोtoken(काष्ठा mmc_spi_host *host, अचिन्हित दीर्घ समयout)
अणु
	वापस mmc_spi_skip(host, समयout, 1, 0xff);
पूर्ण


/*
 * Note that क्रम SPI, cmd->resp[0] is not the same data as "native" protocol
 * hosts वापस!  The low byte holds R1_SPI bits.  The next byte may hold
 * R2_SPI bits ... क्रम SEND_STATUS, or after data पढ़ो errors.
 *
 * cmd->resp[1] holds any four-byte response, क्रम R3 (READ_OCR) and on
 * newer cards R7 (IF_COND).
 */

अटल अक्षर *maptype(काष्ठा mmc_command *cmd)
अणु
	चयन (mmc_spi_resp_type(cmd)) अणु
	हाल MMC_RSP_SPI_R1:	वापस "R1";
	हाल MMC_RSP_SPI_R1B:	वापस "R1B";
	हाल MMC_RSP_SPI_R2:	वापस "R2/R5";
	हाल MMC_RSP_SPI_R3:	वापस "R3/R4/R7";
	शेष:		वापस "?";
	पूर्ण
पूर्ण

/* वापस zero, अन्यथा negative त्रुटि_सं after setting cmd->error */
अटल पूर्णांक mmc_spi_response_get(काष्ठा mmc_spi_host *host,
		काष्ठा mmc_command *cmd, पूर्णांक cs_on)
अणु
	अचिन्हित दीर्घ समयout_ms;
	u8	*cp = host->data->status;
	u8	*end = cp + host->t.len;
	पूर्णांक	value = 0;
	पूर्णांक	bitshअगरt;
	u8 	leftover = 0;
	अचिन्हित लघु rotator;
	पूर्णांक 	i;
	अक्षर	tag[32];

	snम_लिखो(tag, माप(tag), "  ... CMD%d response SPI_%s",
		cmd->opcode, maptype(cmd));

	/* Except क्रम data block पढ़ोs, the whole response will alपढ़ोy
	 * be stored in the scratch buffer.  It's somewhere after the
	 * command and the first byte we पढ़ो after it.  We ignore that
	 * first byte.  After STOP_TRANSMISSION command it may include
	 * two data bits, but otherwise it's all ones.
	 */
	cp += 8;
	जबतक (cp < end && *cp == 0xff)
		cp++;

	/* Data block पढ़ोs (R1 response types) may need more data... */
	अगर (cp == end) अणु
		cp = host->data->status;
		end = cp+1;

		/* Card sends N(CR) (== 1..8) bytes of all-ones then one
		 * status byte ... and we alपढ़ोy scanned 2 bytes.
		 *
		 * REVISIT block पढ़ो paths use nasty byte-at-a-समय I/O
		 * so it can always DMA directly पूर्णांकo the target buffer.
		 * It'd probably be better to स_नकल() the first chunk and
		 * aव्योम extra i/o calls...
		 *
		 * Note we check क्रम more than 8 bytes, because in practice,
		 * some SD cards are slow...
		 */
		क्रम (i = 2; i < 16; i++) अणु
			value = mmc_spi_पढ़ोbytes(host, 1);
			अगर (value < 0)
				जाओ करोne;
			अगर (*cp != 0xff)
				जाओ checkstatus;
		पूर्ण
		value = -ETIMEDOUT;
		जाओ करोne;
	पूर्ण

checkstatus:
	bitshअगरt = 0;
	अगर (*cp & 0x80)	अणु
		/* Houston, we have an ugly card with a bit-shअगरted response */
		rotator = *cp++ << 8;
		/* पढ़ो the next byte */
		अगर (cp == end) अणु
			value = mmc_spi_पढ़ोbytes(host, 1);
			अगर (value < 0)
				जाओ करोne;
			cp = host->data->status;
			end = cp+1;
		पूर्ण
		rotator |= *cp++;
		जबतक (rotator & 0x8000) अणु
			bitshअगरt++;
			rotator <<= 1;
		पूर्ण
		cmd->resp[0] = rotator >> 8;
		leftover = rotator;
	पूर्ण अन्यथा अणु
		cmd->resp[0] = *cp++;
	पूर्ण
	cmd->error = 0;

	/* Status byte: the entire seven-bit R1 response.  */
	अगर (cmd->resp[0] != 0) अणु
		अगर ((R1_SPI_PARAMETER | R1_SPI_ADDRESS)
				& cmd->resp[0])
			value = -EFAULT; /* Bad address */
		अन्यथा अगर (R1_SPI_ILLEGAL_COMMAND & cmd->resp[0])
			value = -ENOSYS; /* Function not implemented */
		अन्यथा अगर (R1_SPI_COM_CRC & cmd->resp[0])
			value = -EILSEQ; /* Illegal byte sequence */
		अन्यथा अगर ((R1_SPI_ERASE_SEQ | R1_SPI_ERASE_RESET)
				& cmd->resp[0])
			value = -EIO;    /* I/O error */
		/* अन्यथा R1_SPI_IDLE, "it's resetting" */
	पूर्ण

	चयन (mmc_spi_resp_type(cmd)) अणु

	/* SPI R1B == R1 + busy; STOP_TRANSMISSION (क्रम multiblock पढ़ोs)
	 * and less-common stuff like various erase operations.
	 */
	हाल MMC_RSP_SPI_R1B:
		/* maybe we पढ़ो all the busy tokens alपढ़ोy */
		जबतक (cp < end && *cp == 0)
			cp++;
		अगर (cp == end) अणु
			समयout_ms = cmd->busy_समयout ? cmd->busy_समयout :
				MMC_SPI_R1B_TIMEOUT_MS;
			mmc_spi_रुको_unbusy(host, msecs_to_jअगरfies(समयout_ms));
		पूर्ण
		अवरोध;

	/* SPI R2 == R1 + second status byte; SEND_STATUS
	 * SPI R5 == R1 + data byte; IO_RW_सूचीECT
	 */
	हाल MMC_RSP_SPI_R2:
		/* पढ़ो the next byte */
		अगर (cp == end) अणु
			value = mmc_spi_पढ़ोbytes(host, 1);
			अगर (value < 0)
				जाओ करोne;
			cp = host->data->status;
			end = cp+1;
		पूर्ण
		अगर (bitshअगरt) अणु
			rotator = leftover << 8;
			rotator |= *cp << bitshअगरt;
			cmd->resp[0] |= (rotator & 0xFF00);
		पूर्ण अन्यथा अणु
			cmd->resp[0] |= *cp << 8;
		पूर्ण
		अवरोध;

	/* SPI R3, R4, or R7 == R1 + 4 bytes */
	हाल MMC_RSP_SPI_R3:
		rotator = leftover << 8;
		cmd->resp[1] = 0;
		क्रम (i = 0; i < 4; i++) अणु
			cmd->resp[1] <<= 8;
			/* पढ़ो the next byte */
			अगर (cp == end) अणु
				value = mmc_spi_पढ़ोbytes(host, 1);
				अगर (value < 0)
					जाओ करोne;
				cp = host->data->status;
				end = cp+1;
			पूर्ण
			अगर (bitshअगरt) अणु
				rotator |= *cp++ << bitshअगरt;
				cmd->resp[1] |= (rotator >> 8);
				rotator <<= 8;
			पूर्ण अन्यथा अणु
				cmd->resp[1] |= *cp++;
			पूर्ण
		पूर्ण
		अवरोध;

	/* SPI R1 == just one status byte */
	हाल MMC_RSP_SPI_R1:
		अवरोध;

	शेष:
		dev_dbg(&host->spi->dev, "bad response type %04x\n",
			mmc_spi_resp_type(cmd));
		अगर (value >= 0)
			value = -EINVAL;
		जाओ करोne;
	पूर्ण

	अगर (value < 0)
		dev_dbg(&host->spi->dev, "%s: resp %04x %08x\n",
			tag, cmd->resp[0], cmd->resp[1]);

	/* disable chipselect on errors and some success हालs */
	अगर (value >= 0 && cs_on)
		वापस value;
करोne:
	अगर (value < 0)
		cmd->error = value;
	mmc_cs_off(host);
	वापस value;
पूर्ण

/* Issue command and पढ़ो its response.
 * Returns zero on success, negative क्रम error.
 *
 * On error, caller must cope with mmc core retry mechanism.  That
 * means immediate low-level resubmit, which affects the bus lock...
 */
अटल पूर्णांक
mmc_spi_command_send(काष्ठा mmc_spi_host *host,
		काष्ठा mmc_request *mrq,
		काष्ठा mmc_command *cmd, पूर्णांक cs_on)
अणु
	काष्ठा scratch		*data = host->data;
	u8			*cp = data->status;
	पूर्णांक			status;
	काष्ठा spi_transfer	*t;

	/* We can handle most commands (except block पढ़ोs) in one full
	 * duplex I/O operation beक्रमe either starting the next transfer
	 * (data block or command) or अन्यथा deselecting the card.
	 *
	 * First, ग_लिखो 7 bytes:
	 *  - an all-ones byte to ensure the card is पढ़ोy
	 *  - opcode byte (plus start and transmission bits)
	 *  - four bytes of big-endian argument
	 *  - crc7 (plus end bit) ... always computed, it's cheap
	 *
	 * We init the whole buffer to all-ones, which is what we need
	 * to ग_लिखो जबतक we're पढ़ोing (later) response data.
	 */
	स_रखो(cp, 0xff, माप(data->status));

	cp[1] = 0x40 | cmd->opcode;
	put_unaligned_be32(cmd->arg, cp + 2);
	cp[6] = crc7_be(0, cp + 1, 5) | 0x01;
	cp += 7;

	/* Then, पढ़ो up to 13 bytes (जबतक writing all-ones):
	 *  - N(CR) (== 1..8) bytes of all-ones
	 *  - status byte (क्रम all response types)
	 *  - the rest of the response, either:
	 *      + nothing, क्रम R1 or R1B responses
	 *	+ second status byte, क्रम R2 responses
	 *	+ four data bytes, क्रम R3 and R7 responses
	 *
	 * Finally, पढ़ो some more bytes ... in the nice हालs we know in
	 * advance how many, and पढ़ोing 1 more is always OK:
	 *  - N(EC) (== 0..N) bytes of all-ones, beक्रमe deselect/finish
	 *  - N(RC) (== 1..N) bytes of all-ones, beक्रमe next command
	 *  - N(WR) (== 1..N) bytes of all-ones, beक्रमe data ग_लिखो
	 *
	 * So in those हालs one full duplex I/O of at most 21 bytes will
	 * handle the whole command, leaving the card पढ़ोy to receive a
	 * data block or new command.  We करो that whenever we can, shaving
	 * CPU and IRQ costs (especially when using DMA or FIFOs).
	 *
	 * There are two other हालs, where it's not generally practical
	 * to rely on a single I/O:
	 *
	 *  - R1B responses need at least N(EC) bytes of all-zeroes.
	 *
	 *    In this हाल we can *try* to fit it पूर्णांकo one I/O, then
	 *    maybe पढ़ो more data later.
	 *
	 *  - Data block पढ़ोs are more troublesome, since a variable
	 *    number of padding bytes precede the token and data.
	 *      + N(CX) (== 0..8) bytes of all-ones, beक्रमe CSD or CID
	 *      + N(AC) (== 1..many) bytes of all-ones
	 *
	 *    In this हाल we currently only have minimal speedups here:
	 *    when N(CR) == 1 we can aव्योम I/O in response_get().
	 */
	अगर (cs_on && (mrq->data->flags & MMC_DATA_READ)) अणु
		cp += 2;	/* min(N(CR)) + status */
		/* R1 */
	पूर्ण अन्यथा अणु
		cp += 10;	/* max(N(CR)) + status + min(N(RC),N(WR)) */
		अगर (cmd->flags & MMC_RSP_SPI_S2)	/* R2/R5 */
			cp++;
		अन्यथा अगर (cmd->flags & MMC_RSP_SPI_B4)	/* R3/R4/R7 */
			cp += 4;
		अन्यथा अगर (cmd->flags & MMC_RSP_BUSY)	/* R1B */
			cp = data->status + माप(data->status);
		/* अन्यथा:  R1 (most commands) */
	पूर्ण

	dev_dbg(&host->spi->dev, "  mmc_spi: CMD%d, resp %s\n",
		cmd->opcode, maptype(cmd));

	/* send command, leaving chipselect active */
	spi_message_init(&host->m);

	t = &host->t;
	स_रखो(t, 0, माप(*t));
	t->tx_buf = t->rx_buf = data->status;
	t->tx_dma = t->rx_dma = host->data_dma;
	t->len = cp - data->status;
	t->cs_change = 1;
	spi_message_add_tail(t, &host->m);

	अगर (host->dma_dev) अणु
		host->m.is_dma_mapped = 1;
		dma_sync_single_क्रम_device(host->dma_dev,
				host->data_dma, माप(*host->data),
				DMA_BIसूचीECTIONAL);
	पूर्ण
	status = spi_sync_locked(host->spi, &host->m);

	अगर (host->dma_dev)
		dma_sync_single_क्रम_cpu(host->dma_dev,
				host->data_dma, माप(*host->data),
				DMA_BIसूचीECTIONAL);
	अगर (status < 0) अणु
		dev_dbg(&host->spi->dev, "  ... write returned %d\n", status);
		cmd->error = status;
		वापस status;
	पूर्ण

	/* after no-data commands and STOP_TRANSMISSION, chipselect off */
	वापस mmc_spi_response_get(host, cmd, cs_on);
पूर्ण

/* Build data message with up to four separate transfers.  For TX, we
 * start by writing the data token.  And in most हालs, we finish with
 * a status transfer.
 *
 * We always provide TX data क्रम data and CRC.  The MMC/SD protocol
 * requires us to ग_लिखो ones; but Linux शेषs to writing zeroes;
 * so we explicitly initialize it to all ones on RX paths.
 *
 * We also handle DMA mapping, so the underlying SPI controller करोes
 * not need to (re)करो it क्रम each message.
 */
अटल व्योम
mmc_spi_setup_data_message(
	काष्ठा mmc_spi_host	*host,
	पूर्णांक			multiple,
	क्रमागत dma_data_direction	direction)
अणु
	काष्ठा spi_transfer	*t;
	काष्ठा scratch		*scratch = host->data;
	dma_addr_t		dma = host->data_dma;

	spi_message_init(&host->m);
	अगर (dma)
		host->m.is_dma_mapped = 1;

	/* क्रम पढ़ोs, पढ़ोblock() skips 0xff bytes beक्रमe finding
	 * the token; क्रम ग_लिखोs, this transfer issues that token.
	 */
	अगर (direction == DMA_TO_DEVICE) अणु
		t = &host->token;
		स_रखो(t, 0, माप(*t));
		t->len = 1;
		अगर (multiple)
			scratch->data_token = SPI_TOKEN_MULTI_WRITE;
		अन्यथा
			scratch->data_token = SPI_TOKEN_SINGLE;
		t->tx_buf = &scratch->data_token;
		अगर (dma)
			t->tx_dma = dma + दुरत्व(काष्ठा scratch, data_token);
		spi_message_add_tail(t, &host->m);
	पूर्ण

	/* Body of transfer is buffer, then CRC ...
	 * either TX-only, or RX with TX-ones.
	 */
	t = &host->t;
	स_रखो(t, 0, माप(*t));
	t->tx_buf = host->ones;
	t->tx_dma = host->ones_dma;
	/* length and actual buffer info are written later */
	spi_message_add_tail(t, &host->m);

	t = &host->crc;
	स_रखो(t, 0, माप(*t));
	t->len = 2;
	अगर (direction == DMA_TO_DEVICE) अणु
		/* the actual CRC may get written later */
		t->tx_buf = &scratch->crc_val;
		अगर (dma)
			t->tx_dma = dma + दुरत्व(काष्ठा scratch, crc_val);
	पूर्ण अन्यथा अणु
		t->tx_buf = host->ones;
		t->tx_dma = host->ones_dma;
		t->rx_buf = &scratch->crc_val;
		अगर (dma)
			t->rx_dma = dma + दुरत्व(काष्ठा scratch, crc_val);
	पूर्ण
	spi_message_add_tail(t, &host->m);

	/*
	 * A single block पढ़ो is followed by N(EC) [0+] all-ones bytes
	 * beक्रमe deselect ... करोn't bother.
	 *
	 * Multiblock पढ़ोs are followed by N(AC) [1+] all-ones bytes beक्रमe
	 * the next block is पढ़ो, or a STOP_TRANSMISSION is issued.  We'll
	 * collect that single byte, so पढ़ोblock() करोesn't need to.
	 *
	 * For a ग_लिखो, the one-byte data response follows immediately, then
	 * come zero or more busy bytes, then N(WR) [1+] all-ones bytes.
	 * Then single block पढ़ोs may deselect, and multiblock ones issue
	 * the next token (next data block, or STOP_TRAN).  We can try to
	 * minimize I/O ops by using a single पढ़ो to collect end-of-busy.
	 */
	अगर (multiple || direction == DMA_TO_DEVICE) अणु
		t = &host->early_status;
		स_रखो(t, 0, माप(*t));
		t->len = (direction == DMA_TO_DEVICE) ? माप(scratch->status) : 1;
		t->tx_buf = host->ones;
		t->tx_dma = host->ones_dma;
		t->rx_buf = scratch->status;
		अगर (dma)
			t->rx_dma = dma + दुरत्व(काष्ठा scratch, status);
		t->cs_change = 1;
		spi_message_add_tail(t, &host->m);
	पूर्ण
पूर्ण

/*
 * Write one block:
 *  - caller handled preceding N(WR) [1+] all-ones bytes
 *  - data block
 *	+ token
 *	+ data bytes
 *	+ crc16
 *  - an all-ones byte ... card ग_लिखोs a data-response byte
 *  - followed by N(EC) [0+] all-ones bytes, card ग_लिखोs zero/'busy'
 *
 * Return negative त्रुटि_सं, अन्यथा success.
 */
अटल पूर्णांक
mmc_spi_ग_लिखोblock(काष्ठा mmc_spi_host *host, काष्ठा spi_transfer *t,
	अचिन्हित दीर्घ समयout)
अणु
	काष्ठा spi_device	*spi = host->spi;
	पूर्णांक			status, i;
	काष्ठा scratch		*scratch = host->data;
	u32			pattern;

	अगर (host->mmc->use_spi_crc)
		scratch->crc_val = cpu_to_be16(crc_itu_t(0, t->tx_buf, t->len));
	अगर (host->dma_dev)
		dma_sync_single_क्रम_device(host->dma_dev,
				host->data_dma, माप(*scratch),
				DMA_BIसूचीECTIONAL);

	status = spi_sync_locked(spi, &host->m);

	अगर (status != 0) अणु
		dev_dbg(&spi->dev, "write error (%d)\n", status);
		वापस status;
	पूर्ण

	अगर (host->dma_dev)
		dma_sync_single_क्रम_cpu(host->dma_dev,
				host->data_dma, माप(*scratch),
				DMA_BIसूचीECTIONAL);

	/*
	 * Get the transmission data-response reply.  It must follow
	 * immediately after the data block we transferred.  This reply
	 * करोesn't necessarily tell whether the ग_लिखो operation succeeded;
	 * it just says अगर the transmission was ok and whether *earlier*
	 * ग_लिखोs succeeded; see the standard.
	 *
	 * In practice, there are (even modern SDHC-)cards which are late
	 * in sending the response, and miss the समय frame by a few bits,
	 * so we have to cope with this situation and check the response
	 * bit-by-bit. Arggh!!!
	 */
	pattern = get_unaligned_be32(scratch->status);

	/* First 3 bit of pattern are undefined */
	pattern |= 0xE0000000;

	/* left-adjust to leading 0 bit */
	जबतक (pattern & 0x80000000)
		pattern <<= 1;
	/* right-adjust क्रम pattern matching. Code is in bit 4..0 now. */
	pattern >>= 27;

	चयन (pattern) अणु
	हाल SPI_RESPONSE_ACCEPTED:
		status = 0;
		अवरोध;
	हाल SPI_RESPONSE_CRC_ERR:
		/* host shall then issue MMC_STOP_TRANSMISSION */
		status = -EILSEQ;
		अवरोध;
	हाल SPI_RESPONSE_WRITE_ERR:
		/* host shall then issue MMC_STOP_TRANSMISSION,
		 * and should MMC_SEND_STATUS to sort it out
		 */
		status = -EIO;
		अवरोध;
	शेष:
		status = -EPROTO;
		अवरोध;
	पूर्ण
	अगर (status != 0) अणु
		dev_dbg(&spi->dev, "write error %02x (%d)\n",
			scratch->status[0], status);
		वापस status;
	पूर्ण

	t->tx_buf += t->len;
	अगर (host->dma_dev)
		t->tx_dma += t->len;

	/* Return when not busy.  If we didn't collect that status yet,
	 * we'll need some more I/O.
	 */
	क्रम (i = 4; i < माप(scratch->status); i++) अणु
		/* card is non-busy अगर the most recent bit is 1 */
		अगर (scratch->status[i] & 0x01)
			वापस 0;
	पूर्ण
	वापस mmc_spi_रुको_unbusy(host, समयout);
पूर्ण

/*
 * Read one block:
 *  - skip leading all-ones bytes ... either
 *      + N(AC) [1..f(घड़ी,CSD)] usually, अन्यथा
 *      + N(CX) [0..8] when पढ़ोing CSD or CID
 *  - data block
 *	+ token ... अगर error token, no data or crc
 *	+ data bytes
 *	+ crc16
 *
 * After single block पढ़ोs, we're करोne; N(EC) [0+] all-ones bytes follow
 * beक्रमe dropping chipselect.
 *
 * For multiblock पढ़ोs, caller either पढ़ोs the next block or issues a
 * STOP_TRANSMISSION command.
 */
अटल पूर्णांक
mmc_spi_पढ़ोblock(काष्ठा mmc_spi_host *host, काष्ठा spi_transfer *t,
	अचिन्हित दीर्घ समयout)
अणु
	काष्ठा spi_device	*spi = host->spi;
	पूर्णांक			status;
	काष्ठा scratch		*scratch = host->data;
	अचिन्हित पूर्णांक 		bitshअगरt;
	u8			leftover;

	/* At least one SD card sends an all-zeroes byte when N(CX)
	 * applies, beक्रमe the all-ones bytes ... just cope with that.
	 */
	status = mmc_spi_पढ़ोbytes(host, 1);
	अगर (status < 0)
		वापस status;
	status = scratch->status[0];
	अगर (status == 0xff || status == 0)
		status = mmc_spi_पढ़ोtoken(host, समयout);

	अगर (status < 0) अणु
		dev_dbg(&spi->dev, "read error %02x (%d)\n", status, status);
		वापस status;
	पूर्ण

	/* The token may be bit-shअगरted...
	 * the first 0-bit precedes the data stream.
	 */
	bitshअगरt = 7;
	जबतक (status & 0x80) अणु
		status <<= 1;
		bitshअगरt--;
	पूर्ण
	leftover = status << 1;

	अगर (host->dma_dev) अणु
		dma_sync_single_क्रम_device(host->dma_dev,
				host->data_dma, माप(*scratch),
				DMA_BIसूचीECTIONAL);
		dma_sync_single_क्रम_device(host->dma_dev,
				t->rx_dma, t->len,
				DMA_FROM_DEVICE);
	पूर्ण

	status = spi_sync_locked(spi, &host->m);
	अगर (status < 0) अणु
		dev_dbg(&spi->dev, "read error %d\n", status);
		वापस status;
	पूर्ण

	अगर (host->dma_dev) अणु
		dma_sync_single_क्रम_cpu(host->dma_dev,
				host->data_dma, माप(*scratch),
				DMA_BIसूचीECTIONAL);
		dma_sync_single_क्रम_cpu(host->dma_dev,
				t->rx_dma, t->len,
				DMA_FROM_DEVICE);
	पूर्ण

	अगर (bitshअगरt) अणु
		/* Walk through the data and the crc and करो
		 * all the magic to get byte-aligned data.
		 */
		u8 *cp = t->rx_buf;
		अचिन्हित पूर्णांक len;
		अचिन्हित पूर्णांक bitright = 8 - bitshअगरt;
		u8 temp;
		क्रम (len = t->len; len; len--) अणु
			temp = *cp;
			*cp++ = leftover | (temp >> bitshअगरt);
			leftover = temp << bitright;
		पूर्ण
		cp = (u8 *) &scratch->crc_val;
		temp = *cp;
		*cp++ = leftover | (temp >> bitshअगरt);
		leftover = temp << bitright;
		temp = *cp;
		*cp = leftover | (temp >> bitshअगरt);
	पूर्ण

	अगर (host->mmc->use_spi_crc) अणु
		u16 crc = crc_itu_t(0, t->rx_buf, t->len);

		be16_to_cpus(&scratch->crc_val);
		अगर (scratch->crc_val != crc) अणु
			dev_dbg(&spi->dev,
				"read - crc error: crc_val=0x%04x, computed=0x%04x len=%d\n",
				scratch->crc_val, crc, t->len);
			वापस -EILSEQ;
		पूर्ण
	पूर्ण

	t->rx_buf += t->len;
	अगर (host->dma_dev)
		t->rx_dma += t->len;

	वापस 0;
पूर्ण

/*
 * An MMC/SD data stage includes one or more blocks, optional CRCs,
 * and अंतरभूत handshaking.  That handhaking makes it unlike most
 * other SPI protocol stacks.
 */
अटल व्योम
mmc_spi_data_करो(काष्ठा mmc_spi_host *host, काष्ठा mmc_command *cmd,
		काष्ठा mmc_data *data, u32 blk_size)
अणु
	काष्ठा spi_device	*spi = host->spi;
	काष्ठा device		*dma_dev = host->dma_dev;
	काष्ठा spi_transfer	*t;
	क्रमागत dma_data_direction	direction;
	काष्ठा scatterlist	*sg;
	अचिन्हित		n_sg;
	पूर्णांक			multiple = (data->blocks > 1);
	u32			घड़ी_rate;
	अचिन्हित दीर्घ		समयout;

	direction = mmc_get_dma_dir(data);
	mmc_spi_setup_data_message(host, multiple, direction);
	t = &host->t;

	अगर (t->speed_hz)
		घड़ी_rate = t->speed_hz;
	अन्यथा
		घड़ी_rate = spi->max_speed_hz;

	समयout = data->समयout_ns / 1000 +
		  data->समयout_clks * 1000000 / घड़ी_rate;
	समयout = usecs_to_jअगरfies((अचिन्हित पूर्णांक)समयout) + 1;

	/* Handle scatterlist segments one at a समय, with synch क्रम
	 * each 512-byte block
	 */
	क्रम_each_sg(data->sg, sg, data->sg_len, n_sg) अणु
		पूर्णांक			status = 0;
		dma_addr_t		dma_addr = 0;
		व्योम			*kmap_addr;
		अचिन्हित		length = sg->length;
		क्रमागत dma_data_direction	dir = direction;

		/* set up dma mapping क्रम controller drivers that might
		 * use DMA ... though they may fall back to PIO
		 */
		अगर (dma_dev) अणु
			/* never invalidate whole *shared* pages ... */
			अगर ((sg->offset != 0 || length != PAGE_SIZE)
					&& dir == DMA_FROM_DEVICE)
				dir = DMA_BIसूचीECTIONAL;

			dma_addr = dma_map_page(dma_dev, sg_page(sg), 0,
						PAGE_SIZE, dir);
			अगर (dma_mapping_error(dma_dev, dma_addr)) अणु
				data->error = -EFAULT;
				अवरोध;
			पूर्ण
			अगर (direction == DMA_TO_DEVICE)
				t->tx_dma = dma_addr + sg->offset;
			अन्यथा
				t->rx_dma = dma_addr + sg->offset;
		पूर्ण

		/* allow pio too; we करोn't allow highmem */
		kmap_addr = kmap(sg_page(sg));
		अगर (direction == DMA_TO_DEVICE)
			t->tx_buf = kmap_addr + sg->offset;
		अन्यथा
			t->rx_buf = kmap_addr + sg->offset;

		/* transfer each block, and update request status */
		जबतक (length) अणु
			t->len = min(length, blk_size);

			dev_dbg(&host->spi->dev,
				"    mmc_spi: %s block, %d bytes\n",
				(direction == DMA_TO_DEVICE) ? "write" : "read",
				t->len);

			अगर (direction == DMA_TO_DEVICE)
				status = mmc_spi_ग_लिखोblock(host, t, समयout);
			अन्यथा
				status = mmc_spi_पढ़ोblock(host, t, समयout);
			अगर (status < 0)
				अवरोध;

			data->bytes_xfered += t->len;
			length -= t->len;

			अगर (!multiple)
				अवरोध;
		पूर्ण

		/* discard mappings */
		अगर (direction == DMA_FROM_DEVICE)
			flush_kernel_dcache_page(sg_page(sg));
		kunmap(sg_page(sg));
		अगर (dma_dev)
			dma_unmap_page(dma_dev, dma_addr, PAGE_SIZE, dir);

		अगर (status < 0) अणु
			data->error = status;
			dev_dbg(&spi->dev, "%s status %d\n",
				(direction == DMA_TO_DEVICE) ? "write" : "read",
				status);
			अवरोध;
		पूर्ण
	पूर्ण

	/* NOTE some करोcs describe an MMC-only SET_BLOCK_COUNT (CMD23) that
	 * can be issued beक्रमe multiblock ग_लिखोs.  Unlike its more widely
	 * करोcumented analogue क्रम SD cards (SET_WR_BLK_ERASE_COUNT, ACMD23),
	 * that can affect the STOP_TRAN logic.   Complete (and current)
	 * MMC specs should sort that out beक्रमe Linux starts using CMD23.
	 */
	अगर (direction == DMA_TO_DEVICE && multiple) अणु
		काष्ठा scratch	*scratch = host->data;
		पूर्णांक		पंचांगp;
		स्थिर अचिन्हित	statlen = माप(scratch->status);

		dev_dbg(&spi->dev, "    mmc_spi: STOP_TRAN\n");

		/* Tweak the per-block message we set up earlier by morphing
		 * it to hold single buffer with the token followed by some
		 * all-ones bytes ... skip N(BR) (0..1), scan the rest क्रम
		 * "not busy any longer" status, and leave chip selected.
		 */
		INIT_LIST_HEAD(&host->m.transfers);
		list_add(&host->early_status.transfer_list,
				&host->m.transfers);

		स_रखो(scratch->status, 0xff, statlen);
		scratch->status[0] = SPI_TOKEN_STOP_TRAN;

		host->early_status.tx_buf = host->early_status.rx_buf;
		host->early_status.tx_dma = host->early_status.rx_dma;
		host->early_status.len = statlen;

		अगर (host->dma_dev)
			dma_sync_single_क्रम_device(host->dma_dev,
					host->data_dma, माप(*scratch),
					DMA_BIसूचीECTIONAL);

		पंचांगp = spi_sync_locked(spi, &host->m);

		अगर (host->dma_dev)
			dma_sync_single_क्रम_cpu(host->dma_dev,
					host->data_dma, माप(*scratch),
					DMA_BIसूचीECTIONAL);

		अगर (पंचांगp < 0) अणु
			अगर (!data->error)
				data->error = पंचांगp;
			वापस;
		पूर्ण

		/* Ideally we collected "not busy" status with one I/O,
		 * aव्योमing wasteful byte-at-a-समय scanning... but more
		 * I/O is often needed.
		 */
		क्रम (पंचांगp = 2; पंचांगp < statlen; पंचांगp++) अणु
			अगर (scratch->status[पंचांगp] != 0)
				वापस;
		पूर्ण
		पंचांगp = mmc_spi_रुको_unbusy(host, समयout);
		अगर (पंचांगp < 0 && !data->error)
			data->error = पंचांगp;
	पूर्ण
पूर्ण

/****************************************************************************/

/*
 * MMC driver implementation -- the पूर्णांकerface to the MMC stack
 */

अटल व्योम mmc_spi_request(काष्ठा mmc_host *mmc, काष्ठा mmc_request *mrq)
अणु
	काष्ठा mmc_spi_host	*host = mmc_priv(mmc);
	पूर्णांक			status = -EINVAL;
	पूर्णांक			crc_retry = 5;
	काष्ठा mmc_command	stop;

#अगर_घोषित DEBUG
	/* MMC core and layered drivers *MUST* issue SPI-aware commands */
	अणु
		काष्ठा mmc_command	*cmd;
		पूर्णांक			invalid = 0;

		cmd = mrq->cmd;
		अगर (!mmc_spi_resp_type(cmd)) अणु
			dev_dbg(&host->spi->dev, "bogus command\n");
			cmd->error = -EINVAL;
			invalid = 1;
		पूर्ण

		cmd = mrq->stop;
		अगर (cmd && !mmc_spi_resp_type(cmd)) अणु
			dev_dbg(&host->spi->dev, "bogus STOP command\n");
			cmd->error = -EINVAL;
			invalid = 1;
		पूर्ण

		अगर (invalid) अणु
			dump_stack();
			mmc_request_करोne(host->mmc, mrq);
			वापस;
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	/* request exclusive bus access */
	spi_bus_lock(host->spi->master);

crc_recover:
	/* issue command; then optionally data and stop */
	status = mmc_spi_command_send(host, mrq, mrq->cmd, mrq->data != शून्य);
	अगर (status == 0 && mrq->data) अणु
		mmc_spi_data_करो(host, mrq->cmd, mrq->data, mrq->data->blksz);

		/*
		 * The SPI bus is not always reliable क्रम large data transfers.
		 * If an occasional crc error is reported by the SD device with
		 * data पढ़ो/ग_लिखो over SPI, it may be recovered by repeating
		 * the last SD command again. The retry count is set to 5 to
		 * ensure the driver passes stress tests.
		 */
		अगर (mrq->data->error == -EILSEQ && crc_retry) अणु
			stop.opcode = MMC_STOP_TRANSMISSION;
			stop.arg = 0;
			stop.flags = MMC_RSP_SPI_R1B | MMC_RSP_R1B | MMC_CMD_AC;
			status = mmc_spi_command_send(host, mrq, &stop, 0);
			crc_retry--;
			mrq->data->error = 0;
			जाओ crc_recover;
		पूर्ण

		अगर (mrq->stop)
			status = mmc_spi_command_send(host, mrq, mrq->stop, 0);
		अन्यथा
			mmc_cs_off(host);
	पूर्ण

	/* release the bus */
	spi_bus_unlock(host->spi->master);

	mmc_request_करोne(host->mmc, mrq);
पूर्ण

/* See Section 6.4.1, in SD "Simplified Physical Layer Specification 2.0"
 *
 * NOTE that here we can't know that the card has just been घातered up;
 * not all MMC/SD sockets support घातer चयनing.
 *
 * FIXME when the card is still in SPI mode, e.g. from a previous kernel,
 * this करोesn't seem to करो the right thing at all...
 */
अटल व्योम mmc_spi_initsequence(काष्ठा mmc_spi_host *host)
अणु
	/* Try to be very sure any previous command has completed;
	 * रुको till not-busy, skip debris from any old commands.
	 */
	mmc_spi_रुको_unbusy(host, msecs_to_jअगरfies(MMC_SPI_INIT_TIMEOUT_MS));
	mmc_spi_पढ़ोbytes(host, 10);

	/*
	 * Do a burst with chipselect active-high.  We need to करो this to
	 * meet the requirement of 74 घड़ी cycles with both chipselect
	 * and CMD (MOSI) high beक्रमe CMD0 ... after the card has been
	 * घातered up to Vdd(min), and so is पढ़ोy to take commands.
	 *
	 * Some cards are particularly needy of this (e.g. Viking "SD256")
	 * जबतक most others करोn't seem to care.
	 *
	 * Note that this is one of the places MMC/SD plays games with the
	 * SPI protocol.  Another is that when chipselect is released जबतक
	 * the card वापसs BUSY status, the घड़ी must issue several cycles
	 * with chipselect high beक्रमe the card will stop driving its output.
	 *
	 * SPI_CS_HIGH means "asserted" here. In some हालs like when using
	 * GPIOs क्रम chip select, SPI_CS_HIGH is set but this will be logically
	 * inverted by gpiolib, so अगर we want to ascertain to drive it high
	 * we should toggle the शेष with an XOR as we करो here.
	 */
	host->spi->mode ^= SPI_CS_HIGH;
	अगर (spi_setup(host->spi) != 0) अणु
		/* Just warn; most cards work without it. */
		dev_warn(&host->spi->dev,
				"can't change chip-select polarity\n");
		host->spi->mode ^= SPI_CS_HIGH;
	पूर्ण अन्यथा अणु
		mmc_spi_पढ़ोbytes(host, 18);

		host->spi->mode ^= SPI_CS_HIGH;
		अगर (spi_setup(host->spi) != 0) अणु
			/* Wot, we can't get the same setup we had beक्रमe? */
			dev_err(&host->spi->dev,
					"can't restore chip-select polarity\n");
		पूर्ण
	पूर्ण
पूर्ण

अटल अक्षर *mmc_घातerstring(u8 घातer_mode)
अणु
	चयन (घातer_mode) अणु
	हाल MMC_POWER_OFF: वापस "off";
	हाल MMC_POWER_UP:  वापस "up";
	हाल MMC_POWER_ON:  वापस "on";
	पूर्ण
	वापस "?";
पूर्ण

अटल व्योम mmc_spi_set_ios(काष्ठा mmc_host *mmc, काष्ठा mmc_ios *ios)
अणु
	काष्ठा mmc_spi_host *host = mmc_priv(mmc);

	अगर (host->घातer_mode != ios->घातer_mode) अणु
		पूर्णांक		canघातer;

		canघातer = host->pdata && host->pdata->setघातer;

		dev_dbg(&host->spi->dev, "mmc_spi: power %s (%d)%s\n",
				mmc_घातerstring(ios->घातer_mode),
				ios->vdd,
				canघातer ? ", can switch" : "");

		/* चयन घातer on/off अगर possible, accounting क्रम
		 * max 250msec घातerup समय अगर needed.
		 */
		अगर (canघातer) अणु
			चयन (ios->घातer_mode) अणु
			हाल MMC_POWER_OFF:
			हाल MMC_POWER_UP:
				host->pdata->setघातer(&host->spi->dev,
						ios->vdd);
				अगर (ios->घातer_mode == MMC_POWER_UP)
					msleep(host->घातerup_msecs);
			पूर्ण
		पूर्ण

		/* See 6.4.1 in the simplअगरied SD card physical spec 2.0 */
		अगर (ios->घातer_mode == MMC_POWER_ON)
			mmc_spi_initsequence(host);

		/* If घातering करोwn, ground all card inमाला_दो to aव्योम घातer
		 * delivery from data lines!  On a shared SPI bus, this
		 * will probably be temporary; 6.4.2 of the simplअगरied SD
		 * spec says this must last at least 1msec.
		 *
		 *   - Clock low means CPOL 0, e.g. mode 0
		 *   - MOSI low comes from writing zero
		 *   - Chipselect is usually active low...
		 */
		अगर (canघातer && ios->घातer_mode == MMC_POWER_OFF) अणु
			पूर्णांक mres;
			u8 nullbyte = 0;

			host->spi->mode &= ~(SPI_CPOL|SPI_CPHA);
			mres = spi_setup(host->spi);
			अगर (mres < 0)
				dev_dbg(&host->spi->dev,
					"switch to SPI mode 0 failed\n");

			अगर (spi_ग_लिखो(host->spi, &nullbyte, 1) < 0)
				dev_dbg(&host->spi->dev,
					"put spi signals to low failed\n");

			/*
			 * Now घड़ी should be low due to spi mode 0;
			 * MOSI should be low because of written 0x00;
			 * chipselect should be low (it is active low)
			 * घातer supply is off, so now MMC is off too!
			 *
			 * FIXME no, chipselect can be high since the
			 * device is inactive and SPI_CS_HIGH is clear...
			 */
			msleep(10);
			अगर (mres == 0) अणु
				host->spi->mode |= (SPI_CPOL|SPI_CPHA);
				mres = spi_setup(host->spi);
				अगर (mres < 0)
					dev_dbg(&host->spi->dev,
						"switch back to SPI mode 3 failed\n");
			पूर्ण
		पूर्ण

		host->घातer_mode = ios->घातer_mode;
	पूर्ण

	अगर (host->spi->max_speed_hz != ios->घड़ी && ios->घड़ी != 0) अणु
		पूर्णांक		status;

		host->spi->max_speed_hz = ios->घड़ी;
		status = spi_setup(host->spi);
		dev_dbg(&host->spi->dev,
			"mmc_spi:  clock to %d Hz, %d\n",
			host->spi->max_speed_hz, status);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा mmc_host_ops mmc_spi_ops = अणु
	.request	= mmc_spi_request,
	.set_ios	= mmc_spi_set_ios,
	.get_ro		= mmc_gpio_get_ro,
	.get_cd		= mmc_gpio_get_cd,
पूर्ण;


/****************************************************************************/

/*
 * SPI driver implementation
 */

अटल irqवापस_t
mmc_spi_detect_irq(पूर्णांक irq, व्योम *mmc)
अणु
	काष्ठा mmc_spi_host *host = mmc_priv(mmc);
	u16 delay_msec = max(host->pdata->detect_delay, (u16)100);

	mmc_detect_change(mmc, msecs_to_jअगरfies(delay_msec));
	वापस IRQ_HANDLED;
पूर्ण

#अगर_घोषित CONFIG_HAS_DMA
अटल पूर्णांक mmc_spi_dma_alloc(काष्ठा mmc_spi_host *host)
अणु
	काष्ठा spi_device *spi = host->spi;
	काष्ठा device *dev;

	अगर (!spi->master->dev.parent->dma_mask)
		वापस 0;

	dev = spi->master->dev.parent;

	host->ones_dma = dma_map_single(dev, host->ones, MMC_SPI_BLOCKSIZE,
					DMA_TO_DEVICE);
	अगर (dma_mapping_error(dev, host->ones_dma))
		वापस -ENOMEM;

	host->data_dma = dma_map_single(dev, host->data, माप(*host->data),
					DMA_BIसूचीECTIONAL);
	अगर (dma_mapping_error(dev, host->data_dma)) अणु
		dma_unmap_single(dev, host->ones_dma, MMC_SPI_BLOCKSIZE,
				 DMA_TO_DEVICE);
		वापस -ENOMEM;
	पूर्ण

	dma_sync_single_क्रम_cpu(dev, host->data_dma, माप(*host->data),
				DMA_BIसूचीECTIONAL);

	host->dma_dev = dev;
	वापस 0;
पूर्ण

अटल व्योम mmc_spi_dma_मुक्त(काष्ठा mmc_spi_host *host)
अणु
	अगर (!host->dma_dev)
		वापस;

	dma_unmap_single(host->dma_dev, host->ones_dma, MMC_SPI_BLOCKSIZE,
			 DMA_TO_DEVICE);
	dma_unmap_single(host->dma_dev, host->data_dma,	माप(*host->data),
			 DMA_BIसूचीECTIONAL);
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक mmc_spi_dma_alloc(काष्ठा mmc_spi_host *host) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम mmc_spi_dma_मुक्त(काष्ठा mmc_spi_host *host) अणुपूर्ण
#पूर्ण_अगर

अटल पूर्णांक mmc_spi_probe(काष्ठा spi_device *spi)
अणु
	व्योम			*ones;
	काष्ठा mmc_host		*mmc;
	काष्ठा mmc_spi_host	*host;
	पूर्णांक			status;
	bool			has_ro = false;

	/* We rely on full duplex transfers, mostly to reduce
	 * per-transfer overheads (by making fewer transfers).
	 */
	अगर (spi->master->flags & SPI_MASTER_HALF_DUPLEX)
		वापस -EINVAL;

	/* MMC and SD specs only seem to care that sampling is on the
	 * rising edge ... meaning SPI modes 0 or 3.  So either SPI mode
	 * should be legit.  We'll use mode 0 since the steady state is 0,
	 * which is appropriate क्रम hotplugging, unless the platक्रमm data
	 * specअगरy mode 3 (अगर hardware is not compatible to mode 0).
	 */
	अगर (spi->mode != SPI_MODE_3)
		spi->mode = SPI_MODE_0;
	spi->bits_per_word = 8;

	status = spi_setup(spi);
	अगर (status < 0) अणु
		dev_dbg(&spi->dev, "needs SPI mode %02x, %d KHz; %d\n",
				spi->mode, spi->max_speed_hz / 1000,
				status);
		वापस status;
	पूर्ण

	/* We need a supply of ones to transmit.  This is the only समय
	 * the CPU touches these, so cache coherency isn't a concern.
	 *
	 * NOTE अगर many प्रणालीs use more than one MMC-over-SPI connector
	 * it'd save some memory to share this.  That's evidently rare.
	 */
	status = -ENOMEM;
	ones = kदो_स्मृति(MMC_SPI_BLOCKSIZE, GFP_KERNEL);
	अगर (!ones)
		जाओ nomem;
	स_रखो(ones, 0xff, MMC_SPI_BLOCKSIZE);

	mmc = mmc_alloc_host(माप(*host), &spi->dev);
	अगर (!mmc)
		जाओ nomem;

	mmc->ops = &mmc_spi_ops;
	mmc->max_blk_size = MMC_SPI_BLOCKSIZE;
	mmc->max_segs = MMC_SPI_BLOCKSATONCE;
	mmc->max_req_size = MMC_SPI_BLOCKSATONCE * MMC_SPI_BLOCKSIZE;
	mmc->max_blk_count = MMC_SPI_BLOCKSATONCE;

	mmc->caps = MMC_CAP_SPI;

	/* SPI करोesn't need the lowspeed device identअगरication thing क्रम
	 * MMC or SD cards, since it never comes up in खोलो drain mode.
	 * That's good; some SPI masters can't handle very low speeds!
	 *
	 * However, low speed SDIO cards need not handle over 400 KHz;
	 * that's the only reason not to use a few MHz क्रम f_min (until
	 * the upper layer पढ़ोs the target frequency from the CSD).
	 */
	mmc->f_min = 400000;
	mmc->f_max = spi->max_speed_hz;

	host = mmc_priv(mmc);
	host->mmc = mmc;
	host->spi = spi;

	host->ones = ones;

	dev_set_drvdata(&spi->dev, mmc);

	/* Platक्रमm data is used to hook up things like card sensing
	 * and घातer चयनing gpios.
	 */
	host->pdata = mmc_spi_get_pdata(spi);
	अगर (host->pdata)
		mmc->ocr_avail = host->pdata->ocr_mask;
	अगर (!mmc->ocr_avail) अणु
		dev_warn(&spi->dev, "ASSUMING 3.2-3.4 V slot power\n");
		mmc->ocr_avail = MMC_VDD_32_33|MMC_VDD_33_34;
	पूर्ण
	अगर (host->pdata && host->pdata->setघातer) अणु
		host->घातerup_msecs = host->pdata->घातerup_msecs;
		अगर (!host->घातerup_msecs || host->घातerup_msecs > 250)
			host->घातerup_msecs = 250;
	पूर्ण

	/* pपुनः_स्मृतिate dma buffers */
	host->data = kदो_स्मृति(माप(*host->data), GFP_KERNEL);
	अगर (!host->data)
		जाओ fail_nobuf1;

	status = mmc_spi_dma_alloc(host);
	अगर (status)
		जाओ fail_dma;

	/* setup message क्रम status/busy पढ़ोback */
	spi_message_init(&host->पढ़ोback);
	host->पढ़ोback.is_dma_mapped = (host->dma_dev != शून्य);

	spi_message_add_tail(&host->status, &host->पढ़ोback);
	host->status.tx_buf = host->ones;
	host->status.tx_dma = host->ones_dma;
	host->status.rx_buf = &host->data->status;
	host->status.rx_dma = host->data_dma + दुरत्व(काष्ठा scratch, status);
	host->status.cs_change = 1;

	/* रेजिस्टर card detect irq */
	अगर (host->pdata && host->pdata->init) अणु
		status = host->pdata->init(&spi->dev, mmc_spi_detect_irq, mmc);
		अगर (status != 0)
			जाओ fail_glue_init;
	पूर्ण

	/* pass platक्रमm capabilities, अगर any */
	अगर (host->pdata) अणु
		mmc->caps |= host->pdata->caps;
		mmc->caps2 |= host->pdata->caps2;
	पूर्ण

	status = mmc_add_host(mmc);
	अगर (status != 0)
		जाओ fail_add_host;

	/*
	 * Index 0 is card detect
	 * Old boardfiles were specअगरying 1 ms as debounce
	 */
	status = mmc_gpiod_request_cd(mmc, शून्य, 0, false, 1000);
	अगर (status == -EPROBE_DEFER)
		जाओ fail_add_host;
	अगर (!status) अणु
		/*
		 * The platक्रमm has a CD GPIO संकेत that may support
		 * पूर्णांकerrupts, so let mmc_gpiod_request_cd_irq() decide
		 * अगर polling is needed or not.
		 */
		mmc->caps &= ~MMC_CAP_NEEDS_POLL;
		mmc_gpiod_request_cd_irq(mmc);
	पूर्ण
	mmc_detect_change(mmc, 0);

	/* Index 1 is ग_लिखो protect/पढ़ो only */
	status = mmc_gpiod_request_ro(mmc, शून्य, 1, 0);
	अगर (status == -EPROBE_DEFER)
		जाओ fail_add_host;
	अगर (!status)
		has_ro = true;

	dev_info(&spi->dev, "SD/MMC host %s%s%s%s%s\n",
			dev_name(&mmc->class_dev),
			host->dma_dev ? "" : ", no DMA",
			has_ro ? "" : ", no WP",
			(host->pdata && host->pdata->setघातer)
				? "" : ", no poweroff",
			(mmc->caps & MMC_CAP_NEEDS_POLL)
				? ", cd polling" : "");
	वापस 0;

fail_add_host:
	mmc_हटाओ_host(mmc);
fail_glue_init:
	mmc_spi_dma_मुक्त(host);
fail_dma:
	kमुक्त(host->data);
fail_nobuf1:
	mmc_spi_put_pdata(spi);
	mmc_मुक्त_host(mmc);
nomem:
	kमुक्त(ones);
	वापस status;
पूर्ण


अटल पूर्णांक mmc_spi_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा mmc_host		*mmc = dev_get_drvdata(&spi->dev);
	काष्ठा mmc_spi_host	*host = mmc_priv(mmc);

	/* prevent new mmc_detect_change() calls */
	अगर (host->pdata && host->pdata->निकास)
		host->pdata->निकास(&spi->dev, mmc);

	mmc_हटाओ_host(mmc);

	mmc_spi_dma_मुक्त(host);
	kमुक्त(host->data);
	kमुक्त(host->ones);

	spi->max_speed_hz = mmc->f_max;
	mmc_spi_put_pdata(spi);
	mmc_मुक्त_host(mmc);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id mmc_spi_of_match_table[] = अणु
	अणु .compatible = "mmc-spi-slot", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, mmc_spi_of_match_table);

अटल काष्ठा spi_driver mmc_spi_driver = अणु
	.driver = अणु
		.name =		"mmc_spi",
		.of_match_table = mmc_spi_of_match_table,
	पूर्ण,
	.probe =	mmc_spi_probe,
	.हटाओ =	mmc_spi_हटाओ,
पूर्ण;

module_spi_driver(mmc_spi_driver);

MODULE_AUTHOR("Mike Lavender, David Brownell, Hans-Peter Nilsson, Jan Nikitenko");
MODULE_DESCRIPTION("SPI SD/MMC host driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("spi:mmc_spi");
