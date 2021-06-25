<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (C) B.A.T.M.A.N. contributors:
 *
 * Marek Lindner, Simon Wunderlich
 */

#अगर_अघोषित _NET_BATMAN_ADV_LOG_H_
#घोषणा _NET_BATMAN_ADV_LOG_H_

#समावेश "main.h"

#समावेश <linux/atomic.h>
#समावेश <linux/bitops.h>
#समावेश <linux/compiler.h>
#समावेश <linux/prपूर्णांकk.h>

#अगर_घोषित CONFIG_BATMAN_ADV_DEBUG

पूर्णांक batadv_debug_log_setup(काष्ठा batadv_priv *bat_priv);
व्योम batadv_debug_log_cleanup(काष्ठा batadv_priv *bat_priv);

#अन्यथा

अटल अंतरभूत पूर्णांक batadv_debug_log_setup(काष्ठा batadv_priv *bat_priv)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम batadv_debug_log_cleanup(काष्ठा batadv_priv *bat_priv)
अणु
पूर्ण

#पूर्ण_अगर

/**
 * क्रमागत batadv_dbg_level - available log levels
 */
क्रमागत batadv_dbg_level अणु
	/** @BATADV_DBG_BATMAN: OGM and TQ computations related messages */
	BATADV_DBG_BATMAN	= BIT(0),

	/** @BATADV_DBG_ROUTES: route added / changed / deleted */
	BATADV_DBG_ROUTES	= BIT(1),

	/** @BATADV_DBG_TT: translation table messages */
	BATADV_DBG_TT		= BIT(2),

	/** @BATADV_DBG_BLA: bridge loop aव्योमance messages */
	BATADV_DBG_BLA		= BIT(3),

	/** @BATADV_DBG_DAT: ARP snooping and DAT related messages */
	BATADV_DBG_DAT		= BIT(4),

	/** @BATADV_DBG_NC: network coding related messages */
	BATADV_DBG_NC		= BIT(5),

	/** @BATADV_DBG_MCAST: multicast related messages */
	BATADV_DBG_MCAST	= BIT(6),

	/** @BATADV_DBG_TP_METER: throughput meter messages */
	BATADV_DBG_TP_METER	= BIT(7),

	/** @BATADV_DBG_ALL: the जोड़ of all the above log levels */
	BATADV_DBG_ALL		= 255,
पूर्ण;

#अगर_घोषित CONFIG_BATMAN_ADV_DEBUG
पूर्णांक batadv_debug_log(काष्ठा batadv_priv *bat_priv, स्थिर अक्षर *fmt, ...)
__म_लिखो(2, 3);

/**
 * _batadv_dbg() - Store debug output with(out) rate limiting
 * @type: type of debug message
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @ratelimited: whether output should be rate limited
 * @fmt: क्रमmat string
 * @arg: variable arguments
 */
#घोषणा _batadv_dbg(type, bat_priv, ratelimited, fmt, arg...)		\
	करो अणु								\
		काष्ठा batadv_priv *__batpriv = (bat_priv);		\
		अगर (atomic_पढ़ो(&__batpriv->log_level) & (type) &&	\
		    (!(ratelimited) || net_ratelimit()))		\
			batadv_debug_log(__batpriv, fmt, ## arg);	\
	पूर्ण								\
	जबतक (0)
#अन्यथा /* !CONFIG_BATMAN_ADV_DEBUG */
__म_लिखो(4, 5)
अटल अंतरभूत व्योम _batadv_dbg(पूर्णांक type __always_unused,
			       काष्ठा batadv_priv *bat_priv __always_unused,
			       पूर्णांक ratelimited __always_unused,
			       स्थिर अक्षर *fmt __always_unused, ...)
अणु
पूर्ण
#पूर्ण_अगर

/**
 * batadv_dbg() - Store debug output without rate limiting
 * @type: type of debug message
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @arg: क्रमmat string and variable arguments
 */
#घोषणा batadv_dbg(type, bat_priv, arg...) \
	_batadv_dbg(type, bat_priv, 0, ## arg)

/**
 * batadv_dbg_ratelimited() - Store debug output with rate limiting
 * @type: type of debug message
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @arg: क्रमmat string and variable arguments
 */
#घोषणा batadv_dbg_ratelimited(type, bat_priv, arg...) \
	_batadv_dbg(type, bat_priv, 1, ## arg)

/**
 * batadv_info() - Store message in debug buffer and prपूर्णांक it to kmsg buffer
 * @net_dev: the soft पूर्णांकerface net device
 * @fmt: क्रमmat string
 * @arg: variable arguments
 */
#घोषणा batadv_info(net_dev, fmt, arg...)				\
	करो अणु								\
		काष्ठा net_device *_netdev = (net_dev);                 \
		काष्ठा batadv_priv *_batpriv = netdev_priv(_netdev);    \
		batadv_dbg(BATADV_DBG_ALL, _batpriv, fmt, ## arg);	\
		pr_info("%s: " fmt, _netdev->name, ## arg);		\
	पूर्ण जबतक (0)

/**
 * batadv_err() - Store error in debug buffer and prपूर्णांक it to kmsg buffer
 * @net_dev: the soft पूर्णांकerface net device
 * @fmt: क्रमmat string
 * @arg: variable arguments
 */
#घोषणा batadv_err(net_dev, fmt, arg...)				\
	करो अणु								\
		काष्ठा net_device *_netdev = (net_dev);                 \
		काष्ठा batadv_priv *_batpriv = netdev_priv(_netdev);    \
		batadv_dbg(BATADV_DBG_ALL, _batpriv, fmt, ## arg);	\
		pr_err("%s: " fmt, _netdev->name, ## arg);		\
	पूर्ण जबतक (0)

#पूर्ण_अगर /* _NET_BATMAN_ADV_LOG_H_ */
