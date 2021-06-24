<शैली गुरु>
/*
 * Copyright (c) 2007 Bruno Ranकरोlf <bruno@thinktube.com>
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

#अगर_अघोषित _ATH5K_DEBUG_H
#घोषणा _ATH5K_DEBUG_H

काष्ठा ath5k_hw;
काष्ठा sk_buff;
काष्ठा ath5k_buf;

काष्ठा ath5k_dbg_info अणु
	अचिन्हित पूर्णांक		level;		/* debug level */
पूर्ण;

/**
 * क्रमागत ath5k_debug_level - ath5k debug level
 *
 * @ATH5K_DEBUG_RESET: reset processing
 * @ATH5K_DEBUG_INTR: पूर्णांकerrupt handling
 * @ATH5K_DEBUG_MODE: mode init/setup
 * @ATH5K_DEBUG_XMIT: basic xmit operation
 * @ATH5K_DEBUG_BEACON: beacon handling
 * @ATH5K_DEBUG_CALIBRATE: periodic calibration
 * @ATH5K_DEBUG_TXPOWER: transmit घातer setting
 * @ATH5K_DEBUG_LED: led management
 * @ATH5K_DEBUG_DUMP_RX: prपूर्णांक received skb content
 * @ATH5K_DEBUG_DUMP_TX: prपूर्णांक transmit skb content
 * @ATH5K_DEBUG_DUMPBANDS: dump bands
 * @ATH5K_DEBUG_DMA: debug dma start/stop
 * @ATH5K_DEBUG_TRACE: trace function calls
 * @ATH5K_DEBUG_DESC: descriptor setup
 * @ATH5K_DEBUG_ANY: show at any debug level
 *
 * The debug level is used to control the amount and type of debugging output
 * we want to see. The debug level is given in calls to ATH5K_DBG to specअगरy
 * where the message should appear, and the user can control the debugging
 * messages he wants to see, either by the module parameter 'debug' on module
 * load, or dynamically by using debugfs 'ath5k/phyX/debug'. these levels can
 * be combined together by bitwise OR.
 */
क्रमागत ath5k_debug_level अणु
	ATH5K_DEBUG_RESET	= 0x00000001,
	ATH5K_DEBUG_INTR	= 0x00000002,
	ATH5K_DEBUG_MODE	= 0x00000004,
	ATH5K_DEBUG_XMIT	= 0x00000008,
	ATH5K_DEBUG_BEACON	= 0x00000010,
	ATH5K_DEBUG_CALIBRATE	= 0x00000020,
	ATH5K_DEBUG_TXPOWER	= 0x00000040,
	ATH5K_DEBUG_LED		= 0x00000080,
	ATH5K_DEBUG_DUMPBANDS	= 0x00000400,
	ATH5K_DEBUG_DMA		= 0x00000800,
	ATH5K_DEBUG_ANI		= 0x00002000,
	ATH5K_DEBUG_DESC	= 0x00004000,
	ATH5K_DEBUG_ANY		= 0xffffffff
पूर्ण;

#अगर_घोषित CONFIG_ATH5K_DEBUG

#घोषणा ATH5K_DBG(_sc, _m, _fmt, ...) करो अणु \
	अगर (unlikely((_sc)->debug.level & (_m) && net_ratelimit())) \
		ATH5K_PRINTK(_sc, KERN_DEBUG, "(%s:%d): " _fmt, \
			__func__, __LINE__, ##__VA_ARGS__); \
	पूर्ण जबतक (0)

#घोषणा ATH5K_DBG_UNLIMIT(_sc, _m, _fmt, ...) करो अणु \
	अगर (unlikely((_sc)->debug.level & (_m))) \
		ATH5K_PRINTK(_sc, KERN_DEBUG, "(%s:%d): " _fmt, \
			__func__, __LINE__, ##__VA_ARGS__); \
	पूर्ण जबतक (0)

व्योम
ath5k_debug_init_device(काष्ठा ath5k_hw *ah);

व्योम
ath5k_debug_prपूर्णांकrxbuffs(काष्ठा ath5k_hw *ah);

व्योम
ath5k_debug_dump_bands(काष्ठा ath5k_hw *ah);

व्योम
ath5k_debug_prपूर्णांकtxbuf(काष्ठा ath5k_hw *ah, काष्ठा ath5k_buf *bf);

#अन्यथा /* no debugging */

#समावेश <linux/compiler.h>

अटल अंतरभूत __म_लिखो(3, 4) व्योम
ATH5K_DBG(काष्ठा ath5k_hw *ah, अचिन्हित पूर्णांक m, स्थिर अक्षर *fmt, ...) अणुपूर्ण

अटल अंतरभूत __म_लिखो(3, 4) व्योम
ATH5K_DBG_UNLIMIT(काष्ठा ath5k_hw *ah, अचिन्हित पूर्णांक m, स्थिर अक्षर *fmt, ...)
अणुपूर्ण

अटल अंतरभूत व्योम
ath5k_debug_init_device(काष्ठा ath5k_hw *ah) अणुपूर्ण

अटल अंतरभूत व्योम
ath5k_debug_prपूर्णांकrxbuffs(काष्ठा ath5k_hw *ah) अणुपूर्ण

अटल अंतरभूत व्योम
ath5k_debug_dump_bands(काष्ठा ath5k_hw *ah) अणुपूर्ण

अटल अंतरभूत व्योम
ath5k_debug_prपूर्णांकtxbuf(काष्ठा ath5k_hw *ah, काष्ठा ath5k_buf *bf) अणुपूर्ण

#पूर्ण_अगर /* अगरdef CONFIG_ATH5K_DEBUG */

#पूर्ण_अगर /* अगरndef _ATH5K_DEBUG_H */
