<शैली गुरु>
/*
 *  linux/drivers/message/fusion/mptlan.h
 *      IP Over Fibre Channel device driver.
 *      For use with LSI Fibre Channel PCI chip/adapters
 *      running LSI Fusion MPT (Message Passing Technology) firmware.
 *
 *  Copyright (c) 2000-2008 LSI Corporation
 *  (mailto:DL-MPTFusionLinux@lsi.com)
 *
 */
/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/*
    This program is मुक्त software; you can redistribute it and/or modअगरy
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; version 2 of the License.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License क्रम more details.

    NO WARRANTY
    THE PROGRAM IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OR
    CONDITIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED INCLUDING, WITHOUT
    LIMITATION, ANY WARRANTIES OR CONDITIONS OF TITLE, NON-INFRINGEMENT,
    MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE. Each Recipient is
    solely responsible क्रम determining the appropriateness of using and
    distributing the Program and assumes all risks associated with its
    exercise of rights under this Agreement, including but not limited to
    the risks and costs of program errors, damage to or loss of data,
    programs or equipment, and unavailability or पूर्णांकerruption of operations.

    DISCLAIMER OF LIABILITY
    NEITHER RECIPIENT NOR ANY CONTRIBUTORS SHALL HAVE ANY LIABILITY FOR ANY
    सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
    DAMAGES (INCLUDING WITHOUT LIMITATION LOST PROFITS), HOWEVER CAUSED AND
    ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR
    TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
    USE OR DISTRIBUTION OF THE PROGRAM OR THE EXERCISE OF ANY RIGHTS GRANTED
    HEREUNDER, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGES

    You should have received a copy of the GNU General Public License
    aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/
/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/

/* mptlan.h */

#अगर_अघोषित LINUX_MPTLAN_H_INCLUDED
#घोषणा LINUX_MPTLAN_H_INCLUDED
/*****************************************************************************/

#अगर !defined(__GENKSYMS__)
#समावेश <linux/module.h>
#पूर्ण_अगर

#समावेश <linux/netdevice.h>
#समावेश <linux/त्रुटिसं.स>
// #समावेश <linux/etherdevice.h>
#समावेश <linux/fcdevice.h>
// #समावेश <linux/fddidevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/delay.h>

#समावेश <linux/uaccess.h>
#समावेश <यंत्र/पन.स>

    /* Override mptbase.h by pre-defining these! */
#घोषणा MODULEAUTHOR	"LSI Corporation"

#समावेश "mptbase.h"

/*****************************************************************************/
#घोषणा LANAME		"Fusion MPT LAN driver"
#घोषणा LANVER		MPT_LINUX_VERSION_COMMON

#अगर_घोषित MODULE
MODULE_AUTHOR(MODULEAUTHOR);
MODULE_DESCRIPTION(LANAME);
#पूर्ण_अगर
/*****************************************************************************/

#घोषणा MPT_LAN_MAX_BUCKETS_OUT 256
#घोषणा MPT_LAN_BUCKET_THRESH	18 /* 9 buckets in one message */
#घोषणा MPT_LAN_BUCKETS_REMAIN_MISMATCH_THRESH 10
#घोषणा MPT_LAN_RX_COPYBREAK	200
#घोषणा MPT_LAN_TX_TIMEOUT	(1*HZ)
#घोषणा MPT_TX_MAX_OUT_LIM      127

#घोषणा MPT_LAN_MIN_MTU		96		/* RFC2625 */
#घोषणा MPT_LAN_MAX_MTU		65280		/* RFC2625 */
#घोषणा MPT_LAN_MTU             13312		/* Max perf range + lower mem
						   usage than 16128 */

#घोषणा MPT_LAN_NAA_RFC2625     0x1
#घोषणा MPT_LAN_NAA_QLOGIC      0x2

/* MPT LAN Reset and Suspend Resource Flags Defines */

#घोषणा MPT_LAN_RESOURCE_FLAG_RETURN_POSTED_BUCKETS    0x01
#घोषणा MPT_LAN_RESOURCE_FLAG_RETURN_PEND_TRANSMITS    0x02

/*****************************************************************************/
#अगर_घोषित MPT_LAN_IO_DEBUG
#घोषणा dioprपूर्णांकk(x)  prपूर्णांकk x
#अन्यथा
#घोषणा dioprपूर्णांकk(x)  no_prपूर्णांकk x
#पूर्ण_अगर

#अगर_घोषित MPT_LAN_DEBUG
#घोषणा dlprपूर्णांकk(x)  prपूर्णांकk x
#अन्यथा
#घोषणा dlprपूर्णांकk(x)  no_prपूर्णांकk x
#पूर्ण_अगर

#घोषणा NETDEV_TO_LANPRIV_PTR(d)	((काष्ठा mpt_lan_priv *)netdev_priv(d))
#घोषणा NETDEV_PTR_TO_IOC_NAME_s(d)	(NETDEV_TO_LANPRIV_PTR(d)->mpt_dev->name)
#घोषणा IOC_AND_NETDEV_NAMES_s_s(d)	NETDEV_PTR_TO_IOC_NAME_s(d), (d)->name

/*****************************************************************************/
#पूर्ण_अगर

