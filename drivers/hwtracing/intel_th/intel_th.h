<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Intel(R) Trace Hub data काष्ठाures
 *
 * Copyright (C) 2014-2015 Intel Corporation.
 */

#अगर_अघोषित __INTEL_TH_H__
#घोषणा __INTEL_TH_H__

#समावेश <linux/irqवापस.h>

/* पूर्णांकel_th_device device types */
क्रमागत अणु
	/* Devices that generate trace data */
	INTEL_TH_SOURCE = 0,
	/* Output ports (MSC, PTI) */
	INTEL_TH_OUTPUT,
	/* Switch, the Global Trace Hub (GTH) */
	INTEL_TH_SWITCH,
पूर्ण;

काष्ठा पूर्णांकel_th_device;

/**
 * काष्ठा पूर्णांकel_th_output - descriptor INTEL_TH_OUTPUT type devices
 * @port:	output port number, asचिन्हित by the चयन
 * @type:	GTH_अणुMSU,CTP,PTIपूर्ण
 * @scratchpad:	scratchpad bits to flag when this output is enabled
 * @multiblock:	true क्रम multiblock output configuration
 * @active:	true when this output is enabled
 * @रुको_empty:	रुको क्रम device pipeline to be empty
 *
 * Output port descriptor, used by चयन driver to tell which output
 * port this output device corresponds to. Filled in at output device's
 * probe समय by चयन::assign(). Passed from output device driver to
 * चयन related code to enable/disable its port.
 */
काष्ठा पूर्णांकel_th_output अणु
	पूर्णांक		port;
	अचिन्हित पूर्णांक	type;
	अचिन्हित पूर्णांक	scratchpad;
	bool		multiblock;
	bool		active;
पूर्ण;

/**
 * काष्ठा पूर्णांकel_th_drvdata - describes hardware capabilities and quirks
 * @tscu_enable:	device needs SW to enable समय stamping unit
 * @multi_is_broken:	device has multiblock mode is broken
 * @has_mपूर्णांकctl:	device has पूर्णांकerrupt control (MINTCTL) रेजिस्टर
 * @host_mode_only:	device can only operate in 'host debugger' mode
 */
काष्ठा पूर्णांकel_th_drvdata अणु
	अचिन्हित पूर्णांक	tscu_enable        : 1,
			multi_is_broken    : 1,
			has_mपूर्णांकctl        : 1,
			host_mode_only     : 1;
पूर्ण;

#घोषणा INTEL_TH_CAP(_th, _cap) ((_th)->drvdata ? (_th)->drvdata->_cap : 0)

/**
 * काष्ठा पूर्णांकel_th_device - device on the पूर्णांकel_th bus
 * @dev:		device
 * @drvdata:		hardware capabilities/quirks
 * @resource:		array of resources available to this device
 * @num_resources:	number of resources in @resource array
 * @type:		INTEL_TH_अणुSOURCE,OUTPUT,SWITCHपूर्ण
 * @id:			device instance or -1
 * @host_mode:		Intel TH is controlled by an बाह्यal debug host
 * @output:		output descriptor क्रम INTEL_TH_OUTPUT devices
 * @name:		device name to match the driver
 */
काष्ठा पूर्णांकel_th_device अणु
	काष्ठा device		dev;
	स्थिर काष्ठा पूर्णांकel_th_drvdata *drvdata;
	काष्ठा resource		*resource;
	अचिन्हित पूर्णांक		num_resources;
	अचिन्हित पूर्णांक		type;
	पूर्णांक			id;

	/* INTEL_TH_SWITCH specअगरic */
	bool			host_mode;

	/* INTEL_TH_OUTPUT specअगरic */
	काष्ठा पूर्णांकel_th_output	output;

	अक्षर		name[];
पूर्ण;

#घोषणा to_पूर्णांकel_th_device(_d)				\
	container_of((_d), काष्ठा पूर्णांकel_th_device, dev)

/**
 * पूर्णांकel_th_device_get_resource() - obtain @num'th resource of type @type
 * @thdev:	the device to search the resource क्रम
 * @type:	resource type
 * @num:	number of the resource
 */
अटल अंतरभूत काष्ठा resource *
पूर्णांकel_th_device_get_resource(काष्ठा पूर्णांकel_th_device *thdev, अचिन्हित पूर्णांक type,
			     अचिन्हित पूर्णांक num)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < thdev->num_resources; i++)
		अगर (resource_type(&thdev->resource[i]) == type && !num--)
			वापस &thdev->resource[i];

	वापस शून्य;
पूर्ण

/*
 * GTH, output ports configuration
 */
क्रमागत अणु
	GTH_NONE = 0,
	GTH_MSU,	/* memory/usb */
	GTH_CTP,	/* Common Trace Port */
	GTH_LPP,	/* Low Power Path */
	GTH_PTI,	/* MIPI-PTI */
पूर्ण;

/**
 * पूर्णांकel_th_output_asचिन्हित() - अगर an output device is asचिन्हित to a चयन port
 * @thdev:	the output device
 *
 * Return:	true अगर the device is INTEL_TH_OUTPUT *and* is asचिन्हित a port
 */
अटल अंतरभूत bool
पूर्णांकel_th_output_asचिन्हित(काष्ठा पूर्णांकel_th_device *thdev)
अणु
	वापस thdev->type == INTEL_TH_OUTPUT &&
		(thdev->output.port >= 0 ||
		 thdev->output.type == GTH_NONE);
पूर्ण

/**
 * काष्ठा पूर्णांकel_th_driver - driver क्रम an पूर्णांकel_th_device device
 * @driver:	generic driver
 * @probe:	probe method
 * @हटाओ:	हटाओ method
 * @assign:	match a given output type device against available outमाला_दो
 * @unassign:	deassociate an output type device from an output port
 * @enable:	enable tracing क्रम a given output device
 * @disable:	disable tracing क्रम a given output device
 * @irq:	पूर्णांकerrupt callback
 * @activate:	enable tracing on the output's side
 * @deactivate:	disable tracing on the output's side
 * @fops:	file operations क्रम device nodes
 * @attr_group:	attributes provided by the driver
 *
 * Callbacks @probe and @हटाओ are required क्रम all device types.
 * Switch device driver needs to fill in @assign, @enable and @disable
 * callbacks.
 */
काष्ठा पूर्णांकel_th_driver अणु
	काष्ठा device_driver	driver;
	पूर्णांक			(*probe)(काष्ठा पूर्णांकel_th_device *thdev);
	व्योम			(*हटाओ)(काष्ठा पूर्णांकel_th_device *thdev);
	/* चयन (GTH) ops */
	पूर्णांक			(*assign)(काष्ठा पूर्णांकel_th_device *thdev,
					  काष्ठा पूर्णांकel_th_device *othdev);
	व्योम			(*unassign)(काष्ठा पूर्णांकel_th_device *thdev,
					    काष्ठा पूर्णांकel_th_device *othdev);
	व्योम			(*enable)(काष्ठा पूर्णांकel_th_device *thdev,
					  काष्ठा पूर्णांकel_th_output *output);
	व्योम			(*trig_चयन)(काष्ठा पूर्णांकel_th_device *thdev,
					       काष्ठा पूर्णांकel_th_output *output);
	व्योम			(*disable)(काष्ठा पूर्णांकel_th_device *thdev,
					   काष्ठा पूर्णांकel_th_output *output);
	/* output ops */
	irqवापस_t		(*irq)(काष्ठा पूर्णांकel_th_device *thdev);
	व्योम			(*रुको_empty)(काष्ठा पूर्णांकel_th_device *thdev);
	पूर्णांक			(*activate)(काष्ठा पूर्णांकel_th_device *thdev);
	व्योम			(*deactivate)(काष्ठा पूर्णांकel_th_device *thdev);
	/* file_operations क्रम those who want a device node */
	स्थिर काष्ठा file_operations *fops;
	/* optional attributes */
	स्थिर काष्ठा attribute_group *attr_group;

	/* source ops */
	पूर्णांक			(*set_output)(काष्ठा पूर्णांकel_th_device *thdev,
					      अचिन्हित पूर्णांक master);
पूर्ण;

#घोषणा to_पूर्णांकel_th_driver(_d)					\
	container_of((_d), काष्ठा पूर्णांकel_th_driver, driver)

#घोषणा to_पूर्णांकel_th_driver_or_null(_d)		\
	((_d) ? to_पूर्णांकel_th_driver(_d) : शून्य)

/*
 * Subdevice tree काष्ठाure is as follows:
 * + काष्ठा पूर्णांकel_th device (pci; dev_अणुget,setपूर्ण_drvdata()
 *   + काष्ठा पूर्णांकel_th_device INTEL_TH_SWITCH (GTH)
 *     + काष्ठा पूर्णांकel_th_device INTEL_TH_OUTPUT (MSU, PTI)
 *   + काष्ठा पूर्णांकel_th_device INTEL_TH_SOURCE (STH)
 *
 * In other words, INTEL_TH_OUTPUT devices are children of INTEL_TH_SWITCH;
 * INTEL_TH_SWITCH and INTEL_TH_SOURCE are children of the पूर्णांकel_th device.
 */
अटल अंतरभूत काष्ठा पूर्णांकel_th_device *
to_पूर्णांकel_th_parent(काष्ठा पूर्णांकel_th_device *thdev)
अणु
	काष्ठा device *parent = thdev->dev.parent;

	अगर (!parent)
		वापस शून्य;

	वापस to_पूर्णांकel_th_device(parent);
पूर्ण

अटल अंतरभूत काष्ठा पूर्णांकel_th *to_पूर्णांकel_th(काष्ठा पूर्णांकel_th_device *thdev)
अणु
	अगर (thdev->type == INTEL_TH_OUTPUT)
		thdev = to_पूर्णांकel_th_parent(thdev);

	अगर (WARN_ON_ONCE(!thdev || thdev->type == INTEL_TH_OUTPUT))
		वापस शून्य;

	वापस dev_get_drvdata(thdev->dev.parent);
पूर्ण

काष्ठा पूर्णांकel_th *
पूर्णांकel_th_alloc(काष्ठा device *dev, स्थिर काष्ठा पूर्णांकel_th_drvdata *drvdata,
	       काष्ठा resource *devres, अचिन्हित पूर्णांक ndevres);
व्योम पूर्णांकel_th_मुक्त(काष्ठा पूर्णांकel_th *th);

पूर्णांक पूर्णांकel_th_driver_रेजिस्टर(काष्ठा पूर्णांकel_th_driver *thdrv);
व्योम पूर्णांकel_th_driver_unरेजिस्टर(काष्ठा पूर्णांकel_th_driver *thdrv);

पूर्णांक पूर्णांकel_th_trace_enable(काष्ठा पूर्णांकel_th_device *thdev);
पूर्णांक पूर्णांकel_th_trace_चयन(काष्ठा पूर्णांकel_th_device *thdev);
पूर्णांक पूर्णांकel_th_trace_disable(काष्ठा पूर्णांकel_th_device *thdev);
पूर्णांक पूर्णांकel_th_set_output(काष्ठा पूर्णांकel_th_device *thdev,
			अचिन्हित पूर्णांक master);
पूर्णांक पूर्णांकel_th_output_enable(काष्ठा पूर्णांकel_th *th, अचिन्हित पूर्णांक otype);

क्रमागत th_mmio_idx अणु
	TH_MMIO_CONFIG = 0,
	TH_MMIO_SW = 1,
	TH_MMIO_RTIT = 2,
	TH_MMIO_END,
पूर्ण;

#घोषणा TH_POSSIBLE_OUTPUTS	8
/* Total number of possible subdevices: outमाला_दो + GTH + STH */
#घोषणा TH_SUBDEVICE_MAX	(TH_POSSIBLE_OUTPUTS + 2)
#घोषणा TH_CONFIGURABLE_MASTERS 256
#घोषणा TH_MSC_MAX		2

/* Maximum IRQ vectors */
#घोषणा TH_NVEC_MAX		8

/**
 * काष्ठा पूर्णांकel_th - Intel TH controller
 * @dev:	driver core's device
 * @thdev:	subdevices
 * @hub:	"switch" subdevice (GTH)
 * @resource:	resources of the entire controller
 * @num_thdevs:	number of devices in the @thdev array
 * @num_resources:	number of resources in the @resource array
 * @irq:	irq number
 * @num_irqs:	number of IRQs is use
 * @id:		this Intel TH controller's device ID in the प्रणाली
 * @major:	device node major क्रम output devices
 */
काष्ठा पूर्णांकel_th अणु
	काष्ठा device		*dev;

	काष्ठा पूर्णांकel_th_device	*thdev[TH_SUBDEVICE_MAX];
	काष्ठा पूर्णांकel_th_device	*hub;
	स्थिर काष्ठा पूर्णांकel_th_drvdata	*drvdata;

	काष्ठा resource		resource[TH_MMIO_END];
	पूर्णांक			(*activate)(काष्ठा पूर्णांकel_th *);
	व्योम			(*deactivate)(काष्ठा पूर्णांकel_th *);
	अचिन्हित पूर्णांक		num_thdevs;
	अचिन्हित पूर्णांक		num_resources;
	पूर्णांक			irq;
	पूर्णांक			num_irqs;

	पूर्णांक			id;
	पूर्णांक			major;
#अगर_घोषित CONFIG_MODULES
	काष्ठा work_काष्ठा	request_module_work;
#पूर्ण_अगर /* CONFIG_MODULES */
#अगर_घोषित CONFIG_INTEL_TH_DEBUG
	काष्ठा dentry		*dbg;
#पूर्ण_अगर
पूर्ण;

अटल अंतरभूत काष्ठा पूर्णांकel_th_device *
to_पूर्णांकel_th_hub(काष्ठा पूर्णांकel_th_device *thdev)
अणु
	अगर (thdev->type == INTEL_TH_SWITCH)
		वापस thdev;
	अन्यथा अगर (thdev->type == INTEL_TH_OUTPUT)
		वापस to_पूर्णांकel_th_parent(thdev);

	वापस to_पूर्णांकel_th(thdev)->hub;
पूर्ण

/*
 * Register winकरोws
 */
क्रमागत अणु
	/* Global Trace Hub (GTH) */
	REG_GTH_OFFSET		= 0x0000,
	REG_GTH_LENGTH		= 0x2000,

	/* Timestamp counter unit (TSCU) */
	REG_TSCU_OFFSET		= 0x2000,
	REG_TSCU_LENGTH		= 0x1000,

	REG_CTS_OFFSET		= 0x3000,
	REG_CTS_LENGTH		= 0x1000,

	/* Software Trace Hub (STH) [0x4000..0x4fff] */
	REG_STH_OFFSET		= 0x4000,
	REG_STH_LENGTH		= 0x2000,

	/* Memory Storage Unit (MSU) [0xa0000..0xa1fff] */
	REG_MSU_OFFSET		= 0xa0000,
	REG_MSU_LENGTH		= 0x02000,

	/* Internal MSU trace buffer [0x80000..0x9ffff] */
	BUF_MSU_OFFSET		= 0x80000,
	BUF_MSU_LENGTH		= 0x20000,

	/* PTI output == same winकरोw as GTH */
	REG_PTI_OFFSET		= REG_GTH_OFFSET,
	REG_PTI_LENGTH		= REG_GTH_LENGTH,

	/* DCI Handler (DCIH) == some winकरोw as MSU */
	REG_DCIH_OFFSET		= REG_MSU_OFFSET,
	REG_DCIH_LENGTH		= REG_MSU_LENGTH,
पूर्ण;

/*
 * Scratchpad bits: tell firmware and बाह्यal debuggers
 * what we are up to.
 */
क्रमागत अणु
	/* Memory is the primary destination */
	SCRPD_MEM_IS_PRIM_DEST		= BIT(0),
	/* XHCI DbC is the primary destination */
	SCRPD_DBC_IS_PRIM_DEST		= BIT(1),
	/* PTI is the primary destination */
	SCRPD_PTI_IS_PRIM_DEST		= BIT(2),
	/* BSSB is the primary destination */
	SCRPD_BSSB_IS_PRIM_DEST		= BIT(3),
	/* PTI is the alternate destination */
	SCRPD_PTI_IS_ALT_DEST		= BIT(4),
	/* BSSB is the alternate destination */
	SCRPD_BSSB_IS_ALT_DEST		= BIT(5),
	/* DeepSx निकास occurred */
	SCRPD_DEEPSX_EXIT		= BIT(6),
	/* S4 निकास occurred */
	SCRPD_S4_EXIT			= BIT(7),
	/* S5 निकास occurred */
	SCRPD_S5_EXIT			= BIT(8),
	/* MSU controller 0/1 is enabled */
	SCRPD_MSC0_IS_ENABLED		= BIT(9),
	SCRPD_MSC1_IS_ENABLED		= BIT(10),
	/* Sx निकास occurred */
	SCRPD_SX_EXIT			= BIT(11),
	/* Trigger Unit is enabled */
	SCRPD_TRIGGER_IS_ENABLED	= BIT(12),
	SCRPD_ODLA_IS_ENABLED		= BIT(13),
	SCRPD_SOCHAP_IS_ENABLED		= BIT(14),
	SCRPD_STH_IS_ENABLED		= BIT(15),
	SCRPD_DCIH_IS_ENABLED		= BIT(16),
	SCRPD_VER_IS_ENABLED		= BIT(17),
	/* External debugger is using Intel TH */
	SCRPD_DEBUGGER_IN_USE		= BIT(24),
पूर्ण;

#पूर्ण_अगर
