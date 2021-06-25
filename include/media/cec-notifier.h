<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * cec-notअगरier.h - notअगरy CEC drivers of physical address changes
 *
 * Copyright 2016 Russell King.
 * Copyright 2016-2017 Cisco Systems, Inc. and/or its affiliates. All rights reserved.
 */

#अगर_अघोषित LINUX_CEC_NOTIFIER_H
#घोषणा LINUX_CEC_NOTIFIER_H

#समावेश <linux/err.h>
#समावेश <media/cec.h>

काष्ठा device;
काष्ठा edid;
काष्ठा cec_adapter;
काष्ठा cec_notअगरier;

#अगर IS_REACHABLE(CONFIG_CEC_CORE) && IS_ENABLED(CONFIG_CEC_NOTIFIER)

/**
 * cec_notअगरier_conn_रेजिस्टर - find or create a new cec_notअगरier क्रम the given
 * HDMI device and connector tuple.
 * @hdmi_dev: HDMI device that sends the events.
 * @port_name: the connector name from which the event occurs. May be शून्य
 * अगर there is always only one HDMI connector created by the HDMI device.
 * @conn_info: the connector info from which the event occurs (may be शून्य)
 *
 * If a notअगरier क्रम device @dev and connector @port_name alपढ़ोy exists, then
 * increase the refcount and वापस that notअगरier.
 *
 * If it करोesn't exist, then allocate a new notअगरier काष्ठा and वापस a
 * poपूर्णांकer to that new काष्ठा.
 *
 * Return शून्य अगर the memory could not be allocated.
 */
काष्ठा cec_notअगरier *
cec_notअगरier_conn_रेजिस्टर(काष्ठा device *hdmi_dev, स्थिर अक्षर *port_name,
			   स्थिर काष्ठा cec_connector_info *conn_info);

/**
 * cec_notअगरier_conn_unरेजिस्टर - decrease refcount and delete when the
 * refcount reaches 0.
 * @n: notअगरier. If शून्य, then this function करोes nothing.
 */
व्योम cec_notअगरier_conn_unरेजिस्टर(काष्ठा cec_notअगरier *n);

/**
 * cec_notअगरier_cec_adap_रेजिस्टर - find or create a new cec_notअगरier क्रम the
 * given device.
 * @hdmi_dev: HDMI device that sends the events.
 * @port_name: the connector name from which the event occurs. May be शून्य
 * अगर there is always only one HDMI connector created by the HDMI device.
 * @adap: the cec adapter that रेजिस्टरed this notअगरier.
 *
 * If a notअगरier क्रम device @dev and connector @port_name alपढ़ोy exists, then
 * increase the refcount and वापस that notअगरier.
 *
 * If it करोesn't exist, then allocate a new notअगरier काष्ठा and वापस a
 * poपूर्णांकer to that new काष्ठा.
 *
 * Return शून्य अगर the memory could not be allocated.
 */
काष्ठा cec_notअगरier *
cec_notअगरier_cec_adap_रेजिस्टर(काष्ठा device *hdmi_dev, स्थिर अक्षर *port_name,
			       काष्ठा cec_adapter *adap);

/**
 * cec_notअगरier_cec_adap_unरेजिस्टर - decrease refcount and delete when the
 * refcount reaches 0.
 * @n: notअगरier. If शून्य, then this function करोes nothing.
 * @adap: the cec adapter that रेजिस्टरed this notअगरier.
 */
व्योम cec_notअगरier_cec_adap_unरेजिस्टर(काष्ठा cec_notअगरier *n,
				      काष्ठा cec_adapter *adap);

/**
 * cec_notअगरier_set_phys_addr - set a new physical address.
 * @n: the CEC notअगरier
 * @pa: the CEC physical address
 *
 * Set a new CEC physical address.
 * Does nothing अगर @n == शून्य.
 */
व्योम cec_notअगरier_set_phys_addr(काष्ठा cec_notअगरier *n, u16 pa);

/**
 * cec_notअगरier_set_phys_addr_from_edid - set parse the PA from the EDID.
 * @n: the CEC notअगरier
 * @edid: the काष्ठा edid poपूर्णांकer
 *
 * Parses the EDID to obtain the new CEC physical address and set it.
 * Does nothing अगर @n == शून्य.
 */
व्योम cec_notअगरier_set_phys_addr_from_edid(काष्ठा cec_notअगरier *n,
					  स्थिर काष्ठा edid *edid);

/**
 * cec_notअगरier_parse_hdmi_phandle - find the hdmi device from "hdmi-phandle"
 * @dev: the device with the "hdmi-phandle" device tree property
 *
 * Returns the device poपूर्णांकer referenced by the "hdmi-phandle" property.
 * Note that the refcount of the वापसed device is not incremented.
 * This device poपूर्णांकer is only used as a key value in the notअगरier
 * list, but it is never accessed by the CEC driver.
 */
काष्ठा device *cec_notअगरier_parse_hdmi_phandle(काष्ठा device *dev);

#अन्यथा

अटल अंतरभूत काष्ठा cec_notअगरier *
cec_notअगरier_conn_रेजिस्टर(काष्ठा device *hdmi_dev, स्थिर अक्षर *port_name,
			   स्थिर काष्ठा cec_connector_info *conn_info)
अणु
	/* A non-शून्य poपूर्णांकer is expected on success */
	वापस (काष्ठा cec_notअगरier *)0xdeadfeed;
पूर्ण

अटल अंतरभूत व्योम cec_notअगरier_conn_unरेजिस्टर(काष्ठा cec_notअगरier *n)
अणु
पूर्ण

अटल अंतरभूत काष्ठा cec_notअगरier *
cec_notअगरier_cec_adap_रेजिस्टर(काष्ठा device *hdmi_dev, स्थिर अक्षर *port_name,
			       काष्ठा cec_adapter *adap)
अणु
	/* A non-शून्य poपूर्णांकer is expected on success */
	वापस (काष्ठा cec_notअगरier *)0xdeadfeed;
पूर्ण

अटल अंतरभूत व्योम cec_notअगरier_cec_adap_unरेजिस्टर(काष्ठा cec_notअगरier *n,
						    काष्ठा cec_adapter *adap)
अणु
पूर्ण

अटल अंतरभूत व्योम cec_notअगरier_set_phys_addr(काष्ठा cec_notअगरier *n, u16 pa)
अणु
पूर्ण

अटल अंतरभूत व्योम cec_notअगरier_set_phys_addr_from_edid(काष्ठा cec_notअगरier *n,
							स्थिर काष्ठा edid *edid)
अणु
पूर्ण

अटल अंतरभूत काष्ठा device *cec_notअगरier_parse_hdmi_phandle(काष्ठा device *dev)
अणु
	वापस ERR_PTR(-ENODEV);
पूर्ण

#पूर्ण_अगर

/**
 * cec_notअगरier_phys_addr_invalidate() - set the physical address to INVALID
 *
 * @n: the CEC notअगरier
 *
 * This is a simple helper function to invalidate the physical
 * address. Does nothing अगर @n == शून्य.
 */
अटल अंतरभूत व्योम cec_notअगरier_phys_addr_invalidate(काष्ठा cec_notअगरier *n)
अणु
	cec_notअगरier_set_phys_addr(n, CEC_PHYS_ADDR_INVALID);
पूर्ण

#पूर्ण_अगर
