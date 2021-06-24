<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/******************************************************************************
 *
 * Copyright(c) 2003 - 2014 Intel Corporation. All rights reserved.
 * Copyright(c) 2018 - 2020 Intel Corporation
 *
 * Portions of this file are derived from the ipw3945 project.
 *
 * Contact Inक्रमmation:
 *  Intel Linux Wireless <linuxwअगरi@पूर्णांकel.com>
 * Intel Corporation, 5200 N.E. Elam Young Parkway, Hillsboro, OR 97124-6497
 *
 *****************************************************************************/

#अगर_अघोषित __iwl_debug_h__
#घोषणा __iwl_debug_h__

#समावेश "iwl-modparams.h"


अटल अंतरभूत bool iwl_have_debug_level(u32 level)
अणु
#अगर_घोषित CONFIG_IWLWIFI_DEBUG
	वापस iwlwअगरi_mod_params.debug_level & level;
#अन्यथा
	वापस false;
#पूर्ण_अगर
पूर्ण

काष्ठा device;
व्योम __iwl_err(काष्ठा device *dev, bool rfसमाप्त_prefix, bool only_trace,
		स्थिर अक्षर *fmt, ...) __म_लिखो(4, 5);
व्योम __iwl_warn(काष्ठा device *dev, स्थिर अक्षर *fmt, ...) __म_लिखो(2, 3);
व्योम __iwl_info(काष्ठा device *dev, स्थिर अक्षर *fmt, ...) __म_लिखो(2, 3);
व्योम __iwl_crit(काष्ठा device *dev, स्थिर अक्षर *fmt, ...) __म_लिखो(2, 3);

/* not all compilers can evaluate म_माप() at compile समय, so use माप() */
#घोषणा CHECK_FOR_NEWLINE(f) BUILD_BUG_ON(f[माप(f) - 2] != '\n')

/* No matter what is m (priv, bus, trans), this will work */
#घोषणा IWL_ERR_DEV(d, f, a...)						\
	करो अणु								\
		CHECK_FOR_NEWLINE(f);					\
		__iwl_err((d), false, false, f, ## a);			\
	पूर्ण जबतक (0)
#घोषणा IWL_ERR(m, f, a...)						\
	IWL_ERR_DEV((m)->dev, f, ## a)
#घोषणा IWL_WARN(m, f, a...)						\
	करो अणु								\
		CHECK_FOR_NEWLINE(f);					\
		__iwl_warn((m)->dev, f, ## a);				\
	पूर्ण जबतक (0)
#घोषणा IWL_INFO(m, f, a...)						\
	करो अणु								\
		CHECK_FOR_NEWLINE(f);					\
		__iwl_info((m)->dev, f, ## a);				\
	पूर्ण जबतक (0)
#घोषणा IWL_CRIT(m, f, a...)						\
	करो अणु								\
		CHECK_FOR_NEWLINE(f);					\
		__iwl_crit((m)->dev, f, ## a);				\
	पूर्ण जबतक (0)

#अगर defined(CONFIG_IWLWIFI_DEBUG) || defined(CONFIG_IWLWIFI_DEVICE_TRACING)
व्योम __iwl_dbg(काष्ठा device *dev,
	       u32 level, bool limit, स्थिर अक्षर *function,
	       स्थिर अक्षर *fmt, ...) __म_लिखो(5, 6);
#अन्यथा
__म_लिखो(5, 6) अटल अंतरभूत व्योम
__iwl_dbg(काष्ठा device *dev,
	  u32 level, bool limit, स्थिर अक्षर *function,
	  स्थिर अक्षर *fmt, ...)
अणुपूर्ण
#पूर्ण_अगर

#घोषणा iwl_prपूर्णांक_hex_error(m, p, len)					\
करो अणु									\
	prपूर्णांक_hex_dump(KERN_ERR, "iwl data: ",				\
		       DUMP_PREFIX_OFFSET, 16, 1, p, len, 1);		\
पूर्ण जबतक (0)

#घोषणा __IWL_DEBUG_DEV(dev, level, limit, fmt, args...)		\
	करो अणु								\
		CHECK_FOR_NEWLINE(fmt);					\
		__iwl_dbg(dev, level, limit, __func__, fmt, ##args);	\
	पूर्ण जबतक (0)
#घोषणा IWL_DEBUG(m, level, fmt, args...)				\
	__IWL_DEBUG_DEV((m)->dev, level, false, fmt, ##args)
#घोषणा IWL_DEBUG_DEV(dev, level, fmt, args...)				\
	__IWL_DEBUG_DEV(dev, level, false, fmt, ##args)
#घोषणा IWL_DEBUG_LIMIT(m, level, fmt, args...)				\
	__IWL_DEBUG_DEV((m)->dev, level, true, fmt, ##args)

#अगर_घोषित CONFIG_IWLWIFI_DEBUG
#घोषणा iwl_prपूर्णांक_hex_dump(m, level, p, len)				\
करो अणु                                            			\
	अगर (iwl_have_debug_level(level))				\
		prपूर्णांक_hex_dump(KERN_DEBUG, "iwl data: ",		\
			       DUMP_PREFIX_OFFSET, 16, 1, p, len, 1);	\
पूर्ण जबतक (0)
#अन्यथा
#घोषणा iwl_prपूर्णांक_hex_dump(m, level, p, len)
#पूर्ण_अगर				/* CONFIG_IWLWIFI_DEBUG */

/*
 * To use the debug प्रणाली:
 *
 * If you are defining a new debug classअगरication, simply add it to the #घोषणा
 * list here in the क्रमm of
 *
 * #घोषणा IWL_DL_xxxx VALUE
 *
 * where xxxx should be the name of the classअगरication (क्रम example, WEP).
 *
 * You then need to either add a IWL_xxxx_DEBUG() macro definition क्रम your
 * classअगरication, or use IWL_DEBUG(IWL_DL_xxxx, ...) whenever you want
 * to send output to that classअगरication.
 *
 * The active debug levels can be accessed via files
 *
 *	/sys/module/iwlwअगरi/parameters/debug
 * when CONFIG_IWLWIFI_DEBUG=y.
 *
 *	/sys/kernel/debug/phy0/iwlwअगरi/debug/debug_level
 * when CONFIG_IWLWIFI_DEBUGFS=y.
 *
 */

/* 0x0000000F - 0x00000001 */
#घोषणा IWL_DL_INFO		0x00000001
#घोषणा IWL_DL_MAC80211		0x00000002
#घोषणा IWL_DL_HCMD		0x00000004
#घोषणा IWL_DL_TDLS		0x00000008
/* 0x000000F0 - 0x00000010 */
#घोषणा IWL_DL_QUOTA		0x00000010
#घोषणा IWL_DL_TE		0x00000020
#घोषणा IWL_DL_EEPROM		0x00000040
#घोषणा IWL_DL_RADIO		0x00000080
/* 0x00000F00 - 0x00000100 */
#घोषणा IWL_DL_POWER		0x00000100
#घोषणा IWL_DL_TEMP		0x00000200
#घोषणा IWL_DL_WOWLAN		0x00000400
#घोषणा IWL_DL_SCAN		0x00000800
/* 0x0000F000 - 0x00001000 */
#घोषणा IWL_DL_ASSOC		0x00001000
#घोषणा IWL_DL_DROP		0x00002000
#घोषणा IWL_DL_LAR		0x00004000
#घोषणा IWL_DL_COEX		0x00008000
/* 0x000F0000 - 0x00010000 */
#घोषणा IWL_DL_FW		0x00010000
#घोषणा IWL_DL_RF_KILL		0x00020000
#घोषणा IWL_DL_TPT		0x00040000
/* 0x00F00000 - 0x00100000 */
#घोषणा IWL_DL_RATE		0x00100000
#घोषणा IWL_DL_CALIB		0x00200000
#घोषणा IWL_DL_WEP		0x00400000
#घोषणा IWL_DL_TX		0x00800000
/* 0x0F000000 - 0x01000000 */
#घोषणा IWL_DL_RX		0x01000000
#घोषणा IWL_DL_ISR		0x02000000
#घोषणा IWL_DL_HT		0x04000000
#घोषणा IWL_DL_EXTERNAL		0x08000000
/* 0xF0000000 - 0x10000000 */
#घोषणा IWL_DL_11H		0x10000000
#घोषणा IWL_DL_STATS		0x20000000
#घोषणा IWL_DL_TX_REPLY		0x40000000
#घोषणा IWL_DL_TX_QUEUES	0x80000000

#घोषणा IWL_DEBUG_INFO(p, f, a...)	IWL_DEBUG(p, IWL_DL_INFO, f, ## a)
#घोषणा IWL_DEBUG_TDLS(p, f, a...)	IWL_DEBUG(p, IWL_DL_TDLS, f, ## a)
#घोषणा IWL_DEBUG_MAC80211(p, f, a...)	IWL_DEBUG(p, IWL_DL_MAC80211, f, ## a)
#घोषणा IWL_DEBUG_EXTERNAL(p, f, a...)	IWL_DEBUG(p, IWL_DL_EXTERNAL, f, ## a)
#घोषणा IWL_DEBUG_TEMP(p, f, a...)	IWL_DEBUG(p, IWL_DL_TEMP, f, ## a)
#घोषणा IWL_DEBUG_SCAN(p, f, a...)	IWL_DEBUG(p, IWL_DL_SCAN, f, ## a)
#घोषणा IWL_DEBUG_RX(p, f, a...)	IWL_DEBUG(p, IWL_DL_RX, f, ## a)
#घोषणा IWL_DEBUG_TX(p, f, a...)	IWL_DEBUG(p, IWL_DL_TX, f, ## a)
#घोषणा IWL_DEBUG_ISR(p, f, a...)	IWL_DEBUG(p, IWL_DL_ISR, f, ## a)
#घोषणा IWL_DEBUG_WEP(p, f, a...)	IWL_DEBUG(p, IWL_DL_WEP, f, ## a)
#घोषणा IWL_DEBUG_HC(p, f, a...)	IWL_DEBUG(p, IWL_DL_HCMD, f, ## a)
#घोषणा IWL_DEBUG_QUOTA(p, f, a...)	IWL_DEBUG(p, IWL_DL_QUOTA, f, ## a)
#घोषणा IWL_DEBUG_TE(p, f, a...)	IWL_DEBUG(p, IWL_DL_TE, f, ## a)
#घोषणा IWL_DEBUG_EEPROM(d, f, a...)	IWL_DEBUG_DEV(d, IWL_DL_EEPROM, f, ## a)
#घोषणा IWL_DEBUG_CALIB(p, f, a...)	IWL_DEBUG(p, IWL_DL_CALIB, f, ## a)
#घोषणा IWL_DEBUG_FW(p, f, a...)	IWL_DEBUG(p, IWL_DL_FW, f, ## a)
#घोषणा IWL_DEBUG_RF_KILL(p, f, a...)	IWL_DEBUG(p, IWL_DL_RF_KILL, f, ## a)
#घोषणा IWL_DEBUG_DROP(p, f, a...)	IWL_DEBUG(p, IWL_DL_DROP, f, ## a)
#घोषणा IWL_DEBUG_DROP_LIMIT(p, f, a...)	\
		IWL_DEBUG_LIMIT(p, IWL_DL_DROP, f, ## a)
#घोषणा IWL_DEBUG_COEX(p, f, a...)	IWL_DEBUG(p, IWL_DL_COEX, f, ## a)
#घोषणा IWL_DEBUG_RATE(p, f, a...)	IWL_DEBUG(p, IWL_DL_RATE, f, ## a)
#घोषणा IWL_DEBUG_RATE_LIMIT(p, f, a...)	\
		IWL_DEBUG_LIMIT(p, IWL_DL_RATE, f, ## a)
#घोषणा IWL_DEBUG_ASSOC(p, f, a...)	\
		IWL_DEBUG(p, IWL_DL_ASSOC | IWL_DL_INFO, f, ## a)
#घोषणा IWL_DEBUG_ASSOC_LIMIT(p, f, a...)	\
		IWL_DEBUG_LIMIT(p, IWL_DL_ASSOC | IWL_DL_INFO, f, ## a)
#घोषणा IWL_DEBUG_HT(p, f, a...)	IWL_DEBUG(p, IWL_DL_HT, f, ## a)
#घोषणा IWL_DEBUG_STATS(p, f, a...)	IWL_DEBUG(p, IWL_DL_STATS, f, ## a)
#घोषणा IWL_DEBUG_STATS_LIMIT(p, f, a...)	\
		IWL_DEBUG_LIMIT(p, IWL_DL_STATS, f, ## a)
#घोषणा IWL_DEBUG_TX_REPLY(p, f, a...)	IWL_DEBUG(p, IWL_DL_TX_REPLY, f, ## a)
#घोषणा IWL_DEBUG_TX_QUEUES(p, f, a...)	IWL_DEBUG(p, IWL_DL_TX_QUEUES, f, ## a)
#घोषणा IWL_DEBUG_RADIO(p, f, a...)	IWL_DEBUG(p, IWL_DL_RADIO, f, ## a)
#घोषणा IWL_DEBUG_DEV_RADIO(p, f, a...)	IWL_DEBUG_DEV(p, IWL_DL_RADIO, f, ## a)
#घोषणा IWL_DEBUG_POWER(p, f, a...)	IWL_DEBUG(p, IWL_DL_POWER, f, ## a)
#घोषणा IWL_DEBUG_11H(p, f, a...)	IWL_DEBUG(p, IWL_DL_11H, f, ## a)
#घोषणा IWL_DEBUG_TPT(p, f, a...)	IWL_DEBUG(p, IWL_DL_TPT, f, ## a)
#घोषणा IWL_DEBUG_WOWLAN(p, f, a...)	IWL_DEBUG(p, IWL_DL_WOWLAN, f, ## a)
#घोषणा IWL_DEBUG_LAR(p, f, a...)	IWL_DEBUG(p, IWL_DL_LAR, f, ## a)
#घोषणा IWL_DEBUG_FW_INFO(p, f, a...)		\
		IWL_DEBUG(p, IWL_DL_INFO | IWL_DL_FW, f, ## a)

#पूर्ण_अगर
