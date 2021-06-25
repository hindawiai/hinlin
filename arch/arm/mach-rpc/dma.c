<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/arch/arm/mach-rpc/dma.c
 *
 *  Copyright (C) 1998 Russell King
 *
 *  DMA functions specअगरic to RiscPC architecture
 */
#समावेश <linux/mman.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/पन.स>

#समावेश <यंत्र/page.h>
#समावेश <यंत्र/dma.h>
#समावेश <यंत्र/fiq.h>
#समावेश <यंत्र/irq.h>
#समावेश <mach/hardware.h>
#समावेश <linux/uaccess.h>

#समावेश <यंत्र/mach/dma.h>
#समावेश <यंत्र/hardware/iomd.h>

काष्ठा iomd_dma अणु
	काष्ठा dma_काष्ठा	dma;
	व्योम __iomem		*base;		/* Controller base address */
	पूर्णांक			irq;		/* Controller IRQ */
	अचिन्हित पूर्णांक		state;
	dma_addr_t		cur_addr;
	अचिन्हित पूर्णांक		cur_len;
	dma_addr_t		dma_addr;
	अचिन्हित पूर्णांक		dma_len;
पूर्ण;

#अगर 0
प्रकार क्रमागत अणु
	dma_size_8	= 1,
	dma_size_16	= 2,
	dma_size_32	= 4,
	dma_size_128	= 16
पूर्ण dma_माप_प्रकार;
#पूर्ण_अगर

#घोषणा TRANSFER_SIZE	2

#घोषणा CURA	(0)
#घोषणा ENDA	(IOMD_IO0ENDA - IOMD_IO0CURA)
#घोषणा CURB	(IOMD_IO0CURB - IOMD_IO0CURA)
#घोषणा ENDB	(IOMD_IO0ENDB - IOMD_IO0CURA)
#घोषणा CR	(IOMD_IO0CR - IOMD_IO0CURA)
#घोषणा ST	(IOMD_IO0ST - IOMD_IO0CURA)

अटल व्योम iomd_get_next_sg(काष्ठा iomd_dma *idma)
अणु
	अचिन्हित दीर्घ end, offset, flags = 0;

	अगर (idma->dma.sg) अणु
		idma->cur_addr = idma->dma_addr;
		offset = idma->cur_addr & ~PAGE_MASK;

		end = offset + idma->dma_len;

		अगर (end > PAGE_SIZE)
			end = PAGE_SIZE;

		अगर (offset + TRANSFER_SIZE >= end)
			flags |= DMA_END_L;

		idma->cur_len = end - TRANSFER_SIZE;

		idma->dma_len -= end - offset;
		idma->dma_addr += end - offset;

		अगर (idma->dma_len == 0) अणु
			अगर (idma->dma.sgcount > 1) अणु
				idma->dma.sg = sg_next(idma->dma.sg);
				idma->dma_addr = idma->dma.sg->dma_address;
				idma->dma_len = idma->dma.sg->length;
				idma->dma.sgcount--;
			पूर्ण अन्यथा अणु
				idma->dma.sg = शून्य;
				flags |= DMA_END_S;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		flags = DMA_END_S | DMA_END_L;
		idma->cur_addr = 0;
		idma->cur_len = 0;
	पूर्ण

	idma->cur_len |= flags;
पूर्ण

अटल irqवापस_t iomd_dma_handle(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा iomd_dma *idma = dev_id;
	व्योम __iomem *base = idma->base;
	अचिन्हित पूर्णांक state = idma->state;
	अचिन्हित पूर्णांक status, cur, end;

	करो अणु
		status = पढ़ोb(base + ST);
		अगर (!(status & DMA_ST_INT))
			जाओ out;

		अगर ((state ^ status) & DMA_ST_AB)
			iomd_get_next_sg(idma);

		// This efficiently implements state = OFL != AB ? AB : 0
		state = ((status >> 2) ^ status) & DMA_ST_AB;
		अगर (state) अणु
			cur = CURA;
			end = ENDA;
		पूर्ण अन्यथा अणु
			cur = CURB;
			end = ENDB;
		पूर्ण
		ग_लिखोl(idma->cur_addr, base + cur);
		ग_लिखोl(idma->cur_len, base + end);

		अगर (status & DMA_ST_OFL &&
		    idma->cur_len == (DMA_END_S|DMA_END_L))
			अवरोध;
	पूर्ण जबतक (1);

	state = ~DMA_ST_AB;
	disable_irq_nosync(irq);
out:
	idma->state = state;
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक iomd_request_dma(अचिन्हित पूर्णांक chan, dma_t *dma)
अणु
	काष्ठा iomd_dma *idma = container_of(dma, काष्ठा iomd_dma, dma);

	वापस request_irq(idma->irq, iomd_dma_handle,
			   0, idma->dma.device_id, idma);
पूर्ण

अटल व्योम iomd_मुक्त_dma(अचिन्हित पूर्णांक chan, dma_t *dma)
अणु
	काष्ठा iomd_dma *idma = container_of(dma, काष्ठा iomd_dma, dma);

	मुक्त_irq(idma->irq, idma);
पूर्ण

अटल काष्ठा device isa_dma_dev = अणु
	.init_name		= "fallback device",
	.coherent_dma_mask	= ~(dma_addr_t)0,
	.dma_mask		= &isa_dma_dev.coherent_dma_mask,
पूर्ण;

अटल व्योम iomd_enable_dma(अचिन्हित पूर्णांक chan, dma_t *dma)
अणु
	काष्ठा iomd_dma *idma = container_of(dma, काष्ठा iomd_dma, dma);
	व्योम __iomem *base = idma->base;
	अचिन्हित पूर्णांक ctrl = TRANSFER_SIZE | DMA_CR_E;

	अगर (idma->dma.invalid) अणु
		idma->dma.invalid = 0;

		/*
		 * Cope with ISA-style drivers which expect cache
		 * coherence.
		 */
		अगर (!idma->dma.sg) अणु
			idma->dma.sg = &idma->dma.buf;
			idma->dma.sgcount = 1;
			idma->dma.buf.length = idma->dma.count;
			idma->dma.buf.dma_address = dma_map_single(&isa_dma_dev,
				idma->dma.addr, idma->dma.count,
				idma->dma.dma_mode == DMA_MODE_READ ?
				DMA_FROM_DEVICE : DMA_TO_DEVICE);
		पूर्ण

		idma->dma_addr = idma->dma.sg->dma_address;
		idma->dma_len = idma->dma.sg->length;

		ग_लिखोb(DMA_CR_C, base + CR);
		idma->state = DMA_ST_AB;
	पूर्ण

	अगर (idma->dma.dma_mode == DMA_MODE_READ)
		ctrl |= DMA_CR_D;

	ग_लिखोb(ctrl, base + CR);
	enable_irq(idma->irq);
पूर्ण

अटल व्योम iomd_disable_dma(अचिन्हित पूर्णांक chan, dma_t *dma)
अणु
	काष्ठा iomd_dma *idma = container_of(dma, काष्ठा iomd_dma, dma);
	व्योम __iomem *base = idma->base;
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	अगर (idma->state != ~DMA_ST_AB)
		disable_irq(idma->irq);
	ग_लिखोb(0, base + CR);
	local_irq_restore(flags);
पूर्ण

अटल पूर्णांक iomd_set_dma_speed(अचिन्हित पूर्णांक chan, dma_t *dma, पूर्णांक cycle)
अणु
	पूर्णांक tcr, speed;

	अगर (cycle < 188)
		speed = 3;
	अन्यथा अगर (cycle <= 250)
		speed = 2;
	अन्यथा अगर (cycle < 438)
		speed = 1;
	अन्यथा
		speed = 0;

	tcr = iomd_पढ़ोb(IOMD_DMATCR);
	speed &= 3;

	चयन (chan) अणु
	हाल DMA_0:
		tcr = (tcr & ~0x03) | speed;
		अवरोध;

	हाल DMA_1:
		tcr = (tcr & ~0x0c) | (speed << 2);
		अवरोध;

	हाल DMA_2:
		tcr = (tcr & ~0x30) | (speed << 4);
		अवरोध;

	हाल DMA_3:
		tcr = (tcr & ~0xc0) | (speed << 6);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	iomd_ग_लिखोb(tcr, IOMD_DMATCR);

	वापस speed;
पूर्ण

अटल काष्ठा dma_ops iomd_dma_ops = अणु
	.type		= "IOMD",
	.request	= iomd_request_dma,
	.मुक्त		= iomd_मुक्त_dma,
	.enable		= iomd_enable_dma,
	.disable	= iomd_disable_dma,
	.setspeed	= iomd_set_dma_speed,
पूर्ण;

अटल काष्ठा fiq_handler fh = अणु
	.name	= "floppydma"
पूर्ण;

काष्ठा floppy_dma अणु
	काष्ठा dma_काष्ठा	dma;
	अचिन्हित पूर्णांक		fiq;
पूर्ण;

अटल व्योम floppy_enable_dma(अचिन्हित पूर्णांक chan, dma_t *dma)
अणु
	काष्ठा floppy_dma *fdma = container_of(dma, काष्ठा floppy_dma, dma);
	व्योम *fiqhandler_start;
	अचिन्हित पूर्णांक fiqhandler_length;
	काष्ठा pt_regs regs;

	अगर (fdma->dma.sg)
		BUG();

	अगर (fdma->dma.dma_mode == DMA_MODE_READ) अणु
		बाह्य अचिन्हित अक्षर floppy_fiqin_start, floppy_fiqin_end;
		fiqhandler_start = &floppy_fiqin_start;
		fiqhandler_length = &floppy_fiqin_end - &floppy_fiqin_start;
	पूर्ण अन्यथा अणु
		बाह्य अचिन्हित अक्षर floppy_fiqout_start, floppy_fiqout_end;
		fiqhandler_start = &floppy_fiqout_start;
		fiqhandler_length = &floppy_fiqout_end - &floppy_fiqout_start;
	पूर्ण

	regs.ARM_r9  = fdma->dma.count;
	regs.ARM_r10 = (अचिन्हित दीर्घ)fdma->dma.addr;
	regs.ARM_fp  = (अचिन्हित दीर्घ)FLOPPYDMA_BASE;

	अगर (claim_fiq(&fh)) अणु
		prपूर्णांकk("floppydma: couldn't claim FIQ.\n");
		वापस;
	पूर्ण

	set_fiq_handler(fiqhandler_start, fiqhandler_length);
	set_fiq_regs(&regs);
	enable_fiq(fdma->fiq);
पूर्ण

अटल व्योम floppy_disable_dma(अचिन्हित पूर्णांक chan, dma_t *dma)
अणु
	काष्ठा floppy_dma *fdma = container_of(dma, काष्ठा floppy_dma, dma);
	disable_fiq(fdma->fiq);
	release_fiq(&fh);
पूर्ण

अटल पूर्णांक floppy_get_residue(अचिन्हित पूर्णांक chan, dma_t *dma)
अणु
	काष्ठा pt_regs regs;
	get_fiq_regs(&regs);
	वापस regs.ARM_r9;
पूर्ण

अटल काष्ठा dma_ops floppy_dma_ops = अणु
	.type		= "FIQDMA",
	.enable		= floppy_enable_dma,
	.disable	= floppy_disable_dma,
	.residue	= floppy_get_residue,
पूर्ण;

/*
 * This is भव DMA - we करोn't need anything here.
 */
अटल व्योम sound_enable_disable_dma(अचिन्हित पूर्णांक chan, dma_t *dma)
अणु
पूर्ण

अटल काष्ठा dma_ops sound_dma_ops = अणु
	.type		= "VIRTUAL",
	.enable		= sound_enable_disable_dma,
	.disable	= sound_enable_disable_dma,
पूर्ण;

अटल काष्ठा iomd_dma iomd_dma[6];

अटल काष्ठा floppy_dma floppy_dma = अणु
	.dma		= अणु
		.d_ops	= &floppy_dma_ops,
	पूर्ण,
	.fiq		= FIQ_FLOPPYDATA,
पूर्ण;

अटल dma_t sound_dma = अणु
	.d_ops		= &sound_dma_ops,
पूर्ण;

अटल पूर्णांक __init rpc_dma_init(व्योम)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	iomd_ग_लिखोb(0, IOMD_IO0CR);
	iomd_ग_लिखोb(0, IOMD_IO1CR);
	iomd_ग_लिखोb(0, IOMD_IO2CR);
	iomd_ग_लिखोb(0, IOMD_IO3CR);

	iomd_ग_लिखोb(0xa0, IOMD_DMATCR);

	/*
	 * Setup DMA channels 2,3 to be क्रम podules
	 * and channels 0,1 क्रम पूर्णांकernal devices
	 */
	iomd_ग_लिखोb(DMA_EXT_IO3|DMA_EXT_IO2, IOMD_DMAEXT);

	iomd_dma[DMA_0].base	= IOMD_BASE + IOMD_IO0CURA;
	iomd_dma[DMA_0].irq	= IRQ_DMA0;
	iomd_dma[DMA_1].base	= IOMD_BASE + IOMD_IO1CURA;
	iomd_dma[DMA_1].irq	= IRQ_DMA1;
	iomd_dma[DMA_2].base	= IOMD_BASE + IOMD_IO2CURA;
	iomd_dma[DMA_2].irq	= IRQ_DMA2;
	iomd_dma[DMA_3].base	= IOMD_BASE + IOMD_IO3CURA;
	iomd_dma[DMA_3].irq	= IRQ_DMA3;
	iomd_dma[DMA_S0].base	= IOMD_BASE + IOMD_SD0CURA;
	iomd_dma[DMA_S0].irq	= IRQ_DMAS0;
	iomd_dma[DMA_S1].base	= IOMD_BASE + IOMD_SD1CURA;
	iomd_dma[DMA_S1].irq	= IRQ_DMAS1;

	क्रम (i = DMA_0; i <= DMA_S1; i++) अणु
		iomd_dma[i].dma.d_ops = &iomd_dma_ops;

		ret = isa_dma_add(i, &iomd_dma[i].dma);
		अगर (ret)
			prपूर्णांकk("IOMDDMA%u: unable to register: %d\n", i, ret);
	पूर्ण

	ret = isa_dma_add(DMA_VIRTUAL_FLOPPY, &floppy_dma.dma);
	अगर (ret)
		prपूर्णांकk("IOMDFLOPPY: unable to register: %d\n", ret);
	ret = isa_dma_add(DMA_VIRTUAL_SOUND, &sound_dma);
	अगर (ret)
		prपूर्णांकk("IOMDSOUND: unable to register: %d\n", ret);
	वापस 0;
पूर्ण
core_initcall(rpc_dma_init);
