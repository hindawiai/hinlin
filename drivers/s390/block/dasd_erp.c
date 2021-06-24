<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Author(s)......: Holger Smolinski <Holger.Smolinski@de.ibm.com>
 *		    Horst Hummel <Horst.Hummel@de.ibm.com>
 *		    Carsten Otte <Cotte@de.ibm.com>
 *		    Martin Schwidefsky <schwidefsky@de.ibm.com>
 * Bugreports.to..: <Linux390@de.ibm.com>
 * Copyright IBM Corp. 1999, 2001
 *
 */

#घोषणा KMSG_COMPONENT "dasd"

#समावेश <linux/प्रकार.स>
#समावेश <linux/init.h>

#समावेश <यंत्र/debug.h>
#समावेश <यंत्र/ebcdic.h>
#समावेश <linux/uaccess.h>

/* This is ugly... */
#घोषणा PRINTK_HEADER "dasd_erp:"

#समावेश "dasd_int.h"

काष्ठा dasd_ccw_req *
dasd_alloc_erp_request(अक्षर *magic, पूर्णांक cplength, पूर्णांक datasize,
		       काष्ठा dasd_device * device)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा dasd_ccw_req *cqr;
	अक्षर *data;
	पूर्णांक size;

	/* Sanity checks */
	BUG_ON( magic == शून्य || datasize > PAGE_SIZE ||
	     (cplength*माप(काष्ठा ccw1)) > PAGE_SIZE);

	size = (माप(काष्ठा dasd_ccw_req) + 7L) & -8L;
	अगर (cplength > 0)
		size += cplength * माप(काष्ठा ccw1);
	अगर (datasize > 0)
		size += datasize;
	spin_lock_irqsave(&device->mem_lock, flags);
	cqr = (काष्ठा dasd_ccw_req *)
		dasd_alloc_chunk(&device->erp_chunks, size);
	spin_unlock_irqrestore(&device->mem_lock, flags);
	अगर (cqr == शून्य)
		वापस ERR_PTR(-ENOMEM);
	स_रखो(cqr, 0, माप(काष्ठा dasd_ccw_req));
	INIT_LIST_HEAD(&cqr->devlist);
	INIT_LIST_HEAD(&cqr->blocklist);
	data = (अक्षर *) cqr + ((माप(काष्ठा dasd_ccw_req) + 7L) & -8L);
	cqr->cpaddr = शून्य;
	अगर (cplength > 0) अणु
		cqr->cpaddr = (काष्ठा ccw1 *) data;
		data += cplength*माप(काष्ठा ccw1);
		स_रखो(cqr->cpaddr, 0, cplength*माप(काष्ठा ccw1));
	पूर्ण
	cqr->data = शून्य;
	अगर (datasize > 0) अणु
		cqr->data = data;
 		स_रखो(cqr->data, 0, datasize);
	पूर्ण
	म_नकलन((अक्षर *) &cqr->magic, magic, 4);
	ASCEBC((अक्षर *) &cqr->magic, 4);
	set_bit(DASD_CQR_FLAGS_USE_ERP, &cqr->flags);
	dasd_get_device(device);
	वापस cqr;
पूर्ण

व्योम
dasd_मुक्त_erp_request(काष्ठा dasd_ccw_req *cqr, काष्ठा dasd_device * device)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&device->mem_lock, flags);
	dasd_मुक्त_chunk(&device->erp_chunks, cqr);
	spin_unlock_irqrestore(&device->mem_lock, flags);
	atomic_dec(&device->ref_count);
पूर्ण


/*
 * dasd_शेष_erp_action just retries the current cqr
 */
काष्ठा dasd_ccw_req *
dasd_शेष_erp_action(काष्ठा dasd_ccw_req *cqr)
अणु
	काष्ठा dasd_device *device;

	device = cqr->startdev;

        /* just retry - there is nothing to save ... I got no sense data.... */
        अगर (cqr->retries > 0) अणु
		DBF_DEV_EVENT(DBF_DEBUG, device,
                             "default ERP called (%i retries left)",
                             cqr->retries);
		अगर (!test_bit(DASD_CQR_VERIFY_PATH, &cqr->flags))
			cqr->lpm = dasd_path_get_opm(device);
		cqr->status = DASD_CQR_FILLED;
        पूर्ण अन्यथा अणु
		pr_err("%s: default ERP has run out of retries and failed\n",
		       dev_name(&device->cdev->dev));
		cqr->status = DASD_CQR_FAILED;
		cqr->stopclk = get_tod_घड़ी();
        पूर्ण
        वापस cqr;
पूर्ण				/* end dasd_शेष_erp_action */

/*
 * DESCRIPTION
 *   Frees all ERPs of the current ERP Chain and set the status
 *   of the original CQR either to DASD_CQR_DONE अगर ERP was successful
 *   or to DASD_CQR_FAILED अगर ERP was NOT successful.
 *   NOTE: This function is only called अगर no discipline postaction
 *	   is available
 *
 * PARAMETER
 *   erp		current erp_head
 *
 * RETURN VALUES
 *   cqr		poपूर्णांकer to the original CQR
 */
काष्ठा dasd_ccw_req *dasd_शेष_erp_postaction(काष्ठा dasd_ccw_req *cqr)
अणु
	पूर्णांक success;
	अचिन्हित दीर्घ startclk, stopclk;
	काष्ठा dasd_device *startdev;

	BUG_ON(cqr->refers == शून्य || cqr->function == शून्य);

	success = cqr->status == DASD_CQR_DONE;
	startclk = cqr->startclk;
	stopclk = cqr->stopclk;
	startdev = cqr->startdev;

	/* मुक्त all ERPs - but NOT the original cqr */
	जबतक (cqr->refers != शून्य) अणु
		काष्ठा dasd_ccw_req *refers;

		refers = cqr->refers;
		/* हटाओ the request from the block queue */
		list_del(&cqr->blocklist);
		/* मुक्त the finished erp request */
		dasd_मुक्त_erp_request(cqr, cqr->memdev);
		cqr = refers;
	पूर्ण

	/* set corresponding status to original cqr */
	cqr->startclk = startclk;
	cqr->stopclk = stopclk;
	cqr->startdev = startdev;
	अगर (success)
		cqr->status = DASD_CQR_DONE;
	अन्यथा अणु
		cqr->status = DASD_CQR_FAILED;
		cqr->stopclk = get_tod_घड़ी();
	पूर्ण

	वापस cqr;

पूर्ण				/* end शेष_erp_postaction */

व्योम
dasd_log_sense(काष्ठा dasd_ccw_req *cqr, काष्ठा irb *irb)
अणु
	काष्ठा dasd_device *device;

	device = cqr->startdev;
	अगर (cqr->पूर्णांकrc == -ETIMEDOUT) अणु
		dev_err(&device->cdev->dev,
			"A timeout error occurred for cqr %p\n", cqr);
		वापस;
	पूर्ण
	अगर (cqr->पूर्णांकrc == -ENOLINK) अणु
		dev_err(&device->cdev->dev,
			"A transport error occurred for cqr %p\n", cqr);
		वापस;
	पूर्ण
	/* dump sense data */
	अगर (device->discipline && device->discipline->dump_sense)
		device->discipline->dump_sense(device, cqr, irb);
पूर्ण

व्योम
dasd_log_sense_dbf(काष्ठा dasd_ccw_req *cqr, काष्ठा irb *irb)
अणु
	काष्ठा dasd_device *device;

	device = cqr->startdev;
	/* dump sense data to s390 debugfeature*/
	अगर (device->discipline && device->discipline->dump_sense_dbf)
		device->discipline->dump_sense_dbf(device, irb, "log");
पूर्ण
EXPORT_SYMBOL(dasd_log_sense_dbf);

EXPORT_SYMBOL(dasd_शेष_erp_action);
EXPORT_SYMBOL(dasd_शेष_erp_postaction);
EXPORT_SYMBOL(dasd_alloc_erp_request);
EXPORT_SYMBOL(dasd_मुक्त_erp_request);
EXPORT_SYMBOL(dasd_log_sense);

