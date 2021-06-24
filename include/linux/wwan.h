<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* Copyright (c) 2021, Linaro Ltd <loic.poulain@linaro.org> */

#अगर_अघोषित __WWAN_H
#घोषणा __WWAN_H

#समावेश <linux/device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/skbuff.h>

/**
 * क्रमागत wwan_port_type - WWAN port types
 * @WWAN_PORT_AT: AT commands
 * @WWAN_PORT_MBIM: Mobile Broadband Interface Model control
 * @WWAN_PORT_QMI: Qcom modem/MSM पूर्णांकerface क्रम modem control
 * @WWAN_PORT_QCDM: Qcom Modem diagnostic पूर्णांकerface
 * @WWAN_PORT_FIREHOSE: XML based command protocol
 * @WWAN_PORT_MAX: Number of supported port types
 */
क्रमागत wwan_port_type अणु
	WWAN_PORT_AT,
	WWAN_PORT_MBIM,
	WWAN_PORT_QMI,
	WWAN_PORT_QCDM,
	WWAN_PORT_FIREHOSE,
	WWAN_PORT_MAX,
पूर्ण;

काष्ठा wwan_port;

/** काष्ठा wwan_port_ops - The WWAN port operations
 * @start: The routine क्रम starting the WWAN port device.
 * @stop: The routine क्रम stopping the WWAN port device.
 * @tx: The routine that sends WWAN port protocol data to the device.
 *
 * The wwan_port_ops काष्ठाure contains a list of low-level operations
 * that control a WWAN port device. All functions are mandatory.
 */
काष्ठा wwan_port_ops अणु
	पूर्णांक (*start)(काष्ठा wwan_port *port);
	व्योम (*stop)(काष्ठा wwan_port *port);
	पूर्णांक (*tx)(काष्ठा wwan_port *port, काष्ठा sk_buff *skb);
पूर्ण;

/**
 * wwan_create_port - Add a new WWAN port
 * @parent: Device to use as parent and shared by all WWAN ports
 * @type: WWAN port type
 * @ops: WWAN port operations
 * @drvdata: Poपूर्णांकer to caller driver data
 *
 * Allocate and रेजिस्टर a new WWAN port. The port will be स्वतःmatically exposed
 * to user as a अक्षरacter device and attached to the right भव WWAN device,
 * based on the parent poपूर्णांकer. The parent poपूर्णांकer is the device shared by all
 * components of a same WWAN modem (e.g. USB dev, PCI dev, MHI controller...).
 *
 * drvdata will be placed in the WWAN port device driver data and can be
 * retrieved with wwan_port_get_drvdata().
 *
 * This function must be balanced with a call to wwan_हटाओ_port().
 *
 * Returns a valid poपूर्णांकer to wwan_port on success or PTR_ERR on failure
 */
काष्ठा wwan_port *wwan_create_port(काष्ठा device *parent,
				   क्रमागत wwan_port_type type,
				   स्थिर काष्ठा wwan_port_ops *ops,
				   व्योम *drvdata);

/**
 * wwan_हटाओ_port - Remove a WWAN port
 * @port: WWAN port to हटाओ
 *
 * Remove a previously created port.
 */
व्योम wwan_हटाओ_port(काष्ठा wwan_port *port);

/**
 * wwan_port_rx - Receive data from the WWAN port
 * @port: WWAN port क्रम which data is received
 * @skb: Poपूर्णांकer to the rx buffer
 *
 * A port driver calls this function upon data reception (MBIM, AT...).
 */
व्योम wwan_port_rx(काष्ठा wwan_port *port, काष्ठा sk_buff *skb);

/**
 * wwan_port_txoff - Stop TX on WWAN port
 * @port: WWAN port क्रम which TX must be stopped
 *
 * Used क्रम TX flow control, a port driver calls this function to indicate TX
 * is temporary unavailable (e.g. due to ring buffer fullness).
 */
व्योम wwan_port_txoff(काष्ठा wwan_port *port);


/**
 * wwan_port_txon - Restart TX on WWAN port
 * @port: WWAN port क्रम which TX must be restarted
 *
 * Used क्रम TX flow control, a port driver calls this function to indicate TX
 * is available again.
 */
व्योम wwan_port_txon(काष्ठा wwan_port *port);

/**
 * wwan_port_get_drvdata - Retrieve driver data from a WWAN port
 * @port: Related WWAN port
 */
व्योम *wwan_port_get_drvdata(काष्ठा wwan_port *port);

#पूर्ण_अगर /* __WWAN_H */
