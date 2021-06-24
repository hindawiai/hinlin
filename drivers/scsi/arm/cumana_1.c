<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Generic Generic NCR5380 driver
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
#घोषणा NCR5380_पढ़ो(reg)		cumanascsi_पढ़ो(hostdata, reg)
#घोषणा NCR5380_ग_लिखो(reg, value)	cumanascsi_ग_लिखो(hostdata, reg, value)

#घोषणा NCR5380_dma_xfer_len		cumanascsi_dma_xfer_len
#घोषणा NCR5380_dma_recv_setup		cumanascsi_pपढ़ो
#घोषणा NCR5380_dma_send_setup		cumanascsi_pग_लिखो
#घोषणा NCR5380_dma_residual		NCR5380_dma_residual_none

#घोषणा NCR5380_पूर्णांकr			cumanascsi_पूर्णांकr
#घोषणा NCR5380_queue_command		cumanascsi_queue_command
#घोषणा NCR5380_info			cumanascsi_info

#घोषणा NCR5380_implementation_fields	\
	अचिन्हित ctrl

काष्ठा NCR5380_hostdata;
अटल u8 cumanascsi_पढ़ो(काष्ठा NCR5380_hostdata *, अचिन्हित पूर्णांक);
अटल व्योम cumanascsi_ग_लिखो(काष्ठा NCR5380_hostdata *, अचिन्हित पूर्णांक, u8);

#समावेश "../NCR5380.h"

#घोषणा CTRL	0x16fc
#घोषणा STAT	0x2004
#घोषणा L(v)	(((v)<<16)|((v) & 0x0000ffff))
#घोषणा H(v)	(((v)>>16)|((v) & 0xffff0000))

अटल अंतरभूत पूर्णांक cumanascsi_pग_लिखो(काष्ठा NCR5380_hostdata *hostdata,
                                    अचिन्हित अक्षर *addr, पूर्णांक len)
अणु
  अचिन्हित दीर्घ *laddr;
  u8 __iomem *base = hostdata->io;
  u8 __iomem *dma = hostdata->pdma_io + 0x2000;

  अगर(!len) वापस 0;

  ग_लिखोb(0x02, base + CTRL);
  laddr = (अचिन्हित दीर्घ *)addr;
  जबतक(len >= 32)
  अणु
    अचिन्हित पूर्णांक status;
    अचिन्हित दीर्घ v;
    status = पढ़ोb(base + STAT);
    अगर(status & 0x80)
      जाओ end;
    अगर(!(status & 0x40))
      जारी;
    v=*laddr++; ग_लिखोw(L(v), dma); ग_लिखोw(H(v), dma);
    v=*laddr++; ग_लिखोw(L(v), dma); ग_लिखोw(H(v), dma);
    v=*laddr++; ग_लिखोw(L(v), dma); ग_लिखोw(H(v), dma);
    v=*laddr++; ग_लिखोw(L(v), dma); ग_लिखोw(H(v), dma);
    v=*laddr++; ग_लिखोw(L(v), dma); ग_लिखोw(H(v), dma);
    v=*laddr++; ग_लिखोw(L(v), dma); ग_लिखोw(H(v), dma);
    v=*laddr++; ग_लिखोw(L(v), dma); ग_लिखोw(H(v), dma);
    v=*laddr++; ग_लिखोw(L(v), dma); ग_लिखोw(H(v), dma);
    len -= 32;
    अगर(len == 0)
      अवरोध;
  पूर्ण

  addr = (अचिन्हित अक्षर *)laddr;
  ग_लिखोb(0x12, base + CTRL);

  जबतक(len > 0)
  अणु
    अचिन्हित पूर्णांक status;
    status = पढ़ोb(base + STAT);
    अगर(status & 0x80)
      जाओ end;
    अगर(status & 0x40)
    अणु
      ग_लिखोb(*addr++, dma);
      अगर(--len == 0)
        अवरोध;
    पूर्ण

    status = पढ़ोb(base + STAT);
    अगर(status & 0x80)
      जाओ end;
    अगर(status & 0x40)
    अणु
      ग_लिखोb(*addr++, dma);
      अगर(--len == 0)
        अवरोध;
    पूर्ण
  पूर्ण
end:
  ग_लिखोb(hostdata->ctrl | 0x40, base + CTRL);

	अगर (len)
		वापस -1;
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक cumanascsi_pपढ़ो(काष्ठा NCR5380_hostdata *hostdata,
                                   अचिन्हित अक्षर *addr, पूर्णांक len)
अणु
  अचिन्हित दीर्घ *laddr;
  u8 __iomem *base = hostdata->io;
  u8 __iomem *dma = hostdata->pdma_io + 0x2000;

  अगर(!len) वापस 0;

  ग_लिखोb(0x00, base + CTRL);
  laddr = (अचिन्हित दीर्घ *)addr;
  जबतक(len >= 32)
  अणु
    अचिन्हित पूर्णांक status;
    status = पढ़ोb(base + STAT);
    अगर(status & 0x80)
      जाओ end;
    अगर(!(status & 0x40))
      जारी;
    *laddr++ = पढ़ोw(dma) | (पढ़ोw(dma) << 16);
    *laddr++ = पढ़ोw(dma) | (पढ़ोw(dma) << 16);
    *laddr++ = पढ़ोw(dma) | (पढ़ोw(dma) << 16);
    *laddr++ = पढ़ोw(dma) | (पढ़ोw(dma) << 16);
    *laddr++ = पढ़ोw(dma) | (पढ़ोw(dma) << 16);
    *laddr++ = पढ़ोw(dma) | (पढ़ोw(dma) << 16);
    *laddr++ = पढ़ोw(dma) | (पढ़ोw(dma) << 16);
    *laddr++ = पढ़ोw(dma) | (पढ़ोw(dma) << 16);
    len -= 32;
    अगर(len == 0)
      अवरोध;
  पूर्ण

  addr = (अचिन्हित अक्षर *)laddr;
  ग_लिखोb(0x10, base + CTRL);

  जबतक(len > 0)
  अणु
    अचिन्हित पूर्णांक status;
    status = पढ़ोb(base + STAT);
    अगर(status & 0x80)
      जाओ end;
    अगर(status & 0x40)
    अणु
      *addr++ = पढ़ोb(dma);
      अगर(--len == 0)
        अवरोध;
    पूर्ण

    status = पढ़ोb(base + STAT);
    अगर(status & 0x80)
      जाओ end;
    अगर(status & 0x40)
    अणु
      *addr++ = पढ़ोb(dma);
      अगर(--len == 0)
        अवरोध;
    पूर्ण
  पूर्ण
end:
  ग_लिखोb(hostdata->ctrl | 0x40, base + CTRL);

	अगर (len)
		वापस -1;
	वापस 0;
पूर्ण

अटल पूर्णांक cumanascsi_dma_xfer_len(काष्ठा NCR5380_hostdata *hostdata,
                                   काष्ठा scsi_cmnd *cmd)
अणु
	वापस cmd->transfersize;
पूर्ण

अटल u8 cumanascsi_पढ़ो(काष्ठा NCR5380_hostdata *hostdata,
                          अचिन्हित पूर्णांक reg)
अणु
	u8 __iomem *base = hostdata->io;
	u8 val;

	ग_लिखोb(0, base + CTRL);

	val = पढ़ोb(base + 0x2100 + (reg << 2));

	hostdata->ctrl = 0x40;
	ग_लिखोb(0x40, base + CTRL);

	वापस val;
पूर्ण

अटल व्योम cumanascsi_ग_लिखो(काष्ठा NCR5380_hostdata *hostdata,
                             अचिन्हित पूर्णांक reg, u8 value)
अणु
	u8 __iomem *base = hostdata->io;

	ग_लिखोb(0, base + CTRL);

	ग_लिखोb(value, base + 0x2100 + (reg << 2));

	hostdata->ctrl = 0x40;
	ग_लिखोb(0x40, base + CTRL);
पूर्ण

#समावेश "../NCR5380.c"

अटल काष्ठा scsi_host_ढाँचा cumanascsi_ढाँचा = अणु
	.module			= THIS_MODULE,
	.name			= "Cumana 16-bit SCSI",
	.info			= cumanascsi_info,
	.queuecommand		= cumanascsi_queue_command,
	.eh_पात_handler	= NCR5380_पात,
	.eh_host_reset_handler	= NCR5380_host_reset,
	.can_queue		= 16,
	.this_id		= 7,
	.sg_tablesize		= SG_ALL,
	.cmd_per_lun		= 2,
	.proc_name		= "CumanaSCSI-1",
	.cmd_size		= NCR5380_CMD_SIZE,
	.max_sectors		= 128,
	.dma_boundary		= PAGE_SIZE - 1,
पूर्ण;

अटल पूर्णांक cumanascsi1_probe(काष्ठा expansion_card *ec,
			     स्थिर काष्ठा ecard_id *id)
अणु
	काष्ठा Scsi_Host *host;
	पूर्णांक ret;

	ret = ecard_request_resources(ec);
	अगर (ret)
		जाओ out;

	host = scsi_host_alloc(&cumanascsi_ढाँचा, माप(काष्ठा NCR5380_hostdata));
	अगर (!host) अणु
		ret = -ENOMEM;
		जाओ out_release;
	पूर्ण

	priv(host)->io = ioremap(ecard_resource_start(ec, ECARD_RES_IOCSLOW),
	                         ecard_resource_len(ec, ECARD_RES_IOCSLOW));
	priv(host)->pdma_io = ioremap(ecard_resource_start(ec, ECARD_RES_MEMC),
	                              ecard_resource_len(ec, ECARD_RES_MEMC));
	अगर (!priv(host)->io || !priv(host)->pdma_io) अणु
		ret = -ENOMEM;
		जाओ out_unmap;
	पूर्ण

	host->irq = ec->irq;

	ret = NCR5380_init(host, FLAG_DMA_FIXUP | FLAG_LATE_DMA_SETUP);
	अगर (ret)
		जाओ out_unmap;

	NCR5380_maybe_reset_bus(host);

        priv(host)->ctrl = 0;
        ग_लिखोb(0, priv(host)->io + CTRL);

	ret = request_irq(host->irq, cumanascsi_पूर्णांकr, 0,
			  "CumanaSCSI-1", host);
	अगर (ret) अणु
		prपूर्णांकk("scsi%d: IRQ%d not free: %d\n",
		    host->host_no, host->irq, ret);
		जाओ out_निकास;
	पूर्ण

	ret = scsi_add_host(host, &ec->dev);
	अगर (ret)
		जाओ out_मुक्त_irq;

	scsi_scan_host(host);
	जाओ out;

 out_मुक्त_irq:
	मुक्त_irq(host->irq, host);
 out_निकास:
	NCR5380_निकास(host);
 out_unmap:
	iounmap(priv(host)->io);
	iounmap(priv(host)->pdma_io);
	scsi_host_put(host);
 out_release:
	ecard_release_resources(ec);
 out:
	वापस ret;
पूर्ण

अटल व्योम cumanascsi1_हटाओ(काष्ठा expansion_card *ec)
अणु
	काष्ठा Scsi_Host *host = ecard_get_drvdata(ec);
	व्योम __iomem *base = priv(host)->io;
	व्योम __iomem *dma = priv(host)->pdma_io;

	ecard_set_drvdata(ec, शून्य);

	scsi_हटाओ_host(host);
	मुक्त_irq(host->irq, host);
	NCR5380_निकास(host);
	scsi_host_put(host);
	iounmap(base);
	iounmap(dma);
	ecard_release_resources(ec);
पूर्ण

अटल स्थिर काष्ठा ecard_id cumanascsi1_cids[] = अणु
	अणु MANU_CUMANA, PROD_CUMANA_SCSI_1 पूर्ण,
	अणु 0xffff, 0xffff पूर्ण
पूर्ण;

अटल काष्ठा ecard_driver cumanascsi1_driver = अणु
	.probe		= cumanascsi1_probe,
	.हटाओ		= cumanascsi1_हटाओ,
	.id_table	= cumanascsi1_cids,
	.drv = अणु
		.name		= "cumanascsi1",
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init cumanascsi_init(व्योम)
अणु
	वापस ecard_रेजिस्टर_driver(&cumanascsi1_driver);
पूर्ण

अटल व्योम __निकास cumanascsi_निकास(व्योम)
अणु
	ecard_हटाओ_driver(&cumanascsi1_driver);
पूर्ण

module_init(cumanascsi_init);
module_निकास(cumanascsi_निकास);

MODULE_DESCRIPTION("Cumana SCSI-1 driver for Acorn machines");
MODULE_LICENSE("GPL");
