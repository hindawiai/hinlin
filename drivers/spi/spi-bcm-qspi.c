<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Driver क्रम Broadcom BRCMSTB, NSP,  NS2, Cygnus SPI Controllers
 *
 * Copyright 2016 Broadcom
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/ioport.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/spi/spi-स्मृति.स>
#समावेश <linux/sysfs.h>
#समावेश <linux/types.h>
#समावेश "spi-bcm-qspi.h"

#घोषणा DRIVER_NAME "bcm_qspi"


/* BSPI रेजिस्टर offsets */
#घोषणा BSPI_REVISION_ID			0x000
#घोषणा BSPI_SCRATCH				0x004
#घोषणा BSPI_MAST_N_BOOT_CTRL			0x008
#घोषणा BSPI_BUSY_STATUS			0x00c
#घोषणा BSPI_INTR_STATUS			0x010
#घोषणा BSPI_B0_STATUS				0x014
#घोषणा BSPI_B0_CTRL				0x018
#घोषणा BSPI_B1_STATUS				0x01c
#घोषणा BSPI_B1_CTRL				0x020
#घोषणा BSPI_STRAP_OVERRIDE_CTRL		0x024
#घोषणा BSPI_FLEX_MODE_ENABLE			0x028
#घोषणा BSPI_BITS_PER_CYCLE			0x02c
#घोषणा BSPI_BITS_PER_PHASE			0x030
#घोषणा BSPI_CMD_AND_MODE_BYTE			0x034
#घोषणा BSPI_BSPI_FLASH_UPPER_ADDR_BYTE	0x038
#घोषणा BSPI_BSPI_XOR_VALUE			0x03c
#घोषणा BSPI_BSPI_XOR_ENABLE			0x040
#घोषणा BSPI_BSPI_PIO_MODE_ENABLE		0x044
#घोषणा BSPI_BSPI_PIO_IOसूची			0x048
#घोषणा BSPI_BSPI_PIO_DATA			0x04c

/* RAF रेजिस्टर offsets */
#घोषणा BSPI_RAF_START_ADDR			0x100
#घोषणा BSPI_RAF_NUM_WORDS			0x104
#घोषणा BSPI_RAF_CTRL				0x108
#घोषणा BSPI_RAF_FULLNESS			0x10c
#घोषणा BSPI_RAF_WATERMARK			0x110
#घोषणा BSPI_RAF_STATUS			0x114
#घोषणा BSPI_RAF_READ_DATA			0x118
#घोषणा BSPI_RAF_WORD_CNT			0x11c
#घोषणा BSPI_RAF_CURR_ADDR			0x120

/* Override mode masks */
#घोषणा BSPI_STRAP_OVERRIDE_CTRL_OVERRIDE	BIT(0)
#घोषणा BSPI_STRAP_OVERRIDE_CTRL_DATA_DUAL	BIT(1)
#घोषणा BSPI_STRAP_OVERRIDE_CTRL_ADDR_4BYTE	BIT(2)
#घोषणा BSPI_STRAP_OVERRIDE_CTRL_DATA_QUAD	BIT(3)
#घोषणा BSPI_STRAP_OVERRIDE_CTRL_ENDAIN_MODE	BIT(4)

#घोषणा BSPI_ADDRLEN_3BYTES			3
#घोषणा BSPI_ADDRLEN_4BYTES			4

#घोषणा BSPI_RAF_STATUS_FIFO_EMPTY_MASK	BIT(1)

#घोषणा BSPI_RAF_CTRL_START_MASK		BIT(0)
#घोषणा BSPI_RAF_CTRL_CLEAR_MASK		BIT(1)

#घोषणा BSPI_BPP_MODE_SELECT_MASK		BIT(8)
#घोषणा BSPI_BPP_ADDR_SELECT_MASK		BIT(16)

#घोषणा BSPI_READ_LENGTH			256

/* MSPI रेजिस्टर offsets */
#घोषणा MSPI_SPCR0_LSB				0x000
#घोषणा MSPI_SPCR0_MSB				0x004
#घोषणा MSPI_SPCR1_LSB				0x008
#घोषणा MSPI_SPCR1_MSB				0x00c
#घोषणा MSPI_NEWQP				0x010
#घोषणा MSPI_ENDQP				0x014
#घोषणा MSPI_SPCR2				0x018
#घोषणा MSPI_MSPI_STATUS			0x020
#घोषणा MSPI_CPTQP				0x024
#घोषणा MSPI_SPCR3				0x028
#घोषणा MSPI_REV				0x02c
#घोषणा MSPI_TXRAM				0x040
#घोषणा MSPI_RXRAM				0x0c0
#घोषणा MSPI_CDRAM				0x140
#घोषणा MSPI_WRITE_LOCK			0x180

#घोषणा MSPI_MASTER_BIT			BIT(7)

#घोषणा MSPI_NUM_CDRAM				16
#घोषणा MSPI_CDRAM_CONT_BIT			BIT(7)
#घोषणा MSPI_CDRAM_BITSE_BIT			BIT(6)
#घोषणा MSPI_CDRAM_PCS				0xf

#घोषणा MSPI_SPCR2_SPE				BIT(6)
#घोषणा MSPI_SPCR2_CONT_AFTER_CMD		BIT(7)

#घोषणा MSPI_SPCR3_FASTBR			BIT(0)
#घोषणा MSPI_SPCR3_FASTDT			BIT(1)
#घोषणा MSPI_SPCR3_SYSCLKSEL_MASK		GENMASK(11, 10)
#घोषणा MSPI_SPCR3_SYSCLKSEL_27			(MSPI_SPCR3_SYSCLKSEL_MASK & \
						 ~(BIT(10) | BIT(11)))
#घोषणा MSPI_SPCR3_SYSCLKSEL_108		(MSPI_SPCR3_SYSCLKSEL_MASK & \
						 BIT(11))

#घोषणा MSPI_MSPI_STATUS_SPIF			BIT(0)

#घोषणा INTR_BASE_BIT_SHIFT			0x02
#घोषणा INTR_COUNT				0x07

#घोषणा NUM_CHIPSELECT				4
#घोषणा QSPI_SPBR_MAX				255U
#घोषणा MSPI_BASE_FREQ				27000000UL

#घोषणा OPCODE_DIOR				0xBB
#घोषणा OPCODE_QIOR				0xEB
#घोषणा OPCODE_DIOR_4B				0xBC
#घोषणा OPCODE_QIOR_4B				0xEC

#घोषणा MAX_CMD_SIZE				6

#घोषणा ADDR_4MB_MASK				GENMASK(22, 0)

/* stop at end of transfer, no other reason */
#घोषणा TRANS_STATUS_BREAK_NONE		0
/* stop at end of spi_message */
#घोषणा TRANS_STATUS_BREAK_EOM			1
/* stop at end of spi_transfer अगर delay */
#घोषणा TRANS_STATUS_BREAK_DELAY		2
/* stop at end of spi_transfer अगर cs_change */
#घोषणा TRANS_STATUS_BREAK_CS_CHANGE		4
/* stop अगर we run out of bytes */
#घोषणा TRANS_STATUS_BREAK_NO_BYTES		8

/* events that make us stop filling TX slots */
#घोषणा TRANS_STATUS_BREAK_TX (TRANS_STATUS_BREAK_EOM |		\
			       TRANS_STATUS_BREAK_DELAY |		\
			       TRANS_STATUS_BREAK_CS_CHANGE)

/* events that make us deनिश्चित CS */
#घोषणा TRANS_STATUS_BREAK_DESELECT (TRANS_STATUS_BREAK_EOM |		\
				     TRANS_STATUS_BREAK_CS_CHANGE)

काष्ठा bcm_qspi_parms अणु
	u32 speed_hz;
	u8 mode;
	u8 bits_per_word;
पूर्ण;

काष्ठा bcm_xfer_mode अणु
	bool flex_mode;
	अचिन्हित पूर्णांक width;
	अचिन्हित पूर्णांक addrlen;
	अचिन्हित पूर्णांक hp;
पूर्ण;

क्रमागत base_type अणु
	MSPI,
	BSPI,
	CHIP_SELECT,
	BASEMAX,
पूर्ण;

क्रमागत irq_source अणु
	SINGLE_L2,
	MUXED_L1,
पूर्ण;

काष्ठा bcm_qspi_irq अणु
	स्थिर अक्षर *irq_name;
	स्थिर irq_handler_t irq_handler;
	पूर्णांक irq_source;
	u32 mask;
पूर्ण;

काष्ठा bcm_qspi_dev_id अणु
	स्थिर काष्ठा bcm_qspi_irq *irqp;
	व्योम *dev;
पूर्ण;


काष्ठा qspi_trans अणु
	काष्ठा spi_transfer *trans;
	पूर्णांक byte;
	bool mspi_last_trans;
पूर्ण;

काष्ठा bcm_qspi अणु
	काष्ठा platक्रमm_device *pdev;
	काष्ठा spi_master *master;
	काष्ठा clk *clk;
	u32 base_clk;
	u32 max_speed_hz;
	व्योम __iomem *base[BASEMAX];

	/* Some SoCs provide custom पूर्णांकerrupt status रेजिस्टर(s) */
	काष्ठा bcm_qspi_soc_पूर्णांकc	*soc_पूर्णांकc;

	काष्ठा bcm_qspi_parms last_parms;
	काष्ठा qspi_trans  trans_pos;
	पूर्णांक curr_cs;
	पूर्णांक bspi_maj_rev;
	पूर्णांक bspi_min_rev;
	पूर्णांक bspi_enabled;
	स्थिर काष्ठा spi_mem_op *bspi_rf_op;
	u32 bspi_rf_op_idx;
	u32 bspi_rf_op_len;
	u32 bspi_rf_op_status;
	काष्ठा bcm_xfer_mode xfer_mode;
	u32 s3_strap_override_ctrl;
	bool bspi_mode;
	bool big_endian;
	पूर्णांक num_irqs;
	काष्ठा bcm_qspi_dev_id *dev_ids;
	काष्ठा completion mspi_करोne;
	काष्ठा completion bspi_करोne;
	u8 mspi_maj_rev;
	u8 mspi_min_rev;
	bool mspi_spcr3_sysclk;
पूर्ण;

अटल अंतरभूत bool has_bspi(काष्ठा bcm_qspi *qspi)
अणु
	वापस qspi->bspi_mode;
पूर्ण

/* hardware supports spcr3 and fast baud-rate  */
अटल अंतरभूत bool bcm_qspi_has_fastbr(काष्ठा bcm_qspi *qspi)
अणु
	अगर (!has_bspi(qspi) &&
	    ((qspi->mspi_maj_rev >= 1) &&
	     (qspi->mspi_min_rev >= 5)))
		वापस true;

	वापस false;
पूर्ण

/* hardware supports sys clk 108Mhz  */
अटल अंतरभूत bool bcm_qspi_has_sysclk_108(काष्ठा bcm_qspi *qspi)
अणु
	अगर (!has_bspi(qspi) && (qspi->mspi_spcr3_sysclk ||
	    ((qspi->mspi_maj_rev >= 1) &&
	     (qspi->mspi_min_rev >= 6))))
		वापस true;

	वापस false;
पूर्ण

अटल अंतरभूत पूर्णांक bcm_qspi_spbr_min(काष्ठा bcm_qspi *qspi)
अणु
	अगर (bcm_qspi_has_fastbr(qspi))
		वापस 1;
	अन्यथा
		वापस 8;
पूर्ण

/* Read qspi controller रेजिस्टर*/
अटल अंतरभूत u32 bcm_qspi_पढ़ो(काष्ठा bcm_qspi *qspi, क्रमागत base_type type,
				अचिन्हित पूर्णांक offset)
अणु
	वापस bcm_qspi_पढ़ोl(qspi->big_endian, qspi->base[type] + offset);
पूर्ण

/* Write qspi controller रेजिस्टर*/
अटल अंतरभूत व्योम bcm_qspi_ग_लिखो(काष्ठा bcm_qspi *qspi, क्रमागत base_type type,
				  अचिन्हित पूर्णांक offset, अचिन्हित पूर्णांक data)
अणु
	bcm_qspi_ग_लिखोl(qspi->big_endian, data, qspi->base[type] + offset);
पूर्ण

/* BSPI helpers */
अटल पूर्णांक bcm_qspi_bspi_busy_poll(काष्ठा bcm_qspi *qspi)
अणु
	पूर्णांक i;

	/* this should normally finish within 10us */
	क्रम (i = 0; i < 1000; i++) अणु
		अगर (!(bcm_qspi_पढ़ो(qspi, BSPI, BSPI_BUSY_STATUS) & 1))
			वापस 0;
		udelay(1);
	पूर्ण
	dev_warn(&qspi->pdev->dev, "timeout waiting for !busy_status\n");
	वापस -EIO;
पूर्ण

अटल अंतरभूत bool bcm_qspi_bspi_ver_three(काष्ठा bcm_qspi *qspi)
अणु
	अगर (qspi->bspi_maj_rev < 4)
		वापस true;
	वापस false;
पूर्ण

अटल व्योम bcm_qspi_bspi_flush_prefetch_buffers(काष्ठा bcm_qspi *qspi)
अणु
	bcm_qspi_bspi_busy_poll(qspi);
	/* Force rising edge क्रम the b0/b1 'flush' field */
	bcm_qspi_ग_लिखो(qspi, BSPI, BSPI_B0_CTRL, 1);
	bcm_qspi_ग_लिखो(qspi, BSPI, BSPI_B1_CTRL, 1);
	bcm_qspi_ग_लिखो(qspi, BSPI, BSPI_B0_CTRL, 0);
	bcm_qspi_ग_लिखो(qspi, BSPI, BSPI_B1_CTRL, 0);
पूर्ण

अटल पूर्णांक bcm_qspi_bspi_lr_is_fअगरo_empty(काष्ठा bcm_qspi *qspi)
अणु
	वापस (bcm_qspi_पढ़ो(qspi, BSPI, BSPI_RAF_STATUS) &
				BSPI_RAF_STATUS_FIFO_EMPTY_MASK);
पूर्ण

अटल अंतरभूत u32 bcm_qspi_bspi_lr_पढ़ो_fअगरo(काष्ठा bcm_qspi *qspi)
अणु
	u32 data = bcm_qspi_पढ़ो(qspi, BSPI, BSPI_RAF_READ_DATA);

	/* BSPI v3 LR is LE only, convert data to host endianness */
	अगर (bcm_qspi_bspi_ver_three(qspi))
		data = le32_to_cpu(data);

	वापस data;
पूर्ण

अटल अंतरभूत व्योम bcm_qspi_bspi_lr_start(काष्ठा bcm_qspi *qspi)
अणु
	bcm_qspi_bspi_busy_poll(qspi);
	bcm_qspi_ग_लिखो(qspi, BSPI, BSPI_RAF_CTRL,
		       BSPI_RAF_CTRL_START_MASK);
पूर्ण

अटल अंतरभूत व्योम bcm_qspi_bspi_lr_clear(काष्ठा bcm_qspi *qspi)
अणु
	bcm_qspi_ग_लिखो(qspi, BSPI, BSPI_RAF_CTRL,
		       BSPI_RAF_CTRL_CLEAR_MASK);
	bcm_qspi_bspi_flush_prefetch_buffers(qspi);
पूर्ण

अटल व्योम bcm_qspi_bspi_lr_data_पढ़ो(काष्ठा bcm_qspi *qspi)
अणु
	u32 *buf = (u32 *)qspi->bspi_rf_op->data.buf.in;
	u32 data = 0;

	dev_dbg(&qspi->pdev->dev, "xfer %p rx %p rxlen %d\n", qspi->bspi_rf_op,
		qspi->bspi_rf_op->data.buf.in, qspi->bspi_rf_op_len);
	जबतक (!bcm_qspi_bspi_lr_is_fअगरo_empty(qspi)) अणु
		data = bcm_qspi_bspi_lr_पढ़ो_fअगरo(qspi);
		अगर (likely(qspi->bspi_rf_op_len >= 4) &&
		    IS_ALIGNED((uपूर्णांकptr_t)buf, 4)) अणु
			buf[qspi->bspi_rf_op_idx++] = data;
			qspi->bspi_rf_op_len -= 4;
		पूर्ण अन्यथा अणु
			/* Read out reमुख्यing bytes, make sure*/
			u8 *cbuf = (u8 *)&buf[qspi->bspi_rf_op_idx];

			data = cpu_to_le32(data);
			जबतक (qspi->bspi_rf_op_len) अणु
				*cbuf++ = (u8)data;
				data >>= 8;
				qspi->bspi_rf_op_len--;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम bcm_qspi_bspi_set_xfer_params(काष्ठा bcm_qspi *qspi, u8 cmd_byte,
					  पूर्णांक bpp, पूर्णांक bpc, पूर्णांक flex_mode)
अणु
	bcm_qspi_ग_लिखो(qspi, BSPI, BSPI_FLEX_MODE_ENABLE, 0);
	bcm_qspi_ग_लिखो(qspi, BSPI, BSPI_BITS_PER_CYCLE, bpc);
	bcm_qspi_ग_लिखो(qspi, BSPI, BSPI_BITS_PER_PHASE, bpp);
	bcm_qspi_ग_लिखो(qspi, BSPI, BSPI_CMD_AND_MODE_BYTE, cmd_byte);
	bcm_qspi_ग_लिखो(qspi, BSPI, BSPI_FLEX_MODE_ENABLE, flex_mode);
पूर्ण

अटल पूर्णांक bcm_qspi_bspi_set_flex_mode(काष्ठा bcm_qspi *qspi,
				       स्थिर काष्ठा spi_mem_op *op, पूर्णांक hp)
अणु
	पूर्णांक bpc = 0, bpp = 0;
	u8 command = op->cmd.opcode;
	पूर्णांक width = op->data.buswidth ? op->data.buswidth : SPI_NBITS_SINGLE;
	पूर्णांक addrlen = op->addr.nbytes;
	पूर्णांक flex_mode = 1;

	dev_dbg(&qspi->pdev->dev, "set flex mode w %x addrlen %x hp %d\n",
		width, addrlen, hp);

	अगर (addrlen == BSPI_ADDRLEN_4BYTES)
		bpp = BSPI_BPP_ADDR_SELECT_MASK;

	bpp |= (op->dummy.nbytes * 8) / op->dummy.buswidth;

	चयन (width) अणु
	हाल SPI_NBITS_SINGLE:
		अगर (addrlen == BSPI_ADDRLEN_3BYTES)
			/* शेष mode, करोes not need flex_cmd */
			flex_mode = 0;
		अवरोध;
	हाल SPI_NBITS_DUAL:
		bpc = 0x00000001;
		अगर (hp) अणु
			bpc |= 0x00010100; /* address and mode are 2-bit */
			bpp = BSPI_BPP_MODE_SELECT_MASK;
		पूर्ण
		अवरोध;
	हाल SPI_NBITS_QUAD:
		bpc = 0x00000002;
		अगर (hp) अणु
			bpc |= 0x00020200; /* address and mode are 4-bit */
			bpp |= BSPI_BPP_MODE_SELECT_MASK;
		पूर्ण
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	bcm_qspi_bspi_set_xfer_params(qspi, command, bpp, bpc, flex_mode);

	वापस 0;
पूर्ण

अटल पूर्णांक bcm_qspi_bspi_set_override(काष्ठा bcm_qspi *qspi,
				      स्थिर काष्ठा spi_mem_op *op, पूर्णांक hp)
अणु
	पूर्णांक width = op->data.buswidth ? op->data.buswidth : SPI_NBITS_SINGLE;
	पूर्णांक addrlen = op->addr.nbytes;
	u32 data = bcm_qspi_पढ़ो(qspi, BSPI, BSPI_STRAP_OVERRIDE_CTRL);

	dev_dbg(&qspi->pdev->dev, "set override mode w %x addrlen %x hp %d\n",
		width, addrlen, hp);

	चयन (width) अणु
	हाल SPI_NBITS_SINGLE:
		/* clear quad/dual mode */
		data &= ~(BSPI_STRAP_OVERRIDE_CTRL_DATA_QUAD |
			  BSPI_STRAP_OVERRIDE_CTRL_DATA_DUAL);
		अवरोध;
	हाल SPI_NBITS_QUAD:
		/* clear dual mode and set quad mode */
		data &= ~BSPI_STRAP_OVERRIDE_CTRL_DATA_DUAL;
		data |= BSPI_STRAP_OVERRIDE_CTRL_DATA_QUAD;
		अवरोध;
	हाल SPI_NBITS_DUAL:
		/* clear quad mode set dual mode */
		data &= ~BSPI_STRAP_OVERRIDE_CTRL_DATA_QUAD;
		data |= BSPI_STRAP_OVERRIDE_CTRL_DATA_DUAL;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (addrlen == BSPI_ADDRLEN_4BYTES)
		/* set 4byte mode*/
		data |= BSPI_STRAP_OVERRIDE_CTRL_ADDR_4BYTE;
	अन्यथा
		/* clear 4 byte mode */
		data &= ~BSPI_STRAP_OVERRIDE_CTRL_ADDR_4BYTE;

	/* set the override mode */
	data |=	BSPI_STRAP_OVERRIDE_CTRL_OVERRIDE;
	bcm_qspi_ग_लिखो(qspi, BSPI, BSPI_STRAP_OVERRIDE_CTRL, data);
	bcm_qspi_bspi_set_xfer_params(qspi, op->cmd.opcode, 0, 0, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक bcm_qspi_bspi_set_mode(काष्ठा bcm_qspi *qspi,
				  स्थिर काष्ठा spi_mem_op *op, पूर्णांक hp)
अणु
	पूर्णांक error = 0;
	पूर्णांक width = op->data.buswidth ? op->data.buswidth : SPI_NBITS_SINGLE;
	पूर्णांक addrlen = op->addr.nbytes;

	/* शेष mode */
	qspi->xfer_mode.flex_mode = true;

	अगर (!bcm_qspi_bspi_ver_three(qspi)) अणु
		u32 val, mask;

		val = bcm_qspi_पढ़ो(qspi, BSPI, BSPI_STRAP_OVERRIDE_CTRL);
		mask = BSPI_STRAP_OVERRIDE_CTRL_OVERRIDE;
		अगर (val & mask || qspi->s3_strap_override_ctrl & mask) अणु
			qspi->xfer_mode.flex_mode = false;
			bcm_qspi_ग_लिखो(qspi, BSPI, BSPI_FLEX_MODE_ENABLE, 0);
			error = bcm_qspi_bspi_set_override(qspi, op, hp);
		पूर्ण
	पूर्ण

	अगर (qspi->xfer_mode.flex_mode)
		error = bcm_qspi_bspi_set_flex_mode(qspi, op, hp);

	अगर (error) अणु
		dev_warn(&qspi->pdev->dev,
			 "INVALID COMBINATION: width=%d addrlen=%d hp=%d\n",
			 width, addrlen, hp);
	पूर्ण अन्यथा अगर (qspi->xfer_mode.width != width ||
		   qspi->xfer_mode.addrlen != addrlen ||
		   qspi->xfer_mode.hp != hp) अणु
		qspi->xfer_mode.width = width;
		qspi->xfer_mode.addrlen = addrlen;
		qspi->xfer_mode.hp = hp;
		dev_dbg(&qspi->pdev->dev,
			"cs:%d %d-lane output, %d-byte address%s\n",
			qspi->curr_cs,
			qspi->xfer_mode.width,
			qspi->xfer_mode.addrlen,
			qspi->xfer_mode.hp != -1 ? ", hp mode" : "");
	पूर्ण

	वापस error;
पूर्ण

अटल व्योम bcm_qspi_enable_bspi(काष्ठा bcm_qspi *qspi)
अणु
	अगर (!has_bspi(qspi))
		वापस;

	qspi->bspi_enabled = 1;
	अगर ((bcm_qspi_पढ़ो(qspi, BSPI, BSPI_MAST_N_BOOT_CTRL) & 1) == 0)
		वापस;

	bcm_qspi_bspi_flush_prefetch_buffers(qspi);
	udelay(1);
	bcm_qspi_ग_लिखो(qspi, BSPI, BSPI_MAST_N_BOOT_CTRL, 0);
	udelay(1);
पूर्ण

अटल व्योम bcm_qspi_disable_bspi(काष्ठा bcm_qspi *qspi)
अणु
	अगर (!has_bspi(qspi))
		वापस;

	qspi->bspi_enabled = 0;
	अगर ((bcm_qspi_पढ़ो(qspi, BSPI, BSPI_MAST_N_BOOT_CTRL) & 1))
		वापस;

	bcm_qspi_bspi_busy_poll(qspi);
	bcm_qspi_ग_लिखो(qspi, BSPI, BSPI_MAST_N_BOOT_CTRL, 1);
	udelay(1);
पूर्ण

अटल व्योम bcm_qspi_chip_select(काष्ठा bcm_qspi *qspi, पूर्णांक cs)
अणु
	u32 rd = 0;
	u32 wr = 0;

	अगर (qspi->base[CHIP_SELECT]) अणु
		rd = bcm_qspi_पढ़ो(qspi, CHIP_SELECT, 0);
		wr = (rd & ~0xff) | (1 << cs);
		अगर (rd == wr)
			वापस;
		bcm_qspi_ग_लिखो(qspi, CHIP_SELECT, 0, wr);
		usleep_range(10, 20);
	पूर्ण

	dev_dbg(&qspi->pdev->dev, "using cs:%d\n", cs);
	qspi->curr_cs = cs;
पूर्ण

/* MSPI helpers */
अटल व्योम bcm_qspi_hw_set_parms(काष्ठा bcm_qspi *qspi,
				  स्थिर काष्ठा bcm_qspi_parms *xp)
अणु
	u32 spcr, spbr = 0;

	अगर (xp->speed_hz)
		spbr = qspi->base_clk / (2 * xp->speed_hz);

	spcr = clamp_val(spbr, bcm_qspi_spbr_min(qspi), QSPI_SPBR_MAX);
	bcm_qspi_ग_लिखो(qspi, MSPI, MSPI_SPCR0_LSB, spcr);

	अगर (!qspi->mspi_maj_rev)
		/* legacy controller */
		spcr = MSPI_MASTER_BIT;
	अन्यथा
		spcr = 0;

	/* क्रम 16 bit the data should be zero */
	अगर (xp->bits_per_word != 16)
		spcr |= xp->bits_per_word << 2;
	spcr |= xp->mode & 3;

	bcm_qspi_ग_लिखो(qspi, MSPI, MSPI_SPCR0_MSB, spcr);

	अगर (bcm_qspi_has_fastbr(qspi)) अणु
		spcr = 0;

		/* enable fastbr */
		spcr |=	MSPI_SPCR3_FASTBR;

		अगर (bcm_qspi_has_sysclk_108(qspi)) अणु
			/* SYSCLK_108 */
			spcr |= MSPI_SPCR3_SYSCLKSEL_108;
			qspi->base_clk = MSPI_BASE_FREQ * 4;
			/* Change spbr as we changed sysclk */
			bcm_qspi_ग_लिखो(qspi, MSPI, MSPI_SPCR0_LSB, 4);
		पूर्ण

		bcm_qspi_ग_लिखो(qspi, MSPI, MSPI_SPCR3, spcr);
	पूर्ण

	qspi->last_parms = *xp;
पूर्ण

अटल व्योम bcm_qspi_update_parms(काष्ठा bcm_qspi *qspi,
				  काष्ठा spi_device *spi,
				  काष्ठा spi_transfer *trans)
अणु
	काष्ठा bcm_qspi_parms xp;

	xp.speed_hz = trans->speed_hz;
	xp.bits_per_word = trans->bits_per_word;
	xp.mode = spi->mode;

	bcm_qspi_hw_set_parms(qspi, &xp);
पूर्ण

अटल पूर्णांक bcm_qspi_setup(काष्ठा spi_device *spi)
अणु
	काष्ठा bcm_qspi_parms *xp;

	अगर (spi->bits_per_word > 16)
		वापस -EINVAL;

	xp = spi_get_ctldata(spi);
	अगर (!xp) अणु
		xp = kzalloc(माप(*xp), GFP_KERNEL);
		अगर (!xp)
			वापस -ENOMEM;
		spi_set_ctldata(spi, xp);
	पूर्ण
	xp->speed_hz = spi->max_speed_hz;
	xp->mode = spi->mode;

	अगर (spi->bits_per_word)
		xp->bits_per_word = spi->bits_per_word;
	अन्यथा
		xp->bits_per_word = 8;

	वापस 0;
पूर्ण

अटल bool bcm_qspi_mspi_transfer_is_last(काष्ठा bcm_qspi *qspi,
					   काष्ठा qspi_trans *qt)
अणु
	अगर (qt->mspi_last_trans &&
	    spi_transfer_is_last(qspi->master, qt->trans))
		वापस true;
	अन्यथा
		वापस false;
पूर्ण

अटल पूर्णांक update_qspi_trans_byte_count(काष्ठा bcm_qspi *qspi,
					काष्ठा qspi_trans *qt, पूर्णांक flags)
अणु
	पूर्णांक ret = TRANS_STATUS_BREAK_NONE;

	/* count the last transferred bytes */
	अगर (qt->trans->bits_per_word <= 8)
		qt->byte++;
	अन्यथा
		qt->byte += 2;

	अगर (qt->byte >= qt->trans->len) अणु
		/* we're at the end of the spi_transfer */
		/* in TX mode, need to छोड़ो क्रम a delay or CS change */
		अगर (qt->trans->delay.value &&
		    (flags & TRANS_STATUS_BREAK_DELAY))
			ret |= TRANS_STATUS_BREAK_DELAY;
		अगर (qt->trans->cs_change &&
		    (flags & TRANS_STATUS_BREAK_CS_CHANGE))
			ret |= TRANS_STATUS_BREAK_CS_CHANGE;

		अगर (bcm_qspi_mspi_transfer_is_last(qspi, qt))
			ret |= TRANS_STATUS_BREAK_EOM;
		अन्यथा
			ret |= TRANS_STATUS_BREAK_NO_BYTES;

		qt->trans = शून्य;
	पूर्ण

	dev_dbg(&qspi->pdev->dev, "trans %p len %d byte %d ret %x\n",
		qt->trans, qt->trans ? qt->trans->len : 0, qt->byte, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत u8 पढ़ो_rxram_slot_u8(काष्ठा bcm_qspi *qspi, पूर्णांक slot)
अणु
	u32 slot_offset = MSPI_RXRAM + (slot << 3) + 0x4;

	/* mask out reserved bits */
	वापस bcm_qspi_पढ़ो(qspi, MSPI, slot_offset) & 0xff;
पूर्ण

अटल अंतरभूत u16 पढ़ो_rxram_slot_u16(काष्ठा bcm_qspi *qspi, पूर्णांक slot)
अणु
	u32 reg_offset = MSPI_RXRAM;
	u32 lsb_offset = reg_offset + (slot << 3) + 0x4;
	u32 msb_offset = reg_offset + (slot << 3);

	वापस (bcm_qspi_पढ़ो(qspi, MSPI, lsb_offset) & 0xff) |
		((bcm_qspi_पढ़ो(qspi, MSPI, msb_offset) & 0xff) << 8);
पूर्ण

अटल व्योम पढ़ो_from_hw(काष्ठा bcm_qspi *qspi, पूर्णांक slots)
अणु
	काष्ठा qspi_trans tp;
	पूर्णांक slot;

	bcm_qspi_disable_bspi(qspi);

	अगर (slots > MSPI_NUM_CDRAM) अणु
		/* should never happen */
		dev_err(&qspi->pdev->dev, "%s: too many slots!\n", __func__);
		वापस;
	पूर्ण

	tp = qspi->trans_pos;

	क्रम (slot = 0; slot < slots; slot++) अणु
		अगर (tp.trans->bits_per_word <= 8) अणु
			u8 *buf = tp.trans->rx_buf;

			अगर (buf)
				buf[tp.byte] = पढ़ो_rxram_slot_u8(qspi, slot);
			dev_dbg(&qspi->pdev->dev, "RD %02x\n",
				buf ? buf[tp.byte] : 0x0);
		पूर्ण अन्यथा अणु
			u16 *buf = tp.trans->rx_buf;

			अगर (buf)
				buf[tp.byte / 2] = पढ़ो_rxram_slot_u16(qspi,
								      slot);
			dev_dbg(&qspi->pdev->dev, "RD %04x\n",
				buf ? buf[tp.byte / 2] : 0x0);
		पूर्ण

		update_qspi_trans_byte_count(qspi, &tp,
					     TRANS_STATUS_BREAK_NONE);
	पूर्ण

	qspi->trans_pos = tp;
पूर्ण

अटल अंतरभूत व्योम ग_लिखो_txram_slot_u8(काष्ठा bcm_qspi *qspi, पूर्णांक slot,
				       u8 val)
अणु
	u32 reg_offset = MSPI_TXRAM + (slot << 3);

	/* mask out reserved bits */
	bcm_qspi_ग_लिखो(qspi, MSPI, reg_offset, val);
पूर्ण

अटल अंतरभूत व्योम ग_लिखो_txram_slot_u16(काष्ठा bcm_qspi *qspi, पूर्णांक slot,
					u16 val)
अणु
	u32 reg_offset = MSPI_TXRAM;
	u32 msb_offset = reg_offset + (slot << 3);
	u32 lsb_offset = reg_offset + (slot << 3) + 0x4;

	bcm_qspi_ग_लिखो(qspi, MSPI, msb_offset, (val >> 8));
	bcm_qspi_ग_लिखो(qspi, MSPI, lsb_offset, (val & 0xff));
पूर्ण

अटल अंतरभूत u32 पढ़ो_cdram_slot(काष्ठा bcm_qspi *qspi, पूर्णांक slot)
अणु
	वापस bcm_qspi_पढ़ो(qspi, MSPI, MSPI_CDRAM + (slot << 2));
पूर्ण

अटल अंतरभूत व्योम ग_लिखो_cdram_slot(काष्ठा bcm_qspi *qspi, पूर्णांक slot, u32 val)
अणु
	bcm_qspi_ग_लिखो(qspi, MSPI, (MSPI_CDRAM + (slot << 2)), val);
पूर्ण

/* Return number of slots written */
अटल पूर्णांक ग_लिखो_to_hw(काष्ठा bcm_qspi *qspi, काष्ठा spi_device *spi)
अणु
	काष्ठा qspi_trans tp;
	पूर्णांक slot = 0, tstatus = 0;
	u32 mspi_cdram = 0;

	bcm_qspi_disable_bspi(qspi);
	tp = qspi->trans_pos;
	bcm_qspi_update_parms(qspi, spi, tp.trans);

	/* Run until end of transfer or reached the max data */
	जबतक (!tstatus && slot < MSPI_NUM_CDRAM) अणु
		अगर (tp.trans->bits_per_word <= 8) अणु
			स्थिर u8 *buf = tp.trans->tx_buf;
			u8 val = buf ? buf[tp.byte] : 0x00;

			ग_लिखो_txram_slot_u8(qspi, slot, val);
			dev_dbg(&qspi->pdev->dev, "WR %02x\n", val);
		पूर्ण अन्यथा अणु
			स्थिर u16 *buf = tp.trans->tx_buf;
			u16 val = buf ? buf[tp.byte / 2] : 0x0000;

			ग_लिखो_txram_slot_u16(qspi, slot, val);
			dev_dbg(&qspi->pdev->dev, "WR %04x\n", val);
		पूर्ण
		mspi_cdram = MSPI_CDRAM_CONT_BIT;

		अगर (has_bspi(qspi))
			mspi_cdram &= ~1;
		अन्यथा
			mspi_cdram |= (~(1 << spi->chip_select) &
				       MSPI_CDRAM_PCS);

		mspi_cdram |= ((tp.trans->bits_per_word <= 8) ? 0 :
				MSPI_CDRAM_BITSE_BIT);

		ग_लिखो_cdram_slot(qspi, slot, mspi_cdram);

		tstatus = update_qspi_trans_byte_count(qspi, &tp,
						       TRANS_STATUS_BREAK_TX);
		slot++;
	पूर्ण

	अगर (!slot) अणु
		dev_err(&qspi->pdev->dev, "%s: no data to send?", __func__);
		जाओ करोne;
	पूर्ण

	dev_dbg(&qspi->pdev->dev, "submitting %d slots\n", slot);
	bcm_qspi_ग_लिखो(qspi, MSPI, MSPI_NEWQP, 0);
	bcm_qspi_ग_लिखो(qspi, MSPI, MSPI_ENDQP, slot - 1);

	/*
	 *  हाल 1) EOM =1, cs_change =0: SSb inactive
	 *  हाल 2) EOM =1, cs_change =1: SSb stay active
	 *  हाल 3) EOM =0, cs_change =0: SSb stay active
	 *  हाल 4) EOM =0, cs_change =1: SSb inactive
	 */
	अगर (((tstatus & TRANS_STATUS_BREAK_DESELECT)
	     == TRANS_STATUS_BREAK_CS_CHANGE) ||
	    ((tstatus & TRANS_STATUS_BREAK_DESELECT)
	     == TRANS_STATUS_BREAK_EOM)) अणु
		mspi_cdram = पढ़ो_cdram_slot(qspi, slot - 1) &
			~MSPI_CDRAM_CONT_BIT;
		ग_लिखो_cdram_slot(qspi, slot - 1, mspi_cdram);
	पूर्ण

	अगर (has_bspi(qspi))
		bcm_qspi_ग_लिखो(qspi, MSPI, MSPI_WRITE_LOCK, 1);

	/* Must flush previous ग_लिखोs beक्रमe starting MSPI operation */
	mb();
	/* Set cont | spe | spअगरie */
	bcm_qspi_ग_लिखो(qspi, MSPI, MSPI_SPCR2, 0xe0);

करोne:
	वापस slot;
पूर्ण

अटल पूर्णांक bcm_qspi_bspi_exec_mem_op(काष्ठा spi_device *spi,
				     स्थिर काष्ठा spi_mem_op *op)
अणु
	काष्ठा bcm_qspi *qspi = spi_master_get_devdata(spi->master);
	u32 addr = 0, len, rdlen, len_words, from = 0;
	पूर्णांक ret = 0;
	अचिन्हित दीर्घ समयo = msecs_to_jअगरfies(100);
	काष्ठा bcm_qspi_soc_पूर्णांकc *soc_पूर्णांकc = qspi->soc_पूर्णांकc;

	अगर (bcm_qspi_bspi_ver_three(qspi))
		अगर (op->addr.nbytes == BSPI_ADDRLEN_4BYTES)
			वापस -EIO;

	from = op->addr.val;
	अगर (!spi->cs_gpiod)
		bcm_qspi_chip_select(qspi, spi->chip_select);
	bcm_qspi_ग_लिखो(qspi, MSPI, MSPI_WRITE_LOCK, 0);

	/*
	 * when using flex mode we need to send
	 * the upper address byte to bspi
	 */
	अगर (!bcm_qspi_bspi_ver_three(qspi)) अणु
		addr = from & 0xff000000;
		bcm_qspi_ग_लिखो(qspi, BSPI,
			       BSPI_BSPI_FLASH_UPPER_ADDR_BYTE, addr);
	पूर्ण

	अगर (!qspi->xfer_mode.flex_mode)
		addr = from;
	अन्यथा
		addr = from & 0x00ffffff;

	अगर (bcm_qspi_bspi_ver_three(qspi) == true)
		addr = (addr + 0xc00000) & 0xffffff;

	/*
	 * पढ़ो पूर्णांकo the entire buffer by अवरोधing the पढ़ोs
	 * पूर्णांकo RAF buffer पढ़ो lengths
	 */
	len = op->data.nbytes;
	qspi->bspi_rf_op_idx = 0;

	करो अणु
		अगर (len > BSPI_READ_LENGTH)
			rdlen = BSPI_READ_LENGTH;
		अन्यथा
			rdlen = len;

		reinit_completion(&qspi->bspi_करोne);
		bcm_qspi_enable_bspi(qspi);
		len_words = (rdlen + 3) >> 2;
		qspi->bspi_rf_op = op;
		qspi->bspi_rf_op_status = 0;
		qspi->bspi_rf_op_len = rdlen;
		dev_dbg(&qspi->pdev->dev,
			"bspi xfr addr 0x%x len 0x%x", addr, rdlen);
		bcm_qspi_ग_लिखो(qspi, BSPI, BSPI_RAF_START_ADDR, addr);
		bcm_qspi_ग_लिखो(qspi, BSPI, BSPI_RAF_NUM_WORDS, len_words);
		bcm_qspi_ग_लिखो(qspi, BSPI, BSPI_RAF_WATERMARK, 0);
		अगर (qspi->soc_पूर्णांकc) अणु
			/*
			 * clear soc MSPI and BSPI पूर्णांकerrupts and enable
			 * BSPI पूर्णांकerrupts.
			 */
			soc_पूर्णांकc->bcm_qspi_पूर्णांक_ack(soc_पूर्णांकc, MSPI_BSPI_DONE);
			soc_पूर्णांकc->bcm_qspi_पूर्णांक_set(soc_पूर्णांकc, BSPI_DONE, true);
		पूर्ण

		/* Must flush previous ग_लिखोs beक्रमe starting BSPI operation */
		mb();
		bcm_qspi_bspi_lr_start(qspi);
		अगर (!रुको_क्रम_completion_समयout(&qspi->bspi_करोne, समयo)) अणु
			dev_err(&qspi->pdev->dev, "timeout waiting for BSPI\n");
			ret = -ETIMEDOUT;
			अवरोध;
		पूर्ण

		/* set msg वापस length */
		addr += rdlen;
		len -= rdlen;
	पूर्ण जबतक (len);

	वापस ret;
पूर्ण

अटल पूर्णांक bcm_qspi_transfer_one(काष्ठा spi_master *master,
				 काष्ठा spi_device *spi,
				 काष्ठा spi_transfer *trans)
अणु
	काष्ठा bcm_qspi *qspi = spi_master_get_devdata(master);
	पूर्णांक slots;
	अचिन्हित दीर्घ समयo = msecs_to_jअगरfies(100);

	अगर (!spi->cs_gpiod)
		bcm_qspi_chip_select(qspi, spi->chip_select);
	qspi->trans_pos.trans = trans;
	qspi->trans_pos.byte = 0;

	जबतक (qspi->trans_pos.byte < trans->len) अणु
		reinit_completion(&qspi->mspi_करोne);

		slots = ग_लिखो_to_hw(qspi, spi);
		अगर (!रुको_क्रम_completion_समयout(&qspi->mspi_करोne, समयo)) अणु
			dev_err(&qspi->pdev->dev, "timeout waiting for MSPI\n");
			वापस -ETIMEDOUT;
		पूर्ण

		पढ़ो_from_hw(qspi, slots);
	पूर्ण
	bcm_qspi_enable_bspi(qspi);

	वापस 0;
पूर्ण

अटल पूर्णांक bcm_qspi_mspi_exec_mem_op(काष्ठा spi_device *spi,
				     स्थिर काष्ठा spi_mem_op *op)
अणु
	काष्ठा spi_master *master = spi->master;
	काष्ठा bcm_qspi *qspi = spi_master_get_devdata(master);
	काष्ठा spi_transfer t[2];
	u8 cmd[6] = अणु पूर्ण;
	पूर्णांक ret, i;

	स_रखो(cmd, 0, माप(cmd));
	स_रखो(t, 0, माप(t));

	/* tx */
	/* opcode is in cmd[0] */
	cmd[0] = op->cmd.opcode;
	क्रम (i = 0; i < op->addr.nbytes; i++)
		cmd[1 + i] = op->addr.val >> (8 * (op->addr.nbytes - i - 1));

	t[0].tx_buf = cmd;
	t[0].len = op->addr.nbytes + op->dummy.nbytes + 1;
	t[0].bits_per_word = spi->bits_per_word;
	t[0].tx_nbits = op->cmd.buswidth;
	/* lets mspi know that this is not last transfer */
	qspi->trans_pos.mspi_last_trans = false;
	ret = bcm_qspi_transfer_one(master, spi, &t[0]);

	/* rx */
	qspi->trans_pos.mspi_last_trans = true;
	अगर (!ret) अणु
		/* rx */
		t[1].rx_buf = op->data.buf.in;
		t[1].len = op->data.nbytes;
		t[1].rx_nbits =  op->data.buswidth;
		t[1].bits_per_word = spi->bits_per_word;
		ret = bcm_qspi_transfer_one(master, spi, &t[1]);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक bcm_qspi_exec_mem_op(काष्ठा spi_mem *mem,
				स्थिर काष्ठा spi_mem_op *op)
अणु
	काष्ठा spi_device *spi = mem->spi;
	काष्ठा bcm_qspi *qspi = spi_master_get_devdata(spi->master);
	पूर्णांक ret = 0;
	bool mspi_पढ़ो = false;
	u32 addr = 0, len;
	u_अक्षर *buf;

	अगर (!op->data.nbytes || !op->addr.nbytes || op->addr.nbytes > 4 ||
	    op->data.dir != SPI_MEM_DATA_IN)
		वापस -ENOTSUPP;

	buf = op->data.buf.in;
	addr = op->addr.val;
	len = op->data.nbytes;

	अगर (bcm_qspi_bspi_ver_three(qspi) == true) अणु
		/*
		 * The address coming पूर्णांकo this function is a raw flash offset.
		 * But क्रम BSPI <= V3, we need to convert it to a remapped BSPI
		 * address. If it crosses a 4MB boundary, just revert back to
		 * using MSPI.
		 */
		addr = (addr + 0xc00000) & 0xffffff;

		अगर ((~ADDR_4MB_MASK & addr) ^
		    (~ADDR_4MB_MASK & (addr + len - 1)))
			mspi_पढ़ो = true;
	पूर्ण

	/* non-aligned and very लघु transfers are handled by MSPI */
	अगर (!IS_ALIGNED((uपूर्णांकptr_t)addr, 4) || !IS_ALIGNED((uपूर्णांकptr_t)buf, 4) ||
	    len < 4)
		mspi_पढ़ो = true;

	अगर (mspi_पढ़ो)
		वापस bcm_qspi_mspi_exec_mem_op(spi, op);

	ret = bcm_qspi_bspi_set_mode(qspi, op, 0);

	अगर (!ret)
		ret = bcm_qspi_bspi_exec_mem_op(spi, op);

	वापस ret;
पूर्ण

अटल व्योम bcm_qspi_cleanup(काष्ठा spi_device *spi)
अणु
	काष्ठा bcm_qspi_parms *xp = spi_get_ctldata(spi);

	kमुक्त(xp);
पूर्ण

अटल irqवापस_t bcm_qspi_mspi_l2_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा bcm_qspi_dev_id *qspi_dev_id = dev_id;
	काष्ठा bcm_qspi *qspi = qspi_dev_id->dev;
	u32 status = bcm_qspi_पढ़ो(qspi, MSPI, MSPI_MSPI_STATUS);

	अगर (status & MSPI_MSPI_STATUS_SPIF) अणु
		काष्ठा bcm_qspi_soc_पूर्णांकc *soc_पूर्णांकc = qspi->soc_पूर्णांकc;
		/* clear पूर्णांकerrupt */
		status &= ~MSPI_MSPI_STATUS_SPIF;
		bcm_qspi_ग_लिखो(qspi, MSPI, MSPI_MSPI_STATUS, status);
		अगर (qspi->soc_पूर्णांकc)
			soc_पूर्णांकc->bcm_qspi_पूर्णांक_ack(soc_पूर्णांकc, MSPI_DONE);
		complete(&qspi->mspi_करोne);
		वापस IRQ_HANDLED;
	पूर्ण

	वापस IRQ_NONE;
पूर्ण

अटल irqवापस_t bcm_qspi_bspi_lr_l2_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा bcm_qspi_dev_id *qspi_dev_id = dev_id;
	काष्ठा bcm_qspi *qspi = qspi_dev_id->dev;
	काष्ठा bcm_qspi_soc_पूर्णांकc *soc_पूर्णांकc = qspi->soc_पूर्णांकc;
	u32 status = qspi_dev_id->irqp->mask;

	अगर (qspi->bspi_enabled && qspi->bspi_rf_op) अणु
		bcm_qspi_bspi_lr_data_पढ़ो(qspi);
		अगर (qspi->bspi_rf_op_len == 0) अणु
			qspi->bspi_rf_op = शून्य;
			अगर (qspi->soc_पूर्णांकc) अणु
				/* disable soc BSPI पूर्णांकerrupt */
				soc_पूर्णांकc->bcm_qspi_पूर्णांक_set(soc_पूर्णांकc, BSPI_DONE,
							   false);
				/* indicate करोne */
				status = INTR_BSPI_LR_SESSION_DONE_MASK;
			पूर्ण

			अगर (qspi->bspi_rf_op_status)
				bcm_qspi_bspi_lr_clear(qspi);
			अन्यथा
				bcm_qspi_bspi_flush_prefetch_buffers(qspi);
		पूर्ण

		अगर (qspi->soc_पूर्णांकc)
			/* clear soc BSPI पूर्णांकerrupt */
			soc_पूर्णांकc->bcm_qspi_पूर्णांक_ack(soc_पूर्णांकc, BSPI_DONE);
	पूर्ण

	status &= INTR_BSPI_LR_SESSION_DONE_MASK;
	अगर (qspi->bspi_enabled && status && qspi->bspi_rf_op_len == 0)
		complete(&qspi->bspi_करोne);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t bcm_qspi_bspi_lr_err_l2_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा bcm_qspi_dev_id *qspi_dev_id = dev_id;
	काष्ठा bcm_qspi *qspi = qspi_dev_id->dev;
	काष्ठा bcm_qspi_soc_पूर्णांकc *soc_पूर्णांकc = qspi->soc_पूर्णांकc;

	dev_err(&qspi->pdev->dev, "BSPI INT error\n");
	qspi->bspi_rf_op_status = -EIO;
	अगर (qspi->soc_पूर्णांकc)
		/* clear soc पूर्णांकerrupt */
		soc_पूर्णांकc->bcm_qspi_पूर्णांक_ack(soc_पूर्णांकc, BSPI_ERR);

	complete(&qspi->bspi_करोne);
	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t bcm_qspi_l1_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा bcm_qspi_dev_id *qspi_dev_id = dev_id;
	काष्ठा bcm_qspi *qspi = qspi_dev_id->dev;
	काष्ठा bcm_qspi_soc_पूर्णांकc *soc_पूर्णांकc = qspi->soc_पूर्णांकc;
	irqवापस_t ret = IRQ_NONE;

	अगर (soc_पूर्णांकc) अणु
		u32 status = soc_पूर्णांकc->bcm_qspi_get_पूर्णांक_status(soc_पूर्णांकc);

		अगर (status & MSPI_DONE)
			ret = bcm_qspi_mspi_l2_isr(irq, dev_id);
		अन्यथा अगर (status & BSPI_DONE)
			ret = bcm_qspi_bspi_lr_l2_isr(irq, dev_id);
		अन्यथा अगर (status & BSPI_ERR)
			ret = bcm_qspi_bspi_lr_err_l2_isr(irq, dev_id);
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा bcm_qspi_irq qspi_irq_tab[] = अणु
	अणु
		.irq_name = "spi_lr_fullness_reached",
		.irq_handler = bcm_qspi_bspi_lr_l2_isr,
		.mask = INTR_BSPI_LR_FULLNESS_REACHED_MASK,
	पूर्ण,
	अणु
		.irq_name = "spi_lr_session_aborted",
		.irq_handler = bcm_qspi_bspi_lr_err_l2_isr,
		.mask = INTR_BSPI_LR_SESSION_ABORTED_MASK,
	पूर्ण,
	अणु
		.irq_name = "spi_lr_impatient",
		.irq_handler = bcm_qspi_bspi_lr_err_l2_isr,
		.mask = INTR_BSPI_LR_IMPATIENT_MASK,
	पूर्ण,
	अणु
		.irq_name = "spi_lr_session_done",
		.irq_handler = bcm_qspi_bspi_lr_l2_isr,
		.mask = INTR_BSPI_LR_SESSION_DONE_MASK,
	पूर्ण,
#अगर_घोषित QSPI_INT_DEBUG
	/* this पूर्णांकerrupt is क्रम debug purposes only, करोnt request irq */
	अणु
		.irq_name = "spi_lr_overread",
		.irq_handler = bcm_qspi_bspi_lr_err_l2_isr,
		.mask = INTR_BSPI_LR_OVERREAD_MASK,
	पूर्ण,
#पूर्ण_अगर
	अणु
		.irq_name = "mspi_done",
		.irq_handler = bcm_qspi_mspi_l2_isr,
		.mask = INTR_MSPI_DONE_MASK,
	पूर्ण,
	अणु
		.irq_name = "mspi_halted",
		.irq_handler = bcm_qspi_mspi_l2_isr,
		.mask = INTR_MSPI_HALTED_MASK,
	पूर्ण,
	अणु
		/* single muxed L1 पूर्णांकerrupt source */
		.irq_name = "spi_l1_intr",
		.irq_handler = bcm_qspi_l1_isr,
		.irq_source = MUXED_L1,
		.mask = QSPI_INTERRUPTS_ALL,
	पूर्ण,
पूर्ण;

अटल व्योम bcm_qspi_bspi_init(काष्ठा bcm_qspi *qspi)
अणु
	u32 val = 0;

	val = bcm_qspi_पढ़ो(qspi, BSPI, BSPI_REVISION_ID);
	qspi->bspi_maj_rev = (val >> 8) & 0xff;
	qspi->bspi_min_rev = val & 0xff;
	अगर (!(bcm_qspi_bspi_ver_three(qspi))) अणु
		/* Force mapping of BSPI address -> flash offset */
		bcm_qspi_ग_लिखो(qspi, BSPI, BSPI_BSPI_XOR_VALUE, 0);
		bcm_qspi_ग_लिखो(qspi, BSPI, BSPI_BSPI_XOR_ENABLE, 1);
	पूर्ण
	qspi->bspi_enabled = 1;
	bcm_qspi_disable_bspi(qspi);
	bcm_qspi_ग_लिखो(qspi, BSPI, BSPI_B0_CTRL, 0);
	bcm_qspi_ग_लिखो(qspi, BSPI, BSPI_B1_CTRL, 0);
पूर्ण

अटल व्योम bcm_qspi_hw_init(काष्ठा bcm_qspi *qspi)
अणु
	काष्ठा bcm_qspi_parms parms;

	bcm_qspi_ग_लिखो(qspi, MSPI, MSPI_SPCR1_LSB, 0);
	bcm_qspi_ग_लिखो(qspi, MSPI, MSPI_SPCR1_MSB, 0);
	bcm_qspi_ग_लिखो(qspi, MSPI, MSPI_NEWQP, 0);
	bcm_qspi_ग_लिखो(qspi, MSPI, MSPI_ENDQP, 0);
	bcm_qspi_ग_लिखो(qspi, MSPI, MSPI_SPCR2, 0x20);

	parms.mode = SPI_MODE_3;
	parms.bits_per_word = 8;
	parms.speed_hz = qspi->max_speed_hz;
	bcm_qspi_hw_set_parms(qspi, &parms);

	अगर (has_bspi(qspi))
		bcm_qspi_bspi_init(qspi);
पूर्ण

अटल व्योम bcm_qspi_hw_uninit(काष्ठा bcm_qspi *qspi)
अणु
	bcm_qspi_ग_लिखो(qspi, MSPI, MSPI_SPCR2, 0);
	अगर (has_bspi(qspi))
		bcm_qspi_ग_लिखो(qspi, MSPI, MSPI_WRITE_LOCK, 0);

पूर्ण

अटल स्थिर काष्ठा spi_controller_mem_ops bcm_qspi_mem_ops = अणु
	.exec_op = bcm_qspi_exec_mem_op,
पूर्ण;

काष्ठा bcm_qspi_data अणु
	bool	has_mspi_rev;
	bool	has_spcr3_sysclk;
पूर्ण;

अटल स्थिर काष्ठा bcm_qspi_data bcm_qspi_no_rev_data = अणु
	.has_mspi_rev	= false,
	.has_spcr3_sysclk = false,
पूर्ण;

अटल स्थिर काष्ठा bcm_qspi_data bcm_qspi_rev_data = अणु
	.has_mspi_rev	= true,
	.has_spcr3_sysclk = false,
पूर्ण;

अटल स्थिर काष्ठा bcm_qspi_data bcm_qspi_spcr3_data = अणु
	.has_mspi_rev	= true,
	.has_spcr3_sysclk = true,
पूर्ण;

अटल स्थिर काष्ठा of_device_id bcm_qspi_of_match[] = अणु
	अणु
		.compatible = "brcm,spi-bcm7445-qspi",
		.data = &bcm_qspi_rev_data,

	पूर्ण,
	अणु
		.compatible = "brcm,spi-bcm-qspi",
		.data = &bcm_qspi_no_rev_data,
	पूर्ण,
	अणु
		.compatible = "brcm,spi-bcm7216-qspi",
		.data = &bcm_qspi_spcr3_data,
	पूर्ण,
	अणु
		.compatible = "brcm,spi-bcm7278-qspi",
		.data = &bcm_qspi_spcr3_data,
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, bcm_qspi_of_match);

पूर्णांक bcm_qspi_probe(काष्ठा platक्रमm_device *pdev,
		   काष्ठा bcm_qspi_soc_पूर्णांकc *soc_पूर्णांकc)
अणु
	स्थिर काष्ठा of_device_id *of_id = शून्य;
	स्थिर काष्ठा bcm_qspi_data *data;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा bcm_qspi *qspi;
	काष्ठा spi_master *master;
	काष्ठा resource *res;
	पूर्णांक irq, ret = 0, num_पूर्णांकs = 0;
	u32 val;
	u32 rev = 0;
	स्थिर अक्षर *name = शून्य;
	पूर्णांक num_irqs = ARRAY_SIZE(qspi_irq_tab);

	/* We only support device-tree instantiation */
	अगर (!dev->of_node)
		वापस -ENODEV;

	of_id = of_match_node(bcm_qspi_of_match, dev->of_node);
	अगर (!of_id)
		वापस -ENODEV;

	data = of_id->data;

	master = devm_spi_alloc_master(dev, माप(काष्ठा bcm_qspi));
	अगर (!master) अणु
		dev_err(dev, "error allocating spi_master\n");
		वापस -ENOMEM;
	पूर्ण

	qspi = spi_master_get_devdata(master);

	qspi->clk = devm_clk_get_optional(&pdev->dev, शून्य);
	अगर (IS_ERR(qspi->clk))
		वापस PTR_ERR(qspi->clk);

	qspi->pdev = pdev;
	qspi->trans_pos.trans = शून्य;
	qspi->trans_pos.byte = 0;
	qspi->trans_pos.mspi_last_trans = true;
	qspi->master = master;

	master->bus_num = -1;
	master->mode_bits = SPI_CPHA | SPI_CPOL | SPI_RX_DUAL | SPI_RX_QUAD;
	master->setup = bcm_qspi_setup;
	master->transfer_one = bcm_qspi_transfer_one;
	master->mem_ops = &bcm_qspi_mem_ops;
	master->cleanup = bcm_qspi_cleanup;
	master->dev.of_node = dev->of_node;
	master->num_chipselect = NUM_CHIPSELECT;
	master->use_gpio_descriptors = true;

	qspi->big_endian = of_device_is_big_endian(dev->of_node);

	अगर (!of_property_पढ़ो_u32(dev->of_node, "num-cs", &val))
		master->num_chipselect = val;

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "hif_mspi");
	अगर (!res)
		res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM,
						   "mspi");

	अगर (res) अणु
		qspi->base[MSPI]  = devm_ioremap_resource(dev, res);
		अगर (IS_ERR(qspi->base[MSPI]))
			वापस PTR_ERR(qspi->base[MSPI]);
	पूर्ण अन्यथा अणु
		वापस 0;
	पूर्ण

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "bspi");
	अगर (res) अणु
		qspi->base[BSPI]  = devm_ioremap_resource(dev, res);
		अगर (IS_ERR(qspi->base[BSPI]))
			वापस PTR_ERR(qspi->base[BSPI]);
		qspi->bspi_mode = true;
	पूर्ण अन्यथा अणु
		qspi->bspi_mode = false;
	पूर्ण

	dev_info(dev, "using %smspi mode\n", qspi->bspi_mode ? "bspi-" : "");

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "cs_reg");
	अगर (res) अणु
		qspi->base[CHIP_SELECT]  = devm_ioremap_resource(dev, res);
		अगर (IS_ERR(qspi->base[CHIP_SELECT]))
			वापस PTR_ERR(qspi->base[CHIP_SELECT]);
	पूर्ण

	qspi->dev_ids = kसुस्मृति(num_irqs, माप(काष्ठा bcm_qspi_dev_id),
				GFP_KERNEL);
	अगर (!qspi->dev_ids)
		वापस -ENOMEM;

	क्रम (val = 0; val < num_irqs; val++) अणु
		irq = -1;
		name = qspi_irq_tab[val].irq_name;
		अगर (qspi_irq_tab[val].irq_source == SINGLE_L2) अणु
			/* get the l2 पूर्णांकerrupts */
			irq = platक्रमm_get_irq_byname_optional(pdev, name);
		पूर्ण अन्यथा अगर (!num_पूर्णांकs && soc_पूर्णांकc) अणु
			/* all mspi, bspi पूर्णांकrs muxed to one L1 पूर्णांकr */
			irq = platक्रमm_get_irq(pdev, 0);
		पूर्ण

		अगर (irq  >= 0) अणु
			ret = devm_request_irq(&pdev->dev, irq,
					       qspi_irq_tab[val].irq_handler, 0,
					       name,
					       &qspi->dev_ids[val]);
			अगर (ret < 0) अणु
				dev_err(&pdev->dev, "IRQ %s not found\n", name);
				जाओ qspi_probe_err;
			पूर्ण

			qspi->dev_ids[val].dev = qspi;
			qspi->dev_ids[val].irqp = &qspi_irq_tab[val];
			num_पूर्णांकs++;
			dev_dbg(&pdev->dev, "registered IRQ %s %d\n",
				qspi_irq_tab[val].irq_name,
				irq);
		पूर्ण
	पूर्ण

	अगर (!num_पूर्णांकs) अणु
		dev_err(&pdev->dev, "no IRQs registered, cannot init driver\n");
		ret = -EINVAL;
		जाओ qspi_probe_err;
	पूर्ण

	/*
	 * Some SoCs पूर्णांकegrate spi controller (e.g., its पूर्णांकerrupt bits)
	 * in specअगरic ways
	 */
	अगर (soc_पूर्णांकc) अणु
		qspi->soc_पूर्णांकc = soc_पूर्णांकc;
		soc_पूर्णांकc->bcm_qspi_पूर्णांक_set(soc_पूर्णांकc, MSPI_DONE, true);
	पूर्ण अन्यथा अणु
		qspi->soc_पूर्णांकc = शून्य;
	पूर्ण

	ret = clk_prepare_enable(qspi->clk);
	अगर (ret) अणु
		dev_err(dev, "failed to prepare clock\n");
		जाओ qspi_probe_err;
	पूर्ण

	qspi->base_clk = clk_get_rate(qspi->clk);

	अगर (data->has_mspi_rev) अणु
		rev = bcm_qspi_पढ़ो(qspi, MSPI, MSPI_REV);
		/* some older revs करो not have a MSPI_REV रेजिस्टर */
		अगर ((rev & 0xff) == 0xff)
			rev = 0;
	पूर्ण

	qspi->mspi_maj_rev = (rev >> 4) & 0xf;
	qspi->mspi_min_rev = rev & 0xf;
	qspi->mspi_spcr3_sysclk = data->has_spcr3_sysclk;

	qspi->max_speed_hz = qspi->base_clk / (bcm_qspi_spbr_min(qspi) * 2);

	bcm_qspi_hw_init(qspi);
	init_completion(&qspi->mspi_करोne);
	init_completion(&qspi->bspi_करोne);
	qspi->curr_cs = -1;

	platक्रमm_set_drvdata(pdev, qspi);

	qspi->xfer_mode.width = -1;
	qspi->xfer_mode.addrlen = -1;
	qspi->xfer_mode.hp = -1;

	ret = spi_रेजिस्टर_master(master);
	अगर (ret < 0) अणु
		dev_err(dev, "can't register master\n");
		जाओ qspi_reg_err;
	पूर्ण

	वापस 0;

qspi_reg_err:
	bcm_qspi_hw_uninit(qspi);
	clk_disable_unprepare(qspi->clk);
qspi_probe_err:
	kमुक्त(qspi->dev_ids);
	वापस ret;
पूर्ण
/* probe function to be called by SoC specअगरic platक्रमm driver probe */
EXPORT_SYMBOL_GPL(bcm_qspi_probe);

पूर्णांक bcm_qspi_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा bcm_qspi *qspi = platक्रमm_get_drvdata(pdev);

	spi_unरेजिस्टर_master(qspi->master);
	bcm_qspi_hw_uninit(qspi);
	clk_disable_unprepare(qspi->clk);
	kमुक्त(qspi->dev_ids);

	वापस 0;
पूर्ण
/* function to be called by SoC specअगरic platक्रमm driver हटाओ() */
EXPORT_SYMBOL_GPL(bcm_qspi_हटाओ);

अटल पूर्णांक __maybe_unused bcm_qspi_suspend(काष्ठा device *dev)
अणु
	काष्ठा bcm_qspi *qspi = dev_get_drvdata(dev);

	/* store the override strap value */
	अगर (!bcm_qspi_bspi_ver_three(qspi))
		qspi->s3_strap_override_ctrl =
			bcm_qspi_पढ़ो(qspi, BSPI, BSPI_STRAP_OVERRIDE_CTRL);

	spi_master_suspend(qspi->master);
	clk_disable_unprepare(qspi->clk);
	bcm_qspi_hw_uninit(qspi);

	वापस 0;
पूर्ण;

अटल पूर्णांक __maybe_unused bcm_qspi_resume(काष्ठा device *dev)
अणु
	काष्ठा bcm_qspi *qspi = dev_get_drvdata(dev);
	पूर्णांक ret = 0;

	bcm_qspi_hw_init(qspi);
	bcm_qspi_chip_select(qspi, qspi->curr_cs);
	अगर (qspi->soc_पूर्णांकc)
		/* enable MSPI पूर्णांकerrupt */
		qspi->soc_पूर्णांकc->bcm_qspi_पूर्णांक_set(qspi->soc_पूर्णांकc, MSPI_DONE,
						 true);

	ret = clk_prepare_enable(qspi->clk);
	अगर (!ret)
		spi_master_resume(qspi->master);

	वापस ret;
पूर्ण

SIMPLE_DEV_PM_OPS(bcm_qspi_pm_ops, bcm_qspi_suspend, bcm_qspi_resume);

/* pm_ops to be called by SoC specअगरic platक्रमm driver */
EXPORT_SYMBOL_GPL(bcm_qspi_pm_ops);

MODULE_AUTHOR("Kamal Dasu");
MODULE_DESCRIPTION("Broadcom QSPI driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:" DRIVER_NAME);
