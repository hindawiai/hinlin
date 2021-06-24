<शैली गुरु>
/*
 * Copyright (c) 2007-2008 Bruno Ranकरोlf <bruno@thinktube.com>
 *
 *  This file is मुक्त software: you may copy, redistribute and/or modअगरy it
 *  under the terms of the GNU General Public License as published by the
 *  Free Software Foundation, either version 2 of the License, or (at your
 *  option) any later version.
 *
 *  This file is distributed in the hope that it will be useful, but
 *  WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  General Public License क्रम more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  aदीर्घ with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *
 * This file incorporates work covered by the following copyright and
 * permission notice:
 *
 * Copyright (c) 2002-2005 Sam Leffler, Errno Consulting
 * Copyright (c) 2004-2005 Atheros Communications, Inc.
 * Copyright (c) 2006 Devicescape Software, Inc.
 * Copyright (c) 2007 Jiri Slaby <jirislaby@gmail.com>
 * Copyright (c) 2007 Luis R. Rodriguez <mcgrof@winlab.rutgers.edu>
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer,
 *    without modअगरication.
 * 2. Redistributions in binary क्रमm must reproduce at minimum a disclaimer
 *    similar to the "NO WARRANTY" disclaimer below ("Disclaimer") and any
 *    redistribution must be conditioned upon including a substantially
 *    similar Disclaimer requirement क्रम further binary redistribution.
 * 3. Neither the names of the above-listed copyright holders nor the names
 *    of any contributors may be used to enकरोrse or promote products derived
 *    from this software without specअगरic prior written permission.
 *
 * Alternatively, this software may be distributed under the terms of the
 * GNU General Public License ("GPL") version 2 as published by the Free
 * Software Foundation.
 *
 * NO WARRANTY
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF NONINFRINGEMENT, MERCHANTIBILITY
 * AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL
 * THE COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR SPECIAL, EXEMPLARY,
 * OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER
 * IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGES.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/export.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/vदो_स्मृति.h>

#समावेश <linux/seq_file.h>
#समावेश <linux/list.h>
#समावेश "debug.h"
#समावेश "ath5k.h"
#समावेश "reg.h"
#समावेश "base.h"

अटल अचिन्हित पूर्णांक ath5k_debug;
module_param_named(debug, ath5k_debug, uपूर्णांक, 0);


/* debugfs: रेजिस्टरs */

काष्ठा reg अणु
	स्थिर अक्षर *name;
	पूर्णांक addr;
पूर्ण;

#घोषणा REG_STRUCT_INIT(r) अणु #r, r पूर्ण

/* just a few अक्रमom रेजिस्टरs, might want to add more */
अटल स्थिर काष्ठा reg regs[] = अणु
	REG_STRUCT_INIT(AR5K_CR),
	REG_STRUCT_INIT(AR5K_RXDP),
	REG_STRUCT_INIT(AR5K_CFG),
	REG_STRUCT_INIT(AR5K_IER),
	REG_STRUCT_INIT(AR5K_BCR),
	REG_STRUCT_INIT(AR5K_RTSD0),
	REG_STRUCT_INIT(AR5K_RTSD1),
	REG_STRUCT_INIT(AR5K_TXCFG),
	REG_STRUCT_INIT(AR5K_RXCFG),
	REG_STRUCT_INIT(AR5K_RXJLA),
	REG_STRUCT_INIT(AR5K_MIBC),
	REG_STRUCT_INIT(AR5K_TOPS),
	REG_STRUCT_INIT(AR5K_RXNOFRM),
	REG_STRUCT_INIT(AR5K_TXNOFRM),
	REG_STRUCT_INIT(AR5K_RPGTO),
	REG_STRUCT_INIT(AR5K_RFCNT),
	REG_STRUCT_INIT(AR5K_MISC),
	REG_STRUCT_INIT(AR5K_QCUDCU_CLKGT),
	REG_STRUCT_INIT(AR5K_ISR),
	REG_STRUCT_INIT(AR5K_PISR),
	REG_STRUCT_INIT(AR5K_SISR0),
	REG_STRUCT_INIT(AR5K_SISR1),
	REG_STRUCT_INIT(AR5K_SISR2),
	REG_STRUCT_INIT(AR5K_SISR3),
	REG_STRUCT_INIT(AR5K_SISR4),
	REG_STRUCT_INIT(AR5K_IMR),
	REG_STRUCT_INIT(AR5K_PIMR),
	REG_STRUCT_INIT(AR5K_SIMR0),
	REG_STRUCT_INIT(AR5K_SIMR1),
	REG_STRUCT_INIT(AR5K_SIMR2),
	REG_STRUCT_INIT(AR5K_SIMR3),
	REG_STRUCT_INIT(AR5K_SIMR4),
	REG_STRUCT_INIT(AR5K_DCM_ADDR),
	REG_STRUCT_INIT(AR5K_DCCFG),
	REG_STRUCT_INIT(AR5K_CCFG),
	REG_STRUCT_INIT(AR5K_CPC0),
	REG_STRUCT_INIT(AR5K_CPC1),
	REG_STRUCT_INIT(AR5K_CPC2),
	REG_STRUCT_INIT(AR5K_CPC3),
	REG_STRUCT_INIT(AR5K_CPCOVF),
	REG_STRUCT_INIT(AR5K_RESET_CTL),
	REG_STRUCT_INIT(AR5K_SLEEP_CTL),
	REG_STRUCT_INIT(AR5K_INTPEND),
	REG_STRUCT_INIT(AR5K_SFR),
	REG_STRUCT_INIT(AR5K_PCICFG),
	REG_STRUCT_INIT(AR5K_GPIOCR),
	REG_STRUCT_INIT(AR5K_GPIODO),
	REG_STRUCT_INIT(AR5K_SREV),
पूर्ण;

अटल व्योम *reg_start(काष्ठा seq_file *seq, loff_t *pos)
अणु
	वापस *pos < ARRAY_SIZE(regs) ? (व्योम *)&regs[*pos] : शून्य;
पूर्ण

अटल व्योम reg_stop(काष्ठा seq_file *seq, व्योम *p)
अणु
	/* nothing to करो */
पूर्ण

अटल व्योम *reg_next(काष्ठा seq_file *seq, व्योम *p, loff_t *pos)
अणु
	++*pos;
	वापस *pos < ARRAY_SIZE(regs) ? (व्योम *)&regs[*pos] : शून्य;
पूर्ण

अटल पूर्णांक reg_show(काष्ठा seq_file *seq, व्योम *p)
अणु
	काष्ठा ath5k_hw *ah = seq->निजी;
	काष्ठा reg *r = p;
	seq_म_लिखो(seq, "%-25s0x%08x\n", r->name,
		ath5k_hw_reg_पढ़ो(ah, r->addr));
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations रेजिस्टरs_sops = अणु
	.start = reg_start,
	.next  = reg_next,
	.stop  = reg_stop,
	.show  = reg_show
पूर्ण;

DEFINE_SEQ_ATTRIBUTE(रेजिस्टरs);

/* debugfs: beacons */

अटल sमाप_प्रकार पढ़ो_file_beacon(काष्ठा file *file, अक्षर __user *user_buf,
				   माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath5k_hw *ah = file->निजी_data;
	अक्षर buf[500];
	अचिन्हित पूर्णांक len = 0;
	अचिन्हित पूर्णांक v;
	u64 tsf;

	v = ath5k_hw_reg_पढ़ो(ah, AR5K_BEACON);
	len += scnम_लिखो(buf + len, माप(buf) - len,
		"%-24s0x%08x\tintval: %d\tTIM: 0x%x\n",
		"AR5K_BEACON", v, v & AR5K_BEACON_PERIOD,
		(v & AR5K_BEACON_TIM) >> AR5K_BEACON_TIM_S);

	len += scnम_लिखो(buf + len, माप(buf) - len, "%-24s0x%08x\n",
		"AR5K_LAST_TSTP", ath5k_hw_reg_पढ़ो(ah, AR5K_LAST_TSTP));

	len += scnम_लिखो(buf + len, माप(buf) - len, "%-24s0x%08x\n\n",
		"AR5K_BEACON_CNT", ath5k_hw_reg_पढ़ो(ah, AR5K_BEACON_CNT));

	v = ath5k_hw_reg_पढ़ो(ah, AR5K_TIMER0);
	len += scnम_लिखो(buf + len, माप(buf) - len, "%-24s0x%08x\tTU: %08x\n",
		"AR5K_TIMER0 (TBTT)", v, v);

	v = ath5k_hw_reg_पढ़ो(ah, AR5K_TIMER1);
	len += scnम_लिखो(buf + len, माप(buf) - len, "%-24s0x%08x\tTU: %08x\n",
		"AR5K_TIMER1 (DMA)", v, v >> 3);

	v = ath5k_hw_reg_पढ़ो(ah, AR5K_TIMER2);
	len += scnम_लिखो(buf + len, माप(buf) - len, "%-24s0x%08x\tTU: %08x\n",
		"AR5K_TIMER2 (SWBA)", v, v >> 3);

	v = ath5k_hw_reg_पढ़ो(ah, AR5K_TIMER3);
	len += scnम_लिखो(buf + len, माप(buf) - len, "%-24s0x%08x\tTU: %08x\n",
		"AR5K_TIMER3 (ATIM)", v, v);

	tsf = ath5k_hw_get_tsf64(ah);
	len += scnम_लिखो(buf + len, माप(buf) - len,
		"TSF\t\t0x%016llx\tTU: %08x\n",
		(अचिन्हित दीर्घ दीर्घ)tsf, TSF_TO_TU(tsf));

	अगर (len > माप(buf))
		len = माप(buf);

	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, len);
पूर्ण

अटल sमाप_प्रकार ग_लिखो_file_beacon(काष्ठा file *file,
				 स्थिर अक्षर __user *userbuf,
				 माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath5k_hw *ah = file->निजी_data;
	अक्षर buf[20];

	count = min_t(माप_प्रकार, count, माप(buf) - 1);
	अगर (copy_from_user(buf, userbuf, count))
		वापस -EFAULT;

	buf[count] = '\0';
	अगर (म_भेदन(buf, "disable", 7) == 0) अणु
		AR5K_REG_DISABLE_BITS(ah, AR5K_BEACON, AR5K_BEACON_ENABLE);
		pr_info("debugfs disable beacons\n");
	पूर्ण अन्यथा अगर (म_भेदन(buf, "enable", 6) == 0) अणु
		AR5K_REG_ENABLE_BITS(ah, AR5K_BEACON, AR5K_BEACON_ENABLE);
		pr_info("debugfs enable beacons\n");
	पूर्ण
	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations fops_beacon = अणु
	.पढ़ो = पढ़ो_file_beacon,
	.ग_लिखो = ग_लिखो_file_beacon,
	.खोलो = simple_खोलो,
	.owner = THIS_MODULE,
	.llseek = शेष_llseek,
पूर्ण;


/* debugfs: reset */

अटल sमाप_प्रकार ग_लिखो_file_reset(काष्ठा file *file,
				 स्थिर अक्षर __user *userbuf,
				 माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath5k_hw *ah = file->निजी_data;
	ATH5K_DBG(ah, ATH5K_DEBUG_RESET, "debug file triggered reset\n");
	ieee80211_queue_work(ah->hw, &ah->reset_work);
	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations fops_reset = अणु
	.ग_लिखो = ग_लिखो_file_reset,
	.खोलो = simple_खोलो,
	.owner = THIS_MODULE,
	.llseek = noop_llseek,
पूर्ण;


/* debugfs: debug level */

अटल स्थिर काष्ठा अणु
	क्रमागत ath5k_debug_level level;
	स्थिर अक्षर *name;
	स्थिर अक्षर *desc;
पूर्ण dbg_info[] = अणु
	अणु ATH5K_DEBUG_RESET,	"reset",	"reset and initialization" पूर्ण,
	अणु ATH5K_DEBUG_INTR,	"intr",		"interrupt handling" पूर्ण,
	अणु ATH5K_DEBUG_MODE,	"mode",		"mode init/setup" पूर्ण,
	अणु ATH5K_DEBUG_XMIT,	"xmit",		"basic xmit operation" पूर्ण,
	अणु ATH5K_DEBUG_BEACON,	"beacon",	"beacon handling" पूर्ण,
	अणु ATH5K_DEBUG_CALIBRATE, "calib",	"periodic calibration" पूर्ण,
	अणु ATH5K_DEBUG_TXPOWER,	"txpower",	"transmit power setting" पूर्ण,
	अणु ATH5K_DEBUG_LED,	"led",		"LED management" पूर्ण,
	अणु ATH5K_DEBUG_DUMPBANDS, "dumpbands",	"dump bands" पूर्ण,
	अणु ATH5K_DEBUG_DMA,	"dma",		"dma start/stop" पूर्ण,
	अणु ATH5K_DEBUG_ANI,	"ani",		"adaptive noise immunity" पूर्ण,
	अणु ATH5K_DEBUG_DESC,	"desc",		"descriptor chains" पूर्ण,
	अणु ATH5K_DEBUG_ANY,	"all",		"show all debug levels" पूर्ण,
पूर्ण;

अटल sमाप_प्रकार पढ़ो_file_debug(काष्ठा file *file, अक्षर __user *user_buf,
				   माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath5k_hw *ah = file->निजी_data;
	अक्षर buf[700];
	अचिन्हित पूर्णांक len = 0;
	अचिन्हित पूर्णांक i;

	len += scnम_लिखो(buf + len, माप(buf) - len,
		"DEBUG LEVEL: 0x%08x\n\n", ah->debug.level);

	क्रम (i = 0; i < ARRAY_SIZE(dbg_info) - 1; i++) अणु
		len += scnम_लिखो(buf + len, माप(buf) - len,
			"%10s %c 0x%08x - %s\n", dbg_info[i].name,
			ah->debug.level & dbg_info[i].level ? '+' : ' ',
			dbg_info[i].level, dbg_info[i].desc);
	पूर्ण
	len += scnम_लिखो(buf + len, माप(buf) - len,
		"%10s %c 0x%08x - %s\n", dbg_info[i].name,
		ah->debug.level == dbg_info[i].level ? '+' : ' ',
		dbg_info[i].level, dbg_info[i].desc);

	अगर (len > माप(buf))
		len = माप(buf);

	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, len);
पूर्ण

अटल sमाप_प्रकार ग_लिखो_file_debug(काष्ठा file *file,
				 स्थिर अक्षर __user *userbuf,
				 माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath5k_hw *ah = file->निजी_data;
	अचिन्हित पूर्णांक i;
	अक्षर buf[20];

	count = min_t(माप_प्रकार, count, माप(buf) - 1);
	अगर (copy_from_user(buf, userbuf, count))
		वापस -EFAULT;

	buf[count] = '\0';
	क्रम (i = 0; i < ARRAY_SIZE(dbg_info); i++) अणु
		अगर (म_भेदन(buf, dbg_info[i].name,
					म_माप(dbg_info[i].name)) == 0) अणु
			ah->debug.level ^= dbg_info[i].level; /* toggle bit */
			अवरोध;
		पूर्ण
	पूर्ण
	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations fops_debug = अणु
	.पढ़ो = पढ़ो_file_debug,
	.ग_लिखो = ग_लिखो_file_debug,
	.खोलो = simple_खोलो,
	.owner = THIS_MODULE,
	.llseek = शेष_llseek,
पूर्ण;


/* debugfs: antenna */

अटल sमाप_प्रकार पढ़ो_file_antenna(काष्ठा file *file, अक्षर __user *user_buf,
				   माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath5k_hw *ah = file->निजी_data;
	अक्षर buf[700];
	अचिन्हित पूर्णांक len = 0;
	अचिन्हित पूर्णांक i;
	अचिन्हित पूर्णांक v;

	len += scnम_लिखो(buf + len, माप(buf) - len, "antenna mode\t%d\n",
		ah->ah_ant_mode);
	len += scnम_लिखो(buf + len, माप(buf) - len, "default antenna\t%d\n",
		ah->ah_def_ant);
	len += scnम_लिखो(buf + len, माप(buf) - len, "tx antenna\t%d\n",
		ah->ah_tx_ant);

	len += scnम_लिखो(buf + len, माप(buf) - len, "\nANTENNA\t\tRX\tTX\n");
	क्रम (i = 1; i < ARRAY_SIZE(ah->stats.antenna_rx); i++) अणु
		len += scnम_लिखो(buf + len, माप(buf) - len,
			"[antenna %d]\t%d\t%d\n",
			i, ah->stats.antenna_rx[i], ah->stats.antenna_tx[i]);
	पूर्ण
	len += scnम_लिखो(buf + len, माप(buf) - len, "[invalid]\t%d\t%d\n",
			ah->stats.antenna_rx[0], ah->stats.antenna_tx[0]);

	v = ath5k_hw_reg_पढ़ो(ah, AR5K_DEFAULT_ANTENNA);
	len += scnम_लिखो(buf + len, माप(buf) - len,
			"\nAR5K_DEFAULT_ANTENNA\t0x%08x\n", v);

	v = ath5k_hw_reg_पढ़ो(ah, AR5K_STA_ID1);
	len += scnम_लिखो(buf + len, माप(buf) - len,
		"AR5K_STA_ID1_DEFAULT_ANTENNA\t%d\n",
		(v & AR5K_STA_ID1_DEFAULT_ANTENNA) != 0);
	len += scnम_लिखो(buf + len, माप(buf) - len,
		"AR5K_STA_ID1_DESC_ANTENNA\t%d\n",
		(v & AR5K_STA_ID1_DESC_ANTENNA) != 0);
	len += scnम_लिखो(buf + len, माप(buf) - len,
		"AR5K_STA_ID1_RTS_DEF_ANTENNA\t%d\n",
		(v & AR5K_STA_ID1_RTS_DEF_ANTENNA) != 0);
	len += scnम_लिखो(buf + len, माप(buf) - len,
		"AR5K_STA_ID1_SELFGEN_DEF_ANT\t%d\n",
		(v & AR5K_STA_ID1_SELFGEN_DEF_ANT) != 0);

	v = ath5k_hw_reg_पढ़ो(ah, AR5K_PHY_AGCCTL);
	len += scnम_लिखो(buf + len, माप(buf) - len,
		"\nAR5K_PHY_AGCCTL_OFDM_DIV_DIS\t%d\n",
		(v & AR5K_PHY_AGCCTL_OFDM_DIV_DIS) != 0);

	v = ath5k_hw_reg_पढ़ो(ah, AR5K_PHY_RESTART);
	len += scnम_लिखो(buf + len, माप(buf) - len,
		"AR5K_PHY_RESTART_DIV_GC\t\t%x\n",
		(v & AR5K_PHY_RESTART_DIV_GC) >> AR5K_PHY_RESTART_DIV_GC_S);

	v = ath5k_hw_reg_पढ़ो(ah, AR5K_PHY_FAST_ANT_DIV);
	len += scnम_लिखो(buf + len, माप(buf) - len,
		"AR5K_PHY_FAST_ANT_DIV_EN\t%d\n",
		(v & AR5K_PHY_FAST_ANT_DIV_EN) != 0);

	v = ath5k_hw_reg_पढ़ो(ah, AR5K_PHY_ANT_SWITCH_TABLE_0);
	len += scnम_लिखो(buf + len, माप(buf) - len,
			"\nAR5K_PHY_ANT_SWITCH_TABLE_0\t0x%08x\n", v);
	v = ath5k_hw_reg_पढ़ो(ah, AR5K_PHY_ANT_SWITCH_TABLE_1);
	len += scnम_लिखो(buf + len, माप(buf) - len,
			"AR5K_PHY_ANT_SWITCH_TABLE_1\t0x%08x\n", v);

	अगर (len > माप(buf))
		len = माप(buf);

	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, len);
पूर्ण

अटल sमाप_प्रकार ग_लिखो_file_antenna(काष्ठा file *file,
				 स्थिर अक्षर __user *userbuf,
				 माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath5k_hw *ah = file->निजी_data;
	अचिन्हित पूर्णांक i;
	अक्षर buf[20];

	count = min_t(माप_प्रकार, count, माप(buf) - 1);
	अगर (copy_from_user(buf, userbuf, count))
		वापस -EFAULT;

	buf[count] = '\0';
	अगर (म_भेदन(buf, "diversity", 9) == 0) अणु
		ath5k_hw_set_antenna_mode(ah, AR5K_ANTMODE_DEFAULT);
		pr_info("debug: enable diversity\n");
	पूर्ण अन्यथा अगर (म_भेदन(buf, "fixed-a", 7) == 0) अणु
		ath5k_hw_set_antenna_mode(ah, AR5K_ANTMODE_FIXED_A);
		pr_info("debug: fixed antenna A\n");
	पूर्ण अन्यथा अगर (म_भेदन(buf, "fixed-b", 7) == 0) अणु
		ath5k_hw_set_antenna_mode(ah, AR5K_ANTMODE_FIXED_B);
		pr_info("debug: fixed antenna B\n");
	पूर्ण अन्यथा अगर (म_भेदन(buf, "clear", 5) == 0) अणु
		क्रम (i = 0; i < ARRAY_SIZE(ah->stats.antenna_rx); i++) अणु
			ah->stats.antenna_rx[i] = 0;
			ah->stats.antenna_tx[i] = 0;
		पूर्ण
		pr_info("debug: cleared antenna stats\n");
	पूर्ण
	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations fops_antenna = अणु
	.पढ़ो = पढ़ो_file_antenna,
	.ग_लिखो = ग_लिखो_file_antenna,
	.खोलो = simple_खोलो,
	.owner = THIS_MODULE,
	.llseek = शेष_llseek,
पूर्ण;

/* debugfs: misc */

अटल sमाप_प्रकार पढ़ो_file_misc(काष्ठा file *file, अक्षर __user *user_buf,
				   माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath5k_hw *ah = file->निजी_data;
	अक्षर buf[700];
	अचिन्हित पूर्णांक len = 0;
	u32 filt = ath5k_hw_get_rx_filter(ah);

	len += scnम_लिखो(buf + len, माप(buf) - len, "bssid-mask: %pM\n",
			ah->bssidmask);
	len += scnम_लिखो(buf + len, माप(buf) - len, "filter-flags: 0x%x ",
			filt);
	अगर (filt & AR5K_RX_FILTER_UCAST)
		len += scnम_लिखो(buf + len, माप(buf) - len, " UCAST");
	अगर (filt & AR5K_RX_FILTER_MCAST)
		len += scnम_लिखो(buf + len, माप(buf) - len, " MCAST");
	अगर (filt & AR5K_RX_FILTER_BCAST)
		len += scnम_लिखो(buf + len, माप(buf) - len, " BCAST");
	अगर (filt & AR5K_RX_FILTER_CONTROL)
		len += scnम_लिखो(buf + len, माप(buf) - len, " CONTROL");
	अगर (filt & AR5K_RX_FILTER_BEACON)
		len += scnम_लिखो(buf + len, माप(buf) - len, " BEACON");
	अगर (filt & AR5K_RX_FILTER_PROM)
		len += scnम_लिखो(buf + len, माप(buf) - len, " PROM");
	अगर (filt & AR5K_RX_FILTER_XRPOLL)
		len += scnम_लिखो(buf + len, माप(buf) - len, " XRPOLL");
	अगर (filt & AR5K_RX_FILTER_PROBEREQ)
		len += scnम_लिखो(buf + len, माप(buf) - len, " PROBEREQ");
	अगर (filt & AR5K_RX_FILTER_PHYERR_5212)
		len += scnम_लिखो(buf + len, माप(buf) - len, " PHYERR-5212");
	अगर (filt & AR5K_RX_FILTER_RADARERR_5212)
		len += scnम_लिखो(buf + len, माप(buf) - len, " RADARERR-5212");
	अगर (filt & AR5K_RX_FILTER_PHYERR_5211)
		snम_लिखो(buf + len, माप(buf) - len, " PHYERR-5211");
	अगर (filt & AR5K_RX_FILTER_RADARERR_5211)
		len += scnम_लिखो(buf + len, माप(buf) - len, " RADARERR-5211");

	len += scnम_लिखो(buf + len, माप(buf) - len, "\nopmode: %s (%d)\n",
			ath_opmode_to_string(ah->opmode), ah->opmode);

	अगर (len > माप(buf))
		len = माप(buf);

	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, len);
पूर्ण

अटल स्थिर काष्ठा file_operations fops_misc = अणु
	.पढ़ो = पढ़ो_file_misc,
	.खोलो = simple_खोलो,
	.owner = THIS_MODULE,
पूर्ण;


/* debugfs: frameerrors */

अटल sमाप_प्रकार पढ़ो_file_frameerrors(काष्ठा file *file, अक्षर __user *user_buf,
				   माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath5k_hw *ah = file->निजी_data;
	काष्ठा ath5k_statistics *st = &ah->stats;
	अक्षर buf[700];
	अचिन्हित पूर्णांक len = 0;
	पूर्णांक i;

	len += scnम_लिखो(buf + len, माप(buf) - len,
			"RX\n---------------------\n");
	len += scnम_लिखो(buf + len, माप(buf) - len, "CRC\t%u\t(%u%%)\n",
			st->rxerr_crc,
			st->rx_all_count > 0 ?
				st->rxerr_crc * 100 / st->rx_all_count : 0);
	len += scnम_लिखो(buf + len, माप(buf) - len, "PHY\t%u\t(%u%%)\n",
			st->rxerr_phy,
			st->rx_all_count > 0 ?
				st->rxerr_phy * 100 / st->rx_all_count : 0);
	क्रम (i = 0; i < 32; i++) अणु
		अगर (st->rxerr_phy_code[i])
			len += scnम_लिखो(buf + len, माप(buf) - len,
				" phy_err[%u]\t%u\n",
				i, st->rxerr_phy_code[i]);
	पूर्ण

	len += scnम_लिखो(buf + len, माप(buf) - len, "FIFO\t%u\t(%u%%)\n",
			st->rxerr_fअगरo,
			st->rx_all_count > 0 ?
				st->rxerr_fअगरo * 100 / st->rx_all_count : 0);
	len += scnम_लिखो(buf + len, माप(buf) - len, "decrypt\t%u\t(%u%%)\n",
			st->rxerr_decrypt,
			st->rx_all_count > 0 ?
				st->rxerr_decrypt * 100 / st->rx_all_count : 0);
	len += scnम_लिखो(buf + len, माप(buf) - len, "MIC\t%u\t(%u%%)\n",
			st->rxerr_mic,
			st->rx_all_count > 0 ?
				st->rxerr_mic * 100 / st->rx_all_count : 0);
	len += scnम_लिखो(buf + len, माप(buf) - len, "process\t%u\t(%u%%)\n",
			st->rxerr_proc,
			st->rx_all_count > 0 ?
				st->rxerr_proc * 100 / st->rx_all_count : 0);
	len += scnम_लिखो(buf + len, माप(buf) - len, "jumbo\t%u\t(%u%%)\n",
			st->rxerr_jumbo,
			st->rx_all_count > 0 ?
				st->rxerr_jumbo * 100 / st->rx_all_count : 0);
	len += scnम_लिखो(buf + len, माप(buf) - len, "[RX all\t%u]\n",
			st->rx_all_count);
	len += scnम_लिखो(buf + len, माप(buf) - len, "RX-all-bytes\t%u\n",
			st->rx_bytes_count);

	len += scnम_लिखो(buf + len, माप(buf) - len,
			"\nTX\n---------------------\n");
	len += scnम_लिखो(buf + len, माप(buf) - len, "retry\t%u\t(%u%%)\n",
			st->txerr_retry,
			st->tx_all_count > 0 ?
				st->txerr_retry * 100 / st->tx_all_count : 0);
	len += scnम_लिखो(buf + len, माप(buf) - len, "FIFO\t%u\t(%u%%)\n",
			st->txerr_fअगरo,
			st->tx_all_count > 0 ?
				st->txerr_fअगरo * 100 / st->tx_all_count : 0);
	len += scnम_लिखो(buf + len, माप(buf) - len, "filter\t%u\t(%u%%)\n",
			st->txerr_filt,
			st->tx_all_count > 0 ?
				st->txerr_filt * 100 / st->tx_all_count : 0);
	len += scnम_लिखो(buf + len, माप(buf) - len, "[TX all\t%u]\n",
			st->tx_all_count);
	len += scnम_लिखो(buf + len, माप(buf) - len, "TX-all-bytes\t%u\n",
			st->tx_bytes_count);

	अगर (len > माप(buf))
		len = माप(buf);

	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, len);
पूर्ण

अटल sमाप_प्रकार ग_लिखो_file_frameerrors(काष्ठा file *file,
				 स्थिर अक्षर __user *userbuf,
				 माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath5k_hw *ah = file->निजी_data;
	काष्ठा ath5k_statistics *st = &ah->stats;
	अक्षर buf[20];

	count = min_t(माप_प्रकार, count, माप(buf) - 1);
	अगर (copy_from_user(buf, userbuf, count))
		वापस -EFAULT;

	buf[count] = '\0';
	अगर (म_भेदन(buf, "clear", 5) == 0) अणु
		st->rxerr_crc = 0;
		st->rxerr_phy = 0;
		st->rxerr_fअगरo = 0;
		st->rxerr_decrypt = 0;
		st->rxerr_mic = 0;
		st->rxerr_proc = 0;
		st->rxerr_jumbo = 0;
		st->rx_all_count = 0;
		st->txerr_retry = 0;
		st->txerr_fअगरo = 0;
		st->txerr_filt = 0;
		st->tx_all_count = 0;
		pr_info("debug: cleared frameerrors stats\n");
	पूर्ण
	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations fops_frameerrors = अणु
	.पढ़ो = पढ़ो_file_frameerrors,
	.ग_लिखो = ग_लिखो_file_frameerrors,
	.खोलो = simple_खोलो,
	.owner = THIS_MODULE,
	.llseek = शेष_llseek,
पूर्ण;


/* debugfs: ani */

अटल sमाप_प्रकार पढ़ो_file_ani(काष्ठा file *file, अक्षर __user *user_buf,
				   माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath5k_hw *ah = file->निजी_data;
	काष्ठा ath5k_statistics *st = &ah->stats;
	काष्ठा ath5k_ani_state *as = &ah->ani_state;

	अक्षर buf[700];
	अचिन्हित पूर्णांक len = 0;

	len += scnम_लिखो(buf + len, माप(buf) - len,
			"HW has PHY error counters:\t%s\n",
			ah->ah_capabilities.cap_has_phyerr_counters ?
			"yes" : "no");
	len += scnम_लिखो(buf + len, माप(buf) - len,
			"HW max spur immunity level:\t%d\n",
			as->max_spur_level);
	len += scnम_लिखो(buf + len, माप(buf) - len,
		"\nANI state\n--------------------------------------------\n");
	len += scnम_लिखो(buf + len, माप(buf) - len, "operating mode:\t\t\t");
	चयन (as->ani_mode) अणु
	हाल ATH5K_ANI_MODE_OFF:
		len += scnम_लिखो(buf + len, माप(buf) - len, "OFF\n");
		अवरोध;
	हाल ATH5K_ANI_MODE_MANUAL_LOW:
		len += scnम_लिखो(buf + len, माप(buf) - len,
			"MANUAL LOW\n");
		अवरोध;
	हाल ATH5K_ANI_MODE_MANUAL_HIGH:
		len += scnम_लिखो(buf + len, माप(buf) - len,
			"MANUAL HIGH\n");
		अवरोध;
	हाल ATH5K_ANI_MODE_AUTO:
		len += scnम_लिखो(buf + len, माप(buf) - len, "AUTO\n");
		अवरोध;
	शेष:
		len += scnम_लिखो(buf + len, माप(buf) - len,
			"??? (not good)\n");
		अवरोध;
	पूर्ण
	len += scnम_लिखो(buf + len, माप(buf) - len,
			"noise immunity level:\t\t%d\n",
			as->noise_imm_level);
	len += scnम_लिखो(buf + len, माप(buf) - len,
			"spur immunity level:\t\t%d\n",
			as->spur_level);
	len += scnम_लिखो(buf + len, माप(buf) - len,
			"firstep level:\t\t\t%d\n",
			as->firstep_level);
	len += scnम_लिखो(buf + len, माप(buf) - len,
			"OFDM weak signal detection:\t%s\n",
			as->ofdm_weak_sig ? "on" : "off");
	len += scnम_लिखो(buf + len, माप(buf) - len,
			"CCK weak signal detection:\t%s\n",
			as->cck_weak_sig ? "on" : "off");

	len += scnम_लिखो(buf + len, माप(buf) - len,
			"\nMIB INTERRUPTS:\t\t%u\n",
			st->mib_पूर्णांकr);
	len += scnम_लिखो(buf + len, माप(buf) - len,
			"beacon RSSI average:\t%d\n",
			(पूर्णांक)ewma_beacon_rssi_पढ़ो(&ah->ah_beacon_rssi_avg));

#घोषणा CC_PRINT(_काष्ठा, _field) \
	_काष्ठा._field, \
	_काष्ठा.cycles > 0 ? \
	_काष्ठा._field * 100 / _काष्ठा.cycles : 0

	len += scnम_लिखो(buf + len, माप(buf) - len,
			"profcnt tx\t\t%u\t(%d%%)\n",
			CC_PRINT(as->last_cc, tx_frame));
	len += scnम_लिखो(buf + len, माप(buf) - len,
			"profcnt rx\t\t%u\t(%d%%)\n",
			CC_PRINT(as->last_cc, rx_frame));
	len += scnम_लिखो(buf + len, माप(buf) - len,
			"profcnt busy\t\t%u\t(%d%%)\n",
			CC_PRINT(as->last_cc, rx_busy));
#अघोषित CC_PRINT
	len += scnम_लिखो(buf + len, माप(buf) - len, "profcnt cycles\t\t%u\n",
			as->last_cc.cycles);
	len += scnम_लिखो(buf + len, माप(buf) - len,
			"listen time\t\t%d\tlast: %d\n",
			as->listen_समय, as->last_listen);
	len += scnम_लिखो(buf + len, माप(buf) - len,
			"OFDM errors\t\t%u\tlast: %u\tsum: %u\n",
			as->ofdm_errors, as->last_ofdm_errors,
			as->sum_ofdm_errors);
	len += scnम_लिखो(buf + len, माप(buf) - len,
			"CCK errors\t\t%u\tlast: %u\tsum: %u\n",
			as->cck_errors, as->last_cck_errors,
			as->sum_cck_errors);
	len += scnम_लिखो(buf + len, माप(buf) - len,
			"AR5K_PHYERR_CNT1\t%x\t(=%d)\n",
			ath5k_hw_reg_पढ़ो(ah, AR5K_PHYERR_CNT1),
			ATH5K_ANI_OFDM_TRIG_HIGH - (ATH5K_PHYERR_CNT_MAX -
			ath5k_hw_reg_पढ़ो(ah, AR5K_PHYERR_CNT1)));
	len += scnम_लिखो(buf + len, माप(buf) - len,
			"AR5K_PHYERR_CNT2\t%x\t(=%d)\n",
			ath5k_hw_reg_पढ़ो(ah, AR5K_PHYERR_CNT2),
			ATH5K_ANI_CCK_TRIG_HIGH - (ATH5K_PHYERR_CNT_MAX -
			ath5k_hw_reg_पढ़ो(ah, AR5K_PHYERR_CNT2)));

	अगर (len > माप(buf))
		len = माप(buf);

	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, len);
पूर्ण

अटल sमाप_प्रकार ग_लिखो_file_ani(काष्ठा file *file,
				 स्थिर अक्षर __user *userbuf,
				 माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath5k_hw *ah = file->निजी_data;
	अक्षर buf[20];

	count = min_t(माप_प्रकार, count, माप(buf) - 1);
	अगर (copy_from_user(buf, userbuf, count))
		वापस -EFAULT;

	buf[count] = '\0';
	अगर (म_भेदन(buf, "sens-low", 8) == 0) अणु
		ath5k_ani_init(ah, ATH5K_ANI_MODE_MANUAL_HIGH);
	पूर्ण अन्यथा अगर (म_भेदन(buf, "sens-high", 9) == 0) अणु
		ath5k_ani_init(ah, ATH5K_ANI_MODE_MANUAL_LOW);
	पूर्ण अन्यथा अगर (म_भेदन(buf, "ani-off", 7) == 0) अणु
		ath5k_ani_init(ah, ATH5K_ANI_MODE_OFF);
	पूर्ण अन्यथा अगर (म_भेदन(buf, "ani-on", 6) == 0) अणु
		ath5k_ani_init(ah, ATH5K_ANI_MODE_AUTO);
	पूर्ण अन्यथा अगर (म_भेदन(buf, "noise-low", 9) == 0) अणु
		ath5k_ani_set_noise_immunity_level(ah, 0);
	पूर्ण अन्यथा अगर (म_भेदन(buf, "noise-high", 10) == 0) अणु
		ath5k_ani_set_noise_immunity_level(ah,
						   ATH5K_ANI_MAX_NOISE_IMM_LVL);
	पूर्ण अन्यथा अगर (म_भेदन(buf, "spur-low", 8) == 0) अणु
		ath5k_ani_set_spur_immunity_level(ah, 0);
	पूर्ण अन्यथा अगर (म_भेदन(buf, "spur-high", 9) == 0) अणु
		ath5k_ani_set_spur_immunity_level(ah,
						  ah->ani_state.max_spur_level);
	पूर्ण अन्यथा अगर (म_भेदन(buf, "fir-low", 7) == 0) अणु
		ath5k_ani_set_firstep_level(ah, 0);
	पूर्ण अन्यथा अगर (म_भेदन(buf, "fir-high", 8) == 0) अणु
		ath5k_ani_set_firstep_level(ah, ATH5K_ANI_MAX_FIRSTEP_LVL);
	पूर्ण अन्यथा अगर (म_भेदन(buf, "ofdm-off", 8) == 0) अणु
		ath5k_ani_set_ofdm_weak_संकेत_detection(ah, false);
	पूर्ण अन्यथा अगर (म_भेदन(buf, "ofdm-on", 7) == 0) अणु
		ath5k_ani_set_ofdm_weak_संकेत_detection(ah, true);
	पूर्ण अन्यथा अगर (म_भेदन(buf, "cck-off", 7) == 0) अणु
		ath5k_ani_set_cck_weak_संकेत_detection(ah, false);
	पूर्ण अन्यथा अगर (म_भेदन(buf, "cck-on", 6) == 0) अणु
		ath5k_ani_set_cck_weak_संकेत_detection(ah, true);
	पूर्ण
	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations fops_ani = अणु
	.पढ़ो = पढ़ो_file_ani,
	.ग_लिखो = ग_लिखो_file_ani,
	.खोलो = simple_खोलो,
	.owner = THIS_MODULE,
	.llseek = शेष_llseek,
पूर्ण;


/* debugfs: queues etc */

अटल sमाप_प्रकार पढ़ो_file_queue(काष्ठा file *file, अक्षर __user *user_buf,
				   माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath5k_hw *ah = file->निजी_data;
	अक्षर buf[700];
	अचिन्हित पूर्णांक len = 0;

	काष्ठा ath5k_txq *txq;
	काष्ठा ath5k_buf *bf, *bf0;
	पूर्णांक i, n;

	len += scnम_लिखो(buf + len, माप(buf) - len,
			"available txbuffers: %d\n", ah->txbuf_len);

	क्रम (i = 0; i < ARRAY_SIZE(ah->txqs); i++) अणु
		txq = &ah->txqs[i];

		len += scnम_लिखो(buf + len, माप(buf) - len,
			"%02d: %ssetup\n", i, txq->setup ? "" : "not ");

		अगर (!txq->setup)
			जारी;

		n = 0;
		spin_lock_bh(&txq->lock);
		list_क्रम_each_entry_safe(bf, bf0, &txq->q, list)
			n++;
		spin_unlock_bh(&txq->lock);

		len += scnम_लिखो(buf + len, माप(buf) - len,
				"  len: %d bufs: %d\n", txq->txq_len, n);
		len += scnम_लिखो(buf + len, माप(buf) - len,
				"  stuck: %d\n", txq->txq_stuck);
	पूर्ण

	अगर (len > माप(buf))
		len = माप(buf);

	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, len);
पूर्ण

अटल sमाप_प्रकार ग_लिखो_file_queue(काष्ठा file *file,
				 स्थिर अक्षर __user *userbuf,
				 माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath5k_hw *ah = file->निजी_data;
	अक्षर buf[20];

	count = min_t(माप_प्रकार, count, माप(buf) - 1);
	अगर (copy_from_user(buf, userbuf, count))
		वापस -EFAULT;

	buf[count] = '\0';
	अगर (म_भेदन(buf, "start", 5) == 0)
		ieee80211_wake_queues(ah->hw);
	अन्यथा अगर (म_भेदन(buf, "stop", 4) == 0)
		ieee80211_stop_queues(ah->hw);

	वापस count;
पूर्ण


अटल स्थिर काष्ठा file_operations fops_queue = अणु
	.पढ़ो = पढ़ो_file_queue,
	.ग_लिखो = ग_लिखो_file_queue,
	.खोलो = simple_खोलो,
	.owner = THIS_MODULE,
	.llseek = शेष_llseek,
पूर्ण;

/* debugfs: eeprom */

काष्ठा eeprom_निजी अणु
	u16 *buf;
	पूर्णांक len;
पूर्ण;

अटल पूर्णांक खोलो_file_eeprom(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा eeprom_निजी *ep;
	काष्ठा ath5k_hw *ah = inode->i_निजी;
	bool res;
	पूर्णांक i, ret;
	u32 eesize;	/* NB: in 16-bit words */
	u16 val, *buf;

	/* Get eeprom size */

	res = ath5k_hw_nvram_पढ़ो(ah, AR5K_EEPROM_SIZE_UPPER, &val);
	अगर (!res)
		वापस -EACCES;

	अगर (val == 0) अणु
		eesize = AR5K_EEPROM_INFO_MAX + AR5K_EEPROM_INFO_BASE;
	पूर्ण अन्यथा अणु
		eesize = (val & AR5K_EEPROM_SIZE_UPPER_MASK) <<
			AR5K_EEPROM_SIZE_ENDLOC_SHIFT;
		ath5k_hw_nvram_पढ़ो(ah, AR5K_EEPROM_SIZE_LOWER, &val);
		eesize = eesize | val;
	पूर्ण

	अगर (eesize > 4096)
		वापस -EINVAL;

	/* Create buffer and पढ़ो in eeprom */

	buf = vदो_स्मृति(array_size(eesize, 2));
	अगर (!buf) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	क्रम (i = 0; i < eesize; ++i) अणु
		अगर (!ath5k_hw_nvram_पढ़ो(ah, i, &val)) अणु
			ret = -EIO;
			जाओ मुक्तbuf;
		पूर्ण
		buf[i] = val;
	पूर्ण

	/* Create निजी काष्ठा and assign to file */

	ep = kदो_स्मृति(माप(*ep), GFP_KERNEL);
	अगर (!ep) अणु
		ret = -ENOMEM;
		जाओ मुक्तbuf;
	पूर्ण

	ep->buf = buf;
	ep->len = eesize * 2;

	file->निजी_data = (व्योम *)ep;

	वापस 0;

मुक्तbuf:
	vमुक्त(buf);
err:
	वापस ret;

पूर्ण

अटल sमाप_प्रकार पढ़ो_file_eeprom(काष्ठा file *file, अक्षर __user *user_buf,
				   माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा eeprom_निजी *ep = file->निजी_data;

	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, ep->buf, ep->len);
पूर्ण

अटल पूर्णांक release_file_eeprom(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा eeprom_निजी *ep = file->निजी_data;

	vमुक्त(ep->buf);
	kमुक्त(ep);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations fops_eeprom = अणु
	.खोलो = खोलो_file_eeprom,
	.पढ़ो = पढ़ो_file_eeprom,
	.release = release_file_eeprom,
	.owner = THIS_MODULE,
पूर्ण;


व्योम
ath5k_debug_init_device(काष्ठा ath5k_hw *ah)
अणु
	काष्ठा dentry *phydir;

	ah->debug.level = ath5k_debug;

	phydir = debugfs_create_dir("ath5k", ah->hw->wiphy->debugfsdir);
	अगर (!phydir)
		वापस;

	debugfs_create_file("debug", 0600, phydir, ah, &fops_debug);
	debugfs_create_file("registers", 0400, phydir, ah, &रेजिस्टरs_fops);
	debugfs_create_file("beacon", 0600, phydir, ah, &fops_beacon);
	debugfs_create_file("reset", 0200, phydir, ah, &fops_reset);
	debugfs_create_file("antenna", 0600, phydir, ah, &fops_antenna);
	debugfs_create_file("misc", 0400, phydir, ah, &fops_misc);
	debugfs_create_file("eeprom", 0400, phydir, ah, &fops_eeprom);
	debugfs_create_file("frameerrors", 0600, phydir, ah, &fops_frameerrors);
	debugfs_create_file("ani", 0600, phydir, ah, &fops_ani);
	debugfs_create_file("queue", 0600, phydir, ah, &fops_queue);
	debugfs_create_bool("32khz_clock", 0600, phydir,
			    &ah->ah_use_32khz_घड़ी);
पूर्ण

/* functions used in other places */

व्योम
ath5k_debug_dump_bands(काष्ठा ath5k_hw *ah)
अणु
	अचिन्हित पूर्णांक b, i;

	अगर (likely(!(ah->debug.level & ATH5K_DEBUG_DUMPBANDS)))
		वापस;

	क्रम (b = 0; b < NUM_NL80211_BANDS; b++) अणु
		काष्ठा ieee80211_supported_band *band = &ah->sbands[b];
		अक्षर bname[6];
		चयन (band->band) अणु
		हाल NL80211_BAND_2GHZ:
			म_नकल(bname, "2 GHz");
			अवरोध;
		हाल NL80211_BAND_5GHZ:
			म_नकल(bname, "5 GHz");
			अवरोध;
		शेष:
			prपूर्णांकk(KERN_DEBUG "Band not supported: %d\n",
				band->band);
			वापस;
		पूर्ण
		prपूर्णांकk(KERN_DEBUG "Band %s: channels %d, rates %d\n", bname,
				band->n_channels, band->n_bitrates);
		prपूर्णांकk(KERN_DEBUG " channels:\n");
		क्रम (i = 0; i < band->n_channels; i++)
			prपूर्णांकk(KERN_DEBUG "  %3d %d %.4x %.4x\n",
					ieee80211_frequency_to_channel(
						band->channels[i].center_freq),
					band->channels[i].center_freq,
					band->channels[i].hw_value,
					band->channels[i].flags);
		prपूर्णांकk(KERN_DEBUG " rates:\n");
		क्रम (i = 0; i < band->n_bitrates; i++)
			prपूर्णांकk(KERN_DEBUG "  %4d %.4x %.4x %.4x\n",
					band->bitrates[i].bitrate,
					band->bitrates[i].hw_value,
					band->bitrates[i].flags,
					band->bitrates[i].hw_value_लघु);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम
ath5k_debug_prपूर्णांकrxbuf(काष्ठा ath5k_buf *bf, पूर्णांक करोne,
		       काष्ठा ath5k_rx_status *rs)
अणु
	काष्ठा ath5k_desc *ds = bf->desc;
	काष्ठा ath5k_hw_all_rx_desc *rd = &ds->ud.ds_rx;

	prपूर्णांकk(KERN_DEBUG "R (%p %llx) %08x %08x %08x %08x %08x %08x %c\n",
		ds, (अचिन्हित दीर्घ दीर्घ)bf->daddr,
		ds->ds_link, ds->ds_data,
		rd->rx_ctl.rx_control_0, rd->rx_ctl.rx_control_1,
		rd->rx_stat.rx_status_0, rd->rx_stat.rx_status_1,
		!करोne ? ' ' : (rs->rs_status == 0) ? '*' : '!');
पूर्ण

व्योम
ath5k_debug_prपूर्णांकrxbuffs(काष्ठा ath5k_hw *ah)
अणु
	काष्ठा ath5k_desc *ds;
	काष्ठा ath5k_buf *bf;
	काष्ठा ath5k_rx_status rs = अणुपूर्ण;
	पूर्णांक status;

	अगर (likely(!(ah->debug.level & ATH5K_DEBUG_DESC)))
		वापस;

	prपूर्णांकk(KERN_DEBUG "rxdp %x, rxlink %p\n",
		ath5k_hw_get_rxdp(ah), ah->rxlink);

	spin_lock_bh(&ah->rxbuflock);
	list_क्रम_each_entry(bf, &ah->rxbuf, list) अणु
		ds = bf->desc;
		status = ah->ah_proc_rx_desc(ah, ds, &rs);
		अगर (!status)
			ath5k_debug_prपूर्णांकrxbuf(bf, status == 0, &rs);
	पूर्ण
	spin_unlock_bh(&ah->rxbuflock);
पूर्ण

व्योम
ath5k_debug_prपूर्णांकtxbuf(काष्ठा ath5k_hw *ah, काष्ठा ath5k_buf *bf)
अणु
	काष्ठा ath5k_desc *ds = bf->desc;
	काष्ठा ath5k_hw_5212_tx_desc *td = &ds->ud.ds_tx5212;
	काष्ठा ath5k_tx_status ts = अणुपूर्ण;
	पूर्णांक करोne;

	अगर (likely(!(ah->debug.level & ATH5K_DEBUG_DESC)))
		वापस;

	करोne = ah->ah_proc_tx_desc(ah, bf->desc, &ts);

	prपूर्णांकk(KERN_DEBUG "T (%p %llx) %08x %08x %08x %08x %08x %08x %08x "
		"%08x %c\n", ds, (अचिन्हित दीर्घ दीर्घ)bf->daddr, ds->ds_link,
		ds->ds_data, td->tx_ctl.tx_control_0, td->tx_ctl.tx_control_1,
		td->tx_ctl.tx_control_2, td->tx_ctl.tx_control_3,
		td->tx_stat.tx_status_0, td->tx_stat.tx_status_1,
		करोne ? ' ' : (ts.ts_status == 0) ? '*' : '!');
पूर्ण
