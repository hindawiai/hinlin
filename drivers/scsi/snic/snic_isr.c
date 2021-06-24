<शैली गुरु>
/*
 * Copyright 2014 Cisco Systems, Inc.  All rights reserved.
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

#समावेश "vnic_dev.h"
#समावेश "vnic_intr.h"
#समावेश "vnic_stats.h"
#समावेश "snic_io.h"
#समावेश "snic.h"


/*
 * snic_isr_msix_wq : MSIx ISR क्रम work queue.
 */

अटल irqवापस_t
snic_isr_msix_wq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा snic *snic = data;
	अचिन्हित दीर्घ wq_work_करोne = 0;

	snic->s_stats.misc.last_isr_समय = jअगरfies;
	atomic64_inc(&snic->s_stats.misc.ack_isr_cnt);

	wq_work_करोne = snic_wq_cmpl_handler(snic, -1);
	svnic_पूर्णांकr_वापस_credits(&snic->पूर्णांकr[SNIC_MSIX_WQ],
				  wq_work_करोne,
				  1 /* unmask पूर्णांकr */,
				  1 /* reset पूर्णांकr समयr */);

	वापस IRQ_HANDLED;
पूर्ण /* end of snic_isr_msix_wq */

अटल irqवापस_t
snic_isr_msix_io_cmpl(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा snic *snic = data;
	अचिन्हित दीर्घ iocmpl_work_करोne = 0;

	snic->s_stats.misc.last_isr_समय = jअगरfies;
	atomic64_inc(&snic->s_stats.misc.cmpl_isr_cnt);

	iocmpl_work_करोne = snic_fwcq_cmpl_handler(snic, -1);
	svnic_पूर्णांकr_वापस_credits(&snic->पूर्णांकr[SNIC_MSIX_IO_CMPL],
				  iocmpl_work_करोne,
				  1 /* unmask पूर्णांकr */,
				  1 /* reset पूर्णांकr समयr */);

	वापस IRQ_HANDLED;
पूर्ण /* end of snic_isr_msix_io_cmpl */

अटल irqवापस_t
snic_isr_msix_err_notअगरy(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा snic *snic = data;

	snic->s_stats.misc.last_isr_समय = jअगरfies;
	atomic64_inc(&snic->s_stats.misc.त्रुटि_संtअगरy_isr_cnt);

	svnic_पूर्णांकr_वापस_all_credits(&snic->पूर्णांकr[SNIC_MSIX_ERR_NOTIFY]);
	snic_log_q_error(snic);

	/*Handling link events */
	snic_handle_link_event(snic);

	वापस IRQ_HANDLED;
पूर्ण /* end of snic_isr_msix_err_notअगरy */


व्योम
snic_मुक्त_पूर्णांकr(काष्ठा snic *snic)
अणु
	पूर्णांक i;

	/* ONLY पूर्णांकerrupt mode MSIX is supported */
	क्रम (i = 0; i < ARRAY_SIZE(snic->msix); i++) अणु
		अगर (snic->msix[i].requested) अणु
			मुक्त_irq(pci_irq_vector(snic->pdev, i),
				 snic->msix[i].devid);
		पूर्ण
	पूर्ण
पूर्ण /* end of snic_मुक्त_पूर्णांकr */

पूर्णांक
snic_request_पूर्णांकr(काष्ठा snic *snic)
अणु
	पूर्णांक ret = 0, i;
	क्रमागत vnic_dev_पूर्णांकr_mode पूर्णांकr_mode;

	पूर्णांकr_mode = svnic_dev_get_पूर्णांकr_mode(snic->vdev);
	SNIC_BUG_ON(पूर्णांकr_mode != VNIC_DEV_INTR_MODE_MSIX);

	/*
	 * Currently HW supports single WQ and CQ. So passing devid as snic.
	 * When hardware supports multiple WQs and CQs, one idea is
	 * to pass devid as corresponding WQ or CQ ptr and retrieve snic
	 * from queue ptr.
	 * Except क्रम err_notअगरy, which is always one.
	 */
	प्र_लिखो(snic->msix[SNIC_MSIX_WQ].devname,
		"%.11s-scsi-wq",
		snic->name);
	snic->msix[SNIC_MSIX_WQ].isr = snic_isr_msix_wq;
	snic->msix[SNIC_MSIX_WQ].devid = snic;

	प्र_लिखो(snic->msix[SNIC_MSIX_IO_CMPL].devname,
		"%.11s-io-cmpl",
		snic->name);
	snic->msix[SNIC_MSIX_IO_CMPL].isr = snic_isr_msix_io_cmpl;
	snic->msix[SNIC_MSIX_IO_CMPL].devid = snic;

	प्र_लिखो(snic->msix[SNIC_MSIX_ERR_NOTIFY].devname,
		"%.11s-err-notify",
		snic->name);
	snic->msix[SNIC_MSIX_ERR_NOTIFY].isr = snic_isr_msix_err_notअगरy;
	snic->msix[SNIC_MSIX_ERR_NOTIFY].devid = snic;

	क्रम (i = 0; i < ARRAY_SIZE(snic->msix); i++) अणु
		ret = request_irq(pci_irq_vector(snic->pdev, i),
				  snic->msix[i].isr,
				  0,
				  snic->msix[i].devname,
				  snic->msix[i].devid);
		अगर (ret) अणु
			SNIC_HOST_ERR(snic->shost,
				      "MSI-X: request_irq(%d) failed %d\n",
				      i,
				      ret);
			snic_मुक्त_पूर्णांकr(snic);
			अवरोध;
		पूर्ण
		snic->msix[i].requested = 1;
	पूर्ण

	वापस ret;
पूर्ण /* end of snic_request_पूर्णांकr */

पूर्णांक
snic_set_पूर्णांकr_mode(काष्ठा snic *snic)
अणु
	अचिन्हित पूर्णांक n = ARRAY_SIZE(snic->wq);
	अचिन्हित पूर्णांक m = SNIC_CQ_IO_CMPL_MAX;
	अचिन्हित पूर्णांक vecs = n + m + 1;

	/*
	 * We need n WQs, m CQs, and n+m+1 INTRs
	 * (last INTR is used क्रम WQ/CQ errors and notअगरication area
	 */
	BUILD_BUG_ON((ARRAY_SIZE(snic->wq) + SNIC_CQ_IO_CMPL_MAX) >
			ARRAY_SIZE(snic->पूर्णांकr));

	अगर (snic->wq_count < n || snic->cq_count < n + m)
		जाओ fail;

	अगर (pci_alloc_irq_vectors(snic->pdev, vecs, vecs, PCI_IRQ_MSIX) < 0)
		जाओ fail;

	snic->wq_count = n;
	snic->cq_count = n + m;
	snic->पूर्णांकr_count = vecs;
	snic->err_पूर्णांकr_offset = SNIC_MSIX_ERR_NOTIFY;

	SNIC_ISR_DBG(snic->shost, "Using MSI-X Interrupts\n");
	svnic_dev_set_पूर्णांकr_mode(snic->vdev, VNIC_DEV_INTR_MODE_MSIX);
	वापस 0;
fail:
	svnic_dev_set_पूर्णांकr_mode(snic->vdev, VNIC_DEV_INTR_MODE_UNKNOWN);
	वापस -EINVAL;
पूर्ण /* end of snic_set_पूर्णांकr_mode */

व्योम
snic_clear_पूर्णांकr_mode(काष्ठा snic *snic)
अणु
	pci_मुक्त_irq_vectors(snic->pdev);
	svnic_dev_set_पूर्णांकr_mode(snic->vdev, VNIC_DEV_INTR_MODE_INTX);
पूर्ण
