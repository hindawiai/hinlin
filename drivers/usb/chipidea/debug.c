<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/kernel.h>
#समावेश <linux/device.h>
#समावेश <linux/types.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/usb/ch9.h>
#समावेश <linux/usb/gadget.h>
#समावेश <linux/usb/phy.h>
#समावेश <linux/usb/otg.h>
#समावेश <linux/usb/otg-fsm.h>
#समावेश <linux/usb/chipidea.h>

#समावेश "ci.h"
#समावेश "udc.h"
#समावेश "bits.h"
#समावेश "otg.h"

/*
 * ci_device_show: prपूर्णांकs inक्रमmation about device capabilities and status
 */
अटल पूर्णांक ci_device_show(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा ci_hdrc *ci = s->निजी;
	काष्ठा usb_gadget *gadget = &ci->gadget;

	seq_म_लिखो(s, "speed             = %d\n", gadget->speed);
	seq_म_लिखो(s, "max_speed         = %d\n", gadget->max_speed);
	seq_म_लिखो(s, "is_otg            = %d\n", gadget->is_otg);
	seq_म_लिखो(s, "is_a_peripheral   = %d\n", gadget->is_a_peripheral);
	seq_म_लिखो(s, "b_hnp_enable      = %d\n", gadget->b_hnp_enable);
	seq_म_लिखो(s, "a_hnp_support     = %d\n", gadget->a_hnp_support);
	seq_म_लिखो(s, "a_alt_hnp_support = %d\n", gadget->a_alt_hnp_support);
	seq_म_लिखो(s, "name              = %s\n",
		   (gadget->name ? gadget->name : ""));

	अगर (!ci->driver)
		वापस 0;

	seq_म_लिखो(s, "gadget function   = %s\n",
		       (ci->driver->function ? ci->driver->function : ""));
	seq_म_लिखो(s, "gadget max speed  = %d\n", ci->driver->max_speed);

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(ci_device);

/*
 * ci_port_test_show: पढ़ोs port test mode
 */
अटल पूर्णांक ci_port_test_show(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा ci_hdrc *ci = s->निजी;
	अचिन्हित दीर्घ flags;
	अचिन्हित mode;

	pm_runसमय_get_sync(ci->dev);
	spin_lock_irqsave(&ci->lock, flags);
	mode = hw_port_test_get(ci);
	spin_unlock_irqrestore(&ci->lock, flags);
	pm_runसमय_put_sync(ci->dev);

	seq_म_लिखो(s, "mode = %u\n", mode);

	वापस 0;
पूर्ण

/*
 * ci_port_test_ग_लिखो: ग_लिखोs port test mode
 */
अटल sमाप_प्रकार ci_port_test_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *ubuf,
				  माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा seq_file *s = file->निजी_data;
	काष्ठा ci_hdrc *ci = s->निजी;
	अचिन्हित दीर्घ flags;
	अचिन्हित mode;
	अक्षर buf[32];
	पूर्णांक ret;

	count = min_t(माप_प्रकार, माप(buf) - 1, count);
	अगर (copy_from_user(buf, ubuf, count))
		वापस -EFAULT;

	/* माला_पूछो requires a zero terminated string */
	buf[count] = '\0';

	अगर (माला_पूछो(buf, "%u", &mode) != 1)
		वापस -EINVAL;

	अगर (mode > 255)
		वापस -EBADRQC;

	pm_runसमय_get_sync(ci->dev);
	spin_lock_irqsave(&ci->lock, flags);
	ret = hw_port_test_set(ci, mode);
	spin_unlock_irqrestore(&ci->lock, flags);
	pm_runसमय_put_sync(ci->dev);

	वापस ret ? ret : count;
पूर्ण

अटल पूर्णांक ci_port_test_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, ci_port_test_show, inode->i_निजी);
पूर्ण

अटल स्थिर काष्ठा file_operations ci_port_test_fops = अणु
	.खोलो		= ci_port_test_खोलो,
	.ग_लिखो		= ci_port_test_ग_लिखो,
	.पढ़ो		= seq_पढ़ो,
	.llseek		= seq_lseek,
	.release	= single_release,
पूर्ण;

/*
 * ci_qheads_show: DMA contents of all queue heads
 */
अटल पूर्णांक ci_qheads_show(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा ci_hdrc *ci = s->निजी;
	अचिन्हित दीर्घ flags;
	अचिन्हित i, j;

	अगर (ci->role != CI_ROLE_GADGET) अणु
		seq_म_लिखो(s, "not in gadget mode\n");
		वापस 0;
	पूर्ण

	spin_lock_irqsave(&ci->lock, flags);
	क्रम (i = 0; i < ci->hw_ep_max/2; i++) अणु
		काष्ठा ci_hw_ep *hweprx = &ci->ci_hw_ep[i];
		काष्ठा ci_hw_ep *hweptx =
			&ci->ci_hw_ep[i + ci->hw_ep_max/2];
		seq_म_लिखो(s, "EP=%02i: RX=%08X TX=%08X\n",
			   i, (u32)hweprx->qh.dma, (u32)hweptx->qh.dma);
		क्रम (j = 0; j < (माप(काष्ठा ci_hw_qh)/माप(u32)); j++)
			seq_म_लिखो(s, " %04X:    %08X    %08X\n", j,
				   *((u32 *)hweprx->qh.ptr + j),
				   *((u32 *)hweptx->qh.ptr + j));
	पूर्ण
	spin_unlock_irqrestore(&ci->lock, flags);

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(ci_qheads);

/*
 * ci_requests_show: DMA contents of all requests currently queued (all endpts)
 */
अटल पूर्णांक ci_requests_show(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा ci_hdrc *ci = s->निजी;
	अचिन्हित दीर्घ flags;
	काष्ठा ci_hw_req *req = शून्य;
	काष्ठा td_node *node, *पंचांगpnode;
	अचिन्हित i, j, qsize = माप(काष्ठा ci_hw_td)/माप(u32);

	अगर (ci->role != CI_ROLE_GADGET) अणु
		seq_म_लिखो(s, "not in gadget mode\n");
		वापस 0;
	पूर्ण

	spin_lock_irqsave(&ci->lock, flags);
	क्रम (i = 0; i < ci->hw_ep_max; i++)
		list_क्रम_each_entry(req, &ci->ci_hw_ep[i].qh.queue, queue) अणु
			list_क्रम_each_entry_safe(node, पंचांगpnode, &req->tds, td) अणु
				seq_म_लिखो(s, "EP=%02i: TD=%08X %s\n",
					   i % (ci->hw_ep_max / 2),
					   (u32)node->dma,
					   ((i < ci->hw_ep_max/2) ?
					   "RX" : "TX"));

				क्रम (j = 0; j < qsize; j++)
					seq_म_लिखो(s, " %04X:    %08X\n", j,
						   *((u32 *)node->ptr + j));
			पूर्ण
		पूर्ण
	spin_unlock_irqrestore(&ci->lock, flags);

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(ci_requests);

अटल पूर्णांक ci_otg_show(काष्ठा seq_file *s, व्योम *unused)
अणु
	काष्ठा ci_hdrc *ci = s->निजी;
	काष्ठा otg_fsm *fsm;

	अगर (!ci || !ci_otg_is_fsm_mode(ci))
		वापस 0;

	fsm = &ci->fsm;

	/* ------ State ----- */
	seq_म_लिखो(s, "OTG state: %s\n\n",
			usb_otg_state_string(ci->otg.state));

	/* ------ State Machine Variables ----- */
	seq_म_लिखो(s, "a_bus_drop: %d\n", fsm->a_bus_drop);

	seq_म_लिखो(s, "a_bus_req: %d\n", fsm->a_bus_req);

	seq_म_लिखो(s, "a_srp_det: %d\n", fsm->a_srp_det);

	seq_म_लिखो(s, "a_vbus_vld: %d\n", fsm->a_vbus_vld);

	seq_म_लिखो(s, "b_conn: %d\n", fsm->b_conn);

	seq_म_लिखो(s, "adp_change: %d\n", fsm->adp_change);

	seq_म_लिखो(s, "power_up: %d\n", fsm->घातer_up);

	seq_म_लिखो(s, "a_bus_resume: %d\n", fsm->a_bus_resume);

	seq_म_लिखो(s, "a_bus_suspend: %d\n", fsm->a_bus_suspend);

	seq_म_लिखो(s, "a_conn: %d\n", fsm->a_conn);

	seq_म_लिखो(s, "b_bus_req: %d\n", fsm->b_bus_req);

	seq_म_लिखो(s, "b_bus_suspend: %d\n", fsm->b_bus_suspend);

	seq_म_लिखो(s, "b_se0_srp: %d\n", fsm->b_se0_srp);

	seq_म_लिखो(s, "b_ssend_srp: %d\n", fsm->b_ssend_srp);

	seq_म_लिखो(s, "b_sess_vld: %d\n", fsm->b_sess_vld);

	seq_म_लिखो(s, "b_srp_done: %d\n", fsm->b_srp_करोne);

	seq_म_लिखो(s, "drv_vbus: %d\n", fsm->drv_vbus);

	seq_म_लिखो(s, "loc_conn: %d\n", fsm->loc_conn);

	seq_म_लिखो(s, "loc_sof: %d\n", fsm->loc_sof);

	seq_म_लिखो(s, "adp_prb: %d\n", fsm->adp_prb);

	seq_म_लिखो(s, "id: %d\n", fsm->id);

	seq_म_लिखो(s, "protocol: %d\n", fsm->protocol);

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(ci_otg);

अटल पूर्णांक ci_role_show(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा ci_hdrc *ci = s->निजी;

	अगर (ci->role != CI_ROLE_END)
		seq_म_लिखो(s, "%s\n", ci_role(ci)->name);

	वापस 0;
पूर्ण

अटल sमाप_प्रकार ci_role_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *ubuf,
			     माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा seq_file *s = file->निजी_data;
	काष्ठा ci_hdrc *ci = s->निजी;
	क्रमागत ci_role role;
	अक्षर buf[8];
	पूर्णांक ret;

	अगर (copy_from_user(buf, ubuf, min_t(माप_प्रकार, माप(buf) - 1, count)))
		वापस -EFAULT;

	क्रम (role = CI_ROLE_HOST; role < CI_ROLE_END; role++)
		अगर (ci->roles[role] &&
		    !म_भेदन(buf, ci->roles[role]->name,
			     म_माप(ci->roles[role]->name)))
			अवरोध;

	अगर (role == CI_ROLE_END || role == ci->role)
		वापस -EINVAL;

	pm_runसमय_get_sync(ci->dev);
	disable_irq(ci->irq);
	ci_role_stop(ci);
	ret = ci_role_start(ci, role);
	enable_irq(ci->irq);
	pm_runसमय_put_sync(ci->dev);

	वापस ret ? ret : count;
पूर्ण

अटल पूर्णांक ci_role_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, ci_role_show, inode->i_निजी);
पूर्ण

अटल स्थिर काष्ठा file_operations ci_role_fops = अणु
	.खोलो		= ci_role_खोलो,
	.ग_लिखो		= ci_role_ग_लिखो,
	.पढ़ो		= seq_पढ़ो,
	.llseek		= seq_lseek,
	.release	= single_release,
पूर्ण;

अटल पूर्णांक ci_रेजिस्टरs_show(काष्ठा seq_file *s, व्योम *unused)
अणु
	काष्ठा ci_hdrc *ci = s->निजी;
	u32 पंचांगp_reg;

	अगर (!ci || ci->in_lpm)
		वापस -EPERM;

	/* ------ Registers ----- */
	पंचांगp_reg = hw_पढ़ो_पूर्णांकr_enable(ci);
	seq_म_लिखो(s, "USBINTR reg: %08x\n", पंचांगp_reg);

	पंचांगp_reg = hw_पढ़ो_पूर्णांकr_status(ci);
	seq_म_लिखो(s, "USBSTS reg: %08x\n", पंचांगp_reg);

	पंचांगp_reg = hw_पढ़ो(ci, OP_USBMODE, ~0);
	seq_म_लिखो(s, "USBMODE reg: %08x\n", पंचांगp_reg);

	पंचांगp_reg = hw_पढ़ो(ci, OP_USBCMD, ~0);
	seq_म_लिखो(s, "USBCMD reg: %08x\n", पंचांगp_reg);

	पंचांगp_reg = hw_पढ़ो(ci, OP_PORTSC, ~0);
	seq_म_लिखो(s, "PORTSC reg: %08x\n", पंचांगp_reg);

	अगर (ci->is_otg) अणु
		पंचांगp_reg = hw_पढ़ो_otgsc(ci, ~0);
		seq_म_लिखो(s, "OTGSC reg: %08x\n", पंचांगp_reg);
	पूर्ण

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(ci_रेजिस्टरs);

/**
 * dbg_create_files: initializes the attribute पूर्णांकerface
 * @ci: device
 *
 * This function वापसs an error code
 */
व्योम dbg_create_files(काष्ठा ci_hdrc *ci)
अणु
	ci->debugfs = debugfs_create_dir(dev_name(ci->dev), usb_debug_root);

	debugfs_create_file("device", S_IRUGO, ci->debugfs, ci,
			    &ci_device_fops);
	debugfs_create_file("port_test", S_IRUGO | S_IWUSR, ci->debugfs, ci,
			    &ci_port_test_fops);
	debugfs_create_file("qheads", S_IRUGO, ci->debugfs, ci,
			    &ci_qheads_fops);
	debugfs_create_file("requests", S_IRUGO, ci->debugfs, ci,
			    &ci_requests_fops);

	अगर (ci_otg_is_fsm_mode(ci)) अणु
		debugfs_create_file("otg", S_IRUGO, ci->debugfs, ci,
				    &ci_otg_fops);
	पूर्ण

	debugfs_create_file("role", S_IRUGO | S_IWUSR, ci->debugfs, ci,
			    &ci_role_fops);
	debugfs_create_file("registers", S_IRUGO, ci->debugfs, ci,
			    &ci_रेजिस्टरs_fops);
पूर्ण

/**
 * dbg_हटाओ_files: destroys the attribute पूर्णांकerface
 * @ci: device
 */
व्योम dbg_हटाओ_files(काष्ठा ci_hdrc *ci)
अणु
	debugfs_हटाओ_recursive(ci->debugfs);
पूर्ण
