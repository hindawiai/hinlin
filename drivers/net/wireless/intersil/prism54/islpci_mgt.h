<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  Copyright (C) 2002 Intersil Americas Inc.
 *  Copyright (C) 2003 Luis R. Rodriguez <mcgrof@ruslug.rutgers.edu>
 */

#अगर_अघोषित _ISLPCI_MGT_H
#घोषणा _ISLPCI_MGT_H

#समावेश <linux/wireless.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/slab.h>

/*
 *  Function definitions
 */

#घोषणा K_DEBUG(f, m, args...) करो अणु अगर(f & m) prपूर्णांकk(KERN_DEBUG args); पूर्ण जबतक(0)
#घोषणा DEBUG(f, args...) K_DEBUG(f, pc_debug, args)

बाह्य पूर्णांक pc_debug;
#घोषणा init_wds 0	/* help compiler optimize away dead code */


/* General driver definitions */
#घोषणा PCIDEVICE_LATENCY_TIMER_MIN		0x40
#घोषणा PCIDEVICE_LATENCY_TIMER_VAL		0x50

/* Debugging verbose definitions */
#घोषणा SHOW_NOTHING                            0x00	/* overrules everything */
#घोषणा SHOW_ANYTHING                           0xFF
#घोषणा SHOW_ERROR_MESSAGES                     0x01
#घोषणा SHOW_TRAPS                              0x02
#घोषणा SHOW_FUNCTION_CALLS                     0x04
#घोषणा SHOW_TRACING                            0x08
#घोषणा SHOW_QUEUE_INDEXES                      0x10
#घोषणा SHOW_PIMFOR_FRAMES                      0x20
#घोषणा SHOW_BUFFER_CONTENTS                    0x40
#घोषणा VERBOSE                                 0x01

/* Default card definitions */
#घोषणा CARD_DEFAULT_CHANNEL                    6
#घोषणा CARD_DEFAULT_MODE                       INL_MODE_CLIENT
#घोषणा CARD_DEFAULT_IW_MODE			IW_MODE_INFRA
#घोषणा CARD_DEFAULT_BSSTYPE                    DOT11_BSSTYPE_INFRA
#घोषणा CARD_DEFAULT_CLIENT_SSID		""
#घोषणा CARD_DEFAULT_AP_SSID			"default"
#घोषणा CARD_DEFAULT_KEY1                       "default_key_1"
#घोषणा CARD_DEFAULT_KEY2                       "default_key_2"
#घोषणा CARD_DEFAULT_KEY3                       "default_key_3"
#घोषणा CARD_DEFAULT_KEY4                       "default_key_4"
#घोषणा CARD_DEFAULT_WEP                        0
#घोषणा CARD_DEFAULT_FILTER                     0
#घोषणा CARD_DEFAULT_WDS                        0
#घोषणा	CARD_DEFAULT_AUTHEN                     DOT11_AUTH_OS
#घोषणा	CARD_DEFAULT_DOT1X			0
#घोषणा CARD_DEFAULT_MLME_MODE			DOT11_MLME_AUTO
#घोषणा CARD_DEFAULT_CONFORMANCE                OID_INL_CONFORMANCE_NONE
#घोषणा CARD_DEFAULT_PROखाता			DOT11_PROखाता_MIXED_G_WIFI
#घोषणा CARD_DEFAULT_MAXFRAMEBURST		DOT11_MAXFRAMEBURST_MIXED_SAFE

/* PIMFOR package definitions */
#घोषणा PIMFOR_ETHERTYPE                        0x8828
#घोषणा PIMFOR_HEADER_SIZE                      12
#घोषणा PIMFOR_VERSION                          1
#घोषणा PIMFOR_OP_GET                           0
#घोषणा PIMFOR_OP_SET                           1
#घोषणा PIMFOR_OP_RESPONSE                      2
#घोषणा PIMFOR_OP_ERROR                         3
#घोषणा PIMFOR_OP_TRAP                          4
#घोषणा PIMFOR_OP_RESERVED                      5	/* till 255 */
#घोषणा PIMFOR_DEV_ID_MHLI_MIB                  0
#घोषणा PIMFOR_FLAG_APPLIC_ORIGIN               0x01
#घोषणा PIMFOR_FLAG_LITTLE_ENDIAN               0x02

व्योम display_buffer(अक्षर *, पूर्णांक);

/*
 *  Type definition section
 *
 *  the काष्ठाure defines only the header allowing copyless
 *  frame handling
 */
प्रकार काष्ठा अणु
	u8 version;
	u8 operation;
	u32 oid;
	u8 device_id;
	u8 flags;
	u32 length;
पूर्ण __packed
pimक्रम_header_t;

/* A received and पूर्णांकerrupt-processed management frame, either क्रम
 * schedule_work(prism54_process_trap) or क्रम priv->mgmt_received,
 * processed by islpci_mgt_transaction(). */
काष्ठा islpci_mgmtframe अणु
	काष्ठा net_device *ndev;      /* poपूर्णांकer to network device */
	pimक्रम_header_t *header;      /* payload header, poपूर्णांकs पूर्णांकo buf */
	व्योम *data;		      /* payload ex header, poपूर्णांकs पूर्णांकo buf */
        काष्ठा work_काष्ठा ws;	      /* argument क्रम schedule_work() */
	अक्षर buf[];		      /* fragment buffer */
पूर्ण;

पूर्णांक
islpci_mgt_receive(काष्ठा net_device *ndev);

पूर्णांक
islpci_mgmt_rx_fill(काष्ठा net_device *ndev);

व्योम
islpci_mgt_cleanup_transmit(काष्ठा net_device *ndev);

पूर्णांक
islpci_mgt_transaction(काष्ठा net_device *ndev,
                       पूर्णांक operation, अचिन्हित दीर्घ oid,
		       व्योम *senddata, पूर्णांक sendlen,
		       काष्ठा islpci_mgmtframe **recvframe);

अटल अंतरभूत व्योम
islpci_mgt_release(काष्ठा islpci_mgmtframe *frame)
अणु
        kमुक्त(frame);
पूर्ण

#पूर्ण_अगर				/* _ISLPCI_MGT_H */
