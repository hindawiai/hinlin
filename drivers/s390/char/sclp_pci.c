<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * PCI I/O adapter configuration related functions.
 *
 * Copyright IBM Corp. 2016
 */
#घोषणा KMSG_COMPONENT "sclp_cmd"
#घोषणा pr_fmt(fmt) KMSG_COMPONENT ": " fmt

#समावेश <linux/completion.h>
#समावेश <linux/export.h>
#समावेश <linux/mutex.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/err.h>

#समावेश <यंत्र/sclp.h>

#समावेश "sclp.h"

#घोषणा SCLP_CMDW_CONFIGURE_PCI			0x001a0001
#घोषणा SCLP_CMDW_DECONFIGURE_PCI		0x001b0001

#घोषणा SCLP_ATYPE_PCI				2

#घोषणा SCLP_ERRNOTIFY_AQ_RESET			0
#घोषणा SCLP_ERRNOTIFY_AQ_REPAIR		1
#घोषणा SCLP_ERRNOTIFY_AQ_INFO_LOG		2

अटल DEFINE_MUTEX(sclp_pci_mutex);
अटल काष्ठा sclp_रेजिस्टर sclp_pci_event = अणु
	.send_mask = EVTYP_ERRNOTIFY_MASK,
पूर्ण;

काष्ठा err_notअगरy_evbuf अणु
	काष्ठा evbuf_header header;
	u8 action;
	u8 atype;
	u32 fh;
	u32 fid;
	u8 data[];
पूर्ण __packed;

काष्ठा err_notअगरy_sccb अणु
	काष्ठा sccb_header header;
	काष्ठा err_notअगरy_evbuf evbuf;
पूर्ण __packed;

काष्ठा pci_cfg_sccb अणु
	काष्ठा sccb_header header;
	u8 atype;		/* adapter type */
	u8 reserved1;
	u16 reserved2;
	u32 aid;		/* adapter identअगरier */
पूर्ण __packed;

अटल पूर्णांक करो_pci_configure(sclp_cmdw_t cmd, u32 fid)
अणु
	काष्ठा pci_cfg_sccb *sccb;
	पूर्णांक rc;

	अगर (!SCLP_HAS_PCI_RECONFIG)
		वापस -EOPNOTSUPP;

	sccb = (काष्ठा pci_cfg_sccb *) get_zeroed_page(GFP_KERNEL | GFP_DMA);
	अगर (!sccb)
		वापस -ENOMEM;

	sccb->header.length = PAGE_SIZE;
	sccb->atype = SCLP_ATYPE_PCI;
	sccb->aid = fid;
	rc = sclp_sync_request(cmd, sccb);
	अगर (rc)
		जाओ out;
	चयन (sccb->header.response_code) अणु
	हाल 0x0020:
	हाल 0x0120:
		अवरोध;
	शेष:
		pr_warn("configure PCI I/O adapter failed: cmd=0x%08x  response=0x%04x\n",
			cmd, sccb->header.response_code);
		rc = -EIO;
		अवरोध;
	पूर्ण
out:
	मुक्त_page((अचिन्हित दीर्घ) sccb);
	वापस rc;
पूर्ण

पूर्णांक sclp_pci_configure(u32 fid)
अणु
	वापस करो_pci_configure(SCLP_CMDW_CONFIGURE_PCI, fid);
पूर्ण
EXPORT_SYMBOL(sclp_pci_configure);

पूर्णांक sclp_pci_deconfigure(u32 fid)
अणु
	वापस करो_pci_configure(SCLP_CMDW_DECONFIGURE_PCI, fid);
पूर्ण
EXPORT_SYMBOL(sclp_pci_deconfigure);

अटल व्योम sclp_pci_callback(काष्ठा sclp_req *req, व्योम *data)
अणु
	काष्ठा completion *completion = data;

	complete(completion);
पूर्ण

अटल पूर्णांक sclp_pci_check_report(काष्ठा zpci_report_error_header *report)
अणु
	अगर (report->version != 1)
		वापस -EINVAL;

	चयन (report->action) अणु
	हाल SCLP_ERRNOTIFY_AQ_RESET:
	हाल SCLP_ERRNOTIFY_AQ_REPAIR:
	हाल SCLP_ERRNOTIFY_AQ_INFO_LOG:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (report->length > (PAGE_SIZE - माप(काष्ठा err_notअगरy_sccb)))
		वापस -EINVAL;

	वापस 0;
पूर्ण

पूर्णांक sclp_pci_report(काष्ठा zpci_report_error_header *report, u32 fh, u32 fid)
अणु
	DECLARE_COMPLETION_ONSTACK(completion);
	काष्ठा err_notअगरy_sccb *sccb;
	काष्ठा sclp_req req;
	पूर्णांक ret;

	ret = sclp_pci_check_report(report);
	अगर (ret)
		वापस ret;

	mutex_lock(&sclp_pci_mutex);
	ret = sclp_रेजिस्टर(&sclp_pci_event);
	अगर (ret)
		जाओ out_unlock;

	अगर (!(sclp_pci_event.sclp_receive_mask & EVTYP_ERRNOTIFY_MASK)) अणु
		ret = -EOPNOTSUPP;
		जाओ out_unरेजिस्टर;
	पूर्ण

	sccb = (व्योम *) get_zeroed_page(GFP_KERNEL | GFP_DMA);
	अगर (!sccb) अणु
		ret = -ENOMEM;
		जाओ out_unरेजिस्टर;
	पूर्ण

	स_रखो(&req, 0, माप(req));
	req.callback_data = &completion;
	req.callback = sclp_pci_callback;
	req.command = SCLP_CMDW_WRITE_EVENT_DATA;
	req.status = SCLP_REQ_FILLED;
	req.sccb = sccb;

	sccb->evbuf.header.length = माप(sccb->evbuf) + report->length;
	sccb->evbuf.header.type = EVTYP_ERRNOTIFY;
	sccb->header.length = माप(sccb->header) + sccb->evbuf.header.length;

	sccb->evbuf.action = report->action;
	sccb->evbuf.atype = SCLP_ATYPE_PCI;
	sccb->evbuf.fh = fh;
	sccb->evbuf.fid = fid;

	स_नकल(sccb->evbuf.data, report->data, report->length);

	ret = sclp_add_request(&req);
	अगर (ret)
		जाओ out_मुक्त_req;

	रुको_क्रम_completion(&completion);
	अगर (req.status != SCLP_REQ_DONE) अणु
		pr_warn("request failed (status=0x%02x)\n",
			req.status);
		ret = -EIO;
		जाओ out_मुक्त_req;
	पूर्ण

	अगर (sccb->header.response_code != 0x0020) अणु
		pr_warn("request failed with response code 0x%x\n",
			sccb->header.response_code);
		ret = -EIO;
	पूर्ण

out_मुक्त_req:
	मुक्त_page((अचिन्हित दीर्घ) sccb);
out_unरेजिस्टर:
	sclp_unरेजिस्टर(&sclp_pci_event);
out_unlock:
	mutex_unlock(&sclp_pci_mutex);
	वापस ret;
पूर्ण
