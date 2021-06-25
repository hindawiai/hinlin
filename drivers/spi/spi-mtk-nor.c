<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Mediatek SPI NOR controller driver
//
// Copyright (C) 2020 Chuanhong Guo <gch981213@gmail.com>

#समावेश <linux/bits.h>
#समावेश <linux/clk.h>
#समावेश <linux/completion.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/spi/spi.h>
#समावेश <linux/spi/spi-स्मृति.स>
#समावेश <linux/माला.स>

#घोषणा DRIVER_NAME "mtk-spi-nor"

#घोषणा MTK_NOR_REG_CMD			0x00
#घोषणा MTK_NOR_CMD_WRITE		BIT(4)
#घोषणा MTK_NOR_CMD_PROGRAM		BIT(2)
#घोषणा MTK_NOR_CMD_READ		BIT(0)
#घोषणा MTK_NOR_CMD_MASK		GENMASK(5, 0)

#घोषणा MTK_NOR_REG_PRG_CNT		0x04
#घोषणा MTK_NOR_PRG_CNT_MAX		56
#घोषणा MTK_NOR_REG_RDATA		0x0c

#घोषणा MTK_NOR_REG_RADR0		0x10
#घोषणा MTK_NOR_REG_RADR(n)		(MTK_NOR_REG_RADR0 + 4 * (n))
#घोषणा MTK_NOR_REG_RADR3		0xc8

#घोषणा MTK_NOR_REG_WDATA		0x1c

#घोषणा MTK_NOR_REG_PRGDATA0		0x20
#घोषणा MTK_NOR_REG_PRGDATA(n)		(MTK_NOR_REG_PRGDATA0 + 4 * (n))
#घोषणा MTK_NOR_REG_PRGDATA_MAX		5

#घोषणा MTK_NOR_REG_SHIFT0		0x38
#घोषणा MTK_NOR_REG_SHIFT(n)		(MTK_NOR_REG_SHIFT0 + 4 * (n))
#घोषणा MTK_NOR_REG_SHIFT_MAX		9

#घोषणा MTK_NOR_REG_CFG1		0x60
#घोषणा MTK_NOR_FAST_READ		BIT(0)

#घोषणा MTK_NOR_REG_CFG2		0x64
#घोषणा MTK_NOR_WR_CUSTOM_OP_EN		BIT(4)
#घोषणा MTK_NOR_WR_BUF_EN		BIT(0)

#घोषणा MTK_NOR_REG_PP_DATA		0x98

#घोषणा MTK_NOR_REG_IRQ_STAT		0xa8
#घोषणा MTK_NOR_REG_IRQ_EN		0xac
#घोषणा MTK_NOR_IRQ_DMA			BIT(7)
#घोषणा MTK_NOR_IRQ_MASK		GENMASK(7, 0)

#घोषणा MTK_NOR_REG_CFG3		0xb4
#घोषणा MTK_NOR_DISABLE_WREN		BIT(7)
#घोषणा MTK_NOR_DISABLE_SR_POLL		BIT(5)

#घोषणा MTK_NOR_REG_WP			0xc4
#घोषणा MTK_NOR_ENABLE_SF_CMD		0x30

#घोषणा MTK_NOR_REG_BUSCFG		0xcc
#घोषणा MTK_NOR_4B_ADDR			BIT(4)
#घोषणा MTK_NOR_QUAD_ADDR		BIT(3)
#घोषणा MTK_NOR_QUAD_READ		BIT(2)
#घोषणा MTK_NOR_DUAL_ADDR		BIT(1)
#घोषणा MTK_NOR_DUAL_READ		BIT(0)
#घोषणा MTK_NOR_BUS_MODE_MASK		GENMASK(4, 0)

#घोषणा MTK_NOR_REG_DMA_CTL		0x718
#घोषणा MTK_NOR_DMA_START		BIT(0)

#घोषणा MTK_NOR_REG_DMA_FADR		0x71c
#घोषणा MTK_NOR_REG_DMA_DADR		0x720
#घोषणा MTK_NOR_REG_DMA_END_DADR	0x724
#घोषणा MTK_NOR_REG_DMA_DADR_HB		0x738
#घोषणा MTK_NOR_REG_DMA_END_DADR_HB	0x73c

#घोषणा MTK_NOR_PRG_MAX_SIZE		6
// Reading DMA src/dst addresses have to be 16-byte aligned
#घोषणा MTK_NOR_DMA_ALIGN		16
#घोषणा MTK_NOR_DMA_ALIGN_MASK		(MTK_NOR_DMA_ALIGN - 1)
// and we allocate a bounce buffer अगर destination address isn't aligned.
#घोषणा MTK_NOR_BOUNCE_BUF_SIZE		PAGE_SIZE

// Buffered page program can करो one 128-byte transfer
#घोषणा MTK_NOR_PP_SIZE			128

#घोषणा CLK_TO_US(sp, clkcnt)		DIV_ROUND_UP(clkcnt, sp->spi_freq / 1000000)

काष्ठा mtk_nor अणु
	काष्ठा spi_controller *ctlr;
	काष्ठा device *dev;
	व्योम __iomem *base;
	u8 *buffer;
	dma_addr_t buffer_dma;
	काष्ठा clk *spi_clk;
	काष्ठा clk *ctlr_clk;
	काष्ठा clk *axi_clk;
	अचिन्हित पूर्णांक spi_freq;
	bool wbuf_en;
	bool has_irq;
	bool high_dma;
	काष्ठा completion op_करोne;
पूर्ण;

अटल अंतरभूत व्योम mtk_nor_rmw(काष्ठा mtk_nor *sp, u32 reg, u32 set, u32 clr)
अणु
	u32 val = पढ़ोl(sp->base + reg);

	val &= ~clr;
	val |= set;
	ग_लिखोl(val, sp->base + reg);
पूर्ण

अटल अंतरभूत पूर्णांक mtk_nor_cmd_exec(काष्ठा mtk_nor *sp, u32 cmd, uदीर्घ clk)
अणु
	uदीर्घ delay = CLK_TO_US(sp, clk);
	u32 reg;
	पूर्णांक ret;

	ग_लिखोl(cmd, sp->base + MTK_NOR_REG_CMD);
	ret = पढ़ोl_poll_समयout(sp->base + MTK_NOR_REG_CMD, reg, !(reg & cmd),
				 delay / 3, (delay + 1) * 200);
	अगर (ret < 0)
		dev_err(sp->dev, "command %u timeout.\n", cmd);
	वापस ret;
पूर्ण

अटल व्योम mtk_nor_set_addr(काष्ठा mtk_nor *sp, स्थिर काष्ठा spi_mem_op *op)
अणु
	u32 addr = op->addr.val;
	पूर्णांक i;

	क्रम (i = 0; i < 3; i++) अणु
		ग_लिखोb(addr & 0xff, sp->base + MTK_NOR_REG_RADR(i));
		addr >>= 8;
	पूर्ण
	अगर (op->addr.nbytes == 4) अणु
		ग_लिखोb(addr & 0xff, sp->base + MTK_NOR_REG_RADR3);
		mtk_nor_rmw(sp, MTK_NOR_REG_BUSCFG, MTK_NOR_4B_ADDR, 0);
	पूर्ण अन्यथा अणु
		mtk_nor_rmw(sp, MTK_NOR_REG_BUSCFG, 0, MTK_NOR_4B_ADDR);
	पूर्ण
पूर्ण

अटल bool need_bounce(काष्ठा mtk_nor *sp, स्थिर काष्ठा spi_mem_op *op)
अणु
	वापस ((uपूर्णांकptr_t)op->data.buf.in & MTK_NOR_DMA_ALIGN_MASK);
पूर्ण

अटल bool mtk_nor_match_पढ़ो(स्थिर काष्ठा spi_mem_op *op)
अणु
	पूर्णांक dummy = 0;

	अगर (op->dummy.buswidth)
		dummy = op->dummy.nbytes * BITS_PER_BYTE / op->dummy.buswidth;

	अगर ((op->data.buswidth == 2) || (op->data.buswidth == 4)) अणु
		अगर (op->addr.buswidth == 1)
			वापस dummy == 8;
		अन्यथा अगर (op->addr.buswidth == 2)
			वापस dummy == 4;
		अन्यथा अगर (op->addr.buswidth == 4)
			वापस dummy == 6;
	पूर्ण अन्यथा अगर ((op->addr.buswidth == 1) && (op->data.buswidth == 1)) अणु
		अगर (op->cmd.opcode == 0x03)
			वापस dummy == 0;
		अन्यथा अगर (op->cmd.opcode == 0x0b)
			वापस dummy == 8;
	पूर्ण
	वापस false;
पूर्ण

अटल bool mtk_nor_match_prg(स्थिर काष्ठा spi_mem_op *op)
अणु
	पूर्णांक tx_len, rx_len, prg_len, prg_left;

	// prg mode is spi-only.
	अगर ((op->cmd.buswidth > 1) || (op->addr.buswidth > 1) ||
	    (op->dummy.buswidth > 1) || (op->data.buswidth > 1))
		वापस false;

	tx_len = op->cmd.nbytes + op->addr.nbytes;

	अगर (op->data.dir == SPI_MEM_DATA_OUT) अणु
		// count dummy bytes only अगर we need to ग_लिखो data after it
		tx_len += op->dummy.nbytes;

		// leave at least one byte क्रम data
		अगर (tx_len > MTK_NOR_REG_PRGDATA_MAX)
			वापस false;

		// अगर there's no addr, meaning adjust_op_size is impossible,
		// check data length as well.
		अगर ((!op->addr.nbytes) &&
		    (tx_len + op->data.nbytes > MTK_NOR_REG_PRGDATA_MAX + 1))
			वापस false;
	पूर्ण अन्यथा अगर (op->data.dir == SPI_MEM_DATA_IN) अणु
		अगर (tx_len > MTK_NOR_REG_PRGDATA_MAX + 1)
			वापस false;

		rx_len = op->data.nbytes;
		prg_left = MTK_NOR_PRG_CNT_MAX / 8 - tx_len - op->dummy.nbytes;
		अगर (prg_left > MTK_NOR_REG_SHIFT_MAX + 1)
			prg_left = MTK_NOR_REG_SHIFT_MAX + 1;
		अगर (rx_len > prg_left) अणु
			अगर (!op->addr.nbytes)
				वापस false;
			rx_len = prg_left;
		पूर्ण

		prg_len = tx_len + op->dummy.nbytes + rx_len;
		अगर (prg_len > MTK_NOR_PRG_CNT_MAX / 8)
			वापस false;
	पूर्ण अन्यथा अणु
		prg_len = tx_len + op->dummy.nbytes;
		अगर (prg_len > MTK_NOR_PRG_CNT_MAX / 8)
			वापस false;
	पूर्ण
	वापस true;
पूर्ण

अटल व्योम mtk_nor_adj_prg_size(काष्ठा spi_mem_op *op)
अणु
	पूर्णांक tx_len, tx_left, prg_left;

	tx_len = op->cmd.nbytes + op->addr.nbytes;
	अगर (op->data.dir == SPI_MEM_DATA_OUT) अणु
		tx_len += op->dummy.nbytes;
		tx_left = MTK_NOR_REG_PRGDATA_MAX + 1 - tx_len;
		अगर (op->data.nbytes > tx_left)
			op->data.nbytes = tx_left;
	पूर्ण अन्यथा अगर (op->data.dir == SPI_MEM_DATA_IN) अणु
		prg_left = MTK_NOR_PRG_CNT_MAX / 8 - tx_len - op->dummy.nbytes;
		अगर (prg_left > MTK_NOR_REG_SHIFT_MAX + 1)
			prg_left = MTK_NOR_REG_SHIFT_MAX + 1;
		अगर (op->data.nbytes > prg_left)
			op->data.nbytes = prg_left;
	पूर्ण
पूर्ण

अटल पूर्णांक mtk_nor_adjust_op_size(काष्ठा spi_mem *mem, काष्ठा spi_mem_op *op)
अणु
	काष्ठा mtk_nor *sp = spi_controller_get_devdata(mem->spi->master);

	अगर (!op->data.nbytes)
		वापस 0;

	अगर ((op->addr.nbytes == 3) || (op->addr.nbytes == 4)) अणु
		अगर ((op->data.dir == SPI_MEM_DATA_IN) &&
		    mtk_nor_match_पढ़ो(op)) अणु
			// limit size to prevent समयout calculation overflow
			अगर (op->data.nbytes > 0x400000)
				op->data.nbytes = 0x400000;

			अगर ((op->addr.val & MTK_NOR_DMA_ALIGN_MASK) ||
			    (op->data.nbytes < MTK_NOR_DMA_ALIGN))
				op->data.nbytes = 1;
			अन्यथा अगर (!need_bounce(sp, op))
				op->data.nbytes &= ~MTK_NOR_DMA_ALIGN_MASK;
			अन्यथा अगर (op->data.nbytes > MTK_NOR_BOUNCE_BUF_SIZE)
				op->data.nbytes = MTK_NOR_BOUNCE_BUF_SIZE;
			वापस 0;
		पूर्ण अन्यथा अगर (op->data.dir == SPI_MEM_DATA_OUT) अणु
			अगर (op->data.nbytes >= MTK_NOR_PP_SIZE)
				op->data.nbytes = MTK_NOR_PP_SIZE;
			अन्यथा
				op->data.nbytes = 1;
			वापस 0;
		पूर्ण
	पूर्ण

	mtk_nor_adj_prg_size(op);
	वापस 0;
पूर्ण

अटल bool mtk_nor_supports_op(काष्ठा spi_mem *mem,
				स्थिर काष्ठा spi_mem_op *op)
अणु
	अगर (!spi_mem_शेष_supports_op(mem, op))
		वापस false;

	अगर (op->cmd.buswidth != 1)
		वापस false;

	अगर ((op->addr.nbytes == 3) || (op->addr.nbytes == 4)) अणु
		चयन (op->data.dir) अणु
		हाल SPI_MEM_DATA_IN:
			अगर (mtk_nor_match_पढ़ो(op))
				वापस true;
			अवरोध;
		हाल SPI_MEM_DATA_OUT:
			अगर ((op->addr.buswidth == 1) &&
			    (op->dummy.nbytes == 0) &&
			    (op->data.buswidth == 1))
				वापस true;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	वापस mtk_nor_match_prg(op);
पूर्ण

अटल व्योम mtk_nor_setup_bus(काष्ठा mtk_nor *sp, स्थिर काष्ठा spi_mem_op *op)
अणु
	u32 reg = 0;

	अगर (op->addr.nbytes == 4)
		reg |= MTK_NOR_4B_ADDR;

	अगर (op->data.buswidth == 4) अणु
		reg |= MTK_NOR_QUAD_READ;
		ग_लिखोb(op->cmd.opcode, sp->base + MTK_NOR_REG_PRGDATA(4));
		अगर (op->addr.buswidth == 4)
			reg |= MTK_NOR_QUAD_ADDR;
	पूर्ण अन्यथा अगर (op->data.buswidth == 2) अणु
		reg |= MTK_NOR_DUAL_READ;
		ग_लिखोb(op->cmd.opcode, sp->base + MTK_NOR_REG_PRGDATA(3));
		अगर (op->addr.buswidth == 2)
			reg |= MTK_NOR_DUAL_ADDR;
	पूर्ण अन्यथा अणु
		अगर (op->cmd.opcode == 0x0b)
			mtk_nor_rmw(sp, MTK_NOR_REG_CFG1, MTK_NOR_FAST_READ, 0);
		अन्यथा
			mtk_nor_rmw(sp, MTK_NOR_REG_CFG1, 0, MTK_NOR_FAST_READ);
	पूर्ण
	mtk_nor_rmw(sp, MTK_NOR_REG_BUSCFG, reg, MTK_NOR_BUS_MODE_MASK);
पूर्ण

अटल पूर्णांक mtk_nor_dma_exec(काष्ठा mtk_nor *sp, u32 from, अचिन्हित पूर्णांक length,
			    dma_addr_t dma_addr)
अणु
	पूर्णांक ret = 0;
	uदीर्घ delay;
	u32 reg;

	ग_लिखोl(from, sp->base + MTK_NOR_REG_DMA_FADR);
	ग_लिखोl(dma_addr, sp->base + MTK_NOR_REG_DMA_DADR);
	ग_लिखोl(dma_addr + length, sp->base + MTK_NOR_REG_DMA_END_DADR);

	अगर (sp->high_dma) अणु
		ग_लिखोl(upper_32_bits(dma_addr),
		       sp->base + MTK_NOR_REG_DMA_DADR_HB);
		ग_लिखोl(upper_32_bits(dma_addr + length),
		       sp->base + MTK_NOR_REG_DMA_END_DADR_HB);
	पूर्ण

	अगर (sp->has_irq) अणु
		reinit_completion(&sp->op_करोne);
		mtk_nor_rmw(sp, MTK_NOR_REG_IRQ_EN, MTK_NOR_IRQ_DMA, 0);
	पूर्ण

	mtk_nor_rmw(sp, MTK_NOR_REG_DMA_CTL, MTK_NOR_DMA_START, 0);

	delay = CLK_TO_US(sp, (length + 5) * BITS_PER_BYTE);

	अगर (sp->has_irq) अणु
		अगर (!रुको_क्रम_completion_समयout(&sp->op_करोne,
						 (delay + 1) * 100))
			ret = -ETIMEDOUT;
	पूर्ण अन्यथा अणु
		ret = पढ़ोl_poll_समयout(sp->base + MTK_NOR_REG_DMA_CTL, reg,
					 !(reg & MTK_NOR_DMA_START), delay / 3,
					 (delay + 1) * 100);
	पूर्ण

	अगर (ret < 0)
		dev_err(sp->dev, "dma read timeout.\n");

	वापस ret;
पूर्ण

अटल पूर्णांक mtk_nor_पढ़ो_bounce(काष्ठा mtk_nor *sp, स्थिर काष्ठा spi_mem_op *op)
अणु
	अचिन्हित पूर्णांक rdlen;
	पूर्णांक ret;

	अगर (op->data.nbytes & MTK_NOR_DMA_ALIGN_MASK)
		rdlen = (op->data.nbytes + MTK_NOR_DMA_ALIGN) & ~MTK_NOR_DMA_ALIGN_MASK;
	अन्यथा
		rdlen = op->data.nbytes;

	ret = mtk_nor_dma_exec(sp, op->addr.val, rdlen, sp->buffer_dma);

	अगर (!ret)
		स_नकल(op->data.buf.in, sp->buffer, op->data.nbytes);

	वापस ret;
पूर्ण

अटल पूर्णांक mtk_nor_पढ़ो_dma(काष्ठा mtk_nor *sp, स्थिर काष्ठा spi_mem_op *op)
अणु
	पूर्णांक ret;
	dma_addr_t dma_addr;

	अगर (need_bounce(sp, op))
		वापस mtk_nor_पढ़ो_bounce(sp, op);

	dma_addr = dma_map_single(sp->dev, op->data.buf.in,
				  op->data.nbytes, DMA_FROM_DEVICE);

	अगर (dma_mapping_error(sp->dev, dma_addr))
		वापस -EINVAL;

	ret = mtk_nor_dma_exec(sp, op->addr.val, op->data.nbytes, dma_addr);

	dma_unmap_single(sp->dev, dma_addr, op->data.nbytes, DMA_FROM_DEVICE);

	वापस ret;
पूर्ण

अटल पूर्णांक mtk_nor_पढ़ो_pio(काष्ठा mtk_nor *sp, स्थिर काष्ठा spi_mem_op *op)
अणु
	u8 *buf = op->data.buf.in;
	पूर्णांक ret;

	ret = mtk_nor_cmd_exec(sp, MTK_NOR_CMD_READ, 6 * BITS_PER_BYTE);
	अगर (!ret)
		buf[0] = पढ़ोb(sp->base + MTK_NOR_REG_RDATA);
	वापस ret;
पूर्ण

अटल पूर्णांक mtk_nor_ग_लिखो_buffer_enable(काष्ठा mtk_nor *sp)
अणु
	पूर्णांक ret;
	u32 val;

	अगर (sp->wbuf_en)
		वापस 0;

	val = पढ़ोl(sp->base + MTK_NOR_REG_CFG2);
	ग_लिखोl(val | MTK_NOR_WR_BUF_EN, sp->base + MTK_NOR_REG_CFG2);
	ret = पढ़ोl_poll_समयout(sp->base + MTK_NOR_REG_CFG2, val,
				 val & MTK_NOR_WR_BUF_EN, 0, 10000);
	अगर (!ret)
		sp->wbuf_en = true;
	वापस ret;
पूर्ण

अटल पूर्णांक mtk_nor_ग_लिखो_buffer_disable(काष्ठा mtk_nor *sp)
अणु
	पूर्णांक ret;
	u32 val;

	अगर (!sp->wbuf_en)
		वापस 0;
	val = पढ़ोl(sp->base + MTK_NOR_REG_CFG2);
	ग_लिखोl(val & ~MTK_NOR_WR_BUF_EN, sp->base + MTK_NOR_REG_CFG2);
	ret = पढ़ोl_poll_समयout(sp->base + MTK_NOR_REG_CFG2, val,
				 !(val & MTK_NOR_WR_BUF_EN), 0, 10000);
	अगर (!ret)
		sp->wbuf_en = false;
	वापस ret;
पूर्ण

अटल पूर्णांक mtk_nor_pp_buffered(काष्ठा mtk_nor *sp, स्थिर काष्ठा spi_mem_op *op)
अणु
	स्थिर u8 *buf = op->data.buf.out;
	u32 val;
	पूर्णांक ret, i;

	ret = mtk_nor_ग_लिखो_buffer_enable(sp);
	अगर (ret < 0)
		वापस ret;

	क्रम (i = 0; i < op->data.nbytes; i += 4) अणु
		val = buf[i + 3] << 24 | buf[i + 2] << 16 | buf[i + 1] << 8 |
		      buf[i];
		ग_लिखोl(val, sp->base + MTK_NOR_REG_PP_DATA);
	पूर्ण
	वापस mtk_nor_cmd_exec(sp, MTK_NOR_CMD_WRITE,
				(op->data.nbytes + 5) * BITS_PER_BYTE);
पूर्ण

अटल पूर्णांक mtk_nor_pp_unbuffered(काष्ठा mtk_nor *sp,
				 स्थिर काष्ठा spi_mem_op *op)
अणु
	स्थिर u8 *buf = op->data.buf.out;
	पूर्णांक ret;

	ret = mtk_nor_ग_लिखो_buffer_disable(sp);
	अगर (ret < 0)
		वापस ret;
	ग_लिखोb(buf[0], sp->base + MTK_NOR_REG_WDATA);
	वापस mtk_nor_cmd_exec(sp, MTK_NOR_CMD_WRITE, 6 * BITS_PER_BYTE);
पूर्ण

अटल पूर्णांक mtk_nor_spi_mem_prg(काष्ठा mtk_nor *sp, स्थिर काष्ठा spi_mem_op *op)
अणु
	पूर्णांक rx_len = 0;
	पूर्णांक reg_offset = MTK_NOR_REG_PRGDATA_MAX;
	पूर्णांक tx_len, prg_len;
	पूर्णांक i, ret;
	व्योम __iomem *reg;
	u8 bufbyte;

	tx_len = op->cmd.nbytes + op->addr.nbytes;

	// count dummy bytes only अगर we need to ग_लिखो data after it
	अगर (op->data.dir == SPI_MEM_DATA_OUT)
		tx_len += op->dummy.nbytes + op->data.nbytes;
	अन्यथा अगर (op->data.dir == SPI_MEM_DATA_IN)
		rx_len = op->data.nbytes;

	prg_len = op->cmd.nbytes + op->addr.nbytes + op->dummy.nbytes +
		  op->data.nbytes;

	// an invalid op may reach here अगर the caller calls exec_op without
	// adjust_op_size. वापस -EINVAL instead of -ENOTSUPP so that
	// spi-mem won't try this op again with generic spi transfers.
	अगर ((tx_len > MTK_NOR_REG_PRGDATA_MAX + 1) ||
	    (rx_len > MTK_NOR_REG_SHIFT_MAX + 1) ||
	    (prg_len > MTK_NOR_PRG_CNT_MAX / 8))
		वापस -EINVAL;

	// fill tx data
	क्रम (i = op->cmd.nbytes; i > 0; i--, reg_offset--) अणु
		reg = sp->base + MTK_NOR_REG_PRGDATA(reg_offset);
		bufbyte = (op->cmd.opcode >> ((i - 1) * BITS_PER_BYTE)) & 0xff;
		ग_लिखोb(bufbyte, reg);
	पूर्ण

	क्रम (i = op->addr.nbytes; i > 0; i--, reg_offset--) अणु
		reg = sp->base + MTK_NOR_REG_PRGDATA(reg_offset);
		bufbyte = (op->addr.val >> ((i - 1) * BITS_PER_BYTE)) & 0xff;
		ग_लिखोb(bufbyte, reg);
	पूर्ण

	अगर (op->data.dir == SPI_MEM_DATA_OUT) अणु
		क्रम (i = 0; i < op->dummy.nbytes; i++, reg_offset--) अणु
			reg = sp->base + MTK_NOR_REG_PRGDATA(reg_offset);
			ग_लिखोb(0, reg);
		पूर्ण

		क्रम (i = 0; i < op->data.nbytes; i++, reg_offset--) अणु
			reg = sp->base + MTK_NOR_REG_PRGDATA(reg_offset);
			ग_लिखोb(((स्थिर u8 *)(op->data.buf.out))[i], reg);
		पूर्ण
	पूर्ण

	क्रम (; reg_offset >= 0; reg_offset--) अणु
		reg = sp->base + MTK_NOR_REG_PRGDATA(reg_offset);
		ग_लिखोb(0, reg);
	पूर्ण

	// trigger op
	ग_लिखोl(prg_len * BITS_PER_BYTE, sp->base + MTK_NOR_REG_PRG_CNT);
	ret = mtk_nor_cmd_exec(sp, MTK_NOR_CMD_PROGRAM,
			       prg_len * BITS_PER_BYTE);
	अगर (ret)
		वापस ret;

	// fetch पढ़ो data
	reg_offset = 0;
	अगर (op->data.dir == SPI_MEM_DATA_IN) अणु
		क्रम (i = op->data.nbytes - 1; i >= 0; i--, reg_offset++) अणु
			reg = sp->base + MTK_NOR_REG_SHIFT(reg_offset);
			((u8 *)(op->data.buf.in))[i] = पढ़ोb(reg);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mtk_nor_exec_op(काष्ठा spi_mem *mem, स्थिर काष्ठा spi_mem_op *op)
अणु
	काष्ठा mtk_nor *sp = spi_controller_get_devdata(mem->spi->master);
	पूर्णांक ret;

	अगर ((op->data.nbytes == 0) ||
	    ((op->addr.nbytes != 3) && (op->addr.nbytes != 4)))
		वापस mtk_nor_spi_mem_prg(sp, op);

	अगर (op->data.dir == SPI_MEM_DATA_OUT) अणु
		mtk_nor_set_addr(sp, op);
		ग_लिखोb(op->cmd.opcode, sp->base + MTK_NOR_REG_PRGDATA0);
		अगर (op->data.nbytes == MTK_NOR_PP_SIZE)
			वापस mtk_nor_pp_buffered(sp, op);
		वापस mtk_nor_pp_unbuffered(sp, op);
	पूर्ण

	अगर ((op->data.dir == SPI_MEM_DATA_IN) && mtk_nor_match_पढ़ो(op)) अणु
		ret = mtk_nor_ग_लिखो_buffer_disable(sp);
		अगर (ret < 0)
			वापस ret;
		mtk_nor_setup_bus(sp, op);
		अगर (op->data.nbytes == 1) अणु
			mtk_nor_set_addr(sp, op);
			वापस mtk_nor_पढ़ो_pio(sp, op);
		पूर्ण अन्यथा अणु
			वापस mtk_nor_पढ़ो_dma(sp, op);
		पूर्ण
	पूर्ण

	वापस mtk_nor_spi_mem_prg(sp, op);
पूर्ण

अटल पूर्णांक mtk_nor_setup(काष्ठा spi_device *spi)
अणु
	काष्ठा mtk_nor *sp = spi_controller_get_devdata(spi->master);

	अगर (spi->max_speed_hz && (spi->max_speed_hz < sp->spi_freq)) अणु
		dev_err(&spi->dev, "spi clock should be %u Hz.\n",
			sp->spi_freq);
		वापस -EINVAL;
	पूर्ण
	spi->max_speed_hz = sp->spi_freq;

	वापस 0;
पूर्ण

अटल पूर्णांक mtk_nor_transfer_one_message(काष्ठा spi_controller *master,
					काष्ठा spi_message *m)
अणु
	काष्ठा mtk_nor *sp = spi_controller_get_devdata(master);
	काष्ठा spi_transfer *t = शून्य;
	अचिन्हित दीर्घ trx_len = 0;
	पूर्णांक stat = 0;
	पूर्णांक reg_offset = MTK_NOR_REG_PRGDATA_MAX;
	व्योम __iomem *reg;
	स्थिर u8 *txbuf;
	u8 *rxbuf;
	पूर्णांक i;

	list_क्रम_each_entry(t, &m->transfers, transfer_list) अणु
		txbuf = t->tx_buf;
		क्रम (i = 0; i < t->len; i++, reg_offset--) अणु
			reg = sp->base + MTK_NOR_REG_PRGDATA(reg_offset);
			अगर (txbuf)
				ग_लिखोb(txbuf[i], reg);
			अन्यथा
				ग_लिखोb(0, reg);
		पूर्ण
		trx_len += t->len;
	पूर्ण

	ग_लिखोl(trx_len * BITS_PER_BYTE, sp->base + MTK_NOR_REG_PRG_CNT);

	stat = mtk_nor_cmd_exec(sp, MTK_NOR_CMD_PROGRAM,
				trx_len * BITS_PER_BYTE);
	अगर (stat < 0)
		जाओ msg_करोne;

	reg_offset = trx_len - 1;
	list_क्रम_each_entry(t, &m->transfers, transfer_list) अणु
		rxbuf = t->rx_buf;
		क्रम (i = 0; i < t->len; i++, reg_offset--) अणु
			reg = sp->base + MTK_NOR_REG_SHIFT(reg_offset);
			अगर (rxbuf)
				rxbuf[i] = पढ़ोb(reg);
		पूर्ण
	पूर्ण

	m->actual_length = trx_len;
msg_करोne:
	m->status = stat;
	spi_finalize_current_message(master);

	वापस 0;
पूर्ण

अटल व्योम mtk_nor_disable_clk(काष्ठा mtk_nor *sp)
अणु
	clk_disable_unprepare(sp->spi_clk);
	clk_disable_unprepare(sp->ctlr_clk);
	clk_disable_unprepare(sp->axi_clk);
पूर्ण

अटल पूर्णांक mtk_nor_enable_clk(काष्ठा mtk_nor *sp)
अणु
	पूर्णांक ret;

	ret = clk_prepare_enable(sp->spi_clk);
	अगर (ret)
		वापस ret;

	ret = clk_prepare_enable(sp->ctlr_clk);
	अगर (ret) अणु
		clk_disable_unprepare(sp->spi_clk);
		वापस ret;
	पूर्ण

	ret = clk_prepare_enable(sp->axi_clk);
	अगर (ret) अणु
		clk_disable_unprepare(sp->spi_clk);
		clk_disable_unprepare(sp->ctlr_clk);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम mtk_nor_init(काष्ठा mtk_nor *sp)
अणु
	ग_लिखोl(0, sp->base + MTK_NOR_REG_IRQ_EN);
	ग_लिखोl(MTK_NOR_IRQ_MASK, sp->base + MTK_NOR_REG_IRQ_STAT);

	ग_लिखोl(MTK_NOR_ENABLE_SF_CMD, sp->base + MTK_NOR_REG_WP);
	mtk_nor_rmw(sp, MTK_NOR_REG_CFG2, MTK_NOR_WR_CUSTOM_OP_EN, 0);
	mtk_nor_rmw(sp, MTK_NOR_REG_CFG3,
		    MTK_NOR_DISABLE_WREN | MTK_NOR_DISABLE_SR_POLL, 0);
पूर्ण

अटल irqवापस_t mtk_nor_irq_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा mtk_nor *sp = data;
	u32 irq_status, irq_enabled;

	irq_status = पढ़ोl(sp->base + MTK_NOR_REG_IRQ_STAT);
	irq_enabled = पढ़ोl(sp->base + MTK_NOR_REG_IRQ_EN);
	// ग_लिखो status back to clear पूर्णांकerrupt
	ग_लिखोl(irq_status, sp->base + MTK_NOR_REG_IRQ_STAT);

	अगर (!(irq_status & irq_enabled))
		वापस IRQ_NONE;

	अगर (irq_status & MTK_NOR_IRQ_DMA) अणु
		complete(&sp->op_करोne);
		ग_लिखोl(0, sp->base + MTK_NOR_REG_IRQ_EN);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल माप_प्रकार mtk_max_msg_size(काष्ठा spi_device *spi)
अणु
	वापस MTK_NOR_PRG_MAX_SIZE;
पूर्ण

अटल स्थिर काष्ठा spi_controller_mem_ops mtk_nor_mem_ops = अणु
	.adjust_op_size = mtk_nor_adjust_op_size,
	.supports_op = mtk_nor_supports_op,
	.exec_op = mtk_nor_exec_op
पूर्ण;

अटल स्थिर काष्ठा of_device_id mtk_nor_match[] = अणु
	अणु .compatible = "mediatek,mt8192-nor", .data = (व्योम *)36 पूर्ण,
	अणु .compatible = "mediatek,mt8173-nor", .data = (व्योम *)32 पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, mtk_nor_match);

अटल पूर्णांक mtk_nor_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा spi_controller *ctlr;
	काष्ठा mtk_nor *sp;
	व्योम __iomem *base;
	काष्ठा clk *spi_clk, *ctlr_clk, *axi_clk;
	पूर्णांक ret, irq;
	अचिन्हित दीर्घ dma_bits;

	base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	spi_clk = devm_clk_get(&pdev->dev, "spi");
	अगर (IS_ERR(spi_clk))
		वापस PTR_ERR(spi_clk);

	ctlr_clk = devm_clk_get(&pdev->dev, "sf");
	अगर (IS_ERR(ctlr_clk))
		वापस PTR_ERR(ctlr_clk);

	axi_clk = devm_clk_get_optional(&pdev->dev, "axi");
	अगर (IS_ERR(axi_clk))
		वापस PTR_ERR(axi_clk);

	dma_bits = (अचिन्हित दीर्घ)of_device_get_match_data(&pdev->dev);
	अगर (dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(dma_bits))) अणु
		dev_err(&pdev->dev, "failed to set dma mask(%lu)\n", dma_bits);
		वापस -EINVAL;
	पूर्ण

	ctlr = devm_spi_alloc_master(&pdev->dev, माप(*sp));
	अगर (!ctlr) अणु
		dev_err(&pdev->dev, "failed to allocate spi controller\n");
		वापस -ENOMEM;
	पूर्ण

	ctlr->bits_per_word_mask = SPI_BPW_MASK(8);
	ctlr->dev.of_node = pdev->dev.of_node;
	ctlr->max_message_size = mtk_max_msg_size;
	ctlr->mem_ops = &mtk_nor_mem_ops;
	ctlr->mode_bits = SPI_RX_DUAL | SPI_RX_QUAD | SPI_TX_DUAL | SPI_TX_QUAD;
	ctlr->num_chipselect = 1;
	ctlr->setup = mtk_nor_setup;
	ctlr->transfer_one_message = mtk_nor_transfer_one_message;
	ctlr->स्वतः_runसमय_pm = true;

	dev_set_drvdata(&pdev->dev, ctlr);

	sp = spi_controller_get_devdata(ctlr);
	sp->base = base;
	sp->has_irq = false;
	sp->wbuf_en = false;
	sp->ctlr = ctlr;
	sp->dev = &pdev->dev;
	sp->spi_clk = spi_clk;
	sp->ctlr_clk = ctlr_clk;
	sp->axi_clk = axi_clk;
	sp->high_dma = (dma_bits > 32);
	sp->buffer = dmam_alloc_coherent(&pdev->dev,
				MTK_NOR_BOUNCE_BUF_SIZE + MTK_NOR_DMA_ALIGN,
				&sp->buffer_dma, GFP_KERNEL);
	अगर (!sp->buffer)
		वापस -ENOMEM;

	अगर ((uपूर्णांकptr_t)sp->buffer & MTK_NOR_DMA_ALIGN_MASK) अणु
		dev_err(sp->dev, "misaligned allocation of internal buffer.\n");
		वापस -ENOMEM;
	पूर्ण

	ret = mtk_nor_enable_clk(sp);
	अगर (ret < 0)
		वापस ret;

	sp->spi_freq = clk_get_rate(sp->spi_clk);

	mtk_nor_init(sp);

	irq = platक्रमm_get_irq_optional(pdev, 0);

	अगर (irq < 0) अणु
		dev_warn(sp->dev, "IRQ not available.");
	पूर्ण अन्यथा अणु
		ret = devm_request_irq(sp->dev, irq, mtk_nor_irq_handler, 0,
				       pdev->name, sp);
		अगर (ret < 0) अणु
			dev_warn(sp->dev, "failed to request IRQ.");
		पूर्ण अन्यथा अणु
			init_completion(&sp->op_करोne);
			sp->has_irq = true;
		पूर्ण
	पूर्ण

	pm_runसमय_set_स्वतःsuspend_delay(&pdev->dev, -1);
	pm_runसमय_use_स्वतःsuspend(&pdev->dev);
	pm_runसमय_set_active(&pdev->dev);
	pm_runसमय_enable(&pdev->dev);
	pm_runसमय_get_noresume(&pdev->dev);

	ret = devm_spi_रेजिस्टर_controller(&pdev->dev, ctlr);
	अगर (ret < 0)
		जाओ err_probe;

	pm_runसमय_mark_last_busy(&pdev->dev);
	pm_runसमय_put_स्वतःsuspend(&pdev->dev);

	dev_info(&pdev->dev, "spi frequency: %d Hz\n", sp->spi_freq);

	वापस 0;

err_probe:
	pm_runसमय_disable(&pdev->dev);
	pm_runसमय_set_suspended(&pdev->dev);
	pm_runसमय_करोnt_use_स्वतःsuspend(&pdev->dev);

	mtk_nor_disable_clk(sp);

	वापस ret;
पूर्ण

अटल पूर्णांक mtk_nor_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा spi_controller *ctlr = dev_get_drvdata(&pdev->dev);
	काष्ठा mtk_nor *sp = spi_controller_get_devdata(ctlr);

	pm_runसमय_disable(&pdev->dev);
	pm_runसमय_set_suspended(&pdev->dev);
	pm_runसमय_करोnt_use_स्वतःsuspend(&pdev->dev);

	mtk_nor_disable_clk(sp);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused mtk_nor_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा spi_controller *ctlr = dev_get_drvdata(dev);
	काष्ठा mtk_nor *sp = spi_controller_get_devdata(ctlr);

	mtk_nor_disable_clk(sp);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused mtk_nor_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा spi_controller *ctlr = dev_get_drvdata(dev);
	काष्ठा mtk_nor *sp = spi_controller_get_devdata(ctlr);

	वापस mtk_nor_enable_clk(sp);
पूर्ण

अटल पूर्णांक __maybe_unused mtk_nor_suspend(काष्ठा device *dev)
अणु
	वापस pm_runसमय_क्रमce_suspend(dev);
पूर्ण

अटल पूर्णांक __maybe_unused mtk_nor_resume(काष्ठा device *dev)
अणु
	वापस pm_runसमय_क्रमce_resume(dev);
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops mtk_nor_pm_ops = अणु
	SET_RUNTIME_PM_OPS(mtk_nor_runसमय_suspend,
			   mtk_nor_runसमय_resume, शून्य)
	SET_SYSTEM_SLEEP_PM_OPS(mtk_nor_suspend, mtk_nor_resume)
पूर्ण;

अटल काष्ठा platक्रमm_driver mtk_nor_driver = अणु
	.driver = अणु
		.name = DRIVER_NAME,
		.of_match_table = mtk_nor_match,
		.pm = &mtk_nor_pm_ops,
	पूर्ण,
	.probe = mtk_nor_probe,
	.हटाओ = mtk_nor_हटाओ,
पूर्ण;

module_platक्रमm_driver(mtk_nor_driver);

MODULE_DESCRIPTION("Mediatek SPI NOR controller driver");
MODULE_AUTHOR("Chuanhong Guo <gch981213@gmail.com>");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:" DRIVER_NAME);
