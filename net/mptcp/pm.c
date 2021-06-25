<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Multipath TCP
 *
 * Copyright (c) 2019, Intel Corporation.
 */
#घोषणा pr_fmt(fmt) "MPTCP: " fmt

#समावेश <linux/kernel.h>
#समावेश <net/tcp.h>
#समावेश <net/mptcp.h>
#समावेश "protocol.h"

/* path manager command handlers */

पूर्णांक mptcp_pm_announce_addr(काष्ठा mptcp_sock *msk,
			   स्थिर काष्ठा mptcp_addr_info *addr,
			   bool echo)
अणु
	u8 add_addr = READ_ONCE(msk->pm.addr_संकेत);

	pr_debug("msk=%p, local_id=%d", msk, addr->id);

	lockdep_निश्चित_held(&msk->pm.lock);

	अगर (add_addr) अणु
		pr_warn("addr_signal error, add_addr=%d", add_addr);
		वापस -EINVAL;
	पूर्ण

	msk->pm.local = *addr;
	add_addr |= BIT(MPTCP_ADD_ADDR_SIGNAL);
	अगर (echo)
		add_addr |= BIT(MPTCP_ADD_ADDR_ECHO);
	अगर (addr->family == AF_INET6)
		add_addr |= BIT(MPTCP_ADD_ADDR_IPV6);
	अगर (addr->port)
		add_addr |= BIT(MPTCP_ADD_ADDR_PORT);
	WRITE_ONCE(msk->pm.addr_संकेत, add_addr);
	वापस 0;
पूर्ण

पूर्णांक mptcp_pm_हटाओ_addr(काष्ठा mptcp_sock *msk, स्थिर काष्ठा mptcp_rm_list *rm_list)
अणु
	u8 rm_addr = READ_ONCE(msk->pm.addr_संकेत);

	pr_debug("msk=%p, rm_list_nr=%d", msk, rm_list->nr);

	अगर (rm_addr) अणु
		pr_warn("addr_signal error, rm_addr=%d", rm_addr);
		वापस -EINVAL;
	पूर्ण

	msk->pm.rm_list_tx = *rm_list;
	rm_addr |= BIT(MPTCP_RM_ADDR_SIGNAL);
	WRITE_ONCE(msk->pm.addr_संकेत, rm_addr);
	mptcp_pm_nl_addr_send_ack(msk);
	वापस 0;
पूर्ण

पूर्णांक mptcp_pm_हटाओ_subflow(काष्ठा mptcp_sock *msk, स्थिर काष्ठा mptcp_rm_list *rm_list)
अणु
	pr_debug("msk=%p, rm_list_nr=%d", msk, rm_list->nr);

	spin_lock_bh(&msk->pm.lock);
	mptcp_pm_nl_rm_subflow_received(msk, rm_list);
	spin_unlock_bh(&msk->pm.lock);
	वापस 0;
पूर्ण

/* path manager event handlers */

व्योम mptcp_pm_new_connection(काष्ठा mptcp_sock *msk, स्थिर काष्ठा sock *ssk, पूर्णांक server_side)
अणु
	काष्ठा mptcp_pm_data *pm = &msk->pm;

	pr_debug("msk=%p, token=%u side=%d", msk, msk->token, server_side);

	WRITE_ONCE(pm->server_side, server_side);
	mptcp_event(MPTCP_EVENT_CREATED, msk, ssk, GFP_ATOMIC);
पूर्ण

bool mptcp_pm_allow_new_subflow(काष्ठा mptcp_sock *msk)
अणु
	काष्ठा mptcp_pm_data *pm = &msk->pm;
	अचिन्हित पूर्णांक subflows_max;
	पूर्णांक ret = 0;

	subflows_max = mptcp_pm_get_subflows_max(msk);

	pr_debug("msk=%p subflows=%d max=%d allow=%d", msk, pm->subflows,
		 subflows_max, READ_ONCE(pm->accept_subflow));

	/* try to aव्योम acquiring the lock below */
	अगर (!READ_ONCE(pm->accept_subflow))
		वापस false;

	spin_lock_bh(&pm->lock);
	अगर (READ_ONCE(pm->accept_subflow)) अणु
		ret = pm->subflows < subflows_max;
		अगर (ret && ++pm->subflows == subflows_max)
			WRITE_ONCE(pm->accept_subflow, false);
	पूर्ण
	spin_unlock_bh(&pm->lock);

	वापस ret;
पूर्ण

/* वापस true अगर the new status bit is currently cleared, that is, this event
 * can be server, eventually by an alपढ़ोy scheduled work
 */
अटल bool mptcp_pm_schedule_work(काष्ठा mptcp_sock *msk,
				   क्रमागत mptcp_pm_status new_status)
अणु
	pr_debug("msk=%p status=%x new=%lx", msk, msk->pm.status,
		 BIT(new_status));
	अगर (msk->pm.status & BIT(new_status))
		वापस false;

	msk->pm.status |= BIT(new_status);
	mptcp_schedule_work((काष्ठा sock *)msk);
	वापस true;
पूर्ण

व्योम mptcp_pm_fully_established(काष्ठा mptcp_sock *msk, स्थिर काष्ठा sock *ssk, gfp_t gfp)
अणु
	काष्ठा mptcp_pm_data *pm = &msk->pm;
	bool announce = false;

	pr_debug("msk=%p", msk);

	spin_lock_bh(&pm->lock);

	/* mptcp_pm_fully_established() can be invoked by multiple
	 * racing paths - accept() and check_fully_established()
	 * be sure to serve this event only once.
	 */
	अगर (READ_ONCE(pm->work_pending) &&
	    !(msk->pm.status & BIT(MPTCP_PM_ALREADY_ESTABLISHED)))
		mptcp_pm_schedule_work(msk, MPTCP_PM_ESTABLISHED);

	अगर ((msk->pm.status & BIT(MPTCP_PM_ALREADY_ESTABLISHED)) == 0)
		announce = true;

	msk->pm.status |= BIT(MPTCP_PM_ALREADY_ESTABLISHED);
	spin_unlock_bh(&pm->lock);

	अगर (announce)
		mptcp_event(MPTCP_EVENT_ESTABLISHED, msk, ssk, gfp);
पूर्ण

व्योम mptcp_pm_connection_बंदd(काष्ठा mptcp_sock *msk)
अणु
	pr_debug("msk=%p", msk);
पूर्ण

व्योम mptcp_pm_subflow_established(काष्ठा mptcp_sock *msk)
अणु
	काष्ठा mptcp_pm_data *pm = &msk->pm;

	pr_debug("msk=%p", msk);

	अगर (!READ_ONCE(pm->work_pending))
		वापस;

	spin_lock_bh(&pm->lock);

	अगर (READ_ONCE(pm->work_pending))
		mptcp_pm_schedule_work(msk, MPTCP_PM_SUBFLOW_ESTABLISHED);

	spin_unlock_bh(&pm->lock);
पूर्ण

व्योम mptcp_pm_subflow_बंदd(काष्ठा mptcp_sock *msk, u8 id)
अणु
	pr_debug("msk=%p", msk);
पूर्ण

व्योम mptcp_pm_add_addr_received(काष्ठा mptcp_sock *msk,
				स्थिर काष्ठा mptcp_addr_info *addr)
अणु
	काष्ठा mptcp_pm_data *pm = &msk->pm;

	pr_debug("msk=%p remote_id=%d accept=%d", msk, addr->id,
		 READ_ONCE(pm->accept_addr));

	mptcp_event_addr_announced(msk, addr);

	spin_lock_bh(&pm->lock);

	अगर (!READ_ONCE(pm->accept_addr)) अणु
		mptcp_pm_announce_addr(msk, addr, true);
		mptcp_pm_add_addr_send_ack(msk);
	पूर्ण अन्यथा अगर (mptcp_pm_schedule_work(msk, MPTCP_PM_ADD_ADDR_RECEIVED)) अणु
		pm->remote = *addr;
	पूर्ण

	spin_unlock_bh(&pm->lock);
पूर्ण

व्योम mptcp_pm_add_addr_echoed(काष्ठा mptcp_sock *msk,
			      काष्ठा mptcp_addr_info *addr)
अणु
	काष्ठा mptcp_pm_data *pm = &msk->pm;

	pr_debug("msk=%p", msk);

	spin_lock_bh(&pm->lock);

	अगर (mptcp_lookup_anno_list_by_saddr(msk, addr) && READ_ONCE(pm->work_pending))
		mptcp_pm_schedule_work(msk, MPTCP_PM_SUBFLOW_ESTABLISHED);

	spin_unlock_bh(&pm->lock);
पूर्ण

व्योम mptcp_pm_add_addr_send_ack(काष्ठा mptcp_sock *msk)
अणु
	अगर (!mptcp_pm_should_add_संकेत(msk))
		वापस;

	mptcp_pm_schedule_work(msk, MPTCP_PM_ADD_ADDR_SEND_ACK);
पूर्ण

व्योम mptcp_pm_rm_addr_received(काष्ठा mptcp_sock *msk,
			       स्थिर काष्ठा mptcp_rm_list *rm_list)
अणु
	काष्ठा mptcp_pm_data *pm = &msk->pm;
	u8 i;

	pr_debug("msk=%p remote_ids_nr=%d", msk, rm_list->nr);

	क्रम (i = 0; i < rm_list->nr; i++)
		mptcp_event_addr_हटाओd(msk, rm_list->ids[i]);

	spin_lock_bh(&pm->lock);
	mptcp_pm_schedule_work(msk, MPTCP_PM_RM_ADDR_RECEIVED);
	pm->rm_list_rx = *rm_list;
	spin_unlock_bh(&pm->lock);
पूर्ण

व्योम mptcp_pm_mp_prio_received(काष्ठा sock *sk, u8 bkup)
अणु
	काष्ठा mptcp_subflow_context *subflow = mptcp_subflow_ctx(sk);

	pr_debug("subflow->backup=%d, bkup=%d\n", subflow->backup, bkup);
	subflow->backup = bkup;

	mptcp_event(MPTCP_EVENT_SUB_PRIORITY, mptcp_sk(subflow->conn), sk, GFP_ATOMIC);
पूर्ण

/* path manager helpers */

bool mptcp_pm_add_addr_संकेत(काष्ठा mptcp_sock *msk, अचिन्हित पूर्णांक reमुख्यing,
			      काष्ठा mptcp_addr_info *saddr, bool *echo, bool *port)
अणु
	पूर्णांक ret = false;

	spin_lock_bh(&msk->pm.lock);

	/* द्विगुन check after the lock is acquired */
	अगर (!mptcp_pm_should_add_संकेत(msk))
		जाओ out_unlock;

	*echo = mptcp_pm_should_add_संकेत_echo(msk);
	*port = mptcp_pm_should_add_संकेत_port(msk);

	अगर (reमुख्यing < mptcp_add_addr_len(msk->pm.local.family, *echo, *port))
		जाओ out_unlock;

	*saddr = msk->pm.local;
	WRITE_ONCE(msk->pm.addr_संकेत, 0);
	ret = true;

out_unlock:
	spin_unlock_bh(&msk->pm.lock);
	वापस ret;
पूर्ण

bool mptcp_pm_rm_addr_संकेत(काष्ठा mptcp_sock *msk, अचिन्हित पूर्णांक reमुख्यing,
			     काष्ठा mptcp_rm_list *rm_list)
अणु
	पूर्णांक ret = false, len;

	spin_lock_bh(&msk->pm.lock);

	/* द्विगुन check after the lock is acquired */
	अगर (!mptcp_pm_should_rm_संकेत(msk))
		जाओ out_unlock;

	len = mptcp_rm_addr_len(&msk->pm.rm_list_tx);
	अगर (len < 0) अणु
		WRITE_ONCE(msk->pm.addr_संकेत, 0);
		जाओ out_unlock;
	पूर्ण
	अगर (reमुख्यing < len)
		जाओ out_unlock;

	*rm_list = msk->pm.rm_list_tx;
	WRITE_ONCE(msk->pm.addr_संकेत, 0);
	ret = true;

out_unlock:
	spin_unlock_bh(&msk->pm.lock);
	वापस ret;
पूर्ण

पूर्णांक mptcp_pm_get_local_id(काष्ठा mptcp_sock *msk, काष्ठा sock_common *skc)
अणु
	वापस mptcp_pm_nl_get_local_id(msk, skc);
पूर्ण

व्योम mptcp_pm_data_init(काष्ठा mptcp_sock *msk)
अणु
	msk->pm.add_addr_संकेतed = 0;
	msk->pm.add_addr_accepted = 0;
	msk->pm.local_addr_used = 0;
	msk->pm.subflows = 0;
	msk->pm.rm_list_tx.nr = 0;
	msk->pm.rm_list_rx.nr = 0;
	WRITE_ONCE(msk->pm.work_pending, false);
	WRITE_ONCE(msk->pm.addr_संकेत, 0);
	WRITE_ONCE(msk->pm.accept_addr, false);
	WRITE_ONCE(msk->pm.accept_subflow, false);
	msk->pm.status = 0;

	spin_lock_init(&msk->pm.lock);
	INIT_LIST_HEAD(&msk->pm.anno_list);

	mptcp_pm_nl_data_init(msk);
पूर्ण

व्योम __init mptcp_pm_init(व्योम)
अणु
	mptcp_pm_nl_init();
पूर्ण
