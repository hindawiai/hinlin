<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright IBM Corp. 2012
 *
 * Author(s):
 *   Jan Glauber <jang@linux.vnet.ibm.com>
 */

#घोषणा KMSG_COMPONENT "zpci"
#घोषणा pr_fmt(fmt) KMSG_COMPONENT ": " fmt

#समावेश <linux/compat.h>
#समावेश <linux/kernel.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/slab.h>
#समावेश <linux/err.h>
#समावेश <linux/delay.h>
#समावेश <linux/pci.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/pci_debug.h>
#समावेश <यंत्र/pci_clp.h>
#समावेश <यंत्र/clp.h>
#समावेश <uapi/यंत्र/clp.h>

bool zpci_unique_uid;

व्योम update_uid_checking(bool new)
अणु
	अगर (zpci_unique_uid != new)
		zpci_dbg(1, "uid checking:%d\n", new);

	zpci_unique_uid = new;
पूर्ण

अटल अंतरभूत व्योम zpci_err_clp(अचिन्हित पूर्णांक rsp, पूर्णांक rc)
अणु
	काष्ठा अणु
		अचिन्हित पूर्णांक rsp;
		पूर्णांक rc;
	पूर्ण __packed data = अणुrsp, rcपूर्ण;

	zpci_err_hex(&data, माप(data));
पूर्ण

/*
 * Call Logical Processor with c=1, lps=0 and command 1
 * to get the bit mask of installed logical processors
 */
अटल अंतरभूत पूर्णांक clp_get_ilp(अचिन्हित दीर्घ *ilp)
अणु
	अचिन्हित दीर्घ mask;
	पूर्णांक cc = 3;

	यंत्र अस्थिर (
		"	.insn	rrf,0xb9a00000,%[mask],%[cmd],8,0\n"
		"0:	ipm	%[cc]\n"
		"	srl	%[cc],28\n"
		"1:\n"
		EX_TABLE(0b, 1b)
		: [cc] "+d" (cc), [mask] "=d" (mask) : [cmd] "a" (1)
		: "cc");
	*ilp = mask;
	वापस cc;
पूर्ण

/*
 * Call Logical Processor with c=0, the give स्थिरant lps and an lpcb request.
 */
अटल __always_अंतरभूत पूर्णांक clp_req(व्योम *data, अचिन्हित पूर्णांक lps)
अणु
	काष्ठा अणु u8 _[CLP_BLK_SIZE]; पूर्ण *req = data;
	u64 ignored;
	पूर्णांक cc = 3;

	यंत्र अस्थिर (
		"	.insn	rrf,0xb9a00000,%[ign],%[req],0,%[lps]\n"
		"0:	ipm	%[cc]\n"
		"	srl	%[cc],28\n"
		"1:\n"
		EX_TABLE(0b, 1b)
		: [cc] "+d" (cc), [ign] "=d" (ignored), "+m" (*req)
		: [req] "a" (req), [lps] "i" (lps)
		: "cc");
	वापस cc;
पूर्ण

अटल व्योम *clp_alloc_block(gfp_t gfp_mask)
अणु
	वापस (व्योम *) __get_मुक्त_pages(gfp_mask, get_order(CLP_BLK_SIZE));
पूर्ण

अटल व्योम clp_मुक्त_block(व्योम *ptr)
अणु
	मुक्त_pages((अचिन्हित दीर्घ) ptr, get_order(CLP_BLK_SIZE));
पूर्ण

अटल व्योम clp_store_query_pci_fngrp(काष्ठा zpci_dev *zdev,
				      काष्ठा clp_rsp_query_pci_grp *response)
अणु
	zdev->tlb_refresh = response->refresh;
	zdev->dma_mask = response->dयंत्र;
	zdev->msi_addr = response->msia;
	zdev->max_msi = response->noi;
	zdev->fmb_update = response->mui;
	zdev->version = response->version;

	चयन (response->version) अणु
	हाल 1:
		zdev->max_bus_speed = PCIE_SPEED_5_0GT;
		अवरोध;
	शेष:
		zdev->max_bus_speed = PCI_SPEED_UNKNOWN;
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक clp_query_pci_fngrp(काष्ठा zpci_dev *zdev, u8 pfgid)
अणु
	काष्ठा clp_req_rsp_query_pci_grp *rrb;
	पूर्णांक rc;

	rrb = clp_alloc_block(GFP_KERNEL);
	अगर (!rrb)
		वापस -ENOMEM;

	स_रखो(rrb, 0, माप(*rrb));
	rrb->request.hdr.len = माप(rrb->request);
	rrb->request.hdr.cmd = CLP_QUERY_PCI_FNGRP;
	rrb->response.hdr.len = माप(rrb->response);
	rrb->request.pfgid = pfgid;

	rc = clp_req(rrb, CLP_LPS_PCI);
	अगर (!rc && rrb->response.hdr.rsp == CLP_RC_OK)
		clp_store_query_pci_fngrp(zdev, &rrb->response);
	अन्यथा अणु
		zpci_err("Q PCI FGRP:\n");
		zpci_err_clp(rrb->response.hdr.rsp, rc);
		rc = -EIO;
	पूर्ण
	clp_मुक्त_block(rrb);
	वापस rc;
पूर्ण

अटल पूर्णांक clp_store_query_pci_fn(काष्ठा zpci_dev *zdev,
				  काष्ठा clp_rsp_query_pci *response)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < PCI_STD_NUM_BARS; i++) अणु
		zdev->bars[i].val = le32_to_cpu(response->bar[i]);
		zdev->bars[i].size = response->bar_size[i];
	पूर्ण
	zdev->start_dma = response->sdma;
	zdev->end_dma = response->edma;
	zdev->pchid = response->pchid;
	zdev->pfgid = response->pfgid;
	zdev->pft = response->pft;
	zdev->vfn = response->vfn;
	zdev->port = response->port;
	zdev->uid = response->uid;
	zdev->fmb_length = माप(u32) * response->fmb_len;
	zdev->rid_available = response->rid_avail;
	zdev->is_physfn = response->is_physfn;
	अगर (!s390_pci_no_rid && zdev->rid_available)
		zdev->devfn = response->rid & ZPCI_RID_MASK_DEVFN;

	स_नकल(zdev->pfip, response->pfip, माप(zdev->pfip));
	अगर (response->util_str_avail) अणु
		स_नकल(zdev->util_str, response->util_str,
		       माप(zdev->util_str));
		zdev->util_str_avail = 1;
	पूर्ण
	zdev->mio_capable = response->mio_addr_avail;
	क्रम (i = 0; i < PCI_STD_NUM_BARS; i++) अणु
		अगर (!(response->mio.valid & (1 << (PCI_STD_NUM_BARS - i - 1))))
			जारी;

		zdev->bars[i].mio_wb = (व्योम __iomem *) response->mio.addr[i].wb;
		zdev->bars[i].mio_wt = (व्योम __iomem *) response->mio.addr[i].wt;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक clp_query_pci_fn(काष्ठा zpci_dev *zdev)
अणु
	काष्ठा clp_req_rsp_query_pci *rrb;
	पूर्णांक rc;

	rrb = clp_alloc_block(GFP_KERNEL);
	अगर (!rrb)
		वापस -ENOMEM;

	स_रखो(rrb, 0, माप(*rrb));
	rrb->request.hdr.len = माप(rrb->request);
	rrb->request.hdr.cmd = CLP_QUERY_PCI_FN;
	rrb->response.hdr.len = माप(rrb->response);
	rrb->request.fh = zdev->fh;

	rc = clp_req(rrb, CLP_LPS_PCI);
	अगर (!rc && rrb->response.hdr.rsp == CLP_RC_OK) अणु
		rc = clp_store_query_pci_fn(zdev, &rrb->response);
		अगर (rc)
			जाओ out;
		rc = clp_query_pci_fngrp(zdev, rrb->response.pfgid);
	पूर्ण अन्यथा अणु
		zpci_err("Q PCI FN:\n");
		zpci_err_clp(rrb->response.hdr.rsp, rc);
		rc = -EIO;
	पूर्ण
out:
	clp_मुक्त_block(rrb);
	वापस rc;
पूर्ण

अटल पूर्णांक clp_refresh_fh(u32 fid);
/*
 * Enable/Disable a given PCI function and update its function handle अगर
 * necessary
 */
अटल पूर्णांक clp_set_pci_fn(काष्ठा zpci_dev *zdev, u8 nr_dma_as, u8 command)
अणु
	काष्ठा clp_req_rsp_set_pci *rrb;
	पूर्णांक rc, retries = 100;
	u32 fid = zdev->fid;

	rrb = clp_alloc_block(GFP_KERNEL);
	अगर (!rrb)
		वापस -ENOMEM;

	करो अणु
		स_रखो(rrb, 0, माप(*rrb));
		rrb->request.hdr.len = माप(rrb->request);
		rrb->request.hdr.cmd = CLP_SET_PCI_FN;
		rrb->response.hdr.len = माप(rrb->response);
		rrb->request.fh = zdev->fh;
		rrb->request.oc = command;
		rrb->request.ndas = nr_dma_as;

		rc = clp_req(rrb, CLP_LPS_PCI);
		अगर (rrb->response.hdr.rsp == CLP_RC_SETPCIFN_BUSY) अणु
			retries--;
			अगर (retries < 0)
				अवरोध;
			msleep(20);
		पूर्ण
	पूर्ण जबतक (rrb->response.hdr.rsp == CLP_RC_SETPCIFN_BUSY);

	अगर (rc || rrb->response.hdr.rsp != CLP_RC_OK) अणु
		zpci_err("Set PCI FN:\n");
		zpci_err_clp(rrb->response.hdr.rsp, rc);
	पूर्ण

	अगर (!rc && rrb->response.hdr.rsp == CLP_RC_OK) अणु
		zdev->fh = rrb->response.fh;
	पूर्ण अन्यथा अगर (!rc && rrb->response.hdr.rsp == CLP_RC_SETPCIFN_ALRDY &&
			rrb->response.fh == 0) अणु
		/* Function is alपढ़ोy in desired state - update handle */
		rc = clp_refresh_fh(fid);
	पूर्ण
	clp_मुक्त_block(rrb);
	वापस rc;
पूर्ण

पूर्णांक clp_setup_ग_लिखोback_mio(व्योम)
अणु
	काष्ठा clp_req_rsp_slpc_pci *rrb;
	u8  wb_bit_pos;
	पूर्णांक rc;

	rrb = clp_alloc_block(GFP_KERNEL);
	अगर (!rrb)
		वापस -ENOMEM;

	स_रखो(rrb, 0, माप(*rrb));
	rrb->request.hdr.len = माप(rrb->request);
	rrb->request.hdr.cmd = CLP_SLPC;
	rrb->response.hdr.len = माप(rrb->response);

	rc = clp_req(rrb, CLP_LPS_PCI);
	अगर (!rc && rrb->response.hdr.rsp == CLP_RC_OK) अणु
		अगर (rrb->response.vwb) अणु
			wb_bit_pos = rrb->response.mio_wb;
			set_bit_inv(wb_bit_pos, &mio_wb_bit_mask);
			zpci_dbg(3, "wb bit: %d\n", wb_bit_pos);
		पूर्ण अन्यथा अणु
			zpci_dbg(3, "wb bit: n.a.\n");
		पूर्ण

	पूर्ण अन्यथा अणु
		zpci_err("SLPC PCI:\n");
		zpci_err_clp(rrb->response.hdr.rsp, rc);
		rc = -EIO;
	पूर्ण
	clp_मुक्त_block(rrb);
	वापस rc;
पूर्ण

पूर्णांक clp_enable_fh(काष्ठा zpci_dev *zdev, u8 nr_dma_as)
अणु
	पूर्णांक rc;

	rc = clp_set_pci_fn(zdev, nr_dma_as, CLP_SET_ENABLE_PCI_FN);
	zpci_dbg(3, "ena fid:%x, fh:%x, rc:%d\n", zdev->fid, zdev->fh, rc);
	अगर (rc)
		जाओ out;

	अगर (zpci_use_mio(zdev)) अणु
		rc = clp_set_pci_fn(zdev, nr_dma_as, CLP_SET_ENABLE_MIO);
		zpci_dbg(3, "ena mio fid:%x, fh:%x, rc:%d\n",
				zdev->fid, zdev->fh, rc);
		अगर (rc)
			clp_disable_fh(zdev);
	पूर्ण
out:
	वापस rc;
पूर्ण

पूर्णांक clp_disable_fh(काष्ठा zpci_dev *zdev)
अणु
	पूर्णांक rc;

	अगर (!zdev_enabled(zdev))
		वापस 0;

	rc = clp_set_pci_fn(zdev, 0, CLP_SET_DISABLE_PCI_FN);
	zpci_dbg(3, "dis fid:%x, fh:%x, rc:%d\n", zdev->fid, zdev->fh, rc);
	वापस rc;
पूर्ण

अटल पूर्णांक clp_list_pci(काष्ठा clp_req_rsp_list_pci *rrb, व्योम *data,
			व्योम (*cb)(काष्ठा clp_fh_list_entry *, व्योम *))
अणु
	u64 resume_token = 0;
	पूर्णांक entries, i, rc;

	करो अणु
		स_रखो(rrb, 0, माप(*rrb));
		rrb->request.hdr.len = माप(rrb->request);
		rrb->request.hdr.cmd = CLP_LIST_PCI;
		/* store as many entries as possible */
		rrb->response.hdr.len = CLP_BLK_SIZE - LIST_PCI_HDR_LEN;
		rrb->request.resume_token = resume_token;

		/* Get PCI function handle list */
		rc = clp_req(rrb, CLP_LPS_PCI);
		अगर (rc || rrb->response.hdr.rsp != CLP_RC_OK) अणु
			zpci_err("List PCI FN:\n");
			zpci_err_clp(rrb->response.hdr.rsp, rc);
			rc = -EIO;
			जाओ out;
		पूर्ण

		update_uid_checking(rrb->response.uid_checking);
		WARN_ON_ONCE(rrb->response.entry_size !=
			माप(काष्ठा clp_fh_list_entry));

		entries = (rrb->response.hdr.len - LIST_PCI_HDR_LEN) /
			rrb->response.entry_size;

		resume_token = rrb->response.resume_token;
		क्रम (i = 0; i < entries; i++)
			cb(&rrb->response.fh_list[i], data);
	पूर्ण जबतक (resume_token);
out:
	वापस rc;
पूर्ण

अटल व्योम __clp_add(काष्ठा clp_fh_list_entry *entry, व्योम *data)
अणु
	काष्ठा zpci_dev *zdev;

	अगर (!entry->venकरोr_id)
		वापस;

	zdev = get_zdev_by_fid(entry->fid);
	अगर (!zdev)
		zpci_create_device(entry->fid, entry->fh, entry->config_state);
पूर्ण

पूर्णांक clp_scan_pci_devices(व्योम)
अणु
	काष्ठा clp_req_rsp_list_pci *rrb;
	पूर्णांक rc;

	rrb = clp_alloc_block(GFP_KERNEL);
	अगर (!rrb)
		वापस -ENOMEM;

	rc = clp_list_pci(rrb, शून्य, __clp_add);

	clp_मुक्त_block(rrb);
	वापस rc;
पूर्ण

अटल व्योम __clp_refresh_fh(काष्ठा clp_fh_list_entry *entry, व्योम *data)
अणु
	काष्ठा zpci_dev *zdev;
	u32 fid = *((u32 *)data);

	अगर (!entry->venकरोr_id || fid != entry->fid)
		वापस;

	zdev = get_zdev_by_fid(fid);
	अगर (!zdev)
		वापस;

	zdev->fh = entry->fh;
पूर्ण

/*
 * Refresh the function handle of the function matching @fid
 */
अटल पूर्णांक clp_refresh_fh(u32 fid)
अणु
	काष्ठा clp_req_rsp_list_pci *rrb;
	पूर्णांक rc;

	rrb = clp_alloc_block(GFP_NOWAIT);
	अगर (!rrb)
		वापस -ENOMEM;

	rc = clp_list_pci(rrb, &fid, __clp_refresh_fh);

	clp_मुक्त_block(rrb);
	वापस rc;
पूर्ण

काष्ठा clp_state_data अणु
	u32 fid;
	क्रमागत zpci_state state;
पूर्ण;

अटल व्योम __clp_get_state(काष्ठा clp_fh_list_entry *entry, व्योम *data)
अणु
	काष्ठा clp_state_data *sd = data;

	अगर (entry->fid != sd->fid)
		वापस;

	sd->state = entry->config_state;
पूर्ण

पूर्णांक clp_get_state(u32 fid, क्रमागत zpci_state *state)
अणु
	काष्ठा clp_req_rsp_list_pci *rrb;
	काष्ठा clp_state_data sd = अणुfid, ZPCI_FN_STATE_RESERVEDपूर्ण;
	पूर्णांक rc;

	rrb = clp_alloc_block(GFP_ATOMIC);
	अगर (!rrb)
		वापस -ENOMEM;

	rc = clp_list_pci(rrb, &sd, __clp_get_state);
	अगर (!rc)
		*state = sd.state;

	clp_मुक्त_block(rrb);
	वापस rc;
पूर्ण

अटल पूर्णांक clp_base_slpc(काष्ठा clp_req *req, काष्ठा clp_req_rsp_slpc *lpcb)
अणु
	अचिन्हित दीर्घ limit = PAGE_SIZE - माप(lpcb->request);

	अगर (lpcb->request.hdr.len != माप(lpcb->request) ||
	    lpcb->response.hdr.len > limit)
		वापस -EINVAL;
	वापस clp_req(lpcb, CLP_LPS_BASE) ? -EOPNOTSUPP : 0;
पूर्ण

अटल पूर्णांक clp_base_command(काष्ठा clp_req *req, काष्ठा clp_req_hdr *lpcb)
अणु
	चयन (lpcb->cmd) अणु
	हाल 0x0001: /* store logical-processor अक्षरacteristics */
		वापस clp_base_slpc(req, (व्योम *) lpcb);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक clp_pci_slpc(काष्ठा clp_req *req, काष्ठा clp_req_rsp_slpc_pci *lpcb)
अणु
	अचिन्हित दीर्घ limit = PAGE_SIZE - माप(lpcb->request);

	अगर (lpcb->request.hdr.len != माप(lpcb->request) ||
	    lpcb->response.hdr.len > limit)
		वापस -EINVAL;
	वापस clp_req(lpcb, CLP_LPS_PCI) ? -EOPNOTSUPP : 0;
पूर्ण

अटल पूर्णांक clp_pci_list(काष्ठा clp_req *req, काष्ठा clp_req_rsp_list_pci *lpcb)
अणु
	अचिन्हित दीर्घ limit = PAGE_SIZE - माप(lpcb->request);

	अगर (lpcb->request.hdr.len != माप(lpcb->request) ||
	    lpcb->response.hdr.len > limit)
		वापस -EINVAL;
	अगर (lpcb->request.reserved2 != 0)
		वापस -EINVAL;
	वापस clp_req(lpcb, CLP_LPS_PCI) ? -EOPNOTSUPP : 0;
पूर्ण

अटल पूर्णांक clp_pci_query(काष्ठा clp_req *req,
			 काष्ठा clp_req_rsp_query_pci *lpcb)
अणु
	अचिन्हित दीर्घ limit = PAGE_SIZE - माप(lpcb->request);

	अगर (lpcb->request.hdr.len != माप(lpcb->request) ||
	    lpcb->response.hdr.len > limit)
		वापस -EINVAL;
	अगर (lpcb->request.reserved2 != 0 || lpcb->request.reserved3 != 0)
		वापस -EINVAL;
	वापस clp_req(lpcb, CLP_LPS_PCI) ? -EOPNOTSUPP : 0;
पूर्ण

अटल पूर्णांक clp_pci_query_grp(काष्ठा clp_req *req,
			     काष्ठा clp_req_rsp_query_pci_grp *lpcb)
अणु
	अचिन्हित दीर्घ limit = PAGE_SIZE - माप(lpcb->request);

	अगर (lpcb->request.hdr.len != माप(lpcb->request) ||
	    lpcb->response.hdr.len > limit)
		वापस -EINVAL;
	अगर (lpcb->request.reserved2 != 0 || lpcb->request.reserved3 != 0 ||
	    lpcb->request.reserved4 != 0)
		वापस -EINVAL;
	वापस clp_req(lpcb, CLP_LPS_PCI) ? -EOPNOTSUPP : 0;
पूर्ण

अटल पूर्णांक clp_pci_command(काष्ठा clp_req *req, काष्ठा clp_req_hdr *lpcb)
अणु
	चयन (lpcb->cmd) अणु
	हाल 0x0001: /* store logical-processor अक्षरacteristics */
		वापस clp_pci_slpc(req, (व्योम *) lpcb);
	हाल 0x0002: /* list PCI functions */
		वापस clp_pci_list(req, (व्योम *) lpcb);
	हाल 0x0003: /* query PCI function */
		वापस clp_pci_query(req, (व्योम *) lpcb);
	हाल 0x0004: /* query PCI function group */
		वापस clp_pci_query_grp(req, (व्योम *) lpcb);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक clp_normal_command(काष्ठा clp_req *req)
अणु
	काष्ठा clp_req_hdr *lpcb;
	व्योम __user *uptr;
	पूर्णांक rc;

	rc = -EINVAL;
	अगर (req->lps != 0 && req->lps != 2)
		जाओ out;

	rc = -ENOMEM;
	lpcb = clp_alloc_block(GFP_KERNEL);
	अगर (!lpcb)
		जाओ out;

	rc = -EFAULT;
	uptr = (व्योम __क्रमce __user *)(अचिन्हित दीर्घ) req->data_p;
	अगर (copy_from_user(lpcb, uptr, PAGE_SIZE) != 0)
		जाओ out_मुक्त;

	rc = -EINVAL;
	अगर (lpcb->fmt != 0 || lpcb->reserved1 != 0 || lpcb->reserved2 != 0)
		जाओ out_मुक्त;

	चयन (req->lps) अणु
	हाल 0:
		rc = clp_base_command(req, lpcb);
		अवरोध;
	हाल 2:
		rc = clp_pci_command(req, lpcb);
		अवरोध;
	पूर्ण
	अगर (rc)
		जाओ out_मुक्त;

	rc = -EFAULT;
	अगर (copy_to_user(uptr, lpcb, PAGE_SIZE) != 0)
		जाओ out_मुक्त;

	rc = 0;

out_मुक्त:
	clp_मुक्त_block(lpcb);
out:
	वापस rc;
पूर्ण

अटल पूर्णांक clp_immediate_command(काष्ठा clp_req *req)
अणु
	व्योम __user *uptr;
	अचिन्हित दीर्घ ilp;
	पूर्णांक exists;

	अगर (req->cmd > 1 || clp_get_ilp(&ilp) != 0)
		वापस -EINVAL;

	uptr = (व्योम __क्रमce __user *)(अचिन्हित दीर्घ) req->data_p;
	अगर (req->cmd == 0) अणु
		/* Command code 0: test क्रम a specअगरic processor */
		exists = test_bit_inv(req->lps, &ilp);
		वापस put_user(exists, (पूर्णांक __user *) uptr);
	पूर्ण
	/* Command code 1: वापस bit mask of installed processors */
	वापस put_user(ilp, (अचिन्हित दीर्घ __user *) uptr);
पूर्ण

अटल दीर्घ clp_misc_ioctl(काष्ठा file *filp, अचिन्हित पूर्णांक cmd,
			   अचिन्हित दीर्घ arg)
अणु
	काष्ठा clp_req req;
	व्योम __user *argp;

	अगर (cmd != CLP_SYNC)
		वापस -EINVAL;

	argp = is_compat_task() ? compat_ptr(arg) : (व्योम __user *) arg;
	अगर (copy_from_user(&req, argp, माप(req)))
		वापस -EFAULT;
	अगर (req.r != 0)
		वापस -EINVAL;
	वापस req.c ? clp_immediate_command(&req) : clp_normal_command(&req);
पूर्ण

अटल पूर्णांक clp_misc_release(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations clp_misc_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = nonseekable_खोलो,
	.release = clp_misc_release,
	.unlocked_ioctl = clp_misc_ioctl,
	.compat_ioctl = clp_misc_ioctl,
	.llseek = no_llseek,
पूर्ण;

अटल काष्ठा miscdevice clp_misc_device = अणु
	.minor = MISC_DYNAMIC_MINOR,
	.name = "clp",
	.fops = &clp_misc_fops,
पूर्ण;

अटल पूर्णांक __init clp_misc_init(व्योम)
अणु
	वापस misc_रेजिस्टर(&clp_misc_device);
पूर्ण

device_initcall(clp_misc_init);
