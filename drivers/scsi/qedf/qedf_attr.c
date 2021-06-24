<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  QLogic FCoE Offload Driver
 *  Copyright (c) 2016-2018 Cavium Inc.
 */
#समावेश "qedf.h"

अंतरभूत bool qedf_is_vport(काष्ठा qedf_ctx *qedf)
अणु
	वापस qedf->lport->vport != शून्य;
पूर्ण

/* Get base qedf क्रम physical port from vport */
अटल काष्ठा qedf_ctx *qedf_get_base_qedf(काष्ठा qedf_ctx *qedf)
अणु
	काष्ठा fc_lport *lport;
	काष्ठा fc_lport *base_lport;

	अगर (!(qedf_is_vport(qedf)))
		वापस शून्य;

	lport = qedf->lport;
	base_lport = shost_priv(vport_to_shost(lport->vport));
	वापस lport_priv(base_lport);
पूर्ण

अटल sमाप_प्रकार
qedf_fcoe_mac_show(काष्ठा device *dev,
	काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा fc_lport *lport = shost_priv(class_to_shost(dev));
	u32 port_id;
	u8 lport_src_id[3];
	u8 fcoe_mac[6];

	port_id = fc_host_port_id(lport->host);
	lport_src_id[2] = (port_id & 0x000000FF);
	lport_src_id[1] = (port_id & 0x0000FF00) >> 8;
	lport_src_id[0] = (port_id & 0x00FF0000) >> 16;
	fc_fcoe_set_mac(fcoe_mac, lport_src_id);

	वापस scnम_लिखो(buf, PAGE_SIZE, "%pM\n", fcoe_mac);
पूर्ण

अटल sमाप_प्रकार
qedf_fka_period_show(काष्ठा device *dev,
	काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा fc_lport *lport = shost_priv(class_to_shost(dev));
	काष्ठा qedf_ctx *qedf = lport_priv(lport);
	पूर्णांक fka_period = -1;

	अगर (qedf_is_vport(qedf))
		qedf = qedf_get_base_qedf(qedf);

	अगर (qedf->ctlr.sel_fcf)
		fka_period = qedf->ctlr.sel_fcf->fka_period;

	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n", fka_period);
पूर्ण

अटल DEVICE_ATTR(fcoe_mac, S_IRUGO, qedf_fcoe_mac_show, शून्य);
अटल DEVICE_ATTR(fka_period, S_IRUGO, qedf_fka_period_show, शून्य);

काष्ठा device_attribute *qedf_host_attrs[] = अणु
	&dev_attr_fcoe_mac,
	&dev_attr_fka_period,
	शून्य,
पूर्ण;

बाह्य स्थिर काष्ठा qed_fcoe_ops *qed_ops;

व्योम qedf_capture_grc_dump(काष्ठा qedf_ctx *qedf)
अणु
	काष्ठा qedf_ctx *base_qedf;

	/* Make sure we use the base qedf to take the GRC dump */
	अगर (qedf_is_vport(qedf))
		base_qedf = qedf_get_base_qedf(qedf);
	अन्यथा
		base_qedf = qedf;

	अगर (test_bit(QEDF_GRCDUMP_CAPTURE, &base_qedf->flags)) अणु
		QEDF_INFO(&(base_qedf->dbg_ctx), QEDF_LOG_INFO,
		    "GRC Dump already captured.\n");
		वापस;
	पूर्ण


	qedf_get_grc_dump(base_qedf->cdev, qed_ops->common,
	    &base_qedf->grcdump, &base_qedf->grcdump_size);
	QEDF_ERR(&(base_qedf->dbg_ctx), "GRC Dump captured.\n");
	set_bit(QEDF_GRCDUMP_CAPTURE, &base_qedf->flags);
	qedf_uevent_emit(base_qedf->lport->host, QEDF_UEVENT_CODE_GRCDUMP,
	    शून्य);
पूर्ण

अटल sमाप_प्रकार
qedf_sysfs_पढ़ो_grcdump(काष्ठा file *filep, काष्ठा kobject *kobj,
			काष्ठा bin_attribute *ba, अक्षर *buf, loff_t off,
			माप_प्रकार count)
अणु
	sमाप_प्रकार ret = 0;
	काष्ठा fc_lport *lport = shost_priv(dev_to_shost(container_of(kobj,
							काष्ठा device, kobj)));
	काष्ठा qedf_ctx *qedf = lport_priv(lport);

	अगर (test_bit(QEDF_GRCDUMP_CAPTURE, &qedf->flags)) अणु
		ret = memory_पढ़ो_from_buffer(buf, count, &off,
		    qedf->grcdump, qedf->grcdump_size);
	पूर्ण अन्यथा अणु
		QEDF_ERR(&(qedf->dbg_ctx), "GRC Dump not captured!\n");
	पूर्ण

	वापस ret;
पूर्ण

अटल sमाप_प्रकार
qedf_sysfs_ग_लिखो_grcdump(काष्ठा file *filep, काष्ठा kobject *kobj,
			काष्ठा bin_attribute *ba, अक्षर *buf, loff_t off,
			माप_प्रकार count)
अणु
	काष्ठा fc_lport *lport = शून्य;
	काष्ठा qedf_ctx *qedf = शून्य;
	दीर्घ पढ़ोing;
	पूर्णांक ret = 0;
	अक्षर msg[40];

	अगर (off != 0)
		वापस ret;


	lport = shost_priv(dev_to_shost(container_of(kobj,
	    काष्ठा device, kobj)));
	qedf = lport_priv(lport);

	buf[1] = 0;
	ret = kम_से_दीर्घ(buf, 10, &पढ़ोing);
	अगर (ret) अणु
		QEDF_ERR(&(qedf->dbg_ctx), "Invalid input, err(%d)\n", ret);
		वापस ret;
	पूर्ण

	स_रखो(msg, 0, माप(msg));
	चयन (पढ़ोing) अणु
	हाल 0:
		स_रखो(qedf->grcdump, 0, qedf->grcdump_size);
		clear_bit(QEDF_GRCDUMP_CAPTURE, &qedf->flags);
		अवरोध;
	हाल 1:
		qedf_capture_grc_dump(qedf);
		अवरोध;
	पूर्ण

	वापस count;
पूर्ण

अटल काष्ठा bin_attribute sysfs_grcdump_attr = अणु
	.attr = अणु
		.name = "grcdump",
		.mode = S_IRUSR | S_IWUSR,
	पूर्ण,
	.size = 0,
	.पढ़ो = qedf_sysfs_पढ़ो_grcdump,
	.ग_लिखो = qedf_sysfs_ग_लिखो_grcdump,
पूर्ण;

अटल काष्ठा sysfs_bin_attrs bin_file_entries[] = अणु
	अणु"grcdump", &sysfs_grcdump_attrपूर्ण,
	अणुशून्यपूर्ण,
पूर्ण;

व्योम qedf_create_sysfs_ctx_attr(काष्ठा qedf_ctx *qedf)
अणु
	qedf_create_sysfs_attr(qedf->lport->host, bin_file_entries);
पूर्ण

व्योम qedf_हटाओ_sysfs_ctx_attr(काष्ठा qedf_ctx *qedf)
अणु
	qedf_हटाओ_sysfs_attr(qedf->lport->host, bin_file_entries);
पूर्ण
