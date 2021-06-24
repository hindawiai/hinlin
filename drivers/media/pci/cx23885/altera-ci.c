<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * altera-ci.c
 *
 *  CI driver in conjunction with NetUp Dual DVB-T/C RF CI card
 *
 * Copyright (C) 2010,2011 NetUP Inc.
 * Copyright (C) 2010,2011 Igor M. Liplianin <liplianin@netup.ru>
 */

/*
 * currently cx23885 GPIO's used.
 * GPIO-0 ~INT in
 * GPIO-1 TMS out
 * GPIO-2 ~reset chips out
 * GPIO-3 to GPIO-10 data/addr क्रम CA in/out
 * GPIO-11 ~CS out
 * GPIO-12 AD_RG out
 * GPIO-13 ~WR out
 * GPIO-14 ~RD out
 * GPIO-15 ~RDY in
 * GPIO-16 TCK out
 * GPIO-17 TDO in
 * GPIO-18 TDI out
 */
/*
 *  Bit definitions क्रम MC417_RWD and MC417_OEN रेजिस्टरs
 * bits 31-16
 * +-----------+
 * | Reserved  |
 * +-----------+
 *   bit 15  bit 14  bit 13 bit 12  bit 11  bit 10  bit 9   bit 8
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 * |  TDI  |  TDO  |  TCK  |  RDY# |  #RD  |  #WR  | AD_RG |  #CS  |
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 *  bit 7   bit 6   bit 5   bit 4   bit 3   bit 2   bit 1   bit 0
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 * |  DATA7|  DATA6|  DATA5|  DATA4|  DATA3|  DATA2|  DATA1|  DATA0|
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <media/dvb_demux.h>
#समावेश <media/dvb_frontend.h>
#समावेश "altera-ci.h"
#समावेश <media/dvb_ca_en50221.h>

/* FPGA regs */
#घोषणा NETUP_CI_INT_CTRL	0x00
#घोषणा NETUP_CI_BUSCTRL2	0x01
#घोषणा NETUP_CI_ADDR0		0x04
#घोषणा NETUP_CI_ADDR1		0x05
#घोषणा NETUP_CI_DATA		0x06
#घोषणा NETUP_CI_BUSCTRL	0x07
#घोषणा NETUP_CI_PID_ADDR0	0x08
#घोषणा NETUP_CI_PID_ADDR1	0x09
#घोषणा NETUP_CI_PID_DATA	0x0a
#घोषणा NETUP_CI_TSA_DIV	0x0c
#घोषणा NETUP_CI_TSB_DIV	0x0d
#घोषणा NETUP_CI_REVISION	0x0f

/* स्थिर क्रम ci op */
#घोषणा NETUP_CI_FLG_CTL	1
#घोषणा NETUP_CI_FLG_RD		1
#घोषणा NETUP_CI_FLG_AD		1

अटल अचिन्हित पूर्णांक ci_dbg;
module_param(ci_dbg, पूर्णांक, 0644);
MODULE_PARM_DESC(ci_dbg, "Enable CI debugging");

अटल अचिन्हित पूर्णांक pid_dbg;
module_param(pid_dbg, पूर्णांक, 0644);
MODULE_PARM_DESC(pid_dbg, "Enable PID filtering debugging");

MODULE_DESCRIPTION("altera FPGA CI module");
MODULE_AUTHOR("Igor M. Liplianin  <liplianin@netup.ru>");
MODULE_LICENSE("GPL");

#घोषणा ci_dbg_prपूर्णांक(fmt, args...) \
	करो अणु \
		अगर (ci_dbg) \
			prपूर्णांकk(KERN_DEBUG pr_fmt("%s: " fmt), \
			       __func__, ##args); \
	पूर्ण जबतक (0)

#घोषणा pid_dbg_prपूर्णांक(fmt, args...) \
	करो अणु \
		अगर (pid_dbg) \
			prपूर्णांकk(KERN_DEBUG pr_fmt("%s: " fmt), \
			       __func__, ##args); \
	पूर्ण जबतक (0)

काष्ठा altera_ci_state;
काष्ठा netup_hw_pid_filter;

काष्ठा fpga_पूर्णांकernal अणु
	व्योम *dev;
	काष्ठा mutex fpga_mutex;/* two CI's on the same fpga */
	काष्ठा netup_hw_pid_filter *pid_filt[2];
	काष्ठा altera_ci_state *state[2];
	काष्ठा work_काष्ठा work;
	पूर्णांक (*fpga_rw) (व्योम *dev, पूर्णांक flag, पूर्णांक data, पूर्णांक rw);
	पूर्णांक cis_used;
	पूर्णांक filts_used;
	पूर्णांक strt_wrk;
पूर्ण;

/* stores all निजी variables क्रम communication with CI */
काष्ठा altera_ci_state अणु
	काष्ठा fpga_पूर्णांकernal *पूर्णांकernal;
	काष्ठा dvb_ca_en50221 ca;
	पूर्णांक status;
	पूर्णांक nr;
पूर्ण;

/* stores all निजी variables क्रम hardware pid filtering */
काष्ठा netup_hw_pid_filter अणु
	काष्ठा fpga_पूर्णांकernal *पूर्णांकernal;
	काष्ठा dvb_demux *demux;
	/* save old functions */
	पूर्णांक (*start_feed)(काष्ठा dvb_demux_feed *feed);
	पूर्णांक (*stop_feed)(काष्ठा dvb_demux_feed *feed);

	पूर्णांक status;
	पूर्णांक nr;
पूर्ण;

/* पूर्णांकernal params node */
काष्ठा fpga_inode अणु
	/* poपूर्णांकer क्रम पूर्णांकernal params, one क्रम each pair of CI's */
	काष्ठा fpga_पूर्णांकernal		*पूर्णांकernal;
	काष्ठा fpga_inode		*next_inode;
पूर्ण;

/* first पूर्णांकernal params */
अटल काष्ठा fpga_inode *fpga_first_inode;

/* find chip by dev */
अटल काष्ठा fpga_inode *find_inode(व्योम *dev)
अणु
	काष्ठा fpga_inode *temp_chip = fpga_first_inode;

	अगर (temp_chip == शून्य)
		वापस temp_chip;

	/*
	 Search क्रम the last fpga CI chip or
	 find it by dev */
	जबतक ((temp_chip != शून्य) &&
				(temp_chip->पूर्णांकernal->dev != dev))
		temp_chip = temp_chip->next_inode;

	वापस temp_chip;
पूर्ण
/* check demux */
अटल काष्ठा fpga_पूर्णांकernal *check_filter(काष्ठा fpga_पूर्णांकernal *temp_पूर्णांक,
						व्योम *demux_dev, पूर्णांक filt_nr)
अणु
	अगर (temp_पूर्णांक == शून्य)
		वापस शून्य;

	अगर ((temp_पूर्णांक->pid_filt[filt_nr]) == शून्य)
		वापस शून्य;

	अगर (temp_पूर्णांक->pid_filt[filt_nr]->demux == demux_dev)
		वापस temp_पूर्णांक;

	वापस शून्य;
पूर्ण

/* find chip by demux */
अटल काष्ठा fpga_inode *find_dinode(व्योम *demux_dev)
अणु
	काष्ठा fpga_inode *temp_chip = fpga_first_inode;
	काष्ठा fpga_पूर्णांकernal *temp_पूर्णांक;

	/*
	 * Search of the last fpga CI chip or
	 * find it by demux
	 */
	जबतक (temp_chip != शून्य) अणु
		अगर (temp_chip->पूर्णांकernal != शून्य) अणु
			temp_पूर्णांक = temp_chip->पूर्णांकernal;
			अगर (check_filter(temp_पूर्णांक, demux_dev, 0))
				अवरोध;
			अगर (check_filter(temp_पूर्णांक, demux_dev, 1))
				अवरोध;
		पूर्ण

		temp_chip = temp_chip->next_inode;
	पूर्ण

	वापस temp_chip;
पूर्ण

/* deallocating chip */
अटल व्योम हटाओ_inode(काष्ठा fpga_पूर्णांकernal *पूर्णांकernal)
अणु
	काष्ठा fpga_inode *prev_node = fpga_first_inode;
	काष्ठा fpga_inode *del_node = find_inode(पूर्णांकernal->dev);

	अगर (del_node != शून्य) अणु
		अगर (del_node == fpga_first_inode) अणु
			fpga_first_inode = del_node->next_inode;
		पूर्ण अन्यथा अणु
			जबतक (prev_node->next_inode != del_node)
				prev_node = prev_node->next_inode;

			अगर (del_node->next_inode == शून्य)
				prev_node->next_inode = शून्य;
			अन्यथा
				prev_node->next_inode =
					prev_node->next_inode->next_inode;
		पूर्ण

		kमुक्त(del_node);
	पूर्ण
पूर्ण

/* allocating new chip */
अटल काष्ठा fpga_inode *append_पूर्णांकernal(काष्ठा fpga_पूर्णांकernal *पूर्णांकernal)
अणु
	काष्ठा fpga_inode *new_node = fpga_first_inode;

	अगर (new_node == शून्य) अणु
		new_node = kदो_स्मृति(माप(काष्ठा fpga_inode), GFP_KERNEL);
		fpga_first_inode = new_node;
	पूर्ण अन्यथा अणु
		जबतक (new_node->next_inode != शून्य)
			new_node = new_node->next_inode;

		new_node->next_inode =
				kदो_स्मृति(माप(काष्ठा fpga_inode), GFP_KERNEL);
		अगर (new_node->next_inode != शून्य)
			new_node = new_node->next_inode;
		अन्यथा
			new_node = शून्य;
	पूर्ण

	अगर (new_node != शून्य) अणु
		new_node->पूर्णांकernal = पूर्णांकernal;
		new_node->next_inode = शून्य;
	पूर्ण

	वापस new_node;
पूर्ण

अटल पूर्णांक netup_fpga_op_rw(काष्ठा fpga_पूर्णांकernal *पूर्णांकer, पूर्णांक addr,
							u8 val, u8 पढ़ो)
अणु
	पूर्णांकer->fpga_rw(पूर्णांकer->dev, NETUP_CI_FLG_AD, addr, 0);
	वापस पूर्णांकer->fpga_rw(पूर्णांकer->dev, 0, val, पढ़ो);
पूर्ण

/* flag - mem/io, पढ़ो - पढ़ो/ग_लिखो */
अटल पूर्णांक altera_ci_op_cam(काष्ठा dvb_ca_en50221 *en50221, पूर्णांक slot,
				u8 flag, u8 पढ़ो, पूर्णांक addr, u8 val)
अणु

	काष्ठा altera_ci_state *state = en50221->data;
	काष्ठा fpga_पूर्णांकernal *पूर्णांकer = state->पूर्णांकernal;

	u8 store;
	पूर्णांक mem = 0;

	अगर (0 != slot)
		वापस -EINVAL;

	mutex_lock(&पूर्णांकer->fpga_mutex);

	netup_fpga_op_rw(पूर्णांकer, NETUP_CI_ADDR0, ((addr << 1) & 0xfe), 0);
	netup_fpga_op_rw(पूर्णांकer, NETUP_CI_ADDR1, ((addr >> 7) & 0x7f), 0);
	store = netup_fpga_op_rw(पूर्णांकer, NETUP_CI_BUSCTRL, 0, NETUP_CI_FLG_RD);

	store &= 0x0f;
	store |= ((state->nr << 7) | (flag << 6));

	netup_fpga_op_rw(पूर्णांकer, NETUP_CI_BUSCTRL, store, 0);
	mem = netup_fpga_op_rw(पूर्णांकer, NETUP_CI_DATA, val, पढ़ो);

	mutex_unlock(&पूर्णांकer->fpga_mutex);

	ci_dbg_prपूर्णांक("%s: %s: addr=[0x%02x], %s=%x\n", __func__,
			(पढ़ो) ? "read" : "write", addr,
			(flag == NETUP_CI_FLG_CTL) ? "ctl" : "mem",
			(पढ़ो) ? mem : val);

	वापस mem;
पूर्ण

अटल पूर्णांक altera_ci_पढ़ो_attribute_mem(काष्ठा dvb_ca_en50221 *en50221,
					पूर्णांक slot, पूर्णांक addr)
अणु
	वापस altera_ci_op_cam(en50221, slot, 0, NETUP_CI_FLG_RD, addr, 0);
पूर्ण

अटल पूर्णांक altera_ci_ग_लिखो_attribute_mem(काष्ठा dvb_ca_en50221 *en50221,
					 पूर्णांक slot, पूर्णांक addr, u8 data)
अणु
	वापस altera_ci_op_cam(en50221, slot, 0, 0, addr, data);
पूर्ण

अटल पूर्णांक altera_ci_पढ़ो_cam_ctl(काष्ठा dvb_ca_en50221 *en50221,
				  पूर्णांक slot, u8 addr)
अणु
	वापस altera_ci_op_cam(en50221, slot, NETUP_CI_FLG_CTL,
						NETUP_CI_FLG_RD, addr, 0);
पूर्ण

अटल पूर्णांक altera_ci_ग_लिखो_cam_ctl(काष्ठा dvb_ca_en50221 *en50221, पूर्णांक slot,
				   u8 addr, u8 data)
अणु
	वापस altera_ci_op_cam(en50221, slot, NETUP_CI_FLG_CTL, 0, addr, data);
पूर्ण

अटल पूर्णांक altera_ci_slot_reset(काष्ठा dvb_ca_en50221 *en50221, पूर्णांक slot)
अणु
	काष्ठा altera_ci_state *state = en50221->data;
	काष्ठा fpga_पूर्णांकernal *पूर्णांकer = state->पूर्णांकernal;
	/* reasonable समयout क्रम CI reset is 10 seconds */
	अचिन्हित दीर्घ t_out = jअगरfies + msecs_to_jअगरfies(9999);
	पूर्णांक ret;

	ci_dbg_prपूर्णांक("%s\n", __func__);

	अगर (0 != slot)
		वापस -EINVAL;

	mutex_lock(&पूर्णांकer->fpga_mutex);

	ret = netup_fpga_op_rw(पूर्णांकer, NETUP_CI_BUSCTRL, 0, NETUP_CI_FLG_RD);
	netup_fpga_op_rw(पूर्णांकer, NETUP_CI_BUSCTRL,
				(ret & 0xcf) | (1 << (5 - state->nr)), 0);

	mutex_unlock(&पूर्णांकer->fpga_mutex);

	क्रम (;;) अणु
		msleep(50);

		mutex_lock(&पूर्णांकer->fpga_mutex);

		ret = netup_fpga_op_rw(पूर्णांकer, NETUP_CI_BUSCTRL,
						0, NETUP_CI_FLG_RD);
		mutex_unlock(&पूर्णांकer->fpga_mutex);

		अगर ((ret & (1 << (5 - state->nr))) == 0)
			अवरोध;
		अगर (समय_after(jअगरfies, t_out))
			अवरोध;
	पूर्ण


	ci_dbg_prपूर्णांक("%s: %d msecs\n", __func__,
		jअगरfies_to_msecs(jअगरfies + msecs_to_jअगरfies(9999) - t_out));

	वापस 0;
पूर्ण

अटल पूर्णांक altera_ci_slot_shutकरोwn(काष्ठा dvb_ca_en50221 *en50221, पूर्णांक slot)
अणु
	/* not implemented */
	वापस 0;
पूर्ण

अटल पूर्णांक altera_ci_slot_ts_ctl(काष्ठा dvb_ca_en50221 *en50221, पूर्णांक slot)
अणु
	काष्ठा altera_ci_state *state = en50221->data;
	काष्ठा fpga_पूर्णांकernal *पूर्णांकer = state->पूर्णांकernal;
	पूर्णांक ret;

	ci_dbg_prपूर्णांक("%s\n", __func__);

	अगर (0 != slot)
		वापस -EINVAL;

	mutex_lock(&पूर्णांकer->fpga_mutex);

	ret = netup_fpga_op_rw(पूर्णांकer, NETUP_CI_BUSCTRL, 0, NETUP_CI_FLG_RD);
	netup_fpga_op_rw(पूर्णांकer, NETUP_CI_BUSCTRL,
				(ret & 0x0f) | (1 << (3 - state->nr)), 0);

	mutex_unlock(&पूर्णांकer->fpga_mutex);

	वापस 0;
पूर्ण

/* work handler */
अटल व्योम netup_पढ़ो_ci_status(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा fpga_पूर्णांकernal *पूर्णांकer =
			container_of(work, काष्ठा fpga_पूर्णांकernal, work);
	पूर्णांक ret;

	ci_dbg_prपूर्णांक("%s\n", __func__);

	mutex_lock(&पूर्णांकer->fpga_mutex);
	/* ack' irq */
	ret = netup_fpga_op_rw(पूर्णांकer, NETUP_CI_INT_CTRL, 0, NETUP_CI_FLG_RD);
	ret = netup_fpga_op_rw(पूर्णांकer, NETUP_CI_BUSCTRL, 0, NETUP_CI_FLG_RD);

	mutex_unlock(&पूर्णांकer->fpga_mutex);

	अगर (पूर्णांकer->state[1] != शून्य) अणु
		पूर्णांकer->state[1]->status =
				((ret & 1) == 0 ?
				DVB_CA_EN50221_POLL_CAM_PRESENT |
				DVB_CA_EN50221_POLL_CAM_READY : 0);
		ci_dbg_prपूर्णांक("%s: setting CI[1] status = 0x%x\n",
				__func__, पूर्णांकer->state[1]->status);
	पूर्ण

	अगर (पूर्णांकer->state[0] != शून्य) अणु
		पूर्णांकer->state[0]->status =
				((ret & 2) == 0 ?
				DVB_CA_EN50221_POLL_CAM_PRESENT |
				DVB_CA_EN50221_POLL_CAM_READY : 0);
		ci_dbg_prपूर्णांक("%s: setting CI[0] status = 0x%x\n",
				__func__, पूर्णांकer->state[0]->status);
	पूर्ण
पूर्ण

/* CI irq handler */
पूर्णांक altera_ci_irq(व्योम *dev)
अणु
	काष्ठा fpga_inode *temp_पूर्णांक = शून्य;
	काष्ठा fpga_पूर्णांकernal *पूर्णांकer = शून्य;

	ci_dbg_prपूर्णांक("%s\n", __func__);

	अगर (dev != शून्य) अणु
		temp_पूर्णांक = find_inode(dev);
		अगर (temp_पूर्णांक != शून्य) अणु
			पूर्णांकer = temp_पूर्णांक->पूर्णांकernal;
			schedule_work(&पूर्णांकer->work);
		पूर्ण
	पूर्ण

	वापस 1;
पूर्ण
EXPORT_SYMBOL(altera_ci_irq);

अटल पूर्णांक altera_poll_ci_slot_status(काष्ठा dvb_ca_en50221 *en50221,
				      पूर्णांक slot, पूर्णांक खोलो)
अणु
	काष्ठा altera_ci_state *state = en50221->data;

	अगर (0 != slot)
		वापस -EINVAL;

	वापस state->status;
पूर्ण

अटल व्योम altera_hw_filt_release(व्योम *मुख्य_dev, पूर्णांक filt_nr)
अणु
	काष्ठा fpga_inode *temp_पूर्णांक = find_inode(मुख्य_dev);
	काष्ठा netup_hw_pid_filter *pid_filt = शून्य;

	ci_dbg_prपूर्णांक("%s\n", __func__);

	अगर (temp_पूर्णांक != शून्य) अणु
		pid_filt = temp_पूर्णांक->पूर्णांकernal->pid_filt[filt_nr - 1];
		/* stored old feed controls */
		pid_filt->demux->start_feed = pid_filt->start_feed;
		pid_filt->demux->stop_feed = pid_filt->stop_feed;

		अगर (((--(temp_पूर्णांक->पूर्णांकernal->filts_used)) <= 0) &&
			 ((temp_पूर्णांक->पूर्णांकernal->cis_used) <= 0)) अणु

			ci_dbg_prपूर्णांक("%s: Actually removing\n", __func__);

			हटाओ_inode(temp_पूर्णांक->पूर्णांकernal);
			kमुक्त(pid_filt->पूर्णांकernal);
		पूर्ण

		kमुक्त(pid_filt);

	पूर्ण

पूर्ण

व्योम altera_ci_release(व्योम *dev, पूर्णांक ci_nr)
अणु
	काष्ठा fpga_inode *temp_पूर्णांक = find_inode(dev);
	काष्ठा altera_ci_state *state = शून्य;

	ci_dbg_prपूर्णांक("%s\n", __func__);

	अगर (temp_पूर्णांक != शून्य) अणु
		state = temp_पूर्णांक->पूर्णांकernal->state[ci_nr - 1];
		altera_hw_filt_release(dev, ci_nr);


		अगर (((temp_पूर्णांक->पूर्णांकernal->filts_used) <= 0) &&
				((--(temp_पूर्णांक->पूर्णांकernal->cis_used)) <= 0)) अणु

			ci_dbg_prपूर्णांक("%s: Actually removing\n", __func__);

			हटाओ_inode(temp_पूर्णांक->पूर्णांकernal);
			kमुक्त(state->पूर्णांकernal);
		पूर्ण

		अगर (state != शून्य) अणु
			अगर (state->ca.data != शून्य)
				dvb_ca_en50221_release(&state->ca);

			kमुक्त(state);
		पूर्ण
	पूर्ण

पूर्ण
EXPORT_SYMBOL(altera_ci_release);

अटल व्योम altera_pid_control(काष्ठा netup_hw_pid_filter *pid_filt,
		u16 pid, पूर्णांक onoff)
अणु
	काष्ठा fpga_पूर्णांकernal *पूर्णांकer = pid_filt->पूर्णांकernal;
	u8 store = 0;

	/* pid 0-0x1f always enabled, करोn't touch them */
	अगर ((pid == 0x2000) || (pid < 0x20))
		वापस;

	mutex_lock(&पूर्णांकer->fpga_mutex);

	netup_fpga_op_rw(पूर्णांकer, NETUP_CI_PID_ADDR0, (pid >> 3) & 0xff, 0);
	netup_fpga_op_rw(पूर्णांकer, NETUP_CI_PID_ADDR1,
			((pid >> 11) & 0x03) | (pid_filt->nr << 2), 0);

	store = netup_fpga_op_rw(पूर्णांकer, NETUP_CI_PID_DATA, 0, NETUP_CI_FLG_RD);

	अगर (onoff)/* 0 - on, 1 - off */
		store |= (1 << (pid & 7));
	अन्यथा
		store &= ~(1 << (pid & 7));

	netup_fpga_op_rw(पूर्णांकer, NETUP_CI_PID_DATA, store, 0);

	mutex_unlock(&पूर्णांकer->fpga_mutex);

	pid_dbg_prपूर्णांक("%s: (%d) set pid: %5d 0x%04x '%s'\n", __func__,
		pid_filt->nr, pid, pid, onoff ? "off" : "on");
पूर्ण

अटल व्योम altera_toggle_fullts_streaming(काष्ठा netup_hw_pid_filter *pid_filt,
					पूर्णांक filt_nr, पूर्णांक onoff)
अणु
	काष्ठा fpga_पूर्णांकernal *पूर्णांकer = pid_filt->पूर्णांकernal;
	u8 store = 0;
	पूर्णांक i;

	pid_dbg_prपूर्णांक("%s: pid_filt->nr[%d]  now %s\n", __func__, pid_filt->nr,
			onoff ? "off" : "on");

	अगर (onoff)/* 0 - on, 1 - off */
		store = 0xff;/* ignore pid */
	अन्यथा
		store = 0;/* enable pid */

	mutex_lock(&पूर्णांकer->fpga_mutex);

	क्रम (i = 0; i < 1024; i++) अणु
		netup_fpga_op_rw(पूर्णांकer, NETUP_CI_PID_ADDR0, i & 0xff, 0);

		netup_fpga_op_rw(पूर्णांकer, NETUP_CI_PID_ADDR1,
				((i >> 8) & 0x03) | (pid_filt->nr << 2), 0);
		/* pid 0-0x1f always enabled */
		netup_fpga_op_rw(पूर्णांकer, NETUP_CI_PID_DATA,
				(i > 3 ? store : 0), 0);
	पूर्ण

	mutex_unlock(&पूर्णांकer->fpga_mutex);
पूर्ण

अटल पूर्णांक altera_pid_feed_control(व्योम *demux_dev, पूर्णांक filt_nr,
		काष्ठा dvb_demux_feed *feed, पूर्णांक onoff)
अणु
	काष्ठा fpga_inode *temp_पूर्णांक = find_dinode(demux_dev);
	काष्ठा fpga_पूर्णांकernal *पूर्णांकer = temp_पूर्णांक->पूर्णांकernal;
	काष्ठा netup_hw_pid_filter *pid_filt = पूर्णांकer->pid_filt[filt_nr - 1];

	altera_pid_control(pid_filt, feed->pid, onoff ? 0 : 1);
	/* call old feed proc's */
	अगर (onoff)
		pid_filt->start_feed(feed);
	अन्यथा
		pid_filt->stop_feed(feed);

	अगर (feed->pid == 0x2000)
		altera_toggle_fullts_streaming(pid_filt, filt_nr,
						onoff ? 0 : 1);

	वापस 0;
पूर्ण

अटल पूर्णांक altera_ci_start_feed(काष्ठा dvb_demux_feed *feed, पूर्णांक num)
अणु
	altera_pid_feed_control(feed->demux, num, feed, 1);

	वापस 0;
पूर्ण

अटल पूर्णांक altera_ci_stop_feed(काष्ठा dvb_demux_feed *feed, पूर्णांक num)
अणु
	altera_pid_feed_control(feed->demux, num, feed, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक altera_ci_start_feed_1(काष्ठा dvb_demux_feed *feed)
अणु
	वापस altera_ci_start_feed(feed, 1);
पूर्ण

अटल पूर्णांक altera_ci_stop_feed_1(काष्ठा dvb_demux_feed *feed)
अणु
	वापस altera_ci_stop_feed(feed, 1);
पूर्ण

अटल पूर्णांक altera_ci_start_feed_2(काष्ठा dvb_demux_feed *feed)
अणु
	वापस altera_ci_start_feed(feed, 2);
पूर्ण

अटल पूर्णांक altera_ci_stop_feed_2(काष्ठा dvb_demux_feed *feed)
अणु
	वापस altera_ci_stop_feed(feed, 2);
पूर्ण

अटल पूर्णांक altera_hw_filt_init(काष्ठा altera_ci_config *config, पूर्णांक hw_filt_nr)
अणु
	काष्ठा netup_hw_pid_filter *pid_filt = शून्य;
	काष्ठा fpga_inode *temp_पूर्णांक = find_inode(config->dev);
	काष्ठा fpga_पूर्णांकernal *पूर्णांकer = शून्य;
	पूर्णांक ret = 0;

	pid_filt = kzalloc(माप(काष्ठा netup_hw_pid_filter), GFP_KERNEL);

	ci_dbg_prपूर्णांक("%s\n", __func__);

	अगर (!pid_filt) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	अगर (temp_पूर्णांक != शून्य) अणु
		पूर्णांकer = temp_पूर्णांक->पूर्णांकernal;
		(पूर्णांकer->filts_used)++;
		ci_dbg_prपूर्णांक("%s: Find Internal Structure!\n", __func__);
	पूर्ण अन्यथा अणु
		पूर्णांकer = kzalloc(माप(काष्ठा fpga_पूर्णांकernal), GFP_KERNEL);
		अगर (!पूर्णांकer) अणु
			ret = -ENOMEM;
			जाओ err;
		पूर्ण

		temp_पूर्णांक = append_पूर्णांकernal(पूर्णांकer);
		अगर (!temp_पूर्णांक) अणु
			ret = -ENOMEM;
			जाओ err;
		पूर्ण
		पूर्णांकer->filts_used = 1;
		पूर्णांकer->dev = config->dev;
		पूर्णांकer->fpga_rw = config->fpga_rw;
		mutex_init(&पूर्णांकer->fpga_mutex);
		पूर्णांकer->strt_wrk = 1;
		ci_dbg_prपूर्णांक("%s: Create New Internal Structure!\n", __func__);
	पूर्ण

	ci_dbg_prपूर्णांक("%s: setting hw pid filter = %p for ci = %d\n", __func__,
						pid_filt, hw_filt_nr - 1);
	पूर्णांकer->pid_filt[hw_filt_nr - 1] = pid_filt;
	pid_filt->demux = config->demux;
	pid_filt->पूर्णांकernal = पूर्णांकer;
	pid_filt->nr = hw_filt_nr - 1;
	/* store old feed controls */
	pid_filt->start_feed = config->demux->start_feed;
	pid_filt->stop_feed = config->demux->stop_feed;
	/* replace with new feed controls */
	अगर (hw_filt_nr == 1) अणु
		pid_filt->demux->start_feed = altera_ci_start_feed_1;
		pid_filt->demux->stop_feed = altera_ci_stop_feed_1;
	पूर्ण अन्यथा अगर (hw_filt_nr == 2) अणु
		pid_filt->demux->start_feed = altera_ci_start_feed_2;
		pid_filt->demux->stop_feed = altera_ci_stop_feed_2;
	पूर्ण

	altera_toggle_fullts_streaming(pid_filt, 0, 1);

	वापस 0;
err:
	ci_dbg_prपूर्णांक("%s: Can't init hardware filter: Error %d\n",
		     __func__, ret);

	kमुक्त(pid_filt);
	kमुक्त(पूर्णांकer);

	वापस ret;
पूर्ण

पूर्णांक altera_ci_init(काष्ठा altera_ci_config *config, पूर्णांक ci_nr)
अणु
	काष्ठा altera_ci_state *state;
	काष्ठा fpga_inode *temp_पूर्णांक = find_inode(config->dev);
	काष्ठा fpga_पूर्णांकernal *पूर्णांकer = शून्य;
	पूर्णांक ret = 0;
	u8 store = 0;

	state = kzalloc(माप(काष्ठा altera_ci_state), GFP_KERNEL);

	ci_dbg_prपूर्णांक("%s\n", __func__);

	अगर (!state) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	अगर (temp_पूर्णांक != शून्य) अणु
		पूर्णांकer = temp_पूर्णांक->पूर्णांकernal;
		(पूर्णांकer->cis_used)++;
		पूर्णांकer->fpga_rw = config->fpga_rw;
		ci_dbg_prपूर्णांक("%s: Find Internal Structure!\n", __func__);
	पूर्ण अन्यथा अणु
		पूर्णांकer = kzalloc(माप(काष्ठा fpga_पूर्णांकernal), GFP_KERNEL);
		अगर (!पूर्णांकer) अणु
			ret = -ENOMEM;
			जाओ err;
		पूर्ण

		temp_पूर्णांक = append_पूर्णांकernal(पूर्णांकer);
		अगर (!temp_पूर्णांक) अणु
			ret = -ENOMEM;
			जाओ err;
		पूर्ण
		पूर्णांकer->cis_used = 1;
		पूर्णांकer->dev = config->dev;
		पूर्णांकer->fpga_rw = config->fpga_rw;
		mutex_init(&पूर्णांकer->fpga_mutex);
		पूर्णांकer->strt_wrk = 1;
		ci_dbg_prपूर्णांक("%s: Create New Internal Structure!\n", __func__);
	पूर्ण

	ci_dbg_prपूर्णांक("%s: setting state = %p for ci = %d\n", __func__,
						state, ci_nr - 1);
	state->पूर्णांकernal = पूर्णांकer;
	state->nr = ci_nr - 1;

	state->ca.owner = THIS_MODULE;
	state->ca.पढ़ो_attribute_mem = altera_ci_पढ़ो_attribute_mem;
	state->ca.ग_लिखो_attribute_mem = altera_ci_ग_लिखो_attribute_mem;
	state->ca.पढ़ो_cam_control = altera_ci_पढ़ो_cam_ctl;
	state->ca.ग_लिखो_cam_control = altera_ci_ग_लिखो_cam_ctl;
	state->ca.slot_reset = altera_ci_slot_reset;
	state->ca.slot_shutकरोwn = altera_ci_slot_shutकरोwn;
	state->ca.slot_ts_enable = altera_ci_slot_ts_ctl;
	state->ca.poll_slot_status = altera_poll_ci_slot_status;
	state->ca.data = state;

	ret = dvb_ca_en50221_init(config->adapter,
				   &state->ca,
				   /* flags */ 0,
				   /* n_slots */ 1);
	अगर (0 != ret)
		जाओ err;

	पूर्णांकer->state[ci_nr - 1] = state;

	altera_hw_filt_init(config, ci_nr);

	अगर (पूर्णांकer->strt_wrk) अणु
		INIT_WORK(&पूर्णांकer->work, netup_पढ़ो_ci_status);
		पूर्णांकer->strt_wrk = 0;
	पूर्ण

	ci_dbg_prपूर्णांक("%s: CI initialized!\n", __func__);

	mutex_lock(&पूर्णांकer->fpga_mutex);

	/* Enable भाग */
	netup_fpga_op_rw(पूर्णांकer, NETUP_CI_TSA_DIV, 0x0, 0);
	netup_fpga_op_rw(पूर्णांकer, NETUP_CI_TSB_DIV, 0x0, 0);

	/* enable TS out */
	store = netup_fpga_op_rw(पूर्णांकer, NETUP_CI_BUSCTRL2, 0, NETUP_CI_FLG_RD);
	store |= (3 << 4);
	netup_fpga_op_rw(पूर्णांकer, NETUP_CI_BUSCTRL2, store, 0);

	ret = netup_fpga_op_rw(पूर्णांकer, NETUP_CI_REVISION, 0, NETUP_CI_FLG_RD);
	/* enable irq */
	netup_fpga_op_rw(पूर्णांकer, NETUP_CI_INT_CTRL, 0x44, 0);

	mutex_unlock(&पूर्णांकer->fpga_mutex);

	ci_dbg_prपूर्णांक("%s: NetUP CI Revision = 0x%x\n", __func__, ret);

	schedule_work(&पूर्णांकer->work);

	वापस 0;
err:
	ci_dbg_prपूर्णांक("%s: Cannot initialize CI: Error %d.\n", __func__, ret);

	kमुक्त(state);
	kमुक्त(पूर्णांकer);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(altera_ci_init);

पूर्णांक altera_ci_tuner_reset(व्योम *dev, पूर्णांक ci_nr)
अणु
	काष्ठा fpga_inode *temp_पूर्णांक = find_inode(dev);
	काष्ठा fpga_पूर्णांकernal *पूर्णांकer = शून्य;
	u8 store;

	ci_dbg_prपूर्णांक("%s\n", __func__);

	अगर (temp_पूर्णांक == शून्य)
		वापस -1;

	अगर (temp_पूर्णांक->पूर्णांकernal == शून्य)
		वापस -1;

	पूर्णांकer = temp_पूर्णांक->पूर्णांकernal;

	mutex_lock(&पूर्णांकer->fpga_mutex);

	store = netup_fpga_op_rw(पूर्णांकer, NETUP_CI_BUSCTRL2, 0, NETUP_CI_FLG_RD);
	store &= ~(4 << (2 - ci_nr));
	netup_fpga_op_rw(पूर्णांकer, NETUP_CI_BUSCTRL2, store, 0);
	msleep(100);
	store |= (4 << (2 - ci_nr));
	netup_fpga_op_rw(पूर्णांकer, NETUP_CI_BUSCTRL2, store, 0);

	mutex_unlock(&पूर्णांकer->fpga_mutex);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(altera_ci_tuner_reset);
