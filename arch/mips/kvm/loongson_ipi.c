<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Loongson-3 Virtual IPI पूर्णांकerrupt support.
 *
 * Copyright (C) 2019  Loongson Technologies, Inc.  All rights reserved.
 *
 * Authors: Chen Zhu <zhuchen@loongson.cn>
 * Authors: Huacai Chen <chenhc@lemote.com>
 */

#समावेश <linux/kvm_host.h>

#घोषणा IPI_BASE            0x3ff01000ULL

#घोषणा CORE0_STATUS_OFF       0x000
#घोषणा CORE0_EN_OFF           0x004
#घोषणा CORE0_SET_OFF          0x008
#घोषणा CORE0_CLEAR_OFF        0x00c
#घोषणा CORE0_BUF_20           0x020
#घोषणा CORE0_BUF_28           0x028
#घोषणा CORE0_BUF_30           0x030
#घोषणा CORE0_BUF_38           0x038

#घोषणा CORE1_STATUS_OFF       0x100
#घोषणा CORE1_EN_OFF           0x104
#घोषणा CORE1_SET_OFF          0x108
#घोषणा CORE1_CLEAR_OFF        0x10c
#घोषणा CORE1_BUF_20           0x120
#घोषणा CORE1_BUF_28           0x128
#घोषणा CORE1_BUF_30           0x130
#घोषणा CORE1_BUF_38           0x138

#घोषणा CORE2_STATUS_OFF       0x200
#घोषणा CORE2_EN_OFF           0x204
#घोषणा CORE2_SET_OFF          0x208
#घोषणा CORE2_CLEAR_OFF        0x20c
#घोषणा CORE2_BUF_20           0x220
#घोषणा CORE2_BUF_28           0x228
#घोषणा CORE2_BUF_30           0x230
#घोषणा CORE2_BUF_38           0x238

#घोषणा CORE3_STATUS_OFF       0x300
#घोषणा CORE3_EN_OFF           0x304
#घोषणा CORE3_SET_OFF          0x308
#घोषणा CORE3_CLEAR_OFF        0x30c
#घोषणा CORE3_BUF_20           0x320
#घोषणा CORE3_BUF_28           0x328
#घोषणा CORE3_BUF_30           0x330
#घोषणा CORE3_BUF_38           0x338

अटल पूर्णांक loongson_vipi_पढ़ो(काष्ठा loongson_kvm_ipi *ipi,
				gpa_t addr, पूर्णांक len, व्योम *val)
अणु
	uपूर्णांक32_t core = (addr >> 8) & 3;
	uपूर्णांक32_t node = (addr >> 44) & 3;
	uपूर्णांक32_t id = core + node * 4;
	uपूर्णांक64_t offset = addr & 0xff;
	व्योम *pbuf;
	काष्ठा ipi_state *s = &(ipi->ipistate[id]);

	BUG_ON(offset & (len - 1));

	चयन (offset) अणु
	हाल CORE0_STATUS_OFF:
		*(uपूर्णांक64_t *)val = s->status;
		अवरोध;

	हाल CORE0_EN_OFF:
		*(uपूर्णांक64_t *)val = s->en;
		अवरोध;

	हाल CORE0_SET_OFF:
		*(uपूर्णांक64_t *)val = 0;
		अवरोध;

	हाल CORE0_CLEAR_OFF:
		*(uपूर्णांक64_t *)val = 0;
		अवरोध;

	हाल CORE0_BUF_20 ... CORE0_BUF_38:
		pbuf = (व्योम *)s->buf + (offset - 0x20);
		अगर (len == 8)
			*(uपूर्णांक64_t *)val = *(uपूर्णांक64_t *)pbuf;
		अन्यथा /* Assume len == 4 */
			*(uपूर्णांक32_t *)val = *(uपूर्णांक32_t *)pbuf;
		अवरोध;

	शेष:
		pr_notice("%s with unknown addr %llx\n", __func__, addr);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक loongson_vipi_ग_लिखो(काष्ठा loongson_kvm_ipi *ipi,
				gpa_t addr, पूर्णांक len, स्थिर व्योम *val)
अणु
	uपूर्णांक32_t core = (addr >> 8) & 3;
	uपूर्णांक32_t node = (addr >> 44) & 3;
	uपूर्णांक32_t id = core + node * 4;
	uपूर्णांक64_t data, offset = addr & 0xff;
	व्योम *pbuf;
	काष्ठा kvm *kvm = ipi->kvm;
	काष्ठा kvm_mips_पूर्णांकerrupt irq;
	काष्ठा ipi_state *s = &(ipi->ipistate[id]);

	data = *(uपूर्णांक64_t *)val;
	BUG_ON(offset & (len - 1));

	चयन (offset) अणु
	हाल CORE0_STATUS_OFF:
		अवरोध;

	हाल CORE0_EN_OFF:
		s->en = data;
		अवरोध;

	हाल CORE0_SET_OFF:
		s->status |= data;
		irq.cpu = id;
		irq.irq = 6;
		kvm_vcpu_ioctl_पूर्णांकerrupt(kvm->vcpus[id], &irq);
		अवरोध;

	हाल CORE0_CLEAR_OFF:
		s->status &= ~data;
		अगर (!s->status) अणु
			irq.cpu = id;
			irq.irq = -6;
			kvm_vcpu_ioctl_पूर्णांकerrupt(kvm->vcpus[id], &irq);
		पूर्ण
		अवरोध;

	हाल CORE0_BUF_20 ... CORE0_BUF_38:
		pbuf = (व्योम *)s->buf + (offset - 0x20);
		अगर (len == 8)
			*(uपूर्णांक64_t *)pbuf = (uपूर्णांक64_t)data;
		अन्यथा /* Assume len == 4 */
			*(uपूर्णांक32_t *)pbuf = (uपूर्णांक32_t)data;
		अवरोध;

	शेष:
		pr_notice("%s with unknown addr %llx\n", __func__, addr);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक kvm_ipi_पढ़ो(काष्ठा kvm_vcpu *vcpu, काष्ठा kvm_io_device *dev,
			gpa_t addr, पूर्णांक len, व्योम *val)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा loongson_kvm_ipi *ipi;
	काष्ठा ipi_io_device *ipi_device;

	ipi_device = container_of(dev, काष्ठा ipi_io_device, device);
	ipi = ipi_device->ipi;

	spin_lock_irqsave(&ipi->lock, flags);
	loongson_vipi_पढ़ो(ipi, addr, len, val);
	spin_unlock_irqrestore(&ipi->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक kvm_ipi_ग_लिखो(काष्ठा kvm_vcpu *vcpu, काष्ठा kvm_io_device *dev,
			gpa_t addr, पूर्णांक len, स्थिर व्योम *val)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा loongson_kvm_ipi *ipi;
	काष्ठा ipi_io_device *ipi_device;

	ipi_device = container_of(dev, काष्ठा ipi_io_device, device);
	ipi = ipi_device->ipi;

	spin_lock_irqsave(&ipi->lock, flags);
	loongson_vipi_ग_लिखो(ipi, addr, len, val);
	spin_unlock_irqrestore(&ipi->lock, flags);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा kvm_io_device_ops kvm_ipi_ops = अणु
	.पढ़ो     = kvm_ipi_पढ़ो,
	.ग_लिखो    = kvm_ipi_ग_लिखो,
पूर्ण;

व्योम kvm_init_loongson_ipi(काष्ठा kvm *kvm)
अणु
	पूर्णांक i;
	अचिन्हित दीर्घ addr;
	काष्ठा loongson_kvm_ipi *s;
	काष्ठा kvm_io_device *device;

	s = &kvm->arch.ipi;
	s->kvm = kvm;
	spin_lock_init(&s->lock);

	/*
	 * Initialize IPI device
	 */
	क्रम (i = 0; i < 4; i++) अणु
		device = &s->dev_ipi[i].device;
		kvm_iodevice_init(device, &kvm_ipi_ops);
		addr = (((अचिन्हित दीर्घ)i) << 44) + IPI_BASE;
		mutex_lock(&kvm->slots_lock);
		kvm_io_bus_रेजिस्टर_dev(kvm, KVM_MMIO_BUS, addr, 0x400, device);
		mutex_unlock(&kvm->slots_lock);
		s->dev_ipi[i].ipi = s;
		s->dev_ipi[i].node_id = i;
	पूर्ण
पूर्ण
