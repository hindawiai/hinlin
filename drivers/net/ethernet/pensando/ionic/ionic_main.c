<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2017 - 2019 Pensanकरो Systems, Inc */

#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/dynamic_debug.h>
#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/utsname.h>
#समावेश <generated/utsrelease.h>

#समावेश "ionic.h"
#समावेश "ionic_bus.h"
#समावेश "ionic_lif.h"
#समावेश "ionic_debugfs.h"

MODULE_DESCRIPTION(IONIC_DRV_DESCRIPTION);
MODULE_AUTHOR("Pensando Systems, Inc");
MODULE_LICENSE("GPL");

अटल स्थिर अक्षर *ionic_error_to_str(क्रमागत ionic_status_code code)
अणु
	चयन (code) अणु
	हाल IONIC_RC_SUCCESS:
		वापस "IONIC_RC_SUCCESS";
	हाल IONIC_RC_EVERSION:
		वापस "IONIC_RC_EVERSION";
	हाल IONIC_RC_EOPCODE:
		वापस "IONIC_RC_EOPCODE";
	हाल IONIC_RC_EIO:
		वापस "IONIC_RC_EIO";
	हाल IONIC_RC_EPERM:
		वापस "IONIC_RC_EPERM";
	हाल IONIC_RC_EQID:
		वापस "IONIC_RC_EQID";
	हाल IONIC_RC_EQTYPE:
		वापस "IONIC_RC_EQTYPE";
	हाल IONIC_RC_ENOENT:
		वापस "IONIC_RC_ENOENT";
	हाल IONIC_RC_EINTR:
		वापस "IONIC_RC_EINTR";
	हाल IONIC_RC_EAGAIN:
		वापस "IONIC_RC_EAGAIN";
	हाल IONIC_RC_ENOMEM:
		वापस "IONIC_RC_ENOMEM";
	हाल IONIC_RC_EFAULT:
		वापस "IONIC_RC_EFAULT";
	हाल IONIC_RC_EBUSY:
		वापस "IONIC_RC_EBUSY";
	हाल IONIC_RC_EEXIST:
		वापस "IONIC_RC_EEXIST";
	हाल IONIC_RC_EINVAL:
		वापस "IONIC_RC_EINVAL";
	हाल IONIC_RC_ENOSPC:
		वापस "IONIC_RC_ENOSPC";
	हाल IONIC_RC_दुस्फल:
		वापस "IONIC_RC_ERANGE";
	हाल IONIC_RC_BAD_ADDR:
		वापस "IONIC_RC_BAD_ADDR";
	हाल IONIC_RC_DEV_CMD:
		वापस "IONIC_RC_DEV_CMD";
	हाल IONIC_RC_ENOSUPP:
		वापस "IONIC_RC_ENOSUPP";
	हाल IONIC_RC_ERROR:
		वापस "IONIC_RC_ERROR";
	हाल IONIC_RC_ERDMA:
		वापस "IONIC_RC_ERDMA";
	हाल IONIC_RC_EBAD_FW:
		वापस "IONIC_RC_EBAD_FW";
	शेष:
		वापस "IONIC_RC_UNKNOWN";
	पूर्ण
पूर्ण

अटल पूर्णांक ionic_error_to_त्रुटि_सं(क्रमागत ionic_status_code code)
अणु
	चयन (code) अणु
	हाल IONIC_RC_SUCCESS:
		वापस 0;
	हाल IONIC_RC_EVERSION:
	हाल IONIC_RC_EQTYPE:
	हाल IONIC_RC_EQID:
	हाल IONIC_RC_EINVAL:
	हाल IONIC_RC_ENOSUPP:
		वापस -EINVAL;
	हाल IONIC_RC_EPERM:
		वापस -EPERM;
	हाल IONIC_RC_ENOENT:
		वापस -ENOENT;
	हाल IONIC_RC_EAGAIN:
		वापस -EAGAIN;
	हाल IONIC_RC_ENOMEM:
		वापस -ENOMEM;
	हाल IONIC_RC_EFAULT:
		वापस -EFAULT;
	हाल IONIC_RC_EBUSY:
		वापस -EBUSY;
	हाल IONIC_RC_EEXIST:
		वापस -EEXIST;
	हाल IONIC_RC_ENOSPC:
		वापस -ENOSPC;
	हाल IONIC_RC_दुस्फल:
		वापस -दुस्फल;
	हाल IONIC_RC_BAD_ADDR:
		वापस -EFAULT;
	हाल IONIC_RC_EOPCODE:
	हाल IONIC_RC_EINTR:
	हाल IONIC_RC_DEV_CMD:
	हाल IONIC_RC_ERROR:
	हाल IONIC_RC_ERDMA:
	हाल IONIC_RC_EIO:
	शेष:
		वापस -EIO;
	पूर्ण
पूर्ण

अटल स्थिर अक्षर *ionic_opcode_to_str(क्रमागत ionic_cmd_opcode opcode)
अणु
	चयन (opcode) अणु
	हाल IONIC_CMD_NOP:
		वापस "IONIC_CMD_NOP";
	हाल IONIC_CMD_INIT:
		वापस "IONIC_CMD_INIT";
	हाल IONIC_CMD_RESET:
		वापस "IONIC_CMD_RESET";
	हाल IONIC_CMD_IDENTIFY:
		वापस "IONIC_CMD_IDENTIFY";
	हाल IONIC_CMD_GETATTR:
		वापस "IONIC_CMD_GETATTR";
	हाल IONIC_CMD_SETATTR:
		वापस "IONIC_CMD_SETATTR";
	हाल IONIC_CMD_PORT_IDENTIFY:
		वापस "IONIC_CMD_PORT_IDENTIFY";
	हाल IONIC_CMD_PORT_INIT:
		वापस "IONIC_CMD_PORT_INIT";
	हाल IONIC_CMD_PORT_RESET:
		वापस "IONIC_CMD_PORT_RESET";
	हाल IONIC_CMD_PORT_GETATTR:
		वापस "IONIC_CMD_PORT_GETATTR";
	हाल IONIC_CMD_PORT_SETATTR:
		वापस "IONIC_CMD_PORT_SETATTR";
	हाल IONIC_CMD_LIF_INIT:
		वापस "IONIC_CMD_LIF_INIT";
	हाल IONIC_CMD_LIF_RESET:
		वापस "IONIC_CMD_LIF_RESET";
	हाल IONIC_CMD_LIF_IDENTIFY:
		वापस "IONIC_CMD_LIF_IDENTIFY";
	हाल IONIC_CMD_LIF_SETATTR:
		वापस "IONIC_CMD_LIF_SETATTR";
	हाल IONIC_CMD_LIF_GETATTR:
		वापस "IONIC_CMD_LIF_GETATTR";
	हाल IONIC_CMD_LIF_SETPHC:
		वापस "IONIC_CMD_LIF_SETPHC";
	हाल IONIC_CMD_RX_MODE_SET:
		वापस "IONIC_CMD_RX_MODE_SET";
	हाल IONIC_CMD_RX_FILTER_ADD:
		वापस "IONIC_CMD_RX_FILTER_ADD";
	हाल IONIC_CMD_RX_FILTER_DEL:
		वापस "IONIC_CMD_RX_FILTER_DEL";
	हाल IONIC_CMD_Q_IDENTIFY:
		वापस "IONIC_CMD_Q_IDENTIFY";
	हाल IONIC_CMD_Q_INIT:
		वापस "IONIC_CMD_Q_INIT";
	हाल IONIC_CMD_Q_CONTROL:
		वापस "IONIC_CMD_Q_CONTROL";
	हाल IONIC_CMD_RDMA_RESET_LIF:
		वापस "IONIC_CMD_RDMA_RESET_LIF";
	हाल IONIC_CMD_RDMA_CREATE_EQ:
		वापस "IONIC_CMD_RDMA_CREATE_EQ";
	हाल IONIC_CMD_RDMA_CREATE_CQ:
		वापस "IONIC_CMD_RDMA_CREATE_CQ";
	हाल IONIC_CMD_RDMA_CREATE_ADMINQ:
		वापस "IONIC_CMD_RDMA_CREATE_ADMINQ";
	हाल IONIC_CMD_FW_DOWNLOAD:
		वापस "IONIC_CMD_FW_DOWNLOAD";
	हाल IONIC_CMD_FW_CONTROL:
		वापस "IONIC_CMD_FW_CONTROL";
	हाल IONIC_CMD_FW_DOWNLOAD_V1:
		वापस "IONIC_CMD_FW_DOWNLOAD_V1";
	हाल IONIC_CMD_FW_CONTROL_V1:
		वापस "IONIC_CMD_FW_CONTROL_V1";
	हाल IONIC_CMD_VF_GETATTR:
		वापस "IONIC_CMD_VF_GETATTR";
	हाल IONIC_CMD_VF_SETATTR:
		वापस "IONIC_CMD_VF_SETATTR";
	शेष:
		वापस "DEVCMD_UNKNOWN";
	पूर्ण
पूर्ण

अटल व्योम ionic_adminq_flush(काष्ठा ionic_lअगर *lअगर)
अणु
	काष्ठा ionic_desc_info *desc_info;
	अचिन्हित दीर्घ irqflags;
	काष्ठा ionic_queue *q;

	spin_lock_irqsave(&lअगर->adminq_lock, irqflags);
	अगर (!lअगर->adminqcq) अणु
		spin_unlock_irqrestore(&lअगर->adminq_lock, irqflags);
		वापस;
	पूर्ण

	q = &lअगर->adminqcq->q;

	जबतक (q->tail_idx != q->head_idx) अणु
		desc_info = &q->info[q->tail_idx];
		स_रखो(desc_info->desc, 0, माप(जोड़ ionic_adminq_cmd));
		desc_info->cb = शून्य;
		desc_info->cb_arg = शून्य;
		q->tail_idx = (q->tail_idx + 1) & (q->num_descs - 1);
	पूर्ण
	spin_unlock_irqrestore(&lअगर->adminq_lock, irqflags);
पूर्ण

अटल पूर्णांक ionic_adminq_check_err(काष्ठा ionic_lअगर *lअगर,
				  काष्ठा ionic_admin_ctx *ctx,
				  bool समयout)
अणु
	काष्ठा net_device *netdev = lअगर->netdev;
	स्थिर अक्षर *opcode_str;
	स्थिर अक्षर *status_str;
	पूर्णांक err = 0;

	अगर (ctx->comp.comp.status || समयout) अणु
		opcode_str = ionic_opcode_to_str(ctx->cmd.cmd.opcode);
		status_str = ionic_error_to_str(ctx->comp.comp.status);
		err = समयout ? -ETIMEDOUT :
				ionic_error_to_त्रुटि_सं(ctx->comp.comp.status);

		netdev_err(netdev, "%s (%d) failed: %s (%d)\n",
			   opcode_str, ctx->cmd.cmd.opcode,
			   समयout ? "TIMEOUT" : status_str, err);

		अगर (समयout)
			ionic_adminq_flush(lअगर);
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम ionic_adminq_cb(काष्ठा ionic_queue *q,
			    काष्ठा ionic_desc_info *desc_info,
			    काष्ठा ionic_cq_info *cq_info, व्योम *cb_arg)
अणु
	काष्ठा ionic_admin_ctx *ctx = cb_arg;
	काष्ठा ionic_admin_comp *comp;

	अगर (!ctx)
		वापस;

	comp = cq_info->cq_desc;

	स_नकल(&ctx->comp, comp, माप(*comp));

	dev_dbg(q->dev, "comp admin queue command:\n");
	dynamic_hex_dump("comp ", DUMP_PREFIX_OFFSET, 16, 1,
			 &ctx->comp, माप(ctx->comp), true);

	complete_all(&ctx->work);
पूर्ण

पूर्णांक ionic_adminq_post(काष्ठा ionic_lअगर *lअगर, काष्ठा ionic_admin_ctx *ctx)
अणु
	काष्ठा ionic_desc_info *desc_info;
	अचिन्हित दीर्घ irqflags;
	काष्ठा ionic_queue *q;
	पूर्णांक err = 0;

	spin_lock_irqsave(&lअगर->adminq_lock, irqflags);
	अगर (!lअगर->adminqcq) अणु
		spin_unlock_irqrestore(&lअगर->adminq_lock, irqflags);
		वापस -EIO;
	पूर्ण

	q = &lअगर->adminqcq->q;

	अगर (!ionic_q_has_space(q, 1)) अणु
		err = -ENOSPC;
		जाओ err_out;
	पूर्ण

	err = ionic_heartbeat_check(lअगर->ionic);
	अगर (err)
		जाओ err_out;

	desc_info = &q->info[q->head_idx];
	स_नकल(desc_info->desc, &ctx->cmd, माप(ctx->cmd));

	dev_dbg(&lअगर->netdev->dev, "post admin queue command:\n");
	dynamic_hex_dump("cmd ", DUMP_PREFIX_OFFSET, 16, 1,
			 &ctx->cmd, माप(ctx->cmd), true);

	ionic_q_post(q, true, ionic_adminq_cb, ctx);

err_out:
	spin_unlock_irqrestore(&lअगर->adminq_lock, irqflags);

	वापस err;
पूर्ण

पूर्णांक ionic_adminq_रुको(काष्ठा ionic_lअगर *lअगर, काष्ठा ionic_admin_ctx *ctx, पूर्णांक err)
अणु
	काष्ठा net_device *netdev = lअगर->netdev;
	अचिन्हित दीर्घ reमुख्यing;
	स्थिर अक्षर *name;

	अगर (err) अणु
		अगर (!test_bit(IONIC_LIF_F_FW_RESET, lअगर->state)) अणु
			name = ionic_opcode_to_str(ctx->cmd.cmd.opcode);
			netdev_err(netdev, "Posting of %s (%d) failed: %d\n",
				   name, ctx->cmd.cmd.opcode, err);
		पूर्ण
		वापस err;
	पूर्ण

	reमुख्यing = रुको_क्रम_completion_समयout(&ctx->work,
						HZ * (uदीर्घ)DEVCMD_TIMEOUT);
	वापस ionic_adminq_check_err(lअगर, ctx, (reमुख्यing == 0));
पूर्ण

पूर्णांक ionic_adminq_post_रुको(काष्ठा ionic_lअगर *lअगर, काष्ठा ionic_admin_ctx *ctx)
अणु
	पूर्णांक err;

	err = ionic_adminq_post(lअगर, ctx);

	वापस ionic_adminq_रुको(lअगर, ctx, err);
पूर्ण

अटल व्योम ionic_dev_cmd_clean(काष्ठा ionic *ionic)
अणु
	जोड़ __iomem ionic_dev_cmd_regs *regs = ionic->idev.dev_cmd_regs;

	ioग_लिखो32(0, &regs->करोorbell);
	स_रखो_io(&regs->cmd, 0, माप(regs->cmd));
पूर्ण

पूर्णांक ionic_dev_cmd_रुको(काष्ठा ionic *ionic, अचिन्हित दीर्घ max_seconds)
अणु
	काष्ठा ionic_dev *idev = &ionic->idev;
	अचिन्हित दीर्घ start_समय;
	अचिन्हित दीर्घ max_रुको;
	अचिन्हित दीर्घ duration;
	पूर्णांक opcode;
	पूर्णांक hb = 0;
	पूर्णांक करोne;
	पूर्णांक err;

	/* Wait क्रम dev cmd to complete, retrying अगर we get EAGAIN,
	 * but करोn't रुको any दीर्घer than max_seconds.
	 */
	max_रुको = jअगरfies + (max_seconds * HZ);
try_again:
	opcode = पढ़ोb(&idev->dev_cmd_regs->cmd.cmd.opcode);
	start_समय = jअगरfies;
	करो अणु
		करोne = ionic_dev_cmd_करोne(idev);
		अगर (करोne)
			अवरोध;
		usleep_range(100, 200);

		/* Don't check the heartbeat on FW_CONTROL commands as they are
		 * notorious क्रम पूर्णांकerrupting the firmware's heartbeat update.
		 */
		अगर (opcode != IONIC_CMD_FW_CONTROL)
			hb = ionic_heartbeat_check(ionic);
	पूर्ण जबतक (!करोne && !hb && समय_beक्रमe(jअगरfies, max_रुको));
	duration = jअगरfies - start_समय;

	dev_dbg(ionic->dev, "DEVCMD %s (%d) done=%d took %ld secs (%ld jiffies)\n",
		ionic_opcode_to_str(opcode), opcode,
		करोne, duration / HZ, duration);

	अगर (!करोne && hb) अणु
		/* It is possible (but unlikely) that FW was busy and missed a
		 * heartbeat check but is still alive and will process this
		 * request, so करोn't clean the dev_cmd in this हाल.
		 */
		dev_warn(ionic->dev, "DEVCMD %s (%d) failed - FW halted\n",
			 ionic_opcode_to_str(opcode), opcode);
		वापस -ENXIO;
	पूर्ण

	अगर (!करोne && !समय_beक्रमe(jअगरfies, max_रुको)) अणु
		ionic_dev_cmd_clean(ionic);
		dev_warn(ionic->dev, "DEVCMD %s (%d) timeout after %ld secs\n",
			 ionic_opcode_to_str(opcode), opcode, max_seconds);
		वापस -ETIMEDOUT;
	पूर्ण

	err = ionic_dev_cmd_status(&ionic->idev);
	अगर (err) अणु
		अगर (err == IONIC_RC_EAGAIN &&
		    समय_beक्रमe(jअगरfies, (max_रुको - HZ))) अणु
			dev_dbg(ionic->dev, "DEV_CMD %s (%d), %s (%d) retrying...\n",
				ionic_opcode_to_str(opcode), opcode,
				ionic_error_to_str(err), err);

			msleep(1000);
			ioग_लिखो32(0, &idev->dev_cmd_regs->करोne);
			ioग_लिखो32(1, &idev->dev_cmd_regs->करोorbell);
			जाओ try_again;
		पूर्ण

		अगर (!(opcode == IONIC_CMD_FW_CONTROL && err == IONIC_RC_EAGAIN))
			dev_err(ionic->dev, "DEV_CMD %s (%d) error, %s (%d) failed\n",
				ionic_opcode_to_str(opcode), opcode,
				ionic_error_to_str(err), err);

		वापस ionic_error_to_त्रुटि_सं(err);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक ionic_setup(काष्ठा ionic *ionic)
अणु
	पूर्णांक err;

	err = ionic_dev_setup(ionic);
	अगर (err)
		वापस err;
	ionic_reset(ionic);

	वापस 0;
पूर्ण

पूर्णांक ionic_identअगरy(काष्ठा ionic *ionic)
अणु
	काष्ठा ionic_identity *ident = &ionic->ident;
	काष्ठा ionic_dev *idev = &ionic->idev;
	माप_प्रकार sz;
	पूर्णांक err;

	स_रखो(ident, 0, माप(*ident));

	ident->drv.os_type = cpu_to_le32(IONIC_OS_TYPE_LINUX);
	म_नकलन(ident->drv.driver_ver_str, UTS_RELEASE,
		माप(ident->drv.driver_ver_str) - 1);

	mutex_lock(&ionic->dev_cmd_lock);

	sz = min(माप(ident->drv), माप(idev->dev_cmd_regs->data));
	स_नकल_toio(&idev->dev_cmd_regs->data, &ident->drv, sz);

	ionic_dev_cmd_identअगरy(idev, IONIC_IDENTITY_VERSION_1);
	err = ionic_dev_cmd_रुको(ionic, DEVCMD_TIMEOUT);
	अगर (!err) अणु
		sz = min(माप(ident->dev), माप(idev->dev_cmd_regs->data));
		स_नकल_fromio(&ident->dev, &idev->dev_cmd_regs->data, sz);
	पूर्ण
	mutex_unlock(&ionic->dev_cmd_lock);

	अगर (err) अणु
		dev_err(ionic->dev, "Cannot identify ionic: %dn", err);
		जाओ err_out;
	पूर्ण

	err = ionic_lअगर_identअगरy(ionic, IONIC_LIF_TYPE_CLASSIC,
				 &ionic->ident.lअगर);
	अगर (err) अणु
		dev_err(ionic->dev, "Cannot identify LIFs: %d\n", err);
		जाओ err_out;
	पूर्ण

	वापस 0;

err_out:
	वापस err;
पूर्ण

पूर्णांक ionic_init(काष्ठा ionic *ionic)
अणु
	काष्ठा ionic_dev *idev = &ionic->idev;
	पूर्णांक err;

	mutex_lock(&ionic->dev_cmd_lock);
	ionic_dev_cmd_init(idev);
	err = ionic_dev_cmd_रुको(ionic, DEVCMD_TIMEOUT);
	mutex_unlock(&ionic->dev_cmd_lock);

	वापस err;
पूर्ण

पूर्णांक ionic_reset(काष्ठा ionic *ionic)
अणु
	काष्ठा ionic_dev *idev = &ionic->idev;
	पूर्णांक err;

	mutex_lock(&ionic->dev_cmd_lock);
	ionic_dev_cmd_reset(idev);
	err = ionic_dev_cmd_रुको(ionic, DEVCMD_TIMEOUT);
	mutex_unlock(&ionic->dev_cmd_lock);

	वापस err;
पूर्ण

पूर्णांक ionic_port_identअगरy(काष्ठा ionic *ionic)
अणु
	काष्ठा ionic_identity *ident = &ionic->ident;
	काष्ठा ionic_dev *idev = &ionic->idev;
	माप_प्रकार sz;
	पूर्णांक err;

	mutex_lock(&ionic->dev_cmd_lock);

	ionic_dev_cmd_port_identअगरy(idev);
	err = ionic_dev_cmd_रुको(ionic, DEVCMD_TIMEOUT);
	अगर (!err) अणु
		sz = min(माप(ident->port), माप(idev->dev_cmd_regs->data));
		स_नकल_fromio(&ident->port, &idev->dev_cmd_regs->data, sz);
	पूर्ण

	mutex_unlock(&ionic->dev_cmd_lock);

	वापस err;
पूर्ण

पूर्णांक ionic_port_init(काष्ठा ionic *ionic)
अणु
	काष्ठा ionic_identity *ident = &ionic->ident;
	काष्ठा ionic_dev *idev = &ionic->idev;
	माप_प्रकार sz;
	पूर्णांक err;

	अगर (!idev->port_info) अणु
		idev->port_info_sz = ALIGN(माप(*idev->port_info), PAGE_SIZE);
		idev->port_info = dma_alloc_coherent(ionic->dev,
						     idev->port_info_sz,
						     &idev->port_info_pa,
						     GFP_KERNEL);
		अगर (!idev->port_info)
			वापस -ENOMEM;
	पूर्ण

	sz = min(माप(ident->port.config), माप(idev->dev_cmd_regs->data));

	mutex_lock(&ionic->dev_cmd_lock);

	स_नकल_toio(&idev->dev_cmd_regs->data, &ident->port.config, sz);
	ionic_dev_cmd_port_init(idev);
	err = ionic_dev_cmd_रुको(ionic, DEVCMD_TIMEOUT);

	ionic_dev_cmd_port_state(&ionic->idev, IONIC_PORT_ADMIN_STATE_UP);
	(व्योम)ionic_dev_cmd_रुको(ionic, DEVCMD_TIMEOUT);

	mutex_unlock(&ionic->dev_cmd_lock);
	अगर (err) अणु
		dev_err(ionic->dev, "Failed to init port\n");
		dma_मुक्त_coherent(ionic->dev, idev->port_info_sz,
				  idev->port_info, idev->port_info_pa);
		idev->port_info = शून्य;
		idev->port_info_pa = 0;
	पूर्ण

	वापस err;
पूर्ण

पूर्णांक ionic_port_reset(काष्ठा ionic *ionic)
अणु
	काष्ठा ionic_dev *idev = &ionic->idev;
	पूर्णांक err;

	अगर (!idev->port_info)
		वापस 0;

	mutex_lock(&ionic->dev_cmd_lock);
	ionic_dev_cmd_port_reset(idev);
	err = ionic_dev_cmd_रुको(ionic, DEVCMD_TIMEOUT);
	mutex_unlock(&ionic->dev_cmd_lock);

	dma_मुक्त_coherent(ionic->dev, idev->port_info_sz,
			  idev->port_info, idev->port_info_pa);

	idev->port_info = शून्य;
	idev->port_info_pa = 0;

	अगर (err)
		dev_err(ionic->dev, "Failed to reset port\n");

	वापस err;
पूर्ण

अटल पूर्णांक __init ionic_init_module(व्योम)
अणु
	ionic_debugfs_create();
	वापस ionic_bus_रेजिस्टर_driver();
पूर्ण

अटल व्योम __निकास ionic_cleanup_module(व्योम)
अणु
	ionic_bus_unरेजिस्टर_driver();
	ionic_debugfs_destroy();

	pr_info("%s removed\n", IONIC_DRV_NAME);
पूर्ण

module_init(ionic_init_module);
module_निकास(ionic_cleanup_module);
