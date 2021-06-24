<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Texas Instruments K3 AM65 Ethernet QoS submodule
 * Copyright (C) 2020 Texas Instruments Incorporated - http://www.ti.com/
 *
 * quality of service module includes:
 * Enhanced Scheduler Traffic (EST - P802.1Qbv/D2.2)
 */

#समावेश <linux/pm_runसमय.स>
#समावेश <linux/समय.स>

#समावेश "am65-cpsw-nuss.h"
#समावेश "am65-cpsw-qos.h"
#समावेश "am65-cpts.h"

#घोषणा AM65_CPSW_REG_CTL			0x004
#घोषणा AM65_CPSW_PN_REG_CTL			0x004
#घोषणा AM65_CPSW_PN_REG_FIFO_STATUS		0x050
#घोषणा AM65_CPSW_PN_REG_EST_CTL		0x060

/* AM65_CPSW_REG_CTL रेजिस्टर fields */
#घोषणा AM65_CPSW_CTL_EST_EN			BIT(18)

/* AM65_CPSW_PN_REG_CTL रेजिस्टर fields */
#घोषणा AM65_CPSW_PN_CTL_EST_PORT_EN		BIT(17)

/* AM65_CPSW_PN_REG_EST_CTL रेजिस्टर fields */
#घोषणा AM65_CPSW_PN_EST_ONEBUF			BIT(0)
#घोषणा AM65_CPSW_PN_EST_BUFSEL			BIT(1)
#घोषणा AM65_CPSW_PN_EST_TS_EN			BIT(2)
#घोषणा AM65_CPSW_PN_EST_TS_FIRST		BIT(3)
#घोषणा AM65_CPSW_PN_EST_ONEPRI			BIT(4)
#घोषणा AM65_CPSW_PN_EST_TS_PRI_MSK		GENMASK(7, 5)

/* AM65_CPSW_PN_REG_FIFO_STATUS रेजिस्टर fields */
#घोषणा AM65_CPSW_PN_FST_TX_PRI_ACTIVE_MSK	GENMASK(7, 0)
#घोषणा AM65_CPSW_PN_FST_TX_E_MAC_ALLOW_MSK	GENMASK(15, 8)
#घोषणा AM65_CPSW_PN_FST_EST_CNT_ERR		BIT(16)
#घोषणा AM65_CPSW_PN_FST_EST_ADD_ERR		BIT(17)
#घोषणा AM65_CPSW_PN_FST_EST_BUFACT		BIT(18)

/* EST FETCH COMMAND RAM */
#घोषणा AM65_CPSW_FETCH_RAM_CMD_NUM		0x80
#घोषणा AM65_CPSW_FETCH_CNT_MSK			GENMASK(21, 8)
#घोषणा AM65_CPSW_FETCH_CNT_MAX			(AM65_CPSW_FETCH_CNT_MSK >> 8)
#घोषणा AM65_CPSW_FETCH_CNT_OFFSET		8
#घोषणा AM65_CPSW_FETCH_ALLOW_MSK		GENMASK(7, 0)
#घोषणा AM65_CPSW_FETCH_ALLOW_MAX		AM65_CPSW_FETCH_ALLOW_MSK

क्रमागत समयr_act अणु
	TACT_PROG,		/* need program समयr */
	TACT_NEED_STOP,		/* need stop first */
	TACT_SKIP_PROG,		/* just buffer can be updated */
पूर्ण;

अटल पूर्णांक am65_cpsw_port_est_enabled(काष्ठा am65_cpsw_port *port)
अणु
	वापस port->qos.est_oper || port->qos.est_admin;
पूर्ण

अटल व्योम am65_cpsw_est_enable(काष्ठा am65_cpsw_common *common, पूर्णांक enable)
अणु
	u32 val;

	val = पढ़ोl(common->cpsw_base + AM65_CPSW_REG_CTL);

	अगर (enable)
		val |= AM65_CPSW_CTL_EST_EN;
	अन्यथा
		val &= ~AM65_CPSW_CTL_EST_EN;

	ग_लिखोl(val, common->cpsw_base + AM65_CPSW_REG_CTL);
	common->est_enabled = enable;
पूर्ण

अटल व्योम am65_cpsw_port_est_enable(काष्ठा am65_cpsw_port *port, पूर्णांक enable)
अणु
	u32 val;

	val = पढ़ोl(port->port_base + AM65_CPSW_PN_REG_CTL);
	अगर (enable)
		val |= AM65_CPSW_PN_CTL_EST_PORT_EN;
	अन्यथा
		val &= ~AM65_CPSW_PN_CTL_EST_PORT_EN;

	ग_लिखोl(val, port->port_base + AM65_CPSW_PN_REG_CTL);
पूर्ण

/* target new EST RAM buffer, actual toggle happens after cycle completion */
अटल व्योम am65_cpsw_port_est_assign_buf_num(काष्ठा net_device *ndev,
					      पूर्णांक buf_num)
अणु
	काष्ठा am65_cpsw_port *port = am65_ndev_to_port(ndev);
	u32 val;

	val = पढ़ोl(port->port_base + AM65_CPSW_PN_REG_EST_CTL);
	अगर (buf_num)
		val |= AM65_CPSW_PN_EST_BUFSEL;
	अन्यथा
		val &= ~AM65_CPSW_PN_EST_BUFSEL;

	ग_लिखोl(val, port->port_base + AM65_CPSW_PN_REG_EST_CTL);
पूर्ण

/* am65_cpsw_port_est_is_swapped() - Indicate अगर h/w is transitioned
 * admin -> oper or not
 *
 * Return true अगर alपढ़ोy transitioned. i.e oper is equal to admin and buf
 * numbers match (est_oper->buf match with est_admin->buf).
 * false अगर beक्रमe transition. i.e oper is not equal to admin, (i.e a
 * previous admin command is रुकोing to be transitioned to oper state
 * and est_oper->buf not match with est_oper->buf).
 */
अटल पूर्णांक am65_cpsw_port_est_is_swapped(काष्ठा net_device *ndev, पूर्णांक *oper,
					 पूर्णांक *admin)
अणु
	काष्ठा am65_cpsw_port *port = am65_ndev_to_port(ndev);
	u32 val;

	val = पढ़ोl(port->port_base + AM65_CPSW_PN_REG_FIFO_STATUS);
	*oper = !!(val & AM65_CPSW_PN_FST_EST_BUFACT);

	val = पढ़ोl(port->port_base + AM65_CPSW_PN_REG_EST_CTL);
	*admin = !!(val & AM65_CPSW_PN_EST_BUFSEL);

	वापस *admin == *oper;
पूर्ण

/* am65_cpsw_port_est_get_मुक्त_buf_num() - Get मुक्त buffer number क्रम
 * Admin to program the new schedule.
 *
 * Logic as follows:-
 * If oper is same as admin, वापस the other buffer (!oper) as the admin
 * buffer.  If oper is not the same, driver let the current oper to जारी
 * as it is in the process of transitioning from admin -> oper. So keep the
 * oper by selecting the same oper buffer by writing to EST_BUFSEL bit in
 * EST CTL रेजिस्टर. In the second iteration they will match and code वापसs.
 * The actual buffer to ग_लिखो command is selected later beक्रमe it is पढ़ोy
 * to update the schedule.
 */
अटल पूर्णांक am65_cpsw_port_est_get_मुक्त_buf_num(काष्ठा net_device *ndev)
अणु
	पूर्णांक oper, admin;
	पूर्णांक roll = 2;

	जबतक (roll--) अणु
		अगर (am65_cpsw_port_est_is_swapped(ndev, &oper, &admin))
			वापस !oper;

		/* admin is not set, so hinder transition as it's not allowed
		 * to touch memory in-flight, by targeting same oper buf.
		 */
		am65_cpsw_port_est_assign_buf_num(ndev, oper);

		dev_info(&ndev->dev,
			 "Prev. EST admin cycle is in transit %d -> %d\n",
			 oper, admin);
	पूर्ण

	वापस admin;
पूर्ण

अटल व्योम am65_cpsw_admin_to_oper(काष्ठा net_device *ndev)
अणु
	काष्ठा am65_cpsw_port *port = am65_ndev_to_port(ndev);

	अगर (port->qos.est_oper)
		devm_kमुक्त(&ndev->dev, port->qos.est_oper);

	port->qos.est_oper = port->qos.est_admin;
	port->qos.est_admin = शून्य;
पूर्ण

अटल व्योम am65_cpsw_port_est_get_buf_num(काष्ठा net_device *ndev,
					   काष्ठा am65_cpsw_est *est_new)
अणु
	काष्ठा am65_cpsw_port *port = am65_ndev_to_port(ndev);
	u32 val;

	val = पढ़ोl(port->port_base + AM65_CPSW_PN_REG_EST_CTL);
	val &= ~AM65_CPSW_PN_EST_ONEBUF;
	ग_लिखोl(val, port->port_base + AM65_CPSW_PN_REG_EST_CTL);

	est_new->buf = am65_cpsw_port_est_get_मुक्त_buf_num(ndev);

	/* rolled buf num means changed buf जबतक configuring */
	अगर (port->qos.est_oper && port->qos.est_admin &&
	    est_new->buf == port->qos.est_oper->buf)
		am65_cpsw_admin_to_oper(ndev);
पूर्ण

अटल व्योम am65_cpsw_est_set(काष्ठा net_device *ndev, पूर्णांक enable)
अणु
	काष्ठा am65_cpsw_port *port = am65_ndev_to_port(ndev);
	काष्ठा am65_cpsw_common *common = port->common;
	पूर्णांक common_enable = 0;
	पूर्णांक i;

	am65_cpsw_port_est_enable(port, enable);

	क्रम (i = 0; i < common->port_num; i++)
		common_enable |= am65_cpsw_port_est_enabled(&common->ports[i]);

	common_enable |= enable;
	am65_cpsw_est_enable(common, common_enable);
पूर्ण

/* This update is supposed to be used in any routine beक्रमe getting real state
 * of admin -> oper transition, particularly it's supposed to be used in some
 * generic routine क्रम providing real state to Taprio Qdisc.
 */
अटल व्योम am65_cpsw_est_update_state(काष्ठा net_device *ndev)
अणु
	काष्ठा am65_cpsw_port *port = am65_ndev_to_port(ndev);
	पूर्णांक oper, admin;

	अगर (!port->qos.est_admin)
		वापस;

	अगर (!am65_cpsw_port_est_is_swapped(ndev, &oper, &admin))
		वापस;

	am65_cpsw_admin_to_oper(ndev);
पूर्ण

/* Fetch command count it's number of bytes in Gigabit mode or nibbles in
 * 10/100Mb mode. So, having speed and समय in ns, recalculate ns to number of
 * bytes/nibbles that can be sent जबतक transmission on given speed.
 */
अटल पूर्णांक am65_est_cmd_ns_to_cnt(u64 ns, पूर्णांक link_speed)
अणु
	u64 temp;

	temp = ns * link_speed;
	अगर (link_speed < SPEED_1000)
		temp <<= 1;

	वापस DIV_ROUND_UP(temp, 8 * 1000);
पूर्ण

अटल व्योम __iomem *am65_cpsw_est_set_sched_cmds(व्योम __iomem *addr,
						  पूर्णांक fetch_cnt,
						  पूर्णांक fetch_allow)
अणु
	u32 prio_mask, cmd_fetch_cnt, cmd;

	करो अणु
		अगर (fetch_cnt > AM65_CPSW_FETCH_CNT_MAX) अणु
			fetch_cnt -= AM65_CPSW_FETCH_CNT_MAX;
			cmd_fetch_cnt = AM65_CPSW_FETCH_CNT_MAX;
		पूर्ण अन्यथा अणु
			cmd_fetch_cnt = fetch_cnt;
			/* fetch count can't be less than 16? */
			अगर (cmd_fetch_cnt && cmd_fetch_cnt < 16)
				cmd_fetch_cnt = 16;

			fetch_cnt = 0;
		पूर्ण

		prio_mask = fetch_allow & AM65_CPSW_FETCH_ALLOW_MSK;
		cmd = (cmd_fetch_cnt << AM65_CPSW_FETCH_CNT_OFFSET) | prio_mask;

		ग_लिखोl(cmd, addr);
		addr += 4;
	पूर्ण जबतक (fetch_cnt);

	वापस addr;
पूर्ण

अटल पूर्णांक am65_cpsw_est_calc_cmd_num(काष्ठा net_device *ndev,
				      काष्ठा tc_taprio_qopt_offload *taprio,
				      पूर्णांक link_speed)
अणु
	पूर्णांक i, cmd_cnt, cmd_sum = 0;
	u32 fetch_cnt;

	क्रम (i = 0; i < taprio->num_entries; i++) अणु
		अगर (taprio->entries[i].command != TC_TAPRIO_CMD_SET_GATES) अणु
			dev_err(&ndev->dev, "Only SET command is supported");
			वापस -EINVAL;
		पूर्ण

		fetch_cnt = am65_est_cmd_ns_to_cnt(taprio->entries[i].पूर्णांकerval,
						   link_speed);

		cmd_cnt = DIV_ROUND_UP(fetch_cnt, AM65_CPSW_FETCH_CNT_MAX);
		अगर (!cmd_cnt)
			cmd_cnt++;

		cmd_sum += cmd_cnt;

		अगर (!fetch_cnt)
			अवरोध;
	पूर्ण

	वापस cmd_sum;
पूर्ण

अटल पूर्णांक am65_cpsw_est_check_scheds(काष्ठा net_device *ndev,
				      काष्ठा am65_cpsw_est *est_new)
अणु
	काष्ठा am65_cpsw_port *port = am65_ndev_to_port(ndev);
	पूर्णांक cmd_num;

	cmd_num = am65_cpsw_est_calc_cmd_num(ndev, &est_new->taprio,
					     port->qos.link_speed);
	अगर (cmd_num < 0)
		वापस cmd_num;

	अगर (cmd_num > AM65_CPSW_FETCH_RAM_CMD_NUM / 2) अणु
		dev_err(&ndev->dev, "No fetch RAM");
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम am65_cpsw_est_set_sched_list(काष्ठा net_device *ndev,
					 काष्ठा am65_cpsw_est *est_new)
अणु
	काष्ठा am65_cpsw_port *port = am65_ndev_to_port(ndev);
	u32 fetch_cnt, fetch_allow, all_fetch_allow = 0;
	व्योम __iomem *ram_addr, *max_ram_addr;
	काष्ठा tc_taprio_sched_entry *entry;
	पूर्णांक i, ram_size;

	ram_addr = port->fetch_ram_base;
	ram_size = AM65_CPSW_FETCH_RAM_CMD_NUM * 2;
	ram_addr += est_new->buf * ram_size;

	max_ram_addr = ram_size + ram_addr;
	क्रम (i = 0; i < est_new->taprio.num_entries; i++) अणु
		entry = &est_new->taprio.entries[i];

		fetch_cnt = am65_est_cmd_ns_to_cnt(entry->पूर्णांकerval,
						   port->qos.link_speed);
		fetch_allow = entry->gate_mask;
		अगर (fetch_allow > AM65_CPSW_FETCH_ALLOW_MAX)
			dev_dbg(&ndev->dev, "fetch_allow > 8 bits: %d\n",
				fetch_allow);

		ram_addr = am65_cpsw_est_set_sched_cmds(ram_addr, fetch_cnt,
							fetch_allow);

		अगर (!fetch_cnt && i < est_new->taprio.num_entries - 1) अणु
			dev_info(&ndev->dev,
				 "next scheds after %d have no impact", i + 1);
			अवरोध;
		पूर्ण

		all_fetch_allow |= fetch_allow;
	पूर्ण

	/* end cmd, enabling non-समयd queues क्रम potential over cycle समय */
	अगर (ram_addr < max_ram_addr)
		ग_लिखोl(~all_fetch_allow & AM65_CPSW_FETCH_ALLOW_MSK, ram_addr);
पूर्ण

/*
 * Enable ESTf periodic output, set cycle start समय and पूर्णांकerval.
 */
अटल पूर्णांक am65_cpsw_समयr_set(काष्ठा net_device *ndev,
			       काष्ठा am65_cpsw_est *est_new)
अणु
	काष्ठा am65_cpsw_port *port = am65_ndev_to_port(ndev);
	काष्ठा am65_cpsw_common *common = port->common;
	काष्ठा am65_cpts *cpts = common->cpts;
	काष्ठा am65_cpts_estf_cfg cfg;

	cfg.ns_period = est_new->taprio.cycle_समय;
	cfg.ns_start = est_new->taprio.base_समय;

	वापस am65_cpts_estf_enable(cpts, port->port_id - 1, &cfg);
पूर्ण

अटल व्योम am65_cpsw_समयr_stop(काष्ठा net_device *ndev)
अणु
	काष्ठा am65_cpsw_port *port = am65_ndev_to_port(ndev);
	काष्ठा am65_cpts *cpts = port->common->cpts;

	am65_cpts_estf_disable(cpts, port->port_id - 1);
पूर्ण

अटल क्रमागत समयr_act am65_cpsw_समयr_act(काष्ठा net_device *ndev,
					  काष्ठा am65_cpsw_est *est_new)
अणु
	काष्ठा tc_taprio_qopt_offload *taprio_oper, *taprio_new;
	काष्ठा am65_cpsw_port *port = am65_ndev_to_port(ndev);
	काष्ठा am65_cpts *cpts = port->common->cpts;
	u64 cur_समय;
	s64 dअगरf;

	अगर (!port->qos.est_oper)
		वापस TACT_PROG;

	taprio_new = &est_new->taprio;
	taprio_oper = &port->qos.est_oper->taprio;

	अगर (taprio_new->cycle_समय != taprio_oper->cycle_समय)
		वापस TACT_NEED_STOP;

	/* in order to aव्योम समयr reset get base_समय क्रमm oper taprio */
	अगर (!taprio_new->base_समय && taprio_oper)
		taprio_new->base_समय = taprio_oper->base_समय;

	अगर (taprio_new->base_समय == taprio_oper->base_समय)
		वापस TACT_SKIP_PROG;

	/* base बार are cycle synchronized */
	dअगरf = taprio_new->base_समय - taprio_oper->base_समय;
	dअगरf = dअगरf < 0 ? -dअगरf : dअगरf;
	अगर (dअगरf % taprio_new->cycle_समय)
		वापस TACT_NEED_STOP;

	cur_समय = am65_cpts_ns_समय_लो(cpts);
	अगर (taprio_new->base_समय <= cur_समय + taprio_new->cycle_समय)
		वापस TACT_SKIP_PROG;

	/* TODO: Admin schedule at future समय is not currently supported */
	वापस TACT_NEED_STOP;
पूर्ण

अटल व्योम am65_cpsw_stop_est(काष्ठा net_device *ndev)
अणु
	am65_cpsw_est_set(ndev, 0);
	am65_cpsw_समयr_stop(ndev);
पूर्ण

अटल व्योम am65_cpsw_purge_est(काष्ठा net_device *ndev)
अणु
	काष्ठा am65_cpsw_port *port = am65_ndev_to_port(ndev);

	am65_cpsw_stop_est(ndev);

	अगर (port->qos.est_admin)
		devm_kमुक्त(&ndev->dev, port->qos.est_admin);

	अगर (port->qos.est_oper)
		devm_kमुक्त(&ndev->dev, port->qos.est_oper);

	port->qos.est_oper = शून्य;
	port->qos.est_admin = शून्य;
पूर्ण

अटल पूर्णांक am65_cpsw_configure_taprio(काष्ठा net_device *ndev,
				      काष्ठा am65_cpsw_est *est_new)
अणु
	काष्ठा am65_cpsw_common *common = am65_ndev_to_common(ndev);
	काष्ठा am65_cpts *cpts = common->cpts;
	पूर्णांक ret = 0, tact = TACT_PROG;

	am65_cpsw_est_update_state(ndev);

	अगर (!est_new->taprio.enable) अणु
		am65_cpsw_stop_est(ndev);
		वापस ret;
	पूर्ण

	ret = am65_cpsw_est_check_scheds(ndev, est_new);
	अगर (ret < 0)
		वापस ret;

	tact = am65_cpsw_समयr_act(ndev, est_new);
	अगर (tact == TACT_NEED_STOP) अणु
		dev_err(&ndev->dev,
			"Can't toggle estf timer, stop taprio first");
		वापस -EINVAL;
	पूर्ण

	अगर (tact == TACT_PROG)
		am65_cpsw_समयr_stop(ndev);

	अगर (!est_new->taprio.base_समय)
		est_new->taprio.base_समय = am65_cpts_ns_समय_लो(cpts);

	am65_cpsw_port_est_get_buf_num(ndev, est_new);
	am65_cpsw_est_set_sched_list(ndev, est_new);
	am65_cpsw_port_est_assign_buf_num(ndev, est_new->buf);

	am65_cpsw_est_set(ndev, est_new->taprio.enable);

	अगर (tact == TACT_PROG) अणु
		ret = am65_cpsw_समयr_set(ndev, est_new);
		अगर (ret) अणु
			dev_err(&ndev->dev, "Failed to set cycle time");
			वापस ret;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम am65_cpsw_cp_taprio(काष्ठा tc_taprio_qopt_offload *from,
				काष्ठा tc_taprio_qopt_offload *to)
अणु
	पूर्णांक i;

	*to = *from;
	क्रम (i = 0; i < from->num_entries; i++)
		to->entries[i] = from->entries[i];
पूर्ण

अटल पूर्णांक am65_cpsw_set_taprio(काष्ठा net_device *ndev, व्योम *type_data)
अणु
	काष्ठा am65_cpsw_port *port = am65_ndev_to_port(ndev);
	काष्ठा tc_taprio_qopt_offload *taprio = type_data;
	काष्ठा am65_cpsw_est *est_new;
	पूर्णांक ret = 0;

	अगर (taprio->cycle_समय_extension) अणु
		dev_err(&ndev->dev, "Failed to set cycle time extension");
		वापस -EOPNOTSUPP;
	पूर्ण

	est_new = devm_kzalloc(&ndev->dev,
			       काष्ठा_size(est_new, taprio.entries, taprio->num_entries),
			       GFP_KERNEL);
	अगर (!est_new)
		वापस -ENOMEM;

	am65_cpsw_cp_taprio(taprio, &est_new->taprio);
	ret = am65_cpsw_configure_taprio(ndev, est_new);
	अगर (!ret) अणु
		अगर (taprio->enable) अणु
			अगर (port->qos.est_admin)
				devm_kमुक्त(&ndev->dev, port->qos.est_admin);

			port->qos.est_admin = est_new;
		पूर्ण अन्यथा अणु
			devm_kमुक्त(&ndev->dev, est_new);
			am65_cpsw_purge_est(ndev);
		पूर्ण
	पूर्ण अन्यथा अणु
		devm_kमुक्त(&ndev->dev, est_new);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम am65_cpsw_est_link_up(काष्ठा net_device *ndev, पूर्णांक link_speed)
अणु
	काष्ठा am65_cpsw_port *port = am65_ndev_to_port(ndev);
	kसमय_प्रकार cur_समय;
	s64 delta;

	port->qos.link_speed = link_speed;
	अगर (!am65_cpsw_port_est_enabled(port))
		वापस;

	अगर (port->qos.link_करोwn_समय) अणु
		cur_समय = kसमय_get();
		delta = kसमय_us_delta(cur_समय, port->qos.link_करोwn_समय);
		अगर (delta > USEC_PER_SEC) अणु
			dev_err(&ndev->dev,
				"Link has been lost too long, stopping TAS");
			जाओ purge_est;
		पूर्ण
	पूर्ण

	वापस;

purge_est:
	am65_cpsw_purge_est(ndev);
पूर्ण

अटल पूर्णांक am65_cpsw_setup_taprio(काष्ठा net_device *ndev, व्योम *type_data)
अणु
	काष्ठा am65_cpsw_port *port = am65_ndev_to_port(ndev);
	काष्ठा am65_cpsw_common *common = port->common;

	अगर (!IS_ENABLED(CONFIG_TI_AM65_CPSW_TAS))
		वापस -ENODEV;

	अगर (!netअगर_running(ndev)) अणु
		dev_err(&ndev->dev, "interface is down, link speed unknown\n");
		वापस -ENETDOWN;
	पूर्ण

	अगर (common->pf_p0_rx_ptype_rrobin) अणु
		dev_err(&ndev->dev,
			"p0-rx-ptype-rrobin flag conflicts with taprio qdisc\n");
		वापस -EINVAL;
	पूर्ण

	अगर (port->qos.link_speed == SPEED_UNKNOWN)
		वापस -ENOLINK;

	वापस am65_cpsw_set_taprio(ndev, type_data);
पूर्ण

पूर्णांक am65_cpsw_qos_nकरो_setup_tc(काष्ठा net_device *ndev, क्रमागत tc_setup_type type,
			       व्योम *type_data)
अणु
	चयन (type) अणु
	हाल TC_SETUP_QDISC_TAPRIO:
		वापस am65_cpsw_setup_taprio(ndev, type_data);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

व्योम am65_cpsw_qos_link_up(काष्ठा net_device *ndev, पूर्णांक link_speed)
अणु
	काष्ठा am65_cpsw_port *port = am65_ndev_to_port(ndev);

	अगर (!IS_ENABLED(CONFIG_TI_AM65_CPSW_TAS))
		वापस;

	am65_cpsw_est_link_up(ndev, link_speed);
	port->qos.link_करोwn_समय = 0;
पूर्ण

व्योम am65_cpsw_qos_link_करोwn(काष्ठा net_device *ndev)
अणु
	काष्ठा am65_cpsw_port *port = am65_ndev_to_port(ndev);

	अगर (!IS_ENABLED(CONFIG_TI_AM65_CPSW_TAS))
		वापस;

	अगर (!port->qos.link_करोwn_समय)
		port->qos.link_करोwn_समय = kसमय_get();

	port->qos.link_speed = SPEED_UNKNOWN;
पूर्ण
