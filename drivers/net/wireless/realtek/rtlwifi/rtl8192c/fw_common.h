<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright(c) 2009-2012  Realtek Corporation.*/

#अगर_अघोषित __RTL92C__FW__COMMON__H__
#घोषणा __RTL92C__FW__COMMON__H__

#घोषणा FW_8192C_SIZE				0x3000
#घोषणा FW_8192C_START_ADDRESS			0x1000
#घोषणा FW_8192C_END_ADDRESS			0x1FFF
#घोषणा FW_8192C_PAGE_SIZE			4096
#घोषणा FW_8192C_POLLING_DELAY			5
#घोषणा FW_8192C_POLLING_TIMEOUT_COUNT		100
#घोषणा NORMAL_CHIP				BIT(4)
#घोषणा H2C_92C_KEEP_ALIVE_CTRL			48

#घोषणा IS_FW_HEADER_EXIST(_pfwhdr)	\
	((le16_to_cpu(_pfwhdr->signature)&0xFFF0) == 0x92C0 ||\
	(le16_to_cpu(_pfwhdr->signature)&0xFFF0) == 0x88C0)

#घोषणा CUT_VERSION_MASK		(BIT(6)|BIT(7))
#घोषणा CHIP_VENDOR_UMC			BIT(5)
#घोषणा CHIP_VENDOR_UMC_B_CUT		BIT(6) /* Chip version क्रम ECO */
#घोषणा IS_CHIP_VER_B(version)  ((version & CHIP_VER_B) ? true : false)
#घोषणा RF_TYPE_MASK			(BIT(0)|BIT(1))
#घोषणा GET_CVID_RF_TYPE(version)	\
	((version) & RF_TYPE_MASK)
#घोषणा GET_CVID_CUT_VERSION(version) \
	((version) & CUT_VERSION_MASK)
#घोषणा IS_NORMAL_CHIP(version)	\
	((version & NORMAL_CHIP) ? true : false)
#घोषणा IS_2T2R(version) \
	(((GET_CVID_RF_TYPE(version)) == \
	CHIP_92C_BITMASK) ? true : false)
#घोषणा IS_92C_SERIAL(version) \
	((IS_2T2R(version)) ? true : false)
#घोषणा IS_CHIP_VENDOR_UMC(version)	\
	((version & CHIP_VENDOR_UMC) ? true : false)
#घोषणा IS_VENDOR_UMC_A_CUT(version) \
	((IS_CHIP_VENDOR_UMC(version)) ? \
	((GET_CVID_CUT_VERSION(version)) ? false : true) : false)
#घोषणा IS_81XXC_VENDOR_UMC_B_CUT(version)	\
	((IS_CHIP_VENDOR_UMC(version)) ? \
	((GET_CVID_CUT_VERSION(version) == \
		CHIP_VENDOR_UMC_B_CUT) ? true : false) : false)

#घोषणा pagक्रमागत_128(_len)	(u32)(((_len)>>7) + ((_len)&0x7F ? 1 : 0))

#घोषणा SET_H2CCMD_PWRMODE_PARM_MODE(__ph2ccmd, __val)			\
	*(u8 *)(__ph2ccmd) = __val
#घोषणा SET_H2CCMD_PWRMODE_PARM_SMART_PS(__ph2ccmd, __val)		\
	*(u8 *)(__ph2ccmd + 1) = __val
#घोषणा SET_H2CCMD_PWRMODE_PARM_BCN_PASS_TIME(__ph2ccmd, __val)	\
	*(u8 *)(__ph2ccmd + 2) = __val
#घोषणा SET_H2CCMD_JOINBSSRPT_PARM_OPMODE(__ph2ccmd, __val)		\
	*(u8 *)(__ph2ccmd) = __val
#घोषणा SET_H2CCMD_RSVDPAGE_LOC_PROBE_RSP(__ph2ccmd, __val)		\
	*(u8 *)(__ph2ccmd) = __val
#घोषणा SET_H2CCMD_RSVDPAGE_LOC_PSPOLL(__ph2ccmd, __val)		\
	*(u8 *)(__ph2ccmd + 1) = __val
#घोषणा SET_H2CCMD_RSVDPAGE_LOC_शून्य_DATA(__ph2ccmd, __val)		\
	*(u8 *)(__ph2ccmd + 2) = __val

पूर्णांक rtl92c_करोwnload_fw(काष्ठा ieee80211_hw *hw);
व्योम rtl92c_fill_h2c_cmd(काष्ठा ieee80211_hw *hw, u8 element_id,
			 u32 cmd_len, u8 *p_cmdbuffer);
व्योम rtl92c_firmware_selfreset(काष्ठा ieee80211_hw *hw);
व्योम rtl92c_set_fw_pwrmode_cmd(काष्ठा ieee80211_hw *hw, u8 mode);
व्योम rtl92c_set_fw_rsvdpagepkt
	(काष्ठा ieee80211_hw *hw,
	 bool (*cmd_send_packet)(काष्ठा ieee80211_hw *, काष्ठा sk_buff *));
व्योम rtl92c_set_fw_joinbss_report_cmd(काष्ठा ieee80211_hw *hw, u8 mstatus);
व्योम usb_ग_लिखोN_async(काष्ठा rtl_priv *rtlpriv, u32 addr, व्योम *data, u16 len);
व्योम rtl92c_set_p2p_ps_offload_cmd(काष्ठा ieee80211_hw *hw, u8 p2p_ps_state);

#पूर्ण_अगर
