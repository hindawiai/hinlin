<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * SCSI Enclosure Services
 *
 * Copyright (C) 2008 James Bottomley <James.Bottomley@HansenPartnership.com>
 */

#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/enclosure.h>
#समावेश <यंत्र/unaligned.h>

#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_cmnd.h>
#समावेश <scsi/scsi_dbg.h>
#समावेश <scsi/scsi_device.h>
#समावेश <scsi/scsi_driver.h>
#समावेश <scsi/scsi_host.h>

#समावेश <scsi/scsi_transport_sas.h>

काष्ठा ses_device अणु
	अचिन्हित अक्षर *page1;
	अचिन्हित अक्षर *page1_types;
	अचिन्हित अक्षर *page2;
	अचिन्हित अक्षर *page10;
	लघु page1_len;
	लघु page1_num_types;
	लघु page2_len;
	लघु page10_len;
पूर्ण;

काष्ठा ses_component अणु
	u64 addr;
पूर्ण;

अटल bool ses_page2_supported(काष्ठा enclosure_device *edev)
अणु
	काष्ठा ses_device *ses_dev = edev->scratch;

	वापस (ses_dev->page2 != शून्य);
पूर्ण

अटल पूर्णांक ses_probe(काष्ठा device *dev)
अणु
	काष्ठा scsi_device *sdev = to_scsi_device(dev);
	पूर्णांक err = -ENODEV;

	अगर (sdev->type != TYPE_ENCLOSURE)
		जाओ out;

	err = 0;
	sdev_prपूर्णांकk(KERN_NOTICE, sdev, "Attached Enclosure device\n");

 out:
	वापस err;
पूर्ण

#घोषणा SES_TIMEOUT (30 * HZ)
#घोषणा SES_RETRIES 3

अटल व्योम init_device_slot_control(अचिन्हित अक्षर *dest_desc,
				     काष्ठा enclosure_component *ecomp,
				     अचिन्हित अक्षर *status)
अणु
	स_नकल(dest_desc, status, 4);
	dest_desc[0] = 0;
	/* only clear byte 1 क्रम ENCLOSURE_COMPONENT_DEVICE */
	अगर (ecomp->type == ENCLOSURE_COMPONENT_DEVICE)
		dest_desc[1] = 0;
	dest_desc[2] &= 0xde;
	dest_desc[3] &= 0x3c;
पूर्ण


अटल पूर्णांक ses_recv_diag(काष्ठा scsi_device *sdev, पूर्णांक page_code,
			 व्योम *buf, पूर्णांक bufflen)
अणु
	पूर्णांक ret;
	अचिन्हित अक्षर cmd[] = अणु
		RECEIVE_DIAGNOSTIC,
		1,		/* Set PCV bit */
		page_code,
		bufflen >> 8,
		bufflen & 0xff,
		0
	पूर्ण;
	अचिन्हित अक्षर recv_page_code;

	ret =  scsi_execute_req(sdev, cmd, DMA_FROM_DEVICE, buf, bufflen,
				शून्य, SES_TIMEOUT, SES_RETRIES, शून्य);
	अगर (unlikely(ret))
		वापस ret;

	recv_page_code = ((अचिन्हित अक्षर *)buf)[0];

	अगर (likely(recv_page_code == page_code))
		वापस ret;

	/* successful diagnostic but wrong page code.  This happens to some
	 * USB devices, just prपूर्णांक a message and pretend there was an error */

	sdev_prपूर्णांकk(KERN_ERR, sdev,
		    "Wrong diagnostic page; asked for %d got %u\n",
		    page_code, recv_page_code);

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक ses_send_diag(काष्ठा scsi_device *sdev, पूर्णांक page_code,
			 व्योम *buf, पूर्णांक bufflen)
अणु
	u32 result;

	अचिन्हित अक्षर cmd[] = अणु
		SEND_DIAGNOSTIC,
		0x10,		/* Set PF bit */
		0,
		bufflen >> 8,
		bufflen & 0xff,
		0
	पूर्ण;

	result = scsi_execute_req(sdev, cmd, DMA_TO_DEVICE, buf, bufflen,
				  शून्य, SES_TIMEOUT, SES_RETRIES, शून्य);
	अगर (result)
		sdev_prपूर्णांकk(KERN_ERR, sdev, "SEND DIAGNOSTIC result: %8x\n",
			    result);
	वापस result;
पूर्ण

अटल पूर्णांक ses_set_page2_descriptor(काष्ठा enclosure_device *edev,
				      काष्ठा enclosure_component *ecomp,
				      अचिन्हित अक्षर *desc)
अणु
	पूर्णांक i, j, count = 0, descriptor = ecomp->number;
	काष्ठा scsi_device *sdev = to_scsi_device(edev->edev.parent);
	काष्ठा ses_device *ses_dev = edev->scratch;
	अचिन्हित अक्षर *type_ptr = ses_dev->page1_types;
	अचिन्हित अक्षर *desc_ptr = ses_dev->page2 + 8;

	/* Clear everything */
	स_रखो(desc_ptr, 0, ses_dev->page2_len - 8);
	क्रम (i = 0; i < ses_dev->page1_num_types; i++, type_ptr += 4) अणु
		क्रम (j = 0; j < type_ptr[1]; j++) अणु
			desc_ptr += 4;
			अगर (type_ptr[0] != ENCLOSURE_COMPONENT_DEVICE &&
			    type_ptr[0] != ENCLOSURE_COMPONENT_ARRAY_DEVICE)
				जारी;
			अगर (count++ == descriptor) अणु
				स_नकल(desc_ptr, desc, 4);
				/* set select */
				desc_ptr[0] |= 0x80;
				/* clear reserved, just in हाल */
				desc_ptr[0] &= 0xf0;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस ses_send_diag(sdev, 2, ses_dev->page2, ses_dev->page2_len);
पूर्ण

अटल अचिन्हित अक्षर *ses_get_page2_descriptor(काष्ठा enclosure_device *edev,
				      काष्ठा enclosure_component *ecomp)
अणु
	पूर्णांक i, j, count = 0, descriptor = ecomp->number;
	काष्ठा scsi_device *sdev = to_scsi_device(edev->edev.parent);
	काष्ठा ses_device *ses_dev = edev->scratch;
	अचिन्हित अक्षर *type_ptr = ses_dev->page1_types;
	अचिन्हित अक्षर *desc_ptr = ses_dev->page2 + 8;

	अगर (ses_recv_diag(sdev, 2, ses_dev->page2, ses_dev->page2_len) < 0)
		वापस शून्य;

	क्रम (i = 0; i < ses_dev->page1_num_types; i++, type_ptr += 4) अणु
		क्रम (j = 0; j < type_ptr[1]; j++) अणु
			desc_ptr += 4;
			अगर (type_ptr[0] != ENCLOSURE_COMPONENT_DEVICE &&
			    type_ptr[0] != ENCLOSURE_COMPONENT_ARRAY_DEVICE)
				जारी;
			अगर (count++ == descriptor)
				वापस desc_ptr;
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण

/* For device slot and array device slot elements, byte 3 bit 6
 * is "fault sensed" जबतक byte 3 bit 5 is "fault reqstd". As this
 * code stands these bits are shअगरted 4 positions right so in
 * sysfs they will appear as bits 2 and 1 respectively. Strange. */
अटल व्योम ses_get_fault(काष्ठा enclosure_device *edev,
			  काष्ठा enclosure_component *ecomp)
अणु
	अचिन्हित अक्षर *desc;

	अगर (!ses_page2_supported(edev)) अणु
		ecomp->fault = 0;
		वापस;
	पूर्ण
	desc = ses_get_page2_descriptor(edev, ecomp);
	अगर (desc)
		ecomp->fault = (desc[3] & 0x60) >> 4;
पूर्ण

अटल पूर्णांक ses_set_fault(काष्ठा enclosure_device *edev,
			  काष्ठा enclosure_component *ecomp,
			 क्रमागत enclosure_component_setting val)
अणु
	अचिन्हित अक्षर desc[4];
	अचिन्हित अक्षर *desc_ptr;

	अगर (!ses_page2_supported(edev))
		वापस -EINVAL;

	desc_ptr = ses_get_page2_descriptor(edev, ecomp);

	अगर (!desc_ptr)
		वापस -EIO;

	init_device_slot_control(desc, ecomp, desc_ptr);

	चयन (val) अणु
	हाल ENCLOSURE_SETTING_DISABLED:
		desc[3] &= 0xdf;
		अवरोध;
	हाल ENCLOSURE_SETTING_ENABLED:
		desc[3] |= 0x20;
		अवरोध;
	शेष:
		/* SES करोesn't करो the SGPIO blink settings */
		वापस -EINVAL;
	पूर्ण

	वापस ses_set_page2_descriptor(edev, ecomp, desc);
पूर्ण

अटल व्योम ses_get_status(काष्ठा enclosure_device *edev,
			   काष्ठा enclosure_component *ecomp)
अणु
	अचिन्हित अक्षर *desc;

	अगर (!ses_page2_supported(edev)) अणु
		ecomp->status = 0;
		वापस;
	पूर्ण
	desc = ses_get_page2_descriptor(edev, ecomp);
	अगर (desc)
		ecomp->status = (desc[0] & 0x0f);
पूर्ण

अटल व्योम ses_get_locate(काष्ठा enclosure_device *edev,
			   काष्ठा enclosure_component *ecomp)
अणु
	अचिन्हित अक्षर *desc;

	अगर (!ses_page2_supported(edev)) अणु
		ecomp->locate = 0;
		वापस;
	पूर्ण
	desc = ses_get_page2_descriptor(edev, ecomp);
	अगर (desc)
		ecomp->locate = (desc[2] & 0x02) ? 1 : 0;
पूर्ण

अटल पूर्णांक ses_set_locate(काष्ठा enclosure_device *edev,
			  काष्ठा enclosure_component *ecomp,
			  क्रमागत enclosure_component_setting val)
अणु
	अचिन्हित अक्षर desc[4];
	अचिन्हित अक्षर *desc_ptr;

	अगर (!ses_page2_supported(edev))
		वापस -EINVAL;

	desc_ptr = ses_get_page2_descriptor(edev, ecomp);

	अगर (!desc_ptr)
		वापस -EIO;

	init_device_slot_control(desc, ecomp, desc_ptr);

	चयन (val) अणु
	हाल ENCLOSURE_SETTING_DISABLED:
		desc[2] &= 0xfd;
		अवरोध;
	हाल ENCLOSURE_SETTING_ENABLED:
		desc[2] |= 0x02;
		अवरोध;
	शेष:
		/* SES करोesn't करो the SGPIO blink settings */
		वापस -EINVAL;
	पूर्ण
	वापस ses_set_page2_descriptor(edev, ecomp, desc);
पूर्ण

अटल पूर्णांक ses_set_active(काष्ठा enclosure_device *edev,
			  काष्ठा enclosure_component *ecomp,
			  क्रमागत enclosure_component_setting val)
अणु
	अचिन्हित अक्षर desc[4];
	अचिन्हित अक्षर *desc_ptr;

	अगर (!ses_page2_supported(edev))
		वापस -EINVAL;

	desc_ptr = ses_get_page2_descriptor(edev, ecomp);

	अगर (!desc_ptr)
		वापस -EIO;

	init_device_slot_control(desc, ecomp, desc_ptr);

	चयन (val) अणु
	हाल ENCLOSURE_SETTING_DISABLED:
		desc[2] &= 0x7f;
		ecomp->active = 0;
		अवरोध;
	हाल ENCLOSURE_SETTING_ENABLED:
		desc[2] |= 0x80;
		ecomp->active = 1;
		अवरोध;
	शेष:
		/* SES करोesn't करो the SGPIO blink settings */
		वापस -EINVAL;
	पूर्ण
	वापस ses_set_page2_descriptor(edev, ecomp, desc);
पूर्ण

अटल पूर्णांक ses_show_id(काष्ठा enclosure_device *edev, अक्षर *buf)
अणु
	काष्ठा ses_device *ses_dev = edev->scratch;
	अचिन्हित दीर्घ दीर्घ id = get_unaligned_be64(ses_dev->page1+8+4);

	वापस प्र_लिखो(buf, "%#llx\n", id);
पूर्ण

अटल व्योम ses_get_घातer_status(काष्ठा enclosure_device *edev,
				 काष्ठा enclosure_component *ecomp)
अणु
	अचिन्हित अक्षर *desc;

	अगर (!ses_page2_supported(edev)) अणु
		ecomp->घातer_status = 0;
		वापस;
	पूर्ण

	desc = ses_get_page2_descriptor(edev, ecomp);
	अगर (desc)
		ecomp->घातer_status = (desc[3] & 0x10) ? 0 : 1;
पूर्ण

अटल पूर्णांक ses_set_घातer_status(काष्ठा enclosure_device *edev,
				काष्ठा enclosure_component *ecomp,
				पूर्णांक val)
अणु
	अचिन्हित अक्षर desc[4];
	अचिन्हित अक्षर *desc_ptr;

	अगर (!ses_page2_supported(edev))
		वापस -EINVAL;

	desc_ptr = ses_get_page2_descriptor(edev, ecomp);

	अगर (!desc_ptr)
		वापस -EIO;

	init_device_slot_control(desc, ecomp, desc_ptr);

	चयन (val) अणु
	/* घातer = 1 is device_off = 0 and vice versa */
	हाल 0:
		desc[3] |= 0x10;
		अवरोध;
	हाल 1:
		desc[3] &= 0xef;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	ecomp->घातer_status = val;
	वापस ses_set_page2_descriptor(edev, ecomp, desc);
पूर्ण

अटल काष्ठा enclosure_component_callbacks ses_enclosure_callbacks = अणु
	.get_fault		= ses_get_fault,
	.set_fault		= ses_set_fault,
	.get_status		= ses_get_status,
	.get_locate		= ses_get_locate,
	.set_locate		= ses_set_locate,
	.get_घातer_status	= ses_get_घातer_status,
	.set_घातer_status	= ses_set_घातer_status,
	.set_active		= ses_set_active,
	.show_id		= ses_show_id,
पूर्ण;

काष्ठा ses_host_edev अणु
	काष्ठा Scsi_Host *shost;
	काष्ठा enclosure_device *edev;
पूर्ण;

#अगर 0
पूर्णांक ses_match_host(काष्ठा enclosure_device *edev, व्योम *data)
अणु
	काष्ठा ses_host_edev *sed = data;
	काष्ठा scsi_device *sdev;

	अगर (!scsi_is_sdev_device(edev->edev.parent))
		वापस 0;

	sdev = to_scsi_device(edev->edev.parent);

	अगर (sdev->host != sed->shost)
		वापस 0;

	sed->edev = edev;
	वापस 1;
पूर्ण
#पूर्ण_अगर  /*  0  */

अटल व्योम ses_process_descriptor(काष्ठा enclosure_component *ecomp,
				   अचिन्हित अक्षर *desc)
अणु
	पूर्णांक eip = desc[0] & 0x10;
	पूर्णांक invalid = desc[0] & 0x80;
	क्रमागत scsi_protocol proto = desc[0] & 0x0f;
	u64 addr = 0;
	पूर्णांक slot = -1;
	काष्ठा ses_component *scomp = ecomp->scratch;
	अचिन्हित अक्षर *d;

	अगर (invalid)
		वापस;

	चयन (proto) अणु
	हाल SCSI_PROTOCOL_FCP:
		अगर (eip) अणु
			d = desc + 4;
			slot = d[3];
		पूर्ण
		अवरोध;
	हाल SCSI_PROTOCOL_SAS:
		अगर (eip) अणु
			d = desc + 4;
			slot = d[3];
			d = desc + 8;
		पूर्ण अन्यथा
			d = desc + 4;
		/* only take the phy0 addr */
		addr = (u64)d[12] << 56 |
			(u64)d[13] << 48 |
			(u64)d[14] << 40 |
			(u64)d[15] << 32 |
			(u64)d[16] << 24 |
			(u64)d[17] << 16 |
			(u64)d[18] << 8 |
			(u64)d[19];
		अवरोध;
	शेष:
		/* FIXME: Need to add more protocols than just SAS */
		अवरोध;
	पूर्ण
	ecomp->slot = slot;
	scomp->addr = addr;
पूर्ण

काष्ठा efd अणु
	u64 addr;
	काष्ठा device *dev;
पूर्ण;

अटल पूर्णांक ses_enclosure_find_by_addr(काष्ठा enclosure_device *edev,
				      व्योम *data)
अणु
	काष्ठा efd *efd = data;
	पूर्णांक i;
	काष्ठा ses_component *scomp;

	अगर (!edev->component[0].scratch)
		वापस 0;

	क्रम (i = 0; i < edev->components; i++) अणु
		scomp = edev->component[i].scratch;
		अगर (scomp->addr != efd->addr)
			जारी;

		अगर (enclosure_add_device(edev, i, efd->dev) == 0)
			kobject_uevent(&efd->dev->kobj, KOBJ_CHANGE);
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

#घोषणा INIT_ALLOC_SIZE 32

अटल व्योम ses_enclosure_data_process(काष्ठा enclosure_device *edev,
				       काष्ठा scsi_device *sdev,
				       पूर्णांक create)
अणु
	u32 result;
	अचिन्हित अक्षर *buf = शून्य, *type_ptr, *desc_ptr, *addl_desc_ptr = शून्य;
	पूर्णांक i, j, page7_len, len, components;
	काष्ठा ses_device *ses_dev = edev->scratch;
	पूर्णांक types = ses_dev->page1_num_types;
	अचिन्हित अक्षर *hdr_buf = kzalloc(INIT_ALLOC_SIZE, GFP_KERNEL);

	अगर (!hdr_buf)
		जाओ simple_populate;

	/* re-पढ़ो page 10 */
	अगर (ses_dev->page10)
		ses_recv_diag(sdev, 10, ses_dev->page10, ses_dev->page10_len);
	/* Page 7 क्रम the descriptors is optional */
	result = ses_recv_diag(sdev, 7, hdr_buf, INIT_ALLOC_SIZE);
	अगर (result)
		जाओ simple_populate;

	page7_len = len = (hdr_buf[2] << 8) + hdr_buf[3] + 4;
	/* add 1 क्रम trailing '\0' we'll use */
	buf = kzalloc(len + 1, GFP_KERNEL);
	अगर (!buf)
		जाओ simple_populate;
	result = ses_recv_diag(sdev, 7, buf, len);
	अगर (result) अणु
 simple_populate:
		kमुक्त(buf);
		buf = शून्य;
		desc_ptr = शून्य;
		len = 0;
		page7_len = 0;
	पूर्ण अन्यथा अणु
		desc_ptr = buf + 8;
		len = (desc_ptr[2] << 8) + desc_ptr[3];
		/* skip past overall descriptor */
		desc_ptr += len + 4;
	पूर्ण
	अगर (ses_dev->page10)
		addl_desc_ptr = ses_dev->page10 + 8;
	type_ptr = ses_dev->page1_types;
	components = 0;
	क्रम (i = 0; i < types; i++, type_ptr += 4) अणु
		क्रम (j = 0; j < type_ptr[1]; j++) अणु
			अक्षर *name = शून्य;
			काष्ठा enclosure_component *ecomp;

			अगर (desc_ptr) अणु
				अगर (desc_ptr >= buf + page7_len) अणु
					desc_ptr = शून्य;
				पूर्ण अन्यथा अणु
					len = (desc_ptr[2] << 8) + desc_ptr[3];
					desc_ptr += 4;
					/* Add trailing zero - pushes पूर्णांकo
					 * reserved space */
					desc_ptr[len] = '\0';
					name = desc_ptr;
				पूर्ण
			पूर्ण
			अगर (type_ptr[0] == ENCLOSURE_COMPONENT_DEVICE ||
			    type_ptr[0] == ENCLOSURE_COMPONENT_ARRAY_DEVICE) अणु

				अगर (create)
					ecomp =	enclosure_component_alloc(
						edev,
						components++,
						type_ptr[0],
						name);
				अन्यथा
					ecomp = &edev->component[components++];

				अगर (!IS_ERR(ecomp)) अणु
					अगर (addl_desc_ptr)
						ses_process_descriptor(
							ecomp,
							addl_desc_ptr);
					अगर (create)
						enclosure_component_रेजिस्टर(
							ecomp);
				पूर्ण
			पूर्ण
			अगर (desc_ptr)
				desc_ptr += len;

			अगर (addl_desc_ptr &&
			    /* only find additional descriptions क्रम specअगरic devices */
			    (type_ptr[0] == ENCLOSURE_COMPONENT_DEVICE ||
			     type_ptr[0] == ENCLOSURE_COMPONENT_ARRAY_DEVICE ||
			     type_ptr[0] == ENCLOSURE_COMPONENT_SAS_EXPANDER ||
			     /* these elements are optional */
			     type_ptr[0] == ENCLOSURE_COMPONENT_SCSI_TARGET_PORT ||
			     type_ptr[0] == ENCLOSURE_COMPONENT_SCSI_INITIATOR_PORT ||
			     type_ptr[0] == ENCLOSURE_COMPONENT_CONTROLLER_ELECTRONICS))
				addl_desc_ptr += addl_desc_ptr[1] + 2;

		पूर्ण
	पूर्ण
	kमुक्त(buf);
	kमुक्त(hdr_buf);
पूर्ण

अटल व्योम ses_match_to_enclosure(काष्ठा enclosure_device *edev,
				   काष्ठा scsi_device *sdev,
				   पूर्णांक refresh)
अणु
	काष्ठा scsi_device *edev_sdev = to_scsi_device(edev->edev.parent);
	काष्ठा efd efd = अणु
		.addr = 0,
	पूर्ण;

	अगर (refresh)
		ses_enclosure_data_process(edev, edev_sdev, 0);

	अगर (scsi_is_sas_rphy(sdev->sdev_target->dev.parent))
		efd.addr = sas_get_address(sdev);

	अगर (efd.addr) अणु
		efd.dev = &sdev->sdev_gendev;

		enclosure_क्रम_each_device(ses_enclosure_find_by_addr, &efd);
	पूर्ण
पूर्ण

अटल पूर्णांक ses_पूर्णांकf_add(काष्ठा device *cdev,
			काष्ठा class_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा scsi_device *sdev = to_scsi_device(cdev->parent);
	काष्ठा scsi_device *पंचांगp_sdev;
	अचिन्हित अक्षर *buf = शून्य, *hdr_buf, *type_ptr, page;
	काष्ठा ses_device *ses_dev;
	u32 result;
	पूर्णांक i, types, len, components = 0;
	पूर्णांक err = -ENOMEM;
	पूर्णांक num_enclosures;
	काष्ठा enclosure_device *edev;
	काष्ठा ses_component *scomp = शून्य;

	अगर (!scsi_device_enclosure(sdev)) अणु
		/* not an enclosure, but might be in one */
		काष्ठा enclosure_device *prev = शून्य;

		जबतक ((edev = enclosure_find(&sdev->host->shost_gendev, prev)) != शून्य) अणु
			ses_match_to_enclosure(edev, sdev, 1);
			prev = edev;
		पूर्ण
		वापस -ENODEV;
	पूर्ण

	/* TYPE_ENCLOSURE prपूर्णांकs a message in probe */
	अगर (sdev->type != TYPE_ENCLOSURE)
		sdev_prपूर्णांकk(KERN_NOTICE, sdev, "Embedded Enclosure Device\n");

	ses_dev = kzalloc(माप(*ses_dev), GFP_KERNEL);
	hdr_buf = kzalloc(INIT_ALLOC_SIZE, GFP_KERNEL);
	अगर (!hdr_buf || !ses_dev)
		जाओ err_init_मुक्त;

	page = 1;
	result = ses_recv_diag(sdev, page, hdr_buf, INIT_ALLOC_SIZE);
	अगर (result)
		जाओ recv_failed;

	len = (hdr_buf[2] << 8) + hdr_buf[3] + 4;
	buf = kzalloc(len, GFP_KERNEL);
	अगर (!buf)
		जाओ err_मुक्त;

	result = ses_recv_diag(sdev, page, buf, len);
	अगर (result)
		जाओ recv_failed;

	types = 0;

	/* we always have one मुख्य enclosure and the rest are referred
	 * to as secondary subenclosures */
	num_enclosures = buf[1] + 1;

	/* begin at the enclosure descriptor */
	type_ptr = buf + 8;
	/* skip all the enclosure descriptors */
	क्रम (i = 0; i < num_enclosures && type_ptr < buf + len; i++) अणु
		types += type_ptr[2];
		type_ptr += type_ptr[3] + 4;
	पूर्ण

	ses_dev->page1_types = type_ptr;
	ses_dev->page1_num_types = types;

	क्रम (i = 0; i < types && type_ptr < buf + len; i++, type_ptr += 4) अणु
		अगर (type_ptr[0] == ENCLOSURE_COMPONENT_DEVICE ||
		    type_ptr[0] == ENCLOSURE_COMPONENT_ARRAY_DEVICE)
			components += type_ptr[1];
	पूर्ण
	ses_dev->page1 = buf;
	ses_dev->page1_len = len;
	buf = शून्य;

	page = 2;
	result = ses_recv_diag(sdev, page, hdr_buf, INIT_ALLOC_SIZE);
	अगर (result)
		जाओ page2_not_supported;

	len = (hdr_buf[2] << 8) + hdr_buf[3] + 4;
	buf = kzalloc(len, GFP_KERNEL);
	अगर (!buf)
		जाओ err_मुक्त;

	/* make sure getting page 2 actually works */
	result = ses_recv_diag(sdev, 2, buf, len);
	अगर (result)
		जाओ recv_failed;
	ses_dev->page2 = buf;
	ses_dev->page2_len = len;
	buf = शून्य;

	/* The additional inक्रमmation page --- allows us
	 * to match up the devices */
	page = 10;
	result = ses_recv_diag(sdev, page, hdr_buf, INIT_ALLOC_SIZE);
	अगर (!result) अणु

		len = (hdr_buf[2] << 8) + hdr_buf[3] + 4;
		buf = kzalloc(len, GFP_KERNEL);
		अगर (!buf)
			जाओ err_मुक्त;

		result = ses_recv_diag(sdev, page, buf, len);
		अगर (result)
			जाओ recv_failed;
		ses_dev->page10 = buf;
		ses_dev->page10_len = len;
		buf = शून्य;
	पूर्ण
page2_not_supported:
	scomp = kसुस्मृति(components, माप(काष्ठा ses_component), GFP_KERNEL);
	अगर (!scomp)
		जाओ err_मुक्त;

	edev = enclosure_रेजिस्टर(cdev->parent, dev_name(&sdev->sdev_gendev),
				  components, &ses_enclosure_callbacks);
	अगर (IS_ERR(edev)) अणु
		err = PTR_ERR(edev);
		जाओ err_मुक्त;
	पूर्ण

	kमुक्त(hdr_buf);

	edev->scratch = ses_dev;
	क्रम (i = 0; i < components; i++)
		edev->component[i].scratch = scomp + i;

	ses_enclosure_data_process(edev, sdev, 1);

	/* see अगर there are any devices matching beक्रमe
	 * we found the enclosure */
	shost_क्रम_each_device(पंचांगp_sdev, sdev->host) अणु
		अगर (पंचांगp_sdev->lun != 0 || scsi_device_enclosure(पंचांगp_sdev))
			जारी;
		ses_match_to_enclosure(edev, पंचांगp_sdev, 0);
	पूर्ण

	वापस 0;

 recv_failed:
	sdev_prपूर्णांकk(KERN_ERR, sdev, "Failed to get diagnostic page 0x%x\n",
		    page);
	err = -ENODEV;
 err_मुक्त:
	kमुक्त(buf);
	kमुक्त(scomp);
	kमुक्त(ses_dev->page10);
	kमुक्त(ses_dev->page2);
	kमुक्त(ses_dev->page1);
 err_init_मुक्त:
	kमुक्त(ses_dev);
	kमुक्त(hdr_buf);
	sdev_prपूर्णांकk(KERN_ERR, sdev, "Failed to bind enclosure %d\n", err);
	वापस err;
पूर्ण

अटल पूर्णांक ses_हटाओ(काष्ठा device *dev)
अणु
	वापस 0;
पूर्ण

अटल व्योम ses_पूर्णांकf_हटाओ_component(काष्ठा scsi_device *sdev)
अणु
	काष्ठा enclosure_device *edev, *prev = शून्य;

	जबतक ((edev = enclosure_find(&sdev->host->shost_gendev, prev)) != शून्य) अणु
		prev = edev;
		अगर (!enclosure_हटाओ_device(edev, &sdev->sdev_gendev))
			अवरोध;
	पूर्ण
	अगर (edev)
		put_device(&edev->edev);
पूर्ण

अटल व्योम ses_पूर्णांकf_हटाओ_enclosure(काष्ठा scsi_device *sdev)
अणु
	काष्ठा enclosure_device *edev;
	काष्ठा ses_device *ses_dev;

	/*  exact match to this enclosure */
	edev = enclosure_find(&sdev->sdev_gendev, शून्य);
	अगर (!edev)
		वापस;

	ses_dev = edev->scratch;
	edev->scratch = शून्य;

	kमुक्त(ses_dev->page10);
	kमुक्त(ses_dev->page1);
	kमुक्त(ses_dev->page2);
	kमुक्त(ses_dev);

	kमुक्त(edev->component[0].scratch);

	put_device(&edev->edev);
	enclosure_unरेजिस्टर(edev);
पूर्ण

अटल व्योम ses_पूर्णांकf_हटाओ(काष्ठा device *cdev,
			    काष्ठा class_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा scsi_device *sdev = to_scsi_device(cdev->parent);

	अगर (!scsi_device_enclosure(sdev))
		ses_पूर्णांकf_हटाओ_component(sdev);
	अन्यथा
		ses_पूर्णांकf_हटाओ_enclosure(sdev);
पूर्ण

अटल काष्ठा class_पूर्णांकerface ses_पूर्णांकerface = अणु
	.add_dev	= ses_पूर्णांकf_add,
	.हटाओ_dev	= ses_पूर्णांकf_हटाओ,
पूर्ण;

अटल काष्ठा scsi_driver ses_ढाँचा = अणु
	.gendrv = अणु
		.name		= "ses",
		.owner		= THIS_MODULE,
		.probe		= ses_probe,
		.हटाओ		= ses_हटाओ,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init ses_init(व्योम)
अणु
	पूर्णांक err;

	err = scsi_रेजिस्टर_पूर्णांकerface(&ses_पूर्णांकerface);
	अगर (err)
		वापस err;

	err = scsi_रेजिस्टर_driver(&ses_ढाँचा.gendrv);
	अगर (err)
		जाओ out_unreg;

	वापस 0;

 out_unreg:
	scsi_unरेजिस्टर_पूर्णांकerface(&ses_पूर्णांकerface);
	वापस err;
पूर्ण

अटल व्योम __निकास ses_निकास(व्योम)
अणु
	scsi_unरेजिस्टर_driver(&ses_ढाँचा.gendrv);
	scsi_unरेजिस्टर_पूर्णांकerface(&ses_पूर्णांकerface);
पूर्ण

module_init(ses_init);
module_निकास(ses_निकास);

MODULE_ALIAS_SCSI_DEVICE(TYPE_ENCLOSURE);

MODULE_AUTHOR("James Bottomley");
MODULE_DESCRIPTION("SCSI Enclosure Services (ses) driver");
MODULE_LICENSE("GPL v2");
