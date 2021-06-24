<शैली गुरु>
/*
 * Atheros CARL9170 driver
 *
 * Basic HW रेजिस्टर/memory/command access functions
 *
 * Copyright 2008, Johannes Berg <johannes@sipsolutions.net>
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

#समावेश <यंत्र/भाग64.h>
#समावेश "carl9170.h"
#समावेश "cmd.h"

पूर्णांक carl9170_ग_लिखो_reg(काष्ठा ar9170 *ar, स्थिर u32 reg, स्थिर u32 val)
अणु
	स्थिर __le32 buf[2] = अणु
		cpu_to_le32(reg),
		cpu_to_le32(val),
	पूर्ण;
	पूर्णांक err;

	err = carl9170_exec_cmd(ar, CARL9170_CMD_WREG, माप(buf),
				(u8 *) buf, 0, शून्य);
	अगर (err) अणु
		अगर (net_ratelimit()) अणु
			wiphy_err(ar->hw->wiphy, "writing reg %#x "
				"(val %#x) failed (%d)\n", reg, val, err);
		पूर्ण
	पूर्ण
	वापस err;
पूर्ण

पूर्णांक carl9170_पढ़ो_mreg(काष्ठा ar9170 *ar, स्थिर पूर्णांक nregs,
		       स्थिर u32 *regs, u32 *out)
अणु
	पूर्णांक i, err;
	__le32 *offs, *res;

	/* abuse "out" क्रम the रेजिस्टर offsets, must be same length */
	offs = (__le32 *)out;
	क्रम (i = 0; i < nregs; i++)
		offs[i] = cpu_to_le32(regs[i]);

	/* also use the same buffer क्रम the input */
	res = (__le32 *)out;

	err = carl9170_exec_cmd(ar, CARL9170_CMD_RREG,
				4 * nregs, (u8 *)offs,
				4 * nregs, (u8 *)res);
	अगर (err) अणु
		अगर (net_ratelimit()) अणु
			wiphy_err(ar->hw->wiphy, "reading regs failed (%d)\n",
				  err);
		पूर्ण
		वापस err;
	पूर्ण

	/* convert result to cpu endian */
	क्रम (i = 0; i < nregs; i++)
		out[i] = le32_to_cpu(res[i]);

	वापस 0;
पूर्ण

पूर्णांक carl9170_पढ़ो_reg(काष्ठा ar9170 *ar, u32 reg, u32 *val)
अणु
	वापस carl9170_पढ़ो_mreg(ar, 1, &reg, val);
पूर्ण

पूर्णांक carl9170_echo_test(काष्ठा ar9170 *ar, स्थिर u32 v)
अणु
	u32 echores;
	पूर्णांक err;

	err = carl9170_exec_cmd(ar, CARL9170_CMD_ECHO,
				4, (u8 *)&v,
				4, (u8 *)&echores);
	अगर (err)
		वापस err;

	अगर (v != echores) अणु
		wiphy_info(ar->hw->wiphy, "wrong echo %x != %x", v, echores);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

काष्ठा carl9170_cmd *carl9170_cmd_buf(काष्ठा ar9170 *ar,
	स्थिर क्रमागत carl9170_cmd_oids cmd, स्थिर अचिन्हित पूर्णांक len)
अणु
	काष्ठा carl9170_cmd *पंचांगp;

	पंचांगp = kzalloc(माप(काष्ठा carl9170_cmd_head) + len, GFP_ATOMIC);
	अगर (पंचांगp) अणु
		पंचांगp->hdr.cmd = cmd;
		पंचांगp->hdr.len = len;
	पूर्ण

	वापस पंचांगp;
पूर्ण

पूर्णांक carl9170_reboot(काष्ठा ar9170 *ar)
अणु
	काष्ठा carl9170_cmd *cmd;
	पूर्णांक err;

	cmd = carl9170_cmd_buf(ar, CARL9170_CMD_REBOOT_ASYNC, 0);
	अगर (!cmd)
		वापस -ENOMEM;

	err = __carl9170_exec_cmd(ar, cmd, true);
	वापस err;
पूर्ण

पूर्णांक carl9170_mac_reset(काष्ठा ar9170 *ar)
अणु
	वापस carl9170_exec_cmd(ar, CARL9170_CMD_SWRST,
				 0, शून्य, 0, शून्य);
पूर्ण

पूर्णांक carl9170_bcn_ctrl(काष्ठा ar9170 *ar, स्थिर अचिन्हित पूर्णांक vअगर_id,
		       स्थिर u32 mode, स्थिर u32 addr, स्थिर u32 len)
अणु
	काष्ठा carl9170_cmd *cmd;

	cmd = carl9170_cmd_buf(ar, CARL9170_CMD_BCN_CTRL_ASYNC,
			       माप(काष्ठा carl9170_bcn_ctrl_cmd));
	अगर (!cmd)
		वापस -ENOMEM;

	cmd->bcn_ctrl.vअगर_id = cpu_to_le32(vअगर_id);
	cmd->bcn_ctrl.mode = cpu_to_le32(mode);
	cmd->bcn_ctrl.bcn_addr = cpu_to_le32(addr);
	cmd->bcn_ctrl.bcn_len = cpu_to_le32(len);

	वापस __carl9170_exec_cmd(ar, cmd, true);
पूर्ण

पूर्णांक carl9170_collect_tally(काष्ठा ar9170 *ar)
अणु
	काष्ठा carl9170_tally_rsp tally;
	काष्ठा survey_info *info;
	अचिन्हित पूर्णांक tick;
	पूर्णांक err;

	err = carl9170_exec_cmd(ar, CARL9170_CMD_TALLY, 0, शून्य,
				माप(tally), (u8 *)&tally);
	अगर (err)
		वापस err;

	tick = le32_to_cpu(tally.tick);
	अगर (tick) अणु
		ar->tally.active += le32_to_cpu(tally.active) / tick;
		ar->tally.cca += le32_to_cpu(tally.cca) / tick;
		ar->tally.tx_समय += le32_to_cpu(tally.tx_समय) / tick;
		ar->tally.rx_total += le32_to_cpu(tally.rx_total);
		ar->tally.rx_overrun += le32_to_cpu(tally.rx_overrun);

		अगर (ar->channel) अणु
			info = &ar->survey[ar->channel->hw_value];
			info->समय = ar->tally.active;
			info->समय_busy = ar->tally.cca;
			info->समय_प्रकारx = ar->tally.tx_समय;
			करो_भाग(info->समय, 1000);
			करो_भाग(info->समय_busy, 1000);
			करो_भाग(info->समय_प्रकारx, 1000);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक carl9170_घातersave(काष्ठा ar9170 *ar, स्थिर bool ps)
अणु
	काष्ठा carl9170_cmd *cmd;
	u32 state;

	cmd = carl9170_cmd_buf(ar, CARL9170_CMD_PSM_ASYNC,
			       माप(काष्ठा carl9170_psm));
	अगर (!cmd)
		वापस -ENOMEM;

	अगर (ps) अणु
		/* Sleep until next TBTT */
		state = CARL9170_PSM_SLEEP | 1;
	पूर्ण अन्यथा अणु
		/* wake up immediately */
		state = 1;
	पूर्ण

	cmd->psm.state = cpu_to_le32(state);
	वापस __carl9170_exec_cmd(ar, cmd, true);
पूर्ण
