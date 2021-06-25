<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * qdio queue initialization
 *
 * Copyright IBM Corp. 2008
 * Author(s): Jan Glauber <jang@linux.vnet.ibm.com>
 */
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/export.h>
#समावेश <linux/पन.स>

#समावेश <यंत्र/ebcdic.h>
#समावेश <यंत्र/qdपन.स>

#समावेश "cio.h"
#समावेश "css.h"
#समावेश "device.h"
#समावेश "ioasm.h"
#समावेश "chsc.h"
#समावेश "qdio.h"
#समावेश "qdio_debug.h"

#घोषणा QBUFF_PER_PAGE (PAGE_SIZE / माप(काष्ठा qdio_buffer))

अटल काष्ठा kmem_cache *qdio_q_cache;
अटल काष्ठा kmem_cache *qdio_aob_cache;

काष्ठा qaob *qdio_allocate_aob(व्योम)
अणु
	वापस kmem_cache_zalloc(qdio_aob_cache, GFP_ATOMIC);
पूर्ण
EXPORT_SYMBOL_GPL(qdio_allocate_aob);

व्योम qdio_release_aob(काष्ठा qaob *aob)
अणु
	kmem_cache_मुक्त(qdio_aob_cache, aob);
पूर्ण
EXPORT_SYMBOL_GPL(qdio_release_aob);

/**
 * qdio_मुक्त_buffers() - मुक्त qdio buffers
 * @buf: array of poपूर्णांकers to qdio buffers
 * @count: number of qdio buffers to मुक्त
 */
व्योम qdio_मुक्त_buffers(काष्ठा qdio_buffer **buf, अचिन्हित पूर्णांक count)
अणु
	पूर्णांक pos;

	क्रम (pos = 0; pos < count; pos += QBUFF_PER_PAGE)
		मुक्त_page((अचिन्हित दीर्घ) buf[pos]);
पूर्ण
EXPORT_SYMBOL_GPL(qdio_मुक्त_buffers);

/**
 * qdio_alloc_buffers() - allocate qdio buffers
 * @buf: array of poपूर्णांकers to qdio buffers
 * @count: number of qdio buffers to allocate
 */
पूर्णांक qdio_alloc_buffers(काष्ठा qdio_buffer **buf, अचिन्हित पूर्णांक count)
अणु
	पूर्णांक pos;

	क्रम (pos = 0; pos < count; pos += QBUFF_PER_PAGE) अणु
		buf[pos] = (व्योम *) get_zeroed_page(GFP_KERNEL);
		अगर (!buf[pos]) अणु
			qdio_मुक्त_buffers(buf, count);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण
	क्रम (pos = 0; pos < count; pos++)
		अगर (pos % QBUFF_PER_PAGE)
			buf[pos] = buf[pos - 1] + 1;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(qdio_alloc_buffers);

/**
 * qdio_reset_buffers() - reset qdio buffers
 * @buf: array of poपूर्णांकers to qdio buffers
 * @count: number of qdio buffers that will be zeroed
 */
व्योम qdio_reset_buffers(काष्ठा qdio_buffer **buf, अचिन्हित पूर्णांक count)
अणु
	पूर्णांक pos;

	क्रम (pos = 0; pos < count; pos++)
		स_रखो(buf[pos], 0, माप(काष्ठा qdio_buffer));
पूर्ण
EXPORT_SYMBOL_GPL(qdio_reset_buffers);

/*
 * qebsm is only available under 64bit but the adapter sets the feature
 * flag anyway, so we manually override it.
 */
अटल अंतरभूत पूर्णांक qebsm_possible(व्योम)
अणु
	वापस css_general_अक्षरacteristics.qebsm;
पूर्ण

/*
 * qib_param_field: poपूर्णांकer to 128 bytes or शून्य, अगर no param field
 * nr_input_qs: poपूर्णांकer to nr_queues*128 words of data or शून्य
 */
अटल व्योम set_impl_params(काष्ठा qdio_irq *irq_ptr,
			    अचिन्हित पूर्णांक qib_param_field_क्रमmat,
			    अचिन्हित अक्षर *qib_param_field,
			    अचिन्हित दीर्घ *input_slib_elements,
			    अचिन्हित दीर्घ *output_slib_elements)
अणु
	काष्ठा qdio_q *q;
	पूर्णांक i, j;

	अगर (!irq_ptr)
		वापस;

	irq_ptr->qib.pfmt = qib_param_field_क्रमmat;
	अगर (qib_param_field)
		स_नकल(irq_ptr->qib.parm, qib_param_field,
		       माप(irq_ptr->qib.parm));

	अगर (!input_slib_elements)
		जाओ output;

	क्रम_each_input_queue(irq_ptr, q, i) अणु
		क्रम (j = 0; j < QDIO_MAX_BUFFERS_PER_Q; j++)
			q->slib->slibe[j].parms =
				input_slib_elements[i * QDIO_MAX_BUFFERS_PER_Q + j];
	पूर्ण
output:
	अगर (!output_slib_elements)
		वापस;

	क्रम_each_output_queue(irq_ptr, q, i) अणु
		क्रम (j = 0; j < QDIO_MAX_BUFFERS_PER_Q; j++)
			q->slib->slibe[j].parms =
				output_slib_elements[i * QDIO_MAX_BUFFERS_PER_Q + j];
	पूर्ण
पूर्ण

अटल व्योम __qdio_मुक्त_queues(काष्ठा qdio_q **queues, अचिन्हित पूर्णांक count)
अणु
	काष्ठा qdio_q *q;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < count; i++) अणु
		q = queues[i];
		मुक्त_page((अचिन्हित दीर्घ) q->slib);
		kmem_cache_मुक्त(qdio_q_cache, q);
	पूर्ण
पूर्ण

व्योम qdio_मुक्त_queues(काष्ठा qdio_irq *irq_ptr)
अणु
	__qdio_मुक्त_queues(irq_ptr->input_qs, irq_ptr->max_input_qs);
	irq_ptr->max_input_qs = 0;

	__qdio_मुक्त_queues(irq_ptr->output_qs, irq_ptr->max_output_qs);
	irq_ptr->max_output_qs = 0;
पूर्ण

अटल पूर्णांक __qdio_allocate_qs(काष्ठा qdio_q **irq_ptr_qs, पूर्णांक nr_queues)
अणु
	काष्ठा qdio_q *q;
	पूर्णांक i;

	क्रम (i = 0; i < nr_queues; i++) अणु
		q = kmem_cache_zalloc(qdio_q_cache, GFP_KERNEL);
		अगर (!q) अणु
			__qdio_मुक्त_queues(irq_ptr_qs, i);
			वापस -ENOMEM;
		पूर्ण

		q->slib = (काष्ठा slib *) __get_मुक्त_page(GFP_KERNEL);
		अगर (!q->slib) अणु
			kmem_cache_मुक्त(qdio_q_cache, q);
			__qdio_मुक्त_queues(irq_ptr_qs, i);
			वापस -ENOMEM;
		पूर्ण
		irq_ptr_qs[i] = q;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक qdio_allocate_qs(काष्ठा qdio_irq *irq_ptr, पूर्णांक nr_input_qs, पूर्णांक nr_output_qs)
अणु
	पूर्णांक rc;

	rc = __qdio_allocate_qs(irq_ptr->input_qs, nr_input_qs);
	अगर (rc)
		वापस rc;

	rc = __qdio_allocate_qs(irq_ptr->output_qs, nr_output_qs);
	अगर (rc) अणु
		__qdio_मुक्त_queues(irq_ptr->input_qs, nr_input_qs);
		वापस rc;
	पूर्ण

	irq_ptr->max_input_qs = nr_input_qs;
	irq_ptr->max_output_qs = nr_output_qs;
	वापस 0;
पूर्ण

अटल व्योम setup_queues_misc(काष्ठा qdio_q *q, काष्ठा qdio_irq *irq_ptr,
			      qdio_handler_t *handler, पूर्णांक i)
अणु
	काष्ठा slib *slib = q->slib;

	/* queue must be cleared क्रम qdio_establish */
	स_रखो(q, 0, माप(*q));
	स_रखो(slib, 0, PAGE_SIZE);
	q->slib = slib;
	q->irq_ptr = irq_ptr;
	q->mask = 1 << (31 - i);
	q->nr = i;
	q->handler = handler;
पूर्ण

अटल व्योम setup_storage_lists(काष्ठा qdio_q *q, काष्ठा qdio_irq *irq_ptr,
				काष्ठा qdio_buffer **sbals_array, पूर्णांक i)
अणु
	काष्ठा qdio_q *prev;
	पूर्णांक j;

	DBF_HEX(&q, माप(व्योम *));
	q->sl = (काष्ठा sl *)((अक्षर *)q->slib + PAGE_SIZE / 2);

	/* fill in sbal */
	क्रम (j = 0; j < QDIO_MAX_BUFFERS_PER_Q; j++)
		q->sbal[j] = *sbals_array++;

	/* fill in slib */
	अगर (i > 0) अणु
		prev = (q->is_input_q) ? irq_ptr->input_qs[i - 1]
			: irq_ptr->output_qs[i - 1];
		prev->slib->nsliba = (अचिन्हित दीर्घ)q->slib;
	पूर्ण

	q->slib->sla = (अचिन्हित दीर्घ)q->sl;
	q->slib->slsba = (अचिन्हित दीर्घ)&q->slsb.val[0];

	/* fill in sl */
	क्रम (j = 0; j < QDIO_MAX_BUFFERS_PER_Q; j++)
		q->sl->element[j].sbal = virt_to_phys(q->sbal[j]);
पूर्ण

अटल व्योम setup_queues(काष्ठा qdio_irq *irq_ptr,
			 काष्ठा qdio_initialize *qdio_init)
अणु
	काष्ठा qdio_q *q;
	पूर्णांक i;

	क्रम_each_input_queue(irq_ptr, q, i) अणु
		DBF_EVENT("inq:%1d", i);
		setup_queues_misc(q, irq_ptr, qdio_init->input_handler, i);

		q->is_input_q = 1;

		setup_storage_lists(q, irq_ptr,
				    qdio_init->input_sbal_addr_array[i], i);
	पूर्ण

	क्रम_each_output_queue(irq_ptr, q, i) अणु
		DBF_EVENT("outq:%1d", i);
		setup_queues_misc(q, irq_ptr, qdio_init->output_handler, i);

		q->is_input_q = 0;
		setup_storage_lists(q, irq_ptr,
				    qdio_init->output_sbal_addr_array[i], i);

		tasklet_setup(&q->u.out.tasklet, qdio_outbound_tasklet);
		समयr_setup(&q->u.out.समयr, qdio_outbound_समयr, 0);
	पूर्ण
पूर्ण

अटल व्योम process_ac_flags(काष्ठा qdio_irq *irq_ptr, अचिन्हित अक्षर qdioac)
अणु
	अगर (qdioac & AC1_SIGA_INPUT_NEEDED)
		irq_ptr->siga_flag.input = 1;
	अगर (qdioac & AC1_SIGA_OUTPUT_NEEDED)
		irq_ptr->siga_flag.output = 1;
	अगर (qdioac & AC1_SIGA_SYNC_NEEDED)
		irq_ptr->siga_flag.sync = 1;
	अगर (!(qdioac & AC1_AUTOMATIC_SYNC_ON_THININT))
		irq_ptr->siga_flag.sync_after_ai = 1;
	अगर (!(qdioac & AC1_AUTOMATIC_SYNC_ON_OUT_PCI))
		irq_ptr->siga_flag.sync_out_after_pci = 1;
पूर्ण

अटल व्योम check_and_setup_qebsm(काष्ठा qdio_irq *irq_ptr,
				  अचिन्हित अक्षर qdioac, अचिन्हित दीर्घ token)
अणु
	अगर (!(irq_ptr->qib.rflags & QIB_RFLAGS_ENABLE_QEBSM))
		जाओ no_qebsm;
	अगर (!(qdioac & AC1_SC_QEBSM_AVAILABLE) ||
	    (!(qdioac & AC1_SC_QEBSM_ENABLED)))
		जाओ no_qebsm;

	irq_ptr->sch_token = token;

	DBF_EVENT("V=V:1");
	DBF_EVENT("%8lx", irq_ptr->sch_token);
	वापस;

no_qebsm:
	irq_ptr->sch_token = 0;
	irq_ptr->qib.rflags &= ~QIB_RFLAGS_ENABLE_QEBSM;
	DBF_EVENT("noV=V");
पूर्ण

/*
 * If there is a qdio_irq we use the chsc_page and store the inक्रमmation
 * in the qdio_irq, otherwise we copy it to the specअगरied काष्ठाure.
 */
पूर्णांक qdio_setup_get_ssqd(काष्ठा qdio_irq *irq_ptr,
			काष्ठा subchannel_id *schid,
			काष्ठा qdio_ssqd_desc *data)
अणु
	काष्ठा chsc_ssqd_area *ssqd;
	पूर्णांक rc;

	DBF_EVENT("getssqd:%4x", schid->sch_no);
	अगर (!irq_ptr) अणु
		ssqd = (काष्ठा chsc_ssqd_area *)__get_मुक्त_page(GFP_KERNEL);
		अगर (!ssqd)
			वापस -ENOMEM;
	पूर्ण अन्यथा अणु
		ssqd = (काष्ठा chsc_ssqd_area *)irq_ptr->chsc_page;
	पूर्ण

	rc = chsc_ssqd(*schid, ssqd);
	अगर (rc)
		जाओ out;

	अगर (!(ssqd->qdio_ssqd.flags & CHSC_FLAG_QDIO_CAPABILITY) ||
	    !(ssqd->qdio_ssqd.flags & CHSC_FLAG_VALIDITY) ||
	    (ssqd->qdio_ssqd.sch != schid->sch_no))
		rc = -EINVAL;

	अगर (!rc)
		स_नकल(data, &ssqd->qdio_ssqd, माप(*data));

out:
	अगर (!irq_ptr)
		मुक्त_page((अचिन्हित दीर्घ)ssqd);

	वापस rc;
पूर्ण

व्योम qdio_setup_ssqd_info(काष्ठा qdio_irq *irq_ptr)
अणु
	अचिन्हित अक्षर qdioac;
	पूर्णांक rc;

	rc = qdio_setup_get_ssqd(irq_ptr, &irq_ptr->schid, &irq_ptr->ssqd_desc);
	अगर (rc) अणु
		DBF_ERROR("%4x ssqd ERR", irq_ptr->schid.sch_no);
		DBF_ERROR("rc:%x", rc);
		/* all flags set, worst हाल */
		qdioac = AC1_SIGA_INPUT_NEEDED | AC1_SIGA_OUTPUT_NEEDED |
			 AC1_SIGA_SYNC_NEEDED;
	पूर्ण अन्यथा
		qdioac = irq_ptr->ssqd_desc.qdioac1;

	check_and_setup_qebsm(irq_ptr, qdioac, irq_ptr->ssqd_desc.sch_token);
	process_ac_flags(irq_ptr, qdioac);
	DBF_EVENT("ac 1:%2x 2:%4x", qdioac, irq_ptr->ssqd_desc.qdioac2);
	DBF_EVENT("3:%4x qib:%4x", irq_ptr->ssqd_desc.qdioac3, irq_ptr->qib.ac);
पूर्ण

अटल व्योम qdio_fill_qdr_desc(काष्ठा qdesfmt0 *desc, काष्ठा qdio_q *queue)
अणु
	desc->sliba = virt_to_phys(queue->slib);
	desc->sla = virt_to_phys(queue->sl);
	desc->slsba = virt_to_phys(&queue->slsb);

	desc->akey = PAGE_DEFAULT_KEY >> 4;
	desc->bkey = PAGE_DEFAULT_KEY >> 4;
	desc->ckey = PAGE_DEFAULT_KEY >> 4;
	desc->dkey = PAGE_DEFAULT_KEY >> 4;
पूर्ण

अटल व्योम setup_qdr(काष्ठा qdio_irq *irq_ptr,
		      काष्ठा qdio_initialize *qdio_init)
अणु
	काष्ठा qdesfmt0 *desc = &irq_ptr->qdr->qdf0[0];
	पूर्णांक i;

	irq_ptr->qdr->qfmt = qdio_init->q_क्रमmat;
	irq_ptr->qdr->ac = qdio_init->qdr_ac;
	irq_ptr->qdr->iqdcnt = qdio_init->no_input_qs;
	irq_ptr->qdr->oqdcnt = qdio_init->no_output_qs;
	irq_ptr->qdr->iqdsz = माप(काष्ठा qdesfmt0) / 4; /* size in words */
	irq_ptr->qdr->oqdsz = माप(काष्ठा qdesfmt0) / 4;
	irq_ptr->qdr->qiba = virt_to_phys(&irq_ptr->qib);
	irq_ptr->qdr->qkey = PAGE_DEFAULT_KEY >> 4;

	क्रम (i = 0; i < qdio_init->no_input_qs; i++)
		qdio_fill_qdr_desc(desc++, irq_ptr->input_qs[i]);

	क्रम (i = 0; i < qdio_init->no_output_qs; i++)
		qdio_fill_qdr_desc(desc++, irq_ptr->output_qs[i]);
पूर्ण

अटल व्योम setup_qib(काष्ठा qdio_irq *irq_ptr,
		      काष्ठा qdio_initialize *init_data)
अणु
	अगर (qebsm_possible())
		irq_ptr->qib.rflags |= QIB_RFLAGS_ENABLE_QEBSM;

	irq_ptr->qib.rflags |= init_data->qib_rflags;

	irq_ptr->qib.qfmt = init_data->q_क्रमmat;
	अगर (init_data->no_input_qs)
		irq_ptr->qib.isliba =
			(अचिन्हित दीर्घ)(irq_ptr->input_qs[0]->slib);
	अगर (init_data->no_output_qs)
		irq_ptr->qib.osliba =
			(अचिन्हित दीर्घ)(irq_ptr->output_qs[0]->slib);
	स_नकल(irq_ptr->qib.ebcnam, dev_name(&irq_ptr->cdev->dev), 8);
	ASCEBC(irq_ptr->qib.ebcnam, 8);
पूर्ण

पूर्णांक qdio_setup_irq(काष्ठा qdio_irq *irq_ptr, काष्ठा qdio_initialize *init_data)
अणु
	काष्ठा ccw_device *cdev = irq_ptr->cdev;
	काष्ठा ciw *ciw;

	स_रखो(&irq_ptr->qib, 0, माप(irq_ptr->qib));
	स_रखो(&irq_ptr->siga_flag, 0, माप(irq_ptr->siga_flag));
	स_रखो(&irq_ptr->ccw, 0, माप(irq_ptr->ccw));
	स_रखो(&irq_ptr->ssqd_desc, 0, माप(irq_ptr->ssqd_desc));
	स_रखो(&irq_ptr->perf_stat, 0, माप(irq_ptr->perf_stat));

	irq_ptr->debugfs_dev = शून्य;
	irq_ptr->sch_token = irq_ptr->perf_stat_enabled = 0;
	irq_ptr->state = QDIO_IRQ_STATE_INACTIVE;

	/* wipes qib.ac, required by ar7063 */
	स_रखो(irq_ptr->qdr, 0, माप(काष्ठा qdr));

	irq_ptr->पूर्णांक_parm = init_data->पूर्णांक_parm;
	irq_ptr->nr_input_qs = init_data->no_input_qs;
	irq_ptr->nr_output_qs = init_data->no_output_qs;
	irq_ptr->scan_threshold = init_data->scan_threshold;
	ccw_device_get_schid(cdev, &irq_ptr->schid);
	setup_queues(irq_ptr, init_data);

	irq_ptr->irq_poll = init_data->irq_poll;
	set_bit(QDIO_IRQ_DISABLED, &irq_ptr->poll_state);

	setup_qib(irq_ptr, init_data);
	set_impl_params(irq_ptr, init_data->qib_param_field_क्रमmat,
			init_data->qib_param_field,
			init_data->input_slib_elements,
			init_data->output_slib_elements);

	/* fill input and output descriptors */
	setup_qdr(irq_ptr, init_data);

	/* qdr, qib, sls, slsbs, slibs, sbales are filled now */

	/* set our IRQ handler */
	spin_lock_irq(get_ccwdev_lock(cdev));
	irq_ptr->orig_handler = cdev->handler;
	cdev->handler = qdio_पूर्णांक_handler;
	spin_unlock_irq(get_ccwdev_lock(cdev));

	/* get qdio commands */
	ciw = ccw_device_get_ciw(cdev, CIW_TYPE_EQUEUE);
	अगर (!ciw) अणु
		DBF_ERROR("%4x NO EQ", irq_ptr->schid.sch_no);
		वापस -EINVAL;
	पूर्ण
	irq_ptr->equeue = *ciw;

	ciw = ccw_device_get_ciw(cdev, CIW_TYPE_AQUEUE);
	अगर (!ciw) अणु
		DBF_ERROR("%4x NO AQ", irq_ptr->schid.sch_no);
		वापस -EINVAL;
	पूर्ण
	irq_ptr->aqueue = *ciw;

	वापस 0;
पूर्ण

व्योम qdio_shutकरोwn_irq(काष्ठा qdio_irq *irq)
अणु
	काष्ठा ccw_device *cdev = irq->cdev;

	/* restore IRQ handler */
	spin_lock_irq(get_ccwdev_lock(cdev));
	cdev->handler = irq->orig_handler;
	cdev->निजी->पूर्णांकparm = 0;
	spin_unlock_irq(get_ccwdev_lock(cdev));
पूर्ण

व्योम qdio_prपूर्णांक_subchannel_info(काष्ठा qdio_irq *irq_ptr)
अणु
	अक्षर s[80];

	snम_लिखो(s, 80, "qdio: %s %s on SC %x using "
		 "AI:%d QEBSM:%d PRI:%d TDD:%d SIGA:%s%s%s%s%s\n",
		 dev_name(&irq_ptr->cdev->dev),
		 (irq_ptr->qib.qfmt == QDIO_QETH_QFMT) ? "OSA" :
			((irq_ptr->qib.qfmt == QDIO_ZFCP_QFMT) ? "ZFCP" : "HS"),
		 irq_ptr->schid.sch_no,
		 is_thinपूर्णांक_irq(irq_ptr),
		 (irq_ptr->sch_token) ? 1 : 0,
		 pci_out_supported(irq_ptr) ? 1 : 0,
		 css_general_अक्षरacteristics.aअगर_tdd,
		 (irq_ptr->siga_flag.input) ? "R" : " ",
		 (irq_ptr->siga_flag.output) ? "W" : " ",
		 (irq_ptr->siga_flag.sync) ? "S" : " ",
		 (irq_ptr->siga_flag.sync_after_ai) ? "A" : " ",
		 (irq_ptr->siga_flag.sync_out_after_pci) ? "P" : " ");
	prपूर्णांकk(KERN_INFO "%s", s);
पूर्ण

पूर्णांक __init qdio_setup_init(व्योम)
अणु
	पूर्णांक rc;

	qdio_q_cache = kmem_cache_create("qdio_q", माप(काष्ठा qdio_q),
					 256, 0, शून्य);
	अगर (!qdio_q_cache)
		वापस -ENOMEM;

	qdio_aob_cache = kmem_cache_create("qdio_aob",
					माप(काष्ठा qaob),
					माप(काष्ठा qaob),
					0,
					शून्य);
	अगर (!qdio_aob_cache) अणु
		rc = -ENOMEM;
		जाओ मुक्त_qdio_q_cache;
	पूर्ण

	/* Check क्रम OSA/FCP thin पूर्णांकerrupts (bit 67). */
	DBF_EVENT("thinint:%1d",
		  (css_general_अक्षरacteristics.aअगर_osa) ? 1 : 0);

	/* Check क्रम QEBSM support in general (bit 58). */
	DBF_EVENT("cssQEBSM:%1d", (qebsm_possible()) ? 1 : 0);
	rc = 0;
out:
	वापस rc;
मुक्त_qdio_q_cache:
	kmem_cache_destroy(qdio_q_cache);
	जाओ out;
पूर्ण

व्योम qdio_setup_निकास(व्योम)
अणु
	kmem_cache_destroy(qdio_aob_cache);
	kmem_cache_destroy(qdio_q_cache);
पूर्ण
