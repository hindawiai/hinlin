<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2011-2014, Intel Corporation.
 * Copyright (c) 2017-2021 Christoph Hellwig.
 */
#समावेश <linux/ptrace.h>	/* क्रम क्रमce_successful_syscall_वापस */
#समावेश <linux/nvme_ioctl.h>
#समावेश "nvme.h"

/*
 * Convert पूर्णांकeger values from ioctl काष्ठाures to user poपूर्णांकers, silently
 * ignoring the upper bits in the compat हाल to match behaviour of 32-bit
 * kernels.
 */
अटल व्योम __user *nvme_to_user_ptr(uपूर्णांकptr_t ptrval)
अणु
	अगर (in_compat_syscall())
		ptrval = (compat_uptr_t)ptrval;
	वापस (व्योम __user *)ptrval;
पूर्ण

अटल व्योम *nvme_add_user_metadata(काष्ठा bio *bio, व्योम __user *ubuf,
		अचिन्हित len, u32 seed, bool ग_लिखो)
अणु
	काष्ठा bio_पूर्णांकegrity_payload *bip;
	पूर्णांक ret = -ENOMEM;
	व्योम *buf;

	buf = kदो_स्मृति(len, GFP_KERNEL);
	अगर (!buf)
		जाओ out;

	ret = -EFAULT;
	अगर (ग_लिखो && copy_from_user(buf, ubuf, len))
		जाओ out_मुक्त_meta;

	bip = bio_पूर्णांकegrity_alloc(bio, GFP_KERNEL, 1);
	अगर (IS_ERR(bip)) अणु
		ret = PTR_ERR(bip);
		जाओ out_मुक्त_meta;
	पूर्ण

	bip->bip_iter.bi_size = len;
	bip->bip_iter.bi_sector = seed;
	ret = bio_पूर्णांकegrity_add_page(bio, virt_to_page(buf), len,
			offset_in_page(buf));
	अगर (ret == len)
		वापस buf;
	ret = -ENOMEM;
out_मुक्त_meta:
	kमुक्त(buf);
out:
	वापस ERR_PTR(ret);
पूर्ण

अटल पूर्णांक nvme_submit_user_cmd(काष्ठा request_queue *q,
		काष्ठा nvme_command *cmd, व्योम __user *ubuffer,
		अचिन्हित bufflen, व्योम __user *meta_buffer, अचिन्हित meta_len,
		u32 meta_seed, u64 *result, अचिन्हित समयout)
अणु
	bool ग_लिखो = nvme_is_ग_लिखो(cmd);
	काष्ठा nvme_ns *ns = q->queuedata;
	काष्ठा block_device *bdev = ns ? ns->disk->part0 : शून्य;
	काष्ठा request *req;
	काष्ठा bio *bio = शून्य;
	व्योम *meta = शून्य;
	पूर्णांक ret;

	req = nvme_alloc_request(q, cmd, 0);
	अगर (IS_ERR(req))
		वापस PTR_ERR(req);

	अगर (समयout)
		req->समयout = समयout;
	nvme_req(req)->flags |= NVME_REQ_USERCMD;

	अगर (ubuffer && bufflen) अणु
		ret = blk_rq_map_user(q, req, शून्य, ubuffer, bufflen,
				GFP_KERNEL);
		अगर (ret)
			जाओ out;
		bio = req->bio;
		अगर (bdev)
			bio_set_dev(bio, bdev);
		अगर (bdev && meta_buffer && meta_len) अणु
			meta = nvme_add_user_metadata(bio, meta_buffer, meta_len,
					meta_seed, ग_लिखो);
			अगर (IS_ERR(meta)) अणु
				ret = PTR_ERR(meta);
				जाओ out_unmap;
			पूर्ण
			req->cmd_flags |= REQ_INTEGRITY;
		पूर्ण
	पूर्ण

	nvme_execute_passthru_rq(req);
	अगर (nvme_req(req)->flags & NVME_REQ_CANCELLED)
		ret = -EINTR;
	अन्यथा
		ret = nvme_req(req)->status;
	अगर (result)
		*result = le64_to_cpu(nvme_req(req)->result.u64);
	अगर (meta && !ret && !ग_लिखो) अणु
		अगर (copy_to_user(meta_buffer, meta, meta_len))
			ret = -EFAULT;
	पूर्ण
	kमुक्त(meta);
 out_unmap:
	अगर (bio)
		blk_rq_unmap_user(bio);
 out:
	blk_mq_मुक्त_request(req);
	वापस ret;
पूर्ण


अटल पूर्णांक nvme_submit_io(काष्ठा nvme_ns *ns, काष्ठा nvme_user_io __user *uio)
अणु
	काष्ठा nvme_user_io io;
	काष्ठा nvme_command c;
	अचिन्हित length, meta_len;
	व्योम __user *metadata;

	अगर (copy_from_user(&io, uio, माप(io)))
		वापस -EFAULT;
	अगर (io.flags)
		वापस -EINVAL;

	चयन (io.opcode) अणु
	हाल nvme_cmd_ग_लिखो:
	हाल nvme_cmd_पढ़ो:
	हाल nvme_cmd_compare:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	length = (io.nblocks + 1) << ns->lba_shअगरt;

	अगर ((io.control & NVME_RW_PRINFO_PRACT) &&
	    ns->ms == माप(काष्ठा t10_pi_tuple)) अणु
		/*
		 * Protection inक्रमmation is stripped/inserted by the
		 * controller.
		 */
		अगर (nvme_to_user_ptr(io.metadata))
			वापस -EINVAL;
		meta_len = 0;
		metadata = शून्य;
	पूर्ण अन्यथा अणु
		meta_len = (io.nblocks + 1) * ns->ms;
		metadata = nvme_to_user_ptr(io.metadata);
	पूर्ण

	अगर (ns->features & NVME_NS_EXT_LBAS) अणु
		length += meta_len;
		meta_len = 0;
	पूर्ण अन्यथा अगर (meta_len) अणु
		अगर ((io.metadata & 3) || !io.metadata)
			वापस -EINVAL;
	पूर्ण

	स_रखो(&c, 0, माप(c));
	c.rw.opcode = io.opcode;
	c.rw.flags = io.flags;
	c.rw.nsid = cpu_to_le32(ns->head->ns_id);
	c.rw.slba = cpu_to_le64(io.slba);
	c.rw.length = cpu_to_le16(io.nblocks);
	c.rw.control = cpu_to_le16(io.control);
	c.rw.dsmgmt = cpu_to_le32(io.dsmgmt);
	c.rw.reftag = cpu_to_le32(io.reftag);
	c.rw.apptag = cpu_to_le16(io.apptag);
	c.rw.appmask = cpu_to_le16(io.appmask);

	वापस nvme_submit_user_cmd(ns->queue, &c,
			nvme_to_user_ptr(io.addr), length,
			metadata, meta_len, lower_32_bits(io.slba), शून्य, 0);
पूर्ण

अटल पूर्णांक nvme_user_cmd(काष्ठा nvme_ctrl *ctrl, काष्ठा nvme_ns *ns,
			काष्ठा nvme_passthru_cmd __user *ucmd)
अणु
	काष्ठा nvme_passthru_cmd cmd;
	काष्ठा nvme_command c;
	अचिन्हित समयout = 0;
	u64 result;
	पूर्णांक status;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EACCES;
	अगर (copy_from_user(&cmd, ucmd, माप(cmd)))
		वापस -EFAULT;
	अगर (cmd.flags)
		वापस -EINVAL;
	अगर (ns && cmd.nsid != ns->head->ns_id) अणु
		dev_err(ctrl->device,
			"%s: nsid (%u) in cmd does not match nsid (%u) of namespace\n",
			current->comm, cmd.nsid, ns->head->ns_id);
		वापस -EINVAL;
	पूर्ण

	स_रखो(&c, 0, माप(c));
	c.common.opcode = cmd.opcode;
	c.common.flags = cmd.flags;
	c.common.nsid = cpu_to_le32(cmd.nsid);
	c.common.cdw2[0] = cpu_to_le32(cmd.cdw2);
	c.common.cdw2[1] = cpu_to_le32(cmd.cdw3);
	c.common.cdw10 = cpu_to_le32(cmd.cdw10);
	c.common.cdw11 = cpu_to_le32(cmd.cdw11);
	c.common.cdw12 = cpu_to_le32(cmd.cdw12);
	c.common.cdw13 = cpu_to_le32(cmd.cdw13);
	c.common.cdw14 = cpu_to_le32(cmd.cdw14);
	c.common.cdw15 = cpu_to_le32(cmd.cdw15);

	अगर (cmd.समयout_ms)
		समयout = msecs_to_jअगरfies(cmd.समयout_ms);

	status = nvme_submit_user_cmd(ns ? ns->queue : ctrl->admin_q, &c,
			nvme_to_user_ptr(cmd.addr), cmd.data_len,
			nvme_to_user_ptr(cmd.metadata), cmd.metadata_len,
			0, &result, समयout);

	अगर (status >= 0) अणु
		अगर (put_user(result, &ucmd->result))
			वापस -EFAULT;
	पूर्ण

	वापस status;
पूर्ण

अटल पूर्णांक nvme_user_cmd64(काष्ठा nvme_ctrl *ctrl, काष्ठा nvme_ns *ns,
			काष्ठा nvme_passthru_cmd64 __user *ucmd)
अणु
	काष्ठा nvme_passthru_cmd64 cmd;
	काष्ठा nvme_command c;
	अचिन्हित समयout = 0;
	पूर्णांक status;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EACCES;
	अगर (copy_from_user(&cmd, ucmd, माप(cmd)))
		वापस -EFAULT;
	अगर (cmd.flags)
		वापस -EINVAL;
	अगर (ns && cmd.nsid != ns->head->ns_id) अणु
		dev_err(ctrl->device,
			"%s: nsid (%u) in cmd does not match nsid (%u) of namespace\n",
			current->comm, cmd.nsid, ns->head->ns_id);
		वापस -EINVAL;
	पूर्ण

	स_रखो(&c, 0, माप(c));
	c.common.opcode = cmd.opcode;
	c.common.flags = cmd.flags;
	c.common.nsid = cpu_to_le32(cmd.nsid);
	c.common.cdw2[0] = cpu_to_le32(cmd.cdw2);
	c.common.cdw2[1] = cpu_to_le32(cmd.cdw3);
	c.common.cdw10 = cpu_to_le32(cmd.cdw10);
	c.common.cdw11 = cpu_to_le32(cmd.cdw11);
	c.common.cdw12 = cpu_to_le32(cmd.cdw12);
	c.common.cdw13 = cpu_to_le32(cmd.cdw13);
	c.common.cdw14 = cpu_to_le32(cmd.cdw14);
	c.common.cdw15 = cpu_to_le32(cmd.cdw15);

	अगर (cmd.समयout_ms)
		समयout = msecs_to_jअगरfies(cmd.समयout_ms);

	status = nvme_submit_user_cmd(ns ? ns->queue : ctrl->admin_q, &c,
			nvme_to_user_ptr(cmd.addr), cmd.data_len,
			nvme_to_user_ptr(cmd.metadata), cmd.metadata_len,
			0, &cmd.result, समयout);

	अगर (status >= 0) अणु
		अगर (put_user(cmd.result, &ucmd->result))
			वापस -EFAULT;
	पूर्ण

	वापस status;
पूर्ण

अटल bool is_ctrl_ioctl(अचिन्हित पूर्णांक cmd)
अणु
	अगर (cmd == NVME_IOCTL_ADMIN_CMD || cmd == NVME_IOCTL_ADMIN64_CMD)
		वापस true;
	अगर (is_sed_ioctl(cmd))
		वापस true;
	वापस false;
पूर्ण

अटल पूर्णांक nvme_ctrl_ioctl(काष्ठा nvme_ctrl *ctrl, अचिन्हित पूर्णांक cmd,
		व्योम __user *argp)
अणु
	चयन (cmd) अणु
	हाल NVME_IOCTL_ADMIN_CMD:
		वापस nvme_user_cmd(ctrl, शून्य, argp);
	हाल NVME_IOCTL_ADMIN64_CMD:
		वापस nvme_user_cmd64(ctrl, शून्य, argp);
	शेष:
		वापस sed_ioctl(ctrl->opal_dev, cmd, argp);
	पूर्ण
पूर्ण

#अगर_घोषित COMPAT_FOR_U64_ALIGNMENT
काष्ठा nvme_user_io32 अणु
	__u8	opcode;
	__u8	flags;
	__u16	control;
	__u16	nblocks;
	__u16	rsvd;
	__u64	metadata;
	__u64	addr;
	__u64	slba;
	__u32	dsmgmt;
	__u32	reftag;
	__u16	apptag;
	__u16	appmask;
पूर्ण __attribute__((__packed__));
#घोषणा NVME_IOCTL_SUBMIT_IO32	_IOW('N', 0x42, काष्ठा nvme_user_io32)
#पूर्ण_अगर /* COMPAT_FOR_U64_ALIGNMENT */

अटल पूर्णांक nvme_ns_ioctl(काष्ठा nvme_ns *ns, अचिन्हित पूर्णांक cmd,
		व्योम __user *argp)
अणु
	चयन (cmd) अणु
	हाल NVME_IOCTL_ID:
		क्रमce_successful_syscall_वापस();
		वापस ns->head->ns_id;
	हाल NVME_IOCTL_IO_CMD:
		वापस nvme_user_cmd(ns->ctrl, ns, argp);
	/*
	 * काष्ठा nvme_user_io can have dअगरferent padding on some 32-bit ABIs.
	 * Just accept the compat version as all fields that are used are the
	 * same size and at the same offset.
	 */
#अगर_घोषित COMPAT_FOR_U64_ALIGNMENT
	हाल NVME_IOCTL_SUBMIT_IO32:
#पूर्ण_अगर
	हाल NVME_IOCTL_SUBMIT_IO:
		वापस nvme_submit_io(ns, argp);
	हाल NVME_IOCTL_IO64_CMD:
		वापस nvme_user_cmd64(ns->ctrl, ns, argp);
	शेष:
		अगर (!ns->ndev)
			वापस -ENOTTY;
		वापस nvme_nvm_ioctl(ns, cmd, argp);
	पूर्ण
पूर्ण

अटल पूर्णांक __nvme_ioctl(काष्ठा nvme_ns *ns, अचिन्हित पूर्णांक cmd, व्योम __user *arg)
अणु
       अगर (is_ctrl_ioctl(cmd))
               वापस nvme_ctrl_ioctl(ns->ctrl, cmd, arg);
       वापस nvme_ns_ioctl(ns, cmd, arg);
पूर्ण

पूर्णांक nvme_ioctl(काष्ठा block_device *bdev, भ_शेषe_t mode,
		अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा nvme_ns *ns = bdev->bd_disk->निजी_data;

	वापस __nvme_ioctl(ns, cmd, (व्योम __user *)arg);
पूर्ण

दीर्घ nvme_ns_chr_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा nvme_ns *ns =
		container_of(file_inode(file)->i_cdev, काष्ठा nvme_ns, cdev);

	वापस __nvme_ioctl(ns, cmd, (व्योम __user *)arg);
पूर्ण

#अगर_घोषित CONFIG_NVME_MULTIPATH
अटल पूर्णांक nvme_ns_head_ctrl_ioctl(काष्ठा nvme_ns *ns, अचिन्हित पूर्णांक cmd,
		व्योम __user *argp, काष्ठा nvme_ns_head *head, पूर्णांक srcu_idx)
अणु
	काष्ठा nvme_ctrl *ctrl = ns->ctrl;
	पूर्णांक ret;

	nvme_get_ctrl(ns->ctrl);
	nvme_put_ns_from_disk(head, srcu_idx);
	ret = nvme_ctrl_ioctl(ns->ctrl, cmd, argp);

	nvme_put_ctrl(ctrl);
	वापस ret;
पूर्ण

पूर्णांक nvme_ns_head_ioctl(काष्ठा block_device *bdev, भ_शेषe_t mode,
		अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा nvme_ns_head *head = शून्य;
	व्योम __user *argp = (व्योम __user *)arg;
	काष्ठा nvme_ns *ns;
	पूर्णांक srcu_idx, ret;

	ns = nvme_get_ns_from_disk(bdev->bd_disk, &head, &srcu_idx);
	अगर (unlikely(!ns))
		वापस -EWOULDBLOCK;

	/*
	 * Handle ioctls that apply to the controller instead of the namespace
	 * seperately and drop the ns SRCU reference early.  This aव्योमs a
	 * deadlock when deleting namespaces using the passthrough पूर्णांकerface.
	 */
	अगर (is_ctrl_ioctl(cmd))
		ret = nvme_ns_head_ctrl_ioctl(ns, cmd, argp, head, srcu_idx);
	अन्यथा अणु
		ret = nvme_ns_ioctl(ns, cmd, argp);
		nvme_put_ns_from_disk(head, srcu_idx);
	पूर्ण

	वापस ret;
पूर्ण

दीर्घ nvme_ns_head_chr_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
		अचिन्हित दीर्घ arg)
अणु
	काष्ठा cdev *cdev = file_inode(file)->i_cdev;
	काष्ठा nvme_ns_head *head =
		container_of(cdev, काष्ठा nvme_ns_head, cdev);
	व्योम __user *argp = (व्योम __user *)arg;
	काष्ठा nvme_ns *ns;
	पूर्णांक srcu_idx, ret;

	srcu_idx = srcu_पढ़ो_lock(&head->srcu);
	ns = nvme_find_path(head);
	अगर (!ns) अणु
		srcu_पढ़ो_unlock(&head->srcu, srcu_idx);
		वापस -EWOULDBLOCK;
	पूर्ण

	अगर (is_ctrl_ioctl(cmd))
		वापस nvme_ns_head_ctrl_ioctl(ns, cmd, argp, head, srcu_idx);

	ret = nvme_ns_ioctl(ns, cmd, argp);
	nvme_put_ns_from_disk(head, srcu_idx);

	वापस ret;
पूर्ण
#पूर्ण_अगर /* CONFIG_NVME_MULTIPATH */

अटल पूर्णांक nvme_dev_user_cmd(काष्ठा nvme_ctrl *ctrl, व्योम __user *argp)
अणु
	काष्ठा nvme_ns *ns;
	पूर्णांक ret;

	करोwn_पढ़ो(&ctrl->namespaces_rwsem);
	अगर (list_empty(&ctrl->namespaces)) अणु
		ret = -ENOTTY;
		जाओ out_unlock;
	पूर्ण

	ns = list_first_entry(&ctrl->namespaces, काष्ठा nvme_ns, list);
	अगर (ns != list_last_entry(&ctrl->namespaces, काष्ठा nvme_ns, list)) अणु
		dev_warn(ctrl->device,
			"NVME_IOCTL_IO_CMD not supported when multiple namespaces present!\n");
		ret = -EINVAL;
		जाओ out_unlock;
	पूर्ण

	dev_warn(ctrl->device,
		"using deprecated NVME_IOCTL_IO_CMD ioctl on the char device!\n");
	kref_get(&ns->kref);
	up_पढ़ो(&ctrl->namespaces_rwsem);

	ret = nvme_user_cmd(ctrl, ns, argp);
	nvme_put_ns(ns);
	वापस ret;

out_unlock:
	up_पढ़ो(&ctrl->namespaces_rwsem);
	वापस ret;
पूर्ण

दीर्घ nvme_dev_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
		अचिन्हित दीर्घ arg)
अणु
	काष्ठा nvme_ctrl *ctrl = file->निजी_data;
	व्योम __user *argp = (व्योम __user *)arg;

	चयन (cmd) अणु
	हाल NVME_IOCTL_ADMIN_CMD:
		वापस nvme_user_cmd(ctrl, शून्य, argp);
	हाल NVME_IOCTL_ADMIN64_CMD:
		वापस nvme_user_cmd64(ctrl, शून्य, argp);
	हाल NVME_IOCTL_IO_CMD:
		वापस nvme_dev_user_cmd(ctrl, argp);
	हाल NVME_IOCTL_RESET:
		dev_warn(ctrl->device, "resetting controller\n");
		वापस nvme_reset_ctrl_sync(ctrl);
	हाल NVME_IOCTL_SUBSYS_RESET:
		वापस nvme_reset_subप्रणाली(ctrl);
	हाल NVME_IOCTL_RESCAN:
		nvme_queue_scan(ctrl);
		वापस 0;
	शेष:
		वापस -ENOTTY;
	पूर्ण
पूर्ण
