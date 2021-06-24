<शैली गुरु>
/*
 * Copyright 2008 Cisco Systems, Inc.  All rights reserved.
 * Copyright 2007 Nuova Systems, Inc.  All rights reserved.
 *
 * This program is मुक्त software; you may redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#समावेश <linux/माला.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/pci.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <scsi/libfc.h>
#समावेश <scsi/fc_frame.h>
#समावेश "vnic_dev.h"
#समावेश "vnic_intr.h"
#समावेश "vnic_stats.h"
#समावेश "fnic_io.h"
#समावेश "fnic.h"

अटल irqवापस_t fnic_isr_legacy(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा fnic *fnic = data;
	u32 pba;
	अचिन्हित दीर्घ work_करोne = 0;

	pba = vnic_पूर्णांकr_legacy_pba(fnic->legacy_pba);
	अगर (!pba)
		वापस IRQ_NONE;

	fnic->fnic_stats.misc_stats.last_isr_समय = jअगरfies;
	atomic64_inc(&fnic->fnic_stats.misc_stats.isr_count);

	अगर (pba & (1 << FNIC_INTX_NOTIFY)) अणु
		vnic_पूर्णांकr_वापस_all_credits(&fnic->पूर्णांकr[FNIC_INTX_NOTIFY]);
		fnic_handle_link_event(fnic);
	पूर्ण

	अगर (pba & (1 << FNIC_INTX_ERR)) अणु
		vnic_पूर्णांकr_वापस_all_credits(&fnic->पूर्णांकr[FNIC_INTX_ERR]);
		fnic_log_q_error(fnic);
	पूर्ण

	अगर (pba & (1 << FNIC_INTX_WQ_RQ_COPYWQ)) अणु
		work_करोne += fnic_wq_copy_cmpl_handler(fnic, io_completions);
		work_करोne += fnic_wq_cmpl_handler(fnic, -1);
		work_करोne += fnic_rq_cmpl_handler(fnic, -1);

		vnic_पूर्णांकr_वापस_credits(&fnic->पूर्णांकr[FNIC_INTX_WQ_RQ_COPYWQ],
					 work_करोne,
					 1 /* unmask पूर्णांकr */,
					 1 /* reset पूर्णांकr समयr */);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t fnic_isr_msi(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा fnic *fnic = data;
	अचिन्हित दीर्घ work_करोne = 0;

	fnic->fnic_stats.misc_stats.last_isr_समय = jअगरfies;
	atomic64_inc(&fnic->fnic_stats.misc_stats.isr_count);

	work_करोne += fnic_wq_copy_cmpl_handler(fnic, io_completions);
	work_करोne += fnic_wq_cmpl_handler(fnic, -1);
	work_करोne += fnic_rq_cmpl_handler(fnic, -1);

	vnic_पूर्णांकr_वापस_credits(&fnic->पूर्णांकr[0],
				 work_करोne,
				 1 /* unmask पूर्णांकr */,
				 1 /* reset पूर्णांकr समयr */);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t fnic_isr_msix_rq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा fnic *fnic = data;
	अचिन्हित दीर्घ rq_work_करोne = 0;

	fnic->fnic_stats.misc_stats.last_isr_समय = jअगरfies;
	atomic64_inc(&fnic->fnic_stats.misc_stats.isr_count);

	rq_work_करोne = fnic_rq_cmpl_handler(fnic, -1);
	vnic_पूर्णांकr_वापस_credits(&fnic->पूर्णांकr[FNIC_MSIX_RQ],
				 rq_work_करोne,
				 1 /* unmask पूर्णांकr */,
				 1 /* reset पूर्णांकr समयr */);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t fnic_isr_msix_wq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा fnic *fnic = data;
	अचिन्हित दीर्घ wq_work_करोne = 0;

	fnic->fnic_stats.misc_stats.last_isr_समय = jअगरfies;
	atomic64_inc(&fnic->fnic_stats.misc_stats.isr_count);

	wq_work_करोne = fnic_wq_cmpl_handler(fnic, -1);
	vnic_पूर्णांकr_वापस_credits(&fnic->पूर्णांकr[FNIC_MSIX_WQ],
				 wq_work_करोne,
				 1 /* unmask पूर्णांकr */,
				 1 /* reset पूर्णांकr समयr */);
	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t fnic_isr_msix_wq_copy(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा fnic *fnic = data;
	अचिन्हित दीर्घ wq_copy_work_करोne = 0;

	fnic->fnic_stats.misc_stats.last_isr_समय = jअगरfies;
	atomic64_inc(&fnic->fnic_stats.misc_stats.isr_count);

	wq_copy_work_करोne = fnic_wq_copy_cmpl_handler(fnic, io_completions);
	vnic_पूर्णांकr_वापस_credits(&fnic->पूर्णांकr[FNIC_MSIX_WQ_COPY],
				 wq_copy_work_करोne,
				 1 /* unmask पूर्णांकr */,
				 1 /* reset पूर्णांकr समयr */);
	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t fnic_isr_msix_err_notअगरy(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा fnic *fnic = data;

	fnic->fnic_stats.misc_stats.last_isr_समय = jअगरfies;
	atomic64_inc(&fnic->fnic_stats.misc_stats.isr_count);

	vnic_पूर्णांकr_वापस_all_credits(&fnic->पूर्णांकr[FNIC_MSIX_ERR_NOTIFY]);
	fnic_log_q_error(fnic);
	fnic_handle_link_event(fnic);

	वापस IRQ_HANDLED;
पूर्ण

व्योम fnic_मुक्त_पूर्णांकr(काष्ठा fnic *fnic)
अणु
	पूर्णांक i;

	चयन (vnic_dev_get_पूर्णांकr_mode(fnic->vdev)) अणु
	हाल VNIC_DEV_INTR_MODE_INTX:
	हाल VNIC_DEV_INTR_MODE_MSI:
		मुक्त_irq(pci_irq_vector(fnic->pdev, 0), fnic);
		अवरोध;

	हाल VNIC_DEV_INTR_MODE_MSIX:
		क्रम (i = 0; i < ARRAY_SIZE(fnic->msix); i++)
			अगर (fnic->msix[i].requested)
				मुक्त_irq(pci_irq_vector(fnic->pdev, i),
					 fnic->msix[i].devid);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण
पूर्ण

पूर्णांक fnic_request_पूर्णांकr(काष्ठा fnic *fnic)
अणु
	पूर्णांक err = 0;
	पूर्णांक i;

	चयन (vnic_dev_get_पूर्णांकr_mode(fnic->vdev)) अणु

	हाल VNIC_DEV_INTR_MODE_INTX:
		err = request_irq(pci_irq_vector(fnic->pdev, 0),
				&fnic_isr_legacy, IRQF_SHARED, DRV_NAME, fnic);
		अवरोध;

	हाल VNIC_DEV_INTR_MODE_MSI:
		err = request_irq(pci_irq_vector(fnic->pdev, 0), &fnic_isr_msi,
				  0, fnic->name, fnic);
		अवरोध;

	हाल VNIC_DEV_INTR_MODE_MSIX:

		प्र_लिखो(fnic->msix[FNIC_MSIX_RQ].devname,
			"%.11s-fcs-rq", fnic->name);
		fnic->msix[FNIC_MSIX_RQ].isr = fnic_isr_msix_rq;
		fnic->msix[FNIC_MSIX_RQ].devid = fnic;

		प्र_लिखो(fnic->msix[FNIC_MSIX_WQ].devname,
			"%.11s-fcs-wq", fnic->name);
		fnic->msix[FNIC_MSIX_WQ].isr = fnic_isr_msix_wq;
		fnic->msix[FNIC_MSIX_WQ].devid = fnic;

		प्र_लिखो(fnic->msix[FNIC_MSIX_WQ_COPY].devname,
			"%.11s-scsi-wq", fnic->name);
		fnic->msix[FNIC_MSIX_WQ_COPY].isr = fnic_isr_msix_wq_copy;
		fnic->msix[FNIC_MSIX_WQ_COPY].devid = fnic;

		प्र_लिखो(fnic->msix[FNIC_MSIX_ERR_NOTIFY].devname,
			"%.11s-err-notify", fnic->name);
		fnic->msix[FNIC_MSIX_ERR_NOTIFY].isr =
			fnic_isr_msix_err_notअगरy;
		fnic->msix[FNIC_MSIX_ERR_NOTIFY].devid = fnic;

		क्रम (i = 0; i < ARRAY_SIZE(fnic->msix); i++) अणु
			err = request_irq(pci_irq_vector(fnic->pdev, i),
					  fnic->msix[i].isr, 0,
					  fnic->msix[i].devname,
					  fnic->msix[i].devid);
			अगर (err) अणु
				shost_prपूर्णांकk(KERN_ERR, fnic->lport->host,
					     "MSIX: request_irq"
					     " failed %d\n", err);
				fnic_मुक्त_पूर्णांकr(fnic);
				अवरोध;
			पूर्ण
			fnic->msix[i].requested = 1;
		पूर्ण
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण

पूर्णांक fnic_set_पूर्णांकr_mode(काष्ठा fnic *fnic)
अणु
	अचिन्हित पूर्णांक n = ARRAY_SIZE(fnic->rq);
	अचिन्हित पूर्णांक m = ARRAY_SIZE(fnic->wq);
	अचिन्हित पूर्णांक o = ARRAY_SIZE(fnic->wq_copy);

	/*
	 * Set पूर्णांकerrupt mode (INTx, MSI, MSI-X) depending
	 * प्रणाली capabilities.
	 *
	 * Try MSI-X first
	 *
	 * We need n RQs, m WQs, o Copy WQs, n+m+o CQs, and n+m+o+1 INTRs
	 * (last INTR is used क्रम WQ/RQ errors and notअगरication area)
	 */
	अगर (fnic->rq_count >= n &&
	    fnic->raw_wq_count >= m &&
	    fnic->wq_copy_count >= o &&
	    fnic->cq_count >= n + m + o) अणु
		पूर्णांक vecs = n + m + o + 1;

		अगर (pci_alloc_irq_vectors(fnic->pdev, vecs, vecs,
				PCI_IRQ_MSIX) == vecs) अणु
			fnic->rq_count = n;
			fnic->raw_wq_count = m;
			fnic->wq_copy_count = o;
			fnic->wq_count = m + o;
			fnic->cq_count = n + m + o;
			fnic->पूर्णांकr_count = vecs;
			fnic->err_पूर्णांकr_offset = FNIC_MSIX_ERR_NOTIFY;

			FNIC_ISR_DBG(KERN_DEBUG, fnic->lport->host,
				     "Using MSI-X Interrupts\n");
			vnic_dev_set_पूर्णांकr_mode(fnic->vdev,
					       VNIC_DEV_INTR_MODE_MSIX);
			वापस 0;
		पूर्ण
	पूर्ण

	/*
	 * Next try MSI
	 * We need 1 RQ, 1 WQ, 1 WQ_COPY, 3 CQs, and 1 INTR
	 */
	अगर (fnic->rq_count >= 1 &&
	    fnic->raw_wq_count >= 1 &&
	    fnic->wq_copy_count >= 1 &&
	    fnic->cq_count >= 3 &&
	    fnic->पूर्णांकr_count >= 1 &&
	    pci_alloc_irq_vectors(fnic->pdev, 1, 1, PCI_IRQ_MSI) == 1) अणु
		fnic->rq_count = 1;
		fnic->raw_wq_count = 1;
		fnic->wq_copy_count = 1;
		fnic->wq_count = 2;
		fnic->cq_count = 3;
		fnic->पूर्णांकr_count = 1;
		fnic->err_पूर्णांकr_offset = 0;

		FNIC_ISR_DBG(KERN_DEBUG, fnic->lport->host,
			     "Using MSI Interrupts\n");
		vnic_dev_set_पूर्णांकr_mode(fnic->vdev, VNIC_DEV_INTR_MODE_MSI);

		वापस 0;
	पूर्ण

	/*
	 * Next try INTx
	 * We need 1 RQ, 1 WQ, 1 WQ_COPY, 3 CQs, and 3 INTRs
	 * 1 INTR is used क्रम all 3 queues, 1 INTR क्रम queue errors
	 * 1 INTR क्रम notअगरication area
	 */

	अगर (fnic->rq_count >= 1 &&
	    fnic->raw_wq_count >= 1 &&
	    fnic->wq_copy_count >= 1 &&
	    fnic->cq_count >= 3 &&
	    fnic->पूर्णांकr_count >= 3) अणु

		fnic->rq_count = 1;
		fnic->raw_wq_count = 1;
		fnic->wq_copy_count = 1;
		fnic->cq_count = 3;
		fnic->पूर्णांकr_count = 3;

		FNIC_ISR_DBG(KERN_DEBUG, fnic->lport->host,
			     "Using Legacy Interrupts\n");
		vnic_dev_set_पूर्णांकr_mode(fnic->vdev, VNIC_DEV_INTR_MODE_INTX);

		वापस 0;
	पूर्ण

	vnic_dev_set_पूर्णांकr_mode(fnic->vdev, VNIC_DEV_INTR_MODE_UNKNOWN);

	वापस -EINVAL;
पूर्ण

व्योम fnic_clear_पूर्णांकr_mode(काष्ठा fnic *fnic)
अणु
	pci_मुक्त_irq_vectors(fnic->pdev);
	vnic_dev_set_पूर्णांकr_mode(fnic->vdev, VNIC_DEV_INTR_MODE_INTX);
पूर्ण

