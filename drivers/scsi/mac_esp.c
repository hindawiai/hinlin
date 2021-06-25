<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* mac_esp.c: ESP front-end क्रम Macपूर्णांकosh Quadra प्रणालीs.
 *
 * Adapted from jazz_esp.c and the old mac_esp.c.
 *
 * The pseuकरो DMA algorithm is based on the one used in NetBSD.
 * See sys/arch/mac68k/obio/esp.c क्रम some background inक्रमmation.
 *
 * Copyright (C) 2007-2008 Finn Thain
 */

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/nubus.h>
#समावेश <linux/slab.h>

#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/dma.h>
#समावेश <यंत्र/macपूर्णांकs.h>
#समावेश <यंत्र/macपूर्णांकosh.h>
#समावेश <यंत्र/mac_via.h>

#समावेश <scsi/scsi_host.h>

#समावेश "esp_scsi.h"

#घोषणा DRV_MODULE_NAME     "mac_esp"
#घोषणा PFX                 DRV_MODULE_NAME ": "
#घोषणा DRV_VERSION         "1.000"
#घोषणा DRV_MODULE_RELDATE  "Sept 15, 2007"

#घोषणा MAC_ESP_IO_BASE          0x50F00000
#घोषणा MAC_ESP_REGS_QUADRA      (MAC_ESP_IO_BASE + 0x10000)
#घोषणा MAC_ESP_REGS_QUADRA2     (MAC_ESP_IO_BASE + 0xF000)
#घोषणा MAC_ESP_REGS_QUADRA3     (MAC_ESP_IO_BASE + 0x18000)
#घोषणा MAC_ESP_REGS_SPACING     0x402
#घोषणा MAC_ESP_PDMA_REG         0xF9800024
#घोषणा MAC_ESP_PDMA_REG_SPACING 0x4
#घोषणा MAC_ESP_PDMA_IO_OFFSET   0x100

#घोषणा esp_पढ़ो8(REG)		mac_esp_पढ़ो8(esp, REG)
#घोषणा esp_ग_लिखो8(VAL, REG)	mac_esp_ग_लिखो8(esp, VAL, REG)

काष्ठा mac_esp_priv अणु
	काष्ठा esp *esp;
	व्योम __iomem *pdma_regs;
	व्योम __iomem *pdma_io;
पूर्ण;
अटल काष्ठा esp *esp_chips[2];
अटल DEFINE_SPINLOCK(esp_chips_lock);

#घोषणा MAC_ESP_GET_PRIV(esp) ((काष्ठा mac_esp_priv *) \
			       dev_get_drvdata((esp)->dev))

अटल अंतरभूत व्योम mac_esp_ग_लिखो8(काष्ठा esp *esp, u8 val, अचिन्हित दीर्घ reg)
अणु
	nubus_ग_लिखोb(val, esp->regs + reg * 16);
पूर्ण

अटल अंतरभूत u8 mac_esp_पढ़ो8(काष्ठा esp *esp, अचिन्हित दीर्घ reg)
अणु
	वापस nubus_पढ़ोb(esp->regs + reg * 16);
पूर्ण

अटल व्योम mac_esp_reset_dma(काष्ठा esp *esp)
अणु
	/* Nothing to करो. */
पूर्ण

अटल व्योम mac_esp_dma_drain(काष्ठा esp *esp)
अणु
	/* Nothing to करो. */
पूर्ण

अटल व्योम mac_esp_dma_invalidate(काष्ठा esp *esp)
अणु
	/* Nothing to करो. */
पूर्ण

अटल पूर्णांक mac_esp_dma_error(काष्ठा esp *esp)
अणु
	वापस esp->send_cmd_error;
पूर्ण

अटल अंतरभूत पूर्णांक mac_esp_रुको_क्रम_empty_fअगरo(काष्ठा esp *esp)
अणु
	पूर्णांक i = 500000;

	करो अणु
		अगर (!(esp_पढ़ो8(ESP_FFLAGS) & ESP_FF_FBYTES))
			वापस 0;

		अगर (esp_पढ़ो8(ESP_STATUS) & ESP_STAT_INTR)
			वापस 1;

		udelay(2);
	पूर्ण जबतक (--i);

	prपूर्णांकk(KERN_ERR PFX "FIFO is not empty (sreg %02x)\n",
	       esp_पढ़ो8(ESP_STATUS));
	esp->send_cmd_error = 1;
	वापस 1;
पूर्ण

अटल अंतरभूत पूर्णांक mac_esp_रुको_क्रम_dreq(काष्ठा esp *esp)
अणु
	काष्ठा mac_esp_priv *mep = MAC_ESP_GET_PRIV(esp);
	पूर्णांक i = 500000;

	करो अणु
		अगर (mep->pdma_regs == शून्य) अणु
			अगर (via2_scsi_drq_pending())
				वापस 0;
		पूर्ण अन्यथा अणु
			अगर (nubus_पढ़ोl(mep->pdma_regs) & 0x200)
				वापस 0;
		पूर्ण

		अगर (esp_पढ़ो8(ESP_STATUS) & ESP_STAT_INTR)
			वापस 1;

		udelay(2);
	पूर्ण जबतक (--i);

	prपूर्णांकk(KERN_ERR PFX "PDMA timeout (sreg %02x)\n",
	       esp_पढ़ो8(ESP_STATUS));
	esp->send_cmd_error = 1;
	वापस 1;
पूर्ण

#घोषणा MAC_ESP_PDMA_LOOP(opeअक्रमs) \
	यंत्र अस्थिर ( \
	     "       tstw %1                   \n" \
	     "       jbeq 20f                  \n" \
	     "1:     movew " opeअक्रमs "        \n" \
	     "2:     movew " opeअक्रमs "        \n" \
	     "3:     movew " opeअक्रमs "        \n" \
	     "4:     movew " opeअक्रमs "        \n" \
	     "5:     movew " opeअक्रमs "        \n" \
	     "6:     movew " opeअक्रमs "        \n" \
	     "7:     movew " opeअक्रमs "        \n" \
	     "8:     movew " opeअक्रमs "        \n" \
	     "9:     movew " opeअक्रमs "        \n" \
	     "10:    movew " opeअक्रमs "        \n" \
	     "11:    movew " opeअक्रमs "        \n" \
	     "12:    movew " opeअक्रमs "        \n" \
	     "13:    movew " opeअक्रमs "        \n" \
	     "14:    movew " opeअक्रमs "        \n" \
	     "15:    movew " opeअक्रमs "        \n" \
	     "16:    movew " opeअक्रमs "        \n" \
	     "       subqw #1,%1               \n" \
	     "       jbne 1b                   \n" \
	     "20:    tstw %2                   \n" \
	     "       jbeq 30f                  \n" \
	     "21:    movew " opeअक्रमs "        \n" \
	     "       subqw #1,%2               \n" \
	     "       jbne 21b                  \n" \
	     "30:    tstw %3                   \n" \
	     "       jbeq 40f                  \n" \
	     "31:    moveb " opeअक्रमs "        \n" \
	     "32:    nop                       \n" \
	     "40:                              \n" \
	     "                                 \n" \
	     "       .section __ex_table,\"a\" \n" \
	     "       .align  4                 \n" \
	     "       .long   1b,40b            \n" \
	     "       .long   2b,40b            \n" \
	     "       .long   3b,40b            \n" \
	     "       .long   4b,40b            \n" \
	     "       .long   5b,40b            \n" \
	     "       .long   6b,40b            \n" \
	     "       .long   7b,40b            \n" \
	     "       .long   8b,40b            \n" \
	     "       .long   9b,40b            \n" \
	     "       .long  10b,40b            \n" \
	     "       .long  11b,40b            \n" \
	     "       .long  12b,40b            \n" \
	     "       .long  13b,40b            \n" \
	     "       .long  14b,40b            \n" \
	     "       .long  15b,40b            \n" \
	     "       .long  16b,40b            \n" \
	     "       .long  21b,40b            \n" \
	     "       .long  31b,40b            \n" \
	     "       .long  32b,40b            \n" \
	     "       .previous                 \n" \
	     : "+a" (addr), "+r" (count32), "+r" (count2) \
	     : "g" (count1), "a" (mep->pdma_io))

अटल व्योम mac_esp_send_pdma_cmd(काष्ठा esp *esp, u32 addr, u32 esp_count,
				  u32 dma_count, पूर्णांक ग_लिखो, u8 cmd)
अणु
	काष्ठा mac_esp_priv *mep = MAC_ESP_GET_PRIV(esp);

	esp->send_cmd_error = 0;

	अगर (!ग_लिखो)
		scsi_esp_cmd(esp, ESP_CMD_FLUSH);

	esp_ग_लिखो8((esp_count >> 0) & 0xFF, ESP_TCLOW);
	esp_ग_लिखो8((esp_count >> 8) & 0xFF, ESP_TCMED);

	scsi_esp_cmd(esp, cmd);

	करो अणु
		अचिन्हित पूर्णांक count32 = esp_count >> 5;
		अचिन्हित पूर्णांक count2 = (esp_count & 0x1F) >> 1;
		अचिन्हित पूर्णांक count1 = esp_count & 1;
		अचिन्हित पूर्णांक start_addr = addr;

		अगर (mac_esp_रुको_क्रम_dreq(esp))
			अवरोध;

		अगर (ग_लिखो) अणु
			MAC_ESP_PDMA_LOOP("%4@,%0@+");

			esp_count -= addr - start_addr;
		पूर्ण अन्यथा अणु
			अचिन्हित पूर्णांक n;

			MAC_ESP_PDMA_LOOP("%0@+,%4@");

			अगर (mac_esp_रुको_क्रम_empty_fअगरo(esp))
				अवरोध;

			n = (esp_पढ़ो8(ESP_TCMED) << 8) + esp_पढ़ो8(ESP_TCLOW);
			addr = start_addr + esp_count - n;
			esp_count = n;
		पूर्ण
	पूर्ण जबतक (esp_count);
पूर्ण

अटल पूर्णांक mac_esp_irq_pending(काष्ठा esp *esp)
अणु
	अगर (esp_पढ़ो8(ESP_STATUS) & ESP_STAT_INTR)
		वापस 1;
	वापस 0;
पूर्ण

अटल u32 mac_esp_dma_length_limit(काष्ठा esp *esp, u32 dma_addr, u32 dma_len)
अणु
	वापस dma_len > 0xFFFF ? 0xFFFF : dma_len;
पूर्ण

अटल irqवापस_t mac_scsi_esp_पूर्णांकr(पूर्णांक irq, व्योम *dev_id)
अणु
	पूर्णांक got_पूर्णांकr;

	/*
	 * This is an edge triggered IRQ, so we have to be careful to
	 * aव्योम missing a transition when it is shared by two ESP devices.
	 */

	करो अणु
		got_पूर्णांकr = 0;
		अगर (esp_chips[0] &&
		    (mac_esp_पढ़ो8(esp_chips[0], ESP_STATUS) & ESP_STAT_INTR)) अणु
			(व्योम)scsi_esp_पूर्णांकr(irq, esp_chips[0]);
			got_पूर्णांकr = 1;
		पूर्ण
		अगर (esp_chips[1] &&
		    (mac_esp_पढ़ो8(esp_chips[1], ESP_STATUS) & ESP_STAT_INTR)) अणु
			(व्योम)scsi_esp_पूर्णांकr(irq, esp_chips[1]);
			got_पूर्णांकr = 1;
		पूर्ण
	पूर्ण जबतक (got_पूर्णांकr);

	वापस IRQ_HANDLED;
पूर्ण

अटल काष्ठा esp_driver_ops mac_esp_ops = अणु
	.esp_ग_लिखो8       = mac_esp_ग_लिखो8,
	.esp_पढ़ो8        = mac_esp_पढ़ो8,
	.irq_pending      = mac_esp_irq_pending,
	.dma_length_limit = mac_esp_dma_length_limit,
	.reset_dma        = mac_esp_reset_dma,
	.dma_drain        = mac_esp_dma_drain,
	.dma_invalidate   = mac_esp_dma_invalidate,
	.send_dma_cmd     = mac_esp_send_pdma_cmd,
	.dma_error        = mac_esp_dma_error,
पूर्ण;

अटल पूर्णांक esp_mac_probe(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा scsi_host_ढाँचा *tpnt = &scsi_esp_ढाँचा;
	काष्ठा Scsi_Host *host;
	काष्ठा esp *esp;
	पूर्णांक err;
	काष्ठा mac_esp_priv *mep;

	अगर (!MACH_IS_MAC)
		वापस -ENODEV;

	अगर (dev->id > 1)
		वापस -ENODEV;

	host = scsi_host_alloc(tpnt, माप(काष्ठा esp));

	err = -ENOMEM;
	अगर (!host)
		जाओ fail;

	host->max_id = 8;
	host->dma_boundary = PAGE_SIZE - 1;
	esp = shost_priv(host);

	esp->host = host;
	esp->dev = &dev->dev;

	esp->command_block = kzalloc(16, GFP_KERNEL);
	अगर (!esp->command_block)
		जाओ fail_unlink;
	esp->command_block_dma = (dma_addr_t)esp->command_block;

	esp->scsi_id = 7;
	host->this_id = esp->scsi_id;
	esp->scsi_id_mask = 1 << esp->scsi_id;

	mep = kzalloc(माप(काष्ठा mac_esp_priv), GFP_KERNEL);
	अगर (!mep)
		जाओ fail_मुक्त_command_block;
	mep->esp = esp;
	platक्रमm_set_drvdata(dev, mep);

	चयन (macपूर्णांकosh_config->scsi_type) अणु
	हाल MAC_SCSI_QUADRA:
		esp->cfreq     = 16500000;
		esp->regs      = (व्योम __iomem *)MAC_ESP_REGS_QUADRA;
		mep->pdma_io   = esp->regs + MAC_ESP_PDMA_IO_OFFSET;
		mep->pdma_regs = शून्य;
		अवरोध;
	हाल MAC_SCSI_QUADRA2:
		esp->cfreq     = 25000000;
		esp->regs      = (व्योम __iomem *)(MAC_ESP_REGS_QUADRA2 +
				 dev->id * MAC_ESP_REGS_SPACING);
		mep->pdma_io   = esp->regs + MAC_ESP_PDMA_IO_OFFSET;
		mep->pdma_regs = (व्योम __iomem *)(MAC_ESP_PDMA_REG +
				 dev->id * MAC_ESP_PDMA_REG_SPACING);
		nubus_ग_लिखोl(0x1d1, mep->pdma_regs);
		अवरोध;
	हाल MAC_SCSI_QUADRA3:
		/* These quadras have a real DMA controller (the PSC) but we
		 * करोn't know how to drive it so we must use PIO instead.
		 */
		esp->cfreq     = 25000000;
		esp->regs      = (व्योम __iomem *)MAC_ESP_REGS_QUADRA3;
		mep->pdma_io   = शून्य;
		mep->pdma_regs = शून्य;
		अवरोध;
	पूर्ण
	esp->fअगरo_reg = esp->regs + ESP_FDATA * 16;

	esp->ops = &mac_esp_ops;
	esp->flags = ESP_FLAG_NO_DMA_MAP;
	अगर (mep->pdma_io == शून्य) अणु
		prपूर्णांकk(KERN_INFO PFX "using PIO for controller %d\n", dev->id);
		esp_ग_लिखो8(0, ESP_TCLOW);
		esp_ग_लिखो8(0, ESP_TCMED);
		esp->flags |= ESP_FLAG_DISABLE_SYNC;
		mac_esp_ops.send_dma_cmd = esp_send_pio_cmd;
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_INFO PFX "using PDMA for controller %d\n", dev->id);
	पूर्ण

	host->irq = IRQ_MAC_SCSI;

	/* The request_irq() call is पूर्णांकended to succeed क्रम the first device
	 * and fail क्रम the second device.
	 */
	err = request_irq(host->irq, mac_scsi_esp_पूर्णांकr, 0, "ESP", शून्य);
	spin_lock(&esp_chips_lock);
	अगर (err < 0 && esp_chips[!dev->id] == शून्य) अणु
		spin_unlock(&esp_chips_lock);
		जाओ fail_मुक्त_priv;
	पूर्ण
	esp_chips[dev->id] = esp;
	spin_unlock(&esp_chips_lock);

	err = scsi_esp_रेजिस्टर(esp);
	अगर (err)
		जाओ fail_मुक्त_irq;

	वापस 0;

fail_मुक्त_irq:
	spin_lock(&esp_chips_lock);
	esp_chips[dev->id] = शून्य;
	अगर (esp_chips[!dev->id] == शून्य) अणु
		spin_unlock(&esp_chips_lock);
		मुक्त_irq(host->irq, शून्य);
	पूर्ण अन्यथा
		spin_unlock(&esp_chips_lock);
fail_मुक्त_priv:
	kमुक्त(mep);
fail_मुक्त_command_block:
	kमुक्त(esp->command_block);
fail_unlink:
	scsi_host_put(host);
fail:
	वापस err;
पूर्ण

अटल पूर्णांक esp_mac_हटाओ(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा mac_esp_priv *mep = platक्रमm_get_drvdata(dev);
	काष्ठा esp *esp = mep->esp;
	अचिन्हित पूर्णांक irq = esp->host->irq;

	scsi_esp_unरेजिस्टर(esp);

	spin_lock(&esp_chips_lock);
	esp_chips[dev->id] = शून्य;
	अगर (esp_chips[!dev->id] == शून्य) अणु
		spin_unlock(&esp_chips_lock);
		मुक्त_irq(irq, शून्य);
	पूर्ण अन्यथा
		spin_unlock(&esp_chips_lock);

	kमुक्त(mep);

	kमुक्त(esp->command_block);

	scsi_host_put(esp->host);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver esp_mac_driver = अणु
	.probe    = esp_mac_probe,
	.हटाओ   = esp_mac_हटाओ,
	.driver   = अणु
		.name	= DRV_MODULE_NAME,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(esp_mac_driver);

MODULE_DESCRIPTION("Mac ESP SCSI driver");
MODULE_AUTHOR("Finn Thain");
MODULE_LICENSE("GPL v2");
MODULE_VERSION(DRV_VERSION);
MODULE_ALIAS("platform:" DRV_MODULE_NAME);
