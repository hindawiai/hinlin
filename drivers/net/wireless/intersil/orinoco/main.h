<शैली गुरु>
/* Exports from मुख्य to helper modules
 *
 * See copyright notice in मुख्य.c
 */
#अगर_अघोषित _ORINOCO_MAIN_H_
#घोषणा _ORINOCO_MAIN_H_

#समावेश <linux/ieee80211.h>
#समावेश "orinoco.h"

/********************************************************************/
/* Compile समय configuration and compatibility stuff               */
/********************************************************************/

/* We करो this this way to aव्योम अगरdefs in the actual code */
#अगर_घोषित WIRELESS_SPY
#घोषणा SPY_NUMBER(priv)	(priv->spy_data.spy_number)
#अन्यथा
#घोषणा SPY_NUMBER(priv)	0
#पूर्ण_अगर /* WIRELESS_SPY */

/********************************************************************/

/* Export module parameter */
बाह्य पूर्णांक क्रमce_monitor;

/* Forward declarations */
काष्ठा net_device;
काष्ठा work_काष्ठा;

व्योम set_port_type(काष्ठा orinoco_निजी *priv);
पूर्णांक orinoco_commit(काष्ठा orinoco_निजी *priv);
व्योम orinoco_reset(काष्ठा work_काष्ठा *work);

/* Inक्रमmation element helpers - find a home क्रम these... */
#घोषणा WPA_OUI_TYPE	"\x00\x50\xF2\x01"
#घोषणा WPA_SELECTOR_LEN 4
अटल अंतरभूत u8 *orinoco_get_wpa_ie(u8 *data, माप_प्रकार len)
अणु
	u8 *p = data;
	जबतक ((p + 2 + WPA_SELECTOR_LEN) < (data + len)) अणु
		अगर ((p[0] == WLAN_EID_VENDOR_SPECIFIC) &&
		    (स_भेद(&p[2], WPA_OUI_TYPE, WPA_SELECTOR_LEN) == 0))
			वापस p;
		p += p[1] + 2;
	पूर्ण
	वापस शून्य;
पूर्ण

#पूर्ण_अगर /* _ORINOCO_MAIN_H_ */
