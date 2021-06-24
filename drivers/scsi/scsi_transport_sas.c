<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2005-2006 Dell Inc.
 *
 * Serial Attached SCSI (SAS) transport class.
 *
 * The SAS transport class contains common code to deal with SAS HBAs,
 * an aproximated representation of SAS topologies in the driver model,
 * and various sysfs attributes to expose these topologies and management
 * पूर्णांकerfaces to userspace.
 *
 * In addition to the basic SCSI core objects this transport class
 * पूर्णांकroduces two additional पूर्णांकermediate objects:  The SAS PHY
 * as represented by काष्ठा sas_phy defines an "outgoing" PHY on
 * a SAS HBA or Expander, and the SAS remote PHY represented by
 * काष्ठा sas_rphy defines an "incoming" PHY on a SAS Expander or
 * end device.  Note that this is purely a software concept, the
 * underlying hardware क्रम a PHY and a remote PHY is the exactly
 * the same.
 *
 * There is no concept of a SAS port in this code, users can see
 * what PHYs क्रमm a wide port based on the port_identअगरier attribute,
 * which is the same क्रम all PHYs in a port.
 */

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/err.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/blkdev.h>
#समावेश <linux/bsg.h>

#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_cmnd.h>
#समावेश <scsi/scsi_request.h>
#समावेश <scsi/scsi_device.h>
#समावेश <scsi/scsi_host.h>
#समावेश <scsi/scsi_transport.h>
#समावेश <scsi/scsi_transport_sas.h>

#समावेश "scsi_sas_internal.h"
काष्ठा sas_host_attrs अणु
	काष्ठा list_head rphy_list;
	काष्ठा mutex lock;
	काष्ठा request_queue *q;
	u32 next_target_id;
	u32 next_expander_id;
	पूर्णांक next_port_id;
पूर्ण;
#घोषणा to_sas_host_attrs(host)	((काष्ठा sas_host_attrs *)(host)->shost_data)


/*
 * Hack to allow attributes of the same name in dअगरferent objects.
 */
#घोषणा SAS_DEVICE_ATTR(_prefix,_name,_mode,_show,_store) \
	काष्ठा device_attribute dev_attr_##_prefix##_##_name = \
	__ATTR(_name,_mode,_show,_store)


/*
 * Pretty prपूर्णांकing helpers
 */

#घोषणा sas_bitfield_name_match(title, table)			\
अटल sमाप_प्रकार							\
get_sas_##title##_names(u32 table_key, अक्षर *buf)		\
अणु								\
	अक्षर *prefix = "";					\
	sमाप_प्रकार len = 0;					\
	पूर्णांक i;							\
								\
	क्रम (i = 0; i < ARRAY_SIZE(table); i++) अणु		\
		अगर (table[i].value & table_key) अणु		\
			len += प्र_लिखो(buf + len, "%s%s",	\
				prefix, table[i].name);		\
			prefix = ", ";				\
		पूर्ण						\
	पूर्ण							\
	len += प्र_लिखो(buf + len, "\n");			\
	वापस len;						\
पूर्ण

#घोषणा sas_bitfield_name_set(title, table)			\
अटल sमाप_प्रकार							\
set_sas_##title##_names(u32 *table_key, स्थिर अक्षर *buf)	\
अणु								\
	sमाप_प्रकार len = 0;					\
	पूर्णांक i;							\
								\
	क्रम (i = 0; i < ARRAY_SIZE(table); i++) अणु		\
		len = म_माप(table[i].name);			\
		अगर (म_भेदन(buf, table[i].name, len) == 0 &&	\
		    (buf[len] == '\n' || buf[len] == '\0')) अणु	\
			*table_key = table[i].value;		\
			वापस 0;				\
		पूर्ण						\
	पूर्ण							\
	वापस -EINVAL;						\
पूर्ण

#घोषणा sas_bitfield_name_search(title, table)			\
अटल sमाप_प्रकार							\
get_sas_##title##_names(u32 table_key, अक्षर *buf)		\
अणु								\
	sमाप_प्रकार len = 0;					\
	पूर्णांक i;							\
								\
	क्रम (i = 0; i < ARRAY_SIZE(table); i++) अणु		\
		अगर (table[i].value == table_key) अणु		\
			len += प्र_लिखो(buf + len, "%s",		\
				table[i].name);			\
			अवरोध;					\
		पूर्ण						\
	पूर्ण							\
	len += प्र_लिखो(buf + len, "\n");			\
	वापस len;						\
पूर्ण

अटल काष्ठा अणु
	u32		value;
	अक्षर		*name;
पूर्ण sas_device_type_names[] = अणु
	अणु SAS_PHY_UNUSED,		"unused" पूर्ण,
	अणु SAS_END_DEVICE,		"end device" पूर्ण,
	अणु SAS_EDGE_EXPANDER_DEVICE,	"edge expander" पूर्ण,
	अणु SAS_FANOUT_EXPANDER_DEVICE,	"fanout expander" पूर्ण,
पूर्ण;
sas_bitfield_name_search(device_type, sas_device_type_names)


अटल काष्ठा अणु
	u32		value;
	अक्षर		*name;
पूर्ण sas_protocol_names[] = अणु
	अणु SAS_PROTOCOL_SATA,		"sata" पूर्ण,
	अणु SAS_PROTOCOL_SMP,		"smp" पूर्ण,
	अणु SAS_PROTOCOL_STP,		"stp" पूर्ण,
	अणु SAS_PROTOCOL_SSP,		"ssp" पूर्ण,
पूर्ण;
sas_bitfield_name_match(protocol, sas_protocol_names)

अटल काष्ठा अणु
	u32		value;
	अक्षर		*name;
पूर्ण sas_linkspeed_names[] = अणु
	अणु SAS_LINK_RATE_UNKNOWN,	"Unknown" पूर्ण,
	अणु SAS_PHY_DISABLED,		"Phy disabled" पूर्ण,
	अणु SAS_LINK_RATE_FAILED,		"Link Rate failed" पूर्ण,
	अणु SAS_SATA_SPINUP_HOLD,		"Spin-up hold" पूर्ण,
	अणु SAS_LINK_RATE_1_5_GBPS,	"1.5 Gbit" पूर्ण,
	अणु SAS_LINK_RATE_3_0_GBPS,	"3.0 Gbit" पूर्ण,
	अणु SAS_LINK_RATE_6_0_GBPS,	"6.0 Gbit" पूर्ण,
	अणु SAS_LINK_RATE_12_0_GBPS,	"12.0 Gbit" पूर्ण,
पूर्ण;
sas_bitfield_name_search(linkspeed, sas_linkspeed_names)
sas_bitfield_name_set(linkspeed, sas_linkspeed_names)

अटल काष्ठा sas_end_device *sas_sdev_to_rdev(काष्ठा scsi_device *sdev)
अणु
	काष्ठा sas_rphy *rphy = target_to_rphy(sdev->sdev_target);
	काष्ठा sas_end_device *rdev;

	BUG_ON(rphy->identअगरy.device_type != SAS_END_DEVICE);

	rdev = rphy_to_end_device(rphy);
	वापस rdev;
पूर्ण

अटल पूर्णांक sas_smp_dispatch(काष्ठा bsg_job *job)
अणु
	काष्ठा Scsi_Host *shost = dev_to_shost(job->dev);
	काष्ठा sas_rphy *rphy = शून्य;

	अगर (!scsi_is_host_device(job->dev))
		rphy = dev_to_rphy(job->dev);

	अगर (!job->reply_payload.payload_len) अणु
		dev_warn(job->dev, "space for a smp response is missing\n");
		bsg_job_करोne(job, -EINVAL, 0);
		वापस 0;
	पूर्ण

	to_sas_पूर्णांकernal(shost->transportt)->f->smp_handler(job, shost, rphy);
	वापस 0;
पूर्ण

अटल पूर्णांक sas_bsg_initialize(काष्ठा Scsi_Host *shost, काष्ठा sas_rphy *rphy)
अणु
	काष्ठा request_queue *q;

	अगर (!to_sas_पूर्णांकernal(shost->transportt)->f->smp_handler) अणु
		prपूर्णांकk("%s can't handle SMP requests\n", shost->hostt->name);
		वापस 0;
	पूर्ण

	अगर (rphy) अणु
		q = bsg_setup_queue(&rphy->dev, dev_name(&rphy->dev),
				sas_smp_dispatch, शून्य, 0);
		अगर (IS_ERR(q))
			वापस PTR_ERR(q);
		rphy->q = q;
	पूर्ण अन्यथा अणु
		अक्षर name[20];

		snम_लिखो(name, माप(name), "sas_host%d", shost->host_no);
		q = bsg_setup_queue(&shost->shost_gendev, name,
				sas_smp_dispatch, शून्य, 0);
		अगर (IS_ERR(q))
			वापस PTR_ERR(q);
		to_sas_host_attrs(shost)->q = q;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * SAS host attributes
 */

अटल पूर्णांक sas_host_setup(काष्ठा transport_container *tc, काष्ठा device *dev,
			  काष्ठा device *cdev)
अणु
	काष्ठा Scsi_Host *shost = dev_to_shost(dev);
	काष्ठा sas_host_attrs *sas_host = to_sas_host_attrs(shost);

	INIT_LIST_HEAD(&sas_host->rphy_list);
	mutex_init(&sas_host->lock);
	sas_host->next_target_id = 0;
	sas_host->next_expander_id = 0;
	sas_host->next_port_id = 0;

	अगर (sas_bsg_initialize(shost, शून्य))
		dev_prपूर्णांकk(KERN_ERR, dev, "fail to a bsg device %d\n",
			   shost->host_no);

	वापस 0;
पूर्ण

अटल पूर्णांक sas_host_हटाओ(काष्ठा transport_container *tc, काष्ठा device *dev,
			   काष्ठा device *cdev)
अणु
	काष्ठा Scsi_Host *shost = dev_to_shost(dev);
	काष्ठा request_queue *q = to_sas_host_attrs(shost)->q;

	bsg_हटाओ_queue(q);
	वापस 0;
पूर्ण

अटल DECLARE_TRANSPORT_CLASS(sas_host_class,
		"sas_host", sas_host_setup, sas_host_हटाओ, शून्य);

अटल पूर्णांक sas_host_match(काष्ठा attribute_container *cont,
			    काष्ठा device *dev)
अणु
	काष्ठा Scsi_Host *shost;
	काष्ठा sas_पूर्णांकernal *i;

	अगर (!scsi_is_host_device(dev))
		वापस 0;
	shost = dev_to_shost(dev);

	अगर (!shost->transportt)
		वापस 0;
	अगर (shost->transportt->host_attrs.ac.class !=
			&sas_host_class.class)
		वापस 0;

	i = to_sas_पूर्णांकernal(shost->transportt);
	वापस &i->t.host_attrs.ac == cont;
पूर्ण

अटल पूर्णांक करो_sas_phy_delete(काष्ठा device *dev, व्योम *data)
अणु
	पूर्णांक pass = (पूर्णांक)(अचिन्हित दीर्घ)data;

	अगर (pass == 0 && scsi_is_sas_port(dev))
		sas_port_delete(dev_to_sas_port(dev));
	अन्यथा अगर (pass == 1 && scsi_is_sas_phy(dev))
		sas_phy_delete(dev_to_phy(dev));
	वापस 0;
पूर्ण

/**
 * sas_हटाओ_children  -  tear करोwn a devices SAS data काष्ठाures
 * @dev:	device beदीर्घing to the sas object
 *
 * Removes all SAS PHYs and remote PHYs क्रम a given object
 */
व्योम sas_हटाओ_children(काष्ठा device *dev)
अणु
	device_क्रम_each_child(dev, (व्योम *)0, करो_sas_phy_delete);
	device_क्रम_each_child(dev, (व्योम *)1, करो_sas_phy_delete);
पूर्ण
EXPORT_SYMBOL(sas_हटाओ_children);

/**
 * sas_हटाओ_host  -  tear करोwn a Scsi_Host's SAS data काष्ठाures
 * @shost:	Scsi Host that is torn करोwn
 *
 * Removes all SAS PHYs and remote PHYs क्रम a given Scsi_Host and हटाओ the
 * Scsi_Host as well.
 *
 * Note: Do not call scsi_हटाओ_host() on the Scsi_Host any more, as it is
 * alपढ़ोy हटाओd.
 */
व्योम sas_हटाओ_host(काष्ठा Scsi_Host *shost)
अणु
	sas_हटाओ_children(&shost->shost_gendev);
	scsi_हटाओ_host(shost);
पूर्ण
EXPORT_SYMBOL(sas_हटाओ_host);

/**
 * sas_get_address - वापस the SAS address of the device
 * @sdev: scsi device
 *
 * Returns the SAS address of the scsi device
 */
u64 sas_get_address(काष्ठा scsi_device *sdev)
अणु
	काष्ठा sas_end_device *rdev = sas_sdev_to_rdev(sdev);

	वापस rdev->rphy.identअगरy.sas_address;
पूर्ण
EXPORT_SYMBOL(sas_get_address);

/**
 * sas_tlr_supported - checking TLR bit in vpd 0x90
 * @sdev: scsi device काष्ठा
 *
 * Check Transport Layer Retries are supported or not.
 * If vpd page 0x90 is present, TRL is supported.
 *
 */
अचिन्हित पूर्णांक
sas_tlr_supported(काष्ठा scsi_device *sdev)
अणु
	स्थिर पूर्णांक vpd_len = 32;
	काष्ठा sas_end_device *rdev = sas_sdev_to_rdev(sdev);
	अक्षर *buffer = kzalloc(vpd_len, GFP_KERNEL);
	पूर्णांक ret = 0;

	अगर (!buffer)
		जाओ out;

	अगर (scsi_get_vpd_page(sdev, 0x90, buffer, vpd_len))
		जाओ out;

	/*
	 * Magic numbers: the VPD Protocol page (0x90)
	 * has a 4 byte header and then one entry per device port
	 * the TLR bit is at offset 8 on each port entry
	 * अगर we take the first port, that's at total offset 12
	 */
	ret = buffer[12] & 0x01;

 out:
	kमुक्त(buffer);
	rdev->tlr_supported = ret;
	वापस ret;

पूर्ण
EXPORT_SYMBOL_GPL(sas_tlr_supported);

/**
 * sas_disable_tlr - setting TLR flags
 * @sdev: scsi device काष्ठा
 *
 * Seting tlr_enabled flag to 0.
 *
 */
व्योम
sas_disable_tlr(काष्ठा scsi_device *sdev)
अणु
	काष्ठा sas_end_device *rdev = sas_sdev_to_rdev(sdev);

	rdev->tlr_enabled = 0;
पूर्ण
EXPORT_SYMBOL_GPL(sas_disable_tlr);

/**
 * sas_enable_tlr - setting TLR flags
 * @sdev: scsi device काष्ठा
 *
 * Seting tlr_enabled flag 1.
 *
 */
व्योम sas_enable_tlr(काष्ठा scsi_device *sdev)
अणु
	अचिन्हित पूर्णांक tlr_supported = 0;
	tlr_supported  = sas_tlr_supported(sdev);

	अगर (tlr_supported) अणु
		काष्ठा sas_end_device *rdev = sas_sdev_to_rdev(sdev);

		rdev->tlr_enabled = 1;
	पूर्ण

	वापस;
पूर्ण
EXPORT_SYMBOL_GPL(sas_enable_tlr);

अचिन्हित पूर्णांक sas_is_tlr_enabled(काष्ठा scsi_device *sdev)
अणु
	काष्ठा sas_end_device *rdev = sas_sdev_to_rdev(sdev);
	वापस rdev->tlr_enabled;
पूर्ण
EXPORT_SYMBOL_GPL(sas_is_tlr_enabled);

/*
 * SAS Phy attributes
 */

#घोषणा sas_phy_show_simple(field, name, क्रमmat_string, cast)		\
अटल sमाप_प्रकार								\
show_sas_phy_##name(काष्ठा device *dev, 				\
		    काष्ठा device_attribute *attr, अक्षर *buf)		\
अणु									\
	काष्ठा sas_phy *phy = transport_class_to_phy(dev);		\
									\
	वापस snम_लिखो(buf, 20, क्रमmat_string, cast phy->field);	\
पूर्ण

#घोषणा sas_phy_simple_attr(field, name, क्रमmat_string, type)		\
	sas_phy_show_simple(field, name, क्रमmat_string, (type))	\
अटल DEVICE_ATTR(name, S_IRUGO, show_sas_phy_##name, शून्य)

#घोषणा sas_phy_show_protocol(field, name)				\
अटल sमाप_प्रकार								\
show_sas_phy_##name(काष्ठा device *dev, 				\
		    काष्ठा device_attribute *attr, अक्षर *buf)		\
अणु									\
	काष्ठा sas_phy *phy = transport_class_to_phy(dev);		\
									\
	अगर (!phy->field)						\
		वापस snम_लिखो(buf, 20, "none\n");			\
	वापस get_sas_protocol_names(phy->field, buf);		\
पूर्ण

#घोषणा sas_phy_protocol_attr(field, name)				\
	sas_phy_show_protocol(field, name)				\
अटल DEVICE_ATTR(name, S_IRUGO, show_sas_phy_##name, शून्य)

#घोषणा sas_phy_show_linkspeed(field)					\
अटल sमाप_प्रकार								\
show_sas_phy_##field(काष्ठा device *dev, 				\
		     काष्ठा device_attribute *attr, अक्षर *buf)		\
अणु									\
	काष्ठा sas_phy *phy = transport_class_to_phy(dev);		\
									\
	वापस get_sas_linkspeed_names(phy->field, buf);		\
पूर्ण

/* Fudge to tell अगर we're minimum or maximum */
#घोषणा sas_phy_store_linkspeed(field)					\
अटल sमाप_प्रकार								\
store_sas_phy_##field(काष्ठा device *dev, 				\
		      काष्ठा device_attribute *attr, 			\
		      स्थिर अक्षर *buf,	माप_प्रकार count)			\
अणु									\
	काष्ठा sas_phy *phy = transport_class_to_phy(dev);		\
	काष्ठा Scsi_Host *shost = dev_to_shost(phy->dev.parent);	\
	काष्ठा sas_पूर्णांकernal *i = to_sas_पूर्णांकernal(shost->transportt);	\
	u32 value;							\
	काष्ठा sas_phy_linkrates rates = अणु0पूर्ण;				\
	पूर्णांक error;							\
									\
	error = set_sas_linkspeed_names(&value, buf);			\
	अगर (error)							\
		वापस error;						\
	rates.field = value;						\
	error = i->f->set_phy_speed(phy, &rates);			\
									\
	वापस error ? error : count;					\
पूर्ण

#घोषणा sas_phy_linkspeed_rw_attr(field)				\
	sas_phy_show_linkspeed(field)					\
	sas_phy_store_linkspeed(field)					\
अटल DEVICE_ATTR(field, S_IRUGO, show_sas_phy_##field,		\
	store_sas_phy_##field)

#घोषणा sas_phy_linkspeed_attr(field)					\
	sas_phy_show_linkspeed(field)					\
अटल DEVICE_ATTR(field, S_IRUGO, show_sas_phy_##field, शून्य)


#घोषणा sas_phy_show_linkerror(field)					\
अटल sमाप_प्रकार								\
show_sas_phy_##field(काष्ठा device *dev, 				\
		     काष्ठा device_attribute *attr, अक्षर *buf)		\
अणु									\
	काष्ठा sas_phy *phy = transport_class_to_phy(dev);		\
	काष्ठा Scsi_Host *shost = dev_to_shost(phy->dev.parent);	\
	काष्ठा sas_पूर्णांकernal *i = to_sas_पूर्णांकernal(shost->transportt);	\
	पूर्णांक error;							\
									\
	error = i->f->get_linkerrors ? i->f->get_linkerrors(phy) : 0;	\
	अगर (error)							\
		वापस error;						\
	वापस snम_लिखो(buf, 20, "%u\n", phy->field);			\
पूर्ण

#घोषणा sas_phy_linkerror_attr(field)					\
	sas_phy_show_linkerror(field)					\
अटल DEVICE_ATTR(field, S_IRUGO, show_sas_phy_##field, शून्य)


अटल sमाप_प्रकार
show_sas_device_type(काष्ठा device *dev,
		     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा sas_phy *phy = transport_class_to_phy(dev);

	अगर (!phy->identअगरy.device_type)
		वापस snम_लिखो(buf, 20, "none\n");
	वापस get_sas_device_type_names(phy->identअगरy.device_type, buf);
पूर्ण
अटल DEVICE_ATTR(device_type, S_IRUGO, show_sas_device_type, शून्य);

अटल sमाप_प्रकार करो_sas_phy_enable(काष्ठा device *dev,
		माप_प्रकार count, पूर्णांक enable)
अणु
	काष्ठा sas_phy *phy = transport_class_to_phy(dev);
	काष्ठा Scsi_Host *shost = dev_to_shost(phy->dev.parent);
	काष्ठा sas_पूर्णांकernal *i = to_sas_पूर्णांकernal(shost->transportt);
	पूर्णांक error;

	error = i->f->phy_enable(phy, enable);
	अगर (error)
		वापस error;
	phy->enabled = enable;
	वापस count;
पूर्ण;

अटल sमाप_प्रकार
store_sas_phy_enable(काष्ठा device *dev, काष्ठा device_attribute *attr,
		     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अगर (count < 1)
		वापस -EINVAL;

	चयन (buf[0]) अणु
	हाल '0':
		करो_sas_phy_enable(dev, count, 0);
		अवरोध;
	हाल '1':
		करो_sas_phy_enable(dev, count, 1);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस count;
पूर्ण

अटल sमाप_प्रकार
show_sas_phy_enable(काष्ठा device *dev, काष्ठा device_attribute *attr,
		    अक्षर *buf)
अणु
	काष्ठा sas_phy *phy = transport_class_to_phy(dev);

	वापस snम_लिखो(buf, 20, "%d\n", phy->enabled);
पूर्ण

अटल DEVICE_ATTR(enable, S_IRUGO | S_IWUSR, show_sas_phy_enable,
			 store_sas_phy_enable);

अटल sमाप_प्रकार
करो_sas_phy_reset(काष्ठा device *dev, माप_प्रकार count, पूर्णांक hard_reset)
अणु
	काष्ठा sas_phy *phy = transport_class_to_phy(dev);
	काष्ठा Scsi_Host *shost = dev_to_shost(phy->dev.parent);
	काष्ठा sas_पूर्णांकernal *i = to_sas_पूर्णांकernal(shost->transportt);
	पूर्णांक error;

	error = i->f->phy_reset(phy, hard_reset);
	अगर (error)
		वापस error;
	phy->enabled = 1;
	वापस count;
पूर्ण;

अटल sमाप_प्रकार
store_sas_link_reset(काष्ठा device *dev, काष्ठा device_attribute *attr,
		     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	वापस करो_sas_phy_reset(dev, count, 0);
पूर्ण
अटल DEVICE_ATTR(link_reset, S_IWUSR, शून्य, store_sas_link_reset);

अटल sमाप_प्रकार
store_sas_hard_reset(काष्ठा device *dev, काष्ठा device_attribute *attr,
		     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	वापस करो_sas_phy_reset(dev, count, 1);
पूर्ण
अटल DEVICE_ATTR(hard_reset, S_IWUSR, शून्य, store_sas_hard_reset);

sas_phy_protocol_attr(identअगरy.initiator_port_protocols,
		initiator_port_protocols);
sas_phy_protocol_attr(identअगरy.target_port_protocols,
		target_port_protocols);
sas_phy_simple_attr(identअगरy.sas_address, sas_address, "0x%016llx\n",
		अचिन्हित दीर्घ दीर्घ);
sas_phy_simple_attr(identअगरy.phy_identअगरier, phy_identअगरier, "%d\n", u8);
sas_phy_linkspeed_attr(negotiated_linkrate);
sas_phy_linkspeed_attr(minimum_linkrate_hw);
sas_phy_linkspeed_rw_attr(minimum_linkrate);
sas_phy_linkspeed_attr(maximum_linkrate_hw);
sas_phy_linkspeed_rw_attr(maximum_linkrate);
sas_phy_linkerror_attr(invalid_dword_count);
sas_phy_linkerror_attr(running_disparity_error_count);
sas_phy_linkerror_attr(loss_of_dword_sync_count);
sas_phy_linkerror_attr(phy_reset_problem_count);

अटल पूर्णांक sas_phy_setup(काष्ठा transport_container *tc, काष्ठा device *dev,
			 काष्ठा device *cdev)
अणु
	काष्ठा sas_phy *phy = dev_to_phy(dev);
	काष्ठा Scsi_Host *shost = dev_to_shost(phy->dev.parent);
	काष्ठा sas_पूर्णांकernal *i = to_sas_पूर्णांकernal(shost->transportt);

	अगर (i->f->phy_setup)
		i->f->phy_setup(phy);

	वापस 0;
पूर्ण

अटल DECLARE_TRANSPORT_CLASS(sas_phy_class,
		"sas_phy", sas_phy_setup, शून्य, शून्य);

अटल पूर्णांक sas_phy_match(काष्ठा attribute_container *cont, काष्ठा device *dev)
अणु
	काष्ठा Scsi_Host *shost;
	काष्ठा sas_पूर्णांकernal *i;

	अगर (!scsi_is_sas_phy(dev))
		वापस 0;
	shost = dev_to_shost(dev->parent);

	अगर (!shost->transportt)
		वापस 0;
	अगर (shost->transportt->host_attrs.ac.class !=
			&sas_host_class.class)
		वापस 0;

	i = to_sas_पूर्णांकernal(shost->transportt);
	वापस &i->phy_attr_cont.ac == cont;
पूर्ण

अटल व्योम sas_phy_release(काष्ठा device *dev)
अणु
	काष्ठा sas_phy *phy = dev_to_phy(dev);
	काष्ठा Scsi_Host *shost = dev_to_shost(phy->dev.parent);
	काष्ठा sas_पूर्णांकernal *i = to_sas_पूर्णांकernal(shost->transportt);

	अगर (i->f->phy_release)
		i->f->phy_release(phy);
	put_device(dev->parent);
	kमुक्त(phy);
पूर्ण

/**
 * sas_phy_alloc  -  allocates and initialize a SAS PHY काष्ठाure
 * @parent:	Parent device
 * @number:	Phy index
 *
 * Allocates an SAS PHY काष्ठाure.  It will be added in the device tree
 * below the device specअगरied by @parent, which has to be either a Scsi_Host
 * or sas_rphy.
 *
 * Returns:
 *	SAS PHY allocated or %शून्य अगर the allocation failed.
 */
काष्ठा sas_phy *sas_phy_alloc(काष्ठा device *parent, पूर्णांक number)
अणु
	काष्ठा Scsi_Host *shost = dev_to_shost(parent);
	काष्ठा sas_phy *phy;

	phy = kzalloc(माप(*phy), GFP_KERNEL);
	अगर (!phy)
		वापस शून्य;

	phy->number = number;
	phy->enabled = 1;

	device_initialize(&phy->dev);
	phy->dev.parent = get_device(parent);
	phy->dev.release = sas_phy_release;
	INIT_LIST_HEAD(&phy->port_siblings);
	अगर (scsi_is_sas_expander_device(parent)) अणु
		काष्ठा sas_rphy *rphy = dev_to_rphy(parent);
		dev_set_name(&phy->dev, "phy-%d:%d:%d", shost->host_no,
			rphy->scsi_target_id, number);
	पूर्ण अन्यथा
		dev_set_name(&phy->dev, "phy-%d:%d", shost->host_no, number);

	transport_setup_device(&phy->dev);

	वापस phy;
पूर्ण
EXPORT_SYMBOL(sas_phy_alloc);

/**
 * sas_phy_add  -  add a SAS PHY to the device hierarchy
 * @phy:	The PHY to be added
 *
 * Publishes a SAS PHY to the rest of the प्रणाली.
 */
पूर्णांक sas_phy_add(काष्ठा sas_phy *phy)
अणु
	पूर्णांक error;

	error = device_add(&phy->dev);
	अगर (!error) अणु
		transport_add_device(&phy->dev);
		transport_configure_device(&phy->dev);
	पूर्ण

	वापस error;
पूर्ण
EXPORT_SYMBOL(sas_phy_add);

/**
 * sas_phy_मुक्त  -  मुक्त a SAS PHY
 * @phy:	SAS PHY to मुक्त
 *
 * Frees the specअगरied SAS PHY.
 *
 * Note:
 *   This function must only be called on a PHY that has not
 *   successfully been added using sas_phy_add().
 */
व्योम sas_phy_मुक्त(काष्ठा sas_phy *phy)
अणु
	transport_destroy_device(&phy->dev);
	put_device(&phy->dev);
पूर्ण
EXPORT_SYMBOL(sas_phy_मुक्त);

/**
 * sas_phy_delete  -  हटाओ SAS PHY
 * @phy:	SAS PHY to हटाओ
 *
 * Removes the specअगरied SAS PHY.  If the SAS PHY has an
 * associated remote PHY it is हटाओd beक्रमe.
 */
व्योम
sas_phy_delete(काष्ठा sas_phy *phy)
अणु
	काष्ठा device *dev = &phy->dev;

	/* this happens अगर the phy is still part of a port when deleted */
	BUG_ON(!list_empty(&phy->port_siblings));

	transport_हटाओ_device(dev);
	device_del(dev);
	transport_destroy_device(dev);
	put_device(dev);
पूर्ण
EXPORT_SYMBOL(sas_phy_delete);

/**
 * scsi_is_sas_phy  -  check अगर a काष्ठा device represents a SAS PHY
 * @dev:	device to check
 *
 * Returns:
 *	%1 अगर the device represents a SAS PHY, %0 अन्यथा
 */
पूर्णांक scsi_is_sas_phy(स्थिर काष्ठा device *dev)
अणु
	वापस dev->release == sas_phy_release;
पूर्ण
EXPORT_SYMBOL(scsi_is_sas_phy);

/*
 * SAS Port attributes
 */
#घोषणा sas_port_show_simple(field, name, क्रमmat_string, cast)		\
अटल sमाप_प्रकार								\
show_sas_port_##name(काष्ठा device *dev, 				\
		     काष्ठा device_attribute *attr, अक्षर *buf)		\
अणु									\
	काष्ठा sas_port *port = transport_class_to_sas_port(dev);	\
									\
	वापस snम_लिखो(buf, 20, क्रमmat_string, cast port->field);	\
पूर्ण

#घोषणा sas_port_simple_attr(field, name, क्रमmat_string, type)		\
	sas_port_show_simple(field, name, क्रमmat_string, (type))	\
अटल DEVICE_ATTR(name, S_IRUGO, show_sas_port_##name, शून्य)

sas_port_simple_attr(num_phys, num_phys, "%d\n", पूर्णांक);

अटल DECLARE_TRANSPORT_CLASS(sas_port_class,
			       "sas_port", शून्य, शून्य, शून्य);

अटल पूर्णांक sas_port_match(काष्ठा attribute_container *cont, काष्ठा device *dev)
अणु
	काष्ठा Scsi_Host *shost;
	काष्ठा sas_पूर्णांकernal *i;

	अगर (!scsi_is_sas_port(dev))
		वापस 0;
	shost = dev_to_shost(dev->parent);

	अगर (!shost->transportt)
		वापस 0;
	अगर (shost->transportt->host_attrs.ac.class !=
			&sas_host_class.class)
		वापस 0;

	i = to_sas_पूर्णांकernal(shost->transportt);
	वापस &i->port_attr_cont.ac == cont;
पूर्ण


अटल व्योम sas_port_release(काष्ठा device *dev)
अणु
	काष्ठा sas_port *port = dev_to_sas_port(dev);

	BUG_ON(!list_empty(&port->phy_list));

	put_device(dev->parent);
	kमुक्त(port);
पूर्ण

अटल व्योम sas_port_create_link(काष्ठा sas_port *port,
				 काष्ठा sas_phy *phy)
अणु
	पूर्णांक res;

	res = sysfs_create_link(&port->dev.kobj, &phy->dev.kobj,
				dev_name(&phy->dev));
	अगर (res)
		जाओ err;
	res = sysfs_create_link(&phy->dev.kobj, &port->dev.kobj, "port");
	अगर (res)
		जाओ err;
	वापस;
err:
	prपूर्णांकk(KERN_ERR "%s: Cannot create port links, err=%d\n",
	       __func__, res);
पूर्ण

अटल व्योम sas_port_delete_link(काष्ठा sas_port *port,
				 काष्ठा sas_phy *phy)
अणु
	sysfs_हटाओ_link(&port->dev.kobj, dev_name(&phy->dev));
	sysfs_हटाओ_link(&phy->dev.kobj, "port");
पूर्ण

/** sas_port_alloc - allocate and initialize a SAS port काष्ठाure
 *
 * @parent:	parent device
 * @port_id:	port number
 *
 * Allocates a SAS port काष्ठाure.  It will be added to the device tree
 * below the device specअगरied by @parent which must be either a Scsi_Host
 * or a sas_expander_device.
 *
 * Returns %शून्य on error
 */
काष्ठा sas_port *sas_port_alloc(काष्ठा device *parent, पूर्णांक port_id)
अणु
	काष्ठा Scsi_Host *shost = dev_to_shost(parent);
	काष्ठा sas_port *port;

	port = kzalloc(माप(*port), GFP_KERNEL);
	अगर (!port)
		वापस शून्य;

	port->port_identअगरier = port_id;

	device_initialize(&port->dev);

	port->dev.parent = get_device(parent);
	port->dev.release = sas_port_release;

	mutex_init(&port->phy_list_mutex);
	INIT_LIST_HEAD(&port->phy_list);

	अगर (scsi_is_sas_expander_device(parent)) अणु
		काष्ठा sas_rphy *rphy = dev_to_rphy(parent);
		dev_set_name(&port->dev, "port-%d:%d:%d", shost->host_no,
			     rphy->scsi_target_id, port->port_identअगरier);
	पूर्ण अन्यथा
		dev_set_name(&port->dev, "port-%d:%d", shost->host_no,
			     port->port_identअगरier);

	transport_setup_device(&port->dev);

	वापस port;
पूर्ण
EXPORT_SYMBOL(sas_port_alloc);

/** sas_port_alloc_num - allocate and initialize a SAS port काष्ठाure
 *
 * @parent:	parent device
 *
 * Allocates a SAS port काष्ठाure and a number to go with it.  This
 * पूर्णांकerface is really क्रम adapters where the port number has no
 * meansing, so the sas class should manage them.  It will be added to
 * the device tree below the device specअगरied by @parent which must be
 * either a Scsi_Host or a sas_expander_device.
 *
 * Returns %शून्य on error
 */
काष्ठा sas_port *sas_port_alloc_num(काष्ठा device *parent)
अणु
	पूर्णांक index;
	काष्ठा Scsi_Host *shost = dev_to_shost(parent);
	काष्ठा sas_host_attrs *sas_host = to_sas_host_attrs(shost);

	/* FIXME: use idr क्रम this eventually */
	mutex_lock(&sas_host->lock);
	अगर (scsi_is_sas_expander_device(parent)) अणु
		काष्ठा sas_rphy *rphy = dev_to_rphy(parent);
		काष्ठा sas_expander_device *exp = rphy_to_expander_device(rphy);

		index = exp->next_port_id++;
	पूर्ण अन्यथा
		index = sas_host->next_port_id++;
	mutex_unlock(&sas_host->lock);
	वापस sas_port_alloc(parent, index);
पूर्ण
EXPORT_SYMBOL(sas_port_alloc_num);

/**
 * sas_port_add - add a SAS port to the device hierarchy
 * @port:	port to be added
 *
 * publishes a port to the rest of the प्रणाली
 */
पूर्णांक sas_port_add(काष्ठा sas_port *port)
अणु
	पूर्णांक error;

	/* No phys should be added until this is made visible */
	BUG_ON(!list_empty(&port->phy_list));

	error = device_add(&port->dev);

	अगर (error)
		वापस error;

	transport_add_device(&port->dev);
	transport_configure_device(&port->dev);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(sas_port_add);

/**
 * sas_port_मुक्त  -  मुक्त a SAS PORT
 * @port:	SAS PORT to मुक्त
 *
 * Frees the specअगरied SAS PORT.
 *
 * Note:
 *   This function must only be called on a PORT that has not
 *   successfully been added using sas_port_add().
 */
व्योम sas_port_मुक्त(काष्ठा sas_port *port)
अणु
	transport_destroy_device(&port->dev);
	put_device(&port->dev);
पूर्ण
EXPORT_SYMBOL(sas_port_मुक्त);

/**
 * sas_port_delete  -  हटाओ SAS PORT
 * @port:	SAS PORT to हटाओ
 *
 * Removes the specअगरied SAS PORT.  If the SAS PORT has an
 * associated phys, unlink them from the port as well.
 */
व्योम sas_port_delete(काष्ठा sas_port *port)
अणु
	काष्ठा device *dev = &port->dev;
	काष्ठा sas_phy *phy, *पंचांगp_phy;

	अगर (port->rphy) अणु
		sas_rphy_delete(port->rphy);
		port->rphy = शून्य;
	पूर्ण

	mutex_lock(&port->phy_list_mutex);
	list_क्रम_each_entry_safe(phy, पंचांगp_phy, &port->phy_list,
				 port_siblings) अणु
		sas_port_delete_link(port, phy);
		list_del_init(&phy->port_siblings);
	पूर्ण
	mutex_unlock(&port->phy_list_mutex);

	अगर (port->is_backlink) अणु
		काष्ठा device *parent = port->dev.parent;

		sysfs_हटाओ_link(&port->dev.kobj, dev_name(parent));
		port->is_backlink = 0;
	पूर्ण

	transport_हटाओ_device(dev);
	device_del(dev);
	transport_destroy_device(dev);
	put_device(dev);
पूर्ण
EXPORT_SYMBOL(sas_port_delete);

/**
 * scsi_is_sas_port -  check अगर a काष्ठा device represents a SAS port
 * @dev:	device to check
 *
 * Returns:
 *	%1 अगर the device represents a SAS Port, %0 अन्यथा
 */
पूर्णांक scsi_is_sas_port(स्थिर काष्ठा device *dev)
अणु
	वापस dev->release == sas_port_release;
पूर्ण
EXPORT_SYMBOL(scsi_is_sas_port);

/**
 * sas_port_get_phy - try to take a reference on a port member
 * @port: port to check
 */
काष्ठा sas_phy *sas_port_get_phy(काष्ठा sas_port *port)
अणु
	काष्ठा sas_phy *phy;

	mutex_lock(&port->phy_list_mutex);
	अगर (list_empty(&port->phy_list))
		phy = शून्य;
	अन्यथा अणु
		काष्ठा list_head *ent = port->phy_list.next;

		phy = list_entry(ent, typeof(*phy), port_siblings);
		get_device(&phy->dev);
	पूर्ण
	mutex_unlock(&port->phy_list_mutex);

	वापस phy;
पूर्ण
EXPORT_SYMBOL(sas_port_get_phy);

/**
 * sas_port_add_phy - add another phy to a port to क्रमm a wide port
 * @port:	port to add the phy to
 * @phy:	phy to add
 *
 * When a port is initially created, it is empty (has no phys).  All
 * ports must have at least one phy to operated, and all wide ports
 * must have at least two.  The current code makes no dअगरference
 * between ports and wide ports, but the only object that can be
 * connected to a remote device is a port, so ports must be क्रमmed on
 * all devices with phys अगर they're connected to anything.
 */
व्योम sas_port_add_phy(काष्ठा sas_port *port, काष्ठा sas_phy *phy)
अणु
	mutex_lock(&port->phy_list_mutex);
	अगर (unlikely(!list_empty(&phy->port_siblings))) अणु
		/* make sure we're alपढ़ोy on this port */
		काष्ठा sas_phy *पंचांगp;

		list_क्रम_each_entry(पंचांगp, &port->phy_list, port_siblings)
			अगर (पंचांगp == phy)
				अवरोध;
		/* If this trips, you added a phy that was alपढ़ोy
		 * part of a dअगरferent port */
		अगर (unlikely(पंचांगp != phy)) अणु
			dev_prपूर्णांकk(KERN_ERR, &port->dev, "trying to add phy %s fails: it's already part of another port\n",
				   dev_name(&phy->dev));
			BUG();
		पूर्ण
	पूर्ण अन्यथा अणु
		sas_port_create_link(port, phy);
		list_add_tail(&phy->port_siblings, &port->phy_list);
		port->num_phys++;
	पूर्ण
	mutex_unlock(&port->phy_list_mutex);
पूर्ण
EXPORT_SYMBOL(sas_port_add_phy);

/**
 * sas_port_delete_phy - हटाओ a phy from a port or wide port
 * @port:	port to हटाओ the phy from
 * @phy:	phy to हटाओ
 *
 * This operation is used क्रम tearing करोwn ports again.  It must be
 * करोne to every port or wide port beक्रमe calling sas_port_delete.
 */
व्योम sas_port_delete_phy(काष्ठा sas_port *port, काष्ठा sas_phy *phy)
अणु
	mutex_lock(&port->phy_list_mutex);
	sas_port_delete_link(port, phy);
	list_del_init(&phy->port_siblings);
	port->num_phys--;
	mutex_unlock(&port->phy_list_mutex);
पूर्ण
EXPORT_SYMBOL(sas_port_delete_phy);

व्योम sas_port_mark_backlink(काष्ठा sas_port *port)
अणु
	पूर्णांक res;
	काष्ठा device *parent = port->dev.parent->parent->parent;

	अगर (port->is_backlink)
		वापस;
	port->is_backlink = 1;
	res = sysfs_create_link(&port->dev.kobj, &parent->kobj,
				dev_name(parent));
	अगर (res)
		जाओ err;
	वापस;
err:
	prपूर्णांकk(KERN_ERR "%s: Cannot create port backlink, err=%d\n",
	       __func__, res);

पूर्ण
EXPORT_SYMBOL(sas_port_mark_backlink);

/*
 * SAS remote PHY attributes.
 */

#घोषणा sas_rphy_show_simple(field, name, क्रमmat_string, cast)		\
अटल sमाप_प्रकार								\
show_sas_rphy_##name(काष्ठा device *dev, 				\
		     काष्ठा device_attribute *attr, अक्षर *buf)		\
अणु									\
	काष्ठा sas_rphy *rphy = transport_class_to_rphy(dev);		\
									\
	वापस snम_लिखो(buf, 20, क्रमmat_string, cast rphy->field);	\
पूर्ण

#घोषणा sas_rphy_simple_attr(field, name, क्रमmat_string, type)		\
	sas_rphy_show_simple(field, name, क्रमmat_string, (type))	\
अटल SAS_DEVICE_ATTR(rphy, name, S_IRUGO, 			\
		show_sas_rphy_##name, शून्य)

#घोषणा sas_rphy_show_protocol(field, name)				\
अटल sमाप_प्रकार								\
show_sas_rphy_##name(काष्ठा device *dev, 				\
		     काष्ठा device_attribute *attr, अक्षर *buf)		\
अणु									\
	काष्ठा sas_rphy *rphy = transport_class_to_rphy(dev);		\
									\
	अगर (!rphy->field)					\
		वापस snम_लिखो(buf, 20, "none\n");			\
	वापस get_sas_protocol_names(rphy->field, buf);	\
पूर्ण

#घोषणा sas_rphy_protocol_attr(field, name)				\
	sas_rphy_show_protocol(field, name)				\
अटल SAS_DEVICE_ATTR(rphy, name, S_IRUGO,			\
		show_sas_rphy_##name, शून्य)

अटल sमाप_प्रकार
show_sas_rphy_device_type(काष्ठा device *dev,
			  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा sas_rphy *rphy = transport_class_to_rphy(dev);

	अगर (!rphy->identअगरy.device_type)
		वापस snम_लिखो(buf, 20, "none\n");
	वापस get_sas_device_type_names(
			rphy->identअगरy.device_type, buf);
पूर्ण

अटल SAS_DEVICE_ATTR(rphy, device_type, S_IRUGO,
		show_sas_rphy_device_type, शून्य);

अटल sमाप_प्रकार
show_sas_rphy_enclosure_identअगरier(काष्ठा device *dev,
				   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा sas_rphy *rphy = transport_class_to_rphy(dev);
	काष्ठा sas_phy *phy = dev_to_phy(rphy->dev.parent);
	काष्ठा Scsi_Host *shost = dev_to_shost(phy->dev.parent);
	काष्ठा sas_पूर्णांकernal *i = to_sas_पूर्णांकernal(shost->transportt);
	u64 identअगरier;
	पूर्णांक error;

	error = i->f->get_enclosure_identअगरier(rphy, &identअगरier);
	अगर (error)
		वापस error;
	वापस प्र_लिखो(buf, "0x%llx\n", (अचिन्हित दीर्घ दीर्घ)identअगरier);
पूर्ण

अटल SAS_DEVICE_ATTR(rphy, enclosure_identअगरier, S_IRUGO,
		show_sas_rphy_enclosure_identअगरier, शून्य);

अटल sमाप_प्रकार
show_sas_rphy_bay_identअगरier(काष्ठा device *dev,
			     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा sas_rphy *rphy = transport_class_to_rphy(dev);
	काष्ठा sas_phy *phy = dev_to_phy(rphy->dev.parent);
	काष्ठा Scsi_Host *shost = dev_to_shost(phy->dev.parent);
	काष्ठा sas_पूर्णांकernal *i = to_sas_पूर्णांकernal(shost->transportt);
	पूर्णांक val;

	val = i->f->get_bay_identअगरier(rphy);
	अगर (val < 0)
		वापस val;
	वापस प्र_लिखो(buf, "%d\n", val);
पूर्ण

अटल SAS_DEVICE_ATTR(rphy, bay_identअगरier, S_IRUGO,
		show_sas_rphy_bay_identअगरier, शून्य);

sas_rphy_protocol_attr(identअगरy.initiator_port_protocols,
		initiator_port_protocols);
sas_rphy_protocol_attr(identअगरy.target_port_protocols, target_port_protocols);
sas_rphy_simple_attr(identअगरy.sas_address, sas_address, "0x%016llx\n",
		अचिन्हित दीर्घ दीर्घ);
sas_rphy_simple_attr(identअगरy.phy_identअगरier, phy_identअगरier, "%d\n", u8);
sas_rphy_simple_attr(scsi_target_id, scsi_target_id, "%d\n", u32);

/* only need 8 bytes of data plus header (4 or 8) */
#घोषणा BUF_SIZE 64

पूर्णांक sas_पढ़ो_port_mode_page(काष्ठा scsi_device *sdev)
अणु
	अक्षर *buffer = kzalloc(BUF_SIZE, GFP_KERNEL), *msdata;
	काष्ठा sas_end_device *rdev = sas_sdev_to_rdev(sdev);
	काष्ठा scsi_mode_data mode_data;
	पूर्णांक res, error;

	अगर (!buffer)
		वापस -ENOMEM;

	res = scsi_mode_sense(sdev, 1, 0x19, buffer, BUF_SIZE, 30*HZ, 3,
			      &mode_data, शून्य);

	error = -EINVAL;
	अगर (!scsi_status_is_good(res))
		जाओ out;

	msdata = buffer +  mode_data.header_length +
		mode_data.block_descriptor_length;

	अगर (msdata - buffer > BUF_SIZE - 8)
		जाओ out;

	error = 0;

	rdev->पढ़ोy_led_meaning = msdata[2] & 0x10 ? 1 : 0;
	rdev->I_T_nexus_loss_समयout = (msdata[4] << 8) + msdata[5];
	rdev->initiator_response_समयout = (msdata[6] << 8) + msdata[7];

 out:
	kमुक्त(buffer);
	वापस error;
पूर्ण
EXPORT_SYMBOL(sas_पढ़ो_port_mode_page);

अटल DECLARE_TRANSPORT_CLASS(sas_end_dev_class,
			       "sas_end_device", शून्य, शून्य, शून्य);

#घोषणा sas_end_dev_show_simple(field, name, क्रमmat_string, cast)	\
अटल sमाप_प्रकार								\
show_sas_end_dev_##name(काष्ठा device *dev, 				\
			काष्ठा device_attribute *attr, अक्षर *buf)	\
अणु									\
	काष्ठा sas_rphy *rphy = transport_class_to_rphy(dev);		\
	काष्ठा sas_end_device *rdev = rphy_to_end_device(rphy);		\
									\
	वापस snम_लिखो(buf, 20, क्रमmat_string, cast rdev->field);	\
पूर्ण

#घोषणा sas_end_dev_simple_attr(field, name, क्रमmat_string, type)	\
	sas_end_dev_show_simple(field, name, क्रमmat_string, (type))	\
अटल SAS_DEVICE_ATTR(end_dev, name, S_IRUGO, 			\
		show_sas_end_dev_##name, शून्य)

sas_end_dev_simple_attr(पढ़ोy_led_meaning, पढ़ोy_led_meaning, "%d\n", पूर्णांक);
sas_end_dev_simple_attr(I_T_nexus_loss_समयout, I_T_nexus_loss_समयout,
			"%d\n", पूर्णांक);
sas_end_dev_simple_attr(initiator_response_समयout, initiator_response_समयout,
			"%d\n", पूर्णांक);
sas_end_dev_simple_attr(tlr_supported, tlr_supported,
			"%d\n", पूर्णांक);
sas_end_dev_simple_attr(tlr_enabled, tlr_enabled,
			"%d\n", पूर्णांक);

अटल DECLARE_TRANSPORT_CLASS(sas_expander_class,
			       "sas_expander", शून्य, शून्य, शून्य);

#घोषणा sas_expander_show_simple(field, name, क्रमmat_string, cast)	\
अटल sमाप_प्रकार								\
show_sas_expander_##name(काष्ठा device *dev, 				\
			 काष्ठा device_attribute *attr, अक्षर *buf)	\
अणु									\
	काष्ठा sas_rphy *rphy = transport_class_to_rphy(dev);		\
	काष्ठा sas_expander_device *edev = rphy_to_expander_device(rphy); \
									\
	वापस snम_लिखो(buf, 20, क्रमmat_string, cast edev->field);	\
पूर्ण

#घोषणा sas_expander_simple_attr(field, name, क्रमmat_string, type)	\
	sas_expander_show_simple(field, name, क्रमmat_string, (type))	\
अटल SAS_DEVICE_ATTR(expander, name, S_IRUGO, 			\
		show_sas_expander_##name, शून्य)

sas_expander_simple_attr(venकरोr_id, venकरोr_id, "%s\n", अक्षर *);
sas_expander_simple_attr(product_id, product_id, "%s\n", अक्षर *);
sas_expander_simple_attr(product_rev, product_rev, "%s\n", अक्षर *);
sas_expander_simple_attr(component_venकरोr_id, component_venकरोr_id,
			 "%s\n", अक्षर *);
sas_expander_simple_attr(component_id, component_id, "%u\n", अचिन्हित पूर्णांक);
sas_expander_simple_attr(component_revision_id, component_revision_id, "%u\n",
			 अचिन्हित पूर्णांक);
sas_expander_simple_attr(level, level, "%d\n", पूर्णांक);

अटल DECLARE_TRANSPORT_CLASS(sas_rphy_class,
		"sas_device", शून्य, शून्य, शून्य);

अटल पूर्णांक sas_rphy_match(काष्ठा attribute_container *cont, काष्ठा device *dev)
अणु
	काष्ठा Scsi_Host *shost;
	काष्ठा sas_पूर्णांकernal *i;

	अगर (!scsi_is_sas_rphy(dev))
		वापस 0;
	shost = dev_to_shost(dev->parent->parent);

	अगर (!shost->transportt)
		वापस 0;
	अगर (shost->transportt->host_attrs.ac.class !=
			&sas_host_class.class)
		वापस 0;

	i = to_sas_पूर्णांकernal(shost->transportt);
	वापस &i->rphy_attr_cont.ac == cont;
पूर्ण

अटल पूर्णांक sas_end_dev_match(काष्ठा attribute_container *cont,
			     काष्ठा device *dev)
अणु
	काष्ठा Scsi_Host *shost;
	काष्ठा sas_पूर्णांकernal *i;
	काष्ठा sas_rphy *rphy;

	अगर (!scsi_is_sas_rphy(dev))
		वापस 0;
	shost = dev_to_shost(dev->parent->parent);
	rphy = dev_to_rphy(dev);

	अगर (!shost->transportt)
		वापस 0;
	अगर (shost->transportt->host_attrs.ac.class !=
			&sas_host_class.class)
		वापस 0;

	i = to_sas_पूर्णांकernal(shost->transportt);
	वापस &i->end_dev_attr_cont.ac == cont &&
		rphy->identअगरy.device_type == SAS_END_DEVICE;
पूर्ण

अटल पूर्णांक sas_expander_match(काष्ठा attribute_container *cont,
			      काष्ठा device *dev)
अणु
	काष्ठा Scsi_Host *shost;
	काष्ठा sas_पूर्णांकernal *i;
	काष्ठा sas_rphy *rphy;

	अगर (!scsi_is_sas_rphy(dev))
		वापस 0;
	shost = dev_to_shost(dev->parent->parent);
	rphy = dev_to_rphy(dev);

	अगर (!shost->transportt)
		वापस 0;
	अगर (shost->transportt->host_attrs.ac.class !=
			&sas_host_class.class)
		वापस 0;

	i = to_sas_पूर्णांकernal(shost->transportt);
	वापस &i->expander_attr_cont.ac == cont &&
		(rphy->identअगरy.device_type == SAS_EDGE_EXPANDER_DEVICE ||
		 rphy->identअगरy.device_type == SAS_FANOUT_EXPANDER_DEVICE);
पूर्ण

अटल व्योम sas_expander_release(काष्ठा device *dev)
अणु
	काष्ठा sas_rphy *rphy = dev_to_rphy(dev);
	काष्ठा sas_expander_device *edev = rphy_to_expander_device(rphy);

	put_device(dev->parent);
	kमुक्त(edev);
पूर्ण

अटल व्योम sas_end_device_release(काष्ठा device *dev)
अणु
	काष्ठा sas_rphy *rphy = dev_to_rphy(dev);
	काष्ठा sas_end_device *edev = rphy_to_end_device(rphy);

	put_device(dev->parent);
	kमुक्त(edev);
पूर्ण

/**
 * sas_rphy_initialize - common rphy initialization
 * @rphy:	rphy to initialise
 *
 * Used by both sas_end_device_alloc() and sas_expander_alloc() to
 * initialise the common rphy component of each.
 */
अटल व्योम sas_rphy_initialize(काष्ठा sas_rphy *rphy)
अणु
	INIT_LIST_HEAD(&rphy->list);
पूर्ण

/**
 * sas_end_device_alloc - allocate an rphy क्रम an end device
 * @parent: which port
 *
 * Allocates an SAS remote PHY काष्ठाure, connected to @parent.
 *
 * Returns:
 *	SAS PHY allocated or %शून्य अगर the allocation failed.
 */
काष्ठा sas_rphy *sas_end_device_alloc(काष्ठा sas_port *parent)
अणु
	काष्ठा Scsi_Host *shost = dev_to_shost(&parent->dev);
	काष्ठा sas_end_device *rdev;

	rdev = kzalloc(माप(*rdev), GFP_KERNEL);
	अगर (!rdev) अणु
		वापस शून्य;
	पूर्ण

	device_initialize(&rdev->rphy.dev);
	rdev->rphy.dev.parent = get_device(&parent->dev);
	rdev->rphy.dev.release = sas_end_device_release;
	अगर (scsi_is_sas_expander_device(parent->dev.parent)) अणु
		काष्ठा sas_rphy *rphy = dev_to_rphy(parent->dev.parent);
		dev_set_name(&rdev->rphy.dev, "end_device-%d:%d:%d",
			     shost->host_no, rphy->scsi_target_id,
			     parent->port_identअगरier);
	पूर्ण अन्यथा
		dev_set_name(&rdev->rphy.dev, "end_device-%d:%d",
			     shost->host_no, parent->port_identअगरier);
	rdev->rphy.identअगरy.device_type = SAS_END_DEVICE;
	sas_rphy_initialize(&rdev->rphy);
	transport_setup_device(&rdev->rphy.dev);

	वापस &rdev->rphy;
पूर्ण
EXPORT_SYMBOL(sas_end_device_alloc);

/**
 * sas_expander_alloc - allocate an rphy क्रम an end device
 * @parent: which port
 * @type: SAS_EDGE_EXPANDER_DEVICE or SAS_FANOUT_EXPANDER_DEVICE
 *
 * Allocates an SAS remote PHY काष्ठाure, connected to @parent.
 *
 * Returns:
 *	SAS PHY allocated or %शून्य अगर the allocation failed.
 */
काष्ठा sas_rphy *sas_expander_alloc(काष्ठा sas_port *parent,
				    क्रमागत sas_device_type type)
अणु
	काष्ठा Scsi_Host *shost = dev_to_shost(&parent->dev);
	काष्ठा sas_expander_device *rdev;
	काष्ठा sas_host_attrs *sas_host = to_sas_host_attrs(shost);

	BUG_ON(type != SAS_EDGE_EXPANDER_DEVICE &&
	       type != SAS_FANOUT_EXPANDER_DEVICE);

	rdev = kzalloc(माप(*rdev), GFP_KERNEL);
	अगर (!rdev) अणु
		वापस शून्य;
	पूर्ण

	device_initialize(&rdev->rphy.dev);
	rdev->rphy.dev.parent = get_device(&parent->dev);
	rdev->rphy.dev.release = sas_expander_release;
	mutex_lock(&sas_host->lock);
	rdev->rphy.scsi_target_id = sas_host->next_expander_id++;
	mutex_unlock(&sas_host->lock);
	dev_set_name(&rdev->rphy.dev, "expander-%d:%d",
		     shost->host_no, rdev->rphy.scsi_target_id);
	rdev->rphy.identअगरy.device_type = type;
	sas_rphy_initialize(&rdev->rphy);
	transport_setup_device(&rdev->rphy.dev);

	वापस &rdev->rphy;
पूर्ण
EXPORT_SYMBOL(sas_expander_alloc);

/**
 * sas_rphy_add  -  add a SAS remote PHY to the device hierarchy
 * @rphy:	The remote PHY to be added
 *
 * Publishes a SAS remote PHY to the rest of the प्रणाली.
 */
पूर्णांक sas_rphy_add(काष्ठा sas_rphy *rphy)
अणु
	काष्ठा sas_port *parent = dev_to_sas_port(rphy->dev.parent);
	काष्ठा Scsi_Host *shost = dev_to_shost(parent->dev.parent);
	काष्ठा sas_host_attrs *sas_host = to_sas_host_attrs(shost);
	काष्ठा sas_identअगरy *identअगरy = &rphy->identअगरy;
	पूर्णांक error;

	अगर (parent->rphy)
		वापस -ENXIO;
	parent->rphy = rphy;

	error = device_add(&rphy->dev);
	अगर (error)
		वापस error;
	transport_add_device(&rphy->dev);
	transport_configure_device(&rphy->dev);
	अगर (sas_bsg_initialize(shost, rphy))
		prपूर्णांकk("fail to a bsg device %s\n", dev_name(&rphy->dev));


	mutex_lock(&sas_host->lock);
	list_add_tail(&rphy->list, &sas_host->rphy_list);
	अगर (identअगरy->device_type == SAS_END_DEVICE &&
	    (identअगरy->target_port_protocols &
	     (SAS_PROTOCOL_SSP | SAS_PROTOCOL_STP | SAS_PROTOCOL_SATA)))
		rphy->scsi_target_id = sas_host->next_target_id++;
	अन्यथा अगर (identअगरy->device_type == SAS_END_DEVICE)
		rphy->scsi_target_id = -1;
	mutex_unlock(&sas_host->lock);

	अगर (identअगरy->device_type == SAS_END_DEVICE &&
	    rphy->scsi_target_id != -1) अणु
		पूर्णांक lun;

		अगर (identअगरy->target_port_protocols & SAS_PROTOCOL_SSP)
			lun = SCAN_WILD_CARD;
		अन्यथा
			lun = 0;

		scsi_scan_target(&rphy->dev, 0, rphy->scsi_target_id, lun,
				 SCSI_SCAN_INITIAL);
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(sas_rphy_add);

/**
 * sas_rphy_मुक्त  -  मुक्त a SAS remote PHY
 * @rphy: SAS remote PHY to मुक्त
 *
 * Frees the specअगरied SAS remote PHY.
 *
 * Note:
 *   This function must only be called on a remote
 *   PHY that has not successfully been added using
 *   sas_rphy_add() (or has been sas_rphy_हटाओ()'d)
 */
व्योम sas_rphy_मुक्त(काष्ठा sas_rphy *rphy)
अणु
	काष्ठा device *dev = &rphy->dev;
	काष्ठा Scsi_Host *shost = dev_to_shost(rphy->dev.parent->parent);
	काष्ठा sas_host_attrs *sas_host = to_sas_host_attrs(shost);

	mutex_lock(&sas_host->lock);
	list_del(&rphy->list);
	mutex_unlock(&sas_host->lock);

	transport_destroy_device(dev);

	put_device(dev);
पूर्ण
EXPORT_SYMBOL(sas_rphy_मुक्त);

/**
 * sas_rphy_delete  -  हटाओ and मुक्त SAS remote PHY
 * @rphy:	SAS remote PHY to हटाओ and मुक्त
 *
 * Removes the specअगरied SAS remote PHY and मुक्तs it.
 */
व्योम
sas_rphy_delete(काष्ठा sas_rphy *rphy)
अणु
	sas_rphy_हटाओ(rphy);
	sas_rphy_मुक्त(rphy);
पूर्ण
EXPORT_SYMBOL(sas_rphy_delete);

/**
 * sas_rphy_unlink  -  unlink SAS remote PHY
 * @rphy:	SAS remote phy to unlink from its parent port
 *
 * Removes port reference to an rphy
 */
व्योम sas_rphy_unlink(काष्ठा sas_rphy *rphy)
अणु
	काष्ठा sas_port *parent = dev_to_sas_port(rphy->dev.parent);

	parent->rphy = शून्य;
पूर्ण
EXPORT_SYMBOL(sas_rphy_unlink);

/**
 * sas_rphy_हटाओ  -  हटाओ SAS remote PHY
 * @rphy:	SAS remote phy to हटाओ
 *
 * Removes the specअगरied SAS remote PHY.
 */
व्योम
sas_rphy_हटाओ(काष्ठा sas_rphy *rphy)
अणु
	काष्ठा device *dev = &rphy->dev;

	चयन (rphy->identअगरy.device_type) अणु
	हाल SAS_END_DEVICE:
		scsi_हटाओ_target(dev);
		अवरोध;
	हाल SAS_EDGE_EXPANDER_DEVICE:
	हाल SAS_FANOUT_EXPANDER_DEVICE:
		sas_हटाओ_children(dev);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	sas_rphy_unlink(rphy);
	bsg_हटाओ_queue(rphy->q);
	transport_हटाओ_device(dev);
	device_del(dev);
पूर्ण
EXPORT_SYMBOL(sas_rphy_हटाओ);

/**
 * scsi_is_sas_rphy  -  check अगर a काष्ठा device represents a SAS remote PHY
 * @dev:	device to check
 *
 * Returns:
 *	%1 अगर the device represents a SAS remote PHY, %0 अन्यथा
 */
पूर्णांक scsi_is_sas_rphy(स्थिर काष्ठा device *dev)
अणु
	वापस dev->release == sas_end_device_release ||
		dev->release == sas_expander_release;
पूर्ण
EXPORT_SYMBOL(scsi_is_sas_rphy);


/*
 * SCSI scan helper
 */

अटल पूर्णांक sas_user_scan(काष्ठा Scsi_Host *shost, uपूर्णांक channel,
		uपूर्णांक id, u64 lun)
अणु
	काष्ठा sas_host_attrs *sas_host = to_sas_host_attrs(shost);
	काष्ठा sas_rphy *rphy;

	mutex_lock(&sas_host->lock);
	list_क्रम_each_entry(rphy, &sas_host->rphy_list, list) अणु
		अगर (rphy->identअगरy.device_type != SAS_END_DEVICE ||
		    rphy->scsi_target_id == -1)
			जारी;

		अगर ((channel == SCAN_WILD_CARD || channel == 0) &&
		    (id == SCAN_WILD_CARD || id == rphy->scsi_target_id)) अणु
			scsi_scan_target(&rphy->dev, 0, rphy->scsi_target_id,
					 lun, SCSI_SCAN_MANUAL);
		पूर्ण
	पूर्ण
	mutex_unlock(&sas_host->lock);

	वापस 0;
पूर्ण


/*
 * Setup / Tearकरोwn code
 */

#घोषणा SETUP_TEMPLATE(attrb, field, perm, test)			\
	i->निजी_##attrb[count] = dev_attr_##field;		\
	i->निजी_##attrb[count].attr.mode = perm;			\
	i->attrb[count] = &i->निजी_##attrb[count];			\
	अगर (test)							\
		count++

#घोषणा SETUP_TEMPLATE_RW(attrb, field, perm, test, ro_test, ro_perm)	\
	i->निजी_##attrb[count] = dev_attr_##field;		\
	i->निजी_##attrb[count].attr.mode = perm;			\
	अगर (ro_test) अणु							\
		i->निजी_##attrb[count].attr.mode = ro_perm;		\
		i->निजी_##attrb[count].store = शून्य;			\
	पूर्ण								\
	i->attrb[count] = &i->निजी_##attrb[count];			\
	अगर (test)							\
		count++

#घोषणा SETUP_RPORT_ATTRIBUTE(field) 					\
	SETUP_TEMPLATE(rphy_attrs, field, S_IRUGO, 1)

#घोषणा SETUP_OPTIONAL_RPORT_ATTRIBUTE(field, func)			\
	SETUP_TEMPLATE(rphy_attrs, field, S_IRUGO, i->f->func)

#घोषणा SETUP_PHY_ATTRIBUTE(field)					\
	SETUP_TEMPLATE(phy_attrs, field, S_IRUGO, 1)

#घोषणा SETUP_PHY_ATTRIBUTE_RW(field)					\
	SETUP_TEMPLATE_RW(phy_attrs, field, S_IRUGO | S_IWUSR, 1,	\
			!i->f->set_phy_speed, S_IRUGO)

#घोषणा SETUP_OPTIONAL_PHY_ATTRIBUTE_RW(field, func)			\
	SETUP_TEMPLATE_RW(phy_attrs, field, S_IRUGO | S_IWUSR, 1,	\
			  !i->f->func, S_IRUGO)

#घोषणा SETUP_PORT_ATTRIBUTE(field)					\
	SETUP_TEMPLATE(port_attrs, field, S_IRUGO, 1)

#घोषणा SETUP_OPTIONAL_PHY_ATTRIBUTE(field, func)			\
	SETUP_TEMPLATE(phy_attrs, field, S_IRUGO, i->f->func)

#घोषणा SETUP_PHY_ATTRIBUTE_WRONLY(field)				\
	SETUP_TEMPLATE(phy_attrs, field, S_IWUSR, 1)

#घोषणा SETUP_OPTIONAL_PHY_ATTRIBUTE_WRONLY(field, func)		\
	SETUP_TEMPLATE(phy_attrs, field, S_IWUSR, i->f->func)

#घोषणा SETUP_END_DEV_ATTRIBUTE(field)					\
	SETUP_TEMPLATE(end_dev_attrs, field, S_IRUGO, 1)

#घोषणा SETUP_EXPANDER_ATTRIBUTE(field)					\
	SETUP_TEMPLATE(expander_attrs, expander_##field, S_IRUGO, 1)

/**
 * sas_attach_transport  -  instantiate SAS transport ढाँचा
 * @ft:		SAS transport class function ढाँचा
 */
काष्ठा scsi_transport_ढाँचा *
sas_attach_transport(काष्ठा sas_function_ढाँचा *ft)
अणु
	काष्ठा sas_पूर्णांकernal *i;
	पूर्णांक count;

	i = kzalloc(माप(काष्ठा sas_पूर्णांकernal), GFP_KERNEL);
	अगर (!i)
		वापस शून्य;

	i->t.user_scan = sas_user_scan;

	i->t.host_attrs.ac.attrs = &i->host_attrs[0];
	i->t.host_attrs.ac.class = &sas_host_class.class;
	i->t.host_attrs.ac.match = sas_host_match;
	transport_container_रेजिस्टर(&i->t.host_attrs);
	i->t.host_size = माप(काष्ठा sas_host_attrs);

	i->phy_attr_cont.ac.class = &sas_phy_class.class;
	i->phy_attr_cont.ac.attrs = &i->phy_attrs[0];
	i->phy_attr_cont.ac.match = sas_phy_match;
	transport_container_रेजिस्टर(&i->phy_attr_cont);

	i->port_attr_cont.ac.class = &sas_port_class.class;
	i->port_attr_cont.ac.attrs = &i->port_attrs[0];
	i->port_attr_cont.ac.match = sas_port_match;
	transport_container_रेजिस्टर(&i->port_attr_cont);

	i->rphy_attr_cont.ac.class = &sas_rphy_class.class;
	i->rphy_attr_cont.ac.attrs = &i->rphy_attrs[0];
	i->rphy_attr_cont.ac.match = sas_rphy_match;
	transport_container_रेजिस्टर(&i->rphy_attr_cont);

	i->end_dev_attr_cont.ac.class = &sas_end_dev_class.class;
	i->end_dev_attr_cont.ac.attrs = &i->end_dev_attrs[0];
	i->end_dev_attr_cont.ac.match = sas_end_dev_match;
	transport_container_रेजिस्टर(&i->end_dev_attr_cont);

	i->expander_attr_cont.ac.class = &sas_expander_class.class;
	i->expander_attr_cont.ac.attrs = &i->expander_attrs[0];
	i->expander_attr_cont.ac.match = sas_expander_match;
	transport_container_रेजिस्टर(&i->expander_attr_cont);

	i->f = ft;

	count = 0;
	SETUP_PHY_ATTRIBUTE(initiator_port_protocols);
	SETUP_PHY_ATTRIBUTE(target_port_protocols);
	SETUP_PHY_ATTRIBUTE(device_type);
	SETUP_PHY_ATTRIBUTE(sas_address);
	SETUP_PHY_ATTRIBUTE(phy_identअगरier);
	SETUP_PHY_ATTRIBUTE(negotiated_linkrate);
	SETUP_PHY_ATTRIBUTE(minimum_linkrate_hw);
	SETUP_PHY_ATTRIBUTE_RW(minimum_linkrate);
	SETUP_PHY_ATTRIBUTE(maximum_linkrate_hw);
	SETUP_PHY_ATTRIBUTE_RW(maximum_linkrate);

	SETUP_PHY_ATTRIBUTE(invalid_dword_count);
	SETUP_PHY_ATTRIBUTE(running_disparity_error_count);
	SETUP_PHY_ATTRIBUTE(loss_of_dword_sync_count);
	SETUP_PHY_ATTRIBUTE(phy_reset_problem_count);
	SETUP_OPTIONAL_PHY_ATTRIBUTE_WRONLY(link_reset, phy_reset);
	SETUP_OPTIONAL_PHY_ATTRIBUTE_WRONLY(hard_reset, phy_reset);
	SETUP_OPTIONAL_PHY_ATTRIBUTE_RW(enable, phy_enable);
	i->phy_attrs[count] = शून्य;

	count = 0;
	SETUP_PORT_ATTRIBUTE(num_phys);
	i->port_attrs[count] = शून्य;

	count = 0;
	SETUP_RPORT_ATTRIBUTE(rphy_initiator_port_protocols);
	SETUP_RPORT_ATTRIBUTE(rphy_target_port_protocols);
	SETUP_RPORT_ATTRIBUTE(rphy_device_type);
	SETUP_RPORT_ATTRIBUTE(rphy_sas_address);
	SETUP_RPORT_ATTRIBUTE(rphy_phy_identअगरier);
	SETUP_RPORT_ATTRIBUTE(rphy_scsi_target_id);
	SETUP_OPTIONAL_RPORT_ATTRIBUTE(rphy_enclosure_identअगरier,
				       get_enclosure_identअगरier);
	SETUP_OPTIONAL_RPORT_ATTRIBUTE(rphy_bay_identअगरier,
				       get_bay_identअगरier);
	i->rphy_attrs[count] = शून्य;

	count = 0;
	SETUP_END_DEV_ATTRIBUTE(end_dev_पढ़ोy_led_meaning);
	SETUP_END_DEV_ATTRIBUTE(end_dev_I_T_nexus_loss_समयout);
	SETUP_END_DEV_ATTRIBUTE(end_dev_initiator_response_समयout);
	SETUP_END_DEV_ATTRIBUTE(end_dev_tlr_supported);
	SETUP_END_DEV_ATTRIBUTE(end_dev_tlr_enabled);
	i->end_dev_attrs[count] = शून्य;

	count = 0;
	SETUP_EXPANDER_ATTRIBUTE(venकरोr_id);
	SETUP_EXPANDER_ATTRIBUTE(product_id);
	SETUP_EXPANDER_ATTRIBUTE(product_rev);
	SETUP_EXPANDER_ATTRIBUTE(component_venकरोr_id);
	SETUP_EXPANDER_ATTRIBUTE(component_id);
	SETUP_EXPANDER_ATTRIBUTE(component_revision_id);
	SETUP_EXPANDER_ATTRIBUTE(level);
	i->expander_attrs[count] = शून्य;

	वापस &i->t;
पूर्ण
EXPORT_SYMBOL(sas_attach_transport);

/**
 * sas_release_transport  -  release SAS transport ढाँचा instance
 * @t:		transport ढाँचा instance
 */
व्योम sas_release_transport(काष्ठा scsi_transport_ढाँचा *t)
अणु
	काष्ठा sas_पूर्णांकernal *i = to_sas_पूर्णांकernal(t);

	transport_container_unरेजिस्टर(&i->t.host_attrs);
	transport_container_unरेजिस्टर(&i->phy_attr_cont);
	transport_container_unरेजिस्टर(&i->port_attr_cont);
	transport_container_unरेजिस्टर(&i->rphy_attr_cont);
	transport_container_unरेजिस्टर(&i->end_dev_attr_cont);
	transport_container_unरेजिस्टर(&i->expander_attr_cont);

	kमुक्त(i);
पूर्ण
EXPORT_SYMBOL(sas_release_transport);

अटल __init पूर्णांक sas_transport_init(व्योम)
अणु
	पूर्णांक error;

	error = transport_class_रेजिस्टर(&sas_host_class);
	अगर (error)
		जाओ out;
	error = transport_class_रेजिस्टर(&sas_phy_class);
	अगर (error)
		जाओ out_unरेजिस्टर_transport;
	error = transport_class_रेजिस्टर(&sas_port_class);
	अगर (error)
		जाओ out_unरेजिस्टर_phy;
	error = transport_class_रेजिस्टर(&sas_rphy_class);
	अगर (error)
		जाओ out_unरेजिस्टर_port;
	error = transport_class_रेजिस्टर(&sas_end_dev_class);
	अगर (error)
		जाओ out_unरेजिस्टर_rphy;
	error = transport_class_रेजिस्टर(&sas_expander_class);
	अगर (error)
		जाओ out_unरेजिस्टर_end_dev;

	वापस 0;

 out_unरेजिस्टर_end_dev:
	transport_class_unरेजिस्टर(&sas_end_dev_class);
 out_unरेजिस्टर_rphy:
	transport_class_unरेजिस्टर(&sas_rphy_class);
 out_unरेजिस्टर_port:
	transport_class_unरेजिस्टर(&sas_port_class);
 out_unरेजिस्टर_phy:
	transport_class_unरेजिस्टर(&sas_phy_class);
 out_unरेजिस्टर_transport:
	transport_class_unरेजिस्टर(&sas_host_class);
 out:
	वापस error;

पूर्ण

अटल व्योम __निकास sas_transport_निकास(व्योम)
अणु
	transport_class_unरेजिस्टर(&sas_host_class);
	transport_class_unरेजिस्टर(&sas_phy_class);
	transport_class_unरेजिस्टर(&sas_port_class);
	transport_class_unरेजिस्टर(&sas_rphy_class);
	transport_class_unरेजिस्टर(&sas_end_dev_class);
	transport_class_unरेजिस्टर(&sas_expander_class);
पूर्ण

MODULE_AUTHOR("Christoph Hellwig");
MODULE_DESCRIPTION("SAS Transport Attributes");
MODULE_LICENSE("GPL");

module_init(sas_transport_init);
module_निकास(sas_transport_निकास);
