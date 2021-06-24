<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __LINUX_USB_DLN2_H
#घोषणा __LINUX_USB_DLN2_H

#घोषणा DLN2_CMD(cmd, id)		((cmd) | ((id) << 8))

काष्ठा dln2_platक्रमm_data अणु
	u16 handle;		/* sub-driver handle (पूर्णांकernally used only) */
	u8 port;		/* I2C/SPI port */
पूर्ण;

/**
 * dln2_event_cb_t - event callback function signature
 *
 * @pdev - the sub-device that रेजिस्टरed this callback
 * @echo - the echo header field received in the message
 * @data - the data payload
 * @len  - the data payload length
 *
 * The callback function is called in पूर्णांकerrupt context and the data payload is
 * only valid during the call. If the user needs later access of the data, it
 * must copy it.
 */

प्रकार व्योम (*dln2_event_cb_t)(काष्ठा platक्रमm_device *pdev, u16 echo,
				स्थिर व्योम *data, पूर्णांक len);

/**
 * dl2n_रेजिस्टर_event_cb - रेजिस्टर a callback function क्रम an event
 *
 * @pdev - the sub-device that रेजिस्टरs the callback
 * @event - the event क्रम which to रेजिस्टर a callback
 * @event_cb - the callback function
 *
 * @वापस 0 in हाल of success, negative value in हाल of error
 */
पूर्णांक dln2_रेजिस्टर_event_cb(काष्ठा platक्रमm_device *pdev, u16 event,
			   dln2_event_cb_t event_cb);

/**
 * dln2_unरेजिस्टर_event_cb - unरेजिस्टर the callback function क्रम an event
 *
 * @pdev - the sub-device that रेजिस्टरed the callback
 * @event - the event क्रम which to रेजिस्टर a callback
 */
व्योम dln2_unरेजिस्टर_event_cb(काष्ठा platक्रमm_device *pdev, u16 event);

/**
 * dln2_transfer - issue a DLN2 command and रुको क्रम a response and the
 * associated data
 *
 * @pdev - the sub-device which is issuing this transfer
 * @cmd - the command to be sent to the device
 * @obuf - the buffer to be sent to the device; it can be शून्य अगर the user
 *	करोesn't need to transmit data with this command
 * @obuf_len - the size of the buffer to be sent to the device
 * @ibuf - any data associated with the response will be copied here; it can be
 *	शून्य अगर the user करोesn't need the response data
 * @ibuf_len - must be initialized to the input buffer size; it will be modअगरied
 *	to indicate the actual data transferred;
 *
 * @वापस 0 क्रम success, negative value क्रम errors
 */
पूर्णांक dln2_transfer(काष्ठा platक्रमm_device *pdev, u16 cmd,
		  स्थिर व्योम *obuf, अचिन्हित obuf_len,
		  व्योम *ibuf, अचिन्हित *ibuf_len);

/**
 * dln2_transfer_rx - variant of @dln2_transfer() where TX buffer is not needed
 *
 * @pdev - the sub-device which is issuing this transfer
 * @cmd - the command to be sent to the device
 * @ibuf - any data associated with the response will be copied here; it can be
 *	शून्य अगर the user करोesn't need the response data
 * @ibuf_len - must be initialized to the input buffer size; it will be modअगरied
 *	to indicate the actual data transferred;
 *
 * @वापस 0 क्रम success, negative value क्रम errors
 */

अटल अंतरभूत पूर्णांक dln2_transfer_rx(काष्ठा platक्रमm_device *pdev, u16 cmd,
				   व्योम *ibuf, अचिन्हित *ibuf_len)
अणु
	वापस dln2_transfer(pdev, cmd, शून्य, 0, ibuf, ibuf_len);
पूर्ण

/**
 * dln2_transfer_tx - variant of @dln2_transfer() where RX buffer is not needed
 *
 * @pdev - the sub-device which is issuing this transfer
 * @cmd - the command to be sent to the device
 * @obuf - the buffer to be sent to the device; it can be शून्य अगर the
 *	user करोesn't need to transmit data with this command
 * @obuf_len - the size of the buffer to be sent to the device
 *
 * @वापस 0 क्रम success, negative value क्रम errors
 */
अटल अंतरभूत पूर्णांक dln2_transfer_tx(काष्ठा platक्रमm_device *pdev, u16 cmd,
				   स्थिर व्योम *obuf, अचिन्हित obuf_len)
अणु
	वापस dln2_transfer(pdev, cmd, obuf, obuf_len, शून्य, शून्य);
पूर्ण

#पूर्ण_अगर
