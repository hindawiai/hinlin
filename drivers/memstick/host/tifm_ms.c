<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  TI FlashMedia driver
 *
 *  Copyright (C) 2007 Alex Dubov <oakad@yahoo.com>
 *
 * Special thanks to Carlos Corbacho क्रम providing various MemoryStick cards
 * that made this driver possible.
 */

#समावेश <linux/tअगरm.h>
#समावेश <linux/memstick.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/scatterlist.h>
#समावेश <linux/log2.h>
#समावेश <linux/module.h>
#समावेश <यंत्र/पन.स>

#घोषणा DRIVER_NAME "tifm_ms"

अटल bool no_dma;
module_param(no_dma, bool, 0644);

/*
 * Some control bits of TIFM appear to conक्रमm to Sony's reference design,
 * so I'm just assuming they all are.
 */

#घोषणा TIFM_MS_STAT_DRQ     0x04000
#घोषणा TIFM_MS_STAT_MSINT   0x02000
#घोषणा TIFM_MS_STAT_RDY     0x01000
#घोषणा TIFM_MS_STAT_CRC     0x00200
#घोषणा TIFM_MS_STAT_TOE     0x00100
#घोषणा TIFM_MS_STAT_EMP     0x00020
#घोषणा TIFM_MS_STAT_FUL     0x00010
#घोषणा TIFM_MS_STAT_CED     0x00008
#घोषणा TIFM_MS_STAT_ERR     0x00004
#घोषणा TIFM_MS_STAT_BRQ     0x00002
#घोषणा TIFM_MS_STAT_CNK     0x00001

#घोषणा TIFM_MS_SYS_DMA      0x10000
#घोषणा TIFM_MS_SYS_RESET    0x08000
#घोषणा TIFM_MS_SYS_SRAC     0x04000
#घोषणा TIFM_MS_SYS_INTEN    0x02000
#घोषणा TIFM_MS_SYS_NOCRC    0x01000
#घोषणा TIFM_MS_SYS_INTCLR   0x00800
#घोषणा TIFM_MS_SYS_MSIEN    0x00400
#घोषणा TIFM_MS_SYS_FCLR     0x00200
#घोषणा TIFM_MS_SYS_Fसूची     0x00100
#घोषणा TIFM_MS_SYS_DAM      0x00080
#घोषणा TIFM_MS_SYS_DRM      0x00040
#घोषणा TIFM_MS_SYS_DRQSL    0x00020
#घोषणा TIFM_MS_SYS_REI      0x00010
#घोषणा TIFM_MS_SYS_REO      0x00008
#घोषणा TIFM_MS_SYS_BSY_MASK 0x00007

#घोषणा TIFM_MS_SYS_FIFO     (TIFM_MS_SYS_INTEN | TIFM_MS_SYS_MSIEN \
			      | TIFM_MS_SYS_FCLR | TIFM_MS_SYS_BSY_MASK)

/* Hardware flags */
क्रमागत अणु
	CMD_READY  = 0x01,
	FIFO_READY = 0x02,
	CARD_INT   = 0x04
पूर्ण;

काष्ठा tअगरm_ms अणु
	काष्ठा tअगरm_dev         *dev;
	काष्ठा समयr_list       समयr;
	काष्ठा memstick_request *req;
	काष्ठा tasklet_काष्ठा   notअगरy;
	अचिन्हित पूर्णांक            mode_mask;
	अचिन्हित पूर्णांक            block_pos;
	अचिन्हित दीर्घ           समयout_jअगरfies;
	अचिन्हित अक्षर           eject:1,
				use_dma:1;
	अचिन्हित अक्षर           cmd_flags;
	अचिन्हित अक्षर           io_pos;
	अचिन्हित पूर्णांक            io_word;
पूर्ण;

अटल अचिन्हित पूर्णांक tअगरm_ms_पढ़ो_data(काष्ठा tअगरm_ms *host,
				      अचिन्हित अक्षर *buf, अचिन्हित पूर्णांक length)
अणु
	काष्ठा tअगरm_dev *sock = host->dev;
	अचिन्हित पूर्णांक off = 0;

	जबतक (host->io_pos && length) अणु
		buf[off++] = host->io_word & 0xff;
		host->io_word >>= 8;
		length--;
		host->io_pos--;
	पूर्ण

	अगर (!length)
		वापस off;

	जबतक (!(TIFM_MS_STAT_EMP & पढ़ोl(sock->addr + SOCK_MS_STATUS))) अणु
		अगर (length < 4)
			अवरोध;
		*(अचिन्हित पूर्णांक *)(buf + off) = __raw_पढ़ोl(sock->addr
							   + SOCK_MS_DATA);
		length -= 4;
		off += 4;
	पूर्ण

	अगर (length
	    && !(TIFM_MS_STAT_EMP & पढ़ोl(sock->addr + SOCK_MS_STATUS))) अणु
		host->io_word = पढ़ोl(sock->addr + SOCK_MS_DATA);
		क्रम (host->io_pos = 4; host->io_pos; --host->io_pos) अणु
			buf[off++] = host->io_word & 0xff;
			host->io_word >>= 8;
			length--;
			अगर (!length)
				अवरोध;
		पूर्ण
	पूर्ण

	वापस off;
पूर्ण

अटल अचिन्हित पूर्णांक tअगरm_ms_ग_लिखो_data(काष्ठा tअगरm_ms *host,
				       अचिन्हित अक्षर *buf, अचिन्हित पूर्णांक length)
अणु
	काष्ठा tअगरm_dev *sock = host->dev;
	अचिन्हित पूर्णांक off = 0;

	अगर (host->io_pos) अणु
		जबतक (host->io_pos < 4 && length) अणु
			host->io_word |=  buf[off++] << (host->io_pos * 8);
			host->io_pos++;
			length--;
		पूर्ण
	पूर्ण

	अगर (host->io_pos == 4
	    && !(TIFM_MS_STAT_FUL & पढ़ोl(sock->addr + SOCK_MS_STATUS))) अणु
		ग_लिखोl(TIFM_MS_SYS_Fसूची | पढ़ोl(sock->addr + SOCK_MS_SYSTEM),
		       sock->addr + SOCK_MS_SYSTEM);
		ग_लिखोl(host->io_word, sock->addr + SOCK_MS_DATA);
		host->io_pos = 0;
		host->io_word = 0;
	पूर्ण अन्यथा अगर (host->io_pos) अणु
		वापस off;
	पूर्ण

	अगर (!length)
		वापस off;

	जबतक (!(TIFM_MS_STAT_FUL & पढ़ोl(sock->addr + SOCK_MS_STATUS))) अणु
		अगर (length < 4)
			अवरोध;
		ग_लिखोl(TIFM_MS_SYS_Fसूची | पढ़ोl(sock->addr + SOCK_MS_SYSTEM),
		       sock->addr + SOCK_MS_SYSTEM);
		__raw_ग_लिखोl(*(अचिन्हित पूर्णांक *)(buf + off),
			     sock->addr + SOCK_MS_DATA);
		length -= 4;
		off += 4;
	पूर्ण

	चयन (length) अणु
	हाल 3:
		host->io_word |= buf[off + 2] << 16;
		host->io_pos++;
		fallthrough;
	हाल 2:
		host->io_word |= buf[off + 1] << 8;
		host->io_pos++;
		fallthrough;
	हाल 1:
		host->io_word |= buf[off];
		host->io_pos++;
	पूर्ण

	off += host->io_pos;

	वापस off;
पूर्ण

अटल अचिन्हित पूर्णांक tअगरm_ms_transfer_data(काष्ठा tअगरm_ms *host)
अणु
	काष्ठा tअगरm_dev *sock = host->dev;
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
	dev_dbg(&sock->dev, "fifo data transfer, %d, %d\n", length,
		host->block_pos);

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

		t_size = host->req->data_dir == WRITE
			 ? tअगरm_ms_ग_लिखो_data(host, buf, p_cnt)
			 : tअगरm_ms_पढ़ो_data(host, buf, p_cnt);

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

	dev_dbg(&sock->dev, "fifo data transfer, %d remaining\n", length);
	अगर (!length && (host->req->data_dir == WRITE)) अणु
		अगर (host->io_pos) अणु
			ग_लिखोl(TIFM_MS_SYS_Fसूची
			       | पढ़ोl(sock->addr + SOCK_MS_SYSTEM),
			       sock->addr + SOCK_MS_SYSTEM);
			ग_लिखोl(host->io_word, sock->addr + SOCK_MS_DATA);
		पूर्ण
		ग_लिखोl(TIFM_MS_SYS_Fसूची
		       | पढ़ोl(sock->addr + SOCK_MS_SYSTEM),
		       sock->addr + SOCK_MS_SYSTEM);
		ग_लिखोl(0, sock->addr + SOCK_MS_DATA);
	पूर्ण अन्यथा अणु
		पढ़ोl(sock->addr + SOCK_MS_DATA);
	पूर्ण

	वापस length;
पूर्ण

अटल पूर्णांक tअगरm_ms_issue_cmd(काष्ठा tअगरm_ms *host)
अणु
	काष्ठा tअगरm_dev *sock = host->dev;
	अचिन्हित पूर्णांक data_len, cmd, sys_param;

	host->cmd_flags = 0;
	host->block_pos = 0;
	host->io_pos = 0;
	host->io_word = 0;
	host->cmd_flags = 0;

	host->use_dma = !no_dma;

	अगर (host->req->दीर्घ_data) अणु
		data_len = host->req->sg.length;
		अगर (!is_घातer_of_2(data_len))
			host->use_dma = 0;
	पूर्ण अन्यथा अणु
		data_len = host->req->data_len;
		host->use_dma = 0;
	पूर्ण

	ग_लिखोl(TIFM_FIFO_INT_SETALL,
	       sock->addr + SOCK_DMA_FIFO_INT_ENABLE_CLEAR);
	ग_लिखोl(TIFM_FIFO_ENABLE,
	       sock->addr + SOCK_FIFO_CONTROL);

	अगर (host->use_dma) अणु
		अगर (1 != tअगरm_map_sg(sock, &host->req->sg, 1,
				     host->req->data_dir == READ
				     ? PCI_DMA_FROMDEVICE
				     : PCI_DMA_TODEVICE)) अणु
			host->req->error = -ENOMEM;
			वापस host->req->error;
		पूर्ण
		data_len = sg_dma_len(&host->req->sg);

		ग_लिखोl(ilog2(data_len) - 2,
		       sock->addr + SOCK_FIFO_PAGE_SIZE);
		ग_लिखोl(TIFM_FIFO_INTMASK,
		       sock->addr + SOCK_DMA_FIFO_INT_ENABLE_SET);
		sys_param = TIFM_DMA_EN | (1 << 8);
		अगर (host->req->data_dir == WRITE)
			sys_param |= TIFM_DMA_TX;

		ग_लिखोl(TIFM_FIFO_INTMASK,
		       sock->addr + SOCK_DMA_FIFO_INT_ENABLE_SET);

		ग_लिखोl(sg_dma_address(&host->req->sg),
		       sock->addr + SOCK_DMA_ADDRESS);
		ग_लिखोl(sys_param, sock->addr + SOCK_DMA_CONTROL);
	पूर्ण अन्यथा अणु
		ग_लिखोl(host->mode_mask | TIFM_MS_SYS_FIFO,
		       sock->addr + SOCK_MS_SYSTEM);

		ग_लिखोl(TIFM_FIFO_MORE,
		       sock->addr + SOCK_DMA_FIFO_INT_ENABLE_SET);
	पूर्ण

	mod_समयr(&host->समयr, jअगरfies + host->समयout_jअगरfies);
	ग_लिखोl(TIFM_CTRL_LED | पढ़ोl(sock->addr + SOCK_CONTROL),
	       sock->addr + SOCK_CONTROL);
	host->req->error = 0;

	sys_param = पढ़ोl(sock->addr + SOCK_MS_SYSTEM);
	sys_param |= TIFM_MS_SYS_INTCLR;

	अगर (host->use_dma)
		sys_param |= TIFM_MS_SYS_DMA;
	अन्यथा
		sys_param &= ~TIFM_MS_SYS_DMA;

	ग_लिखोl(sys_param, sock->addr + SOCK_MS_SYSTEM);

	cmd = (host->req->tpc & 0xf) << 12;
	cmd |= data_len;
	ग_लिखोl(cmd, sock->addr + SOCK_MS_COMMAND);

	dev_dbg(&sock->dev, "executing TPC %x, %x\n", cmd, sys_param);
	वापस 0;
पूर्ण

अटल व्योम tअगरm_ms_complete_cmd(काष्ठा tअगरm_ms *host)
अणु
	काष्ठा tअगरm_dev *sock = host->dev;
	काष्ठा memstick_host *msh = tअगरm_get_drvdata(sock);
	पूर्णांक rc;

	del_समयr(&host->समयr);

	host->req->पूर्णांक_reg = पढ़ोl(sock->addr + SOCK_MS_STATUS) & 0xff;
	host->req->पूर्णांक_reg = (host->req->पूर्णांक_reg & 1)
			     | ((host->req->पूर्णांक_reg << 4) & 0xe0);

	ग_लिखोl(TIFM_FIFO_INT_SETALL,
	       sock->addr + SOCK_DMA_FIFO_INT_ENABLE_CLEAR);
	ग_लिखोl(TIFM_DMA_RESET, sock->addr + SOCK_DMA_CONTROL);

	अगर (host->use_dma) अणु
		tअगरm_unmap_sg(sock, &host->req->sg, 1,
			      host->req->data_dir == READ
			      ? PCI_DMA_FROMDEVICE
			      : PCI_DMA_TODEVICE);
	पूर्ण

	ग_लिखोl((~TIFM_CTRL_LED) & पढ़ोl(sock->addr + SOCK_CONTROL),
	       sock->addr + SOCK_CONTROL);

	dev_dbg(&sock->dev, "TPC complete\n");
	करो अणु
		rc = memstick_next_req(msh, &host->req);
	पूर्ण जबतक (!rc && tअगरm_ms_issue_cmd(host));
पूर्ण

अटल पूर्णांक tअगरm_ms_check_status(काष्ठा tअगरm_ms *host)
अणु
	अगर (!host->req->error) अणु
		अगर (!(host->cmd_flags & CMD_READY))
			वापस 1;
		अगर (!(host->cmd_flags & FIFO_READY))
			वापस 1;
		अगर (host->req->need_card_पूर्णांक
		    && !(host->cmd_flags & CARD_INT))
			वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

/* Called from पूर्णांकerrupt handler */
अटल व्योम tअगरm_ms_data_event(काष्ठा tअगरm_dev *sock)
अणु
	काष्ठा tअगरm_ms *host;
	अचिन्हित पूर्णांक fअगरo_status = 0, host_status = 0;
	पूर्णांक rc = 1;

	spin_lock(&sock->lock);
	host = memstick_priv((काष्ठा memstick_host *)tअगरm_get_drvdata(sock));
	fअगरo_status = पढ़ोl(sock->addr + SOCK_DMA_FIFO_STATUS);
	host_status = पढ़ोl(sock->addr + SOCK_MS_STATUS);
	dev_dbg(&sock->dev,
		"data event: fifo_status %x, host_status %x, flags %x\n",
		fअगरo_status, host_status, host->cmd_flags);

	अगर (host->req) अणु
		अगर (host->use_dma && (fअगरo_status & 1)) अणु
			host->cmd_flags |= FIFO_READY;
			rc = tअगरm_ms_check_status(host);
		पूर्ण
		अगर (!host->use_dma && (fअगरo_status & TIFM_FIFO_MORE)) अणु
			अगर (!tअगरm_ms_transfer_data(host)) अणु
				host->cmd_flags |= FIFO_READY;
				rc = tअगरm_ms_check_status(host);
			पूर्ण
		पूर्ण
	पूर्ण

	ग_लिखोl(fअगरo_status, sock->addr + SOCK_DMA_FIFO_STATUS);
	अगर (!rc)
		tअगरm_ms_complete_cmd(host);

	spin_unlock(&sock->lock);
पूर्ण


/* Called from पूर्णांकerrupt handler */
अटल व्योम tअगरm_ms_card_event(काष्ठा tअगरm_dev *sock)
अणु
	काष्ठा tअगरm_ms *host;
	अचिन्हित पूर्णांक host_status = 0;
	पूर्णांक rc = 1;

	spin_lock(&sock->lock);
	host = memstick_priv((काष्ठा memstick_host *)tअगरm_get_drvdata(sock));
	host_status = पढ़ोl(sock->addr + SOCK_MS_STATUS);
	dev_dbg(&sock->dev, "host event: host_status %x, flags %x\n",
		host_status, host->cmd_flags);

	अगर (host->req) अणु
		अगर (host_status & TIFM_MS_STAT_TOE)
			host->req->error = -ETIME;
		अन्यथा अगर (host_status & TIFM_MS_STAT_CRC)
			host->req->error = -EILSEQ;

		अगर (host_status & TIFM_MS_STAT_RDY)
			host->cmd_flags |= CMD_READY;

		अगर (host_status & TIFM_MS_STAT_MSINT)
			host->cmd_flags |= CARD_INT;

		rc = tअगरm_ms_check_status(host);

	पूर्ण

	ग_लिखोl(TIFM_MS_SYS_INTCLR | पढ़ोl(sock->addr + SOCK_MS_SYSTEM),
	       sock->addr + SOCK_MS_SYSTEM);

	अगर (!rc)
		tअगरm_ms_complete_cmd(host);

	spin_unlock(&sock->lock);
	वापस;
पूर्ण

अटल व्योम tअगरm_ms_req_tasklet(अचिन्हित दीर्घ data)
अणु
	काष्ठा memstick_host *msh = (काष्ठा memstick_host *)data;
	काष्ठा tअगरm_ms *host = memstick_priv(msh);
	काष्ठा tअगरm_dev *sock = host->dev;
	अचिन्हित दीर्घ flags;
	पूर्णांक rc;

	spin_lock_irqsave(&sock->lock, flags);
	अगर (!host->req) अणु
		अगर (host->eject) अणु
			करो अणु
				rc = memstick_next_req(msh, &host->req);
				अगर (!rc)
					host->req->error = -ETIME;
			पूर्ण जबतक (!rc);
			spin_unlock_irqrestore(&sock->lock, flags);
			वापस;
		पूर्ण

		करो अणु
			rc = memstick_next_req(msh, &host->req);
		पूर्ण जबतक (!rc && tअगरm_ms_issue_cmd(host));
	पूर्ण
	spin_unlock_irqrestore(&sock->lock, flags);
पूर्ण

अटल व्योम tअगरm_ms_dummy_submit(काष्ठा memstick_host *msh)
अणु
	वापस;
पूर्ण

अटल व्योम tअगरm_ms_submit_req(काष्ठा memstick_host *msh)
अणु
	काष्ठा tअगरm_ms *host = memstick_priv(msh);

	tasklet_schedule(&host->notअगरy);
पूर्ण

अटल पूर्णांक tअगरm_ms_set_param(काष्ठा memstick_host *msh,
			     क्रमागत memstick_param param,
			     पूर्णांक value)
अणु
	काष्ठा tअगरm_ms *host = memstick_priv(msh);
	काष्ठा tअगरm_dev *sock = host->dev;

	चयन (param) अणु
	हाल MEMSTICK_POWER:
		/* also affected by media detection mechanism */
		अगर (value == MEMSTICK_POWER_ON) अणु
			host->mode_mask = TIFM_MS_SYS_SRAC | TIFM_MS_SYS_REI;
			ग_लिखोl(TIFM_MS_SYS_RESET, sock->addr + SOCK_MS_SYSTEM);
			ग_लिखोl(TIFM_MS_SYS_FCLR | TIFM_MS_SYS_INTCLR,
			       sock->addr + SOCK_MS_SYSTEM);
			ग_लिखोl(0xffffffff, sock->addr + SOCK_MS_STATUS);
		पूर्ण अन्यथा अगर (value == MEMSTICK_POWER_OFF) अणु
			ग_लिखोl(TIFM_MS_SYS_FCLR | TIFM_MS_SYS_INTCLR,
			       sock->addr + SOCK_MS_SYSTEM);
			ग_लिखोl(0xffffffff, sock->addr + SOCK_MS_STATUS);
		पूर्ण अन्यथा
			वापस -EINVAL;
		अवरोध;
	हाल MEMSTICK_INTERFACE:
		अगर (value == MEMSTICK_SERIAL) अणु
			host->mode_mask = TIFM_MS_SYS_SRAC | TIFM_MS_SYS_REI;
			ग_लिखोl((~TIFM_CTRL_FAST_CLK)
			       & पढ़ोl(sock->addr + SOCK_CONTROL),
			       sock->addr + SOCK_CONTROL);
		पूर्ण अन्यथा अगर (value == MEMSTICK_PAR4) अणु
			host->mode_mask = 0;
			ग_लिखोl(TIFM_CTRL_FAST_CLK
			       | पढ़ोl(sock->addr + SOCK_CONTROL),
			       sock->addr + SOCK_CONTROL);
		पूर्ण अन्यथा
			वापस -EINVAL;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम tअगरm_ms_पात(काष्ठा समयr_list *t)
अणु
	काष्ठा tअगरm_ms *host = from_समयr(host, t, समयr);

	dev_dbg(&host->dev->dev, "status %x\n",
		पढ़ोl(host->dev->addr + SOCK_MS_STATUS));
	prपूर्णांकk(KERN_ERR
	       "%s : card failed to respond for a long period of time "
	       "(%x, %x)\n",
	       dev_name(&host->dev->dev), host->req ? host->req->tpc : 0,
	       host->cmd_flags);

	tअगरm_eject(host->dev);
पूर्ण

अटल पूर्णांक tअगरm_ms_probe(काष्ठा tअगरm_dev *sock)
अणु
	काष्ठा memstick_host *msh;
	काष्ठा tअगरm_ms *host;
	पूर्णांक rc = -EIO;

	अगर (!(TIFM_SOCK_STATE_OCCUPIED
	      & पढ़ोl(sock->addr + SOCK_PRESENT_STATE))) अणु
		prपूर्णांकk(KERN_WARNING "%s : card gone, unexpectedly\n",
		       dev_name(&sock->dev));
		वापस rc;
	पूर्ण

	msh = memstick_alloc_host(माप(काष्ठा tअगरm_ms), &sock->dev);
	अगर (!msh)
		वापस -ENOMEM;

	host = memstick_priv(msh);
	tअगरm_set_drvdata(sock, msh);
	host->dev = sock;
	host->समयout_jअगरfies = msecs_to_jअगरfies(1000);

	समयr_setup(&host->समयr, tअगरm_ms_पात, 0);
	tasklet_init(&host->notअगरy, tअगरm_ms_req_tasklet, (अचिन्हित दीर्घ)msh);

	msh->request = tअगरm_ms_submit_req;
	msh->set_param = tअगरm_ms_set_param;
	sock->card_event = tअगरm_ms_card_event;
	sock->data_event = tअगरm_ms_data_event;
	अगर (tअगरm_has_ms_pअगर(sock))
		msh->caps |= MEMSTICK_CAP_PAR4;

	rc = memstick_add_host(msh);
	अगर (!rc)
		वापस 0;

	memstick_मुक्त_host(msh);
	वापस rc;
पूर्ण

अटल व्योम tअगरm_ms_हटाओ(काष्ठा tअगरm_dev *sock)
अणु
	काष्ठा memstick_host *msh = tअगरm_get_drvdata(sock);
	काष्ठा tअगरm_ms *host = memstick_priv(msh);
	पूर्णांक rc = 0;
	अचिन्हित दीर्घ flags;

	msh->request = tअगरm_ms_dummy_submit;
	tasklet_समाप्त(&host->notअगरy);
	spin_lock_irqsave(&sock->lock, flags);
	host->eject = 1;
	अगर (host->req) अणु
		del_समयr(&host->समयr);
		ग_लिखोl(TIFM_FIFO_INT_SETALL,
		       sock->addr + SOCK_DMA_FIFO_INT_ENABLE_CLEAR);
		ग_लिखोl(TIFM_DMA_RESET, sock->addr + SOCK_DMA_CONTROL);
		अगर (host->use_dma)
			tअगरm_unmap_sg(sock, &host->req->sg, 1,
				      host->req->data_dir == READ
				      ? PCI_DMA_TODEVICE
				      : PCI_DMA_FROMDEVICE);
		host->req->error = -ETIME;

		करो अणु
			rc = memstick_next_req(msh, &host->req);
			अगर (!rc)
				host->req->error = -ETIME;
		पूर्ण जबतक (!rc);
	पूर्ण
	spin_unlock_irqrestore(&sock->lock, flags);

	memstick_हटाओ_host(msh);
	memstick_मुक्त_host(msh);
पूर्ण

#अगर_घोषित CONFIG_PM

अटल पूर्णांक tअगरm_ms_suspend(काष्ठा tअगरm_dev *sock, pm_message_t state)
अणु
	काष्ठा memstick_host *msh = tअगरm_get_drvdata(sock);

	memstick_suspend_host(msh);
	वापस 0;
पूर्ण

अटल पूर्णांक tअगरm_ms_resume(काष्ठा tअगरm_dev *sock)
अणु
	काष्ठा memstick_host *msh = tअगरm_get_drvdata(sock);

	memstick_resume_host(msh);
	वापस 0;
पूर्ण

#अन्यथा

#घोषणा tअगरm_ms_suspend शून्य
#घोषणा tअगरm_ms_resume शून्य

#पूर्ण_अगर /* CONFIG_PM */

अटल काष्ठा tअगरm_device_id tअगरm_ms_id_tbl[] = अणु
	अणु TIFM_TYPE_MS पूर्ण, अणु 0 पूर्ण
पूर्ण;

अटल काष्ठा tअगरm_driver tअगरm_ms_driver = अणु
	.driver = अणु
		.name  = DRIVER_NAME,
		.owner = THIS_MODULE
	पूर्ण,
	.id_table = tअगरm_ms_id_tbl,
	.probe    = tअगरm_ms_probe,
	.हटाओ   = tअगरm_ms_हटाओ,
	.suspend  = tअगरm_ms_suspend,
	.resume   = tअगरm_ms_resume
पूर्ण;

अटल पूर्णांक __init tअगरm_ms_init(व्योम)
अणु
	वापस tअगरm_रेजिस्टर_driver(&tअगरm_ms_driver);
पूर्ण

अटल व्योम __निकास tअगरm_ms_निकास(व्योम)
अणु
	tअगरm_unरेजिस्टर_driver(&tअगरm_ms_driver);
पूर्ण

MODULE_AUTHOR("Alex Dubov");
MODULE_DESCRIPTION("TI FlashMedia MemoryStick driver");
MODULE_LICENSE("GPL");
MODULE_DEVICE_TABLE(tअगरm, tअगरm_ms_id_tbl);

module_init(tअगरm_ms_init);
module_निकास(tअगरm_ms_निकास);
