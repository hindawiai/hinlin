<शैली गुरु>
/*
*******************************************************************************
**        O.S   : Linux
**   खाता NAME  : arcmsr_attr.c
**        BY    : Nick Cheng
**   Description: attributes exported to sysfs and device host
*******************************************************************************
** Copyright (C) 2002 - 2005, Areca Technology Corporation All rights reserved
**
**     Web site: www.areca.com.tw
**       E-mail: support@areca.com.tw
**
** This program is मुक्त software; you can redistribute it and/or modअगरy
** it under the terms of the GNU General Public License version 2 as
** published by the Free Software Foundation.
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License क्रम more details.
*******************************************************************************
** Redistribution and use in source and binary क्रमms, with or without
** modअगरication, are permitted provided that the following conditions
** are met:
** 1. Redistributions of source code must retain the above copyright
**    notice, this list of conditions and the following disclaimer.
** 2. Redistributions in binary क्रमm must reproduce the above copyright
**    notice, this list of conditions and the following disclaimer in the
**    करोcumentation and/or other materials provided with the distribution.
** 3. The name of the author may not be used to enकरोrse or promote products
**    derived from this software without specअगरic prior written permission.
**
** THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
** IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
** OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
** IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY सूचीECT, INसूचीECT,
** INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES(INCLUDING,BUT
** NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION)HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE)ARISING IN ANY WAY OUT OF THE USE OF
** THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*******************************************************************************
** For history of changes, see Documentation/scsi/ChangeLog.arcmsr
**     Firmware Specअगरication, see Documentation/scsi/arcmsr_spec.rst
*******************************************************************************
*/
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/delay.h>
#समावेश <linux/pci.h>
#समावेश <linux/circ_buf.h>

#समावेश <scsi/scsi_cmnd.h>
#समावेश <scsi/scsi_device.h>
#समावेश <scsi/scsi_host.h>
#समावेश <scsi/scsi_transport.h>
#समावेश "arcmsr.h"

काष्ठा device_attribute *arcmsr_host_attrs[];

अटल sमाप_प्रकार arcmsr_sysfs_iop_message_पढ़ो(काष्ठा file *filp,
					     काष्ठा kobject *kobj,
					     काष्ठा bin_attribute *bin,
					     अक्षर *buf, loff_t off,
					     माप_प्रकार count)
अणु
	काष्ठा device *dev = container_of(kobj,काष्ठा device,kobj);
	काष्ठा Scsi_Host *host = class_to_shost(dev);
	काष्ठा AdapterControlBlock *acb = (काष्ठा AdapterControlBlock *) host->hostdata;
	uपूर्णांक8_t *pपंचांगpQbuffer;
	पूर्णांक32_t allxfer_len = 0;
	अचिन्हित दीर्घ flags;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EACCES;

	/* करो message unit पढ़ो. */
	pपंचांगpQbuffer = (uपूर्णांक8_t *)buf;
	spin_lock_irqsave(&acb->rqbuffer_lock, flags);
	अगर (acb->rqbuf_getIndex != acb->rqbuf_putIndex) अणु
		अचिन्हित पूर्णांक tail = acb->rqbuf_getIndex;
		अचिन्हित पूर्णांक head = acb->rqbuf_putIndex;
		अचिन्हित पूर्णांक cnt_to_end = CIRC_CNT_TO_END(head, tail, ARCMSR_MAX_QBUFFER);

		allxfer_len = CIRC_CNT(head, tail, ARCMSR_MAX_QBUFFER);
		अगर (allxfer_len > ARCMSR_API_DATA_BUFLEN)
			allxfer_len = ARCMSR_API_DATA_BUFLEN;

		अगर (allxfer_len <= cnt_to_end)
			स_नकल(pपंचांगpQbuffer, acb->rqbuffer + tail, allxfer_len);
		अन्यथा अणु
			स_नकल(pपंचांगpQbuffer, acb->rqbuffer + tail, cnt_to_end);
			स_नकल(pपंचांगpQbuffer + cnt_to_end, acb->rqbuffer, allxfer_len - cnt_to_end);
		पूर्ण
		acb->rqbuf_getIndex = (acb->rqbuf_getIndex + allxfer_len) % ARCMSR_MAX_QBUFFER;
	पूर्ण
	अगर (acb->acb_flags & ACB_F_IOPDATA_OVERFLOW) अणु
		काष्ठा QBUFFER __iomem *prbuffer;
		acb->acb_flags &= ~ACB_F_IOPDATA_OVERFLOW;
		prbuffer = arcmsr_get_iop_rqbuffer(acb);
		अगर (arcmsr_Read_iop_rqbuffer_data(acb, prbuffer) == 0)
			acb->acb_flags |= ACB_F_IOPDATA_OVERFLOW;
	पूर्ण
	spin_unlock_irqrestore(&acb->rqbuffer_lock, flags);
	वापस allxfer_len;
पूर्ण

अटल sमाप_प्रकार arcmsr_sysfs_iop_message_ग_लिखो(काष्ठा file *filp,
					      काष्ठा kobject *kobj,
					      काष्ठा bin_attribute *bin,
					      अक्षर *buf, loff_t off,
					      माप_प्रकार count)
अणु
	काष्ठा device *dev = container_of(kobj,काष्ठा device,kobj);
	काष्ठा Scsi_Host *host = class_to_shost(dev);
	काष्ठा AdapterControlBlock *acb = (काष्ठा AdapterControlBlock *) host->hostdata;
	पूर्णांक32_t user_len, cnt2end;
	uपूर्णांक8_t *pQbuffer, *pपंचांगpuserbuffer;
	अचिन्हित दीर्घ flags;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EACCES;
	अगर (count > ARCMSR_API_DATA_BUFLEN)
		वापस -EINVAL;
	/* करो message unit ग_लिखो. */
	pपंचांगpuserbuffer = (uपूर्णांक8_t *)buf;
	user_len = (पूर्णांक32_t)count;
	spin_lock_irqsave(&acb->wqbuffer_lock, flags);
	अगर (acb->wqbuf_putIndex != acb->wqbuf_getIndex) अणु
		arcmsr_ग_लिखो_ioctldata2iop(acb);
		spin_unlock_irqrestore(&acb->wqbuffer_lock, flags);
		वापस 0;	/*need retry*/
	पूर्ण अन्यथा अणु
		pQbuffer = &acb->wqbuffer[acb->wqbuf_putIndex];
		cnt2end = ARCMSR_MAX_QBUFFER - acb->wqbuf_putIndex;
		अगर (user_len > cnt2end) अणु
			स_नकल(pQbuffer, pपंचांगpuserbuffer, cnt2end);
			pपंचांगpuserbuffer += cnt2end;
			user_len -= cnt2end;
			acb->wqbuf_putIndex = 0;
			pQbuffer = acb->wqbuffer;
		पूर्ण
		स_नकल(pQbuffer, pपंचांगpuserbuffer, user_len);
		acb->wqbuf_putIndex += user_len;
		acb->wqbuf_putIndex %= ARCMSR_MAX_QBUFFER;
		अगर (acb->acb_flags & ACB_F_MESSAGE_WQBUFFER_CLEARED) अणु
			acb->acb_flags &=
				~ACB_F_MESSAGE_WQBUFFER_CLEARED;
			arcmsr_ग_लिखो_ioctldata2iop(acb);
		पूर्ण
		spin_unlock_irqrestore(&acb->wqbuffer_lock, flags);
		वापस count;
	पूर्ण
पूर्ण

अटल sमाप_प्रकार arcmsr_sysfs_iop_message_clear(काष्ठा file *filp,
					      काष्ठा kobject *kobj,
					      काष्ठा bin_attribute *bin,
					      अक्षर *buf, loff_t off,
					      माप_प्रकार count)
अणु
	काष्ठा device *dev = container_of(kobj,काष्ठा device,kobj);
	काष्ठा Scsi_Host *host = class_to_shost(dev);
	काष्ठा AdapterControlBlock *acb = (काष्ठा AdapterControlBlock *) host->hostdata;
	uपूर्णांक8_t *pQbuffer;
	अचिन्हित दीर्घ flags;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EACCES;

	arcmsr_clear_iop2drv_rqueue_buffer(acb);
	acb->acb_flags |=
		(ACB_F_MESSAGE_WQBUFFER_CLEARED
		| ACB_F_MESSAGE_RQBUFFER_CLEARED
		| ACB_F_MESSAGE_WQBUFFER_READED);
	spin_lock_irqsave(&acb->rqbuffer_lock, flags);
	acb->rqbuf_getIndex = 0;
	acb->rqbuf_putIndex = 0;
	spin_unlock_irqrestore(&acb->rqbuffer_lock, flags);
	spin_lock_irqsave(&acb->wqbuffer_lock, flags);
	acb->wqbuf_getIndex = 0;
	acb->wqbuf_putIndex = 0;
	spin_unlock_irqrestore(&acb->wqbuffer_lock, flags);
	pQbuffer = acb->rqbuffer;
	स_रखो(pQbuffer, 0, माप (काष्ठा QBUFFER));
	pQbuffer = acb->wqbuffer;
	स_रखो(pQbuffer, 0, माप (काष्ठा QBUFFER));
	वापस 1;
पूर्ण

अटल स्थिर काष्ठा bin_attribute arcmsr_sysfs_message_पढ़ो_attr = अणु
	.attr = अणु
		.name = "mu_read",
		.mode = S_IRUSR ,
	पूर्ण,
	.size = ARCMSR_API_DATA_BUFLEN,
	.पढ़ो = arcmsr_sysfs_iop_message_पढ़ो,
पूर्ण;

अटल स्थिर काष्ठा bin_attribute arcmsr_sysfs_message_ग_लिखो_attr = अणु
	.attr = अणु
		.name = "mu_write",
		.mode = S_IWUSR,
	पूर्ण,
	.size = ARCMSR_API_DATA_BUFLEN,
	.ग_लिखो = arcmsr_sysfs_iop_message_ग_लिखो,
पूर्ण;

अटल स्थिर काष्ठा bin_attribute arcmsr_sysfs_message_clear_attr = अणु
	.attr = अणु
		.name = "mu_clear",
		.mode = S_IWUSR,
	पूर्ण,
	.size = 1,
	.ग_लिखो = arcmsr_sysfs_iop_message_clear,
पूर्ण;

पूर्णांक arcmsr_alloc_sysfs_attr(काष्ठा AdapterControlBlock *acb)
अणु
	काष्ठा Scsi_Host *host = acb->host;
	पूर्णांक error;

	error = sysfs_create_bin_file(&host->shost_dev.kobj, &arcmsr_sysfs_message_पढ़ो_attr);
	अगर (error) अणु
		prपूर्णांकk(KERN_ERR "arcmsr: alloc sysfs mu_read failed\n");
		जाओ error_bin_file_message_पढ़ो;
	पूर्ण
	error = sysfs_create_bin_file(&host->shost_dev.kobj, &arcmsr_sysfs_message_ग_लिखो_attr);
	अगर (error) अणु
		prपूर्णांकk(KERN_ERR "arcmsr: alloc sysfs mu_write failed\n");
		जाओ error_bin_file_message_ग_लिखो;
	पूर्ण
	error = sysfs_create_bin_file(&host->shost_dev.kobj, &arcmsr_sysfs_message_clear_attr);
	अगर (error) अणु
		prपूर्णांकk(KERN_ERR "arcmsr: alloc sysfs mu_clear failed\n");
		जाओ error_bin_file_message_clear;
	पूर्ण
	वापस 0;
error_bin_file_message_clear:
	sysfs_हटाओ_bin_file(&host->shost_dev.kobj, &arcmsr_sysfs_message_ग_लिखो_attr);
error_bin_file_message_ग_लिखो:
	sysfs_हटाओ_bin_file(&host->shost_dev.kobj, &arcmsr_sysfs_message_पढ़ो_attr);
error_bin_file_message_पढ़ो:
	वापस error;
पूर्ण

व्योम arcmsr_मुक्त_sysfs_attr(काष्ठा AdapterControlBlock *acb)
अणु
	काष्ठा Scsi_Host *host = acb->host;

	sysfs_हटाओ_bin_file(&host->shost_dev.kobj, &arcmsr_sysfs_message_clear_attr);
	sysfs_हटाओ_bin_file(&host->shost_dev.kobj, &arcmsr_sysfs_message_ग_लिखो_attr);
	sysfs_हटाओ_bin_file(&host->shost_dev.kobj, &arcmsr_sysfs_message_पढ़ो_attr);
पूर्ण


अटल sमाप_प्रकार
arcmsr_attr_host_driver_version(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस snम_लिखो(buf, PAGE_SIZE,
			"%s\n",
			ARCMSR_DRIVER_VERSION);
पूर्ण

अटल sमाप_प्रकार
arcmsr_attr_host_driver_posted_cmd(काष्ठा device *dev,
				   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा Scsi_Host *host = class_to_shost(dev);
	काष्ठा AdapterControlBlock *acb =
		(काष्ठा AdapterControlBlock *) host->hostdata;
	वापस snम_लिखो(buf, PAGE_SIZE,
			"%4d\n",
			atomic_पढ़ो(&acb->ccboutstandingcount));
पूर्ण

अटल sमाप_प्रकार
arcmsr_attr_host_driver_reset(काष्ठा device *dev,
			      काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा Scsi_Host *host = class_to_shost(dev);
	काष्ठा AdapterControlBlock *acb =
		(काष्ठा AdapterControlBlock *) host->hostdata;
	वापस snम_लिखो(buf, PAGE_SIZE,
			"%4d\n",
			acb->num_resets);
पूर्ण

अटल sमाप_प्रकार
arcmsr_attr_host_driver_पात(काष्ठा device *dev,
			      काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा Scsi_Host *host = class_to_shost(dev);
	काष्ठा AdapterControlBlock *acb =
		(काष्ठा AdapterControlBlock *) host->hostdata;
	वापस snम_लिखो(buf, PAGE_SIZE,
			"%4d\n",
			acb->num_पातs);
पूर्ण

अटल sमाप_प्रकार
arcmsr_attr_host_fw_model(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  अक्षर *buf)
अणु
	काष्ठा Scsi_Host *host = class_to_shost(dev);
	काष्ठा AdapterControlBlock *acb =
		(काष्ठा AdapterControlBlock *) host->hostdata;
	वापस snम_लिखो(buf, PAGE_SIZE,
			"%s\n",
			acb->firm_model);
पूर्ण

अटल sमाप_प्रकार
arcmsr_attr_host_fw_version(काष्ठा device *dev,
			    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा Scsi_Host *host = class_to_shost(dev);
	काष्ठा AdapterControlBlock *acb =
			(काष्ठा AdapterControlBlock *) host->hostdata;

	वापस snम_लिखो(buf, PAGE_SIZE,
			"%s\n",
			acb->firm_version);
पूर्ण

अटल sमाप_प्रकार
arcmsr_attr_host_fw_request_len(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा Scsi_Host *host = class_to_shost(dev);
	काष्ठा AdapterControlBlock *acb =
		(काष्ठा AdapterControlBlock *) host->hostdata;

	वापस snम_लिखो(buf, PAGE_SIZE,
			"%4d\n",
			acb->firm_request_len);
पूर्ण

अटल sमाप_प्रकार
arcmsr_attr_host_fw_numbers_queue(काष्ठा device *dev,
				  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा Scsi_Host *host = class_to_shost(dev);
	काष्ठा AdapterControlBlock *acb =
		(काष्ठा AdapterControlBlock *) host->hostdata;

	वापस snम_लिखो(buf, PAGE_SIZE,
			"%4d\n",
			acb->firm_numbers_queue);
पूर्ण

अटल sमाप_प्रकार
arcmsr_attr_host_fw_sdram_size(काष्ठा device *dev,
			       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा Scsi_Host *host = class_to_shost(dev);
	काष्ठा AdapterControlBlock *acb =
		(काष्ठा AdapterControlBlock *) host->hostdata;

	वापस snम_लिखो(buf, PAGE_SIZE,
			"%4d\n",
			acb->firm_sdram_size);
पूर्ण

अटल sमाप_प्रकार
arcmsr_attr_host_fw_hd_channels(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा Scsi_Host *host = class_to_shost(dev);
	काष्ठा AdapterControlBlock *acb =
		(काष्ठा AdapterControlBlock *) host->hostdata;

	वापस snम_लिखो(buf, PAGE_SIZE,
			"%4d\n",
			acb->firm_hd_channels);
पूर्ण

अटल DEVICE_ATTR(host_driver_version, S_IRUGO, arcmsr_attr_host_driver_version, शून्य);
अटल DEVICE_ATTR(host_driver_posted_cmd, S_IRUGO, arcmsr_attr_host_driver_posted_cmd, शून्य);
अटल DEVICE_ATTR(host_driver_reset, S_IRUGO, arcmsr_attr_host_driver_reset, शून्य);
अटल DEVICE_ATTR(host_driver_पात, S_IRUGO, arcmsr_attr_host_driver_पात, शून्य);
अटल DEVICE_ATTR(host_fw_model, S_IRUGO, arcmsr_attr_host_fw_model, शून्य);
अटल DEVICE_ATTR(host_fw_version, S_IRUGO, arcmsr_attr_host_fw_version, शून्य);
अटल DEVICE_ATTR(host_fw_request_len, S_IRUGO, arcmsr_attr_host_fw_request_len, शून्य);
अटल DEVICE_ATTR(host_fw_numbers_queue, S_IRUGO, arcmsr_attr_host_fw_numbers_queue, शून्य);
अटल DEVICE_ATTR(host_fw_sdram_size, S_IRUGO, arcmsr_attr_host_fw_sdram_size, शून्य);
अटल DEVICE_ATTR(host_fw_hd_channels, S_IRUGO, arcmsr_attr_host_fw_hd_channels, शून्य);

काष्ठा device_attribute *arcmsr_host_attrs[] = अणु
	&dev_attr_host_driver_version,
	&dev_attr_host_driver_posted_cmd,
	&dev_attr_host_driver_reset,
	&dev_attr_host_driver_पात,
	&dev_attr_host_fw_model,
	&dev_attr_host_fw_version,
	&dev_attr_host_fw_request_len,
	&dev_attr_host_fw_numbers_queue,
	&dev_attr_host_fw_sdram_size,
	&dev_attr_host_fw_hd_channels,
	शून्य,
पूर्ण;
