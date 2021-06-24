<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 *  Copyright (C) 2012 Thomas Langer <thomas.langer@lantiq.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/delay.h>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>

#समावेश <lantiq_soc.h>

#घोषणा DRV_NAME		"sflash-falcon"

#घोषणा FALCON_SPI_XFER_BEGIN	(1 << 0)
#घोषणा FALCON_SPI_XFER_END	(1 << 1)

/* Bus Read Configuration Register0 */
#घोषणा BUSRCON0		0x00000010
/* Bus Write Configuration Register0 */
#घोषणा BUSWCON0		0x00000018
/* Serial Flash Configuration Register */
#घोषणा SFCON			0x00000080
/* Serial Flash Time Register */
#घोषणा SFTIME			0x00000084
/* Serial Flash Status Register */
#घोषणा SFSTAT			0x00000088
/* Serial Flash Command Register */
#घोषणा SFCMD			0x0000008C
/* Serial Flash Address Register */
#घोषणा SFADDR			0x00000090
/* Serial Flash Data Register */
#घोषणा SFDATA			0x00000094
/* Serial Flash I/O Control Register */
#घोषणा SFIO			0x00000098
/* EBU Clock Control Register */
#घोषणा EBUCC			0x000000C4

/* Dummy Phase Length */
#घोषणा SFCMD_DUMLEN_OFFSET	16
#घोषणा SFCMD_DUMLEN_MASK	0x000F0000
/* Chip Select */
#घोषणा SFCMD_CS_OFFSET		24
#घोषणा SFCMD_CS_MASK		0x07000000
/* field offset */
#घोषणा SFCMD_ALEN_OFFSET	20
#घोषणा SFCMD_ALEN_MASK		0x00700000
/* SCK Rise-edge Position */
#घोषणा SFTIME_SCKR_POS_OFFSET	8
#घोषणा SFTIME_SCKR_POS_MASK	0x00000F00
/* SCK Period */
#घोषणा SFTIME_SCK_PER_OFFSET	0
#घोषणा SFTIME_SCK_PER_MASK	0x0000000F
/* SCK Fall-edge Position */
#घोषणा SFTIME_SCKF_POS_OFFSET	12
#घोषणा SFTIME_SCKF_POS_MASK	0x0000F000
/* Device Size */
#घोषणा SFCON_DEV_SIZE_A23_0	0x03000000
#घोषणा SFCON_DEV_SIZE_MASK	0x0F000000
/* Read Data Position */
#घोषणा SFTIME_RD_POS_MASK	0x000F0000
/* Data Output */
#घोषणा SFIO_UNUSED_WD_MASK	0x0000000F
/* Command Opcode mask */
#घोषणा SFCMD_OPC_MASK		0x000000FF
/* dlen bytes of data to ग_लिखो */
#घोषणा SFCMD_सूची_WRITE		0x00000100
/* Data Length offset */
#घोषणा SFCMD_DLEN_OFFSET	9
/* Command Error */
#घोषणा SFSTAT_CMD_ERR		0x20000000
/* Access Command Pending */
#घोषणा SFSTAT_CMD_PEND		0x00400000
/* Frequency set to 100MHz. */
#घोषणा EBUCC_EBUDIV_SELF100	0x00000001
/* Serial Flash */
#घोषणा BUSRCON0_AGEN_SERIAL_FLASH	0xF0000000
/* 8-bit multiplexed */
#घोषणा BUSRCON0_PORTW_8_BIT_MUX	0x00000000
/* Serial Flash */
#घोषणा BUSWCON0_AGEN_SERIAL_FLASH	0xF0000000
/* Chip Select after opcode */
#घोषणा SFCMD_KEEP_CS_KEEP_SELECTED	0x00008000

#घोषणा CLOCK_100M	100000000
#घोषणा CLOCK_50M	50000000

काष्ठा falcon_sflash अणु
	u32 sfcmd; /* क्रम caching of opcode, direction, ... */
	काष्ठा spi_master *master;
पूर्ण;

पूर्णांक falcon_sflash_xfer(काष्ठा spi_device *spi, काष्ठा spi_transfer *t,
		अचिन्हित दीर्घ flags)
अणु
	काष्ठा device *dev = &spi->dev;
	काष्ठा falcon_sflash *priv = spi_master_get_devdata(spi->master);
	स्थिर u8 *txp = t->tx_buf;
	u8 *rxp = t->rx_buf;
	अचिन्हित पूर्णांक bytelen = ((8 * t->len + 7) / 8);
	अचिन्हित पूर्णांक len, alen, dumlen;
	u32 val;
	क्रमागत अणु
		state_init,
		state_command_prepare,
		state_ग_लिखो,
		state_पढ़ो,
		state_disable_cs,
		state_end
	पूर्ण state = state_init;

	करो अणु
		चयन (state) अणु
		हाल state_init: /* detect phase of upper layer sequence */
		अणु
			/* initial ग_लिखो ? */
			अगर (flags & FALCON_SPI_XFER_BEGIN) अणु
				अगर (!txp) अणु
					dev_err(dev,
						"BEGIN without tx data!\n");
					वापस -ENODATA;
				पूर्ण
				/*
				 * Prepare the parts of the sfcmd रेजिस्टर,
				 * which should not change during a sequence!
				 * Only exception are the length fields,
				 * especially alen and dumlen.
				 */

				priv->sfcmd = ((spi->chip_select
						<< SFCMD_CS_OFFSET)
					       & SFCMD_CS_MASK);
				priv->sfcmd |= SFCMD_KEEP_CS_KEEP_SELECTED;
				priv->sfcmd |= *txp;
				txp++;
				bytelen--;
				अगर (bytelen) अणु
					/*
					 * more data:
					 * maybe address and/or dummy
					 */
					state = state_command_prepare;
					अवरोध;
				पूर्ण अन्यथा अणु
					dev_dbg(dev, "write cmd %02X\n",
						priv->sfcmd & SFCMD_OPC_MASK);
				पूर्ण
			पूर्ण
			/* जारीd ग_लिखो ? */
			अगर (txp && bytelen) अणु
				state = state_ग_लिखो;
				अवरोध;
			पूर्ण
			/* पढ़ो data? */
			अगर (rxp && bytelen) अणु
				state = state_पढ़ो;
				अवरोध;
			पूर्ण
			/* end of sequence? */
			अगर (flags & FALCON_SPI_XFER_END)
				state = state_disable_cs;
			अन्यथा
				state = state_end;
			अवरोध;
		पूर्ण
		/* collect tx data क्रम address and dummy phase */
		हाल state_command_prepare:
		अणु
			/* txp is valid, alपढ़ोy checked */
			val = 0;
			alen = 0;
			dumlen = 0;
			जबतक (bytelen > 0) अणु
				अगर (alen < 3) अणु
					val = (val << 8) | (*txp++);
					alen++;
				पूर्ण अन्यथा अगर ((dumlen < 15) && (*txp == 0)) अणु
					/*
					 * assume dummy bytes are set to 0
					 * from upper layer
					 */
					dumlen++;
					txp++;
				पूर्ण अन्यथा अणु
					अवरोध;
				पूर्ण
				bytelen--;
			पूर्ण
			priv->sfcmd &= ~(SFCMD_ALEN_MASK | SFCMD_DUMLEN_MASK);
			priv->sfcmd |= (alen << SFCMD_ALEN_OFFSET) |
					 (dumlen << SFCMD_DUMLEN_OFFSET);
			अगर (alen > 0)
				ltq_ebu_w32(val, SFADDR);

			dev_dbg(dev, "wr %02X, alen=%d (addr=%06X) dlen=%d\n",
				priv->sfcmd & SFCMD_OPC_MASK,
				alen, val, dumlen);

			अगर (bytelen > 0) अणु
				/* जारी with ग_लिखो */
				state = state_ग_लिखो;
			पूर्ण अन्यथा अगर (flags & FALCON_SPI_XFER_END) अणु
				/* end of sequence? */
				state = state_disable_cs;
			पूर्ण अन्यथा अणु
				/*
				 * go to end and expect another
				 * call (पढ़ो or ग_लिखो)
				 */
				state = state_end;
			पूर्ण
			अवरोध;
		पूर्ण
		हाल state_ग_लिखो:
		अणु
			/* txp still valid */
			priv->sfcmd |= SFCMD_सूची_WRITE;
			len = 0;
			val = 0;
			करो अणु
				अगर (bytelen--)
					val |= (*txp++) << (8 * len++);
				अगर ((flags & FALCON_SPI_XFER_END)
				    && (bytelen == 0)) अणु
					priv->sfcmd &=
						~SFCMD_KEEP_CS_KEEP_SELECTED;
				पूर्ण
				अगर ((len == 4) || (bytelen == 0)) अणु
					ltq_ebu_w32(val, SFDATA);
					ltq_ebu_w32(priv->sfcmd
						| (len<<SFCMD_DLEN_OFFSET),
						SFCMD);
					len = 0;
					val = 0;
					priv->sfcmd &= ~(SFCMD_ALEN_MASK
							 | SFCMD_DUMLEN_MASK);
				पूर्ण
			पूर्ण जबतक (bytelen);
			state = state_end;
			अवरोध;
		पूर्ण
		हाल state_पढ़ो:
		अणु
			/* पढ़ो data */
			priv->sfcmd &= ~SFCMD_सूची_WRITE;
			करो अणु
				अगर ((flags & FALCON_SPI_XFER_END)
				    && (bytelen <= 4)) अणु
					priv->sfcmd &=
						~SFCMD_KEEP_CS_KEEP_SELECTED;
				पूर्ण
				len = (bytelen > 4) ? 4 : bytelen;
				bytelen -= len;
				ltq_ebu_w32(priv->sfcmd
					| (len << SFCMD_DLEN_OFFSET), SFCMD);
				priv->sfcmd &= ~(SFCMD_ALEN_MASK
						 | SFCMD_DUMLEN_MASK);
				करो अणु
					val = ltq_ebu_r32(SFSTAT);
					अगर (val & SFSTAT_CMD_ERR) अणु
						/* reset error status */
						dev_err(dev, "SFSTAT: CMD_ERR");
						dev_err(dev, " (%x)\n", val);
						ltq_ebu_w32(SFSTAT_CMD_ERR,
							SFSTAT);
						वापस -EBADE;
					पूर्ण
				पूर्ण जबतक (val & SFSTAT_CMD_PEND);
				val = ltq_ebu_r32(SFDATA);
				करो अणु
					*rxp = (val & 0xFF);
					rxp++;
					val >>= 8;
					len--;
				पूर्ण जबतक (len);
			पूर्ण जबतक (bytelen);
			state = state_end;
			अवरोध;
		पूर्ण
		हाल state_disable_cs:
		अणु
			priv->sfcmd &= ~SFCMD_KEEP_CS_KEEP_SELECTED;
			ltq_ebu_w32(priv->sfcmd | (0 << SFCMD_DLEN_OFFSET),
				SFCMD);
			val = ltq_ebu_r32(SFSTAT);
			अगर (val & SFSTAT_CMD_ERR) अणु
				/* reset error status */
				dev_err(dev, "SFSTAT: CMD_ERR (%x)\n", val);
				ltq_ebu_w32(SFSTAT_CMD_ERR, SFSTAT);
				वापस -EBADE;
			पूर्ण
			state = state_end;
			अवरोध;
		पूर्ण
		हाल state_end:
			अवरोध;
		पूर्ण
	पूर्ण जबतक (state != state_end);

	वापस 0;
पूर्ण

अटल पूर्णांक falcon_sflash_setup(काष्ठा spi_device *spi)
अणु
	अचिन्हित पूर्णांक i;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ebu_lock, flags);

	अगर (spi->max_speed_hz >= CLOCK_100M) अणु
		/* set EBU घड़ी to 100 MHz */
		ltq_sys1_w32_mask(0, EBUCC_EBUDIV_SELF100, EBUCC);
		i = 1; /* भागider */
	पूर्ण अन्यथा अणु
		/* set EBU घड़ी to 50 MHz */
		ltq_sys1_w32_mask(EBUCC_EBUDIV_SELF100, 0, EBUCC);

		/* search क्रम suitable भागider */
		क्रम (i = 1; i < 7; i++) अणु
			अगर (CLOCK_50M / i <= spi->max_speed_hz)
				अवरोध;
		पूर्ण
	पूर्ण

	/* setup period of serial घड़ी */
	ltq_ebu_w32_mask(SFTIME_SCKF_POS_MASK
		     | SFTIME_SCKR_POS_MASK
		     | SFTIME_SCK_PER_MASK,
		     (i << SFTIME_SCKR_POS_OFFSET)
		     | (i << (SFTIME_SCK_PER_OFFSET + 1)),
		     SFTIME);

	/*
	 * set some bits of unused_wd, to not trigger HOLD/WP
	 * संकेतs on non QUAD flashes
	 */
	ltq_ebu_w32((SFIO_UNUSED_WD_MASK & (0x8 | 0x4)), SFIO);

	ltq_ebu_w32(BUSRCON0_AGEN_SERIAL_FLASH | BUSRCON0_PORTW_8_BIT_MUX,
			BUSRCON0);
	ltq_ebu_w32(BUSWCON0_AGEN_SERIAL_FLASH, BUSWCON0);
	/* set address wrap around to maximum क्रम 24-bit addresses */
	ltq_ebu_w32_mask(SFCON_DEV_SIZE_MASK, SFCON_DEV_SIZE_A23_0, SFCON);

	spin_unlock_irqrestore(&ebu_lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक falcon_sflash_xfer_one(काष्ठा spi_master *master,
					काष्ठा spi_message *m)
अणु
	काष्ठा falcon_sflash *priv = spi_master_get_devdata(master);
	काष्ठा spi_transfer *t;
	अचिन्हित दीर्घ spi_flags;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	priv->sfcmd = 0;
	m->actual_length = 0;

	spi_flags = FALCON_SPI_XFER_BEGIN;
	list_क्रम_each_entry(t, &m->transfers, transfer_list) अणु
		अगर (list_is_last(&t->transfer_list, &m->transfers))
			spi_flags |= FALCON_SPI_XFER_END;

		spin_lock_irqsave(&ebu_lock, flags);
		ret = falcon_sflash_xfer(m->spi, t, spi_flags);
		spin_unlock_irqrestore(&ebu_lock, flags);

		अगर (ret)
			अवरोध;

		m->actual_length += t->len;

		WARN_ON(t->delay.value || t->cs_change);
		spi_flags = 0;
	पूर्ण

	m->status = ret;
	spi_finalize_current_message(master);

	वापस 0;
पूर्ण

अटल पूर्णांक falcon_sflash_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा falcon_sflash *priv;
	काष्ठा spi_master *master;
	पूर्णांक ret;

	master = spi_alloc_master(&pdev->dev, माप(*priv));
	अगर (!master)
		वापस -ENOMEM;

	priv = spi_master_get_devdata(master);
	priv->master = master;

	master->mode_bits = SPI_MODE_3;
	master->flags = SPI_MASTER_HALF_DUPLEX;
	master->setup = falcon_sflash_setup;
	master->transfer_one_message = falcon_sflash_xfer_one;
	master->dev.of_node = pdev->dev.of_node;

	ret = devm_spi_रेजिस्टर_master(&pdev->dev, master);
	अगर (ret)
		spi_master_put(master);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा of_device_id falcon_sflash_match[] = अणु
	अणु .compatible = "lantiq,sflash-falcon" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, falcon_sflash_match);

अटल काष्ठा platक्रमm_driver falcon_sflash_driver = अणु
	.probe	= falcon_sflash_probe,
	.driver = अणु
		.name	= DRV_NAME,
		.of_match_table = falcon_sflash_match,
	पूर्ण
पूर्ण;

module_platक्रमm_driver(falcon_sflash_driver);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Lantiq Falcon SPI/SFLASH controller driver");
