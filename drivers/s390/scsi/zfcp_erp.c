<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * zfcp device driver
 *
 * Error Recovery Procedures (ERP).
 *
 * Copyright IBM Corp. 2002, 2020
 */

#घोषणा KMSG_COMPONENT "zfcp"
#घोषणा pr_fmt(fmt) KMSG_COMPONENT ": " fmt

#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/bug.h>
#समावेश "zfcp_ext.h"
#समावेश "zfcp_reqlist.h"
#समावेश "zfcp_diag.h"

#घोषणा ZFCP_MAX_ERPS                   3

क्रमागत zfcp_erp_act_flags अणु
	ZFCP_STATUS_ERP_TIMEDOUT	= 0x10000000,
	ZFCP_STATUS_ERP_CLOSE_ONLY	= 0x01000000,
	ZFCP_STATUS_ERP_DISMISSED	= 0x00200000,
	ZFCP_STATUS_ERP_LOWMEM		= 0x00400000,
	ZFCP_STATUS_ERP_NO_REF		= 0x00800000,
पूर्ण;

/*
 * Eyecatcher pseuकरो flag to bitwise or-combine with क्रमागत zfcp_erp_act_type.
 * Used to indicate that an ERP action could not be set up despite a detected
 * need क्रम some recovery.
 */
#घोषणा ZFCP_ERP_ACTION_NONE		0xc0
/*
 * Eyecatcher pseuकरो flag to bitwise or-combine with क्रमागत zfcp_erp_act_type.
 * Used to indicate that ERP not needed because the object has
 * ZFCP_STATUS_COMMON_ERP_FAILED.
 */
#घोषणा ZFCP_ERP_ACTION_FAILED		0xe0

क्रमागत zfcp_erp_act_result अणु
	ZFCP_ERP_SUCCEEDED = 0,
	ZFCP_ERP_FAILED    = 1,
	ZFCP_ERP_CONTINUES = 2,
	ZFCP_ERP_EXIT      = 3,
	ZFCP_ERP_DISMISSED = 4,
	ZFCP_ERP_NOMEM     = 5,
पूर्ण;

अटल व्योम zfcp_erp_adapter_block(काष्ठा zfcp_adapter *adapter, पूर्णांक mask)
अणु
	zfcp_erp_clear_adapter_status(adapter,
				       ZFCP_STATUS_COMMON_UNBLOCKED | mask);
पूर्ण

अटल bool zfcp_erp_action_is_running(काष्ठा zfcp_erp_action *act)
अणु
	काष्ठा zfcp_erp_action *curr_act;

	list_क्रम_each_entry(curr_act, &act->adapter->erp_running_head, list)
		अगर (act == curr_act)
			वापस true;
	वापस false;
पूर्ण

अटल व्योम zfcp_erp_action_पढ़ोy(काष्ठा zfcp_erp_action *act)
अणु
	काष्ठा zfcp_adapter *adapter = act->adapter;

	list_move(&act->list, &adapter->erp_पढ़ोy_head);
	zfcp_dbf_rec_run("erardy1", act);
	wake_up(&adapter->erp_पढ़ोy_wq);
	zfcp_dbf_rec_run("erardy2", act);
पूर्ण

अटल व्योम zfcp_erp_action_dismiss(काष्ठा zfcp_erp_action *act)
अणु
	act->status |= ZFCP_STATUS_ERP_DISMISSED;
	अगर (zfcp_erp_action_is_running(act))
		zfcp_erp_action_पढ़ोy(act);
पूर्ण

अटल व्योम zfcp_erp_action_dismiss_lun(काष्ठा scsi_device *sdev)
अणु
	काष्ठा zfcp_scsi_dev *zfcp_sdev = sdev_to_zfcp(sdev);

	अगर (atomic_पढ़ो(&zfcp_sdev->status) & ZFCP_STATUS_COMMON_ERP_INUSE)
		zfcp_erp_action_dismiss(&zfcp_sdev->erp_action);
पूर्ण

अटल व्योम zfcp_erp_action_dismiss_port(काष्ठा zfcp_port *port)
अणु
	काष्ठा scsi_device *sdev;

	अगर (atomic_पढ़ो(&port->status) & ZFCP_STATUS_COMMON_ERP_INUSE)
		zfcp_erp_action_dismiss(&port->erp_action);
	अन्यथा अणु
		spin_lock(port->adapter->scsi_host->host_lock);
		__shost_क्रम_each_device(sdev, port->adapter->scsi_host)
			अगर (sdev_to_zfcp(sdev)->port == port)
				zfcp_erp_action_dismiss_lun(sdev);
		spin_unlock(port->adapter->scsi_host->host_lock);
	पूर्ण
पूर्ण

अटल व्योम zfcp_erp_action_dismiss_adapter(काष्ठा zfcp_adapter *adapter)
अणु
	काष्ठा zfcp_port *port;

	अगर (atomic_पढ़ो(&adapter->status) & ZFCP_STATUS_COMMON_ERP_INUSE)
		zfcp_erp_action_dismiss(&adapter->erp_action);
	अन्यथा अणु
		पढ़ो_lock(&adapter->port_list_lock);
		list_क्रम_each_entry(port, &adapter->port_list, list)
		    zfcp_erp_action_dismiss_port(port);
		पढ़ो_unlock(&adapter->port_list_lock);
	पूर्ण
पूर्ण

अटल क्रमागत zfcp_erp_act_type zfcp_erp_handle_failed(
	क्रमागत zfcp_erp_act_type want, काष्ठा zfcp_adapter *adapter,
	काष्ठा zfcp_port *port,	काष्ठा scsi_device *sdev)
अणु
	क्रमागत zfcp_erp_act_type need = want;
	काष्ठा zfcp_scsi_dev *zsdev;

	चयन (want) अणु
	हाल ZFCP_ERP_ACTION_REOPEN_LUN:
		zsdev = sdev_to_zfcp(sdev);
		अगर (atomic_पढ़ो(&zsdev->status) & ZFCP_STATUS_COMMON_ERP_FAILED)
			need = 0;
		अवरोध;
	हाल ZFCP_ERP_ACTION_REOPEN_PORT_FORCED:
		अगर (atomic_पढ़ो(&port->status) & ZFCP_STATUS_COMMON_ERP_FAILED)
			need = 0;
		अवरोध;
	हाल ZFCP_ERP_ACTION_REOPEN_PORT:
		अगर (atomic_पढ़ो(&port->status) &
		    ZFCP_STATUS_COMMON_ERP_FAILED) अणु
			need = 0;
			/* ensure propagation of failed status to new devices */
			zfcp_erp_set_port_status(
				port, ZFCP_STATUS_COMMON_ERP_FAILED);
		पूर्ण
		अवरोध;
	हाल ZFCP_ERP_ACTION_REOPEN_ADAPTER:
		अगर (atomic_पढ़ो(&adapter->status) &
		    ZFCP_STATUS_COMMON_ERP_FAILED) अणु
			need = 0;
			/* ensure propagation of failed status to new devices */
			zfcp_erp_set_adapter_status(
				adapter, ZFCP_STATUS_COMMON_ERP_FAILED);
		पूर्ण
		अवरोध;
	पूर्ण

	वापस need;
पूर्ण

अटल क्रमागत zfcp_erp_act_type zfcp_erp_required_act(क्रमागत zfcp_erp_act_type want,
				 काष्ठा zfcp_adapter *adapter,
				 काष्ठा zfcp_port *port,
				 काष्ठा scsi_device *sdev)
अणु
	क्रमागत zfcp_erp_act_type need = want;
	पूर्णांक l_status, p_status, a_status;
	काष्ठा zfcp_scsi_dev *zfcp_sdev;

	चयन (want) अणु
	हाल ZFCP_ERP_ACTION_REOPEN_LUN:
		zfcp_sdev = sdev_to_zfcp(sdev);
		l_status = atomic_पढ़ो(&zfcp_sdev->status);
		अगर (l_status & ZFCP_STATUS_COMMON_ERP_INUSE)
			वापस 0;
		p_status = atomic_पढ़ो(&port->status);
		अगर (!(p_status & ZFCP_STATUS_COMMON_RUNNING) ||
		    p_status & ZFCP_STATUS_COMMON_ERP_FAILED)
			वापस 0;
		अगर (!(p_status & ZFCP_STATUS_COMMON_UNBLOCKED))
			need = ZFCP_ERP_ACTION_REOPEN_PORT;
		fallthrough;
	हाल ZFCP_ERP_ACTION_REOPEN_PORT_FORCED:
		p_status = atomic_पढ़ो(&port->status);
		अगर (!(p_status & ZFCP_STATUS_COMMON_OPEN))
			need = ZFCP_ERP_ACTION_REOPEN_PORT;
		fallthrough;
	हाल ZFCP_ERP_ACTION_REOPEN_PORT:
		p_status = atomic_पढ़ो(&port->status);
		अगर (p_status & ZFCP_STATUS_COMMON_ERP_INUSE)
			वापस 0;
		a_status = atomic_पढ़ो(&adapter->status);
		अगर (!(a_status & ZFCP_STATUS_COMMON_RUNNING) ||
		    a_status & ZFCP_STATUS_COMMON_ERP_FAILED)
			वापस 0;
		अगर (p_status & ZFCP_STATUS_COMMON_NOESC)
			वापस need;
		अगर (!(a_status & ZFCP_STATUS_COMMON_UNBLOCKED))
			need = ZFCP_ERP_ACTION_REOPEN_ADAPTER;
		fallthrough;
	हाल ZFCP_ERP_ACTION_REOPEN_ADAPTER:
		a_status = atomic_पढ़ो(&adapter->status);
		अगर (a_status & ZFCP_STATUS_COMMON_ERP_INUSE)
			वापस 0;
		अगर (!(a_status & ZFCP_STATUS_COMMON_RUNNING) &&
		    !(a_status & ZFCP_STATUS_COMMON_OPEN))
			वापस 0; /* shutकरोwn requested क्रम बंदd adapter */
	पूर्ण

	वापस need;
पूर्ण

अटल काष्ठा zfcp_erp_action *zfcp_erp_setup_act(क्रमागत zfcp_erp_act_type need,
						  u32 act_status,
						  काष्ठा zfcp_adapter *adapter,
						  काष्ठा zfcp_port *port,
						  काष्ठा scsi_device *sdev)
अणु
	काष्ठा zfcp_erp_action *erp_action;
	काष्ठा zfcp_scsi_dev *zfcp_sdev;

	अगर (WARN_ON_ONCE(need != ZFCP_ERP_ACTION_REOPEN_LUN &&
			 need != ZFCP_ERP_ACTION_REOPEN_PORT &&
			 need != ZFCP_ERP_ACTION_REOPEN_PORT_FORCED &&
			 need != ZFCP_ERP_ACTION_REOPEN_ADAPTER))
		वापस शून्य;

	चयन (need) अणु
	हाल ZFCP_ERP_ACTION_REOPEN_LUN:
		zfcp_sdev = sdev_to_zfcp(sdev);
		अगर (!(act_status & ZFCP_STATUS_ERP_NO_REF))
			अगर (scsi_device_get(sdev))
				वापस शून्य;
		atomic_or(ZFCP_STATUS_COMMON_ERP_INUSE,
				&zfcp_sdev->status);
		erp_action = &zfcp_sdev->erp_action;
		WARN_ON_ONCE(erp_action->port != port);
		WARN_ON_ONCE(erp_action->sdev != sdev);
		अगर (!(atomic_पढ़ो(&zfcp_sdev->status) &
		      ZFCP_STATUS_COMMON_RUNNING))
			act_status |= ZFCP_STATUS_ERP_CLOSE_ONLY;
		अवरोध;

	हाल ZFCP_ERP_ACTION_REOPEN_PORT:
	हाल ZFCP_ERP_ACTION_REOPEN_PORT_FORCED:
		अगर (!get_device(&port->dev))
			वापस शून्य;
		zfcp_erp_action_dismiss_port(port);
		atomic_or(ZFCP_STATUS_COMMON_ERP_INUSE, &port->status);
		erp_action = &port->erp_action;
		WARN_ON_ONCE(erp_action->port != port);
		WARN_ON_ONCE(erp_action->sdev != शून्य);
		अगर (!(atomic_पढ़ो(&port->status) & ZFCP_STATUS_COMMON_RUNNING))
			act_status |= ZFCP_STATUS_ERP_CLOSE_ONLY;
		अवरोध;

	हाल ZFCP_ERP_ACTION_REOPEN_ADAPTER:
		kref_get(&adapter->ref);
		zfcp_erp_action_dismiss_adapter(adapter);
		atomic_or(ZFCP_STATUS_COMMON_ERP_INUSE, &adapter->status);
		erp_action = &adapter->erp_action;
		WARN_ON_ONCE(erp_action->port != शून्य);
		WARN_ON_ONCE(erp_action->sdev != शून्य);
		अगर (!(atomic_पढ़ो(&adapter->status) &
		      ZFCP_STATUS_COMMON_RUNNING))
			act_status |= ZFCP_STATUS_ERP_CLOSE_ONLY;
		अवरोध;
	पूर्ण

	WARN_ON_ONCE(erp_action->adapter != adapter);
	स_रखो(&erp_action->list, 0, माप(erp_action->list));
	स_रखो(&erp_action->समयr, 0, माप(erp_action->समयr));
	erp_action->step = ZFCP_ERP_STEP_UNINITIALIZED;
	erp_action->fsf_req_id = 0;
	erp_action->type = need;
	erp_action->status = act_status;

	वापस erp_action;
पूर्ण

अटल व्योम zfcp_erp_action_enqueue(क्रमागत zfcp_erp_act_type want,
				    काष्ठा zfcp_adapter *adapter,
				    काष्ठा zfcp_port *port,
				    काष्ठा scsi_device *sdev,
				    अक्षर *dbftag, u32 act_status)
अणु
	क्रमागत zfcp_erp_act_type need;
	काष्ठा zfcp_erp_action *act;

	need = zfcp_erp_handle_failed(want, adapter, port, sdev);
	अगर (!need) अणु
		need = ZFCP_ERP_ACTION_FAILED; /* marker क्रम trace */
		जाओ out;
	पूर्ण

	अगर (!adapter->erp_thपढ़ो) अणु
		need = ZFCP_ERP_ACTION_NONE; /* marker क्रम trace */
		जाओ out;
	पूर्ण

	need = zfcp_erp_required_act(want, adapter, port, sdev);
	अगर (!need)
		जाओ out;

	act = zfcp_erp_setup_act(need, act_status, adapter, port, sdev);
	अगर (!act) अणु
		need |= ZFCP_ERP_ACTION_NONE; /* marker क्रम trace */
		जाओ out;
	पूर्ण
	atomic_or(ZFCP_STATUS_ADAPTER_ERP_PENDING, &adapter->status);
	++adapter->erp_total_count;
	list_add_tail(&act->list, &adapter->erp_पढ़ोy_head);
	wake_up(&adapter->erp_पढ़ोy_wq);
 out:
	zfcp_dbf_rec_trig(dbftag, adapter, port, sdev, want, need);
पूर्ण

व्योम zfcp_erp_port_क्रमced_no_port_dbf(अक्षर *dbftag,
				      काष्ठा zfcp_adapter *adapter,
				      u64 port_name, u32 port_id)
अणु
	अचिन्हित दीर्घ flags;
	अटल /* करोn't waste stack */ काष्ठा zfcp_port पंचांगpport;

	ग_लिखो_lock_irqsave(&adapter->erp_lock, flags);
	/* Stand-in zfcp port with fields just good enough क्रम
	 * zfcp_dbf_rec_trig() and zfcp_dbf_set_common().
	 * Under lock because पंचांगpport is अटल.
	 */
	atomic_set(&पंचांगpport.status, -1); /* unknown */
	पंचांगpport.wwpn = port_name;
	पंचांगpport.d_id = port_id;
	zfcp_dbf_rec_trig(dbftag, adapter, &पंचांगpport, शून्य,
			  ZFCP_ERP_ACTION_REOPEN_PORT_FORCED,
			  ZFCP_ERP_ACTION_NONE);
	ग_लिखो_unlock_irqrestore(&adapter->erp_lock, flags);
पूर्ण

अटल व्योम _zfcp_erp_adapter_reखोलो(काष्ठा zfcp_adapter *adapter,
				    पूर्णांक clear_mask, अक्षर *dbftag)
अणु
	zfcp_erp_adapter_block(adapter, clear_mask);
	zfcp_scsi_schedule_rports_block(adapter);

	zfcp_erp_action_enqueue(ZFCP_ERP_ACTION_REOPEN_ADAPTER,
				adapter, शून्य, शून्य, dbftag, 0);
पूर्ण

/**
 * zfcp_erp_adapter_reखोलो - Reखोलो adapter.
 * @adapter: Adapter to reखोलो.
 * @clear: Status flags to clear.
 * @dbftag: Tag क्रम debug trace event.
 */
व्योम zfcp_erp_adapter_reखोलो(काष्ठा zfcp_adapter *adapter, पूर्णांक clear,
			     अक्षर *dbftag)
अणु
	अचिन्हित दीर्घ flags;

	zfcp_erp_adapter_block(adapter, clear);
	zfcp_scsi_schedule_rports_block(adapter);

	ग_लिखो_lock_irqsave(&adapter->erp_lock, flags);
	zfcp_erp_action_enqueue(ZFCP_ERP_ACTION_REOPEN_ADAPTER, adapter,
				शून्य, शून्य, dbftag, 0);
	ग_लिखो_unlock_irqrestore(&adapter->erp_lock, flags);
पूर्ण

/**
 * zfcp_erp_adapter_shutकरोwn - Shutकरोwn adapter.
 * @adapter: Adapter to shut करोwn.
 * @clear: Status flags to clear.
 * @dbftag: Tag क्रम debug trace event.
 */
व्योम zfcp_erp_adapter_shutकरोwn(काष्ठा zfcp_adapter *adapter, पूर्णांक clear,
			       अक्षर *dbftag)
अणु
	पूर्णांक flags = ZFCP_STATUS_COMMON_RUNNING | ZFCP_STATUS_COMMON_ERP_FAILED;
	zfcp_erp_adapter_reखोलो(adapter, clear | flags, dbftag);
पूर्ण

/**
 * zfcp_erp_port_shutकरोwn - Shutकरोwn port
 * @port: Port to shut करोwn.
 * @clear: Status flags to clear.
 * @dbftag: Tag क्रम debug trace event.
 */
व्योम zfcp_erp_port_shutकरोwn(काष्ठा zfcp_port *port, पूर्णांक clear, अक्षर *dbftag)
अणु
	पूर्णांक flags = ZFCP_STATUS_COMMON_RUNNING | ZFCP_STATUS_COMMON_ERP_FAILED;
	zfcp_erp_port_reखोलो(port, clear | flags, dbftag);
पूर्ण

अटल व्योम zfcp_erp_port_block(काष्ठा zfcp_port *port, पूर्णांक clear)
अणु
	zfcp_erp_clear_port_status(port,
				    ZFCP_STATUS_COMMON_UNBLOCKED | clear);
पूर्ण

अटल व्योम _zfcp_erp_port_क्रमced_reखोलो(काष्ठा zfcp_port *port, पूर्णांक clear,
					 अक्षर *dbftag)
अणु
	zfcp_erp_port_block(port, clear);
	zfcp_scsi_schedule_rport_block(port);

	zfcp_erp_action_enqueue(ZFCP_ERP_ACTION_REOPEN_PORT_FORCED,
				port->adapter, port, शून्य, dbftag, 0);
पूर्ण

/**
 * zfcp_erp_port_क्रमced_reखोलो - Forced बंद of port and खोलो again
 * @port: Port to क्रमce बंद and to reखोलो.
 * @clear: Status flags to clear.
 * @dbftag: Tag क्रम debug trace event.
 */
व्योम zfcp_erp_port_क्रमced_reखोलो(काष्ठा zfcp_port *port, पूर्णांक clear,
				 अक्षर *dbftag)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा zfcp_adapter *adapter = port->adapter;

	ग_लिखो_lock_irqsave(&adapter->erp_lock, flags);
	_zfcp_erp_port_क्रमced_reखोलो(port, clear, dbftag);
	ग_लिखो_unlock_irqrestore(&adapter->erp_lock, flags);
पूर्ण

अटल व्योम _zfcp_erp_port_reखोलो(काष्ठा zfcp_port *port, पूर्णांक clear,
				  अक्षर *dbftag)
अणु
	zfcp_erp_port_block(port, clear);
	zfcp_scsi_schedule_rport_block(port);

	zfcp_erp_action_enqueue(ZFCP_ERP_ACTION_REOPEN_PORT,
				port->adapter, port, शून्य, dbftag, 0);
पूर्ण

/**
 * zfcp_erp_port_reखोलो - trigger remote port recovery
 * @port: port to recover
 * @clear: flags in port status to be cleared
 * @dbftag: Tag क्रम debug trace event.
 */
व्योम zfcp_erp_port_reखोलो(काष्ठा zfcp_port *port, पूर्णांक clear, अक्षर *dbftag)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा zfcp_adapter *adapter = port->adapter;

	ग_लिखो_lock_irqsave(&adapter->erp_lock, flags);
	_zfcp_erp_port_reखोलो(port, clear, dbftag);
	ग_लिखो_unlock_irqrestore(&adapter->erp_lock, flags);
पूर्ण

अटल व्योम zfcp_erp_lun_block(काष्ठा scsi_device *sdev, पूर्णांक clear_mask)
अणु
	zfcp_erp_clear_lun_status(sdev,
				  ZFCP_STATUS_COMMON_UNBLOCKED | clear_mask);
पूर्ण

अटल व्योम _zfcp_erp_lun_reखोलो(काष्ठा scsi_device *sdev, पूर्णांक clear,
				 अक्षर *dbftag, u32 act_status)
अणु
	काष्ठा zfcp_scsi_dev *zfcp_sdev = sdev_to_zfcp(sdev);
	काष्ठा zfcp_adapter *adapter = zfcp_sdev->port->adapter;

	zfcp_erp_lun_block(sdev, clear);

	zfcp_erp_action_enqueue(ZFCP_ERP_ACTION_REOPEN_LUN, adapter,
				zfcp_sdev->port, sdev, dbftag, act_status);
पूर्ण

/**
 * zfcp_erp_lun_reखोलो - initiate reखोलो of a LUN
 * @sdev: SCSI device / LUN to be reखोलोed
 * @clear: specअगरies flags in LUN status to be cleared
 * @dbftag: Tag क्रम debug trace event.
 *
 * Return: 0 on success, < 0 on error
 */
व्योम zfcp_erp_lun_reखोलो(काष्ठा scsi_device *sdev, पूर्णांक clear, अक्षर *dbftag)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा zfcp_scsi_dev *zfcp_sdev = sdev_to_zfcp(sdev);
	काष्ठा zfcp_port *port = zfcp_sdev->port;
	काष्ठा zfcp_adapter *adapter = port->adapter;

	ग_लिखो_lock_irqsave(&adapter->erp_lock, flags);
	_zfcp_erp_lun_reखोलो(sdev, clear, dbftag, 0);
	ग_लिखो_unlock_irqrestore(&adapter->erp_lock, flags);
पूर्ण

/**
 * zfcp_erp_lun_shutकरोwn - Shutकरोwn LUN
 * @sdev: SCSI device / LUN to shut करोwn.
 * @clear: Status flags to clear.
 * @dbftag: Tag क्रम debug trace event.
 */
व्योम zfcp_erp_lun_shutकरोwn(काष्ठा scsi_device *sdev, पूर्णांक clear, अक्षर *dbftag)
अणु
	पूर्णांक flags = ZFCP_STATUS_COMMON_RUNNING | ZFCP_STATUS_COMMON_ERP_FAILED;
	zfcp_erp_lun_reखोलो(sdev, clear | flags, dbftag);
पूर्ण

/**
 * zfcp_erp_lun_shutकरोwn_रुको - Shutकरोwn LUN and रुको क्रम erp completion
 * @sdev: SCSI device / LUN to shut करोwn.
 * @dbftag: Tag क्रम debug trace event.
 *
 * Do not acquire a reference क्रम the LUN when creating the ERP
 * action. It is safe, because this function रुकोs क्रम the ERP to
 * complete first. This allows to shutकरोwn the LUN, even when the SCSI
 * device is in the state SDEV_DEL when scsi_device_get will fail.
 */
व्योम zfcp_erp_lun_shutकरोwn_रुको(काष्ठा scsi_device *sdev, अक्षर *dbftag)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा zfcp_scsi_dev *zfcp_sdev = sdev_to_zfcp(sdev);
	काष्ठा zfcp_port *port = zfcp_sdev->port;
	काष्ठा zfcp_adapter *adapter = port->adapter;
	पूर्णांक clear = ZFCP_STATUS_COMMON_RUNNING | ZFCP_STATUS_COMMON_ERP_FAILED;

	ग_लिखो_lock_irqsave(&adapter->erp_lock, flags);
	_zfcp_erp_lun_reखोलो(sdev, clear, dbftag, ZFCP_STATUS_ERP_NO_REF);
	ग_लिखो_unlock_irqrestore(&adapter->erp_lock, flags);

	zfcp_erp_रुको(adapter);
पूर्ण

अटल पूर्णांक zfcp_erp_status_change_set(अचिन्हित दीर्घ mask, atomic_t *status)
अणु
	वापस (atomic_पढ़ो(status) ^ mask) & mask;
पूर्ण

अटल व्योम zfcp_erp_adapter_unblock(काष्ठा zfcp_adapter *adapter)
अणु
	अगर (zfcp_erp_status_change_set(ZFCP_STATUS_COMMON_UNBLOCKED,
				       &adapter->status))
		zfcp_dbf_rec_run("eraubl1", &adapter->erp_action);
	atomic_or(ZFCP_STATUS_COMMON_UNBLOCKED, &adapter->status);
पूर्ण

अटल व्योम zfcp_erp_port_unblock(काष्ठा zfcp_port *port)
अणु
	अगर (zfcp_erp_status_change_set(ZFCP_STATUS_COMMON_UNBLOCKED,
				       &port->status))
		zfcp_dbf_rec_run("erpubl1", &port->erp_action);
	atomic_or(ZFCP_STATUS_COMMON_UNBLOCKED, &port->status);
पूर्ण

अटल व्योम zfcp_erp_lun_unblock(काष्ठा scsi_device *sdev)
अणु
	काष्ठा zfcp_scsi_dev *zfcp_sdev = sdev_to_zfcp(sdev);

	अगर (zfcp_erp_status_change_set(ZFCP_STATUS_COMMON_UNBLOCKED,
				       &zfcp_sdev->status))
		zfcp_dbf_rec_run("erlubl1", &sdev_to_zfcp(sdev)->erp_action);
	atomic_or(ZFCP_STATUS_COMMON_UNBLOCKED, &zfcp_sdev->status);
पूर्ण

अटल व्योम zfcp_erp_action_to_running(काष्ठा zfcp_erp_action *erp_action)
अणु
	list_move(&erp_action->list, &erp_action->adapter->erp_running_head);
	zfcp_dbf_rec_run("erator1", erp_action);
पूर्ण

अटल व्योम zfcp_erp_strategy_check_fsfreq(काष्ठा zfcp_erp_action *act)
अणु
	काष्ठा zfcp_adapter *adapter = act->adapter;
	काष्ठा zfcp_fsf_req *req;

	अगर (!act->fsf_req_id)
		वापस;

	spin_lock(&adapter->req_list->lock);
	req = _zfcp_reqlist_find(adapter->req_list, act->fsf_req_id);
	अगर (req && req->erp_action == act) अणु
		अगर (act->status & (ZFCP_STATUS_ERP_DISMISSED |
				   ZFCP_STATUS_ERP_TIMEDOUT)) अणु
			req->status |= ZFCP_STATUS_FSFREQ_DISMISSED;
			zfcp_dbf_rec_run("erscf_1", act);
			/* lock-मुक्त concurrent access with
			 * zfcp_erp_समयout_handler()
			 */
			WRITE_ONCE(req->erp_action, शून्य);
		पूर्ण
		अगर (act->status & ZFCP_STATUS_ERP_TIMEDOUT)
			zfcp_dbf_rec_run("erscf_2", act);
		अगर (req->status & ZFCP_STATUS_FSFREQ_DISMISSED)
			act->fsf_req_id = 0;
	पूर्ण अन्यथा
		act->fsf_req_id = 0;
	spin_unlock(&adapter->req_list->lock);
पूर्ण

/**
 * zfcp_erp_notअगरy - Trigger ERP action.
 * @erp_action: ERP action to जारी.
 * @set_mask: ERP action status flags to set.
 */
व्योम zfcp_erp_notअगरy(काष्ठा zfcp_erp_action *erp_action, अचिन्हित दीर्घ set_mask)
अणु
	काष्ठा zfcp_adapter *adapter = erp_action->adapter;
	अचिन्हित दीर्घ flags;

	ग_लिखो_lock_irqsave(&adapter->erp_lock, flags);
	अगर (zfcp_erp_action_is_running(erp_action)) अणु
		erp_action->status |= set_mask;
		zfcp_erp_action_पढ़ोy(erp_action);
	पूर्ण
	ग_लिखो_unlock_irqrestore(&adapter->erp_lock, flags);
पूर्ण

/**
 * zfcp_erp_समयout_handler - Trigger ERP action from समयd out ERP request
 * @t: समयr list entry embedded in zfcp FSF request
 */
व्योम zfcp_erp_समयout_handler(काष्ठा समयr_list *t)
अणु
	काष्ठा zfcp_fsf_req *fsf_req = from_समयr(fsf_req, t, समयr);
	काष्ठा zfcp_erp_action *act;

	अगर (fsf_req->status & ZFCP_STATUS_FSFREQ_DISMISSED)
		वापस;
	/* lock-मुक्त concurrent access with zfcp_erp_strategy_check_fsfreq() */
	act = READ_ONCE(fsf_req->erp_action);
	अगर (!act)
		वापस;
	zfcp_erp_notअगरy(act, ZFCP_STATUS_ERP_TIMEDOUT);
पूर्ण

अटल व्योम zfcp_erp_memरुको_handler(काष्ठा समयr_list *t)
अणु
	काष्ठा zfcp_erp_action *act = from_समयr(act, t, समयr);

	zfcp_erp_notअगरy(act, 0);
पूर्ण

अटल व्योम zfcp_erp_strategy_memरुको(काष्ठा zfcp_erp_action *erp_action)
अणु
	समयr_setup(&erp_action->समयr, zfcp_erp_memरुको_handler, 0);
	erp_action->समयr.expires = jअगरfies + HZ;
	add_समयr(&erp_action->समयr);
पूर्ण

व्योम zfcp_erp_port_क्रमced_reखोलो_all(काष्ठा zfcp_adapter *adapter,
				     पूर्णांक clear, अक्षर *dbftag)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा zfcp_port *port;

	ग_लिखो_lock_irqsave(&adapter->erp_lock, flags);
	पढ़ो_lock(&adapter->port_list_lock);
	list_क्रम_each_entry(port, &adapter->port_list, list)
		_zfcp_erp_port_क्रमced_reखोलो(port, clear, dbftag);
	पढ़ो_unlock(&adapter->port_list_lock);
	ग_लिखो_unlock_irqrestore(&adapter->erp_lock, flags);
पूर्ण

अटल व्योम _zfcp_erp_port_reखोलो_all(काष्ठा zfcp_adapter *adapter,
				      पूर्णांक clear, अक्षर *dbftag)
अणु
	काष्ठा zfcp_port *port;

	पढ़ो_lock(&adapter->port_list_lock);
	list_क्रम_each_entry(port, &adapter->port_list, list)
		_zfcp_erp_port_reखोलो(port, clear, dbftag);
	पढ़ो_unlock(&adapter->port_list_lock);
पूर्ण

अटल व्योम _zfcp_erp_lun_reखोलो_all(काष्ठा zfcp_port *port, पूर्णांक clear,
				     अक्षर *dbftag)
अणु
	काष्ठा scsi_device *sdev;

	spin_lock(port->adapter->scsi_host->host_lock);
	__shost_क्रम_each_device(sdev, port->adapter->scsi_host)
		अगर (sdev_to_zfcp(sdev)->port == port)
			_zfcp_erp_lun_reखोलो(sdev, clear, dbftag, 0);
	spin_unlock(port->adapter->scsi_host->host_lock);
पूर्ण

अटल व्योम zfcp_erp_strategy_followup_failed(काष्ठा zfcp_erp_action *act)
अणु
	चयन (act->type) अणु
	हाल ZFCP_ERP_ACTION_REOPEN_ADAPTER:
		_zfcp_erp_adapter_reखोलो(act->adapter, 0, "ersff_1");
		अवरोध;
	हाल ZFCP_ERP_ACTION_REOPEN_PORT_FORCED:
		_zfcp_erp_port_क्रमced_reखोलो(act->port, 0, "ersff_2");
		अवरोध;
	हाल ZFCP_ERP_ACTION_REOPEN_PORT:
		_zfcp_erp_port_reखोलो(act->port, 0, "ersff_3");
		अवरोध;
	हाल ZFCP_ERP_ACTION_REOPEN_LUN:
		_zfcp_erp_lun_reखोलो(act->sdev, 0, "ersff_4", 0);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम zfcp_erp_strategy_followup_success(काष्ठा zfcp_erp_action *act)
अणु
	चयन (act->type) अणु
	हाल ZFCP_ERP_ACTION_REOPEN_ADAPTER:
		_zfcp_erp_port_reखोलो_all(act->adapter, 0, "ersfs_1");
		अवरोध;
	हाल ZFCP_ERP_ACTION_REOPEN_PORT_FORCED:
		_zfcp_erp_port_reखोलो(act->port, 0, "ersfs_2");
		अवरोध;
	हाल ZFCP_ERP_ACTION_REOPEN_PORT:
		_zfcp_erp_lun_reखोलो_all(act->port, 0, "ersfs_3");
		अवरोध;
	हाल ZFCP_ERP_ACTION_REOPEN_LUN:
		/* NOP */
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम zfcp_erp_wakeup(काष्ठा zfcp_adapter *adapter)
अणु
	अचिन्हित दीर्घ flags;

	पढ़ो_lock_irqsave(&adapter->erp_lock, flags);
	अगर (list_empty(&adapter->erp_पढ़ोy_head) &&
	    list_empty(&adapter->erp_running_head)) अणु
			atomic_andnot(ZFCP_STATUS_ADAPTER_ERP_PENDING,
					  &adapter->status);
			wake_up(&adapter->erp_करोne_wqh);
	पूर्ण
	पढ़ो_unlock_irqrestore(&adapter->erp_lock, flags);
पूर्ण

अटल व्योम zfcp_erp_enqueue_ptp_port(काष्ठा zfcp_adapter *adapter)
अणु
	काष्ठा zfcp_port *port;
	port = zfcp_port_enqueue(adapter, adapter->peer_wwpn, 0,
				 adapter->peer_d_id);
	अगर (IS_ERR(port)) /* error or port alपढ़ोy attached */
		वापस;
	zfcp_erp_port_reखोलो(port, 0, "ereptp1");
पूर्ण

अटल क्रमागत zfcp_erp_act_result zfcp_erp_adapter_strat_fsf_xconf(
	काष्ठा zfcp_erp_action *erp_action)
अणु
	पूर्णांक retries;
	पूर्णांक sleep = 1;
	काष्ठा zfcp_adapter *adapter = erp_action->adapter;

	atomic_andnot(ZFCP_STATUS_ADAPTER_XCONFIG_OK, &adapter->status);

	क्रम (retries = 7; retries; retries--) अणु
		atomic_andnot(ZFCP_STATUS_ADAPTER_HOST_CON_INIT,
				  &adapter->status);
		ग_लिखो_lock_irq(&adapter->erp_lock);
		zfcp_erp_action_to_running(erp_action);
		ग_लिखो_unlock_irq(&adapter->erp_lock);
		अगर (zfcp_fsf_exchange_config_data(erp_action)) अणु
			atomic_andnot(ZFCP_STATUS_ADAPTER_HOST_CON_INIT,
					  &adapter->status);
			वापस ZFCP_ERP_FAILED;
		पूर्ण

		रुको_event(adapter->erp_पढ़ोy_wq,
			   !list_empty(&adapter->erp_पढ़ोy_head));
		अगर (erp_action->status & ZFCP_STATUS_ERP_TIMEDOUT)
			अवरोध;

		अगर (!(atomic_पढ़ो(&adapter->status) &
		      ZFCP_STATUS_ADAPTER_HOST_CON_INIT))
			अवरोध;

		ssleep(sleep);
		sleep *= 2;
	पूर्ण

	atomic_andnot(ZFCP_STATUS_ADAPTER_HOST_CON_INIT,
			  &adapter->status);

	अगर (!(atomic_पढ़ो(&adapter->status) & ZFCP_STATUS_ADAPTER_XCONFIG_OK))
		वापस ZFCP_ERP_FAILED;

	वापस ZFCP_ERP_SUCCEEDED;
पूर्ण

अटल व्योम
zfcp_erp_adapter_strategy_खोलो_ptp_port(काष्ठा zfcp_adapter *स्थिर adapter)
अणु
	अगर (fc_host_port_type(adapter->scsi_host) == FC_PORTTYPE_PTP)
		zfcp_erp_enqueue_ptp_port(adapter);
पूर्ण

अटल क्रमागत zfcp_erp_act_result zfcp_erp_adapter_strategy_खोलो_fsf_xport(
	काष्ठा zfcp_erp_action *act)
अणु
	पूर्णांक ret;
	काष्ठा zfcp_adapter *adapter = act->adapter;

	ग_लिखो_lock_irq(&adapter->erp_lock);
	zfcp_erp_action_to_running(act);
	ग_लिखो_unlock_irq(&adapter->erp_lock);

	ret = zfcp_fsf_exchange_port_data(act);
	अगर (ret == -EOPNOTSUPP)
		वापस ZFCP_ERP_SUCCEEDED;
	अगर (ret)
		वापस ZFCP_ERP_FAILED;

	zfcp_dbf_rec_run("erasox1", act);
	रुको_event(adapter->erp_पढ़ोy_wq,
		   !list_empty(&adapter->erp_पढ़ोy_head));
	zfcp_dbf_rec_run("erasox2", act);
	अगर (act->status & ZFCP_STATUS_ERP_TIMEDOUT)
		वापस ZFCP_ERP_FAILED;

	वापस ZFCP_ERP_SUCCEEDED;
पूर्ण

अटल क्रमागत zfcp_erp_act_result
zfcp_erp_adapter_strategy_alloc_shost(काष्ठा zfcp_adapter *स्थिर adapter)
अणु
	काष्ठा zfcp_diag_adapter_config_data *स्थिर config_data =
		&adapter->diagnostics->config_data;
	काष्ठा zfcp_diag_adapter_port_data *स्थिर port_data =
		&adapter->diagnostics->port_data;
	अचिन्हित दीर्घ flags;
	पूर्णांक rc;

	rc = zfcp_scsi_adapter_रेजिस्टर(adapter);
	अगर (rc == -EEXIST)
		वापस ZFCP_ERP_SUCCEEDED;
	अन्यथा अगर (rc)
		वापस ZFCP_ERP_FAILED;

	/*
	 * We allocated the shost क्रम the first समय. Beक्रमe it was शून्य,
	 * and so we deferred all updates in the xconf- and xport-data
	 * handlers. We need to make up क्रम that now, and make all the updates
	 * that would have been करोne beक्रमe.
	 *
	 * We can be sure that xconf- and xport-data succeeded, because
	 * otherwise this function is not called. But they might have been
	 * incomplete.
	 */

	spin_lock_irqsave(&config_data->header.access_lock, flags);
	zfcp_scsi_shost_update_config_data(adapter, &config_data->data,
					   !!config_data->header.incomplete);
	spin_unlock_irqrestore(&config_data->header.access_lock, flags);

	अगर (adapter->adapter_features & FSF_FEATURE_HBAAPI_MANAGEMENT) अणु
		spin_lock_irqsave(&port_data->header.access_lock, flags);
		zfcp_scsi_shost_update_port_data(adapter, &port_data->data);
		spin_unlock_irqrestore(&port_data->header.access_lock, flags);
	पूर्ण

	/*
	 * There is a remote possibility that the 'Exchange Port Data' request
	 * reports a dअगरferent connectivity status than 'Exchange Config Data'.
	 * But any change to the connectivity status of the local optic that
	 * happens after the initial xconf request is expected to be reported
	 * to us, as soon as we post Status Read Buffers to the FCP channel
	 * firmware after this function. So any resulting inconsistency will
	 * only be momentary.
	 */
	अगर (config_data->header.incomplete)
		zfcp_fsf_fc_host_link_करोwn(adapter);

	वापस ZFCP_ERP_SUCCEEDED;
पूर्ण

अटल क्रमागत zfcp_erp_act_result zfcp_erp_adapter_strategy_खोलो_fsf(
	काष्ठा zfcp_erp_action *act)
अणु
	अगर (zfcp_erp_adapter_strat_fsf_xconf(act) == ZFCP_ERP_FAILED)
		वापस ZFCP_ERP_FAILED;

	अगर (zfcp_erp_adapter_strategy_खोलो_fsf_xport(act) == ZFCP_ERP_FAILED)
		वापस ZFCP_ERP_FAILED;

	अगर (zfcp_erp_adapter_strategy_alloc_shost(act->adapter) ==
	    ZFCP_ERP_FAILED)
		वापस ZFCP_ERP_FAILED;

	zfcp_erp_adapter_strategy_खोलो_ptp_port(act->adapter);

	अगर (mempool_resize(act->adapter->pool.sr_data,
			   act->adapter->stat_पढ़ो_buf_num))
		वापस ZFCP_ERP_FAILED;

	अगर (mempool_resize(act->adapter->pool.status_पढ़ो_req,
			   act->adapter->stat_पढ़ो_buf_num))
		वापस ZFCP_ERP_FAILED;

	atomic_set(&act->adapter->stat_miss, act->adapter->stat_पढ़ो_buf_num);
	अगर (zfcp_status_पढ़ो_refill(act->adapter))
		वापस ZFCP_ERP_FAILED;

	वापस ZFCP_ERP_SUCCEEDED;
पूर्ण

अटल व्योम zfcp_erp_adapter_strategy_बंद(काष्ठा zfcp_erp_action *act)
अणु
	काष्ठा zfcp_adapter *adapter = act->adapter;

	/* बंद queues to ensure that buffers are not accessed by adapter */
	zfcp_qdio_बंद(adapter->qdio);
	zfcp_fsf_req_dismiss_all(adapter);
	adapter->fsf_req_seq_no = 0;
	zfcp_fc_wka_ports_क्रमce_offline(adapter->gs);
	/* all ports and LUNs are बंदd */
	zfcp_erp_clear_adapter_status(adapter, ZFCP_STATUS_COMMON_OPEN);

	atomic_andnot(ZFCP_STATUS_ADAPTER_XCONFIG_OK |
			  ZFCP_STATUS_ADAPTER_LINK_UNPLUGGED, &adapter->status);
पूर्ण

अटल क्रमागत zfcp_erp_act_result zfcp_erp_adapter_strategy_खोलो(
	काष्ठा zfcp_erp_action *act)
अणु
	काष्ठा zfcp_adapter *adapter = act->adapter;

	अगर (zfcp_qdio_खोलो(adapter->qdio)) अणु
		atomic_andnot(ZFCP_STATUS_ADAPTER_XCONFIG_OK |
				  ZFCP_STATUS_ADAPTER_LINK_UNPLUGGED,
				  &adapter->status);
		वापस ZFCP_ERP_FAILED;
	पूर्ण

	अगर (zfcp_erp_adapter_strategy_खोलो_fsf(act)) अणु
		zfcp_erp_adapter_strategy_बंद(act);
		वापस ZFCP_ERP_FAILED;
	पूर्ण

	atomic_or(ZFCP_STATUS_COMMON_OPEN, &adapter->status);

	वापस ZFCP_ERP_SUCCEEDED;
पूर्ण

अटल क्रमागत zfcp_erp_act_result zfcp_erp_adapter_strategy(
	काष्ठा zfcp_erp_action *act)
अणु
	काष्ठा zfcp_adapter *adapter = act->adapter;

	अगर (atomic_पढ़ो(&adapter->status) & ZFCP_STATUS_COMMON_OPEN) अणु
		zfcp_erp_adapter_strategy_बंद(act);
		अगर (act->status & ZFCP_STATUS_ERP_CLOSE_ONLY)
			वापस ZFCP_ERP_EXIT;
	पूर्ण

	अगर (zfcp_erp_adapter_strategy_खोलो(act)) अणु
		ssleep(8);
		वापस ZFCP_ERP_FAILED;
	पूर्ण

	वापस ZFCP_ERP_SUCCEEDED;
पूर्ण

अटल क्रमागत zfcp_erp_act_result zfcp_erp_port_क्रमced_strategy_बंद(
	काष्ठा zfcp_erp_action *act)
अणु
	पूर्णांक retval;

	retval = zfcp_fsf_बंद_physical_port(act);
	अगर (retval == -ENOMEM)
		वापस ZFCP_ERP_NOMEM;
	act->step = ZFCP_ERP_STEP_PHYS_PORT_CLOSING;
	अगर (retval)
		वापस ZFCP_ERP_FAILED;

	वापस ZFCP_ERP_CONTINUES;
पूर्ण

अटल क्रमागत zfcp_erp_act_result zfcp_erp_port_क्रमced_strategy(
	काष्ठा zfcp_erp_action *erp_action)
अणु
	काष्ठा zfcp_port *port = erp_action->port;
	पूर्णांक status = atomic_पढ़ो(&port->status);

	चयन (erp_action->step) अणु
	हाल ZFCP_ERP_STEP_UNINITIALIZED:
		अगर ((status & ZFCP_STATUS_PORT_PHYS_OPEN) &&
		    (status & ZFCP_STATUS_COMMON_OPEN))
			वापस zfcp_erp_port_क्रमced_strategy_बंद(erp_action);
		अन्यथा
			वापस ZFCP_ERP_FAILED;

	हाल ZFCP_ERP_STEP_PHYS_PORT_CLOSING:
		अगर (!(status & ZFCP_STATUS_PORT_PHYS_OPEN))
			वापस ZFCP_ERP_SUCCEEDED;
		अवरोध;
	हाल ZFCP_ERP_STEP_PORT_CLOSING:
	हाल ZFCP_ERP_STEP_PORT_OPENING:
	हाल ZFCP_ERP_STEP_LUN_CLOSING:
	हाल ZFCP_ERP_STEP_LUN_OPENING:
		/* NOP */
		अवरोध;
	पूर्ण
	वापस ZFCP_ERP_FAILED;
पूर्ण

अटल क्रमागत zfcp_erp_act_result zfcp_erp_port_strategy_बंद(
	काष्ठा zfcp_erp_action *erp_action)
अणु
	पूर्णांक retval;

	retval = zfcp_fsf_बंद_port(erp_action);
	अगर (retval == -ENOMEM)
		वापस ZFCP_ERP_NOMEM;
	erp_action->step = ZFCP_ERP_STEP_PORT_CLOSING;
	अगर (retval)
		वापस ZFCP_ERP_FAILED;
	वापस ZFCP_ERP_CONTINUES;
पूर्ण

अटल क्रमागत zfcp_erp_act_result zfcp_erp_port_strategy_खोलो_port(
	काष्ठा zfcp_erp_action *erp_action)
अणु
	पूर्णांक retval;

	retval = zfcp_fsf_खोलो_port(erp_action);
	अगर (retval == -ENOMEM)
		वापस ZFCP_ERP_NOMEM;
	erp_action->step = ZFCP_ERP_STEP_PORT_OPENING;
	अगर (retval)
		वापस ZFCP_ERP_FAILED;
	वापस ZFCP_ERP_CONTINUES;
पूर्ण

अटल पूर्णांक zfcp_erp_खोलो_ptp_port(काष्ठा zfcp_erp_action *act)
अणु
	काष्ठा zfcp_adapter *adapter = act->adapter;
	काष्ठा zfcp_port *port = act->port;

	अगर (port->wwpn != adapter->peer_wwpn) अणु
		zfcp_erp_set_port_status(port, ZFCP_STATUS_COMMON_ERP_FAILED);
		वापस ZFCP_ERP_FAILED;
	पूर्ण
	port->d_id = adapter->peer_d_id;
	वापस zfcp_erp_port_strategy_खोलो_port(act);
पूर्ण

अटल क्रमागत zfcp_erp_act_result zfcp_erp_port_strategy_खोलो_common(
	काष्ठा zfcp_erp_action *act)
अणु
	काष्ठा zfcp_adapter *adapter = act->adapter;
	काष्ठा zfcp_port *port = act->port;
	पूर्णांक p_status = atomic_पढ़ो(&port->status);

	चयन (act->step) अणु
	हाल ZFCP_ERP_STEP_UNINITIALIZED:
	हाल ZFCP_ERP_STEP_PHYS_PORT_CLOSING:
	हाल ZFCP_ERP_STEP_PORT_CLOSING:
		अगर (fc_host_port_type(adapter->scsi_host) == FC_PORTTYPE_PTP)
			वापस zfcp_erp_खोलो_ptp_port(act);
		अगर (!port->d_id) अणु
			zfcp_fc_trigger_did_lookup(port);
			वापस ZFCP_ERP_EXIT;
		पूर्ण
		वापस zfcp_erp_port_strategy_खोलो_port(act);

	हाल ZFCP_ERP_STEP_PORT_OPENING:
		/* D_ID might have changed during खोलो */
		अगर (p_status & ZFCP_STATUS_COMMON_OPEN) अणु
			अगर (!port->d_id) अणु
				zfcp_fc_trigger_did_lookup(port);
				वापस ZFCP_ERP_EXIT;
			पूर्ण
			वापस ZFCP_ERP_SUCCEEDED;
		पूर्ण
		अगर (port->d_id && !(p_status & ZFCP_STATUS_COMMON_NOESC)) अणु
			port->d_id = 0;
			वापस ZFCP_ERP_FAILED;
		पूर्ण
		/* no early वापस otherwise, जारी after चयन हाल */
		अवरोध;
	हाल ZFCP_ERP_STEP_LUN_CLOSING:
	हाल ZFCP_ERP_STEP_LUN_OPENING:
		/* NOP */
		अवरोध;
	पूर्ण
	वापस ZFCP_ERP_FAILED;
पूर्ण

अटल क्रमागत zfcp_erp_act_result zfcp_erp_port_strategy(
	काष्ठा zfcp_erp_action *erp_action)
अणु
	काष्ठा zfcp_port *port = erp_action->port;
	पूर्णांक p_status = atomic_पढ़ो(&port->status);

	अगर ((p_status & ZFCP_STATUS_COMMON_NOESC) &&
	    !(p_status & ZFCP_STATUS_COMMON_OPEN))
		जाओ बंद_init_करोne;

	चयन (erp_action->step) अणु
	हाल ZFCP_ERP_STEP_UNINITIALIZED:
		अगर (p_status & ZFCP_STATUS_COMMON_OPEN)
			वापस zfcp_erp_port_strategy_बंद(erp_action);
		अवरोध;

	हाल ZFCP_ERP_STEP_PORT_CLOSING:
		अगर (p_status & ZFCP_STATUS_COMMON_OPEN)
			वापस ZFCP_ERP_FAILED;
		अवरोध;
	हाल ZFCP_ERP_STEP_PHYS_PORT_CLOSING:
	हाल ZFCP_ERP_STEP_PORT_OPENING:
	हाल ZFCP_ERP_STEP_LUN_CLOSING:
	हाल ZFCP_ERP_STEP_LUN_OPENING:
		/* NOP */
		अवरोध;
	पूर्ण

बंद_init_करोne:
	अगर (erp_action->status & ZFCP_STATUS_ERP_CLOSE_ONLY)
		वापस ZFCP_ERP_EXIT;

	वापस zfcp_erp_port_strategy_खोलो_common(erp_action);
पूर्ण

अटल व्योम zfcp_erp_lun_strategy_clearstati(काष्ठा scsi_device *sdev)
अणु
	काष्ठा zfcp_scsi_dev *zfcp_sdev = sdev_to_zfcp(sdev);

	atomic_andnot(ZFCP_STATUS_COMMON_ACCESS_DENIED,
			  &zfcp_sdev->status);
पूर्ण

अटल क्रमागत zfcp_erp_act_result zfcp_erp_lun_strategy_बंद(
	काष्ठा zfcp_erp_action *erp_action)
अणु
	पूर्णांक retval = zfcp_fsf_बंद_lun(erp_action);
	अगर (retval == -ENOMEM)
		वापस ZFCP_ERP_NOMEM;
	erp_action->step = ZFCP_ERP_STEP_LUN_CLOSING;
	अगर (retval)
		वापस ZFCP_ERP_FAILED;
	वापस ZFCP_ERP_CONTINUES;
पूर्ण

अटल क्रमागत zfcp_erp_act_result zfcp_erp_lun_strategy_खोलो(
	काष्ठा zfcp_erp_action *erp_action)
अणु
	पूर्णांक retval = zfcp_fsf_खोलो_lun(erp_action);
	अगर (retval == -ENOMEM)
		वापस ZFCP_ERP_NOMEM;
	erp_action->step = ZFCP_ERP_STEP_LUN_OPENING;
	अगर (retval)
		वापस  ZFCP_ERP_FAILED;
	वापस ZFCP_ERP_CONTINUES;
पूर्ण

अटल क्रमागत zfcp_erp_act_result zfcp_erp_lun_strategy(
	काष्ठा zfcp_erp_action *erp_action)
अणु
	काष्ठा scsi_device *sdev = erp_action->sdev;
	काष्ठा zfcp_scsi_dev *zfcp_sdev = sdev_to_zfcp(sdev);

	चयन (erp_action->step) अणु
	हाल ZFCP_ERP_STEP_UNINITIALIZED:
		zfcp_erp_lun_strategy_clearstati(sdev);
		अगर (atomic_पढ़ो(&zfcp_sdev->status) & ZFCP_STATUS_COMMON_OPEN)
			वापस zfcp_erp_lun_strategy_बंद(erp_action);
		/* alपढ़ोy बंदd */
		fallthrough;
	हाल ZFCP_ERP_STEP_LUN_CLOSING:
		अगर (atomic_पढ़ो(&zfcp_sdev->status) & ZFCP_STATUS_COMMON_OPEN)
			वापस ZFCP_ERP_FAILED;
		अगर (erp_action->status & ZFCP_STATUS_ERP_CLOSE_ONLY)
			वापस ZFCP_ERP_EXIT;
		वापस zfcp_erp_lun_strategy_खोलो(erp_action);

	हाल ZFCP_ERP_STEP_LUN_OPENING:
		अगर (atomic_पढ़ो(&zfcp_sdev->status) & ZFCP_STATUS_COMMON_OPEN)
			वापस ZFCP_ERP_SUCCEEDED;
		अवरोध;
	हाल ZFCP_ERP_STEP_PHYS_PORT_CLOSING:
	हाल ZFCP_ERP_STEP_PORT_CLOSING:
	हाल ZFCP_ERP_STEP_PORT_OPENING:
		/* NOP */
		अवरोध;
	पूर्ण
	वापस ZFCP_ERP_FAILED;
पूर्ण

अटल क्रमागत zfcp_erp_act_result zfcp_erp_strategy_check_lun(
	काष्ठा scsi_device *sdev, क्रमागत zfcp_erp_act_result result)
अणु
	काष्ठा zfcp_scsi_dev *zfcp_sdev = sdev_to_zfcp(sdev);

	चयन (result) अणु
	हाल ZFCP_ERP_SUCCEEDED :
		atomic_set(&zfcp_sdev->erp_counter, 0);
		zfcp_erp_lun_unblock(sdev);
		अवरोध;
	हाल ZFCP_ERP_FAILED :
		atomic_inc(&zfcp_sdev->erp_counter);
		अगर (atomic_पढ़ो(&zfcp_sdev->erp_counter) > ZFCP_MAX_ERPS) अणु
			dev_err(&zfcp_sdev->port->adapter->ccw_device->dev,
				"ERP failed for LUN 0x%016Lx on "
				"port 0x%016Lx\n",
				(अचिन्हित दीर्घ दीर्घ)zfcp_scsi_dev_lun(sdev),
				(अचिन्हित दीर्घ दीर्घ)zfcp_sdev->port->wwpn);
			zfcp_erp_set_lun_status(sdev,
						ZFCP_STATUS_COMMON_ERP_FAILED);
		पूर्ण
		अवरोध;
	हाल ZFCP_ERP_CONTINUES:
	हाल ZFCP_ERP_EXIT:
	हाल ZFCP_ERP_DISMISSED:
	हाल ZFCP_ERP_NOMEM:
		/* NOP */
		अवरोध;
	पूर्ण

	अगर (atomic_पढ़ो(&zfcp_sdev->status) & ZFCP_STATUS_COMMON_ERP_FAILED) अणु
		zfcp_erp_lun_block(sdev, 0);
		result = ZFCP_ERP_EXIT;
	पूर्ण
	वापस result;
पूर्ण

अटल क्रमागत zfcp_erp_act_result zfcp_erp_strategy_check_port(
	काष्ठा zfcp_port *port, क्रमागत zfcp_erp_act_result result)
अणु
	चयन (result) अणु
	हाल ZFCP_ERP_SUCCEEDED :
		atomic_set(&port->erp_counter, 0);
		zfcp_erp_port_unblock(port);
		अवरोध;

	हाल ZFCP_ERP_FAILED :
		अगर (atomic_पढ़ो(&port->status) & ZFCP_STATUS_COMMON_NOESC) अणु
			zfcp_erp_port_block(port, 0);
			result = ZFCP_ERP_EXIT;
		पूर्ण
		atomic_inc(&port->erp_counter);
		अगर (atomic_पढ़ो(&port->erp_counter) > ZFCP_MAX_ERPS) अणु
			dev_err(&port->adapter->ccw_device->dev,
				"ERP failed for remote port 0x%016Lx\n",
				(अचिन्हित दीर्घ दीर्घ)port->wwpn);
			zfcp_erp_set_port_status(port,
					 ZFCP_STATUS_COMMON_ERP_FAILED);
		पूर्ण
		अवरोध;
	हाल ZFCP_ERP_CONTINUES:
	हाल ZFCP_ERP_EXIT:
	हाल ZFCP_ERP_DISMISSED:
	हाल ZFCP_ERP_NOMEM:
		/* NOP */
		अवरोध;
	पूर्ण

	अगर (atomic_पढ़ो(&port->status) & ZFCP_STATUS_COMMON_ERP_FAILED) अणु
		zfcp_erp_port_block(port, 0);
		result = ZFCP_ERP_EXIT;
	पूर्ण
	वापस result;
पूर्ण

अटल क्रमागत zfcp_erp_act_result zfcp_erp_strategy_check_adapter(
	काष्ठा zfcp_adapter *adapter, क्रमागत zfcp_erp_act_result result)
अणु
	चयन (result) अणु
	हाल ZFCP_ERP_SUCCEEDED :
		atomic_set(&adapter->erp_counter, 0);
		zfcp_erp_adapter_unblock(adapter);
		अवरोध;

	हाल ZFCP_ERP_FAILED :
		atomic_inc(&adapter->erp_counter);
		अगर (atomic_पढ़ो(&adapter->erp_counter) > ZFCP_MAX_ERPS) अणु
			dev_err(&adapter->ccw_device->dev,
				"ERP cannot recover an error "
				"on the FCP device\n");
			zfcp_erp_set_adapter_status(adapter,
					    ZFCP_STATUS_COMMON_ERP_FAILED);
		पूर्ण
		अवरोध;
	हाल ZFCP_ERP_CONTINUES:
	हाल ZFCP_ERP_EXIT:
	हाल ZFCP_ERP_DISMISSED:
	हाल ZFCP_ERP_NOMEM:
		/* NOP */
		अवरोध;
	पूर्ण

	अगर (atomic_पढ़ो(&adapter->status) & ZFCP_STATUS_COMMON_ERP_FAILED) अणु
		zfcp_erp_adapter_block(adapter, 0);
		result = ZFCP_ERP_EXIT;
	पूर्ण
	वापस result;
पूर्ण

अटल क्रमागत zfcp_erp_act_result zfcp_erp_strategy_check_target(
	काष्ठा zfcp_erp_action *erp_action, क्रमागत zfcp_erp_act_result result)
अणु
	काष्ठा zfcp_adapter *adapter = erp_action->adapter;
	काष्ठा zfcp_port *port = erp_action->port;
	काष्ठा scsi_device *sdev = erp_action->sdev;

	चयन (erp_action->type) अणु

	हाल ZFCP_ERP_ACTION_REOPEN_LUN:
		result = zfcp_erp_strategy_check_lun(sdev, result);
		अवरोध;

	हाल ZFCP_ERP_ACTION_REOPEN_PORT_FORCED:
	हाल ZFCP_ERP_ACTION_REOPEN_PORT:
		result = zfcp_erp_strategy_check_port(port, result);
		अवरोध;

	हाल ZFCP_ERP_ACTION_REOPEN_ADAPTER:
		result = zfcp_erp_strategy_check_adapter(adapter, result);
		अवरोध;
	पूर्ण
	वापस result;
पूर्ण

अटल पूर्णांक zfcp_erp_strat_change_det(atomic_t *target_status, u32 erp_status)
अणु
	पूर्णांक status = atomic_पढ़ो(target_status);

	अगर ((status & ZFCP_STATUS_COMMON_RUNNING) &&
	    (erp_status & ZFCP_STATUS_ERP_CLOSE_ONLY))
		वापस 1; /* take it online */

	अगर (!(status & ZFCP_STATUS_COMMON_RUNNING) &&
	    !(erp_status & ZFCP_STATUS_ERP_CLOSE_ONLY))
		वापस 1; /* take it offline */

	वापस 0;
पूर्ण

अटल क्रमागत zfcp_erp_act_result zfcp_erp_strategy_statechange(
	काष्ठा zfcp_erp_action *act, क्रमागत zfcp_erp_act_result result)
अणु
	क्रमागत zfcp_erp_act_type type = act->type;
	काष्ठा zfcp_adapter *adapter = act->adapter;
	काष्ठा zfcp_port *port = act->port;
	काष्ठा scsi_device *sdev = act->sdev;
	काष्ठा zfcp_scsi_dev *zfcp_sdev;
	u32 erp_status = act->status;

	चयन (type) अणु
	हाल ZFCP_ERP_ACTION_REOPEN_ADAPTER:
		अगर (zfcp_erp_strat_change_det(&adapter->status, erp_status)) अणु
			_zfcp_erp_adapter_reखोलो(adapter,
						 ZFCP_STATUS_COMMON_ERP_FAILED,
						 "ersscg1");
			वापस ZFCP_ERP_EXIT;
		पूर्ण
		अवरोध;

	हाल ZFCP_ERP_ACTION_REOPEN_PORT_FORCED:
	हाल ZFCP_ERP_ACTION_REOPEN_PORT:
		अगर (zfcp_erp_strat_change_det(&port->status, erp_status)) अणु
			_zfcp_erp_port_reखोलो(port,
					      ZFCP_STATUS_COMMON_ERP_FAILED,
					      "ersscg2");
			वापस ZFCP_ERP_EXIT;
		पूर्ण
		अवरोध;

	हाल ZFCP_ERP_ACTION_REOPEN_LUN:
		zfcp_sdev = sdev_to_zfcp(sdev);
		अगर (zfcp_erp_strat_change_det(&zfcp_sdev->status, erp_status)) अणु
			_zfcp_erp_lun_reखोलो(sdev,
					     ZFCP_STATUS_COMMON_ERP_FAILED,
					     "ersscg3", 0);
			वापस ZFCP_ERP_EXIT;
		पूर्ण
		अवरोध;
	पूर्ण
	वापस result;
पूर्ण

अटल व्योम zfcp_erp_action_dequeue(काष्ठा zfcp_erp_action *erp_action)
अणु
	काष्ठा zfcp_adapter *adapter = erp_action->adapter;
	काष्ठा zfcp_scsi_dev *zfcp_sdev;

	adapter->erp_total_count--;
	अगर (erp_action->status & ZFCP_STATUS_ERP_LOWMEM) अणु
		adapter->erp_low_mem_count--;
		erp_action->status &= ~ZFCP_STATUS_ERP_LOWMEM;
	पूर्ण

	list_del(&erp_action->list);
	zfcp_dbf_rec_run("eractd1", erp_action);

	चयन (erp_action->type) अणु
	हाल ZFCP_ERP_ACTION_REOPEN_LUN:
		zfcp_sdev = sdev_to_zfcp(erp_action->sdev);
		atomic_andnot(ZFCP_STATUS_COMMON_ERP_INUSE,
				  &zfcp_sdev->status);
		अवरोध;

	हाल ZFCP_ERP_ACTION_REOPEN_PORT_FORCED:
	हाल ZFCP_ERP_ACTION_REOPEN_PORT:
		atomic_andnot(ZFCP_STATUS_COMMON_ERP_INUSE,
				  &erp_action->port->status);
		अवरोध;

	हाल ZFCP_ERP_ACTION_REOPEN_ADAPTER:
		atomic_andnot(ZFCP_STATUS_COMMON_ERP_INUSE,
				  &erp_action->adapter->status);
		अवरोध;
	पूर्ण
पूर्ण

/**
 * zfcp_erp_try_rport_unblock - unblock rport अगर no more/new recovery
 * @port: zfcp_port whose fc_rport we should try to unblock
 */
अटल व्योम zfcp_erp_try_rport_unblock(काष्ठा zfcp_port *port)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा zfcp_adapter *adapter = port->adapter;
	पूर्णांक port_status;
	काष्ठा Scsi_Host *shost = adapter->scsi_host;
	काष्ठा scsi_device *sdev;

	ग_लिखो_lock_irqsave(&adapter->erp_lock, flags);
	port_status = atomic_पढ़ो(&port->status);
	अगर ((port_status & ZFCP_STATUS_COMMON_UNBLOCKED)    == 0 ||
	    (port_status & (ZFCP_STATUS_COMMON_ERP_INUSE |
			    ZFCP_STATUS_COMMON_ERP_FAILED)) != 0) अणु
		/* new ERP of severity >= port triggered अन्यथाwhere meanजबतक or
		 * local link करोwn (adapter erp_failed but not clear unblock)
		 */
		zfcp_dbf_rec_run_lvl(4, "ertru_p", &port->erp_action);
		ग_लिखो_unlock_irqrestore(&adapter->erp_lock, flags);
		वापस;
	पूर्ण
	spin_lock(shost->host_lock);
	__shost_क्रम_each_device(sdev, shost) अणु
		काष्ठा zfcp_scsi_dev *zsdev = sdev_to_zfcp(sdev);
		पूर्णांक lun_status;

		अगर (sdev->sdev_state == SDEV_DEL ||
		    sdev->sdev_state == SDEV_CANCEL)
			जारी;
		अगर (zsdev->port != port)
			जारी;
		/* LUN under port of पूर्णांकerest */
		lun_status = atomic_पढ़ो(&zsdev->status);
		अगर ((lun_status & ZFCP_STATUS_COMMON_ERP_FAILED) != 0)
			जारी; /* unblock rport despite failed LUNs */
		/* LUN recovery not given up yet [maybe follow-up pending] */
		अगर ((lun_status & ZFCP_STATUS_COMMON_UNBLOCKED) == 0 ||
		    (lun_status & ZFCP_STATUS_COMMON_ERP_INUSE) != 0) अणु
			/* LUN blocked:
			 * not yet unblocked [LUN recovery pending]
			 * or meanजबतक blocked [new LUN recovery triggered]
			 */
			zfcp_dbf_rec_run_lvl(4, "ertru_l", &zsdev->erp_action);
			spin_unlock(shost->host_lock);
			ग_लिखो_unlock_irqrestore(&adapter->erp_lock, flags);
			वापस;
		पूर्ण
	पूर्ण
	/* now port has no child or all children have completed recovery,
	 * and no ERP of severity >= port was meanजबतक triggered अन्यथाwhere
	 */
	zfcp_scsi_schedule_rport_रेजिस्टर(port);
	spin_unlock(shost->host_lock);
	ग_लिखो_unlock_irqrestore(&adapter->erp_lock, flags);
पूर्ण

अटल व्योम zfcp_erp_action_cleanup(काष्ठा zfcp_erp_action *act,
				    क्रमागत zfcp_erp_act_result result)
अणु
	काष्ठा zfcp_adapter *adapter = act->adapter;
	काष्ठा zfcp_port *port = act->port;
	काष्ठा scsi_device *sdev = act->sdev;

	चयन (act->type) अणु
	हाल ZFCP_ERP_ACTION_REOPEN_LUN:
		अगर (!(act->status & ZFCP_STATUS_ERP_NO_REF))
			scsi_device_put(sdev);
		zfcp_erp_try_rport_unblock(port);
		अवरोध;

	हाल ZFCP_ERP_ACTION_REOPEN_PORT:
		/* This चयन हाल might also happen after a क्रमced reखोलो
		 * was successfully करोne and thus overwritten with a new
		 * non-क्रमced reखोलो at `ersfs_2'. In this हाल, we must not
		 * करो the clean-up of the non-क्रमced version.
		 */
		अगर (act->step != ZFCP_ERP_STEP_UNINITIALIZED)
			अगर (result == ZFCP_ERP_SUCCEEDED)
				zfcp_erp_try_rport_unblock(port);
		fallthrough;
	हाल ZFCP_ERP_ACTION_REOPEN_PORT_FORCED:
		put_device(&port->dev);
		अवरोध;

	हाल ZFCP_ERP_ACTION_REOPEN_ADAPTER:
		अगर (result == ZFCP_ERP_SUCCEEDED) अणु
			रेजिस्टर_service_level(&adapter->service_level);
			zfcp_fc_conditional_port_scan(adapter);
			queue_work(adapter->work_queue, &adapter->ns_up_work);
		पूर्ण अन्यथा
			unरेजिस्टर_service_level(&adapter->service_level);

		kref_put(&adapter->ref, zfcp_adapter_release);
		अवरोध;
	पूर्ण
पूर्ण

अटल क्रमागत zfcp_erp_act_result zfcp_erp_strategy_करो_action(
	काष्ठा zfcp_erp_action *erp_action)
अणु
	चयन (erp_action->type) अणु
	हाल ZFCP_ERP_ACTION_REOPEN_ADAPTER:
		वापस zfcp_erp_adapter_strategy(erp_action);
	हाल ZFCP_ERP_ACTION_REOPEN_PORT_FORCED:
		वापस zfcp_erp_port_क्रमced_strategy(erp_action);
	हाल ZFCP_ERP_ACTION_REOPEN_PORT:
		वापस zfcp_erp_port_strategy(erp_action);
	हाल ZFCP_ERP_ACTION_REOPEN_LUN:
		वापस zfcp_erp_lun_strategy(erp_action);
	पूर्ण
	वापस ZFCP_ERP_FAILED;
पूर्ण

अटल क्रमागत zfcp_erp_act_result zfcp_erp_strategy(
	काष्ठा zfcp_erp_action *erp_action)
अणु
	क्रमागत zfcp_erp_act_result result;
	अचिन्हित दीर्घ flags;
	काष्ठा zfcp_adapter *adapter = erp_action->adapter;

	kref_get(&adapter->ref);

	ग_लिखो_lock_irqsave(&adapter->erp_lock, flags);
	zfcp_erp_strategy_check_fsfreq(erp_action);

	अगर (erp_action->status & ZFCP_STATUS_ERP_DISMISSED) अणु
		zfcp_erp_action_dequeue(erp_action);
		result = ZFCP_ERP_DISMISSED;
		जाओ unlock;
	पूर्ण

	अगर (erp_action->status & ZFCP_STATUS_ERP_TIMEDOUT) अणु
		result = ZFCP_ERP_FAILED;
		जाओ check_target;
	पूर्ण

	zfcp_erp_action_to_running(erp_action);

	/* no lock to allow क्रम blocking operations */
	ग_लिखो_unlock_irqrestore(&adapter->erp_lock, flags);
	result = zfcp_erp_strategy_करो_action(erp_action);
	ग_लिखो_lock_irqsave(&adapter->erp_lock, flags);

	अगर (erp_action->status & ZFCP_STATUS_ERP_DISMISSED)
		result = ZFCP_ERP_CONTINUES;

	चयन (result) अणु
	हाल ZFCP_ERP_NOMEM:
		अगर (!(erp_action->status & ZFCP_STATUS_ERP_LOWMEM)) अणु
			++adapter->erp_low_mem_count;
			erp_action->status |= ZFCP_STATUS_ERP_LOWMEM;
		पूर्ण
		अगर (adapter->erp_total_count == adapter->erp_low_mem_count)
			_zfcp_erp_adapter_reखोलो(adapter, 0, "erstgy1");
		अन्यथा अणु
			zfcp_erp_strategy_memरुको(erp_action);
			result = ZFCP_ERP_CONTINUES;
		पूर्ण
		जाओ unlock;

	हाल ZFCP_ERP_CONTINUES:
		अगर (erp_action->status & ZFCP_STATUS_ERP_LOWMEM) अणु
			--adapter->erp_low_mem_count;
			erp_action->status &= ~ZFCP_STATUS_ERP_LOWMEM;
		पूर्ण
		जाओ unlock;
	हाल ZFCP_ERP_SUCCEEDED:
	हाल ZFCP_ERP_FAILED:
	हाल ZFCP_ERP_EXIT:
	हाल ZFCP_ERP_DISMISSED:
		/* NOP */
		अवरोध;
	पूर्ण

check_target:
	result = zfcp_erp_strategy_check_target(erp_action, result);
	zfcp_erp_action_dequeue(erp_action);
	result = zfcp_erp_strategy_statechange(erp_action, result);
	अगर (result == ZFCP_ERP_EXIT)
		जाओ unlock;
	अगर (result == ZFCP_ERP_SUCCEEDED)
		zfcp_erp_strategy_followup_success(erp_action);
	अगर (result == ZFCP_ERP_FAILED)
		zfcp_erp_strategy_followup_failed(erp_action);

 unlock:
	ग_लिखो_unlock_irqrestore(&adapter->erp_lock, flags);

	अगर (result != ZFCP_ERP_CONTINUES)
		zfcp_erp_action_cleanup(erp_action, result);

	kref_put(&adapter->ref, zfcp_adapter_release);
	वापस result;
पूर्ण

अटल पूर्णांक zfcp_erp_thपढ़ो(व्योम *data)
अणु
	काष्ठा zfcp_adapter *adapter = (काष्ठा zfcp_adapter *) data;
	काष्ठा zfcp_erp_action *act;
	अचिन्हित दीर्घ flags;

	क्रम (;;) अणु
		रुको_event_पूर्णांकerruptible(adapter->erp_पढ़ोy_wq,
			   !list_empty(&adapter->erp_पढ़ोy_head) ||
			   kthपढ़ो_should_stop());

		अगर (kthपढ़ो_should_stop())
			अवरोध;

		ग_लिखो_lock_irqsave(&adapter->erp_lock, flags);
		act = list_first_entry_or_null(&adapter->erp_पढ़ोy_head,
					       काष्ठा zfcp_erp_action, list);
		ग_लिखो_unlock_irqrestore(&adapter->erp_lock, flags);

		अगर (act) अणु
			/* there is more to come after dismission, no notअगरy */
			अगर (zfcp_erp_strategy(act) != ZFCP_ERP_DISMISSED)
				zfcp_erp_wakeup(adapter);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/**
 * zfcp_erp_thपढ़ो_setup - Start ERP thपढ़ो क्रम adapter
 * @adapter: Adapter to start the ERP thपढ़ो क्रम
 *
 * Return: 0 on success, or error code from kthपढ़ो_run().
 */
पूर्णांक zfcp_erp_thपढ़ो_setup(काष्ठा zfcp_adapter *adapter)
अणु
	काष्ठा task_काष्ठा *thपढ़ो;

	thपढ़ो = kthपढ़ो_run(zfcp_erp_thपढ़ो, adapter, "zfcperp%s",
			     dev_name(&adapter->ccw_device->dev));
	अगर (IS_ERR(thपढ़ो)) अणु
		dev_err(&adapter->ccw_device->dev,
			"Creating an ERP thread for the FCP device failed.\n");
		वापस PTR_ERR(thपढ़ो);
	पूर्ण

	adapter->erp_thपढ़ो = thपढ़ो;
	वापस 0;
पूर्ण

/**
 * zfcp_erp_thपढ़ो_समाप्त - Stop ERP thपढ़ो.
 * @adapter: Adapter where the ERP thपढ़ो should be stopped.
 *
 * The caller of this routine ensures that the specअगरied adapter has
 * been shut करोwn and that this operation has been completed. Thus,
 * there are no pending erp_actions which would need to be handled
 * here.
 */
व्योम zfcp_erp_thपढ़ो_समाप्त(काष्ठा zfcp_adapter *adapter)
अणु
	kthपढ़ो_stop(adapter->erp_thपढ़ो);
	adapter->erp_thपढ़ो = शून्य;
	WARN_ON(!list_empty(&adapter->erp_पढ़ोy_head));
	WARN_ON(!list_empty(&adapter->erp_running_head));
पूर्ण

/**
 * zfcp_erp_रुको - रुको क्रम completion of error recovery on an adapter
 * @adapter: adapter क्रम which to रुको क्रम completion of its error recovery
 */
व्योम zfcp_erp_रुको(काष्ठा zfcp_adapter *adapter)
अणु
	रुको_event(adapter->erp_करोne_wqh,
		   !(atomic_पढ़ो(&adapter->status) &
			ZFCP_STATUS_ADAPTER_ERP_PENDING));
पूर्ण

/**
 * zfcp_erp_set_adapter_status - set adapter status bits
 * @adapter: adapter to change the status
 * @mask: status bits to change
 *
 * Changes in common status bits are propagated to attached ports and LUNs.
 */
व्योम zfcp_erp_set_adapter_status(काष्ठा zfcp_adapter *adapter, u32 mask)
अणु
	काष्ठा zfcp_port *port;
	काष्ठा scsi_device *sdev;
	अचिन्हित दीर्घ flags;
	u32 common_mask = mask & ZFCP_COMMON_FLAGS;

	atomic_or(mask, &adapter->status);

	अगर (!common_mask)
		वापस;

	पढ़ो_lock_irqsave(&adapter->port_list_lock, flags);
	list_क्रम_each_entry(port, &adapter->port_list, list)
		atomic_or(common_mask, &port->status);
	पढ़ो_unlock_irqrestore(&adapter->port_list_lock, flags);

	/*
	 * अगर `scsi_host` is missing, xconfig/xport data has never completed
	 * yet, so we can't access it, but there are also no SDEVs yet
	 */
	अगर (adapter->scsi_host == शून्य)
		वापस;

	spin_lock_irqsave(adapter->scsi_host->host_lock, flags);
	__shost_क्रम_each_device(sdev, adapter->scsi_host)
		atomic_or(common_mask, &sdev_to_zfcp(sdev)->status);
	spin_unlock_irqrestore(adapter->scsi_host->host_lock, flags);
पूर्ण

/**
 * zfcp_erp_clear_adapter_status - clear adapter status bits
 * @adapter: adapter to change the status
 * @mask: status bits to change
 *
 * Changes in common status bits are propagated to attached ports and LUNs.
 */
व्योम zfcp_erp_clear_adapter_status(काष्ठा zfcp_adapter *adapter, u32 mask)
अणु
	काष्ठा zfcp_port *port;
	काष्ठा scsi_device *sdev;
	अचिन्हित दीर्घ flags;
	u32 common_mask = mask & ZFCP_COMMON_FLAGS;
	u32 clear_counter = mask & ZFCP_STATUS_COMMON_ERP_FAILED;

	atomic_andnot(mask, &adapter->status);

	अगर (!common_mask)
		वापस;

	अगर (clear_counter)
		atomic_set(&adapter->erp_counter, 0);

	पढ़ो_lock_irqsave(&adapter->port_list_lock, flags);
	list_क्रम_each_entry(port, &adapter->port_list, list) अणु
		atomic_andnot(common_mask, &port->status);
		अगर (clear_counter)
			atomic_set(&port->erp_counter, 0);
	पूर्ण
	पढ़ो_unlock_irqrestore(&adapter->port_list_lock, flags);

	/*
	 * अगर `scsi_host` is missing, xconfig/xport data has never completed
	 * yet, so we can't access it, but there are also no SDEVs yet
	 */
	अगर (adapter->scsi_host == शून्य)
		वापस;

	spin_lock_irqsave(adapter->scsi_host->host_lock, flags);
	__shost_क्रम_each_device(sdev, adapter->scsi_host) अणु
		atomic_andnot(common_mask, &sdev_to_zfcp(sdev)->status);
		अगर (clear_counter)
			atomic_set(&sdev_to_zfcp(sdev)->erp_counter, 0);
	पूर्ण
	spin_unlock_irqrestore(adapter->scsi_host->host_lock, flags);
पूर्ण

/**
 * zfcp_erp_set_port_status - set port status bits
 * @port: port to change the status
 * @mask: status bits to change
 *
 * Changes in common status bits are propagated to attached LUNs.
 */
व्योम zfcp_erp_set_port_status(काष्ठा zfcp_port *port, u32 mask)
अणु
	काष्ठा scsi_device *sdev;
	u32 common_mask = mask & ZFCP_COMMON_FLAGS;
	अचिन्हित दीर्घ flags;

	atomic_or(mask, &port->status);

	अगर (!common_mask)
		वापस;

	spin_lock_irqsave(port->adapter->scsi_host->host_lock, flags);
	__shost_क्रम_each_device(sdev, port->adapter->scsi_host)
		अगर (sdev_to_zfcp(sdev)->port == port)
			atomic_or(common_mask,
					&sdev_to_zfcp(sdev)->status);
	spin_unlock_irqrestore(port->adapter->scsi_host->host_lock, flags);
पूर्ण

/**
 * zfcp_erp_clear_port_status - clear port status bits
 * @port: adapter to change the status
 * @mask: status bits to change
 *
 * Changes in common status bits are propagated to attached LUNs.
 */
व्योम zfcp_erp_clear_port_status(काष्ठा zfcp_port *port, u32 mask)
अणु
	काष्ठा scsi_device *sdev;
	u32 common_mask = mask & ZFCP_COMMON_FLAGS;
	u32 clear_counter = mask & ZFCP_STATUS_COMMON_ERP_FAILED;
	अचिन्हित दीर्घ flags;

	atomic_andnot(mask, &port->status);

	अगर (!common_mask)
		वापस;

	अगर (clear_counter)
		atomic_set(&port->erp_counter, 0);

	spin_lock_irqsave(port->adapter->scsi_host->host_lock, flags);
	__shost_क्रम_each_device(sdev, port->adapter->scsi_host)
		अगर (sdev_to_zfcp(sdev)->port == port) अणु
			atomic_andnot(common_mask,
					  &sdev_to_zfcp(sdev)->status);
			अगर (clear_counter)
				atomic_set(&sdev_to_zfcp(sdev)->erp_counter, 0);
		पूर्ण
	spin_unlock_irqrestore(port->adapter->scsi_host->host_lock, flags);
पूर्ण

/**
 * zfcp_erp_set_lun_status - set lun status bits
 * @sdev: SCSI device / lun to set the status bits
 * @mask: status bits to change
 */
व्योम zfcp_erp_set_lun_status(काष्ठा scsi_device *sdev, u32 mask)
अणु
	काष्ठा zfcp_scsi_dev *zfcp_sdev = sdev_to_zfcp(sdev);

	atomic_or(mask, &zfcp_sdev->status);
पूर्ण

/**
 * zfcp_erp_clear_lun_status - clear lun status bits
 * @sdev: SCSi device / lun to clear the status bits
 * @mask: status bits to change
 */
व्योम zfcp_erp_clear_lun_status(काष्ठा scsi_device *sdev, u32 mask)
अणु
	काष्ठा zfcp_scsi_dev *zfcp_sdev = sdev_to_zfcp(sdev);

	atomic_andnot(mask, &zfcp_sdev->status);

	अगर (mask & ZFCP_STATUS_COMMON_ERP_FAILED)
		atomic_set(&zfcp_sdev->erp_counter, 0);
पूर्ण

/**
 * zfcp_erp_adapter_reset_sync() - Really reखोलो adapter and रुको.
 * @adapter: Poपूर्णांकer to zfcp_adapter to reखोलो.
 * @dbftag: Trace tag string of length %ZFCP_DBF_TAG_LEN.
 */
व्योम zfcp_erp_adapter_reset_sync(काष्ठा zfcp_adapter *adapter, अक्षर *dbftag)
अणु
	zfcp_erp_set_adapter_status(adapter, ZFCP_STATUS_COMMON_RUNNING);
	zfcp_erp_adapter_reखोलो(adapter, ZFCP_STATUS_COMMON_ERP_FAILED, dbftag);
	zfcp_erp_रुको(adapter);
पूर्ण
