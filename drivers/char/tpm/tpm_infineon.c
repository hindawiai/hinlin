<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Description:
 * Device Driver क्रम the Infineon Technologies
 * SLD 9630 TT 1.1 and SLB 9635 TT 1.2 Trusted Platक्रमm Module
 * Specअगरications at www.trustedcomputinggroup.org
 *
 * Copyright (C) 2005, Marcel Selhorst <tpmdd@selhorst.net>
 * Sirrix AG - security technologies <tpmdd@sirrix.com> and
 * Applied Data Security Group, Ruhr-University Bochum, Germany
 * Project-Homepage: http://www.trust.rub.de/projects/linux-device-driver-infineon-tpm/ 
 */

#समावेश <linux/init.h>
#समावेश <linux/pnp.h>
#समावेश "tpm.h"

/* Infineon specअगरic definitions */
/* maximum number of WTX-packages */
#घोषणा	TPM_MAX_WTX_PACKAGES 	50
/* msleep-Time क्रम WTX-packages */
#घोषणा	TPM_WTX_MSLEEP_TIME 	20
/* msleep-Time --> Interval to check status रेजिस्टर */
#घोषणा	TPM_MSLEEP_TIME 	3
/* gives number of max. msleep()-calls beक्रमe throwing समयout */
#घोषणा	TPM_MAX_TRIES		5000
#घोषणा	TPM_INFINEON_DEV_VEN_VALUE	0x15D1

#घोषणा TPM_INF_IO_PORT		0x0
#घोषणा TPM_INF_IO_MEM		0x1

#घोषणा TPM_INF_ADDR		0x0
#घोषणा TPM_INF_DATA		0x1

काष्ठा tpm_inf_dev अणु
	पूर्णांक iotype;

	व्योम __iomem *mem_base;	/* MMIO ioremap'd addr */
	अचिन्हित दीर्घ map_base;	/* phys MMIO base */
	अचिन्हित दीर्घ map_size;	/* MMIO region size */
	अचिन्हित पूर्णांक index_off;	/* index रेजिस्टर offset */

	अचिन्हित पूर्णांक data_regs;	/* Data रेजिस्टरs */
	अचिन्हित पूर्णांक data_size;

	अचिन्हित पूर्णांक config_port;	/* IO Port config index reg */
	अचिन्हित पूर्णांक config_size;
पूर्ण;

अटल काष्ठा tpm_inf_dev tpm_dev;

अटल अंतरभूत व्योम tpm_data_out(अचिन्हित अक्षर data, अचिन्हित अक्षर offset)
अणु
	अगर (tpm_dev.iotype == TPM_INF_IO_PORT)
		outb(data, tpm_dev.data_regs + offset);
	अन्यथा
		ग_लिखोb(data, tpm_dev.mem_base + tpm_dev.data_regs + offset);
पूर्ण

अटल अंतरभूत अचिन्हित अक्षर tpm_data_in(अचिन्हित अक्षर offset)
अणु
	अगर (tpm_dev.iotype == TPM_INF_IO_PORT)
		वापस inb(tpm_dev.data_regs + offset);
	अन्यथा
		वापस पढ़ोb(tpm_dev.mem_base + tpm_dev.data_regs + offset);
पूर्ण

अटल अंतरभूत व्योम tpm_config_out(अचिन्हित अक्षर data, अचिन्हित अक्षर offset)
अणु
	अगर (tpm_dev.iotype == TPM_INF_IO_PORT)
		outb(data, tpm_dev.config_port + offset);
	अन्यथा
		ग_लिखोb(data, tpm_dev.mem_base + tpm_dev.index_off + offset);
पूर्ण

अटल अंतरभूत अचिन्हित अक्षर tpm_config_in(अचिन्हित अक्षर offset)
अणु
	अगर (tpm_dev.iotype == TPM_INF_IO_PORT)
		वापस inb(tpm_dev.config_port + offset);
	अन्यथा
		वापस पढ़ोb(tpm_dev.mem_base + tpm_dev.index_off + offset);
पूर्ण

/* TPM header definitions */
क्रमागत infineon_tpm_header अणु
	TPM_VL_VER = 0x01,
	TPM_VL_CHANNEL_CONTROL = 0x07,
	TPM_VL_CHANNEL_PERSONALISATION = 0x0A,
	TPM_VL_CHANNEL_TPM = 0x0B,
	TPM_VL_CONTROL = 0x00,
	TPM_INF_NAK = 0x15,
	TPM_CTRL_WTX = 0x10,
	TPM_CTRL_WTX_ABORT = 0x18,
	TPM_CTRL_WTX_ABORT_ACK = 0x18,
	TPM_CTRL_ERROR = 0x20,
	TPM_CTRL_CHAININGACK = 0x40,
	TPM_CTRL_CHAINING = 0x80,
	TPM_CTRL_DATA = 0x04,
	TPM_CTRL_DATA_CHA = 0x84,
	TPM_CTRL_DATA_CHA_ACK = 0xC4
पूर्ण;

क्रमागत infineon_tpm_रेजिस्टर अणु
	WRFIFO = 0x00,
	RDFIFO = 0x01,
	STAT = 0x02,
	CMD = 0x03
पूर्ण;

क्रमागत infineon_tpm_command_bits अणु
	CMD_DIS = 0x00,
	CMD_LP = 0x01,
	CMD_RES = 0x02,
	CMD_IRQC = 0x06
पूर्ण;

क्रमागत infineon_tpm_status_bits अणु
	STAT_XFE = 0x00,
	STAT_LPA = 0x01,
	STAT_FOK = 0x02,
	STAT_TOK = 0x03,
	STAT_IRQA = 0x06,
	STAT_RDA = 0x07
पूर्ण;

/* some outgoing values */
क्रमागत infineon_tpm_values अणु
	CHIP_ID1 = 0x20,
	CHIP_ID2 = 0x21,
	TPM_DAR = 0x30,
	RESET_LP_IRQC_DISABLE = 0x41,
	ENABLE_REGISTER_PAIR = 0x55,
	IOLIMH = 0x60,
	IOLIML = 0x61,
	DISABLE_REGISTER_PAIR = 0xAA,
	IDVENL = 0xF1,
	IDVENH = 0xF2,
	IDPDL = 0xF3,
	IDPDH = 0xF4
पूर्ण;

अटल पूर्णांक number_of_wtx;

अटल पूर्णांक empty_fअगरo(काष्ठा tpm_chip *chip, पूर्णांक clear_wrfअगरo)
अणु
	पूर्णांक status;
	पूर्णांक check = 0;
	पूर्णांक i;

	अगर (clear_wrfअगरo) अणु
		क्रम (i = 0; i < 4096; i++) अणु
			status = tpm_data_in(WRFIFO);
			अगर (status == 0xff) अणु
				अगर (check == 5)
					अवरोध;
				अन्यथा
					check++;
			पूर्ण
		पूर्ण
	पूर्ण
	/* Note: The values which are currently in the FIFO of the TPM
	   are thrown away since there is no usage क्रम them. Usually,
	   this has nothing to say, since the TPM will give its answer
	   immediately or will be पातed anyway, so the data here is
	   usually garbage and useless.
	   We have to clean this, because the next communication with
	   the TPM would be rubbish, अगर there is still some old data
	   in the Read FIFO.
	 */
	i = 0;
	करो अणु
		status = tpm_data_in(RDFIFO);
		status = tpm_data_in(STAT);
		i++;
		अगर (i == TPM_MAX_TRIES)
			वापस -EIO;
	पूर्ण जबतक ((status & (1 << STAT_RDA)) != 0);
	वापस 0;
पूर्ण

अटल पूर्णांक रुको(काष्ठा tpm_chip *chip, पूर्णांक रुको_क्रम_bit)
अणु
	पूर्णांक status;
	पूर्णांक i;
	क्रम (i = 0; i < TPM_MAX_TRIES; i++) अणु
		status = tpm_data_in(STAT);
		/* check the status-रेजिस्टर अगर रुको_क्रम_bit is set */
		अगर (status & 1 << रुको_क्रम_bit)
			अवरोध;
		tpm_msleep(TPM_MSLEEP_TIME);
	पूर्ण
	अगर (i == TPM_MAX_TRIES) अणु	/* समयout occurs */
		अगर (रुको_क्रम_bit == STAT_XFE)
			dev_err(&chip->dev, "Timeout in wait(STAT_XFE)\n");
		अगर (रुको_क्रम_bit == STAT_RDA)
			dev_err(&chip->dev, "Timeout in wait(STAT_RDA)\n");
		वापस -EIO;
	पूर्ण
	वापस 0;
पूर्ण;

अटल व्योम रुको_and_send(काष्ठा tpm_chip *chip, u8 sendbyte)
अणु
	रुको(chip, STAT_XFE);
	tpm_data_out(sendbyte, WRFIFO);
पूर्ण

    /* Note: WTX means Waiting-Time-Extension. Whenever the TPM needs more
       calculation समय, it sends a WTX-package, which has to be acknowledged
       or पातed. This usually occurs अगर you are hammering the TPM with key
       creation. Set the maximum number of WTX-packages in the definitions
       above, अगर the number is reached, the रुकोing-समय will be denied
       and the TPM command has to be resend.
     */

अटल व्योम tpm_wtx(काष्ठा tpm_chip *chip)
अणु
	number_of_wtx++;
	dev_info(&chip->dev, "Granting WTX (%02d / %02d)\n",
		 number_of_wtx, TPM_MAX_WTX_PACKAGES);
	रुको_and_send(chip, TPM_VL_VER);
	रुको_and_send(chip, TPM_CTRL_WTX);
	रुको_and_send(chip, 0x00);
	रुको_and_send(chip, 0x00);
	tpm_msleep(TPM_WTX_MSLEEP_TIME);
पूर्ण

अटल व्योम tpm_wtx_पात(काष्ठा tpm_chip *chip)
अणु
	dev_info(&chip->dev, "Aborting WTX\n");
	रुको_and_send(chip, TPM_VL_VER);
	रुको_and_send(chip, TPM_CTRL_WTX_ABORT);
	रुको_and_send(chip, 0x00);
	रुको_and_send(chip, 0x00);
	number_of_wtx = 0;
	tpm_msleep(TPM_WTX_MSLEEP_TIME);
पूर्ण

अटल पूर्णांक tpm_inf_recv(काष्ठा tpm_chip *chip, u8 * buf, माप_प्रकार count)
अणु
	पूर्णांक i;
	पूर्णांक ret;
	u32 size = 0;
	number_of_wtx = 0;

recv_begin:
	/* start receiving header */
	क्रम (i = 0; i < 4; i++) अणु
		ret = रुको(chip, STAT_RDA);
		अगर (ret)
			वापस -EIO;
		buf[i] = tpm_data_in(RDFIFO);
	पूर्ण

	अगर (buf[0] != TPM_VL_VER) अणु
		dev_err(&chip->dev,
			"Wrong transport protocol implementation!\n");
		वापस -EIO;
	पूर्ण

	अगर (buf[1] == TPM_CTRL_DATA) अणु
		/* size of the data received */
		size = ((buf[2] << 8) | buf[3]);

		क्रम (i = 0; i < size; i++) अणु
			रुको(chip, STAT_RDA);
			buf[i] = tpm_data_in(RDFIFO);
		पूर्ण

		अगर ((size == 0x6D00) && (buf[1] == 0x80)) अणु
			dev_err(&chip->dev, "Error handling on vendor layer!\n");
			वापस -EIO;
		पूर्ण

		क्रम (i = 0; i < size; i++)
			buf[i] = buf[i + 6];

		size = size - 6;
		वापस size;
	पूर्ण

	अगर (buf[1] == TPM_CTRL_WTX) अणु
		dev_info(&chip->dev, "WTX-package received\n");
		अगर (number_of_wtx < TPM_MAX_WTX_PACKAGES) अणु
			tpm_wtx(chip);
			जाओ recv_begin;
		पूर्ण अन्यथा अणु
			tpm_wtx_पात(chip);
			जाओ recv_begin;
		पूर्ण
	पूर्ण

	अगर (buf[1] == TPM_CTRL_WTX_ABORT_ACK) अणु
		dev_info(&chip->dev, "WTX-abort acknowledged\n");
		वापस size;
	पूर्ण

	अगर (buf[1] == TPM_CTRL_ERROR) अणु
		dev_err(&chip->dev, "ERROR-package received:\n");
		अगर (buf[4] == TPM_INF_NAK)
			dev_err(&chip->dev,
				"-> Negative acknowledgement"
				" - retransmit command!\n");
		वापस -EIO;
	पूर्ण
	वापस -EIO;
पूर्ण

अटल पूर्णांक tpm_inf_send(काष्ठा tpm_chip *chip, u8 * buf, माप_प्रकार count)
अणु
	पूर्णांक i;
	पूर्णांक ret;
	u8 count_high, count_low, count_4, count_3, count_2, count_1;

	/* Disabling Reset, LP and IRQC */
	tpm_data_out(RESET_LP_IRQC_DISABLE, CMD);

	ret = empty_fअगरo(chip, 1);
	अगर (ret) अणु
		dev_err(&chip->dev, "Timeout while clearing FIFO\n");
		वापस -EIO;
	पूर्ण

	ret = रुको(chip, STAT_XFE);
	अगर (ret)
		वापस -EIO;

	count_4 = (count & 0xff000000) >> 24;
	count_3 = (count & 0x00ff0000) >> 16;
	count_2 = (count & 0x0000ff00) >> 8;
	count_1 = (count & 0x000000ff);
	count_high = ((count + 6) & 0xffffff00) >> 8;
	count_low = ((count + 6) & 0x000000ff);

	/* Sending Header */
	रुको_and_send(chip, TPM_VL_VER);
	रुको_and_send(chip, TPM_CTRL_DATA);
	रुको_and_send(chip, count_high);
	रुको_and_send(chip, count_low);

	/* Sending Data Header */
	रुको_and_send(chip, TPM_VL_VER);
	रुको_and_send(chip, TPM_VL_CHANNEL_TPM);
	रुको_and_send(chip, count_4);
	रुको_and_send(chip, count_3);
	रुको_and_send(chip, count_2);
	रुको_and_send(chip, count_1);

	/* Sending Data */
	क्रम (i = 0; i < count; i++) अणु
		रुको_and_send(chip, buf[i]);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम tpm_inf_cancel(काष्ठा tpm_chip *chip)
अणु
	/*
	   Since we are using the legacy mode to communicate
	   with the TPM, we have no cancel functions, but have
	   a workaround क्रम पूर्णांकerrupting the TPM through WTX.
	 */
पूर्ण

अटल u8 tpm_inf_status(काष्ठा tpm_chip *chip)
अणु
	वापस tpm_data_in(STAT);
पूर्ण

अटल स्थिर काष्ठा tpm_class_ops tpm_inf = अणु
	.recv = tpm_inf_recv,
	.send = tpm_inf_send,
	.cancel = tpm_inf_cancel,
	.status = tpm_inf_status,
	.req_complete_mask = 0,
	.req_complete_val = 0,
पूर्ण;

अटल स्थिर काष्ठा pnp_device_id tpm_inf_pnp_tbl[] = अणु
	/* Infineon TPMs */
	अणु"IFX0101", 0पूर्ण,
	अणु"IFX0102", 0पूर्ण,
	अणु"", 0पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pnp, tpm_inf_pnp_tbl);

अटल पूर्णांक tpm_inf_pnp_probe(काष्ठा pnp_dev *dev,
				       स्थिर काष्ठा pnp_device_id *dev_id)
अणु
	पूर्णांक rc = 0;
	u8 iol, ioh;
	पूर्णांक venकरोrid[2];
	पूर्णांक version[2];
	पूर्णांक productid[2];
	स्थिर अक्षर *chipname;
	काष्ठा tpm_chip *chip;

	/* पढ़ो IO-ports through PnP */
	अगर (pnp_port_valid(dev, 0) && pnp_port_valid(dev, 1) &&
	    !(pnp_port_flags(dev, 0) & IORESOURCE_DISABLED)) अणु

		tpm_dev.iotype = TPM_INF_IO_PORT;

		tpm_dev.config_port = pnp_port_start(dev, 0);
		tpm_dev.config_size = pnp_port_len(dev, 0);
		tpm_dev.data_regs = pnp_port_start(dev, 1);
		tpm_dev.data_size = pnp_port_len(dev, 1);
		अगर ((tpm_dev.data_size < 4) || (tpm_dev.config_size < 2)) अणु
			rc = -EINVAL;
			जाओ err_last;
		पूर्ण
		dev_info(&dev->dev, "Found %s with ID %s\n",
			 dev->name, dev_id->id);
		अगर (!((tpm_dev.data_regs >> 8) & 0xff)) अणु
			rc = -EINVAL;
			जाओ err_last;
		पूर्ण
		/* publish my base address and request region */
		अगर (request_region(tpm_dev.data_regs, tpm_dev.data_size,
				   "tpm_infineon0") == शून्य) अणु
			rc = -EINVAL;
			जाओ err_last;
		पूर्ण
		अगर (request_region(tpm_dev.config_port, tpm_dev.config_size,
				   "tpm_infineon0") == शून्य) अणु
			release_region(tpm_dev.data_regs, tpm_dev.data_size);
			rc = -EINVAL;
			जाओ err_last;
		पूर्ण
	पूर्ण अन्यथा अगर (pnp_mem_valid(dev, 0) &&
		   !(pnp_mem_flags(dev, 0) & IORESOURCE_DISABLED)) अणु

		tpm_dev.iotype = TPM_INF_IO_MEM;

		tpm_dev.map_base = pnp_mem_start(dev, 0);
		tpm_dev.map_size = pnp_mem_len(dev, 0);

		dev_info(&dev->dev, "Found %s with ID %s\n",
			 dev->name, dev_id->id);

		/* publish my base address and request region */
		अगर (request_mem_region(tpm_dev.map_base, tpm_dev.map_size,
				       "tpm_infineon0") == शून्य) अणु
			rc = -EINVAL;
			जाओ err_last;
		पूर्ण

		tpm_dev.mem_base = ioremap(tpm_dev.map_base, tpm_dev.map_size);
		अगर (tpm_dev.mem_base == शून्य) अणु
			release_mem_region(tpm_dev.map_base, tpm_dev.map_size);
			rc = -EINVAL;
			जाओ err_last;
		पूर्ण

		/*
		 * The only known MMIO based Infineon TPM प्रणाली provides
		 * a single large mem region with the device config
		 * रेजिस्टरs at the शेष TPM_ADDR.  The data रेजिस्टरs
		 * seem like they could be placed anywhere within the MMIO
		 * region, but lets just put them at zero offset.
		 */
		tpm_dev.index_off = TPM_ADDR;
		tpm_dev.data_regs = 0x0;
	पूर्ण अन्यथा अणु
		rc = -EINVAL;
		जाओ err_last;
	पूर्ण

	/* query chip क्रम its venकरोr, its version number a.s.o. */
	tpm_config_out(ENABLE_REGISTER_PAIR, TPM_INF_ADDR);
	tpm_config_out(IDVENL, TPM_INF_ADDR);
	venकरोrid[1] = tpm_config_in(TPM_INF_DATA);
	tpm_config_out(IDVENH, TPM_INF_ADDR);
	venकरोrid[0] = tpm_config_in(TPM_INF_DATA);
	tpm_config_out(IDPDL, TPM_INF_ADDR);
	productid[1] = tpm_config_in(TPM_INF_DATA);
	tpm_config_out(IDPDH, TPM_INF_ADDR);
	productid[0] = tpm_config_in(TPM_INF_DATA);
	tpm_config_out(CHIP_ID1, TPM_INF_ADDR);
	version[1] = tpm_config_in(TPM_INF_DATA);
	tpm_config_out(CHIP_ID2, TPM_INF_ADDR);
	version[0] = tpm_config_in(TPM_INF_DATA);

	चयन ((productid[0] << 8) | productid[1]) अणु
	हाल 6:
		chipname = " (SLD 9630 TT 1.1)";
		अवरोध;
	हाल 11:
		chipname = " (SLB 9635 TT 1.2)";
		अवरोध;
	शेष:
		chipname = " (unknown chip)";
		अवरोध;
	पूर्ण

	अगर ((venकरोrid[0] << 8 | venकरोrid[1]) == (TPM_INFINEON_DEV_VEN_VALUE)) अणु

		/* configure TPM with IO-ports */
		tpm_config_out(IOLIMH, TPM_INF_ADDR);
		tpm_config_out((tpm_dev.data_regs >> 8) & 0xff, TPM_INF_DATA);
		tpm_config_out(IOLIML, TPM_INF_ADDR);
		tpm_config_out((tpm_dev.data_regs & 0xff), TPM_INF_DATA);

		/* control अगर IO-ports are set correctly */
		tpm_config_out(IOLIMH, TPM_INF_ADDR);
		ioh = tpm_config_in(TPM_INF_DATA);
		tpm_config_out(IOLIML, TPM_INF_ADDR);
		iol = tpm_config_in(TPM_INF_DATA);

		अगर ((ioh << 8 | iol) != tpm_dev.data_regs) अणु
			dev_err(&dev->dev,
				"Could not set IO-data registers to 0x%x\n",
				tpm_dev.data_regs);
			rc = -EIO;
			जाओ err_release_region;
		पूर्ण

		/* activate रेजिस्टर */
		tpm_config_out(TPM_DAR, TPM_INF_ADDR);
		tpm_config_out(0x01, TPM_INF_DATA);
		tpm_config_out(DISABLE_REGISTER_PAIR, TPM_INF_ADDR);

		/* disable RESET, LP and IRQC */
		tpm_data_out(RESET_LP_IRQC_DISABLE, CMD);

		/* Finally, we're करोne, prपूर्णांक some infos */
		dev_info(&dev->dev, "TPM found: "
			 "config base 0x%lx, "
			 "data base 0x%lx, "
			 "chip version 0x%02x%02x, "
			 "vendor id 0x%x%x (Infineon), "
			 "product id 0x%02x%02x"
			 "%s\n",
			 tpm_dev.iotype == TPM_INF_IO_PORT ?
			 tpm_dev.config_port :
			 tpm_dev.map_base + tpm_dev.index_off,
			 tpm_dev.iotype == TPM_INF_IO_PORT ?
			 tpm_dev.data_regs :
			 tpm_dev.map_base + tpm_dev.data_regs,
			 version[0], version[1],
			 venकरोrid[0], venकरोrid[1],
			 productid[0], productid[1], chipname);

		chip = tpmm_chip_alloc(&dev->dev, &tpm_inf);
		अगर (IS_ERR(chip)) अणु
			rc = PTR_ERR(chip);
			जाओ err_release_region;
		पूर्ण

		rc = tpm_chip_रेजिस्टर(chip);
		अगर (rc)
			जाओ err_release_region;

		वापस 0;
	पूर्ण अन्यथा अणु
		rc = -ENODEV;
		जाओ err_release_region;
	पूर्ण

err_release_region:
	अगर (tpm_dev.iotype == TPM_INF_IO_PORT) अणु
		release_region(tpm_dev.data_regs, tpm_dev.data_size);
		release_region(tpm_dev.config_port, tpm_dev.config_size);
	पूर्ण अन्यथा अणु
		iounmap(tpm_dev.mem_base);
		release_mem_region(tpm_dev.map_base, tpm_dev.map_size);
	पूर्ण

err_last:
	वापस rc;
पूर्ण

अटल व्योम tpm_inf_pnp_हटाओ(काष्ठा pnp_dev *dev)
अणु
	काष्ठा tpm_chip *chip = pnp_get_drvdata(dev);

	tpm_chip_unरेजिस्टर(chip);

	अगर (tpm_dev.iotype == TPM_INF_IO_PORT) अणु
		release_region(tpm_dev.data_regs, tpm_dev.data_size);
		release_region(tpm_dev.config_port,
			       tpm_dev.config_size);
	पूर्ण अन्यथा अणु
		iounmap(tpm_dev.mem_base);
		release_mem_region(tpm_dev.map_base, tpm_dev.map_size);
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक tpm_inf_resume(काष्ठा device *dev)
अणु
	/* Re-configure TPM after suspending */
	tpm_config_out(ENABLE_REGISTER_PAIR, TPM_INF_ADDR);
	tpm_config_out(IOLIMH, TPM_INF_ADDR);
	tpm_config_out((tpm_dev.data_regs >> 8) & 0xff, TPM_INF_DATA);
	tpm_config_out(IOLIML, TPM_INF_ADDR);
	tpm_config_out((tpm_dev.data_regs & 0xff), TPM_INF_DATA);
	/* activate रेजिस्टर */
	tpm_config_out(TPM_DAR, TPM_INF_ADDR);
	tpm_config_out(0x01, TPM_INF_DATA);
	tpm_config_out(DISABLE_REGISTER_PAIR, TPM_INF_ADDR);
	/* disable RESET, LP and IRQC */
	tpm_data_out(RESET_LP_IRQC_DISABLE, CMD);
	वापस tpm_pm_resume(dev);
पूर्ण
#पूर्ण_अगर
अटल SIMPLE_DEV_PM_OPS(tpm_inf_pm, tpm_pm_suspend, tpm_inf_resume);

अटल काष्ठा pnp_driver tpm_inf_pnp_driver = अणु
	.name = "tpm_inf_pnp",
	.id_table = tpm_inf_pnp_tbl,
	.probe = tpm_inf_pnp_probe,
	.हटाओ = tpm_inf_pnp_हटाओ,
	.driver = अणु
		.pm = &tpm_inf_pm,
	पूर्ण
पूर्ण;

module_pnp_driver(tpm_inf_pnp_driver);

MODULE_AUTHOR("Marcel Selhorst <tpmdd@sirrix.com>");
MODULE_DESCRIPTION("Driver for Infineon TPM SLD 9630 TT 1.1 / SLB 9635 TT 1.2");
MODULE_VERSION("1.9.2");
MODULE_LICENSE("GPL");
