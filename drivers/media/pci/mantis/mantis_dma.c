<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
	Mantis PCI bridge driver

	Copyright (C) Manu Abraham (abraham.manu@gmail.com)

*/

#समावेश <linux/kernel.h>
#समावेश <यंत्र/page.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/pci.h>

#समावेश <यंत्र/irq.h>
#समावेश <linux/संकेत.स>
#समावेश <linux/sched.h>
#समावेश <linux/पूर्णांकerrupt.h>

#समावेश <media/dmxdev.h>
#समावेश <media/dvbdev.h>
#समावेश <media/dvb_demux.h>
#समावेश <media/dvb_frontend.h>
#समावेश <media/dvb_net.h>

#समावेश "mantis_common.h"
#समावेश "mantis_reg.h"
#समावेश "mantis_dma.h"

#घोषणा RISC_WRITE		(0x01 << 28)
#घोषणा RISC_JUMP		(0x07 << 28)
#घोषणा RISC_IRQ		(0x01 << 24)

#घोषणा RISC_STATUS(status)	((((~status) & 0x0f) << 20) | ((status & 0x0f) << 16))
#घोषणा RISC_FLUSH(risc_pos)		(risc_pos = 0)
#घोषणा RISC_INSTR(risc_pos, opcode)	(mantis->risc_cpu[risc_pos++] = cpu_to_le32(opcode))

#घोषणा MANTIS_BUF_SIZE		(64 * 1024)
#घोषणा MANTIS_BLOCK_BYTES      (MANTIS_BUF_SIZE / 4)
#घोषणा MANTIS_DMA_TR_BYTES     (2 * 1024) /* upper limit: 4095 bytes. */
#घोषणा MANTIS_BLOCK_COUNT	(MANTIS_BUF_SIZE / MANTIS_BLOCK_BYTES)

#घोषणा MANTIS_DMA_TR_UNITS     (MANTIS_BLOCK_BYTES / MANTIS_DMA_TR_BYTES)
/* MANTIS_BUF_SIZE / MANTIS_DMA_TR_UNITS must not exceed MANTIS_RISC_SIZE (4k RISC cmd buffer) */
#घोषणा MANTIS_RISC_SIZE	PAGE_SIZE /* RISC program must fit here. */

पूर्णांक mantis_dma_निकास(काष्ठा mantis_pci *mantis)
अणु
	अगर (mantis->buf_cpu) अणु
		dprपूर्णांकk(MANTIS_ERROR, 1,
			"DMA=0x%lx cpu=0x%p size=%d",
			(अचिन्हित दीर्घ) mantis->buf_dma,
			 mantis->buf_cpu,
			 MANTIS_BUF_SIZE);

		dma_मुक्त_coherent(&mantis->pdev->dev, MANTIS_BUF_SIZE,
				  mantis->buf_cpu, mantis->buf_dma);

		mantis->buf_cpu = शून्य;
	पूर्ण
	अगर (mantis->risc_cpu) अणु
		dprपूर्णांकk(MANTIS_ERROR, 1,
			"RISC=0x%lx cpu=0x%p size=%lx",
			(अचिन्हित दीर्घ) mantis->risc_dma,
			mantis->risc_cpu,
			MANTIS_RISC_SIZE);

		dma_मुक्त_coherent(&mantis->pdev->dev, MANTIS_RISC_SIZE,
				  mantis->risc_cpu, mantis->risc_dma);

		mantis->risc_cpu = शून्य;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mantis_dma_निकास);

अटल अंतरभूत पूर्णांक mantis_alloc_buffers(काष्ठा mantis_pci *mantis)
अणु
	अगर (!mantis->buf_cpu) अणु
		mantis->buf_cpu = dma_alloc_coherent(&mantis->pdev->dev,
						     MANTIS_BUF_SIZE,
						     &mantis->buf_dma, GFP_KERNEL);
		अगर (!mantis->buf_cpu) अणु
			dprपूर्णांकk(MANTIS_ERROR, 1,
				"DMA buffer allocation failed");

			जाओ err;
		पूर्ण
		dprपूर्णांकk(MANTIS_ERROR, 1,
			"DMA=0x%lx cpu=0x%p size=%d",
			(अचिन्हित दीर्घ) mantis->buf_dma,
			mantis->buf_cpu, MANTIS_BUF_SIZE);
	पूर्ण
	अगर (!mantis->risc_cpu) अणु
		mantis->risc_cpu = dma_alloc_coherent(&mantis->pdev->dev,
						      MANTIS_RISC_SIZE,
						      &mantis->risc_dma, GFP_KERNEL);

		अगर (!mantis->risc_cpu) अणु
			dprपूर्णांकk(MANTIS_ERROR, 1,
				"RISC program allocation failed");

			mantis_dma_निकास(mantis);

			जाओ err;
		पूर्ण
		dprपूर्णांकk(MANTIS_ERROR, 1,
			"RISC=0x%lx cpu=0x%p size=%lx",
			(अचिन्हित दीर्घ) mantis->risc_dma,
			mantis->risc_cpu, MANTIS_RISC_SIZE);
	पूर्ण

	वापस 0;
err:
	dprपूर्णांकk(MANTIS_ERROR, 1, "Out of memory (?) .....");
	वापस -ENOMEM;
पूर्ण

पूर्णांक mantis_dma_init(काष्ठा mantis_pci *mantis)
अणु
	पूर्णांक err;

	dprपूर्णांकk(MANTIS_DEBUG, 1, "Mantis DMA init");
	err = mantis_alloc_buffers(mantis);
	अगर (err < 0) अणु
		dprपूर्णांकk(MANTIS_ERROR, 1, "Error allocating DMA buffer");

		/* Stop RISC Engine */
		mmग_लिखो(0, MANTIS_DMA_CTL);

		वापस err;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mantis_dma_init);

अटल अंतरभूत व्योम mantis_risc_program(काष्ठा mantis_pci *mantis)
अणु
	u32 buf_pos = 0;
	u32 line, step;
	u32 risc_pos;

	dprपूर्णांकk(MANTIS_DEBUG, 1, "Mantis create RISC program");
	RISC_FLUSH(risc_pos);

	dprपूर्णांकk(MANTIS_DEBUG, 1, "risc len lines %u, bytes per line %u, bytes per DMA tr %u",
		MANTIS_BLOCK_COUNT, MANTIS_BLOCK_BYTES, MANTIS_DMA_TR_BYTES);

	क्रम (line = 0; line < MANTIS_BLOCK_COUNT; line++) अणु
		क्रम (step = 0; step < MANTIS_DMA_TR_UNITS; step++) अणु
			dprपूर्णांकk(MANTIS_DEBUG, 1, "RISC PROG line=[%d], step=[%d]", line, step);
			अगर (step == 0) अणु
				RISC_INSTR(risc_pos, RISC_WRITE	|
					   RISC_IRQ	|
					   RISC_STATUS(line) |
					   MANTIS_DMA_TR_BYTES);
			पूर्ण अन्यथा अणु
				RISC_INSTR(risc_pos, RISC_WRITE | MANTIS_DMA_TR_BYTES);
			पूर्ण
			RISC_INSTR(risc_pos, mantis->buf_dma + buf_pos);
			buf_pos += MANTIS_DMA_TR_BYTES;
		  पूर्ण
	पूर्ण
	RISC_INSTR(risc_pos, RISC_JUMP);
	RISC_INSTR(risc_pos, mantis->risc_dma);
पूर्ण

व्योम mantis_dma_start(काष्ठा mantis_pci *mantis)
अणु
	dprपूर्णांकk(MANTIS_DEBUG, 1, "Mantis Start DMA engine");

	mantis_risc_program(mantis);
	mmग_लिखो(mantis->risc_dma, MANTIS_RISC_START);
	mmग_लिखो(mmपढ़ो(MANTIS_GPIF_ADDR) | MANTIS_GPIF_HIFRDWRN, MANTIS_GPIF_ADDR);

	mmग_लिखो(0, MANTIS_DMA_CTL);
	mantis->last_block = mantis->busy_block = 0;

	mantis_unmask_पूर्णांकs(mantis, MANTIS_INT_RISCI);

	mmग_लिखो(MANTIS_FIFO_EN | MANTIS_DCAP_EN
			       | MANTIS_RISC_EN, MANTIS_DMA_CTL);

पूर्ण

व्योम mantis_dma_stop(काष्ठा mantis_pci *mantis)
अणु
	dprपूर्णांकk(MANTIS_DEBUG, 1, "Mantis Stop DMA engine");

	mmग_लिखो((mmपढ़ो(MANTIS_GPIF_ADDR) & (~(MANTIS_GPIF_HIFRDWRN))), MANTIS_GPIF_ADDR);

	mmग_लिखो((mmपढ़ो(MANTIS_DMA_CTL) & ~(MANTIS_FIFO_EN |
					    MANTIS_DCAP_EN |
					    MANTIS_RISC_EN)), MANTIS_DMA_CTL);

	mmग_लिखो(mmपढ़ो(MANTIS_INT_STAT), MANTIS_INT_STAT);

	mantis_mask_पूर्णांकs(mantis, MANTIS_INT_RISCI | MANTIS_INT_RISCEN);
पूर्ण


व्योम mantis_dma_xfer(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा mantis_pci *mantis = from_tasklet(mantis, t, tasklet);
	काष्ठा mantis_hwconfig *config = mantis->hwconfig;

	जबतक (mantis->last_block != mantis->busy_block) अणु
		dprपूर्णांकk(MANTIS_DEBUG, 1, "last block=[%d] finished block=[%d]",
			mantis->last_block, mantis->busy_block);

		(config->ts_size ? dvb_dmx_swfilter_204 : dvb_dmx_swfilter)
		(&mantis->demux, &mantis->buf_cpu[mantis->last_block * MANTIS_BLOCK_BYTES], MANTIS_BLOCK_BYTES);
		mantis->last_block = (mantis->last_block + 1) % MANTIS_BLOCK_COUNT;
	पूर्ण
पूर्ण
