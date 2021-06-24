<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2018-2019 Synopsys, Inc. and/or its affiliates.
 * Synopsys DesignWare eDMA v0 core
 *
 * Author: Gustavo Pimentel <gustavo.pimentel@synopsys.com>
 */

#समावेश <linux/bitfield.h>

#समावेश "dw-edma-core.h"
#समावेश "dw-edma-v0-core.h"
#समावेश "dw-edma-v0-regs.h"
#समावेश "dw-edma-v0-debugfs.h"

क्रमागत dw_edma_control अणु
	DW_EDMA_V0_CB					= BIT(0),
	DW_EDMA_V0_TCB					= BIT(1),
	DW_EDMA_V0_LLP					= BIT(2),
	DW_EDMA_V0_LIE					= BIT(3),
	DW_EDMA_V0_RIE					= BIT(4),
	DW_EDMA_V0_CCS					= BIT(8),
	DW_EDMA_V0_LLE					= BIT(9),
पूर्ण;

अटल अंतरभूत काष्ठा dw_edma_v0_regs __iomem *__dw_regs(काष्ठा dw_edma *dw)
अणु
	वापस dw->rg_region.vaddr;
पूर्ण

#घोषणा SET_32(dw, name, value)				\
	ग_लिखोl(value, &(__dw_regs(dw)->name))

#घोषणा GET_32(dw, name)				\
	पढ़ोl(&(__dw_regs(dw)->name))

#घोषणा SET_RW_32(dw, dir, name, value)			\
	करो अणु						\
		अगर ((dir) == EDMA_सूची_WRITE)		\
			SET_32(dw, wr_##name, value);	\
		अन्यथा					\
			SET_32(dw, rd_##name, value);	\
	पूर्ण जबतक (0)

#घोषणा GET_RW_32(dw, dir, name)			\
	((dir) == EDMA_सूची_WRITE			\
	  ? GET_32(dw, wr_##name)			\
	  : GET_32(dw, rd_##name))

#घोषणा SET_BOTH_32(dw, name, value)			\
	करो अणु						\
		SET_32(dw, wr_##name, value);		\
		SET_32(dw, rd_##name, value);		\
	पूर्ण जबतक (0)

#अगर_घोषित CONFIG_64BIT

#घोषणा SET_64(dw, name, value)				\
	ग_लिखोq(value, &(__dw_regs(dw)->name))

#घोषणा GET_64(dw, name)				\
	पढ़ोq(&(__dw_regs(dw)->name))

#घोषणा SET_RW_64(dw, dir, name, value)			\
	करो अणु						\
		अगर ((dir) == EDMA_सूची_WRITE)		\
			SET_64(dw, wr_##name, value);	\
		अन्यथा					\
			SET_64(dw, rd_##name, value);	\
	पूर्ण जबतक (0)

#घोषणा GET_RW_64(dw, dir, name)			\
	((dir) == EDMA_सूची_WRITE			\
	  ? GET_64(dw, wr_##name)			\
	  : GET_64(dw, rd_##name))

#घोषणा SET_BOTH_64(dw, name, value)			\
	करो अणु						\
		SET_64(dw, wr_##name, value);		\
		SET_64(dw, rd_##name, value);		\
	पूर्ण जबतक (0)

#पूर्ण_अगर /* CONFIG_64BIT */

#घोषणा SET_COMPAT(dw, name, value)			\
	ग_लिखोl(value, &(__dw_regs(dw)->type.unroll.name))

#घोषणा SET_RW_COMPAT(dw, dir, name, value)		\
	करो अणु						\
		अगर ((dir) == EDMA_सूची_WRITE)		\
			SET_COMPAT(dw, wr_##name, value); \
		अन्यथा					\
			SET_COMPAT(dw, rd_##name, value); \
	पूर्ण जबतक (0)

अटल अंतरभूत काष्ठा dw_edma_v0_ch_regs __iomem *
__dw_ch_regs(काष्ठा dw_edma *dw, क्रमागत dw_edma_dir dir, u16 ch)
अणु
	अगर (dw->mf == EDMA_MF_EDMA_LEGACY)
		वापस &(__dw_regs(dw)->type.legacy.ch);

	अगर (dir == EDMA_सूची_WRITE)
		वापस &__dw_regs(dw)->type.unroll.ch[ch].wr;

	वापस &__dw_regs(dw)->type.unroll.ch[ch].rd;
पूर्ण

अटल अंतरभूत व्योम ग_लिखोl_ch(काष्ठा dw_edma *dw, क्रमागत dw_edma_dir dir, u16 ch,
			     u32 value, व्योम __iomem *addr)
अणु
	अगर (dw->mf == EDMA_MF_EDMA_LEGACY) अणु
		u32 viewport_sel;
		अचिन्हित दीर्घ flags;

		raw_spin_lock_irqsave(&dw->lock, flags);

		viewport_sel = FIELD_PREP(EDMA_V0_VIEWPORT_MASK, ch);
		अगर (dir == EDMA_सूची_READ)
			viewport_sel |= BIT(31);

		ग_लिखोl(viewport_sel,
		       &(__dw_regs(dw)->type.legacy.viewport_sel));
		ग_लिखोl(value, addr);

		raw_spin_unlock_irqrestore(&dw->lock, flags);
	पूर्ण अन्यथा अणु
		ग_लिखोl(value, addr);
	पूर्ण
पूर्ण

अटल अंतरभूत u32 पढ़ोl_ch(काष्ठा dw_edma *dw, क्रमागत dw_edma_dir dir, u16 ch,
			   स्थिर व्योम __iomem *addr)
अणु
	u32 value;

	अगर (dw->mf == EDMA_MF_EDMA_LEGACY) अणु
		u32 viewport_sel;
		अचिन्हित दीर्घ flags;

		raw_spin_lock_irqsave(&dw->lock, flags);

		viewport_sel = FIELD_PREP(EDMA_V0_VIEWPORT_MASK, ch);
		अगर (dir == EDMA_सूची_READ)
			viewport_sel |= BIT(31);

		ग_लिखोl(viewport_sel,
		       &(__dw_regs(dw)->type.legacy.viewport_sel));
		value = पढ़ोl(addr);

		raw_spin_unlock_irqrestore(&dw->lock, flags);
	पूर्ण अन्यथा अणु
		value = पढ़ोl(addr);
	पूर्ण

	वापस value;
पूर्ण

#घोषणा SET_CH_32(dw, dir, ch, name, value) \
	ग_लिखोl_ch(dw, dir, ch, value, &(__dw_ch_regs(dw, dir, ch)->name))

#घोषणा GET_CH_32(dw, dir, ch, name) \
	पढ़ोl_ch(dw, dir, ch, &(__dw_ch_regs(dw, dir, ch)->name))

#घोषणा SET_LL_32(ll, value) \
	ग_लिखोl(value, ll)

#अगर_घोषित CONFIG_64BIT

अटल अंतरभूत व्योम ग_लिखोq_ch(काष्ठा dw_edma *dw, क्रमागत dw_edma_dir dir, u16 ch,
			     u64 value, व्योम __iomem *addr)
अणु
	अगर (dw->mf == EDMA_MF_EDMA_LEGACY) अणु
		u32 viewport_sel;
		अचिन्हित दीर्घ flags;

		raw_spin_lock_irqsave(&dw->lock, flags);

		viewport_sel = FIELD_PREP(EDMA_V0_VIEWPORT_MASK, ch);
		अगर (dir == EDMA_सूची_READ)
			viewport_sel |= BIT(31);

		ग_लिखोl(viewport_sel,
		       &(__dw_regs(dw)->type.legacy.viewport_sel));
		ग_लिखोq(value, addr);

		raw_spin_unlock_irqrestore(&dw->lock, flags);
	पूर्ण अन्यथा अणु
		ग_लिखोq(value, addr);
	पूर्ण
पूर्ण

अटल अंतरभूत u64 पढ़ोq_ch(काष्ठा dw_edma *dw, क्रमागत dw_edma_dir dir, u16 ch,
			   स्थिर व्योम __iomem *addr)
अणु
	u32 value;

	अगर (dw->mf == EDMA_MF_EDMA_LEGACY) अणु
		u32 viewport_sel;
		अचिन्हित दीर्घ flags;

		raw_spin_lock_irqsave(&dw->lock, flags);

		viewport_sel = FIELD_PREP(EDMA_V0_VIEWPORT_MASK, ch);
		अगर (dir == EDMA_सूची_READ)
			viewport_sel |= BIT(31);

		ग_लिखोl(viewport_sel,
		       &(__dw_regs(dw)->type.legacy.viewport_sel));
		value = पढ़ोq(addr);

		raw_spin_unlock_irqrestore(&dw->lock, flags);
	पूर्ण अन्यथा अणु
		value = पढ़ोq(addr);
	पूर्ण

	वापस value;
पूर्ण

#घोषणा SET_CH_64(dw, dir, ch, name, value) \
	ग_लिखोq_ch(dw, dir, ch, value, &(__dw_ch_regs(dw, dir, ch)->name))

#घोषणा GET_CH_64(dw, dir, ch, name) \
	पढ़ोq_ch(dw, dir, ch, &(__dw_ch_regs(dw, dir, ch)->name))

#घोषणा SET_LL_64(ll, value) \
	ग_लिखोq(value, ll)

#पूर्ण_अगर /* CONFIG_64BIT */

/* eDMA management callbacks */
व्योम dw_edma_v0_core_off(काष्ठा dw_edma *dw)
अणु
	SET_BOTH_32(dw, पूर्णांक_mask,
		    EDMA_V0_DONE_INT_MASK | EDMA_V0_ABORT_INT_MASK);
	SET_BOTH_32(dw, पूर्णांक_clear,
		    EDMA_V0_DONE_INT_MASK | EDMA_V0_ABORT_INT_MASK);
	SET_BOTH_32(dw, engine_en, 0);
पूर्ण

u16 dw_edma_v0_core_ch_count(काष्ठा dw_edma *dw, क्रमागत dw_edma_dir dir)
अणु
	u32 num_ch;

	अगर (dir == EDMA_सूची_WRITE)
		num_ch = FIELD_GET(EDMA_V0_WRITE_CH_COUNT_MASK,
				   GET_32(dw, ctrl));
	अन्यथा
		num_ch = FIELD_GET(EDMA_V0_READ_CH_COUNT_MASK,
				   GET_32(dw, ctrl));

	अगर (num_ch > EDMA_V0_MAX_NR_CH)
		num_ch = EDMA_V0_MAX_NR_CH;

	वापस (u16)num_ch;
पूर्ण

क्रमागत dma_status dw_edma_v0_core_ch_status(काष्ठा dw_edma_chan *chan)
अणु
	काष्ठा dw_edma *dw = chan->chip->dw;
	u32 पंचांगp;

	पंचांगp = FIELD_GET(EDMA_V0_CH_STATUS_MASK,
			GET_CH_32(dw, chan->dir, chan->id, ch_control1));

	अगर (पंचांगp == 1)
		वापस DMA_IN_PROGRESS;
	अन्यथा अगर (पंचांगp == 3)
		वापस DMA_COMPLETE;
	अन्यथा
		वापस DMA_ERROR;
पूर्ण

व्योम dw_edma_v0_core_clear_करोne_पूर्णांक(काष्ठा dw_edma_chan *chan)
अणु
	काष्ठा dw_edma *dw = chan->chip->dw;

	SET_RW_32(dw, chan->dir, पूर्णांक_clear,
		  FIELD_PREP(EDMA_V0_DONE_INT_MASK, BIT(chan->id)));
पूर्ण

व्योम dw_edma_v0_core_clear_पात_पूर्णांक(काष्ठा dw_edma_chan *chan)
अणु
	काष्ठा dw_edma *dw = chan->chip->dw;

	SET_RW_32(dw, chan->dir, पूर्णांक_clear,
		  FIELD_PREP(EDMA_V0_ABORT_INT_MASK, BIT(chan->id)));
पूर्ण

u32 dw_edma_v0_core_status_करोne_पूर्णांक(काष्ठा dw_edma *dw, क्रमागत dw_edma_dir dir)
अणु
	वापस FIELD_GET(EDMA_V0_DONE_INT_MASK,
			 GET_RW_32(dw, dir, पूर्णांक_status));
पूर्ण

u32 dw_edma_v0_core_status_पात_पूर्णांक(काष्ठा dw_edma *dw, क्रमागत dw_edma_dir dir)
अणु
	वापस FIELD_GET(EDMA_V0_ABORT_INT_MASK,
			 GET_RW_32(dw, dir, पूर्णांक_status));
पूर्ण

अटल व्योम dw_edma_v0_core_ग_लिखो_chunk(काष्ठा dw_edma_chunk *chunk)
अणु
	काष्ठा dw_edma_burst *child;
	काष्ठा dw_edma_v0_lli __iomem *lli;
	काष्ठा dw_edma_v0_llp __iomem *llp;
	u32 control = 0, i = 0;
	पूर्णांक j;

	lli = chunk->ll_region.vaddr;

	अगर (chunk->cb)
		control = DW_EDMA_V0_CB;

	j = chunk->bursts_alloc;
	list_क्रम_each_entry(child, &chunk->burst->list, list) अणु
		j--;
		अगर (!j)
			control |= (DW_EDMA_V0_LIE | DW_EDMA_V0_RIE);

		/* Channel control */
		SET_LL_32(&lli[i].control, control);
		/* Transfer size */
		SET_LL_32(&lli[i].transfer_size, child->sz);
		/* SAR */
		#अगर_घोषित CONFIG_64BIT
			SET_LL_64(&lli[i].sar.reg, child->sar);
		#अन्यथा /* CONFIG_64BIT */
			SET_LL_32(&lli[i].sar.lsb, lower_32_bits(child->sar));
			SET_LL_32(&lli[i].sar.msb, upper_32_bits(child->sar));
		#पूर्ण_अगर /* CONFIG_64BIT */
		/* DAR */
		#अगर_घोषित CONFIG_64BIT
			SET_LL_64(&lli[i].dar.reg, child->dar);
		#अन्यथा /* CONFIG_64BIT */
			SET_LL_32(&lli[i].dar.lsb, lower_32_bits(child->dar));
			SET_LL_32(&lli[i].dar.msb, upper_32_bits(child->dar));
		#पूर्ण_अगर /* CONFIG_64BIT */
		i++;
	पूर्ण

	llp = (व्योम __iomem *)&lli[i];
	control = DW_EDMA_V0_LLP | DW_EDMA_V0_TCB;
	अगर (!chunk->cb)
		control |= DW_EDMA_V0_CB;

	/* Channel control */
	SET_LL_32(&llp->control, control);
	/* Linked list */
	#अगर_घोषित CONFIG_64BIT
		SET_LL_64(&llp->llp.reg, chunk->ll_region.paddr);
	#अन्यथा /* CONFIG_64BIT */
		SET_LL_32(&llp->llp.lsb, lower_32_bits(chunk->ll_region.paddr));
		SET_LL_32(&llp->llp.msb, upper_32_bits(chunk->ll_region.paddr));
	#पूर्ण_अगर /* CONFIG_64BIT */
पूर्ण

व्योम dw_edma_v0_core_start(काष्ठा dw_edma_chunk *chunk, bool first)
अणु
	काष्ठा dw_edma_chan *chan = chunk->chan;
	काष्ठा dw_edma *dw = chan->chip->dw;
	u32 पंचांगp;

	dw_edma_v0_core_ग_लिखो_chunk(chunk);

	अगर (first) अणु
		/* Enable engine */
		SET_RW_32(dw, chan->dir, engine_en, BIT(0));
		अगर (dw->mf == EDMA_MF_HDMA_COMPAT) अणु
			चयन (chan->id) अणु
			हाल 0:
				SET_RW_COMPAT(dw, chan->dir, ch0_pwr_en,
					      BIT(0));
				अवरोध;
			हाल 1:
				SET_RW_COMPAT(dw, chan->dir, ch1_pwr_en,
					      BIT(0));
				अवरोध;
			हाल 2:
				SET_RW_COMPAT(dw, chan->dir, ch2_pwr_en,
					      BIT(0));
				अवरोध;
			हाल 3:
				SET_RW_COMPAT(dw, chan->dir, ch3_pwr_en,
					      BIT(0));
				अवरोध;
			हाल 4:
				SET_RW_COMPAT(dw, chan->dir, ch4_pwr_en,
					      BIT(0));
				अवरोध;
			हाल 5:
				SET_RW_COMPAT(dw, chan->dir, ch5_pwr_en,
					      BIT(0));
				अवरोध;
			हाल 6:
				SET_RW_COMPAT(dw, chan->dir, ch6_pwr_en,
					      BIT(0));
				अवरोध;
			हाल 7:
				SET_RW_COMPAT(dw, chan->dir, ch7_pwr_en,
					      BIT(0));
				अवरोध;
			पूर्ण
		पूर्ण
		/* Interrupt unmask - करोne, पात */
		पंचांगp = GET_RW_32(dw, chan->dir, पूर्णांक_mask);
		पंचांगp &= ~FIELD_PREP(EDMA_V0_DONE_INT_MASK, BIT(chan->id));
		पंचांगp &= ~FIELD_PREP(EDMA_V0_ABORT_INT_MASK, BIT(chan->id));
		SET_RW_32(dw, chan->dir, पूर्णांक_mask, पंचांगp);
		/* Linked list error */
		पंचांगp = GET_RW_32(dw, chan->dir, linked_list_err_en);
		पंचांगp |= FIELD_PREP(EDMA_V0_LINKED_LIST_ERR_MASK, BIT(chan->id));
		SET_RW_32(dw, chan->dir, linked_list_err_en, पंचांगp);
		/* Channel control */
		SET_CH_32(dw, chan->dir, chan->id, ch_control1,
			  (DW_EDMA_V0_CCS | DW_EDMA_V0_LLE));
		/* Linked list */
		#अगर_घोषित CONFIG_64BIT
			SET_CH_64(dw, chan->dir, chan->id, llp.reg,
				  chunk->ll_region.paddr);
		#अन्यथा /* CONFIG_64BIT */
			SET_CH_32(dw, chan->dir, chan->id, llp.lsb,
				  lower_32_bits(chunk->ll_region.paddr));
			SET_CH_32(dw, chan->dir, chan->id, llp.msb,
				  upper_32_bits(chunk->ll_region.paddr));
		#पूर्ण_अगर /* CONFIG_64BIT */
	पूर्ण
	/* Doorbell */
	SET_RW_32(dw, chan->dir, करोorbell,
		  FIELD_PREP(EDMA_V0_DOORBELL_CH_MASK, chan->id));
पूर्ण

पूर्णांक dw_edma_v0_core_device_config(काष्ठा dw_edma_chan *chan)
अणु
	काष्ठा dw_edma *dw = chan->chip->dw;
	u32 पंचांगp = 0;

	/* MSI करोne addr - low, high */
	SET_RW_32(dw, chan->dir, करोne_imwr.lsb, chan->msi.address_lo);
	SET_RW_32(dw, chan->dir, करोne_imwr.msb, chan->msi.address_hi);
	/* MSI पात addr - low, high */
	SET_RW_32(dw, chan->dir, पात_imwr.lsb, chan->msi.address_lo);
	SET_RW_32(dw, chan->dir, पात_imwr.msb, chan->msi.address_hi);
	/* MSI data - low, high */
	चयन (chan->id) अणु
	हाल 0:
	हाल 1:
		पंचांगp = GET_RW_32(dw, chan->dir, ch01_imwr_data);
		अवरोध;

	हाल 2:
	हाल 3:
		पंचांगp = GET_RW_32(dw, chan->dir, ch23_imwr_data);
		अवरोध;

	हाल 4:
	हाल 5:
		पंचांगp = GET_RW_32(dw, chan->dir, ch45_imwr_data);
		अवरोध;

	हाल 6:
	हाल 7:
		पंचांगp = GET_RW_32(dw, chan->dir, ch67_imwr_data);
		अवरोध;
	पूर्ण

	अगर (chan->id & BIT(0)) अणु
		/* Channel odd अणु1, 3, 5, 7पूर्ण */
		पंचांगp &= EDMA_V0_CH_EVEN_MSI_DATA_MASK;
		पंचांगp |= FIELD_PREP(EDMA_V0_CH_ODD_MSI_DATA_MASK,
				  chan->msi.data);
	पूर्ण अन्यथा अणु
		/* Channel even अणु0, 2, 4, 6पूर्ण */
		पंचांगp &= EDMA_V0_CH_ODD_MSI_DATA_MASK;
		पंचांगp |= FIELD_PREP(EDMA_V0_CH_EVEN_MSI_DATA_MASK,
				  chan->msi.data);
	पूर्ण

	चयन (chan->id) अणु
	हाल 0:
	हाल 1:
		SET_RW_32(dw, chan->dir, ch01_imwr_data, पंचांगp);
		अवरोध;

	हाल 2:
	हाल 3:
		SET_RW_32(dw, chan->dir, ch23_imwr_data, पंचांगp);
		अवरोध;

	हाल 4:
	हाल 5:
		SET_RW_32(dw, chan->dir, ch45_imwr_data, पंचांगp);
		अवरोध;

	हाल 6:
	हाल 7:
		SET_RW_32(dw, chan->dir, ch67_imwr_data, पंचांगp);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

/* eDMA debugfs callbacks */
व्योम dw_edma_v0_core_debugfs_on(काष्ठा dw_edma_chip *chip)
अणु
	dw_edma_v0_debugfs_on(chip);
पूर्ण

व्योम dw_edma_v0_core_debugfs_off(काष्ठा dw_edma_chip *chip)
अणु
	dw_edma_v0_debugfs_off(chip);
पूर्ण
