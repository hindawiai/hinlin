<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */

#अगर_अघोषित __KVM_IODEV_H__
#घोषणा __KVM_IODEV_H__

#समावेश <linux/kvm_types.h>
#समावेश <linux/त्रुटिसं.स>

काष्ठा kvm_io_device;
काष्ठा kvm_vcpu;

/**
 * kvm_io_device_ops are called under kvm slots_lock.
 * पढ़ो and ग_लिखो handlers वापस 0 अगर the transaction has been handled,
 * or non-zero to have it passed to the next device.
 **/
काष्ठा kvm_io_device_ops अणु
	पूर्णांक (*पढ़ो)(काष्ठा kvm_vcpu *vcpu,
		    काष्ठा kvm_io_device *this,
		    gpa_t addr,
		    पूर्णांक len,
		    व्योम *val);
	पूर्णांक (*ग_लिखो)(काष्ठा kvm_vcpu *vcpu,
		     काष्ठा kvm_io_device *this,
		     gpa_t addr,
		     पूर्णांक len,
		     स्थिर व्योम *val);
	व्योम (*deकाष्ठाor)(काष्ठा kvm_io_device *this);
पूर्ण;


काष्ठा kvm_io_device अणु
	स्थिर काष्ठा kvm_io_device_ops *ops;
पूर्ण;

अटल अंतरभूत व्योम kvm_iodevice_init(काष्ठा kvm_io_device *dev,
				     स्थिर काष्ठा kvm_io_device_ops *ops)
अणु
	dev->ops = ops;
पूर्ण

अटल अंतरभूत पूर्णांक kvm_iodevice_पढ़ो(काष्ठा kvm_vcpu *vcpu,
				    काष्ठा kvm_io_device *dev, gpa_t addr,
				    पूर्णांक l, व्योम *v)
अणु
	वापस dev->ops->पढ़ो ? dev->ops->पढ़ो(vcpu, dev, addr, l, v)
				: -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक kvm_iodevice_ग_लिखो(काष्ठा kvm_vcpu *vcpu,
				     काष्ठा kvm_io_device *dev, gpa_t addr,
				     पूर्णांक l, स्थिर व्योम *v)
अणु
	वापस dev->ops->ग_लिखो ? dev->ops->ग_लिखो(vcpu, dev, addr, l, v)
				 : -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत व्योम kvm_iodevice_deकाष्ठाor(काष्ठा kvm_io_device *dev)
अणु
	अगर (dev->ops->deकाष्ठाor)
		dev->ops->deकाष्ठाor(dev);
पूर्ण

#पूर्ण_अगर /* __KVM_IODEV_H__ */
