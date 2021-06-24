<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * QLogic iSCSI Offload Driver
 * Copyright (c) 2016 Cavium Inc.
 */

#समावेश "qedi.h"
#समावेश "qedi_gbl.h"
#समावेश "qedi_iscsi.h"
#समावेश "qedi_dbg.h"

अटल अंतरभूत काष्ठा qedi_ctx *qedi_dev_to_hba(काष्ठा device *dev)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(dev);

	वापस iscsi_host_priv(shost);
पूर्ण

अटल sमाप_प्रकार qedi_show_port_state(काष्ठा device *dev,
				    काष्ठा device_attribute *attr,
				    अक्षर *buf)
अणु
	काष्ठा qedi_ctx *qedi = qedi_dev_to_hba(dev);

	अगर (atomic_पढ़ो(&qedi->link_state) == QEDI_LINK_UP)
		वापस प्र_लिखो(buf, "Online\n");
	अन्यथा
		वापस प्र_लिखो(buf, "Linkdown\n");
पूर्ण

अटल sमाप_प्रकार qedi_show_speed(काष्ठा device *dev,
			       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा qedi_ctx *qedi = qedi_dev_to_hba(dev);
	काष्ठा qed_link_output अगर_link;

	qedi_ops->common->get_link(qedi->cdev, &अगर_link);

	वापस प्र_लिखो(buf, "%d Gbit\n", अगर_link.speed / 1000);
पूर्ण

अटल DEVICE_ATTR(port_state, 0444, qedi_show_port_state, शून्य);
अटल DEVICE_ATTR(speed, 0444, qedi_show_speed, शून्य);

काष्ठा device_attribute *qedi_shost_attrs[] = अणु
	&dev_attr_port_state,
	&dev_attr_speed,
	शून्य
पूर्ण;
