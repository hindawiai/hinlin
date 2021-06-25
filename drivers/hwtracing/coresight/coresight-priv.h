<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2011-2012, The Linux Foundation. All rights reserved.
 */

#अगर_अघोषित _CORESIGHT_PRIV_H
#घोषणा _CORESIGHT_PRIV_H

#समावेश <linux/amba/bus.h>
#समावेश <linux/bitops.h>
#समावेश <linux/पन.स>
#समावेश <linux/coresight.h>
#समावेश <linux/pm_runसमय.स>

/*
 * Coresight management रेजिस्टरs (0xf00-0xfcc)
 * 0xfa0 - 0xfa4: Management	रेजिस्टरs in PFTv1.0
 *		  Trace		रेजिस्टरs in PFTv1.1
 */
#घोषणा CORESIGHT_ITCTRL	0xf00
#घोषणा CORESIGHT_CLAIMSET	0xfa0
#घोषणा CORESIGHT_CLAIMCLR	0xfa4
#घोषणा CORESIGHT_LAR		0xfb0
#घोषणा CORESIGHT_LSR		0xfb4
#घोषणा CORESIGHT_DEVARCH	0xfbc
#घोषणा CORESIGHT_AUTHSTATUS	0xfb8
#घोषणा CORESIGHT_DEVID		0xfc8
#घोषणा CORESIGHT_DEVTYPE	0xfcc


/*
 * Coresight device CLAIM protocol.
 * See PSCI - ARM DEN 0022D, Section: 6.8.1 Debug and Trace save and restore.
 */
#घोषणा CORESIGHT_CLAIM_SELF_HOSTED	BIT(1)

#घोषणा TIMEOUT_US		100
#घोषणा BMVAL(val, lsb, msb)	((val & GENMASK(msb, lsb)) >> lsb)

#घोषणा ETM_MODE_EXCL_KERN	BIT(30)
#घोषणा ETM_MODE_EXCL_USER	BIT(31)

प्रकार u32 (*coresight_पढ़ो_fn)(स्थिर काष्ठा device *, u32 offset);
#घोषणा __coresight_simple_func(type, func, name, lo_off, hi_off)	\
अटल sमाप_प्रकार name##_show(काष्ठा device *_dev,				\
			   काष्ठा device_attribute *attr, अक्षर *buf)	\
अणु									\
	type *drvdata = dev_get_drvdata(_dev->parent);			\
	coresight_पढ़ो_fn fn = func;					\
	u64 val;							\
	pm_runसमय_get_sync(_dev->parent);				\
	अगर (fn)								\
		val = (u64)fn(_dev->parent, lo_off);			\
	अन्यथा								\
		val = coresight_पढ़ो_reg_pair(drvdata->base,		\
						 lo_off, hi_off);	\
	pm_runसमय_put_sync(_dev->parent);				\
	वापस scnम_लिखो(buf, PAGE_SIZE, "0x%llx\n", val);		\
पूर्ण									\
अटल DEVICE_ATTR_RO(name)

#घोषणा coresight_simple_func(type, func, name, offset)			\
	__coresight_simple_func(type, func, name, offset, -1)
#घोषणा coresight_simple_reg32(type, name, offset)			\
	__coresight_simple_func(type, शून्य, name, offset, -1)
#घोषणा coresight_simple_reg64(type, name, lo_off, hi_off)		\
	__coresight_simple_func(type, शून्य, name, lo_off, hi_off)

बाह्य स्थिर u32 coresight_barrier_pkt[4];
#घोषणा CORESIGHT_BARRIER_PKT_SIZE (माप(coresight_barrier_pkt))

क्रमागत eपंचांग_addr_type अणु
	ETM_ADDR_TYPE_NONE,
	ETM_ADDR_TYPE_SINGLE,
	ETM_ADDR_TYPE_RANGE,
	ETM_ADDR_TYPE_START,
	ETM_ADDR_TYPE_STOP,
पूर्ण;

क्रमागत cs_mode अणु
	CS_MODE_DISABLED,
	CS_MODE_SYSFS,
	CS_MODE_PERF,
पूर्ण;

/**
 * काष्ठा cs_buffer - keep track of a recording session' specअगरics
 * @cur:	index of the current buffer
 * @nr_pages:	max number of pages granted to us
 * @pid:	PID this cs_buffer beदीर्घs to
 * @offset:	offset within the current buffer
 * @data_size:	how much we collected in this run
 * @snapshot:	is this run in snapshot mode
 * @data_pages:	a handle the ring buffer
 */
काष्ठा cs_buffers अणु
	अचिन्हित पूर्णांक		cur;
	अचिन्हित पूर्णांक		nr_pages;
	pid_t			pid;
	अचिन्हित दीर्घ		offset;
	local_t			data_size;
	bool			snapshot;
	व्योम			**data_pages;
पूर्ण;

अटल अंतरभूत व्योम coresight_insert_barrier_packet(व्योम *buf)
अणु
	अगर (buf)
		स_नकल(buf, coresight_barrier_pkt, CORESIGHT_BARRIER_PKT_SIZE);
पूर्ण

अटल अंतरभूत व्योम CS_LOCK(व्योम __iomem *addr)
अणु
	करो अणु
		/* Wait क्रम things to settle */
		mb();
		ग_लिखोl_relaxed(0x0, addr + CORESIGHT_LAR);
	पूर्ण जबतक (0);
पूर्ण

अटल अंतरभूत व्योम CS_UNLOCK(व्योम __iomem *addr)
अणु
	करो अणु
		ग_लिखोl_relaxed(CORESIGHT_UNLOCK, addr + CORESIGHT_LAR);
		/* Make sure everyone has seen this */
		mb();
	पूर्ण जबतक (0);
पूर्ण

अटल अंतरभूत u64
coresight_पढ़ो_reg_pair(व्योम __iomem *addr, s32 lo_offset, s32 hi_offset)
अणु
	u64 val;

	val = पढ़ोl_relaxed(addr + lo_offset);
	val |= (hi_offset < 0) ? 0 :
	       (u64)पढ़ोl_relaxed(addr + hi_offset) << 32;
	वापस val;
पूर्ण

अटल अंतरभूत व्योम coresight_ग_लिखो_reg_pair(व्योम __iomem *addr, u64 val,
						 s32 lo_offset, s32 hi_offset)
अणु
	ग_लिखोl_relaxed((u32)val, addr + lo_offset);
	अगर (hi_offset >= 0)
		ग_लिखोl_relaxed((u32)(val >> 32), addr + hi_offset);
पूर्ण

व्योम coresight_disable_path(काष्ठा list_head *path);
पूर्णांक coresight_enable_path(काष्ठा list_head *path, u32 mode, व्योम *sink_data);
काष्ठा coresight_device *coresight_get_sink(काष्ठा list_head *path);
काष्ठा coresight_device *
coresight_get_enabled_sink(काष्ठा coresight_device *source);
काष्ठा coresight_device *coresight_get_sink_by_id(u32 id);
काष्ठा coresight_device *
coresight_find_शेष_sink(काष्ठा coresight_device *csdev);
काष्ठा list_head *coresight_build_path(काष्ठा coresight_device *csdev,
				       काष्ठा coresight_device *sink);
व्योम coresight_release_path(काष्ठा list_head *path);
पूर्णांक coresight_add_sysfs_link(काष्ठा coresight_sysfs_link *info);
व्योम coresight_हटाओ_sysfs_link(काष्ठा coresight_sysfs_link *info);
पूर्णांक coresight_create_conns_sysfs_group(काष्ठा coresight_device *csdev);
व्योम coresight_हटाओ_conns_sysfs_group(काष्ठा coresight_device *csdev);
पूर्णांक coresight_make_links(काष्ठा coresight_device *orig,
			 काष्ठा coresight_connection *conn,
			 काष्ठा coresight_device *target);
व्योम coresight_हटाओ_links(काष्ठा coresight_device *orig,
			    काष्ठा coresight_connection *conn);

#अगर IS_ENABLED(CONFIG_CORESIGHT_SOURCE_ETM3X)
बाह्य पूर्णांक eपंचांग_पढ़ोl_cp14(u32 off, अचिन्हित पूर्णांक *val);
बाह्य पूर्णांक eपंचांग_ग_लिखोl_cp14(u32 off, u32 val);
#अन्यथा
अटल अंतरभूत पूर्णांक eपंचांग_पढ़ोl_cp14(u32 off, अचिन्हित पूर्णांक *val) अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक eपंचांग_ग_लिखोl_cp14(u32 off, u32 val) अणु वापस 0; पूर्ण
#पूर्ण_अगर

काष्ठा cti_assoc_op अणु
	व्योम (*add)(काष्ठा coresight_device *csdev);
	व्योम (*हटाओ)(काष्ठा coresight_device *csdev);
पूर्ण;

बाह्य व्योम coresight_set_cti_ops(स्थिर काष्ठा cti_assoc_op *cti_op);
बाह्य व्योम coresight_हटाओ_cti_ops(व्योम);

/*
 * Macros and अंतरभूत functions to handle CoreSight UCI data and driver
 * निजी data in AMBA ID table entries, and extract data values.
 */

/* coresight AMBA ID, no UCI, no driver data: id table entry */
#घोषणा CS_AMBA_ID(pid)			\
	अणु				\
		.id	= pid,		\
		.mask	= 0x000fffff,	\
	पूर्ण

/* coresight AMBA ID, UCI with driver data only: id table entry. */
#घोषणा CS_AMBA_ID_DATA(pid, dval)				\
	अणु							\
		.id	= pid,					\
		.mask	= 0x000fffff,				\
		.data	=  (व्योम *)&(काष्ठा amba_cs_uci_id)	\
			अणु				\
				.data = (व्योम *)dval,	\
			पूर्ण				\
	पूर्ण

/* coresight AMBA ID, full UCI काष्ठाure: id table entry. */
#घोषणा CS_AMBA_UCI_ID(pid, uci_ptr)		\
	अणु					\
		.id	= pid,			\
		.mask	= 0x000fffff,		\
		.data	= (व्योम *)uci_ptr	\
	पूर्ण

/* extract the data value from a UCI काष्ठाure given amba_id poपूर्णांकer. */
अटल अंतरभूत व्योम *coresight_get_uci_data(स्थिर काष्ठा amba_id *id)
अणु
	काष्ठा amba_cs_uci_id *uci_id = id->data;

	अगर (!uci_id)
		वापस शून्य;

	वापस uci_id->data;
पूर्ण

व्योम coresight_release_platक्रमm_data(काष्ठा coresight_device *csdev,
				     काष्ठा coresight_platक्रमm_data *pdata);
काष्ठा coresight_device *
coresight_find_csdev_by_fwnode(काष्ठा fwnode_handle *r_fwnode);
व्योम coresight_set_assoc_ectdev_mutex(काष्ठा coresight_device *csdev,
				      काष्ठा coresight_device *ect_csdev);

व्योम coresight_set_percpu_sink(पूर्णांक cpu, काष्ठा coresight_device *csdev);
काष्ठा coresight_device *coresight_get_percpu_sink(पूर्णांक cpu);

#पूर्ण_अगर
