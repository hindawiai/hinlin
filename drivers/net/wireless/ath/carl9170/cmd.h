<शैली गुरु>
/*
 * Atheros CARL9170 driver
 *
 * Basic HW रेजिस्टर/memory/command access functions
 *
 * Copyright 2008, Johannes Berg <johannes@sipsolutions.net>
 * Copyright 2010, Christian Lamparter <chunkeey@googlemail.com>
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program; see the file COPYING.  If not, see
 * http://www.gnu.org/licenses/.
 *
 * This file incorporates work covered by the following copyright and
 * permission notice:
 *    Copyright (c) 2007-2008 Atheros Communications, Inc.
 *
 *    Permission to use, copy, modअगरy, and/or distribute this software क्रम any
 *    purpose with or without fee is hereby granted, provided that the above
 *    copyright notice and this permission notice appear in all copies.
 *
 *    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 *    WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 *    MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 *    ANY SPECIAL, सूचीECT, INसूचीECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 *    WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 *    ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 *    OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */
#अगर_अघोषित __CMD_H
#घोषणा __CMD_H

#समावेश "carl9170.h"

/* basic HW access */
पूर्णांक carl9170_ग_लिखो_reg(काष्ठा ar9170 *ar, स्थिर u32 reg, स्थिर u32 val);
पूर्णांक carl9170_पढ़ो_reg(काष्ठा ar9170 *ar, स्थिर u32 reg, u32 *val);
पूर्णांक carl9170_पढ़ो_mreg(काष्ठा ar9170 *ar, स्थिर पूर्णांक nregs,
		       स्थिर u32 *regs, u32 *out);
पूर्णांक carl9170_echo_test(काष्ठा ar9170 *ar, u32 v);
पूर्णांक carl9170_reboot(काष्ठा ar9170 *ar);
पूर्णांक carl9170_mac_reset(काष्ठा ar9170 *ar);
पूर्णांक carl9170_घातersave(काष्ठा ar9170 *ar, स्थिर bool घातer_on);
पूर्णांक carl9170_collect_tally(काष्ठा ar9170 *ar);
पूर्णांक carl9170_bcn_ctrl(काष्ठा ar9170 *ar, स्थिर अचिन्हित पूर्णांक vअगर_id,
		       स्थिर u32 mode, स्थिर u32 addr, स्थिर u32 len);

अटल अंतरभूत पूर्णांक carl9170_flush_cab(काष्ठा ar9170 *ar,
				     स्थिर अचिन्हित पूर्णांक vअगर_id)
अणु
	वापस carl9170_bcn_ctrl(ar, vअगर_id, CARL9170_BCN_CTRL_DRAIN, 0, 0);
पूर्ण

अटल अंतरभूत पूर्णांक carl9170_rx_filter(काष्ठा ar9170 *ar,
				     स्थिर अचिन्हित पूर्णांक _rx_filter)
अणु
	__le32 rx_filter = cpu_to_le32(_rx_filter);

	वापस carl9170_exec_cmd(ar, CARL9170_CMD_RX_FILTER,
				माप(rx_filter), (u8 *)&rx_filter,
				0, शून्य);
पूर्ण

काष्ठा carl9170_cmd *carl9170_cmd_buf(काष्ठा ar9170 *ar,
	स्थिर क्रमागत carl9170_cmd_oids cmd, स्थिर अचिन्हित पूर्णांक len);

/*
 * Macros to facilitate writing multiple रेजिस्टरs in a single
 * ग_लिखो-combining USB command. Note that when the first group
 * fails the whole thing will fail without any others attempted,
 * but you won't know which ग_लिखो in the group failed.
 */
#घोषणा carl9170_regग_लिखो_begin(ar)					\
करो अणु									\
	पूर्णांक __nreg = 0, __err = 0;					\
	काष्ठा ar9170 *__ar = ar;

#घोषणा carl9170_regग_लिखो(r, v) करो अणु					\
	__ar->cmd_buf[2 * __nreg + 1] = cpu_to_le32(r);			\
	__ar->cmd_buf[2 * __nreg + 2] = cpu_to_le32(v);			\
	__nreg++;							\
	अगर ((__nreg >= PAYLOAD_MAX / 2)) अणु				\
		अगर (IS_ACCEPTING_CMD(__ar))				\
			__err = carl9170_exec_cmd(__ar,			\
				CARL9170_CMD_WREG, 8 * __nreg,		\
				(u8 *) &__ar->cmd_buf[1], 0, शून्य);	\
		अन्यथा							\
			जाओ __regग_लिखो_out;				\
									\
		__nreg = 0;						\
		अगर (__err)						\
			जाओ __regग_लिखो_out;				\
	पूर्ण								\
पूर्ण जबतक (0)

#घोषणा carl9170_regग_लिखो_finish()					\
__regग_लिखो_out :							\
	अगर (__err == 0 && __nreg) अणु					\
		अगर (IS_ACCEPTING_CMD(__ar))				\
			__err = carl9170_exec_cmd(__ar,			\
				CARL9170_CMD_WREG, 8 * __nreg,		\
				(u8 *) &__ar->cmd_buf[1], 0, शून्य);	\
		__nreg = 0;						\
	पूर्ण

#घोषणा carl9170_regग_लिखो_result()					\
	__err;								\
पूर्ण जबतक (0)


#घोषणा carl9170_async_regग_लिखो_get_buf()				\
करो अणु									\
	__nreg = 0;							\
	__cmd = carl9170_cmd_buf(__carl, CARL9170_CMD_WREG_ASYNC,	\
				 CARL9170_MAX_CMD_PAYLOAD_LEN);		\
	अगर (__cmd == शून्य) अणु						\
		__err = -ENOMEM;					\
		जाओ __async_regग_लिखो_out;				\
	पूर्ण								\
पूर्ण जबतक (0)

#घोषणा carl9170_async_regग_लिखो_begin(carl)				\
करो अणु									\
	काष्ठा ar9170 *__carl = carl;					\
	काष्ठा carl9170_cmd *__cmd;					\
	अचिन्हित पूर्णांक __nreg;						\
	पूर्णांक  __err = 0;							\
	carl9170_async_regग_लिखो_get_buf();				\

#घोषणा carl9170_async_regग_लिखो_flush()					\
करो अणु									\
	अगर (__cmd == शून्य || __nreg == 0)				\
		अवरोध;							\
									\
	अगर (IS_ACCEPTING_CMD(__carl) && __nreg) अणु			\
		__cmd->hdr.len = 8 * __nreg;				\
		__err = __carl9170_exec_cmd(__carl, __cmd, true);	\
		__cmd = शून्य;						\
		अवरोध;							\
	पूर्ण								\
	जाओ __async_regग_लिखो_out;					\
पूर्ण जबतक (0)

#घोषणा carl9170_async_regग_लिखो(r, v) करो अणु				\
	अगर (__cmd == शून्य)						\
		carl9170_async_regग_लिखो_get_buf();			\
	__cmd->wreg.regs[__nreg].addr = cpu_to_le32(r);			\
	__cmd->wreg.regs[__nreg].val = cpu_to_le32(v);			\
	__nreg++;							\
	अगर ((__nreg >= PAYLOAD_MAX / 2))				\
		carl9170_async_regग_लिखो_flush();			\
पूर्ण जबतक (0)

#घोषणा carl9170_async_regग_लिखो_finish() करो अणु				\
__async_regग_लिखो_out:							\
	अगर (__cmd != शून्य && __err == 0)				\
		carl9170_async_regग_लिखो_flush();			\
	kमुक्त(__cmd);							\
पूर्ण जबतक (0)								\

#घोषणा carl9170_async_regग_लिखो_result()				\
	__err;								\
पूर्ण जबतक (0)

#पूर्ण_अगर /* __CMD_H */
