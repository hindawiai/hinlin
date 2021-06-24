<शैली गुरु>
/*
 * Copyright (c) 2004-2011 Atheros Communications Inc.
 * Copyright (c) 2011 Qualcomm Atheros, Inc.
 *
 * Permission to use, copy, modअगरy, and/or distribute this software क्रम any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, सूचीECT, INसूचीECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#अगर_अघोषित BMI_H
#घोषणा BMI_H

/*
 * Bootloader Messaging Interface (BMI)
 *
 * BMI is a very simple messaging पूर्णांकerface used during initialization
 * to पढ़ो memory, ग_लिखो memory, execute code, and to define an
 * application entry PC.
 *
 * It is used to करोwnload an application to ATH6KL, to provide
 * patches to code that is alपढ़ोy resident on ATH6KL, and generally
 * to examine and modअगरy state.  The Host has an opportunity to use
 * BMI only once during bootup.  Once the Host issues a BMI_DONE
 * command, this opportunity ends.
 *
 * The Host ग_लिखोs BMI requests to mailbox0, and पढ़ोs BMI responses
 * from mailbox0.   BMI requests all begin with a command
 * (see below क्रम specअगरic commands), and are followed by
 * command-specअगरic data.
 *
 * Flow control:
 * The Host can only issue a command once the Target gives it a
 * "BMI Command Credit", using ATH6KL Counter #4.  As soon as the
 * Target has completed a command, it issues another BMI Command
 * Credit (so the Host can issue the next command).
 *
 * BMI handles all required Target-side cache flushing.
 */

/* BMI Commands */

#घोषणा BMI_NO_COMMAND                      0

#घोषणा BMI_DONE                            1
/*
 * Semantics: Host is करोne using BMI
 * Request क्रमmat:
 *    u32 command (BMI_DONE)
 * Response क्रमmat: none
 */

#घोषणा BMI_READ_MEMORY                     2
/*
 * Semantics: Host पढ़ोs ATH6KL memory
 * Request क्रमmat:
 *    u32 command (BMI_READ_MEMORY)
 *    u32 address
 *    u32 length, at most BMI_DATASZ_MAX
 * Response क्रमmat:
 *    u8 data[length]
 */

#घोषणा BMI_WRITE_MEMORY                    3
/*
 * Semantics: Host ग_लिखोs ATH6KL memory
 * Request क्रमmat:
 *    u32 command (BMI_WRITE_MEMORY)
 *    u32 address
 *    u32 length, at most BMI_DATASZ_MAX
 *    u8 data[length]
 * Response क्रमmat: none
 */

#घोषणा BMI_EXECUTE                         4
/*
 * Semantics: Causes ATH6KL to execute code
 * Request क्रमmat:
 *    u32 command (BMI_EXECUTE)
 *    u32 address
 *    u32 parameter
 * Response क्रमmat:
 *    u32 वापस value
 */

#घोषणा BMI_SET_APP_START                   5
/*
 * Semantics: Set Target application starting address
 * Request क्रमmat:
 *    u32 command (BMI_SET_APP_START)
 *    u32 address
 * Response क्रमmat: none
 */

#घोषणा BMI_READ_SOC_REGISTER               6
/*
 * Semantics: Read a 32-bit Target SOC रेजिस्टर.
 * Request क्रमmat:
 *    u32 command (BMI_READ_REGISTER)
 *    u32 address
 * Response क्रमmat:
 *    u32 value
 */

#घोषणा BMI_WRITE_SOC_REGISTER              7
/*
 * Semantics: Write a 32-bit Target SOC रेजिस्टर.
 * Request क्रमmat:
 *    u32 command (BMI_WRITE_REGISTER)
 *    u32 address
 *    u32 value
 *
 * Response क्रमmat: none
 */

#घोषणा BMI_GET_TARGET_ID                  8
#घोषणा BMI_GET_TARGET_INFO                8
/*
 * Semantics: Fetch the 4-byte Target inक्रमmation
 * Request क्रमmat:
 *    u32 command (BMI_GET_TARGET_ID/INFO)
 * Response क्रमmat1 (old firmware):
 *    u32 TargetVersionID
 * Response क्रमmat2 (newer firmware):
 *    u32 TARGET_VERSION_SENTINAL
 *    काष्ठा bmi_target_info;
 */

#घोषणा TARGET_VERSION_SENTINAL 0xffffffff
#घोषणा TARGET_TYPE_AR6003      3
#घोषणा TARGET_TYPE_AR6004      5
#घोषणा BMI_ROMPATCH_INSTALL               9
/*
 * Semantics: Install a ROM Patch.
 * Request क्रमmat:
 *    u32 command (BMI_ROMPATCH_INSTALL)
 *    u32 Target ROM Address
 *    u32 Target RAM Address or Value (depending on Target Type)
 *    u32 Size, in bytes
 *    u32 Activate? 1-->activate;
 *                            0-->install but करो not activate
 * Response क्रमmat:
 *    u32 PatchID
 */

#घोषणा BMI_ROMPATCH_UNINSTALL             10
/*
 * Semantics: Uninstall a previously-installed ROM Patch,
 * स्वतःmatically deactivating, अगर necessary.
 * Request क्रमmat:
 *    u32 command (BMI_ROMPATCH_UNINSTALL)
 *    u32 PatchID
 *
 * Response क्रमmat: none
 */

#घोषणा BMI_ROMPATCH_ACTIVATE              11
/*
 * Semantics: Activate a list of previously-installed ROM Patches.
 * Request क्रमmat:
 *    u32 command (BMI_ROMPATCH_ACTIVATE)
 *    u32 rompatch_count
 *    u32 PatchID[rompatch_count]
 *
 * Response क्रमmat: none
 */

#घोषणा BMI_ROMPATCH_DEACTIVATE            12
/*
 * Semantics: Deactivate a list of active ROM Patches.
 * Request क्रमmat:
 *    u32 command (BMI_ROMPATCH_DEACTIVATE)
 *    u32 rompatch_count
 *    u32 PatchID[rompatch_count]
 *
 * Response क्रमmat: none
 */


#घोषणा BMI_LZ_STREAM_START                13
/*
 * Semantics: Begin an LZ-compressed stream of input
 * which is to be uncompressed by the Target to an
 * output buffer at address.  The output buffer must
 * be sufficiently large to hold the uncompressed
 * output from the compressed input stream.  This BMI
 * command should be followed by a series of 1 or more
 * BMI_LZ_DATA commands.
 *    u32 command (BMI_LZ_STREAM_START)
 *    u32 address
 * Note: Not supported on all versions of ROM firmware.
 */

#घोषणा BMI_LZ_DATA                        14
/*
 * Semantics: Host ग_लिखोs ATH6KL memory with LZ-compressed
 * data which is uncompressed by the Target.  This command
 * must be preceded by a BMI_LZ_STREAM_START command. A series
 * of BMI_LZ_DATA commands are considered part of a single
 * input stream until another BMI_LZ_STREAM_START is issued.
 * Request क्रमmat:
 *    u32 command (BMI_LZ_DATA)
 *    u32 length (of compressed data),
 *                  at most BMI_DATASZ_MAX
 *    u8 CompressedData[length]
 * Response क्रमmat: none
 * Note: Not supported on all versions of ROM firmware.
 */

#घोषणा BMI_COMMUNICATION_TIMEOUT       1000 /* in msec */

काष्ठा ath6kl;
काष्ठा ath6kl_bmi_target_info अणु
	__le32 byte_count;   /* size of this काष्ठाure */
	__le32 version;      /* target version id */
	__le32 type;         /* target type */
पूर्ण __packed;

#घोषणा ath6kl_bmi_ग_लिखो_hi32(ar, item, val)				\
	(अणु								\
		u32 addr;						\
		__le32 v;						\
									\
		addr = ath6kl_get_hi_item_addr(ar, HI_ITEM(item));	\
		v = cpu_to_le32(val);					\
		ath6kl_bmi_ग_लिखो(ar, addr, (u8 *) &v, माप(v));	\
	पूर्ण)

#घोषणा ath6kl_bmi_पढ़ो_hi32(ar, item, val)				\
	(अणु								\
		u32 addr, *check_type = val;				\
		__le32 पंचांगp;						\
		पूर्णांक ret;						\
									\
		(व्योम) (check_type == val);				\
		addr = ath6kl_get_hi_item_addr(ar, HI_ITEM(item));	\
		ret = ath6kl_bmi_पढ़ो(ar, addr, (u8 *) &पंचांगp, 4);	\
		अगर (!ret)						\
			*val = le32_to_cpu(पंचांगp);			\
		ret;							\
	पूर्ण)

पूर्णांक ath6kl_bmi_init(काष्ठा ath6kl *ar);
व्योम ath6kl_bmi_cleanup(काष्ठा ath6kl *ar);
व्योम ath6kl_bmi_reset(काष्ठा ath6kl *ar);

पूर्णांक ath6kl_bmi_करोne(काष्ठा ath6kl *ar);
पूर्णांक ath6kl_bmi_get_target_info(काष्ठा ath6kl *ar,
			       काष्ठा ath6kl_bmi_target_info *targ_info);
पूर्णांक ath6kl_bmi_पढ़ो(काष्ठा ath6kl *ar, u32 addr, u8 *buf, u32 len);
पूर्णांक ath6kl_bmi_ग_लिखो(काष्ठा ath6kl *ar, u32 addr, u8 *buf, u32 len);
पूर्णांक ath6kl_bmi_execute(काष्ठा ath6kl *ar,
		       u32 addr, u32 *param);
पूर्णांक ath6kl_bmi_set_app_start(काष्ठा ath6kl *ar,
			     u32 addr);
पूर्णांक ath6kl_bmi_reg_पढ़ो(काष्ठा ath6kl *ar, u32 addr, u32 *param);
पूर्णांक ath6kl_bmi_reg_ग_लिखो(काष्ठा ath6kl *ar, u32 addr, u32 param);
पूर्णांक ath6kl_bmi_lz_data(काष्ठा ath6kl *ar,
		       u8 *buf, u32 len);
पूर्णांक ath6kl_bmi_lz_stream_start(काष्ठा ath6kl *ar,
			       u32 addr);
पूर्णांक ath6kl_bmi_fast_करोwnload(काष्ठा ath6kl *ar,
			     u32 addr, u8 *buf, u32 len);
#पूर्ण_अगर
