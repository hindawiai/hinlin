<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Earthsoft PT3 driver
 *
 * Copyright (C) 2014 Akihiro Tsukada <tskd08@gmail.com>
 */
#समावेश <linux/dma-mapping.h>
#समावेश <linux/kernel.h>
#समावेश <linux/pci.h>

#समावेश "pt3.h"

#घोषणा PT3_ACCESS_UNIT (TS_PACKET_SZ * 128)
#घोषणा PT3_BUF_CANARY  (0x74)

अटल u32 get_dma_base(पूर्णांक idx)
अणु
	पूर्णांक i;

	i = (idx == 1 || idx == 2) ? 3 - idx : idx;
	वापस REG_DMA_BASE + 0x18 * i;
पूर्ण

पूर्णांक pt3_stop_dma(काष्ठा pt3_adapter *adap)
अणु
	काष्ठा pt3_board *pt3 = adap->dvb_adap.priv;
	u32 base;
	u32 stat;
	पूर्णांक retry;

	base = get_dma_base(adap->adap_idx);
	stat = ioपढ़ो32(pt3->regs[0] + base + OFST_STATUS);
	अगर (!(stat & 0x01))
		वापस 0;

	ioग_लिखो32(0x02, pt3->regs[0] + base + OFST_DMA_CTL);
	क्रम (retry = 0; retry < 5; retry++) अणु
		stat = ioपढ़ो32(pt3->regs[0] + base + OFST_STATUS);
		अगर (!(stat & 0x01))
			वापस 0;
		msleep(50);
	पूर्ण
	वापस -EIO;
पूर्ण

पूर्णांक pt3_start_dma(काष्ठा pt3_adapter *adap)
अणु
	काष्ठा pt3_board *pt3 = adap->dvb_adap.priv;
	u32 base = get_dma_base(adap->adap_idx);

	ioग_लिखो32(0x02, pt3->regs[0] + base + OFST_DMA_CTL);
	ioग_लिखो32(lower_32_bits(adap->desc_buf[0].b_addr),
			pt3->regs[0] + base + OFST_DMA_DESC_L);
	ioग_लिखो32(upper_32_bits(adap->desc_buf[0].b_addr),
			pt3->regs[0] + base + OFST_DMA_DESC_H);
	ioग_लिखो32(0x01, pt3->regs[0] + base + OFST_DMA_CTL);
	वापस 0;
पूर्ण


अटल u8 *next_unit(काष्ठा pt3_adapter *adap, पूर्णांक *idx, पूर्णांक *ofs)
अणु
	*ofs += PT3_ACCESS_UNIT;
	अगर (*ofs >= DATA_BUF_SZ) अणु
		*ofs -= DATA_BUF_SZ;
		(*idx)++;
		अगर (*idx == adap->num_bufs)
			*idx = 0;
	पूर्ण
	वापस &adap->buffer[*idx].data[*ofs];
पूर्ण

पूर्णांक pt3_proc_dma(काष्ठा pt3_adapter *adap)
अणु
	पूर्णांक idx, ofs;

	idx = adap->buf_idx;
	ofs = adap->buf_ofs;

	अगर (adap->buffer[idx].data[ofs] == PT3_BUF_CANARY)
		वापस 0;

	जबतक (*next_unit(adap, &idx, &ofs) != PT3_BUF_CANARY) अणु
		u8 *p;

		p = &adap->buffer[adap->buf_idx].data[adap->buf_ofs];
		अगर (adap->num_discard > 0)
			adap->num_discard--;
		अन्यथा अगर (adap->buf_ofs + PT3_ACCESS_UNIT > DATA_BUF_SZ) अणु
			dvb_dmx_swfilter_packets(&adap->demux, p,
				(DATA_BUF_SZ - adap->buf_ofs) / TS_PACKET_SZ);
			dvb_dmx_swfilter_packets(&adap->demux,
				adap->buffer[idx].data, ofs / TS_PACKET_SZ);
		पूर्ण अन्यथा
			dvb_dmx_swfilter_packets(&adap->demux, p,
				PT3_ACCESS_UNIT / TS_PACKET_SZ);

		*p = PT3_BUF_CANARY;
		adap->buf_idx = idx;
		adap->buf_ofs = ofs;
	पूर्ण
	वापस 0;
पूर्ण

व्योम pt3_init_dmabuf(काष्ठा pt3_adapter *adap)
अणु
	पूर्णांक idx, ofs;
	u8 *p;

	idx = 0;
	ofs = 0;
	p = adap->buffer[0].data;
	/* mark the whole buffers as "not written yet" */
	जबतक (idx < adap->num_bufs) अणु
		p[ofs] = PT3_BUF_CANARY;
		ofs += PT3_ACCESS_UNIT;
		अगर (ofs >= DATA_BUF_SZ) अणु
			ofs -= DATA_BUF_SZ;
			idx++;
			p = adap->buffer[idx].data;
		पूर्ण
	पूर्ण
	adap->buf_idx = 0;
	adap->buf_ofs = 0;
पूर्ण

व्योम pt3_मुक्त_dmabuf(काष्ठा pt3_adapter *adap)
अणु
	काष्ठा pt3_board *pt3;
	पूर्णांक i;

	pt3 = adap->dvb_adap.priv;
	क्रम (i = 0; i < adap->num_bufs; i++)
		dma_मुक्त_coherent(&pt3->pdev->dev, DATA_BUF_SZ,
			adap->buffer[i].data, adap->buffer[i].b_addr);
	adap->num_bufs = 0;

	क्रम (i = 0; i < adap->num_desc_bufs; i++)
		dma_मुक्त_coherent(&pt3->pdev->dev, PAGE_SIZE,
			adap->desc_buf[i].descs, adap->desc_buf[i].b_addr);
	adap->num_desc_bufs = 0;
पूर्ण


पूर्णांक pt3_alloc_dmabuf(काष्ठा pt3_adapter *adap)
अणु
	काष्ठा pt3_board *pt3;
	व्योम *p;
	पूर्णांक i, j;
	पूर्णांक idx, ofs;
	पूर्णांक num_desc_bufs;
	dma_addr_t data_addr, desc_addr;
	काष्ठा xfer_desc *d;

	pt3 = adap->dvb_adap.priv;
	adap->num_bufs = 0;
	adap->num_desc_bufs = 0;
	क्रम (i = 0; i < pt3->num_bufs; i++) अणु
		p = dma_alloc_coherent(&pt3->pdev->dev, DATA_BUF_SZ,
					&adap->buffer[i].b_addr, GFP_KERNEL);
		अगर (p == शून्य)
			जाओ failed;
		adap->buffer[i].data = p;
		adap->num_bufs++;
	पूर्ण
	pt3_init_dmabuf(adap);

	/* build circular-linked poपूर्णांकers (xfer_desc) to the data buffers*/
	idx = 0;
	ofs = 0;
	num_desc_bufs =
		DIV_ROUND_UP(adap->num_bufs * DATA_BUF_XFERS, DESCS_IN_PAGE);
	क्रम (i = 0; i < num_desc_bufs; i++) अणु
		p = dma_alloc_coherent(&pt3->pdev->dev, PAGE_SIZE,
					&desc_addr, GFP_KERNEL);
		अगर (p == शून्य)
			जाओ failed;
		adap->num_desc_bufs++;
		adap->desc_buf[i].descs = p;
		adap->desc_buf[i].b_addr = desc_addr;

		अगर (i > 0) अणु
			d = &adap->desc_buf[i - 1].descs[DESCS_IN_PAGE - 1];
			d->next_l = lower_32_bits(desc_addr);
			d->next_h = upper_32_bits(desc_addr);
		पूर्ण
		क्रम (j = 0; j < DESCS_IN_PAGE; j++) अणु
			data_addr = adap->buffer[idx].b_addr + ofs;
			d = &adap->desc_buf[i].descs[j];
			d->addr_l = lower_32_bits(data_addr);
			d->addr_h = upper_32_bits(data_addr);
			d->size = DATA_XFER_SZ;

			desc_addr += माप(काष्ठा xfer_desc);
			d->next_l = lower_32_bits(desc_addr);
			d->next_h = upper_32_bits(desc_addr);

			ofs += DATA_XFER_SZ;
			अगर (ofs >= DATA_BUF_SZ) अणु
				ofs -= DATA_BUF_SZ;
				idx++;
				अगर (idx >= adap->num_bufs) अणु
					desc_addr = adap->desc_buf[0].b_addr;
					d->next_l = lower_32_bits(desc_addr);
					d->next_h = upper_32_bits(desc_addr);
					वापस 0;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
	वापस 0;

failed:
	pt3_मुक्त_dmabuf(adap);
	वापस -ENOMEM;
पूर्ण
