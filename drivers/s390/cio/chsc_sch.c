<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Driver क्रम s390 chsc subchannels
 *
 * Copyright IBM Corp. 2008, 2011
 *
 * Author(s): Cornelia Huck <cornelia.huck@de.ibm.com>
 *
 */

#समावेश <linux/slab.h>
#समावेश <linux/compat.h>
#समावेश <linux/device.h>
#समावेश <linux/module.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/kernel_स्थिति.स>

#समावेश <यंत्र/cपन.स>
#समावेश <यंत्र/chsc.h>
#समावेश <यंत्र/isc.h>

#समावेश "cio.h"
#समावेश "cio_debug.h"
#समावेश "css.h"
#समावेश "chsc_sch.h"
#समावेश "ioasm.h"

अटल debug_info_t *chsc_debug_msg_id;
अटल debug_info_t *chsc_debug_log_id;

अटल काष्ठा chsc_request *on_बंद_request;
अटल काष्ठा chsc_async_area *on_बंद_chsc_area;
अटल DEFINE_MUTEX(on_बंद_mutex);

#घोषणा CHSC_MSG(imp, args...) करो अणु					\
		debug_प्र_लिखो_event(chsc_debug_msg_id, imp , ##args);	\
	पूर्ण जबतक (0)

#घोषणा CHSC_LOG(imp, txt) करो अणु					\
		debug_text_event(chsc_debug_log_id, imp , txt);	\
	पूर्ण जबतक (0)

अटल व्योम CHSC_LOG_HEX(पूर्णांक level, व्योम *data, पूर्णांक length)
अणु
	debug_event(chsc_debug_log_id, level, data, length);
पूर्ण

MODULE_AUTHOR("IBM Corporation");
MODULE_DESCRIPTION("driver for s390 chsc subchannels");
MODULE_LICENSE("GPL");

अटल व्योम chsc_subchannel_irq(काष्ठा subchannel *sch)
अणु
	काष्ठा chsc_निजी *निजी = dev_get_drvdata(&sch->dev);
	काष्ठा chsc_request *request = निजी->request;
	काष्ठा irb *irb = this_cpu_ptr(&cio_irb);

	CHSC_LOG(4, "irb");
	CHSC_LOG_HEX(4, irb, माप(*irb));
	inc_irq_stat(IRQIO_CSC);

	/* Copy irb to provided request and set करोne. */
	अगर (!request) अणु
		CHSC_MSG(0, "Interrupt on sch 0.%x.%04x with no request\n",
			 sch->schid.ssid, sch->schid.sch_no);
		वापस;
	पूर्ण
	निजी->request = शून्य;
	स_नकल(&request->irb, irb, माप(*irb));
	cio_update_schib(sch);
	complete(&request->completion);
	put_device(&sch->dev);
पूर्ण

अटल पूर्णांक chsc_subchannel_probe(काष्ठा subchannel *sch)
अणु
	काष्ठा chsc_निजी *निजी;
	पूर्णांक ret;

	CHSC_MSG(6, "Detected chsc subchannel 0.%x.%04x\n",
		 sch->schid.ssid, sch->schid.sch_no);
	sch->isc = CHSC_SCH_ISC;
	निजी = kzalloc(माप(*निजी), GFP_KERNEL);
	अगर (!निजी)
		वापस -ENOMEM;
	dev_set_drvdata(&sch->dev, निजी);
	ret = cio_enable_subchannel(sch, (u32)(अचिन्हित दीर्घ)sch);
	अगर (ret) अणु
		CHSC_MSG(0, "Failed to enable 0.%x.%04x: %d\n",
			 sch->schid.ssid, sch->schid.sch_no, ret);
		dev_set_drvdata(&sch->dev, शून्य);
		kमुक्त(निजी);
	पूर्ण अन्यथा अणु
		अगर (dev_get_uevent_suppress(&sch->dev)) अणु
			dev_set_uevent_suppress(&sch->dev, 0);
			kobject_uevent(&sch->dev.kobj, KOBJ_ADD);
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक chsc_subchannel_हटाओ(काष्ठा subchannel *sch)
अणु
	काष्ठा chsc_निजी *निजी;

	cio_disable_subchannel(sch);
	निजी = dev_get_drvdata(&sch->dev);
	dev_set_drvdata(&sch->dev, शून्य);
	अगर (निजी->request) अणु
		complete(&निजी->request->completion);
		put_device(&sch->dev);
	पूर्ण
	kमुक्त(निजी);
	वापस 0;
पूर्ण

अटल व्योम chsc_subchannel_shutकरोwn(काष्ठा subchannel *sch)
अणु
	cio_disable_subchannel(sch);
पूर्ण

अटल काष्ठा css_device_id chsc_subchannel_ids[] = अणु
	अणु .match_flags = 0x1, .type =SUBCHANNEL_TYPE_CHSC, पूर्ण,
	अणु /* end of list */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(css, chsc_subchannel_ids);

अटल काष्ठा css_driver chsc_subchannel_driver = अणु
	.drv = अणु
		.owner = THIS_MODULE,
		.name = "chsc_subchannel",
	पूर्ण,
	.subchannel_type = chsc_subchannel_ids,
	.irq = chsc_subchannel_irq,
	.probe = chsc_subchannel_probe,
	.हटाओ = chsc_subchannel_हटाओ,
	.shutकरोwn = chsc_subchannel_shutकरोwn,
पूर्ण;

अटल पूर्णांक __init chsc_init_dbfs(व्योम)
अणु
	chsc_debug_msg_id = debug_रेजिस्टर("chsc_msg", 8, 1, 4 * माप(दीर्घ));
	अगर (!chsc_debug_msg_id)
		जाओ out;
	debug_रेजिस्टर_view(chsc_debug_msg_id, &debug_प्र_लिखो_view);
	debug_set_level(chsc_debug_msg_id, 2);
	chsc_debug_log_id = debug_रेजिस्टर("chsc_log", 16, 1, 16);
	अगर (!chsc_debug_log_id)
		जाओ out;
	debug_रेजिस्टर_view(chsc_debug_log_id, &debug_hex_ascii_view);
	debug_set_level(chsc_debug_log_id, 2);
	वापस 0;
out:
	debug_unरेजिस्टर(chsc_debug_msg_id);
	वापस -ENOMEM;
पूर्ण

अटल व्योम chsc_हटाओ_dbfs(व्योम)
अणु
	debug_unरेजिस्टर(chsc_debug_log_id);
	debug_unरेजिस्टर(chsc_debug_msg_id);
पूर्ण

अटल पूर्णांक __init chsc_init_sch_driver(व्योम)
अणु
	वापस css_driver_रेजिस्टर(&chsc_subchannel_driver);
पूर्ण

अटल व्योम chsc_cleanup_sch_driver(व्योम)
अणु
	css_driver_unरेजिस्टर(&chsc_subchannel_driver);
पूर्ण

अटल DEFINE_SPINLOCK(chsc_lock);

अटल पूर्णांक chsc_subchannel_match_next_मुक्त(काष्ठा device *dev, स्थिर व्योम *data)
अणु
	काष्ठा subchannel *sch = to_subchannel(dev);

	वापस sch->schib.pmcw.ena && !scsw_fctl(&sch->schib.scsw);
पूर्ण

अटल काष्ठा subchannel *chsc_get_next_subchannel(काष्ठा subchannel *sch)
अणु
	काष्ठा device *dev;

	dev = driver_find_device(&chsc_subchannel_driver.drv,
				 sch ? &sch->dev : शून्य, शून्य,
				 chsc_subchannel_match_next_मुक्त);
	वापस dev ? to_subchannel(dev) : शून्य;
पूर्ण

/**
 * chsc_async() - try to start a chsc request asynchronously
 * @chsc_area: request to be started
 * @request: request काष्ठाure to associate
 *
 * Tries to start a chsc request on one of the existing chsc subchannels.
 * Returns:
 *  %0 अगर the request was perक्रमmed synchronously
 *  %-EINPROGRESS अगर the request was successfully started
 *  %-EBUSY अगर all chsc subchannels are busy
 *  %-ENODEV अगर no chsc subchannels are available
 * Context:
 *  पूर्णांकerrupts disabled, chsc_lock held
 */
अटल पूर्णांक chsc_async(काष्ठा chsc_async_area *chsc_area,
		      काष्ठा chsc_request *request)
अणु
	पूर्णांक cc;
	काष्ठा chsc_निजी *निजी;
	काष्ठा subchannel *sch = शून्य;
	पूर्णांक ret = -ENODEV;
	अक्षर dbf[10];

	chsc_area->header.key = PAGE_DEFAULT_KEY >> 4;
	जबतक ((sch = chsc_get_next_subchannel(sch))) अणु
		spin_lock(sch->lock);
		निजी = dev_get_drvdata(&sch->dev);
		अगर (निजी->request) अणु
			spin_unlock(sch->lock);
			ret = -EBUSY;
			जारी;
		पूर्ण
		chsc_area->header.sid = sch->schid;
		CHSC_LOG(2, "schid");
		CHSC_LOG_HEX(2, &sch->schid, माप(sch->schid));
		cc = chsc(chsc_area);
		snम_लिखो(dbf, माप(dbf), "cc:%d", cc);
		CHSC_LOG(2, dbf);
		चयन (cc) अणु
		हाल 0:
			ret = 0;
			अवरोध;
		हाल 1:
			sch->schib.scsw.cmd.fctl |= SCSW_FCTL_START_FUNC;
			ret = -EINPROGRESS;
			निजी->request = request;
			अवरोध;
		हाल 2:
			ret = -EBUSY;
			अवरोध;
		शेष:
			ret = -ENODEV;
		पूर्ण
		spin_unlock(sch->lock);
		CHSC_MSG(2, "chsc on 0.%x.%04x returned cc=%d\n",
			 sch->schid.ssid, sch->schid.sch_no, cc);
		अगर (ret == -EINPROGRESS)
			वापस -EINPROGRESS;
		put_device(&sch->dev);
		अगर (ret == 0)
			वापस 0;
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम chsc_log_command(व्योम *chsc_area)
अणु
	अक्षर dbf[10];

	snम_लिखो(dbf, माप(dbf), "CHSC:%x", ((uपूर्णांक16_t *)chsc_area)[1]);
	CHSC_LOG(0, dbf);
	CHSC_LOG_HEX(0, chsc_area, 32);
पूर्ण

अटल पूर्णांक chsc_examine_irb(काष्ठा chsc_request *request)
अणु
	पूर्णांक backed_up;

	अगर (!(scsw_stctl(&request->irb.scsw) & SCSW_STCTL_STATUS_PEND))
		वापस -EIO;
	backed_up = scsw_cstat(&request->irb.scsw) & SCHN_STAT_CHAIN_CHECK;
	request->irb.scsw.cmd.cstat &= ~SCHN_STAT_CHAIN_CHECK;
	अगर (scsw_cstat(&request->irb.scsw) == 0)
		वापस 0;
	अगर (!backed_up)
		वापस 0;
	अगर (scsw_cstat(&request->irb.scsw) & SCHN_STAT_PROG_CHECK)
		वापस -EIO;
	अगर (scsw_cstat(&request->irb.scsw) & SCHN_STAT_PROT_CHECK)
		वापस -EPERM;
	अगर (scsw_cstat(&request->irb.scsw) & SCHN_STAT_CHN_DATA_CHK)
		वापस -EAGAIN;
	अगर (scsw_cstat(&request->irb.scsw) & SCHN_STAT_CHN_CTRL_CHK)
		वापस -EAGAIN;
	वापस -EIO;
पूर्ण

अटल पूर्णांक chsc_ioctl_start(व्योम __user *user_area)
अणु
	काष्ठा chsc_request *request;
	काष्ठा chsc_async_area *chsc_area;
	पूर्णांक ret;
	अक्षर dbf[10];

	अगर (!css_general_अक्षरacteristics.dynio)
		/* It makes no sense to try. */
		वापस -EOPNOTSUPP;
	chsc_area = (व्योम *)get_zeroed_page(GFP_DMA | GFP_KERNEL);
	अगर (!chsc_area)
		वापस -ENOMEM;
	request = kzalloc(माप(*request), GFP_KERNEL);
	अगर (!request) अणु
		ret = -ENOMEM;
		जाओ out_मुक्त;
	पूर्ण
	init_completion(&request->completion);
	अगर (copy_from_user(chsc_area, user_area, PAGE_SIZE)) अणु
		ret = -EFAULT;
		जाओ out_मुक्त;
	पूर्ण
	chsc_log_command(chsc_area);
	spin_lock_irq(&chsc_lock);
	ret = chsc_async(chsc_area, request);
	spin_unlock_irq(&chsc_lock);
	अगर (ret == -EINPROGRESS) अणु
		रुको_क्रम_completion(&request->completion);
		ret = chsc_examine_irb(request);
	पूर्ण
	/* copy area back to user */
	अगर (!ret)
		अगर (copy_to_user(user_area, chsc_area, PAGE_SIZE))
			ret = -EFAULT;
out_मुक्त:
	snम_लिखो(dbf, माप(dbf), "ret:%d", ret);
	CHSC_LOG(0, dbf);
	kमुक्त(request);
	मुक्त_page((अचिन्हित दीर्घ)chsc_area);
	वापस ret;
पूर्ण

अटल पूर्णांक chsc_ioctl_on_बंद_set(व्योम __user *user_area)
अणु
	अक्षर dbf[13];
	पूर्णांक ret;

	mutex_lock(&on_बंद_mutex);
	अगर (on_बंद_chsc_area) अणु
		ret = -EBUSY;
		जाओ out_unlock;
	पूर्ण
	on_बंद_request = kzalloc(माप(*on_बंद_request), GFP_KERNEL);
	अगर (!on_बंद_request) अणु
		ret = -ENOMEM;
		जाओ out_unlock;
	पूर्ण
	on_बंद_chsc_area = (व्योम *)get_zeroed_page(GFP_DMA | GFP_KERNEL);
	अगर (!on_बंद_chsc_area) अणु
		ret = -ENOMEM;
		जाओ out_मुक्त_request;
	पूर्ण
	अगर (copy_from_user(on_बंद_chsc_area, user_area, PAGE_SIZE)) अणु
		ret = -EFAULT;
		जाओ out_मुक्त_chsc;
	पूर्ण
	ret = 0;
	जाओ out_unlock;

out_मुक्त_chsc:
	मुक्त_page((अचिन्हित दीर्घ)on_बंद_chsc_area);
	on_बंद_chsc_area = शून्य;
out_मुक्त_request:
	kमुक्त(on_बंद_request);
	on_बंद_request = शून्य;
out_unlock:
	mutex_unlock(&on_बंद_mutex);
	snम_लिखो(dbf, माप(dbf), "ocsret:%d", ret);
	CHSC_LOG(0, dbf);
	वापस ret;
पूर्ण

अटल पूर्णांक chsc_ioctl_on_बंद_हटाओ(व्योम)
अणु
	अक्षर dbf[13];
	पूर्णांक ret;

	mutex_lock(&on_बंद_mutex);
	अगर (!on_बंद_chsc_area) अणु
		ret = -ENOENT;
		जाओ out_unlock;
	पूर्ण
	मुक्त_page((अचिन्हित दीर्घ)on_बंद_chsc_area);
	on_बंद_chsc_area = शून्य;
	kमुक्त(on_बंद_request);
	on_बंद_request = शून्य;
	ret = 0;
out_unlock:
	mutex_unlock(&on_बंद_mutex);
	snम_लिखो(dbf, माप(dbf), "ocrret:%d", ret);
	CHSC_LOG(0, dbf);
	वापस ret;
पूर्ण

अटल पूर्णांक chsc_ioctl_start_sync(व्योम __user *user_area)
अणु
	काष्ठा chsc_sync_area *chsc_area;
	पूर्णांक ret, ccode;

	chsc_area = (व्योम *)get_zeroed_page(GFP_KERNEL | GFP_DMA);
	अगर (!chsc_area)
		वापस -ENOMEM;
	अगर (copy_from_user(chsc_area, user_area, PAGE_SIZE)) अणु
		ret = -EFAULT;
		जाओ out_मुक्त;
	पूर्ण
	अगर (chsc_area->header.code & 0x4000) अणु
		ret = -EINVAL;
		जाओ out_मुक्त;
	पूर्ण
	chsc_log_command(chsc_area);
	ccode = chsc(chsc_area);
	अगर (ccode != 0) अणु
		ret = -EIO;
		जाओ out_मुक्त;
	पूर्ण
	अगर (copy_to_user(user_area, chsc_area, PAGE_SIZE))
		ret = -EFAULT;
	अन्यथा
		ret = 0;
out_मुक्त:
	मुक्त_page((अचिन्हित दीर्घ)chsc_area);
	वापस ret;
पूर्ण

अटल पूर्णांक chsc_ioctl_info_channel_path(व्योम __user *user_cd)
अणु
	काष्ठा chsc_chp_cd *cd;
	पूर्णांक ret, ccode;
	काष्ठा अणु
		काष्ठा chsc_header request;
		u32 : 2;
		u32 m : 1;
		u32 : 1;
		u32 fmt1 : 4;
		u32 cssid : 8;
		u32 : 8;
		u32 first_chpid : 8;
		u32 : 24;
		u32 last_chpid : 8;
		u32 : 32;
		काष्ठा chsc_header response;
		u8 data[PAGE_SIZE - 20];
	पूर्ण __attribute__ ((packed)) *scpcd_area;

	scpcd_area = (व्योम *)get_zeroed_page(GFP_KERNEL | GFP_DMA);
	अगर (!scpcd_area)
		वापस -ENOMEM;
	cd = kzalloc(माप(*cd), GFP_KERNEL);
	अगर (!cd) अणु
		ret = -ENOMEM;
		जाओ out_मुक्त;
	पूर्ण
	अगर (copy_from_user(cd, user_cd, माप(*cd))) अणु
		ret = -EFAULT;
		जाओ out_मुक्त;
	पूर्ण
	scpcd_area->request.length = 0x0010;
	scpcd_area->request.code = 0x0028;
	scpcd_area->m = cd->m;
	scpcd_area->fmt1 = cd->fmt;
	scpcd_area->cssid = cd->chpid.cssid;
	scpcd_area->first_chpid = cd->chpid.id;
	scpcd_area->last_chpid = cd->chpid.id;

	ccode = chsc(scpcd_area);
	अगर (ccode != 0) अणु
		ret = -EIO;
		जाओ out_मुक्त;
	पूर्ण
	अगर (scpcd_area->response.code != 0x0001) अणु
		ret = -EIO;
		CHSC_MSG(0, "scpcd: response code=%x\n",
			 scpcd_area->response.code);
		जाओ out_मुक्त;
	पूर्ण
	स_नकल(&cd->cpcb, &scpcd_area->response, scpcd_area->response.length);
	अगर (copy_to_user(user_cd, cd, माप(*cd)))
		ret = -EFAULT;
	अन्यथा
		ret = 0;
out_मुक्त:
	kमुक्त(cd);
	मुक्त_page((अचिन्हित दीर्घ)scpcd_area);
	वापस ret;
पूर्ण

अटल पूर्णांक chsc_ioctl_info_cu(व्योम __user *user_cd)
अणु
	काष्ठा chsc_cu_cd *cd;
	पूर्णांक ret, ccode;
	काष्ठा अणु
		काष्ठा chsc_header request;
		u32 : 2;
		u32 m : 1;
		u32 : 1;
		u32 fmt1 : 4;
		u32 cssid : 8;
		u32 : 8;
		u32 first_cun : 8;
		u32 : 24;
		u32 last_cun : 8;
		u32 : 32;
		काष्ठा chsc_header response;
		u8 data[PAGE_SIZE - 20];
	पूर्ण __attribute__ ((packed)) *scucd_area;

	scucd_area = (व्योम *)get_zeroed_page(GFP_KERNEL | GFP_DMA);
	अगर (!scucd_area)
		वापस -ENOMEM;
	cd = kzalloc(माप(*cd), GFP_KERNEL);
	अगर (!cd) अणु
		ret = -ENOMEM;
		जाओ out_मुक्त;
	पूर्ण
	अगर (copy_from_user(cd, user_cd, माप(*cd))) अणु
		ret = -EFAULT;
		जाओ out_मुक्त;
	पूर्ण
	scucd_area->request.length = 0x0010;
	scucd_area->request.code = 0x0026;
	scucd_area->m = cd->m;
	scucd_area->fmt1 = cd->fmt;
	scucd_area->cssid = cd->cssid;
	scucd_area->first_cun = cd->cun;
	scucd_area->last_cun = cd->cun;

	ccode = chsc(scucd_area);
	अगर (ccode != 0) अणु
		ret = -EIO;
		जाओ out_मुक्त;
	पूर्ण
	अगर (scucd_area->response.code != 0x0001) अणु
		ret = -EIO;
		CHSC_MSG(0, "scucd: response code=%x\n",
			 scucd_area->response.code);
		जाओ out_मुक्त;
	पूर्ण
	स_नकल(&cd->cucb, &scucd_area->response, scucd_area->response.length);
	अगर (copy_to_user(user_cd, cd, माप(*cd)))
		ret = -EFAULT;
	अन्यथा
		ret = 0;
out_मुक्त:
	kमुक्त(cd);
	मुक्त_page((अचिन्हित दीर्घ)scucd_area);
	वापस ret;
पूर्ण

अटल पूर्णांक chsc_ioctl_info_sch_cu(व्योम __user *user_cud)
अणु
	काष्ठा chsc_sch_cud *cud;
	पूर्णांक ret, ccode;
	काष्ठा अणु
		काष्ठा chsc_header request;
		u32 : 2;
		u32 m : 1;
		u32 : 5;
		u32 fmt1 : 4;
		u32 : 2;
		u32 ssid : 2;
		u32 first_sch : 16;
		u32 : 8;
		u32 cssid : 8;
		u32 last_sch : 16;
		u32 : 32;
		काष्ठा chsc_header response;
		u8 data[PAGE_SIZE - 20];
	पूर्ण __attribute__ ((packed)) *sscud_area;

	sscud_area = (व्योम *)get_zeroed_page(GFP_KERNEL | GFP_DMA);
	अगर (!sscud_area)
		वापस -ENOMEM;
	cud = kzalloc(माप(*cud), GFP_KERNEL);
	अगर (!cud) अणु
		ret = -ENOMEM;
		जाओ out_मुक्त;
	पूर्ण
	अगर (copy_from_user(cud, user_cud, माप(*cud))) अणु
		ret = -EFAULT;
		जाओ out_मुक्त;
	पूर्ण
	sscud_area->request.length = 0x0010;
	sscud_area->request.code = 0x0006;
	sscud_area->m = cud->schid.m;
	sscud_area->fmt1 = cud->fmt;
	sscud_area->ssid = cud->schid.ssid;
	sscud_area->first_sch = cud->schid.sch_no;
	sscud_area->cssid = cud->schid.cssid;
	sscud_area->last_sch = cud->schid.sch_no;

	ccode = chsc(sscud_area);
	अगर (ccode != 0) अणु
		ret = -EIO;
		जाओ out_मुक्त;
	पूर्ण
	अगर (sscud_area->response.code != 0x0001) अणु
		ret = -EIO;
		CHSC_MSG(0, "sscud: response code=%x\n",
			 sscud_area->response.code);
		जाओ out_मुक्त;
	पूर्ण
	स_नकल(&cud->scub, &sscud_area->response, sscud_area->response.length);
	अगर (copy_to_user(user_cud, cud, माप(*cud)))
		ret = -EFAULT;
	अन्यथा
		ret = 0;
out_मुक्त:
	kमुक्त(cud);
	मुक्त_page((अचिन्हित दीर्घ)sscud_area);
	वापस ret;
पूर्ण

अटल पूर्णांक chsc_ioctl_conf_info(व्योम __user *user_ci)
अणु
	काष्ठा chsc_conf_info *ci;
	पूर्णांक ret, ccode;
	काष्ठा अणु
		काष्ठा chsc_header request;
		u32 : 2;
		u32 m : 1;
		u32 : 1;
		u32 fmt1 : 4;
		u32 cssid : 8;
		u32 : 6;
		u32 ssid : 2;
		u32 : 8;
		u64 : 64;
		काष्ठा chsc_header response;
		u8 data[PAGE_SIZE - 20];
	पूर्ण __attribute__ ((packed)) *sci_area;

	sci_area = (व्योम *)get_zeroed_page(GFP_KERNEL | GFP_DMA);
	अगर (!sci_area)
		वापस -ENOMEM;
	ci = kzalloc(माप(*ci), GFP_KERNEL);
	अगर (!ci) अणु
		ret = -ENOMEM;
		जाओ out_मुक्त;
	पूर्ण
	अगर (copy_from_user(ci, user_ci, माप(*ci))) अणु
		ret = -EFAULT;
		जाओ out_मुक्त;
	पूर्ण
	sci_area->request.length = 0x0010;
	sci_area->request.code = 0x0012;
	sci_area->m = ci->id.m;
	sci_area->fmt1 = ci->fmt;
	sci_area->cssid = ci->id.cssid;
	sci_area->ssid = ci->id.ssid;

	ccode = chsc(sci_area);
	अगर (ccode != 0) अणु
		ret = -EIO;
		जाओ out_मुक्त;
	पूर्ण
	अगर (sci_area->response.code != 0x0001) अणु
		ret = -EIO;
		CHSC_MSG(0, "sci: response code=%x\n",
			 sci_area->response.code);
		जाओ out_मुक्त;
	पूर्ण
	स_नकल(&ci->scid, &sci_area->response, sci_area->response.length);
	अगर (copy_to_user(user_ci, ci, माप(*ci)))
		ret = -EFAULT;
	अन्यथा
		ret = 0;
out_मुक्त:
	kमुक्त(ci);
	मुक्त_page((अचिन्हित दीर्घ)sci_area);
	वापस ret;
पूर्ण

अटल पूर्णांक chsc_ioctl_conf_comp_list(व्योम __user *user_ccl)
अणु
	काष्ठा chsc_comp_list *ccl;
	पूर्णांक ret, ccode;
	काष्ठा अणु
		काष्ठा chsc_header request;
		u32 ctype : 8;
		u32 : 4;
		u32 fmt : 4;
		u32 : 16;
		u64 : 64;
		u32 list_parm[2];
		u64 : 64;
		काष्ठा chsc_header response;
		u8 data[PAGE_SIZE - 36];
	पूर्ण __attribute__ ((packed)) *sccl_area;
	काष्ठा अणु
		u32 m : 1;
		u32 : 31;
		u32 cssid : 8;
		u32 : 16;
		u32 chpid : 8;
	पूर्ण __attribute__ ((packed)) *chpid_parm;
	काष्ठा अणु
		u32 f_cssid : 8;
		u32 l_cssid : 8;
		u32 : 16;
		u32 res;
	पूर्ण __attribute__ ((packed)) *cssids_parm;

	sccl_area = (व्योम *)get_zeroed_page(GFP_KERNEL | GFP_DMA);
	अगर (!sccl_area)
		वापस -ENOMEM;
	ccl = kzalloc(माप(*ccl), GFP_KERNEL);
	अगर (!ccl) अणु
		ret = -ENOMEM;
		जाओ out_मुक्त;
	पूर्ण
	अगर (copy_from_user(ccl, user_ccl, माप(*ccl))) अणु
		ret = -EFAULT;
		जाओ out_मुक्त;
	पूर्ण
	sccl_area->request.length = 0x0020;
	sccl_area->request.code = 0x0030;
	sccl_area->fmt = ccl->req.fmt;
	sccl_area->ctype = ccl->req.ctype;
	चयन (sccl_area->ctype) अणु
	हाल CCL_CU_ON_CHP:
	हाल CCL_IOP_CHP:
		chpid_parm = (व्योम *)&sccl_area->list_parm;
		chpid_parm->m = ccl->req.chpid.m;
		chpid_parm->cssid = ccl->req.chpid.chp.cssid;
		chpid_parm->chpid = ccl->req.chpid.chp.id;
		अवरोध;
	हाल CCL_CSS_IMG:
	हाल CCL_CSS_IMG_CONF_CHAR:
		cssids_parm = (व्योम *)&sccl_area->list_parm;
		cssids_parm->f_cssid = ccl->req.cssids.f_cssid;
		cssids_parm->l_cssid = ccl->req.cssids.l_cssid;
		अवरोध;
	पूर्ण
	ccode = chsc(sccl_area);
	अगर (ccode != 0) अणु
		ret = -EIO;
		जाओ out_मुक्त;
	पूर्ण
	अगर (sccl_area->response.code != 0x0001) अणु
		ret = -EIO;
		CHSC_MSG(0, "sccl: response code=%x\n",
			 sccl_area->response.code);
		जाओ out_मुक्त;
	पूर्ण
	स_नकल(&ccl->sccl, &sccl_area->response, sccl_area->response.length);
	अगर (copy_to_user(user_ccl, ccl, माप(*ccl)))
		ret = -EFAULT;
	अन्यथा
		ret = 0;
out_मुक्त:
	kमुक्त(ccl);
	मुक्त_page((अचिन्हित दीर्घ)sccl_area);
	वापस ret;
पूर्ण

अटल पूर्णांक chsc_ioctl_chpd(व्योम __user *user_chpd)
अणु
	काष्ठा chsc_scpd *scpd_area;
	काष्ठा chsc_cpd_info *chpd;
	पूर्णांक ret;

	chpd = kzalloc(माप(*chpd), GFP_KERNEL);
	scpd_area = (व्योम *)get_zeroed_page(GFP_KERNEL | GFP_DMA);
	अगर (!scpd_area || !chpd) अणु
		ret = -ENOMEM;
		जाओ out_मुक्त;
	पूर्ण
	अगर (copy_from_user(chpd, user_chpd, माप(*chpd))) अणु
		ret = -EFAULT;
		जाओ out_मुक्त;
	पूर्ण
	ret = chsc_determine_channel_path_desc(chpd->chpid, chpd->fmt,
					       chpd->rfmt, chpd->c, chpd->m,
					       scpd_area);
	अगर (ret)
		जाओ out_मुक्त;
	स_नकल(&chpd->chpdb, &scpd_area->response, scpd_area->response.length);
	अगर (copy_to_user(user_chpd, chpd, माप(*chpd)))
		ret = -EFAULT;
out_मुक्त:
	kमुक्त(chpd);
	मुक्त_page((अचिन्हित दीर्घ)scpd_area);
	वापस ret;
पूर्ण

अटल पूर्णांक chsc_ioctl_dcal(व्योम __user *user_dcal)
अणु
	काष्ठा chsc_dcal *dcal;
	पूर्णांक ret, ccode;
	काष्ठा अणु
		काष्ठा chsc_header request;
		u32 atype : 8;
		u32 : 4;
		u32 fmt : 4;
		u32 : 16;
		u32 res0[2];
		u32 list_parm[2];
		u32 res1[2];
		काष्ठा chsc_header response;
		u8 data[PAGE_SIZE - 36];
	पूर्ण __attribute__ ((packed)) *sdcal_area;

	sdcal_area = (व्योम *)get_zeroed_page(GFP_KERNEL | GFP_DMA);
	अगर (!sdcal_area)
		वापस -ENOMEM;
	dcal = kzalloc(माप(*dcal), GFP_KERNEL);
	अगर (!dcal) अणु
		ret = -ENOMEM;
		जाओ out_मुक्त;
	पूर्ण
	अगर (copy_from_user(dcal, user_dcal, माप(*dcal))) अणु
		ret = -EFAULT;
		जाओ out_मुक्त;
	पूर्ण
	sdcal_area->request.length = 0x0020;
	sdcal_area->request.code = 0x0034;
	sdcal_area->atype = dcal->req.atype;
	sdcal_area->fmt = dcal->req.fmt;
	स_नकल(&sdcal_area->list_parm, &dcal->req.list_parm,
	       माप(sdcal_area->list_parm));

	ccode = chsc(sdcal_area);
	अगर (ccode != 0) अणु
		ret = -EIO;
		जाओ out_मुक्त;
	पूर्ण
	अगर (sdcal_area->response.code != 0x0001) अणु
		ret = -EIO;
		CHSC_MSG(0, "sdcal: response code=%x\n",
			 sdcal_area->response.code);
		जाओ out_मुक्त;
	पूर्ण
	स_नकल(&dcal->sdcal, &sdcal_area->response,
	       sdcal_area->response.length);
	अगर (copy_to_user(user_dcal, dcal, माप(*dcal)))
		ret = -EFAULT;
	अन्यथा
		ret = 0;
out_मुक्त:
	kमुक्त(dcal);
	मुक्त_page((अचिन्हित दीर्घ)sdcal_area);
	वापस ret;
पूर्ण

अटल दीर्घ chsc_ioctl(काष्ठा file *filp, अचिन्हित पूर्णांक cmd,
		       अचिन्हित दीर्घ arg)
अणु
	व्योम __user *argp;

	CHSC_MSG(2, "chsc_ioctl called, cmd=%x\n", cmd);
	अगर (is_compat_task())
		argp = compat_ptr(arg);
	अन्यथा
		argp = (व्योम __user *)arg;
	चयन (cmd) अणु
	हाल CHSC_START:
		वापस chsc_ioctl_start(argp);
	हाल CHSC_START_SYNC:
		वापस chsc_ioctl_start_sync(argp);
	हाल CHSC_INFO_CHANNEL_PATH:
		वापस chsc_ioctl_info_channel_path(argp);
	हाल CHSC_INFO_CU:
		वापस chsc_ioctl_info_cu(argp);
	हाल CHSC_INFO_SCH_CU:
		वापस chsc_ioctl_info_sch_cu(argp);
	हाल CHSC_INFO_CI:
		वापस chsc_ioctl_conf_info(argp);
	हाल CHSC_INFO_CCL:
		वापस chsc_ioctl_conf_comp_list(argp);
	हाल CHSC_INFO_CPD:
		वापस chsc_ioctl_chpd(argp);
	हाल CHSC_INFO_DCAL:
		वापस chsc_ioctl_dcal(argp);
	हाल CHSC_ON_CLOSE_SET:
		वापस chsc_ioctl_on_बंद_set(argp);
	हाल CHSC_ON_CLOSE_REMOVE:
		वापस chsc_ioctl_on_बंद_हटाओ();
	शेष: /* unknown ioctl number */
		वापस -ENOIOCTLCMD;
	पूर्ण
पूर्ण

अटल atomic_t chsc_पढ़ोy_क्रम_use = ATOMIC_INIT(1);

अटल पूर्णांक chsc_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	अगर (!atomic_dec_and_test(&chsc_पढ़ोy_क्रम_use)) अणु
		atomic_inc(&chsc_पढ़ोy_क्रम_use);
		वापस -EBUSY;
	पूर्ण
	वापस nonseekable_खोलो(inode, file);
पूर्ण

अटल पूर्णांक chsc_release(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	अक्षर dbf[13];
	पूर्णांक ret;

	mutex_lock(&on_बंद_mutex);
	अगर (!on_बंद_chsc_area)
		जाओ out_unlock;
	init_completion(&on_बंद_request->completion);
	CHSC_LOG(0, "on_close");
	chsc_log_command(on_बंद_chsc_area);
	spin_lock_irq(&chsc_lock);
	ret = chsc_async(on_बंद_chsc_area, on_बंद_request);
	spin_unlock_irq(&chsc_lock);
	अगर (ret == -EINPROGRESS) अणु
		रुको_क्रम_completion(&on_बंद_request->completion);
		ret = chsc_examine_irb(on_बंद_request);
	पूर्ण
	snम_लिखो(dbf, माप(dbf), "relret:%d", ret);
	CHSC_LOG(0, dbf);
	मुक्त_page((अचिन्हित दीर्घ)on_बंद_chsc_area);
	on_बंद_chsc_area = शून्य;
	kमुक्त(on_बंद_request);
	on_बंद_request = शून्य;
out_unlock:
	mutex_unlock(&on_बंद_mutex);
	atomic_inc(&chsc_पढ़ोy_क्रम_use);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations chsc_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = chsc_खोलो,
	.release = chsc_release,
	.unlocked_ioctl = chsc_ioctl,
	.compat_ioctl = chsc_ioctl,
	.llseek = no_llseek,
पूर्ण;

अटल काष्ठा miscdevice chsc_misc_device = अणु
	.minor = MISC_DYNAMIC_MINOR,
	.name = "chsc",
	.fops = &chsc_fops,
पूर्ण;

अटल पूर्णांक __init chsc_misc_init(व्योम)
अणु
	वापस misc_रेजिस्टर(&chsc_misc_device);
पूर्ण

अटल व्योम chsc_misc_cleanup(व्योम)
अणु
	misc_deरेजिस्टर(&chsc_misc_device);
पूर्ण

अटल पूर्णांक __init chsc_sch_init(व्योम)
अणु
	पूर्णांक ret;

	ret = chsc_init_dbfs();
	अगर (ret)
		वापस ret;
	isc_रेजिस्टर(CHSC_SCH_ISC);
	ret = chsc_init_sch_driver();
	अगर (ret)
		जाओ out_dbf;
	ret = chsc_misc_init();
	अगर (ret)
		जाओ out_driver;
	वापस ret;
out_driver:
	chsc_cleanup_sch_driver();
out_dbf:
	isc_unरेजिस्टर(CHSC_SCH_ISC);
	chsc_हटाओ_dbfs();
	वापस ret;
पूर्ण

अटल व्योम __निकास chsc_sch_निकास(व्योम)
अणु
	chsc_misc_cleanup();
	chsc_cleanup_sch_driver();
	isc_unरेजिस्टर(CHSC_SCH_ISC);
	chsc_हटाओ_dbfs();
पूर्ण

module_init(chsc_sch_init);
module_निकास(chsc_sch_निकास);
