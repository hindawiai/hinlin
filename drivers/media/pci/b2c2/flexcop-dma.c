<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Linux driver क्रम digital TV devices equipped with B2C2 FlexcopII(b)/III
 * flexcop-dma.c - configuring and controlling the DMA of the FlexCop
 * see flexcop.c क्रम copyright inक्रमmation
 */
#समावेश "flexcop.h"

पूर्णांक flexcop_dma_allocate(काष्ठा pci_dev *pdev,
		काष्ठा flexcop_dma *dma, u32 size)
अणु
	u8 *tcpu;
	dma_addr_t tdma = 0;

	अगर (size % 2) अणु
		err("dma buffersize has to be even.");
		वापस -EINVAL;
	पूर्ण

	tcpu = dma_alloc_coherent(&pdev->dev, size, &tdma, GFP_KERNEL);
	अगर (tcpu != शून्य) अणु
		dma->pdev = pdev;
		dma->cpu_addr0 = tcpu;
		dma->dma_addr0 = tdma;
		dma->cpu_addr1 = tcpu + size/2;
		dma->dma_addr1 = tdma + size/2;
		dma->size = size/2;
		वापस 0;
	पूर्ण
	वापस -ENOMEM;
पूर्ण
EXPORT_SYMBOL(flexcop_dma_allocate);

व्योम flexcop_dma_मुक्त(काष्ठा flexcop_dma *dma)
अणु
	dma_मुक्त_coherent(&dma->pdev->dev, dma->size * 2, dma->cpu_addr0,
			  dma->dma_addr0);
	स_रखो(dma, 0, माप(काष्ठा flexcop_dma));
पूर्ण
EXPORT_SYMBOL(flexcop_dma_मुक्त);

पूर्णांक flexcop_dma_config(काष्ठा flexcop_device *fc,
		काष्ठा flexcop_dma *dma,
		flexcop_dma_index_t dma_idx)
अणु
	flexcop_ibi_value v0x0, v0x4, v0xc;

	v0x0.raw = v0x4.raw = v0xc.raw = 0;
	v0x0.dma_0x0.dma_address0 = dma->dma_addr0 >> 2;
	v0xc.dma_0xc.dma_address1 = dma->dma_addr1 >> 2;
	v0x4.dma_0x4_ग_लिखो.dma_addr_size = dma->size / 4;

	अगर ((dma_idx & FC_DMA_1) == dma_idx) अणु
		fc->ग_लिखो_ibi_reg(fc, dma1_000, v0x0);
		fc->ग_लिखो_ibi_reg(fc, dma1_004, v0x4);
		fc->ग_लिखो_ibi_reg(fc, dma1_00c, v0xc);
	पूर्ण अन्यथा अगर ((dma_idx & FC_DMA_2) == dma_idx) अणु
		fc->ग_लिखो_ibi_reg(fc, dma2_010, v0x0);
		fc->ग_लिखो_ibi_reg(fc, dma2_014, v0x4);
		fc->ग_लिखो_ibi_reg(fc, dma2_01c, v0xc);
	पूर्ण अन्यथा अणु
		err("either DMA1 or DMA2 can be configured within one %s call.",
			__func__);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(flexcop_dma_config);

/* start the DMA transfers, but not the DMA IRQs */
पूर्णांक flexcop_dma_xfer_control(काष्ठा flexcop_device *fc,
		flexcop_dma_index_t dma_idx,
		flexcop_dma_addr_index_t index,
		पूर्णांक onoff)
अणु
	flexcop_ibi_value v0x0, v0xc;
	flexcop_ibi_रेजिस्टर r0x0, r0xc;

	अगर ((dma_idx & FC_DMA_1) == dma_idx) अणु
		r0x0 = dma1_000;
		r0xc = dma1_00c;
	पूर्ण अन्यथा अगर ((dma_idx & FC_DMA_2) == dma_idx) अणु
		r0x0 = dma2_010;
		r0xc = dma2_01c;
	पूर्ण अन्यथा अणु
		err("transfer DMA1 or DMA2 can be started within one %s call.",
			__func__);
		वापस -EINVAL;
	पूर्ण

	v0x0 = fc->पढ़ो_ibi_reg(fc, r0x0);
	v0xc = fc->पढ़ो_ibi_reg(fc, r0xc);

	deb_rdump("reg: %03x: %x\n", r0x0, v0x0.raw);
	deb_rdump("reg: %03x: %x\n", r0xc, v0xc.raw);

	अगर (index & FC_DMA_SUBADDR_0)
		v0x0.dma_0x0.dma_0start = onoff;

	अगर (index & FC_DMA_SUBADDR_1)
		v0xc.dma_0xc.dma_1start = onoff;

	fc->ग_लिखो_ibi_reg(fc, r0x0, v0x0);
	fc->ग_लिखो_ibi_reg(fc, r0xc, v0xc);

	deb_rdump("reg: %03x: %x\n", r0x0, v0x0.raw);
	deb_rdump("reg: %03x: %x\n", r0xc, v0xc.raw);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(flexcop_dma_xfer_control);

अटल पूर्णांक flexcop_dma_remap(काष्ठा flexcop_device *fc,
		flexcop_dma_index_t dma_idx,
		पूर्णांक onoff)
अणु
	flexcop_ibi_रेजिस्टर r = (dma_idx & FC_DMA_1) ? dma1_00c : dma2_01c;
	flexcop_ibi_value v = fc->पढ़ो_ibi_reg(fc, r);

	deb_info("%s\n", __func__);
	v.dma_0xc.remap_enable = onoff;
	fc->ग_लिखो_ibi_reg(fc, r, v);
	वापस 0;
पूर्ण

पूर्णांक flexcop_dma_control_size_irq(काष्ठा flexcop_device *fc,
		flexcop_dma_index_t no,
		पूर्णांक onoff)
अणु
	flexcop_ibi_value v = fc->पढ़ो_ibi_reg(fc, ctrl_208);

	अगर (no & FC_DMA_1)
		v.ctrl_208.DMA1_IRQ_Enable_sig = onoff;

	अगर (no & FC_DMA_2)
		v.ctrl_208.DMA2_IRQ_Enable_sig = onoff;

	fc->ग_लिखो_ibi_reg(fc, ctrl_208, v);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(flexcop_dma_control_size_irq);

पूर्णांक flexcop_dma_control_समयr_irq(काष्ठा flexcop_device *fc,
		flexcop_dma_index_t no,
		पूर्णांक onoff)
अणु
	flexcop_ibi_value v = fc->पढ़ो_ibi_reg(fc, ctrl_208);

	अगर (no & FC_DMA_1)
		v.ctrl_208.DMA1_Timer_Enable_sig = onoff;

	अगर (no & FC_DMA_2)
		v.ctrl_208.DMA2_Timer_Enable_sig = onoff;

	fc->ग_लिखो_ibi_reg(fc, ctrl_208, v);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(flexcop_dma_control_समयr_irq);

/* 1 cycles = 1.97 msec */
पूर्णांक flexcop_dma_config_समयr(काष्ठा flexcop_device *fc,
		flexcop_dma_index_t dma_idx, u8 cycles)
अणु
	flexcop_ibi_रेजिस्टर r = (dma_idx & FC_DMA_1) ? dma1_004 : dma2_014;
	flexcop_ibi_value v = fc->पढ़ो_ibi_reg(fc, r);

	flexcop_dma_remap(fc, dma_idx, 0);

	deb_info("%s\n", __func__);
	v.dma_0x4_ग_लिखो.dmaसमयr = cycles;
	fc->ग_लिखो_ibi_reg(fc, r, v);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(flexcop_dma_config_समयr);

