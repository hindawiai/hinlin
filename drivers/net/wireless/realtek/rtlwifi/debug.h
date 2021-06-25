<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright(c) 2009-2012  Realtek Corporation.*/

#अगर_अघोषित __RTL_DEBUG_H__
#घोषणा __RTL_DEBUG_H__

/*--------------------------------------------------------------
			Debug level
--------------------------------------------------------------*/
/*
 *Fatal bug.
 *For example, Tx/Rx/IO locked up,
 *memory access violation,
 *resource allocation failed,
 *unexpected HW behavior, HW BUG
 *and so on.
 */
/*#घोषणा DBG_EMERG			0 */

/*
 *Abnormal, rare, or unexpeted हालs.
 *For example, Packet/IO Ctl canceled,
 *device suprisely unहटाओd and so on.
 */
#घोषणा	DBG_WARNING			2

/*
 *Normal हाल driver developer should
 *खोलो, we can see link status like
 *assoc/AddBA/DHCP/adapter start and
 *so on basic and useful infromations.
 */
#घोषणा DBG_DMESG			3

/*
 *Normal हाल with useful inक्रमmation
 *about current SW or HW state.
 *For example, Tx/Rx descriptor to fill,
 *Tx/Rx descriptor completed status,
 *SW protocol state change, dynamic
 *mechanism state change and so on.
 */
#घोषणा DBG_LOUD			4

/*
 *Normal हाल with detail execution
 *flow or inक्रमmation.
 */
#घोषणा	DBG_TRACE			5

/*--------------------------------------------------------------
		Define the rt_trace components
--------------------------------------------------------------*/
#घोषणा COMP_ERR			BIT(0)
#घोषणा COMP_FW				BIT(1)
#घोषणा COMP_INIT			BIT(2)	/*For init/deinit */
#घोषणा COMP_RECV			BIT(3)	/*For Rx. */
#घोषणा COMP_SEND			BIT(4)	/*For Tx. */
#घोषणा COMP_MLME			BIT(5)	/*For MLME. */
#घोषणा COMP_SCAN			BIT(6)	/*For Scan. */
#घोषणा COMP_INTR			BIT(7)	/*For पूर्णांकerrupt Related. */
#घोषणा COMP_LED			BIT(8)	/*For LED. */
#घोषणा COMP_SEC			BIT(9)	/*For sec. */
#घोषणा COMP_BEACON			BIT(10)	/*For beacon. */
#घोषणा COMP_RATE			BIT(11)	/*For rate. */
#घोषणा COMP_RXDESC			BIT(12)	/*For rx desc. */
#घोषणा COMP_DIG			BIT(13)	/*For DIG */
#घोषणा COMP_TXAGC			BIT(14)	/*For Tx घातer */
#घोषणा COMP_HIPWR			BIT(15)	/*For High Power Mechanism */
#घोषणा COMP_POWER			BIT(16)	/*For lps/ips/aspm. */
#घोषणा COMP_POWER_TRACKING	BIT(17)	/*For TX POWER TRACKING */
#घोषणा COMP_BB_POWERSAVING	BIT(18)
#घोषणा COMP_SWAS			BIT(19)	/*For SW Antenna Switch */
#घोषणा COMP_RF				BIT(20)	/*For RF. */
#घोषणा COMP_TURBO			BIT(21)	/*For EDCA TURBO. */
#घोषणा COMP_RATR			BIT(22)
#घोषणा COMP_CMD			BIT(23)
#घोषणा COMP_EFUSE			BIT(24)
#घोषणा COMP_QOS			BIT(25)
#घोषणा COMP_MAC80211		BIT(26)
#घोषणा COMP_REGD			BIT(27)
#घोषणा COMP_CHAN			BIT(28)
#घोषणा COMP_USB			BIT(29)
#घोषणा COMP_EASY_CONCURRENT	COMP_USB /* reuse of this bit is OK */
#घोषणा COMP_BT_COEXIST			BIT(30)
#घोषणा COMP_IQK			BIT(31)
#घोषणा COMP_TX_REPORT			BIT_ULL(32)

/*--------------------------------------------------------------
		Define the rt_prपूर्णांक components
--------------------------------------------------------------*/
/* Define EEPROM and EFUSE  check module bit*/
#घोषणा EEPROM_W			BIT(0)
#घोषणा EFUSE_PG			BIT(1)
#घोषणा EFUSE_READ_ALL			BIT(2)

/* Define init check क्रम module bit*/
#घोषणा	INIT_EEPROM			BIT(0)
#घोषणा	INIT_TXPOWER			BIT(1)
#घोषणा	INIT_IQK			BIT(2)
#घोषणा	INIT_RF				BIT(3)

/* Define PHY-BB/RF/MAC check module bit */
#घोषणा	PHY_BBR				BIT(0)
#घोषणा	PHY_BBW				BIT(1)
#घोषणा	PHY_RFR				BIT(2)
#घोषणा	PHY_RFW				BIT(3)
#घोषणा	PHY_MACR			BIT(4)
#घोषणा	PHY_MACW			BIT(5)
#घोषणा	PHY_ALLR			BIT(6)
#घोषणा	PHY_ALLW			BIT(7)
#घोषणा	PHY_TXPWR			BIT(8)
#घोषणा	PHY_PWRDIFF			BIT(9)

/* Define Dynamic Mechanism check module bit --> FDM */
#घोषणा WA_IOT				BIT(0)
#घोषणा DM_PWDB				BIT(1)
#घोषणा DM_MONITOR			BIT(2)
#घोषणा DM_DIG				BIT(3)
#घोषणा DM_EDCA_TURBO			BIT(4)

#घोषणा DM_PWDB				BIT(1)

क्रमागत dbgp_flag_e अणु
	FQOS = 0,
	FTX = 1,
	FRX = 2,
	FSEC = 3,
	FMGNT = 4,
	FMLME = 5,
	FRESOURCE = 6,
	FBEACON = 7,
	FISR = 8,
	FPHY = 9,
	FMP = 10,
	FEEPROM = 11,
	FPWR = 12,
	FDM = 13,
	FDBGCTRL = 14,
	FC2H = 15,
	FBT = 16,
	FINIT = 17,
	FIOCTL = 18,
	DBGP_TYPE_MAX
पूर्ण;

#अगर_घोषित CONFIG_RTLWIFI_DEBUG

काष्ठा rtl_priv;

__म_लिखो(4, 5)
व्योम _rtl_dbg_prपूर्णांक(काष्ठा rtl_priv *rtlpriv, u64 comp, पूर्णांक level,
		    स्थिर अक्षर *fmt, ...);

व्योम _rtl_dbg_prपूर्णांक_data(काष्ठा rtl_priv *rtlpriv, u64 comp, पूर्णांक level,
			 स्थिर अक्षर *titlestring,
			 स्थिर व्योम *hexdata, पूर्णांक hexdatalen);

#घोषणा rtl_dbg(rtlpriv, comp, level, fmt, ...)				\
	_rtl_dbg_prपूर्णांक(rtlpriv, comp, level,				\
		       fmt, ##__VA_ARGS__)

#घोषणा RTPRINT(rtlpriv, dbgtype, dbgflag, fmt, ...)			\
	_rtl_dbg_prपूर्णांक(rtlpriv, dbgtype, dbgflag, fmt, ##__VA_ARGS__)

#घोषणा RT_PRINT_DATA(rtlpriv, _comp, _level, _titlestring, _hexdata,	\
		      _hexdatalen)					\
	_rtl_dbg_prपूर्णांक_data(rtlpriv, _comp, _level,			\
			    _titlestring, _hexdata, _hexdatalen)

#अन्यथा

काष्ठा rtl_priv;

__म_लिखो(4, 5)
अटल अंतरभूत व्योम rtl_dbg(काष्ठा rtl_priv *rtlpriv,
			   u64 comp, पूर्णांक level,
			   स्थिर अक्षर *fmt, ...)
अणु
पूर्ण

__म_लिखो(4, 5)
अटल अंतरभूत व्योम RTPRINT(काष्ठा rtl_priv *rtlpriv,
			   पूर्णांक dbgtype, पूर्णांक dbgflag,
			   स्थिर अक्षर *fmt, ...)
अणु
पूर्ण

अटल अंतरभूत व्योम RT_PRINT_DATA(काष्ठा rtl_priv *rtlpriv,
				 u64 comp, पूर्णांक level,
				 स्थिर अक्षर *titlestring,
				 स्थिर व्योम *hexdata, माप_प्रकार hexdatalen)
अणु
पूर्ण

#पूर्ण_अगर

#अगर_घोषित CONFIG_RTLWIFI_DEBUG
व्योम rtl_debug_add_one(काष्ठा ieee80211_hw *hw);
व्योम rtl_debug_हटाओ_one(काष्ठा ieee80211_hw *hw);
व्योम rtl_debugfs_add_topdir(व्योम);
व्योम rtl_debugfs_हटाओ_topdir(व्योम);
#अन्यथा
#घोषणा rtl_debug_add_one(hw)
#घोषणा rtl_debug_हटाओ_one(hw)
#घोषणा rtl_debugfs_add_topdir()
#घोषणा rtl_debugfs_हटाओ_topdir()
#पूर्ण_अगर
#पूर्ण_अगर
