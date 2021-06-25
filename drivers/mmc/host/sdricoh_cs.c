<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  sdricoh_cs.c - driver क्रम Ricoh Secure Digital Card Readers that can be
 *     found on some Ricoh RL5c476 II cardbus bridge
 *
 *  Copyright (C) 2006 - 2008 Sascha Sommer <saschasommer@मुक्तnet.de>
 */

/*
#घोषणा DEBUG
#घोषणा VERBOSE_DEBUG
*/
#समावेश <linux/delay.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/ioport.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/scatterlist.h>

#समावेश <pcmcia/cistpl.h>
#समावेश <pcmcia/ds.h>
#समावेश <linux/पन.स>

#समावेश <linux/mmc/host.h>
#समावेश <linux/mmc/mmc.h>

#घोषणा DRIVER_NAME "sdricoh_cs"

अटल अचिन्हित पूर्णांक चयनlocked;

/* i/o region */
#घोषणा SDRICOH_PCI_REGION 0
#घोषणा SDRICOH_PCI_REGION_SIZE 0x1000

/* रेजिस्टरs */
#घोषणा R104_VERSION     0x104
#घोषणा R200_CMD         0x200
#घोषणा R204_CMD_ARG     0x204
#घोषणा R208_DATAIO      0x208
#घोषणा R20C_RESP        0x20c
#घोषणा R21C_STATUS      0x21c
#घोषणा R2E0_INIT        0x2e0
#घोषणा R2E4_STATUS_RESP 0x2e4
#घोषणा R2F0_RESET       0x2f0
#घोषणा R224_MODE        0x224
#घोषणा R226_BLOCKSIZE   0x226
#घोषणा R228_POWER       0x228
#घोषणा R230_DATA        0x230

/* flags क्रम the R21C_STATUS रेजिस्टर */
#घोषणा STATUS_CMD_FINISHED      0x00000001
#घोषणा STATUS_TRANSFER_FINISHED 0x00000004
#घोषणा STATUS_CARD_INSERTED     0x00000020
#घोषणा STATUS_CARD_LOCKED       0x00000080
#घोषणा STATUS_CMD_TIMEOUT       0x00400000
#घोषणा STATUS_READY_TO_READ     0x01000000
#घोषणा STATUS_READY_TO_WRITE    0x02000000
#घोषणा STATUS_BUSY              0x40000000

/* समयouts */
#घोषणा SDRICOH_CMD_TIMEOUT_US	1000000
#घोषणा SDRICOH_DATA_TIMEOUT_US	1000000

/* list of supported pcmcia devices */
अटल स्थिर काष्ठा pcmcia_device_id pcmcia_ids[] = अणु
	/* venकरोr and device strings followed by their crc32 hashes */
	PCMCIA_DEVICE_PROD_ID12("RICOH", "Bay1Controller", 0xd9f522ed,
				0xc3901202),
	PCMCIA_DEVICE_PROD_ID12("RICOH", "Bay Controller", 0xd9f522ed,
				0xace80909),
	PCMCIA_DEVICE_शून्य,
पूर्ण;

MODULE_DEVICE_TABLE(pcmcia, pcmcia_ids);

/* mmc privdata */
काष्ठा sdricoh_host अणु
	काष्ठा device *dev;
	काष्ठा mmc_host *mmc;	/* MMC काष्ठाure */
	अचिन्हित अक्षर __iomem *iobase;
	काष्ठा pci_dev *pci_dev;
	पूर्णांक app_cmd;
पूर्ण;

/***************** रेजिस्टर i/o helper functions *****************************/

अटल अंतरभूत अचिन्हित पूर्णांक sdricoh_पढ़ोl(काष्ठा sdricoh_host *host,
					 अचिन्हित पूर्णांक reg)
अणु
	अचिन्हित पूर्णांक value = पढ़ोl(host->iobase + reg);
	dev_vdbg(host->dev, "rl %x 0x%x\n", reg, value);
	वापस value;
पूर्ण

अटल अंतरभूत व्योम sdricoh_ग_लिखोl(काष्ठा sdricoh_host *host, अचिन्हित पूर्णांक reg,
				  अचिन्हित पूर्णांक value)
अणु
	ग_लिखोl(value, host->iobase + reg);
	dev_vdbg(host->dev, "wl %x 0x%x\n", reg, value);

पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक sdricoh_पढ़ोw(काष्ठा sdricoh_host *host,
					 अचिन्हित पूर्णांक reg)
अणु
	अचिन्हित पूर्णांक value = पढ़ोw(host->iobase + reg);
	dev_vdbg(host->dev, "rb %x 0x%x\n", reg, value);
	वापस value;
पूर्ण

अटल अंतरभूत व्योम sdricoh_ग_लिखोw(काष्ठा sdricoh_host *host, अचिन्हित पूर्णांक reg,
					 अचिन्हित लघु value)
अणु
	ग_लिखोw(value, host->iobase + reg);
	dev_vdbg(host->dev, "ww %x 0x%x\n", reg, value);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक sdricoh_पढ़ोb(काष्ठा sdricoh_host *host,
					 अचिन्हित पूर्णांक reg)
अणु
	अचिन्हित पूर्णांक value = पढ़ोb(host->iobase + reg);
	dev_vdbg(host->dev, "rb %x 0x%x\n", reg, value);
	वापस value;
पूर्ण

अटल bool sdricoh_status_ok(काष्ठा sdricoh_host *host, अचिन्हित पूर्णांक status,
			      अचिन्हित पूर्णांक wanted)
अणु
	sdricoh_ग_लिखोl(host, R2E4_STATUS_RESP, status);
	वापस status & wanted;
पूर्ण

अटल पूर्णांक sdricoh_query_status(काष्ठा sdricoh_host *host, अचिन्हित पूर्णांक wanted)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक status = 0;
	काष्ठा device *dev = host->dev;

	ret = पढ़ो_poll_समयout(sdricoh_पढ़ोl, status,
				sdricoh_status_ok(host, status, wanted),
				32, SDRICOH_DATA_TIMEOUT_US, false,
				host, R21C_STATUS);
	अगर (ret) अणु
		dev_err(dev, "query_status: timeout waiting for %x\n", wanted);
		वापस -ETIMEDOUT;
	पूर्ण

	/* करो not करो this check in the loop as some commands fail otherwise */
	अगर (status & 0x7F0000) अणु
		dev_err(dev, "waiting for status bit %x failed\n", wanted);
		वापस -EINVAL;
	पूर्ण
	वापस 0;

पूर्ण

अटल पूर्णांक sdricoh_mmc_cmd(काष्ठा sdricoh_host *host, काष्ठा mmc_command *cmd)
अणु
	अचिन्हित पूर्णांक status, समयout_us;
	पूर्णांक ret;
	अचिन्हित अक्षर opcode = cmd->opcode;

	/* reset status reg? */
	sdricoh_ग_लिखोl(host, R21C_STATUS, 0x18);

	/* MMC_APP_CMDs need some special handling */
	अगर (host->app_cmd) अणु
		opcode |= 64;
		host->app_cmd = 0;
	पूर्ण अन्यथा अगर (opcode == MMC_APP_CMD)
		host->app_cmd = 1;

	/* fill parameters */
	sdricoh_ग_लिखोl(host, R204_CMD_ARG, cmd->arg);
	sdricoh_ग_लिखोl(host, R200_CMD, (0x10000 << 8) | opcode);

	/* रुको क्रम command completion */
	अगर (!opcode)
		वापस 0;

	समयout_us = cmd->busy_समयout ? cmd->busy_समयout * 1000 :
		SDRICOH_CMD_TIMEOUT_US;

	ret = पढ़ो_poll_समयout(sdricoh_पढ़ोl, status,
			sdricoh_status_ok(host, status, STATUS_CMD_FINISHED),
			32, समयout_us, false,
			host, R21C_STATUS);

	/*
	 * Don't check for timeout status in the loop, as it's not always reset
	 * correctly.
	 */
	अगर (ret || status & STATUS_CMD_TIMEOUT)
		वापस -ETIMEDOUT;

	वापस 0;
पूर्ण

अटल पूर्णांक sdricoh_reset(काष्ठा sdricoh_host *host)
अणु
	dev_dbg(host->dev, "reset\n");
	sdricoh_ग_लिखोl(host, R2F0_RESET, 0x10001);
	sdricoh_ग_लिखोl(host, R2E0_INIT, 0x10000);
	अगर (sdricoh_पढ़ोl(host, R2E0_INIT) != 0x10000)
		वापस -EIO;
	sdricoh_ग_लिखोl(host, R2E0_INIT, 0x10007);

	sdricoh_ग_लिखोl(host, R224_MODE, 0x2000000);
	sdricoh_ग_लिखोl(host, R228_POWER, 0xe0);


	/* status रेजिस्टर ? */
	sdricoh_ग_लिखोl(host, R21C_STATUS, 0x18);

	वापस 0;
पूर्ण

अटल पूर्णांक sdricoh_blockio(काष्ठा sdricoh_host *host, पूर्णांक पढ़ो,
				u8 *buf, पूर्णांक len)
अणु
	पूर्णांक size;
	u32 data = 0;
	/* रुको until the data is available */
	अगर (पढ़ो) अणु
		अगर (sdricoh_query_status(host, STATUS_READY_TO_READ))
			वापस -ETIMEDOUT;
		sdricoh_ग_लिखोl(host, R21C_STATUS, 0x18);
		/* पढ़ो data */
		जबतक (len) अणु
			data = sdricoh_पढ़ोl(host, R230_DATA);
			size = min(len, 4);
			len -= size;
			जबतक (size) अणु
				*buf = data & 0xFF;
				buf++;
				data >>= 8;
				size--;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (sdricoh_query_status(host, STATUS_READY_TO_WRITE))
			वापस -ETIMEDOUT;
		sdricoh_ग_लिखोl(host, R21C_STATUS, 0x18);
		/* ग_लिखो data */
		जबतक (len) अणु
			size = min(len, 4);
			len -= size;
			जबतक (size) अणु
				data >>= 8;
				data |= (u32)*buf << 24;
				buf++;
				size--;
			पूर्ण
			sdricoh_ग_लिखोl(host, R230_DATA, data);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम sdricoh_request(काष्ठा mmc_host *mmc, काष्ठा mmc_request *mrq)
अणु
	काष्ठा sdricoh_host *host = mmc_priv(mmc);
	काष्ठा mmc_command *cmd = mrq->cmd;
	काष्ठा mmc_data *data = cmd->data;
	काष्ठा device *dev = host->dev;
	पूर्णांक i;

	dev_dbg(dev, "=============================\n");
	dev_dbg(dev, "sdricoh_request opcode=%i\n", cmd->opcode);

	sdricoh_ग_लिखोl(host, R21C_STATUS, 0x18);

	/* पढ़ो/ग_लिखो commands seem to require this */
	अगर (data) अणु
		sdricoh_ग_लिखोw(host, R226_BLOCKSIZE, data->blksz);
		sdricoh_ग_लिखोl(host, R208_DATAIO, 0);
	पूर्ण

	cmd->error = sdricoh_mmc_cmd(host, cmd);

	/* पढ़ो response buffer */
	अगर (cmd->flags & MMC_RSP_PRESENT) अणु
		अगर (cmd->flags & MMC_RSP_136) अणु
			/* CRC is stripped so we need to करो some shअगरting. */
			क्रम (i = 0; i < 4; i++) अणु
				cmd->resp[i] =
				    sdricoh_पढ़ोl(host,
						  R20C_RESP + (3 - i) * 4) << 8;
				अगर (i != 3)
					cmd->resp[i] |=
					    sdricoh_पढ़ोb(host, R20C_RESP +
							  (3 - i) * 4 - 1);
			पूर्ण
		पूर्ण अन्यथा
			cmd->resp[0] = sdricoh_पढ़ोl(host, R20C_RESP);
	पूर्ण

	/* transfer data */
	अगर (data && cmd->error == 0) अणु
		dev_dbg(dev, "transfer: blksz %i blocks %i sg_len %i "
			"sg length %i\n", data->blksz, data->blocks,
			data->sg_len, data->sg->length);

		/* enter data पढ़ोing mode */
		sdricoh_ग_लिखोl(host, R21C_STATUS, 0x837f031e);
		क्रम (i = 0; i < data->blocks; i++) अणु
			माप_प्रकार len = data->blksz;
			u8 *buf;
			काष्ठा page *page;
			पूर्णांक result;
			page = sg_page(data->sg);

			buf = kmap(page) + data->sg->offset + (len * i);
			result =
				sdricoh_blockio(host,
					data->flags & MMC_DATA_READ, buf, len);
			kunmap(page);
			flush_dcache_page(page);
			अगर (result) अणु
				dev_err(dev, "sdricoh_request: cmd %i "
					"block transfer failed\n", cmd->opcode);
				cmd->error = result;
				अवरोध;
			पूर्ण अन्यथा
				data->bytes_xfered += len;
		पूर्ण

		sdricoh_ग_लिखोl(host, R208_DATAIO, 1);

		अगर (sdricoh_query_status(host, STATUS_TRANSFER_FINISHED)) अणु
			dev_err(dev, "sdricoh_request: transfer end error\n");
			cmd->error = -EINVAL;
		पूर्ण
	पूर्ण
	/* FIXME check busy flag */

	mmc_request_करोne(mmc, mrq);
	dev_dbg(dev, "=============================\n");
पूर्ण

अटल व्योम sdricoh_set_ios(काष्ठा mmc_host *mmc, काष्ठा mmc_ios *ios)
अणु
	काष्ठा sdricoh_host *host = mmc_priv(mmc);
	dev_dbg(host->dev, "set_ios\n");

	अगर (ios->घातer_mode == MMC_POWER_ON) अणु
		sdricoh_ग_लिखोl(host, R228_POWER, 0xc0e0);

		अगर (ios->bus_width == MMC_BUS_WIDTH_4) अणु
			sdricoh_ग_लिखोl(host, R224_MODE, 0x2000300);
			sdricoh_ग_लिखोl(host, R228_POWER, 0x40e0);
		पूर्ण अन्यथा अणु
			sdricoh_ग_लिखोl(host, R224_MODE, 0x2000340);
		पूर्ण

	पूर्ण अन्यथा अगर (ios->घातer_mode == MMC_POWER_UP) अणु
		sdricoh_ग_लिखोl(host, R224_MODE, 0x2000320);
		sdricoh_ग_लिखोl(host, R228_POWER, 0xe0);
	पूर्ण
पूर्ण

अटल पूर्णांक sdricoh_get_ro(काष्ठा mmc_host *mmc)
अणु
	काष्ठा sdricoh_host *host = mmc_priv(mmc);
	अचिन्हित पूर्णांक status;

	status = sdricoh_पढ़ोl(host, R21C_STATUS);
	sdricoh_ग_लिखोl(host, R2E4_STATUS_RESP, status);

	/* some notebooks seem to have the locked flag चयनed */
	अगर (चयनlocked)
		वापस !(status & STATUS_CARD_LOCKED);

	वापस (status & STATUS_CARD_LOCKED);
पूर्ण

अटल स्थिर काष्ठा mmc_host_ops sdricoh_ops = अणु
	.request = sdricoh_request,
	.set_ios = sdricoh_set_ios,
	.get_ro = sdricoh_get_ro,
पूर्ण;

/* initialize the control and रेजिस्टर it to the mmc framework */
अटल पूर्णांक sdricoh_init_mmc(काष्ठा pci_dev *pci_dev,
			    काष्ठा pcmcia_device *pcmcia_dev)
अणु
	पूर्णांक result;
	व्योम __iomem *iobase;
	काष्ठा mmc_host *mmc;
	काष्ठा sdricoh_host *host;
	काष्ठा device *dev = &pcmcia_dev->dev;
	/* map iomem */
	अगर (pci_resource_len(pci_dev, SDRICOH_PCI_REGION) !=
	    SDRICOH_PCI_REGION_SIZE) अणु
		dev_dbg(dev, "unexpected pci resource len\n");
		वापस -ENODEV;
	पूर्ण
	iobase =
	    pci_iomap(pci_dev, SDRICOH_PCI_REGION, SDRICOH_PCI_REGION_SIZE);
	अगर (!iobase) अणु
		dev_err(dev, "unable to map iobase\n");
		वापस -ENODEV;
	पूर्ण
	/* check version? */
	अगर (पढ़ोl(iobase + R104_VERSION) != 0x4000) अणु
		dev_dbg(dev, "no supported mmc controller found\n");
		result = -ENODEV;
		जाओ unmap_io;
	पूर्ण
	/* allocate privdata */
	mmc = pcmcia_dev->priv =
	    mmc_alloc_host(माप(काष्ठा sdricoh_host), &pcmcia_dev->dev);
	अगर (!mmc) अणु
		dev_err(dev, "mmc_alloc_host failed\n");
		result = -ENOMEM;
		जाओ unmap_io;
	पूर्ण
	host = mmc_priv(mmc);

	host->iobase = iobase;
	host->dev = dev;
	host->pci_dev = pci_dev;

	mmc->ops = &sdricoh_ops;

	/* FIXME: frequency and voltage handling is करोne by the controller
	 */
	mmc->f_min = 450000;
	mmc->f_max = 24000000;
	mmc->ocr_avail = MMC_VDD_32_33 | MMC_VDD_33_34;
	mmc->caps |= MMC_CAP_4_BIT_DATA;

	mmc->max_seg_size = 1024 * 512;
	mmc->max_blk_size = 512;

	/* reset the controller */
	अगर (sdricoh_reset(host)) अणु
		dev_dbg(dev, "could not reset\n");
		result = -EIO;
		जाओ मुक्त_host;
	पूर्ण

	result = mmc_add_host(mmc);

	अगर (!result) अणु
		dev_dbg(dev, "mmc host registered\n");
		वापस 0;
	पूर्ण
मुक्त_host:
	mmc_मुक्त_host(mmc);
unmap_io:
	pci_iounmap(pci_dev, iobase);
	वापस result;
पूर्ण

/* search क्रम supported mmc controllers */
अटल पूर्णांक sdricoh_pcmcia_probe(काष्ठा pcmcia_device *pcmcia_dev)
अणु
	काष्ठा pci_dev *pci_dev = शून्य;

	dev_info(&pcmcia_dev->dev, "Searching MMC controller for pcmcia device"
		" %s %s ...\n", pcmcia_dev->prod_id[0], pcmcia_dev->prod_id[1]);

	/* search pci cardbus bridge that contains the mmc controller */
	/* the io region is alपढ़ोy claimed by yenta_socket... */
	जबतक ((pci_dev =
		pci_get_device(PCI_VENDOR_ID_RICOH, PCI_DEVICE_ID_RICOH_RL5C476,
			       pci_dev))) अणु
		/* try to init the device */
		अगर (!sdricoh_init_mmc(pci_dev, pcmcia_dev)) अणु
			dev_info(&pcmcia_dev->dev, "MMC controller found\n");
			वापस 0;
		पूर्ण

	पूर्ण
	dev_err(&pcmcia_dev->dev, "No MMC controller was found.\n");
	वापस -ENODEV;
पूर्ण

अटल व्योम sdricoh_pcmcia_detach(काष्ठा pcmcia_device *link)
अणु
	काष्ठा mmc_host *mmc = link->priv;

	dev_dbg(&link->dev, "detach\n");

	/* हटाओ mmc host */
	अगर (mmc) अणु
		काष्ठा sdricoh_host *host = mmc_priv(mmc);
		mmc_हटाओ_host(mmc);
		pci_iounmap(host->pci_dev, host->iobase);
		pci_dev_put(host->pci_dev);
		mmc_मुक्त_host(mmc);
	पूर्ण
	pcmcia_disable_device(link);

पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक sdricoh_pcmcia_suspend(काष्ठा pcmcia_device *link)
अणु
	dev_dbg(&link->dev, "suspend\n");
	वापस 0;
पूर्ण

अटल पूर्णांक sdricoh_pcmcia_resume(काष्ठा pcmcia_device *link)
अणु
	काष्ठा mmc_host *mmc = link->priv;
	dev_dbg(&link->dev, "resume\n");
	sdricoh_reset(mmc_priv(mmc));
	वापस 0;
पूर्ण
#अन्यथा
#घोषणा sdricoh_pcmcia_suspend शून्य
#घोषणा sdricoh_pcmcia_resume शून्य
#पूर्ण_अगर

अटल काष्ठा pcmcia_driver sdricoh_driver = अणु
	.name = DRIVER_NAME,
	.probe = sdricoh_pcmcia_probe,
	.हटाओ = sdricoh_pcmcia_detach,
	.id_table = pcmcia_ids,
	.suspend = sdricoh_pcmcia_suspend,
	.resume = sdricoh_pcmcia_resume,
पूर्ण;
module_pcmcia_driver(sdricoh_driver);

module_param(चयनlocked, uपूर्णांक, 0444);

MODULE_AUTHOR("Sascha Sommer <saschasommer@freenet.de>");
MODULE_DESCRIPTION("Ricoh PCMCIA Secure Digital Interface driver");
MODULE_LICENSE("GPL");

MODULE_PARM_DESC(चयनlocked, "Switch the cards locked status."
		"Use this when unlocked cards are shown readonly (default 0)");
