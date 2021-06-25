<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB
// Copyright (c) 2018 Mellanox Technologies

#समावेश <linux/mlx5/driver.h>

#समावेश "mlx5_core.h"
#समावेश "lib/eq.h"
#समावेश "lib/mlx5.h"

काष्ठा mlx5_event_nb अणु
	काष्ठा mlx5_nb  nb;
	व्योम           *ctx;
पूर्ण;

/* General events handlers क्रम the low level mlx5_core driver
 *
 * Other Major feature specअगरic events such as
 * घड़ी/eचयन/fpga/FW trace and many others, are handled अन्यथाwhere, with
 * separate notअगरiers callbacks, specअगरically by those mlx5 components.
 */
अटल पूर्णांक any_notअगरier(काष्ठा notअगरier_block *, अचिन्हित दीर्घ, व्योम *);
अटल पूर्णांक temp_warn(काष्ठा notअगरier_block *, अचिन्हित दीर्घ, व्योम *);
अटल पूर्णांक port_module(काष्ठा notअगरier_block *, अचिन्हित दीर्घ, व्योम *);
अटल पूर्णांक pcie_core(काष्ठा notअगरier_block *, अचिन्हित दीर्घ, व्योम *);

/* handler which क्रमwards the event to events->fw_nh, driver notअगरiers */
अटल पूर्णांक क्रमward_event(काष्ठा notअगरier_block *, अचिन्हित दीर्घ, व्योम *);

अटल काष्ठा mlx5_nb events_nbs_ref[] = अणु
	/* Events to be proccessed by mlx5_core */
	अणु.nb.notअगरier_call = any_notअगरier,  .event_type = MLX5_EVENT_TYPE_NOTIFY_ANY पूर्ण,
	अणु.nb.notअगरier_call = temp_warn,     .event_type = MLX5_EVENT_TYPE_TEMP_WARN_EVENT पूर्ण,
	अणु.nb.notअगरier_call = port_module,   .event_type = MLX5_EVENT_TYPE_PORT_MODULE_EVENT पूर्ण,
	अणु.nb.notअगरier_call = pcie_core,     .event_type = MLX5_EVENT_TYPE_GENERAL_EVENT पूर्ण,

	/* Events to be क्रमwarded (as is) to mlx5 core पूर्णांकerfaces (mlx5e/mlx5_ib) */
	अणु.nb.notअगरier_call = क्रमward_event,   .event_type = MLX5_EVENT_TYPE_PORT_CHANGE पूर्ण,
	अणु.nb.notअगरier_call = क्रमward_event,   .event_type = MLX5_EVENT_TYPE_GENERAL_EVENT पूर्ण,
	/* QP/WQ resource events to क्रमward */
	अणु.nb.notअगरier_call = क्रमward_event,   .event_type = MLX5_EVENT_TYPE_DCT_DRAINED पूर्ण,
	अणु.nb.notअगरier_call = क्रमward_event,   .event_type = MLX5_EVENT_TYPE_PATH_MIG पूर्ण,
	अणु.nb.notअगरier_call = क्रमward_event,   .event_type = MLX5_EVENT_TYPE_COMM_EST पूर्ण,
	अणु.nb.notअगरier_call = क्रमward_event,   .event_type = MLX5_EVENT_TYPE_SQ_DRAINED पूर्ण,
	अणु.nb.notअगरier_call = क्रमward_event,   .event_type = MLX5_EVENT_TYPE_SRQ_LAST_WQE पूर्ण,
	अणु.nb.notअगरier_call = क्रमward_event,   .event_type = MLX5_EVENT_TYPE_WQ_CATAS_ERROR पूर्ण,
	अणु.nb.notअगरier_call = क्रमward_event,   .event_type = MLX5_EVENT_TYPE_PATH_MIG_FAILED पूर्ण,
	अणु.nb.notअगरier_call = क्रमward_event,   .event_type = MLX5_EVENT_TYPE_WQ_INVAL_REQ_ERROR पूर्ण,
	अणु.nb.notअगरier_call = क्रमward_event,   .event_type = MLX5_EVENT_TYPE_WQ_ACCESS_ERROR पूर्ण,
	/* SRQ events */
	अणु.nb.notअगरier_call = क्रमward_event,   .event_type = MLX5_EVENT_TYPE_SRQ_CATAS_ERROR पूर्ण,
	अणु.nb.notअगरier_call = क्रमward_event,   .event_type = MLX5_EVENT_TYPE_SRQ_RQ_LIMIT पूर्ण,
पूर्ण;

काष्ठा mlx5_events अणु
	काष्ठा mlx5_core_dev *dev;
	काष्ठा workqueue_काष्ठा *wq;
	काष्ठा mlx5_event_nb  notअगरiers[ARRAY_SIZE(events_nbs_ref)];
	/* driver notअगरier chain क्रम fw events */
	काष्ठा atomic_notअगरier_head fw_nh;
	/* port module events stats */
	काष्ठा mlx5_pme_stats pme_stats;
	/*pcie_core*/
	काष्ठा work_काष्ठा pcie_core_work;
	/* driver notअगरier chain क्रम sw events */
	काष्ठा blocking_notअगरier_head sw_nh;
पूर्ण;

अटल स्थिर अक्षर *eqe_type_str(u8 type)
अणु
	चयन (type) अणु
	हाल MLX5_EVENT_TYPE_COMP:
		वापस "MLX5_EVENT_TYPE_COMP";
	हाल MLX5_EVENT_TYPE_PATH_MIG:
		वापस "MLX5_EVENT_TYPE_PATH_MIG";
	हाल MLX5_EVENT_TYPE_COMM_EST:
		वापस "MLX5_EVENT_TYPE_COMM_EST";
	हाल MLX5_EVENT_TYPE_SQ_DRAINED:
		वापस "MLX5_EVENT_TYPE_SQ_DRAINED";
	हाल MLX5_EVENT_TYPE_SRQ_LAST_WQE:
		वापस "MLX5_EVENT_TYPE_SRQ_LAST_WQE";
	हाल MLX5_EVENT_TYPE_SRQ_RQ_LIMIT:
		वापस "MLX5_EVENT_TYPE_SRQ_RQ_LIMIT";
	हाल MLX5_EVENT_TYPE_CQ_ERROR:
		वापस "MLX5_EVENT_TYPE_CQ_ERROR";
	हाल MLX5_EVENT_TYPE_WQ_CATAS_ERROR:
		वापस "MLX5_EVENT_TYPE_WQ_CATAS_ERROR";
	हाल MLX5_EVENT_TYPE_PATH_MIG_FAILED:
		वापस "MLX5_EVENT_TYPE_PATH_MIG_FAILED";
	हाल MLX5_EVENT_TYPE_WQ_INVAL_REQ_ERROR:
		वापस "MLX5_EVENT_TYPE_WQ_INVAL_REQ_ERROR";
	हाल MLX5_EVENT_TYPE_WQ_ACCESS_ERROR:
		वापस "MLX5_EVENT_TYPE_WQ_ACCESS_ERROR";
	हाल MLX5_EVENT_TYPE_SRQ_CATAS_ERROR:
		वापस "MLX5_EVENT_TYPE_SRQ_CATAS_ERROR";
	हाल MLX5_EVENT_TYPE_INTERNAL_ERROR:
		वापस "MLX5_EVENT_TYPE_INTERNAL_ERROR";
	हाल MLX5_EVENT_TYPE_PORT_CHANGE:
		वापस "MLX5_EVENT_TYPE_PORT_CHANGE";
	हाल MLX5_EVENT_TYPE_GPIO_EVENT:
		वापस "MLX5_EVENT_TYPE_GPIO_EVENT";
	हाल MLX5_EVENT_TYPE_PORT_MODULE_EVENT:
		वापस "MLX5_EVENT_TYPE_PORT_MODULE_EVENT";
	हाल MLX5_EVENT_TYPE_TEMP_WARN_EVENT:
		वापस "MLX5_EVENT_TYPE_TEMP_WARN_EVENT";
	हाल MLX5_EVENT_TYPE_REMOTE_CONFIG:
		वापस "MLX5_EVENT_TYPE_REMOTE_CONFIG";
	हाल MLX5_EVENT_TYPE_DB_BF_CONGESTION:
		वापस "MLX5_EVENT_TYPE_DB_BF_CONGESTION";
	हाल MLX5_EVENT_TYPE_STALL_EVENT:
		वापस "MLX5_EVENT_TYPE_STALL_EVENT";
	हाल MLX5_EVENT_TYPE_CMD:
		वापस "MLX5_EVENT_TYPE_CMD";
	हाल MLX5_EVENT_TYPE_ESW_FUNCTIONS_CHANGED:
		वापस "MLX5_EVENT_TYPE_ESW_FUNCTIONS_CHANGED";
	हाल MLX5_EVENT_TYPE_VHCA_STATE_CHANGE:
		वापस "MLX5_EVENT_TYPE_VHCA_STATE_CHANGE";
	हाल MLX5_EVENT_TYPE_PAGE_REQUEST:
		वापस "MLX5_EVENT_TYPE_PAGE_REQUEST";
	हाल MLX5_EVENT_TYPE_PAGE_FAULT:
		वापस "MLX5_EVENT_TYPE_PAGE_FAULT";
	हाल MLX5_EVENT_TYPE_PPS_EVENT:
		वापस "MLX5_EVENT_TYPE_PPS_EVENT";
	हाल MLX5_EVENT_TYPE_NIC_VPORT_CHANGE:
		वापस "MLX5_EVENT_TYPE_NIC_VPORT_CHANGE";
	हाल MLX5_EVENT_TYPE_FPGA_ERROR:
		वापस "MLX5_EVENT_TYPE_FPGA_ERROR";
	हाल MLX5_EVENT_TYPE_FPGA_QP_ERROR:
		वापस "MLX5_EVENT_TYPE_FPGA_QP_ERROR";
	हाल MLX5_EVENT_TYPE_GENERAL_EVENT:
		वापस "MLX5_EVENT_TYPE_GENERAL_EVENT";
	हाल MLX5_EVENT_TYPE_MONITOR_COUNTER:
		वापस "MLX5_EVENT_TYPE_MONITOR_COUNTER";
	हाल MLX5_EVENT_TYPE_DEVICE_TRACER:
		वापस "MLX5_EVENT_TYPE_DEVICE_TRACER";
	शेष:
		वापस "Unrecognized event";
	पूर्ण
पूर्ण

/* handles all FW events, type == eqe->type */
अटल पूर्णांक any_notअगरier(काष्ठा notअगरier_block *nb,
			अचिन्हित दीर्घ type, व्योम *data)
अणु
	काष्ठा mlx5_event_nb *event_nb = mlx5_nb_cof(nb, काष्ठा mlx5_event_nb, nb);
	काष्ठा mlx5_events   *events   = event_nb->ctx;
	काष्ठा mlx5_eqe      *eqe      = data;

	mlx5_core_dbg(events->dev, "Async eqe type %s, subtype (%d)\n",
		      eqe_type_str(eqe->type), eqe->sub_type);
	वापस NOTIFY_OK;
पूर्ण

/* type == MLX5_EVENT_TYPE_TEMP_WARN_EVENT */
अटल पूर्णांक temp_warn(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ type, व्योम *data)
अणु
	काष्ठा mlx5_event_nb *event_nb = mlx5_nb_cof(nb, काष्ठा mlx5_event_nb, nb);
	काष्ठा mlx5_events   *events   = event_nb->ctx;
	काष्ठा mlx5_eqe      *eqe      = data;
	u64 value_lsb;
	u64 value_msb;

	value_lsb = be64_to_cpu(eqe->data.temp_warning.sensor_warning_lsb);
	value_msb = be64_to_cpu(eqe->data.temp_warning.sensor_warning_msb);

	mlx5_core_warn(events->dev,
		       "High temperature on sensors with bit set %llx %llx",
		       value_msb, value_lsb);

	वापस NOTIFY_OK;
पूर्ण

/* MLX5_EVENT_TYPE_PORT_MODULE_EVENT */
अटल स्थिर अक्षर *mlx5_pme_status_to_string(क्रमागत port_module_event_status_type status)
अणु
	चयन (status) अणु
	हाल MLX5_MODULE_STATUS_PLUGGED:
		वापस "Cable plugged";
	हाल MLX5_MODULE_STATUS_UNPLUGGED:
		वापस "Cable unplugged";
	हाल MLX5_MODULE_STATUS_ERROR:
		वापस "Cable error";
	हाल MLX5_MODULE_STATUS_DISABLED:
		वापस "Cable disabled";
	शेष:
		वापस "Unknown status";
	पूर्ण
पूर्ण

अटल स्थिर अक्षर *mlx5_pme_error_to_string(क्रमागत port_module_event_error_type error)
अणु
	चयन (error) अणु
	हाल MLX5_MODULE_EVENT_ERROR_POWER_BUDGET_EXCEEDED:
		वापस "Power budget exceeded";
	हाल MLX5_MODULE_EVENT_ERROR_LONG_RANGE_FOR_NON_MLNX:
		वापस "Long Range for non MLNX cable";
	हाल MLX5_MODULE_EVENT_ERROR_BUS_STUCK:
		वापस "Bus stuck (I2C or data shorted)";
	हाल MLX5_MODULE_EVENT_ERROR_NO_EEPROM_RETRY_TIMEOUT:
		वापस "No EEPROM/retry timeout";
	हाल MLX5_MODULE_EVENT_ERROR_ENFORCE_PART_NUMBER_LIST:
		वापस "Enforce part number list";
	हाल MLX5_MODULE_EVENT_ERROR_UNKNOWN_IDENTIFIER:
		वापस "Unknown identifier";
	हाल MLX5_MODULE_EVENT_ERROR_HIGH_TEMPERATURE:
		वापस "High Temperature";
	हाल MLX5_MODULE_EVENT_ERROR_BAD_CABLE:
		वापस "Bad or shorted cable/module";
	हाल MLX5_MODULE_EVENT_ERROR_PCIE_POWER_SLOT_EXCEEDED:
		वापस "One or more network ports have been powered down due to insufficient/unadvertised power on the PCIe slot";
	शेष:
		वापस "Unknown error";
	पूर्ण
पूर्ण

/* type == MLX5_EVENT_TYPE_PORT_MODULE_EVENT */
अटल पूर्णांक port_module(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ type, व्योम *data)
अणु
	काष्ठा mlx5_event_nb *event_nb = mlx5_nb_cof(nb, काष्ठा mlx5_event_nb, nb);
	काष्ठा mlx5_events   *events   = event_nb->ctx;
	काष्ठा mlx5_eqe      *eqe      = data;

	क्रमागत port_module_event_status_type module_status;
	क्रमागत port_module_event_error_type error_type;
	काष्ठा mlx5_eqe_port_module *module_event_eqe;
	स्थिर अक्षर *status_str;
	u8 module_num;

	module_event_eqe = &eqe->data.port_module;
	module_status = module_event_eqe->module_status &
			PORT_MODULE_EVENT_MODULE_STATUS_MASK;
	error_type = module_event_eqe->error_type &
		     PORT_MODULE_EVENT_ERROR_TYPE_MASK;

	अगर (module_status < MLX5_MODULE_STATUS_NUM)
		events->pme_stats.status_counters[module_status]++;

	अगर (module_status == MLX5_MODULE_STATUS_ERROR)
		अगर (error_type < MLX5_MODULE_EVENT_ERROR_NUM)
			events->pme_stats.error_counters[error_type]++;

	अगर (!prपूर्णांकk_ratelimit())
		वापस NOTIFY_OK;

	module_num = module_event_eqe->module;
	status_str = mlx5_pme_status_to_string(module_status);
	अगर (module_status == MLX5_MODULE_STATUS_ERROR) अणु
		स्थिर अक्षर *error_str = mlx5_pme_error_to_string(error_type);

		mlx5_core_err(events->dev,
			      "Port module event[error]: module %u, %s, %s\n",
			      module_num, status_str, error_str);
	पूर्ण अन्यथा अणु
		mlx5_core_info(events->dev,
			       "Port module event: module %u, %s\n",
			       module_num, status_str);
	पूर्ण

	वापस NOTIFY_OK;
पूर्ण

क्रमागत अणु
	MLX5_PCI_POWER_COULD_NOT_BE_READ = 0x0,
	MLX5_PCI_POWER_SUFFICIENT_REPORTED = 0x1,
	MLX5_PCI_POWER_INSUFFICIENT_REPORTED = 0x2,
पूर्ण;

अटल व्योम mlx5_pcie_event(काष्ठा work_काष्ठा *work)
अणु
	u32 out[MLX5_ST_SZ_DW(mpein_reg)] = अणु0पूर्ण;
	u32 in[MLX5_ST_SZ_DW(mpein_reg)] = अणु0पूर्ण;
	काष्ठा mlx5_events *events;
	काष्ठा mlx5_core_dev *dev;
	u8 घातer_status;
	u16 pci_घातer;

	events = container_of(work, काष्ठा mlx5_events, pcie_core_work);
	dev  = events->dev;

	अगर (!MLX5_CAP_MCAM_FEATURE(dev, pci_status_and_घातer))
		वापस;

	mlx5_core_access_reg(dev, in, माप(in), out, माप(out),
			     MLX5_REG_MPEIN, 0, 0);
	घातer_status = MLX5_GET(mpein_reg, out, pwr_status);
	pci_घातer = MLX5_GET(mpein_reg, out, pci_घातer);

	चयन (घातer_status) अणु
	हाल MLX5_PCI_POWER_COULD_NOT_BE_READ:
		mlx5_core_info_rl(dev,
				  "PCIe slot power capability was not advertised.\n");
		अवरोध;
	हाल MLX5_PCI_POWER_INSUFFICIENT_REPORTED:
		mlx5_core_warn_rl(dev,
				  "Detected insufficient power on the PCIe slot (%uW).\n",
				  pci_घातer);
		अवरोध;
	हाल MLX5_PCI_POWER_SUFFICIENT_REPORTED:
		mlx5_core_info_rl(dev,
				  "PCIe slot advertised sufficient power (%uW).\n",
				  pci_घातer);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक pcie_core(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ type, व्योम *data)
अणु
	काष्ठा mlx5_event_nb    *event_nb = mlx5_nb_cof(nb,
							काष्ठा mlx5_event_nb,
							nb);
	काष्ठा mlx5_events      *events   = event_nb->ctx;
	काष्ठा mlx5_eqe         *eqe      = data;

	चयन (eqe->sub_type) अणु
	हाल MLX5_GENERAL_SUBTYPE_PCI_POWER_CHANGE_EVENT:
			queue_work(events->wq, &events->pcie_core_work);
		अवरोध;
	शेष:
		वापस NOTIFY_DONE;
	पूर्ण

	वापस NOTIFY_OK;
पूर्ण

व्योम mlx5_get_pme_stats(काष्ठा mlx5_core_dev *dev, काष्ठा mlx5_pme_stats *stats)
अणु
	*stats = dev->priv.events->pme_stats;
पूर्ण

/* क्रमward event as is to रेजिस्टरed पूर्णांकerfaces (mlx5e/mlx5_ib) */
अटल पूर्णांक क्रमward_event(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ event, व्योम *data)
अणु
	काष्ठा mlx5_event_nb *event_nb = mlx5_nb_cof(nb, काष्ठा mlx5_event_nb, nb);
	काष्ठा mlx5_events   *events   = event_nb->ctx;
	काष्ठा mlx5_eqe      *eqe      = data;

	mlx5_core_dbg(events->dev, "Async eqe type %s, subtype (%d) forward to interfaces\n",
		      eqe_type_str(eqe->type), eqe->sub_type);
	atomic_notअगरier_call_chain(&events->fw_nh, event, data);
	वापस NOTIFY_OK;
पूर्ण

पूर्णांक mlx5_events_init(काष्ठा mlx5_core_dev *dev)
अणु
	काष्ठा mlx5_events *events = kzalloc(माप(*events), GFP_KERNEL);

	अगर (!events)
		वापस -ENOMEM;

	ATOMIC_INIT_NOTIFIER_HEAD(&events->fw_nh);
	events->dev = dev;
	dev->priv.events = events;
	events->wq = create_singlethपढ़ो_workqueue("mlx5_events");
	अगर (!events->wq) अणु
		kमुक्त(events);
		वापस -ENOMEM;
	पूर्ण
	INIT_WORK(&events->pcie_core_work, mlx5_pcie_event);
	BLOCKING_INIT_NOTIFIER_HEAD(&events->sw_nh);

	वापस 0;
पूर्ण

व्योम mlx5_events_cleanup(काष्ठा mlx5_core_dev *dev)
अणु
	destroy_workqueue(dev->priv.events->wq);
	kvमुक्त(dev->priv.events);
पूर्ण

व्योम mlx5_events_start(काष्ठा mlx5_core_dev *dev)
अणु
	काष्ठा mlx5_events *events = dev->priv.events;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(events_nbs_ref); i++) अणु
		events->notअगरiers[i].nb  = events_nbs_ref[i];
		events->notअगरiers[i].ctx = events;
		mlx5_eq_notअगरier_रेजिस्टर(dev, &events->notअगरiers[i].nb);
	पूर्ण
पूर्ण

व्योम mlx5_events_stop(काष्ठा mlx5_core_dev *dev)
अणु
	काष्ठा mlx5_events *events = dev->priv.events;
	पूर्णांक i;

	क्रम (i = ARRAY_SIZE(events_nbs_ref) - 1; i >= 0 ; i--)
		mlx5_eq_notअगरier_unरेजिस्टर(dev, &events->notअगरiers[i].nb);
	flush_workqueue(events->wq);
पूर्ण

/* This API is used only क्रम processing and क्रमwarding firmware
 * events to mlx5 consumer.
 */
पूर्णांक mlx5_notअगरier_रेजिस्टर(काष्ठा mlx5_core_dev *dev, काष्ठा notअगरier_block *nb)
अणु
	काष्ठा mlx5_events *events = dev->priv.events;

	वापस atomic_notअगरier_chain_रेजिस्टर(&events->fw_nh, nb);
पूर्ण
EXPORT_SYMBOL(mlx5_notअगरier_रेजिस्टर);

पूर्णांक mlx5_notअगरier_unरेजिस्टर(काष्ठा mlx5_core_dev *dev, काष्ठा notअगरier_block *nb)
अणु
	काष्ठा mlx5_events *events = dev->priv.events;

	वापस atomic_notअगरier_chain_unरेजिस्टर(&events->fw_nh, nb);
पूर्ण
EXPORT_SYMBOL(mlx5_notअगरier_unरेजिस्टर);

पूर्णांक mlx5_notअगरier_call_chain(काष्ठा mlx5_events *events, अचिन्हित पूर्णांक event, व्योम *data)
अणु
	वापस atomic_notअगरier_call_chain(&events->fw_nh, event, data);
पूर्ण

/* This API is used only क्रम processing and क्रमwarding driver-specअगरic
 * events to mlx5 consumers.
 */
पूर्णांक mlx5_blocking_notअगरier_रेजिस्टर(काष्ठा mlx5_core_dev *dev, काष्ठा notअगरier_block *nb)
अणु
	काष्ठा mlx5_events *events = dev->priv.events;

	वापस blocking_notअगरier_chain_रेजिस्टर(&events->sw_nh, nb);
पूर्ण

पूर्णांक mlx5_blocking_notअगरier_unरेजिस्टर(काष्ठा mlx5_core_dev *dev, काष्ठा notअगरier_block *nb)
अणु
	काष्ठा mlx5_events *events = dev->priv.events;

	वापस blocking_notअगरier_chain_unरेजिस्टर(&events->sw_nh, nb);
पूर्ण

पूर्णांक mlx5_blocking_notअगरier_call_chain(काष्ठा mlx5_core_dev *dev, अचिन्हित पूर्णांक event,
				      व्योम *data)
अणु
	काष्ठा mlx5_events *events = dev->priv.events;

	वापस blocking_notअगरier_call_chain(&events->sw_nh, event, data);
पूर्ण

व्योम mlx5_events_work_enqueue(काष्ठा mlx5_core_dev *dev, काष्ठा work_काष्ठा *work)
अणु
	queue_work(dev->priv.events->wq, work);
पूर्ण
