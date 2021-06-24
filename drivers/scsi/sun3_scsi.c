<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Sun3 SCSI stuff by Erik Verbruggen (erik@bigmama.xtdnet.nl)
 *
 * Sun3 DMA routines added by Sam Creasey (sammy@sammy.net)
 *
 * VME support added by Sam Creasey
 *
 * TODO: modअगरy this driver to support multiple Sun3 SCSI VME boards
 *
 * Adapted from mac_scsinew.c:
 */
/*
 * Generic Macपूर्णांकosh NCR5380 driver
 *
 * Copyright 1998, Michael Schmitz <mschmitz@lbl.gov>
 *
 * derived in part from:
 */
/*
 * Generic Generic NCR5380 driver
 *
 * Copyright 1995, Russell King
 */

#समावेश <linux/types.h>
#समावेश <linux/delay.h>
#समावेश <linux/module.h>
#समावेश <linux/ioport.h>
#समावेश <linux/init.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/dvma.h>

#समावेश <scsi/scsi_host.h>

/* minimum number of bytes to करो dma on */
#घोषणा DMA_MIN_SIZE                    129

/* Definitions क्रम the core NCR5380 driver. */

#घोषणा NCR5380_implementation_fields   /* none */

#घोषणा NCR5380_पढ़ो(reg)               in_8(hostdata->io + (reg))
#घोषणा NCR5380_ग_लिखो(reg, value)       out_8(hostdata->io + (reg), value)

#घोषणा NCR5380_queue_command           sun3scsi_queue_command
#घोषणा NCR5380_host_reset              sun3scsi_host_reset
#घोषणा NCR5380_पात                   sun3scsi_पात
#घोषणा NCR5380_info                    sun3scsi_info

#घोषणा NCR5380_dma_xfer_len            sun3scsi_dma_xfer_len
#घोषणा NCR5380_dma_recv_setup          sun3scsi_dma_count
#घोषणा NCR5380_dma_send_setup          sun3scsi_dma_count
#घोषणा NCR5380_dma_residual            sun3scsi_dma_residual

#समावेश "NCR5380.h"

/* dma regs start at regbase + 8, directly after the NCR regs */
काष्ठा sun3_dma_regs अणु
	अचिन्हित लघु dma_addr_hi; /* vme only */
	अचिन्हित लघु dma_addr_lo; /* vme only */
	अचिन्हित लघु dma_count_hi; /* vme only */
	अचिन्हित लघु dma_count_lo; /* vme only */
	अचिन्हित लघु udc_data; /* udc dma data reg (obio only) */
	अचिन्हित लघु udc_addr; /* uda dma addr reg (obio only) */
	अचिन्हित लघु fअगरo_data; /* fअगरo data reg,
	                           * holds extra byte on odd dma पढ़ोs
	                           */
	अचिन्हित लघु fअगरo_count;
	अचिन्हित लघु csr; /* control/status reg */
	अचिन्हित लघु bpack_hi; /* vme only */
	अचिन्हित लघु bpack_lo; /* vme only */
	अचिन्हित लघु ivect; /* vme only */
	अचिन्हित लघु fअगरo_count_hi; /* vme only */
पूर्ण;

/* ucd chip specअगरic regs - live in dvma space */
काष्ठा sun3_udc_regs अणु
	अचिन्हित लघु rsel; /* select regs to load */
	अचिन्हित लघु addr_hi; /* high word of addr */
	अचिन्हित लघु addr_lo; /* low word */
	अचिन्हित लघु count; /* words to be xfer'd */
	अचिन्हित लघु mode_hi; /* high word of channel mode */
	अचिन्हित लघु mode_lo; /* low word of channel mode */
पूर्ण;

/* addresses of the udc रेजिस्टरs */
#घोषणा UDC_MODE 0x38
#घोषणा UDC_CSR 0x2e /* command/status */
#घोषणा UDC_CHN_HI 0x26 /* chain high word */
#घोषणा UDC_CHN_LO 0x22 /* chain lo word */
#घोषणा UDC_CURA_HI 0x1a /* cur reg A high */
#घोषणा UDC_CURA_LO 0x0a /* cur reg A low */
#घोषणा UDC_CURB_HI 0x12 /* cur reg B high */
#घोषणा UDC_CURB_LO 0x02 /* cur reg B low */
#घोषणा UDC_MODE_HI 0x56 /* mode reg high */
#घोषणा UDC_MODE_LO 0x52 /* mode reg low */
#घोषणा UDC_COUNT 0x32 /* words to xfer */

/* some udc commands */
#घोषणा UDC_RESET 0
#घोषणा UDC_CHN_START 0xa0 /* start chain */
#घोषणा UDC_INT_ENABLE 0x32 /* channel 1 पूर्णांक on */

/* udc mode words */
#घोषणा UDC_MODE_HIWORD 0x40
#घोषणा UDC_MODE_LSEND 0xc2
#घोषणा UDC_MODE_LRECV 0xd2

/* udc reg selections */
#घोषणा UDC_RSEL_SEND 0x282
#घोषणा UDC_RSEL_RECV 0x182

/* bits in csr reg */
#घोषणा CSR_DMA_ACTIVE 0x8000
#घोषणा CSR_DMA_CONFLICT 0x4000
#घोषणा CSR_DMA_BUSERR 0x2000

#घोषणा CSR_FIFO_EMPTY 0x400 /* fअगरo flushed? */
#घोषणा CSR_SDB_INT 0x200 /* sbc पूर्णांकerrupt pending */
#घोषणा CSR_DMA_INT 0x100 /* dma पूर्णांकerrupt pending */

#घोषणा CSR_LEFT 0xc0
#घोषणा CSR_LEFT_3 0xc0
#घोषणा CSR_LEFT_2 0x80
#घोषणा CSR_LEFT_1 0x40
#घोषणा CSR_PACK_ENABLE 0x20

#घोषणा CSR_DMA_ENABLE 0x10

#घोषणा CSR_SEND 0x8 /* 1 = send  0 = recv */
#घोषणा CSR_FIFO 0x2 /* reset fअगरo */
#घोषणा CSR_INTR 0x4 /* पूर्णांकerrupt enable */
#घोषणा CSR_SCSI 0x1

#घोषणा VME_DATA24 0x3d00

बाह्य पूर्णांक sun3_map_test(अचिन्हित दीर्घ, अक्षर *);

अटल पूर्णांक setup_can_queue = -1;
module_param(setup_can_queue, पूर्णांक, 0);
अटल पूर्णांक setup_cmd_per_lun = -1;
module_param(setup_cmd_per_lun, पूर्णांक, 0);
अटल पूर्णांक setup_sg_tablesize = -1;
module_param(setup_sg_tablesize, पूर्णांक, 0);
अटल पूर्णांक setup_hostid = -1;
module_param(setup_hostid, पूर्णांक, 0);

/* ms to रुको after hitting dma regs */
#घोषणा SUN3_DMA_DELAY 10

/* dvma buffer to allocate -- 32k should hopefully be more than sufficient */
#घोषणा SUN3_DVMA_बफ_मानE 0xe000

अटल काष्ठा scsi_cmnd *sun3_dma_setup_करोne;
अटल अस्थिर काष्ठा sun3_dma_regs *dregs;
अटल काष्ठा sun3_udc_regs *udc_regs;
अटल अचिन्हित अक्षर *sun3_dma_orig_addr;
अटल अचिन्हित दीर्घ sun3_dma_orig_count;
अटल पूर्णांक sun3_dma_active;
अटल अचिन्हित दीर्घ last_residual;

#अगर_अघोषित SUN3_SCSI_VME
/* dma controller रेजिस्टर access functions */

अटल अंतरभूत अचिन्हित लघु sun3_udc_पढ़ो(अचिन्हित अक्षर reg)
अणु
	अचिन्हित लघु ret;

	dregs->udc_addr = UDC_CSR;
	udelay(SUN3_DMA_DELAY);
	ret = dregs->udc_data;
	udelay(SUN3_DMA_DELAY);
	
	वापस ret;
पूर्ण

अटल अंतरभूत व्योम sun3_udc_ग_लिखो(अचिन्हित लघु val, अचिन्हित अक्षर reg)
अणु
	dregs->udc_addr = reg;
	udelay(SUN3_DMA_DELAY);
	dregs->udc_data = val;
	udelay(SUN3_DMA_DELAY);
पूर्ण
#पूर्ण_अगर

// safe bits क्रम the CSR
#घोषणा CSR_GOOD 0x060f

अटल irqवापस_t scsi_sun3_पूर्णांकr(पूर्णांक irq, व्योम *dev)
अणु
	काष्ठा Scsi_Host *instance = dev;
	अचिन्हित लघु csr = dregs->csr;
	पूर्णांक handled = 0;

#अगर_घोषित SUN3_SCSI_VME
	dregs->csr &= ~CSR_DMA_ENABLE;
#पूर्ण_अगर

	अगर(csr & ~CSR_GOOD) अणु
		अगर (csr & CSR_DMA_BUSERR)
			shost_prपूर्णांकk(KERN_ERR, instance, "bus error in DMA\n");
		अगर (csr & CSR_DMA_CONFLICT)
			shost_prपूर्णांकk(KERN_ERR, instance, "DMA conflict\n");
		handled = 1;
	पूर्ण

	अगर(csr & (CSR_SDB_INT | CSR_DMA_INT)) अणु
		NCR5380_पूर्णांकr(irq, dev);
		handled = 1;
	पूर्ण

	वापस IRQ_RETVAL(handled);
पूर्ण

/* sun3scsi_dma_setup() -- initialize the dma controller क्रम a पढ़ो/ग_लिखो */
अटल पूर्णांक sun3scsi_dma_setup(काष्ठा NCR5380_hostdata *hostdata,
                              अचिन्हित अक्षर *data, पूर्णांक count, पूर्णांक ग_लिखो_flag)
अणु
	व्योम *addr;

	अगर(sun3_dma_orig_addr != शून्य)
		dvma_unmap(sun3_dma_orig_addr);

#अगर_घोषित SUN3_SCSI_VME
	addr = (व्योम *)dvma_map_vme((अचिन्हित दीर्घ) data, count);
#अन्यथा
	addr = (व्योम *)dvma_map((अचिन्हित दीर्घ) data, count);
#पूर्ण_अगर
		
	sun3_dma_orig_addr = addr;
	sun3_dma_orig_count = count;

#अगर_अघोषित SUN3_SCSI_VME
	dregs->fअगरo_count = 0;
	sun3_udc_ग_लिखो(UDC_RESET, UDC_CSR);
	
	/* reset fअगरo */
	dregs->csr &= ~CSR_FIFO;
	dregs->csr |= CSR_FIFO;
#पूर्ण_अगर
	
	/* set direction */
	अगर(ग_लिखो_flag)
		dregs->csr |= CSR_SEND;
	अन्यथा
		dregs->csr &= ~CSR_SEND;
	
#अगर_घोषित SUN3_SCSI_VME
	dregs->csr |= CSR_PACK_ENABLE;

	dregs->dma_addr_hi = ((अचिन्हित दीर्घ)addr >> 16);
	dregs->dma_addr_lo = ((अचिन्हित दीर्घ)addr & 0xffff);

	dregs->dma_count_hi = 0;
	dregs->dma_count_lo = 0;
	dregs->fअगरo_count_hi = 0;
	dregs->fअगरo_count = 0;
#अन्यथा
	/* byte count क्रम fअगरo */
	dregs->fअगरo_count = count;

	sun3_udc_ग_लिखो(UDC_RESET, UDC_CSR);
	
	/* reset fअगरo */
	dregs->csr &= ~CSR_FIFO;
	dregs->csr |= CSR_FIFO;
	
	अगर(dregs->fअगरo_count != count) अणु 
		shost_prपूर्णांकk(KERN_ERR, hostdata->host,
		             "FIFO mismatch %04x not %04x\n",
		             dregs->fअगरo_count, (अचिन्हित पूर्णांक) count);
		NCR5380_dprपूर्णांक(न_संशोधन_DMA, hostdata->host);
	पूर्ण

	/* setup udc */
	udc_regs->addr_hi = (((अचिन्हित दीर्घ)(addr) & 0xff0000) >> 8);
	udc_regs->addr_lo = ((अचिन्हित दीर्घ)(addr) & 0xffff);
	udc_regs->count = count/2; /* count in words */
	udc_regs->mode_hi = UDC_MODE_HIWORD;
	अगर(ग_लिखो_flag) अणु
		अगर(count & 1)
			udc_regs->count++;
		udc_regs->mode_lo = UDC_MODE_LSEND;
		udc_regs->rsel = UDC_RSEL_SEND;
	पूर्ण अन्यथा अणु
		udc_regs->mode_lo = UDC_MODE_LRECV;
		udc_regs->rsel = UDC_RSEL_RECV;
	पूर्ण
	
	/* announce location of regs block */
	sun3_udc_ग_लिखो(((dvma_vtob(udc_regs) & 0xff0000) >> 8),
		       UDC_CHN_HI); 

	sun3_udc_ग_लिखो((dvma_vtob(udc_regs) & 0xffff), UDC_CHN_LO);

	/* set dma master on */
	sun3_udc_ग_लिखो(0xd, UDC_MODE);

	/* पूर्णांकerrupt enable */
	sun3_udc_ग_लिखो(UDC_INT_ENABLE, UDC_CSR);
#पूर्ण_अगर
	
       	वापस count;

पूर्ण

अटल पूर्णांक sun3scsi_dma_count(काष्ठा NCR5380_hostdata *hostdata,
                              अचिन्हित अक्षर *data, पूर्णांक count)
अणु
	वापस count;
पूर्ण

अटल अंतरभूत पूर्णांक sun3scsi_dma_recv_setup(काष्ठा NCR5380_hostdata *hostdata,
                                          अचिन्हित अक्षर *data, पूर्णांक count)
अणु
	वापस sun3scsi_dma_setup(hostdata, data, count, 0);
पूर्ण

अटल अंतरभूत पूर्णांक sun3scsi_dma_send_setup(काष्ठा NCR5380_hostdata *hostdata,
                                          अचिन्हित अक्षर *data, पूर्णांक count)
अणु
	वापस sun3scsi_dma_setup(hostdata, data, count, 1);
पूर्ण

अटल पूर्णांक sun3scsi_dma_residual(काष्ठा NCR5380_hostdata *hostdata)
अणु
	वापस last_residual;
पूर्ण

अटल पूर्णांक sun3scsi_dma_xfer_len(काष्ठा NCR5380_hostdata *hostdata,
                                 काष्ठा scsi_cmnd *cmd)
अणु
	पूर्णांक wanted_len = cmd->SCp.this_residual;

	अगर (wanted_len < DMA_MIN_SIZE || blk_rq_is_passthrough(cmd->request))
		वापस 0;

	वापस wanted_len;
पूर्ण

अटल अंतरभूत पूर्णांक sun3scsi_dma_start(अचिन्हित दीर्घ count, अचिन्हित अक्षर *data)
अणु
#अगर_घोषित SUN3_SCSI_VME
	अचिन्हित लघु csr;

	csr = dregs->csr;

	dregs->dma_count_hi = (sun3_dma_orig_count >> 16);
	dregs->dma_count_lo = (sun3_dma_orig_count & 0xffff);

	dregs->fअगरo_count_hi = (sun3_dma_orig_count >> 16);
	dregs->fअगरo_count = (sun3_dma_orig_count & 0xffff);

/*	अगर(!(csr & CSR_DMA_ENABLE))
 *		dregs->csr |= CSR_DMA_ENABLE;
 */
#अन्यथा
    sun3_udc_ग_लिखो(UDC_CHN_START, UDC_CSR);
#पूर्ण_अगर
    
    वापस 0;
पूर्ण

/* clean up after our dma is करोne */
अटल पूर्णांक sun3scsi_dma_finish(पूर्णांक ग_लिखो_flag)
अणु
	अचिन्हित लघु __maybe_unused count;
	अचिन्हित लघु fअगरo;
	पूर्णांक ret = 0;
	
	sun3_dma_active = 0;

#अगर_घोषित SUN3_SCSI_VME
	dregs->csr &= ~CSR_DMA_ENABLE;

	fअगरo = dregs->fअगरo_count;
	अगर (ग_लिखो_flag) अणु
		अगर ((fअगरo > 0) && (fअगरo < sun3_dma_orig_count))
			fअगरo++;
	पूर्ण

	last_residual = fअगरo;
	/* empty bytes from the fअगरo which didn't make it */
	अगर ((!ग_लिखो_flag) && (dregs->csr & CSR_LEFT)) अणु
		अचिन्हित अक्षर *vaddr;

		vaddr = (अचिन्हित अक्षर *)dvma_vmetov(sun3_dma_orig_addr);

		vaddr += (sun3_dma_orig_count - fअगरo);
		vaddr--;

		चयन (dregs->csr & CSR_LEFT) अणु
		हाल CSR_LEFT_3:
			*vaddr = (dregs->bpack_lo & 0xff00) >> 8;
			vaddr--;
			fallthrough;

		हाल CSR_LEFT_2:
			*vaddr = (dregs->bpack_hi & 0x00ff);
			vaddr--;
			fallthrough;

		हाल CSR_LEFT_1:
			*vaddr = (dregs->bpack_hi & 0xff00) >> 8;
			अवरोध;
		पूर्ण
	पूर्ण
#अन्यथा
	// check to empty the fअगरo on a पढ़ो
	अगर(!ग_लिखो_flag) अणु
		पूर्णांक पंचांगo = 20000; /* .2 sec */
		
		जबतक(1) अणु
			अगर(dregs->csr & CSR_FIFO_EMPTY)
				अवरोध;

			अगर(--पंचांगo <= 0) अणु
				prपूर्णांकk("sun3scsi: fifo failed to empty!\n");
				वापस 1;
			पूर्ण
			udelay(10);
		पूर्ण
	पूर्ण

	dregs->udc_addr = 0x32;
	udelay(SUN3_DMA_DELAY);
	count = 2 * dregs->udc_data;
	udelay(SUN3_DMA_DELAY);

	fअगरo = dregs->fअगरo_count;
	last_residual = fअगरo;

	/* empty bytes from the fअगरo which didn't make it */
	अगर((!ग_लिखो_flag) && (count - fअगरo) == 2) अणु
		अचिन्हित लघु data;
		अचिन्हित अक्षर *vaddr;

		data = dregs->fअगरo_data;
		vaddr = (अचिन्हित अक्षर *)dvma_btov(sun3_dma_orig_addr);
		
		vaddr += (sun3_dma_orig_count - fअगरo);

		vaddr[-2] = (data & 0xff00) >> 8;
		vaddr[-1] = (data & 0xff);
	पूर्ण
#पूर्ण_अगर

	dvma_unmap(sun3_dma_orig_addr);
	sun3_dma_orig_addr = शून्य;

#अगर_घोषित SUN3_SCSI_VME
	dregs->dma_addr_hi = 0;
	dregs->dma_addr_lo = 0;
	dregs->dma_count_hi = 0;
	dregs->dma_count_lo = 0;

	dregs->fअगरo_count = 0;
	dregs->fअगरo_count_hi = 0;

	dregs->csr &= ~CSR_SEND;
/*	dregs->csr |= CSR_DMA_ENABLE; */
#अन्यथा
	sun3_udc_ग_लिखो(UDC_RESET, UDC_CSR);
	dregs->fअगरo_count = 0;
	dregs->csr &= ~CSR_SEND;

	/* reset fअगरo */
	dregs->csr &= ~CSR_FIFO;
	dregs->csr |= CSR_FIFO;
#पूर्ण_अगर
	
	sun3_dma_setup_करोne = शून्य;

	वापस ret;

पूर्ण
	
#समावेश "NCR5380.c"

#अगर_घोषित SUN3_SCSI_VME
#घोषणा SUN3_SCSI_NAME          "Sun3 NCR5380 VME SCSI"
#घोषणा DRV_MODULE_NAME         "sun3_scsi_vme"
#अन्यथा
#घोषणा SUN3_SCSI_NAME          "Sun3 NCR5380 SCSI"
#घोषणा DRV_MODULE_NAME         "sun3_scsi"
#पूर्ण_अगर

#घोषणा PFX                     DRV_MODULE_NAME ": "

अटल काष्ठा scsi_host_ढाँचा sun3_scsi_ढाँचा = अणु
	.module			= THIS_MODULE,
	.proc_name		= DRV_MODULE_NAME,
	.name			= SUN3_SCSI_NAME,
	.info			= sun3scsi_info,
	.queuecommand		= sun3scsi_queue_command,
	.eh_पात_handler	= sun3scsi_पात,
	.eh_host_reset_handler	= sun3scsi_host_reset,
	.can_queue		= 16,
	.this_id		= 7,
	.sg_tablesize		= 1,
	.cmd_per_lun		= 2,
	.dma_boundary		= PAGE_SIZE - 1,
	.cmd_size		= NCR5380_CMD_SIZE,
पूर्ण;

अटल पूर्णांक __init sun3_scsi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा Scsi_Host *instance;
	काष्ठा NCR5380_hostdata *hostdata;
	पूर्णांक error;
	काष्ठा resource *irq, *mem;
	व्योम __iomem *ioaddr;
	पूर्णांक host_flags = 0;
#अगर_घोषित SUN3_SCSI_VME
	पूर्णांक i;
#पूर्ण_अगर

	अगर (setup_can_queue > 0)
		sun3_scsi_ढाँचा.can_queue = setup_can_queue;
	अगर (setup_cmd_per_lun > 0)
		sun3_scsi_ढाँचा.cmd_per_lun = setup_cmd_per_lun;
	अगर (setup_sg_tablesize > 0)
		sun3_scsi_ढाँचा.sg_tablesize = setup_sg_tablesize;
	अगर (setup_hostid >= 0)
		sun3_scsi_ढाँचा.this_id = setup_hostid & 7;

#अगर_घोषित SUN3_SCSI_VME
	ioaddr = शून्य;
	क्रम (i = 0; i < 2; i++) अणु
		अचिन्हित अक्षर x;

		irq = platक्रमm_get_resource(pdev, IORESOURCE_IRQ, i);
		mem = platक्रमm_get_resource(pdev, IORESOURCE_MEM, i);
		अगर (!irq || !mem)
			अवरोध;

		ioaddr = sun3_ioremap(mem->start, resource_size(mem),
		                      SUN3_PAGE_TYPE_VME16);
		dregs = (काष्ठा sun3_dma_regs *)(ioaddr + 8);

		अगर (sun3_map_test((अचिन्हित दीर्घ)dregs, &x)) अणु
			अचिन्हित लघु oldcsr;

			oldcsr = dregs->csr;
			dregs->csr = 0;
			udelay(SUN3_DMA_DELAY);
			अगर (dregs->csr == 0x1400)
				अवरोध;

			dregs->csr = oldcsr;
		पूर्ण

		iounmap(ioaddr);
		ioaddr = शून्य;
	पूर्ण
	अगर (!ioaddr)
		वापस -ENODEV;
#अन्यथा
	irq = platक्रमm_get_resource(pdev, IORESOURCE_IRQ, 0);
	mem = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!irq || !mem)
		वापस -ENODEV;

	ioaddr = ioremap(mem->start, resource_size(mem));
	dregs = (काष्ठा sun3_dma_regs *)(ioaddr + 8);

	udc_regs = dvma_दो_स्मृति(माप(काष्ठा sun3_udc_regs));
	अगर (!udc_regs) अणु
		pr_err(PFX "couldn't allocate DVMA memory!\n");
		iounmap(ioaddr);
		वापस -ENOMEM;
	पूर्ण
#पूर्ण_अगर

	instance = scsi_host_alloc(&sun3_scsi_ढाँचा,
	                           माप(काष्ठा NCR5380_hostdata));
	अगर (!instance) अणु
		error = -ENOMEM;
		जाओ fail_alloc;
	पूर्ण

	instance->irq = irq->start;

	hostdata = shost_priv(instance);
	hostdata->base = mem->start;
	hostdata->io = ioaddr;

	error = NCR5380_init(instance, host_flags);
	अगर (error)
		जाओ fail_init;

	error = request_irq(instance->irq, scsi_sun3_पूर्णांकr, 0,
	                    "NCR5380", instance);
	अगर (error) अणु
		pr_err(PFX "scsi%d: IRQ %d not free, bailing out\n",
		       instance->host_no, instance->irq);
		जाओ fail_irq;
	पूर्ण

	dregs->csr = 0;
	udelay(SUN3_DMA_DELAY);
	dregs->csr = CSR_SCSI | CSR_FIFO | CSR_INTR;
	udelay(SUN3_DMA_DELAY);
	dregs->fअगरo_count = 0;
#अगर_घोषित SUN3_SCSI_VME
	dregs->fअगरo_count_hi = 0;
	dregs->dma_addr_hi = 0;
	dregs->dma_addr_lo = 0;
	dregs->dma_count_hi = 0;
	dregs->dma_count_lo = 0;

	dregs->ivect = VME_DATA24 | (instance->irq & 0xff);
#पूर्ण_अगर

	NCR5380_maybe_reset_bus(instance);

	error = scsi_add_host(instance, शून्य);
	अगर (error)
		जाओ fail_host;

	platक्रमm_set_drvdata(pdev, instance);

	scsi_scan_host(instance);
	वापस 0;

fail_host:
	मुक्त_irq(instance->irq, instance);
fail_irq:
	NCR5380_निकास(instance);
fail_init:
	scsi_host_put(instance);
fail_alloc:
	अगर (udc_regs)
		dvma_मुक्त(udc_regs);
	iounmap(ioaddr);
	वापस error;
पूर्ण

अटल पूर्णांक __निकास sun3_scsi_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा Scsi_Host *instance = platक्रमm_get_drvdata(pdev);
	काष्ठा NCR5380_hostdata *hostdata = shost_priv(instance);
	व्योम __iomem *ioaddr = hostdata->io;

	scsi_हटाओ_host(instance);
	मुक्त_irq(instance->irq, instance);
	NCR5380_निकास(instance);
	scsi_host_put(instance);
	अगर (udc_regs)
		dvma_मुक्त(udc_regs);
	iounmap(ioaddr);
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver sun3_scsi_driver = अणु
	.हटाओ = __निकास_p(sun3_scsi_हटाओ),
	.driver = अणु
		.name	= DRV_MODULE_NAME,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver_probe(sun3_scsi_driver, sun3_scsi_probe);

MODULE_ALIAS("platform:" DRV_MODULE_NAME);
MODULE_LICENSE("GPL");
