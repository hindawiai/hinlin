<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright तऊ 2006, Intel Corporation.
 */
#अगर_अघोषित _ADMA_H
#घोषणा _ADMA_H
#समावेश <linux/types.h>
#समावेश <linux/पन.स>
#समावेश <linux/platक्रमm_data/dma-iop32x.h>

/* Memory copy units */
#घोषणा DMA_CCR(chan)		(chan->mmr_base + 0x0)
#घोषणा DMA_CSR(chan)		(chan->mmr_base + 0x4)
#घोषणा DMA_DAR(chan)		(chan->mmr_base + 0xc)
#घोषणा DMA_NDAR(chan)		(chan->mmr_base + 0x10)
#घोषणा DMA_PADR(chan)		(chan->mmr_base + 0x14)
#घोषणा DMA_PUADR(chan)	(chan->mmr_base + 0x18)
#घोषणा DMA_LADR(chan)		(chan->mmr_base + 0x1c)
#घोषणा DMA_BCR(chan)		(chan->mmr_base + 0x20)
#घोषणा DMA_DCR(chan)		(chan->mmr_base + 0x24)

/* Application accelerator unit  */
#घोषणा AAU_ACR(chan)		(chan->mmr_base + 0x0)
#घोषणा AAU_ASR(chan)		(chan->mmr_base + 0x4)
#घोषणा AAU_ADAR(chan)		(chan->mmr_base + 0x8)
#घोषणा AAU_ANDAR(chan)	(chan->mmr_base + 0xc)
#घोषणा AAU_SAR(src, chan)	(chan->mmr_base + (0x10 + ((src) << 2)))
#घोषणा AAU_DAR(chan)		(chan->mmr_base + 0x20)
#घोषणा AAU_ABCR(chan)		(chan->mmr_base + 0x24)
#घोषणा AAU_ADCR(chan)		(chan->mmr_base + 0x28)
#घोषणा AAU_SAR_EDCR(src_edc)	(chan->mmr_base + (0x02c + ((src_edc-4) << 2)))
#घोषणा AAU_EDCR0_IDX	8
#घोषणा AAU_EDCR1_IDX	17
#घोषणा AAU_EDCR2_IDX	26

काष्ठा iop3xx_aau_desc_ctrl अणु
	अचिन्हित पूर्णांक पूर्णांक_en:1;
	अचिन्हित पूर्णांक blk1_cmd_ctrl:3;
	अचिन्हित पूर्णांक blk2_cmd_ctrl:3;
	अचिन्हित पूर्णांक blk3_cmd_ctrl:3;
	अचिन्हित पूर्णांक blk4_cmd_ctrl:3;
	अचिन्हित पूर्णांक blk5_cmd_ctrl:3;
	अचिन्हित पूर्णांक blk6_cmd_ctrl:3;
	अचिन्हित पूर्णांक blk7_cmd_ctrl:3;
	अचिन्हित पूर्णांक blk8_cmd_ctrl:3;
	अचिन्हित पूर्णांक blk_ctrl:2;
	अचिन्हित पूर्णांक dual_xor_en:1;
	अचिन्हित पूर्णांक tx_complete:1;
	अचिन्हित पूर्णांक zero_result_err:1;
	अचिन्हित पूर्णांक zero_result_en:1;
	अचिन्हित पूर्णांक dest_ग_लिखो_en:1;
पूर्ण;

काष्ठा iop3xx_aau_e_desc_ctrl अणु
	अचिन्हित पूर्णांक reserved:1;
	अचिन्हित पूर्णांक blk1_cmd_ctrl:3;
	अचिन्हित पूर्णांक blk2_cmd_ctrl:3;
	अचिन्हित पूर्णांक blk3_cmd_ctrl:3;
	अचिन्हित पूर्णांक blk4_cmd_ctrl:3;
	अचिन्हित पूर्णांक blk5_cmd_ctrl:3;
	अचिन्हित पूर्णांक blk6_cmd_ctrl:3;
	अचिन्हित पूर्णांक blk7_cmd_ctrl:3;
	अचिन्हित पूर्णांक blk8_cmd_ctrl:3;
	अचिन्हित पूर्णांक reserved2:7;
पूर्ण;

काष्ठा iop3xx_dma_desc_ctrl अणु
	अचिन्हित पूर्णांक pci_transaction:4;
	अचिन्हित पूर्णांक पूर्णांक_en:1;
	अचिन्हित पूर्णांक dac_cycle_en:1;
	अचिन्हित पूर्णांक mem_to_mem_en:1;
	अचिन्हित पूर्णांक crc_data_tx_en:1;
	अचिन्हित पूर्णांक crc_gen_en:1;
	अचिन्हित पूर्णांक crc_seed_dis:1;
	अचिन्हित पूर्णांक reserved:21;
	अचिन्हित पूर्णांक crc_tx_complete:1;
पूर्ण;

काष्ठा iop3xx_desc_dma अणु
	u32 next_desc;
	जोड़ अणु
		u32 pci_src_addr;
		u32 pci_dest_addr;
		u32 src_addr;
	पूर्ण;
	जोड़ अणु
		u32 upper_pci_src_addr;
		u32 upper_pci_dest_addr;
	पूर्ण;
	जोड़ अणु
		u32 local_pci_src_addr;
		u32 local_pci_dest_addr;
		u32 dest_addr;
	पूर्ण;
	u32 byte_count;
	जोड़ अणु
		u32 desc_ctrl;
		काष्ठा iop3xx_dma_desc_ctrl desc_ctrl_field;
	पूर्ण;
	u32 crc_addr;
पूर्ण;

काष्ठा iop3xx_desc_aau अणु
	u32 next_desc;
	u32 src[4];
	u32 dest_addr;
	u32 byte_count;
	जोड़ अणु
		u32 desc_ctrl;
		काष्ठा iop3xx_aau_desc_ctrl desc_ctrl_field;
	पूर्ण;
	जोड़ अणु
		u32 src_addr;
		u32 e_desc_ctrl;
		काष्ठा iop3xx_aau_e_desc_ctrl e_desc_ctrl_field;
	पूर्ण src_edc[31];
पूर्ण;

काष्ठा iop3xx_aau_gfmr अणु
	अचिन्हित पूर्णांक gfmr1:8;
	अचिन्हित पूर्णांक gfmr2:8;
	अचिन्हित पूर्णांक gfmr3:8;
	अचिन्हित पूर्णांक gfmr4:8;
पूर्ण;

काष्ठा iop3xx_desc_pq_xor अणु
	u32 next_desc;
	u32 src[3];
	जोड़ अणु
		u32 data_mult1;
		काष्ठा iop3xx_aau_gfmr data_mult1_field;
	पूर्ण;
	u32 dest_addr;
	u32 byte_count;
	जोड़ अणु
		u32 desc_ctrl;
		काष्ठा iop3xx_aau_desc_ctrl desc_ctrl_field;
	पूर्ण;
	जोड़ अणु
		u32 src_addr;
		u32 e_desc_ctrl;
		काष्ठा iop3xx_aau_e_desc_ctrl e_desc_ctrl_field;
		u32 data_multiplier;
		काष्ठा iop3xx_aau_gfmr data_mult_field;
		u32 reserved;
	पूर्ण src_edc_gfmr[19];
पूर्ण;

काष्ठा iop3xx_desc_dual_xor अणु
	u32 next_desc;
	u32 src0_addr;
	u32 src1_addr;
	u32 h_src_addr;
	u32 d_src_addr;
	u32 h_dest_addr;
	u32 byte_count;
	जोड़ अणु
		u32 desc_ctrl;
		काष्ठा iop3xx_aau_desc_ctrl desc_ctrl_field;
	पूर्ण;
	u32 d_dest_addr;
पूर्ण;

जोड़ iop3xx_desc अणु
	काष्ठा iop3xx_desc_aau *aau;
	काष्ठा iop3xx_desc_dma *dma;
	काष्ठा iop3xx_desc_pq_xor *pq_xor;
	काष्ठा iop3xx_desc_dual_xor *dual_xor;
	व्योम *ptr;
पूर्ण;

/* No support क्रम p+q operations */
अटल अंतरभूत पूर्णांक
iop_chan_pq_slot_count(माप_प्रकार len, पूर्णांक src_cnt, पूर्णांक *slots_per_op)
अणु
	BUG();
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम
iop_desc_init_pq(काष्ठा iop_adma_desc_slot *desc, पूर्णांक src_cnt,
		  अचिन्हित दीर्घ flags)
अणु
	BUG();
पूर्ण

अटल अंतरभूत व्योम
iop_desc_set_pq_addr(काष्ठा iop_adma_desc_slot *desc, dma_addr_t *addr)
अणु
	BUG();
पूर्ण

अटल अंतरभूत व्योम
iop_desc_set_pq_src_addr(काष्ठा iop_adma_desc_slot *desc, पूर्णांक src_idx,
			 dma_addr_t addr, अचिन्हित अक्षर coef)
अणु
	BUG();
पूर्ण

अटल अंतरभूत पूर्णांक
iop_chan_pq_zero_sum_slot_count(माप_प्रकार len, पूर्णांक src_cnt, पूर्णांक *slots_per_op)
अणु
	BUG();
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम
iop_desc_init_pq_zero_sum(काष्ठा iop_adma_desc_slot *desc, पूर्णांक src_cnt,
			  अचिन्हित दीर्घ flags)
अणु
	BUG();
पूर्ण

अटल अंतरभूत व्योम
iop_desc_set_pq_zero_sum_byte_count(काष्ठा iop_adma_desc_slot *desc, u32 len)
अणु
	BUG();
पूर्ण

#घोषणा iop_desc_set_pq_zero_sum_src_addr iop_desc_set_pq_src_addr

अटल अंतरभूत व्योम
iop_desc_set_pq_zero_sum_addr(काष्ठा iop_adma_desc_slot *desc, पूर्णांक pq_idx,
			      dma_addr_t *src)
अणु
	BUG();
पूर्ण

अटल अंतरभूत पूर्णांक iop_adma_get_max_xor(व्योम)
अणु
	वापस 32;
पूर्ण

अटल अंतरभूत पूर्णांक iop_adma_get_max_pq(व्योम)
अणु
	BUG();
	वापस 0;
पूर्ण

अटल अंतरभूत u32 iop_chan_get_current_descriptor(काष्ठा iop_adma_chan *chan)
अणु
	पूर्णांक id = chan->device->id;

	चयन (id) अणु
	हाल DMA0_ID:
	हाल DMA1_ID:
		वापस __raw_पढ़ोl(DMA_DAR(chan));
	हाल AAU_ID:
		वापस __raw_पढ़ोl(AAU_ADAR(chan));
	शेष:
		BUG();
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम iop_chan_set_next_descriptor(काष्ठा iop_adma_chan *chan,
						u32 next_desc_addr)
अणु
	पूर्णांक id = chan->device->id;

	चयन (id) अणु
	हाल DMA0_ID:
	हाल DMA1_ID:
		__raw_ग_लिखोl(next_desc_addr, DMA_NDAR(chan));
		अवरोध;
	हाल AAU_ID:
		__raw_ग_लिखोl(next_desc_addr, AAU_ANDAR(chan));
		अवरोध;
	पूर्ण

पूर्ण

#घोषणा IOP_ADMA_STATUS_BUSY (1 << 10)
#घोषणा IOP_ADMA_ZERO_SUM_MAX_BYTE_COUNT (1024)
#घोषणा IOP_ADMA_XOR_MAX_BYTE_COUNT (16 * 1024 * 1024)
#घोषणा IOP_ADMA_MAX_BYTE_COUNT (16 * 1024 * 1024)

अटल अंतरभूत पूर्णांक iop_chan_is_busy(काष्ठा iop_adma_chan *chan)
अणु
	u32 status = __raw_पढ़ोl(DMA_CSR(chan));
	वापस (status & IOP_ADMA_STATUS_BUSY) ? 1 : 0;
पूर्ण

अटल अंतरभूत पूर्णांक iop_desc_is_aligned(काष्ठा iop_adma_desc_slot *desc,
					पूर्णांक num_slots)
अणु
	/* num_slots will only ever be 1, 2, 4, or 8 */
	वापस (desc->idx & (num_slots - 1)) ? 0 : 1;
पूर्ण

/* to करो: support large (i.e. > hw max) buffer sizes */
अटल अंतरभूत पूर्णांक iop_chan_स_नकल_slot_count(माप_प्रकार len, पूर्णांक *slots_per_op)
अणु
	*slots_per_op = 1;
	वापस 1;
पूर्ण

/* to करो: support large (i.e. > hw max) buffer sizes */
अटल अंतरभूत पूर्णांक iop_chan_स_रखो_slot_count(माप_प्रकार len, पूर्णांक *slots_per_op)
अणु
	*slots_per_op = 1;
	वापस 1;
पूर्ण

अटल अंतरभूत पूर्णांक iop3xx_aau_xor_slot_count(माप_प्रकार len, पूर्णांक src_cnt,
					पूर्णांक *slots_per_op)
अणु
	अटल स्थिर अक्षर slot_count_table[] = अणु
						1, 1, 1, 1, /* 01 - 04 */
						2, 2, 2, 2, /* 05 - 08 */
						4, 4, 4, 4, /* 09 - 12 */
						4, 4, 4, 4, /* 13 - 16 */
						8, 8, 8, 8, /* 17 - 20 */
						8, 8, 8, 8, /* 21 - 24 */
						8, 8, 8, 8, /* 25 - 28 */
						8, 8, 8, 8, /* 29 - 32 */
					      पूर्ण;
	*slots_per_op = slot_count_table[src_cnt - 1];
	वापस *slots_per_op;
पूर्ण

अटल अंतरभूत पूर्णांक
iop_chan_पूर्णांकerrupt_slot_count(पूर्णांक *slots_per_op, काष्ठा iop_adma_chan *chan)
अणु
	चयन (chan->device->id) अणु
	हाल DMA0_ID:
	हाल DMA1_ID:
		वापस iop_chan_स_नकल_slot_count(0, slots_per_op);
	हाल AAU_ID:
		वापस iop3xx_aau_xor_slot_count(0, 2, slots_per_op);
	शेष:
		BUG();
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक iop_chan_xor_slot_count(माप_प्रकार len, पूर्णांक src_cnt,
						पूर्णांक *slots_per_op)
अणु
	पूर्णांक slot_cnt = iop3xx_aau_xor_slot_count(len, src_cnt, slots_per_op);

	अगर (len <= IOP_ADMA_XOR_MAX_BYTE_COUNT)
		वापस slot_cnt;

	len -= IOP_ADMA_XOR_MAX_BYTE_COUNT;
	जबतक (len > IOP_ADMA_XOR_MAX_BYTE_COUNT) अणु
		len -= IOP_ADMA_XOR_MAX_BYTE_COUNT;
		slot_cnt += *slots_per_op;
	पूर्ण

	slot_cnt += *slots_per_op;

	वापस slot_cnt;
पूर्ण

/* zero sum on iop3xx is limited to 1k at a समय so it requires multiple
 * descriptors
 */
अटल अंतरभूत पूर्णांक iop_chan_zero_sum_slot_count(माप_प्रकार len, पूर्णांक src_cnt,
						पूर्णांक *slots_per_op)
अणु
	पूर्णांक slot_cnt = iop3xx_aau_xor_slot_count(len, src_cnt, slots_per_op);

	अगर (len <= IOP_ADMA_ZERO_SUM_MAX_BYTE_COUNT)
		वापस slot_cnt;

	len -= IOP_ADMA_ZERO_SUM_MAX_BYTE_COUNT;
	जबतक (len > IOP_ADMA_ZERO_SUM_MAX_BYTE_COUNT) अणु
		len -= IOP_ADMA_ZERO_SUM_MAX_BYTE_COUNT;
		slot_cnt += *slots_per_op;
	पूर्ण

	slot_cnt += *slots_per_op;

	वापस slot_cnt;
पूर्ण

अटल अंतरभूत u32 iop_desc_get_byte_count(काष्ठा iop_adma_desc_slot *desc,
					काष्ठा iop_adma_chan *chan)
अणु
	जोड़ iop3xx_desc hw_desc = अणु .ptr = desc->hw_desc, पूर्ण;

	चयन (chan->device->id) अणु
	हाल DMA0_ID:
	हाल DMA1_ID:
		वापस hw_desc.dma->byte_count;
	हाल AAU_ID:
		वापस hw_desc.aau->byte_count;
	शेष:
		BUG();
	पूर्ण
	वापस 0;
पूर्ण

/* translate the src_idx to a descriptor word index */
अटल अंतरभूत पूर्णांक __desc_idx(पूर्णांक src_idx)
अणु
	अटल स्थिर पूर्णांक desc_idx_table[] = अणु 0, 0, 0, 0,
					      0, 1, 2, 3,
					      5, 6, 7, 8,
					      9, 10, 11, 12,
					      14, 15, 16, 17,
					      18, 19, 20, 21,
					      23, 24, 25, 26,
					      27, 28, 29, 30,
					    पूर्ण;

	वापस desc_idx_table[src_idx];
पूर्ण

अटल अंतरभूत u32 iop_desc_get_src_addr(काष्ठा iop_adma_desc_slot *desc,
					काष्ठा iop_adma_chan *chan,
					पूर्णांक src_idx)
अणु
	जोड़ iop3xx_desc hw_desc = अणु .ptr = desc->hw_desc, पूर्ण;

	चयन (chan->device->id) अणु
	हाल DMA0_ID:
	हाल DMA1_ID:
		वापस hw_desc.dma->src_addr;
	हाल AAU_ID:
		अवरोध;
	शेष:
		BUG();
	पूर्ण

	अगर (src_idx < 4)
		वापस hw_desc.aau->src[src_idx];
	अन्यथा
		वापस hw_desc.aau->src_edc[__desc_idx(src_idx)].src_addr;
पूर्ण

अटल अंतरभूत व्योम iop3xx_aau_desc_set_src_addr(काष्ठा iop3xx_desc_aau *hw_desc,
					पूर्णांक src_idx, dma_addr_t addr)
अणु
	अगर (src_idx < 4)
		hw_desc->src[src_idx] = addr;
	अन्यथा
		hw_desc->src_edc[__desc_idx(src_idx)].src_addr = addr;
पूर्ण

अटल अंतरभूत व्योम
iop_desc_init_स_नकल(काष्ठा iop_adma_desc_slot *desc, अचिन्हित दीर्घ flags)
अणु
	काष्ठा iop3xx_desc_dma *hw_desc = desc->hw_desc;
	जोड़ अणु
		u32 value;
		काष्ठा iop3xx_dma_desc_ctrl field;
	पूर्ण u_desc_ctrl;

	u_desc_ctrl.value = 0;
	u_desc_ctrl.field.mem_to_mem_en = 1;
	u_desc_ctrl.field.pci_transaction = 0xe; /* memory पढ़ो block */
	u_desc_ctrl.field.पूर्णांक_en = flags & DMA_PREP_INTERRUPT;
	hw_desc->desc_ctrl = u_desc_ctrl.value;
	hw_desc->upper_pci_src_addr = 0;
	hw_desc->crc_addr = 0;
पूर्ण

अटल अंतरभूत व्योम
iop_desc_init_स_रखो(काष्ठा iop_adma_desc_slot *desc, अचिन्हित दीर्घ flags)
अणु
	काष्ठा iop3xx_desc_aau *hw_desc = desc->hw_desc;
	जोड़ अणु
		u32 value;
		काष्ठा iop3xx_aau_desc_ctrl field;
	पूर्ण u_desc_ctrl;

	u_desc_ctrl.value = 0;
	u_desc_ctrl.field.blk1_cmd_ctrl = 0x2; /* memory block fill */
	u_desc_ctrl.field.dest_ग_लिखो_en = 1;
	u_desc_ctrl.field.पूर्णांक_en = flags & DMA_PREP_INTERRUPT;
	hw_desc->desc_ctrl = u_desc_ctrl.value;
पूर्ण

अटल अंतरभूत u32
iop3xx_desc_init_xor(काष्ठा iop3xx_desc_aau *hw_desc, पूर्णांक src_cnt,
		     अचिन्हित दीर्घ flags)
अणु
	पूर्णांक i, shअगरt;
	u32 edcr;
	जोड़ अणु
		u32 value;
		काष्ठा iop3xx_aau_desc_ctrl field;
	पूर्ण u_desc_ctrl;

	u_desc_ctrl.value = 0;
	चयन (src_cnt) अणु
	हाल 25 ... 32:
		u_desc_ctrl.field.blk_ctrl = 0x3; /* use EDCR[2:0] */
		edcr = 0;
		shअगरt = 1;
		क्रम (i = 24; i < src_cnt; i++) अणु
			edcr |= (1 << shअगरt);
			shअगरt += 3;
		पूर्ण
		hw_desc->src_edc[AAU_EDCR2_IDX].e_desc_ctrl = edcr;
		src_cnt = 24;
		fallthrough;
	हाल 17 ... 24:
		अगर (!u_desc_ctrl.field.blk_ctrl) अणु
			hw_desc->src_edc[AAU_EDCR2_IDX].e_desc_ctrl = 0;
			u_desc_ctrl.field.blk_ctrl = 0x3; /* use EDCR[2:0] */
		पूर्ण
		edcr = 0;
		shअगरt = 1;
		क्रम (i = 16; i < src_cnt; i++) अणु
			edcr |= (1 << shअगरt);
			shअगरt += 3;
		पूर्ण
		hw_desc->src_edc[AAU_EDCR1_IDX].e_desc_ctrl = edcr;
		src_cnt = 16;
		fallthrough;
	हाल 9 ... 16:
		अगर (!u_desc_ctrl.field.blk_ctrl)
			u_desc_ctrl.field.blk_ctrl = 0x2; /* use EDCR0 */
		edcr = 0;
		shअगरt = 1;
		क्रम (i = 8; i < src_cnt; i++) अणु
			edcr |= (1 << shअगरt);
			shअगरt += 3;
		पूर्ण
		hw_desc->src_edc[AAU_EDCR0_IDX].e_desc_ctrl = edcr;
		src_cnt = 8;
		fallthrough;
	हाल 2 ... 8:
		shअगरt = 1;
		क्रम (i = 0; i < src_cnt; i++) अणु
			u_desc_ctrl.value |= (1 << shअगरt);
			shअगरt += 3;
		पूर्ण

		अगर (!u_desc_ctrl.field.blk_ctrl && src_cnt > 4)
			u_desc_ctrl.field.blk_ctrl = 0x1; /* use mini-desc */
	पूर्ण

	u_desc_ctrl.field.dest_ग_लिखो_en = 1;
	u_desc_ctrl.field.blk1_cmd_ctrl = 0x7; /* direct fill */
	u_desc_ctrl.field.पूर्णांक_en = flags & DMA_PREP_INTERRUPT;
	hw_desc->desc_ctrl = u_desc_ctrl.value;

	वापस u_desc_ctrl.value;
पूर्ण

अटल अंतरभूत व्योम
iop_desc_init_xor(काष्ठा iop_adma_desc_slot *desc, पूर्णांक src_cnt,
		  अचिन्हित दीर्घ flags)
अणु
	iop3xx_desc_init_xor(desc->hw_desc, src_cnt, flags);
पूर्ण

/* वापस the number of operations */
अटल अंतरभूत पूर्णांक
iop_desc_init_zero_sum(काष्ठा iop_adma_desc_slot *desc, पूर्णांक src_cnt,
		       अचिन्हित दीर्घ flags)
अणु
	पूर्णांक slot_cnt = desc->slot_cnt, slots_per_op = desc->slots_per_op;
	काष्ठा iop3xx_desc_aau *hw_desc, *prev_hw_desc, *iter;
	जोड़ अणु
		u32 value;
		काष्ठा iop3xx_aau_desc_ctrl field;
	पूर्ण u_desc_ctrl;
	पूर्णांक i, j;

	hw_desc = desc->hw_desc;

	क्रम (i = 0, j = 0; (slot_cnt -= slots_per_op) >= 0;
		i += slots_per_op, j++) अणु
		iter = iop_hw_desc_slot_idx(hw_desc, i);
		u_desc_ctrl.value = iop3xx_desc_init_xor(iter, src_cnt, flags);
		u_desc_ctrl.field.dest_ग_लिखो_en = 0;
		u_desc_ctrl.field.zero_result_en = 1;
		u_desc_ctrl.field.पूर्णांक_en = flags & DMA_PREP_INTERRUPT;
		iter->desc_ctrl = u_desc_ctrl.value;

		/* क्रम the subsequent descriptors preserve the store queue
		 * and chain them together
		 */
		अगर (i) अणु
			prev_hw_desc =
				iop_hw_desc_slot_idx(hw_desc, i - slots_per_op);
			prev_hw_desc->next_desc =
				(u32) (desc->async_tx.phys + (i << 5));
		पूर्ण
	पूर्ण

	वापस j;
पूर्ण

अटल अंतरभूत व्योम
iop_desc_init_null_xor(काष्ठा iop_adma_desc_slot *desc, पूर्णांक src_cnt,
		       अचिन्हित दीर्घ flags)
अणु
	काष्ठा iop3xx_desc_aau *hw_desc = desc->hw_desc;
	जोड़ अणु
		u32 value;
		काष्ठा iop3xx_aau_desc_ctrl field;
	पूर्ण u_desc_ctrl;

	u_desc_ctrl.value = 0;
	चयन (src_cnt) अणु
	हाल 25 ... 32:
		u_desc_ctrl.field.blk_ctrl = 0x3; /* use EDCR[2:0] */
		hw_desc->src_edc[AAU_EDCR2_IDX].e_desc_ctrl = 0;
		fallthrough;
	हाल 17 ... 24:
		अगर (!u_desc_ctrl.field.blk_ctrl) अणु
			hw_desc->src_edc[AAU_EDCR2_IDX].e_desc_ctrl = 0;
			u_desc_ctrl.field.blk_ctrl = 0x3; /* use EDCR[2:0] */
		पूर्ण
		hw_desc->src_edc[AAU_EDCR1_IDX].e_desc_ctrl = 0;
		fallthrough;
	हाल 9 ... 16:
		अगर (!u_desc_ctrl.field.blk_ctrl)
			u_desc_ctrl.field.blk_ctrl = 0x2; /* use EDCR0 */
		hw_desc->src_edc[AAU_EDCR0_IDX].e_desc_ctrl = 0;
		fallthrough;
	हाल 1 ... 8:
		अगर (!u_desc_ctrl.field.blk_ctrl && src_cnt > 4)
			u_desc_ctrl.field.blk_ctrl = 0x1; /* use mini-desc */
	पूर्ण

	u_desc_ctrl.field.dest_ग_लिखो_en = 0;
	u_desc_ctrl.field.पूर्णांक_en = flags & DMA_PREP_INTERRUPT;
	hw_desc->desc_ctrl = u_desc_ctrl.value;
पूर्ण

अटल अंतरभूत व्योम iop_desc_set_byte_count(काष्ठा iop_adma_desc_slot *desc,
					काष्ठा iop_adma_chan *chan,
					u32 byte_count)
अणु
	जोड़ iop3xx_desc hw_desc = अणु .ptr = desc->hw_desc, पूर्ण;

	चयन (chan->device->id) अणु
	हाल DMA0_ID:
	हाल DMA1_ID:
		hw_desc.dma->byte_count = byte_count;
		अवरोध;
	हाल AAU_ID:
		hw_desc.aau->byte_count = byte_count;
		अवरोध;
	शेष:
		BUG();
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम
iop_desc_init_पूर्णांकerrupt(काष्ठा iop_adma_desc_slot *desc,
			काष्ठा iop_adma_chan *chan)
अणु
	जोड़ iop3xx_desc hw_desc = अणु .ptr = desc->hw_desc, पूर्ण;

	चयन (chan->device->id) अणु
	हाल DMA0_ID:
	हाल DMA1_ID:
		iop_desc_init_स_नकल(desc, 1);
		hw_desc.dma->byte_count = 0;
		hw_desc.dma->dest_addr = 0;
		hw_desc.dma->src_addr = 0;
		अवरोध;
	हाल AAU_ID:
		iop_desc_init_null_xor(desc, 2, 1);
		hw_desc.aau->byte_count = 0;
		hw_desc.aau->dest_addr = 0;
		hw_desc.aau->src[0] = 0;
		hw_desc.aau->src[1] = 0;
		अवरोध;
	शेष:
		BUG();
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम
iop_desc_set_zero_sum_byte_count(काष्ठा iop_adma_desc_slot *desc, u32 len)
अणु
	पूर्णांक slots_per_op = desc->slots_per_op;
	काष्ठा iop3xx_desc_aau *hw_desc = desc->hw_desc, *iter;
	पूर्णांक i = 0;

	अगर (len <= IOP_ADMA_ZERO_SUM_MAX_BYTE_COUNT) अणु
		hw_desc->byte_count = len;
	पूर्ण अन्यथा अणु
		करो अणु
			iter = iop_hw_desc_slot_idx(hw_desc, i);
			iter->byte_count = IOP_ADMA_ZERO_SUM_MAX_BYTE_COUNT;
			len -= IOP_ADMA_ZERO_SUM_MAX_BYTE_COUNT;
			i += slots_per_op;
		पूर्ण जबतक (len > IOP_ADMA_ZERO_SUM_MAX_BYTE_COUNT);

		iter = iop_hw_desc_slot_idx(hw_desc, i);
		iter->byte_count = len;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम iop_desc_set_dest_addr(काष्ठा iop_adma_desc_slot *desc,
					काष्ठा iop_adma_chan *chan,
					dma_addr_t addr)
अणु
	जोड़ iop3xx_desc hw_desc = अणु .ptr = desc->hw_desc, पूर्ण;

	चयन (chan->device->id) अणु
	हाल DMA0_ID:
	हाल DMA1_ID:
		hw_desc.dma->dest_addr = addr;
		अवरोध;
	हाल AAU_ID:
		hw_desc.aau->dest_addr = addr;
		अवरोध;
	शेष:
		BUG();
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम iop_desc_set_स_नकल_src_addr(काष्ठा iop_adma_desc_slot *desc,
					dma_addr_t addr)
अणु
	काष्ठा iop3xx_desc_dma *hw_desc = desc->hw_desc;
	hw_desc->src_addr = addr;
पूर्ण

अटल अंतरभूत व्योम
iop_desc_set_zero_sum_src_addr(काष्ठा iop_adma_desc_slot *desc, पूर्णांक src_idx,
				dma_addr_t addr)
अणु

	काष्ठा iop3xx_desc_aau *hw_desc = desc->hw_desc, *iter;
	पूर्णांक slot_cnt = desc->slot_cnt, slots_per_op = desc->slots_per_op;
	पूर्णांक i;

	क्रम (i = 0; (slot_cnt -= slots_per_op) >= 0;
		i += slots_per_op, addr += IOP_ADMA_ZERO_SUM_MAX_BYTE_COUNT) अणु
		iter = iop_hw_desc_slot_idx(hw_desc, i);
		iop3xx_aau_desc_set_src_addr(iter, src_idx, addr);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम iop_desc_set_xor_src_addr(काष्ठा iop_adma_desc_slot *desc,
					पूर्णांक src_idx, dma_addr_t addr)
अणु

	काष्ठा iop3xx_desc_aau *hw_desc = desc->hw_desc, *iter;
	पूर्णांक slot_cnt = desc->slot_cnt, slots_per_op = desc->slots_per_op;
	पूर्णांक i;

	क्रम (i = 0; (slot_cnt -= slots_per_op) >= 0;
		i += slots_per_op, addr += IOP_ADMA_XOR_MAX_BYTE_COUNT) अणु
		iter = iop_hw_desc_slot_idx(hw_desc, i);
		iop3xx_aau_desc_set_src_addr(iter, src_idx, addr);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम iop_desc_set_next_desc(काष्ठा iop_adma_desc_slot *desc,
					u32 next_desc_addr)
अणु
	/* hw_desc->next_desc is the same location क्रम all channels */
	जोड़ iop3xx_desc hw_desc = अणु .ptr = desc->hw_desc, पूर्ण;

	iop_paranoia(hw_desc.dma->next_desc);
	hw_desc.dma->next_desc = next_desc_addr;
पूर्ण

अटल अंतरभूत u32 iop_desc_get_next_desc(काष्ठा iop_adma_desc_slot *desc)
अणु
	/* hw_desc->next_desc is the same location क्रम all channels */
	जोड़ iop3xx_desc hw_desc = अणु .ptr = desc->hw_desc, पूर्ण;
	वापस hw_desc.dma->next_desc;
पूर्ण

अटल अंतरभूत व्योम iop_desc_clear_next_desc(काष्ठा iop_adma_desc_slot *desc)
अणु
	/* hw_desc->next_desc is the same location क्रम all channels */
	जोड़ iop3xx_desc hw_desc = अणु .ptr = desc->hw_desc, पूर्ण;
	hw_desc.dma->next_desc = 0;
पूर्ण

अटल अंतरभूत व्योम iop_desc_set_block_fill_val(काष्ठा iop_adma_desc_slot *desc,
						u32 val)
अणु
	काष्ठा iop3xx_desc_aau *hw_desc = desc->hw_desc;
	hw_desc->src[0] = val;
पूर्ण

अटल अंतरभूत क्रमागत sum_check_flags
iop_desc_get_zero_result(काष्ठा iop_adma_desc_slot *desc)
अणु
	काष्ठा iop3xx_desc_aau *hw_desc = desc->hw_desc;
	काष्ठा iop3xx_aau_desc_ctrl desc_ctrl = hw_desc->desc_ctrl_field;

	iop_paranoia(!(desc_ctrl.tx_complete && desc_ctrl.zero_result_en));
	वापस desc_ctrl.zero_result_err << SUM_CHECK_P;
पूर्ण

अटल अंतरभूत व्योम iop_chan_append(काष्ठा iop_adma_chan *chan)
अणु
	u32 dma_chan_ctrl;

	dma_chan_ctrl = __raw_पढ़ोl(DMA_CCR(chan));
	dma_chan_ctrl |= 0x2;
	__raw_ग_लिखोl(dma_chan_ctrl, DMA_CCR(chan));
पूर्ण

अटल अंतरभूत u32 iop_chan_get_status(काष्ठा iop_adma_chan *chan)
अणु
	वापस __raw_पढ़ोl(DMA_CSR(chan));
पूर्ण

अटल अंतरभूत व्योम iop_chan_disable(काष्ठा iop_adma_chan *chan)
अणु
	u32 dma_chan_ctrl = __raw_पढ़ोl(DMA_CCR(chan));
	dma_chan_ctrl &= ~1;
	__raw_ग_लिखोl(dma_chan_ctrl, DMA_CCR(chan));
पूर्ण

अटल अंतरभूत व्योम iop_chan_enable(काष्ठा iop_adma_chan *chan)
अणु
	u32 dma_chan_ctrl = __raw_पढ़ोl(DMA_CCR(chan));

	dma_chan_ctrl |= 1;
	__raw_ग_लिखोl(dma_chan_ctrl, DMA_CCR(chan));
पूर्ण

अटल अंतरभूत व्योम iop_adma_device_clear_eot_status(काष्ठा iop_adma_chan *chan)
अणु
	u32 status = __raw_पढ़ोl(DMA_CSR(chan));
	status &= (1 << 9);
	__raw_ग_लिखोl(status, DMA_CSR(chan));
पूर्ण

अटल अंतरभूत व्योम iop_adma_device_clear_eoc_status(काष्ठा iop_adma_chan *chan)
अणु
	u32 status = __raw_पढ़ोl(DMA_CSR(chan));
	status &= (1 << 8);
	__raw_ग_लिखोl(status, DMA_CSR(chan));
पूर्ण

अटल अंतरभूत व्योम iop_adma_device_clear_err_status(काष्ठा iop_adma_chan *chan)
अणु
	u32 status = __raw_पढ़ोl(DMA_CSR(chan));

	चयन (chan->device->id) अणु
	हाल DMA0_ID:
	हाल DMA1_ID:
		status &= (1 << 5) | (1 << 3) | (1 << 2) | (1 << 1);
		अवरोध;
	हाल AAU_ID:
		status &= (1 << 5);
		अवरोध;
	शेष:
		BUG();
	पूर्ण

	__raw_ग_लिखोl(status, DMA_CSR(chan));
पूर्ण

अटल अंतरभूत पूर्णांक
iop_is_err_पूर्णांक_parity(अचिन्हित दीर्घ status, काष्ठा iop_adma_chan *chan)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक
iop_is_err_mcu_पात(अचिन्हित दीर्घ status, काष्ठा iop_adma_chan *chan)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक
iop_is_err_पूर्णांक_tपात(अचिन्हित दीर्घ status, काष्ठा iop_adma_chan *chan)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक
iop_is_err_पूर्णांक_mपात(अचिन्हित दीर्घ status, काष्ठा iop_adma_chan *chan)
अणु
	वापस test_bit(5, &status);
पूर्ण

अटल अंतरभूत पूर्णांक
iop_is_err_pci_tपात(अचिन्हित दीर्घ status, काष्ठा iop_adma_chan *chan)
अणु
	चयन (chan->device->id) अणु
	हाल DMA0_ID:
	हाल DMA1_ID:
		वापस test_bit(2, &status);
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक
iop_is_err_pci_mपात(अचिन्हित दीर्घ status, काष्ठा iop_adma_chan *chan)
अणु
	चयन (chan->device->id) अणु
	हाल DMA0_ID:
	हाल DMA1_ID:
		वापस test_bit(3, &status);
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक
iop_is_err_split_tx(अचिन्हित दीर्घ status, काष्ठा iop_adma_chan *chan)
अणु
	चयन (chan->device->id) अणु
	हाल DMA0_ID:
	हाल DMA1_ID:
		वापस test_bit(1, &status);
	शेष:
		वापस 0;
	पूर्ण
पूर्ण
#पूर्ण_अगर /* _ADMA_H */
