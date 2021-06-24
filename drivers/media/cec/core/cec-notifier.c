<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * cec-notअगरier.c - notअगरy CEC drivers of physical address changes
 *
 * Copyright 2016 Russell King.
 * Copyright 2016-2017 Cisco Systems, Inc. and/or its affiliates. All rights reserved.
 */

#समावेश <linux/export.h>
#समावेश <linux/माला.स>
#समावेश <linux/slab.h>
#समावेश <linux/i2c.h>
#समावेश <linux/list.h>
#समावेश <linux/kref.h>
#समावेश <linux/of_platक्रमm.h>

#समावेश <media/cec.h>
#समावेश <media/cec-notअगरier.h>
#समावेश <drm/drm_edid.h>

काष्ठा cec_notअगरier अणु
	काष्ठा mutex lock;
	काष्ठा list_head head;
	काष्ठा kref kref;
	काष्ठा device *hdmi_dev;
	काष्ठा cec_connector_info conn_info;
	स्थिर अक्षर *port_name;
	काष्ठा cec_adapter *cec_adap;

	u16 phys_addr;
पूर्ण;

अटल LIST_HEAD(cec_notअगरiers);
अटल DEFINE_MUTEX(cec_notअगरiers_lock);

/**
 * cec_notअगरier_get_conn - find or create a new cec_notअगरier क्रम the given
 * device and connector tuple.
 * @hdmi_dev: device that sends the events.
 * @port_name: the connector name from which the event occurs
 *
 * If a notअगरier क्रम device @dev alपढ़ोy exists, then increase the refcount
 * and वापस that notअगरier.
 *
 * If it करोesn't exist, then allocate a new notअगरier काष्ठा and वापस a
 * poपूर्णांकer to that new काष्ठा.
 *
 * Return शून्य अगर the memory could not be allocated.
 */
अटल काष्ठा cec_notअगरier *
cec_notअगरier_get_conn(काष्ठा device *hdmi_dev, स्थिर अक्षर *port_name)
अणु
	काष्ठा cec_notअगरier *n;

	mutex_lock(&cec_notअगरiers_lock);
	list_क्रम_each_entry(n, &cec_notअगरiers, head) अणु
		अगर (n->hdmi_dev == hdmi_dev &&
		    (!port_name ||
		     (n->port_name && !म_भेद(n->port_name, port_name)))) अणु
			kref_get(&n->kref);
			mutex_unlock(&cec_notअगरiers_lock);
			वापस n;
		पूर्ण
	पूर्ण
	n = kzalloc(माप(*n), GFP_KERNEL);
	अगर (!n)
		जाओ unlock;
	n->hdmi_dev = hdmi_dev;
	अगर (port_name) अणु
		n->port_name = kstrdup(port_name, GFP_KERNEL);
		अगर (!n->port_name) अणु
			kमुक्त(n);
			n = शून्य;
			जाओ unlock;
		पूर्ण
	पूर्ण
	n->phys_addr = CEC_PHYS_ADDR_INVALID;

	mutex_init(&n->lock);
	kref_init(&n->kref);
	list_add_tail(&n->head, &cec_notअगरiers);
unlock:
	mutex_unlock(&cec_notअगरiers_lock);
	वापस n;
पूर्ण

अटल व्योम cec_notअगरier_release(काष्ठा kref *kref)
अणु
	काष्ठा cec_notअगरier *n =
		container_of(kref, काष्ठा cec_notअगरier, kref);

	list_del(&n->head);
	kमुक्त(n->port_name);
	kमुक्त(n);
पूर्ण

अटल व्योम cec_notअगरier_put(काष्ठा cec_notअगरier *n)
अणु
	mutex_lock(&cec_notअगरiers_lock);
	kref_put(&n->kref, cec_notअगरier_release);
	mutex_unlock(&cec_notअगरiers_lock);
पूर्ण

काष्ठा cec_notअगरier *
cec_notअगरier_conn_रेजिस्टर(काष्ठा device *hdmi_dev, स्थिर अक्षर *port_name,
			   स्थिर काष्ठा cec_connector_info *conn_info)
अणु
	काष्ठा cec_notअगरier *n = cec_notअगरier_get_conn(hdmi_dev, port_name);

	अगर (!n)
		वापस n;

	mutex_lock(&n->lock);
	n->phys_addr = CEC_PHYS_ADDR_INVALID;
	अगर (conn_info)
		n->conn_info = *conn_info;
	अन्यथा
		स_रखो(&n->conn_info, 0, माप(n->conn_info));
	अगर (n->cec_adap) अणु
		अगर (!n->cec_adap->adap_controls_phys_addr)
			cec_phys_addr_invalidate(n->cec_adap);
		cec_s_conn_info(n->cec_adap, conn_info);
	पूर्ण
	mutex_unlock(&n->lock);
	वापस n;
पूर्ण
EXPORT_SYMBOL_GPL(cec_notअगरier_conn_रेजिस्टर);

व्योम cec_notअगरier_conn_unरेजिस्टर(काष्ठा cec_notअगरier *n)
अणु
	अगर (!n)
		वापस;

	mutex_lock(&n->lock);
	स_रखो(&n->conn_info, 0, माप(n->conn_info));
	n->phys_addr = CEC_PHYS_ADDR_INVALID;
	अगर (n->cec_adap) अणु
		अगर (!n->cec_adap->adap_controls_phys_addr)
			cec_phys_addr_invalidate(n->cec_adap);
		cec_s_conn_info(n->cec_adap, शून्य);
	पूर्ण
	mutex_unlock(&n->lock);
	cec_notअगरier_put(n);
पूर्ण
EXPORT_SYMBOL_GPL(cec_notअगरier_conn_unरेजिस्टर);

काष्ठा cec_notअगरier *
cec_notअगरier_cec_adap_रेजिस्टर(काष्ठा device *hdmi_dev, स्थिर अक्षर *port_name,
			       काष्ठा cec_adapter *adap)
अणु
	काष्ठा cec_notअगरier *n;

	अगर (WARN_ON(!adap))
		वापस शून्य;

	n = cec_notअगरier_get_conn(hdmi_dev, port_name);
	अगर (!n)
		वापस n;

	mutex_lock(&n->lock);
	n->cec_adap = adap;
	adap->conn_info = n->conn_info;
	adap->notअगरier = n;
	अगर (!adap->adap_controls_phys_addr)
		cec_s_phys_addr(adap, n->phys_addr, false);
	mutex_unlock(&n->lock);
	वापस n;
पूर्ण
EXPORT_SYMBOL_GPL(cec_notअगरier_cec_adap_रेजिस्टर);

व्योम cec_notअगरier_cec_adap_unरेजिस्टर(काष्ठा cec_notअगरier *n,
				      काष्ठा cec_adapter *adap)
अणु
	अगर (!n)
		वापस;

	mutex_lock(&n->lock);
	adap->notअगरier = शून्य;
	n->cec_adap = शून्य;
	mutex_unlock(&n->lock);
	cec_notअगरier_put(n);
पूर्ण
EXPORT_SYMBOL_GPL(cec_notअगरier_cec_adap_unरेजिस्टर);

व्योम cec_notअगरier_set_phys_addr(काष्ठा cec_notअगरier *n, u16 pa)
अणु
	अगर (n == शून्य)
		वापस;

	mutex_lock(&n->lock);
	n->phys_addr = pa;
	अगर (n->cec_adap && !n->cec_adap->adap_controls_phys_addr)
		cec_s_phys_addr(n->cec_adap, n->phys_addr, false);
	mutex_unlock(&n->lock);
पूर्ण
EXPORT_SYMBOL_GPL(cec_notअगरier_set_phys_addr);

व्योम cec_notअगरier_set_phys_addr_from_edid(काष्ठा cec_notअगरier *n,
					  स्थिर काष्ठा edid *edid)
अणु
	u16 pa = CEC_PHYS_ADDR_INVALID;

	अगर (n == शून्य)
		वापस;

	अगर (edid && edid->extensions)
		pa = cec_get_edid_phys_addr((स्थिर u8 *)edid,
				EDID_LENGTH * (edid->extensions + 1), शून्य);
	cec_notअगरier_set_phys_addr(n, pa);
पूर्ण
EXPORT_SYMBOL_GPL(cec_notअगरier_set_phys_addr_from_edid);

काष्ठा device *cec_notअगरier_parse_hdmi_phandle(काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_device *hdmi_pdev;
	काष्ठा device *hdmi_dev = शून्य;
	काष्ठा device_node *np;

	np = of_parse_phandle(dev->of_node, "hdmi-phandle", 0);

	अगर (!np) अणु
		dev_err(dev, "Failed to find HDMI node in device tree\n");
		वापस ERR_PTR(-ENODEV);
	पूर्ण

	hdmi_pdev = of_find_device_by_node(np);
	अगर (hdmi_pdev)
		hdmi_dev = &hdmi_pdev->dev;
#अगर IS_REACHABLE(CONFIG_I2C)
	अगर (!hdmi_dev) अणु
		काष्ठा i2c_client *hdmi_client = of_find_i2c_device_by_node(np);

		अगर (hdmi_client)
			hdmi_dev = &hdmi_client->dev;
	पूर्ण
#पूर्ण_अगर
	of_node_put(np);
	अगर (!hdmi_dev)
		वापस ERR_PTR(-EPROBE_DEFER);

	/*
	 * Note that the device काष्ठा is only used as a key पूर्णांकo the
	 * cec_notअगरiers list, it is never actually accessed.
	 * So we decrement the reference here so we करोn't leak
	 * memory.
	 */
	put_device(hdmi_dev);
	वापस hdmi_dev;
पूर्ण
EXPORT_SYMBOL_GPL(cec_notअगरier_parse_hdmi_phandle);
