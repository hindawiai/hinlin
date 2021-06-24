<शैली गुरु>
/*
 * Toshiba TMIO न_अंकD flash controller driver
 *
 * Slightly murky pre-git history of the driver:
 *
 * Copyright (c) Ian Molton 2004, 2005, 2008
 *    Original work, independent of sharps code. Included hardware ECC support.
 *    Hard ECC did not work क्रम ग_लिखोs in the early revisions.
 * Copyright (c) Dirk Opfer 2005.
 *    Modअगरications developed from sharps code but
 *    NOT containing any, ported onto Ians base.
 * Copyright (c) Chris Humbert 2005
 * Copyright (c) Dmitry Baryshkov 2008
 *    Minor fixes
 *
 * Parts copyright Sebastian Carlier
 *
 * This file is licensed under
 * the terms of the GNU General Public License version 2. This program
 * is licensed "as is" without any warranty of any kind, whether express
 * or implied.
 *
 */


#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/mfd/पंचांगपन.स>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/irq.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ioport.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/nand-ecc-sw-hamming.h>
#समावेश <linux/mtd/rawnand.h>
#समावेश <linux/mtd/partitions.h>
#समावेश <linux/slab.h>

/*--------------------------------------------------------------------------*/

/*
 * न_अंकD Flash Host Controller Configuration Register
 */
#घोषणा CCR_COMMAND	0x04	/* w Command				*/
#घोषणा CCR_BASE	0x10	/* l न_अंकD Flash Control Reg Base Addr	*/
#घोषणा CCR_INTP	0x3d	/* b Interrupt Pin			*/
#घोषणा CCR_INTE	0x48	/* b Interrupt Enable			*/
#घोषणा CCR_EC		0x4a	/* b Event Control			*/
#घोषणा CCR_ICC		0x4c	/* b Internal Clock Control		*/
#घोषणा CCR_ECCC	0x5b	/* b ECC Control			*/
#घोषणा CCR_NFTC	0x60	/* b न_अंकD Flash Transaction Control	*/
#घोषणा CCR_NFM		0x61	/* b न_अंकD Flash Monitor			*/
#घोषणा CCR_NFPSC	0x62	/* b न_अंकD Flash Power Supply Control	*/
#घोषणा CCR_NFDC	0x63	/* b न_अंकD Flash Detect Control		*/

/*
 * न_अंकD Flash Control Register
 */
#घोषणा FCR_DATA	0x00	/* bwl Data Register			*/
#घोषणा FCR_MODE	0x04	/* b Mode Register			*/
#घोषणा FCR_STATUS	0x05	/* b Status Register			*/
#घोषणा FCR_ISR		0x06	/* b Interrupt Status Register		*/
#घोषणा FCR_IMR		0x07	/* b Interrupt Mask Register		*/

/* FCR_MODE Register Command List */
#घोषणा FCR_MODE_DATA	0x94	/* Data Data_Mode */
#घोषणा FCR_MODE_COMMAND 0x95	/* Data Command_Mode */
#घोषणा FCR_MODE_ADDRESS 0x96	/* Data Address_Mode */

#घोषणा FCR_MODE_HWECC_CALC	0xB4	/* HW-ECC Data */
#घोषणा FCR_MODE_HWECC_RESULT	0xD4	/* HW-ECC Calc result Read_Mode */
#घोषणा FCR_MODE_HWECC_RESET	0xF4	/* HW-ECC Reset */

#घोषणा FCR_MODE_POWER_ON	0x0C	/* Power Supply ON  to SSFDC card */
#घोषणा FCR_MODE_POWER_OFF	0x08	/* Power Supply OFF to SSFDC card */

#घोषणा FCR_MODE_LED_OFF	0x00	/* LED OFF */
#घोषणा FCR_MODE_LED_ON		0x04	/* LED ON */

#घोषणा FCR_MODE_EJECT_ON	0x68	/* Ejection events active  */
#घोषणा FCR_MODE_EJECT_OFF	0x08	/* Ejection events ignored */

#घोषणा FCR_MODE_LOCK		0x6C	/* Lock_Mode. Eject Switch Invalid */
#घोषणा FCR_MODE_UNLOCK		0x0C	/* UnLock_Mode. Eject Switch is valid */

#घोषणा FCR_MODE_CONTROLLER_ID	0x40	/* Controller ID Read */
#घोषणा FCR_MODE_STANDBY	0x00	/* SSFDC card Changes Standby State */

#घोषणा FCR_MODE_WE		0x80
#घोषणा FCR_MODE_ECC1		0x40
#घोषणा FCR_MODE_ECC0		0x20
#घोषणा FCR_MODE_CE		0x10
#घोषणा FCR_MODE_PCNT1		0x08
#घोषणा FCR_MODE_PCNT0		0x04
#घोषणा FCR_MODE_ALE		0x02
#घोषणा FCR_MODE_CLE		0x01

#घोषणा FCR_STATUS_BUSY		0x80

/*--------------------------------------------------------------------------*/

काष्ठा पंचांगio_nand अणु
	काष्ठा nand_controller controller;
	काष्ठा nand_chip chip;
	काष्ठा completion comp;

	काष्ठा platक्रमm_device *dev;

	व्योम __iomem *ccr;
	व्योम __iomem *fcr;
	अचिन्हित दीर्घ fcr_base;

	अचिन्हित पूर्णांक irq;

	/* क्रम पंचांगio_nand_पढ़ो_byte */
	u8			पढ़ो;
	अचिन्हित पढ़ो_good:1;
पूर्ण;

अटल अंतरभूत काष्ठा पंचांगio_nand *mtd_to_पंचांगio(काष्ठा mtd_info *mtd)
अणु
	वापस container_of(mtd_to_nand(mtd), काष्ठा पंचांगio_nand, chip);
पूर्ण


/*--------------------------------------------------------------------------*/

अटल व्योम पंचांगio_nand_hwcontrol(काष्ठा nand_chip *chip, पूर्णांक cmd,
				अचिन्हित पूर्णांक ctrl)
अणु
	काष्ठा पंचांगio_nand *पंचांगio = mtd_to_पंचांगio(nand_to_mtd(chip));

	अगर (ctrl & न_अंकD_CTRL_CHANGE) अणु
		u8 mode;

		अगर (ctrl & न_अंकD_NCE) अणु
			mode = FCR_MODE_DATA;

			अगर (ctrl & न_अंकD_CLE)
				mode |=  FCR_MODE_CLE;
			अन्यथा
				mode &= ~FCR_MODE_CLE;

			अगर (ctrl & न_अंकD_ALE)
				mode |=  FCR_MODE_ALE;
			अन्यथा
				mode &= ~FCR_MODE_ALE;
		पूर्ण अन्यथा अणु
			mode = FCR_MODE_STANDBY;
		पूर्ण

		पंचांगio_ioग_लिखो8(mode, पंचांगio->fcr + FCR_MODE);
		पंचांगio->पढ़ो_good = 0;
	पूर्ण

	अगर (cmd != न_अंकD_CMD_NONE)
		पंचांगio_ioग_लिखो8(cmd, chip->legacy.IO_ADDR_W);
पूर्ण

अटल पूर्णांक पंचांगio_nand_dev_पढ़ोy(काष्ठा nand_chip *chip)
अणु
	काष्ठा पंचांगio_nand *पंचांगio = mtd_to_पंचांगio(nand_to_mtd(chip));

	वापस !(पंचांगio_ioपढ़ो8(पंचांगio->fcr + FCR_STATUS) & FCR_STATUS_BUSY);
पूर्ण

अटल irqवापस_t पंचांगio_irq(पूर्णांक irq, व्योम *__पंचांगio)
अणु
	काष्ठा पंचांगio_nand *पंचांगio = __पंचांगio;

	/* disable RDYREQ पूर्णांकerrupt */
	पंचांगio_ioग_लिखो8(0x00, पंचांगio->fcr + FCR_IMR);
	complete(&पंचांगio->comp);

	वापस IRQ_HANDLED;
पूर्ण

/*
  *The TMIO core has a RDYREQ पूर्णांकerrupt on the posedge of #SMRB.
  *This पूर्णांकerrupt is normally disabled, but क्रम दीर्घ operations like
  *erase and ग_लिखो, we enable it to wake us up.  The irq handler
  *disables the पूर्णांकerrupt.
 */
अटल पूर्णांक पंचांगio_nand_रुको(काष्ठा nand_chip *nand_chip)
अणु
	काष्ठा पंचांगio_nand *पंचांगio = mtd_to_पंचांगio(nand_to_mtd(nand_chip));
	दीर्घ समयout;
	u8 status;

	/* enable RDYREQ पूर्णांकerrupt */

	पंचांगio_ioग_लिखो8(0x0f, पंचांगio->fcr + FCR_ISR);
	reinit_completion(&पंचांगio->comp);
	पंचांगio_ioग_लिखो8(0x81, पंचांगio->fcr + FCR_IMR);

	समयout = 400;
	समयout = रुको_क्रम_completion_समयout(&पंचांगio->comp,
					      msecs_to_jअगरfies(समयout));

	अगर (unlikely(!पंचांगio_nand_dev_पढ़ोy(nand_chip))) अणु
		पंचांगio_ioग_लिखो8(0x00, पंचांगio->fcr + FCR_IMR);
		dev_warn(&पंचांगio->dev->dev, "still busy after 400 ms\n");

	पूर्ण अन्यथा अगर (unlikely(!समयout)) अणु
		पंचांगio_ioग_लिखो8(0x00, पंचांगio->fcr + FCR_IMR);
		dev_warn(&पंचांगio->dev->dev, "timeout waiting for interrupt\n");
	पूर्ण

	nand_status_op(nand_chip, &status);
	वापस status;
पूर्ण

/*
  *The TMIO controller combines two 8-bit data bytes पूर्णांकo one 16-bit
  *word. This function separates them so nand_base.c works as expected,
  *especially its न_अंकD_CMD_READID routines.
 *
  *To prevent stale data from being पढ़ो, पंचांगio_nand_hwcontrol() clears
  *पंचांगio->पढ़ो_good.
 */
अटल u_अक्षर पंचांगio_nand_पढ़ो_byte(काष्ठा nand_chip *chip)
अणु
	काष्ठा पंचांगio_nand *पंचांगio = mtd_to_पंचांगio(nand_to_mtd(chip));
	अचिन्हित पूर्णांक data;

	अगर (पंचांगio->पढ़ो_good--)
		वापस पंचांगio->पढ़ो;

	data = पंचांगio_ioपढ़ो16(पंचांगio->fcr + FCR_DATA);
	पंचांगio->पढ़ो = data >> 8;
	वापस data;
पूर्ण

/*
  *The TMIO controller converts an 8-bit न_अंकD पूर्णांकerface to a 16-bit
  *bus पूर्णांकerface, so all data पढ़ोs and ग_लिखोs must be 16-bit wide.
  *Thus, we implement 16-bit versions of the पढ़ो, ग_लिखो, and verअगरy
  *buffer functions.
 */
अटल व्योम
पंचांगio_nand_ग_लिखो_buf(काष्ठा nand_chip *chip, स्थिर u_अक्षर *buf, पूर्णांक len)
अणु
	काष्ठा पंचांगio_nand *पंचांगio = mtd_to_पंचांगio(nand_to_mtd(chip));

	पंचांगio_ioग_लिखो16_rep(पंचांगio->fcr + FCR_DATA, buf, len >> 1);
पूर्ण

अटल व्योम पंचांगio_nand_पढ़ो_buf(काष्ठा nand_chip *chip, u_अक्षर *buf, पूर्णांक len)
अणु
	काष्ठा पंचांगio_nand *पंचांगio = mtd_to_पंचांगio(nand_to_mtd(chip));

	पंचांगio_ioपढ़ो16_rep(पंचांगio->fcr + FCR_DATA, buf, len >> 1);
पूर्ण

अटल व्योम पंचांगio_nand_enable_hwecc(काष्ठा nand_chip *chip, पूर्णांक mode)
अणु
	काष्ठा पंचांगio_nand *पंचांगio = mtd_to_पंचांगio(nand_to_mtd(chip));

	पंचांगio_ioग_लिखो8(FCR_MODE_HWECC_RESET, पंचांगio->fcr + FCR_MODE);
	पंचांगio_ioपढ़ो8(पंचांगio->fcr + FCR_DATA);	/* dummy पढ़ो */
	पंचांगio_ioग_लिखो8(FCR_MODE_HWECC_CALC, पंचांगio->fcr + FCR_MODE);
पूर्ण

अटल पूर्णांक पंचांगio_nand_calculate_ecc(काष्ठा nand_chip *chip, स्थिर u_अक्षर *dat,
				   u_अक्षर *ecc_code)
अणु
	काष्ठा पंचांगio_nand *पंचांगio = mtd_to_पंचांगio(nand_to_mtd(chip));
	अचिन्हित पूर्णांक ecc;

	पंचांगio_ioग_लिखो8(FCR_MODE_HWECC_RESULT, पंचांगio->fcr + FCR_MODE);

	ecc = पंचांगio_ioपढ़ो16(पंचांगio->fcr + FCR_DATA);
	ecc_code[1] = ecc;	/* 000-255 LP7-0 */
	ecc_code[0] = ecc >> 8;	/* 000-255 LP15-8 */
	ecc = पंचांगio_ioपढ़ो16(पंचांगio->fcr + FCR_DATA);
	ecc_code[2] = ecc;	/* 000-255 CP5-0,11b */
	ecc_code[4] = ecc >> 8;	/* 256-511 LP7-0 */
	ecc = पंचांगio_ioपढ़ो16(पंचांगio->fcr + FCR_DATA);
	ecc_code[3] = ecc;	/* 256-511 LP15-8 */
	ecc_code[5] = ecc >> 8;	/* 256-511 CP5-0,11b */

	पंचांगio_ioग_लिखो8(FCR_MODE_DATA, पंचांगio->fcr + FCR_MODE);
	वापस 0;
पूर्ण

अटल पूर्णांक पंचांगio_nand_correct_data(काष्ठा nand_chip *chip, अचिन्हित अक्षर *buf,
				  अचिन्हित अक्षर *पढ़ो_ecc,
				  अचिन्हित अक्षर *calc_ecc)
अणु
	पूर्णांक r0, r1;

	/* assume ecc.size = 512 and ecc.bytes = 6 */
	r0 = ecc_sw_hamming_correct(buf, पढ़ो_ecc, calc_ecc,
				    chip->ecc.size, false);
	अगर (r0 < 0)
		वापस r0;
	r1 = ecc_sw_hamming_correct(buf + 256, पढ़ो_ecc + 3, calc_ecc + 3,
				    chip->ecc.size, false);
	अगर (r1 < 0)
		वापस r1;
	वापस r0 + r1;
पूर्ण

अटल पूर्णांक पंचांगio_hw_init(काष्ठा platक्रमm_device *dev, काष्ठा पंचांगio_nand *पंचांगio)
अणु
	स्थिर काष्ठा mfd_cell *cell = mfd_get_cell(dev);
	पूर्णांक ret;

	अगर (cell->enable) अणु
		ret = cell->enable(dev);
		अगर (ret)
			वापस ret;
	पूर्ण

	/* (4Ch) CLKRUN Enable    1st spcrunc */
	पंचांगio_ioग_लिखो8(0x81, पंचांगio->ccr + CCR_ICC);

	/* (10h)BaseAddress    0x1000 spba.spba2 */
	पंचांगio_ioग_लिखो16(पंचांगio->fcr_base, पंचांगio->ccr + CCR_BASE);
	पंचांगio_ioग_लिखो16(पंचांगio->fcr_base >> 16, पंचांगio->ccr + CCR_BASE + 2);

	/* (04h)Command Register I/O spcmd */
	पंचांगio_ioग_लिखो8(0x02, पंचांगio->ccr + CCR_COMMAND);

	/* (62h) Power Supply Control ssmpwc */
	/* HardPowerOFF - SuspendOFF - PowerSupplyWait_4MS */
	पंचांगio_ioग_लिखो8(0x02, पंचांगio->ccr + CCR_NFPSC);

	/* (63h) Detect Control ssmdtc */
	पंचांगio_ioग_लिखो8(0x02, पंचांगio->ccr + CCR_NFDC);

	/* Interrupt status रेजिस्टर clear sपूर्णांकst */
	पंचांगio_ioग_लिखो8(0x0f, पंचांगio->fcr + FCR_ISR);

	/* After घातer supply, Media are reset smode */
	पंचांगio_ioग_लिखो8(FCR_MODE_POWER_ON, पंचांगio->fcr + FCR_MODE);
	पंचांगio_ioग_लिखो8(FCR_MODE_COMMAND, पंचांगio->fcr + FCR_MODE);
	पंचांगio_ioग_लिखो8(न_अंकD_CMD_RESET, पंचांगio->fcr + FCR_DATA);

	/* Standby Mode smode */
	पंचांगio_ioग_लिखो8(FCR_MODE_STANDBY, पंचांगio->fcr + FCR_MODE);

	mdelay(5);

	वापस 0;
पूर्ण

अटल व्योम पंचांगio_hw_stop(काष्ठा platक्रमm_device *dev, काष्ठा पंचांगio_nand *पंचांगio)
अणु
	स्थिर काष्ठा mfd_cell *cell = mfd_get_cell(dev);

	पंचांगio_ioग_लिखो8(FCR_MODE_POWER_OFF, पंचांगio->fcr + FCR_MODE);
	अगर (cell->disable)
		cell->disable(dev);
पूर्ण

अटल पूर्णांक पंचांगio_attach_chip(काष्ठा nand_chip *chip)
अणु
	अगर (chip->ecc.engine_type != न_अंकD_ECC_ENGINE_TYPE_ON_HOST)
		वापस 0;

	chip->ecc.size = 512;
	chip->ecc.bytes = 6;
	chip->ecc.strength = 2;
	chip->ecc.hwctl = पंचांगio_nand_enable_hwecc;
	chip->ecc.calculate = पंचांगio_nand_calculate_ecc;
	chip->ecc.correct = पंचांगio_nand_correct_data;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा nand_controller_ops पंचांगio_ops = अणु
	.attach_chip = पंचांगio_attach_chip,
पूर्ण;

अटल पूर्णांक पंचांगio_probe(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा पंचांगio_nand_data *data = dev_get_platdata(&dev->dev);
	काष्ठा resource *fcr = platक्रमm_get_resource(dev,
			IORESOURCE_MEM, 0);
	काष्ठा resource *ccr = platक्रमm_get_resource(dev,
			IORESOURCE_MEM, 1);
	पूर्णांक irq = platक्रमm_get_irq(dev, 0);
	काष्ठा पंचांगio_nand *पंचांगio;
	काष्ठा mtd_info *mtd;
	काष्ठा nand_chip *nand_chip;
	पूर्णांक retval;

	अगर (data == शून्य)
		dev_warn(&dev->dev, "NULL platform data!\n");

	पंचांगio = devm_kzalloc(&dev->dev, माप(*पंचांगio), GFP_KERNEL);
	अगर (!पंचांगio)
		वापस -ENOMEM;

	init_completion(&पंचांगio->comp);

	पंचांगio->dev = dev;

	platक्रमm_set_drvdata(dev, पंचांगio);
	nand_chip = &पंचांगio->chip;
	mtd = nand_to_mtd(nand_chip);
	mtd->name = "tmio-nand";
	mtd->dev.parent = &dev->dev;

	nand_controller_init(&पंचांगio->controller);
	पंचांगio->controller.ops = &पंचांगio_ops;
	nand_chip->controller = &पंचांगio->controller;

	पंचांगio->ccr = devm_ioremap(&dev->dev, ccr->start, resource_size(ccr));
	अगर (!पंचांगio->ccr)
		वापस -EIO;

	पंचांगio->fcr_base = fcr->start & 0xfffff;
	पंचांगio->fcr = devm_ioremap(&dev->dev, fcr->start, resource_size(fcr));
	अगर (!पंचांगio->fcr)
		वापस -EIO;

	retval = पंचांगio_hw_init(dev, पंचांगio);
	अगर (retval)
		वापस retval;

	/* Set address of न_अंकD IO lines */
	nand_chip->legacy.IO_ADDR_R = पंचांगio->fcr;
	nand_chip->legacy.IO_ADDR_W = पंचांगio->fcr;

	/* Set address of hardware control function */
	nand_chip->legacy.cmd_ctrl = पंचांगio_nand_hwcontrol;
	nand_chip->legacy.dev_पढ़ोy = पंचांगio_nand_dev_पढ़ोy;
	nand_chip->legacy.पढ़ो_byte = पंचांगio_nand_पढ़ो_byte;
	nand_chip->legacy.ग_लिखो_buf = पंचांगio_nand_ग_लिखो_buf;
	nand_chip->legacy.पढ़ो_buf = पंचांगio_nand_पढ़ो_buf;

	अगर (data)
		nand_chip->badblock_pattern = data->badblock_pattern;

	/* 15 us command delay समय */
	nand_chip->legacy.chip_delay = 15;

	retval = devm_request_irq(&dev->dev, irq, &पंचांगio_irq, 0,
				  dev_name(&dev->dev), पंचांगio);
	अगर (retval) अणु
		dev_err(&dev->dev, "request_irq error %d\n", retval);
		जाओ err_irq;
	पूर्ण

	पंचांगio->irq = irq;
	nand_chip->legacy.रुकोfunc = पंचांगio_nand_रुको;

	/* Scan to find existence of the device */
	retval = nand_scan(nand_chip, 1);
	अगर (retval)
		जाओ err_irq;

	/* Register the partitions */
	retval = mtd_device_parse_रेजिस्टर(mtd,
					   data ? data->part_parsers : शून्य,
					   शून्य,
					   data ? data->partition : शून्य,
					   data ? data->num_partitions : 0);
	अगर (!retval)
		वापस retval;

	nand_cleanup(nand_chip);

err_irq:
	पंचांगio_hw_stop(dev, पंचांगio);
	वापस retval;
पूर्ण

अटल पूर्णांक पंचांगio_हटाओ(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा पंचांगio_nand *पंचांगio = platक्रमm_get_drvdata(dev);
	काष्ठा nand_chip *chip = &पंचांगio->chip;
	पूर्णांक ret;

	ret = mtd_device_unरेजिस्टर(nand_to_mtd(chip));
	WARN_ON(ret);
	nand_cleanup(chip);
	पंचांगio_hw_stop(dev, पंचांगio);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक पंचांगio_suspend(काष्ठा platक्रमm_device *dev, pm_message_t state)
अणु
	स्थिर काष्ठा mfd_cell *cell = mfd_get_cell(dev);

	अगर (cell->suspend)
		cell->suspend(dev);

	पंचांगio_hw_stop(dev, platक्रमm_get_drvdata(dev));
	वापस 0;
पूर्ण

अटल पूर्णांक पंचांगio_resume(काष्ठा platक्रमm_device *dev)
अणु
	स्थिर काष्ठा mfd_cell *cell = mfd_get_cell(dev);

	/* FIXME - is this required or merely another attack of the broken
	 * SHARP platक्रमm? Looks suspicious.
	 */
	पंचांगio_hw_init(dev, platक्रमm_get_drvdata(dev));

	अगर (cell->resume)
		cell->resume(dev);

	वापस 0;
पूर्ण
#अन्यथा
#घोषणा पंचांगio_suspend शून्य
#घोषणा पंचांगio_resume शून्य
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver पंचांगio_driver = अणु
	.driver.name	= "tmio-nand",
	.driver.owner	= THIS_MODULE,
	.probe		= पंचांगio_probe,
	.हटाओ		= पंचांगio_हटाओ,
	.suspend	= पंचांगio_suspend,
	.resume		= पंचांगio_resume,
पूर्ण;

module_platक्रमm_driver(पंचांगio_driver);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Ian Molton, Dirk Opfer, Chris Humbert, Dmitry Baryshkov");
MODULE_DESCRIPTION("NAND flash driver on Toshiba Mobile IO controller");
MODULE_ALIAS("platform:tmio-nand");
