<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2012, The Linux Foundation. All rights reserved.
 */

#अगर_अघोषित _LINUX_CORESIGHT_H
#घोषणा _LINUX_CORESIGHT_H

#समावेश <linux/device.h>
#समावेश <linux/पन.स>
#समावेश <linux/perf_event.h>
#समावेश <linux/sched.h>

/* Peripheral id रेजिस्टरs (0xFD0-0xFEC) */
#घोषणा CORESIGHT_PERIPHIDR4	0xfd0
#घोषणा CORESIGHT_PERIPHIDR5	0xfd4
#घोषणा CORESIGHT_PERIPHIDR6	0xfd8
#घोषणा CORESIGHT_PERIPHIDR7	0xfdC
#घोषणा CORESIGHT_PERIPHIDR0	0xfe0
#घोषणा CORESIGHT_PERIPHIDR1	0xfe4
#घोषणा CORESIGHT_PERIPHIDR2	0xfe8
#घोषणा CORESIGHT_PERIPHIDR3	0xfeC
/* Component id रेजिस्टरs (0xFF0-0xFFC) */
#घोषणा CORESIGHT_COMPIDR0	0xff0
#घोषणा CORESIGHT_COMPIDR1	0xff4
#घोषणा CORESIGHT_COMPIDR2	0xff8
#घोषणा CORESIGHT_COMPIDR3	0xffC

#घोषणा ETM_ARCH_V3_3		0x23
#घोषणा ETM_ARCH_V3_5		0x25
#घोषणा PFT_ARCH_V1_0		0x30
#घोषणा PFT_ARCH_V1_1		0x31

#घोषणा CORESIGHT_UNLOCK	0xc5acce55

बाह्य काष्ठा bus_type coresight_bustype;

क्रमागत coresight_dev_type अणु
	CORESIGHT_DEV_TYPE_NONE,
	CORESIGHT_DEV_TYPE_SINK,
	CORESIGHT_DEV_TYPE_LINK,
	CORESIGHT_DEV_TYPE_LINKSINK,
	CORESIGHT_DEV_TYPE_SOURCE,
	CORESIGHT_DEV_TYPE_HELPER,
	CORESIGHT_DEV_TYPE_ECT,
पूर्ण;

क्रमागत coresight_dev_subtype_sink अणु
	CORESIGHT_DEV_SUBTYPE_SINK_NONE,
	CORESIGHT_DEV_SUBTYPE_SINK_PORT,
	CORESIGHT_DEV_SUBTYPE_SINK_BUFFER,
	CORESIGHT_DEV_SUBTYPE_SINK_SYSMEM,
	CORESIGHT_DEV_SUBTYPE_SINK_PERCPU_SYSMEM,
पूर्ण;

क्रमागत coresight_dev_subtype_link अणु
	CORESIGHT_DEV_SUBTYPE_LINK_NONE,
	CORESIGHT_DEV_SUBTYPE_LINK_MERG,
	CORESIGHT_DEV_SUBTYPE_LINK_SPLIT,
	CORESIGHT_DEV_SUBTYPE_LINK_FIFO,
पूर्ण;

क्रमागत coresight_dev_subtype_source अणु
	CORESIGHT_DEV_SUBTYPE_SOURCE_NONE,
	CORESIGHT_DEV_SUBTYPE_SOURCE_PROC,
	CORESIGHT_DEV_SUBTYPE_SOURCE_BUS,
	CORESIGHT_DEV_SUBTYPE_SOURCE_SOFTWARE,
पूर्ण;

क्रमागत coresight_dev_subtype_helper अणु
	CORESIGHT_DEV_SUBTYPE_HELPER_NONE,
	CORESIGHT_DEV_SUBTYPE_HELPER_CATU,
पूर्ण;

/* Embedded Cross Trigger (ECT) sub-types */
क्रमागत coresight_dev_subtype_ect अणु
	CORESIGHT_DEV_SUBTYPE_ECT_NONE,
	CORESIGHT_DEV_SUBTYPE_ECT_CTI,
पूर्ण;

/**
 * जोड़ coresight_dev_subtype - further अक्षरacterisation of a type
 * @sink_subtype:	type of sink this component is, as defined
 *			by @coresight_dev_subtype_sink.
 * @link_subtype:	type of link this component is, as defined
 *			by @coresight_dev_subtype_link.
 * @source_subtype:	type of source this component is, as defined
 *			by @coresight_dev_subtype_source.
 * @helper_subtype:	type of helper this component is, as defined
 *			by @coresight_dev_subtype_helper.
 * @ect_subtype:        type of cross trigger this component is, as
 *			defined by @coresight_dev_subtype_ect
 */
जोड़ coresight_dev_subtype अणु
	/* We have some devices which acts as LINK and SINK */
	काष्ठा अणु
		क्रमागत coresight_dev_subtype_sink sink_subtype;
		क्रमागत coresight_dev_subtype_link link_subtype;
	पूर्ण;
	क्रमागत coresight_dev_subtype_source source_subtype;
	क्रमागत coresight_dev_subtype_helper helper_subtype;
	क्रमागत coresight_dev_subtype_ect ect_subtype;
पूर्ण;

/**
 * काष्ठा coresight_platक्रमm_data - data harvested from the firmware
 * specअगरication.
 *
 * @nr_inport:	Number of elements क्रम the input connections.
 * @nr_outport:	Number of elements क्रम the output connections.
 * @conns:	Sparse array of nr_outport connections from this component.
 */
काष्ठा coresight_platक्रमm_data अणु
	पूर्णांक nr_inport;
	पूर्णांक nr_outport;
	काष्ठा coresight_connection *conns;
पूर्ण;

/**
 * काष्ठा csdev_access - Abstraction of a CoreSight device access.
 *
 * @io_mem	: True अगर the device has memory mapped I/O
 * @base	: When io_mem == true, base address of the component
 * @पढ़ो	: Read from the given "offset" of the given instance.
 * @ग_लिखो	: Write "val" to the given "offset".
 */
काष्ठा csdev_access अणु
	bool io_mem;
	जोड़ अणु
		व्योम __iomem *base;
		काष्ठा अणु
			u64 (*पढ़ो)(u32 offset, bool relaxed, bool _64bit);
			व्योम (*ग_लिखो)(u64 val, u32 offset, bool relaxed,
				      bool _64bit);
		पूर्ण;
	पूर्ण;
पूर्ण;

#घोषणा CSDEV_ACCESS_IOMEM(_addr)		\
	((काष्ठा csdev_access)	अणु		\
		.io_mem		= true,		\
		.base		= (_addr),	\
	पूर्ण)

/**
 * काष्ठा coresight_desc - description of a component required from drivers
 * @type:	as defined by @coresight_dev_type.
 * @subtype:	as defined by @coresight_dev_subtype.
 * @ops:	generic operations क्रम this component, as defined
 *		by @coresight_ops.
 * @pdata:	platक्रमm data collected from DT.
 * @dev:	The device entity associated to this component.
 * @groups:	operations specअगरic to this component. These will end up
 *		in the component's sysfs sub-directory.
 * @name:	name क्रम the coresight device, also shown under sysfs.
 * @access:	Describe access to the device
 */
काष्ठा coresight_desc अणु
	क्रमागत coresight_dev_type type;
	जोड़ coresight_dev_subtype subtype;
	स्थिर काष्ठा coresight_ops *ops;
	काष्ठा coresight_platक्रमm_data *pdata;
	काष्ठा device *dev;
	स्थिर काष्ठा attribute_group **groups;
	स्थिर अक्षर *name;
	काष्ठा csdev_access access;
पूर्ण;

/**
 * काष्ठा coresight_connection - representation of a single connection
 * @outport:	a connection's output port number.
 * @child_port:	remote component's port number @output is connected to.
 * @chid_fwnode: remote component's fwnode handle.
 * @child_dev:	a @coresight_device representation of the component
		connected to @outport.
 * @link: Representation of the connection as a sysfs link.
 */
काष्ठा coresight_connection अणु
	पूर्णांक outport;
	पूर्णांक child_port;
	काष्ठा fwnode_handle *child_fwnode;
	काष्ठा coresight_device *child_dev;
	काष्ठा coresight_sysfs_link *link;
पूर्ण;

/**
 * काष्ठा coresight_sysfs_link - representation of a connection in sysfs.
 * @orig:		Originating (master) coresight device क्रम the link.
 * @orig_name:		Name to use क्रम the link orig->target.
 * @target:		Target (slave) coresight device क्रम the link.
 * @target_name:	Name to use क्रम the link target->orig.
 */
काष्ठा coresight_sysfs_link अणु
	काष्ठा coresight_device *orig;
	स्थिर अक्षर *orig_name;
	काष्ठा coresight_device *target;
	स्थिर अक्षर *target_name;
पूर्ण;

/**
 * काष्ठा coresight_device - representation of a device as used by the framework
 * @pdata:	Platक्रमm data with device connections associated to this device.
 * @type:	as defined by @coresight_dev_type.
 * @subtype:	as defined by @coresight_dev_subtype.
 * @ops:	generic operations क्रम this component, as defined
 *		by @coresight_ops.
 * @access:	Device i/o access असलtraction क्रम this device.
 * @dev:	The device entity associated to this component.
 * @refcnt:	keep track of what is in use.
 * @orphan:	true अगर the component has connections that haven't been linked.
 * @enable:	'true' अगर component is currently part of an active path.
 * @activated:	'true' only अगर a _sink_ has been activated.  A sink can be
 *		activated but not yet enabled.  Enabling क्रम a _sink_
 *		happens when a source has been selected and a path is enabled
 *		from source to that sink.
 * @ea:		Device attribute क्रम sink representation under PMU directory.
 * @def_sink:	cached reference to शेष sink found क्रम this device.
 * @ect_dev:	Associated cross trigger device. Not part of the trace data
 *		path or connections.
 * @nr_links:   number of sysfs links created to other components from this
 *		device. These will appear in the "connections" group.
 * @has_conns_grp: Have added a "connections" group क्रम sysfs links.
 */
काष्ठा coresight_device अणु
	काष्ठा coresight_platक्रमm_data *pdata;
	क्रमागत coresight_dev_type type;
	जोड़ coresight_dev_subtype subtype;
	स्थिर काष्ठा coresight_ops *ops;
	काष्ठा csdev_access access;
	काष्ठा device dev;
	atomic_t *refcnt;
	bool orphan;
	bool enable;	/* true only अगर configured as part of a path */
	/* sink specअगरic fields */
	bool activated;	/* true only अगर a sink is part of a path */
	काष्ठा dev_ext_attribute *ea;
	काष्ठा coresight_device *def_sink;
	/* cross trigger handling */
	काष्ठा coresight_device *ect_dev;
	/* sysfs links between components */
	पूर्णांक nr_links;
	bool has_conns_grp;
	bool ect_enabled; /* true only अगर associated ect device is enabled */
पूर्ण;

/*
 * coresight_dev_list - Mapping क्रम devices to "name" index क्रम device
 * names.
 *
 * @nr_idx:		Number of entries alपढ़ोy allocated.
 * @pfx:		Prefix pattern क्रम device name.
 * @fwnode_list:	Array of fwnode_handles associated with each allocated
 *			index, upto nr_idx entries.
 */
काष्ठा coresight_dev_list अणु
	पूर्णांक			nr_idx;
	स्थिर अक्षर		*pfx;
	काष्ठा fwnode_handle	**fwnode_list;
पूर्ण;

#घोषणा DEFINE_CORESIGHT_DEVLIST(var, dev_pfx)				\
अटल काष्ठा coresight_dev_list (var) = अणु				\
						.pfx = dev_pfx,		\
						.nr_idx = 0,		\
						.fwnode_list = शून्य,	\
पूर्ण

#घोषणा to_coresight_device(d) container_of(d, काष्ठा coresight_device, dev)

#घोषणा source_ops(csdev)	csdev->ops->source_ops
#घोषणा sink_ops(csdev)		csdev->ops->sink_ops
#घोषणा link_ops(csdev)		csdev->ops->link_ops
#घोषणा helper_ops(csdev)	csdev->ops->helper_ops
#घोषणा ect_ops(csdev)		csdev->ops->ect_ops

/**
 * काष्ठा coresight_ops_sink - basic operations क्रम a sink
 * Operations available क्रम sinks
 * @enable:		enables the sink.
 * @disable:		disables the sink.
 * @alloc_buffer:	initialises perf's ring buffer क्रम trace collection.
 * @मुक्त_buffer:	release memory allocated in @get_config.
 * @update_buffer:	update buffer poपूर्णांकers after a trace session.
 */
काष्ठा coresight_ops_sink अणु
	पूर्णांक (*enable)(काष्ठा coresight_device *csdev, u32 mode, व्योम *data);
	पूर्णांक (*disable)(काष्ठा coresight_device *csdev);
	व्योम *(*alloc_buffer)(काष्ठा coresight_device *csdev,
			      काष्ठा perf_event *event, व्योम **pages,
			      पूर्णांक nr_pages, bool overग_लिखो);
	व्योम (*मुक्त_buffer)(व्योम *config);
	अचिन्हित दीर्घ (*update_buffer)(काष्ठा coresight_device *csdev,
			      काष्ठा perf_output_handle *handle,
			      व्योम *sink_config);
पूर्ण;

/**
 * काष्ठा coresight_ops_link - basic operations क्रम a link
 * Operations available क्रम links.
 * @enable:	enables flow between iport and oport.
 * @disable:	disables flow between iport and oport.
 */
काष्ठा coresight_ops_link अणु
	पूर्णांक (*enable)(काष्ठा coresight_device *csdev, पूर्णांक iport, पूर्णांक oport);
	व्योम (*disable)(काष्ठा coresight_device *csdev, पूर्णांक iport, पूर्णांक oport);
पूर्ण;

/**
 * काष्ठा coresight_ops_source - basic operations क्रम a source
 * Operations available क्रम sources.
 * @cpu_id:	वापसs the value of the CPU number this component
 *		is associated to.
 * @trace_id:	वापसs the value of the component's trace ID as known
 *		to the HW.
 * @enable:	enables tracing क्रम a source.
 * @disable:	disables tracing क्रम a source.
 */
काष्ठा coresight_ops_source अणु
	पूर्णांक (*cpu_id)(काष्ठा coresight_device *csdev);
	पूर्णांक (*trace_id)(काष्ठा coresight_device *csdev);
	पूर्णांक (*enable)(काष्ठा coresight_device *csdev,
		      काष्ठा perf_event *event,  u32 mode);
	व्योम (*disable)(काष्ठा coresight_device *csdev,
			काष्ठा perf_event *event);
पूर्ण;

/**
 * काष्ठा coresight_ops_helper - Operations क्रम a helper device.
 *
 * All operations could pass in a device specअगरic data, which could
 * help the helper device to determine what to करो.
 *
 * @enable	: Enable the device
 * @disable	: Disable the device
 */
काष्ठा coresight_ops_helper अणु
	पूर्णांक (*enable)(काष्ठा coresight_device *csdev, व्योम *data);
	पूर्णांक (*disable)(काष्ठा coresight_device *csdev, व्योम *data);
पूर्ण;

/**
 * काष्ठा coresight_ops_ect - Ops क्रम an embedded cross trigger device
 *
 * @enable	: Enable the device
 * @disable	: Disable the device
 */
काष्ठा coresight_ops_ect अणु
	पूर्णांक (*enable)(काष्ठा coresight_device *csdev);
	पूर्णांक (*disable)(काष्ठा coresight_device *csdev);
पूर्ण;

काष्ठा coresight_ops अणु
	स्थिर काष्ठा coresight_ops_sink *sink_ops;
	स्थिर काष्ठा coresight_ops_link *link_ops;
	स्थिर काष्ठा coresight_ops_source *source_ops;
	स्थिर काष्ठा coresight_ops_helper *helper_ops;
	स्थिर काष्ठा coresight_ops_ect *ect_ops;
पूर्ण;

#अगर IS_ENABLED(CONFIG_CORESIGHT)

अटल अंतरभूत u32 csdev_access_relaxed_पढ़ो32(काष्ठा csdev_access *csa,
					      u32 offset)
अणु
	अगर (likely(csa->io_mem))
		वापस पढ़ोl_relaxed(csa->base + offset);

	वापस csa->पढ़ो(offset, true, false);
पूर्ण

अटल अंतरभूत u32 csdev_access_पढ़ो32(काष्ठा csdev_access *csa, u32 offset)
अणु
	अगर (likely(csa->io_mem))
		वापस पढ़ोl(csa->base + offset);

	वापस csa->पढ़ो(offset, false, false);
पूर्ण

अटल अंतरभूत व्योम csdev_access_relaxed_ग_लिखो32(काष्ठा csdev_access *csa,
						u32 val, u32 offset)
अणु
	अगर (likely(csa->io_mem))
		ग_लिखोl_relaxed(val, csa->base + offset);
	अन्यथा
		csa->ग_लिखो(val, offset, true, false);
पूर्ण

अटल अंतरभूत व्योम csdev_access_ग_लिखो32(काष्ठा csdev_access *csa, u32 val, u32 offset)
अणु
	अगर (likely(csa->io_mem))
		ग_लिखोl(val, csa->base + offset);
	अन्यथा
		csa->ग_लिखो(val, offset, false, false);
पूर्ण

#अगर_घोषित CONFIG_64BIT

अटल अंतरभूत u64 csdev_access_relaxed_पढ़ो64(काष्ठा csdev_access *csa,
					      u32 offset)
अणु
	अगर (likely(csa->io_mem))
		वापस पढ़ोq_relaxed(csa->base + offset);

	वापस csa->पढ़ो(offset, true, true);
पूर्ण

अटल अंतरभूत u64 csdev_access_पढ़ो64(काष्ठा csdev_access *csa, u32 offset)
अणु
	अगर (likely(csa->io_mem))
		वापस पढ़ोq(csa->base + offset);

	वापस csa->पढ़ो(offset, false, true);
पूर्ण

अटल अंतरभूत व्योम csdev_access_relaxed_ग_लिखो64(काष्ठा csdev_access *csa,
						u64 val, u32 offset)
अणु
	अगर (likely(csa->io_mem))
		ग_लिखोq_relaxed(val, csa->base + offset);
	अन्यथा
		csa->ग_लिखो(val, offset, true, true);
पूर्ण

अटल अंतरभूत व्योम csdev_access_ग_लिखो64(काष्ठा csdev_access *csa, u64 val, u32 offset)
अणु
	अगर (likely(csa->io_mem))
		ग_लिखोq(val, csa->base + offset);
	अन्यथा
		csa->ग_लिखो(val, offset, false, true);
पूर्ण

#अन्यथा	/* !CONFIG_64BIT */

अटल अंतरभूत u64 csdev_access_relaxed_पढ़ो64(काष्ठा csdev_access *csa,
					      u32 offset)
अणु
	WARN_ON(1);
	वापस 0;
पूर्ण

अटल अंतरभूत u64 csdev_access_पढ़ो64(काष्ठा csdev_access *csa, u32 offset)
अणु
	WARN_ON(1);
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम csdev_access_relaxed_ग_लिखो64(काष्ठा csdev_access *csa,
						u64 val, u32 offset)
अणु
	WARN_ON(1);
पूर्ण

अटल अंतरभूत व्योम csdev_access_ग_लिखो64(काष्ठा csdev_access *csa, u64 val, u32 offset)
अणु
	WARN_ON(1);
पूर्ण
#पूर्ण_अगर	/* CONFIG_64BIT */

अटल अंतरभूत bool coresight_is_percpu_source(काष्ठा coresight_device *csdev)
अणु
	वापस csdev && (csdev->type == CORESIGHT_DEV_TYPE_SOURCE) &&
	       (csdev->subtype.source_subtype == CORESIGHT_DEV_SUBTYPE_SOURCE_PROC);
पूर्ण

अटल अंतरभूत bool coresight_is_percpu_sink(काष्ठा coresight_device *csdev)
अणु
	वापस csdev && (csdev->type == CORESIGHT_DEV_TYPE_SINK) &&
	       (csdev->subtype.sink_subtype == CORESIGHT_DEV_SUBTYPE_SINK_PERCPU_SYSMEM);
पूर्ण

बाह्य काष्ठा coresight_device *
coresight_रेजिस्टर(काष्ठा coresight_desc *desc);
बाह्य व्योम coresight_unरेजिस्टर(काष्ठा coresight_device *csdev);
बाह्य पूर्णांक coresight_enable(काष्ठा coresight_device *csdev);
बाह्य व्योम coresight_disable(काष्ठा coresight_device *csdev);
बाह्य पूर्णांक coresight_समयout(काष्ठा csdev_access *csa, u32 offset,
			     पूर्णांक position, पूर्णांक value);

बाह्य पूर्णांक coresight_claim_device(काष्ठा coresight_device *csdev);
बाह्य पूर्णांक coresight_claim_device_unlocked(काष्ठा coresight_device *csdev);

बाह्य व्योम coresight_disclaim_device(काष्ठा coresight_device *csdev);
बाह्य व्योम coresight_disclaim_device_unlocked(काष्ठा coresight_device *csdev);
बाह्य अक्षर *coresight_alloc_device_name(काष्ठा coresight_dev_list *devs,
					 काष्ठा device *dev);

बाह्य bool coresight_loses_context_with_cpu(काष्ठा device *dev);

u32 coresight_relaxed_पढ़ो32(काष्ठा coresight_device *csdev, u32 offset);
u32 coresight_पढ़ो32(काष्ठा coresight_device *csdev, u32 offset);
व्योम coresight_ग_लिखो32(काष्ठा coresight_device *csdev, u32 val, u32 offset);
व्योम coresight_relaxed_ग_लिखो32(काष्ठा coresight_device *csdev,
			       u32 val, u32 offset);
u64 coresight_relaxed_पढ़ो64(काष्ठा coresight_device *csdev, u32 offset);
u64 coresight_पढ़ो64(काष्ठा coresight_device *csdev, u32 offset);
व्योम coresight_relaxed_ग_लिखो64(काष्ठा coresight_device *csdev,
			       u64 val, u32 offset);
व्योम coresight_ग_लिखो64(काष्ठा coresight_device *csdev, u64 val, u32 offset);

#अन्यथा
अटल अंतरभूत काष्ठा coresight_device *
coresight_रेजिस्टर(काष्ठा coresight_desc *desc) अणु वापस शून्य; पूर्ण
अटल अंतरभूत व्योम coresight_unरेजिस्टर(काष्ठा coresight_device *csdev) अणुपूर्ण
अटल अंतरभूत पूर्णांक
coresight_enable(काष्ठा coresight_device *csdev) अणु वापस -ENOSYS; पूर्ण
अटल अंतरभूत व्योम coresight_disable(काष्ठा coresight_device *csdev) अणुपूर्ण

अटल अंतरभूत पूर्णांक coresight_समयout(काष्ठा csdev_access *csa, u32 offset,
				    पूर्णांक position, पूर्णांक value)
अणु
	वापस 1;
पूर्ण

अटल अंतरभूत पूर्णांक coresight_claim_device_unlocked(काष्ठा coresight_device *csdev)
अणु
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत पूर्णांक coresight_claim_device(काष्ठा coresight_device *csdev)
अणु
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत व्योम coresight_disclaim_device(काष्ठा coresight_device *csdev) अणुपूर्ण
अटल अंतरभूत व्योम coresight_disclaim_device_unlocked(काष्ठा coresight_device *csdev) अणुपूर्ण

अटल अंतरभूत bool coresight_loses_context_with_cpu(काष्ठा device *dev)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत u32 coresight_relaxed_पढ़ो32(काष्ठा coresight_device *csdev, u32 offset)
अणु
	WARN_ON_ONCE(1);
	वापस 0;
पूर्ण

अटल अंतरभूत u32 coresight_पढ़ो32(काष्ठा coresight_device *csdev, u32 offset)
अणु
	WARN_ON_ONCE(1);
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम coresight_ग_लिखो32(काष्ठा coresight_device *csdev, u32 val, u32 offset)
अणु
पूर्ण

अटल अंतरभूत व्योम coresight_relaxed_ग_लिखो32(काष्ठा coresight_device *csdev,
					     u32 val, u32 offset)
अणु
पूर्ण

अटल अंतरभूत u64 coresight_relaxed_पढ़ो64(काष्ठा coresight_device *csdev,
					   u32 offset)
अणु
	WARN_ON_ONCE(1);
	वापस 0;
पूर्ण

अटल अंतरभूत u64 coresight_पढ़ो64(काष्ठा coresight_device *csdev, u32 offset)
अणु
	WARN_ON_ONCE(1);
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम coresight_relaxed_ग_लिखो64(काष्ठा coresight_device *csdev,
					     u64 val, u32 offset)
अणु
पूर्ण

अटल अंतरभूत व्योम coresight_ग_लिखो64(काष्ठा coresight_device *csdev, u64 val, u32 offset)
अणु
पूर्ण

#पूर्ण_अगर		/* IS_ENABLED(CONFIG_CORESIGHT) */

बाह्य पूर्णांक coresight_get_cpu(काष्ठा device *dev);

काष्ठा coresight_platक्रमm_data *coresight_get_platक्रमm_data(काष्ठा device *dev);

#पूर्ण_अगर		/* _LINUX_COREISGHT_H */
