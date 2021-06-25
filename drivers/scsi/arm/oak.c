<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Oak Generic NCR5380 driver
 *
 * Copyright 1995-2002, Russell King
 */

#समावेश <linux/module.h>
#समावेश <linux/ioport.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/init.h>

#समावेश <यंत्र/ecard.h>
#समावेश <यंत्र/पन.स>

#समावेश <scsi/scsi_host.h>

#घोषणा priv(host)			((काष्ठा NCR5380_hostdata *)(host)->hostdata)

#घोषणा NCR5380_पढ़ो(reg)           पढ़ोb(hostdata->io + ((reg) << 2))
#घोषणा NCR5380_ग_लिखो(reg, value)   ग_लिखोb(value, hostdata->io + ((reg) << 2))

#घोषणा NCR5380_dma_xfer_len		NCR5380_dma_xfer_none
#घोषणा NCR5380_dma_recv_setup		oakscsi_pपढ़ो
#घोषणा NCR5380_dma_send_setup		oakscsi_pग_लिखो
#घोषणा NCR5380_dma_residual		NCR5380_dma_residual_none

#घोषणा NCR5380_queue_command		oakscsi_queue_command
#घोषणा NCR5380_info			oakscsi_info

#घोषणा NCR5380_implementation_fields	/* none */

#समावेश "../NCR5380.h"

#अघोषित START_DMA_INITIATOR_RECEIVE_REG
#घोषणा START_DMA_INITIATOR_RECEIVE_REG	(128 + 7)

#घोषणा STAT	((128 + 16) << 2)
#घोषणा DATA	((128 + 8) << 2)

अटल अंतरभूत पूर्णांक oakscsi_pग_लिखो(काष्ठा NCR5380_hostdata *hostdata,
                                 अचिन्हित अक्षर *addr, पूर्णांक len)
अणु
  u8 __iomem *base = hostdata->io;

prपूर्णांकk("writing %p len %d\n",addr, len);

  जबतक(1)
  अणु
    पूर्णांक status;
    जबतक (((status = पढ़ोw(base + STAT)) & 0x100)==0);
  पूर्ण
  वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक oakscsi_pपढ़ो(काष्ठा NCR5380_hostdata *hostdata,
                                अचिन्हित अक्षर *addr, पूर्णांक len)
अणु
  u8 __iomem *base = hostdata->io;

prपूर्णांकk("reading %p len %d\n", addr, len);
  जबतक(len > 0)
  अणु
    अचिन्हित पूर्णांक status, समयout;
    अचिन्हित दीर्घ b;
    
    समयout = 0x01FFFFFF;
    
    जबतक (((status = पढ़ोw(base + STAT)) & 0x100)==0)
    अणु
      समयout--;
      अगर(status & 0x200 || !समयout)
      अणु
        prपूर्णांकk("status = %08X\n", status);
        वापस -1;
      पूर्ण
    पूर्ण

    अगर(len >= 128)
    अणु
      पढ़ोsw(base + DATA, addr, 128);
      addr += 128;
      len -= 128;
    पूर्ण
    अन्यथा
    अणु
      b = (अचिन्हित दीर्घ) पढ़ोw(base + DATA);
      *addr ++ = b;
      len -= 1;
      अगर(len)
        *addr ++ = b>>8;
      len -= 1;
    पूर्ण
  पूर्ण
  वापस 0;
पूर्ण

#अघोषित STAT
#अघोषित DATA

#समावेश "../NCR5380.c"

अटल काष्ठा scsi_host_ढाँचा oakscsi_ढाँचा = अणु
	.module			= THIS_MODULE,
	.name			= "Oak 16-bit SCSI",
	.info			= oakscsi_info,
	.queuecommand		= oakscsi_queue_command,
	.eh_पात_handler	= NCR5380_पात,
	.eh_host_reset_handler	= NCR5380_host_reset,
	.can_queue		= 16,
	.this_id		= 7,
	.sg_tablesize		= SG_ALL,
	.cmd_per_lun		= 2,
	.dma_boundary		= PAGE_SIZE - 1,
	.proc_name		= "oakscsi",
	.cmd_size		= NCR5380_CMD_SIZE,
	.max_sectors		= 128,
पूर्ण;

अटल पूर्णांक oakscsi_probe(काष्ठा expansion_card *ec, स्थिर काष्ठा ecard_id *id)
अणु
	काष्ठा Scsi_Host *host;
	पूर्णांक ret;

	ret = ecard_request_resources(ec);
	अगर (ret)
		जाओ out;

	host = scsi_host_alloc(&oakscsi_ढाँचा, माप(काष्ठा NCR5380_hostdata));
	अगर (!host) अणु
		ret = -ENOMEM;
		जाओ release;
	पूर्ण

	priv(host)->io = ioremap(ecard_resource_start(ec, ECARD_RES_MEMC),
	                         ecard_resource_len(ec, ECARD_RES_MEMC));
	अगर (!priv(host)->io) अणु
		ret = -ENOMEM;
		जाओ unreg;
	पूर्ण

	host->irq = NO_IRQ;

	ret = NCR5380_init(host, FLAG_DMA_FIXUP | FLAG_LATE_DMA_SETUP);
	अगर (ret)
		जाओ out_unmap;

	NCR5380_maybe_reset_bus(host);

	ret = scsi_add_host(host, &ec->dev);
	अगर (ret)
		जाओ out_निकास;

	scsi_scan_host(host);
	जाओ out;

 out_निकास:
	NCR5380_निकास(host);
 out_unmap:
	iounmap(priv(host)->io);
 unreg:
	scsi_host_put(host);
 release:
	ecard_release_resources(ec);
 out:
	वापस ret;
पूर्ण

अटल व्योम oakscsi_हटाओ(काष्ठा expansion_card *ec)
अणु
	काष्ठा Scsi_Host *host = ecard_get_drvdata(ec);
	व्योम __iomem *base = priv(host)->io;

	ecard_set_drvdata(ec, शून्य);
	scsi_हटाओ_host(host);

	NCR5380_निकास(host);
	scsi_host_put(host);
	iounmap(base);
	ecard_release_resources(ec);
पूर्ण

अटल स्थिर काष्ठा ecard_id oakscsi_cids[] = अणु
	अणु MANU_OAK, PROD_OAK_SCSI पूर्ण,
	अणु 0xffff, 0xffff पूर्ण
पूर्ण;

अटल काष्ठा ecard_driver oakscsi_driver = अणु
	.probe		= oakscsi_probe,
	.हटाओ		= oakscsi_हटाओ,
	.id_table	= oakscsi_cids,
	.drv = अणु
		.name		= "oakscsi",
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init oakscsi_init(व्योम)
अणु
	वापस ecard_रेजिस्टर_driver(&oakscsi_driver);
पूर्ण

अटल व्योम __निकास oakscsi_निकास(व्योम)
अणु
	ecard_हटाओ_driver(&oakscsi_driver);
पूर्ण

module_init(oakscsi_init);
module_निकास(oakscsi_निकास);

MODULE_AUTHOR("Russell King");
MODULE_DESCRIPTION("Oak SCSI driver");
MODULE_LICENSE("GPL");

