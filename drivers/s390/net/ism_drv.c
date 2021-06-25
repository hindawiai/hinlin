<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * ISM driver क्रम s390.
 *
 * Copyright IBM Corp. 2018
 */
#घोषणा KMSG_COMPONENT "ism"
#घोषणा pr_fmt(fmt) KMSG_COMPONENT ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/device.h>
#समावेश <linux/pci.h>
#समावेश <linux/err.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/processor.h>
#समावेश <net/smc.h>

#समावेश <यंत्र/debug.h>

#समावेश "ism.h"

MODULE_DESCRIPTION("ISM driver for s390");
MODULE_LICENSE("GPL");

#घोषणा PCI_DEVICE_ID_IBM_ISM 0x04ED
#घोषणा DRV_NAME "ism"

अटल स्थिर काष्ठा pci_device_id ism_device_table[] = अणु
	अणु PCI_VDEVICE(IBM, PCI_DEVICE_ID_IBM_ISM), 0 पूर्ण,
	अणु 0, पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, ism_device_table);

अटल debug_info_t *ism_debug_info;

अटल पूर्णांक ism_cmd(काष्ठा ism_dev *ism, व्योम *cmd)
अणु
	काष्ठा ism_req_hdr *req = cmd;
	काष्ठा ism_resp_hdr *resp = cmd;

	__ism_ग_लिखो_cmd(ism, req + 1, माप(*req), req->len - माप(*req));
	__ism_ग_लिखो_cmd(ism, req, 0, माप(*req));

	WRITE_ONCE(resp->ret, ISM_ERROR);

	__ism_पढ़ो_cmd(ism, resp, 0, माप(*resp));
	अगर (resp->ret) अणु
		debug_text_event(ism_debug_info, 0, "cmd failure");
		debug_event(ism_debug_info, 0, resp, माप(*resp));
		जाओ out;
	पूर्ण
	__ism_पढ़ो_cmd(ism, resp + 1, माप(*resp), resp->len - माप(*resp));
out:
	वापस resp->ret;
पूर्ण

अटल पूर्णांक ism_cmd_simple(काष्ठा ism_dev *ism, u32 cmd_code)
अणु
	जोड़ ism_cmd_simple cmd;

	स_रखो(&cmd, 0, माप(cmd));
	cmd.request.hdr.cmd = cmd_code;
	cmd.request.hdr.len = माप(cmd.request);

	वापस ism_cmd(ism, &cmd);
पूर्ण

अटल पूर्णांक query_info(काष्ठा ism_dev *ism)
अणु
	जोड़ ism_qi cmd;

	स_रखो(&cmd, 0, माप(cmd));
	cmd.request.hdr.cmd = ISM_QUERY_INFO;
	cmd.request.hdr.len = माप(cmd.request);

	अगर (ism_cmd(ism, &cmd))
		जाओ out;

	debug_text_event(ism_debug_info, 3, "query info");
	debug_event(ism_debug_info, 3, &cmd.response, माप(cmd.response));
out:
	वापस 0;
पूर्ण

अटल पूर्णांक रेजिस्टर_sba(काष्ठा ism_dev *ism)
अणु
	जोड़ ism_reg_sba cmd;
	dma_addr_t dma_handle;
	काष्ठा ism_sba *sba;

	sba = dma_alloc_coherent(&ism->pdev->dev, PAGE_SIZE, &dma_handle,
				 GFP_KERNEL);
	अगर (!sba)
		वापस -ENOMEM;

	स_रखो(&cmd, 0, माप(cmd));
	cmd.request.hdr.cmd = ISM_REG_SBA;
	cmd.request.hdr.len = माप(cmd.request);
	cmd.request.sba = dma_handle;

	अगर (ism_cmd(ism, &cmd)) अणु
		dma_मुक्त_coherent(&ism->pdev->dev, PAGE_SIZE, sba, dma_handle);
		वापस -EIO;
	पूर्ण

	ism->sba = sba;
	ism->sba_dma_addr = dma_handle;

	वापस 0;
पूर्ण

अटल पूर्णांक रेजिस्टर_ieq(काष्ठा ism_dev *ism)
अणु
	जोड़ ism_reg_ieq cmd;
	dma_addr_t dma_handle;
	काष्ठा ism_eq *ieq;

	ieq = dma_alloc_coherent(&ism->pdev->dev, PAGE_SIZE, &dma_handle,
				 GFP_KERNEL);
	अगर (!ieq)
		वापस -ENOMEM;

	स_रखो(&cmd, 0, माप(cmd));
	cmd.request.hdr.cmd = ISM_REG_IEQ;
	cmd.request.hdr.len = माप(cmd.request);
	cmd.request.ieq = dma_handle;
	cmd.request.len = माप(*ieq);

	अगर (ism_cmd(ism, &cmd)) अणु
		dma_मुक्त_coherent(&ism->pdev->dev, PAGE_SIZE, ieq, dma_handle);
		वापस -EIO;
	पूर्ण

	ism->ieq = ieq;
	ism->ieq_idx = -1;
	ism->ieq_dma_addr = dma_handle;

	वापस 0;
पूर्ण

अटल पूर्णांक unरेजिस्टर_sba(काष्ठा ism_dev *ism)
अणु
	पूर्णांक ret;

	अगर (!ism->sba)
		वापस 0;

	ret = ism_cmd_simple(ism, ISM_UNREG_SBA);
	अगर (ret && ret != ISM_ERROR)
		वापस -EIO;

	dma_मुक्त_coherent(&ism->pdev->dev, PAGE_SIZE,
			  ism->sba, ism->sba_dma_addr);

	ism->sba = शून्य;
	ism->sba_dma_addr = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक unरेजिस्टर_ieq(काष्ठा ism_dev *ism)
अणु
	पूर्णांक ret;

	अगर (!ism->ieq)
		वापस 0;

	ret = ism_cmd_simple(ism, ISM_UNREG_IEQ);
	अगर (ret && ret != ISM_ERROR)
		वापस -EIO;

	dma_मुक्त_coherent(&ism->pdev->dev, PAGE_SIZE,
			  ism->ieq, ism->ieq_dma_addr);

	ism->ieq = शून्य;
	ism->ieq_dma_addr = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक ism_पढ़ो_local_gid(काष्ठा ism_dev *ism)
अणु
	जोड़ ism_पढ़ो_gid cmd;
	पूर्णांक ret;

	स_रखो(&cmd, 0, माप(cmd));
	cmd.request.hdr.cmd = ISM_READ_GID;
	cmd.request.hdr.len = माप(cmd.request);

	ret = ism_cmd(ism, &cmd);
	अगर (ret)
		जाओ out;

	ism->smcd->local_gid = cmd.response.gid;
out:
	वापस ret;
पूर्ण

अटल पूर्णांक ism_query_rgid(काष्ठा smcd_dev *smcd, u64 rgid, u32 vid_valid,
			  u32 vid)
अणु
	काष्ठा ism_dev *ism = smcd->priv;
	जोड़ ism_query_rgid cmd;

	स_रखो(&cmd, 0, माप(cmd));
	cmd.request.hdr.cmd = ISM_QUERY_RGID;
	cmd.request.hdr.len = माप(cmd.request);

	cmd.request.rgid = rgid;
	cmd.request.vlan_valid = vid_valid;
	cmd.request.vlan_id = vid;

	वापस ism_cmd(ism, &cmd);
पूर्ण

अटल व्योम ism_मुक्त_dmb(काष्ठा ism_dev *ism, काष्ठा smcd_dmb *dmb)
अणु
	clear_bit(dmb->sba_idx, ism->sba_biपंचांगap);
	dma_मुक्त_coherent(&ism->pdev->dev, dmb->dmb_len,
			  dmb->cpu_addr, dmb->dma_addr);
पूर्ण

अटल पूर्णांक ism_alloc_dmb(काष्ठा ism_dev *ism, काष्ठा smcd_dmb *dmb)
अणु
	अचिन्हित दीर्घ bit;

	अगर (PAGE_ALIGN(dmb->dmb_len) > dma_get_max_seg_size(&ism->pdev->dev))
		वापस -EINVAL;

	अगर (!dmb->sba_idx) अणु
		bit = find_next_zero_bit(ism->sba_biपंचांगap, ISM_NR_DMBS,
					 ISM_DMB_BIT_OFFSET);
		अगर (bit == ISM_NR_DMBS)
			वापस -ENOSPC;

		dmb->sba_idx = bit;
	पूर्ण
	अगर (dmb->sba_idx < ISM_DMB_BIT_OFFSET ||
	    test_and_set_bit(dmb->sba_idx, ism->sba_biपंचांगap))
		वापस -EINVAL;

	dmb->cpu_addr = dma_alloc_coherent(&ism->pdev->dev, dmb->dmb_len,
					   &dmb->dma_addr,
					   GFP_KERNEL | __GFP_NOWARN | __GFP_NOMEMALLOC | __GFP_COMP | __GFP_NORETRY);
	अगर (!dmb->cpu_addr)
		clear_bit(dmb->sba_idx, ism->sba_biपंचांगap);

	वापस dmb->cpu_addr ? 0 : -ENOMEM;
पूर्ण

अटल पूर्णांक ism_रेजिस्टर_dmb(काष्ठा smcd_dev *smcd, काष्ठा smcd_dmb *dmb)
अणु
	काष्ठा ism_dev *ism = smcd->priv;
	जोड़ ism_reg_dmb cmd;
	पूर्णांक ret;

	ret = ism_alloc_dmb(ism, dmb);
	अगर (ret)
		जाओ out;

	स_रखो(&cmd, 0, माप(cmd));
	cmd.request.hdr.cmd = ISM_REG_DMB;
	cmd.request.hdr.len = माप(cmd.request);

	cmd.request.dmb = dmb->dma_addr;
	cmd.request.dmb_len = dmb->dmb_len;
	cmd.request.sba_idx = dmb->sba_idx;
	cmd.request.vlan_valid = dmb->vlan_valid;
	cmd.request.vlan_id = dmb->vlan_id;
	cmd.request.rgid = dmb->rgid;

	ret = ism_cmd(ism, &cmd);
	अगर (ret) अणु
		ism_मुक्त_dmb(ism, dmb);
		जाओ out;
	पूर्ण
	dmb->dmb_tok = cmd.response.dmb_tok;
out:
	वापस ret;
पूर्ण

अटल पूर्णांक ism_unरेजिस्टर_dmb(काष्ठा smcd_dev *smcd, काष्ठा smcd_dmb *dmb)
अणु
	काष्ठा ism_dev *ism = smcd->priv;
	जोड़ ism_unreg_dmb cmd;
	पूर्णांक ret;

	स_रखो(&cmd, 0, माप(cmd));
	cmd.request.hdr.cmd = ISM_UNREG_DMB;
	cmd.request.hdr.len = माप(cmd.request);

	cmd.request.dmb_tok = dmb->dmb_tok;

	ret = ism_cmd(ism, &cmd);
	अगर (ret && ret != ISM_ERROR)
		जाओ out;

	ism_मुक्त_dmb(ism, dmb);
out:
	वापस ret;
पूर्ण

अटल पूर्णांक ism_add_vlan_id(काष्ठा smcd_dev *smcd, u64 vlan_id)
अणु
	काष्ठा ism_dev *ism = smcd->priv;
	जोड़ ism_set_vlan_id cmd;

	स_रखो(&cmd, 0, माप(cmd));
	cmd.request.hdr.cmd = ISM_ADD_VLAN_ID;
	cmd.request.hdr.len = माप(cmd.request);

	cmd.request.vlan_id = vlan_id;

	वापस ism_cmd(ism, &cmd);
पूर्ण

अटल पूर्णांक ism_del_vlan_id(काष्ठा smcd_dev *smcd, u64 vlan_id)
अणु
	काष्ठा ism_dev *ism = smcd->priv;
	जोड़ ism_set_vlan_id cmd;

	स_रखो(&cmd, 0, माप(cmd));
	cmd.request.hdr.cmd = ISM_DEL_VLAN_ID;
	cmd.request.hdr.len = माप(cmd.request);

	cmd.request.vlan_id = vlan_id;

	वापस ism_cmd(ism, &cmd);
पूर्ण

अटल पूर्णांक ism_set_vlan_required(काष्ठा smcd_dev *smcd)
अणु
	वापस ism_cmd_simple(smcd->priv, ISM_SET_VLAN);
पूर्ण

अटल पूर्णांक ism_reset_vlan_required(काष्ठा smcd_dev *smcd)
अणु
	वापस ism_cmd_simple(smcd->priv, ISM_RESET_VLAN);
पूर्ण

अटल पूर्णांक ism_संकेत_ieq(काष्ठा smcd_dev *smcd, u64 rgid, u32 trigger_irq,
			  u32 event_code, u64 info)
अणु
	काष्ठा ism_dev *ism = smcd->priv;
	जोड़ ism_sig_ieq cmd;

	स_रखो(&cmd, 0, माप(cmd));
	cmd.request.hdr.cmd = ISM_SIGNAL_IEQ;
	cmd.request.hdr.len = माप(cmd.request);

	cmd.request.rgid = rgid;
	cmd.request.trigger_irq = trigger_irq;
	cmd.request.event_code = event_code;
	cmd.request.info = info;

	वापस ism_cmd(ism, &cmd);
पूर्ण

अटल अचिन्हित पूर्णांक max_bytes(अचिन्हित पूर्णांक start, अचिन्हित पूर्णांक len,
			      अचिन्हित पूर्णांक boundary)
अणु
	वापस min(boundary - (start & (boundary - 1)), len);
पूर्ण

अटल पूर्णांक ism_move(काष्ठा smcd_dev *smcd, u64 dmb_tok, अचिन्हित पूर्णांक idx,
		    bool sf, अचिन्हित पूर्णांक offset, व्योम *data, अचिन्हित पूर्णांक size)
अणु
	काष्ठा ism_dev *ism = smcd->priv;
	अचिन्हित पूर्णांक bytes;
	u64 dmb_req;
	पूर्णांक ret;

	जबतक (size) अणु
		bytes = max_bytes(offset, size, PAGE_SIZE);
		dmb_req = ISM_CREATE_REQ(dmb_tok, idx, size == bytes ? sf : 0,
					 offset);

		ret = __ism_move(ism, dmb_req, data, bytes);
		अगर (ret)
			वापस ret;

		size -= bytes;
		data += bytes;
		offset += bytes;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा ism_प्रणालीeid SYSTEM_EID = अणु
	.seid_string = "IBM-SYSZ-ISMSEID00000000",
	.serial_number = "0000",
	.type = "0000",
पूर्ण;

अटल व्योम ism_create_प्रणाली_eid(व्योम)
अणु
	काष्ठा cpuid id;
	u16 ident_tail;
	अक्षर पंचांगp[5];

	get_cpu_id(&id);
	ident_tail = (u16)(id.ident & ISM_IDENT_MASK);
	snम_लिखो(पंचांगp, 5, "%04X", ident_tail);
	स_नकल(&SYSTEM_EID.serial_number, पंचांगp, 4);
	snम_लिखो(पंचांगp, 5, "%04X", id.machine);
	स_नकल(&SYSTEM_EID.type, पंचांगp, 4);
पूर्ण

अटल व्योम ism_get_प्रणाली_eid(काष्ठा smcd_dev *smcd, u8 **eid)
अणु
	*eid = &SYSTEM_EID.seid_string[0];
पूर्ण

अटल u16 ism_get_chid(काष्ठा smcd_dev *smcd)
अणु
	काष्ठा ism_dev *ismdev;

	ismdev = (काष्ठा ism_dev *)smcd->priv;
	अगर (!ismdev || !ismdev->pdev)
		वापस 0;

	वापस to_zpci(ismdev->pdev)->pchid;
पूर्ण

अटल व्योम ism_handle_event(काष्ठा ism_dev *ism)
अणु
	काष्ठा smcd_event *entry;

	जबतक ((ism->ieq_idx + 1) != READ_ONCE(ism->ieq->header.idx)) अणु
		अगर (++(ism->ieq_idx) == ARRAY_SIZE(ism->ieq->entry))
			ism->ieq_idx = 0;

		entry = &ism->ieq->entry[ism->ieq_idx];
		debug_event(ism_debug_info, 2, entry, माप(*entry));
		smcd_handle_event(ism->smcd, entry);
	पूर्ण
पूर्ण

अटल irqवापस_t ism_handle_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा ism_dev *ism = data;
	अचिन्हित दीर्घ bit, end;
	अचिन्हित दीर्घ *bv;

	bv = (व्योम *) &ism->sba->dmb_bits[ISM_DMB_WORD_OFFSET];
	end = माप(ism->sba->dmb_bits) * BITS_PER_BYTE - ISM_DMB_BIT_OFFSET;

	spin_lock(&ism->lock);
	ism->sba->s = 0;
	barrier();
	क्रम (bit = 0;;) अणु
		bit = find_next_bit_inv(bv, end, bit);
		अगर (bit >= end)
			अवरोध;

		clear_bit_inv(bit, bv);
		ism->sba->dmbe_mask[bit + ISM_DMB_BIT_OFFSET] = 0;
		barrier();
		smcd_handle_irq(ism->smcd, bit + ISM_DMB_BIT_OFFSET);
	पूर्ण

	अगर (ism->sba->e) अणु
		ism->sba->e = 0;
		barrier();
		ism_handle_event(ism);
	पूर्ण
	spin_unlock(&ism->lock);
	वापस IRQ_HANDLED;
पूर्ण

अटल स्थिर काष्ठा smcd_ops ism_ops = अणु
	.query_remote_gid = ism_query_rgid,
	.रेजिस्टर_dmb = ism_रेजिस्टर_dmb,
	.unरेजिस्टर_dmb = ism_unरेजिस्टर_dmb,
	.add_vlan_id = ism_add_vlan_id,
	.del_vlan_id = ism_del_vlan_id,
	.set_vlan_required = ism_set_vlan_required,
	.reset_vlan_required = ism_reset_vlan_required,
	.संकेत_event = ism_संकेत_ieq,
	.move_data = ism_move,
	.get_प्रणाली_eid = ism_get_प्रणाली_eid,
	.get_chid = ism_get_chid,
पूर्ण;

अटल पूर्णांक ism_dev_init(काष्ठा ism_dev *ism)
अणु
	काष्ठा pci_dev *pdev = ism->pdev;
	पूर्णांक ret;

	ret = pci_alloc_irq_vectors(pdev, 1, 1, PCI_IRQ_MSI);
	अगर (ret <= 0)
		जाओ out;

	ret = request_irq(pci_irq_vector(pdev, 0), ism_handle_irq, 0,
			  pci_name(pdev), ism);
	अगर (ret)
		जाओ मुक्त_vectors;

	ret = रेजिस्टर_sba(ism);
	अगर (ret)
		जाओ मुक्त_irq;

	ret = रेजिस्टर_ieq(ism);
	अगर (ret)
		जाओ unreg_sba;

	ret = ism_पढ़ो_local_gid(ism);
	अगर (ret)
		जाओ unreg_ieq;

	अगर (!ism_add_vlan_id(ism->smcd, ISM_RESERVED_VLANID))
		/* hardware is V2 capable */
		ism_create_प्रणाली_eid();

	ret = smcd_रेजिस्टर_dev(ism->smcd);
	अगर (ret)
		जाओ unreg_ieq;

	query_info(ism);
	वापस 0;

unreg_ieq:
	unरेजिस्टर_ieq(ism);
unreg_sba:
	unरेजिस्टर_sba(ism);
मुक्त_irq:
	मुक्त_irq(pci_irq_vector(pdev, 0), ism);
मुक्त_vectors:
	pci_मुक्त_irq_vectors(pdev);
out:
	वापस ret;
पूर्ण

अटल पूर्णांक ism_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा ism_dev *ism;
	पूर्णांक ret;

	ism = kzalloc(माप(*ism), GFP_KERNEL);
	अगर (!ism)
		वापस -ENOMEM;

	spin_lock_init(&ism->lock);
	dev_set_drvdata(&pdev->dev, ism);
	ism->pdev = pdev;

	ret = pci_enable_device_mem(pdev);
	अगर (ret)
		जाओ err;

	ret = pci_request_mem_regions(pdev, DRV_NAME);
	अगर (ret)
		जाओ err_disable;

	ret = pci_set_dma_mask(pdev, DMA_BIT_MASK(64));
	अगर (ret)
		जाओ err_resource;

	dma_set_seg_boundary(&pdev->dev, SZ_1M - 1);
	dma_set_max_seg_size(&pdev->dev, SZ_1M);
	pci_set_master(pdev);

	ism->smcd = smcd_alloc_dev(&pdev->dev, dev_name(&pdev->dev), &ism_ops,
				   ISM_NR_DMBS);
	अगर (!ism->smcd) अणु
		ret = -ENOMEM;
		जाओ err_resource;
	पूर्ण

	ism->smcd->priv = ism;
	ret = ism_dev_init(ism);
	अगर (ret)
		जाओ err_मुक्त;

	वापस 0;

err_मुक्त:
	smcd_मुक्त_dev(ism->smcd);
err_resource:
	pci_release_mem_regions(pdev);
err_disable:
	pci_disable_device(pdev);
err:
	kमुक्त(ism);
	dev_set_drvdata(&pdev->dev, शून्य);
	वापस ret;
पूर्ण

अटल व्योम ism_dev_निकास(काष्ठा ism_dev *ism)
अणु
	काष्ठा pci_dev *pdev = ism->pdev;

	smcd_unरेजिस्टर_dev(ism->smcd);
	अगर (SYSTEM_EID.serial_number[0] != '0' ||
	    SYSTEM_EID.type[0] != '0')
		ism_del_vlan_id(ism->smcd, ISM_RESERVED_VLANID);
	unरेजिस्टर_ieq(ism);
	unरेजिस्टर_sba(ism);
	मुक्त_irq(pci_irq_vector(pdev, 0), ism);
	pci_मुक्त_irq_vectors(pdev);
पूर्ण

अटल व्योम ism_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा ism_dev *ism = dev_get_drvdata(&pdev->dev);

	ism_dev_निकास(ism);

	smcd_मुक्त_dev(ism->smcd);
	pci_release_mem_regions(pdev);
	pci_disable_device(pdev);
	dev_set_drvdata(&pdev->dev, शून्य);
	kमुक्त(ism);
पूर्ण

अटल काष्ठा pci_driver ism_driver = अणु
	.name	  = DRV_NAME,
	.id_table = ism_device_table,
	.probe	  = ism_probe,
	.हटाओ	  = ism_हटाओ,
पूर्ण;

अटल पूर्णांक __init ism_init(व्योम)
अणु
	पूर्णांक ret;

	ism_debug_info = debug_रेजिस्टर("ism", 2, 1, 16);
	अगर (!ism_debug_info)
		वापस -ENODEV;

	debug_रेजिस्टर_view(ism_debug_info, &debug_hex_ascii_view);
	ret = pci_रेजिस्टर_driver(&ism_driver);
	अगर (ret)
		debug_unरेजिस्टर(ism_debug_info);

	वापस ret;
पूर्ण

अटल व्योम __निकास ism_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&ism_driver);
	debug_unरेजिस्टर(ism_debug_info);
पूर्ण

module_init(ism_init);
module_निकास(ism_निकास);
