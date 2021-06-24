<शैली गुरु>
/*
 * 8259 पूर्णांकerrupt controller emulation
 *
 * Copyright (c) 2003-2004 Fabrice Bellard
 * Copyright (c) 2007 Intel Corporation
 * Copyright 2009 Red Hat, Inc. and/or its affiliates.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a copy
 * of this software and associated करोcumentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modअगरy, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 * Authors:
 *   Yaozu (Eddie) Dong <Eddie.करोng@पूर्णांकel.com>
 *   Port from Qemu.
 */
#समावेश <linux/mm.h>
#समावेश <linux/slab.h>
#समावेश <linux/bitops.h>
#समावेश "irq.h"

#समावेश <linux/kvm_host.h>
#समावेश "trace.h"

#घोषणा pr_pic_unimpl(fmt, ...)	\
	pr_err_ratelimited("kvm: pic: " fmt, ## __VA_ARGS__)

अटल व्योम pic_irq_request(काष्ठा kvm *kvm, पूर्णांक level);

अटल व्योम pic_lock(काष्ठा kvm_pic *s)
	__acquires(&s->lock)
अणु
	spin_lock(&s->lock);
पूर्ण

अटल व्योम pic_unlock(काष्ठा kvm_pic *s)
	__releases(&s->lock)
अणु
	bool wakeup = s->wakeup_needed;
	काष्ठा kvm_vcpu *vcpu;
	पूर्णांक i;

	s->wakeup_needed = false;

	spin_unlock(&s->lock);

	अगर (wakeup) अणु
		kvm_क्रम_each_vcpu(i, vcpu, s->kvm) अणु
			अगर (kvm_apic_accept_pic_पूर्णांकr(vcpu)) अणु
				kvm_make_request(KVM_REQ_EVENT, vcpu);
				kvm_vcpu_kick(vcpu);
				वापस;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम pic_clear_isr(काष्ठा kvm_kpic_state *s, पूर्णांक irq)
अणु
	s->isr &= ~(1 << irq);
	अगर (s != &s->pics_state->pics[0])
		irq += 8;
	/*
	 * We are dropping lock जबतक calling ack notअगरiers since ack
	 * notअगरier callbacks क्रम asचिन्हित devices call पूर्णांकo PIC recursively.
	 * Other पूर्णांकerrupt may be delivered to PIC जबतक lock is dropped but
	 * it should be safe since PIC state is alपढ़ोy updated at this stage.
	 */
	pic_unlock(s->pics_state);
	kvm_notअगरy_acked_irq(s->pics_state->kvm, SELECT_PIC(irq), irq);
	pic_lock(s->pics_state);
पूर्ण

/*
 * set irq level. If an edge is detected, then the IRR is set to 1
 */
अटल अंतरभूत पूर्णांक pic_set_irq1(काष्ठा kvm_kpic_state *s, पूर्णांक irq, पूर्णांक level)
अणु
	पूर्णांक mask, ret = 1;
	mask = 1 << irq;
	अगर (s->elcr & mask)	/* level triggered */
		अगर (level) अणु
			ret = !(s->irr & mask);
			s->irr |= mask;
			s->last_irr |= mask;
		पूर्ण अन्यथा अणु
			s->irr &= ~mask;
			s->last_irr &= ~mask;
		पूर्ण
	अन्यथा	/* edge triggered */
		अगर (level) अणु
			अगर ((s->last_irr & mask) == 0) अणु
				ret = !(s->irr & mask);
				s->irr |= mask;
			पूर्ण
			s->last_irr |= mask;
		पूर्ण अन्यथा
			s->last_irr &= ~mask;

	वापस (s->imr & mask) ? -1 : ret;
पूर्ण

/*
 * वापस the highest priority found in mask (highest = smallest
 * number). Return 8 अगर no irq
 */
अटल अंतरभूत पूर्णांक get_priority(काष्ठा kvm_kpic_state *s, पूर्णांक mask)
अणु
	पूर्णांक priority;
	अगर (mask == 0)
		वापस 8;
	priority = 0;
	जबतक ((mask & (1 << ((priority + s->priority_add) & 7))) == 0)
		priority++;
	वापस priority;
पूर्ण

/*
 * वापस the pic wanted पूर्णांकerrupt. वापस -1 अगर none
 */
अटल पूर्णांक pic_get_irq(काष्ठा kvm_kpic_state *s)
अणु
	पूर्णांक mask, cur_priority, priority;

	mask = s->irr & ~s->imr;
	priority = get_priority(s, mask);
	अगर (priority == 8)
		वापस -1;
	/*
	 * compute current priority. If special fully nested mode on the
	 * master, the IRQ coming from the slave is not taken पूर्णांकo account
	 * क्रम the priority computation.
	 */
	mask = s->isr;
	अगर (s->special_fully_nested_mode && s == &s->pics_state->pics[0])
		mask &= ~(1 << 2);
	cur_priority = get_priority(s, mask);
	अगर (priority < cur_priority)
		/*
		 * higher priority found: an irq should be generated
		 */
		वापस (priority + s->priority_add) & 7;
	अन्यथा
		वापस -1;
पूर्ण

/*
 * उठाओ irq to CPU अगर necessary. must be called every समय the active
 * irq may change
 */
अटल व्योम pic_update_irq(काष्ठा kvm_pic *s)
अणु
	पूर्णांक irq2, irq;

	irq2 = pic_get_irq(&s->pics[1]);
	अगर (irq2 >= 0) अणु
		/*
		 * अगर irq request by slave pic, संकेत master PIC
		 */
		pic_set_irq1(&s->pics[0], 2, 1);
		pic_set_irq1(&s->pics[0], 2, 0);
	पूर्ण
	irq = pic_get_irq(&s->pics[0]);
	pic_irq_request(s->kvm, irq >= 0);
पूर्ण

व्योम kvm_pic_update_irq(काष्ठा kvm_pic *s)
अणु
	pic_lock(s);
	pic_update_irq(s);
	pic_unlock(s);
पूर्ण

पूर्णांक kvm_pic_set_irq(काष्ठा kvm_pic *s, पूर्णांक irq, पूर्णांक irq_source_id, पूर्णांक level)
अणु
	पूर्णांक ret, irq_level;

	BUG_ON(irq < 0 || irq >= PIC_NUM_PINS);

	pic_lock(s);
	irq_level = __kvm_irq_line_state(&s->irq_states[irq],
					 irq_source_id, level);
	ret = pic_set_irq1(&s->pics[irq >> 3], irq & 7, irq_level);
	pic_update_irq(s);
	trace_kvm_pic_set_irq(irq >> 3, irq & 7, s->pics[irq >> 3].elcr,
			      s->pics[irq >> 3].imr, ret == 0);
	pic_unlock(s);

	वापस ret;
पूर्ण

व्योम kvm_pic_clear_all(काष्ठा kvm_pic *s, पूर्णांक irq_source_id)
अणु
	पूर्णांक i;

	pic_lock(s);
	क्रम (i = 0; i < PIC_NUM_PINS; i++)
		__clear_bit(irq_source_id, &s->irq_states[i]);
	pic_unlock(s);
पूर्ण

/*
 * acknowledge पूर्णांकerrupt 'irq'
 */
अटल अंतरभूत व्योम pic_पूर्णांकack(काष्ठा kvm_kpic_state *s, पूर्णांक irq)
अणु
	s->isr |= 1 << irq;
	/*
	 * We करोn't clear a level sensitive पूर्णांकerrupt here
	 */
	अगर (!(s->elcr & (1 << irq)))
		s->irr &= ~(1 << irq);

	अगर (s->स्वतः_eoi) अणु
		अगर (s->rotate_on_स्वतः_eoi)
			s->priority_add = (irq + 1) & 7;
		pic_clear_isr(s, irq);
	पूर्ण

पूर्ण

पूर्णांक kvm_pic_पढ़ो_irq(काष्ठा kvm *kvm)
अणु
	पूर्णांक irq, irq2, पूर्णांकno;
	काष्ठा kvm_pic *s = kvm->arch.vpic;

	s->output = 0;

	pic_lock(s);
	irq = pic_get_irq(&s->pics[0]);
	अगर (irq >= 0) अणु
		pic_पूर्णांकack(&s->pics[0], irq);
		अगर (irq == 2) अणु
			irq2 = pic_get_irq(&s->pics[1]);
			अगर (irq2 >= 0)
				pic_पूर्णांकack(&s->pics[1], irq2);
			अन्यथा
				/*
				 * spurious IRQ on slave controller
				 */
				irq2 = 7;
			पूर्णांकno = s->pics[1].irq_base + irq2;
			irq = irq2 + 8;
		पूर्ण अन्यथा
			पूर्णांकno = s->pics[0].irq_base + irq;
	पूर्ण अन्यथा अणु
		/*
		 * spurious IRQ on host controller
		 */
		irq = 7;
		पूर्णांकno = s->pics[0].irq_base + irq;
	पूर्ण
	pic_update_irq(s);
	pic_unlock(s);

	वापस पूर्णांकno;
पूर्ण

अटल व्योम kvm_pic_reset(काष्ठा kvm_kpic_state *s)
अणु
	पूर्णांक irq, i;
	काष्ठा kvm_vcpu *vcpu;
	u8 edge_irr = s->irr & ~s->elcr;
	bool found = false;

	s->last_irr = 0;
	s->irr &= s->elcr;
	s->imr = 0;
	s->priority_add = 0;
	s->special_mask = 0;
	s->पढ़ो_reg_select = 0;
	अगर (!s->init4) अणु
		s->special_fully_nested_mode = 0;
		s->स्वतः_eoi = 0;
	पूर्ण
	s->init_state = 1;

	kvm_क्रम_each_vcpu(i, vcpu, s->pics_state->kvm)
		अगर (kvm_apic_accept_pic_पूर्णांकr(vcpu)) अणु
			found = true;
			अवरोध;
		पूर्ण


	अगर (!found)
		वापस;

	क्रम (irq = 0; irq < PIC_NUM_PINS/2; irq++)
		अगर (edge_irr & (1 << irq))
			pic_clear_isr(s, irq);
पूर्ण

अटल व्योम pic_ioport_ग_लिखो(व्योम *opaque, u32 addr, u32 val)
अणु
	काष्ठा kvm_kpic_state *s = opaque;
	पूर्णांक priority, cmd, irq;

	addr &= 1;
	अगर (addr == 0) अणु
		अगर (val & 0x10) अणु
			s->init4 = val & 1;
			अगर (val & 0x02)
				pr_pic_unimpl("single mode not supported");
			अगर (val & 0x08)
				pr_pic_unimpl(
						"level sensitive irq not supported");
			kvm_pic_reset(s);
		पूर्ण अन्यथा अगर (val & 0x08) अणु
			अगर (val & 0x04)
				s->poll = 1;
			अगर (val & 0x02)
				s->पढ़ो_reg_select = val & 1;
			अगर (val & 0x40)
				s->special_mask = (val >> 5) & 1;
		पूर्ण अन्यथा अणु
			cmd = val >> 5;
			चयन (cmd) अणु
			हाल 0:
			हाल 4:
				s->rotate_on_स्वतः_eoi = cmd >> 2;
				अवरोध;
			हाल 1:	/* end of पूर्णांकerrupt */
			हाल 5:
				priority = get_priority(s, s->isr);
				अगर (priority != 8) अणु
					irq = (priority + s->priority_add) & 7;
					अगर (cmd == 5)
						s->priority_add = (irq + 1) & 7;
					pic_clear_isr(s, irq);
					pic_update_irq(s->pics_state);
				पूर्ण
				अवरोध;
			हाल 3:
				irq = val & 7;
				pic_clear_isr(s, irq);
				pic_update_irq(s->pics_state);
				अवरोध;
			हाल 6:
				s->priority_add = (val + 1) & 7;
				pic_update_irq(s->pics_state);
				अवरोध;
			हाल 7:
				irq = val & 7;
				s->priority_add = (irq + 1) & 7;
				pic_clear_isr(s, irq);
				pic_update_irq(s->pics_state);
				अवरोध;
			शेष:
				अवरोध;	/* no operation */
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा
		चयन (s->init_state) अणु
		हाल 0: अणु /* normal mode */
			u8 imr_dअगरf = s->imr ^ val,
				off = (s == &s->pics_state->pics[0]) ? 0 : 8;
			s->imr = val;
			क्रम (irq = 0; irq < PIC_NUM_PINS/2; irq++)
				अगर (imr_dअगरf & (1 << irq))
					kvm_fire_mask_notअगरiers(
						s->pics_state->kvm,
						SELECT_PIC(irq + off),
						irq + off,
						!!(s->imr & (1 << irq)));
			pic_update_irq(s->pics_state);
			अवरोध;
		पूर्ण
		हाल 1:
			s->irq_base = val & 0xf8;
			s->init_state = 2;
			अवरोध;
		हाल 2:
			अगर (s->init4)
				s->init_state = 3;
			अन्यथा
				s->init_state = 0;
			अवरोध;
		हाल 3:
			s->special_fully_nested_mode = (val >> 4) & 1;
			s->स्वतः_eoi = (val >> 1) & 1;
			s->init_state = 0;
			अवरोध;
		पूर्ण
पूर्ण

अटल u32 pic_poll_पढ़ो(काष्ठा kvm_kpic_state *s, u32 addr1)
अणु
	पूर्णांक ret;

	ret = pic_get_irq(s);
	अगर (ret >= 0) अणु
		अगर (addr1 >> 7) अणु
			s->pics_state->pics[0].isr &= ~(1 << 2);
			s->pics_state->pics[0].irr &= ~(1 << 2);
		पूर्ण
		s->irr &= ~(1 << ret);
		pic_clear_isr(s, ret);
		अगर (addr1 >> 7 || ret != 2)
			pic_update_irq(s->pics_state);
	पूर्ण अन्यथा अणु
		ret = 0x07;
		pic_update_irq(s->pics_state);
	पूर्ण

	वापस ret;
पूर्ण

अटल u32 pic_ioport_पढ़ो(व्योम *opaque, u32 addr)
अणु
	काष्ठा kvm_kpic_state *s = opaque;
	पूर्णांक ret;

	अगर (s->poll) अणु
		ret = pic_poll_पढ़ो(s, addr);
		s->poll = 0;
	पूर्ण अन्यथा
		अगर ((addr & 1) == 0)
			अगर (s->पढ़ो_reg_select)
				ret = s->isr;
			अन्यथा
				ret = s->irr;
		अन्यथा
			ret = s->imr;
	वापस ret;
पूर्ण

अटल व्योम elcr_ioport_ग_लिखो(व्योम *opaque, u32 addr, u32 val)
अणु
	काष्ठा kvm_kpic_state *s = opaque;
	s->elcr = val & s->elcr_mask;
पूर्ण

अटल u32 elcr_ioport_पढ़ो(व्योम *opaque, u32 addr1)
अणु
	काष्ठा kvm_kpic_state *s = opaque;
	वापस s->elcr;
पूर्ण

अटल पूर्णांक picdev_ग_लिखो(काष्ठा kvm_pic *s,
			 gpa_t addr, पूर्णांक len, स्थिर व्योम *val)
अणु
	अचिन्हित अक्षर data = *(अचिन्हित अक्षर *)val;

	अगर (len != 1) अणु
		pr_pic_unimpl("non byte write\n");
		वापस 0;
	पूर्ण
	चयन (addr) अणु
	हाल 0x20:
	हाल 0x21:
		pic_lock(s);
		pic_ioport_ग_लिखो(&s->pics[0], addr, data);
		pic_unlock(s);
		अवरोध;
	हाल 0xa0:
	हाल 0xa1:
		pic_lock(s);
		pic_ioport_ग_लिखो(&s->pics[1], addr, data);
		pic_unlock(s);
		अवरोध;
	हाल 0x4d0:
	हाल 0x4d1:
		pic_lock(s);
		elcr_ioport_ग_लिखो(&s->pics[addr & 1], addr, data);
		pic_unlock(s);
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक picdev_पढ़ो(काष्ठा kvm_pic *s,
		       gpa_t addr, पूर्णांक len, व्योम *val)
अणु
	अचिन्हित अक्षर *data = (अचिन्हित अक्षर *)val;

	अगर (len != 1) अणु
		स_रखो(val, 0, len);
		pr_pic_unimpl("non byte read\n");
		वापस 0;
	पूर्ण
	चयन (addr) अणु
	हाल 0x20:
	हाल 0x21:
	हाल 0xa0:
	हाल 0xa1:
		pic_lock(s);
		*data = pic_ioport_पढ़ो(&s->pics[addr >> 7], addr);
		pic_unlock(s);
		अवरोध;
	हाल 0x4d0:
	हाल 0x4d1:
		pic_lock(s);
		*data = elcr_ioport_पढ़ो(&s->pics[addr & 1], addr);
		pic_unlock(s);
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक picdev_master_ग_लिखो(काष्ठा kvm_vcpu *vcpu, काष्ठा kvm_io_device *dev,
			       gpa_t addr, पूर्णांक len, स्थिर व्योम *val)
अणु
	वापस picdev_ग_लिखो(container_of(dev, काष्ठा kvm_pic, dev_master),
			    addr, len, val);
पूर्ण

अटल पूर्णांक picdev_master_पढ़ो(काष्ठा kvm_vcpu *vcpu, काष्ठा kvm_io_device *dev,
			      gpa_t addr, पूर्णांक len, व्योम *val)
अणु
	वापस picdev_पढ़ो(container_of(dev, काष्ठा kvm_pic, dev_master),
			    addr, len, val);
पूर्ण

अटल पूर्णांक picdev_slave_ग_लिखो(काष्ठा kvm_vcpu *vcpu, काष्ठा kvm_io_device *dev,
			      gpa_t addr, पूर्णांक len, स्थिर व्योम *val)
अणु
	वापस picdev_ग_लिखो(container_of(dev, काष्ठा kvm_pic, dev_slave),
			    addr, len, val);
पूर्ण

अटल पूर्णांक picdev_slave_पढ़ो(काष्ठा kvm_vcpu *vcpu, काष्ठा kvm_io_device *dev,
			     gpa_t addr, पूर्णांक len, व्योम *val)
अणु
	वापस picdev_पढ़ो(container_of(dev, काष्ठा kvm_pic, dev_slave),
			    addr, len, val);
पूर्ण

अटल पूर्णांक picdev_eclr_ग_लिखो(काष्ठा kvm_vcpu *vcpu, काष्ठा kvm_io_device *dev,
			     gpa_t addr, पूर्णांक len, स्थिर व्योम *val)
अणु
	वापस picdev_ग_लिखो(container_of(dev, काष्ठा kvm_pic, dev_eclr),
			    addr, len, val);
पूर्ण

अटल पूर्णांक picdev_eclr_पढ़ो(काष्ठा kvm_vcpu *vcpu, काष्ठा kvm_io_device *dev,
			    gpa_t addr, पूर्णांक len, व्योम *val)
अणु
	वापस picdev_पढ़ो(container_of(dev, काष्ठा kvm_pic, dev_eclr),
			    addr, len, val);
पूर्ण

/*
 * callback when PIC0 irq status changed
 */
अटल व्योम pic_irq_request(काष्ठा kvm *kvm, पूर्णांक level)
अणु
	काष्ठा kvm_pic *s = kvm->arch.vpic;

	अगर (!s->output)
		s->wakeup_needed = true;
	s->output = level;
पूर्ण

अटल स्थिर काष्ठा kvm_io_device_ops picdev_master_ops = अणु
	.पढ़ो     = picdev_master_पढ़ो,
	.ग_लिखो    = picdev_master_ग_लिखो,
पूर्ण;

अटल स्थिर काष्ठा kvm_io_device_ops picdev_slave_ops = अणु
	.पढ़ो     = picdev_slave_पढ़ो,
	.ग_लिखो    = picdev_slave_ग_लिखो,
पूर्ण;

अटल स्थिर काष्ठा kvm_io_device_ops picdev_eclr_ops = अणु
	.पढ़ो     = picdev_eclr_पढ़ो,
	.ग_लिखो    = picdev_eclr_ग_लिखो,
पूर्ण;

पूर्णांक kvm_pic_init(काष्ठा kvm *kvm)
अणु
	काष्ठा kvm_pic *s;
	पूर्णांक ret;

	s = kzalloc(माप(काष्ठा kvm_pic), GFP_KERNEL_ACCOUNT);
	अगर (!s)
		वापस -ENOMEM;
	spin_lock_init(&s->lock);
	s->kvm = kvm;
	s->pics[0].elcr_mask = 0xf8;
	s->pics[1].elcr_mask = 0xde;
	s->pics[0].pics_state = s;
	s->pics[1].pics_state = s;

	/*
	 * Initialize PIO device
	 */
	kvm_iodevice_init(&s->dev_master, &picdev_master_ops);
	kvm_iodevice_init(&s->dev_slave, &picdev_slave_ops);
	kvm_iodevice_init(&s->dev_eclr, &picdev_eclr_ops);
	mutex_lock(&kvm->slots_lock);
	ret = kvm_io_bus_रेजिस्टर_dev(kvm, KVM_PIO_BUS, 0x20, 2,
				      &s->dev_master);
	अगर (ret < 0)
		जाओ fail_unlock;

	ret = kvm_io_bus_रेजिस्टर_dev(kvm, KVM_PIO_BUS, 0xa0, 2, &s->dev_slave);
	अगर (ret < 0)
		जाओ fail_unreg_2;

	ret = kvm_io_bus_रेजिस्टर_dev(kvm, KVM_PIO_BUS, 0x4d0, 2, &s->dev_eclr);
	अगर (ret < 0)
		जाओ fail_unreg_1;

	mutex_unlock(&kvm->slots_lock);

	kvm->arch.vpic = s;

	वापस 0;

fail_unreg_1:
	kvm_io_bus_unरेजिस्टर_dev(kvm, KVM_PIO_BUS, &s->dev_slave);

fail_unreg_2:
	kvm_io_bus_unरेजिस्टर_dev(kvm, KVM_PIO_BUS, &s->dev_master);

fail_unlock:
	mutex_unlock(&kvm->slots_lock);

	kमुक्त(s);

	वापस ret;
पूर्ण

व्योम kvm_pic_destroy(काष्ठा kvm *kvm)
अणु
	काष्ठा kvm_pic *vpic = kvm->arch.vpic;

	अगर (!vpic)
		वापस;

	mutex_lock(&kvm->slots_lock);
	kvm_io_bus_unरेजिस्टर_dev(vpic->kvm, KVM_PIO_BUS, &vpic->dev_master);
	kvm_io_bus_unरेजिस्टर_dev(vpic->kvm, KVM_PIO_BUS, &vpic->dev_slave);
	kvm_io_bus_unरेजिस्टर_dev(vpic->kvm, KVM_PIO_BUS, &vpic->dev_eclr);
	mutex_unlock(&kvm->slots_lock);

	kvm->arch.vpic = शून्य;
	kमुक्त(vpic);
पूर्ण
