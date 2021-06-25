<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  linux/include/linux/mmc/core.h
 */
#अगर_अघोषित LINUX_MMC_CORE_H
#घोषणा LINUX_MMC_CORE_H

#समावेश <linux/completion.h>
#समावेश <linux/types.h>

काष्ठा mmc_data;
काष्ठा mmc_request;

क्रमागत mmc_blk_status अणु
	MMC_BLK_SUCCESS = 0,
	MMC_BLK_PARTIAL,
	MMC_BLK_CMD_ERR,
	MMC_BLK_RETRY,
	MMC_BLK_ABORT,
	MMC_BLK_DATA_ERR,
	MMC_BLK_ECC_ERR,
	MMC_BLK_NOMEDIUM,
	MMC_BLK_NEW_REQUEST,
पूर्ण;

काष्ठा mmc_command अणु
	u32			opcode;
	u32			arg;
#घोषणा MMC_CMD23_ARG_REL_WR	(1 << 31)
#घोषणा MMC_CMD23_ARG_PACKED	((0 << 31) | (1 << 30))
#घोषणा MMC_CMD23_ARG_TAG_REQ	(1 << 29)
	u32			resp[4];
	अचिन्हित पूर्णांक		flags;		/* expected response type */
#घोषणा MMC_RSP_PRESENT	(1 << 0)
#घोषणा MMC_RSP_136	(1 << 1)		/* 136 bit response */
#घोषणा MMC_RSP_CRC	(1 << 2)		/* expect valid crc */
#घोषणा MMC_RSP_BUSY	(1 << 3)		/* card may send busy */
#घोषणा MMC_RSP_OPCODE	(1 << 4)		/* response contains opcode */

#घोषणा MMC_CMD_MASK	(3 << 5)		/* non-SPI command type */
#घोषणा MMC_CMD_AC	(0 << 5)
#घोषणा MMC_CMD_ADTC	(1 << 5)
#घोषणा MMC_CMD_BC	(2 << 5)
#घोषणा MMC_CMD_BCR	(3 << 5)

#घोषणा MMC_RSP_SPI_S1	(1 << 7)		/* one status byte */
#घोषणा MMC_RSP_SPI_S2	(1 << 8)		/* second byte */
#घोषणा MMC_RSP_SPI_B4	(1 << 9)		/* four data bytes */
#घोषणा MMC_RSP_SPI_BUSY (1 << 10)		/* card may send busy */

/*
 * These are the native response types, and correspond to valid bit
 * patterns of the above flags.  One additional valid pattern
 * is all zeros, which means we करोn't expect a response.
 */
#घोषणा MMC_RSP_NONE	(0)
#घोषणा MMC_RSP_R1	(MMC_RSP_PRESENT|MMC_RSP_CRC|MMC_RSP_OPCODE)
#घोषणा MMC_RSP_R1B	(MMC_RSP_PRESENT|MMC_RSP_CRC|MMC_RSP_OPCODE|MMC_RSP_BUSY)
#घोषणा MMC_RSP_R2	(MMC_RSP_PRESENT|MMC_RSP_136|MMC_RSP_CRC)
#घोषणा MMC_RSP_R3	(MMC_RSP_PRESENT)
#घोषणा MMC_RSP_R4	(MMC_RSP_PRESENT)
#घोषणा MMC_RSP_R5	(MMC_RSP_PRESENT|MMC_RSP_CRC|MMC_RSP_OPCODE)
#घोषणा MMC_RSP_R6	(MMC_RSP_PRESENT|MMC_RSP_CRC|MMC_RSP_OPCODE)
#घोषणा MMC_RSP_R7	(MMC_RSP_PRESENT|MMC_RSP_CRC|MMC_RSP_OPCODE)

/* Can be used by core to poll after चयन to MMC HS mode */
#घोषणा MMC_RSP_R1_NO_CRC	(MMC_RSP_PRESENT|MMC_RSP_OPCODE)

#घोषणा mmc_resp_type(cmd)	((cmd)->flags & (MMC_RSP_PRESENT|MMC_RSP_136|MMC_RSP_CRC|MMC_RSP_BUSY|MMC_RSP_OPCODE))

/*
 * These are the SPI response types क्रम MMC, SD, and SDIO cards.
 * Commands वापस R1, with maybe more info.  Zero is an error type;
 * callers must always provide the appropriate MMC_RSP_SPI_Rx flags.
 */
#घोषणा MMC_RSP_SPI_R1	(MMC_RSP_SPI_S1)
#घोषणा MMC_RSP_SPI_R1B	(MMC_RSP_SPI_S1|MMC_RSP_SPI_BUSY)
#घोषणा MMC_RSP_SPI_R2	(MMC_RSP_SPI_S1|MMC_RSP_SPI_S2)
#घोषणा MMC_RSP_SPI_R3	(MMC_RSP_SPI_S1|MMC_RSP_SPI_B4)
#घोषणा MMC_RSP_SPI_R4	(MMC_RSP_SPI_S1|MMC_RSP_SPI_B4)
#घोषणा MMC_RSP_SPI_R5	(MMC_RSP_SPI_S1|MMC_RSP_SPI_S2)
#घोषणा MMC_RSP_SPI_R7	(MMC_RSP_SPI_S1|MMC_RSP_SPI_B4)

#घोषणा mmc_spi_resp_type(cmd)	((cmd)->flags & \
		(MMC_RSP_SPI_S1|MMC_RSP_SPI_BUSY|MMC_RSP_SPI_S2|MMC_RSP_SPI_B4))

/*
 * These are the command types.
 */
#घोषणा mmc_cmd_type(cmd)	((cmd)->flags & MMC_CMD_MASK)

	अचिन्हित पूर्णांक		retries;	/* max number of retries */
	पूर्णांक			error;		/* command error */

/*
 * Standard त्रुटि_सं values are used क्रम errors, but some have specअगरic
 * meaning in the MMC layer:
 *
 * ETIMEDOUT    Card took too दीर्घ to respond
 * EILSEQ       Basic क्रमmat problem with the received or sent data
 *              (e.g. CRC check failed, incorrect opcode in response
 *              or bad end bit)
 * EINVAL       Request cannot be perक्रमmed because of restrictions
 *              in hardware and/or the driver
 * ENOMEDIUM    Host can determine that the slot is empty and is
 *              actively failing requests
 */

	अचिन्हित पूर्णांक		busy_समयout;	/* busy detect समयout in ms */
	काष्ठा mmc_data		*data;		/* data segment associated with cmd */
	काष्ठा mmc_request	*mrq;		/* associated request */
पूर्ण;

काष्ठा mmc_data अणु
	अचिन्हित पूर्णांक		समयout_ns;	/* data समयout (in ns, max 80ms) */
	अचिन्हित पूर्णांक		समयout_clks;	/* data समयout (in घड़ीs) */
	अचिन्हित पूर्णांक		blksz;		/* data block size */
	अचिन्हित पूर्णांक		blocks;		/* number of blocks */
	अचिन्हित पूर्णांक		blk_addr;	/* block address */
	पूर्णांक			error;		/* data error */
	अचिन्हित पूर्णांक		flags;

#घोषणा MMC_DATA_WRITE		BIT(8)
#घोषणा MMC_DATA_READ		BIT(9)
/* Extra flags used by CQE */
#घोषणा MMC_DATA_QBR		BIT(10)		/* CQE queue barrier*/
#घोषणा MMC_DATA_PRIO		BIT(11)		/* CQE high priority */
#घोषणा MMC_DATA_REL_WR		BIT(12)		/* Reliable ग_लिखो */
#घोषणा MMC_DATA_DAT_TAG	BIT(13)		/* Tag request */
#घोषणा MMC_DATA_FORCED_PRG	BIT(14)		/* Forced programming */

	अचिन्हित पूर्णांक		bytes_xfered;

	काष्ठा mmc_command	*stop;		/* stop command */
	काष्ठा mmc_request	*mrq;		/* associated request */

	अचिन्हित पूर्णांक		sg_len;		/* size of scatter list */
	पूर्णांक			sg_count;	/* mapped sg entries */
	काष्ठा scatterlist	*sg;		/* I/O scatter list */
	s32			host_cookie;	/* host निजी data */
पूर्ण;

काष्ठा mmc_host;
काष्ठा mmc_request अणु
	काष्ठा mmc_command	*sbc;		/* SET_BLOCK_COUNT क्रम multiblock */
	काष्ठा mmc_command	*cmd;
	काष्ठा mmc_data		*data;
	काष्ठा mmc_command	*stop;

	काष्ठा completion	completion;
	काष्ठा completion	cmd_completion;
	व्योम			(*करोne)(काष्ठा mmc_request *);/* completion function */
	/*
	 * Notअगरy uppers layers (e.g. mmc block driver) that recovery is needed
	 * due to an error associated with the mmc_request. Currently used only
	 * by CQE.
	 */
	व्योम			(*recovery_notअगरier)(काष्ठा mmc_request *);
	काष्ठा mmc_host		*host;

	/* Allow other commands during this ongoing data transfer or busy रुको */
	bool			cap_cmd_during_tfr;

	पूर्णांक			tag;

#अगर_घोषित CONFIG_MMC_CRYPTO
	bool			crypto_enabled;
	पूर्णांक			crypto_key_slot;
	u32			data_unit_num;
#पूर्ण_अगर
पूर्ण;

काष्ठा mmc_card;

व्योम mmc_रुको_क्रम_req(काष्ठा mmc_host *host, काष्ठा mmc_request *mrq);
पूर्णांक mmc_रुको_क्रम_cmd(काष्ठा mmc_host *host, काष्ठा mmc_command *cmd,
		पूर्णांक retries);

पूर्णांक mmc_hw_reset(काष्ठा mmc_host *host);
पूर्णांक mmc_sw_reset(काष्ठा mmc_host *host);
व्योम mmc_set_data_समयout(काष्ठा mmc_data *data, स्थिर काष्ठा mmc_card *card);

#पूर्ण_अगर /* LINUX_MMC_CORE_H */
