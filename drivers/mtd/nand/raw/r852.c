<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright तऊ 2009 - Maxim Levitsky
 * driver क्रम Ricoh xD पढ़ोers
 */

#घोषणा DRV_NAME "r852"
#घोषणा pr_fmt(fmt)  DRV_NAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pci.h>
#समावेश <linux/pci_ids.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <linux/sched.h>
#समावेश "sm_common.h"
#समावेश "r852.h"


अटल bool r852_enable_dma = 1;
module_param(r852_enable_dma, bool, S_IRUGO);
MODULE_PARM_DESC(r852_enable_dma, "Enable usage of the DMA (default)");

अटल पूर्णांक debug;
module_param(debug, पूर्णांक, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(debug, "Debug level (0-2)");

/* पढ़ो रेजिस्टर */
अटल अंतरभूत uपूर्णांक8_t r852_पढ़ो_reg(काष्ठा r852_device *dev, पूर्णांक address)
अणु
	uपूर्णांक8_t reg = पढ़ोb(dev->mmio + address);
	वापस reg;
पूर्ण

/* ग_लिखो रेजिस्टर */
अटल अंतरभूत व्योम r852_ग_लिखो_reg(काष्ठा r852_device *dev,
						पूर्णांक address, uपूर्णांक8_t value)
अणु
	ग_लिखोb(value, dev->mmio + address);
पूर्ण


/* पढ़ो dword sized रेजिस्टर */
अटल अंतरभूत uपूर्णांक32_t r852_पढ़ो_reg_dword(काष्ठा r852_device *dev, पूर्णांक address)
अणु
	uपूर्णांक32_t reg = le32_to_cpu(पढ़ोl(dev->mmio + address));
	वापस reg;
पूर्ण

/* ग_लिखो dword sized रेजिस्टर */
अटल अंतरभूत व्योम r852_ग_लिखो_reg_dword(काष्ठा r852_device *dev,
							पूर्णांक address, uपूर्णांक32_t value)
अणु
	ग_लिखोl(cpu_to_le32(value), dev->mmio + address);
पूर्ण

/* वापसs poपूर्णांकer to our निजी काष्ठाure */
अटल अंतरभूत काष्ठा r852_device *r852_get_dev(काष्ठा mtd_info *mtd)
अणु
	काष्ठा nand_chip *chip = mtd_to_nand(mtd);
	वापस nand_get_controller_data(chip);
पूर्ण


/* check अगर controller supports dma */
अटल व्योम r852_dma_test(काष्ठा r852_device *dev)
अणु
	dev->dma_usable = (r852_पढ़ो_reg(dev, R852_DMA_CAP) &
		(R852_DMA1 | R852_DMA2)) == (R852_DMA1 | R852_DMA2);

	अगर (!dev->dma_usable)
		message("Non dma capable device detected, dma disabled");

	अगर (!r852_enable_dma) अणु
		message("disabling dma on user request");
		dev->dma_usable = 0;
	पूर्ण
पूर्ण

/*
 * Enable dma. Enables ether first or second stage of the DMA,
 * Expects dev->dma_dir and dev->dma_state be set
 */
अटल व्योम r852_dma_enable(काष्ठा r852_device *dev)
अणु
	uपूर्णांक8_t dma_reg, dma_irq_reg;

	/* Set up dma settings */
	dma_reg = r852_पढ़ो_reg_dword(dev, R852_DMA_SETTINGS);
	dma_reg &= ~(R852_DMA_READ | R852_DMA_INTERNAL | R852_DMA_MEMORY);

	अगर (dev->dma_dir)
		dma_reg |= R852_DMA_READ;

	अगर (dev->dma_state == DMA_INTERNAL) अणु
		dma_reg |= R852_DMA_INTERNAL;
		/* Precaution to make sure HW करोesn't ग_लिखो */
			/* to अक्रमom kernel memory */
		r852_ग_लिखो_reg_dword(dev, R852_DMA_ADDR,
			cpu_to_le32(dev->phys_bounce_buffer));
	पूर्ण अन्यथा अणु
		dma_reg |= R852_DMA_MEMORY;
		r852_ग_लिखो_reg_dword(dev, R852_DMA_ADDR,
			cpu_to_le32(dev->phys_dma_addr));
	पूर्ण

	/* Precaution: make sure ग_लिखो reached the device */
	r852_पढ़ो_reg_dword(dev, R852_DMA_ADDR);

	r852_ग_लिखो_reg_dword(dev, R852_DMA_SETTINGS, dma_reg);

	/* Set dma irq */
	dma_irq_reg = r852_पढ़ो_reg_dword(dev, R852_DMA_IRQ_ENABLE);
	r852_ग_लिखो_reg_dword(dev, R852_DMA_IRQ_ENABLE,
		dma_irq_reg |
		R852_DMA_IRQ_INTERNAL |
		R852_DMA_IRQ_ERROR |
		R852_DMA_IRQ_MEMORY);
पूर्ण

/*
 * Disable dma, called from the पूर्णांकerrupt handler, which specअगरies
 * success of the operation via 'error' argument
 */
अटल व्योम r852_dma_करोne(काष्ठा r852_device *dev, पूर्णांक error)
अणु
	WARN_ON(dev->dma_stage == 0);

	r852_ग_लिखो_reg_dword(dev, R852_DMA_IRQ_STA,
			r852_पढ़ो_reg_dword(dev, R852_DMA_IRQ_STA));

	r852_ग_लिखो_reg_dword(dev, R852_DMA_SETTINGS, 0);
	r852_ग_लिखो_reg_dword(dev, R852_DMA_IRQ_ENABLE, 0);

	/* Precaution to make sure HW करोesn't ग_लिखो to अक्रमom kernel memory */
	r852_ग_लिखो_reg_dword(dev, R852_DMA_ADDR,
		cpu_to_le32(dev->phys_bounce_buffer));
	r852_पढ़ो_reg_dword(dev, R852_DMA_ADDR);

	dev->dma_error = error;
	dev->dma_stage = 0;

	अगर (dev->phys_dma_addr && dev->phys_dma_addr != dev->phys_bounce_buffer)
		dma_unmap_single(&dev->pci_dev->dev, dev->phys_dma_addr,
			R852_DMA_LEN,
			dev->dma_dir ? DMA_FROM_DEVICE : DMA_TO_DEVICE);
पूर्ण

/*
 * Wait, till dma is करोne, which includes both phases of it
 */
अटल पूर्णांक r852_dma_रुको(काष्ठा r852_device *dev)
अणु
	दीर्घ समयout = रुको_क्रम_completion_समयout(&dev->dma_करोne,
				msecs_to_jअगरfies(1000));
	अगर (!समयout) अणु
		dbg("timeout waiting for DMA interrupt");
		वापस -ETIMEDOUT;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Read/Write one page using dma. Only pages can be पढ़ो (512 bytes)
*/
अटल व्योम r852_करो_dma(काष्ठा r852_device *dev, uपूर्णांक8_t *buf, पूर्णांक करो_पढ़ो)
अणु
	पूर्णांक bounce = 0;
	अचिन्हित दीर्घ flags;
	पूर्णांक error;

	dev->dma_error = 0;

	/* Set dma direction */
	dev->dma_dir = करो_पढ़ो;
	dev->dma_stage = 1;
	reinit_completion(&dev->dma_करोne);

	dbg_verbose("doing dma %s ", करो_पढ़ो ? "read" : "write");

	/* Set initial dma state: क्रम पढ़ोing first fill on board buffer,
	  from device, क्रम ग_लिखोs first fill the buffer  from memory*/
	dev->dma_state = करो_पढ़ो ? DMA_INTERNAL : DMA_MEMORY;

	/* अगर incoming buffer is not page aligned, we should करो bounce */
	अगर ((अचिन्हित दीर्घ)buf & (R852_DMA_LEN-1))
		bounce = 1;

	अगर (!bounce) अणु
		dev->phys_dma_addr = dma_map_single(&dev->pci_dev->dev, buf,
			R852_DMA_LEN,
			करो_पढ़ो ? DMA_FROM_DEVICE : DMA_TO_DEVICE);
		अगर (dma_mapping_error(&dev->pci_dev->dev, dev->phys_dma_addr))
			bounce = 1;
	पूर्ण

	अगर (bounce) अणु
		dbg_verbose("dma: using bounce buffer");
		dev->phys_dma_addr = dev->phys_bounce_buffer;
		अगर (!करो_पढ़ो)
			स_नकल(dev->bounce_buffer, buf, R852_DMA_LEN);
	पूर्ण

	/* Enable DMA */
	spin_lock_irqsave(&dev->irqlock, flags);
	r852_dma_enable(dev);
	spin_unlock_irqrestore(&dev->irqlock, flags);

	/* Wait till complete */
	error = r852_dma_रुको(dev);

	अगर (error) अणु
		r852_dma_करोne(dev, error);
		वापस;
	पूर्ण

	अगर (करो_पढ़ो && bounce)
		स_नकल((व्योम *)buf, dev->bounce_buffer, R852_DMA_LEN);
पूर्ण

/*
 * Program data lines of the nand chip to send data to it
 */
अटल व्योम r852_ग_लिखो_buf(काष्ठा nand_chip *chip, स्थिर uपूर्णांक8_t *buf, पूर्णांक len)
अणु
	काष्ठा r852_device *dev = r852_get_dev(nand_to_mtd(chip));
	uपूर्णांक32_t reg;

	/* Don't allow any access to hardware अगर we suspect card removal */
	अगर (dev->card_unstable)
		वापस;

	/* Special हाल क्रम whole sector पढ़ो */
	अगर (len == R852_DMA_LEN && dev->dma_usable) अणु
		r852_करो_dma(dev, (uपूर्णांक8_t *)buf, 0);
		वापस;
	पूर्ण

	/* ग_लिखो DWORD chinks - faster */
	जबतक (len >= 4) अणु
		reg = buf[0] | buf[1] << 8 | buf[2] << 16 | buf[3] << 24;
		r852_ग_लिखो_reg_dword(dev, R852_DATALINE, reg);
		buf += 4;
		len -= 4;

	पूर्ण

	/* ग_लिखो rest */
	जबतक (len > 0) अणु
		r852_ग_लिखो_reg(dev, R852_DATALINE, *buf++);
		len--;
	पूर्ण
पूर्ण

/*
 * Read data lines of the nand chip to retrieve data
 */
अटल व्योम r852_पढ़ो_buf(काष्ठा nand_chip *chip, uपूर्णांक8_t *buf, पूर्णांक len)
अणु
	काष्ठा r852_device *dev = r852_get_dev(nand_to_mtd(chip));
	uपूर्णांक32_t reg;

	अगर (dev->card_unstable) अणु
		/* since we can't संकेत error here, at least, वापस
			predictable buffer */
		स_रखो(buf, 0, len);
		वापस;
	पूर्ण

	/* special हाल क्रम whole sector पढ़ो */
	अगर (len == R852_DMA_LEN && dev->dma_usable) अणु
		r852_करो_dma(dev, buf, 1);
		वापस;
	पूर्ण

	/* पढ़ो in dword sized chunks */
	जबतक (len >= 4) अणु

		reg = r852_पढ़ो_reg_dword(dev, R852_DATALINE);
		*buf++ = reg & 0xFF;
		*buf++ = (reg >> 8) & 0xFF;
		*buf++ = (reg >> 16) & 0xFF;
		*buf++ = (reg >> 24) & 0xFF;
		len -= 4;
	पूर्ण

	/* पढ़ो the reset by bytes */
	जबतक (len--)
		*buf++ = r852_पढ़ो_reg(dev, R852_DATALINE);
पूर्ण

/*
 * Read one byte from nand chip
 */
अटल uपूर्णांक8_t r852_पढ़ो_byte(काष्ठा nand_chip *chip)
अणु
	काष्ठा r852_device *dev = r852_get_dev(nand_to_mtd(chip));

	/* Same problem as in r852_पढ़ो_buf.... */
	अगर (dev->card_unstable)
		वापस 0;

	वापस r852_पढ़ो_reg(dev, R852_DATALINE);
पूर्ण

/*
 * Control several chip lines & send commands
 */
अटल व्योम r852_cmdctl(काष्ठा nand_chip *chip, पूर्णांक dat, अचिन्हित पूर्णांक ctrl)
अणु
	काष्ठा r852_device *dev = r852_get_dev(nand_to_mtd(chip));

	अगर (dev->card_unstable)
		वापस;

	अगर (ctrl & न_अंकD_CTRL_CHANGE) अणु

		dev->ctlreg &= ~(R852_CTL_DATA | R852_CTL_COMMAND |
				 R852_CTL_ON | R852_CTL_CARDENABLE);

		अगर (ctrl & न_अंकD_ALE)
			dev->ctlreg |= R852_CTL_DATA;

		अगर (ctrl & न_अंकD_CLE)
			dev->ctlreg |= R852_CTL_COMMAND;

		अगर (ctrl & न_अंकD_NCE)
			dev->ctlreg |= (R852_CTL_CARDENABLE | R852_CTL_ON);
		अन्यथा
			dev->ctlreg &= ~R852_CTL_WRITE;

		/* when ग_लिखो is stareted, enable ग_लिखो access */
		अगर (dat == न_अंकD_CMD_ERASE1)
			dev->ctlreg |= R852_CTL_WRITE;

		r852_ग_लिखो_reg(dev, R852_CTL, dev->ctlreg);
	पूर्ण

	 /* HACK: न_अंकD_CMD_SEQIN is called without न_अंकD_CTRL_CHANGE, but we need
		to set ग_लिखो mode */
	अगर (dat == न_अंकD_CMD_SEQIN && (dev->ctlreg & R852_CTL_COMMAND)) अणु
		dev->ctlreg |= R852_CTL_WRITE;
		r852_ग_लिखो_reg(dev, R852_CTL, dev->ctlreg);
	पूर्ण

	अगर (dat != न_अंकD_CMD_NONE)
		r852_ग_लिखो_reg(dev, R852_DATALINE, dat);
पूर्ण

/*
 * Wait till card is पढ़ोy.
 * based on nand_रुको, but वापसs errors on DMA error
 */
अटल पूर्णांक r852_रुको(काष्ठा nand_chip *chip)
अणु
	काष्ठा r852_device *dev = nand_get_controller_data(chip);

	अचिन्हित दीर्घ समयout;
	u8 status;

	समयout = jअगरfies + msecs_to_jअगरfies(400);

	जबतक (समय_beक्रमe(jअगरfies, समयout))
		अगर (chip->legacy.dev_पढ़ोy(chip))
			अवरोध;

	nand_status_op(chip, &status);

	/* Unक्रमtunelly, no way to send detailed error status... */
	अगर (dev->dma_error) अणु
		status |= न_अंकD_STATUS_FAIL;
		dev->dma_error = 0;
	पूर्ण
	वापस status;
पूर्ण

/*
 * Check अगर card is पढ़ोy
 */

अटल पूर्णांक r852_पढ़ोy(काष्ठा nand_chip *chip)
अणु
	काष्ठा r852_device *dev = r852_get_dev(nand_to_mtd(chip));
	वापस !(r852_पढ़ो_reg(dev, R852_CARD_STA) & R852_CARD_STA_BUSY);
पूर्ण


/*
 * Set ECC engine mode
*/

अटल व्योम r852_ecc_hwctl(काष्ठा nand_chip *chip, पूर्णांक mode)
अणु
	काष्ठा r852_device *dev = r852_get_dev(nand_to_mtd(chip));

	अगर (dev->card_unstable)
		वापस;

	चयन (mode) अणु
	हाल न_अंकD_ECC_READ:
	हाल न_अंकD_ECC_WRITE:
		/* enable ecc generation/check*/
		dev->ctlreg |= R852_CTL_ECC_ENABLE;

		/* flush ecc buffer */
		r852_ग_लिखो_reg(dev, R852_CTL,
			dev->ctlreg | R852_CTL_ECC_ACCESS);

		r852_पढ़ो_reg_dword(dev, R852_DATALINE);
		r852_ग_लिखो_reg(dev, R852_CTL, dev->ctlreg);
		वापस;

	हाल न_अंकD_ECC_READSYN:
		/* disable ecc generation */
		dev->ctlreg &= ~R852_CTL_ECC_ENABLE;
		r852_ग_लिखो_reg(dev, R852_CTL, dev->ctlreg);
	पूर्ण
पूर्ण

/*
 * Calculate ECC, only used क्रम ग_लिखोs
 */

अटल पूर्णांक r852_ecc_calculate(काष्ठा nand_chip *chip, स्थिर uपूर्णांक8_t *dat,
			      uपूर्णांक8_t *ecc_code)
अणु
	काष्ठा r852_device *dev = r852_get_dev(nand_to_mtd(chip));
	काष्ठा sm_oob *oob = (काष्ठा sm_oob *)ecc_code;
	uपूर्णांक32_t ecc1, ecc2;

	अगर (dev->card_unstable)
		वापस 0;

	dev->ctlreg &= ~R852_CTL_ECC_ENABLE;
	r852_ग_लिखो_reg(dev, R852_CTL, dev->ctlreg | R852_CTL_ECC_ACCESS);

	ecc1 = r852_पढ़ो_reg_dword(dev, R852_DATALINE);
	ecc2 = r852_पढ़ो_reg_dword(dev, R852_DATALINE);

	oob->ecc1[0] = (ecc1) & 0xFF;
	oob->ecc1[1] = (ecc1 >> 8) & 0xFF;
	oob->ecc1[2] = (ecc1 >> 16) & 0xFF;

	oob->ecc2[0] = (ecc2) & 0xFF;
	oob->ecc2[1] = (ecc2 >> 8) & 0xFF;
	oob->ecc2[2] = (ecc2 >> 16) & 0xFF;

	r852_ग_लिखो_reg(dev, R852_CTL, dev->ctlreg);
	वापस 0;
पूर्ण

/*
 * Correct the data using ECC, hw did almost everything क्रम us
 */

अटल पूर्णांक r852_ecc_correct(काष्ठा nand_chip *chip, uपूर्णांक8_t *dat,
			    uपूर्णांक8_t *पढ़ो_ecc, uपूर्णांक8_t *calc_ecc)
अणु
	uपूर्णांक32_t ecc_reg;
	uपूर्णांक8_t ecc_status, err_byte;
	पूर्णांक i, error = 0;

	काष्ठा r852_device *dev = r852_get_dev(nand_to_mtd(chip));

	अगर (dev->card_unstable)
		वापस 0;

	अगर (dev->dma_error) अणु
		dev->dma_error = 0;
		वापस -EIO;
	पूर्ण

	r852_ग_लिखो_reg(dev, R852_CTL, dev->ctlreg | R852_CTL_ECC_ACCESS);
	ecc_reg = r852_पढ़ो_reg_dword(dev, R852_DATALINE);
	r852_ग_लिखो_reg(dev, R852_CTL, dev->ctlreg);

	क्रम (i = 0 ; i <= 1 ; i++) अणु

		ecc_status = (ecc_reg >> 8) & 0xFF;

		/* ecc uncorrectable error */
		अगर (ecc_status & R852_ECC_FAIL) अणु
			dbg("ecc: unrecoverable error, in half %d", i);
			error = -EBADMSG;
			जाओ निकास;
		पूर्ण

		/* correctable error */
		अगर (ecc_status & R852_ECC_CORRECTABLE) अणु

			err_byte = ecc_reg & 0xFF;
			dbg("ecc: recoverable error, "
				"in half %d, byte %d, bit %d", i,
				err_byte, ecc_status & R852_ECC_ERR_BIT_MSK);

			dat[err_byte] ^=
				1 << (ecc_status & R852_ECC_ERR_BIT_MSK);
			error++;
		पूर्ण

		dat += 256;
		ecc_reg >>= 16;
	पूर्ण
निकास:
	वापस error;
पूर्ण

/*
 * This is copy of nand_पढ़ो_oob_std
 * nand_पढ़ो_oob_syndrome assumes we can send column address - we can't
 */
अटल पूर्णांक r852_पढ़ो_oob(काष्ठा nand_chip *chip, पूर्णांक page)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);

	वापस nand_पढ़ो_oob_op(chip, page, 0, chip->oob_poi, mtd->oobsize);
पूर्ण

/*
 * Start the nand engine
 */

अटल व्योम r852_engine_enable(काष्ठा r852_device *dev)
अणु
	अगर (r852_पढ़ो_reg_dword(dev, R852_HW) & R852_HW_UNKNOWN) अणु
		r852_ग_लिखो_reg(dev, R852_CTL, R852_CTL_RESET | R852_CTL_ON);
		r852_ग_लिखो_reg_dword(dev, R852_HW, R852_HW_ENABLED);
	पूर्ण अन्यथा अणु
		r852_ग_लिखो_reg_dword(dev, R852_HW, R852_HW_ENABLED);
		r852_ग_लिखो_reg(dev, R852_CTL, R852_CTL_RESET | R852_CTL_ON);
	पूर्ण
	msleep(300);
	r852_ग_लिखो_reg(dev, R852_CTL, 0);
पूर्ण


/*
 * Stop the nand engine
 */

अटल व्योम r852_engine_disable(काष्ठा r852_device *dev)
अणु
	r852_ग_लिखो_reg_dword(dev, R852_HW, 0);
	r852_ग_लिखो_reg(dev, R852_CTL, R852_CTL_RESET);
पूर्ण

/*
 * Test अगर card is present
 */

अटल व्योम r852_card_update_present(काष्ठा r852_device *dev)
अणु
	अचिन्हित दीर्घ flags;
	uपूर्णांक8_t reg;

	spin_lock_irqsave(&dev->irqlock, flags);
	reg = r852_पढ़ो_reg(dev, R852_CARD_STA);
	dev->card_detected = !!(reg & R852_CARD_STA_PRESENT);
	spin_unlock_irqrestore(&dev->irqlock, flags);
पूर्ण

/*
 * Update card detection IRQ state according to current card state
 * which is पढ़ो in r852_card_update_present
 */
अटल व्योम r852_update_card_detect(काष्ठा r852_device *dev)
अणु
	पूर्णांक card_detect_reg = r852_पढ़ो_reg(dev, R852_CARD_IRQ_ENABLE);
	dev->card_unstable = 0;

	card_detect_reg &= ~(R852_CARD_IRQ_REMOVE | R852_CARD_IRQ_INSERT);
	card_detect_reg |= R852_CARD_IRQ_GENABLE;

	card_detect_reg |= dev->card_detected ?
		R852_CARD_IRQ_REMOVE : R852_CARD_IRQ_INSERT;

	r852_ग_लिखो_reg(dev, R852_CARD_IRQ_ENABLE, card_detect_reg);
पूर्ण

अटल sमाप_प्रकार r852_media_type_show(काष्ठा device *sys_dev,
			काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा mtd_info *mtd = container_of(sys_dev, काष्ठा mtd_info, dev);
	काष्ठा r852_device *dev = r852_get_dev(mtd);
	अक्षर *data = dev->sm ? "smartmedia" : "xd";

	म_नकल(buf, data);
	वापस म_माप(data);
पूर्ण

अटल DEVICE_ATTR(media_type, S_IRUGO, r852_media_type_show, शून्य);


/* Detect properties of card in slot */
अटल व्योम r852_update_media_status(काष्ठा r852_device *dev)
अणु
	uपूर्णांक8_t reg;
	अचिन्हित दीर्घ flags;
	पूर्णांक पढ़ोonly;

	spin_lock_irqsave(&dev->irqlock, flags);
	अगर (!dev->card_detected) अणु
		message("card removed");
		spin_unlock_irqrestore(&dev->irqlock, flags);
		वापस ;
	पूर्ण

	पढ़ोonly  = r852_पढ़ो_reg(dev, R852_CARD_STA) & R852_CARD_STA_RO;
	reg = r852_पढ़ो_reg(dev, R852_DMA_CAP);
	dev->sm = (reg & (R852_DMA1 | R852_DMA2)) && (reg & R852_SMBIT);

	message("detected %s %s card in slot",
		dev->sm ? "SmartMedia" : "xD",
		पढ़ोonly ? "readonly" : "writeable");

	dev->पढ़ोonly = पढ़ोonly;
	spin_unlock_irqrestore(&dev->irqlock, flags);
पूर्ण

/*
 * Register the nand device
 * Called when the card is detected
 */
अटल पूर्णांक r852_रेजिस्टर_nand_device(काष्ठा r852_device *dev)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(dev->chip);

	WARN_ON(dev->card_रेजिस्टरed);

	mtd->dev.parent = &dev->pci_dev->dev;

	अगर (dev->पढ़ोonly)
		dev->chip->options |= न_अंकD_ROM;

	r852_engine_enable(dev);

	अगर (sm_रेजिस्टर_device(mtd, dev->sm))
		जाओ error1;

	अगर (device_create_file(&mtd->dev, &dev_attr_media_type)) अणु
		message("can't create media type sysfs attribute");
		जाओ error3;
	पूर्ण

	dev->card_रेजिस्टरed = 1;
	वापस 0;
error3:
	WARN_ON(mtd_device_unरेजिस्टर(nand_to_mtd(dev->chip)));
	nand_cleanup(dev->chip);
error1:
	/* Force card redetect */
	dev->card_detected = 0;
	वापस -1;
पूर्ण

/*
 * Unरेजिस्टर the card
 */

अटल व्योम r852_unरेजिस्टर_nand_device(काष्ठा r852_device *dev)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(dev->chip);

	अगर (!dev->card_रेजिस्टरed)
		वापस;

	device_हटाओ_file(&mtd->dev, &dev_attr_media_type);
	WARN_ON(mtd_device_unरेजिस्टर(mtd));
	nand_cleanup(dev->chip);
	r852_engine_disable(dev);
	dev->card_रेजिस्टरed = 0;
पूर्ण

/* Card state updater */
अटल व्योम r852_card_detect_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा r852_device *dev =
		container_of(work, काष्ठा r852_device, card_detect_work.work);

	r852_card_update_present(dev);
	r852_update_card_detect(dev);
	dev->card_unstable = 0;

	/* False alarm */
	अगर (dev->card_detected == dev->card_रेजिस्टरed)
		जाओ निकास;

	/* Read media properties */
	r852_update_media_status(dev);

	/* Register the card */
	अगर (dev->card_detected)
		r852_रेजिस्टर_nand_device(dev);
	अन्यथा
		r852_unरेजिस्टर_nand_device(dev);
निकास:
	r852_update_card_detect(dev);
पूर्ण

/* Ack + disable IRQ generation */
अटल व्योम r852_disable_irqs(काष्ठा r852_device *dev)
अणु
	uपूर्णांक8_t reg;
	reg = r852_पढ़ो_reg(dev, R852_CARD_IRQ_ENABLE);
	r852_ग_लिखो_reg(dev, R852_CARD_IRQ_ENABLE, reg & ~R852_CARD_IRQ_MASK);

	reg = r852_पढ़ो_reg_dword(dev, R852_DMA_IRQ_ENABLE);
	r852_ग_लिखो_reg_dword(dev, R852_DMA_IRQ_ENABLE,
					reg & ~R852_DMA_IRQ_MASK);

	r852_ग_लिखो_reg(dev, R852_CARD_IRQ_STA, R852_CARD_IRQ_MASK);
	r852_ग_लिखो_reg_dword(dev, R852_DMA_IRQ_STA, R852_DMA_IRQ_MASK);
पूर्ण

/* Interrupt handler */
अटल irqवापस_t r852_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा r852_device *dev = (काष्ठा r852_device *)data;

	uपूर्णांक8_t card_status, dma_status;
	irqवापस_t ret = IRQ_NONE;

	spin_lock(&dev->irqlock);

	/* handle card detection पूर्णांकerrupts first */
	card_status = r852_पढ़ो_reg(dev, R852_CARD_IRQ_STA);
	r852_ग_लिखो_reg(dev, R852_CARD_IRQ_STA, card_status);

	अगर (card_status & (R852_CARD_IRQ_INSERT|R852_CARD_IRQ_REMOVE)) अणु

		ret = IRQ_HANDLED;
		dev->card_detected = !!(card_status & R852_CARD_IRQ_INSERT);

		/* we shouldn't receive any पूर्णांकerrupts अगर we रुको क्रम card
			to settle */
		WARN_ON(dev->card_unstable);

		/* disable irqs जबतक card is unstable */
		/* this will समयout DMA अगर active, but better that garbage */
		r852_disable_irqs(dev);

		अगर (dev->card_unstable)
			जाओ out;

		/* let, card state to settle a bit, and then करो the work */
		dev->card_unstable = 1;
		queue_delayed_work(dev->card_workqueue,
			&dev->card_detect_work, msecs_to_jअगरfies(100));
		जाओ out;
	पूर्ण


	/* Handle dma पूर्णांकerrupts */
	dma_status = r852_पढ़ो_reg_dword(dev, R852_DMA_IRQ_STA);
	r852_ग_लिखो_reg_dword(dev, R852_DMA_IRQ_STA, dma_status);

	अगर (dma_status & R852_DMA_IRQ_MASK) अणु

		ret = IRQ_HANDLED;

		अगर (dma_status & R852_DMA_IRQ_ERROR) अणु
			dbg("received dma error IRQ");
			r852_dma_करोne(dev, -EIO);
			complete(&dev->dma_करोne);
			जाओ out;
		पूर्ण

		/* received DMA पूर्णांकerrupt out of nowhere? */
		WARN_ON_ONCE(dev->dma_stage == 0);

		अगर (dev->dma_stage == 0)
			जाओ out;

		/* करोne device access */
		अगर (dev->dma_state == DMA_INTERNAL &&
				(dma_status & R852_DMA_IRQ_INTERNAL)) अणु

			dev->dma_state = DMA_MEMORY;
			dev->dma_stage++;
		पूर्ण

		/* करोne memory DMA */
		अगर (dev->dma_state == DMA_MEMORY &&
				(dma_status & R852_DMA_IRQ_MEMORY)) अणु
			dev->dma_state = DMA_INTERNAL;
			dev->dma_stage++;
		पूर्ण

		/* Enable 2nd half of dma dance */
		अगर (dev->dma_stage == 2)
			r852_dma_enable(dev);

		/* Operation करोne */
		अगर (dev->dma_stage == 3) अणु
			r852_dma_करोne(dev, 0);
			complete(&dev->dma_करोne);
		पूर्ण
		जाओ out;
	पूर्ण

	/* Handle unknown पूर्णांकerrupts */
	अगर (dma_status)
		dbg("bad dma IRQ status = %x", dma_status);

	अगर (card_status & ~R852_CARD_STA_CD)
		dbg("strange card status = %x", card_status);

out:
	spin_unlock(&dev->irqlock);
	वापस ret;
पूर्ण

अटल पूर्णांक r852_attach_chip(काष्ठा nand_chip *chip)
अणु
	अगर (chip->ecc.engine_type != न_अंकD_ECC_ENGINE_TYPE_ON_HOST)
		वापस 0;

	chip->ecc.placement = न_अंकD_ECC_PLACEMENT_INTERLEAVED;
	chip->ecc.size = R852_DMA_LEN;
	chip->ecc.bytes = SM_OOB_SIZE;
	chip->ecc.strength = 2;
	chip->ecc.hwctl = r852_ecc_hwctl;
	chip->ecc.calculate = r852_ecc_calculate;
	chip->ecc.correct = r852_ecc_correct;

	/* TODO: hack */
	chip->ecc.पढ़ो_oob = r852_पढ़ो_oob;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा nand_controller_ops r852_ops = अणु
	.attach_chip = r852_attach_chip,
पूर्ण;

अटल पूर्णांक  r852_probe(काष्ठा pci_dev *pci_dev, स्थिर काष्ठा pci_device_id *id)
अणु
	पूर्णांक error;
	काष्ठा nand_chip *chip;
	काष्ठा r852_device *dev;

	/* pci initialization */
	error = pci_enable_device(pci_dev);

	अगर (error)
		जाओ error1;

	pci_set_master(pci_dev);

	error = dma_set_mask(&pci_dev->dev, DMA_BIT_MASK(32));
	अगर (error)
		जाओ error2;

	error = pci_request_regions(pci_dev, DRV_NAME);

	अगर (error)
		जाओ error3;

	error = -ENOMEM;

	/* init nand chip, but रेजिस्टर it only on card insert */
	chip = kzalloc(माप(काष्ठा nand_chip), GFP_KERNEL);

	अगर (!chip)
		जाओ error4;

	/* commands */
	chip->legacy.cmd_ctrl = r852_cmdctl;
	chip->legacy.रुकोfunc = r852_रुको;
	chip->legacy.dev_पढ़ोy = r852_पढ़ोy;

	/* I/O */
	chip->legacy.पढ़ो_byte = r852_पढ़ो_byte;
	chip->legacy.पढ़ो_buf = r852_पढ़ो_buf;
	chip->legacy.ग_लिखो_buf = r852_ग_लिखो_buf;

	/* init our device काष्ठाure */
	dev = kzalloc(माप(काष्ठा r852_device), GFP_KERNEL);

	अगर (!dev)
		जाओ error5;

	nand_set_controller_data(chip, dev);
	dev->chip = chip;
	dev->pci_dev = pci_dev;
	pci_set_drvdata(pci_dev, dev);

	nand_controller_init(&dev->controller);
	dev->controller.ops = &r852_ops;
	chip->controller = &dev->controller;

	dev->bounce_buffer = dma_alloc_coherent(&pci_dev->dev, R852_DMA_LEN,
		&dev->phys_bounce_buffer, GFP_KERNEL);

	अगर (!dev->bounce_buffer)
		जाओ error6;


	error = -ENODEV;
	dev->mmio = pci_ioremap_bar(pci_dev, 0);

	अगर (!dev->mmio)
		जाओ error7;

	error = -ENOMEM;
	dev->पंचांगp_buffer = kzalloc(SM_SECTOR_SIZE, GFP_KERNEL);

	अगर (!dev->पंचांगp_buffer)
		जाओ error8;

	init_completion(&dev->dma_करोne);

	dev->card_workqueue = create_मुक्तzable_workqueue(DRV_NAME);

	अगर (!dev->card_workqueue)
		जाओ error9;

	INIT_DELAYED_WORK(&dev->card_detect_work, r852_card_detect_work);

	/* shutकरोwn everything - precation */
	r852_engine_disable(dev);
	r852_disable_irqs(dev);

	r852_dma_test(dev);

	dev->irq = pci_dev->irq;
	spin_lock_init(&dev->irqlock);

	dev->card_detected = 0;
	r852_card_update_present(dev);

	/*रेजिस्टर irq handler*/
	error = -ENODEV;
	अगर (request_irq(pci_dev->irq, &r852_irq, IRQF_SHARED,
			  DRV_NAME, dev))
		जाओ error10;

	/* kick initial present test */
	queue_delayed_work(dev->card_workqueue,
		&dev->card_detect_work, 0);


	pr_notice("driver loaded successfully\n");
	वापस 0;

error10:
	destroy_workqueue(dev->card_workqueue);
error9:
	kमुक्त(dev->पंचांगp_buffer);
error8:
	pci_iounmap(pci_dev, dev->mmio);
error7:
	dma_मुक्त_coherent(&pci_dev->dev, R852_DMA_LEN, dev->bounce_buffer,
			  dev->phys_bounce_buffer);
error6:
	kमुक्त(dev);
error5:
	kमुक्त(chip);
error4:
	pci_release_regions(pci_dev);
error3:
error2:
	pci_disable_device(pci_dev);
error1:
	वापस error;
पूर्ण

अटल व्योम r852_हटाओ(काष्ठा pci_dev *pci_dev)
अणु
	काष्ठा r852_device *dev = pci_get_drvdata(pci_dev);

	/* Stop detect workqueue -
		we are going to unरेजिस्टर the device anyway*/
	cancel_delayed_work_sync(&dev->card_detect_work);
	destroy_workqueue(dev->card_workqueue);

	/* Unरेजिस्टर the device, this might make more IO */
	r852_unरेजिस्टर_nand_device(dev);

	/* Stop पूर्णांकerrupts */
	r852_disable_irqs(dev);
	मुक्त_irq(dev->irq, dev);

	/* Cleanup */
	kमुक्त(dev->पंचांगp_buffer);
	pci_iounmap(pci_dev, dev->mmio);
	dma_मुक्त_coherent(&pci_dev->dev, R852_DMA_LEN, dev->bounce_buffer,
			  dev->phys_bounce_buffer);

	kमुक्त(dev->chip);
	kमुक्त(dev);

	/* Shutकरोwn the PCI device */
	pci_release_regions(pci_dev);
	pci_disable_device(pci_dev);
पूर्ण

अटल व्योम r852_shutकरोwn(काष्ठा pci_dev *pci_dev)
अणु
	काष्ठा r852_device *dev = pci_get_drvdata(pci_dev);

	cancel_delayed_work_sync(&dev->card_detect_work);
	r852_disable_irqs(dev);
	synchronize_irq(dev->irq);
	pci_disable_device(pci_dev);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक r852_suspend(काष्ठा device *device)
अणु
	काष्ठा r852_device *dev = dev_get_drvdata(device);

	अगर (dev->ctlreg & R852_CTL_CARDENABLE)
		वापस -EBUSY;

	/* First make sure the detect work is gone */
	cancel_delayed_work_sync(&dev->card_detect_work);

	/* Turn off the पूर्णांकerrupts and stop the device */
	r852_disable_irqs(dev);
	r852_engine_disable(dev);

	/* If card was pulled off just during the suspend, which is very
		unlikely, we will हटाओ it on resume, it too late now
		anyway... */
	dev->card_unstable = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक r852_resume(काष्ठा device *device)
अणु
	काष्ठा r852_device *dev = dev_get_drvdata(device);

	r852_disable_irqs(dev);
	r852_card_update_present(dev);
	r852_engine_disable(dev);


	/* If card status changed, just करो the work */
	अगर (dev->card_detected != dev->card_रेजिस्टरed) अणु
		dbg("card was %s during low power state",
			dev->card_detected ? "added" : "removed");

		queue_delayed_work(dev->card_workqueue,
		&dev->card_detect_work, msecs_to_jअगरfies(1000));
		वापस 0;
	पूर्ण

	/* Otherwise, initialize the card */
	अगर (dev->card_रेजिस्टरed) अणु
		r852_engine_enable(dev);
		nand_select_target(dev->chip, 0);
		nand_reset_op(dev->chip);
		nand_deselect_target(dev->chip);
	पूर्ण

	/* Program card detection IRQ */
	r852_update_card_detect(dev);
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा pci_device_id r852_pci_id_tbl[] = अणु

	अणु PCI_VDEVICE(RICOH, 0x0852), पूर्ण,
	अणु पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(pci, r852_pci_id_tbl);

अटल SIMPLE_DEV_PM_OPS(r852_pm_ops, r852_suspend, r852_resume);

अटल काष्ठा pci_driver r852_pci_driver = अणु
	.name		= DRV_NAME,
	.id_table	= r852_pci_id_tbl,
	.probe		= r852_probe,
	.हटाओ		= r852_हटाओ,
	.shutकरोwn	= r852_shutकरोwn,
	.driver.pm	= &r852_pm_ops,
पूर्ण;

module_pci_driver(r852_pci_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Maxim Levitsky <maximlevitsky@gmail.com>");
MODULE_DESCRIPTION("Ricoh 85xx xD/smartmedia card reader driver");
