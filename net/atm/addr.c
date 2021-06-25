<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* net/aपंचांग/addr.c - Local ATM address registry */

/* Written 1995-2000 by Werner Almesberger, EPFL LRC/ICA */

#समावेश <linux/aपंचांग.h>
#समावेश <linux/aपंचांगdev.h>
#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>

#समावेश "signaling.h"
#समावेश "addr.h"

अटल पूर्णांक check_addr(स्थिर काष्ठा sockaddr_aपंचांगsvc *addr)
अणु
	पूर्णांक i;

	अगर (addr->sas_family != AF_ATMSVC)
		वापस -EAFNOSUPPORT;
	अगर (!*addr->sas_addr.pub)
		वापस *addr->sas_addr.prv ? 0 : -EINVAL;
	क्रम (i = 1; i < ATM_E164_LEN + 1; i++)	/* make sure it's \0-terminated */
		अगर (!addr->sas_addr.pub[i])
			वापस 0;
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक identical(स्थिर काष्ठा sockaddr_aपंचांगsvc *a, स्थिर काष्ठा sockaddr_aपंचांगsvc *b)
अणु
	अगर (*a->sas_addr.prv)
		अगर (स_भेद(a->sas_addr.prv, b->sas_addr.prv, ATM_ESA_LEN))
			वापस 0;
	अगर (!*a->sas_addr.pub)
		वापस !*b->sas_addr.pub;
	अगर (!*b->sas_addr.pub)
		वापस 0;
	वापस !म_भेद(a->sas_addr.pub, b->sas_addr.pub);
पूर्ण

अटल व्योम notअगरy_sigd(स्थिर काष्ठा aपंचांग_dev *dev)
अणु
	काष्ठा sockaddr_aपंचांगpvc pvc;

	pvc.sap_addr.itf = dev->number;
	sigd_enq(शून्य, as_itf_notअगरy, शून्य, &pvc, शून्य);
पूर्ण

व्योम aपंचांग_reset_addr(काष्ठा aपंचांग_dev *dev, क्रमागत aपंचांग_addr_type_t atype)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा aपंचांग_dev_addr *this, *p;
	काष्ठा list_head *head;

	spin_lock_irqsave(&dev->lock, flags);
	अगर (atype == ATM_ADDR_LECS)
		head = &dev->lecs;
	अन्यथा
		head = &dev->local;
	list_क्रम_each_entry_safe(this, p, head, entry) अणु
		list_del(&this->entry);
		kमुक्त(this);
	पूर्ण
	spin_unlock_irqrestore(&dev->lock, flags);
	अगर (head == &dev->local)
		notअगरy_sigd(dev);
पूर्ण

पूर्णांक aपंचांग_add_addr(काष्ठा aपंचांग_dev *dev, स्थिर काष्ठा sockaddr_aपंचांगsvc *addr,
		 क्रमागत aपंचांग_addr_type_t atype)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा aपंचांग_dev_addr *this;
	काष्ठा list_head *head;
	पूर्णांक error;

	error = check_addr(addr);
	अगर (error)
		वापस error;
	spin_lock_irqsave(&dev->lock, flags);
	अगर (atype == ATM_ADDR_LECS)
		head = &dev->lecs;
	अन्यथा
		head = &dev->local;
	list_क्रम_each_entry(this, head, entry) अणु
		अगर (identical(&this->addr, addr)) अणु
			spin_unlock_irqrestore(&dev->lock, flags);
			वापस -EEXIST;
		पूर्ण
	पूर्ण
	this = kदो_स्मृति(माप(काष्ठा aपंचांग_dev_addr), GFP_ATOMIC);
	अगर (!this) अणु
		spin_unlock_irqrestore(&dev->lock, flags);
		वापस -ENOMEM;
	पूर्ण
	this->addr = *addr;
	list_add(&this->entry, head);
	spin_unlock_irqrestore(&dev->lock, flags);
	अगर (head == &dev->local)
		notअगरy_sigd(dev);
	वापस 0;
पूर्ण

पूर्णांक aपंचांग_del_addr(काष्ठा aपंचांग_dev *dev, स्थिर काष्ठा sockaddr_aपंचांगsvc *addr,
		 क्रमागत aपंचांग_addr_type_t atype)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा aपंचांग_dev_addr *this;
	काष्ठा list_head *head;
	पूर्णांक error;

	error = check_addr(addr);
	अगर (error)
		वापस error;
	spin_lock_irqsave(&dev->lock, flags);
	अगर (atype == ATM_ADDR_LECS)
		head = &dev->lecs;
	अन्यथा
		head = &dev->local;
	list_क्रम_each_entry(this, head, entry) अणु
		अगर (identical(&this->addr, addr)) अणु
			list_del(&this->entry);
			spin_unlock_irqrestore(&dev->lock, flags);
			kमुक्त(this);
			अगर (head == &dev->local)
				notअगरy_sigd(dev);
			वापस 0;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&dev->lock, flags);
	वापस -ENOENT;
पूर्ण

पूर्णांक aपंचांग_get_addr(काष्ठा aपंचांग_dev *dev, काष्ठा sockaddr_aपंचांगsvc __user * buf,
		 माप_प्रकार size, क्रमागत aपंचांग_addr_type_t atype)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा aपंचांग_dev_addr *this;
	काष्ठा list_head *head;
	पूर्णांक total = 0, error;
	काष्ठा sockaddr_aपंचांगsvc *पंचांगp_buf, *पंचांगp_bufp;

	spin_lock_irqsave(&dev->lock, flags);
	अगर (atype == ATM_ADDR_LECS)
		head = &dev->lecs;
	अन्यथा
		head = &dev->local;
	list_क्रम_each_entry(this, head, entry)
	    total += माप(काष्ठा sockaddr_aपंचांगsvc);
	पंचांगp_buf = पंचांगp_bufp = kदो_स्मृति(total, GFP_ATOMIC);
	अगर (!पंचांगp_buf) अणु
		spin_unlock_irqrestore(&dev->lock, flags);
		वापस -ENOMEM;
	पूर्ण
	list_क्रम_each_entry(this, head, entry)
	    स_नकल(पंचांगp_bufp++, &this->addr, माप(काष्ठा sockaddr_aपंचांगsvc));
	spin_unlock_irqrestore(&dev->lock, flags);
	error = total > size ? -E2BIG : total;
	अगर (copy_to_user(buf, पंचांगp_buf, total < size ? total : size))
		error = -EFAULT;
	kमुक्त(पंचांगp_buf);
	वापस error;
पूर्ण
