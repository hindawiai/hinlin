<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  jmb38x_ms.c - JMicron jmb38x MemoryStick card पढ़ोer
 *
 *  Copyright (C) 2008 Alex Dubov <oakad@yahoo.com>
 */

#समावेश <linux/spinlock.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pci.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/delay.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/memstick.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>

#घोषणा DRIVER_NAME "jmb38x_ms"

अटल bool no_dma;
module_param(no_dma, bool, 0644);

क्रमागत अणु
	DMA_ADDRESS       = 0x00,
	BLOCK             = 0x04,
	DMA_CONTROL       = 0x08,
	TPC_P0            = 0x0c,
	TPC_P1            = 0x10,
	TPC               = 0x14,
	HOST_CONTROL      = 0x18,
	DATA              = 0x1c,
	STATUS            = 0x20,
	INT_STATUS        = 0x24,
	INT_STATUS_ENABLE = 0x28,
	INT_SIGNAL_ENABLE = 0x2c,
	TIMER             = 0x30,
	TIMER_CONTROL     = 0x34,
	PAD_OUTPUT_ENABLE = 0x38,
	PAD_PU_PD         = 0x3c,
	CLOCK_DELAY       = 0x40,
	ADMA_ADDRESS      = 0x44,
	CLOCK_CONTROL     = 0x48,
	LED_CONTROL       = 0x4c,
	VERSION           = 0x50
पूर्ण;

काष्ठा jmb38x_ms_host अणु
	काष्ठा jmb38x_ms        *chip;
	व्योम __iomem            *addr;
	spinlock_t              lock;
	काष्ठा tasklet_काष्ठा   notअगरy;
	पूर्णांक                     id;
	अक्षर                    host_id[32];
	पूर्णांक                     irq;
	अचिन्हित पूर्णांक            block_pos;
	अचिन्हित दीर्घ           समयout_jअगरfies;
	काष्ठा समयr_list       समयr;
	काष्ठा memstick_host	*msh;
	काष्ठा memstick_request *req;
	अचिन्हित अक्षर           cmd_flags;
	अचिन्हित अक्षर           io_pos;
	अचिन्हित अक्षर           अगरmode;
	अचिन्हित पूर्णांक            io_word[2];
पूर्ण;

काष्ठा jmb38x_ms अणु
	काष्ठा pci_dev        *pdev;
	पूर्णांक                   host_cnt;
	काष्ठा memstick_host  *hosts[];
पूर्ण;

#घोषणा BLOCK_COUNT_MASK       0xffff0000
#घोषणा BLOCK_SIZE_MASK        0x00000fff

#घोषणा DMA_CONTROL_ENABLE     0x00000001

#घोषणा TPC_DATA_SEL           0x00008000
#घोषणा TPC_सूची                0x00004000
#घोषणा TPC_WAIT_INT           0x00002000
#घोषणा TPC_GET_INT            0x00000800
#घोषणा TPC_CODE_SZ_MASK       0x00000700
#घोषणा TPC_DATA_SZ_MASK       0x00000007

#घोषणा HOST_CONTROL_TDELAY_EN 0x00040000
#घोषणा HOST_CONTROL_HW_OC_P   0x00010000
#घोषणा HOST_CONTROL_RESET_REQ 0x00008000
#घोषणा HOST_CONTROL_REI       0x00004000
#घोषणा HOST_CONTROL_LED       0x00000400
#घोषणा HOST_CONTROL_FAST_CLK  0x00000200
#घोषणा HOST_CONTROL_RESET     0x00000100
#घोषणा HOST_CONTROL_POWER_EN  0x00000080
#घोषणा HOST_CONTROL_CLOCK_EN  0x00000040
#घोषणा HOST_CONTROL_REO       0x00000008
#घोषणा HOST_CONTROL_IF_SHIFT  4

#घोषणा HOST_CONTROL_IF_SERIAL 0x0
#घोषणा HOST_CONTROL_IF_PAR4   0x1
#घोषणा HOST_CONTROL_IF_PAR8   0x3

#घोषणा STATUS_BUSY             0x00080000
#घोषणा STATUS_MS_DAT7          0x00040000
#घोषणा STATUS_MS_DAT6          0x00020000
#घोषणा STATUS_MS_DAT5          0x00010000
#घोषणा STATUS_MS_DAT4          0x00008000
#घोषणा STATUS_MS_DAT3          0x00004000
#घोषणा STATUS_MS_DAT2          0x00002000
#घोषणा STATUS_MS_DAT1          0x00001000
#घोषणा STATUS_MS_DAT0          0x00000800
#घोषणा STATUS_HAS_MEDIA        0x00000400
#घोषणा STATUS_FIFO_EMPTY       0x00000200
#घोषणा STATUS_FIFO_FULL        0x00000100
#घोषणा STATUS_MS_CED           0x00000080
#घोषणा STATUS_MS_ERR           0x00000040
#घोषणा STATUS_MS_BRQ           0x00000020
#घोषणा STATUS_MS_CNK           0x00000001

#घोषणा INT_STATUS_TPC_ERR      0x00080000
#घोषणा INT_STATUS_CRC_ERR      0x00040000
#घोषणा INT_STATUS_TIMER_TO     0x00020000
#घोषणा INT_STATUS_HSK_TO       0x00010000
#घोषणा INT_STATUS_ANY_ERR      0x00008000
#घोषणा INT_STATUS_FIFO_WRDY    0x00000080
#घोषणा INT_STATUS_FIFO_RRDY    0x00000040
#घोषणा INT_STATUS_MEDIA_OUT    0x00000010
#घोषणा INT_STATUS_MEDIA_IN     0x00000008
#घोषणा INT_STATUS_DMA_BOUNDARY 0x00000004
#घोषणा INT_STATUS_EOTRAN       0x00000002
#घोषणा INT_STATUS_EOTPC        0x00000001

#घोषणा INT_STATUS_ALL          0x000f801f

#घोषणा PAD_OUTPUT_ENABLE_MS  0x0F3F

#घोषणा PAD_PU_PD_OFF         0x7FFF0000
#घोषणा PAD_PU_PD_ON_MS_SOCK0 0x5f8f0000
#घोषणा PAD_PU_PD_ON_MS_SOCK1 0x0f0f0000

#घोषणा CLOCK_CONTROL_BY_MMIO 0x00000008
#घोषणा CLOCK_CONTROL_40MHZ   0x00000001
#घोषणा CLOCK_CONTROL_50MHZ   0x00000002
#घोषणा CLOCK_CONTROL_60MHZ   0x00000010
#घोषणा CLOCK_CONTROL_62_5MHZ 0x00000004
#घोषणा CLOCK_CONTROL_OFF     0x00000000

#घोषणा PCI_CTL_CLOCK_DLY_ADDR   0x000000b0

क्रमागत अणु
	CMD_READY    = 0x01,
	FIFO_READY   = 0x02,
	REG_DATA     = 0x04,
	DMA_DATA     = 0x08
पूर्ण;

अटल अचिन्हित पूर्णांक jmb38x_ms_पढ़ो_data(काष्ठा jmb38x_ms_host *host,
					अचिन्हित अक्षर *buf, अचिन्हित पूर्णांक length)
अणु
	अचिन्हित पूर्णांक off = 0;

	जबतक (host->io_pos && length) अणु
		buf[off++] = host->io_word[0] & 0xff;
		host->io_word[0] >>= 8;
		length--;
		host->io_pos--;
	पूर्ण

	अगर (!length)
		वापस off;

	जबतक (!(STATUS_FIFO_EMPTY & पढ़ोl(host->addr + STATUS))) अणु
		अगर (length < 4)
			अवरोध;
		*(अचिन्हित पूर्णांक *)(buf + off) = __raw_पढ़ोl(host->addr + DATA);
		length -= 4;
		off += 4;
	पूर्ण

	अगर (length
	    && !(STATUS_FIFO_EMPTY & पढ़ोl(host->addr + STATUS))) अणु
		host->io_word[0] = पढ़ोl(host->addr + DATA);
		क्रम (host->io_pos = 4; host->io_pos; --host->io_pos) अणु
			buf[off++] = host->io_word[0] & 0xff;
			host->io_word[0] >>= 8;
			length--;
			अगर (!length)
				अवरोध;
		पूर्ण
	पूर्ण

	वापस off;
पूर्ण

अटल अचिन्हित पूर्णांक jmb38x_ms_पढ़ो_reg_data(काष्ठा jmb38x_ms_host *host,
					    अचिन्हित अक्षर *buf,
					    अचिन्हित पूर्णांक length)
अणु
	अचिन्हित पूर्णांक off = 0;

	जबतक (host->io_pos > 4 && length) अणु
		buf[off++] = host->io_word[0] & 0xff;
		host->io_word[0] >>= 8;
		length--;
		host->io_pos--;
	पूर्ण

	अगर (!length)
		वापस off;

	जबतक (host->io_pos && length) अणु
		buf[off++] = host->io_word[1] & 0xff;
		host->io_word[1] >>= 8;
		length--;
		host->io_pos--;
	पूर्ण

	वापस off;
पूर्ण

अटल अचिन्हित पूर्णांक jmb38x_ms_ग_लिखो_data(काष्ठा jmb38x_ms_host *host,
					 अचिन्हित अक्षर *buf,
					 अचिन्हित पूर्णांक length)
अणु
	अचिन्हित पूर्णांक off = 0;

	अगर (host->io_pos) अणु
		जबतक (host->io_pos < 4 && length) अणु
			host->io_word[0] |=  buf[off++] << (host->io_pos * 8);
			host->io_pos++;
			length--;
		पूर्ण
	पूर्ण

	अगर (host->io_pos == 4
	    && !(STATUS_FIFO_FULL & पढ़ोl(host->addr + STATUS))) अणु
		ग_लिखोl(host->io_word[0], host->addr + DATA);
		host->io_pos = 0;
		host->io_word[0] = 0;
	पूर्ण अन्यथा अगर (host->io_pos) अणु
		वापस off;
	पूर्ण

	अगर (!length)
		वापस off;

	जबतक (!(STATUS_FIFO_FULL & पढ़ोl(host->addr + STATUS))) अणु
		अगर (length < 4)
			अवरोध;

		__raw_ग_लिखोl(*(अचिन्हित पूर्णांक *)(buf + off),
			     host->addr + DATA);
		length -= 4;
		off += 4;
	पूर्ण

	चयन (length) अणु
	हाल 3:
		host->io_word[0] |= buf[off + 2] << 16;
		host->io_pos++;
		fallthrough;
	हाल 2:
		host->io_word[0] |= buf[off + 1] << 8;
		host->io_pos++;
		fallthrough;
	हाल 1:
		host->io_word[0] |= buf[off];
		host->io_pos++;
	पूर्ण

	off += host->io_pos;

	वापस off;
पूर्ण

अटल अचिन्हित पूर्णांक jmb38x_ms_ग_लिखो_reg_data(काष्ठा jmb38x_ms_host *host,
					     अचिन्हित अक्षर *buf,
					     अचिन्हित पूर्णांक length)
अणु
	अचिन्हित पूर्णांक off = 0;

	जबतक (host->io_pos < 4 && length) अणु
		host->io_word[0] &= ~(0xff << (host->io_pos * 8));
		host->io_word[0] |=  buf[off++] << (host->io_pos * 8);
		host->io_pos++;
		length--;
	पूर्ण

	अगर (!length)
		वापस off;

	जबतक (host->io_pos < 8 && length) अणु
		host->io_word[1] &= ~(0xff << (host->io_pos * 8));
		host->io_word[1] |=  buf[off++] << (host->io_pos * 8);
		host->io_pos++;
		length--;
	पूर्ण

	वापस off;
पूर्ण

अटल पूर्णांक jmb38x_ms_transfer_data(काष्ठा jmb38x_ms_host *host)
अणु
	अचिन्हित पूर्णांक length;
	अचिन्हित पूर्णांक off;
	अचिन्हित पूर्णांक t_size, p_cnt;
	अचिन्हित अक्षर *buf;
	काष्ठा page *pg;
	अचिन्हित दीर्घ flags = 0;

	अगर (host->req->दीर्घ_data) अणु
		length = host->req->sg.length - host->block_pos;
		off = host->req->sg.offset + host->block_pos;
	पूर्ण अन्यथा अणु
		length = host->req->data_len - host->block_pos;
		off = 0;
	पूर्ण

	जबतक (length) अणु
		अचिन्हित पूर्णांक p_off;

		अगर (host->req->दीर्घ_data) अणु
			pg = nth_page(sg_page(&host->req->sg),
				      off >> PAGE_SHIFT);
			p_off = offset_in_page(off);
			p_cnt = PAGE_SIZE - p_off;
			p_cnt = min(p_cnt, length);

			local_irq_save(flags);
			buf = kmap_atomic(pg) + p_off;
		पूर्ण अन्यथा अणु
			buf = host->req->data + host->block_pos;
			p_cnt = host->req->data_len - host->block_pos;
		पूर्ण

		अगर (host->req->data_dir == WRITE)
			t_size = !(host->cmd_flags & REG_DATA)
				 ? jmb38x_ms_ग_लिखो_data(host, buf, p_cnt)
				 : jmb38x_ms_ग_लिखो_reg_data(host, buf, p_cnt);
		अन्यथा
			t_size = !(host->cmd_flags & REG_DATA)
				 ? jmb38x_ms_पढ़ो_data(host, buf, p_cnt)
				 : jmb38x_ms_पढ़ो_reg_data(host, buf, p_cnt);

		अगर (host->req->दीर्घ_data) अणु
			kunmap_atomic(buf - p_off);
			local_irq_restore(flags);
		पूर्ण

		अगर (!t_size)
			अवरोध;
		host->block_pos += t_size;
		length -= t_size;
		off += t_size;
	पूर्ण

	अगर (!length && host->req->data_dir == WRITE) अणु
		अगर (host->cmd_flags & REG_DATA) अणु
			ग_लिखोl(host->io_word[0], host->addr + TPC_P0);
			ग_लिखोl(host->io_word[1], host->addr + TPC_P1);
		पूर्ण अन्यथा अगर (host->io_pos) अणु
			ग_लिखोl(host->io_word[0], host->addr + DATA);
		पूर्ण
	पूर्ण

	वापस length;
पूर्ण

अटल पूर्णांक jmb38x_ms_issue_cmd(काष्ठा memstick_host *msh)
अणु
	काष्ठा jmb38x_ms_host *host = memstick_priv(msh);
	अचिन्हित पूर्णांक data_len, cmd, t_val;

	अगर (!(STATUS_HAS_MEDIA & पढ़ोl(host->addr + STATUS))) अणु
		dev_dbg(&msh->dev, "no media status\n");
		host->req->error = -ETIME;
		वापस host->req->error;
	पूर्ण

	dev_dbg(&msh->dev, "control %08x\n", पढ़ोl(host->addr + HOST_CONTROL));
	dev_dbg(&msh->dev, "status %08x\n", पढ़ोl(host->addr + INT_STATUS));
	dev_dbg(&msh->dev, "hstatus %08x\n", पढ़ोl(host->addr + STATUS));

	host->cmd_flags = 0;
	host->block_pos = 0;
	host->io_pos = 0;
	host->io_word[0] = 0;
	host->io_word[1] = 0;

	cmd = host->req->tpc << 16;
	cmd |= TPC_DATA_SEL;

	अगर (host->req->data_dir == READ)
		cmd |= TPC_सूची;

	अगर (host->req->need_card_पूर्णांक) अणु
		अगर (host->अगरmode == MEMSTICK_SERIAL)
			cmd |= TPC_GET_INT;
		अन्यथा
			cmd |= TPC_WAIT_INT;
	पूर्ण

	अगर (!no_dma)
		host->cmd_flags |= DMA_DATA;

	अगर (host->req->दीर्घ_data) अणु
		data_len = host->req->sg.length;
	पूर्ण अन्यथा अणु
		data_len = host->req->data_len;
		host->cmd_flags &= ~DMA_DATA;
	पूर्ण

	अगर (data_len <= 8) अणु
		cmd &= ~(TPC_DATA_SEL | 0xf);
		host->cmd_flags |= REG_DATA;
		cmd |= data_len & 0xf;
		host->cmd_flags &= ~DMA_DATA;
	पूर्ण

	अगर (host->cmd_flags & DMA_DATA) अणु
		अगर (1 != dma_map_sg(&host->chip->pdev->dev, &host->req->sg, 1,
				    host->req->data_dir == READ
				    ? DMA_FROM_DEVICE
				    : DMA_TO_DEVICE)) अणु
			host->req->error = -ENOMEM;
			वापस host->req->error;
		पूर्ण
		data_len = sg_dma_len(&host->req->sg);
		ग_लिखोl(sg_dma_address(&host->req->sg),
		       host->addr + DMA_ADDRESS);
		ग_लिखोl(((1 << 16) & BLOCK_COUNT_MASK)
		       | (data_len & BLOCK_SIZE_MASK),
		       host->addr + BLOCK);
		ग_लिखोl(DMA_CONTROL_ENABLE, host->addr + DMA_CONTROL);
	पूर्ण अन्यथा अगर (!(host->cmd_flags & REG_DATA)) अणु
		ग_लिखोl(((1 << 16) & BLOCK_COUNT_MASK)
		       | (data_len & BLOCK_SIZE_MASK),
		       host->addr + BLOCK);
		t_val = पढ़ोl(host->addr + INT_STATUS_ENABLE);
		t_val |= host->req->data_dir == READ
			 ? INT_STATUS_FIFO_RRDY
			 : INT_STATUS_FIFO_WRDY;

		ग_लिखोl(t_val, host->addr + INT_STATUS_ENABLE);
		ग_लिखोl(t_val, host->addr + INT_SIGNAL_ENABLE);
	पूर्ण अन्यथा अणु
		cmd &= ~(TPC_DATA_SEL | 0xf);
		host->cmd_flags |= REG_DATA;
		cmd |= data_len & 0xf;

		अगर (host->req->data_dir == WRITE) अणु
			jmb38x_ms_transfer_data(host);
			ग_लिखोl(host->io_word[0], host->addr + TPC_P0);
			ग_लिखोl(host->io_word[1], host->addr + TPC_P1);
		पूर्ण
	पूर्ण

	mod_समयr(&host->समयr, jअगरfies + host->समयout_jअगरfies);
	ग_लिखोl(HOST_CONTROL_LED | पढ़ोl(host->addr + HOST_CONTROL),
	       host->addr + HOST_CONTROL);
	host->req->error = 0;

	ग_लिखोl(cmd, host->addr + TPC);
	dev_dbg(&msh->dev, "executing TPC %08x, len %x\n", cmd, data_len);

	वापस 0;
पूर्ण

अटल व्योम jmb38x_ms_complete_cmd(काष्ठा memstick_host *msh, पूर्णांक last)
अणु
	काष्ठा jmb38x_ms_host *host = memstick_priv(msh);
	अचिन्हित पूर्णांक t_val = 0;
	पूर्णांक rc;

	del_समयr(&host->समयr);

	dev_dbg(&msh->dev, "c control %08x\n",
		पढ़ोl(host->addr + HOST_CONTROL));
	dev_dbg(&msh->dev, "c status %08x\n",
		पढ़ोl(host->addr + INT_STATUS));
	dev_dbg(&msh->dev, "c hstatus %08x\n", पढ़ोl(host->addr + STATUS));

	host->req->पूर्णांक_reg = पढ़ोl(host->addr + STATUS) & 0xff;

	ग_लिखोl(0, host->addr + BLOCK);
	ग_लिखोl(0, host->addr + DMA_CONTROL);

	अगर (host->cmd_flags & DMA_DATA) अणु
		dma_unmap_sg(&host->chip->pdev->dev, &host->req->sg, 1,
			     host->req->data_dir == READ
			     ? DMA_FROM_DEVICE : DMA_TO_DEVICE);
	पूर्ण अन्यथा अणु
		t_val = पढ़ोl(host->addr + INT_STATUS_ENABLE);
		अगर (host->req->data_dir == READ)
			t_val &= ~INT_STATUS_FIFO_RRDY;
		अन्यथा
			t_val &= ~INT_STATUS_FIFO_WRDY;

		ग_लिखोl(t_val, host->addr + INT_STATUS_ENABLE);
		ग_लिखोl(t_val, host->addr + INT_SIGNAL_ENABLE);
	पूर्ण

	ग_लिखोl((~HOST_CONTROL_LED) & पढ़ोl(host->addr + HOST_CONTROL),
	       host->addr + HOST_CONTROL);

	अगर (!last) अणु
		करो अणु
			rc = memstick_next_req(msh, &host->req);
		पूर्ण जबतक (!rc && jmb38x_ms_issue_cmd(msh));
	पूर्ण अन्यथा अणु
		करो अणु
			rc = memstick_next_req(msh, &host->req);
			अगर (!rc)
				host->req->error = -ETIME;
		पूर्ण जबतक (!rc);
	पूर्ण
पूर्ण

अटल irqवापस_t jmb38x_ms_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा memstick_host *msh = dev_id;
	काष्ठा jmb38x_ms_host *host = memstick_priv(msh);
	अचिन्हित पूर्णांक irq_status;

	spin_lock(&host->lock);
	irq_status = पढ़ोl(host->addr + INT_STATUS);
	dev_dbg(&host->chip->pdev->dev, "irq_status = %08x\n", irq_status);
	अगर (irq_status == 0 || irq_status == (~0)) अणु
		spin_unlock(&host->lock);
		वापस IRQ_NONE;
	पूर्ण

	अगर (host->req) अणु
		अगर (irq_status & INT_STATUS_ANY_ERR) अणु
			अगर (irq_status & INT_STATUS_CRC_ERR)
				host->req->error = -EILSEQ;
			अन्यथा अगर (irq_status & INT_STATUS_TPC_ERR) अणु
				dev_dbg(&host->chip->pdev->dev, "TPC_ERR\n");
				jmb38x_ms_complete_cmd(msh, 0);
			पूर्ण अन्यथा
				host->req->error = -ETIME;
		पूर्ण अन्यथा अणु
			अगर (host->cmd_flags & DMA_DATA) अणु
				अगर (irq_status & INT_STATUS_EOTRAN)
					host->cmd_flags |= FIFO_READY;
			पूर्ण अन्यथा अणु
				अगर (irq_status & (INT_STATUS_FIFO_RRDY
						  | INT_STATUS_FIFO_WRDY))
					jmb38x_ms_transfer_data(host);

				अगर (irq_status & INT_STATUS_EOTRAN) अणु
					jmb38x_ms_transfer_data(host);
					host->cmd_flags |= FIFO_READY;
				पूर्ण
			पूर्ण

			अगर (irq_status & INT_STATUS_EOTPC) अणु
				host->cmd_flags |= CMD_READY;
				अगर (host->cmd_flags & REG_DATA) अणु
					अगर (host->req->data_dir == READ) अणु
						host->io_word[0]
							= पढ़ोl(host->addr
								+ TPC_P0);
						host->io_word[1]
							= पढ़ोl(host->addr
								+ TPC_P1);
						host->io_pos = 8;

						jmb38x_ms_transfer_data(host);
					पूर्ण
					host->cmd_flags |= FIFO_READY;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (irq_status & (INT_STATUS_MEDIA_IN | INT_STATUS_MEDIA_OUT)) अणु
		dev_dbg(&host->chip->pdev->dev, "media changed\n");
		memstick_detect_change(msh);
	पूर्ण

	ग_लिखोl(irq_status, host->addr + INT_STATUS);

	अगर (host->req
	    && (((host->cmd_flags & CMD_READY)
		 && (host->cmd_flags & FIFO_READY))
		|| host->req->error))
		jmb38x_ms_complete_cmd(msh, 0);

	spin_unlock(&host->lock);
	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम jmb38x_ms_पात(काष्ठा समयr_list *t)
अणु
	काष्ठा jmb38x_ms_host *host = from_समयr(host, t, समयr);
	काष्ठा memstick_host *msh = host->msh;
	अचिन्हित दीर्घ flags;

	dev_dbg(&host->chip->pdev->dev, "abort\n");
	spin_lock_irqsave(&host->lock, flags);
	अगर (host->req) अणु
		host->req->error = -ETIME;
		jmb38x_ms_complete_cmd(msh, 0);
	पूर्ण
	spin_unlock_irqrestore(&host->lock, flags);
पूर्ण

अटल व्योम jmb38x_ms_req_tasklet(अचिन्हित दीर्घ data)
अणु
	काष्ठा memstick_host *msh = (काष्ठा memstick_host *)data;
	काष्ठा jmb38x_ms_host *host = memstick_priv(msh);
	अचिन्हित दीर्घ flags;
	पूर्णांक rc;

	spin_lock_irqsave(&host->lock, flags);
	अगर (!host->req) अणु
		करो अणु
			rc = memstick_next_req(msh, &host->req);
			dev_dbg(&host->chip->pdev->dev, "tasklet req %d\n", rc);
		पूर्ण जबतक (!rc && jmb38x_ms_issue_cmd(msh));
	पूर्ण
	spin_unlock_irqrestore(&host->lock, flags);
पूर्ण

अटल व्योम jmb38x_ms_dummy_submit(काष्ठा memstick_host *msh)
अणु
	वापस;
पूर्ण

अटल व्योम jmb38x_ms_submit_req(काष्ठा memstick_host *msh)
अणु
	काष्ठा jmb38x_ms_host *host = memstick_priv(msh);

	tasklet_schedule(&host->notअगरy);
पूर्ण

अटल पूर्णांक jmb38x_ms_reset(काष्ठा jmb38x_ms_host *host)
अणु
	पूर्णांक cnt;

	ग_लिखोl(HOST_CONTROL_RESET_REQ | HOST_CONTROL_CLOCK_EN
	       | पढ़ोl(host->addr + HOST_CONTROL),
	       host->addr + HOST_CONTROL);

	क्रम (cnt = 0; cnt < 20; ++cnt) अणु
		अगर (!(HOST_CONTROL_RESET_REQ
		      & पढ़ोl(host->addr + HOST_CONTROL)))
			जाओ reset_next;

		ndelay(20);
	पूर्ण
	dev_dbg(&host->chip->pdev->dev, "reset_req timeout\n");

reset_next:
	ग_लिखोl(HOST_CONTROL_RESET | HOST_CONTROL_CLOCK_EN
	       | पढ़ोl(host->addr + HOST_CONTROL),
	       host->addr + HOST_CONTROL);

	क्रम (cnt = 0; cnt < 20; ++cnt) अणु
		अगर (!(HOST_CONTROL_RESET
		      & पढ़ोl(host->addr + HOST_CONTROL)))
			जाओ reset_ok;

		ndelay(20);
	पूर्ण
	dev_dbg(&host->chip->pdev->dev, "reset timeout\n");
	वापस -EIO;

reset_ok:
	ग_लिखोl(INT_STATUS_ALL, host->addr + INT_SIGNAL_ENABLE);
	ग_लिखोl(INT_STATUS_ALL, host->addr + INT_STATUS_ENABLE);
	वापस 0;
पूर्ण

अटल पूर्णांक jmb38x_ms_set_param(काष्ठा memstick_host *msh,
			       क्रमागत memstick_param param,
			       पूर्णांक value)
अणु
	काष्ठा jmb38x_ms_host *host = memstick_priv(msh);
	अचिन्हित पूर्णांक host_ctl = पढ़ोl(host->addr + HOST_CONTROL);
	अचिन्हित पूर्णांक घड़ी_ctl = CLOCK_CONTROL_BY_MMIO, घड़ी_delay = 0;
	पूर्णांक rc = 0;

	चयन (param) अणु
	हाल MEMSTICK_POWER:
		अगर (value == MEMSTICK_POWER_ON) अणु
			rc = jmb38x_ms_reset(host);
			अगर (rc)
				वापस rc;

			host_ctl = 7;
			host_ctl |= HOST_CONTROL_POWER_EN
				 | HOST_CONTROL_CLOCK_EN;
			ग_लिखोl(host_ctl, host->addr + HOST_CONTROL);

			ग_लिखोl(host->id ? PAD_PU_PD_ON_MS_SOCK1
					: PAD_PU_PD_ON_MS_SOCK0,
			       host->addr + PAD_PU_PD);

			ग_लिखोl(PAD_OUTPUT_ENABLE_MS,
			       host->addr + PAD_OUTPUT_ENABLE);

			msleep(10);
			dev_dbg(&host->chip->pdev->dev, "power on\n");
		पूर्ण अन्यथा अगर (value == MEMSTICK_POWER_OFF) अणु
			host_ctl &= ~(HOST_CONTROL_POWER_EN
				      | HOST_CONTROL_CLOCK_EN);
			ग_लिखोl(host_ctl, host->addr +  HOST_CONTROL);
			ग_लिखोl(0, host->addr + PAD_OUTPUT_ENABLE);
			ग_लिखोl(PAD_PU_PD_OFF, host->addr + PAD_PU_PD);
			dev_dbg(&host->chip->pdev->dev, "power off\n");
		पूर्ण अन्यथा
			वापस -EINVAL;
		अवरोध;
	हाल MEMSTICK_INTERFACE:
		dev_dbg(&host->chip->pdev->dev,
			"Set Host Interface Mode to %d\n", value);
		host_ctl &= ~(HOST_CONTROL_FAST_CLK | HOST_CONTROL_REI |
			      HOST_CONTROL_REO);
		host_ctl |= HOST_CONTROL_TDELAY_EN | HOST_CONTROL_HW_OC_P;
		host_ctl &= ~(3 << HOST_CONTROL_IF_SHIFT);

		अगर (value == MEMSTICK_SERIAL) अणु
			host_ctl |= HOST_CONTROL_IF_SERIAL
				    << HOST_CONTROL_IF_SHIFT;
			host_ctl |= HOST_CONTROL_REI;
			घड़ी_ctl |= CLOCK_CONTROL_40MHZ;
			घड़ी_delay = 0;
		पूर्ण अन्यथा अगर (value == MEMSTICK_PAR4) अणु
			host_ctl |= HOST_CONTROL_FAST_CLK;
			host_ctl |= HOST_CONTROL_IF_PAR4
				    << HOST_CONTROL_IF_SHIFT;
			host_ctl |= HOST_CONTROL_REO;
			घड़ी_ctl |= CLOCK_CONTROL_40MHZ;
			घड़ी_delay = 4;
		पूर्ण अन्यथा अगर (value == MEMSTICK_PAR8) अणु
			host_ctl |= HOST_CONTROL_FAST_CLK;
			host_ctl |= HOST_CONTROL_IF_PAR8
				    << HOST_CONTROL_IF_SHIFT;
			घड़ी_ctl |= CLOCK_CONTROL_50MHZ;
			घड़ी_delay = 0;
		पूर्ण अन्यथा
			वापस -EINVAL;

		ग_लिखोl(host_ctl, host->addr + HOST_CONTROL);
		ग_लिखोl(CLOCK_CONTROL_OFF, host->addr + CLOCK_CONTROL);
		ग_लिखोl(घड़ी_ctl, host->addr + CLOCK_CONTROL);
		pci_ग_लिखो_config_byte(host->chip->pdev,
				      PCI_CTL_CLOCK_DLY_ADDR + 1,
				      घड़ी_delay);
		host->अगरmode = value;
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

#घोषणा PCI_PMOS0_CONTROL		0xae
#घोषणा  PMOS0_ENABLE			0x01
#घोषणा  PMOS0_OVERCURRENT_LEVEL_2_4V	0x06
#घोषणा  PMOS0_EN_OVERCURRENT_DEBOUNCE	0x40
#घोषणा  PMOS0_SW_LED_POLARITY_ENABLE	0x80
#घोषणा  PMOS0_ACTIVE_BITS (PMOS0_ENABLE | PMOS0_EN_OVERCURRENT_DEBOUNCE | \
			    PMOS0_OVERCURRENT_LEVEL_2_4V)
#घोषणा PCI_PMOS1_CONTROL		0xbd
#घोषणा  PMOS1_ACTIVE_BITS		0x4a
#घोषणा PCI_CLOCK_CTL			0xb9

अटल पूर्णांक jmb38x_ms_pmos(काष्ठा pci_dev *pdev, पूर्णांक flag)
अणु
	अचिन्हित अक्षर val;

	pci_पढ़ो_config_byte(pdev, PCI_PMOS0_CONTROL, &val);
	अगर (flag)
		val |= PMOS0_ACTIVE_BITS;
	अन्यथा
		val &= ~PMOS0_ACTIVE_BITS;
	pci_ग_लिखो_config_byte(pdev, PCI_PMOS0_CONTROL, val);
	dev_dbg(&pdev->dev, "JMB38x: set PMOS0 val 0x%x\n", val);

	अगर (pci_resource_flags(pdev, 1)) अणु
		pci_पढ़ो_config_byte(pdev, PCI_PMOS1_CONTROL, &val);
		अगर (flag)
			val |= PMOS1_ACTIVE_BITS;
		अन्यथा
			val &= ~PMOS1_ACTIVE_BITS;
		pci_ग_लिखो_config_byte(pdev, PCI_PMOS1_CONTROL, val);
		dev_dbg(&pdev->dev, "JMB38x: set PMOS1 val 0x%x\n", val);
	पूर्ण

	pci_पढ़ो_config_byte(pdev, PCI_CLOCK_CTL, &val);
	pci_ग_लिखो_config_byte(pdev, PCI_CLOCK_CTL, val & ~0x0f);
	pci_ग_लिखो_config_byte(pdev, PCI_CLOCK_CTL, val | 0x01);
	dev_dbg(&pdev->dev, "Clock Control by PCI config is disabled!\n");

        वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused jmb38x_ms_suspend(काष्ठा device *dev)
अणु
	काष्ठा jmb38x_ms *jm = dev_get_drvdata(dev);

	पूर्णांक cnt;

	क्रम (cnt = 0; cnt < jm->host_cnt; ++cnt) अणु
		अगर (!jm->hosts[cnt])
			अवरोध;
		memstick_suspend_host(jm->hosts[cnt]);
	पूर्ण

	device_wakeup_disable(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused jmb38x_ms_resume(काष्ठा device *dev)
अणु
	काष्ठा jmb38x_ms *jm = dev_get_drvdata(dev);
	पूर्णांक rc;

	jmb38x_ms_pmos(to_pci_dev(dev), 1);

	क्रम (rc = 0; rc < jm->host_cnt; ++rc) अणु
		अगर (!jm->hosts[rc])
			अवरोध;
		memstick_resume_host(jm->hosts[rc]);
		memstick_detect_change(jm->hosts[rc]);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक jmb38x_ms_count_slots(काष्ठा pci_dev *pdev)
अणु
	पूर्णांक cnt, rc = 0;

	क्रम (cnt = 0; cnt < PCI_STD_NUM_BARS; ++cnt) अणु
		अगर (!(IORESOURCE_MEM & pci_resource_flags(pdev, cnt)))
			अवरोध;

		अगर (256 != pci_resource_len(pdev, cnt))
			अवरोध;

		++rc;
	पूर्ण
	वापस rc;
पूर्ण

अटल काष्ठा memstick_host *jmb38x_ms_alloc_host(काष्ठा jmb38x_ms *jm, पूर्णांक cnt)
अणु
	काष्ठा memstick_host *msh;
	काष्ठा jmb38x_ms_host *host;

	msh = memstick_alloc_host(माप(काष्ठा jmb38x_ms_host),
				  &jm->pdev->dev);
	अगर (!msh)
		वापस शून्य;

	host = memstick_priv(msh);
	host->msh = msh;
	host->chip = jm;
	host->addr = ioremap(pci_resource_start(jm->pdev, cnt),
			     pci_resource_len(jm->pdev, cnt));
	अगर (!host->addr)
		जाओ err_out_मुक्त;

	spin_lock_init(&host->lock);
	host->id = cnt;
	snम_लिखो(host->host_id, माप(host->host_id), DRIVER_NAME ":slot%d",
		 host->id);
	host->irq = jm->pdev->irq;
	host->समयout_jअगरfies = msecs_to_jअगरfies(1000);

	tasklet_init(&host->notअगरy, jmb38x_ms_req_tasklet, (अचिन्हित दीर्घ)msh);
	msh->request = jmb38x_ms_submit_req;
	msh->set_param = jmb38x_ms_set_param;

	msh->caps = MEMSTICK_CAP_PAR4 | MEMSTICK_CAP_PAR8;

	समयr_setup(&host->समयr, jmb38x_ms_पात, 0);

	अगर (!request_irq(host->irq, jmb38x_ms_isr, IRQF_SHARED, host->host_id,
			 msh))
		वापस msh;

	iounmap(host->addr);
err_out_मुक्त:
	kमुक्त(msh);
	वापस शून्य;
पूर्ण

अटल व्योम jmb38x_ms_मुक्त_host(काष्ठा memstick_host *msh)
अणु
	काष्ठा jmb38x_ms_host *host = memstick_priv(msh);

	मुक्त_irq(host->irq, msh);
	iounmap(host->addr);
	memstick_मुक्त_host(msh);
पूर्ण

अटल पूर्णांक jmb38x_ms_probe(काष्ठा pci_dev *pdev,
			   स्थिर काष्ठा pci_device_id *dev_id)
अणु
	काष्ठा jmb38x_ms *jm;
	पूर्णांक pci_dev_busy = 0;
	पूर्णांक rc, cnt;

	rc = dma_set_mask(&pdev->dev, DMA_BIT_MASK(32));
	अगर (rc)
		वापस rc;

	rc = pci_enable_device(pdev);
	अगर (rc)
		वापस rc;

	pci_set_master(pdev);

	rc = pci_request_regions(pdev, DRIVER_NAME);
	अगर (rc) अणु
		pci_dev_busy = 1;
		जाओ err_out;
	पूर्ण

	jmb38x_ms_pmos(pdev, 1);

	cnt = jmb38x_ms_count_slots(pdev);
	अगर (!cnt) अणु
		rc = -ENODEV;
		pci_dev_busy = 1;
		जाओ err_out_पूर्णांक;
	पूर्ण

	jm = kzalloc(माप(काष्ठा jmb38x_ms)
		     + cnt * माप(काष्ठा memstick_host *), GFP_KERNEL);
	अगर (!jm) अणु
		rc = -ENOMEM;
		जाओ err_out_पूर्णांक;
	पूर्ण

	jm->pdev = pdev;
	jm->host_cnt = cnt;
	pci_set_drvdata(pdev, jm);

	क्रम (cnt = 0; cnt < jm->host_cnt; ++cnt) अणु
		jm->hosts[cnt] = jmb38x_ms_alloc_host(jm, cnt);
		अगर (!jm->hosts[cnt])
			अवरोध;

		rc = memstick_add_host(jm->hosts[cnt]);

		अगर (rc) अणु
			jmb38x_ms_मुक्त_host(jm->hosts[cnt]);
			jm->hosts[cnt] = शून्य;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (cnt)
		वापस 0;

	rc = -ENODEV;

	pci_set_drvdata(pdev, शून्य);
	kमुक्त(jm);
err_out_पूर्णांक:
	pci_release_regions(pdev);
err_out:
	अगर (!pci_dev_busy)
		pci_disable_device(pdev);
	वापस rc;
पूर्ण

अटल व्योम jmb38x_ms_हटाओ(काष्ठा pci_dev *dev)
अणु
	काष्ठा jmb38x_ms *jm = pci_get_drvdata(dev);
	काष्ठा jmb38x_ms_host *host;
	पूर्णांक cnt;
	अचिन्हित दीर्घ flags;

	क्रम (cnt = 0; cnt < jm->host_cnt; ++cnt) अणु
		अगर (!jm->hosts[cnt])
			अवरोध;

		host = memstick_priv(jm->hosts[cnt]);

		jm->hosts[cnt]->request = jmb38x_ms_dummy_submit;
		tasklet_समाप्त(&host->notअगरy);
		ग_लिखोl(0, host->addr + INT_SIGNAL_ENABLE);
		ग_लिखोl(0, host->addr + INT_STATUS_ENABLE);
		dev_dbg(&jm->pdev->dev, "interrupts off\n");
		spin_lock_irqsave(&host->lock, flags);
		अगर (host->req) अणु
			host->req->error = -ETIME;
			jmb38x_ms_complete_cmd(jm->hosts[cnt], 1);
		पूर्ण
		spin_unlock_irqrestore(&host->lock, flags);

		memstick_हटाओ_host(jm->hosts[cnt]);
		dev_dbg(&jm->pdev->dev, "host removed\n");

		jmb38x_ms_मुक्त_host(jm->hosts[cnt]);
	पूर्ण

	jmb38x_ms_pmos(dev, 0);

	pci_set_drvdata(dev, शून्य);
	pci_release_regions(dev);
	pci_disable_device(dev);
	kमुक्त(jm);
पूर्ण

अटल काष्ठा pci_device_id jmb38x_ms_id_tbl [] = अणु
	अणु PCI_VDEVICE(JMICRON, PCI_DEVICE_ID_JMICRON_JMB38X_MS) पूर्ण,
	अणु PCI_VDEVICE(JMICRON, PCI_DEVICE_ID_JMICRON_JMB385_MS) पूर्ण,
	अणु PCI_VDEVICE(JMICRON, PCI_DEVICE_ID_JMICRON_JMB390_MS) पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल SIMPLE_DEV_PM_OPS(jmb38x_ms_pm_ops, jmb38x_ms_suspend, jmb38x_ms_resume);

अटल काष्ठा pci_driver jmb38x_ms_driver = अणु
	.name = DRIVER_NAME,
	.id_table = jmb38x_ms_id_tbl,
	.probe = jmb38x_ms_probe,
	.हटाओ = jmb38x_ms_हटाओ,
	.driver.pm = &jmb38x_ms_pm_ops,
पूर्ण;

module_pci_driver(jmb38x_ms_driver);

MODULE_AUTHOR("Alex Dubov");
MODULE_DESCRIPTION("JMicron jmb38x MemoryStick driver");
MODULE_LICENSE("GPL");
MODULE_DEVICE_TABLE(pci, jmb38x_ms_id_tbl);
