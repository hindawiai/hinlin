<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2018-2019 Synopsys, Inc. and/or its affiliates.
 * Synopsys DesignWare eDMA v0 core
 *
 * Author: Gustavo Pimentel <gustavo.pimentel@synopsys.com>
 */

#समावेश <linux/debugfs.h>
#समावेश <linux/bitfield.h>

#समावेश "dw-edma-v0-debugfs.h"
#समावेश "dw-edma-v0-regs.h"
#समावेश "dw-edma-core.h"

#घोषणा REGS_ADDR(name) \
	((व्योम __क्रमce *)&regs->name)
#घोषणा REGISTER(name) \
	अणु #name, REGS_ADDR(name) पूर्ण

#घोषणा WR_REGISTER(name) \
	अणु #name, REGS_ADDR(wr_##name) पूर्ण
#घोषणा RD_REGISTER(name) \
	अणु #name, REGS_ADDR(rd_##name) पूर्ण

#घोषणा WR_REGISTER_LEGACY(name) \
	अणु #name, REGS_ADDR(type.legacy.wr_##name) पूर्ण
#घोषणा RD_REGISTER_LEGACY(name) \
	अणु #name, REGS_ADDR(type.legacy.rd_##name) पूर्ण

#घोषणा WR_REGISTER_UNROLL(name) \
	अणु #name, REGS_ADDR(type.unroll.wr_##name) पूर्ण
#घोषणा RD_REGISTER_UNROLL(name) \
	अणु #name, REGS_ADDR(type.unroll.rd_##name) पूर्ण

#घोषणा WRITE_STR				"write"
#घोषणा READ_STR				"read"
#घोषणा CHANNEL_STR				"channel"
#घोषणा REGISTERS_STR				"registers"

अटल काष्ठा dw_edma				*dw;
अटल काष्ठा dw_edma_v0_regs			__iomem *regs;

अटल काष्ठा अणु
	व्योम					__iomem *start;
	व्योम					__iomem *end;
पूर्ण lim[2][EDMA_V0_MAX_NR_CH];

काष्ठा debugfs_entries अणु
	स्थिर अक्षर				*name;
	dma_addr_t				*reg;
पूर्ण;

अटल पूर्णांक dw_edma_debugfs_u32_get(व्योम *data, u64 *val)
अणु
	व्योम __iomem *reg = (व्योम __क्रमce __iomem *)data;
	अगर (dw->mf == EDMA_MF_EDMA_LEGACY &&
	    reg >= (व्योम __iomem *)&regs->type.legacy.ch) अणु
		व्योम __iomem *ptr = &regs->type.legacy.ch;
		u32 viewport_sel = 0;
		अचिन्हित दीर्घ flags;
		u16 ch;

		क्रम (ch = 0; ch < dw->wr_ch_cnt; ch++)
			अगर (lim[0][ch].start >= reg && reg < lim[0][ch].end) अणु
				ptr += (reg - lim[0][ch].start);
				जाओ legacy_sel_wr;
			पूर्ण

		क्रम (ch = 0; ch < dw->rd_ch_cnt; ch++)
			अगर (lim[1][ch].start >= reg && reg < lim[1][ch].end) अणु
				ptr += (reg - lim[1][ch].start);
				जाओ legacy_sel_rd;
			पूर्ण

		वापस 0;
legacy_sel_rd:
		viewport_sel = BIT(31);
legacy_sel_wr:
		viewport_sel |= FIELD_PREP(EDMA_V0_VIEWPORT_MASK, ch);

		raw_spin_lock_irqsave(&dw->lock, flags);

		ग_लिखोl(viewport_sel, &regs->type.legacy.viewport_sel);
		*val = पढ़ोl(ptr);

		raw_spin_unlock_irqrestore(&dw->lock, flags);
	पूर्ण अन्यथा अणु
		*val = पढ़ोl(reg);
	पूर्ण

	वापस 0;
पूर्ण
DEFINE_DEBUGFS_ATTRIBUTE(fops_x32, dw_edma_debugfs_u32_get, शून्य, "0x%08llx\n");

अटल व्योम dw_edma_debugfs_create_x32(स्थिर काष्ठा debugfs_entries entries[],
				       पूर्णांक nr_entries, काष्ठा dentry *dir)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < nr_entries; i++) अणु
		अगर (!debugfs_create_file_unsafe(entries[i].name, 0444, dir,
						entries[i].reg,	&fops_x32))
			अवरोध;
	पूर्ण
पूर्ण

अटल व्योम dw_edma_debugfs_regs_ch(काष्ठा dw_edma_v0_ch_regs __iomem *regs,
				    काष्ठा dentry *dir)
अणु
	पूर्णांक nr_entries;
	स्थिर काष्ठा debugfs_entries debugfs_regs[] = अणु
		REGISTER(ch_control1),
		REGISTER(ch_control2),
		REGISTER(transfer_size),
		REGISTER(sar.lsb),
		REGISTER(sar.msb),
		REGISTER(dar.lsb),
		REGISTER(dar.msb),
		REGISTER(llp.lsb),
		REGISTER(llp.msb),
	पूर्ण;

	nr_entries = ARRAY_SIZE(debugfs_regs);
	dw_edma_debugfs_create_x32(debugfs_regs, nr_entries, dir);
पूर्ण

अटल व्योम dw_edma_debugfs_regs_wr(काष्ठा dentry *dir)
अणु
	स्थिर काष्ठा debugfs_entries debugfs_regs[] = अणु
		/* eDMA global रेजिस्टरs */
		WR_REGISTER(engine_en),
		WR_REGISTER(करोorbell),
		WR_REGISTER(ch_arb_weight.lsb),
		WR_REGISTER(ch_arb_weight.msb),
		/* eDMA पूर्णांकerrupts रेजिस्टरs */
		WR_REGISTER(पूर्णांक_status),
		WR_REGISTER(पूर्णांक_mask),
		WR_REGISTER(पूर्णांक_clear),
		WR_REGISTER(err_status),
		WR_REGISTER(करोne_imwr.lsb),
		WR_REGISTER(करोne_imwr.msb),
		WR_REGISTER(पात_imwr.lsb),
		WR_REGISTER(पात_imwr.msb),
		WR_REGISTER(ch01_imwr_data),
		WR_REGISTER(ch23_imwr_data),
		WR_REGISTER(ch45_imwr_data),
		WR_REGISTER(ch67_imwr_data),
		WR_REGISTER(linked_list_err_en),
	पूर्ण;
	स्थिर काष्ठा debugfs_entries debugfs_unroll_regs[] = अणु
		/* eDMA channel context grouping */
		WR_REGISTER_UNROLL(engine_chgroup),
		WR_REGISTER_UNROLL(engine_hshake_cnt.lsb),
		WR_REGISTER_UNROLL(engine_hshake_cnt.msb),
		WR_REGISTER_UNROLL(ch0_pwr_en),
		WR_REGISTER_UNROLL(ch1_pwr_en),
		WR_REGISTER_UNROLL(ch2_pwr_en),
		WR_REGISTER_UNROLL(ch3_pwr_en),
		WR_REGISTER_UNROLL(ch4_pwr_en),
		WR_REGISTER_UNROLL(ch5_pwr_en),
		WR_REGISTER_UNROLL(ch6_pwr_en),
		WR_REGISTER_UNROLL(ch7_pwr_en),
	पूर्ण;
	काष्ठा dentry *regs_dir, *ch_dir;
	पूर्णांक nr_entries, i;
	अक्षर name[16];

	regs_dir = debugfs_create_dir(WRITE_STR, dir);
	अगर (!regs_dir)
		वापस;

	nr_entries = ARRAY_SIZE(debugfs_regs);
	dw_edma_debugfs_create_x32(debugfs_regs, nr_entries, regs_dir);

	अगर (dw->mf == EDMA_MF_HDMA_COMPAT) अणु
		nr_entries = ARRAY_SIZE(debugfs_unroll_regs);
		dw_edma_debugfs_create_x32(debugfs_unroll_regs, nr_entries,
					   regs_dir);
	पूर्ण

	क्रम (i = 0; i < dw->wr_ch_cnt; i++) अणु
		snम_लिखो(name, माप(name), "%s:%d", CHANNEL_STR, i);

		ch_dir = debugfs_create_dir(name, regs_dir);
		अगर (!ch_dir)
			वापस;

		dw_edma_debugfs_regs_ch(&regs->type.unroll.ch[i].wr, ch_dir);

		lim[0][i].start = &regs->type.unroll.ch[i].wr;
		lim[0][i].end = &regs->type.unroll.ch[i].padding_1[0];
	पूर्ण
पूर्ण

अटल व्योम dw_edma_debugfs_regs_rd(काष्ठा dentry *dir)
अणु
	स्थिर काष्ठा debugfs_entries debugfs_regs[] = अणु
		/* eDMA global रेजिस्टरs */
		RD_REGISTER(engine_en),
		RD_REGISTER(करोorbell),
		RD_REGISTER(ch_arb_weight.lsb),
		RD_REGISTER(ch_arb_weight.msb),
		/* eDMA पूर्णांकerrupts रेजिस्टरs */
		RD_REGISTER(पूर्णांक_status),
		RD_REGISTER(पूर्णांक_mask),
		RD_REGISTER(पूर्णांक_clear),
		RD_REGISTER(err_status.lsb),
		RD_REGISTER(err_status.msb),
		RD_REGISTER(linked_list_err_en),
		RD_REGISTER(करोne_imwr.lsb),
		RD_REGISTER(करोne_imwr.msb),
		RD_REGISTER(पात_imwr.lsb),
		RD_REGISTER(पात_imwr.msb),
		RD_REGISTER(ch01_imwr_data),
		RD_REGISTER(ch23_imwr_data),
		RD_REGISTER(ch45_imwr_data),
		RD_REGISTER(ch67_imwr_data),
	पूर्ण;
	स्थिर काष्ठा debugfs_entries debugfs_unroll_regs[] = अणु
		/* eDMA channel context grouping */
		RD_REGISTER_UNROLL(engine_chgroup),
		RD_REGISTER_UNROLL(engine_hshake_cnt.lsb),
		RD_REGISTER_UNROLL(engine_hshake_cnt.msb),
		RD_REGISTER_UNROLL(ch0_pwr_en),
		RD_REGISTER_UNROLL(ch1_pwr_en),
		RD_REGISTER_UNROLL(ch2_pwr_en),
		RD_REGISTER_UNROLL(ch3_pwr_en),
		RD_REGISTER_UNROLL(ch4_pwr_en),
		RD_REGISTER_UNROLL(ch5_pwr_en),
		RD_REGISTER_UNROLL(ch6_pwr_en),
		RD_REGISTER_UNROLL(ch7_pwr_en),
	पूर्ण;
	काष्ठा dentry *regs_dir, *ch_dir;
	पूर्णांक nr_entries, i;
	अक्षर name[16];

	regs_dir = debugfs_create_dir(READ_STR, dir);
	अगर (!regs_dir)
		वापस;

	nr_entries = ARRAY_SIZE(debugfs_regs);
	dw_edma_debugfs_create_x32(debugfs_regs, nr_entries, regs_dir);

	अगर (dw->mf == EDMA_MF_HDMA_COMPAT) अणु
		nr_entries = ARRAY_SIZE(debugfs_unroll_regs);
		dw_edma_debugfs_create_x32(debugfs_unroll_regs, nr_entries,
					   regs_dir);
	पूर्ण

	क्रम (i = 0; i < dw->rd_ch_cnt; i++) अणु
		snम_लिखो(name, माप(name), "%s:%d", CHANNEL_STR, i);

		ch_dir = debugfs_create_dir(name, regs_dir);
		अगर (!ch_dir)
			वापस;

		dw_edma_debugfs_regs_ch(&regs->type.unroll.ch[i].rd, ch_dir);

		lim[1][i].start = &regs->type.unroll.ch[i].rd;
		lim[1][i].end = &regs->type.unroll.ch[i].padding_2[0];
	पूर्ण
पूर्ण

अटल व्योम dw_edma_debugfs_regs(व्योम)
अणु
	स्थिर काष्ठा debugfs_entries debugfs_regs[] = अणु
		REGISTER(ctrl_data_arb_prior),
		REGISTER(ctrl),
	पूर्ण;
	काष्ठा dentry *regs_dir;
	पूर्णांक nr_entries;

	regs_dir = debugfs_create_dir(REGISTERS_STR, dw->debugfs);
	अगर (!regs_dir)
		वापस;

	nr_entries = ARRAY_SIZE(debugfs_regs);
	dw_edma_debugfs_create_x32(debugfs_regs, nr_entries, regs_dir);

	dw_edma_debugfs_regs_wr(regs_dir);
	dw_edma_debugfs_regs_rd(regs_dir);
पूर्ण

व्योम dw_edma_v0_debugfs_on(काष्ठा dw_edma_chip *chip)
अणु
	dw = chip->dw;
	अगर (!dw)
		वापस;

	regs = dw->rg_region.vaddr;
	अगर (!regs)
		वापस;

	dw->debugfs = debugfs_create_dir(dw->name, शून्य);
	अगर (!dw->debugfs)
		वापस;

	debugfs_create_u32("mf", 0444, dw->debugfs, &dw->mf);
	debugfs_create_u16("wr_ch_cnt", 0444, dw->debugfs, &dw->wr_ch_cnt);
	debugfs_create_u16("rd_ch_cnt", 0444, dw->debugfs, &dw->rd_ch_cnt);

	dw_edma_debugfs_regs();
पूर्ण

व्योम dw_edma_v0_debugfs_off(काष्ठा dw_edma_chip *chip)
अणु
	dw = chip->dw;
	अगर (!dw)
		वापस;

	debugfs_हटाओ_recursive(dw->debugfs);
	dw->debugfs = शून्य;
पूर्ण
