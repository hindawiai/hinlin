<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_OLPC_EC_H
#घोषणा _LINUX_OLPC_EC_H

#समावेश <linux/bits.h>

/* XO-1 EC commands */
#घोषणा EC_FIRMWARE_REV			0x08
#घोषणा EC_WRITE_SCI_MASK		0x1b
#घोषणा EC_WAKE_UP_WLAN			0x24
#घोषणा EC_WLAN_LEAVE_RESET		0x25
#घोषणा EC_DCON_POWER_MODE		0x26
#घोषणा EC_READ_EB_MODE			0x2a
#घोषणा EC_SET_SCI_INHIBIT		0x32
#घोषणा EC_SET_SCI_INHIBIT_RELEASE	0x34
#घोषणा EC_WLAN_ENTER_RESET		0x35
#घोषणा EC_WRITE_EXT_SCI_MASK		0x38
#घोषणा EC_SCI_QUERY			0x84
#घोषणा EC_EXT_SCI_QUERY		0x85

/* SCI source values */
#घोषणा EC_SCI_SRC_GAME         BIT(0)
#घोषणा EC_SCI_SRC_BATTERY      BIT(1)
#घोषणा EC_SCI_SRC_BATSOC       BIT(2)
#घोषणा EC_SCI_SRC_BATERR       BIT(3)
#घोषणा EC_SCI_SRC_EBOOK        BIT(4)    /* XO-1 only */
#घोषणा EC_SCI_SRC_WLAN         BIT(5)    /* XO-1 only */
#घोषणा EC_SCI_SRC_ACPWR        BIT(6)
#घोषणा EC_SCI_SRC_BATCRIT      BIT(7)
#घोषणा EC_SCI_SRC_GPWAKE       BIT(8)   /* XO-1.5 only */
#घोषणा EC_SCI_SRC_ALL          GENMASK(8, 0)

काष्ठा platक्रमm_device;

काष्ठा olpc_ec_driver अणु
	पूर्णांक (*suspend)(काष्ठा platक्रमm_device *);
	पूर्णांक (*resume)(काष्ठा platक्रमm_device *);

	पूर्णांक (*ec_cmd)(u8, u8 *, माप_प्रकार, u8 *, माप_प्रकार, व्योम *);

	bool wakeup_available;
पूर्ण;

#अगर_घोषित CONFIG_OLPC_EC

बाह्य व्योम olpc_ec_driver_रेजिस्टर(काष्ठा olpc_ec_driver *drv, व्योम *arg);

बाह्य पूर्णांक olpc_ec_cmd(u8 cmd, u8 *inbuf, माप_प्रकार inlen, u8 *outbuf,
		माप_प्रकार outlen);

बाह्य व्योम olpc_ec_wakeup_set(u16 value);
बाह्य व्योम olpc_ec_wakeup_clear(u16 value);

बाह्य पूर्णांक olpc_ec_mask_ग_लिखो(u16 bits);
बाह्य पूर्णांक olpc_ec_sci_query(u16 *sci_value);

बाह्य bool olpc_ec_wakeup_available(व्योम);

#अन्यथा

अटल अंतरभूत पूर्णांक olpc_ec_cmd(u8 cmd, u8 *inbuf, माप_प्रकार inlen, u8 *outbuf,
		माप_प्रकार outlen) अणु वापस -ENODEV; पूर्ण

अटल अंतरभूत व्योम olpc_ec_wakeup_set(u16 value) अणु पूर्ण
अटल अंतरभूत व्योम olpc_ec_wakeup_clear(u16 value) अणु पूर्ण

अटल अंतरभूत bool olpc_ec_wakeup_available(व्योम)
अणु
	वापस false;
पूर्ण

#पूर्ण_अगर /* CONFIG_OLPC_EC */

#पूर्ण_अगर /* _LINUX_OLPC_EC_H */
