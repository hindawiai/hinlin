<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _SPARC64_LDC_H
#घोषणा _SPARC64_LDC_H

#समावेश <यंत्र/hypervisor.h>

बाह्य पूर्णांक lकरोm_करोमुख्यing_enabled;
व्योम lकरोm_set_var(स्थिर अक्षर *var, स्थिर अक्षर *value);
व्योम lकरोm_reboot(स्थिर अक्षर *boot_command);
व्योम lकरोm_घातer_off(व्योम);

/* The event handler will be evoked when link state changes
 * or data becomes available on the receive side.
 *
 * For non-RAW links, अगर the LDC_EVENT_RESET event arrives the
 * driver should reset all of it's पूर्णांकernal state and reinvoke
 * ldc_connect() to try and bring the link up again.
 *
 * For RAW links, ldc_connect() is not used.  Instead the driver
 * just रुकोs क्रम the LDC_EVENT_UP event.
 */
काष्ठा ldc_channel_config अणु
	व्योम (*event)(व्योम *arg, पूर्णांक event);

	u32			mtu;
	अचिन्हित पूर्णांक		rx_irq;
	अचिन्हित पूर्णांक		tx_irq;
	u8			mode;
#घोषणा LDC_MODE_RAW		0x00
#घोषणा LDC_MODE_UNRELIABLE	0x01
#घोषणा LDC_MODE_RESERVED	0x02
#घोषणा LDC_MODE_STREAM		0x03

	u8			debug;
#घोषणा LDC_DEBUG_HS		0x01
#घोषणा LDC_DEBUG_STATE		0x02
#घोषणा LDC_DEBUG_RX		0x04
#घोषणा LDC_DEBUG_TX		0x08
#घोषणा LDC_DEBUG_DATA		0x10
पूर्ण;

#घोषणा LDC_EVENT_RESET		0x01
#घोषणा LDC_EVENT_UP		0x02
#घोषणा LDC_EVENT_DATA_READY	0x04

#घोषणा LDC_STATE_INVALID	0x00
#घोषणा LDC_STATE_INIT		0x01
#घोषणा LDC_STATE_BOUND		0x02
#घोषणा LDC_STATE_READY		0x03
#घोषणा LDC_STATE_CONNECTED	0x04

#घोषणा	LDC_PACKET_SIZE		64

काष्ठा ldc_channel;

/* Allocate state क्रम a channel.  */
काष्ठा ldc_channel *ldc_alloc(अचिन्हित दीर्घ id,
			      स्थिर काष्ठा ldc_channel_config *cfgp,
			      व्योम *event_arg,
			      स्थिर अक्षर *name);

/* Shut करोwn and मुक्त state क्रम a channel.  */
व्योम ldc_मुक्त(काष्ठा ldc_channel *lp);

/* Register TX and RX queues of the link with the hypervisor.  */
पूर्णांक ldc_bind(काष्ठा ldc_channel *lp);
व्योम ldc_unbind(काष्ठा ldc_channel *lp);

/* For non-RAW protocols we need to complete a handshake beक्रमe
 * communication can proceed.  ldc_connect() करोes that, अगर the
 * handshake completes successfully, an LDC_EVENT_UP event will
 * be sent up to the driver.
 */
पूर्णांक ldc_connect(काष्ठा ldc_channel *lp);
पूर्णांक ldc_disconnect(काष्ठा ldc_channel *lp);

पूर्णांक ldc_state(काष्ठा ldc_channel *lp);
व्योम ldc_set_state(काष्ठा ldc_channel *lp, u8 state);
पूर्णांक ldc_mode(काष्ठा ldc_channel *lp);
व्योम __ldc_prपूर्णांक(काष्ठा ldc_channel *lp, स्थिर अक्षर *caller);
पूर्णांक ldc_rx_reset(काष्ठा ldc_channel *lp);

#घोषणा	ldc_prपूर्णांक(chan)	__ldc_prपूर्णांक(chan, __func__)

/* Read and ग_लिखो operations.  Only valid when the link is up.  */
पूर्णांक ldc_ग_लिखो(काष्ठा ldc_channel *lp, स्थिर व्योम *buf,
	      अचिन्हित पूर्णांक size);
पूर्णांक ldc_पढ़ो(काष्ठा ldc_channel *lp, व्योम *buf, अचिन्हित पूर्णांक size);

#घोषणा LDC_MAP_SHADOW	0x01
#घोषणा LDC_MAP_सूचीECT	0x02
#घोषणा LDC_MAP_IO	0x04
#घोषणा LDC_MAP_R	0x08
#घोषणा LDC_MAP_W	0x10
#घोषणा LDC_MAP_X	0x20
#घोषणा LDC_MAP_RW	(LDC_MAP_R | LDC_MAP_W)
#घोषणा LDC_MAP_RWX	(LDC_MAP_R | LDC_MAP_W | LDC_MAP_X)
#घोषणा LDC_MAP_ALL	0x03f

काष्ठा ldc_trans_cookie अणु
	u64			cookie_addr;
	u64			cookie_size;
पूर्ण;

काष्ठा scatterlist;
पूर्णांक ldc_map_sg(काष्ठा ldc_channel *lp,
	       काष्ठा scatterlist *sg, पूर्णांक num_sg,
	       काष्ठा ldc_trans_cookie *cookies, पूर्णांक ncookies,
	       अचिन्हित पूर्णांक map_perm);

पूर्णांक ldc_map_single(काष्ठा ldc_channel *lp,
		   व्योम *buf, अचिन्हित पूर्णांक len,
		   काष्ठा ldc_trans_cookie *cookies, पूर्णांक ncookies,
		   अचिन्हित पूर्णांक map_perm);

व्योम ldc_unmap(काष्ठा ldc_channel *lp, काष्ठा ldc_trans_cookie *cookies,
	       पूर्णांक ncookies);

पूर्णांक ldc_copy(काष्ठा ldc_channel *lp, पूर्णांक copy_dir,
	     व्योम *buf, अचिन्हित पूर्णांक len, अचिन्हित दीर्घ offset,
	     काष्ठा ldc_trans_cookie *cookies, पूर्णांक ncookies);

अटल अंतरभूत पूर्णांक ldc_get_dring_entry(काष्ठा ldc_channel *lp,
				      व्योम *buf, अचिन्हित पूर्णांक len,
				      अचिन्हित दीर्घ offset,
				      काष्ठा ldc_trans_cookie *cookies,
				      पूर्णांक ncookies)
अणु
	वापस ldc_copy(lp, LDC_COPY_IN, buf, len, offset, cookies, ncookies);
पूर्ण

अटल अंतरभूत पूर्णांक ldc_put_dring_entry(काष्ठा ldc_channel *lp,
				      व्योम *buf, अचिन्हित पूर्णांक len,
				      अचिन्हित दीर्घ offset,
				      काष्ठा ldc_trans_cookie *cookies,
				      पूर्णांक ncookies)
अणु
	वापस ldc_copy(lp, LDC_COPY_OUT, buf, len, offset, cookies, ncookies);
पूर्ण

व्योम *ldc_alloc_exp_dring(काष्ठा ldc_channel *lp, अचिन्हित पूर्णांक len,
			  काष्ठा ldc_trans_cookie *cookies,
			  पूर्णांक *ncookies, अचिन्हित पूर्णांक map_perm);

व्योम ldc_मुक्त_exp_dring(काष्ठा ldc_channel *lp, व्योम *buf,
		        अचिन्हित पूर्णांक len,
		        काष्ठा ldc_trans_cookie *cookies, पूर्णांक ncookies);

#पूर्ण_अगर /* _SPARC64_LDC_H */
