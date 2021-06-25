<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * QLogic qlcnic NIC Driver
 * Copyright (c) 2009-2013 QLogic Corporation
 */

#समावेश <net/ip.h>

#समावेश "qlcnic.h"
#समावेश "qlcnic_hdr.h"
#समावेश "qlcnic_83xx_hw.h"
#समावेश "qlcnic_hw.h"

#घोषणा QLC_83XX_MINIDUMP_FLASH		0x520000
#घोषणा QLC_83XX_OCM_INDEX			3
#घोषणा QLC_83XX_PCI_INDEX			0
#घोषणा QLC_83XX_DMA_ENGINE_INDEX		8

अटल स्थिर u32 qlcnic_ms_पढ़ो_data[] = अणु
	0x410000A8, 0x410000AC, 0x410000B8, 0x410000BC
पूर्ण;

#घोषणा QLCNIC_DUMP_WCRB	BIT_0
#घोषणा QLCNIC_DUMP_RWCRB	BIT_1
#घोषणा QLCNIC_DUMP_ANDCRB	BIT_2
#घोषणा QLCNIC_DUMP_ORCRB	BIT_3
#घोषणा QLCNIC_DUMP_POLLCRB	BIT_4
#घोषणा QLCNIC_DUMP_RD_SAVE	BIT_5
#घोषणा QLCNIC_DUMP_WRT_SAVED	BIT_6
#घोषणा QLCNIC_DUMP_MOD_SAVE_ST	BIT_7
#घोषणा QLCNIC_DUMP_SKIP	BIT_7

#घोषणा QLCNIC_DUMP_MASK_MAX	0xff

काष्ठा qlcnic_pex_dma_descriptor अणु
	u32	पढ़ो_data_size;
	u32	dma_desc_cmd;
	u32	src_addr_low;
	u32	src_addr_high;
	u32	dma_bus_addr_low;
	u32	dma_bus_addr_high;
	u32	rsvd[6];
पूर्ण __packed;

काष्ठा qlcnic_common_entry_hdr अणु
	u32     type;
	u32     offset;
	u32     cap_size;
#अगर defined(__LITTLE_ENDIAN)
	u8      mask;
	u8      rsvd[2];
	u8      flags;
#अन्यथा
	u8      flags;
	u8      rsvd[2];
	u8      mask;
#पूर्ण_अगर
पूर्ण __packed;

काष्ठा __crb अणु
	u32	addr;
#अगर defined(__LITTLE_ENDIAN)
	u8	stride;
	u8	rsvd1[3];
#अन्यथा
	u8	rsvd1[3];
	u8	stride;
#पूर्ण_अगर
	u32	data_size;
	u32	no_ops;
	u32	rsvd2[4];
पूर्ण __packed;

काष्ठा __ctrl अणु
	u32	addr;
#अगर defined(__LITTLE_ENDIAN)
	u8	stride;
	u8	index_a;
	u16	समयout;
#अन्यथा
	u16	समयout;
	u8	index_a;
	u8	stride;
#पूर्ण_अगर
	u32	data_size;
	u32	no_ops;
#अगर defined(__LITTLE_ENDIAN)
	u8	opcode;
	u8	index_v;
	u8	shl_val;
	u8	shr_val;
#अन्यथा
	u8	shr_val;
	u8	shl_val;
	u8	index_v;
	u8	opcode;
#पूर्ण_अगर
	u32	val1;
	u32	val2;
	u32	val3;
पूर्ण __packed;

काष्ठा __cache अणु
	u32	addr;
#अगर defined(__LITTLE_ENDIAN)
	u16	stride;
	u16	init_tag_val;
#अन्यथा
	u16	init_tag_val;
	u16	stride;
#पूर्ण_अगर
	u32	size;
	u32	no_ops;
	u32	ctrl_addr;
	u32	ctrl_val;
	u32	पढ़ो_addr;
#अगर defined(__LITTLE_ENDIAN)
	u8	पढ़ो_addr_stride;
	u8	पढ़ो_addr_num;
	u8	rsvd1[2];
#अन्यथा
	u8	rsvd1[2];
	u8	पढ़ो_addr_num;
	u8	पढ़ो_addr_stride;
#पूर्ण_अगर
पूर्ण __packed;

काष्ठा __ocm अणु
	u8	rsvd[8];
	u32	size;
	u32	no_ops;
	u8	rsvd1[8];
	u32	पढ़ो_addr;
	u32	पढ़ो_addr_stride;
पूर्ण __packed;

काष्ठा __mem अणु
	u32	desc_card_addr;
	u32	dma_desc_cmd;
	u32	start_dma_cmd;
	u32	rsvd[3];
	u32	addr;
	u32	size;
पूर्ण __packed;

काष्ठा __mux अणु
	u32	addr;
	u8	rsvd[4];
	u32	size;
	u32	no_ops;
	u32	val;
	u32	val_stride;
	u32	पढ़ो_addr;
	u8	rsvd2[4];
पूर्ण __packed;

काष्ठा __queue अणु
	u32	sel_addr;
#अगर defined(__LITTLE_ENDIAN)
	u16	stride;
	u8	rsvd[2];
#अन्यथा
	u8	rsvd[2];
	u16	stride;
#पूर्ण_अगर
	u32	size;
	u32	no_ops;
	u8	rsvd2[8];
	u32	पढ़ो_addr;
#अगर defined(__LITTLE_ENDIAN)
	u8	पढ़ो_addr_stride;
	u8	पढ़ो_addr_cnt;
	u8	rsvd3[2];
#अन्यथा
	u8	rsvd3[2];
	u8	पढ़ो_addr_cnt;
	u8	पढ़ो_addr_stride;
#पूर्ण_अगर
पूर्ण __packed;

काष्ठा __pollrd अणु
	u32	sel_addr;
	u32	पढ़ो_addr;
	u32	sel_val;
#अगर defined(__LITTLE_ENDIAN)
	u16	sel_val_stride;
	u16	no_ops;
#अन्यथा
	u16	no_ops;
	u16	sel_val_stride;
#पूर्ण_अगर
	u32	poll_रुको;
	u32	poll_mask;
	u32	data_size;
	u8	rsvd[4];
पूर्ण __packed;

काष्ठा __mux2 अणु
	u32	sel_addr1;
	u32	sel_addr2;
	u32	sel_val1;
	u32	sel_val2;
	u32	no_ops;
	u32	sel_val_mask;
	u32	पढ़ो_addr;
#अगर defined(__LITTLE_ENDIAN)
	u8	sel_val_stride;
	u8	data_size;
	u8	rsvd[2];
#अन्यथा
	u8	rsvd[2];
	u8	data_size;
	u8	sel_val_stride;
#पूर्ण_अगर
पूर्ण __packed;

काष्ठा __pollrdmwr अणु
	u32	addr1;
	u32	addr2;
	u32	val1;
	u32	val2;
	u32	poll_रुको;
	u32	poll_mask;
	u32	mod_mask;
	u32	data_size;
पूर्ण __packed;

काष्ठा qlcnic_dump_entry अणु
	काष्ठा qlcnic_common_entry_hdr hdr;
	जोड़ अणु
		काष्ठा __crb		crb;
		काष्ठा __cache		cache;
		काष्ठा __ocm		ocm;
		काष्ठा __mem		mem;
		काष्ठा __mux		mux;
		काष्ठा __queue		que;
		काष्ठा __ctrl		ctrl;
		काष्ठा __pollrdmwr	pollrdmwr;
		काष्ठा __mux2		mux2;
		काष्ठा __pollrd		pollrd;
	पूर्ण region;
पूर्ण __packed;

क्रमागत qlcnic_minidump_opcode अणु
	QLCNIC_DUMP_NOP		= 0,
	QLCNIC_DUMP_READ_CRB	= 1,
	QLCNIC_DUMP_READ_MUX	= 2,
	QLCNIC_DUMP_QUEUE	= 3,
	QLCNIC_DUMP_BRD_CONFIG	= 4,
	QLCNIC_DUMP_READ_OCM	= 6,
	QLCNIC_DUMP_PEG_REG	= 7,
	QLCNIC_DUMP_L1_DTAG	= 8,
	QLCNIC_DUMP_L1_ITAG	= 9,
	QLCNIC_DUMP_L1_DATA	= 11,
	QLCNIC_DUMP_L1_INST	= 12,
	QLCNIC_DUMP_L2_DTAG	= 21,
	QLCNIC_DUMP_L2_ITAG	= 22,
	QLCNIC_DUMP_L2_DATA	= 23,
	QLCNIC_DUMP_L2_INST	= 24,
	QLCNIC_DUMP_POLL_RD	= 35,
	QLCNIC_READ_MUX2	= 36,
	QLCNIC_READ_POLLRDMWR	= 37,
	QLCNIC_DUMP_READ_ROM	= 71,
	QLCNIC_DUMP_READ_MEM	= 72,
	QLCNIC_DUMP_READ_CTRL	= 98,
	QLCNIC_DUMP_TLHDR	= 99,
	QLCNIC_DUMP_RDEND	= 255
पूर्ण;

अंतरभूत u32 qlcnic_82xx_get_saved_state(व्योम *t_hdr, u32 index)
अणु
	काष्ठा qlcnic_82xx_dump_ढाँचा_hdr *hdr = t_hdr;

	वापस hdr->saved_state[index];
पूर्ण

अंतरभूत व्योम qlcnic_82xx_set_saved_state(व्योम *t_hdr, u32 index,
					u32 value)
अणु
	काष्ठा qlcnic_82xx_dump_ढाँचा_hdr *hdr = t_hdr;

	hdr->saved_state[index] = value;
पूर्ण

व्योम qlcnic_82xx_cache_पंचांगpl_hdr_values(काष्ठा qlcnic_fw_dump *fw_dump)
अणु
	काष्ठा qlcnic_82xx_dump_ढाँचा_hdr *hdr;

	hdr = fw_dump->पंचांगpl_hdr;
	fw_dump->पंचांगpl_hdr_size = hdr->size;
	fw_dump->version = hdr->version;
	fw_dump->num_entries = hdr->num_entries;
	fw_dump->offset = hdr->offset;

	hdr->drv_cap_mask = hdr->cap_mask;
	fw_dump->cap_mask = hdr->cap_mask;

	fw_dump->use_pex_dma = (hdr->capabilities & BIT_0) ? true : false;
पूर्ण

अंतरभूत u32 qlcnic_82xx_get_cap_size(व्योम *t_hdr, पूर्णांक index)
अणु
	काष्ठा qlcnic_82xx_dump_ढाँचा_hdr *hdr = t_hdr;

	वापस hdr->cap_sizes[index];
पूर्ण

व्योम qlcnic_82xx_set_sys_info(व्योम *t_hdr, पूर्णांक idx, u32 value)
अणु
	काष्ठा qlcnic_82xx_dump_ढाँचा_hdr *hdr = t_hdr;

	hdr->sys_info[idx] = value;
पूर्ण

व्योम qlcnic_82xx_store_cap_mask(व्योम *पंचांगpl_hdr, u32 mask)
अणु
	काष्ठा qlcnic_82xx_dump_ढाँचा_hdr *hdr = पंचांगpl_hdr;

	hdr->drv_cap_mask = mask;
पूर्ण

अंतरभूत u32 qlcnic_83xx_get_saved_state(व्योम *t_hdr, u32 index)
अणु
	काष्ठा qlcnic_83xx_dump_ढाँचा_hdr *hdr = t_hdr;

	वापस hdr->saved_state[index];
पूर्ण

अंतरभूत व्योम qlcnic_83xx_set_saved_state(व्योम *t_hdr, u32 index,
					u32 value)
अणु
	काष्ठा qlcnic_83xx_dump_ढाँचा_hdr *hdr = t_hdr;

	hdr->saved_state[index] = value;
पूर्ण

#घोषणा QLCNIC_TEMPLATE_VERSION (0x20001)

व्योम qlcnic_83xx_cache_पंचांगpl_hdr_values(काष्ठा qlcnic_fw_dump *fw_dump)
अणु
	काष्ठा qlcnic_83xx_dump_ढाँचा_hdr *hdr;

	hdr = fw_dump->पंचांगpl_hdr;
	fw_dump->पंचांगpl_hdr_size = hdr->size;
	fw_dump->version = hdr->version;
	fw_dump->num_entries = hdr->num_entries;
	fw_dump->offset = hdr->offset;

	hdr->drv_cap_mask = hdr->cap_mask;
	fw_dump->cap_mask = hdr->cap_mask;

	fw_dump->use_pex_dma = (fw_dump->version & 0xfffff) >=
			       QLCNIC_TEMPLATE_VERSION;
पूर्ण

अंतरभूत u32 qlcnic_83xx_get_cap_size(व्योम *t_hdr, पूर्णांक index)
अणु
	काष्ठा qlcnic_83xx_dump_ढाँचा_hdr *hdr = t_hdr;

	वापस hdr->cap_sizes[index];
पूर्ण

व्योम qlcnic_83xx_set_sys_info(व्योम *t_hdr, पूर्णांक idx, u32 value)
अणु
	काष्ठा qlcnic_83xx_dump_ढाँचा_hdr *hdr = t_hdr;

	hdr->sys_info[idx] = value;
पूर्ण

व्योम qlcnic_83xx_store_cap_mask(व्योम *पंचांगpl_hdr, u32 mask)
अणु
	काष्ठा qlcnic_83xx_dump_ढाँचा_hdr *hdr;

	hdr = पंचांगpl_hdr;
	hdr->drv_cap_mask = mask;
पूर्ण

काष्ठा qlcnic_dump_operations अणु
	क्रमागत qlcnic_minidump_opcode opcode;
	u32 (*handler)(काष्ठा qlcnic_adapter *, काष्ठा qlcnic_dump_entry *,
		       __le32 *);
पूर्ण;

अटल u32 qlcnic_dump_crb(काष्ठा qlcnic_adapter *adapter,
			   काष्ठा qlcnic_dump_entry *entry, __le32 *buffer)
अणु
	पूर्णांक i;
	u32 addr, data;
	काष्ठा __crb *crb = &entry->region.crb;

	addr = crb->addr;

	क्रम (i = 0; i < crb->no_ops; i++) अणु
		data = qlcnic_ind_rd(adapter, addr);
		*buffer++ = cpu_to_le32(addr);
		*buffer++ = cpu_to_le32(data);
		addr += crb->stride;
	पूर्ण
	वापस crb->no_ops * 2 * माप(u32);
पूर्ण

अटल u32 qlcnic_dump_ctrl(काष्ठा qlcnic_adapter *adapter,
			    काष्ठा qlcnic_dump_entry *entry, __le32 *buffer)
अणु
	व्योम *hdr = adapter->ahw->fw_dump.पंचांगpl_hdr;
	काष्ठा __ctrl *ctr = &entry->region.ctrl;
	पूर्णांक i, k, समयout = 0;
	u32 addr, data, temp;
	u8 no_ops;

	addr = ctr->addr;
	no_ops = ctr->no_ops;

	क्रम (i = 0; i < no_ops; i++) अणु
		k = 0;
		क्रम (k = 0; k < 8; k++) अणु
			अगर (!(ctr->opcode & (1 << k)))
				जारी;
			चयन (1 << k) अणु
			हाल QLCNIC_DUMP_WCRB:
				qlcnic_ind_wr(adapter, addr, ctr->val1);
				अवरोध;
			हाल QLCNIC_DUMP_RWCRB:
				data = qlcnic_ind_rd(adapter, addr);
				qlcnic_ind_wr(adapter, addr, data);
				अवरोध;
			हाल QLCNIC_DUMP_ANDCRB:
				data = qlcnic_ind_rd(adapter, addr);
				qlcnic_ind_wr(adapter, addr,
					      (data & ctr->val2));
				अवरोध;
			हाल QLCNIC_DUMP_ORCRB:
				data = qlcnic_ind_rd(adapter, addr);
				qlcnic_ind_wr(adapter, addr,
					      (data | ctr->val3));
				अवरोध;
			हाल QLCNIC_DUMP_POLLCRB:
				जबतक (समयout <= ctr->समयout) अणु
					data = qlcnic_ind_rd(adapter, addr);
					अगर ((data & ctr->val2) == ctr->val1)
						अवरोध;
					usleep_range(1000, 2000);
					समयout++;
				पूर्ण
				अगर (समयout > ctr->समयout) अणु
					dev_info(&adapter->pdev->dev,
					"Timed out, aborting poll CRB\n");
					वापस -EINVAL;
				पूर्ण
				अवरोध;
			हाल QLCNIC_DUMP_RD_SAVE:
				temp = ctr->index_a;
				अगर (temp)
					addr = qlcnic_get_saved_state(adapter,
								      hdr,
								      temp);
				data = qlcnic_ind_rd(adapter, addr);
				qlcnic_set_saved_state(adapter, hdr,
						       ctr->index_v, data);
				अवरोध;
			हाल QLCNIC_DUMP_WRT_SAVED:
				temp = ctr->index_v;
				अगर (temp)
					data = qlcnic_get_saved_state(adapter,
								      hdr,
								      temp);
				अन्यथा
					data = ctr->val1;

				temp = ctr->index_a;
				अगर (temp)
					addr = qlcnic_get_saved_state(adapter,
								      hdr,
								      temp);
				qlcnic_ind_wr(adapter, addr, data);
				अवरोध;
			हाल QLCNIC_DUMP_MOD_SAVE_ST:
				data = qlcnic_get_saved_state(adapter, hdr,
							      ctr->index_v);
				data <<= ctr->shl_val;
				data >>= ctr->shr_val;
				अगर (ctr->val2)
					data &= ctr->val2;
				data |= ctr->val3;
				data += ctr->val1;
				qlcnic_set_saved_state(adapter, hdr,
						       ctr->index_v, data);
				अवरोध;
			शेष:
				dev_info(&adapter->pdev->dev,
					 "Unknown opcode\n");
				अवरोध;
			पूर्ण
		पूर्ण
		addr += ctr->stride;
	पूर्ण
	वापस 0;
पूर्ण

अटल u32 qlcnic_dump_mux(काष्ठा qlcnic_adapter *adapter,
			   काष्ठा qlcnic_dump_entry *entry, __le32 *buffer)
अणु
	पूर्णांक loop;
	u32 val, data = 0;
	काष्ठा __mux *mux = &entry->region.mux;

	val = mux->val;
	क्रम (loop = 0; loop < mux->no_ops; loop++) अणु
		qlcnic_ind_wr(adapter, mux->addr, val);
		data = qlcnic_ind_rd(adapter, mux->पढ़ो_addr);
		*buffer++ = cpu_to_le32(val);
		*buffer++ = cpu_to_le32(data);
		val += mux->val_stride;
	पूर्ण
	वापस 2 * mux->no_ops * माप(u32);
पूर्ण

अटल u32 qlcnic_dump_que(काष्ठा qlcnic_adapter *adapter,
			   काष्ठा qlcnic_dump_entry *entry, __le32 *buffer)
अणु
	पूर्णांक i, loop;
	u32 cnt, addr, data, que_id = 0;
	काष्ठा __queue *que = &entry->region.que;

	addr = que->पढ़ो_addr;
	cnt = que->पढ़ो_addr_cnt;

	क्रम (loop = 0; loop < que->no_ops; loop++) अणु
		qlcnic_ind_wr(adapter, que->sel_addr, que_id);
		addr = que->पढ़ो_addr;
		क्रम (i = 0; i < cnt; i++) अणु
			data = qlcnic_ind_rd(adapter, addr);
			*buffer++ = cpu_to_le32(data);
			addr += que->पढ़ो_addr_stride;
		पूर्ण
		que_id += que->stride;
	पूर्ण
	वापस que->no_ops * cnt * माप(u32);
पूर्ण

अटल u32 qlcnic_dump_ocm(काष्ठा qlcnic_adapter *adapter,
			   काष्ठा qlcnic_dump_entry *entry, __le32 *buffer)
अणु
	पूर्णांक i;
	u32 data;
	व्योम __iomem *addr;
	काष्ठा __ocm *ocm = &entry->region.ocm;

	addr = adapter->ahw->pci_base0 + ocm->पढ़ो_addr;
	क्रम (i = 0; i < ocm->no_ops; i++) अणु
		data = पढ़ोl(addr);
		*buffer++ = cpu_to_le32(data);
		addr += ocm->पढ़ो_addr_stride;
	पूर्ण
	वापस ocm->no_ops * माप(u32);
पूर्ण

अटल u32 qlcnic_पढ़ो_rom(काष्ठा qlcnic_adapter *adapter,
			   काष्ठा qlcnic_dump_entry *entry, __le32 *buffer)
अणु
	पूर्णांक i, count = 0;
	u32 fl_addr, size, val, lck_val, addr;
	काष्ठा __mem *rom = &entry->region.mem;

	fl_addr = rom->addr;
	size = rom->size / 4;
lock_try:
	lck_val = QLC_SHARED_REG_RD32(adapter, QLCNIC_FLASH_LOCK);
	अगर (!lck_val && count < MAX_CTL_CHECK) अणु
		usleep_range(10000, 11000);
		count++;
		जाओ lock_try;
	पूर्ण
	QLC_SHARED_REG_WR32(adapter, QLCNIC_FLASH_LOCK_OWNER,
			    adapter->ahw->pci_func);
	क्रम (i = 0; i < size; i++) अणु
		addr = fl_addr & 0xFFFF0000;
		qlcnic_ind_wr(adapter, FLASH_ROM_WINDOW, addr);
		addr = LSW(fl_addr) + FLASH_ROM_DATA;
		val = qlcnic_ind_rd(adapter, addr);
		fl_addr += 4;
		*buffer++ = cpu_to_le32(val);
	पूर्ण
	QLC_SHARED_REG_RD32(adapter, QLCNIC_FLASH_UNLOCK);
	वापस rom->size;
पूर्ण

अटल u32 qlcnic_dump_l1_cache(काष्ठा qlcnic_adapter *adapter,
				काष्ठा qlcnic_dump_entry *entry, __le32 *buffer)
अणु
	पूर्णांक i;
	u32 cnt, val, data, addr;
	काष्ठा __cache *l1 = &entry->region.cache;

	val = l1->init_tag_val;

	क्रम (i = 0; i < l1->no_ops; i++) अणु
		qlcnic_ind_wr(adapter, l1->addr, val);
		qlcnic_ind_wr(adapter, l1->ctrl_addr, LSW(l1->ctrl_val));
		addr = l1->पढ़ो_addr;
		cnt = l1->पढ़ो_addr_num;
		जबतक (cnt) अणु
			data = qlcnic_ind_rd(adapter, addr);
			*buffer++ = cpu_to_le32(data);
			addr += l1->पढ़ो_addr_stride;
			cnt--;
		पूर्ण
		val += l1->stride;
	पूर्ण
	वापस l1->no_ops * l1->पढ़ो_addr_num * माप(u32);
पूर्ण

अटल u32 qlcnic_dump_l2_cache(काष्ठा qlcnic_adapter *adapter,
				काष्ठा qlcnic_dump_entry *entry, __le32 *buffer)
अणु
	पूर्णांक i;
	u32 cnt, val, data, addr;
	u8 poll_mask, poll_to, समय_out = 0;
	काष्ठा __cache *l2 = &entry->region.cache;

	val = l2->init_tag_val;
	poll_mask = LSB(MSW(l2->ctrl_val));
	poll_to = MSB(MSW(l2->ctrl_val));

	क्रम (i = 0; i < l2->no_ops; i++) अणु
		qlcnic_ind_wr(adapter, l2->addr, val);
		अगर (LSW(l2->ctrl_val))
			qlcnic_ind_wr(adapter, l2->ctrl_addr,
				      LSW(l2->ctrl_val));
		अगर (!poll_mask)
			जाओ skip_poll;
		करो अणु
			data = qlcnic_ind_rd(adapter, l2->ctrl_addr);
			अगर (!(data & poll_mask))
				अवरोध;
			usleep_range(1000, 2000);
			समय_out++;
		पूर्ण जबतक (समय_out <= poll_to);

		अगर (समय_out > poll_to) अणु
			dev_err(&adapter->pdev->dev,
				"Timeout exceeded in %s, aborting dump\n",
				__func__);
			वापस -EINVAL;
		पूर्ण
skip_poll:
		addr = l2->पढ़ो_addr;
		cnt = l2->पढ़ो_addr_num;
		जबतक (cnt) अणु
			data = qlcnic_ind_rd(adapter, addr);
			*buffer++ = cpu_to_le32(data);
			addr += l2->पढ़ो_addr_stride;
			cnt--;
		पूर्ण
		val += l2->stride;
	पूर्ण
	वापस l2->no_ops * l2->पढ़ो_addr_num * माप(u32);
पूर्ण

अटल u32 qlcnic_पढ़ो_memory_test_agent(काष्ठा qlcnic_adapter *adapter,
					 काष्ठा __mem *mem, __le32 *buffer,
					 पूर्णांक *ret)
अणु
	u32 addr, data, test;
	पूर्णांक i, reg_पढ़ो;

	reg_पढ़ो = mem->size;
	addr = mem->addr;
	/* check क्रम data size of multiple of 16 and 16 byte alignment */
	अगर ((addr & 0xf) || (reg_पढ़ो%16)) अणु
		dev_info(&adapter->pdev->dev,
			 "Unaligned memory addr:0x%x size:0x%x\n",
			 addr, reg_पढ़ो);
		*ret = -EINVAL;
		वापस 0;
	पूर्ण

	mutex_lock(&adapter->ahw->mem_lock);

	जबतक (reg_पढ़ो != 0) अणु
		qlcnic_ind_wr(adapter, QLCNIC_MS_ADDR_LO, addr);
		qlcnic_ind_wr(adapter, QLCNIC_MS_ADDR_HI, 0);
		qlcnic_ind_wr(adapter, QLCNIC_MS_CTRL, QLCNIC_TA_START_ENABLE);

		क्रम (i = 0; i < MAX_CTL_CHECK; i++) अणु
			test = qlcnic_ind_rd(adapter, QLCNIC_MS_CTRL);
			अगर (!(test & TA_CTL_BUSY))
				अवरोध;
		पूर्ण
		अगर (i == MAX_CTL_CHECK) अणु
			अगर (prपूर्णांकk_ratelimit()) अणु
				dev_err(&adapter->pdev->dev,
					"failed to read through agent\n");
				*ret = -EIO;
				जाओ out;
			पूर्ण
		पूर्ण
		क्रम (i = 0; i < 4; i++) अणु
			data = qlcnic_ind_rd(adapter, qlcnic_ms_पढ़ो_data[i]);
			*buffer++ = cpu_to_le32(data);
		पूर्ण
		addr += 16;
		reg_पढ़ो -= 16;
		ret += 16;
		cond_resched();
	पूर्ण
out:
	mutex_unlock(&adapter->ahw->mem_lock);
	वापस mem->size;
पूर्ण

/* DMA रेजिस्टर base address */
#घोषणा QLC_DMA_REG_BASE_ADDR(dma_no)	(0x77320000 + (dma_no * 0x10000))

/* DMA रेजिस्टर offsets w.r.t base address */
#घोषणा QLC_DMA_CMD_BUFF_ADDR_LOW	0
#घोषणा QLC_DMA_CMD_BUFF_ADDR_HI	4
#घोषणा QLC_DMA_CMD_STATUS_CTRL		8

अटल पूर्णांक qlcnic_start_pex_dma(काष्ठा qlcnic_adapter *adapter,
				काष्ठा __mem *mem)
अणु
	काष्ठा device *dev = &adapter->pdev->dev;
	u32 dma_no, dma_base_addr, temp_addr;
	पूर्णांक i, ret, dma_sts;
	व्योम *पंचांगpl_hdr;

	पंचांगpl_hdr = adapter->ahw->fw_dump.पंचांगpl_hdr;
	dma_no = qlcnic_get_saved_state(adapter, पंचांगpl_hdr,
					QLC_83XX_DMA_ENGINE_INDEX);
	dma_base_addr = QLC_DMA_REG_BASE_ADDR(dma_no);

	temp_addr = dma_base_addr + QLC_DMA_CMD_BUFF_ADDR_LOW;
	ret = qlcnic_ind_wr(adapter, temp_addr, mem->desc_card_addr);
	अगर (ret)
		वापस ret;

	temp_addr = dma_base_addr + QLC_DMA_CMD_BUFF_ADDR_HI;
	ret = qlcnic_ind_wr(adapter, temp_addr, 0);
	अगर (ret)
		वापस ret;

	temp_addr = dma_base_addr + QLC_DMA_CMD_STATUS_CTRL;
	ret = qlcnic_ind_wr(adapter, temp_addr, mem->start_dma_cmd);
	अगर (ret)
		वापस ret;

	/* Wait क्रम DMA to complete */
	temp_addr = dma_base_addr + QLC_DMA_CMD_STATUS_CTRL;
	क्रम (i = 0; i < 400; i++) अणु
		dma_sts = qlcnic_ind_rd(adapter, temp_addr);

		अगर (dma_sts & BIT_1)
			usleep_range(250, 500);
		अन्यथा
			अवरोध;
	पूर्ण

	अगर (i >= 400) अणु
		dev_info(dev, "PEX DMA operation timed out");
		ret = -EIO;
	पूर्ण

	वापस ret;
पूर्ण

अटल u32 qlcnic_पढ़ो_memory_pexdma(काष्ठा qlcnic_adapter *adapter,
				     काष्ठा __mem *mem,
				     __le32 *buffer, पूर्णांक *ret)
अणु
	काष्ठा qlcnic_fw_dump *fw_dump = &adapter->ahw->fw_dump;
	u32 temp, dma_base_addr, size = 0, पढ़ो_size = 0;
	काष्ठा qlcnic_pex_dma_descriptor *dma_descr;
	काष्ठा device *dev = &adapter->pdev->dev;
	dma_addr_t dma_phys_addr;
	व्योम *dma_buffer;
	व्योम *पंचांगpl_hdr;

	पंचांगpl_hdr = fw_dump->पंचांगpl_hdr;

	/* Check अगर DMA engine is available */
	temp = qlcnic_get_saved_state(adapter, पंचांगpl_hdr,
				      QLC_83XX_DMA_ENGINE_INDEX);
	dma_base_addr = QLC_DMA_REG_BASE_ADDR(temp);
	temp = qlcnic_ind_rd(adapter,
			     dma_base_addr + QLC_DMA_CMD_STATUS_CTRL);

	अगर (!(temp & BIT_31)) अणु
		dev_info(dev, "%s: DMA engine is not available\n", __func__);
		*ret = -EIO;
		वापस 0;
	पूर्ण

	/* Create DMA descriptor */
	dma_descr = kzalloc(माप(काष्ठा qlcnic_pex_dma_descriptor),
			    GFP_KERNEL);
	अगर (!dma_descr) अणु
		*ret = -ENOMEM;
		वापस 0;
	पूर्ण

	/* dma_desc_cmd  0:15  = 0
	 * dma_desc_cmd 16:19  = mem->dma_desc_cmd 0:3
	 * dma_desc_cmd 20:23  = pci function number
	 * dma_desc_cmd 24:31  = mem->dma_desc_cmd 8:15
	 */
	dma_phys_addr = fw_dump->phys_addr;
	dma_buffer = fw_dump->dma_buffer;
	temp = 0;
	temp = mem->dma_desc_cmd & 0xff0f;
	temp |= (adapter->ahw->pci_func & 0xf) << 4;
	dma_descr->dma_desc_cmd = (temp << 16) & 0xffff0000;
	dma_descr->dma_bus_addr_low = LSD(dma_phys_addr);
	dma_descr->dma_bus_addr_high = MSD(dma_phys_addr);
	dma_descr->src_addr_high = 0;

	/* Collect memory dump using multiple DMA operations अगर required */
	जबतक (पढ़ो_size < mem->size) अणु
		अगर (mem->size - पढ़ो_size >= QLC_PEX_DMA_READ_SIZE)
			size = QLC_PEX_DMA_READ_SIZE;
		अन्यथा
			size = mem->size - पढ़ो_size;

		dma_descr->src_addr_low = mem->addr + पढ़ो_size;
		dma_descr->पढ़ो_data_size = size;

		/* Write DMA descriptor to MS memory*/
		temp = माप(काष्ठा qlcnic_pex_dma_descriptor) / 16;
		*ret = qlcnic_ms_mem_ग_लिखो128(adapter, mem->desc_card_addr,
					      (u32 *)dma_descr, temp);
		अगर (*ret) अणु
			dev_info(dev, "Failed to write DMA descriptor to MS memory at address 0x%x\n",
				 mem->desc_card_addr);
			जाओ मुक्त_dma_descr;
		पूर्ण

		*ret = qlcnic_start_pex_dma(adapter, mem);
		अगर (*ret) अणु
			dev_info(dev, "Failed to start PEX DMA operation\n");
			जाओ मुक्त_dma_descr;
		पूर्ण

		स_नकल(buffer, dma_buffer, size);
		buffer += size / 4;
		पढ़ो_size += size;
	पूर्ण

मुक्त_dma_descr:
	kमुक्त(dma_descr);

	वापस पढ़ो_size;
पूर्ण

अटल u32 qlcnic_पढ़ो_memory(काष्ठा qlcnic_adapter *adapter,
			      काष्ठा qlcnic_dump_entry *entry, __le32 *buffer)
अणु
	काष्ठा qlcnic_fw_dump *fw_dump = &adapter->ahw->fw_dump;
	काष्ठा device *dev = &adapter->pdev->dev;
	काष्ठा __mem *mem = &entry->region.mem;
	u32 data_size;
	पूर्णांक ret = 0;

	अगर (fw_dump->use_pex_dma) अणु
		data_size = qlcnic_पढ़ो_memory_pexdma(adapter, mem, buffer,
						      &ret);
		अगर (ret)
			dev_info(dev,
				 "Failed to read memory dump using PEX DMA: mask[0x%x]\n",
				 entry->hdr.mask);
		अन्यथा
			वापस data_size;
	पूर्ण

	data_size = qlcnic_पढ़ो_memory_test_agent(adapter, mem, buffer, &ret);
	अगर (ret) अणु
		dev_info(dev,
			 "Failed to read memory dump using test agent method: mask[0x%x]\n",
			 entry->hdr.mask);
		वापस 0;
	पूर्ण अन्यथा अणु
		वापस data_size;
	पूर्ण
पूर्ण

अटल u32 qlcnic_dump_nop(काष्ठा qlcnic_adapter *adapter,
			   काष्ठा qlcnic_dump_entry *entry, __le32 *buffer)
अणु
	entry->hdr.flags |= QLCNIC_DUMP_SKIP;
	वापस 0;
पूर्ण

अटल पूर्णांक qlcnic_valid_dump_entry(काष्ठा device *dev,
				   काष्ठा qlcnic_dump_entry *entry, u32 size)
अणु
	पूर्णांक ret = 1;
	अगर (size != entry->hdr.cap_size) अणु
		dev_err(dev,
			"Invalid entry, Type:%d\tMask:%d\tSize:%dCap_size:%d\n",
			entry->hdr.type, entry->hdr.mask, size,
			entry->hdr.cap_size);
		ret = 0;
	पूर्ण
	वापस ret;
पूर्ण

अटल u32 qlcnic_पढ़ो_pollrdmwr(काष्ठा qlcnic_adapter *adapter,
				 काष्ठा qlcnic_dump_entry *entry,
				 __le32 *buffer)
अणु
	काष्ठा __pollrdmwr *poll = &entry->region.pollrdmwr;
	u32 data, रुको_count, poll_रुको, temp;

	poll_रुको = poll->poll_रुको;

	qlcnic_ind_wr(adapter, poll->addr1, poll->val1);
	रुको_count = 0;

	जबतक (रुको_count < poll_रुको) अणु
		data = qlcnic_ind_rd(adapter, poll->addr1);
		अगर ((data & poll->poll_mask) != 0)
			अवरोध;
		रुको_count++;
	पूर्ण

	अगर (रुको_count == poll_रुको) अणु
		dev_err(&adapter->pdev->dev,
			"Timeout exceeded in %s, aborting dump\n",
			__func__);
		वापस 0;
	पूर्ण

	data = qlcnic_ind_rd(adapter, poll->addr2) & poll->mod_mask;
	qlcnic_ind_wr(adapter, poll->addr2, data);
	qlcnic_ind_wr(adapter, poll->addr1, poll->val2);
	रुको_count = 0;

	जबतक (रुको_count < poll_रुको) अणु
		temp = qlcnic_ind_rd(adapter, poll->addr1);
		अगर ((temp & poll->poll_mask) != 0)
			अवरोध;
		रुको_count++;
	पूर्ण

	*buffer++ = cpu_to_le32(poll->addr2);
	*buffer++ = cpu_to_le32(data);

	वापस 2 * माप(u32);

पूर्ण

अटल u32 qlcnic_पढ़ो_pollrd(काष्ठा qlcnic_adapter *adapter,
			      काष्ठा qlcnic_dump_entry *entry, __le32 *buffer)
अणु
	काष्ठा __pollrd *pollrd = &entry->region.pollrd;
	u32 data, रुको_count, poll_रुको, sel_val;
	पूर्णांक i;

	poll_रुको = pollrd->poll_रुको;
	sel_val = pollrd->sel_val;

	क्रम (i = 0; i < pollrd->no_ops; i++) अणु
		qlcnic_ind_wr(adapter, pollrd->sel_addr, sel_val);
		रुको_count = 0;
		जबतक (रुको_count < poll_रुको) अणु
			data = qlcnic_ind_rd(adapter, pollrd->sel_addr);
			अगर ((data & pollrd->poll_mask) != 0)
				अवरोध;
			रुको_count++;
		पूर्ण

		अगर (रुको_count == poll_रुको) अणु
			dev_err(&adapter->pdev->dev,
				"Timeout exceeded in %s, aborting dump\n",
				__func__);
			वापस 0;
		पूर्ण

		data = qlcnic_ind_rd(adapter, pollrd->पढ़ो_addr);
		*buffer++ = cpu_to_le32(sel_val);
		*buffer++ = cpu_to_le32(data);
		sel_val += pollrd->sel_val_stride;
	पूर्ण
	वापस pollrd->no_ops * (2 * माप(u32));
पूर्ण

अटल u32 qlcnic_पढ़ो_mux2(काष्ठा qlcnic_adapter *adapter,
			    काष्ठा qlcnic_dump_entry *entry, __le32 *buffer)
अणु
	काष्ठा __mux2 *mux2 = &entry->region.mux2;
	u32 data;
	u32 t_sel_val, sel_val1, sel_val2;
	पूर्णांक i;

	sel_val1 = mux2->sel_val1;
	sel_val2 = mux2->sel_val2;

	क्रम (i = 0; i < mux2->no_ops; i++) अणु
		qlcnic_ind_wr(adapter, mux2->sel_addr1, sel_val1);
		t_sel_val = sel_val1 & mux2->sel_val_mask;
		qlcnic_ind_wr(adapter, mux2->sel_addr2, t_sel_val);
		data = qlcnic_ind_rd(adapter, mux2->पढ़ो_addr);
		*buffer++ = cpu_to_le32(t_sel_val);
		*buffer++ = cpu_to_le32(data);
		qlcnic_ind_wr(adapter, mux2->sel_addr1, sel_val2);
		t_sel_val = sel_val2 & mux2->sel_val_mask;
		qlcnic_ind_wr(adapter, mux2->sel_addr2, t_sel_val);
		data = qlcnic_ind_rd(adapter, mux2->पढ़ो_addr);
		*buffer++ = cpu_to_le32(t_sel_val);
		*buffer++ = cpu_to_le32(data);
		sel_val1 += mux2->sel_val_stride;
		sel_val2 += mux2->sel_val_stride;
	पूर्ण

	वापस mux2->no_ops * (4 * माप(u32));
पूर्ण

अटल u32 qlcnic_83xx_dump_rom(काष्ठा qlcnic_adapter *adapter,
				काष्ठा qlcnic_dump_entry *entry, __le32 *buffer)
अणु
	u32 fl_addr, size;
	काष्ठा __mem *rom = &entry->region.mem;

	fl_addr = rom->addr;
	size = rom->size / 4;

	अगर (!qlcnic_83xx_lockless_flash_पढ़ो32(adapter, fl_addr,
					       (u8 *)buffer, size))
		वापस rom->size;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा qlcnic_dump_operations qlcnic_fw_dump_ops[] = अणु
	अणुQLCNIC_DUMP_NOP, qlcnic_dump_nopपूर्ण,
	अणुQLCNIC_DUMP_READ_CRB, qlcnic_dump_crbपूर्ण,
	अणुQLCNIC_DUMP_READ_MUX, qlcnic_dump_muxपूर्ण,
	अणुQLCNIC_DUMP_QUEUE, qlcnic_dump_queपूर्ण,
	अणुQLCNIC_DUMP_BRD_CONFIG, qlcnic_पढ़ो_romपूर्ण,
	अणुQLCNIC_DUMP_READ_OCM, qlcnic_dump_ocmपूर्ण,
	अणुQLCNIC_DUMP_PEG_REG, qlcnic_dump_ctrlपूर्ण,
	अणुQLCNIC_DUMP_L1_DTAG, qlcnic_dump_l1_cacheपूर्ण,
	अणुQLCNIC_DUMP_L1_ITAG, qlcnic_dump_l1_cacheपूर्ण,
	अणुQLCNIC_DUMP_L1_DATA, qlcnic_dump_l1_cacheपूर्ण,
	अणुQLCNIC_DUMP_L1_INST, qlcnic_dump_l1_cacheपूर्ण,
	अणुQLCNIC_DUMP_L2_DTAG, qlcnic_dump_l2_cacheपूर्ण,
	अणुQLCNIC_DUMP_L2_ITAG, qlcnic_dump_l2_cacheपूर्ण,
	अणुQLCNIC_DUMP_L2_DATA, qlcnic_dump_l2_cacheपूर्ण,
	अणुQLCNIC_DUMP_L2_INST, qlcnic_dump_l2_cacheपूर्ण,
	अणुQLCNIC_DUMP_READ_ROM, qlcnic_पढ़ो_romपूर्ण,
	अणुQLCNIC_DUMP_READ_MEM, qlcnic_पढ़ो_memoryपूर्ण,
	अणुQLCNIC_DUMP_READ_CTRL, qlcnic_dump_ctrlपूर्ण,
	अणुQLCNIC_DUMP_TLHDR, qlcnic_dump_nopपूर्ण,
	अणुQLCNIC_DUMP_RDEND, qlcnic_dump_nopपूर्ण,
पूर्ण;

अटल स्थिर काष्ठा qlcnic_dump_operations qlcnic_83xx_fw_dump_ops[] = अणु
	अणुQLCNIC_DUMP_NOP, qlcnic_dump_nopपूर्ण,
	अणुQLCNIC_DUMP_READ_CRB, qlcnic_dump_crbपूर्ण,
	अणुQLCNIC_DUMP_READ_MUX, qlcnic_dump_muxपूर्ण,
	अणुQLCNIC_DUMP_QUEUE, qlcnic_dump_queपूर्ण,
	अणुQLCNIC_DUMP_BRD_CONFIG, qlcnic_83xx_dump_romपूर्ण,
	अणुQLCNIC_DUMP_READ_OCM, qlcnic_dump_ocmपूर्ण,
	अणुQLCNIC_DUMP_PEG_REG, qlcnic_dump_ctrlपूर्ण,
	अणुQLCNIC_DUMP_L1_DTAG, qlcnic_dump_l1_cacheपूर्ण,
	अणुQLCNIC_DUMP_L1_ITAG, qlcnic_dump_l1_cacheपूर्ण,
	अणुQLCNIC_DUMP_L1_DATA, qlcnic_dump_l1_cacheपूर्ण,
	अणुQLCNIC_DUMP_L1_INST, qlcnic_dump_l1_cacheपूर्ण,
	अणुQLCNIC_DUMP_L2_DTAG, qlcnic_dump_l2_cacheपूर्ण,
	अणुQLCNIC_DUMP_L2_ITAG, qlcnic_dump_l2_cacheपूर्ण,
	अणुQLCNIC_DUMP_L2_DATA, qlcnic_dump_l2_cacheपूर्ण,
	अणुQLCNIC_DUMP_L2_INST, qlcnic_dump_l2_cacheपूर्ण,
	अणुQLCNIC_DUMP_POLL_RD, qlcnic_पढ़ो_pollrdपूर्ण,
	अणुQLCNIC_READ_MUX2, qlcnic_पढ़ो_mux2पूर्ण,
	अणुQLCNIC_READ_POLLRDMWR, qlcnic_पढ़ो_pollrdmwrपूर्ण,
	अणुQLCNIC_DUMP_READ_ROM, qlcnic_83xx_dump_romपूर्ण,
	अणुQLCNIC_DUMP_READ_MEM, qlcnic_पढ़ो_memoryपूर्ण,
	अणुQLCNIC_DUMP_READ_CTRL, qlcnic_dump_ctrlपूर्ण,
	अणुQLCNIC_DUMP_TLHDR, qlcnic_dump_nopपूर्ण,
	अणुQLCNIC_DUMP_RDEND, qlcnic_dump_nopपूर्ण,
पूर्ण;

अटल uपूर्णांक32_t qlcnic_temp_checksum(uपूर्णांक32_t *temp_buffer, u32 temp_size)
अणु
	uपूर्णांक64_t sum = 0;
	पूर्णांक count = temp_size / माप(uपूर्णांक32_t);
	जबतक (count-- > 0)
		sum += *temp_buffer++;
	जबतक (sum >> 32)
		sum = (sum & 0xFFFFFFFF) + (sum >> 32);
	वापस ~sum;
पूर्ण

अटल पूर्णांक qlcnic_fw_flash_get_minidump_temp(काष्ठा qlcnic_adapter *adapter,
					     u8 *buffer, u32 size)
अणु
	पूर्णांक ret = 0;

	अगर (qlcnic_82xx_check(adapter))
		वापस -EIO;

	अगर (qlcnic_83xx_lock_flash(adapter))
		वापस -EIO;

	ret = qlcnic_83xx_lockless_flash_पढ़ो32(adapter,
						QLC_83XX_MINIDUMP_FLASH,
						buffer, size / माप(u32));

	qlcnic_83xx_unlock_flash(adapter);

	वापस ret;
पूर्ण

अटल पूर्णांक
qlcnic_fw_flash_get_minidump_temp_size(काष्ठा qlcnic_adapter *adapter,
				       काष्ठा qlcnic_cmd_args *cmd)
अणु
	काष्ठा qlcnic_83xx_dump_ढाँचा_hdr पंचांगp_hdr;
	u32 size = माप(पंचांगp_hdr) / माप(u32);
	पूर्णांक ret = 0;

	अगर (qlcnic_82xx_check(adapter))
		वापस -EIO;

	अगर (qlcnic_83xx_lock_flash(adapter))
		वापस -EIO;

	ret = qlcnic_83xx_lockless_flash_पढ़ो32(adapter,
						QLC_83XX_MINIDUMP_FLASH,
						(u8 *)&पंचांगp_hdr, size);

	qlcnic_83xx_unlock_flash(adapter);

	cmd->rsp.arg[2] = पंचांगp_hdr.size;
	cmd->rsp.arg[3] = पंचांगp_hdr.version;

	वापस ret;
पूर्ण

अटल पूर्णांक qlcnic_fw_get_minidump_temp_size(काष्ठा qlcnic_adapter *adapter,
					    u32 *version, u32 *temp_size,
					    u8 *use_flash_temp)
अणु
	पूर्णांक err = 0;
	काष्ठा qlcnic_cmd_args cmd;

	अगर (qlcnic_alloc_mbx_args(&cmd, adapter, QLCNIC_CMD_TEMP_SIZE))
		वापस -ENOMEM;

	err = qlcnic_issue_cmd(adapter, &cmd);
	अगर (err != QLCNIC_RCODE_SUCCESS) अणु
		अगर (qlcnic_fw_flash_get_minidump_temp_size(adapter, &cmd)) अणु
			qlcnic_मुक्त_mbx_args(&cmd);
			वापस -EIO;
		पूर्ण
		*use_flash_temp = 1;
	पूर्ण

	*temp_size = cmd.rsp.arg[2];
	*version = cmd.rsp.arg[3];
	qlcnic_मुक्त_mbx_args(&cmd);

	अगर (!(*temp_size))
		वापस -EIO;

	वापस 0;
पूर्ण

अटल पूर्णांक __qlcnic_fw_cmd_get_minidump_temp(काष्ठा qlcnic_adapter *adapter,
					     u32 *buffer, u32 temp_size)
अणु
	पूर्णांक err = 0, i;
	व्योम *पंचांगp_addr;
	__le32 *पंचांगp_buf;
	काष्ठा qlcnic_cmd_args cmd;
	dma_addr_t पंचांगp_addr_t = 0;

	पंचांगp_addr = dma_alloc_coherent(&adapter->pdev->dev, temp_size,
				      &पंचांगp_addr_t, GFP_KERNEL);
	अगर (!पंचांगp_addr)
		वापस -ENOMEM;

	अगर (qlcnic_alloc_mbx_args(&cmd, adapter, QLCNIC_CMD_GET_TEMP_HDR)) अणु
		err = -ENOMEM;
		जाओ मुक्त_mem;
	पूर्ण

	cmd.req.arg[1] = LSD(पंचांगp_addr_t);
	cmd.req.arg[2] = MSD(पंचांगp_addr_t);
	cmd.req.arg[3] = temp_size;
	err = qlcnic_issue_cmd(adapter, &cmd);

	पंचांगp_buf = पंचांगp_addr;
	अगर (err == QLCNIC_RCODE_SUCCESS) अणु
		क्रम (i = 0; i < temp_size / माप(u32); i++)
			*buffer++ = __le32_to_cpu(*पंचांगp_buf++);
	पूर्ण

	qlcnic_मुक्त_mbx_args(&cmd);

मुक्त_mem:
	dma_मुक्त_coherent(&adapter->pdev->dev, temp_size, पंचांगp_addr, पंचांगp_addr_t);

	वापस err;
पूर्ण

पूर्णांक qlcnic_fw_cmd_get_minidump_temp(काष्ठा qlcnic_adapter *adapter)
अणु
	काष्ठा qlcnic_hardware_context *ahw;
	काष्ठा qlcnic_fw_dump *fw_dump;
	u32 version, csum, *पंचांगp_buf;
	u8 use_flash_temp = 0;
	u32 temp_size = 0;
	व्योम *temp_buffer;
	पूर्णांक err;

	ahw = adapter->ahw;
	fw_dump = &ahw->fw_dump;
	err = qlcnic_fw_get_minidump_temp_size(adapter, &version, &temp_size,
					       &use_flash_temp);
	अगर (err) अणु
		dev_err(&adapter->pdev->dev,
			"Can't get template size %d\n", err);
		वापस -EIO;
	पूर्ण

	fw_dump->पंचांगpl_hdr = vzalloc(temp_size);
	अगर (!fw_dump->पंचांगpl_hdr)
		वापस -ENOMEM;

	पंचांगp_buf = (u32 *)fw_dump->पंचांगpl_hdr;
	अगर (use_flash_temp)
		जाओ flash_temp;

	err = __qlcnic_fw_cmd_get_minidump_temp(adapter, पंचांगp_buf, temp_size);

	अगर (err) अणु
flash_temp:
		err = qlcnic_fw_flash_get_minidump_temp(adapter, (u8 *)पंचांगp_buf,
							temp_size);

		अगर (err) अणु
			dev_err(&adapter->pdev->dev,
				"Failed to get minidump template header %d\n",
				err);
			vमुक्त(fw_dump->पंचांगpl_hdr);
			fw_dump->पंचांगpl_hdr = शून्य;
			वापस -EIO;
		पूर्ण
	पूर्ण

	csum = qlcnic_temp_checksum((uपूर्णांक32_t *)पंचांगp_buf, temp_size);

	अगर (csum) अणु
		dev_err(&adapter->pdev->dev,
			"Template header checksum validation failed\n");
		vमुक्त(fw_dump->पंचांगpl_hdr);
		fw_dump->पंचांगpl_hdr = शून्य;
		वापस -EIO;
	पूर्ण

	qlcnic_cache_पंचांगpl_hdr_values(adapter, fw_dump);

	अगर (fw_dump->use_pex_dma) अणु
		fw_dump->dma_buffer = शून्य;
		temp_buffer = dma_alloc_coherent(&adapter->pdev->dev,
						 QLC_PEX_DMA_READ_SIZE,
						 &fw_dump->phys_addr,
						 GFP_KERNEL);
		अगर (!temp_buffer)
			fw_dump->use_pex_dma = false;
		अन्यथा
			fw_dump->dma_buffer = temp_buffer;
	पूर्ण


	dev_info(&adapter->pdev->dev,
		 "Default minidump capture mask 0x%x\n",
		 fw_dump->cap_mask);

	qlcnic_enable_fw_dump_state(adapter);

	वापस 0;
पूर्ण

पूर्णांक qlcnic_dump_fw(काष्ठा qlcnic_adapter *adapter)
अणु
	काष्ठा qlcnic_fw_dump *fw_dump = &adapter->ahw->fw_dump;
	स्थिर काष्ठा qlcnic_dump_operations *fw_dump_ops;
	काष्ठा qlcnic_83xx_dump_ढाँचा_hdr *hdr_83xx;
	u32 entry_offset, dump, no_entries, buf_offset = 0;
	पूर्णांक i, k, ops_cnt, ops_index, dump_size = 0;
	काष्ठा device *dev = &adapter->pdev->dev;
	काष्ठा qlcnic_hardware_context *ahw;
	काष्ठा qlcnic_dump_entry *entry;
	व्योम *पंचांगpl_hdr;
	u32 ocm_winकरोw;
	__le32 *buffer;
	अक्षर mesg[64];
	अक्षर *msg[] = अणुmesg, शून्यपूर्ण;

	ahw = adapter->ahw;
	पंचांगpl_hdr = fw_dump->पंचांगpl_hdr;

	/* Return अगर we करोn't have firmware dump ढाँचा header */
	अगर (!पंचांगpl_hdr)
		वापस -EIO;

	अगर (!qlcnic_check_fw_dump_state(adapter)) अणु
		dev_info(&adapter->pdev->dev, "Dump not enabled\n");
		वापस -EIO;
	पूर्ण

	अगर (fw_dump->clr) अणु
		dev_info(&adapter->pdev->dev,
			 "Previous dump not cleared, not capturing dump\n");
		वापस -EIO;
	पूर्ण

	netअगर_info(adapter->ahw, drv, adapter->netdev, "Take FW dump\n");
	/* Calculate the size क्रम dump data area only */
	क्रम (i = 2, k = 1; (i & QLCNIC_DUMP_MASK_MAX); i <<= 1, k++)
		अगर (i & fw_dump->cap_mask)
			dump_size += qlcnic_get_cap_size(adapter, पंचांगpl_hdr, k);

	अगर (!dump_size)
		वापस -EIO;

	fw_dump->data = vzalloc(dump_size);
	अगर (!fw_dump->data)
		वापस -ENOMEM;

	buffer = fw_dump->data;
	fw_dump->size = dump_size;
	no_entries = fw_dump->num_entries;
	entry_offset = fw_dump->offset;
	qlcnic_set_sys_info(adapter, पंचांगpl_hdr, 0, QLCNIC_DRIVER_VERSION);
	qlcnic_set_sys_info(adapter, पंचांगpl_hdr, 1, adapter->fw_version);

	अगर (qlcnic_82xx_check(adapter)) अणु
		ops_cnt = ARRAY_SIZE(qlcnic_fw_dump_ops);
		fw_dump_ops = qlcnic_fw_dump_ops;
	पूर्ण अन्यथा अणु
		hdr_83xx = पंचांगpl_hdr;
		ops_cnt = ARRAY_SIZE(qlcnic_83xx_fw_dump_ops);
		fw_dump_ops = qlcnic_83xx_fw_dump_ops;
		ocm_winकरोw = hdr_83xx->ocm_wnd_reg[ahw->pci_func];
		hdr_83xx->saved_state[QLC_83XX_OCM_INDEX] = ocm_winकरोw;
		hdr_83xx->saved_state[QLC_83XX_PCI_INDEX] = ahw->pci_func;
	पूर्ण

	क्रम (i = 0; i < no_entries; i++) अणु
		entry = पंचांगpl_hdr + entry_offset;
		अगर (!(entry->hdr.mask & fw_dump->cap_mask)) अणु
			entry->hdr.flags |= QLCNIC_DUMP_SKIP;
			entry_offset += entry->hdr.offset;
			जारी;
		पूर्ण

		/* Find the handler क्रम this entry */
		ops_index = 0;
		जबतक (ops_index < ops_cnt) अणु
			अगर (entry->hdr.type == fw_dump_ops[ops_index].opcode)
				अवरोध;
			ops_index++;
		पूर्ण

		अगर (ops_index == ops_cnt) अणु
			dev_info(dev, "Skipping unknown entry opcode %d\n",
				 entry->hdr.type);
			entry->hdr.flags |= QLCNIC_DUMP_SKIP;
			entry_offset += entry->hdr.offset;
			जारी;
		पूर्ण

		/* Collect dump क्रम this entry */
		dump = fw_dump_ops[ops_index].handler(adapter, entry, buffer);
		अगर (!qlcnic_valid_dump_entry(dev, entry, dump)) अणु
			entry->hdr.flags |= QLCNIC_DUMP_SKIP;
			entry_offset += entry->hdr.offset;
			जारी;
		पूर्ण

		buf_offset += entry->hdr.cap_size;
		entry_offset += entry->hdr.offset;
		buffer = fw_dump->data + buf_offset;
		cond_resched();
	पूर्ण

	fw_dump->clr = 1;
	snम_लिखो(mesg, माप(mesg), "FW_DUMP=%s", adapter->netdev->name);
	netdev_info(adapter->netdev,
		    "Dump data %d bytes captured, dump data address = %p, template header size %d bytes, template address = %p\n",
		    fw_dump->size, fw_dump->data, fw_dump->पंचांगpl_hdr_size,
		    fw_dump->पंचांगpl_hdr);
	/* Send a udev event to notअगरy availability of FW dump */
	kobject_uevent_env(&dev->kobj, KOBJ_CHANGE, msg);

	वापस 0;
पूर्ण

अटल अंतरभूत bool
qlcnic_83xx_md_check_extended_dump_capability(काष्ठा qlcnic_adapter *adapter)
अणु
	/* For special adapters (with 0x8830 device ID), where iSCSI firmware
	 * dump needs to be captured as part of regular firmware dump
	 * collection process, firmware exports it's capability through
	 * capability रेजिस्टरs
	 */
	वापस ((adapter->pdev->device == PCI_DEVICE_ID_QLOGIC_QLE8830) &&
		(adapter->ahw->extra_capability[0] &
		 QLCNIC_FW_CAPABILITY_2_EXT_ISCSI_DUMP));
पूर्ण

व्योम qlcnic_83xx_get_minidump_ढाँचा(काष्ठा qlcnic_adapter *adapter)
अणु
	u32 prev_version, current_version;
	काष्ठा qlcnic_hardware_context *ahw = adapter->ahw;
	काष्ठा qlcnic_fw_dump *fw_dump = &ahw->fw_dump;
	काष्ठा pci_dev *pdev = adapter->pdev;
	bool extended = false;
	पूर्णांक ret;

	prev_version = adapter->fw_version;
	current_version = qlcnic_83xx_get_fw_version(adapter);

	अगर (fw_dump->पंचांगpl_hdr == शून्य || current_version > prev_version) अणु
		vमुक्त(fw_dump->पंचांगpl_hdr);
		fw_dump->पंचांगpl_hdr = शून्य;

		अगर (qlcnic_83xx_md_check_extended_dump_capability(adapter))
			extended = !qlcnic_83xx_extend_md_capab(adapter);

		ret = qlcnic_fw_cmd_get_minidump_temp(adapter);
		अगर (ret)
			वापस;

		dev_info(&pdev->dev, "Supports FW dump capability\n");

		/* Once we have minidump ढाँचा with extended iSCSI dump
		 * capability, update the minidump capture mask to 0x1f as
		 * per FW requirement
		 */
		अगर (extended) अणु
			काष्ठा qlcnic_83xx_dump_ढाँचा_hdr *hdr;

			hdr = fw_dump->पंचांगpl_hdr;
			अगर (!hdr)
				वापस;
			hdr->drv_cap_mask = 0x1f;
			fw_dump->cap_mask = 0x1f;
			dev_info(&pdev->dev,
				 "Extended iSCSI dump capability and updated capture mask to 0x1f\n");
		पूर्ण
	पूर्ण
पूर्ण
