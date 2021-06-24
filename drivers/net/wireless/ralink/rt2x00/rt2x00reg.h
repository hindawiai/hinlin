<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
	Copyright (C) 2004 - 2009 Ivo van Doorn <IvDoorn@gmail.com>
	<http://rt2x00.serialmonkey.com>

 */

/*
	Module: rt2x00
	Abstract: rt2x00 generic रेजिस्टर inक्रमmation.
 */

#अगर_अघोषित RT2X00REG_H
#घोषणा RT2X00REG_H

/*
 * RX crypto status
 */
क्रमागत rx_crypto अणु
	RX_CRYPTO_SUCCESS = 0,
	RX_CRYPTO_FAIL_ICV = 1,
	RX_CRYPTO_FAIL_MIC = 2,
	RX_CRYPTO_FAIL_KEY = 3,
पूर्ण;

/*
 * Antenna values
 */
क्रमागत antenna अणु
	ANTENNA_SW_DIVERSITY = 0,
	ANTENNA_A = 1,
	ANTENNA_B = 2,
	ANTENNA_HW_DIVERSITY = 3,
पूर्ण;

/*
 * Led mode values.
 */
क्रमागत led_mode अणु
	LED_MODE_DEFAULT = 0,
	LED_MODE_TXRX_ACTIVITY = 1,
	LED_MODE_SIGNAL_STRENGTH = 2,
	LED_MODE_ASUS = 3,
	LED_MODE_ALPHA = 4,
पूर्ण;

/*
 * TSF sync values
 */
क्रमागत tsf_sync अणु
	TSF_SYNC_NONE = 0,
	TSF_SYNC_INFRA = 1,
	TSF_SYNC_ADHOC = 2,
	TSF_SYNC_AP_NONE = 3,
पूर्ण;

/*
 * Device states
 */
क्रमागत dev_state अणु
	STATE_DEEP_SLEEP = 0,
	STATE_SLEEP = 1,
	STATE_STANDBY = 2,
	STATE_AWAKE = 3,

/*
 * Additional device states, these values are
 * not strict since they are not directly passed
 * पूर्णांकo the device.
 */
	STATE_RADIO_ON,
	STATE_RADIO_OFF,
	STATE_RADIO_IRQ_ON,
	STATE_RADIO_IRQ_OFF,
पूर्ण;

/*
 * IFS backoff values
 */
क्रमागत अगरs अणु
	IFS_BACKOFF = 0,
	IFS_SIFS = 1,
	IFS_NEW_BACKOFF = 2,
	IFS_NONE = 3,
पूर्ण;

/*
 * IFS backoff values क्रम HT devices
 */
क्रमागत txop अणु
	TXOP_HTTXOP = 0,
	TXOP_PIFS = 1,
	TXOP_SIFS = 2,
	TXOP_BACKOFF = 3,
पूर्ण;

/*
 * Cipher types क्रम hardware encryption
 */
क्रमागत cipher अणु
	CIPHER_NONE = 0,
	CIPHER_WEP64 = 1,
	CIPHER_WEP128 = 2,
	CIPHER_TKIP = 3,
	CIPHER_AES = 4,
/*
 * The following fields were added by rt61pci and rt73usb.
 */
	CIPHER_CKIP64 = 5,
	CIPHER_CKIP128 = 6,
	CIPHER_TKIP_NO_MIC = 7, /* Don't send to device */

/*
 * Max cipher type.
 * Note that CIPHER_NONE isn't counted, and CKIP64 and CKIP128
 * are excluded due to limitations in mac80211.
 */
	CIPHER_MAX = 4,
पूर्ण;

/*
 * Rate modulations
 */
क्रमागत rate_modulation अणु
	RATE_MODE_CCK = 0,
	RATE_MODE_OFDM = 1,
	RATE_MODE_HT_MIX = 2,
	RATE_MODE_HT_GREENFIELD = 3,
पूर्ण;

/*
 * Firmware validation error codes
 */
क्रमागत firmware_errors अणु
	FW_OK,
	FW_BAD_CRC,
	FW_BAD_LENGTH,
	FW_BAD_VERSION,
पूर्ण;

/*
 * Register handlers.
 * We store the position of a रेजिस्टर field inside a field काष्ठाure,
 * This will simplअगरy the process of setting and पढ़ोing a certain field
 * inside the रेजिस्टर जबतक making sure the process reमुख्यs byte order safe.
 */
काष्ठा rt2x00_field8 अणु
	u8 bit_offset;
	u8 bit_mask;
पूर्ण;

काष्ठा rt2x00_field16 अणु
	u16 bit_offset;
	u16 bit_mask;
पूर्ण;

काष्ठा rt2x00_field32 अणु
	u32 bit_offset;
	u32 bit_mask;
पूर्ण;

/*
 * Power of two check, this will check
 * अगर the mask that has been given contains and contiguous set of bits.
 * Note that we cannot use the is_घातer_of_2() function since this
 * check must be करोne at compile-समय.
 */
#घोषणा is_घातer_of_two(x)	( !((x) & ((x)-1)) )
#घोषणा low_bit_mask(x)		( ((x)-1) & ~(x) )
#घोषणा is_valid_mask(x)	is_घातer_of_two(1LU + (x) + low_bit_mask(x))

/*
 * Macros to find first set bit in a variable.
 * These macros behave the same as the __ffs() functions but
 * the most important dअगरference that this is करोne during
 * compile-समय rather then run-समय.
 */
#घोषणा compile_ffs2(__x) \
	__builtin_choose_expr(((__x) & 0x1), 0, 1)

#घोषणा compile_ffs4(__x) \
	__builtin_choose_expr(((__x) & 0x3), \
			      (compile_ffs2((__x))), \
			      (compile_ffs2((__x) >> 2) + 2))

#घोषणा compile_ffs8(__x) \
	__builtin_choose_expr(((__x) & 0xf), \
			      (compile_ffs4((__x))), \
			      (compile_ffs4((__x) >> 4) + 4))

#घोषणा compile_ffs16(__x) \
	__builtin_choose_expr(((__x) & 0xff), \
			      (compile_ffs8((__x))), \
			      (compile_ffs8((__x) >> 8) + 8))

#घोषणा compile_ffs32(__x) \
	__builtin_choose_expr(((__x) & 0xffff), \
			      (compile_ffs16((__x))), \
			      (compile_ffs16((__x) >> 16) + 16))

/*
 * This macro will check the requirements क्रम the FIELDअणु8,16,32पूर्ण macros
 * The mask should be a स्थिरant non-zero contiguous set of bits which
 * करोes not exceed the given typelimit.
 */
#घोषणा FIELD_CHECK(__mask, __type)			\
	BUILD_BUG_ON(!(__mask) ||			\
		     !is_valid_mask(__mask) ||		\
		     (__mask) != (__type)(__mask))	\

#घोषणा FIELD8(__mask)				\
(अणु						\
	FIELD_CHECK(__mask, u8);		\
	(काष्ठा rt2x00_field8) अणु		\
		compile_ffs8(__mask), (__mask)	\
	पूर्ण;					\
पूर्ण)

#घोषणा FIELD16(__mask)				\
(अणु						\
	FIELD_CHECK(__mask, u16);		\
	(काष्ठा rt2x00_field16) अणु		\
		compile_ffs16(__mask), (__mask)	\
	पूर्ण;					\
पूर्ण)

#घोषणा FIELD32(__mask)				\
(अणु						\
	FIELD_CHECK(__mask, u32);		\
	(काष्ठा rt2x00_field32) अणु		\
		compile_ffs32(__mask), (__mask)	\
	पूर्ण;					\
पूर्ण)

#घोषणा SET_FIELD(__reg, __type, __field, __value)\
(अणु						\
	typecheck(__type, __field);		\
	*(__reg) &= ~((__field).bit_mask);	\
	*(__reg) |= ((__value) <<		\
	    ((__field).bit_offset)) &		\
	    ((__field).bit_mask);		\
पूर्ण)

#घोषणा GET_FIELD(__reg, __type, __field)	\
(अणु						\
	typecheck(__type, __field);		\
	((__reg) & ((__field).bit_mask)) >>	\
	    ((__field).bit_offset);		\
पूर्ण)

#घोषणा rt2x00_set_field32(__reg, __field, __value) \
	SET_FIELD(__reg, काष्ठा rt2x00_field32, __field, __value)
#घोषणा rt2x00_get_field32(__reg, __field) \
	GET_FIELD(__reg, काष्ठा rt2x00_field32, __field)

#घोषणा rt2x00_set_field16(__reg, __field, __value) \
	SET_FIELD(__reg, काष्ठा rt2x00_field16, __field, __value)
#घोषणा rt2x00_get_field16(__reg, __field) \
	GET_FIELD(__reg, काष्ठा rt2x00_field16, __field)

#घोषणा rt2x00_set_field8(__reg, __field, __value) \
	SET_FIELD(__reg, काष्ठा rt2x00_field8, __field, __value)
#घोषणा rt2x00_get_field8(__reg, __field) \
	GET_FIELD(__reg, काष्ठा rt2x00_field8, __field)

#पूर्ण_अगर /* RT2X00REG_H */
