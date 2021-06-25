<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2015-2018, Intel Corporation.
 */

#घोषणा pr_fmt(fmt) "kcs-bmc: " fmt

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/पन.स>
#समावेश <linux/ipmi_bmc.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/poll.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>

#समावेश "kcs_bmc.h"

#घोषणा DEVICE_NAME "ipmi-kcs"

#घोषणा KCS_MSG_बफ_मान    1000

#घोषणा KCS_ZERO_DATA     0


/* IPMI 2.0 - Table 9-1, KCS Interface Status Register Bits */
#घोषणा KCS_STATUS_STATE(state) (state << 6)
#घोषणा KCS_STATUS_STATE_MASK   GENMASK(7, 6)
#घोषणा KCS_STATUS_CMD_DAT      BIT(3)
#घोषणा KCS_STATUS_SMS_ATN      BIT(2)
#घोषणा KCS_STATUS_IBF          BIT(1)
#घोषणा KCS_STATUS_OBF          BIT(0)

/* IPMI 2.0 - Table 9-2, KCS Interface State Bits */
क्रमागत kcs_states अणु
	IDLE_STATE  = 0,
	READ_STATE  = 1,
	WRITE_STATE = 2,
	ERROR_STATE = 3,
पूर्ण;

/* IPMI 2.0 - Table 9-3, KCS Interface Control Codes */
#घोषणा KCS_CMD_GET_STATUS_ABORT  0x60
#घोषणा KCS_CMD_WRITE_START       0x61
#घोषणा KCS_CMD_WRITE_END         0x62
#घोषणा KCS_CMD_READ_BYTE         0x68

अटल अंतरभूत u8 पढ़ो_data(काष्ठा kcs_bmc *kcs_bmc)
अणु
	वापस kcs_bmc->io_inputb(kcs_bmc, kcs_bmc->ioreg.idr);
पूर्ण

अटल अंतरभूत व्योम ग_लिखो_data(काष्ठा kcs_bmc *kcs_bmc, u8 data)
अणु
	kcs_bmc->io_outputb(kcs_bmc, kcs_bmc->ioreg.odr, data);
पूर्ण

अटल अंतरभूत u8 पढ़ो_status(काष्ठा kcs_bmc *kcs_bmc)
अणु
	वापस kcs_bmc->io_inputb(kcs_bmc, kcs_bmc->ioreg.str);
पूर्ण

अटल अंतरभूत व्योम ग_लिखो_status(काष्ठा kcs_bmc *kcs_bmc, u8 data)
अणु
	kcs_bmc->io_outputb(kcs_bmc, kcs_bmc->ioreg.str, data);
पूर्ण

अटल व्योम update_status_bits(काष्ठा kcs_bmc *kcs_bmc, u8 mask, u8 val)
अणु
	u8 पंचांगp = पढ़ो_status(kcs_bmc);

	पंचांगp &= ~mask;
	पंचांगp |= val & mask;

	ग_लिखो_status(kcs_bmc, पंचांगp);
पूर्ण

अटल अंतरभूत व्योम set_state(काष्ठा kcs_bmc *kcs_bmc, u8 state)
अणु
	update_status_bits(kcs_bmc, KCS_STATUS_STATE_MASK,
					KCS_STATUS_STATE(state));
पूर्ण

अटल व्योम kcs_क्रमce_पात(काष्ठा kcs_bmc *kcs_bmc)
अणु
	set_state(kcs_bmc, ERROR_STATE);
	पढ़ो_data(kcs_bmc);
	ग_लिखो_data(kcs_bmc, KCS_ZERO_DATA);

	kcs_bmc->phase = KCS_PHASE_ERROR;
	kcs_bmc->data_in_avail = false;
	kcs_bmc->data_in_idx = 0;
पूर्ण

अटल व्योम kcs_bmc_handle_data(काष्ठा kcs_bmc *kcs_bmc)
अणु
	u8 data;

	चयन (kcs_bmc->phase) अणु
	हाल KCS_PHASE_WRITE_START:
		kcs_bmc->phase = KCS_PHASE_WRITE_DATA;
		fallthrough;

	हाल KCS_PHASE_WRITE_DATA:
		अगर (kcs_bmc->data_in_idx < KCS_MSG_बफ_मान) अणु
			set_state(kcs_bmc, WRITE_STATE);
			ग_लिखो_data(kcs_bmc, KCS_ZERO_DATA);
			kcs_bmc->data_in[kcs_bmc->data_in_idx++] =
						पढ़ो_data(kcs_bmc);
		पूर्ण अन्यथा अणु
			kcs_क्रमce_पात(kcs_bmc);
			kcs_bmc->error = KCS_LENGTH_ERROR;
		पूर्ण
		अवरोध;

	हाल KCS_PHASE_WRITE_END_CMD:
		अगर (kcs_bmc->data_in_idx < KCS_MSG_बफ_मान) अणु
			set_state(kcs_bmc, READ_STATE);
			kcs_bmc->data_in[kcs_bmc->data_in_idx++] =
						पढ़ो_data(kcs_bmc);
			kcs_bmc->phase = KCS_PHASE_WRITE_DONE;
			kcs_bmc->data_in_avail = true;
			wake_up_पूर्णांकerruptible(&kcs_bmc->queue);
		पूर्ण अन्यथा अणु
			kcs_क्रमce_पात(kcs_bmc);
			kcs_bmc->error = KCS_LENGTH_ERROR;
		पूर्ण
		अवरोध;

	हाल KCS_PHASE_READ:
		अगर (kcs_bmc->data_out_idx == kcs_bmc->data_out_len)
			set_state(kcs_bmc, IDLE_STATE);

		data = पढ़ो_data(kcs_bmc);
		अगर (data != KCS_CMD_READ_BYTE) अणु
			set_state(kcs_bmc, ERROR_STATE);
			ग_लिखो_data(kcs_bmc, KCS_ZERO_DATA);
			अवरोध;
		पूर्ण

		अगर (kcs_bmc->data_out_idx == kcs_bmc->data_out_len) अणु
			ग_लिखो_data(kcs_bmc, KCS_ZERO_DATA);
			kcs_bmc->phase = KCS_PHASE_IDLE;
			अवरोध;
		पूर्ण

		ग_लिखो_data(kcs_bmc,
			kcs_bmc->data_out[kcs_bmc->data_out_idx++]);
		अवरोध;

	हाल KCS_PHASE_ABORT_ERROR1:
		set_state(kcs_bmc, READ_STATE);
		पढ़ो_data(kcs_bmc);
		ग_लिखो_data(kcs_bmc, kcs_bmc->error);
		kcs_bmc->phase = KCS_PHASE_ABORT_ERROR2;
		अवरोध;

	हाल KCS_PHASE_ABORT_ERROR2:
		set_state(kcs_bmc, IDLE_STATE);
		पढ़ो_data(kcs_bmc);
		ग_लिखो_data(kcs_bmc, KCS_ZERO_DATA);
		kcs_bmc->phase = KCS_PHASE_IDLE;
		अवरोध;

	शेष:
		kcs_क्रमce_पात(kcs_bmc);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम kcs_bmc_handle_cmd(काष्ठा kcs_bmc *kcs_bmc)
अणु
	u8 cmd;

	set_state(kcs_bmc, WRITE_STATE);
	ग_लिखो_data(kcs_bmc, KCS_ZERO_DATA);

	cmd = पढ़ो_data(kcs_bmc);
	चयन (cmd) अणु
	हाल KCS_CMD_WRITE_START:
		kcs_bmc->phase = KCS_PHASE_WRITE_START;
		kcs_bmc->error = KCS_NO_ERROR;
		kcs_bmc->data_in_avail = false;
		kcs_bmc->data_in_idx = 0;
		अवरोध;

	हाल KCS_CMD_WRITE_END:
		अगर (kcs_bmc->phase != KCS_PHASE_WRITE_DATA) अणु
			kcs_क्रमce_पात(kcs_bmc);
			अवरोध;
		पूर्ण

		kcs_bmc->phase = KCS_PHASE_WRITE_END_CMD;
		अवरोध;

	हाल KCS_CMD_GET_STATUS_ABORT:
		अगर (kcs_bmc->error == KCS_NO_ERROR)
			kcs_bmc->error = KCS_ABORTED_BY_COMMAND;

		kcs_bmc->phase = KCS_PHASE_ABORT_ERROR1;
		kcs_bmc->data_in_avail = false;
		kcs_bmc->data_in_idx = 0;
		अवरोध;

	शेष:
		kcs_क्रमce_पात(kcs_bmc);
		kcs_bmc->error = KCS_ILLEGAL_CONTROL_CODE;
		अवरोध;
	पूर्ण
पूर्ण

पूर्णांक kcs_bmc_handle_event(काष्ठा kcs_bmc *kcs_bmc)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = -ENODATA;
	u8 status;

	spin_lock_irqsave(&kcs_bmc->lock, flags);

	status = पढ़ो_status(kcs_bmc);
	अगर (status & KCS_STATUS_IBF) अणु
		अगर (!kcs_bmc->running)
			kcs_क्रमce_पात(kcs_bmc);
		अन्यथा अगर (status & KCS_STATUS_CMD_DAT)
			kcs_bmc_handle_cmd(kcs_bmc);
		अन्यथा
			kcs_bmc_handle_data(kcs_bmc);

		ret = 0;
	पूर्ण

	spin_unlock_irqrestore(&kcs_bmc->lock, flags);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(kcs_bmc_handle_event);

अटल अंतरभूत काष्ठा kcs_bmc *to_kcs_bmc(काष्ठा file *filp)
अणु
	वापस container_of(filp->निजी_data, काष्ठा kcs_bmc, miscdev);
पूर्ण

अटल पूर्णांक kcs_bmc_खोलो(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा kcs_bmc *kcs_bmc = to_kcs_bmc(filp);
	पूर्णांक ret = 0;

	spin_lock_irq(&kcs_bmc->lock);
	अगर (!kcs_bmc->running)
		kcs_bmc->running = 1;
	अन्यथा
		ret = -EBUSY;
	spin_unlock_irq(&kcs_bmc->lock);

	वापस ret;
पूर्ण

अटल __poll_t kcs_bmc_poll(काष्ठा file *filp, poll_table *रुको)
अणु
	काष्ठा kcs_bmc *kcs_bmc = to_kcs_bmc(filp);
	__poll_t mask = 0;

	poll_रुको(filp, &kcs_bmc->queue, रुको);

	spin_lock_irq(&kcs_bmc->lock);
	अगर (kcs_bmc->data_in_avail)
		mask |= EPOLLIN;
	spin_unlock_irq(&kcs_bmc->lock);

	वापस mask;
पूर्ण

अटल sमाप_प्रकार kcs_bmc_पढ़ो(काष्ठा file *filp, अक्षर __user *buf,
			    माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा kcs_bmc *kcs_bmc = to_kcs_bmc(filp);
	bool data_avail;
	माप_प्रकार data_len;
	sमाप_प्रकार ret;

	अगर (!(filp->f_flags & O_NONBLOCK))
		रुको_event_पूर्णांकerruptible(kcs_bmc->queue,
					 kcs_bmc->data_in_avail);

	mutex_lock(&kcs_bmc->mutex);

	spin_lock_irq(&kcs_bmc->lock);
	data_avail = kcs_bmc->data_in_avail;
	अगर (data_avail) अणु
		data_len = kcs_bmc->data_in_idx;
		स_नकल(kcs_bmc->kbuffer, kcs_bmc->data_in, data_len);
	पूर्ण
	spin_unlock_irq(&kcs_bmc->lock);

	अगर (!data_avail) अणु
		ret = -EAGAIN;
		जाओ out_unlock;
	पूर्ण

	अगर (count < data_len) अणु
		pr_err("channel=%u with too large data : %zu\n",
			kcs_bmc->channel, data_len);

		spin_lock_irq(&kcs_bmc->lock);
		kcs_क्रमce_पात(kcs_bmc);
		spin_unlock_irq(&kcs_bmc->lock);

		ret = -EOVERFLOW;
		जाओ out_unlock;
	पूर्ण

	अगर (copy_to_user(buf, kcs_bmc->kbuffer, data_len)) अणु
		ret = -EFAULT;
		जाओ out_unlock;
	पूर्ण

	ret = data_len;

	spin_lock_irq(&kcs_bmc->lock);
	अगर (kcs_bmc->phase == KCS_PHASE_WRITE_DONE) अणु
		kcs_bmc->phase = KCS_PHASE_WAIT_READ;
		kcs_bmc->data_in_avail = false;
		kcs_bmc->data_in_idx = 0;
	पूर्ण अन्यथा अणु
		ret = -EAGAIN;
	पूर्ण
	spin_unlock_irq(&kcs_bmc->lock);

out_unlock:
	mutex_unlock(&kcs_bmc->mutex);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार kcs_bmc_ग_लिखो(काष्ठा file *filp, स्थिर अक्षर __user *buf,
			     माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा kcs_bmc *kcs_bmc = to_kcs_bmc(filp);
	sमाप_प्रकार ret;

	/* a minimum response size '3' : netfn + cmd + ccode */
	अगर (count < 3 || count > KCS_MSG_बफ_मान)
		वापस -EINVAL;

	mutex_lock(&kcs_bmc->mutex);

	अगर (copy_from_user(kcs_bmc->kbuffer, buf, count)) अणु
		ret = -EFAULT;
		जाओ out_unlock;
	पूर्ण

	spin_lock_irq(&kcs_bmc->lock);
	अगर (kcs_bmc->phase == KCS_PHASE_WAIT_READ) अणु
		kcs_bmc->phase = KCS_PHASE_READ;
		kcs_bmc->data_out_idx = 1;
		kcs_bmc->data_out_len = count;
		स_नकल(kcs_bmc->data_out, kcs_bmc->kbuffer, count);
		ग_लिखो_data(kcs_bmc, kcs_bmc->data_out[0]);
		ret = count;
	पूर्ण अन्यथा अणु
		ret = -EINVAL;
	पूर्ण
	spin_unlock_irq(&kcs_bmc->lock);

out_unlock:
	mutex_unlock(&kcs_bmc->mutex);

	वापस ret;
पूर्ण

अटल दीर्घ kcs_bmc_ioctl(काष्ठा file *filp, अचिन्हित पूर्णांक cmd,
			  अचिन्हित दीर्घ arg)
अणु
	काष्ठा kcs_bmc *kcs_bmc = to_kcs_bmc(filp);
	दीर्घ ret = 0;

	spin_lock_irq(&kcs_bmc->lock);

	चयन (cmd) अणु
	हाल IPMI_BMC_IOCTL_SET_SMS_ATN:
		update_status_bits(kcs_bmc, KCS_STATUS_SMS_ATN,
				   KCS_STATUS_SMS_ATN);
		अवरोध;

	हाल IPMI_BMC_IOCTL_CLEAR_SMS_ATN:
		update_status_bits(kcs_bmc, KCS_STATUS_SMS_ATN,
				   0);
		अवरोध;

	हाल IPMI_BMC_IOCTL_FORCE_ABORT:
		kcs_क्रमce_पात(kcs_bmc);
		अवरोध;

	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	spin_unlock_irq(&kcs_bmc->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक kcs_bmc_release(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा kcs_bmc *kcs_bmc = to_kcs_bmc(filp);

	spin_lock_irq(&kcs_bmc->lock);
	kcs_bmc->running = 0;
	kcs_क्रमce_पात(kcs_bmc);
	spin_unlock_irq(&kcs_bmc->lock);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations kcs_bmc_fops = अणु
	.owner          = THIS_MODULE,
	.खोलो           = kcs_bmc_खोलो,
	.पढ़ो           = kcs_bmc_पढ़ो,
	.ग_लिखो          = kcs_bmc_ग_लिखो,
	.release        = kcs_bmc_release,
	.poll           = kcs_bmc_poll,
	.unlocked_ioctl = kcs_bmc_ioctl,
पूर्ण;

काष्ठा kcs_bmc *kcs_bmc_alloc(काष्ठा device *dev, पूर्णांक माप_priv, u32 channel)
अणु
	काष्ठा kcs_bmc *kcs_bmc;

	kcs_bmc = devm_kzalloc(dev, माप(*kcs_bmc) + माप_priv, GFP_KERNEL);
	अगर (!kcs_bmc)
		वापस शून्य;

	spin_lock_init(&kcs_bmc->lock);
	kcs_bmc->channel = channel;

	mutex_init(&kcs_bmc->mutex);
	init_रुकोqueue_head(&kcs_bmc->queue);

	kcs_bmc->data_in = devm_kदो_स्मृति(dev, KCS_MSG_बफ_मान, GFP_KERNEL);
	kcs_bmc->data_out = devm_kदो_स्मृति(dev, KCS_MSG_बफ_मान, GFP_KERNEL);
	kcs_bmc->kbuffer = devm_kदो_स्मृति(dev, KCS_MSG_बफ_मान, GFP_KERNEL);

	kcs_bmc->miscdev.minor = MISC_DYNAMIC_MINOR;
	kcs_bmc->miscdev.name = devm_kaप्र_लिखो(dev, GFP_KERNEL, "%s%u",
					       DEVICE_NAME, channel);
	अगर (!kcs_bmc->data_in || !kcs_bmc->data_out || !kcs_bmc->kbuffer ||
	    !kcs_bmc->miscdev.name)
		वापस शून्य;
	kcs_bmc->miscdev.fops = &kcs_bmc_fops;

	वापस kcs_bmc;
पूर्ण
EXPORT_SYMBOL(kcs_bmc_alloc);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Haiyue Wang <haiyue.wang@linux.intel.com>");
MODULE_DESCRIPTION("KCS BMC to handle the IPMI request from system software");
